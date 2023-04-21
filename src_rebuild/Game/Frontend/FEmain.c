#include "driver2.h"

#include "FEmain.h"
#include "FEtypes.h"

#include "C/cd_icon.h"

#include "C/system.h"
#include "C/glaunch.h"
#include "C/mission.h"
#include "C/time.h"
#include "C/loadsave.h"
#include "C/pad.h"
#include "C/loadview.h"
#include "C/pres.h"
#include "C/sound.h"
#include "C/debris.h"
#include "C/E3stuff.h"
#include "C/fmvplay.h"
#include "C/gamesnd.h"
#include "C/scores.h"
#include "C/loadsave.h"
#include "C/spool.h"
#include "C/state.h"

#ifndef PSX

#include "PsyX/PsyX_render.h"
#include "../utils/targa.h"
#include "../utils/hqfont.h"

#define HIRES_FONTS

struct FEFONT_QUAD
{
	float x0, y0, s0, t0; // top-left
	float x1, y1, s1, t1; // bottom-right
};

TextureID gHiresFEFontTexture = 0;
OUT_FN2RANGE gHiresFEFontRanges[4];
OUT_FN2INFO gHiresFEFontCharData[4][224];
int gHiresFEFontRangeCount = 0;

void InitHiresFEFont()
{
	char namebuffer[64];
	u_char* data;

	// init font2
	if (!gHiresFEFontTexture)
	{
		gHiresFEFontRangeCount = 0;

		int width, height, bpp;
		int x, y;
		int size;
		FILE* fp;
		sprintf(namebuffer, "%s%s", gDataFolder, "GFX\\HQ\\fefont.fn2");
		FS_FixPathSlashes(namebuffer);

		fp = fopen(namebuffer, "rb");
		if (fp)
		{
			int i;

			// read fn2 step by step
			OUT_FN2HEADER fn2hdr;
			fread(&fn2hdr, sizeof(fn2hdr), 1, fp);

			gHiresFEFontRangeCount = fn2hdr.range_count;
			for (i = 0; i < fn2hdr.range_count; ++i)
			{
				fread(&gHiresFEFontRanges[i], sizeof(gHiresFEFontRanges[i]), 1, fp);
				fread(gHiresFEFontCharData[i], sizeof(OUT_FN2INFO), gHiresFEFontRanges[i].count, fp);
			}

			fclose(fp);
		}

		// load TGA file
		sprintf(namebuffer, "%s%s", gDataFolder, "GFX\\HQ\\fefont.tga");
		FS_FixPathSlashes(namebuffer);
		
		if (LoadTGAImage(namebuffer, &data, width, height, bpp))
		{
			if (bpp == 32)
			{
				gHiresFEFontTexture = GR_CreateRGBATexture(HIRES_FONT_SIZE_W, HIRES_FONT_SIZE_H, data);
			}
			free(data);
		}
	}
}

void FEGetHiresBakedQuad(int char_index, float scale, float* xpos, float* ypos, FEFONT_QUAD* q)
{
	float ipw = 1.0f / (float)HIRES_FONT_SIZE_W;
	float iph = 1.0f / (float)HIRES_FONT_SIZE_H;

	const OUT_FN2INFO* b = gHiresFEFontCharData[0] + char_index - gHiresFEFontRanges[0].start;

	float fscale = 0.5f * scale;

	float s_x = b->x1 - b->x0;
	float s_y = b->y1 - b->y0;

	q->x0 = *xpos + b->xoff * fscale;
	q->y0 = *ypos + b->yoff * fscale;
	q->x1 = (b->xoff2 - b->xoff) * fscale;
	q->y1 = (b->yoff2 - b->yoff) * fscale;

	q->s0 = b->x0 * 255.0f * ipw;
	q->t0 = b->y0 * 255.0f * iph;
	q->s1 = s_x * 255.0f * ipw;
	q->t1 = s_y * 255.0f * iph;

	q->y0 += 32.0f;

	*xpos += b->xadvance * fscale;
}

void SetHiresFEFontTexture(int enabled)
{
	if (gHiresFEFontTexture == 0)
	{
		return;
	}

	DR_PSYX_TEX* tex = (DR_PSYX_TEX*)current->primptr;
	if (enabled)
		SetPsyXTexture(tex, gHiresFEFontTexture, 255, 255);
	else
		SetPsyXTexture(tex, 0, 0, 0);

	addPrim(current->ot + 1, tex);
	current->primptr += sizeof(DR_PSYX_TEX);
}

int FEStringWidthHires(char* string)
{
	char* pString = string;
	u_char c = 0;

	int w = 0;

	while ((c = *pString++) != 0)
	{
		float fx, fy;
		fx = 0;
		fy = 0;
		FEFONT_QUAD q;
		FEGetHiresBakedQuad(c, 1.0f, &fx, &fy, &q);

		w += fx;
	}

	return w;
}

int FEPrintStringSizedHires(char* string, int x, int y, int scale, int transparent, int r, int g, int b)
{
	if (current == NULL || string == NULL)
		return -1;

	POLY_FT4* shadow;
	POLY_FT4* font;
	u_char let;
	int w;
	int h;

	SetHiresFEFontTexture(0);
	font = (POLY_FT4*)current->primptr;

	while ((let = *string++) != 0)
	{
		if (let == '\n')
			continue;

		float fx, fy;
		fx = x;
		fy = y;
		FEFONT_QUAD q;
		FEGetHiresBakedQuad(let, scale / 4096.0f, &fx, &fy, &q);

		setPolyFT4(font);
		setSemiTrans(font, 1);

		setRGB0(font, r, g, b);
		setUVWH(font, q.s0, q.t0, q.s1, q.t1);
		setXYWH(font, q.x0, q.y0, q.x1, q.y1);

		font->clut = 0;
		font->tpage = 0;

		addPrim(current->ot + 1, font);
		shadow = font + 1;

		// add shadow poly
		memcpy(shadow, font, sizeof(POLY_FT4));
		setRGB0(shadow, 10, 10, 10);
		setXYWH(shadow, q.x0 + 1.0f, q.y0 + 1.0f, q.x1, q.y1);

		addPrim(current->ot + 1, shadow);
		font += 2;

		// make room for next character
		x += fx - x;
	}

	// set tail
	current->primptr = (char*)font;
	SetHiresFEFontTexture(1);

	return x;
}

int FEPrintStringHires(char* string, float x, float y, int justification, int r, int g, int b)
{
	POLY_FT4* shadow;
	POLY_FT4* font;
	u_char let;

	if (justification & 4)
	{
		x -= FEStringWidthHires(string);
	}

	SetHiresFEFontTexture(0);
	font = (POLY_FT4*)current->primptr;

	int counter = 0;

	while ((let = *string++) != 0)
	{
		float fx, fy;
		fx = x;
		fy = y;
		FEFONT_QUAD q;
		FEGetHiresBakedQuad(let, 1.0f, &fx, &fy, &q);

		setPolyFT4(font);
		setSemiTrans(font, 1);

		setRGB0(font, r, g, b);
		setUVWH(font, q.s0, q.t0, q.s1, q.t1);
		setXYWH(font, q.x0, q.y0, q.x1, q.y1);

		font->clut = 0;
		font->tpage = 0;

		addPrim(current->ot + 1, font);
		shadow = font + 1;

		// add shadow poly
		memcpy(shadow, font, sizeof(POLY_FT4));
		setRGB0(shadow, 10, 10, 10);
		setXYWH(shadow, q.x0 + 1.0f, q.y0 + 1.0f, q.x1, q.y1);

		addPrim(current->ot + 1, shadow);
		font += 2;

		// add space for next character
		x += fx - x;

		if (++counter >= 32)
			break;
	}

	// set tail
	current->primptr = (char *)font;

	SetHiresFEFontTexture(1);

	return x;
}

#endif // PSX

#define FE_OTSIZE 16

enum FEScreenType
{
	// Defaults - do not edit
	Sc_Main				= 0,
	Sc_TakeARide		= 1,
	Sc_Undercover		= 2,
	Sc_TimeOfDay		= 3,
	Sc_Replays			= 4,
	Sc_DrivingGames		= 5,
	Sc_Multiplayer		= 6,
	Sc_SubGameType		= 7,
	Sc_SubGameTime		= 8,
	Sc_SubGameCity		= 9,
	Sc_NotAvailable		= 10, // unused replay menu?
	Sc_GameCity			= 11,
	Sc_CentreScreen		= 12,
	Sc_Options			= 13,
	Sc_CarSelect		= 14,
	Sc_GameplayOptions	= 15,
	Sc_CopDifficulty	= 16,
	Sc_VibrationOnOff	= 17,
	Sc_MPSubGameCity	= 18,
	Sc_MissionSelect	= 19,
	Sc_MissionCity		= 20,
	Sc_CutSceneCity		= 21,
	Sc_CutSceneSelect	= 22,
	Sc_SoundOptions		= 23,
	Sc_ScoreSelect		= 24,
	Sc_ScoreMode		= 25,
	Sc_HighScores		= 26,
	Sc_SubtitlesOnOff	= 27,
	Sc_Controller		= 28,
	Sc_Secrets			= 29,
	Sc_InvincibleOnOff	= 30,
	Sc_ImmunityOnOff	= 31,
	Sc_RaceSelect		= 32,
	Sc_RaceMode			= 33,
	Sc_MPCitySelect		= 34,
	Sc_MPChicagoMode	= 35,
	Sc_MPHavanaMode		= 36,
	Sc_MPVegasMode		= 37,
	Sc_MPRioMode		= 38,

	_Sc_DefaultsLast	= Sc_MPRioMode,

	// New entries
	Sc_ReplayTheater,
	Sc_MiniCarsOnOff,
	Sc_AdjustDensity,

#ifndef PSX
	Sc_DetailOptions,
	Sc_FullScreenOnOff, // NB: implement if/when Psy-X can reload the renderer
	Sc_VSyncOnOff,
	Sc_BilinearOnOff,
	Sc_PGXPSettings,
	Sc_DrawDistance,
	Sc_DynamicLightsOnOff,
#endif

	// Total number of screens
	_Sc_NumScreens, // default = 42

	// Helpers
	_Sc_NumDefaultScreens = _Sc_DefaultsLast + 1,
	_Sc_NumCustomScreens = _Sc_NumScreens - _Sc_NumDefaultScreens,
};

// #define USE_EMBEDDED_FRONTEND_SCREENS

#ifdef USE_EMBEDDED_FRONTEND_SCREENS
#include "FEscreens.inc"
#else
FE_SCREEN PsxScreens[_Sc_NumScreens];
#endif

struct SCREEN_LIMITS
{
	short minx, miny, maxx, maxy;
};

struct BOTCH
{
	int missNum;
	char** name;
};

char* NullStr = "\0";

extern ACTIVE_CHEATS AvailableCheats;
extern ACTIVE_CHEATS ActiveCheats;

int CentreScreen(int bSetup); // 0x001C31FC
int CarSelectScreen(int bSetup); // 0x001C3430
int CopDiffLevelScreen(int bSetup); // 0x001C6404
int VibroOnOffScreen(int bSetup); // 0x001C3A60
int MissionSelectScreen(int bSetup); // 0x001C3B1C
int MissionCityScreen(int bSetup); // 0x001C4338
int CutSceneSelectScreen(int bSetup); // 0x001C4600
int CutSceneCitySelectScreen(int bSetup); // 0x001C4B30
int SetVolumeScreen(int bSetup); // 0x001C50B0
int ScoreScreen(int bSetup); // 0x001C59A0
int SubtitlesOnOffScreen(int bSetup); // 0x001C64B0
int CityCutOffScreen(int bSetup); // 0x001C64FC
int ControllerScreen(int bSetup); // 0x001C6548
int MainScreen(int bSetup); // 0x001C6614
int CheatScreen(int bSetup); // 0x001C5B4C
int ImmunityOnOffScreen(int bSetup); // 0x001C6654
int InvincibleOnOffScreen(int bSetup); // 0x001C66A0
int GamePlayScreen(int bSetup); // 0x001C66EC
int GameNameScreen(int bSetup); // 0x001C60A0
int CheatNumlayerSelect(int bSetup); // 0x001C6724
int UserReplaySelectScreen(int bSetup);
int TimeOfDaySelectScreen(int bSetup);
int DemoScreen(int bSetup);
int MiniCarsOnOffScreen(int bSetup);
#ifndef PSX
int ChooseOptionScreen(int bSetup);

#endif

screenFunc fpUserFunctions[] = {

	// Defaults - do not edit
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

	// New entries
	UserReplaySelectScreen,
	TimeOfDaySelectScreen,
	DemoScreen,
	MiniCarsOnOffScreen,
	ChooseOptionScreen,
};

#define FE_CALLBACK(userFunctionNum) (fpUserFunctions[userFunctionNum - 1])

