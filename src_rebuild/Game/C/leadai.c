#include "driver2.h"
#include "leadai.h"
#include "overlay.h"
#include "gamesnd.h"
#include "dr2roads.h"
#include "replays.h"
#include "players.h"
#include "camera.h"
#include "cars.h"
#include "spool.h"
#include "handling.h"
#include "map.h"
#include "cell.h"
#include "draw.h"
#include "models.h"
#include "main.h"
#include "pad.h"
#include "pres.h"
#include "shadow.h"

#define NUM_RAND_STATES		17
#define NUM_RAND_ITERATIONS	40

static int randIndex;
static int randState[NUM_RAND_STATES];

LEAD_PARAMETERS LeadValues;

static int pathParams[5] = {
	20480,-8192, 2048,-4096, 800
};

int road_s = 0;
int road_c = 0;

struct MAP_DATA
{
	CAR_DATA* cp;
	VECTOR* base;
	VECTOR* pos;
	VECTOR* vel;
	VECTOR* size;
	int intention;
	int* map;
	int* local;
};

enum LeadDriveState
{
	LeadDrive_Handbrake = 0,
	LeadDrive_DropPedals = 1,
	LeadDrive_CorrectOversteer = 2,
	LeadDrive_NormalDrive = 3,
	LeadDrive_Unstuck = 4,
	LeadDrive_Panic = 5,
	LeadDrive_EmergencyBrake = 6,
	LeadDrive_Wheelspin = 7,
	LeadDrive_FakeMotion = 8,
};

void CheckCurrentRoad(CAR_DATA* cp);
void UpdateRoadPosition(CAR_DATA* cp, VECTOR* basePos, int intention);
void FakeMotion(CAR_DATA* cp);
void SelectExit(CAR_DATA* cp, DRIVER2_JUNCTION* junction);
void SetTarget(CAR_DATA* cp, int curRoad, int heading, int* nextJunction);

// [D] [T]
int leadRand(void)
{
	randIndex = (randIndex + 1) % NUM_RAND_STATES;

	return randState[randIndex] += randState[(randIndex + 12) % NUM_RAND_STATES];
}

// [D] [T]
void InitLead(CAR_DATA* cp)
{
	int x, z;
	int i;

	cp->hndType = 5;
	cp->controlType = CONTROL_TYPE_LEAD_AI;
	cp->ai.l.roadPosition = 512;
	cp->ai.l.dstate = LeadDrive_NormalDrive;
	cp->ai.l.recoverTime = 40;
	cp->ai.l.nextExit = 2;
	cp->ai.l.roadForward = 5120;
	cp->ai.l.takeDamage = 0;

	x = cp->hd.where.t[0];
	z = cp->hd.where.t[2];

	if (valid_region(x, z))
	{
		cp->ai.l.currentRoad = GetSurfaceIndex((VECTOR*)cp->hd.where.t);
	}
	else
	{
		DRIVER2_STRAIGHT* straight;
		DRIVER2_CURVE* curve;

		int dx, dz;
		int sqrdist;
		int min;

		min = -1;

		for (i = 0; i < NumDriver2Straights; i++)
		{
			straight = &Driver2StraightsPtr[i];

			dx = (x - straight->Midx) >> 10;
			dz = (z - straight->Midz) >> 10;

			sqrdist = dx * dx + dz * dz;

			if (dx <= 1000 && dz <= 1000 && (sqrdist < min || min == -1))
			{
				cp->ai.l.currentRoad = i;
				min = sqrdist;
			}
		}

		for (i = 0; i < NumDriver2Curves; i++)
		{
			curve = &Driver2CurvesPtr[i];

			dx = (x - curve->Midx) >> 10;
			dz = (z - curve->Midz) >> 10;

			sqrdist = dx * dx + dz * dz;

			if (dx <= 1000 && dz <= 1000 && (sqrdist < min || min == -1))
			{
				cp->ai.l.currentRoad = i & 0x4000;
				min = sqrdist;
			}
		}
	}

	randState[0] = 0x27a2a;
	randState[1] = 0x717d58;
	randState[2] = 0x38b0;
	randState[3] = 0x701ced;
	randState[4] = 0xbdfda3;
	randState[5] = 0xe;
	randState[6] = 0x268833;
	randState[7] = 0x8748;
	randState[8] = 0x180d85;
	randState[9] = 0x127fba;
	randState[10] = 0x1678874;
	randState[11] = 0x3941b;
	randState[12] = 0x701d01;
	randState[13] = 0x39369;
	randState[14] = 0x1d98;
	randState[15] = 0x165dab9;
	randState[16] = 0xe9d4a4;

	randIndex = 0;

	InitLeadHorn();
}

// [D] [T] - needless to say, the AI isn't very smart :D
void LeadUpdateState(CAR_DATA* cp)
{
	volatile int dx, dz;
	volatile int x, z;

	volatile int avel;
	volatile int end;

	VECTOR tmpStart = { 0 };
	VECTOR pos = { 0 };

	x = cp->hd.where.t[0];
	z = cp->hd.where.t[2];

	// is he spooled in?
	if (!valid_region(x, z)
		|| ABS(x - player[0].pos[0]) > 15900
		|| ABS(z - player[0].pos[2]) > 15900)
	{
		// request that we spool him in
		cp->ai.l.dstate = LeadDrive_FakeMotion;
		return;
	}

	if (cp->ai.l.dstate == LeadDrive_FakeMotion)
	{
		// don't spool him in until everything is loaded
		if (spoolactive)
			return;

		tmpStart.vx = x;
		tmpStart.vz = z;
		tmpStart.vy = MapHeight(&tmpStart) - cp->ap.carCos->wheelDisp[0].vy;

		InitCarPhysics(cp, (LONGVECTOR4*)&tmpStart, cp->ai.l.targetDir);

		// start him up
		cp->ai.l.dstate = LeadDrive_NormalDrive;

		ResetTyreTracks(cp, GetPlayerId(cp));
	}

	if (ABS(cp->ai.l.panicCount) > 0)
		cp->ai.l.dstate = LeadDrive_Panic;

	if (cp->ai.l.dstate == LeadDrive_EmergencyBrake)
		cp->ai.l.dstate = LeadDrive_NormalDrive;

	if (cp->hd.speed < 10)
		++cp->ai.l.stuckCount;
	else
		cp->ai.l.stuckCount = 0;

	if (cp->ai.l.dstate == LeadDrive_Unstuck)
	{
		if (cp->ai.l.stuckCount > 20)
		{
			cp->ai.l.stuckCount = 0;
			cp->ai.l.recoverTime = 1;
			cp->ai.l.roadForward = -cp->ai.l.roadForward;
		}
	}
	else
	{
		if (cp->ai.l.stuckCount > 10)
		{
			cp->ai.l.stuckCount = 0;
			cp->ai.l.recoverTime = 0;
			cp->ai.l.dstate = LeadDrive_Unstuck;
		}
	}

	avel = FIXEDH(cp->st.n.angularVelocity[1]);
	end = DIFF_ANGLES(cp->ai.l.targetDir, cp->hd.direction);// (cp->hd.direction - cp->ai.l.targetDir) + 2048U & 0xfff) - 2048;

	switch (cp->ai.l.dstate)
	{
		case LeadDrive_Handbrake:
		{
			CheckCurrentRoad(cp);

			if (cp->hd.speed < 20)
				cp->ai.l.dstate = LeadDrive_NormalDrive;

			if (ABS(end) < LeadValues.hEnd)
			{
				if (ABS(avel) > 150)
					cp->ai.l.dstate = LeadDrive_DropPedals;
			}

			break;
		}
		case LeadDrive_DropPedals:
		{
			CheckCurrentRoad(cp);

			if (ABS(end) < LeadValues.dEnd)
			{
				if (ABS(avel) < 24)
				{
					cp->ai.l.dstate = LeadDrive_NormalDrive;
				}
				else
				{
					cp->ai.l.dstate = LeadDrive_CorrectOversteer;
				}
			}

			break;
		}
		case LeadDrive_CorrectOversteer:
		{
			CheckCurrentRoad(cp);

			if (ABS(avel) < 24)
				cp->ai.l.dstate = LeadDrive_NormalDrive;

			break;
		}
		case LeadDrive_NormalDrive:
		{
			volatile int dist;
		
			if (cp->ai.l.recoverTime > 40)
				--cp->ai.l.recoverTime;

			CheckCurrentRoad(cp);

			dx = (cp->ai.l.targetX - x) * RSIN(cp->hd.direction);
			dz = (cp->ai.l.targetZ - z) * RCOS(cp->hd.direction);

			dist = FIXEDH(dx + dz);

			if (cp->hd.speed > 100 || (cp->hd.speed > 30 && ABS(end) > 1024))
			{
				if (ABS(end) > LeadValues.hEnd)
				{
					if (cp->hd.speed > 100)
					{
						int hDist = LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul;

						if (dist < hDist)
							cp->ai.l.dstate = LeadDrive_NormalDrive;	// [A] was LeadDrive_OversteerBrake
						else
							cp->ai.l.dstate = LeadDrive_Handbrake;

						break;
					}
					else
					{
						int tDist = LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul;

						if (dist < tDist)
						{
							cp->ai.l.dstate = LeadDrive_Handbrake;
							break;
						}
					}
				}
			}

			if (ABS(end) > cp->hd.speed + LeadValues.tEnd)
			{
				int lDist;

				if (cp->hd.speed > 100)
					lDist = LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul;
				else
					lDist = LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul;

				if (dist < lDist && cp->ai.l.roadForward > 0)
					cp->ai.l.dstate = LeadDrive_Wheelspin;
				else
					cp->ai.l.dstate = LeadDrive_EmergencyBrake;
			}

			break;
		}
		case LeadDrive_Unstuck:
		{
			pos.vx = cp->hd.where.t[0];
			pos.vy = cp->hd.where.t[1];
			pos.vz = cp->hd.where.t[2];

			UpdateRoadPosition(cp, &pos, 5);

			cp->ai.l.recoverTime++;

			if (cp->ai.l.roadForward == 0)
			{
				cp->ai.l.dstate = LeadDrive_NormalDrive;
				cp->ai.l.stuckCount = 0;
			}

			break;
		}
		case LeadDrive_Panic:
		{
			CheckCurrentRoad(cp);

			if (cp->ai.l.panicCount == 0)
			{
				if (ABS(end) < 200)
					cp->ai.l.dstate = LeadDrive_CorrectOversteer;
			}

			break;
		}
		case LeadDrive_Wheelspin:
		{
			CheckCurrentRoad(cp);

			if (ABS(end) < cp->hd.speed + LeadValues.tEnd)
				cp->ai.l.dstate = LeadDrive_CorrectOversteer;

			break;
		}
	}
}

