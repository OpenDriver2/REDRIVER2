#include "driver2.h"
#include "main.h"

#include "ASM/rndrasm.h"
#include "ASM/d2mapasm.h"

#include "system.h"
#include "pad.h"
#include "sound.h"
#include "fmvplay.h"
#include "E3stuff.h"
#include "gamesnd.h"
#include "scores.h"
#include "glaunch.h"
#include "loadview.h"
#include "replays.h"
#include "event.h"
#include "mission.h"
#include "cutscene.h"
#include "texture.h"
#include "sky.h"
#include "pres.h"
#include "draw.h"
#include "denting.h"
#include "cosmetic.h"
#include "pedest.h"
#include "spool.h"
#include "map.h"
#include "objanim.h"
#include "handling.h"
#include "drivinggames.h"
#include "bomberman.h"
#include "players.h"
#include "ai.h"
#include "civ_ai.h"
#include "cop_ai.h"
#include "camera.h"
#include "overlay.h"
#include "debris.h"
#include "job_fx.h"
#include "director.h"
#include "convert.h"
#include "tile.h"
#include "overmap.h"
#include "motion_c.h"
#include "dr2roads.h"
#include "models.h"
#include "cars.h"
#include "objcoll.h"
#include "mc_snd.h"
#include "felony.h"
#include "leadai.h"
#include "loadsave.h"
#include "Frontend/FEmain.h"
#include "xaplay.h"
#include "shadow.h"
#include "pause.h"
#include "sysclock.h"
#include "platform.h"
#include "state.h"
#include "cutrecorder.h"

int levelstartpos[8][4] = {
	{ 4785, -1024, -223340, 0},
	{ -223276, 2048, -235167, 0},
	{ 230347, -1024, 704030, 0},
	{ 91631, -1024, -347175, 0},

	// what?
	{ 148808, 6163, -112000, 0},
	{ -170000, 6163, 361000, 0},
	{ -10500, -6163, -22144, 0},
	{ -8995, -6163, 63655, 0},
};

XZPAIR gStartPos = { 0 };

enum LevLumpType
{
	// known lumps indexes
	LUMP_MODELS = 1,			// level models
	LUMP_MAP = 2,				// map info

	LUMP_TEXTURENAMES = 5,		// texture name strings

	LUMP_ROADMAP = 7,			// unused lump in Driver 2
	LUMP_ROADS = 8,				// unused lump in Driver 2
	LUMP_JUNCTIONS = 9,			// unused lump in Driver 2
	LUMP_ROADSURF = 10,			// unused lump in Driver 2

	LUMP_MODELNAMES = 12,		// model name strings

	LUMP_ROADBOUNDS = 16,		// unused lump in Driver 2
	LUMP_JUNCBOUNDS = 17,		// unused lump in Driver 2

	LUMP_SUBDIVISION = 20,
	LUMP_LOWDETAILTABLE = 21,	// LOD tables for models
	LUMP_MOTIONCAPTURE = 22,	// motion capture/animation data for peds and Tanner
	LUMP_OVERLAYMAP = 24,		// overlay map
	LUMP_PALLET = 25,			// car palettes
	LUMP_SPOOLINFO = 26,		// level region spooling
	LUMP_CAR_MODELS = 28,		// car models

	LUMP_CHAIR = 33,
	LUMP_TEXTUREINFO = 34,		// texture page info and details (atlases)

	LUMP_LEVELDESC = 35,
	LUMP_LEVELDATA = 36,
	LUMP_LUMPDESC = 37,

	LUMP_STRAIGHTS2 = 40,		// road straights (AI)
	LUMP_CURVES2 = 41,

	LUMP_JUNCTIONS2 = 42,		// previously LUMP_JUNCTIONS2
	LUMP_JUNCTIONS2_NEW = 43,	// Only appear in release Driver2
};

int gStopPadReads = 0;
int gDieWithFade = 0;

int game_over = 0;
int saved_counter = 0;
int saved_leadcar_pos = 0;

int DawnCount = 0;
int current_camera_angle = 2048;

int scr_z = 0;
int FrameCnt = 0;

static int WantPause = 0;
static PAUSEMODE PauseMode = PAUSEMODE_PAUSE;

u_char defaultPlayerModel[2] = { 0 }; // offset 0xAA604
u_char defaultPlayerPalette = 0; // offset 0xAA606

u_int* transparent_buffer;

// system?
int gameinit = 0;
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

// [D] [T]
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

int gDemoLevel = 0;

// [D] [T]
void ProcessLumps(char* lump_ptr, int lump_size)
{
	int quit;

	int lump_type;
	int seg_size;
	int* ptr;

	int numLumps = -1;

	quit = 0;
	do {
		lump_type = *(int*)lump_ptr;
		seg_size = *(int*)(lump_ptr + 4);
		ptr = (int*)(lump_ptr + 8);

		if (lump_type == LUMP_LOWDETAILTABLE)
		{
			printInfo("LUMP_LOWDETAILTABLE: size: %d\n", seg_size);
			ProcessLowDetailTable((char*)ptr, seg_size);
		}
		else if (lump_type == LUMP_CHAIR)
		{
			printInfo("LUMP_CHAIR: size: %d\n", seg_size);
			ProcessChairLump((char*)ptr, seg_size);
		}
		else if (lump_type == LUMP_MOTIONCAPTURE)
		{
			printInfo("LUMP_MOTIONCAPTURE: size: %d\n", seg_size);
			ProcessMotionLump((char*)ptr, seg_size);
			gLoadedMotionCapture = 1;
		}
		else if (lump_type == LUMP_OVERLAYMAP)
		{
			printInfo("LUMP_OVERLAYMAP: size: %d\n", seg_size);
			ProcessOverlayLump((char*)ptr, seg_size);
			gLoadedOverlay = 1;
		}
		else if (lump_type == LUMP_MAP)
		{
			map_lump = (char*)ptr;
		}
		else if (lump_type == LUMP_SPOOLINFO)
		{
			printInfo("LUMP_SPOOLINFO: size: %d\n", seg_size);
			ProcessSpoolInfoLump((char*)ptr, lump_size);
			ProcessMapLump(map_lump, 0);

			// [A] only used in alpha 1.6
			region_buffer_xor = (cells_down >> 5 & 2U | cells_across >> 6 & 1U) << 2;
			sdSelfModifyingCode = sdSelfModifyingCode ^ (sdSelfModifyingCode ^ region_buffer_xor) & 12;
		}
		else if (lump_type == LUMP_CURVES2)
		{
			printInfo("LUMP_CURVES2: size: %d\n", seg_size);
			ProcessCurvesDriver2Lump((char*)ptr, seg_size);
		}
		else if (lump_type == LUMP_TEXTURENAMES)
		{
			printInfo("LUMP_TEXTURENAMES: size: %d\n", seg_size);
#ifndef PSX
			// we need to copy texture names
			texturename_buffer = D_MALLOC(seg_size);
			memcpy(texturename_buffer, ptr, seg_size);
#else
			// we need to copy texture names
			texturename_buffer = (char*)ptr;
#endif
		}
		else if (lump_type == LUMP_PALLET)
		{
			printInfo("LUMP_PALLET: size: %d\n", seg_size);
			palette_lump = (char*)ptr;
		}
		else if (lump_type == LUMP_TEXTUREINFO)
		{
			printInfo("LUMP_TEXTUREINFO: size: %d\n", seg_size);
			ProcessTextureInfo((char*)ptr);
		}
		else if (lump_type == LUMP_STRAIGHTS2)
		{
			printInfo("LUMP_STRAIGHTS2: size: %d\n", seg_size);
			ProcessStraightsDriver2Lump((char*)ptr, seg_size);
		}
		else if (lump_type == LUMP_JUNCTIONS2_NEW)
		{
			int cnt;

			printInfo("LUMP_JUNCTIONS2_NEW: size: %d\n", seg_size);
			ProcessJunctionsDriver2Lump((char*)ptr, seg_size, 0);

			// put junction flags if any
			cnt = 0;

			while (cnt < NumTempJunctions)
			{
				Driver2JunctionsPtr[cnt].flags = Driver2TempJunctionsPtr[cnt];
				cnt++;
			}

			gDemoLevel = 0; // [A]
		}
		else if (lump_type == LUMP_JUNCTIONS2)
		{
			int cnt;

			printInfo("LUMP_JUNCTIONS2: size: %d\n", seg_size);
			ProcessJunctionsDriver2Lump((char*)ptr, seg_size, 1);

			// put junction flags if any
			cnt = 0;

			while (cnt < NumTempJunctions)
			{
				Driver2JunctionsPtr[cnt].flags = Driver2TempJunctionsPtr[cnt];
				cnt++;
			}

			gDemoLevel = 1; // [A]
			gLoadedMotionCapture = 0;
		}
		else if (lump_type == LUMP_JUNCTIONS)
		{
			printInfo("LUMP_JUNCTIONS: size: %d\n", seg_size);
			ProcessJunctionsLump((char*)ptr, seg_size);
		}
		else if (lump_type == LUMP_CAR_MODELS)
		{
			printInfo("LUMP_CAR_MODELS: size: %d\n", seg_size);
			car_models_lump = (char*)ptr;
		}
		else if (lump_type == LUMP_MODELS)
		{
			printInfo("LUMP_MODELS: size: %d\n", seg_size);
			ProcessMDSLump((char*)ptr, seg_size);
			ProcessCarModelLump(car_models_lump, 0);
			
			InitModelNames();

			SetUpEvents(1);
		}
		else if (lump_type == LUMP_ROADMAP)
		{
			printInfo("LUMP_ROADMAP: size: %d\n", seg_size);
			NewProcessRoadMapLump(&roadMapLumpData, (char*)ptr);
		}
		else if (lump_type == LUMP_ROADS)
		{
			printInfo("LUMP_ROADS: size: %d\n", seg_size);
			ProcessRoadsLump((char*)ptr, seg_size);
		}
		else if (lump_type == LUMP_ROADBOUNDS)
		{
			printInfo("LUMP_ROADBOUNDS: size: %d\n", seg_size);
			ProcessRoadBoundsLump((char*)ptr, seg_size);
		}
		else if (lump_type == LUMP_JUNCBOUNDS)
		{
			printInfo("LUMP_JUNCBOUNDS: size: %d\n", seg_size);
			ProcessJuncBoundsLump((char*)ptr, seg_size);
		}
		else if (lump_type == LUMP_SUBDIVISION)
		{
			printInfo("LUMP_SUBDIVISION: size: %d\n", seg_size);
			ProcessSubDivisionLump((char*)ptr, seg_size);
		}
		else if (lump_type == LUMP_ROADSURF)
		{
			printInfo("LUMP_ROADSURF: size: %d\n", seg_size);
		}
		else if (lump_type == LUMP_MODELNAMES)
		{
			printInfo("LUMP_MODELNAMES: size: %d\n", seg_size);
			modelname_buffer = (char*)ptr;
		}
		else if (lump_type == 0xff)
		{
			quit = true;
		}
		else
		{
			printInfo("ERROR - unknown lump type %d\n", lump_type);
			numLumps = lump_type;

			lump_ptr += 4;
			continue;
		}

		lump_ptr = (char*)ptr + ((seg_size + 3) & ~0x3); // aligned to 4-byte boundary

		if (quit)
			return;

		numLumps--;
	} while (numLumps != 0);
}

