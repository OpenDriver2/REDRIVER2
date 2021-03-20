#include "driver2.h"
#include "cop_ai.h"
#include "civ_ai.h"
#include "mission.h"
#include "system.h"
#include "felony.h"
#include "cars.h"
#include "players.h"
#include "pathfind.h"
#include "gamesnd.h"
#include "cutscene.h"
#include "convert.h"
#include "map.h"
#include "camera.h"
#include "handling.h"
#include "objcoll.h"
#include "wheelforces.h"
#include "pad.h"
#include "pedest.h"
#include "pres.h"

struct iVectNT
{
	int n;
	int t;
};

COP_DATA gCopData = {
	0,
	0,
	0,
	2048,
	0,
	4096,
	2048,
	3000000,
	{ 0, 0, 0, 0, 0 }
};

int speed1[] = { 203, 210, 217 };
int speed2[] = { 238, 266, 294 };

int CopsCanSeePlayer = 0;
short pedestrianFelony = 0;

int numRoadblockCars = 0;
int roadblockCount = 0;
int copsAreInPursuit = 0;
int requestRoadblock = 0;
int roadblockDelay = 250;
int roadblockDelayDiff[3] = { 1500, 1000, 800 };
int requestCopCar = 0;
int cop_respawn_timer = 0;
char first_offence = 0;

ROADBLOCK Roadblock;
VECTOR roadblockLoc;

static int said_picked_up = 0;

char last_cop_phrase = 0;

char CopWorkMem[444];		// PVS table
COP_SIGHT_DATA copSightData;

int player_position_known = 0;
VECTOR lastKnownPosition;
VECTOR CarTail;
CAR_DATA *targetVehicle;

int numActiveCops = 0;
int pathStraight = 0;
int LastHeading = 0;
int OutOfSightCount = 0;

// [D] [T]
void InitCopState(CAR_DATA *cp, char *extraData)
{
	ClearMem((char *)&cp->ai.p, sizeof(COP));

	cp->controlType = CONTROL_TYPE_PURSUER_AI;
	cp->controlFlags = 0;
	cp->ai.p.justPinged = 1;

	if (gCopDifficultyLevel == 0)
		cp->hndType = 2;
	else if (gCopDifficultyLevel == 1) 
		cp->hndType = 3;
	else
		cp->hndType = 4;
}

int ReplayLog_Fnarr_He_Said_Log(int val)
{
	return 0;
}


// [D] [T]
int FindCost(int x, int z, int dvx, int dvz)
{
	static unsigned char sqtbl[] = {
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x81, 0x81, 0x81, 0x82, 0x82, 0x83, 0x83, 0x83, 0x84,
		0x84, 0x85, 0x86, 0x86, 0x87, 0x88, 0x88, 0x89, 0x8A,
		0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x90, 0x91,
		0x92, 0x93, 0x94, 0x95, 0x96, 0x98, 0x99, 0x9A, 0x9B,
		0x9C, 0x9D, 0x9E, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA6,
		0xA7, 0xA8, 0xAA, 0xAB, 0xAC, 0xAE, 0xAF, 0xB0, 0xB2,
		0xB3, 0xB5
	};

	int tx, tz, dx, dz;
	int d;

	tx = targetVehicle->hd.where.t[0] + dvx / 256;
	tz = targetVehicle->hd.where.t[2] + dvz / 256;

	dx = ABS(x - tx);
	dz = ABS(z - tz);

	// swap
	if (dz > dx)
	{
		d = dx;

		dx = dz;
		dz = d;
	}

	if (dx == 0)
		return 0;

	return (dx * sqtbl[(dz * 64) / dx]) / 128;
}

extern int distanceReturnedLog[8];
extern int distLogIndex;
extern int lastDistanceFound;

