#include "THISDUST.H"
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

// [D]
void InitFelonyDelayArray(FELONY_DELAY *pFelonyDelay, short *pMaximum, int count)
{
	FELONY_DELAY *pFVar1;

	pFVar1 = pFelonyDelay + count;

	if (pFelonyDelay < pFVar1)
	{
		do {
			pFelonyDelay->current = 0;
			pFelonyDelay->maximum = *pMaximum++;

			pFelonyDelay++;
		} while (pFelonyDelay < pFVar1);
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

// [D]
void InitFelonyData(FELONY_DATA *pFelonyData)
{
	FELONY_VALUE *pFVar1;
	FELONY_VALUE *pFVar2;

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

// [D]
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

// [D]
char GetCarDirectionOfTravel(_CAR_DATA *cp)
{
	unsigned char bVar1;
	int iVar2;

	iVar2 = GetCarHeading((cp->hd).direction);
	bVar1 = iVar2;

	if (cp->hd.wheel_speed < 0) 
		bVar1 = bVar1 + 2 & 3;

	return (char)bVar1;
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
	short sVar1;
	char cVar2;
	uint uVar4;
	short *felony;
	uint uVar6;
	int phrase;
	uint uVar7;

	uVar6 = type;
	if (player[0].playerCarId < 0)
		felony = &pedestrianFelony;
	else
		felony = &car_data[player[0].playerCarId].felonyRating;

	sVar1 = *felony;
	if (pFelonyData->occurrenceDelay[uVar6].current < pFelonyData->occurrenceDelay[uVar6].maximum)
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

	if (pFelonyData->reoccurrenceDelay[uVar6].current != 0) 
		return;

	pFelonyData->reoccurrenceDelay[uVar6].current = pFelonyData->reoccurrenceDelay[uVar6].maximum;

	if (*felony < 0x293)
		phrase = (pFelonyData->occurrenceDelay + uVar6)[0x18].current;
	else
		phrase = (pFelonyData->occurrenceDelay + uVar6)[0x18].maximum * pFelonyData->pursuitFelonyScale >> 0xc;

	*felony += (phrase * scale >> 0xc);

	if (player[0].playerCarId < 0)
		felony = &pedestrianFelony;
	else
		felony = &car_data[player[0].playerCarId].felonyRating;

	if (0x1000 < *felony) 
		*felony = 0x1000;

	// KILL PEDESTRIA FELONY HERE
	if (player[0].playerType == 2)
		*felony = 0;

	if (numActiveCops == 0) 
		goto switchD_0004c6a8_caseD_1;

	uVar4 = Random2(1);
	uVar7 = uVar4 & 0xff;
	cVar2 = GetCarDirectionOfTravel(&car_data[player[0].playerCarId]);

	if (first_offence != 0)
		goto switchD_0004c6a8_caseD_1;

	switch (uVar6) 
	{
		case 1:
		case 5:
		case 6:
		case 7:
		case 0xb:
			goto switchD_0004c6a8_caseD_1;
		default:
			if ((uVar7 - (((uint)((long long)uVar7 * 0xf0f0f0f1 >> 0x20) & 0xfffffff0) + uVar7 / 0x11) & 0xff) == 0) 
			{
				phrase = MaxPlayerDamage[0] * 3;

				if (phrase >> 2 < car_data[player[0].playerCarId].totalDamage)
					uVar4 = uVar4 & 3;
				else 
					uVar4 = uVar7 - (((uint)((long long)uVar7 * 0xaaaaaaab >> 0x20) & 0xfffffffe) + uVar7 / 3) & 0xff;

				if (last_cop_phrase != uVar4 && 0 < TimeSinceLastSpeech) 
				{
					if (uVar4 < 3)
						CopSay(uVar4 + 0xf, cVar2);
					else
						CopSay(6, 0);

					last_cop_phrase = uVar4;
				}
			}
			goto switchD_0004c6a8_caseD_1;
		case 3:
			phrase = 5;

			if ((uVar4 & 3) != 0) 
				goto switchD_0004c6a8_caseD_1;

			break;
		case 4:
			if ((uVar7 - (((uint)((long long)uVar7 * 0xaaaaaaab >> 0x20) & 0xfffffffe) + uVar7 / 3) & 0xff) != 0) 
				goto switchD_0004c6a8_caseD_1;

			phrase = (uVar4 & 1) + 7;
	}
	CopSay(phrase, 0);
switchD_0004c6a8_caseD_1:

	if (sVar1 < 0x527)
	{
		if (0x526 < *felony) 
		{
			uVar6 = Random2(0);
			roadblockCount = roadblockDelayDiff[gCopDifficultyLevel] + (uVar6 & 0xff);
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

// [D]
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

// [D]
void CheckPlayerMiscFelonies(void)
{
	unsigned char bVar1;
	long lVar3;
	int uVar4;
	int iVar5;
	int uVar6;
	int iVar7;
	int iVar8;

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
	if (IS_JUNCTION_SURFACE(surfInd)) // (((surfInd & 0xffffe000U) == 0x2000) && ((int)(surfInd & 0x1fffU) < NumDriver2Junctions)) && (-1 < surfInd))
	{
		jn = GET_JUNCTION(surfInd);

		//if (((((playerLastRoad & 0xe000U) == 0x4000) && ((int)((uint)(ushort)playerLastRoad & 0x1fff) < NumDriver2Curves)) || 
		//	(((playerLastRoad & 0xe000U) == 0 && ((int)((uint)(ushort)playerLastRoad & 0x1fff) < NumDriver2Straights)))) &&
		//	((-1 < playerLastRoad && (jn = Driver2JunctionsPtr + surfInd + -0x2000, (jn->flags & 1) != 0)))) 
		if(	(IS_CURVED_SURFACE(playerLastRoad) || IS_STRAIGHT_SURFACE(playerLastRoad)) && (jn->flags & 0x1))
		{
			if (jn->ExitIdx[0] == playerLastRoad) 
			{
				_exitId = 0;
			}
			else 
			{
				uVar6 = 1;
				do {
					uVar4 = uVar6 & 0xff;
					_exitId = exitId;

					if (3 < uVar4)
						break;

					uVar6 = uVar4 + 1;
					_exitId = uVar4;
				} while (jn->ExitIdx[uVar4] != playerLastRoad);
			}

			if (junctionLightsPhase[_exitId & 1] == 1) 
			{
				NoteFelony(&felonyData, 3, 0x1000);
			}
		}
	}

	playerLastRoad = surfInd;
	goingWrongWay = false;

	// straight or curve
	if (IS_STRAIGHT_SURFACE(surfInd)) //(((surfInd & 0xffffe000U) == 0) && ((int)(surfInd & 0x1fffU) < NumDriver2Straights)) && (-1 < surfInd)) 
	{
		st = GET_STRAIGHT(surfInd); // Driver2StraightsPtr + surfInd;
		uVar6 = st->angle & 0xfff;
		uVar4 = st->NumLanes & 0xf;
		uVar6 = uVar4 - (FIXED((carPos->vx - st->Midx) * rcossin_tbl[uVar6 * 2 + 1] - (carPos->vz - st->Midz) * rcossin_tbl[uVar6 * 2]) + 0x200 >> 9);
		iVar5 = uVar4 * 2;

		if (uVar6 < 0)
			uVar6 = 0;
	
		if (iVar5 <= uVar6)
			uVar6 = iVar5 - 1;
	
		if ((st->AILanes >> (uVar6 / 2 & 0x1fU) & 1U) != 0) 
		{
			uVar4 = (st->angle - cp->hd.direction) + 0x400U >> 0xb & 1;

			if ((*(uint *)(st->ConnectIdx + 3) & 0xffff0000) != 0xff010000) 
			{
				uVar6 = st->LaneDirs >> (uVar6 / 2 & 0x1fU);
			}

			if ((uVar6 & 1) == 0) 
			{
				if (uVar4 == 1)
				{
					goingWrongWay = true;
				}
			}
			else if (uVar4 == 0)
				goingWrongWay = true;
		}
	}
	else if(IS_CURVED_SURFACE(surfInd)) //(((surfInd & 0xffffe000U) == 0x4000) && ((int)(surfInd & 0x1fffU) < NumDriver2Curves)) && (-1 < surfInd))
	{
		cv = GET_CURVE(surfInd); // Driver2CurvesPtr + surfInd + -0x4000;
		iVar5 = carPos->vx - cv->Midx;
		iVar7 = carPos->vz - cv->Midz;
		lVar3 = SquareRoot0(iVar5 * iVar5 + iVar7 * iVar7);

		uVar6 = (lVar3 >> 9) - cv->inside * 2;
		if (uVar6 < 0)
			uVar6 = 0;

		iVar5 = (cv->NumLanes & 0xf) * 2;

		if (iVar5 <= uVar6)
			uVar6 = iVar5 - 1;

		if ((cv->AILanes >> (uVar6 / 2 & 0x1fU) & 1U) != 0)
		{
			if (*(short *)&cv->NumLanes != -0xff)
				uVar6 = cv->LaneDirs >> (uVar6 / 2 & 0x1fU);

			if ((uVar6 & 1) == 0)
			{
				if (NotTravellingAlongCurve(carPos->vx, carPos->vz, cp->hd.direction, cv))
					goingWrongWay = true;
			}
			else if (iVar5 == 0)
			{
				goingWrongWay = true;
			}
		}
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
		maxSpeed = speedLimits[(st->NumLanes >> 4) & 3];
	else if (cv != NULL)
		maxSpeed = speedLimits[(cv->NumLanes >> 4) & 3];
	else
		maxSpeed = speedLimits[2];

	if (speedLimits[2] == maxSpeed)
		limit = (maxSpeed * 19) >> 4;
	else 
		limit = (maxSpeed * 3) >> 1;

	if (FIXED(cp->hd.wheel_speed) > limit)
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

// [D]
void InitFelonySystem(void)
{
	FelonyIncreaseTime = 0x1f;
	FelonyDecreaseTime = 0x1f;
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

// [D]
void CarHitByPlayer(_CAR_DATA *victim, int howHard)
{
	char type;

	if ((0 < howHard) && (victim->controlType != 3)) 
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