// [D] [T]
void LoadGameLevel(void)
{
	char* malloc_lump;
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
	loadsectors((char*)_primTab1, sector, nsectors);
#else
	extern char g_CurrentLevelFileName[64];
	loadsectorsPC(g_CurrentLevelFileName, (char*)_primTab1, sector, nsectors);
#endif // PSX

	sector += nsectors;

	// CITYLUMP_DATA1 - load-time lump
	ProcessLumps((char*)_primTab1 + 8, nsectors * CDSECTOR_SIZE);
	
	// CITYLUMP_TPAGE is right next after DATA1
	LoadPermanentTPages(&sector);

	sector = citylumps[GameLevel][CITYLUMP_DATA2].x / CDSECTOR_SIZE;
	nsectors = citylumps[GameLevel][CITYLUMP_DATA2].y / CDSECTOR_SIZE;

	D_MALLOC_BEGIN();
	malloc_lump = D_MALLOC(nsectors * CDSECTOR_SIZE);
	D_MALLOC_END();

#ifdef PSX
	loadsectors(malloc_lump, sector, nsectors);
#else
	extern char g_CurrentLevelFileName[64];
	loadsectorsPC(g_CurrentLevelFileName, malloc_lump, sector, nsectors);
#endif // PSX
	sector += nsectors;
	
	// CITYLUMP_DATA2 - in-memory lump
	ProcessLumps(malloc_lump + 8, (nsectors * CDSECTOR_SIZE));	

	SpoolLumpOffset = citylumps[GameLevel][CITYLUMP_SPOOL].x;

	//Init_Reflection_Mapping();	// [A] I know that this is obsolete and used NOWHERE
	InitDebrisNames();
	InitShadow();
	//InitTextureNames();			// [A] I know that this is obsolete and used NOWHERE
	
#if USE_PC_FILESYSTEM
	extern int gContentOverride;

	if (gContentOverride)
	{
		// [A] override textures
		LoadPermanentTPagesFromTIM();
	}
#endif
	
	ReportMode(1);
}

// [D] [T]
void State_GameInit(void* param)
{
	STREAM_SOURCE* plStart;
	int i, musicType;
	char padid;

	if (NewLevel)
	{
#ifdef USE_CRT_MALLOC
		sys_freeall();
		malloctab = D_MALLOC(0x200000);
#endif // USE_CRT_MALLOC
		
		mallocptr = (char*)malloctab;

		// 4 regions, 1024 packed cell pointers
		D_MALLOC_BEGIN();
		packed_cell_pointers = D_MALLOC(1024 * 4);
		D_MALLOC_END();
	}
	else
	{
		SetPleaseWait(NULL);
	}

	gameinit = 1;

	InitGameVariables();
	InitEvents();
	InitPadRecording();
	InitSpeechQueue(&gSpeechQueue);

	if (NewLevel)
	{
		leadAIRequired = 0;
		leadAILoaded = 0;
		pathAILoaded = 0;
	}

	LoadMission(gCurrentMissionNumber);

	if (gCurrentMissionNumber == 38)
		MissionHeader->residentModels[4] = 9;

	if (GameType == GAME_MISSION)
		SetupFadePolys();

	if (NewLevel)
		ShowLoadingScreen(LoadingScreenNames[GameLevel], 1, 36);

	if (AttractMode)
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
#ifdef DEBUG
		printInfo("*---LOCKED P2 CHANS---*\n");
#endif
	}

	if (NewLevel != 0)
	{
		ShowLoading();
		LoadLevelSFX(gCurrentMissionNumber);
	}

	PauseSound();
	ThisMotion = 0;

	// [A] Driver 1 music support
#ifndef PSX
	if (gDriver1Music)
	{
		if (GameType == GAME_TAKEADRIVE)
		{
			if(GameLevel == 0)
				musicType = 0 + (gCurrentMissionNumber & 1);
			else if (GameLevel == 1)
				musicType = 5 + (gCurrentMissionNumber & 1);
			else if (GameLevel == 2)
				musicType = 2 + (gCurrentMissionNumber & 1) * 5;
			else if (GameLevel == 3)
				musicType = 3 + (gCurrentMissionNumber & 1);
		}
		else
		{
			musicType = gCurrentMissionNumber % 8;
		}
	}
	else 