// [D] [T]
u_int LeadPadResponse(CAR_DATA* cp)
{
	u_int t0;

	volatile int deltaTh;
	volatile int avel;
	
	t0 = 0;

	deltaTh = DIFF_ANGLES(cp->ai.l.targetDir, cp->hd.direction); // ((cp->hd.direction - cp->ai.l.targetDir) + 2048U & 0xfff) - 2048;
	avel = FIXEDH(cp->st.n.angularVelocity[1]);

#if defined(COLLISION_DEBUG) && !defined(PSX)
	extern int gShowCollisionDebug;
	if (gShowCollisionDebug == 4)
	{
		extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
		extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

		CVECTOR yycv = { 250, 250, 0 };
		CVECTOR ggcv = { 0, 250, 0 };
		CVECTOR bbcv = { 0, 0, 250 };
		CVECTOR rrcv = { 250, 0, 0 };

		VECTOR _zero = { 0 };
		VECTOR _up = { 0, 1000, 0 };

		VECTOR pos = { cp->ai.l.targetX, cp->hd.where.t[1], cp->ai.l.targetZ };

		static char* LeadDebugStateNames[] = {
			"Handbrake",
			"Accelerate",
			"Correct oversteer",
			"Drive to target",
			"Unblock",
			"Panic",
			"Ovrstr + brk",
			"Stupidly go forward",
			"FakeMotion",
		};

		SetTextColour(120, 15, 15);
		
		char text[256];
		sprintf(text, "%s", LeadDebugStateNames[cp->ai.l.dstate]);
		PrintString(text, 20, 180);

		SetTextColour(128, 128, 64);
		
		sprintf(text, "dir: %d, fwd: %d, pos: %d, width: %d", cp->ai.l.targetDir, cp->ai.l.roadForward, cp->ai.l.roadPosition, cp->ai.l.width);
		PrintString(text, 20, 195);
		
		sprintf(text, "panic: %d, boring: %d, nextTurn: %d", cp->ai.l.panicCount, cp->ai.l.boringness, cp->ai.l.nextTurn);
		PrintString(text, 20, 210);

		sprintf(text, "currentRoad: %d", cp->ai.l.currentRoad);
		PrintString(text, 20, 230);
		
		Debug_AddLineOfs(_zero, _up, pos, yycv);
	}
#endif

	switch (cp->ai.l.dstate)
	{
		case LeadDrive_Handbrake:
		{
			int deltaAVel;
			
			// [A] check angular velocity when making this maneuver with handbrake
			deltaAVel = ABS(avel);
		
			t0 = (deltaAVel < 200 ? CAR_PAD_HANDBRAKE : 0) | ((deltaTh < 0) ? CAR_PAD_RIGHT : CAR_PAD_LEFT);
			break;
			case 1:
				t0 = CAR_PAD_ACCEL;
			break;
			case 2:
				t0 = CAR_PAD_ACCEL | ((avel < 0) ? CAR_PAD_RIGHT : CAR_PAD_LEFT);

			if (ABS(avel) > 40)
				t0 |= CAR_PAD_FASTSTEER;

			break;
		}
		case LeadDrive_NormalDrive:
		{
			volatile int dx, dz;
			volatile int deltaPos;
			volatile int maxDist;
			volatile int deltaVel;
			volatile int steerDelta;
			
			dx = -RCOS(cp->ai.l.targetDir) * (cp->hd.where.t[0] - cp->ai.l.targetX);
			dz =  RSIN(cp->ai.l.targetDir) * (cp->hd.where.t[2] - cp->ai.l.targetZ);

			deltaPos = FIXEDH(dx + dz);

			maxDist = pathParams[4];

			if (deltaPos > maxDist || (maxDist = -maxDist, deltaPos < maxDist))
				deltaPos = maxDist;

			deltaVel = FIXEDH(
                - RCOS(cp->ai.l.targetDir) * FIXEDH(cp->st.n.linearVelocity[0])
                + RSIN(cp->ai.l.targetDir) * FIXEDH(cp->st.n.linearVelocity[2]));

			steerDelta = FIXEDH(
                    pathParams[0] * deltaVel
                    + pathParams[1] * avel
                    + pathParams[2] * deltaPos
                    + pathParams[3] * deltaTh) - cp->wheel_angle;

			t0 = CAR_PAD_ACCEL;
		
			if (steerDelta > 32)
				t0 |= CAR_PAD_RIGHT;
			else if (steerDelta < -32)
				t0 |= CAR_PAD_LEFT;

			if (ABS(steerDelta) > 64)
				t0 |= CAR_PAD_FASTSTEER;
		
			if (steerDelta + 31U <= 62 && ABS(avel) <= 5)
			{
				if (t0 & CAR_PAD_ACCEL)
					t0 |= CAR_PAD_WHEELSPIN;
			}

			break;
		}
		case LeadDrive_Unstuck:
		{
			volatile int deltaPos;
			
			t0 = CAR_PAD_WHEELSPIN;

			deltaPos = DIFF_ANGLES(cp->hd.direction, cp->ai.l.roadPosition);// ((cp->ai.l.roadPosition - cp->hd.direction) + 2048U & 0xfff) - 2048;

			if (cp->ai.l.roadForward < 0)
				t0 = CAR_PAD_BRAKE;

			if (deltaPos * cp->ai.l.roadForward < 1)
				t0 |= CAR_PAD_LEFT;
			else
				t0 |= CAR_PAD_RIGHT;

			if (ABS(deltaPos) > 200 && ABS(deltaTh) < 1848)
			{
				t0 |= CAR_PAD_FASTSTEER;
			}

			break;
		}
		case LeadDrive_Panic:
		{
			volatile int deltaAVel;
			
			deltaAVel = ABS(avel);

			if (ABS(cp->ai.l.panicCount) < 2 || deltaAVel > 150)
			{
				if (cp->hd.speed <= 100)
					t0 |= CAR_PAD_ACCEL;
			}
			else
			{
				t0 = (cp->hd.speed > 100) ? CAR_PAD_HANDBRAKE : CAR_PAD_WHEELSPIN;
			}

			if (deltaAVel < 80)
				t0 |= CAR_PAD_FASTSTEER;

			if (cp->ai.l.panicCount == 0)
			{
				// already straight ahead?
				if (deltaTh == 0)
					break;

				// straighten up if needed
				if (deltaTh > 0)
				{
					if (deltaAVel < 150 || avel > 0)
						t0 |= CAR_PAD_LEFT;
				}
				else
				{
					if (deltaAVel < 150 || avel < 0)
						t0 |= CAR_PAD_RIGHT;
				}
			}
			else if (cp->ai.l.panicCount < 0)
			{
				// panick to the left?
				if (deltaAVel < 150 || avel > 0)
					t0 |= CAR_PAD_LEFT;
			}
			else
			{
				// panick to the right?
				if (deltaAVel < 150 || avel < 0)
					t0 |= CAR_PAD_RIGHT;
			}

			break;
		}
		case LeadDrive_EmergencyBrake:
		{
			t0 = (avel < 0) ? CAR_PAD_RIGHT : CAR_PAD_LEFT;
			//t0 |= ((deltaTh < 0) ? CAR_PAD_RIGHT : CAR_PAD_LEFT);
		
			if (cp->ai.l.roadForward < 0 && cp->hd.speed > 100)
				t0 |= CAR_PAD_BRAKE;
			else
				t0 |= CAR_PAD_ACCEL;

			break;
		}
		case LeadDrive_Wheelspin:
		{
			if (ABS(avel) > LeadValues.tAvelLimit)
			{
				if (ABS(deltaTh) > 1024)
					t0 = CAR_PAD_FASTSTEER | ((deltaTh < 0) ? CAR_PAD_RIGHT : CAR_PAD_LEFT);
			}

			t0 |= CAR_PAD_WHEELSPIN;
			break;
		}
		case LeadDrive_FakeMotion:
		{
			FakeMotion(cp);
			break;
		}
	}

	return t0;
}