#define FE_INIT_SCREEN(screen) FE_CALLBACK(screen->userFunctionNum)(1)
#define FE_STEP_SCREEN(screen) FE_CALLBACK(screen->userFunctionNum)(0)

// NB: Any changes to 'fpUserFunctions' must be reflected here
enum FEUserFunction
{
	Fn_None = 0,

	// Defaults - do not edit
	Fn_CentreScreen				= 1,
	Fn_CarSelectScreen			= 2,
	Fn_CopDiffLevelScreen		= 3,
	Fn_VibroOnOffScreen			= 4,
	Fn_MissionSelectScreen		= 5,
	Fn_MissionCityScreen		= 6,
	Fn_CutSceneCitySelectScreen = 7,
	Fn_CutSceneSelectScreen		= 8,
	Fn_SetVolumeScreen			= 9,
	Fn_ScoreScreen				= 10,
	Fn_SubtitlesOnOffScreen		= 11,
	Fn_CityCutOffScreen			= 12,
	Fn_ControllerScreen			= 13,
	Fn_MainScreen				= 14,
	Fn_CheatScreen				= 15,
	Fn_ImmunityOnOffScreen		= 16,
	Fn_InvincibleOnOffScreen	= 17,
	Fn_GamePlayScreen			= 18,
	Fn_GameNameScreen			= 19,
	Fn_CheatNumlayerSelect		= 20,

	// New entries
	Fn_UserReplaySelectScreen,
	Fn_TimeOfDaySelectScreen,
	Fn_DemoScreen,
	Fn_MiniCarsOnOffScreen,
	Fn_ChooseOptionScreen,

	Fn_End = 128,
};

enum FEButtonAction
{
	BTN_NEXT_SCREEN = 1,
	BTN_START_GAME = 2,
	BTN_DISABLED = 3,
	BTN_PREVIOUS_SCREEN = 4,
	BTN_HIDDEN = 5
};

enum FEButtonVariable
{
	VAR_NONE			= FE_NULLVAR,

	// Defaults - do not edit
	VAR_GAME_LEVEL		= 1,
	VAR_GAME_TYPE		= 2,
	VAR_MULTIPLAYER		= 3,
	VAR_TIMEOFDAY		= 4,
	VAR_MISSION_NUMBER	= 5,
	VAR_LOAD_GAME		= 6,
	VAR_SAVE_GAME		= 7,
	VAR_SUB_GAME		= 8,
	VAR_SUBTITLES		= 9,
	VAR_INVINCIBILITY	= 10,
	VAR_IMMUNITY		= 11,
	VAR_MINIGAME		= 12,
	VAR_DEMO_CHASE		= 13,

	// New entries
	VAR_BONUS_GALLERY,
	VAR_MINI_CARS,
	VAR_CHOOSE_TYPE,
	VAR_CHOOSE_VALUE,
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
	M_LTXT_ID(MTXT_RedRiver),
	M_LTXT_ID(MTXT_Themorgue),
	M_LTXT_ID(MTXT_TheWitness),
	M_LTXT_ID(MTXT_Lennysapartment),
	M_LTXT_ID(MTXT_TheCubaConnection),
	M_LTXT_ID(MTXT_TheIntruder),
	M_LTXT_ID(MTXT_MeetingCaine),
	M_LTXT_ID(MTXT_LeavingTown),

	M_LTXT_ID(MTXT_Lookingforalead),
	M_LTXT_ID(MTXT_Movingout),
	M_LTXT_ID(MTXT_Watchingthetruck),
	M_LTXT_ID(MTXT_RosannaSotoClue),
	M_LTXT_ID(MTXT_TheDockyard),
	M_LTXT_ID(MTXT_TheHit),
	M_LTXT_ID(MTXT_SeizingJericho),

	M_LTXT_ID(MTXT_VasquezinVegas),
	M_LTXT_ID(MTXT_TradingJericho),
	M_LTXT_ID(MTXT_CBankjob),
	M_LTXT_ID(MTXT_ThePoolHall),
	M_LTXT_ID(MTXT_CainesWarpath),

	M_LTXT_ID(MTXT_CaineinRio),
	M_LTXT_ID(MTXT_WarningJones),
	M_LTXT_ID(MTXT_TheShootout),
	M_LTXT_ID(MTXT_Lennysgetaway),
	M_LTXT_ID(MTXT_Lennygetsit),
	M_LTXT_ID(MTXT_BackinChicago),
	M_LTXT_ID(MTXT_VasquezmeetsCaine),
	M_LTXT_ID(MTXT_Credits),
};

