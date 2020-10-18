#include "DRIVER2.H"
#include "AI.H"
#include "MISSION.H"
#include "COSMETIC.H"
#include "COP_AI.H"
#include "CARS.H"
#include "FELONY.H"
#include "PLAYERS.H"
#include "REPLAYS.H"

// decompiled code
// original method signature: 
// void /*$ra*/ StoreGameFlags()
 // line 275, offset 0x0001bbb8
	/* begin block 1 */
		// Start line: 615
	/* end block 1 */
	// End Line: 616

	/* begin block 2 */
		// Start line: 550
	/* end block 2 */
	// End Line: 551

	/* begin block 3 */
		// Start line: 616
	/* end block 3 */
	// End Line: 617

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void StoreGameFlags(void)
{
	ReplayParameterPtr->weather = gWeather;
	ReplayParameterPtr->timeofday = gTimeOfDay;
}



// decompiled code
// original method signature: 
// int /*$ra*/ TannerCanEnterCar(struct _CAR_DATA *cp /*$a0*/, int distToCarSq /*$a1*/)
 // line 297, offset 0x0001bbe8
	/* begin block 1 */
		// Start line: 298
		// Start offset: 0x0001BBE8

		/* begin block 1.1 */
			// Start line: 310
			// Start offset: 0x0001BC7C
			// Variables:
		// 		struct SVECTOR *carCollBox; // $v0
		// 		int carRange; // $a0
		/* end block 1.1 */
		// End offset: 0x0001BCCC
		// End Line: 317
	/* end block 1 */
	// End offset: 0x0001BCD4
	// End Line: 320

	/* begin block 2 */
		// Start line: 659
	/* end block 2 */
	// End Line: 660

	/* begin block 3 */
		// Start line: 660
	/* end block 3 */
	// End Line: 661

// [D] [T]
int TannerCanEnterCar(_CAR_DATA *cp, int distToCarSq)
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
			
			if (carRange > 5000)
				carRange = 5000;

			return (carRange*carRange < distToCarSq) ^ 1;
		}
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ TannerStuckInCar(int doSpeedCheck /*$a0*/)
 // line 324, offset 0x0001ba90
	/* begin block 1 */
		// Start line: 325
		// Start offset: 0x0001BA90
		// Variables:
	// 		struct _CAR_DATA *cp; // $a2
	/* end block 1 */
	// End offset: 0x0001BBB8
	// End Line: 341

	/* begin block 2 */
		// Start line: 648
	/* end block 2 */
	// End Line: 649

	/* begin block 3 */
		// Start line: 649
	/* end block 3 */
	// End Line: 650

// [D]
int TannerStuckInCar(int doSpeedCheck, int player_id)
{
	short *playerFelony;
	int speed;

	_CAR_DATA *cp;
	_PLAYER* lp;
	
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