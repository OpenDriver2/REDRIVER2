#include "DRIVER2.H"
#include "LEADAI.H"
#include "OVERLAY.H"
#include "GAMESND.H"
#include "DR2ROADS.H"
#include "REPLAYS.H"
#include "PLAYERS.H"
#include "CAMERA.H"
#include "CARS.H"
#include "SPOOL.H"
#include "HANDLING.H"
#include "MAP.H"
#include "CELL.H"
#include "DRAW.H"
#include "MODELS.H"
#include "MAIN.H"
#include "PAD.H"

#define NUM_STATES 17
#define NUM_ITERATIONS 40

static int randIndex;
static int randState[NUM_STATES];

LEAD_PARAMETERS LeadValues;

static int pathParams[5] = {
	20480,-8192, 2048,-4096, 800
};

int road_s = 0;
int road_c = 0;

// decompiled code
// original method signature: 
// int /*$ra*/ leadRand()
 // line 205, offset 0x000e70a0
	/* begin block 1 */
		// Start line: 410
	/* end block 1 */
	// End Line: 411

	/* begin block 2 */
		// Start line: 412
	/* end block 2 */
	// End Line: 413

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
int leadRand(void)
{
	randIndex = (randIndex + 1) % NUM_STATES;

	return randState[randIndex] += randState[(randIndex + 12) % NUM_STATES];
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitLead(CAR_DATA *cp /*$s0*/)
 // line 278, offset 0x000e7128
	/* begin block 1 */
		// Start line: 279
		// Start offset: 0x000E7128

		/* begin block 1.1 */
			// Start line: 319
			// Start offset: 0x000E71A0
			// Variables:
		// 		DRIVER2_STRAIGHT *straight; // $a3
		// 		DRIVER2_CURVE *curve; // $t0
		// 		int i; // $a2
		// 		int dx; // $a0
		// 		int dz; // $a1
		// 		int sqrdist; // $v1
		// 		int min; // $t1
		/* end block 1.1 */
		// End offset: 0x000E7310
		// End Line: 352
	/* end block 1 */
	// End offset: 0x000E73E8
	// End Line: 378

	/* begin block 2 */
		// Start line: 559
	/* end block 2 */
	// End Line: 560

// [D] [T]
void InitLead(CAR_DATA* cp)
{
	cp->hndType = 5;
	cp->controlType = CONTROL_TYPE_LEAD_AI;
	cp->ai.l.roadPosition = 512;
	cp->ai.l.dstate = 3;
	cp->ai.l.recoverTime = 40;
	cp->ai.l.nextExit = 2;
	cp->ai.l.roadForward = 5120;
	cp->ai.l.takeDamage = 0;

	int x = cp->hd.where.t[0];
	int z = cp->hd.where.t[2];

	if (valid_region(x, z))
	{
		cp->ai.l.currentRoad = GetSurfaceIndex((VECTOR*)cp->hd.where.t);
	}
	else
	{
		DRIVER2_STRAIGHT* straight;
		DRIVER2_CURVE* curve;
		int i;
		int dx;
		int dz;
		int sqrdist;
		int min;

		min = -1;

		for (i = 0; i < NumDriver2Straights; i++)
		{
			straight = &Driver2StraightsPtr[i];

			dx = (x - straight->Midx) >> 10;
			dz = (z - straight->Midz) >> 10;

			sqrdist = dx * dx + dz * dz;

			if ((dx < 1001 && dz < 1001) && (sqrdist < min || min == -1))
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

			if ((dx < 1001 && dz < 1001) && (sqrdist < min || min == -1))
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



// decompiled code
// original method signature: 
// void /*$ra*/ LeadUpdateState(CAR_DATA *cp /*$s0*/)
 // line 382, offset 0x000e73e8
	/* begin block 1 */
		// Start line: 383
		// Start offset: 0x000E73E8
		// Variables:
	// 		int dif; // $t0
	// 		int avel; // $s1

		/* begin block 1.1 */
			// Start line: 399
			// Start offset: 0x000E7498
			// Variables:
		// 		VECTOR tmpStart; // stack offset -48
		/* end block 1.1 */
		// End offset: 0x000E74EC
		// End Line: 412

		/* begin block 1.2 */
			// Start line: 506
			// Start offset: 0x000E7768
			// Variables:
		// 		int dist; // $t1
		/* end block 1.2 */
		// End offset: 0x000E792C
		// End Line: 535

		/* begin block 1.3 */
			// Start line: 542
			// Start offset: 0x000E7938
			// Variables:
		// 		VECTOR pos; // stack offset -32
		/* end block 1.3 */
		// End offset: 0x000E7980
		// End Line: 557
	/* end block 1 */
	// End offset: 0x000E7980
	// End Line: 564

	/* begin block 2 */
		// Start line: 865
	/* end block 2 */
	// End Line: 866

	/* begin block 3 */
		// Start line: 870
	/* end block 3 */
	// End Line: 871

// [D] [T] - needless to say, the AI isn't very smart :D
void LeadUpdateState(CAR_DATA* cp)
{
	int dif;
	int avel;
	int end;
	int dist;
	int dx;
	int dz;
	VECTOR tmpStart;
	VECTOR pos;

	int x = cp->hd.where.t[0];
	int z = cp->hd.where.t[2];

	// is he spooled in?
	if (!valid_region(x, z)
		|| ABS(x - player[0].pos[0]) > 15900
		|| ABS(z - player[0].pos[2]) > 15900)
	{
		// request that we spool him in
		cp->ai.l.dstate = 8;
		return;
	}

	if (cp->ai.l.dstate == 8)
	{
		// don't spool him in until everything is loaded
		if (spoolactive)
			return;

		tmpStart.vx = x;
		tmpStart.vz = z;
		tmpStart.vy = MapHeight(&tmpStart) - cp->ap.carCos->wheelDisp[0].vy;

		InitCarPhysics(cp, (LONGVECTOR4*)&tmpStart, cp->ai.l.targetDir);

		// start him up
		cp->ai.l.dstate = 3;
	}

	if (ABS(cp->ai.l.panicCount) > 0)
		cp->ai.l.dstate = 5;

	if (cp->ai.l.dstate == 6)
		cp->ai.l.dstate = 3;

	if (cp->hd.speed < 10)
		++cp->ai.l.stuckCount;
	else
		cp->ai.l.stuckCount = 0;

	if (cp->ai.l.dstate == 4)
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
			cp->ai.l.dstate = 4;
		}
	}

	dif = cp->hd.direction - cp->ai.l.targetDir;
	avel = FIXEDH(cp->st.n.angularVelocity[1]);

	end = (dif + 2048u & 0xfff) - 2048;

	switch (cp->ai.l.dstate)
	{
		case 0:
			CheckCurrentRoad(cp);

			if (cp->hd.speed < 20)
				cp->ai.l.dstate = 3;

			if (ABS(end) < LeadValues.hEnd)
			{
				if (ABS(avel) > 150)
					cp->ai.l.dstate = 1;
			}

			break;
		case 1:
			CheckCurrentRoad(cp);

			if (ABS(end) < LeadValues.dEnd)
			{
				if (ABS(avel) < 24)
				{
					cp->ai.l.dstate = 3;
				}
				else
				{
					cp->ai.l.dstate = 2;
				}
			}

			break;
		case 2:
			CheckCurrentRoad(cp);

			if (ABS(avel) < 24)
				cp->ai.l.dstate = 3;

			break;
		case 3:
			if (cp->ai.l.recoverTime > 40)
				--cp->ai.l.recoverTime;

			CheckCurrentRoad(cp);

			dx = (cp->ai.l.targetX - x) * rcossin_tbl[(cp->hd.direction & 0xfff) * 2];
			dz = (cp->ai.l.targetZ - z) * rcossin_tbl[(cp->hd.direction & 0xfff) * 2 + 1];

			dist = FIXEDH(dx + dz);

			if (cp->hd.speed > 100 || (cp->hd.speed > 30 && ABS(end) > 1024))
			{
				if (ABS(end) > LeadValues.hEnd)
				{
					if (cp->hd.speed > 100)
					{
						int hDist = LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul;

						if (dist < hDist)
						{
							cp->ai.l.dstate = 6;
						}
						else
						{
							cp->ai.l.dstate = 0;
						}

						break;
					}
					else
					{
						int tDist = LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul;

						if (dist < tDist)
						{
							cp->ai.l.dstate = 0;
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

				if (dist < lDist)
					cp->ai.l.dstate = 7;
				else
					cp->ai.l.dstate = 6;
			}

			break;
		case 4:
			pos.vx = cp->hd.where.t[0];
			pos.vy = cp->hd.where.t[1];
			pos.vz = cp->hd.where.t[2];

			UpdateRoadPosition(cp, &pos, 5);

			cp->ai.l.recoverTime++;

			if (cp->ai.l.roadForward == 0)
			{
				cp->ai.l.dstate = 3;
				cp->ai.l.stuckCount = 0;
			}

			break;
		case 5:
			CheckCurrentRoad(cp);

			if (cp->ai.l.panicCount == 0)
			{
				if (ABS(end) < 200)
					cp->ai.l.dstate = 2;
			}

			break;
		case 7:
			CheckCurrentRoad(cp);

			if (ABS(end) < cp->hd.speed + LeadValues.tEnd)
				cp->ai.l.dstate = 2;

			break;
	}
}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ LeadPadResponse(CAR_DATA *cp /*$t0*/)
 // line 566, offset 0x000e7994
	/* begin block 1 */
		// Start line: 567
		// Start offset: 0x000E7994
		// Variables:
	// 		int dif; // $t2
	// 		int avel; // $t1
	// 		unsigned long t0; // $s0

		/* begin block 1.1 */
			// Start line: 600
			// Start offset: 0x000E7A4C
		/* end block 1.1 */
		// End offset: 0x000E7B18
		// End Line: 626

		/* begin block 1.2 */
			// Start line: 661
			// Start offset: 0x000E7BC8
			// Variables:
		// 		int deltaVel; // $a1
		// 		int deltaAVel; // $a3
		// 		int deltaPos; // $a0
		// 		int deltaTh; // $t2
		// 		int steerDelta; // $a0
		/* end block 1.2 */
		// End offset: 0x000E7D50
		// End Line: 688

		/* begin block 1.3 */
			// Start line: 694
			// Start offset: 0x000E7D58
			// Variables:
		// 		int diff; // $a0
		/* end block 1.3 */
		// End offset: 0x000E7DD4
		// End Line: 707
	/* end block 1 */
	// End offset: 0x000E7DE8
	// End Line: 715

	/* begin block 2 */
		// Start line: 1282
	/* end block 2 */
	// End Line: 1283

// [D] [T]
u_int LeadPadResponse(CAR_DATA* cp)
{
	int dif;
	int avel;
	u_int t0;
	int deltaVel;
	int deltaAVel;
	int deltaPos;
	int deltaTh;
	int steerDelta;
	int dx;
	int dz;
	int dist;
	int diff;
	int maxDist;

	t0 = 0;

	dif = cp->hd.direction - cp->ai.l.targetDir;

	deltaTh = (dif + 2048U & 0xfff) - 2048;
	avel = FIXEDH(cp->st.n.angularVelocity[1]);

#ifdef COLLISION_DEBUG
	extern int gShowCollisionDebug;
	//if (gShowCollisionDebug == 3)
	{
		extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
		extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

		CVECTOR ggcv = { 0, 250, 0 };
		CVECTOR bbcv = { 0, 0, 250 };
		CVECTOR rrcv = { 250, 0, 0 };

		VECTOR _zero = { 0 };
		VECTOR _up = { 0, 1000, 0 };

		VECTOR pos = { cp->ai.l.targetX, cp->hd.where.t[1], cp->ai.l.targetZ };

		Debug_AddLineOfs(_zero, _up, pos, rrcv);
	}
#endif

	switch (cp->ai.l.dstate)
	{
		case 0:
			// [A] check angular velocity when making this maneuver with handbrake
			deltaAVel = ABS(avel);
		
			t0 = (deltaAVel < 100 ? CAR_PAD_HANDBRAKE : 0) | ((deltaTh < 0) ? CAR_PAD_RIGHT : CAR_PAD_LEFT);
			break;
		case 1:
			t0 = CAR_PAD_ACCEL;
			break;
		case 2:
			t0 = CAR_PAD_ACCEL | ((avel < 0) ? CAR_PAD_RIGHT : CAR_PAD_LEFT);

			if (ABS(avel) > 40)
				t0 |= CAR_PAD_FASTSTEER;

			break;
		case 3:
			dx = -rcossin_tbl[(cp->ai.l.targetDir & 0xfff) * 2 + 1] * (cp->hd.where.t[0] - cp->ai.l.targetX);
			dz = rcossin_tbl[(cp->ai.l.targetDir & 0xfff) * 2] * (cp->hd.where.t[2] - cp->ai.l.targetZ);

			deltaPos = FIXEDH(dx + dz);

			maxDist = pathParams[4];

			if (deltaPos > maxDist || (maxDist = -maxDist, deltaPos < maxDist))
				deltaPos = maxDist;

			deltaVel = FIXEDH(
				-rcossin_tbl[(cp->ai.l.targetDir & 0xfff) * 2 + 1] * FIXEDH(cp->st.n.linearVelocity[0])
				+ rcossin_tbl[(cp->ai.l.targetDir & 0xfff) * 2] * FIXEDH(cp->st.n.linearVelocity[2]));

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
		
			if (steerDelta + 31U <= 62) 
			{
				if (ABS(avel) <= 5)
				{
					if (t0 & CAR_PAD_ACCEL)
						t0 |= CAR_PAD_WHEELSPIN;
				}
			}

			break;
		case 4:
			t0 = CAR_PAD_WHEELSPIN;

			diff = cp->ai.l.roadPosition - cp->hd.direction;

			deltaPos = (diff + 2048u & 0xfff) - 2048;

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
		case 5:
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
		case 6:
			t0 = (avel < 0) ? CAR_PAD_RIGHT : CAR_PAD_LEFT;

			if (cp->ai.l.roadForward < 0 && cp->hd.speed > 100)
				t0 |= CAR_PAD_BRAKE;
			else
				t0 |= CAR_PAD_ACCEL;

			break;
		case 7:
			if (ABS(avel) > LeadValues.tAvelLimit)
			{
				if (ABS(deltaTh) > 1024)
					t0 = CAR_PAD_FASTSTEER | ((deltaTh < 0) ? CAR_PAD_RIGHT : CAR_PAD_LEFT);
			}

			t0 |= CAR_PAD_WHEELSPIN;
			break;

		case 8:
			FakeMotion(cp);
			break;
	}

	return t0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FakeMotion(CAR_DATA *cp /*$s1*/)
 // line 718, offset 0x000e7de8
	/* begin block 1 */
		// Start line: 719
		// Start offset: 0x000E7DE8

		/* begin block 1.1 */
			// Start line: 724
			// Start offset: 0x000E7E40
			// Variables:
		// 		DRIVER2_STRAIGHT *straight; // $t1
		// 		static int d; // offset 0x0
		// 		static int toGo; // offset 0x4
		// 		static int angle; // offset 0x8
		// 		static int s; // offset 0xc
		// 		static int c; // offset 0x10
		// 		int dx; // $a2
		// 		int dz; // $t3
		// 		int nextJunction; // $t0

			/* begin block 1.1.1 */
				// Start line: 757
				// Start offset: 0x000E7FA4
				// Variables:
			// 		DRIVER2_JUNCTION *junction; // $s0
			/* end block 1.1.1 */
			// End offset: 0x000E7FA4
			// End Line: 757
		/* end block 1.1 */
		// End offset: 0x000E8010
		// End Line: 778

		/* begin block 1.2 */
			// Start line: 781
			// Start offset: 0x000E8010
			// Variables:
		// 		DRIVER2_CURVE *curve; // $s0
		// 		int angle; // $a3
		// 		int toGo; // $v0
		// 		int radius; // $a2
		// 		int dx; // $a0
		// 		int dz; // $a1
		// 		int nextJunction; // $a2

			/* begin block 1.2.1 */
				// Start line: 813
				// Start offset: 0x000E8104
				// Variables:
			// 		DRIVER2_JUNCTION *junction; // $s0
			/* end block 1.2.1 */
			// End offset: 0x000E8104
			// End Line: 813

			/* begin block 1.2.2 */
				// Start line: 848
				// Start offset: 0x000E81F0
				// Variables:
			// 		DRIVER2_JUNCTION *junction; // $s0
			/* end block 1.2.2 */
			// End offset: 0x000E81F0
			// End Line: 848
		/* end block 1.2 */
		// End offset: 0x000E82E0
		// End Line: 874

		/* begin block 1.3 */
			// Start line: 877
			// Start offset: 0x000E82E0
			// Variables:
		// 		DRIVER2_JUNCTION *junction; // $s0
		/* end block 1.3 */
		// End offset: 0x000E8338
		// End Line: 885
	/* end block 1 */
	// End offset: 0x000E8338
	// End Line: 888

	/* begin block 2 */
		// Start line: 1640
	/* end block 2 */
	// End Line: 1641

	/* begin block 3 */
		// Start line: 1644
	/* end block 3 */
	// End Line: 1645

// [D] [T]
// FakeMotion: when car is too far from the player it just moves, not drives
void FakeMotion(CAR_DATA* cp)
{
	static int d; // offset 0x0
	static int toGo; // offset 0x4
	static int angle; // offset 0x8
	static int s; // offset 0xc
	static int c; // offset 0x10

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

		c = rcossin_tbl[(angle & 0xfff) * 2];
		s = rcossin_tbl[(angle & 0xfff) * 2 + 1];

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
		int dx, dz;
		int radius;
		int dir;

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
			if (((curve->end - angle & 0xfff) + 2048 & 0xfff) - 2048 > -1) 
			{
				dir = angle + 0x13193 / radius;

				cp->ai.l.targetDir = (dir + 1024) & 0xfff;
				
				cp->hd.where.t[0] = FIXEDH(rcossin_tbl[(dir & 0xfff) * 2] * radius) + curve->Midx;
				cp->hd.where.t[2] = FIXEDH(rcossin_tbl[(dir & 0xfff) * 2 + 1] * radius) + curve->Midz;
				return;
			}

			nextJunction = curve->ConnectIdx[1];
			if (nextJunction == -1)
				nextJunction = curve->ConnectIdx[0];
		}
		else
		{
			if (((angle - curve->start & 0xfff) + 2048 & 0xfff) - 2048 > -1)
			{
				dir = angle - 0x13193 / radius;

				cp->ai.l.targetDir = (dir - 1024) & 0xfff;
				
				cp->hd.where.t[0] = FIXEDH(rcossin_tbl[(dir & 0xfff) * 2] * radius) + curve->Midx;
				cp->hd.where.t[2] = FIXEDH(rcossin_tbl[(dir & 0xfff) * 2 + 1] * radius) + curve->Midz;
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



// decompiled code
// original method signature: 
// void /*$ra*/ PosToIndex(int *normal /*$t1*/, int *tangent /*$t4*/, int intention /*$a2*/, CAR_DATA *cp /*$a3*/)
 // line 932, offset 0x000e834c
	/* begin block 1 */
		// Start line: 933
		// Start offset: 0x000E834C

		/* begin block 1.1 */
			// Start line: 950
			// Start offset: 0x000E8398
			// Variables:
		// 		int dist; // $a1
		/* end block 1.1 */
		// End offset: 0x000E8420
		// End Line: 958

		/* begin block 1.2 */
			// Start line: 970
			// Start offset: 0x000E84B0
			// Variables:
		// 		int w; // $t2
		// 		int w80; // $t0
		// 		int t; // $a1
		// 		int t80; // $a3

			/* begin block 1.2.1 */
				// Start line: 979
				// Start offset: 0x000E85F0
				// Variables:
			// 		int temp; // $v1
			/* end block 1.2.1 */
			// End offset: 0x000E85F0
			// End Line: 979

			/* begin block 1.2.2 */
				// Start line: 986
				// Start offset: 0x000E8614
				// Variables:
			// 		int temp; // $a0
			/* end block 1.2.2 */
			// End offset: 0x000E8614
			// End Line: 988

			/* begin block 1.2.3 */
				// Start line: 998
				// Start offset: 0x000E865C
			/* end block 1.2.3 */
			// End offset: 0x000E8690
			// End Line: 1002
		/* end block 1.2 */
		// End offset: 0x000E86B4
		// End Line: 1045
	/* end block 1 */
	// End offset: 0x000E86B4
	// End Line: 1048

	/* begin block 2 */
		// Start line: 2158
	/* end block 2 */
	// End Line: 2159

// [D] [T]
void PosToIndex(int* normal, int* tangent, int intention, CAR_DATA* cp)
{
	int w;
	int w80;
	int t;
	int t80;
	int dist;

	if (intention - 4U < 3)
	{ 
		*normal = (*normal + 2048U & 0xfff) - 2048;

		if (intention == 6)
		{
			if (ABS(*normal) < 240)
			{
				dist = FIXEDH(*tangent * rcossin_tbl[(*normal & 0xfff) * 2]);
				
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
			int myspeed;
			
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
				t = LeadValues.hDist + (myspeed + -100) * LeadValues.hDistMul;
			else
				t = LeadValues.tDist + myspeed * LeadValues.tDistMul;

			t80 = (t << 3) / 10;

			if (intention == 2)
				*normal = -*normal;

			if (w < *normal)
			{
				int temp;
				temp = *tangent;
				
				*tangent = (t + *normal) - w;
				*normal = t - temp;
			}
			else if (w80 < *normal)
			{
				int temp;
				temp = ((*normal - w80) * (t - t80)) / (w - w80) + t80;
				
				*normal = temp - *tangent;
				*tangent = temp;
			}
			else if (*normal > 0)
			{
				int temp;
				temp = (t80 * w80) / *normal;

				*normal = temp - *tangent;
				*tangent = temp;
			}
		}

		t80 = *normal / 100;
	}

	*normal = t80 + 21;
}



// decompiled code
// original method signature: 
// void /*$ra*/ BlockToMap(MAP_DATA *data /*$s3*/)
 // line 1053, offset 0x000e86bc
	/* begin block 1 */
		// Start line: 1054
		// Start offset: 0x000E86BC
		// Variables:
	// 		static int carLength; // offset 0x14
	// 		static int carWidth; // offset 0x18
	// 		static int length; // offset 0x14
	// 		static int width; // offset 0x18
	// 		static int left; // offset 0x1c
	// 		static int right; // offset 0x20
	// 		static int ldist; // offset 0x24
	// 		static int rdist; // offset 0x28
	// 		static MAP_DATA newdata; // offset 0x30

		/* begin block 1.1 */
			// Start line: 1074
			// Start offset: 0x000E873C
			// Variables:
		// 		int dx; // $t4
		// 		int dz; // $t3
		// 		int v; // $v1
		// 		int tangent; // $s0
		// 		int normal; // $s1
		/* end block 1.1 */
		// End offset: 0x000E8AB0
		// End Line: 1161

		/* begin block 1.2 */
			// Start line: 1166
			// Start offset: 0x000E8AB0
			// Variables:
		// 		DRIVER2_CURVE *curve; // $s1
		// 		int dx; // $s6
		// 		int dz; // $s5
		// 		int v; // $a0
		// 		int angle; // $a2
		// 		int s; // $s4
		// 		int c; // $s2
		// 		int tangent; // $s0
		// 		int normal; // $s1
		/* end block 1.2 */
		// End offset: 0x000E8E48
		// End Line: 1264

		/* begin block 1.3 */
			// Start line: 1271
			// Start offset: 0x000E8E48
			// Variables:
		// 		int dx; // $s0
		// 		int dz; // $s2
		// 		int angle; // $s5
		// 		int s; // $t3
		// 		int c; // $t2
		// 		int tangent; // $s1
		// 		int normal; // $s0
		// 		int i; // $s2

			/* begin block 1.3.1 */
				// Start line: 1301
				// Start offset: 0x000E8F7C
				// Variables:
			// 		int corners[4][3]; // stack offset -112
			// 		int diff; // $v0
			// 		int overlap; // $s1
			// 		int quad1; // $a1
			// 		int quad2; // $v1

				/* begin block 1.3.1.1 */
					// Start line: 1350
					// Start offset: 0x000E9184
					// Variables:
				// 		int temp; // $v1
				/* end block 1.3.1.1 */
				// End offset: 0x000E91B0
				// End Line: 1354

				/* begin block 1.3.1.2 */
					// Start line: 1363
					// Start offset: 0x000E921C
					// Variables:
				// 		int vx; // $a1
				// 		int vz; // $t0
				// 		int theta; // $v0
				/* end block 1.3.1.2 */
				// End offset: 0x000E9324
				// End Line: 1381
			/* end block 1.3.1 */
			// End offset: 0x000E9324
			// End Line: 1382

			/* begin block 1.3.2 */
				// Start line: 1387
				// Start offset: 0x000E9350
				// Variables:
			// 		int temp; // $a0
			/* end block 1.3.2 */
			// End offset: 0x000E93F0
			// End Line: 1407
		/* end block 1.3 */
		// End offset: 0x000E93F0
		// End Line: 1411

		/* begin block 1.4 */
			// Start line: 1425
			// Start offset: 0x000E9424
			// Variables:
		// 		int *nearest; // $s2
		// 		int *furthest; // $s4
		// 		int *ndist; // $s1
		// 		int *fdist; // $s0

			/* begin block 1.4.1 */
				// Start line: 1443
				// Start offset: 0x000E94A4
				// Variables:
			// 		int temp; // stack offset -64
			// 		int tdist; // stack offset -60
			/* end block 1.4.1 */
			// End offset: 0x000E9560
			// End Line: 1467
		/* end block 1.4 */
		// End offset: 0x000E9560
		// End Line: 1468

		/* begin block 1.5 */
			// Start line: 1482
			// Start offset: 0x000E95A0
			// Variables:
		// 		int locall; // stack offset -56
		// 		int localr; // stack offset -48
		// 		int localld; // stack offset -52
		// 		int localrd; // stack offset -44

			/* begin block 1.5.1 */
				// Start line: 1492
				// Start offset: 0x000E9614
				// Variables:
			// 		int i; // $a2
			/* end block 1.5.1 */
			// End offset: 0x000E9664
			// End Line: 1499

			/* begin block 1.5.2 */
				// Start line: 1499
				// Start offset: 0x000E9664
				// Variables:
			// 		int i; // $a0
			/* end block 1.5.2 */
			// End offset: 0x000E96EC
			// End Line: 1512
		/* end block 1.5 */
		// End offset: 0x000E96EC
		// End Line: 1513

		/* begin block 1.6 */
			// Start line: 1522
			// Start offset: 0x000E9734
			// Variables:
		// 		int tangent; // $a2
		// 		int i; // $a1
		/* end block 1.6 */
		// End offset: 0x000E97B0
		// End Line: 1533

		/* begin block 1.7 */
			// Start line: 1546
			// Start offset: 0x000E97B0
			// Variables:
		// 		int dtan; // $a3
		// 		int tangent; // $a2
		// 		int i; // $a1
		/* end block 1.7 */
		// End offset: 0x000E9874
		// End Line: 1558
	/* end block 1 */
	// End offset: 0x000E9874
	// End Line: 1560

	/* begin block 2 */
		// Start line: 2406
	/* end block 2 */
	// End Line: 2407

/* WARNING: Type propagation algorithm not settling */

// [D] [T] - seems to be working as expected
void BlockToMap(MAP_DATA* data)
{
	static int carLength; // offset 0x14
	static int carWidth; // offset 0x18
	static int length; // offset 0x14
	static int width; // offset 0x18
	static int left; // offset 0x1c
	static int right; // offset 0x20
	static int ldist; // offset 0x24
	static int rdist; // offset 0x28
	static MAP_DATA newdata; // offset 0x30

	static int someVar;
	static int offx;

	bool overlap;

	DRIVER2_CURVE* curve;

	int x;
	int y;

	int* ndist;
	int* fdist;
	int* nearest;
	int* furthest;

	int corners[4][3];
	int temp;
	int tdist;
	int locall;
	int localld;
	int localr;
	int localrd;

	int dx;
	int dy;
	int dz;
	int v;
	int angle;
	int s;
	int c;
	int tangent;
	int normal;

	CAR_COSMETICS* pCarCos = data->cp->ap.carCos;

	carLength = pCarCos->colBox.vz;
	carWidth = pCarCos->colBox.vx;

	switch (data->intention)
	{
		case 0:
		case 2:
		case 3:
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

			if (data->intention == 0 || data->cp->ai.l.dstate == 3)
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
		case 1:
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

			s = rcossin_tbl[((tangent + 1024u) & 0xfff) * 2];
			c = rcossin_tbl[((tangent + 1024u) & 0xfff) * 2 + 1];

			tangent = (((tangent - data->cp->ai.l.base_Angle) + 2048u & 0xfff) - 2048) *
				data->cp->ai.l.base_Dir * ((curve->inside * 0xb000) / 0x7000);

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
		case 4:
		case 5:
		case 6:
			dx = data->pos->vx - data->base->vx;
			dy = data->base->vy - data->pos->vy;
			dz = data->pos->vz - data->base->vz;

			if (dy < 1)
				v = pCarCos->colBox.vy;
			else
				v = data->size->vy;

			if (dy > v)
				return;

			angle = (ratan2(dx, dz) + 2048u & 0xfff) - 2048;

			s = rcossin_tbl[(angle & 0xfff) * 2];
			c = rcossin_tbl[(angle & 0xfff) * 2 + 1];

			someVar = FIXEDH(ABS(data->size->vx * s) + ABS(data->size->vz * c));

			tangent = (hypot(dx, dz) - someVar) - carLength;

			if (tangent < 2000 || data->intention == 6)
			{
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

				overlap = false;

				left = 0;
				right = 0;

				int quad1 = corners[0][2] + 2048 >> 10;
				//fdist = corners + 5;	// corners[1][2] = 5

				for (int i = 1; i < 4; i++)
				{
					y = corners[i][2];

					if (0 < (int)(((corners[left][2] - y) + 2048u & 0xfff) - 2048))
						left = i;

					if (0 < (int)(((y - corners[right][2]) + 2048u & 0xfff) - 2048))
						right = i;

					int quad2 = y + 2048 >> 10;

					if ((quad1 != quad2) && (quad1 + (quad1 - (corners[0][2] + 2048 >> 0x1f) >> 1) * -2 == quad2 + (quad2 - (y + 2048 >> 0x1f) >> 1) * -2))
						overlap = true;

					//fdist = fdist + 3;
				};

				if (overlap)
				{
					temp = angle - data->cp->hd.direction;

					left = temp - 512;
					right = temp + 512;

					rdist = 0;
				}
				else if (left + right == 3)
				{
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

					left = corners[left][2] - data->cp->hd.direction;
					right = corners[right][2] - data->cp->hd.direction;

					rdist = tangent;
				}
				else
				{
					dx = corners[left][1] - corners[right][1];
					dy = corners[left][0] - corners[right][0];

					int theta = (ratan2(dy, dx) + 3072u & 0xfff) - 2048;

					int vx = rcossin_tbl[(theta & 0xfff) * 2] * corners[left][0];
					int vz = rcossin_tbl[(theta & 0xfff) * 2 + 1] * corners[left][1];

					left = corners[left][2] - data->cp->hd.direction;
					right = corners[right][2] - data->cp->hd.direction;

					rdist = ABS(FIXEDH(vx + vz));
				}

				left = (left + 2048u & 0xfff) - 2048;
				right = (right + 2048u & 0xfff) - 2048;
			}
			else
			{
				normal = ((angle - data->cp->hd.direction) + 2048 & 0xfff) - 2048;

				offx = ratan2(FIXEDH(ABS(data->size->vx * c) + ABS(data->size->vz * s)) + carWidth, tangent);

				left = normal - offx;
				right = normal + offx;

				rdist = tangent;
			}

			ldist = rdist;
			break;
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
		case 5:
		case 6:
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



// decompiled code
// original method signature: 
// int /*$ra*/ IsOnMap(int x /*$t0*/, int z /*$a1*/, VECTOR *basePos /*$a2*/, int intention /*$s4*/, CAR_DATA *cp /*stack 16*/)
 // line 1563, offset 0x000e98a4
	/* begin block 1 */
		// Start line: 1564
		// Start offset: 0x000E98A4
		// Variables:
	// 		int dx; // $s1
	// 		int dz; // $s2

		/* begin block 1.1 */
			// Start line: 1577
			// Start offset: 0x000E9938
			// Variables:
		// 		int tangent; // stack offset -44
		// 		int normal; // stack offset -48
		/* end block 1.1 */
		// End offset: 0x000E99F4
		// End Line: 1591

		/* begin block 1.2 */
			// Start line: 1596
			// Start offset: 0x000E99F4
			// Variables:
		// 		DRIVER2_CURVE *curve; // $s0
		// 		int tangent; // stack offset -36
		// 		int normal; // stack offset -40
		/* end block 1.2 */
		// End offset: 0x000E9B20
		// End Line: 1622

		/* begin block 1.3 */
			// Start line: 1628
			// Start offset: 0x000E9B20
			// Variables:
		// 		int tangent; // stack offset -28
		// 		int normal; // stack offset -32
		/* end block 1.3 */
		// End offset: 0x000E9B94
		// End Line: 1642
	/* end block 1 */
	// End offset: 0x000E9BB8
	// End Line: 1650

	/* begin block 2 */
		// Start line: 3728
	/* end block 2 */
	// End Line: 3729

	/* begin block 3 */
		// Start line: 3729
	/* end block 3 */
	// End Line: 3730

/* WARNING: Type propagation algorithm not settling */

// [D] [T]
int IsOnMap(int x, int z, VECTOR* basePos, int intention, CAR_DATA* cp)
{
	DRIVER2_CURVE* curve;
	int dx;
	int dz;
	int normal;
	int tangent;

	dx = ABS(x - basePos->vx);
	dz = ABS(z - basePos->vz);

	if (dz < 3000)
		return 1;

	switch (intention)
	{
		case 0:
		case 2:
		case 3:
			tangent = FIXEDH(dx * road_s + dz * road_c);
			normal = FIXEDH(dx * road_c - dz * road_s);

			PosToIndex(&normal, &tangent, intention, cp);
			break;
		case 1:
			curve = GET_CURVE(cp->ai.l.currentRoad);

			dx = x - curve->Midx;
			dz = z - curve->Midz;

			tangent = (((ratan2(dx, dz) - cp->ai.l.base_Angle) + 2048u & 0xfff) - 2048) * cp->ai.l.base_Dir * ((curve->inside * 0xb000) / 0x7000);
			normal = (cp->ai.l.base_Normal - hypot(dx, dz)) * cp->ai.l.base_Dir;

			PosToIndex(&normal, &tangent, intention, cp);
			break;
		case 4:
		case 5:
			tangent = hypot(dx, dz);
			normal = ((ratan2(dx, dz) - cp->hd.direction) + 2048u & 0xfff) - 2048;

			PosToIndex(&normal, &tangent, intention, cp);

			if (tangent > 7000)
				return 0;

			if (normal > -1 && normal < 42)
				return 1;
		default:
			return 0;
	}

	if ((tangent + 2048) > 0x5800)
		return 0;

	if (normal < -4)
		return 0;

	if (normal <= 45)
		return 1;

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateRoadPosition(CAR_DATA *cp /*$s3*/, VECTOR *basePos /*stack 4*/, int intention /*stack 8*/)
 // line 1657, offset 0x000e9bb8
	/* begin block 1 */
		// Start line: 1658
		// Start offset: 0x000E9BB8
		// Variables:
	// 		int sindex; // $t0
	// 		int i; // $s0
	// 		int di; // $a2
	// 		CAR_DATA *lcp; // $s0
	// 		int laneAvoid; // stack offset -56

		/* begin block 1.1 */
			// Start line: 1680
			// Start offset: 0x000E9C4C
			// Variables:
		// 		int cell_x; // $s4
		// 		int x1; // $a0

			/* begin block 1.1.1 */
				// Start line: 1693
				// Start offset: 0x000E9CB0
				// Variables:
			// 		int cell_z; // $s0
			// 		int z1; // $s1

				/* begin block 1.1.1.1 */
					// Start line: 1700
					// Start offset: 0x000E9CFC
					// Variables:
				// 		int cbrx; // $a3
				// 		int cbrz; // $a2
				// 		int cbr; // $a0

					/* begin block 1.1.1.1.1 */
						// Start line: 1714
						// Start offset: 0x000E9D94
						// Variables:
					// 		CELL_OBJECT *cop; // $s1
					// 		CELL_ITERATOR ci; // stack offset -344

						/* begin block 1.1.1.1.1.1 */
							// Start line: 1721
							// Start offset: 0x000E9DB0
							// Variables:
						// 		COLLISION_PACKET *collide; // $s0
						// 		MODEL *model; // $a0
						// 		int num_cb; // $a0
						// 		int box_loop; // $s2

							/* begin block 1.1.1.1.1.1.1 */
								// Start line: 1739
								// Start offset: 0x000E9E4C
								// Variables:
							// 		MATRIX *mat; // $a1
							// 		VECTOR offset; // stack offset -320
							// 		VECTOR vel; // stack offset -304
							// 		VECTOR size; // stack offset -288
							// 		MAP_DATA data; // stack offset -272

								/* begin block 1.1.1.1.1.1.1.1 */
									// Start line: 1753
									// Start offset: 0x000E9EF8
									// Variables:
								// 		int sb; // $t0
								// 		int cb; // $a1
								// 		int theta; // $v1
								// 		int xsize; // $a0
								// 		int zsize; // $a3
								/* end block 1.1.1.1.1.1.1.1 */
								// End offset: 0x000E9FD8
								// End Line: 1767
							/* end block 1.1.1.1.1.1.1 */
							// End offset: 0x000E9FD8
							// End Line: 1775
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x000EA068
						// End Line: 1795
					/* end block 1.1.1.1.1 */
					// End offset: 0x000EA088
					// End Line: 1797
				/* end block 1.1.1.1 */
				// End offset: 0x000EA088
				// End Line: 1798
			/* end block 1.1.1 */
			// End offset: 0x000EA098
			// End Line: 1799
		/* end block 1.1 */
		// End offset: 0x000EA0AC
		// End Line: 1800

		/* begin block 1.2 */
			// Start line: 1814
			// Start offset: 0x000EA0CC
			// Variables:
		// 		SVECTOR *colBox; // $a3
		// 		VECTOR pos; // stack offset -344
		// 		VECTOR vel; // stack offset -328
		// 		VECTOR size; // stack offset -312
		// 		MAP_DATA data; // stack offset -296
		/* end block 1.2 */
		// End offset: 0x000EA260
		// End Line: 1845

		/* begin block 1.3 */
			// Start line: 1860
			// Start offset: 0x000EA2F4
			// Variables:
		// 		int left; // $a3
		// 		int right; // $a2
		/* end block 1.3 */
		// End offset: 0x000EA3D8
		// End Line: 1889

		/* begin block 1.4 */
			// Start line: 1904
			// Start offset: 0x000EA410
			// Variables:
		// 		int smallest; // $s1
		/* end block 1.4 */
		// End offset: 0x000EA4E0
		// End Line: 1923

		/* begin block 1.5 */
			// Start line: 1931
			// Start offset: 0x000EA4EC
			// Variables:
		// 		int tmpMap[41]; // stack offset -240

			/* begin block 1.5.1 */
				// Start line: 1937
				// Start offset: 0x000EA528
				// Variables:
			// 		int count; // $t0
			// 		int j; // $a1
			/* end block 1.5.1 */
			// End offset: 0x000EA594
			// End Line: 1944
		/* end block 1.5 */
		// End offset: 0x000EA5C4
		// End Line: 1946

		/* begin block 1.6 */
			// Start line: 2006
			// Start offset: 0x000EA8AC
			// Variables:
		// 		int i; // stack offset -68
		// 		int penalty; // $a2
		// 		int left; // stack offset -72
		// 		int right; // stack offset -64
		// 		int centre; // stack offset -60
		/* end block 1.6 */
		// End offset: 0x000EAAA0
		// End Line: 2046

		/* begin block 1.7 */
			// Start line: 2069
			// Start offset: 0x000EAD80
			// Variables:
		// 		int biggest; // $a3

			/* begin block 1.7.1 */
				// Start line: 2090
				// Start offset: 0x000EAEAC
			/* end block 1.7.1 */
			// End offset: 0x000EAEAC
			// End Line: 2090
		/* end block 1.7 */
		// End offset: 0x000EAEE0
		// End Line: 2099

		/* begin block 1.8 */
			// Start line: 2103
			// Start offset: 0x000EAEE0
			// Variables:
		// 		int biggest; // $a1
		/* end block 1.8 */
		// End offset: 0x000EAF4C
		// End Line: 2113

		/* begin block 1.9 */
			// Start line: 2134
			// Start offset: 0x000EAFFC
			// Variables:
		// 		int smallForward; // $a1
		// 		int smallBack; // $v0
		/* end block 1.9 */
		// End offset: 0x000EB060
		// End Line: 2151

		/* begin block 1.10 */
			// Start line: 2226
			// Start offset: 0x000EB0C4
			// Variables:
		// 		CAR_DATA *cp; // $s3
		// 		int sindex; // $a0
		// 		int intention; // stack offset 8
		/* end block 1.10 */
		// End offset: 0x000EB1CC
		// End Line: 2226
	/* end block 1 */
	// End offset: 0x000EB1CC
	// End Line: 2239

	/* begin block 2 */
		// Start line: 3935
	/* end block 2 */
	// End Line: 3936

	/* begin block 3 */
		// Start line: 3943
	/* end block 3 */
	// End Line: 3944

int roadAhead[41]; // offset 0x000ecde8
int localMap[41]; // offset 0x000ecd40

// [D] [A] overlapping stack variables - might be incorrect (i've tried to resolve them so far)
void UpdateRoadPosition(CAR_DATA* cp, VECTOR* basePos, int intention)
{
	short* psVar1;
	short* psVar2;
	bool bVar3;
	int cellx;
	PACKED_CELL_OBJECT* ppco;
	CELL_OBJECT* cop;
	long lVar4;
	int local_v0_4816;
	int* piVar5;
	int uVar6;
	int* piVar7;
	MODEL* model;
	int iVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int cellz;
	CAR_COSMETICS* car_cos;
	int iVar13;
	int iVar14;
	int iVar15;
	int iVar16;
	COLLISION_PACKET* collide;
	CAR_DATA* lcp;
	int uVar17;
	VECTOR offset;
	VECTOR pos;
	VECTOR vel;
	VECTOR size;
	MAP_DATA data;
	int tmpMap[41];
	int left;
	int i;
	int right;
	int centre;
	int laneAvoid;
	CELL_ITERATOR ci;

	iVar16 = 40;
	laneAvoid = -1;
	piVar7 = roadAhead + 0x28;

	do {
		*piVar7 = 0x5000;
		iVar16 = iVar16 + -1;
		piVar7 = piVar7 + -1;
	} while (-1 < iVar16);

	piVar7 = localMap;
	iVar16 = 0x28;

	do {
		iVar16 = iVar16 + -1;
		*piVar7 = ((cp->hd).speed + 100) * 10;
		piVar7 = piVar7 + 1;
	} while (-1 < iVar16);

	cellx = (uint)(ushort)cp->ai.l.targetDir & 0xfff;
	road_s = (int)rcossin_tbl[cellx * 2];
	iVar16 = basePos->vx + units_across_halved;
	iVar13 = iVar16 + -0x400;
	road_c = (int)rcossin_tbl[cellx * 2 + 1];

	ClearCopUsage();
	iVar16 = 0;
	cellx = (iVar13 >> 0xb) - 5;

	do {
		iVar13 = basePos->vz + units_down_halved;
		iVar11 = iVar13 + -0x400;

		iVar13 = 0;
		iVar16 = iVar16 + 1;
		cellz = (iVar11 >> 0xb) - 5;

		do {
			iVar11 = IsOnMap((cellx * 0x800 - units_across_halved) + 0x400, (cellz * 0x800 - units_down_halved) + 0x400, basePos, intention, cp);
			iVar13 = iVar13 + 1;

			if (iVar11 != 0)
			{
				iVar11 = cells_across;

				if (RoadMapRegions[(cellx >> 5 & 1) + (cellz >> 5 & 1) * 2] == (cellx >> 5) + (cellz >> 5) * (iVar11 >> 5))
				{
					ppco = GetFirstPackedCop(cellx, cellz, &ci, 1);

					while (cop = UnpackCellObject(ppco, &ci.nearCell), cop != NULL)
					{
						model = modelpointers[cop->type];
						if ((((model->num_vertices - 3 < 300) && (model->num_point_normals < 300)) &&
							(model->num_polys < 300)) &&
							((piVar7 = (int*)model->collision_block, piVar7 != NULL &&
								((model->flags2 & 0x800) == 0))))
						{
							iVar11 = *piVar7;
							collide = (COLLISION_PACKET*)(piVar7 + 1);
							if (0 < iVar11) {
								do {
									uVar6 = -cop->yang & 0x3f;

									if (collide->type == 0)
									{
										iVar9 = collide->zsize << 0x10;
										uVar17 = (cop->yang + collide->yang) * 0x100 & 0x3f00;
										iVar15 = (int)*(short*)((int)rcossin_tbl + uVar17);
										iVar14 = (iVar9 >> 0x10) - (iVar9 >> 0x1f) >> 1;
										iVar9 = iVar14 * iVar15;
										iVar12 = (int)*(short*)((int)rcossin_tbl + uVar17 + 2);
										iVar10 = collide->xsize << 0x10;
										iVar8 = (iVar10 >> 0x10) - (iVar10 >> 0x1f) >> 1;
										iVar10 = iVar8 * iVar12;
										iVar14 = iVar14 * iVar12;
										iVar8 = iVar8 * iVar15;

										if (iVar9 < 0)
											iVar9 = -iVar9;

										if (iVar10 < 0)
											iVar10 = -iVar10;

										size.vx = FIXEDH(iVar9 + iVar10);
										size.vy = (long)collide->ysize;

										if (iVar14 < 0)
											iVar14 = -iVar14;

										if (iVar8 < 0)
											iVar8 = -iVar8;

										size.vz = FIXEDH(iVar14 - iVar8);
									}
									offset.vx = FIXEDH(collide->xpos * matrixtable[uVar6].m[0][0] + collide->zpos * matrixtable[uVar6].m[2][0]) + (cop->pos).vx;
									offset.vz = FIXEDH(collide->xpos * matrixtable[uVar6].m[0][2] + collide->zpos * matrixtable[uVar6].m[2][2]) + (cop->pos).vz;
									offset.vy = -(cop->pos).vy - (cop->pos).vy;

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

									iVar11--;
									collide++;
								} while (iVar11 != 0);
							}
						}
						ppco = GetNextPackedCop(&ci);
					}
				}
			}
			cellz = cellz + 1;
		} while (iVar13 < 0xb);

		cellx = cellx + 1;

	} while (iVar16 < 11);

	lcp = &car_data[MAX_CARS - 1];

	while (car_data < lcp)
	{
		if ((lcp != cp) && (lcp->controlType != CONTROL_TYPE_NONE))
		{
			car_cos = (lcp->ap).carCos;
			iVar16 = (uint)(ushort)(car_cos->colBox).vz << 0x10;
			iVar16 = (int)(lcp->hd).where.m[2][0] * ((iVar16 >> 0x10) - (iVar16 >> 0x1f) >> 1);
			iVar13 = (uint)(ushort)(car_cos->colBox).vx << 0x10;
			iVar13 = (int)(lcp->hd).where.m[0][0] * ((iVar13 >> 0x10) - (iVar13 >> 0x1f) >> 1);

			if (iVar16 < 0)
				iVar16 = -iVar16;

			if (iVar13 < 0)
				iVar13 = -iVar13;

			size.vx = FIXEDH(iVar16 + iVar13) + (int)(car_cos->colBox).vy;
			size.vy = (long)(car_cos->colBox).vy;
			iVar16 = (uint)(ushort)(car_cos->colBox).vz << 0x10;
			iVar16 = (int)(lcp->hd).where.m[2][2] * ((iVar16 >> 0x10) - (iVar16 >> 0x1f) >> 1);
			iVar13 = (uint)(ushort)(car_cos->colBox).vx << 0x10;
			iVar13 = (int)(lcp->hd).where.m[0][2] * ((iVar13 >> 0x10) - (iVar13 >> 0x1f) >> 1);
			iVar11 = (cp->st).n.linearVelocity[0];
			pos.vx = (lcp->hd).where.t[0];
			pos.vy = (lcp->hd).where.t[1];
			pos.vz = (lcp->hd).where.t[2];

			if (iVar16 < 0)
				iVar16 = -iVar16;

			if (iVar13 < 0)
				iVar13 = -iVar13;

			size.vz = FIXEDH(iVar16 + iVar13) + (int)(car_cos->colBox).vy;

			iVar16 = (cp->st).n.linearVelocity[2];
			vel.vx = iVar11 >> 10;

			vel.vz = iVar16 >> 10;
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

	if (cp->ai.l.dstate != 4 && 
		(localMap[20] < (cp->hd.speed + 100) * 8 || 
		 localMap[21] < (cp->hd.speed + 100) * 8 || 
		 localMap[22] < (cp->hd.speed + 100) * 8))
	{
		iVar16 = 1;
		piVar7 = localMap + 23;
		piVar5 = localMap + 19;

		while (true)
		{
			iVar11 = *piVar5 + localMap[21 - iVar16] + localMap[22 - iVar16];
			iVar13 = piVar7[-2] + piVar7[-1] + *piVar7;

			if (iVar11 < iVar13 && (cp->hd.speed + 100) * 24 < iVar13 * 2)
			{
				if (iVar16 > 13)
				{
					cp->ai.l.panicCount = 2;
					return;
				}

				cp->ai.l.panicCount = 1;
				return;
			}

			if (iVar11 > iVar13 && (cp->hd.speed + 100) * 24 < iVar11 * 2)
				break;

			if (iVar16 == 20)
			{
				if (iVar11 > iVar13)
					cp->ai.l.panicCount = -2;
				else
					cp->ai.l.panicCount = 2;
			}

			piVar7 = piVar7 + 1;
			iVar16 = iVar16 + 1;
			piVar5 = piVar5 + -1;

			if (iVar16 > 20)
				return;
		}

		if (iVar16 > 13)
			cp->ai.l.panicCount = -2;
		else
			cp->ai.l.panicCount = -1;
	
		return;
	}

	cp->ai.l.panicCount = 0;

	if (intention < 2)
	{
		
		piVar7 = roadAhead + 24;
		iVar16 = roadAhead[24];

		i = 24;
		do {
			if (*piVar7 < iVar16)
				iVar16 = *piVar7;

			lVar4 = SquareRoot0(i - 21);

			if (iVar16 < (cp->hd.speed + 100) * lVar4)
				*piVar7 = 0;

			i++;
			piVar7++;
		} while (i < 41);

		
		piVar7 = roadAhead + 18;
		iVar16 = roadAhead[18];

		i = 18;
		do {
			if (*piVar7 < iVar16)
				iVar16 = *piVar7;

			lVar4 = SquareRoot0(21 - i);

			if (iVar16 < (cp->hd.speed + 100) * lVar4)
				*piVar7 = 0;

			i--;
			piVar7--;
		} while (i > -1);
	}

	if (intention - 2U < 2)
	{
		piVar5 = roadAhead;
		iVar16 = 40;
		piVar7 = tmpMap;

		do {
			iVar13 = *piVar5;
			piVar5 = piVar5 + 1;
			iVar16 = iVar16 + -1;
			*piVar7 = iVar13;
			piVar7 = piVar7 + 1;
		} while (-1 < iVar16);

		iVar16 = 0;

		do {
			iVar13 = 0;
			roadAhead[iVar16] = 0;
			cellz = iVar16 - 3;
			iVar11 = iVar16 + 1;

			if (cellz < iVar16 + 4)
			{
				piVar7 = tmpMap + cellz;
				do {
					if (cellz < 41)
					{
						roadAhead[iVar16] = roadAhead[iVar16] + *piVar7;
					}
					piVar7++;
					cellz++;
					iVar13++;
				} while (cellz < iVar16 + 4);
			}

			roadAhead[iVar16] = roadAhead[iVar16] / iVar13;
			iVar16 = iVar11;
		} while (iVar11 < 41);
	}

	if (intention == 4)
	{
		iVar11 = 0;
		iVar13 = 63;
		iVar16 = -21;
		piVar7 = roadAhead;
		do {
			iVar9 = *piVar7 * 21;
			*piVar7 = iVar9;

			if (iVar11 - 21 < 0)
				*piVar7 = iVar9 / iVar13;
			else
				*piVar7 = iVar9 / iVar16;

			iVar13 -= 2;
			iVar16 += 2;
			iVar11++;
			piVar7++;
		} while (iVar11 < 41);
	}

	if (intention < 2 && cp->ai.l.nextTurn < 10)
	{
		iVar16 = cp->ai.l.boringness;

		if (iVar16 < 31)
		{
			iVar9 = cp->ai.l.width;
			iVar11 = cp->ai.l.roadPosition;
			iVar10 = iVar9 - cp->ai.l.d;

			if (ABS(iVar11 - iVar10) < iVar9 / 3 && iVar16 < 31)
				cp->ai.l.boringness = iVar16 + 1;

		}
		else
		{
			iVar11 = cp->ai.l.width;
			iVar13 = cp->ai.l.roadPosition;
			iVar9 = iVar11 - cp->ai.l.d;

			if (ABS(iVar13 - iVar9) < iVar11 / 3)
			{
				cp->ai.l.avoid = cp->ai.l.width - cp->ai.l.d;
				cp->ai.l.boringness = cp->ai.l.boringness + 1;
			}

			iVar11 = 0;
			piVar7 = roadAhead;
			laneAvoid = (cp->ai.l.avoid + cp->ai.l.d - cp->ai.l.width) / 100 + 21;
			
			iVar13 = laneAvoid * 100;
			iVar16 = laneAvoid * -100;

			do {
				iVar9 = iVar16;

				if (laneAvoid - iVar11 > -1)
					iVar9 = iVar13;

				if (iVar9 < cp->ai.l.width / 3)
					*piVar7 = *piVar7 + cp->ai.l.boringness * -100;

				piVar7++;
				iVar16 += 100;
				iVar11++;
				iVar13 -= 100;
			} while (iVar11 < 41);

			iVar9 = cp->ai.l.width;
			iVar16 = iVar9 / 3;
			iVar11 = cp->ai.l.avoid;
			iVar9 = iVar9 - cp->ai.l.d;
			
			if (ABS(iVar9 - iVar11) > iVar16)
			{
				cp->ai.l.boringness = 0;
			}
		}
	}
	else
	{
		cp->ai.l.boringness = 0;
	}

	if (intention - 4U > 1)
	{
		centre = cp->ai.l.d;
		right = cp->ai.l.width;
		
		left = centre - right;
		right = right + centre;

		i = 0;
		PosToIndex(&left, &i, intention, cp);
		PosToIndex(&right, &i, intention, cp);
		PosToIndex(&centre, &i, intention, cp);

		if (left < centre && centre < right)
		{
			if (intention - 2U > 1 && (cp->ai.l.nextTurn == 15 || cp->ai.l.nextTurn == 17))
			{
				cp->ai.l.nextTurn -= 16;
				
				i = left;
				while (i <= right)
				{
					if ((i - centre) * cp->ai.l.nextTurn > 0)
						iVar16 = -2000;
					else
						iVar16 = 2000;

					if (i < 41)
					{
						iVar13 = roadAhead[i];

						if (iVar13 > 0)
							roadAhead[i] = iVar13 + iVar16;
					}
					
					i++;
				}
			}
			
			// [A] bug fix
			if (left < 0)
				left = 0;

			if (right < 0)
				right = 0;

			iVar16 = 0;
			while (left < 41)
			{
				roadAhead[left] = roadAhead[left] - iVar16;

				if (roadAhead[left] < 0)
					roadAhead[left] = 0;

				left++;
				iVar16 += 500;
			}

			iVar16 = 0;
			while (right < 41)
			{
				roadAhead[right] = roadAhead[right] - iVar16;

				if (roadAhead[right] < 0)
					roadAhead[right] = 0;

				right++;
				iVar16 += 500;
			}
		}
	}

	if (intention - 2U < 3)
	{
	LAB_LEAD__000ead84:
		cellz = 21;
		uVar17 = 21;
		uVar6 = 0;
		iVar13 = 84;
		iVar16 = roadAhead[21];
		
		do {
			if (iVar16 < *(int*)((int)roadAhead + iVar13))
			{
				iVar16 = *(int*)((int)roadAhead + iVar13);
				cellz = uVar17;
			}

			if (uVar6 < 0)
				uVar6 = -uVar6;

			uVar6 = uVar6 + 1;
			
			if ((uVar6 & 1) == 0)
				uVar6 = -uVar6;

			uVar17 = uVar17 + uVar6;
			iVar13 = uVar17 * 4;
		} while (uVar17 < 41);

		if (intention - 2U < 2)
		{
			if (cp->hd.speed > 100)
				cp->ai.l.roadForward = LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul;
			else
				cp->ai.l.roadForward = LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul;
			
			if (cp->ai.l.roadForward > iVar16)
			{
				if (cp->ai.l.roadForward > -1)
					cp->ai.l.roadForward = -1;
				else
					cp->ai.l.roadForward -= 1;
				
				if (intention == 3)
					cp->ai.l.roadPosition = -20000;
				else
					cp->ai.l.roadPosition = 20000;
				
				if (cp->ai.l.roadForward > -21)
					return;

				SelectExit(cp, GET_JUNCTION(cp->ai.l.nextJunction));
				return;
			}
		}
	}
	else
	{
		iVar16 = cp->ai.l.boringness;
		cellz = cp->ai.l.lastTarget;

		if (cp->ai.l.boringness < 31)
		{
			int spdThresh;

			spdThresh = ((cp->hd.speed + 100) / 50) * 1024;

			if(	roadAhead[MAX(0, MIN(40, cellz - 1))] <= spdThresh &&
				roadAhead[MAX(0, MIN(40, cellz))] <= spdThresh &&
				roadAhead[MAX(0, MIN(40, cellz + 1))] <= spdThresh)
			{
				goto LAB_LEAD__000ead84;
			}
		}
		else
		{
			if (ABS((cellz - laneAvoid) * 100) < cp->ai.l.width / 3)
			{
				goto LAB_LEAD__000ead84;
			}

			int spdThresh;

			spdThresh = ((cp->hd.speed + 100) / 50) * 1024;

			if(	roadAhead[MAX(0, MIN(40, cellz - 1))] <= spdThresh &&
				roadAhead[MAX(0, MIN(40, cellz))] <= spdThresh &&
				roadAhead[MAX(0, MIN(40, cellz + 1))] <= spdThresh)
			{
				goto LAB_LEAD__000ead84;
			}
		}
		
		iVar16 = roadAhead[cellz];
		uVar6 = cellz - 2;
		iVar13 = cellz + 2;

		if (uVar6 < iVar13)
		{
			piVar7 = roadAhead + uVar6;
			do {
				if ((uVar6 < 41) && (iVar16 < *piVar7))
				{
					iVar16 = *piVar7;
					cellz = uVar6;
				}

				uVar6 = uVar6 + 1;
				piVar7 = piVar7 + 1;
			} while (uVar6 < iVar13);
		}
	}

	if (intention < 2 || intention == 4)
	{
		cp->ai.l.roadForward = 5120;

		if (cellz > 21)
			iVar16 = -1;
		else
			iVar16 = 1;

		if (cellz == 21)
		{
			cp->ai.l.lastTarget = cellz;
		}
		else
		{
			piVar7 = &roadAhead[cellz];
			uVar6 = cellz;

			do {
				if (cp->ai.l.roadForward > *piVar7)
					cp->ai.l.roadForward = *piVar7;

				uVar6 = uVar6 + iVar16;
				piVar7 = piVar7 + iVar16;
			} while (uVar6 != 21);

			cp->ai.l.lastTarget = cellz;
		}
	}
	else if (intention == 5)
	{
		if (cp->ai.l.recoverTime == 0 ||
			cp->ai.l.recoverTime > 20)
		{
			cp->ai.l.recoverTime = 0;
	
			piVar7 = &roadAhead[20];
			iVar16 = roadAhead[19];

			i = 0;
			do {
				if (*piVar7 < iVar16)
					iVar16 = *piVar7;
				
				piVar7++;
				i++;
			} while (i < 4);

			if (roadAhead[38] > iVar16)
				cp->ai.l.roadForward = -1;
			else
				cp->ai.l.roadForward = 1;
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

	iVar16 = cellz - 21;

	if (intention == 6)
	{
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	if (intention - 4U < 2)
	{
		if (intention == 4)
			iVar16 *= 1536;
		else
			iVar16 *= 2048;

		cp->ai.l.roadPosition = ((iVar16 / 21 + 2048U & 0xfff) + cp->hd.direction & 4095) - 2048;
	}
	else if (intention < 2)
	{
		cp->ai.l.roadPosition = (iVar16 * 200 + cp->ai.l.width) - cp->ai.l.d;
	}
	else
	{
		if (intention - 2U > 1)
			return;

		cp->ai.l.roadPosition = iVar16 * 100 + cp->ai.l.width;
	}
}


// decompiled code
// original method signature: 
// void /*$ra*/ CheckCurrentRoad(CAR_DATA *cp /*$s3*/)
 // line 2242, offset 0x000eb1fc
	/* begin block 1 */
		// Start line: 2243
		// Start offset: 0x000EB1FC
		// Variables:
	// 		static int heading; // offset 0x1c
	// 		int cr; // $s5
	// 		static int jdist; // offset 0x20
	// 		static int nextJunction; // offset 0x50
	// 		static VECTOR basePosition; // offset 0x60
	// 		int checkNext; // $s6

		/* begin block 1.1 */
			// Start line: 2278
			// Start offset: 0x000EB300
			// Variables:
		// 		DRIVER2_STRAIGHT *straight; // $t3
		// 		static int d; // offset 0x70
		// 		static int toGo; // offset 0x74
		// 		static int angle; // offset 0x78
		// 		static int s; // offset 0x7c
		// 		static int c; // offset 0x80
		// 		int dx; // $t5
		// 		int dz; // $t6
		/* end block 1.1 */
		// End offset: 0x000EB578
		// End Line: 2319

		/* begin block 1.2 */
			// Start line: 2328
			// Start offset: 0x000EB5C4
			// Variables:
		// 		DRIVER2_CURVE *curve; // $s2
		// 		static int angle; // offset 0x84
		// 		static int radius; // offset 0x88
		// 		static int dx; // offset 0x8c
		// 		static int dz; // offset 0x90
		// 		static int fixedThresh; // offset 0x94
		/* end block 1.2 */
		// End offset: 0x000EB8F8
		// End Line: 2386

		/* begin block 1.3 */
			// Start line: 2415
			// Start offset: 0x000EB974
			// Variables:
		// 		static int diff; // offset 0x98

			/* begin block 1.3.1 */
				// Start line: 2420
				// Start offset: 0x000EB98C
				// Variables:
			// 		DRIVER2_JUNCTION *junction; // $s0
			/* end block 1.3.1 */
			// End offset: 0x000EB9D4
			// End Line: 2428

			/* begin block 1.3.2 */
				// Start line: 2440
				// Start offset: 0x000EBA14
				// Variables:
			// 		DRIVER2_STRAIGHT *straight; // $v1
			/* end block 1.3.2 */
			// End offset: 0x000EBA5C
			// End Line: 2446

			/* begin block 1.3.3 */
				// Start line: 2449
				// Start offset: 0x000EBA5C
				// Variables:
			// 		DRIVER2_CURVE *curve; // $v1
			// 		static int dx; // offset 0x9c
			// 		static int dz; // offset 0xa0
			/* end block 1.3.3 */
			// End offset: 0x000EBAE8
			// End Line: 2460

			/* begin block 1.3.4 */
				// Start line: 2475
				// Start offset: 0x000EBB2C
				// Variables:
			// 		DRIVER2_STRAIGHT *straight; // $t1
			// 		static int dx; // offset 0xa4
			// 		static int dz; // offset 0xa8
			// 		static int dist; // offset 0xac
			// 		static int offx; // offset 0xb0
			// 		static int offz; // offset 0xb4
			/* end block 1.3.4 */
			// End offset: 0x000EBB2C
			// End Line: 2475

			/* begin block 1.3.5 */
				// Start line: 2504
				// Start offset: 0x000EBC5C
				// Variables:
			// 		DRIVER2_CURVE *curve; // $s4
			// 		static int angle; // offset 0xb8
			// 		int radius; // $s2
			// 		static int dx; // offset 0xbc
			// 		static int dz; // offset 0xc0
			// 		static int basex; // offset 0xc4
			// 		static int basez; // offset 0xc8
			// 		static int dist; // offset 0xcc
			// 		static int offx; // offset 0xd0
			// 		static int offz; // offset 0xd4
			/* end block 1.3.5 */
			// End offset: 0x000EBE44
			// End Line: 2544
		/* end block 1.3 */
		// End offset: 0x000EBFD0
		// End Line: 2594

		/* begin block 1.4 */
			// Start line: 2629
			// Start offset: 0x000EC158
		/* end block 1.4 */
		// End offset: 0x000EC158
		// End Line: 2630
	/* end block 1 */
	// End offset: 0x000EC194
	// End Line: 2641

	/* begin block 2 */
		// Start line: 5778
	/* end block 2 */
	// End Line: 5779

// [D] [T]
void CheckCurrentRoad(CAR_DATA* cp)
{
	static int heading; // offset 0x1c
	static int nextJunction; // offset 0x50
	static VECTOR basePosition; // offset 0x60

	int checkNext;
	int currentRoad;
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
		static int d; // offset 0x70
		static int toGo; // offset 0x74
		static int angle; // offset 0x78
		static int s; // offset 0x7c
		static int c; // offset 0x80
		int fixedThresh;
		int dx, dz;

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

		s = rcossin_tbl[(angle & 0xfff) * 2];
		c = rcossin_tbl[(angle & 0xfff) * 2 + 1];
		
		d = FIXEDH(s * dx + c * dz);

		toGo = (straight->length / 2) - d;
		
		if (cp->hd.speed > 100)
			fixedThresh = LeadValues.hDist + (cp->hd.speed - 100) * LeadValues.hDistMul;
		else
			fixedThresh = LeadValues.tDist + cp->hd.speed * LeadValues.tDistMul;

		if (toGo < fixedThresh && cp->ai.l.offRoad == 0 && cp->ai.l.dstate != 5)
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
		static int angle; // offset 0x84
		static int radius; // offset 0x88
		static int dx; // offset 0x8c
		static int dz; // offset 0x90
		static int fixedThresh; // offset 0x94

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
		currentRoad = nextJunction;
		
		static int diff;

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
				static int dx; // offset 0x9c
				static int dz; // offset 0xa0

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

		diff = (heading - cp->hd.direction + 2048 & 0xfff) - 2048;

		if (IS_STRAIGHT_SURFACE(currentRoad))
		{
			int cs, sn;
			static int dx; // offset 0xa4
			static int dz; // offset 0xa8
			static int dist; // offset 0xac
			static int offx; // offset 0xb0
			static int offz; // offset 0xb4

			straight = GET_STRAIGHT(currentRoad);

			sn = rcossin_tbl[(heading & 0xfff) * 2];
			cs = rcossin_tbl[(heading & 0xfff) * 2 + 1];
			
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
			static int angle; // offset 0xb8
			static int dx; // offset 0xbc
			static int dz; // offset 0xc0
			static int basex; // offset 0xc4
			static int basez; // offset 0xc8
			static int dist; // offset 0xcc
			static int offx; // offset 0xd0
			static int offz; // offset 0xd4

			curve = GET_CURVE(currentRoad);
			dx = cp->hd.where.t[0] - curve->Midx;
			dz = cp->hd.where.t[2] - curve->Midz;
			
			radius = curve->inside * 1024 + ROAD_LANES_COUNT(curve) * 512;
			angle = ratan2(dx, dz);

			// check directions
			if (angle - heading & 0x800)
			{
				basex = FIXEDH(rcossin_tbl[(curve->start & 0xfff) * 2] * radius);
				basez = FIXEDH(rcossin_tbl[(curve->start & 0xfff) * 2 + 1] * radius);

				cp->ai.l.base_Normal = cp->ai.l.d = hypot(dx, dz);
				cp->ai.l.base_Dir = 1;
				cp->ai.l.base_Angle = angle;
				cp->ai.l.d = cp->ai.l.d - radius;
			}
			else
			{
				basex = FIXEDH(rcossin_tbl[(curve->end & 0xfff) * 2] * radius);
				basez = FIXEDH(rcossin_tbl[(curve->end & 0xfff) * 2 + 1] * radius);

				cp->ai.l.base_Normal = cp->ai.l.d = hypot(dx, dz);
				cp->ai.l.base_Dir = -1;
				cp->ai.l.base_Angle = angle;
				cp->ai.l.d = radius - cp->ai.l.d;
			}

			cp->ai.l.width = ROAD_LANES_COUNT(curve) * 512;
			offx = basex - cp->hd.where.t[0];
			offz = basez - cp->hd.where.t[2];
			
			dist = -FIXEDH(offx * rcossin_tbl[(heading & 0xfff) * 2] + offz * rcossin_tbl[(heading & 0xfff) * 2 + 1]);
			dx = FIXEDH(rcossin_tbl[(heading & 0xfff) * 2] * dist);
			dz = FIXEDH(rcossin_tbl[(heading & 0xfff) * 2 + 1] * dist);
			
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



// decompiled code
// original method signature: 
// void /*$ra*/ SetTarget(CAR_DATA *cp /*$s1*/, int cr /*$a0*/, int heading /*$s4*/, int *nextJunction /*$s3*/)
 // line 2644, offset 0x000ec1c4
	/* begin block 1 */
		// Start line: 2645
		// Start offset: 0x000EC1C4

		/* begin block 1.1 */
			// Start line: 2657
			// Start offset: 0x000EC1FC
			// Variables:
		// 		static int dx; // offset 0xd8
		// 		static int dz; // offset 0xdc
		/* end block 1.1 */
		// End offset: 0x000EC278
		// End Line: 2668

		/* begin block 1.2 */
			// Start line: 2675
			// Start offset: 0x000EC298
			// Variables:
		// 		DRIVER2_STRAIGHT *straight; // $t5
		// 		int dx; // $a1
		// 		int dz; // $a0
		// 		int rx; // $v1
		// 		int rz; // $a2
		// 		int ux; // $t0
		// 		int uz; // $t4
		// 		int d; // $v1
		// 		int angle; // $v0
		// 		int mul; // $v1
		/* end block 1.2 */
		// End offset: 0x000EC33C
		// End Line: 2695

		/* begin block 1.3 */
			// Start line: 2720
			// Start offset: 0x000EC444
			// Variables:
		// 		DRIVER2_CURVE *curve; // $s0
		// 		int angle; // $a1
		// 		int radius; // $a2
		/* end block 1.3 */
		// End offset: 0x000EC5C4
		// End Line: 2754
	/* end block 1 */
	// End offset: 0x000EC5C4
	// End Line: 2760

	/* begin block 2 */
		// Start line: 6937
	/* end block 2 */
	// End Line: 6938

// [D] [T]
void SetTarget(CAR_DATA* cp, int curRoad, int heading, int* nextJunction)
{
	static int dx = 0; // offset 0xd8
	static int dz = 0; // offset 0xdc

	DRIVER2_STRAIGHT* straight;
	DRIVER2_CURVE* curve;

	if (cp->ai.l.offRoad == 1)
	{
		cp->ai.l.targetDir = cp->ai.l.roadPosition;

		// get the road
		dx = FIXEDH(rcossin_tbl[(cp->ai.l.targetDir & 0xfff) * 2 + 1] * cp->ai.l.roadForward);
		dz = FIXEDH(rcossin_tbl[(cp->ai.l.targetDir & 0xfff) * 2] * cp->ai.l.roadForward);

		cp->ai.l.targetX = cp->hd.where.t[0] + dx;
		cp->ai.l.targetZ = cp->hd.where.t[2] + dz;

		return;
	}

	if (IS_STRAIGHT_SURFACE(curRoad))
	{
		int dx;
		int dz;
		int rx;
		int rz;
		int ux;
		int uz;
		int d;
		int angle;
		int mul;
		
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

		angle = cp->ai.l.targetDir + 1024U & 0xfff;
		d = cp->ai.l.targetDir & 0xfff;
		
		dx = straight->Midx - cp->hd.where.t[0];
		dz = straight->Midz - cp->hd.where.t[2];

		rx = FIXEDH(rcossin_tbl[d * 2] * cp->ai.l.roadForward);
		rz = FIXEDH(rcossin_tbl[d * 2 + 1] * cp->ai.l.roadForward);

		ux = rcossin_tbl[angle * 2];
		uz = rcossin_tbl[angle * 2 + 1];

		// l.roadPosition gives the lane offset
		// [A] it's obviously bugged somewhere as car always tends to be on left lanes
		// on curves it's even WORSE
		mul = FIXEDH(ux * dx + uz * dz) - ROAD_LANES_COUNT(straight) * 512 + cp->ai.l.roadPosition;
		
		ux = FIXEDH(mul * ux);
		uz = FIXEDH(mul * uz);
		
		cp->ai.l.targetX = cp->hd.where.t[0] + rx + ux;
		cp->ai.l.targetZ = cp->hd.where.t[2] + rz + uz;
	}
	else if (IS_CURVED_SURFACE(curRoad))
	{
		int angle;
		int radius;
		
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

		cp->ai.l.targetX = curve->Midx + FIXEDH(radius * rcossin_tbl[(angle & 0xfff) * 2]);
		cp->ai.l.targetZ = curve->Midz + FIXEDH(radius * rcossin_tbl[(angle & 0xfff) * 2 + 1]);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SelectExit(CAR_DATA *cp /*$s3*/, DRIVER2_JUNCTION *junction /*$a3*/)
 // line 2763, offset 0x000ec5e4
	/* begin block 1 */
		// Start line: 2764
		// Start offset: 0x000EC5E4
		// Variables:
	// 		int onward; // $s1
	// 		int numExits; // $s2
	// 		int el[4][2]; // stack offset -56
	// 		int tmp; // $a1
	// 		int i; // $a2
	// 		int total; // $s0

		/* begin block 1.1 */
			// Start line: 2781
			// Start offset: 0x000EC6F4
		/* end block 1.1 */
		// End offset: 0x000EC71C
		// End Line: 2788

		/* begin block 1.2 */
			// Start line: 2792
			// Start offset: 0x000EC79C
		/* end block 1.2 */
		// End offset: 0x000EC7C8
		// End Line: 2799

		/* begin block 1.3 */
			// Start line: 2803
			// Start offset: 0x000EC844
		/* end block 1.3 */
		// End offset: 0x000EC870
		// End Line: 2810
	/* end block 1 */
	// End offset: 0x000EC99C
	// End Line: 2843

	/* begin block 2 */
		// Start line: 7239
	/* end block 2 */
	// End Line: 7240

	/* begin block 3 */
		// Start line: 7241
	/* end block 3 */
	// End Line: 7242

// [D] [T]
void SelectExit(CAR_DATA* cp, DRIVER2_JUNCTION* junction)
{
	int el[4][2];
	int rnd;
	int onward; // $s1
	int numExits; // $s2
	int tmp; // $a1
	int i; // $a2
	int total; // $s0

	numExits = 0;
	total = 0;

	onward = (cp->ai.l.targetDir + 512U & 0xfff) >> 10;

	// [A] was weird loop
	for(i = 0; i < 4; i++)
	{
		if(junction->ExitIdx[i] == cp->ai.l.lastRoad)
		{
			onward = i + 2U & 3;
			break;
		}
	}

	// [A] seems was unrolled loopp
	for(i = -1; i < 2; i++)
	{
		int road;

		tmp = (onward + i) & 3;
		road = junction->ExitIdx[tmp];
		
		if(IS_CURVED_SURFACE(road) || IS_STRAIGHT_SURFACE(road))
		{
			el[numExits][0] = i;
			el[numExits][1] = junction->flags >> (tmp << 3) & 0xf;

			total += el[numExits][1];
			numExits++;
		}
	}

	if (total == 0)
	{
		el[numExits][0] = 2;
		el[numExits][1] = 1;
		numExits++;
		total = 1;
	}

	rnd = ABS(leadRand());

	// [A] again, was a strange loop. Hope it works
	tmp = 0;
	for(i = 0; i < numExits; i++)
	{
		if(tmp + el[i][1] > rnd % total)
		{
			cp->ai.l.nextTurn = el[i][0];
			break;
		}

		tmp += el[i][1];
	}

	cp->ai.l.nextExit = onward + cp->ai.l.nextTurn & 3;

	rnd = ABS(leadRand());

	if (rnd == (rnd / 3) * 3)
		cp->ai.l.nextTurn = -cp->ai.l.nextTurn;

}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ FreeRoamer(CAR_DATA *cp /*$s1*/)
 // line 2848, offset 0x000ec99c
	/* begin block 1 */
		// Start line: 2849
		// Start offset: 0x000EC99C

		/* begin block 1.1 */
			// Start line: 2965
			// Start offset: 0x000ECA4C
			// Variables:
		// 		CAR_DATA *pCar; // $v0

			/* begin block 1.1.1 */
				// Start line: 2965
				// Start offset: 0x000ECA4C
				// Variables:
			// 		int seed; // $a0

				/* begin block 1.1.1.1 */
					// Start line: 2965
					// Start offset: 0x000ECA4C
					// Variables:
				// 		int i; // $s0
				/* end block 1.1.1.1 */
				// End offset: 0x000ECB04
				// End Line: 2966
			/* end block 1.1.1 */
			// End offset: 0x000ECB04
			// End Line: 2966
		/* end block 1.1 */
		// End offset: 0x000ECB04
		// End Line: 2967
	/* end block 1 */
	// End offset: 0x000ECB28
	// End Line: 2971

	/* begin block 2 */
		// Start line: 7429
	/* end block 2 */
	// End Line: 7430

	/* begin block 3 */
		// Start line: 7435
	/* end block 3 */
	// End Line: 7436

// [D] [T]
u_int FreeRoamer(CAR_DATA* cp)
{
	LeadHorn(cp);
	DamageBar.position = cp->totalDamage;

	if (cp->ai.l.dstate != 8)
	{
		// falling out of the world/sinking in water?
		if (cp->hd.where.m[1][1] < 100 || ((cp->hd.wheel[1].surface & 7) == 1 && ((cp->hd.wheel[3].surface & 7) == 1)))
			cp->totalDamage += 100;
	}

	cp->ai.l.ctt++;

	if (cp->ai.l.takeDamage != 0)
		cp->ai.l.takeDamage--;

	if (CameraCnt == 100)
	{
		CAR_DATA* pCar = &car_data[player[0].playerCarId];

		if (CAR_INDEX(pCar) >= 0) // [A] bug fix
		{
			int seed = (pCar->hd.where.t[0] + pCar->hd.where.t[2]) / (pCar->hd.speed + 1);

			randIndex = 0;

			for (int i = NUM_STATES - 1; i > -1; i--)
			{
				randState[i] = seed;
				seed = seed * 0x751 + 0x10cc2af;
			}

			for (int i = NUM_ITERATIONS - 1; i > -1; i--)
				leadRand();
		}
	}

	LeadUpdateState(cp);

	return LeadPadResponse(cp);
}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ hypot(long x /*$s1*/, long y /*$a1*/)
 // line 2993, offset 0x000ecb28
	/* begin block 1 */
		// Start line: 2994
		// Start offset: 0x000ECB28

		/* begin block 1.1 */
			// Start line: 2997
			// Start offset: 0x000ECB5C
			// Variables:
		// 		long t; // $v0
		/* end block 1.1 */
		// End offset: 0x000ECB64
		// End Line: 2997

		/* begin block 1.2 */
			// Start line: 3001
			// Start offset: 0x000ECBB4
		/* end block 1.2 */
		// End offset: 0x000ECBE8
		// End Line: 3006
	/* end block 1 */
	// End offset: 0x000ECBE8
	// End Line: 3007

	/* begin block 2 */
		// Start line: 3236
	/* end block 2 */
	// End Line: 3237

	/* begin block 3 */
		// Start line: 10452
	/* end block 3 */
	// End Line: 10453

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





