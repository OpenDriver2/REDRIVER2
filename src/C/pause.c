
#include "../decomp_defs.h"

void PauseMap(int direction);
void SfxVolume(int direction);
void MusicVolume(int direction);
void SaveReplay(int direction);
void SaveGame(int direction);
void EnterName();

char EnterScoreText[32] = { 0 };

MENU_ITEM MainPauseItems[9] =
{
	{ "Resume", 1u, 2u, NULL, MENU_QUIT_CONTINUE, NULL },
	{ "View map", 3u, 2u, &PauseMap, MENU_QUIT_NONE, NULL },
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Effects volume", 13u, 2u, &SfxVolume, MENU_QUIT_NONE, NULL },
	{ "Music volume", 21u, 2u, &MusicVolume, MENU_QUIT_NONE, NULL },
	{ "Film director", 1u, 2u, NULL, MENU_QUIT_DIRECTOR, NULL},
	{ "Quick replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MultiplayerPauseItems[7] =
{
	{ "Resume", 1u, 2u, NULL, MENU_QUIT_CONTINUE, NULL },
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Effects volume", 13u, 2u, &SfxVolume, MENU_QUIT_NONE, NULL },
	{ "Music volume", 21u, 2u, &MusicVolume, MENU_QUIT_NONE, NULL },
	{ "Quick replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};


MENU_ITEM CutscenePauseItems[6] =
{
	{ "Continue", 1u, 2u, NULL, MENU_QUIT_CONTINUE, NULL },
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Effects volume", 13u, 2u, &SfxVolume, MENU_QUIT_NONE, NULL },
	{ "Music volume", 21u, 2u, &MusicVolume, MENU_QUIT_NONE, NULL },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MissionCompleteItems[8] =
{
	{ "Save game", 3u, 2u, &SaveGame, MENU_QUIT_NONE, NULL },
	{ "Next mission", 1u, 2u, NULL, MENU_QUIT_NEXTMISSION, NULL },
	{ "Film director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save replay", 3u, 2u, &SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MissionFailedItems[6] =
{
	{ "Film director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Exit", 3u, 2u, &SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Retry mission",65u,2u,NULL,MENU_QUIT_NONE,&YesNoRestartHeader },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM TakeARideFinishedItems[6] =
{
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Film director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save replay", 3u, 2u, &SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM DrivingGameFinishedItems[7] =
{
	{ "Try again", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ &EnterScoreText, 3u, 2u, &EnterName, MENU_QUIT_NONE, NULL },
	{ "Film director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save replay", 3u, 2u, &SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MultiplayerFinishedItems[5] =
{
	{ "Try again", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Quick replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save replay", 3u, 2u, &SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM ChaseGameFinishedItems[6] =
{
	{ "Try again", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Film director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save replay", 3u, 2u, &SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM YesNoRestartItems[3] =
{
	{ "NO", 1u, 2u, NULL, MENU_QUIT_BACKMENU, NULL },
	{ "YES", 1u, 2u, NULL, MENU_QUIT_RESTART, NULL },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM YesNoQuitItems[3] =
{
	{ "NO", 1u, 2u, NULL, MENU_QUIT_BACKMENU, NULL },
	{ "YES", 1u, 2u, NULL, MENU_QUIT_QUIT, NULL },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM NoPadItems[1] =
{ 
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL}
};

MENU_ITEM NoMultiPadItems[2] =
{
	{ "Exit", 1u, 2u, NULL, MENU_QUIT_QUIT, NULL },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM InvalidPadItems[1] =
{ 
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL} 
};

MENU_ITEM InvalidMultiPadItems[2] =
{
	{ "Exit", 1u, 2u, NULL, MENU_QUIT_QUIT, NULL },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_HEADER PauseMenuHeader =
{ "Game paused", { 0, 0, 0, 0 }, 0u, MainPauseItems };

MENU_HEADER MultiplayerPauseHeader =
{ "Game paused", { 0, 0, 0, 0 }, 0u, MultiplayerPauseItems };

MENU_HEADER CutscenePauseMenuHeader =
{ "Game paused", { 0, 0, 0, 0 }, 0u, CutscenePauseItems };

MENU_HEADER MissionCompleteHeader =
{ "Mission successful", { 0, 0, 0, 0 }, 0u, MissionCompleteItems };

MENU_HEADER MissionFailedHeader =
{ "Mission failed", { 0, 0, 0, 0 }, 0u, MissionFailedItems };

MENU_HEADER TakeARideFinishedHeader =
{ "Game over", { 0, 0, 0, 0 }, 0u, TakeARideFinishedItems };

MENU_HEADER DrivingGameFinishedHeader =
{ "Game over", { 0, 0, 0, 0 }, 0u, DrivingGameFinishedItems };

MENU_HEADER MultiplayerFinishedHeader =
{ "Game over", { 0, 0, 0, 0 }, 0u, MultiplayerFinishedItems };

MENU_HEADER ChaseGameFinishedHeader =
{ "Game over", { 0, 0, 0, 0 }, 0u, ChaseGameFinishedItems };

MENU_HEADER NoPadHeader =
{
	"Insert controller in slot 1",
	{ 0, 0, 0, 0 },
	0u,
	NoPadItems
};

MENU_HEADER NoMultiPadHeader =
{
	"Insert controller in slot 1",
	{ 0, 0, 0, 0 },
	0u,
	NoMultiPadItems
};

MENU_HEADER InvalidPadHeader =
{
	"Incompatible controller in port 1",
	{ 0, 0, 0, 0 },
	0u,
	InvalidPadItems
};

MENU_HEADER InvalidMultiPadHeader =
{
	"Incompatible controller in port 1",
	{ 0, 0, 0, 0 },
	0u,
	InvalidMultiPadItems
};

int playerwithcontrol[3] = { 0 };

MENU_HEADER YesNoRestartHeader =
{ "Are you sure?", { 0, 0, 0, 0 }, 0u, YesNoRestartItems };

MENU_HEADER YesNoQuitHeader =
{ "Are you sure?", { 0, 0, 0, 0 }, 0u, YesNoQuitItems };



/*
 * Offset 0x6BFB8
 * D:\driver2\game\C\PAUSE.C (line 1004)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ ShowPauseMenu(enum PAUSEMODE mode /*$s0*/)
{ // line 1, address 0x6bfb8
	enum PAUSEMODE passed_mode; // $s2
	{ // line 58, address 0x6c128
	} // line 81, address 0x6c1a8
	{ // line 88, address 0x6c1e0
		struct RECT rect; // stack address -32
	} // line 97, address 0x6c264
} // line 133, address 0x6c314
/*
 * Offset 0x6C314
 * D:\driver2\game\C\PAUSE.C (line 1216)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitaliseMenu(enum PAUSEMODE mode /*$a2*/)
{ // line 1, address 0x6c314
	struct MENU_ITEM *pItem; // $a0
	int i; // $a1
} // line 172, address 0x6c720
/*
 * Offset 0x6C720
 * D:\driver2\game\C\PAUSE.C (line 1401)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupMenu(struct MENU_HEADER *menu /*$a0*/, int back /*$a1*/)
{ // line 1, address 0x6c720
	struct MENU_ITEM *pItem; // $a2
	int count; // $a3
} // line 30, address 0x6c85c
/*
 * Offset 0x6C85C
 * D:\driver2\game\C\PAUSE.C (line 1443)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawVisibleMenus()
{ // line 2, address 0x6c85c
	struct MENU_HEADER *pActive; // $s5
	struct MENU_ITEM *pItem; // $s1
	struct POLY_FT3 *null; // $a0
	int i; // stack address -48
	int ypos; // $s3
	int xpos; // $fp
	int width; // $s4
	{ // line 30, address 0x6c928
		unsigned char r; // $s6
		unsigned char b; // $s7
		int x1; // $s0
		int x2; // $s2
	} // line 66, address 0x6caa8
} // line 85, address 0x6cc50
/*
 * Offset 0x6CC50
 * D:\driver2\game\C\PAUSE.C (line 1543)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ControlMenu()
{ // line 2, address 0x6cc50
	static int debounce; // address 0x38
	unsigned short paddata; // $a2
	unsigned short paddirect; // $a3
	{ // line 53, address 0x6cd3c
		int doit; // $v1
	} // line 78, address 0x6cde0
	{ // line 132, address 0x6cfbc
		int i; // $a0
	} // line 139, address 0x6d020
	{ // line 149, address 0x6d040
		int i; // $a0
	} // line 160, address 0x6d09c
} // line 162, address 0x6d09c
/*
 * Offset 0x6D0AC
 * D:\driver2\game\C\PAUSE.C (line 1787)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ EnterScoreName()
{ // line 2, address 0x6d0ac
	struct SCORE_ENTRY *table; // stack address -40
	char *username; // $s3
	unsigned short npad; // $a1
	int so; // $s0
	int co; // $s1
	int delay; // $s2
	char c; // $a0
	char toggle; // $s6
} // line 154, address 0x6d38c
/*
 * Offset 0x6D38C
 * D:\driver2\game\C\PAUSE.C (line 1943)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CreateScoreNames(struct SCORE_ENTRY *table /*$s0*/, struct PLAYER_SCORE *score /*stack 4*/, int position /*stack 8*/)
{ // line 1, address 0x6d38c
	char *text; // $s1
	int min; // $t1
	int frac; // $v0
	int i; // $s5
} // line 69, address 0x6d6cc
/*
 * Offset 0x6D6FC
 * D:\driver2\game\C\PAUSE.C (line 2020)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawHighScoreMenu(int selection /*stack 0*/)
{ // line 1, address 0x6d6fc
	struct POLY_FT3 *null; // $a0
	char text[4]; // stack address -48
	unsigned char r; // $s3
	unsigned char g; // $s5
	unsigned char b; // $s2
	int i; // $s0
	int ypos; // $s4
} // line 55, address 0x6da18
/*
 * Offset 0x6DA18
 * D:\driver2\game\C\PAUSE.C (line 1153)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SaveReplay(int direction /*$a0*/)
{
}
/*
 * Offset 0x6DA3C
 * D:\driver2\game\C\PAUSE.C (line 1158)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SaveGame(int direction /*$a0*/)
{
}
/*
 * Offset 0x6DA60
 * D:\driver2\game\C\PAUSE.C (line 1163)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ EnterName()
{
}
/*
 * Offset 0x6DA80
 * D:\driver2\game\C\PAUSE.C (line 1185)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ MaxMenuStringLength(struct MENU_HEADER *pMenu /*$v0*/)
{ // line 1, address 0x6da80
	struct MENU_ITEM *pItems; // $s1
	int max; // $s2
	int temp; // $s0
} // line 21, address 0x6db38
/*
 * Offset 0x6DB38
 * D:\driver2\game\C\PAUSE.C (line 1710)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ PauseMap(int direction /*$a0*/)
{
}
/*
 * Offset 0x6DB9C
 * D:\driver2\game\C\PAUSE.C (line 1725)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SfxVolume(int direction /*$a0*/)
{ // line 1, address 0x6db9c
} // line 19, address 0x6dc6c
/*
 * Offset 0x6DC6C
 * D:\driver2\game\C\PAUSE.C (line 1746)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ MusicVolume(int direction /*$a0*/)
{ // line 1, address 0x6dc6c
} // line 19, address 0x6dd3c
/*
 * Offset 0x6DD3C
 * D:\driver2\game\C\PAUSE.C (line 1139)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DrawPauseMenus()
{
}