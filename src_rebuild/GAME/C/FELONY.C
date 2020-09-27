#include "DRIVER2.H"
#include "FELONY.H"
#include "STRINGS.H"
#include "COP_AI.H"
#include "CIV_AI.H"

#include "PLAYERS.H"
#include "CARS.H"
#include "MISSION.H"
#include "CONVERT.H"
#include "GAMESND.H"
#include "DR2ROADS.H"
#include "OVERLAY.H"
#include "MISSION.H"

#include "ABS.H"

short initialOccurrenceDelay[12] = { 0x18, 0, 0, 0, 0, 0, 0, 0, 0x18, 0, 0x18, 0 };
short initialReccurrenceDelay[12] = { 0x80, 0, 0x80, 0x40, 0x40, 0x20, 0x20, 0, 0x80, 0x100 };

FELONY_VALUE initialFelonyValue[12] =
{
  { 659, 0 },
  { 659, 75 },
  { 659, 0 },
  { 659, 0 },
  { 659, 659 },
  { 1318, 659 },
  { 659, 659 },
  { 659, 25 },
  { 659, 0 },
  { 659, 0 },
  { 659, 0 },
  { 4096, 0 }
};

FELONY_DATA felonyData;

int FelonyIncreaseTime = 0;
int FelonyDecreaseTime = 0;

int FelonyIncreaseTimer = 0;
int FelonyDecreaseTimer = 0;


// decompiled code
// original method signature: 
// void /*$ra*/ InitFelonyDelayArray(struct FELONY_DELAY *pFelonyDelay /*$a0*/, short *pMaximum /*$a1*/, int count /*$a2*/)
 // line 413, offset 0x0004d364
	/* begin block 1 */
		// Start line: 414
		// Start offset: 0x0004D364
		// Variables:
	// 		struct FELONY_DELAY *pCurrent; // $a0
	/* end block 1 */
	// End offset: 0x0004D3A0
	// End Line: 422

	/* begin block 2 */
		// Start line: 826
	/* end block 2 */
	// End Line: 827

	/* begin block 3 */
		// Start line: 1334
	/* end block 3 */
	// End Line: 1335

