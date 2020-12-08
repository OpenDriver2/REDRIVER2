#include "DRIVER2.H"
#include "FEMAIN.H"
#include <string.h>

#include "LIBGPU.H"
#include "LIBETC.H"

#include "C/CD_ICON.H"

#include "C/SYSTEM.H"
#include "C/GLAUNCH.H"
#include "C/MISSION.H"
#include "C/LOADVIEW.H"
#include "C/PAD.H"
#include "C/TIME.H"
#include "C/PRES.H"
#include "C/SOUND.H"
#include "C/DEBRIS.H"
#include "C/E3STUFF.H"
#include "C/FMVPLAY.H"
#include "C/SCORES.H"
#include "C/LOADSAVE.H"

#include "MEMCARD/MAIN.H"

struct FE_CHARDATA
{
	u_char u;
	u_char v;
	u_char w;
	u_char h;
};

struct FE_FONT
{
	int NumFonts;
	FE_CHARDATA CharInfo[256];
};

struct SCREEN_LIMITS
{
	short minx;
	short miny;
	short maxx;
	short maxy;
};

struct BOTCH
{
	int missNum;
	char** name;
};

typedef int(*screenFunc)(int bSetup);

extern ACTIVE_CHEATS AvailableCheats;
extern ACTIVE_CHEATS ActiveCheats;

screenFunc fpUserFunctions[] = {
	CentreScreen,
	CarSelectScreen,
	CopDiffLevelScreen,
	VibroOnOffScreen,
	MissionSelectScreen,
	MissionCityScreen,
	CutSceneCitySelectScreen,
	CutSceneSelectScreen,
	SetVolumeScreen,
	ScoreScreen,
	SubtitlesOnOffScreen,
	CityCutOffScreen,
	ControllerScreen,
	MainScreen,
	CheatScreen,
	ImmunityOnOffScreen,
	InvincibleOnOffScreen,
	GamePlayScreen,
	GameNameScreen,
	CheatNumlayerSelect,

};

char* gfxNames[4] = {
	"DATA\\CARS\\CCARS.RAW",
	"DATA\\CARS\\HCARS.RAW",
	"DATA\\CARS\\VCARS.RAW",
	"DATA\\CARS\\RCARS.RAW",
};

char* cutGfxNames[4] = {
	"DATA\\CUTS\\CCUTS.RAW",
	"DATA\\CUTS\\HCUTS.RAW",
	"DATA\\CUTS\\VCUTS.RAW",
	"DATA\\CUTS\\RCUTS.RAW",
};

int CutAmounts[5] = {
	0, 8, 7, 5, 8
};

int CutAmountsTotal[5] = {
	0, 8, 15, 20, 40
};

char* CutSceneNames[28] =
{
	"Red River",
	"The morgue",
	"The Witness",
	"Lenny's apartment",
	"The Cuba Connection",
	"The Intruder",
	"Meeting Caine",
	"Leaving Town",

	"Looking for a lead",
	"Moving out",
	"Watching the truck",
	"Rosanna Soto Clue",
	"The Dockyard",
	"The Hit",
	"Seizing Jericho",

	"Vasquez in Vegas",
	"Trading Jericho",
	"Bank job",
	"The Pool Hall",
	"Caine's Warpath",

	"Caine in Rio",
	"Warning Jones",
	"The Shootout",
	"Lenny's getaway",
	"Lenny gets it",
	"Back in Chicago",
	"Vasquez meets Caine",
	"Credits",
};

#ifndef PSX
char *areaNames[4][8] = {
	{
		"Downtown",
		"Wrigleyville",
		"Greektown",
		"Grant Park",
		"Meigs Field",
		"Ukrainian Village",
		"River North",
		"Cabrini Green",
	},
	{
		"Necropolis de Colon",
		"Capitolio",
		"Old Havana",
		"The Docks",
		"Vedado",
		"Plaza",
		"Plaza de la Revolucion",
		NULL,
	},
	{
		"Downtown",
		"Upper Strip",
		"Lakeside",
		"Mid Strip",
		"North Vegas",
		"Lakes",
		"Ghost Town",
		NULL,
	},
	{
		"Centro",
		"Copacabana",
		"Santa Tereza",
		"Lagoa Rodrigo de Freitas",
		"Praca da Bandeira",
		"Leblon",
		"Flamengo",
		NULL,
	},
};

static char gameAreas[64] = {
	// Getaway (0-6)
	0, 1, // Downtown, Wrigleyville
	0, 1, // Necropolis De Colon, Capitolio
	0, 1, // Downtown, Upper Strip
	0, 1, // Centro, Copacabana

	// Gate race (8-14)
	2, 3, // Greektown, Grant Park
	0, 2, // Necropolis de Colon, Old Havana
	2, 3, // Lakeside, Mid Strip
	1, 2, // Copacabana, Santa Tereza

	// Checkpoint (16-22)
	0, 4, // Downtown, Meigs Field
	3, 2, // The Docks, Old Havana
	4, 2, // North Vegas, Lakeside
	3, 4, // Lagoa Rodrigo de Freitas, Praca da Bandeira

	// Trailblazer (24-30)
	3, 0, // Grant Park, Downtown
	2, 4, // Old Havana, Vedado
	0, 1, // Downtown, Upper Strip
	5, 4, // Leblon, Praca da Bandeira

	// [MP] Cops 'n Robbers (32-38)
	5, 0, // Ukrainian Village, Downtown
	4, 0, // Vedado, Necropolis de Colon
	3, 0, // Mid Strip, Downtown
	1, 0, // Copacabana, Centro

	// [MP] Capture the Flag (40-46)
	7, 6, // Cabrini Green, River North
	2, 5, // Old Havana, Plaza
	5, 6, // Lakes, Ghost Town
	6, 0, // Flamengo, Centro

	// [MP] Take a Ride (48-54)
	6, 7, // River North, Cabrini Green
	5, 2, // Plaza, Old Havana
	0, 5, // Downtown, Lakes
	0, 6, // Centro, Flamengo

	// [MP] Checkpoint (56-62)
	6, 7, // River North, Cabrini Green
	2, 6, // Old Havana, Plaza de la Revolucion
	6, 4, // Ghost Town, North Vegas
	0, 6, // Centro, Flamengo
};

#define AREA_NAME(level, index) areaNames[level][index]

#define GAMEMODE_AREA(level, offset, index) gameAreas[offset + level * 2 + index]
#define GAMEMODE_AREA_NAME(level, offset, index) AREA_NAME(level, GAMEMODE_AREA(level, offset, index))
#else
static char* gameNames[64] = {
	// Getaway (0-6)
	"Downtown",						"Wrigleyville",
	"Necropolis De Colon",			"Capitolio",
	"Downtown",						"Upper Strip",
	"Centro",						"Copacabana",

	// Gate race (8-14)
	"Greektown",					"Grant Park",
	"Necropolis de Colon",			"Old Havana",
	"Lakeside",						"Mid Strip",
	"Copacabana",					"Santa Tereza",

	// Checkpoint (16-22)
	"Downtown",						"Meigs Field",
	"The Docks",					"Old Havana",
	"North Vegas",					"Lakeside",
	"Lagoa Rodrigo de Freitas",		"Praca da Bandeira",
	
	// Trailblazer (24-30)
	"Grant Park",					"Downtown",
	"Old Havana",					"Vedado",
	"Downtown",						"Upper Strip",
	"Leblon",						"Praca da Bandeira",

	// [MP] Cops 'n Robbers (32-38)
	"Ukrainian Village",			"Downtown",
	"Vedado",						"Necropolis de Colon",
	"Mid Strip",					"Downtown",
	"Copacabana",					"Centro",

	// [MP] Capture the Flag (40-46)
	"Cabrini Green",				"River North",
	"Old Havana",					"Plaza",
	"Lakes",						"Ghost Town",
	"Flamengo",						"Centro",
	
	// [MP] Take a Ride (48-54)
	"River North",					"Cabrini Green",
	"Plaza",						"Old Havana",
	"Downtown",						"Lakes",
	"Centro",						"Flamengo",

	// [MP] Checkpoint (56-62)
	"River North",					"Cabrini Green",
	"Old Havana",					"Plaza de la Revolucion",
	"Ghost Town",					"North Vegas",
	"Centro",						"Flamengo",
};

#define AREA_NAME(level, index) "???"

#define GAMEMODE_AREA(level, offset, index) (0)
#define GAMEMODE_AREA_NAME(level, offset, index) gameNames[offset + level * 2 + index]
#endif

int CarAvailability[4][10] = {
	{1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,0,0},
};

char carNumLookup[4][10] = {
	{1, 2, 3, 4, 0, 8, 9, 10, 11, 12},
	{1, 2, 3, 4, 0, 8, 9, 10, 11, 12},
	{1, 2, 3, 4, 0, 8, 9, 10, 11, 12},
	{1, 2, 3, 4, 0, 8, 9, 10, 11, 12},
};

int minmaxSelections[4][2] = {

	{ 0, 8 },
	{ 8, 17 },
	{ 18, 27 },
	{ 28, 37 }
};

BOTCH botch[38] = {
	{ 1, &MissionName[0]},
	{ 2, &MissionName[1]},
	{ 3, &MissionName[2]},
	{ 4, &MissionName[3]},
	{ 5, &MissionName[4]},
	{ 6, &MissionName[5]},
	{ 7, &MissionName[6]},
	{ 9, &MissionName[7]},
	{ 10, &MissionName[8]},
	{ 11, &MissionName[9]},
	{ 13, &MissionName[10]},
	{ 14, &MissionName[11]},
	{ 15, &MissionName[12]},
	{ 16, &MissionName[13]},
	{ 17, &MissionName[14]},
	{ 18, &MissionName[15]},
	{ 19, &MissionName[16]},
	{ 20, &MissionName[17]},
	{ 21, &MissionName[18]},
	{ 22, &MissionName[19]},
	{ 23, &MissionName[20]},
	{ 24, &MissionName[21]},
	{ 25, &MissionName[22]},
	{ 26, &MissionName[23]},
	{ 27, &MissionName[24]},
	{ 28, &MissionName[25]},
	{ 29, &MissionName[26]},
	{ 30, &MissionName[27]},
	{ 31, &MissionName[28]},
	{ 32, &MissionName[29]},
	{ 33, &MissionName[30]},
	{ 34, &MissionName[31]},
	{ 35, &MissionName[32]},
	{ 37, &MissionName[33]},
	{ 38, &MissionName[34]},
	{ 39, &MissionName[35]},
	{ 40, &MissionName[36]},
	{ 0,NULL}
};

char ScreenTitle[128];
char ScoreName[128];

int bDoingScores = 0;
int bInCutSelect = 0;
int cutSelection = 0;
int currCity = 0;

int bRedrawFrontend = 0;
int bReturnToMain = 1;

int idle_timer = 0;
int currPlayer = 1;
int fePad = 0;
int ScreenDepth = 0;

int gIdleReplay = 0;

int padsConnected[2] = { 1, 0 };
int feVariableSave[4] = { -1 };
int bCdIconSetup = 0;
int bMissionSelect = 0;
int bDoingCarSelect = 0;
int bDoingCutSelect = 0;
int bDrawExtra = 0;
int mainScreenLoaded = 1;
int bDoneAllready = 0;
int allowVibration = 1;
int bQuitToSystem = 0;
int bQuitToSystemSel = 0;

int carSelection = 0;
int currSelIndex = 0;
int lastCutCity = -1;
int lastCity = -1;
int currMission = -1;
int missionSetup = 0;

char* ScreenNames[12] = { 0 };

char loaded[3] = { -1, -1, -1 };

PSXSCREEN* pCurrScreen = NULL;
PSXSCREEN* pNewScreen = NULL;

PSXBUTTON* pNewButton = NULL;
PSXBUTTON* pCurrButton = NULL;

PSXSCREEN PsxScreens[42] = { 0 };
PSXSCREEN* pScreenStack[10] = { 0 };
PSXBUTTON* pButtonStack[10] = { 0 };

POLY_FT4 BackgroundPolys[6];
FE_FONT feFont;

RECT16 extraRect = { 896, 256, 64, 219 };

POLY_FT4 cd_sprite;

SPRT extraSprt;
POLY_FT3 extraDummy;

