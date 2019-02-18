
#include "../decomp_defs.h"

/*
 * Offset 0x1C096C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1205)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetVariable(int var /*$a0*/)
{ // line 1, address 0x1c096c
	int code; // $v1
	int value; // $a2
} // line 157, address 0x1c0c14
/*
 * Offset 0x1C0C14
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1371)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ LoadFrontendScreens()
{ // line 2, address 0x1c0c14
	int iTpage; // $s0
	int iNumScreens; // $t6
	int i; // $t0
	int j; // $a3
	struct RECT rect; // stack address -40
	char *ptr; // $a2
} // line 83, address 0x1c0f1c
/*
 * Offset 0x1C0F1C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1461)
 * Stack frame base $sp, length 88
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ LoadBackgroundFile(char *name /*$s4*/)
{ // line 1, address 0x1c0f1c
	int iTpage; // $s2
	struct RECT rect; // stack address -72
	int p; // $s0
	int pages[7]; // stack address -64
} // line 48, address 0x1c10ec
/*
 * Offset 0x1C10EC
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1516)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupBackgroundPolys()
{ // line 2, address 0x1c10ec
	int i; // $v1
	int tpage; // $t3
} // line 64, address 0x1c1324
/*
 * Offset 0x1C1324
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1588)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupScreenSprts(struct PSXSCREEN *pScr /*$a0*/)
{ // line 1, address 0x1c1324
	int tpage; // $a1
	struct POLY_FT3 *null; // $v0
} // line 62, address 0x1c1474
/*
 * Offset 0x1C1474
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1658)
 * Stack frame base $sp, length 120
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawScreen(struct PSXSCREEN *pScr /*stack 0*/)
{ // line 1, address 0x1c1474
	int i; // $s1
	char version_info[32]; // stack address -88
	int numBtnsToDraw; // stack address -56
} // line 102, address 0x1c18ac
/*
 * Offset 0x1C18DC
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1769)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DisplayOnScreenText()
{ // line 2, address 0x1c18dc
	int i; // $s0
	char text[32]; // stack address -64
	{ // line 26, address 0x1c19d4
		{ // line 28, address 0x1c19dc
		} // line 29, address 0x1c19e4
	} // line 30, address 0x1c19e4
	{ // line 38, address 0x1c1a44
		int extraVal; // $t1
	} // line 41, address 0x1c1aa4
} // line 78, address 0x1c1ac8
/*
 * Offset 0x1C1AC8
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1855)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ SetupExtraPoly(char *fileName /*$s5*/, int address /*$s1*/, int offset2 /*$s0*/)
{ // line 1, address 0x1c1ac8
	int i; // $s0
	int tpage; // $v1
	struct RECT rect; // stack address -40
} // line 61, address 0x1c1cec
/*
 * Offset 0x1C1CEC
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1941)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ReInitScreens()
{
}
/*
 * Offset 0x1C1E10
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1991)
 * Stack frame base $sp, length 80
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ NewSelection(short dir /*$s3*/)
{ // line 1, address 0x1c1e10
	struct RECT rect; // stack address -48
	struct PSXBUTTON *pNewB; // $s2
} // line 94, address 0x1c2274
/*
 * Offset 0x1C22A0
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2093)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ HandleKeyPress()
{ // line 2, address 0x1c22a0
	{ // line 19, address 0x1c2338
		int action; // $s0
		{ // line 48, address 0x1c2444
		} // line 73, address 0x1c2508
	} // line 93, address 0x1c255c
} // line 139, address 0x1c2660
/*
 * Offset 0x1C2660
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2300)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ PadChecks()
{ // line 2, address 0x1c2660
	int i; // $a2
	int oldnum; // $s2
} // line 117, address 0x1c2964
/*
 * Offset 0x1C2964
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2423)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DoFrontEnd()
{ // line 2, address 0x1c2964
	static unsigned char result[8]; // address 0x0
} // line 165, address 0x1c2c24
/*
 * Offset 0x1C2C24
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2630)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ SetFEDrawMode()
{ // line 2, address 0x1c2c24
	struct DRAW_MODE *dm; // $s3
} // line 57, address 0x1c2d88
/*
 * Offset 0x1C2D88
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2745)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: s0 s1 s2 s3 s4
 */