// [D] [T]
void WibbleDownTheRoad(VECTOR *from, int distance, VECTOR *to)
{
	int val;
	int j;
	int thl[4];
	VECTOR pos;
	VECTOR dir;

	pos.vx = from->vx;
	pos.vy = from->vy;
	pos.vz = from->vz;
	pos.pad = from->pad;

	j = 0;

	do {
		ReplayLog_Fnarr_He_Said_Log(pos.vx);
		ReplayLog_Fnarr_He_Said_Log(pos.vy);
		ReplayLog_Fnarr_He_Said_Log(pos.vz);

		val = getHeadingToPlayer(pos.vx, pos.vy, pos.vz);
		ReplayLog_Fnarr_He_Said_Log(val);

		if (j == 0)
		{
			distanceReturnedLog[distLogIndex & 7] = lastDistanceFound;
			distLogIndex++;
		}

		dir.vy = 0;
		dir.vx = FIXEDH((distance >> 2) * rcossin_tbl[(val & 0xfff) * 2]);
		dir.vz = FIXEDH((distance >> 2) * rcossin_tbl[(val & 0xfff) * 2 + 1]);

		thl[j] = val;

		VECTOR p2 = pos;

		pos.vx += dir.vx;
		pos.vy += dir.vy;
		pos.vz += dir.vz;

#if defined(COLLISION_DEBUG)
		extern int gShowCollisionDebug;
		if (gShowCollisionDebug == 3)
		{
			extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
			extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

			CVECTOR ggcv = { 0, 250, 0 };
			CVECTOR bbcv = { 0, 0, 250 };
			CVECTOR rrcv = { 250, 0, 0 };

			VECTOR _zero = { 0 };
			VECTOR _up = { 0, 1000, 0 };

			Debug_AddLine(p2, pos, bbcv);
		}
#endif

		j++;
	} while (j < 4);

	to->vx = pos.vx;
	to->vy = pos.vy;
	to->vz = pos.vz;
	to->pad = pos.pad;

	if (((thl[3] - thl[0]) + 200U & 0xfff) < 400) 
	{
		pathStraight = 1;
	}
}

// [D] [T]
void UpdateCopSightData(void)
{
	short* playerFelony;

	if (player[0].playerCarId < 0)
		playerFelony = &pedestrianFelony;
	else
		playerFelony = &car_data[player[0].playerCarId].felonyRating;

	if (*playerFelony > FELONY_MIN_VALUE)
	{
		copSightData.surroundViewDistance = 5440;
		copSightData.frontViewDistance = 16320;
		copSightData.frontViewAngle = 1024;
		return;
	}

	copSightData.surroundViewDistance = 2720;
	copSightData.frontViewDistance = 7820;
	copSightData.frontViewAngle = 512;
}

// [D] [T]
void InitCopData(COP_DATA* pCopData)
{
	short* pTrigger;
	int trigger;

	pTrigger = pCopData->trigger;
	trigger = 0;

	while (pTrigger < pCopData->trigger + 4)
	{
		*pTrigger = trigger;
		pTrigger++;

		trigger += 0x333;
	}

	*pTrigger = 0x7fff;
	said_picked_up = 0;
}

// [D] [T]
void InitCops(void)
{
	targetVehicle = &car_data[0];
	requestCopCar = 0;

	InitFelonySystem();
	InitPathFinding();

	felonyData.pursuitFelonyScale = 3000;

	gCopDesiredSpeedScale = 4096;
	gCopMaxPowerScale = 4096;
	gPuppyDogCop = 0;

	copsAreInPursuit = 0;

	player_position_known = 2;
	OutOfSightCount = 0;

	UpdateCopSightData();

	gCopData.autoMaxPowerScaleLimit = 0;
	gCopData.autoDesiredSpeedScaleLimit = 0;

	if (GameType == GAME_GETAWAY) 
	{
		gCopRespawnTime = 10000;
	}
	else if (GameType == GAME_SURVIVAL)
	{
		gCopRespawnTime = 0;
		gCopDesiredSpeedScale = 4596;
		gCopMaxPowerScale = 4596;
	
		gCopData.autoMaxPowerScaleLimit = 1024;
		gCopData.autoDesiredSpeedScaleLimit = 1024;
	}
	else
	{
		gCopRespawnTime = 320;

		if (gCurrentMissionNumber < 40)
			gCopRespawnTime = gCurrentMissionNumber * -4 + 320;
	}

	LastHeading = -1;
	pathStraight = 0;
	numActiveCops = 0;

	OutOfSightCount = 0;
	cop_respawn_timer = 0;
	CopsCanSeePlayer = 0;

	CarTail.vx = 0;
	CarTail.vy = 0;
	CarTail.vz = 0;

	lastKnownPosition.vx = 0x7fffffff;
	lastKnownPosition.vy = 0x7fffffff;
	lastKnownPosition.vz = 0x7fffffff;

	InitCopData(&gCopData);

	copsAreInPursuit = 0;
}

VECTOR targetPoint = { 0,0,0 };

