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
#include "GAMESND.H"
#include "SOUND.H"
#include "BCOLLIDE.H"
#include "LEADAI.H"
#include "MAIN.H"
#include "PEDEST.H"
#include "OBJCOLL.H"

#include "INLINE_C.H"
#include "STRINGS.H"

unsigned char speedLimits[3] = { 56, 97, 138 };

CIV_AI_234fake civPingTest = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char modelRandomList[] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 1, 0, 4 };
unsigned char reservedSlots[20] = { 0 };

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

char junctionLightsPhase[2];

int test42 = 0;
int test123 = 0;
int test555 = 0;

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
	VECTOR tmpStart;

	ClearMem((char *)cp, sizeof(_CAR_DATA));

	cp->wasOnGround = 1;

	cp->id = CAR_INDEX(cp);

	if (startPos == NULL)
		return 0;

	cp->ap.model = model;
	cp->lowDetail = -1;
	cp->ap.qy = 0;
	cp->ap.qw = 0;
	cp->ap.carCos = &car_cosmetics[model];
	tmpStart.vx = (*startPos)[0];
	tmpStart.vy = (*startPos)[1];
	tmpStart.vz = (*startPos)[2];
	tmpStart.vy = MapHeight(&tmpStart);
	tmpStart.vy = tmpStart.vy - cp->ap.carCos->wheelDisp[0].vy;

	if (control == 0) 
		return 1;

	InitCarPhysics(cp, (long(*)[4])&tmpStart, direction);
	cp->ap.palette = (char)palette;

	cp->controlType = control;

	switch (control) 
	{
		case 1:
		case 7:
			cp->ai.padid = extraData;

			player[cp->id].worldCentreCarId = cp->id;
			cp->hndType = 0;
			break;
		case 2:
			cp->hndType = 1;

			if (extraData == NULL)
			{
				cp->controlFlags = 0;
				cp->ap.palette = 0;
			}
			else
			{
				cp->controlFlags = ((EXTRA_CIV_DATA*)extraData)->controlFlags;
				cp->ap.palette = ((EXTRA_CIV_DATA*)extraData)->palette;
			}

			InitCivState(cp, (EXTRA_CIV_DATA*)extraData);

			break;
		case 3:
			InitCopState(cp, extraData);
			cp->ap.palette = 0;
			numCopCars++;
			break;
		case 4:
			InitLead(cp);
			leadCarId = cp->id;
			cp->hndType = 5;
			break;
	}

	CreateDentableCar(cp);
	DentCar(cp);

	return 1;
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

					if (iVar4 < 0)
						iVar1 = -iVar4;

					if ((iVar1 < 0x1000) && (uVar2 = iVar3 * iVar3 + iVar4 * iVar4, uVar2 < retDistSq)) 
					{
						retDistSq = uVar2;
						retCar = lcp;
					}
				}
			}
		}
		lcp++;
	} while (lcp < &car_data[20]);

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

// [D]
int NotTravellingAlongCurve(int x, int z, int dir, DRIVER2_CURVE *cv)
{
	return ((((dir - ratan2(x - cv->Midx, z - cv->Midz)) + 0x800U & 0xfff) - 0x800) < 1) << 0xb;
}

// decompiled code
// original method signature: 
// void /*$ra*/ CivCarFX(struct _CAR_DATA *cp /*$s0*/)
 // line 930, offset 0x0002d084
	/* begin block 1 */
		// Start line: 1860
	/* end block 1 */
	// End Line: 1861

