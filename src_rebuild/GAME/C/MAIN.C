#include "THISDUST.H"
#include "MAIN.H"

#include "LIBETC.H"
#include "LIBSPU.H"
#include "LIBGPU.H"
#include "LIBMCRD.H"

#include "../ASM/ASMTEST.H"
#include "SYSTEM.H"
#include "PAD.H"
#include "SOUND.H"
#include "FMVPLAY.H"
#include "E3STUFF.H"
#include "GAMESND.H"
#include "SCORES.H"
#include "GLAUNCH.H"
#include "LOADVIEW.H"
#include "REPLAYS.H"
#include "EVENT.H"
#include "MISSION.H"
#include "CUTSCENE.H"
#include "TEXTURE.H"
#include "SKY.H"
#include "PRES.H"
#include "DRAW.H"
#include "DENTING.H"
#include "COSMETIC.H"
#include "PEDEST.H"
#include "SPOOL.H"
#include "MAP.H"
#include "OBJANIM.H"
#include "HANDLING.H"
#include "DRIVINGGAMES.H"
#include "BOMBERMAN.H"
#include "PLAYERS.H"
#include "AI.H"
#include "CIV_AI.H"
#include "COP_AI.H"
#include "CAMERA.H"
#include "EVENT.H"
#include "OVERLAY.H"
#include "DEBRIS.H"
#include "JOB_FX.H"
#include "DIRECTOR.H"
#include "CONVERT.H"
#include "TILE.H"
#include "OVERMAP.H"
#include "MOTION_C.H"
#include "DR2ROADS.H"
#include "MODELS.H"
#include "CARS.H"
#include "GLAUNCH.H"

#include "XAPLAY.H"
#include "SHADOW.H"

#include "PAUSE.H"

#include <stdlib.h>

#include "../FRONTEND/FEMAIN.H"

int scr_z = 0;

int levelstartpos[8][4] = {
	{ 0x12B1, 0xFFFFFC00, 0xFFFC9794, 0},
	{ 0xFFFC74AC, 0x800, 0xFFFC6961, 0},
	{ 0x383CB, 0xFFFFFC00, 0xABE1E, 0},
	{ 0x165EF, 0xFFFFFC00, 0xFFFAB3D9, 0},
	{ 0x24548, 0x1813, 0xFFFE4A80, 0},
	{ 0xFFFD67F0, 0x1813, 0x58228, 0},
	{ 0xFFFFD6FC, 0xFFFFE7ED, 0xFFFFA980, 0},
	{ 0xFFFFDCDD, 0xFFFFE7ED, 0xF8A7, 0},
};

enum LevLumpType
{
	// known lumps indexes
	LUMP_MODELS				= 1,		// level models
	LUMP_MAP				= 2,		// map info

	LUMP_TEXTURENAMES		= 5,		// texture name strings

	LUMP_ROADMAP			= 7,		// unused lump in Driver 2
	LUMP_ROADS				= 8,		// unused lump in Driver 2
	LUMP_JUNCTIONS			= 9,		// unused lump in Driver 2
	LUMP_ROADSURF			= 10,		// unused lump in Driver 2

	LUMP_MODELNAMES			= 12,		// model name strings

	LUMP_ROADBOUNDS			= 16,		// unused lump in Driver 2
	LUMP_JUNCBOUNDS			= 17,		// unused lump in Driver 2

	LUMP_SUBDIVISION		= 20,		
	LUMP_LOWDETAILTABLE		= 21,		// LOD tables for models
	LUMP_MOTIONCAPTURE		= 22,		// motion capture/animation data for peds and Tanner
	LUMP_OVERLAYMAP			= 24,		// overlay map
	LUMP_PALLET				= 25,		// car palettes
	LUMP_SPOOLINFO			= 26,		// level region spooling
	LUMP_CAR_MODELS			= 28,		// car models

	LUMP_CHAIR				= 33,
	LUMP_TEXTUREINFO		= 34,		// texture page info and details (atlases)

	LUMP_LEVELDESC			= 35,
	LUMP_LEVELDATA			= 36,
	LUMP_LUMPDESC			= 37,

	LUMP_STRAIGHTS2			= 40,		// road straights (AI)
	LUMP_CURVES2			= 41,

	LUMP_JUNCTIONS2			= 42,		// previously LUMP_JUNCTIONS2
	LUMP_JUNCTIONS2_NEW		= 43,		// Only appear in release Driver2
};

REPLAY_STREAM ReplayStreams[8];

int HitLeadCar = 0;
int game_over = 0;
int saved_counter = 0;
int saved_leadcar_pos = 0;
int gStopPadReads = 0;
int DawnCount = 0;
int variable_weather = 0;
int current_camera_angle = 0x800;
int gDieWithFade = 0;

int FrameCnt = 0x78654321;	// wait for CD sync?

unsigned char defaultPlayerModel[2] = { 0 }; // offset 0xAA604
unsigned char defaultPlayerPalette = 0; // offset 0xAA606


// decompiled code
// original method signature: 
// void /*$ra*/ ProcessLumps(char *lump_ptr /*$s1*/, int lump_size /*$a1*/)
 // line 2672, offset 0x00058c08
	/* begin block 1 */
		// Start line: 2673
		// Start offset: 0x00058C08
		// Variables:
	// 		int quit; // $s3
	// 		int lump_type; // $v1
	// 		int seg_size; // $s0

		/* begin block 1.1 */
			// Start line: 2686
			// Start offset: 0x00058D94

			/* begin block 1.1.1 */
				// Start line: 2845
				// Start offset: 0x00058F7C
				// Variables:
			// 		struct DRIVER2_JUNCTION *dst; // $a0
			// 		unsigned long *src; // $a2
			// 		int i; // $v1
			/* end block 1.1.1 */
			// End offset: 0x00058FC4
			// End Line: 2858

			/* begin block 1.1.2 */
				// Start line: 2865
				// Start offset: 0x00058FCC
				// Variables:
			// 		struct DRIVER2_JUNCTION *dst; // $a0
			// 		unsigned long *src; // $a2
			// 		int i; // $v1
			/* end block 1.1.2 */
			// End offset: 0x00059018
			// End Line: 2878
		/* end block 1.1 */
		// End offset: 0x00059024
		// End Line: 2890
	/* end block 1 */
	// End offset: 0x00059050
	// End Line: 2894

	/* begin block 2 */
		// Start line: 5344
	/* end block 2 */
	// End Line: 5345