// [D]
void CopControl1(CAR_DATA *cp)
{
	int targetFound;
	int steeringFac;
	int dist;
	short* playerFelony;
	int steerDif;
	int dz;
	int plcrspd;
	int dx;
	int dvx, dvz, idvx, idvz;
	int desiredSteerAngle;
	int x;
	int z;
	int currentSpeed;
	int slidevel;
	int maxPower;
	int speedDif;
	int doBatter;
	VECTOR pos;
	iVectNT path[2];
	AIZone targetZone;

	if (player[0].playerCarId < 0)
		playerFelony = &pedestrianFelony;
	else
		playerFelony = &car_data[player[0].playerCarId].felonyRating;

	desiredSteerAngle = 0;

	cp->wheelspin = 0;
	currentSpeed = FIXEDH(cp->hd.wheel_speed);

	if (CopsAllowed == 0)
	{
		cp->thrust = 0;
		cp->handbrake = 1;

		return;
	}

	// [A] new cop batter logic
	// survival setting really
	if(gBatterPlayer)
		doBatter = 1;
	else
		doBatter = 0;

	// [A] periodically beat player in ass
	if (!doBatter && *playerFelony > gCopData.autoBatterPlayerTrigger)
	{
		int batterTrigger;

		if(gCopDifficultyLevel == 0)
			batterTrigger = 80;
		else if (gCopDifficultyLevel == 1)
			batterTrigger = 50;
		else if (gCopDifficultyLevel == 2)
			batterTrigger = 0;

		if (cp->ai.p.batterTimer > batterTrigger)
			doBatter = 1;
		
		cp->ai.p.batterTimer++;
		cp->ai.p.batterTimer &= 127;
	}



	if (cp->ai.p.dying != 0 || 
		cp->totalDamage > 27000 && gCopData.immortal == 0)
	{
		cp->thrust = 0;

		if (cp->ai.p.dying > 85)
			return;

		if (cp->ai.p.dying == 0)
			numActiveCops--;

		cp->ai.p.dying++;
		return;
	}

	if (gStopCops.radius != 0)
	{
		dx = ABS(cp->hd.where.t[0] - gStopCops.pos.vx);
		dz = ABS(cp->hd.where.t[2] - gStopCops.pos.vz);

		if (dx + dz < gStopCops.radius * 3 / 2 && 
			SquareRoot0(dx * dx + dz * dz) < gStopCops.radius)
		{
			cp->thrust = 0;
			cp->handbrake = 1;
			return;
		}
	}

	if ((CameraCnt & 7U) == 0)
	{
		pos.vx = cp->hd.where.t[0] + FIXEDH(cp->hd.where.m[0][2] * 400 - cp->hd.where.m[0][0] * 150);
		pos.vy = cp->hd.where.t[1] + FIXEDH(cp->hd.where.m[1][2] * 400 - cp->hd.where.m[1][0] * 150);
		pos.vz = cp->hd.where.t[2] + FIXEDH(cp->hd.where.m[2][2] * 400 - cp->hd.where.m[2][0] * 150);

		cp->ai.p.frontLClear = CellAtPositionEmpty(&pos, 80);

#ifdef COLLISION_DEBUG
		extern int gShowCollisionDebug;
		if (gShowCollisionDebug == 3)
		{
			extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
			extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

			CVECTOR ggcv = { 0, 250, 0 };
			CVECTOR bbcv = { 0, 0, 250 };
			CVECTOR rrcv = { 250, 0, 0 };

			VECTOR _zero = { 0 };
			VECTOR _up = { 0, 1000, 0 };

			Debug_AddLineOfs(_zero, _up, pos, cp->ai.p.frontLClear ? ggcv : rrcv);
		}
#endif

		pos.vx = cp->hd.where.t[0] + FIXEDH(cp->hd.where.m[0][2] * 400 + cp->hd.where.m[0][0] * 150);
		pos.vy = cp->hd.where.t[1] + FIXEDH(cp->hd.where.m[1][2] * 400 + cp->hd.where.m[1][0] * 150);
		pos.vz = cp->hd.where.t[2] + FIXEDH(cp->hd.where.m[2][2] * 400 + cp->hd.where.m[2][0] * 150);

		cp->ai.p.frontRClear = CellAtPositionEmpty(&pos, 80);

#ifdef COLLISION_DEBUG
		extern int gShowCollisionDebug;
		if (gShowCollisionDebug == 3)
		{
			extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
			extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

			CVECTOR ggcv = { 0, 250, 0 };
			CVECTOR bbcv = { 0, 0, 250 };
			CVECTOR rrcv = { 250, 0, 0 };

			VECTOR _zero = { 0 };
			VECTOR _up = { 0, 1000, 0 };

			Debug_AddLineOfs(_zero, _up, pos, cp->ai.p.frontRClear ? ggcv : rrcv);
		}
#endif
	}

	x = cp->hd.where.t[0];
	z = cp->hd.where.t[2];

	pathStraight = 0;

	if (cp->hd.speed < 6 && cp->ai.p.desiredSpeed != 0)
		cp->ai.p.stuckTimer++;
	else
		cp->ai.p.stuckTimer = 0;

	if (cp->ai.p.stuckTimer > 10 && cp->ai.p.recoveryTimer == 0)
	{
		cp->ai.p.recoveryTimer = 22;
		cp->ai.p.lastRecoverStrategy = cp->ai.p.lastRecoverStrategy & 7;

		if (cp->ai.p.desiredSpeed < 0)
			cp->ai.p.desiredSpeed = 200;
		else
			cp->ai.p.desiredSpeed = -200;

		desiredSteerAngle = ((cp->ai.p.lastRecoverStrategy * 5 & 6) - 3) * 0x80;
		cp->ai.p.stuckTimer = 0;
	}

	dvx = targetVehicle->st.n.linearVelocity[0] - cp->st.n.linearVelocity[0];
	dvz = targetVehicle->st.n.linearVelocity[2] - cp->st.n.linearVelocity[2];
	
	dist = FindCost(x, z, dvx, dvz);

	cp->ai.p.close_pursuit = (dist < 2800);
	
	targetFound = 0;

	if (cp->ai.p.recoveryTimer < 1)
	{
		if (dist < 8400)
		{
			int dd;
			
			dx = x - targetVehicle->hd.where.t[0];
			dz = targetVehicle->hd.where.t[2] - z;
			
			idvx = FIXEDH(dvx);
			idvz = FIXEDH(dvz);
			
			dd = (dx * idvx - dz * idvz) / (idvx * idvx + idvz * idvz + 1);

			if (doBatter == 0)
				dd = dd * 3 / 4;

			if (dd < 0)
				dd = 0;
			else if (dd > 60) 
				dd = 60;

			dvz = targetVehicle->hd.where.t[0] + FIXEDH(targetVehicle->st.n.linearVelocity[0] * dd);
			dvx = targetVehicle->hd.where.t[2] + FIXEDH(targetVehicle->st.n.linearVelocity[2] * dd);

			if (doBatter == 0)
			{
				CarTail.vx = dvz - (targetVehicle->hd.where.m[0][2] * 5 >> 7);
				CarTail.vz = dvx - (targetVehicle->hd.where.m[2][2] * 5 >> 7);
			}
			else 
			{
				CarTail.vx = dvz + (targetVehicle->hd.where.m[0][0] * 5 >> 8);
				CarTail.vz = dvx + (targetVehicle->hd.where.m[2][0] * 5 >> 8);
			}
		}
		else 
		{
			CarTail.vx = targetVehicle->hd.where.t[0];
			CarTail.vz = targetVehicle->hd.where.t[2];
		}

		if (cp->ai.p.close_pursuit == 0) 
		{
			WibbleDownTheRoad((VECTOR*)cp->hd.where.t, cp->hd.speed * 10 + 680, &targetPoint);
		}
		else 
		{
			targetPoint.vx = CarTail.vx;
			targetPoint.vz = CarTail.vz;

#if 0
			{
				extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
				extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

				CVECTOR ggcv = { 0, 250, 0 };
				CVECTOR bbcv = { 0, 0, 250 };
				CVECTOR rrcv = { 250, 0, 0 };

				VECTOR _zero = { 0 };
				VECTOR _up = { 0, 1000, 0 };

				Debug_AddLineOfs(_zero, _up, targetPoint, rrcv);
			}
#endif
		}

		targetFound = 1;

		cp->ai.p.targetHistory[1].vx = cp->ai.p.targetHistory[0].vx;
		cp->ai.p.targetHistory[1].vz = cp->ai.p.targetHistory[0].vz;
		cp->ai.p.targetHistory[0].vx = targetPoint.vx;
		cp->ai.p.targetHistory[0].vz = targetPoint.vz;
	}
	else 
	{
		cp->ai.p.recoveryTimer--;
	}

	//if (gTimeInWater == 0) 
	//	targetFound = 0;

	if (targetFound) 
	{
		slidevel = FIXEDH(cp->hd.where.m[0][0] * cp->st.n.linearVelocity[0] + cp->hd.where.m[2][0] * cp->st.n.linearVelocity[2]);

		path[1].t = dvx = FIXEDH((x - targetPoint.vx) * cp->hd.where.m[2][0] + (targetPoint.vz - z) * cp->hd.where.m[0][0]);
		path[1].n = steeringFac = FIXEDH((targetPoint.vx - x) * cp->hd.where.m[0][0] + (targetPoint.vz - z) * cp->hd.where.m[2][0]) - slidevel / 140;

		if (path[1].n < 1) 
		{
			if (path[1].n * -2 >= path[1].t || cp->ai.p.frontLClear == 0)
			{
				targetZone = zoneLeft;
				targetFound = -path[1].n < (path[1].t << 2);

				if (targetFound && cp->ai.p.close_pursuit != 0) 
					targetZone = zoneBack;
			}
			else
				targetZone = zoneFrnt;
		}
		else 
		{
			if (path[1].n * 2 >= path[1].t || cp->ai.p.frontRClear == 0) 
			{
				targetZone = zoneRght;
				targetFound = path[1].n < (path[1].t << 2);
				
				if (targetFound && cp->ai.p.close_pursuit != 0) 
					targetZone = zoneBack;
			}
			else
				targetZone = zoneFrnt;
		}

		steerDif = path[1].n + slidevel / 140;

		if (targetZone == zoneFrnt)
		{			
			if (pathStraight == 0)
				cp->ai.p.desiredSpeed = speed1[gCopDifficultyLevel];
			else
				cp->ai.p.desiredSpeed = speed2[gCopDifficultyLevel];

			if (gCopData.cutOffDistance < cp->ai.p.DistanceToPlayer)
				maxPower = gCopData.cutOffPowerScale;
			else
				maxPower = gCopDesiredSpeedScale;

			cp->ai.p.desiredSpeed = FIXEDH(cp->ai.p.desiredSpeed * (maxPower + FIXEDH(*playerFelony * gCopData.autoDesiredSpeedScaleLimit)));

			if ((gPuppyDogCop || player[0].playerType == 2) && cp->ai.p.close_pursuit)
			{
				plcrspd = targetVehicle->hd.speed + 10;
				
				if (dist > 4000)
				{
					speedDif = (cp->ai.p.desiredSpeed - plcrspd) * (dist - 4000);
					cp->ai.p.desiredSpeed = plcrspd + speedDif / 4000;
				}
				else
				{
					cp->ai.p.desiredSpeed = plcrspd;
				}
			}

			desiredSteerAngle = (steerDif * 512) / path[1].t;
		}
		else if (targetZone == zoneBack)
		{
			cp->ai.p.desiredSpeed = -70;
			
			if ((steerDif ^ currentSpeed) < 0) 
				desiredSteerAngle = -284;
			else
				desiredSteerAngle = 284;
		}
		else
		{
			cp->ai.p.desiredSpeed = 110;

			if (cp->ai.p.frontLClear == 0 && cp->ai.p.frontRClear == 0)
			{
				cp->ai.p.desiredSpeed = -120;
			}
			else if ((targetZone == zoneLeft && cp->st.n.angularVelocity[1] > -130) || 
					 (targetZone == zoneRght && cp->st.n.angularVelocity[1] < 130))
			{
				cp->wheelspin = 1;
			}

			if ((steerDif ^ currentSpeed) < 0)
				desiredSteerAngle = -512;
			else
				desiredSteerAngle = 512;
		}
	}
	else if (cp->ai.p.recoveryTimer < 1) 
	{
		cp->ai.p.desiredSpeed = 0;
		desiredSteerAngle = 0;
	}

	// calculate the desired speed
	if (dist < 4096 && cp->ai.p.desiredSpeed > 0 && doBatter == 0)
	{
		plcrspd = targetVehicle->hd.speed - 20;

		if (plcrspd < 20)
			plcrspd = 20;

		cp->ai.p.desiredSpeed = FIXEDH(dist * cp->ai.p.desiredSpeed + (4096 - dist) * plcrspd);
	}

	// calculate acceleration
	maxPower = steeringFac = (gCopDifficultyLevel + 8) * 1024;
	currentSpeed = cp->ai.p.desiredSpeed - currentSpeed;

	if (pathStraight != 0)
		maxPower += (gCopDifficultyLevel + 4) * 1024;

	if (player[0].playerCarId < 0)
		playerFelony = &pedestrianFelony;
	else
		playerFelony = &car_data[player[0].playerCarId].felonyRating;

	maxPower = FIXEDH(maxPower * (gCopMaxPowerScale + FIXEDH(*playerFelony * gCopData.autoMaxPowerScaleLimit)));

	if (currentSpeed < -50)
		cp->thrust = -maxPower;
	else if (currentSpeed > 50)
		cp->thrust = maxPower;
	else
		cp->thrust = (currentSpeed * maxPower) / 50;

	if (cp->hd.speed < 48) 
		cp->thrust = (cp->thrust * (cp->hd.speed + 80) >> 7);

	if (handlingType[cp->hndType].fourWheelDrive == 1)
		cp->thrust /= 2;

	cp->thrust = (cp->thrust * 7) / 10;

	// calculate steering and direction
	steeringFac = ((desiredSteerAngle + 0x800U & 0xfff) - 0x800) - cp->wheel_angle;

	if (steeringFac < -200)
		steeringFac = -200;
	else if (steeringFac > 200)
		steeringFac = 200;

	cp->wheel_angle += steeringFac;

	if (cp->ai.p.justPinged == 1)
	{
		cp->hd.direction = getHeadingToPlayer(cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2]);
		TempBuildHandlingMatrix((CAR_DATA*)cp, 0);

		cp->ai.p.justPinged = 0;
	}
}

