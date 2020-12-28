#include "driver2.h"
#include "pause.h"
#include "system.h"
#include "mission.h"
#include "overlay.h"
#include "pres.h"
#include "pad.h"
#include "main.h"
#include "glaunch.h"
#include "scores.h"
#include "sound.h"
#include "cutscene.h"
#include "replays.h"
#include "overmap.h"
#include "handling.h"
#include "MemCard/main.h"

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

#define PAUSE_MENU_LEVELS 3

static MENU_ITEM* ActiveItem[PAUSE_MENU_LEVELS];
static MENU_HEADER* VisibleMenus[PAUSE_MENU_LEVELS];
static MENU_HEADER* ActiveMenu;
static int ActiveMenuItem;
static int VisibleMenu;

static char SfxVolumeText[8];
static char MusicVolumeText[8];

static char ScoreTime[5][16];
static char ScoreItems[5][16];
static char ScoreName[5][7];

static char validchars[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-+!\xFF\xFE";

void PauseMap(int direction);
void SfxVolume(int direction);
void MusicVolume(int direction);
void SaveReplay(int direction);
void SaveGame(int direction);
void SkipCutscene(int direction);

void EnterScoreName();
void CreateScoreNames(SCORE_ENTRY *table, PLAYER_SCORE *score, int position);
void DrawHighScoreMenu(int selection); 
void EnterName();

char EnterScoreText[32] = { 0 };

enum MenuItemType
{
	//PAUSE_TYPE_ACTIVE		= (1 << 0),		// suggested - USUSED flag
	PAUSE_TYPE_FUNC			= (1 << 1),		// simple function calling when pressing Cross
	PAUSE_TYPE_DIRFUNC		= (1 << 2),		// function calling with direction (left/right)
	PAUSE_TYPE_SFXVOLUME	= (1 << 3),
	PAUSE_TYPE_MUSICVOLUME	= (1 << 4),
	PAUSE_TYPE_SUBMENU		= (1 << 6),
	PAUSE_TYPE_ENDITEMS		= (1 << 7),
};

#if defined(_DEBUG) || defined(DEBUG_OPTIONS)

#ifdef CUTSCENE_RECORDER
extern void NextCutsceneRecorderPlayer(int dir);
extern char gCutsceneRecorderPauseText[64];

extern void NextChase(int dir);
extern char gCurrentChasePauseText[64];
#endif

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
	wantedTimeOfDay = 1;
	gTimeOfDay = 1;
	gWantNight = 0;
	LoadSky();
}

void DebugTimeOfDayNight(int direction)
{
	wantedTimeOfDay = 3;
	gTimeOfDay = 3;
	gWantNight = 1;
	LoadSky();
}

void DebugTimeOfDayDusk(int direction)
{
	wantedTimeOfDay = 0;
	gTimeOfDay = 0;
	gWantNight = 0;
	LoadSky();
}

void DebugTimeOfDayDawn(int direction)
{
	wantedTimeOfDay = 2;
	gTimeOfDay = 2;
	gWantNight = 0;
	LoadSky();
}

void DebugTimeOfDayRain(int direction)
{
	//extern int weather;
	//weather ^= weather;
	gWeather ^= 1;
	wantedWeather = gWeather;

	if (gWeather == 1)
		wetness = 7000;
	else
		wetness = 0;

	LoadSky();
}