// [D] [T]
// FakeMotion: when car is too far from the player it just moves, not drives
void FakeMotion(CAR_DATA* cp)
{
	DRIVER2_STRAIGHT* straight;
	DRIVER2_CURVE* curve;
	DRIVER2_JUNCTION* junction;
	int currentRoad;
	int nextJunction;
	int temp;
	
	currentRoad = cp->ai.l.currentRoad;

	if (IS_JUNCTION_SURFACE(currentRoad))
	{
		// straight away
		// select next exit and proceed
		nextJunction = currentRoad;
	}
	else if (IS_STRAIGHT_SURFACE(currentRoad))
	{
		int dx, dz;
		
		volatile int angle;
		volatile int c, s, d;
		volatile int toGo;
		straight = GET_STRAIGHT(currentRoad);

		dx = cp->hd.where.t[0] - straight->Midx;
		dz = cp->hd.where.t[2] - straight->Midz;

		angle = straight->angle & 0xfff;
		
		nextJunction = (straight->ConnectIdx[1]);

		if (nextJunction == -1)
			nextJunction = (straight->ConnectIdx[0]);

		if (cp->ai.l.direction == 0)
		{
			if (cp->ai.l.targetDir - angle + 1024U & 0x800)
				cp->ai.l.direction = -1;
			else
				cp->ai.l.direction = 1;
		}

		if (cp->ai.l.direction == -1)
		{
			angle ^= 2048;

			nextJunction = (straight->ConnectIdx[3]);
	
			if (nextJunction == -1)
				nextJunction = (straight->ConnectIdx[2]);
		}

		// WARNING: variables are flipped!
		c = RSIN(angle);
		s = RCOS(angle);

		d = FIXEDH(c * dx + s * dz);
		
		toGo = (straight->length / 2) - d;

		if (toGo > -1)
		{
			d += 120;

			cp->hd.where.t[0] = FIXEDH(c * d) + straight->Midx;
			cp->hd.where.t[2] = FIXEDH(s * d) + straight->Midz;
			return;
		}

		if (!IS_JUNCTION_SURFACE(nextJunction))
		{
			cp->ai.l.currentRoad = nextJunction;
			cp->ai.l.direction = 0;
			return;
		}
	}
	else if (IS_CURVED_SURFACE(currentRoad))
	{
		volatile int dx, dz;
		volatile int radius;
		volatile int angle;
		volatile int dir;

		curve = GET_CURVE(currentRoad);

		dx = cp->hd.where.t[0] - curve->Midx;
		dz = cp->hd.where.t[2] - curve->Midz;
		
		angle = ratan2(dx, dz);
		
		if (cp->ai.l.direction == 0)
		{
			if (angle - cp->ai.l.targetDir & 0x800U)
				cp->ai.l.direction = 1;
			else
				cp->ai.l.direction = -1;
		}

		radius = (curve->inside * 2 + ROAD_LANES_COUNT(curve)) * 512;

		// move car in desired direction
		if (cp->ai.l.direction == 1)
		{
			
			if (DIFF_ANGLES(angle, curve->end) >= 0) // ((curve->end - angle & 0xfff) + 2048 & 0xfff) - 2048 > -1) 
			{
				dir = angle + 0x13193 / radius;

				cp->ai.l.targetDir = (dir + 1024) & 0xfff;
				
				cp->hd.where.t[0] = FIXEDH(RSIN(dir)* radius) + curve->Midx;
				cp->hd.where.t[2] = FIXEDH(RCOS(dir) * radius) + curve->Midz;
				return;
			}

			nextJunction = curve->ConnectIdx[1];
			if (nextJunction == -1)
				nextJunction = curve->ConnectIdx[0];
		}
		else
		{
			if (DIFF_ANGLES(curve->start, angle) >= 0) //if (((angle - curve->start & 0xfff) + 2048 & 0xfff) - 2048 > -1)
			{
				dir = angle - 0x13193 / radius;

				cp->ai.l.targetDir = (dir - 1024) & 0xfff;
				
				cp->hd.where.t[0] = FIXEDH(RSIN(dir) * radius) + curve->Midx;
				cp->hd.where.t[2] = FIXEDH(RCOS(dir) * radius) + curve->Midz;

				return;
			}

			nextJunction = curve->ConnectIdx[3];
			if (nextJunction == -1)
				nextJunction = (curve->ConnectIdx[2]);
		}
		
		if(!IS_JUNCTION_SURFACE(nextJunction))
		{
			cp->ai.l.currentRoad = nextJunction;
			cp->ai.l.direction = 0;
			return;
		}
	}

	junction = GET_JUNCTION(nextJunction);
	cp->ai.l.lastRoad = cp->ai.l.currentRoad;

	SelectExit(cp, junction);

	temp = cp->ai.l.nextExit;

	cp->ai.l.targetDir = (temp << 10);
	cp->ai.l.currentRoad = junction->ExitIdx[temp];
	cp->ai.l.direction = 0;
}

// [D] [T]
void PosToIndex(int* normal, int* tangent, int intention, CAR_DATA* cp)
{
	volatile int t80;

	if (intention - 4U < 3)
	{ 
		*normal = DIFF_ANGLES(0, *normal); //(*normal + 2048U & 0xfff) - 2048;

		if (intention == 6 && ABS(*normal) < 240)
		{
			int dist;
			
			dist = FIXEDH(*tangent * RSIN(*normal));
				
			if (dist > 125)
			{
				*normal = 23;
				return;
			}

			if (dist > 50)
			{
				*normal = 22;
				return;
			}

			if (dist > -50)
			{
				*normal = 21;
				return;
			}

			if (dist < -124)
			{
				*normal = 19;
				return;
			}

			*normal = 20;
			return;
		}
	
		*normal *= 21;

		if (intention == 4)
			*normal /= 1536; // [A] (*normal / 6 + (*normal >> 0x1f) >> 8) - (*normal >> 0x1f);
		else if (intention == 5)
			*normal /= 2048;
		else
			*normal /= 1024;

		t80 = *normal;
	}
	else
	{
		if (intention > 1)
		{
			volatile int w, t;
			volatile int myspeed;
			volatile int temp;
			volatile int w80;
			
			myspeed = cp->hd.speed;
			w = LeadValues.tWidth;
			t80 = LeadValues.tWidthMul;
			
			if (myspeed > 100)
			{
				w = LeadValues.hWidth;
				t80 = LeadValues.hWidthMul;
			}
			
			w = w + myspeed * t80;
			
			if (myspeed > 100)
				w80 = LeadValues.hWidth80 + myspeed * LeadValues.hWidth80Mul;
			else
				w80 = LeadValues.tWidth80 + myspeed / LeadValues.tWidth80Mul;
			
			if (myspeed > 100)
				t = LeadValues.hDist + (myspeed - 100) * LeadValues.hDistMul;
			else
				t = LeadValues.tDist + myspeed * LeadValues.tDistMul;

			t80 = (t << 3) / 10;

			if (intention == 2)
				*normal = -*normal;

			if (w < *normal)
			{
				temp = *tangent;
				
				*tangent = (t + *normal) - w;
				*normal = t - temp;
			}
			else if (w80 < *normal)
			{
				temp = ((*normal - w80) * (t - t80)) / (w - w80) + t80;
				
				*normal = temp - *tangent;
				*tangent = temp;
			}
			else if (*normal > 0)
			{
				temp = (t80 * w80) / *normal;

				*normal = temp - *tangent;
				*tangent = temp;
			}
		}

		t80 = *normal / 100;
	}

	*normal = t80 + 21;
}

