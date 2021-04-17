#ifndef DR2LOCALE_H
#define DR2LOCALE_H

#define MAX_LANGUAGE_TEXT 350

enum GameStrId
{
	GTXT_Damage = 0,
	GTXT_Felony,
	GTXT_Proximity,

	GTXT_Best,
	
	GTXT_Cone,
	GTXT_Gate,
	GTXT_Check,
	
	GTXT_Cones,
	GTXT_Gates,
	GTXT_Checks,
	GTXT_Minus1second,
	
	GTXT_Flags,
	GTXT_Lap,
	GTXT_YouGotTheFlag,
	GTXT_WellDone,
	GTXT_YouveBeenCaught,

	GTXT_OutOfTape,
	GTXT_DEMO,
	GTXT_Fastforward,
	GTXT_Autodirect,

	// pause strings
	GTXT_PleaseWait,
	GTXT_PleaseinsertDISC1,
	GTXT_PleaseinsertDISC2,
	GTXT_NoDISCinserted,
	GTXT_IncorrectDISCinserted,
	GTXT_Checking,
	
	GTXT_AreYouSure,
	GTXT_Paused,
	GTXT_MissionSuccessful,
	GTXT_MissionFailed,
	GTXT_GameOver,
	GTXT_HighScores,
	GTXT_EnterName,
	GTXT_QuitToSystem,
	GTXT_LoadingConfiguration,
	GTXT_LoadingError,
	GTXT_NoSavedData,
	GTXT_SavingConfiguration,
	GTXT_SavingError,
	GTXT_LoadingProgress,
	GTXT_SavingProgress,
	GTXT_OK,
	GTXT_YES,
	GTXT_NO,
	GTXT_SaveGame,
	GTXT_SaveReplay,
	GTXT_Continue,
	GTXT_ShowMap,
	GTXT_Restart,
	GTXT_SfxVolume,
	GTXT_MusicVolume,
	GTXT_FilmDirector,
	GTXT_QuickReplay,
	GTXT_Exit,
	GTXT_Rotation,
	GTXT_Move,
	GTXT_SkipCutscene,
	GTXT_RetryMission,
	GTXT_PlayAgain,
	GTXT_ViewTable,
	GTXT_EnterScore,

	GTXT_InsertController1,
	GTXT_InsertController2,
	GTXT_IncorrectController1,
	GTXT_IncorrectController2,
	GTXT_Player1,
	GTXT_Player2,
	GTXT_Name,
	GTXT_Time,
	GTXT_NoSecrets,
	GTXT_MountainTrack,
	GTXT_Circuit,
	GTXT_Invincibility,
	GTXT_Immunity,
	GTXT_BonusGallery,

	// director strings
	GTXT_Pause,
	GTXT_Play,
	GTXT_AutoDirector,
	GTXT_FastForward,
	GTXT_FrameAdvance,
	GTXT_Rewindtobeginning,
	GTXT_AddCamera,
	GTXT_EditCamera,
	GTXT_InCar,
	GTXT_ChaseCamera,
	GTXT_TripodCamera,
	GTXT_MoveCameraStart,
	GTXT_DeleteCamera,
	GTXT_Accept,
	GTXT_YouorPursuer,
	GTXT_MoveCamera,
	GTXT_LocktoCar,
	GTXT_Rotate,
	GTXT_Zoom,

	// RED2
	GTXT_GetawayIs,

	GTXT_TimeOfDay,
	GTXT_Condition,

	GTXT_Dusk,
	GTXT_Day,
	GTXT_Dawn,
	GTXT_Night,

	GTXT_Clear,
	GTXT_Rainy,
	GTXT_Wet
};

enum MissionStrId
{
	MTXT_Chicago = 0,
	MTXT_Havana,
	MTXT_LasVegas,
	MTXT_RioDeJaneiro,

	// main campaingn mission names
	MTXT_Surveillancetipoff,
	MTXT_Chasethewitness,
	MTXT_Trainpursuit,
	MTXT_Tailingthedrop,
	MTXT_Escapetothesafehouse,
	MTXT_Chasetheintruder,
	MTXT_Cainescompound,
	MTXT_LeavingChicago,
	MTXT_Followupthelead,
	MTXT_Hijackthetruck,
	MTXT_Stopthetruck,
	MTXT_Findtheclue,
	MTXT_Escapetoferry,
	MTXT_Tothedocks,
	MTXT_BacktoJones,
	MTXT_TailJericho,
	MTXT_PursueJericho,
	MTXT_EscapetheBrazilians,
	MTXT_Casinogetaway,
	MTXT_Beatthetrain,
	MTXT_Carbomb,
	MTXT_Carbombgetaway,
	MTXT_Bankjob,
	MTXT_Stealtheambulance,
	MTXT_StakeOut,
	MTXT_Stealthekeys,
	MTXT_C4deal,
	MTXT_Destroytheyard,
	MTXT_Buscrash,
	MTXT_Stealthecopcar,
	MTXT_Cainescash,
	MTXT_SaveJones,
	MTXT_Boatjump,
	MTXT_Jonesintrouble,
	MTXT_ChasetheGunMan,
	MTXT_Lennyescaping,
	MTXT_Lennygetscaught,