int /*$ra*/ FEPrintString(char *string /*$t1*/, int x /*$t2*/, int y /*$s4*/, int justification /*$a3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/)
{ // line 1, address 0x1c2d88
	struct FE_CHARDATA *pFontInfo; // $a0
	struct SPRT *font; // $t0
	unsigned char let; // $a0
	int counter; // $t4
	{ // line 1, address 0x1c2de4
		char *pString; // $a1
		{ // line 1, address 0x1c2de4
			char let; // $v1
			int w; // $a2
		} // line 1, address 0x1c2e30
	} // line 1, address 0x1c2e30
	{ // line 47, address 0x1c2f20
		int tpage; // $v1
	} // line 47, address 0x1c2f20
} // line 64, address 0x1c2fd0
/*
 * Offset 0x1C2FD0
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2817)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: s0 s1 s2 s3 s4
 */
int /*$ra*/ FEPrintStringSized(char *string /*$t2*/, int x /*$t1*/, int y /*$t7*/, int scale /*$a3*/, int transparent /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, address 0x1c2fd0
	struct POLY_FT4 *font; // $t0
	struct FE_CHARDATA *pFontInfo; // $a2
	char let; // $v1
	int tpage; // $v0
	int w; // $t3
	int h; // $t4
} // line 63, address 0x1c31f4
/*
 * Offset 0x1C31F4
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2894)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ CentreScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C3428
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3029)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ CarSelectScreen(int bSetup /*$a0*/)
{ // line 2, address 0x1c3428
	int i; // $a0
	struct RECT rect; // stack address -32
	{ // line 116, address 0x1c3734
		int lastVal; // $a3
		{ // line 1, address 0x1c37b4
			{ // line 1, address 0x1c37b4
				struct RECT rect; // stack address -24
			} // line 1, address 0x1c37b4
		} // line 1, address 0x1c37b4
	} // line 1, address 0x1c37b4
	{ // line 135, address 0x1c37c8
		int lastVal; // $a3
		{ // line 1, address 0x1c3850
			{ // line 1, address 0x1c3850
				struct RECT rect; // stack address -24
			} // line 1, address 0x1c3850
		} // line 1, address 0x1c3850
	} // line 1, address 0x1c3850
} // line 183, address 0x1c3a58
/*
 * Offset 0x1C3A58
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3256)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ VibroOnOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C3B14
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3394)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ MissionSelectScreen(int bSetup /*$a0*/)
{ // line 2, address 0x1c3b14
	int i; // $a1
	{ // line 29, address 0x1c3bd4
		int usedB; // $s2
		int done; // $t0
		int bP; // $a3
		int bN; // $s5
		int shift; // $a3
	} // line 158, address 0x1c40d0
} // line 231, address 0x1c4330
/*
 * Offset 0x1C4330
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3632)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
int /*$ra*/ MissionCityScreen(int bSetup /*$a0*/)
{ // line 6, address 0x1c4330
	{ // line 71, address 0x1c4494
		{ // line 71, address 0x1c4494
			struct RECT rect; // stack address -16
		} // line 71, address 0x1c4494
	} // line 71, address 0x1c4494
	{ // line 77, address 0x1c44bc
		{ // line 77, address 0x1c44bc
			struct RECT rect; // stack address -16
		} // line 77, address 0x1c44bc
	} // line 77, address 0x1c44bc
} // line 88, address 0x1c45f8
/*
 * Offset 0x1C45F8
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3728)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: ra
 */
int /*$ra*/ CutSceneSelectScreen(int bSetup /*$a0*/)
{ // line 2, address 0x1c45f8
	struct RENDER_ARGS renderArgs; // stack address -48
	int extraVal; // $a0
	struct RECT rect; // stack address -24
	{ // line 61, address 0x1c4790
		{ // line 61, address 0x1c4790
			struct RECT rect; // stack address -16
		} // line 61, address 0x1c4790
	} // line 61, address 0x1c4790
	{ // line 1, address 0x1c483c
		int address; // $a1
		{ // line 1, address 0x1c483c
			struct RECT rect; // stack address -16
		} // line 1, address 0x1c483c
	} // line 1, address 0x1c483c
	{ // line 80, address 0x1c48f8
		{ // line 80, address 0x1c48f8
			struct RECT rect; // stack address -16
		} // line 80, address 0x1c48f8
	} // line 80, address 0x1c48f8
	{ // line 85, address 0x1c4938
		{ // line 85, address 0x1c4938
			struct RECT rect; // stack address -16
		} // line 85, address 0x1c4938
	} // line 85, address 0x1c4938
} // line 119, address 0x1c4b28
/*
 * Offset 0x1C4B28
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3855)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: ra
 */