char *areaNames[4][8] = {
	{
		M_LTXT_ID(MTXT_Downtown),
		M_LTXT_ID(MTXT_Wrigleyville),
		M_LTXT_ID(MTXT_Greektown),
		M_LTXT_ID(MTXT_GrantPark),
		M_LTXT_ID(MTXT_MeigsField),
		M_LTXT_ID(MTXT_UkrainianVillage),
		M_LTXT_ID(MTXT_RiverNorth),
		M_LTXT_ID(MTXT_CabriniGreen),
	},
	{
		M_LTXT_ID(MTXT_NecropolisdeColon),
		M_LTXT_ID(MTXT_Capitolio),
		M_LTXT_ID(MTXT_OldHavana),
		M_LTXT_ID(MTXT_TheDocks),
		M_LTXT_ID(MTXT_Vedado),
		M_LTXT_ID(MTXT_Plaza),
		M_LTXT_ID(MTXT_PlazadelaRevolucion),
		NULL,
	},
	{
		M_LTXT_ID(MTXT_Downtown),
		M_LTXT_ID(MTXT_UpperStrip),
		M_LTXT_ID(MTXT_Lakeside),
		M_LTXT_ID(MTXT_MidStrip),
		M_LTXT_ID(MTXT_NorthVegas),
		M_LTXT_ID(MTXT_Lakes),
		M_LTXT_ID(MTXT_GhostTown),
		NULL,
	},
	{
		M_LTXT_ID(MTXT_Centro),
		M_LTXT_ID(MTXT_Copacabana),
		M_LTXT_ID(MTXT_SantaTereza),
		M_LTXT_ID(MTXT_LagoaRodrigodeFreitas),
		M_LTXT_ID(MTXT_PracadaBandeira),
		M_LTXT_ID(MTXT_Leblon),
		M_LTXT_ID(MTXT_Flamengo),
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

#define AREA_NAME(level, index) GET_MISSION_TXT(areaNames[level][index])

#define GAMEMODE_AREA(level, offset, index) gameAreas[offset + level * 2 + index]
#define GAMEMODE_AREA_NAME(level, offset, index) AREA_NAME(level, GAMEMODE_AREA(level, offset, index))

char cutUnlock[] = {
	2, 2, 2, 4, 5,
	6, 7, 7, 7, 9,
	11, 11, 11, 11, 12,
	12, 13, 13, 14, 15,
	17, 17, 17, 17, 18,
	18, 19, 19, 19, 19,
	21, 21, 21, 21, 22,
	22, 22, 23, 23, 23,
	28
};

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
	{ 8, 18 },
	{ 18, 28 },
	{ 28, 37 }
};

BOTCH botch[38] = {
	// Chicago
	{ 1, &MissionName[0]},
	{ 2, &MissionName[1]},
	{ 3, &MissionName[2]},
	{ 4, &MissionName[3]},
	{ 5, &MissionName[4]},
	{ 6, &MissionName[5]},
	{ 7, &MissionName[6]},
	{ 9, &MissionName[7]},
	// Havana
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
	// Vegas
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
	// Rio
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

int cutSelection = 0;
int currCity = 0;

enum MenuSelectScreens
{
	SCREEN_NONE = 0,

	SCREEN_MISSION,
	SCREEN_CAR,
	SCREEN_CUTCITY,		// really not used, but keep it here
	SCREEN_CUTSCENE,
	SCREEN_SCORES,
	SCREEN_TIMEOFDAY,
};

MenuSelectScreens iScreenSelect = SCREEN_NONE;

int bRedrawFrontend = 1;
int bReturnToMain = 1;

int idle_timer = 0;
int currPlayer = 1;
int feNewPad = 0;
int fePad = 0;
int ScreenDepth = 0;

int gIdleReplay = 0;

int padsConnected[2] = { 1, 0 };
int feVariableSave[4] = { -1 };

int bDrawExtra = 0;
int mainScreenLoaded = 1;
int bDoneAllready = 0;
int allowVibration = 1;
int bQuitToSystem = 0;
int bQuitToSystemSel = 0;

int carSelection = 0;
int carColour = 0;
int currSelIndex = 0;
int lastCutCity = -1;
int lastCity = -1;
int currMission = -1;
int missionSetup = 0;

#ifndef PSX
#define S_INT(v)  ((
#define S_INT_U8(v) ((((v) << 24) >> 24) & 0xff)

int choose_type;
int choose_mode;
int choose_count;
int choose_error;
int *choose_custom;
int *choose_default;
char **choose_items;
u_char *choose_value;
#endif

char* ScreenNames[12] = { 0 };

char loaded[3] = {
	-1,	// City
	-1, // Cars
	-1  // Cuts
};

FE_SCREEN* pCurrScreen = NULL;
FE_SCREEN* pNewScreen = NULL;

FE_BUTTON* pNewButton = NULL;
FE_BUTTON* pCurrButton = NULL;

FE_SCREEN* pScreenStack[10] = { 0 };
FE_BUTTON* pButtonStack[10] = { 0 };

POLY_FT4 BackgroundPolys[6];
FE_FONT feFont;

RECT16 extraRect = { 896, 256, 64, 219 };

SPRT extraSprt;
POLY_FT3 extraDummy;

int BuildButtonsVertical(FE_SCREEN *screen, int count, int xStart, int yStart);
void InitChooserScreen(FE_SCREEN *screen);

int FEStringWidth(char* string);
int FEPrintStringSized(char* string, int x, int y, int scale, int transparent, int r, int g, int b);
int FEPrintString(char* string, int x, int y, int justification, int r, int g, int b);

void LoadFrontendScreens(int full);
void NewSelection(short dir);
void EndFrame(void);

// [D] [T]
void SetVariable(int var, int &action)
{
	int code = (var >> 8);
	int value = (var & 0xff);

	switch (code)
	{
		case VAR_GAME_LEVEL:
			GameLevel = value;
			break;
		case VAR_GAME_TYPE:
			GameType = (GAMETYPE)value;

			if (value != GAME_COPSANDROBBERS)
				gWantNight = 0;

			break;
		case VAR_MULTIPLAYER:
			NumPlayers = (value + 1);
			break;
		case VAR_TIMEOFDAY:
			gWantNight = value > 0;

			break;
		case VAR_MISSION_NUMBER:
			gCurrentMissionNumber = 1;
			GameType = GAME_MISSION;
			break;
		case VAR_LOAD_GAME:
			pScreenStack[ScreenDepth] = pCurrScreen;
			pButtonStack[ScreenDepth] = pCurrButton;

			if (value == 1) 
			{
#ifdef PSX
#else
				// [A] temporary
				// TODO: Do menu with the replays
				if(LoadReplayFromFile("Replays/CHASE.D2RP"))
				{
					StoredGameType = GameType;
					GameType = GAME_LOADEDREPLAY;
					SetState(STATE_GAMESTART);
				}
				else
#endif
				{
					SetState(STATE_INITFRONTEND);
				}
			}
			else
			{
				// [A] load configuration
				LoadCurrentProfile(0);

				//SetState(STATE_INITFRONTEND);
				SetMasterVolume(gMasterVolume);
				SetXMVolume(gMusicVolume);
			}

			break;
		case VAR_SAVE_GAME:
			pScreenStack[ScreenDepth] = pCurrScreen;
			pButtonStack[ScreenDepth] = pCurrButton;

#ifndef PSX
			if (value == 0) 
			{
				// [A] save configuration
				SaveCurrentProfile(1);
			}
			else 
			{
				// [A] load progress
				if(LoadCurrentGame())
				{
					GameType = GAME_CONTINUEMISSION;
					SetState(STATE_GAMESTART);
				}
			}
#endif

			break;
		case VAR_SUB_GAME:
			gSubGameNumber = value;
			break;
		case VAR_SUBTITLES:
			gSubtitles = (value == 0) ? 0 : 1;
			break;
		case VAR_INVINCIBILITY:
			gInvincibleCar = value;
			ActiveCheats.cheat3 = value;
			break;
		case VAR_IMMUNITY:
			gPlayerImmune = value;
			ActiveCheats.cheat4 = value;
			break;
		case VAR_MINIGAME:
			GameLevel = 3;
			gSubGameNumber = (value == 0) ? 2 : 0;
			break;
		case VAR_DEMO_CHASE:
			GameType = GAME_IDLEDEMO;
			gCurrentMissionNumber = (value + 400);
			break;
#if ENABLE_BONUS_CONTENT
		case VAR_BONUS_GALLERY: // [A]
			ShowBonusGallery();
			LoadFrontendScreens(0);
			break;
		case VAR_MINI_CARS: // [A] mini cars cheat
			ActiveCheats.cheat13 = value;
			break;
#endif
#ifndef PSX
		case VAR_CHOOSE_TYPE: // [A] chooser type
		{
			static char* ChooseQualityItems[] = {
				G_LTXT(GTXT_Low),
				G_LTXT(GTXT_Medium),
				G_LTXT(GTXT_High),
				G_LTXT(GTXT_Ultra),
				NULL,
			};

			static char* ChoosePGXPItems[] = {
				G_LTXT(GTXT_Off),
				G_LTXT(GTXT_TexturesOnly),
				G_LTXT(GTXT_ZBufferOnly),
				G_LTXT(GTXT_All),
				NULL,
			};

			choose_type = value;
			choose_default = NULL;
			choose_custom = NULL;
			choose_items = NULL;
			choose_value = NULL;
			choose_mode = -1;
			choose_error = 0;

			switch (value)
			{
				case 0:
					choose_default = &syscfg.gTrafficDensity;
					choose_value = &gExtraConfig.gTrafficDensity;
					choose_items = ChooseQualityItems;
					choose_mode = 1;
					break;
				case 1:
					choose_default = &syscfg.gPedestrianDensity;
					choose_value = &gExtraConfig.gPedestrianDensity;
					choose_items = ChooseQualityItems;
					choose_mode = 1;
					break;
				case 2:
					choose_custom = &syscfg.gDrawDistance;
					choose_default = &syscfg.gDrawDistanceLevelBackup;
					choose_value = &gExtraConfig.p.DrawDistance;
					choose_items = ChooseQualityItems;
					choose_mode = 1;
					break;
				case 3:
					choose_default = &syscfg.psyx_cfg_pgxpMode;
					choose_value = &gExtraConfig.p.PGXPMode;
					choose_items = ChoosePGXPItems;
					choose_mode = 1;
					break;
				case 4:
					// TODO
					choose_default = &syscfg.fullScreen;
					choose_value = &gExtraConfig.p.FullScreen;
					choose_mode = 0;
					break;
				case 5:
					choose_default = &syscfg.vsync;
					choose_value = &gExtraConfig.p.VSync;
					choose_mode = 0;
					break;
				case 6:
					choose_default = &syscfg.psyx_cfg_bilinearFiltering;
					choose_value = &gExtraConfig.p.Bilinear;
					choose_mode = 0;
					break;
				case 7:
					choose_default = &syscfg.gEnableDlights;
					choose_value = &gExtraConfig.p.DynamicLights;
					choose_mode = 0;
					break;
				default:
					choose_type = -1;
					break;
			}

			choose_count = 0;

			if (choose_mode == 1)
			{
				while (choose_items[choose_count] != 0)
					choose_count++;
			}

			break;
		}
		case VAR_CHOOSE_VALUE:
			if (choose_value)
			{
				if (value > choose_count)
				{
					value = -1;

					if (choose_mode == 0)
					{
						if (choose_default == NULL)
						{
							printError("HEY!\n");
							return;
						}

						value = *choose_default;
					}
					else if (choose_custom == NULL)
					{
						if (choose_default != NULL)
							value = *choose_default;
					}

					if (value == -1)
					{
						int var = pCurrScreen->buttons[choose_count - 1].var;

						int code = (var >> 8);

						value = (var & 0xff);

						if (code != VAR_CHOOSE_VALUE)
						{
							action = 0;

							FESound(1);
							choose_error = 1;
						}
					}

					choose_error = 0;
				}

				if (choose_error)
					return;

				*choose_value = value + 1;

				switch (choose_type)
				{
					case 2:
						extern void SetDrawDistance(int level);

						value = *choose_value;

						SetDrawDistance(value);
						break;
					case 3:
						extern int g_cfg_pgxpTextureCorrection;
						extern int g_cfg_pgxpZBuffer;

						// Disabled/None (0), TextureCorrection (1), ZBuffer (2), Enabled/Both (3)
						g_cfg_pgxpTextureCorrection = (value & 1);
						g_cfg_pgxpZBuffer = (value & 2);
						
						break;
					case 4:
						// TODO: Psy-X reinitialize in fullscreen!
						break;
					case 5:
						extern int g_cfg_swapInterval;
						g_cfg_swapInterval = value;
						break;
					case 6:
						extern int g_cfg_bilinearFiltering;
						g_cfg_bilinearFiltering = value;
						break;
					case 7:
						extern int gEnableDlights;
						gEnableDlights = value;
						break;
				}
			}

			choose_error = 0;
			break;
#endif
	}
}

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

	if (pScr->userFunctionNum == Fn_None || pScr->userFunctionNum == Fn_End || FE_INIT_SCREEN(pScr) == FN_OK)
	{
		if (pNewButton != NULL) 
		{
			pCurrButton = pNewButton;
			pNewButton = NULL;
		}
		else 
			pCurrButton = pScr->buttons;
	}
}

DR_MOVE In;
DR_MOVE Out;
RECT16 storeRect = { 768, 475, 255, 36 };

char* TimeOfDayNames[] = {
	G_LTXT_ID(GTXT_Dawn),
	G_LTXT_ID(GTXT_Day),
	G_LTXT_ID(GTXT_Dusk),
	G_LTXT_ID(GTXT_Night)
};

char* WeatherNames[] = {
	G_LTXT_ID(GTXT_Clear),
	G_LTXT_ID(GTXT_Rainy),
	G_LTXT_ID(GTXT_Wet),
};

// [D] [T]
void DisplayOnScreenText(void)
{
	char* text;

	sprintf(ScreenTitle, NullStr);

	if (padsConnected[0] == 0) {
		int transparent = 0;

		if (Pads[0].type == 0) {
			text = "Please insert controller into Port 1";
			transparent = 1;
		}
		else 
		{
			if (Pads[0].type != 1)
				return;

			text = "Incompatible controller in Port 1";
		}

		FEPrintStringSized(text, 40, 400, 3072, transparent, 64, 64, 64);
	}
	else
	{
		if (iScreenSelect != SCREEN_SCORES && iScreenSelect != SCREEN_CAR)
		{
			for (int i = 0; i < ScreenDepth; i++)
			{
				if (i > 0)
					strcat(ScreenTitle, " - ");

				strcat(ScreenTitle, ScreenNames[i]);
			}

			FEPrintStringSized(ScreenTitle, 40, 400, 3072, 1, 64, 64, 64);
		}

		if (iScreenSelect == SCREEN_CUTSCENE)
		{
			text = GET_MISSION_TXT(CutSceneNames[cutSelection + CutAmountsTotal[currCity]]);

			FEPrintStringSized(text, 100, 226, 3072, 1, 64, 64, 64);
		}

		if (iScreenSelect == SCREEN_TIMEOFDAY)
		{
			FEPrintString(GET_GAME_TXT(TimeOfDayNames[wantedTimeOfDay]), 596, 208, 4, 128, 128, 128);
			FEPrintString(GET_GAME_TXT(WeatherNames[wantedWeather]), 596, 246, 4, 128, 128, 128);
		}

		if (iScreenSelect == SCREEN_CAR)
		{
			FE_BUTTON *btn = &PsxScreens[Sc_CarSelect].buttons[3];

			extern CVECTOR debris_colour[4][31];

			int car_model = carNumLookup[GameLevel][carSelection];
			int car_colour = 0;

			if (car_model == 0)
				car_colour = 1;
			else if(car_model < 8)
				car_colour = (car_model-1) * 6 + carColour + 7;
			else 
				car_colour = car_model - 6;

			CVECTOR *col = &debris_colour[GameLevel][car_colour];

			FEPrintString(G_LTXT(GTXT_Color), btn->x + 190, btn->y + 270, 4, 128, 128, 128);

			POLY_F4 *f4 = (POLY_F4*)current->primptr;
			current->primptr += sizeof(POLY_F4);

			setPolyF4(f4);
			setXYWH(f4, btn->x + 200, btn->y + 277, 24, 24);
			setRGB0(f4, col->r, col->g, col->b);

			addPrim(current->ot + 1, f4);
		}

#ifndef PSX
		if (choose_error)
		{
			FEPrintStringSized("Invalid selection - please select a new option", 140, 200, 0xc00, 0, 128, 0, 0);
		}
#endif
	}
}

void DrawButton(FE_BUTTON* pBtn, int i)
{
	int status = pBtn->action >> 8;

	int draw = (status != BTN_HIDDEN);

#ifndef PSX
	if (pBtn == pCurrButton)
	{
		SPRT* hghltSprt;
		POLY_FT4* hghltDummy;
		RECT16 rect;

		rect.x = pCurrButton->s_x;
		rect.y = pCurrButton->s_y;
#ifndef PSX
		rect.w = pCurrButton->s_w;
		rect.h = pCurrButton->s_h;
#endif

		hghltSprt = (SPRT*)current->primptr;
		current->primptr += sizeof(SPRT);
		*hghltSprt = HighlightSprt;

		hghltDummy = (POLY_FT4*)current->primptr;
		current->primptr += sizeof(POLY_FT4);
		*hghltDummy = HighlightDummy;

		setXY0(hghltSprt, rect.x, rect.y);
#ifndef PSX
		setWH(hghltSprt, rect.w, rect.h);
#endif

		addPrim(current->ot + 6, hghltSprt);
		addPrim(current->ot + 6, hghltDummy);

		draw = 1;
	}
#endif

	if (draw)
	{
		if (status == BTN_DISABLED)
		{
#ifndef PSX
			FEPrintString(pBtn->Name, pBtn->x * 2 + pBtn->w, pBtn->y, pBtn->justify, 32, 32, 32);
#else
			FEPrintString(pBtn->Name, pBtn->x * 2 + pBtn->w, pBtn->y, 4, 32, 32, 32);
#endif
		}
		else
		{
#ifndef PSX
			FEPrintString(pBtn->Name, pBtn->x * 2 + pBtn->w, pBtn->y, pBtn->justify, pBtn->cR, pBtn->cG, pBtn->cB);
#else
			if (iScreenSelect == SCREEN_MISSION && (i == 0 || i == 5) ||
				iScreenSelect == SCREEN_CAR && (i == 0 || i == 2) ||
				iScreenSelect == SCREEN_CUTSCENE && (i == 0 || i == 2) ||
				iScreenSelect == SCREEN_TIMEOFDAY && i == 2)				// [A]
			{
				FEPrintString(pBtn->Name, pBtn->x * 2 + pBtn->w, pBtn->y, 4, 124, 108, 40);
			}
			else
			{
				FEPrintString(pBtn->Name, pBtn->x * 2 + pBtn->w, pBtn->y, 4, 128, 128, 128);
			}
#endif
		}
	}
}

// [D] [T]
void DrawScreen(PSXSCREEN *pScr)
{
	char version_info[32];
	int numBtnsToDraw;
	int i;

	for (i = 0; i < 6; i++)
		addPrim(current->ot + 11, &BackgroundPolys[i]);

	if (pScr)
	{
		GetTimeStamp(version_info);

		if (iScreenSelect == SCREEN_CUTCITY && (gFurthestMission < 39))
		{
			// hide the Director's Cut button
			numBtnsToDraw = pScr->numButtons - 1;
		}
		else 
		{
			numBtnsToDraw = pScr->numButtons;
		}

#ifdef PSX
		for (i = 0; i < numBtnsToDraw; i++)
			DrawButton(&pScr->buttons[i], i);
#else
		if(bQuitToSystem)
		{
			int len;
			int quitLen;

			quitLen = FEStringWidth(G_LTXT(GTXT_QuitToSystem));
			FEPrintString(G_LTXT(GTXT_QuitToSystem), 320 - quitLen / 2, 256, 0, 128, 128, 128);

			if (quitLen < 100)
				quitLen = 100;
			
			len = FEStringWidth(G_LTXT(GTXT_YES));
			FEPrintString(G_LTXT(GTXT_YES), 320 - quitLen / 4 - len / 2, 288, 0, 128, 128, bQuitToSystemSel ? 0 : 128);

			len = FEStringWidth(G_LTXT(GTXT_NO));
			FEPrintString(G_LTXT(GTXT_NO), 320 + quitLen / 4 - len/2, 288, 0, 128, 128, bQuitToSystemSel ? 128 : 0);
		}
		else
		{
			NewSelection(0);
			
			for (i = 0; i < numBtnsToDraw; i++)
				DrawButton(&pScr->buttons[i], i);
		}
#endif

		// debug version text
#if defined(_DEBUG) || defined(DEBUG_OPTIONS)
		FEPrintString(version_info, 40, 16, 0, 128, 128, 0);
		FEPrintString("--- " GAME_VERSION " ---", 320, 16, 0, 128, 128, 0);
#endif

		SetTextColour(128, 0, 0);

		DisplayOnScreenText();
		
		if (bDrawExtra) 
		{
#ifdef PSX
			addPrim(current->ot + 2, &extraSprt);
			addPrim(current->ot + 2, &extraDummy);
#else
			SPRT* extrSprt;
			POLY_FT3* extrDummy;
			
			extrSprt = (SPRT*)current->primptr;
			current->primptr += sizeof(SPRT);
			*extrSprt = extraSprt;

			extrDummy = (POLY_FT3*)current->primptr;
			current->primptr += sizeof(POLY_FT3);
			*extrDummy = extraDummy;

			addPrim(current->ot + 2, extrSprt);
			addPrim(current->ot + 2, extrDummy);
#endif
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

extern POLY_FT4 cd_sprite;

// [D] [T]
void FEDrawCDicon(void)
{
	ushort* palette;
	int i;
	RECT16 dest;

	if(!bCdIconSetup)
		return;

	cd_icon[23] = cd_icon[11];

	palette = &cd_icon[10];

	for (i = 0; i < 12; i++)
	{
		palette[1] = palette[2];
		palette++;
	}

	dest.x = 960;
	dest.y = 433;
	dest.w = 16;
	dest.h = 1;

	LoadImage(&dest, (u_long*)(cd_icon + 10));

	DrawPrim(&cd_sprite);
	DrawSync(0);
#ifndef PSX
	PsyX_EndScene();
#endif
}

// [D] [T]
void SetupExtraPoly(char *fileName, int offset, int offset2)
{
	int i;
	RECT16 rect = extraRect;

	FEDrawCDicon();
	Loadfile(fileName, (char*)_frontend_buffer + offset2);

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

// [D] [T]
void LoadBackgroundFile(char* name)
{
	int iTpage;
	RECT16 rect;
	int i;

	iTpage = 11;

	mainScreenLoaded = (strcmp(name, "DATA\\GFX.RAW") == 0);

	rect.w = 64;
	rect.h = 256;

	for (i = 0; i < 6; i++)
	{
		FEDrawCDicon();

		LoadfileSeg(name, (char*)_other_buffer, i * 0x8000, 0x8000);
		FEDrawCDicon();

		rect.y = (i / 6);
		rect.x = (i - rect.y * 6) * 64 + 640;
		rect.y *= 256;

		LoadImage(&rect, (u_long*)_other_buffer);
		FEDrawCDicon();
	}

	LoadfileSeg(name, (char*)_other_buffer, iTpage * 0x8000, 512);
	FEDrawCDicon();

	rect.h = 1;
	rect.y = (iTpage / 6);
	rect.x = (iTpage - rect.y * 6) * 64 + 640;
	rect.y *= 256;

	LoadImage(&rect, (u_long*)_other_buffer);
	DrawSync(0);

	SetupBackgroundPolys();

	bRedrawFrontend = 1;
}

FE_BUTTON * InsertButtonVertical(FE_SCREEN *screen, int index, char *text)
{
	if (index < 0 || index >= 8)
		return NULL;

	int numButtons = screen->numButtons;
	int lastButton = numButtons - 1;
	int height = 0;

	if (numButtons + 1 > 8)
		return NULL;

	if (index < numButtons)
	{
		height = screen->buttons[index].y - screen->buttons[index - 1].y;

		for (int i = lastButton; i >= index; i--)
		{
			FE_BUTTON& oldBtn = screen->buttons[i];
			FE_BUTTON& newBtn = screen->buttons[i + 1];

			newBtn = oldBtn;

			if (newBtn.u != 0)
			{
				newBtn.u++;
			}

			if (newBtn.d != 0)
			{
				if (newBtn.d > 1)
					newBtn.d++;
			}

			newBtn.y += height;
			newBtn.s_y += height;
		}
	}
	else
	{
		if (numButtons > 1)
		{
			height = screen->buttons[lastButton].y - screen->buttons[lastButton - 1].y;
		}
		else
		{
			height = screen->buttons[lastButton].y + 38;
		}

		height *= 1 + (index - numButtons);

		FE_BUTTON& oldBtn = screen->buttons[lastButton];
		FE_BUTTON& newBtn = screen->buttons[index];

		newBtn = oldBtn;

		oldBtn.d = index + 1;
		newBtn.u = index;

		newBtn.y += height;
		newBtn.s_y += height;

		newBtn.action = 0;
		newBtn.var = VAR_NONE;
	}

	if (text != NULL)
		strcpy(screen->buttons[index].Name, text);
	else
		screen->buttons[index].Name[0] = '\0';

	screen->buttons[screen->numButtons++].d = 1;
	screen->buttons[0].u = screen->numButtons;

	return &screen->buttons[index];
}

void InitChooserScreen(FE_SCREEN *screen)
{
	*screen = PsxScreens[Sc_SubtitlesOnOff];
	screen->userFunctionNum = Fn_ChooseOptionScreen;

	// NB: assumes 'On' / 'Off' buttons in that order!
	for (int i = 0; i < screen->numButtons; i++)
	{
		FE_BUTTON& btn = screen->buttons[i];

		btn.action = FE_MAKEVAR(BTN_PREVIOUS_SCREEN, 0);
		btn.var = FE_MAKEVAR(VAR_CHOOSE_VALUE, i ^ 1);
	}
}

void InitDetailsScreen(FE_SCREEN *screen)
{
	static int ButtonScreenMap[] = {
		Sc_FullScreenOnOff,
		Sc_VSyncOnOff,
		Sc_PGXPSettings,
		Sc_BilinearOnOff,
		Sc_DrawDistance,
		Sc_DynamicLightsOnOff,
		Sc_AdjustDensity,
		Sc_AdjustDensity,
	};

	static char ButtonTypeMap[] = {
		-4, 5, 3, 6, 2, 7, 0, 1
	};

	static char *ButtonNames[] = {
		G_LTXT(GTXT_FullScreen),
		G_LTXT(GTXT_VSync),
		G_LTXT(GTXT_PGXP),
		G_LTXT(GTXT_TextureFilter),
		G_LTXT(GTXT_DrawDistance),
		G_LTXT(GTXT_DynamicLights),
		G_LTXT(GTXT_TrafficDensity),
		G_LTXT(GTXT_PedsDensity),
	};

	int numButtons = BuildButtonsVertical(screen, 8, 156, 190);

	for (int i = 0; i < numButtons; i++)
	{
		FE_BUTTON& btn = screen->buttons[i];
		int type = ButtonTypeMap[i];

		strcpy(btn.Name, ButtonNames[i]);

		if (type < 0)
		{
			type = -type;
			btn.action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		else
		{
			btn.action = FE_MAKEVAR(BTN_NEXT_SCREEN, ButtonScreenMap[i]);
		}

		btn.var = FE_MAKEVAR(VAR_CHOOSE_TYPE, type);
	}
}

void InitCustomScreens()
{
	// Time of day extended screen
	PsxScreens[Sc_TimeOfDay].userFunctionNum = Fn_TimeOfDaySelectScreen;

	// for web demo content (or empty SCRS.BIN)
	if (PsxScreens[Sc_Main].userFunctionNum == Fn_End)
		PsxScreens[Sc_Main].userFunctionNum = Fn_DemoScreen;

#ifndef PSX
	// replay theater
	PsxScreens[Sc_Replays].buttons[0].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_ReplayTheater);
	PsxScreens[Sc_Replays].buttons[0].var = VAR_NONE;
	PsxScreens[Sc_ReplayTheater].userFunctionNum = Fn_UserReplaySelectScreen;

	InitChooserScreen(&PsxScreens[Sc_FullScreenOnOff]);
	InitChooserScreen(&PsxScreens[Sc_VSyncOnOff]);
	InitChooserScreen(&PsxScreens[Sc_BilinearOnOff]);
	InitChooserScreen(&PsxScreens[Sc_PGXPSettings]);
	InitChooserScreen(&PsxScreens[Sc_DrawDistance]);
	InitChooserScreen(&PsxScreens[Sc_DynamicLightsOnOff]);
	InitChooserScreen(&PsxScreens[Sc_AdjustDensity]);

	InitDetailsScreen(&PsxScreens[Sc_DetailOptions]);

	// insert link in Options
	InsertButtonVertical(&PsxScreens[Sc_Options], 2, G_LTXT(GTXT_Details));

	FE_BUTTON &btn = PsxScreens[Sc_Options].buttons[2];

	btn.action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_DetailOptions);
	btn.var = VAR_NONE;

	//{
	//	//
	//	// add to end of Gameplay menu
	//	//
	//
	//	FE_SCREEN *gameplaySc = &PsxScreens[Sc_GameplayOptions];
	//	FE_BUTTON *btn = &gameplaySc->buttons[gameplaySc->numButtons - 1];
	//
	//	int lastButton = gameplaySc->numButtons;
	//
	//	static char *density_names[] = {
	//		"Traffic Density",
	//		"Peds Density",
	//	};
	//
	//	for (int i = 0; i < 2; i++)
	//	{
	//		if (i == 0)
	//			btn->d = lastButton + 1;
	//		else
	//			btn[i].d = lastButton + 1;
	//
	//		// copy the button
	//		btn[i + 1] = *btn;
	//
	//		btn[i + 1].u = lastButton;
	//		btn[i + 1].d = 1;
	//
	//		btn[i + 1].l = 0;
	//		btn[i + 1].r = 0;
	//
	//		btn[i + 1].s_x = btn->s_x;
	//		btn[i + 1].s_y = btn->s_y + (i + 1) * 38;
	//
	//		btn[i + 1].x = btn->x;
	//		btn[i + 1].y = btn->y + (i + 1) * 38;
	//
	//		btn[i + 1].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_AdjustDensity);
	//		btn[i + 1].var = FE_MAKEVAR(VAR_CHOOSE_TYPE, i);
	//
	//		strcpy(btn[i + 1].Name, density_names[i]);
	//
	//		lastButton = ++gameplaySc->numButtons;
	//	}
	//
	//	gameplaySc->buttons[0].u = lastButton;
	//	gameplaySc->buttons[lastButton - 1].d = 1;
	//}
#endif // PSX

#if ENABLE_BONUS_CONTENT
	// make mini cars cheat screen
	PsxScreens[Sc_MiniCarsOnOff] = PsxScreens[Sc_ImmunityOnOff];
	PsxScreens[Sc_MiniCarsOnOff].userFunctionNum = Fn_MiniCarsOnOffScreen;
	PsxScreens[Sc_MiniCarsOnOff].buttons[0].var = FE_MAKEVAR(VAR_MINI_CARS, 1);
	PsxScreens[Sc_MiniCarsOnOff].buttons[1].var = FE_MAKEVAR(VAR_MINI_CARS, 0);
#endif
}

// [D] [T]
void LoadFrontendScreens(int full)
{
	int size;
	int iNumScreens;
	char* ptr;
	RECT16 rect;

	ShowLoadingScreen("GFX\\FELOAD.TIM", 1, 12);
	ShowLoading();

#ifndef USE_EMBEDDED_FRONTEND_SCREENS
	if (full)
	{
		Loadfile("DATA\\SCRS.BIN", (char*)_other_buffer);

		ptr = (char*)_other_buffer + 20; // skip header and number of screens
		iNumScreens = (int)_other_buffer[16];

		for (int i = 0; i < iNumScreens; i++)
		{
			PsxScreens[i].numButtons = *ptr++;
			PsxScreens[i].userFunctionNum = *ptr++;

			for (int j = 0; j < PsxScreens[i].numButtons; j++)
			{
#ifndef PSX
				PSXBUTTON *pPSXBtn = (PSXBUTTON*)ptr;
				FE_BUTTON *pBtn = &PsxScreens[i].buttons[j];

				// copy everything into our struct
				memcpy((u_char*)pBtn, (u_char*)ptr, sizeof(PSXBUTTON));
				ptr += sizeof(PSXBUTTON);

				// fixup our struct
				pBtn->justify = 4;

				pBtn->s_w = 256;
				pBtn->s_h = 36;

				pBtn->action = (short)pPSXBtn->action;
				pBtn->var = (short)pPSXBtn->var;

				if (i == Sc_MissionSelect && (j == 0 || j == 5) ||
					i == Sc_CarSelect && (j == 0 || j == 2) ||
					i == Sc_CutSceneSelect && (j == 0 || j == 2))
				{
					pBtn->cR = 124;
					pBtn->cG = 108;
					pBtn->cB = 40;
				}
				else
				{
					pBtn->cR = 128;
					pBtn->cG = 128;
					pBtn->cB = 128;
				}
#else
				memcpy((u_char*)&PsxScreens[i].buttons[j], (u_char*)ptr, sizeof(PSXBUTTON));
				ptr += sizeof(PSXBUTTON);
#endif
			}
		}
	}
#endif // !USE_EMBEDDED_FRONTEND_SCREENS

	// [A] SCREEN HACKS
	InitCustomScreens();

	rect.w = 64;
	rect.h = 256;

	ShowLoading();
	LoadBackgroundFile("DATA\\GFX.RAW");

	for (int i = 0; i < 2; i++)
	{
		// [A] optimized. Before it was to wasteful to load 16 sectors
		int loadSize = i == 0 ? 0x8000 : (36 * 128);
		rect.h = i == 0 ? 256 : 36;
		
		ShowLoading();
		LoadfileSeg("DATA\\GFX.RAW", (char*)_other_buffer, 0x30000 + (i * 0x8000), loadSize);

		rect.x = 640 + (i * 64);
		rect.y = 256;

		LoadImage(&rect, (u_long*)_other_buffer);
		DrawSync(0);
	}

	// Load clut
	ShowLoading();
	LoadfileSeg("DATA\\GFX.RAW", (char*)_other_buffer, 0x58000, /*0x8000*/ 512);

	rect.x = 960;
	rect.y = 256;
	rect.h = 4;

	LoadImage(&rect, (u_long*)_other_buffer);
	DrawSync(0);

	if (full)
	{
		Loadfile("DATA\\FEFONT.BNK", (char*)_other_buffer);
		memcpy((u_char*)&feFont, (u_char*)_other_buffer, sizeof(feFont));
	}
}

// [D] [T]
void ReInitScreens(int returnToMain)
{
#ifndef PSX
	bReturnToMain = returnToMain;

	if(bReturnToMain)
	{
		bCdIconSetup = 0;
		iScreenSelect = SCREEN_NONE;

		cutSelection = 0;
		currCity = 0;

		bRedrawFrontend = 0;

		idle_timer = 0;
		currPlayer = 1;
		feNewPad = 0;
		fePad = 0;
		ScreenDepth = 0;

		loaded[0] = -1;
		loaded[1] = -1;
		loaded[2] = -1;
	
		padsConnected[0] = 1;
		padsConnected[1] = 0;

		bDrawExtra = 0;
		mainScreenLoaded = 1;
		bDoneAllready = 0;
		allowVibration = 1;

		ScreenNames[0] = 0;
		gInFrontend = 1;
		currMission = -1;
		missionSetup = 0;
	}

	extern void SwitchMappings(int menu);
	SwitchMappings(1);
#endif // !PSX

	bCdIconSetup = 0;
	InitCdIcon();

	if (bReturnToMain)
	{
		ScreenDepth = 0;
		NumPlayers = 1;
		gWantNight = 0;
		gNight = 0;
		gTimeOfDay = TIME_DAY;
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

	// [A] state hack for demo
	if (pCurrScreen == NULL)
		pCurrScreen = &PsxScreens[Sc_Main];

	SetupScreenSprts(pCurrScreen);
	SetupBackgroundPolys();

	idle_timer = VSync(-1);
}

// [D] [T]
void NewSelection(short dir)
{
	FE_BUTTON *pNewB;
	RECT16 rect;

	if (pCurrScreen->numButtons == 0)
		return;

	pNewB = pCurrButton;
	int btn = 0;

	// any buttons pressed?
	if (dir != 0)
	{
#ifdef PSX
		SetDrawMove(&In, &storeRect, pCurrButton->s_x, pCurrButton->s_y);
		addPrim(current->ot + 9, &In);
#endif

		if ((dir & MPAD_D_UP) != 0)
		{
			btn = pCurrButton->u;
		}
		else if ((dir & MPAD_D_DOWN) != 0)
		{
			btn = pCurrButton->d;
		}
		else if ((dir & MPAD_D_LEFT) != 0)
		{
			btn = pCurrButton->l;
		}
		else if ((dir & MPAD_D_RIGHT) != 0)
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

	// show who has control
	if (NumPlayers == 2 && currPlayer != 1)
		FEPrintStringSized(G_LTXT(GTXT_Player2), 400, 260, 3072, 0, 128, 128, 128);

#ifdef PSX
	rect.x = pCurrButton->s_x;
	rect.y = pCurrButton->s_y;
	rect.w = 255;
	rect.h = 36;

	SetDrawMove(&Out, &rect, storeRect.x, storeRect.y);
	addPrim(current->ot + 8, &Out);

	setXY0(&HighlightSprt, rect.x, rect.y);

	addPrim(current->ot + 6, &HighlightSprt);
	addPrim(current->ot + 6, &HighlightDummy);

	DrawButton(pNewB, pNewB - pCurrScreen->buttons);

	EndFrame();
#endif
}

// [D] [T]
int HandleKeyPress(void)
{
	if (pCurrScreen == NULL || pCurrButton == NULL)
		return 0;

	if (pCurrScreen->userFunctionNum != Fn_None)
	{
		// notify the user function first
		if (FE_STEP_SCREEN(pCurrScreen) != FN_OK)
		{
			// user function handled the key press
			feNewPad = 0;
		}
	}

	if (feNewPad & MPAD_CROSS)
	{	
		int action = pCurrButton->action >> 8;

		if (action != BTN_DISABLED)
		{
			FESound(2);

			if (pCurrButton->var != VAR_NONE)
				SetVariable(pCurrButton->var, action);

			switch (action)
			{
				case BTN_NEXT_SCREEN:
					pScreenStack[ScreenDepth] = pCurrScreen;
					pButtonStack[ScreenDepth] = pCurrButton;

					ScreenNames[ScreenDepth] = pCurrButton->Name;

					pNewScreen = &PsxScreens[pCurrButton->action & 0xFF];

#ifndef PSX
					if (pNewScreen->userFunctionNum == Fn_ChooseOptionScreen)
						InitChooserScreen(pNewScreen);
#endif

					if (ScreenDepth < 10)
						ScreenDepth++;

					break;
				case BTN_START_GAME:
					if (NumPlayers == 2 && iScreenSelect == SCREEN_CAR && (currPlayer == 2))
					{
						FE_INIT_SCREEN(pCurrScreen);
						bRedrawFrontend = 1;
					}
					else
					{
						pScreenStack[ScreenDepth] = pCurrScreen;
						pButtonStack[ScreenDepth] = pCurrButton;

						ScreenNames[ScreenDepth] = pCurrButton->Name;

						SetState(STATE_GAMESTART);
					}
					break;
				case BTN_PREVIOUS_SCREEN:
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
	else if (feNewPad & MPAD_TRIANGLE)
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
		if ((feNewPad & (MPAD_D_UP | MPAD_D_RIGHT | MPAD_D_DOWN | MPAD_D_LEFT)) != 0)
		{
			NewSelection(feNewPad);
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


// [D] [T]
void PadChecks(void)
{
	int i;
	// TODO: null check for pCurrScreen

	int oldnum = numPadsConnected;

	ReadControllers();
	
	numPadsConnected = 0;
	feNewPad = Pads[0].mapnew;
	fePad = Pads[0].mapped;

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
	if(feNewPad & MPAD_TRIANGLE)
	{
		if(ScreenDepth == 0)
		{
			bQuitToSystem ^= 1;
			FESound(0);
		}
	}

	if(bQuitToSystem)
	{
		if (feNewPad & MPAD_CROSS)
		{
			if(bQuitToSystemSel == 1)
				bQuitToSystem = 2;
			else
				bQuitToSystem = 0;

			FESound(2);
		}
		else if ((feNewPad & MPAD_D_LEFT) || (feNewPad & MPAD_D_RIGHT))
		{
			bQuitToSystemSel += 1;
			bQuitToSystemSel &= 1;

			FESound(3);
		}

		feNewPad = 0;
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

			if (pCurrScreen->userFunctionNum == Fn_GamePlayScreen)
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

			if (pCurrScreen->userFunctionNum == Fn_GamePlayScreen)
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
		feNewPad = 0x10;

		if (pCurrScreen->userFunctionNum != Fn_None) 
		{
			FE_STEP_SCREEN(pCurrScreen);
		}

		feNewPad = 0;

		if (ScreenDepth != 0) 
		{
			ReInitScreens(bReturnToMain);
		}
	}
	if (bRedrawFrontend == 0 && numPadsConnected != oldnum &&
		(gInFrontend != 0 && (pCurrScreen != NULL && pCurrScreen->userFunctionNum != Fn_None)))
	{
		FE_INIT_SCREEN(pCurrScreen);
		bRedrawFrontend = 1;
	}
}

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
	MPBuff[0][0].primtab = (char*)_primTab1;
	MPBuff[0][0].primptr = (char*)_primTab1;
	MPBuff[0][0].ot = (OTTYPE*)_OT1;

	MPBuff[0][1].draw.isbg = 0;
	MPBuff[0][1].disp.isinter = 1;
	MPBuff[0][1].draw.dfe = 1;
	MPBuff[0][1].disp.screen.h = 256;
	MPBuff[0][1].primtab = (char*)_primTab2;
	MPBuff[0][1].primptr = (char*)_primTab2;
	MPBuff[0][1].ot = (OTTYPE*)_OT2;

	last = &MPBuff[0][1];
	current = &MPBuff[0][0];

	MPBuff[0][0].disp.screen.x = draw_mode.framex * 2;
	MPBuff[0][0].disp.screen.y = draw_mode.framey;
	MPBuff[0][1].disp.screen.y = draw_mode.framey;
	MPBuff[0][1].disp.screen.x = MPBuff[0][0].disp.screen.x;

	PutDispEnv(&MPBuff[0][0].disp);
	PutDrawEnv(&current->draw);
}

// [A] - was inlined in State_FrontEnd
void InitFrontend(void)
{
	InitCdIcon();
#ifdef HIRES_FONTS
	InitHiresFEFont();
#endif

	ResetGraph(1);
	SetDispMask(0);

	bRedrawFrontend = 0;
	gInFrontend = 1;

	idle_timer = VSync(-1);

	LoadFrontendScreens(1);

	SetupBackgroundPolys();
	SetupScreenSprts(&PsxScreens[Sc_Main]);

	// load frontend bank
	LoadBankFromLump(SOUND_BANK_SFX, SBK_ID_MENU);
}

// [A] - was inlined in State_FrontEnd
void InitFrontendDisplay(void)
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

// [D] [T]
void State_FrontEnd(void* param)
{
	PadChecks();

	if (currPlayer == 2)
	{
		if (Pads[1].type < 2)
		{
			feNewPad = ((feNewPad & MPAD_TRIANGLE) != 0) ? MPAD_TRIANGLE : 0;
		}
		else 
		{
			feNewPad = Pads[1].mapnew;
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
		DrawSync(0);
		EndFrame();

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

			SetState(STATE_GAMESTART);

			pCurrScreen = pScreenStack[0];

			bRedrawFrontend = 1;
			ScreenDepth = 0; // fail-safe?
		}

		idle_timer = VSync(-1);
	}

	if(bQuitToSystem == 2)
		SetState(STATE_NONE);
}

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

	DrawOTag((u_long*)(db_hold->ot + FE_OTSIZE - 1));

	ClearOTagR((u_long*)current->ot, FE_OTSIZE);
	VSync(0);

#ifndef PSX
	PsyX_EndScene();
#endif
}

// [A]
int FEStringWidth(char* string)
{
	char* pString = string;
	u_char c = 0;
	int w = 0;

#ifdef HIRES_FONTS
	if (gHiresFEFontTexture)
	{
		return FEStringWidthHires(string);
	}
#endif

	while ((c = *pString++) != 0)
	{
		if (c == ' ')
			w += 4;
		else
			w += feFont.CharInfo[c].w;
	}

	return w;
}

// [D] [T]
int FEPrintString(char *string, int x, int y, int justification, int r, int g, int b)
{
	if (current == NULL || string == NULL)
		return -1;

#ifdef HIRES_FONTS
	if (gHiresFEFontTexture)
	{
		return FEPrintStringHires(string, x, y, justification, r, g, b);
	}
#endif

	FE_CHARDATA *pFontInfo;
	SPRT *font;
	u_char let;

	if (justification & 4)
	{
		x -= FEStringWidth(string);
	}

	font = (SPRT*)current->primptr;

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
			setSemiTrans(font, 1);

			setRGB0(font, r, g, b);
			setXY0(font, x, y);
			setUV0(font, pFontInfo->u, pFontInfo->v);
			setWH(font, pFontInfo->w, pFontInfo->h);
			// setTPage(font, 0, 0, 640, 256); // [A]
			setClut(font, 960, 257); // [A] seems clut has a transparency bit; width is 256

			addPrim(current->ot + 1, font);
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

	addPrim(current->ot + 1, null);
	null++;

	current->primptr = (char *)null;

	return x;
}


// [D] [T]
int FEPrintStringSized(char *string, int x, int y, int scale, int transparent, int r, int g, int b)
{
	if (current == NULL || string == NULL)
		return -1;

#ifdef HIRES_FONTS
	if (gHiresFEFontTexture)
	{
		return FEPrintStringSizedHires(string, x, y, scale, transparent, r, g, b);
	}
#endif

	POLY_FT4 *font;
	FE_CHARDATA *pFontInfo;
	u_char let;
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
			setSemiTrans(font, transparent);

			setRGB0(font, 128, 128, 128);
			setUVWH(font, pFontInfo->u, pFontInfo->v, pFontInfo->w - 1, pFontInfo->h - 1);
			setXYWH(font, x, y, w, h);
			setRGB0(font, r, g, b);
			setTPage(font, 0, 0, 640, 256);
			setClut(font, 960, 257); // [A] seems clut has a transparency bit; width is 256

			addPrim(current->ot + 1, font);
			font++;

			// make room for next character
			x += w;
		}
	}

	// set tail
	current->primptr = (char *)font;

	return x;
}


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
		return FN_OK;

#if defined(DEBUG) && !defined(PSX)
	char text[32];

	sprintf(text, "X1: %d, Y1: %d", current->disp.screen.x, current->disp.screen.y);
	FEPrintStringSized(text, 25, 50, 3072, 0, 128, 0, 0);

	sprintf(text, "X2: %d, Y2: %d", last->disp.screen.x, last->disp.screen.y);
	FEPrintStringSized(text, 25, 75, 3072, 0, 128, 0, 0);
#endif

	if (feNewPad & MPAD_CROSS)
	{
		draw_mode_pal.framex = current->disp.screen.x / 2;
		draw_mode_pal.framey = current->disp.screen.y;
		draw_mode_ntsc.framex = current->disp.screen.x / 2;
		draw_mode_ntsc.framey = current->disp.screen.y;
	}
	else if (feNewPad & MPAD_TRIANGLE)
	{
		current->disp.screen.x = draw_mode.framex * 2;
		current->disp.screen.y = draw_mode.framey;
		last->disp.screen.x = draw_mode.framex * 2;
		last->disp.screen.y = draw_mode.framey;
	}
	else
	{
		bool done = false;

		if (feNewPad & MPAD_D_UP)
		{
			if (current->disp.screen.y >= screen_limits[video_mode].miny)
			{
				current->disp.screen.y--;
				last->disp.screen.y--;
				done = true;
			}
		}
		else if (feNewPad & MPAD_D_DOWN)
		{
			if (current->disp.screen.y <= screen_limits[video_mode].maxy)
			{
				current->disp.screen.y++;
				last->disp.screen.y++;
				done = true;
			}
		}
		else if (feNewPad & MPAD_D_LEFT)
		{
			if (current->disp.screen.x >= screen_limits[video_mode].minx)
			{
				current->disp.screen.x--;
				last->disp.screen.x--;
				done = true;
			}
		}
		else if (feNewPad & MPAD_D_RIGHT)
		{
			if (current->disp.screen.x <= screen_limits[video_mode].maxx)
			{
				current->disp.screen.x++;
				last->disp.screen.x++;
				done = true;
			}
		}
		else
		{
			// unhandled button press
			return FN_OK;
		}

		FESound((done) ? 3 : 1);
	}

	return FN_OK;
}

u_char defaultCarColours[] = { 5, 0, 0, 1 };

// [D] [T]
int CarSelectScreen(int bSetup)
{
	int newSel;
	RECT16 rect;

	newSel = carSelection;
	rect = extraRect;

	if (bSetup)
	{
		iScreenSelect = SCREEN_CAR;

		// setup secret cars
		if (NumPlayers == 1)
		{
			CarAvailability[0][9] = AvailableCheats.cheat5;
			CarAvailability[1][9] = AvailableCheats.cheat6;
			CarAvailability[2][9] = AvailableCheats.cheat7;
			CarAvailability[3][9] = AvailableCheats.cheat8;
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

#ifdef PSX
		if (currPlayer != 1) 
			return FN_OK;
#endif

		LoadBackgroundFile("DATA\\CARS\\CARBACK.RAW");

		if (feVariableSave[2] != -1)
		{
			carSelection = feVariableSave[2];
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

		carColour = defaultCarColours[GameLevel]; // special player color

		//feVariableSave[0] = -1;
		//feVariableSave[1] = -1;
		//feVariableSave[2] = -1;
		//feVariableSave[3] = -1;

		lastCutCity = -1;
		currSelIndex = 1;

		pCurrButton = &pCurrScreen->buttons[1];

		return FN_DONE;
	}

	if (feNewPad & MPAD_TRIANGLE)
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
		feVariableSave[2] = carSelection;

		iScreenSelect = SCREEN_NONE;
	}

	else if (feNewPad & MPAD_CROSS)
	{
		if (currSelIndex == 1)
		{
			// select the vehicle
			if (currPlayer == 1)
			{
				feVariableSave[2] = carSelection;
				wantedCar[0] = carNumLookup[GameLevel][carSelection];
				wantedColour[0] = carColour;
			}
			else {
				wantedCar[1] = carNumLookup[GameLevel][carSelection];
				wantedColour[1] = carColour;
			}

			// time for player 2 to select their vehicle?
			if (NumPlayers == 2)
				currPlayer++;

			return FN_OK;
		}
		else
		{
			if (currSelIndex == 0)
			{
				// find best-fit for previous vehicle
				do
				{
					if (--newSel < 0)
						newSel = 9;

				} while (CarAvailability[GameLevel][newSel] == 0);
			}
			else if (currSelIndex == 2)
			{
				// find best-fit for next vehicle
				do
				{
					if (++newSel > 9)
						newSel = 0;

				} while (CarAvailability[GameLevel][newSel] == 0);
			}

			if (newSel != carSelection)
			{
				carSelection = newSel;

				if (carSelection < 4)
					carColour = 0; // cop cars / specials don't have multiple colors
				else
					carColour = defaultCarColours[GameLevel];
			}
		}
		
		rect = extraRect;
		LoadImage(&rect, (u_long *)(_frontend_buffer + carSelection * 0x8000));
		DrawSync(0);

#ifdef PSX
		DisplayOnScreenText();

		addPrim(current->ot + 2, &extraSprt);
		addPrim(current->ot + 2, &extraDummy);

		EndFrame();
#endif
	}
	else if (feNewPad & MPAD_D_UP)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (feNewPad & MPAD_D_DOWN)
	{
		currSelIndex = pCurrButton->d - 1;
	}
	else if (carSelection < 4)
	{
		if (feNewPad & MPAD_L1)
		{
			if (--carColour < 0)
				carColour = 5;
			FESound(3);
		}
		else if (feNewPad & MPAD_R1)
		{
			if (++carColour > 5)
				carColour = 0;
			FESound(3);
		}
	}
	else
	{
		if (feNewPad & (MPAD_L1 | MPAD_R1))
		{
			// can't change colors
			FESound(1);
		}
	}

	return FN_OK;
}

// [D] [T]
int CopDiffLevelScreen(int bSetup)
{
	if (bSetup) 
	{
		pCurrButton = &pCurrScreen->buttons[gCopDifficultyLevel];
		return FN_DONE;
	}

	if (feNewPad & MPAD_CROSS)
	{
		gCopDifficultyLevel = currSelIndex;
	}
	else if (feNewPad & MPAD_D_UP)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (feNewPad & MPAD_D_DOWN)
	{
		currSelIndex = pCurrButton->d - 1;
	}

	return FN_OK;
}

// [D] [T]
int VibroOnOffScreen(int bSetup)
{
	if (bSetup) 
	{
		currSelIndex = (gVibration ^ 1);
		pCurrButton = &pCurrScreen->buttons[currSelIndex];
		return FN_DONE;
	}

	if (feNewPad & MPAD_CROSS)
	{
		gVibration = (currSelIndex ^ 1);
	}
	else if (feNewPad & MPAD_D_UP)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (feNewPad & MPAD_D_DOWN)
	{
		currSelIndex = pCurrButton->d - 1;
	}

	return FN_OK;
}


// [D] [T]
int MissionSelectScreen(int bSetup)
{
	int i;

	if (bSetup) 
	{
		iScreenSelect = SCREEN_MISSION;

		if (!missionSetup)
		{
			currMission = minmaxSelections[currCity][0];
			currSelIndex = 0;

			if (GameType == GAME_REPLAYMISSION)
				LoadBackgroundFile("DATA\\CITYBACK.RAW");
		}

		if (feVariableSave[0] != -1) 
		{
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
				currMission + i >= minmaxSelections[currCity][1] ||
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
			sprintf(pCurrScreen->buttons[1].Name, GET_MISSION_TXT(MissionName[currMission]));
			sprintf(pCurrScreen->buttons[2].Name, NullStr);
			sprintf(pCurrScreen->buttons[3].Name, NullStr);
			sprintf(pCurrScreen->buttons[4].Name, NullStr);
			break;
		case 2:
			pCurrScreen->buttons[1].u = 3;
			pCurrScreen->buttons[1].d = 3;
			pCurrScreen->buttons[2].u = 2;
			pCurrScreen->buttons[2].d = 2;
			sprintf(pCurrScreen->buttons[1].Name, GET_MISSION_TXT(MissionName[currMission]));
			sprintf(pCurrScreen->buttons[2].Name, GET_MISSION_TXT(MissionName[currMission + 1]));
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
			sprintf(pCurrScreen->buttons[1].Name, GET_MISSION_TXT(MissionName[currMission]));
			sprintf(pCurrScreen->buttons[2].Name, GET_MISSION_TXT(MissionName[currMission + 1]));
			sprintf(pCurrScreen->buttons[3].Name, GET_MISSION_TXT(MissionName[currMission + 2]));
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
			sprintf(pCurrScreen->buttons[1].Name, GET_MISSION_TXT(MissionName[currMission]));
			sprintf(pCurrScreen->buttons[2].Name, GET_MISSION_TXT(MissionName[currMission + 1]));
			sprintf(pCurrScreen->buttons[3].Name, GET_MISSION_TXT(MissionName[currMission + 2]));
			sprintf(pCurrScreen->buttons[4].Name, GET_MISSION_TXT(MissionName[currMission + 3]));
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
				pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_HIDDEN, 0);
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
				pCurrScreen->buttons[5].action = FE_MAKEVAR(BTN_HIDDEN, 0);
			}
			else
			{
				// list missions only
				pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_HIDDEN, 0);
				pCurrScreen->buttons[5].action = FE_MAKEVAR(BTN_HIDDEN, 0);
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

		return FN_DONE;
	}

	if (feNewPad & MPAD_CROSS)
	{
		i = currMission;

		if (currSelIndex == 0)
		{
			i -= 4;

			if (i < minmaxSelections[currCity][0])
				return FN_OK;
		}
		else if (currSelIndex == 5)
		{
			i += 4;

			if (i > minmaxSelections[currCity][1] || i > gFurthestMission)
				return FN_OK;
		}
		else
		{
			bReturnToMain = 0;
			GameType = GAME_REPLAYMISSION;
			feVariableSave[0] = currMission;
			feVariableSave[1] = currSelIndex;
			feVariableSave[2] = currCity;
			gCurrentMissionNumber = botch[currMission + (currSelIndex - 1)].missNum;

			return FN_OK;
		}

		currMission = i;
		FESound(3);
		FE_INIT_SCREEN(pCurrScreen);
		bRedrawFrontend = 1;

		return FN_DONE;
	}
	else if (feNewPad & MPAD_TRIANGLE)
	{
		missionSetup = 0;
		iScreenSelect = SCREEN_NONE;
	}
	else if (feNewPad & MPAD_D_UP)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (feNewPad & MPAD_D_DOWN)
	{
		currSelIndex = pCurrButton->d - 1;
	}

	return FN_OK;
}

// [D] [T]
int MissionCityScreen(int bSetup)
{
	RECT16 rect;

	if (bSetup)
	{
		GameType = GAME_MISSION;

		if (gFurthestMission == 0)
		{
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		else if (gFurthestMission < 10)
		{
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		else if (gFurthestMission < 21)
		{
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		else if (gFurthestMission < 31)
		{
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		else
		{
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MissionSelect);
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

		return FN_OK;
	}

	if (feNewPad & MPAD_TRIANGLE)
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
		if (feNewPad & MPAD_D_UP)
		{
			currCity = pCurrButton->u - 1;
		}
		else if (feNewPad & MPAD_D_DOWN)
		{
			currCity = pCurrButton->d - 1;
		}
		else
		{
			currCity = pCurrButton->u & 3;
			return FN_OK;
		}

		rect = extraRect;
		LoadImage(&rect, (u_long *)(_frontend_buffer + currCity * 0x8000));
		DrawSync(0);

#ifdef PSX
		DisplayOnScreenText();

		addPrim(current->ot + 2, &extraSprt);
		addPrim(current->ot + 2, &extraDummy);

		EndFrame();
#endif
	}
	
	return FN_OK;
}

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
			LoadImage(&rect, (u_long*)(_frontend_buffer + 0x20000 + cutSelection * 0x8000));
			DrawSync(0);
		}
		else
		{
			SetupExtraPoly(cutGfxNames[GameLevel], cutSelection, 0x20000);
		}

		currSelIndex = 1;

		iScreenSelect = SCREEN_CUTSCENE;

		pCurrButton = pCurrScreen->buttons + 1;

		return FN_DONE;
	}

	if (feNewPad & MPAD_TRIANGLE)
	{
		bDrawExtra = 0;
		iScreenSelect = SCREEN_NONE;
	}
	else if (feNewPad & MPAD_CROSS)
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
				SetState(STATE_FMVPLAY, (void*)(feVariableSave[0] + CutAmountsTotal[feVariableSave[1]] + 1));

				return FN_DONE;
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

		addPrim(current->ot + 2, &extraSprt);
		addPrim(current->ot + 2, &extraDummy);

		EndFrame();
#endif

		return FN_OK;
	}
	else if (feNewPad & MPAD_D_UP)
	{
		currSelIndex = pCurrButton->u - 1;
	}
	else if (feNewPad & MPAD_D_DOWN)
	{
		currSelIndex = pCurrButton->d - 1;
	}

	return FN_OK;
}



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
			if (iScreenSelect == SCREEN_NONE)
				iScreenSelect = SCREEN_CUTCITY;
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
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		else if (gFurthestMission < 10)
		{
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		else if (gFurthestMission < 21)
		{
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_DISABLED, 0);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		else if (gFurthestMission < 31) 
		{
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		else 
		{
			pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CutSceneSelect);

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

		return FN_OK;
	}

	if (feNewPad & MPAD_CROSS)
	{
		lastCity = -1;
		lastCutCity = GameLevel;

		if (GameLevel == 4)
		{
			bReturnToMain = 0;

			pScreenStack[ScreenDepth] = pCurrScreen;
			pButtonStack[ScreenDepth] = pCurrButton;

			ScreenNames[ScreenDepth] = pCurrButton->Name;

			feVariableSave[0] = currCity;

			SetState(STATE_FMVPLAY, (void*)96);
			return FN_DONE;
		}
		else
		{
			lastCity = -1;
		}

		return FN_OK;
	}
	else if (feNewPad & MPAD_TRIANGLE)
	{
		FESound(0);
		bDoneAllready = 1;
		LoadBackgroundFile("DATA\\GFX.RAW");
		iScreenSelect = SCREEN_NONE;
		bDrawExtra = 0;

		return FN_OK;
	}
	else if (feNewPad & MPAD_D_UP)
	{
		currCity = pCurrButton->u - 1;
	}
	else if (feNewPad & MPAD_D_DOWN)
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

	addPrim(current->ot + 2, &extraSprt);
	addPrim(current->ot + 2, &extraDummy);

	EndFrame();
#endif

	return FN_OK;
}



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

		return FN_OK;
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

	if (feNewPad & MPAD_TRIANGLE)
	{
		FESound(0);
		bDoneAllready = 1;

		gMasterVolume = masterVolumeHold;
		gMusicVolume = musicVolumeHold;

		LoadBackgroundFile("DATA\\GFX.RAW");

		SetMasterVolume(gMasterVolume);
		SetXMVolume(gMusicVolume);

		return FN_OK;
	}
	else if (feNewPad & MPAD_CROSS)
	{
		if (currSelIndex == 2)
			LoadBackgroundFile("DATA\\GFX.RAW");

		return FN_OK;
	}
	else
	{
		int dir = -1; // -1: no action, 0: limit reached, 1: OK

		if (fePad & MPAD_D_LEFT)
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
		else if (fePad & MPAD_D_RIGHT)
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
		return FN_DONE;
#endif
	}

	return FN_OK;
}

int GameNum = 0;
CVECTOR scoreCol = { 120, 120, 120 };
CVECTOR otherCol = {125, 115, 34};

// [D] [T]
void DisplayScoreTable(void)
{
	static char* CityNames[4] = {
		M_LTXT(MTXT_Chicago),
		M_LTXT(MTXT_Havana),
		M_LTXT(MTXT_LasVegas),
		M_LTXT(MTXT_RioDeJaneiro)
	};

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
	FEPrintStringSized(text, 280, 206, 3072, 2, otherCol.r, otherCol.g, otherCol.b);

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
		FEPrintStringSized(text, 420, 206, 3072, 2, otherCol.r, otherCol.g, otherCol.b);
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


// [D] [T]
int ScoreScreen(int bSetup)
{
	if (bSetup)
	{
		GameLevel = 0;

		DisplayScoreTable();

		iScreenSelect = SCREEN_SCORES;
		currSelIndex = 0;

		return FN_OK;
	}

	if (feNewPad & MPAD_CROSS)
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

				if (GameNum == 1)
				{
					if (--GameLevel < 0)
						GameLevel = 3;
				}
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

				if (GameNum == 0)
				{
					if (++GameLevel > 3)
						GameLevel = 0;
				}
			}
		}

#ifdef PSX
		DisplayScoreTable();
		bRedrawFrontend = 1;
#endif
	}
	else if (feNewPad & MPAD_TRIANGLE)
	{
		iScreenSelect = SCREEN_NONE;
		return FN_OK;
	}
	else if ((feNewPad & MPAD_D_UP) || (feNewPad & MPAD_D_DOWN))
	{
		currSelIndex ^= 1;
	}

#ifndef PSX
	DisplayScoreTable();
#endif

	return FN_OK;
}

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

		return FN_DONE;
	}
	return FN_OK;
}