	// Cutscene name ids
	MTXT_RedRiver,
	MTXT_Themorgue,
	MTXT_TheWitness,
	MTXT_Lennysapartment,
	MTXT_TheCubaConnection,
	MTXT_TheIntruder,
	MTXT_MeetingCaine,
	MTXT_LeavingTown,
	MTXT_Lookingforalead,
	MTXT_Movingout,
	MTXT_Watchingthetruck,
	MTXT_RosannaSotoClue,
	MTXT_TheDockyard,
	MTXT_TheHit,
	MTXT_SeizingJericho,
	MTXT_VasquezinVegas,
	MTXT_TradingJericho,
	MTXT_CBankjob,
	MTXT_ThePoolHall,
	MTXT_CainesWarpath,
	MTXT_CaineinRio,
	MTXT_WarningJones,
	MTXT_TheShootout,
	MTXT_Lennysgetaway,
	MTXT_Lennygetsit,
	MTXT_BackinChicago,
	MTXT_VasquezmeetsCaine,
	MTXT_Credits,

	// Minigame locations
	MTXT_Downtown,
	MTXT_Wrigleyville,
	MTXT_Greektown,
	MTXT_GrantPark,
	MTXT_MeigsField,
	MTXT_UkrainianVillage,
	MTXT_RiverNorth,
	MTXT_CabriniGreen,

	MTXT_NecropolisdeColon,
	MTXT_Capitolio,
	MTXT_OldHavana,
	MTXT_TheDocks,
	MTXT_Vedado,
	MTXT_Plaza,
	MTXT_PlazadelaRevolucion,

	MTXT_UpperStrip,
	MTXT_Lakeside,
	MTXT_MidStrip,
	MTXT_NorthVegas,
	MTXT_Lakes,
	MTXT_GhostTown,

	MTXT_Centro,
	MTXT_Copacabana,
	MTXT_SantaTereza,
	MTXT_LagoaRodrigodeFreitas,
	MTXT_PracadaBandeira,
	MTXT_Leblon,
	MTXT_Flamengo,
};

#define MISSION_NAMES_START			MTXT_Surveillancetipoff
#define MISSION_NAMES_COUNT			(MTXT_Lennygetscaught - MISSION_NAMES_START + 1)

#define CUTSCENE_NAMES_START		MTXT_Downtown
#define CUTSCENE_NAMES_COUNT		(MTXT_Credits - CUTSCENE_NAMES_START + 1)

#define MINIGAME_NAMES_START		MTXT_Downtown
#define MINIGAME_NAMES_COUNT		(MTXT_Flamengo - MINIGAME_NAMES_START + 1)

// lookup game string
#define G_LTXT(id)	gGameLangTable[id]

// lookup mission string
#define M_LTXT(id)	gMissionLangTable[id]

#ifndef PSX

extern char* gGameLangTable[MAX_LANGUAGE_TEXT];
extern char* gMissionLangTable[MAX_LANGUAGE_TEXT];

// get Game string ID in as string pointer
#define G_LTXT_ID(id)		(char*)(id)

// get Mission string ID in as string pointer
#define M_LTXT_ID(id)		(char*)(id)

// fancy logic
#define GET_GAME_TXT(st)		(((int)st < MAX_LANGUAGE_TEXT && st) ? gGameLangTable[(int)st] : st)
#define GET_MISSION_TXT(st)		(((int)st < MAX_LANGUAGE_TEXT && st) ? gMissionLangTable[(int)st] : st)

extern int InitStringMng();
extern void DeinitStringMng();
extern int InitStringLanguage(char* filename, int mission);

#else

/*
static char* gGameLangTable[] = {
	#include "GAME_ENGLISH.INC",
};

static char* gMissionLangTable[MAX_LANGUAGE_TEXT] = {
	#include "MISSION_ENGLISH.INC",
};*/

static char* gGameLangTable[MAX_LANGUAGE_TEXT] = {
	"",
};

static char* gMissionLangTable[MAX_LANGUAGE_TEXT] = {
	"",
};

#define G_LTXT_ID(id)	G_LTXT(id)
#define M_LTXT_ID(id)	M_LTXT(id)

#define GET_GAME_TXT(st)		st
#define GET_MISSION_TXT(st)		st

#endif

#endif