// [D] [T] - seems to be working as expected
void BlockToMap(MAP_DATA* data)
{
	volatile int carLength, carWidth;
	volatile int offx;
	MAP_DATA newdata;

	static int left = 0;
	static int right = 0;
	static int rdist = 0;
	static int ldist = 0;
	volatile int someVar = 0;

	volatile int overlap = 0;

	DRIVER2_CURVE* curve;

	volatile int x, y;

	int* ndist;
	int* fdist;
	int* nearest;
	int* furthest;

	volatile int corners[4][3];

	volatile int dx, dy, dz;
	volatile int angle;
	volatile int v;
	volatile int c, s;
	volatile int tangent, normal;

	tangent = 0;
	normal = 0;
	dx = dy = dz = 0;
	offx = 0;

	CAR_COSMETICS* pCarCos = data->cp->ap.carCos;

	carLength = pCarCos->colBox.vz;
	carWidth = pCarCos->colBox.vx;

	switch (data->intention)
	{
		case 0:
		case 2:
		case 3:
		{
			dx = data->pos->vx - data->base->vx;
			dy = data->base->vy - data->pos->vy;
			dz = data->pos->vz - data->base->vz;

			if (dy < 1)
				v = pCarCos->colBox.vy;
			else
				v = data->size->vy;

			if (dy > v)
				return;

			normal = FIXEDH(dx * road_c - dz * road_s);
			tangent = FIXEDH(dx * road_s + dz * road_c);

			someVar = FIXEDH(ABS(data->size->vx * road_s) + ABS(data->size->vz * road_c));

			if (data->intention == 0 || data->cp->ai.l.dstate == LeadDrive_NormalDrive)
			{
				v = (data->cp->hd.speed + 100) * 10;

				if (v > ABS(tangent) && v > ABS(normal))
				{
					newdata.base = data->base;
					newdata.pos = data->pos;
					newdata.vel = data->vel;
					newdata.size = data->size;
					newdata.intention = 6;
					newdata.map = data->local;
					newdata.local = NULL;
					newdata.cp = data->cp;

					BlockToMap(&newdata);
				}
			}

			if (tangent + someVar < 0)
				return;

			if (data->vel != NULL)
			{
				v = (data->vel->vx * road_s) + (data->vel->vz * road_c) + 2048;
				v = FIXEDH(v) - (v >> 31) >> 1;

				tangent += v;
				someVar += ABS(v);

				if (v < 0 && data->intention == 0)
					tangent /= 2;
			}

			rdist = (tangent - someVar) - carLength;

			if (rdist < 0)
				rdist = 0;

			offx = FIXEDH(ABS(data->size->vx * road_c) + ABS(data->size->vz * road_s)) + carWidth * 2;

			left = normal - offx;
			right = normal + offx;

			if (data->vel != NULL)
			{
				v = FIXEDH(data->vel->vx * road_c + data->vel->vz * road_s);

				if (v < 1)
				{
					left -= v;
				}
				else
				{
					right += v;
				}
			}

			ldist = rdist;
			break;
		}
		case 1:
		{
			curve = GET_CURVE(data->cp->ai.l.currentRoad);

			dx = data->pos->vx - curve->Midx;
			dy = data->base->vy - data->pos->vy;
			dz = data->pos->vz - curve->Midz;

			if (dy < 1)
				v = pCarCos->colBox.vy;
			else
				v = data->size->vy;

			if (dy > v)
				return;

			tangent = ratan2(dx, dz);

			s = RSIN(tangent + 1024);
			c = RCOS(tangent + 1024);

			tangent = DIFF_ANGLES(data->cp->ai.l.base_Angle, tangent) * //(((tangent - data->cp->ai.l.base_Angle) + 2048U & 0xfff) - 2048) *
                data->cp->ai.l.base_Dir * ((curve->inside * 45056) / 28672);

			someVar = FIXEDH(ABS(data->size->vx * s) + ABS(data->size->vz * c));

			if (tangent + someVar < 0)
				return;

			if (data->vel != NULL)
			{
				v = (data->vel->vx * s) + (data->vel->vz * c) + 2048;
				v = FIXEDH(v) - (v >> 31) >> 1;

				tangent += v;
				someVar += ABS(v);

				if (v < 0)
					tangent /= 2;

			}

			rdist = (tangent - someVar) - carLength;

			if (rdist < 0)
				rdist = 0;

			normal = (data->cp->ai.l.base_Normal - hypot(dx, dz)) * data->cp->ai.l.base_Dir;
			v = (data->cp->hd.speed + 100) * 10;

			if (v > rdist && v > ABS(normal))
			{
				newdata.base = data->base;
				newdata.pos = data->pos;
				newdata.vel = data->vel;
				newdata.size = data->size;
				newdata.intention = 6;
				newdata.map = data->local;
				newdata.local = NULL;
				newdata.cp = data->cp;

				BlockToMap(&newdata);
			}

			offx = FIXEDH(ABS(data->size->vx * c) + ABS(data->size->vy * s)) + carWidth;

			left = normal - offx;
			right = normal + offx;

			if (data->vel != NULL)
			{
				v = FIXEDH(data->vel->vx * c + data->vel->vz * s);

				if (v < 1)
					left -= v;
				else
					right += v;
			}

			ldist = rdist;
			break;
		}
		case 4:
		case 5:
		case 6:
		{
			dx = data->pos->vx - data->base->vx;
			dy = data->base->vy - data->pos->vy;
			dz = data->pos->vz - data->base->vz;

			if (dy < 1)
				v = pCarCos->colBox.vy;
			else
				v = data->size->vy;

			if (dy > v)
				return;

			angle = DIFF_ANGLES(0, ratan2(dx, dz)); //(ratan2(dx, dz) + 2048U & 0xfff) - 2048;

			s = RSIN(angle);
			c = RCOS(angle);

			someVar = FIXEDH(ABS(data->size->vx * s) + ABS(data->size->vz * c));

			tangent = (hypot(dx, dz) - someVar) - carLength;

			if (tangent < 2000 || data->intention == 6)
			{
				volatile int quad1, quad2;
				
				corners[0][0] = dx + data->size->vx;
				corners[0][1] = dz + data->size->vz;
				corners[2][0] = dx - data->size->vx;
				corners[1][1] = dz - data->size->vz;

				corners[1][0] = corners[0][0];
				corners[2][1] = corners[0][1];
				corners[3][0] = corners[2][0];
				corners[3][1] = corners[1][1];

				corners[0][2] = ratan2(corners[0][0], corners[0][1]);
				corners[1][2] = ratan2(corners[1][0], corners[1][1]);
				corners[2][2] = ratan2(corners[2][0], corners[2][1]);
				corners[3][2] = ratan2(corners[3][0], corners[3][1]);

				overlap = 0;

				left = 0;
				right = 0;

				quad1 = corners[0][2] + 2048 >> 10;

				for (int i = 1; i < 4; i++)
				{
					y = corners[i][2];

					if (DIFF_ANGLES(y, corners[left][2]) > 0) // ((int)(((corners[left][2] - y) + 2048U & 0xfff) - 2048) > 0)
						left = i;

					if (DIFF_ANGLES(corners[right][2], y) > 0) // ((int)(((y - corners[right][2]) + 2048U & 0xfff) - 2048) > 0)
						right = i;

					quad2 = y + 2048 >> 10;

					if ((quad1 != quad2) && (quad1 + (quad1 - (corners[0][2] + 2048 >> 0x1f) >> 1) * -2 == quad2 + (quad2 - (y + 2048 >> 0x1f) >> 1) * -2))
						overlap = 1;
				}

				if (overlap)
				{
					//int temp;
					//temp = angle - data->cp->hd.direction;

					left = DIFF_ANGLES(data->cp->hd.direction - 512, angle); // temp - 512;
					right = DIFF_ANGLES(data->cp->hd.direction + 512, angle); // temp + 512;

					rdist = 0;
				}
				else if (left + right == 3)
				{
					int temp;
					tangent = -1;

					for (int i = 0; i < 4; i++)
					{
						if (i != left && i != right)
						{
							temp = hypot(corners[i][0], corners[i][1]);

							if (tangent < temp || tangent == -1)
								tangent = temp;
						}
					}

					left = DIFF_ANGLES(data->cp->hd.direction, corners[left][2]); // corners[left][2] - data->cp->hd.direction;
					right = DIFF_ANGLES(data->cp->hd.direction, corners[right][2]); // corners[right][2] - data->cp->hd.direction;

					rdist = tangent;
				}
				else
				{
					int vx, vz;
					int theta;
					
					dx = corners[left][1] - corners[right][1];
					dy = corners[left][0] - corners[right][0];

					theta = (ratan2(dy, dx) + 3072 & 0xfff) - 2048;	// there should be DIFF_ANGLES but idk

					vx = RSIN(theta) * corners[left][0];
					vz = RCOS(theta) * corners[left][1];

					left = DIFF_ANGLES(data->cp->hd.direction, corners[left][2]); // corners[left][2] - data->cp->hd.direction;
					right = DIFF_ANGLES(data->cp->hd.direction, corners[right][2]); // corners[right][2] - data->cp->hd.direction;

					rdist = ABS(FIXEDH(vx + vz));
				}

				// left = (left + 2048U & 0xfff) - 2048;
				// right = (right + 2048U & 0xfff) - 2048;
			}
			else
			{
				normal = DIFF_ANGLES(data->cp->hd.direction, angle); // ((angle - data->cp->hd.direction) + 2048 & 0xfff) - 2048;

				offx = ratan2(FIXEDH(ABS(data->size->vx * c) + ABS(data->size->vz * s)) + carWidth, tangent);

				left = normal - offx;
				right = normal + offx;

				rdist = tangent;
			}

			ldist = rdist;
			break;
		}
		default:
		{
			printError("\nunknwn intention in leadai.c LOCKUP!!\n");
		}
	}
	
	switch (data->intention)
	{
		case 2:
		case 3:
			if (data->intention == 2)
			{
				nearest = &left;
				furthest = &right;
				ndist = &ldist;
				fdist = &rdist;
			}
			else
			{
				nearest = &right;
				furthest = &left;
				ndist = &rdist;
				fdist = &ldist;
			}

			x = LeadValues.hWidth + data->cp->hd.speed * LeadValues.hWidthMul;

			if (x < ldist && x < rdist)
			{
				int tdist;
				int temp;
				
				*ndist += carLength * 2;
				*fdist = ABS(*fdist + carLength * -2);

				left -= carWidth;
				right -= carWidth;

				temp = *nearest;
				tdist = *ndist + someVar * 2;

				PosToIndex(&temp, &tdist, data->intention, data->cp);
				PosToIndex(nearest, ndist, data->intention, data->cp);
				PosToIndex(furthest, fdist, data->intention, data->cp);

				*nearest = temp;
				break;
			}
		case 0:
		case 1:
			PosToIndex(&left, &ldist, data->intention, data->cp);
			PosToIndex(&right, &rdist, data->intention, data->cp);
			break;
		case 4:
		{
			int locall = 0;
			int localld = 0;
			int localr = 0;
			int localrd = 0;
			
			locall = left;
			localr = right;
			localld = ldist;
			localrd = rdist;

			PosToIndex(&locall, &localld, 6, data->cp);
			PosToIndex(&localr, &localrd, 6, data->cp);

			if (localr < locall)
			{
				for (int i = locall; i <= 40; i++)
				{
					if (i <= 40 && localld < data->local[i])
						data->local[i] = localld;
				}

				left = -2048;
				PosToIndex(&locall, &localld, 6, data->cp);
			}

			for (int i = locall; i <= localr; i++)
			{
				if (i <= 40 && localld < data->local[i])
					data->local[i] = localld;
			}
			/*
			*
			* FALLTHROUGH
			*
			*/
		}
		case 5:
		case 6:
		{
			PosToIndex(&left, &ldist, data->intention, data->cp);
			PosToIndex(&right, &rdist, data->intention, data->cp);

			if (right < left)
			{
				for (int i = left; i <= 40; i++)
				{
					if ((i >= 0 && i <= 40) && ldist < data->map[i])
						data->map[i] = ldist;
				}

				left = -2048;
				PosToIndex(&left, &ldist, data->intention, data->cp);
			}

			break;
		}
		default:
		{
			printError("\nunknwn intention in leadai.c LOCKUP!!\n");
		}
	}

	tangent = ldist;

	int dtan = 0;

	if (left < right)
		dtan = (rdist - ldist) / (right - left);

	for (int i = left; i <= right; i++)
	{
		if ((i >= 0 && i <= 40) && tangent < data->map[i])
			data->map[i] = tangent;

		tangent += dtan;
	}
}

// [D] [T]
int IsOnMap(int x, int z, VECTOR* basePos, int intention, CAR_DATA* cp)
{
	DRIVER2_CURVE* curve;
	int dx, dz;
	int normal;
	int tangent;

	dx = ABS(x - basePos->vx);
	dz = ABS(z - basePos->vz);

	if (dx < 3000 && dz < 3000)
		return 1;

	switch (intention)
	{
		case 0:
		case 2:
		case 3:
		{
			tangent = FIXEDH(dx * road_s + dz * road_c);
			normal = FIXEDH(dx * road_c - dz * road_s);

			PosToIndex(&normal, &tangent, intention, cp);
			break;
		}
		case 1:
		{
			curve = GET_CURVE(cp->ai.l.currentRoad);

			dx = x - curve->Midx;
			dz = z - curve->Midz;

			tangent = DIFF_ANGLES(cp->ai.l.base_Angle, ratan2(dx, dz)) // (((ratan2(dx, dz) - cp->ai.l.base_Angle) + 2048U & 0xfff) - 2048) * 
				* cp->ai.l.base_Dir * ((curve->inside * 45056) / 28672);

			normal = (cp->ai.l.base_Normal - hypot(dx, dz)) * cp->ai.l.base_Dir;

			PosToIndex(&normal, &tangent, intention, cp);
			break;
		}
		case 4:
		case 5:
		{
			tangent = hypot(dx, dz);
			normal = DIFF_ANGLES(cp->hd.direction, ratan2(dx, dz)); // ((ratan2(dx, dz) - cp->hd.direction) + 2048U & 0xfff) - 2048;

			PosToIndex(&normal, &tangent, intention, cp);

			if (tangent > 7000)
				return 0;

			if (normal > -1 && normal < 42)
				return 1;
		}
		default:
			return 0;
	}

	if ((tangent + 2048) > 22528)
		return 0;

	if (normal < -4)
		return 0;

	if (normal <= 45)
		return 1;

	return 0;
}