MENU_ITEM DebugTimeOfDayItems[] =
{
	{ "Day",	PAUSE_TYPE_FUNC, 	2,	DebugTimeOfDayDay,	MENU_QUIT_NONE,		NULL },
	{ "Night", 	PAUSE_TYPE_FUNC,  2,  DebugTimeOfDayNight,MENU_QUIT_NONE,		NULL },
	{ "Dusk", 	PAUSE_TYPE_FUNC, 	2,  DebugTimeOfDayDusk, MENU_QUIT_NONE,		NULL },
	{ "Dawn", 	PAUSE_TYPE_FUNC, 	2,  DebugTimeOfDayDawn,	MENU_QUIT_NONE,		NULL },
	{ "Rain", 	PAUSE_TYPE_FUNC, 	2,  DebugTimeOfDayRain,	MENU_QUIT_NONE,		NULL },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_HEADER DebugTimeOfDayHeader =
{ "Time Of Day", { 0, 0, 0, 0 }, 0u, DebugTimeOfDayItems };

MENU_ITEM DebugJustForFunItems[] =
{
	{ "Secret Car Fun", PAUSE_TYPE_FUNC,	2,  ToggleSecretCarFun, MENU_QUIT_RESTART,	NULL },
	{ "Mini Cars", PAUSE_TYPE_FUNC,	2,  ToggleMiniCars, MENU_QUIT_NONE,	NULL },
	{ "Jericho Mode",	PAUSE_TYPE_FUNC,	2,  ToggleJerichoMode,	MENU_QUIT_NONE,		NULL },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_HEADER DebugJustForFunHeader =
{ "Just for fun", { 0, 0, 0, 0 }, 0u, DebugJustForFunItems };

MENU_ITEM DebugOptionsItems[] =
{
#ifdef CUTSCENE_RECORDER
	//{ gCutsceneRecorderPauseText, 5u, 2u, (pauseFunc)&NextCutsceneRecorderPlayer, MENU_QUIT_NONE, NULL },
	{ gCurrentChasePauseText, 5u, 2u, (pauseFunc)&NextChase, MENU_QUIT_NONE, NULL },
#endif
	{ "Display position", PAUSE_TYPE_FUNC, 	2,	SetDisplayPosition,		MENU_QUIT_NONE,		NULL},
	{ "Back on Wheels",	PAUSE_TYPE_FUNC, 	2,	SetRightWayUp,		MENU_QUIT_NONE,		NULL},
	{ "Time of Day", 	PAUSE_TYPE_SUBMENU, 2,  NULL,		  		MENU_QUIT_NONE,		&DebugTimeOfDayHeader },
	{ "Fun Cheats", 	PAUSE_TYPE_SUBMENU, 2,  NULL,		  		MENU_QUIT_NONE,		&DebugJustForFunHeader },
	{ "Invincibility", 	PAUSE_TYPE_FUNC, 	2,  ToggleInvincibility,MENU_QUIT_NONE,		NULL},
	{ "Immunity", 		PAUSE_TYPE_FUNC, 	2,  ToggleImmunity,		MENU_QUIT_NONE,		NULL},
	{ "Puppy Dog Cops",	PAUSE_TYPE_FUNC,	2,  TogglePuppyDogCops,	MENU_QUIT_NONE,		NULL },
	{ "Toggle Overlay",	PAUSE_TYPE_FUNC,	2,  ToggleOverlays,		MENU_QUIT_NONE,		NULL },
	{ "Player Ghost", 	PAUSE_TYPE_FUNC, 	2,  TogglePlayerGhost,	MENU_QUIT_NONE,		NULL },
	{ "Next Mission",	0, 					2,  NULL,				MENU_QUIT_NEXTMISSION, 	NULL },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_HEADER DebugOptionsHeader =
{ "Debug Options", { 0, 0, 0, 0 }, 0u, DebugOptionsItems };
#endif

MENU_ITEM YesNoRestartItems[] =
{
	{ G_LTXT_ID(GTXT_NO), 1u, 2u, NULL, MENU_QUIT_BACKMENU, NULL },
	{ G_LTXT_ID(GTXT_YES), 1u, 2u, NULL, MENU_QUIT_RESTART, NULL },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM YesNoQuitItems[] =
{
	{ G_LTXT_ID(GTXT_NO), 1u, 2u, NULL, MENU_QUIT_BACKMENU, NULL },
	{ G_LTXT_ID(GTXT_YES), 1u, 2u, NULL, MENU_QUIT_QUIT, NULL },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_HEADER YesNoRestartHeader =
{ G_LTXT_ID(GTXT_AreYouSure), { 0, 0, 0, 0 }, 0u, YesNoRestartItems };

MENU_HEADER YesNoQuitHeader =
{ G_LTXT_ID(GTXT_AreYouSure), { 0, 0, 0, 0 }, 0u, YesNoQuitItems };

MENU_ITEM MainPauseItems[] =
{
	{ G_LTXT_ID(GTXT_Continue), 1u, 2u, NULL, MENU_QUIT_CONTINUE, NULL },
	{ G_LTXT_ID(GTXT_ShowMap), PAUSE_TYPE_FUNC, 2u, (pauseFunc)&PauseMap, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_Restart), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ G_LTXT_ID(GTXT_SfxVolume), PAUSE_TYPE_SFXVOLUME | PAUSE_TYPE_DIRFUNC, 2u, (pauseFunc)&SfxVolume, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_MusicVolume), PAUSE_TYPE_MUSICVOLUME | PAUSE_TYPE_DIRFUNC, 2u, (pauseFunc)&MusicVolume, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_FilmDirector), 1u, 2u, NULL, MENU_QUIT_DIRECTOR, NULL},
	{ G_LTXT_ID(GTXT_QuickReplay),1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
#if defined(_DEBUG) || defined(DEBUG_OPTIONS)
	{ "Debug Options", PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &DebugOptionsHeader },
#endif
	{ G_LTXT_ID(GTXT_Exit), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MultiplayerPauseItems[] =
{
	{ G_LTXT_ID(GTXT_Continue), 1u, 2u, NULL, MENU_QUIT_CONTINUE, NULL },
	{ G_LTXT_ID(GTXT_Restart), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ G_LTXT_ID(GTXT_SfxVolume), PAUSE_TYPE_SFXVOLUME | PAUSE_TYPE_DIRFUNC, 2u, (pauseFunc)&SfxVolume, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_MusicVolume), PAUSE_TYPE_MUSICVOLUME | PAUSE_TYPE_DIRFUNC, 2u, (pauseFunc)&MusicVolume, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_QuickReplay),1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ G_LTXT_ID(GTXT_Exit), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM CutscenePauseItems[] =
{
	{ G_LTXT_ID(GTXT_Continue), 1u, 2u, NULL, MENU_QUIT_CONTINUE, NULL },
	{ G_LTXT_ID(GTXT_SkipCutscene), PAUSE_TYPE_FUNC, 2u, (pauseFunc)&SkipCutscene, MENU_QUIT_CONTINUE, NULL },
	{ G_LTXT_ID(GTXT_Restart), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ G_LTXT_ID(GTXT_SfxVolume), PAUSE_TYPE_SFXVOLUME | PAUSE_TYPE_DIRFUNC, 2u, (pauseFunc)&SfxVolume, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_MusicVolume), PAUSE_TYPE_MUSICVOLUME | PAUSE_TYPE_DIRFUNC, 2u, (pauseFunc)&MusicVolume, MENU_QUIT_NONE, NULL },
#if defined(_DEBUG) || defined(DEBUG_OPTIONS)
	{ "Debug Options", PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &DebugOptionsHeader },
#endif
	{ G_LTXT_ID(GTXT_Exit), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MissionCompleteItems[] =
{
#ifdef PSX
	{ G_LTXT_ID(GTXT_SaveGame), 3u, 2u, (pauseFunc)&SaveGame, MENU_QUIT_NONE, NULL },
#endif
	{ G_LTXT_ID(GTXT_Continue), 1u, 2u, NULL, MENU_QUIT_NEXTMISSION, NULL },
	{ G_LTXT_ID(GTXT_FilmDirector),1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ G_LTXT_ID(GTXT_QuickReplay),1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ G_LTXT_ID(GTXT_SaveReplay), PAUSE_TYPE_FUNC, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_Restart), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ G_LTXT_ID(GTXT_Exit), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MissionFailedItems[6] =
{
	{ G_LTXT_ID(GTXT_FilmDirector),1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ G_LTXT_ID(GTXT_QuickReplay),1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ G_LTXT_ID(GTXT_Exit), 3u, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_RetryMission),PAUSE_TYPE_SUBMENU,2u,NULL,MENU_QUIT_NONE,&YesNoRestartHeader },
	{ G_LTXT_ID(GTXT_Exit), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM TakeARideFinishedItems[] =
{
	{ G_LTXT_ID(GTXT_Restart), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ G_LTXT_ID(GTXT_FilmDirector),1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ G_LTXT_ID(GTXT_QuickReplay),1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ G_LTXT_ID(GTXT_SaveReplay), PAUSE_TYPE_FUNC, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_Exit), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM DrivingGameFinishedItems[] =
{
	{ G_LTXT_ID(GTXT_PlayAgain), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ EnterScoreText, 3u, 2u, (pauseFunc)&EnterName, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_FilmDirector),1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ G_LTXT_ID(GTXT_QuickReplay),1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ G_LTXT_ID(GTXT_SaveReplay), PAUSE_TYPE_FUNC, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_Exit), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM MultiplayerFinishedItems[] =
{
	{ G_LTXT_ID(GTXT_PlayAgain), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ G_LTXT_ID(GTXT_QuickReplay),1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ G_LTXT_ID(GTXT_SaveReplay), PAUSE_TYPE_FUNC, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_Exit), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM ChaseGameFinishedItems[] =
{
	{ G_LTXT_ID(GTXT_PlayAgain), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoRestartHeader },
	{ G_LTXT_ID(GTXT_FilmDirector),1u,2u,NULL,MENU_QUIT_DIRECTOR,NULL},
	{ G_LTXT_ID(GTXT_QuickReplay),1u,2u,NULL,MENU_QUIT_QUICKREPLAY,NULL},
	{ G_LTXT_ID(GTXT_SaveReplay), PAUSE_TYPE_FUNC, 2u, (pauseFunc)&SaveReplay, MENU_QUIT_NONE, NULL },
	{ G_LTXT_ID(GTXT_Exit), PAUSE_TYPE_SUBMENU, 2u, NULL, MENU_QUIT_NONE, &YesNoQuitHeader },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM NoPadItems[] =
{
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL}
};

MENU_ITEM NoMultiPadItems[] =
{
	{ "Exit", 1u, 2u, NULL, MENU_QUIT_QUIT, NULL },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};

MENU_ITEM InvalidPadItems[] =
{
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL}
};

MENU_ITEM InvalidMultiPadItems[] =
{
	{ G_LTXT_ID(GTXT_Exit), 1u, 2u, NULL, MENU_QUIT_QUIT, NULL },
	{ NULL, PAUSE_TYPE_ENDITEMS, 0u, NULL, MENU_QUIT_NONE, NULL }
};


MENU_HEADER PauseMenuHeader =
{ G_LTXT_ID(GTXT_Paused), { 0, 0, 0, 0 }, 0u, MainPauseItems };

MENU_HEADER MultiplayerPauseHeader =
{ G_LTXT_ID(GTXT_Paused), { 0, 0, 0, 0 }, 0u, MultiplayerPauseItems };

MENU_HEADER CutscenePauseMenuHeader =
{ G_LTXT_ID(GTXT_Paused), { 0, 0, 0, 0 }, 0u, CutscenePauseItems };

MENU_HEADER MissionCompleteHeader =
{ G_LTXT_ID(GTXT_MissionSuccessful), { 0, 0, 0, 0 }, 0u, MissionCompleteItems };

MENU_HEADER MissionFailedHeader =
{ G_LTXT_ID(GTXT_MissionFailed), { 0, 0, 0, 0 }, 0u, MissionFailedItems };

MENU_HEADER TakeARideFinishedHeader =
{ G_LTXT_ID(GTXT_GameOver), { 0, 0, 0, 0 }, 0u, TakeARideFinishedItems };

MENU_HEADER DrivingGameFinishedHeader =
{ G_LTXT_ID(GTXT_GameOver), { 0, 0, 0, 0 }, 0u, DrivingGameFinishedItems };

MENU_HEADER MultiplayerFinishedHeader =
{ G_LTXT_ID(GTXT_GameOver), { 0, 0, 0, 0 }, 0u, MultiplayerFinishedItems };

MENU_HEADER ChaseGameFinishedHeader =
{ G_LTXT_ID(GTXT_GameOver), { 0, 0, 0, 0 }, 0u, ChaseGameFinishedItems };

MENU_HEADER NoPadHeader =
{
	G_LTXT_ID(GTXT_InsertController1),
	{ 0, 0, 0, 0 },
	0u,
	NoPadItems
};

MENU_HEADER NoMultiPadHeader =
{
	G_LTXT_ID(GTXT_InsertController2),
	{ 0, 0, 0, 0 },
	0u,
	NoMultiPadItems
};

MENU_HEADER InvalidPadHeader =
{
	G_LTXT_ID(GTXT_IncorrectController1),
	{ 0, 0, 0, 0 },
	0u,
	InvalidPadItems
};

MENU_HEADER InvalidMultiPadHeader =
{
	G_LTXT_ID(GTXT_IncorrectController2),
	{ 0, 0, 0, 0 },
	0u,
	InvalidMultiPadItems
};

int playerwithcontrol[3] = { 0 };

void SkipCutscene(int direction)
{
	gSkipInGameCutscene = 1;
}

// [D] [T]
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
	else
	{
		sprintf(filename, "CHASE.D2RP");// , gCurrentMissionNumber);
	}
#else
	sprintf(filename, "CHASE.D2RP", gCurrentMissionNumber);
#endif
	FILE* fp = fopen(filename, "wb");
	if (fp)
	{
		printInfo("Saving replay '%s'\n", filename);
		fwrite(_other_buffer, 1, size, fp);
		fclose(fp);
	}
#endif
}

// [D] [T]
void SaveGame(int direction)
{
	CallMemoryCard(0x20, 1);
}

// [D] [T]
void EnterName(void)
{
	EnterScoreName();
}

// [D] [T]
int MaxMenuStringLength(MENU_HEADER *pMenu)
{
	int max;
	int temp;
	MENU_ITEM *pItems;

	pItems = pMenu->MenuItems;
	max = StringWidth(GET_GAME_TXT(pMenu->Title));

	while ((pItems->Type & PAUSE_TYPE_ENDITEMS) == 0)
	{
		temp = StringWidth(GET_GAME_TXT(pItems->Text));

		if (pItems->Type & (PAUSE_TYPE_SFXVOLUME | PAUSE_TYPE_MUSICVOLUME)) 
			temp = temp + StringWidth(" 100");

		if (max < temp)
			max = temp;

		pItems++;
	}

	return max;
}


// [D] [T]
void SetupMenu(MENU_HEADER *menu, int back)
{
	int len;
	MENU_ITEM *pItem;
	int numItems;

	numItems = 0;

	ActiveMenuItem = 0;

	pItem = menu->MenuItems;
	while (pItem->Type != PAUSE_TYPE_ENDITEMS)
	{
		if (back && pItem == ActiveItem[VisibleMenu])
			ActiveMenuItem = numItems;

		numItems++;
		pItem++;
	}

	ActiveMenu = menu;
	ActiveMenu->NumItems = numItems;

	len = MaxMenuStringLength(ActiveMenu);

	ActiveMenu->Bound.x = ((304 - len) / 2) - 4;
	ActiveMenu->Bound.w = len + 24;
	ActiveMenu->Bound.y = MAX(48, ((numItems + 1) * -15 + 256) / 2);
	ActiveMenu->Bound.h = (numItems + 1) * 15 + 10;

	ActiveItem[VisibleMenu] = &ActiveMenu->MenuItems[ActiveMenuItem];
}

// [D] [T]
void InitaliseMenu(PAUSEMODE mode)
{
	MENU_HEADER* pNewMenu;
	int i;

	for (i = 0; i < PAUSE_MENU_LEVELS; i++)
	{
		ActiveItem[i] = NULL;
		VisibleMenus[i] = NULL;
	}

	pNewMenu = NULL;

	allownameentry = 0;

	switch (mode) 
	{
		case PAUSEMODE_PAUSE:
		case PAUSEMODE_PAUSEP1:
		case PAUSEMODE_PAUSEP2:
			if (NumPlayers == 1 && gMultiplayerLevels == 0) 
			{
				if (gInGameCutsceneActive == 0)
					pNewMenu = &PauseMenuHeader;
				else 
					pNewMenu = &CutscenePauseMenuHeader;
			}
			else 
				pNewMenu = &MultiplayerPauseHeader;

			break;
		case PAUSEMODE_GAMEOVER:
			switch (GameType) 
			{
				case GAME_PURSUIT:
					pNewMenu = &ChaseGameFinishedHeader;
					gMissionCompletionState = mode;
					break;
				case GAME_GETAWAY:
				case GAME_CHECKPOINT:
					if (NumPlayers == 1)
					{
						pNewMenu = &DrivingGameFinishedHeader;
						gMissionCompletionState = mode;
					}
					else
					{
						pNewMenu = &MultiplayerFinishedHeader;
						gMissionCompletionState = mode;
					}
					break;
				case GAME_GATERACE:
				case GAME_TRAILBLAZER:
				case GAME_SURVIVAL:
					if (NumPlayers == 1)
					{
						pNewMenu = &DrivingGameFinishedHeader;
						gMissionCompletionState = mode;
						allownameentry = 1;
					}
					else
					{
						pNewMenu = &MultiplayerFinishedHeader;
						gMissionCompletionState = mode;
					}
					break;
				default:
					if (NumPlayers == 1)
					{
						pNewMenu = &TakeARideFinishedHeader;
						gMissionCompletionState = mode;
					}
					else
					{
						pNewMenu = &MultiplayerFinishedHeader;
						gMissionCompletionState = mode;
					}
					break;
			}
			break;
		case PAUSEMODE_COMPLETE:

			switch (GameType) 
			{
				case GAME_MISSION:
					pNewMenu = &MissionCompleteHeader;
					gMissionCompletionState = mode;
					break;
				case GAME_GETAWAY:
				case GAME_GATERACE:
				case GAME_CHECKPOINT:
				case GAME_TRAILBLAZER:
				case GAME_SURVIVAL:
				case GAME_COPSANDROBBERS:
				case GAME_CAPTURETHEFLAG:
					if (NumPlayers == 1) 
					{
						pNewMenu = &DrivingGameFinishedHeader;
						gMissionCompletionState = mode;
						allownameentry = 1;
					}
					else
					{
						pNewMenu = &MultiplayerFinishedHeader;
						gMissionCompletionState = mode;
					}
					break;
				case GAME_PURSUIT:
					pNewMenu = &ChaseGameFinishedHeader;
					gMissionCompletionState = mode;
					break;
				default:
					if (NumPlayers == 1)
					{
						pNewMenu = &TakeARideFinishedHeader;
						gMissionCompletionState = mode;
					}
					else
					{
						pNewMenu = &MultiplayerFinishedHeader;
						gMissionCompletionState = mode;
					}
					break;
			}
			break;
		case PAUSEMODE_PADERROR:
			if (pad_connected < 0) 
			{
				if (NumPlayers == 1) 
					pNewMenu = &InvalidPadHeader;
				else
					pNewMenu = &InvalidMultiPadHeader;

				if (Pads[0].type == 1)
					pNewMenu->Title = G_LTXT(GTXT_IncorrectController1);
				else
					pNewMenu->Title = G_LTXT(GTXT_IncorrectController2);
			}
			else 
			{
				if (NumPlayers == 1) 
					pNewMenu = &NoPadHeader;
				else
					pNewMenu = &NoMultiPadHeader;

				if (Pads[0].type == 0)
					pNewMenu->Title = G_LTXT(GTXT_InsertController1);
				else
					pNewMenu->Title = G_LTXT(GTXT_InsertController2);
			}
			break;
	}

	// [A]
	if(pNewMenu)
	{
		VisibleMenu = 0;
		VisibleMenus[VisibleMenu] = pNewMenu;

		SetupMenu(pNewMenu, 0);
	}
	else
	{
		printError("pNewMenu is NULL!\n");
	}
}

// [D] [T]
void DrawVisibleMenus(void)
{
	int width;
	int itemXpos;
	POLY_FT3 *null;
	POLY_F4 *poly;
	MENU_ITEM *pItem;
	MENU_HEADER *pActive;
	int r, b;
	int i;
	int xpos, ypos;
	int menuWidth;
	
	int x1, x2, y1, y2;
	static int maxPercentageWidth = StringWidth(" 100");

	if (NumPlayers > 1)
	{
		SetFullscreenDrawing();
	}

	pActive = VisibleMenus[VisibleMenu];

	xpos = pActive->Bound.x;
	ypos = pActive->Bound.y;
	menuWidth = pActive->Bound.w;
	
	if (pActive->Title)
	{
		OutputString(GET_GAME_TXT(pActive->Title), 2, xpos, ypos, menuWidth, 128, 32, 32);

		ypos += 15;
	}

	// show all menu items
	for (i = 0; i < pActive->NumItems; i++)
	{
		pItem = &pActive->MenuItems[i];

		if (!pItem->Text)
			continue;
	
		if (pItem == ActiveItem[VisibleMenu])
		{
			r = 0;
			b = 0;
		}
		else
		{
			b = 128;
			r = 128;
		}

		if(pItem->Type & (PAUSE_TYPE_SFXVOLUME | PAUSE_TYPE_MUSICVOLUME))
		{
			width = StringWidth(GET_GAME_TXT(pItem->Text));

			itemXpos = xpos + ((menuWidth - width) - maxPercentageWidth) / 2;

			OutputString(GET_GAME_TXT(pItem->Text), 1, itemXpos, ypos, menuWidth, r, 128, b);
			
			if (pItem->Type & PAUSE_TYPE_SFXVOLUME)
				OutputString(SfxVolumeText, 1, itemXpos + width + 10, ypos, menuWidth, r, 128, b);
			else if (pItem->Type & PAUSE_TYPE_MUSICVOLUME)
				OutputString(MusicVolumeText, 1, itemXpos + width + 10, ypos, menuWidth, r, 128, b);
		}
		else
		{
			OutputString(GET_GAME_TXT(pItem->Text), pItem->Justify, xpos, ypos, menuWidth, r, 128, b);
		}

		ypos += 15;
	}

	poly = (POLY_F4*)current->primptr;

	ypos = pActive->Bound.y;
	
	setPolyF4(poly);
	x1 = xpos - 5;
	x2 = xpos + menuWidth + 5;

	y1 = ypos - 5;
	y2 = ypos + pActive->Bound.h;

	poly->x0 = x1;
	poly->x1 = x2;
	poly->y0 = y1;
	poly->x2 = x1;

	poly->y1 = y1;
	poly->y2 = y2;

	poly->x3 = x2;
	poly->y3 = y2;

	poly->r0 = 16;
	poly->g0 = 16;
	poly->b0 = 16;

	setSemiTrans(poly, 1);

	addPrim(current->ot, poly);
	current->primptr += sizeof(POLY_F4);

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


}

// [D] [T]
void ControlMenu(void)
{
	static int controlmenu_debounce = 0;
	MENU_ITEM* pItem;
	int i;
	ushort paddata;
	MENU_HEADER* menu;
	ushort paddirect;
	int doit;

	if (playerwithcontrol[2] == 0)
	{
		paddata = Pads[1].dirnew;
		paddirect = Pads[1].direct;

		if (playerwithcontrol[0])
		{
			paddata = Pads[0].dirnew;
			paddirect = Pads[0].direct;
		}
	}
	else
	{
		paddata = Pads[0].dirnew;
		paddirect = Pads[0].direct;
	
		if (NumPlayers == 2)
		{
			paddata = Pads[1].dirnew | Pads[0].dirnew;
			paddirect = Pads[1].direct | Pads[0].direct;
		}
	}

	// toggle map off
	if (gShowMap)
	{
		if (paddata & 0x50)
			PauseMap(0);

		return;
	}

	pItem = ActiveItem[VisibleMenu];

	if ((paddirect & 0xA000) && (pItem->Type & PAUSE_TYPE_DIRFUNC))
	{
		doit = 0;

		if (controlmenu_debounce == 0)
		{
			doit = 1;
			controlmenu_debounce = 10;
		}
		else
		{
			controlmenu_debounce--;

			if (controlmenu_debounce == 0)
			{
				doit = 1;
				controlmenu_debounce = 2;
			}
		}

		if (doit)
		{
			// left/right
			(*pItem->func)((paddirect & 0x8000) ? -1 : 1);
		}

		return;
	}

	controlmenu_debounce = 0;

#ifndef PSX
	// Pause fix for PC mapping
	if ((paddata & 0x10) && paddata & (0x1000 | 0x4000))
	{
		paddata = 0;
	}
#endif

	if (paddata & 0x1000)
	{
		// go up
		ActiveMenuItem--;
		
		if (ActiveMenuItem < 0)
			ActiveMenuItem = ActiveMenu->NumItems - 1;

		ActiveItem[VisibleMenu] = &ActiveMenu->MenuItems[ActiveMenuItem];
	}
	else if (paddata & 0x4000)
	{
		// go down
		ActiveMenuItem++;
		
		if (ActiveMenuItem > ActiveMenu->NumItems - 1)
			ActiveMenuItem = 0;

		ActiveItem[VisibleMenu] = &ActiveMenu->MenuItems[ActiveMenuItem];
	}
	else if (paddata & 0x40)
	{
		// Enter submenu
		if (pItem->Type & PAUSE_TYPE_SUBMENU)
		{
			menu = pItem->SubMenu;
	
			VisibleMenu++;
			VisibleMenus[VisibleMenu] = menu;
	
			SetupMenu(menu, 0);
			return;
		}

		// function flag
		if (pItem->Type & PAUSE_TYPE_FUNC)
			(*pItem->func)(0);
			
		if (pItem->ExitValue == MENU_QUIT_NONE)
			return;

		if (pItem->ExitValue == MENU_QUIT_BACKMENU)
		{
			VisibleMenu--;		// go back in menu stack
			SetupMenu(VisibleMenus[VisibleMenu], 1);
		}
		else
			PauseReturnValue = pItem->ExitValue;
	}
	else if ((paddata & 0x10) || (paddata & 0x800)) // Triangle or Start
	{
		// continue game if needed

		if (VisibleMenu == 0)
		{
#ifndef PSX
			// hack for keyboard swap
			if(!(paddata & 0x800))
				return;
#endif
			for (i = 0; i < ActiveMenu->NumItems; i++)
			{
				pItem = &ActiveMenu->MenuItems[i];

				if (pItem->ExitValue == MENU_QUIT_CONTINUE)
				{
					PauseReturnValue = pItem->ExitValue;
					return;
				}
			}
		}
		else
		{
			// only triangle
			if(paddata & 0x10)
			{
				VisibleMenu--;
				SetupMenu(VisibleMenus[VisibleMenu], 1);
			}
		}
	}
}


// [D] [T]
void PauseMap(int direction)
{
	gShowMap ^= 1;

	ReadControllers();

	map_x_shift = 0;
	map_z_shift = 0;

	if (gShowMap == 0)
		InitOverheadMap();
}

// [D] [T]
void SfxVolume(int direction)
{
	if (direction < 0) 
		gMasterVolume = gMasterVolume + -100;
	else if (0 < direction)
		gMasterVolume = gMasterVolume + 100;

	if (gMasterVolume < -10000) 
		gMasterVolume = -10000;

	if (gMasterVolume > 0) 
		gMasterVolume = 0;

	sprintf(SfxVolumeText, "%d", (10000 + gMasterVolume) / 100);

	SetMasterVolume(gMasterVolume);
}

// [D] [T]
void MusicVolume(int direction)
{
	if (direction < 0)
		gMusicVolume = gMusicVolume + -100;
	else if (0 < direction) 
		gMusicVolume = gMusicVolume + 100;

	if (gMusicVolume < -10000)
		gMusicVolume = -10000;

	if (gMusicVolume > 0) 
		gMusicVolume = 0;

	sprintf(MusicVolumeText, "%d", (10000 + gMusicVolume) / 100);

	SetXMVolume(gMusicVolume);
}

// [D] [T]
void EnterScoreName(void)
{
	u_char chr;
	int so;
	int co;
	int delay;
	char* username;
	int toggle;
	SCORE_ENTRY* table;
	unsigned short npad, dpad;

	username = NULL;
	delay = 0;
	gEnteringScore = 1;
	toggle = 0;

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

	co = 1;
	so = 0;

	CreateScoreNames(table, &gPlayerScore, gScorePosition);

	do {
		ReadControllers();

		npad = Pads[0].dirnew;
		dpad = Pads[0].direct;

		if (gScoreEntered)
		{
			if (npad & 0x50)
			{
				gEnteringScore = 0;
				return;
			}
		}
		else
		{
			// cancel
			if (npad & 0x10)
			{
				gEnteringScore = 0;
				return;
			}

			if (dpad & 0x20)
			{
				// switch to end
				delay = 1;
				toggle = 0;
				co = 67;
			}
			else if (dpad & 0x8000)
			{
				// move left/right to switch chars
				if (delay-- == 0)
				{
					delay = 20;
					toggle = 0;
					co--;
				}
				else if (delay < 1)
				{
					delay = 2;
					toggle = 0;
					co--;
				}

				if (co < 0)
					co = 67;
			}
			else if (dpad & 0x2000)
			{
				if (delay-- == 0)
				{
					delay = 20;
					toggle = 0;
					co++;
				}
				else if (delay < 1)
				{
					delay = 2;
					toggle = 0;
					co++;
				}

				if (co > 67)
					co = 0;
			}
			else
			{
				delay = 0;
			}

			if (so == 5)
				chr = 254;
			else
				chr = validchars[co];

			toggle++;

			if (toggle & 4)
				username[so] = 0;
			else if (chr == ' ')
				username[so] = '.';
			else
				username[so] = chr;

			if (npad & 0x80)
			{
				if (so > 0)
					so--;

				username[so] = 0;
				username[so+1] = 0;
			}

			if (npad & 0x40)
			{
				// complete
				if (chr == 254)
				{
					username[so] = 0;
					strcpy(gPlayerScore.name, username);
					AddScoreToTable(table, gScorePosition);
					
					sprintf(EnterScoreText, "View Table");
					sprintf(EnterNameText, "High Scores");
					
					gEnteringScore = 0;
					gScoreEntered = 1;
					return;
				}

				// delete chars
				if(chr == 255)
				{
					if (so > 0)
						so--;

					username[so] = 0;
					username[so + 1] = 0;
				}
				else if (so < 5)
				{
					username[so] = chr;
					username[so+1] = 0;
					so++;
				}
			}
		}

		DrawGame();
	} while (true);
}

// [D] [T]
void DrawHighScoreMenu(int selection)
{
	POLY_FT3* null;
	POLY_F4* prim;
	int i;
	int b;
	int r;
	int ypos;
	char text[8];

	OutputString(EnterNameText, 2, 160, 70, 0, 128, 32, 32);
	OutputString(G_LTXT(GTXT_Name), 1, 40, 90, 0, 128, 128, 32);
	OutputString(G_LTXT(GTXT_Time), 4, 280, 90, 0, 128, 128, 32);

	ypos = 110;

	i = 0;
	do {
		
		if (i == selection) 
		{
			r = 0;
			b = 0;
		}
		else
		{
			r = 128;
			b = 128;
		}

		sprintf(text, "%d", i+1);

		OutputString(text, 1, 40, ypos, 0, r, 128, b);

		OutputString(ScoreName[i], 1, 60, ypos, 0, r, 128, b);
		OutputString(ScoreItems[i], 4, 220, ypos, 0, r, 128, b);
		OutputString(ScoreTime[i], 4, 280, ypos, 0, r, 128, b);

		ypos += 15;

		i++;
	} while (i < 5);

	prim = (POLY_F4*)current->primptr;
	setPolyF4(prim);
	setSemiTrans(prim, 1);
	setShadeTex(prim, 1);

	prim->y0 = 65;
	prim->y1 = 65;
	prim->y2 = 197;
	prim->y3 = 197;
	prim->x0 = 26;
	prim->x1 = 294;
	prim->x2 = 26;
	prim->x3 = 294;

	prim->r0 = 16;
	prim->g0 = 16;
	prim->b0 = 16;

	addPrim(current->ot, prim);
	current->primptr += sizeof(POLY_F4);

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
}

// [D] [T]
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
			printError("CreateScoreNames: Invalid game type\n");
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

			if (text != NULL && score->items != -1)
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

			if (text != NULL && table->items != -1)
				sprintf(ScoreItems[i], "%d %s", table->items, text);

			sprintf(ScoreName[i], "%s", table->name);
			table = table + 1;
		}

		i++;
	} while (i < 5);

}


// [D] [T]
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

	if (NoPlayerControl == 0 && OnScoreTable(NULL) != -1 && allownameentry)
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

	if (NumPlayers > 1)
	{
		rect.x = 0;
		rect.w = 320;
		rect.h = 1;
		rect.y = current->draw.clip.y + current->draw.clip.h;

		ClearImage2(&rect, 0, 0, 0);
		DrawGame();

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

// [D] [T]
void DrawPauseMenus(void)
{
#if !defined(PSX) && defined(DEBUG_OPTIONS)
	extern int g_FreeCameraEnabled;

	if (g_FreeCameraEnabled)
		return;
#endif

	if (gDrawPauseMenus && gShowMap == 0)
	{
		if (gEnteringScore == 0)
			DrawVisibleMenus();
		else
			DrawHighScoreMenu(gScorePosition);
	}
}