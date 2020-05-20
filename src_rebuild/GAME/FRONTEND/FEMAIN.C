#include "THISDUST.H"
#include "FEMAIN.H"

#include "../C/CD_ICON.H"

#include <string.h>

#include "LIBGPU.H"
#include "LIBETC.H"

#include "../C/SYSTEM.H"
#include "../C/GLAUNCH.H"
#include "../C/MISSION.H"
#include "../C/LOADVIEW.H"
#include "../C/PAD.H"
#include "../C/TIME.H"
#include "../C/PRES.H"
#include "../C/SOUND.H"
#include "../C/DEBRIS.H"
#include "../C/FMVPLAY.H"
#include "../C/SCORES.H"

#include "../MEMCARD/MAIN.H"

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
	"Il fiume rosso",
	"L'obitorio",
	"Il testimone",
	"L'appartamento di Lenny",
	"La setta cubana",
	"L'intruso",
	"L'incontro con Caine",
	"Partenza dalla citt",
	"In cerca di indizi",
	"Partenza",
	"Osservando l'autocarro",
	"L'indizio nella Rosanna Soto",
	"Il cantiere navale",
	"Il colpo",
	"L'arresto di Jericho",
	"Vasquez in Las Vegas",
	"Lo scambio di Jericho",
	"Rapina nella banca",
	"La sala da biliardo",
	"Il sentiero di guerra di Caine",
	"Caine a Rio",
	"Avviso a Jones",
	"La sparatoria",
	"La fuga di Lenny",
	"Lenny takedown",
	"Back to chicago",
	"Vasquez and Caine",
	"Credits"
};


static char* gameNames[64] = {
	"Downtown",
	"Wrigleyville",
	"Necropolis De Colon",
	"Capitolio",
	"Downtown",
	"Upper Strip",
	"Centro",
	"Copacabana",
	"Greektown",
	"Grant Park",
	"Necropolis de Colon",
	"Old Havana",
	"Lakeside",
	"Mid Strip",
	"Copacabana",
	"Santa Tereza",
	"Downtown",
	"Meigs Field",
	"The Docks",
	"Old Havana",
	"North Vegas",
	"Lakeside",
	"Lagoa Rodrigo de Freitas",
	"Praca da Bandeira",
	"Grant Park",
	"Downtown",
	"Old Havana",
	"Vedado",
	"Downtown",
	"Upper Strip",
	"Leblon",
	"Praca da Bandeira",
	"Ukrainian Village",
	"Downtown",
	"Vedado",
	"Necropolis de Colon",
	"Mid Strip",
	"Downtown",
	"Copacabana",
	"Centro",
	"Cabrini Green",
	"River North",
	"Old Havana",
	"Plaza",
	"Lakes",
	"Ghost Town",
	"Flamengo",
	"Centro",
	"River North",
	"Cabrini Green",
	"Plaza",
	"Old Havana",
	"Downtown",
	"Lakes",
	"Centro",
	"Flamengo",
	"River North",
	"Cabrini Green",
	"Old Havana",
	"Plaza de la Revolucion",
	"Ghost Town",
	"North Vegas",
	"Centro",
};

int CarAvailability[4][10] = {
	{1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,0,0},
};

char carNumLookup[4][10] = {
	{0x1, 0x2, 0x3, 0x4, 0x0, 0x8, 0x9, 0xA, 0xB, 0xC},
	{0x1, 0x2, 0x3, 0x4, 0x0, 0x8, 0x9, 0xA, 0xB, 0xC},
	{0x1, 0x2, 0x3, 0x4, 0x0, 0x8, 0x9, 0xA, 0xB, 0xC},
	{0x1, 0x2, 0x3, 0x4, 0x0, 0x8, 0x9, 0xA, 0xB, 0xC},
};

int minmaxSelections[4][2] = {

	{ 0, 8 },
	{ 8, 17 },
	{ 18, 27 },
	{ 28, 37 }
};

BOTCH botch[38] = {
	{ 0x1, &MissionName[0]},
	{ 0x2, &MissionName[1]},
	{ 0x3, &MissionName[2]},
	{ 0x4, &MissionName[3]},
	{ 0x5, &MissionName[4]},
	{ 0x6, &MissionName[5]},
	{ 0x7, &MissionName[6]},
	{ 0x9, &MissionName[7]},
	{ 0xa, &MissionName[8]},
	{ 0xb, &MissionName[9]},
	{ 0xd, &MissionName[10]},
	{ 0xe, &MissionName[11]},
	{ 0xf, &MissionName[12]},
	{ 0x10, &MissionName[13]},
	{ 0x11, &MissionName[14]},
	{ 0x12, &MissionName[15]},
	{ 0x13, &MissionName[16]},
	{ 0x14, &MissionName[17]},
	{ 0x15, &MissionName[18]},
	{ 0x16, &MissionName[19]},
	{ 0x17, &MissionName[20]},
	{ 0x18, &MissionName[21]},
	{ 0x19, &MissionName[22]},
	{ 0x1a, &MissionName[23]},
	{ 0x1b, &MissionName[24]},
	{ 0x1c, &MissionName[25]},
	{ 0x1d, &MissionName[26]},
	{ 0x1e, &MissionName[27]},
	{ 0x1f, &MissionName[28]},
	{ 0x20, &MissionName[29]},
	{ 0x21, &MissionName[30]},
	{ 0x22, &MissionName[31]},
	{ 0x23, &MissionName[32]},
	{ 0x25, &MissionName[33]},
	{ 0x26, &MissionName[34]},
	{ 0x27, &MissionName[35]},
	{ 0x28, &MissionName[36]},
	{ 0,NULL}
};

char ScreenTitle[128];
char ScoreName[128];

int bDoingScores = 0;
int bInCutSelect = 0;
int cutSelection = 0;
int currCity = 0;

int bRedrawFrontend = 0;
int bReturnToMain = 0;

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