int roadAhead[42]; // offset 0x000ecde8
int localMap[42]; // offset 0x000ecd40

// [D] [A] overlapping stack variables - might be incorrect (i've tried to resolve them so far)
void UpdateRoadPosition(CAR_DATA* cp, VECTOR* basePos, int intention)
{
	MAP_DATA data;
	VECTOR offset = { 0 };
	VECTOR pos = { 0 };
	VECTOR vel = { 0 };
	VECTOR size = { 0 };
	CELL_ITERATOR ci;
	COLLISION_PACKET* collide;
	_CAR_DATA* lcp;

	PACKED_CELL_OBJECT* ppco;
	CELL_OBJECT tempCO;
	CAR_COSMETICS* car_cos;

	MODEL* model;
	int i, j;

	volatile int laneAvoid;
	volatile int newTarget = 21;
	volatile int sindex = 0;
	
	volatile int cell_x, cell_z;
	volatile int initial_cell_x, initial_cell_z;
	volatile int x1, z1;

	for(i = 0; i < 41; i++)
		roadAhead[i] = 20480;

	for (i = 0; i < 41; i++)
		localMap[i] = (cp->hd.speed + 100) * 10;
	
	laneAvoid = -1;
	
	road_s = RSIN(cp->ai.l.targetDir);
	road_c = RCOS(cp->ai.l.targetDir);

	ClearCopUsage();
	
	initial_cell_x = ((basePos->vx + units_across_halved - 1024) / MAP_CELL_SIZE) - 5;
	initial_cell_z = ((basePos->vz + units_down_halved - 1024) / MAP_CELL_SIZE) - 5;

	//
	// check all nearby collision cells
	cell_x = initial_cell_x;

	for (x1 = 0; x1 < 11; x1++, cell_x++)
	{
		cell_z = initial_cell_z;

		for (z1 = 0; z1 < 11; z1++, cell_z++)
		{
			int cbr;
			int cbrX, cbrZ;

			if (!IsOnMap(
				cell_x * MAP_CELL_SIZE - units_across_halved + MAP_REGION_SIZE * MAP_REGION_SIZE,
				cell_z * MAP_CELL_SIZE - units_down_halved + MAP_REGION_SIZE * MAP_REGION_SIZE,
				basePos, intention, cp))
				continue;

			cbrX = cell_x / MAP_REGION_SIZE;
			cbrZ = cell_z / MAP_REGION_SIZE;

			cbr = (cbrX & 1) + (cbrZ & 1) * 2;

			if (RoadMapRegions[cbr] != cbrX + cbrZ * regions_across)
				continue;

			ppco = GetFirstPackedCop(cell_x, cell_z, &ci, 1);

			while (ppco)
			{
				int type = (ppco->value >> 6) | ((ppco->pos.vy & 1) << 10);
				model = modelpointers[type];

				if (/*model->num_vertices - 3 < 300 &&
					model->num_point_normals < 300 &&
					model->num_polys < 300 &&*/
					(uint)model->collision_block > 0 &&
					(model->flags2 & MODEL_FLAG_SMASHABLE) == 0)
				{
					int num_cb;

					QuickUnpackCellObject(ppco, &ci.nearCell, &tempCO);
					
					num_cb = *(int*)model->collision_block;
					collide = (COLLISION_PACKET*)((int*)model->collision_block + 1);

					while (num_cb > 0)
					{
						int yang;
						int theta;
						int xsize, zsize;
						
						yang = -tempCO.yang & 0x3f;

						if (collide->type == 0)
						{
							int cs, sn;

							theta = (tempCO.yang + collide->yang) * 64;

							xsize = collide->xsize / 2;
							zsize = collide->zsize / 2;

							cs = RCOS(theta);
							sn = RSIN(theta);

							size.vx = FIXEDH(ABS(zsize * sn) + ABS(xsize * cs));
							size.vy = collide->ysize;
							size.vz = FIXEDH(ABS(zsize * cs) - ABS(xsize * sn));
						}
						else
						{
							theta = 0;
							xsize = 1;
							zsize = 1;
							
							printError("\nERROR! unknown collision box type in leadai.c\n");
						}

						offset.vx = FIXEDH(collide->xpos * matrixtable[yang].m[0][0] + collide->zpos * matrixtable[yang].m[2][0]) + tempCO.pos.vx;
						offset.vz = FIXEDH(collide->xpos * matrixtable[yang].m[0][2] + collide->zpos * matrixtable[yang].m[2][2]) + tempCO.pos.vz;
						offset.vy = -tempCO.pos.vy + collide->ypos;

#if defined(_DEBUG) || defined(DEBUG_OPTIONS) && !defined(PSX)
						extern int gShowCollisionDebug;
						if (gShowCollisionDebug == 4)
						{
							CDATA2D cd[1];

							cd[0].x.vx = offset.vx;// (tempCO.pos.vx + xxd);
							cd[0].x.vz = offset.vz;// (tempCO.pos.vz + zzd);
							cd[0].x.vy = cp->hd.where.t[1];

							cd[0].theta = theta; // (pCellObject->yang + collide->yang) * 64 & 0xfff;
							cd[0].length[0] = collide->zsize / 2;
							cd[0].length[1] = collide->xsize / 2;

							// calc axes of box
							int dtheta = cd[0].theta;

							cd[0].axis[0].vx = RSIN(dtheta);
							cd[0].axis[0].vz = RCOS(dtheta);

							cd[0].axis[1].vz = -RSIN(dtheta);
							cd[0].axis[1].vx = RCOS(dtheta);

							extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
							extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

							CVECTOR ggcv = { 0, 250, 0 };
							CVECTOR rrcv = { 250, 0, 0 };
							CVECTOR yycv = { 250, 250, 0 };
							CVECTOR bbcv = { 0, 0, 250 };

							// show both box axes
							{
								VECTOR _zero = { 0 };
								VECTOR b1p = cd[0].x;

								// show position to position
								//Debug_AddLine(b1p1, b2p1, yycv);

								VECTOR b1ax[2] = { {0} , {0} };
								b1ax[0].vx = FIXEDH(cd[0].axis[0].vx * cd[0].length[0]);
								b1ax[0].vz = FIXEDH(cd[0].axis[0].vz * cd[0].length[0]);
								b1ax[1].vx = FIXEDH(cd[0].axis[1].vx * cd[0].length[1]);
								b1ax[1].vz = FIXEDH(cd[0].axis[1].vz * cd[0].length[1]);

								// show axis of body 1
								Debug_AddLineOfs(_zero, b1ax[0], b1p, rrcv);
								Debug_AddLineOfs(_zero, b1ax[1], b1p, yycv);

								// display 2D box 1
								{
									int h = b1ax[0].vy;
									VECTOR box_points[4] = {
										{b1ax[0].vx - b1ax[1].vx, h, b1ax[0].vz - b1ax[1].vz, 0},	// front left
										{b1ax[0].vx + b1ax[1].vx, h, b1ax[0].vz + b1ax[1].vz, 0},	// front right

										{-b1ax[0].vx + b1ax[1].vx, h, -b1ax[0].vz + b1ax[1].vz, 0},	// back right
										{-b1ax[0].vx - b1ax[1].vx, h, -b1ax[0].vz - b1ax[1].vz, 0}	// back left
									};

									Debug_AddLineOfs(box_points[0], box_points[1], b1p, bbcv);
									Debug_AddLineOfs(box_points[1], box_points[2], b1p, bbcv);
									Debug_AddLineOfs(box_points[2], box_points[3], b1p, bbcv);
									Debug_AddLineOfs(box_points[3], box_points[0], b1p, bbcv);
								}
							}
						}
#endif

						vel.vx = 0;
						vel.vz = 0;
						data.vel = NULL;
						data.pos = &offset;
						data.size = &size;
						data.map = roadAhead;
						data.local = localMap;

						data.cp = cp;
						data.base = basePos;
						data.intention = intention;

						BlockToMap(&data);

						num_cb--;
						collide++;
					}
				}
				ppco = GetNextPackedCop(&ci);
			}
		}
	}

	//
	// check nearby cars
	//
	lcp = &car_data[MAX_CARS - 1];

	while (lcp >= car_data)
	{
		if (lcp != cp && lcp->controlType != CONTROL_TYPE_NONE)
		{
			int lbody;
			int wbody;
		
			car_cos = lcp->ap.carCos;

			wbody = car_cos->colBox.vx / 2;
			lbody = car_cos->colBox.vz / 2;

			size.vx = FIXEDH(ABS(lcp->hd.where.m[2][0] * lbody) + ABS(lcp->hd.where.m[0][0] * wbody)) + car_cos->colBox.vy;
			size.vz = FIXEDH(ABS(lcp->hd.where.m[2][2] * lbody) + ABS(lcp->hd.where.m[2][0] * wbody)) + car_cos->colBox.vy;
			size.vy = car_cos->colBox.vy;

			pos.vx = lcp->hd.where.t[0];
			pos.vy = lcp->hd.where.t[1];
			pos.vz = lcp->hd.where.t[2];

			vel.vx = cp->st.n.linearVelocity[0] / 1024;
			vel.vz = cp->st.n.linearVelocity[2] / 1024;

			data.vel = &vel;
			data.pos = &pos;
			data.size = &size;
			data.map = roadAhead;
			data.local = localMap;
			data.cp = cp;
			data.base = basePos;
			data.intention = intention;

			BlockToMap(&data);
		}

		lcp--;
	}

	// update panic
	if (cp->ai.l.dstate != LeadDrive_Unstuck)
	{
		int left, right;
		int spd;
		spd = (cp->hd.speed + 100) * 8;

		if (localMap[20] < spd ||
			localMap[21] < spd ||
			localMap[22] < spd)
		{
			for (i = 1; i < 21; i++)
			{
				spd = (cp->hd.speed + 100) * 24;

				left = localMap[20 - i] + localMap[21 - i] + localMap[22 - i];
				right = localMap[20 + i] + localMap[21 + i] + localMap[22 + i];

				if (left < right && spd < right * 2)
				{
					if (i > 13)
						cp->ai.l.panicCount = 2;
					else
						cp->ai.l.panicCount = 1;

					return;
				}

				if (left > right && spd < left * 2)
					break;

				if (i == 20)
				{
					if (left > right)
						cp->ai.l.panicCount = -2;
					else
						cp->ai.l.panicCount = 2;
				}
			}

			if (i > 13)
				cp->ai.l.panicCount = -2;
			else
				cp->ai.l.panicCount = -1;

			return;
		}
	}

	cp->ai.l.panicCount = 0;

	if (intention < 2)
	{
		int smallest;
	
		smallest = roadAhead[24];
		for (i = 24; i < 41; i++)
		{
			if (roadAhead[i] < smallest)
				smallest = roadAhead[i];

			if (smallest < (cp->hd.speed + 100) * SquareRoot0(i - 21))
				roadAhead[i] = 0;
		}

		smallest = roadAhead[18];
		for (i = 18; i >= 0; i--)
		{
			if (roadAhead[i] < smallest)
				smallest = roadAhead[i];

			if (smallest < (cp->hd.speed + 100) * SquareRoot0(21 - i))
				roadAhead[i] = 0;
		}
	}

	if (intention - 2 < 2)
	{
		int count;
		int tmpMap[41];

		for (i = 0; i < 41; i++)
			tmpMap[i] = roadAhead[i];

		for (i = 0; i < 41; i++)
		{
			count = 0;
			roadAhead[i] = 0;

			for (j = i - 3; j < i + 4; j++)
			{
				if (j < 41)
					roadAhead[i] += tmpMap[j];

				count++;
			}

			roadAhead[i] /= count;
		}
	}

	if (intention == 4)
	{
		int left, right;

		left = 42 + 21;
		right = -21;

		for (i = 0; i < 41; i++)
		{
			if (i - 21 < 0)
				roadAhead[i] = (roadAhead[i] * 21) / left;
			else
				roadAhead[i] = (roadAhead[i] * 21) / right;

			left -= 2;
			right += 2;
		}
	}

	// update boringness
	if (intention < 2 && cp->ai.l.nextTurn < 10)
	{
		int width = cp->ai.l.width;
		int bounds = ABS(cp->ai.l.roadPosition - (width - cp->ai.l.d));

		if (cp->ai.l.boringness < 31)
		{
			if (bounds < width / 3)
			{
				if (cp->ai.l.boringness < 31)
					cp->ai.l.boringness++;
			}
		}
		else
		{
			int left, right;
			int centre;

			if (bounds < width / 3)
			{
				cp->ai.l.avoid = cp->ai.l.width - cp->ai.l.d;
				cp->ai.l.boringness++;
			}

			laneAvoid = (cp->ai.l.avoid + cp->ai.l.d - cp->ai.l.width) / 100 + 21;

			left = laneAvoid * 100;
			right = laneAvoid * -100;

			for (i = 0; i < 41; i++)
			{
				if (laneAvoid - i > -1)
					centre = left;
				else
					centre = right;

				if (centre < cp->ai.l.width / 3)
					roadAhead[i] -= cp->ai.l.boringness * 100;

				right += 100;
				left -= 100;
			}

			if (ABS(cp->ai.l.avoid - width - cp->ai.l.d) > width / 3)
			{
				cp->ai.l.boringness = 0;
			}
		}
	}
	else
	{
		cp->ai.l.boringness = 0;
	}

	// turning intention
	if (intention - 4U > 1)
	{
		int penalty;
		int centre;
		int left, right;
		int width;

		width = cp->ai.l.width;
		centre = cp->ai.l.d;

		i = 0;

		left = centre - width;
		right = width + centre;

		PosToIndex(&left, &i, intention, cp);
		PosToIndex(&right, &i, intention, cp);
		PosToIndex(&centre, &i, intention, cp);

		if (left < centre && centre < right)
		{
			if ((cp->ai.l.nextTurn == 15 || cp->ai.l.nextTurn == 17) && intention - 2 > 1)
			{
				cp->ai.l.nextTurn -= 16;

				for (i = left; i <= right; i++)
				{
					if (cp->ai.l.nextTurn * (i - centre) > 0)
						penalty = -2000;
					else
						penalty = 2000;

					if (i < 41)
					{
						if (roadAhead[i] > 0)
							roadAhead[i] += penalty;
					}
				}
			}

			penalty = 0;
			while ((u_int)left < 41)
			{
				roadAhead[left] -= penalty;

				if (roadAhead[left] < 0)
					roadAhead[left] = 0;

				left--;
				penalty += 500;
			}

			penalty = 0;
			while ((u_int)right < 41)
			{
				roadAhead[right] -= penalty;

				if (roadAhead[right] < 0)
					roadAhead[right] = 0;

				right++;
				penalty += 500;
			}
		}
	}

	if (intention - 2 < 3)
	{
	LAB_LEAD__000ead84:
		int biggest;
		int step;

		newTarget = 21;

		biggest = roadAhead[21];

		step = 0;

		i = 21;
		do
		{
			if (roadAhead[i] > biggest)
			{
				biggest = roadAhead[i];
				newTarget = i;
			}

			if (step < 0)
				step = -step;

			step++;

			if ((step & 1) == 0)
				step = -step;

			i += step;
		} while (i < 41);

		if (intention - 2 < 2)
		{
			int dist;

			if (cp->hd.speed <= 100)
				dist = LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul;
			else
				dist = LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul;

			if (dist > biggest)
			{
				if (cp->ai.l.roadForward > -1)
					cp->ai.l.roadForward = -1;
				else
					cp->ai.l.roadForward--;

				if (intention == 3)
					cp->ai.l.roadPosition = -20000;
				else
					cp->ai.l.roadPosition = 20000;

				if (cp->ai.l.roadForward > -21)
					return;

				SelectExit(cp, &Driver2JunctionsPtr[cp->ai.l.nextJunction - 8192]);

				return;
			}
		}
	}
	else
	{
		int biggest;
		int bound;
		int lim;

		newTarget = cp->ai.l.lastTarget;
		bound = ABS((newTarget - laneAvoid) * 100);

		lim = ((bound + 100) / 50) * 1024;

		if (cp->ai.l.boringness < 31 || bound < cp->ai.l.width / 3 ||
			lim >= roadAhead[MAX(0, MIN(40, newTarget - 1))] &&
			lim >= roadAhead[MAX(0, MIN(40, newTarget))] &&
			lim >= roadAhead[MAX(0, MIN(40, newTarget + 1))])
		{
			lim = ((cp->ai.l.boringness + 100) / 50) * 1024;

			if (lim >= roadAhead[MAX(0, MIN(40, newTarget - 1))] &&
				lim >= roadAhead[MAX(0, MIN(40, newTarget))] &&
				lim >= roadAhead[MAX(0, MIN(40, newTarget + 1))])
			{
				goto LAB_LEAD__000ead84;
			}
		}

		biggest = roadAhead[newTarget];
		for (i = newTarget - 2; i < newTarget + 2; i++)
		{
			if (i < 41 && roadAhead[i] > biggest)
			{
				biggest = roadAhead[i];
				newTarget = i;
			}
		}
	}

	cp->ai.l.lastTarget = newTarget;

	if (intention < 2 || intention == 4)
	{
		int dir;
		cp->ai.l.roadForward = 5120;

		if (newTarget > 21)
			dir = -1;
		else
			dir = 1;

		for (i = newTarget; i != 21; i += dir)
		{
			if (cp->ai.l.roadForward > roadAhead[i])
				cp->ai.l.roadForward = roadAhead[i];
		}
	}
	else
	{
		if (intention == 5)
		{
			if (cp->ai.l.recoverTime == 0 || cp->ai.l.recoverTime > 20)
			{
				int small;
				small = roadAhead[19];

				for (i = 0; i < 4; i++)
				{
					if (roadAhead[20 + i] < small)
						small = roadAhead[20 + i];
				}

				if (small < roadAhead[38])
					cp->ai.l.roadForward = -1;
				else
					cp->ai.l.roadForward = 1;

				cp->ai.l.recoverTime = 0;
			}

			if (roadAhead[21] > 1500 &&
				roadAhead[22] > 1500 &&
				roadAhead[20] > 1500 &&
				cp->hd.speed > 40)
			{
				cp->ai.l.roadForward = 0;
			}
		}
		else
		{
			cp->ai.l.roadForward = 0;
		}
	}

	sindex = newTarget - 21;

	D_CHECK_ERROR(intention == 6, "Unknw intention in leadai.c");

	if (intention - 4U < 2)
	{
		if (intention == 4)
			sindex *= 1536;
		else
			sindex *= 2048;

		// This is something DIFF_ANGLES but rather different...
		sindex = ((sindex / 21 + 2048U & 0xfff) + cp->hd.direction & 0xfff) - 2048;
	}
	else
	{
		if (intention < 2)
		{
			sindex = (sindex * 200 + cp->ai.l.width) - cp->ai.l.d;
		}
		else
		{
			if (intention - 2 > 1)
				return;

			sindex = sindex * 100 + cp->ai.l.width;
		}
	}

	cp->ai.l.roadPosition = sindex;
}