// [D] [T]
int CityCutOffScreen(int bSetup)
{
	if (bSetup)
	{
		if (gFurthestMission < 20)
			pCurrScreen->buttons[2].action = FE_MAKEVAR(BTN_DISABLED, 0);

		if (gFurthestMission < 29)
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);

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
		return FN_OK;
	}

#ifndef PSX
	/*
	if ((fePad & MPAD_CROSS) != 0)
	{
		lastCity = currCity;

		bDrawExtra = 0;

		LoadBackgroundFile("DATA\\GFX.RAW");
		loaded[0] = -1;

		return FN_OK;
	}*/

	if (feNewPad & MPAD_TRIANGLE)
	{
		lastCity = -1;

		bDrawExtra = 0;
		FESound(0);
		bDoneAllready = 1;

		LoadBackgroundFile("DATA\\GFX.RAW");
		loaded[0] = -1;

		return FN_OK;
	}
	else if (feNewPad & MPAD_D_UP)
	{
		currCity = pCurrButton->u - 1;
	}
	else if (feNewPad & MPAD_D_DOWN)
	{
		currCity = pCurrButton->d - 1;
	}
	else
	{
		currCity = pCurrButton->u & 3;
		return FN_OK;
	}

	RECT16 rect = extraRect;
	LoadImage(&rect, (u_long *)(_frontend_buffer + currCity * 0x8000));
	DrawSync(0);
