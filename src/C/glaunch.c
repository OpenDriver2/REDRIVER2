
#include "../decomp_defs.h"

MISSION_STEP MissionLadder[68] =
{
  { 1, 0, 1, 0 },
  { 1, 0, 2, 0 },
  { 2, 0, 1, 0 },
  { 2, 1, 2, 0 },
  { 2, 1, 3, 0 },
  { 1, 1, 3, 0 },
  { 1, 1, 4, 0 },
  { 2, 1, 4, 0 },
  { 1, 2, 5, 0 },
  { 2, 2, 5, 0 },
  { 1, 3, 6, 0 },
  { 2, 3, 6, 0 },
  { 1, 4, 7, 0 },
  { 2, 5, 7, 0 },
  { 6, 5, 0, 0 },
  { 2, 5, 9, 0 },
  { 1, 5, 8, 0 },
  { 1, 5, 9, 0 },
  { 2, 6, 10, 0 },
  { 1, 6, 10, 0 },
  { 1, 6, 11, 0 },
  { 2, 7, 11, 0 },
  { 6, 7, 0, 0 },
  { 2, 7, 13, 0 },
  { 2, 7, 14, 0 },
  { 1, 7, 12, 0 },
  { 2, 8, 15, 0 },
  { 2, 8, 16, 0 },
  { 1, 8, 13, 0 },
  { 2, 9, 17, 0 },
  { 2, 9, 18, 0 },
  { 1, 9, 14, 0 },
  { 2, 10, 19, 0 },
  { 1, 10, 15, 0 },
  { 2, 11, 20, 0 },
  { 1, 12, 16, 1 },
  { 1, 12, 17, 1 },
  { 2, 13, 21, 1 },
  { 2, 13, 22, 1 },
  { 2, 13, 23, 1 },
  { 2, 13, 24, 1 },
  { 1, 13, 18, 1 },
  { 2, 14, 25, 1 },
  { 2, 14, 26, 1 },
  { 1, 14, 19, 1 },
  { 2, 15, 27, 1 },
  { 2, 15, 28, 1 },
  { 2, 15, 29, 1 },
  { 2, 15, 30, 1 },
  { 1, 15, 20, 1 },
  { 1, 15, 21, 1 },
  { 2, 16, 31, 1 },
  { 2, 16, 32, 1 },
  { 2, 16, 33, 1 },
  { 2, 16, 34, 1 },
  { 1, 16, 22, 1 },
  { 2, 17, 35, 1 },
  { 6, 17, 0, 1 },
  { 2, 17, 37, 1 },
  { 1, 17, 23, 1 },
  { 2, 18, 38, 1 },
  { 2, 18, 39, 1 },
  { 1, 18, 24, 1 },
  { 2, 19, 40, 1 },
  { 1, 19, 25, 1 },
  { 1, 19, 26, 1 },
  { 1, 19, 27, 1 },
  { 4, 19, 28, 1 }
};

unsigned short RecapFrameLength[19] = {
	0x203, 0x2FC, 0x3C2, 0x496, 0x56D, 0x616, 0x6D4, 0x70E, 0x800, 0x8CD, 0x99A, 0x430, 0x550, 0x5E3, 0x67B, 0x96D, 0xA17, 0xAC9, 0xBB6
};

/*
 * Offset 0x52A90
 * D:\driver2\game\C\GLAUNCH.C (line 834)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ GameStart()
{ // line 2, address 0x52a90
	struct RECT rect; // stack address -16
	int oldVMode; // $s0
	int SurvivalCopSettingsBackup; // $s0
} // line 177, address 0x52f00
/*
 * Offset 0x52F00
 * D:\driver2\game\C\GLAUNCH.C (line 1030)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ReInitFrontend()
{ // line 2, address 0x52f00
	struct RECT rect; // stack address -24
} // line 73, address 0x53050
/*
 * Offset 0x53050
 * D:\driver2\game\C\GLAUNCH.C (line 1105)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ RunMissionLadder(int newgame /*$a1*/)
{ // line 1, address 0x53050
	struct MISSION_STEP *CurrentStep; // $s0
	struct RENDER_ARGS RenderArgs; // stack address -48
	int quit; // $s3
	{ // line 38, address 0x5310c
	} // line 38, address 0x5310c
	{ // line 43, address 0x5311c
	} // line 44, address 0x53124
	{ // line 48, address 0x53134
	} // line 52, address 0x53150
	{ // line 58, address 0x5319c
		{ // line 67, address 0x53200
		} // line 70, address 0x53214
	} // line 107, address 0x532f4
} // line 110, address 0x53320
/*
 * Offset 0x53320
 * D:\driver2\game\C\GLAUNCH.C (line 1279)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ LaunchGame()
{ // line 2, address 0x53320
	struct RECT rect; // stack address -16
	int quit; // $s0
} // line 136, address 0x53640
/*
 * Offset 0x53640
 * D:\driver2\game\C\GLAUNCH.C (line 1222)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ GetRandomChase()
{ // line 2, address 0x53640
	int bump; // $s1
} // line 28, address 0x53704
/*
 * Offset 0x53718
 * D:\driver2\game\C\GLAUNCH.C (line 1018)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ StartRender(int renderNum /*$a0*/)
{
}
/*
 * Offset 0x53740
 * D:\driver2\game\C\GLAUNCH.C (line 1252)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ FindPrevMissionFromLadderPos(int pos /*$a0*/)
{ // line 2, address 0x53740
} // line 16, address 0x537a8
/*
 * Offset 0x537A8
 * D:\driver2\game\C\GLAUNCH.C (line 1417)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ FindMissionLadderPos(int mission /*$a0*/)
{ // line 1, address 0x537a8
	struct MISSION_STEP *step; // $a1
	int pos; // $a2
} // line 40, address 0x5387c