#include "DRIVER2.H"
#include "PAUSE.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "OVERLAY.H"
#include "PRES.H"
#include "PAD.H"
#include "MAIN.H"
#include "GLAUNCH.H"
#include "SCORES.H"
#include "SOUND.H"
#include "CUTSCENE.H"
#include "REPLAYS.H"
#include "OVERMAP.H"
#include "HANDLING.H"
#include "../MEMCARD/MAIN.H"

#include "STRINGS.H"

static int gScoreEntered = 0;
static char EnterNameText[32] = { 0 };
static int PauseReturnValue;
int pauseflag = 0;
int gShowMap = 0;
int gDrawPauseMenus = 0;
int gEnteringScore = 0;
static int gScorePosition = 0;
static int allownameentry = 0;

static MENU_ITEM* ActiveItem[3];
static MENU_HEADER* ActiveMenu;
static int ActiveMenuItem;
static int VisibleMenu;
static MENU_HEADER* VisibleMenus[3];
static char SfxVolumeText[8];
static char MusicVolumeText[8];

static char ScoreTime[5][16];
static char ScoreItems[5][16];
static char ScoreName[5][7];

static char validchars[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-+!";

void PauseMap(int direction);
void SfxVolume(int direction);
void MusicVolume(int direction);
void SaveReplay(int direction);
void SaveGame(int direction);
void EnterName();

char EnterScoreText[32] = { 0 };

#if defined(_DEBUG) || defined(DEBUG_OPTIONS)

void SetRightWayUp(int direction)
{
	extern char gRightWayUp;
	gRightWayUp = 1;
	PauseReturnValue = MENU_QUIT_CONTINUE;
}

void SetDisplayPosition(int direction)
{
	extern int gDisplayPosition;
	gDisplayPosition ^= 1;
}

void ToggleInvincibility(int direction)
{
	extern int gInvincibleCar;
	gInvincibleCar ^= 1;
}

void ToggleImmunity(int direction)
{
	extern int gPlayerImmune;
	gPlayerImmune ^= 1;
}

void TogglePlayerGhost(int direction)
{
	extern int playerghost;
	playerghost ^= 1;
}

void ToggleOverlays(int direction)
{
	extern int gDoOverlays;
	gDoOverlays ^= 1;
}

int lastCar = -1;

void ToggleSecretCarFun(int direction)
{
	extern CAR_COSMETICS car_cosmetics[5];
	extern int wantedCar[2];

	int active = (ActiveCheats.cheat10 ^= 1);

	if (active)
	{
		if (lastCar == -1)
			lastCar = wantedCar[0];

		// make our current car the secret car
		wantedCar[0] = 12;
	}
	else
	{
		if (lastCar != -1)
		{
			// restore our initial car
			wantedCar[0] = lastCar;
			lastCar = -1;
		}
	}

	FixCarCos(&car_cosmetics[4], 12);
}

void ToggleMiniCars(int direction)
{
	ActiveCheats.cheat13 ^= 1;
}

void ToggleJerichoMode(int direction)
{
	ActiveCheats.cheat12 ^= 1;
}

void TogglePuppyDogCops(int direction)
{
	gPuppyDogCop ^= 1;
}

extern void LoadSky(void);

void DebugTimeOfDayDay(int direction)
{
	gTimeOfDay = 1;
	gWantNight = 0;
	LoadSky();
}

void DebugTimeOfDayNight(int direction)
{
	gTimeOfDay = 3;
	gWantNight = 1;
	LoadSky();
}

void DebugTimeOfDayDusk(int direction)
{
	gTimeOfDay = 0;
	gWantNight = 0;
	LoadSky();
}

void DebugTimeOfDayDawn(int direction)
{
	gTimeOfDay = 2;
	gWantNight = 0;
	LoadSky();
}

void DebugTimeOfDayRain(int direction)
{
	//extern int weather;
	//weather ^= weather;
	gWeather ^= 1;

	if (gWeather == 1)
		wetness = 7000;
	else
		wetness = 0;

	LoadSky();
}

MENU_ITEM DebugTimeOfDayItems[] =
{
	{ "Day",	3, 	2,	DebugTimeOfDayDay,	MENU_QUIT_NONE,		NULL },
	{ "Night", 	3,  2,  DebugTimeOfDayNight,MENU_QUIT_NONE,		NULL },
	{ "Dusk", 	3, 	2,  DebugTimeOfDayDusk, MENU_QUIT_NONE,		NULL },
	{ "Dawn", 	3, 	2,  DebugTimeOfDayDawn,	MENU_QUIT_NONE,		NULL },
	{ "Rain", 	3, 	2,  DebugTimeOfDayRain,	MENU_QUIT_NONE,		NULL },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_HEADER DebugTimeOfDayHeader =
{ "Time Of Day", { 0, 0, 0, 0 }, 0u, DebugTimeOfDayItems };

MENU_ITEM DebugJustForFunItems[] =
{
	{ "Secret Car Fun", 3,	2,  ToggleSecretCarFun, MENU_QUIT_RESTART,	NULL },
	{ "Mini Cars", 3,	2,  ToggleMiniCars, MENU_QUIT_NONE,	NULL },
	{ "Jericho Mode",	3,	2,  ToggleJerichoMode,	MENU_QUIT_NONE,		NULL },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_HEADER DebugJustForFunHeader =
{ "Just for fun", { 0, 0, 0, 0 }, 0u, DebugJustForFunItems };

#ifdef CUTSCENE_RECORDER
extern void NextCutsceneRecorderPlayer(int dir);
extern char gCutsceneRecorderPauseText[64];

extern void NextChase(int dir);
extern char gCurrentChasePauseText[64];
#endif

MENU_ITEM DebugOptionsItems[] =
{
#ifdef CUTSCENE_RECORDER
	//{ gCutsceneRecorderPauseText, 5u, 2u, (pauseFunc)&NextCutsceneRecorderPlayer, MENU_QUIT_NONE, NULL },
	{ gCurrentChasePauseText, 5u, 2u, (pauseFunc)&NextChase, MENU_QUIT_NONE, NULL },
#endif
	{ "Display position", 3, 	2,	SetDisplayPosition,		MENU_QUIT_NONE,		NULL},
	{ "Back on Wheels",	3, 	2,	SetRightWayUp,		MENU_QUIT_NONE,		NULL},
	{ "Time of Day", 	65, 2,  NULL,		  		MENU_QUIT_NONE,		&DebugTimeOfDayHeader },
	{ "Fun Cheats", 	65, 2,  NULL,		  		MENU_QUIT_NONE,		&DebugJustForFunHeader },
	{ "Invincibility", 	3, 	2,  ToggleInvincibility,MENU_QUIT_NONE,		NULL},
	{ "Immunity", 		3, 	2,  ToggleImmunity,		MENU_QUIT_NONE,		NULL},
	{ "Puppy Dog Cops",	3,	2,  TogglePuppyDogCops,	MENU_QUIT_NONE,		NULL },
	{ "Toggle Overlay",	3,	2,  ToggleOverlays,		MENU_QUIT_NONE,		NULL },
	{ "Player Ghost", 	3, 	2,  TogglePlayerGhost,	MENU_QUIT_NONE,		NULL },
	{ "Next Mission",	1, 	2,  NULL,				MENU_QUIT_NEXTMISSION, 	NULL },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_HEADER DebugOptionsHeader =
{ "Debug Options", { 0, 0, 0, 0 }, 0u, DebugOptionsItems };
#endif

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

MENU_HEADER YesNoRestartHeader =
{ "Are You Sure?", { 0, 0, 0, 0 }, 0u, YesNoRestartItems };

MENU_HEADER YesNoQuitHeader =
{ "Are You Sure?", { 0, 0, 0, 0 }, 0u, YesNoQuitItems };

MENU_ITEM MainPauseItems[] =
{
	{ "Continue", 1u, 2u, NULL, MENU_QUIT_CONTINUE, NULL },
	{ "Show Map", 3u, 2u, (pauseFunc)&PauseMap, MENU_QUIT_NONE, NULL },
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Sfx Volume", 13u, 2u, (pauseFunc)&SfxVolume, MENU_QUIT_NONE, NULL },
	{ "Music Volume", 21u, 2u, (pauseFunc)&MusicVolume, MENU_QUIT_NONE, NULL },
	{ "Film Director", 1u, 2u, NULL, MENU_QUIT_DIRECTOR, NULL},
	{ "Quick Replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
#if defined(_DEBUG) || defined(DEBUG_OPTIONS)
	{ "Debug Options", 65u, 2u, NULL, MENU_QUIT_NONE, &DebugOptionsHeader },
#endif
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MultiplayerPauseItems[7] =
{
	{ "Resume", 1u, 2u, NULL, MENU_QUIT_CONTINUE, NULL },
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Sfx Volume", 13u, 2u, (pauseFunc)&SfxVolume, MENU_QUIT_NONE, NULL },
	{ "Music Volume", 21u, 2u, (pauseFunc)&MusicVolume, MENU_QUIT_NONE, NULL },
	{ "Quick Replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

void SkipCutscene(int dir)
{
	gSkipInGameCutscene = 1;
}

MENU_ITEM CutscenePauseItems[] =
{
	{ "Continue", 1u, 2u, NULL, MENU_QUIT_CONTINUE, NULL },
#if defined(_DEBUG) || defined(DEBUG_OPTIONS)
	{ "Skip Cutscene", 3u, 2u, (pauseFunc)&SkipCutscene, MENU_QUIT_CONTINUE, NULL },
#endif
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Effects Volume", 13u, 2u, (pauseFunc)&SfxVolume, MENU_QUIT_NONE, NULL },
	{ "Music Volume", 21u, 2u, (pauseFunc)&MusicVolume, MENU_QUIT_NONE, NULL },
#if defined(_DEBUG) || defined(DEBUG_OPTIONS)
	{ "Debug Options", 65u, 2u, NULL, MENU_QUIT_NONE, &DebugOptionsHeader },
#endif
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MissionCompleteItems[] =
{
#ifdef PSX
	{ "Save Game", 3u, 2u, (pauseFunc)&SaveGame, MENU_QUIT_NONE, NULL },
#endif
	{ "Continue", 1u, 2u, NULL, MENU_QUIT_NEXTMISSION, NULL },
	{ "Film Director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick Replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save Replay", 3u, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MissionFailedItems[6] =
{
	{ "Film Director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick Replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Exit", 3u, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Retry Mission",65u,2u,NULL,MENU_QUIT_NONE,&YesNoRestartHeader },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM TakeARideFinishedItems[] =
{
	{ "Restart", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Film Director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick Replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save Replay", 3u, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM DrivingGameFinishedItems[7] =
{
	{ "Play Again", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ EnterScoreText, 3u, 2u, (pauseFunc)&EnterName, MENU_QUIT_NONE, NULL },
	{ "Film Director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick Replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save Replay", 3u, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MultiplayerFinishedItems[5] =
{
	{ "Play Again", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Quick Replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save Replay", 3u, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, 128u, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM ChaseGameFinishedItems[6] =
{
	{ "Play Again", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ "Film Director",1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ "Quick Replay",1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ "Save Replay", 3u, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ "Exit", 65u, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
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
{ "Paused", { 0, 0, 0, 0 }, 0u, MainPauseItems };

MENU_HEADER MultiplayerPauseHeader =
{ "Paused", { 0, 0, 0, 0 }, 0u, MultiplayerPauseItems };

MENU_HEADER CutscenePauseMenuHeader =
{ "Paused", { 0, 0, 0, 0 }, 0u, CutscenePauseItems };

MENU_HEADER MissionCompleteHeader =
{ "Mission Successful", { 0, 0, 0, 0 }, 0u, MissionCompleteItems };

MENU_HEADER MissionFailedHeader =
{ "Mission Failed", { 0, 0, 0, 0 }, 0u, MissionFailedItems };

MENU_HEADER TakeARideFinishedHeader =
{ "Game Over", { 0, 0, 0, 0 }, 0u, TakeARideFinishedItems };

MENU_HEADER DrivingGameFinishedHeader =
{ "Game Over", { 0, 0, 0, 0 }, 0u, DrivingGameFinishedItems };

MENU_HEADER MultiplayerFinishedHeader =
{ "Game Over", { 0, 0, 0, 0 }, 0u, MultiplayerFinishedItems };

MENU_HEADER ChaseGameFinishedHeader =
{ "Game Over", { 0, 0, 0, 0 }, 0u, ChaseGameFinishedItems };

MENU_HEADER NoPadHeader =
{
	"Insert a Controller in port 1",
	{ 0, 0, 0, 0 },
	0u,
	NoPadItems
};

MENU_HEADER NoMultiPadHeader =
{
	"Insert a Controller in port 2",
	{ 0, 0, 0, 0 },
	0u,
	NoMultiPadItems
};

MENU_HEADER InvalidPadHeader =
{
	"Unsupported controller in port 1",
	{ 0, 0, 0, 0 },
	0u,
	InvalidPadItems
};

MENU_HEADER InvalidMultiPadHeader =
{
	"Unsupported controller in port 2",
	{ 0, 0, 0, 0 },
	0u,
	InvalidMultiPadItems
};

int playerwithcontrol[3] = { 0 };



// decompiled code
// original method signature: 
// int /*$ra*/ ShowPauseMenu(PAUSEMODE mode /*$s0*/)
 // line 1004, offset 0x0006bf50
	/* begin block 1 */
		// Start line: 1005
		// Start offset: 0x0006BF50
		// Variables:
	// 		PAUSEMODE passed_mode; // $s2

		/* begin block 1.1 */
			// Start line: 1062
			// Start offset: 0x0006C0C0
		/* end block 1.1 */
		// End offset: 0x0006C140
		// End Line: 1085

		/* begin block 1.2 */
			// Start line: 1092
			// Start offset: 0x0006C178
			// Variables:
		// 		RECT rect; // stack offset -32
		/* end block 1.2 */
		// End offset: 0x0006C1FC
		// End Line: 1101
	/* end block 1 */
	// End offset: 0x0006C2AC
	// End Line: 1137

	/* begin block 2 */
		// Start line: 2008
	/* end block 2 */
	// End Line: 2009

// [D]
int ShowPauseMenu(PAUSEMODE mode)
{
	PAUSEMODE passed_mode;
	RECT16 rect;

	ReadControllers();

	if (mode == PAUSEMODE_PAUSEP1)
	{
		playerwithcontrol[0] = 1;
		playerwithcontrol[1] = 0;
		playerwithcontrol[2] = 0;
	}
	else if (mode == PAUSEMODE_PAUSEP2) 
	{
		playerwithcontrol[0] = 0;
		playerwithcontrol[1] = 1;
		playerwithcontrol[2] = 0;
	}
	else 
	{
		playerwithcontrol[0] = 0;
		playerwithcontrol[1] = 0;
		playerwithcontrol[2] = 1;
	}

	SetDispMask(1);

	SfxVolume(0);
	MusicVolume(0);

	StopPadVibration(0);
	StopPadVibration(1);

	InitaliseMenu(mode);
	gDrawPauseMenus = 1;

	if (NoPlayerControl == 0 && OnScoreTable(NULL) != -1 && allownameentry != 0) 
	{
		gScoreEntered = 0;
		sprintf(EnterScoreText, "Enter Score");
		sprintf(EnterNameText, "Enter Name:");
	}
	else
	{
		gScoreEntered = 1;
		sprintf(EnterScoreText, "View Table");
		sprintf(EnterNameText, "High Scores");
	}

	passed_mode = mode;

	if (mode == PAUSEMODE_PADERROR)
		mode = PAUSEMODE_PAUSE;

	PauseReturnValue = 0;

	do {
		UpdatePadData();

		if (passed_mode == PAUSEMODE_PADERROR)
		{
			if (pad_connected == 1) 
			{
				InitaliseMenu(mode);
				passed_mode = mode;
			}
			else 
			{
				InitaliseMenu(PAUSEMODE_PADERROR);
			}
		}
		else 
		{
			if (pad_connected != 1) 
			{
				passed_mode = PAUSEMODE_PADERROR;
				InitaliseMenu(PAUSEMODE_PADERROR);
			}
		}

		if (pad_connected < 1) 
			playerwithcontrol[2] = 1;

		ControlMenu();
		DrawGame();

	} while (PauseReturnValue == 0);

	gDrawPauseMenus = 0;

	if (1 < NumPlayers)
	{
		rect.x = 0;
		rect.w = 320;
		rect.h = 1;
		rect.y = current->draw.clip.y + current->draw.clip.h;
		ClearImage2(&rect, 0, 0, 0);
		DrawGame();

		rect.x = 0;
		rect.w = 320;
		rect.h = 1;
		rect.y = current->draw.clip.y + current->draw.clip.h;
		ClearImage2(&rect, 0, 0, 0);
		DrawGame();
	}

	switch (PauseReturnValue)
	{
		case 1:
			pauseflag = 0;
			break;
		case 2:
			EndGame(GAMEMODE_QUIT);
			break;
		case 3:
			EndGame(GAMEMODE_RESTART);
			break;
		case 4:
			EndGame(GAMEMODE_DIRECTOR);
			break;
		case 5:
			EndGame(GAMEMODE_REPLAY);
			break;
		case 7:
			EndGame(GAMEMODE_NEXTMISSION);
			break;
	}

	return PauseReturnValue;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawPauseMenus()
 // line 1139, offset 0x0006dcd4
	/* begin block 1 */
		// Start line: 4357
	/* end block 1 */
	// End Line: 4358

	/* begin block 2 */
		// Start line: 2278
	/* end block 2 */
	// End Line: 2279

	/* begin block 3 */
		// Start line: 4358
	/* end block 3 */
	// End Line: 4359

/* WARNING: Unknown calling convention yet parameter storage is locked */



// [D]
void DrawPauseMenus(void)
{
#if !defined(PSX) && defined(DEBUG_OPTIONS)
	extern int g_FreeCameraEnabled;

	if (g_FreeCameraEnabled)
		return;
#endif

	if (gDrawPauseMenus != 0 && gShowMap == 0) 
	{
		if (gEnteringScore == 0)
			DrawVisibleMenus();
		else 
			DrawHighScoreMenu(gScorePosition);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SaveReplay(int direction /*$a0*/)
 // line 1153, offset 0x0006d9b0
	/* begin block 1 */
		// Start line: 3753
	/* end block 1 */
	// End Line: 3754

	/* begin block 2 */
		// Start line: 2306
	/* end block 2 */
	// End Line: 2307

	/* begin block 3 */
		// Start line: 3754
	/* end block 3 */
	// End Line: 3755

void SaveReplay(int direction)
{
	char filename[64];
#ifdef PSX
	CallMemoryCard(0x10, 1);
#else
	int size = SaveReplayToBuffer(_other_buffer);

#ifdef CUTSCENE_RECORDER
	extern int gCutsceneAsReplay;
	if(gCutsceneAsReplay != 0)
	{
		FILE* temp;
		int cnt;
		cnt = 2;

		while(cnt < 14)
		{
			sprintf(filename, "CUT%d_%d.D2RP", gCutsceneAsReplay, cnt);

			temp = fopen(filename, "rb");
			if (temp)
			{
				fclose(temp);
				cnt++;
			}
			else
				break;
		}
	}
#else
	sprintf(filename, "CHASE.D2RP", gCurrentMissionNumber);
#endif
	FILE* fp = fopen(filename, "wb");
	if (fp)
	{
		fwrite(_other_buffer, 1, size, fp);
		fclose(fp);
	}
#endif
}



// decompiled code
// original method signature: 
// void /*$ra*/ SaveGame(int direction /*$a0*/)
 // line 1158, offset 0x0006d9d4
	/* begin block 1 */
		// Start line: 3763
	/* end block 1 */
	// End Line: 3764

	/* begin block 2 */
		// Start line: 3764
	/* end block 2 */
	// End Line: 3765

void SaveGame(int direction)
{
	CallMemoryCard(0x20, 1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ EnterName()
 // line 1163, offset 0x0006d9f8
	/* begin block 1 */
		// Start line: 3773
	/* end block 1 */
	// End Line: 3774

	/* begin block 2 */
		// Start line: 3774
	/* end block 2 */
	// End Line: 3775

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void EnterName(void)
{
	EnterScoreName();
}



// decompiled code
// original method signature: 
// int /*$ra*/ MaxMenuStringLength(MENU_HEADER *pMenu /*$v0*/)
 // line 1185, offset 0x0006da18
	/* begin block 1 */
		// Start line: 1186
		// Start offset: 0x0006DA18
		// Variables:
	// 		MENU_ITEM *pItems; // $s1
	// 		int max; // $s2
	// 		int temp; // $s0
	/* end block 1 */
	// End offset: 0x0006DAD0
	// End Line: 1206

	/* begin block 2 */
		// Start line: 3817
	/* end block 2 */
	// End Line: 3818

// [D]
int MaxMenuStringLength(MENU_HEADER *pMenu)
{
	int max;
	int temp;
	MENU_ITEM *pItems;

	pItems = pMenu->MenuItems;
	max = StringWidth(pMenu->Title);

	while ((pItems->Type & 0x80) == 0)
	{
		temp = StringWidth(pItems->Text);

		if ((pItems->Type & 0x18) != 0) 
			temp = temp + StringWidth(" 100");

		if (max < temp)
			max = temp;

		pItems++;
	}

	return max;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitaliseMenu(PAUSEMODE mode /*$a2*/)
 // line 1216, offset 0x0006c2ac
	/* begin block 1 */
		// Start line: 1217
		// Start offset: 0x0006C2AC
		// Variables:
	// 		MENU_ITEM *pItem; // $a0
	// 		int i; // $a1
	/* end block 1 */
	// End offset: 0x0006C6B8
	// End Line: 1388

	/* begin block 2 */
		// Start line: 2361
	/* end block 2 */
	// End Line: 2362

	/* begin block 3 */
		// Start line: 2441
	/* end block 3 */
	// End Line: 2442

// [D] [A] please get rid of inlined code
void InitaliseMenu(PAUSEMODE mode)
{
	unsigned char uVar1;
	unsigned char bVar2;
	unsigned char bVar3;
	MENU_ITEM *pMVar4;
	MENU_HEADER *pMVar5;
	MENU_HEADER **ppMVar6;
	char *pcVar7;
	MENU_ITEM **ppMVar8;
	unsigned char uVar9;
	int iVar10;

	ppMVar8 = ActiveItem;
	ppMVar6 = VisibleMenus;
	iVar10 = 2;

	do {
		*ppMVar8++ = NULL;
		*ppMVar6++ = NULL;

		iVar10--;
	} while (-1 < iVar10);

	allownameentry = 0;

	switch (mode) 
	{
		case PAUSEMODE_PAUSE:
		case PAUSEMODE_PAUSEP1:
		case PAUSEMODE_PAUSEP2:
			if (NumPlayers == 1 && gMultiplayerLevels == 0) 
			{
				if (gInGameCutsceneActive == 0)
				{
					ActiveMenu = &PauseMenuHeader;
				}
				else 
				{
					ActiveMenu = &CutscenePauseMenuHeader;
				}
			}
			else 
			{
				ActiveMenu = &MultiplayerPauseHeader;
			}
			break;
		case PAUSEMODE_GAMEOVER:
			switch (GameType) 
			{
				case GAME_PURSUIT:
				switchD_0006c3b4_caseD_3:
					ActiveMenu = &ChaseGameFinishedHeader;
					gMissionCompletionState = mode;
					goto LAB_0006c5d0;
				case GAME_GETAWAY:
				case GAME_CHECKPOINT:
					if (NumPlayers == 1)
					{
						ActiveMenu = &DrivingGameFinishedHeader;
						allownameentry = 0;
						gMissionCompletionState = mode;
						goto LAB_0006c5d0;
					}
					break;
				case GAME_GATERACE:
				case GAME_TRAILBLAZER:
				case GAME_SURVIVAL:
					if (NumPlayers == 1)
					{
						ActiveMenu = &DrivingGameFinishedHeader;
						gMissionCompletionState = mode;
						allownameentry = NumPlayers;
						goto LAB_0006c5d0;
					}
					break;
				default:
					if (NumPlayers == 1)
						goto switchD_0006c460_caseD_1;
			}
		LAB_0006c4c0:
			ActiveMenu = &MultiplayerFinishedHeader;
			gMissionCompletionState = mode;
			break;
		case PAUSEMODE_COMPLETE:
			if (true)
			{
				switch (GameType) 
				{
					case GAME_MISSION:
						ActiveMenu = &MissionCompleteHeader;
						gMissionCompletionState = mode;
						goto LAB_0006c5d0;
					case GAME_GETAWAY:
					case GAME_GATERACE:
					case GAME_CHECKPOINT:
					case GAME_TRAILBLAZER:
					case GAME_SURVIVAL:
					case GAME_COPSANDROBBERS:
						if (NumPlayers == 1) {

							ActiveMenu = &DrivingGameFinishedHeader;
							gMissionCompletionState = mode;
							allownameentry = NumPlayers;
							goto LAB_0006c5d0;
						}
						goto LAB_0006c4c0;
					case GAME_PURSUIT:
						goto switchD_0006c3b4_caseD_3;
				}
			}
		switchD_0006c460_caseD_1:
			ActiveMenu = &TakeARideFinishedHeader;
			gMissionCompletionState = mode;
			break;
		case PAUSEMODE_PADERROR:
			if (pad_connected < 0) 
			{
				if (NumPlayers == 1) 
				{
					ActiveMenu = &InvalidPadHeader;
				}
				else
				{
					ActiveMenu = &InvalidMultiPadHeader;
					if (Pads[0].type != 1) 
					{
						pcVar7 = "Incorrect controller in Port 2";
							goto LAB_0006c5cc;
					}
				}
				pcVar7 = "Incorrect controller in Port 1";
			}
			else 
			{
				if (NumPlayers == 1) 
				{
					ActiveMenu = &NoPadHeader;
				}
				else
				{
					ActiveMenu = &NoMultiPadHeader;
					if (Pads[0].type != 0) 
					{
						pcVar7 = "Please insert controller into port";
							goto LAB_0006c5cc;
					}
				}
				pcVar7 = "Please insert controller into port";
			}
		LAB_0006c5cc:
			ActiveMenu->Title = pcVar7;
	}
LAB_0006c5d0:
	ActiveItem[0] = ActiveMenu->MenuItems;
	VisibleMenus[0] = ActiveMenu;

	ActiveMenuItem = 0;
	VisibleMenu = 0;

	uVar1 = ActiveMenu->MenuItems->Type;
	uVar9 = 0;
	pMVar4 = ActiveMenu->MenuItems;

	while (uVar1 != 0x80)
	{
		uVar1 = (pMVar4+1)->Type;
		uVar9++;
		pMVar4++;
	}

	ActiveMenu->NumItems = uVar9;
	iVar10 = MaxMenuStringLength(ActiveMenu);

	bVar2 = ActiveMenu->NumItems;
	bVar3 = ActiveMenu->NumItems;
	(ActiveMenu->Bound).x = (short)((0x130 - iVar10) / 2) + -4;
	(ActiveMenu->Bound).w = (short)iVar10 + 0x18;
	iVar10 = (int)(((uint)bVar2 + 1) * -0xf + 0x100) / 2;
	(ActiveMenu->Bound).y = (short)iVar10;
	(ActiveMenu->Bound).h = ((ushort)bVar3 + 1) * 0xf + 10;

	if (iVar10 < 0x30)
		(ActiveMenu->Bound).y = 0x30;

}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupMenu(MENU_HEADER *menu /*$a0*/, int back /*$a1*/)
 // line 1401, offset 0x0006c6b8
	/* begin block 1 */
		// Start line: 1402
		// Start offset: 0x0006C6B8
		// Variables:
	// 		MENU_ITEM *pItem; // $a2
	// 		int count; // $a3
	/* end block 1 */
	// End offset: 0x0006C7F4
	// End Line: 1431

	/* begin block 2 */
		// Start line: 2819
	/* end block 2 */
	// End Line: 2820

	/* begin block 3 */
		// Start line: 2833
	/* end block 3 */
	// End Line: 2834

	/* begin block 4 */
		// Start line: 2840
	/* end block 4 */
	// End Line: 2841

// [D]
void SetupMenu(MENU_HEADER *menu, int back)
{
	unsigned char bVar1;
	unsigned char bVar2;
	MENU_ITEM *pMVar3;
	MENU_HEADER *pMVar4;
	int iVar5;
	MENU_ITEM *pMVar6;
	int count;

	count = 0;

	ActiveMenuItem = 0;
	if (menu->MenuItems->Type != 0x80) 
	{
		pMVar6 = menu->MenuItems;
		do {
			if ((back != 0) && (pMVar6 == ActiveItem[VisibleMenu]))
			{
				ActiveMenuItem = count;
			}
			pMVar3 = pMVar6 + 1;
			count = count + 1;

			pMVar6 = pMVar6 + 1;
		} while (pMVar3->Type != 0x80);
	}
	ActiveMenu = menu;
	menu->NumItems = count;
	iVar5 = MaxMenuStringLength(ActiveMenu);
	pMVar4 = ActiveMenu;
	bVar1 = ActiveMenu->NumItems;
	bVar2 = ActiveMenu->NumItems;
	(ActiveMenu->Bound).x = (short)((0x130 - iVar5) / 2) + -4;
	(pMVar4->Bound).w = (short)iVar5 + 0x18;
	iVar5 = (int)(((uint)bVar1 + 1) * -0xf + 0x100) / 2;
	(pMVar4->Bound).y = (short)iVar5;
	(pMVar4->Bound).h = ((ushort)bVar2 + 1) * 0xf + 10;

	if (iVar5 < 0x30)
	{
		(pMVar4->Bound).y = 0x30;
	}

	ActiveItem[VisibleMenu] = ActiveMenu->MenuItems + ActiveMenuItem;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawVisibleMenus()
 // line 1443, offset 0x0006c7f4
	/* begin block 1 */
		// Start line: 1445
		// Start offset: 0x0006C7F4
		// Variables:
	// 		MENU_HEADER *pActive; // $s5
	// 		MENU_ITEM *pItem; // $s1
	// 		POLY_FT3 *null; // $a0
	// 		int i; // stack offset -48
	// 		int ypos; // $s3
	// 		int xpos; // $fp
	// 		int width; // $s4

		/* begin block 1.1 */
			// Start line: 1473
			// Start offset: 0x0006C8C0
			// Variables:
		// 		unsigned char r; // $s6
		// 		unsigned char b; // $s7
		// 		int x1; // $s0
		// 		int x2; // $s2
		/* end block 1.1 */
		// End offset: 0x0006CA40
		// End Line: 1509
	/* end block 1 */
	// End offset: 0x0006CBE8
	// End Line: 1528

	/* begin block 2 */
		// Start line: 2919
	/* end block 2 */
	// End Line: 2920

	/* begin block 3 */
		// Start line: 2932
	/* end block 3 */
	// End Line: 2933

	/* begin block 4 */
		// Start line: 2933
	/* end block 4 */
	// End Line: 2934

	/* begin block 5 */
		// Start line: 2939
	/* end block 5 */
	// End Line: 2940

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DrawVisibleMenus(void)
{
	short sVar1;
	short sVar2;
	short sVar3;
	DB *pDVar4;
	uint uVar5;
	int iVar6;
	int x;
	char *pString;
	POLY_FT3 *null;
	POLY_F4 *poly;
	short sVar8;
	MENU_ITEM *pMVar9;
	int y;
	int y_00;
	MENU_HEADER *pMVar10;
	int r;
	int b;
	int x_00;
	int i;

	if (1 < NumPlayers) {
		SetFullscreenDrawing();
	}
	pMVar10 = VisibleMenus[VisibleMenu];
	y = (int)(pMVar10->Bound).y;
	y_00 = y;
	if (pMVar10->Title != NULL) 
{
		y_00 = y + 0xf;
		OutputString(pMVar10->Title, 2, (int)(pMVar10->Bound).x, y, (int)(pMVar10->Bound).w, 0x80, 0x20, 0x20);
	}
	i = 0;
	uVar5 = (uint)pMVar10->NumItems;
	pMVar9 = pMVar10->MenuItems;
	sVar1 = (pMVar10->Bound).x;
	x_00 = (int)sVar1;
	sVar2 = (pMVar10->Bound).w;
	y = (int)sVar2;
	if (pMVar10->NumItems != 0) {
		do {
			if (pMVar9->Text != NULL) {
				r = 0x80;
				if (pMVar9 == ActiveItem[VisibleMenu])
				{
					r = 0;
					b = 0;
				}
				else
				{
					b = 0x80;
				}
				if ((pMVar9->Type & 8) == 0) 
				{
					if ((pMVar9->Type & 0x10) != 0) 
					{
						iVar6 = StringWidth(pMVar9->Text);
						x = StringWidth(" 100");
						x = x_00 + ((y - iVar6) - x >> 1);
						iVar6 = StringWidth(pMVar9->Text);
						iVar6 = x + iVar6;
						OutputString(pMVar9->Text, 1, x, y_00, y, r, 0x80, b);
						pString = MusicVolumeText;
						goto LAB_0006c9ec;
					}

					OutputString(pMVar9->Text, (uint)pMVar9->Justify, x_00, y_00, y, r, 0x80, b);
				}
				else 
				{
					iVar6 = StringWidth(pMVar9->Text);
					x = StringWidth(" 100");
					x = x_00 + ((y - iVar6) - x >> 1);
					iVar6 = StringWidth(pMVar9->Text);
					iVar6 = x + iVar6;
					OutputString(pMVar9->Text, 1, x, y_00, y, r, 0x80, b);
					pString = SfxVolumeText;
				LAB_0006c9ec:
					OutputString(pString, 1, iVar6 + 10, y_00, y, r, 0x80, b);
				}

				y_00 = y_00 + 0xf;
				uVar5 = (uint)pMVar10->NumItems;
			}
			pMVar9 = pMVar9 + 1;
			i = i + 1;
		} while (i < (int)uVar5);
	}
	
	null = (POLY_FT3 *)current->primptr;
	setPolyFT3(null);
	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = 0;

	addPrim(current->ot, null);

	current->primptr += sizeof(POLY_FT3);
	poly = (POLY_F4*)current->primptr;
	
	setPolyF4(poly);
	sVar8 = sVar1 + sVar2 + 5;	// x + w
	sVar3 = (pMVar10->Bound).y;

	poly->x0 = sVar1 + -5;
	poly->x1 = sVar8;
	poly->y0 = sVar3 + -5;
	poly->x2 = sVar1 + -5;

	poly->y1 = sVar3 + -5;
	poly->y2 = sVar3 + (pMVar10->Bound).h;

	poly->x3 = sVar8;
	poly->y3 = sVar3 + (pMVar10->Bound).h;

	poly->r0 = '\x10';
	poly->g0 = '\x10';
	poly->b0 = '\x10';

	setSemiTrans(poly, 1);

	addPrim(current->ot, poly);
	current->primptr += sizeof(POLY_F4);

}

// decompiled code
// original method signature: 
// void /*$ra*/ ControlMenu()
 // line 1543, offset 0x0006cbe8
	/* begin block 1 */
		// Start line: 1545
		// Start offset: 0x0006CBE8
		// Variables:
	// 		static int debounce; // offset 0x30
	// 		unsigned short paddata; // $a2
	// 		unsigned short paddirect; // $a3

		/* begin block 1.1 */
			// Start line: 1596
			// Start offset: 0x0006CCD4
			// Variables:
		// 		int doit; // $v1
		/* end block 1.1 */
		// End offset: 0x0006CD78
		// End Line: 1621

		/* begin block 1.2 */
			// Start line: 1675
			// Start offset: 0x0006CF54
			// Variables:
		// 		int i; // $a0
		/* end block 1.2 */
		// End offset: 0x0006CFB8
		// End Line: 1682

		/* begin block 1.3 */
			// Start line: 1692
			// Start offset: 0x0006CFD8
			// Variables:
		// 		int i; // $a0
		/* end block 1.3 */
		// End offset: 0x0006D034
		// End Line: 1703
	/* end block 1 */
	// End offset: 0x0006D034
	// End Line: 1705

	/* begin block 2 */
		// Start line: 3196
	/* end block 2 */
	// End Line: 3197

	/* begin block 3 */
		// Start line: 3212
	/* end block 3 */
	// End Line: 3213

	/* begin block 4 */
		// Start line: 3213
	/* end block 4 */
	// End Line: 3214

	/* begin block 5 */
		// Start line: 3233
	/* end block 5 */
	// End Line: 3234

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void ControlMenu(void)
{
	EXIT_VALUE EVar1;
	bool bVar2;
	int iVar3;
	MENU_ITEM *pMVar4;
	ushort uVar5;
	MENU_HEADER *menu;
	ushort uVar6;

	if (playerwithcontrol[2] == 0) 
	{
		uVar5 = Pads[1].dirnew;
		uVar6 = Pads[1].direct;

		if (playerwithcontrol[0] != 0) 
		{
			uVar5 = Pads[0].dirnew;
			uVar6 = Pads[0].direct;
		}
	}
	else 
	{
		uVar5 = Pads[0].dirnew;
		uVar6 = Pads[0].direct;

		if (NumPlayers == 2) 
		{
			uVar5 = Pads[1].dirnew | Pads[0].dirnew;
			uVar6 = Pads[1].direct | Pads[0].direct;
		}
	}

	if (gShowMap != 0) 
	{
		if ((uVar5 & 0x50) == 0)
			return;

		PauseMap(0);
		return;
	}

	static int controlmenu_debounce = 0;

	if (((uVar6 & 0xa000) == 0) || ((ActiveItem[VisibleMenu]->Type & 4) == 0)) 
	{
		controlmenu_debounce = 0;
		if ((uVar5 & 0x1000) != 0)
		{
			ActiveMenuItem--;

			if (ActiveMenuItem < 0) 
				ActiveMenuItem = (uint)ActiveMenu->NumItems - 1;

			ActiveItem[VisibleMenu] = ActiveMenu->MenuItems + ActiveMenuItem;
			return;
		}

		if ((uVar5 & 0x4000) != 0) 
		{
			ActiveMenuItem++;

			if (((uint)ActiveMenu->NumItems - 1) < ActiveMenuItem)
				ActiveMenuItem = 0;

			ActiveItem[VisibleMenu] = ActiveMenu->MenuItems + ActiveMenuItem;
			return;
		}

		if ((uVar5 & 0x40) == 0) 
		{
			if ((uVar5 & 0x10) == 0) 
			{
				if ((uVar5 & 0x800) == 0) 
				{
					controlmenu_debounce = 0;
					return;
				}

				if (VisibleMenu != 0) 
				{
					controlmenu_debounce = 0;
					return;
				}

				iVar3 = 0;
				if (ActiveMenu->NumItems == 0) 
				{
					controlmenu_debounce = 0;
					return;
				}

				pMVar4 = ActiveMenu->MenuItems;
				while (true)
				{
					if (pMVar4->ExitValue == MENU_QUIT_CONTINUE)
					{
						controlmenu_debounce = 0;
						PauseReturnValue = (uint)pMVar4->ExitValue;
						return;
					}

					iVar3++;
					if ((uint)ActiveMenu->NumItems <= iVar3)
						break;

					pMVar4 = ActiveMenu->MenuItems + iVar3;
				}

				controlmenu_debounce = 0;
				return;
			}

			if (VisibleMenu < 1)
			{
				iVar3 = 0;

				if (ActiveMenu->NumItems == 0)
				{
					controlmenu_debounce = 0;
					return;
				}

				EVar1 = ActiveMenu->MenuItems->ExitValue;
				while (true)
				{
					if (EVar1 == MENU_QUIT_CONTINUE)
					{
						controlmenu_debounce = 0;
						PauseReturnValue = (uint)EVar1;
						return;
					}

					iVar3++;

					if ((uint)ActiveMenu->NumItems <= iVar3) 
						break;

					EVar1 = ActiveMenu->MenuItems[iVar3].ExitValue;
				}
				controlmenu_debounce = 0;
				return;
			}
		}
		else 
		{
			pMVar4 = ActiveItem[VisibleMenu];

			if ((pMVar4->Type & 0x40) != 0) 
			{
				menu = pMVar4->SubMenu;
				VisibleMenu = VisibleMenu + 1;
				VisibleMenus[VisibleMenu] = menu;
				SetupMenu(menu, 0);
				return;
			}

			if ((pMVar4->Type & 2) != 0) 
			{
				(*pMVar4->func)(0);
			}

			EVar1 = ActiveItem[VisibleMenu]->ExitValue;

			if (EVar1 == MENU_QUIT_NONE) 
			{
				return;
			}

			if (EVar1 != MENU_QUIT_BACKMENU)
			{
				PauseReturnValue = (uint)ActiveItem[VisibleMenu]->ExitValue;
				return;
			}
		}
		VisibleMenu = VisibleMenu + -1;
		SetupMenu(VisibleMenus[VisibleMenu], 1);
		return;
	}
	bVar2 = false;

	if (controlmenu_debounce < 1)
	{
		iVar3 = 10;
	}
	else
	{
		controlmenu_debounce = controlmenu_debounce + -1;
		iVar3 = 2;

		if (controlmenu_debounce != 0) 
			goto LAB_0006cd08;
	}

	bVar2 = true;
	controlmenu_debounce = iVar3;
LAB_0006cd08:

	if (bVar2)
	{
		if ((uVar6 & 0x8000) == 0)
		{
			(*ActiveItem[VisibleMenu]->func)(1);
		}
		else 
		{
			(*ActiveItem[VisibleMenu]->func)(-1);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PauseMap(int direction /*$a0*/)
 // line 1710, offset 0x0006dad0
	/* begin block 1 */
		// Start line: 4364
	/* end block 1 */
	// End Line: 4365

	/* begin block 2 */
		// Start line: 4869
	/* end block 2 */
	// End Line: 4870

	/* begin block 3 */
		// Start line: 4870
	/* end block 3 */
	// End Line: 4871

// [D]
void PauseMap(int direction)
{
	gShowMap ^= 1;

	ReadControllers();

	map_x_shift = 0;
	map_z_shift = 0;

	if (gShowMap == 0)
		InitOverheadMap();
}



// decompiled code
// original method signature: 
// void /*$ra*/ SfxVolume(int direction /*$a0*/)
 // line 1725, offset 0x0006db34
	/* begin block 1 */
		// Start line: 1726
		// Start offset: 0x0006DB34
	/* end block 1 */
	// End offset: 0x0006DC04
	// End Line: 1744

	/* begin block 2 */
		// Start line: 4902
	/* end block 2 */
	// End Line: 4903

	/* begin block 3 */
		// Start line: 4905
	/* end block 3 */
	// End Line: 4906

// [D]
void SfxVolume(int direction)
{
	if (direction < 0) 
		gMasterVolume = gMasterVolume + -100;
	else if (0 < direction)
		gMasterVolume = gMasterVolume + 100;

	if (gMasterVolume < -10000) 
		gMasterVolume = -10000;

	if (0 < gMasterVolume) 
		gMasterVolume = 0;

	sprintf(SfxVolumeText, "%d", (int)(10000 + gMasterVolume) / 100);

	SetMasterVolume(gMasterVolume);
}



// decompiled code
// original method signature: 
// void /*$ra*/ MusicVolume(int direction /*$a0*/)
 // line 1746, offset 0x0006dc04
	/* begin block 1 */
		// Start line: 1747
		// Start offset: 0x0006DC04
	/* end block 1 */
	// End offset: 0x0006DCD4
	// End Line: 1765

	/* begin block 2 */
		// Start line: 4942
	/* end block 2 */
	// End Line: 4943

	/* begin block 3 */
		// Start line: 4945
	/* end block 3 */
	// End Line: 4946

	/* begin block 4 */
		// Start line: 4948
	/* end block 4 */
	// End Line: 4949

// [D]
void MusicVolume(int direction)
{
	if (direction < 0)
		gMusicVolume = gMusicVolume + -100;
	else if (0 < direction) 
		gMusicVolume = gMusicVolume + 100;

	if (gMusicVolume < -10000)
		gMusicVolume = -10000;

	if (0 < gMusicVolume) 
		gMusicVolume = 0;

	sprintf(MusicVolumeText, "%d", (int)(10000 + gMusicVolume) / 100);

	SetXMVolume(gMusicVolume);
}



// decompiled code
// original method signature: 
// void /*$ra*/ EnterScoreName()
 // line 1787, offset 0x0006d044
	/* begin block 1 */
		// Start line: 1789
		// Start offset: 0x0006D044
		// Variables:
	// 		SCORE_ENTRY *table; // stack offset -40
	// 		char *username; // $s3
	// 		unsigned short npad; // $a1
	// 		int so; // $s0
	// 		int co; // $s1
	// 		int delay; // $s2
	// 		char c; // $a0
	// 		char toggle; // $s6
	/* end block 1 */
	// End offset: 0x0006D324
	// End Line: 1941

	/* begin block 2 */
		// Start line: 3716
	/* end block 2 */
	// End Line: 3717

	/* begin block 3 */
		// Start line: 3717
	/* end block 3 */
	// End Line: 3718

	/* begin block 4 */
		// Start line: 3718
	/* end block 4 */
	// End Line: 3719

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void EnterScoreName(void)
{
	bool bVar1;
	short uVar2;
	int uVar3;
	char* pcVar4;
	char cVar5;
	int iVar6;
	int uVar7;
	int iVar8;
	char* username;
	int uVar9;
	SCORE_ENTRY* table;

	username = NULL;
	iVar8 = 0;
	gEnteringScore = 1;
	uVar9 = 0;

	if (gScoreEntered == 0) 
	{
		gScorePosition = OnScoreTable(&table);

		if (gScorePosition != -1) 
			username = ScoreName[gScorePosition];
	}
	else 
	{
		OnScoreTable(&table);
		gScorePosition = -1;
	}

	uVar7 = 1;
	iVar6 = 0;

	CreateScoreNames(table, &gPlayerScore, gScorePosition);

	do {
		ReadControllers();
		uVar2 = Pads[0].dirnew;

		if (gScoreEntered == 0)
		{
			if ((Pads[0].dirnew & 0x10) != 0)
			{
				gEnteringScore = 0;
				return;
			}

			if ((Pads[0].direct & 0x20) == 0)
			{
				if ((Pads[0].direct & 0x8000) == 0) 
				{
					if ((Pads[0].direct & 0x2000) == 0)
					{
						iVar8 = 0;
						goto LAB_0006d1e8;
					}

					bVar1 = iVar8 == 0;
					iVar8 = iVar8 + -1;
					if (bVar1) 
					{
						iVar8 = 0x14;
					LAB_0006d1c4:
						uVar9 = 0;
						uVar7 = uVar7 + 1;
					}
					else if (iVar8 < 1)
					{
						iVar8 = 2;
						goto LAB_0006d1c4;
					}

					if (0x43 < uVar7)
						uVar7 = 0;

				}
				else 
				{
					bVar1 = iVar8 == 0;
					iVar8 = iVar8 + -1;

					if (bVar1) 
					{
						iVar8 = 0x14;
					LAB_0006d184:
						uVar9 = 0;
						uVar7 = uVar7 - 1;
					}
					else if (iVar8 < 1) 
					{
						iVar8 = 2;
						goto LAB_0006d184;
					}

					if ((int)uVar7 < 0)
						uVar7 = 0x43;
				}
			}
			else 
			{
				iVar8 = 1;
				uVar9 = 0;
				uVar7 = 0x43;
			}

		LAB_0006d1e8:
			cVar5 = validchars[uVar7];
			uVar3 = uVar9 + 1;

			if (iVar6 == 5)
				cVar5 = -2;

			uVar9 = uVar3 & 0xff;

			if ((uVar3 & 4) == 0)
			{
				if (cVar5 == ' ')
					username[iVar6] = '.';
				else
					username[iVar6] = cVar5;
			}
			else 
			{
				username[iVar6] = 0;
			}

			pcVar4 = username + iVar6;

			if ((uVar2 & 0x80) != 0) 
			{
				if (0 < iVar6)
					iVar6--;

				pcVar4 = username + iVar6;
				*pcVar4 = 0;
				pcVar4[1] = 0;
			}

			if ((uVar2 & 0x40) != 0) 
			{
				if (cVar5 == -2) 
				{
					*pcVar4 = 0;
					strcpy(gPlayerScore.name, username);
					AddScoreToTable(table, gScorePosition);
					sprintf(EnterScoreText, "View Table");
					sprintf(EnterNameText, "High Scores");
					gEnteringScore = 0;
					gScoreEntered = 1;
					return;
				}

				if (cVar5 == -1) 
				{
					if (0 < iVar6)
						iVar6--;

					username[iVar6] = 0;
					username[iVar6+1] = 0;
				}
				else if (iVar6 < 5) 
				{
					iVar6 = iVar6 + 1;
					*pcVar4 = cVar5;
					username[iVar6] = 0;
				}
			}
		}
		else if((Pads[0].dirnew & 0x50) != 0)
		{
			gEnteringScore = 0;
			return;
		}

		DrawGame();
	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawHighScoreMenu(int selection /*stack 0*/)
 // line 2020, offset 0x0006d694
	/* begin block 1 */
		// Start line: 2021
		// Start offset: 0x0006D694
		// Variables:
	// 		POLY_FT3 *null; // $a0
	// 		char text[4]; // stack offset -48
	// 		unsigned char r; // $s3
	// 		unsigned char g; // $s5
	// 		unsigned char b; // $s2
	// 		int i; // $s0
	// 		int ypos; // $s4
	/* end block 1 */
	// End offset: 0x0006D9B0
	// End Line: 2075

	/* begin block 2 */
		// Start line: 4486
	/* end block 2 */
	// End Line: 4487

// [D]
void DrawHighScoreMenu(int selection)
{
	POLY_FT3* null;
	POLY_F4* prim;
	int iVar1;
	int iVar2;
	int b;
	int r;
	int y;
	int iVar3;
	char text[8];

	OutputString(EnterNameText, 2, 0xa0, 0x46, 0, 0x80, 0x20, 0x20);
	OutputString("Name", 1, 0x28, 0x5a, 0, 0x80, 0x80, 0x20);
	OutputString("Time", 4, 0x118, 0x5a, 0, 0x80, 0x80, 0x20);
	y = 0x6e;
	iVar3 = 0;
	iVar1 = 0;
	iVar2 = 0;
	do {
		r = 0x80;
		if (iVar1 == selection) 
		{
			r = 0;
			b = 0;
		}
		else
		{
			b = 0x80;
		}

		sprintf(text, "%d", iVar2);

		OutputString(text, 1, 0x28, y, 0, r, 0x80, b);
		OutputString(ScoreName[iVar2], 1, 0x3c, y, 0, r, 0x80, b);
		OutputString(ScoreItems[iVar2], 4, 0xdc, y, 0, r, 0x80, b);
		OutputString(ScoreTime[iVar2], 4, 0x118, y, 0, r, 0x80, b);

		y = y + 0xf;

		iVar2++;
	} while (iVar2 < 5);

	null = (POLY_FT3*)current->primptr;

	setPolyFT3(null);

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = 0;

	addPrim(current->ot, null);

	current->primptr += sizeof(POLY_FT3);

	prim = (POLY_F4*)current->primptr;
	setPolyF4(prim);
	setSemiTrans(prim, 1); // code is 43 '+';

	prim->y0 = 0x41;
	prim->y1 = 0x41;
	prim->y2 = 0xc5;
	prim->y3 = 0xc5;
	prim->x0 = 0x1a;
	prim->x1 = 0x126;
	prim->x2 = 0x1a;
	prim->x3 = 0x126;
	prim->r0 = 16;
	prim->g0 = 16;
	prim->b0 = 16;

	addPrim(current->ot, prim);
	current->primptr += sizeof(POLY_F4);
}

//*Offset 0x6D324, from D : \driver2\game\C\PAUSE.C(lines 1943..2011)
//* Stack frame base $sp, size 80
//* Saved registers at offset - 4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
//* /
//void /*$ra*/ CreateScoreNames(SCORE_ENTRY* table /*$s0*/, PLAYER_SCORE* score /*stack 4*/, int position /*stack 8*/)
//{ // line 1, offset 0x6d324
//	char* text; // $s1
//	int min; // $t1
//	int frac; // $v0
//	int i; // $s5
//} // line 69, offset 0x6d664

// [D]
void CreateScoreNames(SCORE_ENTRY* table, PLAYER_SCORE* score, int position)
{
	int time;
	char* text;
	int i;

	switch (GameType) 
	{
		case GAME_PURSUIT:
		case GAME_GETAWAY:
		case GAME_CHECKPOINT:
		case GAME_SURVIVAL:
			text = NULL;
			break;
		case GAME_GATERACE:
			text = "Gates";
			break;
		case GAME_TRAILBLAZER:
			text = "Cones";
			break;
		default:
			return;
	}

	i = 0;

	do {
		if (i == position)
		{
			time = score->time;
			if (time == -1)
				sprintf(ScoreTime[i], "-:--.--");
			else
				sprintf(ScoreTime[i], "%d:%02d.%02d", time / 180000, time / 3000 + (time / 180000) * -0x3c, (time % 3000) / 0x1e);

			ScoreItems[i][0] = '\0';

			if ((text != NULL) && (score->items != -1))
				sprintf(ScoreItems[i], "%d %s", score->items, text);

			ClearMem(ScoreName[i], 7);
		}
		else 
		{
			time = table->time;

			if (time == -1)
				sprintf(ScoreTime[i], "-:--.--");
			else
				sprintf(ScoreTime[i], "%d:%02d.%02d", time / 180000, time / 3000 + (time / 180000) * -0x3c, (time % 3000) / 0x1e);

			ScoreItems[i][0] = '\0';

			if ((text != NULL) && (table->items != -1))
				sprintf(ScoreItems[i], "%d %s", table->items, text);

			sprintf(ScoreName[i], "%s", table->name);
			table = table + 1;
		}

		i++;
	} while (i < 5);

}