#endif
	return FN_OK;
}


char* contNames[2] = {
	"DATA\\CARCONT.RAW",
	"DATA\\TANCONT.RAW"
};

// [D] [T]
int ControllerScreen(int bSetup)
{
	if (bSetup ) 
	{
		iScreenSelect = SCREEN_SCORES;
		currSelIndex = 0;
		pCurrScreen->numButtons = 0;

		LoadBackgroundFile(contNames[currSelIndex]);
	}
	else
	{
		if (feNewPad & MPAD_CROSS)
		{
			currSelIndex = currSelIndex ^ 1;
			LoadBackgroundFile(contNames[currSelIndex]);

			bRedrawFrontend = 1;
		}
		else if (feNewPad & MPAD_TRIANGLE)
		{
			iScreenSelect = SCREEN_SCORES;
			LoadBackgroundFile("DATA\\GFX.RAW");
		}
	}

	return FN_OK;
}

// [D] [T]
int MainScreen(int bSetup)
{
	if (bSetup) 
	{
		if (numPadsConnected == 2) 
		{
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_Multiplayer);
		}
		else 
		{
			pCurrScreen->buttons[3].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
	}

	return FN_OK;
}

static char* cheatText[] =
{
	G_LTXT_ID(GTXT_NoSecrets),
	G_LTXT_ID(GTXT_MountainTrack),
	G_LTXT_ID(GTXT_Circuit),
	G_LTXT_ID(GTXT_Invincibility),
	G_LTXT_ID(GTXT_Immunity),
	G_LTXT_ID(GTXT_MiniCars),		// [A]
	G_LTXT_ID(GTXT_BonusGallery)	// [A]
};

