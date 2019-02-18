#include "../decomp_defs.h"

POLYCOORD polycoords[6] =
{
  { 0, 0, 640, 0, 256, 256 },
  { 256, 0, 768, 0, 256, 256 },
  { 512, 0, 896, 0, 128, 256 },
  { 0, 256, 640, 256, 256, 256 },
  { 256, 256, 768, 256, 256, 256 },
  { 512, 256, 896, 256, 128, 256 }
};

DRAW_MODE draw_mode_pal =
{ 0, 0, 0, 0, 512, 256, 0, 16 };

DRAW_MODE draw_mode_ntsc =
{ 0, 0, 0, 8, 512, 240, 0, 0 };

/*
 * Offset 0x442AC
 * D:\driver2\game\C\E3STUFF.C (line 171)
 * Stack frame base $sp, length 512
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ FadeInHiresScreen(char *filename /*stack 0*/)
{ // line 1, address 0x442ac
	struct DISPENV disp; // stack address -488
	struct DRAWENV draw; // stack address -464
	struct SPRT prims[6]; // stack address -368
	struct POLY_FT3 nulls[6]; // stack address -248
	struct RECT rect; // stack address -56
	unsigned long ot; // stack address -48
	int i; // $t5
	int col; // $s1
} // line 80, address 0x4465c
/*
 * Offset 0x4465C
 * D:\driver2\game\C\E3STUFF.C (line 258)
 * Stack frame base $sp, length 520
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ FadeOutHiresScreen()
{ // line 2, address 0x4465c
	struct DISPENV disp; // stack address -496
	struct DRAWENV draw; // stack address -472
	struct SPRT prims[6]; // stack address -376
	struct POLY_FT3 nulls[6]; // stack address -256
	struct RECT rect; // stack address -64
	unsigned long ot; // stack address -56
	int i; // $t5
	int col; // $s1
} // line 60, address 0x44934
/*
 * Offset 0x44934
 * D:\driver2\game\C\E3STUFF.C (line 391)
 * Stack frame base $sp, length 168
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ SetPleaseWait(char *buffer /*$s2*/)
{ // line 1, address 0x44934
	struct DISPENV disp; // stack address -144
	struct DRAWENV draw; // stack address -120
	struct RECT rect; // stack address -24
	char *exe; // $a0
} // line 44, address 0x44aa8
/*
 * Offset 0x44AA8
 * D:\driver2\game\C\E3STUFF.C (line 443)
 * Stack frame base $sp, length 184
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ CheckForCorrectDisc(int disc /*$s0*/)
{ // line 1, address 0x44aa8
	struct DISPENV disp; // stack address -160
	struct DRAWENV draw; // stack address -136
	struct RECT rect; // stack address -40
	char *mess1; // $s6
	char *mess2; // $s3
	char *exe; // $s4
	int ret; // $s0
	int discerror; // $s5
	{ // line 49, address 0x44bd8
	} // line 79, address 0x44c5c
} // line 95, address 0x44d20
/*
 * Offset 0x44D48
 * D:\driver2\game\C\E3STUFF.C (line 139)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ ShowHiresScreens(char **names /*$s1*/, int delay /*$s4*/, int wait /*$s3*/)
{ // line 1, address 0x44d48
	char *filename; // $a0
	int timedelay; // $s0
} // line 25, address 0x44e08
/*
 * Offset 0x44E08
 * D:\driver2\game\C\E3STUFF.C (line 350)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupDefDispEnv(struct DISPENV *env /*$s0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/)
{
}
/*
 * Offset 0x44EA8
 * D:\driver2\game\C\E3STUFF.C (line 325)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetupDefDrawEnv(struct DRAWENV *env /*$a0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/)
{
}