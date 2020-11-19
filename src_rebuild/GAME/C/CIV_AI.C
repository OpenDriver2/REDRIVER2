#include "DRIVER2.H"
#include "CIV_AI.H"

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
#include "GAMESND.H"
#include "SOUND.H"
#include "BCOLLIDE.H"
#include "LEADAI.H"
#include "MAIN.H"
#include "PEDEST.H"
#include "OBJCOLL.H"

#include "INLINE_C.H"
#include "OVERLAY.H"
#include "STRINGS.H"

const u_char speedLimits[3] = { 56, 97, 138 };

struct
{
	int NumPingedIn;
	int OffRoad;
	int NotDrivable;
	int TooShortStr;
	int NearEndStr;
	int TooShortCrv;
	int NearEndCrv;
	int TooCloseNuddaCar;
	int TooClosePlayer;
	int InvalidRegion;
} civPingTest = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

char modelRandomList[] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 1, 0, 4 };
unsigned char reservedSlots[MAX_CARS] = { 0 };

int distFurthestCivCarSq = 0;
char furthestCivID = 0;
char makeLimoPullOver = 0;
int frameStart = 0;

char limoId = 0;	// Seems to be unused
char playerNum = 0;
char PingOutCivsOnly = 0;
char cookieCount = 0;
int roadSeg = 0;
int testNumPingedOut = 0;
int currentAngle = 0;
int closeEncounter = 3;

char junctionLightsPhase[2];

int test42 = 0;
int test123 = 0;
int test555 = 0;

// check path node validty in cars
#define IS_NODE_VALID(cp, node) \
	((node) >= cp->ai.c.targetRoute && (node) <= cp->ai.c.targetRoute+12)

#define GET_NEXT_NODE(cp, relNode)\
	(relNode + 1 > cp->ai.c.targetRoute+12 ? relNode - 12 : relNode + 1)

#define GET_NODE_ID(cp, node)	int((node) - cp->ai.c.targetRoute)

#ifdef _DEBUG
#define CIV_STATE_SET_CONFUSED(cp) \
	printInfo("CIV confused: at %s, %d\n", __FUNCTION__, __LINE__);\
	cp->ai.c.thrustState = 3; cp->ai.c.ctrlState = 7;
#else
#define CIV_STATE_SET_CONFUSED(cp) \
	cp->ai.c.thrustState = 3; cp->ai.c.ctrlState = 7;
#endif


// decompiled code
// original method signature: 
// int /*$ra*/ InitCar(CAR_DATA *cp /*$s0*/, int direction /*$s6*/, LONGVECTOR* startPos /*$s2*/, unsigned char control /*$s4*/, int model /*stack 16*/, int palette /*stack 20*/, char *extraData /*stack 24*/)
 // line 717, offset 0x00023de8
	/* begin block 1 */
		// Start line: 718
		// Start offset: 0x00023DE8
		// Variables:
	// 		VECTOR tmpStart; // stack offset -48
	/* end block 1 */
	// End offset: 0x00024028
	// End Line: 786

	/* begin block 2 */
		// Start line: 1434
	/* end block 2 */
	// End Line: 1435

