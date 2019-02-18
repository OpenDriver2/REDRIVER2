#include "../decomp_defs.h"

REPLAY_ICON replay_icons[23] =
{
  { 20, 26, &dir_pause, "Pause", 20, 48 },
  { 20, 26, &playpause, "Resume", 20, 48 },
  { 44, 26, &autocam, "Auto director", 44, 48 },
  { 68, 26, &playcam, "Play camera", 68, 48 },
  { 92, 26, &frameadv, "Single frame", 92, 48 },
  { 116, 26, &restart, "Rewind", 116, 48 },
  { 140, 26, &addcam, "Add camera", 140, 48 },
  { 164, 26, &editcam, "Edit camera", 164, 48 },
  { 188, 26, &save2card, "Save replay", 188, 48 },
  { 212, 26, &ok, "OK", 212, 48 },
  { 140, 50, &incar, "Inside car", 164, 48 },
  { 140, 74, &chasecar, "Chase camera", 164, 72 },
  { 140, 98, &fixedcam, "Fixed camera", 164, 96 },
  { 140, 122, &ok, "Accept", 164, 120 },
  { 140, 122, &clock, "Move camera start", 164, 120 },
  { 140, 146, &delcam, "Delete camera", 164, 144 },
  { 140, 170, &ok, "Accept", 164, 168 },
  { 164, 50, &choosecar, "Choose target vehicle", 164, 72 },
  { 164, 74, &movecampos, "Move camera position", 164, 96 },
  { 164, 98, &movecampos, "Move camera position", 164, 120 },
  { 188, 98, &lookcar, "Look at target", 188, 120 },
  { 212, 98, &movecam, "Move camera", 212, 120 },
  { 236, 98, &lenschan, "Lens zoom", 236, 120 }
};

char menu0[] = { 0, 0xFF };

char menu1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xFF };

char menu2[] = { 0xA, 0xB, 0xC, 0xD, 0xFF };

char menu3[] = { 0x11, 0xFF };

char menu4[] = { 0x12, 0xFF };

char menu5[] = { 0x13, 0x14, 0x15, 0x16, 0xFF };

char menu6[] = { 0xA, 0xB, 0xC, 0xE, 0xF, 0x10, 0xFF };

/*
 * Offset 0x3B34C
 * D:\driver2\game\C\DIRECTOR.C (line 513)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ EditCamera(int CameraCnt /*$a0*/)
{ // line 2, address 0x3b34c
	int count; // $t0
	{ // line 30, address 0x3b47c
		int prev; // $a2
		int next; // $v1
	} // line 57, address 0x3b584
} // line 59, address 0x3b5b0
/*
 * Offset 0x3B5B0
 * D:\driver2\game\C\DIRECTOR.C (line 574)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ RecordCamera(int CameraCnt /*$s0*/)
{ // line 1, address 0x3b5b0
	struct PLAYBACKCAMERA *TempChange; // $a1
} // line 58, address 0x3b7fc
/*
 * Offset 0x3B7FC
 * D:\driver2\game\C\DIRECTOR.C (line 658)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ CheckCameraChange(int CameraCnt /*$s0*/)
{
}
/*
 * Offset 0x3B930
 * D:\driver2\game\C\DIRECTOR.C (line 731)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ IsMovingCamera(struct PLAYBACKCAMERA *lastcam /*$t3*/, struct PLAYBACKCAMERA *nextcam /*$t0*/, int cameracnt /*$a2*/)
{ // line 1, address 0x3b930
	struct PLAYBACKCAMERA cam; // stack address -56
	long xdist; // $t5
	long ydist; // $t6
	long zdist; // $t4
	long xangle; // $a3
	long yangle; // $t1
	long zangle; // $t2
	int s; // $a0
	int e; // $v1
	int f; // $t8
	int t; // $a2
	int nextcview; // $a0
} // line 61, address 0x3bc10
/*
 * Offset 0x3BC10
 * D:\driver2\game\C\DIRECTOR.C (line 794)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 fp
 */