// [D] [T]
void InitFelonyDelayArray(FELONY_DELAY *pFelonyDelay, short *pMaximum, int count)
{
	FELONY_DELAY *pCurrent;

	pCurrent = pFelonyDelay + count;

	if (pFelonyDelay < pCurrent)
	{
		do {
			pFelonyDelay->current = 0;
			pFelonyDelay->maximum = *pMaximum++;

			pFelonyDelay++;
		} while (pFelonyDelay < pCurrent);
	}
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitFelonyData(struct FELONY_DATA *pFelonyData /*$s0*/)
 // line 431, offset 0x0004d3a0
	/* begin block 1 */
		// Start line: 432
		// Start offset: 0x0004D3A0

		/* begin block 1.1 */
			// Start line: 432
			// Start offset: 0x0004D3A0
			// Variables:
		// 		struct FELONY_VALUE *pSrc; // $v1
		// 		struct FELONY_VALUE *pDest; // $s0
		// 		struct FELONY_VALUE *pEnd; // $a0
		/* end block 1.1 */
		// End offset: 0x0004D420
		// End Line: 445
	/* end block 1 */
	// End offset: 0x0004D420
	// End Line: 446

	/* begin block 2 */
		// Start line: 1363
	/* end block 2 */
	// End Line: 1364

	/* begin block 3 */
		// Start line: 1373
	/* end block 3 */
	// End Line: 1374

// [D] [T]
void InitFelonyData(FELONY_DATA *pFelonyData)
{
	InitFelonyDelayArray(pFelonyData->occurrenceDelay, initialOccurrenceDelay, 12);
	InitFelonyDelayArray(pFelonyData->reoccurrenceDelay, initialReccurrenceDelay, 12);

	memcpy(&pFelonyData->value, &initialFelonyValue, sizeof(initialFelonyValue));
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetCarHeading(int direction /*$a0*/)
 // line 450, offset 0x0004d420
	/* begin block 1 */
		// Start line: 1408
	/* end block 1 */
	// End Line: 1409

	/* begin block 2 */
		// Start line: 1409
	/* end block 2 */
	// End Line: 1410

	/* begin block 3 */
		// Start line: 1414
	/* end block 3 */
	// End Line: 1415

	/* begin block 4 */
		// Start line: 1415
	/* end block 4 */
	// End Line: 1416

// [D] [T]
int GetCarHeading(int direction)
{
	return (direction + 0x200U & 0xfff) >> 10;
}



// decompiled code
// original method signature: 
// char /*$ra*/ GetCarDirectionOfTravel(struct _CAR_DATA *cp /*$s0*/)
 // line 454, offset 0x0004d430
	/* begin block 1 */
		// Start line: 455
		// Start offset: 0x0004D430
		// Variables:
	// 		int direction; // $v0
	/* end block 1 */
	// End offset: 0x0004D478
	// End Line: 466

	/* begin block 2 */
		// Start line: 1422
	/* end block 2 */
	// End Line: 1423

// [D] [T]
char GetCarDirectionOfTravel(_CAR_DATA *cp)
{
	int direction;

	direction = GetCarHeading(cp->hd.direction);;

	if (cp->hd.wheel_speed < 0) 
		direction = direction + 2 & 3;

	return direction;
}



// decompiled code
// original method signature: 
// void /*$ra*/ NoteFelony(struct FELONY_DATA *pFelonyData /*$a3*/, char type /*$s3*/, short scale /*$t0*/)
 // line 476, offset 0x0004c330
	/* begin block 1 */
		// Start line: 477
		// Start offset: 0x0004C330
		// Variables:
	// 		int felonyTooLowForRoadblocks; // $s4

		/* begin block 1.1 */
			// Start line: 478
			// Start offset: 0x0004C3A8
			// Variables:
		// 		struct FELONY_DELAY *pFelonyDelay; // $v1
		/* end block 1.1 */
		// End offset: 0x0004C3CC
		// End Line: 495

		/* begin block 1.2 */
			// Start line: 512
			// Start offset: 0x0004C400
			// Variables:
		// 		int additionalFelonyPoints; // $a0
		/* end block 1.2 */
		// End offset: 0x0004C514
		// End Line: 528

		/* begin block 1.3 */
			// Start line: 553
			// Start offset: 0x0004C630
			// Variables:
		// 		char rnd; // $s1
		// 		int dir; // $a3
		/* end block 1.3 */
		// End offset: 0x0004C804
		// End Line: 583
	/* end block 1 */
	// End offset: 0x0004C894
	// End Line: 588

	/* begin block 2 */
		// Start line: 952
	/* end block 2 */
	// End Line: 953

// [D]
void NoteFelony(FELONY_DATA *pFelonyData, char type, short scale)
{
	int felonyTooLowForRoadblocks;
	char rnd; // $s1
	int dir; // $a3
	short *felony;
	int phrase;
	int additionalFelonyPoints;

	if (player[0].playerCarId < 0)
		felony = &pedestrianFelony;
	else
		felony = &car_data[player[0].playerCarId].felonyRating;

	felonyTooLowForRoadblocks = *felony;

	if (pFelonyData->occurrenceDelay[type].current < pFelonyData->occurrenceDelay[type].maximum)
		return;

#ifdef FELONY_DEBUG
	switch (type)
	{
		case 1:
			SetPlayerMessage(0, "Scaring pedestrians", 0, 1);
			break;
		case 2:
			SetPlayerMessage(0, "Speeding", 0, 1);
			break;
		case 3:
			SetPlayerMessage(0, "Red light crossing", 0, 1);
			break;
		case 4:
			SetPlayerMessage(0, "Collision with another vehicle", 0, 1);
			break;
		case 5:
			SetPlayerMessage(0, "Collision with cop", 0, 1);
			break;
		case 6:
			SetPlayerMessage(0, "Collision with building", 0, 1);
			break;
		case 7:
			SetPlayerMessage(0, "Damaging propery", 0, 1);
			break;
		case 8:
			SetPlayerMessage(0, "Wrong way", 0, 1);
			break;
		case 9:
			SetPlayerMessage(0, "Driving without lights", 0, 1);
			break;
		case 10:
			SetPlayerMessage(0, "Reckless driving", 0, 1);
			break;
	}
#endif

	if (CopsCanSeePlayer == 0 && (type != 11))
		return;

	if (pFelonyData->reoccurrenceDelay[type].current != 0)
		return;

	pFelonyData->reoccurrenceDelay[type].current = pFelonyData->reoccurrenceDelay[type].maximum;

	if (*felony < 0x293)
		additionalFelonyPoints = pFelonyData->value[type].placid;
	else
		additionalFelonyPoints = pFelonyData->value[type].angry * pFelonyData->pursuitFelonyScale >> 0xc;

	*felony += (additionalFelonyPoints * scale >> 12);

	if (player[0].playerCarId < 0)
		felony = &pedestrianFelony;
	else
		felony = &car_data[player[0].playerCarId].felonyRating;

	if (0x1000 < *felony) 
		*felony = 0x1000;

	// KILL PEDESTRIAN FELONY HERE
	if (player[0].playerType == 2)
		*felony = 0;

	if (first_offence == 0 && numActiveCops)
	{
		// say something..
		rnd = Random2(1) & 0xff;
		dir = GetCarDirectionOfTravel(&car_data[player[0].playerCarId]);

		switch (type)
		{
			case 1:
			case 5:
			case 6:
			case 7:
			case 11:
				break;
			case 3:
				if ((rnd & 3) != 0)
					break;

				CopSay(5, 0);
				break;
			case 4:
				if ((rnd - (((uint)((long long)rnd * 0xaaaaaaab >> 0x20) & 0xfffffffe) + rnd / 3) & 0xff) != 0)
					break;

				CopSay((rnd & 1) + 7, 0);

				break;
			default:
				if ((rnd - (((uint)((long long)rnd * 0xf0f0f0f1 >> 0x20) & 0xfffffff0) + rnd / 0x11) & 0xff) == 0)
				{
					if (MaxPlayerDamage[0] * 3 >> 2 < car_data[player[0].playerCarId].totalDamage)
						phrase = rnd & 3;
					else
						phrase = rnd - (((uint)((long long)rnd * 0xaaaaaaab >> 0x20) & 0xfffffffe) + rnd / 3) & 0xff;

					if (last_cop_phrase != phrase && 0 < TimeSinceLastSpeech)
					{
						if (phrase < 3)
							CopSay(phrase + 15, dir);
						else
							CopSay(6, 0);

						last_cop_phrase = phrase;
					}
				}
				break;
		}
	}

	if (felonyTooLowForRoadblocks < 0x527) 
	{
		if (*felony > 0x526)
		{
			roadblockCount = roadblockDelayDiff[gCopDifficultyLevel] + (Random2(0) & 0xff);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ AdjustFelony(struct FELONY_DATA *pFelonyData /*$a0*/)
 // line 597, offset 0x0004c8b4
	/* begin block 1 */
		// Start line: 598
		// Start offset: 0x0004C8B4

		/* begin block 1.1 */
			// Start line: 649
			// Start offset: 0x0004CBE8
			// Variables:
		// 		struct FELONY_DELAY *pFelonyDelay; // $v1
		/* end block 1.1 */
		// End offset: 0x0004CC28
		// End Line: 658
	/* end block 1 */
	// End offset: 0x0004CC28
	// End Line: 659

	/* begin block 2 */
		// Start line: 1231
	/* end block 2 */
	// End Line: 1232

	/* begin block 3 */
		// Start line: 1242
	/* end block 3 */
	// End Line: 1243

// [D] [T]
void AdjustFelony(FELONY_DATA *pFelonyData)
{
	bool bVar1;
	short *psVar2;
	FELONY_DELAY *pFelonyDelay;
	short *felony;

	if (player[0].playerCarId < 0)
		felony = &pedestrianFelony;
	else
		felony = &car_data[player[0].playerCarId].felonyRating;

	if (*felony != 0 && *felony < 0x293)
	{
		if (FelonyDecreaseTimer++ == FelonyDecreaseTime)
		{
			*felony--;

			FelonyDecreaseTimer = 0;
		}
	}
	else if (CopsCanSeePlayer) 
	{
		if (*felony > 0x292 && FelonyIncreaseTimer++ == FelonyIncreaseTime)
		{
			*felony++;

			if (*felony > 0x1000)
				*felony = 0x1000;

			FelonyIncreaseTimer = 0;
		}
	}

	pFelonyDelay = pFelonyData->reoccurrenceDelay;

	while (pFelonyDelay <= &pFelonyData->reoccurrenceDelay[11]) 
	{
		if (pFelonyDelay->current != 0)
			pFelonyDelay->current--;

		pFelonyDelay++;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckPlayerMiscFelonies()
 // line 668, offset 0x0004cc28
	/* begin block 1 */
		// Start line: 670
		// Start offset: 0x0004CC28
		// Variables:
	// 		struct FELONY_DATA *pFelonyData; // $s4
	// 		struct DRIVER2_CURVE *cv; // $s5
	// 		struct DRIVER2_STRAIGHT *st; // $s6
	// 		struct _CAR_DATA *cp; // $s3
	// 		struct VECTOR *carPos; // $s2
	// 		int surfInd; // $s0

		/* begin block 1.1 */
			// Start line: 690
			// Start offset: 0x0004CCC0
			// Variables:
		// 		char i; // $a1

			/* begin block 1.1.1 */
				// Start line: 699
				// Start offset: 0x0004CD64
				// Variables:
			// 		struct DRIVER2_JUNCTION *jn; // $a2
			// 		short exitId; // $s1
			/* end block 1.1.1 */
			// End offset: 0x0004CE0C
			// End Line: 715
		/* end block 1.1 */
		// End offset: 0x0004CE0C
		// End Line: 716

		/* begin block 1.2 */
			// Start line: 716
			// Start offset: 0x0004CE0C
			// Variables:
		// 		char goingWrongWay; // $s7
		// 		int lane; // $s0
		// 		int dx; // $v1
		// 		int dz; // $a0

			/* begin block 1.2.1 */
				// Start line: 738
				// Start offset: 0x0004CFAC
			/* end block 1.2.1 */
			// End offset: 0x0004D0D8
			// End Line: 748
		/* end block 1.2 */
		// End offset: 0x0004D0F8
		// End Line: 758

		/* begin block 1.3 */
			// Start line: 779
			// Start offset: 0x0004D198
			// Variables:
		// 		int maxSpeed; // $a0
		// 		int limit; // $v1
		/* end block 1.3 */
		// End offset: 0x0004D250
		// End Line: 805
	/* end block 1 */
	// End offset: 0x0004D250
	// End Line: 806

	/* begin block 2 */
		// Start line: 1367
	/* end block 2 */
	// End Line: 1368

	/* begin block 3 */
		// Start line: 1368
	/* end block 3 */
	// End Line: 1369

	/* begin block 4 */
		// Start line: 1378
	/* end block 4 */
	// End Line: 1379

	/* begin block 5 */
		// Start line: 1379
	/* end block 5 */
	// End Line: 1380

	/* begin block 6 */
		// Start line: 1380
	/* end block 6 */
	// End Line: 1381

/* WARNING: Removing unreachable block (ram,0x0004d214) */
/* WARNING: Unknown calling convention yet parameter storage is locked */

short playerLastRoad = 0;

// [D] [T]
void CheckPlayerMiscFelonies(void)
{
	int i;
	bool goingWrongWay;
	int surfInd;
	int maxSpeed;
	int limit;
	int exitId;
	int _exitId;
	VECTOR *carPos;
	DRIVER2_CURVE *cv;
	DRIVER2_STRAIGHT *st;
	DRIVER2_JUNCTION *jn;
	_CAR_DATA* cp;

	cv = NULL;
	st = NULL;

	if (player[0].playerType == 2 || player[0].playerCarId < 0 || FelonyBar.active == 0)
		return;

	cp = &car_data[player[0].playerCarId];
	carPos = (VECTOR *)cp->hd.where.t;

	surfInd = GetSurfaceIndex(carPos);

	// check junctions
	if (IS_JUNCTION_SURFACE(surfInd))
	{
		jn = GET_JUNCTION(surfInd);

		if(	(IS_CURVED_SURFACE(playerLastRoad) || IS_STRAIGHT_SURFACE(playerLastRoad)) && (jn->flags & 0x1))
		{
			exitId = 0;
			i = 0;
			while (i < 4)
			{
				if (jn->ExitIdx[i] == playerLastRoad)
				{
					exitId = i;
					break;
				}
				i++;
			}

			// Run a red light!
			if (junctionLightsPhase[exitId & 1] == 1)
				NoteFelony(&felonyData, 3, 0x1000);
		}
	}

	playerLastRoad = surfInd;
	goingWrongWay = false;

	// straight or curve
	if (IS_STRAIGHT_SURFACE(surfInd))
	{
		int lane_count;
		int lane; // $s0
		int dx; // $v1
		int dz; // $a0

		st = GET_STRAIGHT(surfInd);

		dx = carPos->vx - st->Midx;
		dz = carPos->vz - st->Midz;

		lane = ROAD_LANES_COUNT(st) - (FIXEDH(dx * rcossin_tbl[(st->angle & 0xfff) * 2 + 1] - dz * rcossin_tbl[(st->angle & 0xfff) * 2]) + 512 >> 9);

		lane_count = ROAD_WIDTH_IN_LANES(st);

		if (lane < 0)
			lane = 0;
	
		if (lane_count <= lane)
			lane = lane_count - 1;
	
		// check if on correct lane
		if (ROAD_IS_AI_LANE(st, lane))
		{
			int crd;
			crd = (st->angle - cp->hd.direction) + 0x400U >> 0xb & 1;

			if (ROAD_LANE_DIR(st, lane) == 0)
			{
				if (crd == 1)
					goingWrongWay = true;
			}
			else
			{
				if (crd == 0)
					goingWrongWay = true;
			}
		}

#if 0
		printInfo("str lane: %d / %d (%d). AI drive: %d, flg: %d%d, dir: %d, spd: %d (wrong way: %d)\n",
			lane + 1,
			((u_char)st->NumLanes & 0xF) * 2,			// lane count. * 2 for both sides as roads are symmetric
			IS_NARROW_ROAD(st),
			((u_char)st->AILanes >> (lane / 2) & 1U),	// lane AI driveable flag
			(st->NumLanes & 0x40) > 0,					// flag 1 - parking allowed?
			(st->NumLanes & 0x80) > 0,					// flag 2 - spawning allowed?
			((u_char)st->LaneDirs >> (lane / 2) & 1U),	// direction bit
			((u_char)st->NumLanes >> 4) & 3,			// speed limit id
			goingWrongWay);
#endif
	}
	else if(IS_CURVED_SURFACE(surfInd))
	{
		int lane_count;
		int lane; // $s0
		int dx; // $v1
		int dz; // $a0

		cv = GET_CURVE(surfInd);
		dx = carPos->vx - cv->Midx;
		dz = carPos->vz - cv->Midz;

		lane = (SquareRoot0(dx * dx + dz * dz) >> 9) - cv->inside * 2;
		if (lane < 0)
			lane = 0;

		lane_count = ROAD_WIDTH_IN_LANES(cv);

		if (lane >= lane_count)
			lane = lane_count - 1;

		// check if on correct lane
		if (ROAD_IS_AI_LANE(cv, lane))
		{
			int crd;

			crd = NotTravellingAlongCurve(carPos->vx, carPos->vz, cp->hd.direction, cv);

			if (ROAD_LANE_DIR(cv, lane) == 0)
			{
				if (crd != 0)
					goingWrongWay = true;
			}
			else
			{
				if (crd == 0)
					goingWrongWay = true;
			}
		}

#if 0
		printInfo("crv lane: %d / %d, (%d). AI drive: %d, flg: %d%d, dir: %d, spd: %d (wrong way: %d)\n",
			lane + 1,
			((u_char)cv->NumLanes & 0xF) * 2,			// lane count. * 2 for both sides as roads are symmetric
			IS_NARROW_ROAD(cv),
			((u_char)cv->AILanes >> (lane / 2) & 1U),	// lane AI driveable flag
			(cv->NumLanes & 0x40) > 0,					// flag 1 - parking allowed?
			(cv->NumLanes & 0x80) > 0,					// flag 2 - spawning allowed?
			((u_char)cv->LaneDirs >> (lane / 2) & 1U),	// direction bit
			((u_char)cv->NumLanes >> 4) & 3,			// speed limit id
			goingWrongWay);
#endif
	}

	// wrong way
	if (goingWrongWay)
		felonyData.occurrenceDelay[8].current++;
	else
		felonyData.occurrenceDelay[8].current = 0;

	NoteFelony(&felonyData, 8, 0x1000);

	// if lights are off (broken)
	if (gTimeOfDay == 3 && cp->ap.damage[0] > 1000 && cp->ap.damage[1] > 1000)
		NoteFelony(&felonyData, 9, 0x1000);

	// reckless driving.
	// for that checking if rear wheels are sliding
	if (cp->wheelspin == 0)
	{
		if (ABS(cp->hd.rear_vel) > 11100)
			felonyData.occurrenceDelay[10].current++;
		else
			felonyData.occurrenceDelay[10].current = 0;
	}
	else
	{
		felonyData.occurrenceDelay[10].current++;
	}

	NoteFelony(&felonyData, 10, 0x1000);

	// check the speed limit
	if (st != NULL)
		maxSpeed = speedLimits[ROAD_SPEED_LIMIT(st)];
	else if (cv != NULL)
		maxSpeed = speedLimits[ROAD_SPEED_LIMIT(cv)];
	else
		maxSpeed = speedLimits[2];

	if (speedLimits[2] == maxSpeed)
		limit = (maxSpeed * 19) >> 4;
	else 
		limit = (maxSpeed * 3) >> 1;

	if (FIXEDH(cp->hd.wheel_speed) > limit)
		NoteFelony(&felonyData, 2, 0x1000);
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitFelonySystem()
 // line 810, offset 0x0004d280
	/* begin block 1 */
		// Start line: 1682
	/* end block 1 */
	// End Line: 1683

	/* begin block 2 */
		// Start line: 1687
	/* end block 2 */
	// End Line: 1688

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitFelonySystem(void)
{
	FelonyIncreaseTime = 31;
	FelonyDecreaseTime = 31;
	FelonyIncreaseTimer = 0;
	FelonyDecreaseTimer = 0;

	InitFelonyData(&felonyData);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CarHitByPlayer(struct _CAR_DATA *victim /*$a0*/, int howHard /*$a2*/)
 // line 824, offset 0x0004d2b8
	/* begin block 1 */
		// Start line: 1714
	/* end block 1 */
	// End Line: 1715

// [D] [T]
void CarHitByPlayer(_CAR_DATA *victim, int howHard)
{
	char type;

	if ((0 < howHard) && (victim->controlType != CONTROL_TYPE_PURSUER_AI)) 
	{
		if ((victim->controlFlags & 1) == 0)
		{
			if (howHard < 0x20) 
			{
				NoteFelony(&felonyData, 4, (howHard << 0x17) >> 0x10);
				return;
			}
			type = 4;
		}
		else
		{
			if (howHard < 0x10)
			{
				NoteFelony(&felonyData, 5, (howHard << 0x18) >> 0x10);
				return;
			}
			type = 5;
		}

		NoteFelony(&felonyData, type, 0x1000);
	}
}