// [D] [T]
int CheatScreen(int bSetup)
{
	int i;
	int numOpen;
	int k;
	unsigned char cheatOn[12];
	int evilRuss[6];

	int hackLookup1[6] = {
		FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_RaceMode),
		FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_RaceMode),
		FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_InvincibleOnOff),
		FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_ImmunityOnOff),
		FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_MiniCarsOnOff),
		0,
	};

	int hackLookup2[6] = {
		FE_MAKEVAR(VAR_MINIGAME, 1),
		FE_MAKEVAR(VAR_MINIGAME, 0),
		-1,
		-1,
		-1,
		FE_MAKEVAR(VAR_BONUS_GALLERY, 0),
	};

	if (bSetup == 0)
	{
		return FN_OK;
	}

	if (gFurthestMission == 40) 
		numOpen = 4 + ENABLE_BONUS_CONTENT * 2;	// [A] now 5 elements as "Bonus gallery" is open
	else 
		numOpen = AvailableCheats.cheat1 + AvailableCheats.cheat2 + AvailableCheats.cheat3 + AvailableCheats.cheat4;
	
	// "Sorry no secrets"
	if (numOpen == 0)
	{
		pCurrScreen->numButtons = 1;
		
		pCurrScreen->buttons[0].u = 1;
		pCurrScreen->buttons[0].d = 1;
		pCurrScreen->buttons[0].action = FE_MAKEVAR(BTN_PREVIOUS_SCREEN, 0);

		sprintf(pCurrScreen->buttons[0].Name, GET_GAME_TXT(cheatText[0]));

		return FN_OK;
	}

	pCurrScreen->numButtons = numOpen;

	evilRuss[0] = AvailableCheats.cheat1;
	evilRuss[1] = AvailableCheats.cheat2;
	evilRuss[2] = AvailableCheats.cheat3;
	evilRuss[3] = AvailableCheats.cheat4;
	evilRuss[4] = 0;
	evilRuss[5] = 0;

	if (numOpen >= 6)
	{
		pCurrScreen->buttons[4] = pCurrScreen->buttons[3];
		pCurrScreen->buttons[5] = pCurrScreen->buttons[3];
	}

	k = 0;

	for (i = 0; i < 6; i++)
	{
		if (evilRuss[i] || gFurthestMission == 40)
		{
			sprintf(pCurrScreen->buttons[i].Name, GET_GAME_TXT(cheatText[i + 1]));
			cheatOn[k++] = i;
		}
	}

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
	
		return FN_OK;
	}

	if (numOpen == 1)
	{
		pCurrScreen->buttons[0].action = hackLookup1[cheatOn[0]];
		pCurrScreen->buttons[0].var = hackLookup2[cheatOn[0]];
		pCurrScreen->buttons[0].d = 1;
		pCurrScreen->buttons[0].u = 1;
		
		currSelIndex = 0;
	
		return FN_OK;
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
		return FN_OK;
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

		// [A] adding bonus gallery
		if(numOpen >= 5)
		{
			pCurrScreen->buttons[4].action = hackLookup1[cheatOn[4]];
			pCurrScreen->buttons[4].var = hackLookup2[cheatOn[4]];
			pCurrScreen->buttons[4].y += 40;
			pCurrScreen->buttons[4].s_y += 40;

			pCurrScreen->buttons[0].u = 5;
			pCurrScreen->buttons[3].d = 5;
			
			pCurrScreen->buttons[4].d = 1;
			pCurrScreen->buttons[4].u = 4;
		}

		// [A] adding mini cars cheat
		if (numOpen >= 6)
		{
			pCurrScreen->buttons[5].action = hackLookup1[cheatOn[5]];
			pCurrScreen->buttons[5].var = hackLookup2[cheatOn[5]];
			pCurrScreen->buttons[5].y += 80;
			pCurrScreen->buttons[5].s_y += 80;

			pCurrScreen->buttons[0].u = 6;
			pCurrScreen->buttons[4].d = 6;

			pCurrScreen->buttons[5].d = 1;
			pCurrScreen->buttons[5].u = 5;
		}

		currSelIndex = 0;
		return FN_OK;
	}

	pCurrScreen->numButtons = 0;
	currSelIndex = 0;

	return FN_OK;
}


