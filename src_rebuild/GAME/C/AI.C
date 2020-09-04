#include "THISDUST.H"
#include "AI.H"
#include "MISSION.H"
#include "COSMETIC.H"
#include "COP_AI.H"
#include "CARS.H"
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
	int speed;
	int carRange;

	if ((cp->controlFlags & 1) != 0) 
		gCopCarTheftAttempted = 1;


	if ((cp->controlType == 2 || cp->controlType == 7) && 
		(cp->controlFlags & 1) == 0 && 
		(cp->controlFlags & 2) == 0 && 
		cp->hd.where.m[1][1] > 99)			// not flipped over
	{
		speed = FIXED(cp->hd.wheel_speed);

		if (speed < 0)
			speed = -speed;

		if (speed < 3)
		{
			carRange = car_cosmetics[cp->ap.model].colBox.vx * 2;
			carRange *= carRange;

			if (5000 < carRange)
				carRange = 25000000;

			return (carRange < distToCarSq) ^ 1;
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
	short *psVar1;
	int speed;
	int iVar3;

	_CAR_DATA *cp;
	_PLAYER* lp;
	
	cp = NULL;
	lp = &player[player_id];

	if (lp->playerType == 1)
	{
		if (lp->playerCarId < 0)
		{
			psVar1 = &pedestrianFelony;
		}
		else 
		{
			cp = &car_data[lp->playerCarId];
			psVar1 = &cp->felonyRating;
		}

		if ((*psVar1 < 0x293 || player_position_known < 1) &&
			cp &&
			(cp->hd.wheel[1].surface & 7) != 1 &&
			(cp->hd.wheel[3].surface & 7) != 1)
		{
			if (doSpeedCheck != 0)
			{
				speed = FIXED(cp->hd.wheel_speed);

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