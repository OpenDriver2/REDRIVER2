#include "driver2.h"
#include "ai.h"
#include "mission.h"
#include "cosmetic.h"
#include "cop_ai.h"
#include "cars.h"
#include "felony.h"
#include "glaunch.h"
#include "players.h"
#include "replays.h"

// [D] [T]
void StoreGameFlags(void)
{
	ReplayParameterPtr->weather = gWeather;
	ReplayParameterPtr->timeofday = gTimeOfDay;
}

// [D] [T]
int TannerCanEnterCar(CAR_DATA *cp, int distToCarSq)
{
	int carRange;

	if (cp->controlFlags & CONTROL_FLAG_COP) 
		gCopCarTheftAttempted = 1;

	if ((cp->controlType == CONTROL_TYPE_CIV_AI || cp->controlType == CONTROL_TYPE_CUTSCENE) && 
		(cp->controlFlags & CONTROL_FLAG_COP) == 0 && 
		(cp->controlFlags & CONTROL_FLAG_COP_SLEEPING) == 0 && 
		cp->hd.where.m[1][1] > 99)			// not flipped over
	{
		if (ABS(FIXEDH(cp->hd.wheel_speed)) < 3)
		{
			carRange = car_cosmetics[cp->ap.model].colBox.vx * 2;

			if (ActiveCheats.cheat13 != 0)
				carRange <<= 1;
			
			if (carRange > 5000)
				carRange = 5000;

			return (carRange*carRange < distToCarSq) ^ 1;
		}
	}

	return 0;
}

// [D] [T]
int TannerStuckInCar(int doSpeedCheck, int player_id)
{
	short *playerFelony;
	int speed;

	CAR_DATA *cp;
	PLAYER* lp;
	
	cp = NULL;
	lp = &player[player_id];

	if (lp->playerType == 1)
	{
		if (lp->playerCarId < 0)
		{
			playerFelony = &pedestrianFelony;
		}
		else 
		{
			cp = &car_data[lp->playerCarId];
			playerFelony = &cp->felonyRating;
		}

		if ((*playerFelony <= FELONY_MIN_VALUE || player_position_known < 1) &&
			cp &&
			(cp->hd.wheel[1].surface & 7) != 1 &&
			(cp->hd.wheel[3].surface & 7) != 1)
		{
			if (doSpeedCheck != 0)
			{
				speed = FIXEDH(cp->hd.wheel_speed);

				if (speed < 0)
					speed = -speed;

				if (speed > 2)
					return 1;
			}

			if (cp->hd.where.m[1][1] > 99 && lockAllTheDoors == 0)
			{
				return 0;
			}
		}
	}

	return 1;
}