// [D] [T]
void CheckCurrentRoad(CAR_DATA* cp)
{
	volatile int heading = 0; // offset 0x1c
	int nextJunction = 0; // offset 0x50
	VECTOR basePosition = {0}; // offset 0x60

	volatile int checkNext = -1;
	volatile int currentRoad = -1;

	DRIVER2_STRAIGHT* straight;
	DRIVER2_JUNCTION* junction;
	DRIVER2_CURVE* curve;

	checkNext = 0;

	// check if on grass
	if ((cp->hd.wheel[1].surface & 7) == 3 || (cp->hd.wheel[3].surface & 7) == 3)
		currentRoad = cp->ai.l.currentRoad;
	else
		currentRoad = GetSurfaceIndex((VECTOR*)cp->hd.where.t);

	if (IS_STRAIGHT_SURFACE(currentRoad) || IS_CURVED_SURFACE(currentRoad) || IS_JUNCTION_SURFACE(currentRoad))
	{
		cp->ai.l.offRoad = 0;

		if (currentRoad != cp->ai.l.lastRoad && 
			currentRoad != cp->ai.l.currentRoad)
		{
			cp->ai.l.direction = 0;
		}
	}
	else
	{
		currentRoad = cp->ai.l.lastRoad;
		cp->ai.l.direction = cp->ai.l.lastDirection;
	}

	if (IS_JUNCTION_SURFACE(currentRoad))
	{
		checkNext = 1;
		nextJunction = currentRoad;
	}
	else if (IS_STRAIGHT_SURFACE(currentRoad))
	{
		volatile int d; // offset 0x70
		volatile int toGo; // offset 0x74
		volatile int angle; // offset 0x78
		volatile int s; // offset 0x7c
		volatile int c; // offset 0x80
		volatile int fixedThresh;
		volatile int dx, dz;

		straight = GET_STRAIGHT(currentRoad);
		angle = straight->angle & 0xfff;

		dx = cp->hd.where.t[0] - straight->Midx;
		dz = cp->hd.where.t[2] - straight->Midz;
		
		if (straight->ConnectIdx[1] == -1)
			nextJunction = straight->ConnectIdx[0];
		else
			nextJunction = straight->ConnectIdx[1];

		if (cp->ai.l.direction == 0)
		{
			if (cp->hd.direction - angle + 1024 & 2048)
				cp->ai.l.direction = -1;
			else
				cp->ai.l.direction = 1;
		}

		if (cp->ai.l.direction == -1)
		{
			angle ^= 2048;
			
			if (straight->ConnectIdx[3] == -1)
				nextJunction = straight->ConnectIdx[2];
			else
				nextJunction = straight->ConnectIdx[3];
		}
		
		s = RSIN(angle);
		c = RCOS(angle);
		
		d = FIXEDH(s * dx + c * dz);

		toGo = (straight->length / 2) - d;
		
		if (cp->hd.speed > 100)
			fixedThresh = LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul;
		else
			fixedThresh = LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul;

		if (toGo < fixedThresh && cp->ai.l.offRoad == 0 && cp->ai.l.dstate != LeadDrive_Panic)
		{
			checkNext = 1;
			cp->ai.l.direction = 0;
		}
		else
		{
			if (cp->hd.speed > 100)
				fixedThresh = LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul;
			else
				fixedThresh = LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul;

			if (toGo < fixedThresh * 3)
				cp->ai.l.nextTurn += 16;

			cp->ai.l.d = FIXEDH(-c * dx + s * dz);
			cp->ai.l.width = ROAD_LANES_COUNT(straight) * 512;
		}
	}
	else if (IS_CURVED_SURFACE(currentRoad))
	{
		volatile int angle; // offset 0x84
		volatile int radius; // offset 0x88
		volatile int dx; // offset 0x8c
		volatile int dz; // offset 0x90
		volatile int fixedThresh; // offset 0x94

		curve = GET_CURVE(currentRoad);
		dx = cp->hd.where.t[0] - curve->Midx;
		dz = cp->hd.where.t[2] - curve->Midz;
		angle = ratan2(dx, dz);

		if (cp->ai.l.direction == 0)
		{

			if (angle - cp->hd.direction & 2048U)
				cp->ai.l.direction = 1;
			else
				cp->ai.l.direction = -1;
		}

		if (cp->ai.l.direction == 1)
		{
			radius = (curve->inside + ROAD_LANES_COUNT(curve)) * 1024 - cp->ai.l.roadPosition;

			if (cp->hd.speed > 100)
				fixedThresh = (LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul) / radius;
			else
				fixedThresh = (LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul) / radius;

			if (fixedThresh >= 4096 && (curve->end - angle & 1U) != 0)
			{
				if (curve->ConnectIdx[1] == -1)
					nextJunction = curve->ConnectIdx[0];
				else
					nextJunction = curve->ConnectIdx[1];

				checkNext = 1;
				cp->ai.l.direction = 0;
			}
			else
			{
				if (fixedThresh * 3 >= 4096 && (curve->end - angle & 1U))
				{
					cp->ai.l.nextTurn += 16;
				}

				cp->ai.l.base_Normal = cp->ai.l.d = hypot(dx, dz);
				cp->ai.l.base_Dir = 1;
				cp->ai.l.base_Angle = angle;
				cp->ai.l.d = cp->ai.l.d - (curve->inside * 1024 + ROAD_LANES_COUNT(curve) * 512);
				cp->ai.l.width = ROAD_LANES_COUNT(curve) * 512;
			}
		}
		else
		{
			radius = curve->inside * 1024 + cp->ai.l.roadPosition;

			if (cp->hd.speed > 100)
				fixedThresh = (LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul) / radius;
			else
				fixedThresh = (LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul) / radius;

			if (fixedThresh >= 4096 && (angle - curve->start & 1U))
			{
				if (curve->ConnectIdx[3] == -1)
					nextJunction = curve->ConnectIdx[2];
				else
					nextJunction = curve->ConnectIdx[3];

				checkNext = 1;
				cp->ai.l.direction = 0;
			}
			else
			{
				if (fixedThresh * 3 >= 4096 && (angle - curve->start & 1U))
					cp->ai.l.nextTurn += 16;

				cp->ai.l.base_Normal = cp->ai.l.d = hypot(dx, dz);
				cp->ai.l.base_Dir = -1;
				cp->ai.l.base_Angle = angle;
				cp->ai.l.d = curve->inside * 1024 + ROAD_LANES_COUNT(curve) * 512 - cp->ai.l.d;
				cp->ai.l.width = ROAD_LANES_COUNT(curve) * 512;
			}
		}
	}
	else
	{
		// continue
		currentRoad = cp->ai.l.lastRoad;
	}

	if (checkNext)
	{
		int diff;
		
		currentRoad = nextJunction;

		if (IS_JUNCTION_SURFACE(nextJunction))
		{
			junction = GET_JUNCTION(nextJunction);
			
			if (nextJunction != cp->ai.l.nextJunction)
			{
				SelectExit(cp, junction);
				cp->ai.l.nextJunction = nextJunction;
			}
			
			currentRoad = junction->ExitIdx[cp->ai.l.nextExit];
			heading = (cp->ai.l.nextExit & 3) << 10;
		}
		else
		{
			if (IS_STRAIGHT_SURFACE(nextJunction))
			{
				straight = GET_STRAIGHT(nextJunction);
				heading = straight->angle & 0xfff;

				if ((cp->hd.direction - heading + 0x400 & 0x800) != 0)
				{
					heading ^= 2048;
				}
			}
			else if (IS_CURVED_SURFACE(nextJunction))
			{
				int angle;
				int dx; // offset 0x9c
				int dz; // offset 0xa0

				curve = GET_CURVE(nextJunction);

				dx = cp->hd.where.t[0] - curve->Midx;
				dz = cp->hd.where.t[2] - curve->Midz;
				
				angle = ratan2(dx, dz);

				if ((angle - cp->hd.direction & 2048U) != 0)
					heading = angle + 1024U & 0xfff;
				else
					heading = angle - 1024U & 0xfff;
			}
		}

		diff = DIFF_ANGLES(cp->hd.direction, heading); //(heading - cp->hd.direction + 2048 & 0xfff) - 2048;

		if (IS_STRAIGHT_SURFACE(currentRoad))
		{
			int cs, sn;
			int dx; // offset 0xa4
			int dz; // offset 0xa8
			int dist; // offset 0xac
			int offx; // offset 0xb0
			int offz; // offset 0xb4

			straight = GET_STRAIGHT(currentRoad);

			sn = RSIN(heading);
			cs = RCOS(heading);
			
			offx = straight->Midx - cp->hd.where.t[0];
			offz = straight->Midz - cp->hd.where.t[2];
			
			dist = -FIXEDH(offx * sn + offz * cs);
			
			cp->ai.l.d = FIXEDH(cs * offx - sn * offz);
			cp->ai.l.width = ROAD_LANES_COUNT(straight) * 512;
			
			dx = FIXEDH(sn * dist);
			dz = FIXEDH(cs * dist);
			
			basePosition.vx = straight->Midx + dx;
			basePosition.vy = cp->hd.where.t[1];
			basePosition.vz = straight->Midz + dz;
		}
		else if (IS_CURVED_SURFACE(currentRoad))
		{
			int radius;
			int angle; // offset 0xb8
			int dx; // offset 0xbc
			int dz; // offset 0xc0
			int basex; // offset 0xc4
			int basez; // offset 0xc8
			int dist; // offset 0xcc
			int offx; // offset 0xd0
			int offz; // offset 0xd4

			curve = GET_CURVE(currentRoad);
			dx = cp->hd.where.t[0] - curve->Midx;
			dz = cp->hd.where.t[2] - curve->Midz;
			
			radius = curve->inside * 1024 + ROAD_LANES_COUNT(curve) * 512;
			angle = ratan2(dx, dz);

			// check directions
			if (angle - heading & 2048)
			{
				basex = FIXEDH(RSIN(curve->start) * radius);
				basez = FIXEDH(RCOS(curve->start) * radius);

				cp->ai.l.base_Normal = cp->ai.l.d = hypot(dx, dz);
				cp->ai.l.base_Dir = 1;
				cp->ai.l.base_Angle = angle;
				cp->ai.l.d = cp->ai.l.d - radius;
			}
			else
			{
				basex = FIXEDH(RSIN(curve->end) * radius);
				basez = FIXEDH(RCOS(curve->end) * radius);

				cp->ai.l.base_Normal = cp->ai.l.d = hypot(dx, dz);
				cp->ai.l.base_Dir = -1;
				cp->ai.l.base_Angle = angle;
				cp->ai.l.d = radius - cp->ai.l.d;
			}

			cp->ai.l.width = ROAD_LANES_COUNT(curve) * 512;
			offx = basex - cp->hd.where.t[0];
			offz = basez - cp->hd.where.t[2];
			
			dist = -FIXEDH(offx * RSIN(heading) + offz * RCOS(heading));
			dx = FIXEDH(RSIN(heading) * dist);
			dz = FIXEDH(RCOS(heading) * dist);
			
			basePosition.vx = basex + dx;
			basePosition.vy = cp->hd.where.t[1];
			basePosition.vz = basez + dz;
		}
		else
		{
			basePosition.vx = cp->hd.where.t[0];
			basePosition.vy = cp->hd.where.t[1];
			basePosition.vz = cp->hd.where.t[2];
		}

		cp->ai.l.currentRoad = currentRoad;

		if (ABS(diff) < 512)
		{
			basePosition.vx = cp->hd.where.t[0];
			basePosition.vy = cp->hd.where.t[1];
			basePosition.vz = cp->hd.where.t[2];

			UpdateRoadPosition(cp, &basePosition, 0);
		}
		else if (diff < 1)
		{
			UpdateRoadPosition(cp, &basePosition, 2);
		}
		else
		{
			UpdateRoadPosition(cp, &basePosition, 3);
		}

		SetTarget(cp, currentRoad, heading, &nextJunction);
	}
	else
	{
		basePosition.vx = cp->hd.where.t[0];
		basePosition.vy = cp->hd.where.t[1];
		basePosition.vz = cp->hd.where.t[2];

		// check for grass surface
		// or if AI is too far from road
		if (cp->ai.l.width + 2048 >= ABS(cp->ai.l.d) || 
			(cp->hd.wheel[1].surface & 7) == 3 || 
			(cp->hd.wheel[3].surface & 7) == 3)
		{
			cp->ai.l.currentRoad = currentRoad;
			cp->ai.l.lastRoad = currentRoad;
			cp->ai.l.lastDirection = cp->ai.l.direction;

			UpdateRoadPosition(cp, &basePosition, IS_CURVED_SURFACE(currentRoad) ? 1 : 0);

			SetTarget(cp, currentRoad, cp->hd.direction, &nextJunction);

			if (IS_JUNCTION_SURFACE(nextJunction))
			{
				if (nextJunction != cp->ai.l.nextJunction)
				{
					SelectExit(cp, GET_JUNCTION(nextJunction));
					cp->ai.l.nextJunction = nextJunction;
				}
			}
			else
			{
				cp->ai.l.nextJunction = -1;
			}
		}
		else
		{
			cp->ai.l.offRoad = 1;
			cp->ai.l.nextJunction = -1;
			
			UpdateRoadPosition(cp, &basePosition, 4);
			SetTarget(cp, currentRoad, cp->hd.direction, &nextJunction);
		}
	}
}