// [D] [T]
int ImmunityOnOffScreen(int bSetup)
{
	if (bSetup)
	{
		if (gPlayerImmune == 0)
			pCurrButton = pCurrScreen->buttons + 1;
		else
			pCurrButton = pCurrScreen->buttons;
		return FN_DONE;
	}

	return FN_OK;
}

// [D] [T]
int InvincibleOnOffScreen(int bSetup)
{
	if (bSetup)
	{
		if (gInvincibleCar == 0) 
			pCurrButton = pCurrScreen->buttons + 1;
		else 
			pCurrButton = pCurrScreen->buttons;

		return FN_DONE;
	}
	return FN_OK;
}

int MiniCarsOnOffScreen(int bSetup)
{
	if (bSetup)
	{
		if (ActiveCheats.cheat13 == 0)
			pCurrButton = pCurrScreen->buttons + 1;
		else
			pCurrButton = pCurrScreen->buttons;

		return FN_DONE;
	}
	return FN_OK;
}

// [D] [T]
int GamePlayScreen(int bSetup)
{
	if (bSetup)
	{
		pCurrScreen->buttons[2].action = (allowVibration == 0) ? FE_MAKEVAR(BTN_DISABLED, 0) : FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_VibrationOnOff);
	}

	return FN_OK;
}

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

	return FN_OK;
}
// [D] [T]
int CheatNumlayerSelect(int bSetup)
{
	if (bSetup) 
	{
		if (numPadsConnected == 2) 
		{
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_RaceSelect);
		}
		else 
		{
			pCurrScreen->buttons[1].action = FE_MAKEVAR(BTN_DISABLED, 0);
		}
		return FN_OK;
	}
	return FN_OK;
}