// [D] [T]
int InitCar(CAR_DATA* cp, int direction, LONGVECTOR* startPos, unsigned char control, int model, int palette, char* extraData)
{
	VECTOR tmpStart;

	ClearMem((char*)cp, sizeof(CAR_DATA));

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

	// not valid request
	if (control == CONTROL_TYPE_NONE)
		return 1;

	InitCarPhysics(cp, (LONGVECTOR *)&tmpStart, direction);
	cp->ap.palette = palette;

	cp->controlType = control;

	switch (control)
	{
	case 1:
	case 7:
		// player car or cutscene car
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
		// free roamer lead car
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
// CAR_DATA * /*$ra*/ FindClosestCar(int x /*$t4*/, int y /*$a1*/, int z /*$a2*/, int *distToCarSq /*$a3*/)
 // line 891, offset 0x0002d11c
	/* begin block 1 */
		// Start line: 892
		// Start offset: 0x0002D11C
		// Variables:
	// 		CAR_DATA *retCar; // $t2
	// 		CAR_DATA *lcp; // $t0
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

// [D] [T]
CAR_DATA* FindClosestCar(int x, int y, int z, int* distToCarSq)
{
	uint distSq;
	CAR_DATA* lcp;
	uint retDistSq;
	CAR_DATA* retCar;
	int dx; // $a0
	int dz; // $v1

	retCar = NULL;
	retDistSq = 0x7fffffff; // INT_MAX
	lcp = car_data;

	do {

		if (lcp->controlType != CONTROL_TYPE_NONE)
		{
			if (ABS(y - lcp->hd.where.t[1]) < 800)
			{
				dx = x - lcp->hd.where.t[0];
				dz = z - lcp->hd.where.t[2];

				if (ABS(dx) < 4096 && ABS(dz) < 4096)
				{
					distSq = dx * dx + dz * dz;

					if (distSq < retDistSq)
					{
						retDistSq = distSq;
						retCar = lcp;
					}
				}
			}
		}
		lcp++;
	} while (lcp < &car_data[MAX_CARS]);

	if (distToCarSq)
		*distToCarSq = retDistSq;

	return retCar;
}



// decompiled code
// original method signature: 
// int /*$ra*/ NotTravellingAlongCurve(int x /*$a0*/, int z /*$a1*/, int dir /*$s0*/, DRIVER2_CURVE *cv /*$a3*/)
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

// [D] [T]
int NotTravellingAlongCurve(int x, int z, int dir, DRIVER2_CURVE* cv)
{
	int curveDir;
	int cvDiff;

	curveDir = ratan2(x - cv->Midx, z - cv->Midz);
	cvDiff = ((dir - curveDir) + 0x800U & 0xfff) - 0x800U;

	return (cvDiff < 1) << 0xb;
}

// decompiled code
// original method signature: 
// void /*$ra*/ CivCarFX(CAR_DATA *cp /*$s0*/)
 // line 930, offset 0x0002d084
	/* begin block 1 */
		// Start line: 1860
	/* end block 1 */
	// End Line: 1861

// [D] [T]
void CivCarFX(CAR_DATA* cp)
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
// int /*$ra*/ GetNextRoadInfo(CAR_DATA *cp /*$s7*/, int randomExit /*$a1*/, int *turnAngle /*stack 8*/, int *startDist /*stack 12*/, CIV_ROUTE_ENTRY *oldNode /*stack 16*/)
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
	// 		DRIVER2_JUNCTION *jn; // $t5
	// 		DRIVER2_CURVE *cv; // $s1
	// 		DRIVER2_STRAIGHT *st; // $s5
	// 		DRIVER2_STRAIGHT *tmpSt; // $a2
	// 		DRIVER2_CURVE *tmpCv; // $s1
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
			// 		DRIVER2_CURVE *cv; // $s1

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
			// 		DRIVER2_JUNCTION *jn; // $t5
			// 		int currentExit; // $a2
			// 		int turnAngle; // $t1
			// 		CAR_DATA *cp; // $s7
			// 		CIV_ROUTE_ENTRY *oldNode; // $t7

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
				// 		DRIVER2_CURVE *cv; // $s1

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
				// 		DRIVER2_CURVE *cv; // $s1

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

// [D] [T]
// BUGS: sometimes not getting right lane when road direction switched
int GetNextRoadInfo(CAR_DATA* cp, int randomExit, int* turnAngle, int* startDist, CIV_ROUTE_ENTRY* oldNode)
{
	unsigned long junctionFlags;
	DRIVER2_JUNCTION* jn;

	DRIVER2_ROAD_INFO currentRoadInfo;
	DRIVER2_ROAD_INFO roadInfo;

	int currentRoadId = 0;
	int tmpNewRoad[2];
	int newExit = 0;
	int tmpNewLane[2];
	int laneFit[2];
	DRIVER2_STRAIGHT* tmpStr[2];
	DRIVER2_CURVE* tmpCrv[2];
	short validExitIdx[4];

	int newLane;
	int newRoad;

	int numExits;
	int leftLane;
	int rightLane;

	int oldOppDir;
	int oppDir;
	int turnDir;
	int currentLaneDir;

	currentRoadId = cp->ai.c.currentRoad;

	if (GetSurfaceRoadInfo(&currentRoadInfo, currentRoadId))
	{
		int widthInLanes;
		int laneNo;
		int count;

		widthInLanes = ROAD_WIDTH_IN_LANES(&currentRoadInfo);

		currentLaneDir = ROAD_LANE_DIR(&currentRoadInfo, cp->ai.c.currentLane);

		if (currentRoadInfo.straight)
		{
			oldOppDir = (currentRoadInfo.straight->angle - oldNode->dir) + 0x400U & 0x800;
		}
		else
		{
			int dx, dz;
			dx = oldNode->x - currentRoadInfo.curve->Midx;
			dz = oldNode->z - currentRoadInfo.curve->Midz;

			oldOppDir = (((oldNode->dir - ratan2(dx, dz)) + 0x800U & 0xfff) - 0x800);
			oldOppDir = (oldOppDir < 1) << 0xb;
		}

		// first road is picked from road direction
		tmpNewRoad[0] = ((short*)currentRoadInfo.ConnectIdx)[(oldOppDir > 0) * 2];

		// and second picked from lane direction
		tmpNewRoad[1] = ((short*)currentRoadInfo.ConnectIdx)[(currentLaneDir > 0) ? 3 : 1];

		count = widthInLanes;		// counter
		laneNo = widthInLanes;		// bestLane

		do
		{
			count--;
			if (ROAD_IS_AI_LANE(&currentRoadInfo, count) && !ROAD_IS_PARKING_ALLOWED_AT(&currentRoadInfo, count))
			{
				test42 = ROAD_LANE_DIR(&currentRoadInfo, count);
				laneNo = count;
			}
		} while (count >= 0);

		if (currentLaneDir == 0)
			leftLane = laneNo & 0xff;
		else
			rightLane = laneNo & 0xff;

		// ifhas fast lane, use second lane
		count = ROAD_HAS_FAST_LANES(&currentRoadInfo);
		laneNo = widthInLanes;	

		while (count < widthInLanes)
		{
			if (ROAD_IS_AI_LANE(&currentRoadInfo, count) && !ROAD_IS_PARKING_ALLOWED_AT(&currentRoadInfo, count))
			{
				test555 = ROAD_LANE_DIR(&currentRoadInfo, count) ^ 1;
				laneNo = count;

				if (test555 == 0)
				{
					if (currentLaneDir != 0)
						break;
				}
				else
				{
					if (currentLaneDir == 0)
						break;
				}
			}
			laneNo = widthInLanes;
			count++;
		}

		if (currentLaneDir != 0)
			leftLane = laneNo & 0xff;
		else
			rightLane = laneNo & 0xff;
	}

	newLane = -1;
	
	if (IS_JUNCTION_SURFACE(tmpNewRoad[0]))
	{
		int bestExit;

		int exitFrom;
		int exitCnt;
		int rnd;
		numExits = 0;
		
		cp->ai.c.changeLaneCount = 0;
		jn = GET_JUNCTION(tmpNewRoad[0]);

		exitFrom = -1;	// best exit id

		// check if road is valid for this junction
		// by determining connection with junction
		exitCnt = 0;
		while(exitCnt < 4)
		{
			if(jn->ExitIdx[exitCnt] == currentRoadId)
			{
				exitFrom = exitCnt;
				break;
			}
			exitCnt++;
		}

		if (exitFrom == -1)
		{
			CIV_STATE_SET_CONFUSED(cp);
			return 0;
		}

		// check directions of exits
		//printWarning("Checking directions, exitFrom: %d, \n", exitFrom);
		exitCnt = 0;
		do {
			int exitSurfId;
			int exitIdx = (exitFrom + exitCnt + 1) % 4;
			int valid;
			
			valid = 0;

			exitSurfId = jn->ExitIdx[exitIdx];
			
			if (exitSurfId != -1)
			{
				int exitDir;
				exitDir = ((exitIdx + 4) - exitFrom) % 4;
				//exitDir = exitDir - (exitDir / 4) * 4;

				if (exitDir == 1)
					*turnAngle = -1024;
				else if (exitDir == 2)
					*turnAngle = 0;
				else if (exitDir == 3)
					*turnAngle = 1024;
				else
					*turnAngle = 0;

				test123 = 666;
				test555 = 666;
				test42 = 666;
				
				turnDir = oldNode->dir + *turnAngle;

				if (GetSurfaceRoadInfo(&roadInfo, exitSurfId))
				{
					int turnAng;
					int dx, dz;
					int laneCount;

					laneCount = ROAD_WIDTH_IN_LANES(&roadInfo);

					if(roadInfo.straight)
					{
						oppDir = (roadInfo.straight->angle - turnDir) + 1024U & 0x800;
					}
					else
					{
						dx = oldNode->x - roadInfo.curve->Midx;
						dz = oldNode->z - roadInfo.curve->Midz;

						oppDir = ((turnDir - ratan2(dx, dz)) + 2048U & 0xfff) - 2048; // [A]
						oppDir = (oppDir < 1) << 0xb;
					}

					turnAng = *turnAngle;
					
					if (oppDir == 0)
						turnAng = -turnAng;

					if (turnAng == 0) // going forward
					{
						if (oppDir != oldOppDir) // next road is flipped
							newLane = ROAD_WIDTH_IN_LANES(&roadInfo) - (cp->ai.c.currentLane + 1);
						else
							newLane = cp->ai.c.currentLane;

						// goes on invalid lane?
						// [A] bug fix with exitDir == 0
						if (oppDir == 0 && exitDir == 0 || !ROAD_IS_AI_LANE(&roadInfo, newLane))
							newLane = -1;
					}
					else if (turnAng == -1024) // going left
					{
						int count;

						//printInfo("check left\n");

						count = ROAD_HAS_FAST_LANES(&roadInfo); // lane counter
						newLane = laneCount;

						// check if allowed to go on any of lanes
						while (count < laneCount)
						{
							if (ROAD_IS_AI_LANE(&roadInfo, count) && !ROAD_IS_PARKING_ALLOWED_AT(&roadInfo, count))
							{
								test555 = (ROAD_LANE_DIR(&roadInfo, count) ^ 1) & 1;
								newLane = count;

								if (test555 == 0)
								{
									if (oppDir != 0)
										break;
								}
								else
								{
									if (oppDir == 0)
										break;
								}
							}

							count++;
							newLane = laneCount;
						}
					}
					else if (turnAng == 1024)
					{
						int count;

						count = laneCount;		// lane counter
						newLane = laneCount;

						do
						{
							if (ROAD_IS_AI_LANE(&roadInfo, count) && !ROAD_IS_PARKING_ALLOWED_AT(&roadInfo, count))
							{
								test42 = (ROAD_LANE_DIR(&roadInfo, count) ^ 1) & 1;
								newLane = count;
							}
							count--;
						} while (count >= 0);
					}

					// validate lane
					if (newLane > -1 && newLane < laneCount)
					{
						valid = ROAD_IS_AI_LANE(&roadInfo, newLane) && !ROAD_IS_PARKING_ALLOWED_AT(&roadInfo, newLane);
					}
				}
			}

			if (valid)
			{
				validExitIdx[exitCnt] = exitIdx;
				numExits++;
			}
			else
			{
				validExitIdx[exitCnt] = 42;
			}

			// only need 3 cycles because we don't want make U-turns
			exitCnt++;
		} while (exitCnt < 3);

		if (leftLane != rightLane && numExits != 1)
		{
			if (cp->ai.c.currentLane == leftLane)
			{
				if (validExitIdx[2] != 42)
					numExits--;
				
				validExitIdx[2] = 42;
			}
			else if (cp->ai.c.currentLane == rightLane)
			{
				if (validExitIdx[0] != 42)
					numExits--;
				
				validExitIdx[0] = 42;
			}
			else if (validExitIdx[1] != 42)
			{
				if (validExitIdx[0] != 42)
					numExits--;
				
				if (validExitIdx[2] != 42)
					numExits--;
				
				validExitIdx[2] = 42;
				validExitIdx[0] = 42;
			}
		}

		if (numExits < 1)
		{
			CIV_STATE_SET_CONFUSED(cp);
			return 0;
		}
		
		// randomize exit selection
		rnd = Random2(0) % 3;

		do
		{
			bestExit = validExitIdx[rnd % 3];
			rnd++;
		} while (bestExit == 42);
		
		newRoad = jn->ExitIdx[bestExit];

		if (turnAngle != NULL)
		{
			int invExit;
			invExit = (bestExit + 4 - exitFrom) % 4;
			//invExit = invExit - (invExit / 4) * 4;

			if (invExit == 1)
				*turnAngle = -1024;
			else if (invExit > 1 && invExit != 2 && invExit == 3)
				*turnAngle = 1024;
			else
				*turnAngle = 0;

			test42 = exitFrom;
			test555 = bestExit;
		}

		junctionFlags = jn->flags;

		// manage states
		if (cp->ai.c.ctrlState != 8)
		{
			cp->ai.c.ctrlState = 0;

			if ((junctionFlags & 1) == 0)
			{
				int yield = 0;

				if (exitFrom == 0 || exitFrom == 2)
					yield = 1;

				if ((junctionFlags & 2) == 0)
				{
					cp->ai.c.ctrlState = 4;

					if (!yield)
						cp->ai.c.ctrlNode = oldNode;
					else if (*turnAngle != 0)
						cp->ai.c.ctrlNode = oldNode;
					else
						cp->ai.c.ctrlState = 6;
				}
				else
				{
					cp->ai.c.ctrlState = 4;

					if (yield)
						cp->ai.c.ctrlNode = oldNode;
					else if (*turnAngle != 0)
						cp->ai.c.ctrlNode = oldNode;
					else
						cp->ai.c.ctrlState = 6;
				}
			}
			else
			{
				cp->ai.c.trafficLightPhaseId = (exitFrom & 1);
				cp->ai.c.ctrlState = 1;

				if (junctionLightsPhase[exitFrom & 1] == 3)
				{
					if (*turnAngle != 0)
						cp->ai.c.ctrlNode = oldNode;
					else
						cp->ai.c.ctrlState = 6;
				}
				else
					cp->ai.c.ctrlNode = oldNode;
			}
		}

		if(!GetSurfaceRoadInfo(&roadInfo, newRoad))
		{
			CIV_STATE_SET_CONFUSED(cp);
			return 0;
		}

		turnDir = oldNode->dir + *turnAngle;

		{
			int numLanes;
			int turnAng;

			numLanes = ROAD_WIDTH_IN_LANES(&roadInfo);
			turnAng = *turnAngle;

			if (roadInfo.straight)
			{
				oppDir = (turnDir - roadInfo.straight->angle) + 1024 & 0x800;
			}
			else
			{
				int dx, dz;
				dx = oldNode->x - roadInfo.curve->Midx;
				dz = oldNode->z - roadInfo.curve->Midz;

				oppDir = (((turnDir - ratan2(dx, dz)) + 0x800U & 0xfff) - 0x800);
				oppDir = (oppDir < 1) << 0xb;
			}

			if (turnAng == 0)
			{
				//printWarning("car %d check forward lane\n", cp->id);
				
				if (oppDir == oldOppDir)
				{
					newLane = cp->ai.c.currentLane;
				}
				else
				{
					newLane = numLanes - (cp->ai.c.currentLane + 1);

					//if (newLane == 0)// [A] temporary hack
					//	newLane++;
				}

				if (ROAD_LANE_DIR(&roadInfo, newLane))
				{
					if (oppDir == 0)
						newLane = -1;
				}
				else
				{
					if (oppDir != 0)
						newLane = -1;
				}

				if (!ROAD_IS_AI_LANE(&roadInfo, newLane))
					newLane = -1;
			}
			else if (turnAng == -1024)
			{
				int count;
				
				count = ROAD_HAS_FAST_LANES(&roadInfo);
				newLane = numLanes;

				// check if allowed to go on any of lanes
				while (count < numLanes)
				{
					if (ROAD_IS_AI_LANE(&roadInfo, count) && !ROAD_IS_PARKING_ALLOWED_AT(&roadInfo, count))
					{
						test555 = (ROAD_LANE_DIR(&roadInfo, count) ^ 1) & 1;
						newLane = count;

						if (test555 == 0)
						{
							if (oppDir != 0)
								break;
						}
						else
						{
							if (oppDir == 0)
								break;
						}
					}

					count++;
					newLane = numLanes;
				}

				//printWarning("car %d check left lane, chosen %d\n", cp->id, newLane);
			}
			else if (turnAng == 1024)
			{
				int count;

				count = numLanes;
				newLane = numLanes;

				do
				{
					if (ROAD_IS_AI_LANE(&roadInfo, count) && !ROAD_IS_PARKING_ALLOWED_AT(&roadInfo, count))
					{
						test42 = (ROAD_LANE_DIR(&roadInfo, count) ^ 1) & 1;

						if (test42 == 0)
						{
							if (oppDir != 0)
								newLane = count;
						}
						else
						{
							if (oppDir == 0)
								newLane = count;
						}
						
					}
					count--;
				} while (count >= 0);

				//printWarning("car %d check right lane, chosen %d\n", cp->id, newLane);
			}

			if (*turnAngle != 0)
			{
				if (numLanes - 1 == newLane)
				{
					// [A] might be incorrect
					if (ROAD_LANE_DIR(&roadInfo, newLane) == ROAD_LANE_DIR(&roadInfo, newLane - 1))
						newLane = newLane - 1;
				}
				else if (newLane == 0)
				{
					// [A] might be incorrect
					if (ROAD_LANE_DIR(&roadInfo, 1) == ROAD_LANE_DIR(&roadInfo, newLane + 1))
						newLane = newLane + 1;
				}
			}
		}
	}
	else
	{
		// road continuation using connections
		int roadCnt;
		
		if (turnAngle == NULL)
		{
			CIV_STATE_SET_CONFUSED(cp);
			return 0;
		}

		*turnAngle = 0;
		newExit = -1;
		numExits = 0;
		
		if (tmpNewRoad[0] != -1)
			numExits++;
		
		if (tmpNewRoad[1] != -1)
			numExits++;

		// check the connections
		// determine new lanes on possible new roads based on the old node position
		for (roadCnt = 0; roadCnt < 2; roadCnt++)
		{
			if (tmpNewRoad[roadCnt] != -1)
			{
				int dx, dz;
				int numLanes;

				numLanes = 0;

				if (GetSurfaceRoadInfo(&roadInfo, tmpNewRoad[roadCnt]))
				{
					numLanes = ROAD_WIDTH_IN_LANES(&roadInfo);

					// determine new lane by old node position
					if(roadInfo.straight)
					{
						dx = (oldNode->x - roadInfo.straight->Midx);
						dz = (oldNode->z - roadInfo.straight->Midz);

						tmpStr[roadCnt] = roadInfo.straight;
						tmpNewLane[roadCnt] = ROAD_LANES_COUNT(&roadInfo) - (FIXEDH(dx * rcossin_tbl[(roadInfo.straight->angle & 0xfff) * 2 + 1] - dz * rcossin_tbl[(roadInfo.straight->angle & 0xfff) * 2]) + 512 >> 9);

					}
					else
					{
						dx = oldNode->x - roadInfo.curve->Midx;
						dz = oldNode->z - roadInfo.curve->Midz;

						tmpCrv[roadCnt] = roadInfo.curve;
						tmpNewLane[roadCnt] = (SquareRoot0(dx * dx + dz * dz) >> 9) - roadInfo.curve->inside * 2;
					}
				}

				// [A] if there are more than one connections we check the bounds strictly
				if(numExits > 1)
				{
					if (tmpNewLane[roadCnt] < 0 || tmpNewLane[roadCnt] >= numLanes)
					{
						laneFit[roadCnt] = 666;
						continue;
					}
					numExits--;	// there has to be one exit
				}

				// fit new lane
				newLane = tmpNewLane[roadCnt];
				
				if (newLane < 0)
					laneFit[roadCnt] = newLane;
				else if (newLane <= numLanes - 1)
					laneFit[roadCnt] = 0;
				else
					laneFit[roadCnt] = newLane - numLanes - 1;

				// clamp lane
				if (tmpNewLane[roadCnt] >= numLanes - 1)
					tmpNewLane[roadCnt] = numLanes - 1;

				if (tmpNewLane[roadCnt] < 0)
					tmpNewLane[roadCnt] = 0;
				
				// set this a s correct exit
				newExit = roadCnt;
			}
			else
			{
				laneFit[roadCnt] = 666;
			}
		}

		if (newExit == -1 || laneFit[newExit] == 666)
		{
			CIV_STATE_SET_CONFUSED(cp);
			return 0;
		}

		newExit = (ABS(laneFit[0]) < ABS(laneFit[1])) ^ 1;
	
		newRoad = tmpNewRoad[newExit];
		newLane = tmpNewLane[newExit];
		
		if (cp->ai.c.ctrlState != 7)
		{
			// [A] removed old lane fitting code
			
			if (laneFit[newExit] != 0)
			{
				cp->ai.c.turnNode = GET_NODE_ID(cp, GET_NEXT_NODE(cp, oldNode));
				cp->ai.c.turnDir = ROAD_LANE_DIR(&roadInfo, laneFit[newExit]);				
			}
		}
	}

	if (newLane < 0)
	{
		CIV_STATE_SET_CONFUSED(cp);
		return 0;
	}

	// determine distance and speed limit
	if (startDist != NULL)
	{
		if (GetSurfaceRoadInfo(&roadInfo, newRoad))
		{
			if(roadInfo.straight)
			{
				if (ROAD_LANE_DIR(&roadInfo, newLane))
					*startDist = roadInfo.straight->length;
				else
					*startDist = 0;
			}
			else
			{
				if (ROAD_LANE_DIR(&roadInfo, newLane))
					*startDist = roadInfo.curve->end - roadInfo.curve->start & 0xfff;
				else
					*startDist = 0;
			}

			cp->ai.c.maxSpeed = speedLimits[ROAD_SPEED_LIMIT(&roadInfo)];
		}
	}

	if (newRoad < 0)
	{
		CIV_STATE_SET_CONFUSED(cp);
		return 0;
	}

	cp->ai.c.currentLane = newLane;

	return newRoad;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitNodeList(CAR_DATA *cp /*$s6*/, char *extraData /*$s7*/)
 // line 1365, offset 0x00026964
	/* begin block 1 */
		// Start line: 1366
		// Start offset: 0x00026964
		// Variables:
	// 		int i; // $v1
	// 		CIV_ROUTE_ENTRY *cr; // $s5
	// 		int dx; // $s1
	// 		int dz; // $s2
	// 		int surfInd; // $s4

		/* begin block 1.1 */
			// Start line: 1397
			// Start offset: 0x00026A04
			// Variables:
		// 		int theta; // $s0
		// 		int laneDist; // $s1
		// 		DRIVER2_STRAIGHT *str; // $s3
		/* end block 1.1 */
		// End offset: 0x00026B60
		// End Line: 1406

		/* begin block 1.2 */
			// Start line: 1411
			// Start offset: 0x00026B9C
			// Variables:
		// 		DRIVER2_CURVE *crv; // $s0
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

// [D] [T]
void InitNodeList(CAR_DATA* cp, EXTRA_CIV_DATA* extraData)
{
	int dx; // $s1
	int dz; // $s2
	int i;
	DRIVER2_CURVE* curve;
	DRIVER2_STRAIGHT* straight;
	int surfInd;

	CIV_ROUTE_ENTRY* cr;
	cr = cp->ai.c.targetRoute;

	for (i = 0; i < 13; i++)
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

	surfInd = cp->ai.c.currentRoad;

	if (IS_STRAIGHT_SURFACE(surfInd))
	{
		int theta; // $s0
		int laneDist; // $s1

		straight = GET_STRAIGHT(surfInd);

		dx = cp->hd.where.t[0] - straight->Midx;
		dz = cp->hd.where.t[2] - straight->Midz;

		theta = (straight->angle - ratan2(dx, dz) & 0xfffU);
		cr->distAlongSegment = (straight->length / 2) + FIXEDH(rcossin_tbl[theta * 2 + 1] * SquareRoot0(dx * dx + dz * dz));

		laneDist = ROAD_LANES_COUNT(straight) * 512 + FIXEDH(-dx * rcossin_tbl[(straight->angle & 0xfff) * 2 + 1] + dz * rcossin_tbl[(straight->angle & 0xfff) * 2]);
		cp->ai.c.currentLane = laneDist / 512;

		// calc all dirs
		if (ROAD_LANE_DIR(straight, cp->ai.c.currentLane) == 0)
			cr->dir = straight->angle;
		else
			cr->dir = straight->angle + 0x800U & 0xfff;
	}
	else if (IS_CURVED_SURFACE(surfInd))
	{
		if (extraData == NULL)
		{
			curve = GET_CURVE(surfInd);

			cr->distAlongSegment = (ratan2(cr->x - curve->Midx, cr->z - curve->Midz) & 0xfff) - curve->start;

			if (curve->inside < 10)
				cr->distAlongSegment &= 0xf80;
			else if (curve->inside < 20)
				cr->distAlongSegment &= 0xfc0;
			else
				cr->distAlongSegment &= 0xfe0;

			if (ROAD_LANE_DIR(curve, cp->ai.c.currentLane) == 0)
				cr->dir = (cr->distAlongSegment + curve->start) + 1024;
			else
				cr->dir = (cr->distAlongSegment + curve->start) - 1024;
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
// int /*$ra*/ GetNodePos(DRIVER2_STRAIGHT *straight /*$t1*/, DRIVER2_JUNCTION *junction /*$a1*/, DRIVER2_CURVE *curve /*$t0*/, int distAlongPath /*$a3*/, CAR_DATA *cp /*stack 16*/, int *x /*stack 20*/, int *z /*stack 24*/, int laneNo /*stack 28*/)
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



// [D] [T]
int GetNodePos(DRIVER2_STRAIGHT* straight, DRIVER2_JUNCTION* junction, DRIVER2_CURVE* curve, int distAlongPath, CAR_DATA* cp, int* x, int* z, int laneNo)
{
	unsigned char oldLane;
	unsigned char changeLaneCount;
	int angle;
	int distFromCentre;
	int sideShift;
	int radius;

	if (cp)
	{
		oldLane = cp->ai.c.oldLane;
		changeLaneCount = cp->ai.c.changeLaneCount;
	}
	else
	{
		oldLane = 0;
		changeLaneCount = 0;
	}

	if (straight)
	{
		angle = straight->angle;
		distFromCentre = distAlongPath - (straight->length >> 1);

		if (angle < 2048)
		{
			if (laneNo <= oldLane)
				test42 = -changeLaneCount * 128;
			else
				test42 = changeLaneCount * 128;

			sideShift = (ROAD_LANES_COUNT(straight) * 512 - (laneNo * 512 + 256)) + test42;

			*x = straight->Midx + FIXEDH(distFromCentre * rcossin_tbl[(angle & 0xfffU) * 2]) +
				FIXEDH(sideShift * rcossin_tbl[(angle & 0xfffU) * 2 + 1]);

			*z = straight->Midz + FIXEDH(distFromCentre * rcossin_tbl[(angle & 0xfffU) * 2 + 1]) -
				FIXEDH(sideShift * rcossin_tbl[(angle & 0xfffU) * 2]);
		}
		else if (cp)
		{
			CIV_STATE_SET_CONFUSED(cp);
			return 0;
		}
	}
	else if (curve)
	{
		angle = distAlongPath + curve->start;

		if (oldLane < laneNo)
			test42 = -changeLaneCount * 128;
		else
			test42 = changeLaneCount * 128;

		radius = curve->inside * 1024 + laneNo * 512 + 256 + test42;

		*x = curve->Midx + FIXEDH(radius * rcossin_tbl[(angle & 0xfffU) * 2]);
		*z = curve->Midz + FIXEDH(radius * rcossin_tbl[(angle & 0xfffU) * 2 + 1]);
	}
	else if (junction)
	{
		// do nothing really
	}
	else if (cp)
	{
		CIV_STATE_SET_CONFUSED(cp);
		return 0;
	}

	if (cp && changeLaneCount > 0)
		cp->ai.c.changeLaneCount--;

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckChangeLanes(DRIVER2_STRAIGHT *straight /*$s4*/, DRIVER2_CURVE *curve /*$s6*/, int distAlongSegment /*$a2*/, CAR_DATA *cp /*$s3*/, int tryToPark /*stack 16*/)
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
	// 		CAR_DATA *cp1; // $s0
	// 		CIV_ROUTE_ENTRY tmpNode; // stack offset -120

		/* begin block 1.1 */
			// Start line: 1572
			// Start offset: 0x00027290
			// Variables:
		// 		VECTOR pos; // stack offset -104
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

// [D] [T]
int CheckChangeLanes(DRIVER2_STRAIGHT* straight, DRIVER2_CURVE* curve, int distAlongSegment, CAR_DATA* cp, int tryToPark)
{
	int oldLane;
	int currentLane;
	int newLane;
	int trials;
	CAR_COSMETICS* car_cos;
	int dx;
	int dz;
	uint theta;
	int length;
	CAR_DATA* lcp;

	int oldLaneDir;
	VECTOR pos;
	u_char canProceed;
	u_char turnRight;
	CDATA2D cd[2];

	canProceed = 0;
	oldLane = cp->ai.c.currentLane;
	currentLane = oldLane;

	if (cp->ai.c.ctrlState != 8 && cp->ai.c.changeLaneIndicateCount == 0)
	{
		int roadWidthInLanes;

		if (straight == NULL)
			roadWidthInLanes = ROAD_WIDTH_IN_LANES(curve);
		else
			roadWidthInLanes = ROAD_WIDTH_IN_LANES(straight);

		newLane = currentLane + (Random2((int)straight) >> 7 & 2U) + 0xff & 0xff;
		if (tryToPark != 0)
		{
			if (oldLane == 1)
				newLane = 0;
			else if (roadWidthInLanes - 2 == currentLane)
				newLane = roadWidthInLanes - 1;
		}

		for (trials = 0; trials < 2; trials++)
		{
			if (trials == 1)
				newLane = currentLane * 2 - newLane & 0xff;

			if (newLane == 0xff || roadWidthInLanes <= newLane)
				continue;

			//travelAlongRoad = (currentLane ^ 1) & 1;
			
			if (gCurrentMissionNumber == 33 && makeLimoPullOver)
			{
				// bypass checks
			}
			else if (tryToPark == 0)
			{
				int allowedToPark;
				int allowedToDrive;

				// collect the lanes.
				allowedToPark = straight && ROAD_IS_PARKING_ALLOWED_AT(straight, newLane) || curve && ROAD_IS_PARKING_ALLOWED_AT(curve, newLane);
				allowedToDrive = straight && ROAD_IS_AI_LANE(straight, newLane) || curve && ROAD_IS_AI_LANE(curve, newLane);

				if (!allowedToDrive || allowedToPark)
					continue;
			}
			else
			{
				int allowedToDrive;
				allowedToDrive = straight && ROAD_IS_AI_LANE(straight, newLane) || curve && ROAD_IS_AI_LANE(curve, newLane);

				if (!allowedToDrive)
					continue;
			}

			// don't allow to change lane which in wrong direction
			if (straight != NULL) 
			{
				oldLaneDir = ROAD_LANE_DIR(straight, oldLane);
				if (oldLaneDir != ROAD_LANE_DIR(straight, newLane))
					continue;
			}
			else if (curve != NULL) 
			{
				oldLaneDir = ROAD_LANE_DIR(curve, oldLane);
				if (oldLaneDir != ROAD_LANE_DIR(curve, newLane))
					continue;
			}

			if (cp->ai.c.ctrlNode == NULL && cp->ai.c.turnNode == -1) 
			{
				canProceed = true;
				turnRight = oldLaneDir == 0;

				if (currentLane < newLane)
					turnRight = !turnRight;

				if (turnRight)
					theta = cp->hd.direction + 1024;
				else
					theta = cp->hd.direction - 1024;

				cd[0].x.vx = cp->hd.oBox.location.vx + FIXEDH(rcossin_tbl[(theta & 0xfff) * 2] * 512);
				cd[0].x.vz = cp->hd.oBox.location.vz + FIXEDH(rcossin_tbl[(theta & 0xfff) * 2 + 1] * 512);
				cd[0].length[0] = cp->ap.carCos->colBox.vz + 93;
				cd[0].length[1] = cp->ap.carCos->colBox.vx;
				cd[0].theta = cp->hd.direction;

				lcp = &car_data[MAX_CARS-1];

				while (lcp >= car_data)
				{
					if (lcp != cp && lcp->controlType != CONTROL_TYPE_NONE)
					{
						car_cos = lcp->ap.carCos;

						cd[1].length[0] = car_cos->colBox.vz + 93;
						cd[1].length[1] = car_cos->colBox.vx;
						cd[1].x.vx = lcp->hd.oBox.location.vx;
						cd[1].x.vz = lcp->hd.oBox.location.vz;
						cd[1].theta = lcp->hd.direction;

						length = ((cd[0].length[0] + cd[1].length[0]) * 3) / 2;

						dx = cd[0].x.vx - cd[1].x.vx;
						dz = cd[0].x.vz - cd[1].x.vz;

						if (ABS(dx) < length && ABS(dz) < length) 
						{
							if (bcollided2d(cd, 1))
							{
								canProceed = false;
								break;
							}
						}
					}
					lcp--;
				}

				if (canProceed)
					break;
			}
		}

		if (canProceed)
		{
			cp->ai.c.changeLaneIndicateCount = 0xa1;
			cp->ai.c.oldLane = oldLane;
			cp->ai.c.changeLaneCount = 4;
			cp->ai.c.changeLane = turnRight;
			currentLane = newLane;
		}
	}

	return currentLane;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CreateNewNode(CAR_DATA *cp /*$s4*/)
	// line 1637, offset 0x00027530
	/* begin block 1 */
		// Start line: 1638
		// Start offset: 0x00027530
		// Variables:
	// 		int oldRoad; // $s1
	// 		int cr; // $a3
	// 		CIV_ROUTE_ENTRY *newNode; // $s6
	// 		CIV_ROUTE_ENTRY *oldNode; // $s3
	// 		DRIVER2_CURVE *curve; // $s0
	// 		DRIVER2_STRAIGHT *straight; // $s5
	// 		int turnAngle; // stack offset -56

		/* begin block 1.1 */
			// Start line: 1638
			// Start offset: 0x00027530
			// Variables:
		// 		CAR_DATA *cp; // $s4
		// 		CIV_ROUTE_ENTRY *currentNode; // $v1

			/* begin block 1.1.1 */
				// Start line: 1638
				// Start offset: 0x00027530
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $a0
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
		// 		CAR_DATA *cp; // $s4

			/* begin block 1.2.1 */
				// Start line: 1638
				// Start offset: 0x0002758C
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $a0
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
		// 		CAR_DATA *cp; // $s4

			/* begin block 1.3.1 */
				// Start line: 1638
				// Start offset: 0x000275A8
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $a0
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
		// 		CAR_DATA *cp; // $s4

			/* begin block 1.4.1 */
				// Start line: 1638
				// Start offset: 0x000275C4
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $a0
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
		// 		CAR_DATA *cp; // $s4
		// 		CIV_ROUTE_ENTRY *currentNode; // $s3

			/* begin block 1.5.1 */
				// Start line: 1653
				// Start offset: 0x000275F0
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
			// 		CAR_DATA *cp; // $s4

				/* begin block 1.6.1.1 */
					// Start line: 1638
					// Start offset: 0x000275F0
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
		// 		CAR_DATA *cp; // $s4
		// 		CIV_ROUTE_ENTRY *currentNode; // $s3

			/* begin block 1.7.1 */
				// Start line: 1659
				// Start offset: 0x00027634
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $s2
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
		// 		CIV_ROUTE_ENTRY tmpNode; // stack offset -72

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
			// 		CAR_DATA *playerCar; // $v0
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
				// 		CAR_DATA *cp; // $s4

					/* begin block 1.10.4.1.1 */
						// Start line: 1789
						// Start offset: 0x00027EBC
						// Variables:
					// 		CIV_ROUTE_ENTRY *retNode; // $a0
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
				// 		CAR_DATA *cp; // $s4

					/* begin block 1.10.4.2.1 */
						// Start line: 1800
						// Start offset: 0x00027F78
						// Variables:
					// 		CIV_ROUTE_ENTRY *retNode; // $a0
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
				// 		CAR_DATA *cp; // $s4
				// 		CIV_ROUTE_ENTRY *currentNode; // $s6

					/* begin block 1.10.5.1.1 */
						// Start line: 1638
						// Start offset: 0x0002800C
						// Variables:
					// 		CIV_ROUTE_ENTRY *retNode; // $v0
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

// [D] [T]
int CreateNewNode(CAR_DATA * cp)
{
	CIV_ROUTE_ENTRY* start;
	CIV_ROUTE_ENTRY* newNode;
	CIV_ROUTE_ENTRY* retNode;
	int oldRoad;
	int cr;
	DRIVER2_ROAD_INFO roadInfo;
	CIV_ROUTE_ENTRY tempNode;
	int turnAngle;
	int startDist;
	int travelDir;
	int segmentEnd;
	int cornerAngle;

	start = cp->ai.c.pnode;
	turnAngle = 0;

	// validate two next nodes
	if (IS_NODE_VALID(cp, GET_NEXT_NODE(cp, start)) &&
		IS_NODE_VALID(cp, GET_NEXT_NODE(cp, start + 1)))
	{
		do {
			newNode = retNode = GET_NEXT_NODE(cp, start);

			if (retNode->pathType == 127)
			{
				oldRoad = cp->ai.c.currentRoad;

				if (cp->id == makeNextNodeCtrlNode)
				{
					cp->ai.c.ctrlNode = newNode;
					makeNextNodeCtrlNode = -1;
				}

				// stop, dammmm
				if (!GetSurfaceRoadInfo(&roadInfo, oldRoad))
					break;

				if (ROAD_LANE_DIR(&roadInfo, cp->ai.c.currentLane) == 0)
					travelDir = 1;
				else
					travelDir = -1;
				
				if (roadInfo.straight)
				{
					segmentEnd = roadInfo.straight->length;

					newNode->distAlongSegment = start->distAlongSegment + travelDir * 1024;
					newNode->dir = start->dir;
				}
				else
				{
					int dist;

					segmentEnd = roadInfo.curve->end - roadInfo.curve->start & 0xfff;

					if (roadInfo.curve->inside < 10)
						dist = travelDir << 7;
					else if (roadInfo.curve->inside < 20)
						dist = travelDir << 6;
					else
						dist = travelDir << 5;

					newNode->distAlongSegment = start->distAlongSegment + dist;
					newNode->dir = newNode->distAlongSegment + roadInfo.curve->start + travelDir * 1024 & 0xfff;
				}

				// check travelling direction and position on segment
				// advance road if needed
				if ((travelDir > 0 && segmentEnd < newNode->distAlongSegment) ||
					(travelDir < 0 && newNode->distAlongSegment < 0))
				{
					if ((travelDir > 0 && segmentEnd <= start->distAlongSegment) ||
						(travelDir < 0 && start->distAlongSegment < 1))
					{
						cp->ai.c.currentRoad = GetNextRoadInfo(cp, 1, &turnAngle, &startDist, start);
						
						newNode->dir = start->dir + turnAngle & 0xfff;
						newNode->distAlongSegment = startDist;

						if (cp->ai.c.currentRoad == -1)
							break;
					}
					else
					{
						if (travelDir < 1)
							newNode->distAlongSegment = 0;
						else
							newNode->distAlongSegment = segmentEnd;
					}
				}

				cr = cp->ai.c.currentRoad;
				
				if (GetSurfaceRoadInfo(&roadInfo, cr))
				{
					// this node is unused
					tempNode.dir = newNode->dir;
					tempNode.pathType = newNode->pathType;
					tempNode.distAlongSegment = newNode->distAlongSegment;
					tempNode.x = newNode->x;
					tempNode.z = newNode->z;

					if (oldRoad != cr && turnAngle == 0)
					{
						if (ROAD_LANE_DIR(&roadInfo, cp->ai.c.currentLane) == 0)
							travelDir = 1;
						else
							travelDir = -1;
						
						if (roadInfo.curve)
						{
							int dist;

							if (roadInfo.curve->inside < 10)
								dist = travelDir << 7;
							else if (roadInfo.curve->inside < 20)
								dist = travelDir << 6;
							else
								dist = travelDir << 5;

							newNode->distAlongSegment = newNode->distAlongSegment + dist;
						}
						else
						{
							newNode->distAlongSegment = newNode->distAlongSegment + travelDir * 1024;
						}
					}

					// Caine's Cash limo can be stopped by player in police car
					if (gCurrentMissionNumber == 33 && cp->ap.model == 4)
					{
						int dx, dz;
						CAR_DATA* playerCar = &car_data[player[0].playerCarId];

						dx = playerCar->hd.where.t[0] - cp->hd.where.t[0];
						dz = playerCar->hd.where.t[1] - cp->hd.where.t[1];

						// check if siren is on and we near the car
						if (CarHasSiren(playerCar->ap.model) && player[0].horn.on &&
							dx * dx + dz * dz < 16000000)
						{
							makeLimoPullOver = 1;
						}
					}

					// try parking it
					if ((Random2(0) + cp->id * 32 & 0xf1) == 0xf1 || makeLimoPullOver != 0)
					{
						int tryToPark;
						int newLane;

						tryToPark = 0;

						if (numParkedCars < maxParkedCars)
							tryToPark = (Random2(0) & 2U) != 0;

						// apply our Caine's Cash logic
						if (gCurrentMissionNumber == 33 && cp->ap.model == 4 && limoId == cp->id) // [A] limoId was skipped, bringing it back.
						{
							tryToPark = (makeLimoPullOver != 0);
						}

						newLane = CheckChangeLanes(roadInfo.straight, roadInfo.curve, newNode->distAlongSegment, cp, tryToPark);

						// try change lanes or park
						if (newLane != cp->ai.c.currentLane)
						{
							cp->ai.c.currentLane = newLane;

							if (tryToPark)
							{
								if (makeLimoPullOver || cp->ai.c.ctrlState == 0 && ROAD_IS_PARKING_ALLOWED_AT(&roadInfo, newLane))
								{
									makeNextNodeCtrlNode = cp->id;

									cp->ai.c.ctrlState = 8;
									cp->ai.c.ctrlNode = newNode;
									cp->ai.c.changeLaneCount = 0;
								}
							}
						}
					}

					tempNode.dir = newNode->dir;
					tempNode.pathType = newNode->pathType;
					tempNode.distAlongSegment = newNode->distAlongSegment;
					tempNode.x = newNode->x;
					tempNode.z = newNode->z;

					GetNodePos(roadInfo.straight, NULL, roadInfo.curve, newNode->distAlongSegment, cp, &tempNode.x, &tempNode.z, cp->ai.c.currentLane);

					if (turnAngle == -1024)
					{
						int cornerAngle;
						int segLength;
						int tmp;
						int dx;
						int dz;

						dx = tempNode.x - start->x;
						dz = tempNode.z - start->z;

						segLength = (SquareRoot0(dx * dx + dz * dz) - (cp->hd.wheel_speed / 170));
						cornerAngle = ((ratan2(dx, dz) - start->dir) + 0x800U & 0xfff) - 2048;

						tmp = FIXEDH(segLength * rcossin_tbl[(cornerAngle & 0xfffU) * 2 + 1]);

						retNode = newNode;
						if (tmp > 0)
						{
							newNode->x = start->x + FIXEDH(tmp * rcossin_tbl[(start->dir & 0xfff) * 2]);

							newNode->z = start->z + FIXEDH(tmp * rcossin_tbl[(start->dir & 0xfff) * 2 + 1]);
							newNode->pathType = 1;
							newNode->dir = start->dir;

							retNode = GET_NEXT_NODE(cp, newNode);
						}

						tmp = FIXEDH(segLength * rcossin_tbl[(cornerAngle & 0xfffU) * 2]);

						newNode = retNode;
						if (tmp < 0)
						{
							retNode->x = tempNode.x + FIXEDH(tmp * rcossin_tbl[(tempNode.dir & 0xfff) * 2]);
							retNode->z = tempNode.z + FIXEDH(tmp * rcossin_tbl[(tempNode.dir & 0xfff) * 2 + 1]);
							retNode->pathType = 1;
							retNode->dir = tempNode.dir;

							newNode = GET_NEXT_NODE(cp, retNode);
						}
					}

					// push into empty node
					if (newNode->pathType == 127)
					{
						newNode->dir = tempNode.dir;
						newNode->pathType = tempNode.pathType;
						newNode->distAlongSegment = tempNode.distAlongSegment;
						newNode->x = tempNode.x;

						if (tempNode.x < 0)
							tempNode.x = -tempNode.x;

						newNode->z = tempNode.z;

						if (tempNode.x < 600000)
						{
							if (turnAngle != 0)
							{
								cp->ai.c.turnNode = GET_NODE_ID(cp, newNode);
								cp->ai.c.turnDir = (turnAngle == 1024);
							}

							newNode->pathType = 1;
							return 1;
						}
					}
				}
				
				break;
			}

			//if (newNode >= end) // [A] i don't think that's ever needed now, probably have done better macro than OG devs
			//	newNode = start - 12;

			start = newNode;

		} while (newNode != cp->ai.c.pnode);
	}

	CIV_STATE_SET_CONFUSED(cp);
	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ InitCivState(CAR_DATA *cp /*$s1*/, char *extraData /*$s2*/)
	// line 1843, offset 0x000280d8
	/* begin block 1 */
		// Start line: 1844
		// Start offset: 0x000280D8
		// Variables:
	// 		CIV_STATE *cs; // $s0
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

// [D] [T]
int InitCivState(CAR_DATA * cp, EXTRA_CIV_DATA * extraData)
{
	CIV_STATE* cs = &cp->ai.c;

	cp->controlType = CONTROL_TYPE_CIV_AI;

	if (extraData == NULL)
		cp->ai.c.thrustState = 0;
	else
		cp->ai.c.thrustState = extraData->thrustState;

	// not moving in that state
	if (cp->ai.c.thrustState == 3)
	{
		if (extraData == NULL)
			cp->ai.c.ctrlState = 0;
		else
			cp->ai.c.ctrlState = extraData->ctrlState;

		return 1;
	}

	if (extraData == NULL)
		cs->currentRoad = GetSurfaceIndex((VECTOR*)(cp->hd).where.t);
	else
		cs->currentRoad = extraData->surfInd;

	// init road and nodes
	if (cs->currentRoad > -1)
	{
		DRIVER2_ROAD_INFO roadInfo;

		cp->ai.c.currentNode = 0;
		cp->ai.c.pnode = NULL;
		cp->ai.c.ctrlNode = NULL;
		cp->ai.c.turnNode = -1;

		if(GetSurfaceRoadInfo(&roadInfo, cs->currentRoad))
		{
			cp->ai.c.maxSpeed = speedLimits[ROAD_SPEED_LIMIT(&roadInfo)];
			
			InitNodeList(cp, extraData);

			cp->ai.c.pnode = &cp->ai.c.targetRoute[0];
			cp->hd.where.t[0] = cp->ai.c.pnode->x;
			cp->hd.where.t[2] = cp->ai.c.pnode->z;

			return 1;
		}
	}

	CIV_STATE_SET_CONFUSED(cp);

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ PingOutCar(CAR_DATA *cp /*$s0*/)
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

// [D] [T]
int PingOutCar(CAR_DATA * cp)
{
	testNumPingedOut++;

	if (cp->controlType == CONTROL_TYPE_CIV_AI)
	{
		if (cp->controlFlags & CONTROL_FLAG_COP)
			numCopCars--;

		numCivCars--;

		if (cp->ai.c.thrustState == 3 && cp->ai.c.ctrlState == 5)
			numParkedCars--;
	}
	else if (PingOutCivsOnly != 0 && valid_region(cp->hd.where.t[0], cp->hd.where.t[2]))
	{
		return 0;
	}

	if (cp->inform)
		*cp->inform ^= 0x40000000;

	ClearMem((char*)cp, sizeof(CAR_DATA));

	cp->controlType = CONTROL_TYPE_NONE;

	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ PingOutAllSpecialCivCars()
	// line 2016, offset 0x000282e8
	/* begin block 1 */
		// Start line: 2018
		// Start offset: 0x000282E8
		// Variables:
	// 		CAR_DATA *lcp; // $s0

		/* begin block 1.1 */
			// Start line: 2017
			// Start offset: 0x00028348
			// Variables:
		// 		CAR_DATA *cp; // $s0
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

// [D] [T]
// used when secret car is requested
int PingOutAllSpecialCivCars(void)
{
	CAR_DATA* lcp;

	lcp = car_data;

	{
		if (lcp->controlType == CONTROL_TYPE_CIV_AI && MissionHeader->residentModels[lcp->ap.model] > 4)
			PingOutCar(lcp);

		lcp++;
	}
	while (lcp < &car_data[MAX_CARS])

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
	// 		CAR_DATA *lcp; // $s0

		/* begin block 1.1 */
			// Start line: 2029
			// Start offset: 0x0002844C
			// Variables:
		// 		CAR_DATA *cp; // $s0
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

// [D] [T]
// used by cutscenes
int PingOutAllCivCarsAndCopCars(void)
{
	CAR_DATA* cp;

	cp = car_data;

	do {

		if (cp->controlType == CONTROL_TYPE_CIV_AI || cp->controlType == CONTROL_TYPE_PURSUER_AI)
			PingOutCar(cp);

		cp++;
	} while (cp < &car_data[MAX_CARS]);

	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckPingOut(CAR_DATA *cp /*$s0*/)
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
		// 		CAR_DATA *cp; // $s0
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

// [D] [T]
// called by civ car.
// checks distance from player and removes car if too far
int CheckPingOut(CAR_DATA * cp)
{
	int dz;
	int dx;
	int dist;

	dx = player[0].spoolXZ->vx - cp->hd.where.t[0];
	dz = player[0].spoolXZ->vz - cp->hd.where.t[2];
	dist = dx * dx + dz * dz;

	if (dist > 24000 * 24000 && PingOutCar(cp))
		return 1;

	if (requestStationaryCivCar == 1 && distFurthestCivCarSq < dist)
	{
		furthestCivID = cp->id;
		distFurthestCivCarSq = dist;
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

// [D] [T]
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

// [D] [T]
int TrafficLightCycle(int exit)
{
	int timeCnt;

	timeCnt = CameraCnt - frameStart & 0x1ff;

	if (exit == 0 || exit == 2)
	{
		if (timeCnt < 256)
			return 1;

		timeCnt -= 256;
	}
	else if (timeCnt > 255)
		return 1;

	if (timeCnt < 150)
		return 3;
	else if (timeCnt > 199)
		return 1;

	return 2;
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

// [D] [T]
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

	// [A] clear out other values
	distFurthestCivCarSq = 0;
	furthestCivID = 0;
	makeLimoPullOver = 0;
	limoId = 0;
	playerNum = 0;
	roadSeg = 0;
	testNumPingedOut = 0;
	currentAngle = 0;
	closeEncounter = 3;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CreateCivCarWotDrivesABitThenStops(int direction /*$s5*/, LONGVECTOR* startPos /*$s2*/, LONGVECTOR* stopPos /*$a2*/, unsigned char internalModel /*$s4*/, int palette /*stack 16*/)
	// line 2176, offset 0x000286e0
	/* begin block 1 */
		// Start line: 2177
		// Start offset: 0x000286E0
		// Variables:
	// 		EXTRA_CIV_DATA civDat; // stack offset -56
	// 		CAR_DATA *newCar; // $s1
	// 		CIV_ROUTE_ENTRY *stopNode; // $a0
	// 		CIV_ROUTE_ENTRY *spareNode; // $a1

		/* begin block 1.1 */
			// Start line: 2177
			// Start offset: 0x000286E0

			/* begin block 1.1.1 */
				// Start line: 2177
				// Start offset: 0x000286E0
				// Variables:
			// 		char *slot; // $v1
			// 		CAR_DATA *carCnt; // $a0
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
const int DistanceTriggerCarMoves = 700; // 5000;

// [D] [T] [A]
int CreateCivCarWotDrivesABitThenStops(int direction, LONGVECTOR* startPos, LONGVECTOR* stopPos, unsigned char internalModel, int palette)
{
	unsigned char* slot;
	CAR_DATA* carCnt;
	CAR_DATA* pNewCar;
	CIV_ROUTE_ENTRY* stopNode; // $a0
	CIV_ROUTE_ENTRY* spareNode; // $a1

	EXTRA_CIV_DATA civDat;
	ClearMem((char*)&civDat, sizeof(civDat));

	carCnt = car_data;
	slot = reservedSlots;
	pNewCar = NULL;

	// find free slot
	do {
		if (carCnt->controlType == CONTROL_TYPE_NONE && *slot == 0)
		{
			pNewCar = carCnt;
			break;
		}

		carCnt++;
		slot++;
	} while (carCnt < &car_data[MAX_TRAFFIC_CARS]);

	if (pNewCar == NULL)
		return -1;

	civDat.thrustState = 3;
	civDat.ctrlState = 8;
	civDat.controlFlags = 0;
	civDat.palette = palette;
	civDat.angle = direction;

	InitCar(pNewCar, direction, startPos, 2, internalModel, 0, (char*)&civDat);

	pNewCar->ai.c.ctrlState = 8;
	pNewCar->ai.c.maxSpeed = EVENT_CAR_SPEED;

	pNewCar->st.n.linearVelocity[1] = 0;
	pNewCar->st.n.linearVelocity[0] = EVENT_CAR_SPEED * rcossin_tbl[(direction & 0xfffU) * 2];
	pNewCar->st.n.linearVelocity[2] = EVENT_CAR_SPEED * rcossin_tbl[(direction & 0xfffU) * 2 + 1];

	pNewCar->ai.c.velRatio = (EVENT_CAR_SPEED * ONE) / (DistanceTriggerCarMoves - pNewCar->ap.carCos->colBox.vz * 3);
	pNewCar->ai.c.targetRoute[0].x = (*startPos)[0];
	pNewCar->ai.c.targetRoute[0].z = (*startPos)[2];

	stopNode = &pNewCar->ai.c.targetRoute[1];
	pNewCar->ai.c.ctrlNode = stopNode;

	stopNode->pathType = 1;
	stopNode->dir = direction;
	stopNode->distAlongSegment = 0;

	stopNode->x = (*startPos)[0] + FIXEDH(DistanceTriggerCarMoves * rcossin_tbl[(direction & 0xfffU) * 2]);
	stopNode->z = (*startPos)[2] + FIXEDH(DistanceTriggerCarMoves * rcossin_tbl[(direction & 0xfffU) * 2 + 1]);

	spareNode = &pNewCar->ai.c.targetRoute[2];
	spareNode->pathType = 1;
	spareNode->dir = direction;
	spareNode->distAlongSegment = 0;

	spareNode->x = (*startPos)[0] + FIXEDH(DistanceTriggerCarMoves * rcossin_tbl[(direction & 0xfffU) * 2] * 3);
	spareNode->z = (*startPos)[2] + FIXEDH(DistanceTriggerCarMoves * rcossin_tbl[(direction & 0xfffU) * 2 + 1] * 3);

	numCivCars++;

	return pNewCar->id;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CreateStationaryCivCar(int direction /*$t4*/, long orientX /*$s2*/, long orientZ /*$s1*/, LONGVECTOR* startPos /*$a2*/, int externalModel /*stack 16*/, int palette /*stack 20*/, int controlFlags /*stack 24*/)
	// line 2248, offset 0x00028960
	/* begin block 1 */
		// Start line: 2249
		// Start offset: 0x00028960
		// Variables:
	// 		EXTRA_CIV_DATA civDat; // stack offset -72
	// 		CAR_DATA *newCar; // $s0
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
			// 		CAR_DATA *carCnt; // $a0
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

// [D] [T]
int CreateStationaryCivCar(int direction, long orientX, long orientZ, LONGVECTOR* startPos, int externalModel, int palette, int controlFlags)
{
	unsigned char* slot;
	CAR_DATA* newCar;
	CAR_DATA* carCnt;
	int model;
	EXTRA_CIV_DATA civDat;
	long tmpQ[4];

	model = -1;
	
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

	if (model != -1)
	{
		if (externalModel > 4 && specModelValid == 0)
		{
			return -1;
		}

		// pick free slot
		newCar = NULL;
		carCnt = car_data;
		slot = reservedSlots;

		if (true)
		{
			do {
				if (carCnt->controlType == CONTROL_TYPE_NONE && *slot == 0)
				{
					newCar = carCnt;
					break;
				}

				carCnt++;
				slot++;
			} while (carCnt < &car_data[MAX_TRAFFIC_CARS]);
		}

		if (newCar)
		{
			int dx, dz;
			
			civDat.thrustState = 3;
			civDat.ctrlState = 7;

			if (controlFlags & CONTROL_FLAG_COP)
			{
				requestCopCar = 0;
				numCopCars++;
				cop_respawn_timer = gCopRespawnTime;
			}

			civDat.controlFlags = controlFlags | CONTROL_FLAG_WAS_PARKED;

			if (gCurrentMissionNumber != 32 && externalModel == 0)
				civDat.controlFlags |= CONTROL_FLAG_COP_SLEEPING;

			civDat.palette = palette;
			civDat.angle = direction;

			InitCar(newCar, direction, startPos, 2, model, 0, (char*)&civDat);
			
			dx = rcossin_tbl[((orientZ / 2) & 0xfff) * 2];
			dz = rcossin_tbl[((orientZ / 2) & 0xfff) * 2 + 1];

			tmpQ[0] = FIXEDH(newCar->st.n.orientation[1] * dx + newCar->st.n.orientation[0] * dz);
			tmpQ[1] = FIXEDH(newCar->st.n.orientation[1] * dz - newCar->st.n.orientation[0] * dx);
			tmpQ[2] = FIXEDH(newCar->st.n.orientation[3] * dx + newCar->st.n.orientation[2] * dz);
			tmpQ[3] = FIXEDH(newCar->st.n.orientation[3] * dz - newCar->st.n.orientation[2] * dx);

			dx = rcossin_tbl[((orientX / 2) & 0xfff) * 2];
			dz = rcossin_tbl[((orientX / 2) & 0xfff) * 2 + 1];

			newCar->st.n.orientation[0] = FIXEDH(tmpQ[3] * dx + tmpQ[0] * dz);
			newCar->st.n.orientation[1] = FIXEDH(tmpQ[2] * dx + tmpQ[1] * dz);
			newCar->st.n.orientation[2] = FIXEDH(tmpQ[2] * dz - tmpQ[1] * dx);
			newCar->st.n.orientation[3] = FIXEDH(tmpQ[3] * dz - tmpQ[0] * dx);

			numCivCars++;

			return newCar->id;
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
	// 		EXTRA_CIV_DATA civDat; // stack offset -128
	// 		int dir; // stack offset -52
	// 		int distAlongSegment; // $fp
	// 		int lane; // $s7
	// 		CAR_DATA *newCar; // $s1
	// 		DRIVER2_STRAIGHT *str; // $s6
	// 		DRIVER2_CURVE *crv; // $s5
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
			// 		CAR_DATA *carCnt; // $a0
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
			// 		CAR_DATA *cp; // $s1
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
				// 		CAR_DATA *lcp; // $a1
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
				// 		CAR_DATA *lcp; // $a1
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

// [D] [T] [A] - some register is not properly decompiled
// TODO: store pings
int PingInCivCar(int minPingInDist)
{
	int model;
	CAR_DATA* carCnt;
	CAR_DATA* newCar;
	
	//DRIVER2_CURVE* curve;
	//DRIVER2_STRAIGHT* straight;

	DRIVER2_ROAD_INFO roadInfo;
	
	EXTRA_CIV_DATA civDat;
	unsigned char possibleLanes[12];
	// carDistLanes removed as it's unused
	long pos[4];
	int distSq;
	int dir;
	int curveLength;
	int tryPingInParkedCars;
	int count;
	int lbody;
	int lane;
	int i;
	u_char cookieCountStart;
	uint retDistSq;
	unsigned char* slot;

	//straight = NULL;
	//curve = NULL;
	
	civDat.distAlongSegment = -5;
	lane = -1;
	dir = 0xffffff;

	tryPingInParkedCars = 0;

	PingOutCivsOnly = 1;

#ifdef CUTSCENE_RECORDER
	extern int gCutsceneAsReplay;
	if (gCutsceneAsReplay != 0)
	{
		requestCopCar = 0;
		allowSpecSpooling = 0;
	}
#endif
	
	if (requestCopCar == 0 && numParkedCars < maxParkedCars && (gCurrentMissionNumber != 33 || numCivCars != 0))
	{
		tryPingInParkedCars = 1;
	}

	if (NumPlayers == 2)
		playerNum = CameraCnt & 1;
	else
		playerNum = 0;

	if (MissionHeader->type & 0x4)
	{
		PingOutCivsOnly = 1;
		return 0;
	}

	if (gInGameCutsceneActive != 0)
	{
		PingOutCivsOnly = 1;
		return 0;
	}

	if (maxCivCars - 1 <= numCivCars && gInGameChaseActive == 0)
	{
		PingOutCivsOnly = 1;
		return 0;
	}

	/*if (NumPlayers > 1)		// [A] allow pinging in cars in multiplayer game such as Cops and Robbers
	{
		PingOutCivsOnly = 1;
		return 0;
	}*/

	newCar = NULL;

	ClearMem((char*)&civDat, sizeof(civDat));

	baseLoc.vx = player[playerNum].spoolXZ->vx;
	baseLoc.vz = player[playerNum].spoolXZ->vz;

	// allow to use ping buffer sometimes
	if (IsPingInfoAvailable())
	{
		// rely on pings provided by cutscenes/chases
		int angle;
		int dx, dz;
		int newCarId;
		newCarId = GetPingInfo(&cookieCount);

		if (newCarId == -1)
			return 0;

		//if (newCarId > MAX_CARS - 1)
		//	return 0;

		newCar = &car_data[newCarId];

		// ping out old car
		if (newCar->controlType != CONTROL_TYPE_NONE)
		{
			if (PingOutCar(newCar) == 0)
				return 0;
		}

		if (requestCopCar == 0)
		{
			angle = (cookieCount * ONE) / 44 & 0xfff;
			dx = rcossin_tbl[(angle & 0xfff) * 2] << 3;
			dz = rcossin_tbl[(angle & 0xfff) * 2 + 1] << 3;
		}
		else
		{
			angle = (cookieCount * ONE) / 56 & 0xfff;
			dx = rcossin_tbl[(angle & 0xfff) * 2] * 10;
			dz = rcossin_tbl[(angle & 0xfff) * 2 + 1] * 10;
		}

		randomLoc.vx = baseLoc.vx + FIXEDH(dx) * 2048;
		randomLoc.vz = baseLoc.vz + FIXEDH(dz) * 2048;

		roadSeg = RoadInCell(&randomLoc);
	}
	else
	{
		// randomized pings
		int angle;
		int dx, dz;
		
		const int maxCookies = requestCopCar ? 55 : 43;

		if (requestCopCar == 0 && cookieCount > 43)
			cookieCount -= 25;

		cookieCountStart = cookieCount;

		// find a free slot
		carCnt = car_data;
		slot = reservedSlots;

		do {
			if (carCnt->controlType == CONTROL_TYPE_NONE && *slot == 0)
			{
				newCar = carCnt;
				break;
			}

			carCnt++;
			slot++;
		} while (carCnt < &car_data[MAX_TRAFFIC_CARS]);

		if (newCar == NULL)
		{
			PingOutCivsOnly = 1;
			return 0;
		}

		do {
			if (cookieCount < maxCookies)
				cookieCount++;
			else
				cookieCount = 0;

			if (cookieCount == cookieCountStart)
			{
				break;
			}

			if (requestCopCar == 0)
			{
				angle = (cookieCount * ONE) / 44 & 0xfff;
				dx = rcossin_tbl[(angle & 0xfff) * 2] << 3;
				dz = rcossin_tbl[(angle & 0xfff) * 2 + 1] << 3;
			}
			else
			{
				angle = (cookieCount * ONE) / 56 & 0xfff;
				dx = rcossin_tbl[(angle & 0xfff) * 2] * 10;
				dz = rcossin_tbl[(angle & 0xfff) * 2 + 1] * 10;
			}

			randomLoc.vx = baseLoc.vx + FIXEDH(dx) * 2048;
			randomLoc.vz = baseLoc.vz + FIXEDH(dz) * 2048;

			roadSeg = RoadInCell(&randomLoc);

		} while (!IS_STRAIGHT_SURFACE(roadSeg) && !IS_CURVED_SURFACE(roadSeg));
	}
	
	// wtf there were before? car wasn't set to 'confused' state
	if (!GetSurfaceRoadInfo(&roadInfo, roadSeg))
	{
		civPingTest.OffRoad++;
		//CIV_STATE_SET_CONFUSED(newCar);
		return 0;
	}

	{
		volatile int numPossibleLanes;
		volatile int numLanes;
		volatile int allowedToPark;
		
		if (ROAD_LANES_COUNT(&roadInfo) == 0) // BAD ROAD
		{
			//CIV_STATE_SET_CONFUSED(newCar);
			return 0;
		}

		numLanes = ROAD_WIDTH_IN_LANES(&roadInfo);

		numPossibleLanes = 0;

		// Caine's Cash limo spawned always on lane 1. Don't allow it parked!
		if (gCurrentMissionNumber == 33 && minPingInDist == 666)
		{
			lane = 1;
		}
		else
		{
			i = 0;
			while (i < numLanes)
			{
				// collect the lanes.
				allowedToPark = ROAD_IS_PARKING_ALLOWED_AT(&roadInfo, i);

				// this is closest to OG decompiled. Works different!
				//if ((
				//	((tryPingInParkedCars && allowedToPark))) ||
				//	((ROAD_IS_AI_LANE(straight, i) && (((i != 0 || ((straight->NumLanes & 0x40U) == 0)) && (((straight->NumLanes & 0xffffff0f) * 2 - 1 != i || ((straight->NumLanes & 0x80U) == 0))))))))

				// pick only non-parkable driveable lanes if parked cars not requested
				if (tryPingInParkedCars && allowedToPark || ROAD_IS_AI_LANE(&roadInfo, i) && !allowedToPark)
					possibleLanes[numPossibleLanes++] = i;

				i++;
			}

			if (numPossibleLanes == 0)
				return 0;

			lane = possibleLanes[(Random2(0) >> 8) % numPossibleLanes];
		}

		// check if need to make a parked car
		if (ROAD_IS_PARKING_ALLOWED_AT(&roadInfo, lane))
		{
			civDat.thrustState = 3;
			civDat.ctrlState = 7;

			// set to drive off
			if (ROAD_IS_AI_LANE(&roadInfo, lane))
				civDat.ctrlState = 5;
		}
		else
		{
			// Car is not active. Permanently parked
			if (ROAD_IS_AI_LANE(&roadInfo, lane) == 0)
			{
				civPingTest.NotDrivable++;
				return 0;
			}

			civDat.thrustState = 0;
			civDat.ctrlState = 0;
		}
	}

	// [A] what's model is this?
	if (gInGameCutsceneActive == 0 && gInGameChaseActive == 0 && (Random2(0) & 0x40) == 0)
	{
		modelRandomList[12] = 3;
	}

	// seems like this mission check (Get a cop car) is a bug fix
	// choose to spawn parked cops
	if (gCurrentMissionNumber == 32 || civDat.thrustState != 3)
	{
		modelRandomList[12] = 0;
	}

	// check if special car is loaded and add it to random list
	if (specModelValid == 0 || allowSpecSpooling == 0 || MissionHeader->residentModels[4] == 12)
	{
		modelRandomList[15] = 0;
		modelRandomList[14] = 1;
	}
	else
	{
		modelRandomList[15] = 4;
		modelRandomList[14] = 1;

		if ((Random2(0) & 0x100) != 0)
			modelRandomList[14] = 4;
	}

	// another change for Caine's compound
	if (gCurrentMissionNumber == 7 || gCurrentMissionNumber == 33)
	{
		modelRandomList[9] = 0;
		modelRandomList[8] = 0;
		modelRandomList[11] = 1;
		modelRandomList[10] = 1;
	}
	else
	{
		modelRandomList[11] = 2;
		modelRandomList[10] = 2;
		modelRandomList[9] = 2;
		modelRandomList[8] = 2;
	}

	civDat.controlFlags = 0;

	if (requestCopCar)
	{
		model = 3;
		civDat.controlFlags = CONTROL_FLAG_COP;
	}
	else
	{
		model = modelRandomList[Random2(0) & 0xf];
	}

	// force spawn limo nearby in Caine's Cash
	if (gCurrentMissionNumber == 33 && minPingInDist == 666)
		model = 4;

	// select car color palette
	if (MissionHeader->residentModels[model] == 0 || MissionHeader->residentModels[model] > 4)
	{
		civDat.palette = 0;
	}
	else if (player[0].playerType == 1 && car_data[player[0].playerCarId].ap.model == model)
	{
		civDat.palette = Random2(0) % 5; // [A] was % 4; use previously unused palette slot

		// if player got the same color we better select other
		if (car_data[player[0].playerCarId].ap.palette <= civDat.palette)
			civDat.palette++;
	}
	else
	{
		civDat.palette = Random2(0) % 6; // [A] was % 5; use previously unused palette slot
	}

	lbody = car_cosmetics[model].colBox.vz;

	// check bounds
	if (IS_STRAIGHT_SURFACE(roadSeg))
	{
		int theta;
		int minDistAlong;
		int scDist;

		if (requestCopCar == 0)
		{
			scDist = lbody * 2;
			minDistAlong = lbody * 3;
		}
		else
		{
			scDist = lbody / 2;
			minDistAlong = 0;
		}

		if (roadInfo.straight->length <= (scDist + lbody) * 2) // don't spawn outside straight
			return 0;

		dx = randomLoc.vx - roadInfo.straight->Midx;
		dz = randomLoc.vz - roadInfo.straight->Midz;

		theta = (roadInfo.straight->angle - ratan2(dx, dz) & 0xfffU);

		civDat.distAlongSegment = (roadInfo.straight->length / 2) + FIXEDH(rcossin_tbl[theta * 2 + 1] * SquareRoot0(dx * dx + dz * dz));

		if (requestCopCar == 0)
		{
			if (civDat.distAlongSegment < minDistAlong)
				civDat.distAlongSegment = minDistAlong;

			if (roadInfo.straight->length - civDat.distAlongSegment < minDistAlong)
				civDat.distAlongSegment = roadInfo.straight->length - minDistAlong;
		}

		if (ROAD_LANE_DIR(roadInfo.straight, lane) == 0)
			dir = roadInfo.straight->angle;
		else
			dir = roadInfo.straight->angle + 0x800U & 0xfff;
	}
	else if (IS_CURVED_SURFACE(roadSeg))
	{
		int minDistAlong;
		int segmentLen;

		currentAngle = ratan2(randomLoc.vx - roadInfo.curve->Midx, randomLoc.vz - roadInfo.curve->Midz);
		minDistAlong = 0;

		if (requestCopCar == 0)
		{
			if (roadInfo.curve->inside < 10)
				minDistAlong = 128;
			else if (roadInfo.curve->inside < 20)
				minDistAlong = 64;
			else
				minDistAlong = 32;
		}

		segmentLen = (roadInfo.curve->end - roadInfo.curve->start) - minDistAlong & 0xfff;

		if (roadInfo.curve->inside < 10)
			civDat.distAlongSegment = (currentAngle & 0xfffU) - roadInfo.curve->start & 0xf80;
		else if (roadInfo.curve->inside < 20)
			civDat.distAlongSegment = (currentAngle & 0xfffU) - roadInfo.curve->start & 0xfc0;
		else
			civDat.distAlongSegment = (currentAngle & 0xfffU) - roadInfo.curve->start & 0xfe0;
		
		if (civDat.distAlongSegment <= minDistAlong)
			civDat.distAlongSegment = minDistAlong;

		if (civDat.distAlongSegment >= segmentLen)
			civDat.distAlongSegment = segmentLen;

		if (ROAD_LANE_DIR(roadInfo.curve, lane) == 0)
			dir = civDat.distAlongSegment + roadInfo.curve->start + 0x400;
		else
			dir = civDat.distAlongSegment + roadInfo.curve->start - 0x400;

		curveLength = ((roadInfo.curve->end - roadInfo.curve->start & 0xfffU) * roadInfo.curve->inside * 11) / 7;

		if (lbody * 6 > curveLength) // don't spawn outside curve
			return 0;
	}

	// too much parked cars?
	if (civDat.thrustState == 3 && civDat.ctrlState == 5 && numParkedCars >= maxParkedCars)
	{
		return 0;
	}

	if (dir == 0xffffff || lane < 0 || civDat.distAlongSegment < 0)
	{
		//CIV_STATE_SET_CONFUSED(newCar);
		return 0;
	}

	GetNodePos(roadInfo.straight, NULL, roadInfo.curve, civDat.distAlongSegment, newCar, &newCar->ai.c.targetRoute[0].x, &newCar->ai.c.targetRoute[0].z, lane);

	retDistSq = 0x7fffffff; // INT_MAX
	pos[0] = newCar->ai.c.targetRoute[0].x;
	pos[2] = newCar->ai.c.targetRoute[0].z;
	pos[1] = randomLoc.vy;

	count = 0;

	carCnt = car_data;
	while (carCnt < &car_data[MAX_CARS])
	{
		if (carCnt->controlType != CONTROL_TYPE_NONE)
		{
			int dx, dy, dz;
			int sqDist;

			dy = randomLoc.vy - carCnt->hd.where.t[1];
			dy = ABS(dy);

			if (dy < 800)
			{
				dx = pos[0] - carCnt->hd.where.t[0];
				dz = pos[2] - carCnt->hd.where.t[2];

				sqDist = (dx * dx + dz * dz);

				if (ABS(dx) < 0x1000 && ABS(dz) < 0x1000 && sqDist < retDistSq)
				{
					retDistSq = sqDist;
				}

				// check if this car's route is too close to others
				if (ABS(dx) < 0x7000 && ABS(dz) < 0x7000 && sqDist < 9000000)
				{
					count++;

					if (count > closeEncounter)
						return 0;
				}
			}
		}
		carCnt++;
	}

	//if (retDistSq != 56)	// [A] This was decompiled wrong. Can't get the meaning for it
		distSq = retDistSq;

	if (distSq < (lbody * lbody * 8 * 8))
		return 0;

	civDat.surfInd = roadSeg;

	if (roadSeg < 0)
	{
		//CIV_STATE_SET_CONFUSED(newCar); // [A] not needed really before InitCar happens
		return 0;
	}

	
	civDat.angle = dir;
	InitCar(newCar, dir, &pos, 2, model, 0, (char*)&civDat);

	// set the lane
	newCar->ai.c.currentLane = lane;

	if (gCurrentMissionNumber == 33 && minPingInDist == 666)
		limoId = newCar->id;

	if (newCar->ai.c.ctrlState == 5)
	{
		numParkedCars++;

		// parked car is going to unpark
		if (newCar->ai.c.thrustState == 3)
			newCar->controlFlags |= CONTROL_FLAG_WAS_PARKED;
	}

	// cop car request done
	if (newCar->controlFlags & CONTROL_FLAG_COP)
	{
		requestCopCar = 0;
		numCopCars++;
	}

	numCivCars++;

	// init Cop
	if (newCar->controlFlags & CONTROL_FLAG_COP)
		PassiveCopTasks(newCar);

	PingOutCivsOnly = 0;

	// [A] REDRIVER2 always stores pings
	StorePingInfo(cookieCount, newCar->id);

	return newCar->id + 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AttemptUnPark(CAR_DATA *cp /*$s1*/)
	// line 2659, offset 0x0002a4c4
	/* begin block 1 */
		// Start line: 2660
		// Start offset: 0x0002A4C4
		// Variables:
	// 		DRIVER2_STRAIGHT *str; // $s2
	// 		DRIVER2_CURVE *crv; // $s3
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

// [D] [T]
void AttemptUnPark(CAR_DATA * cp)
{
	unsigned char oldLane;
	DRIVER2_ROAD_INFO roadInfo;

	InitCivState(cp, NULL);

	oldLane = cp->ai.c.currentLane;
	
	if(GetSurfaceRoadInfo(&roadInfo, cp->ai.c.currentRoad))
	{
		cp->ai.c.currentLane = CheckChangeLanes(roadInfo.straight, roadInfo.curve, cp->ai.c.targetRoute[0].distAlongSegment, cp, 0);

		if (oldLane == cp->ai.c.currentLane || ROAD_IS_AI_LANE(&roadInfo, cp->ai.c.currentLane) == 0)
		{
			// shut off. Unknown intention
			CIV_STATE_SET_CONFUSED(cp);
		}
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivControl(CAR_DATA *cp /*$s0*/)
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

// [D] [T]
int CivControl(CAR_DATA * cp)
{
	CheckPingOut(cp);

	if (cp->controlType == CONTROL_TYPE_CIV_AI)
	{
		if (cp->ai.c.changeLaneIndicateCount != 0)
			cp->ai.c.changeLaneIndicateCount--;

		if (cp->ai.c.ctrlState == 5 && cp->ai.c.thrustState == 3 &&
			cp->totalDamage < 4 && (cp->ap.model != 3 && (Random2(0) + (25 - cp->id) * 16 & 0xff8) == 0xf00))
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

			extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
			extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

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
				DRIVER2_STRAIGHT* straight = GET_STRAIGHT(cp->ai.c.currentRoad);

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
			}*/

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

					pn = GET_NEXT_NODE(cp, pn);
				}
			}

			// current node - YELLOW
			if (cp->ai.c.currentNode > -1 && cp->ai.c.currentNode < 13)
			{
				CIV_ROUTE_ENTRY& currentNode = cp->ai.c.targetRoute[cp->ai.c.currentNode];

				VECTOR b1p = { currentNode.x, cp->hd.where.t[1], currentNode.z };

				Debug_AddLineOfs(_zero, _up1, b1p, yycv);
			}

			// turn node - RED
			if (cp->ai.c.turnNode > -1 && cp->ai.c.turnNode < 13)
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

	// watch for the player
	if (cp->controlFlags & CONTROL_FLAG_COP)
		PassiveCopTasks(cp);

	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivAccelTrafficRules(CAR_DATA *cp /*$t3*/, int *distToNode /*$a1*/)
	// line 2798, offset 0x0002a5fc
	/* begin block 1 */
		// Start line: 2799
		// Start offset: 0x0002A5FC
		// Variables:
	// 		int lbody; // $t1
	// 		int wbody; // $t2
	// 		CIV_STATE *cs; // $a2

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
			// 		CAR_DATA *cp; // $t3

				/* begin block 1.3.1.1 */
					// Start line: 2932
					// Start offset: 0x0002AA0C
					// Variables:
				// 		CAR_DATA *lcp; // $a3
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
			// 		CAR_DATA *cp; // $t3

				/* begin block 1.3.2.1 */
					// Start line: 2799
					// Start offset: 0x0002AB44
					// Variables:
				// 		CIV_STATE *cs; // $v1
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
const int newAccel = 2000;

// [D] [T]
int CivAccelTrafficRules(CAR_DATA * cp, int* distToNode)
{
	CAR_COSMETICS* car_cos;
	CAR_DATA* lcp;
	int tangent;
	int normal;
	int lbody;
	int wbody;

	car_cos = cp->ap.carCos;
	lbody = car_cos->colBox.vz;
	wbody = car_cos->colBox.vx;

	if (cp->id == 1 && (cp->ai.c.carMustDie == 1))
	{
		cp->ai.c.thrustState = 3;
		cp->ai.c.ctrlState = 9;
		cp->ai.c.carMustDie = 0;
	}

	switch (cp->ai.c.thrustState)
	{
	case 0:
	{
		cp->ai.c.brakeLight = 0;

		if (cp->ai.c.ctrlNode)
		{
			int properVel;
			int brakeDist;

			if (!IS_NODE_VALID(cp, cp->ai.c.ctrlNode))
			{
				CIV_STATE_SET_CONFUSED(cp);
				return 0;
			}

			properVel = cp->hd.wheel_speed;
			brakeDist = (properVel * FIXEDH(properVel)) / (newAccel * 2);

			if (ABS(brakeDist) > * distToNode)
			{
				properVel -= 120000;
				brakeDist = *distToNode - lbody * 3;

				if (brakeDist < 0)
				{
					if (lbody * 3 - *distToNode > 2)
					{
						properVel /= *distToNode - lbody * 3;
					}
				}
				else if (brakeDist > 2)
				{
					properVel /= *distToNode - lbody * 3;
				}

				cp->ai.c.velRatio = properVel;
				cp->ai.c.thrustState = 1;
			}
		}

		if (FIXEDH(cp->hd.wheel_speed) > cp->ai.c.maxSpeed)
			return newAccel >> 2;

		return newAccel;
	}
	case 1:
	{
		int properVel;
		int distToEnd;
		int accelRatio;

		if (cp->ai.c.ctrlState == 5 || cp->ai.c.ctrlState == 8)
			distToEnd = 100;
		else
			distToEnd = lbody * 3;

		cp->ai.c.brakeLight = 1;

		if (cp->ai.c.ctrlNode != NULL && cp->ai.c.ctrlNode->pathType != 127)
		{
			if (cp->ai.c.ctrlState == 1 && junctionLightsPhase[cp->ai.c.trafficLightPhaseId] == 3)
			{
				cp->ai.c.thrustState = 0;
				cp->ai.c.ctrlNode = NULL;

				return newAccel;
			}

			if (*distToNode < distToEnd)
			{
				if (cp->ai.c.ctrlState == 6)
				{
					cp->ai.c.thrustState = 0;
					cp->ai.c.ctrlNode = NULL;

					return newAccel;
				}

				accelRatio = (-cp->hd.wheel_speed) / 4;

				cp->ai.c.thrustState = 3;
			}
			else
			{
				if (cp->ai.c.ctrlState == 6)
				{
					properVel = (*distToNode - distToEnd) * cp->ai.c.velRatio + 70000;
				}
				else if (distToEnd < *distToNode)
				{
					properVel = cp->ai.c.velRatio * ((*distToNode - distToEnd) + 100);
				}
				else
				{
					properVel = 0;
				}

				accelRatio = ((properVel - cp->hd.wheel_speed) * newAccel) / 15;
			}

			if (IS_NODE_VALID(cp, cp->ai.c.ctrlNode))	// [A] Weird.
			{
				if (accelRatio <= newAccel)
				{
					if (accelRatio < newAccel * -2)
						return newAccel * -2;
					else
						return accelRatio;
				}

				return newAccel;
			}
		}

		CIV_STATE_SET_CONFUSED(cp);
		return 0;
	}
	case 3:
	{
		break;
	}
	case 5:
	case 6:
	{
		int distToObstacle;
		int checkObstDist;
		int carDir;
		int dx, dz;

		cp->ai.c.brakeLight = 1;

		if (cp->ai.c.ctrlState == 4)
			checkObstDist = 2048;
		else
			checkObstDist = 512;

		carDir = cp->hd.direction & 0xfff;
		distToObstacle = 0x7fffff;

		lcp = &car_data[MAX_CARS-1];
		while (lcp >= car_data)
		{
			if (lcp->ai.c.thrustState != 3 && lcp != cp && lcp->controlType != CONTROL_TYPE_NONE)
			{
				dx = lcp->hd.where.t[0] - cp->hd.where.t[0];
				dz = lcp->hd.where.t[2] - cp->hd.where.t[2];

				tangent = FIXEDH(dx * rcossin_tbl[carDir * 2] + dz * rcossin_tbl[carDir * 2 + 1]);
				normal = FIXEDH(dx * rcossin_tbl[carDir * 2 + 1] - dz * rcossin_tbl[carDir * 2]);

				if (tangent > 0)
				{
					if (ABS(normal) < wbody * sideMul * 6 && tangent < distToObstacle)
					{
						distToObstacle = tangent;
					}
				}
			}
			lcp--;
		}

		if (distToObstacle <= checkObstDist)
		{
			int speed;
			speed = (-cp->hd.wheel_speed) / 4; // is that a brake dist?

			if (speed <= newAccel)
			{
				if (speed < newAccel * -2)
					return newAccel * -2;
				else
					return speed;
			}

			return newAccel;
		}

		cp->ai.c.ctrlState = 0;
		cp->ai.c.thrustState = 0;
		cp->ai.c.ctrlNode = 0;

		return newAccel;
	}
	default:
	{
		CIV_STATE_SET_CONFUSED(cp);
		return 0;
	}
	}

	// switch lights
	switch (cp->ai.c.ctrlState)
	{
	case 1:
		if (junctionLightsPhase[cp->ai.c.trafficLightPhaseId] == 3)
			cp->ai.c.thrustState = 0;
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
		break;
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
	// 		SVECTOR boxDisp; // stack offset -72
	// 		int carLength[2]; // stack offset -64
	// 		CAR_DATA *cp0; // $s5
	// 		CAR_DATA *cp1; // $s2
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
				// 		CAR_DATA *cp; // $s0

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

int brakeLength[MAX_CARS];

int CAR_PAUSE_START = 100;
static CAR_DATA(*horncarflag[2]) = { 0 };
static unsigned char hornchanflag[2] = { 0 };

// [D] [T]
void SetUpCivCollFlags(void)
{
	CAR_DATA** pp_Var9;
	CAR_COSMETICS* car_cos;
	CAR_DATA* cp1;
	SVECTOR boxDisp;
	CAR_DATA* cp0;
	int carLength[2];
	int i;
	int brake;
	int dx;
	int extraLength;

	CDATA2D cd[2];

	ClearMem((char*)brakeLength, sizeof(brakeLength));

	cp0 = &car_data[MAX_CARS - 1];

	while (cp0 >= car_data)
	{
		if (cp0->controlType == CONTROL_TYPE_CIV_AI)
		{
			extraLength = FIXEDH(cp0->hd.wheel_speed);

			if (cp0->wheel_angle < 61)
				extraLength *= 13;
			else
				extraLength *= 4;

			extraLength = ABS(extraLength);

			car_cos = cp0->ap.carCos;
			carLength[0] = car_cos->colBox.vz;

			cd[0].length[0] = carLength[0] + 93 + extraLength;
			cd[0].length[1] = car_cos->colBox.vx;
			cd[0].theta = cp0->hd.direction;

			gte_SetRotMatrix(&cp0->hd.where.m);
			gte_SetTransMatrix(&cp0->hd.where.m);

			boxDisp.vx = -car_cos->cog.vx;
			boxDisp.vy = -car_cos->cog.vy;
			boxDisp.vz = (extraLength - car_cos->cog.vz) + 93;

			gte_ldv0(&boxDisp);
			gte_rtv0tr();
			gte_stlvnl(&cd[0].x);

			cp1 = &car_data[MAX_CARS];

			while (cp1 >= car_data)
			{
				if (cp1->controlType != CONTROL_TYPE_NONE && cp1 != cp0)
				{
					car_cos = cp1->ap.carCos;

					if (CAR_INDEX(cp1) == TANNER_COLLIDER_CARID)
					{
						if (player[0].playerType != 2)
						{
							cp1--;
							continue;
						}

						cd[1].length[0] = 60;
						cd[1].length[1] = 60;
						cd[1].x.vx = player[0].pos[0];
						cd[1].x.vz = player[0].pos[2];
						cd[1].theta = player[0].dir;
					}
					else
					{
						cd[1].length[0] = car_cos->colBox.vz;
						cd[1].length[1] = car_cos->colBox.vx;
						cd[1].x.vx = cp1->hd.oBox.location.vx;
						cd[1].x.vy = cp1->hd.oBox.location.vy;
						cd[1].x.vz = cp1->hd.oBox.location.vz;
						cd[1].theta = cp1->hd.direction;
					}

					dx = ((cd[0].length[0] + cd[1].length[0]) * 3) / 2;

					if (cd[0].x.vx - cd[1].x.vx < 0)
					{
						if (cd[1].x.vx - cd[0].x.vx >= dx)
						{
							cp1--;
							continue;
						}

					}
					else if (dx <= cd[0].x.vx - cd[1].x.vx)
					{
						cp1--;
						continue;
					}

					if (cd[0].x.vz - cd[1].x.vz < 0)
					{
						if (cd[1].x.vz - cd[0].x.vz >= dx)
						{
							cp1--;
							continue;
						}
					}
					else if (dx <= cd[0].x.vz - cd[1].x.vz)
					{
						cp1--;
						continue;
					}

					// check height difference
					if (CAR_INDEX(cp1) == CAMERA_COLLIDER_CARID)
					{
						if (ABS(player[0].pos[1] - cp0->hd.where.t[1]) >= 500)
						{
							cp1--;
							continue;
						}
					}
					else if (ABS(cp1->hd.where.t[1] - cp0->hd.where.t[1]) >= 500 && ABS(player[0].pos[1] - cp0->hd.where.t[1]) >= 500)
					{
						cp1--;
						continue;
					}

					// do overlap test between boxes
					if (bcollided2d(cd, 1) == 0)
					{
						cp1--;
						continue;
					}

					brake = (cd[0].length[0] - carLength[0]) - boxOverlap;

					if (brake < 1)
						brake = 1;

					if (brakeLength[cp0->id] == 0 || brake < brakeLength[cp0->id])
						brakeLength[cp0->id] = brake;

					// don't do anything further when it tries to park
					if (cp0->ai.c.thrustState == 3)
					{
						cp1--;
						continue;
					}

					if (CAR_INDEX(cp1) == TANNER_COLLIDER_CARID)
						cp0->ai.c.carPauseCnt = CAR_PAUSE_START;

					// do horns
					// horn to player and chased cars (except Steal the Ambulance)
					if (cp0->ai.c.thrustState != 3 &&
						(cp1->controlType == CONTROL_TYPE_PLAYER || cp1->controlType == CONTROL_TYPE_CUTSCENE && gCurrentMissionNumber != 26 && ProxyBar.active == 0 || 
						CAR_INDEX(cp1) == TANNER_COLLIDER_CARID))
					{
						int dont;
						int rnd;
						rnd = Random2(0);

						dont = 0;

						i = 0;
						do {
							if (horncarflag[i] == cp0)
							{
								dont = 1;
								break;
							}

							i++;
						} while (i < 2);

						if (dont)
						{
							cp1--;
							continue;
						}

						i = 0;
						do {
							if (hornchanflag[i] == 0)
							{
								int sample;

								hornchanflag[i] = GetFreeChannel();
								SpuSetVoiceAR(hornchanflag[i], 0x1b);

								if (cp0->ap.model == 4)
									sample = ResidentModelsBodge();
								else if (cp0->ap.model < 3)
									sample = cp0->ap.model;
								else
									sample = cp0->ap.model - 1;

								Start3DSoundVolPitch(hornchanflag[i], SOUND_BANK_CARS, sample * 3 + 2, cp0->hd.where.t[0], cp0->hd.where.t[1], cp0->hd.where.t[2], -2000, 0x1000);
								horncarflag[i] = cp0;

								channels[hornchanflag[i]].time += rnd - (rnd / 30) * 30;
								break;
							}

							i++;
						} while (i < 2);
					}
				}

				cp1--;
			}
		}
		cp0--;
	}

	// clear on timeout
	i = 0;
	do {
		if (hornchanflag[i] != 0 && channels[hornchanflag[i]].time == 0)
		{
			horncarflag[i] = NULL;
			hornchanflag[i] = 0;

			SpuSetVoiceAR(0, 35);
		}

		i++;

	} while (i < 2);
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivAccel(CAR_DATA *cp /*$s0*/)
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

// [D] [T]
int CivAccel(CAR_DATA * cp)
{
	CIV_ROUTE_ENTRY* node;
	int distToNode;
	int ret;

	node = cp->ai.c.ctrlNode;
	carnum = CAR_INDEX(cp);

	if (node == NULL || cp->ai.c.thrustState == 3)
	{
		distToNode = -1;
	}
	else
	{
		int dx, dz;
		dx = cp->hd.where.t[0] - node->x;
		dz = cp->hd.where.t[2] - node->z;

		distToNode = SquareRoot0(dx * dx + dz * dz);
	}

	if (cp->ai.c.thrustState != 3 && node && node->pathType == 127)
	{
		distToNode = -distToNode;
	}

	ret = CivAccelTrafficRules(cp, &distToNode);

	if (cp->ai.c.thrustState != 3)
	{
		int lbd2;
		int lbody;
		int tmpret;
		int brakeDist;

		collDat = brakeLength[cp->id];

		lbody = cp->ap.carCos->colBox.vz;

		// brake in front of obstacles
		if (collDat != 0)
		{
			int sf, c1, c2;
			sf = lbody / 2;

			if (collDat < lbody * 2)
			{
				if (/*lbody * 2 < collDat &&*/ sf <= collDat)	// [A] ancient bug fix
				{
					sf = sf - lbody * 2;
					tmpret = ((collDat + lbody * -2) * -100) / sf + 100;
				}
				else if (sf < collDat && (lbody / 4) <= collDat)
				{
					c2 = (lbody / 4) - sf;
					tmpret = ((collDat - sf) * -300) / c2 + 400;
				}
				else
				{
					tmpret = 100;
				}
			}
			else
			{
				tmpret = 0;
			}

			tmpret = (newAccel * tmpret) / 100;
			brakeDist = (-cp->hd.wheel_speed) / 4;

			if (tmpret >= brakeDist)
			{
				if (brakeDist < tmpret * -2)
					tmpret *= -2;
				else
					tmpret = brakeDist;
			}

			if (ret > tmpret)
				ret = tmpret;
		}

		// stop car if interrupted by pedestrian Tanner
		if (cp->ai.c.carPauseCnt > 0 && collDat == 0)
		{
			int spd;
			spd = cp->hd.wheel_speed;

			if (ABS(FIXEDH(spd)) < 3)
			{
				ret = (-spd) / 4;
				cp->ai.c.carPauseCnt -= 1;
			}
		}
	}

	return ret;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivSteerAngle(CAR_DATA *cp /*$s0*/)
	// line 3166, offset 0x0002b53c
	/* begin block 1 */
		// Start line: 3167
		// Start offset: 0x0002B53C
		// Variables:
	// 		int station; // $a3
	// 		int step; // $s2
	// 		int ret; // $a0
	// 		VECTOR locPath; // stack offset -56
	// 		VECTOR pathPoint; // stack offset -40
	// 		int lbody; // $s3

		/* begin block 1.1 */
			// Start line: 3167
			// Start offset: 0x0002B53C

			/* begin block 1.1.1 */
				// Start line: 3167
				// Start offset: 0x0002B53C
				// Variables:
			// 		CAR_DATA *cp; // $s0

				/* begin block 1.1.1.1 */
					// Start line: 3167
					// Start offset: 0x0002B53C
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
			// 		CAR_DATA *cp; // $s0

				/* begin block 1.1.2.1 */
					// Start line: 3167
					// Start offset: 0x0002B5A0
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
			// 		CAR_DATA *cp; // $s0

				/* begin block 1.1.3.1 */
					// Start line: 3167
					// Start offset: 0x0002B5C0
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
			// 		CAR_DATA *cp; // $s0

				/* begin block 1.1.4.1 */
					// Start line: 3167
					// Start offset: 0x0002B5E0
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
		// 		CAR_DATA *cp; // $s0

			/* begin block 1.2.1 */
				// Start line: 3167
				// Start offset: 0x0002B67C
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $a0
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
		// 		CIV_ROUTE_ENTRY *crLoc; // $a1
		// 		CIV_ROUTE_ENTRY *cr; // $a0
		/* end block 1.3 */
		// End offset: 0x0002B700
		// End Line: 3212

		/* begin block 1.4 */
			// Start line: 3167
			// Start offset: 0x0002B748
			// Variables:
		// 		CAR_DATA *cp; // $s0

			/* begin block 1.4.1 */
				// Start line: 3167
				// Start offset: 0x0002B748
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
		// 		CIV_ROUTE_ENTRY *cr; // $a0

			/* begin block 1.5.1 */
				// Start line: 3167
				// Start offset: 0x0002B8A0
				// Variables:
			// 		CAR_DATA *cp; // $s0

				/* begin block 1.5.1.1 */
					// Start line: 3167
					// Start offset: 0x0002B8A0
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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

// [D] [T] [A] - removed copying of car. Still works okay
int CivSteerAngle(CAR_DATA * cp)
{
	CIV_ROUTE_ENTRY* startNode;
	short lbody;
	CIV_ROUTE_ENTRY* retNode;
	CIV_ROUTE_ENTRY* crLoc;
	VECTOR locPath;
	VECTOR pathPoint;
	int i;

	pathPoint.vx = 0;
	pathPoint.vy = 0;
	pathPoint.vz = 0;

	startNode = cp->ai.c.pnode;

	lbody = cp->ap.carCos->colBox.vz;

	// we need 3 nodes, try making them in each different frame
	i = 0;
	do
	{
		if (GET_NEXT_NODE(cp, startNode + i)->pathType == 127)
		{
			if (CreateNewNode(cp) == 0)
			{
				CIV_STATE_SET_CONFUSED(cp);
				return 0;
			}
		}
		i++;
	} while (i < 4);

	if (startNode->pathType != 127)
	{
		retNode = GET_NEXT_NODE(cp, cp->ai.c.pnode);

		if (retNode->pathType != 127)
		{
			int station;
			station = CivFindStation(cp);

			crLoc = cp->ai.c.pnode;

			if (crLoc->pathType != 127)
			{
				retNode = GET_NEXT_NODE(cp, cp->ai.c.pnode);

				if (retNode->pathType != 127)
				{
					CIV_ROUTE_ENTRY* cr;

					int ret;
					int dx, dz;
					CivFindPointOnPath(cp, station + FIXEDH(cp->hd.wheel_speed) * checkFrames + lbody, &pathPoint);

					dx = pathPoint.vx - cp->hd.where.t[0];
					dz = pathPoint.vz - cp->hd.where.t[2];

					ret = ((ratan2(dx, dz) - cp->hd.direction) + 0x800U & 0xfff) - 2048;

					if (ret < -maxSteer)
						ret = -maxSteer;
					else if (ret > maxSteer)
						ret = maxSteer;

					// invalidate old nodes
					cr = startNode;
					while (cr != cp->ai.c.pnode)
					{
						cr->pathType = 127;

						// invalidate current turn node
						if (cp->ai.c.turnNode == GET_NODE_ID(cp, cr))
							cp->ai.c.turnNode = -1;

						cr = GET_NEXT_NODE(cp, cr);
					}

					return ret;
				}
			}
		}
	}

	CIV_STATE_SET_CONFUSED(cp);
	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivFindStation(CAR_DATA *cp /*$s6*/)
	// line 3265, offset 0x0002b8e4
	/* begin block 1 */
		// Start line: 3266
		// Start offset: 0x0002B8E4
		// Variables:
	// 		CIV_ROUTE_ENTRY *rep; // $s3
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
			// 		CAR_DATA *cp; // $s6

				/* begin block 1.1.1.1 */
					// Start line: 3266
					// Start offset: 0x0002B93C
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
		// 		CAR_DATA *cp; // $s6
		// 		CIV_ROUTE_ENTRY *currentNode; // $s3

			/* begin block 1.2.1 */
				// Start line: 3280
				// Start offset: 0x0002B964
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $s0
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
			// 		CAR_DATA *cp; // $s6
			// 		CIV_ROUTE_ENTRY *currentNode; // $s3

				/* begin block 1.3.1.1 */
					// Start line: 3309
					// Start offset: 0x0002BA28
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
			// 		CAR_DATA *cp; // $s6
			// 		CIV_ROUTE_ENTRY *currentNode; // $s3

				/* begin block 1.3.2.1 */
					// Start line: 3266
					// Start offset: 0x0002BA48
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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
			// 		CAR_DATA *cp; // $s6
			// 		CIV_ROUTE_ENTRY *currentNode; // $s3

				/* begin block 1.3.3.1 */
					// Start line: 3266
					// Start offset: 0x0002BA68
					// Variables:
				// 		CIV_ROUTE_ENTRY *retNode; // $v1
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

// [D] [T]
int CivFindStation(CAR_DATA * cp)
{

	int loop;
	int square;
	CIV_ROUTE_ENTRY* currentNode;
	CIV_ROUTE_ENTRY* retNode;
	CIV_ROUTE_ENTRY* rep;
	int dz;
	int dx;

	int sz;
	int sx;

	int cx;
	int cz;
	int stepsize;
	int i;

	cx = cp->hd.where.t[0];
	cz = cp->hd.where.t[2];

	loop = cp->ai.c.currentNode - 1;

	currentNode = cp->ai.c.targetRoute;
	rep = currentNode;
	while (loop >= 0)
	{
		currentNode = rep = GET_NEXT_NODE(cp, rep);
		loop--;
	}

	do {
		retNode = GET_NEXT_NODE(cp, currentNode);

		if (retNode == NULL)
			break;

		sx = currentNode->x;
		sz = currentNode->z;

		dx = retNode->x - sx;
		dz = retNode->z - sz;

		square = dx * dx + dz * dz;

		if (square < 0)
			break;

		square = SquareRoot0(square);
		if (square > 0)
		{
			stepsize = ((cx - sx) * dx + (cz - sz) * dz) / square;

			if (stepsize < square)
			{
				cp->ai.c.pnode = currentNode;
				return stepsize;
			}
		}

		currentNode = retNode;
		cp->ai.c.currentNode = GET_NODE_ID(cp, currentNode);

		i = 1;
		do
		{
			if (GET_NEXT_NODE(cp, retNode + i)->pathType == 127)
				CreateNewNode(cp);

			i++;
		} while (i < 4);
	} while (true);

	CIV_STATE_SET_CONFUSED(cp);

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CivFindPointOnPath(CAR_DATA *cp /*$s7*/, int station /*$s2*/, VECTOR *ppoint /*$fp*/)
	// line 3337, offset 0x0002baec
	/* begin block 1 */
		// Start line: 3338
		// Start offset: 0x0002BAEC
		// Variables:
	// 		CIV_ROUTE_ENTRY *cprep; // $a0
	// 		CIV_ROUTE_ENTRY *start; // stack offset -48

		/* begin block 1.1 */
			// Start line: 3346
			// Start offset: 0x0002BB50
			// Variables:
		// 		CAR_DATA *cp; // $s7
		// 		CIV_ROUTE_ENTRY *currentNode; // $a0

			/* begin block 1.1.1 */
				// Start line: 3346
				// Start offset: 0x0002BB50
				// Variables:
			// 		CIV_ROUTE_ENTRY *retNode; // $s0
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

// [D] [T]
int CivFindPointOnPath(CAR_DATA * cp, int station, VECTOR * ppoint)
{
	int stepSize;
	CIV_ROUTE_ENTRY* start;
	CIV_ROUTE_ENTRY* currentNode;
	CIV_ROUTE_ENTRY* retNode;
	int dx;
	int dz;
	int sx;
	int sz;

	start = cp->ai.c.pnode;

	if (start != NULL)
	{
		currentNode = start;

		do {
			retNode = currentNode + 1;

			if (cp->ai.c.targetRoute + 13 <= retNode)	// [A] there was reflections bug?
				retNode = currentNode - 12;

			if (retNode == NULL || retNode && retNode->pathType == 127)
			{
				ppoint->vx = currentNode->x;
				ppoint->vz = currentNode->z;

				return 1;
			}

			sx = currentNode->x;
			sz = currentNode->z;

			dx = retNode->x - sx;
			dz = retNode->z - sz;
			stepSize = SquareRoot0(dx * dx + dz * dz);

			// advance
			if (station < stepSize)
			{
				if (station < 0)
					station = 0;

				if (stepSize < 4096)
				{
					ppoint->vx = sx + (dx * station) / stepSize;
					ppoint->vz = sz + (dz * station) / stepSize;
				}
				else
				{
					stepSize /= 16;

					ppoint->vx = sx + FIXEDH(((dx * 256) / stepSize) * station);
					ppoint->vz = sz + FIXEDH(((dz * 256) / stepSize) * station);
				}

				return 1;
			}

			station -= stepSize;
			currentNode = retNode;

		} while (retNode != start);
	}

	CIV_STATE_SET_CONFUSED(cp);

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
	// 		CAR_DATA *cp; // $v1
	// 		CAR_DATA *lcp; // $s0
	// 		CAR_DATA *newCar; // $s0
	// 		DRIVER2_STRAIGHT *str; // stack offset -72
	// 		DRIVER2_CURVE *crv; // $s7
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
			// 		CAR_DATA *cp; // $s0
			/* end block 1.4.2 */
			// End offset: 0x0002C674
			// End Line: 3399

			/* begin block 1.4.3 */
				// Start line: 3399
				// Start offset: 0x0002C708
				// Variables:
			// 		CAR_DATA *cp; // $s0
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
		// 		VECTOR startPos2; // stack offset -88
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
					// 		CAR_DATA *cp; // $s0
					/* end block 1.5.1.1.1 */
					// End offset: 0x0002CBA8
					// End Line: 3399

					/* begin block 1.5.1.1.2 */
						// Start line: 3399
						// Start offset: 0x0002CC3C
						// Variables:
					// 		CAR_DATA *cp; // $s0
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

// [D] [T]
void CreateRoadblock(void)
{
	int laneNo;
	CAR_COSMETICS* car_cos;
	CAR_DATA* cp;
	int distAlongSegment;
	
	DRIVER2_CURVE* crv;
	DRIVER2_STRAIGHT* str;

	VECTOR startPos;
	VECTOR endPos;
	
	VECTOR currentPos;
	int numLanes;
	int externalCopModel;
	int noMoreCars;
	int angle;
	int dir;
	int lbody;
	int delta;
	int dir2NextRow;

	int newSlot;
	CAR_DATA* newCar;

	crv = NULL;
	str = NULL;

	noMoreCars = 0;
	distAlongSegment = -5;
	lbody = car_cosmetics[3].colBox.vz;
	externalCopModel = MissionHeader->residentModels[3];

	// [A] use player instead of car
	dir = player[0].dir;
	
	baseLoc.vx = player[0].pos[0];
	baseLoc.vy = player[0].pos[1];
	baseLoc.vz = player[0].pos[2];
	currentPos.vy = baseLoc.vy;

	angle = 0;

	// scan angle
	do {
		int dv;
		if (requestCopCar == 0)
			dv = rcossin_tbl[(dir + angle & 0xfffU) * 2] << 3;
		else
			dv = rcossin_tbl[(dir + angle & 0xfffU) * 2] * 10;

		roadblockLoc.vx = baseLoc.vx + FIXEDH(dv) * 0x800;

		if (requestCopCar == 0)
			dv = rcossin_tbl[(dir + angle & 0xfffU) * 2 + 1] << 3;
		else
			dv = rcossin_tbl[(dir + angle & 0xfffU) * 2 + 1] * 10;

		roadblockLoc.vz = baseLoc.vz + FIXEDH(dv) * 2048;

		roadSeg = RoadInCell(&roadblockLoc);

		if (IS_STRAIGHT_SURFACE(roadSeg) || IS_CURVED_SURFACE(roadSeg))
			break;

		if (requestCopCar == 0)
			dv = rcossin_tbl[(dir - angle & 0xfffU) * 2] << 3;
		else
			dv = rcossin_tbl[(dir - angle & 0xfffU) * 2] * 10;

		roadblockLoc.vx = baseLoc.vx + FIXEDH(dv) * 2048;

		if (requestCopCar == 0)
			dv = rcossin_tbl[(dir - angle & 0xfffU) * 2 + 1] << 3;
		else
			dv = rcossin_tbl[(dir - angle & 0xfffU) * 2 + 1] * 10;

		roadblockLoc.vz = baseLoc.vz + FIXEDH(dv) * 2048;

		roadSeg = RoadInCell(&roadblockLoc);

		if (IS_STRAIGHT_SURFACE(roadSeg) || IS_CURVED_SURFACE(roadSeg))
			break;

		if (requestCopCar == 0)
			angle = angle + 93;
		else
			angle = angle + 73;

	} while (angle < 2048);

	// no suitable road found
	if (!IS_STRAIGHT_SURFACE(roadSeg) && !IS_CURVED_SURFACE(roadSeg))
		return;

	if (IS_STRAIGHT_SURFACE(roadSeg))
	{
		int segmentLen;
		str = GET_STRAIGHT(roadSeg);

		dx = roadblockLoc.vx - str->Midx;
		dz = roadblockLoc.vz - str->Midz;

		segmentLen = str->length;
		distAlongSegment = (str->length / 2) + FIXEDH(rcossin_tbl[(str->angle - ratan2(dx, dz) & 0xfffU) * 2 + 1] * SquareRoot0(dx * dx + dz * dz));

		if (segmentLen < lbody * 6)
			return;

		if (distAlongSegment < lbody * 3)
			distAlongSegment = lbody * 3;

		if ((segmentLen - distAlongSegment) < lbody * 3)
			distAlongSegment = segmentLen - lbody * 3;

		numLanes = ROAD_WIDTH_IN_LANES(str);
	}
	else if(IS_CURVED_SURFACE(roadSeg))
	{
		int theta;
		int segmentLen;
		int minDistAlong;
		crv = GET_CURVE(roadSeg);

		// check if not outside the curve
		if (((crv->end - crv->start & 0xfffU) * crv->inside * 11) / 7 < lbody * 6)
			return;

		currentAngle = ratan2(roadblockLoc.vx - crv->Midx, roadblockLoc.vz - crv->Midz);
		
		if(crv->inside < 10)
			minDistAlong = 128;
		else if (crv->inside < 20)
			minDistAlong = 64;
		else
			minDistAlong = 32;

		theta = (currentAngle & 0xfffU) - crv->start;
		
		if(crv->inside < 10)
			distAlongSegment = theta & 0xf80;
		else if (crv->inside < 20)
			distAlongSegment = theta & 0xfc0;
		else
			distAlongSegment = theta & 0xfe0;
		
		segmentLen = (crv->end - crv->start) - minDistAlong & 0xfff;

		if (distAlongSegment >= segmentLen)
			distAlongSegment = segmentLen;

		numLanes = ROAD_WIDTH_IN_LANES(crv);
	}

	GetNodePos(str, NULL, crv, distAlongSegment, NULL, (int*)&startPos.vx, (int*)&startPos.vz, 0);

	GetNodePos(str, NULL, crv, distAlongSegment, NULL, (int*)&endPos, (int*)&endPos.vz, numLanes - 1);

	dir2NextRow = ratan2(endPos.vx - startPos.vx, endPos.vz - startPos.vz);

	delta = 256;
	while (delta < numLanes * 512)
	{
		laneNo = (delta >> 9);
		
		currentPos.vx = startPos.vx + FIXEDH(delta * rcossin_tbl[(dir2NextRow & 0xfff) * 2]);
		currentPos.vz = startPos.vz + FIXEDH(delta * rcossin_tbl[(dir2NextRow & 0xfff) * 2 + 1]);

		if((str && ROAD_IS_AI_LANE(str, laneNo) || crv && ROAD_IS_AI_LANE(crv, laneNo)) && 
			CellEmpty(&currentPos, lbody))
		{
			newSlot = CreateStationaryCivCar(dir2NextRow + (Random2(0) * 0x10001 >> (laneNo) & 0x3ffU) - 512, 0, 0, (LONGVECTOR *)&currentPos, externalCopModel, 0, 2);

			if (newSlot == -1)
				break;

			newCar = &car_data[newSlot];

			car_cos = newCar->ap.carCos;

			if (QuickBuildingCollisionCheck((VECTOR*)newCar->hd.where.t, newCar->hd.direction, car_cos->colBox.vz, car_cos->colBox.vx, 0x14) != 0)
			{
				PingOutCar(newCar);
			}

			cp = &car_data[MAX_CARS - 1];
			do {
				if (cp->controlType != CONTROL_TYPE_NONE && !IS_ROADBLOCK_CAR(cp))
				{
					dx = cp->hd.where.t[0] - currentPos.vx;
					dz = cp->hd.where.t[2] - currentPos.vz;

					if (dx * dx + dz * dz < 360000)
					{
						PingOutCar(cp);
					}
				}
				cp--;
			} while (cp >= car_data);
		}

		delta += 1024;
	}

	// try making additional cars
	if (!noMoreCars && gCopDifficultyLevel != 0)
	{
		int faceDir;
		int deltaAngle;
		int theta;
		int numSpareCars;
		int numSpots;
		int count;
		int numCarsToAdd;
		int px, pz;
		
		if (ratan2(baseLoc.vx - startPos.vx, baseLoc.vz - startPos.vz) - dir2NextRow & 0xfff < 2048)
			deltaAngle = -1024;
		else
			deltaAngle = 1024;

		if (gCopDifficultyLevel == 1)
			faceDir = dir2NextRow - deltaAngle;
		else
			faceDir = dir2NextRow;

		theta = dir2NextRow + deltaAngle & 0xfff;
		px = startPos.vx + FIXEDH(rcossin_tbl[theta * 2] * 1500);
		pz = startPos.vz + FIXEDH(rcossin_tbl[theta * 2 + 1] * 1500);
	
		numSpareCars = (maxCivCars - numCivCars) + 2;
		numSpots = numLanes / 2 - 1;

		numCarsToAdd = numSpots;

		if (numCarsToAdd > numSpareCars)
			numCarsToAdd = numSpareCars;

		count = 0;
		while (count < numCarsToAdd)
		{
			delta = ((numSpots * (count * 2 + 1)) / (numCarsToAdd * 2)) * 1024 + 768;

			currentPos.vx = px + FIXEDH(delta * rcossin_tbl[(dir2NextRow & 0xfff) * 2]);
			currentPos.vz = pz + FIXEDH(delta * rcossin_tbl[(dir2NextRow & 0xfff) * 2 + 1]);

			test42 = delta;

			newSlot = CreateStationaryCivCar(faceDir + (Random2(0) * 0x10001 >> (delta >> 9 & 0x1fU) & 0x3ffU) - 512, 0, 0, (LONGVECTOR *)&currentPos, externalCopModel, 0, 2);

			if (newSlot == -1)
				break;

			newCar = &car_data[newSlot];

			car_cos = newCar->ap.carCos;

			if (QuickBuildingCollisionCheck((VECTOR*)newCar->hd.where.t, newCar->hd.direction, car_cos->colBox.vz, car_cos->colBox.vx, 0x14) != 0)
			{
				PingOutCar(newCar);
			}

			cp = &car_data[MAX_CARS - 1];
			do {
				if (cp->controlType != CONTROL_TYPE_NONE && !IS_ROADBLOCK_CAR(cp))
				{
					dx = cp->hd.where.t[0] - currentPos.vx;
					dz = cp->hd.where.t[2] - currentPos.vz;

					if (dx * dx + dz * dz < 360000)
					{
						PingOutCar(cp);
					}
				}
				cp--;
			} while (cp >= car_data);

			count++;
		}
	}

	requestRoadblock = 0;
	roadblockDelay = roadblockDelayDiff[gCopDifficultyLevel] + (Random2(0) & 0xff);
	roadblockCount = roadblockDelay;

	PlaceRoadBlockCops();
}