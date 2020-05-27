#include "THISDUST.H"
#include "FELONY.H"
#include "STRINGS.H"
#include "COP_AI.H"
#include "PLAYERS.H"
#include "CARS.H"
#include "MISSION.H"
#include "CONVERT.H"
#include "GAMESND.H"

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
	if (pFelonyData->occurrenceDelay[uVar6].current < (&pFelonyData->occurrenceDelay[uVar6].current)[1])
		return;

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

void CheckPlayerMiscFelonies(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	bool bVar2;
	uint uVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	uint uVar8;
	DRIVER2_JUNCTION *pDVar9;
	uint unaff_s1;
	uint uVar10;
	VECTOR *pos;
	DRIVER2_CURVE *cv;
	DRIVER2_STRAIGHT *pDVar11;

	cv = (DRIVER2_CURVE *)0x0;
	pDVar11 = (DRIVER2_STRAIGHT *)0x0;
	iVar7 = (int)player.playerCarId;
	pos = (VECTOR *)car_data[iVar7].hd.where.t;
	if (player.playerType == '\x02') {
		return;
	}
	if (iVar7 < 0) {
		return;
	}
	if (FelonyBar.active == 0) {
		return;
	}
	uVar3 = GetSurfaceIndex(pos);
	if ((((uVar3 & 0xffffe000) == 0x2000) && ((int)(uVar3 & 0x1fff) < NumDriver2Junctions)) &&
		(-1 < (int)uVar3)) {
		if (((((playerLastRoad & 0xe000U) == 0x4000) &&
			((int)((uint)(ushort)playerLastRoad & 0x1fff) < NumDriver2Curves)) ||
			(((playerLastRoad & 0xe000U) == 0 &&
			((int)((uint)(ushort)playerLastRoad & 0x1fff) < NumDriver2Straights)))) &&
				((-1 < playerLastRoad &&
			(pDVar9 = Driver2JunctionsPtr + (uVar3 - 0x2000), (pDVar9->flags & 1) != 0)))) {
			if (pDVar9->ExitIdx[0] == playerLastRoad) {
				uVar10 = 0;
			}
			else {
				uVar4 = 1;
				do {
					uVar8 = uVar4 & 0xff;
					uVar10 = unaff_s1;
					if (3 < uVar8) break;
					uVar4 = uVar8 + 1;
					uVar10 = uVar8;
				} while (pDVar9->ExitIdx[uVar8] != playerLastRoad);
			}
			if ((&junctionLightsPhase)[uVar10 & 1] == '\x01') {
				NoteFelony(&felonyData, '\x03', 0x1000);
			}
		}
	}
	playerLastRoad = (short)uVar3;
	bVar2 = false;
	if ((((uVar3 & 0xffffe000) == 0) && ((int)(uVar3 & 0x1fff) < NumDriver2Straights)) &&
		(-1 < (int)uVar3)) {
		pDVar11 = Driver2StraightsPtr + uVar3;
		uVar3 = (uint)(ushort)pDVar11->angle & 0xfff;
		uVar4 = (uint)(byte)pDVar11->NumLanes & 0xf;
		uVar3 = uVar4 - ((((pos->vx - pDVar11->Midx) * (int)rcossin_tbl[uVar3 * 2 + 1] -
			(car_data[iVar7].hd.where.t[2] - pDVar11->Midz) * (int)rcossin_tbl[uVar3 * 2])
			+ 0x800 >> 0xc) + 0x200 >> 9);
		iVar5 = uVar4 * 2;
		if ((int)uVar3 < 0) {
			uVar3 = 0;
		}
		if (iVar5 <= (int)uVar3) {
			uVar3 = iVar5 - 1;
		}
		if (((int)(uint)(byte)pDVar11->AILanes >> ((int)uVar3 / 2 & 0x1fU) & 1U) != 0) {
			uVar4 = ((int)pDVar11->angle - car_data[iVar7].hd.direction) + 0x400U >> 0xb & 1;
			if ((*(uint *)(pDVar11->ConnectIdx + 3) & 0xffff0000) != 0xff010000) {
				uVar3 = (int)(uint)(byte)pDVar11->LaneDirs >> ((int)uVar3 / 2 & 0x1fU);
			}
			if ((uVar3 & 1) == 0) {
				if (uVar4 == 1) {
					bVar2 = true;
				}
			}
			else {
				if (uVar4 == 0) {
					bVar2 = true;
				}
			}
		}
	}
	else {
		if ((((uVar3 & 0xffffe000) == 0x4000) && ((int)(uVar3 & 0x1fff) < NumDriver2Curves)) &&
			(-1 < (int)uVar3)) {
			cv = Driver2CurvesPtr + (uVar3 - 0x4000);
			iVar5 = pos->vx - cv->Midx;
			iVar6 = car_data[iVar7].hd.where.t[2] - cv->Midz;
			iVar5 = SquareRoot0(iVar5 * iVar5 + iVar6 * iVar6);
			if (iVar5 < 0) {
				iVar5 = iVar5 + 0x1ff;
			}
			uVar3 = (iVar5 >> 9) + (uint)(byte)cv->inside * -2;
			if ((int)uVar3 < 0) {
				uVar3 = 0;
			}
			iVar5 = ((uint)(byte)cv->NumLanes & 0xf) * 2;
			if (iVar5 <= (int)uVar3) {
				uVar3 = iVar5 - 1;
			}
			if (((int)(uint)(byte)cv->AILanes >> ((int)uVar3 / 2 & 0x1fU) & 1U) != 0) {
				iVar5 = NotTravellingAlongCurve
				(pos->vx, car_data[iVar7].hd.where.t[2], car_data[iVar7].hd.direction, cv);
				if (*(short *)&cv->NumLanes != -0xff) {
					uVar3 = (int)(uint)(byte)cv->LaneDirs >> ((int)uVar3 / 2 & 0x1fU);
				}
				if ((uVar3 & 1) == 0) {
					if (iVar5 != 0) {
						bVar2 = true;
					}
				}
				else {
					if (iVar5 == 0) {
						bVar2 = true;
					}
				}
			}
		}
	}
	if (bVar2) {
		felonyData.occurrenceDelay[8].current = felonyData.occurrenceDelay[8].current + 1;
	}
	else {
		felonyData.occurrenceDelay[8].current = 0;
	}
	NoteFelony(&felonyData, '\b', 0x1000);
	if (((gTimeOfDay == 3) && (1000 < car_data[iVar7].ap.damage[0])) &&
		(1000 < car_data[iVar7].ap.damage[1])) {
		NoteFelony(&felonyData, '\t', 0x1000);
	}
	if (car_data[iVar7].wheelspin == '\0') {
		iVar5 = car_data[iVar7].hd.rear_vel;
		if (iVar5 < 0) {
			iVar5 = -iVar5;
		}
		if (0x2b5c < iVar5) goto LAB_0004d180;
		felonyData.occurrenceDelay[10].current = 0;
	}
	else {
	LAB_0004d180:
		felonyData.occurrenceDelay[10].current = felonyData.occurrenceDelay[10].current + 1;
	}
	NoteFelony(&felonyData, '\n', 0x1000);
	if (pDVar11 == (DRIVER2_STRAIGHT *)0x0) {
		bVar1 = CHAR_8Ah_0009bf12;
		if (cv == (DRIVER2_CURVE *)0x0) goto LAB_0004d1ec;
		bVar1 = cv->NumLanes;
	}
	else {
		bVar1 = pDVar11->NumLanes;
	}
	bVar1 = speedLimits[(uint)(bVar1 >> 4) & 3];
LAB_0004d1ec:
	uVar3 = (uint)bVar1;
	if (uVar3 == (uint)(byte)CHAR_8Ah_0009bf12) {
		iVar5 = (int)(uVar3 * 0x13) >> 4;
	}
	else {
		iVar5 = (int)(uVar3 * 3) >> 1;
	}
	if (iVar5 < car_data[iVar7].hd.wheel_speed + 0x800 >> 0xc) {
		NoteFelony(&felonyData, '\x02', 0x1000);
	}
	return;*/
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