#endif
	if (GameLevel == 1)
	{
		musicType = 1;

		if ((gCurrentMissionNumber & 1U) != 0)
			musicType = 5;
	}
	else if (GameLevel == 0)
	{
		musicType = 2;

		if ((gCurrentMissionNumber & 1U) != 0)
			musicType = 6;
	}
	else if (GameLevel == 2)
	{
		musicType = 0;

		if ((gCurrentMissionNumber & 1U) == 0)
			musicType = 3;
	}
	else if (GameLevel == 3)
	{
		musicType = 4;

		if ((gCurrentMissionNumber & 1U) != 0)
			musicType = 7;
	}

	InitMusic(musicType);

	if (NewLevel == 0)
	{
		if (IconsLoaded == 0)
			ReloadIcons();

		IconsLoaded = 1;
		SetUpEvents(0);
	}
	else
	{
		LoadGameLevel();
		IconsLoaded = 1;
		LoadSky();
		LoadFont(NULL);
	}

	ClearMem((char*)car_data, sizeof(car_data));

	player[0].spoolXZ = (VECTOR*)car_data[0].hd.where.t;
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
	ClearMem((char*)player, sizeof(player));

	InitDrivingGames();
	InitThrownBombs();

	for (i = 0; i < numPlayersToCreate; i++)
	{
		plStart = PlayerStartInfo[i];
		padid = -i;

		gStartOnFoot = (plStart->type == 2);

		if (i < NumPlayers)
			padid = i;

		InitPlayer(&player[i], &car_data[i], plStart->controlType, plStart->rotation, (LONGVECTOR4 *)&plStart->position, plStart->model, plStart->palette, &padid);

		if (!(plStart->type == 2))
		{
			car_data[i].ap.damage[0] = plStart->damage[0];
			car_data[i].ap.damage[1] = plStart->damage[1];
			car_data[i].ap.damage[2] = plStart->damage[2];
			car_data[i].ap.damage[3] = plStart->damage[3];
			car_data[i].ap.damage[4] = plStart->damage[4];
			car_data[i].ap.damage[5] = plStart->damage[5];

			car_data[i].totalDamage = plStart->totaldamage;

			car_data[i].ap.needsDenting = 1;
		}
	}

	if (pathAILoaded)
		InitCops();

	InitCamera(&player[0]);

	if (gLoadedOverlay && NoPlayerControl == 0)
	{
		InitOverlays();
		IconsLoaded = 0;
	}

	SetupRain();
	InitExObjects();

	if (NewLevel)
	{
		// alloc pointer list
		// [A] use model_tile_ptrs for this since it is only used for drawing purposes
		coplist = (CELL_OBJECT**)(model_tile_ptrs);
		pcoplist = (PACKED_CELL_OBJECT**)(model_tile_ptrs + 160);
	}

	if (NoPlayerControl == 0)
	{
		if (!_CutRec_IsOn())
			DeleteAllCameras();
	}
	else
	{
		FindNextChange(CameraCnt);
	}

	FrAng = 512;

	if (gWeather == 1)
		wetness = 7000;
	//else if (gWeather == 2)	// [A] addition that I have disabled
	//	wetness = 3000;
	else
		wetness = 0;

	if (gTimeOfDay == 2)
	{
		for ( i = 0; i < MAX_CARS; i++)
			lightsOnDelay[i] = (i * 11);
	}

	tracking_car = 1;

	if (NoPlayerControl == 0)
		StoreGameFlags();

	SetReverbState(0);

	for (i = 0; i < 2; i++)
	{
		player[i].horn.request = 0;
		player[i].horn.time = 0;
		player[i].horn.on = 0;
	}

#if defined(DEBUG) || defined(PSX)
	printInfo("malloctab 0x%08x to 0x%08x (%d bytes) (Final: 0x%08x)\n", &malloctab, mallocptr, mallocptr - malloctab, mallocptr);

	if (mallocptr < malloctab + PSX_MALLOC_SIZE)
		printInfo("COOL: Level fits on blue station by %d bytes!\n", malloctab + PSX_MALLOC_SIZE - mallocptr);
	else
		printWarning("WARNING: Level too big to fit on blue station by %d bytes!\n", mallocptr - (malloctab + PSX_MALLOC_SIZE));
#endif

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

	//-------------------------
	// GameLoop start part

	if (NewLevel)
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
	WantPause = 0;
	gDrawPauseMenus = 0;

	SpoolSYNC();

	if (CurrentGameMode != GAMEMODE_DIRECTOR)
		UnPauseSound();

	StartGameSounds();

	SetMasterVolume(gMasterVolume);
	SetXMVolume(gMusicVolume);

	CloseControllers();
	InitControllers();
	VSync(0);

	for (i = 0; i < 5; i++)
	{
		ReadControllers();
		VSync(0);
	}
	
#ifdef PSX
	inittimer(120);
	Clock_SystemStartUp();
#endif

	// switch to STATE_GAMELOOP
	SetState(STATE_GAMELOOP);

#ifndef PSX
	// set to 30 FPS VSync
	PsyX_SetSwapInterval(2);
	PsyX_EnableSwapInterval(1);
#endif
}

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
u_int lead_pad = 0;

int numInactiveCars = 0;
int leadCarId = 0;

VECTOR leadcar_pos;

