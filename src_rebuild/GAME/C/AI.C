#include "THISDUST.H"
#include "AI.H"
#include "MISSION.H"
#include "COSMETIC.H"
#include "COP_AI.H"
#include "CARS.H"
#include "PLAYERS.H"

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

void StoreGameFlags(void)
{
	UNIMPLEMENTED();
	/*
	ReplayParameterPtr->weather = (uchar)gWeather;
	ReplayParameterPtr->timeofday = (uchar)gTimeOfDay;
	return;*/
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

// [D]
int TannerCanEnterCar(_CAR_DATA *cp, int distToCarSq)
{
	int iVar1;
	int iVar2;

	if ((cp->controlFlags & 1) != 0) 
		gCopCarTheftAttempted = 1;


	if ((cp->controlType == 2 || cp->controlType == 7) && 
		(cp->controlFlags & 1) == 0 && 
		(cp->controlFlags & 2) == 0 && 
		cp->hd.where.m[1][1] > 99)			// not flipped over
	{
		iVar1 = cp->hd.wheel_speed / 4096;

		if (iVar1 < 0) 
			iVar1 = -iVar1;

		if (iVar1 < 3)
		{
			iVar1 = car_cosmetics[cp->ap.model].colBox.vx * 2;
			iVar2 = iVar1 * iVar1;

			if (5000 < iVar1)
				iVar2 = 25000000;

			return (uint)(iVar2 < distToCarSq) ^ 1;
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

int TannerStuckInCar(int doSpeedCheck)
{
	short *psVar1;
	int iVar2;
	int iVar3;

	_CAR_DATA *cp;

	if (NumPlayers < 2 && player[0].playerType == 1)
	{
		if (player[0].playerCarId < 0)
		{
			psVar1 = &pedestrianFelony;
		}
		else 
		{
			cp = &car_data[player[0].playerCarId];
			psVar1 = &cp->felonyRating;
		}

		if ((*psVar1 < 0x293 || player_position_known < 1) &&
			(cp->hd.wheel[1].surface & 7) != 1 &&
			(cp->hd.wheel[3].surface & 7) != 1)
		{
			if (doSpeedCheck != 0)
			{
				iVar2 = cp->hd.wheel_speed / 4096;

				if (iVar2 < 0)
					iVar2 = -iVar2;

				if (2 < iVar2)
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





