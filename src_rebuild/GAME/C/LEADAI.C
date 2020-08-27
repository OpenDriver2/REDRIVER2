#include "THISDUST.H"
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

static int randIndex;
static int randState[17];
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

// [D]
int leadRand(void)
{
	randIndex = (randIndex + 1) % 0x11;
	return randState[randIndex] = randState[randIndex] + randState[(randIndex + 0xc) % 0x11];
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitLead(struct _CAR_DATA *cp /*$s0*/)
 // line 278, offset 0x000e7128
	/* begin block 1 */
		// Start line: 279
		// Start offset: 0x000E7128

		/* begin block 1.1 */
			// Start line: 319
			// Start offset: 0x000E71A0
			// Variables:
		// 		struct DRIVER2_STRAIGHT *straight; // $a3
		// 		struct DRIVER2_CURVE *curve; // $t0
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

// [D]
void InitLead(_CAR_DATA *cp)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int x;
	int iVar4;
	int z;
	int uVar5;
	DRIVER2_STRAIGHT* st;
	DRIVER2_CURVE* cr;
	int iVar6;

	x = cp->hd.where.t[0];
	z = cp->hd.where.t[2];

	cp->hndType = 5;
	cp->controlType = 4;
	cp->ai.l.roadPosition = 512;
	cp->ai.l.dstate = 3;
	cp->ai.l.recoverTime = 40;
	cp->ai.l.nextExit = 2;
	cp->ai.l.roadForward = 5120;
	cp->ai.l.takeDamage = 0;

	if (valid_region(x, z) == 0)
	{
		z = -1;

		iVar1 = 0;

		if (0 < NumDriver2Straights)
		{
			iVar6 = (cp->hd).where.t[0];
			st = Driver2StraightsPtr;

			do {
				iVar4 = iVar6 - st->Midx;

				iVar2 = (cp->hd).where.t[2] - st->Midz;
				iVar4 = iVar4 >> 10;

				iVar2 = iVar2 >> 10;
				iVar3 = iVar4 * iVar4 + iVar2 * iVar2;

				if (((iVar4 < 0x3e9) && (iVar2 < 0x3e9)) && ((iVar3 < z || (z == -1))))
				{
					cp->ai.l.currentRoad = iVar1;
					z = iVar3;
				}

				iVar1 = iVar1 + 1;
				st = st + 1;
			} while (iVar1 < NumDriver2Straights);
		}

		uVar5 = 0;

		if (0 < NumDriver2Curves) 
		{
			cr = Driver2CurvesPtr;
			iVar1 = (cp->hd).where.t[0];
			do {
				iVar6 = iVar1 - cr->Midx;

				iVar4 = (cp->hd).where.t[2] - cr->Midz;
				iVar6 = iVar6 >> 10;

				iVar4 = iVar4 >> 10;
				iVar2 = iVar6 * iVar6 + iVar4 * iVar4;

				if (((iVar6 < 0x3e9) && (iVar4 < 0x3e9)) && ((iVar2 < z || (z == -1)))) 
				{
					cp->ai.l.currentRoad = uVar5 & 0x4000;
					z = iVar2;
				}

				uVar5 = uVar5 + 1;
				cr = cr + 1;
			} while ((int)uVar5 < NumDriver2Curves);
		}
	}
	else
	{
		x = GetSurfaceIndex((VECTOR*)cp->hd.where.t);
		cp->ai.l.currentRoad = x;
	}

	randState[0] = 0x27a2a;
	randState[2] = 0x38b0;
	randState[5] = 0xe;
	randState[7] = 0x8748;
	randState[1] = 0x717d58;
	randState[3] = 0x701ced;
	randState[4] = 0xbdfda3;
	randState[6] = 0x268833;
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
// void /*$ra*/ LeadUpdateState(struct _CAR_DATA *cp /*$s0*/)
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
		// 		struct VECTOR tmpStart; // stack offset -48
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
		// 		struct VECTOR pos; // stack offset -32
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

// [D]
void LeadUpdateState(_CAR_DATA *cp)
{
	bool bVar1;
	int iVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	uint uVar7;
	VECTOR tmpStart;
	VECTOR pos;

	if (valid_region(cp->hd.where.t[0], cp->hd.where.t[2]) == 0)
	{
	LAB_LEAD__000e7480:
		cp->ai.l.dstate = 8;
		return;
	}

	iVar3 = cp->hd.where.t[0];
	iVar2 = iVar3 - player[0].pos[0];

	if (iVar2 < 0)
		iVar2 = player[0].pos[0] - iVar3;

	if (0x3e1c < iVar2) 
		goto LAB_LEAD__000e7480;

	iVar5 = cp->hd.where.t[2];
	iVar2 = iVar5 - player[0].pos[2];

	if (iVar2 < 0)
		iVar2 = player[0].pos[2] - iVar5;

	if (0x3e1c < iVar2)
		goto LAB_LEAD__000e7480;

	if (cp->ai.l.dstate == 8)
	{
		if (spoolactive != 0) 
		{
			cp->ai.l.dstate = 8;
			return;
		}

		tmpStart.vz = cp->hd.where.t[2];
		tmpStart.vx = iVar3;
		tmpStart.vy = MapHeight(&tmpStart);
		tmpStart.vy = tmpStart.vy - ((cp->ap).carCos)->wheelDisp[0].vy;

		InitCarPhysics(cp, (long(*)[4]) & tmpStart, (int)cp->ai.l.targetDir);

		cp->ai.l.dstate = 3;
	}

	iVar2 = cp->ai.l.panicCount;

	if (iVar2 < 0)
		iVar2 = -iVar2;

	iVar3 = FIXED(cp->st.n.angularVelocity[1]);

	if (0 < iVar2)
		cp->ai.l.dstate = 5;

	if (cp->ai.l.dstate == 6)
		cp->ai.l.dstate = 3;

	if (cp->hd.speed < 10)
		cp->ai.l.stuckCount++;
	else
		cp->ai.l.stuckCount = 0;

	if (cp->ai.l.dstate == 4)
	{
		if (0x14 < cp->ai.l.stuckCount)
		{
			cp->ai.l.recoverTime = 1;
			cp->ai.l.stuckCount = 0;
			cp->ai.l.roadForward = -cp->ai.l.roadForward;
		}
	}
	else
	{
		if (10 < cp->ai.l.stuckCount)
		{
			cp->ai.l.dstate = 4;
			cp->ai.l.recoverTime = 0;
			cp->ai.l.stuckCount = 0;
		}
	}

	switch (cp->ai.l.dstate)
	{
		case 0:
			CheckCurrentRoad(cp);
			iVar2 = ((cp->hd.direction - (int)cp->ai.l.targetDir) + 0x800U & 0xfff) - 0x800;

			if (cp->hd.speed < 20)
				cp->ai.l.dstate =3;

			if (iVar2 < 0)
				iVar2 = -iVar2;

			if (iVar2 < LeadValues.hEnd) 
			{
				if (iVar3 < 0)
					iVar3 = -iVar3;

				if (0x96 < iVar3)
					cp->ai.l.dstate = 1;

			}
			break;
		case 1:
			CheckCurrentRoad(cp);
			iVar2 = ((cp->hd.direction - (int)cp->ai.l.targetDir) + 0x800U & 0xfff) - 0x800;

			if (iVar2 < 0)
				iVar2 = -iVar2;

			if (iVar2 < LeadValues.dEnd)
				cp->ai.l.dstate = 2;

			goto LAB_LEAD__000e7748;
		case 2:
			CheckCurrentRoad(cp);
		LAB_LEAD__000e7748:
			if (iVar3 < 0)
				iVar3 = -iVar3;

			if (iVar3 < 0x18) 
				cp->ai.l.dstate = 3;

			break;
		case 3:
			iVar2 = cp->ai.l.recoverTime;

			if (0x28 < iVar2)
				cp->ai.l.recoverTime = iVar2 + -1;

			CheckCurrentRoad(cp);
			uVar7 = cp->hd.direction;
			uVar4 = uVar7 & 0xfff;
			iVar3 = cp->hd.speed;
			iVar2 = ((uVar7 - (int)cp->ai.l.targetDir) + 0x800 & 0xfff) - 0x800;
			iVar5 = FIXED((cp->ai.l.targetX - cp->hd.where.t[0]) * (int)rcossin_tbl[uVar4 * 2] + (cp->ai.l.targetZ - cp->hd.where.t[2]) * (int)rcossin_tbl[uVar4 * 2 + 1]);
			if (100 < iVar3) 
			{
			LAB_LEAD__000e7824:
				if (iVar2 < 0)
					iVar2 = -iVar2;

				iVar6 = iVar2;

				if (iVar2 <= LeadValues.hEnd) 
					goto LAB_LEAD__000e78ac;

				if (100 < iVar3)
				{
					if (LeadValues.hDist + (iVar3 + -100) * LeadValues.hDistMul <= iVar5)
					{
						cp->ai.l.dstate = 6;
						return;
					}
				LAB_LEAD__000e78a4:
					cp->ai.l.dstate = 0;
					return;
				}

				if (iVar5 < LeadValues.tDist + iVar3 * LeadValues.tDistMul) 
					goto LAB_LEAD__000e78a4;
			}
			else 
			{
				iVar6 = iVar2;
				if (iVar2 < 0)
					iVar6 = -iVar2;

				if ((0x1e < iVar3) && (0x400 < iVar6))
					goto LAB_LEAD__000e7824;

			LAB_LEAD__000e78ac:
				iVar2 = cp->hd.speed;
				if (iVar6 <= iVar2 + LeadValues.tEnd)
					return;

				if (iVar2 < 0x65)
					iVar2 = LeadValues.tDist + iVar2 * LeadValues.tDistMul;
				else
					iVar2 = LeadValues.hDist + (iVar2 + -100) * LeadValues.hDistMul;

				if (iVar5 < iVar2) 
				{
					cp->ai.l.dstate = 7;
					return;
				}
			}

			cp->ai.l.dstate = 6;
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
			iVar2 = ((cp->hd.direction - cp->ai.l.targetDir) + 0x800U & 0xfff) - 0x800;

			if (cp->ai.l.panicCount != 0)
				return;

			if (iVar2 < 0)
				iVar2 = -iVar2;
	
			bVar1 = iVar2 < 200;

			if (bVar1)
				cp->ai.l.dstate = 2;

			break;
		case 7:
			CheckCurrentRoad(cp);

			iVar2 = ((cp->hd.direction - cp->ai.l.targetDir) + 0x800U & 0xfff) - 0x800;

			if (iVar2 < 0)
				iVar2 = -iVar2;

			bVar1 = iVar2 < cp->hd.speed + LeadValues.tEnd;

			if (bVar1) 
				cp->ai.l.dstate = 2;

			break;
	}
}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ LeadPadResponse(struct _CAR_DATA *cp /*$t0*/)
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

// [D]
ulong LeadPadResponse(_CAR_DATA *cp)
{
	int iVar1;
	int iVar2;
	int steerDelta;
	int iVar3;
	int avel;
	int deltaTh;
	long t0;
	uint uVar4;

	t0 = 0;
	deltaTh = ((cp->hd.direction - cp->ai.l.targetDir) + 0x800U & 0xfff) - 0x800;
	avel = FIXED(cp->st.n.angularVelocity[1]);
	switch (cp->ai.l.dstate)
	{
		case 0:
			t0 = 0x8010;
			if (deltaTh < 0) {
				t0 = 0x2010;
			}
			break;

		case 1:
			t0 = 0x40;
			break;

		case 2:
			if (avel < 0) 
			{
				if (avel < 0)
					avel = -avel;

				t0 = 0x2040;
				if (0x28 < avel)
					t0 = 0x2044;

			}
			else 
			{
				if (avel < 0)
					avel = -avel;

				t0 = 0x8040;

				if (0x28 < avel)
					t0 = 0x8044;

			}
			break;
		case 3:

			uVar4 = cp->ai.l.targetDir & 0xfff;
			iVar2 = FIXED(-rcossin_tbl[uVar4 * 2 + 1] * ((cp->hd).where.t[0] - cp->ai.l.targetX) + rcossin_tbl[uVar4 * 2] * ((cp->hd).where.t[2] - cp->ai.l.targetZ));
			iVar3 = pathParams[4];

			if ((pathParams[4] < iVar2) || (iVar3 = -pathParams[4], iVar2 < -pathParams[4])) 
			{
				iVar2 = iVar3;
			}

			steerDelta = FIXED(pathParams[0] * FIXED(-rcossin_tbl[uVar4 * 2 + 1] * FIXED((cp->st).n.linearVelocity[0]) + rcossin_tbl[uVar4 * 2] * FIXED((cp->st).n.linearVelocity[2])) + pathParams[1] * avel + pathParams[2] * iVar2 + pathParams[3] * deltaTh) - cp->wheel_angle;

			t0 = 0x40;

			if (0x20 < steerDelta)
				t0 = 0x2040;

			if (0x40 < steerDelta)
				t0 = t0 | 4;

			if (steerDelta < -0x20)
				t0 = t0 | 0x8000;

			if (steerDelta < -0x40)
				t0 = t0 | 4;

			if (0x3e < steerDelta + 0x1fU)
				return t0;

			if (avel < 0)
				avel = -avel;

			if (5 < avel)
				return t0;

			if ((t0 & 0x40U) == 0)
				return t0;

			goto LAB_LEAD__000e7d50;
		case 4:

			uVar4 = 0x20;
			iVar2 = cp->ai.l.roadForward;
			iVar3 = ((cp->ai.l.roadPosition - (cp->hd).direction) + 0x800U & 0xfff) - 0x800;

			if (iVar2 < 0)
				uVar4 = 0x80;

			if (iVar3 * iVar2 < 1)
				t0 = uVar4 | 0x8000;
			else
				t0 = uVar4 | 0x2000;

			if (iVar3 < 0)
				iVar3 = -iVar3;

			if (200 < iVar3) 
			{
				if (deltaTh < 0)
					deltaTh = -deltaTh;

				if (deltaTh < 0x738)
					t0 = t0 | 4;
			}

			break;
		case 5:

			iVar2 = cp->ai.l.panicCount;
			iVar3 = avel;

			if (avel < 0)
				iVar3 = -avel;

			iVar1 = iVar2;

			if (iVar2 < 0) 
				iVar1 = -iVar2;

			if ((iVar1 < 2) || (0x96 < iVar3))
			{
				t0 = ((cp->hd).speed < 0x65) << 6;
			}
			else 
			{
				t0 = 0x20;

				if (100 < (cp->hd).speed)
					t0 = 0x10;

			}

			if (iVar3 < 0x50) 
			{
				t0 = t0 | 4;
			}

			if (iVar2 < 1) 
			{
				if (iVar2 < 0) 
				{
					if ((0x95 < iVar3) && (avel < 1)) 
						return t0;

					return t0 | 0x8000;
				}

				if ((0 < deltaTh) && ((iVar3 < 0x96 || (0 < avel)))) 
					t0 = t0 | 0x8000;


				if (-1 < deltaTh)
					return t0;
			}

			if ((iVar3 < 0x96) || (avel < 0)) 
				t0 = t0 | 0x2000;

			break;
		case 6:
			uVar4 = 0x8000;
			if (avel < 0)
				uVar4 = 0x2000;

			if ((cp->ai.l.roadForward < 0) && (100 < (cp->hd).speed))
				t0 = uVar4 | 0x80;
			else
				t0 = uVar4 | 0x40;

			break;
		case 7:
			if (avel < 0)
				avel = -avel;

			if (LeadValues.tAvelLimit <= avel) 
			{
				iVar3 = deltaTh;
				if (deltaTh < 0)
					iVar3 = -deltaTh;

				if (iVar3 < 0x401)
					goto LAB_LEAD__000e7d50;
			}

			t0 = 0x8004;

			if (deltaTh < 0)
				t0 = 0x2004;

		LAB_LEAD__000e7d50:
			t0 = t0 | 0x20;
			break;

		case 8:
			FakeMotion(cp);
			t0 = 0;
			break;
	}

	return t0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FakeMotion(struct _CAR_DATA *cp /*$s1*/)
 // line 718, offset 0x000e7de8
	/* begin block 1 */
		// Start line: 719
		// Start offset: 0x000E7DE8

		/* begin block 1.1 */
			// Start line: 724
			// Start offset: 0x000E7E40
			// Variables:
		// 		struct DRIVER2_STRAIGHT *straight; // $t1
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
			// 		struct DRIVER2_JUNCTION *junction; // $s0
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
		// 		struct DRIVER2_CURVE *curve; // $s0
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
			// 		struct DRIVER2_JUNCTION *junction; // $s0
			/* end block 1.2.1 */
			// End offset: 0x000E8104
			// End Line: 813

			/* begin block 1.2.2 */
				// Start line: 848
				// Start offset: 0x000E81F0
				// Variables:
			// 		struct DRIVER2_JUNCTION *junction; // $s0
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
		// 		struct DRIVER2_JUNCTION *junction; // $s0
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

// [D]
void FakeMotion(_CAR_DATA *cp)
{
	static int d; // offset 0x0
	static int toGo; // offset 0x4
 	static int angle; // offset 0x8
 	static int s; // offset 0xc
 	static int c; // offset 0x10

	short sVar1;
	int iVar2;
	long lVar3;
	short uVar4;
	int iVar5;
	int uVar6;
	int iVar7;
	int iVar8;
	int uVar9;
	int iVar10;
	DRIVER2_STRAIGHT* straight;
	DRIVER2_CURVE* curve;
	DRIVER2_JUNCTION* junction;

	junction = Driver2JunctionsPtr;
	uVar9 = cp->ai.l.currentRoad;
	uVar6 = uVar9 & 0xffffe000;

	if (uVar6 == 0x2000) 
	{
		cp->ai.l.lastRoad = uVar9;
		SelectExit(cp, junction + (uVar9 - 0x2000));
		iVar5 = cp->ai.l.nextExit;
		sVar1 = junction[uVar9 - 0x2000].ExitIdx[iVar5];
		cp->ai.l.targetDir = (short)(iVar5 << 10);
		cp->ai.l.direction = 0;
		cp->ai.l.currentRoad = (int)sVar1;
		return;
	}

	if (uVar6 < 0x2001) 
	{
		if (uVar6 != 0) 
			return;


		iVar10 = (cp->hd).where.t[0];
		iVar8 = (cp->hd).where.t[2];
		straight = Driver2StraightsPtr + uVar9;
		iVar7 = straight->Midx;
		iVar5 = straight->Midz;
		angle = straight->angle & 0xfff;
		uVar6 = (straight->ConnectIdx[1]);

		if (uVar6 == -1)
			uVar6 = (straight->ConnectIdx[0]);

		if (cp->ai.l.direction == 0)
		{
			iVar2 = -1;

			if (((cp->ai.l.targetDir - angle) + 0x400U & 0x800) == 0) 
				iVar2 = 1;

			cp->ai.l.direction = iVar2;
		}

		if (cp->ai.l.direction == -1)
		{
			uVar6 = (straight->ConnectIdx[3]);
			angle = angle ^ 0x800;

			if (uVar6 == -1)
				uVar6 = (straight->ConnectIdx[2]);
		}

		c = rcossin_tbl[(angle & 0xfffU) * 2];
		s = rcossin_tbl[(angle & 0xfffU) * 2 + 1];
		d = FIXED(c * (iVar10 - iVar7) + s * (iVar8 - iVar5));
		toGo = (straight->length >> 1) - d;

		if (-1 < toGo)
		{
			d = d + 0x78;

			(cp->hd).where.t[0] = FIXED(c * d) + straight->Midx;
			(cp->hd).where.t[2] = FIXED(s * d) + straight->Midz;

			cp->st.n.fposition[0] = cp->hd.where.t[0] << 4;
			cp->st.n.fposition[2] = cp->hd.where.t[2] << 4;
			return;
		}

		if ((((uVar6 & 0xffffe000) != 0x2000) || (NumDriver2Junctions <= (uVar6 & 0x1fff))) || (uVar6 < 0)) 
		{
			cp->ai.l.currentRoad = uVar6;
			goto LAB_LEAD__000e824c;
		}
	}
	else 
	{
		if (uVar6 != 0x4000)
			return;

		curve = Driver2CurvesPtr + (uVar9 - 0x4000);
		lVar3 = ratan2((cp->hd).where.t[0] - curve->Midx, (cp->hd).where.t[2] - curve->Midz);
		iVar5 = curve->inside * 2 + ((uint)(u_char)curve->NumLanes & 0xf);
		iVar7 = iVar5 * 0x200;

		if (cp->ai.l.direction == 0)
		{
			iVar8 = 1;

			if ((lVar3 - cp->ai.l.targetDir & 0x800U) == 0)
				iVar8 = -1;

			cp->ai.l.direction = iVar8;
		}

		if (cp->ai.l.direction == 1)
		{
			if (-1 < (int)(((curve->end - lVar3 & 0xfffU) + 0x800 & 0xfff) - 0x800)) {

				uVar9 = lVar3 + 0x13193 / iVar7;
				uVar6 = uVar9 & 0xfff;
				sVar1 = rcossin_tbl[uVar6 * 2 + 1];
				(cp->hd).where.t[0] = FIXED(rcossin_tbl[uVar6 * 2] * iVar7) + curve->Midx;
				iVar5 = curve->Midz;
				uVar4 = (short)uVar9 + 0x400;
			LAB_LEAD__000e82cc:
				cp->ai.l.targetDir = uVar4 & 0xfff;
				(cp->hd).where.t[2] = FIXED(sVar1 * iVar7) + iVar5;

				cp->st.n.fposition[0] = cp->hd.where.t[0] << 4;
				cp->st.n.fposition[2] = cp->hd.where.t[2] << 4;
				return;
			}

			uVar6 = (curve->ConnectIdx[1]);
			if (uVar6 == -1)
				uVar6 = (curve->ConnectIdx[0]);

			if (((uVar6 & 0xffffe000) != 0x2000) || (NumDriver2Junctions <= (int)(uVar6 & 0x1fff))) 
			{
			LAB_LEAD__000e8248:
				cp->ai.l.currentRoad = uVar6;
				goto LAB_LEAD__000e824c;
			}

			if (uVar6 < 0) 
			{
				cp->ai.l.currentRoad = uVar6;
				goto LAB_LEAD__000e824c;
			}
		}
		else 
		{
			if (-1 < (int)(((lVar3 - curve->start & 0xfffU) + 0x800 & 0xfff) - 0x800)) 
			{

				uVar9 = lVar3 - 0x13193 / iVar7;
				uVar6 = uVar9 & 0xfff;
				sVar1 = rcossin_tbl[uVar6 * 2 + 1];
				(cp->hd).where.t[0] = FIXED(rcossin_tbl[uVar6 * 2] * iVar7) + curve->Midx;
				iVar5 = curve->Midz;
				uVar4 = (short)uVar9 - 0x400;
				goto LAB_LEAD__000e82cc;
			}
			uVar6 = (curve->ConnectIdx[3]);

			if (uVar6 == -1)
				uVar6 = (curve->ConnectIdx[2]);

			if ((((uVar6 & 0xffffe000) != 0x2000) || (NumDriver2Junctions <= (int)(uVar6 & 0x1fff))) ||
				((int)uVar6 < 0)) goto LAB_LEAD__000e8248;
		}
	}

	junction = Driver2JunctionsPtr + (uVar6 - 0x2000);
	cp->ai.l.lastRoad = cp->ai.l.currentRoad;

	SelectExit(cp, junction);

	iVar5 = cp->ai.l.nextExit;
	sVar1 = junction->ExitIdx[iVar5];

	cp->ai.l.targetDir = (short)(iVar5 << 10);
	cp->ai.l.currentRoad = (int)sVar1;

LAB_LEAD__000e824c:
	cp->ai.l.direction = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PosToIndex(int *normal /*$t1*/, int *tangent /*$t4*/, int intention /*$a2*/, struct _CAR_DATA *cp /*$a3*/)
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

// [D]
void PosToIndex(int *normal, int *tangent, int intention, _CAR_DATA *cp)
{
	int uVar1;
	int iVar2;
	int uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;

	if (intention - 4U < 3) 
	{
		uVar3 = (*normal + 0x800U & 0xfff) - 0x800;
		*normal = uVar3;

		if (intention == 6)
		{
			uVar1 = uVar3;
			if (uVar3 < 0)
				uVar1 = -uVar3;

			if (uVar1 < 0xf0)
			{
				iVar6 = FIXED(*tangent * (int)rcossin_tbl[(uVar3 & 0xfff) * 2]);
				if (0x7d < iVar6) 
				{
					*normal = 0x17;
					return;
				}

				if (0x32 < iVar6) 
				{
					*normal = 0x16;
					return;
				}

				if (-0x32 < iVar6) 
				{
					*normal = 0x15;
					return;
				}

				if (iVar6 < -0x7c)
				{
					*normal = 0x13;
					return;
				}

				*normal = 0x14;
				return;
			}
		}
		iVar6 = *normal * 0x15;
		*normal = iVar6;

		if (intention == 4) 
			iVar6 = (iVar6 / 6 + (iVar6 >> 0x1f) >> 8) - (iVar6 >> 0x1f);
		else if (intention == 5)
			iVar6 = iVar6 >> 0xb;
		else
			iVar6 = iVar6 >> 10;

		*normal = iVar6;
		iVar6 = *normal;
	}
	else 
	{
		if (1 < intention) 
		{
			iVar2 = (cp->hd).speed;
			iVar7 = LeadValues.tWidth;
			iVar6 = LeadValues.tWidthMul;

			if (100 < iVar2) 
			{
				iVar7 = LeadValues.hWidth;
				iVar6 = LeadValues.hWidthMul;
			}

			iVar7 = iVar7 + iVar2 * iVar6;

			if (iVar2 < 0x65) 
			{
				iVar6 = LeadValues.tWidth80 + iVar2 / LeadValues.tWidth80Mul;
			}
			else 
			{
				iVar6 = LeadValues.hWidth80 + iVar2 * LeadValues.hWidth80Mul;
			}

			if (iVar2 < 0x65)
				iVar2 = LeadValues.tDist + iVar2 * LeadValues.tDistMul;
			else
				iVar2 = LeadValues.hDist + (iVar2 + -100) * LeadValues.hDistMul;

			iVar5 = (iVar2 << 3) / 10;

			if (intention == 2)
				*normal = -*normal;

			iVar4 = *normal;

			if (iVar7 < iVar4)
			{
				iVar6 = *tangent;
				*tangent = (iVar2 + iVar4) - iVar7;
				*normal = iVar2 - iVar6;
			}
			else if (iVar6 < iVar4)
			{
				iVar5 = ((iVar4 - iVar6) * (iVar2 - iVar5)) / (iVar7 - iVar6) + iVar5;
				*normal = iVar5 - *tangent;
				*tangent = iVar5;
			}
			else if (0 < iVar4)
			{
				iVar6 = (iVar5 * iVar6) / iVar4;

				*normal = iVar6 - *tangent;
				*tangent = iVar6;
			}
		}

		iVar6 = *normal / 100;
	}

	*normal = iVar6 + 0x15;
}



// decompiled code
// original method signature: 
// void /*$ra*/ BlockToMap(struct MAP_DATA *data /*$s3*/)
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
	// 		static struct MAP_DATA newdata; // offset 0x30

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
		// 		struct DRIVER2_CURVE *curve; // $s1
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

// [D]
void BlockToMap(MAP_DATA *data)
{
	static int carLength; // offset 0x14
	static int carWidth; // offset 0x18
	static int length; // offset 0x14
	static int width; // offset 0x18
	static int left; // offset 0x1c
	static int right; // offset 0x20
	static int ldist; // offset 0x24
	static int rdist; // offset 0x28
	static struct MAP_DATA newdata; // offset 0x30

	static int offx;

	int someTempVar;

	bool bVar1;
	long uVar2;
	long lVar3;
	ulong uVar4;
	VECTOR* pVVar5;
	CAR_COSMETICS* pCVar6;
	VECTOR* pVVar7;
	_CAR_DATA* cp;
	int x;
	int iVar8;
	int iVar9;
	int x_00;
	long* plVar10;
	int* tangent;
	DRIVER2_CURVE* curve;
	int* tangent_00;
	int iVar11;
	int y;
	int* normal;
	int iVar12;
	int* normal_00;
	int uVar13;
	int iVar14;
	int iVar15;
	int corners[4][3];
	int temp;
	int tdist;
	int locall;
	int localld;
	int localr;
	int localrd;

	pCVar6 = (data->cp->ap).carCos;
	carLength = (int)(pCVar6->colBox).vz;
	carWidth = (int)(pCVar6->colBox).vx;

	switch (data->intention)
	{
		case 0:
		case 2:
		case 3:
			pVVar7 = data->pos;
			pVVar5 = data->base;
			y = pVVar7->vx - pVVar5->vx;
			x = pVVar5->vy - pVVar7->vy;
			x_00 = pVVar7->vz - pVVar5->vz;

			if (x < 1)
				iVar15 = (int)(((data->cp->ap).carCos)->colBox).vy;
			else
				iVar15 = data->size->vy;

			if (iVar15 < x)
				return;

			x = data->size->vx * road_s;
			iVar15 = data->size->vz * road_c;
			iVar9 = FIXED(y * road_s + x_00 * road_c);

			if (x < 0)
				x = -x;

			if (iVar15 < 0)
				iVar15 = -iVar15;

			someTempVar = FIXED(x + iVar15);
			x = FIXED(y * road_c - x_00 * road_s);

			if ((data->intention == 0) || ((data->cp->ai.l).dstate == 3)) 
			{
				x_00 = iVar9;
				if (iVar9 < 0)
					x_00 = -iVar9;

				y = ((data->cp->hd).speed + 100) * 10;

				if (x_00 < y) 
				{
					x_00 = x;

					if (x < 0) 
						x_00 = -x;

					if (x_00 < y) 
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
			}

			if (iVar9 + someTempVar < 0)
				return;

			x_00 = data->size->vx * road_c;
			y = data->size->vz * road_s;

			if (x_00 < 0)
				x_00 = -x_00;

			if (y < 0)
				y = -y;

			pVVar5 = data->vel;
			offx = FIXED(x_00 + y) + carWidth * 2;

			if (pVVar5 != NULL) 
			{
				x_00 = pVVar5->vx * road_s + pVVar5->vz * road_c + 0x800;
				y = FIXED(x_00) - (x_00 >> 0x1f) >> 1;
				iVar9 = iVar9 + y;
				x_00 = y;

				if (y < 0)
					x_00 = -y;

				someTempVar = someTempVar + x_00;

				if ((y < 0) && (data->intention == 0))
					iVar9 = iVar9 / 2;
	
			}
			rdist = (iVar9 - someTempVar) - carLength;

			if (rdist < 0)
				rdist = 0;

			pVVar5 = data->vel;
			left = x - offx;
			x = x + offx;
			right = x;
			if (pVVar5 != NULL) 
			{
				x_00 = FIXED(pVVar5->vx * road_c + pVVar5->vz * road_s);
				right = x + x_00;

				if (x_00 < 1) 
				{
					left = left - x_00;
					right = x;
				}
			}
			break;
		case 1:
			pVVar5 = data->pos;
			curve = Driver2CurvesPtr + (data->cp->ai.l).currentRoad + -0x4000;
			y = pVVar5->vx - curve->Midx;
			x = data->base->vy - pVVar5->vy;
			x_00 = pVVar5->vz - curve->Midz;

			if (x < 1)
				iVar15 = (int)(((data->cp->ap).carCos)->colBox).vy;
			else
				iVar15 = data->size->vy;

			if (iVar15 < x)
				return;

			lVar3 = ratan2(y, x_00);
			iVar9 = data->size->vx;
			uVar13 = lVar3 + 0x400U & 0xfff;
			iVar12 = (int)rcossin_tbl[uVar13 * 2];
			x = iVar9 * iVar12;
			iVar8 = data->size->vz;
			iVar11 = (int)rcossin_tbl[uVar13 * 2 + 1];
			iVar15 = iVar8 * iVar11;
			iVar14 = (((lVar3 - (data->cp->ai.l).base_Angle) + 0x800U & 0xfff) - 0x800) *
				(data->cp->ai.l).base_Dir * ((int)(curve->inside * 0xb000) / 0x7000);
			if (x < 0)
				x = -x;

			if (iVar15 < 0)
				iVar15 = -iVar15;

			someTempVar = FIXED(x + iVar15);

			if (iVar14 + someTempVar < 0)
				return;

			iVar9 = iVar9 * iVar11;
			iVar8 = iVar8 * iVar12;
			if (iVar9 < 0)
				iVar9 = -iVar9;

			if (iVar8 < 0)
				iVar8 = -iVar8;

			pVVar5 = data->vel;
			offx = FIXED(iVar9 + iVar8) + carWidth;

			if (pVVar5 != NULL) 
			{
				x = pVVar5->vx * iVar12 + pVVar5->vz * iVar11 + 0x800;
				iVar15 = FIXED(x) - (x >> 0x1f) >> 1;
				iVar14 = iVar14 + iVar15;
				x = iVar15;

				if (iVar15 < 0)
					x = -iVar15;

				someTempVar = someTempVar + x;
				if (iVar15 < 0)
					iVar14 = iVar14 / 2;

			}
			x = (iVar14 - someTempVar) - carLength;

			if (x < 0)
				x = 0;

			iVar15 = (data->cp->ai.l).base_Normal;
			uVar2 = hypot(y, x_00);
			cp = data->cp;
			y = (iVar15 - uVar2) * cp->ai.l.base_Dir;
			x_00 = ((cp->hd).speed + 100) * 10;
			if (x < x_00)
			{
				iVar15 = y;

				if (y < 0) 
					iVar15 = -y;

				if (iVar15 < x_00) 
				{
					newdata.base = data->base;
					newdata.pos = data->pos;
					newdata.vel = data->vel;
					newdata.size = data->size;
					newdata.intention = 6;
					newdata.map = data->local;
					newdata.local = NULL;
					newdata.cp = cp;
					BlockToMap(&newdata);
				}
			}

			pVVar5 = data->vel;
			left = y - offx;
			y = y + offx;
			right = y;
			rdist = x;

			if (pVVar5 != NULL)
			{
				x = FIXED(pVVar5->vx * iVar11 + pVVar5->vz * iVar12);
				right = y + x;
				if (x < 1) 
				{
					left = left - x;
					right = y;
				}
			}

			break;
		case 4:
		case 5:
		case 6:
			pVVar7 = data->pos;
			pVVar5 = data->base;
			x_00 = pVVar7->vx - pVVar5->vx;
			x = pVVar5->vy - pVVar7->vy;
			y = pVVar7->vz - pVVar5->vz;

			if (x < 1)
				iVar15 = (int)(((data->cp->ap).carCos)->colBox).vy;
			else
				iVar15 = data->size->vy;
	
			if (iVar15 < x)
				return;
	
			uVar2 = hypot(x_00, y);
			lVar3 = ratan2(x_00, y);
			uVar13 = (lVar3 + 0x800U & 0xfff) - 0x800;
			pVVar5 = data->size;
			iVar9 = pVVar5->vx;
			x = iVar9 * (int)rcossin_tbl[(uVar13 & 0xfff) * 2];
			iVar15 = pVVar5->vz * (int)rcossin_tbl[(uVar13 & 0xfff) * 2 + 1];

			if (x < 0)
				x = -x;

			if (iVar15 < 0)
				iVar15 = -iVar15;
	
			someTempVar = FIXED(x + iVar15);
			x = (uVar2 - someTempVar) - carLength;

			if ((x < 2000) ||
				(iVar15 = iVar9 * (int)rcossin_tbl[(uVar13 & 0xfff) * 2 + 1], data->intention == 6)) 
			{
				corners[0][0] = x_00 + iVar9;
				corners[2][0] = x_00 - pVVar5->vx;
				corners[0][1] = y + pVVar5->vz;
				corners[1][1] = y - pVVar5->vz;
				corners[1][0] = corners[0][0];
				corners[2][1] = corners[0][1];
				corners[3][0] = corners[2][0];
				corners[3][1] = corners[1][1];
				corners[0][2] = ratan2(corners[0][0], corners[0][1]);
				corners[1][2] = ratan2(corners[1][0], corners[1][1]);
				corners[2][2] = ratan2(corners[2][0], corners[2][1]);
				corners[3][2] = ratan2(corners[3][0], corners[3][1]);

				bVar1 = false;
				x_00 = 1;
				left = 0;
				right = 0;
				x = corners[0][2] + 0x800 >> 10;
				//tangent = corners + 5;	// corners[1][2] = 5

				do {
					y = corners[x_00][2];

					if (0 < (int)(((corners[left][2] - y) + 0x800U & 0xfff) - 0x800)) 
						left = x_00;

					if (0 < (int)(((y - corners[right][2]) + 0x800U & 0xfff) - 0x800))
						right = x_00;

					iVar15 = y + 0x800 >> 10;
					if ((x != iVar15) && (x + (x - (corners[0][2] + 0x800 >> 0x1f) >> 1) * -2 == iVar15 + (iVar15 - (y + 0x800 >> 0x1f) >> 1) * -2))
						bVar1 = true;

					x_00 = x_00 + 1;
					//tangent = tangent + 3;
				} while (x_00 < 4);

				if (bVar1) 
				{
					rdist = 0;
					right = uVar13 - (data->cp->hd).direction;
					left = right + -0x200;
					right = right + 0x200;
				}
				else if (left + right == 3)
				{
					uVar2 = 0xffffffff;
					x = 0;
					do {

						if (((x != left) && (x != right)) && ((uVar4 = hypot(corners[x][0], corners[x][1]), uVar4 < uVar2 || (uVar2 == 0xffffffff))))
						{
							uVar2 = uVar4;
						}

						x = x + 1;

					} while (x < 4);

					x = (data->cp->hd).direction;
					left = corners[left][2] - x;
					right = corners[right][2] - x;
					rdist = uVar2;
				}
				else
				{
					lVar3 = ratan2(corners[left][0] - corners[right][0], corners[left][1] - corners[right][1]);
					uVar13 = (lVar3 + 0xc00U & 0xfff) - 0x800 & 0xfff;

					y = (data->cp->hd).direction;

					rdist = FIXED(rcossin_tbl[uVar13 * 2] * corners[left][0] + rcossin_tbl[uVar13 * 2 + 1] * corners[left][1]);

					left = corners[left][2] - y;
					right = corners[right][2] - y;

					if (rdist < 0)
						rdist = -rdist;

				}

				left = (left + 0x800U & 0xfff) - 0x800;
				right = (right + 0x800U & 0xfff) - 0x800;
			}
			else
			{
				x_00 = pVVar5->vz * (int)rcossin_tbl[(uVar13 & 0xfff) * 2];
				y = ((uVar13 - (data->cp->hd).direction) + 0x800 & 0xfff) - 0x800;

				if (iVar15 < 0)
					iVar15 = -iVar15;

				if (x_00 < 0)
					x_00 = -x_00;

				offx = ratan2(FIXED(iVar15 + x_00) + carWidth, x);
				left = y - offx;
				right = y + offx;
				rdist = x;
			}

			break;
		default:
			goto LAB_LEAD__000e97b4;
	}

	ldist = rdist;

	switch (data->intention)
	{
		case 2:
		case 3:
			tangent = &rdist;
			tangent_00 = &ldist;
			normal = &left;
			normal_00 = &right;

			if (data->intention != 2)
			{
				normal_00 = &left;
				tangent = &ldist;
				tangent_00 = &rdist;
				normal = &right;
			}

			x = LeadValues.hWidth + (data->cp->hd).speed * LeadValues.hWidthMul;

			if ((x < ldist) && (x < rdist))  // [A] was rdist; ghidra bug?
			{
				*tangent_00 = *tangent_00 + carLength * 2;
				x = *tangent + carLength * -2;
				*tangent = x;

				if (x < 0)
					*tangent = 0;

				left = left - carWidth;
				right = right + carWidth;
				temp = *normal;
				tdist = *tangent_00 + someTempVar * 2;

				PosToIndex(&temp, &tdist, data->intention, data->cp);
				PosToIndex(normal, tangent_00, data->intention, data->cp);
				PosToIndex(normal_00, tangent, data->intention, data->cp);

				*normal = temp;
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
			localld = rdist;
			localrd = rdist;
			PosToIndex(&locall, &localld, 6, data->cp);
			PosToIndex(&localr, &localrd, 6, data->cp);

			uVar13 = locall;

			if (localr < locall) 
			{
				while ((int)uVar13 < 0x29) 
				{
					if ((uVar13 < 0x29) && (localld < data->local[uVar13])) 
						data->local[uVar13] = localld;

					uVar13 = uVar13 + 1;
				}

				left = -0x800;
				PosToIndex(&locall, &localld, 6, data->cp);
				uVar13 = locall;

				if (localr < locall)
					goto LAB_LEAD__000e96f0;

			}
			while ((int)uVar13 <= localr) 
			{
				if ((uVar13 < 0x29) && (localld < data->local[uVar13]))
					data->local[uVar13] = localld;

				uVar13 = uVar13 + 1;
			}
		case 5:
		case 6:
		LAB_LEAD__000e96f0:
			PosToIndex(&left, &ldist, data->intention, data->cp);
			PosToIndex(&right, &rdist, data->intention, data->cp);
			x = ldist;

			if (right < left) 
			{
				while (left < 0x29)
				{
					if (((-1 < left) && (left < 0x29)) && (x < data->map[left])) 
						data->map[left] = x;

					left = left + 1;
				}

				left = -0x800;
				PosToIndex(&left, &ldist, data->intention, data->cp);
			}

			break;
		default:
			break;
	}
LAB_LEAD__000e97b4:
	y = right;
	x = left;
	x_00 = ldist;

	if (left < right)
		iVar15 = (rdist - ldist) / (right - left);
	else 
		iVar15 = 0;

	while (x <= y) 
	{
		if (((-1 < x) && (x < 0x29)) && (x_00 < data->map[x]))
		{
			data->map[x] = x_00;
		}

		x = x + 1;
		x_00 = x_00 + iVar15;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ IsOnMap(int x /*$t0*/, int z /*$a1*/, struct VECTOR *basePos /*$a2*/, int intention /*$s4*/, struct _CAR_DATA *cp /*stack 16*/)
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
		// 		struct DRIVER2_CURVE *curve; // $s0
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

// [D]
int IsOnMap(int x, int z, VECTOR *basePos, int intention, _CAR_DATA *cp)
{
	DRIVER2_CURVE* curve;
	int dx;
	int dz;
	int normal;
	int tangent;

	dx = x - basePos->vx;

	if (dx < 0)
		dx = -dx;

	dz = z - basePos->vz;

	if (dx < 3000)
	{
		if (dz < 0)
			dz = -dz;

		if (dz < 3000)
			return 1;
	}

	switch (intention) 
	{
		case 0:
		case 2:
		case 3:
			tangent = FIXED(dx * road_s + dz * road_c);
			normal = FIXED(dx * road_c - dz * road_s);
			PosToIndex(&normal, &tangent, intention, cp);
			break;
		case 1:
			curve = Driver2CurvesPtr + cp->ai.l.currentRoad - 0x4000;

			x = x - curve->Midx;
			z = z - curve->Midz;

			tangent = (((ratan2(x, z) - cp->ai.l.base_Angle) + 0x800U & 0xfff) - 0x800) * cp->ai.l.base_Dir *(((int)curve->inside * 0xb000) / 0x7000);
			normal = (cp->ai.l.base_Normal - hypot(x, z)) * cp->ai.l.base_Dir;

			PosToIndex(&normal, &tangent, intention, cp);
			break;
		case 4:
		case 5:
			tangent = hypot(dx, dz);
			normal = ((ratan2(dx, dz) - (cp->hd).direction) + 0x800U & 0xfff) - 0x800;

			PosToIndex(&normal, &tangent, intention, cp);

			if (tangent > 7000)
				return 0;

			if (normal > -1 && normal < 42)
				return 1;

		default:
			return 0;
	}

	if (0x5800 < tangent + 0x800U)
		return 0;

	if (normal < -4)
		return 0;

	if (normal < 0x2e)
		return 1;

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateRoadPosition(struct _CAR_DATA *cp /*$s3*/, struct VECTOR *basePos /*stack 4*/, int intention /*stack 8*/)
 // line 1657, offset 0x000e9bb8
	/* begin block 1 */
		// Start line: 1658
		// Start offset: 0x000E9BB8
		// Variables:
	// 		int sindex; // $t0
	// 		int i; // $s0
	// 		int di; // $a2
	// 		struct _CAR_DATA *lcp; // $s0
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
					// 		struct CELL_OBJECT *cop; // $s1
					// 		struct CELL_ITERATOR ci; // stack offset -344

						/* begin block 1.1.1.1.1.1 */
							// Start line: 1721
							// Start offset: 0x000E9DB0
							// Variables:
						// 		struct COLLISION_PACKET *collide; // $s0
						// 		struct MODEL *model; // $a0
						// 		int num_cb; // $a0
						// 		int box_loop; // $s2

							/* begin block 1.1.1.1.1.1.1 */
								// Start line: 1739
								// Start offset: 0x000E9E4C
								// Variables:
							// 		struct MATRIX *mat; // $a1
							// 		struct VECTOR offset; // stack offset -320
							// 		struct VECTOR vel; // stack offset -304
							// 		struct VECTOR size; // stack offset -288
							// 		struct MAP_DATA data; // stack offset -272

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
		// 		struct SVECTOR *colBox; // $a3
		// 		struct VECTOR pos; // stack offset -344
		// 		struct VECTOR vel; // stack offset -328
		// 		struct VECTOR size; // stack offset -312
		// 		struct MAP_DATA data; // stack offset -296
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
		// 		struct _CAR_DATA *cp; // $s3
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
void UpdateRoadPosition(_CAR_DATA *cp, VECTOR *basePos, int intention)
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
	_CAR_DATA* lcp;
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

	iVar16 = 0x28;
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
						if (((((uint)model->num_vertices - 3 < 300) && (model->num_point_normals < 300)) &&
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

										size.vx = FIXED(iVar9 + iVar10);
										size.vy = (long)collide->ysize;

										if (iVar14 < 0)
											iVar14 = -iVar14;

										if (iVar8 < 0)
											iVar8 = -iVar8;
	
										size.vz = FIXED(iVar14 - iVar8);
									}
									offset.vx = FIXED(collide->xpos * matrixtable[uVar6].m[0][0] + collide->zpos * matrixtable[uVar6].m[2][0]) + (cop->pos).vx;
									offset.vz = FIXED(collide->xpos * matrixtable[uVar6].m[0][2] + collide->zpos * matrixtable[uVar6].m[2][2]) + (cop->pos).vz;
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

	} while (iVar16 < 0xb);

	lcp = (car_data + 0x13);

	while (car_data < lcp)
	{
		if ((lcp != cp) && (lcp->controlType != 0))
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

			size.vx = FIXED(iVar16 + iVar13) + (int)(car_cos->colBox).vy;
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

			size.vz = FIXED(iVar16 + iVar13) + (int)(car_cos->colBox).vy;

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

	if ((cp->ai.l.dstate != 4) && (((iVar16 = ((cp->hd).speed + 100) * 8, localMap[20] < iVar16 || (localMap[21] < iVar16)) || (localMap[22] < iVar16))))
	{
		iVar16 = 1;
		piVar7 = localMap + 0x17;
		piVar5 = localMap + 0x13;

		while (true) 
		{
			iVar11 = *piVar5 + localMap[0x15 - iVar16] + localMap[0x16 - iVar16];
			iVar13 = piVar7[-2] + piVar7[-1] + *piVar7;

			if ((iVar11 < iVar13) && (((cp->hd).speed + 100) * 0x18 < iVar13 * 2))
			{
				if (0xd < iVar16) 
				{
					cp->ai.l.panicCount = 2;
					return;
				}

				cp->ai.l.panicCount = 1;
				return;
			}

			if ((iVar11 > iVar13) && (((cp->hd).speed + 100) * 0x18 < iVar11 * 2))
				break;

			if (iVar16 == 0x14) 
			{
				if (iVar11 <= iVar13) 
					cp->ai.l.panicCount = 2;
				else 
					cp->ai.l.panicCount = -2;
			}

			piVar7 = piVar7 + 1;
			iVar16 = iVar16 + 1;
			piVar5 = piVar5 + -1;

			if (0x14 < iVar16) 
				return;
		}
		if (0xd < iVar16)
		{
			cp->ai.l.panicCount = -2;
			return;
		}

		cp->ai.l.panicCount = -1;
		return;
	}

	cp->ai.l.panicCount = 0;
	bVar3 = intention < 2;
	cellx = intention - 2;

	if (bVar3) 
	{
		iVar13 = 0x18;
		piVar7 = roadAhead + 0x18;
		iVar16 = roadAhead[24];

		do {
			if (*piVar7 < iVar16)
				iVar16 = *piVar7;

			lVar4 = SquareRoot0(iVar13 + -0x15);

			if (iVar16 < ((cp->hd).speed + 100) * lVar4)
				*piVar7 = 0;

			iVar13 = iVar13 + 1;
			piVar7 = piVar7 + 1;
		} while (iVar13 < 0x29);

		iVar13 = 0x12;
		piVar7 = roadAhead + 0x12;
		iVar16 = roadAhead[18];

		do {
			if (*piVar7 < iVar16)
				iVar16 = *piVar7;

			lVar4 = SquareRoot0(0x15 - iVar13);

			if (iVar16 < ((cp->hd).speed + 100) * lVar4)
				*piVar7 = 0;

			iVar13 = iVar13 + -1;
			piVar7 = piVar7 + -1;
		} while (-1 < iVar13);
	}

	if (cellx < 2)
	{
		piVar5 = roadAhead;
		iVar16 = 0x28;
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

			if ((int)cellz < iVar16 + 4) 
			{
				piVar7 = tmpMap + cellz;
				do {
					if (cellz < 0x29) {
						roadAhead[iVar16] = roadAhead[iVar16] + *piVar7;
					}
					piVar7 = piVar7 + 1;
					cellz = cellz + 1;
					iVar13 = iVar13 + 1;
				} while ((int)cellz < iVar16 + 4);
			}
			if (iVar13 == 0) {
				trap(7);
			}
			roadAhead[iVar16] = roadAhead[iVar16] / iVar13;
			iVar16 = iVar11;
		} while (iVar11 < 0x29);
	}

	if (intention == 4) 
	{
		iVar11 = 0;
		iVar13 = 0x3f;
		iVar16 = -0x15;
		piVar7 = roadAhead;
		do {
			iVar9 = *piVar7 * 0x15;
			*piVar7 = iVar9;

			if (iVar11 + -0x15 < 0)
				*piVar7 = iVar9 / iVar13;
			else 
				*piVar7 = iVar9 / iVar16;

			iVar13 = iVar13 + -2;
			iVar16 = iVar16 + 2;
			iVar11 = iVar11 + 1;
			piVar7 = piVar7 + 1;
		} while (iVar11 < 0x29);
	}

	if ((bVar3) && (cp->ai.l.nextTurn < 10))
	{
		iVar16 = cp->ai.l.boringness;

		if (iVar16 < 0x1f) 
		{
			iVar9 = cp->ai.l.width;
			iVar11 = cp->ai.l.roadPosition;
			iVar10 = iVar9 - cp->ai.l.d;
			iVar13 = iVar11 - iVar10;
			if (iVar13 < 0)
				iVar13 = iVar10 - iVar11;

			if ((iVar13 < iVar9 / 3) && (iVar16 < 0x1f))
				cp->ai.l.boringness = iVar16 + 1;

		}
		else
		{
			iVar11 = cp->ai.l.width;
			iVar13 = cp->ai.l.roadPosition;
			iVar9 = iVar11 - cp->ai.l.d;
			iVar16 = iVar13 - iVar9;

			if (iVar16 < 0)
				iVar16 = iVar9 - iVar13;

			if (iVar16 < iVar11 / 3) 
			{
				cp->ai.l.avoid = cp->ai.l.width - cp->ai.l.d;
				cp->ai.l.boringness = cp->ai.l.boringness + 1;
			}

			iVar11 = 0;
			piVar7 = roadAhead;
			laneAvoid = ((cp->ai.l.avoid + cp->ai.l.d) - cp->ai.l.width) / 100 + 0x15;
			iVar13 = laneAvoid * 100;
			iVar16 = laneAvoid * -100;

			do {
				iVar9 = iVar16;

				if (-1 < laneAvoid - iVar11)
					iVar9 = iVar13;

				if (iVar9 < cp->ai.l.width / 3)
					*piVar7 = *piVar7 + cp->ai.l.boringness * -100;

				piVar7 = piVar7 + 1;
				iVar16 = iVar16 + 100;
				iVar11 = iVar11 + 1;
				iVar13 = iVar13 + -100;
			} while (iVar11 < 0x29);

			iVar9 = cp->ai.l.width;
			iVar16 = iVar9 / 3;
			iVar11 = cp->ai.l.avoid;
			iVar9 = iVar9 - cp->ai.l.d;
			iVar13 = iVar9 - iVar11;

			if (iVar13 < 0) 
			{
				if (iVar16 < iVar11 - iVar9)
					cp->ai.l.boringness = 0;
			}
			else
			{
				if (iVar16 < iVar13) 
					goto LAB_LEAD__000ea89c;
			}
		}
	}
	else 
	{
	LAB_LEAD__000ea89c:
		cp->ai.l.boringness = 0;
	}

	if (1 < intention - 4U) 
	{
		centre = cp->ai.l.d;
		right = cp->ai.l.width;
		i = 0;
		left = centre - right;
		right = right + centre;

		PosToIndex(&left, &i, intention, cp);
		PosToIndex(&right, &i, intention, cp);
		PosToIndex(&centre, &i, intention, cp);

		if ((left < centre) && (centre < right)) 
		{
			iVar16 = cp->ai.l.nextTurn;
			if (((iVar16 == 0xf) || (iVar16 == 0x11)) && (1 < cellx)) 
			{
				cp->ai.l.nextTurn = iVar16 + -0x10;
				i = left;
				while (i <= right)
				{
					iVar16 = 2000;

					if (0 < (i - centre) * cp->ai.l.nextTurn)
						iVar16 = -2000;

					if (i < 0x29) 
					{
						iVar13 = roadAhead[i];

						if (0 < iVar13)
							roadAhead[i] = iVar13 + iVar16;

					}
					i = i + 1;
				}
			}
			iVar16 = 0;

			// [A] bug fix
			if (left < 0)
				left = 0;

			if (right < 0)
				right = 0;

			while (left < 0x29)
			{
				roadAhead[left] = roadAhead[left] - iVar16;

				if (roadAhead[left] < 0)
					roadAhead[left] = 0;

				left++;
				iVar16 = iVar16 + 500;
			}

			iVar16 = 0;

			while (right < 0x29) 
			{
				roadAhead[right] = roadAhead[right] - iVar16;

				if (roadAhead[right] < 0)
					roadAhead[right] = 0;

				right++;
				iVar16 = iVar16 + 500;
			}
		}
	}

	if (cellx < 3)
	{
	LAB_LEAD__000ead84:
		cellz = 0x15;
		uVar17 = 0x15;
		uVar6 = 0;
		iVar13 = 0x54;
		iVar16 = roadAhead[21];
		do {
			if (iVar16 < *(int*)((int)roadAhead + iVar13)) 
			{
				iVar16 = *(int*)((int)roadAhead + iVar13);
				cellz = uVar17;
			}

			if ((int)uVar6 < 0)
				uVar6 = -uVar6;

			uVar6 = uVar6 + 1;
			if ((uVar6 & 1) == 0) {
				uVar6 = -uVar6;
			}
			uVar17 = uVar17 + uVar6;
			iVar13 = uVar17 * 4;
		} while (uVar17 < 0x29);

		if (cellx < 2) 
		{
			iVar13 = (cp->hd).speed;

			if (iVar13 < 0x65) 
				iVar13 = LeadValues.tDist + iVar13 * LeadValues.tDistMul;
			else
				iVar13 = LeadValues.hDist + (iVar13 + -100) * LeadValues.hDistMul;


			if (iVar16 < iVar13) 
			{
				iVar16 = cp->ai.l.roadForward;
				iVar13 = iVar16 + -1;

				if (-1 < iVar16)
					iVar13 = -1;

				cp->ai.l.roadForward = iVar13;
				local_v0_4816 = 0x4e20;

				if (intention == 3)
					local_v0_4816 = 0xffffb1e0;

				cp->ai.l.roadPosition = local_v0_4816;

				if (-0x15 < cp->ai.l.roadForward)
					return;

				SelectExit(cp, Driver2JunctionsPtr + cp->ai.l.nextJunction + -0x2000);
				return;
			}
		}
	}
	else 
	{
		iVar16 = cp->ai.l.boringness;
		cellz = cp->ai.l.lastTarget;

		if (iVar16 < 0x1f) 
		{
		LAB_LEAD__000eac54:
			iVar16 = cellz - 1;
			if (iVar16 < 0) 
			{
				iVar13 = 0;
			}
			else 
			{
				iVar13 = iVar16 * 4;

				if (0x28 < iVar16) 
					iVar13 = 0xa0;
			}

			iVar16 = (cp->hd).speed;
			if (*(int*)((int)roadAhead + iVar13) <= ((iVar16 + 100) / 0x32) * 0x400)
			{
				if ((int)cellz < 0)
				{
					iVar13 = 0;
				}
				else 
				{
					uVar6 = cellz;
					if (0x28 < (int)cellz)
					{
						uVar6 = 0x28;
					}
					iVar13 = uVar6 << 2;
				}

				if (*(int*)((int)roadAhead + iVar13) <= ((iVar16 + 100) / 0x32) * 0x400)
				{
					iVar13 = cellz + 1;
					if (iVar13 < 0) 
					{
						iVar11 = 0;
					}
					else 
					{
						iVar11 = iVar13 * 4;
						if (0x28 < iVar13)
							iVar11 = 0xa0;
					}

					if (*(int*)((int)roadAhead + iVar11) <= ((iVar16 + 100) / 0x32) * 0x400)
						goto LAB_LEAD__000ead84;
				}
			}
		}
		else 
		{
			iVar13 = (cellz - laneAvoid) * 100;
			if (iVar13 < 0)
				iVar13 = (cellz - laneAvoid) * -100;


			if (iVar13 < cp->ai.l.width / 3)
				goto LAB_LEAD__000ead84;

			iVar13 = cellz - 1;
			if (iVar13 < 0) 
			{
				iVar11 = 0;
			}
			else
			{
				iVar11 = iVar13 * 4;
				if (0x28 < iVar13)
					iVar11 = 0xa0;

			}

			iVar13 = (cp->hd).speed;

			if (*(int*)((int)roadAhead + iVar11) <= ((iVar13 + 100) / 0x32) * 0x400) 
			{
				if ((int)cellz < 0) 
				{
					iVar11 = 0;
				}
				else 
				{
					uVar6 = cellz;

					if (0x28 < (int)cellz)
						uVar6 = 0x28;

					iVar11 = uVar6 << 2;
				}
				if (*(int*)((int)roadAhead + iVar11) <= ((iVar13 + 100) / 0x32) * 0x400)
				{
					iVar11 = cellz + 1;
					if (iVar11 < 0) 
					{
						iVar9 = 0;
					}
					else 
					{
						iVar9 = iVar11 * 4;
						if (0x28 < iVar11)
							iVar9 = 0xa0;

					}
					if (*(int*)((int)roadAhead + iVar9) <= ((iVar13 + 100) / 0x32) * 0x400)
						goto LAB_LEAD__000ead84;
				}
			}
			if (iVar16 < 0x1f) goto LAB_LEAD__000eac54;
		}
		iVar16 = roadAhead[cellz];
		uVar6 = cellz - 2;
		iVar13 = cellz + 2;

		if ((int)uVar6 < iVar13)
		{
			piVar7 = roadAhead + uVar6;
			do {
				if ((uVar6 < 0x29) && (iVar16 < *piVar7)) 
				{
					iVar16 = *piVar7;
					cellz = uVar6;
				}

				uVar6 = uVar6 + 1;
				piVar7 = piVar7 + 1;
			} while ((int)uVar6 < iVar13);
		}
	}

	if ((bVar3) || (intention == 4)) 
	{
		cp->ai.l.roadForward = 0x1400;
		iVar16 = 1;

		if (0x15 < (int)cellz) 
			iVar16 = -1;

		if (cellz != 0x15) 
		{
			piVar7 = roadAhead + cellz;
			uVar6 = cellz;

			do {
				if (*piVar7 < cp->ai.l.roadForward)
					cp->ai.l.roadForward = *piVar7;

				uVar6 = uVar6 + iVar16;
				piVar7 = piVar7 + iVar16;
			} while (uVar6 != 0x15);

			cp->ai.l.lastTarget = cellz;
			goto LAB_LEAD__000eb0c8;
		}
	}
	else 
	{
		if (intention == 5)
		{
			iVar16 = cp->ai.l.recoverTime;

			if ((iVar16 == 0) || (0x14 < iVar16))
			{
				piVar7 = roadAhead + 0x14;
				iVar13 = 3;
				cp->ai.l.recoverTime = 0;
				iVar16 = roadAhead[19];

				do {
					if (*piVar7 < iVar16)
						iVar16 = *piVar7;

					iVar13 = iVar13 + -1;
					piVar7 = piVar7 + 1;
				} while (-1 < iVar13);

				iVar13 = -1;

				if (roadAhead[38] <= iVar16)
					iVar13 = 1;

				cp->ai.l.roadForward = iVar13;
			}

			if ((((0x5dc < roadAhead[21]) && (0x5dc < roadAhead[22])) && (0x5dc < roadAhead[20])) && (0x28 < (cp->hd).speed)) 
			{
				cp->ai.l.roadForward = 0;
			}
		}
		else
		{
			cp->ai.l.roadForward = 0;
		}
	}

	cp->ai.l.lastTarget = cellz;

LAB_LEAD__000eb0c8:
	iVar16 = cellz - 0x15;

	if (intention == 6) 
	{
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	if (intention - 4U < 2) 
	{
		if (intention == 4)
			iVar16 = iVar16 * 0x600;
		else
			iVar16 = iVar16 * 0x800;

		iVar16 = ((iVar16 / 0x15 + 0x800U & 0xfff) + (cp->hd).direction & 0xfff) - 0x800;
	}
	else 
	{
		if (bVar3) 
		{
			iVar16 = (iVar16 * 200 + cp->ai.l.width) - cp->ai.l.d;
		}
		else 
		{
			if (1 < cellx)
				return;

			iVar16 = iVar16 * 100 + cp->ai.l.width;
		}
	}

	cp->ai.l.roadPosition = iVar16;
}


// decompiled code
// original method signature: 
// void /*$ra*/ CheckCurrentRoad(struct _CAR_DATA *cp /*$s3*/)
 // line 2242, offset 0x000eb1fc
	/* begin block 1 */
		// Start line: 2243
		// Start offset: 0x000EB1FC
		// Variables:
	// 		static int heading; // offset 0x1c
	// 		int cr; // $s5
	// 		static int jdist; // offset 0x20
	// 		static int nextJunction; // offset 0x50
	// 		static struct VECTOR basePosition; // offset 0x60
	// 		int checkNext; // $s6

		/* begin block 1.1 */
			// Start line: 2278
			// Start offset: 0x000EB300
			// Variables:
		// 		struct DRIVER2_STRAIGHT *straight; // $t3
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
		// 		struct DRIVER2_CURVE *curve; // $s2
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
			// 		struct DRIVER2_JUNCTION *junction; // $s0
			/* end block 1.3.1 */
			// End offset: 0x000EB9D4
			// End Line: 2428

			/* begin block 1.3.2 */
				// Start line: 2440
				// Start offset: 0x000EBA14
				// Variables:
			// 		struct DRIVER2_STRAIGHT *straight; // $v1
			/* end block 1.3.2 */
			// End offset: 0x000EBA5C
			// End Line: 2446

			/* begin block 1.3.3 */
				// Start line: 2449
				// Start offset: 0x000EBA5C
				// Variables:
			// 		struct DRIVER2_CURVE *curve; // $v1
			// 		static int dx; // offset 0x9c
			// 		static int dz; // offset 0xa0
			/* end block 1.3.3 */
			// End offset: 0x000EBAE8
			// End Line: 2460

			/* begin block 1.3.4 */
				// Start line: 2475
				// Start offset: 0x000EBB2C
				// Variables:
			// 		struct DRIVER2_STRAIGHT *straight; // $t1
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
			// 		struct DRIVER2_CURVE *curve; // $s4
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

// [D]
void CheckCurrentRoad(_CAR_DATA *cp)
{
	static int heading; // offset 0x1c
	static int nextJunction; // offset 0x50
	static VECTOR basePosition; // offset 0x60

	bool bVar1;
	int iVar2;
	long lVar3;
	long uVar4;
	int cr;
	int iVar5;
	DRIVER2_STRAIGHT* straight;
	DRIVER2_JUNCTION* junction;
	DRIVER2_CURVE* curve;
	int iVar6;
	int cr_00;

	bVar1 = false;

	if ((((cp->hd).wheel[1].surface & 7) == 3) || (((cp->hd).wheel[3].surface & 7) == 3))
		cr_00 = cp->ai.l.currentRoad;
	else
		cr_00 = GetSurfaceIndex((VECTOR*)(cp->hd).where.t);

	cr = cr_00 & 0xffffe000;
	if (((cr == 0) || (cr == 0x4000)) || (cr == 0x2000)) 
	{
		cp->ai.l.offRoad = 0;
		if ((cr_00 != cp->ai.l.lastRoad) && (cr_00 != cp->ai.l.currentRoad))
		{
			cp->ai.l.direction = 0;
		}
	}
	else
	{
		cr_00 = cp->ai.l.lastRoad;
		cp->ai.l.direction = cp->ai.l.lastDirection;
	}

	cr = cr_00 & 0xffffe000;

	if (cr == 0x2000) 
	{
		bVar1 = true;
		nextJunction = cr_00;
		goto LAB_LEAD__000eb96c;
	}

	if (cr < 0x2001) 
	{
		if (cr == 0)
		{
 			static int d; // offset 0x70
 			static int toGo; // offset 0x74
 			static int angle; // offset 0x78
 			static int s; // offset 0x7c
 			static int c; // offset 0x80

			straight = Driver2StraightsPtr + cr_00;
			angle = (uint)(ushort)straight->angle & 0xfff;
			iVar5 = (cp->hd).where.t[2] - straight->Midz;
			nextJunction = (int)straight->ConnectIdx[1];
			iVar6 = (cp->hd).where.t[0] - straight->Midx;

			if (nextJunction == -1)
				nextJunction = (int)straight->ConnectIdx[0];

			if (cp->ai.l.direction == 0)
			{
				iVar2 = -1;
				if ((((cp->hd).direction - angle) + 0x400 & 0x800) == 0) {
					iVar2 = 1;
				}
				cp->ai.l.direction = iVar2;
			}

			if (cp->ai.l.direction == -1)
			{
				angle = angle ^ 0x800;
				nextJunction = (int)straight->ConnectIdx[3];
				if (nextJunction == -1) {
					nextJunction = (int)straight->ConnectIdx[2];
				}
			}

			s = (int)rcossin_tbl[(angle & 0xfff) * 2];
			c = (int)rcossin_tbl[(angle & 0xfff) * 2 + 1];
			d = FIXED(s * iVar6 + c * iVar5);
			iVar2 = (cp->hd).speed;
			toGo = (uint)(straight->length >> 1) - d;

			if (iVar2 < 0x65)
				iVar2 = LeadValues.tDist + iVar2 * LeadValues.tDistMul;
			else
				iVar2 = LeadValues.hDist + (iVar2 + -100) * LeadValues.hDistMul;
	
			if (((toGo < iVar2) && (cp->ai.l.offRoad == 0)) && (cp->ai.l.dstate != 5))
			{
				bVar1 = true;
				cp->ai.l.direction = 0;
			}
			else 
			{
				iVar2 = (cp->hd).speed;
				if (iVar2 < 0x65)
					iVar2 = LeadValues.tDist + iVar2 * LeadValues.tDistMul;
				else
					iVar2 = LeadValues.hDist + (iVar2 + -100) * LeadValues.hDistMul;

				if (toGo < iVar2 * 3)
					cp->ai.l.nextTurn = cp->ai.l.nextTurn + 0x10;

				cp->ai.l.d = FIXED(-c * iVar6 + s * iVar5);
				cp->ai.l.width = ((uint)(u_char)straight->NumLanes & 0xf) << 9;
			}
			goto LAB_LEAD__000eb96c;
		}
	}
	else 
	{
		if (cr == 0x4000) 
		{
 			static int angle; // offset 0x84
 			static int radius; // offset 0x88
 			static int dx; // offset 0x8c
 			static int dz; // offset 0x90
 			static int fixedThresh; // offset 0x94

			curve = Driver2CurvesPtr + (cr_00 - 0x4000);
			dx = (cp->hd).where.t[0] - curve->Midx;
			dz = (cp->hd).where.t[2] - curve->Midz;
			angle = ratan2(dx, dz);

			if (cp->ai.l.direction == 0)
			{
				iVar6 = 1;
				if ((angle - (cp->hd).direction & 0x800U) == 0)
					iVar6 = -1;

				cp->ai.l.direction = iVar6;
			}

			if (cp->ai.l.direction == 1)
			{
				radius = ((uint)curve->inside + ((uint)(u_char)curve->NumLanes & 0xf)) * 0x400 - cp->ai.l.roadPosition;
				iVar6 = (cp->hd).speed;
				if (iVar6 < 0x65)
				{
					iVar6 = iVar6 * LeadValues.tDistMul;
					iVar5 = LeadValues.tDist;
				}
				else
				{
					iVar6 = (iVar6 + -100) * LeadValues.hDistMul;
					iVar5 = LeadValues.hDist;
				}

				fixedThresh = (iVar5 + iVar6) / radius;

				if ((fixedThresh < 0x1000) || ((curve->end - angle & 1U) == 0)) 
				{
					if ((0xfff < fixedThresh * 3) && ((curve->end - angle & 1U) != 0)) 
					{
						cp->ai.l.nextTurn = cp->ai.l.nextTurn + 0x10;
					}

					uVar4 = hypot(dx, dz);
					iVar6 = angle;
					cp->ai.l.d = uVar4;
					cp->ai.l.base_Normal = uVar4;
					cp->ai.l.base_Dir = 1;
					cp->ai.l.base_Angle = iVar6;
					cp->ai.l.d = uVar4 - ((uint)curve->inside * 0x400 + ((uint)(u_char)curve->NumLanes & 0xf) * 0x200);
				LAB_LEAD__000eb940:
					cp->ai.l.width = ((u_char)curve->NumLanes & 0xf) << 9;
					goto LAB_LEAD__000eb96c;
				}

				nextJunction = (int)curve->ConnectIdx[1];

				if (nextJunction == -1)
					nextJunction = (int)curve->ConnectIdx[0];

			}
			else 
			{
				iVar6 = (cp->hd).speed;
				radius = curve->inside * 0x400 + cp->ai.l.roadPosition;

				if (iVar6 < 0x65)
				{
					iVar6 = iVar6 * LeadValues.tDistMul;
					iVar5 = LeadValues.tDist;
				}
				else 
				{
					iVar6 = (iVar6 + -100) * LeadValues.hDistMul;
					iVar5 = LeadValues.hDist;
				}

				fixedThresh = (iVar5 + iVar6) / radius;

				if ((fixedThresh < 0x1000) || ((angle - curve->start & 1U) == 0)) 
				{
					if ((0xfff < fixedThresh * 3) && ((angle - curve->start & 1U) != 0))
						cp->ai.l.nextTurn = cp->ai.l.nextTurn + 0x10;
	
					uVar4 = hypot(dx, dz);
					iVar6 = angle;
					cp->ai.l.d = uVar4;
					cp->ai.l.base_Normal = uVar4;
					cp->ai.l.base_Dir = -1;
					cp->ai.l.base_Angle = iVar6;
					cp->ai.l.d = ((uint)curve->inside * 0x400 + ((uint)(u_char)curve->NumLanes & 0xf) * 0x200) - uVar4;
					goto LAB_LEAD__000eb940;
				}
				nextJunction = (int)curve->ConnectIdx[3];
				if (nextJunction == -1)
					nextJunction = (int)curve->ConnectIdx[2];

			}

			bVar1 = true;
			cp->ai.l.direction = 0;
			goto LAB_LEAD__000eb96c;
		}
	}
	cr_00 = cp->ai.l.lastRoad;
LAB_LEAD__000eb96c:
	cr = nextJunction;
	if (bVar1) 
	{
		static int diff;
		cr_00 = nextJunction & 0xffffe000;
		if (cr_00 == 0x2000) 
		{
			junction = Driver2JunctionsPtr + nextJunction + -0x2000;
			if (nextJunction != cp->ai.l.nextJunction)
			{
				SelectExit(cp, junction);
				cp->ai.l.nextJunction = nextJunction;
			}

			cr_00 = cp->ai.l.nextExit;
			cr = (junction->ExitIdx[cr_00]);
			heading = (cr_00 & 3) << 10;
		}
		else 
		{
			if (cr_00 == 0)
			{
				heading = (uint)(ushort)Driver2StraightsPtr[nextJunction].angle & 0xfff;

				if ((((cp->hd).direction - heading) + 0x400 & 0x800) != 0) 
				{
					heading = heading ^ 0x800;
				}
			}
			else if (cr_00 == 0x4000)
			{
				static int dx; // offset 0x9c
				static int dz; // offset 0xa0

				dx = (cp->hd).where.t[0] - Driver2CurvesPtr[nextJunction + -0x4000].Midx;
				dz = (cp->hd).where.t[2] - Driver2CurvesPtr[nextJunction + -0x4000].Midz;
				lVar3 = ratan2(dx, dz);

				if ((lVar3 - (cp->hd).direction & 0x800U) == 0)
					heading = lVar3 - 0x400U & 0xfff;
				else
					heading = lVar3 + 0x400U & 0xfff;
			}
		}
		diff = ((heading - (cp->hd).direction) + 0x800 & 0xfff) - 0x800;

		if ((cr & 0xffffe000) == 0)
		{
			static int dx; // offset 0xa4
			static int dz; // offset 0xa8
			static int dist; // offset 0xac
			static int offx; // offset 0xb0
			static int offz; // offset 0xb4

			straight = Driver2StraightsPtr + cr;
			iVar5 = (int)rcossin_tbl[(heading & 0xfff) * 2 + 1];
			offx = straight->Midx - (cp->hd).where.t[0];
			iVar6 = (int)rcossin_tbl[(heading & 0xfff) * 2];
			offz = straight->Midz - (cp->hd).where.t[2];
			dist = -FIXED(offx * iVar6 + offz * iVar5);
			cp->ai.l.d = FIXED(iVar5 * offx - iVar6 * offz);
			cp->ai.l.width = ((uint)(u_char)straight->NumLanes & 0xf) << 9;
			dx = FIXED(iVar6 * dist);
			basePosition.vx = straight->Midx + dx;
			basePosition.vy = (cp->hd).where.t[1];
			dz = FIXED(iVar5 * dist);
			basePosition.vz = straight->Midz + dz;
		}
		else if ((cr & 0xffffe000) == 0x4000)
		{
			static int angle; // offset 0xb8
			static int dx; // offset 0xbc
			static int dz; // offset 0xc0
			static int basex; // offset 0xc4
			static int basez; // offset 0xc8
			static int dist; // offset 0xcc
			static int offx; // offset 0xd0
			static int offz; // offset 0xd4

			curve = Driver2CurvesPtr + (cr - 0x4000);
			dx = (cp->hd).where.t[0] - curve->Midx;
			dz = (cp->hd).where.t[2] - curve->Midz;
			iVar6 = (uint)curve->inside * 0x400 + ((uint)(u_char)curve->NumLanes & 0xf) * 0x200;
			angle = ratan2(dx, dz);

			if ((angle - heading & 0x800) == 0)
			{
				cr_00 = (uint)(ushort)curve->end & 0xfff;
				basex = FIXED(rcossin_tbl[cr_00 * 2] * iVar6);
				basez = FIXED(rcossin_tbl[cr_00 * 2 + 1] * iVar6);
				uVar4 = hypot(dx, dz);
				lVar3 = angle;
				cp->ai.l.d = uVar4;
				cp->ai.l.base_Normal = uVar4;
				cp->ai.l.base_Dir = -1;
				cp->ai.l.base_Angle = lVar3;
				cp->ai.l.d = ((uint)curve->inside * 0x400 + ((uint)(u_char)curve->NumLanes & 0xf) * 0x200) - uVar4;
			}
			else 
			{
				cr_00 = (uint)(ushort)curve->start & 0xfff;
				basex = FIXED(rcossin_tbl[cr_00 * 2] * iVar6);
				basez = FIXED(rcossin_tbl[cr_00 * 2 + 1] * iVar6);
				uVar4 = hypot(dx, dz);
				lVar3 = angle;
				cp->ai.l.d = uVar4;
				cp->ai.l.base_Normal = uVar4;
				cp->ai.l.base_Dir = 1;
				cp->ai.l.base_Angle = lVar3;
				cp->ai.l.d = uVar4 - ((uint)curve->inside * 0x400 + ((uint)(u_char)curve->NumLanes & 0xf) * 0x200);
			}

			cp->ai.l.width = ((uint)(u_char)curve->NumLanes & 0xf) << 9;
			offx = basex - (cp->hd).where.t[0];
			offz = basez - (cp->hd).where.t[2];
			dist = -FIXED(offx * rcossin_tbl[(heading & 0xfff) * 2] + offz * rcossin_tbl[(heading & 0xfff) * 2 + 1]);
			dx = FIXED(rcossin_tbl[(heading & 0xfff) * 2] * dist);
			basePosition.vx = basex + dx;
			basePosition.vy = (cp->hd).where.t[1];
			dz = FIXED(rcossin_tbl[(heading & 0xfff) * 2 + 1] * dist);
			basePosition.vz = basez + dz;
		}
		else
		{
			basePosition.vx = (cp->hd).where.t[0];
			basePosition.vy = (cp->hd).where.t[1];
			basePosition.vz = (cp->hd).where.t[2];
		}

		iVar5 = diff;
		iVar6 = diff;

		if (diff < 0)
			iVar6 = -diff;

		cp->ai.l.currentRoad = cr;

		if (iVar6 < 0x200)
		{
			basePosition.vx = (cp->hd).where.t[0];
			basePosition.vy = (cp->hd).where.t[1];
			basePosition.vz = (cp->hd).where.t[2];

			UpdateRoadPosition(cp, &basePosition, 0);
		}
		else if (iVar5 < 1)
		{
			UpdateRoadPosition(cp, &basePosition, 2);
		}
		else 
		{
			UpdateRoadPosition(cp, &basePosition, 3);
		}

		SetTarget(cp, cr, heading, &nextJunction);
	}
	else 
	{
		basePosition.vx = (cp->hd).where.t[0];
		basePosition.vy = (cp->hd).where.t[1];
		basePosition.vz = (cp->hd).where.t[2];
		iVar6 = cp->ai.l.d;

		if (iVar6 < 0)
			iVar6 = -iVar6;
	
		if (((cp->ai.l.width + 0x800 < iVar6) && (((cp->hd).wheel[1].surface & 7) != 3)) && (((cp->hd).wheel[3].surface & 7) != 3)) 
		{
			cp->ai.l.offRoad = 1;
			cp->ai.l.nextJunction = -1;
			UpdateRoadPosition(cp, &basePosition, 4);
			heading = (cp->hd).direction;
			SetTarget(cp, cr_00, heading, &nextJunction);
		}
		else
		{
			cp->ai.l.currentRoad = cr_00;
			cp->ai.l.lastRoad = cr_00;
			cp->ai.l.lastDirection = cp->ai.l.direction;

			if ((((cr_00 & 0xffffe000) == 0x4000) && ((int)(cr_00 & 0x1fff) < NumDriver2Curves)) && (-1 < (int)cr_00))
			{
				UpdateRoadPosition(cp, &basePosition, 1);
			}
			else 
			{
				UpdateRoadPosition(cp, &basePosition, 0);
			}

			heading = (cp->hd).direction;
			SetTarget(cp, cr_00, heading, &nextJunction);

			if ((((nextJunction & 0xffffe000U) == 0x2000) &&
				((int)(nextJunction & 0x1fffU) < NumDriver2Junctions)) && (-1 < nextJunction)) 
			{
				if (nextJunction != cp->ai.l.nextJunction)
				{
					SelectExit(cp, Driver2JunctionsPtr + nextJunction + -0x2000);
					cp->ai.l.nextJunction = nextJunction;
				}
			}
			else 
			{
				cp->ai.l.nextJunction = -1;
			}
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetTarget(struct _CAR_DATA *cp /*$s1*/, int cr /*$a0*/, int heading /*$s4*/, int *nextJunction /*$s3*/)
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
		// 		struct DRIVER2_STRAIGHT *straight; // $t5
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
		// 		struct DRIVER2_CURVE *curve; // $s0
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

// [D]
void SetTarget(_CAR_DATA *cp, int cr, int heading, int *nextJunction)
{
	static int dx = 0; // offset 0xd8
	static int dz = 0; // offset 0xdc

	short sVar1;
	short sVar2;
	ushort uVar3;
	uint uVar4;
	uint uVar5;
	long lVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	DRIVER2_STRAIGHT* straight;
	DRIVER2_CURVE* curve;

	if (cp->ai.l.offRoad == 1)
	{
		uVar3 = *(ushort*)&cp->ai.l.roadPosition;
		iVar8 = cp->ai.l.roadForward;
		cp->ai.l.targetDir = uVar3;
		uVar4 = (uint)uVar3 & 0xfff;

		dx = FIXED(rcossin_tbl[uVar4 * 2 + 1] * iVar8);
		dz = FIXED(rcossin_tbl[uVar4 * 2] * iVar8);

		cp->ai.l.targetX = (cp->hd).where.t[0] + dx;
		cp->ai.l.targetZ = (cp->hd).where.t[2] + dz;

		return;
	}

	if ((cr & 0xffffe000U) == 0) 
	{
		straight = Driver2StraightsPtr + cr;
		cp->ai.l.targetDir = straight->angle & 0xfff;

		iVar8 = (int)straight->ConnectIdx[1];

		if (iVar8 == -1)
			iVar8 = (int)straight->ConnectIdx[0];

		*nextJunction = iVar8;
		iVar8 = cp->ai.l.direction;

		if ((iVar8 == -1) || ((iVar8 == 0 && (((heading - cp->ai.l.targetDir) + 0x400U & 0x800) != 0))))
		{
			cp->ai.l.targetDir = cp->ai.l.targetDir ^ 0x800;

			iVar8 = (int)straight->ConnectIdx[3];

			if (iVar8 == -1) 
				iVar8 = (int)straight->ConnectIdx[2];

			*nextJunction = iVar8;
		}

		iVar10 = (cp->hd).where.t[0];
		uVar4 = (int)cp->ai.l.targetDir + 0x400U & 0xfff;
		iVar9 = (cp->hd).where.t[2];
		sVar1 = rcossin_tbl[uVar4 * 2 + 1];
		iVar7 = cp->ai.l.roadForward;
		uVar5 = (uint)(ushort)cp->ai.l.targetDir & 0xfff;
		sVar2 = rcossin_tbl[uVar5 * 2 + 1];
		iVar8 = FIXED(rcossin_tbl[uVar4 * 2] * (straight->Midx - iVar10) + sVar1 * (straight->Midz - iVar9)) +
				((uint)(u_char)straight->NumLanes & 0xf) * -0x200 + cp->ai.l.roadPosition;

		cp->ai.l.targetX = iVar10 + FIXED(rcossin_tbl[uVar5 * 2] * iVar7) + FIXED(iVar8 * rcossin_tbl[uVar4 * 2]);
		cp->ai.l.targetZ = iVar9 + FIXED(sVar2 * iVar7) + FIXED(iVar8 * sVar1);

		return;
	}

	if ((cr & 0xffffe000U) != 0x4000)
	{
		return;
	}

	curve = Driver2CurvesPtr + cr + -0x4000;
	lVar6 = ratan2((cp->hd).where.t[0] - curve->Midx, (cp->hd).where.t[2] - curve->Midz);
	iVar8 = cp->ai.l.direction;

	if ((iVar8 == 1) || ((iVar8 == 0 && ((lVar6 - heading & 0x800U) != 0))))
	{
		iVar8 = (((uint)(u_char)curve->inside + ((uint)(u_char)curve->NumLanes & 0xf)) * 0x400 -
			cp->ai.l.roadPosition) + (cp->hd).speed * 2;

		uVar4 = lVar6 + cp->ai.l.roadForward / iVar8;
		cp->ai.l.targetDir = (short)uVar4 + 0x400;

		iVar7 = (int)curve->ConnectIdx[1];

		if (iVar7 != -1) 
			*nextJunction = iVar7;
		else
			*nextJunction = (int)curve->ConnectIdx[0];
	}
	else 
	{
		iVar8 = (uint)(u_char)curve->inside * 0x400 + cp->ai.l.roadPosition + (cp->hd).speed * -2;

		uVar4 = lVar6 - cp->ai.l.roadForward / iVar8;
		cp->ai.l.targetDir = (short)uVar4 + -0x400;

		iVar7 = (int)curve->ConnectIdx[3];

		if (iVar7 == -1)
			iVar7 = (int)curve->ConnectIdx[2];

		*nextJunction = iVar7;
	}

	cp->ai.l.targetX = curve->Midx + FIXED(iVar8 * rcossin_tbl[(uVar4 & 0xfff) * 2]);
	cp->ai.l.targetZ = curve->Midz + FIXED(iVar8 * rcossin_tbl[(uVar4 & 0xfff) * 2 + 1]);

}



// decompiled code
// original method signature: 
// void /*$ra*/ SelectExit(struct _CAR_DATA *cp /*$s3*/, struct DRIVER2_JUNCTION *junction /*$a3*/)
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

// [D]
void SelectExit(_CAR_DATA *cp, DRIVER2_JUNCTION *junction)
{
	int uVar1;
	int uVar2;
	int iVar3;
	short* psVar4;
	int iVar5;
	int uVar6;
	int iVar7;
	int iVar8;
	int uVar9;
	int iVar10;
	int el[4][2];

	iVar10 = 0;
	uVar6 = 0;
	iVar3 = cp->ai.l.lastRoad;
	iVar8 = 0;

	if (junction->ExitIdx[0] != iVar3) 
	{
		psVar4 = junction->ExitIdx;

		do {
			psVar4 = psVar4 + 1;
			iVar8 = iVar8 + 1;

			if ((int)*psVar4 == iVar3)
				goto LAB_LEAD__000ec664;

		} while (iVar8 < 4);

		if (junction->ExitIdx[iVar8] != iVar3)
		{
			uVar9 = (cp->ai.l.targetDir + 0x200U & 0xfff) >> 10;
			goto LAB_LEAD__000ec684;
		}
	}

LAB_LEAD__000ec664:
	uVar9 = iVar8 + 2U & 3;
LAB_LEAD__000ec684:

	uVar1 = junction->ExitIdx[uVar9];
	if (((((uVar1 & 0xe000) == 0) && ((int)((uint)uVar1 & 0x1fff) < NumDriver2Straights)) ||
		(((uVar1 & 0xe000) == 0x4000 && ((int)((uint)uVar1 & 0x1fff) < NumDriver2Curves)))) &&
		(-1 < junction->ExitIdx[uVar9]))
	{
		iVar10 = 1;
		el[0][0] = 0;
		uVar6 = junction->flags >> (uVar9 << 3) & 0xf;
		el[0][1] = uVar6;
	}

	uVar2 = uVar9 + 1;
	uVar1 = junction->ExitIdx[uVar2 & 3];
	iVar3 = iVar10;

	if (((((uVar1 & 0xe000) == 0) && ((int)((uint)uVar1 & 0x1fff) < NumDriver2Straights)) ||
		(((uVar1 & 0xe000) == 0x4000 && ((int)((uint)uVar1 & 0x1fff) < NumDriver2Curves)))) &&
		(-1 < junction->ExitIdx[uVar2 & 3]))
	{
		iVar3 = iVar10 + 1;
		el[iVar10][0] = 1;
		uVar2 = junction->flags >> ((uVar2 & 3) << 3) & 0xf;
		uVar6 = uVar6 + uVar2;
		el[iVar10][1] = uVar2;
	}

	uVar2 = uVar9 - 1;
	uVar1 = junction->ExitIdx[uVar2 & 3];
	iVar8 = iVar3;

	if (((((uVar1 & 0xe000) == 0) && ((int)((uint)uVar1 & 0x1fff) < NumDriver2Straights)) ||
		(((uVar1 & 0xe000) == 0x4000 && ((int)((uint)uVar1 & 0x1fff) < NumDriver2Curves)))) &&
		(-1 < junction->ExitIdx[uVar2 & 3]))
	{
		iVar8 = iVar3 + 1;
		el[iVar3][0] = -1;
		uVar2 = junction->flags >> ((uVar2 & 3) << 3) & 0xf;
		uVar6 = uVar6 + uVar2;
		el[iVar3][1] = uVar2;
	}

	iVar3 = iVar8;

	if (uVar6 == 0)
	{
		iVar3 = iVar8 + 1;
		uVar6 = 1;
		el[iVar8][0] = 2;
		el[iVar8][1] = 1;
	}

	iVar8 = leadRand();

	if (iVar8 < 0)
		iVar8 = -iVar8;

	if (iVar3 != 0) 
	{
		iVar10 = 1;
		iVar7 = el[0][1];

		if (iVar8 % uVar6 < el[0][1]) 
		{
			cp->ai.l.nextTurn = el[0][0];
		}
		else
		{
			do {
				iVar5 = iVar10;

				if (iVar3 <= iVar5)
					goto LAB_LEAD__000ec924;

				iVar7 = iVar7 + el[iVar5][1];
				iVar10 = iVar5 + 1;
			} while (iVar7 <= iVar8 % uVar6);

			cp->ai.l.nextTurn = el[iVar5][0];
		}
	}

LAB_LEAD__000ec924:

	cp->ai.l.nextExit = uVar9 + cp->ai.l.nextTurn & 3;

	iVar3 = leadRand();

	if (iVar3 < 0)
		iVar3 = -iVar3;

	if (iVar3 == (iVar3 / 3) * 3)
		cp->ai.l.nextTurn = -cp->ai.l.nextTurn;

}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ FreeRoamer(struct _CAR_DATA *cp /*$s1*/)
 // line 2848, offset 0x000ec99c
	/* begin block 1 */
		// Start line: 2849
		// Start offset: 0x000EC99C

		/* begin block 1.1 */
			// Start line: 2965
			// Start offset: 0x000ECA4C
			// Variables:
		// 		struct _CAR_DATA *pCar; // $v0

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

// [D]
ulong FreeRoamer(_CAR_DATA *cp)
{	
	int i;
	int playerCarId;
	int seed;
	int* piVar5;

	LeadHorn(cp);
	DamageBar.position = cp->totalDamage;

	if ((((cp->hd).where.m[1][1] < 100) ||
		((((cp->hd).wheel[1].surface & 7) == 1 && (((cp->hd).wheel[3].surface & 7) == 1)))) &&
		(cp->ai.l.dstate != 8))
	{
		cp->totalDamage += 100;
	}

	cp->ai.l.ctt++;

	if (cp->ai.l.takeDamage != 0)
		cp->ai.l.takeDamage--;

	if (CameraCnt == 100)
	{
		playerCarId = player[0].playerCarId;

		if (playerCarId >= 0) // [A] bug fix
		{
			seed = (car_data[playerCarId].hd.where.t[0] + car_data[playerCarId].hd.where.t[2]) / (car_data[playerCarId].hd.speed + 1);

			piVar5 = randState;

			randIndex = 0;

			i = 16;
			do {
				randState[i--] = seed;
				seed = seed * 0x751 + 0x10cc2af;
			} while (-1 < i);

			i = 39;
			do {
				i--;
				leadRand();
			} while (-1 < i);
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

// [D]
ulong hypot(long x, long y)
{
	bool bVar1;
	int iVar2;
	ulong uVar3;
	int iVar4;

	if (x < 0) {
		x = -x;
	}
	bVar1 = x < y;
	if (y < 0) {
		y = -y;
		bVar1 = x < y;
	}
	iVar2 = y;
	if (bVar1) {
		iVar2 = x;
		x = y;
	}
	iVar4 = x >> 0xc;

	if (x < 0x8000) 
	{
		uVar3 = SquareRoot0(x * x + iVar2 * iVar2);
	}
	else 
	{
		iVar2 = SquareRoot0((iVar2 / iVar4) * (iVar2 / iVar4) + 0x1000800);
		uVar3 = x + iVar4 * (iVar2 + -0x1000);
	}

	return uVar3;
}