// [D] [T]
void SetTarget(CAR_DATA* cp, int curRoad, int heading, int* nextJunction)
{
	volatile int dx, dz; // offset 0xd8

	sdPlane* pl;
	VECTOR pos;
	DRIVER2_STRAIGHT* straight;
	DRIVER2_CURVE* curve;

	if (cp->ai.l.offRoad == 1)
	{
		int dir = cp->ai.l.roadPosition;
		
		// get the road
		dx = FIXEDH(RCOS(dir) * cp->ai.l.roadForward);
		dz = FIXEDH(RSIN(dir) * cp->ai.l.roadForward);

		cp->ai.l.targetX = cp->hd.where.t[0] + dx;
		cp->ai.l.targetZ = cp->hd.where.t[2] + dz;

		cp->ai.l.targetDir = dir;
		
		return;
	}

	if (IS_STRAIGHT_SURFACE(curRoad))
	{
		volatile int rx, rz;
		volatile int ux, uz;
		volatile int d;
		volatile int angle;
		volatile int mul;
		
		straight = GET_STRAIGHT(curRoad);
		cp->ai.l.targetDir = straight->angle & 0xfff;

		if (straight->ConnectIdx[1] == -1)
			*nextJunction = straight->ConnectIdx[0];
		else
			*nextJunction = straight->ConnectIdx[1];

		if (cp->ai.l.direction == -1 || 
			cp->ai.l.direction == 0 && (heading - cp->ai.l.targetDir + 1024U & 2048) != 0)
		{
			cp->ai.l.targetDir ^= 2048;
			
			if (straight->ConnectIdx[3] == -1)
				*nextJunction = straight->ConnectIdx[2];
			else
				*nextJunction = straight->ConnectIdx[3];
		}

		dx = straight->Midx - cp->hd.where.t[0];
		dz = straight->Midz - cp->hd.where.t[2];

		angle = cp->ai.l.targetDir;
		
		rx = FIXEDH(RSIN(angle) * cp->ai.l.roadForward);
		rz = FIXEDH(RCOS(angle) * cp->ai.l.roadForward);

		angle = cp->ai.l.targetDir + 1024;

		ux = RSIN(angle);
		uz = RCOS(angle);

		// l.roadPosition gives the lane offset
		// [A] it's obviously bugged somewhere as car always tends to be on left lanes
		// on curves it's even WORSE
		mul = FIXEDH(ux * dx + uz * dz) - ROAD_LANES_COUNT(straight) * 512 + cp->ai.l.roadPosition;
		
		ux = FIXEDH(mul * ux);
		uz = FIXEDH(mul * uz);
		
		cp->ai.l.targetX = cp->hd.where.t[0] + rx + ux;
		cp->ai.l.targetZ = cp->hd.where.t[2] + rz + uz;

		pos.vx = cp->ai.l.targetX;
		pos.vy = cp->hd.where.t[1];
		pos.vz = cp->ai.l.targetZ;
		
		pl = sdGetCell(&pos);
	}
	else if (IS_CURVED_SURFACE(curRoad))
	{
		volatile int angle;
		volatile int radius;
		
		curve = GET_CURVE(curRoad);
		angle = ratan2(cp->hd.where.t[0] - curve->Midx, cp->hd.where.t[2] - curve->Midz);

		if (cp->ai.l.direction == 1 || 
			cp->ai.l.direction == 0 && (angle - heading & 2048U) != 0)
		{
			radius = (curve->inside + ROAD_LANES_COUNT(curve)) * 1024 - cp->ai.l.roadPosition + cp->hd.speed * 2;

			angle += cp->ai.l.roadForward / radius;
			cp->ai.l.targetDir = angle + 1024;

			if (curve->ConnectIdx[1] != -1)
				*nextJunction = curve->ConnectIdx[1];
			else
				*nextJunction = curve->ConnectIdx[0];
		}
		else
		{
			radius = curve->inside * 1024 + cp->ai.l.roadPosition - cp->hd.speed * 2;

			angle -= cp->ai.l.roadForward / radius;
			cp->ai.l.targetDir = angle - 1024;

			if (curve->ConnectIdx[3] == -1)
				*nextJunction = curve->ConnectIdx[2];
			else
				*nextJunction = curve->ConnectIdx[3];
		}

		cp->ai.l.targetX = curve->Midx + FIXEDH(radius * RSIN(angle));
		cp->ai.l.targetZ = curve->Midz + FIXEDH(radius * RCOS(angle));
	}
}

