#include "THISDUST.H"
#include "CIV_AI.H"
#include "LIBMATH.H"

#include "SYSTEM.H"
#include "HANDLING.H"
#include "DR2ROADS.H"
#include "COSMETIC.H"
#include "MISSION.H"
#include "COP_AI.H"
#include "DENTING.H"
#include "CARS.H"
#include "CAMERA.H"
#include "CUTSCENE.H"
#include "REPLAYS.H"
#include "CONVERT.H"
#include "SPOOL.H"
#include "PLAYERS.H"
#include "COP_AI.H"

char speedLimits[3] = { 56, 97, 138 };

CIV_AI_234fake civPingTest = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char modelRandomList[] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 1, 0, 4 };
unsigned char reservedSlots[20];

int distFurthestCivCarSq = 0;
char furthestCivID = 0;
char makeLimoPullOver = 0;
int frameStart = 0;

char limoId = 0;	// Seems to be unused
char playerNum = 0;
char PingOutCivsOnly = 0;
char cookieCount = 0;
int useStoredPings = 1;
int roadSeg = 0;
int testNumPingedOut = 0;
int currentAngle = 0;
int closeEncounter = 3;

// decompiled code
// original method signature: 
// int /*$ra*/ InitCar(struct _CAR_DATA *cp /*$s0*/, int direction /*$s6*/, long (*startPos)[4] /*$s2*/, unsigned char control /*$s4*/, int model /*stack 16*/, int palette /*stack 20*/, char *extraData /*stack 24*/)
 // line 717, offset 0x00023de8
	/* begin block 1 */
		// Start line: 718
		// Start offset: 0x00023DE8
		// Variables:
	// 		struct VECTOR tmpStart; // stack offset -48
	/* end block 1 */
	// End offset: 0x00024028
	// End Line: 786

	/* begin block 2 */
		// Start line: 1434
	/* end block 2 */
	// End Line: 1435

// [D] [A]
int InitCar(_CAR_DATA *cp, int direction, long(*startPos)[4], unsigned char control, int model, int palette, char *extraData)
{
	VECTOR local_30;

	ClearMem((char *)cp, 0x29c);

	cp->wasOnGround = 1;

	cp->id = CAR_INDEX(cp);

	if (startPos == NULL)
		return 0;

	(cp->ap).model = (char)model;
	cp->lowDetail = -1;
	(cp->ap).qy = 0;
	(cp->ap).qw = 0;
	(cp->ap).carCos = car_cosmetics + (model & 0xff);
	local_30.vx = (*startPos)[0];
	local_30.vy = (*startPos)[1];
	local_30.vz = (*startPos)[2];
	local_30.vy = MapHeight(&local_30);
	local_30.vy = local_30.vy - ((cp->ap).carCos)->wheelDisp[0].vy;

	if (control == 0) 
		return 1;

	InitCarPhysics(cp, (long(*)[4])&local_30, direction);
	(cp->ap).palette = (char)palette;

	switch (control) 
	{
	case 1:
	case 7:
		if (extraData == NULL) {
			cp->ai.c.currentRoad = 0;
		}
		else {
			cp->ai.c.currentRoad = *extraData;
		}

		player[cp->id].worldCentreCarId = cp->id;
		cp->hndType = 0;
		break;
	case 2:
		cp->hndType = 1;
		cp->controlFlags = extraData[0x11];
		InitCivState(cp, extraData);
		if (extraData == NULL)
		{
			cp->ap.palette = 0;
		}
		else 
		{
			cp->ap.palette = extraData[0x10];
		}
		break;
	case 3:
		InitCopState(cp, extraData);
		cp->ap.palette = 0;
		numCopCars++;
		break;
	case 4:
		UNIMPLEMENTED();
		// [A]
		//InitLead(cp);
		//leadCarId = cp->id;
		cp->hndType = 5;
		cp->controlType = control;
		goto LAB_00023fe4;
	}

	cp->controlType = control;

LAB_00023fe4:
	CreateDentableCar(cp);
	DentCar(cp);
}



// decompiled code
// original method signature: 
// struct _CAR_DATA * /*$ra*/ FindClosestCar(int x /*$t4*/, int y /*$a1*/, int z /*$a2*/, int *distToCarSq /*$a3*/)
 // line 891, offset 0x0002d11c
	/* begin block 1 */
		// Start line: 892
		// Start offset: 0x0002D11C
		// Variables:
	// 		struct _CAR_DATA *retCar; // $t2
	// 		struct _CAR_DATA *lcp; // $t0
	// 		unsigned int retDistSq; // $t1
	// 		int distSq; // $v0
	// 		int dx; // $a0
	// 		int dz; // $v1
	/* end block 1 */
	// End offset: 0x0002D220
	// End Line: 915

	/* begin block 2 */
		// Start line: 1782
	/* end block 2 */
	// End Line: 1783

	/* begin block 3 */
		// Start line: 6497
	/* end block 3 */
	// End Line: 6498

// [D]
_CAR_DATA * FindClosestCar(int x, int y, int z, int *distToCarSq)
{
	int iVar1;
	uint uVar2;
	int iVar3;
	int iVar4;
	_CAR_DATA *lcp;
	uint retDistSq;
	_CAR_DATA *retCar;

	retCar = NULL;
	retDistSq = 0x7fffffff; // INT_MAX
	lcp = car_data;

	do {
		if (lcp->controlType != 0)
		{
			iVar3 = lcp->hd.where.t[1];

			iVar1 = y - iVar3;
			if (iVar1 < 0) 
				iVar1 = iVar3 - y;

			if (iVar1 < 800) 
			{
				iVar3 = x - lcp->hd.where.t[0];
				iVar1 = iVar3;

				if (iVar3 < 0)
					iVar1 = -iVar3;

				if (iVar1 < 0x1000) 
				{
					iVar4 = z - lcp->hd.where.t[2];
					iVar1 = iVar4;
					if (iVar4 < 0) {
						iVar1 = -iVar4;
					}
					if ((iVar1 < 0x1000) && (uVar2 = iVar3 * iVar3 + iVar4 * iVar4, uVar2 < retDistSq)) 
					{
						retDistSq = uVar2;
						retCar = lcp;
					}
				}
			}
		}
		lcp++;
	} while (lcp <= &car_data[20]);

	if (distToCarSq) 
		*distToCarSq = retDistSq;

	return retCar;
}



// decompiled code
// original method signature: 
// int /*$ra*/ NotTravellingAlongCurve(int x /*$a0*/, int z /*$a1*/, int dir /*$s0*/, struct DRIVER2_CURVE *cv /*$a3*/)
 // line 918, offset 0x0002d24c
	/* begin block 1 */
		// Start line: 919
		// Start offset: 0x0002D24C
	/* end block 1 */
	// End offset: 0x0002D298
	// End Line: 927

	/* begin block 2 */
		// Start line: 1803
	/* end block 2 */
	// End Line: 1804

	/* begin block 3 */
		// Start line: 7767
	/* end block 3 */
	// End Line: 7768

	/* begin block 4 */
		// Start line: 7769
	/* end block 4 */
	// End Line: 7770

int NotTravellingAlongCurve(int x, int z, int dir, DRIVER2_CURVE *cv)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	iVar1 = ratan2(x - cv->Midx, z - cv->Midz);
	return (uint)((int)(((dir - iVar1) + 0x800U & 0xfff) - 0x800) < 1) << 0xb;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivCarFX(struct _CAR_DATA *cp /*$s0*/)
 // line 930, offset 0x0002d084
	/* begin block 1 */
		// Start line: 1860
	/* end block 1 */
	// End Line: 1861