void /*$ra*/ CameraBar(int CameraCnt /*stack 0*/)
{ // line 1, address 0x3bc10
	struct POLY_G4 *camera; // $a2
	struct LINE_F2 *bar; // $t2
	int x; // $a2
	int min_x; // $t1
	int max_x; // $t0
	int min_y; // $s3
	char red; // $s0
	char green; // $s4
	char blue; // $fp
	int bar_x; // $s1
	int first; // stack address -48
	int last; // $s7
	unsigned long idx; // $t9
} // line 133, address 0x3c1ec
/*
 * Offset 0x3C218
 * D:\driver2\game\C\DIRECTOR.C (line 966)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ ShowIcons(char *menu /*$s3*/, int selected /*stack 4*/, int x_offset /*$s7*/)
{ // line 1, address 0x3c218
	static int FlashCnt; // address 0x0
	struct REPLAY_ICON *IconPtr; // $s0
	struct SPRT *icon; // $a2
	int count; // $s6
	{ // line 61, address 0x3c3a8
		struct TEXTURE_DETAILS *Icon_texture; // $s1
		int min_x; // $v1
		int min_y; // $a0
		{ // line 69, address 0x3c3cc
		} // line 71, address 0x3c3ec
		{ // line 82, address 0x3c44c
			int ramp; // $a0
		} // line 93, address 0x3c4b0
	} // line 100, address 0x3c4d8
} // line 130, address 0x3c624
/*
 * Offset 0x3C624
 * D:\driver2\game\C\DIRECTOR.C (line 1135)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ ShowReplayMenu()
{ // line 2, address 0x3c624
	{ // line 4, address 0x3c64c
	} // line 8, address 0x3c670
	{ // line 12, address 0x3c688
	} // line 16, address 0x3c6a4
	{ // line 43, address 0x3c7b8
		int strobe; // $v0
	} // line 47, address 0x3c800
} // line 49, address 0x3c810
/*
 * Offset 0x3C810
 * D:\driver2\game\C\DIRECTOR.C (line 1186)
 * Stack frame base $sp, length 120
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ ControlReplay()
{ // line 2, address 0x3c810
	static int debounce; // address 0x60
	static int first_time; // address 0x64
	int move; // $s0
	{ // line 85, address 0x3ca68
		int speed; // $s2
		{ // line 95, address 0x3cad0
		} // line 99, address 0x3caf4
		{ // line 102, address 0x3cb0c
			int prev; // $v1
		} // line 105, address 0x3cb44
		{ // line 141, address 0x3cc9c
			struct ROUTE_DATA routeData; // stack address -96
			int road_height; // $s1
		} // line 152, address 0x3cd18
		{ // line 161, address 0x3cd24
			struct VECTOR old_camera; // stack address -88
			int x; // $s5
			int z; // $s4
			int d; // $s3
			int angle; // $s1
			char cameraCar; // $a0
			int dx; // $s1
			int dz; // $s0
			struct VECTOR basePos; // stack address -72
			struct VECTOR tmpPos; // stack address -56
			{ // line 186, address 0x3cda0
				struct _EVENT *event; // $a1
			} // line 190, address 0x3cdd0
			{ // line 224, address 0x3cecc
				int temp; // $v0
			} // line 228, address 0x3ced8
			{ // line 245, address 0x3cf90
			} // line 264, address 0x3cfdc
			{ // line 268, address 0x3cfdc
				struct ROUTE_DATA routeData; // stack address -40
				int road_height; // $s1
			} // line 289, address 0x3d0cc
		} // line 291, address 0x3d0f0
	} // line 320, address 0x3d230
	{ // line 374, address 0x3d574
		{ // line 496, address 0x3d870
		} // line 496, address 0x3d870
		{ // line 605, address 0x3dad4
			int prev1; // $a1
		} // line 615, address 0x3db14
	} // line 789, address 0x3de74
} // line 802, address 0x3dea0
/*
 * Offset 0x3DEC8
 * D:\driver2\game\C\DIRECTOR.C (line 1990)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DoAutoDirect()
{ // line 2, address 0x3dec8
	struct VECTOR pos; // stack address -40
	{ // line 8, address 0x3df64
		int new_view; // $v1
		{ // line 25, address 0x3dffc
		} // line 35, address 0x3e004
		{ // line 58, address 0x3e0c0
			int tmp; // $v0
		} // line 67, address 0x3e138
		{ // line 69, address 0x3e138
			int tmp; // $v0
		} // line 75, address 0x3e15c
	} // line 105, address 0x3e32c
} // line 116, address 0x3e390
/*
 * Offset 0x3E390
 * D:\driver2\game\C\DIRECTOR.C (line 2108)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ SelectCameraCar(int current /*$t1*/)
{ // line 1, address 0x3e390
	int count; // $a2
	{ // line 15, address 0x3e408
		struct _EVENT *event; // $a0
		struct _CAR_DATA *car; // $a3
		struct XZPAIR pos; // stack address -16
		{ // line 60, address 0x3e4ec
			int dist; // $v0
			int dx; // $a1
			int dz; // $a0
		} // line 72, address 0x3e574
	} // line 73, address 0x3e574
} // line 76, address 0x3e5a4
/*
 * Offset 0x3E5A4
 * D:\driver2\game\C\DIRECTOR.C (line 2186)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ InvalidCamera(int car_num /*$a2*/)
{ // line 1, address 0x3e5a4
	{ // line 7, address 0x3e5d0
		char invalidCamera; // $a3
		{ // line 14, address 0x3e638
			char numEventModels; // $a0
			struct _EVENT *event; // $v1
			struct XZPAIR pos; // stack address -24
			{ // line 22, address 0x3e690
				int dist; // $v0
				int dx; // $v1
				int dz; // $a0
			} // line 38, address 0x3e728
		} // line 39, address 0x3e728
	} // line 50, address 0x3e760
} // line 74, address 0x3e804
/*
 * Offset 0x3E804
 * D:\driver2\game\C\DIRECTOR.C (line 445)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitDirectorVariables()
{ // line 2, address 0x3e804
	int count; // $a0
} // line 22, address 0x3e870
/*
 * Offset 0x3E870
 * D:\driver2\game\C\DIRECTOR.C (line 476)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DeleteCurrentCamera(int CameraCnt /*$a0*/)
{ // line 2, address 0x3e870
	int prev; // $a1
	int next; // $a0
} // line 15, address 0x3e8f4
/*
 * Offset 0x3E904
 * D:\driver2\game\C\DIRECTOR.C (line 493)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ setCamera(struct PLAYBACKCAMERA *Change /*$a0*/)
{
}
/*
 * Offset 0x3E9B4
 * D:\driver2\game\C\DIRECTOR.C (line 634)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ FindNextChange(int CameraCnt /*$a0*/)
{ // line 1, address 0x3e9b4
	int count; // $a3
	int nextframe; // $a2
	int found; // $t0
	struct PLAYBACKCAMERA *RestoreChange; // $t1
} // line 21, address 0x3ea20
/*
 * Offset 0x3EA20
 * D:\driver2\game\C\DIRECTOR.C (line 929)
 * Stack frame base $sp, length 0
 */