// [D] [T]
void StepSim(void)
{
	static u_int t0; // offset 0x0
	static char t1; // offset 0x4
	static char t2; // offset 0x5
	static int oldsp; // offset 0x8

	char padAcc;
	short* playerFelony;
	int stream;
	CAR_DATA* cp;
	PLAYER* pl;
	int i, j;
	int car;

	if (gTimeOfDay == 0 || gTimeOfDay == 2)
	{
		DawnCount++;
	}

	SetUpTrafficLightPhase();
	MoveSmashable_object();
	//animate_garage_door();
	StepEvents();
	HandleMission();
	HandleInGameCutscene();
	HandleDrivingGames();

	num_active_cars = 0;

	if (NoPlayerControl && ReplayParameterPtr->RecordingEnd - 2 < CameraCnt)
	{
		ReleaseInGameCutscene();
		pauseflag = 1;
	}

	oldsp = SetSp((u_long)((u_char*)getScratchAddr(0) + 0x3e8)); // i don't know what this does

	lead_pad = (u_int)controller_bits;

	if (player[0].playerCarId < 0)
		playerFelony = &pedestrianFelony;
	else
		playerFelony = &car_data[player[0].playerCarId].felonyRating;

	// control cop roadblocks
	if (*playerFelony <= FELONY_ROADBLOCK_MIN_VALUE || numRoadblockCars != 0)
	{
		if (roadblockCount != 0)
		{
			roadblockCount--;
		}
	}
	else
	{
		if (roadblockCount != 0)
		{
			roadblockCount--;
		}
		else
		{
			if (copsAreInPursuit != 0 && MissionHeader->residentModels[3] == 0 && gCurrentMissionNumber != 26)
				requestRoadblock = 1;

			if (roadblockCount != 0)
				roadblockCount--;
		}
	}

	// control civcars pingin/pingout
	if (requestStationaryCivCar != 1 && requestRoadblock == 0)
	{
		if (gInGameChaseActive || _CutRec_IsPlaying())
		{
			// it will use ping buffer
			// checks are done internally
			for (i = 0; i < 10; i++)
				PingInCivCar(15900);
		}
		else if (numCivCars < maxCivCars && (NumPlayers == 1 || (NumPlayers == 2 && GameType == GAME_COPSANDROBBERS)))
		{
			// make 5 tries
			for (i = 0; i < 5; i++)
			{
				if (PingInCivCar(15900))
					break;
			}
		}

		SetUpCivCollFlags();
	}
	else
	{
		distFurthestCivCarSq = 0;
	}

	numRoadblockCars = 0;
	numInactiveCars = 0;
	numParkedCars = 0;
	numActiveCops = 0;
	numCopCars = 0;
	numCivCars = 0;

	cp = car_data;

	// count cars
	while (cp < &car_data[MAX_CARS])
	{
		if (cp->controlType == CONTROL_TYPE_CIV_AI)
		{
			numCivCars++;

			if (cp->controlFlags & CONTROL_FLAG_COP)
				numCopCars++;

			if (cp->ai.c.thrustState == 3 && cp->ai.c.ctrlState == 5)
				numParkedCars++;

			if (cp->controlFlags & CONTROL_FLAG_COP_SLEEPING)
				numRoadblockCars++;
		}
		else if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
		{
			numCopCars++;

			if (cp->ai.p.dying == 0)
			{
				numActiveCops++;
			}
		}
		else if (cp->controlType == CONTROL_TYPE_NONE)
		{
			numInactiveCars++;
		}

		cp++;
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

	// update cars
	cp = car_data;
	while (cp < &car_data[MAX_CARS])
	{
		switch (cp->controlType)
		{
			case CONTROL_TYPE_PLAYER:
				t0 = Pads[*cp->ai.padid].mapped;	// [A] padid might be wrong
				t1 = Pads[*cp->ai.padid].mapanalog[2];
				t2 = Pads[*cp->ai.padid].type & 4;

				// [A] handle REDRIVER2 dedicated car exit button
				if(t0 & CAR_PAD_LEAVECAR_DED)
				{
					t0 &= ~CAR_PAD_LEAVECAR_DED;
					t0 |= CAR_PAD_LEAVECAR;
				}

				if (NoPlayerControl == 0)
				{
					if (gStopPadReads)
					{
						t0 = CAR_PAD_BRAKE;

						if (cp->hd.wheel_speed <= 0x9000)
							t0 = CAR_PAD_HANDBRAKE;

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
			case CONTROL_TYPE_CIV_AI:
				CivControl(cp);
				break;
			case CONTROL_TYPE_PURSUER_AI:
				CopControl(cp);
				break;
			case CONTROL_TYPE_LEAD_AI:
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
			case CONTROL_TYPE_CUTSCENE:
				if (!_CutRec_RecordPad(cp, &t0, &t1, &t2))
					cjpPlay(-*cp->ai.padid, &t0, &t1, &t2);
			
				ProcessCarPad(cp, t0, t1, t2);
		}

		StepCarPhysics(cp);
		cp++;
	}

	// Update players
	for (i = 0; i < MAX_PLAYERS; i++)
	{
		pl = &player[i];

		if (pl->playerType != 2)
			continue;

		stream = pl->padid;

		if (stream < 0)
		{
			if (cjpPlay(-stream, &t0, &t1, &t2) != 0)
				ProcessTannerPad(pl->pPed, t0, t1, t2);
		}
		else
		{
			if (Pads[stream].type == 4)
			{
				padAcc = Pads[stream].mapanalog[3];

				// walk back
				if (padAcc < -64)
				{
					if(padAcc < -100)
						Pads[stream].mapped |= 0x1000;
					else
						Pads[stream].mapped |= 0x1008;
				}
				else if (padAcc > 32)
				{
					stream = pl->padid;
					Pads[stream].mapped |= 0x4000;
				}
			}

			stream = pl->padid;

			t0 = Pads[stream].mapped;
			t1 = Pads[stream].mapanalog[2];
			t2 = Pads[stream].type & 4;

			// [A] handle REDRIVER2 dedicated car entry button
			if (t0 & TANNER_PAD_ACTION_DED)
			{
				t0 &= ~TANNER_PAD_ACTION_DED;
				t0 |= TANNER_PAD_ACTION;
			}

			if (NoPlayerControl == 0)
			{
				if (gStopPadReads)
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

	if (requestStationaryCivCar == 1 && (numCivCars < maxCivCars || (PingOutCar(&car_data[furthestCivID]), numCivCars < maxCivCars)))
	{
		requestStationaryCivCar = 0;
	}

	if (!game_over)
	{
		if(pathAILoaded)
			ControlCops();

		if (gLoadedMotionCapture)
			HandlePedestrians();
	}

	GlobalTimeStep();
	UpdatePlayers();
	DoScenaryCollisions();
	CheckPlayerMiscFelonies();

	SetSp(oldsp);

	CameraCnt++;

	pl = player;

	// deal with car horns
	for (i = 0; i < NumPlayers; i++)
	{
		int playerCarId;

		playerCarId = pl->playerCarId;

		if (playerCarId >= 0)
		{
			if (pl->horn.on == 0)
			{
				if (CarHasSiren(car_data[playerCarId].ap.model) == 0 && pl->pPed == NULL)
				{
					stream = i != 0 ? 5 : 2;
					StopChannel(stream);

					pl->horn.request = 0;
					pl->horn.time = 0;
				}
			}
			else
			{
				int spuKeys;

				spuKeys = SPU_KEYCH(i != 0 ? 5 : 2);

				if (SpuGetKeyStatus(spuKeys) == 0)
				{
					if (CarHasSiren(car_data[pl->playerCarId].ap.model) == 0 && pl->pPed == NULL && pl->horn.request == 0)
						pl->horn.request = 1;

					pl->horn.time = 11;
				}

			}

			DealWithHorn(&pl->horn.request, i);
		}
		pl++;
	}

	SoundTasks();

	static int stupid_logic[4];

	// "Car Bomb"?
	if (gInGameCutsceneActive != 0 && gCurrentMissionNumber == 23 && gInGameCutsceneID == 0)
		stupid_logic[0] = 2;
	else
		stupid_logic[0] = player[0].playerCarId;

	stupid_logic[1] = player[1].playerCarId;
	stupid_logic[2] = gThePlayerCar;
	stupid_logic[3] = leadCarId;

	for (i = 0; i < 3; i++)
	{
		for (j = i+1; j < 4; j++)
		{
			if (stupid_logic[i] == stupid_logic[j])
				stupid_logic[j] = -1;
		}
	}

	for (car = 0, i = 0; car < 4 && i < 2; car++)
	{
		if (stupid_logic[car] != -1 && SilenceThisCar(car) == 0)
		{
			CheckCarEffects(&car_data[stupid_logic[car]], i);
			SwirlLeaves(&car_data[stupid_logic[car]]);
			
			i++;
		}
	}

	// save car positions
	if (gStopPadReads == 1 && lead_car != 0)
	{
		saved_counter++;

		if (saved_counter > 20 && saved_leadcar_pos == 0)
		{
			leadcar_pos.vx = car_data[lead_car].hd.where.t[0];
			leadcar_pos.vy = car_data[lead_car].hd.where.t[1];
			leadcar_pos.vz = car_data[lead_car].hd.where.t[2];

			saved_leadcar_pos = 1;
		}
	}

	// XA playback timeout
	if (gInGameCutsceneActive == 0 && XAPrepared())
	{
		xa_timeout--;

		if (xa_timeout == 0)
		{
			StopXA();
			UnprepareXA();
			StartSpooling();
		}
	}
}

// [A] checks VSync if can time step
int FilterFrameTime()
{
	static int frame = 0;

	// always stay 30 FPS (2 vblanks)
	if (VSync(-1) - frame < 2)
		return 0;

	frame = VSync(-1);

	return 1;
}

// [D] [T]
void StepGame(void)
{
	int i;
	PLAYER* pl;

	if (CameraCnt == 3 && !pauseflag)
		StartXM(gDriver1Music);

	if (doSpooling)
	{
		CheckValidSpoolData();
		ControlMap();
	}

	if (gTimeOfDay == 3)
		PreLampStreak();

	if ((padd & 0x2000U) && (padd & 0x8000U))
		padd &= ~0xA000;

	i = NumPlayers;
	controller_bits = padd;

	pl = player;
	while (i >= 0)
	{
		if (pl->horn.time == 0 || pl->horn.on == 0)
			pl->horn.time = 0;
		else
			pl->horn.time--;

		i--;
		pl++;
	}

	ModifyCamera();

	lis_pos = camera_position;

	// update colours of ambience
	if (gTimeOfDay == 0)
	{
		NightAmbient = (DawnCount >> 7) + 26;
		gLightsOn = (DawnCount < 4000);

		if (NightAmbient > 96)
			NightAmbient = 96;
	}
	else if (gTimeOfDay == 1)
	{
		gLightsOn = 0;

		if (gWeather - 1U > 1)
			NightAmbient = 128;
		else
			NightAmbient = 78;
	}
	else if (gTimeOfDay == 2)
	{
		if (DawnCount < 3000)
		{
			gLightsOn = 0;
		}
		else
		{
			gLightsOn = 1;

			for (i = 0; i < MAX_CARS; i++)
			{
				if (lightsOnDelay[i] > 0)
					lightsOnDelay[i]--;
			}
		}

		if (gWeather - 1U < 2)
			NightAmbient = 78 - (DawnCount >> 7);
		else
			NightAmbient = 96 - (DawnCount >> 5);

		if (NightAmbient < 45)
			NightAmbient = 45;
	}
	else if (gTimeOfDay == 3)
	{
		gLightsOn = 1;
		NightAmbient = 128;
	}

	if (gWeather != 0 && gWeather == 1)
	{
		DoLightning();
		DoThunder();
	}

	HandleExplosion();

	combointensity = NightAmbient | NightAmbient << 8 | NightAmbient << 0x10;

	if (NoPlayerControl && AttractMode == 0)
		ShowReplayOptions();

	// process fast forward
	if (FastForward != 0 && CameraCnt < ReplayParameterPtr->RecordingEnd - 1)
	{
		int color;
		color = CameraCnt & 0x1f;

		if (color > 15)
			color = 32 - color;

		SetTextColour((color & 0x1f) << 3, 0, 0);
		PrintStringFeature(G_LTXT(GTXT_Fastforward), 100, 0x1e, 0x1000, 0x1000, 0);
	}

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

	CameraChanged = 0;
	old_camera_change = camera_change;

	// do camera changes
	if (gInGameCutsceneActive != 0)
		camera_change = CutsceneCameraChange(CameraCnt);
	else if (pauseflag == 0 && NoPlayerControl != 0)
		camera_change = CheckCameraChange(CameraCnt);
	else
		camera_change = 0;

	// step physics engine
	if (pauseflag)
	{
		if (!NoPlayerControl && !AttractMode && !game_over)
		{
			if (pad_connected < 1)
				EnablePause(PAUSEMODE_PADERROR);
			else
				EnablePause(PAUSEMODE_PAUSE);
		}
		else if(quick_replay && !paused)
		{
			WantPause = 1;
			PauseMode = PAUSEMODE_GAMEOVER;
		}

		paused = 1;
	}
	else
	{
		StepSim();
		UpdatePlayerInformation();

		if (FastForward == 0)
			ColourCycle();

		if (gDieWithFade != 0)
			gDieWithFade++;

		if (paused)
		{
			CamerasSaved = 1;
			paused = 0;
		}
	}

	if (NoPlayerControl && AttractMode == 0)
		ControlReplay();

	// player flip cheat
	if (gRightWayUp)
	{
		TempBuildHandlingMatrix(&car_data[player[0].playerCarId], 0);
		gRightWayUp = 0;
	}

	if (AttractMode && (paddp || ReplayParameterPtr->RecordingEnd <= CameraCnt))
		EndGame(GAMEMODE_QUIT);
}

// [D] [T]
void CheckForPause(void)
{
	int ret;

	if (gDieWithFade == 16 && (quick_replay || !NoPlayerControl))
	{
		PauseMode = PAUSEMODE_GAMEOVER;
		WantPause = 1;

		gDieWithFade = 32;
	}

	// check pads for pause here
	if (AttractMode == 0 && pauseflag == 0)
	{
		if (FrameCnt > 2)
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
			else if (NumPlayers == 2 && (Pads[1].dirnew & 0x800))
			{
				EnablePause(PAUSEMODE_PAUSEP2);
			}
		}
	}
	
	if (WantPause)
	{
		WantPause = 0;
		pauseflag = 1;

		PauseSound();
		ShowPauseMenu(PauseMode);
	}

	if (gDrawPauseMenus)
	{
		ret = UpdatePauseMenu(PauseMode);

		switch (ret)
		{
		case MENU_QUIT_CONTINUE:
			pauseflag = 0;
			break;
		case MENU_QUIT_QUIT:
			EndGame(GAMEMODE_QUIT);
			break;
		case MENU_QUIT_RESTART:
			EndGame(GAMEMODE_RESTART);
			break;
		case MENU_QUIT_DIRECTOR:
			EndGame(GAMEMODE_DIRECTOR);
			break;
		case MENU_QUIT_QUICKREPLAY:
			EndGame(GAMEMODE_REPLAY);
			break;
		case MENU_QUIT_NEXTMISSION:
			EndGame(GAMEMODE_NEXTMISSION);
			break;
		}

		if (ret != 0 && !game_over)
		{
			UnPauseSound();
		}
	}
}

#ifdef PSX
int gMultiStep = 0;
#endif

// [D] [T]
void State_GameLoop(void* param)
{
	int cnt;

	if (gSkipInGameCutscene)
	{
		StepGame();
		ClearCurrentDrawBuffers();
		return;
	}

	if (!FilterFrameTime())
		return;

	UpdatePadData();
	CheckForPause();

#ifdef PSX
	static int lastTime32Hz = 0;

	int curTime = clock_realTime.time32Hz;
	int numFrames = curTime - lastTime32Hz;

	// moved from StepGame
	if (FrameCnt == 5)
		SetDispMask(1);

	// game makes 7 frames
	if (FastForward)
		cnt = 7;
	else
		cnt = gMultiStep ? numFrames : 1;

	if (cnt)
		lastTime32Hz = curTime;

	// don't do more than 3 frames in non-fastforward mode
	if (!FastForward && cnt > 3)
		cnt = 0;

	while (--cnt >= 0)
	{
		if(cnt != 0)
			InitCamera(&player[0]);

		StepGame();
	}

	DrawGame();
#else
	// moved from StepGame
	if (FrameCnt == 5)
		SetDispMask(1);

	// game makes 7 frames
	if (FastForward)
		cnt = 7;
	else
		cnt = 1;

	while (--cnt >= 0)
		StepGame();

	_CutRec_Draw();
	DrawGame();
#endif
	
	if (game_over)
		SetState(STATE_GAMECOMPLETE);

	_CutRec_Step();
}

// TODO: DRAW.C?
int ObjectDrawnValue = 0;
int ObjectDrawnCounter = 0;

// [D] [T]
void DrawGame(void)
{
	if (NumPlayers == 1 || NoPlayerControl)
	{
		ObjectDrawnValue = FrameCnt;
		DrawPauseMenus();

		RenderGame2(0);

		ObjectDrawnCounter++;
		
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

		SwapDrawBuffers2(1);
	}

#ifndef PSX
	if (!FadingScreen)
		PsyX_EndScene();
#endif

	FrameCnt++;
}


// [D] [T]
void EndGame(GAMEMODE mode)
{
	WantedGameMode = mode;
	game_over = 1;
}


// [D] [T]
void EnablePause(PAUSEMODE mode)
{
	if (quick_replay == 0 && NoPlayerControl && mode == PAUSEMODE_GAMEOVER)
		return;

	if (!pauseflag)
	{
		WantPause = 1;
		PauseMode = mode;
	}
}

// [D] [T] This is really a Psy-Q function
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

//-------------------------------------------

#if !defined(PSX) && !defined(__EMSCRIPTEN__)
#include <SDL_messagebox.h>
void PrintCommandLineArguments()
{
	const char* argumentsMessage =
		"Example: REDRIVER2 <command> [arguments]\n\n"
		"  -ini <filename.ini> : starts game with specific configuration ini\n"
		"  -cdimage <filename.iso> : starts game with specific ISO/BIN image file\n"
#ifdef DEBUG_OPTIONS
		"  -exportxasubtitles: Exports strings from XA WAV files to SBN\n"
		"  -startpos <x> <z>: Set player start position\n"
		"  -players <count> : Set player count (1 or 2)\n"
		"  -playercar <number>, -player2car <number> : set player wanted car\n"
		"  -chase <number> : using specified chase number for mission\n"
		"  -mission <number> : starts specified mission\n"
#endif // DEBUG_OPTIONS
		"  -replay <filename.d2rp> : starts replay from file\n"
#ifdef CUTSCENE_RECORDER
		"  -recordcutscene <filename> : starts cutscene recording session. Specify INI filename with it\n"
		"  -chaseautotest <filename> : starts chase autotesting. Specify INI filename with it\n"
#endif
		"  -nointro : disable intro screens\n"
		"  -nofmv : disable all FMVs\n";

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "REDRIVER 2 command line arguments", argumentsMessage, NULL);
}
#endif

// [D] [T]
#ifdef PSX

extern "C" u_long memTab_org;
extern "C" u_long mallocTab_org;

// TODO: mapping in Linker script
//volatile u_char _memoryTab_org[0x50400]  __attribute__((aligned(0x10)));						// 0xE7000
//volatile u_char _mallocTab_org[0xD47BC /*0xC37BC*/] __attribute__((aligned(0x10)));				// 0x137400

volatile u_char* _memoryTab_org = (u_char*)&memTab_org;
volatile u_char* _mallocTab_org = (u_char*)&mallocTab_org;

volatile char* _frontend_buffer = NULL;
volatile char* _other_buffer = NULL;
volatile char* _other_buffer2 = NULL;
volatile OTTYPE* _OT1 = NULL;
volatile OTTYPE* _OT2 = NULL;
volatile char* _primTab1 = NULL;
volatile char* _primTab2 = NULL;
volatile char* _overlay_buffer = NULL;
volatile char* _replay_buffer = NULL;
volatile char* _sbank_buffer = NULL;
volatile char* malloctab = NULL;
volatile char* mallocptr = NULL;

int main(void)
#else
int redriver2_main(int argc, char** argv)
#endif // PSX
{
	char** ScreenNames;
	
	char* PALScreenNames[4] = {		// [A] don't show publisher logo
	//	"GFX\\SPLASH2.TIM",
	//	"GFX\\SPLASH3.TIM",
		"GFX\\SPLASH1P.TIM",
		NULL
	};

	char* NTSCScreenNames[4] = {		// [A] don't show publisher logo
	//	"GFX\\SPLASH2.TIM",
		//"GFX\\SPLASH3.TIM",
		"GFX\\SPLASH1N.TIM",
		NULL
	};

	char* OPMScreenNames[4] = {		// [A] don't show publisher logo
		//"GFX\\OPM1.TIM",
		"GFX\\OPM2.TIM",
		"GFX\\OPM3.TIM",
		NULL
	};

	//_stacksize = 0x4000;
	//_ramsize = 0x200000;

#ifdef PSX
	printf("------REDRIVER2 STARTUP------\n");

	volatile u_char* _path_org = &_memoryTab_org[0];				// 0xE7000
	volatile u_char* _otag1_org = &_memoryTab_org[0xC000];			// 0xF3000
	volatile u_char* _otag2_org = &_memoryTab_org[0x10200];			// 0xF7200
	volatile u_char* _primTab1_org = &_memoryTab_org[0x14400];		// 0xFB400
	volatile u_char* _primTab2_org = &_memoryTab_org[0x32400];		// 0x119400
	volatile u_char* _sbnk_org = &_mallocTab_org[0x48C00];			// 0x180000
	volatile u_char* _frnt_org = &_mallocTab_org[0x88C00];			// 0x1C0000
	volatile u_char* _repl_org = &_mallocTab_org[0xC47BC];			// 0x1FABBC

	_frontend_buffer = (char*)_otag1_org;
	_other_buffer = (char*)_otag1_org;
	_other_buffer2 = (char*)_path_org;
	_OT1 = (OTTYPE*)_otag1_org;
	_OT2 = (OTTYPE*)_otag2_org;
	_primTab1 = (char*)_primTab1_org;
	_primTab2 = (char*)_primTab2_org;
	_overlay_buffer = (char*)_frnt_org;
	_replay_buffer = (char*)_repl_org;
	_sbank_buffer = (char*)_sbnk_org;
	malloctab = (char*)_mallocTab_org;

	printf("path_org = %x\n", _path_org); // 0xE7000
	printf("otag1_org = %x\n", _otag1_org); // 0xF3000
	printf("otag2_org = %x\n", _otag2_org); // 0xF7200
	printf("primTab1_org = %x\n", _primTab1_org); // 0xFB400
	printf("primTab2_org = %x\n", _primTab2_org); // 0x119400
	printf("sbnk_org = %x\n", _sbnk_org); // 0x180000
	printf("frnt_org = %x\n", _frnt_org); // 0x1C0000
	printf("repl_org = %x\n", _repl_org); // 0x1FABBC

	printf("malloctab = %x\n", malloctab);
#endif

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
	
	// [A] REDRIVER 2 version auto-detection
	// this is the only difference between the files on CD
#ifdef DEMO_VERSION
	ScreenNames = OPMScreenNames;
#elif NTSC_VERSION
	ScreenNames = NTSCScreenNames;

	if (!FileExists(ScreenNames[0]))
		ScreenNames[0] = PALScreenNames[0];
#elif PAL_VERSION
	ScreenNames = PALScreenNames;

	if (!FileExists(ScreenNames[0]))
		ScreenNames[0] = NTSCScreenNames[0];
#endif

#if !defined(PSX) && !defined(__EMSCRIPTEN__)
	// verify installation
	if (!FileExists("DATA\\FEFONT.BNK") || !FileExists("GFX\\FONT2.FNT"))
	{
		char str[320];
		sprintf(str, "Cannot initialize REDRIVER2\n\nGame files not found by folder '%s'\n", gDataFolder);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR!", str, NULL);
		return -1;
	}

	// init language
	if (!InitStringMng())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR!", "Unable to load language files!\n\nSee console for details", NULL);
		return -1;
	}

	// TODO: divide game by the states, place main loop here.
	
	if (argc <= 1)
#elif !defined(PSX)
	
	InitStringMng();
	
#endif
	{
		//PlayFMV(99);	// [A] don't show publisher logo

		ShowHiresScreens(ScreenNames, 300, 0); // [A]
		PlayFMV(0);		// play intro movie
	}

	CheckForCorrectDisc(0);
	
	// Init frontend
	LOAD_OVERLAY("FRONTEND.BIN", _overlay_buffer);

	SpuSetMute(0);

	// initializes sound system
	LoadSoundBankDynamic(NULL, 0, 0);

	InitialiseScoreTables();

	// by default go to frontend
	SetState(STATE_INITFRONTEND, (void*)2);

	LoadCurrentProfile(1);
	
#ifndef PSX	
	int commandLinePropsShown;
	commandLinePropsShown = 0;

	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-ini") || 
			!strcmp(argv[i], "-cdimage"))
		{
			i++;
		}
		else if (!strcmp(argv[i], "-nofmv"))
		{
			gNoFMV = 1;
		}
		else if (!strcmp(argv[i], "-nointro"))
		{
			// do nothing. All command line features use it
		}
#ifdef DEBUG_OPTIONS
		else if (!strcmp(argv[i], "-exportxasubtitles"))
		{
			extern void StoreXASubtitles();
			StoreXASubtitles();
		}
		else if (!strcmp(argv[i], "-startpos"))
		{
			if (argc - i < 3)
			{
				printError("-startpos missing two number argument!");
				return -1;
			}

			gStartPos.x = atoi(argv[i + 1]);
			gStartPos.z = atoi(argv[i + 2]);

			i += 2;
		}
		else if (!strcmp(argv[i], "-playercar"))
		{
			if (argc - i < 2)
			{
				printError("-playercar missing number argument!");
				return -1;
			}
			wantedCar[0] = atoi(argv[i + 1]);
			i++;
		}
		else if (!strcmp(argv[i], "-player2car"))
		{
			if (argc - i < 2)
			{
				printError("-player2car missing number argument!");
				return -1;
			}
			wantedCar[1] = atoi(argv[i + 1]);
			i++;
		}
		else if (!strcmp(argv[i], "-players"))
		{
			if (argc - i < 2)
			{
				printError("-players missing number argument!");
				return -1;
			}
			NumPlayers = atoi(argv[i + 1]);
			i++;
		}
		else if (!strcmp(argv[i], "-chase"))
		{
			if (argc - i < 2)
			{
				printError("-chase missing number argument!");
				return -1;
			}

			gChaseNumber = atoi(argv[i + 1]);
			i++;
		}
		else if (!strcmp(argv[i], "-mission"))
		{
			if (argc - i < 2)
			{
				printError("-mission missing number argument!");
				return -1;
			}

			SetFEDrawMode();

			gInFrontend = 0;
			AttractMode = 0;

			gCurrentMissionNumber = atoi(argv[i + 1]);
			i++;

			GameType = GAME_TAKEADRIVE;
			SetState(STATE_GAMELAUNCH);
		}
#endif // _DEBUG_OPTIONS
		else if (!strcmp(argv[i], "-replay"))
		{
			if (argc - i < 2)
			{
				printError("-replay missing argument!");
				return -1;
			}

			SetFEDrawMode();

			gInFrontend = 0;
			AttractMode = 0;

			char nameStr[512];
			sprintf(nameStr, "%s", argv[i + 1]);

			FILE* fp = fopen(nameStr, "rb");
			if (fp)
			{
				int replay_size = 0;
				fseek(fp, 0, SEEK_END);
				replay_size = ftell(fp);
				fseek(fp, 0, SEEK_SET);

				fread((char*)_other_buffer, replay_size, 1, fp);
				fclose(fp);

				if (LoadReplayFromBuffer((char*)_other_buffer))
				{
					CurrentGameMode = GAMEMODE_REPLAY;
					gLoadedReplay = 1;
					
					SetState(STATE_GAMELAUNCH);
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
			i++;
		}
#ifdef CUTSCENE_RECORDER
		else if (!strcmp(argv[i], "-chaseautotest"))
		{
			SetFEDrawMode();

			gInFrontend = 0;
			AttractMode = 0;

			InitChaseAutoTest(argv[i+1]);
			i++;
		}
		else if (!strcmp(argv[i], "-recordcutscene"))
		{
			SetFEDrawMode();

			gInFrontend = 0;
			AttractMode = 0;

			InitCutsceneRecorder(argv[i+1]);
			i++;
		}
#endif
		else
		{
#if !defined(PSX) && !defined(__EMSCRIPTEN__)
			if (!commandLinePropsShown)
				PrintCommandLineArguments();
#endif
			commandLinePropsShown = 1;
		}
	}
#endif // PSX

	DoStateLoop();

#ifndef PSX
	SaveCurrentProfile();
#endif

	return 1;
}

// [D] [T]
void FadeScreen(int end_value)
{
	int tmp2;

	tmp2 = pauseflag;

	pauseflag = 1;
	SetupScreenFade(-32, end_value, gFastLoadingScreens ? 128 : 8);
	FadingScreen = 1;

	do {
		RenderGame();
	} while (FadingScreen);

	DrawSync(0);
	SetDispMask(0);

	pauseflag = tmp2;
}


// [D] [T]
void UpdatePlayerInformation(void)
{
	short* playerFelony;
	WHEEL* wheel;
	int i, j;
	int wheelsInWater;
	int wheelsAboveWaterToDieWithFade;
	CAR_DATA* cp;

	cp = NULL;

	PlayerDamageBar.max = MaxPlayerDamage[0];
	Player2DamageBar.max = MaxPlayerDamage[1];

	if (player[0].playerCarId < 0)
		playerFelony = &pedestrianFelony;
	else
		playerFelony = &car_data[player[0].playerCarId].felonyRating;

	if (gPlayerImmune != 0)
		*playerFelony = 0;

	FelonyBar.position = *playerFelony;

	for (i = 0; i < NumPlayers; i++)
	{
		if (player[i].playerType == 1)
		{
			cp = &car_data[player[i].playerCarId];

			if (gInvincibleCar != 0)
			{
				cp->totalDamage = 0;
				ClearMem((char*)cp->ap.damage, sizeof(cp->ap.damage));
			}

			wheelsInWater = 0;
			wheelsAboveWaterToDieWithFade = 0;

			wheel = cp->hd.wheel;

			// [A] count the wheels above the water and in the water
			for (j = 0; j < 4; j++)
			{
				if ((wheel->surface & 7) == 1)
				{
					if (wheel->susCompression == 0)
						wheelsAboveWaterToDieWithFade++;
					else
						wheelsInWater++;
				}

				wheel++;
			}

			// [A] if all wheels above the water surface and we are falling down
			// fade out and end the game
			if(wheelsAboveWaterToDieWithFade > 0 && cp->hd.where.t[1] < -1000 && gDieWithFade == 0)
			{
				// fix for Havana tunnels and Chicago freeway
				if (GameLevel <= 1)
				{
					if(wheelsAboveWaterToDieWithFade == 4)
						gDieWithFade = 1;
				}
				else // car drown as usual
				{
					gDieWithFade = 1;
				}
			}

			if (wheelsInWater == 4) // apply water damage
				cp->totalDamage += MaxPlayerDamage[i] / 80;

			if (cp->totalDamage > MaxPlayerDamage[i])
				cp->totalDamage = MaxPlayerDamage[i];

			if (i == 0)
				PlayerDamageBar.position = cp->totalDamage;
			else
				Player2DamageBar.position = cp->totalDamage;
		}
		else
		{
			if (i == 0)
				PlayerDamageBar.position = 0;
			else
				Player2DamageBar.position = 0;
		}

		// die with fade on mountain race track
		if ((gCurrentMissionNumber > 479 && gCurrentMissionNumber < 482 ||
			gCurrentMissionNumber > 483 && gCurrentMissionNumber < 486) &&
			cp->hd.where.t[1] < -750 && gDieWithFade == 0)
		{
			gDieWithFade = 1;
		}
	}
}

int CurrentPlayerView = 0;

// [D] [T]
void RenderGame2(int view)
{
	POLY_F4* poly;
	int fadeColour;
	int i;
	int notInDreaAndStevesEvilLair;

	CurrentPlayerView = view;
	InitCamera(&player[view]);

#ifndef PSX
	int screenW, screenH;
	PsyX_GetScreenSize(&screenW, &screenH);

	float aspectVar = float(screenH) / float(screenW);

	FrAng = ratan2(160, float(scr_z) * aspectVar * 1.35f);

	extern void DoFreeCamera();
	DoFreeCamera();
#else
	FrAng = ratan2(160, scr_z);
#endif

	Set_Inv_CameraMatrix();
	SetCameraVector();

	SetupDrawMapPSX();
	setupYet = 0;

	if (gLoadedMotionCapture != 0)
		DrawAllPedestrians();

	// do a lot of stuff
	DisplayMissionTitle();
	DrawInGameCutscene();

	// draw events from level itself
	DrawEvents(1);

	Set_Inv_CameraMatrix();
	SetCameraVector();

	SetupDrawMapPSX();
	
	DrawDrivingGames();
	DrawThrownBombs();
	AddGroundDebris();

	// draw events that use cell object
	DrawEvents(0);

	current->ot += 10;

	DrawSmashable_sprites();
	HandleDebris();

	current->ot -= 10;

	DrawAllExplosions();

	if (AttractMode != 0)
	{
		int colour;
		colour = CameraCnt & 0x1f;

		if (colour > 15)
			colour = 32 - colour;

		SetTextColour((colour & 0x1f) << 3, 0, 0);
		PrintString(G_LTXT(GTXT_DEMO), 32, 15);
	}

	for (i = 0; i < 2; i++)
	{
		if (player[i].playerCarId >= 0 &&
			CarHasSiren(car_data[player[i].playerCarId].ap.model) != 0 &&
			player[i].horn.on != 0)
		{
			AddCopCarLight(&car_data[player[i].playerCarId]);
		}
	}

	if (gLoadedOverlay)
		DisplayOverlays();

	DrawMission();

	if (!FastForward && NumPlayers == 1)
		DrawLensFlare();

	// Retro calls this BSOD...
	if (gDieWithFade)
	{
		fadeColour = (gDieWithFade << 4);

		if (gDieWithFade << 4 > 255)
			fadeColour = 255;

		poly = (POLY_F4*)current->primptr;

		setPolyF4(poly);
		setSemiTrans(poly, 1);

		poly->r0 = fadeColour;
		poly->g0 = fadeColour;
		poly->b0 = fadeColour;

#ifdef PSX
		setXYWH(poly, 0, 0, 320, 256);
#else
		setXYWH(poly, -500, 0, 1200, 256);
#endif

		addPrim(current->ot + 8, poly);

		current->primptr += sizeof(POLY_F4);
		POLY_FT3* null = (POLY_FT3*)current->primptr;

		setPolyFT3(null);
		null->x0 = -1;
		null->y0 = -1;
		null->x1 = -1;
		null->y1 = -1;
		null->x2 = -1;
		null->y2 = -1;
		null->tpage = 0x40;

		addPrim(current->ot + 8, null);
		current->primptr += sizeof(POLY_FT3);
	}

	// Steven Adams and Andreas Tawn of Havana team
	notInDreaAndStevesEvilLair = Havana3DOcclusion(DrawMapPSX, (int*)&ObjectDrawnValue);

	if (notInDreaAndStevesEvilLair)
	{		
		DrawSkyDome();

		if (current->primtab - (current->primptr - PRIMTAB_SIZE) > 40000)
		{
			DoWeather(gWeather);
		}
	}

	if (current->primtab - (current->primptr - PRIMTAB_SIZE) > 37000)
	{
		DrawTyreTracks();
	}

	DrawAllTheCars(view);

#ifndef PSX
	extern void DrawDebugOverlays();

	DrawDebugOverlays();
#endif
}


// [D] [T]
void RenderGame(void)
{
	DrawGame(); // [A] was inline
	FadeGameScreen(0);
}

int Havana3DLevelDraw = -1;
int Havana3DLevelMode = -1;			// 0 = uses 1.0 LEV file, 1 = uses v1.1 LEV file

// [D] [T]
void InitGameVariables(void)
{
	InitDebris();
	InitTyreTracks();
	TargetCar = 0;

	if (NewLevel)
	{
		gLoadedOverlay = 0;
		gLoadedMotionCapture = 0;
	}

	gRainCount = 0;

	if (!NoPlayerControl || AttractMode || quick_replay)
		pauseflag = 0;
	else
		pauseflag = 1;

	FastForward = 0;
	game_over = 0;
	saved_counter = 0;
	saved_leadcar_pos = 0;
	gStopPadReads = 0;
	DawnCount = 0;
	variable_weather = 0;
	current_camera_angle = 2048;
	gDieWithFade = 0;

	pedestrianFelony = 0;	// [A] reset pedestrian felony and also cop visibility state
	CopsCanSeePlayer = 0;

	Havana3DLevelDraw = -1;

	srand(0x1234);
	RandomInit(0xd431, 0x350b1);
	FrameCnt = 0;
	CameraCnt = 0;

	ClearMem((char*)&lightsOnDelay, sizeof(lightsOnDelay));

	PlayerStartInfo[0] = &ReplayStreams[0].SourceType;

	if (!_CutRec_InitPlayers())
	{
		ClearMem((char*)PlayerStartInfo[0], sizeof(STREAM_SOURCE));

		PlayerStartInfo[0]->type = 1;
		PlayerStartInfo[0]->model = defaultPlayerModel[0];
		PlayerStartInfo[0]->palette = defaultPlayerPalette;
		PlayerStartInfo[0]->controlType = CONTROL_TYPE_PLAYER;
		PlayerStartInfo[0]->flags = 0;

		PlayerStartInfo[0]->rotation = levelstartpos[GameLevel + (gWantNight * 4)][1];

		PlayerStartInfo[0]->position.vy = 0;
		PlayerStartInfo[0]->position.vx = levelstartpos[GameLevel + (gWantNight * 4)][0];
		PlayerStartInfo[0]->position.vz = levelstartpos[GameLevel + (gWantNight * 4)][2];

		numPlayersToCreate = 1;

		if (NumPlayers == 2)
		{
			PlayerStartInfo[1] = &ReplayStreams[1].SourceType;
			ClearMem((char*)PlayerStartInfo[1], sizeof(STREAM_SOURCE));

			PlayerStartInfo[1]->type = 1;
			PlayerStartInfo[1]->model = defaultPlayerModel[1];
			PlayerStartInfo[1]->palette = defaultPlayerPalette;
			PlayerStartInfo[1]->controlType = CONTROL_TYPE_PLAYER;
			PlayerStartInfo[1]->flags = 0;

			PlayerStartInfo[1]->rotation = levelstartpos[GameLevel][1];

			PlayerStartInfo[1]->position.vy = 0;
			PlayerStartInfo[1]->position.vx = levelstartpos[GameLevel][0] + 600;
			PlayerStartInfo[1]->position.vz = levelstartpos[GameLevel][2];

			numPlayersToCreate = NumPlayers;
		}
	}

	InitCivCars();
}

// [D] [T]
void DealWithHorn(char* hr, int i)
{
	int channel;
	int modelId;
	CAR_DATA* car;

	car = &car_data[player[i].playerCarId];

	if (*hr == 0)
		return;

	if (*hr == 1)
	{
		channel = i != 0 ? 5 : 2;
		StopChannel(channel);
	}
	else if (*hr == 2)
	{
		if (car->ap.model == 4)
			modelId = ResidentModelsBodge();
		else if (car->ap.model < 3)
			modelId = car->ap.model;
		else
			modelId = car->ap.model - 1;

		channel = i != 0 ? 5 : 2;

		Start3DSoundVolPitch(channel, SOUND_BANK_CARS, modelId * 3 + 2,
			car->hd.where.t[0],
			car->hd.where.t[1],
			car->hd.where.t[2], -10000,
			4096);

		if (NumPlayers > 1 && NoPlayerControl == 0)
		{
			channel = i != 0 ? 5 : 2;

			SetPlayerOwnsChannel(channel, i);
		}

		channel = i != 0 ? 5 : 2;

		SetChannelPosition3(channel, 
			(VECTOR*)car->hd.where.t, 
			(LONGVECTOR3*)car->st.n.linearVelocity, 
			-2000, i * 8 + 4096, 0);
	}

	*hr = (*hr + 1) % 3;
}

// [D] [T] [A] Has bugs - some rooms not drawn properly
int Havana3DOcclusion(occlFunc func, int* param)
{
	int loop;
	int draw;
	int otAltered;
	int outside;
	VECTOR tempPos;

#ifndef PSX
	if (gDemoLevel)
	{
		(*func)(param);
		return 1;
	}
#endif

	if (GameLevel == 1 && 
		camera_position.vx <= -430044 && camera_position.vx >= -480278 && 
		camera_position.vz <= -112814 && camera_position.vz >= -134323)
	{
		// TODO: Hardcode into different builds for PSX version
		if(Havana3DLevelMode == -1)
		{
			// try autodetecting
			tempPos.vy = -3823;
			tempPos.vx = -461964;
			tempPos.vz = -124831;

			if (GetSurfaceIndex(&tempPos) + 32 == 27)
				Havana3DLevelMode = 1;
			else
				Havana3DLevelMode = 0;
		}

		if(Havana3DLevelMode == 0)
		{
			// v1.0 method
			outside = 1;
			draw = 10;

			if (camera_position.vy < 447)
			{
				if (camera_position.vx > -469500)
					draw = 17;
				else
					draw = 16;
			}
			else
			{
				outside = 0;

				if (camera_position.vx < -453093 && camera_position.vx > -457217 &&
					camera_position.vz < -123393 && camera_position.vz > -127493 &&
					camera_position.vy < 3955)
				{
					if (camera_position.vy < 1245)
						draw = 15;
					else if (camera_position.vy < 2001)
						draw = 14;
					else if (camera_position.vy < 3071)
						draw = 13;
				}
				else
				{
					draw = 15;
					
					if (camera_position.vy >= 1730)
					{
						draw = 14;

						if (camera_position.vy >= 2500)
						{
							draw = 13;

							if(camera_position.vz < -120000)
							{
								draw = 12;

								// check final room
								if (camera_position.vy >= 3300 && camera_position.vx >= -458108)
									draw = 10;
							}
						}
					}
				}
			}

			events.camera = 1;

			loop = draw - 1;

			if (loop < 10)
				loop = 10;
		}
		else if(Havana3DLevelMode == 1)
		{
			// v1.1 method - simpler one
			outside = 0;

			if (camera_position.vy < 447)
			{
				if (camera_position.vx > -468500)
					draw = 17;
				else
					draw = 16;
			}
			else
			{
				tempPos.vy = -camera_position.vy;
				tempPos.vx = camera_position.vx;
				tempPos.vz = camera_position.vz;

				loop = GetSurfaceIndex(&tempPos);

				if (loop + 32 == 17)
				{
					Havana3DLevelDraw = -1;
					draw = 9;
				}
				else
				{
					if (loop + 7 < 7)
					{
						draw = loop + 32 & 15;

						if (Havana3DLevelDraw == -1)
							goto still_inside;

						loop = Havana3DLevelDraw - draw;

						if (loop < 0)
							loop = draw - Havana3DLevelDraw;

						if (loop < 2)
							goto still_inside;
					}

					outside = 1;
					draw = Havana3DLevelDraw;
				}
			}

			// FIXME: please handle this goto for me
		still_inside:
			if (Havana3DLevelDraw != draw)
				Havana3DLevelDraw = draw;

			events.camera = 1;

			loop = draw - 1;

			if (loop < 9)
				loop = 9;
		}
	
		otAltered = 0;

		while (true)
		{
			if (draw + 1 < loop)
			{
				events.camera = 0;
				return outside;
			}
			
			if (loop == 16) 
				break;
			
			if (draw != loop)
			{
				otAltered = 200;
			}
			
			events.draw = loop;
			current->ot += otAltered;
			
			(*func)(param);

			if (otAltered != 0)
			{
				current->ot -= otAltered;
				otAltered = 0;
			}
			
			loop++;
		}

		events.camera = 0;
	
		if (draw == 15 && camera_position.vx > -458001)
		{
			events.camera = 0;
			return outside;
		}
	
		(*func)(param);
		return 1;
	}

	(*func)(param);

	return 1;
}