void CivCarFX(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	if (cp->ai[0xf9] != 3) {
		if (*(int *)(cp->ai + 0x14) != -1) {
			AddIndicatorLight(cp, (uint)cp->ai[0xf]);
		}
		if ((*(int *)(cp->ai + 0x18) != 0) && (*(int *)(cp->ai + 0x14) == -1)) {
			AddIndicatorLight(cp, (uint)cp->ai[0xe]);
		}
	}
	if (cp->ai[0x10] != 0) {
		AddBrakeLight(cp);
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetNextRoadInfo(struct _CAR_DATA *cp /*$s7*/, int randomExit /*$a1*/, int *turnAngle /*stack 8*/, int *startDist /*stack 12*/, struct CIV_ROUTE_ENTRY *oldNode /*stack 16*/)
 // line 981, offset 0x00024028
	/* begin block 1 */
		// Start line: 982
		// Start offset: 0x00024028
		// Variables:
	// 		int oldOppDir; // $s4
	// 		int i; // $a1
	// 		int j; // $s6
	// 		int newRoad; // $s3
	// 		int numExits; // stack offset -88
	// 		int currentRoadExit; // $t6
	// 		int newNumLanes; // $a3
	// 		int newDir; // stack offset -84
	// 		int oppDir; // $s0
	// 		struct DRIVER2_JUNCTION *jn; // $t5
	// 		struct DRIVER2_CURVE *cv; // $s1
	// 		struct DRIVER2_STRAIGHT *st; // $s5
	// 		struct DRIVER2_STRAIGHT *tmpSt; // $a2
	// 		struct DRIVER2_CURVE *tmpCv; // $s1
	// 		short *jnExit; // $a2
	// 		int newLane; // $s2
	// 		char leftLane; // stack offset -80
	// 		char rightLane; // stack offset -76

		/* begin block 1.1 */
			// Start line: 1042
			// Start offset: 0x00024734
			// Variables:
		// 		char relExitId; // $fp
		// 		static char validExitRelIdx[4][3][2]; // offset 0x0
		// 		int addRoad; // $t9

			/* begin block 1.1.1 */
				// Start line: 982
				// Start offset: 0x00024804
				// Variables:
			// 		int currentRoadExit; // $t6
			// 		int newRoadExit; // $fp

				/* begin block 1.1.1.1 */
					// Start line: 982
					// Start offset: 0x00024804
					// Variables:
				// 		int exitMod; // $a0
				// 		int ret; // $a1
				/* end block 1.1.1.1 */
				// End offset: 0x00024870
				// End Line: 982
			/* end block 1.1.1 */
			// End offset: 0x00024870
			// End Line: 982

			/* begin block 1.1.2 */
				// Start line: 1091
				// Start offset: 0x00024C18
				// Variables:
			// 		int x; // $v1
			// 		int z; // $v0
			// 		int dir; // stack offset -84
			// 		struct DRIVER2_CURVE *cv; // $s1

				/* begin block 1.1.2.1 */
					// Start line: 1091
					// Start offset: 0x00024C18
				/* end block 1.1.2.1 */
				// End offset: 0x00024C18
				// End Line: 1091
			/* end block 1.1.2 */
			// End offset: 0x00024C18
			// End Line: 1091

			/* begin block 1.1.3 */
				// Start line: 1112
				// Start offset: 0x00025048
				// Variables:
			// 		int exitId; // $a1

				/* begin block 1.1.3.1 */
					// Start line: 1116
					// Start offset: 0x0002506C
					// Variables:
				// 		char lane; // $v0
				/* end block 1.1.3.1 */
				// End offset: 0x000250C4
				// End Line: 1132

				/* begin block 1.1.3.2 */
					// Start line: 982
					// Start offset: 0x00025180
					// Variables:
				// 		int currentRoadExit; // $t6

					/* begin block 1.1.3.2.1 */
						// Start line: 982
						// Start offset: 0x00025180
						// Variables:
					// 		int exitMod; // $a1
					// 		int ret; // $a2
					/* end block 1.1.3.2.1 */
					// End offset: 0x000251E0
					// End Line: 982
				/* end block 1.1.3.2 */
				// End offset: 0x000251E0
				// End Line: 982
			/* end block 1.1.3 */
			// End offset: 0x000251EC
			// End Line: 1147

			/* begin block 1.1.4 */
				// Start line: 982
				// Start offset: 0x000251EC
				// Variables:
			// 		struct DRIVER2_JUNCTION *jn; // $t5
			// 		int currentExit; // $a2
			// 		int turnAngle; // $t1
			// 		struct _CAR_DATA *cp; // $s7
			// 		struct CIV_ROUTE_ENTRY *oldNode; // $t7

				/* begin block 1.1.4.1 */
					// Start line: 982
					// Start offset: 0x000251EC
					// Variables:
				// 		unsigned short jnFlags; // $a0
				// 		int i; // $a1
				// 		int exitId; // $a3
				/* end block 1.1.4.1 */
				// End offset: 0x000252BC
				// End Line: 982
			/* end block 1.1.4 */
			// End offset: 0x000252BC
			// End Line: 982

			/* begin block 1.1.5 */
				// Start line: 1152
				// Start offset: 0x000252BC

				/* begin block 1.1.5.1 */
					// Start line: 1173
					// Start offset: 0x00025774
					// Variables:
				// 		int x; // $v1
				// 		int z; // $v0
				// 		int dir; // stack offset -84
				// 		struct DRIVER2_CURVE *cv; // $s1

					/* begin block 1.1.5.1.1 */
						// Start line: 1173
						// Start offset: 0x00025774
					/* end block 1.1.5.1.1 */
					// End offset: 0x00025774
					// End Line: 1173
				/* end block 1.1.5.1 */
				// End offset: 0x00025774
				// End Line: 1173
			/* end block 1.1.5 */
			// End offset: 0x00025BC8
			// End Line: 1184
		/* end block 1.1 */
		// End offset: 0x00025BC8
		// End Line: 1184

		/* begin block 1.2 */
			// Start line: 1192
			// Start offset: 0x00025BD0
			// Variables:
		// 		int i; // $a1
		// 		int dx; // $v1
		// 		int dz; // $a0
		// 		int numLanes; // $fp
		// 		int *pNewLane; // $s3
		// 		int laneFromLeft; // $a3
		// 		int laneFromRight; // $v1

			/* begin block 1.2.1 */
				// Start line: 1255
				// Start offset: 0x00025FE4
				// Variables:
			// 		int preferredNewLane; // $t1
			/* end block 1.2.1 */
			// End offset: 0x00026314
			// End Line: 1283

			/* begin block 1.2.2 */
				// Start line: 1286
				// Start offset: 0x00026348
				// Variables:
			// 		int preferredNewLane; // $s4

				/* begin block 1.2.2.1 */
					// Start line: 1286
					// Start offset: 0x00026348
					// Variables:
				// 		int x; // $v1
				// 		int z; // $v0
				// 		struct DRIVER2_CURVE *cv; // $s1

					/* begin block 1.2.2.1.1 */
						// Start line: 1286
						// Start offset: 0x00026348
					/* end block 1.2.2.1.1 */
					// End offset: 0x00026348
					// End Line: 1286
				/* end block 1.2.2.1 */
				// End offset: 0x00026348
				// End Line: 1286
			/* end block 1.2.2 */
			// End offset: 0x0002669C
			// End Line: 1313
		/* end block 1.2 */
		// End offset: 0x000267A4
		// End Line: 1326
	/* end block 1 */
	// End offset: 0x00026964
	// End Line: 1350

	/* begin block 2 */
		// Start line: 1783
	/* end block 2 */
	// End Line: 1784

	/* begin block 3 */
		// Start line: 1979
	/* end block 3 */
	// End Line: 1980

/* WARNING: Type propagation algorithm not settling */

int GetNextRoadInfo(_CAR_DATA *cp, int randomExit, int *turnAngle, int *startDist, CIV_ROUTE_ENTRY *oldNode)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	short sVar2;
	ushort uVar3;
	bool bVar4;
	bool bVar5;
	byte bVar6;
	uint uVar7;
	uint uVar8;
	long lVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	DRIVER2_JUNCTION *pDVar15;
	uint *puVar16;
	int iVar17;
	uint uVar18;
	int iVar19;
	uint uVar20;
	ushort *puVar21;
	DRIVER2_STRAIGHT *pDVar22;
	byte *pbVar23;
	DRIVER2_CURVE *pDVar24;
	uint uVar25;
	uint uVar26;
	uint uVar27;
	int *piVar28;
	uint uVar29;
	DRIVER2_STRAIGHT *pDVar30;
	int unaff_s8;
	int local_58;
	int local_54;
	uint local_50;
	uint local_4c;

	currentRoadId = *(int *)cp->ai;
	pDVar30 = (DRIVER2_STRAIGHT *)0x0;
	if ((((currentRoadId & 0xffffe000U) == 0) &&
		((int)(currentRoadId & 0x1fffU) < NumDriver2Straights)) && (-1 < currentRoadId)) {
		pDVar30 = Driver2StraightsPtr + currentRoadId;
		if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) == 0xff010000) {
			uVar7 = (uint)cp->ai[0xfb];
		}
		else {
			uVar7 = (int)(uint)(byte)pDVar30->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
		}
		uVar7 = uVar7 & 1;
		uVar29 = uVar7 << 0xb;
		if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) == 0xff010000) {
			uVar8 = (uint)cp->ai[0xfb];
		}
		else {
			uVar8 = (int)(uint)(byte)pDVar30->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
		}
		tmpNewRoad = (int)pDVar30->ConnectIdx[(uVar8 & 1) * 2];
		if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) == 0xff010000) {
			uVar8 = (uint)cp->ai[0xfb];
		}
		else {
			uVar8 = (int)(uint)(byte)pDVar30->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
		}
		iVar17 = 2;
		if ((uVar8 & 1) != 0) {
			iVar17 = 6;
		}
		INT_000aaadc = (int)*(short *)((int)pDVar30->ConnectIdx + iVar17);
		uVar25 = ((uint)(byte)pDVar30->NumLanes & 0xf) * 2;
		uVar8 = uVar25;
		do {
			do {
				uVar8 = uVar8 - 1;
				uVar18 = uVar25;
				if ((int)uVar8 < 0) goto LAB_00024288;
			} while (((((int)(uint)(byte)pDVar30->AILanes >> ((int)uVar8 / 2 & 0x1fU) & 1U) == 0) ||
				((uVar8 == 0 && ((pDVar30->NumLanes & 0x40U) != 0)))) ||
				((((uint)(byte)pDVar30->NumLanes & 0xffffff0f) * 2 - 1 == uVar8 &&
				((pDVar30->NumLanes & 0x80U) != 0))));
			uVar18 = uVar8;
			if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
				uVar18 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar8 / 2 & 0x1fU);
			}
			test42 = (uVar18 ^ 1) & 1;
			uVar18 = uVar8;
		} while (uVar7 == 0);
	LAB_00024288:
		if (uVar7 == 0) {
			local_50 = uVar18 & 0xff;
		}
		else {
			local_4c = uVar18 & 0xff;
		}
		uVar25 = (uint)(byte)pDVar30->NumLanes;
		uVar26 = (uVar25 & 0xf) << 1;
		uVar18 = (uint)((byte)pDVar30->NumLanes >> 6) & 1;
		uVar8 = uVar26;
		if (uVar18 < uVar26) {
			do {
				if (((((int)(uint)(byte)pDVar30->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) != 0) &&
					((uVar18 != 0 || ((pDVar30->NumLanes & 0x40U) == 0)))) &&
					(((uVar25 & 0xffffff0f) * 2 - 1 != uVar18 || ((uVar25 & 0x80) == 0)))) {
					uVar8 = uVar18;
					if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
						uVar8 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar18 / 2 & 0x1fU);
					}
					test555 = (uVar8 ^ 1) & 1;
					uVar8 = uVar18;
					if (test555 == 0) {
						if (uVar7 != 0) break;
					}
					else {
						if (uVar7 == 0) break;
					}
				}
				uVar25 = (uint)(byte)pDVar30->NumLanes;
				uVar18 = uVar18 + 1;
				uVar8 = uVar26;
			} while ((int)uVar18 < (int)((uVar25 & 0xffffff0f) << 1));
		}
		if (uVar7 != 0) goto LAB_000246dc;
	LAB_000246ec:
		local_4c = uVar8 & 0xff;
	}
	else {
		if ((currentRoadId & 0xffffe000U) != 0x4000) {
			return 0;
		}
		if (NumDriver2Curves <= (int)(currentRoadId & 0x1fffU)) {
			return 0;
		}
		if (currentRoadId < 0) {
			return 0;
		}
		pDVar24 = Driver2CurvesPtr + (currentRoadId - 0x4000);
		if (*(short *)&pDVar24->NumLanes == -0xff) {
			uVar7 = (uint)cp->ai[0xfb];
		}
		else {
			uVar7 = (int)(uint)(byte)pDVar24->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
		}
		uVar7 = uVar7 & 1;
		uVar29 = uVar7 << 0xb;
		if (*(short *)&pDVar24->NumLanes == -0xff) {
			uVar8 = (uint)cp->ai[0xfb];
		}
		else {
			uVar8 = (int)(uint)(byte)pDVar24->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
		}
		tmpNewRoad = (int)pDVar24->ConnectIdx[(uVar8 & 1) * 2];
		if (*(short *)&pDVar24->NumLanes == -0xff) {
			uVar8 = (uint)cp->ai[0xfb];
		}
		else {
			uVar8 = (int)(uint)(byte)pDVar24->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
		}
		iVar17 = 2;
		if ((uVar8 & 1) != 0) {
			iVar17 = 6;
		}
		INT_000aaadc = (int)*(short *)((int)pDVar24->ConnectIdx + iVar17);
		uVar25 = ((uint)(byte)pDVar24->NumLanes & 0xf) * 2;
		uVar8 = uVar25;
		do {
			do {
				uVar8 = uVar8 - 1;
				uVar18 = uVar25;
				if ((int)uVar8 < 0) goto LAB_000245c0;
			} while (((((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar8 / 2 & 0x1fU) & 1U) == 0) ||
				((uVar8 == 0 && ((pDVar24->NumLanes & 0x40U) != 0)))) ||
				((((uint)(byte)pDVar24->NumLanes & 0xffffff0f) * 2 - 1 == uVar8 &&
				((pDVar24->NumLanes & 0x80U) != 0))));
			uVar18 = uVar8;
			if (*(short *)&pDVar24->NumLanes != -0xff) {
				uVar18 = (int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar8 / 2 & 0x1fU);
			}
			test42 = (uVar18 ^ 1) & 1;
			uVar18 = uVar8;
		} while (uVar7 == 0);
	LAB_000245c0:
		if (uVar7 == 0) {
			local_50 = uVar18 & 0xff;
		}
		else {
			local_4c = uVar18 & 0xff;
		}
		uVar25 = (uint)(byte)pDVar24->NumLanes;
		uVar26 = (uVar25 & 0xf) << 1;
		uVar18 = (uint)((byte)pDVar24->NumLanes >> 6) & 1;
		uVar8 = uVar26;
		if (uVar18 < uVar26) {
			do {
				if (((((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) != 0) &&
					((uVar18 != 0 || ((pDVar24->NumLanes & 0x40U) == 0)))) &&
					(((uVar25 & 0xffffff0f) * 2 - 1 != uVar18 || ((uVar25 & 0x80) == 0)))) {
					uVar8 = uVar18;
					if (*(short *)&pDVar24->NumLanes != -0xff) {
						uVar8 = (int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar18 / 2 & 0x1fU);
					}
					test555 = (uVar8 ^ 1) & 1;
					uVar8 = uVar18;
					if (test555 == 0) {
						if (uVar7 != 0) break;
					}
					else {
						if (uVar7 == 0) break;
					}
				}
				uVar25 = (uint)(byte)pDVar24->NumLanes;
				uVar18 = uVar18 + 1;
				uVar8 = uVar26;
			} while ((int)uVar18 < (int)((uVar25 & 0xffffff0f) << 1));
		}
		if (uVar7 == 0) goto LAB_000246ec;
	LAB_000246dc:
		local_50 = uVar8 & 0xff;
	}
	iVar17 = tmpNewRoad;
	uVar7 = 0xffffffff;
	if ((((tmpNewRoad & 0xffffe000U) != 0x2000) ||
		(NumDriver2Junctions <= (int)(tmpNewRoad & 0x1fffU))) || (tmpNewRoad < 0)) {
		iVar17 = 0;
		if (turnAngle == (int *)0x0) goto LAB_00026928;
		*turnAngle = 0;
		newExit = -1;
		do {
			piVar28 = tmpNewLane + iVar17;
			uVar7 = (&tmpNewRoad)[iVar17];
			if (uVar7 == 0xffffffff) {
				(&laneFit)[iVar17] = 0x29a;
			}
			else {
				if ((((uVar7 & 0xffffe000) == 0) && ((int)(uVar7 & 0x1fff) < NumDriver2Straights)) &&
					(-1 < (int)uVar7)) {
					pDVar30 = Driver2StraightsPtr + uVar7;
					tmpStr2[iVar17] = pDVar30;
					uVar7 = (uint)(ushort)pDVar30->angle & 0xfff;
					uVar29 = (uint)(byte)pDVar30->NumLanes & 0xffffff0f;
					test555 = (oldNode->x - pDVar30->Midx) * (int)rcossin_tbl[uVar7 * 2 + 1] -
						(oldNode->z - pDVar30->Midz) * (int)rcossin_tbl[uVar7 * 2];
					test42 = uVar29 - ((test555 + 0x800 >> 0xc) + 0x200 >> 9);
					*piVar28 = test42;
					unaff_s8 = uVar29 * 2;
					uVar29 = ((uint)(byte)pDVar30->NumLanes & 0xffffff0f) * 2;
					uVar7 = uVar29;
					do {
						do {
							uVar7 = uVar7 - 1;
							uVar8 = uVar29;
							if ((int)uVar7 < 0) goto LAB_00025e00;
						} while (((((int)(uint)(byte)pDVar30->AILanes >> ((int)uVar7 / 2 & 0x1fU) & 1U) == 0) ||
							((uVar7 == 0 && ((pDVar30->NumLanes & 0x40U) != 0)))) ||
							((((uint)(byte)pDVar30->NumLanes & 0xffffff0f) * 2 - 1 == uVar7 &&
							((pDVar30->NumLanes & 0x80U) != 0))));
						uVar8 = uVar7;
						if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
							uVar8 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar7 / 2 & 0x1fU);
						}
						test42 = (uVar8 ^ 1) & 1;
						uVar8 = uVar7;
					} while ((((int)oldNode->dir - (int)pDVar30->angle) + 0x400U & 0x800) == 0);
				LAB_00025e00:
					if ((uVar8 == 0) || (unaff_s8 <= (int)uVar8)) {
						(&laneFit)[iVar17] = 0x29a;
						goto LAB_00025f34;
					}
				}
				else {
					pDVar24 = Driver2CurvesPtr + (&tmpNewRoad)[iVar17] + -0x4000;
					tmpCrv2[iVar17] = pDVar24;
					iVar11 = oldNode->x - pDVar24->Midx;
					iVar14 = oldNode->z - pDVar24->Midz;
					unaff_s8 = ((uint)(byte)pDVar24->NumLanes & 0xffffff0f) * 2;
					iVar11 = SquareRoot0(iVar11 * iVar11 + iVar14 * iVar14);
					if (iVar11 < 0) {
						iVar11 = iVar11 + 0x1ff;
					}
					*piVar28 = (iVar11 >> 9) + (uint)(byte)pDVar24->inside * -2;
				}
				iVar14 = unaff_s8 + -1;
				test123 = *piVar28;
				iVar11 = test123;
				if ((-1 < test123) && (iVar11 = test123 - iVar14, test123 <= iVar14)) {
					iVar11 = 0;
				}
				(&laneFit)[iVar17] = iVar11;
				if (iVar14 <= *piVar28) {
					*piVar28 = iVar14;
				}
				newExit = iVar17;
				if (*piVar28 < 0) {
					*piVar28 = 0;
				}
			}
		LAB_00025f34:
			iVar17 = iVar17 + 1;
		} while (iVar17 < 2);
		if ((newExit == -1) || ((&laneFit)[newExit] == 0x29a)) goto LAB_00026928;
		iVar11 = laneFit;
		if (laneFit < 0) {
			iVar11 = -laneFit;
		}
		iVar14 = INT_000aab2c;
		if (INT_000aab2c < 0) {
			iVar14 = -INT_000aab2c;
		}
		newExit = (uint)(iVar11 < iVar14) ^ 1;
		uVar25 = (&tmpNewRoad)[newExit];
		uVar8 = tmpNewLane[newExit];
		if (cp->ai[0xc] != 7) {
			if ((((uVar25 & 0xffffe000) == 0) && ((int)(uVar25 & 0x1fff) < NumDriver2Straights)) &&
				(-1 < (int)uVar25)) {
				pDVar30 = Driver2StraightsPtr + uVar25;
				uVar7 = ((int)oldNode->dir - (int)pDVar30->angle) + 0x400U & 0x800;
				test123 = local_54;
				if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) == 0xff010000) {
					if ((uVar8 & 1) == 0) goto LAB_00026064;
				LAB_00026074:
					if (uVar7 != 0) goto LAB_00026318;
				}
				else {
					if (((int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar8 / 2 & 0x1fU) & 1U) != 0)
						goto LAB_00026074;
				LAB_00026064:
					if (uVar7 == 0) goto LAB_00026318;
				}
				uVar29 = (uint)(byte)pDVar30->NumLanes;
				uVar26 = (uVar29 & 0xf) * 2;
				uVar18 = uVar26;
				do {
					while (true) {
						do {
							uVar18 = uVar18 - 1;
							if ((int)uVar18 < 0) goto LAB_0002616c;
						} while (((((int)(uint)(byte)pDVar30->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) == 0)
							|| ((uVar18 == 0 && ((pDVar30->NumLanes & 0x40U) != 0)))) ||
							(((uVar29 & 0xffffff0f) * 2 - 1 == uVar18 && ((uVar29 & 0x80) != 0))));
						uVar29 = uVar18;
						if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
							uVar29 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar18 / 2 & 0x1fU);
						}
						test42 = (uVar29 ^ 1) & 1;
						if (test42 == 0) break;
						if (uVar7 == 0) goto LAB_00026154;
						uVar29 = (uint)(byte)pDVar30->NumLanes;
					}
					uVar29 = (uint)(byte)pDVar30->NumLanes;
				} while (uVar7 == 0);
			LAB_00026154:
				uVar29 = (uint)(byte)pDVar30->NumLanes;
				uVar26 = uVar18;
			LAB_0002616c:
				if ((int)uVar26 < 0) {
					uVar26 = 0x2a;
				}
				uVar27 = (uVar29 & 0xf) << 1;
				uVar20 = uVar29 >> 6 & 1;
				uVar18 = uVar27;
				if (uVar20 < uVar27) {
					do {
						uVar18 = uVar20;
						if (((((int)(uint)(byte)pDVar30->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) != 0) &&
							((uVar18 != 0 || ((pDVar30->NumLanes & 0x40U) == 0)))) &&
							(((uVar29 & 0xffffff0f) * 2 - 1 != uVar18 || ((uVar29 & 0x80) == 0)))) {
							uVar29 = uVar18;
							if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
								uVar29 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar18 / 2 & 0x1fU);
							}
							test555 = (uVar29 ^ 1) & 1;
							if (test555 == 0) {
								if (uVar7 != 0) break;
							}
							else {
								if (uVar7 == 0) break;
							}
						}
						uVar29 = (uint)(byte)pDVar30->NumLanes;
						uVar20 = uVar18 + 1;
						uVar18 = uVar27;
					} while ((int)uVar20 < (int)((uVar29 & 0xffffff0f) << 1));
				}
				if (unaff_s8 <= (int)uVar18) {
					uVar18 = 0x2a;
				}
				iVar11 = uVar26 - uVar8;
				if ((uVar26 == 0x2a) && (uVar18 == 0x2a)) goto LAB_00026928;
				if (iVar11 < 0) {
					iVar11 = uVar8 - uVar26;
				}
				if ((int)(uVar18 - uVar8) < 0) {
					if (iVar11 <= (int)(uVar8 - uVar18)) {
						uVar18 = uVar26;
					}
				}
				else {
					if (iVar11 <= (int)(uVar18 - uVar8)) {
						uVar18 = uVar26;
					}
				}
				puVar16 = (uint *)(&laneFit + iVar17);
				*puVar16 = uVar18;
				uVar7 = unaff_s8 - 1;
				if (-1 < (int)uVar18) {
					if ((int)uVar7 < (int)uVar18) {
						*puVar16 = uVar18 - uVar7;
					}
					else {
						*puVar16 = 0;
					}
				}
				uVar8 = uVar18;
				if ((int)uVar7 <= (int)uVar18) {
					uVar8 = uVar7;
				}
				if ((int)uVar8 < 0) {
					uVar8 = 0;
				}
			}
		LAB_00026318:
			if ((((uVar25 & 0xffffe000) == 0x4000) && ((int)(uVar25 & 0x1fff) < NumDriver2Curves)) &&
				(-1 < (int)uVar25)) {
				sVar2 = oldNode->dir;
				pDVar24 = Driver2CurvesPtr + (uVar25 - 0x4000);
				iVar11 = ratan2(oldNode->x - pDVar24->Midx, oldNode->z - pDVar24->Midz);
				bVar5 = (int)(((sVar2 - iVar11) + 0x800U & 0xfff) - 0x800) < 1;
				if (*(short *)&pDVar24->NumLanes == -0xff) {
					if ((uVar8 & 1) == 0) goto LAB_000263fc;
				LAB_0002640c:
					if (bVar5) goto LAB_0002669c;
				}
				else {
					if (((int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar8 / 2 & 0x1fU) & 1U) != 0)
						goto LAB_0002640c;
				LAB_000263fc:
					if (!bVar5) goto LAB_0002669c;
				}
				uVar7 = (uint)(byte)pDVar24->NumLanes;
				uVar18 = (uVar7 & 0xf) * 2;
				uVar29 = uVar18;
				do {
					while (true) {
						do {
							uVar29 = uVar29 - 1;
							if ((int)uVar29 < 0) goto LAB_000264fc;
						} while (((((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar29 / 2 & 0x1fU) & 1U) == 0)
							|| ((uVar29 == 0 && ((pDVar24->NumLanes & 0x40U) != 0)))) ||
							(((uVar7 & 0xffffff0f) * 2 - 1 == uVar29 && ((uVar7 & 0x80) != 0))));
						uVar7 = uVar29;
						if (*(short *)&pDVar24->NumLanes != -0xff) {
							uVar7 = (int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar29 / 2 & 0x1fU);
						}
						test42 = (uVar7 ^ 1) & 1;
						if (test42 == 0) break;
						if (!bVar5) goto LAB_000264e4;
						uVar7 = (uint)(byte)pDVar24->NumLanes;
					}
					uVar7 = (uint)(byte)pDVar24->NumLanes;
				} while (!bVar5);
			LAB_000264e4:
				uVar7 = (uint)(byte)pDVar24->NumLanes;
				uVar18 = uVar29;
			LAB_000264fc:
				if ((int)uVar18 < 0) {
					uVar18 = 0x2a;
				}
				uVar20 = (uVar7 & 0xf) << 1;
				uVar26 = uVar7 >> 6 & 1;
				uVar29 = uVar20;
				if (uVar26 < uVar20) {
					do {
						uVar29 = uVar26;
						if (((((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar29 / 2 & 0x1fU) & 1U) != 0) &&
							((uVar29 != 0 || ((pDVar24->NumLanes & 0x40U) == 0)))) &&
							(((uVar7 & 0xffffff0f) * 2 - 1 != uVar29 || ((uVar7 & 0x80) == 0)))) {
							uVar7 = uVar29;
							if (*(short *)&pDVar24->NumLanes != -0xff) {
								uVar7 = (int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar29 / 2 & 0x1fU);
							}
							test555 = (uVar7 ^ 1) & 1;
							if (test555 == 0) {
								if (bVar5) break;
							}
							else {
								if (!bVar5) break;
							}
						}
						uVar7 = (uint)(byte)pDVar24->NumLanes;
						uVar26 = uVar29 + 1;
						uVar29 = uVar20;
					} while ((int)uVar26 < (int)((uVar7 & 0xffffff0f) << 1));
				}
				if (unaff_s8 <= (int)uVar29) {
					uVar29 = 0x2a;
				}
				iVar11 = uVar18 - uVar8;
				if ((uVar18 == 0x2a) && (uVar29 == 0x2a)) goto LAB_00026928;
				if (iVar11 < 0) {
					iVar11 = uVar8 - uVar18;
				}
				if ((int)(uVar29 - uVar8) < 0) {
					if (iVar11 <= (int)(uVar8 - uVar29)) {
						uVar29 = uVar18;
					}
				}
				else {
					if (iVar11 <= (int)(uVar29 - uVar8)) {
						uVar29 = uVar18;
					}
				}
				puVar16 = (uint *)(&laneFit + iVar17);
				*puVar16 = uVar29;
				uVar7 = unaff_s8 - 1;
				if (-1 < (int)uVar29) {
					if ((int)uVar7 < (int)uVar29) {
						*puVar16 = uVar29 - uVar7;
					}
					else {
						*puVar16 = 0;
					}
				}
				uVar8 = uVar29;
				if ((int)uVar7 <= (int)uVar29) {
					uVar8 = uVar7;
				}
				if ((int)uVar8 < 0) {
					uVar8 = 0;
				}
			}
		LAB_0002669c:
			if ((&laneFit)[newExit] != 0) {
				iVar17 = ((int)oldNode + (-0x1b0 - (int)cp) >> 4) + 1;
				*(int *)(cp->ai + 0x14) = iVar17;
				if (0xc < iVar17) {
					*(undefined4 *)(cp->ai + 0x14) = 0;
				}
				bVar6 = (byte)((uint)(&laneFit)[newExit] >> 0x18);
				if ((((uVar25 & 0xffffe000) == 0) && ((int)(uVar25 & 0x1fff) < NumDriver2Straights)) &&
					(-1 < (int)uVar25)) {
					if ((*(uint *)(tmpStr2[newExit]->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
						bVar1 = tmpStr2[newExit]->LaneDirs;
						goto LAB_00026788;
					}
				LAB_00026774:
					bVar6 = ((byte)uVar8 ^ 1) & 1 ^ bVar6 >> 7;
				}
				else {
					if (*(short *)&tmpCrv2[newExit]->NumLanes == -0xff) goto LAB_00026774;
					bVar1 = tmpCrv2[newExit]->LaneDirs;
				LAB_00026788:
					bVar6 = ((byte)((int)(uint)bVar1 >> ((int)uVar8 / 2 & 0x1fU)) ^ 1) & 1 ^ bVar6 >> 7;
				}
				cp->ai[0xf] = bVar6;
			}
		}
		goto LAB_000267a4;
	}
	local_58 = 0;
	cp->ai[0x12] = 0;
	pDVar15 = Driver2JunctionsPtr + iVar17 + -0x2000;
	if ((int)pDVar15->ExitIdx[0] == currentRoadId) {
		iVar11 = 0;
	}
	else {
		iVar17 = 1;
		do {
			iVar14 = iVar17;
			iVar11 = -1;
			if (3 < iVar14) break;
			iVar17 = iVar14 + 1;
			iVar11 = iVar14;
		} while ((int)pDVar15->ExitIdx[iVar14] != currentRoadId);
	}
	if (iVar11 == -1) goto LAB_00026928;
	iVar17 = 1;
	iVar14 = 0;
	do {
		iVar10 = iVar17;
		iVar12 = iVar11 + iVar10;
		iVar17 = iVar12;
		if (iVar12 < 0) {
			iVar17 = iVar12 + 3;
		}
		iVar17 = (iVar12 + (iVar17 >> 2) * -4) * 0x1000000;
		iVar12 = iVar17 >> 0x18;
		puVar21 = (ushort *)(pDVar15->ExitIdx + iVar12);
		bVar5 = false;
		if (*puVar21 != 0xffff) {
			iVar19 = 0;
			iVar13 = (iVar12 + 4) - iVar11;
			iVar12 = iVar13;
			if (iVar13 < 0) {
				iVar12 = iVar13 + 3;
			}
			iVar13 = iVar13 + (iVar12 >> 2) * -4;
			if (iVar13 == 1) {
				iVar19 = -0x400;
			}
			else {
				if (1 < iVar13) {
					if (iVar13 == 2) {
						iVar19 = 0;
					}
					else {
						if (iVar13 == 3) {
							iVar19 = 0x400;
						}
					}
				}
			}
			*turnAngle = iVar19;
			test123 = 0x29a;
			test555 = 0x29a;
			test42 = 0x29a;
			uVar3 = *puVar21;
			iVar19 = oldNode->dir + iVar19;
			if ((((uVar3 & 0xe000) == 0) && ((int)((uint)uVar3 & 0x1fff) < NumDriver2Straights)) &&
				(-1 < (int)(short)uVar3)) {
				pDVar22 = Driver2StraightsPtr + (int)(short)uVar3;
				iVar12 = *turnAngle;
				uVar8 = (iVar19 - pDVar22->angle) + 0x400U & 0x800;
				if (uVar8 == 0) {
					iVar12 = -iVar12;
				}
				if (iVar12 == 0) {
					if (uVar8 == uVar29) {
						uVar7 = (uint)cp->ai[0xfb];
					}
					else {
						uVar7 = ((uint)(byte)pDVar22->NumLanes & 0xffffff0f) * 2 - ((uint)cp->ai[0xfb] + 1);
					}
					if ((uVar8 == 0) ||
						(((int)(uint)(byte)pDVar22->AILanes >> ((int)uVar7 / 2 & 0x1fU) & 1U) == 0)) {
						uVar7 = 0xffffffff;
					}
				}
				else {
					if (iVar12 < 1) {
						if (iVar12 == -0x400) {
							uVar25 = (uint)(byte)pDVar22->NumLanes;
							uVar26 = (uVar25 & 0xffffff0f) << 1;
							uVar18 = (uint)((byte)pDVar22->NumLanes >> 6) & 1;
							uVar7 = uVar26;
							if (uVar18 < uVar26) {
								do {
									if (((((int)(uint)(byte)pDVar22->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) != 0)
										&& ((uVar18 != 0 || ((pDVar22->NumLanes & 0x40U) == 0)))) &&
										(((uVar25 & 0xffffff0f) * 2 - 1 != uVar18 || ((uVar25 & 0x80) == 0)))) {
										uVar7 = uVar18;
										if ((*(uint *)(pDVar22->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
											uVar7 = (int)(uint)(byte)pDVar22->LaneDirs >> ((int)uVar18 / 2 & 0x1fU);
										}
										test555 = (uVar7 ^ 1) & 1;
										uVar7 = uVar18;
										if (test555 == 0) {
											if (uVar8 != 0) break;
										}
										else {
											if (uVar8 == 0) break;
										}
									}
									uVar25 = (uint)(byte)pDVar22->NumLanes;
									uVar18 = uVar18 + 1;
									uVar7 = uVar26;
								} while ((int)uVar18 < (int)((uVar25 & 0xffffff0f) << 1));
							}
						}
					}
					else {
						if (iVar12 == 0x400) {
							uVar18 = ((uint)(byte)pDVar22->NumLanes & 0xffffff0f) * 2;
							uVar25 = uVar18;
							do {
								do {
									uVar25 = uVar25 - 1;
									uVar7 = uVar18;
									if ((int)uVar25 < 0) goto LAB_00024be8;
								} while (((((int)(uint)(byte)pDVar22->AILanes >> ((int)uVar25 / 2 & 0x1fU) & 1U) ==
									0) || ((uVar25 == 0 && ((pDVar22->NumLanes & 0x40U) != 0)))) ||
									((((uint)(byte)pDVar22->NumLanes & 0xffffff0f) * 2 - 1 == uVar25 &&
									((pDVar22->NumLanes & 0x80U) != 0))));
								uVar7 = uVar25;
								if ((*(uint *)(pDVar22->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
									uVar7 = (int)(uint)(byte)pDVar22->LaneDirs >> ((int)uVar25 / 2 & 0x1fU);
								}
								test42 = (uVar7 ^ 1) & 1;
								uVar7 = uVar25;
							} while (uVar8 == 0);
						}
					}
				}
			LAB_00024be8:
				if (-1 < (int)uVar7) {
					uVar8 = (uint)(byte)pDVar22->NumLanes;
					iVar12 = (uVar8 & 0xffffff0f) << 1;
					if ((int)uVar7 < iVar12) {
						bVar6 = pDVar22->AILanes;
						iVar19 = uVar7 - ((int)uVar7 >> 0x1f);
					LAB_00024fa4:
						bVar5 = false;
						if (((((int)(uint)bVar6 >> (iVar19 >> 1 & 0x1fU) & 1U) != 0) &&
							((uVar7 != 0 || ((uVar8 & 0x40) == 0)))) &&
							((iVar12 - 1U != uVar7 || ((uVar8 & 0x80) == 0)))) {
							bVar5 = true;
						}
					}
				}
			}
			else {
				pDVar24 = Driver2CurvesPtr + (int)(short)*puVar21 + -0x4000;
				iVar12 = ratan2(oldNode->x - pDVar24->Midx, oldNode->z - pDVar24->Midz);
				bVar5 = false;
				bVar4 = (int)(((iVar19 - iVar12) + 0x800U & 0xfff) - 0x800) < 1;
				iVar12 = *turnAngle;
				if (!bVar4) {
					iVar12 = -iVar12;
				}
				if (iVar12 == 0) {
					if ((uint)bVar4 << 0xb == uVar29) {
						uVar7 = (uint)cp->ai[0xfb];
					}
					else {
						uVar7 = ((uint)(byte)pDVar24->NumLanes & 0xffffff0f) * 2 - ((uint)cp->ai[0xfb] + 1);
					}
					if ((!bVar4) ||
						(((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar7 / 2 & 0x1fU) & 1U) == 0)) {
						uVar7 = 0xffffffff;
					}
				}
				else {
					if (iVar12 < 1) {
						if (iVar12 == -0x400) {
							uVar8 = (uint)(byte)pDVar24->NumLanes;
							uVar18 = (uVar8 & 0xffffff0f) << 1;
							uVar25 = (uint)((byte)pDVar24->NumLanes >> 6) & 1;
							uVar7 = uVar18;
							if (uVar25 < uVar18) {
								do {
									if (((((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar25 / 2 & 0x1fU) & 1U) != 0)
										&& ((uVar25 != 0 || ((pDVar24->NumLanes & 0x40U) == 0)))) &&
										(((uVar8 & 0xffffff0f) * 2 - 1 != uVar25 || ((uVar8 & 0x80) == 0)))) {
										uVar7 = uVar25;
										if (*(short *)&pDVar24->NumLanes != -0xff) {
											uVar7 = (int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar25 / 2 & 0x1fU);
										}
										test555 = (uVar7 ^ 1) & 1;
										uVar7 = uVar25;
										if (test555 == 0) {
											if (bVar4) break;
										}
										else {
											if (!bVar4) break;
										}
									}
									uVar8 = (uint)(byte)pDVar24->NumLanes;
									uVar25 = uVar25 + 1;
									uVar7 = uVar18;
								} while ((int)uVar25 < (int)((uVar8 & 0xffffff0f) << 1));
							}
						}
					}
					else {
						if (iVar12 == 0x400) {
							uVar25 = ((uint)(byte)pDVar24->NumLanes & 0xffffff0f) * 2;
							uVar8 = uVar25;
							do {
								do {
									uVar8 = uVar8 - 1;
									uVar7 = uVar25;
									if ((int)uVar8 < 0) goto LAB_00024f78;
								} while (((((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar8 / 2 & 0x1fU) & 1U) == 0
									) || ((uVar8 == 0 && ((pDVar24->NumLanes & 0x40U) != 0)))) ||
									((((uint)(byte)pDVar24->NumLanes & 0xffffff0f) * 2 - 1 == uVar8 &&
									((pDVar24->NumLanes & 0x80U) != 0))));
								uVar7 = uVar8;
								if (*(short *)&pDVar24->NumLanes != -0xff) {
									uVar7 = (int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar8 / 2 & 0x1fU);
								}
								test42 = (uVar7 ^ 1) & 1;
								uVar7 = uVar8;
							} while (!bVar4);
						}
					}
				}
			LAB_00024f78:
				if (-1 < (int)uVar7) {
					uVar8 = (uint)(byte)pDVar24->NumLanes;
					iVar12 = (uVar8 & 0xffffff0f) << 1;
					if ((int)uVar7 < iVar12) {
						bVar6 = pDVar24->AILanes;
						iVar19 = uVar7 - ((int)uVar7 >> 0x1f);
						goto LAB_00024fa4;
					}
				}
			}
		}
		if (bVar5) {
			(&validExitIdx)[iVar14] = (short)(iVar17 >> 0x18);
			local_58 = local_58 + 1;
		}
		else {
			(&validExitIdx)[iVar14] = 0x2a;
		}
		iVar17 = iVar10 + 1;
		iVar14 = iVar10;
	} while (iVar10 < 3);
	if ((iVar11 < 0) || (local_58 < 1)) goto LAB_00026928;
	if ((local_50 != local_4c) && (local_58 != 1)) {
		if ((uint)cp->ai[0xfb] == local_50) {
			SHORT_ARRAY_000aab3c[0] = 0x2a;
		}
		else {
			if ((uint)cp->ai[0xfb] == local_4c) {
				validExitIdx = 0x2a;
			}
			else {
				if (SHORT_000aab3a != 0x2a) {
					SHORT_ARRAY_000aab3c[0] = 0x2a;
					validExitIdx = 0x2a;
				}
			}
		}
	}
	lVar9 = Random2(0);
	sVar2 = (&validExitIdx)[lVar9 % 3];
	pbVar23 = cp->ai + 0xc;
	iVar17 = lVar9 % 3;
	while (sVar2 == 0x2a) {
		iVar14 = 0;
		if (iVar17 < 2) {
			iVar14 = iVar17 + 1;
		}
		sVar2 = (&validExitIdx)[iVar14];
		iVar17 = iVar14;
	}
	iVar17 = (int)(&validExitIdx)[iVar17];
	uVar25 = SEXT24(pDVar15->ExitIdx[iVar17]);
	iVar14 = 0;
	if (turnAngle != (int *)0x0) {
		iVar12 = (iVar17 + 4) - iVar11;
		iVar10 = iVar12;
		if (iVar12 < 0) {
			iVar10 = iVar12 + 3;
		}
		iVar12 = iVar12 + (iVar10 >> 2) * -4;
		if (iVar12 == 1) {
			iVar14 = -0x400;
		}
		else {
			if (((1 < iVar12) && (iVar12 != 2)) && (iVar12 == 3)) {
				iVar14 = 0x400;
			}
		}
		test42 = iVar11;
		test555 = iVar17;
		*turnAngle = iVar14;
	}
	uVar8 = 0xffffffff;
	uVar18 = 0;
	iVar17 = *turnAngle;
	uVar3 = *(ushort *)&pDVar15->flags;
	do {
		if ((int)pDVar15->ExitIdx[0] == currentRoadId) {
			uVar8 = uVar18;
		}
		uVar18 = uVar18 + 1;
		pDVar15 = (DRIVER2_JUNCTION *)(pDVar15->ExitIdx + 1);
	} while ((int)uVar18 < 4);
	if (*pbVar23 != 8) {
		*pbVar23 = 0;
		if ((uVar3 & 1) == 0) {
			bVar5 = false;
			if ((uVar8 == 0) || (uVar8 == 2)) {
				bVar5 = true;
			}
			if ((uVar3 & 2) == 0) {
				bVar6 = 4;
				if (!bVar5) goto LAB_000252b4;
			LAB_000252ac:
				bVar6 = 6;
				if (iVar17 == 0) goto LAB_000252bc;
				goto LAB_000252b4;
			}
			bVar6 = 4;
			if (!bVar5) goto LAB_000252ac;
			*(CIV_ROUTE_ENTRY **)(cp->ai + 8) = oldNode;
		}
		else {
			cp->ai[0xd] = (byte)(uVar8 & 1);
			bVar6 = 1;
			if ((&junctionLightsPhase)[uVar8 & 1] == '\x03') goto LAB_000252ac;
		LAB_000252b4:
			*(CIV_ROUTE_ENTRY **)(cp->ai + 8) = oldNode;
		}
		*pbVar23 = bVar6;
	}
LAB_000252bc:
	iVar17 = *turnAngle;
	iVar11 = oldNode->dir + iVar17;
	if (((((uVar25 & 0xffffe000) != 0) || (NumDriver2Straights <= (int)(uVar25 & 0x1fff))) &&
		(((uVar25 & 0xffffe000) != 0x4000 || (NumDriver2Curves <= (int)(uVar25 & 0x1fff))))) ||
		((int)uVar25 < 0)) goto LAB_00026928;
	if (((uVar25 & 0xffffe000) == 0) && ((int)(uVar25 & 0x1fff) < NumDriver2Straights)) {
		pDVar30 = Driver2StraightsPtr + uVar25;
		uVar18 = (iVar11 - pDVar30->angle) + 0x400U & 0x800;
		uVar8 = ((uint)(byte)pDVar30->NumLanes & 0xf) * 2;
		if (uVar18 == 0) {
			iVar17 = -iVar17;
		}
		if (iVar17 == 0) {
			if (uVar18 == uVar29) {
				uVar7 = (uint)cp->ai[0xfb];
			}
			else {
				uVar7 = uVar8 - ((uint)cp->ai[0xfb] + 1);
			}
			bVar5 = uVar18 == 0;
			if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) == 0xff010000) {
				if ((uVar7 & 1) == 0) {
				LAB_00025514:
					if (!bVar5) {
						uVar7 = 0xffffffff;
						goto LAB_0002564c;
					}
				}
				else {
					if (bVar5) {
						uVar7 = 0xffffffff;
						goto LAB_0002564c;
					}
				}
			LAB_0002552c:
				if (((int)(uint)(byte)pDVar30->AILanes >> ((int)uVar7 / 2 & 0x1fU) & 1U) != 0)
					goto LAB_0002564c;
			}
			else {
				if (((int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar7 / 2 & 0x1fU) & 1U) == 0)
					goto LAB_00025514;
				if (!bVar5) goto LAB_0002552c;
			}
			uVar7 = 0xffffffff;
		}
		else {
			if (iVar17 < 1) {
				if ((iVar17 == -0x400) &&
					(uVar29 = (uint)((byte)pDVar30->NumLanes >> 6) & 1, uVar7 = uVar8, uVar29 < uVar8)) {
					do {
						if (((((int)(uint)(byte)pDVar30->AILanes >> ((int)uVar29 / 2 & 0x1fU) & 1U) != 0) &&
							((uVar29 != 0 || ((pDVar30->NumLanes & 0x40U) == 0)))) &&
							((((uint)(byte)pDVar30->NumLanes & 0xffffff0f) * 2 - 1 != uVar29 ||
							((pDVar30->NumLanes & 0x80U) == 0)))) {
							uVar7 = uVar29;
							if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
								uVar7 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar29 / 2 & 0x1fU);
							}
							test555 = (uVar7 ^ 1) & 1;
							uVar7 = uVar29;
							if (test555 == 0) {
								if (uVar18 != 0) break;
							}
							else {
								if (uVar18 == 0) break;
							}
						}
						uVar29 = uVar29 + 1;
						uVar7 = uVar8;
					} while ((int)uVar29 < (int)(((uint)(byte)pDVar30->NumLanes & 0xffffff0f) << 1));
				}
			}
			else {
				uVar29 = uVar8;
				if (iVar17 == 0x400) {
					do {
						do {
							uVar29 = uVar29 - 1;
							uVar7 = uVar8;
							if ((int)uVar29 < 0) goto LAB_0002564c;
						} while (((((int)(uint)(byte)pDVar30->AILanes >> ((int)uVar29 / 2 & 0x1fU) & 1U) == 0)
							|| ((uVar29 == 0 && ((pDVar30->NumLanes & 0x40U) != 0)))) ||
							((((uint)(byte)pDVar30->NumLanes & 0xffffff0f) * 2 - 1 == uVar29 &&
							((pDVar30->NumLanes & 0x80U) != 0))));
						uVar7 = uVar29;
						if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
							uVar7 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar29 / 2 & 0x1fU);
						}
						test42 = (uVar7 ^ 1) & 1;
						uVar7 = uVar29;
					} while (uVar18 == 0);
				}
			}
		}
	LAB_0002564c:
		uVar8 = uVar7;
		if (*turnAngle != 0) {
			if (uVar8 - 1 == uVar7) {
				uVar29 = uVar7;
				if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
					uVar29 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar7 / 2 & 0x1fU);
				}
				uVar18 = uVar7;
				if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
					uVar18 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)(uVar7 - 1) / 2 & 0x1fU) ^ 1;
				}
				uVar8 = uVar7 - 1;
				if (((uVar29 ^ 1) & 1) == (uVar18 & 1)) goto LAB_000267a4;
			}
			uVar8 = uVar7;
			if (uVar7 == 0) {
				uVar29 = 1;
				if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
					uVar29 = ((uint)(byte)pDVar30->LaneDirs ^ 1) & 1;
				}
				if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) goto LAB_00025ba4;
			LAB_00025b80:
				uVar18 = uVar8 + 1;
				if (uVar29 == ((uVar18 ^ 1) & 1)) goto LAB_00025bc8;
			}
		}
	}
	else {
		uVar8 = uVar7;
		if (((uVar25 & 0xffffe000) != 0x4000) ||
			((NumDriver2Curves <= (int)(uVar25 & 0x1fff) || ((int)uVar25 < 0)))) goto LAB_000267a4;
		pDVar24 = Driver2CurvesPtr + (uVar25 - 0x4000);
		iVar17 = ratan2(oldNode->x - pDVar24->Midx, oldNode->z - pDVar24->Midz);
		bVar5 = (int)(((iVar11 - iVar17) + 0x800U & 0xfff) - 0x800) < 1;
		iVar17 = *turnAngle;
		uVar8 = ((uint)(byte)pDVar24->NumLanes & 0xf) * 2;
		if (!bVar5) {
			iVar17 = -iVar17;
		}
		if (iVar17 == 0) {
			if ((uint)bVar5 << 0xb == uVar29) {
				uVar7 = (uint)cp->ai[0xfb];
			}
			else {
				uVar7 = uVar8 - ((uint)cp->ai[0xfb] + 1);
			}
			if (*(short *)&pDVar24->NumLanes == -0xff) {
				if ((uVar7 & 1) == 0) {
				LAB_0002595c:
					if (bVar5) {
						uVar7 = 0xffffffff;
						goto LAB_00025a8c;
					}
				}
				else {
					if (!bVar5) {
						uVar7 = 0xffffffff;
						goto LAB_00025a8c;
					}
				}
			LAB_00025974:
				if (((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar7 / 2 & 0x1fU) & 1U) != 0)
					goto LAB_00025a8c;
			}
			else {
				if (((int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar7 / 2 & 0x1fU) & 1U) == 0)
					goto LAB_0002595c;
				if (bVar5) goto LAB_00025974;
			}
			uVar7 = 0xffffffff;
		}
		else {
			if (iVar17 < 1) {
				if ((iVar17 == -0x400) &&
					(uVar29 = (uint)((byte)pDVar24->NumLanes >> 6) & 1, uVar7 = uVar8, uVar29 < uVar8)) {
					do {
						if (((((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar29 / 2 & 0x1fU) & 1U) != 0) &&
							((uVar29 != 0 || ((pDVar24->NumLanes & 0x40U) == 0)))) &&
							((((uint)(byte)pDVar24->NumLanes & 0xffffff0f) * 2 - 1 != uVar29 ||
							((pDVar24->NumLanes & 0x80U) == 0)))) {
							uVar7 = uVar29;
							if (*(short *)&pDVar24->NumLanes != -0xff) {
								uVar7 = (int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar29 / 2 & 0x1fU);
							}
							test555 = (uVar7 ^ 1) & 1;
							uVar7 = uVar29;
							if (test555 == 0) {
								if (bVar5) break;
							}
							else {
								if (!bVar5) break;
							}
						}
						uVar29 = uVar29 + 1;
						uVar7 = uVar8;
					} while ((int)uVar29 < (int)(((uint)(byte)pDVar24->NumLanes & 0xffffff0f) << 1));
				}
			}
			else {
				uVar29 = uVar8;
				if (iVar17 == 0x400) {
					do {
						do {
							uVar29 = uVar29 - 1;
							uVar7 = uVar8;
							if ((int)uVar29 < 0) goto LAB_00025a8c;
						} while (((((int)(uint)(byte)pDVar24->AILanes >> ((int)uVar29 / 2 & 0x1fU) & 1U) == 0)
							|| ((uVar29 == 0 && ((pDVar24->NumLanes & 0x40U) != 0)))) ||
							((((uint)(byte)pDVar24->NumLanes & 0xffffff0f) * 2 - 1 == uVar29 &&
							((pDVar24->NumLanes & 0x80U) != 0))));
						uVar7 = uVar29;
						if (*(short *)&pDVar24->NumLanes != -0xff) {
							uVar7 = (int)(uint)(byte)pDVar24->LaneDirs >> ((int)uVar29 / 2 & 0x1fU);
						}
						test42 = (uVar7 ^ 1) & 1;
						uVar7 = uVar29;
					} while (!bVar5);
				}
			}
		}
	LAB_00025a8c:
		uVar8 = uVar7;
		if (*turnAngle != 0) {
			if (uVar8 - 1 == uVar7) {
				uVar29 = uVar7;
				if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
					uVar29 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar7 / 2 & 0x1fU);
				}
				uVar18 = uVar7;
				if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
					uVar18 = (int)(uint)(byte)pDVar30->LaneDirs >> ((int)(uVar7 - 1) / 2 & 0x1fU) ^ 1;
				}
				uVar8 = uVar7 - 1;
				if (((uVar29 ^ 1) & 1) == (uVar18 & 1)) goto LAB_000267a4;
			}
			uVar8 = uVar7;
			if (uVar7 == 0) {
				uVar29 = 1;
				if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
					uVar29 = ((uint)(byte)pDVar30->LaneDirs ^ 1) & 1;
				}
				if ((*(uint *)(pDVar30->ConnectIdx + 3) & 0xffff0000) == 0xff010000) goto LAB_00025b80;
			LAB_00025ba4:
				uVar18 = uVar7 + 1;
				uVar8 = uVar7;
				if (uVar29 == (((int)(uint)(byte)pDVar30->LaneDirs >> ((int)uVar18 / 2 & 0x1fU) ^ 1U) & 1))
				{
				LAB_00025bc8:
					uVar8 = uVar18;
				}
			}
		}
	}
