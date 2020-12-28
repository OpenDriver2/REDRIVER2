#include "driver2.h"
#include "felony.h"
#include "cop_ai.h"
#include "civ_ai.h"

#include "players.h"
#include "cars.h"
#include "mission.h"
#include "convert.h"
#include "gamesnd.h"
#include "dr2roads.h"
#include "overlay.h"
#include "mission.h"

#include "ABS.H"
#include "STRINGS.H"

short initialOccurrenceDelay[12] = { 24, 0, 0, 0, 0, 0, 0, 0, 24, 0, 24, 0 };
short initialReccurrenceDelay[12] = { 128, 0, 128, 64, 64, 32, 32, 0, 128, 256 };

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


// [D] [T]
void InitFelonyDelayArray(FELONY_DELAY *pFelonyDelay, short *pMaximum, int count)
{
	FELONY_DELAY *pCurrent;

	pCurrent = pFelonyDelay + count;

	while (pFelonyDelay < pCurrent)
	{
		pFelonyDelay->current = 0;
		pFelonyDelay->maximum = *pMaximum++;

		pFelonyDelay++;
	}
}

// [D] [T]
void InitFelonyData(FELONY_DATA *pFelonyData)
{	
	InitFelonyDelayArray(pFelonyData->occurrenceDelay, initialOccurrenceDelay, numberOf(initialOccurrenceDelay));
	InitFelonyDelayArray(pFelonyData->reoccurrenceDelay, initialReccurrenceDelay, numberOf(initialOccurrenceDelay));

	memcpy(&pFelonyData->value, &initialFelonyValue, sizeof(initialFelonyValue));
}

// [D] [T]
int GetCarHeading(int direction)
{
	return (direction + 0x200U & 0xfff) >> 10;
}

// [D] [T]
char GetCarDirectionOfTravel(CAR_DATA *cp)
{
	int direction;

	direction = GetCarHeading(cp->hd.direction);;

	if (cp->hd.wheel_speed < 0) 
		direction = direction + 2 & 3;

	return direction;
}

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
		case 11:
			SetPlayerMessage(0, "Stealing cop car", 0, 1);
			break;
	}