struct PLAYBACKCAMERA * /*$ra*/ FindFreeCamera()
{ // line 2, address 0x3ea20
	int count; // $a1
} // line 12, address 0x3ea60
/*
 * Offset 0x3EA60
 * D:\driver2\game\C\DIRECTOR.C (line 943)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ deleteCamera(int count /*$a0*/)
{
}
/*
 * Offset 0x3EAA8
 * D:\driver2\game\C\DIRECTOR.C (line 951)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DeleteAllCameras()
{ // line 2, address 0x3eaa8
	struct PLAYBACKCAMERA nextcamera; // stack address -48
	int count; // $s0
} // line 13, address 0x3eb0c
/*
 * Offset 0x3EB0C
 * D:\driver2\game\C\DIRECTOR.C (line 1098)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ ShowReplayOptions()
{ // line 2, address 0x3eb0c
	static int toggle_icons; // address 0x5c
} // line 35, address 0x3eb48
/*
 * Offset 0x3EB58
 * D:\driver2\game\C\DIRECTOR.C (line 2263)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ NoMoreCamerasErrorMessage()
{ // line 2, address 0x3eb58
	{ // line 4, address 0x3eb70
		int strobe; // $v0
	} // line 9, address 0x3ebc4
} // line 12, address 0x3ebd4
/*
 * Offset 0x3EBD4
 * D:\driver2\game\C\DIRECTOR.C (line 2279)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ FirstCamera()
{ // line 2, address 0x3ebd4
} // line 8, address 0x3ec04
/*
 * Offset 0x3EC04
 * D:\driver2\game\C\DIRECTOR.C (line 2289)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ dist(struct VECTOR *pos1 /*$a0*/, struct VECTOR *pos2 /*$a1*/)
{ // line 1, address 0x3ec04
	int dx; // $v0
	int dz; // $a0
} // line 7, address 0x3ec74
/*
 * Offset 0x3EC74
 * D:\driver2\game\C\DIRECTOR.C (line 710)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetPlaybackCamera(struct PLAYBACKCAMERA *camera /*$a0*/)
{
}
/*
 * Offset 0x3ED2C
 * D:\driver2\game\C\DIRECTOR.C (line 2303)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetCameraReturnedFromCutscene(int CameraCnt /*$s0*/)
{ // line 1, address 0x3ed2c
	struct PLAYBACKCAMERA *next; // $a1
	int count; // $a2
} // line 28, address 0x3ede4