LAB_000267a4:
	if ((int)uVar8 < 0) goto LAB_00026928;
	cp->ai[0xfb] = (byte)uVar8;
	if (startDist != (int *)0x0) {
		iVar17 = uVar25 << 3;
		if (((uVar25 & 0xffffe000) == 0x4000) &&
			(iVar17 = uVar25 * 8, (int)(uVar25 & 0x1fff) < NumDriver2Curves)) {
			if ((int)uVar25 < 0) {
				iVar17 = uVar25 << 3;
				goto LAB_0002687c;
			}
			pDVar24 = Driver2CurvesPtr + (uVar25 - 0x4000);
			if (*(short *)&pDVar24->NumLanes == -0xff) {
				if ((uVar8 & 1) == 0) {
					uVar7 = 0;
				}
				else {
				LAB_00026844:
					uVar7 = (int)pDVar24->end - (int)pDVar24->start & 0xfff;
				}
			}
			else {
				if (((int)(uint)(byte)pDVar24->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f) & 1U) != 0)
					goto LAB_00026844;
				uVar7 = 0;
			}
			*startDist = uVar7;
			bVar6 = pDVar24->NumLanes;
		}
		else {
		LAB_0002687c:
			piVar28 = &Driver2StraightsPtr->Midx + (iVar17 - uVar25);
			if ((piVar28[5] & 0xffff0000U) == 0xff010000) {
				test555 = 0;
				if ((cp->ai[0xfb] & 1) != 0) {
				LAB_000268e0:
					test555 = ZEXT24(*(ushort *)(piVar28 + 2));
				}
			}
			else {
				test555 = 0;
				if (((int)(uint)*(byte *)((int)piVar28 + 0x17) >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f) & 1U)
					!= 0) goto LAB_000268e0;
			}
			test123 = test555;
			*startDist = test555;
			bVar6 = *(byte *)((int)piVar28 + 0x16);
		}
		cp->ai[0xf8] = speedLimits[(uint)(bVar6 >> 4) & 3];
	}
	if (-1 < (int)uVar25) {
		return uVar25;
	}
LAB_00026928:
	cp->ai[0xf9] = 3;
	cp->ai[0xc] = 7;
	return 0;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitNodeList(struct _CAR_DATA *cp /*$s6*/, char *extraData /*$s7*/)
 // line 1365, offset 0x00026964
	/* begin block 1 */
		// Start line: 1366
		// Start offset: 0x00026964
		// Variables:
	// 		int i; // $v1
	// 		struct CIV_ROUTE_ENTRY *cr; // $s5
	// 		int dx; // $s1
	// 		int dz; // $s2
	// 		int surfInd; // $s4

		/* begin block 1.1 */
			// Start line: 1397
			// Start offset: 0x00026A04
			// Variables:
		// 		int theta; // $s0
		// 		int laneDist; // $s1
		// 		struct DRIVER2_STRAIGHT *str; // $s3
		/* end block 1.1 */
		// End offset: 0x00026B60
		// End Line: 1406

		/* begin block 1.2 */
			// Start line: 1411
			// Start offset: 0x00026B9C
			// Variables:
		// 		struct DRIVER2_CURVE *crv; // $s0
		/* end block 1.2 */
		// End offset: 0x00026C4C
		// End Line: 1415
	/* end block 1 */
	// End offset: 0x00026CAC
	// End Line: 1425

	/* begin block 2 */
		// Start line: 2972
	/* end block 2 */
	// End Line: 2973

	/* begin block 3 */
		// Start line: 2988
	/* end block 3 */
	// End Line: 2989