// [D] [T]
void SetVariable(int var)
{
	int code = (var >> 8);
	int value = (var & 0xff);

	switch (code)
	{
		case 1:
			GameLevel = value;
			break;
		case 2:
			GameType = (GAMETYPE)value;

			if (value != GAME_COPSANDROBBERS)
				gWantNight = 0;

			break;
		case 3:
			NumPlayers = (value + 1);
			break;
		case 4:
			gWantNight = value > 0;

			break;
		case 5:
			gCurrentMissionNumber = 1;
			GameType = GAME_MISSION;
			break;
		case 6:
			pScreenStack[ScreenDepth] = pCurrScreen;
			pButtonStack[ScreenDepth] = pCurrButton;

			if (value == 1) 
			{
#ifdef PSX
				if (CallMemoryCard(0x11, 0) == 0)
#else
				if(LoadReplayFromFile("CHASE.D2RP") == 0)		// [A] temporary
#endif
				{
					ReInitFrontend();
				}
				else 
				{
					StoredGameType = GameType;
					GameType = GAME_LOADEDREPLAY;
					GameStart();
				}
			}
			else
			{
				CallMemoryCard(0x81, 0);
				ReInitFrontend();
				SetMasterVolume(gMasterVolume);
				SetXMVolume(gMusicVolume);
			}

			break;
		case 7:
			pScreenStack[ScreenDepth] = pCurrScreen;
			pButtonStack[ScreenDepth] = pCurrButton;

			if (value == 0) 
			{
#ifdef PSX
				CallMemoryCard(0x80, 0);
				ReInitFrontend();
#else
				// [A] save configuration
				SaveCurrentProfile();
#endif
			}
			else 
			{
#ifdef PSX
				if (CallMemoryCard(0x21, 0) == 0) 
				{
					ReInitFrontend();
				}
				else
#else
				if(LoadCurrentGame())
#endif
				{
					GameType = GAME_CONTINUEMISSION;
					GameStart();
				}
			}

			break;
		case 8:
			gSubGameNumber = value;
			break;
		case 9:
			gSubtitles = (value == 0) ? 0 : 1;
			break;
		case 10:
			gInvincibleCar = value;
			ActiveCheats.cheat3 = value;
			break;
		case 11:
			gPlayerImmune = value;
			ActiveCheats.cheat4 = value;
			break;
		case 12:
			GameLevel = 3;
			gSubGameNumber = (value == 0) ? 2 : 0;
			break;
		case 13:
			GameType = GAME_IDLEDEMO;
			gCurrentMissionNumber = (value + 400);
			break;
		case 14: // [A]
		{
			ShowBonusGallery();

			LoadFrontendScreens();
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadFrontendScreens()
 // line 1371, offset 0x001c0c1c
	/* begin block 1 */
	// Start line: 1373
	// Start offset: 0x001C0C1C
	// Variables:
	// 		int iTpage; // $s0
	// 		int iNumScreens; // $t6
	// 		int i; // $t0
	// 		int j; // $a3
	// 		RECT rect; // stack offset -40
	// 		char *ptr; // $a2
	/* end block 1 */
	// End offset: 0x001C0F24
	// End Line: 1454

	/* begin block 2 */
		// Start line: 2740
	/* end block 2 */
	// End Line: 2741

	/* begin block 3 */
		// Start line: 2750
	/* end block 3 */
	// End Line: 2751

	/* begin block 4 */
		// Start line: 2751
	/* end block 4 */
	// End Line: 2752

	/* begin block 5 */
		// Start line: 2761
	/* end block 5 */
	// End Line: 2762

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void LoadFrontendScreens(void)
{
	int iNumScreens;
	char *ptr;
	RECT16 rect;

	ShowLoadingScreen("GFX\\FELOAD.TIM", 1, 12);
	ShowLoading();

	Loadfile("DATA\\SCRS.BIN", _frontend_buffer);

	ptr = _frontend_buffer + 20; // skip header and number of screens
	iNumScreens = (int)_frontend_buffer[16];

	for (int i = 0; i < iNumScreens; i++)
	{
		PsxScreens[i].numButtons = *ptr++;
		PsxScreens[i].userFunctionNum = *ptr++;

		for (int j = 0; j < PsxScreens[i].numButtons; j++)
		{
			memcpy(&PsxScreens[i].buttons[j], ptr, sizeof(PSXBUTTON));
			ptr += sizeof(PSXBUTTON);
		}
	}

	rect.w = 64;
	rect.h = 256;

	ShowLoading();
	LoadBackgroundFile("DATA\\GFX.RAW");

	for (int i = 0; i < 2; i++)
	{
		ShowLoading();
		LoadfileSeg("DATA\\GFX.RAW", _frontend_buffer, 0x30000 + (i * 0x8000), 0x8000);

		rect.x = 640 + (i * 64);
		rect.y = 256;

		LoadImage(&rect, (u_long *)_frontend_buffer);
		DrawSync(0);
	}

	ShowLoading();	
	LoadfileSeg("DATA\\GFX.RAW", _frontend_buffer, 0x58000, 0x8000);

	rect.x = 960;
	rect.y = 256;

	// load font
	LoadImage(&rect, (u_long *)_frontend_buffer);
	DrawSync(0);

	Loadfile("DATA\\FEFONT.BNK", (char*)&feFont);
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadBackgroundFile(char *name /*$s4*/)
 // line 1461, offset 0x001c0f24
	/* begin block 1 */
		// Start line: 1462
		// Start offset: 0x001C0F24
		// Variables:
	// 		int iTpage; // $s2
	// 		RECT rect; // stack offset -72
	// 		int p; // $s0
	// 		int pages[7]; // stack offset -64
	/* end block 1 */
	// End offset: 0x001C10F4
	// End Line: 1509

	/* begin block 2 */
		// Start line: 2951
	/* end block 2 */
	// End Line: 2952

	/* begin block 3 */
		// Start line: 2959
	/* end block 3 */
	// End Line: 2960

// [D] [T]
void LoadBackgroundFile(char *name)
{
	int iTpage;
	int p;
	RECT16 rect;
	int pages[6];
	int i;
	
	iTpage = 11;

	pages[0] = 0;
	pages[1] = 1;
	pages[2] = 2;
	pages[3] = 3;
	pages[4] = 4;
	pages[5] = 5;

	mainScreenLoaded = (strcmp(name, "DATA\\GFX.RAW") == 0);

	rect.w = 64;
	rect.h = 256;

	for (i = 0; i < 6; i++)
	{
		FEDrawCDicon();
		
		p = pages[i];

		LoadfileSeg(name, _overlay_buffer, p * 0x8000, 0x8000);
		FEDrawCDicon();

		rect.y = (short)(p / 6);
		rect.x = ((short)p + rect.y * -6) * 64 + 640;
		rect.y *= 256;

		LoadImage(&rect, (u_long *)_overlay_buffer);
		FEDrawCDicon();
	}

	LoadfileSeg(name, _overlay_buffer, iTpage * 0x8000, 0x800);
	FEDrawCDicon();

	rect.h = 1;
	rect.y = (short)(iTpage / 6);
	rect.x = ((short)iTpage + rect.y * -6) * 64 + 640;
	rect.y *= 256;

	LoadImage(&rect, (u_long *)_overlay_buffer);
	DrawSync(0);

	SetupBackgroundPolys();
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupBackgroundPolys()
 // line 1516, offset 0x001c10f4
	/* begin block 1 */
		// Start line: 1518
		// Start offset: 0x001C10F4
		// Variables:
	// 		int i; // $v1
	// 		int tpage; // $t3
	/* end block 1 */
	// End offset: 0x001C132C
	// End Line: 1580

	/* begin block 2 */
		// Start line: 3110
	/* end block 2 */
	// End Line: 3111

	/* begin block 3 */
		// Start line: 3118
	/* end block 3 */
	// End Line: 3119

	/* begin block 4 */
		// Start line: 3119
	/* end block 4 */
	// End Line: 3120

	/* begin block 5 */
		// Start line: 3122
	/* end block 5 */
	// End Line: 3123

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void SetupBackgroundPolys(void)
{
	POLY_FT4 *poly;
	int i;

	for (i = 0; i < 6; i++)
	{
		poly = &BackgroundPolys[i];

		setPolyFT4(poly);
		setRGB0(poly, 128, 128, 128);
	}

	poly = &BackgroundPolys[0];
	setXYWH(poly, 0, 0, 256, 256);
	setUVWH(poly, 0, 0, 255, 255);
	setClut(poly, 960, 256);
	setTPage(poly, 0, 0, 640, 0);

	poly = &BackgroundPolys[1];
	setXYWH(poly, 256, 0, 256, 256);
	setUVWH(poly, 0, 1, 255, 254);
	setClut(poly, 960, 256);
	setTPage(poly, 0, 0, 704, 0);

	poly = &BackgroundPolys[2];
	setXYWH(poly, 512, 0, 128, 256);
	setUVWH(poly, 0, 1, 128, 254);
	setClut(poly, 960, 256);
	setTPage(poly, 0, 0, 768, 0);

	poly = &BackgroundPolys[3];
	setXYWH(poly, 0, 256, 256, 256);
	setUVWH(poly, 0, 0, 255, 255);
	setClut(poly, 960, 256);
	setTPage(poly, 0, 0, 832, 0);

	poly = &BackgroundPolys[4];
	setXYWH(poly, 256, 256, 256, 256);
	setUVWH(poly, 0, 0, 255, 255);
	setClut(poly, 960, 256);
	setTPage(poly, 0, 0, 896, 0);

	poly = &BackgroundPolys[5];
	setXYWH(poly, 512, 256, 128, 256);
	setUVWH(poly, 0, 0, 128, 255);
	setClut(poly, 960, 256);
	setTPage(poly, 0, 0, 960, 0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupScreenSprts(PSXSCREEN *pScr /*$a0*/)
 // line 1588, offset 0x001c132c
	/* begin block 1 */
		// Start line: 1589
		// Start offset: 0x001C132C
		// Variables:
	// 		int tpage; // $a1
	// 		POLY_FT3 *null; // $v0
	/* end block 1 */
	// End offset: 0x001C147C
	// End Line: 1650

	/* begin block 2 */
		// Start line: 3344
	/* end block 2 */
	// End Line: 3345

	/* begin block 3 */
		// Start line: 3353
	/* end block 3 */
	// End Line: 3354

	/* begin block 4 */
		// Start line: 3363
	/* end block 4 */
	// End Line: 3364

SPRT HighlightSprt;
POLY_FT4 HighlightDummy;

// [D] [T]
void SetupScreenSprts(PSXSCREEN *pScr)
{
	setSprt(&HighlightSprt);
	setRGB0(&HighlightSprt, 128, 128, 128);
	setXY0(&HighlightSprt, 364, 198);
	setUV0(&HighlightSprt, 0, 0);
	setWH(&HighlightSprt, 256, 36);
	setClut(&HighlightSprt, 960, 258);

	setPolyFT4(&HighlightDummy);
	setXY3(&HighlightDummy, -1, -1, -1, -1, -1, -1);
	setTPage(&HighlightDummy, 0, 0, 704, 256);

	pNewScreen = NULL;
	pCurrScreen = pScr;

	if (pScr->userFunctionNum == 0) 
	{
		if (pNewButton != NULL) 
		{
			pCurrButton = pNewButton;
			pNewButton = NULL;
		}
		else 
			pCurrButton = pScr->buttons;
	}
	else
	{
		if ((fpUserFunctions[pScr->userFunctionNum - 1])(1) == 0)
		{
			if (pNewButton != NULL) 
			{
				pCurrButton = pNewButton;
				pNewButton = NULL;
			}
			else
				pCurrButton = pCurrScreen->buttons;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawScreen(PSXSCREEN *pScr /*stack 0*/)
 // line 1658, offset 0x001c147c
	/* begin block 1 */
		// Start line: 1659
		// Start offset: 0x001C147C
		// Variables:
	// 		int i; // $s1
	// 		char version_info[32]; // stack offset -88
	// 		int numBtnsToDraw; // stack offset -56
	/* end block 1 */
	// End offset: 0x001C18B4
	// End Line: 1760

	/* begin block 2 */
		// Start line: 3516
	/* end block 2 */
	// End Line: 3517

	/* begin block 3 */
		// Start line: 3525
	/* end block 3 */
	// End Line: 3526

DR_MOVE In;
DR_MOVE Out;
RECT16 storeRect = { 768, 475, 255, 36 };

// [D] [T]
void DrawScreen(PSXSCREEN *pScr)
{
	char version_info[32];
	int numBtnsToDraw;
	int i;
#ifndef PSX
	if (bRedrawFrontend)
	{
		// flush the old screen
		//EndFrame();

		bRedrawFrontend = 0;
	}
#endif
	for (i = 0; i < 6; i++)
		addPrim(current->ot + 11, &BackgroundPolys[i]);

	if (pScr != NULL)
	{
		GetTimeStamp(version_info);

		if (bDoingCutSelect && (gFurthestMission < 39)) 
		{
			// hide the Director's Cut button
			numBtnsToDraw = pScr->numButtons - 1;
		}
		else 
		{
			numBtnsToDraw = pScr->numButtons;
		}
#ifndef PSX
		NewSelection(0);
#endif
		for (i = 0; i < numBtnsToDraw; i++)
		{
			PSXBUTTON *button = &pScr->buttons[i];
			int status = button->action >> 8;

#ifdef PSX
			if (status != 5)
			{
				if (button == pCurrButton)
				{
					if (status == 3)
					{
						FEPrintString(button->Name, button->x * 2 + button->w, button->y, 4, 32, 32, 32);
					}
					else
					{
						if (bMissionSelect && (i == 0 || i == 5) ||
							bDoingCarSelect && (i == 0 || i == 2) ||
							bInCutSelect && (i == 0 || i == 2))
						{
							FEPrintString(button->Name, button->x * 2 + button->w, button->y, 4, 124, 108, 40);
						}
						else
						{
							FEPrintString(button->Name, button->x * 2 + button->w, button->y, 4, 128, 128, 128);
						}
					}
				}
				else
				{
					if (status == 3)
					{
						FEPrintString(button->Name, button->x * 2 + button->w, button->y, 4, 32, 32, 32);
					}
					else
					{
						if (bMissionSelect && (i == 0 || i == 5) ||
							bDoingCarSelect && (i == 0 || i == 2) ||
							bInCutSelect && (i == 0 || i == 2))
						{
							FEPrintString(button->Name, button->x * 2 + button->w, button->y, 4, 124, 108, 40);
						}
						else
						{
							FEPrintString(button->Name, button->x * 2 + button->w, button->y, 4, 128, 128, 128);
						}
					}
				}
			}
#else
			int draw = (status != 5);

			if (button == pCurrButton)
			{
				RECT16 rect;

				rect.x = pCurrButton->s_x;
				rect.y = pCurrButton->s_y;
				rect.w = 255;
				rect.h = 36;

				SetDrawMove(&Out, &rect, storeRect.x, storeRect.y);
				addPrim(current->ot + 8, &Out);

				setXY0(&HighlightSprt, rect.x, rect.y);

				addPrim(current->ot + 6, &HighlightSprt);
				addPrim(current->ot + 7, &HighlightDummy);

				draw = 1;
			}

			if (draw)
			{
				if (status == 3)
				{
					FEPrintString(button->Name, button->x * 2 + button->w, button->y, 4, 32, 32, 32);
				}
				else
				{
					if (bMissionSelect && (i == 0 || i == 5) ||
						bDoingCarSelect && (i == 0 || i == 2) ||
						bInCutSelect && (i == 0 || i == 2))
					{
						FEPrintString(button->Name, button->x * 2 + button->w, button->y, 4, 124, 108, 40);
					}
					else
					{
						FEPrintString(button->Name, button->x * 2 + button->w, button->y, 4, 128, 128, 128);
					}
				}
			}
#endif
		}

#ifndef PSX
		if(bQuitToSystem)
		{
			FEPrintString("Quit to system?", 220, 256, 0, 128, 128, 128);

			FEPrintString("Yes", 240, 288, 0, 128, 128, bQuitToSystemSel ? 0 : 128);
			FEPrintString("No", 340, 288, 0, 128, 128, bQuitToSystemSel ? 128 : 0);
		}
#endif

#if defined(_DEBUG) || defined(DEBUG_OPTIONS)
		FEPrintString(version_info, 40, 16, 0, 128, 128, 0);
		FEPrintString("--- " GAME_VERSION " ---", 320, 16, 0, 128, 128, 0);
#endif

		SetTextColour(128, 0, 0);

		DisplayOnScreenText();
		
		if (bDrawExtra) 
		{
			addPrim(&current->ot[2], &extraSprt);
			addPrim(&current->ot[3], &extraDummy);
		}
	}
#ifdef PSX
	else 
	{
		EndFrame();
	}
#else
	EndFrame();
#endif
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayOnScreenText()
 // line 1769, offset 0x001c18e4
	/* begin block 1 */
		// Start line: 1771
		// Start offset: 0x001C18E4
		// Variables:
	// 		int i; // $s0
	// 		char text[32]; // stack offset -64

		/* begin block 1.1 */
			// Start line: 1795
			// Start offset: 0x001C19DC

			/* begin block 1.1.1 */
				// Start line: 1797
				// Start offset: 0x001C19E4
			/* end block 1.1.1 */
			// End offset: 0x001C19EC
			// End Line: 1798
		/* end block 1.1 */
		// End offset: 0x001C19EC
		// End Line: 1799

		/* begin block 1.2 */
			// Start line: 1807
			// Start offset: 0x001C1A4C
			// Variables:
		// 		int extraVal; // $t1
		/* end block 1.2 */
		// End offset: 0x001C1AAC
		// End Line: 1810
	/* end block 1 */
	// End offset: 0x001C1AD0
	// End Line: 1847

	/* begin block 2 */
		// Start line: 3804
	/* end block 2 */
	// End Line: 3805

	/* begin block 3 */
		// Start line: 3805
	/* end block 3 */
	// End Line: 3806

	/* begin block 4 */
		// Start line: 3809
	/* end block 4 */
	// End Line: 3810

/* WARNING: Unknown calling convention yet parameter storage is locked */

char cutUnlock[] = { 
	2, 2, 2, 4, 5, 
	6, 7, 7, 7, 9,
	11, 11, 11, 11, 12,
	12, 13, 13, 14, 15,
	17, 17, 17, 17, 18,
	18, 19, 19, 19, 19,
	21, 21, 21, 21, 22,
	22, 22, 23, 23, 23,
	28 };

char* NullStr = "\0";

// [D] [T]
void DisplayOnScreenText(void)
{
	char *text;

	sprintf(ScreenTitle, NullStr);

	if (padsConnected[0] == 0) {
		int transparent = 0;

		if (Pads[0].type == 0) {
			text = "Please insert controller into Port 1";
			transparent = 1;
		}
		else {
			if (Pads[0].type != 1)
				return;

			text = "Incompatible controller in Port 1";
		}

		FEPrintStringSized(text, 40, 400, 0xc00, transparent, 64, 64, 64);
	}
	else 
	{
		if (!bDoingScores && !bDoingCarSelect) 
		{
			for (int i = 0; i < ScreenDepth; i++)
			{
				if (i > 0)
					strcat(ScreenTitle, " - ");

				strcat(ScreenTitle, ScreenNames[i]);
			}

			FEPrintStringSized(ScreenTitle, 40, 400, 0xc00, 1, 64, 64, 64);
		}

		if (bInCutSelect) {
			text = CutSceneNames[cutSelection + CutAmountsTotal[currCity]];

			FEPrintStringSized(text, 100, 226, 0xc00, 1, 64, 64, 64);
		}
	}
}

// decompiled code
// original method signature: 
// void /*$ra*/ SetupExtraPoly(char *fileName /*$s5*/, int offset /*$s1*/, int offset2 /*$s0*/)
 // line 1855, offset 0x001c1ad0
	/* begin block 1 */
		// Start line: 1856
		// Start offset: 0x001C1AD0
		// Variables:
	// 		int i; // $s0
	// 		int tpage; // $v1
	// 		RECT rect; // stack offset -40
	/* end block 1 */
	// End offset: 0x001C1CF4
	// End Line: 1916

	/* begin block 2 */
		// Start line: 3983
	/* end block 2 */
	// End Line: 3984

	/* begin block 3 */
		// Start line: 3992
	/* end block 3 */
	// End Line: 3993

	/* begin block 4 */
		// Start line: 3996
	/* end block 4 */
	// End Line: 3997

// [D] [T]
void SetupExtraPoly(char *fileName, int offset, int offset2)
{
	int i;
	RECT16 rect = extraRect;

	FEDrawCDicon();
	Loadfile(fileName, _frontend_buffer + offset2);

	rect.x = 896;
	rect.y = 256;
	rect.w = 64;
	rect.h = 219;
	
	LoadImage(&rect, (u_long *)(_frontend_buffer + offset2 + offset * 0x8000));
	
	DrawSync(0);
	VSync(0);

	if(bDrawExtra == 0)
	{
		setSprt(&extraSprt);
		setPolyFT3(&extraDummy);

		setXY0(&extraSprt, 100, 226);
		setRGB0(&extraSprt, 128, 128, 128);
		setUV0(&extraSprt, 0, 0);
		setWH(&extraSprt, 255, 219);
		setClut(&extraSprt, 960, 256);

		setXY3(&extraDummy, -1, -1, -1, -1, -1, -1);
		setTPage(&extraDummy, 0, 0, 896, 256);
	}

	bDrawExtra = 1;

	if (strcmp(fileName, "DATA\\CITY.RAW") == 0) 
	{
		loaded[0] = 1;
		loaded[1] = -1;
	}

	for (i = 0; i < 4; i++)
	{
		if (strcmp(fileName, gfxNames[i]) == 0)
		{
			loaded[0] = -1;
			loaded[1] = i;
			loaded[2] = -1;
		}
	}

	for (i = 0; i < 4; i++)
	{
		if (strcmp(fileName, cutGfxNames[i]) == 0) 
		{
			loaded[1] = -1;
			loaded[2] = i;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReInitScreens()
 // line 1941, offset 0x001c1cf4
	/* begin block 1 */
		// Start line: 4221
	/* end block 1 */
	// End Line: 4222

	/* begin block 2 */
		// Start line: 4247
	/* end block 2 */
	// End Line: 4248

	/* begin block 3 */
		// Start line: 4248
	/* end block 3 */
	// End Line: 4249

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void ReInitScreens(void)
{
#ifndef PSX
	bCdIconSetup = 0;
	bDoingScores = 0;
	bInCutSelect = 0;
	cutSelection = 0;
	currCity = 0;

	bRedrawFrontend = 0;
	bReturnToMain = 1;

	idle_timer = 0;
	currPlayer = 1;
	fePad = 0;
	ScreenDepth = 0;

	loaded[0] = -1;
	loaded[1] = -1;
	loaded[2] = -1;
	padsConnected[0] = 1;
	padsConnected[1] = 0;
	bMissionSelect = 0;
	bDoingCarSelect = 0;
	bDoingCutSelect = 0;
	bDrawExtra = 0;
	mainScreenLoaded = 1;
	bDoneAllready = 0;
	allowVibration = 1;

	ScreenNames[0] = 0;
	gInFrontend = 1;
	currMission = -1;
	missionSetup = 0;

	extern void SwitchMappings(int menu);
	SwitchMappings(1);
#endif // !PSX

	if (!bCdIconSetup)
		FEInitCdIcon();

	if (bReturnToMain)
	{
		ScreenDepth = 0;
		NumPlayers = 1;
		gWantNight = 0;
		gNight = 0;
		gTimeOfDay = 1;
		gSubGameNumber = 0;

		feVariableSave[3] = -1;
		feVariableSave[2] = -1;
		feVariableSave[1] = -1;
		feVariableSave[0] = -1;

		if (!mainScreenLoaded)
		{
			bDrawExtra = 0;
			LoadBackgroundFile("DATA\\GFX.RAW");
		}
	}
	else 
	{
		bReturnToMain = 1;
	}

	pCurrScreen = pScreenStack[ScreenDepth];
	pNewButton = pButtonStack[ScreenDepth];

	SetupScreenSprts(pCurrScreen);
	SetupBackgroundPolys();

	idle_timer = VSync(0xffffffff);
}



// decompiled code
// original method signature: 
// void /*$ra*/ NewSelection(short dir /*$s3*/)
 // line 1991, offset 0x001c1e18
	/* begin block 1 */
		// Start line: 1992
		// Start offset: 0x001C1E18
		// Variables:
	// 		RECT rect; // stack offset -48
	// 		PSXBUTTON *pNewB; // $s2
	/* end block 1 */
	// End offset: 0x001C227C
	// End Line: 2085

	/* begin block 2 */
		// Start line: 4367
	/* end block 2 */
	// End Line: 4368

	/* begin block 3 */
		// Start line: 4369
	/* end block 3 */
	// End Line: 4370

int NewButton(short dir)
{
	PSXBUTTON *pNewB;
	RECT16 rect;

	if (pCurrScreen->numButtons == 0)
		return -1;

	pNewB = pCurrButton;
	int btn = 0;

	// any buttons pressed?
	if (dir != 0)
	{
		SetDrawMove(&In, &storeRect, pCurrButton->s_x, pCurrButton->s_y);
		addPrim(current->ot+9, &In);

		if ((dir & 0x1000) != 0)
		{
			btn = pCurrButton->u;
		}
		else if ((dir & 0x4000) != 0)
		{
			btn = pCurrButton->d;
		}
		else if ((dir & 0x8000) != 0)
		{
			btn = pCurrButton->l;
		}
		else if ((dir & 0x2000) != 0)
		{
			btn = pCurrButton->r;
		}

		if (btn != 0)
		{
			FESound(3);
			pNewB = &pCurrScreen->buttons[btn - 1];
		}
	}
	
	pCurrButton = pNewB;

#ifdef PSX
	rect.x = pCurrButton->s_x;
	rect.y = pCurrButton->s_y;
	rect.w = 255;
	rect.h = 36;

	SetDrawMove(&Out, &rect, storeRect.x, storeRect.y);
	addPrim(current->ot + 8, &Out);

	setXY0(&HighlightSprt, rect.x, rect.y);
	
	addPrim(current->ot + 6, &HighlightSprt);
	addPrim(current->ot + 7, &HighlightDummy);

	if ((pNewB->action >> 8) == 3) {
		FEPrintString(pNewB->Name, pNewB->x * 2 + pNewB->w, pNewB->y, 4, 32, 32, 32);
	}
	else {
		if ((bMissionSelect && ((pNewB == &pCurrScreen->buttons[0]) || (pNewB == &pCurrScreen->buttons[5]))) ||
			((bDoingCarSelect && ((pNewB == &pCurrScreen->buttons[0]) || (pNewB == &pCurrScreen->buttons[2])))) ||
			((bInCutSelect && ((pNewB == &pCurrScreen->buttons[0]) || (pNewB == &pCurrScreen->buttons[2])))))
		{
			FEPrintString(pNewB->Name, pNewB->x * 2 + pNewB->w, pNewB->y, 4, 124, 108, 40);
		}
		else {
			FEPrintString(pNewB->Name, pNewB->x * 2 + pNewB->w, pNewB->y, 4, 128, 128, 128);
		}
	}
#endif
	return btn;
}

// [D] [T]
void NewSelection(short dir)
{
#ifdef PSX
	NewButton(dir);
	EndFrame();
#else
	NewButton(dir);
#endif
}



// decompiled code
// original method signature: 
// int /*$ra*/ HandleKeyPress()
 // line 2093, offset 0x001c22a8
	/* begin block 1 */
		// Start line: 2095
		// Start offset: 0x001C22A8

		/* begin block 1.1 */
			// Start line: 2112
			// Start offset: 0x001C2340
			// Variables:
		// 		int action; // $s0

			/* begin block 1.1.1 */
				// Start line: 2141
				// Start offset: 0x001C244C
			/* end block 1.1.1 */
			// End offset: 0x001C2510
			// End Line: 2166
		/* end block 1.1 */
		// End offset: 0x001C2564
		// End Line: 2186
	/* end block 1 */
	// End offset: 0x001C2668
	// End Line: 2232

	/* begin block 2 */
		// Start line: 4610
	/* end block 2 */
	// End Line: 4611

	/* begin block 3 */
		// Start line: 4611
	/* end block 3 */
	// End Line: 4612

	/* begin block 4 */
		// Start line: 4613
	/* end block 4 */
	// End Line: 4614

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
int HandleKeyPress(void)
{
	if (pCurrScreen == NULL || pCurrButton == NULL)
		return 0;

	if (pCurrScreen->userFunctionNum != 0)
	{
		// notify the user function first
		if ((fpUserFunctions[pCurrScreen->userFunctionNum - 1])(0) != 0)
		{
			// user function handled the key press
			fePad = 0;
		}
	}

	if (fePad & 0x40)
	{
		int action = pCurrButton->action >> 8;

		if (action != 3)
		{
			FESound(2);

			if (pCurrButton->var != -1)
				SetVariable(pCurrButton->var);

			switch (action)
			{
			case 1:
				pScreenStack[ScreenDepth] = pCurrScreen;
				pButtonStack[ScreenDepth] = pCurrButton;

				ScreenNames[ScreenDepth] = pCurrButton->Name;

				pNewScreen = &PsxScreens[pCurrButton->action & 0xFF];

				if (ScreenDepth < 10)
					ScreenDepth++;

				break;
			case 2:
				if ((NumPlayers == 2) && (bDoingCarSelect != 0) && (currPlayer == 2))
				{
					(fpUserFunctions[pCurrScreen->userFunctionNum - 1])(1);
					bRedrawFrontend = 1;
				}
				else
				{
					pScreenStack[ScreenDepth] = pCurrScreen;
					pButtonStack[ScreenDepth] = pCurrButton;

					ScreenNames[ScreenDepth] = pCurrButton->Name;

					GameStart();
				}
				break;
			case 4:
				if (ScreenDepth > 0)
				{
					if (--ScreenDepth == 0)
						NumPlayers = 1;

					pNewScreen = pScreenStack[ScreenDepth];
					pNewButton = pButtonStack[ScreenDepth];
				}
				break;
			}
		}
	}
	else if (fePad & 0x10)
	{
		if (ScreenDepth > 0)
		{
			if (!bDoneAllready)
				FESound(0);
			else 
				bDoneAllready = 0;

			if (--ScreenDepth == 0)
			{
				gWantNight = 0;
				gSubGameNumber = 0;
				NumPlayers = 1;
			}

			pNewScreen = pScreenStack[ScreenDepth];
			pNewButton = pButtonStack[ScreenDepth];
		}
	}
	else
	{
		// any d-pad buttons pressed?
		if ((fePad & (0x8000 | 0x4000 | 0x2000 | 0x1000)) != 0)
		{
			NewSelection(fePad);
		}
		else
		{
			// button pressed, but we didn't handle it
			return 1;
		}
	}

	idle_timer = VSync(-1);

	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PadChecks()
 // line 2300, offset 0x001c2668
	/* begin block 1 */
		// Start line: 2302
		// Start offset: 0x001C2668
		// Variables:
	// 		int i; // $a2
	// 		int oldnum; // $s2
	/* end block 1 */
	// End offset: 0x001C296C
	// End Line: 2417

	/* begin block 2 */
		// Start line: 4977
	/* end block 2 */
	// End Line: 4978

	/* begin block 3 */
		// Start line: 5046
	/* end block 3 */
	// End Line: 5047

	/* begin block 4 */
		// Start line: 5047
	/* end block 4 */
	// End Line: 5048

	/* begin block 5 */
		// Start line: 5048
	/* end block 5 */
	// End Line: 5049

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void PadChecks(void)
{
	int i;
	// TODO: null check for pCurrScreen

	int oldnum = numPadsConnected;

	ReadControllers();
	
	numPadsConnected = 0;
	fePad = Pads[0].mapnew;

	for (int i = 0; i < 2; i++) 
	{
		if (Pads[i].type < 2) 
		{
			padsConnected[i] = 0;
		}
		else 
		{
			padsConnected[i] = 1;
			numPadsConnected++;
		}
	}

#ifndef PSX
	// [A] quit to system
	if(fePad & 0x10)
	{
		if(ScreenDepth == 0)
		{
			bQuitToSystem ^= 1;
			FESound(0);
		}
	}

	if(bQuitToSystem)
	{
		if (fePad & 0x40)
		{
			if(bQuitToSystemSel == 1)
				bQuitToSystem = 2;
			else
				bQuitToSystem = 0;

			FESound(2);
		}
		else if ((fePad & 0x8000) || (fePad & 0x2000))
		{
			bQuitToSystemSel += 1;
			bQuitToSystemSel &= 1;

			FESound(3);
		}

		fePad = 0;
	}
#endif

	if (oldnum != numPadsConnected && (oldnum == 2 || numPadsConnected == 2) && ScreenDepth == 0) 
	{
		bRedrawFrontend = 1;
		MainScreen(1);
	}

	if ((Pads[0].dualshock == 0 || padsConnected[0] == 0) &&
		(Pads[1].dualshock == 0 || padsConnected[1] == 0)) 
	{
		if(allowVibration == 1)
		{
			allowVibration = 0;

			if (pCurrScreen->userFunctionNum == 18)
			{
				bRedrawFrontend = 1;
				GamePlayScreen(1);
			}
		}
	}
	else 
	{
		if (allowVibration == 0)
		{
			allowVibration = 1;

			if (pCurrScreen->userFunctionNum == 18)
			{
				bRedrawFrontend = 1;
				GamePlayScreen(1);
			}
		}
	}

	if (oldnum != numPadsConnected && NumPlayers == 2 && numPadsConnected != NumPlayers || 
		numPadsConnected == 0 || 
		padsConnected[0] == 0) 
	{
		bReturnToMain = 1;
		bRedrawFrontend = 1;
		fePad = 0x10;

		if (pCurrScreen->userFunctionNum != 0) 
		{
			(fpUserFunctions[pCurrScreen->userFunctionNum - 1])(0);
		}

		fePad = 0;

		if (ScreenDepth != 0) 
		{
			ReInitScreens();
		}
	}
	if (bRedrawFrontend == 0 && numPadsConnected != oldnum &&
		(gInFrontend != 0 && (pCurrScreen != NULL && pCurrScreen->userFunctionNum != 0)))
	{
		(fpUserFunctions[pCurrScreen->userFunctionNum - 1])(1);
		bRedrawFrontend = 1;
	}
}

// [A] - was inlined in DoFrontEnd
void InitFrontend(void)
{
	FEInitCdIcon();

	ResetGraph(1);
	SetDispMask(0);

	bRedrawFrontend = 0;
	gInFrontend = 1;

	idle_timer = VSync(-1);

	LoadFrontendScreens();

	SetupBackgroundPolys();
	SetupScreenSprts(&PsxScreens[0]);
}

// [A] - was inlined in DoFrontEnd
void InitDisplay(void)
{
	SetDispMask(0);
	ResetGraph(0);

	SetFEDrawMode();

	EnableDisplay();

#ifdef PSX
	DrawScreen(pCurrScreen);
	EndFrame();

	NewSelection(0);

	// REALLY make sure the screen is cleared
	EndFrame();
	EndFrame();
	EndFrame();
	EndFrame();
	EndFrame();
	EndFrame();
#endif

	SetDispMask(1);
}

// decompiled code
// original method signature: 
// void /*$ra*/ DoFrontEnd()
 // line 2423, offset 0x001c296c
	/* begin block 1 */
		// Start line: 2425
		// Start offset: 0x001C296C
		// Variables:
	// 		static unsigned char result[8]; // offset 0x0
	/* end block 1 */
	// End offset: 0x001C2C2C
	// End Line: 2588

	/* begin block 2 */
		// Start line: 5332
	/* end block 2 */
	// End Line: 5333

	/* begin block 3 */
		// Start line: 5339
	/* end block 3 */
	// End Line: 5340

	/* begin block 4 */
		// Start line: 5340
	/* end block 4 */
	// End Line: 5341

	/* begin block 5 */
		// Start line: 5346
	/* end block 5 */
	// End Line: 5347

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DoFrontEnd(void)
{
	InitFrontend();
	InitDisplay();

	do
	{
		PadChecks();

		if (currPlayer == 2) {
			if (Pads[1].type < 2) {
				fePad = ((fePad & 0x10) != 0) ? 0x10 : 0;
			}
			else {
				fePad = Pads[1].mapnew;
			}
		}

		if (HandleKeyPress())
		{
			if (pNewScreen != NULL)
			{
				SetupScreenSprts(pNewScreen);
				bRedrawFrontend = 1;
			}
		}

#ifndef PSX
		DrawScreen(pCurrScreen);
#else
		if (bRedrawFrontend)
		{
			DrawScreen(pCurrScreen);
			EndFrame();

			NewSelection(0);

			bRedrawFrontend = 0;
		}
#endif

		if ((VSync(-1) - idle_timer) > 1800)
		{
			if (ScreenDepth == 0)
			{
				GameType = GAME_IDLEDEMO;

				gCurrentMissionNumber = gIdleReplay + 400;
				
				if (++gIdleReplay == 4)
					gIdleReplay = 0;

				pScreenStack[0] = pCurrScreen;
				pButtonStack[0] = pCurrButton;
				ScreenNames[0] = pCurrButton->Name;

				GameStart();

				pCurrScreen = pScreenStack[0];

				bRedrawFrontend = 1;
				ScreenDepth = 0; // fail-safe?
			}

			idle_timer = VSync(-1);
		}
	} while (bQuitToSystem != 2);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetFEDrawMode()
 // line 2630, offset 0x001c2c2c
	/* begin block 1 */
		// Start line: 2632
		// Start offset: 0x001C2C2C
		// Variables:
	// 		DRAW_MODE *dm; // $s3
	/* end block 1 */
	// End offset: 0x001C2D90
	// End Line: 2687

	/* begin block 2 */
		// Start line: 5839
	/* end block 2 */
	// End Line: 5840

	/* begin block 3 */
		// Start line: 5882
	/* end block 3 */
	// End Line: 5883

	/* begin block 4 */
		// Start line: 5883
	/* end block 4 */
	// End Line: 5884

	/* begin block 5 */
		// Start line: 5893
	/* end block 5 */
	// End Line: 5894

/* WARNING: Unknown calling convention yet parameter storage is locked */


// [D] [T]
void SetFEDrawMode(void)
{
	SetVideoMode(video_mode);

	SetDefDrawEnv(&MPBuff[0][0].draw, draw_mode.x1, draw_mode.y1, 640, 512);
	SetDefDispEnv(&MPBuff[0][0].disp, draw_mode.x1, draw_mode.y1, 640, 512);
	SetDefDrawEnv(&MPBuff[0][1].draw, draw_mode.x1, draw_mode.y1, 640, 512);
	SetDefDispEnv(&MPBuff[0][1].disp, draw_mode.x1, draw_mode.y1, 640, 512);

	MPBuff[0][0].draw.isbg = 0;
	MPBuff[0][0].disp.isinter = 1;
	MPBuff[0][0].draw.dfe = 1;
	MPBuff[0][0].disp.screen.h = 256;
	MPBuff[0][0].primtab = _primTab1;
	MPBuff[0][0].primptr = _primTab1;
	MPBuff[0][0].ot = _OT1;

	MPBuff[0][1].draw.isbg = 0;
	MPBuff[0][1].disp.isinter = 1;
	MPBuff[0][1].draw.dfe = 1;
	MPBuff[0][1].disp.screen.h = 256;
	MPBuff[0][1].primtab = _primTab2;
	MPBuff[0][1].primptr = _primTab2;
	MPBuff[0][1].ot = _OT2;

	last = &MPBuff[0][1];
	current = &MPBuff[0][0];

	MPBuff[0][0].disp.screen.x = draw_mode.framex * 2;
	MPBuff[0][0].disp.screen.y = draw_mode.framey;
	MPBuff[0][1].disp.screen.y = draw_mode.framey;
	MPBuff[0][1].disp.screen.x = MPBuff[0][0].disp.screen.x;

	PutDispEnv(&MPBuff[0][0].disp);
	PutDrawEnv(&current->draw);
}



// decompiled code
// original method signature: 
// void /*$ra*/ EndFrame()
 // line 2695, offset 0x001c6378
	/* begin block 1 */
		// Start line: 2697
		// Start offset: 0x001C6378
		// Variables:
	// 		DB *db_hold; // $a1
	/* end block 1 */
	// End offset: 0x001C6404
	// End Line: 2716

	/* begin block 2 */
		// Start line: 8781
	/* end block 2 */
	// End Line: 8782

	/* begin block 3 */
		// Start line: 5390
	/* end block 3 */
	// End Line: 5391

	/* begin block 4 */
		// Start line: 8782
	/* end block 4 */
	// End Line: 8783

	/* begin block 5 */
		// Start line: 8784
	/* end block 5 */
	// End Line: 8785

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void EndFrame(void)
{
	DB *db_hold;

	DrawSync(0);
	VSync(0);

	PutDispEnv(&current->disp);
	PutDrawEnv(&current->draw);

	db_hold = current;
	current = last;

	last->primptr = last->primtab;
	last = db_hold;

	DrawOTag((u_long*)&db_hold->ot[16]);
	ClearOTagR((u_long*)current->ot, 16);
	VSync(0);

#ifndef PSX
	Emulator_EndScene();
#endif
}


// decompiled code
// original method signature: 
// int /*$ra*/ FEPrintString(char *string /*$t1*/, int x /*$t2*/, int y /*$s4*/, int justification /*$a3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/)
 // line 2745, offset 0x001c2d90
	/* begin block 1 */
		// Start line: 2746
		// Start offset: 0x001C2D90
		// Variables:
	// 		FE_CHARDATA *pFontInfo; // $a0
	// 		SPRT *font; // $t0
	// 		unsigned char let; // $a0
	// 		int counter; // $t4

		/* begin block 1.1 */
			// Start line: 2746
			// Start offset: 0x001C2DEC
			// Variables:
		// 		char *pString; // $a1

			/* begin block 1.1.1 */
				// Start line: 2746
				// Start offset: 0x001C2DEC
				// Variables:
			// 		char let; // $v1
			// 		int w; // $a2
			/* end block 1.1.1 */
			// End offset: 0x001C2E38
			// End Line: 2746
		/* end block 1.1 */
		// End offset: 0x001C2E38
		// End Line: 2746

		/* begin block 1.2 */
			// Start line: 2792
			// Start offset: 0x001C2F28
			// Variables:
		// 		int tpage; // $v1
		/* end block 1.2 */
		// End offset: 0x001C2F28
		// End Line: 2792
	/* end block 1 */
	// End offset: 0x001C2FD8
	// End Line: 2809

	/* begin block 2 */
		// Start line: 6177
	/* end block 2 */
	// End Line: 6178

	/* begin block 3 */
		// Start line: 6236
	/* end block 3 */
	// End Line: 6237

// [D] [T]
int FEPrintString(char *string, int x, int y, int justification, int r, int g, int b)
{
	if (current == NULL || string == NULL)
		return -1;

	FE_CHARDATA *pFontInfo;
	SPRT *font;
	unsigned char let;

	font = (SPRT *)current->primptr;

	if (justification & 4)
	{
		char *pString = string;
		unsigned char c = 0;

		int w = 0;

		while ((c = *pString++) != 0)
		{
			if (c == ' ')
				w += 4;
			else
				w += feFont.CharInfo[c].w;
		}

		x -= w;
	}

	int counter = 0;

	while ((let = *string++) != 0)
	{
		if (let == ' ')
		{
			x += 4;
		}
		else
		{
			pFontInfo = &feFont.CharInfo[let];

			setSprt(font);
#ifdef PSX
			setSemiTrans(font, 1);
#endif

			setRGB0(font, r, g, b);
			setXY0(font, x, y);
			setUV0(font, pFontInfo->u, pFontInfo->v);
			setWH(font, pFontInfo->w, pFontInfo->h);
			// setTPage(font, 0, 0, 640, 256); // [A]
			setClut(font, 960, 257); // [A] seems clut has a transparency bit; width is 256

			addPrim(&current->ot[1], font);
			font++;

			// add space for next character
			x += pFontInfo->w;
		}

		if (++counter >= 32)
			break;
	}

	// set tail
	current->primptr = (char *)font;

	POLY_FT3 *null = (POLY_FT3 *)current->primptr;
	setPolyFT3(null);
	setSemiTrans(null, 1);
	setXY3(null, -1, -1, -1, -1, -1, -1);
	setTPage(null, 0, 0, 640, 256);

	addPrim(&current->ot[1], null);
	null++;

	current->primptr = (char *)null;

	return x;
}



// decompiled code
// original method signature: 
// int /*$ra*/ FEPrintStringSized(char *string /*$t2*/, int x /*$t1*/, int y /*$t7*/, int scale /*$a3*/, int transparent /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
 // line 2817, offset 0x001c2fd8
	/* begin block 1 */
		// Start line: 2818
		// Start offset: 0x001C2FD8
		// Variables:
	// 		POLY_FT4 *font; // $t0
	// 		FE_CHARDATA *pFontInfo; // $a2
	// 		char let; // $v1
	// 		int tpage; // $v0
	// 		int w; // $t3
	// 		int h; // $t4
	/* end block 1 */
	// End offset: 0x001C31FC
	// End Line: 2880

	/* begin block 2 */
		// Start line: 6457
	/* end block 2 */
	// End Line: 6458

	/* begin block 3 */
		// Start line: 6466
	/* end block 3 */
	// End Line: 6467

// [D] [T]
int FEPrintStringSized(char *string, int x, int y, int scale, int transparent, int r, int g, int b)
{
	if (current == NULL || string == NULL)
		return -1;

	POLY_FT4 *font;
	FE_CHARDATA *pFontInfo;
	char let;
	int w;
	int h;

	font = (POLY_FT4 *)current->primptr;

	while ((let = *string++) != 0)
	{
		if (let == '\n')
			continue;

		if (let == ' ')
		{
			// add space
			x += 4;
		}
		else
		{
			pFontInfo = &feFont.CharInfo[let];

			w = (pFontInfo->w * scale) / 4096;
			h = (pFontInfo->h * scale) / 4096;

			setPolyFT4(font);
#ifdef PSX
				setSemiTrans(font, transparent);
#endif

			setRGB0(font, 128, 128, 128);
			setUVWH(font, pFontInfo->u, pFontInfo->v, pFontInfo->w - 1, pFontInfo->h - 1);
			setXYWH(font, x, y, w, h);
			setRGB0(font, r, g, b);
			setTPage(font, 0, 0, 640, 256);
			setClut(font, 960, 257); // [A] seems clut has a transparency bit; width is 256

			addPrim(&current->ot[1], font);
			font++;

			// make room for next character
			x += w;
		}
	}

	// set tail
	current->primptr = (char *)font;

	return x;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CentreScreen(int bSetup /*$a0*/)
 // line 2894, offset 0x001c31fc
	/* begin block 1 */
		// Start line: 6662
	/* end block 1 */
	// End Line: 6663

	/* begin block 2 */
		// Start line: 6677
	/* end block 2 */
	// End Line: 6678

	/* begin block 3 */
		// Start line: 6678
	/* end block 3 */
	// End Line: 6679

SCREEN_LIMITS screen_limits[2] = {
	// min(x/y), max(x/y)
	{ -27,   5, 35, 37 },
	{ -32, -11, 32, 21 },
};

int bScreenSetup = 0;

// [D] [T]
int CentreScreen(int bSetup)
{
	if (bSetup)
		return 0;

#if defined(DEBUG) && !defined(PSX)
	char text[32];

	sprintf(text, "X1: %d, Y1: %d", current->disp.screen.x, current->disp.screen.y);
	FEPrintStringSized(text, 25, 50, 0xC00, 0, 128, 0, 0);

	sprintf(text, "X2: %d, Y2: %d", last->disp.screen.x, last->disp.screen.y);
	FEPrintStringSized(text, 25, 75, 0xC00, 0, 128, 0, 0);
#endif

	if (fePad & 0x40)
	{
		draw_mode_pal.framex = current->disp.screen.x / 2;
		draw_mode_pal.framey = current->disp.screen.y;
		draw_mode_ntsc.framex = current->disp.screen.x / 2;
		draw_mode_ntsc.framey = current->disp.screen.y;
	}
	else if (fePad & 0x10)
	{
		current->disp.screen.x = draw_mode.framex * 2;
		current->disp.screen.y = draw_mode.framey;
		last->disp.screen.x = draw_mode.framex * 2;
		last->disp.screen.y = draw_mode.framey;
	}
	else
	{
		bool done = false;

		if (fePad & 0x1000)
		{
			if (current->disp.screen.y > screen_limits[0].miny)
			{
				current->disp.screen.y--;
				last->disp.screen.y--;
				done = true;
			}
		}
		else if (fePad & 0x4000)
		{
			if (current->disp.screen.y < screen_limits[0].maxy)
			{
				current->disp.screen.y++;
				last->disp.screen.y++;
				done = true;
			}
		}
		else if (fePad & 0x8000)
		{
			if (current->disp.screen.x > screen_limits[0].minx) 
			{
				current->disp.screen.x--;
				last->disp.screen.x--;
				done = true;
			}
		}
		else if (fePad & 0x2000)
		{
			if (current->disp.screen.x < screen_limits[0].maxx)
			{
				current->disp.screen.x++;
				last->disp.screen.x++;
				done = true;
			}
		}
		else
		{
			// unhandled button press
			return 0;
		}

		FESound((done) ? 3 : 1);
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CarSelectScreen(int bSetup /*$a0*/)
 // line 3029, offset 0x001c3430
	/* begin block 1 */
		// Start line: 3031
		// Start offset: 0x001C3430
		// Variables:
	// 		int i; // $a0
	// 		RECT rect; // stack offset -32

		/* begin block 1.1 */
			// Start line: 3145
			// Start offset: 0x001C373C
			// Variables:
		// 		int lastVal; // $a3

			/* begin block 1.1.1 */
				// Start line: 3030
				// Start offset: 0x001C37BC

				/* begin block 1.1.1.1 */
					// Start line: 3030
					// Start offset: 0x001C37BC
					// Variables:
				// 		RECT rect; // stack offset -24
				/* end block 1.1.1.1 */
				// End offset: 0x001C37BC
				// End Line: 3030
			/* end block 1.1.1 */
			// End offset: 0x001C37BC
			// End Line: 3030
		/* end block 1.1 */
		// End offset: 0x001C37BC
		// End Line: 3030

		/* begin block 1.2 */
			// Start line: 3164
			// Start offset: 0x001C37D0
			// Variables:
		// 		int lastVal; // $a3

			/* begin block 1.2.1 */
				// Start line: 3030
				// Start offset: 0x001C3858

				/* begin block 1.2.1.1 */
					// Start line: 3030
					// Start offset: 0x001C3858
					// Variables:
				// 		RECT rect; // stack offset -24
				/* end block 1.2.1.1 */
				// End offset: 0x001C3858
				// End Line: 3030
			/* end block 1.2.1 */
			// End offset: 0x001C3858
			// End Line: 3030
		/* end block 1.2 */
		// End offset: 0x001C3858
		// End Line: 3030
	/* end block 1 */
	// End offset: 0x001C3A60
	// End Line: 3212

	/* begin block 2 */
		// Start line: 6955
	/* end block 2 */
	// End Line: 6956

	/* begin block 3 */
		// Start line: 6956
	/* end block 3 */
	// End Line: 6957

	/* begin block 4 */
		// Start line: 6957
	/* end block 4 */
	// End Line: 6958

// [D] [T]
int CarSelectScreen(int bSetup)
{
	int newSel;
	RECT16 rect;

	newSel = carSelection;
	rect = extraRect;

	if (bSetup)
	{
		bDoingCarSelect = 1;

		// setup secret cars
		if (NumPlayers == 1)
		{
#if defined(DEBUG_OPTIONS) || defined(_DEBUG)
			CarAvailability[0][9] = 1;
			CarAvailability[1][9] = 1;
			CarAvailability[2][9] = 1;
			CarAvailability[3][9] = 1;
#else
			CarAvailability[0][9] = AvailableCheats.cheat5;
			CarAvailability[1][9] = AvailableCheats.cheat6;
			CarAvailability[2][9] = AvailableCheats.cheat7;
			CarAvailability[3][9] = AvailableCheats.cheat8;
#endif
		}

		// setup unlockable cars
		if (gFurthestMission == 40 && NumPlayers == 1)
		{
			for (int i = 4; i < 9; i++)
			{
				if (i != 8)
					CarAvailability[0][i] = 1;	// remove truck

				CarAvailability[1][i] = 1;
				CarAvailability[2][i] = 1;
				CarAvailability[3][i] = 1;
			}
		}
		else
		{
			for (int i = 4; i < 9; i++)
			{
				// unlock the cop car only
				int unlocked = (i == 4) && gFurthestMission == 40;

				CarAvailability[0][i] = unlocked; 
				CarAvailability[1][i] = unlocked;
				CarAvailability[2][i] = unlocked;
				CarAvailability[3][i] = unlocked;
			}
		}

		if (currPlayer != 1) {
			if (NumPlayers == 2)
				FEPrintStringSized("Player 2", 400, 260, 0xc00, 0, 128, 128, 128);

			return 0;
		}

		LoadBackgroundFile("DATA\\CARS\\CARBACK.RAW");

		if (feVariableSave[0] != -1)
		{
			carSelection = feVariableSave[0];
			SetupExtraPoly(gfxNames[GameLevel], carSelection, 0);
		}
		else
		{
			carSelection = 0;

			if (loaded[1] == GameLevel)
			{
				bDrawExtra = 1;

				LoadImage(&rect, (u_long*)_frontend_buffer);
				DrawSync(0);
			}
			else
			{
				SetupExtraPoly(gfxNames[GameLevel], carSelection, 0);
				lastCity = GameLevel;
			}
		}

		feVariableSave[0] = -1;
		feVariableSave[1] = -1;
		feVariableSave[2] = -1;
		feVariableSave[3] = -1;

		lastCutCity = -1;
		currSelIndex = 1;

		pCurrButton = &pCurrScreen->buttons[1];

		return 1;
	}

	if (fePad & 0x10)
	{
		FESound(0);
		bDoneAllready = 1;
#ifdef PSX
		LoadBackgroundFile("DATA\\GFX.RAW");
		bDrawExtra = 0;
#else
		LoadBackgroundFile("DATA\\CITYBACK.RAW");

		if (loaded[0] == -1)
		{
			SetupExtraPoly("DATA\\CITY.RAW", currCity, 0);
		}
		else
		{
			bDrawExtra = 1;

			RECT16 rect = extraRect;
			LoadImage(&rect, (u_long*)(_frontend_buffer + currCity * 0x8000));
			DrawSync(0);
		}
#endif
		currPlayer = 1;
		bDoingCarSelect = 0;
	}

	else if (fePad & 0x40)
	{
		if (currSelIndex == 0)
		{
			// find best-fit for previous vehicle
			do
			{
				newSel--;
				if (newSel < 0)
					newSel = 9;

			} while (CarAvailability[GameLevel][newSel] == 0);

			carSelection = newSel;
		}
		else if (currSelIndex == 2)
		{
			// find best-fit for next vehicle
			do
			{
				newSel++;
				if (newSel > 9)
					newSel = 0;

			} while (CarAvailability[GameLevel][newSel] == 0);

			carSelection = newSel;
		}
		else
		{
			// select the vehicle
			if (currPlayer == 1)
			{
				feVariableSave[0] = carSelection;
				wantedCar[0] = carNumLookup[GameLevel][carSelection];
			}
			else {
				wantedCar[1] = carNumLookup[GameLevel][carSelection];
			}

			// time for player 2 to select their vehicle?
			if (NumPlayers == 2)
				currPlayer++;

			return 0;
		}
		
		rect = extraRect;
		LoadImage(&rect, (u_long *)(_frontend_buffer + carSelection * 0x8000));
		DrawSync(0);

#ifdef PSX
		DisplayOnScreenText();

		addPrim(&current->ot[2], &extraSprt);
		addPrim(&current->ot[3], &extraDummy);

		EndFrame();
#endif
	}
	else if (fePad & 0x1000)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (fePad & 0x4000)
	{
		currSelIndex = pCurrButton->d - 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CopDiffLevelScreen(int bSetup /*$a0*/)
 // line 3220, offset 0x001c6404
	/* begin block 1 */
		// Start line: 5153
	/* end block 1 */
	// End Line: 5154

	/* begin block 2 */
		// Start line: 10615
	/* end block 2 */
	// End Line: 10616

	/* begin block 3 */
		// Start line: 10616
	/* end block 3 */
	// End Line: 10617

/* WARNING: Control flow encountered bad instruction data */

// [D] [T]
int CopDiffLevelScreen(int bSetup)
{
	if (bSetup) 
	{
		pCurrButton = &pCurrScreen->buttons[gCopDifficultyLevel];
		return 1;
	}

	if (fePad & 0x40)
	{
		gCopDifficultyLevel = currSelIndex;
	}
	else if (fePad & 0x1000)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (fePad & 0x4000)
	{
		currSelIndex = pCurrButton->d - 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ VibroOnOffScreen(int bSetup /*$a0*/)
 // line 3256, offset 0x001c3a60
	/* begin block 1 */
		// Start line: 7415
	/* end block 1 */
	// End Line: 7416

	/* begin block 2 */
		// Start line: 7460
	/* end block 2 */
	// End Line: 7461

	/* begin block 3 */
		// Start line: 7461
	/* end block 3 */
	// End Line: 7462

/* WARNING: Control flow encountered bad instruction data */

// [D] [T]
int VibroOnOffScreen(int bSetup)
{
	if (bSetup) 
	{
		currSelIndex = (gVibration ^ 1);
		pCurrButton = &pCurrScreen->buttons[currSelIndex];
		return 1;
	}

	if (fePad & 0x40)
	{
		gVibration = (currSelIndex ^ 1);
	}
	else if (fePad & 0x1000)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (fePad & 0x4000)
	{
		currSelIndex = pCurrButton->d - 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ MissionSelectScreen(int bSetup /*$a0*/)
 // line 3394, offset 0x001c3b1c
	/* begin block 1 */
		// Start line: 3396
		// Start offset: 0x001C3B1C
		// Variables:
	// 		int i; // $a1

		/* begin block 1.1 */
			// Start line: 3423
			// Start offset: 0x001C3BDC
			// Variables:
		// 		int usedB; // $s2
		// 		int done; // $t0
		// 		int bP; // $a3
		// 		int bN; // $s5
		// 		int shift; // $a3
		/* end block 1.1 */
		// End offset: 0x001C40D8
		// End Line: 3552
	/* end block 1 */
	// End offset: 0x001C4338
	// End Line: 3625

	/* begin block 2 */
		// Start line: 7783
	/* end block 2 */
	// End Line: 7784

	/* begin block 3 */
		// Start line: 7784
	/* end block 3 */
	// End Line: 7785

	/* begin block 4 */
		// Start line: 7791
	/* end block 4 */
	// End Line: 7792

// [D] [T]
int MissionSelectScreen(int bSetup)
{
	int i;

	if (bSetup) 
	{
		bMissionSelect = 1;

		if (!missionSetup)
		{
			currMission = minmaxSelections[currCity][0];
			currSelIndex = 0;

			if (GameType == GAME_REPLAYMISSION)
				LoadBackgroundFile("DATA\\CITYBACK.RAW");
		}

		if (feVariableSave[0] != -1) {
			currMission = feVariableSave[0];
			currSelIndex = feVariableSave[1];
			currCity = feVariableSave[2];
		}

		int usedB = 0;

		bool done = false;
		bool bP = false; // 'Previous' button is visible?
		bool bN = false; // 'Next' button is visible?

		for (i = 0; (i < 4) && !done; i++)
		{
			if (botch[currMission + i].missNum > gFurthestMission ||
				currMission + i > minmaxSelections[currCity][1] ||
				currMission + i > 36) 
			{
				done = true;
			}
			else
			{
				usedB++;
			}
		}

		switch (usedB)
		{
		case 1:
			pCurrScreen->buttons[1].u = 2;
			pCurrScreen->buttons[1].d = 2;
			sprintf(pCurrScreen->buttons[1].Name, MissionName[currMission]);
			sprintf(pCurrScreen->buttons[2].Name, NullStr);
			sprintf(pCurrScreen->buttons[3].Name, NullStr);
			sprintf(pCurrScreen->buttons[4].Name, NullStr);
			break;
		case 2:
			pCurrScreen->buttons[1].u = 3;
			pCurrScreen->buttons[1].d = 3;
			pCurrScreen->buttons[2].u = 2;
			pCurrScreen->buttons[2].d = 2;
			sprintf(pCurrScreen->buttons[1].Name, MissionName[currMission]);
			sprintf(pCurrScreen->buttons[2].Name, MissionName[currMission + 1]);
			sprintf(pCurrScreen->buttons[3].Name, NullStr);
			sprintf(pCurrScreen->buttons[4].Name, NullStr);
			break;
		case 3:
			pCurrScreen->buttons[1].u = 4;
			pCurrScreen->buttons[1].d = 3;
			pCurrScreen->buttons[2].u = 2;
			pCurrScreen->buttons[2].d = 4;
			pCurrScreen->buttons[3].u = 3;
			pCurrScreen->buttons[3].d = 2;
			sprintf(pCurrScreen->buttons[1].Name, MissionName[currMission]);
			sprintf(pCurrScreen->buttons[2].Name, MissionName[currMission + 1]);
			sprintf(pCurrScreen->buttons[3].Name, MissionName[currMission + 2]);
			sprintf(pCurrScreen->buttons[4].Name, NullStr);
			break;
		case 4:
			pCurrScreen->buttons[1].u = 5;
			pCurrScreen->buttons[1].d = 3;
			pCurrScreen->buttons[2].u = 2;
			pCurrScreen->buttons[2].d = 4;
			pCurrScreen->buttons[3].u = 3;
			pCurrScreen->buttons[3].d = 5;
			pCurrScreen->buttons[4].u = 4;
			pCurrScreen->buttons[4].d = 2;
			sprintf(pCurrScreen->buttons[1].Name, MissionName[currMission]);
			sprintf(pCurrScreen->buttons[2].Name, MissionName[currMission + 1]);
			sprintf(pCurrScreen->buttons[3].Name, MissionName[currMission + 2]);
			sprintf(pCurrScreen->buttons[4].Name, MissionName[currMission + 3]);
			break;
		}

		if (usedB == 4 &&
			botch[currMission + 4].missNum <= gFurthestMission &&
			currMission + 4 != minmaxSelections[currCity][1])
		{
			bN = true;
		}

		if (bN)
		{
			if (currMission != minmaxSelections[currCity][0])
			{
				bP = true;

				pCurrScreen->buttons[0].u = 6;
				pCurrScreen->buttons[0].d = 2;
				pCurrScreen->buttons[5].u = 5;
				pCurrScreen->buttons[5].d = 1;
				pCurrScreen->buttons[1].u = 1;
				pCurrScreen->buttons[4].d = 6;
				pCurrScreen->buttons[0].action = 0;
				pCurrScreen->buttons[5].action = 0;
			}
			else
			{
				pCurrScreen->buttons[1].u = 6;
				pCurrScreen->buttons[4].d = 6;
				pCurrScreen->buttons[5].u = 5;
				pCurrScreen->buttons[5].d = 2;
				pCurrScreen->buttons[5].action = 0;
				pCurrScreen->buttons[0].action = 0x500;
			}
		}
		else
		{
			if (currMission != minmaxSelections[currCity][0])
			{
				bP = true;

				pCurrScreen->buttons[0].u = usedB + 1;
				pCurrScreen->buttons[0].d = 2;
				pCurrScreen->buttons[1].u = 1;
				pCurrScreen->buttons[usedB].d = 1;
				pCurrScreen->buttons[0].action = 0;
				pCurrScreen->buttons[5].action = 0x500;
			}
			else
			{
				// list missions only
				pCurrScreen->buttons[0].action = 0x500;
				pCurrScreen->buttons[5].action = 0x500;
			}
		}

		if (bP)
		{
			pCurrButton = pCurrScreen->buttons;
			currSelIndex = 0;
		}
		else
		{
			pCurrButton = pCurrScreen->buttons + 1;
			currSelIndex = 1;
		}

		if (loaded[0] == -1)
		{
			SetupExtraPoly("DATA\\CITY.RAW", currCity, 0);
		}
		else
		{
			bDrawExtra = 1;
		}

		feVariableSave[0] = -1;
		feVariableSave[1] = -1;
		feVariableSave[2] = -1;
		feVariableSave[3] = -1;

		missionSetup = 1;

		return 1;
	}

	if (fePad & 0x40)
	{
		i = currMission;

		if (currSelIndex == 0)
		{
			i -= 4;

			if (i < minmaxSelections[currCity][0])
				return 0;
		}
		else if (currSelIndex == 5)
		{
			i += 4;

			if (i > minmaxSelections[currCity][1] || i > gFurthestMission)
				return 0;
		}
		else
		{
			bReturnToMain = 0;
			GameType = GAME_REPLAYMISSION;
			feVariableSave[0] = currMission;
			feVariableSave[1] = currSelIndex;
			feVariableSave[2] = currCity;
			gCurrentMissionNumber = botch[currMission + (currSelIndex - 1)].missNum;

			return 0;
		}

		currMission = i;
		FESound(3);
		fpUserFunctions[pCurrScreen->userFunctionNum - 1](1);
		bRedrawFrontend = 1;

		return 1;
	}
	else if (fePad & 0x10)
	{
		missionSetup = 0;
		bMissionSelect = 0;
	}
	else if (fePad & 0x1000)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (fePad & 0x4000)
	{
		currSelIndex = pCurrButton->d - 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ MissionCityScreen(int bSetup /*$a0*/)
 // line 3632, offset 0x001c4338
	/* begin block 1 */
		// Start line: 3638
		// Start offset: 0x001C4338

		/* begin block 1.1 */
			// Start line: 3703
			// Start offset: 0x001C449C

			/* begin block 1.1.1 */
				// Start line: 3703
				// Start offset: 0x001C449C
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.1.1 */
			// End offset: 0x001C449C
			// End Line: 3703
		/* end block 1.1 */
		// End offset: 0x001C449C
		// End Line: 3703

		/* begin block 1.2 */
			// Start line: 3709
			// Start offset: 0x001C44C4

			/* begin block 1.2.1 */
				// Start line: 3709
				// Start offset: 0x001C44C4
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.2.1 */
			// End offset: 0x001C44C4
			// End Line: 3709
		/* end block 1.2 */
		// End offset: 0x001C44C4
		// End Line: 3709
	/* end block 1 */
	// End offset: 0x001C4600
	// End Line: 3720

	/* begin block 2 */
		// Start line: 8321
	/* end block 2 */
	// End Line: 8322

	/* begin block 3 */
		// Start line: 8329
	/* end block 3 */
	// End Line: 8330

	/* begin block 4 */
		// Start line: 8334
	/* end block 4 */
	// End Line: 8335

// [D] [T]
int MissionCityScreen(int bSetup)
{
	RECT16 rect;

	if (bSetup)
	{
		GameType = GAME_MISSION;

		if (gFurthestMission == 0)
		{
			pCurrScreen->buttons[0].action = 0x300;
			pCurrScreen->buttons[1].action = 0x300;
			pCurrScreen->buttons[2].action = 0x300;
			pCurrScreen->buttons[3].action = 0x300;
		}
		else if (gFurthestMission < 10)
		{
			pCurrScreen->buttons[0].action = 0x113;
			pCurrScreen->buttons[1].action = 0x300;
			pCurrScreen->buttons[2].action = 0x300;
			pCurrScreen->buttons[3].action = 0x300;
		}
		else if (gFurthestMission < 21)
		{
			pCurrScreen->buttons[0].action = 0x113;
			pCurrScreen->buttons[1].action = 0x113;
			pCurrScreen->buttons[2].action = 0x300;
			pCurrScreen->buttons[3].action = 0x300;
		}
		else if (gFurthestMission < 31)
		{
			pCurrScreen->buttons[0].action = 0x113;
			pCurrScreen->buttons[1].action = 0x113;
			pCurrScreen->buttons[2].action = 0x113;
			pCurrScreen->buttons[3].action = 0x300;
		}
		else
		{
			pCurrScreen->buttons[0].action = 0x113;
			pCurrScreen->buttons[1].action = 0x113;
			pCurrScreen->buttons[2].action = 0x113;
			pCurrScreen->buttons[3].action = 0x113;
		}

		LoadBackgroundFile("DATA\\CITYBACK.RAW");

		if (loaded[0] == -1)
		{
			SetupExtraPoly("DATA\\CITY.RAW", 0, 0);
		}
		else
		{
			bDrawExtra = 1;
		}

		return 0;
	}

	if (fePad & 0x10)
	{
		// BUGFIX: unload city image
		loaded[0] = -1;

		bDrawExtra = 0;
		FESound(0);
		bDoneAllready = 1;
		LoadBackgroundFile("DATA\\GFX.RAW");
	}
	else
	{
		if (fePad & 0x1000)
		{
			currCity = pCurrButton->u - 1;
		}
		else if (fePad & 0x4000)
		{
			currCity = pCurrButton->d - 1;
		}
		else
		{
			currCity = pCurrButton->u & 3;
			return 0;
		}

		rect = extraRect;
		LoadImage(&rect, (u_long *)(_frontend_buffer + currCity * 0x8000));
		DrawSync(0);

#ifdef PSX
		DisplayOnScreenText();

		addPrim(&current->ot[2], &extraSprt);
		addPrim(&current->ot[3], &extraDummy);

		EndFrame();
#endif
	}
	
	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CutSceneSelectScreen(int bSetup /*$a0*/)
 // line 3728, offset 0x001c4600
	/* begin block 1 */
		// Start line: 3730
		// Start offset: 0x001C4600
		// Variables:
	// 		RENDER_ARGS renderArgs; // stack offset -48
	// 		int extraVal; // $a0
	// 		RECT rect; // stack offset -24

		/* begin block 1.1 */
			// Start line: 3789
			// Start offset: 0x001C4798

			/* begin block 1.1.1 */
				// Start line: 3789
				// Start offset: 0x001C4798
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.1.1 */
			// End offset: 0x001C4798
			// End Line: 3789
		/* end block 1.1 */
		// End offset: 0x001C4798
		// End Line: 3789

		/* begin block 1.2 */
			// Start line: 3729
			// Start offset: 0x001C4844
			// Variables:
		// 		int offset; // $a1

			/* begin block 1.2.1 */
				// Start line: 3729
				// Start offset: 0x001C4844
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.2.1 */
			// End offset: 0x001C4844
			// End Line: 3729
		/* end block 1.2 */
		// End offset: 0x001C4844
		// End Line: 3729

		/* begin block 1.3 */
			// Start line: 3808
			// Start offset: 0x001C4900

			/* begin block 1.3.1 */
				// Start line: 3808
				// Start offset: 0x001C4900
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.3.1 */
			// End offset: 0x001C4900
			// End Line: 3808
		/* end block 1.3 */
		// End offset: 0x001C4900
		// End Line: 3808

		/* begin block 1.4 */
			// Start line: 3813
			// Start offset: 0x001C4940

			/* begin block 1.4.1 */
				// Start line: 3813
				// Start offset: 0x001C4940
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.4.1 */
			// End offset: 0x001C4940
			// End Line: 3813
		/* end block 1.4 */
		// End offset: 0x001C4940
		// End Line: 3813
	/* end block 1 */
	// End offset: 0x001C4B30
	// End Line: 3847

	/* begin block 2 */
		// Start line: 8520
	/* end block 2 */
	// End Line: 8521

	/* begin block 3 */
		// Start line: 8529
	/* end block 3 */
	// End Line: 8530

	/* begin block 4 */
		// Start line: 8530
	/* end block 4 */
	// End Line: 8531

	/* begin block 5 */
		// Start line: 8534
	/* end block 5 */
	// End Line: 8535

// [D] [T]
int CutSceneSelectScreen(int bSetup)
{
	RECT16 rect;

	rect = extraRect;

	if (bSetup)
	{
		LoadBackgroundFile("DATA\\CUTS\\CUTBACK.RAW");
		currCity = feVariableSave[1];

		if (feVariableSave[0] == -1)
		{
			cutSelection = 0;
			currCity = GameLevel;
		}
		else
		{
			cutSelection = feVariableSave[0];
			feVariableSave[3] = -1;
			feVariableSave[2] = -1;
			feVariableSave[1] = -1;
			feVariableSave[0] = -1;
		}

		if (loaded[2] == GameLevel)
		{
			bDrawExtra = 1;
			LoadImage(&rect, (u_long*)_frontend_buffer + 0x20000);
			DrawSync(0);
		}
		else
		{
			SetupExtraPoly(cutGfxNames[GameLevel], cutSelection, 0x20000);
		}


		bInCutSelect = 1;
		currSelIndex = 1;
		bDoingCutSelect = 1;
		pCurrButton = pCurrScreen->buttons + 1;

		return 1;
	}

	if (fePad & 0x10) 
	{
		bDrawExtra = 0;
		bInCutSelect = 0;
		bDoingCutSelect = 0;
	}
	else if (fePad & 0x40)
	{
		if (currSelIndex == 0)
		{
			if (cutSelection == 0)
			{
				cutSelection = CutAmounts[currCity + 1] - 1;

				if (cutUnlock[gFurthestMission] < CutAmounts[currCity + 1] - 1 + CutAmountsTotal[currCity] + 1)
					cutSelection = cutUnlock[gFurthestMission];
			}
			else
			{
				cutSelection--;
			}
		}
		else
		{
			if (currSelIndex != 2)
			{
				bReturnToMain = 0;
				pCurrButton = pButtonStack[ScreenDepth];
				pScreenStack[ScreenDepth] = pCurrScreen;

				feVariableSave[1] = currCity;
				feVariableSave[0] = cutSelection;

				ScreenNames[ScreenDepth] = pCurrButton->Name;
				StartRender(feVariableSave[0] + CutAmountsTotal[feVariableSave[1]] + 1);

				return 0;
			}

			if (cutSelection == CutAmounts[currCity + 1] - 1 || cutUnlock[gFurthestMission] <= cutSelection + CutAmountsTotal[currCity] + 1)
			{
				cutSelection = 0;
			}
			else
			{
				cutSelection++;
			}
		}

		rect = extraRect;
		LoadImage(&rect, (u_long*)(_frontend_buffer + 0x20000 + cutSelection * 0x8000));
		DrawSync(0);
		DisplayOnScreenText();

#ifdef PSX
		DisplayOnScreenText();

		addPrim(&current->ot[2], &extraSprt);
		addPrim(&current->ot[3], &extraDummy);

		EndFrame();
#endif

		return 0;
	}
	else if (fePad & 0x1000)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (fePad & 0x4000)
	{
		currSelIndex = pCurrButton->d - 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CutSceneCitySelectScreen(int bSetup /*$a0*/)
 // line 3855, offset 0x001c4b30
	/* begin block 1 */
		// Start line: 3857
		// Start offset: 0x001C4B30
		// Variables:
	// 		RECT rect; // stack offset -24

		/* begin block 1.1 */
			// Start line: 3856
			// Start offset: 0x001C4E6C

			/* begin block 1.1.1 */
				// Start line: 3856
				// Start offset: 0x001C4E6C
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.1.1 */
			// End offset: 0x001C4E6C
			// End Line: 3856
		/* end block 1.1 */
		// End offset: 0x001C4E6C
		// End Line: 3856

		/* begin block 1.2 */
			// Start line: 3856
			// Start offset: 0x001C4E6C

			/* begin block 1.2.1 */
				// Start line: 3856
				// Start offset: 0x001C4E6C
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.2.1 */
			// End offset: 0x001C4E6C
			// End Line: 3856
		/* end block 1.2 */
		// End offset: 0x001C4E6C
		// End Line: 3856

		/* begin block 1.3 */
			// Start line: 3856
			// Start offset: 0x001C4EB4

			/* begin block 1.3.1 */
				// Start line: 3856
				// Start offset: 0x001C4EB4
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.3.1 */
			// End offset: 0x001C4EB4
			// End Line: 3856
		/* end block 1.3 */
		// End offset: 0x001C4EB4
		// End Line: 3856

		/* begin block 1.4 */
			// Start line: 3856
			// Start offset: 0x001C4FAC

			/* begin block 1.4.1 */
				// Start line: 3856
				// Start offset: 0x001C4FAC
				// Variables:
			// 		RECT rect; // stack offset -16
			/* end block 1.4.1 */
			// End offset: 0x001C50A0
			// End Line: 3856
		/* end block 1.4 */
		// End offset: 0x001C50A0
		// End Line: 3856
	/* end block 1 */
	// End offset: 0x001C50B0
	// End Line: 3995

	/* begin block 2 */
		// Start line: 8827
	/* end block 2 */
	// End Line: 8828

	/* begin block 3 */
		// Start line: 8836
	/* end block 3 */
	// End Line: 8837

	/* begin block 4 */
		// Start line: 8837
	/* end block 4 */
	// End Line: 8838

// [D] [T]
int CutSceneCitySelectScreen(int bSetup)
{
	RECT16 rect;

	rect = extraRect;

	if (bSetup)
	{
		LoadBackgroundFile("DATA\\CITYBACK.RAW");

		if (feVariableSave[0] == -1)
		{
			if (bDoingCutSelect == 0) {
				currCity = 0;
				bDoingCutSelect = 1;
			}
		}
		else
		{
			currCity = feVariableSave[0];

			feVariableSave[3] = -1;
			feVariableSave[2] = -1;
			feVariableSave[1] = -1;
			feVariableSave[0] = -1;
		}

		pCurrScreen->buttons[0].u = 4;
		pCurrScreen->buttons[3].d = 1;

		if (gFurthestMission == 0) 
		{
			pCurrScreen->buttons[0].action = 0x300;
			pCurrScreen->buttons[1].action = 0x300;
			pCurrScreen->buttons[2].action = 0x300;
			pCurrScreen->buttons[3].action = 0x300;
		}
		else if (gFurthestMission < 10)
		{
			pCurrScreen->buttons[0].action = 0x116;
			pCurrScreen->buttons[1].action = 0x300;
			pCurrScreen->buttons[2].action = 0x300;
			pCurrScreen->buttons[3].action = 0x300;
		}
		else if (gFurthestMission < 21)
		{
			pCurrScreen->buttons[0].action = 0x116;
			pCurrScreen->buttons[1].action = 0x116;
			pCurrScreen->buttons[2].action = 0x300;
			pCurrScreen->buttons[3].action = 0x300;
		}
		else if (gFurthestMission < 31) 
		{
			pCurrScreen->buttons[0].action = 0x116;
			pCurrScreen->buttons[1].action = 0x116;
			pCurrScreen->buttons[2].action = 0x116;
			pCurrScreen->buttons[3].action = 0x300;
		}
		else 
		{
			pCurrScreen->buttons[0].action = 0x116;
			pCurrScreen->buttons[1].action = 0x116;
			pCurrScreen->buttons[2].action = 0x116;
			pCurrScreen->buttons[3].action = 0x116;

			if (gFurthestMission == 40)
			{
				pCurrScreen->buttons[0].u = 5;
				pCurrScreen->buttons[3].d = 5;
			}
		}

		if (loaded[0] == -1)
		{
			SetupExtraPoly("DATA\\CITY.RAW", (currCity != 4) ? currCity : 0, 0);
		}
		else
		{
			bDrawExtra = 1;
			
			if (currCity == 4) 
				LoadImage(&rect, (u_long *)_frontend_buffer);
			else 
				LoadImage(&rect, (u_long *)(_frontend_buffer + currCity * 0x8000));

			DrawSync(0);
		}

		return 0;
	}

	if (fePad & 0x40)
	{
		lastCity = -1;
		lastCutCity = GameLevel;

		if (GameLevel != 4)
		{
			lastCity = -1;
		}
		else
		{
			bReturnToMain = 0;

			pScreenStack[ScreenDepth] = pCurrScreen;
			pButtonStack[ScreenDepth] = pCurrButton;

			ScreenNames[ScreenDepth] = pCurrButton->Name;

			feVariableSave[0] = currCity;

			StartRender(0x60);
		}

		return 0;
	}
	else if (fePad & 0x10)
	{
		FESound(0);
		bDoneAllready = 1;
		LoadBackgroundFile("DATA\\GFX.RAW");
		bDoingCutSelect = 0;
		bDrawExtra = 0;

		return 0;
	}
	else if (fePad & 0x1000)
	{
		currCity = pCurrButton->u - 1;
	}
	else if (fePad & 0x4000)
	{
		currCity = pCurrButton->d - 1;
	}

	GameLevel = currCity;

	rect = extraRect;

	if (GameLevel != 4)
		LoadImage(&rect, (u_long *)(_frontend_buffer + GameLevel * 0x8000));
	else
		LoadImage(&rect, (u_long *)_frontend_buffer);

	DrawSync(0);

#ifdef PSX
	DisplayOnScreenText();

	addPrim(&current->ot[2], &extraSprt);
	addPrim(&current->ot[3], &extraDummy);

	EndFrame();
#endif

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ SetVolumeScreen(int bSetup /*$a0*/)
 // line 4005, offset 0x001c50b0
	/* begin block 1 */
		// Start line: 4007
		// Start offset: 0x001C50B0
		// Variables:
	// 		int last; // $s2
	// 		char text[4]; // stack offset -48
	// 		int ypos[2]; // stack offset -40
	// 		RECT rect; // stack offset -32

		/* begin block 1.1 */
			// Start line: 4048
			// Start offset: 0x001C5254

			/* begin block 1.1.1 */
				// Start line: 4048
				// Start offset: 0x001C5254
				// Variables:
			// 		DB *db_hold; // $a1
			/* end block 1.1.1 */
			// End offset: 0x001C5254
			// End Line: 4048
		/* end block 1.1 */
		// End offset: 0x001C5254
		// End Line: 4048

		/* begin block 1.2 */
			// Start line: 4070
			// Start offset: 0x001C5284

			/* begin block 1.2.1 */
				// Start line: 4070
				// Start offset: 0x001C5284
				// Variables:
			// 		DB *db_hold; // $a1
			/* end block 1.2.1 */
			// End offset: 0x001C5284
			// End Line: 4070
		/* end block 1.2 */
		// End offset: 0x001C5284
		// End Line: 4070

		/* begin block 1.3 */
			// Start line: 4097
			// Start offset: 0x001C52CC

			/* begin block 1.3.1 */
				// Start line: 4097
				// Start offset: 0x001C52CC
				// Variables:
			// 		DB *db_hold; // $a1
			/* end block 1.3.1 */
			// End offset: 0x001C52CC
			// End Line: 4097
		/* end block 1.3 */
		// End offset: 0x001C52CC
		// End Line: 4097

		/* begin block 1.4 */
			// Start line: 4119
			// Start offset: 0x001C5420

			/* begin block 1.4.1 */
				// Start line: 4119
				// Start offset: 0x001C5420
				// Variables:
			// 		DB *db_hold; // $a1
			/* end block 1.4.1 */
			// End offset: 0x001C5530
			// End Line: 4122
		/* end block 1.4 */
		// End offset: 0x001C5530
		// End Line: 4122
	/* end block 1 */
	// End offset: 0x001C55F8
	// End Line: 4148

	/* begin block 2 */
		// Start line: 9157
	/* end block 2 */
	// End Line: 9158

	/* begin block 3 */
		// Start line: 9168
	/* end block 3 */
	// End Line: 9169

	/* begin block 4 */
		// Start line: 9169
	/* end block 4 */
	// End Line: 9170

	/* begin block 5 */
		// Start line: 9172
	/* end block 5 */
	// End Line: 9173

// [D] [T]
int SetVolumeScreen(int bSetup)
{
	int last;
	int ypos[2] = { 292, 338 };
	char text[4];
	RECT16 rect;

	static int masterVolumeHold = 0;
	static int musicVolumeHold = 0;

	if (bSetup) 
	{
		currSelIndex = 0;

		masterVolumeHold = gMasterVolume;
		musicVolumeHold = gMusicVolume;

		LoadBackgroundFile("DATA\\VOL.RAW");

#ifdef PSX
		sprintf(text, "%d", (int)(10000 + gMasterVolume) / 100);
		FEPrintString(text, 152, ypos[0], 2, 128, 128, 128);

		sprintf(text, "%d", (int)(10000 + gMusicVolume) / 100);
		FEPrintString(text, 152, ypos[1], 2, 128, 128, 128);
#endif

		return 0;
	}

#ifndef PSX
	sprintf(text, "%d", (int)(10000 + gMasterVolume) / 100);
	FEPrintString(text, 152, ypos[0], 2, 128, 128, 128);

	sprintf(text, "%d", (int)(10000 + gMusicVolume) / 100);
	FEPrintString(text, 152, ypos[1], 2, 128, 128, 128);
#endif

	// did we make any changes?
	bool update = false;

	currSelIndex = (pCurrButton->u & 3);

	if (fePad & 0x10)
	{
		FESound(0);
		bDoneAllready = 1;

		gMasterVolume = masterVolumeHold;
		gMusicVolume = musicVolumeHold;

		LoadBackgroundFile("DATA\\GFX.RAW");

		SetMasterVolume(gMasterVolume);
		SetXMVolume(gMusicVolume);

		return 0;
	}
	else if (fePad & 0x40)
	{
		if (currSelIndex == 2)
			LoadBackgroundFile("DATA\\GFX.RAW");

		return 0;
	}
	else
	{
		int dir = -1; // -1: no action, 0: limit reached, 1: OK

		if (fePad & 0x8000)
		{
			switch (currSelIndex)
			{
			case 0:
				gMasterVolume -= 100;

				if (gMasterVolume < -10000)
				{
					gMasterVolume = -10000;
					dir = 0;
				}
				else
				{
					dir = 1;
				}

				last = gMasterVolume;
				break;
			case 1:
				gMusicVolume -= 100;

				if (gMusicVolume < -10000)
				{
					gMusicVolume = -10000;
					dir = 0;
				}
				else
				{
					dir = 1;
				}

				last = gMusicVolume;
				break;
			}
		}
		else if (fePad & 0x2000)
		{
			switch (currSelIndex)
			{
			case 0:
				gMasterVolume += 100;

				if (gMasterVolume > 0)
				{
					gMasterVolume = 0;
					dir = 0;
				}
				else
				{
					dir = 1;
				}

				last = gMasterVolume;
				break;
			case 1:
				gMusicVolume += 100;

				if (gMusicVolume > 0)
				{
					gMusicVolume = 0;
					dir = 0;
				}
				else
				{
					dir = 1;
				}

				last = gMusicVolume;
				break;
			}
		}

		if (dir != -1)
		{
			FESound((dir == 1) ? 3 : 1);
			update = true;
		}
	}

	if (update)
	{
		SetMasterVolume(gMasterVolume);
		SetXMVolume(gMusicVolume);

#ifdef PSX
		sprintf(text, "%d", (int)(10000 + last) / 100);
		FEPrintString(text, 152, ypos[currSelIndex], 2, 128, 128, 128);

		sprintf(text, "%d", (int)(10000 + last) / 100);
		FEPrintString(text, 152, ypos[currSelIndex], 2, 0, 0, 0);

		EndFrame(); // [A] inlined
#else
		// don't flush the screen
		return 1;
#endif
	}

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayScoreTable()
 // line 4165, offset 0x001c55f8
	/* begin block 1 */
		// Start line: 4167
		// Start offset: 0x001C55F8
		// Variables:
	// 		int offset; // $a2
	// 		int i; // $s4
	// 		char text[32]; // stack offset -80
	// 		SCORE_ENTRY *pSE; // stack offset -48
	// 		int min; // $v1
	// 		int frac; // $t0
	/* end block 1 */
	// End offset: 0x001C59A0
	// End Line: 4221

	/* begin block 2 */
		// Start line: 9490
	/* end block 2 */
	// End Line: 9491

	/* begin block 3 */
		// Start line: 9508
	/* end block 3 */
	// End Line: 9509

	/* begin block 4 */
		// Start line: 9509
	/* end block 4 */
	// End Line: 9510

	/* begin block 5 */
		// Start line: 9517
	/* end block 5 */
	// End Line: 9518

/* WARNING: Unknown calling convention yet parameter storage is locked */

int GameNum = 0;
CVECTOR scoreCol = { 120, 120, 120 };
CVECTOR otherCol = {125, 115, 34};

char* CityNames[4] = {
	"Chicago",
	"Havana",
	"Las Vegas",
	"Rio De Janeiro"
};

// [D] [T]
void DisplayScoreTable(void)
{
	int time;
	int i;
	int offset;
	char text[32];
	SCORE_ENTRY *pSE;

	gSubGameNumber = GameNum;

	OnScoreTable(&pSE);

	sprintf(text, ScreenNames[ScreenDepth - 1]);
	FEPrintString(text, 20, 200, 2, otherCol.r, otherCol.g, otherCol.b);
	sprintf(text, CityNames[GameLevel]);
	FEPrintString(text, 280, 200, 2, otherCol.r, otherCol.g, otherCol.b);

	if (GameType == GAME_TAKEADRIVE && NumPlayers == 2)
		offset = 48;
	else if (GameType == GAME_COPSANDROBBERS)
		offset = 32;
	else if (GameType == GAME_CAPTURETHEFLAG)
		offset = 40;
	else if (GameType == GAME_CHECKPOINT && NumPlayers == 2)
		offset = 56;
	else
		offset = (GameType - 4U) * 8;

	if (GameType != GAME_PURSUIT && GameType != GAME_SURVIVAL) 
	{
		sprintf(text, "%s", GAMEMODE_AREA_NAME(GameLevel, offset, GameNum));
		FEPrintStringSized(text, 420, 206, 0xc00, 2, otherCol.r, otherCol.g, otherCol.b);
	}

	offset = 240;
	
	for (i = 0; i < 5; i++)
	{
		sprintf(text, pSE[i].name);
		FEPrintString(text, 20, offset, 2, scoreCol.r, scoreCol.g, scoreCol.b);

		if (GameType == GAME_GATERACE || GameType == GAME_TRAILBLAZER) 
		{
			if (pSE[i].items != -1) 
			{
				sprintf(text, "%d", pSE[i].items);
				FEPrintString(text, 140, offset, 2, scoreCol.r, scoreCol.g, scoreCol.b);
			}
		}

		time = pSE[i].time;

		if (time != -1) 
		{
			sprintf(text, "%d:%02d.%02d", time / 180000, time / 3000 - (time / 180000) * 60, (time % 3000) / 30);
			
			FEPrintString(text, 280, offset, 2, scoreCol.r, scoreCol.g, scoreCol.b);
		}

		offset += 36;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ ScoreScreen(int bSetup /*$a0*/)
 // line 4227, offset 0x001c59a0
	/* begin block 1 */
		// Start line: 9657
	/* end block 1 */
	// End Line: 9658

	/* begin block 2 */
		// Start line: 9664
	/* end block 2 */
	// End Line: 9665

	/* begin block 3 */
		// Start line: 9666
	/* end block 3 */
	// End Line: 9667

// [D] [T]
int ScoreScreen(int bSetup)
{
	if (bSetup)
	{
		GameLevel = 0;

		DisplayScoreTable();

		bDoingScores = 1;
		currSelIndex = 0;

		return 0;
	}

	if (fePad & 0x40)
	{
		if (currSelIndex == 0)
		{
			if (GameType == GAME_SURVIVAL || GameType == GAME_PURSUIT)
			{
				if (--GameLevel < 0)
					GameLevel = 3;

				GameNum = 0;
			}
			else
			{
				GameNum ^= 1;
			}
		}
		else
		{
			if (GameType == GAME_SURVIVAL || GameType == GAME_PURSUIT)
			{
				if (++GameLevel > 3)
					GameLevel = 0;

				GameNum = 0;
			}
			else
			{
				GameNum ^= 1;
			}
		}

#ifdef PSX
		DisplayScoreTable();
		bRedrawFrontend = 1;
#endif
	}
	else if (fePad & 0x10)
	{
		bDoingScores = 0;
		return 0;
	}
	else if ((fePad & 0x1000) || (fePad & 0x4000))
	{
		currSelIndex ^= 1;
	}

#ifndef PSX
	DisplayScoreTable();
#endif

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ SubtitlesOnOffScreen(int bSetup /*$a0*/)
 // line 4322, offset 0x001c64b0
	/* begin block 1 */
		// Start line: 12820
	/* end block 1 */
	// End Line: 12821

	/* begin block 2 */
		// Start line: 12821
	/* end block 2 */
	// End Line: 12822

/* WARNING: Control flow encountered bad instruction data */

// [D] [T]
int SubtitlesOnOffScreen(int bSetup)
{
	if (bSetup)
	{
		if (gSubtitles == 0)
		{
			pCurrButton = pCurrScreen->buttons + 1;
		}
		else 
		{
			pCurrButton = pCurrScreen->buttons;
		}

		return 1;
	}
	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CityCutOffScreen(int bSetup /*$a0*/)
 // line 4345, offset 0x001c64fc
	/* begin block 1 */
		// Start line: 12866
	/* end block 1 */
	// End Line: 12867

	/* begin block 2 */
		// Start line: 12867
	/* end block 2 */
	// End Line: 12868

/* WARNING: Control flow encountered bad instruction data */

// [D] [T]
int CityCutOffScreen(int bSetup)
{
	if (bSetup)
	{
		if (gFurthestMission < 20)
			pCurrScreen->buttons[2].action = 0x300;

		if (gFurthestMission < 29)
			pCurrScreen->buttons[3].action = 0x300;

#ifndef PSX
		LoadBackgroundFile("DATA\\CITYBACK.RAW");

		if (lastCity == -1)
			currCity = 0;
		else
			currCity = lastCity;

		if (loaded[0] == -1)
		{
			SetupExtraPoly("DATA\\CITY.RAW", currCity, 0);
		}
		else
		{
			bDrawExtra = 1;

			RECT16 rect = extraRect;
			LoadImage(&rect, (u_long *)(_frontend_buffer + currCity * 0x8000));
			DrawSync(0);
		}
#endif
		return 0;
	}

#ifndef PSX
	/*
	if ((fePad & 0x40U) != 0)
	{
		lastCity = currCity;

		bDrawExtra = 0;

		LoadBackgroundFile("DATA\\GFX.RAW");
		loaded[0] = -1;

		return 0;
	}*/

	if (fePad & 0x10)
	{
		lastCity = -1;

		bDrawExtra = 0;
		FESound(0);
		bDoneAllready = 1;

		LoadBackgroundFile("DATA\\GFX.RAW");
		loaded[0] = -1;

		return 0;
	}
	else if (fePad & 0x1000)
	{
		currCity = pCurrButton->u - 1;
	}
	else if (fePad & 0x4000)
	{
		currCity = pCurrButton->d - 1;
	}
	else
	{
		currCity = pCurrButton->u & 3;
		return 0;
	}

	RECT16 rect = extraRect;
	LoadImage(&rect, (u_long *)(_frontend_buffer + currCity * 0x8000));
	DrawSync(0);
#endif
	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ ControllerScreen(int bSetup /*$a0*/)
 // line 4378, offset 0x001c6548
	/* begin block 1 */
		// Start line: 12932
	/* end block 1 */
	// End Line: 12933

	/* begin block 2 */
		// Start line: 12933
	/* end block 2 */
	// End Line: 12934

char* contNames[2] = {
	"DATA\\CARCONT.RAW",
	"DATA\\TANCONT.RAW"
};

// [D] [T]
int ControllerScreen(int bSetup)
{
	if (bSetup ) 
	{
		bDoingScores = 1;
		currSelIndex = 0;
		pCurrScreen->numButtons = 0;

		LoadBackgroundFile(contNames[currSelIndex]);
	}
	else
	{
		if (fePad & 0x40) 
		{
			currSelIndex = currSelIndex ^ 1;
			LoadBackgroundFile(contNames[currSelIndex]);

			bRedrawFrontend = 1;
		}
		else if (fePad & 0x10)
		{
			bDoingScores = 0;
			LoadBackgroundFile("DATA\\GFX.RAW");
		}
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ MainScreen(int bSetup /*$a0*/)
 // line 4412, offset 0x001c6614
	/* begin block 1 */
		// Start line: 13006
	/* end block 1 */
	// End Line: 13007

	/* begin block 2 */
		// Start line: 13007
	/* end block 2 */
	// End Line: 13008

// [D] [T]
int MainScreen(int bSetup)
{
	if (bSetup) 
	{
		if (numPadsConnected == 2) 
		{
			pCurrScreen->buttons[3].action = 0x106;
		}
		else 
		{
			pCurrScreen->buttons[3].action = 0x300;
		}
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheatScreen(int bSetup /*$a0*/)
 // line 4434, offset 0x001c5b4c
	/* begin block 1 */
		// Start line: 4436
		// Start offset: 0x001C5B4C
		// Variables:
	// 		int numOpen; // $s5
	// 		int i; // $s1
	// 		int k; // $s6
	// 		int *uc; // $s2
	// 		unsigned char cheatOn[12]; // stack offset -104
	// 		int hackLookup1[4]; // stack offset -88
	// 		int hackLookup2[4]; // stack offset -72

		/* begin block 1.1 */
			// Start line: 4473
			// Start offset: 0x001C5C6C
			// Variables:
		// 		int evilRuss[4]; // stack offset -56
		/* end block 1.1 */
		// End offset: 0x001C606C
		// End Line: 4560
	/* end block 1 */
	// End offset: 0x001C60A0
	// End Line: 4568

	/* begin block 2 */
		// Start line: 10082
	/* end block 2 */
	// End Line: 10083

	/* begin block 3 */
		// Start line: 10083
	/* end block 3 */
	// End Line: 10084

	/* begin block 4 */
		// Start line: 10087
	/* end block 4 */
	// End Line: 10088

static char* cheatText[] =
{
	"Sorry, no secrets",
	"Mountain track",
	"Circuit",
	"Invincibility",
	"Immunity",
	"Bonus Gallery"
};

// [D] [T] [A] adding bonus gallery
int CheatScreen(int bSetup)
{
	int i;
	int numOpen;
	int k;
	unsigned char cheatOn[12];
	int evilRuss[5];

	int hackLookup1[5] = {
		0x121,
		0x121,
		0x11E,
		0x11F,
		0,
	};

	int hackLookup2[5] = {
		0xC01, 0xC00, -1, -1, 0xE00
	};

	if (bSetup == 0)
		return 0;

	if (gFurthestMission == 40) 
		numOpen = 5;
	else 
		numOpen = AvailableCheats.cheat1 + AvailableCheats.cheat2 + AvailableCheats.cheat3 + AvailableCheats.cheat4;

	// "Sorry no secrets"
	if (numOpen == 0)
	{
		pCurrScreen->numButtons = 1;
		
		pCurrScreen->buttons[0].u = 1;
		pCurrScreen->buttons[0].d = 1;
		pCurrScreen->buttons[0].action = 0x400;

		sprintf(pCurrScreen->buttons[0].Name, cheatText[0]);

		return 0;
	}

	pCurrScreen->numButtons = numOpen;

	evilRuss[0] = AvailableCheats.cheat1;
	evilRuss[1] = AvailableCheats.cheat2;
	evilRuss[2] = AvailableCheats.cheat3;
	evilRuss[3] = AvailableCheats.cheat4;

	if (numOpen >= 5)
		pCurrScreen->buttons[4] = pCurrScreen->buttons[3];

	k = 0;
	i = 0;

	do {
		if (evilRuss[i] || gFurthestMission == 40)
		{
			sprintf(pCurrScreen->buttons[i].Name, cheatText[i + 1]);
			cheatOn[k++] = i;
		}
		i++;
	} while (i < 5);

	if (numOpen == 2) 
	{
		pCurrScreen->buttons[0].action = hackLookup1[cheatOn[0]];
		pCurrScreen->buttons[1].action = hackLookup1[cheatOn[1]];
	
		pCurrScreen->buttons[0].var = hackLookup2[cheatOn[0]];
		pCurrScreen->buttons[1].var = hackLookup2[cheatOn[1]];
		
		pCurrScreen->buttons[0].d = 2;
		pCurrScreen->buttons[0].u = 2;
		
		pCurrScreen->buttons[1].d = 1;
		pCurrScreen->buttons[1].u = 1;
		
		currSelIndex = 0;
	
		return 0;
	}

	if (numOpen == 1)
	{
		pCurrScreen->buttons[0].action = hackLookup1[cheatOn[0]];
		pCurrScreen->buttons[0].var = hackLookup2[cheatOn[0]];
		pCurrScreen->buttons[0].d = 1;
		pCurrScreen->buttons[0].u = 1;
		
		currSelIndex = 0;
	
		return 0;
	}

	if (numOpen == 3) 
	{
		pCurrScreen->buttons[0].action = hackLookup1[cheatOn[0]];
		pCurrScreen->buttons[1].action = hackLookup1[cheatOn[1]];
		pCurrScreen->buttons[2].action = hackLookup1[cheatOn[2]];
		
		pCurrScreen->buttons[0].var = hackLookup2[cheatOn[0]];
		pCurrScreen->buttons[1].var = hackLookup2[cheatOn[1]];
		pCurrScreen->buttons[2].var = hackLookup2[cheatOn[2]];
		
		pCurrScreen->buttons[0].d = 2;
		pCurrScreen->buttons[0].u = 3;
		
		pCurrScreen->buttons[1].d = 3;
		pCurrScreen->buttons[1].u = 1;
		
		pCurrScreen->buttons[2].d = 1;
		pCurrScreen->buttons[2].u = 2;
		
		currSelIndex = 0;
		return 0;
	}

	if (numOpen >= 4) 
	{
		pCurrScreen->buttons[0].action = hackLookup1[cheatOn[0]];
		pCurrScreen->buttons[1].action = hackLookup1[cheatOn[1]];
		pCurrScreen->buttons[2].action = hackLookup1[cheatOn[2]];
		pCurrScreen->buttons[3].action = hackLookup1[cheatOn[3]];

		pCurrScreen->buttons[0].var = hackLookup2[cheatOn[0]];
		pCurrScreen->buttons[1].var = hackLookup2[cheatOn[1]];
		pCurrScreen->buttons[2].var = hackLookup2[cheatOn[2]];
		pCurrScreen->buttons[3].var = hackLookup2[cheatOn[3]];
		
		pCurrScreen->buttons[0].d = 2;
		pCurrScreen->buttons[0].u = 4;
		
		pCurrScreen->buttons[1].d = 3;
		pCurrScreen->buttons[1].u = 1;
		
		pCurrScreen->buttons[2].d = 4;
		pCurrScreen->buttons[2].u = 2;
		
		pCurrScreen->buttons[3].d = 1;
		pCurrScreen->buttons[3].u = 3;

		if(numOpen >= 5)
		{
			pCurrScreen->buttons[4].action = hackLookup1[cheatOn[4]];
			pCurrScreen->buttons[4].var = hackLookup2[cheatOn[4]];
			pCurrScreen->buttons[4].y += 40;
			pCurrScreen->buttons[4].s_y += 40;

			PsxScreens[40].userFunctionNum = 21;

			pCurrScreen->buttons[0].u = 5;
			pCurrScreen->buttons[3].d = 5;
			
			pCurrScreen->buttons[4].d = 1;
			pCurrScreen->buttons[4].u = 4;
		}

		currSelIndex = 0;
		return 0;
	}

	pCurrScreen->numButtons = 0;
	currSelIndex = 0;

	return 0;
}


// decompiled code
// original method signature: 
// int /*$ra*/ ImmunityOnOffScreen(int bSetup /*$a0*/)
 // line 4575, offset 0x001c6654
	/* begin block 1 */
		// Start line: 13332
	/* end block 1 */
	// End Line: 13333

	/* begin block 2 */
		// Start line: 13333
	/* end block 2 */
	// End Line: 13334

/* WARNING: Control flow encountered bad instruction data */

// [D] [T]
int ImmunityOnOffScreen(int bSetup)
{
	if (bSetup)
	{
		if (gPlayerImmune == 0)
			pCurrButton = pCurrScreen->buttons + 1;
		else
			pCurrButton = pCurrScreen->buttons;
		return 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ InvincibleOnOffScreen(int bSetup /*$a0*/)
 // line 4597, offset 0x001c66a0
	/* begin block 1 */
		// Start line: 13376
	/* end block 1 */
	// End Line: 13377

	/* begin block 2 */
		// Start line: 13377
	/* end block 2 */
	// End Line: 13378

/* WARNING: Control flow encountered bad instruction data */

// [D] [T]
int InvincibleOnOffScreen(int bSetup)
{
	if (bSetup)
	{
		if (gInvincibleCar == 0) 
			pCurrButton = pCurrScreen->buttons + 1;
		else 
			pCurrButton = pCurrScreen->buttons;

		return 1;
	}
	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GamePlayScreen(int bSetup /*$a0*/)
 // line 4619, offset 0x001c66ec
	/* begin block 1 */
		// Start line: 13420
	/* end block 1 */
	// End Line: 13421

	/* begin block 2 */
		// Start line: 13421
	/* end block 2 */
	// End Line: 13422

// [D] [T]
int GamePlayScreen(int bSetup)
{
	if (bSetup)
	{
		pCurrScreen->buttons[2].action = (allowVibration == 0) ? 0x300 : 0x111;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GameNameScreen(int bSetup /*$a0*/)
 // line 4642, offset 0x001c60a0
	/* begin block 1 */
		// Start line: 4644
		// Start offset: 0x001C60A0
		// Variables:
	// 		int offset; // $s3
	/* end block 1 */
	// End offset: 0x001C61AC
	// End Line: 4656

	/* begin block 2 */
		// Start line: 10496
	/* end block 2 */
	// End Line: 10497

	/* begin block 3 */
		// Start line: 10571
	/* end block 3 */
	// End Line: 10572

	/* begin block 4 */
		// Start line: 10572
	/* end block 4 */
	// End Line: 10573

	/* begin block 5 */
		// Start line: 10573
	/* end block 5 */
	// End Line: 10574

// [D] [T]
int GameNameScreen(int bSetup)
{
	int offset;

	if (bSetup) 
	{
		
		if (GameType == GAME_TAKEADRIVE && NumPlayers == 2) 
			offset = 48;
		else if (GameType == GAME_COPSANDROBBERS)
			offset = 32;
		else if (GameType == GAME_CAPTURETHEFLAG)
			offset = 40;
		else if (GameType == GAME_CHECKPOINT && NumPlayers == 2)
			offset = 56;
		else
			offset = (GameType - 4U) * 8;

		strcpy(pCurrScreen->buttons[0].Name, GAMEMODE_AREA_NAME(GameLevel, offset, 0));
		strcpy(pCurrScreen->buttons[1].Name, GAMEMODE_AREA_NAME(GameLevel, offset, 1));
	}

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FEInitCdIcon()
 // line 4671, offset 0x001c61ac
	/* begin block 1 */
		// Start line: 4673
		// Start offset: 0x001C61AC
		// Variables:
	// 		int i; // $a0
	// 		RECT dest; // stack offset -24
	// 		unsigned short *palette; // $a2
	/* end block 1 */
	// End offset: 0x001C62F8
	// End Line: 4709

	/* begin block 2 */
		// Start line: 10614
	/* end block 2 */
	// End Line: 10615

	/* begin block 3 */
		// Start line: 10630
	/* end block 3 */
	// End Line: 10631

	/* begin block 4 */
		// Start line: 10631
	/* end block 4 */
	// End Line: 10632

	/* begin block 5 */
		// Start line: 10633
	/* end block 5 */
	// End Line: 10634

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void FEInitCdIcon(void)
{
	ushort *palette;
	RECT16 rect;

	palette = cd_icon + 10;

	for (int i = 0; i < 14; i++)
	{
		*palette &= 0x7fff;
		palette++;
	}

	cd_icon[10] = 0;
	
	rect.x = 960;
	rect.y = 434;
	rect.w = 8;
	rect.h = 32;
	
	cd_icon[24] |= 0x8000;
	cd_icon[25] |= 0x8000;

	LoadImage(&rect, (u_long *)(cd_icon + 0x18));

	setPolyFT4(&cd_sprite);
	setRGB0(&cd_sprite, 128, 128, 128);
	setUVWH(&cd_sprite, 0, 178, 32, 32);
	setXYWH(&cd_sprite, 80, 38, 38, 21);
	setClut(&cd_sprite, 960, 433);
	setTPage(&cd_sprite, 0, 0, 960, 256);

	bCdIconSetup = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FEDrawCDicon()
 // line 4716, offset 0x001c62f8
	/* begin block 1 */
		// Start line: 4718
		// Start offset: 0x001C62F8
		// Variables:
	// 		unsigned short *palette; // $a1
	// 		int temp; // $a2
	// 		int i; // $a0
	// 		RECT dest; // stack offset -16
	/* end block 1 */
	// End offset: 0x001C6378
	// End Line: 4735

	/* begin block 2 */
		// Start line: 10758
	/* end block 2 */
	// End Line: 10759

	/* begin block 3 */
		// Start line: 10766
	/* end block 3 */
	// End Line: 10767

	/* begin block 4 */
		// Start line: 10767
	/* end block 4 */
	// End Line: 10768

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void FEDrawCDicon(void)
{
	ushort *palette;
	int i;
	RECT16 dest;

	cd_icon[23] = cd_icon[11];
	
	palette = cd_icon + 10;

	for (i = 0; i < 12; i++)
	{
		palette[1] = palette[2];
		palette++;
	}
	
	dest.x = 960;
	dest.y = 433;
	dest.w = 16;
	dest.h = 1;

	LoadImage(&dest, (u_long *)(cd_icon + 10));
	DrawPrim(&cd_sprite);
	DrawSync(0);
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheatNumlayerSelect(int bSetup /*$a0*/)
 // line 4742, offset 0x001c6724
	/* begin block 1 */
		// Start line: 13666
	/* end block 1 */
	// End Line: 13667

	/* begin block 2 */
		// Start line: 13667
	/* end block 2 */
	// End Line: 13668

/* WARNING: Control flow encountered bad instruction data */

// [D] [T]
int CheatNumlayerSelect(int bSetup)
{
	if (bSetup) 
	{
		if (numPadsConnected == 2) 
		{
			pCurrScreen->buttons[1].action = 0x120;
		}
		else 
		{
			pCurrScreen->buttons[1].action = 0x300;
		}
		return 0;
	}
	return 0;
}