#endif

	if (CopsCanSeePlayer == 0 && (type != 11))
		return;

	if (pFelonyData->reoccurrenceDelay[type].current != 0)
		return;

	pFelonyData->reoccurrenceDelay[type].current = pFelonyData->reoccurrenceDelay[type].maximum;

	if (*felony <= FELONY_MIN_VALUE)
		additionalFelonyPoints = pFelonyData->value[type].placid;
	else
		additionalFelonyPoints = pFelonyData->value[type].angry * pFelonyData->pursuitFelonyScale >> 0xc;

	*felony += (additionalFelonyPoints * scale >> 12);

	if (*felony > FELONY_MAX_VALUE) 
		*felony = FELONY_MAX_VALUE;

	// KILL PEDESTRIAN FELONY HERE
	if (player[0].playerType == 2)
		*felony = 0;

	if (first_offence == 0 && numActiveCops)
	{
		// say something..
		rnd = Random2(1);
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
				if ((rnd % 3) & 0xff != 0)
					break;

				CopSay((rnd & 1) + 7, 0);

				break;
			default:
				if ((rnd % 17) & 0xFF == 0)
				{
					if (MaxPlayerDamage[0] * 3 / 4 < car_data[player[0].playerCarId].totalDamage)
						phrase = rnd % 4;
					else
						phrase = rnd % 3;

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


// [D] [T]
void AdjustFelony(FELONY_DATA *pFelonyData)
{
	FELONY_DELAY *pFelonyDelay;
	short *felony;

	if (player[0].playerCarId < 0)
		felony = &pedestrianFelony;
	else
		felony = &car_data[player[0].playerCarId].felonyRating;

	if (*felony != 0 && *felony <= FELONY_MIN_VALUE)
	{
		if (FelonyDecreaseTimer++ == FelonyDecreaseTime)
		{
			(*felony)--;

			FelonyDecreaseTimer = 0;
		}
	}
	else if (CopsCanSeePlayer) 
	{
		if (*felony > FELONY_MIN_VALUE && FelonyIncreaseTimer++ == FelonyIncreaseTime)
		{
			(*felony)++;

			if (*felony > FELONY_MAX_VALUE)
				*felony = FELONY_MAX_VALUE;

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
	DRIVER2_ROAD_INFO roadInfo;
	DRIVER2_JUNCTION *jn;
	CAR_DATA* cp;

	// Do not register felony if player does not have a car
	if (player[0].playerType == 2 || 
		player[0].playerCarId < 0 || 
		FelonyBar.active == 0)
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
				NoteFelony(&felonyData, 3, 4096);
		}
	}

	playerLastRoad = surfInd;
	goingWrongWay = false;

	if(GetSurfaceRoadInfo(&roadInfo, surfInd))
	{
		int lane;
		int crd;

		lane = GetLaneByPositionOnRoad(&roadInfo, carPos);

		if(roadInfo.straight)
			crd = (roadInfo.straight->angle - cp->hd.direction) + 1024U >> 0xb & 1;
		else
			crd = NotTravellingAlongCurve(carPos->vx, carPos->vz, cp->hd.direction, roadInfo.curve);

		// check if on correct lane
		if (ROAD_IS_AI_LANE(&roadInfo, lane))
		{
			if (ROAD_LANE_DIR(&roadInfo, lane) == 0)
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
		printInfo("ROAD %d lane: %d / %d, (%d). AI drive: %d, flg: %d%d%d, dir: %d, spd: %d (wrong way: %d)\n",
			roadInfo.surfId,
			lane + 1,
			ROAD_WIDTH_IN_LANES(&roadInfo),					// lane count. * 2 for both sides as roads are symmetric
			IS_NARROW_ROAD(&roadInfo),
			ROAD_IS_AI_LANE(&roadInfo, lane),				// lane AI driveable flag
			(roadInfo.NumLanes & 0x20) > 0,					// flag 0 - first lane?
			(roadInfo.NumLanes & 0x40) > 0,					// flag 1 - leftmost park
			(roadInfo.NumLanes & 0x80) > 0,					// flag 2 - rightmost park
			ROAD_LANE_DIRECTION_BIT(&roadInfo, lane),		// direction bit
			ROAD_SPEED_LIMIT(&roadInfo),					// speed limit id
			goingWrongWay);
#endif

		// get road speed limit
		maxSpeed = speedLimits[ROAD_SPEED_LIMIT(&roadInfo)];
	}
	else
	{
		maxSpeed = speedLimits[2];
	}

	// wrong way
	if (goingWrongWay)
		felonyData.occurrenceDelay[8].current++;
	else
		felonyData.occurrenceDelay[8].current = 0;

	NoteFelony(&felonyData, 8, 4096);

	// if lights are off (broken)
	if (gTimeOfDay == 3 && cp->ap.damage[0] > 1000 && cp->ap.damage[1] > 1000)
		NoteFelony(&felonyData, 9, 4096);

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

	NoteFelony(&felonyData, 10, 4096);

	// check the speed limit
	if (speedLimits[2] == maxSpeed)
		limit = (maxSpeed * 19) >> 4;
	else 
		limit = (maxSpeed * 3) >> 1;

	if (FIXEDH(cp->hd.wheel_speed) > limit)
		NoteFelony(&felonyData, 2, 4096);
}

// [D] [T]
void InitFelonySystem(void)
{
	FelonyIncreaseTime = 31;
	FelonyDecreaseTime = 31;
	FelonyIncreaseTimer = 0;
	FelonyDecreaseTimer = 0;

	InitFelonyData(&felonyData);
}


// [D] [T]
void CarHitByPlayer(CAR_DATA *victim, int howHard)
{
	char type;

	if (howHard > 0 && victim->controlType != CONTROL_TYPE_PURSUER_AI) 
	{
		if ((victim->controlFlags & 1) == 0)
		{
			if (howHard < 32) 
			{
				NoteFelony(&felonyData, 4, (howHard << 0x17) >> 0x10);
				return;
			}
			
			type = 4;
		}
		else
		{
			if (howHard < 16)
			{
				NoteFelony(&felonyData, 5, (howHard << 0x18) >> 0x10);
				return;
			}
			
			type = 5;
		}

		NoteFelony(&felonyData, type, 4096);
	}
}