void InitNodeList(_CAR_DATA *cp, char *extraData)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	ushort uVar2;
	undefined2 *puVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	uint uVar7;
	int iVar8;
	DRIVER2_CURVE *pDVar9;
	DRIVER2_STRAIGHT *pDVar10;
	uint uVar11;
	ushort *puVar12;

	puVar3 = (undefined2 *)(cp->ai + 0x26);
	iVar6 = 0xc;
	uVar11 = *(uint *)cp->ai;
	do {
		*(undefined4 *)(puVar3 + 3) = 0;
		*(undefined4 *)(puVar3 + 5) = 0;
		*puVar3 = 0x7f;
		iVar6 = iVar6 + -1;
		puVar3 = puVar3 + 8;
	} while (-1 < iVar6);
	iVar6 = (cp->hd).where.t[0];
	puVar12 = (ushort *)(cp->ai + 0x24);
	*(int *)(cp->ai + 0x2c) = iVar6;
	iVar8 = (cp->hd).where.t[2];
	*(undefined2 *)(cp->ai + 0x26) = 1;
	*(int *)(cp->ai + 0x30) = iVar8;
	if ((((uVar11 & 0xffffe000) == 0) && ((int)(uVar11 & 0x1fff) < NumDriver2Straights)) &&
		(-1 < (int)uVar11)) {
		pDVar10 = Driver2StraightsPtr + uVar11;
		iVar6 = iVar6 - pDVar10->Midx;
		iVar8 = iVar8 - pDVar10->Midz;
		iVar4 = ratan2(iVar6, iVar8);
		sVar1 = pDVar10->angle;
		iVar5 = SquareRoot0(iVar6 * iVar6 + iVar8 * iVar8);
		*(uint *)(cp->ai + 0x28) =
			(uint)(pDVar10->length >> 1) +
			(rcossin_tbl[(sVar1 - iVar4 & 0xfffU) * 2 + 1] * iVar5 + 0x800 >> 0xc);
		uVar7 = (uint)(ushort)pDVar10->angle & 0xfff;
		iVar6 = ((uint)(byte)pDVar10->NumLanes & 0xf) * 0x200 +
			(-iVar6 * (int)rcossin_tbl[uVar7 * 2 + 1] + iVar8 * rcossin_tbl[uVar7 * 2] + 0x800 >>
				0xc);
		if (iVar6 < 0) {
			iVar6 = iVar6 + 0x1ff;
		}
		uVar7 = iVar6 >> 9;
		cp->ai[0xfb] = (byte)uVar7;
		if ((*(uint *)(pDVar10->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
			uVar7 = (int)(uint)(byte)pDVar10->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
		}
		if ((uVar7 & 1) == 0) {
			*puVar12 = pDVar10->angle;
		}
		else {
			*puVar12 = pDVar10->angle + 0x800U & 0xfff;
		}
	}
	if ((((uVar11 & 0xffffe000) == 0x4000) && ((int)(uVar11 & 0x1fff) < NumDriver2Curves)) &&
		(-1 < (int)uVar11)) {
		if (extraData == (char *)0x0) {
			pDVar9 = Driver2CurvesPtr + (uVar11 - 0x4000);
			uVar11 = ratan2(*(int *)(cp->ai + 0x2c) - pDVar9->Midx, *(int *)(cp->ai + 0x30) - pDVar9->Midz)
				;
			uVar7 = (uVar11 & 0xfff) - (int)pDVar9->start;
			uVar11 = uVar7 & 0xf80;
			if ((9 < (byte)pDVar9->inside) && (uVar11 = uVar7 & 0xfe0, (byte)pDVar9->inside < 0x14)) {
				uVar11 = uVar7 & 0xfc0;
			}
			*(uint *)(cp->ai + 0x28) = uVar11;
			sVar1 = (short)uVar11 + pDVar9->start;
			if (*(short *)&pDVar9->NumLanes == -0xff) {
				uVar11 = (uint)cp->ai[0xfb];
			}
			else {
				uVar11 = (int)(uint)(byte)pDVar9->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
			}
			uVar2 = sVar1 - 0x400;
			if ((uVar11 & 1) == 0) {
				uVar2 = sVar1 + 0x400;
			}
			*puVar12 = uVar2;
		}
		else {
			*(undefined4 *)(cp->ai + 0x28) = *(undefined4 *)(extraData + 4);
			*puVar12 = *(ushort *)(extraData + 8);
		}
	}
	if (extraData != (char *)0x0) {
		*(undefined4 *)(cp->ai + 0x28) = *(undefined4 *)(extraData + 4);
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetNodePos(struct DRIVER2_STRAIGHT *straight /*$t1*/, struct DRIVER2_JUNCTION *junction /*$a1*/, struct DRIVER2_CURVE *curve /*$t0*/, int distAlongPath /*$a3*/, struct _CAR_DATA *cp /*stack 16*/, int *x /*stack 20*/, int *z /*stack 24*/, int laneNo /*stack 28*/)
 // line 1441, offset 0x00026cac
	/* begin block 1 */
		// Start line: 1442
		// Start offset: 0x00026CAC
		// Variables:
	// 		unsigned char oldLane; // $a0
	// 		unsigned char changeLaneCount; // $t3
	/* end block 1 */
	// End offset: 0x00026F20
	// End Line: 1504

	/* begin block 2 */
		// Start line: 3154
	/* end block 2 */
	// End Line: 3155

	/* begin block 3 */
		// Start line: 3171
	/* end block 3 */
	// End Line: 3172

int angle = 0;
int distFromCentre = 0;
int test42 = 0;
int sideShift = 0;
int radius = 0;

// [D]
int GetNodePos(DRIVER2_STRAIGHT *straight, DRIVER2_JUNCTION *junction, DRIVER2_CURVE *curve, int distAlongPath, _CAR_DATA *cp, int *x, int *z, int laneNo)
{
	uint uVar1;
	uint uVar2;
	uint uVar3;

	if (cp == NULL)
	{
		uVar2 = 0;
		uVar3 = 0;
	LAB_00026d04:
		if (curve == NULL) 
		{
			if ((cp != NULL) && (straight == NULL)) 
			{
			LAB_00026ce8:
				cp->ai.c.thrustState = 3;
				cp->ai.c.ctrlState = 7;
				return 0;
			}

			angle = straight->angle;
			distFromCentre = distAlongPath - (straight->length >> 1);

			if ((cp != NULL) && (0x7ff < angle))
				goto LAB_00026ce8;

			uVar1 = uVar3;
			if (laneNo <= uVar2)
				uVar1 = -uVar3;

			test42 = uVar1 * 0x80;
			sideShift = ((straight->NumLanes & 0xf) * 0x200 - (laneNo * 0x200 + 0x100)) + test42;

			*x = straight->Midx +
				(distFromCentre * rcossin_tbl[(angle & 0xfffU) * 2] + 0x800 >> 0xc) +
				(sideShift * rcossin_tbl[(angle & 0xfffU) * 2 + 1] + 0x800 >> 0xc);

			*z = (straight->Midz +
				(distFromCentre * rcossin_tbl[(angle & 0xfffU) * 2 + 1] + 0x800 >> 0xc)) -
				(sideShift * rcossin_tbl[(angle & 0xfffU) * 2] + 0x800 >> 0xc);

			goto LAB_00026f00;
		}
	}
	else {
		uVar2 = cp->ai.c.oldLane;
		uVar3 = cp->ai.c.changeLaneCount;

		if ((straight != NULL) || (junction != NULL)) 
			goto LAB_00026d04;

		if (curve == NULL) 
			goto LAB_00026ce8;
	}

	angle = distAlongPath + curve->start;
	uVar1 = uVar3;

	if (uVar2 < laneNo) 
		uVar1 = -uVar3;

	test42 = uVar1 * 0x80;
	radius = curve->inside * 0x400 + laneNo * 0x200 + 0x100 + test42;

	*x = curve->Midx + (radius * rcossin_tbl[(angle & 0xfffU) * 2] + 0x800 >> 0xc);
	*z = curve->Midz + (radius * rcossin_tbl[(angle & 0xfffU) * 2 + 1] + 0x800 >> 0xc);
LAB_00026f00:
	if (uVar3 != 0) 
	{
		cp->ai.c.changeLaneCount--;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckChangeLanes(struct DRIVER2_STRAIGHT *straight /*$s4*/, struct DRIVER2_CURVE *curve /*$s6*/, int distAlongSegment /*$a2*/, struct _CAR_DATA *cp /*$s3*/, int tryToPark /*stack 16*/)
 // line 1507, offset 0x00026f20
	/* begin block 1 */
		// Start line: 1508
		// Start offset: 0x00026F20
		// Variables:
	// 		unsigned char currentLane; // $s7
	// 		unsigned char newLane; // $s2
	// 		unsigned char trials; // $t3
	// 		unsigned char canProceed; // stack offset -88
	// 		unsigned char travelAlongRoad; // $s5
	// 		unsigned char turnRight; // stack offset -84
	// 		struct _CAR_DATA *cp1; // $s0
	// 		struct CIV_ROUTE_ENTRY tmpNode; // stack offset -120

		/* begin block 1.1 */
			// Start line: 1572
			// Start offset: 0x00027290
			// Variables:
		// 		struct VECTOR pos; // stack offset -104
		// 		int theta; // $a0
		// 		int length; // $a1

			/* begin block 1.1.1 */
				// Start line: 1588
				// Start offset: 0x00027394
			/* end block 1.1.1 */
			// End offset: 0x00027494
			// End Line: 1596
		/* end block 1.1 */
		// End offset: 0x000274A4
		// End Line: 1598
	/* end block 1 */
	// End offset: 0x00027530
	// End Line: 1623

	/* begin block 2 */
		// Start line: 3328
	/* end block 2 */
	// End Line: 3329

	/* begin block 3 */
		// Start line: 3332
	/* end block 3 */
	// End Line: 3333

	/* begin block 4 */
		// Start line: 3337
	/* end block 4 */
	// End Line: 3338

int CheckChangeLanes(DRIVER2_STRAIGHT *straight, DRIVER2_CURVE *curve, int distAlongSegment, _CAR_DATA *cp, int tryToPark)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	bool bVar2;
	byte bVar3;
	uint uVar4;
	long lVar5;
	int iVar6;
	CAR_COSMETICS *pCVar7;
	uint uVar8;
	int iVar9;
	uint uVar10;
	_CAR_DATA *p_Var11;
	uint uVar12;
	uint uVar13;
	uint unaff_s5;
	bool local_54;

	bVar2 = false;
	bVar1 = cp->ai[0xfb];
	uVar12 = (uint)bVar1;
	if ((cp->ai[0xc] != 8) && (*(int *)(cp->ai + 0x18) == 0)) {
		if (straight == (DRIVER2_STRAIGHT *)0x0) {
			bVar3 = curve->NumLanes;
		}
		else {
			bVar3 = straight->NumLanes;
		}
		uVar4 = ((uint)bVar3 & 0xf) * 2;
		lVar5 = Random2((int)straight);
		uVar13 = uVar12 + (lVar5 >> 7 & 2U) + 0xff & 0xff;
		if (tryToPark != 0) {
			if (bVar1 == 1) {
				uVar13 = 0;
			}
			else {
				if (uVar4 - 2 == uVar12) {
					uVar13 = uVar4 - 1 & 0xff;
				}
			}
		}
		bVar3 = 0;
		uVar10 = (uVar12 ^ 1) & 1;
		do {
			if (bVar3 == 1) {
				uVar13 = uVar12 * 2 - uVar13 & 0xff;
			}
			if ((uVar13 == 0xff) || (uVar4 <= uVar13)) goto LAB_000274bc;
			if ((gCurrentMissionNumber == 0x21) && (makeLimoPullOver != '\0')) {
			LAB_0002718c:
				if (straight != (DRIVER2_STRAIGHT *)0x0) {
					unaff_s5 = uVar10;
					if ((*(uint *)(straight->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
						unaff_s5 = ((int)(uint)(byte)straight->LaneDirs >> ((uint)(bVar1 >> 1) & 0x1f) ^ 1U) & 1
							;
					}
					uVar8 = uVar13;
					if ((*(uint *)(straight->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
						uVar8 = (int)(uint)(byte)straight->LaneDirs >> (uVar13 >> 1 & 0x1f);
					}
					if (((uVar8 ^ 1) & 1) != unaff_s5) goto LAB_000274bc;
				}
				if (curve != (DRIVER2_CURVE *)0x0) {
					unaff_s5 = uVar10;
					if ((*(uint *)&curve->NumLanes & 0xffff) != 0xff01) {
						unaff_s5 = ((int)(uint)(byte)curve->LaneDirs >> ((uint)(bVar1 >> 1) & 0x1f) ^ 1U) & 1;
					}
					uVar8 = uVar13;
					if ((*(uint *)&curve->NumLanes & 0xffff) != 0xff01) {
						uVar8 = (int)(uint)(byte)curve->LaneDirs >> (uVar13 >> 1 & 0x1f);
					}
					if (((uVar8 ^ 1) & 1) != unaff_s5) goto LAB_000274bc;
				}
				if ((*(int *)(cp->ai + 8) == 0) && (*(int *)(cp->ai + 0x14) == -1)) {
					bVar2 = true;
					local_54 = unaff_s5 != 0;
					if (uVar12 < uVar13) {
						local_54 = !local_54;
					}
					iVar6 = (cp->hd).direction;
					uVar8 = iVar6 - 0x400;
					if (local_54 != false) {
						uVar8 = iVar6 + 0x400;
					}
					cd.x.vx = (cp->hd).oBox.location.vx +
						((int)rcossin_tbl[(uVar8 & 0xfff) * 2] * 0x200 + 0x800 >> 0xc);
					cd.x.vz = (cp->hd).oBox.location.vz +
						((int)rcossin_tbl[(uVar8 & 0xfff) * 2 + 1] * 0x200 + 0x800 >> 0xc);
					cd.length[0] = (int)(((cp->ap).carCos)->colBox).vz + 0x5d;
					cd.length[1] = (int)(((cp->ap).carCos)->colBox).vx;
					cd.theta = (cp->hd).direction;
					p_Var11 = car_data + 0x13;
					do {
						if ((p_Var11 != cp) && (p_Var11->controlType != '\0')) {
							pCVar7 = (p_Var11->ap).carCos;
							CDATA2D_000bd0e4.length[0] = (int)(pCVar7->colBox).vz + 0x5d;
							CDATA2D_000bd0e4.x.vx = (p_Var11->hd).oBox.location.vx;
							CDATA2D_000bd0e4.length[1] = (int)(pCVar7->colBox).vx;
							CDATA2D_000bd0e4.x.vz = (p_Var11->hd).oBox.location.vz;
							CDATA2D_000bd0e4.theta = (p_Var11->hd).direction;
							iVar9 = ((cd.length[0] + CDATA2D_000bd0e4.length[0]) * 3) / 2;
							iVar6 = cd.x.vx - CDATA2D_000bd0e4.x.vx;
							if (iVar6 < 0) {
								iVar6 = CDATA2D_000bd0e4.x.vx - cd.x.vx;
							}
							if (iVar6 < iVar9) {
								iVar6 = cd.x.vz - CDATA2D_000bd0e4.x.vz;
								if (iVar6 < 0) {
									iVar6 = CDATA2D_000bd0e4.x.vz - cd.x.vz;
								}
								if ((iVar6 < iVar9) && (iVar6 = bcollided2d(&cd, 1), iVar6 != 0)) {
									bVar2 = false;
									break;
								}
							}
						}
						p_Var11 = p_Var11 + -1;
					} while ((_CAR_DATA *)((int)&cheats.MagicMirror + 3U) < p_Var11);
					if (bVar2) goto LAB_000274d8;
				}
			}
			else {
				if (tryToPark == 0) {
					if (((straight == (DRIVER2_STRAIGHT *)0x0) ||
						(((((int)(uint)(byte)straight->AILanes >> (uVar13 >> 1 & 0x1f) & 1U) != 0 &&
						((uVar13 != 0 || ((straight->NumLanes & 0x40U) == 0)))) &&
							((((uint)(byte)straight->NumLanes & 0xf) * 2 - 1 != uVar13 ||
							((straight->NumLanes & 0x80U) == 0)))))) &&
								((curve == (DRIVER2_CURVE *)0x0 ||
						(((((int)(uint)(byte)curve->AILanes >> (uVar13 >> 1 & 0x1f) & 1U) != 0 &&
									((uVar13 != 0 || ((curve->NumLanes & 0x40U) == 0)))) &&
							((((uint)(byte)curve->NumLanes & 0xf) * 2 - 1 != uVar13 ||
							((curve->NumLanes & 0x80U) == 0)))))))) goto LAB_0002718c;
				}
				else {
					if (((straight == (DRIVER2_STRAIGHT *)0x0) ||
						(((int)(uint)(byte)straight->AILanes >> (uVar13 >> 1 & 0x1f) & 1U) != 0)) &&
						((curve == (DRIVER2_CURVE *)0x0 ||
						(((int)(uint)(byte)curve->AILanes >> (uVar13 >> 1 & 0x1f) & 1U) != 0))))
						goto LAB_0002718c;
				}
			}
		LAB_000274bc:
			bVar3 = bVar3 + 1;
		} while (bVar3 < 2);
		if (bVar2) {
		LAB_000274d8:
			*(undefined4 *)(cp->ai + 0x18) = 0xa1;
			cp->ai[0x11] = bVar1;
			cp->ai[0x12] = 4;
			*(bool *)(cp->ai + 0xe) = local_54;
			uVar12 = uVar13;
		}
	}
	return uVar12;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CreateNewNode(struct _CAR_DATA *cp /*$s4*/)
 // line 1637, offset 0x00027530
	/* begin block 1 */
		// Start line: 1638
		// Start offset: 0x00027530
		// Variables:
	// 		int oldRoad; // $s1
	// 		int cr; // $a3
	// 		struct CIV_ROUTE_ENTRY *newNode; // $s6
	// 		struct CIV_ROUTE_ENTRY *oldNode; // $s3
	// 		struct DRIVER2_CURVE *curve; // $s0
	// 		struct DRIVER2_STRAIGHT *straight; // $s5
	// 		int turnAngle; // stack offset -56

		/* begin block 1.1 */
			// Start line: 1638
			// Start offset: 0x00027530
			// Variables:
		// 		struct _CAR_DATA *cp; // $s4
		// 		struct CIV_ROUTE_ENTRY *currentNode; // $v1

			/* begin block 1.1.1 */
				// Start line: 1638
				// Start offset: 0x00027530
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $a0
			/* end block 1.1.1 */
			// End offset: 0x0002757C
			// End Line: 1638
		/* end block 1.1 */
		// End offset: 0x0002757C
		// End Line: 1638

		/* begin block 1.2 */
			// Start line: 1638
			// Start offset: 0x0002758C
			// Variables:
		// 		struct _CAR_DATA *cp; // $s4

			/* begin block 1.2.1 */
				// Start line: 1638
				// Start offset: 0x0002758C
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $a0
			/* end block 1.2.1 */
			// End offset: 0x0002759C
			// End Line: 1638
		/* end block 1.2 */
		// End offset: 0x0002759C
		// End Line: 1638

		/* begin block 1.3 */
			// Start line: 1638
			// Start offset: 0x000275A8
			// Variables:
		// 		struct _CAR_DATA *cp; // $s4

			/* begin block 1.3.1 */
				// Start line: 1638
				// Start offset: 0x000275A8
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $a0
			/* end block 1.3.1 */
			// End offset: 0x000275B8
			// End Line: 1638
		/* end block 1.3 */
		// End offset: 0x000275B8
		// End Line: 1638

		/* begin block 1.4 */
			// Start line: 1638
			// Start offset: 0x000275C4
			// Variables:
		// 		struct _CAR_DATA *cp; // $s4

			/* begin block 1.4.1 */
				// Start line: 1638
				// Start offset: 0x000275C4
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $a0
			/* end block 1.4.1 */
			// End offset: 0x000275D4
			// End Line: 1638
		/* end block 1.4 */
		// End offset: 0x000275D4
		// End Line: 1638

		/* begin block 1.5 */
			// Start line: 1653
			// Start offset: 0x000275F0
			// Variables:
		// 		struct _CAR_DATA *cp; // $s4
		// 		struct CIV_ROUTE_ENTRY *currentNode; // $s3

			/* begin block 1.5.1 */
				// Start line: 1653
				// Start offset: 0x000275F0
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
			/* end block 1.5.1 */
			// End offset: 0x000275F0
			// End Line: 1653
		/* end block 1.5 */
		// End offset: 0x000275F0
		// End Line: 1653

		/* begin block 1.6 */
			// Start line: 1655
			// Start offset: 0x000275F0

			/* begin block 1.6.1 */
				// Start line: 1638
				// Start offset: 0x000275F0
				// Variables:
			// 		struct _CAR_DATA *cp; // $s4

				/* begin block 1.6.1.1 */
					// Start line: 1638
					// Start offset: 0x000275F0
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.6.1.1 */
				// End offset: 0x00027600
				// End Line: 1638
			/* end block 1.6.1 */
			// End offset: 0x00027600
			// End Line: 1638
		/* end block 1.6 */
		// End offset: 0x00027610
		// End Line: 1658

		/* begin block 1.7 */
			// Start line: 1659
			// Start offset: 0x00027634
			// Variables:
		// 		struct _CAR_DATA *cp; // $s4
		// 		struct CIV_ROUTE_ENTRY *currentNode; // $s3

			/* begin block 1.7.1 */
				// Start line: 1659
				// Start offset: 0x00027634
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $s2
			/* end block 1.7.1 */
			// End offset: 0x0002764C
			// End Line: 1659
		/* end block 1.7 */
		// End offset: 0x0002764C
		// End Line: 1659

		/* begin block 1.8 */
			// Start line: 1681
			// Start offset: 0x000276E8
			// Variables:
		// 		int travelDir; // $a1
		// 		int segmentEnd; // $a0

			/* begin block 1.8.1 */
				// Start line: 1688
				// Start offset: 0x000277B0
				// Variables:
			// 		int startDist; // stack offset -52
			/* end block 1.8.1 */
			// End offset: 0x00027808
			// End Line: 1688
		/* end block 1.8 */
		// End offset: 0x00027818
		// End Line: 1688

		/* begin block 1.9 */
			// Start line: 1692
			// Start offset: 0x0002784C
			// Variables:
		// 		int travelDir; // $a2
		// 		int segmentEnd; // $t0

			/* begin block 1.9.1 */
				// Start line: 1699
				// Start offset: 0x00027954
				// Variables:
			// 		int startDist; // stack offset -48
			/* end block 1.9.1 */
			// End offset: 0x00027990
			// End Line: 1699
		/* end block 1.9 */
		// End offset: 0x000279A4
		// End Line: 1700

		/* begin block 1.10 */
			// Start line: 1717
			// Start offset: 0x00027A18
			// Variables:
		// 		struct CIV_ROUTE_ENTRY tmpNode; // stack offset -72

			/* begin block 1.10.1 */
				// Start line: 1721
				// Start offset: 0x00027A58
				// Variables:
			// 		int travelDir; // $a0
			/* end block 1.10.1 */
			// End offset: 0x00027B18
			// End Line: 1732

			/* begin block 1.10.2 */
				// Start line: 1739
				// Start offset: 0x00027B90
				// Variables:
			// 		struct _CAR_DATA *playerCar; // $v0
			// 		int dx; // $v1
			// 		int dz; // $a0
			/* end block 1.10.2 */
			// End offset: 0x00027C00
			// End Line: 1744

			/* begin block 1.10.3 */
				// Start line: 1751
				// Start offset: 0x00027C38
				// Variables:
			// 		int tryToPark; // $s1
			/* end block 1.10.3 */
			// End offset: 0x00027DA0
			// End Line: 1773

			/* begin block 1.10.4 */
				// Start line: 1779
				// Start offset: 0x00027E04
				// Variables:
			// 		int radOfCrv; // $s5
			// 		int cornerAngle; // $a3
			// 		int segLength; // $s0
			// 		int tmp; // $a1
			// 		int dx; // $s1
			// 		int dz; // $s0

				/* begin block 1.10.4.1 */
					// Start line: 1789
					// Start offset: 0x00027EBC
					// Variables:
				// 		struct _CAR_DATA *cp; // $s4

					/* begin block 1.10.4.1.1 */
						// Start line: 1789
						// Start offset: 0x00027EBC
						// Variables:
					// 		struct CIV_ROUTE_ENTRY *retNode; // $a0
					/* end block 1.10.4.1.1 */
					// End offset: 0x00027F44
					// End Line: 1792
				/* end block 1.10.4.1 */
				// End offset: 0x00027F44
				// End Line: 1792

				/* begin block 1.10.4.2 */
					// Start line: 1800
					// Start offset: 0x00027F78
					// Variables:
				// 		struct _CAR_DATA *cp; // $s4

					/* begin block 1.10.4.2.1 */
						// Start line: 1800
						// Start offset: 0x00027F78
						// Variables:
					// 		struct CIV_ROUTE_ENTRY *retNode; // $a0
					/* end block 1.10.4.2.1 */
					// End offset: 0x0002800C
					// End Line: 1803
				/* end block 1.10.4.2 */
				// End offset: 0x0002800C
				// End Line: 1803
			/* end block 1.10.4 */
			// End offset: 0x0002800C
			// End Line: 1806

			/* begin block 1.10.5 */
				// Start line: 1810
				// Start offset: 0x0002800C

				/* begin block 1.10.5.1 */
					// Start line: 1638
					// Start offset: 0x0002800C
					// Variables:
				// 		struct _CAR_DATA *cp; // $s4
				// 		struct CIV_ROUTE_ENTRY *currentNode; // $s6

					/* begin block 1.10.5.1.1 */
						// Start line: 1638
						// Start offset: 0x0002800C
						// Variables:
					// 		struct CIV_ROUTE_ENTRY *retNode; // $v0
					/* end block 1.10.5.1.1 */
					// End offset: 0x0002800C
					// End Line: 1638
				/* end block 1.10.5.1 */
				// End offset: 0x0002800C
				// End Line: 1638
			/* end block 1.10.5 */
			// End offset: 0x0002801C
			// End Line: 1814
		/* end block 1.10 */
		// End offset: 0x0002801C
		// End Line: 1814
	/* end block 1 */
	// End offset: 0x000280D8
	// End Line: 1828

	/* begin block 2 */
		// Start line: 3743
	/* end block 2 */
	// End Line: 3744

	/* begin block 3 */
		// Start line: 3758
	/* end block 3 */
	// End Line: 3759

/* WARNING: Could not reconcile some variable overlaps */

int CreateNewNode(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	return 0;
	/*
	short sVar1;
	uint uVar2;
	long lVar3;
	_CAR_DATA *oldNode;
	_CAR_DATA *p_Var4;
	_CAR_DATA *p_Var5;
	int iVar6;
	undefined4 uVar7;
	_CAR_DATA *p_Var8;
	int iVar9;
	uint tryToPark;
	DRIVER2_CURVE *curve;
	int iVar10;
	int iVar11;
	DRIVER2_STRAIGHT *straight;
	short local_48;
	int local_40;
	int local_3c;
	int local_38;
	int local_34;
	int local_30[2];

	oldNode = *(_CAR_DATA **)(cp->ai + 0xf4);
	p_Var8 = (_CAR_DATA *)(cp->ai + 0xf4);
	tstNode1 = (CIV_ROUTE_ENTRY *)((oldNode->hd).where.m + 8);
	local_38 = 0;
	if (p_Var8 <= tstNode1) {
		tstNode1 = (CIV_ROUTE_ENTRY *)(oldNode[-1].ai + 0x50);
	}
	p_Var5 = (_CAR_DATA *)((oldNode->hd).where.m + 8);
	if (cp < tstNode1) {
		if (p_Var8 <= p_Var5) {
			p_Var5 = (_CAR_DATA *)(oldNode[-1].ai + 0x50);
		}
		p_Var4 = (_CAR_DATA *)&(oldNode->hd).drawCarMat;
		if (p_Var5 < cp + 1) {
			p_Var5 = p_Var4;
			if (p_Var8 <= p_Var4) {
				p_Var5 = (_CAR_DATA *)(oldNode[-1].ai + 0x60);
			}
			if (cp < p_Var5) {
				if (p_Var8 <= p_Var4) {
					p_Var4 = (_CAR_DATA *)(oldNode[-1].ai + 0x60);
				}
				if ((p_Var4 < cp + 1) && (oldNode != (_CAR_DATA *)0x0)) {
					do {
						p_Var4 = (_CAR_DATA *)((oldNode->hd).where.m + 8);
						p_Var5 = p_Var4;
						if (p_Var8 <= p_Var4) {
							p_Var5 = (_CAR_DATA *)(oldNode[-1].ai + 0x50);
						}
						if ((p_Var5->hd).where.m[1] == 0x7f) {
							tryToPark = *(uint *)cp->ai;
							if (p_Var8 <= p_Var4) {
								p_Var4 = (_CAR_DATA *)(oldNode[-1].ai + 0x50);
							}
							if ((uint)(byte)cp->id == makeNextNodeCtrlNode) {
								*(_CAR_DATA **)(cp->ai + 8) = p_Var4;
								makeNextNodeCtrlNode = -1;
							}
							if (((((tryToPark & 0xffffe000) != 0) ||
								(NumDriver2Straights <= (int)(tryToPark & 0x1fff))) &&
								(((tryToPark & 0xffffe000) != 0x4000 ||
								(NumDriver2Curves <= (int)(tryToPark & 0x1fff))))) || ((int)tryToPark < 0))
								break;
							if (((tryToPark & 0xffffe000) == 0) &&
								((int)(tryToPark & 0x1fff) < NumDriver2Straights)) {
								straight = Driver2StraightsPtr + tryToPark;
								if ((*(uint *)(straight->ConnectIdx + 3) & 0xffff0000) == 0xff010000) {
									uVar2 = (uint)cp->ai[0xfb];
								}
								else {
									uVar2 = (int)(uint)(byte)straight->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
								}
								iVar9 = -1;
								if ((uVar2 & 1) == 0) {
									iVar9 = 1;
								}
								uVar2 = (uint)straight->length;
								iVar6 = *(int *)((oldNode->hd).where.m + 2) + iVar9 * 0x400;
								*(int *)((p_Var4->hd).where.m + 2) = iVar6;
								(p_Var4->hd).where.m[0] = (oldNode->hd).where.m[0];
								if (((0 < iVar9) && ((int)uVar2 < iVar6)) || ((iVar9 < 0 && (iVar6 < 0)))) {
									if (((iVar9 < 1) || (*(int *)((oldNode->hd).where.m + 2) < (int)uVar2)) &&
										((-1 < iVar9 || (0 < *(int *)((oldNode->hd).where.m + 2))))) {
										if (iVar9 < 1) {
										LAB_000279a0:
											*(undefined4 *)((p_Var4->hd).where.m + 2) = 0;
										}
										else {
											*(uint *)((p_Var4->hd).where.m + 2) = uVar2;
										}
									}
									else {
										iVar9 = GetNextRoadInfo(cp, 1, &local_38, &local_34, (CIV_ROUTE_ENTRY *)oldNode);
										*(int *)cp->ai = iVar9;
										(p_Var4->hd).where.m[0] = (oldNode->hd).where.m[0] + (short)local_38 & 0xfff;
										*(int *)((p_Var4->hd).where.m + 2) = local_34;
									LAB_000277f0:
										if (*(int *)cp->ai == -1) break;
									}
								}
							}
							else {
								if (((tryToPark & 0xffffe000) == 0x4000) &&
									(((int)(tryToPark & 0x1fff) < NumDriver2Curves && (-1 < (int)tryToPark)))) {
									curve = Driver2CurvesPtr + (tryToPark - 0x4000);
									if (*(short *)&curve->NumLanes == -0xff) {
										uVar2 = (uint)cp->ai[0xfb];
									}
									else {
										uVar2 = (int)(uint)(byte)curve->LaneDirs >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f);
									}
									iVar9 = -1;
									if ((uVar2 & 1) == 0) {
										iVar9 = 1;
									}
									uVar2 = (int)curve->end - (int)curve->start & 0xfff;
									if ((byte)curve->inside < 10) {
										iVar6 = iVar9 << 7;
									}
									else {
										iVar6 = iVar9 << 6;
										if (0x13 < (byte)curve->inside) {
											iVar6 = iVar9 << 5;
										}
									}
									iVar6 = *(int *)((oldNode->hd).where.m + 2) + iVar6;
									*(int *)((p_Var4->hd).where.m + 2) = iVar6;
									(p_Var4->hd).where.m[0] =
										(p_Var4->hd).where.m[2] + curve->start + (short)iVar9 * 0x400 & 0xfff;
									if (((0 < iVar9) && ((int)uVar2 < iVar6)) || ((iVar9 < 0 && (iVar6 < 0)))) {
										if (((0 < iVar9) && ((int)uVar2 <= *(int *)((oldNode->hd).where.m + 2))) ||
											((iVar9 < 0 && (*(int *)((oldNode->hd).where.m + 2) < 1)))) {
											iVar9 = GetNextRoadInfo(cp, 1, &local_38, local_30, (CIV_ROUTE_ENTRY *)oldNode);
											*(int *)cp->ai = iVar9;
											(p_Var4->hd).where.m[0] = (oldNode->hd).where.m[0] + (short)local_38 & 0xfff;
											*(int *)((p_Var4->hd).where.m + 2) = local_30[0];
											goto LAB_000277f0;
										}
										if (iVar9 < 1) goto LAB_000279a0;
										*(uint *)((p_Var4->hd).where.m + 2) = uVar2;
									}
								}
							}
							uVar2 = *(uint *)cp->ai;
							if (-1 < (int)uVar2) {
								curve = (DRIVER2_CURVE *)0x0;
								if (((uVar2 & 0xffffe000) == 0x4000) &&
									(straight = (DRIVER2_STRAIGHT *)0x0, (int)(uVar2 & 0x1fff) < NumDriver2Curves)) {
									curve = Driver2CurvesPtr + (uVar2 - 0x4000);
								}
								else {
									straight = Driver2StraightsPtr + uVar2;
								}
								local_40 = *(int *)((p_Var4->hd).where.m + 4);
								local_3c = *(int *)((p_Var4->hd).where.m + 6);
								if ((tryToPark != uVar2) && (local_38 == 0)) {
									if (straight == (DRIVER2_STRAIGHT *)0x0) {
										if (*(short *)&curve->NumLanes == -0xff) {
											tryToPark = (uint)cp->ai[0xfb];
										}
										else {
											tryToPark = (int)(uint)(byte)curve->LaneDirs >>
												((uint)(cp->ai[0xfb] >> 1) & 0x1f);
										}
										iVar9 = -1;
										if ((tryToPark & 1) == 0) {
											iVar9 = 1;
										}
										iVar6 = iVar9 << 7;
										if ((9 < (byte)curve->inside) &&
											(iVar6 = iVar9 << 6, 0x13 < (byte)curve->inside)) {
											iVar6 = iVar9 << 5;
										}
										iVar6 = *(int *)((p_Var4->hd).where.m + 2) + iVar6;
									}
									else {
										if ((*(uint *)(straight->ConnectIdx + 3) & 0xffff0000) == 0xff010000) {
											tryToPark = (uint)cp->ai[0xfb];
										}
										else {
											tryToPark = (int)(uint)(byte)straight->LaneDirs >>
												((uint)(cp->ai[0xfb] >> 1) & 0x1f);
										}
										iVar9 = -1;
										if ((tryToPark & 1) == 0) {
											iVar9 = 1;
										}
										iVar6 = *(int *)((p_Var4->hd).where.m + 2) + iVar9 * 0x400;
									}
									*(int *)((p_Var4->hd).where.m + 2) = iVar6;
								}
								if ((((gCurrentMissionNumber == 0x21) &&
									(iVar9 = CarHasSiren((uint)(byte)car_data[player.playerCarId].ap.model),
										iVar9 != 0)) && (player.horn.on != '\0')) &&
										(((cp->ap).model == '\x04' &&
									(iVar9 = car_data[player.playerCarId].hd.where.t[0] - (cp->hd).where.t[0],
										iVar6 = car_data[player.playerCarId].hd.where.t[2] - (cp->hd).where.t[2],
										iVar9 * iVar9 + iVar6 * iVar6 < 16000000)))) {
									makeLimoPullOver = '\x01';
								}
								lVar3 = Random2(0);
								if (((lVar3 + (uint)(byte)cp->id * 0x20 & 0xf1) == 0xf1) ||
									(makeLimoPullOver != '\0')) {
									tryToPark = 0;
									if (numParkedCars < maxParkedCars) {
										tryToPark = Random2(0);
										tryToPark = (uint)((tryToPark & 2) != 0);
									}
									if ((gCurrentMissionNumber == 0x21) && ((cp->ap).model == '\x04')) {
										tryToPark = (uint)(makeLimoPullOver != '\0');
									}
									uVar2 = CheckChangeLanes(straight, curve, *(int *)((p_Var4->hd).where.m + 2), cp,
										tryToPark);
									uVar2 = uVar2 & 0xff;
									if (((uVar2 != (uint)cp->ai[0xfb]) && (cp->ai[0xfb] = (byte)uVar2, tryToPark != 0)
										) && ((makeLimoPullOver != '\0' ||
										((cp->ai[0xc] == 0 &&
											(((straight != (DRIVER2_STRAIGHT *)0x0 &&
											(((uVar2 == 0 && ((straight->NumLanes & 0x40U) != 0)) ||
												((((uint)(byte)straight->NumLanes & 0xf) * 2 - 1 ==
												(uint)cp->ai[0xfb] && ((straight->NumLanes & 0x80U) != 0)))))) ||
													((curve != (DRIVER2_CURVE *)0x0 &&
												(((cp->ai[0xfb] == 0 && ((curve->NumLanes & 0x40U) != 0)) ||
														((((uint)(byte)curve->NumLanes & 0xf) * 2 - 1 == (uint)cp->ai[0xfb]
															&& ((curve->NumLanes & 0x80U) != 0)))))))))))))) {
										makeNextNodeCtrlNode = ZEXT14((byte)cp->id);
										cp->ai[0xc] = 8;
										*(_CAR_DATA **)(cp->ai + 8) = p_Var4;
										cp->ai[0x12] = 0;
									}
								}
								tryToPark = *(uint *)(p_Var4->hd).where.m;
								uVar7 = *(undefined4 *)((p_Var4->hd).where.m + 2);
								local_40 = *(int *)((p_Var4->hd).where.m + 4);
								local_3c = *(int *)((p_Var4->hd).where.m + 6);
								GetNodePos(straight, (DRIVER2_JUNCTION *)0x0, curve, *(int *)((p_Var4->hd).where.m + 2)
									, cp, &local_40, &local_3c, (uint)cp->ai[0xfb]);
								if (local_38 == -0x400) {
									iVar11 = local_40 - *(int *)((oldNode->hd).where.m + 4);
									iVar10 = local_3c - *(int *)((oldNode->hd).where.m + 6);
									iVar9 = (cp->hd).wheel_speed / 0xaa;
									iVar6 = SquareRoot0(iVar11 * iVar11 + iVar10 * iVar10);
									iVar10 = ratan2(iVar11, iVar10);
									uVar2 = ((iVar10 - (oldNode->hd).where.m[0]) + 0x800U & 0xfff) - 0x800;
									iVar10 = (iVar6 - iVar9) * (int)rcossin_tbl[(uVar2 & 0xfff) * 2 + 1] + 0x800 >>
										0xc;
									p_Var5 = p_Var4;
									if (0 < iVar10) {
										*(int *)((p_Var4->hd).where.m + 4) =
											*(int *)((oldNode->hd).where.m + 4) +
											(iVar10 * rcossin_tbl[((uint)(ushort)(oldNode->hd).where.m[0] & 0xfff) * 2]
												+ 0x800 >> 0xc);
										p_Var5 = (_CAR_DATA *)((p_Var4->hd).where.m + 8);
										*(int *)((p_Var4->hd).where.m + 6) =
											*(int *)((oldNode->hd).where.m + 6) +
											(iVar10 * rcossin_tbl
												[((uint)(ushort)(oldNode->hd).where.m[0] & 0xfff) * 2 + 1] +
												0x800 >> 0xc);
										sVar1 = (oldNode->hd).where.m[0];
										(p_Var4->hd).where.m[1] = 1;
										(p_Var4->hd).where.m[0] = sVar1;
										if (p_Var8 <= p_Var5) {
											p_Var5 = (_CAR_DATA *)(p_Var4[-1].ai + 0x50);
										}
									}
									iVar9 = (iVar6 - iVar9) * (int)rcossin_tbl[(uVar2 & 0xfff) * 2] + 0x800 >> 0xc;
									p_Var4 = p_Var5;
									if (iVar9 < 0) {
										local_48 = (short)tryToPark;
										*(int *)((p_Var5->hd).where.m + 4) =
											local_40 + (iVar9 * rcossin_tbl[(tryToPark & 0xfff) * 2] + 0x800 >> 0xc);
										p_Var4 = (_CAR_DATA *)((p_Var5->hd).where.m + 8);
										*(int *)((p_Var5->hd).where.m + 6) =
											local_3c +
											(iVar9 * rcossin_tbl[(tryToPark & 0xfff) * 2 + 1] + 0x800 >> 0xc);
										(p_Var5->hd).where.m[1] = 1;
										(p_Var5->hd).where.m[0] = local_48;
										if (p_Var8 <= p_Var4) {
											p_Var4 = (_CAR_DATA *)(p_Var5[-1].ai + 0x50);
										}
									}
								}
								if ((p_Var4->hd).where.m[1] == 0x7f) {
									*(uint *)(p_Var4->hd).where.m = tryToPark;
									*(undefined4 *)((p_Var4->hd).where.m + 2) = uVar7;
									*(int *)((p_Var4->hd).where.m + 4) = local_40;
									if (local_40 < 0) {
										local_40 = -local_40;
									}
									*(int *)((p_Var4->hd).where.m + 6) = local_3c;
									if (local_40 < 600000) {
										if (local_38 != 0) {
											*(int *)(cp->ai + 0x14) = (int)p_Var4 + (-0x1b0 - (int)cp) >> 4;
											*(bool *)(cp->ai + 0xf) = local_38 == 0x400;
										}
										(p_Var4->hd).where.m[1] = 1;
										return 1;
									}
								}
							}
							break;
						}
						if (p_Var8 <= p_Var4) {
							p_Var4 = (_CAR_DATA *)(oldNode[-1].ai + 0x50);
						}
						oldNode = p_Var4;
					} while (p_Var4 != *(_CAR_DATA **)(cp->ai + 0xf4));
				}
			}
		}
	}
	cp->ai[0xf9] = 3;
	cp->ai[0xc] = 7;
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ InitCivState(struct _CAR_DATA *cp /*$s1*/, char *extraData /*$s2*/)
 // line 1843, offset 0x000280d8
	/* begin block 1 */
		// Start line: 1844
		// Start offset: 0x000280D8
		// Variables:
	// 		struct CIV_STATE *cs; // $s0
	/* end block 1 */
	// End offset: 0x000282E8
	// End Line: 1887

	/* begin block 2 */
		// Start line: 4201
	/* end block 2 */
	// End Line: 4202

	/* begin block 3 */
		// Start line: 4217
	/* end block 3 */
	// End Line: 4218

int InitCivState(_CAR_DATA *cp, char *extraData)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uint uVar1;
	long lVar2;
	int iVar3;
	uint *puVar4;

	puVar4 = (uint *)cp->ai;
	cp->controlType = '\x02';
	if (extraData == (char *)0x0) {
		cp->ai[0xf9] = 0;
	}
	else {
		cp->ai[0xf9] = extraData[0xc];
	}
	if (cp->ai[0xf9] == 3) {
	LAB_000282b4:
		if (extraData == (char *)0x0) {
			cp->ai[0xc] = 0;
		}
		else {
			cp->ai[0xc] = extraData[10];
		}
		iVar3 = 1;
	}
	else {
		if (extraData == (char *)0x0) {
			uVar1 = GetSurfaceIndex((VECTOR *)(cp->hd).where.t);
			*puVar4 = uVar1;
		}
		else {
			*puVar4 = *(uint *)extraData;
		}
		uVar1 = *puVar4;
		if (-1 < (int)uVar1) {
			*(undefined4 *)(cp->ai + 4) = 0;
			*(undefined4 *)(cp->ai + 0xf4) = 0;
			*(undefined4 *)(cp->ai + 8) = 0;
			*(undefined4 *)(cp->ai + 0x14) = 0xffffffff;
			if (((((uVar1 & 0xffffe000) == 0) && ((int)(uVar1 & 0x1fff) < NumDriver2Straights)) ||
				(((uVar1 & 0xffffe000) == 0x4000 && ((int)(uVar1 & 0x1fff) < NumDriver2Curves)))) &&
				(uVar1 = *puVar4, -1 < (int)uVar1)) {
				if (cp->ai[0xf9] != 3) {
					if (((uVar1 & 0xffffe000) == 0) && ((int)(uVar1 & 0x1fff) < NumDriver2Straights)) {
						cp->ai[0xf8] = speedLimits[(uint)((byte)Driver2StraightsPtr[uVar1].NumLanes >> 4) & 3];
					}
					else {
						cp->ai[0xf8] = speedLimits
							[(uint)((byte)Driver2CurvesPtr[uVar1 - 0x4000].NumLanes >> 4) & 3];
					}
					InitNodeList(cp, extraData);
					*(byte **)(cp->ai + 0xf4) = cp->ai + 0x24;
					lVar2 = *(long *)(cp->ai + 0x30);
					(cp->hd).where.t[0] = *(long *)(cp->ai + 0x2c);
					(cp->hd).where.t[2] = lVar2;
					if (cp->ai[0xf9] != 3) {
						return 1;
					}
				}
				goto LAB_000282b4;
			}
		}
		iVar3 = 0;
		cp->ai[0xf9] = 3;
		cp->ai[0xc] = 7;
	}
	return iVar3;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ PingOutCar(struct _CAR_DATA *cp /*$s0*/)
 // line 1977, offset 0x0002cf80
	/* begin block 1 */
		// Start line: 7534
	/* end block 1 */
	// End Line: 7535

	/* begin block 2 */
		// Start line: 3954
	/* end block 2 */
	// End Line: 3955

	/* begin block 3 */
		// Start line: 7535
	/* end block 3 */
	// End Line: 7536

// [D]
int PingOutCar(_CAR_DATA *cp)
{
    int iVar1;
    uint *puVar2;
    
    testNumPingedOut = testNumPingedOut + 1;
    if (cp->controlType == 2) {
        if ((cp->controlFlags & 1) != 0) 
		{
            numCopCars = numCopCars + -1;
        }

        numCivCars = numCivCars + -1;
        if ((cp->ai.c.thrustState == 3) && (cp->ai.c.ctrlState == 5)) 
            numParkedCars = numParkedCars + -1;
    }
    else {
        if ((PingOutCivsOnly != 0) &&
           (iVar1 = valid_region((cp->hd).where.t[0],(cp->hd).where.t[2]), iVar1 != 0)) {
            return 0;
        }
    }
    puVar2 = (uint *)cp->inform;
    if (puVar2 != NULL) {
        *puVar2 = *puVar2 ^ 0x40000000;
    }
    ClearMem((char *)cp,sizeof(_CAR_DATA));
    cp->controlType = 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ PingOutAllSpecialCivCars()
 // line 2016, offset 0x000282e8
	/* begin block 1 */
		// Start line: 2018
		// Start offset: 0x000282E8
		// Variables:
	// 		struct _CAR_DATA *lcp; // $s0

		/* begin block 1.1 */
			// Start line: 2017
			// Start offset: 0x00028348
			// Variables:
		// 		struct _CAR_DATA *cp; // $s0
		/* end block 1.1 */
		// End offset: 0x000283E4
		// End Line: 2017
	/* end block 1 */
	// End offset: 0x0002840C
	// End Line: 2025

	/* begin block 2 */
		// Start line: 4449
	/* end block 2 */
	// End Line: 4450

	/* begin block 3 */
		// Start line: 4579
	/* end block 3 */
	// End Line: 4580

	/* begin block 4 */
		// Start line: 4580
	/* end block 4 */
	// End Line: 4581

	/* begin block 5 */
		// Start line: 4581
	/* end block 5 */
	// End Line: 4582

/* WARNING: Unknown calling convention yet parameter storage is locked */

int PingOutAllSpecialCivCars(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uint *puVar1;
	_CAR_DATA *mem;

	mem = car_data;
	do {
		if ((mem->controlType == '\x02') && (4 < MissionHeader->residentModels[(byte)(mem->ap).model]))
		{
			testNumPingedOut = testNumPingedOut + 1;
			if ((mem->controlFlags & 1) != 0) {
				numCopCars = numCopCars + -1;
			}
			numCivCars = numCivCars + -1;
			if ((mem->ai[0xf9] == 3) && (mem->ai[0xc] == 5)) {
				numParkedCars = numParkedCars + -1;
			}
			puVar1 = (uint *)mem->inform;
			if (puVar1 != (uint *)0x0) {
				*puVar1 = *puVar1 ^ 0x40000000;
			}
			ClearMem((char *)mem, 0x29c);
			mem->controlType = '\0';
		}
		mem = mem + 1;
	} while (mem < car_data + 0x14);
	return 1;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ PingOutAllCivCarsAndCopCars()
 // line 2028, offset 0x0002840c
	/* begin block 1 */
		// Start line: 2030
		// Start offset: 0x0002840C
		// Variables:
	// 		struct _CAR_DATA *lcp; // $s0

		/* begin block 1.1 */
			// Start line: 2029
			// Start offset: 0x0002844C
			// Variables:
		// 		struct _CAR_DATA *cp; // $s0
		/* end block 1.1 */
		// End offset: 0x0002852C
		// End Line: 2029
	/* end block 1 */
	// End offset: 0x00028554
	// End Line: 2037

	/* begin block 2 */
		// Start line: 4601
	/* end block 2 */
	// End Line: 4602

	/* begin block 3 */
		// Start line: 4605
	/* end block 3 */
	// End Line: 4606

	/* begin block 4 */
		// Start line: 4606
	/* end block 4 */
	// End Line: 4607

	/* begin block 5 */
		// Start line: 4607
	/* end block 5 */
	// End Line: 4608

/* WARNING: Unknown calling convention yet parameter storage is locked */

int PingOutAllCivCarsAndCopCars(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	uint *puVar2;
	_CAR_DATA *mem;

	mem = car_data;
	do {
		if ((uint)mem->controlType - 2 < 2) {
			testNumPingedOut = testNumPingedOut + 1;
			if (mem->controlType == 2) {
				if ((mem->controlFlags & 1) != 0) {
					numCopCars = numCopCars + -1;
				}
				numCivCars = numCivCars + -1;
				if ((mem->ai[0xf9] == 3) && (mem->ai[0xc] == 5)) {
					numParkedCars = numParkedCars + -1;
				}
			}
			else {
				if ((PingOutCivsOnly != '\0') &&
					(iVar1 = valid_region((mem->hd).where.t[0], (mem->hd).where.t[2]), iVar1 != 0))
					goto LAB_0002852c;
			}
			puVar2 = (uint *)mem->inform;
			if (puVar2 != (uint *)0x0) {
				*puVar2 = *puVar2 ^ 0x40000000;
			}
			ClearMem((char *)mem, 0x29c);
			mem->controlType = '\0';
		}
	LAB_0002852c:
		mem = mem + 1;
		if ((_CAR_DATA *)((int)&car_data[0x13].lastPad + 3U) < mem) {
			return 1;
		}
	} while (true);*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckPingOut(struct _CAR_DATA *cp /*$s0*/)
 // line 2050, offset 0x00028554
	/* begin block 1 */
		// Start line: 2051
		// Start offset: 0x00028554
		// Variables:
	// 		int dx; // $a0
	// 		int dz; // $v1
	// 		int dist; // $s1

		/* begin block 1.1 */
			// Start line: 2051
			// Start offset: 0x000285B8
			// Variables:
		// 		struct _CAR_DATA *cp; // $s0
		/* end block 1.1 */
		// End offset: 0x00028694
		// End Line: 2051
	/* end block 1 */
	// End offset: 0x000286E0
	// End Line: 2081

	/* begin block 2 */
		// Start line: 4648
	/* end block 2 */
	// End Line: 4649

	/* begin block 3 */
		// Start line: 4651
	/* end block 3 */
	// End Line: 4652

	/* begin block 4 */
		// Start line: 4656
	/* end block 4 */
	// End Line: 4657

// [D]
int CheckPingOut(_CAR_DATA *cp)
{
	int iVar1;
	int iVar2;
	uint *puVar3;
	int z;
	int x;

	x = (cp->hd).where.t[0];
	iVar2 = (player[0].spoolXZ)->vx - x;
	z = (cp->hd).where.t[2];
	iVar1 = (player[0].spoolXZ)->vz - z;
	iVar1 = iVar2 * iVar2 + iVar1 * iVar1;

	if (24000 * 24000 < iVar1)
	{
		testNumPingedOut = testNumPingedOut + 1;
		if (cp->controlType == 2)
		{
			if ((cp->controlFlags & 1) != 0) 
			{
				numCopCars = numCopCars + -1;
			}
			numCivCars = numCivCars + -1;

			if ((cp->ai.c.thrustState == 3) && (cp->ai.c.ctrlState == 5)) 
			{
				numParkedCars = numParkedCars + -1;
			}
		}
		else {
			if ((PingOutCivsOnly != '\0') && (iVar2 = valid_region(x, z), iVar2 != 0))
				goto LAB_00028694;
		}
		puVar3 = (uint *)cp->inform;

		if (puVar3 != NULL) 
			*puVar3 = *puVar3 ^ 0x40000000;

		ClearMem((char *)cp, sizeof(_CAR_DATA));
		cp->controlType = 0;
	}
LAB_00028694:
	if ((requestStationaryCivCar == 1) && (distFurthestCivCarSq < iVar1)) {
		furthestCivID = cp->id;
		distFurthestCivCarSq = iVar1;
	}
	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetUpTrafficLightPhase()
 // line 2084, offset 0x0002d220
	/* begin block 1 */
		// Start line: 7728
	/* end block 1 */
	// End Line: 7729

	/* begin block 2 */
		// Start line: 8898
	/* end block 2 */
	// End Line: 8899

	/* begin block 3 */
		// Start line: 8899
	/* end block 3 */
	// End Line: 8900

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SetUpTrafficLightPhase(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	iVar1 = TrafficLightCycle(0);
	junctionLightsPhase = (char)iVar1;
	iVar1 = TrafficLightCycle(1);
	CHAR_00h_000aab91 = (char)iVar1;
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ TrafficLightCycle(int exit /*$a0*/)
 // line 2116, offset 0x0002cf18
	/* begin block 1 */
		// Start line: 2117
		// Start offset: 0x0002CF18
		// Variables:
	// 		int timeCnt; // $v1
	/* end block 1 */
	// End offset: 0x0002CF80
	// End Line: 2141

	/* begin block 2 */
		// Start line: 4232
	/* end block 2 */
	// End Line: 4233

	/* begin block 3 */
		// Start line: 7647
	/* end block 3 */
	// End Line: 7648

int TrafficLightCycle(int exit)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	int iVar2;
	uint uVar3;

	uVar3 = CameraCnt - frameStart & 0x1ff;
	if ((exit == 0) || (exit == 2)) {
		bVar1 = uVar3 < 0x100;
		uVar3 = uVar3 - 0x100;
		if (bVar1) {
			return 1;
		}
		bVar1 = (int)uVar3 < 0x96;
	}
	else {
		bVar1 = uVar3 < 0x96;
		if (0xff < uVar3) {
			return 1;
		}
	}
	iVar2 = 3;
	if ((!bVar1) && (iVar2 = 2, 199 < (int)uVar3)) {
		return 1;
	}
	return iVar2;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitCivCars()
 // line 2144, offset 0x0002cda4
	/* begin block 1 */
		// Start line: 2146
		// Start offset: 0x0002CDA4
	/* end block 1 */
	// End offset: 0x0002CE10
	// End Line: 2157

	/* begin block 2 */
		// Start line: 4928
	/* end block 2 */
	// End Line: 4929

	/* begin block 3 */
		// Start line: 4288
	/* end block 3 */
	// End Line: 4289

	/* begin block 4 */
		// Start line: 7073
	/* end block 4 */
	// End Line: 7074

	/* begin block 5 */
		// Start line: 7075
	/* end block 5 */
	// End Line: 7076

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitCivCars(void)
{
	PingBufferPos = 0;
	cookieCount = 0;
	requestRoadblock = 0;
	makeLimoPullOver = 0;
	frameStart = CameraCnt;
	roadblockDelay = (&roadblockDelayDiff)[gCopDifficultyLevel] + (Random2(0) & 0xff);
	PingOutCivsOnly = 0;
	roadblockCount = roadblockDelay;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CreateCivCarWotDrivesABitThenStops(int direction /*$s5*/, long (*startPos)[4] /*$s2*/, long (*stopPos)[4] /*$a2*/, unsigned char internalModel /*$s4*/, int palette /*stack 16*/)
 // line 2176, offset 0x000286e0
	/* begin block 1 */
		// Start line: 2177
		// Start offset: 0x000286E0
		// Variables:
	// 		struct _EXTRA_CIV_DATA civDat; // stack offset -56
	// 		struct _CAR_DATA *newCar; // $s1
	// 		struct CIV_ROUTE_ENTRY *stopNode; // $a0
	// 		struct CIV_ROUTE_ENTRY *spareNode; // $a1

		/* begin block 1.1 */
			// Start line: 2177
			// Start offset: 0x000286E0

			/* begin block 1.1.1 */
				// Start line: 2177
				// Start offset: 0x000286E0
				// Variables:
			// 		char *slot; // $v1
			// 		struct _CAR_DATA *carCnt; // $a0
			/* end block 1.1.1 */
			// End offset: 0x00028774
			// End Line: 2184
		/* end block 1.1 */
		// End offset: 0x00028774
		// End Line: 2184
	/* end block 1 */
	// End offset: 0x00028960
	// End Line: 2229

	/* begin block 2 */
		// Start line: 4814
	/* end block 2 */
	// End Line: 4815

	/* begin block 3 */
		// Start line: 4910
	/* end block 3 */
	// End Line: 4911

int CreateCivCarWotDrivesABitThenStops(int direction, long(*startPos)[4], long(*stopPos)[4], unsigned char internalModel, int palette)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	uint uVar2;
	uchar *puVar3;
	long lVar4;
	int iVar5;
	_CAR_DATA *cp;
	CAR_COSMETICS *pCVar6;
	short *psVar7;
	short *psVar8;
	undefined2 uVar9;
	int iVar10;
	char acStack56[8];
	undefined2 local_30;
	undefined2 local_2e;
	undefined4 local_2c;
	undefined local_28;
	undefined local_27;

	iVar5 = (int)((int)stopPos - (int)startPos) >> 2;
	ratan2(iVar5, iVar5);
	cp = car_data;
	puVar3 = reservedSlots;
	do {
		if ((cp->controlType == '\0') && (*puVar3 == '\0')) goto LAB_00028774;
		cp = cp + 1;
		puVar3 = puVar3 + 1;
	} while (cp < car_data + 0x13);
	cp = (_CAR_DATA *)0x0;
LAB_00028774:
	if (cp == (_CAR_DATA *)0x0) {
		uVar2 = 0xffffffff;
	}
	else {
		local_2c = 0;
		local_2e = 8;
		local_27 = 0;
		local_28 = (undefined)palette;
		uVar9 = (undefined2)direction;
		local_30 = uVar9;
		InitCar(cp, direction, startPos, '\x02', (uint)internalModel, 0, acStack56);
		cp->ai[0xc] = 8;
		psVar8 = rcossin_tbl + (direction & 0xfffU) * 2;
		cp->ai[0xf8] = (byte)EVENT_CAR_SPEED;
		iVar5 = EVENT_CAR_SPEED;
		iVar10 = EVENT_CAR_SPEED * *psVar8;
		psVar7 = rcossin_tbl + (direction & 0xfffU) * 2 + 1;
		*(undefined4 *)(cp->st + 0x20) = 0;
		*(int *)(cp->st + 0x1c) = iVar10;
		iVar10 = DistanceTriggerCarMoves;
		pCVar6 = (cp->ap).carCos;
		*(int *)(cp->st + 0x24) = iVar5 * *psVar7;
		iVar1 = iVar10 + (int)(pCVar6->colBox).vz * -3;
		if (iVar1 == 0) {
			trap(7);
		}
		*(int *)(cp->ai + 0x20) = (iVar5 << 0xc) / iVar1;
		*(long *)(cp->ai + 0x2c) = (*startPos)[0];
		lVar4 = (*startPos)[2];
		*(byte **)(cp->ai + 8) = cp->ai + 0x34;
		*(long *)(cp->ai + 0x30) = lVar4;
		*(undefined2 *)(cp->ai + 0x36) = 1;
		*(undefined2 *)(cp->ai + 0x34) = uVar9;
		*(undefined4 *)(cp->ai + 0x38) = 0;
		*(long *)(cp->ai + 0x3c) = (*startPos)[0] + (iVar10 * *psVar8 + 0x800 >> 0xc);
		*(long *)(cp->ai + 0x40) = (*startPos)[2] + (iVar10 * *psVar7 + 0x800 >> 0xc);
		*(undefined2 *)(cp->ai + 0x46) = 1;
		*(undefined2 *)(cp->ai + 0x44) = uVar9;
		*(undefined4 *)(cp->ai + 0x48) = 0;
		*(long *)(cp->ai + 0x4c) = (*startPos)[0] + (iVar10 * (int)*psVar8 * 3 + 0x800 >> 0xc);
		numCivCars = numCivCars + 1;
		*(long *)(cp->ai + 0x50) = (*startPos)[0] + (iVar10 * (int)*psVar7 * 3 + 0x800 >> 0xc);
		uVar2 = (uint)(byte)cp->id;
	}
	return uVar2;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CreateStationaryCivCar(int direction /*$t4*/, long orientX /*$s2*/, long orientZ /*$s1*/, long (*startPos)[4] /*$a2*/, int externalModel /*stack 16*/, int palette /*stack 20*/, int controlFlags /*stack 24*/)
 // line 2248, offset 0x00028960
	/* begin block 1 */
		// Start line: 2249
		// Start offset: 0x00028960
		// Variables:
	// 		struct _EXTRA_CIV_DATA civDat; // stack offset -72
	// 		struct _CAR_DATA *newCar; // $s0
	// 		long tmpRes[4]; // stack offset -48
	// 		long tmpQ[4]; // stack offset -32

		/* begin block 1.1 */
			// Start line: 2249
			// Start offset: 0x00028A1C

			/* begin block 1.1.1 */
				// Start line: 2249
				// Start offset: 0x00028A1C
				// Variables:
			// 		char *slot; // $v1
			// 		struct _CAR_DATA *carCnt; // $a0
			/* end block 1.1.1 */
			// End offset: 0x00028A68
			// End Line: 2249
		/* end block 1.1 */
		// End offset: 0x00028A68
		// End Line: 2249
	/* end block 1 */
	// End offset: 0x00028DB4
	// End Line: 2289

	/* begin block 2 */
		// Start line: 5111
	/* end block 2 */
	// End Line: 5112

	/* begin block 3 */
		// Start line: 5131
	/* end block 3 */
	// End Line: 5132

// [D]
int CreateStationaryCivCar(int direction, long orientX, long orientZ, long(*startPos)[4], int externalModel, int palette, int controlFlags)
{
	unsigned char *puVar1;
	int iVar2;
	_CAR_DATA *cp;
	_CAR_DATA *carCnt;
	int iVar3;
	int iVar4;
	int iVar5;
	uint uVar6;
	int iVar7;
	int model;
	_EXTRA_CIV_DATA civDat;
	long tempRes[4];
	long tmpQ[4];

	if (MissionHeader->residentModels[0] == externalModel)
		model = 0;
	else if (MissionHeader->residentModels[1] == externalModel)
		model = 1;
	else if (MissionHeader->residentModels[2] == externalModel)
		model = 2;
	else if (MissionHeader->residentModels[3] == externalModel)
		model = 3;
	else if (MissionHeader->residentModels[4] == externalModel)
		model = 4;

	if (model != 0xff) 
	{
		if (4 < externalModel && specModelValid == 0) 
		{
			return -1;
		}

		cp = NULL;
		carCnt = car_data;
		puVar1 = reservedSlots;

		if (true) 
		{
			do {
				if ((carCnt->controlType == 0) && (*puVar1 == 0))
				{
					cp = carCnt;
					break;
				}

				carCnt++;
				puVar1++;
			} while (carCnt < car_data + 19);
		}

		if (cp != NULL) 
		{
			civDat.thrustState = 3;
			civDat.ctrlState = 7;

			if ((controlFlags & 1U) != 0) 
			{
				requestCopCar = 0;
				numCopCars++;
				cop_respawn_timer = gCopRespawnTime;
			}

			civDat.controlFlags = controlFlags | 4;

			if ((gCurrentMissionNumber != 0x20) && (externalModel == 0))
				civDat.controlFlags = controlFlags | 6;

			civDat.palette = palette;
			civDat.angle = direction;

			InitCar(cp, direction, startPos,  2, model, 0, (char *)&civDat);

			uVar6 = (orientZ - (orientZ >> 0x1f)) * 2 & 0x3ffc;
			iVar7 = (int)*(short *)((int)rcossin_tbl + uVar6);
			iVar4 = (int)*(short *)((int)rcossin_tbl + uVar6 + 2);

			tmpQ[0] = (cp->st.n.orientation[1] * iVar7 + cp->st.n.orientation[0] * iVar4) / 4096;
			tmpQ[1] = (cp->st.n.orientation[1] * iVar4 - cp->st.n.orientation[0] * iVar7) / 4096;
			tmpQ[2] = (cp->st.n.orientation[3] * iVar7 + cp->st.n.orientation[2] * iVar4) / 4096;
			tmpQ[3] = (cp->st.n.orientation[3] * iVar4 - cp->st.n.orientation[2] * iVar7) / 4096;

			uVar6 = (orientX - (orientX >> 0x1f)) * 2 & 0x3ffc;
			iVar5 = (int)*(short *)((int)rcossin_tbl + uVar6);
			iVar7 = (int)*(short *)((int)rcossin_tbl + uVar6 + 2);

			cp->st.n.orientation[0] = (tmpQ[3] * iVar5 + tmpQ[0] * iVar7) / 4096;
			cp->st.n.orientation[1] = (tmpQ[2] * iVar5 + tmpQ[1] * iVar7) / 4096;
			cp->st.n.orientation[2] = (tmpQ[2] * iVar7 - tmpQ[1] * iVar5) / 4096;
			cp->st.n.orientation[3] = (tmpQ[3] * iVar7 - tmpQ[0] * iVar5) / 4096;

			numCivCars++;

			return cp->id;
		}
	}

	return -1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ PingInCivCar(int minPingInDist /*stack 0*/)
 // line 2323, offset 0x00028db4
	/* begin block 1 */
		// Start line: 2324
		// Start offset: 0x00028DB4
		// Variables:
	// 		struct _EXTRA_CIV_DATA civDat; // stack offset -128
	// 		int dir; // stack offset -52
	// 		int distAlongSegment; // $fp
	// 		int lane; // $s7
	// 		struct _CAR_DATA *newCar; // $s1
	// 		struct DRIVER2_STRAIGHT *str; // $s6
	// 		struct DRIVER2_CURVE *crv; // $s5
	// 		unsigned char cookieCountStart; // $s4
	// 		int curveLength; // stack offset -48
	// 		unsigned char model; // $s4
	// 		unsigned char possibleLanes[12]; // stack offset -104
	// 		unsigned char carDistLanes[15]; // stack offset -88
	// 		char numPossibleLanes; // $s0
	// 		int lbody; // $s3

		/* begin block 1.1 */
			// Start line: 2324
			// Start offset: 0x00028EEC

			/* begin block 1.1.1 */
				// Start line: 2324
				// Start offset: 0x00028EEC
				// Variables:
			// 		char *slot; // $a1
			// 		struct _CAR_DATA *carCnt; // $a0
			/* end block 1.1.1 */
			// End offset: 0x00028F40
			// End Line: 2324
		/* end block 1.1 */
		// End offset: 0x00028F40
		// End Line: 2324

		/* begin block 1.2 */
			// Start line: 2393
			// Start offset: 0x00029000
			// Variables:
		// 		char newCarId; // $v1

			/* begin block 1.2.1 */
				// Start line: 2324
				// Start offset: 0x00029058
				// Variables:
			// 		struct _CAR_DATA *cp; // $s1
			/* end block 1.2.1 */
			// End offset: 0x00029140
			// End Line: 2324
		/* end block 1.2 */
		// End offset: 0x000292A4
		// End Line: 2402

		/* begin block 1.3 */
			// Start line: 2462
			// Start offset: 0x00029620
			// Variables:
		// 		char frog; // $a0
		// 		char numLanes; // $a1
		/* end block 1.3 */
		// End offset: 0x00029760
		// End Line: 2462

		/* begin block 1.4 */
			// Start line: 2471
			// Start offset: 0x00029860
			// Variables:
		// 		char frog; // $a0
		// 		char numLanes; // $a1
		/* end block 1.4 */
		// End offset: 0x00029964
		// End Line: 2471

		/* begin block 1.5 */
			// Start line: 2528
			// Start offset: 0x00029C48
			// Variables:
		// 		int externalModel; // $v0

			/* begin block 1.5.1 */
				// Start line: 2535
				// Start offset: 0x00029CC4
				// Variables:
			// 		unsigned char palette; // $v0
			/* end block 1.5.1 */
			// End offset: 0x00029D20
			// End Line: 2539
		/* end block 1.5 */
		// End offset: 0x00029D5C
		// End Line: 2544

		/* begin block 1.6 */
			// Start line: 2550
			// Start offset: 0x00029DB8
			// Variables:
		// 		int theta; // $s0
		// 		int minDistAlong; // $s2
		/* end block 1.6 */
		// End offset: 0x00029F10
		// End Line: 2563

		/* begin block 1.7 */
			// Start line: 2567
			// Start offset: 0x00029F58
			// Variables:
		// 		int minAngle; // $a1
		/* end block 1.7 */
		// End offset: 0x0002A090
		// End Line: 2578

		/* begin block 1.8 */
			// Start line: 2593
			// Start offset: 0x0002A0E8
			// Variables:
		// 		long pos[4]; // stack offset -72
		// 		unsigned int distSq; // stack offset -56

			/* begin block 1.8.1 */
				// Start line: 2593
				// Start offset: 0x0002A0E8
				// Variables:
			// 		int *distToCarSq; // $t2

				/* begin block 1.8.1.1 */
					// Start line: 2593
					// Start offset: 0x0002A0E8
					// Variables:
				// 		int dz; // $v1
				// 		int dx; // $a0
				// 		int distSq; // $v0
				// 		unsigned int retDistSq; // $a2
				// 		struct _CAR_DATA *lcp; // $a1
				/* end block 1.8.1.1 */
				// End offset: 0x0002A228
				// End Line: 2601
			/* end block 1.8.1 */
			// End offset: 0x0002A228
			// End Line: 2601

			/* begin block 1.8.2 */
				// Start line: 2611
				// Start offset: 0x0002A240
				// Variables:
			// 		int x; // $t2
			// 		int y; // $a2
			// 		int z; // $t1
			// 		unsigned int distSq; // $a3

				/* begin block 1.8.2.1 */
					// Start line: 2611
					// Start offset: 0x0002A240
					// Variables:
				// 		int dz; // $v1
				// 		int dx; // $a0
				// 		int ret; // $t0
				// 		struct _CAR_DATA *lcp; // $a1
				/* end block 1.8.2.1 */
				// End offset: 0x0002A340
				// End Line: 2611
			/* end block 1.8.2 */
			// End offset: 0x0002A340
			// End Line: 2611
		/* end block 1.8 */
		// End offset: 0x0002A37C
		// End Line: 2622
	/* end block 1 */
	// End offset: 0x0002A4C4
	// End Line: 2656

	/* begin block 2 */
		// Start line: 5271
	/* end block 2 */
	// End Line: 5272

	/* begin block 3 */
		// Start line: 5306
	/* end block 3 */
	// End Line: 5307

	/* begin block 4 */
		// Start line: 5308
	/* end block 4 */
	// End Line: 5309

/* WARNING: Type propagation algorithm not settling */


VECTOR baseLoc;
VECTOR randomLoc;
int dx = 0; // offset 0xAAB40
int dy = 0; // offset 0xAAB44
int dz = 0; // offset 0xAAB48

// [D] [A] - some register is not properly decompiled
int PingInCivCar(int minPingInDist)
{
	unsigned char bVar1;
	short sVar2;
	ushort uVar3;
	bool bVar4;
	char cVar5;
	int iVar6;
	uint model;
	int iVar7;
	long lVar8;
	long lVar9;
	uint uVar10;
	int iVar11;
	int iVar12;
	_CAR_DATA *p_Var13;
	uint *puVar14;
	unsigned char *puVar15;
	unsigned char bVar16;
	_CAR_DATA *cp;
	uint uVar17;
	DRIVER2_CURVE *curve;
	DRIVER2_STRAIGHT *straight;
	uint uVar18;
	_EXTRA_CIV_DATA civDat;
	unsigned char possibleLanes[12];
	unsigned char carDistLanes[15];
	long pos[4];
	int distSq;
	uint local_34;
	int local_30;
	int local_2c;

	civDat.distAlongSegment = 0xfffffffb;
	uVar18 = 0xffffffff;
	straight = NULL;
	curve = NULL;
	local_34 = 0xffffff;
	local_2c = 0;
	PingOutCivsOnly = 1;
	if (((requestCopCar == 0) && (numParkedCars < maxParkedCars)) &&
		((gCurrentMissionNumber != 0x21 || (numCivCars != 0)))) {
		local_2c = 1;
	}
	playerNum = 0;
	if (NumPlayers == 2) {
		playerNum = CameraCnt & 1;
	}
	if ((MissionHeader->type & 4U) != 0) {
		PingOutCivsOnly = 1;
		return 0;
	}
	if (gInGameCutsceneActive != 0) {
		PingOutCivsOnly = 1;
		return 0;
	}
	if ((maxCivCars + -1 <= numCivCars) && (gInGameChaseActive == 0)) {
		PingOutCivsOnly = 1;
		return 0;
	}
	if (1 < NumPlayers) {
		PingOutCivsOnly = 1;
		return 0;
	}
	p_Var13 = car_data;
	puVar15 = reservedSlots;
	cp = NULL;

	if (true) 
	{
		do {
			if ((p_Var13->controlType == 0) && (cp = p_Var13, *puVar15 == 0))
				goto LAB_00028f40;
			p_Var13 = p_Var13 + 1;
			puVar15 = puVar15 + 1;
		} while (p_Var13 < car_data + 19);
		cp = NULL;
	}

LAB_00028f40:
	if (cp == NULL) {
		PingOutCivsOnly = 1;
		return 0;
	}
	ClearMem((char *)&civDat, 0x14);
	baseLoc.vx = (player[playerNum].spoolXZ)->vx;
	baseLoc.vz = (player[playerNum].spoolXZ)->vz;

	if ((requestCopCar == 0) && (0x2b < cookieCount)) 
	{
		cookieCount = cookieCount-0x19;
	}

	cVar5 = cookieCount;

	if ((useStoredPings == 0) || (gInGameChaseActive == 0)) 
	{
		do {
			if (requestCopCar == 0) 
			{
				if (cookieCount < 0x2b)
					goto LAB_000294b0;
				cookieCount = 0;
			}
			else {
				if (cookieCount < 0x37)
				{
				LAB_000294b0:
					cookieCount = cookieCount + 1;
				}
				else
				{
					cookieCount = 0;
				}
			}
			if (cookieCount == cVar5) break;
			if (requestCopCar == 0) {
				model = (int)(cookieCount * 0x1000) / 0x2c;
			}
			else {
				model = (int)(cookieCount * 0x1000) / 0x38;
			}
			if (requestCopCar == 0) {
				iVar6 = (int)rcossin_tbl[(model & 0xfff) * 2] << 3;
			}
			else {
				iVar6 = (int)rcossin_tbl[(model & 0xfff) * 2] * 10;
			}
			randomLoc.vx = baseLoc.vx + (iVar6 + 0x800 >> 0xc) * 0x800;
			if (requestCopCar == 0) {
				model = (int)(cookieCount * 0x1000) / 0x2c;
			}
			else {
				model = (int)(cookieCount * 0x1000) / 0x38;
			}
			if (requestCopCar == 0) {
				iVar6 = (int)rcossin_tbl[(model & 0xfff) * 2 + 1] << 3;
			}
			else {
				iVar6 = (int)rcossin_tbl[(model & 0xfff) * 2 + 1] * 10;
			}
			randomLoc.vz = baseLoc.vz + (iVar6 + 0x800 >> 0xc) * 0x800;
			roadSeg = RoadInCell(&randomLoc);
		} while (((((roadSeg & 0xffffe000U) != 0) ||
			(NumDriver2Straights <= (int)(roadSeg & 0x1fffU))) &&
			(((roadSeg & 0xffffe000U) != 0x4000 ||
			(NumDriver2Curves <= (int)(roadSeg & 0x1fffU))))) || (roadSeg < 0));
	}
	else {
		cVar5 = GetPingInfo(&cookieCount);
		iVar6 = cVar5;
		if (iVar6 == -1) {
			return 0;
		}
		if (0x13 < iVar6) {
			return 0;
		}
		cp = car_data + iVar6;
		if (car_data[iVar6].controlType != 0) 
		{
			testNumPingedOut = testNumPingedOut + 1;
			if (car_data[iVar6].controlType == 2)
			{
				if ((car_data[iVar6].controlFlags & 1) != 0)
				{
					numCopCars = numCopCars + -1;
				}
				numCivCars = numCivCars + -1;
				if (car_data[iVar6].ai.c.thrustState == 3 && car_data[iVar6].ai.c.ctrlState == 5)
				{
					numParkedCars = numParkedCars + -1;
				}
			LAB_0002910c:
				puVar14 = (uint *)car_data[iVar6].inform;
				if (puVar14 != NULL) 
				{
					*puVar14 = *puVar14 ^ 0x40000000;
				}
				ClearMem((char *)cp, 0x29c);
				car_data[iVar6].controlType = 0;
				bVar4 = true;
			}
			else 
			{
				if (PingOutCivsOnly == 0)
					goto LAB_0002910c;

				iVar7 = valid_region(car_data[iVar6].hd.where.t[0], car_data[iVar6].hd.where.t[2]);
				bVar4 = false;

				if (iVar7 == 0)
					goto LAB_0002910c;
			}
			if (!bVar4) {
				return 0;
			}
		}
		if (requestCopCar == 0) {
			model = (int)(cookieCount * 0x1000) / 0x2c;
		}
		else {
			model = (int)(cookieCount * 0x1000) / 0x38;
		}

		if (requestCopCar == 0) {
			iVar6 = (int)rcossin_tbl[(model & 0xfff) * 2] << 3;
		}
		else {
			iVar6 = (int)rcossin_tbl[(model & 0xfff) * 2] * 10;
		}

		randomLoc.vx = baseLoc.vx + (iVar6 + 0x800 >> 0xc) * 0x800;

		if (requestCopCar == 0) {
			model = (int)(cookieCount * 0x1000) / 0x2c;
		}
		else {
			model = (int)(cookieCount * 0x1000) / 0x38;
		}

		if (requestCopCar == 0) {
			iVar6 = (int)rcossin_tbl[(model & 0xfff) * 2 + 1] << 3;
		}
		else {
			iVar6 = (int)rcossin_tbl[(model & 0xfff) * 2 + 1] * 10;
		}

		randomLoc.vz = baseLoc.vz + (iVar6 + 0x800 >> 0xc) * 0x800;
		roadSeg = RoadInCell(&randomLoc);
	}
	if (((((roadSeg & 0xffffe000U) != 0) || (NumDriver2Straights <= (int)(roadSeg & 0x1fffU))) &&
		(((roadSeg & 0xffffe000U) != 0x4000 || (NumDriver2Curves <= (int)(roadSeg & 0x1fffU))))) ||
		(roadSeg < 0)) 
	{
		civPingTest.OffRoad = civPingTest.OffRoad + 1;
		return 0;
	}

	if (((((roadSeg & 0xffffe000U) != 0) || (NumDriver2Straights <= (int)(roadSeg & 0x1fffU))) &&
		(((roadSeg & 0xffffe000U) != 0x4000 || (NumDriver2Curves <= (int)(roadSeg & 0x1fffU))))) ||
		(roadSeg < 0)) 
		goto LAB_0002a368;

	ClearMem((char *)carDistLanes, 0xf);

	if ((((roadSeg & 0xffffe000U) == 0) && ((int)(roadSeg & 0x1fffU) < NumDriver2Straights)) &&
		(-1 < roadSeg)) {
		straight = Driver2StraightsPtr + roadSeg;
		if ((straight->NumLanes & 0xfU) == 0) goto LAB_0002a368;
		if ((gCurrentMissionNumber == 0x21) && (minPingInDist == 0x29a)) {
			uVar18 = 1;
		}
		else {
			uVar18 = 0;
			model = (straight->NumLanes & 0xf) * 2;
			uVar17 = 0;
			if ((straight->NumLanes & 0xfU) != 0)
			{
				do {
					if (((((uVar18 == 0) || (model - 1 == uVar18)) && (local_2c != 0)) &&
						(((uVar18 == 0 && ((straight->NumLanes & 0x40U) != 0)) ||
						((((uint)straight->NumLanes & 0xffffff0f) * 2 - 1 == uVar18 &&
							((straight->NumLanes & 0x80U) != 0)))))) ||
							(((((int)(uint)straight->AILanes >> (uVar18 >> 1 & 0x1f) & 1U) != 0 &&
						((uVar18 != 0 || ((straight->NumLanes & 0x40U) == 0)))) &&
								((((uint)straight->NumLanes & 0xffffff0f) * 2 - 1 != uVar18 ||
								((straight->NumLanes & 0x80U) == 0)))))) 
					{
						possibleLanes[uVar17] = uVar18;
						uVar17 = uVar17 + 1 & 0xff;
					}

					uVar18 = uVar18 + 1 & 0xff;
				} while (uVar18 < model);
			}
			if (uVar17 == 0) {
				return 0;
			}
			lVar8 = Random2(0);
			if (uVar17 == 0)
				trap(7);

			uVar18 = (uint)possibleLanes[(lVar8 >> 8) % uVar17];
			cp->ai.c.currentLane = possibleLanes[(lVar8 >> 8) % uVar17];
		}
		if (((uVar18 == 0) && ((straight->NumLanes & 0x40U) != 0)) ||
			((((uint)straight->NumLanes & 0xf) * 2 - 1 == uVar18 &&
			((straight->NumLanes & 0x80U) != 0)))) 
		{
			civDat.thrustState = 3;
			civDat.ctrlState = 7;
			if (((int)(uint)straight->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) != 0) 
			{
				civDat.ctrlState = 5;
			}
		}
		else {
			if (((int)(uint)straight->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) == 0) 
			{
			LAB_00029a28:
				civPingTest.NotDrivable = civPingTest.NotDrivable + 1;
				return 0;
			}
			civDat.thrustState = 0;
			civDat.ctrlState = 0;
		}
	}
	else 
	{
		if ((((roadSeg & 0xffffe000U) == 0x4000) && ((int)(roadSeg & 0x1fffU) < NumDriver2Curves)) && (-1 < roadSeg)) 
		{
			curve = Driver2CurvesPtr + roadSeg-0x4000;
			bVar16 = curve->NumLanes;
			uVar18 = 0;
			if ((bVar16 & 0xf) == 0) goto LAB_0002a368;
			model = ((uint)bVar16 & 0xf) * 2;
			uVar17 = 0;
			if ((bVar16 & 0xf) != 0) {
				do {
					if ((((uVar18 == 0) || (model - 1 == uVar18)) &&
						((local_2c != 0 &&
						(((uVar18 == 0 && ((curve->NumLanes & 0x40U) != 0)) ||
							((((uint)curve->NumLanes & 0xffffff0f) * 2 - 1 == uVar18 &&
							((curve->NumLanes & 0x80U) != 0)))))))) ||
								((((int)(uint)curve->AILanes >> (uVar18 >> 1 & 0x1f) & 1U) != 0 &&
						(((uVar18 != 0 || ((curve->NumLanes & 0x40U) == 0)) &&
									((((uint)curve->NumLanes & 0xffffff0f) * 2 - 1 != uVar18 ||
							((curve->NumLanes & 0x80U) == 0)))))))) 
					{
						possibleLanes[uVar17] = uVar18;
						uVar17 = uVar17 + 1 & 0xff;
					}
					uVar18 = uVar18 + 1 & 0xff;
				} while (uVar18 < model);
			}

			if (uVar17 == 0) 
				return 0;

			lVar8 = Random2(0);

			if (uVar17 == 0) 
				trap(7);

			bVar16 = possibleLanes[(lVar8 >> 8) % uVar17];
			uVar18 = bVar16;
			cp->ai.c.currentLane = bVar16;
			bVar1 = curve->NumLanes;
			model = (bVar1 & 0xf) * 2;
			if (model < uVar18) goto LAB_0002a368;
			if (((bVar16 == 0) && ((bVar1 & 0x40) != 0)) ||
				((model - 1 == uVar18 && ((bVar1 & 0x80) != 0)))) {
				civDat.thrustState = 3;
				civDat.ctrlState = 7;
				if (((int)(uint)curve->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) != 0) {
					civDat.ctrlState = 5;
				}
			}
			else {
				if (((int)(uint)curve->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) == 0)
					goto LAB_00029a28;
				civDat.thrustState = 0;
				civDat.ctrlState = 0;
			}
			local_30 = (int)(((int)curve->end - (int)curve->start & 0xfffU) *
				(uint)curve->inside * 0xb) / 7;
		}
	}
	if ((civDat.thrustState != 3) ||
		(((cVar5 = '\0', gInGameCutsceneActive == 0 && (gInGameChaseActive == 0)) &&
		((model = Random2(0), (model & 0x40) == 0 || (cVar5 = '\x03', gCurrentMissionNumber == 0x20)
			))))) {
		cVar5 = '\0';
	}
	modelRandomList[12] = cVar5;
	if (((specModelValid == '\0') || (allowSpecSpooling == 0)) ||
		(MissionHeader->residentModels[4] == 0xc)) 
	{
		modelRandomList[15] = 0;
		modelRandomList[14] = 1;
	}
	else {
		modelRandomList[15] = 4;
		model = Random2(0);
		modelRandomList[14] = 1;

		if ((model & 0x100) != 0) 
			modelRandomList[14] = 4;
	}
	if ((gCurrentMissionNumber == 7) || (gCurrentMissionNumber == 0x21)) {
		modelRandomList[9] = 0;
		modelRandomList[8] = 0;
		modelRandomList[11] = 1;
		modelRandomList[10] = 1;
	}
	else {
		modelRandomList[11] = 2;
		modelRandomList[10] = 2;
		modelRandomList[9] = 2;
		modelRandomList[8] = 2;
	}
	civDat.controlFlags = 0;

	if (requestCopCar == 0)
	{
		model = Random2(0);
		model = modelRandomList[model & 0xf];
	}
	else {
		model = 3;
	}

	if ((gCurrentMissionNumber == 0x21) && (minPingInDist == 0x29a)) {
		model = 4;
	}
	if (requestCopCar != 0) {
		civDat.controlFlags = 1;
	}
	if ((MissionHeader->residentModels[model] == 0) || (4 < MissionHeader->residentModels[model]))
	{
		civDat.palette = 0;
	}
	else 
	{
		if ((player[0].playerType == 1) &&
			((uint)car_data[player[0].playerCarId].ap.model == model)) 
		{
			lVar9 = Random2(0);
			lVar8 = lVar9;
			if (lVar9 < 0) {
				lVar8 = lVar9 + 3;
			}
			uVar17 = lVar9 + (lVar8 >> 2) * -4 & 0xff;
			civDat.palette = uVar17;

			if (car_data[player[0].playerCarId].ap.palette <= uVar17)
				civDat.palette = civDat.palette + 1;

		}
		else {
			lVar8 = Random2(0);
			civDat.palette = (char)lVar8 + (char)(lVar8 / 5) * -5;
		}
	}
	iVar6 = (int)car_cosmetics[model].colBox.vz;
	if ((((roadSeg & 0xffffe000U) == 0) && ((int)(roadSeg & 0x1fffU) < NumDriver2Straights)) && (-1 < roadSeg)) 
	{
		uVar17 = 0;
		if (requestCopCar == 0)
		{
			iVar7 = iVar6 * 2;
			uVar17 = iVar6 * 3;
		}
		else 
		{
			iVar7 = iVar6 << 1;
		}

		if (straight->length <= (iVar7 + iVar6) * 2) 
			return 0;

		dx = randomLoc.vx - straight->Midx;
		dz = randomLoc.vz - straight->Midz;

		lVar8 = ratan2(dx, dz);
		sVar2 = straight->angle;
		lVar9 = SquareRoot0(dx * dx + dz * dz);
		uVar3 = straight->length;
		civDat.distAlongSegment = (uVar3 >> 1) + (rcossin_tbl[(sVar2 - lVar8 & 0xfffU) * 2 + 1] * lVar9 + 0x800 >> 0xc);

		if (requestCopCar == 0) 
		{
			if (civDat.distAlongSegment < uVar17) 
			{
				civDat.distAlongSegment = uVar17;
			}
			if ((uVar3 - civDat.distAlongSegment) < uVar17) {
				civDat.distAlongSegment = uVar3 - uVar17;
			}
		}
		if ((*(uint *)(straight->ConnectIdx + 3) & 0xffff0000) == 0xff010000) {
			uVar17 = cp->ai.c.currentLane;
		}
		else {
			uVar17 = (int)straight->LaneDirs >> ((cp->ai.c.currentLane >> 1) & 0x1f);
		}
		if ((uVar17 & 1) == 0) {
			local_34 = straight->angle;
		}
		else {
			local_34 = straight->angle + 0x800U & 0xfff;
		}
	}
	else 
	{
		if ((((roadSeg & 0xffffe000U) == 0x4000) && ((roadSeg & 0x1fffU) < NumDriver2Curves)) && (-1 < roadSeg))
		{
			currentAngle = ratan2(randomLoc.vx - curve->Midx, randomLoc.vz - curve->Midz);
			uVar17 = 0;
			if (requestCopCar == 0)
			{
				bVar16 = curve->inside;
				uVar17 = 0x80;
				if ((9 < bVar16) && (uVar17 = 0x20, bVar16 < 0x14)) {
					uVar17 = 0x40;
				}
			}
			else {
				bVar16 = curve->inside;
			}
			uVar10 = (currentAngle & 0xfffU) - (int)curve->start;
			civDat.distAlongSegment = uVar10 & 0xf80;
			if ((9 < bVar16) && (civDat.distAlongSegment = uVar10 & 0xfe0, bVar16 < 0x14)) 
			{
				civDat.distAlongSegment = uVar10 & 0xfc0;
			}
			if (civDat.distAlongSegment <= uVar17) {
				civDat.distAlongSegment = uVar17;
			}
			uVar17 = (curve->end - curve->start) - uVar17 & 0xfff;
			if (uVar17 <= civDat.distAlongSegment) {
				civDat.distAlongSegment = uVar17;
			}
			iVar7 = civDat.distAlongSegment + (int)curve->start;
			if (curve->NumLanes == 0xff) {
				uVar17 = cp->ai.c.currentLane;
			}
			else {
				uVar17 = (int)curve->LaneDirs >> ((cp->ai.c.currentLane >> 1) & 0x1f);
			}
			if ((uVar17 & 1) == 0) {
				local_34 = iVar7 + 0x400;
			}
			else {
				local_34 = iVar7 - 0x400;
			}
			if (local_30 < iVar6 * 6) {
				return 0;
			}
		}
	}

	if (civDat.thrustState == 3 && civDat.ctrlState == 5 && maxParkedCars <= numParkedCars)
	{
		return 0;
	}

	if (((local_34 == 0xffffff) || ((int)uVar18 < 0)) || (civDat.distAlongSegment < 0)) 
	{
	LAB_0002a368:
		cp->ai.c.thrustState = 3;
		cp->ai.c.ctrlState = 7;
		return 0;
	}

	GetNodePos(straight, NULL, curve, civDat.distAlongSegment, cp, &cp->ai.c.targetRoute[0].x, &cp->ai.c.targetRoute[0].z, cp->ai.c.currentLane);

	uVar17 = 0x7fffffff;
	p_Var13 = car_data;
	pos[0] = cp->ai.c.targetRoute[0].x;
	pos[2] = cp->ai.c.targetRoute[0].z;
	pos[1] = randomLoc.vy;

	if (true) 
	{
		do {
			if (p_Var13->controlType != 0)
			{
				iVar11 = (p_Var13->hd).where.t[1];
				iVar7 = randomLoc.vy - iVar11;
				if (iVar7 < 0) 
				{
					iVar7 = iVar11 - randomLoc.vy;
				}

				if (iVar7 < 800) 
				{
					iVar11 = pos[0] - (p_Var13->hd).where.t[0];
					iVar7 = iVar11;

					if (iVar11 < 0)
					{
						iVar7 = -iVar11;
					}

					if (iVar7 < 0x1000) 
					{
						iVar12 = pos[2] - (p_Var13->hd).where.t[2];
						iVar7 = iVar12;

						if (iVar12 < 0) 
						{
							iVar7 = -iVar12;
						}

						if ((iVar7 < 0x1000) && (uVar10 = iVar11 * iVar11 + iVar12 * iVar12, uVar10 < uVar17)) 
						{
							uVar17 = uVar10;
						}
					}
				}
			}
			p_Var13 = p_Var13 + 1;
		} while (p_Var13 < car_data+20);
	}

	if (uVar17 != 56)	// [A] This was decompiled wrong
	{
		distSq = uVar17;
	}

	if (distSq < (iVar6 * iVar6 * 8 * 8)) 
		return 0;

	p_Var13 = car_data;
	iVar6 = 0;
	if (true)
	{
		do {
			if (p_Var13->controlType != 0) 
			{
				iVar11 = (p_Var13->hd).where.t[1];
				iVar7 = randomLoc.vy - iVar11;
				if (iVar7 < 0) {
					iVar7 = iVar11 - randomLoc.vy;
				}
				if (iVar7 < 800) {
					iVar11 = pos[0] - (p_Var13->hd).where.t[0];
					iVar7 = iVar11;
					if (iVar11 < 0) {
						iVar7 = -iVar11;
					}
					if (iVar7 < 0x7000) {
						iVar12 = pos[2] - (p_Var13->hd).where.t[2];
						iVar7 = iVar12;
						if (iVar12 < 0) {
							iVar7 = -iVar12;
						}
						if (iVar7 < 0x7000 && (iVar11 * iVar11 + iVar12 * iVar12) < 9000000)
						{
							iVar6 = iVar6 + 1;
						}
					}
				}
			}
			p_Var13 = p_Var13 + 1;
		} while (p_Var13 < car_data+20);
	}
	if (closeEncounter < iVar6)
		return 0;

	civDat.surfInd = roadSeg;
	if (roadSeg < 0) 
		goto LAB_0002a368;

	civDat.angle = local_34;
	InitCar(cp, local_34, &pos, 2, model, 0, (char *)&civDat);

	cp->ai.c.currentLane = uVar18;

	if ((gCurrentMissionNumber == 33) && (minPingInDist == 666)) 
		limoId = cp->id;

	if (cp->ai.c.thrustState == 3) 
	{
		if (cp->ai.c.ctrlState != 5) 
			goto LAB_0002a430;

		cp->controlFlags = cp->controlFlags | 4;
	}

	if (cp->ai.c.ctrlState == 5)
		numParkedCars = numParkedCars + 1;

LAB_0002a430:
	if ((cp->controlFlags & 1) != 0) 
	{
		requestCopCar = 0;
		numCopCars = numCopCars + 1;
	}
	numCivCars = numCivCars + 1;

	if ((cp->controlFlags & 1) != 0)
		PassiveCopTasks(cp);

	PingOutCivsOnly = 0;

	return cp->id + 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AttemptUnPark(struct _CAR_DATA *cp /*$s1*/)
 // line 2659, offset 0x0002a4c4
	/* begin block 1 */
		// Start line: 2660
		// Start offset: 0x0002A4C4
		// Variables:
	// 		struct DRIVER2_STRAIGHT *str; // $s2
	// 		struct DRIVER2_CURVE *crv; // $s3
	/* end block 1 */
	// End offset: 0x0002A5FC
	// End Line: 2690

	/* begin block 2 */
		// Start line: 6109
	/* end block 2 */
	// End Line: 6110

	/* begin block 3 */
		// Start line: 6113
	/* end block 3 */
	// End Line: 6114

	/* begin block 4 */
		// Start line: 6115
	/* end block 4 */
	// End Line: 6116

void AttemptUnPark(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	uint uVar2;
	DRIVER2_STRAIGHT *straight;
	DRIVER2_CURVE *curve;

	straight = (DRIVER2_STRAIGHT *)0x0;
	curve = (DRIVER2_CURVE *)0x0;
	InitCivState(cp, (char *)0x0);
	uVar2 = *(uint *)cp->ai;
	if ((((uVar2 & 0xffffe000) == 0) && ((int)(uVar2 & 0x1fff) < NumDriver2Straights)) &&
		(-1 < (int)uVar2)) {
		straight = Driver2StraightsPtr + uVar2;
	}
	else {
		curve = Driver2CurvesPtr + *(int *)cp->ai + -0x4000;
	}
	bVar1 = cp->ai[0xfb];
	uVar2 = CheckChangeLanes(straight, curve, *(int *)(cp->ai + 0x28), cp, 0);
	cp->ai[0xfb] = (byte)uVar2;
	if ((((uint)bVar1 == (uVar2 & 0xff)) ||
		((straight != (DRIVER2_STRAIGHT *)0x0 &&
		(((int)(uint)(byte)straight->AILanes >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f) & 1U) == 0)))) ||
			((curve != (DRIVER2_CURVE *)0x0 &&
		(((int)(uint)(byte)curve->AILanes >> ((uint)(cp->ai[0xfb] >> 1) & 0x1f) & 1U) == 0)))) {
		cp->ai[0xf9] = 3;
		cp->ai[0xc] = 7;
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivControl(struct _CAR_DATA *cp /*$s0*/)
 // line 2699, offset 0x0002ce10
	/* begin block 1 */
		// Start line: 2700
		// Start offset: 0x0002CE10

		/* begin block 1.1 */
			// Start line: 2700
			// Start offset: 0x0002CE10
		/* end block 1.1 */
		// End offset: 0x0002CE10
		// End Line: 2700

		/* begin block 1.2 */
			// Start line: 2729
			// Start offset: 0x0002CE8C
		/* end block 1.2 */
		// End offset: 0x0002CEC0
		// End Line: 2731
	/* end block 1 */
	// End offset: 0x0002CF18
	// End Line: 2740

	/* begin block 2 */
		// Start line: 7646
	/* end block 2 */
	// End Line: 7647

	/* begin block 3 */
		// Start line: 8189
	/* end block 3 */
	// End Line: 8190

// [D]
int CivControl(_CAR_DATA *cp)
{
	long lVar2;
	int iVar3;

	CheckPingOut(cp);

	if (cp->controlType == 2) 
	{
		if (cp->ai.c.changeLaneIndicateCount != 0) 
			cp->ai.c.changeLaneIndicateCount--;

		if ((((cp->ai.c.ctrlState == 5) && (cp->ai.c.thrustState == 3)) && (cp->totalDamage < 4)) && (((cp->ap).model != 3 &&
			(lVar2 = Random2(0), (lVar2 + (0x19 - cp->id) * 0x10 & 0xff8) == 0xf00)))) 
		{
			AttemptUnPark(cp);
		}

		cp->thrust = CivAccel(cp);

		if (cp->ai.c.thrustState != 3)
		{
			iVar3 = CivSteerAngle(cp);
			cp->wheel_angle = iVar3;
		}
	}

	if ((cp->controlFlags & 1) != 0) {
		PassiveCopTasks(cp);
	}

	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivAccelTrafficRules(struct _CAR_DATA *cp /*$t3*/, int *distToNode /*$a1*/)
 // line 2798, offset 0x0002a5fc
	/* begin block 1 */
		// Start line: 2799
		// Start offset: 0x0002A5FC
		// Variables:
	// 		int lbody; // $t1
	// 		int wbody; // $t2
	// 		struct CIV_STATE *cs; // $a2

		/* begin block 1.1 */
			// Start line: 2844
			// Start offset: 0x0002A71C
			// Variables:
		// 		int stopDist; // $t0

			/* begin block 1.1.1 */
				// Start line: 2848
				// Start offset: 0x0002A794
				// Variables:
			// 		int endSpeed; // $v0
			/* end block 1.1.1 */
			// End offset: 0x0002A800
			// End Line: 2853
		/* end block 1.1 */
		// End offset: 0x0002A800
		// End Line: 2854

		/* begin block 1.2 */
			// Start line: 2863
			// Start offset: 0x0002A844
			// Variables:
		// 		int ret; // $a1
		// 		int properVel; // $v1
		// 		int brakeDist; // $a3

			/* begin block 1.2.1 */
				// Start line: 2901
				// Start offset: 0x0002A918
				// Variables:
			// 		int endSpeed; // $v0
			// 		int currentDist; // $v1
			/* end block 1.2.1 */
			// End offset: 0x0002A918
			// End Line: 2901
		/* end block 1.2 */
		// End offset: 0x0002A9EC
		// End Line: 2915

		/* begin block 1.3 */
			// Start line: 2923
			// Start offset: 0x0002A9EC
			// Variables:
		// 		int roadClear; // $t8
		// 		int checkObstDist; // $t7
		// 		int numLanes; // $v0

			/* begin block 1.3.1 */
				// Start line: 2932
				// Start offset: 0x0002AA0C
				// Variables:
			// 		struct _CAR_DATA *cp; // $t3

				/* begin block 1.3.1.1 */
					// Start line: 2932
					// Start offset: 0x0002AA0C
					// Variables:
				// 		struct _CAR_DATA *lcp; // $a3
				// 		int normal; // $v0
				// 		int tangent; // $a0
				// 		int distToObstacle; // $t0
				// 		int ccarAng; // $t1
				// 		int scarAng; // $t2
				/* end block 1.3.1.1 */
				// End offset: 0x0002AB2C
				// End Line: 2932
			/* end block 1.3.1 */
			// End offset: 0x0002AB2C
			// End Line: 2932

			/* begin block 1.3.2 */
				// Start line: 2799
				// Start offset: 0x0002AB44
				// Variables:
			// 		struct _CAR_DATA *cp; // $t3

				/* begin block 1.3.2.1 */
					// Start line: 2799
					// Start offset: 0x0002AB44
					// Variables:
				// 		struct CIV_STATE *cs; // $v1
				/* end block 1.3.2.1 */
				// End offset: 0x0002AB44
				// End Line: 2799
			/* end block 1.3.2 */
			// End offset: 0x0002AB44
			// End Line: 2799

			/* begin block 1.3.3 */
				// Start line: 2943
				// Start offset: 0x0002AB58
				// Variables:
			// 		int ret; // $v1
			/* end block 1.3.3 */
			// End offset: 0x0002ABA8
			// End Line: 2946
		/* end block 1.3 */
		// End offset: 0x0002ABA8
		// End Line: 2947
	/* end block 1 */
	// End offset: 0x0002ABA8
	// End Line: 2949

	/* begin block 2 */
		// Start line: 6290
	/* end block 2 */
	// End Line: 6291

	/* begin block 3 */
		// Start line: 6399
	/* end block 3 */
	// End Line: 6400

int CivAccelTrafficRules(_CAR_DATA *cp, int *distToNode)
{
	UNIMPLEMENTED();
	return 0;
	/*
	short sVar1;
	byte bVar2;
	CAR_COSMETICS *pCVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	_CAR_DATA *p_Var8;
	int iVar9;
	int iVar10;

	pCVar3 = (cp->ap).carCos;
	iVar10 = (int)(pCVar3->colBox).vz;
	sVar1 = (pCVar3->colBox).vx;
	if ((cp->id == '\x01') && (cp->ai[0xfa] == 1)) {
		cp->ai[0xf9] = 3;
		cp->ai[0xc] = 9;
		cp->ai[0xfa] = 0;
	}
	switch (cp->ai[0xf9]) {
	case 0:
		break;
	case 1:
		if ((cp->ai[0xc] == 5) || (cp->ai[0xc] == 8)) {
			iVar10 = 100;
		}
		else {
			iVar10 = iVar10 * 3;
		}
		cp->ai[0x10] = 1;
		if ((*(int *)(cp->ai + 8) != 0) && (*(short *)(*(int *)(cp->ai + 8) + 2) != 0x7f)) {
			bVar2 = cp->ai[0xc];
			if ((bVar2 == 1) && ((&junctionLightsPhase)[cp->ai[0xd]] == '\x03')) {
			LAB_0002a8b4:
				cp->ai[0xf9] = 0;
				iVar10 = newAccel;
				*(undefined4 *)(cp->ai + 8) = 0;
				return iVar10;
			}
			iVar9 = *distToNode;
			if (iVar9 < iVar10) {
				if (bVar2 == 6) goto LAB_0002a8b4;
				iVar9 = (cp->hd).wheel_speed;
				iVar10 = -iVar9;
				if (0 < iVar9) {
					iVar10 = iVar10 + 3;
				}
				iVar10 = iVar10 >> 2;
				cp->ai[0xf9] = 3;
			}
			else {
				if (bVar2 == 6) {
					iVar10 = (iVar9 - iVar10) * *(int *)(cp->ai + 0x20) + 70000;
				}
				else {
					if (iVar10 < iVar9) {
						iVar10 = *(int *)(cp->ai + 0x20) * ((iVar9 - iVar10) + 100);
					}
					else {
						iVar10 = 0;
					}
				}
				iVar10 = ((iVar10 - (cp->hd).wheel_speed) * newAccel) / 0xf;
			}
			if ((car_data < *(_CAR_DATA **)(cp->ai + 8)) &&
				(*(_CAR_DATA **)(cp->ai + 8) < (_CAR_DATA *)0xd4934)) {
				iVar9 = newAccel;
				if ((iVar10 <= newAccel) && (iVar9 = iVar10, iVar10 < newAccel * -2)) {
					iVar9 = newAccel * -2;
				}
				return iVar9;
			}
		}
	default:
	LAB_0002a670:
		cp->ai[0xf9] = 3;
		cp->ai[0xc] = 7;
		return 0;
	case 3:
		switch (cp->ai[0xc]) {
		case 1:
			if ((&junctionLightsPhase)[cp->ai[0xd]] == '\x03') {
				cp->ai[0xf9] = 0;
			}
		case 2:
			cp->ai[0x10] = 1;
			return 0;
		case 3:
			bVar2 = 5;
			break;
		case 4:
			bVar2 = 6;
			break;
		default:
			cp->ai[0x10] = 0;
			return 0;
		}
		cp->ai[0xf9] = bVar2;
		cp->ai[0x10] = 1;
		return 0;
	case 5:
	case 6:
		cp->ai[0x10] = 1;
		iVar10 = 0x200;
		if (cp->ai[0xc] == 4) {
			iVar10 = 0x800;
		}
		p_Var8 = car_data + 0x13;
		uVar4 = (cp->hd).direction & 0xfff;
		iVar9 = 0x7fffff;
		do {
			if (((p_Var8->ai[0xf9] != 3) && (p_Var8 != cp)) && (p_Var8->controlType != '\0')) {
				iVar7 = (p_Var8->hd).where.t[0] - (cp->hd).where.t[0];
				iVar6 = (p_Var8->hd).where.t[2] - (cp->hd).where.t[2];
				iVar5 = iVar7 * rcossin_tbl[uVar4 * 2] + iVar6 * rcossin_tbl[uVar4 * 2 + 1] + 0x800 >> 0xc;
				if (0 < iVar5) {
					iVar6 = (iVar7 * rcossin_tbl[uVar4 * 2 + 1] - iVar6 * rcossin_tbl[uVar4 * 2]) + 0x800 >>
						0xc;
					if (iVar6 < 0) {
						iVar6 = -iVar6;
					}
					if ((iVar6 < (int)sVar1 * sideMul * 6) && (iVar5 < iVar9)) {
						iVar9 = iVar5;
					}
				}
			}
			p_Var8 = p_Var8 + -1;
		} while ((_CAR_DATA *)((int)&cheats.MagicMirror + 3U) < p_Var8);
		if (iVar10 < iVar9) {
			cp->ai[0xc] = 0;
			cp->ai[0xf9] = 0;
			iVar10 = newAccel;
			*(undefined4 *)(cp->ai + 8) = 0;
			return iVar10;
		}
		iVar9 = (cp->hd).wheel_speed;
		iVar10 = -iVar9;
		if (0 < iVar9) {
			iVar10 = iVar10 + 3;
		}
		iVar10 = iVar10 >> 2;
		iVar9 = newAccel;
		if ((iVar10 <= newAccel) && (iVar9 = iVar10, iVar10 < newAccel * -2)) {
			iVar9 = newAccel * -2;
		}
		return iVar9;
	}
	uVar4 = *(uint *)(cp->ai + 8);
	cp->ai[0x10] = 0;
	if (uVar4 == 0) goto LAB_0002a800;
	iVar5 = (cp->hd).wheel_speed;
	iVar9 = (iVar5 * (iVar5 + 0x800 >> 0xc)) / (newAccel << 1);
	if (newAccel << 1 == 0) {
		trap(7);
	}
	if (iVar9 < 0) {
		iVar9 = -iVar9;
	}
	if ((uVar4 < 0xd1269) || (0xd4933 < uVar4)) goto LAB_0002a670;
	iVar6 = *distToNode;
	if (iVar9 <= iVar6) goto LAB_0002a800;
	iVar5 = iVar5 + -120000;
	iVar9 = iVar6 + iVar10 * -3;
	if (iVar9 < 0) {
		if (2 < iVar10 * 3 - iVar6) goto LAB_0002a7d4;
	LAB_0002a7f8:
		*(int *)(cp->ai + 0x20) = iVar5;
	}
	else {
		if (2 < iVar9) {
		LAB_0002a7d4:
			iVar6 = iVar6 + iVar10 * -3;
			iVar5 = iVar5 / iVar6;
			if (iVar6 == 0) {
				trap(7);
			}
			goto LAB_0002a7f8;
		}
		*(int *)(cp->ai + 0x20) = iVar5;
	}
	cp->ai[0xf9] = 1;
LAB_0002a800:
	if ((cp->hd).wheel_speed + 0x800 >> 0xc <= (int)(uint)cp->ai[0xf8]) {
		return newAccel;
	}
	iVar10 = newAccel;
	if (newAccel < 0) {
		iVar10 = newAccel + 3;
	}
	return iVar10 >> 2;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetUpCivCollFlags()
 // line 2950, offset 0x0002aba8
	/* begin block 1 */
		// Start line: 2952
		// Start offset: 0x0002ABA8
		// Variables:
	// 		struct SVECTOR boxDisp; // stack offset -72
	// 		int carLength[2]; // stack offset -64
	// 		struct _CAR_DATA *cp0; // $s5
	// 		struct _CAR_DATA *cp1; // $s2
	// 		unsigned int dNewLBODY[2]; // stack offset -56
	// 		int dx; // $s0
	// 		int dz; // stack offset -48

		/* begin block 1.1 */
			// Start line: 2985
			// Start offset: 0x0002AC14
			// Variables:
		// 		int extraLength; // $a2
		/* end block 1.1 */
		// End offset: 0x0002AC44
		// End Line: 2985

		/* begin block 1.2 */
			// Start line: 2990
			// Start offset: 0x0002AD74

			/* begin block 1.2.1 */
				// Start line: 3003
				// Start offset: 0x0002ADC4
			/* end block 1.2.1 */
			// End offset: 0x0002AE18
			// End Line: 3003

			/* begin block 1.2.2 */
				// Start line: 3016
				// Start offset: 0x0002AF60
				// Variables:
			// 		int civCD; // $s7
			// 		int brake; // $a0

				/* begin block 1.2.2.1 */
					// Start line: 3024
					// Start offset: 0x0002AF90
					// Variables:
				// 		unsigned int *blth; // $v1
				/* end block 1.2.2.1 */
				// End offset: 0x0002AFC0
				// End Line: 3024

				/* begin block 1.2.2.2 */
					// Start line: 3033
					// Start offset: 0x0002B020
					// Variables:
				// 		int i; // $a1
				// 		int h; // $a3
				// 		int rnd; // $a2
				// 		struct _CAR_DATA *cp; // $s0

					/* begin block 1.2.2.2.1 */
						// Start line: 3040
						// Start offset: 0x0002B0C0
					/* end block 1.2.2.2.1 */
					// End offset: 0x0002B190
					// End Line: 3048
				/* end block 1.2.2.2 */
				// End offset: 0x0002B1A4
				// End Line: 3050
			/* end block 1.2.2 */
			// End offset: 0x0002B1A4
			// End Line: 3051
		/* end block 1.2 */
		// End offset: 0x0002B1A4
		// End Line: 3052

		/* begin block 1.3 */
			// Start line: 3056
			// Start offset: 0x0002B1C8
			// Variables:
		// 		unsigned char i; // $s0
		/* end block 1.3 */
		// End offset: 0x0002B26C
		// End Line: 3065
	/* end block 1 */
	// End offset: 0x0002B26C
	// End Line: 3066

	/* begin block 2 */
		// Start line: 6724
	/* end block 2 */
	// End Line: 6725

	/* begin block 3 */
		// Start line: 6725
	/* end block 3 */
	// End Line: 6726

	/* begin block 4 */
		// Start line: 6727
	/* end block 4 */
	// End Line: 6728

	/* begin block 5 */
		// Start line: 6729
	/* end block 5 */
	// End Line: 6730

	/* begin block 6 */
		// Start line: 6730
	/* end block 6 */
	// End Line: 6731

	/* begin block 7 */
		// Start line: 6757
	/* end block 7 */
	// End Line: 6758

/* WARNING: Removing unreachable block (ram,0x0002b034) */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void SetUpCivCollFlags(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	ushort uVar2;
	bool bVar3;
	undefined4 in_zero;
	undefined4 in_at;
	int iVar4;
	int iVar5;
	uint uVar6;
	long lVar7;
	int iVar8;
	_CAR_DATA **pp_Var9;
	int iVar10;
	int iVar11;
	_CAR_DATA **pp_Var12;
	CAR_COSMETICS *pCVar13;
	uint uVar14;
	uchar *puVar15;
	_CAR_DATA *p_Var16;
	undefined4 local_48;
	uint local_44;
	undefined4 local_30;
	_CAR_DATA *local_2c;

	ClearMem((char *)brakeLength, 0x50);
	local_2c = car_data + 0x13;
	do {
		if (local_2c->controlType == '\x02') {
			iVar10 = (local_2c->hd).wheel_speed + 0x800 >> 0xc;
			if (local_2c->wheel_angle < 0x3d) {
				iVar10 = iVar10 * 0xd;
			}
			else {
				iVar10 = iVar10 << 2;
			}
			pCVar13 = (local_2c->ap).carCos;
			iVar4 = (int)(pCVar13->colBox).vz;
			cd.length[0] = iVar10;
			if (iVar10 < 0) {
				cd.length[0] = -iVar10;
			}
			cd.length[0] = iVar4 + 0x5d + cd.length[0];
			cd.length[1] = (int)(pCVar13->colBox).vx;
			setCopControlWord(2, 0, *(undefined4 *)(local_2c->hd).where.m);
			setCopControlWord(2, 0x800, *(undefined4 *)((local_2c->hd).where.m + 2));
			setCopControlWord(2, 0x1000, *(undefined4 *)((local_2c->hd).where.m + 4));
			setCopControlWord(2, 0x1800, *(undefined4 *)((local_2c->hd).where.m + 6));
			setCopControlWord(2, 0x2000, *(undefined4 *)((local_2c->hd).where.m + 8));
			setCopControlWord(2, 0x2800, (local_2c->hd).where.t[0]);
			setCopControlWord(2, 0x3000, (local_2c->hd).where.t[1]);
			setCopControlWord(2, 0x3800, (local_2c->hd).where.t[2]);
			local_48 = CONCAT22(-(pCVar13->cog).vy, -(pCVar13->cog).vx);
			local_44 = local_44 & 0xffff0000 | (uint)(ushort)(((short)iVar10 - (pCVar13->cog).vz) + 0x5d);
			setCopReg(2, in_zero, local_48);
			setCopReg(2, in_at, local_44);
			copFunction(2, 0x480012);
			cd.x.vx = getCopReg(2, 0x19);
			cd.x.vy = getCopReg(2, 0x1a);
			cd.x.vz = getCopReg(2, 0x1b);
			p_Var16 = car_data + 0x14;
			cd.theta = (local_2c->hd).direction;
			do {
				if ((p_Var16->controlType == '\0') || (p_Var16 == local_2c)) {
				LAB_0002b1a4:
					bVar3 = p_Var16 + -1 < car_data;
				}
				else {
					if ((int)(p_Var16[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2 == 0x14) {
						if (player.playerType != '\x02') goto LAB_0002b1a4;
						CDATA2D_000bd0e4.length[0] = 0x3c;
						CDATA2D_000bd0e4.length[1] = 0x3c;
						CDATA2D_000bd0e4.x.vx = player.pos[0];
						CDATA2D_000bd0e4.x.vz = player.pos[2];
						CDATA2D_000bd0e4.theta = player.dir;
					}
					else {
						pCVar13 = (p_Var16->ap).carCos;
						CDATA2D_000bd0e4.length[0] = (int)(pCVar13->colBox).vz;
						CDATA2D_000bd0e4.length[1] = (int)(pCVar13->colBox).vx;
						CDATA2D_000bd0e4.x.vx = (p_Var16->hd).oBox.location.vx;
						CDATA2D_000bd0e4.x.vy = (p_Var16->hd).oBox.location.vy;
						CDATA2D_000bd0e4.x.vz = (p_Var16->hd).oBox.location.vz;
						CDATA2D_000bd0e4.theta = (p_Var16->hd).direction;
					}
					iVar10 = ((cd.length[0] + CDATA2D_000bd0e4.length[0]) * 3) / 2;
					if (cd.x.vx - CDATA2D_000bd0e4.x.vx < 0) {
						if (CDATA2D_000bd0e4.x.vx - cd.x.vx < iVar10) goto LAB_0002ae74;
						goto LAB_0002b1a4;
					}
					if (iVar10 <= cd.x.vx - CDATA2D_000bd0e4.x.vx) goto LAB_0002b1a4;
				LAB_0002ae74:
					if (cd.x.vz - CDATA2D_000bd0e4.x.vz < 0) {
						if (CDATA2D_000bd0e4.x.vz - cd.x.vz < iVar10) goto LAB_0002aeb0;
						goto LAB_0002b1a4;
					}
					if (iVar10 <= cd.x.vz - CDATA2D_000bd0e4.x.vz) goto LAB_0002b1a4;
				LAB_0002aeb0:
					iVar11 = (local_2c->hd).where.t[1];
					if ((int)(p_Var16[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2 == 0x14) {
					LAB_0002af10:
						iVar5 = player.pos[1] - iVar11;
						if (iVar5 < 0) {
							iVar5 = iVar11 - player.pos[1];
						}
						if (499 < iVar5) goto LAB_0002b1a4;
					}
					else {
						iVar8 = (p_Var16->hd).where.t[1];
						iVar5 = iVar8 - iVar11;
						if (iVar5 < 0) {
							iVar5 = iVar11 - iVar8;
						}
						if (499 < iVar5) {
							if ((int)(p_Var16[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2 != 0x14)
								goto LAB_0002b1a4;
							goto LAB_0002af10;
						}
					}
					iVar11 = bcollided2d(&cd, 1);
					if (iVar11 == 0) goto LAB_0002b1a4;
					ratan2(iVar10, local_30);
					uVar14 = (cd.length[0] - iVar4) - boxOverlap;
					if ((int)uVar14 < 1) {
						uVar14 = 1;
					}
					uVar6 = brakeLength[(byte)local_2c->id];
					if ((uVar6 == 0) || (uVar14 < uVar6)) {
						brakeLength[(byte)local_2c->id] = uVar14;
					}
					if (local_2c->ai[0xf9] == 3) goto LAB_0002b1a4;
					iVar10 = (int)(p_Var16[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2;
					if (iVar10 == 0x14) {
						*(int *)(local_2c->ai + 0x1c) = CAR_PAUSE_START;
					}
					bVar3 = p_Var16 + -1 < car_data;
					if ((local_2c->ai[0xf9] != 3) &&
						((p_Var16->controlType == '\x01' || (bVar3 = p_Var16 + -1 < car_data, iVar10 == 0x14)))
						) {
						lVar7 = Random2(0);
						bVar3 = false;
						pp_Var12 = &horncarflag2;
						iVar10 = 1;
						pp_Var9 = pp_Var12;
						do {
							if (*pp_Var9 == local_2c) {
								bVar3 = true;
							}
							iVar10 = iVar10 + -1;
							pp_Var9 = pp_Var9 + 1;
						} while (-1 < iVar10);
						iVar10 = 0;
						puVar15 = &hornchanflag;
						do {
							if ((!bVar3) && (*puVar15 == 0)) {
								uVar14 = GetFreeChannel();
								*puVar15 = (byte)uVar14;
								SpuSetVoiceAR(uVar14 & 0xff, 0x1b);
								bVar1 = (local_2c->ap).model;
								if (bVar1 == 4) {
									uVar14 = ResidentModelsBodge();
								}
								else {
									if (bVar1 < 3) {
										uVar14 = (uint)(byte)(local_2c->ap).model;
									}
									else {
										uVar14 = (uint)(byte)(local_2c->ap).model - 1;
									}
								}
								Start3DSoundVolPitch
								((uint)*puVar15, 3, uVar14 * 3 + 2, (local_2c->hd).where.t[0],
									(local_2c->hd).where.t[1], (local_2c->hd).where.t[2], -2000, 0x1000);
								bVar1 = *puVar15;
								uVar2 = (&channels)[bVar1].time;
								*pp_Var12 = local_2c;
								(&channels)[bVar1].time = uVar2 + (short)lVar7 + (short)(lVar7 / 0x1e) * -0x1e;
								break;
							}
							pp_Var12 = pp_Var12 + 1;
							iVar10 = iVar10 + 1;
							puVar15 = puVar15 + 1;
						} while (iVar10 < 2);
						goto LAB_0002b1a4;
					}
				}
				p_Var16 = p_Var16 + -1;
			} while (!bVar3);
		}
		local_2c = local_2c + -1;
		if (local_2c <= (_CAR_DATA *)((int)&cheats.MagicMirror + 3U)) {
			uVar14 = 0;
			do {
				bVar1 = (&hornchanflag)[uVar14];
				if ((bVar1 != 0) && ((&channels)[bVar1].time == 0)) {
					(&horncarflag2)[uVar14] = (_CAR_DATA *)0x0;
					(&hornchanflag)[uVar14] = 0;
					SpuSetVoiceAR(0, 0x23);
				}
				uVar14 = uVar14 + 1 & 0xff;
			} while (uVar14 < 2);
			return;
		}
	} while (true);*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivAccel(struct _CAR_DATA *cp /*$s0*/)
 // line 3074, offset 0x0002b26c
	/* begin block 1 */
		// Start line: 3075
		// Start offset: 0x0002B26C
		// Variables:
	// 		int ret; // $t1
	// 		int distToNode; // stack offset -16
	// 		int dx; // $v1
	// 		int dz; // $a0

		/* begin block 1.1 */
			// Start line: 3106
			// Start offset: 0x0002B35C
			// Variables:
		// 		int tmpRet; // $a0
		// 		int lbody; // $a0

			/* begin block 1.1.1 */
				// Start line: 3111
				// Start offset: 0x0002B388
				// Variables:
			// 		int sf; // $v1
			// 		int c1; // $t0
			// 		int c2; // $a3
			// 		int c3; // $a1

				/* begin block 1.1.1.1 */
					// Start line: 3126
					// Start offset: 0x0002B44C
					// Variables:
				// 		int tmp; // $v1
				/* end block 1.1.1.1 */
				// End offset: 0x0002B4B8
				// End Line: 3129
			/* end block 1.1.1 */
			// End offset: 0x0002B4C8
			// End Line: 3132
		/* end block 1.1 */
		// End offset: 0x0002B528
		// End Line: 3146
	/* end block 1 */
	// End offset: 0x0002B53C
	// End Line: 3149

	/* begin block 2 */
		// Start line: 7066
	/* end block 2 */
	// End Line: 7067

	/* begin block 3 */
		// Start line: 7067
	/* end block 3 */
	// End Line: 7068

	/* begin block 4 */
		// Start line: 7076
	/* end block 4 */
	// End Line: 7077

	/* begin block 5 */
		// Start line: 7084
	/* end block 5 */
	// End Line: 7085

int CivAccel(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	uint uVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint uVar6;
	int local_10[2];

	iVar5 = *(int *)(cp->ai + 8);
	carnum = (int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2;
	if ((iVar5 == 0) || (cp->ai[0xf9] == 3)) {
		local_10[0] = -1;
	}
	else {
		iVar3 = (cp->hd).where.t[0] - *(int *)(iVar5 + 8);
		iVar5 = (cp->hd).where.t[2] - *(int *)(iVar5 + 0xc);
		local_10[0] = SquareRoot0(iVar3 * iVar3 + iVar5 * iVar5);
	}
	if ((cp->ai[0xf9] != 3) && (*(short *)(*(int *)(cp->ai + 8) + 2) == 0x7f)) {
		local_10[0] = -local_10[0];
	}
	iVar5 = CivAccelTrafficRules(cp, local_10);
	if (cp->ai[0xf9] != 3) {
		collDat = brakeLength[(byte)cp->id];
		iVar3 = (uint)(ushort)(((cp->ap).carCos)->colBox).vz << 0x10;
		iVar4 = iVar3 >> 0x10;
		if (collDat != 0) {
			iVar1 = iVar4;
			if (iVar4 < 0) {
				iVar1 = iVar4 + 3;
			}
			uVar6 = iVar4 - (iVar3 >> 0x1f) >> 1;
			if (collDat < (uint)(iVar4 * 2)) {
				if (((uint)(iVar4 * 2) < collDat) && (uVar6 <= collDat)) {
					uVar6 = uVar6 + iVar4 * -2;
					if (uVar6 == 0) {
						trap(7);
					}
					iVar3 = ((collDat + iVar4 * -2) * -100) / uVar6 + 100;
				}
				else {
					if ((uVar6 < collDat) && ((uint)(iVar1 >> 2) <= collDat)) {
						uVar2 = (iVar1 >> 2) - uVar6;
						if (uVar2 == 0) {
							trap(7);
						}
						iVar3 = ((collDat - uVar6) * -300) / uVar2 + 400;
					}
					else {
						iVar3 = 100;
					}
				}
			}
			else {
				iVar3 = 0;
			}
			iVar1 = (cp->hd).wheel_speed;
			iVar4 = -iVar1;
			iVar3 = (newAccel * iVar3) / 100;
			if (0 < iVar1) {
				iVar4 = iVar4 + 3;
			}
			iVar4 = iVar4 >> 2;
			if ((iVar4 <= iVar3) && (iVar1 = iVar3 * -2, iVar3 = iVar4, iVar4 < iVar1)) {
				iVar3 = iVar1;
			}
			if (iVar3 < iVar5) {
				iVar5 = iVar3;
			}
		}
		if ((0 < *(int *)(cp->ai + 0x1c)) && (collDat == 0)) {
			iVar4 = (cp->hd).wheel_speed;
			iVar3 = iVar4 + 0x800 >> 0xc;
			if (iVar3 < 0) {
				iVar3 = -iVar3;
			}
			iVar1 = -iVar4;
			if (iVar3 < 3) {
				if (0 < iVar4) {
					iVar1 = iVar1 + 3;
				}
				iVar5 = iVar1 >> 2;
				*(int *)(cp->ai + 0x1c) = *(int *)(cp->ai + 0x1c) + -1;
			}
		}
	}
	return iVar5;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivSteerAngle(struct _CAR_DATA *cp /*$s0*/)
 // line 3166, offset 0x0002b53c
	/* begin block 1 */
		// Start line: 3167
		// Start offset: 0x0002B53C
		// Variables:
	// 		int station; // $a3
	// 		int step; // $s2
	// 		int ret; // $a0
	// 		struct VECTOR locPath; // stack offset -56
	// 		struct VECTOR pathPoint; // stack offset -40
	// 		int lbody; // $s3

		/* begin block 1.1 */
			// Start line: 3167
			// Start offset: 0x0002B53C

			/* begin block 1.1.1 */
				// Start line: 3167
				// Start offset: 0x0002B53C
				// Variables:
			// 		struct _CAR_DATA *cp; // $s0

				/* begin block 1.1.1.1 */
					// Start line: 3167
					// Start offset: 0x0002B53C
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.1.1.1 */
				// End offset: 0x0002B590
				// End Line: 3175
			/* end block 1.1.1 */
			// End offset: 0x0002B590
			// End Line: 3175

			/* begin block 1.1.2 */
				// Start line: 3167
				// Start offset: 0x0002B5A0
				// Variables:
			// 		struct _CAR_DATA *cp; // $s0

				/* begin block 1.1.2.1 */
					// Start line: 3167
					// Start offset: 0x0002B5A0
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.1.2.1 */
				// End offset: 0x0002B5B0
				// End Line: 3167
			/* end block 1.1.2 */
			// End offset: 0x0002B5B0
			// End Line: 3167

			/* begin block 1.1.3 */
				// Start line: 3167
				// Start offset: 0x0002B5C0
				// Variables:
			// 		struct _CAR_DATA *cp; // $s0

				/* begin block 1.1.3.1 */
					// Start line: 3167
					// Start offset: 0x0002B5C0
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.1.3.1 */
				// End offset: 0x0002B5D0
				// End Line: 3167
			/* end block 1.1.3 */
			// End offset: 0x0002B5D0
			// End Line: 3167

			/* begin block 1.1.4 */
				// Start line: 3167
				// Start offset: 0x0002B5E0
				// Variables:
			// 		struct _CAR_DATA *cp; // $s0

				/* begin block 1.1.4.1 */
					// Start line: 3167
					// Start offset: 0x0002B5E0
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.1.4.1 */
				// End offset: 0x0002B5F0
				// End Line: 3167
			/* end block 1.1.4 */
			// End offset: 0x0002B5F0
			// End Line: 3167
		/* end block 1.1 */
		// End offset: 0x0002B610
		// End Line: 3192

		/* begin block 1.2 */
			// Start line: 3167
			// Start offset: 0x0002B67C
			// Variables:
		// 		struct _CAR_DATA *cp; // $s0

			/* begin block 1.2.1 */
				// Start line: 3167
				// Start offset: 0x0002B67C
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $a0
			/* end block 1.2.1 */
			// End offset: 0x0002B690
			// End Line: 3167
		/* end block 1.2 */
		// End offset: 0x0002B690
		// End Line: 3167

		/* begin block 1.3 */
			// Start line: 3201
			// Start offset: 0x0002B6A0
			// Variables:
		// 		struct CIV_ROUTE_ENTRY *crLoc; // $a1
		// 		struct CIV_ROUTE_ENTRY *cr; // $a0
		/* end block 1.3 */
		// End offset: 0x0002B700
		// End Line: 3212

		/* begin block 1.4 */
			// Start line: 3167
			// Start offset: 0x0002B748
			// Variables:
		// 		struct _CAR_DATA *cp; // $s0

			/* begin block 1.4.1 */
				// Start line: 3167
				// Start offset: 0x0002B748
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
			/* end block 1.4.1 */
			// End offset: 0x0002B758
			// End Line: 3167
		/* end block 1.4 */
		// End offset: 0x0002B758
		// End Line: 3167

		/* begin block 1.5 */
			// Start line: 3236
			// Start offset: 0x0002B870
			// Variables:
		// 		struct CIV_ROUTE_ENTRY *cr; // $a0

			/* begin block 1.5.1 */
				// Start line: 3167
				// Start offset: 0x0002B8A0
				// Variables:
			// 		struct _CAR_DATA *cp; // $s0

				/* begin block 1.5.1.1 */
					// Start line: 3167
					// Start offset: 0x0002B8A0
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.5.1.1 */
				// End offset: 0x0002B8B0
				// End Line: 3167
			/* end block 1.5.1 */
			// End offset: 0x0002B8B0
			// End Line: 3167
		/* end block 1.5 */
		// End offset: 0x0002B8C0
		// End Line: 3243
	/* end block 1 */
	// End offset: 0x0002B8E4
	// End Line: 3246

	/* begin block 2 */
		// Start line: 7260
	/* end block 2 */
	// End Line: 7261

	/* begin block 3 */
		// Start line: 7278
	/* end block 3 */
	// End Line: 7279

/* WARNING: Type propagation algorithm not settling */

int CivSteerAngle(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	return 0;
	/*
	undefined4 *puVar1;
	short sVar2;
	int iVar3;
	int iVar4;
	long lVar5;
	_CAR_DATA *p_Var6;
	_CAR_DATA *p_Var7;
	CIV_ROUTE_ENTRY *pCVar8;
	_CAR_DATA *p_Var9;
	CIV_ROUTE_ENTRY *pCVar10;
	undefined4 uVar11;
	long lVar12;
	undefined4 *puVar13;
	int iVar14;
	CIV_ROUTE_ENTRY *pCVar15;
	_CAR_DATA *p_Var16;
	undefined4 *puVar17;
	undefined4 uVar18;
	undefined4 uVar19;
	VECTOR local_28;

	pCVar15 = (CIV_ROUTE_ENTRY *)(cp->ai + 0xf4);
	iVar3 = (cp->hd).wheel_speed;
	startNode = *(CIV_ROUTE_ENTRY **)(cp->ai + 0xf4);
	sVar2 = (((cp->ap).carCos)->colBox).vz;
	pCVar8 = startNode + 1;
	if (pCVar15 <= pCVar8) {
		pCVar8 = startNode + -0xc;
	}
	pCVar10 = startNode + 2;
	if (pCVar8->pathType == 0x7f) {
	LAB_0002b600:
		iVar4 = CreateNewNode(cp);
		if (iVar4 == 0) goto LAB_0002b76c;
	}
	else {
		if (pCVar15 <= pCVar10) {
			pCVar10 = startNode + -0xb;
		}
		pCVar8 = startNode + 3;
		if (pCVar10->pathType == 0x7f) goto LAB_0002b600;
		if (pCVar15 <= pCVar8) {
			pCVar8 = startNode + -10;
		}
		pCVar10 = startNode + 4;
		if (pCVar8->pathType == 0x7f) goto LAB_0002b600;
		if (pCVar15 <= pCVar10) {
			pCVar10 = startNode + -9;
		}
		if (pCVar10->pathType == 0x7f) goto LAB_0002b600;
	}
	p_Var7 = cp;
	p_Var16 = &currentCar;
	do {
		p_Var9 = p_Var16;
		p_Var6 = p_Var7;
		uVar11 = *(undefined4 *)((p_Var6->hd).where.m + 2);
		uVar18 = *(undefined4 *)((p_Var6->hd).where.m + 4);
		uVar19 = *(undefined4 *)((p_Var6->hd).where.m + 6);
		*(undefined4 *)(p_Var9->hd).where.m = *(undefined4 *)(p_Var6->hd).where.m;
		*(undefined4 *)((p_Var9->hd).where.m + 2) = uVar11;
		*(undefined4 *)((p_Var9->hd).where.m + 4) = uVar18;
		*(undefined4 *)((p_Var9->hd).where.m + 6) = uVar19;
		p_Var7 = (_CAR_DATA *)((p_Var6->hd).where.m + 8);
		p_Var16 = (_CAR_DATA *)((p_Var9->hd).where.m + 8);
	} while (p_Var7 != (_CAR_DATA *)&cp->handbrake);
	lVar5 = (p_Var6->hd).where.t[0];
	lVar12 = (p_Var6->hd).where.t[1];
	*(undefined4 *)(p_Var16->hd).where.m = *(undefined4 *)(p_Var7->hd).where.m;
	(p_Var9->hd).where.t[0] = lVar5;
	(p_Var9->hd).where.t[1] = lVar12;
	iVar4 = *(int *)(cp->ai + 0xf4);
	pCVar8 = (CIV_ROUTE_ENTRY *)(iVar4 + 0x10);
	if (*(short *)(iVar4 + 2) != 0x7f) {
		pCVar15 = (CIV_ROUTE_ENTRY *)(cp->ai + 0xf4);
		if (pCVar15 <= pCVar8) {
			pCVar8 = (CIV_ROUTE_ENTRY *)(iVar4 + -0xc0);
		}
		if (pCVar8->pathType != 0x7f) {
			iVar4 = CivFindStation(cp);
			puVar13 = (undefined4 *)(cp->ai + 0xe4);
			puVar17 = (undefined4 *)(currentCar.ai + 0xe4);
			while (cp->ai + 0x24 <= puVar13) {
				*puVar17 = *puVar13;
				puVar17[1] = puVar13[1];
				puVar17[2] = puVar13[2];
				puVar1 = puVar13 + 3;
				puVar13 = puVar13 + -4;
				puVar17[3] = *puVar1;
				puVar17 = puVar17 + -4;
			}
			currentCar.hd.direction = (cp->hd).direction;
			currentCar.ai._244_4_ = *(undefined4 *)(cp->ai + 0xf4);
			currentCar.ai._4_4_ = *(undefined4 *)(cp->ai + 4);
			currentCar.ai._0_4_ = *(undefined4 *)cp->ai;
			iVar14 = *(int *)(cp->ai + 0xf4);
			pCVar8 = (CIV_ROUTE_ENTRY *)(iVar14 + 0x10);
			if (*(short *)(iVar14 + 2) != 0x7f) {
				if (pCVar15 <= pCVar8) {
					pCVar8 = (CIV_ROUTE_ENTRY *)(iVar14 + -0xc0);
				}
				if (pCVar8->pathType != 0x7f) {
					CivFindPointOnPath(cp, iVar4 + (iVar3 + 0x800 >> 0xc) * checkFrames + (int)sVar2, &local_28)
						;
					iVar3 = ratan2(local_28.vx - (cp->hd).where.t[0], local_28.vz - (cp->hd).where.t[2]);
					iVar4 = ((iVar3 - (cp->hd).direction) + 0x800U & 0xfff) - 0x800;
					iVar3 = maxSteer;
					if ((iVar4 <= maxSteer) && (iVar3 = iVar4, iVar4 < -maxSteer)) {
						iVar3 = -maxSteer;
					}
					p_Var7 = &currentCar;
					p_Var16 = cp;
					do {
						p_Var9 = p_Var16;
						p_Var6 = p_Var7;
						uVar11 = *(undefined4 *)((p_Var6->hd).where.m + 2);
						uVar18 = *(undefined4 *)((p_Var6->hd).where.m + 4);
						uVar19 = *(undefined4 *)((p_Var6->hd).where.m + 6);
						*(undefined4 *)(p_Var9->hd).where.m = *(undefined4 *)(p_Var6->hd).where.m;
						*(undefined4 *)((p_Var9->hd).where.m + 2) = uVar11;
						*(undefined4 *)((p_Var9->hd).where.m + 4) = uVar18;
						*(undefined4 *)((p_Var9->hd).where.m + 6) = uVar19;
						p_Var7 = (_CAR_DATA *)((p_Var6->hd).where.m + 8);
						p_Var16 = (_CAR_DATA *)((p_Var9->hd).where.m + 8);
					} while (p_Var7 != (_CAR_DATA *)&currentCar.handbrake);
					lVar5 = (p_Var6->hd).where.t[0];
					lVar12 = (p_Var6->hd).where.t[1];
					*(undefined4 *)(p_Var16->hd).where.m = currentCar._656_4_;
					(p_Var9->hd).where.t[0] = lVar5;
					(p_Var9->hd).where.t[1] = lVar12;
					pCVar8 = startNode;
					if (startNode == *(CIV_ROUTE_ENTRY **)(cp->ai + 0xf4)) {
						return iVar3;
					}
					do {
						pCVar8->pathType = 0x7f;
						pCVar10 = pCVar8 + 1;
						if (*(int *)(cp->ai + 0x14) == (int)pCVar8 + (-0x1b0 - (int)cp) >> 4) {
							*(undefined4 *)(cp->ai + 0x14) = 0xffffffff;
						}
						if (pCVar15 <= pCVar10) {
							pCVar10 = pCVar8 + -0xc;
						}
						pCVar8 = pCVar10;
					} while (pCVar10 != *(CIV_ROUTE_ENTRY **)(cp->ai + 0xf4));
					return iVar3;
				}
			}
		}
	}
LAB_0002b76c:
	cp->ai[0xf9] = 3;
	cp->ai[0xc] = 7;
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivFindStation(struct _CAR_DATA *cp /*$s6*/)
 // line 3265, offset 0x0002b8e4
	/* begin block 1 */
		// Start line: 3266
		// Start offset: 0x0002B8E4
		// Variables:
	// 		struct CIV_ROUTE_ENTRY *rep; // $s3
	// 		int cx; // stack offset -48
	// 		int cz; // $fp

		/* begin block 1.1 */
			// Start line: 3266
			// Start offset: 0x0002B8E4
			// Variables:
		// 		int loop; // $a0

			/* begin block 1.1.1 */
				// Start line: 3266
				// Start offset: 0x0002B93C
				// Variables:
			// 		struct _CAR_DATA *cp; // $s6

				/* begin block 1.1.1.1 */
					// Start line: 3266
					// Start offset: 0x0002B93C
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.1.1.1 */
				// End offset: 0x0002B950
				// End Line: 3266
			/* end block 1.1.1 */
			// End offset: 0x0002B950
			// End Line: 3266
		/* end block 1.1 */
		// End offset: 0x0002B95C
		// End Line: 3277

		/* begin block 1.2 */
			// Start line: 3280
			// Start offset: 0x0002B964
			// Variables:
		// 		struct _CAR_DATA *cp; // $s6
		// 		struct CIV_ROUTE_ENTRY *currentNode; // $s3

			/* begin block 1.2.1 */
				// Start line: 3280
				// Start offset: 0x0002B964
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $s0
			/* end block 1.2.1 */
			// End offset: 0x0002B964
			// End Line: 3280
		/* end block 1.2 */
		// End offset: 0x0002B964
		// End Line: 3280

		/* begin block 1.3 */
			// Start line: 3282
			// Start offset: 0x0002B964
			// Variables:
		// 		int sx; // $s5
		// 		int sz; // $s4
		// 		int dx; // $s2
		// 		int dz; // $s1
		// 		int stepsize; // $a1
		// 		int square; // $a0

			/* begin block 1.3.1 */
				// Start line: 3309
				// Start offset: 0x0002BA28
				// Variables:
			// 		struct _CAR_DATA *cp; // $s6
			// 		struct CIV_ROUTE_ENTRY *currentNode; // $s3

				/* begin block 1.3.1.1 */
					// Start line: 3309
					// Start offset: 0x0002BA28
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.3.1.1 */
				// End offset: 0x0002BA38
				// End Line: 3309
			/* end block 1.3.1 */
			// End offset: 0x0002BA38
			// End Line: 3309

			/* begin block 1.3.2 */
				// Start line: 3266
				// Start offset: 0x0002BA48
				// Variables:
			// 		struct _CAR_DATA *cp; // $s6
			// 		struct CIV_ROUTE_ENTRY *currentNode; // $s3

				/* begin block 1.3.2.1 */
					// Start line: 3266
					// Start offset: 0x0002BA48
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.3.2.1 */
				// End offset: 0x0002BA58
				// End Line: 3266
			/* end block 1.3.2 */
			// End offset: 0x0002BA58
			// End Line: 3266

			/* begin block 1.3.3 */
				// Start line: 3266
				// Start offset: 0x0002BA68
				// Variables:
			// 		struct _CAR_DATA *cp; // $s6
			// 		struct CIV_ROUTE_ENTRY *currentNode; // $s3

				/* begin block 1.3.3.1 */
					// Start line: 3266
					// Start offset: 0x0002BA68
					// Variables:
				// 		struct CIV_ROUTE_ENTRY *retNode; // $v1
				/* end block 1.3.3.1 */
				// End offset: 0x0002BA78
				// End Line: 3266
			/* end block 1.3.3 */
			// End offset: 0x0002BA78
			// End Line: 3266
		/* end block 1.3 */
		// End offset: 0x0002BA90
		// End Line: 3317
	/* end block 1 */
	// End offset: 0x0002BAEC
	// End Line: 3320

	/* begin block 2 */
		// Start line: 7478
	/* end block 2 */
	// End Line: 7479

	/* begin block 3 */
		// Start line: 7498
	/* end block 3 */
	// End Line: 7499

int CivFindStation(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	byte *pbVar3;
	byte *pbVar4;
	byte *pbVar5;
	int iVar6;
	byte *pbVar7;
	int iVar8;
	byte *pbVar9;
	int iVar10;
	int iVar11;
	int iVar12;

	iVar2 = (cp->hd).where.t[0];
	iVar6 = *(int *)(cp->ai + 4) + -1;
	iVar12 = (cp->hd).where.t[2];
	pbVar3 = cp->ai + 0x24;
	if (iVar6 != -1) {
		pbVar9 = pbVar3;
		do {
			pbVar3 = pbVar9 + 0x10;
			if (cp->ai + 0xf4 <= pbVar3) {
				pbVar3 = pbVar9 + -0xc0;
			}
			iVar6 = iVar6 + -1;
			pbVar9 = pbVar3;
		} while (iVar6 != -1);
	}
	pbVar9 = cp->ai + 0xf4;
	do {
		pbVar7 = pbVar3 + 0x10;
		if (pbVar9 <= pbVar7) {
			pbVar7 = pbVar3 + -0xc0;
		}
		if (pbVar7 == (byte *)0x0) {
		LAB_0002baac:
			cp->ai[0xf9] = 3;
			cp->ai[0xc] = 7;
			return 0;
		}
		iVar11 = *(int *)(pbVar3 + 8);
		iVar8 = *(int *)(pbVar7 + 8) - iVar11;
		iVar10 = *(int *)(pbVar3 + 0xc);
		iVar6 = *(int *)(pbVar7 + 0xc) - iVar10;
		if (iVar8 * iVar8 + iVar6 * iVar6 < 0) goto LAB_0002baac;
		iVar1 = SquareRoot0();
		if (0 < iVar1) {
			iVar6 = ((iVar2 - iVar11) * iVar8 + (iVar12 - iVar10) * iVar6) / iVar1;
			if (iVar1 == 0) {
				trap(7);
			}
			if (iVar6 < iVar1) {
				*(byte **)(cp->ai + 0xf4) = pbVar3;
				return iVar6;
			}
		}
		iVar6 = *(int *)(cp->ai + 4) + 1;
		*(int *)(cp->ai + 4) = iVar6;
		pbVar4 = pbVar7 + 0x10;
		if (0xc < iVar6) {
			*(undefined4 *)(cp->ai + 4) = 0;
		}
		if (pbVar9 <= pbVar4) {
			pbVar4 = pbVar7 + -0xc0;
		}
		pbVar5 = pbVar7 + 0x20;
		pbVar3 = pbVar7;
		if (*(short *)(pbVar4 + 2) == 0x7f) goto LAB_0002ba88;
		if (pbVar9 <= pbVar5) {
			pbVar5 = pbVar7 + -0xb0;
		}
		pbVar4 = pbVar7 + 0x30;
		if (*(short *)(pbVar5 + 2) == 0x7f) goto LAB_0002ba88;
		if (pbVar9 <= pbVar4) {
			pbVar4 = pbVar7 + -0xa0;
		}
		if (*(short *)(pbVar4 + 2) == 0x7f) {
		LAB_0002ba88:
			CreateNewNode(cp);
		}
	} while (true);*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivFindPointOnPath(struct _CAR_DATA *cp /*$s7*/, int station /*$s2*/, struct VECTOR *ppoint /*$fp*/)
 // line 3337, offset 0x0002baec
	/* begin block 1 */
		// Start line: 3338
		// Start offset: 0x0002BAEC
		// Variables:
	// 		struct CIV_ROUTE_ENTRY *cprep; // $a0
	// 		struct CIV_ROUTE_ENTRY *start; // stack offset -48

		/* begin block 1.1 */
			// Start line: 3346
			// Start offset: 0x0002BB50
			// Variables:
		// 		struct _CAR_DATA *cp; // $s7
		// 		struct CIV_ROUTE_ENTRY *currentNode; // $a0

			/* begin block 1.1.1 */
				// Start line: 3346
				// Start offset: 0x0002BB50
				// Variables:
			// 		struct CIV_ROUTE_ENTRY *retNode; // $s0
			/* end block 1.1.1 */
			// End offset: 0x0002BB50
			// End Line: 3346
		/* end block 1.1 */
		// End offset: 0x0002BB50
		// End Line: 3346

		/* begin block 1.2 */
			// Start line: 3348
			// Start offset: 0x0002BB50
			// Variables:
		// 		int sx; // $s4
		// 		int sz; // $s5
		// 		int dx; // $s1
		// 		int dz; // $s3
		// 		int stepsize; // $a2
		/* end block 1.2 */
		// End offset: 0x0002BC90
		// End Line: 3381
	/* end block 1 */
	// End offset: 0x0002BCF4
	// End Line: 3385

	/* begin block 2 */
		// Start line: 7686
	/* end block 2 */
	// End Line: 7687

	/* begin block 3 */
		// Start line: 7704
	/* end block 3 */
	// End Line: 7705

int CivFindPointOnPath(_CAR_DATA *cp, int station, VECTOR *ppoint)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	byte *pbVar2;
	byte *pbVar3;
	byte *pbVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	pbVar2 = *(byte **)(cp->ai + 0xf4);
	if (pbVar2 != (byte *)0x0) {
		pbVar3 = pbVar2;
		do {
			pbVar4 = pbVar3 + 0x10;
			if (cp->ai + 0xf4 <= pbVar4) {
				pbVar4 = pbVar3 + -0xc0;
			}
			if (pbVar4 == (byte *)0x0) {
				ppoint->vx = *(long *)(pbVar3 + 8);
				ppoint->vz = *(long *)(pbVar3 + 0xc);
				return 1;
			}
			iVar7 = *(int *)(pbVar3 + 8);
			iVar5 = *(int *)(pbVar4 + 8) - iVar7;
			iVar8 = *(int *)(pbVar3 + 0xc);
			iVar6 = *(int *)(pbVar4 + 0xc) - iVar8;
			iVar1 = SquareRoot0(iVar5 * iVar5 + iVar6 * iVar6);
			if (station < iVar1) {
				if (station < 0) {
					station = 0;
				}
				if (iVar1 < 0x1000) {
					if (iVar1 == 0) {
						trap(7);
					}
					iVar6 = (iVar6 * station) / iVar1;
					ppoint->vx = iVar7 + (iVar5 * station) / iVar1;
					if (iVar1 == 0) {
						trap(7);
					}
				}
				else {
					if (iVar1 < 0) {
						iVar1 = iVar1 + 0xf;
					}
					iVar1 = iVar1 >> 4;
					if (iVar1 == 0) {
						trap(7);
					}
					if (iVar1 == 0) {
						trap(7);
					}
					ppoint->vx = iVar7 + (((iVar5 * 0x100) / iVar1) * station + 0x800 >> 0xc);
					iVar6 = ((iVar6 * 0x100) / iVar1) * station + 0x800 >> 0xc;
				}
				ppoint->vz = iVar8 + iVar6;
				return 1;
			}
			station = station - iVar1;
			pbVar3 = pbVar4;
		} while (pbVar4 != pbVar2);
	}
	cp->ai[0xf9] = 3;
	cp->ai[0xc] = 7;
	return 0;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CreateRoadblock()
 // line 3398, offset 0x0002bcf4
	/* begin block 1 */
		// Start line: 3400
		// Start offset: 0x0002BCF4
		// Variables:
	// 		struct _CAR_DATA *cp; // $v1
	// 		struct _CAR_DATA *lcp; // $s0
	// 		struct _CAR_DATA *newCar; // $s0
	// 		struct DRIVER2_STRAIGHT *str; // stack offset -72
	// 		struct DRIVER2_CURVE *crv; // $s7
	// 		int distAlongSegment; // $s2
	// 		int lbody; // $s4
	// 		int dir; // $s6
	// 		int numLanes; // stack offset -68
	// 		unsigned char externalCopModel; // stack offset -64
	// 		int delta; // $s4
	// 		int noMoreCars; // stack offset -60
	// 		int newCarId; // $v1

		/* begin block 1.1 */
			// Start line: 3400
			// Start offset: 0x0002BCF4
			// Variables:
		// 		int dir; // $s0
		/* end block 1.1 */
		// End offset: 0x0002C078
		// End Line: 3437

		/* begin block 1.2 */
			// Start line: 3442
			// Start offset: 0x0002C09C
			// Variables:
		// 		int theta; // $s0
		/* end block 1.2 */
		// End offset: 0x0002C198
		// End Line: 3451

		/* begin block 1.3 */
			// Start line: 3455
			// Start offset: 0x0002C1E0
			// Variables:
		// 		int minAngle; // $a3
		// 		int curveLength; // $v1
		/* end block 1.3 */
		// End offset: 0x0002C334
		// End Line: 3491

		/* begin block 1.4 */
			// Start line: 3478
			// Start offset: 0x0002C3F8

			/* begin block 1.4.1 */
				// Start line: 3483
				// Start offset: 0x0002C4C8
			/* end block 1.4.1 */
			// End offset: 0x0002C4E4
			// End Line: 3485

			/* begin block 1.4.2 */
				// Start line: 3399
				// Start offset: 0x0002C590
				// Variables:
			// 		struct _CAR_DATA *cp; // $s0
			/* end block 1.4.2 */
			// End offset: 0x0002C674
			// End Line: 3399

			/* begin block 1.4.3 */
				// Start line: 3399
				// Start offset: 0x0002C708
				// Variables:
			// 		struct _CAR_DATA *cp; // $s0
			/* end block 1.4.3 */
			// End offset: 0x0002C7E4
			// End Line: 3399
		/* end block 1.4 */
		// End offset: 0x0002C7F4
		// End Line: 3510

		/* begin block 1.5 */
			// Start line: 3515
			// Start offset: 0x0002C830
			// Variables:
		// 		struct VECTOR startPos2; // stack offset -88
		// 		int deltaAngle; // $a0
		// 		int dir2NextRow; // $a1
		// 		int faceDir; // $s1
		// 		int numSpareCars; // $a0
		// 		int count; // $s2
		// 		int numSpots; // $fp

			/* begin block 1.5.1 */
				// Start line: 3527
				// Start offset: 0x0002C948
				// Variables:
			// 		int numCarsToAdd; // $s5

				/* begin block 1.5.1.1 */
					// Start line: 3531
					// Start offset: 0x0002C97C

					/* begin block 1.5.1.1.1 */
						// Start line: 3399
						// Start offset: 0x0002CAC4
						// Variables:
					// 		struct _CAR_DATA *cp; // $s0
					/* end block 1.5.1.1.1 */
					// End offset: 0x0002CBA8
					// End Line: 3399

					/* begin block 1.5.1.1.2 */
						// Start line: 3399
						// Start offset: 0x0002CC3C
						// Variables:
					// 		struct _CAR_DATA *cp; // $s0
					/* end block 1.5.1.1.2 */
					// End offset: 0x0002CD18
					// End Line: 3399
				/* end block 1.5.1.1 */
				// End offset: 0x0002CD28
				// End Line: 3555
			/* end block 1.5.1 */
			// End offset: 0x0002CD34
			// End Line: 3556
		/* end block 1.5 */
		// End offset: 0x0002CD34
		// End Line: 3557
	/* end block 1 */
	// End offset: 0x0002CD74
	// End Line: 3564

	/* begin block 2 */
		// Start line: 7892
	/* end block 2 */
	// End Line: 7893

	/* begin block 3 */
		// Start line: 7906
	/* end block 3 */
	// End Line: 7907

	/* begin block 4 */
		// Start line: 7907
	/* end block 4 */
	// End Line: 7908

	/* begin block 5 */
		// Start line: 7909
	/* end block 5 */
	// End Line: 7910

/* WARNING: Unknown calling convention yet parameter storage is locked */

void CreateRoadblock(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte bVar2;
	short sVar3;
	bool bVar4;
	char cVar5;
	int laneNo;
	undefined3 extraout_var;
	long lVar6;
	int x;
	int z;
	CAR_COSMETICS *pCVar7;
	uint *puVar8;
	uint uVar9;
	int iVar10;
	int x_00;
	_CAR_DATA *mem;
	uint uVar11;
	uint distAlongPath;
	int z_00;
	int iVar12;
	DRIVER2_CURVE *curve;
	DRIVER2_STRAIGHT *local_48;
	int local_44;

	curve = (DRIVER2_CURVE *)0x0;
	distAlongPath = 0xfffffffb;
	laneNo = (int)player.playerCarId;
	local_48 = (DRIVER2_STRAIGHT *)0x0;
	bVar4 = false;
	z_00 = (int)car_cosmetics[3].colBox.vz;
	iVar10 = car_data[laneNo].hd.direction;
	bVar1 = *(byte *)(MissionHeader->residentModels + 3);
	baseLoc.vx = car_data[laneNo].hd.where.t[0];
	angle = 0;
	baseLoc.vz = car_data[laneNo].hd.where.t[2];
	do {
		if (requestCopCar == 0) {
			laneNo = (int)rcossin_tbl[(iVar10 + angle & 0xfffU) * 2] << 3;
		}
		else {
			laneNo = (int)rcossin_tbl[(iVar10 + angle & 0xfffU) * 2] * 10;
		}
		roadblockLoc.vx = baseLoc.vx + (laneNo + 0x800 >> 0xc) * 0x800;
		if (requestCopCar == 0) {
			laneNo = (int)rcossin_tbl[(iVar10 + angle & 0xfffU) * 2 + 1] << 3;
		}
		else {
			laneNo = (int)rcossin_tbl[(iVar10 + angle & 0xfffU) * 2 + 1] * 10;
		}
		roadblockLoc.vz = baseLoc.vz + (laneNo + 0x800 >> 0xc) * 0x800;
		roadSeg = RoadInCell(&roadblockLoc);
		if (((((roadSeg & 0xffffe000U) == 0) && ((int)(roadSeg & 0x1fffU) < NumDriver2Straights)) ||
			(((roadSeg & 0xffffe000U) == 0x4000 && ((int)(roadSeg & 0x1fffU) < NumDriver2Curves)))) &&
			(-1 < roadSeg)) break;
		if (requestCopCar == 0) {
			laneNo = (int)rcossin_tbl[(iVar10 - angle & 0xfffU) * 2] << 3;
		}
		else {
			laneNo = (int)rcossin_tbl[(iVar10 - angle & 0xfffU) * 2] * 10;
		}
		roadblockLoc.vx = baseLoc.vx + (laneNo + 0x800 >> 0xc) * 0x800;
		if (requestCopCar == 0) {
			laneNo = (int)rcossin_tbl[(iVar10 - angle & 0xfffU) * 2 + 1] << 3;
		}
		else {
			laneNo = (int)rcossin_tbl[(iVar10 - angle & 0xfffU) * 2 + 1] * 10;
		}
		roadblockLoc.vz = baseLoc.vz + (laneNo + 0x800 >> 0xc) * 0x800;
		roadSeg = RoadInCell(&roadblockLoc);
		if (((((roadSeg & 0xffffe000U) == 0) && ((int)(roadSeg & 0x1fffU) < NumDriver2Straights)) ||
			(((roadSeg & 0xffffe000U) == 0x4000 && ((int)(roadSeg & 0x1fffU) < NumDriver2Curves)))) &&
			(-1 < roadSeg)) break;
		if (requestCopCar == 0) {
			angle = angle + 0x5d;
		}
		else {
			angle = angle + 0x49;
		}
	} while (angle < 0x800);
	if (((roadSeg & 0xffffe000U) != 0) || (NumDriver2Straights <= (int)(roadSeg & 0x1fffU))) {
		if ((roadSeg & 0xffffe000U) != 0x4000) {
			return;
		}
		if (NumDriver2Curves <= (int)(roadSeg & 0x1fffU)) {
			return;
		}
	}
	if (roadSeg < 0) {
		return;
	}
	if (((roadSeg & 0xffffe000U) == 0) && ((int)(roadSeg & 0x1fffU) < NumDriver2Straights)) {
		local_48 = Driver2StraightsPtr + roadSeg;
		dx = roadblockLoc.vx - local_48->Midx;
		dz = roadblockLoc.vz - local_48->Midz;
		laneNo = ratan2(dx, dz);
		sVar3 = local_48->angle;
		iVar10 = SquareRoot0(dx * dx + dz * dz);
		uVar9 = (uint)local_48->length;
		uVar11 = z_00 * 3;
		distAlongPath =
			(uint)(local_48->length >> 1) +
			(rcossin_tbl[(sVar3 - laneNo & 0xfffU) * 2 + 1] * iVar10 + 0x800 >> 0xc);
		if ((int)uVar9 < z_00 * 6) {
			return;
		}
		if ((int)distAlongPath < (int)uVar11) {
			distAlongPath = uVar11;
		}
		if ((int)(uVar9 - distAlongPath) < (int)uVar11) {
			distAlongPath = uVar9 + z_00 * -3;
		}
		bVar2 = local_48->NumLanes;
	}
	else {
		if (((roadSeg & 0xffffe000U) != 0x4000) ||
			((NumDriver2Curves <= (int)(roadSeg & 0x1fffU) || (roadSeg < 0)))) goto LAB_0002c33c;
		curve = Driver2CurvesPtr + roadSeg + -0x4000;
		if ((int)(((int)curve->end - (int)curve->start & 0xfffU) * (uint)(byte)curve->inside * 0xb) / 7
			< z_00 * 6) {
			return;
		}
		currentAngle = ratan2(roadblockLoc.vx - curve->Midx, roadblockLoc.vz - curve->Midz);
		uVar11 = 0x80;
		if ((9 < (byte)curve->inside) && (uVar11 = 0x20, (byte)curve->inside < 0x14)) {
			uVar11 = 0x40;
		}
		uVar9 = (currentAngle & 0xfffU) - (int)curve->start;
		distAlongPath = uVar9 & 0xf80;
		if ((9 < (byte)curve->inside) && (distAlongPath = uVar9 & 0xfe0, (byte)curve->inside < 0x14)) {
			distAlongPath = uVar9 & 0xfc0;
		}
		if (distAlongPath <= uVar11) {
			distAlongPath = uVar11;
		}
		uVar11 = ((int)curve->end - (int)curve->start) - uVar11 & 0xfff;
		if (uVar11 <= distAlongPath) {
			distAlongPath = uVar11;
		}
		bVar2 = curve->NumLanes;
	}
	local_44 = ((uint)bVar2 & 0xf) << 1;
LAB_0002c33c:
	GetNodePos(local_48, (DRIVER2_JUNCTION *)0x0, curve, distAlongPath, (_CAR_DATA *)0x0, (int *)&startPos,
		&startPos.vz, 0);
	laneNo = local_44 + -1;
	GetNodePos(local_48, (DRIVER2_JUNCTION *)0x0, curve, distAlongPath, (_CAR_DATA *)0x0, (int *)&endPos,
		&endPos.vz, laneNo);
	iVar10 = 0x100;
	distAlongPath = ratan2(endPos.vx - startPos.vx, endPos.vz - startPos.vz);
	if (0x100 < laneNo * 0x200) {
		do {
			currentPos.vx =
				startPos.vx + (iVar10 * rcossin_tbl[(distAlongPath & 0xfff) * 2] + 0x800 >> 0xc);
			currentPos.vz =
				startPos.vz + (iVar10 * rcossin_tbl[(distAlongPath & 0xfff) * 2 + 1] + 0x800 >> 0xc);
			if (local_48 == (DRIVER2_STRAIGHT *)0x0) {
			LAB_0002c49c:
				if (curve != (DRIVER2_CURVE *)0x0) {
					z_00 = iVar10;
					if (iVar10 < 0) {
						z_00 = iVar10 + 0x3ff;
					}
					if (((int)(uint)(byte)curve->AILanes >> (z_00 >> 10 & 0x1fU) & 1U) == 0)
						goto LAB_0002c4cc;
				}
			LAB_0002c4e4:
				lVar6 = Random2(0);
				z_00 = iVar10;
				if (iVar10 < 0) {
					z_00 = iVar10 + 0x1ff;
				}
				z_00 = CreateStationaryCivCar
				(distAlongPath + (lVar6 * 0x10001 >> (z_00 >> 9 & 0x1fU) & 0x3ffU) + -0x200
					, 0, 0, (long(*)[4])&currentPos, (uint)bVar1, 0, 2);
				if (z_00 == -1) {
					bVar4 = true;
					break;
				}
				pCVar7 = car_data[z_00].ap.carCos;
				x = QuickBuildingCollisionCheck
				((VECTOR *)car_data[z_00].hd.where.t, car_data[z_00].hd.direction,
					(int)(pCVar7->colBox).vz, (int)(pCVar7->colBox).vx, 0x14);
				if (x != 0) {
					testNumPingedOut = testNumPingedOut + 1;
					if (car_data[z_00].controlType == '\x02') {
						if ((car_data[z_00].controlFlags & 1) != 0) {
							numCopCars = numCopCars + -1;
						}
						numCivCars = numCivCars + -1;
						if ((car_data[z_00].ai[0xf9] == 3) && (car_data[z_00].ai[0xc] == 5)) {
							numParkedCars = numParkedCars + -1;
						}
					}
					else {
						if ((PingOutCivsOnly != '\0') &&
							(x = valid_region(car_data[z_00].hd.where.t[0], car_data[z_00].hd.where.t[2]), x != 0)
							) goto LAB_0002c678;
					}
					puVar8 = (uint *)car_data[z_00].inform;
					if (puVar8 != (uint *)0x0) {
						*puVar8 = *puVar8 ^ 0x40000000;
					}
					ClearMem((char *)(car_data + z_00), 0x29c);
					car_data[z_00].controlType = '\0';
				}
			LAB_0002c678:
				mem = car_data + 0x13;
				do {
					if ((mem->controlType != '\0') && ((*(uint *)&mem->hndType & 0x2ff00) != 0x20200)) {
						x = (mem->hd).where.t[0];
						dx = x - currentPos.vx;
						z_00 = (mem->hd).where.t[2];
						dz = z_00 - currentPos.vz;
						if (dx * dx + dz * dz < 360000) {
							testNumPingedOut = testNumPingedOut + 1;
							if (mem->controlType == '\x02') {
								if ((mem->controlFlags & 1) != 0) {
									numCopCars = numCopCars + -1;
								}
								numCivCars = numCivCars + -1;
								if ((mem->ai[0xf9] == 3) && (mem->ai[0xc] == 5)) {
									numParkedCars = numParkedCars + -1;
								}
							}
							else {
								if ((PingOutCivsOnly != '\0') && (z_00 = valid_region(x, z_00), z_00 != 0))
									goto LAB_0002c7e4;
							}
							puVar8 = (uint *)mem->inform;
							if (puVar8 != (uint *)0x0) {
								*puVar8 = *puVar8 ^ 0x40000000;
							}
							ClearMem((char *)mem, 0x29c);
							mem->controlType = '\0';
						}
					}
				LAB_0002c7e4:
					mem = mem + -1;
				} while ((_CAR_DATA *)((int)&cheats.MagicMirror + 3U) < mem);
			}
			else {
				z_00 = iVar10;
				if (iVar10 < 0) {
					z_00 = iVar10 + 0x3ff;
				}
				if (((int)(uint)(byte)local_48->AILanes >> (z_00 >> 10 & 0x1fU) & 1U) != 0)
					goto LAB_0002c49c;
			LAB_0002c4cc:
				cVar5 = CellEmpty(&currentPos, (int)car_cosmetics[3].colBox.vz);
				if (CONCAT31(extraout_var, cVar5) != 0) goto LAB_0002c4e4;
			}
			iVar10 = iVar10 + 0x400;
		} while (iVar10 < laneNo * 0x200);
	}
	if ((!bVar4) && (gCopDifficultyLevel != 0)) {
		laneNo = ratan2(baseLoc.vx - startPos.vx, baseLoc.vz - startPos.vz);
		iVar10 = 0x400;
		if ((((laneNo - distAlongPath) + 0x800 & 0xfff) - 0x800 & 0xfff) < 0x800) {
			iVar10 = -0x400;
		}
		uVar11 = distAlongPath;
		if (gCopDifficultyLevel == 1) {
			uVar11 = distAlongPath - iVar10;
		}
		uVar9 = distAlongPath + iVar10 & 0xfff;
		laneNo = startPos.vx + ((int)rcossin_tbl[uVar9 * 2] * 0x5dc + 0x800 >> 0xc);
		iVar10 = startPos.vz + ((int)rcossin_tbl[uVar9 * 2 + 1] * 0x5dc + 0x800 >> 0xc);
		z_00 = (maxCivCars - numCivCars) + 2;
		x = local_44 / 2 + -1;
		if (0 < z_00) {
			iVar12 = x;
			if (z_00 < x) {
				iVar12 = z_00;
			}
			z_00 = 0;
			if (0 < iVar12) {
				z = 0;
				do {
					if (iVar12 << 1 == 0) {
						trap(7);
					}
					x_00 = ((x * (z + 1)) / (iVar12 << 1)) * 0x400;
					z = x_00 + 0x300;
					currentPos.vx = laneNo + (z * rcossin_tbl[(distAlongPath & 0xfff) * 2] + 0x800 >> 0xc);
					currentPos.vz = iVar10 + (z * rcossin_tbl[(distAlongPath & 0xfff) * 2 + 1] + 0x800 >> 0xc)
						;
					test42 = z;
					lVar6 = Random2(0);
					if (z < 0) {
						z = x_00 + 0x4ff;
					}
					z = CreateStationaryCivCar
					(uVar11 + (lVar6 * 0x10001 >> (z >> 9 & 0x1fU) & 0x3ffU) + -0x200, 0, 0,
						(long(*)[4])&currentPos, (uint)bVar1, 0, 2);
					if (z == -1) break;
					pCVar7 = car_data[z].ap.carCos;
					x_00 = QuickBuildingCollisionCheck
					((VECTOR *)car_data[z].hd.where.t, car_data[z].hd.direction,
						(int)(pCVar7->colBox).vz, (int)(pCVar7->colBox).vx, 0x14);
					if (x_00 != 0) {
						testNumPingedOut = testNumPingedOut + 1;
						if (car_data[z].controlType == '\x02') {
							if ((car_data[z].controlFlags & 1) != 0) {
								numCopCars = numCopCars + -1;
							}
							numCivCars = numCivCars + -1;
							if ((car_data[z].ai[0xf9] == 3) && (car_data[z].ai[0xc] == 5)) {
								numParkedCars = numParkedCars + -1;
							}
						}
						else {
							if ((PingOutCivsOnly != '\0') &&
								(x_00 = valid_region(car_data[z].hd.where.t[0], car_data[z].hd.where.t[2]),
									x_00 != 0)) goto LAB_0002cbac;
						}
						puVar8 = (uint *)car_data[z].inform;
						if (puVar8 != (uint *)0x0) {
							*puVar8 = *puVar8 ^ 0x40000000;
						}
						ClearMem((char *)(car_data + z), 0x29c);
						car_data[z].controlType = '\0';
					}
				LAB_0002cbac:
					mem = car_data + 0x13;
					z_00 = z_00 + 1;
					do {
						if ((mem->controlType != '\0') && ((*(uint *)&mem->hndType & 0x2ff00) != 0x20200)) {
							x_00 = (mem->hd).where.t[0];
							dx = x_00 - currentPos.vx;
							z = (mem->hd).where.t[2];
							dz = z - currentPos.vz;
							if (dx * dx + dz * dz < 360000) {
								testNumPingedOut = testNumPingedOut + 1;
								if (mem->controlType == '\x02') {
									if ((mem->controlFlags & 1) != 0) {
										numCopCars = numCopCars + -1;
									}
									numCivCars = numCivCars + -1;
									if ((mem->ai[0xf9] == 3) && (mem->ai[0xc] == 5)) {
										numParkedCars = numParkedCars + -1;
									}
								}
								else {
									if ((PingOutCivsOnly != '\0') && (z = valid_region(x_00, z), z != 0))
										goto LAB_0002cd18;
								}
								puVar8 = (uint *)mem->inform;
								if (puVar8 != (uint *)0x0) {
									*puVar8 = *puVar8 ^ 0x40000000;
								}
								ClearMem((char *)mem, 0x29c);
								mem->controlType = '\0';
							}
						}
					LAB_0002cd18:
						mem = mem + -1;
					} while ((_CAR_DATA *)((int)&cheats.MagicMirror + 3U) < mem);
					z = z_00 * 2;
				} while (z_00 < iVar12);
			}
		}
	}
	requestRoadblock = 0;
	distAlongPath = Random2(0);
	roadblockDelay = (&roadblockDelayDiff)[gCopDifficultyLevel] + (distAlongPath & 0xff);
	roadblockCount = roadblockDelay;
	PlaceRoadBlockCops();
	return;
	*/
}





