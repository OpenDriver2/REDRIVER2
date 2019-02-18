#include "../decomp_defs.h"

/*
 * Offset 0x581D4
 * D:\driver2\game\C\LOADVIEW.C (line 200)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ShowLoading()
{ // line 2, address 0x581d4
	struct POLY_G4 poly; // stack address -56
	int col; // $s0
} // line 36, address 0x58300
/*
 * Offset 0x58314
 * D:\driver2\game\C\LOADVIEW.C (line 268)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ FadeGameScreen(int flag /*$t0*/, int speed /*$t1*/)
{ // line 1, address 0x58314
	static struct POLY_F4 poly; // address 0x0
	static struct POLY_FT4 p; // address 0x20
	int do_fade; // $v0
	{ // line 23, address 0x58354
		int val; // $a3
	} // line 42, address 0x58430
} // line 47, address 0x5845c
/*
 * Offset 0x5845C
 * D:\driver2\game\C\LOADVIEW.C (line 327)
 * Stack frame base $sp, length 288
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ ShowLoadingScreen(char *screen_name /*$fp*/, int effect /*$s7*/, int loading_steps /*$a2*/)
{ // line 1, address 0x5845c
	int fcount; // $s0
	int j; // $s2
	int done; // $fp
	struct RECT dest; // stack address -264
	struct SPRT prims[4]; // stack address -256
	struct POLY_FT3 nulls[4]; // stack address -176
	int fade; // $s5
	int fade_step; // stack address -48
} // line 142, address 0x587fc
/*
 * Offset 0x587FC
 * D:\driver2\game\C\LOADVIEW.C (line 527)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupFadePolys()
{ // line 3, address 0x587fc
	int i; // $a1
} // line 22, address 0x5888c
/*
 * Offset 0x5888C
 * D:\driver2\game\C\LOADVIEW.C (line 556)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DrawFadePoly()
{ // line 2, address 0x5888c
	struct POLY_G4 *fl_g4; // $a2
} // line 21, address 0x58a18
/*
 * Offset 0x58A18
 * D:\driver2\game\C\LOADVIEW.C (line 248)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupScreenFade(int start /*$a0*/, int end /*$a1*/, int speed /*$a2*/)
{
}
/*
 * Offset 0x58A38
 * D:\driver2\game\C\LOADVIEW.C (line 482)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ CloseShutters(int speed /*$s5*/, int width /*$s1*/, int height /*$s4*/)
{ // line 1, address 0x58a38
	struct POLY_F4 poly[2]; // stack address -80
	int h; // $s0
	int done; // $s2
} // line 31, address 0x58b70
/*
 * Offset 0x58B70
 * D:\driver2\game\C\LOADVIEW.C (line 585)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DisplayMissionTitle()
{ // line 2, address 0x58b70
	{ // line 17, address 0x58bf0
	} // line 21, address 0x58c20
} // line 37, address 0x58c70