int BuildButtonsVertical(FE_SCREEN *screen, int count, int xStart, int yStart)
{
	int numButtons = count;

	if (numButtons > 8)
		numButtons = 8;

	for (int i = 0; i < numButtons; i++)
	{
		int prevButton = i - 1;
		int nextButton = i + 1;

		if (prevButton < 0)
			prevButton += numButtons;

		if (nextButton >= numButtons)
			nextButton -= numButtons;

		FE_BUTTON& btn = screen->buttons[i];

		// copy button 0
		btn = PsxScreens[Sc_Replays].buttons[0];

		btn.u = prevButton + 1;
		btn.d = nextButton + 1;

		btn.l = 0;//i + 1;
		btn.r = 0;//i + 1;

		btn.s_x = xStart + 200;
		btn.s_y = yStart + i * 38;

		btn.x = xStart;
		btn.y = yStart + i * 38;

		btn.action = 0;

		btn.var = i;

		sprintf(btn.Name, "Button %d", i + 1);
	}

	screen->numButtons = numButtons;

	return numButtons;
}

#ifndef PSX
#include "../utils/fs.h"
#define MAX_REPLAY_NAME_LENGTH 48
char gFEReplayList[8][MAX_REPLAY_NAME_LENGTH];
int gFEReplayCount = 0;
#endif

int UserReplaySelectScreen(int bSetup)
{
#ifndef PSX
	if (bSetup)
	{
		FS_FINDDATA* fd;
		const char* filename;
		const char* tmp;

		gFEReplayCount = 0;
		fd = NULL;
		filename = FS_FindFirst("Replays/*.D2RP", &fd);

		while (filename)
		{
			strncpy(gFEReplayList[gFEReplayCount], filename, MAX_REPLAY_NAME_LENGTH);
			tmp = strchr(filename, '.');
			gFEReplayList[gFEReplayCount][MAX_REPLAY_NAME_LENGTH-1] = 0;

			gFEReplayCount++;
			filename = FS_FindNext(fd);

			// [A] don't load more than 8
			if (gFEReplayCount >= 8)
				break;
		}

		FS_FindClose(fd);

		if (gFEReplayCount)
		{
			int yOfs = 170;

			if (gFEReplayCount < 6)
				yOfs = 208;

			int numButtons = BuildButtonsVertical(pCurrScreen, gFEReplayCount, 160, yOfs);

			for (int i = 0; i < numButtons; i++)
			{
				FE_BUTTON& btn = pCurrScreen->buttons[i];
				strncpy(btn.Name, gFEReplayList[i], sizeof(btn.Name));

				tmp = strchr(btn.Name, '.');

				if (tmp)
					btn.Name[tmp - btn.Name] = 0;
				else
					btn.Name[15] = 0;
			}
		}
		else
		{
			BuildButtonsVertical(pCurrScreen, 1, 160, 208);

			FE_BUTTON& btn = pCurrScreen->buttons[0];
			btn.action = FE_MAKEVAR(BTN_PREVIOUS_SCREEN, 0);
			strcpy(btn.Name, G_LTXT(GTXT_NoSavedData));
		}

		return FN_OK;
	}

	if (gFEReplayCount)
	{
		if (feNewPad & MPAD_CROSS)
		{
			char filename[64];
			int selectedReplay = pCurrButton->var;

			sprintf(filename, "Replays/%s", gFEReplayList[selectedReplay]);

			if (LoadReplayFromFile(filename))
			{
				StoredGameType = GameType;
				GameType = GAME_LOADEDREPLAY;
				SetState(STATE_GAMESTART);
			}
			else
			{
				SetState(STATE_INITFRONTEND);
			}
		}
	}
#endif

	return FN_OK;
}

char* TimeOfDayItems[] = {
	G_LTXT_ID(GTXT_TimeOfDay),
	G_LTXT_ID(GTXT_Condition),
	G_LTXT_ID(GTXT_Continue),
};

int TimeOfDaySelectScreen(int bSetup)
{
	int numButtons, i;
	int dir;
	char text[64];
	int ypos[2] = { 208, 246 };

	if (bSetup)
	{
		// setup time we want to reset it
		if (feVariableSave[0] == -1)
		{
			wantedTimeOfDay = TIME_DAY;
			wantedWeather = 0;
		}
		else
		{
			wantedTimeOfDay = feVariableSave[0];
			wantedWeather = feVariableSave[1];
		}

		numButtons = BuildButtonsVertical(pCurrScreen, 3, 168, 208);

		for (i = 0; i < numButtons; i++)
		{
			FE_BUTTON& btn = pCurrScreen->buttons[i];
			sprintf(btn.Name, "%s%c", GET_GAME_TXT(TimeOfDayItems[i]), i == 2 ? 0 : ':');

			if (i == 2)
			{
				btn.y += 32;
				btn.s_y += 32;
				btn.action = FE_MAKEVAR(BTN_NEXT_SCREEN, Sc_CarSelect);
#ifndef PSX
				btn.cR = 124;
				btn.cG = 108;
				btn.cB = 40;
#endif
			}
			else
			{
				btn.x -= 50;
				btn.l = btn.r = i + 1;
#ifndef PSX
				btn.cR = 124;
				btn.cG = 76;
				btn.cB = 20;
#endif
			}
		}

		pCurrButton = &pCurrScreen->buttons[2];
		iScreenSelect = SCREEN_TIMEOFDAY;

		return FN_DONE;
	}

	//FEPrintString(GET_GAME_TXT(TimeOfDayNames[wantedTimeOfDay]), 590, ypos[0], 4, 128, 128, 128);
	//FEPrintString(GET_GAME_TXT(WeatherNames[wantedWeather]), 590, ypos[1], 4, 128, 128, 128);

	if (feNewPad & MPAD_TRIANGLE)
	{
		// reset back
		wantedTimeOfDay = -1;
		wantedWeather = -1;

		feVariableSave[3] = -1;
		feVariableSave[2] = -1;
		feVariableSave[1] = -1;
		feVariableSave[0] = -1;

		iScreenSelect = SCREEN_NONE;

		return FN_OK;
	}

	dir = 0;

	if (feNewPad & MPAD_D_LEFT)
	{
		dir = -1;
	}
	else if (feNewPad & (MPAD_D_RIGHT | MPAD_CROSS))
	{
		dir = 1;
	}

	if (dir != 0)
	{
		i = pCurrButton - pCurrScreen->buttons;

		if (i == 0)
		{
			wantedTimeOfDay += dir;
			wantedTimeOfDay &= 3;
			feVariableSave[0] = wantedTimeOfDay;

			gWantNight = wantedTimeOfDay == TIME_DUSK || wantedTimeOfDay == TIME_NIGHT;
		}
		else if (i == 1)
		{
			wantedWeather += dir;
			if (wantedWeather < 0)
				wantedWeather += 3;
			else if (wantedWeather >= 3)
				wantedWeather -= 3;
			feVariableSave[1] = wantedWeather;
		}
	}

	return FN_OK;
}

int DemoScreen(int bSetup)
{
	if (bSetup)
		return FN_OK;
	
	if (feNewPad & MPAD_CROSS)
	{
		pScreenStack[ScreenDepth] = pCurrScreen;
		pButtonStack[ScreenDepth] = pCurrButton;
		
		FESound(2);
		GameType = GAME_PURSUIT;
	
		GameLevel = 1;
		gWantNight = 0;
		gSubGameNumber = 0;
		
		SetState(STATE_GAMESTART);
		
		return FN_OK;
	}

	if(mainScreenLoaded)
	{
		if (feNewPad & MPAD_CIRCLE)
		{
			LoadBackgroundFile(contNames[0]);
			FESound(2);
		}
	}
	else if(bQuitToSystem)
	{
		bQuitToSystem = 0;
		LoadBackgroundFile("DATA\\GFX.RAW");
	}

	return FN_OK;
}

#ifndef PSX
int ChooseOptionScreen(int bSetup)
{
	if (bSetup)
	{
		int numButtons = pCurrScreen->numButtons;
		int defaultValue = -1;
		int what = -1;

		FE_BUTTON *extraBtn = NULL;
		FE_BUTTON *resetBtn = NULL;

		// create buttons
		if (choose_mode == 1)
		{
			// build buttons
			numButtons = BuildButtonsVertical(pCurrScreen, choose_count, 161, 245);

			for (int i = 0; i < numButtons; i++)
			{
				FE_BUTTON& btn = pCurrScreen->buttons[i];
				strcpy(btn.Name, choose_items[i]);

				btn.action = FE_MAKEVAR(BTN_PREVIOUS_SCREEN, 0);
				btn.var = FE_MAKEVAR(VAR_CHOOSE_VALUE, i);

				btn.y += (i * 8);
				btn.s_y += (i * 8);
			}

			if (choose_custom)
			{
				int value = *choose_custom;

				if (value >= 0)
				{
					extraBtn = InsertButtonVertical(pCurrScreen, numButtons, G_LTXT(GTXT_Custom));

					if (extraBtn != NULL)
					{
						what = numButtons++;
						extraBtn->action = FE_MAKEVAR(BTN_PREVIOUS_SCREEN, 0);
						extraBtn->var = FE_MAKEVAR(VAR_CHOOSE_VALUE, what);
						choose_count++;
					}
				}
			}
		}
		else if (choose_mode == 0)
		{
			choose_count = numButtons;
		}

		if (choose_default)
		{
			defaultValue = *choose_default;

			if (defaultValue >= 0)
			{
				resetBtn = InsertButtonVertical(pCurrScreen, numButtons, G_LTXT(GTXT_ResetToDefault));

				if (resetBtn != NULL)
				{
					resetBtn->cR = 124;
					resetBtn->cG = 108;
					resetBtn->cB = 40;

					resetBtn->action = FE_MAKEVAR(BTN_PREVIOUS_SCREEN, 0);
					resetBtn->var = FE_MAKEVAR(VAR_CHOOSE_VALUE, 255);

					resetBtn->y += 16;
					resetBtn->s_y += 16;

					numButtons++;
				}
			}
		}

		if (numButtons > 5)
		{
			for (int i = 0; i < numButtons; i++)
			{
				FE_BUTTON& btn = pCurrScreen->buttons[i];

				btn.y -= 32;
				btn.s_y -= 32;
			}
		}

		if (choose_value)
		{
			int value = *choose_value;

			if (value != 0)
			{
				what = value - 1;

				if (defaultValue >= 0 && what == defaultValue)
				{
					if (resetBtn)
						resetBtn->action = FE_MAKEVAR(BTN_DISABLED, 0);
				}
			}
		}

		if (choose_mode == 0)
		{
			if (what > choose_count)
			{
				// does not exist!
				what = choose_count - 1;
				choose_error = 1;
			}
		}
		else if (what == -1)
		{
			if (defaultValue >= 0)
				what = defaultValue;
		}

		if (what == -1)
			what = choose_count - 1;
		
		for (int i = 0; i < numButtons; i++)
		{
			FE_BUTTON &btn = pCurrScreen->buttons[i];

			int code = (btn.var >> 8);
			int value = (btn.var & 0xff);

			if (code == VAR_CHOOSE_VALUE && value == what)
			{
				pCurrButton = &pCurrScreen->buttons[i];
				return FN_DONE;
			}
		}

		pCurrButton = &pCurrScreen->buttons[0];
		choose_error = 1;

		return FN_DONE;
	}

	return FN_OK;
}
#endif