// [D] [T]
void ControlCopDetection(void)
{
	bool spotted;
	uint distanceToPlayer;
	uint minDistanceToPlayer;
	int heading;
	int dx, dz;
	CAR_DATA *cp;
	VECTOR vec;
	int ccx;
	int ccz;

	vec.vx = player[0].pos[0];
	vec.vy = player[0].pos[1];
	vec.vz = player[0].pos[2];

	GetVisSetAtPosition(&vec, CopWorkMem, &ccx, &ccz);

	UpdateCopSightData();

	if (player_position_known < 1) 
		player_position_known = 1;
	else
		player_position_known = 2;

	CopsCanSeePlayer = (GameType == GAME_SURVIVAL);

	minDistanceToPlayer = 0xFFFFFFFF;

	// check roadblock visibility
	if (numRoadblockCars != 0)
	{
		dx = ABS(roadblockLoc.vx - vec.vx) >> 8;
		dz = ABS(roadblockLoc.vz - vec.vz) >> 8;

		distanceToPlayer = dx * dx + dz * dz;
		
		if (distanceToPlayer < 1640 &&
			newPositionVisible(&roadblockLoc, CopWorkMem, ccx, ccz) != 0)
		{
			CopsCanSeePlayer = 1;

			if (distanceToPlayer << 8 < minDistanceToPlayer)
				minDistanceToPlayer = distanceToPlayer << 6;
		}
	}

	if (!CopsCanSeePlayer && !((gCurrentMissionNumber == 24 || gCurrentMissionNumber == 30) && CameraCnt-frameStart < 100))
	{
		cp = &car_data[MAX_CARS-1];

		while (car_data <= cp)
		{
			if (cp->controlType == CONTROL_TYPE_PURSUER_AI && cp->ai.p.dying == 0 || 
				(cp->controlFlags & CONTROL_FLAG_COP))
			{
				dx = ABS(cp->hd.where.t[0] - vec.vx) >> 8;
				dz = ABS(cp->hd.where.t[2] - vec.vz) >> 8;

				distanceToPlayer = SquareRoot0(dx * dx + dz * dz) << 8;

				if (distanceToPlayer < minDistanceToPlayer)
					minDistanceToPlayer = distanceToPlayer;

				if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
				{
					cp->ai.p.DistanceToPlayer = distanceToPlayer;

					if(cp->ai.p.close_pursuit)
					{
						CopsCanSeePlayer = 1;
						break;
					}
				}

				if (newPositionVisible(&vec, CopWorkMem, ccx, ccz) )
				{
					spotted = false;
					
					if (distanceToPlayer < copSightData.surroundViewDistance) 
					{
						spotted = true;
					}
					else if (distanceToPlayer < copSightData.frontViewDistance)
					{
						int theta;

						dz = vec.vx - cp->hd.where.t[0];
						dx = vec.vz - cp->hd.where.t[2];

						theta = ABS(ratan2(dz, dx) - cp->hd.direction);
						
						if (theta < copSightData.frontViewAngle || 
							(theta + 512 & 0xfff) < copSightData.frontViewAngle + 512)
						{
							spotted = true;
						}
					}

					// [A] also check player elevation from cops (block cops vision from bridges, tunnels etc)
					if (spotted && ABS(cp->hd.where.t[1] - vec.vy) < 1500) 
					{
						CopsCanSeePlayer = 1;
						break;
					}
				}
			}
			cp--;
		}
	}

	// [A] if Tanner is outside car, cops can arrest him if they are too close
	if(player[0].playerType == 2 && minDistanceToPlayer < 2048 && !player[0].dying && pedestrianFelony > FELONY_MIN_VALUE)
	{
		player[0].dying = 1;
		
		SetMissionMessage(G_LTXT(GTXT_YouveBeenCaught),3,2);
		SetMissionFailed(FAILED_MESSAGESET);
	}

	if (numActiveCops == 0 && OutOfSightCount < 256 && CameraCnt > 8) 
	{
		OutOfSightCount = 256;
	}

	// if cops can't see player - get out of pursued state
	if (!CopsCanSeePlayer)
	{
		if (OutOfSightCount <= 255) 
		{
			OutOfSightCount++;
		}
		else if (OutOfSightCount == 256) 
		{
			player_position_known = -1;
			OutOfSightCount = 257;

			if (first_offence == 0)
			{
				CopSay(12, 0);
				FunkUpDaBGMTunez(0);
			}
		}
		else 
		{
			player_position_known = 0;
		}
	}
	else 
	{
		OutOfSightCount = 0;
	}

	if (player_position_known < 1)
	{
		cp = &car_data[MAX_CARS-1];

		do {
			if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
			{
				vec.vx = cp->hd.where.t[0];
				vec.vz = cp->hd.where.t[2];

				// make cop lose target if target is hidden
				if (newPositionVisible(&vec, CopWorkMem, ccx, ccz) == 0 && cp->ai.p.hiddenTimer++ > 50)
				{
					cp->controlType = CONTROL_TYPE_NONE;
					cp->ai.p.hiddenTimer = 0;
					cp->thrust = 0;
					numCopCars--;
				}
			}

			cp--;
		} while (car_data <= cp);
	}

	if (player_position_known == 1 && first_offence == 0) 
	{
		heading = GetCarDirectionOfTravel(&car_data[player[0].playerCarId]);

		CopSay(Random2(2) % 2 + 10, heading);

		said_picked_up = player_position_known;

		LastHeading = heading;
	}

	if (!CopsCanSeePlayer)
	{
		said_picked_up = 0;
	}
	else if (first_offence == 0 && said_picked_up == 0) 
	{
		int rnd;
		rnd = Random2(2);

		heading = GetCarDirectionOfTravel(&car_data[player[0].playerCarId]);

		if ((rnd == (rnd / 5) * 5) && (dx != LastHeading))
			CopSay(rnd % 2 + 10, heading);

		said_picked_up = 1;
		LastHeading = heading;
	}
}