// [D]
void CivCarFX(_CAR_DATA *cp)
{
	if (cp->ai.c.thrustState != 3)
	{
		if (cp->ai.c.turnNode != -1)
			AddIndicatorLight(cp, cp->ai.c.turnDir);

		if (cp->ai.c.changeLaneIndicateCount != 0 && cp->ai.c.turnNode == -1)
			AddIndicatorLight(cp, cp->ai.c.changeLane);
	}

	if (cp->ai.c.brakeLight != 0)
		AddBrakeLight(cp);
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

int currentRoadId = 0;
int tmpNewRoad[2];
int newExit = 0;
int tmpNewLane[2];
int laneFit[2];
DRIVER2_STRAIGHT* tmpStr[2];
DRIVER2_CURVE* tmpCrv[2];
short validExitIdx[4];

#define IS_NODE_VALID(n) ((char*)(n) > (char*)car_data && (char*)(n) < (char*)&car_data[21])

// [D] [A]
// BUGS:
//		- cannot continue to new straight from curve - unable to determine best lane
int GetNextRoadInfo(_CAR_DATA *cp, int randomExit, int *turnAngle, int *startDist, CIV_ROUTE_ENTRY *oldNode)
{
	short sVar1;
	short uVar2;
	bool bVar3;
	unsigned char bVar6;
	int uVar7;
	int uVar8;
	int uVar9;
	int iVar15;
	long lVar9;
	int iVar10;
	unsigned char bVar7;
	int iVar11;
	int uVar16;
	long lVar17;
	int iVar12;
	int iVar13;
	int iVar14;
	int iVar19;
	DRIVER2_JUNCTION *jn;
	int uVar20;
	int *puVar15;
	int *puVar21;
	int iVar22;
	int iVar23;
	int iVar16;
	int uVar17;
	int iVar18;
	int uVar25;
	int local_a1_7136;
	int uVar19;
	short *puVar20;
	DRIVER2_STRAIGHT *tmpSt;
	int iVar26;
	unsigned char *pbVar21;
	DRIVER2_CURVE *____cv;
	DRIVER2_CURVE *tmpCv;
	DRIVER2_CURVE *_cv;
	DRIVER2_CURVE *___cv;
	DRIVER2_CURVE *__cv;
	DRIVER2_CURVE *cv;
	uint uVar22;
	uint uVar23;
	int newLane;
	int uVar27;
	int uVar24;
	int uVar28;
	int uVar29;
	int *piVar25;
	uint uVar26;
	DRIVER2_STRAIGHT *_st;
	DRIVER2_STRAIGHT *___st;
	DRIVER2_STRAIGHT *__st;
	DRIVER2_STRAIGHT *st;
	int unaff_s8;
	int iVar30;
	int numExits;
	//int direction;
	int leftLane;
	int rightLane;
	short uVar3;
	bool bVar4;
	short sVar2;
	bool bVar5;
	unsigned char bVar1;

	currentRoadId = cp->ai.c.currentRoad;
	_st = NULL;

	if ((((currentRoadId & 0xffffe000U) == 0) && ((int)(currentRoadId & 0x1fffU) < NumDriver2Straights)) && (-1 < currentRoadId)) 
	{
		_st = Driver2StraightsPtr + currentRoadId;

		if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) == 0xff010000)
		{
			uVar7 = (uint)cp->ai.c.currentLane;
		}
		else 
		{
			uVar7 = (int)(u_char)_st->LaneDirs >> ((uint)(cp->ai.c.currentLane >> 1) & 0x1f);
		}

		uVar7 = uVar7 & 1;
		uVar26 = uVar7 << 0xb;

		if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) == 0xff010000)
		{
			uVar8 = (uint)cp->ai.c.currentLane;
		}
		else
		{
			uVar8 = (int)(u_char)_st->LaneDirs >> ((uint)(cp->ai.c.currentLane >> 1) & 0x1f);
		}

		tmpNewRoad[0] = (int)_st->ConnectIdx[(uVar8 & 1) * 2];

		if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) == 0xff010000) 
		{
			uVar9 = (uint)cp->ai.c.currentLane;
		}
		else
		{
			uVar9 = (int)(u_char)_st->LaneDirs >> ((uint)(cp->ai.c.currentLane >> 1) & 0x1f);
		}

		iVar16 = 2;

		if ((uVar9 & 1) != 0) 
		{
			iVar16 = 6;
		}

		tmpNewRoad[1] = (int)*(short *)((int)_st->ConnectIdx + iVar16);
		uVar22 = ((u_char)_st->NumLanes & 0xf) * 2;
		uVar9 = uVar22;
		uVar29 = uVar22;

		do {
			do {
				uVar9 = uVar9 - 1;
				
				if ((int)uVar9 < 0) 
					goto LAB_00024288;

			} while (((((int)(u_char)_st->AILanes >> ((int)uVar9 / 2 & 0x1fU) & 1U) == 0) ||
				((uVar9 == 0 && ((_st->NumLanes & 0x40U) != 0)))) ||
				((((u_char)_st->NumLanes & 0xffffff0f) * 2 - 1 == uVar9 &&
				((_st->NumLanes & 0x80U) != 0))));

			uVar29 = uVar9;

			if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
			{
				uVar29 = (int)(u_char)_st->LaneDirs >> ((int)uVar9 / 2 & 0x1fU);
			}

			test42 = (uVar29 ^ 1) & 1;
			uVar29 = uVar9;
		} while (uVar7 == 0);

	LAB_00024288:

		if (uVar7 == 0)
			leftLane = uVar29 & 0xff;
		else
			rightLane = uVar29 & 0xff;

		uVar9 = (u_char)_st->NumLanes;
		uVar23 = (uVar9 & 0xf) << 1;
		uVar17 = (u_char)(_st->NumLanes >> 6) & 1;
		uVar29 = uVar23;
		if (uVar17 < uVar23)
		{
			do {
				if (((((int)(u_char)_st->AILanes >> ((int)uVar17 / 2 & 0x1fU) & 1U) != 0) &&
					((uVar17 != 0 || ((_st->NumLanes & 0x40U) == 0)))) &&
					(((uVar9 & 0xffffff0f) * 2 - 1 != uVar17 || ((uVar9 & 0x80) == 0)))) 
				{
					uVar9 = uVar17;

					if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000)
					{
						uVar9 = (int)(u_char)_st->LaneDirs >> ((int)uVar17 / 2 & 0x1fU);
					}

					test555 = (uVar9 ^ 1) & 1;
					uVar29 = uVar17;

					if (test555 == 0) 
					{
						if (uVar7 != 0) 
							break;
					}
					else 
					{
						if (uVar7 == 0)
							break;
					}
				}

				uVar9 = (u_char)_st->NumLanes;
				uVar17 = uVar17 + 1;
				uVar29 = uVar23;
			} while ((int)uVar17 < (int)((uVar9 & 0xffffff0f) << 1));
		}

		if (uVar7 != 0)
			goto LAB_000246dc;

	LAB_000246ec:
		rightLane = uVar29 & 0xff;
	}
	else 
	{
		if ((currentRoadId & 0xffffe000U) != 0x4000)
			return 0;
	
		if (NumDriver2Curves <= (int)(currentRoadId & 0x1fffU))
			return 0;
	
		if (currentRoadId < 0)
			return 0;
	
		____cv = Driver2CurvesPtr + (currentRoadId - 0x4000);

		if (*(short *)&____cv->NumLanes == -0xff) 
		{
			uVar9 = (uint)cp->ai.c.currentLane;
		}
		else 
		{
			uVar9 = (int)(u_char)____cv->LaneDirs >> ((uint)(cp->ai.c.currentLane >> 1) & 0x1f);
		}

		uVar9 = uVar9 & 1;
		uVar26 = uVar9 << 0xb;

		if (*(short *)&____cv->NumLanes == -0xff) 
		{
			uVar29 = (uint)cp->ai.c.currentLane;
		}
		else 
		{
			uVar29 = (int)(u_char)____cv->LaneDirs >> ((uint)(cp->ai.c.currentLane >> 1) & 0x1f);
		}

		tmpNewRoad[0] = (int)____cv->ConnectIdx[(uVar29 & 1) * 2];

		if (*(short *)&____cv->NumLanes == -0xff)
		{
			uVar29 = (uint)cp->ai.c.currentLane;
		}
		else 
		{
			uVar29 = (int)(u_char)____cv->LaneDirs >> ((uint)(cp->ai.c.currentLane >> 1) & 0x1f);
		}

		iVar22 = 2;

		if ((uVar29 & 1) != 0)
			iVar22 = 6;

		tmpNewRoad[1] = (int)*(short *)((int)____cv->ConnectIdx + iVar22);
		uVar25 = ((u_char)____cv->NumLanes & 0xf) * 2;
		uVar29 = uVar25;

		do {
			do {
				uVar29 = uVar29 - 1;
				uVar16 = uVar25;

				if ((int)uVar29 < 0) 
					goto LAB_000245c0;

			} while (((((int)(u_char)____cv->AILanes >> ((int)uVar29 / 2 & 0x1fU) & 1U) == 0) ||
				((uVar29 == 0 && ((____cv->NumLanes & 0x40U) != 0)))) ||
				((((u_char)____cv->NumLanes & 0xffffff0f) * 2 - 1 == uVar29 &&
				((____cv->NumLanes & 0x80U) != 0))));

			uVar16 = uVar29;

			if (*(short *)&____cv->NumLanes != -0xff) 
			{
				uVar16 = (int)(u_char)____cv->LaneDirs >> ((int)uVar29 / 2 & 0x1fU);
			}

			test42 = (uVar16 ^ 1) & 1;
			uVar16 = uVar29;
		} while (uVar9 == 0);
	LAB_000245c0:

		if (uVar9 == 0)
			leftLane = uVar16 & 0xff;
		else 
			rightLane = uVar16 & 0xff;

		uVar25 = (u_char)____cv->NumLanes;
		uVar20 = (uVar25 & 0xf) << 1;
		uVar16 = (u_char)(____cv->NumLanes >> 6) & 1;
		uVar29 = uVar20;

		if (uVar16 < uVar20) 
		{
			do {
				if (((((int)(u_char)____cv->AILanes >> ((int)uVar16 / 2 & 0x1fU) & 1U) != 0) && ((uVar16 != 0 || ((____cv->NumLanes & 0x40U) == 0)))) &&
					(((uVar25 & 0xffffff0f) * 2 - 1 != uVar16 || ((uVar25 & 0x80) == 0)))) 
				{
					uVar29 = uVar16;

					if (*(short *)&____cv->NumLanes != -0xff)
					{
						uVar29 = (int)(u_char)____cv->LaneDirs >> ((int)uVar16 / 2 & 0x1fU);
					}

					test555 = (uVar29 ^ 1) & 1;
					uVar29 = uVar16;
					if (test555 == 0) 
					{
						if (uVar9 != 0) 
							break;
					}
					else 
					{
						if (uVar9 == 0) 
							break;
					}
				}
				uVar25 = (u_char)____cv->NumLanes;
				uVar16 = uVar16 + 1;
				uVar29 = uVar20;
			} while ((int)uVar16 < (int)((uVar25 & 0xffffff0f) << 1));
		}

		if (uVar9 == 0)
			goto LAB_000246ec;

	LAB_000246dc:
		leftLane = uVar29 & 0xff;
	}

	iVar22 = tmpNewRoad[0];
	newLane = -1;

	if ((((tmpNewRoad[0] & 0xffffe000U) != 0x2000) || (NumDriver2Junctions <= (int)(tmpNewRoad[0] & 0x1fffU))) || (tmpNewRoad[0] < 0))
	{
		iVar22 = 0;

		if (turnAngle == NULL)
			goto LAB_00026928;

		*turnAngle = 0;
		newExit = -1;

		do {
			piVar25 = tmpNewLane + iVar22;
			local_a1_7136 = tmpNewRoad[iVar22];

			if (local_a1_7136 == -1)
			{
				laneFit[iVar22] = 666;
			}
			else
			{
				if ((((local_a1_7136 & 0xffffe000U) == 0) && ((int)(local_a1_7136 & 0x1fffU) < NumDriver2Straights)) && (-1 < local_a1_7136))
				{
					___st = Driver2StraightsPtr + local_a1_7136;
					tmpStr[iVar22] = ___st;
					uVar9 = (uint)(ushort)___st->angle & 0xfff;
					uVar29 = (u_char)___st->NumLanes & 0xffffff0f;
					test555 = (oldNode->x - ___st->Midx) * (int)rcossin_tbl[uVar9 * 2 + 1] - (oldNode->z - ___st->Midz) * (int)rcossin_tbl[uVar9 * 2];
					test42 = uVar29 - (FIXED(test555) + 512 >> 9);
					*piVar25 = test42;
					unaff_s8 = uVar29 * 2;
					uVar29 = ((u_char)___st->NumLanes & 0xffffff0f) * 2;
					uVar9 = uVar29;

					uVar25 = uVar29;

					do {
						do {
							uVar9 = uVar9 - 1;

							if ((int)uVar9 < 0) 
								goto LAB_00025e00; // break

						} while (((((int)(u_char)___st->AILanes >> ((int)uVar9 / 2 & 0x1fU) & 1U) == 0) || ((uVar9 == 0 && ((___st->NumLanes & 0x40U) != 0)))) ||
								((((u_char)___st->NumLanes & 0xffffff0f) * 2 - 1 == uVar9 && ((___st->NumLanes & 0x80U) != 0))));

						uVar25 = uVar9;

						if ((*(uint *)(___st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
						{
							uVar25 = (int)(u_char)___st->LaneDirs >> ((int)uVar9 / 2 & 0x1fU);
						}

						test42 = (uVar25 ^ 1) & 1;
						uVar25 = uVar9;
					} while ((((int)oldNode->dir - (int)___st->angle) + 0x400U & 0x800) == 0);

				LAB_00025e00:
					if (uVar25 == 0)	// [A] temporary dirty hack
						uVar25++;

					if ((uVar25 == 0) || (unaff_s8 <= (int)uVar25))
					{
						laneFit[iVar22] = 666;
						goto LAB_00025f34; // continue
					}
				}
				else
				{
					___cv = Driver2CurvesPtr + tmpNewRoad[iVar22] + -0x4000;
					tmpCrv[iVar22] = ___cv;
					iVar23 = oldNode->x - ___cv->Midx;
					iVar26 = oldNode->z - ___cv->Midz;
					unaff_s8 = ((u_char)___cv->NumLanes & 0xffffff0f) * 2;
					lVar17 = SquareRoot0(iVar23 * iVar23 + iVar26 * iVar26);
					*piVar25 = (lVar17 >> 9) + (u_char)___cv->inside * -2;
				}

				iVar26 = unaff_s8 + -1;
				test123 = *piVar25;
				iVar23 = test123;

				if ((-1 < test123) && (iVar23 = test123 - iVar26, test123 <= iVar26)) 
				{
					iVar23 = 0;
				}

				laneFit[iVar22] = iVar23;

				if (iVar26 <= *piVar25)
					*piVar25 = iVar26;

				newExit = iVar22;
				if (*piVar25 < 0)
					*piVar25 = 0;

			}
		LAB_00025f34:
			iVar22 = iVar22 + 1;
		} while (iVar22 < 2);

		if ((newExit == -1) || (laneFit[newExit] == 666))
			goto LAB_00026928;

		iVar23 = laneFit[0];

		if (laneFit[0] < 0)
			iVar23 = -laneFit[0];

		iVar26 = laneFit[1];

		if (laneFit[1] < 0)
			iVar26 = -laneFit[1];

		newExit = (uint)(iVar23 < iVar26) ^ 1;
		uVar29 = tmpNewRoad[newExit];
		uVar9 = tmpNewLane[newExit];

		if (cp->ai.c.ctrlState != 7) 
		{
			if ((((uVar29 & 0xffffe000) == 0) && ((int)(uVar29 & 0x1fff) < NumDriver2Straights)) && (-1 < (int)uVar29)) 
			{
				__st = Driver2StraightsPtr + uVar29;
				uVar25 = ((int)oldNode->dir - (int)__st->angle) + 0x400U & 0x800;
				test123 = uVar25;// direction;

				if ((*(uint *)(__st->ConnectIdx + 3) & 0xffff0000) == 0xff010000)
				{
					if ((uVar9 & 1) == 0)
						goto LAB_00026064;
				LAB_00026074:
					if (uVar25 != 0)
						goto LAB_00026318;
				}
				else 
				{
					if (((int)(u_char)__st->LaneDirs >> ((int)uVar9 / 2 & 0x1fU) & 1U) != 0)
						goto LAB_00026074;
				LAB_00026064:
					if (uVar25 == 0)
						goto LAB_00026318;
				}

				uVar16 = (u_char)__st->NumLanes;
				uVar27 = (uVar16 & 0xf) * 2;
				uVar20 = uVar27;

				do {
					while (true) 
					{
						do {
							uVar20 = uVar20 - 1;
							if ((int)uVar20 < 0) goto LAB_0002616c;
						} while (((((int)(u_char)__st->AILanes >> ((int)uVar20 / 2 & 0x1fU) & 1U ) == 0) || ((uVar20 == 0 && ((__st->NumLanes & 0x40U) != 0)))) ||
							(((uVar16 & 0xffffff0f) * 2 - 1 == uVar20 && ((uVar16 & 0x80) != 0))));

						uVar16 = uVar20;

						if ((*(uint *)(__st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
						{
							uVar16 = (int)(u_char)__st->LaneDirs >> ((int)uVar20 / 2 & 0x1fU);
						}

						test42 = (uVar16 ^ 1) & 1;

						if (test42 == 0) 
							break;

						if (uVar25 == 0) 
							goto LAB_00026154;

						uVar16 = (u_char)__st->NumLanes;
					}
					uVar16 = (u_char)__st->NumLanes;
				} while (uVar25 == 0);

			LAB_00026154:
				uVar16 = (u_char)__st->NumLanes;
				uVar27 = uVar20;
			LAB_0002616c:

				if ((int)uVar27 < 0) 
					uVar27 = 42;

				uVar24 = (uVar16 & 0xf) << 1;
				uVar19 = uVar16 >> 6 & 1;
				uVar20 = uVar24;

				if (uVar19 < uVar24) 
				{
					do {
						uVar20 = uVar19;
						if (((((int)(u_char)__st->AILanes >> ((int)uVar20 / 2 & 0x1fU) & 1U) != 0) && ((uVar20 != 0 || ((__st->NumLanes & 0x40U) == 0)))) &&
							(((uVar16 & 0xffffff0f) * 2 - 1 != uVar20 || ((uVar16 & 0x80) == 0)))) 
						{
							uVar16 = uVar20;

							if ((*(uint *)(__st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
							{
								uVar16 = (int)(u_char)__st->LaneDirs >> ((int)uVar20 / 2 & 0x1fU);
							}

							test555 = (uVar16 ^ 1) & 1;
							if (test555 == 0)
							{
								if (uVar25 != 0)
									break;
							}
							else 
							{
								if (uVar25 == 0) 
									break;
							}
						}
						uVar16 = (u_char)__st->NumLanes;
						uVar19 = uVar20 + 1;
						uVar20 = uVar24;
					} while ((int)uVar19 < (int)((uVar16 & 0xffffff0f) << 1));
				}

				if (unaff_s8 <= (int)uVar20)
					uVar20 = 42;

				iVar23 = uVar27 - uVar9;

				if ((uVar27 == 42) && (uVar20 == 42))
					goto LAB_00026928;

				if (iVar23 < 0) 
					iVar23 = uVar9 - uVar27;

				if ((int)(uVar20 - uVar9) < 0) 
				{
					if (iVar23 <= (int)(uVar9 - uVar20))
					{
						uVar20 = uVar27;
					}
				}
				else 
				{
					if (iVar23 <= (int)(uVar20 - uVar9)) 
					{
						uVar20 = uVar27;
					}
				}
				puVar15 = &laneFit[iVar22];
				*puVar15 = uVar20;
				uVar25 = unaff_s8 - 1;

				if (-1 < (int)uVar20) 
				{
					if ((int)uVar25 < (int)uVar20) 
					{
						*puVar15 = uVar20 - uVar25;
					}
					else 
					{
						*puVar15 = 0;
					}
				}

				uVar9 = uVar20;
				if ((int)uVar25 <= (int)uVar20)
					uVar9 = uVar25;

				if ((int)uVar9 < 0) 
					uVar9 = 0;
			}
		LAB_00026318:
			if ((((uVar29 & 0xffffe000) == 0x4000) && ((int)(uVar29 & 0x1fff) < NumDriver2Curves)) && (-1 < (int)uVar29)) 
			{
				sVar1 = oldNode->dir;
				__cv = Driver2CurvesPtr + (uVar29 - 0x4000);
				lVar17 = ratan2(oldNode->x - __cv->Midx, oldNode->z - __cv->Midz);
				bVar3 = (int)(((sVar1 - lVar17) + 0x800U & 0xfff) - 0x800) < 1;

				if (*(short *)&__cv->NumLanes == -0xff)
				{
					if ((uVar9 & 1) == 0)
						goto LAB_000263fc;
				LAB_0002640c:
					if (bVar3)
						goto LAB_0002669c;
				}
				else 
				{
					if (((int)(u_char)__cv->LaneDirs >> ((int)uVar9 / 2 & 0x1fU) & 1U) != 0)
						goto LAB_0002640c;
				LAB_000263fc:
					if (!bVar3)
						goto LAB_0002669c;
				}

				uVar25 = (u_char)__cv->NumLanes;
				uVar20 = (uVar25 & 0xf) * 2;
				uVar16 = uVar20;

				do {
					while (true)
					{
						do {
							uVar16 = uVar16 - 1;

							if ((int)uVar16 < 0)
								goto LAB_000264fc;

						} while (((((int)(u_char)__cv->AILanes >> ((int)uVar16 / 2 & 0x1fU) & 1U) == 0) || ((uVar16 == 0 && ((__cv->NumLanes & 0x40U) != 0)))) ||
							(((uVar25 & 0xffffff0f) * 2 - 1 == uVar16 && ((uVar25 & 0x80) != 0))));

						uVar25 = uVar16;

						if (*(short *)&__cv->NumLanes != -0xff) 
						{
							uVar25 = (int)(u_char)__cv->LaneDirs >> ((int)uVar16 / 2 & 0x1fU);
						}

						test42 = (uVar25 ^ 1) & 1;
						if (test42 == 0) 
							break;

						if (!bVar3) 
							goto LAB_000264e4;

						uVar25 = (u_char)__cv->NumLanes;
					}
					uVar25 = (u_char)__cv->NumLanes;
				} while (!bVar3);

			LAB_000264e4:
				uVar25 = (u_char)__cv->NumLanes;
				uVar20 = uVar16;

			LAB_000264fc:
				if ((int)uVar20 < 0)
					uVar20 = 42;

				uVar28 = (uVar25 & 0xf) << 1;
				uVar27 = uVar25 >> 6 & 1;
				uVar16 = uVar28;

				if (uVar27 < uVar28)
				{
					do {
						uVar16 = uVar27;
						if (((((int)(u_char)__cv->AILanes >> ((int)uVar16 / 2 & 0x1fU) & 1U) !=
							0) && ((uVar16 != 0 || ((__cv->NumLanes & 0x40U) == 0)))) &&
							(((uVar25 & 0xffffff0f) * 2 - 1 != uVar16 || ((uVar25 & 0x80) == 0)))) {
							uVar25 = uVar16;

							if (*(short *)&__cv->NumLanes != -0xff)
							{
								uVar25 = (int)(u_char)__cv->LaneDirs >> ((int)uVar16 / 2 & 0x1fU);
							}

							test555 = (uVar25 ^ 1) & 1;

							if (test555 == 0) 
							{
								if (bVar3)
									break;
							}
							else 
							{
								if (!bVar3) 
									break;
							}
						}
						uVar25 = (u_char)__cv->NumLanes;
						uVar27 = uVar16 + 1;
						uVar16 = uVar28;
					} while ((int)uVar27 < (int)((uVar25 & 0xffffff0f) << 1));
				}

				if (unaff_s8 <= (int)uVar16) 
					uVar16 = 42;

				iVar23 = uVar20 - uVar9;

				if ((uVar20 == 42) && (uVar16 == 42))
					goto LAB_00026928;

				if (iVar23 < 0) 
				{
					iVar23 = uVar9 - uVar20;
				}

				if ((int)(uVar16 - uVar9) < 0)
				{
					if (iVar23 <= (int)(uVar9 - uVar16)) 
					{
						uVar16 = uVar20;
					}
				}
				else 
				{
					if (iVar23 <= (int)(uVar16 - uVar9)) 
					{
						uVar16 = uVar20;
					}
				}

				puVar21 = &laneFit[iVar22];
				*puVar21 = uVar16;
				uVar25 = unaff_s8 - 1;

				if (-1 < (int)uVar16) 
				{
					if ((int)uVar25 < (int)uVar16) 
					{
						*puVar21 = uVar16 - uVar25;
					}
					else 
					{
						*puVar21 = 0;
					}
				}

				uVar9 = uVar16;

				if ((int)uVar25 <= (int)uVar16)
					uVar9 = uVar25;

				if ((int)uVar9 < 0)
					uVar9 = 0;
	
			}
		LAB_0002669c:
			if (laneFit[newExit] != 0) 
			{
				iVar22 = (oldNode - cp->ai.c.targetRoute) + 1;
				cp->ai.c.turnNode = iVar22;

				if (0xc < iVar22)
					cp->ai.c.turnNode = 0;

				bVar7 = (laneFit[newExit] >> 0x18);

				if ((((uVar29 & 0xffffe000) == 0) && ((int)(uVar29 & 0x1fff) < NumDriver2Straights)) && (-1 < (int)uVar29)) 
				{
					if ((*(uint *)(tmpStr[newExit]->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
					{
						bVar1 = (u_char)tmpStr[newExit]->LaneDirs;
						goto LAB_00026788;
					}
				LAB_00026774:
					bVar6 = (uVar9 ^ 1) & 1 ^ bVar7 >> 7;
				}
				else
				{
					if (*(short *)&tmpCrv[newExit]->NumLanes == -0xff)
						goto LAB_00026774;

					bVar1 = (u_char)tmpCrv[newExit]->LaneDirs;
				LAB_00026788:
					bVar6 = (((int)(u_char)bVar1 >> ((int)uVar9 / 2 & 0x1fU)) ^ 1) & 1 ^bVar7 >> 7;
				}

				cp->ai.c.turnDir = bVar6;
			}
		}
		goto LAB_000267a4;
	}

	numExits = 0;
	cp->ai.c.changeLaneCount = 0;
	jn = Driver2JunctionsPtr + iVar22 + -0x2000;

	if ((int)jn->ExitIdx[0] == currentRoadId) 
	{
		iVar23 = 0;
	}
	else 
	{
		iVar22 = 1;
		do {
			iVar26 = iVar22;
			iVar23 = -1;
			if (3 < iVar26) break;
			iVar22 = iVar26 + 1;
			iVar23 = iVar26;
		} while ((int)jn->ExitIdx[iVar26] != currentRoadId);
	}

	if (iVar23 == -1) 
		goto LAB_00026928;

	iVar22 = 1;
	iVar26 = 0;
	do {
		iVar19 = iVar22;
		iVar12 = iVar23 + iVar19;
		iVar22 = iVar12;

		iVar22 = (iVar12 + (iVar22 >> 2) * -4) * 0x1000000;
		iVar30 = iVar22 >> 0x18;
		puVar20 = (short *)(jn->ExitIdx + iVar30);
		bVar3 = false;

		if (*puVar20 != -1) 
		{
			iVar18 = 0;
			iVar13 = (iVar30 + 4) - iVar23;
			iVar30 = iVar13;

			iVar13 = iVar13 + (iVar30 >> 2) * -4;

			if (iVar13 == 1) 
			{
				iVar18 = -0x400;
			}
			else if (iVar13 == 2)
			{
				iVar18 = 0;
			}
			else if (iVar13 == 3)
			{
				iVar18 = 0x400;
			}

			*turnAngle = iVar18;

			test123 = 666;
			test555 = 666;
			test42 = 666;
			uVar3 = *puVar20;
			iVar18 = oldNode->dir + iVar18;

			if ((((uVar3 & 0xe000) == 0) && ((int)((uint)uVar3 & 0x1fff) < NumDriver2Straights)) && (-1 < (int)(short)uVar3))
			{
				tmpSt = Driver2StraightsPtr + (int)(short)uVar3;
				iVar30 = *turnAngle;
				uVar9 = (iVar18 - tmpSt->angle) + 1024 & 0x800;// [A] temporary hack

				if (uVar9 == 0) 
					iVar30 = -iVar30;

				if (iVar30 == 0) 
				{
					if (uVar9 == uVar26) 
					{
						newLane = (cp->ai.c.currentLane);
					}
					else 
					{
						newLane = ((u_char)tmpSt->NumLanes & 0xffffff0f) * 2 - ((uint)cp->ai.c.currentLane + 1);
						if (newLane == 0) // [A] temporary hack
							newLane++;
					}

					if ((uVar9 == 0) || (((int)(u_char)tmpSt->AILanes >> (newLane / 2 & 0x1fU) & 1U) == 0))
					{
						newLane = -1;
					}
				}
				else if (iVar30 == -0x400)
				{
					uVar29 = (u_char)tmpSt->NumLanes;
					uVar16 = (uVar29 & 0xffffff0f) << 1;
					uVar25 = (u_char)(tmpSt->NumLanes >> 6) & 1;
					newLane = uVar16;
					if (uVar25 < uVar16) 
					{
						do {
							if (((((int)(u_char)tmpSt->AILanes >>
								((int)uVar25 / 2 & 0x1fU) & 1U) != 0) &&
								((uVar25 != 0 || ((tmpSt->NumLanes & 0x40U) == 0)))) &&
								(((uVar29 & 0xffffff0f) * 2 - 1 != uVar25 ||
								((uVar29 & 0x80) == 0)))) 
							{
								uVar29 = uVar25;
								if ((*(uint *)(tmpSt->ConnectIdx + 3) & 0xffff0000) != 0xff010000)
								{
									uVar29 = (int)(u_char)tmpSt->LaneDirs >> ((int)uVar25 / 2 & 0x1fU);
								}

								test555 = (uVar29 ^ 1) & 1;
								newLane = uVar25;

								if (test555 == 0) 
								{
									if (uVar9 != 0)
										break;
								}
								else
								{
									if (uVar9 == 0)
										break;
								}
							}
							uVar29 = (u_char)tmpSt->NumLanes;
							uVar25 = uVar25 + 1;
							newLane = uVar16;
						} while ((int)uVar25 < (int)((uVar29 & 0xffffff0f) << 1));
					}
				}
				else if (iVar30 == 0x400)
				{
					uVar25 = ((u_char)tmpSt->NumLanes & 0xffffff0f) << 1;
					uVar29 = uVar25;
					newLane = uVar25;
					do {
						do {
							uVar29 = uVar29 - 1;
							

							if ((int)uVar29 < 0)
								goto LAB_00024be8;

						} while (((((int)(u_char)tmpSt->AILanes >>
							((int)uVar29 / 2 & 0x1fU) & 1U) == 0) || ((uVar29 == 0 && ((tmpSt->NumLanes & 0x40U) != 0)))) ||
							((((u_char)tmpSt->NumLanes & 0xffffff0f) * 2 - 1 == uVar29 && ((tmpSt->NumLanes & 0x80U) != 0))));

						uVar16 = uVar29;

						if ((*(uint *)(tmpSt->ConnectIdx + 3) & 0xffff0000) != 0xff010000)
						{
							uVar16 = (int)(u_char)tmpSt->LaneDirs >> ((int)uVar29 / 2 & 0x1fU);
						}

						test42 = (uVar16 ^ 1) & 1;
						newLane = uVar29;

					} while (uVar9 == 0);
				}
			LAB_00024be8:
				if (-1 < newLane)
				{
					uVar9 = (u_char)tmpSt->NumLanes;
					iVar30 = (uVar9 & 0xffffff0f) << 1;

					if (newLane < iVar30) 
					{
						bVar7 = tmpSt->AILanes;
						iVar15 = newLane - (newLane >> 0x1f);
					LAB_00024fa4:
						bVar3 = false;
						if (((((int)(uint)bVar7 >> (iVar15 >> 1 & 0x1fU) & 1U) != 0) &&
							((newLane != 0 || ((uVar9 & 0x40) == 0)))) &&
							((iVar30 - 1U != newLane || ((uVar9 & 0x80) == 0))))
						{
							bVar3 = true;
						}
					}
				}
			}
			else
			{
				tmpCv = Driver2CurvesPtr + (int)(short)*puVar20 + -0x4000;
				lVar17 = ratan2(oldNode->x - tmpCv->Midx, oldNode->z - tmpCv->Midz);
				bVar3 = false;
				bVar4 = (int)(((iVar18 - lVar17) + 0x800U/* & 0xfff*/) - 0x800) < 1;
				iVar30 = *turnAngle;

				if (!bVar4)
					iVar30 = -iVar30;

				if (iVar30 == 0) 
				{
					if ((uint)bVar4 << 0xb == uVar26) 
					{
						newLane = (cp->ai.c.currentLane);
					}
					else 
					{
						newLane = ((u_char)tmpCv->NumLanes & 0xffffff0f) * 2 - ((uint)cp->ai.c.currentLane + 1);
						if (newLane == 0)// [A] temporary hack
							newLane++;
					}

					if ((!bVar4) || (((int)(u_char)tmpCv->AILanes >> (newLane / 2 & 0x1fU) & 1U) == 0))
					{
						newLane = -1;
					}
				}
				else if (iVar30 == -0x400)
				{
					uVar9 = (u_char)tmpCv->NumLanes;
					uVar25 = (uVar9 & 0xffffff0f) << 1;
					uVar29 = (u_char)(tmpCv->NumLanes >> 6) & 1;
					newLane = uVar25;

					if (uVar29 < uVar25)
					{
						do {
							if (((((int)(u_char)tmpCv->AILanes >>
								((int)uVar29 / 2 & 0x1fU) & 1U) != 0) &&
								((uVar29 != 0 || ((tmpCv->NumLanes & 0x40U) == 0)))) &&
								(((uVar9 & 0xffffff0f) * 2 - 1 != uVar29 ||
								((uVar9 & 0x80) == 0)))) 
							{
								uVar9 = uVar29;

								if (*(short *)&tmpCv->NumLanes != -0xff)
								{
									uVar9 = (int)(u_char)tmpCv->LaneDirs >> ((int)uVar29 / 2 & 0x1fU);
								}

								test555 = (uVar9 ^ 1) & 1;
								newLane = uVar29;

								if (test555 == 0) 
								{
									if (bVar4)
										break;
								}
								else 
								{
									if (!bVar4) 
										break;
								}
							}
							uVar9 = (u_char)tmpCv->NumLanes;
							uVar29 = uVar29 + 1;
							newLane = uVar25;
						} while ((int)uVar29 < (int)((uVar9 & 0xffffff0f) << 1));
					}
				}
				else if (iVar30 == 0x400)
				{
					uVar29 = ((u_char)tmpCv->NumLanes & 0xffffff0f) * 2;
					uVar9 = uVar29;
					newLane = uVar29;
					do {
						do {
							uVar9 = uVar9 - 1;
	
							if ((int)uVar9 < 0) 
								goto LAB_00024f78;

						} while (((((int)(u_char)tmpCv->AILanes >>
							((int)uVar9 / 2 & 0x1fU) & 1U) == 0) || ((uVar9 == 0 && ((tmpCv->NumLanes & 0x40U) != 0)))) ||
							((((u_char)tmpCv->NumLanes & 0xffffff0f) * 2 - 1 == uVar9 && ((tmpCv->NumLanes & 0x80U) != 0))));

						uVar25 = uVar9;

						if (*(short *)&tmpCv->NumLanes != -0xff) 
						{
							uVar25 = (int)(u_char)tmpCv->LaneDirs >> ((int)uVar9 / 2 & 0x1fU);
						}

						test42 = (uVar25 ^ 1) & 1;
						newLane = uVar9;
					} while (!bVar4);
				}

			LAB_00024f78:
				if (-1 < newLane) 
				{
					uVar9 = (u_char)tmpCv->NumLanes;
					iVar30 = (uVar9 & 0xffffff0f) << 1;
					if (newLane < iVar30) 
					{
						bVar7 = tmpCv->AILanes;
						iVar15 = newLane - (newLane >> 0x1f);
						goto LAB_00024fa4;
					}
				}
			}
		}

		if (bVar3) 
		{
			validExitIdx[iVar26] = (short)(iVar22 >> 0x18);
			numExits = numExits + 1;
		}
		else
		{
			validExitIdx[iVar26] = 42;
		}

		iVar22 = iVar19 + 1;
		iVar26 = iVar19;
	} while (iVar19 < 3);

	if ((iVar23 < 0) || (numExits < 1)) 
		goto LAB_00026928;

	if ((leftLane != rightLane) && (numExits != 1)) 
	{
		uVar9 = (uint)cp->ai.c.currentLane;
		if (uVar9 == leftLane)
		{
			validExitIdx[2] = 42;
		}
		else
		{
			if (uVar9 == rightLane)
			{
				validExitIdx[0] = 42;
			}
			else if (validExitIdx[1] != 42)
			{
				validExitIdx[2] = 42;
				validExitIdx[0] = 42;
			}
		}
	}
	lVar9 = Random2(0);
	sVar2 = validExitIdx[lVar9 % 3];
	pbVar21 = &cp->ai.c.ctrlState;
	iVar22 = lVar9 % 3;

	while (sVar2 == 42)
	{
		iVar14 = 0;

		if (iVar22 < 2)
			iVar14 = iVar22 + 1;

		sVar2 = validExitIdx[iVar14];
		iVar22 = iVar14;
	}

	iVar22 = (int)validExitIdx[iVar22];
	uVar29 = (jn->ExitIdx[iVar22]);
	iVar26 = 0;

	if (turnAngle != NULL) 
	{
		iVar19 = (iVar22 + 4) - iVar23;
		iVar10 = iVar19;

		iVar19 = iVar19 + (iVar10 >> 2) * -4;

		if (iVar19 == 1) 
		{
			iVar26 = -0x400;
		}
		else if (((1 < iVar19) && (iVar19 != 2)) && (iVar19 == 3))
		{
			iVar26 = 0x400;
		}

		test42 = iVar23;
		test555 = iVar22;
		*turnAngle = iVar26;
	}

	uVar9 = -1;
	uVar25 = 0;
	iVar22 = *turnAngle;
	uVar2 = *(ushort *)&jn->flags;

	do {
		if ((int)jn->ExitIdx[0] == currentRoadId) 
		{
			uVar9 = uVar25;
		}

		uVar25 = uVar25 + 1;
		jn = (DRIVER2_JUNCTION *)(jn->ExitIdx + 1);
	} while ((int)uVar25 < 4);

	if (*pbVar21 != 8) 
	{
		*pbVar21 = 0;

		if ((uVar2 & 1) == 0) 
		{
			bVar3 = false;

			if ((uVar9 == 0) || (uVar9 == 2)) 
			{
				bVar3 = true;
			}

			if ((uVar2 & 2) == 0) 
			{
				bVar7 = 4;

				if (!bVar3)
					goto LAB_000252b4;
			LAB_000252ac:
				bVar7 = 6;

				if (iVar22 == 0)
					goto LAB_000252bc;

				goto LAB_000252b4;
			}
			bVar7 = 4;

			if (!bVar3) 
				goto LAB_000252ac;

			cp->ai.c.ctrlNode = oldNode;
		}
		else 
		{
			cp->ai.c.trafficLightPhaseId = (uVar9 & 1);
			bVar7 = 1;

			if (junctionLightsPhase[uVar9 & 1] == 3)
				goto LAB_000252ac;

		LAB_000252b4:
			cp->ai.c.ctrlNode = oldNode;
		}

		*pbVar21 = bVar7;
	}

LAB_000252bc:
	iVar22 = *turnAngle;
	iVar11 = oldNode->dir + iVar22;

	if (((((uVar29 & 0xffffe000) != 0) || (NumDriver2Straights <= (int)(uVar29 & 0x1fff))) &&
		(((uVar29 & 0xffffe000) != 0x4000 || (NumDriver2Curves <= (int)(uVar29 & 0x1fff))))) || ((int)uVar29 < 0)) 
		goto LAB_00026928;

	if (((uVar29 & 0xffffe000) == 0) && ((int)(uVar29 & 0x1fff) < NumDriver2Straights))
	{
		_st = Driver2StraightsPtr + uVar29;
		uVar25 = (iVar11 - _st->angle) + 0x400U & 0x800;
		uVar9 = ((u_char)_st->NumLanes & 0xf) * 2;

		if (uVar25 == 0) 
		{
			iVar22 = -iVar22;
		}

		if (iVar22 == 0) 
		{
			if (uVar25 == uVar26)
			{
				newLane = (cp->ai.c.currentLane);
			}
			else 
			{
				newLane = uVar9 - ((uint)cp->ai.c.currentLane + 1);
				if (newLane == 0)// [A] temporary hack
					newLane++;
			}

			bVar5 = uVar25 == 0;
			if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) == 0xff010000) 
			{
				if ((newLane & 1U) == 0) {
				LAB_00025514:
					if (!bVar5)
					{
						newLane = -1;
						goto LAB_0002564c;
					}
				}
				else {
					if (bVar5) 
					{
						newLane = -1;
						goto LAB_0002564c;
					}
				}
			LAB_0002552c:
				if (((int)(u_char)_st->AILanes >> (newLane / 2 & 0x1fU) & 1U) != 0)
					goto LAB_0002564c;
			}
			else 
			{
				if (((int)(u_char)_st->LaneDirs >> (newLane / 2 & 0x1fU) & 1U) == 0)
					goto LAB_00025514;
				if (!bVar5)
					goto LAB_0002552c;
			}
			newLane = -1;
		}
		else 
		{
			if (iVar22 < 1)
			{
				if ((iVar22 == -0x400) && (uVar16 = (uint)(_st->NumLanes >> 6) & 1, newLane = uVar9, uVar16 < uVar9))
				{
					do {
						if (((((int)(u_char)_st->AILanes >> ((int)uVar16 / 2 & 0x1fU) & 1U) != 0
							) && ((uVar16 != 0 || ((_st->NumLanes & 0x40U) == 0)))) &&
							((((u_char)_st->NumLanes & 0xffffff0f) * 2 - 1 != uVar16 ||
							((_st->NumLanes & 0x80U) == 0)))) 
						{
							uVar20 = uVar16;

							if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
							{
								uVar20 = (int)(u_char)_st->LaneDirs >> ((int)uVar16 / 2 & 0x1fU);
							}

							test555 = (uVar20 ^ 1) & 1;
							newLane = uVar16;
							if (test555 == 0) 
							{
								if (uVar25 != 0) 
									break;
							}
							else 
							{
								if (uVar25 == 0) 
									break;
							}
						}
						uVar16 = uVar16 + 1;
						newLane = uVar9;
					} while ((int)uVar16 < (int)(((u_char)_st->NumLanes & 0xffffff0f) << 1));
				}
			}
			else 
			{
				uVar16 = uVar9;
				if (iVar22 == 0x400)
				{
					newLane = uVar9;

					do {
						do {
							uVar16 = uVar16 - 1;

							if ((int)uVar16 < 0)
								goto LAB_0002564c;

						} while (((((int)(u_char)_st->AILanes >> ((int)uVar16 / 2 & 0x1fU) & 1U) == 0) || ((uVar16 == 0 && ((_st->NumLanes & 0x40U) != 0)))) ||
							((((u_char)_st->NumLanes & 0xffffff0f) * 2 - 1 == uVar16 && ((_st->NumLanes & 0x80U) != 0))));

						uVar20 = uVar16;

						if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
						{
							uVar20 = (int)(u_char)_st->LaneDirs >> ((int)uVar16 / 2 & 0x1fU);
						}

						test42 = (uVar20 ^ 1) & 1;
						newLane = uVar16;
					} while (uVar25 == 0);
				}
			}
		}

	LAB_0002564c:
		uVar9 = newLane;
		if (*turnAngle != 0) 
		{
			if (uVar9 - 1 == newLane)
			{
				uVar25 = newLane;
				if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000)
				{
					uVar25 = (int)(u_char)_st->LaneDirs >> (newLane / 2 & 0x1fU);
				}

				uVar16 = newLane;

				if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
				{
					uVar16 = (int)(u_char)_st->LaneDirs >> ((int)(newLane - 1U) / 2 & 0x1fU) ^ 1;
				}

				uVar9 = newLane - 1;
				if (((uVar25 ^ 1) & 1) == (uVar16 & 1))
					goto LAB_000267a4;
			}
			uVar9 = newLane;
			if (newLane == 0) 
			{
				uVar25 = 1;

				if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000)
				{
					uVar25 = ((u_char)_st->LaneDirs ^ 1) & 1;
				}

				if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000)
					goto LAB_00025ba4;

			LAB_00025b80:
				uVar16 = uVar9 + 1;
				if (uVar25 == ((uVar16 ^ 1) & 1)) 
					goto LAB_00025bc8;
			}
		}
	}
	else 
{
		uVar9 = newLane;
		if (((uVar29 & 0xffffe000) != 0x4000) || ((NumDriver2Curves <= (int)(uVar29 & 0x1fff) || ((int)uVar29 < 0))))
			goto LAB_000267a4;

		_cv = Driver2CurvesPtr + (uVar29 - 0x4000);
		lVar17 = ratan2(oldNode->x - _cv->Midx, oldNode->z - _cv->Midz);
		bVar3 = (int)(((iVar11 - lVar17) + 0x800U & 0xfff) - 0x800) < 1;
		iVar22 = *turnAngle;
		uVar9 = ((u_char)_cv->NumLanes & 0xf) * 2;

		if (!bVar3) 
			iVar22 = -iVar22;

		if (iVar22 == 0) 
		{

			if ((uint)bVar3 << 0xb == uVar26) 
			{
				newLane = (cp->ai.c.currentLane);
			}
			else 
			{
				newLane = uVar9 - ((uint)cp->ai.c.currentLane + 1);
				if (newLane == 0)// [A] temporary hack
					newLane++;
			}

			if (*(short *)&_cv->NumLanes == -0xff)
			{
				if ((newLane & 1U) == 0) {
				LAB_0002595c:
					if (bVar3) 
					{
						newLane = -1;
						goto LAB_00025a8c;
					}
				}
				else 
				{
					if (!bVar3) 
					{
						newLane = -1;
						goto LAB_00025a8c;
					}
				}
			LAB_00025974:
				if (((int)(u_char)_cv->AILanes >> (newLane / 2 & 0x1fU) & 1U) != 0)
					goto LAB_00025a8c;
			}
			else 
			{
				if (((int)(u_char)_cv->LaneDirs >> (newLane / 2 & 0x1fU) & 1U) == 0)
					goto LAB_0002595c;
				if (bVar3) goto LAB_00025974;
			}
			newLane = -1;
		}
		else 
		{
			if (iVar22 < 1) 
			{
				if ((iVar22 == -0x400) &&
					(uVar25 = (u_char)(_cv->NumLanes >> 6) & 1, newLane = uVar9, uVar25 < uVar9))
				{
					do {
						if (((((int)(u_char)_cv->AILanes >> ((int)uVar25 / 2 & 0x1fU) & 1U) != 0
							) && ((uVar25 != 0 || ((_cv->NumLanes & 0x40U) == 0)))) &&
							((((u_char)_cv->NumLanes & 0xffffff0f) * 2 - 1 != uVar25 ||
							((_cv->NumLanes & 0x80U) == 0)))) 
						{
							uVar16 = uVar25;
							if (*(short *)&_cv->NumLanes != -0xff) {
								uVar16 = (int)(u_char)_cv->LaneDirs >> ((int)uVar25 / 2 & 0x1fU);
							}
							test555 = (uVar16 ^ 1) & 1;
							newLane = uVar25;

							if (test555 == 0) 
							{
								if (bVar3)
									break;
							}
							else 
							{
								if (!bVar3)
									break;
							}
						}
						uVar25 = uVar25 + 1;
						newLane = uVar9;

					} while ((int)uVar25 < (int)(((uint)_cv->NumLanes & 0xffffff0f) << 1));
				}
			}
			else 
			{
				uVar25 = uVar9;
				if (iVar22 == 0x400) 
				{
					do {
						do {
							uVar25 = uVar25 - 1;
							newLane = uVar9;
							if ((int)uVar25 < 0) goto LAB_00025a8c;
						} while (((((int)(u_char)_cv->AILanes >> ((int)uVar25 / 2 & 0x1fU) & 1U) == 0) || ((uVar25 == 0 && ((_cv->NumLanes & 0x40U) != 0)))) ||
							((((u_char)_cv->NumLanes & 0xffffff0f) * 2 - 1 == uVar25 && ((_cv->NumLanes & 0x80U) != 0))));

						uVar16 = uVar25;

						if (*(short *)&_cv->NumLanes != -0xff) 
						{
							uVar16 = (int)(u_char)_cv->LaneDirs >> ((int)uVar25 / 2 & 0x1fU);
						}

						test42 = (uVar16 ^ 1) & 1;
						newLane = uVar25;
					} while (!bVar3);
				}
			}
		}

	LAB_00025a8c:
		uVar9 = newLane;

		if (*turnAngle != 0)
		{
			if (uVar9 - 1 == newLane) 
			{
				uVar25 = newLane;

				if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
				{
					uVar25 = (int)(u_char)_st->LaneDirs >> (newLane / 2 & 0x1fU);
				}

				uVar16 = newLane;

				if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
				{
					uVar16 = (int)(u_char)_st->LaneDirs >> ((int)(newLane - 1U) / 2 & 0x1fU) ^ 1;
				}

				uVar9 = newLane - 1;
				if (((uVar25 ^ 1) & 1) == (uVar16 & 1))
					goto LAB_000267a4;
			}
			uVar9 = newLane;
			if (newLane == 0) 
			{
				uVar25 = 1;

				if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
					uVar25 = ((u_char)_st->LaneDirs ^ 1) & 1;

				if ((*(uint *)(_st->ConnectIdx + 3) & 0xffff0000) == 0xff010000) 
					goto LAB_00025b80;

			LAB_00025ba4:
				uVar16 = newLane + 1;
				uVar9 = newLane;

				if (uVar25 == (((int)(u_char)_st->LaneDirs >> ((int)uVar16 / 2 & 0x1fU) ^ 1U) & 1))
				{
				LAB_00025bc8:
					uVar9 = uVar16;
				}
			}
		}
	}
LAB_000267a4:
	if ((int)uVar9 < 0) 
		goto LAB_00026928;

	cp->ai.c.currentLane = uVar9;

	if (startDist != NULL) 
	{
		iVar22 = uVar29 << 3;

		if (((uVar29 & 0xffffe000) == 0x4000) && (iVar22 = uVar29 * 8, (int)(uVar29 & 0x1fff) < NumDriver2Curves))
		{
			if ((int)uVar29 < 0)
			{
				iVar22 = uVar29 << 3;
				goto LAB_0002687c;
			}

			cv = Driver2CurvesPtr + (uVar29 - 0x4000);
			if (*(short *)&cv->NumLanes == -0xff)
			{
				if ((uVar9 & 1) == 0) 
				{
					uVar9 = 0;
				}
				else 
				{
				LAB_00026844:
					uVar9 = (int)cv->end - (int)cv->start & 0xfff;
				}
			}
			else 
			{
				if (((int)(u_char)cv->LaneDirs >> ((uint)(cp->ai.c.currentLane >> 1) & 0x1f) & 1U) != 0)
					goto LAB_00026844;
				uVar9 = 0;
			}
			*startDist = uVar9;
			bVar7 = cv->NumLanes;
		}
		else 
		{
		LAB_0002687c:
			st = (DRIVER2_STRAIGHT *)(&Driver2StraightsPtr->Midx + (iVar22 - uVar29));
			if ((*(uint *)(st->ConnectIdx + 3) & 0xffff0000) == 0xff010000)
			{
				test555 = 0;
				if ((cp->ai.c.currentLane & 1) != 0) 
				{
				LAB_000268e0:
					test555 = (st->length);
				}
			}
			else
			{
				test555 = 0;
				if (((int)(u_char)st->LaneDirs >> ((uint)(cp->ai.c.currentLane >> 1) & 0x1f) & 1U) != 0)
					goto LAB_000268e0;
			}

			test123 = test555;
			*startDist = test555;
			bVar7 = st->NumLanes;
		}
		cp->ai.c.maxSpeed = speedLimits[(u_char)(bVar7 >> 4) & 3];
	}

	if (-1 < uVar29)
		return uVar29;

LAB_00026928:
	cp->ai.c.thrustState = 3;
	cp->ai.c.ctrlState = 7;
	return 0;
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

// [D]
void InitNodeList(_CAR_DATA *cp, EXTRA_CIV_DATA *extraData)
{
	short sVar1;
	short uVar2;
	char *pPathType;
	long lVar3;
	long lVar4;
	
	int uVar5;
	int uVar6;

	int y;
	int x;

	DRIVER2_CURVE *curve;
	DRIVER2_STRAIGHT *straight;
	int curRoad;

	CIV_ROUTE_ENTRY* cr;
	cr = cp->ai.c.targetRoute;

	for(int i = 0; i < 13; i++)
	{
		cr->pathType = 127;
		cr->x = 0;
		cr->z = 0;
		cr++;
	}

	cr = &cp->ai.c.targetRoute[0];

	cr->pathType = 1;
	cr->x = cp->hd.where.t[0];
	cr->z = cp->hd.where.t[2];

	curRoad = cp->ai.c.currentRoad;


	if ((((curRoad & 0xffffe000U) == 0) && ((curRoad & 0x1fffU) < NumDriver2Straights)) && (-1 < curRoad))
	{
		straight = Driver2StraightsPtr + curRoad;

		y = cp->hd.where.t[0] - straight->Midx;
		x = cp->hd.where.t[2] - straight->Midz;

		lVar3 = ratan2(y, x);
		sVar1 = straight->angle;
		lVar4 = SquareRoot0(y * y + x * x);

		cr->distAlongSegment = (straight->length >> 1) + FIXED(rcossin_tbl[(sVar1 - lVar3 & 0xfffU) * 2 + 1] * lVar4);

		uVar5 = straight->angle & 0xfff;
		y = (straight->NumLanes & 0xf) * 0x200 + FIXED(-y * rcossin_tbl[uVar5 * 2 + 1] + x * rcossin_tbl[uVar5 * 2]);

		uVar5 = y >> 9;
		cp->ai.c.currentLane = uVar5;
		
		if (!IS_SINGLE_LANE(straight))
			uVar5 = (u_char)straight->LaneDirs >> ((cp->ai.c.currentLane >> 1) & 0x1f);
		if ((uVar5 & 1) == 0) 
			cr->dir = straight->angle;
		else
			cr->dir = straight->angle + 0x800U & 0xfff;
	}

	if ((((curRoad & 0xffffe000U) == 0x4000) && (curRoad & 0x1fffU) < NumDriver2Curves) && curRoad > -1) 
	{
		if (extraData == NULL) 
		{
			curve = Driver2CurvesPtr + curRoad - 0x4000;

			uVar5 = ratan2(cr->x- curve->Midx, cr->z - curve->Midz);

			uVar6 = (uVar5 & 0xfff) - curve->start;
			uVar5 = uVar6 & 0xf80;

			if ((9 < curve->inside) && (uVar5 = uVar6 & 0xfe0, curve->inside < 0x14))
				uVar5 = uVar6 & 0xfc0;

			cr->distAlongSegment = uVar5; 
			sVar1 = uVar5 + curve->start;

			if (curve->NumLanes == -1) 
				uVar5 = cp->ai.c.currentLane;
			else 
				uVar5 = (u_char)curve->LaneDirs >> ((cp->ai.c.currentLane >> 1) & 0x1f);

			uVar2 = sVar1 - 0x400;

			if ((uVar5 & 1) == 0)
				uVar2 = sVar1 + 0x400;

			cr->dir = uVar2;
		}
		else 
		{
			cr->distAlongSegment = extraData->distAlongSegment;
			cr->dir = extraData->angle;
		}
	}

	if (extraData != NULL) 
		cr->distAlongSegment = extraData->distAlongSegment;
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
				FIXED(distFromCentre * rcossin_tbl[(angle & 0xfffU) * 2]) +
				FIXED(sideShift * rcossin_tbl[(angle & 0xfffU) * 2 + 1]);

			*z = (straight->Midz +
				FIXED(distFromCentre * rcossin_tbl[(angle & 0xfffU) * 2 + 1])) -
				FIXED(sideShift * rcossin_tbl[(angle & 0xfffU) * 2]);

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

	*x = curve->Midx + FIXED(radius * rcossin_tbl[(angle & 0xfffU) * 2]);
	*z = curve->Midz + FIXED(radius * rcossin_tbl[(angle & 0xfffU) * 2 + 1]);
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

// [D]
int CheckChangeLanes(DRIVER2_STRAIGHT *straight, DRIVER2_CURVE *curve, int distAlongSegment, _CAR_DATA *cp, int tryToPark)
{
	unsigned char bVar1;
	bool bVar2;
	unsigned char bVar3;
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
	VECTOR pos;
	unsigned char canProceed;
	unsigned char turnRight;

	CDATA2D cd[2];

	bVar2 = false;
	bVar1 = cp->ai.c.currentLane;
	uVar12 = bVar1;

	if (cp->ai.c.ctrlState != 8 && cp->ai.c.changeLaneIndicateCount == 0)
	{
		if (straight == NULL) 
			bVar3 = curve->NumLanes;
		else 
			bVar3 = straight->NumLanes;

		uVar4 = ((uint)bVar3 & 0xf) * 2;
		lVar5 = Random2((int)straight);
		uVar13 = uVar12 + (lVar5 >> 7 & 2U) + 0xff & 0xff;

		if (tryToPark != 0) 
		{
			if (bVar1 == 1)
			{
				uVar13 = 0;
			}
			else if (uVar4 - 2 == uVar12)
			{
				uVar13 = uVar4 - 1 & 0xff;
			}
		}

		bVar3 = 0;
		uVar10 = (uVar12 ^ 1) & 1;

		do {
			if (bVar3 == 1)
				uVar13 = uVar12 * 2 - uVar13 & 0xff;

			if ((uVar13 == 0xff) || (uVar4 <= uVar13)) 
				goto LAB_000274bc;

			if ((gCurrentMissionNumber == 0x21) && (makeLimoPullOver != 0)) 
			{
			LAB_0002718c:
				if (straight != NULL) 
				{
					unaff_s5 = uVar10;

					if (!IS_SINGLE_LANE(straight))
						unaff_s5 = ((u_char)straight->LaneDirs >> ((bVar1 >> 1) & 0x1f) ^ 1U) & 1;

					uVar8 = uVar13;

					if (!IS_SINGLE_LANE(straight))
						uVar8 = (u_char)straight->LaneDirs >> (uVar13 >> 1 & 0x1f);

					if (((uVar8 ^ 1) & 1) != unaff_s5) 
						goto LAB_000274bc;
				}

				if (curve != NULL) 
				{
					unaff_s5 = uVar10;

					if (!IS_SINGLE_LANE(curve))
						unaff_s5 = ((u_char)curve->LaneDirs >> ((bVar1 >> 1) & 0x1f) ^ 1U) & 1;

					uVar8 = uVar13;

					if (!IS_SINGLE_LANE(curve))
						uVar8 = (u_char)curve->LaneDirs >> (uVar13 >> 1 & 0x1f);

					if (((uVar8 ^ 1) & 1) != unaff_s5) 
						goto LAB_000274bc;
				}

				if (cp->ai.c.ctrlNode == 0 && cp->ai.c.turnNode == -1)
				{
					bVar2 = true;
					turnRight = unaff_s5 != 0;

					if (uVar12 < uVar13) 
					{
						turnRight = !(bool)turnRight;
					}

					iVar6 = (cp->hd).direction;
					uVar8 = iVar6 - 0x400;

					if ((bool)turnRight != false) 
					{
						uVar8 = iVar6 + 0x400;
					}

					cd[0].x.vx = (cp->hd).oBox.location.vx + FIXED((int)rcossin_tbl[(uVar8 & 0xfff) * 2] * 0x200);
					cd[0].x.vz = (cp->hd).oBox.location.vz + FIXED((int)rcossin_tbl[(uVar8 & 0xfff) * 2 + 1] * 0x200);
					cd[0].length[0] = (int)(((cp->ap).carCos)->colBox).vz + 0x5d;
					cd[0].length[1] = (int)(((cp->ap).carCos)->colBox).vx;
					cd[0].theta = (cp->hd).direction;

					p_Var11 = car_data + 19;

					if (true)
					{
						do 
						{
							if ((p_Var11 != cp) && (p_Var11->controlType != 0)) 
							{
								pCVar7 = (p_Var11->ap).carCos;

								cd[1].length[0] = (int)(pCVar7->colBox).vz + 0x5d;
								cd[1].x.vx = (p_Var11->hd).oBox.location.vx;
								cd[1].length[1] = (int)(pCVar7->colBox).vx;
								cd[1].x.vz = (p_Var11->hd).oBox.location.vz;
								cd[1].theta = (p_Var11->hd).direction;

								iVar9 = ((cd[0].length[0] + cd[1].length[0]) * 3) / 2;
								iVar6 = cd[0].x.vx - cd[1].x.vx;

								if (iVar6 < 0) 
									iVar6 = cd[1].x.vx - cd[0].x.vx;

								if (iVar6 < iVar9)
								{
									iVar6 = cd[0].x.vz - cd[1].x.vz;

									if (iVar6 < 0)
										iVar6 = cd[1].x.vz - cd[0].x.vz;
	
									if ((iVar6 < iVar9) && bcollided2d(cd, 1) != 0)
									{
										bVar2 = false;
										break;
									}
								}
							}
							p_Var11 = p_Var11-1;
						} while (car_data <= p_Var11);
					}

					if (bVar2) 
						goto LAB_000274d8;
				}
			}
			else 
{
				if (tryToPark == 0)
				{
					if (((straight == NULL) ||
						((((straight->AILanes >> (uVar13 >> 1 & 0x1f) & 1U) != 0 &&
						((uVar13 != 0 || ((straight->NumLanes & 0x40U) == 0)))) &&
						(((straight->NumLanes & 0xf) * 2 - 1 != uVar13 ||
						((straight->NumLanes & 0x80U) == 0)))))) &&
						((curve == NULL || ((((curve->AILanes >> (uVar13 >> 1 & 0x1f) & 1U) != 0 &&
						((uVar13 != 0 || ((curve->NumLanes & 0x40U) == 0)))) &&
						(((curve->NumLanes & 0xf) * 2 - 1 != uVar13 ||
						((curve->NumLanes & 0x80U) == 0)))))))) 
						goto LAB_0002718c;
				}
				else 
				{
					if (((straight == NULL) || ((straight->AILanes >> (uVar13 >> 1 & 0x1f) & 1U) != 0)) &&
						((curve == NULL || ((curve->AILanes >> (uVar13 >> 1 & 0x1f) & 1U) != 0))))
						goto LAB_0002718c;
				}
			}
		LAB_000274bc:
			bVar3 = bVar3 + 1;
		} while (bVar3 < 2);

		if (bVar2) 
		{
		LAB_000274d8:
			
			cp->ai.c.changeLaneIndicateCount = 161;
			cp->ai.c.oldLane = bVar1;
			cp->ai.c.changeLaneCount = 4;
			cp->ai.c.changeLane = turnRight;
			uVar12 = uVar13;
		}
	}
	return uVar12;
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

int makeNextNodeCtrlNode = -1;

// [D]
int CreateNewNode(_CAR_DATA *cp)
{
	short sVar1;
	int local_v0_484;
	int local_v0_840;
	int local_v0_1348;
	int local_v0_1424;
	long lVar2;
	int local_v0_1824;
	int local_v0_1920;
	long lVar3;
	CIV_ROUTE_ENTRY *local_v1_48;
	CIV_ROUTE_ENTRY *pCVar4;
	CIV_ROUTE_ENTRY *pCVar5;
	int x;
	CIV_ROUTE_ENTRY *local_a0_84;
	CIV_ROUTE_ENTRY *local_a0_136;
	CIV_ROUTE_ENTRY *local_a0_168;
	int local_a0_536;
	int local_a0_1932;
	CIV_ROUTE_ENTRY *local_a1_52;
	int iVar6;
	int local_a3_260;
	int local_a3_1140;
	int local_a3_2384;
	int local_t0_908;
	DRIVER2_CURVE *curve;
	int local_s1_1816;
	int y;
	DRIVER2_STRAIGHT *straight;
	CIV_ROUTE_ENTRY tempNode;
	int turnAngle;
	int startDist;
	int startDist2;
	CIV_ROUTE_ENTRY *tstNode1;

	local_v1_48 = (cp->ai.c).pnode;
	local_a1_52 = (CIV_ROUTE_ENTRY *)&(cp->ai.c).pnode;
	tstNode1 = local_v1_48 + 1;
	turnAngle = 0;

	if (local_a1_52 <= tstNode1)
		tstNode1 = local_v1_48 + -0xc;

	local_a0_84 = local_v1_48 + 1;

	if ((int)cp < (int)tstNode1) 
	{
		if (local_a1_52 <= local_a0_84) 
			local_a0_84 = local_v1_48 + -0xc;


		local_a0_168 = local_v1_48 + 2;
		if ((int)local_a0_84 < (int)(cp + 1)) 
		{
			local_a0_136 = local_a0_168;

			if (local_a1_52 <= local_a0_168) 
				local_a0_136 = local_v1_48 + -0xb;


			if ((int)cp < (int)local_a0_136) 
			{
				if (local_a1_52 <= local_a0_168)
					local_a0_168 = local_v1_48 + -0xb;

				if (((int)local_a0_168 < (int)(cp + 1)) && (local_v1_48 != NULL)) 
				{
					do {
						pCVar4 = local_v1_48 + 1;
						pCVar5 = pCVar4;

						if (local_a1_52 <= pCVar4)
							pCVar5 = local_v1_48 + -0xc;

						if (pCVar5->pathType == 127) 
						{
							local_a3_260 = (cp->ai.c).currentRoad;
							if (local_a1_52 <= pCVar4)
							{
								pCVar4 = local_v1_48 + -0xc;
							}

							if ((uint)cp->id == makeNextNodeCtrlNode) 
							{
								(cp->ai.c).ctrlNode = pCVar4;
								makeNextNodeCtrlNode = -1;
							}

							if (((((local_a3_260 & 0xffffe000U) != 0) ||
								(NumDriver2Straights <= (int)(local_a3_260 & 0x1fffU))) &&
								(((local_a3_260 & 0xffffe000U) != 0x4000 ||
								(NumDriver2Curves <= (int)(local_a3_260 & 0x1fffU))))) ||(local_a3_260 < 0)) 
								break;

							if (((local_a3_260 & 0xffffe000U) == 0) && ((int)(local_a3_260 & 0x1fffU) < NumDriver2Straights)) 
							{
								straight = Driver2StraightsPtr + local_a3_260;
								if ((*(uint *)(straight->ConnectIdx + 3) & 0xffff0000) == 0xff010000) 
									local_v0_484 = ((cp->ai.c).currentLane);
								else 
									local_v0_484 = (int)(u_char)straight->LaneDirs >> ((uint)((cp->ai.c).currentLane >> 1) & 0x1f);


								iVar6 = -1;
								if ((local_v0_484 & 1U) == 0)
									iVar6 = 1;

								local_a0_536 = (straight->length);
								x = local_v1_48->distAlongSegment + iVar6 * 0x400;
								pCVar4->distAlongSegment = x;
								pCVar4->dir = local_v1_48->dir;

								if (((0 < iVar6) && (local_a0_536 < x)) || ((iVar6 < 0 && (x < 0))))
								{
									if (((iVar6 < 1) || (local_v1_48->distAlongSegment < local_a0_536)) && ((-1 < iVar6 || (0 < local_v1_48->distAlongSegment)))) 
									{
										if (iVar6 < 1) 
										{
										LAB_000279a0:
											pCVar4->distAlongSegment = 0;
										}
										else 
										{
											pCVar4->distAlongSegment = local_a0_536;
										}
									}
									else
									{
										iVar6 = GetNextRoadInfo(cp, 1, &turnAngle, &startDist, local_v1_48);
										(cp->ai.c).currentRoad = iVar6;
										pCVar4->dir = local_v1_48->dir + (short)turnAngle & 0xfff;
										pCVar4->distAlongSegment = startDist;

									LAB_000277f0:
										if ((cp->ai.c).currentRoad == -1) 
											break;
									}
								}
							}
							else if (((local_a3_260 & 0xffffe000U) == 0x4000) && (((int)(local_a3_260 & 0x1fffU) < NumDriver2Curves && (-1 < local_a3_260))))
							{
								curve = Driver2CurvesPtr + local_a3_260 + -0x4000;

								if (*(short *)&curve->NumLanes == -0xff)
									local_v0_840 = ((cp->ai.c).currentLane);
								else
									local_v0_840 = (int)(u_char)curve->LaneDirs >> ((uint)((cp->ai.c).currentLane >> 1) & 0x1f);


								iVar6 = -1;
								if ((local_v0_840 & 1U) == 0)
									iVar6 = 1;

								local_t0_908 = (int)curve->end - (int)curve->start & 0xfff;

								if (curve->inside < 10) 
								{
									x = iVar6 << 7;
								}
								else
								{
									x = iVar6 << 6;
									if (0x13 < curve->inside)
									{
										x = iVar6 << 5;
									}
								}

								x = local_v1_48->distAlongSegment + x;
								pCVar4->distAlongSegment = x;
								pCVar4->dir = *(short *)&pCVar4->distAlongSegment + curve->start + (short)iVar6 * 0x400 & 0xfff;

								if (((0 < iVar6) && (local_t0_908 < x)) || ((iVar6 < 0 && (x < 0)))) 
								{
									if (((0 < iVar6) &&
										(local_t0_908 <= local_v1_48->distAlongSegment)) ||
										((iVar6 < 0 && (local_v1_48->distAlongSegment < 1)))) 
									{
										iVar6 = GetNextRoadInfo(cp, 1, &turnAngle, &startDist2,local_v1_48);
										(cp->ai.c).currentRoad = iVar6;
										pCVar4->dir = local_v1_48->dir + (short)turnAngle &	0xfff;
										pCVar4->distAlongSegment = startDist2;
										goto LAB_000277f0;
									}

									if (iVar6 < 1)
										goto LAB_000279a0;

									pCVar4->distAlongSegment = local_t0_908;
								}
							}

							local_a3_1140 = (cp->ai.c).currentRoad;
							if (-1 < local_a3_1140)
							{
								curve = NULL;

								if (((local_a3_1140 & 0xffffe000U) == 0x4000) && (straight = NULL, (int)(local_a3_1140 & 0x1fffU) < NumDriver2Curves)) 
									curve = Driver2CurvesPtr + local_a3_1140 + -0x4000;
								else 
									straight = Driver2StraightsPtr + local_a3_1140;

								tempNode.dir = pCVar4->dir;
								tempNode.pathType = pCVar4->pathType;
								tempNode.distAlongSegment = pCVar4->distAlongSegment;
								tempNode.x = pCVar4->x;
								tempNode.z = pCVar4->z;

								if ((local_a3_260 != local_a3_1140) && (turnAngle == 0)) 
								{
									if (straight == NULL) 
									{
										if (*(short *)&curve->NumLanes == -0xff)
											local_v0_1424 = ((cp->ai.c).currentLane);
										else 
											local_v0_1424 = (int)(u_char)curve->LaneDirs >> ((uint)((cp->ai.c).currentLane >> 1) & 0x1f);

										iVar6 = -1;

										if ((local_v0_1424 & 1U) == 0)
											iVar6 = 1;

										x = iVar6 << 7;

										if ((9 < curve->inside) && (x = iVar6 << 6, 0x13 < curve->inside)) 
										{
											x = iVar6 << 5;
										}

										x = pCVar4->distAlongSegment + x;
									}
									else
									{
										if ((*(uint *)(straight->ConnectIdx + 3) & 0xffff0000) == 0xff010000) 
										{
											local_v0_1348 = ((cp->ai.c).currentLane);
										}
										else {
											local_v0_1348 = (int)(u_char)straight->LaneDirs >> ((uint)((cp->ai.c).currentLane >> 1) & 0x1f);
										}

										iVar6 = -1;
										if ((local_v0_1348 & 1U) == 0)
											iVar6 = 1;

										x = pCVar4->distAlongSegment + iVar6 * 0x400;
									}
									pCVar4->distAlongSegment = x;
								}

								if ((((gCurrentMissionNumber == 0x21) && 
									(iVar6 = CarHasSiren((uint)car_data[player[0].playerCarId].ap.model), iVar6 != 0)) && 
									(player[0].horn.on != '\0')) && (((cp->ap).model == '\x04' &&
									(iVar6 = car_data[player[0].playerCarId].hd.where.t[0] - (cp->hd).where.t[0], x = car_data[player[0].playerCarId].hd.where.t[2] - (cp->hd).where.t[2], iVar6 * iVar6 + x * x < 16000000))))
								{
									makeLimoPullOver = '\x01';
								}

								lVar2 = Random2(0);

								if (((lVar2 + (uint)cp->id * 0x20 & 0xf1) == 0xf1) || (makeLimoPullOver != '\0')) 
								{
									local_s1_1816 = 0;
									if (numParkedCars < maxParkedCars)
									{
										local_v0_1824 = Random2(0);
										local_s1_1816 = ((local_v0_1824 & 2U) != 0);
									}

									if ((gCurrentMissionNumber == 0x21) && ((cp->ap).model == '\x04'))
									{
										local_s1_1816 = (makeLimoPullOver != '\0');
									}

									local_v0_1920 = CheckChangeLanes(straight, curve, pCVar4->distAlongSegment, (_CAR_DATA *)cp, local_s1_1816);
									local_a0_1932 = local_v0_1920 & 0xff;

									if (((local_a0_1932 != (uint)(cp->ai.c).currentLane) &&
										((cp->ai.c).currentLane = local_a0_1932, local_s1_1816 != 0)) &&
										((makeLimoPullOver != '\0' || (((cp->ai.c).ctrlState == '\0' &&
										(((straight != NULL &&
										(((local_a0_1932 == 0 &&
										((straight->NumLanes & 0x40U) != 0)) ||
										((((u_char)straight->NumLanes & 0xf) * 2 - 1 ==
										(uint)(cp->ai.c).currentLane &&
										((straight->NumLanes & 0x80U) != 0)))))) ||
										((curve != NULL &&
										((((cp->ai.c).currentLane == '\0' &&
										((curve->NumLanes & 0x40U) != 0)) ||
										((((u_char)curve->NumLanes & 0xf) * 2 - 1 ==
										(uint)(cp->ai.c).currentLane &&
										((curve->NumLanes & 0x80U) != 0)))))))))))))) 
									{
										makeNextNodeCtrlNode = (cp->id);
										(cp->ai.c).ctrlState = '\b';
										(cp->ai.c).ctrlNode = pCVar4;
										(cp->ai.c).changeLaneCount = '\0';
									}
								}

								tempNode.dir = pCVar4->dir;
								tempNode.pathType = pCVar4->pathType;
								tempNode.distAlongSegment = pCVar4->distAlongSegment;
								tempNode.x = pCVar4->x;
								tempNode.z = pCVar4->z;

								GetNodePos(straight, NULL, curve, pCVar4->distAlongSegment, (_CAR_DATA *)cp, &tempNode.x, &tempNode.z, (uint)(cp->ai.c).currentLane);

								if (turnAngle == -0x400)
								{
									y = tempNode.x - local_v1_48->x;
									x = tempNode.z - local_v1_48->z;
									iVar6 = (cp->hd).wheel_speed / 0xaa;
									lVar2 = SquareRoot0(y * y + x * x);
									lVar3 = ratan2(y, x);
									local_a3_2384 = ((lVar3 - local_v1_48->dir) + 0x800U & 0xfff) - 0x800;
									x = FIXED((lVar2 - iVar6) * (int)rcossin_tbl[(local_a3_2384 & 0xfffU) * 2 + 1]);
									pCVar5 = pCVar4;

									if (0 < x) 
									{
										pCVar4->x = local_v1_48->x + FIXED(x * rcossin_tbl[((uint)(ushort)local_v1_48->dir & 0xfff) * 2]);
										pCVar5 = pCVar4 + 1;
										pCVar4->z = local_v1_48->z + FIXED(x * rcossin_tbl[((uint)(ushort)local_v1_48->dir & 0xfff) *	2 + 1]);
										sVar1 = local_v1_48->dir;
										pCVar4->pathType = 1;
										pCVar4->dir = sVar1;
										if (local_a1_52 <= pCVar5) {
											pCVar5 = pCVar4 + -0xc;
										}
									}

									iVar6 = FIXED((lVar2 - iVar6) * (int)rcossin_tbl[(local_a3_2384 & 0xfffU) * 2]);
									pCVar4 = pCVar5;

									if (iVar6 < 0) 
									{
										pCVar5->x = tempNode.x + FIXED(iVar6 * rcossin_tbl[(tempNode.dir & 0xfff) * 2]);
										pCVar4 = pCVar5 + 1;
										pCVar5->z = tempNode.z + FIXED(iVar6 * rcossin_tbl[(tempNode.dir & 0xfff) * 2 + 1]);
										pCVar5->pathType = 1;
										pCVar5->dir = tempNode.dir;
										if (local_a1_52 <= pCVar4)
										{
											pCVar4 = pCVar5 + -0xc;
										}
									}
								}

								if (pCVar4->pathType == 127) 
								{
									pCVar4->dir = tempNode.dir;
									pCVar4->pathType = tempNode.pathType;
									pCVar4->distAlongSegment = tempNode.distAlongSegment;
									pCVar4->x = tempNode.x;
									if (tempNode.x < 0) {
										tempNode.x = -tempNode.x;
									}
									pCVar4->z = tempNode.z;
									if (tempNode.x < 600000)
									{
										if (turnAngle != 0) 
										{
											cp->ai.c.turnNode = pCVar4 - cp->ai.c.targetRoute;
											cp->ai.c.turnDir = turnAngle == 0x400;
										}
										pCVar4->pathType = 1;
										return 1;
									}
								}
							}
							break;
						}

						if (local_a1_52 <= pCVar4)
							pCVar4 = local_v1_48 + -0xc;

						local_v1_48 = pCVar4;
					} while (pCVar4 != (cp->ai.c).pnode);
				}
			}
		}
	}
	cp->ai.c.thrustState = 3;
	cp->ai.c.ctrlState = 7;
	return 0;
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

// [D]
int InitCivState(_CAR_DATA *cp, EXTRA_CIV_DATA *extraData)
{
	int uVar1;
	long lVar2;
	int iVar3;

	CIV_STATE* cs = &cp->ai.c;

	cp->controlType = 2;

	if (extraData == NULL)
		cp->ai.c.thrustState = 0;
	else
		cp->ai.c.thrustState = extraData->thrustState;

	if (cp->ai.c.thrustState == 3) 
	{
	LAB_000282b4:
		if (extraData == NULL)
			cp->ai.c.ctrlState = 0;
		else
			cp->ai.c.ctrlState = extraData->ctrlState;

		iVar3 = 1;
	}
	else 
	{
		if (extraData == NULL) 
			cs->currentRoad = GetSurfaceIndex((VECTOR *)(cp->hd).where.t);
		else 
			cs->currentRoad = extraData->surfInd;

		uVar1 = cs->currentRoad;

		if (uVar1 > -1) 
		{
			cp->ai.c.currentNode = 0;
			cp->ai.c.pnode = NULL;
			cp->ai.c.ctrlNode = NULL;
			cp->ai.c.turnNode = -1;

			if (((((uVar1 & 0xffffe000) == 0) && ((uVar1 & 0x1fff) < NumDriver2Straights)) ||
				(((uVar1 & 0xffffe000) == 0x4000 && ((uVar1 & 0x1fff) < NumDriver2Curves)))) &&
				(uVar1 = cs->currentRoad, -1 < uVar1))
			{
				if (cp->ai.c.thrustState != 3) 
				{
					if (((uVar1 & 0xffffe000) == 0) && ((uVar1 & 0x1fff) < NumDriver2Straights))
						cp->ai.c.maxSpeed = speedLimits[((u_char)Driver2StraightsPtr[uVar1].NumLanes >> 4) & 3];
					else
						cp->ai.c.maxSpeed = speedLimits[((u_char)Driver2CurvesPtr[uVar1 - 0x4000].NumLanes >> 4)& 3];
	
					InitNodeList(cp, extraData);

					cp->ai.c.pnode = &cp->ai.c.targetRoute[0];
					cp->hd.where.t[0] = cp->ai.c.pnode->x;
					cp->hd.where.t[2] = cp->ai.c.pnode->z;

					if (cp->ai.c.thrustState != 3)
						return 1;

				}
				goto LAB_000282b4;
			}
		}

		iVar3 = 0;
		cp->ai.c.thrustState = 3;
		cp->ai.c.ctrlState = 7;
	}
	return iVar3;
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

// [D]
int PingOutAllSpecialCivCars(void)
{
	_CAR_DATA *lcp;

	lcp = car_data;

	while (lcp < &car_data[20])
	{
		if (lcp->controlType == 2 && MissionHeader->residentModels[lcp->ap.model] > 4)
		{
			testNumPingedOut++;
			numCivCars--;

			if (lcp->controlFlags & 1) 
				numCopCars--;

			if (lcp->ai.c.thrustState == 3 && lcp->ai.c.ctrlState == 5)
				numParkedCars--;

			if (lcp->inform != NULL)
				*lcp->inform ^= 0x40000000;

			ClearMem((char *)lcp, sizeof(_CAR_DATA));
			lcp->controlType = 0;
		}

		lcp++;
	} 

	return 1;
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

// [D]
int PingOutAllCivCarsAndCopCars(void)
{
	_CAR_DATA *cp;

	cp = car_data;

	do {

		if ((uint)cp->controlType - 2 < 2) 
		{
			testNumPingedOut++;

			if (cp->controlType == 2) 
			{
				if ((cp->controlFlags & 1) != 0) 
				{
					numCopCars--;
				}
				numCivCars--;
				if (cp->ai.c.thrustState == 3 && cp->ai.c.ctrlState == 5) 
				{
					numParkedCars = numParkedCars + -1;
				}
			}
			else
			{
				if (PingOutCivsOnly != 0 && valid_region(cp->hd.where.t[0], cp->hd.where.t[2]))
					goto LAB_0002852c;
			}

			if (cp->inform != NULL)
				*cp->inform ^= 0x40000000;

			ClearMem((char *)cp, sizeof(_CAR_DATA));
			cp->controlType = 0;
		}

	LAB_0002852c:
		cp++;
	} while (cp < &car_data[20]);

	return 1;
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
		else 
		{
			if (PingOutCivsOnly != 0 && (iVar2 = valid_region(x, z), iVar2 != 0))
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

// [D]
void SetUpTrafficLightPhase(void)
{
	junctionLightsPhase[0] = TrafficLightCycle(0);
	junctionLightsPhase[1] = TrafficLightCycle(1);
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

// [D]
int TrafficLightCycle(int exit)
{
	bool bVar1;
	int iVar2;
	int uVar3;

	uVar3 = CameraCnt - frameStart & 0x1ff;

	if (exit == 0 || exit == 2)
	{
		bVar1 = uVar3 < 0x100;
		uVar3 = uVar3 - 0x100;

		if (bVar1)
			return 1;

		bVar1 = uVar3 < 0x96;
	}
	else 
	{
		bVar1 = uVar3 < 0x96;

		if (0xff < uVar3)
			return 1;
	}

	iVar2 = 3;

	if ((!bVar1) && (iVar2 = 2, 199 < uVar3))
		return 1;

	return iVar2;
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
	roadblockDelay = roadblockDelayDiff[gCopDifficultyLevel] + (Random2(0) & 0xff);
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

const int EVENT_CAR_SPEED = 60;
const int DistanceTriggerCarMoves = 600;

// [D] [A]
int CreateCivCarWotDrivesABitThenStops(int direction, long(*startPos)[4], long(*stopPos)[4], unsigned char internalModel, int palette)
{
	unsigned char *puVar3;
	_CAR_DATA *p_Var5;
	_CAR_DATA *pNewCar;
	CIV_ROUTE_ENTRY *stopNode; // $a0
	CIV_ROUTE_ENTRY *spareNode; // $a1

	_EXTRA_CIV_DATA civDat;
	ClearMem((char *)&civDat, sizeof(civDat));

	p_Var5 = car_data;
	puVar3 = reservedSlots;
	pNewCar = NULL;

	do {
		if (p_Var5->controlType == 0 && *puVar3 == 0)
		{
			pNewCar = p_Var5;
			break;
		}

		p_Var5++;
		puVar3++;
	} while (p_Var5 < car_data + 19);

	if (pNewCar == NULL)
		return -1;

	civDat.thrustState = 0;
	civDat.ctrlState = 8;
	civDat.controlFlags = 0;
	civDat.palette = palette;
	civDat.angle = direction;

	InitCar(pNewCar, direction, startPos, 2, internalModel, 0, (char *)&civDat);

	pNewCar->ai.c.ctrlState = 8;
	pNewCar->ai.c.maxSpeed = EVENT_CAR_SPEED;

	pNewCar->st.n.linearVelocity[1] = 0;
	pNewCar->st.n.linearVelocity[0] = EVENT_CAR_SPEED * rcossin_tbl[(direction & 0xfffU) * 2];
	pNewCar->st.n.linearVelocity[2] = EVENT_CAR_SPEED * rcossin_tbl[(direction & 0xfffU) * 2 + 1];

	pNewCar->ai.c.velRatio = FIXED(EVENT_CAR_SPEED) / (DistanceTriggerCarMoves - pNewCar->ap.carCos->colBox.vz * 3);
	pNewCar->ai.c.targetRoute[0].x = (*startPos)[0];
	pNewCar->ai.c.targetRoute[0].z = (*startPos)[2];

	stopNode = &pNewCar->ai.c.targetRoute[1];
	pNewCar->ai.c.ctrlNode = stopNode;

	stopNode->pathType = 1;
	stopNode->dir = direction;
	stopNode->distAlongSegment = 0;

	stopNode->x = (*startPos)[0] + FIXED(DistanceTriggerCarMoves * rcossin_tbl[(direction & 0xfffU) * 2]);
	stopNode->z = (*startPos)[2] + FIXED(DistanceTriggerCarMoves * rcossin_tbl[(direction & 0xfffU) * 2 + 1]);

	spareNode = &pNewCar->ai.c.targetRoute[2];
	spareNode->pathType = 1;
	spareNode->dir = direction;
	spareNode->distAlongSegment = 0;

	spareNode->x = (*startPos)[0] + FIXED(DistanceTriggerCarMoves * rcossin_tbl[(direction & 0xfffU) * 2] * 3);
	spareNode->z = (*startPos)[2] + FIXED(DistanceTriggerCarMoves * rcossin_tbl[(direction & 0xfffU) * 2 + 1] * 3);

	numCivCars++;

	return pNewCar->id;
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

			tmpQ[0] = FIXED(cp->st.n.orientation[1] * iVar7 + cp->st.n.orientation[0] * iVar4);
			tmpQ[1] = FIXED(cp->st.n.orientation[1] * iVar4 - cp->st.n.orientation[0] * iVar7);
			tmpQ[2] = FIXED(cp->st.n.orientation[3] * iVar7 + cp->st.n.orientation[2] * iVar4);
			tmpQ[3] = FIXED(cp->st.n.orientation[3] * iVar4 - cp->st.n.orientation[2] * iVar7);

			uVar6 = (orientX - (orientX >> 0x1f)) * 2 & 0x3ffc;
			iVar5 = (int)*(short *)((int)rcossin_tbl + uVar6);
			iVar7 = (int)*(short *)((int)rcossin_tbl + uVar6 + 2);

			cp->st.n.orientation[0] = FIXED(tmpQ[3] * iVar5 + tmpQ[0] * iVar7);
			cp->st.n.orientation[1] = FIXED(tmpQ[2] * iVar5 + tmpQ[1] * iVar7);
			cp->st.n.orientation[2] = FIXED(tmpQ[2] * iVar7 - tmpQ[1] * iVar5);
			cp->st.n.orientation[3] = FIXED(tmpQ[3] * iVar7 - tmpQ[0] * iVar5);

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
// TODO: store pings
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
	int uVar18;
	_EXTRA_CIV_DATA civDat;
	unsigned char possibleLanes[12];
	unsigned char carDistLanes[15];
	long pos[4];
	int distSq;
	uint local_34;
	int local_30;
	int local_2c;

	civDat.distAlongSegment = -5;
	uVar18 = -1;
	straight = NULL;
	curve = NULL;
	local_34 = 0xffffff;
	local_2c = 0;

	PingOutCivsOnly = 1;

	if (((requestCopCar == 0) && (numParkedCars < maxParkedCars)) && ((gCurrentMissionNumber != 0x21 || (numCivCars != 0)))) 
	{
		local_2c = 1;
	}

	playerNum = 0;

	if (NumPlayers == 2) 
		playerNum = CameraCnt & 1;

	if ((MissionHeader->type & 4U) != 0)
	{
		PingOutCivsOnly = 1;
		return 0;
	}

	if (gInGameCutsceneActive != 0)
	{
		PingOutCivsOnly = 1;
		return 0;
	}

	if (maxCivCars-1 <= numCivCars && gInGameChaseActive == 0)
	{
		PingOutCivsOnly = 1;
		return 0;
	}

	//if (1 < NumPlayers)		// [A]
	//{
	//	PingOutCivsOnly = 1;
	//	return 0;
	//}

	p_Var13 = car_data;
	puVar15 = reservedSlots;

	// find a free slot
	cp = NULL;

	do {
		if (p_Var13->controlType == 0 && *puVar15 == 0)
		{
			cp = p_Var13;
			break;
		}

		p_Var13++;
		puVar15++;
	} while (p_Var13 < car_data + 19);

	if (cp == NULL)
	{
		PingOutCivsOnly = 1;
		return 0;
	}

	ClearMem((char *)&civDat, sizeof(civDat));
	baseLoc.vx = player[playerNum].spoolXZ->vx;
	baseLoc.vz = player[playerNum].spoolXZ->vz;

	if (requestCopCar == 0 && cookieCount > 43) 
	{
		cookieCount -= 25;
	}

	cVar5 = cookieCount;

	if (useStoredPings == 0 || gInGameChaseActive == 0) 
	{
		do {
			if (requestCopCar == 0) 
			{
				if (cookieCount < 43)
					goto LAB_000294b0;

				cookieCount = 0;
			}
			else 
			{
				if (cookieCount < 55)
				{
				LAB_000294b0:
					cookieCount++;
				}
				else
					cookieCount = 0;
			}

			if (cookieCount == cVar5)
				break;

			if (requestCopCar == 0)
				model = (cookieCount * 0x1000) / 0x2c;
			else
				model = (cookieCount * 0x1000) / 0x38;

			if (requestCopCar == 0)
				iVar6 = rcossin_tbl[(model & 0xfff) * 2] << 3;
			else
				iVar6 = rcossin_tbl[(model & 0xfff) * 2] * 10;

			randomLoc.vx = baseLoc.vx + FIXED(iVar6) * 0x800;

			if (requestCopCar == 0)
				model = (cookieCount * 0x1000) / 0x2c;
			else
				model = (cookieCount * 0x1000) / 0x38;

			if (requestCopCar == 0)
				iVar6 = rcossin_tbl[(model & 0xfff) * 2 + 1] << 3;
			else
				iVar6 = rcossin_tbl[(model & 0xfff) * 2 + 1] * 10;

			randomLoc.vz = baseLoc.vz + FIXED(iVar6) * 0x800;
			roadSeg = RoadInCell(&randomLoc);

		} while (((((roadSeg & 0xffffe000U) != 0) ||
			(NumDriver2Straights <= (int)(roadSeg & 0x1fffU))) &&
			(((roadSeg & 0xffffe000U) != 0x4000 ||
			(NumDriver2Curves <= (int)(roadSeg & 0x1fffU))))) || (roadSeg < 0));
	}
	else 
	{
		iVar6 = GetPingInfo(&cookieCount);

		if (iVar6 == -1)
			return 0;

		if (19 < iVar6)
			return 0;

		cp = car_data + iVar6;

		// free slot
		if (car_data[iVar6].controlType != 0) 
		{
			testNumPingedOut++;

			if (car_data[iVar6].controlType == 2)
			{
				if ((car_data[iVar6].controlFlags & 1) != 0)
					numCopCars--;

				numCivCars--;

				if (car_data[iVar6].ai.c.thrustState == 3 && car_data[iVar6].ai.c.ctrlState == 5)
					numParkedCars--;

			LAB_0002910c:
				puVar14 = (uint *)car_data[iVar6].inform;
				if (puVar14 != NULL) 
					*puVar14 = *puVar14 ^ 0x40000000;

				ClearMem((char *)cp, sizeof(_CAR_DATA));
				car_data[iVar6].controlType = 0;

				bVar4 = true;
			}
			else
			{
				if (PingOutCivsOnly == 0)
					goto LAB_0002910c;

				bVar4 = false;

				if (valid_region(car_data[iVar6].hd.where.t[0], car_data[iVar6].hd.where.t[2]) == 0)
					goto LAB_0002910c;
			}

			if (!bVar4)
				return 0;
		}

		if (requestCopCar == 0)
			model = (cookieCount * 0x1000) / 0x2c;
		else
			model = (cookieCount * 0x1000) / 0x38;

		if (requestCopCar == 0)
			iVar6 = rcossin_tbl[(model & 0xfff) * 2] << 3;
		else
			iVar6 = rcossin_tbl[(model & 0xfff) * 2] * 10;

		randomLoc.vx = baseLoc.vx + FIXED(iVar6) * 0x800;

		if (requestCopCar == 0)
			model = (cookieCount * 0x1000) / 0x2c;
		else
			model = (cookieCount * 0x1000) / 0x38;

		if (requestCopCar == 0)
			iVar6 = rcossin_tbl[(model & 0xfff) * 2 + 1] << 3;
		else
			iVar6 = rcossin_tbl[(model & 0xfff) * 2 + 1] * 10;

		randomLoc.vz = baseLoc.vz + FIXED(iVar6) * 0x800;
		roadSeg = RoadInCell(&randomLoc);
	}

	if (((((roadSeg & 0xffffe000U) != 0) || (NumDriver2Straights <= (int)(roadSeg & 0x1fffU))) &&
		(((roadSeg & 0xffffe000U) != 0x4000 || (NumDriver2Curves <= (int)(roadSeg & 0x1fffU))))) ||
		(roadSeg < 0)) 
	{
		civPingTest.OffRoad++;
		return 0;
	}

	if (((((roadSeg & 0xffffe000U) != 0) || (NumDriver2Straights <= (int)(roadSeg & 0x1fffU))) &&
		(((roadSeg & 0xffffe000U) != 0x4000 || (NumDriver2Curves <= (int)(roadSeg & 0x1fffU))))) ||
		(roadSeg < 0)) 
		goto LAB_0002a368;

	ClearMem((char *)carDistLanes, sizeof(carDistLanes));

	if ((((roadSeg & 0xffffe000U) == 0) && ((int)(roadSeg & 0x1fffU) < NumDriver2Straights)) && (-1 < roadSeg))
	{
		straight = Driver2StraightsPtr + roadSeg;
		if ((straight->NumLanes & 0xfU) == 0) goto LAB_0002a368;
		if ((gCurrentMissionNumber == 0x21) && (minPingInDist == 666)) {
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
						(((straight->NumLanes & 0xffffff0f) * 2 - 1 == uVar18 &&
						((straight->NumLanes & 0x80U) != 0)))))) ||
						((((straight->AILanes >> (uVar18 >> 1 & 0x1f) & 1U) != 0 &&
						((uVar18 != 0 || ((straight->NumLanes & 0x40U) == 0)))) &&
						(((straight->NumLanes & 0xffffff0f) * 2 - 1 != uVar18 ||
						((straight->NumLanes & 0x80U) == 0)))))) 
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

			uVar18 = possibleLanes[(lVar8 >> 8) % uVar17];
			cp->ai.c.currentLane = possibleLanes[(lVar8 >> 8) % uVar17];
		}
		if (((uVar18 == 0) && ((straight->NumLanes & 0x40U) != 0)) ||
			(((straight->NumLanes & 0xf) * 2 - 1 == uVar18 &&
			((straight->NumLanes & 0x80U) != 0)))) 
		{
			civDat.thrustState = 3;
			civDat.ctrlState = 7;

			if ((straight->AILanes >> (uVar18 / 2 & 0x1fU) & 1U) != 0) 
			{
				civDat.ctrlState = 5;
			}
		}
		else 
		{
			if ((straight->AILanes >> (uVar18 / 2 & 0x1fU) & 1U) == 0) 
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

			if ((bVar16 & 0xf) == 0) 
				goto LAB_0002a368;

			model = ((uint)bVar16 & 0xf) * 2;
			uVar17 = 0;
			if ((bVar16 & 0xf) != 0) {
				do {
					if ((((uVar18 == 0) || (model - 1 == uVar18)) &&
						((local_2c != 0 &&
						(((uVar18 == 0 && ((curve->NumLanes & 0x40U) != 0)) ||
						(((curve->NumLanes & 0xffffff0f) * 2 - 1 == uVar18 &&
						((curve->NumLanes & 0x80U) != 0)))))))) ||
						(((curve->AILanes >> (uVar18 >> 1 & 0x1f) & 1U) != 0 &&
						(((uVar18 != 0 || ((curve->NumLanes & 0x40U) == 0)) &&
						(((curve->NumLanes & 0xffffff0f) * 2 - 1 != uVar18 ||
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
				if ((curve->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) != 0) {
					civDat.ctrlState = 5;
				}
			}
			else {
				if (((int)(u_char)curve->AILanes >> ((int)uVar18 / 2 & 0x1fU) & 1U) == 0)
					goto LAB_00029a28;
				civDat.thrustState = 0;
				civDat.ctrlState = 0;
			}
			local_30 = (int)(((int)curve->end - (int)curve->start & 0xfffU) *
				(uint)curve->inside * 0xb) / 7;
		}
	}

	if ((civDat.thrustState != 3) ||
		(((cVar5 = 0, gInGameCutsceneActive == 0 && (gInGameChaseActive == 0)) &&
		(((Random2(0) & 0x40) == 0 || (cVar5 = 3, gCurrentMissionNumber == 0x20)))))) 
	{
		cVar5 = 0;
	}

	modelRandomList[12] = cVar5;
	if (((specModelValid == 0) || (allowSpecSpooling == 0)) ||
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
	else 
	{
		model = 3;
	}

	if ((gCurrentMissionNumber == 0x21) && (minPingInDist == 666))
		model = 4;

	if (requestCopCar != 0) 
		civDat.controlFlags = 1;

	if ((MissionHeader->residentModels[model] == 0) || (4 < MissionHeader->residentModels[model]))
	{
		civDat.palette = 0;
	}
	else 
	{
		if (player[0].playerType == 1 && car_data[player[0].playerCarId].ap.model == model) 
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
	iVar6 = car_cosmetics[model].colBox.vz;
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

		civDat.distAlongSegment = (uVar3 >> 1) + FIXED(rcossin_tbl[(sVar2 - lVar8 & 0xfffU) * 2 + 1] * lVar9);

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
		if (IS_SINGLE_LANE(straight))
			uVar17 = cp->ai.c.currentLane;
		else
			uVar17 = (u_char)straight->LaneDirs >> ((cp->ai.c.currentLane >> 1) & 0x1f);

		if ((uVar17 & 1) == 0)
			local_34 = straight->angle;
		else
			local_34 = straight->angle + 0x800U & 0xfff;
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
				if ((9 < bVar16) && (uVar17 = 0x20, bVar16 < 0x14))
				{
					uVar17 = 0x40;
				}
			}
			else 
			{
				bVar16 = curve->inside;
			}

			uVar10 = (currentAngle & 0xfffU) - (int)curve->start;
			civDat.distAlongSegment = uVar10 & 0xf80;

			if ((9 < bVar16) && (civDat.distAlongSegment = uVar10 & 0xfe0, bVar16 < 0x14)) 
			{
				civDat.distAlongSegment = uVar10 & 0xfc0;
			}

			if (civDat.distAlongSegment <= uVar17)
				civDat.distAlongSegment = uVar17;
	
			uVar17 = (curve->end - curve->start) - uVar17 & 0xfff;
			if (uVar17 <= civDat.distAlongSegment)
				civDat.distAlongSegment = uVar17;

			iVar7 = civDat.distAlongSegment + (int)curve->start;

			if (curve->NumLanes == -1)
				uVar17 = cp->ai.c.currentLane;
			else
				uVar17 = (u_char)curve->LaneDirs >> ((cp->ai.c.currentLane >> 1) & 0x1f);

			if ((uVar17 & 1) == 0)
				local_34 = iVar7 + 0x400;
			else
				local_34 = iVar7 - 0x400;

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

		cp->controlFlags |= 4;
	}

	if (cp->ai.c.ctrlState == 5)
		numParkedCars++;

LAB_0002a430:
	if ((cp->controlFlags & 1) != 0) 
	{
		requestCopCar = 0;
		numCopCars++;
	}
	numCivCars++;

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

// [D]
void AttemptUnPark(_CAR_DATA *cp)
{
	unsigned char bVar1;
	int curRoad;
	DRIVER2_STRAIGHT *straight;
	DRIVER2_CURVE *curve;

	straight = NULL;
	curve = NULL;
	InitCivState(cp, NULL);
	curRoad = cp->ai.c.currentRoad;

	if ((curRoad & 0xffffe000) == 0 && (curRoad & 0x1fff) < NumDriver2Straights && curRoad > -1) 
		straight = Driver2StraightsPtr + curRoad;
	else 
		curve = Driver2CurvesPtr + curRoad - 0x4000;

	bVar1 = cp->ai.c.currentLane;

	if (straight && curve)
	{
		cp->ai.c.currentLane = CheckChangeLanes(straight, curve, cp->ai.c.targetRoute[0].distAlongSegment, cp, 0);

		if (((bVar1 == cp->ai.c.currentLane) ||
			(straight != NULL && ((straight->AILanes >> ((cp->ai.c.currentLane >> 1) & 0x1f) & 1U) == 0))) ||
			(curve != NULL && ((curve->AILanes >> ((cp->ai.c.currentLane >> 1) & 0x1f) & 1U) == 0)))
		{
			cp->ai.c.thrustState = 3;
			cp->ai.c.ctrlState = 7;
		}
	}
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
	//return 1; // [A] disabled - buggy

	long lVar2;
	int iVar3;

	CheckPingOut(cp);

	if (cp->controlType == 2) 
	{
		if (cp->ai.c.changeLaneIndicateCount != 0) 
			cp->ai.c.changeLaneIndicateCount--;

		if (cp->ai.c.ctrlState == 5 && cp->ai.c.thrustState == 3 && cp->totalDamage < 4 && (cp->ap.model != 3 && (Random2(0) + (0x19 - cp->id) * 0x10 & 0xff8) == 0xf00))
		{
			AttemptUnPark(cp);
		}

		cp->thrust = CivAccel(cp);

		if (cp->ai.c.thrustState != 3)
			cp->wheel_angle = CivSteerAngle(cp);

#if 0
		{
			//maxCivCars = 2;
			//maxCopCars = 0;

			extern void Debug_AddLine(VECTOR& pointA, VECTOR& pointB, CVECTOR& color);
			extern void Debug_AddLineOfs(VECTOR& pointA, VECTOR& pointB, VECTOR& ofs, CVECTOR& color);

			CVECTOR ggcv = { 0, 250, 0 };
			CVECTOR bbcv = { 0, 0, 250 };
			CVECTOR rrcv = { 250, 0, 0 };

			CVECTOR yycv = { 250, 250, 0 };

			VECTOR _zero = { 0 };
			VECTOR _up = { 0, 120, 0 };

			VECTOR _up1 = { 0, 20, 0 };
			VECTOR _up2 = { 0, 40, 0 };
			VECTOR _up3 = { 0, 60, 0 };
			VECTOR _up4 = { 0, 80, 0 };

			// show current road
			/*
			if (cp->ai.c.currentRoad != -1)
			{
				DRIVER2_STRAIGHT* straight = Driver2StraightsPtr + cp->ai.c.currentRoad;

				int angle = straight->angle;
				int distFromCentreA = -straight->length / 2;
				int distFromCentreB = straight->length / 2;

				int laneNo = cp->ai.c.currentLane;
				test42 = 0 * 0x80;
				sideShift = ((straight->NumLanes & 0xf) * 0x200 - (laneNo * 0x200 + 0x100)) + test42;

				int straightX1 = straight->Midx + FIXED(distFromCentreA * rcossin_tbl[(angle & 0xfffU) * 2]) + FIXED(sideShift * rcossin_tbl[(angle & 0xfffU) * 2 + 1]);
				int straightZ1 = (straight->Midz + FIXED(distFromCentreA * rcossin_tbl[(angle & 0xfffU) * 2 + 1])) - FIXED(sideShift * rcossin_tbl[(angle & 0xfffU) * 2]);

				int straightX2 = straight->Midx + FIXED(distFromCentreB * rcossin_tbl[(angle & 0xfffU) * 2]) + FIXED(sideShift * rcossin_tbl[(angle & 0xfffU) * 2 + 1]);
				int straightZ2 = (straight->Midz + FIXED(distFromCentreB * rcossin_tbl[(angle & 0xfffU) * 2 + 1])) - FIXED(sideShift * rcossin_tbl[(angle & 0xfffU) * 2]);

				VECTOR roadA = { straightX1, cp->hd.where.t[1], straightZ1 };
				VECTOR roadB = { straightX2, cp->hd.where.t[1], straightZ2 };

				Debug_AddLine(roadA, roadB, rrcv);
			}
			*/


			CIV_ROUTE_ENTRY* pn = cp->ai.c.pnode;
			if (pn)
			{
				for (int i = 0; i < 13; i++)
				{
					if (pn->pathType != 127)
					{
						int sx, cx;
						sx = rsin(pn->dir);
						cx = rcos(pn->dir);

						VECTOR ofs = { sx / 16, 0, cx / 16 };

						VECTOR b1p = { pn->x, cp->hd.where.t[1], pn->z };

						//Debug_AddLineOfs(_zero, _up, b1p, rrcv);
						Debug_AddLineOfs(_zero, ofs, b1p, rrcv);
					}

					pn++;

					if (pn > cp->ai.c.targetRoute + 13)
						pn -= 12;
				}
			}

			// current node - YELLOW
			if(cp->ai.c.currentNode != -1)
			{
				CIV_ROUTE_ENTRY& currentNode = cp->ai.c.targetRoute[cp->ai.c.currentNode];

				VECTOR b1p = { currentNode.x, cp->hd.where.t[1], currentNode.z };

				Debug_AddLineOfs(_zero, _up1, b1p, yycv);
			}

			// turn node - RED
			if(cp->ai.c.turnNode != -1)
			{
				CIV_ROUTE_ENTRY& turnNode = cp->ai.c.targetRoute[cp->ai.c.turnNode];

				VECTOR b1p = { turnNode.x, cp->hd.where.t[1], turnNode.z };

				Debug_AddLineOfs(_up1, _up2, b1p, rrcv);
			}

			// control node - GREEN
			if (cp->ai.c.ctrlNode)
			{
				VECTOR b1p = { cp->ai.c.ctrlNode->x, cp->hd.where.t[1], cp->ai.c.ctrlNode->z };

				Debug_AddLineOfs(_up2, _up3, b1p, ggcv);
			}

			// previous node - BLUE
			if (cp->ai.c.pnode)
			{
				VECTOR b1p = { cp->ai.c.pnode->x, cp->hd.where.t[1], cp->ai.c.pnode->z };

				Debug_AddLineOfs(_up3, _up4, b1p, bbcv);
			}
		}
#endif
	}

	if (cp->controlFlags & 1)
		PassiveCopTasks(cp);

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

int sideMul = 10;
int collDat = 0;
int carnum = 0;
int newAccel = 2000;

int CivAccelTrafficRules(_CAR_DATA *cp, int *distToNode)
{
	short sVar1;
	unsigned char bVar2;
	CAR_COSMETICS *pCVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	_CAR_DATA *p_Var8;
	int iVar9;
	int iVar10;

	pCVar3 = cp->ap.carCos;
	iVar10 = (pCVar3->colBox).vz;
	sVar1 = (pCVar3->colBox).vx;

	if (cp->id == 1 && (cp->ai.c.carMustDie == 1))
	{
		cp->ai.c.thrustState = 3;
		cp->ai.c.ctrlState = 9;
		cp->ai.c.carMustDie = 0;
	}

	switch (cp->ai.c.thrustState)
	{
		case 0:
			cp->ai.c.brakeLight = 0;

			if (cp->ai.c.ctrlNode == NULL)
				goto LAB_0002a800;

			iVar5 = (cp->hd).wheel_speed;
			iVar9 = (iVar5 * FIXED(iVar5)) / (newAccel << 1);

			if (iVar9 < 0)
				iVar9 = -iVar9;

			if (!IS_NODE_VALID(cp->ai.c.ctrlNode))		// [A] Weird.
				goto LAB_0002a670;

			iVar6 = *distToNode;
			if (iVar9 <= iVar6) goto LAB_0002a800;
			iVar5 = iVar5 + -120000;
			iVar9 = iVar6 - iVar10 * 3;
			if (iVar9 < 0)
			{
				if (2 < iVar10 * 3 - iVar6) 
					goto LAB_0002a7d4;
			LAB_0002a7f8:
				cp->ai.c.velRatio = iVar5;
			}
			else 
			{
				if (2 < iVar9) 
				{
				LAB_0002a7d4:
					iVar6 = iVar6 + iVar10 * -3;
					iVar5 = iVar5 / iVar6;
					goto LAB_0002a7f8;
				}
				cp->ai.c.velRatio = iVar5;
			}
			cp->ai.c.thrustState = 1;
		LAB_0002a800:
			if (FIXED(cp->hd.wheel_speed) > cp->ai.c.maxSpeed)
			{
				iVar10 = newAccel;
				return iVar10 >> 2;
			}
			return newAccel;
		case 1:
			if (cp->ai.c.ctrlState == 5 || cp->ai.c.ctrlState == 8)
				iVar10 = 100;
			else
				iVar10 = iVar10 * 3;

			cp->ai.c.brakeLight = 1;

			if (cp->ai.c.ctrlNode != NULL && cp->ai.c.ctrlNode->pathType != 127)
			{
				bVar2 = cp->ai.c.ctrlState;
				if ((bVar2 == 1) && junctionLightsPhase[cp->ai.c.trafficLightPhaseId] == 3)
				{
				LAB_0002a8b4:
					cp->ai.c.thrustState = 0;
					cp->ai.c.ctrlNode = NULL;
					iVar10 = newAccel;
					return iVar10;
				}
				iVar9 = *distToNode;
				if (iVar9 < iVar10) 
				{
					if (bVar2 == 6)
						goto LAB_0002a8b4;

					iVar9 = (cp->hd).wheel_speed;
					iVar10 = -iVar9;
					iVar10 = iVar10 >> 2;

					cp->ai.c.thrustState = 3;
				}
				else 
				{
					if (bVar2 == 6)
					{
						iVar10 = (iVar9 - iVar10) * cp->ai.c.velRatio + 70000;
					}
					else if (iVar10 < iVar9) 
					{
						iVar10 = cp->ai.c.velRatio * ((iVar9 - iVar10) + 100);
					}
					else
					{
						iVar10 = 0;
					}

					iVar10 = ((iVar10 - (cp->hd).wheel_speed) * newAccel) / 0xf;
				}

				if (IS_NODE_VALID(cp->ai.c.ctrlNode))	// [A] Weird.
				{
					iVar9 = newAccel;

					if ((iVar10 <= newAccel) && (iVar9 = iVar10, iVar10 < newAccel * -2)) 
						iVar9 = newAccel * -2;

					return iVar9;
				}
			}
		default:
		LAB_0002a670:
			cp->ai.c.thrustState = 3;
			cp->ai.c.ctrlState = 7;
			return 0;
		case 3:
			break;
		case 5:
		case 6:
			cp->ai.c.brakeLight = 1;
			iVar10 = 0x200;

			if (cp->ai.c.ctrlState == 4)
				iVar10 = 0x800;

			p_Var8 = car_data + 19;
			uVar4 = cp->hd.direction & 0xfff;

			iVar9 = 0x7fffff;

			if (true) 
			{
				do {
					if (((p_Var8->ai.c.thrustState != 3) && (p_Var8 != cp)) && (p_Var8->controlType != 0)) 
					{
						iVar7 = (p_Var8->hd).where.t[0] - (cp->hd).where.t[0];
						iVar6 = (p_Var8->hd).where.t[2] - (cp->hd).where.t[2];

						iVar5 = FIXED(iVar7 * rcossin_tbl[uVar4 * 2] + iVar6 * rcossin_tbl[uVar4 * 2 + 1]);

						if (0 < iVar5)
						{
							iVar6 = FIXED(iVar7 * rcossin_tbl[uVar4 * 2 + 1] - iVar6 * rcossin_tbl[uVar4 * 2]);
							if (iVar6 < 0)
								iVar6 = -iVar6;

							if ((iVar6 < sVar1 * sideMul * 6) && (iVar5 < iVar9))
								iVar9 = iVar5;
						}
					}
					p_Var8--;
				} while (p_Var8 >= car_data);
			}

			if (iVar9 <= iVar10) 
			{
				iVar9 = cp->hd.wheel_speed;
				iVar10 = -iVar9;

				iVar10 = iVar10 >> 2;
				iVar9 = newAccel;

				if ((iVar10 <= newAccel) && (iVar9 = iVar10, iVar10 < newAccel * -2)) 
				{
					iVar9 = newAccel * -2;
				}

				return iVar9;
			}
			cp->ai.c.ctrlState = 0;
			cp->ai.c.thrustState = 0;
			iVar10 = newAccel;
			cp->ai.c.ctrlNode = 0;
			return iVar10;
	}

	switch (cp->ai.c.ctrlState)
	{
		case 1:
			if (junctionLightsPhase[cp->ai.c.trafficLightPhaseId] == 3)
				cp->ai.c.thrustState = 0;

			cp->ai.c.brakeLight = 1;
		case 2:
			cp->ai.c.brakeLight = 1;
			return 0;
		case 3:
			cp->ai.c.thrustState = 5;
			cp->ai.c.brakeLight = 1;
			break;
		case 4:
			cp->ai.c.thrustState = 6;
			cp->ai.c.brakeLight = 1;
			break;
		default:
			cp->ai.c.brakeLight = 0;
	}

	return 0;
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

int brakeLength[20];

int CAR_PAUSE_START = 100;
static _CAR_DATA(*horncarflag[2]) = { 0 };
static unsigned char hornchanflag[2] = { 0 };

// [D]
void SetUpCivCollFlags(void)
{
	unsigned char bVar1;
	ushort uVar2;
	bool bVar3;
	int iVar4;
	int iVar5;
	uint uVar6;
	long lVar7;
	int iVar8;
	_CAR_DATA **pp_Var9;
	int y;
	int iVar10;
	_CAR_DATA **pp_Var11;
	CAR_COSMETICS *pCVar12;
	_CAR_DATA *p_Var13;
	uint uVar14;
	unsigned char *puVar15;
	_CAR_DATA *p_Var16;
	SVECTOR boxDisp;
	int carLength[2];
	int dNewLBODY[2];
	long local_30;
	_CAR_DATA *local_2c;

	CDATA2D cd[2];

	ClearMem((char *)brakeLength, sizeof(brakeLength));

	local_2c = car_data + 19;
	if (true) {
		do {
			if (local_2c->controlType == 2) 
			{
				y = FIXED(local_2c->hd.wheel_speed);

				if (local_2c->wheel_angle < 0x3d)
					y = y * 0xd;
				else 
					y = y << 2;

				pCVar12 = local_2c->ap.carCos;
				iVar4 = pCVar12->colBox.vz;
				cd[0].length[0] = y;

				if (y < 0)
					cd[0].length[0] = -y;

				cd[0].length[0] = iVar4 + 0x5d + cd[0].length[0];
				cd[0].length[1] = (int)(pCVar12->colBox).vx;

				gte_SetRotMatrix(&local_2c->hd.where.m);
				gte_SetTransMatrix(&local_2c->hd.where.m);

				boxDisp.vx = -pCVar12->cog.vx;
				boxDisp.vy = -pCVar12->cog.vy;
				boxDisp.vz = (y - pCVar12->cog.vz) + 0x5d;

				gte_ldv0(&boxDisp);

				gte_rtv0tr();

				gte_stlvnl(&cd[0].x);

				p_Var16 = car_data + 20;
				cd[0].theta = local_2c->hd.direction;
				if (true) {
					do {
						if (p_Var16->controlType == 0 || p_Var16 == local_2c)
						{
						LAB_0002b1a4:
							bVar3 = p_Var16-1 < car_data;
						}
						else 
						{
							if (CAR_INDEX(p_Var16) == 20)
							{
								if (player[0].playerType != 2) 
									goto LAB_0002b1a4;

								cd[1].length[0] = 0x3c;
								cd[1].length[1] = 0x3c;
								cd[1].x.vx = player[0].pos[0];
								cd[1].x.vz = player[0].pos[2];
								cd[1].theta = player[0].dir;
							}
							else 
							{
								pCVar12 = (p_Var16->ap).carCos;
								cd[1].length[0] = pCVar12->colBox.vz;
								cd[1].length[1] = pCVar12->colBox.vx;
								cd[1].x.vx = (p_Var16->hd).oBox.location.vx;
								cd[1].x.vy = (p_Var16->hd).oBox.location.vy;
								cd[1].x.vz = (p_Var16->hd).oBox.location.vz;
								cd[1].theta = (p_Var16->hd).direction;
							}

							y = ((cd[0].length[0] + cd[1].length[0]) * 3) / 2;
							if (cd[0].x.vx - cd[1].x.vx < 0) 
							{
								if (cd[1].x.vx - cd[0].x.vx < y) 
									goto LAB_0002ae74;

								goto LAB_0002b1a4;
							}

							if (y <= cd[0].x.vx - cd[1].x.vx) 
								goto LAB_0002b1a4;

						LAB_0002ae74:
							if (cd[0].x.vz - cd[1].x.vz < 0) 
							{
								if (cd[1].x.vz - cd[0].x.vz < y)
									goto LAB_0002aeb0;

								goto LAB_0002b1a4;
							}

							if (y <= cd[0].x.vz - cd[1].x.vz)
								goto LAB_0002b1a4;

						LAB_0002aeb0:
							iVar10 = (local_2c->hd).where.t[1];

							if (CAR_INDEX(p_Var16) == 20)
							{
							LAB_0002af10:
								iVar5 = player[0].pos[1] - iVar10;
								if (iVar5 < 0)
									iVar5 = iVar10 - player[0].pos[1];

								if (499 < iVar5)
									goto LAB_0002b1a4;
							}
							else 
							{
								iVar8 = (p_Var16->hd).where.t[1];
								iVar5 = iVar8 - iVar10;
								if (iVar5 < 0) {
									iVar5 = iVar10 - iVar8;
								}
								if (499 < iVar5) {
									if (CAR_INDEX(p_Var16) != 20)
										goto LAB_0002b1a4;

									goto LAB_0002af10;
								}
							}

							if (bcollided2d(cd, 1) == 0)
								goto LAB_0002b1a4;

							//ratan2(y, local_30);
							uVar14 = (cd[0].length[0] - iVar4) - boxOverlap;

							if (uVar14 < 1)
								uVar14 = 1;
						
							uVar6 = brakeLength[local_2c->id];

							if ((uVar6 == 0) || (uVar14 < uVar6))
								brakeLength[local_2c->id] = uVar14;
	
							if (local_2c->ai.c.thrustState == 3) 
								goto LAB_0002b1a4;

							if (CAR_INDEX(p_Var16) == 20)
								local_2c->ai.c.carPauseCnt = CAR_PAUSE_START;
			
							bVar3 = p_Var16 + -1 < car_data;
							if ((local_2c->ai.c.thrustState != 3) &&
								((p_Var16->controlType == 1 ||
								(bVar3 = p_Var16-1 < car_data, CAR_INDEX(p_Var16) == 20))))
							{
								lVar7 = Random2(0);
								p_Var13 = local_2c;

								bVar3 = false;
								pp_Var11 = horncarflag;
								y = 1;
								pp_Var9 = pp_Var11;
								do {
									if (*pp_Var9 == p_Var13) {
										bVar3 = true;
									}
									y = y + -1;
									pp_Var9 = pp_Var9 + 1;
								} while (-1 < y);
								y = 0;
								puVar15 = hornchanflag;
								do {
									if ((!bVar3) && (*puVar15 == 0)) {
										uVar14 = GetFreeChannel();
										*puVar15 = uVar14;
										SpuSetVoiceAR(uVar14 & 0xff, 0x1b);
										bVar1 = (p_Var13->ap).model;

										if (bVar1 == 4) 
										{
											uVar14 = ResidentModelsBodge();
										}
										else if(bVar1 < 3) 
										{
											uVar14 = (p_Var13->ap).model;
										}
										else
										{
											uVar14 = (p_Var13->ap).model - 1;
										}

										Start3DSoundVolPitch(*puVar15, 3, uVar14 * 3 + 2, (p_Var13->hd).where.t[0], (p_Var13->hd).where.t[1], (p_Var13->hd).where.t[2], -2000, 0x1000);
										bVar1 = *puVar15;
										uVar2 = channels[bVar1].time;
										*pp_Var11 = p_Var13;

										channels[bVar1].time = uVar2 + lVar7 + (lVar7 / 0x1e) * -0x1e;
										break;
									}
									pp_Var11 = pp_Var11 + 1;
									y = y + 1;
									puVar15 = puVar15 + 1;
								} while (y < 2);
								goto LAB_0002b1a4;
							}
						}
						p_Var16 = p_Var16 + -1;
					} while (!bVar3);
				}
			}
			local_2c = local_2c + -1;
		} while (local_2c >= car_data);
	}
	uVar14 = 0;
	do {
		bVar1 = hornchanflag[uVar14];

		if ((bVar1 != 0) && (channels[bVar1].time == 0)) 
		{
			horncarflag[uVar14] = NULL;
			hornchanflag[uVar14] = 0;
			SpuSetVoiceAR(0, 0x23);
		}
		uVar14 = uVar14 + 1 & 0xff;

	} while (uVar14 < 2);
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

// [D]
int CivAccel(_CAR_DATA *cp)
{
	int iVar1;
	uint uVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	CIV_ROUTE_ENTRY *node;
	uint uVar6;
	int distToNode;

	node = cp->ai.c.ctrlNode;
	carnum = CAR_INDEX(cp);

	if (node == NULL || cp->ai.c.thrustState == 3) 
	{
		distToNode = -1;
	}
	else 
	{
		iVar3 = cp->hd.where.t[0] - node->x;
		iVar4 = cp->hd.where.t[2] - node->z;

		distToNode = SquareRoot0(iVar3 * iVar3 + iVar4 * iVar4);
	}

	if (cp->ai.c.thrustState != 3 && node && node->pathType == 127)
	{
		distToNode = -distToNode;
	}

	iVar3 = CivAccelTrafficRules(cp, &distToNode);

	if (cp->ai.c.thrustState != 3) 
	{
		collDat = brakeLength[cp->id];
		iVar4 = cp->ap.carCos->colBox.vz << 0x10;
		iVar5 = iVar4 >> 0x10;
		if (collDat != 0) 
		{
			iVar1 = iVar5;

			uVar6 = iVar5 - (iVar4 >> 0x1f) >> 1;

			if (collDat < (iVar5 * 2)) 
			{
				if (((iVar5 * 2) < collDat) && (uVar6 <= collDat)) 
				{
					uVar6 = uVar6 + iVar5 * -2;
					iVar4 = ((collDat + iVar5 * -2) * -100) / uVar6 + 100;
				}
				else if ((uVar6 < collDat) && ((iVar1 >> 2) <= collDat))
				{
					uVar2 = (iVar1 >> 2) - uVar6;
					iVar4 = ((collDat - uVar6) * -300) / uVar2 + 400;
				}
				else 
				{
					iVar4 = 100;
				}
			}
			else 
			{
				iVar4 = 0;
			}

			iVar1 = (cp->hd).wheel_speed;
			iVar5 = -iVar1;
			iVar4 = (newAccel * iVar4) / 100;
			iVar5 = iVar5 >> 2;

			if ((iVar5 <= iVar4) && (iVar1 = iVar4 * -2, iVar4 = iVar5, iVar5 < iVar1)) 
			{
				iVar4 = iVar1;
			}

			if (iVar4 < iVar3) 
				iVar3 = iVar4;
		}

		if (cp->ai.c.carPauseCnt > 0 && collDat == 0)
		{
			iVar5 = cp->hd.wheel_speed;
			iVar4 = FIXED(iVar5);
			if (iVar4 < 0)
				iVar4 = -iVar4;

			iVar1 = -iVar5;
			if (iVar4 < 3)
			{
				iVar3 = iVar1 >> 2;
				cp->ai.c.carPauseCnt -= 1;
			}
		}
	}

	return iVar3;
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

const int checkFrames = 20;
const int maxSteer = 512;

// [D]
int CivSteerAngle(_CAR_DATA *cp)
{
	CIV_ROUTE_ENTRY *startNode;
	_CAR_DATA currentCar;

	short sVar2;
	int iVar3;
	int iVar4;
	long lVar5;
	_CAR_DATA *p_Var6;
	_CAR_DATA *p_Var7;
	CIV_ROUTE_ENTRY *pCVar8;
	_CAR_DATA *p_Var9;
	CIV_ROUTE_ENTRY *pCVar10;
	long lVar12;
	_CAR_DATA *p_Var15;
	VECTOR locPath;
	VECTOR pathPoint;

	pathPoint.vx = 0;
	pathPoint.vy = 0;
	pathPoint.vz = 0;

	startNode = cp->ai.c.pnode;

	sVar2 = cp->ap.carCos->colBox.vz;
	pCVar8 = startNode + 1;

	if (cp->ai.c.targetRoute + 13 <= pCVar8)
		pCVar8 = startNode - 12;

	pCVar10 = startNode + 2;

	if (pCVar8->pathType == 127)
	{
	LAB_0002b600:
		if (CreateNewNode(cp) == 0)
			goto LAB_0002b76c;
	}
	else
	{
		if (cp->ai.c.targetRoute + 13 <= pCVar10)
			pCVar10 = startNode - 11;

		pCVar8 = startNode + 3;

		if (pCVar10->pathType == 127)
			goto LAB_0002b600;

		if (cp->ai.c.targetRoute + 13 <= pCVar8)
			pCVar8 = startNode - 10;

		pCVar10 = startNode + 4;

		if (pCVar8->pathType == 127)
			goto LAB_0002b600;

		if (cp->ai.c.targetRoute + 13 <= pCVar10)
			pCVar10 = startNode - 9;

		if (pCVar10->pathType == 127)
			goto LAB_0002b600;
	}

	/* copy car */
	//memcpy(&currentCar, cp, sizeof(_CAR_DATA));

	pCVar8 = cp->ai.c.pnode + 1;

	iVar3 = cp->hd.wheel_speed;

	if (cp->ai.c.pnode->pathType != 127)
	{
		if (cp->ai.c.targetRoute + 13 <= pCVar8)
			pCVar8 = cp->ai.c.pnode - 12;

		if (pCVar8->pathType != 127)
		{
			iVar4 = CivFindStation(cp);

			/* memcpy all targetRoute */
			//memcpy(&currentCar.ai.c.targetRoute, cp->ai.c.targetRoute, sizeof(cp->ai.c.targetRoute));

			pCVar8 = cp->ai.c.pnode + 1;

			if (cp->ai.c.pnode->pathType != 127)
			{
				if (cp->ai.c.targetRoute + 13 <= pCVar8)
					pCVar8 = cp->ai.c.pnode -12;

				if (pCVar8->pathType != 127)
				{
					CivFindPointOnPath(cp, iVar4 + FIXED(iVar3) * checkFrames + sVar2, &pathPoint);

					lVar5 = ratan2(pathPoint.vx - cp->hd.where.t[0], pathPoint.vz - cp->hd.where.t[2]);

					iVar4 = ((lVar5 - cp->hd.direction) + 0x800U & 0xfff) - 0x800;
					iVar3 = maxSteer;

					if ((iVar4 <= maxSteer) && (iVar3 = iVar4, iVar4 < -maxSteer))
					{
						iVar3 = -maxSteer;
					}

					/* copy car data */
					//memcpy(cp, &currentCar, sizeof(_CAR_DATA));

					pCVar8 = startNode;

					if (startNode == cp->ai.c.pnode)
					{
						return iVar3;
					}

					do 
					{
						pCVar8->pathType = 127;
						pCVar10 = pCVar8 + 1;

						if (cp->ai.c.turnNode == (pCVar8 - cp->ai.c.targetRoute))
						{
							cp->ai.c.turnNode = -1;
						}

						if (cp->ai.c.targetRoute + 13 <= pCVar10)
							pCVar10 = pCVar8-12;

						pCVar8 = pCVar10;
					} while (pCVar10 != cp->ai.c.pnode);

					return iVar3;
				}
			}
		}
	}

LAB_0002b76c:
	cp->ai.c.thrustState = 3;
	cp->ai.c.ctrlState = 7;

	return 0;
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

// [D]
int CivFindStation(_CAR_DATA *cp)
{
	long lVar1;
	int iVar2;
	CIV_ROUTE_ENTRY *pCVar3;
	CIV_ROUTE_ENTRY *pCVar4;
	CIV_ROUTE_ENTRY *pCVar5;
	int a;
	CIV_ROUTE_ENTRY *pCVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	int iVar11;

	iVar2 = (cp->hd).where.t[0];
	iVar11 = (cp->hd).where.t[2];

	pCVar3 = cp->ai.c.targetRoute;

	a = cp->ai.c.currentNode - 1;
	if (a != -1)
	{
		pCVar6 = pCVar3;
		do {
			pCVar3 = pCVar6 + 1;

			if (cp->ai.c.targetRoute + 13 <= pCVar3)
				pCVar3 = pCVar6 - 12;
		
			a = a + -1;
			pCVar6 = pCVar3;
		} while (a != -1);
	}

	do {
		pCVar6 = pCVar3 + 1;

		if (cp->ai.c.targetRoute + 13 <= pCVar6)
			pCVar6 = pCVar3 - 12;

		if (pCVar6 == NULL) 
			break;

		iVar10 = pCVar3->x;
		iVar8 = pCVar6->x - iVar10;
		iVar9 = pCVar3->z;
		iVar7 = pCVar6->z - iVar9;
		a = iVar8 * iVar8 + iVar7 * iVar7;

		if (a < 0) 
			break;

		lVar1 = SquareRoot0(a);

		if (0 < lVar1) 
		{
			a = ((iVar2 - iVar10) * iVar8 + (iVar11 - iVar9) * iVar7) / lVar1;

			if (a < lVar1) 
			{
				cp->ai.c.pnode = pCVar3;
				return a;
			}
		}

		pCVar5 = pCVar6 + 1;

		cp->ai.c.currentNode++;

		if (cp->ai.c.currentNode > 12)
			cp->ai.c.currentNode = 0;
	
		if (cp->ai.c.targetRoute + 13 <= pCVar5) 
			pCVar5 = pCVar6 - 12;

		pCVar4 = pCVar6 + 2;
		pCVar3 = pCVar6;

		if (pCVar5->pathType == 127)
			goto LAB_0002ba88;

		if (cp->ai.c.targetRoute + 13 <= pCVar4)
			pCVar4 = pCVar6 - 11;

		pCVar5 = pCVar6 + 3;

		if (pCVar4->pathType == 127)
			goto LAB_0002ba88;

		if (cp->ai.c.targetRoute + 13 <= pCVar5) 
			pCVar5 = pCVar6 - 10;

		if (pCVar5->pathType == 127)
		{
		LAB_0002ba88:
			CreateNewNode(cp);
		}

	} while (true);

	cp->ai.c.thrustState = 3;
	cp->ai.c.ctrlState = 7;

	return 0;
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

// [D]
int CivFindPointOnPath(_CAR_DATA *cp, int station, VECTOR *ppoint)
{
	int stepSize;
	CIV_ROUTE_ENTRY *pCVar2;
	CIV_ROUTE_ENTRY *pCVar3;
	int dx;
	int dz;
	int sx;
	int sz;

	if (cp->ai.c.pnode != NULL)
	{
		pCVar2 = cp->ai.c.pnode;

		do {
			pCVar3 = pCVar2 + 1;

			if (cp->ai.c.targetRoute + 13 <= pCVar3) 
				pCVar3 = pCVar2-12;

			if (pCVar3 == NULL || pCVar3->pathType == 127)
			{
				ppoint->vx = pCVar2->x;
				ppoint->vz = pCVar2->z;

				return 1;
			}

			sx = pCVar2->x;
			sz = pCVar2->z;

			dx = pCVar3->x - sx;
			dz = pCVar3->z - sz;

			stepSize = SquareRoot0(dx * dx + dz * dz);

			if (station < stepSize) 
			{
				if (station < 0)
					station = 0;
			
				if (stepSize < 0x1000) 
				{
					ppoint->vx = sx + (dx * station) / stepSize;
					ppoint->vz = sz + (dz * station) / stepSize;
				}
				else 
				{
					stepSize >>= 4;

					ppoint->vx = sx + FIXED(((dx * 256) / stepSize) * station);
					ppoint->vz = sz + FIXED(((dz * 256) / stepSize) * station);
				}

				return 1;
			}

			station -= stepSize;
			pCVar2 = pCVar3;
		} while (pCVar3 != cp->ai.c.pnode);
	}

	cp->ai.c.thrustState = 3;
	cp->ai.c.ctrlState = 7;

	return 0;
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

// [D]
void CreateRoadblock(void)
{
	unsigned char bVar1;
	unsigned char bVar2;
	short sVar3;
	bool bVar4;
	char cVar5;
	int laneNo;
	long lVar6;
	long lVar7;
	uint uVar8;
	int x;
	int z;
	CAR_COSMETICS *car_cos;
	uint *puVar9;
	uint uVar10;
	uint uVar11;
	int iVar12;
	int x_00;
	_CAR_DATA *cp;
	int distAlongSegment;
	int z_00;
	int iVar13;
	DRIVER2_CURVE *crv;
	VECTOR startPos;
	VECTOR endPos;
	DRIVER2_STRAIGHT *str;
	VECTOR currentPos;
	int numLanes;
	int externalCopModel;
	int noMoreCars;

	crv = NULL;
	distAlongSegment = -5;
	laneNo = (int)player[0].playerCarId;
	str = NULL;
	bVar4 = false;
	z_00 = (int)car_cosmetics[3].colBox.vz;
	iVar12 = car_data[laneNo].hd.direction;
	bVar1 = MissionHeader->residentModels[3];
	baseLoc.vx = car_data[laneNo].hd.where.t[0];
	angle = 0;
	baseLoc.vz = car_data[laneNo].hd.where.t[2];

	do {
		if (requestCopCar == 0)
			laneNo = (int)rcossin_tbl[(iVar12 + angle & 0xfffU) * 2] << 3;
		else
			laneNo = (int)rcossin_tbl[(iVar12 + angle & 0xfffU) * 2] * 10;

		roadblockLoc.vx = baseLoc.vx + FIXED(laneNo) * 0x800;

		if (requestCopCar == 0)
			laneNo = (int)rcossin_tbl[(iVar12 + angle & 0xfffU) * 2 + 1] << 3;
		else
			laneNo = (int)rcossin_tbl[(iVar12 + angle & 0xfffU) * 2 + 1] * 10;

		roadblockLoc.vz = baseLoc.vz + FIXED(laneNo) * 0x800;

		roadSeg = RoadInCell(&roadblockLoc);

		if (((((roadSeg & 0xffffe000U) == 0) && ((int)(roadSeg & 0x1fffU) < NumDriver2Straights)) ||
			(((roadSeg & 0xffffe000U) == 0x4000 && ((int)(roadSeg & 0x1fffU) < NumDriver2Curves))))
			&& (-1 < roadSeg))
			break;

		if (requestCopCar == 0)
			laneNo = (int)rcossin_tbl[(iVar12 - angle & 0xfffU) * 2] << 3;

		else
			laneNo = (int)rcossin_tbl[(iVar12 - angle & 0xfffU) * 2] * 10;

		roadblockLoc.vx = baseLoc.vx + FIXED(laneNo) * 0x800;

		if (requestCopCar == 0)
			laneNo = (int)rcossin_tbl[(iVar12 - angle & 0xfffU) * 2 + 1] << 3;
		else
			laneNo = (int)rcossin_tbl[(iVar12 - angle & 0xfffU) * 2 + 1] * 10;

		roadblockLoc.vz = baseLoc.vz + FIXED(laneNo) * 0x800;

		roadSeg = RoadInCell(&roadblockLoc);

		if (((((roadSeg & 0xffffe000U) == 0) && ((int)(roadSeg & 0x1fffU) < NumDriver2Straights)) ||
			(((roadSeg & 0xffffe000U) == 0x4000 && ((int)(roadSeg & 0x1fffU) < NumDriver2Curves))))
			&& (-1 < roadSeg)) 
			break;

		if (requestCopCar == 0)
			angle = angle + 0x5d;
		else
			angle = angle + 0x49;

	} while (angle < 0x800);

	if (((roadSeg & 0xffffe000U) != 0) || (NumDriver2Straights <= (int)(roadSeg & 0x1fffU))) 
	{
		if ((roadSeg & 0xffffe000U) != 0x4000)
			return;

		if (NumDriver2Curves <= (int)(roadSeg & 0x1fffU))
			return;

	}

	if (roadSeg < 0)
		return;

	if (((roadSeg & 0xffffe000U) == 0) && ((int)(roadSeg & 0x1fffU) < NumDriver2Straights))
	{
		str = Driver2StraightsPtr + roadSeg;
		dx = roadblockLoc.vx - str->Midx;
		dz = roadblockLoc.vz - str->Midz;
		lVar6 = ratan2(dx, dz);
		sVar3 = str->angle;
		lVar7 = SquareRoot0(dx * dx + dz * dz);
		uVar10 = (uint)str->length;
		uVar8 = z_00 * 3;
		distAlongSegment = (uint)(str->length >> 1) + FIXED(rcossin_tbl[(sVar3 - lVar6 & 0xfffU) * 2 + 1] * lVar7);

		if ((int)uVar10 < z_00 * 6)
			return;

		if (distAlongSegment < (int)uVar8)
			distAlongSegment = uVar8;
	
		if ((int)(uVar10 - distAlongSegment) < (int)uVar8) 

			distAlongSegment = uVar10 + z_00 * -3;

		bVar2 = str->NumLanes;
	}
	else 
	{
		if (((roadSeg & 0xffffe000U) != 0x4000) || ((NumDriver2Curves <= (int)(roadSeg & 0x1fffU) || (roadSeg < 0)))) 
			goto LAB_0002c33c;

		crv = Driver2CurvesPtr + roadSeg + -0x4000;

		if ((int)(((int)crv->end - (int)crv->start & 0xfffU) * crv->inside * 0xb) / 7 < z_00 * 6) 
			return;
	
		currentAngle = ratan2(roadblockLoc.vx - crv->Midx, roadblockLoc.vz - crv->Midz);
		uVar8 = 0x80;

		if ((9 < crv->inside) && (uVar8 = 0x20, crv->inside < 0x14)) 
		{
			uVar8 = 0x40;
		}

		uVar10 = (currentAngle & 0xfffU) - (int)crv->start;
		distAlongSegment = uVar10 & 0xf80;

		if ((9 < crv->inside) && (distAlongSegment = uVar10 & 0xfe0, crv->inside < 0x14)) 
		{
			distAlongSegment = uVar10 & 0xfc0;
		}

		if (distAlongSegment <= uVar8)
			distAlongSegment = uVar8;

		uVar8 = ((int)crv->end - (int)crv->start) - uVar8 & 0xfff;

		if (uVar8 <= (uint)distAlongSegment)
			distAlongSegment = uVar8;

		bVar2 = crv->NumLanes;
	}
	numLanes = ((u_char)bVar2 & 0xf) << 1;

LAB_0002c33c:
	GetNodePos(str, NULL, crv, distAlongSegment, NULL, (int*)&startPos.vx, (int*)&startPos.vz, 0);

	laneNo = numLanes-1;
	GetNodePos(str, NULL, crv, distAlongSegment, NULL, (int*)&endPos, (int*)&endPos.vz, laneNo);

	iVar12 = 0x100;
	uVar8 = ratan2(endPos.vx - startPos.vx, endPos.vz - startPos.vz);

	if (0x100 < laneNo * 0x200)
	{
		do {
			currentPos.vx = startPos.vx + FIXED(iVar12 * rcossin_tbl[(uVar8 & 0xfff) * 2] );
			currentPos.vz = startPos.vz + FIXED(iVar12 * rcossin_tbl[(uVar8 & 0xfff) * 2 + 1]);

			if (str == NULL) 
			{
			LAB_0002c49c:
				if (crv != NULL) 
				{
					z_00 = iVar12;

					if (((int)(u_char)crv->AILanes >> (z_00 >> 10 & 0x1fU) & 1U) == 0)
						goto LAB_0002c4cc;
				}
			LAB_0002c4e4:
				lVar6 = Random2(0);
				z_00 = iVar12;

				z_00 = CreateStationaryCivCar(uVar8 + (lVar6 * 0x10001 >> (z_00 >> 9 & 0x1fU) & 0x3ffU) + -0x200, 0, 0, (long(*)[4])&currentPos, (uint)bVar1, 0, 2);

				if (z_00 == -1)
				{
					bVar4 = true;
					break;
				}

				car_cos = car_data[z_00].ap.carCos;

				if (QuickBuildingCollisionCheck((VECTOR *)car_data[z_00].hd.where.t, car_data[z_00].hd.direction, (int)(car_cos->colBox).vz, (int)(car_cos->colBox).vx, 0x14) != 0)
				{
					testNumPingedOut++;
					if (car_data[z_00].controlType == 2) 
					{
						if ((car_data[z_00].controlFlags & 1) != 0)
							numCopCars--;

						numCivCars--;

						if (car_data[z_00].ai.c.thrustState == 3 && car_data[z_00].ai.c.ctrlState == 5)
							numParkedCars--;
					}
					else if ((PingOutCivsOnly != 0) && (x = valid_region(car_data[z_00].hd.where.t[0], car_data[z_00].hd.where.t[2]), x != 0))
						goto LAB_0002c678;

					puVar9 = (uint *)car_data[z_00].inform;

					if (puVar9 != NULL)
						*puVar9 = *puVar9 ^ 0x40000000;

					ClearMem((char *)(car_data + z_00), sizeof(_CAR_DATA));
					car_data[z_00].controlType = 0;
				}
			LAB_0002c678:
				cp = car_data + 19;
				if (true) 
				{
					do {
						if ((cp->controlType != 0) &&((*(uint *)&cp->hndType & 0x2ff00) != 0x20200)) 
						{
							x = (cp->hd).where.t[0];
							dx = x - currentPos.vx;
							z_00 = (cp->hd).where.t[2];
							dz = z_00 - currentPos.vz;

							if (dx * dx + dz * dz < 360000) 
							{
								testNumPingedOut++;

								if (cp->controlType == 2) 
								{
									if ((cp->controlFlags & 1) != 0)
										numCopCars--;
	
									numCivCars = numCivCars + -1;

									if ((cp->ai.c.thrustState == 3) && (cp->ai.c.ctrlState == 5)) 
										numParkedCars--;

								}
								else if ((PingOutCivsOnly != 0) && (z_00 = valid_region(x, z_00), z_00 != 0))
									goto LAB_0002c7e4;

								puVar9 = (uint *)cp->inform;
								if (puVar9 != NULL)
									*puVar9 = *puVar9 ^ 0x40000000;

								ClearMem((char *)cp, sizeof(_CAR_DATA));
								cp->controlType = 0;
							}
						}
					LAB_0002c7e4:
						cp--;
					} while (cp >= car_data);
				}
			}
			else 
			{
				z_00 = iVar12;

				if (((int)(u_char)str->AILanes >> (z_00 >> 10 & 0x1fU) & 1U) != 0)
					goto LAB_0002c49c;
			LAB_0002c4cc:

				if (CellEmpty(&currentPos, (int)car_cosmetics[3].colBox.vz) != 0) 
					goto LAB_0002c4e4;
			}

			iVar12 = iVar12 + 0x400;
		} while (iVar12 < laneNo * 0x200);
	}

	if ((!bVar4) && (gCopDifficultyLevel != 0)) 
	{
		lVar6 = ratan2(baseLoc.vx - startPos.vx, baseLoc.vz - startPos.vz);
		laneNo = 0x400;

		if ((((lVar6 - uVar8) + 0x800 & 0xfff) - 0x800 & 0xfff) < 0x800) 
			laneNo = -0x400;

		uVar10 = uVar8;

		if (gCopDifficultyLevel == 1)
			uVar10 = uVar8 - laneNo;

		uVar11 = uVar8 + laneNo & 0xfff;
		laneNo = startPos.vx + FIXED((int)rcossin_tbl[uVar11 * 2] * 0x5dc);
		iVar12 = startPos.vz + FIXED((int)rcossin_tbl[uVar11 * 2 + 1] * 0x5dc);
		z_00 = (maxCivCars - numCivCars) + 2;
		x = numLanes / 2 + -1;

		if (0 < z_00)
		{
			iVar13 = x;
			if (z_00 < x) 
				iVar13 = z_00;

			z_00 = 0;
			if (0 < iVar13) 
			{
				z = 0;
				do {

					x_00 = ((x * (z + 1)) / (iVar13 << 1)) * 0x400;
					z = x_00 + 0x300;

					currentPos.vx = laneNo + FIXED(z * rcossin_tbl[(uVar8 & 0xfff) * 2]);
					currentPos.vz = iVar12 + FIXED(z * rcossin_tbl[(uVar8 & 0xfff) * 2 + 1]);

					test42 = z;
					lVar6 = Random2(0);

					z = CreateStationaryCivCar(uVar10 + (lVar6 * 0x10001 >> (z >> 9 & 0x1fU) & 0x3ffU) + -0x200,0, 0, (long(*)[4])&currentPos, (uint)bVar1, 0, 2);

					if (z == -1) 
						break;

					car_cos = car_data[z].ap.carCos;

					if (QuickBuildingCollisionCheck((VECTOR *)car_data[z].hd.where.t, car_data[z].hd.direction, (int)(car_cos->colBox).vz, (int)(car_cos->colBox).vx, 0x14) != 0)
					{
						testNumPingedOut++;
						if (car_data[z].controlType == 2)
						{
							if ((car_data[z].controlFlags & 1) != 0) 
								numCopCars--;

							numCivCars = numCivCars + -1;

							if (car_data[z].ai.c.thrustState == 3 && car_data[z].ai.c.ctrlState == 5)
								numParkedCars--;

						}
						else if (PingOutCivsOnly != 0 && (valid_region(car_data[z].hd.where.t[0], car_data[z].hd.where.t[2]) != 0))
							goto LAB_0002cbac;

						puVar9 = (uint *)car_data[z].inform;
						if (puVar9 != NULL)
							*puVar9 = *puVar9 ^ 0x40000000;

						ClearMem((char *)(car_data + z), sizeof(_CAR_DATA));
						car_data[z].controlType = 0;
					}

				LAB_0002cbac:
					cp = car_data + 0x13;
					z_00 = z_00 + 1;
					if (true) 
					{
						do {
							if ((cp->controlType != 0) && ((*(uint *)&cp->hndType & 0x2ff00) != 0x20200)) 
							{
								x_00 = (cp->hd).where.t[0];
								dx = x_00 - currentPos.vx;
								z = (cp->hd).where.t[2];
								dz = z - currentPos.vz;

								if (dx * dx + dz * dz < 360000) 
								{
									testNumPingedOut++;
									if (cp->controlType == 2) 
									{
										if ((cp->controlFlags & 1) != 0) 
											numCopCars = numCopCars + -1;

										numCivCars--;

										if (cp->ai.c.thrustState == 3 && cp->ai.c.ctrlState == 5) 
											numParkedCars--;
									}
									else if ((PingOutCivsOnly != 0) && (z = valid_region(x_00, z), z != 0))
										goto LAB_0002cd18; // continue

									puVar9 = (uint *)cp->inform;
									if (puVar9 != NULL)
										*puVar9 = *puVar9 ^ 0x40000000;

									ClearMem((char *)cp, sizeof(_CAR_DATA));
									cp->controlType = 0;
								}
							}
						LAB_0002cd18:
							cp--;
						} while (cp >= car_data);
					}
					z = z_00 * 2;
				} while (z_00 < iVar13);
			}
		}
	}
	requestRoadblock = 0;
	uVar8 = Random2(0);
	roadblockDelay = roadblockDelayDiff[gCopDifficultyLevel] + (uVar8 & 0xff);
	roadblockCount = roadblockDelay;

	PlaceRoadBlockCops();
}





