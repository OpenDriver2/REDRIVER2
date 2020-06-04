#include "THISDUST.H"
#include "MAIN.H"

#include "LIBETC.H"
#include "LIBSPU.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
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
#include "COP_AI.H"
#include "GLAUNCH.H"
#include "OBJCOLL.H"
#include "MC_SND.H"
#include "FELONY.H"
#include "LEADAI.H"

#include "XAPLAY.H"
#include "SHADOW.H"

#include "PAUSE.H"

#include <stdlib.h>
#include "STRINGS.H"

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

int HitLeadCar = 0;
int game_over = 0;
int saved_counter = 0;
int saved_leadcar_pos = 0;
int gStopPadReads = 0;
int DawnCount = 0;
int variable_weather = 0;
int current_camera_angle = 0x800;
int gDieWithFade = 0;

int FrameCnt = 0;

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

bool gDriver1Level = false;

void ProcessLumps(char *lump_ptr, int lump_size)
{
	int quit;

	int lump_type;
	DRIVER2_JUNCTION *pDVar8;
	ulong *puVar9;
	int size;
	int *ptr;

	int numLumps = -1;
	gDriver1Level = false;

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
		else if (lump_type == LUMP_ROADBOUNDS)
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
		else
		{
			printf("ERROR - unknown lump type %d... assuming it's Driver 1 level\n", lump_type);
			gDriver1Level = true;
			numLumps = lump_type;

			lump_ptr += 4;
			continue;
		}

		lump_size = size + 3;
		lump_ptr = (char*)ptr + (lump_size & ~0x3); // aligned to 4-byte boundary

		if (quit) 
			return;
		numLumps--;
	} while (numLumps != 0);
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
		if (gTimeOfDay == 3)
			SetCityType(CITYTYPE_NIGHT);
		else 
			SetCityType(CITYTYPE_DAY);
	}
	else 
	{
		if (gTimeOfDay == 3)
			SetCityType(CITYTYPE_MULTI_NIGHT);
		else
			SetCityType(CITYTYPE_MULTI_DAY);
	}

	ReportMode(0);

	sector = citylumps[GameLevel][CITYLUMP_DATA1].x / CDSECTOR_SIZE;
	nsectors = citylumps[GameLevel][CITYLUMP_DATA1].y / CDSECTOR_SIZE;

#ifdef PSX 
	loadsectors(_frontend_buffer, sector, nsectors);
#else
	extern char g_CurrentLevelFileName[64];
	loadsectorsPC(g_CurrentLevelFileName, _frontend_buffer, sector, nsectors);
#endif // PSX

	sector += nsectors;

	// CITYLUMP_DATA1 - load-time lump
	ProcessLumps(_frontend_buffer+8, nsectors * CDSECTOR_SIZE);

	// CITYLUMP_TPAGE is right next after DATA1
	LoadPermanentTPages(&sector);

	sector = citylumps[GameLevel][CITYLUMP_DATA2].x / CDSECTOR_SIZE;
	nsectors = citylumps[GameLevel][CITYLUMP_DATA2].y / CDSECTOR_SIZE;

	MALLOC_BEGIN();
	malloc_lump = D_MALLOC(nsectors * CDSECTOR_SIZE);
	MALLOC_END();

#ifdef PSX
	loadsectors(malloc_lump, sector, nsectors);
#else
	extern char g_CurrentLevelFileName[64];
	loadsectorsPC(g_CurrentLevelFileName, malloc_lump, sector, nsectors);
#endif // PSX
	sector += nsectors;

	// CITYLUMP_DATA2 - in-memory lump
	ProcessLumps(malloc_lump + 8, (nsectors * CDSECTOR_SIZE));

	SpoolLumpOffset = citylumps[GameLevel][CITYLUMP_SPOOL].x; // not used anyway

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

