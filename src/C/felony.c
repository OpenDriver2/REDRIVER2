#include "../decomp_defs.h"

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



/*
 * Offset 0x4C398
 * D:\driver2\game\C\FELONY.C (line 476)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ NoteFelony(struct FELONY_DATA *pFelonyData /*$a3*/, char type /*$s3*/, short scale /*$t0*/)
{ // line 1, address 0x4c398
	int felonyTooLowForRoadblocks; // $s4
	{ // line 2, address 0x4c410
		struct FELONY_DELAY *pFelonyDelay; // $v1
	} // line 19, address 0x4c434
	{ // line 36, address 0x4c468
		int additionalFelonyPoints; // $a0
	} // line 52, address 0x4c57c
	{ // line 77, address 0x4c698
		char rnd; // $s1
		int dir; // $a3
	} // line 107, address 0x4c86c
} // line 112, address 0x4c8fc
/*
 * Offset 0x4C91C
 * D:\driver2\game\C\FELONY.C (line 597)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ AdjustFelony(struct FELONY_DATA *pFelonyData /*$a0*/)
{ // line 1, address 0x4c91c
	{ // line 52, address 0x4cc50
		struct FELONY_DELAY *pFelonyDelay; // $v1
	} // line 61, address 0x4cc90
} // line 62, address 0x4cc90
/*
 * Offset 0x4CC90
 * D:\driver2\game\C\FELONY.C (line 668)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CheckPlayerMiscFelonies()
{ // line 2, address 0x4cc90
	struct FELONY_DATA *pFelonyData; // $s4
	struct DRIVER2_CURVE *cv; // $s5
	struct DRIVER2_STRAIGHT *st; // $s6
	struct _CAR_DATA *cp; // $s3
	struct VECTOR *carPos; // $s2
	int surfInd; // $s0
	{ // line 22, address 0x4cd28
		char i; // $a1
		{ // line 31, address 0x4cdcc
			struct DRIVER2_JUNCTION *jn; // $a2
			short exitId; // $s1
		} // line 47, address 0x4ce74
	} // line 48, address 0x4ce74
	{ // line 48, address 0x4ce74
		char goingWrongWay; // $s7
		int lane; // $s0
		int dx; // $v1
		int dz; // $a0
		{ // line 70, address 0x4d014
		} // line 80, address 0x4d140
	} // line 90, address 0x4d160
	{ // line 111, address 0x4d200
		int maxSpeed; // $a0
		int limit; // $v1
	} // line 137, address 0x4d2b8
} // line 138, address 0x4d2b8
/*
 * Offset 0x4D2E8
 * D:\driver2\game\C\FELONY.C (line 810)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitFelonySystem()
{
}
/*
 * Offset 0x4D320
 * D:\driver2\game\C\FELONY.C (line 824)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ CarHitByPlayer(struct _CAR_DATA *victim /*$a0*/, int howHard /*$a2*/)
{
}
/*
 * Offset 0x4D3CC
 * D:\driver2\game\C\FELONY.C (line 413)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitFelonyDelayArray(struct FELONY_DELAY *pFelonyDelay /*$a0*/, short *pMaximum /*$a1*/, int count /*$a2*/)
{ // line 1, address 0x4d3cc
	struct FELONY_DELAY *pCurrent; // $a0
} // line 9, address 0x4d408
/*
 * Offset 0x4D408
 * D:\driver2\game\C\FELONY.C (line 431)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ InitFelonyData(struct FELONY_DATA *pFelonyData /*$s0*/)
{ // line 1, address 0x4d408
	{ // line 1, address 0x4d408
		struct FELONY_VALUE *pSrc; // $v1
		struct FELONY_VALUE *pDest; // $s0
		struct FELONY_VALUE *pEnd; // $a0
	} // line 14, address 0x4d488
} // line 15, address 0x4d488
/*
 * Offset 0x4D488
 * D:\driver2\game\C\FELONY.C (line 450)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetCarHeading(int direction /*$a0*/)
{
}
/*
 * Offset 0x4D498
 * D:\driver2\game\C\FELONY.C (line 454)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
char /*$ra*/ GetCarDirectionOfTravel(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x4d498
	int direction; // $v0
} // line 12, address 0x4d4e0