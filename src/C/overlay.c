#include "../decomp_defs.h"

COLOUR_BAND felonyColour[3] =
{
  { { 0u, 0u, 255u, 0u }, 0, 0 },
  { { 255u, 0u, 0u, 0u }, 659, 0 },
  { { 0u, 0u, 255u, 0u }, 4096, 2 }
};

COLOUR_BAND playerDamageColour[3] =
{
  { { 0u, 255u, 0u, 0u }, 0, 0 },
  { { 255u, 0u, 0u, 0u }, 3686, 0 },
  { { 0u, 0u, 0u, 0u }, 4096, 2 }
};

COLOUR_BAND damageColour[2] =
{ { { 0u, 255u, 0u, 0u }, 0, 0 }, { { 255u, 0u, 0u, 0u }, 4096, 0 } };




/*
 * Offset 0x14AC0
 * D:\driver2\game\C\OVERLAY.C (line 270)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ InitOverlays()
{
}
/*
 * Offset 0x14CA4
 * D:\driver2\game\C\OVERLAY.C (line 329)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DisplayOverlays()
{
}
/*
 * Offset 0x14E10
 * D:\driver2\game\C\OVERLAY.C (line 426)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawPercentageBar(struct _PERCENTAGE_BAR *bar /*$fp*/)
{ // line 1, address 0x14e10
	struct POLY_G4 *poly; // $s0
	struct CVECTOR temp; // stack address -56
	int min_x; // $s1
	int max_x; // $s7
	int min_y; // $s2
	int max_y; // stack address -48
	char *tag; // $s0
	{ // line 94, address 0x152b0
		short tagX; // $s1
		short tagY; // $s2
	} // line 102, address 0x1530c
} // line 104, address 0x1533c
/*
 * Offset 0x1533C
 * D:\driver2\game\C\OVERLAY.C (line 532)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawProximityBar(struct _PERCENTAGE_BAR *bar /*$t3*/)
{ // line 1, address 0x1533c
	struct TILE *tile; // $a1
	int min_x; // $s1
	int max_x; // $s7
	int min_y; // $s2
	int max_y; // $fp
	short total; // $v1
	char *tag; // $s0
	{ // line 87, address 0x157c8
		short tagX; // $s1
		short tagY; // $s2
	} // line 95, address 0x1582c
} // line 97, address 0x1585c
/*
 * Offset 0x1585C
 * D:\driver2\game\C\OVERLAY.C (line 707)
 * Stack frame base $sp, length 80
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DrawDrivingGameOverlays()
{ // line 2, address 0x1585c
	struct SCORE_ENTRY *table; // $s1
	char string[32]; // stack address -64
	int i; // $s1
	int x; // $s3
	int y; // $s2
	{ // line 11, address 0x158c4
		{ // line 25, address 0x1593c
		} // line 25, address 0x1593c
		{ // line 50, address 0x15a4c
		} // line 63, address 0x15b10
	} // line 136, address 0x15eb4
} // line 137, address 0x15ed8
/*
 * Offset 0x15ED8
 * D:\driver2\game\C\OVERLAY.C (line 378)
 * Stack frame base $sp, length 128
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetFullscreenDrawing()
{ // line 2, address 0x15ed8
	struct DRAWENV drawenv; // stack address -104
	struct DR_ENV *dr_env; // $s0
} // line 10, address 0x15f88
/*
 * Offset 0x15F88
 * D:\driver2\game\C\OVERLAY.C (line 395)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitPercentageBar(struct _PERCENTAGE_BAR *bar /*$a0*/, int length /*$a1*/, struct COLOUR_BAND *pColourBand /*$a2*/, char *tag /*$a3*/)
{
}
/*
 * Offset 0x15FC0
 * D:\driver2\game\C\OVERLAY.C (line 414)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ EnablePercentageBar(struct _PERCENTAGE_BAR *bar /*$a0*/, int max /*$a1*/)
{
}
/*
 * Offset 0x15FD4
 * D:\driver2\game\C\OVERLAY.C (line 631)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetColourByValue(struct COLOUR_BAND *pColourBand /*$a3*/, int value /*$a1*/, struct CVECTOR *pOut /*$t0*/)
{ // line 1, address 0x15fd4
	struct COLOUR_BAND *pPrevColourBand; // $a2
	int scale; // $a0
	int temp; // $a1
} // line 30, address 0x16100
/*
 * Offset 0x16100
 * D:\driver2\game\C\OVERLAY.C (line 669)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ TransparencyOn(void *potz /*$a0*/, unsigned short tpage /*$a1*/)
{ // line 1, address 0x16100
	struct DR_TPAGE *null; // $a2
} // line 7, address 0x1617c
/*
 * Offset 0x1617C
 * D:\driver2\game\C\OVERLAY.C (line 687)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ UpdateFlashValue()
{ // line 2, address 0x1617c
	char length; // $v1
} // line 13, address 0x161ec
/*
 * Offset 0x161EC
 * D:\driver2\game\C\OVERLAY.C (line 846)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ PrintScoreTableTime(int x /*$s0*/, int y /*$s1*/, int time /*$a0*/)
{ // line 1, address 0x161ec
	char string[32]; // stack address -48
	int min; // $t0
	int frac; // $v1
} // line 15, address 0x162e8