// [D]
void InitModelNames(void)
{
	gHubcapModelPtr = FindModelPtrWithName("HUBCAP1");
	gCleanWheelModelPtr = FindModelPtrWithName("CLEANWHEEL");
	gFastWheelModelPtr = FindModelPtrWithName("FASTWHEEL");
	gDamWheelModelPtr = FindModelPtrWithName("DAMWHEEL");
	gPed1HeadModelPtr = FindModelPtrWithName("PEDHEAD1");
	gPed2HeadModelPtr = FindModelPtrWithName("HEAD");
	gPed3HeadModelPtr = FindModelPtrWithName("HEAD");
	gPed4HeadModelPtr = FindModelPtrWithName("HEAD");

	//gBoxModelPtr = FindModelPtrWithName("CRATE");
	//gRotorPtr = FindModelPtrWithName("ROTOR");
	gTrailblazerConeModel = FindModelPtrWithName("GREENCONE");
	gBombModel = FindModelPtrWithName("BOMB");

	MangleWheelModels();
	InitTanner();
	InitAnimatingObjects();
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

ulong* transparent_buffer;

// system?
int gameinit = 0;
int gMusicType = 0;
int xa_timeout = 0;

int IconsLoaded = 0;

// OVERLAY
int gLoadedOverlay = 0;

// MOTION_C
int gLoadedMotionCapture = 0;

// DRAWGAME.C ???
int FrAng = 0;
int wetness = 0;

extern SPEECH_QUEUE gSpeechQueue;

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
#ifdef PSX
		mallocptr = 0x137400;
#else

#ifdef USE_CRT_MALLOC
		sys_freeall();
		mallocptr_start = D_MALLOC(0x200000);
#else

#endif // USE_CRT_MALLOC
		mallocptr = (char*)mallocptr_start;
#endif // PSX

		MALLOC_BEGIN();
		packed_cell_pointers = D_MALLOC(0x1000);
		MALLOC_END();
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

	if (gCurrentMissionNumber == 38) 
		MissionHeader->residentModels[4] = 9;

	if (GameType == GAME_MISSION) 
		SetupFadePolys();
	
	if (NewLevel != 0)
		ShowLoadingScreen(LoadingScreenNames[GameLevel], 1, 36);

	if (AttractMode != 0) 
	{
		TriggerInGameCutscene(0);
		NoPlayerControl = 1;
	}

	ResetSound();

	LockChannel(0);
	LockChannel(1);
	LockChannel(2);

	if (NumPlayers == 2)
	{
		LockChannel(3);
		LockChannel(4);
		LockChannel(5);
	}

	if (NewLevel != 0)
	{
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
		gMusicType = 2;

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

	if ((NewLevel == 0 || gCarCleanModelPtr[4] == NULL) && allowSpecSpooling == 1) // [A] to load even more secret truck from Chicago
	{
		QuickSpoolSpecial();
	}

	int_garage_door();
	SpoolSYNC();

	InitialiseCarHandling();
	ClearMem((char *)player, sizeof(player));

	InitDrivingGames();
	InitThrownBombs();

	i = 0;
	if (0 < numPlayersToCreate) 
	{
		do {
			pSVar3 = PlayerStartInfo[i];
			padid = -i;

			if (i < NumPlayers) 
				padid = i;

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

#ifdef CUTSCENE_RECORDER
	extern int gCutsceneAsReplay;
	extern int gCutsceneAsReplay_PlayerId;
	if (gCutsceneAsReplay != 0)
	{
		player[0].playerCarId = gCutsceneAsReplay_PlayerId;
		player[0].cameraCarId = gCutsceneAsReplay_PlayerId;
	}
#endif

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
		MALLOC_BEGIN();
		char* mem = D_MALLOC(1024);
		tile_overflow_buffer = (ulong *)mem;
		coplist = (CELL_OBJECT **)mem;

		pcoplist = (PACKED_CELL_OBJECT **)D_MALLOC(1024 + 256);
		//transparent_buffer = D_MALLOC(256);		// [A] unused
		MALLOC_END();
	}

	if (NoPlayerControl == 0) 
	{
#ifdef CUTSCENE_RECORDER
		extern int gCutsceneAsReplay;
		if(gCutsceneAsReplay == 0)
#endif
		DeleteAllCameras();
	}
	else 
	{
		FindNextChange(CameraCnt);
	}

	FrAng = 0x200;

	if (gWeather == 1) 
		wetness = 7000;
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

int num_active_cars = 0;
unsigned long lead_pad = 0;

int numInactiveCars = 0;
int leadCarId = 0;

VECTOR leadcar_pos;

void StepSim(void)
{
	static unsigned long t0; // offset 0x0
	static char t1; // offset 0x4
	static char t2; // offset 0x5
	static int oldsp; // offset 0x8

	char cVar1;
	ushort uVar2;
	short *psVar3;
	int *piVar4;
	//undefined3 extraout_var;
	int stream;
	uint uVar5;
	int *piVar6;
	_CAR_DATA *cp;
	_PLAYER *pl;
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

	if ((NoPlayerControl != 0) && (ReplayParameterPtr->RecordingEnd + -2 < CameraCnt)) 
	{
		ReleaseInGameCutscene();
		pauseflag = 1;
	}

	oldsp = SetSp(0x1f8003e8); // i don't know what this does

	lead_pad = (ulong)controller_bits;

	if ((int)player[0].playerCarId < 0)
	{
		psVar3 = &pedestrianFelony;
	}
	else 
	{
		psVar3 = &car_data[(int)player[0].playerCarId].felonyRating;
	}

	// control cop roadblocks
	if ((*psVar3 < 0x527) || (numRoadblockCars != 0)) 
	{
	LAB_00059c00:
		if (roadblockCount == 0) 
			goto LAB_00059c1c;
	}
	else 
	{
		if (roadblockCount == 0)
		{
			if (((copsAreInPursuit != 0) && (MissionHeader->residentModels[3] == 0)) && (gCurrentMissionNumber != 0x1a)) 
				requestRoadblock = 1;

			goto LAB_00059c00;
		}
	}

	roadblockCount = roadblockCount + -1;

LAB_00059c1c:
	// control civcars pingin/pingout
	if ((requestStationaryCivCar == 1) || (requestRoadblock != 0)) 
	{
		distFurthestCivCarSq = 0;
	}
	else 
	{
		if (gInGameChaseActive == 0) 
		{
			if(numCivCars < maxCivCars && NumPlayers == 1)
			{
				// make 5 tries
				for (i = 0; i < 5; i++)
				{
					if (PingInCivCar(15900))
						break;
				}
			}
		}
		else 
		{
			// ping buffer used to spawn civ cars
			i = 0;
			while (i < 10 && PingBufferPos < 400 && PingBuffer[PingBufferPos].frame <= (CameraCnt - frameStart & 0xffffU))
			{
				PingInCivCar(15900);
				i++;
			}
		}

		SetUpCivCollFlags();
	}

	numRoadblockCars = 0;
	numInactiveCars = 0;
	numParkedCars = 0;
	numActiveCops = 0;
	numCopCars = 0;
	numCivCars = 0;

	if (true) 
	{
		cp = car_data;

		do {
			cVar1 = cp->controlType;

			if (cVar1 == 2) 
			{
				numCivCars++;

				if ((cp->controlFlags & 1) != 0) 
				{
					numCopCars++;
				}

				if (((cp->controlFlags & 2) != 0) && (cp->ai.c.thrustState == 3))
				{
					if (cp->ai.c.ctrlState == 5)
					{
						numParkedCars++;
					}

					if ((cp->controlFlags & 2) != 0) 
					{
						numRoadblockCars++;
					}
				}
			}
			else if (cVar1 == 3)
			{
				numCopCars++;

				if (cp->ai.p.dying == 0)
				{
					numActiveCops++;
				}
			}
			else if (cVar1 == 0)
			{
				numInactiveCars++;
			}

			cp++;
		} while (cp <= &car_data[21]);
	}

	if (numRoadblockCars != 0)
		roadblockCount = roadblockDelay;

	if (requestStationaryCivCar == 0 && requestRoadblock != 0 && numRoadblockCars == 0 && maxCivCars - numCivCars > 4) 
	{
		CreateRoadblock();
	}

	

	if (gInGameCutsceneActive == 0) 
	{
		CheckSpecialSpool();
	}

	cp = car_data;
	while (cp <= &car_data[0x13])
	{
		switch (cp->controlType) 
		{
		case 1:
			t0 = Pads[*cp->ai.padid].mapped;	// [A] padid might be wrong
			t1 = Pads[*cp->ai.padid].mapanalog[2];
			t2 = Pads[*cp->ai.padid].type & 4;

			if (NoPlayerControl == 0) 
			{
				if (gStopPadReads != 0) 
				{
					t0 = 0x80;

					if (cp->hd.wheel_speed < 0x9001)
						t0 = 0x10;

					t1 = 0;
					t2 = 1;
				}

				cjpRecord(*cp->ai.padid, &t0, &t1, &t2);
			}
			else 
			{
				cjpPlay(*cp->ai.padid, &t0, &t1, &t2);
			}

			ProcessCarPad(cp, t0, t1, t2);
			break;
		case 2:
			CivControl(cp);
			break;
		case 3:
			CopControl(cp);
			break;
		case 4:
			t2 = 0;
			t1 = 0;
			t0 = 0;

			t0 = FreeRoamer(cp);

			if (t0 == 0)
			{
				cp->handbrake = 1;
				cp->wheel_angle = 0;
			}
			else 
			{
				ProcessCarPad(cp, t0, t1, t2);
			}

			break;
		case 7:
#ifdef CUTSCENE_RECORDER
			extern int gCutsceneAsReplay;
			extern int gCutsceneAsReplay_PlayerId;

			if (gCutsceneAsReplay != 0 && NoPlayerControl == 0 && cp->id == gCutsceneAsReplay_PlayerId)
			{
				t0 = Pads[0].mapped;	// [A] padid might be wrong
				t1 = Pads[0].mapanalog[2];
				t2 = Pads[0].type & 4;

				if (gStopPadReads != 0)
				{
					t0 = 0x80;

					if (cp->hd.wheel_speed < 0x9001)
						t0 = 0x10;

					t1 = 0;
					t2 = 1;
				}

				cjpRecord(-*cp->ai.padid, &t0, &t1, &t2);
			}
			else
#endif
			cjpPlay(-*cp->ai.padid, &t0, &t1, &t2);
			ProcessCarPad(cp, t0, t1, t2);
		}

		StepCarPhysics(cp);
		cp++;
	}

	for (i = 0; i < 8; i++)
	{
		pl = &player[i];

		if (pl->playerType != 2)
			continue;

		stream = pl->padid;

		if (stream < 0)
		{
			stream = cjpPlay(-stream, &t0, &t1, &t2);

			if (stream != 0)
				ProcessTannerPad(pl->pPed, t0, t1, t2);
		}
		else
		{
			if (Pads[stream].type == 4)
			{
				cVar1 = Pads[stream].mapanalog[3];

				if ((cVar1 < -64) && (-100 < cVar1))
				{
					Pads[stream].mapped = Pads[stream].mapped | 0x1008;
				}
				else if ((cVar1 < -100) && (127 < cVar1))
				{
					stream = pl->padid;
					Pads[stream].mapped = Pads[stream].mapped | 0x1000;
				}
				else if (cVar1 > 32)
				{
					stream = pl->padid;
					Pads[stream].mapped = Pads[stream].mapped | 0x4000;
				}
			}

			stream = pl->padid;

			t0 = Pads[stream].mapped;
			t1 = Pads[stream].mapanalog[2];
			t2 = Pads[stream].type & 4;

			if (NoPlayerControl == 0)
			{
				if (gStopPadReads != 0)
				{
					t2 = 0;
					t1 = 0;
					t0 = 0;
				}

				cjpRecord(stream, &t0, &t1, &t2);
			}
			else
			{
				if (cjpPlay(stream, &t0, &t1, &t2) == 0)
					continue;
			}

			ProcessTannerPad(pl->pPed, t0, t1, t2);
		}
	}

	if (requestStationaryCivCar == 1 && (numCivCars < maxCivCars || (PingOutCar(car_data + furthestCivID), numCivCars < maxCivCars))) 
	{
		requestStationaryCivCar = 0;
	}

	if (game_over == 0)
	{
		ControlCops();

		if(gLoadedMotionCapture)
			HandlePedestrians();
	}

	i = 0;

	GlobalTimeStep();
	UpdatePlayers();
	DoScenaryCollisions();
	CheckPlayerMiscFelonies();

	SetSp(oldsp);

	CameraCnt = CameraCnt + 1;
	gBobIndex = gBobIndex + 0x3cU & 0xfff;
	if (NumPlayers != 0)
	{
		car = 0;
		pl = player;
		do {
			if (pl->horn.on == 0) 
			{
			LAB_0005a5b8:
				stream = CarHasSiren(car_data[player[car].playerCarId].ap.model);

				if (stream == 0 && pl->pPed == NULL) 
				{
					stream = 2;
					if (i != 0) 
						stream = 5;

					StopChannel(stream);
					player[car].horn.request = 0;
					player[car].horn.time = 0;
				}
			}
			else 
			{
				uVar5 = 4;

				if (i != 0) 
					uVar5 = 0x20;

				stream = SpuGetKeyStatus(uVar5);

				if (stream == 0) 
				{
					stream = CarHasSiren(car_data[pl->playerCarId].ap.model);

					if (stream == 0 && pl->pPed == NULL && pl->horn.request == 0)
						pl->horn.request = 1;

					pl->horn.time = 11;
				}

			}

			DealWithHorn(&player[car].horn.request, i);

			car++;
			i++;
			pl++;
		} while (i < NumPlayers);
	}

	SoundTasks();

	static int stupid_logic[4];

	if (gInGameCutsceneActive == 0 || gCurrentMissionNumber != 23 || gInGameCutsceneID != 0) 
		stupid_logic[0] = player[0].playerCarId;
	else
		stupid_logic[0] = 2;


	i = 0;
	piVar4 = stupid_logic;

	stupid_logic[1] = player[1].playerCarId;
	stupid_logic[2] = gThePlayerCar;
	stupid_logic[3] = leadCarId;

	do {
		car = i + 1;
		if (car < 4)
		{
			piVar6 = stupid_logic + car;
			do {
				if (*piVar4 == *piVar6)
					*piVar6 = -1;

				car++;
				piVar6++;
			} while (car < 4);
		}
		i = i + 1;
		piVar4 = piVar4 + 1;
	} while (i < 3);

	car = 0;
	i = 0;

	do {
		stream = i;

		if ((stupid_logic[car] != -1) && SilenceThisCar(car) == 0)
		{
			stream = i + 1;
			CheckCarEffects(&car_data[stupid_logic[car]], i);
		}

		car++;
	} while(car < 4 && (i = stream, stream < 2));

	SwirlLeaves(car_data);
	if ((gStopPadReads == 1) && (((lead_car != 0 && (saved_counter = saved_counter + 1, 0x14 < saved_counter)) && (saved_leadcar_pos == 0)))) 
	{
		saved_leadcar_pos = gStopPadReads;
		leadcar_pos.vx = car_data[lead_car].hd.where.t[0];
		leadcar_pos.vy = car_data[lead_car].hd.where.t[1];
		leadcar_pos.vz = car_data[lead_car].hd.where.t[2];
	}

	if (gInGameCutsceneActive == 0 &&
		(((i = xa_timeout, XAPrepared() != 0 && (i = xa_timeout + -1, xa_timeout == 0)) ||
		(xa_timeout = i, xa_timeout == 0))))
	{
		StopXA();
		UnprepareXA();
		StartSpooling();
	}
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

// [D]
void GameLoop(void)
{
	uint uVar1;
	int iVar2;
	static POLY_FT3 buffer[2];
	static POLY_FT3 *null;

	if (NewLevel != 0)
	{
#ifdef PSX
		CloseShutters(2, 320, 512);
#else
		CloseShutters(16, 320, 512);
#endif // PSX
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
		ReplayParameterPtr->RecordingEnd = CameraCnt;
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

// [D]
void StepGame(void)
{
	char cVar1;
	int iVar2;
	uint uVar3;
	unsigned char *puVar4;
	_PLAYER *pPVar5;

	if (CameraCnt == 3) 
	{
		StartXM(0);
	}

	if (doSpooling != 0) 
	{
		CheckValidSpoolData();
		ControlMap();
	}

	if (gTimeOfDay == 3) 
		PreLampStreak();

	UpdatePadData();
	if (FrameCnt == 5) 
		SetDispMask(1);

	if ((padd & 0x2000U) != 0 && (padd & 0x8000U) != 0) 
		padd = padd & 0x5fff;

	uVar3 = NumPlayers;
	controller_bits = padd;

	if (NumPlayers != 0)
	{
		pPVar5 = player;
		do {
			if (pPVar5->horn.time == 0 || pPVar5->horn.on == 0)
				pPVar5->horn.time = 0;
			else 
				pPVar5->horn.time--;

			uVar3--;
			pPVar5++;
		} while (uVar3 != 0);
	}

	ModifyCamera();

	lis_pos.vx = camera_position.vx;
	lis_pos.vy = camera_position.vy;
	lis_pos.vz = camera_position.vz;
	lis_pos.pad = camera_position.pad;

#ifndef PSX
	int screenW, screenH;
	Emulator_GetScreenSize(screenW, screenH);

	float aspectVar = float(screenH) / float(screenW);

	FrAng = ratan2(160, float(scr_z) * aspectVar* 1.35f);
	
	aspect.m[0][0] = 5500 * aspectVar;
	aspect.m[0][1] = 0;
	aspect.m[0][2] = 0;

	aspect.m[1][0] = 0;
	aspect.m[1][1] = 4710;
	aspect.m[1][2] = 0;

	aspect.m[2][0] = 0;
	aspect.m[2][1] = 0;
	aspect.m[2][2] = 4096;
	
#else
	FrAng = ratan2(160, scr_z);
#endif

	if ((gTimeInWater == 0) || (gSinkingTimer < 100)) 
	{
		gStopPadReads = 1;
		TargetCar = 0;
		cameraview = 0;
		gSinkingTimer = gSinkingTimer + -1;
		gCameraAngle = gCameraAngle - 0x16U & 0xfff;

		if (gCameraDistance < 1000) 
		{
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

	if (gTimeOfDay == 1)
	{
		gLightsOn = 0;
		iVar2 = 0x4e;

		if (1 < gWeather - 1U) 
			iVar2 = 0x80;

		goto LAB_0005aea0;
	}

	if (gTimeOfDay < 2)
	{
		if (gTimeOfDay == 0)
		{
			NightAmbient = (DawnCount >> 7) + 0x1a;
			gLightsOn = (DawnCount < 4000);
			iVar2 = 0x60;
			if (0x60 < NightAmbient) goto LAB_0005aea0;
		}
	}
	else 
	{
		if (gTimeOfDay == 2) 
		{
			if (DawnCount < 3000) 
			{
				gLightsOn = 0;
			}
			else
			{
				gLightsOn = 1;
				puVar4 = lightsOnDelay;
				do {
					if (*puVar4 != 0)
						*puVar4 = *puVar4 - 1;

					puVar4++;
				} while (puVar4 < lightsOnDelay + sizeof(lightsOnDelay));
			}

			NightAmbient = 0x4e;

			if (gWeather - 1U < 2)
			{
				iVar2 = DawnCount >> 7;
			}
			else
			{
				NightAmbient = 0x60;
				iVar2 = DawnCount >> 5;
			}

			NightAmbient = NightAmbient - iVar2;
			iVar2 = 0x2d;

			if (NightAmbient < 0x2d)
				goto LAB_0005aea0;
		}
		else 
		{
			if (gTimeOfDay == 3) 
			{
				gLightsOn = 1;
				iVar2 = 0x80;
			LAB_0005aea0:
				NightAmbient = iVar2;
			}
		}
	}
	if ((gWeather != 0) && (gWeather == 1)) 
	{
		DoLightning();
		DoThunder();
	}

	HandleExplosion();

	if (FastForward == 0)
		ColourCycle();

	combointensity = NightAmbient | NightAmbient << 8 | NightAmbient << 0x10;

	if ((NoPlayerControl != 0) && (AttractMode == 0))
		ShowReplayOptions();
	
	if ((FastForward != 0) && (uVar3 = CameraCnt & 0x1f, CameraCnt < ReplayParameterPtr->RecordingEnd-1))
	{
		if (0xf < uVar3)
			uVar3 = 0x20 - uVar3;

		SetTextColour((uVar3 & 0x1f) << 3, 0, 0);
		PrintStringFeature("Fast forward", 100, 0x1e, 0x1000, 0x1000, 0);
	}

	if (AttractMode == 0 && pauseflag == 0) 
	{
		//if (NoPlayerControl == 0) 
		{
			if (2 < FrameCnt)
			{
				if (NumPlayers == 1) 
				{
					if (paddp == 0x800 && bMissionTitleFade == 0) // [A] && gInGameCutsceneActive == 0)		// allow pausing during cutscene
					{
						EnablePause(PAUSEMODE_PAUSE);
					}
				}
				else if (paddp == 0x800)
				{
					EnablePause(PAUSEMODE_PAUSEP1);
				}
				else if (NumPlayers == 2 && (Pads[1].dirnew & 0x800) != 0)
				{
					EnablePause(PAUSEMODE_PAUSEP2);
				}
			}
			goto LAB_0005b0a8;
		}
	}
	else 
	{
	LAB_0005b0a8:
		if (NoPlayerControl == 0)
		{
			if (pad_connected < 1 && FrameCnt > 2 && bMissionTitleFade == 0 && gInGameCutsceneActive == 0)
			{
				pauseflag = 1;
				PauseSound();
			}

			if (NoPlayerControl == 0 && NoTextureMemory != 0)
				NoTextureMemory--;
		}
	}

	CameraChanged = 0;
	old_camera_change = camera_change;

	if (pauseflag == 0 && NoPlayerControl != 0) 
	{
		if (gInGameCutsceneActive == 0) 
		{
			camera_change = CheckCameraChange(CameraCnt);
			goto LAB_0005b1e0;
		}
	}
	else {
		if (gInGameCutsceneActive == 0) 
		{
			camera_change = 0;
			goto LAB_0005b1e0;
		}
	}

	camera_change = CutsceneCameraChange(CameraCnt);
LAB_0005b1e0:


	if (pauseflag == 0) 
	{
		StepSim();

		if (gDieWithFade != 0)
		{
			gDieWithFade = gDieWithFade + 1;
		}
		if (paused != 0) 
		{
			CamerasSaved = 1;
			paused = 0;
		}
	}
	else 
	{
		if (NoPlayerControl == 0 && AttractMode == 0 && game_over == 0) 
		{
			if (pad_connected < 1)
				EnablePause(PAUSEMODE_PADERROR);
			else 
				EnablePause(PAUSEMODE_PAUSE);
		}

		paused = 1;
	}

	if (NoPlayerControl != 0 && AttractMode == 0) 
		ControlReplay();
	
	if (gRightWayUp != 0) 
	{
		TempBuildHandlingMatrix(car_data + player[0].playerCarId, 0);
		gRightWayUp = 0;
	}

	if (AttractMode != 0 && (paddp != 0 || ReplayParameterPtr->RecordingEnd <= CameraCnt)) 
		EndGame(GAMEMODE_QUIT);

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

	if ((NumPlayers == 1) || (NoPlayerControl != 0)) 
	{
		ObjectDrawnValue = FrameCnt;
		DrawPauseMenus();
		RenderGame2(0);

		ObjectDrawnCounter++;

		while ((VSync(-1) - frame) < 2);
		frame = VSync(-1);

		SwapDrawBuffers();
	}
	else 
	{
		ObjectDrawnValue = FrameCnt;
		RenderGame2(0);
		ObjectDrawnCounter++;

		SwapDrawBuffers2(0);

		ObjectDrawnValue += 16;
		DrawPauseMenus();
		RenderGame2(1);
		ObjectDrawnCounter++;

		while ((VSync(-1) - frame) < 2);
		frame = VSync(-1);

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
	if (quick_replay != 0 || NoPlayerControl == 0 || mode != PAUSEMODE_GAMEOVER)
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
	if (gDieWithFade > 15 && (quick_replay != 0 || NoPlayerControl == 0)) 
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

// [D]
void SsSetSerialVol(short s_num, short voll, short volr)
{
	SpuCommonAttr attr;

	if ((s_num & 0xffU) == 0)
	{
		attr.mask = 0xc0;
		if (0x7f < voll)
			voll = 0x7f;

		if (0x7f < volr)
			volr = 0x7f;

		attr.cd.volume.left = voll * 0x102;
		attr.cd.volume.right = volr * 0x102;
	}

	if (s_num == 1)
	{
		attr.mask = 0xc00;
		if (0x7f < voll)
			voll = 0x7f;

		if (0x7f < volr)
			volr = 0x7f;

		attr.ext.volume.left = voll * 0x102;
		attr.ext.volume.right = volr * 0x102;
	}

	SpuSetCommonAttr(&attr);
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

// [D]
#ifdef PSX
int main(void)
#else
int redriver2_main(int argc, char** argv)
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

#ifndef PSX
	if(argc <= 1)
#endif
	{
		//PlayFMV(99);	// [A] don't show publisher logo

		ShowHiresScreens(OPMScreenNames, 300, 0); // [A]

		PlayFMV(0);		// play intro movie
	}

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

#ifndef PSX
	for (int i = 0; i < argc; i++)
	{
		if (!_stricmp(argv[i], "-replay"))
		{
			if (argc-i < 2)
			{
				printError("-replay missing argument!");
				return -1;
			}

			SetFEDrawMode();

			gInFrontend = 0;
			AttractMode = 0;

			char nameStr[512];
			sprintf(nameStr, "%s.d2rp", argv[i+1]);

			FILE* fp = fopen(nameStr, "rb");
			if (fp)
			{
				int replay_size = 0;
				fseek(fp, 0, SEEK_END);
				replay_size = ftell(fp);
				fseek(fp, 0, SEEK_SET);

				fread(_other_buffer, replay_size, 1, fp);
				fclose(fp);

				if (LoadReplayFromBuffer(_other_buffer))
				{
					CurrentGameMode = GAMEMODE_REPLAY;
					gLoadedReplay = 1;

					LaunchGame();

					gLoadedReplay = 0;
				}
				else
				{
					printError("Error loading replay file '%s'!\n", nameStr);
				}
			}
			else
			{
				printError("Cannot open replay '%s'!\n", nameStr);
				return -1;
			}
		}
#ifdef CUTSCENE_RECORDER
		if (!_stricmp(argv[i], "-recordcutscene"))
		{
			if (argc-i < 3)
			{
				printWarning("Example: -recordcutscene <mission_number> <base_mission> <player_id>");
				return 0;
			}

			SetFEDrawMode();

			gInFrontend = 0;
			AttractMode = 0;

			int player_id = atoi(argv[i+3]);

			extern int LoadCutsceneAsReplay(int subindex);
			extern int gCutsceneAsReplay;
			extern int gCutsceneAsReplay_PlayerId;

			gCutsceneAsReplay = atoi(argv[i + 1]);			// acts as cutscene mission
			gCurrentMissionNumber = atoi(argv[i + 2]);		// acts as base mission. Some mission requires other base
			gCutsceneAsReplay_PlayerId = atoi(argv[i + 3]);

			if (LoadCutsceneAsReplay(0))
			{
				CurrentGameMode = GAMEMODE_REPLAY;
				gLoadedReplay = 1;

				LaunchGame();

				gLoadedReplay = 0;	
			}
			gCutsceneAsReplay = 0;
			return 1;
		}
#endif
	}
#endif // PSX

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

// [D]
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

// [D]
void UpdatePlayerInformation(void)
{
	short *psVar1;
	int iVar2;
	unsigned char *pbVar3;
	WHEEL *pWVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	_CAR_DATA *cp;

	cp = NULL;
	PlayerDamageBar.max = MaxPlayerDamage[0];
	Player2DamageBar.max = MaxPlayerDamage[1];

	if (player[0].playerCarId < 0)
		psVar1 = &pedestrianFelony;
	else
		psVar1 = &car_data[player[0].playerCarId].felonyRating;

	if (gPlayerImmune != 0) 
		*psVar1 = 0;

	FelonyBar.position = *psVar1;
	if (NumPlayers != 0) 
	{
		iVar2 = 0;
		iVar8 = 0;
		do {

			if (player[iVar8].playerType == 1)
			{
				iVar2 = player[iVar8].playerCarId;
				cp = &car_data[iVar2];

				if (gInvincibleCar != 0)
				{
					cp->totalDamage = 0;
					ClearMem((char *)cp->ap.damage, 0xc);
				}

				iVar6 = 0;
				iVar7 = iVar8 + 1;
				pWVar4 = cp->hd.wheel;
				iVar5 = 3;

				do {
					if ((pWVar4->surface & 7) == 1)
					{
						if (pWVar4->susCompression == 0) 
						{
							if (cp->hd.where.t[1] < -1000 && gDieWithFade == 0)
							{
								gDieWithFade = pWVar4->surface & 7;
							}
						}
						else 
						{
							iVar6++;
						}
					}

					pWVar4++;
					iVar5--;
				} while (-1 < iVar5);

				if (iVar6 == 4) // apply water damage
					cp->totalDamage += MaxPlayerDamage[iVar8] / 80;

				if (MaxPlayerDamage[iVar8] < cp->totalDamage)
					cp->totalDamage = MaxPlayerDamage[iVar8];

				if (iVar8 == 0)
					PlayerDamageBar.position = cp->totalDamage;
				else
					Player2DamageBar.position = cp->totalDamage;
			}
			else 
			{
				iVar7 = iVar8 + 1;
				if (iVar8 == 0)
				{
					PlayerDamageBar.position = 0;
					iVar7 = 1;
				}
				else
				{
					Player2DamageBar.position = 0;
				}
			}

			if (((0x1df < gCurrentMissionNumber) &&
				(((gCurrentMissionNumber < 0x1e2 ||
				((gCurrentMissionNumber < 0x1e6 && (0x1e3 < gCurrentMissionNumber)))) &&
				(cp->hd.where.t[1] < -750)))) && (gDieWithFade == 0))
			{
				gDieWithFade = 1;
			}

			iVar2 = iVar7 << 3;
			iVar8 = iVar7;
		} while (iVar7 < NumPlayers);
	}
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

		if (0xf < uVar3)
			uVar3 = 0x20 - uVar3;

		SetTextColour((uVar3 & 0x1f) << 3, 0, 0);
		PrintString("DEMO", 0x23, 0xf);
	}

	pPVar6 = player;
	iVar7 = 2;

	do {
		if (CarHasSiren(car_data[pPVar6->playerCarId].ap.model) != 0 && (pPVar6->horn.on != 0))
			AddCopCarLight(car_data + pPVar6->playerCarId);
	
		iVar7--;
		pPVar6++;
	} while (-1 < iVar7);

	if (gLoadedOverlay != 0)
		DisplayOverlays();

	DrawMission();

	if (FastForward == 0 && NumPlayers == 1)
		DrawLensFlare();

	uVar4 = (unsigned char)(gDieWithFade << 4);

	if (gDieWithFade != 0) 
	{
		if (0xff < gDieWithFade << 4) 
			uVar4 = -1;

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
		addPrim(pDVar1->ot + 8, poly);

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

		addPrim(pDVar1->ot + 8, null);
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

#ifndef PSX
	extern void DrawDebugOverlays();

	DrawDebugOverlays();
#endif
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

	if (NewLevel != 0) 
	{
		gLoadedOverlay = 0;
		gLoadedMotionCapture = 0;
	}

	gRainCount = 0;

	if (NoPlayerControl == 0 || AttractMode != 0)
		pauseflag = 0;
	else
		pauseflag = 1;

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

	ClearMem((char *)&lightsOnDelay, sizeof(lightsOnDelay));

	PlayerStartInfo[0] = &ReplayStreams[0].SourceType;

#ifdef CUTSCENE_RECORDER
	extern int gCutsceneAsReplay;
	if (gCutsceneAsReplay == 0)
	{
#endif
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

		if (NumPlayers == 2)
		{
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
#ifdef CUTSCENE_RECORDER
	}
	else
	{
		extern int gCutsceneAsReplay_PlayerId;
		extern int gCutsceneAsReplay_PlayerChanged;

		for (int i = 0; i < NumReplayStreams; i++)
		{
			PlayerStartInfo[i] = &ReplayStreams[i].SourceType;
		}

		numPlayersToCreate = NumReplayStreams;
	}
#endif // CUTSCENE_RECORDER


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
	unsigned char bVar1;
	int channel;
	int modelId;
	_CAR_DATA* car;

	channel = player[i].playerCarId;
	car = &car_data[player[i].playerCarId];

	bVar1 = *hr;

	if (bVar1 == 0)
	{
		return;
	}
	else if (bVar1 == 1) 
	{
		channel = 2;

		if (i != 0)
			channel = 5;

		StopChannel(channel);
	}
	else if (bVar1 == 2)
	{
		bVar1 = car->ap.model;

		if (bVar1 == 4)
			modelId = ResidentModelsBodge();
		else if (bVar1 < 3)
			modelId = car->ap.model;
		else
			modelId = car->ap.model - 1;

		channel = 2;

		if (i != 0)
			channel = 5;

		Start3DSoundVolPitch(channel, 3, modelId * 3 + 2,
			car->hd.where.t[0],
			car->hd.where.t[1],
			car->hd.where.t[2], -10000,
			0x1000);

		if ((1 < NumPlayers) && (NoPlayerControl == 0))
		{
			channel = 2;

			if (i != 0)
				channel = 5;

			SetPlayerOwnsChannel(channel, (char)i);
		}

		channel = 2;
		if (i != 0)
			channel = 5;

		SetChannelPosition3(channel, (VECTOR *)car->hd.where.t, car->st.n.linearVelocity, -2000, i * 8 + 0x1000, 0);
	}

	*hr = (*hr+1) % 28;	// [A]
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





