#include "driver2.h"
#include "civ_ai.h"

#include "system.h"
#include "handling.h"
#include "dr2roads.h"
#include "cosmetic.h"
#include "mission.h"
#include "cop_ai.h"
#include "denting.h"
#include "cars.h"
#include "camera.h"
#include "cutscene.h"
#include "replays.h"
#include "convert.h"
#include "spool.h"
#include "players.h"
#include "gamesnd.h"
#include "sound.h"
#include "bcollide.h"
#include "leadai.h"
#include "main.h"
#include "pedest.h"
#include "objcoll.h"
#include "overlay.h"
#include "cutrecorder.h"

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
} civPingTest;

char modelRandomList[] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 1, 0, 4 };
u_char reservedSlots[MAX_CARS] = { 0 };

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

// [D] [T]
int InitCar(CAR_DATA* cp, int direction, LONGVECTOR4* startPos, unsigned char control, int model, int palette, char* extraData)
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

	tmpStart.vy = MapHeight(&tmpStart) - cp->ap.carCos->wheelDisp[0].vy;

	// not valid request
	if (control == CONTROL_TYPE_NONE)
		return 1;

	InitCarPhysics(cp, (LONGVECTOR4 *)&tmpStart, direction);
	cp->ap.palette = palette;

	cp->controlType = control;

	switch (control)
	{
		case CONTROL_TYPE_PLAYER:
		case CONTROL_TYPE_CUTSCENE:
			// player car or cutscene car
			cp->ai.padid = extraData;

			player[cp->id].worldCentreCarId = cp->id;
			cp->hndType = 0;
			break;
		case CONTROL_TYPE_CIV_AI:
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
		case CONTROL_TYPE_PURSUER_AI:
			InitCopState(cp, extraData);
			cp->ap.palette = 0;
			numCopCars++;
			break;
		case CONTROL_TYPE_LEAD_AI:
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

// [D] [T]
CAR_DATA* FindClosestCar(int x, int y, int z, int* distToCarSq)
{
	u_int distSq;
	CAR_DATA* lcp;
	u_int retDistSq;
	CAR_DATA* retCar;
	int dx; // $a0
	int dz; // $v1

	retCar = NULL;
	retDistSq = INT_MAX;
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

// [D] [T]
int NotTravellingAlongCurve(int x, int z, int dir, DRIVER2_CURVE* cv)
{
	int curveDir;
	int cvDiff;

	curveDir = ratan2(x - cv->Midx, z - cv->Midz);
	cvDiff = DIFF_ANGLES(curveDir, dir); //((dir - curveDir) + 2048U & 0xfff) - 2048U;

	return (cvDiff < 1) * 2048;
}

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

// [D] [T]
int GetNextRoadInfo(CAR_DATA* cp, int randomExit, int* turnAngle, int* startDist, CIV_ROUTE_ENTRY* oldNode)
{
	u_int junctionFlags;
	DRIVER2_JUNCTION* jn;

	DRIVER2_ROAD_INFO currentRoadInfo;
	DRIVER2_ROAD_INFO roadInfo;

	int currentRoadId = 0;
	int tmpNewRoad[2];
	int newExit = 0;
	int tmpNewLane[2];
	int laneFit[2];
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
			oldOppDir = (currentRoadInfo.straight->angle - oldNode->dir) + 1024U & 2048;
		}
		else
		{
			int dx, dz;
			dx = oldNode->x - currentRoadInfo.curve->Midx;
			dz = oldNode->z - currentRoadInfo.curve->Midz;

			oldOppDir = DIFF_ANGLES(ratan2(dx, dz), oldNode->dir); // (((oldNode->dir - ratan2(dx, dz)) + 2048U & 0xfff) - 2048);
			oldOppDir = (oldOppDir < 1) * 2048;
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
					*turnAngle = -1024;	// left
				else if (exitDir == 2)
					*turnAngle = 0;		// forward
				else if (exitDir == 3)
					*turnAngle = 1024;	// right
				else
					*turnAngle = 0;		// forward again?

				test123 = 666;
				test555 = 666;
				test42 = 666;

				// current node direction and new direction
				turnDir = oldNode->dir + *turnAngle;

				if (GetSurfaceRoadInfo(&roadInfo, exitSurfId))
				{
					int turnAng;
					int dx, dz;
					int laneCount;

					laneCount = ROAD_WIDTH_IN_LANES(&roadInfo);

					if(roadInfo.straight)
					{
						oppDir = (roadInfo.straight->angle - turnDir) + 1024U & 2048;
					}
					else
					{
						dx = oldNode->x - roadInfo.curve->Midx;
						dz = oldNode->z - roadInfo.curve->Midz;

						oppDir = DIFF_ANGLES(ratan2(dx, dz), turnDir);// ((turnDir - ratan2(dx, dz)) + 2048U & 0xfff) - 2048; // [A]
						oppDir = (oppDir < 1) * 2048;
					}

					turnAng = *turnAngle;
					
					if (oppDir == 0)
						turnAng = -turnAng;

					if (turnAng == 0) // going forward
					{
						if (oppDir != oldOppDir) // next road is flipped
							newLane = laneCount - (cp->ai.c.currentLane + 1);
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
					}

					// validate lane
					if (turnAng == 0 || newLane >= 0 && newLane < laneCount)
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

		if (numExits == 0)
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

			if (junctionFlags & 1)
			{
				// wait for traffic light
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
			else
			{
				int yield = 0;

				if (exitFrom == 0 || exitFrom == 2)
					yield = 1;

				if (junctionFlags & 2)
				{
					if (yield || *turnAngle != 0)
					{
						cp->ai.c.ctrlNode = oldNode;
						cp->ai.c.ctrlState = 4;
					}
					else
						cp->ai.c.ctrlState = 6;
				}
				else
				{
					

					if (!yield || *turnAngle != 0)
					{
						cp->ai.c.ctrlNode = oldNode;
						cp->ai.c.ctrlState = 4;
					}
					else
						cp->ai.c.ctrlState = 6;
				}
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
				oppDir = (turnDir - roadInfo.straight->angle) + 1024 & 2048;
			}
			else
			{
				int dx, dz;
				dx = oldNode->x - roadInfo.curve->Midx;
				dz = oldNode->z - roadInfo.curve->Midz;

				oppDir = DIFF_ANGLES(ratan2(dx, dz), turnDir); // (((turnDir - ratan2(dx, dz)) + 2048U & 0xfff) - 2048);
				oppDir = (oppDir < 1) * 2048;
			}

			if (turnAng == 0)
			{
				//printWarning("car %d check forward lane\n", cp->id);
				
				if (oppDir == oldOppDir)
					newLane = cp->ai.c.currentLane;
				else
					newLane = numLanes - (cp->ai.c.currentLane + 1);

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
					if (ROAD_LANE_DIR(&roadInfo, 0) == ROAD_LANE_DIR(&roadInfo, newLane + 1))
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

						tmpNewLane[roadCnt] = ROAD_LANES_COUNT(&roadInfo)
											- (FIXEDH(dx * RCOS(roadInfo.straight->angle) - dz * RSIN(roadInfo.straight->angle)) + 512 >> 9);

					}
					else
					{
						dx = oldNode->x - roadInfo.curve->Midx;
						dz = oldNode->z - roadInfo.curve->Midz;

						tmpNewLane[roadCnt] = (SquareRoot0(dx * dx + dz * dz) >> 9) - roadInfo.curve->inside * 2;
					}
				}

				// [A] if there are more than one connections we check the bounds strictly
				if(numExits > 1)
				{
					if (tmpNewLane[roadCnt] < 0 || tmpNewLane[roadCnt] >= numLanes)
					{
						laneFit[roadCnt] = 666;
						numExits--;	// there has to be one exit
						continue;
					}
				}


				// fit new lane
				newLane = tmpNewLane[roadCnt];

				if (newLane < 0)
					laneFit[roadCnt] = 0;
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

		theta = straight->angle - ratan2(dx, dz);
		cr->distAlongSegment = (straight->length / 2) + FIXEDH(RCOS(theta) * SquareRoot0(dx * dx + dz * dz));

		laneDist = ROAD_LANES_COUNT(straight) * 512 + FIXEDH(-dx * RCOS(straight->angle) + dz * RSIN(straight->angle));
		cp->ai.c.currentLane = laneDist / 512;

		// calc all dirs
		if (ROAD_LANE_DIR(straight, cp->ai.c.currentLane))
			cr->dir = straight->angle + 2048U & 0xfff;
		else
			cr->dir = straight->angle;
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
		distFromCentre = distAlongPath - (straight->length / 2);

		if (angle < 2048)
		{
			if (laneNo <= oldLane)
				test42 = -changeLaneCount * 128;
			else
				test42 = changeLaneCount * 128;

			sideShift = (ROAD_LANES_COUNT(straight) * 512 - (laneNo * 512 + 256)) + test42;

			*x = straight->Midx + FIXEDH(distFromCentre * RSIN(angle)) +
								  FIXEDH(sideShift * RCOS(angle));

			*z = straight->Midz + FIXEDH(distFromCentre * RCOS(angle)) -
								  FIXEDH(sideShift * RSIN(angle));
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

		if (oldLane <= laneNo)
			test42 = -changeLaneCount * 128;
		else
			test42 = changeLaneCount * 128;

		radius = curve->inside * 1024 + laneNo * 512 + 256 + test42;

		*x = curve->Midx + FIXEDH(radius * RSIN(angle));
		*z = curve->Midz + FIXEDH(radius * RCOS(angle));
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
	u_int theta;
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
		int segLen;

		if (straight == NULL)
		{
			roadWidthInLanes = ROAD_WIDTH_IN_LANES(curve);
			segLen = curve->end - curve->start & 0xfff;
		}
		else
		{
			roadWidthInLanes = ROAD_WIDTH_IN_LANES(straight);
			segLen = straight->length;
		}

		newLane = currentLane + (Random2((int)straight) >> 7 & 2U) + 0xff & 0xff;
		
		if (tryToPark)
		{
			if (oldLane == 1)
				newLane = 0;
			else if (roadWidthInLanes - 2 == currentLane)
				newLane = roadWidthInLanes - 1;

			// [A] don't park near the road ends
			if(distAlongSegment < 1024 && distAlongSegment > segLen - 1024)
				return currentLane;
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
			else if (tryToPark)
			{
				int allowedToDrive;
				allowedToDrive = straight && ROAD_IS_AI_LANE(straight, newLane) || curve && ROAD_IS_AI_LANE(curve, newLane);

				if (!allowedToDrive)
					continue;
			}
			else
			{
				int allowedToPark;
				int allowedToDrive;

				// collect the lanes.
				allowedToPark = straight && ROAD_IS_PARKING_ALLOWED_AT(straight, newLane) || curve && ROAD_IS_PARKING_ALLOWED_AT(curve, newLane);
				allowedToDrive = straight && ROAD_IS_AI_LANE(straight, newLane) || curve && ROAD_IS_AI_LANE(curve, newLane);

				if (!allowedToDrive || allowedToPark)
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

				cd[0].x.vx = cp->hd.oBox.location.vx + FIXEDH(RSIN(theta) * 512);
				cd[0].x.vz = cp->hd.oBox.location.vz + FIXEDH(RCOS(theta) * 512);
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
							if (bcollided2d(cd))
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
			cp->ai.c.changeLaneIndicateCount = 161;
			cp->ai.c.oldLane = oldLane;
			cp->ai.c.changeLaneCount = 4;
			cp->ai.c.changeLane = turnRight;
			currentLane = newLane;
		}
	}

	return currentLane;
}

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
					if ((Random2(0) + cp->id * 32 & 0xf1) == 0xf1 || makeLimoPullOver)
					{
						int tryToPark;
						int newLane;

						tryToPark = 0;

						if (numParkedCars < maxParkedCars)
							tryToPark = (Random2(0) & 2U) != 0;

						// apply our Caine's Cash logic
						if (gCurrentMissionNumber == 33 && cp->ap.model == 4 && limoId == cp->id) // [A] limoId was skipped, bringing it back.
						{
							tryToPark = makeLimoPullOver;
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
									cp->ai.c.ctrlNode = newNode; // [A]
									cp->ai.c.changeLaneCount = 0;
								}
							}
						}
					}		

					tempNode.x = newNode->x;
					tempNode.z = newNode->z;

					tempNode.dir = newNode->dir;
					tempNode.pathType = newNode->pathType;
					tempNode.distAlongSegment = newNode->distAlongSegment;

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
						cornerAngle = DIFF_ANGLES(start->dir, ratan2(dx, dz)); //((ratan2(dx, dz) - start->dir) + 2048U & 0xfff) - 2048;

						tmp = FIXEDH(segLength * RCOS(cornerAngle));

						retNode = newNode;
						if (tmp > 0)
						{
							newNode->x = start->x + FIXEDH(tmp * RSIN(start->dir));
							newNode->z = start->z + FIXEDH(tmp * RCOS(start->dir));

							newNode->pathType = 1;
							newNode->dir = start->dir;

							retNode = GET_NEXT_NODE(cp, newNode);
						}

						tmp = FIXEDH(segLength * RSIN(cornerAngle));

						newNode = retNode;

						if (tmp < 0)
						{
							retNode->x = tempNode.x + FIXEDH(tmp * RSIN(tempNode.dir));
							retNode->z = tempNode.z + FIXEDH(tmp * RCOS(tempNode.dir));

							retNode->pathType = 1;
							retNode->dir = tempNode.dir;

							newNode = GET_NEXT_NODE(cp, retNode);
						}
					}

					// push into empty node
					if (newNode->pathType == 127)
					{
						newNode->x = tempNode.x;
						newNode->z = tempNode.z;

						newNode->dir = tempNode.dir;
						newNode->pathType = tempNode.pathType;
						newNode->distAlongSegment = tempNode.distAlongSegment;

						if (ABS(tempNode.x) < 600000)
						{
							if (turnAngle)
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
		cs->currentRoad = GetSurfaceIndex((VECTOR*)cp->hd.where.t);
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

	// inform target that car was pinged out
	if (cp->inform)
		*cp->inform ^= TARGET_FLAG_CAR_PINGED_IN;
	
	cp->inform = NULL;

	ClearMem((char*)cp, sizeof(CAR_DATA));

	cp->controlType = CONTROL_TYPE_NONE;

	return 1;
}

// [D] [T]
// used when secret car is requested
int PingOutAllSpecialCivCars(void)
{
	CAR_DATA* lcp;

	lcp = car_data;

	do
	{
		if (lcp->controlType == CONTROL_TYPE_CIV_AI && MissionHeader->residentModels[lcp->ap.model] > 4)
			PingOutCar(lcp);

		lcp++;
	}
	while (lcp < &car_data[MAX_CARS]);

	return 1;
}

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

// [D] [T]
// called by civ car.
// checks distance from player and removes car if too far
int CheckPingOut(CAR_DATA * cp)
{
	int dx, dz;
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

// [D] [T]
void SetUpTrafficLightPhase(void)
{
	junctionLightsPhase[0] = TrafficLightCycle(0);
	junctionLightsPhase[1] = TrafficLightCycle(1);
}

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

const int EVENT_CAR_SPEED = 71;
const int DistanceTriggerCarMoves = 5000;

// [D] [T] [A]
int CreateCivCarWotDrivesABitThenStops(int direction, LONGVECTOR4* startPos, LONGVECTOR4* stopPos, unsigned char internalModel, int palette)
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
	} while (carCnt < &car_data[MAX_CARS]);

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
	pNewCar->st.n.linearVelocity[0] = EVENT_CAR_SPEED * RSIN(direction);
	pNewCar->st.n.linearVelocity[2] = EVENT_CAR_SPEED * RCOS(direction);

	pNewCar->ai.c.velRatio = (EVENT_CAR_SPEED * ONE) / (DistanceTriggerCarMoves - pNewCar->ap.carCos->colBox.vz * 3);
	pNewCar->ai.c.targetRoute[0].x = (*startPos)[0];
	pNewCar->ai.c.targetRoute[0].z = (*startPos)[2];

	stopNode = &pNewCar->ai.c.targetRoute[1];
	pNewCar->ai.c.ctrlNode = stopNode;

	stopNode->pathType = 1;
	stopNode->dir = direction;
	stopNode->distAlongSegment = 0;

	stopNode->x = (*startPos)[0] + FIXEDH(DistanceTriggerCarMoves * RSIN(direction));
	stopNode->z = (*startPos)[2] + FIXEDH(DistanceTriggerCarMoves * RCOS(direction));

	spareNode = &pNewCar->ai.c.targetRoute[2];
	spareNode->pathType = 1;
	spareNode->dir = direction;
	spareNode->distAlongSegment = 0;

	spareNode->x = (*startPos)[0] + FIXEDH(DistanceTriggerCarMoves * RSIN(direction) * 3);
	spareNode->z = (*startPos)[2] + FIXEDH(DistanceTriggerCarMoves * RCOS(direction) * 3);

	numCivCars++;

	return pNewCar->id;
}

// [D] [T]
int CreateStationaryCivCar(int direction, long orientX, long orientZ, LONGVECTOR4* startPos, int externalModel, int palette, int controlFlags)
{
	unsigned char* slot;
	CAR_DATA* newCar;
	CAR_DATA* carCnt;
	int model;
	EXTRA_CIV_DATA civDat;
	LONGQUATERNION tmpQ;

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

		do {
			if (carCnt->controlType == CONTROL_TYPE_NONE && *slot == 0)
			{
				newCar = carCnt;
				break;
			}

			carCnt++;
			slot++;
		} while (carCnt < &car_data[MAX_CARS]);

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
			
			dx = RSIN(orientZ / 2);
			dz = RCOS(orientZ / 2);

			tmpQ[0] = FIXEDH(newCar->st.n.orientation[1] * dx + newCar->st.n.orientation[0] * dz);
			tmpQ[1] = FIXEDH(newCar->st.n.orientation[1] * dz - newCar->st.n.orientation[0] * dx);
			tmpQ[2] = FIXEDH(newCar->st.n.orientation[3] * dx + newCar->st.n.orientation[2] * dz);
			tmpQ[3] = FIXEDH(newCar->st.n.orientation[3] * dz - newCar->st.n.orientation[2] * dx);

			dx = RSIN(orientX / 2);
			dz = RCOS(orientX / 2);

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


VECTOR baseLoc;
VECTOR randomLoc;
int dx = 0; // offset 0xAAB40
int dy = 0; // offset 0xAAB44
int dz = 0; // offset 0xAAB48

#define PINGIN_DIST_WANTED_MULT			(10)
#define PINGIN_DIST_MULT		(8)

// [D] [T] [A] - some register is not properly decompiled
int PingInCivCar(int minPingInDist)
{
	int model;
	CAR_DATA* carCnt;
	CAR_DATA* newCar;
	
	//DRIVER2_CURVE* curve;
	//DRIVER2_STRAIGHT* straight;

	DRIVER2_ROAD_INFO roadInfo;
	
	EXTRA_CIV_DATA civDat;
	u_char possibleLanes[12];
	// carDistLanes removed as it's unused
	LONGVECTOR4 pos;
	int distSq;
	int dir;
	int curveLength;
	int tryPingInParkedCars;
	int count;
	int lbody;
	int lane;
	int i;
	u_char cookieCountStart;
	u_int retDistSq;
	unsigned char* slot;

	//straight = NULL;
	//curve = NULL;
	
	civDat.distAlongSegment = -5;
	lane = -1;
	dir = 0xffffff;

	tryPingInParkedCars = 0;

	PingOutCivsOnly = 1;

	_CutRec_HandleCarRequest();
	
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

	if (numCivCars >= maxCivCars - 1 && gInGameChaseActive == 0)
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

		if (requestCopCar != 0)
		{
			angle = (cookieCount * ONE) / 56;
			dx = RSIN(angle) * PINGIN_DIST_WANTED_MULT;
			dz = RCOS(angle) * PINGIN_DIST_WANTED_MULT;
		}
		else
		{
			angle = (cookieCount * ONE) / 44;
			dx = RSIN(angle) * PINGIN_DIST_MULT;
			dz = RCOS(angle) * PINGIN_DIST_MULT;
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
		} while (carCnt < &car_data[MAX_CARS]);

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

			if (requestCopCar != 0)
			{
				angle = (cookieCount * ONE) / 56;
				dx = RSIN(angle) * PINGIN_DIST_WANTED_MULT;
				dz = RCOS(angle) * PINGIN_DIST_WANTED_MULT;
			}
			else
			{
				angle = (cookieCount * ONE) / 44;
				dx = RSIN(angle) * PINGIN_DIST_MULT;
				dz = RCOS(angle) * PINGIN_DIST_MULT;
			}

			// [A] make limo ping in closer and in right direction
			if (minPingInDist == 666)
			{
				randomLoc.vx = baseLoc.vx + FIXEDH(dx) * 1024;
				randomLoc.vz = baseLoc.vz + FIXEDH(dz) * 1024;
			}
			else
			{
				randomLoc.vx = baseLoc.vx + FIXEDH(dx) * 2048;
				randomLoc.vz = baseLoc.vz + FIXEDH(dz) * 2048;
			}
			
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
		if (minPingInDist == 666)
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
	if (minPingInDist == 666)
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

		theta = roadInfo.straight->angle - ratan2(dx, dz);

		civDat.distAlongSegment = (roadInfo.straight->length / 2) + FIXEDH(RCOS(theta) * SquareRoot0(dx * dx + dz * dz));

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
			dir = roadInfo.straight->angle + 2048U & 0xfff;
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
			dir = civDat.distAlongSegment + roadInfo.curve->start + 1024;
		else
			dir = civDat.distAlongSegment + roadInfo.curve->start - 1024;

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

	retDistSq = INT_MAX;
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
			u_int sqDist;

			dy = randomLoc.vy - carCnt->hd.where.t[1];
			dy = ABS(dy);

			if (dy < 800)
			{
				dx = pos[0] - carCnt->hd.where.t[0];
				dz = pos[2] - carCnt->hd.where.t[2];

				sqDist = (dx * dx + dz * dz);

				if (ABS(dx) < 4096 && ABS(dz) < 4096 && sqDist < retDistSq)
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

	if (minPingInDist == 666)
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
	_CutRec_StorePingInfo(cookieCount, newCar->id);

	return newCar->id + 1;
}


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

	// why only first car must die?
	// P.S. it's the only one with the music
	if (cp->id == 1 && cp->ai.c.carMustDie == 1)
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

				if (ABS(brakeDist) > *distToNode)
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

				if (*distToNode < distToEnd + 32) // [A] add some number to make Havana cops not getting stuck while yielding
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

				if (IS_NODE_VALID(cp, cp->ai.c.ctrlNode))
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

			carDir = cp->hd.direction;
			distToObstacle = 0x7fffff;

			lcp = &car_data[MAX_CARS-1];
			while (lcp >= car_data)
			{
				if (lcp->ai.c.thrustState != 3 &&
					lcp->ai.c.ctrlState != 4 &&		// [A] don't check cars that are yielding
					lcp != cp && 
					lcp->controlType != CONTROL_TYPE_NONE)
				{
					dx = lcp->hd.where.t[0] - cp->hd.where.t[0];
					dz = lcp->hd.where.t[2] - cp->hd.where.t[2];

					tangent = FIXEDH(dx * RSIN(carDir) + dz * RCOS(carDir));
					normal  = FIXEDH(dx * RCOS(carDir) - dz * RSIN(carDir));

					if (tangent > 0)
					{
						// keep it 6. Does work alright
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

int brakeLength[MAX_CARS];

int CAR_PAUSE_START = 100;
static CAR_DATA(*horncarflag[2]) = { 0 };
static u_char hornchanflag[2] = { 0 };

// [D] [T]
void SetUpCivCollFlags(void)
{
	CAR_COSMETICS* car_cos;
	CAR_DATA* cp1;
	SVECTOR boxDisp;
	CAR_DATA* cp0;
	int carLength[2];
	int i;
	int brake;
	int dx;
	int extraLength;
	int boxOverlap;

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
					if (!bcollided2d(cd, &boxOverlap))
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

						for (i = 0; i < 2; i++)
						{
							if (horncarflag[i] == cp0)
							{
								dont = 1;
								break;
							}
						}

						if (dont)
						{
							cp1--;
							continue;
						}

						for (i = 0; i < 2; i++) 
						{
							if (hornchanflag[i] == 0)
							{
								int sample;

								hornchanflag[i] = GetFreeChannel();
								SpuSetVoiceAR(hornchanflag[i], 27);

								if (cp0->ap.model == 4)
									sample = ResidentModelsBodge();
								else if (cp0->ap.model < 3)
									sample = cp0->ap.model;
								else
									sample = cp0->ap.model - 1;

								// [A] use tracking sound
								Start3DTrackingSound(hornchanflag[i], SOUND_BANK_CARS, sample * 3 + 2, 
									(VECTOR*)cp0->hd.where.t,
									(LONGVECTOR3*)cp0->st.n.linearVelocity);
								
								SetChannelVolume(hornchanflag[i], -2000, 0);

								horncarflag[i] = cp0;

								channels[hornchanflag[i]].time += rnd - (rnd / 30) * 30;
								break;
							}
						}
					}
				}

				cp1--;
			}
		}
		cp0--;
	}

	// clear on timeout
	for (i = 0; i < 2; i++)
	{
		if (hornchanflag[i] != 0 && channels[hornchanflag[i]].time == 0)
		{
			horncarflag[i] = NULL;
			hornchanflag[i] = 0;

			SpuSetVoiceAR(0, 35);
		}
	}
}

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

	if (start)
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

const int checkFrames = 20;
const int maxSteer = 512;

// [D] [T] [A] - removed copying of car. Still works okay
int CivSteerAngle(CAR_DATA* cp)
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

					ret = DIFF_ANGLES(cp->hd.direction, ratan2(dx, dz)); // ((ratan2(dx, dz) - cp->hd.direction) + 2048U & 0xfff) - 2048;

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

	// scan for roads
	do {
		int dx, dz;
		
		if (requestCopCar != 0)
		{
			dx = RSIN(dir + angle) * PINGIN_DIST_WANTED_MULT;
			dz = RCOS(dir + angle) * PINGIN_DIST_WANTED_MULT;
		}
		else
		{
			dx = RSIN(dir + angle) * PINGIN_DIST_MULT;
			dz = RCOS(dir + angle) * PINGIN_DIST_MULT;
		}

		roadblockLoc.vx = baseLoc.vx + FIXEDH(dx) * 2048;
		roadblockLoc.vz = baseLoc.vz + FIXEDH(dz) * 2048;

		roadSeg = RoadInCell(&roadblockLoc);

		if (IS_STRAIGHT_SURFACE(roadSeg) || IS_CURVED_SURFACE(roadSeg))
			break;

		if (requestCopCar != 0)
		{
			dx = RSIN(dir - angle) * PINGIN_DIST_WANTED_MULT;
			dz = RCOS(dir - angle) * PINGIN_DIST_WANTED_MULT;
		}
		else
		{
			dx = RSIN(dir - angle) * PINGIN_DIST_MULT;
			dz = RCOS(dir - angle) * PINGIN_DIST_MULT;
		}

		roadblockLoc.vx = baseLoc.vx + FIXEDH(dx) * 2048;
		roadblockLoc.vz = baseLoc.vz + FIXEDH(dz) * 2048;

		roadSeg = RoadInCell(&roadblockLoc);

		if (IS_STRAIGHT_SURFACE(roadSeg) || IS_CURVED_SURFACE(roadSeg))
			break;

		// FIXME: there must be some computed constant
		if (requestCopCar != 0)
			angle += 73;
		else
			angle += 93;

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
		distAlongSegment = (str->length / 2) + FIXEDH(RCOS(str->angle - ratan2(dx, dz)) * SquareRoot0(dx * dx + dz * dz));

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
		
		currentPos.vx = startPos.vx + FIXEDH(delta * RSIN(dir2NextRow));
		currentPos.vz = startPos.vz + FIXEDH(delta * RCOS(dir2NextRow));

		if((str && ROAD_IS_AI_LANE(str, laneNo) || crv && ROAD_IS_AI_LANE(crv, laneNo)) && 
			CellEmpty(&currentPos, lbody))
		{
			newSlot = CreateStationaryCivCar(dir2NextRow + (Random2(0) * 0x10001 >> (laneNo) & 0x3ffU) - 512, 0, 0, (LONGVECTOR4 *)&currentPos, externalCopModel, 0, 2);

			if (newSlot == -1)
			{
				noMoreCars = 1;
				break;
			}

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

		theta = dir2NextRow + deltaAngle;
		px = startPos.vx + FIXEDH(RSIN(theta) * 1500);
		pz = startPos.vz + FIXEDH(RCOS(theta) * 1500);
	
		numSpareCars = (maxCivCars - numCivCars) + 2;
		numSpots = numLanes / 2 - 1;

		numCarsToAdd = numSpots;

		if (numCarsToAdd > numSpareCars)
			numCarsToAdd = numSpareCars;

		count = 0;
		while (count < numCarsToAdd)
		{
			delta = ((numSpots * (count * 2 + 1)) / (numCarsToAdd * 2)) * 1024 + 768;

			currentPos.vx = px + FIXEDH(delta * RSIN(dir2NextRow));
			currentPos.vz = pz + FIXEDH(delta * RCOS(dir2NextRow));

			test42 = delta;

			newSlot = CreateStationaryCivCar(faceDir + (Random2(0) * 0x10001 >> (delta >> 9 & 0x1fU) & 0x3ffU) - 512, 0, 0, (LONGVECTOR4 *)&currentPos, externalCopModel, 0, 2);

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


// [D] [T]
int CivControl(CAR_DATA* cp)
{
	int thrust;
	int steer;
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

		steer = cp->wheel_angle;

		if (cp->ai.c.thrustState != 3)
			steer = CivSteerAngle(cp);

		// reduce acceleration when steering is applied
		thrust = CivAccel(cp) - MAX(ABS(steer), 4) * 3;

		if (thrust < 0 && cp->hd.wheel_speed < 5)
			thrust = 0;

		cp->wheel_angle = steer;
		cp->thrust = thrust;

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

				int straightX1 = straight->Midx + FIXED(distFromCentreA * RSIN(angle)) + FIXED(sideShift * RCOS(angle));
				int straightZ1 = (straight->Midz + FIXED(distFromCentreA * RCOS(angle))) - FIXED(sideShift * RSIN(angle));

				int straightX2 = straight->Midx + FIXED(distFromCentreB * RSIN(angle)) + FIXED(sideShift * RCOS(angle));
				int straightZ2 = (straight->Midz + FIXED(distFromCentreB * RCOS(angle))) - FIXED(sideShift * RSIN(angle));

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

						if (pn->pathType == 2)
						{
							ofs.vy = 1000;
						}

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