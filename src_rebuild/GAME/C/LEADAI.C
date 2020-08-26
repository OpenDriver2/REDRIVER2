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

static int randIndex;
static int randState[17];
LEAD_PARAMETERS LeadValues;

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
			CheckCurrentRoad((_CAR_DATA*)cp);
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
			CheckCurrentRoad((_CAR_DATA*)cp);
			iVar2 = ((cp->hd.direction - (int)cp->ai.l.targetDir) + 0x800U & 0xfff) - 0x800;

			if (iVar2 < 0)
				iVar2 = -iVar2;

			if (iVar2 < LeadValues.dEnd)
				cp->ai.l.dstate = 2;

			goto LAB_LEAD__000e7748;
		case 2:
			CheckCurrentRoad((_CAR_DATA*)cp);
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

			CheckCurrentRoad((_CAR_DATA*)cp);
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

ulong LeadPadResponse(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	undefined *puVar6;
	uint uVar7;

	puVar6 = (undefined *)0x0;
	iVar5 = (((cp->hd).direction - (int)*(short *)(cp->ai + 2)) + 0x800U & 0xfff) - 0x800;
	iVar4 = *(int *)(cp->st + 0x2c) + 0x800 >> 0xc;
	switch (cp->ai[0]) {
	case 0:
		puVar6 = &DAT_00008010;
		if (iVar5 < 0) {
			puVar6 = &DAT_00002010;
		}
		break;
	case 1:
		puVar6 = (undefined *)0x40;
		break;
	case 2:
		if (iVar4 < 0) {
			if (iVar4 < 0) {
				iVar4 = -iVar4;
			}
			puVar6 = &DAT_00002040;
			if (0x28 < iVar4) {
				puVar6 = &DAT_00002044;
			}
		}
		else {
			if (iVar4 < 0) {
				iVar4 = -iVar4;
			}
			puVar6 = &DAT_00008040;
			if (0x28 < iVar4) {
				puVar6 = &DAT_00008044;
			}
		}
		break;
	case 3:
		uVar7 = (uint)*(ushort *)(cp->ai + 2) & 0xfff;
		iVar2 = -(int)rcossin_tbl[uVar7 * 2 + 1] * ((cp->hd).where.t[0] - *(int *)(cp->ai + 4)) +
			(int)rcossin_tbl[uVar7 * 2] * ((cp->hd).where.t[2] - *(int *)(cp->ai + 8)) + 0x800 >>
			0xc;
		iVar3 = DAT_LEAD__000ecbf8;
		if ((DAT_LEAD__000ecbf8 < iVar2) || (iVar3 = -DAT_LEAD__000ecbf8, iVar2 < -DAT_LEAD__000ecbf8))
		{
			iVar2 = iVar3;
		}
		iVar5 = ((int)PTR_DAT_LEAD__000ecbe8 *
			(-(int)rcossin_tbl[uVar7 * 2 + 1] * (*(int *)(cp->st + 0x1c) + 0x800 >> 0xc) +
			(int)rcossin_tbl[uVar7 * 2] * (*(int *)(cp->st + 0x24) + 0x800 >> 0xc) + 0x800 >> 0xc)
			+ DAT_LEAD__000ecbec * iVar4 + DAT_LEAD__000ecbf0 * iVar2 + DAT_LEAD__000ecbf4 * iVar5
			+ 0x800 >> 0xc) - (int)cp->wheel_angle;
		puVar6 = (undefined *)0x40;
		if (0x20 < iVar5) {
			puVar6 = &DAT_00002040;
		}
		if (0x40 < iVar5) {
			puVar6 = (undefined *)((uint)puVar6 | 4);
		}
		if (iVar5 < -0x20) {
			puVar6 = (undefined *)((uint)puVar6 | 0x8000);
		}
		if (iVar5 < -0x40) {
			puVar6 = (undefined *)((uint)puVar6 | 4);
		}
		if (0x3e < iVar5 + 0x1fU) {
			return (ulong)puVar6;
		}
		if (iVar4 < 0) {
			iVar4 = -iVar4;
		}
		if (5 < iVar4) {
			return (ulong)puVar6;
		}
		if (((uint)puVar6 & 0x40) == 0) {
			return (ulong)puVar6;
		}
		goto LAB_LEAD__000e7d50;
	case 4:
		uVar7 = 0x20;
		iVar4 = ((*(int *)(cp->ai + 0x2c) - (cp->hd).direction) + 0x800U & 0xfff) - 0x800;
		if (*(int *)(cp->ai + 0x30) < 0) {
			uVar7 = 0x80;
		}
		if (iVar4 * *(int *)(cp->ai + 0x30) < 1) {
			puVar6 = (undefined *)(uVar7 | 0x8000);
		}
		else {
			puVar6 = (undefined *)(uVar7 | 0x2000);
		}
		if (iVar4 < 0) {
			iVar4 = -iVar4;
		}
		if (200 < iVar4) {
			if (iVar5 < 0) {
				iVar5 = -iVar5;
			}
			if (iVar5 < 0x738) {
				puVar6 = (undefined *)((uint)puVar6 | 4);
			}
		}
		break;
	case 5:
		iVar2 = *(int *)(cp->ai + 0x24);
		iVar3 = iVar4;
		if (iVar4 < 0) {
			iVar3 = -iVar4;
		}
		iVar1 = iVar2;
		if (iVar2 < 0) {
			iVar1 = -iVar2;
		}
		if ((iVar1 < 2) || (0x96 < iVar3)) {
			puVar6 = (undefined *)((uint)((cp->hd).speed < 0x65) << 6);
		}
		else {
			puVar6 = (undefined *)0x20;
			if (100 < (cp->hd).speed) {
				puVar6 = (undefined *)0x10;
			}
		}
		if (iVar3 < 0x50) {
			puVar6 = (undefined *)((uint)puVar6 | 4);
		}
		if (iVar2 < 1) {
			if (iVar2 < 0) {
				if ((0x95 < iVar3) && (iVar4 < 1)) {
					return (ulong)puVar6;
				}
				return (uint)puVar6 | 0x8000;
			}
			if ((0 < iVar5) && ((iVar3 < 0x96 || (0 < iVar4)))) {
				puVar6 = (undefined *)((uint)puVar6 | 0x8000);
			}
			if (-1 < iVar5) {
				return (ulong)puVar6;
			}
		}
		if ((iVar3 < 0x96) || (iVar4 < 0)) {
			puVar6 = (undefined *)((uint)puVar6 | 0x2000);
		}
		break;
	case 6:
		uVar7 = 0x8000;
		if (iVar4 < 0) {
			uVar7 = 0x2000;
		}
		if ((*(int *)(cp->ai + 0x30) < 0) && (100 < (cp->hd).speed)) {
			puVar6 = (undefined *)(uVar7 | 0x80);
		}
		else {
			puVar6 = (undefined *)(uVar7 | 0x40);
		}
		break;
	case 7:
		if (iVar4 < 0) {
			iVar4 = -iVar4;
		}
		if (DAT_LEAD__000ece94 <= iVar4) {
			iVar4 = iVar5;
			if (iVar5 < 0) {
				iVar4 = -iVar5;
			}
			if (iVar4 < 0x401) goto LAB_LEAD__000e7d50;
		}
		puVar6 = (undefined *)0x8004;
		if (iVar5 < 0) {
			puVar6 = (undefined *)0x2004;
		}
	LAB_LEAD__000e7d50:
		puVar6 = (undefined *)((uint)puVar6 | 0x20);
		break;
	case 8:
		FakeMotion(cp);
		puVar6 = (undefined *)0x0;
	}
	return (ulong)puVar6;*/
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

void FakeMotion(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	undefined4 uVar2;
	ushort uVar3;
	int iVar4;
	uint uVar5;
	int iVar6;
	int iVar7;
	uint uVar8;
	int iVar9;
	DRIVER2_STRAIGHT *pDVar10;
	DRIVER2_CURVE *pDVar11;
	DRIVER2_JUNCTION *junction;

	junction = Driver2JunctionsPtr;
	uVar8 = *(uint *)(cp->ai + 0xc);
	uVar5 = uVar8 & 0xffffe000;
	if (uVar5 == 0x2000) {
		*(uint *)(cp->ai + 0x10) = uVar8;
		SelectExit(cp, junction + (uVar8 - 0x2000));
		sVar1 = junction[uVar8 - 0x2000].ExitIdx[*(int *)(cp->ai + 0x1c)];
		*(short *)(cp->ai + 2) = (short)(*(int *)(cp->ai + 0x1c) << 10);
		*(undefined4 *)(cp->ai + 0x5c) = 0;
		*(int *)(cp->ai + 0xc) = (int)sVar1;
		return;
	}
	if ((int)uVar5 < 0x2001) {
		if (uVar5 != 0) {
			return;
		}
		iVar9 = (cp->hd).where.t[0];
		iVar7 = (cp->hd).where.t[2];
		pDVar10 = Driver2StraightsPtr + uVar8;
		iVar6 = pDVar10->Midx;
		iVar4 = pDVar10->Midz;
		DAT_LEAD__000ecc18 = (uint)(ushort)pDVar10->angle & 0xfff;
		uVar5 = SEXT24(pDVar10->ConnectIdx[1]);
		if (uVar5 == 0xffffffff) {
			uVar5 = SEXT24(pDVar10->ConnectIdx[0]);
		}
		if (*(int *)(cp->ai + 0x5c) == 0) {
			uVar2 = 0xffffffff;
			if ((((int)*(short *)(cp->ai + 2) - DAT_LEAD__000ecc18) + 0x400 & 0x800) == 0) {
				uVar2 = 1;
			}
			*(undefined4 *)(cp->ai + 0x5c) = uVar2;
		}
		if (*(int *)(cp->ai + 0x5c) == -1) {
			uVar5 = SEXT24(pDVar10->ConnectIdx[3]);
			DAT_LEAD__000ecc18 = DAT_LEAD__000ecc18 ^ 0x800;
			if (uVar5 == 0xffffffff) {
				uVar5 = SEXT24(pDVar10->ConnectIdx[2]);
			}
		}
		DAT_LEAD__000ecc1c = (int)rcossin_tbl[(DAT_LEAD__000ecc18 & 0xfff) * 2];
		DAT_LEAD__000ecc20 = (int)rcossin_tbl[(DAT_LEAD__000ecc18 & 0xfff) * 2 + 1];
		DAT_LEAD__000ecc10 =
			DAT_LEAD__000ecc1c * (iVar9 - iVar6) + DAT_LEAD__000ecc20 * (iVar7 - iVar4) + 0x800 >> 0xc;
		DAT_LEAD__000ecc14 = (uint)(pDVar10->length >> 1) - DAT_LEAD__000ecc10;
		if (-1 < DAT_LEAD__000ecc14) {
			DAT_LEAD__000ecc10 = DAT_LEAD__000ecc10 + 0x78;
			iVar4 = DAT_LEAD__000ecc20 * DAT_LEAD__000ecc10;
			(cp->hd).where.t[0] = (DAT_LEAD__000ecc1c * DAT_LEAD__000ecc10 + 0x800 >> 0xc) + pDVar10->Midx
				;
			(cp->hd).where.t[2] = (iVar4 + 0x800 >> 0xc) + pDVar10->Midz;
			return;
		}
		if ((((uVar5 & 0xffffe000) != 0x2000) || (NumDriver2Junctions <= (int)(uVar5 & 0x1fff))) ||
			((int)uVar5 < 0)) {
			*(uint *)(cp->ai + 0xc) = uVar5;
			goto LAB_LEAD__000e824c;
		}
	}
	else {
		if (uVar5 != 0x4000) {
			return;
		}
		pDVar11 = Driver2CurvesPtr + (uVar8 - 0x4000);
		iVar4 = ratan2((cp->hd).where.t[0] - pDVar11->Midx, (cp->hd).where.t[2] - pDVar11->Midz);
		iVar6 = (uint)(byte)pDVar11->inside * 2 + ((uint)(byte)pDVar11->NumLanes & 0xf);
		iVar7 = iVar6 * 0x200;
		if (*(int *)(cp->ai + 0x5c) == 0) {
			uVar2 = 1;
			if ((iVar4 - *(short *)(cp->ai + 2) & 0x800U) == 0) {
				uVar2 = 0xffffffff;
			}
			*(undefined4 *)(cp->ai + 0x5c) = uVar2;
		}
		if (*(int *)(cp->ai + 0x5c) == 1) {
			if (-1 < (int)(((pDVar11->end - iVar4 & 0xfffU) + 0x800 & 0xfff) - 0x800)) {
				if (iVar6 == 0) {
					trap(7);
				}
				uVar8 = iVar4 + 0x13193 / iVar7;
				uVar5 = uVar8 & 0xfff;
				sVar1 = rcossin_tbl[uVar5 * 2 + 1];
				(cp->hd).where.t[0] = (rcossin_tbl[uVar5 * 2] * iVar7 + 0x800 >> 0xc) + pDVar11->Midx;
				iVar4 = pDVar11->Midz;
				uVar3 = (short)uVar8 + 0x400;
			LAB_LEAD__000e82cc:
				*(ushort *)(cp->ai + 2) = uVar3 & 0xfff;
				(cp->hd).where.t[2] = (sVar1 * iVar7 + 0x800 >> 0xc) + iVar4;
				return;
			}
			uVar5 = SEXT24(pDVar11->ConnectIdx[1]);
			if (uVar5 == 0xffffffff) {
				uVar5 = SEXT24(pDVar11->ConnectIdx[0]);
			}
			if (((uVar5 & 0xffffe000) != 0x2000) || (NumDriver2Junctions <= (int)(uVar5 & 0x1fff))) {
			LAB_LEAD__000e8248:
				*(uint *)(cp->ai + 0xc) = uVar5;
				goto LAB_LEAD__000e824c;
			}
			if ((int)uVar5 < 0) {
				*(uint *)(cp->ai + 0xc) = uVar5;
				goto LAB_LEAD__000e824c;
			}
		}
		else {
			if (-1 < (int)(((iVar4 - pDVar11->start & 0xfffU) + 0x800 & 0xfff) - 0x800)) {
				if (iVar6 == 0) {
					trap(7);
				}
				uVar8 = iVar4 - 0x13193 / iVar7;
				uVar5 = uVar8 & 0xfff;
				sVar1 = rcossin_tbl[uVar5 * 2 + 1];
				(cp->hd).where.t[0] = (rcossin_tbl[uVar5 * 2] * iVar7 + 0x800 >> 0xc) + pDVar11->Midx;
				iVar4 = pDVar11->Midz;
				uVar3 = (short)uVar8 - 0x400;
				goto LAB_LEAD__000e82cc;
			}
			uVar5 = SEXT24(pDVar11->ConnectIdx[3]);
			if (uVar5 == 0xffffffff) {
				uVar5 = SEXT24(pDVar11->ConnectIdx[2]);
			}
			if ((((uVar5 & 0xffffe000) != 0x2000) || (NumDriver2Junctions <= (int)(uVar5 & 0x1fff))) ||
				((int)uVar5 < 0)) goto LAB_LEAD__000e8248;
		}
	}
	junction = Driver2JunctionsPtr + (uVar5 - 0x2000);
	*(undefined4 *)(cp->ai + 0x10) = *(undefined4 *)(cp->ai + 0xc);
	SelectExit(cp, junction);
	sVar1 = junction->ExitIdx[*(int *)(cp->ai + 0x1c)];
	*(short *)(cp->ai + 2) = (short)(*(int *)(cp->ai + 0x1c) << 10);
	*(int *)(cp->ai + 0xc) = (int)sVar1;
LAB_LEAD__000e824c:
	*(undefined4 *)(cp->ai + 0x5c) = 0;
	return;*/
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

void BlockToMap(MAP_DATA *data)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	int iVar2;
	int iVar3;
	ulong uVar4;
	ulong uVar5;
	VECTOR *pVVar6;
	CAR_COSMETICS *pCVar7;
	VECTOR *pVVar8;
	_CAR_DATA *p_Var9;
	int iVar10;
	int iVar11;
	int iVar12;
	long *plVar13;
	int *tangent;
	DRIVER2_CURVE *pDVar14;
	int *tangent_00;
	int iVar15;
	int y;
	int *normal;
	int iVar16;
	int *normal_00;
	uint uVar17;
	int x;
	int iStack112;
	int aiStack108[11];
	int iStack64;
	int iStack60;
	uint uStack56;
	ulong uStack52;
	int iStack48;
	ulong uStack44;

	pCVar7 = (data->cp->ap).carCos;
	DAT_LEAD__000ecc24 = (int)(pCVar7->colBox).vz;
	DAT_LEAD__000ecc28 = (int)(pCVar7->colBox).vx;
	switch (data->intention) {
	case 0:
	case 2:
	case 3:
		pVVar8 = data->pos;
		pVVar6 = data->base;
		y = pVVar8->vx - pVVar6->vx;
		iVar10 = pVVar6->vy - pVVar8->vy;
		x = pVVar8->vz - pVVar6->vz;
		if (iVar10 < 1) {
			iVar3 = (int)(((data->cp->ap).carCos)->colBox).vy;
		}
		else {
			iVar3 = data->size->vy;
		}
		if (iVar3 < iVar10) {
			return;
		}
		iVar10 = data->size->vx * DAT_LEAD__000ecd3c;
		iVar3 = data->size->vz * DAT_LEAD__000ecd38;
		iVar12 = y * DAT_LEAD__000ecd3c + x * DAT_LEAD__000ecd38 + 0x800 >> 0xc;
		if (iVar10 < 0) {
			iVar10 = -iVar10;
		}
		if (iVar3 < 0) {
			iVar3 = -iVar3;
		}
		DAT_LEAD__000ecbfc = iVar10 + iVar3 + 0x800 >> 0xc;
		iVar10 = (y * DAT_LEAD__000ecd38 - x * DAT_LEAD__000ecd3c) + 0x800 >> 0xc;
		if ((data->intention == 0) || (data->cp->ai[0] == 3)) {
			x = iVar12;
			if (iVar12 < 0) {
				x = -iVar12;
			}
			y = ((data->cp->hd).speed + 100) * 10;
			if (x < y) {
				x = iVar10;
				if (iVar10 < 0) {
					x = -iVar10;
				}
				if (x < y) {
					DAT_LEAD__000ecc44 = data->base;
					DAT_LEAD__000ecc48 = data->pos;
					DAT_LEAD__000ecc4c = data->vel;
					DAT_LEAD__000ecc50 = data->size;
					DAT_LEAD__000ecc54 = 6;
					DAT_LEAD__000ecc58 = data->local;
					DAT_LEAD__000ecc5c = 0;
					DAT_LEAD__000ecc40 = data->cp;
					BlockToMap((MAP_DATA *)&DAT_LEAD__000ecc40);
				}
			}
		}
		if (iVar12 + DAT_LEAD__000ecbfc < 0) {
			return;
		}
		x = data->size->vx * DAT_LEAD__000ecd38;
		y = data->size->vz * DAT_LEAD__000ecd3c;
		if (x < 0) {
			x = -x;
		}
		if (y < 0) {
			y = -y;
		}
		pVVar6 = data->vel;
		DAT_LEAD__000ecc00 = (x + y + 0x800 >> 0xc) + DAT_LEAD__000ecc28 * 2;
		if (pVVar6 != (VECTOR *)0x0) {
			x = pVVar6->vx * DAT_LEAD__000ecd3c + pVVar6->vz * DAT_LEAD__000ecd38 + 0x800;
			y = (x >> 0xc) - (x >> 0x1f) >> 1;
			iVar12 = iVar12 + y;
			x = y;
			if (y < 0) {
				x = -y;
			}
			DAT_LEAD__000ecbfc = DAT_LEAD__000ecbfc + x;
			if ((y < 0) && (data->intention == 0)) {
				iVar12 = iVar12 / 2;
			}
		}
		DAT_LEAD__000ecc38 = (iVar12 - DAT_LEAD__000ecbfc) - DAT_LEAD__000ecc24;
		if ((int)DAT_LEAD__000ecc38 < 0) {
			DAT_LEAD__000ecc38 = 0;
		}
		pVVar6 = data->vel;
		DAT_LEAD__000ecc2c = iVar10 - DAT_LEAD__000ecc00;
		iVar10 = iVar10 + DAT_LEAD__000ecc00;
		DAT_LEAD__000ecc30 = iVar10;
		if (pVVar6 != (VECTOR *)0x0) {
			x = pVVar6->vx * DAT_LEAD__000ecd38 + pVVar6->vz * DAT_LEAD__000ecd3c + 0x800 >> 0xc;
			DAT_LEAD__000ecc30 = iVar10 + x;
			if (x < 1) {
				DAT_LEAD__000ecc2c = DAT_LEAD__000ecc2c - x;
				DAT_LEAD__000ecc30 = iVar10;
			}
		}
		break;
	case 1:
		pVVar6 = data->pos;
		pDVar14 = Driver2CurvesPtr + *(int *)(data->cp->ai + 0xc) + -0x4000;
		y = pVVar6->vx - pDVar14->Midx;
		iVar10 = data->base->vy - pVVar6->vy;
		x = pVVar6->vz - pDVar14->Midz;
		if (iVar10 < 1) {
			iVar3 = (int)(((data->cp->ap).carCos)->colBox).vy;
		}
		else {
			iVar3 = data->size->vy;
		}
		if (iVar3 < iVar10) {
			return;
		}
		iVar2 = ratan2(y, x);
		iVar12 = data->size->vx;
		uVar17 = iVar2 + 0x400U & 0xfff;
		iVar16 = (int)rcossin_tbl[uVar17 * 2];
		iVar10 = iVar12 * iVar16;
		iVar11 = data->size->vz;
		iVar15 = (int)rcossin_tbl[uVar17 * 2 + 1];
		iVar3 = iVar11 * iVar15;
		iVar2 = (((iVar2 - *(int *)(data->cp->ai + 0x50)) + 0x800U & 0xfff) - 0x800) *
			*(int *)(data->cp->ai + 0x54) * ((int)((uint)(byte)pDVar14->inside * 0xb000) / 0x7000);
		if (iVar10 < 0) {
			iVar10 = -iVar10;
		}
		if (iVar3 < 0) {
			iVar3 = -iVar3;
		}
		DAT_LEAD__000ecbfc = iVar10 + iVar3 + 0x800 >> 0xc;
		if (iVar2 + DAT_LEAD__000ecbfc < 0) {
			return;
		}
		iVar12 = iVar12 * iVar15;
		iVar11 = iVar11 * iVar16;
		if (iVar12 < 0) {
			iVar12 = -iVar12;
		}
		if (iVar11 < 0) {
			iVar11 = -iVar11;
		}
		pVVar6 = data->vel;
		DAT_LEAD__000ecc00 = (iVar12 + iVar11 + 0x800 >> 0xc) + DAT_LEAD__000ecc28;
		if (pVVar6 != (VECTOR *)0x0) {
			iVar10 = pVVar6->vx * iVar16 + pVVar6->vz * iVar15 + 0x800;
			iVar3 = (iVar10 >> 0xc) - (iVar10 >> 0x1f) >> 1;
			iVar2 = iVar2 + iVar3;
			iVar10 = iVar3;
			if (iVar3 < 0) {
				iVar10 = -iVar3;
			}
			DAT_LEAD__000ecbfc = DAT_LEAD__000ecbfc + iVar10;
			if (iVar3 < 0) {
				iVar2 = iVar2 / 2;
			}
		}
		uVar4 = (iVar2 - DAT_LEAD__000ecbfc) - DAT_LEAD__000ecc24;
		if ((int)uVar4 < 0) {
			uVar4 = 0;
		}
		iVar10 = *(int *)(data->cp->ai + 0x4c);
		uVar5 = hypot(y, x);
		p_Var9 = data->cp;
		x = (iVar10 - uVar5) * *(int *)(p_Var9->ai + 0x54);
		iVar10 = ((p_Var9->hd).speed + 100) * 10;
		if ((int)uVar4 < iVar10) {
			y = x;
			if (x < 0) {
				y = -x;
			}
			if (y < iVar10) {
				DAT_LEAD__000ecc44 = data->base;
				DAT_LEAD__000ecc48 = data->pos;
				DAT_LEAD__000ecc4c = data->vel;
				DAT_LEAD__000ecc50 = data->size;
				DAT_LEAD__000ecc54 = 6;
				DAT_LEAD__000ecc58 = data->local;
				DAT_LEAD__000ecc5c = 0;
				DAT_LEAD__000ecc40 = p_Var9;
				BlockToMap((MAP_DATA *)&DAT_LEAD__000ecc40);
			}
		}
		pVVar6 = data->vel;
		DAT_LEAD__000ecc2c = x - DAT_LEAD__000ecc00;
		x = x + DAT_LEAD__000ecc00;
		DAT_LEAD__000ecc30 = x;
		DAT_LEAD__000ecc38 = uVar4;
		if (pVVar6 != (VECTOR *)0x0) {
			iVar10 = pVVar6->vx * iVar15 + pVVar6->vz * iVar16 + 0x800 >> 0xc;
			DAT_LEAD__000ecc30 = x + iVar10;
			if (iVar10 < 1) {
				DAT_LEAD__000ecc2c = DAT_LEAD__000ecc2c - iVar10;
				DAT_LEAD__000ecc30 = x;
			}
		}
		break;
	case 4:
	case 5:
	case 6:
		pVVar8 = data->pos;
		pVVar6 = data->base;
		x = pVVar8->vx - pVVar6->vx;
		iVar10 = pVVar6->vy - pVVar8->vy;
		y = pVVar8->vz - pVVar6->vz;
		if (iVar10 < 1) {
			iVar3 = (int)(((data->cp->ap).carCos)->colBox).vy;
		}
		else {
			iVar3 = data->size->vy;
		}
		if (iVar3 < iVar10) {
			return;
		}
		uVar4 = hypot(x, y);
		iVar10 = ratan2(x, y);
		uVar17 = (iVar10 + 0x800U & 0xfff) - 0x800;
		pVVar6 = data->size;
		iVar12 = pVVar6->vx;
		iVar10 = iVar12 * (int)rcossin_tbl[(uVar17 & 0xfff) * 2];
		iVar3 = pVVar6->vz * (int)rcossin_tbl[(uVar17 & 0xfff) * 2 + 1];
		if (iVar10 < 0) {
			iVar10 = -iVar10;
		}
		if (iVar3 < 0) {
			iVar3 = -iVar3;
		}
		DAT_LEAD__000ecbfc = iVar10 + iVar3 + 0x800 >> 0xc;
		uVar4 = (uVar4 - DAT_LEAD__000ecbfc) - DAT_LEAD__000ecc24;
		if (((int)uVar4 < 2000) ||
			(iVar10 = iVar12 * (int)rcossin_tbl[(uVar17 & 0xfff) * 2 + 1], data->intention == 6)) {
			iStack112 = x + iVar12;
			aiStack108[5] = x - pVVar6->vx;
			aiStack108[0] = y + pVVar6->vz;
			aiStack108[3] = y - pVVar6->vz;
			aiStack108[2] = iStack112;
			aiStack108[6] = aiStack108[0];
			aiStack108[8] = aiStack108[5];
			aiStack108[9] = aiStack108[3];
			aiStack108[1] = ratan2();
			aiStack108[4] = ratan2(aiStack108[2], aiStack108[3]);
			bVar1 = false;
			aiStack108[7] = ratan2(aiStack108[5], aiStack108[6]);
			x = 1;
			aiStack108[10] = ratan2(aiStack108[8], aiStack108[9]);
			tangent_00 = aiStack108 + 1;
			tangent = aiStack108 + 4;
			DAT_LEAD__000ecc2c = 0;
			DAT_LEAD__000ecc30 = 0;
			iVar10 = aiStack108[1] + 0x800 >> 10;
			do {
				y = *tangent;
				if (0 < (int)(((tangent_00[DAT_LEAD__000ecc2c * 3] - y) + 0x800U & 0xfff) - 0x800)) {
					DAT_LEAD__000ecc2c = x;
				}
				if (0 < (int)(((y - tangent_00[DAT_LEAD__000ecc30 * 3]) + 0x800U & 0xfff) - 0x800)) {
					DAT_LEAD__000ecc30 = x;
				}
				iVar3 = y + 0x800 >> 10;
				if ((iVar10 != iVar3) &&
					(iVar10 + (iVar10 - (aiStack108[1] + 0x800 >> 0x1f) >> 1) * -2 ==
						iVar3 + (iVar3 - (y + 0x800 >> 0x1f) >> 1) * -2)) {
					bVar1 = true;
				}
				x = x + 1;
				tangent = tangent + 3;
			} while (x < 4);
			if (bVar1) {
				DAT_LEAD__000ecc38 = 0;
				DAT_LEAD__000ecc30 = uVar17 - (data->cp->hd).direction;
				DAT_LEAD__000ecc2c = DAT_LEAD__000ecc30 + -0x200;
				DAT_LEAD__000ecc30 = DAT_LEAD__000ecc30 + 0x200;
			}
			else {
				if (DAT_LEAD__000ecc2c + DAT_LEAD__000ecc30 == 3) {
					uVar4 = 0xffffffff;
					iVar10 = 0;
					plVar13 = aiStack108;
					do {
						if (((iVar10 != DAT_LEAD__000ecc2c) && (iVar10 != DAT_LEAD__000ecc30)) &&
							((uVar5 = hypot(plVar13[-1], *plVar13), (int)uVar5 < (int)uVar4 ||
							(uVar4 == 0xffffffff)))) {
							uVar4 = uVar5;
						}
						iVar10 = iVar10 + 1;
						plVar13 = plVar13 + 3;
					} while (iVar10 < 4);
					iVar10 = (data->cp->hd).direction;
					DAT_LEAD__000ecc2c = tangent_00[DAT_LEAD__000ecc2c * 3] - iVar10;
					DAT_LEAD__000ecc30 = tangent_00[DAT_LEAD__000ecc30 * 3] - iVar10;
					DAT_LEAD__000ecc38 = uVar4;
				}
				else {
					iVar10 = ratan2((&iStack112)[DAT_LEAD__000ecc2c * 3] -
						(&iStack112)[DAT_LEAD__000ecc30 * 3],
						aiStack108[DAT_LEAD__000ecc2c * 3] - aiStack108[DAT_LEAD__000ecc30 * 3]);
					uVar17 = (iVar10 + 0xc00U & 0xfff) - 0x800 & 0xfff;
					iVar10 = DAT_LEAD__000ecc2c * 3;
					x = DAT_LEAD__000ecc2c * 3;
					y = (data->cp->hd).direction;
					DAT_LEAD__000ecc2c = tangent_00[DAT_LEAD__000ecc2c * 3] - y;
					DAT_LEAD__000ecc30 = tangent_00[DAT_LEAD__000ecc30 * 3] - y;
					DAT_LEAD__000ecc38 =
						(int)rcossin_tbl[uVar17 * 2] * (&iStack112)[iVar10] +
						(int)rcossin_tbl[uVar17 * 2 + 1] * aiStack108[x] + 0x800 >> 0xc;
					if ((int)DAT_LEAD__000ecc38 < 0) {
						DAT_LEAD__000ecc38 = -DAT_LEAD__000ecc38;
					}
				}
			}
			DAT_LEAD__000ecc2c = (DAT_LEAD__000ecc2c + 0x800 & 0xfff) - 0x800;
			DAT_LEAD__000ecc30 = (DAT_LEAD__000ecc30 + 0x800U & 0xfff) - 0x800;
		}
		else {
			x = pVVar6->vz * (int)rcossin_tbl[(uVar17 & 0xfff) * 2];
			y = ((uVar17 - (data->cp->hd).direction) + 0x800 & 0xfff) - 0x800;
			if (iVar10 < 0) {
				iVar10 = -iVar10;
			}
			if (x < 0) {
				x = -x;
			}
			DAT_LEAD__000ecc00 = ratan2((iVar10 + x + 0x800 >> 0xc) + DAT_LEAD__000ecc28, uVar4);
			DAT_LEAD__000ecc2c = y - DAT_LEAD__000ecc00;
			DAT_LEAD__000ecc30 = y + DAT_LEAD__000ecc00;
			DAT_LEAD__000ecc38 = uVar4;
		}
		break;
	default:
		goto LAB_LEAD__000e97b4;
	}
	DAT_LEAD__000ecc34 = DAT_LEAD__000ecc38;
	switch (data->intention) {
	case 2:
	case 3:
		tangent = &DAT_LEAD__000ecc38;
		tangent_00 = &DAT_LEAD__000ecc34;
		normal = &DAT_LEAD__000ecc2c;
		normal_00 = &DAT_LEAD__000ecc30;
		if (data->intention != 2) {
			normal_00 = &DAT_LEAD__000ecc2c;
			tangent = &DAT_LEAD__000ecc34;
			tangent_00 = &DAT_LEAD__000ecc38;
			normal = &DAT_LEAD__000ecc30;
		}
		iVar10 = DAT_LEAD__000ecec0 + (data->cp->hd).speed * DAT_LEAD__000ecec4;
		if ((iVar10 < (int)DAT_LEAD__000ecc38) && (iVar10 < (int)DAT_LEAD__000ecc38)) {
			*tangent_00 = *tangent_00 + DAT_LEAD__000ecc24 * 2;
			iVar10 = *tangent + DAT_LEAD__000ecc24 * -2;
			*tangent = iVar10;
			if (iVar10 < 0) {
				*tangent = 0;
			}
			DAT_LEAD__000ecc2c = DAT_LEAD__000ecc2c - DAT_LEAD__000ecc28;
			DAT_LEAD__000ecc30 = DAT_LEAD__000ecc30 + DAT_LEAD__000ecc28;
			iStack64 = *normal;
			iStack60 = *tangent_00 + DAT_LEAD__000ecbfc * 2;
			PosToIndex(&iStack64, &iStack60, data->intention, data->cp);
			PosToIndex(normal, tangent_00, data->intention, data->cp);
			PosToIndex(normal_00, tangent, data->intention, data->cp);
			*normal = iStack64;
			break;
		}
	case 0:
	case 1:
		PosToIndex(&DAT_LEAD__000ecc2c, &DAT_LEAD__000ecc34, data->intention, data->cp);
		PosToIndex(&DAT_LEAD__000ecc30, &DAT_LEAD__000ecc38, data->intention, data->cp);
		break;
	case 4:
		uStack56 = DAT_LEAD__000ecc2c;
		iStack48 = DAT_LEAD__000ecc30;
		uStack52 = DAT_LEAD__000ecc38;
		uStack44 = DAT_LEAD__000ecc38;
		PosToIndex((int *)&uStack56, (int *)&uStack52, 6, data->cp);
		PosToIndex(&iStack48, (int *)&uStack44, 6, data->cp);
		uVar17 = uStack56;
		if (iStack48 < (int)uStack56) {
			while ((int)uVar17 < 0x29) {
				if ((uVar17 < 0x29) && ((int)uStack52 < data->local[uVar17])) {
					data->local[uVar17] = uStack52;
				}
				uVar17 = uVar17 + 1;
			}
			DAT_LEAD__000ecc2c = 0xfffff800;
			PosToIndex((int *)&uStack56, (int *)&uStack52, 6, data->cp);
			uVar17 = uStack56;
			if (iStack48 < (int)uStack56) goto LAB_LEAD__000e96f0;
		}
		while ((int)uVar17 <= iStack48) {
			if ((uVar17 < 0x29) && ((int)uStack52 < data->local[uVar17])) {
				data->local[uVar17] = uStack52;
			}
			uVar17 = uVar17 + 1;
		}
	case 5:
	case 6:
	LAB_LEAD__000e96f0:
		PosToIndex(&DAT_LEAD__000ecc2c, &DAT_LEAD__000ecc34, data->intention, data->cp);
		PosToIndex(&DAT_LEAD__000ecc30, &DAT_LEAD__000ecc38, data->intention, data->cp);
		uVar4 = DAT_LEAD__000ecc34;
		if (DAT_LEAD__000ecc30 < (int)DAT_LEAD__000ecc2c) {
			while ((int)DAT_LEAD__000ecc2c < 0x29) {
				if (((-1 < (int)DAT_LEAD__000ecc2c) && ((int)DAT_LEAD__000ecc2c < 0x29)) &&
					((int)uVar4 < data->map[DAT_LEAD__000ecc2c])) {
					data->map[DAT_LEAD__000ecc2c] = uVar4;
				}
				DAT_LEAD__000ecc2c = DAT_LEAD__000ecc2c + 1;
			}
			DAT_LEAD__000ecc2c = 0xfffff800;
			PosToIndex(&DAT_LEAD__000ecc2c, &DAT_LEAD__000ecc34, data->intention, data->cp);
		}
		break;
	default:
		break;
	}
LAB_LEAD__000e97b4:
	iVar10 = DAT_LEAD__000ecc30;
	uVar17 = DAT_LEAD__000ecc2c;
	uVar4 = DAT_LEAD__000ecc34;
	if ((int)DAT_LEAD__000ecc2c < DAT_LEAD__000ecc30) {
		x = (int)(DAT_LEAD__000ecc38 - DAT_LEAD__000ecc34) /
			(int)(DAT_LEAD__000ecc30 - DAT_LEAD__000ecc2c);
		if (DAT_LEAD__000ecc30 - DAT_LEAD__000ecc2c == 0) {
			trap(7);
		}
	}
	else {
		x = 0;
	}
	while ((int)uVar17 <= iVar10) {
		if (((-1 < (int)uVar17) && ((int)uVar17 < 0x29)) && ((int)uVar4 < data->map[uVar17])) {
			data->map[uVar17] = uVar4;
		}
		uVar17 = uVar17 + 1;
		uVar4 = uVar4 + x;
	}
	return;*/
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
			tangent = dx * road_s + dz * road_c + 0x800 >> 0xc;
			normal = (dx * road_c - dz * road_s) + 0x800 >> 0xc;
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

void UpdateRoadPosition(_CAR_DATA *cp, VECTOR *basePos, int intention)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	short *psVar2;
	bool bVar3;
	undefined4 *puVar4;
	uint cellx;
	PACKED_CELL_OBJECT *ppco;
	int iVar5;
	CELL_OBJECT *pCVar6;
	undefined *puVar7;
	undefined4 uVar8;
	uint uVar9;
	int *piVar10;
	MODEL *pMVar11;
	int iVar12;
	int iVar13;
	uint cellz;
	CAR_COSMETICS *pCVar14;
	int iVar15;
	int iVar16;
	int iVar17;
	int iVar18;
	int *piVar19;
	int iVar20;
	_CAR_DATA *p_Var21;
	uint uVar22;
	CELL_DATA *local_158;
	PACKED_CELL_OBJECT *local_154;
	long local_150;
	int local_148;
	int local_140;
	int local_13c;
	int local_138;
	int local_134;
	int local_130;
	_CAR_DATA *local_128;
	VECTOR *local_124;
	VECTOR *local_120;
	VECTOR *local_11c;
	VECTOR *local_118;
	int local_114;
	MAP_DATA local_110;
	int local_f0[42];
	uint local_48;
	uint local_44;
	uint local_40;
	int local_3c;
	int local_38;
	uint local_34;
	int local_30;
	int local_2c;

	iVar20 = 0x28;
	local_38 = -1;
	puVar4 = &DAT_LEAD__000ece88;
	do {
		*puVar4 = 0x5000;
		iVar20 = iVar20 + -1;
		puVar4 = puVar4 + -1;
	} while (-1 < iVar20);
	piVar10 = &DAT_LEAD__000ecd40;
	iVar20 = 0x28;
	do {
		iVar20 = iVar20 + -1;
		*piVar10 = ((cp->hd).speed + 100) * 10;
		piVar10 = piVar10 + 1;
	} while (-1 < iVar20);
	cellx = (uint)*(ushort *)(cp->ai + 2) & 0xfff;
	DAT_LEAD__000ecd3c = (int)rcossin_tbl[cellx * 2];
	iVar20 = basePos->vx + units_across_halved;
	iVar15 = iVar20 + -0x400;
	DAT_LEAD__000ecd38 = (int)rcossin_tbl[cellx * 2 + 1];
	if (iVar15 < 0) {
		iVar15 = iVar20 + 0x3ff;
	}
	ClearCopUsage();
	local_30 = 0;
	cellx = (iVar15 >> 0xb) - 5;
	do {
		iVar20 = basePos->vz + units_down_halved;
		iVar15 = iVar20 + -0x400;
		if (iVar15 < 0) {
			iVar15 = iVar20 + 0x3ff;
		}
		iVar20 = 0;
		local_2c = cellx << 0xb;
		local_30 = local_30 + 1;
		local_34 = cellx + 1;
		cellz = (iVar15 >> 0xb) - 5;
		do {
			iVar15 = IsOnMap((local_2c - units_across_halved) + 0x400,
				(cellz * 0x800 - units_down_halved) + 0x400, basePos, intention, cp);
			iVar20 = iVar20 + 1;
			if (iVar15 != 0) {
				iVar15 = cells_across;
				if (cells_across < 0) {
					iVar15 = cells_across + 0x1f;
				}
				if (RoadMapRegions[(cellx >> 5 & 1) + (cellz >> 5 & 1) * 2] ==
					(cellx >> 5) + (cellz >> 5) * (iVar15 >> 5)) {
					ppco = GetFirstPackedCop(cellx, cellz, (CELL_ITERATOR *)&local_158, 1);
					while (pCVar6 = UnpackCellObject(ppco, (XZPAIR *)(&local_158 + 8)),
						pCVar6 != (CELL_OBJECT *)0x0) {
						pMVar11 = modelpointers1536[pCVar6->type];
						if (((((uint)pMVar11->num_vertices - 3 < 300) && (pMVar11->num_point_normals < 300)) &&
							(pMVar11->num_polys < 300)) &&
							((piVar10 = (int *)pMVar11->collision_block, piVar10 != (int *)0x0 &&
							((pMVar11->flags2 & 0x800) == 0)))) {
							iVar15 = *piVar10;
							piVar10 = piVar10 + 1;
							if (0 < iVar15) {
								do {
									uVar9 = -(uint)pCVar6->yang & 0x3f;
									psVar1 = (short *)((int)piVar10 + 2);
									psVar2 = (short *)((int)piVar10 + 6);
									if (*(short *)piVar10 == 0) {
										iVar17 = (uint)*(ushort *)((int)piVar10 + 0x12) << 0x10;
										uVar22 = ((uint)pCVar6->yang + (int)*(short *)((int)piVar10 + 10)) * 0x100 &
											0x3f00;
										iVar18 = (int)*(short *)((int)rcossin_tbl + uVar22);
										iVar16 = (iVar17 >> 0x10) - (iVar17 >> 0x1f) >> 1;
										iVar17 = iVar16 * iVar18;
										iVar13 = (int)*(short *)((int)rcossin_tbl + uVar22 + 2);
										iVar5 = (uint)*(ushort *)((int)piVar10 + 0xe) << 0x10;
										iVar12 = (iVar5 >> 0x10) - (iVar5 >> 0x1f) >> 1;
										iVar5 = iVar12 * iVar13;
										iVar16 = iVar16 * iVar13;
										iVar12 = iVar12 * iVar18;
										if (iVar17 < 0) {
											iVar17 = -iVar17;
										}
										if (iVar5 < 0) {
											iVar5 = -iVar5;
										}
										local_120 = (VECTOR *)(iVar17 + iVar5 + 0x800 >> 0xc);
										local_11c = (VECTOR *)(int)*(short *)(piVar10 + 4);
										if (iVar16 < 0) {
											iVar16 = -iVar16;
										}
										if (iVar12 < 0) {
											iVar12 = -iVar12;
										}
										local_118 = (VECTOR *)((iVar16 - iVar12) + 0x800 >> 0xc);
									}
									local_140 = ((int)*(short *)((int)piVar10 + 2) * (int)(&matrixtable)[uVar9].m[0] +
										(int)*(short *)((int)piVar10 + 6) * (int)(&matrixtable)[uVar9].m[6] +
										0x800 >> 0xc) + (pCVar6->pos).vx;
									iVar15 = iVar15 + -1;
									piVar10 = piVar10 + 5;
									local_13c = -(pCVar6->pos).vy - (pCVar6->pos).vy;
									local_130 = 0;
									local_128 = (_CAR_DATA *)0x0;
									local_110.vel = (VECTOR *)0x0;
									local_110.pos = (VECTOR *)&local_140;
									local_110.size = (VECTOR *)(&local_128 + 8);
									local_110.map = &DAT_LEAD__000ecde8;
									local_110.local = &DAT_LEAD__000ecd40;
									local_138 = ((int)*psVar1 * (int)(&matrixtable)[uVar9].m[2] +
										(int)*psVar2 * (int)(&matrixtable)[uVar9].m[8] + 0x800 >> 0xc) +
										(pCVar6->pos).vz;
									local_110.cp = cp;
									local_110.base = basePos;
									local_110.intention = intention;
									BlockToMap(&local_110);
								} while (iVar15 != 0);
							}
						}
						ppco = GetNextPackedCop((CELL_ITERATOR *)&local_158);
					}
				}
			}
			cellz = cellz + 1;
		} while (iVar20 < 0xb);
		cellx = local_34;
	} while (local_30 < 0xb);
	p_Var21 = car_data + 0x13;
	while ((_CAR_DATA *)((int)&cheats.MagicMirror + 3U) < p_Var21) {
		if ((p_Var21 != cp) && (p_Var21->controlType != '\0')) {
			pCVar14 = (p_Var21->ap).carCos;
			iVar20 = (uint)(ushort)(pCVar14->colBox).vz << 0x10;
			iVar20 = (int)(p_Var21->hd).where.m[6] * ((iVar20 >> 0x10) - (iVar20 >> 0x1f) >> 1);
			iVar15 = (uint)(ushort)(pCVar14->colBox).vx << 0x10;
			iVar15 = (int)(p_Var21->hd).where.m[0] * ((iVar15 >> 0x10) - (iVar15 >> 0x1f) >> 1);
			if (iVar20 < 0) {
				iVar20 = -iVar20;
			}
			if (iVar15 < 0) {
				iVar15 = -iVar15;
			}
			local_138 = (iVar20 + iVar15 + 0x800 >> 0xc) + (int)(pCVar14->colBox).vy;
			local_134 = (int)(pCVar14->colBox).vy;
			iVar20 = (uint)(ushort)(pCVar14->colBox).vz << 0x10;
			iVar20 = (int)(p_Var21->hd).where.m[8] * ((iVar20 >> 0x10) - (iVar20 >> 0x1f) >> 1);
			iVar15 = (uint)(ushort)(pCVar14->colBox).vx << 0x10;
			iVar15 = (int)(p_Var21->hd).where.m[2] * ((iVar15 >> 0x10) - (iVar15 >> 0x1f) >> 1);
			local_148 = *(int *)(cp->st + 0x1c);
			local_158 = (CELL_DATA *)(p_Var21->hd).where.t[0];
			local_154 = (PACKED_CELL_OBJECT *)(p_Var21->hd).where.t[1];
			local_150 = (p_Var21->hd).where.t[2];
			if (iVar20 < 0) {
				iVar20 = -iVar20;
			}
			if (iVar15 < 0) {
				iVar15 = -iVar15;
			}
			local_130 = (iVar20 + iVar15 + 0x800 >> 0xc) + (int)(pCVar14->colBox).vy;
			if (local_148 < 0) {
				local_148 = local_148 + 0x3ff;
			}
			local_140 = *(int *)(cp->st + 0x24);
			local_148 = local_148 >> 10;
			if (local_140 < 0) {
				local_140 = local_140 + 0x3ff;
			}
			local_140 = local_140 >> 10;
			local_11c = (VECTOR *)(&local_158 + 0x10);
			local_120 = (VECTOR *)&local_158;
			local_118 = (VECTOR *)(&local_140 + 8);
			local_110.cp = (_CAR_DATA *)&DAT_LEAD__000ecde8;
			local_110.base = (VECTOR *)&DAT_LEAD__000ecd40;
			local_128 = cp;
			local_124 = basePos;
			local_114 = intention;
			BlockToMap((MAP_DATA *)&local_128);
		}
		p_Var21 = p_Var21 + -1;
	}
	if ((cp->ai[0] != 4) &&
		(((iVar20 = ((cp->hd).speed + 100) * 8, DAT_LEAD__000ecd90 < iVar20 ||
		(DAT_LEAD__000ecd94 < iVar20)) || (DAT_LEAD__000ecd98 < iVar20)))) {
		iVar20 = 1;
		piVar10 = &DAT_LEAD__000ecd9c;
		piVar19 = &DAT_LEAD__000ecd8c;
		while (true) {
			iVar17 = *piVar19 + (&DAT_LEAD__000ecd40)[0x15 - iVar20] +
				(&DAT_LEAD__000ecd40)[0x16 - iVar20];
			iVar15 = piVar10[-2] + piVar10[-1] + *piVar10;
			if ((iVar17 < iVar15) && (((cp->hd).speed + 100) * 0x18 < iVar15 * 2)) {
				if (0xd < iVar20) {
					*(undefined4 *)(cp->ai + 0x24) = 2;
					return;
				}
				*(undefined4 *)(cp->ai + 0x24) = 1;
				return;
			}
			if ((iVar17 > iVar15) && (((cp->hd).speed + 100) * 0x18 < iVar17 * 2)) break;
			if (iVar20 == 0x14) {
				if (iVar17 <= iVar15) {
					*(undefined4 *)(cp->ai + 0x24) = 2;
				}
				else {
					*(undefined4 *)(cp->ai + 0x24) = 0xfffffffe;
				}
			}
			piVar10 = piVar10 + 1;
			iVar20 = iVar20 + 1;
			piVar19 = piVar19 + -1;
			if (0x14 < iVar20) {
				return;
			}
		}
		if (0xd < iVar20) {
			*(undefined4 *)(cp->ai + 0x24) = 0xfffffffe;
			return;
		}
		*(undefined4 *)(cp->ai + 0x24) = 0xffffffff;
		return;
	}
	*(undefined4 *)(cp->ai + 0x24) = 0;
	bVar3 = (uint)intention < 2;
	cellx = intention - 2;
	if (bVar3) {
		iVar15 = 0x18;
		piVar10 = &DAT_LEAD__000ece48;
		iVar20 = DAT_LEAD__000ece48;
		do {
			if (*piVar10 < iVar20) {
				iVar20 = *piVar10;
			}
			iVar17 = SquareRoot0(iVar15 + -0x15);
			if (iVar20 < ((cp->hd).speed + 100) * iVar17) {
				*piVar10 = 0;
			}
			iVar15 = iVar15 + 1;
			piVar10 = piVar10 + 1;
		} while (iVar15 < 0x29);
		iVar15 = 0x12;
		piVar10 = &DAT_LEAD__000ece30;
		iVar20 = DAT_LEAD__000ece30;
		do {
			if (*piVar10 < iVar20) {
				iVar20 = *piVar10;
			}
			iVar17 = SquareRoot0(0x15 - iVar15);
			if (iVar20 < ((cp->hd).speed + 100) * iVar17) {
				*piVar10 = 0;
			}
			iVar15 = iVar15 + -1;
			piVar10 = piVar10 + -1;
		} while (-1 < iVar15);
	}
	if (cellx < 2) {
		piVar19 = &DAT_LEAD__000ecde8;
		iVar20 = 0x28;
		piVar10 = local_f0;
		do {
			iVar15 = *piVar19;
			piVar19 = piVar19 + 1;
			iVar20 = iVar20 + -1;
			*piVar10 = iVar15;
			piVar10 = piVar10 + 1;
		} while (-1 < iVar20);
		iVar20 = 0;
		do {
			iVar15 = 0;
			(&DAT_LEAD__000ecde8)[iVar20] = 0;
			cellz = iVar20 - 3;
			iVar17 = iVar20 + 1;
			if ((int)cellz < iVar20 + 4) {
				piVar10 = local_f0 + cellz;
				do {
					if (cellz < 0x29) {
						(&DAT_LEAD__000ecde8)[iVar20] = (&DAT_LEAD__000ecde8)[iVar20] + *piVar10;
					}
					piVar10 = piVar10 + 1;
					cellz = cellz + 1;
					iVar15 = iVar15 + 1;
				} while ((int)cellz < iVar20 + 4);
			}
			if (iVar15 == 0) {
				trap(7);
			}
			(&DAT_LEAD__000ecde8)[iVar20] = (int)(&DAT_LEAD__000ecde8)[iVar20] / iVar15;
			iVar20 = iVar17;
		} while (iVar17 < 0x29);
	}
	if (intention == 4) {
		iVar17 = 0;
		iVar15 = 0x3f;
		iVar20 = -0x15;
		piVar10 = &DAT_LEAD__000ecde8;
		do {
			iVar5 = *piVar10 * 0x15;
			*piVar10 = iVar5;
			if (iVar17 + -0x15 < 0) {
				if (iVar15 == 0) {
					trap(7);
				}
				*piVar10 = iVar5 / iVar15;
			}
			else {
				if (iVar20 == 0) {
					trap(7);
				}
				*piVar10 = iVar5 / iVar20;
			}
			iVar15 = iVar15 + -2;
			iVar20 = iVar20 + 2;
			iVar17 = iVar17 + 1;
			piVar10 = piVar10 + 1;
		} while (iVar17 < 0x29);
	}
	if ((bVar3) && (*(int *)(cp->ai + 0x18) < 10)) {
		iVar20 = *(int *)(cp->ai + 0x34);
		if (iVar20 < 0x1f) {
			iVar17 = *(int *)(cp->ai + 0x44) - *(int *)(cp->ai + 0x48);
			iVar15 = *(int *)(cp->ai + 0x2c) - iVar17;
			if (iVar15 < 0) {
				iVar15 = iVar17 - *(int *)(cp->ai + 0x2c);
			}
			if ((iVar15 < *(int *)(cp->ai + 0x44) / 3) && (iVar20 < 0x1f)) {
				*(int *)(cp->ai + 0x34) = iVar20 + 1;
			}
		}
		else {
			iVar15 = *(int *)(cp->ai + 0x44) - *(int *)(cp->ai + 0x48);
			iVar20 = *(int *)(cp->ai + 0x2c) - iVar15;
			if (iVar20 < 0) {
				iVar20 = iVar15 - *(int *)(cp->ai + 0x2c);
			}
			if (iVar20 < *(int *)(cp->ai + 0x44) / 3) {
				*(int *)(cp->ai + 0x38) = *(int *)(cp->ai + 0x44) - *(int *)(cp->ai + 0x48);
				*(int *)(cp->ai + 0x34) = *(int *)(cp->ai + 0x34) + 1;
			}
			iVar17 = 0;
			piVar10 = &DAT_LEAD__000ecde8;
			local_38 = ((*(int *)(cp->ai + 0x38) + *(int *)(cp->ai + 0x48)) - *(int *)(cp->ai + 0x44)) /
				100 + 0x15;
			iVar15 = local_38 * 100;
			iVar20 = local_38 * -100;
			do {
				iVar5 = iVar20;
				if (-1 < local_38 - iVar17) {
					iVar5 = iVar15;
				}
				if (iVar5 < *(int *)(cp->ai + 0x44) / 3) {
					*piVar10 = *piVar10 + *(int *)(cp->ai + 0x34) * -100;
				}
				piVar10 = piVar10 + 1;
				iVar20 = iVar20 + 100;
				iVar17 = iVar17 + 1;
				iVar15 = iVar15 + -100;
			} while (iVar17 < 0x29);
			iVar20 = *(int *)(cp->ai + 0x44) / 3;
			iVar17 = *(int *)(cp->ai + 0x44) - *(int *)(cp->ai + 0x48);
			iVar15 = iVar17 - *(int *)(cp->ai + 0x38);
			if (iVar15 < 0) {
				if (iVar20 < *(int *)(cp->ai + 0x38) - iVar17) {
					*(undefined4 *)(cp->ai + 0x34) = 0;
				}
			}
			else {
				if (iVar20 < iVar15) goto LAB_LEAD__000ea89c;
			}
		}
	}
	else {
	LAB_LEAD__000ea89c:
		*(undefined4 *)(cp->ai + 0x34) = 0;
	}
	if (1 < intention - 4U) {
		local_3c = *(int *)(cp->ai + 0x48);
		local_44 = 0;
		local_48 = local_3c - *(int *)(cp->ai + 0x44);
		local_40 = *(int *)(cp->ai + 0x44) + local_3c;
		PosToIndex((int *)&local_48, (int *)&local_44, intention, cp);
		PosToIndex((int *)&local_40, (int *)&local_44, intention, cp);
		PosToIndex(&local_3c, (int *)&local_44, intention, cp);
		if (((int)local_48 < local_3c) && (local_3c < (int)local_40)) {
			iVar20 = *(int *)(cp->ai + 0x18);
			if (((iVar20 == 0xf) || (iVar20 == 0x11)) && (1 < cellx)) {
				*(int *)(cp->ai + 0x18) = iVar20 + -0x10;
				local_44 = local_48;
				while ((int)local_44 <= (int)local_40) {
					iVar20 = 2000;
					if (0 < (int)((local_44 - local_3c) * *(int *)(cp->ai + 0x18))) {
						iVar20 = -2000;
					}
					if (local_44 < 0x29) {
						iVar15 = (&DAT_LEAD__000ecde8)[local_44];
						if (0 < iVar15) {
							(&DAT_LEAD__000ecde8)[local_44] = iVar15 + iVar20;
						}
					}
					local_44 = local_44 + 1;
				}
			}
			iVar20 = 0;
			while (local_48 < 0x29) {
				(&DAT_LEAD__000ecde8)[local_48] = (&DAT_LEAD__000ecde8)[local_48] - iVar20;
				if ((int)(&DAT_LEAD__000ecde8)[local_48] < 0) {
					(&DAT_LEAD__000ecde8)[local_48] = 0;
				}
				local_48 = local_48 - 1;
				iVar20 = iVar20 + 500;
			}
			iVar20 = 0;
			while (local_40 < 0x29) {
				(&DAT_LEAD__000ecde8)[local_40] = (&DAT_LEAD__000ecde8)[local_40] - iVar20;
				if ((int)(&DAT_LEAD__000ecde8)[local_40] < 0) {
					(&DAT_LEAD__000ecde8)[local_40] = 0;
				}
				local_40 = local_40 + 1;
				iVar20 = iVar20 + 500;
			}
		}
	}
	if (cellx < 3) {
	LAB_LEAD__000ead84:
		cellz = 0x15;
		uVar22 = 0x15;
		uVar9 = 0;
		iVar15 = 0x54;
		iVar20 = DAT_LEAD__000ece3c;
		do {
			if (iVar20 < *(int *)((int)&DAT_LEAD__000ecde8 + iVar15)) {
				iVar20 = *(int *)((int)&DAT_LEAD__000ecde8 + iVar15);
				cellz = uVar22;
			}
			if ((int)uVar9 < 0) {
				uVar9 = -uVar9;
			}
			uVar9 = uVar9 + 1;
			if ((uVar9 & 1) == 0) {
				uVar9 = -uVar9;
			}
			uVar22 = uVar22 + uVar9;
			iVar15 = uVar22 * 4;
		} while (uVar22 < 0x29);
		if (cellx < 2) {
			iVar15 = (cp->hd).speed;
			if (iVar15 < 0x65) {
				iVar15 = DAT_LEAD__000ece98 + iVar15 * DAT_LEAD__000ece9c;
			}
			else {
				iVar15 = DAT_LEAD__000eceb8 + (iVar15 + -100) * DAT_LEAD__000ecebc;
			}
			if (iVar20 < iVar15) {
				iVar20 = *(int *)(cp->ai + 0x30) + -1;
				if (-1 < *(int *)(cp->ai + 0x30)) {
					iVar20 = -1;
				}
				*(int *)(cp->ai + 0x30) = iVar20;
				puVar7 = &DAT_00004e20;
				if (intention == 3) {
					puVar7 = (undefined *)0xffffb1e0;
				}
				*(undefined **)(cp->ai + 0x2c) = puVar7;
				if (-0x15 < *(int *)(cp->ai + 0x30)) {
					return;
				}
				SelectExit(cp, Driver2JunctionsPtr + *(int *)(cp->ai + 0x14) + -0x2000);
				return;
			}
		}
	}
	else {
		cellz = *(uint *)(cp->ai + 0x3c);
		if (*(int *)(cp->ai + 0x34) < 0x1f) {
		LAB_LEAD__000eac54:
			iVar20 = cellz - 1;
			if (iVar20 < 0) {
				iVar15 = 0;
			}
			else {
				iVar15 = iVar20 * 4;
				if (0x28 < iVar20) {
					iVar15 = 0xa0;
				}
			}
			iVar20 = (cp->hd).speed;
			if (*(int *)((int)&DAT_LEAD__000ecde8 + iVar15) <= ((iVar20 + 100) / 0x32) * 0x400) {
				if ((int)cellz < 0) {
					iVar15 = 0;
				}
				else {
					uVar9 = cellz;
					if (0x28 < (int)cellz) {
						uVar9 = 0x28;
					}
					iVar15 = uVar9 << 2;
				}
				if (*(int *)((int)&DAT_LEAD__000ecde8 + iVar15) <= ((iVar20 + 100) / 0x32) * 0x400) {
					iVar15 = cellz + 1;
					if (iVar15 < 0) {
						iVar17 = 0;
					}
					else {
						iVar17 = iVar15 * 4;
						if (0x28 < iVar15) {
							iVar17 = 0xa0;
						}
					}
					if (*(int *)((int)&DAT_LEAD__000ecde8 + iVar17) <= ((iVar20 + 100) / 0x32) * 0x400)
						goto LAB_LEAD__000ead84;
				}
			}
		}
		else {
			iVar20 = (cellz - local_38) * 100;
			if (iVar20 < 0) {
				iVar20 = (cellz - local_38) * -100;
			}
			if (iVar20 < *(int *)(cp->ai + 0x44) / 3) goto LAB_LEAD__000ead84;
			iVar20 = cellz - 1;
			if (iVar20 < 0) {
				iVar15 = 0;
			}
			else {
				iVar15 = iVar20 * 4;
				if (0x28 < iVar20) {
					iVar15 = 0xa0;
				}
			}
			iVar20 = (cp->hd).speed;
			if (*(int *)((int)&DAT_LEAD__000ecde8 + iVar15) <= ((iVar20 + 100) / 0x32) * 0x400) {
				if ((int)cellz < 0) {
					iVar15 = 0;
				}
				else {
					uVar9 = cellz;
					if (0x28 < (int)cellz) {
						uVar9 = 0x28;
					}
					iVar15 = uVar9 << 2;
				}
				if (*(int *)((int)&DAT_LEAD__000ecde8 + iVar15) <= ((iVar20 + 100) / 0x32) * 0x400) {
					iVar15 = cellz + 1;
					if (iVar15 < 0) {
						iVar17 = 0;
					}
					else {
						iVar17 = iVar15 * 4;
						if (0x28 < iVar15) {
							iVar17 = 0xa0;
						}
					}
					if (*(int *)((int)&DAT_LEAD__000ecde8 + iVar17) <= ((iVar20 + 100) / 0x32) * 0x400)
						goto LAB_LEAD__000ead84;
				}
			}
			if (*(int *)(cp->ai + 0x34) < 0x1f) goto LAB_LEAD__000eac54;
		}
		iVar20 = (&DAT_LEAD__000ecde8)[cellz];
		uVar9 = cellz - 2;
		iVar15 = cellz + 2;
		if ((int)uVar9 < iVar15) {
			piVar10 = &DAT_LEAD__000ecde8 + uVar9;
			do {
				if ((uVar9 < 0x29) && (iVar20 < *piVar10)) {
					iVar20 = *piVar10;
					cellz = uVar9;
				}
				uVar9 = uVar9 + 1;
				piVar10 = piVar10 + 1;
			} while ((int)uVar9 < iVar15);
		}
	}
	if ((bVar3) || (intention == 4)) {
		*(undefined4 *)(cp->ai + 0x30) = 0x1400;
		iVar20 = 1;
		if (0x15 < (int)cellz) {
			iVar20 = -1;
		}
		if (cellz != 0x15) {
			piVar10 = &DAT_LEAD__000ecde8 + cellz;
			uVar9 = cellz;
			do {
				if (*piVar10 < *(int *)(cp->ai + 0x30)) {
					*(int *)(cp->ai + 0x30) = *piVar10;
				}
				uVar9 = uVar9 + iVar20;
				piVar10 = piVar10 + iVar20;
			} while (uVar9 != 0x15);
			*(uint *)(cp->ai + 0x3c) = cellz;
			goto LAB_LEAD__000eb0c8;
		}
	}
	else {
		if (intention == 5) {
			if ((*(int *)(cp->ai + 0x28) == 0) || (0x14 < *(int *)(cp->ai + 0x28))) {
				piVar10 = &DAT_LEAD__000ece38;
				iVar15 = 3;
				*(undefined4 *)(cp->ai + 0x28) = 0;
				iVar20 = DAT_LEAD__000ece34;
				do {
					if (*piVar10 < iVar20) {
						iVar20 = *piVar10;
					}
					iVar15 = iVar15 + -1;
					piVar10 = piVar10 + 1;
				} while (-1 < iVar15);
				uVar8 = 0xffffffff;
				if (DAT_LEAD__000ece80 <= iVar20) {
					uVar8 = 1;
				}
				*(undefined4 *)(cp->ai + 0x30) = uVar8;
			}
			if ((((0x5dc < DAT_LEAD__000ece3c) && (0x5dc < DAT_LEAD__000ece40)) &&
				(0x5dc < DAT_LEAD__000ece38)) && (0x28 < (cp->hd).speed)) {
				*(undefined4 *)(cp->ai + 0x30) = 0;
			}
		}
		else {
			*(undefined4 *)(cp->ai + 0x30) = 0;
		}
	}
	*(uint *)(cp->ai + 0x3c) = cellz;
LAB_LEAD__000eb0c8:
	iVar20 = cellz - 0x15;
	if (intention == 6) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	if (intention - 4U < 2) {
		if (intention == 4) {
			iVar20 = iVar20 * 0x600;
		}
		else {
			iVar20 = iVar20 * 0x800;
		}
		iVar20 = ((iVar20 / 0x15 + 0x800U & 0xfff) + (cp->hd).direction & 0xfff) - 0x800;
	}
	else {
		if (bVar3) {
			iVar20 = (iVar20 * 200 + *(int *)(cp->ai + 0x44)) - *(int *)(cp->ai + 0x48);
		}
		else {
			if (1 < cellx) {
				return;
			}
			iVar20 = iVar20 * 100 + *(int *)(cp->ai + 0x44);
		}
	}
	*(int *)(cp->ai + 0x2c) = iVar20;
	return;*/
}



// autogenerated function stub: 
// void slowWallTests() /* slowWallTests method signature is not contained in the debug symbol data. This is likely either a library function or the game was compiled without debug symbols. Please refer to the TDR documentation for additional guidance. */
void slowWallTests()
{
	// line 1807, offset 0x000e913c
	UNIMPLEMENTED();
}


// autogenerated function stub: 
// void asf() /* asf method signature is not contained in the debug symbol data. This is likely either a library function or the game was compiled without debug symbols. Please refer to the TDR documentation for additional guidance. */
void asf()
{ // line 1811, offset 0x000e9158
	UNIMPLEMENTED();
}


// autogenerated function stub: 
// void DoExtraWorkForNFrames() /* DoExtraWorkForNFrames method signature is not contained in the debug symbol data. This is likely either a library function or the game was compiled without debug symbols. Please refer to the TDR documentation for additional guidance. */
void DoExtraWorkForNFrames()
{ // line 2195, offset 0x000e99ac
	UNIMPLEMENTED();
}


// autogenerated function stub: 
// void searchTarget() /* searchTarget method signature is not contained in the debug symbol data. This is likely either a library function or the game was compiled without debug symbols. Please refer to the TDR documentation for additional guidance. */
void searchTarget()
{ // line 2233, offset 0x000e9ab8
	UNIMPLEMENTED();
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

void CheckCurrentRoad(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	undefined4 uVar2;
	ulong uVar3;
	uint cr;
	int iVar4;
	int iVar5;
	DRIVER2_STRAIGHT *pDVar6;
	DRIVER2_JUNCTION *junction;
	DRIVER2_CURVE *pDVar7;
	int iVar8;
	uint cr_00;

	bVar1 = false;
	if ((((cp->hd).wheel[1].surface & 7) == 3) || (((cp->hd).wheel[3].surface & 7) == 3)) {
		cr_00 = *(uint *)(cp->ai + 0xc);
	}
	else {
		cr_00 = GetSurfaceIndex((VECTOR *)(cp->hd).where.t);
	}
	cr = cr_00 & 0xffffe000;
	if (((cr == 0) || (cr == 0x4000)) || (cr == 0x2000)) {
		*(undefined4 *)(cp->ai + 0x40) = 0;
		if ((cr_00 != *(uint *)(cp->ai + 0x10)) && (cr_00 != *(uint *)(cp->ai + 0xc))) {
			*(undefined4 *)(cp->ai + 0x5c) = 0;
		}
	}
	else {
		cr_00 = *(uint *)(cp->ai + 0x10);
		*(undefined4 *)(cp->ai + 0x5c) = *(undefined4 *)(cp->ai + 0x60);
	}
	cr = cr_00 & 0xffffe000;
	if (cr == 0x2000) {
		bVar1 = true;
		DAT_LEAD__000ecc60 = cr_00;
		goto LAB_LEAD__000eb96c;
	}
	if ((int)cr < 0x2001) {
		if (cr == 0) {
			pDVar6 = Driver2StraightsPtr + cr_00;
			DAT_LEAD__000ecc88 = (uint)(ushort)pDVar6->angle & 0xfff;
			iVar5 = (cp->hd).where.t[2] - pDVar6->Midz;
			DAT_LEAD__000ecc60 = SEXT24(pDVar6->ConnectIdx[1]);
			iVar8 = (cp->hd).where.t[0] - pDVar6->Midx;
			if (DAT_LEAD__000ecc60 == 0xffffffff) {
				DAT_LEAD__000ecc60 = SEXT24(pDVar6->ConnectIdx[0]);
			}
			if (*(int *)(cp->ai + 0x5c) == 0) {
				uVar2 = 0xffffffff;
				if ((((cp->hd).direction - DAT_LEAD__000ecc88) + 0x400 & 0x800) == 0) {
					uVar2 = 1;
				}
				*(undefined4 *)(cp->ai + 0x5c) = uVar2;
			}
			if (*(int *)(cp->ai + 0x5c) == -1) {
				DAT_LEAD__000ecc88 = DAT_LEAD__000ecc88 ^ 0x800;
				DAT_LEAD__000ecc60 = SEXT24(pDVar6->ConnectIdx[3]);
				if (DAT_LEAD__000ecc60 == 0xffffffff) {
					DAT_LEAD__000ecc60 = SEXT24(pDVar6->ConnectIdx[2]);
				}
			}
			DAT_LEAD__000ecc8c = (int)rcossin_tbl[(DAT_LEAD__000ecc88 & 0xfff) * 2];
			DAT_LEAD__000ecc90 = (int)rcossin_tbl[(DAT_LEAD__000ecc88 & 0xfff) * 2 + 1];
			DAT_LEAD__000ecc80 = DAT_LEAD__000ecc8c * iVar8 + DAT_LEAD__000ecc90 * iVar5 + 0x800 >> 0xc;
			iVar4 = (cp->hd).speed;
			DAT_LEAD__000ecc84 = (uint)(pDVar6->length >> 1) - DAT_LEAD__000ecc80;
			if (iVar4 < 0x65) {
				iVar4 = DAT_LEAD__000ece98 + iVar4 * DAT_LEAD__000ece9c;
			}
			else {
				iVar4 = DAT_LEAD__000eceb8 + (iVar4 + -100) * DAT_LEAD__000ecebc;
			}
			if (((DAT_LEAD__000ecc84 < iVar4) && (*(int *)(cp->ai + 0x40) == 0)) && (cp->ai[0] != 5)) {
				bVar1 = true;
				*(undefined4 *)(cp->ai + 0x5c) = 0;
			}
			else {
				iVar4 = (cp->hd).speed;
				if (iVar4 < 0x65) {
					iVar4 = DAT_LEAD__000ece98 + iVar4 * DAT_LEAD__000ece9c;
				}
				else {
					iVar4 = DAT_LEAD__000eceb8 + (iVar4 + -100) * DAT_LEAD__000ecebc;
				}
				if (DAT_LEAD__000ecc84 < iVar4 * 3) {
					*(int *)(cp->ai + 0x18) = *(int *)(cp->ai + 0x18) + 0x10;
				}
				*(int *)(cp->ai + 0x48) =
					-DAT_LEAD__000ecc90 * iVar8 + DAT_LEAD__000ecc8c * iVar5 + 0x800 >> 0xc;
				*(uint *)(cp->ai + 0x44) = ((uint)(byte)pDVar6->NumLanes & 0xf) << 9;
			}
			goto LAB_LEAD__000eb96c;
		}
	}
	else {
		if (cr == 0x4000) {
			pDVar7 = Driver2CurvesPtr + (cr_00 - 0x4000);
			DAT_LEAD__000ecc9c = (cp->hd).where.t[0] - pDVar7->Midx;
			DAT_LEAD__000ecca0 = (cp->hd).where.t[2] - pDVar7->Midz;
			DAT_LEAD__000ecc94 = ratan2(DAT_LEAD__000ecc9c, DAT_LEAD__000ecca0);
			if (*(int *)(cp->ai + 0x5c) == 0) {
				uVar2 = 1;
				if ((DAT_LEAD__000ecc94 - (cp->hd).direction & 0x800U) == 0) {
					uVar2 = 0xffffffff;
				}
				*(undefined4 *)(cp->ai + 0x5c) = uVar2;
			}
			if (*(int *)(cp->ai + 0x5c) == 1) {
				DAT_LEAD__000ecc98 =
					((uint)(byte)pDVar7->inside + ((uint)(byte)pDVar7->NumLanes & 0xf)) * 0x400 -
					*(int *)(cp->ai + 0x2c);
				iVar8 = (cp->hd).speed;
				if (iVar8 < 0x65) {
					iVar8 = iVar8 * DAT_LEAD__000ece9c;
					iVar5 = DAT_LEAD__000ece98;
				}
				else {
					iVar8 = (iVar8 + -100) * DAT_LEAD__000ecebc;
					iVar5 = DAT_LEAD__000eceb8;
				}
				DAT_LEAD__000ecca4 = (iVar5 + iVar8) / DAT_LEAD__000ecc98;
				if (DAT_LEAD__000ecc98 == 0) {
					trap(7);
				}
				if ((DAT_LEAD__000ecca4 < 0x1000) || ((pDVar7->end - DAT_LEAD__000ecc94 & 1U) == 0)) {
					if ((0xfff < DAT_LEAD__000ecca4 * 3) && ((pDVar7->end - DAT_LEAD__000ecc94 & 1U) != 0)) {
						*(int *)(cp->ai + 0x18) = *(int *)(cp->ai + 0x18) + 0x10;
					}
					uVar3 = hypot(DAT_LEAD__000ecc9c, DAT_LEAD__000ecca0);
					iVar8 = DAT_LEAD__000ecc94;
					*(ulong *)(cp->ai + 0x48) = uVar3;
					*(ulong *)(cp->ai + 0x4c) = uVar3;
					*(undefined4 *)(cp->ai + 0x54) = 1;
					*(int *)(cp->ai + 0x50) = iVar8;
					*(ulong *)(cp->ai + 0x48) =
						uVar3 - ((uint)(byte)pDVar7->inside * 0x400 +
						((uint)(byte)pDVar7->NumLanes & 0xf) * 0x200);
				LAB_LEAD__000eb940:
					*(uint *)(cp->ai + 0x44) = ((uint)(byte)pDVar7->NumLanes & 0xf) << 9;
					goto LAB_LEAD__000eb96c;
				}
				DAT_LEAD__000ecc60 = SEXT24(pDVar7->ConnectIdx[1]);
				if (DAT_LEAD__000ecc60 == 0xffffffff) {
					DAT_LEAD__000ecc60 = SEXT24(pDVar7->ConnectIdx[0]);
				}
			}
			else {
				iVar8 = (cp->hd).speed;
				DAT_LEAD__000ecc98 = (uint)(byte)pDVar7->inside * 0x400 + *(int *)(cp->ai + 0x2c);
				if (iVar8 < 0x65) {
					iVar8 = iVar8 * DAT_LEAD__000ece9c;
					iVar5 = DAT_LEAD__000ece98;
				}
				else {
					iVar8 = (iVar8 + -100) * DAT_LEAD__000ecebc;
					iVar5 = DAT_LEAD__000eceb8;
				}
				DAT_LEAD__000ecca4 = (iVar5 + iVar8) / DAT_LEAD__000ecc98;
				if (DAT_LEAD__000ecc98 == 0) {
					trap(7);
				}
				if ((DAT_LEAD__000ecca4 < 0x1000) || ((DAT_LEAD__000ecc94 - pDVar7->start & 1U) == 0)) {
					if ((0xfff < DAT_LEAD__000ecca4 * 3) && ((DAT_LEAD__000ecc94 - pDVar7->start & 1U) != 0))
					{
						*(int *)(cp->ai + 0x18) = *(int *)(cp->ai + 0x18) + 0x10;
					}
					uVar3 = hypot(DAT_LEAD__000ecc9c, DAT_LEAD__000ecca0);
					iVar8 = DAT_LEAD__000ecc94;
					*(ulong *)(cp->ai + 0x48) = uVar3;
					*(ulong *)(cp->ai + 0x4c) = uVar3;
					*(undefined4 *)(cp->ai + 0x54) = 0xffffffff;
					*(int *)(cp->ai + 0x50) = iVar8;
					*(uint *)(cp->ai + 0x48) =
						((uint)(byte)pDVar7->inside * 0x400 + ((uint)(byte)pDVar7->NumLanes & 0xf) * 0x200) -
						uVar3;
					goto LAB_LEAD__000eb940;
				}
				DAT_LEAD__000ecc60 = SEXT24(pDVar7->ConnectIdx[3]);
				if (DAT_LEAD__000ecc60 == 0xffffffff) {
					DAT_LEAD__000ecc60 = SEXT24(pDVar7->ConnectIdx[2]);
				}
			}
			bVar1 = true;
			*(undefined4 *)(cp->ai + 0x5c) = 0;
			goto LAB_LEAD__000eb96c;
		}
	}
	cr_00 = *(uint *)(cp->ai + 0x10);
LAB_LEAD__000eb96c:
	cr = DAT_LEAD__000ecc60;
	if (bVar1) {
		cr_00 = DAT_LEAD__000ecc60 & 0xffffe000;
		if (cr_00 == 0x2000) {
			junction = Driver2JunctionsPtr + (DAT_LEAD__000ecc60 - 0x2000);
			if (DAT_LEAD__000ecc60 != *(uint *)(cp->ai + 0x14)) {
				SelectExit(cp, junction);
				*(uint *)(cp->ai + 0x14) = DAT_LEAD__000ecc60;
			}
			cr = SEXT24(junction->ExitIdx[*(uint *)(cp->ai + 0x1c)]);
			DAT_LEAD__000ecc04 = (*(uint *)(cp->ai + 0x1c) & 3) << 10;
		}
		else {
			if (cr_00 == 0) {
				DAT_LEAD__000ecc04 = (uint)(ushort)Driver2StraightsPtr[DAT_LEAD__000ecc60].angle & 0xfff;
				if ((((cp->hd).direction - DAT_LEAD__000ecc04) + 0x400 & 0x800) != 0) {
					DAT_LEAD__000ecc04 = DAT_LEAD__000ecc04 ^ 0x800;
				}
			}
			else {
				if (cr_00 == 0x4000) {
					DAT_LEAD__000eccac =
						(cp->hd).where.t[0] - Driver2CurvesPtr[DAT_LEAD__000ecc60 - 0x4000].Midx;
					DAT_LEAD__000eccb0 =
						(cp->hd).where.t[2] - Driver2CurvesPtr[DAT_LEAD__000ecc60 - 0x4000].Midz;
					iVar8 = ratan2(DAT_LEAD__000eccac, DAT_LEAD__000eccb0);
					if ((iVar8 - (cp->hd).direction & 0x800U) == 0) {
						DAT_LEAD__000ecc04 = iVar8 - 0x400U & 0xfff;
					}
					else {
						DAT_LEAD__000ecc04 = iVar8 + 0x400U & 0xfff;
					}
				}
			}
		}
		DAT_LEAD__000ecca8 = ((DAT_LEAD__000ecc04 - (cp->hd).direction) + 0x800 & 0xfff) - 0x800;
		if ((cr & 0xffffe000) == 0) {
			pDVar6 = Driver2StraightsPtr + cr;
			iVar5 = (int)rcossin_tbl[(DAT_LEAD__000ecc04 & 0xfff) * 2 + 1];
			DAT_LEAD__000eccc0 = pDVar6->Midx - (cp->hd).where.t[0];
			iVar8 = (int)rcossin_tbl[(DAT_LEAD__000ecc04 & 0xfff) * 2];
			DAT_LEAD__000eccc4 = pDVar6->Midz - (cp->hd).where.t[2];
			DAT_LEAD__000eccbc = -(DAT_LEAD__000eccc0 * iVar8 + DAT_LEAD__000eccc4 * iVar5 + 0x800 >> 0xc)
				;
			*(int *)(cp->ai + 0x48) =
				(iVar5 * DAT_LEAD__000eccc0 - iVar8 * DAT_LEAD__000eccc4) + 0x800 >> 0xc;
			*(uint *)(cp->ai + 0x44) = ((uint)(byte)pDVar6->NumLanes & 0xf) << 9;
			DAT_LEAD__000eccb4 = iVar8 * DAT_LEAD__000eccbc + 0x800 >> 0xc;
			DAT_LEAD__000ecc70 = pDVar6->Midx + DAT_LEAD__000eccb4;
			DAT_LEAD__000ecc74 = (cp->hd).where.t[1];
			DAT_LEAD__000eccb8 = iVar5 * DAT_LEAD__000eccbc + 0x800 >> 0xc;
			DAT_LEAD__000ecc78 = pDVar6->Midz + DAT_LEAD__000eccb8;
		}
		else {
			if ((cr & 0xffffe000) == 0x4000) {
				pDVar7 = Driver2CurvesPtr + (cr - 0x4000);
				DAT_LEAD__000ecccc = (cp->hd).where.t[0] - pDVar7->Midx;
				DAT_LEAD__000eccd0 = (cp->hd).where.t[2] - pDVar7->Midz;
				iVar8 = (uint)(byte)pDVar7->inside * 0x400 + ((uint)(byte)pDVar7->NumLanes & 0xf) * 0x200;
				DAT_LEAD__000eccc8 = ratan2(DAT_LEAD__000ecccc, DAT_LEAD__000eccd0);
				if ((DAT_LEAD__000eccc8 - DAT_LEAD__000ecc04 & 0x800) == 0) {
					cr_00 = (uint)(ushort)pDVar7->end & 0xfff;
					DAT_LEAD__000eccd4 = rcossin_tbl[cr_00 * 2] * iVar8 + 0x800 >> 0xc;
					DAT_LEAD__000eccd8 = rcossin_tbl[cr_00 * 2 + 1] * iVar8 + 0x800 >> 0xc;
					uVar3 = hypot(DAT_LEAD__000ecccc, DAT_LEAD__000eccd0);
					iVar8 = DAT_LEAD__000eccc8;
					*(ulong *)(cp->ai + 0x48) = uVar3;
					*(ulong *)(cp->ai + 0x4c) = uVar3;
					*(undefined4 *)(cp->ai + 0x54) = 0xffffffff;
					*(int *)(cp->ai + 0x50) = iVar8;
					*(uint *)(cp->ai + 0x48) =
						((uint)(byte)pDVar7->inside * 0x400 + ((uint)(byte)pDVar7->NumLanes & 0xf) * 0x200) -
						uVar3;
				}
				else {
					cr_00 = (uint)(ushort)pDVar7->start & 0xfff;
					DAT_LEAD__000eccd4 = rcossin_tbl[cr_00 * 2] * iVar8 + 0x800 >> 0xc;
					DAT_LEAD__000eccd8 = rcossin_tbl[cr_00 * 2 + 1] * iVar8 + 0x800 >> 0xc;
					uVar3 = hypot(DAT_LEAD__000ecccc, DAT_LEAD__000eccd0);
					iVar8 = DAT_LEAD__000eccc8;
					*(ulong *)(cp->ai + 0x48) = uVar3;
					*(ulong *)(cp->ai + 0x4c) = uVar3;
					*(undefined4 *)(cp->ai + 0x54) = 1;
					*(int *)(cp->ai + 0x50) = iVar8;
					*(ulong *)(cp->ai + 0x48) =
						uVar3 - ((uint)(byte)pDVar7->inside * 0x400 +
						((uint)(byte)pDVar7->NumLanes & 0xf) * 0x200);
				}
				*(uint *)(cp->ai + 0x44) = ((uint)(byte)pDVar7->NumLanes & 0xf) << 9;
				DAT_LEAD__000ecce0 = DAT_LEAD__000eccd4 - (cp->hd).where.t[0];
				DAT_LEAD__000ecce4 = DAT_LEAD__000eccd8 - (cp->hd).where.t[2];
				DAT_LEAD__000eccdc =
					-(DAT_LEAD__000ecce0 * rcossin_tbl[(DAT_LEAD__000ecc04 & 0xfff) * 2] +
						DAT_LEAD__000ecce4 * rcossin_tbl[(DAT_LEAD__000ecc04 & 0xfff) * 2 + 1] + 0x800 >> 0xc
						);
				DAT_LEAD__000ecccc =
					rcossin_tbl[(DAT_LEAD__000ecc04 & 0xfff) * 2] * DAT_LEAD__000eccdc + 0x800 >> 0xc;
				DAT_LEAD__000ecc70 = DAT_LEAD__000eccd4 + DAT_LEAD__000ecccc;
				DAT_LEAD__000ecc74 = (cp->hd).where.t[1];
				DAT_LEAD__000eccd0 =
					rcossin_tbl[(DAT_LEAD__000ecc04 & 0xfff) * 2 + 1] * DAT_LEAD__000eccdc + 0x800 >> 0xc;
				DAT_LEAD__000ecc78 = DAT_LEAD__000eccd8 + DAT_LEAD__000eccd0;
			}
			else {
				DAT_LEAD__000ecc70 = (cp->hd).where.t[0];
				DAT_LEAD__000ecc74 = (cp->hd).where.t[1];
				DAT_LEAD__000ecc78 = (cp->hd).where.t[2];
			}
		}
		iVar5 = DAT_LEAD__000ecca8;
		iVar8 = DAT_LEAD__000ecca8;
		if (DAT_LEAD__000ecca8 < 0) {
			iVar8 = -DAT_LEAD__000ecca8;
		}
		*(uint *)(cp->ai + 0xc) = cr;
		if (iVar8 < 0x200) {
			DAT_LEAD__000ecc70 = (cp->hd).where.t[0];
			DAT_LEAD__000ecc74 = (cp->hd).where.t[1];
			DAT_LEAD__000ecc78 = (cp->hd).where.t[2];
			UpdateRoadPosition(cp, (VECTOR *)&DAT_LEAD__000ecc70, 0);
		}
		else {
			if (iVar5 < 1) {
				UpdateRoadPosition(cp, (VECTOR *)&DAT_LEAD__000ecc70, 2);
			}
			else {
				UpdateRoadPosition(cp, (VECTOR *)&DAT_LEAD__000ecc70, 3);
			}
		}
		SetTarget(cp, cr, DAT_LEAD__000ecc04, &DAT_LEAD__000ecc60);
	}
	else {
		DAT_LEAD__000ecc70 = (cp->hd).where.t[0];
		DAT_LEAD__000ecc74 = (cp->hd).where.t[1];
		DAT_LEAD__000ecc78 = (cp->hd).where.t[2];
		iVar8 = *(int *)(cp->ai + 0x48);
		if (iVar8 < 0) {
			iVar8 = -iVar8;
		}
		if (((*(int *)(cp->ai + 0x44) + 0x800 < iVar8) && (((cp->hd).wheel[1].surface & 7) != 3)) &&
			(((cp->hd).wheel[3].surface & 7) != 3)) {
			*(undefined4 *)(cp->ai + 0x40) = 1;
			*(undefined4 *)(cp->ai + 0x14) = 0xffffffff;
			UpdateRoadPosition(cp, (VECTOR *)&DAT_LEAD__000ecc70, 4);
			DAT_LEAD__000ecc04 = (cp->hd).direction;
			SetTarget(cp, cr_00, DAT_LEAD__000ecc04, &DAT_LEAD__000ecc60);
		}
		else {
			*(uint *)(cp->ai + 0xc) = cr_00;
			*(uint *)(cp->ai + 0x10) = cr_00;
			*(undefined4 *)(cp->ai + 0x60) = *(undefined4 *)(cp->ai + 0x5c);
			if ((((cr_00 & 0xffffe000) == 0x4000) && ((int)(cr_00 & 0x1fff) < NumDriver2Curves)) &&
				(-1 < (int)cr_00)) {
				UpdateRoadPosition(cp, (VECTOR *)&DAT_LEAD__000ecc70, 1);
			}
			else {
				UpdateRoadPosition(cp, (VECTOR *)&DAT_LEAD__000ecc70, 0);
			}
			DAT_LEAD__000ecc04 = (cp->hd).direction;
			SetTarget(cp, cr_00, DAT_LEAD__000ecc04, &DAT_LEAD__000ecc60);
			if ((((DAT_LEAD__000ecc60 & 0xffffe000) == 0x2000) &&
				((int)(DAT_LEAD__000ecc60 & 0x1fff) < NumDriver2Junctions)) &&
				(-1 < (int)DAT_LEAD__000ecc60)) {
				if (DAT_LEAD__000ecc60 != *(uint *)(cp->ai + 0x14)) {
					SelectExit(cp, Driver2JunctionsPtr + (DAT_LEAD__000ecc60 - 0x2000));
					*(uint *)(cp->ai + 0x14) = DAT_LEAD__000ecc60;
				}
			}
			else {
				*(undefined4 *)(cp->ai + 0x14) = 0xffffffff;
			}
		}
	}
	return;*/
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

	cp->ai.l.targetX = curve->Midx + (iVar8 * rcossin_tbl[(uVar4 & 0xfff) * 2] + 0x800 >> 0xc);
	cp->ai.l.targetZ = curve->Midz + (iVar8 * rcossin_tbl[(uVar4 & 0xfff) * 2 + 1] + 0x800 >> 0xc);

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
	if (x < 0x8000) {
		uVar3 = SquareRoot0(x * x + iVar2 * iVar2);
	}
	else {
		if (iVar4 == 0) {
			trap(7);
		}
		iVar2 = SquareRoot0((iVar2 / iVar4) * (iVar2 / iVar4) + 0x1000800);
		uVar3 = x + iVar4 * (iVar2 + -0x1000);
	}
	return uVar3;
}