// [D] [T]
void PassiveCopTasks(CAR_DATA *cp)
{
	short *playerFelony;

	if (player[0].playerCarId < 0)
		playerFelony = &pedestrianFelony;
	else 
		playerFelony = &car_data[player[0].playerCarId].felonyRating;

	if (*playerFelony <= FELONY_MIN_VALUE)
		return;

	// [A] make an ambush on player in Destroy the yard
	// but don't in Car bomb getaway
	if (player_position_known < 1 || !CopsCanSeePlayer && gCurrentMissionNumber == 24)
		return;

	InitCopState(cp, NULL);

	cp->ai.p.justPinged = 0;

	numCivCars--;
	numActiveCops++;
}

// [D] [T]
void ControlNumberOfCops(void)
{
	short *pTrigger;
	short *playerFelony;
	int tempDist;
	CAR_DATA *lcp;
	int respawnTime;
	int num_closer;
	int cutOffDistance;
	int numWantedCops;

	pTrigger = gCopData.trigger;
	numWantedCops = 0;

	while( true ) 
	{
		if (player[0].playerCarId < 0)
			playerFelony = &pedestrianFelony;
		else
			playerFelony = &car_data[player[0].playerCarId].felonyRating;

		if (*playerFelony < *pTrigger) 
			break;

		pTrigger++;
		numWantedCops++;
	}

	if (numWantedCops < gMinimumCops)
		numWantedCops = gMinimumCops;

	if (numWantedCops > maxCopCars)
		numWantedCops = maxCopCars;
	
	if (numCopCars < numWantedCops && gDontPingInCops == 0)
	{
		respawnTime = gCopRespawnTime;
		
		if (Roadblock.status == 2)
			respawnTime = Roadblock.copRespawnTime;

		if (respawnTime * FIXED(4096 - FIXED(*playerFelony * gCopData.autoRespawnScaleLimit)) < cop_respawn_timer + 1)
		{
			requestCopCar = 1;
		}

		cop_respawn_timer++;
		return;
	}

	if (numCopCars <= numWantedCops) 
	{
		gCopData.cutOffDistance = 0x7fffffff;
		cop_respawn_timer = 0;
		return;
	}
	
	gCopData.cutOffDistance = 0x7fffffff;

	do {
		cutOffDistance = 0;
		lcp = car_data;
		num_closer = 0;

		do {
			if (lcp->controlType == CONTROL_TYPE_PURSUER_AI) 
			{
				tempDist = lcp->ai.p.DistanceToPlayer;
				
				if (tempDist < gCopData.cutOffDistance)
				{
					if(cutOffDistance < tempDist)
						cutOffDistance = tempDist;
					
					num_closer++;
				}
			}
			lcp++;
		} while (lcp < &car_data[MAX_CARS]);

		gCopData.cutOffDistance = cutOffDistance;
	} while (numWantedCops < num_closer);

	cop_respawn_timer = 0;
}