// [D]
void SetVariable(int var)
{
	int code = (var >> 8);
	int value = (var & 0xff);

	switch (var >> 8) {
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
		if (value != 0)
			gWantNight = 1;
		break;
	case 5:
		gCurrentMissionNumber = 1;
		GameType = GAME_MISSION;
		break;
	case 6:
		pScreenStack[ScreenDepth] = pCurrScreen;
		pButtonStack[ScreenDepth] = pCurrButton;

		if (value == 1) {
			if (CallMemoryCard(0x11, 0) == 0) {
				ReInitFrontend();
			}
			else {
				StoredGameType = GameType;
				GameType = GAME_LOADEDREPLAY;
				GameStart();
			}
		}
		else {
			CallMemoryCard(0x81, 0);
			ReInitFrontend();
			SetMasterVolume(gMasterVolume);
			SetXMVolume(gMusicVolume);
		}

		break;
	case 7:
		pScreenStack[ScreenDepth] = pCurrScreen;
		pButtonStack[ScreenDepth] = pCurrButton;

		if (value == 0) {
			CallMemoryCard(0x80, 0);
			ReInitFrontend();
		}
		else {
			if (CallMemoryCard(0x21, 0) == 0) {
				ReInitFrontend();
			} else {
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
	// 		struct RECT rect; // stack offset -40
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

// [D]
void LoadFrontendScreens(void)
{
	unsigned char uVar1;
	int iVar2;
	int *local_v1_356;
	int *piVar3;
	char *ptr;
	int iVar4;
	int offset;
	int iVar5;
	int iNumScreens;
	int iVar6;
	int iVar7;
	int iVar8;
	short sVar9;
	RECT16 rect;

	ShowLoadingScreen("GFX\\FELOAD.TIM", 1, 0xc);
	ShowLoading();
	Loadfile("DATA\\SCRS.BIN", _frontend_buffer);

	ptr = _frontend_buffer + 20; // skip header and number of screens
	iNumScreens = (int)_frontend_buffer[16];

	if (iNumScreens) 
	{
		for (int i = 0; i < iNumScreens; i++)
		{
			PsxScreens[i].numButtons = *ptr++;
			PsxScreens[i].userFunctionNum = *ptr++;

			if (PsxScreens[i].numButtons)
			{
				for (int j = 0; j < PsxScreens[i].numButtons; j++)
				{
					memcpy(&PsxScreens[i].buttons[j], ptr, sizeof(PSXBUTTON));
					ptr += sizeof(PSXBUTTON);
				}
			}
		}		
	}

	rect.w = 64;
	rect.h = 256;

	ShowLoading();
	LoadBackgroundFile("DATA\\GFX.RAW");

	sVar9 = 640;
	offset = 0x30000;
	iVar7 = 1;
	
	do {
		iVar7 = iVar7 + -1;
		ShowLoading();
		LoadfileSeg("DATA\\GFX.RAW", _frontend_buffer, offset, 0x8000);
		rect.y = 0x100;
		rect.x = sVar9;
		LoadImage(&rect, (u_long *)_frontend_buffer);
		DrawSync(0);
		sVar9 = sVar9 + 64;
		offset = offset + 0x8000;
	} while (-1 < iVar7);
	ShowLoading();
	
	LoadfileSeg("DATA\\GFX.RAW", _frontend_buffer, 0x58000, 0x8000);
	rect.x = 960;
	rect.y = 256;
	LoadImage(&rect, (u_long *)_frontend_buffer);
	DrawSync(0);

	Loadfile("DATA\\FEFONT.BNK", (char*)&feFont);
	//PadChecks();	// [A] there is a bug too
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
	// 		struct RECT rect; // stack offset -72
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

// [D]
void LoadBackgroundFile(char *name)
{
	int iVar1;
	int iVar2;
	int p;
	int *piVar4;
	RECT16 rect;
	int pages[6];

	iVar1 = 11;
	pages[0] = 0;
	pages[1] = 1;
	pages[2] = 2;
	pages[3] = 3;
	pages[4] = 4;
	pages[5] = 5;
	iVar2 = strcmp(name, "DATA\\GFX.RAW");
	mainScreenLoaded = (iVar2 == 0);
	piVar4 = pages;
	iVar2 = 5;
	rect.w = 0x40;
	rect.h = 0x100;
	do {
		FEDrawCDicon();
		p = *piVar4;
		LoadfileSeg(name, _overlay_buffer, p * 0x8000, 0x8000);
		piVar4 = piVar4 + 1;
		FEDrawCDicon();
		iVar2 = iVar2 + -1;
		rect.y = (short)(p / 6);
		rect.x = ((short)p + rect.y * -6) * 64 + 640;
		rect.y = rect.y * 256;
		LoadImage(&rect, (u_long *)_overlay_buffer);
		FEDrawCDicon();
	} while (-1 < iVar2);
	LoadfileSeg(name, _overlay_buffer, iVar1 * 0x8000, 0x800);
	FEDrawCDicon();
	rect.h = 1;
	rect.y = (short)(iVar1 / 6);
	rect.x = ((short)iVar1 + rect.y * -6) * 64 + 640;
	rect.y = rect.y * 256;
	LoadImage(&rect, (u_long *)_overlay_buffer);
	DrawSync(0);
	SetupBackgroundPolys();
	return;
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

// [D]
void SetupBackgroundPolys(void)
{
	POLY_FT4 *poly;
	int i;

	poly = BackgroundPolys;
	i = 5;
	do {
		setPolyFT4(poly);
		setRGB0(poly, 128, 128, 128);

		i--;
		poly++;
	} while (-1 < i);

	BackgroundPolys[0].x0 = 0;
	BackgroundPolys[0].y0 = 0;
	BackgroundPolys[0].u0 = '\0';
	BackgroundPolys[0].v0 = '\x01';
	BackgroundPolys[0].clut = getClut(960, 256);
	BackgroundPolys[0].x1 = 0x100;
	BackgroundPolys[0].y1 = 0;
	BackgroundPolys[0].u1 = -1;
	BackgroundPolys[0].v1 = '\x01';
	BackgroundPolys[0].tpage = getTPage(0, 0, 640, 0);
	BackgroundPolys[0].x2 = 0;
	BackgroundPolys[0].y2 = 0x100;
	BackgroundPolys[0].u2 = '\0';
	BackgroundPolys[0].v2 = -1;
	BackgroundPolys[0].x3 = 0x100;
	BackgroundPolys[0].y3 = 0x100;
	BackgroundPolys[0].u3 = -1;
	BackgroundPolys[0].v3 = -1;
	BackgroundPolys[1].x0 = 0x100;
	BackgroundPolys[1].y0 = 0;
	BackgroundPolys[1].u0 = '\0';
	BackgroundPolys[1].v0 = '\x01';
	BackgroundPolys[1].clut = getClut(960, 256);
	BackgroundPolys[1].x1 = 0x200;
	BackgroundPolys[1].y1 = 0;
	BackgroundPolys[1].u1 = -1;
	BackgroundPolys[1].v1 = '\x01';
	BackgroundPolys[1].tpage = getTPage(0, 0, 704, 0);
	BackgroundPolys[1].x2 = 0x100;
	BackgroundPolys[1].y2 = 0x100;
	BackgroundPolys[1].u2 = '\0';
	BackgroundPolys[1].v2 = -1;
	BackgroundPolys[1].x3 = 0x200;
	BackgroundPolys[1].y3 = 0x100;
	BackgroundPolys[1].u3 = -1;
	BackgroundPolys[1].v3 = -1;
	BackgroundPolys[2].x0 = 0x200;
	BackgroundPolys[2].y0 = 0;
	BackgroundPolys[2].u0 = '\0';
	BackgroundPolys[2].v0 = '\x01';
	BackgroundPolys[2].clut = getClut(960, 256);
	BackgroundPolys[2].x1 = 0x280;
	BackgroundPolys[2].y1 = 0;
	BackgroundPolys[2].u1 = -0x80;
	BackgroundPolys[2].v1 = '\x01';
	BackgroundPolys[2].tpage = getTPage(0, 0, 768, 0);
	BackgroundPolys[2].x2 = 0x200;
	BackgroundPolys[2].y2 = 0x100;
	BackgroundPolys[2].u2 = '\0';
	BackgroundPolys[2].v2 = -1;
	BackgroundPolys[2].x3 = 0x280;
	BackgroundPolys[2].y3 = 0x100;
	BackgroundPolys[2].u3 = -0x80;
	BackgroundPolys[2].v3 = -1;
	BackgroundPolys[3].x0 = 0;
	BackgroundPolys[3].y0 = 0x100;
	BackgroundPolys[3].u0 = '\0';
	BackgroundPolys[3].v0 = '\0';
	BackgroundPolys[3].clut = getClut(960, 256);
	BackgroundPolys[3].x1 = 0x100;
	BackgroundPolys[3].y1 = 0x100;
	BackgroundPolys[3].u1 = -1;
	BackgroundPolys[3].v1 = '\0';
	BackgroundPolys[3].tpage = getTPage(0, 0, 832, 0);
	BackgroundPolys[3].x2 = 0;
	BackgroundPolys[3].y2 = 0x200;
	BackgroundPolys[3].u2 = '\0';
	BackgroundPolys[3].v2 = -1;
	BackgroundPolys[3].x3 = 0x100;
	BackgroundPolys[3].y3 = 0x200;
	BackgroundPolys[3].u3 = -1;
	BackgroundPolys[3].v3 = -1;
	BackgroundPolys[4].x0 = 0x100;
	BackgroundPolys[4].y0 = 0x100;
	BackgroundPolys[4].u0 = '\0';
	BackgroundPolys[4].v0 = '\0';
	BackgroundPolys[4].clut = getClut(960, 256);
	BackgroundPolys[4].x1 = 0x200;
	BackgroundPolys[4].y1 = 0x100;
	BackgroundPolys[4].u1 = -1;
	BackgroundPolys[4].v1 = '\0';
	BackgroundPolys[4].tpage = getTPage(0, 0, 896, 0);
	BackgroundPolys[4].x2 = 0x100;
	BackgroundPolys[4].y2 = 0x200;
	BackgroundPolys[4].u2 = '\0';
	BackgroundPolys[4].v2 = -1;
	BackgroundPolys[4].x3 = 0x200;
	BackgroundPolys[4].y3 = 0x200;
	BackgroundPolys[4].u3 = -1;
	BackgroundPolys[4].v3 = -1;
	BackgroundPolys[5].x0 = 0x200;
	BackgroundPolys[5].y0 = 0x100;
	BackgroundPolys[5].u0 = '\0';
	BackgroundPolys[5].v0 = '\0';
	BackgroundPolys[5].clut = getClut(960, 256);
	BackgroundPolys[5].x1 = 0x280;
	BackgroundPolys[5].y1 = 0x100;
	BackgroundPolys[5].u1 = -0x80;
	BackgroundPolys[5].v1 = '\0';
	BackgroundPolys[5].tpage = getTPage(0, 0, 960, 0);
	BackgroundPolys[5].x2 = 0x200;
	BackgroundPolys[5].y2 = 0x200;
	BackgroundPolys[5].u2 = '\0';
	BackgroundPolys[5].v2 = -1;
	BackgroundPolys[5].x3 = 0x280;
	BackgroundPolys[5].y3 = 0x200;
	BackgroundPolys[5].u3 = -0x80;
	BackgroundPolys[5].v3 = -1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupScreenSprts(struct PSXSCREEN *pScr /*$a0*/)
 // line 1588, offset 0x001c132c
	/* begin block 1 */
		// Start line: 1589
		// Start offset: 0x001C132C
		// Variables:
	// 		int tpage; // $a1
	// 		struct POLY_FT3 *null; // $v0
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

// [D]
void SetupScreenSprts(PSXSCREEN *pScr)
{
	int result;

	setSprt(&HighlightSprt);
	setRGB0(&HighlightSprt, 128, 128, 128);
	HighlightSprt.x0 = 0x16c;
	HighlightSprt.y0 = 0xc6;
	HighlightSprt.w = 0x100;
	HighlightSprt.u0 = '\0';
	HighlightSprt.v0 = '\0';
	HighlightSprt.h = 0x24;
	setClut(&HighlightSprt, 960, 258);

	setPolyFT4(&HighlightDummy);
	//HighlightDummy.code = '$';
	HighlightDummy.x0 = -1;
	HighlightDummy.y0 = -1;
	HighlightDummy.x1 = -1;
	HighlightDummy.y1 = -1;
	HighlightDummy.x2 = -1;
	HighlightDummy.y2 = -1;
	//setTPage(&HighlightDummy, 0,0, 1728, 256); // feels wrong
	HighlightDummy.tpage = 0x1b;

	pNewScreen = NULL;
	pCurrScreen = pScr;

	if (pScr->userFunctionNum == 0) {
		if (pNewButton == NULL) {
			pCurrButton = pScr->buttons;
		}
		else {
			pCurrButton = pNewButton;
			pNewButton = NULL;
		}
	}
	else {
		result = (fpUserFunctions[pScr->userFunctionNum - 1])(1);
		if (result == 0) {
			if (pNewButton == NULL) {
				pCurrButton = pCurrScreen->buttons;
			}
			else {
				pCurrButton = pNewButton;
				pNewButton = NULL;
			}
		}
	}
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawScreen(struct PSXSCREEN *pScr /*stack 0*/)
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



// [D]
void DrawScreen(PSXSCREEN *pScr)
{
	short sVar1;
	DB *pDVar2;
	u_long *puVar3;
	uint uVar4;
	int local_68;
	char *string;
	POLY_FT4 *pPVar5;
	PSXSCREEN *pPVar6;
	int iVar7;
	PSXBUTTON *pPVar8;
	char *pcVar9;
	char *pcVar10;
	char *string_00;
	char *pcVar11;
	int local_64;
	int local_60;
	char version_info[32];
	int numBtnsToDraw;
	int local_34;
	char *local_30;

	pDVar2 = current;
	pPVar5 = BackgroundPolys;
	iVar7 = 5;
	do {
		addPrim(&pDVar2->ot[0xb], pPVar5);
	
		iVar7 = iVar7 + -1;
		pPVar5 = pPVar5 + 1;
	} while (-1 < iVar7);

	if (pScr == NULL) {
		EndFrame();
	}
	else {
		GetTimeStamp(version_info);

		if ((bDoingCutSelect == 0) || (0x27 < gFurthestMission)) {
			uVar4 = (uint)pScr->numButtons;
		}
		else {
			uVar4 = (uint)pScr->numButtons - 1;
		}
		iVar7 = 0;
		if (0 < (int)uVar4) {
			local_34 = 0;
			pcVar9 = pScr->buttons[0].Name;
			pPVar8 = pScr->buttons;
			pPVar6 = pScr;
			pcVar10 = pcVar9;
			string_00 = pcVar9;
			pcVar11 = pcVar9;
			local_30 = pcVar9;
			do {
				local_68 = *(int *)((int)&pScr->buttons[0].action + local_34) >> 8;
				if (local_68 != 5) {
					if (pPVar8 == pCurrButton) {
						string = pcVar10;
						if (local_68 == 3) {
						LAB_FRNT__001c16a8:
							sVar1 = pPVar6->buttons[0].x;
							local_68 = 0x20;
							local_64 = 0x20;
							local_60 = 0x20;
						}
						else {
							string = pcVar11;
							if ((((bMissionSelect != 0) && ((iVar7 == 0 || (iVar7 == 5)))) ||
								((bDoingCarSelect != 0 && ((iVar7 == 0 || (iVar7 == 2)))))) ||
								((bInCutSelect != 0 && ((iVar7 == 0 || (iVar7 == 2)))))) {
							LAB_FRNT__001c174c:
								FEPrintString(string, (int)pPVar6->buttons[0].x * 2 +
									(int)pPVar6->buttons[0].w,
									(int)pPVar6->buttons[0].y, 4, 0x7c, 0x6c, 0x28);
								goto LAB_FRNT__001c17ac;
							}
							sVar1 = pPVar6->buttons[0].x;
							local_68 = 0x80;
							local_64 = 0x80;
							local_60 = 0x80;
							string = pcVar9;
						}
						FEPrintString(string, (int)sVar1 * 2 + (int)pPVar6->buttons[0].w,
							(int)pPVar6->buttons[0].y, 4, local_68, local_64, local_60);
					}
					else {
						if (local_68 == 3) {
							string = pPVar8->Name;
							goto LAB_FRNT__001c16a8;
						}
						string = local_30;
						if ((((bMissionSelect != 0) && ((iVar7 == 0 || (iVar7 == 5)))) ||
							((bDoingCarSelect != 0 && ((iVar7 == 0 || (iVar7 == 2)))))) ||
							((bInCutSelect != 0 && ((iVar7 == 0 || (iVar7 == 2))))))
							goto LAB_FRNT__001c174c;
						FEPrintString(string_00,
							(int)pPVar6->buttons[0].x * 2 + (int)pPVar6->buttons[0].w,
							(int)pPVar6->buttons[0].y, 4, 0x80, 0x80, 0x80);
					}
				}
			LAB_FRNT__001c17ac:
				pPVar6 = (PSXSCREEN *)(pPVar6->buttons[0].Name + 0x1c);
				string_00 = string_00 + 0x3c;
				pcVar9 = pcVar9 + 0x3c;
				pcVar11 = pcVar11 + 0x3c;
				pcVar10 = pcVar10 + 0x3c;
				pPVar8 = pPVar8 + 1;
				iVar7 = iVar7 + 1;
				local_34 = local_34 + 0x3c;
				local_30 = local_30 + 0x3c;
			} while (iVar7 < (int)uVar4);

#if defined(_DEBUG) || defined(DEBUG_OPTIONS)
			FEPrintString(version_info, 40, 16, 0, 128, 128, 0);
			FEPrintString("--- " GAME_VERSION " ---", 320, 16, 0, 128, 128, 0);
#endif
		}
		SetTextColour(0x80, 0, 0);

		DisplayOnScreenText();
		pDVar2 = current;

		if (bDrawExtra != 0) {
			addPrim(current->ot + 2, &extraSprt);
			addPrim(current->ot + 3, &extraDummy);
		}
	}
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
	0x02, 0x02, 0x02, 0x04, 0x05, 
	0x06, 0x07, 0x07, 0x07, 0x09,
	0x0b, 0x0b, 0x0b, 0x0b, 0x0c,
	0x0c, 0x0d, 0x0d, 0x0e, 0x0f,
	0x11, 0x11, 0x11, 0x11, 0x12,
	0x12, 0x13, 0x13, 0x13, 0x13, 
	0x15, 0x15, 0x15, 0x15, 0x16, 
	0x16, 0x16, 0x17, 0x17, 0x17,
	0x1c };

char* NullStr = "\0";

// [D]
void DisplayOnScreenText(void)
{
	uint transparent;
	char *__src;
	int iVar1;
	char **ppcVar2;

	sprintf(ScreenTitle, NullStr);
	if (padsConnected[0] == 0) {
		transparent = (uint)Pads[0].type;
		if (Pads[0].type == '\0') {
			__src = "Please insert controller into Port 1";
				transparent = 1;
		}
		else {
			if (Pads[0].type != '\x01') {
				return;
			}
			__src = "Incompatible controller in Port 1";
		}
		FEPrintStringSized(__src, 0x28, 400, 0xc00, transparent, 0x40, 0x40, 0x40);
	}
	else {
		if ((bDoingScores == 0) && (iVar1 = 0, bDoingCarSelect == 0)) {
			if (0 < ScreenDepth) {
				ppcVar2 = ScreenNames;
				do {
					if (0 < iVar1) {
						strcat(ScreenTitle, (char *)" - ");
					}
					__src = *ppcVar2;
					ppcVar2 = ppcVar2 + 1;
					strcat(ScreenTitle, __src);
					iVar1 = iVar1 + 1;
				} while (iVar1 < ScreenDepth);
			}
			FEPrintStringSized(ScreenTitle, 0x28, 400, 0xc00, 1, 0x40, 0x40, 0x40);
		}
		if (bInCutSelect != 0) {
			FEPrintStringSized(CutSceneNames[cutSelection + CutAmountsTotal[currCity]], 100, 0xe2,
				0xc00, 1, 0x60, 0x60, 0x60);
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
	// 		struct RECT rect; // stack offset -40
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

// [D]
void SetupExtraPoly(char *fileName, int offset, int offset2)
{
	int iVar1;
	int iVar2;
	char **ppuVar3;
	RECT16 rect;

	rect = extraRect;
	FEDrawCDicon();
	Loadfile(fileName, _frontend_buffer + offset2);
	setSprt(&extraSprt);
	//extraSprt.tag._3_1_ = 4;
	//extraSprt.code = 'd';
	extraSprt.x0 = 100;
	extraSprt.w = 255;
	extraSprt.y0 = 226;
	extraSprt.r0 = 128;
	extraSprt.g0 = 128;
	extraSprt.b0 = 128;
	extraSprt.u0 = '\0';
	extraSprt.v0 = '\0';
	extraSprt.h = 219;
	extraSprt.clut = 0x403c;

	rect.x = 896;
	rect.y = 256;
	rect.w = 64;
	rect.h = 219;

	LoadImage(&rect, (u_long *)(_frontend_buffer + offset2 + offset * 0x8000));
	DrawSync(0);
	VSync(0);
	setPolyFT3(&extraDummy);
	extraDummy.x0 = -1;
	extraDummy.y0 = -1;
	extraDummy.x1 = -1;
	extraDummy.y1 = -1;
	extraDummy.x2 = -1;
	extraDummy.y2 = -1;
	extraDummy.tpage = 0x1e;
	bDrawExtra = 1;
	iVar1 = strcmp(fileName, "DATA\\CITY.RAW");
	if (iVar1 == 0) {
		loaded[0] = 1;
		loaded[1] = -1;
	}
	iVar1 = 0;
	ppuVar3 = gfxNames;
	do {
		iVar2 = strcmp(fileName, *ppuVar3);
		if (iVar2 == 0) {
			loaded[0] = -1;
			loaded[1] = (char)iVar1;
			loaded[2] = -1;
		}
		iVar1 = iVar1 + 1;
		ppuVar3 = ppuVar3 + 1;
	} while (iVar1 < 4);
	iVar1 = 0;
	ppuVar3 = cutGfxNames;
	do {
		iVar2 = strcmp(fileName, *ppuVar3);
		if (iVar2 == 0) {
			loaded[1] = -1;
			loaded[2] = (char)iVar1;
		}
		iVar1 = iVar1 + 1;
		ppuVar3 = ppuVar3 + 1;
	} while (iVar1 < 4);
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

// [D]
void ReInitScreens(void)
{
#ifndef PSX
	bCdIconSetup = 0;
	bDoingScores = 0;
	bInCutSelect = 0;
	cutSelection = 0;
	currCity = 0;

	bRedrawFrontend = 0;
	bReturnToMain = 0;

	idle_timer = 0;
	currPlayer = 1;
	fePad = 0;
	ScreenDepth = 0;

	gIdleReplay = 0;

	loaded[0] = -1;
	loaded[1] = -1;
	loaded[2] = -1;
	padsConnected[0] = 1;
	padsConnected[1] = 0;
	bCdIconSetup = 0;
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
#endif // !PSX

	if (bCdIconSetup == 0) {
		FEInitCdIcon();
	}
	if (bReturnToMain == 0) {
		bReturnToMain = 1;
	}
	else {
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

		if (mainScreenLoaded == 0) 
		{
			bDrawExtra = 0;
			LoadBackgroundFile("DATA\\GFX.RAW");
		}
	}
	pCurrScreen = pScreenStack[ScreenDepth];
	pNewButton = pButtonStack[ScreenDepth];

	SetupScreenSprts(pCurrScreen);
	SetupBackgroundPolys();

	idle_timer = VSync(0xffffffff);

	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ NewSelection(short dir /*$s3*/)
 // line 1991, offset 0x001c1e18
	/* begin block 1 */
		// Start line: 1992
		// Start offset: 0x001C1E18
		// Variables:
	// 		struct RECT rect; // stack offset -48
	// 		struct PSXBUTTON *pNewB; // $s2
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

DR_MOVE In;
DR_MOVE Out;
RECT16 storeRect = { 768, 475, 255, 36 };

// [D]
void NewSelection(short dir)
{
	DB *pDVar1;
	PSXBUTTON *pPVar2;
	PSXBUTTON *pPVar3;
	uint uVar4;
	RECT16 rect;

	pPVar2 = pCurrButton;
	uVar4 = dir;// >> 10; //SEXT24(dir);
	if (pCurrScreen->numButtons == '\0') {
		return;
	}
	if (uVar4 != 0) {
		SetDrawMove(&In, &storeRect, (int)pCurrButton->s_x, (int)pCurrButton->s_y);
		addPrim(current->ot+9, &In);
		//In.tag = In.tag & 0xff000000 | *(uint *)current->ot[9] & 0xffffff;
		//*(uint *)current->ot[9] = *(uint *)current->ot[9] & 0xff000000 | 0x1cc550;
	}
	pPVar3 = pPVar2;
	if ((uVar4 & 0x1000) == 0) {
		if ((uVar4 & 0x4000) == 0) {
			if ((uVar4 & 0x8000) == 0) {
				pPVar3 = pCurrButton;
				if (((uVar4 & 0x2000) == 0) || (pPVar3 = pPVar2, pCurrButton->r == '\0'))
					goto LAB_FRNT__001c1ff4;
				FESound(3);
				uVar4 = (uint)pCurrButton->r;
			}
			else {
				if (pCurrButton->l == '\0') goto LAB_FRNT__001c1ff4;
				FESound(3);
				uVar4 = (uint)pCurrButton->l;
			}
		}
		else {
			if (pCurrButton->d == '\0') goto LAB_FRNT__001c1ff4;
			FESound(3);
			uVar4 = (uint)pCurrButton->d;
		}
	}
	else {
		if (pCurrButton->u == '\0') goto LAB_FRNT__001c1ff4;
		FESound(3);
		uVar4 = (uint)pCurrButton->u;
	}
	pPVar3 = (PSXBUTTON *)&pCurrScreen[-1].buttons[uVar4 + 7].w;
LAB_FRNT__001c1ff4:
	rect.x = pPVar3->s_x;
	rect.y = pPVar3->s_y;
	rect.w = 0xff;
	rect.h = 0x24;
	SetDrawMove(&Out, &rect, (int)storeRect.x, (int)storeRect.y);
	pDVar1 = current;
	addPrim(current->ot+8, &Out);
	//Out.tag = Out.tag & 0xff000000 | *(uint *)current->ot[8] & 0xffffff;

	//*(uint *)current->ot[8] = *(uint *)current->ot[8] & 0xff000000 | 0x1cc570;
	HighlightSprt.x0 = pPVar3->s_x;
	HighlightSprt.y0 = pPVar3->s_y;

	addPrim(pDVar1->ot+6, &HighlightSprt);
	//HighlightSprt.tag = HighlightSprt.tag & 0xff000000 | *(uint *)pDVar1->ot[6] & 0xffffff;
	pCurrButton = pPVar3;

	addPrim(pDVar1->ot + 7, &HighlightDummy);

	if (pPVar3->action >> 8 == 3) {
		FEPrintString(pPVar3->Name, (int)pPVar3->x * 2 + (int)pPVar3->w, (int)pPVar3->y, 4, 0x20, 0x20,
			0x20);
	}
	else {
		if ((((bDoingCarSelect == 0) ||
			((pPVar3 != pCurrScreen->buttons && (pPVar3 != pCurrScreen->buttons + 2)))) &&
			((bMissionSelect == 0 ||
			((pPVar3 != pCurrScreen->buttons && (pPVar3 != pCurrScreen->buttons + 5)))))) &&
			((bInCutSelect == 0 ||
			((pPVar3 != pCurrScreen->buttons && (pPVar3 != pCurrScreen->buttons + 2)))))) 
		{
			FEPrintString(pCurrButton->Name, (int)pCurrButton->x * 2 + (int)pCurrButton->w,
				(int)pCurrButton->y, 4, 0x80, 0x80, 0x80);
		}
		else {
			FEPrintString(pCurrButton->Name, (int)pCurrButton->x * 2 + (int)pCurrButton->w,
				(int)pCurrButton->y, 4, 0x7c, 0x6c, 0x28);
		}
	}
	EndFrame();
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

// [D]
int HandleKeyPress(void)
{
	if ((pCurrScreen == NULL) || (pCurrButton == NULL))
		return 0;

	if (pCurrScreen->userFunctionNum != 0) {
		if ((fpUserFunctions[pCurrScreen->userFunctionNum - 1])(0) != 0)
			fePad = 0;
	}

	if ((fePad & 0x40U) == 0) {
		if ((fePad & 0x10U) == 0) {
			if ((((fePad & 0x5000U) == 0) && ((fePad & 0x8000U) == 0)) &&
				((fePad & 0x2000U) == 0)) {
				return 1;
			}
			NewSelection(fePad);
		}
		else {
			if (0 < ScreenDepth) {
				if (bDoneAllready == 0) {
					FESound(0);
				}
				else {
					bDoneAllready = 0;
				}
				ScreenDepth = ScreenDepth + -1;
				if (ScreenDepth == 0) {
					gWantNight = 0;
					gSubGameNumber = 0;
					NumPlayers = 1;
				}
				pNewScreen = pScreenStack[ScreenDepth];
				pNewButton = pButtonStack[ScreenDepth];
			}
		}
	}
	else {
		int action = pCurrButton->action >> 8;

		if (action != 3) {
			FESound(2);
			
			if (pCurrButton->var != -1)
				SetVariable(pCurrButton->var);

			switch (action)
			{
			case 1:
				pScreenStack[ScreenDepth] = pCurrScreen;
				pButtonStack[ScreenDepth] = pCurrButton;

				ScreenNames[ScreenDepth] = pCurrButton->Name;

				action = (ScreenDepth < 11) ? ScreenDepth + 1 : 10;

				pNewScreen = &PsxScreens[pCurrButton->action & 0xFF];
				ScreenDepth = action;
				break;
			case 2:
				if (((NumPlayers == 2) && (bDoingCarSelect != 0)) && (currPlayer == 2)) {
					(fpUserFunctions[pCurrScreen->userFunctionNum - 1])(1);
					bRedrawFrontend = 1;
				}
				else {
					pScreenStack[ScreenDepth] = pCurrScreen;
					pButtonStack[ScreenDepth] = pCurrButton;

					ScreenNames[ScreenDepth] = pCurrButton->Name;

					GameStart();
				}
				break;
			case 4:
				if (ScreenDepth > 0)
				{
					action = ScreenDepth - 1;

					if (action == 0)
						NumPlayers = 1;

					pNewScreen = pScreenStack[action];
					pNewButton = pButtonStack[action];
					ScreenDepth = action;
				}
				break;
			}
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

// [D]
void PadChecks(void)
{
	int iVar2;

	// TODO: null check for pCurrScreen

	int oldnum = numPadsConnected;

	ReadControllers();
	
	iVar2 = 1;
	numPadsConnected = 0;
	fePad = Pads[0].mapnew;

	for (int i = 0; i < 2; i++) {
		if (Pads[i].type < 2) {
			padsConnected[i] = 0;
		}
		else {
			padsConnected[i] = 1;
			numPadsConnected++;
		}
	}

	if ((oldnum != numPadsConnected) &&
		(((oldnum == 2 || (numPadsConnected == 2)) && (ScreenDepth == 0)))) {
		bRedrawFrontend = 1;
		MainScreen(1);
	}

	if (((Pads[0].dualshock == 0) || (padsConnected[0] == 0)) &&
		((Pads[1].dualshock == 0 || (padsConnected[1] == 0)))) {
		if ((allowVibration == 1) && (allowVibration = 0, pCurrScreen->userFunctionNum == 18)) {
			bRedrawFrontend = 1;
			GamePlayScreen(1);
		}
	}
	else {
		if ((allowVibration == 0) && (allowVibration = 1, pCurrScreen->userFunctionNum == 18)) {
			bRedrawFrontend = 1;
			GamePlayScreen(1);
		}
	}

	if ((oldnum != numPadsConnected) &&
		((((NumPlayers == 2 && (numPadsConnected != NumPlayers)) || (numPadsConnected == 0)) ||
		(padsConnected[0] == 0)))) {
		bReturnToMain = 1;
		bRedrawFrontend = 1;
		fePad = 0x10;
		if (pCurrScreen->userFunctionNum != 0) {
			(fpUserFunctions[pCurrScreen->userFunctionNum - 1])(0);
		}
		fePad = 0;
		if (ScreenDepth != 0) {
			ReInitScreens();
		}
	}
	if (((bRedrawFrontend == 0) && (numPadsConnected != oldnum)) &&
		((gInFrontend != 0 && ((pCurrScreen != NULL && (pCurrScreen->userFunctionNum != 0)))))) {
		(fpUserFunctions[pCurrScreen->userFunctionNum - 1])(1);
		bRedrawFrontend = 1;
	}
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

// [D]
void DoFrontEnd(void)
{
	UNIMPLEMENTED();
	int iVar1;

	ResetGraph(1);
	SetDispMask(0);
	//PadChecks();		// [A] there is a BUG
	bRedrawFrontend = 0;
	gInFrontend = 1;
	idle_timer = VSync(0xffffffff);
	LoadFrontendScreens();
	pCurrScreen = PsxScreens;
	pCurrButton = PsxScreens[0].buttons;
	SetupBackgroundPolys();
	SetupScreenSprts(pCurrScreen);
	SetDispMask(0);
	ResetGraph(0);
	SetFEDrawMode();
	SetVideoMode(video_mode);
	EnableDisplay();
	DrawScreen(pCurrScreen);
	EndFrame();
	NewSelection(0);
	EndFrame();
	EndFrame();
	EndFrame();
	EndFrame();
	EndFrame();
	EndFrame();
	SetDispMask(1);
	FEInitCdIcon();
	do {
		PadChecks();
		if (currPlayer == 2) {
			if (Pads[1].type < 2) {
				if ((fePad & 0x10U) == 0) {
					fePad = 0;
				}
				else {
					fePad = 0x10;
				}
			}
			else {
				fePad = Pads[1].mapnew;
			}
		}
		iVar1 = HandleKeyPress();
		if ((iVar1 != 0) && (pNewScreen != NULL)) {
			SetupScreenSprts(pNewScreen);
			DrawScreen(pCurrScreen);
			EndFrame();
			NewSelection(0);
		}
		if (bRedrawFrontend != 0) {
			DrawScreen(pCurrScreen);
			EndFrame();
			NewSelection(0);
			bRedrawFrontend = 0;
		}

		iVar1 = VSync(0xffffffff);
		if (0x708 < iVar1 - idle_timer) {
			if (ScreenDepth == 0) {
				GameType = GAME_IDLEDEMO;
				gCurrentMissionNumber = gIdleReplay + 400;
				gIdleReplay = gIdleReplay + 1;
				if (gIdleReplay == 4) {
					gIdleReplay = 0;
				}
				pScreenStack[0] = pCurrScreen;
				pButtonStack[0] = pCurrButton;
				ScreenNames[0] = pCurrButton->Name;
				GameStart();
				pCurrScreen = pScreenStack[ScreenDepth];
				bRedrawFrontend = 1;
				ScreenDepth = 0;
			}
			idle_timer = VSync(0xffffffff);
		}

#ifndef PSX
		// [A] Always redraw frontend
		DrawScreen(pCurrScreen);
		NewSelection(0);
#endif
	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetFEDrawMode()
 // line 2630, offset 0x001c2c2c
	/* begin block 1 */
		// Start line: 2632
		// Start offset: 0x001C2C2C
		// Variables:
	// 		struct DRAW_MODE *dm; // $s3
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


// [D]
void SetFEDrawMode(void)
{
	SetVideoMode(video_mode);

	SetDefDrawEnv(&MPBuff[0][0].draw, (int)draw_mode.x1, (int)draw_mode.y1, 0x280, 0x200);
	SetDefDispEnv(&MPBuff[0][0].disp, (int)draw_mode.x1, (int)draw_mode.y1, 0x280, 0x200);
	SetDefDrawEnv(&MPBuff[0][1].draw, (int)draw_mode.x1, (int)draw_mode.y1, 0x280, 0x200);
	SetDefDispEnv(&MPBuff[0][1].disp, (int)draw_mode.x1, (int)draw_mode.y1, 0x280, 0x200);

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

	MPBuff[0][0].disp.screen.x = draw_mode.framex << 1;
	MPBuff[0][0].disp.screen.y = draw_mode.framey;
	MPBuff[0][1].disp.screen.y = draw_mode.framey;
	MPBuff[0][1].disp.screen.x = MPBuff[0][0].disp.screen.x;

	PutDispEnv(&MPBuff[0][0].disp);
	PutDrawEnv(&current->draw);
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ EndFrame()
 // line 2695, offset 0x001c6378
	/* begin block 1 */
		// Start line: 2697
		// Start offset: 0x001C6378
		// Variables:
	// 		struct DB *db_hold; // $a1
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

// [D]
void EndFrame(void)
{
	char **ppcVar1;
	DB *pDVar2;
	DB *pDVar3;

	DrawSync(0);
	VSync(0);
	PutDispEnv(&current->disp);
	PutDrawEnv(&current->draw);

	pDVar3 = last;
	pDVar2 = current;
	ppcVar1 = &last->primtab;
	current = last;
	last = pDVar2;
	pDVar3->primptr = *ppcVar1;

	DrawOTag((u_long*)(pDVar2->ot + 0x10));
	ClearOTagR((u_long*)(current->ot), 0x10);
	VSync(0);
}


// decompiled code
// original method signature: 
// int /*$ra*/ FEPrintString(char *string /*$t1*/, int x /*$t2*/, int y /*$s4*/, int justification /*$a3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/)
 // line 2745, offset 0x001c2d90
	/* begin block 1 */
		// Start line: 2746
		// Start offset: 0x001C2D90
		// Variables:
	// 		struct FE_CHARDATA *pFontInfo; // $a0
	// 		struct SPRT *font; // $t0
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

// [D]
int FEPrintString(char *string, int x, int y, int justification, int r, int g, int b)
{
	char bVar1;
	char bVar2;
	unsigned char uVar3;
	DB *pDVar4;
	int iVar5;
	uint uVar6;
	uint uVar7;
	ulong *puVar8;
	char *pbVar9;
	SPRT *font;
	char *pbVar10;
	int iVar11;

	iVar11 = 0;
	iVar5 = -1;
	if (current != NULL) {
		font = (SPRT *)current->primptr;
		bVar1 = *string;
		uVar7 = (uint)bVar1;
		pbVar10 = (char *)(string + 1);
		iVar5 = x;
		if ((justification & 4U) != 0) {
			iVar5 = 0;
			uVar6 = uVar7;
			pbVar9 = pbVar10;
			bVar2 = bVar1;
			while (bVar2 != 0) {
				if (uVar6 == 0x20) {
					iVar5 = iVar5 + 4;
				}
				else {
					iVar5 = iVar5 + (uint)feFont.CharInfo[uVar6].w;
				}
				bVar2 = *pbVar9;
				uVar6 = (uint)bVar2;
				pbVar9 = pbVar9 + 1;
			}
			iVar5 = x - iVar5;
		}
		if ((bVar1 != 0) && (true)) {
			do {
				if (uVar7 == 0x20) {
					iVar5 = iVar5 + 4;
				}
				else {
					bVar1 = feFont.CharInfo[uVar7].w;
					setSprt(font);
					//font->code = 'f';
#ifdef PSX
					setSemiTrans(font, 1);
#endif

					//font->tpage = 0x1a;	// [A]

					font->r0 = (unsigned char)r;
					font->g0 = (unsigned char)g;
					font->b0 = (unsigned char)b;
					font->x0 = (short)iVar5;
					font->y0 = (short)y;
					font->u0 = feFont.CharInfo[uVar7].u;
					uVar3 = feFont.CharInfo[uVar7].v;
					font->w = (ushort)bVar1;
					font->v0 = uVar3;
					pDVar4 = current;
					bVar2 = feFont.CharInfo[uVar7].h;
					iVar5 = iVar5 + (uint)bVar1;
					font->clut = 0x407c;
					font->h = (ushort)bVar2;
					addPrim(pDVar4->ot+1, font);
					font++;
				}
				iVar11 = iVar11 + 1;
				bVar1 = *pbVar10;
				uVar7 = (uint)bVar1;
				pbVar10 = pbVar10 + 1;
			} while ((bVar1 != 0) && (iVar11 < 0x20));
		}
		current->primptr = (char*)font;

		/*
		// this is not SPRT
		font->code = '&';
		pDVar4 = current;
		font->x0 = -1;
		font->y0 = -1;
		font->w = -1;
		font->h = -1;
		*(undefined2 *)&font[1].r0 = 0xffff;
		*(undefined2 *)&font[1].b0 = 0xffff;
		*(undefined2 *)((int)&font[1].tag + 2) = 0x1a;
		*/

		// [A] - don't use odd poly_ft prims
		DR_TPAGE* tp = (DR_TPAGE*)current->primptr;

		setDrawTPage(tp, 0, 0, 0x1a);
		addPrim(current->ot + 1, tp);

		current->primptr += sizeof(DR_TPAGE);
	}
	return iVar5;
}



// decompiled code
// original method signature: 
// int /*$ra*/ FEPrintStringSized(char *string /*$t2*/, int x /*$t1*/, int y /*$t7*/, int scale /*$a3*/, int transparent /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
 // line 2817, offset 0x001c2fd8
	/* begin block 1 */
		// Start line: 2818
		// Start offset: 0x001C2FD8
		// Variables:
	// 		struct POLY_FT4 *font; // $t0
	// 		struct FE_CHARDATA *pFontInfo; // $a2
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

// [D]
int FEPrintStringSized(char *string, int x, int y, int scale, int transparent, int r, int g, int b)
{
	char bVar1;
	char bVar2;
	unsigned char uVar3;
	short sVar4;
	DB *pDVar5;
	unsigned char uVar6;
	int iVar7;
	short sVar8;
	uint uVar9;
	FE_CHARDATA *pFontInfo;
	POLY_FT4 *font;
	int iVar10;

	iVar7 = -1;
	if (current != NULL) {
		bVar1 = *string;
		font = (POLY_FT4 *)current->primptr;
		iVar7 = x;
		while (bVar1 != 0) {
			bVar1 = *string;
			uVar9 = (uint)bVar1;
			string = (char *)(string + 1);
			iVar10 = iVar7;
			if (bVar1 != 10) {
				if (bVar1 == 0x20) {
					iVar10 = iVar7 + 4;
				}
				else {
					pFontInfo = feFont.CharInfo + uVar9;
					bVar1 = feFont.CharInfo[uVar9].w;
					bVar2 = feFont.CharInfo[uVar9].h;

					setPolyFT4(font);
					//*(undefined *)((int)&font->tag + 3) = 9;
					//font->code = ',';
#ifdef PSX
					setSemiTrans(font, transparent);
#endif
					font->tpage = 0x1a;
					
					font->r0 = 128;
					font->g0 = 128;
					font->b0 = 128;
					font->u0 = pFontInfo->u;
					font->v0 = feFont.CharInfo[uVar9].v;
					font->u1 = feFont.CharInfo[uVar9].w + pFontInfo->u + -1;
					font->v1 = feFont.CharInfo[uVar9].v;
					font->u2 = pFontInfo->u;
					font->v2 = feFont.CharInfo[uVar9].h + feFont.CharInfo[uVar9].v + -1;
					font->u3 = feFont.CharInfo[uVar9].w + pFontInfo->u + -1;
					uVar6 = feFont.CharInfo[uVar9].v;
					uVar3 = feFont.CharInfo[uVar9].h;
					iVar10 = iVar7 + ((int)((uint)bVar1 * scale) >> 0xc);
					sVar4 = (short)y;
					sVar8 = sVar4 + (short)((int)((uint)bVar2 * scale) >> 0xc);
					font->x0 = (short)iVar7;
					font->y0 = sVar4;
					font->x1 = (short)iVar10;
					font->y1 = sVar4;
					font->x2 = (short)iVar7;
					font->y2 = sVar8;
					font->x3 = (short)iVar10;
					font->y3 = sVar8;
					font->clut = 0x407c;
					font->r0 = (unsigned char)r;
					font->v3 = uVar3 + uVar6 + -1;
					font->g0 = (unsigned char)g;
					font->b0 = (unsigned char)b;
					pDVar5 = current;
					addPrim(current->ot + 1, font);
					//font->tag = font->tag & 0xff000000 | current->ot[1] & 0xffffff;
					//uVar9 = (uint)font & 0xffffff;
					font++;
					///pDVar5->ot[1] = pDVar5->ot[1] & 0xff000000 | uVar9;
				}
			}
			bVar1 = *string;
			iVar7 = iVar10;
		}
		*(POLY_FT4 **)&current->primptr = font;
	}
	return iVar7;
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

int CentreScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	DB *pDVar1;
	DB *pDVar2;
	short sVar3;

	pDVar2 = last;
	pDVar1 = current;
	if (bSetup != 0) {
		return 0;
	}
	if (DAT_FRNT__001c6a94 == 0) {
		DAT_FRNT__001c6a94 = 1;
	}
	if ((uRam001cc5dc & 0x2000) == 0) {
		if ((uRam001cc5dc & 0x8000) == 0) {
			if ((uRam001cc5dc & 0x1000) == 0) {
				if ((uRam001cc5dc & 0x4000) == 0) {
					if ((uRam001cc5dc & 0x40) != 0) {
						draw_mode_pal.framex = (current->disp).screen.x >> 1;
						draw_mode_pal.framey = (current->disp).screen.y;
						draw_mode_ntsc.framex = (current->disp).screen.x >> 1;
						draw_mode_ntsc.framey = (current->disp).screen.y;
						return 0;
					}
					if ((uRam001cc5dc & 0x10) == 0) {
						return 0;
					}
					(current->disp).screen.x = draw_mode_pal.framex << 1;
					(pDVar1->disp).screen.y = draw_mode_pal.framey;
					pDVar1 = last;
					(last->disp).screen.x = draw_mode_pal.framex << 1;
					(pDVar1->disp).screen.y = draw_mode_pal.framey;
					return 0;
				}
				if ((current->disp).screen.y < DAT_FRNT__001c6992) {
					(current->disp).screen.y = (current->disp).screen.y + 1;
					sVar3 = (pDVar2->disp).screen.y + 1;
					goto LAB_FRNT__001c3360;
				}
			}
			else {
				if (DAT_FRNT__001c698e < (current->disp).screen.y) {
					(current->disp).screen.y = (current->disp).screen.y + -1;
					sVar3 = (pDVar2->disp).screen.y + -1;
				LAB_FRNT__001c3360:
					(pDVar2->disp).screen.y = sVar3;
					FESound(3);
					return 0;
				}
			}
		}
		else {
			if (DAT_FRNT__001c698c < (current->disp).screen.x) {
				(current->disp).screen.x = (current->disp).screen.x + -1;
				sVar3 = (pDVar2->disp).screen.x + -1;
				goto LAB_FRNT__001c32c0;
			}
		}
	}
	else {
		if ((current->disp).screen.x < DAT_FRNT__001c6990) {
			(current->disp).screen.x = (current->disp).screen.x + 1;
			sVar3 = (pDVar2->disp).screen.x + 1;
		LAB_FRNT__001c32c0:
			(pDVar2->disp).screen.x = sVar3;
			FESound(3);
			return 0;
		}
	}
	FESound(1);
	return 0;*/
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
	// 		struct RECT rect; // stack offset -32

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
				// 		struct RECT rect; // stack offset -24
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
				// 		struct RECT rect; // stack offset -24
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

// [D]
int CarSelectScreen(int bSetup)
{
	char bVar1;
	DB *pDVar2;
	int *piVar3;
	int iVar4;
	int iVar5;
	uint *puVar6;
	RECT16 rect;

	iVar5 = carSelection;
	rect = extraRect;
	if (bSetup == 0) {
		if ((fePad & 0x10U) == 0) {
			if ((fePad & 0x40U) != 0) {
				if (currSelIndex == 0) {
					iVar4 = 9;
					if (carSelection != 0) {
						iVar4 = carSelection + -1;
					}
					while ((carSelection = iVar4,
						CarAvailability[GameLevel][carSelection] == 0 &&
						(carSelection != iVar5))) {
						iVar4 = carSelection + -1;
						if (carSelection + -1 == -1) {
							carSelection = 9;
							iVar4 = carSelection;
						}
					}
				}
				else {
					if (currSelIndex != 2) {
						if (currPlayer == 1) {
							feVariableSave[0] = carSelection;
							wantedCar[0] = carNumLookup[GameLevel][carSelection];
						}
						else {
							wantedCar[1] = carNumLookup[GameLevel][carSelection];
						}
						if (NumPlayers == 2) {
							currPlayer = currPlayer + 1;
							return 0;
						}
						return 0;
					}
					if (carSelection == 9) {
						carSelection = 0;
					}
					else {
						carSelection = carSelection + 1;
					}
					while ((CarAvailability[GameLevel][carSelection] == 0 &&
						(iVar4 = carSelection + 1, carSelection != iVar5))) {
						carSelection = iVar4;
						if (iVar4 == 10) {
							carSelection = 0;
						}
					}
				}
				rect = extraRect;
				LoadImage(&rect, (u_long *)(_frontend_buffer + carSelection * 0x8000));
				DrawSync(0);
				DisplayOnScreenText();

				pDVar2 = current;

				addPrim(current->ot + 2, &extraSprt);
				addPrim(current->ot + 3, &extraDummy);

				EndFrame();
				return 0;
			}
			if ((fePad & 0x1000U) == 0) {
				if ((fePad & 0x4000U) == 0) {
					return 0;
				}
				bVar1 = pCurrButton->d;
			}
			else {
				bVar1 = pCurrButton->u;
			}
			currSelIndex = (uint)bVar1 - 1;
		}
		else {
			FESound(0);
			bDoneAllready = 1;
			LoadBackgroundFile("DATA\\GFX.RAW");
			currPlayer = 1;
			bDrawExtra = 0;
			bDoingCarSelect = 0;
		}
		return 0;
	}
	bDoingCarSelect = 1;
	if (NumPlayers == 1) {
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
	if ((gFurthestMission == 0x28) && (NumPlayers == 1)) {
		iVar5 = 4;
		piVar3 = (int*)CarAvailability + 4;
		do {
			if (iVar5 != 8) {
				*piVar3 = 1;
			}
			piVar3[10] = 1;
			piVar3[0x14] = 1;
			piVar3[0x1e] = 1;
			iVar5 = iVar5 + 1;
			piVar3 = piVar3 + 1;
		} while (iVar5 < 9);
	}
	else {
		piVar3 = (int*)CarAvailability + 4;
		iVar5 = 4;
		do {
			*piVar3 = 0;
			piVar3[10] = 0;
			piVar3[0x14] = 0;
			piVar3[0x1e] = 0;
			iVar5 = iVar5 + -1;
			piVar3 = piVar3 + 1;
		} while (-1 < iVar5);
	}
	if (currPlayer != 1) {
		if (NumPlayers == 2) {
			FEPrintStringSized("Player 2", 400, 0x104, 0xc00, 0,
				0x80, 0x80, 0x80);
			return 0;
		}
		return 0;
	}
	if (feVariableSave[0] == -1) {
		carSelection = 0;
		if (loaded[1] == GameLevel) {
			bDrawExtra = currPlayer;
			LoadImage(&rect, (u_long*)_frontend_buffer);
		}
		else {
			SetupExtraPoly(gfxNames[GameLevel], 0, 0);
			lastCity = GameLevel;
		}
	}
	else {
		carSelection = feVariableSave[0];
		SetupExtraPoly(gfxNames[GameLevel], feVariableSave[0], 0);
	}
	LoadBackgroundFile("DATA\\CARS\\CARBACK.RAW");
	feVariableSave[0] = -1;
	feVariableSave[1] = -1;
	feVariableSave[2] = -1;
	feVariableSave[3] = -1;
	lastCutCity = -1;
	currSelIndex = 1;
	pCurrButton = pCurrScreen->buttons + 1;
	return 1;
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

int CopDiffLevelScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;

	/* WARNING: Bad instruction - Truncating control flow here */
	//halt_baddata();
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

int VibroOnOffScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*

	/* WARNING: Bad instruction - Truncating control flow here */
	//halt_baddata();
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

// [D]
int MissionSelectScreen(int bSetup)
{
	unsigned char bVar1;
	bool bVar2;
	bool bVar3;
	unsigned char uVar4;
	PSXSCREEN *pPVar5;
	BOTCH *pBVar6;
	int iVar7;
	int iVar8;

	if (bSetup == 0) 
	{
		if ((fePad & 0x40U) == 0)
		{
			if ((fePad & 0x10U) == 0) 
			{
				if ((fePad & 0x1000U) == 0) 
				{
					if ((fePad & 0x4000U) == 0) 
					{
						return 0;
					}
					bVar1 = pCurrButton->d;
				}
				else 
				{
					bVar1 = pCurrButton->u;
				}
				currSelIndex = bVar1 - 1;
			}
			else
			{
				missionSetup = 0;
				bMissionSelect = 0;
			}
		}
		else 
		{
			if (currSelIndex == 5) 
			{
				iVar7 = currMission + 4;
				if ((iVar7 < minmaxSelections[currCity][1]) && (iVar7 < gFurthestMission))
				{
				LAB_FRNT__001c41fc:
					currMission = iVar7;
					FESound(3);
					fpUserFunctions[pCurrScreen->userFunctionNum-1](1);
					bRedrawFrontend = 1;
					return 1;
				}
			}
			else 
			{
				if (currSelIndex == 0)
				{
					if (minmaxSelections[currCity][0] < currMission)
					{
						iVar7 = currMission + -4;
						goto LAB_FRNT__001c41fc;
					}
				}
				else
				{
					bReturnToMain = 0;
					GameType = GAME_REPLAYMISSION;
					feVariableSave[1] = currSelIndex;
					feVariableSave[0] = currMission;
					feVariableSave[2] = currCity;
					gCurrentMissionNumber = botch[currMission + currSelIndex + -1].missNum;
				}
			}
		}
		return 0;
	}

	bMissionSelect = 1;
	if (missionSetup == 0)
	{
		currMission = minmaxSelections[currCity][0];
		currSelIndex = 0;

		if (GameType == GAME_REPLAYMISSION) 
		{
			LoadBackgroundFile("DATA\\CITYBACK.RAW");
		}
	}

	pPVar5 = pCurrScreen;
	if (feVariableSave[0] != -1) {
		currMission = feVariableSave[0];
		currSelIndex = feVariableSave[1];
		currCity = feVariableSave[2];
	}
	iVar8 = 0;
	bVar2 = false;
	bVar3 = false;
	iVar7 = 0;
	pBVar6 = botch + currMission;
	do {
		if (((gFurthestMission < pBVar6->missNum) ||
			(minmaxSelections[currCity][1] < iVar7 + currMission)) ||
			(0x24 < iVar7 + currMission)) {
			bVar2 = true;
		}
		else {
			iVar8 = iVar8 + 1;
		}
		iVar7 = iVar7 + 1;
		pBVar6 = pBVar6 + 1;
	} while ((iVar7 < 4) && (!bVar2));
	uVar4 = iVar8;
	if (iVar8 == 1) 
	{
		pCurrScreen->buttons[1].d = '\x02';
		pPVar5->buttons[1].u = '\x02';
		sprintf(pCurrScreen->buttons[1].Name, MissionName[currMission]);
		sprintf(pCurrScreen->buttons[2].Name, NullStr);
		sprintf(pCurrScreen->buttons[3].Name, NullStr);
	LAB_FRNT__001c3e3c:
		sprintf(pCurrScreen->buttons[4].Name, NullStr);
	}
	else 
	{
		if (iVar8 == 2)
		{
			pCurrScreen->buttons[1].u = '\x03';
			pCurrScreen->buttons[1].d = '\x03';
			pCurrScreen->buttons[2].u = uVar4;
			pCurrScreen->buttons[2].d = uVar4;
			sprintf(pCurrScreen->buttons[1].Name, MissionName[currMission]);
			sprintf(pCurrScreen->buttons[2].Name, MissionName[currMission + 1]);
			sprintf(pCurrScreen->buttons[3].Name, NullStr);
			goto LAB_FRNT__001c3e3c;
		}
		if (iVar8 == 3)
		{
			pCurrScreen->buttons[1].u = '\x04';
			pCurrScreen->buttons[1].d = uVar4;
			pCurrScreen->buttons[2].u = '\x02';
			pCurrScreen->buttons[2].d = '\x04';
			pCurrScreen->buttons[3].u = uVar4;
			pCurrScreen->buttons[3].d = '\x02';
			sprintf(pCurrScreen->buttons[1].Name, MissionName[currMission]);
			sprintf(pCurrScreen->buttons[2].Name, MissionName[currMission + 1]);
			sprintf(pCurrScreen->buttons[3].Name, MissionName[currMission + 2]);
			goto LAB_FRNT__001c3e3c;
		}
		if (iVar8 == 4)
		{
			pCurrScreen->buttons[1].u = '\x05';
			pCurrScreen->buttons[1].d = '\x03';
			pCurrScreen->buttons[2].u = '\x02';
			pCurrScreen->buttons[2].d = uVar4;
			pCurrScreen->buttons[3].u = '\x03';
			pCurrScreen->buttons[3].d = '\x05';
			pCurrScreen->buttons[4].u = uVar4;
			pCurrScreen->buttons[4].d = '\x02';
			sprintf(pCurrScreen->buttons[1].Name, MissionName[currMission]);
			sprintf(pCurrScreen->buttons[2].Name, MissionName[currMission + 1]);
			sprintf(pCurrScreen->buttons[3].Name, MissionName[currMission + 2]);
			sprintf(pCurrScreen->buttons[4].Name, MissionName[currMission + 3]);
		}
	}

	pPVar5 = pCurrScreen;

	if (((iVar8 == 4) && (botch[currMission + 4].missNum <= gFurthestMission)) && (currMission + 4 != minmaxSelections[currCity][1])) 
	{
		bVar3 = true;
	}

	if (bVar3) 
	{
		if (currMission == minmaxSelections[currCity][0]) 
		{
		LAB_FRNT__001c406c:
			if (bVar3) 
			{
				pCurrScreen->buttons[1].u = '\x06';
				pCurrScreen->buttons[4].d = '\x06';
				pCurrScreen->buttons[5].u = '\x05';
				pCurrScreen->buttons[5].d = '\x02';
				pPVar5 = pCurrScreen;
				pCurrScreen->buttons[5].action = 0;
				pPVar5->buttons[0].action = 0x500;
			}
			else
			{
				pCurrScreen->buttons[0].action = 0x500;
				pPVar5->buttons[5].action = 0x500;
			}

			pCurrButton = pPVar5->buttons + 1;
			currSelIndex = 1;
			goto LAB_FRNT__001c40d8;
		}
		pCurrScreen->buttons[0].u = '\x06';
		pCurrScreen->buttons[0].d = '\x02';
		pCurrScreen->buttons[5].u = '\x05';
		pCurrScreen->buttons[5].d = '\x01';
		pCurrScreen->buttons[1].u = '\x01';
		pCurrScreen->buttons[4].d = '\x06';
		pPVar5 = pCurrScreen;
		pCurrScreen->buttons[0].action = 0;
		pPVar5->buttons[5].action = 0;
	}
	else 
	{
		if (currMission == minmaxSelections[currCity][0])
			goto LAB_FRNT__001c406c;

		pCurrScreen->buttons[0].u = uVar4 + '\x01';
		pCurrScreen->buttons[0].d = '\x02';
		pCurrScreen->buttons[1].u = '\x01';
		pCurrScreen->buttons[iVar8].d = '\x01';
		pPVar5 = pCurrScreen;
		pCurrScreen->buttons[0].action = 0;
		pPVar5->buttons[5].action = 0x500;
	}
	pCurrButton = pPVar5->buttons;
	currSelIndex = 0;

LAB_FRNT__001c40d8:
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
			// 		struct RECT rect; // stack offset -16
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
			// 		struct RECT rect; // stack offset -16
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

// [D]
int MissionCityScreen(int bSetup)
{
	unsigned char bVar1;
	DB *pDVar2;
	PSXSCREEN *pPVar3;
	int iVar4;
	uint *puVar5;
	RECT16 rect;

	pPVar3 = pCurrScreen;
	if (bSetup == 0)
	{
		if ((fePad & 0x10U) != 0) 
		{
			bDrawExtra = 0;
			FESound(0);
			bDoneAllready = 1;
			LoadBackgroundFile("DATA\\GFX.RAW");
			return 0;
		}

		if ((fePad & 0x1000U) == 0) 
		{
			if ((fePad & 0x4000U) == 0) 
			{
				currCity = (uint)pCurrButton->u & 3;
				return 0;
			}
			bVar1 = pCurrButton->d;
		}
		else 
		{
			bVar1 = pCurrButton->u;
		}

		rect = extraRect;
		currCity = (uint)bVar1 - 1;
		LoadImage(&rect, (u_long *)(_frontend_buffer + currCity * 0x8000));

		DrawSync(0);
		DisplayOnScreenText();

		addPrim(current->ot + 2, &extraSprt);
		addPrim(current->ot + 2, &extraDummy);

		EndFrame();
		return 0;
	}
	GameType = GAME_MISSION;
	if (gFurthestMission == 0)
	{
		iVar4 = 0x300;
	LAB_FRNT__001c43f4:
		pCurrScreen->buttons[0].action = iVar4;
		pPVar3->buttons[1].action = iVar4;
		pPVar3->buttons[2].action = iVar4;
	}
	else
	{
		if (gFurthestMission < 10)
		{
			pCurrScreen->buttons[0].action = 0x113;
			pPVar3->buttons[1].action = 0x300;
			pPVar3->buttons[2].action = 0x300;
			pPVar3->buttons[3].action = 0x300;
			goto LAB_FRNT__001c4404;
		}
		if (gFurthestMission < 0x15)
		{
			pCurrScreen->buttons[0].action = 0x113;
			pPVar3->buttons[1].action = 0x113;
			pPVar3->buttons[2].action = 0x300;
			pPVar3->buttons[3].action = 0x300;
			goto LAB_FRNT__001c4404;
		}
		if (0x1e < gFurthestMission)
		{
			iVar4 = 0x113;
			goto LAB_FRNT__001c43f4;
		}
		iVar4 = 0x300;
		pCurrScreen->buttons[0].action = 0x113;
		pPVar3->buttons[1].action = 0x113;
		pPVar3->buttons[2].action = 0x113;
	}

	pPVar3->buttons[3].action = iVar4;
LAB_FRNT__001c4404:

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



// decompiled code
// original method signature: 
// int /*$ra*/ CutSceneSelectScreen(int bSetup /*$a0*/)
 // line 3728, offset 0x001c4600
	/* begin block 1 */
		// Start line: 3730
		// Start offset: 0x001C4600
		// Variables:
	// 		struct RENDER_ARGS renderArgs; // stack offset -48
	// 		int extraVal; // $a0
	// 		struct RECT rect; // stack offset -24

		/* begin block 1.1 */
			// Start line: 3789
			// Start offset: 0x001C4798

			/* begin block 1.1.1 */
				// Start line: 3789
				// Start offset: 0x001C4798
				// Variables:
			// 		struct RECT rect; // stack offset -16
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
			// 		struct RECT rect; // stack offset -16
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
			// 		struct RECT rect; // stack offset -16
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
			// 		struct RECT rect; // stack offset -16
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

int CutSceneSelectScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	DB *pDVar2;
	PSXBUTTON *pPVar3;
	int iVar4;
	uint *puVar5;
	PSXBUTTON **ppPVar6;
	undefined *puVar7;
	undefined4 local_18;
	undefined4 local_14;
	undefined4 local_10;
	undefined4 local_c;

	iVar4 = ScreenDepth;
	local_18 = DAT_FRNT__001c0884;
	local_14 = DAT_FRNT__001c0888;
	if (bSetup == 0) {
		if ((uRam001cc5dc & 0x10) == 0) {
			if ((uRam001cc5dc & 0x40) != 0) {
				if (DAT_FRNT__001c6a8c == 0) {
					if (DAT_FRNT__001c69a0 == 0) {
						DAT_FRNT__001c69a0 = *(int *)(&DAT_FRNT__001c69b8 + (DAT_FRNT__001c6a70 + 1) * 4) - 1U;
						if ((int)(uint)(byte)(&DAT_FRNT__001c69e0)[gFurthestMission] <
							(int)((*(int *)(&DAT_FRNT__001c69b8 + (DAT_FRNT__001c6a70 + 1) * 4) - 1U) +
								*(int *)(&DAT_FRNT__001c69cc + DAT_FRNT__001c6a70 * 4) + 1)) {
							DAT_FRNT__001c69a0 = (uint)(byte)(&DAT_FRNT__001c69e0)[gFurthestMission];
						}
						puVar7 = &DAT_0015f400 + DAT_FRNT__001c69a0 * 0x8000;
					}
					else {
						DAT_FRNT__001c69a0 = DAT_FRNT__001c69a0 - 1;
						puVar7 = &DAT_0015f400 + DAT_FRNT__001c69a0 * 0x8000;
					}
				}
				else {
					if (DAT_FRNT__001c6a8c != 2) {
						bReturnToMain = 0;
						ppPVar6 = pButtonStack10 + ScreenDepth;
						pScreenStack10[ScreenDepth] = pCurrScreen;
						pPVar3 = pCurrButton;
						feVariableSave[1] = DAT_FRNT__001c6a70;
						feVariableSave[0] = DAT_FRNT__001c69a0;
						*ppPVar6 = pCurrButton;
						ScreenNames12[iVar4] = pPVar3->Name;
						StartRender(feVariableSave[0] +
							*(int *)(&DAT_FRNT__001c69cc + feVariableSave[1] * 4) + 1);
						return 0;
					}
					if ((DAT_FRNT__001c69a0 ==
						*(int *)(&DAT_FRNT__001c69b8 + (DAT_FRNT__001c6a70 + 1) * 4) + -1) ||
						((int)(uint)(byte)(&DAT_FRNT__001c69e0)[gFurthestMission] <=
						(int)(DAT_FRNT__001c69a0 + *(int *)(&DAT_FRNT__001c69cc + DAT_FRNT__001c6a70 * 4) + 1)
							)) {
						puVar7 = &DAT_0015f400;
						DAT_FRNT__001c69a0 = 0;
					}
					else {
						DAT_FRNT__001c69a0 = DAT_FRNT__001c69a0 + 1;
						puVar7 = &DAT_0015f400 + DAT_FRNT__001c69a0 * 0x8000;
					}
				}
				local_c = DAT_FRNT__001c0888;
				local_10 = DAT_FRNT__001c0884;
				LoadImage(&local_10, puVar7);
				DrawSync(0);
				DisplayOnScreenText();
				pDVar2 = current;
				DAT_FRNT__001cc5c8 = DAT_FRNT__001cc5c8 & 0xff000000 | *(uint *)current->ot[2] & 0xffffff;
				*(uint *)current->ot[2] = *(uint *)current->ot[2] & 0xff000000 | 0x1cc5c8;
				DAT_FRNT__001cbdb8 = DAT_FRNT__001cbdb8 & 0xff000000 | *(uint *)pDVar2->ot[3] & 0xffffff;
				puVar5 = (uint *)pDVar2->ot[3];
				*puVar5 = *puVar5 & 0xff000000 | 0x1cbdb8;
				EndFrame();
				return 0;
			}
			if ((uRam001cc5dc & 0x1000) == 0) {
				if ((uRam001cc5dc & 0x4000) == 0) {
					return 0;
				}
				bVar1 = pCurrButton->d;
			}
			else {
				bVar1 = pCurrButton->u;
			}
			DAT_FRNT__001c6a8c = (uint)bVar1 - 1;
		}
		else {
			DAT_FRNT__001c6a90 = 0;
			DAT_FRNT__001c6a80 = 0;
		}
		iVar4 = 0;
	}
	else {
		LoadBackgroundFile(s_DATA_CUTS_CUTBACK_RAW_FRNT__001c08c8);
		DAT_FRNT__001c6a70 = feVariableSave[1];
		if (feVariableSave[0] == -1) {
			DAT_FRNT__001c69a0 = 0;
			DAT_FRNT__001c6a70 = GameLevel;
		}
		else {
			DAT_FRNT__001c69a0 = feVariableSave[0];
			feVariableSave[3] = 0xffffffff;
			feVariableSave[2] = 0xffffffff;
			feVariableSave[1] = -1;
			feVariableSave[0] = -1;
		}
		if ((int)DAT_FRNT__001c6a7a == GameLevel) {
			DAT_FRNT__001c6a90 = 1;
			LoadImage(&local_18, &DAT_0015f400);
			DrawSync(0);
		}
		else {
			SetupExtraPoly((&PTR_s_DATA_CUTS_CCUTS_RAW_FRNT__001c073c_FRNT__001c69a8)[GameLevel],
				DAT_FRNT__001c69a0, 0x20000);
		}
		iVar4 = 1;
		DAT_FRNT__001c6a80 = 1;
		DAT_FRNT__001c6a8c = 1;
		DAT_FRNT__001c69a4 = 1;
		pCurrButton = pCurrScreen->buttons + 1;
	}
	return iVar4;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CutSceneCitySelectScreen(int bSetup /*$a0*/)
 // line 3855, offset 0x001c4b30
	/* begin block 1 */
		// Start line: 3857
		// Start offset: 0x001C4B30
		// Variables:
	// 		struct RECT rect; // stack offset -24

		/* begin block 1.1 */
			// Start line: 3856
			// Start offset: 0x001C4E6C

			/* begin block 1.1.1 */
				// Start line: 3856
				// Start offset: 0x001C4E6C
				// Variables:
			// 		struct RECT rect; // stack offset -16
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
			// 		struct RECT rect; // stack offset -16
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
			// 		struct RECT rect; // stack offset -16
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
			// 		struct RECT rect; // stack offset -16
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

int CutSceneCitySelectScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	DB *pDVar1;
	PSXSCREEN *pPVar2;
	PSXBUTTON *pPVar3;
	PSXBUTTON **ppPVar4;
	uint *puVar5;
	int offset;
	undefined *puVar6;
	undefined4 local_18;
	undefined4 local_14;
	undefined4 local_10;
	undefined4 local_c;

	offset = ScreenDepth;
	local_18 = DAT_FRNT__001c0884;
	local_14 = DAT_FRNT__001c0888;
	if (bSetup != 0) {
		LoadBackgroundFile(s_DATA_CITYBACK_RAW_FRNT__001c08b4);
		if (feVariableSave[0] == -1) {
			if (DAT_FRNT__001c69a4 == 0) {
				DAT_FRNT__001c6a70 = 0;
				DAT_FRNT__001c69a4 = 1;
			}
		}
		else {
			DAT_FRNT__001c6a70 = feVariableSave[0];
			feVariableSave[3] = 0xffffffff;
			feVariableSave[2] = 0xffffffff;
			feVariableSave[1] = 0xffffffff;
			feVariableSave[0] = -1;
		}
		pCurrScreen->buttons[3].d = '\x01';
		pCurrScreen->buttons[0].u = '\x04';
		pPVar2 = pCurrScreen;
		offset = gFurthestMission;
		if (gFurthestMission == 0) {
			pCurrScreen->buttons[0].action = 0x300;
			pPVar2->buttons[1].action = 0x300;
			pPVar2->buttons[2].action = 0x300;
			pPVar2->buttons[3].action = 0x300;
		}
		else {
			if (gFurthestMission < 10) {
				pCurrScreen->buttons[0].action = 0x116;
				pPVar2->buttons[1].action = 0x300;
				pPVar2->buttons[2].action = 0x300;
				pPVar2->buttons[3].action = 0x300;
			}
			else {
				if (gFurthestMission < 0x15) {
					pCurrScreen->buttons[0].action = 0x116;
					pPVar2->buttons[1].action = 0x116;
					pPVar2->buttons[2].action = 0x300;
					pPVar2->buttons[3].action = 0x300;
				}
				else {
					if (gFurthestMission < 0x1f) {
						pCurrScreen->buttons[0].action = 0x116;
						pPVar2->buttons[1].action = 0x116;
						pPVar2->buttons[2].action = 0x116;
						pPVar2->buttons[3].action = 0x300;
					}
					else {
						pCurrScreen->buttons[0].action = 0x116;
						pPVar2->buttons[1].action = 0x116;
						pPVar2->buttons[2].action = 0x116;
						pPVar2->buttons[3].action = 0x116;
						if (offset == 0x28) {
							pPVar2->buttons[3].d = '\x05';
							pCurrScreen->buttons[0].u = '\x05';
						}
					}
				}
			}
		}
		if (DAT_FRNT__001c6a78 == -1) {
			offset = DAT_FRNT__001c6a70;
			if (DAT_FRNT__001c6a70 == 4) {
				offset = 0;
			}
			SetupExtraPoly(s_DATA_CITY_RAW_FRNT__001c088c, offset, 0);
			return 0;
		}
		DAT_FRNT__001c6a90 = 1;
		if (DAT_FRNT__001c6a70 == 4) {
			LoadImage(&local_18, &DAT_0013f400);
		}
		else {
			LoadImage(&local_18, &DAT_0013f400 + DAT_FRNT__001c6a70 * 0x8000);
		}
		DrawSync(0);
		return 0;
	}
	if ((uRam001cc5dc & 0x40) != 0) {
		DAT_FRNT__001c6a7b = 0xff;
		DAT_FRNT__001c6a7c = (undefined)GameLevel;
		if (GameLevel != 4) {
			DAT_FRNT__001c6a7b = 0xff;
			return 0;
		}
		bReturnToMain = 0;
		ppPVar4 = pButtonStack10 + ScreenDepth;
		pScreenStack10[ScreenDepth] = pCurrScreen;
		pPVar3 = pCurrButton;
		*ppPVar4 = pCurrButton;
		ScreenNames12[offset] = pPVar3->Name;
		feVariableSave[0] = DAT_FRNT__001c6a70;
		StartRender(0x60);
		return 0;
	}
	if ((uRam001cc5dc & 0x10) != 0) {
		FESound(0);
		DAT_FRNT__001c6aac = 1;
		LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
		DAT_FRNT__001c69a4 = 0;
		DAT_FRNT__001c6a90 = 0;
		return 0;
	}
	if ((uRam001cc5dc & 0x1000) == 0) {
		if ((uRam001cc5dc & 0x4000) == 0) {
			return 0;
		}
		GameLevel = (uint)pCurrButton->d - 1;
		DAT_FRNT__001c6a70 = GameLevel;
		if (GameLevel != 4) {
			local_10 = DAT_FRNT__001c0884;
			local_c = DAT_FRNT__001c0888;
			LoadImage(&local_10, &DAT_0013f400 + GameLevel * 0x8000);
			DrawSync(0);
			DisplayOnScreenText();
			pDVar1 = current;
			DAT_FRNT__001cc5c8 = DAT_FRNT__001cc5c8 & 0xff000000 | *(uint *)current->ot[2] & 0xffffff;
			*(uint *)current->ot[2] = *(uint *)current->ot[2] & 0xff000000 | 0x1cc5c8;
			DAT_FRNT__001cbdb8 = DAT_FRNT__001cbdb8 & 0xff000000 | *(uint *)pDVar1->ot[3] & 0xffffff;
			puVar5 = (uint *)pDVar1->ot[3];
			*puVar5 = *puVar5 & 0xff000000 | 0x1cbdb8;
			EndFrame();
			return 0;
		}
	}
	else {
		DAT_FRNT__001c6a70 = (uint)pCurrButton->u - 1;
		if (DAT_FRNT__001c6a70 != 4) {
			puVar6 = &DAT_0013f400 + DAT_FRNT__001c6a70 * 0x8000;
			goto LAB_FRNT__001c4ec0;
		}
	}
	puVar6 = &DAT_0013f400;
LAB_FRNT__001c4ec0:
	local_10 = DAT_FRNT__001c0884;
	local_c = DAT_FRNT__001c0888;
	GameLevel = DAT_FRNT__001c6a70;
	LoadImage(&local_10, puVar6);
	DrawSync(0);
	DisplayOnScreenText();
	pDVar1 = current;
	DAT_FRNT__001cc5c8 = DAT_FRNT__001cc5c8 & 0xff000000 | *(uint *)current->ot[2] & 0xffffff;
	*(uint *)current->ot[2] = *(uint *)current->ot[2] & 0xff000000 | 0x1cc5c8;
	DAT_FRNT__001cbdb8 = DAT_FRNT__001cbdb8 & 0xff000000 | *(uint *)pDVar1->ot[3] & 0xffffff;
	puVar5 = (uint *)pDVar1->ot[3];
	*puVar5 = *puVar5 & 0xff000000 | 0x1cbdb8;
	EndFrame();
	return 0;*/
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
	// 		struct RECT rect; // stack offset -32

		/* begin block 1.1 */
			// Start line: 4048
			// Start offset: 0x001C5254

			/* begin block 1.1.1 */
				// Start line: 4048
				// Start offset: 0x001C5254
				// Variables:
			// 		struct DB *db_hold; // $a1
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
			// 		struct DB *db_hold; // $a1
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
			// 		struct DB *db_hold; // $a1
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
			// 		struct DB *db_hold; // $a1
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

int SetVolumeScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*

	char **ppcVar1;
	byte bVar2;
	int iVar3;
	int iVar4;
	DB *pDVar5;
	DB *pDVar6;
	char acStack48[8];
	int local_28;
	int local_24;
	undefined4 local_20;
	undefined4 local_1c;

	iVar4 = gMasterVolume;
	iVar3 = gMusicVolume;
	local_28 = DAT_FRNT__001c08e0;
	local_24 = DAT_FRNT__001c08e4;
	local_20 = DAT_FRNT__001c0884;
	local_1c = DAT_FRNT__001c0888;
	if (bSetup != 0) {
		DAT_FRNT__001c6a8c = 0;
		DAT_FRNT__001cc260 = gMasterVolume;
		DAT_FRNT__001cc588 = gMusicVolume;
		LoadBackgroundFile(s_DATA_VOL_RAW_FRNT__001c08e8);
		sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + gMasterVolume) / 100);
		FEPrintString(acStack48, 0x98, local_28, 2, 0x80, 0x80, 0x80);
		sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + gMusicVolume) / 100);
		FEPrintString(acStack48, 0x98, local_24, 2, 0x80, 0x80, 0x80);
		return 0;
	}
	bVar2 = pCurrButton->u;
	DAT_FRNT__001c6a8c = (uint)bVar2 & 3;
	if (((int)(short)uRam001cc5dc & 0x8000U) == 0) {
		if ((uRam001cc5dc & 0x2000) == 0) {
			if ((uRam001cc5dc & 0x10) != 0) {
				FESound(0);
				DAT_FRNT__001c6aac = 1;
				gMasterVolume = DAT_FRNT__001cc260;
				gMusicVolume = DAT_FRNT__001cc588;
				LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
				SetMasterVolume(gMasterVolume);
				SetXMVolume(gMusicVolume);
				return 0;
			}
			if ((uRam001cc5dc & 0x40) == 0) {
				return 0;
			}
			if (DAT_FRNT__001c6a8c != 2) {
				return 0;
			}
			LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
			return 0;
		}
		if ((bVar2 & 3) != 0) {
			if (DAT_FRNT__001c6a8c != 1) goto LAB_FRNT__001c5530;
			gMusicVolume = gMusicVolume + 100;
			if (gMusicVolume < 1) goto LAB_FRNT__001c5418;
			gMusicVolume = 0;
		LAB_FRNT__001c5408:
			FESound(1);
			goto LAB_FRNT__001c5424;
		}
		gMasterVolume = gMasterVolume + 100;
		if (gMasterVolume < 1) goto LAB_FRNT__001c52c4;
		gMasterVolume = 0;
	LAB_FRNT__001c52b4:
		FESound(1);
	}
	else {
		if ((bVar2 & 3) != 0) {
			if (DAT_FRNT__001c6a8c != 1) goto LAB_FRNT__001c5530;
			gMusicVolume = gMusicVolume + -100;
			if (gMusicVolume < -10000) {
				gMusicVolume = -10000;
				goto LAB_FRNT__001c5408;
			}
		LAB_FRNT__001c5418:
			FESound(3);
		LAB_FRNT__001c5424:
			sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + gMusicVolume) / 100);
			FEPrintString(acStack48, 0x98, local_24, 2, 0x80, 0x80, 0x80);
			sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + iVar3) / 100);
			FEPrintString(acStack48, 0x98, local_24, 2, 0, 0, 0);
			DrawSync(0);
			VSync(0);
			PutDispEnv(&current->disp);
			PutDrawEnv(&current->draw);
			pDVar6 = last;
			pDVar5 = current;
			ppcVar1 = &last->primtab;
			current = last;
			last = pDVar5;
			pDVar6->primptr = *ppcVar1;
			DrawOTag(pDVar5->ot + 0x10);
			ClearOTagR(current->ot, 0x10);
			VSync(0);
			goto LAB_FRNT__001c5530;
		}
		gMasterVolume = gMasterVolume + -100;
		if (gMasterVolume < -10000) {
			gMasterVolume = -10000;
			goto LAB_FRNT__001c52b4;
		}
	LAB_FRNT__001c52c4:
		FESound(3);
	}
	sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + gMasterVolume) / 100);
	FEPrintString(acStack48, 0x98, local_28, 2, 0x80, 0x80, 0x80);
	sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + iVar4) / 100);
	FEPrintString(acStack48, 0x98, local_28, 2, 0, 0, 0);
	DrawSync(0);
	VSync(0);
	PutDispEnv(&current->disp);
	PutDrawEnv(&current->draw);
	pDVar6 = last;
	pDVar5 = current;
	ppcVar1 = &last->primtab;
	current = last;
	last = pDVar5;
	pDVar6->primptr = *ppcVar1;
	DrawOTag(pDVar5->ot + 0x10);
	ClearOTagR(current->ot, 0x10);
	VSync(0);
LAB_FRNT__001c5530:
	SetMasterVolume(gMasterVolume);
	SetXMVolume(gMusicVolume);
	return 0;*/
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
	// 		struct SCORE_ENTRY *pSE; // stack offset -48
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
CVECTOR scoreCol;
CVECTOR otherCol;

char* CityNames[4] = {
	"Chicago",
	"Havana",
	"Las Vegas",
	"Rio De Janeiro"
};

// [D]
void DisplayScoreTable(void)
{
	int iVar1;
	int iVar2;
	int y;
	int iVar3;
	char text[32];
	SCORE_ENTRY *pSE;

	gSubGameNumber = GameNum;

	OnScoreTable(&pSE);

	sprintf(text, ScreenNames[ScreenDepth + -1]);
	FEPrintString(text, 0x14, 200, 2, (uint)otherCol.r, (uint)otherCol.g, (uint)otherCol.b);
	sprintf(text, CityNames[GameLevel]);
	FEPrintString(text, 0x118, 200, 2, (uint)otherCol.r, (uint)otherCol.g, (uint)otherCol.b);

	iVar2 = ((uint)GameType - 4) * 8;

	if ((GameType == GAME_TAKEADRIVE) && (NumPlayers == 2)) {
		iVar2 = 0x30;
	}

	if (GameType == GAME_COPSANDROBBERS) {
		iVar2 = 0x20;
	}

	if (GameType == GAME_CAPTURETHEFLAG) {
		iVar2 = 0x28;
	}

	if ((GameType != GAME_PURSUIT) && (GameType != GAME_SURVIVAL)) {
		sprintf(text, "%s", gameNames[iVar2 + GameLevel * 2 + GameNum]);
		FEPrintStringSized(text, 0x1a4, 0xce, 0xc00, 2, (uint)otherCol.r, (uint)otherCol.g,
			(uint)otherCol.b);
	}

	y = 0xf0;
	iVar2 = 0;
	iVar3 = 4;

	do {
		sprintf(text, pSE->name + iVar2);
		FEPrintString(text, 0x14, y, 2, (uint)scoreCol.r, (uint)scoreCol.g, (uint)scoreCol.b);

		if ((GameType == GAME_GATERACE) || (GameType == GAME_TRAILBLAZER)) 
		{
			if (pSE->items + iVar2 != -1) {
				sprintf(text, "%d");
				FEPrintString(text, 0x8c, y, 2, (uint)scoreCol.r, (uint)scoreCol.g, (uint)scoreCol.b)
					;
			}
		}

		iVar1 = pSE->time + iVar2;

		if (iVar1 != -1) {
			sprintf(text, "%d:%02d.%02d", iVar1 / 180000,
				iVar1 / 3000 + (iVar1 / 180000) * -0x3c, (iVar1 % 3000) / 0x1e);
			FEPrintString(text, 0x118, y, 2, (uint)scoreCol.r, (uint)scoreCol.g, (uint)scoreCol.b);
		}

		y = y + 0x24;
		iVar3 = iVar3 + -1;
		iVar2 = iVar2 + 0xc;

	} while (-1 < iVar3);
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

// [D]
int ScoreScreen(int bSetup)
{
	if (bSetup != 0) {
		GameLevel = 0;
		DisplayScoreTable();
		bDoingScores = 1;
		currSelIndex = 0;
		return 0;
	}
	if ((fePad & 0x40U) == 0) {
		if ((fePad & 0x10U) != 0) {
			bDoingScores = 0;
			return 0;
		}
		if (((fePad & 0x1000U) == 0) && ((fePad & 0x4000U) == 0)) {
			return 0;
		}
		currSelIndex = currSelIndex ^ 1;
		return 0;
	}
	if (currSelIndex == 0) {
		if ((GameType != GAME_SURVIVAL) && (GameType != GAME_PURSUIT)) {
			if (GameNum == 1) {
				GameNum = 0;
			}
			else {
				GameNum = 1;
				GameLevel = GameLevel + -1;
				if (GameLevel < 0) {
					GameLevel = 3;
				}
			}
		LAB_FRNT__001c5ab0:
			DisplayScoreTable();
			bRedrawFrontend = 1;
			return 0;
		}
		GameLevel = GameLevel + -1;
		if (GameLevel < 0) {
			GameLevel = 3;
		}
	}
	else {
		if (((GameType != GAME_SURVIVAL) && (GameType != GAME_PURSUIT)) && (GameNum == 0)) {
			GameNum = 1;
			goto LAB_FRNT__001c5ab0;
		}
		GameLevel = GameLevel + 1;
		if (3 < GameLevel) {
			GameLevel = 0;
		}
	}
	GameNum = 0;
	DisplayScoreTable();
	bRedrawFrontend = 1;
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

// [D]
int SubtitlesOnOffScreen(int bSetup)
{
	if (bSetup != 0) {
		if (gSubtitles == 0) {
			pCurrButton = pCurrScreen->buttons + 1;
		}
		else {
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

// [D]
int CityCutOffScreen(int bSetup)
{
	PSXSCREEN *pPVar1;

	pPVar1 = pCurrScreen;
	if (bSetup != 0) {
		if (gFurthestMission < 0x14) {
			pCurrScreen->buttons[2].action = 0x300;
		}
		else {
			if (0x1d < gFurthestMission) {
				return 0;
			}
		}
		pPVar1->buttons[3].action = 0x300;
	}
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

// [D]
int ControllerScreen(int bSetup)
{
	if (bSetup == 0) 
	{
		if ((fePad & 0x40U) == 0) 
		{
			if ((fePad & 0x10U) != 0)
			{
				bDoingScores = 0;
				LoadBackgroundFile("DATA\\GFX.RAW");
			}
		}
		else 
		{
			currSelIndex = currSelIndex ^ 1;
			LoadBackgroundFile(contNames[currSelIndex]);

			bRedrawFrontend = 1;
		}
	}
	else {
		bDoingScores = 1;
		currSelIndex = 0;
		pCurrScreen->numButtons = '\0';

		LoadBackgroundFile(contNames[currSelIndex]);
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

// [D]
int MainScreen(int bSetup)
{
	if (bSetup != 0) {
		if (numPadsConnected == 2) {
			pCurrScreen->buttons[3].action = 0x106;
		}
		else {
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

static char* cheatText[5] =
{
	"Sorry, no secrets",
	"Mountain track",
	"Circuit",
	"Invincibility",
	"Immunity"
};

int CheatScreen(int bSetup)
{
	PSXSCREEN *pPVar1;
	PSXSCREEN *pPVar2;
	int iVar3;
	int iVar4;
	int *piVar5;
	int iVar6;
	unsigned char bVar7;
	int iVar8;
	int iVar9;
	unsigned char cheatOn[12];
	int evilRuss[4];

	int hackLookup1[4] = {
		0x121, 0x121, 0x11E, 0x11F
	};

	int hackLookup2[4] = {
		0xC01, 0xC00, -1, -1
	};

	if (bSetup == 0) {
		return 0;
	}
	if (gFurthestMission == 0x28) 
	{
		bVar7 = 4;
	}
	else 
	{
		bVar7 = AvailableCheats.cheat1 + AvailableCheats.cheat2 + AvailableCheats.cheat3 + AvailableCheats.cheat4;
	}

	if (bVar7 == 0)
	{
		pCurrScreen->buttons[0].u = 1;
		pCurrScreen->buttons[0].d = 1;
		pCurrScreen->numButtons = 1;
		pPVar1 = pCurrScreen;
		pCurrScreen->buttons[0].action = 0x400;

		sprintf(pPVar1->buttons[0].Name, cheatText[0]);

		return 0;
	}

	piVar5 = evilRuss;
	iVar4 = 0;
	pCurrScreen->numButtons = bVar7;

	evilRuss[0] = AvailableCheats.cheat1;
	evilRuss[1] = AvailableCheats.cheat2;
	evilRuss[2] = AvailableCheats.cheat3;
	evilRuss[3] = AvailableCheats.cheat4;

	iVar3 = 4;
	iVar8 = 0;

	do {
		if ((*piVar5 == 1) || (iVar6 = iVar3, iVar9 = iVar8, gFurthestMission == 0x28)) {
			iVar6 = iVar3 + 0x3c;
			sprintf((char *)((int)&pCurrScreen->buttons[0].var + iVar3), cheatText[iVar4 + 1]);
			iVar9 = iVar8 + 1;
			cheatOn[iVar8] = (unsigned char)iVar4;
		}
		pPVar1 = pCurrScreen;
		iVar4 = iVar4 + 1;
		piVar5 = piVar5 + 1;
		iVar3 = iVar6;
		iVar8 = iVar9;
	} while (iVar4 < 4);

	if (bVar7 == 2) {
		pCurrScreen->buttons[0].action = hackLookup1[cheatOn[0]];
		pPVar1->buttons[1].action = hackLookup1[cheatOn[1]];
		pPVar1->buttons[0].var = hackLookup2[cheatOn[0]];
		iVar3 = hackLookup2[cheatOn[1]];
		pPVar1->buttons[0].d = '\x02';
		pPVar2 = pCurrScreen;
		pPVar1->buttons[1].var = iVar3;
		pPVar2->buttons[0].u = '\x02';
		pCurrScreen->buttons[1].d = '\x01';
		pCurrScreen->buttons[1].u = '\x01';
		currSelIndex = 0;
		return 0;
	}

	if (bVar7 == 1) {
		pCurrScreen->buttons[0].action = hackLookup1[cheatOn[0]];
		iVar3 = hackLookup2[cheatOn[0]];
		pPVar1->buttons[0].d = '\x01';
		pPVar2 = pCurrScreen;
		pPVar1->buttons[0].var = iVar3;
		pPVar2->buttons[0].u = '\x01';
		currSelIndex = 0;
		return 0;
	}

	if (bVar7 == 3) {
		pCurrScreen->buttons[0].action = hackLookup1[cheatOn[0]];
		pPVar1->buttons[1].action = hackLookup1[cheatOn[1]];
		pPVar1->buttons[2].action = hackLookup1[cheatOn[2]];
		pPVar1->buttons[0].var = hackLookup2[cheatOn[0]];
		pPVar1->buttons[1].var = hackLookup2[cheatOn[1]];
		iVar3 = hackLookup2[cheatOn[2]];
		pPVar1->buttons[0].d = '\x02';
		pPVar2 = pCurrScreen;
		pPVar1->buttons[2].var = iVar3;
		pPVar2->buttons[0].u = '\x03';
		pCurrScreen->buttons[1].d = '\x03';
		pCurrScreen->buttons[1].u = '\x01';
		pCurrScreen->buttons[2].d = '\x01';
		pCurrScreen->buttons[2].u = '\x02';
		currSelIndex = 0;
		return 0;
	}

	if (bVar7 == 4) {
		pCurrScreen->buttons[0].action = hackLookup1[cheatOn[0]];
		pPVar1->buttons[1].action = hackLookup1[cheatOn[1]];
		pPVar1->buttons[2].action = hackLookup1[cheatOn[2]];
		pPVar1->buttons[3].action = hackLookup1[cheatOn[3]];
		pPVar1->buttons[0].var = hackLookup2[cheatOn[0]];
		pPVar1->buttons[1].var = hackLookup2[cheatOn[1]];
		pPVar1->buttons[2].var = hackLookup2[cheatOn[2]];
		iVar3 = hackLookup2[cheatOn[3]];
		pPVar1->buttons[0].d = '\x02';
		pPVar2 = pCurrScreen;
		pPVar1->buttons[3].var = iVar3;
		pPVar2->buttons[0].u = '\x04';
		pCurrScreen->buttons[1].d = '\x03';
		pCurrScreen->buttons[1].u = '\x01';
		pCurrScreen->buttons[2].d = '\x04';
		pCurrScreen->buttons[2].u = '\x02';
		pCurrScreen->buttons[3].d = '\x01';
		pCurrScreen->buttons[3].u = '\x03';
		currSelIndex = 0;
		return 0;
	}

	pCurrScreen->numButtons = '\0';
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

// [D]
int ImmunityOnOffScreen(int bSetup)
{
	if (bSetup != 0) {
		if (gPlayerImmune == 0) {
			pCurrButton = pCurrScreen->buttons + 1;
		}
		else {
			pCurrButton = pCurrScreen->buttons;
		}
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

// [D]
int InvincibleOnOffScreen(int bSetup)
{
	if (bSetup != 0) {
		if (gInvincibleCar == 0) {
			pCurrButton = pCurrScreen->buttons + 1;
		}
		else {
			pCurrButton = pCurrScreen->buttons;
		}
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

// [D]
int GamePlayScreen(int bSetup)
{
	int iVar1;

	if (bSetup != 0) {
		if (allowVibration == 0) {
			iVar1 = 0x300;
		}
		else {
			iVar1 = 0x111;
		}
		pCurrScreen->buttons[2].action = iVar1;
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

// [D]
int GameNameScreen(int bSetup)
{
	int iVar1;

	if (bSetup != 0) {
		iVar1 = ((uint)GameType - 4) * 8;
		if ((GameType == GAME_TAKEADRIVE) && (NumPlayers == 2)) {
			iVar1 = 0x30;
		}
		if (GameType == GAME_COPSANDROBBERS) {
			iVar1 = 0x20;
		}
		if (GameType == GAME_CAPTURETHEFLAG) {
			iVar1 = 0x28;
		}
		if ((GameType == GAME_CHECKPOINT) && (NumPlayers == 2)) {
			iVar1 = 0x38;
		}
		sprintf(pCurrScreen->buttons[0].Name, gameNames[iVar1 + GameLevel * 2]);
		sprintf(pCurrScreen->buttons[1].Name, gameNames[iVar1 + GameLevel * 2 + 1]);
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
	// 		struct RECT dest; // stack offset -24
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

// [D]
void FEInitCdIcon(void)
{
	ushort *puVar1;
	int iVar2;
	RECT16 rect;

	puVar1 = cd_icon + 10;
	iVar2 = 0xd;
	do {
		iVar2 = iVar2 + -1;
		*puVar1 = *puVar1 & 0x7fff;
		puVar1 = puVar1 + 1;
	} while (-1 < iVar2);
	cd_icon[10] = 0;
	rect.x = 0x3c0;
	rect.y = 0x1b2;
	rect.w = 8;
	rect.h = 0x20;
	cd_icon[24] = cd_icon[24] | 0x8000;
	cd_icon[25] = cd_icon[25] | 0x8000;
	LoadImage(&rect, (u_long *)(cd_icon + 0x18));
	setPolyFT4(&cd_sprite);
	cd_sprite.r0 = 128;
	cd_sprite.g0 = 128;
	cd_sprite.b0 = 128;
	cd_sprite.v0 = -0x4d;
	cd_sprite.v1 = -0x4d;
	cd_sprite.u0 = '\0';
	cd_sprite.u1 = ' ';
	cd_sprite.u2 = '\0';
	cd_sprite.v2 = -0x2d;
	cd_sprite.u3 = ' ';
	cd_sprite.v3 = -0x2d;
	cd_sprite.clut = GetClut(0x3c0, 0x1b1);
	cd_sprite.tpage = GetTPage(0, 0, 0x3c0, 0x100);
	bCdIconSetup = 1;
	cd_sprite.x0 = 0x50;
	cd_sprite.y0 = 0x26;
	cd_sprite.x1 = 0x76;
	cd_sprite.y1 = 0x26;
	cd_sprite.x2 = 0x50;
	cd_sprite.y2 = 0x3b;
	cd_sprite.x3 = 0x76;
	cd_sprite.y3 = 0x3b;
	return;
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
	// 		struct RECT dest; // stack offset -16
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

// [D]
void FEDrawCDicon(void)
{
	ushort *puVar1;
	int iVar2;
	RECT16 dest;

	cd_icon[23] = cd_icon[11];
	iVar2 = 0xb;
	puVar1 = cd_icon + 10;
	do {
		iVar2 = iVar2 + -1;
		puVar1[1] = puVar1[2];
		puVar1 = puVar1 + 1;
	} while (-1 < iVar2);
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

// [D]
int CheatNumlayerSelect(int bSetup)
{
	if (bSetup != 0) {
		if (numPadsConnected == 2) {
			pCurrScreen->buttons[1].action = 0x120;
		}
		else {
			pCurrScreen->buttons[1].action = 0x300;
		}
		return 0;
	}
	return 0;
}