void ProcessLumps(char *lump_ptr, int lump_size)
{
	int quit;

	int lump_type;
	DRIVER2_JUNCTION *pDVar8;
	ulong *puVar9;
	int size;
	int *ptr;

	quit = false;
	do {
		lump_type = *(int *)lump_ptr;
		size = *(int *)(lump_ptr + 4);
		ptr = (int *)(lump_ptr + 8);

		if (lump_type == LUMP_LOWDETAILTABLE) 
		{
			printf("LUMP_LOWDETAILTABLE: size: %d\n", size);
			ProcessLowDetailTable((char *)ptr, size);
		}
		else if (lump_type == LUMP_CHAIR)
		{
			printf("LUMP_CHAIR: size: %d\n", size);
			ProcessChairLump((char *)ptr, size);
		}
		else if (lump_type == LUMP_MOTIONCAPTURE)
		{
			printf("LUMP_MOTIONCAPTURE: size: %d\n", size);
			ProcessMotionLump((char *)ptr, size);
			gLoadedMotionCapture = 1;
		}
		else if (lump_type == LUMP_OVERLAYMAP)
		{
			printf("LUMP_OVERLAYMAP: size: %d\n", size);
			ProcessOverlayLump((char *)ptr, size);
			gLoadedOverlay = 1;
		}
		
		else if (lump_type == LUMP_MAP)
		{
			map_lump = (char *)ptr;
		}
		else if (lump_type == LUMP_SPOOLINFO)
		{
			printf("LUMP_SPOOLINFO: size: %d\n", size);
			ProcessSpoolInfoLump((char *)ptr, lump_size);
			ProcessMapLump(map_lump, 0);

			// [A] I don't think it's used anymore
			//region_buffer_xor =
			//	(cells_down >> 5 & 2U | cells_across >> 6 & 1U) << 2;

			//sdSelfModifyingCode =
			//	sdSelfModifyingCode ^
			//	(sdSelfModifyingCode ^ region_buffer_xor) & 0xc;
		}
		else if (lump_type == LUMP_CURVES2) 
		{
			printf("LUMP_CURVES2: size: %d\n", size);
			ProcessCurvesDriver2Lump((char *)ptr, size);
		}
		else if (lump_type == LUMP_TEXTURENAMES)
		{
			printf("LUMP_TEXTURENAMES: size: %d\n", size);
			texturename_buffer = (char*)ptr;
		}
		else if (lump_type == LUMP_PALLET)
		{
			printf("LUMP_PALLET: size: %d\n", size);
			palette_lump = (char*)ptr;
		}
		else if (lump_type == LUMP_TEXTUREINFO) 
		{
			printf("LUMP_TEXTUREINFO: size: %d\n", size);
			ProcessTextureInfo((char *)ptr);
		}
		else if (lump_type == LUMP_STRAIGHTS2) 
		{
			printf("LUMP_STRAIGHTS2: size: %d\n", size);
			ProcessStraightsDriver2Lump((char *)ptr, size);
		}
		else if (lump_type == LUMP_JUNCTIONS2_NEW)
		{
			printf("LUMP_JUNCTIONS2_NEW: size: %d\n", size);
			ProcessJunctionsDriver2Lump((char *)ptr, size, 0);
			lump_type = NumTempJunctions;
			pDVar8 = Driver2JunctionsPtr;
			puVar9 = Driver2TempJunctionsPtr;

			if (0 < NumTempJunctions)
			{
				do {
					lump_type = lump_type + -1;
					pDVar8->flags = *puVar9;
					pDVar8 = pDVar8 + 1;
					puVar9 = puVar9 + 1;
				} while (lump_type != 0);
			}
		}
		else if (lump_type == LUMP_JUNCTIONS2)
		{
			printf("LUMP_JUNCTIONS2: size: %d\n", size);
			ProcessJunctionsDriver2Lump
			((char *)ptr, size, 1);
			lump_type = NumTempJunctions;
			pDVar8 = Driver2JunctionsPtr;
			puVar9 = Driver2TempJunctionsPtr;

			if (0 < NumTempJunctions) {
				do {
					lump_type = lump_type + -1;
					pDVar8->flags = *puVar9;
					pDVar8 = pDVar8 + 1;
					puVar9 = puVar9 + 1;
				} while (lump_type != 0);
			}
		}
		else if (lump_type == LUMP_JUNCTIONS)
		{
			printf("LUMP_JUNCTIONS: size: %d\n", size);
			ProcessJunctionsLump((char *)ptr, size);
		}
		
		else if (lump_type == LUMP_CAR_MODELS)
		{
			printf("LUMP_CAR_MODELS: size: %d\n", size);
			car_models_lump = (char*)ptr;
		}
		else if (lump_type == LUMP_MODELS)
		{
			printf("LUMP_MODELS: size: %d\n", size);
			ProcessMDSLump((char *)ptr, size);
			ProcessCarModelLump(car_models_lump, 0);
			InitModelNames();
			SetUpEvents(1);
		}
		else if (lump_type == LUMP_ROADMAP)
		{
			printf("LUMP_ROADMAP: size: %d\n", size);
			NewProcessRoadMapLump(&roadMapLumpData, (char *)ptr);
		}
		else if (lump_type == LUMP_ROADS)
		{
			printf("LUMP_ROADS: size: %d\n", size);
			ProcessRoadsLump((char *)ptr, size);
		}
		if (lump_type == LUMP_ROADBOUNDS)
		{
			printf("LUMP_ROADBOUNDS: size: %d\n", size);
			ProcessRoadBoundsLump((char *)ptr, size);
		}
		else if (lump_type == LUMP_JUNCBOUNDS)
		{
			printf("LUMP_JUNCBOUNDS: size: %d\n", size);
			ProcessJuncBoundsLump((char *)ptr, size);
		}
		else if (lump_type == LUMP_SUBDIVISION)
		{
			printf("LUMP_SUBDIVISION: size: %d\n", size);
			ProcessSubDivisionLump((char *)ptr, size);
		}
		else if (lump_type == LUMP_ROADSURF)
		{
			printf("LUMP_ROADSURF: size: %d\n", size);
		}
		else if (lump_type == LUMP_MODELNAMES)
		{
			printf("LUMP_MODELNAMES: size: %d\n", size);
			modelname_buffer = (char *)ptr;
		}
		else if (lump_type == 0xff)
		{
			quit = true;
		}

		lump_size = size + 3;
		lump_ptr = (char*)ptr + (lump_size & ~0x3); // aligned to 4-byte boundary

		if (quit) 
			return;

	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadGameLevel()
 // line 2896, offset 0x00059050
	/* begin block 1 */
		// Start line: 2898
		// Start offset: 0x00059050
		// Variables:
	// 		int sector; // stack offset -32
	// 		int nsectors; // $s1
	// 		char name[64]; // stack offset -96
	// 		char *malloc_lump; // $s2
	/* end block 1 */
	// End offset: 0x00059238
	// End Line: 2967

	/* begin block 2 */
		// Start line: 5806
	/* end block 2 */
	// End Line: 5807

	/* begin block 3 */
		// Start line: 5809
	/* end block 3 */
	// End Line: 5810

	/* begin block 4 */
		// Start line: 5810
	/* end block 4 */
	// End Line: 5811

	/* begin block 5 */
		// Start line: 5818
	/* end block 5 */
	// End Line: 5819

/* WARNING: Unknown calling convention yet parameter storage is locked */

int SpoolLumpOffset;
SEATED_PEDESTRIANS* seated_pedestrian = NULL;

// [D]
void LoadGameLevel(void)
{
	char *malloc_lump;
	int nsectors;
	int sector;

	seated_pedestrian = NULL;
	LoadCosmetics(GameLevel);

	if (gMultiplayerLevels == 0)
	{
		if (gTimeOfDay == 3) {
			SetCityType(CITYTYPE_NIGHT);
		}
		else {
			SetCityType(CITYTYPE_DAY);
		}
	}
	else {
		if (gTimeOfDay == 3) {
			SetCityType(CITYTYPE_MULTI_NIGHT);
		}
		else {
			SetCityType(CITYTYPE_MULTI_DAY);
		}
	}
	ReportMode(0);
	sector = citylumps[GameLevel][0].x;

	if (sector < 0) {
		sector = sector + 2047;
	}

	nsectors = citylumps[GameLevel][0].y;
	sector = sector / CDSECTOR_SIZE;

	if (nsectors < 0) {
		nsectors = nsectors + (CDSECTOR_SIZE-1);
	}

	nsectors = nsectors / CDSECTOR_SIZE;

#ifdef PSX 
	loadsectors(_frontend_buffer, sector, nsectors);
#else
	extern char g_CurrentLevelFileName[64];
	loadsectorsPC(g_CurrentLevelFileName, _frontend_buffer, sector, nsectors);
#endif // PSX

	sector += nsectors;

	// CITYLUMP_DATA1
	ProcessLumps(_frontend_buffer+8, nsectors * CDSECTOR_SIZE);

	// CITYLUMP_TPAGE is right next after DATA1
	LoadPermanentTPages(&sector);

	malloc_lump = mallocptr;
	sector = citylumps[GameLevel][CITYLUMP_DATA2].x;

	if (sector < 0) {
		sector = sector + (CDSECTOR_SIZE-1);
	}

	nsectors = citylumps[GameLevel][CITYLUMP_DATA2].y;
	sector = sector / CDSECTOR_SIZE;

	if (nsectors < 0) {
		nsectors = nsectors + (CDSECTOR_SIZE-1);
	}

	nsectors = nsectors / CDSECTOR_SIZE;
	mallocptr = mallocptr + (nsectors * CDSECTOR_SIZE);

#ifdef PSX
	loadsectors(malloc_lump, sector, nsectors);
#else
	extern char g_CurrentLevelFileName[64];
	loadsectorsPC(g_CurrentLevelFileName, malloc_lump, sector, nsectors);
#endif // PSX
	sector += nsectors;

	ProcessLumps(malloc_lump + 8, (nsectors * CDSECTOR_SIZE));

	SpoolLumpOffset = citylumps[GameLevel][CITYLUMP_SPOOL].x;

	//Init_Reflection_Mapping();	// [A] I know that this is obsolete and used NOWHERE
	InitDebrisNames();
	InitShadow();
	//InitTextureNames();			// [A] I know that this is obsolete and used NOWHERE
	ReportMode(1);
}



// decompiled code
// original method signature: 
// int /*$ra*/ ReplayLog_Fnarr_He_Said_Log(int val /*$a0*/)
 // line 2973, offset 0x0005c81c
	/* begin block 1 */
		// Start line: 5946
	/* end block 1 */
	// End Line: 5947

	/* begin block 2 */
		// Start line: 9921
	/* end block 2 */
	// End Line: 9922

int ReplayLog_Fnarr_He_Said_Log(int val)
{
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitModelNames()
 // line 3003, offset 0x00059238
	/* begin block 1 */
		// Start line: 3005
		// Start offset: 0x00059238
	/* end block 1 */
	// End offset: 0x00059330
	// End Line: 3067

	/* begin block 2 */
		// Start line: 6005
	/* end block 2 */
	// End Line: 6006

	/* begin block 3 */
		// Start line: 6042
	/* end block 3 */
	// End Line: 6043

	/* begin block 4 */
		// Start line: 6043
	/* end block 4 */
	// End Line: 6044

	/* begin block 5 */
		// Start line: 6050
	/* end block 5 */
	// End Line: 6051

/* WARNING: Unknown calling convention yet parameter storage is locked */

void InitModelNames(void)
{
	UNIMPLEMENTED();
	/*
	gHubcapModelPtr = FindModelPtrWithName(s_HUBCAP1_000aa648);
	gCleanWheelModelPtr = FindModelPtrWithName(s_CLEANWHEEL_00010cd0);
	gFastWheelModelPtr = FindModelPtrWithName(s_FASTWHEEL_00010cdc);
	gDamWheelModelPtr = FindModelPtrWithName(s_DAMWHEEL_00010ce8);
	gPed1HeadModelPtr = FindModelPtrWithName(s_PEDHEAD1_00010cf4);
	gPed2HeadModelPtr = FindModelPtrWithName(&DAT_000aa650);
	gPed3HeadModelPtr = FindModelPtrWithName(&DAT_000aa650);
	gPed4HeadModelPtr = FindModelPtrWithName(&DAT_000aa650);
	gBoxModelPtr = FindModelPtrWithName(s_CRATE_000aa658);
	gRotorPtr = FindModelPtrWithName(s_ROTOR_000aa660);
	gTrailblazerConeModel = FindModelPtrWithName(s_GREENCONE_00010d00);
	gBombModel = FindModelPtrWithName(&DAT_000aa668);
	MangleWheelModels();
	InitTanner();
	InitAnimatingObjects();
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ GameInit()
 // line 3114, offset 0x00059330
	/* begin block 1 */
		// Start line: 3122
		// Start offset: 0x00059330

		/* begin block 1.1 */
			// Start line: 3226
			// Start offset: 0x000594C0
		/* end block 1.1 */
		// End offset: 0x000594D4
		// End Line: 3228

		/* begin block 1.2 */
			// Start line: 3263
			// Start offset: 0x000595B4
		/* end block 1.2 */
		// End offset: 0x000595B4
		// End Line: 3263

		/* begin block 1.3 */
			// Start line: 3271
			// Start offset: 0x000595DC
		/* end block 1.3 */
		// End offset: 0x00059604
		// End Line: 3277

		/* begin block 1.4 */
			// Start line: 3305
			// Start offset: 0x000596B0
			// Variables:
		// 		struct STREAM_SOURCE *pinfo; // $s0
		// 		char padid; // stack offset -48
		// 		int i; // $s2
		/* end block 1.4 */
		// End offset: 0x0005980C
		// End Line: 3359

		/* begin block 1.5 */
			// Start line: 3442
			// Start offset: 0x00059944
			// Variables:
		// 		int loop; // $s0

			/* begin block 1.5.1 */
				// Start line: 3445
				// Start offset: 0x0005994C
			/* end block 1.5.1 */
			// End offset: 0x0005994C
			// End Line: 3445
		/* end block 1.5 */
		// End offset: 0x0005996C
		// End Line: 3447

		/* begin block 1.6 */
			// Start line: 3455
			// Start offset: 0x0005998C
			// Variables:
		// 		int i; // $v1
		/* end block 1.6 */
		// End offset: 0x000599B8
		// End Line: 3460

		/* begin block 1.7 */
			// Start line: 3464
			// Start offset: 0x000599B8
		/* end block 1.7 */
		// End offset: 0x000599B8
		// End Line: 3475

		/* begin block 1.8 */
			// Start line: 3504
			// Start offset: 0x00059A0C
		/* end block 1.8 */
		// End offset: 0x00059A14
		// End Line: 3506
	/* end block 1 */
	// End offset: 0x00059A44
	// End Line: 3509

	/* begin block 2 */
		// Start line: 6262
	/* end block 2 */
	// End Line: 6263

	/* begin block 3 */
		// Start line: 6310
	/* end block 3 */
	// End Line: 6311

	/* begin block 4 */
		// Start line: 6317
	/* end block 4 */
	// End Line: 6318

/* WARNING: Unknown calling convention yet parameter storage is locked */

// TODO: SPOOL?
PACKED_CELL_OBJECT** pcoplist;
CELL_OBJECT** coplist;

ulong* transparent_buffer;

// system?
int gameinit = 0;
int gMusicType = 0;
int xa_timeout = 0;

int ThisMotion = 0;
int IconsLoaded = 0;

// TODO: AI.C?
SPEECH_QUEUE gSpeechQueue;

// OVERLAY
int gLoadedOverlay = 0;

// MOTION_C
int gLoadedMotionCapture = 0;

// DRAWGAME.C ???
int FrAng = 0;
int wetness = 0;

// [D]
void GameInit(void)
{
	long lVar1;
	_PLAYER *p_Var2;
	STREAM_SOURCE *pSVar3;
	int i;
	int iVar5;
	int iVar6;
	char padid;
	short totaldam;

	if (NewLevel == 0) {
		SetPleaseWait(NULL);
	}
	else {
		packed_cell_pointers = D_MALLOC(0x1000);
	}

	gameinit = 1;
	InitGameVariables();
	InitEvents();
	InitPadRecording();
	InitSpeechQueue(&gSpeechQueue);

	if (NewLevel != 0) {
		leadAIRequired = 0;
		leadAILoaded = 0;
		pathAILoaded = 0;
	}

	LoadMission(gCurrentMissionNumber);
	if (gCurrentMissionNumber == 0x26) {
		MissionHeader->residentModels[4] = 9;
	}
	if (GameType == GAME_MISSION) {
		SetupFadePolys();
	}
	if (NewLevel != 0) {
		ShowLoadingScreen(LoadingScreenNames[GameLevel], 1, 36);
	}
	if (AttractMode != 0) {
		TriggerInGameCutscene(0);
		NoPlayerControl = 1;
	}
	ResetSound();

	LockChannel(0);
	LockChannel(1);
	LockChannel(2);
	if (NumPlayers == 2) {
		LockChannel(3);
		LockChannel(4);
		LockChannel(5);
	}

	if (NewLevel != 0) {
		ShowLoading();
		LoadLevelSFX(gCurrentMissionNumber);
	}

	PauseSound();
	ThisMotion = 0;

	if (GameLevel == 1) 
	{
		gMusicType = 1;

		if ((gCurrentMissionNumber & 1U) != 0) 
			gMusicType = 5;
	}
	else if (GameLevel == 0)
	{
		gMusicType = 6;

		if ((gCurrentMissionNumber & 1U) != 0)
			gMusicType = 6;
	}
	else if (GameLevel == 2)
	{
		gMusicType = 0;

		if ((gCurrentMissionNumber & 1U) == 0) 
			gMusicType = 3;
	}
	else if(GameLevel == 3)
	{
		gMusicType = 4;

		if((gCurrentMissionNumber & 1U) != 0)
			gMusicType = 7;
	}

	InitMusic(gMusicType);

	if (NewLevel == 0) 
	{
		if (IconsLoaded == 0) 
			ReloadIcons();

		IconsLoaded = 1;
		SetUpEvents(0);
	}
	else {
		LoadGameLevel();
		IconsLoaded = 1;
		LoadSky();
		LoadFont(NULL);
	}

	ClearMem((char *)car_data, sizeof(car_data));

	player[0].spoolXZ = (VECTOR *)car_data[0].hd.where.t;
	car_data[0].hd.where.t[0] = PlayerStartInfo[0]->position.vx;
	car_data[0].hd.where.t[2] = PlayerStartInfo[0]->position.vz;

	CalcObjectRotationMatrices();
	InitialiseDenting();

	cameraview = 0;

	if (gLoadedMotionCapture != 0)
		InitPedestrians();

	InitSpooling();
	InitMap();
	InitSpecSpool();

	if (NewLevel == 0 && allowSpecSpooling == 1) 
	{
		QuickSpoolSpecial();
	}

	int_garage_door();
	SpoolSYNC();

	Emulator_SaveVRAM("VRAM_AFTER_LOAD.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);

	InitialiseCarHandling();
	ClearMem((char *)&player, 0x3a0);

	InitDrivingGames();
	InitThrownBombs();

	i = 0;
	if (0 < numPlayersToCreate) 
	{
		do {
			pSVar3 = PlayerStartInfo[i];
			padid = -(char)i;

			if (i < (int)(uint)NumPlayers) 
				padid = (char)i;

			gStartOnFoot = (pSVar3->type == 2);

			InitPlayer(&player[i], &car_data[i], pSVar3->controlType, pSVar3->rotation, (long(*)[4])&pSVar3->position, pSVar3->model, pSVar3->palette, &padid);

			if (gStartOnFoot == 0) 
			{
				car_data[i].ap.damage[0] = pSVar3->damage[0];
				car_data[i].ap.damage[1] = pSVar3->damage[1];
				car_data[i].ap.damage[2] = pSVar3->damage[2];
				car_data[i].ap.damage[3] = pSVar3->damage[3];
				car_data[i].ap.damage[4] = pSVar3->damage[4];
				car_data[i].ap.damage[5] = pSVar3->damage[5];

				car_data[i].totalDamage = pSVar3->totaldamage;

				car_data[i].ap.needsDenting = 1;
			}

			i++;
		} while (i < numPlayersToCreate);
	}

	if (pathAILoaded != 0)
		InitCops();

	InitCamera(&player[0]);

	if (gLoadedOverlay != 0 && NoPlayerControl == 0) {
		InitOverlays();
		IconsLoaded = 0;
	}

	gSinkingTimer = 100;
	gTimeInWater = 0x19;
	InWater = 0;
	gBobIndex = 0;
	SetupRain();
	InitExObjects();

	if (NewLevel != 0) 
	{
		pcoplist = (PACKED_CELL_OBJECT **)(mallocptr + 1024);
		transparent_buffer = (ulong *)(mallocptr + 2048);
		tile_overflow_buffer = (ulong *)mallocptr;
		coplist = (CELL_OBJECT **)mallocptr;
		mallocptr = mallocptr + 0x900;
	}

	if (NoPlayerControl == 0) 
	{
		DeleteAllCameras();
	}
	else 
	{
		FindNextChange(CameraCnt);
	}

	FrAng = 0x200;

	if (gWeather == 1) 
		wetness = 0x1b58;
	else 
		wetness = 0;

	if (gTimeOfDay == 2)
	{
		i = 0;
		do {
			lightsOnDelay[i] = Random2(0);
			i++;
		} while (i < 20);
	}

	tracking_car = 1;

	if (NoPlayerControl == 0)
		StoreGameFlags();

	SetReverbState(0);

	for(i = 0; i < 2; i++)
	{
		player[i].horn.request = 0;
		player[i].horn.time = 0;
		player[i].horn.on = 0;
	}

	gShowPlayerDamage = 1;
	InitThunder();
	GetXAData(-1);
	SetXAVolume(0);

	switch (gCurrentMissionNumber) 
	{
		case 2:
		case 3:
		case 6:
		case 11:
		case 13:
		case 14:
		case 19:
		case 26:
		case 28:
		case 34:
		case 38:
			FunkUpDaBGMTunez(1);
	}

	xa_timeout = 0;

	// [A]
	EnablePause(PAUSEMODE_PAUSE);
}

// decompiled code
// original method signature: 
// void /*$ra*/ StepSim()
 // line 3555, offset 0x00059a44
	/* begin block 1 */
		// Start line: 3557
		// Start offset: 0x00059A44
		// Variables:
	// 		static unsigned long t0; // offset 0x0
	// 		static char t1; // offset 0x4
	// 		static char t2; // offset 0x5
	// 		static int oldsp; // offset 0x8
	// 		struct _CAR_DATA *lcp; // $s0
	// 		int i; // $s2

		/* begin block 1.1 */
			// Start line: 3633
			// Start offset: 0x00059C70
			// Variables:
		// 		int eekTimer; // $s0

			/* begin block 1.1.1 */
				// Start line: 3639
				// Start offset: 0x00059CC4
			/* end block 1.1.1 */
			// End offset: 0x00059CC4
			// End Line: 3641
		/* end block 1.1 */
		// End offset: 0x00059D20
		// End Line: 3645

		/* begin block 1.2 */
			// Start line: 3649
			// Start offset: 0x00059D6C
		/* end block 1.2 */
		// End offset: 0x00059D6C
		// End Line: 3653

		/* begin block 1.3 */
			// Start line: 3556
			// Start offset: 0x00059FD8
		/* end block 1.3 */
		// End offset: 0x00059FD8
		// End Line: 3556

		/* begin block 1.4 */
			// Start line: 3838
			// Start offset: 0x0005A220
			// Variables:
		// 		int padsteer; // $a1

			/* begin block 1.4.1 */
				// Start line: 3868
				// Start offset: 0x0005A320
			/* end block 1.4.1 */
			// End offset: 0x0005A33C
			// End Line: 3872

			/* begin block 1.4.2 */
				// Start line: 3879
				// Start offset: 0x0005A374
			/* end block 1.4.2 */
			// End offset: 0x0005A374
			// End Line: 3879
		/* end block 1.4 */
		// End offset: 0x0005A374
		// End Line: 3879

		/* begin block 1.5 */
			// Start line: 3886
			// Start offset: 0x0005A394
		/* end block 1.5 */
		// End offset: 0x0005A3C8
		// End Line: 3888

		/* begin block 1.6 */
			// Start line: 3983
			// Start offset: 0x0005A650
			// Variables:
		// 		int i; // $s1
		// 		int j; // $s0
		// 		static int stupid_logic[4]; // offset 0x0

			/* begin block 1.6.1 */
				// Start line: 4003
				// Start offset: 0x0005A744
			/* end block 1.6.1 */
			// End offset: 0x0005A794
			// End Line: 4005
		/* end block 1.6 */
		// End offset: 0x0005A7B0
		// End Line: 4006

		/* begin block 1.7 */
			// Start line: 4033
			// Start offset: 0x0005A894
		/* end block 1.7 */
		// End offset: 0x0005A8AC
		// End Line: 4036
	/* end block 1 */
	// End offset: 0x0005A8DC
	// End Line: 4039

	/* begin block 2 */
		// Start line: 7193
	/* end block 2 */
	// End Line: 7194

	/* begin block 3 */
		// Start line: 7240
	/* end block 3 */
	// End Line: 7241

	/* begin block 4 */
		// Start line: 7241
	/* end block 4 */
	// End Line: 7242

	/* begin block 5 */
		// Start line: 7263
	/* end block 5 */
	// End Line: 7264

/* WARNING: Unknown calling convention yet parameter storage is locked */

void StepSim(void)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	ushort uVar2;
	short *psVar3;
	int *piVar4;
	undefined3 extraout_var;
	int stream;
	undefined4 uVar5;
	int *piVar6;
	uint uVar7;
	_CAR_DATA *cp;
	_PLAYER *p_Var8;
	int i;
	int car;

	if ((gTimeOfDay == 0) || (gTimeOfDay == 2)) {
		DawnCount = DawnCount + 1;
	}
	SetUpTrafficLightPhase();
	MoveSmashable_object();
	animate_garage_door();
	StepEvents();
	HandleMission();
	HandleInGameCutscene();
	HandleDrivingGames();
	num_active_cars = 0;
	if ((NoPlayerControl != 0) && (ReplayParameterPtr->RecordingEnd + -2 < CameraCnt)) {
		ReleaseInGameCutscene();
		pauseflag = 1;
	}
	oldsp_21 = SetSp(&DAT_1f8003e8);
	lead_pad = (ulong)controller_bits;
	if ((int)player.playerCarId < 0) {
		psVar3 = &pedestrianFelony;
	}
	else {
		psVar3 = &car_data[(int)player.playerCarId].felonyRating;
	}
	if ((*psVar3 < 0x527) || (numRoadblockCars != 0)) {
	LAB_00059c00:
		if (roadblockCount == 0) goto LAB_00059c1c;
	}
	else {
		if (roadblockCount == 0) {
			if (((copsAreInPursuit != 0) && (MissionHeader->residentModels[3] == 0)) &&
				(gCurrentMissionNumber != 0x1a)) {
				requestRoadblock = 1;
			}
			goto LAB_00059c00;
		}
	}
	roadblockCount = roadblockCount + -1;
LAB_00059c1c:
	if ((requestStationaryCivCar == 1) || (requestRoadblock != 0)) {
		distFurthestCivCarSq = 0;
	}
	else {
		i = 0;
		if (gInGameChaseActive == 0) {
			if ((numCivCars < maxCivCars) && (NumPlayers == 1)) {
				i = 0;
				while ((i < 5 && (car = PingInCivCar((int)&DAT_00003e1c), car == 0))) {
					i = i + 1;
				}
			}
		}
		else {
			if ((PingBufferPos < 400) &&
				((uint)PingBuffer[PingBufferPos].frame <= (CameraCnt - frameStart & 0xffffU))) {
				while (true) {
					PingInCivCar((int)&DAT_00003e1c);
					i = i + 1;
					if (399 < PingBufferPos) break;
					if (((CameraCnt - frameStart & 0xffffU) < (uint)PingBuffer[PingBufferPos].frame) ||
						(10 < i)) break;
				}
			}
		}
		SetUpCivCollFlags();
	}
	uVar7 = 0xd43fc;
	numRoadblockCars = 0;
	numInactiveCars = 0;
	numParkedCars = 0;
	numActiveCops = 0;
	numCopCars = 0;
	numCivCars = 0;
	do {
		cVar1 = *(char *)(uVar7 + 0x189);
		if (cVar1 == '\x02') {
			numCivCars = numCivCars + 1;
			if ((*(byte *)(uVar7 + 0x18a) & 1) != 0) {
				numCopCars = numCopCars + 1;
			}
			if (((*(byte *)(uVar7 + 0x18a) & 2) != 0) && (*(char *)(uVar7 + 0x285) == '\x03')) {
				if (*(char *)(uVar7 + 0x198) == '\x05') {
					numParkedCars = numParkedCars + 1;
				}
				if ((*(byte *)(uVar7 + 0x18a) & 2) != 0) {
					numRoadblockCars = numRoadblockCars + 1;
				}
			}
		}
		else {
			if (cVar1 == '\x03') {
				numCopCars = numCopCars + 1;
				if (*(char *)(uVar7 + 0x19f) == '\0') {
					numActiveCops = numActiveCops + 1;
				}
			}
			else {
				if (cVar1 == '\0') {
					numInactiveCars = numInactiveCars + 1;
				}
			}
		}
		uVar7 = uVar7 - 0x29c;
	} while (0xd1267 < uVar7);
	if (numRoadblockCars != 0) {
		roadblockCount = roadblockDelay;
	}
	if ((((requestStationaryCivCar == 0) && (requestRoadblock != 0)) && (numRoadblockCars == 0)) &&
		(4 < maxCivCars - numCivCars)) {
		CreateRoadblock();
	}
	cp = car_data + 0x13;
	if (gInGameCutsceneActive == 0) {
		CheckSpecialSpool();
	}
	while ((_CAR_DATA *)((int)&cheats.MagicMirror + 3U) < cp) {
		switch (cp->controlType) {
		case '\x01':
			t0_18 = (ulong)Pads[**(char **)cp->ai].mapped;
			t1_19 = Pads[**(char **)cp->ai].mapanalog[2];
			t2_20 = Pads[**(char **)cp->ai].type & 4;
			if (NoPlayerControl == 0) {
				if (gStopPadReads != 0) {
					t0_18 = 0x80;
					if ((cp->hd).wheel_speed < 0x9001) {
						t0_18 = 0x10;
					}
					t1_19 = '\0';
					t2_20 = 1;
				}
				cjpRecord((int)**(char **)cp->ai, &t0_18, &t1_19, &t2_20);
			}
			else {
				cjpPlay((int)**(char **)cp->ai, &t0_18, &t1_19, &t2_20);
			}
			ProcessCarPad(cp, t0_18, t1_19, t2_20);
			break;
		case '\x02':
			CivControl(cp);
			break;
		case '\x03':
			CopControl(cp);
			break;
		case '\x04':
			t2_20 = 0;
			t1_19 = '\0';
			t0_18 = 0;
			t0_18 = func_0x000ec99c(cp);
			if (t0_18 == 0) {
				cp->handbrake = '\x01';
				cp->wheel_angle = 0;
			}
			else {
				ProcessCarPad(cp, t0_18, t1_19, t2_20);
			}
			break;
		case '\a':
			cjpPlay(-(int)**(char **)cp->ai, &t0_18, &t1_19, &t2_20);
			ProcessCarPad(cp, t0_18, t1_19, t2_20);
		}
		StepCarPhysics(cp);
		cp = cp + -1;
	}
	i = 0;
	p_Var8 = &player;
	car = 7;
	do {
		if (p_Var8->playerType == '\x02') {
			stream = (int)p_Var8->padid;
			if (stream < 0) {
				stream = cjpPlay(-stream, &t0_18, &t1_19, &t2_20);
				if (stream != 0) {
					ProcessTannerPad(*(PEDESTRIAN **)((int)&player.pPed + i), t0_18, t1_19, t2_20);
				}
			}
			else {
				if (Pads[stream].type == '\x04') {
					cVar1 = Pads[stream].mapanalog[3];
					if ((cVar1 < -0x40) && (-100 < cVar1)) {
						Pads[stream].mapped = Pads[stream].mapped | 0x1008;
					}
					else {
						if ((cVar1 < -100) && ('\x7f' < cVar1)) {
							stream = (int)p_Var8->padid;
							uVar2 = Pads[stream].mapped | 0x1000;
						}
						else {
							if (cVar1 < '!') goto LAB_0005a2dc;
							stream = (int)p_Var8->padid;
							uVar2 = Pads[stream].mapped | 0x4000;
						}
						(&Pads[0].mapped)[stream * 0x24] = uVar2;
					}
				}
			LAB_0005a2dc:
				stream = (int)(&player.padid)[i];
				t0_18 = (ulong)Pads[stream].mapped;
				t1_19 = Pads[stream].mapanalog[2];
				t2_20 = Pads[stream].type & 4;
				if (NoPlayerControl == 0) {
					if (gStopPadReads != 0) {
						t2_20 = 0;
						t1_19 = '\0';
						t0_18 = 0;
					}
					cjpRecord(stream, &t0_18, &t1_19, &t2_20);
				}
				else {
					stream = cjpPlay(stream, &t0_18, &t1_19, &t2_20);
					if (stream == 0) goto LAB_0005a3d0;
				}
				ProcessTannerPad(*(PEDESTRIAN **)((int)&player.pPed + i), t0_18, t1_19, t2_20);
			}
		}
	LAB_0005a3d0:
		i = i + 0x74;
		p_Var8 = p_Var8 + 1;
		car = car + -1;
	} while (-1 < car);
	if ((requestStationaryCivCar == 1) &&
		((numCivCars < maxCivCars ||
		(PingOutCar(car_data + (byte)furthestCivID), numCivCars < maxCivCars)))) {
		requestStationaryCivCar = 0;
	}
	if ((game_over == 0) && (ControlCops(), gLoadedMotionCapture != 0)) {
		HandlePedestrians();
	}
	i = 0;
	GlobalTimeStep();
	UpdatePlayers();
	DoScenaryCollisions();
	CheckPlayerMiscFelonies();
	SetSp(oldsp_21);
	CameraCnt = CameraCnt + 1;
	gBobIndex = gBobIndex + 0x3cU & 0xfff;
	if (NumPlayers != 0) {
		car = 0;
		p_Var8 = &player;
		do {
			if ((p_Var8->horn).on == '\0') {
			LAB_0005a5b8:
				stream = CarHasSiren((uint)(byte)car_data[(&player.playerCarId)[car]].ap.model);
				if ((stream == 0) && (p_Var8->pPed == (PEDESTRIAN *)0x0)) {
					stream = 2;
					if (i != 0) {
						stream = 5;
					}
					StopChannel(stream);
					(&player.horn.request)[car] = '\0';
					(&player.horn.time)[car] = '\0';
				}
			}
			else {
				uVar5 = 4;
				if (i != 0) {
					uVar5 = 0x20;
				}
				stream = SpuGetKeyStatus(uVar5);
				if (stream == 0) {
					stream = CarHasSiren((uint)(byte)car_data[p_Var8->playerCarId].ap.model);
					if (((stream == 0) && (p_Var8->pPed == (PEDESTRIAN *)0x0)) &&
						((p_Var8->horn).request == '\0')) {
						(p_Var8->horn).request = '\x01';
					}
					(p_Var8->horn).time = '\v';
				}
				else {
					if ((p_Var8->horn).on == '\0') goto LAB_0005a5b8;
				}
			}
			DealWithHorn(&player.horn.request + car, i);
			car = car + 0x74;
			i = i + 1;
			p_Var8 = p_Var8 + 1;
		} while (i < (int)(uint)NumPlayers);
	}
	SoundTasks();
	if (((gInGameCutsceneActive == 0) || (gCurrentMissionNumber != 0x17)) || (gInGameCutsceneID != 0))
	{
		stupid_logic_22 = (int)player.playerCarId;
	}
	else {
		stupid_logic_22 = 2;
	}
	i = 0;
	piVar4 = &stupid_logic_22;
	DAT_000d565c = (int)_PLAYER_ARRAY_000d979c[0].playerCarId;
	DAT_000d5660 = gThePlayerCar;
	DAT_000d5664 = leadCarId;
	do {
		car = i + 1;
		if (car < 4) {
			piVar6 = &stupid_logic_22 + car;
			do {
				if (*piVar4 == *piVar6) {
					*piVar6 = -1;
				}
				car = car + 1;
				piVar6 = piVar6 + 1;
			} while (car < 4);
		}
		i = i + 1;
		piVar4 = piVar4 + 1;
	} while (i < 3);
	car = 0;
	piVar4 = &stupid_logic_22;
	i = 0;
	do {
		stream = i;
		if ((*piVar4 != -1) && (cVar1 = SilenceThisCar(car), CONCAT31(extraout_var, cVar1) == 0)) {
			stream = i + 1;
			CheckCarEffects(car_data + *piVar4, i);
		}
		car = car + 1;
		piVar4 = piVar4 + 1;
	} while ((car < 4) && (i = stream, stream < 2));
	SwirlLeaves(car_data);
	if ((gStopPadReads == 1) &&
		(((lead_car != 0 && (saved_counter = saved_counter + 1, 0x14 < saved_counter)) &&
		(saved_leadcar_pos == 0)))) {
		saved_leadcar_pos = gStopPadReads;
		leadcar_pos.vx = car_data[lead_car].hd.where.t[0];
		leadcar_pos.vy = car_data[lead_car].hd.where.t[1];
		leadcar_pos.vz = car_data[lead_car].hd.where.t[2];
	}
	if ((gInGameCutsceneActive == 0) &&
		(((car = XAPrepared(), i = xa_timeout, car != 0 && (i = xa_timeout + -1, xa_timeout == 0)) ||
		(xa_timeout = i, xa_timeout == 0)))) {
		StopXA();
		UnprepareXA();
		StartSpooling();
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ GameLoop()
 // line 4046, offset 0x0005a8dc
	/* begin block 1 */
		// Start line: 4048
		// Start offset: 0x0005A8DC
		// Variables:
	// 		int i; // $s0
	// 		struct RECT dest; // stack offset -24

		/* begin block 1.1 */
			// Start line: 4125
			// Start offset: 0x0005AA2C
			// Variables:
		// 		static struct POLY_FT3 buffer[2]; // offset 0x10
		// 		static struct POLY_FT3 *null; // offset 0xc
		/* end block 1.1 */
		// End offset: 0x0005AA98
		// End Line: 4140
	/* end block 1 */
	// End offset: 0x0005AB28
	// End Line: 4188

	/* begin block 2 */
		// Start line: 8546
	/* end block 2 */
	// End Line: 8547

	/* begin block 3 */
		// Start line: 8554
	/* end block 3 */
	// End Line: 8555

	/* begin block 4 */
		// Start line: 8555
	/* end block 4 */
	// End Line: 8556

	/* begin block 5 */
		// Start line: 8575
	/* end block 5 */
	// End Line: 8576

/* WARNING: Unknown calling convention yet parameter storage is locked */

REPLAY_PARAMETER_BLOCK *ReplayParameterPtr = NULL;

// [D]
void GameLoop(void)
{
	uint uVar1;
	int iVar2;
	static POLY_FT3 buffer[2];
	static POLY_FT3 *null;

	if (NewLevel != 0) {
		CloseShutters(2, 0x140, 0x200);
	}

	DisableDisplay();
	SetupDrawBuffers();
	EnableDisplay();

	srand(0x1234);

	cameraview = 0;
	FrameCnt = 0;
	NoTextureMemory = 0;

	SpoolSYNC();
	if (CurrentGameMode != GAMEMODE_DIRECTOR) {
		UnPauseSound();
	}

	iVar2 = 4;
	StartGameSounds();
	SetMasterVolume(gMasterVolume);
	SetXMVolume(gMusicVolume);
	CloseControllers();
	InitControllers();
	VSync(0);

	do {
		iVar2 = iVar2 + -1;
		ReadControllers();
		VSync(0);
	} while (-1 < iVar2);

	while (game_over == 0) {
		StepGame();

		if ((FastForward == 0) || (FrameCnt == (FrameCnt / 7) * 7)) 
		{
			DrawGame();
		}
		else
		{
			FrameCnt = FrameCnt + 1;
			uVar1 = FrameCnt & 1;
			null = buffer + uVar1;

			setPolyFT3(null);

			null->code = '$';
			null->x0 = -1;
			null->y0 = -1;
			null->x1 = -1;
			null->y1 = -1;
			null->x2 = -1;
			null->y2 = -1;
			null->tpage = 0x20;

			DrawPrim(null);
			DrawSync(0);
		}
		CheckForPause();
	}

	if (NoPlayerControl == 0) 
	{
		UNIMPLEMENTED(); // [A]
		//ReplayParameterPtr->RecordingEnd = CameraCnt;
	}

	StopPadVibration(0);
	StopPadVibration(1);
	StopAllChannels();
	FreeXM();

	iVar2 = XAPrepared();
	if (iVar2 != 0) {
		StopXA();
		UnprepareXA();
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepGame()
 // line 4196, offset 0x0005ab28
	/* begin block 1 */
		// Start line: 4198
		// Start offset: 0x0005AB28

		/* begin block 1.1 */
			// Start line: 4238
			// Start offset: 0x0005AB60
		/* end block 1.1 */
		// End offset: 0x0005AB70
		// End Line: 4240

		/* begin block 1.2 */
			// Start line: 4252
			// Start offset: 0x0005ABD8
			// Variables:
		// 		int i; // $a1
		/* end block 1.2 */
		// End offset: 0x0005AC3C
		// End Line: 4262

		/* begin block 1.3 */
			// Start line: 4336
			// Start offset: 0x0005AE20
		/* end block 1.3 */
		// End offset: 0x0005AE50
		// End Line: 4345

		/* begin block 1.4 */
			// Start line: 4361
			// Start offset: 0x0005AEC0
		/* end block 1.4 */
		// End offset: 0x0005AED0
		// End Line: 4368

		/* begin block 1.5 */
			// Start line: 4395
			// Start offset: 0x0005AF6C
			// Variables:
		// 		int strobe; // $v0
		/* end block 1.5 */
		// End offset: 0x0005AFB8
		// End Line: 4398

		/* begin block 1.6 */
			// Start line: 4536
			// Start offset: 0x0005B2E4
		/* end block 1.6 */
		// End offset: 0x0005B31C
		// End Line: 4538
	/* end block 1 */
	// End offset: 0x0005B384
	// End Line: 4547

	/* begin block 2 */
		// Start line: 8865
	/* end block 2 */
	// End Line: 8866

	/* begin block 3 */
		// Start line: 8874
	/* end block 3 */
	// End Line: 8875

	/* begin block 4 */
		// Start line: 8875
	/* end block 4 */
	// End Line: 8876

/* WARNING: Unknown calling convention yet parameter storage is locked */

extern short paddp;
extern short padd;
unsigned short controller_bits = 0;

VECTOR lis_pos;

int gLightsOn = 0;
int NightAmbient = 0;

char CameraChanged = 0;
char CamerasSaved = 0;
char paused = 0;

char gRightWayUp = 0;	// cheat

// [D]
void StepGame(void)
{
	char cVar1;
	int iVar2;
	uint uVar3;
	unsigned char *puVar4;
	_PLAYER *pPVar5;

	if (CameraCnt == 3) {
		StartXM(0);
	}
	if (doSpooling != 0) {
		CheckValidSpoolData();
		ControlMap();
	}
	if (gTimeOfDay == 3) {
		PreLampStreak();
	}
	UpdatePadData();
	if (FrameCnt == 5) {
		SetDispMask(1);
	}
	if (((padd & 0x2000U) != 0) && ((padd & 0x8000U) != 0)) {
		padd = padd & 0x5fff;
	}
	uVar3 = (uint)NumPlayers;
	controller_bits = padd;
	if (NumPlayers != 0) {
		pPVar5 = player;
		do {
			cVar1 = (pPVar5->horn).time;
			if ((cVar1 == '\0') || ((pPVar5->horn).on == '\0')) {
				(pPVar5->horn).time = '\0';
			}
			else {
				(pPVar5->horn).time = cVar1 + -1;
			}
			uVar3 = uVar3 - 1;
			pPVar5 = pPVar5 + 1;
		} while (uVar3 != 0);
	}
	ModifyCamera();
	lis_pos.vx = camera_position.vx;
	lis_pos.vy = camera_position.vy;
	lis_pos.vz = camera_position.vz;
	lis_pos.pad = camera_position.pad;
	FrAng = ratan2(0xa0, scr_z);
	if ((gTimeInWater == 0) || (gSinkingTimer < 100)) {
		gStopPadReads = 1;
		TargetCar = 0;
		cameraview = 0;
		gSinkingTimer = gSinkingTimer + -1;
		gCameraAngle = gCameraAngle - 0x16U & 0xfff;
		if (gCameraDistance < 1000) {
			gCameraMaxDistance = gCameraMaxDistance + 8;
			gCameraDistance = gCameraDistance + 8;
		}
		if (-1000 < CameraPos.vy) {
			CameraPos.vy = CameraPos.vy + -8;
		}
		if (gSinkingTimer < 0) {
			EnablePause(PAUSEMODE_GAMEOVER);
		}
	}
	if (gTimeOfDay == 1) {
		gLightsOn = 0;
		iVar2 = 0x4e;
		if (1 < gWeather - 1U) {
			iVar2 = 0x80;
		}
		goto LAB_0005aea0;
	}
	if (gTimeOfDay < 2) {
		if (gTimeOfDay == 0) {
			NightAmbient = (DawnCount >> 7) + 0x1a;
			gLightsOn = (DawnCount < 4000);
			iVar2 = 0x60;
			if (0x60 < NightAmbient) goto LAB_0005aea0;
		}
	}
	else {
		if (gTimeOfDay == 2) {
			if (DawnCount < 3000) {
				gLightsOn = 0;
			}
			else {
				gLightsOn = 1;
				puVar4 = lightsOnDelay;
				do {
					if (*puVar4 != '\0') {
						*puVar4 = *puVar4 + -1;
					}
					puVar4 = puVar4 + 1;
				} while ((int)puVar4 < 0xd56e4);
			}
			NightAmbient = 0x4e;
			if (gWeather - 1U < 2) {
				iVar2 = DawnCount >> 7;
			}
			else {
				NightAmbient = 0x60;
				iVar2 = DawnCount >> 5;
			}
			NightAmbient = NightAmbient - iVar2;
			iVar2 = 0x2d;
			if (NightAmbient < 0x2d) goto LAB_0005aea0;
		}
		else {
			if (gTimeOfDay == 3) {
				gLightsOn = 1;
				iVar2 = 0x80;
			LAB_0005aea0:
				NightAmbient = iVar2;
			}
		}
	}
	if ((gWeather != 0) && (gWeather == 1)) {
		DoLightning();
		DoThunder();
	}
	HandleExplosion();
	if (FastForward == 0) {
		ColourCycle();
	}
	combointensity = NightAmbient | NightAmbient << 8 | NightAmbient << 0x10;
	if ((NoPlayerControl != 0) && (AttractMode == 0)) {
		ShowReplayOptions();
	}

	if ((FastForward != 0) &&
		(uVar3 = CameraCnt & 0x1f, CameraCnt < ReplayParameterPtr->RecordingEnd + -1))
	{
		if (0xf < uVar3) {
			uVar3 = 0x20 - uVar3;
		}
		SetTextColour((uVar3 & 0x1f) << 3, '\0', '\0');
		PrintStringFeature("Fast forward", 100, 0x1e, 0x1000, 0x1000, 0);
	}

	if ((AttractMode == 0) && (pauseflag == 0)) {
		if (NoPlayerControl == 0) {
			if (2 < FrameCnt) {
				if (NumPlayers == 1) {
					if (((paddp == 0x800) && (bMissionTitleFade == 0)) &&
						(gInGameCutsceneActive == 0)) {
						EnablePause(PAUSEMODE_PAUSE);
					}
				}
				else {
					if (paddp == 0x800) {
						EnablePause(PAUSEMODE_PAUSEP1);
					}
					else {
						if ((NumPlayers == 2) && ((Pads[1].dirnew & 0x800) != 0)) {
							EnablePause(PAUSEMODE_PAUSEP2);
						}
					}
				}
			}
			goto LAB_0005b0a8;
		}
	}
	else {
	LAB_0005b0a8:
		if (NoPlayerControl == 0) {
			if (((pad_connected < 1) && (2 < FrameCnt)) &&
				((bMissionTitleFade == 0 && (gInGameCutsceneActive == 0)))) {
				pauseflag = 1;
				PauseSound();
			}
			if ((NoPlayerControl == 0) && (NoTextureMemory != 0)) {
				NoTextureMemory = NoTextureMemory + -1;
			}
		}
	}
	CameraChanged = '\0';
	old_camera_change = camera_change;
	if ((pauseflag == 0) && (NoPlayerControl != 0)) {
		if (gInGameCutsceneActive == 0) {
			iVar2 = CheckCameraChange(CameraCnt);
			camera_change = (char)iVar2;
			goto LAB_0005b1e0;
		}
	}
	else {
		if (gInGameCutsceneActive == 0) {
			camera_change = '\0';
			goto LAB_0005b1e0;
		}
	}
	iVar2 = CutsceneCameraChange(CameraCnt);
	camera_change = (char)iVar2;
LAB_0005b1e0:
	if (pauseflag == 0) {
		StepSim();
		if (gDieWithFade != 0) {
			gDieWithFade = gDieWithFade + 1;
		}
		if (paused != 0) {
			CamerasSaved = 1;
			paused = 0;
		}
	}
	else {
		if (((NoPlayerControl == 0) && (AttractMode == 0)) && (game_over == 0)) {
			if (pad_connected < 1) {
				EnablePause(PAUSEMODE_PADERROR);
			}
			else {
				EnablePause(PAUSEMODE_PAUSE);
			}
		}
		paused = 1;
	}
	if ((NoPlayerControl != 0) && (AttractMode == 0)) {
		ControlReplay();
	}
	if (gRightWayUp != 0) {
		TempBuildHandlingMatrix(car_data + player[0].playerCarId, 0);
		gRightWayUp = 0;
	}
	if ((AttractMode != 0) && ((paddp != 0 || (ReplayParameterPtr->RecordingEnd <= CameraCnt)))) {
		EndGame(GAMEMODE_QUIT);
	}
	UpdatePlayerInformation();
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawGame()
 // line 4549, offset 0x0005c458
	/* begin block 1 */
		// Start line: 4551
		// Start offset: 0x0005C458
		// Variables:
	// 		static unsigned long frame; // offset 0xc8

		/* begin block 1.1 */
			// Start line: 4555
			// Start offset: 0x0005C480
		/* end block 1.1 */
		// End offset: 0x0005C4D0
		// End Line: 4561

		/* begin block 1.2 */
			// Start line: 4567
			// Start offset: 0x0005C4EC
		/* end block 1.2 */
		// End offset: 0x0005C554
		// End Line: 4577
	/* end block 1 */
	// End offset: 0x0005C574
	// End Line: 4583

	/* begin block 2 */
		// Start line: 10753
	/* end block 2 */
	// End Line: 10754

	/* begin block 3 */
		// Start line: 9098
	/* end block 3 */
	// End Line: 9099

	/* begin block 4 */
		// Start line: 10754
	/* end block 4 */
	// End Line: 10755

	/* begin block 5 */
		// Start line: 10756
	/* end block 5 */
	// End Line: 10757

/* WARNING: Unknown calling convention yet parameter storage is locked */

// TODO: DRAW.C?
int ObjectDrawnValue = 0;
int ObjectDrawnCounter = 0;

void DrawGame(void)
{
	static unsigned long frame = 0;

	if ((NumPlayers == 1) || (NoPlayerControl != 0)) {
		ObjectDrawnValue = FrameCnt;
		DrawPauseMenus();
		RenderGame2(0);

		ObjectDrawnCounter++;

		while ((VSync(-1) - frame) < 2);

		frame = VSync(-1);
		SwapDrawBuffers();
	}
	else {
		ObjectDrawnValue = FrameCnt;
		RenderGame2(0);
		ObjectDrawnCounter++;

		SwapDrawBuffers2(0);

		ObjectDrawnValue += 16;
		DrawPauseMenus();
		RenderGame2(1);
		ObjectDrawnCounter++;

		SwapDrawBuffers2(1);
	}

	FrameCnt++;
}



// decompiled code
// original method signature: 
// void /*$ra*/ EndGame(enum GAMEMODE mode /*$a0*/)
 // line 4586, offset 0x0005c574
	/* begin block 1 */
		// Start line: 10823
	/* end block 1 */
	// End Line: 10824

	/* begin block 2 */
		// Start line: 10827
	/* end block 2 */
	// End Line: 10828

	/* begin block 3 */
		// Start line: 10829
	/* end block 3 */
	// End Line: 10830

static int WantPause = 0;
static PAUSEMODE PauseMode = PAUSEMODE_PAUSE;

// [D]
void EndGame(GAMEMODE mode)
{
	WantedGameMode = mode;
	pauseflag = 0;
	game_over = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ EnablePause(enum PAUSEMODE mode /*$a0*/)
 // line 4593, offset 0x0005c590
	/* begin block 1 */
		// Start line: 10842
	/* end block 1 */
	// End Line: 10843

	/* begin block 2 */
		// Start line: 10843
	/* end block 2 */
	// End Line: 10844

// [D]
void EnablePause(PAUSEMODE mode)
{
	if (((quick_replay != 0) || (NoPlayerControl == 0)) || (mode != PAUSEMODE_GAMEOVER))
	{
		WantPause = 1;
		PauseMode = mode;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckForPause()
 // line 4602, offset 0x0005c5d0
	/* begin block 1 */
		// Start line: 4604
		// Start offset: 0x0005C5D0

		/* begin block 1.1 */
			// Start line: 4603
			// Start offset: 0x0005C5E4
		/* end block 1.1 */
		// End offset: 0x0005C614
		// End Line: 4603
	/* end block 1 */
	// End offset: 0x0005C668
	// End Line: 4618

	/* begin block 2 */
		// Start line: 10861
	/* end block 2 */
	// End Line: 10862

	/* begin block 3 */
		// Start line: 10862
	/* end block 3 */
	// End Line: 10863

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void CheckForPause(void)
{
	if ((gDieWithFade > 15) && ((quick_replay != 0 || (NoPlayerControl == 0)))) 
	{
		PauseMode = PAUSEMODE_GAMEOVER;
		WantPause = 1;
	}

	if (WantPause != 0)
	{
		WantPause = 0;
		pauseflag = 1;

		PauseSound();
		ShowPauseMenu(PauseMode);

		if (game_over == 0)
		{
			UnPauseSound();
		}
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ main()
 // line 4767, offset 0x0005b384
	/* begin block 1 */
		// Start line: 4768
		// Start offset: 0x0005B384

		/* begin block 1.1 */
			// Start line: 4768
			// Start offset: 0x0005B384

			/* begin block 1.1.1 */
				// Start line: 4768
				// Start offset: 0x0005B384
				// Variables:
			// 		char (*PALScreenNames[4]); // stack offset -24
			// 		char (*NTSCScreenNames[4]); // stack offset -40
			// 		char (*OPMScreenNames[4]); // stack offset -56
			/* end block 1.1.1 */
			// End offset: 0x0005B384
			// End Line: 4768
		/* end block 1.1 */
		// End offset: 0x0005B384
		// End Line: 4768
	/* end block 1 */
	// End offset: 0x0005B54C
	// End Line: 4868

	/* begin block 2 */
		// Start line: 9845
	/* end block 2 */
	// End Line: 9846

	/* begin block 3 */
		// Start line: 10066
	/* end block 3 */
	// End Line: 10067

/* WARNING: Unknown calling convention yet parameter storage is locked */

// decompiled code
// original method signature: 
// void SsSetSerialVol(char param_1,short param_2,short param_3);
 // line -1, offset 0x00092b3c
// function 'SsSetSerialVol' @0x00092B3C was found in the decompiled code exported from Ghidra, but not the original debug symbol data.
void SsSetSerialVol(char param_1, short param_2, short param_3)
{
	UNIMPLEMENTED();

	/*
	undefined4 local_30[4];
	short local_20;
	short local_1e;
	short local_14;
	short local_12;

	if (param_1 == '\0') {
		local_30[0] = 0xc0;
		if (0x7f < param_2) {
			param_2 = 0x7f;
		}
		if (0x7f < param_3) {
			param_3 = 0x7f;
		}
		local_20 = param_2 * 0x102;
		local_1e = param_3 * 0x102;
	}
	if (param_1 == '\x01') {
		local_30[0] = 0xc00;
		if (0x7f < param_2) {
			param_2 = 0x7f;
		}
		if (0x7f < param_3) {
			param_3 = 0x7f;
		}
		local_14 = param_2 * 0x102;
		local_12 = param_3 * 0x102;
	}
	SpuSetCommonAttr(local_30);
	return;
	*/
}

// [D]
#ifdef PSX
int main(void)
#else
int redriver2_main(void)
#endif // PSX
{
	char *PALScreenNames[4] = {		// [A] don't show publisher logo
	//	"GFX\\SPLASH2.TIM",
	//	"GFX\\SPLASH3.TIM",
		"GFX\\SPLASH1P.TIM",
		NULL
	};

	char *NTSCScreenNames[4] = {		// [A] don't show publisher logo
	//	"GFX\\SPLASH2.TIM",
	//	"GFX\\SPLASH3.TIM",
		"GFX\\SPLASH1N.TIM",
		NULL
	};

	char *OPMScreenNames[4] = {		// [A] don't show publisher logo
		//"GFX\\OPM1.TIM",
		"GFX\\OPM2.TIM",
		"GFX\\OPM3.TIM",
		NULL
	};

	//_stacksize = 0x4000;
	//_ramsize = 0x200000;

	SetDispMask(0);
	StopCallback();
	ResetCallback();
	ResetGraph(0);
	SsSetSerialVol(0, 0, 0);
	SetDispMask(0);
	SetGraphDebug(0);
	SetVideoMode(video_mode);
	CdInit();
	SsSetSerialVol(0, 0, 0);
	SpuInit();
	InitGeom();
	SetGeomOffset(160, 128);
	scr_z = 256;
	SetGeomScreen(256);
	MemCardInit(1);
	InitControllers();
	Init_FileSystem();
	InitSound();

	//PlayFMV(99);	// [A] don't show publisher logo

	ShowHiresScreens(OPMScreenNames, 300, 0); // [A]

	PlayFMV(0);		// play intro movie

	CheckForCorrectDisc(0);

	// Init frontend
#ifdef PSX
	Loadfile("FRONTEND.BIN", &DAT_001c0000);
#endif // PSX

	SpuSetMute(0);

	// initializes sound system
	LoadSoundBankDynamic(NULL, 0, 0);

	// load frontend bank
	LoadBankFromLump(1, 0);

	InitialiseScoreTables();

	// now run the frontend
	DoFrontEnd();

	return 1;
}

// decompiled code
// original method signature: 
// void /*$ra*/ FadeScreen(int end_value /*$a1*/)
 // line 4870, offset 0x0005c668
	/* begin block 1 */
		// Start line: 4871
		// Start offset: 0x0005C668
		// Variables:
	// 		int tmp2; // $s1
	/* end block 1 */
	// End offset: 0x0005C6E0
	// End Line: 4888

	/* begin block 2 */
		// Start line: 11280
	/* end block 2 */
	// End Line: 11281

	/* begin block 3 */
		// Start line: 11397
	/* end block 3 */
	// End Line: 11398

void FadeScreen(int end_value)
{
	int tmp2 = pauseflag;

	pauseflag = 1;
	SetupScreenFade(-0x20, end_value, 1);
	FadingScreen = 1;

	do {
		RenderGame();
	} while (FadingScreen != 0);

	DrawSync(0);
	SetDispMask(0);
	pauseflag = tmp2;
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdatePlayerInformation()
 // line 4893, offset 0x0005b54c
	/* begin block 1 */
		// Start line: 4895
		// Start offset: 0x0005B54C
		// Variables:
	// 		struct _CAR_DATA *cp; // $s1
	// 		int count; // $s0
	// 		int scale; // $v1
	// 		int wheel; // $t1
	// 		int wheelsonwater; // $t2
	/* end block 1 */
	// End offset: 0x0005B888
	// End Line: 4972

	/* begin block 2 */
		// Start line: 10293
	/* end block 2 */
	// End Line: 10294

	/* begin block 3 */
		// Start line: 10319
	/* end block 3 */
	// End Line: 10320

	/* begin block 4 */
		// Start line: 10320
	/* end block 4 */
	// End Line: 10321

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdatePlayerInformation(void)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	int iVar2;
	byte *pbVar3;
	WHEEL *pWVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	_CAR_DATA *p_Var9;

	p_Var9 = (_CAR_DATA *)0x0;
	PlayerDamageBar.max = (ushort)MaxPlayerDamage;
	Player2DamageBar.max = (ushort)INT_000aa714;
	if (gPlayerImmune != 0) {
		if ((int)player.playerCarId < 0) {
			psVar1 = &pedestrianFelony;
		}
		else {
			psVar1 = &car_data[(int)player.playerCarId].felonyRating;
		}
		*psVar1 = 0;
	}
	if ((int)player.playerCarId < 0) {
		psVar1 = &pedestrianFelony;
	}
	else {
		psVar1 = &car_data[(int)player.playerCarId].felonyRating;
	}
	FelonyBar.position = *psVar1;
	if (NumPlayers != 0) {
		iVar2 = 0;
		iVar8 = 0;
		do {
			iVar2 = (iVar2 * 4 + iVar8 * -3) * 4;
			if ((&player.playerType)[iVar2] == '\x01') {
				iVar2 = (int)(&player.playerCarId)[iVar2];
				p_Var9 = car_data + iVar2;
				if (gInvincibleCar != 0) {
					car_data[iVar2].totalDamage = 0;
					ClearMem((char *)car_data[iVar2].ap.damage, 0xc);
				}
				iVar6 = 0;
				iVar7 = iVar8 + 1;
				pWVar4 = car_data[iVar2].hd.wheel;
				pbVar3 = &car_data[iVar2].hd.wheel[0].surface;
				iVar5 = 3;
				do {
					if (((uint)*pbVar3 & 7) == 1) {
						if (pWVar4->susCompression == '\0') {
							if ((car_data[iVar2].hd.where.t[1] < -1000) && (gDieWithFade == 0)) {
								gDieWithFade = (uint)*pbVar3 & 7;
							}
						}
						else {
							iVar6 = iVar6 + 1;
						}
					}
					pWVar4 = pWVar4 + 1;
					iVar5 = iVar5 + -1;
					pbVar3 = pbVar3 + 4;
				} while (-1 < iVar5);
				if (iVar6 == 4) {
					car_data[iVar2].totalDamage =
						car_data[iVar2].totalDamage + (short)((&MaxPlayerDamage)[iVar8] / 0x50);
				}
				if ((&MaxPlayerDamage)[iVar8] < (int)(uint)car_data[iVar2].totalDamage) {
					car_data[iVar2].totalDamage = *(ushort *)(&MaxPlayerDamage + iVar8);
				}
				if (iVar8 == 0) {
					PlayerDamageBar.position = car_data[iVar2].totalDamage;
				}
				else {
					Player2DamageBar.position = car_data[iVar2].totalDamage;
				}
			}
			else {
				iVar7 = iVar8 + 1;
				if (iVar8 == 0) {
					PlayerDamageBar.position = 0;
					iVar7 = 1;
				}
				else {
					Player2DamageBar.position = 0;
				}
			}
			if (((0x1df < gCurrentMissionNumber) &&
				(((gCurrentMissionNumber < 0x1e2 ||
				((gCurrentMissionNumber < 0x1e6 && (0x1e3 < gCurrentMissionNumber)))) &&
					((p_Var9->hd).where.t[1] < -0x2ee)))) && (gDieWithFade == 0)) {
				gDieWithFade = 1;
			}
			iVar2 = iVar7 << 3;
			iVar8 = iVar7;
		} while (iVar7 < (int)(uint)NumPlayers);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ RenderGame2(int view /*$s3*/)
 // line 5021, offset 0x0005b888
	/* begin block 1 */
		// Start line: 5022
		// Start offset: 0x0005B888
		// Variables:
	// 		int spaceFree; // $a1
	// 		int notInDreaAndStevesEvilLair; // $s0

		/* begin block 1.1 */
			// Start line: 5067
			// Start offset: 0x0005B9A4
			// Variables:
		// 		int strobe; // $v0
		/* end block 1.1 */
		// End offset: 0x0005B9EC
		// End Line: 5070

		/* begin block 1.2 */
			// Start line: 5073
			// Start offset: 0x0005B9EC
			// Variables:
		// 		int i; // $s1
		/* end block 1.2 */
		// End offset: 0x0005BA84
		// End Line: 5077

		/* begin block 1.3 */
			// Start line: 5090
			// Start offset: 0x0005BAE4
			// Variables:
		// 		struct POLY_F4 *poly; // $v1
		// 		int col; // $a1
		/* end block 1.3 */
		// End offset: 0x0005BC20
		// End Line: 5113

		/* begin block 1.4 */
			// Start line: 5121
			// Start offset: 0x0005BC40
		/* end block 1.4 */
		// End offset: 0x0005BC88
		// End Line: 5125
	/* end block 1 */
	// End offset: 0x0005BCE4
	// End Line: 5132

	/* begin block 2 */
		// Start line: 10644
	/* end block 2 */
	// End Line: 10645

	/* begin block 3 */
		// Start line: 10654
	/* end block 3 */
	// End Line: 10655

int CurrentPlayerView = 0;

// [D]
void RenderGame2(int view)
{
	DB *pDVar1;
	int iVar2;
	POLY_F4 *poly;
	uint uVar3;
	unsigned char uVar4;
	char *pcVar5;
	_PLAYER *pPVar6;
	int iVar7;

	CurrentPlayerView = view;
	InitCamera((_PLAYER *)(player + view));
	Set_Inv_CameraMatrix();
	SetCameraVector();
	SetupDrawMapPSX();

	if (gLoadedMotionCapture != 0) 
		DrawAllPedestrians();

	DisplayMissionTitle();
	DrawInGameCutscene();
	DrawEvents(1);
	Set_Inv_CameraMatrix();
	SetCameraVector();
	SetupDrawMapPSX();
	DrawDrivingGames();
	DrawThrownBombs();
	AddGroundDebris();
	DrawEvents(0);
	current->ot = current->ot + 10;
	DrawSmashable_sprites();
	HandleDebris();
	current->ot = current->ot + -10;
	DrawAllExplosions();

	if (AttractMode != 0) 
	{
		uVar3 = CameraCnt & 0x1f;

		if (0xf < uVar3) {
			uVar3 = 0x20 - uVar3;
		}

		SetTextColour(((uVar3 & 0x1f) << 3), '\0', '\0');
		PrintString("DEMO", 0x23, 0xf);
	}

	pPVar6 = player;
	iVar7 = 2;

	do {
		iVar2 = CarHasSiren((uint)(char)car_data[pPVar6->playerCarId].ap.model);

		if ((iVar2 != 0) && ((pPVar6->horn).on != '\0'))
			AddCopCarLight(car_data + pPVar6->playerCarId);
	
		iVar7 = iVar7 + -1;
		pPVar6 = pPVar6 + 1;
	} while (-1 < iVar7);

	if (gLoadedOverlay != 0)
	{
		DisplayOverlays();
	}

	DrawMission();

	if ((FastForward == 0) && (NumPlayers == 1))
	{
		DrawLensFlare();
	}

	uVar4 = (unsigned char)(gDieWithFade << 4);

	if (gDieWithFade != 0) 
	{
		if (0xff < gDieWithFade << 4) {
			uVar4 = -1;
		}
		poly = (POLY_F4 *)current->primptr;

		setPolyF4(poly);
		setSemiTrans(poly, 1);

		poly->r0 = uVar4;
		poly->g0 = uVar4;
		poly->b0 = uVar4;
		pDVar1 = current;
		poly->x0 = 0;
		poly->y0 = 0;
		poly->x1 = 0x140;
		poly->y1 = 0;
		poly->x2 = 0;
		poly->y2 = 0x100;
		poly->x3 = 0x140;
		poly->y3 = 0x100;
		addPrim((u_long*)(pDVar1->ot + 8), poly);

		pDVar1->primptr += sizeof(POLY_F4);
		POLY_FT3* null = (POLY_FT3*)pDVar1->primptr;

		setPolyFT3(null);
		null->x0 = -1;
		null->y0 = -1;
		null->x1 = -1;
		null->y1 = -1;
		null->x2 = -1;
		null->y2 = -1;
		null->tpage = 0x40;

		addPrim((u_long*)(pDVar1->ot + 8), poly);
		pDVar1->primptr += sizeof(POLY_FT3);
	}

	iVar7 = Havana3DOcclusion(DrawMapPSX, (int *)&ObjectDrawnValue);

	ScaleCamera();

	if ((iVar7 != 0) && (DrawSkyDome(), 40000 < (int)(current->primtab + -(int)(current->primptr + -0x1e000)))) 
	{
		DoWeather(gWeather);
	}

	if (37000 < (int)(current->primtab + -(int)(current->primptr + -0x1e000)))
	{
		DrawTyreTracks();
	}

	DrawAllTheCars(view);
}



// decompiled code
// original method signature: 
// void /*$ra*/ RenderGame()
 // line 5260, offset 0x0005c6e0
	/* begin block 1 */
		// Start line: 5262
		// Start offset: 0x0005C6E0

		/* begin block 1.1 */
			// Start line: 5262
			// Start offset: 0x0005C6E0

			/* begin block 1.1.1 */
				// Start line: 5262
				// Start offset: 0x0005C6E0
				// Variables:
			// 		static unsigned long frame; // offset 0xc8

				/* begin block 1.1.1.1 */
					// Start line: 5261
					// Start offset: 0x0005C714
				/* end block 1.1.1.1 */
				// End offset: 0x0005C764
				// End Line: 5261

				/* begin block 1.1.1.2 */
					// Start line: 5261
					// Start offset: 0x0005C780
				/* end block 1.1.1.2 */
				// End offset: 0x0005C7E8
				// End Line: 5261
			/* end block 1.1.1 */
			// End offset: 0x0005C7E8
			// End Line: 5261
		/* end block 1.1 */
		// End offset: 0x0005C7E8
		// End Line: 5261
	/* end block 1 */
	// End offset: 0x0005C81C
	// End Line: 5269

	/* begin block 2 */
		// Start line: 11914
	/* end block 2 */
	// End Line: 11915

	/* begin block 3 */
		// Start line: 12188
	/* end block 3 */
	// End Line: 12189

	/* begin block 4 */
		// Start line: 12189
	/* end block 4 */
	// End Line: 12190

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void RenderGame(void)
{
	UpdatePadData();

	DrawGame();

	FadeGameScreen(0, 8);
}

// decompiled code
// original method signature: 
// void /*$ra*/ InitGameVariables()
 // line 5272, offset 0x0005bce4
	/* begin block 1 */
		// Start line: 5274
		// Start offset: 0x0005BCE4
	/* end block 1 */
	// End offset: 0x0005BF74
	// End Line: 5341

	/* begin block 2 */
		// Start line: 11050
	/* end block 2 */
	// End Line: 11051

	/* begin block 3 */
		// Start line: 11191
	/* end block 3 */
	// End Line: 11192

	/* begin block 4 */
		// Start line: 11192
	/* end block 4 */
	// End Line: 11193

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitGameVariables(void)
{
	InitDebris();
	InitTyreTracks();
	TargetCar = 0;

	if (NewLevel != 0) {
		gLoadedOverlay = 0;
		gLoadedMotionCapture = 0;
	}

	gRainCount = '\0';

	if ((NoPlayerControl == 0) || (AttractMode != 0)) {
		pauseflag = 0;
	}
	else {
		pauseflag = 1;
	}

	HitLeadCar = 0;
	FastForward = 0;
	game_over = 0;
	saved_counter = 0;
	saved_leadcar_pos = 0;
	gStopPadReads = 0;
	DawnCount = 0;
	variable_weather = 0;
	current_camera_angle = 0x800;
	gDieWithFade = 0;

	srand(0x1234);
	RandomInit(0xd431, 0x350b1);
	FrameCnt = 0;
	CameraCnt = 0;

	ClearMem((char *)&lightsOnDelay, 0x14);

	PlayerStartInfo[0] = &ReplayStreams[0].SourceType;
	ClearMem((char *)PlayerStartInfo[0], sizeof(STREAM_SOURCE));

	PlayerStartInfo[0]->type = 1;
	PlayerStartInfo[0]->model = defaultPlayerModel[0];
	PlayerStartInfo[0]->palette = defaultPlayerPalette;
	PlayerStartInfo[0]->controlType = 1;
	PlayerStartInfo[0]->flags = 0;

	PlayerStartInfo[0]->rotation = levelstartpos[GameLevel][1];
	PlayerStartInfo[0]->position.vx = levelstartpos[GameLevel][0];
	PlayerStartInfo[0]->position.vy = 0;
	PlayerStartInfo[0]->position.vz = levelstartpos[GameLevel][2];

	numPlayersToCreate = 1;

	if (NumPlayers == 2) {
		PlayerStartInfo[1] = &ReplayStreams[1].SourceType;
		ClearMem((char *)PlayerStartInfo[1], sizeof(STREAM_SOURCE));

		PlayerStartInfo[1]->type = 1;
		PlayerStartInfo[1]->model = defaultPlayerModel[1];
		PlayerStartInfo[1]->palette = defaultPlayerPalette;
		PlayerStartInfo[1]->controlType = 1;
		PlayerStartInfo[1]->flags = 0;
		PlayerStartInfo[1]->rotation = levelstartpos[GameLevel][1];
		PlayerStartInfo[1]->position.vx = levelstartpos[GameLevel][0] + 600;
		PlayerStartInfo[1]->position.vy = 0;
		PlayerStartInfo[1]->position.vz = levelstartpos[GameLevel][2];

		numPlayersToCreate = NumPlayers;
	}

	InitCivCars();
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DealWithHorn(char *hr /*$s2*/, int i /*$s1*/)
 // line 5345, offset 0x0005bf74
	/* begin block 1 */
		// Start line: 5346
		// Start offset: 0x0005BF74
		// Variables:
	// 		struct _CAR_DATA *car; // $s0

		/* begin block 1.1 */
			// Start line: 5348
			// Start offset: 0x0005C014
		/* end block 1.1 */
		// End offset: 0x0005C124
		// End Line: 5363
	/* end block 1 */
	// End offset: 0x0005C154
	// End Line: 5365

	/* begin block 2 */
		// Start line: 11377
	/* end block 2 */
	// End Line: 11378

	/* begin block 3 */
		// Start line: 11382
	/* end block 3 */
	// End Line: 11383

void DealWithHorn(char *hr, int i)
{
	UNIMPLEMENTED();

	/*
	byte bVar1;
	int channel;
	int channel_00;
	uint uVar2;

	channel = (int)(&player)[i].playerCarId;
	bVar1 = *hr;
	if (bVar1 == 1) {
		channel = 2;
		if (i != 0) {
			channel = 5;
		}
		StopChannel(channel);
	}
	else {
		if (bVar1 < 2) {
			if (bVar1 == 0) {
				return;
			}
		}
		else {
			if (bVar1 == 2) {
				bVar1 = car_data[channel].ap.model;
				if (bVar1 == 4) {
					uVar2 = ResidentModelsBodge();
				}
				else {
					if (bVar1 < 3) {
						uVar2 = (uint)(byte)car_data[channel].ap.model;
					}
					else {
						uVar2 = (uint)(byte)car_data[channel].ap.model - 1;
					}
				}
				channel_00 = 2;
				if (i != 0) {
					channel_00 = 5;
				}
				Start3DSoundVolPitch
				(channel_00, 3, uVar2 * 3 + 2, car_data[channel].hd.where.t[0],
					car_data[channel].hd.where.t[1], car_data[channel].hd.where.t[2], -10000, 0x1000);
				if ((1 < NumPlayers) && (NoPlayerControl == 0)) {
					channel_00 = 2;
					if (i != 0) {
						channel_00 = 5;
					}
					SetPlayerOwnsChannel(channel_00, (char)i);
				}
				channel_00 = 2;
				if (i != 0) {
					channel_00 = 5;
				}
				SetChannelPosition3(channel_00, (VECTOR *)car_data[channel].hd.where.t,
					(long *)(car_data[channel].st + 0x1c), -2000, i * 8 + 0x1000, 0);
			}
		}
	}
	uVar2 = (uint)(byte)*hr + 1 & 0xff;
	*hr = (char)uVar2 - (((byte)((ulonglong)uVar2 * 0xaaaaaaab >> 0x20) & 0xfe) + (char)(uVar2 / 3));
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ Havana3DOcclusion(TDRFuncPtr_Havana3DOcclusion0func func /*$a3*/, int *param /*$fp*/)
 // line 5367, offset 0x0005c16c
	/* begin block 1 */
		// Start line: 5368
		// Start offset: 0x0005C16C
		// Variables:
	// 		int outside; // $s6
	// 		int otAltered; // $s5

		/* begin block 1.1 */
			// Start line: 5379
			// Start offset: 0x0005C208
			// Variables:
		// 		int draw; // $s2
		// 		int loop; // $s0
		/* end block 1.1 */
		// End offset: 0x0005C414
		// End Line: 5473
	/* end block 1 */
	// End offset: 0x0005C458
	// End Line: 5480

	/* begin block 2 */
		// Start line: 11426
	/* end block 2 */
	// End Line: 11427

	/* begin block 3 */
		// Start line: 11430
	/* end block 3 */
	// End Line: 11431

// [D]
int Havana3DOcclusion(occlFunc func, int *param)
{
	bool bVar1;
	int iVar2;
	int unaff_s2;
	int iVar3;
	int iVar4;
	int iVar5;

	iVar5 = 1;

	if ((((GameLevel != 1) || (-0x68fdc < camera_position.vx)) || (camera_position.vx < -0x75416))
		|| ((-0x1b8ae < camera_position.vz || (camera_position.vz < -0x20cb3))))
	{
		(*func)(param);
		return 1;
	}

	if (camera_position.vy < 0x1bf) 
	{
		unaff_s2 = 0x10;

		if (-0x729fc < camera_position.vx) 
			unaff_s2 = 0x11;
	}
	else 
	{
		iVar5 = 0;
		if (((camera_position.vx < -0x6e9e5) && (-0x6fa01 < camera_position.vx)) &&
			((camera_position.vz < -0x1e201 &&
			((-0x1f205 < camera_position.vz && (camera_position.vy < 0xf73))))))
		{
			if (camera_position.vy < 0x4dd) 
			{
			LAB_0005c2b4:
				unaff_s2 = 0xf;
			}
			else 
			{
				bVar1 = camera_position.vy < 0xc00;
				if (camera_position.vy < 0x7d1) 
				{
					unaff_s2 = 0xe;
				}
				else 
				{
				LAB_0005c2d8:
					if (bVar1) 
					{
						unaff_s2 = 0xd;
					}
				}
			}
		}
		else 
		{
			if (camera_position.vy < 0x6c2)
				goto LAB_0005c2b4;

			unaff_s2 = 0xe;

			if (camera_position.vy < 0x834) 
			{
				bVar1 = camera_position.vx < -0x73609;
				goto LAB_0005c2d8;
			}

			if ((((0xbff < camera_position.vy) && (-0x6fa01 < camera_position.vx)) ||
				(unaff_s2 = 0xc, camera_position.vz < -0x1f9db)) &&
				(unaff_s2 = 10, camera_position.vz < -0x1f9dc)) {
				unaff_s2 = 0xb;
			}
		}
	}

	events.camera = 1;

	iVar2 = unaff_s2 + -1;
	if (iVar2 < 10) {
		iVar2 = 10;
	}

	iVar3 = 0;

	while (true)
	{
		if (unaff_s2 + 1 < iVar2) 
		{
			events.camera = 0;
			return iVar5;
		}

		if (iVar2 == 0x10)
			break;

		if (unaff_s2 != iVar2)
		{
			iVar3 = 200;
		}

		events.draw = iVar2;
		current->ot = current->ot + iVar3;
		(*func)(param);

		iVar4 = iVar3;
		if (iVar3 != 0) 
		{
			iVar4 = 0;
			current->ot = current->ot + iVar3 * 0x3fffffff;
		}

		iVar2 = iVar2 + 1;
		iVar3 = iVar4;
	}

	events.camera = 0;
	if ((unaff_s2 == 0xf) && (-0x6fd11 < camera_position.vx)) 
	{
		events.camera = 0;
		return iVar5;
	}

	return 1;
}