int /*$ra*/ CutSceneCitySelectScreen(int bSetup /*$a0*/)
{ // line 2, address 0x1c4b28
	struct RECT rect; // stack address -24
	{ // line 1, address 0x1c4e64
		{ // line 1, address 0x1c4e64
			struct RECT rect; // stack address -16
		} // line 1, address 0x1c4e64
	} // line 1, address 0x1c4e64
	{ // line 1, address 0x1c4e64
		{ // line 1, address 0x1c4e64
			struct RECT rect; // stack address -16
		} // line 1, address 0x1c4e64
	} // line 1, address 0x1c4e64
	{ // line 1, address 0x1c4eac
		{ // line 1, address 0x1c4eac
			struct RECT rect; // stack address -16
		} // line 1, address 0x1c4eac
	} // line 1, address 0x1c4eac
	{ // line 1, address 0x1c4fa4
		{ // line 1, address 0x1c4fa4
			struct RECT rect; // stack address -16
		} // line 1, address 0x1c5098
	} // line 1, address 0x1c5098
} // line 140, address 0x1c50a8
/*
 * Offset 0x1C50A8
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4005)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ SetVolumeScreen(int bSetup /*$a0*/)
{ // line 2, address 0x1c50a8
	int last; // $s2
	char text[4]; // stack address -48
	int ypos[2]; // stack address -40
	struct RECT rect; // stack address -32
	{ // line 43, address 0x1c524c
		{ // line 43, address 0x1c524c
			struct DB *db_hold; // $a1
		} // line 43, address 0x1c524c
	} // line 43, address 0x1c524c
	{ // line 65, address 0x1c527c
		{ // line 65, address 0x1c527c
			struct DB *db_hold; // $a1
		} // line 65, address 0x1c527c
	} // line 65, address 0x1c527c
	{ // line 92, address 0x1c52c4
		{ // line 92, address 0x1c52c4
			struct DB *db_hold; // $a1
		} // line 92, address 0x1c52c4
	} // line 92, address 0x1c52c4
	{ // line 114, address 0x1c5418
		{ // line 114, address 0x1c5418
			struct DB *db_hold; // $a1
		} // line 117, address 0x1c5528
	} // line 117, address 0x1c5528
} // line 143, address 0x1c55f0
/*
 * Offset 0x1C55F0
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4165)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DisplayScoreTable()
{ // line 2, address 0x1c55f0
	int address; // $a2
	int i; // $s4
	char text[32]; // stack address -80
	struct SCORE_ENTRY *pSE; // stack address -48
	int min; // $v1
	int frac; // $t0
} // line 56, address 0x1c5998
/*
 * Offset 0x1C5998
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4227)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ ScoreScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C5B44
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4434)
 * Stack frame base $sp, length 120
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CheatScreen(int bSetup /*$a0*/)
{ // line 2, address 0x1c5b44
	int numOpen; // $s5
	int i; // $s1
	int k; // $s6
	int *uc; // $s2
	unsigned char cheatOn[12]; // stack address -104
	int hackLookup1[4]; // stack address -88
	int hackLookup2[4]; // stack address -72
	{ // line 39, address 0x1c5c64
		int evilRuss[4]; // stack address -56
	} // line 126, address 0x1c6064
} // line 134, address 0x1c6098
/*
 * Offset 0x1C6098
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4642)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ GameNameScreen(int bSetup /*$a0*/)
{ // line 2, address 0x1c6098
	int address; // $s3
} // line 14, address 0x1c61a4
/*
 * Offset 0x1C61A4
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4671)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ FEInitCdIcon()
{ // line 2, address 0x1c61a4
	int i; // $a0
	struct RECT dest; // stack address -24
	unsigned short *palette; // $a2
} // line 38, address 0x1c62f0
/*
 * Offset 0x1C62F0
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4716)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ FEDrawCDicon()
{ // line 2, address 0x1c62f0
	unsigned short *palette; // $a1
	int temp; // $a2
	int i; // $a0
	struct RECT dest; // stack address -16
} // line 19, address 0x1c6370
/*
 * Offset 0x1C6370
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2695)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ EndFrame()
{ // line 2, address 0x1c6370
	struct DB *db_hold; // $a1
} // line 21, address 0x1c63fc
/*
 * Offset 0x1C63FC
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3220)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ CopDiffLevelScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C64A8
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4322)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ SubtitlesOnOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C64F4
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4345)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ CityCutOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C6540
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4378)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ ControllerScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C660C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4412)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ MainScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C664C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4575)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ ImmunityOnOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C6698
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4597)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ InvincibleOnOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C66E4
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4619)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GamePlayScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C671C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4742)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ CheatNumlayerSelect(int bSetup /*$a0*/)
{
}