// [D] [T]
void SelectExit(CAR_DATA* cp, DRIVER2_JUNCTION* junction)
{
	volatile int rnd;
	volatile int i;
	volatile int total;
	volatile int tmp;
	volatile int onward;
	volatile int numExits;
	volatile int el[4][2];
	short road;

	numExits = 0;
	total = 0;

	onward = (cp->ai.l.targetDir + 512U & 0xfff) >> 10;
	
	// [A] was weird loop
	for (i = 0; i < 4; i++)
	{
		if (junction->ExitIdx[i] == cp->ai.l.lastRoad)
		{
			onward = i + 2 & 3;
			break;
		}
	}

	// [A] was unrolled
	for(i = 0; i < 3; i++)
	{
		int d;

		if (i == 2)
			d = -1;
		else if (i == 1)
			d = 1;
		else
			d = 0;

		tmp = onward + d & 3;
		
		road = junction->ExitIdx[tmp];
		if (IS_CURVED_SURFACE(road) || IS_STRAIGHT_SURFACE(road))
		{
			el[numExits][0] = d;
			el[numExits][1] = junction->flags >> (tmp << 3) & 0xf;
			total += el[numExits][1];
			numExits++;
		}
	}

	if (total == 0)
	{
		total = 1;
		el[numExits][0] = 2;
		el[numExits][1] = 1;
		numExits++;
	}
	
	rnd = leadRand();
	rnd = ABS(rnd);

	// [A] again, was a strange loop. Hope it works
	tmp = 0;
	for(i = 0; i < numExits; i++)
	{
		tmp += el[i][1];

		cp->ai.l.nextTurn = el[i][0];
		
		if(tmp > rnd % total)
			break;
	}

	cp->ai.l.nextExit = onward + cp->ai.l.nextTurn & 3;

	rnd = leadRand();
	rnd = ABS(rnd);

	if (rnd == (rnd / 3) * 3)
		cp->ai.l.nextTurn = -cp->ai.l.nextTurn;
}

// [D] [T]
u_int FreeRoamer(CAR_DATA* cp)
{
	int i;
	int seed;
	CAR_DATA* pCar;

	LeadHorn(cp);
	
	DamageBar.position = cp->totalDamage;

	if (cp->ai.l.dstate != LeadDrive_FakeMotion)
	{
		// flipped? Or sinking in water?
		if (cp->hd.where.m[1][1] < 100 || (cp->hd.wheel[1].surface & 7) == 1 && (cp->hd.wheel[3].surface & 7) == 1)
			cp->totalDamage += 100;
	}

	cp->ai.l.ctt++;

	if (cp->ai.l.takeDamage != 0)
		cp->ai.l.takeDamage--;

	// re-randomize
	if (CameraCnt == 100)
	{
		if(player[0].playerCarId >= 0)
		{
			pCar = &car_data[player[0].playerCarId];
			seed = (pCar->hd.where.t[0] + pCar->hd.where.t[2]) / (pCar->hd.speed + 1);

			randIndex = 0;

			for (i = NUM_RAND_STATES - 1; i > -1; i--)
			{
				randState[i] = seed;
				seed = seed * 0x751 + 0x10cc2af;
			}

			for (i = NUM_RAND_ITERATIONS - 1; i > -1; i--)
				leadRand();
		}
	}

	LeadUpdateState(cp);

	return LeadPadResponse(cp);
}

// [D] [T]
u_int hypot(int x, int y)
{
	int t;

	x = ABS(x);
	y = ABS(y);

	if (x < y)
	{
		y = x;
		x = y;
	}

	if (x < 0x8000)
	{
		t = SquareRoot0(x * x + y * y);
	}
	else
	{
		t = FIXED(x);
		t = x + t * (SquareRoot0((y / t) * (y / t) + 0x1000800) - 4096);
	}

	return t;
}