// [D] [T]
void ControlCops(void)
{
	short* playerFelony;
	int heading;
	int phrase;
	int copsWereInPursuit;

#if 0 // [A] lineClear debugging code - pls remove after fixing bugs
	extern int gShowCollisionDebug;
	if (gShowCollisionDebug == 3)
	{
		extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
		extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

		CVECTOR ggcv = { 0, 250, 0 };
		CVECTOR bbcv = { 0, 0, 250 };
		CVECTOR rrcv = { 250, 0, 0 };

		VECTOR _zero = { 0 };
		VECTOR _up = { 0, 1000, 0 };

		VECTOR v1 = *(VECTOR*)targetVehicle->hd.where.t;
		VECTOR v2 = v1;
		v2.vx -= FIXEDH(targetVehicle->hd.where.m[2][0] * 1024);
		v2.vz += FIXEDH(targetVehicle->hd.where.m[2][2] * 1024);

		int result = lineClear(&v1, &v2);

		Debug_AddLine(v1, v2, result ? ggcv : rrcv);
	}
#endif

	if (player[0].playerCarId < 0)
		playerFelony = &pedestrianFelony;
	else
		playerFelony = &car_data[player[0].playerCarId].felonyRating;

	gCopData.autoBatterPlayerTrigger = 2048;

	if (CopsAllowed == 0 || gInGameCutsceneActive != 0)
	{
		player_position_known = 0;
		CopsCanSeePlayer = 0;
		requestCopCar = 0;
		copsWereInPursuit = copsAreInPursuit;
	}
	else
	{
		if (player[0].playerCarId > -1)
			targetVehicle = &car_data[player[0].playerCarId];
		else
			targetVehicle = &car_data[TANNER_COLLIDER_CARID];	// [A] fix bug of chasing car

		if (player_position_known > 0)
		{
			lastKnownPosition.vx = player[0].pos[0];
			lastKnownPosition.vy = player[0].pos[1];
			lastKnownPosition.vz = player[0].pos[2];
			lastKnownPosition.pad = player[0].pos[3];
		}

		// update pathfinding
		UpdateCopMap();

		heading = LastHeading;

		// play the phrases about direction
		if (first_offence == 0 && CopsCanSeePlayer && numActiveCops != 0)
		{
			if (*playerFelony > 658 && TimeSinceLastSpeech > 720 && targetVehicle->hd.speed > 20)
			{
				int rnd;
				heading = GetCarDirectionOfTravel(targetVehicle);

				if (heading != LastHeading)
				{
					rnd = Random2(1);

					if ((MaxPlayerDamage[0] * 3) / 4 < car_data[player[0].playerCarId].totalDamage)
						phrase = rnd % 4;
					else
						phrase = rnd % 3;

					//phrase = rnd + phrase;

					if (first_offence == 0 && last_cop_phrase != phrase && TimeSinceLastSpeech > 720)
					{
						if (phrase < 3)
						{
							CopSay(phrase + 15, heading);
							last_cop_phrase = phrase;
						}
						else
						{
							CopSay(6, 0);
							last_cop_phrase = phrase;
						}
					}
				}
			}
		}

		LastHeading = heading;

		ControlCopDetection();

		AdjustFelony(&felonyData);

		ControlNumberOfCops();

		copsWereInPursuit = 0;

		if (CopsCanSeePlayer && OutOfSightCount < 256 ||	// [A] was player_position_known. Resolves speech in some missions
			player_position_known > 1 && GameType == GAME_GETAWAY)
		{
			if (*playerFelony > FELONY_MIN_VALUE)
				copsWereInPursuit = 1;
		}

		// start pursuit
		if (copsWereInPursuit != 0)
		{
			if (copsAreInPursuit == 0)
				Pads[0].alarmShakeCounter = 12;

			copsAreInPursuit = 1;

			FunkUpDaBGMTunez(1);

			if (first_offence != 0)
			{
				CopSay(9, 0);

				first_offence = 0;
				said_picked_up = 1;
			}
		}
	}

	copsAreInPursuit = copsWereInPursuit;
}

// [D] [T]
void CopControl(CAR_DATA* cp)
{
	CopControl1(cp);

	CheckPingOut(cp);

	if (cp->ai.p.dying == 0 && cp->controlType == CONTROL_TYPE_NONE)
	{
		numActiveCops--;
		numCopCars--;
	}
}