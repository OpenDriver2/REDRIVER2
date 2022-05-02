// redriver2_psxpc.cpp
//

#include <SDL_keyboard.h>

#include "platform.h"

#include "driver2.h"
#include "C/main.h"
#include "C/system.h"
#include "C/gamesnd.h"
#include "C/camera.h"
#include "C/cars.h"
#include "C/civ_ai.h"
#include "C/mission.h"
#include "C/cutscene.h"
#include "C/glaunch.h"
#include "C/loadview.h"
#include "C/overlay.h"
#include "C/players.h"
#include "C/time.h"
#include "C/draw.h"
#include "C/pres.h"
#include "C/cosmetic.h"

#include "utils/ini.h"

#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_messagebox.h>

#include "PsyX/PsyX_globals.h"


int(*GPU_printf)(const char *fmt, ...);

bool CtrlModifier;
bool ShiftModifier;
bool AltModifier;

void CheckModifierKeys(int nKey, bool down)
{
	switch (nKey)
	{
	case SDL_SCANCODE_LCTRL:
		CtrlModifier = down;
		break;
	case SDL_SCANCODE_LSHIFT:
		ShiftModifier = down;
		break;
	case SDL_SCANCODE_LALT:
		AltModifier = down;
		break;
	}
}

extern int gDrawDistance;

int cursorX, cursorY, cursorOldX, cursorOldY;
extern int g_FreeCameraEnabled;

void FreeCameraMouseHandler(int x, int y)
{
	if (g_FreeCameraEnabled)
	{
		extern SVECTOR g_FreeCameraRotation;

		int width, height;
		PsyX_GetScreenSize(&width, &height);

		cursorX = x;
		cursorY = y;

		PsyX_SetCursorPosition(width / 2, height / 2);

		g_FreeCameraRotation.vy -= cursorX - cursorOldX;
		g_FreeCameraRotation.vx += cursorY - cursorOldY;

		cursorX = width / 2;
		cursorY = height / 2;

		cursorOldX = cursorX;
		cursorOldY = cursorY;
	}
}

void FreeCameraKeyboardHandler(int nKey, char down)
{
	if (g_FreeCameraEnabled)
	{
		extern int g_FreeCameraControls;
		if (nKey == SDL_SCANCODE_W)
		{
			if (down)
				g_FreeCameraControls |= 0x1;
			else
				g_FreeCameraControls &= ~0x1;
		}
		else if (nKey == SDL_SCANCODE_S)
		{
			if (down)
				g_FreeCameraControls |= 0x2;
			else
				g_FreeCameraControls &= ~0x2;
		}
		else if (nKey == SDL_SCANCODE_A)
		{
			if (down)
				g_FreeCameraControls |= 0x4;
			else
				g_FreeCameraControls &= ~0x4;
		}
		else if (nKey == SDL_SCANCODE_D)
		{
			if (down)
				g_FreeCameraControls |= 0x8;
			else
				g_FreeCameraControls &= ~0x8;
		}
	}

	if(!down)
		return;

	if (nKey == SDL_SCANCODE_F7)
	{
		g_FreeCameraEnabled ^= 1;
		printf("Free camera: %s\n", g_FreeCameraEnabled ? "ON" : "OFF");
	}

	if (nKey == SDL_SCANCODE_L)
	{
		gToggleBeamStrength ^= 1;
		//gSpeedoType ^= 1;
		printf("LightBeams: %s\n", g_FreeCameraEnabled ? "ON" : "OFF");
	}
}

int gShowCollisionDebug = 0;

#if defined(DEBUG_OPTIONS) || defined(_DEBUG)

extern int gDisplayPosition;
extern int gDisplayDrawStats;
int gStopCivCars = 0;

extern void FunkUpDaBGMTunez(int funk);

void GameDebugKeys(int nKey, char down)
{
	CheckModifierKeys(nKey, down);
	FreeCameraKeyboardHandler(nKey, down);

	if (!down)
		return;

	if (nKey == SDL_SCANCODE_1)
	{
		gDisplayPosition ^= 1;
		printf("Position display %s\n", gDisplayPosition ? "ON" : "OFF");
	}
	else if (nKey == SDL_SCANCODE_2)
	{
		gShowCollisionDebug++;
		gShowCollisionDebug %= 5;

		printf("Collision debug: %d\n", gShowCollisionDebug);
	}
	else if (nKey == SDL_SCANCODE_3)
	{
		gDisplayDrawStats ^= 1;
		printf("Stats %s\n", gDisplayDrawStats ? "ON" : "OFF");
	}
	else if (nKey == SDL_SCANCODE_BACKSPACE)
	{
		extern int FastForward;
		FastForward = 1;
	}
#ifdef _DEBUG
	else if (nKey == SDL_SCANCODE_0)
	{
		gStopCivCars ^= 1;
		printf("Civ cars stop %s\n", gStopCivCars ? "ON" : "OFF");
	}
	else if (nKey == SDL_SCANCODE_PAGEUP)
	{
		player[0].cameraCarId++;

		if (player[0].cameraCarId > MAX_CARS - 1)
			player[0].cameraCarId = MAX_CARS - 1;

		printf("Car on camera: %d\n", player[0].cameraCarId);
	}
	else if (nKey == SDL_SCANCODE_PAGEDOWN)
	{
		player[0].cameraCarId--;

		if (player[0].cameraCarId < 0)
			player[0].cameraCarId = 0;

		printf("Car on camera: %d\n", player[0].cameraCarId);
	}
	else if (nKey == SDL_SCANCODE_KP_DIVIDE)
	{
		FunkUpDaBGMTunez(0);
	}
	else if (nKey == SDL_SCANCODE_KP_MULTIPLY)
	{
		FunkUpDaBGMTunez(1);
		extern void CreateRoadblock();
		CreateRoadblock();
	}
	else if (nKey == SDL_SCANCODE_KP_PLUS)
	{
		extern LEAD_PARAMETERS LeadValues;

		static bool already = false;
		static bool leadReady = false;
		static int lastmodel = 1;

		/*
			---- LEAD VALUES ----
			500 1000 428 21 885 10 487 2
			700 350 1731 30 320 7 225 3
		*/

		// Find the clue
		LeadValues.tEnd			= 500;	LeadValues.tAvelLimit	= 1000;
		LeadValues.tDist		= 428;	LeadValues.tDistMul		= 21;
		LeadValues.tWidth		= 885;	LeadValues.tWidthMul	= 10;
		LeadValues.tWidth80		= 487;	LeadValues.tWidth80Mul	= 2;

		LeadValues.hEnd			= 700;	LeadValues.dEnd			= 350;
		LeadValues.hDist		= 1731; LeadValues.hDistMul		= 30;
		LeadValues.hWidth		= 320;	LeadValues.hWidthMul	= 7;
		LeadValues.hWidth80		= 225;	LeadValues.hWidth80Mul	= 3;

		CAR_DATA *pCar = &car_data[player[0].playerCarId];

		LONGVECTOR4 startpos = {
			pCar->hd.where.t[0],
			pCar->hd.where.t[1],
			pCar->hd.where.t[2],
		};

		int dir = pCar->hd.direction;
		int offset = 1000 + (pCar->hd.speed * 36);
		int heading = (((dir + 512) & 0xfff) >> 10) + 2 & 3;

		int which = (heading & 1) ? 0 : 2;

		int model = lastmodel;
		int palette = 1;

		if (ShiftModifier)
		{
			// force a special car
			model = MissionHeader->residentModels[4];
			palette = 0;
			lastmodel = model;
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				// horrible randomness
				int newmodel = MissionHeader->residentModels[i];

				if (newmodel == 0 || newmodel == lastmodel)
					continue;

				if (newmodel != model)
				{
					int tmp = CameraCnt % (newmodel + 1);

					if (tmp & 4)
					{
						// rare chance of spawning special car
						model = MissionHeader->residentModels[4];
						palette = 0;
						lastmodel = model;
						break;
					}
					else if (tmp & 3)
					{
						model = newmodel;
						palette = CameraCnt % 6;
						lastmodel = model;
						break;
					}
				}
			}
		}

		// add a little more room
		if (model > 4)
			offset += 250;

		// spawn it in front of us
		if (ABS(dir) >= 750)
		{
			if ((heading >> 1) != 1)
				offset = -offset;
		}

		startpos[which] += offset;

		int slot = CreateStationaryCivCar(dir, 0, 0, &startpos, model, palette, 0);

		if (slot == -1)
		{
			slot = PingInCivCar(15900);
			slot--;
		}

		if (slot != -1)
		{
			char playerid = 0xff;

			InitPlayer((PLAYER *)(player + 1), &car_data[slot], 4, dir, &startpos, model, palette, &playerid);
			already = true;
		}
		else
		{
			requestStationaryCivCar = 1;
		}
	}
	else if (nKey == SDL_SCANCODE_KP_MINUS)
	{
		PingOutAllCivCarsAndCopCars();
	}
#endif
}
#endif

#ifndef USE_CRT_MALLOC
char g_Overlay_buffer[0x50000];		// 0x1C0000
char g_Frontend_buffer[0x60000];	// 0xFB400
char g_Other_buffer[0x50000];		// 0xF3000
char g_Other_buffer2[0x50000];		// 0xE7000
OTTYPE g_OT1[OTSIZE];				// 0xF3000
OTTYPE g_OT2[OTSIZE];				// 0xF7200
char g_PrimTab1[PRIMTAB_SIZE];		// 0xFB400
char g_PrimTab2[PRIMTAB_SIZE];		// 0x119400
char g_SBank_buffer[0x50000];		// 0x180000
char g_Replay_buffer[0x50000];		// 0x1fABBC
#endif

void ParseKeyboardMappings(ini_t* config, char* section, PsyXKeyboardMapping& outMapping)
{
	// since it is configured by default
	const PsyXKeyboardMapping& defaultMapping = g_cfg_keyboardMapping;

	const char* str;

	str = ini_get(config, section, "square");
	outMapping.kc_square = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_square);

	str = ini_get(config, section, "circle");
	outMapping.kc_circle = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_circle);

	str = ini_get(config, section, "triangle");
	outMapping.kc_triangle = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_triangle);

	str = ini_get(config, section, "cross");
	outMapping.kc_cross = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_cross);

	str = ini_get(config, section, "l1");
	outMapping.kc_l1 = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_l1);

	str = ini_get(config, section, "l2");
	outMapping.kc_l2 = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_l2);

	str = ini_get(config, section, "l3");
	outMapping.kc_l3 = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_l3);

	str = ini_get(config, section, "r1");
	outMapping.kc_r1 = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_r1);

	str = ini_get(config, section, "r2");
	outMapping.kc_r2 = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_r2);

	str = ini_get(config, section, "r3");
	outMapping.kc_r3 = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_r3);

	str = ini_get(config, section, "up");
	outMapping.kc_dpad_up = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_dpad_up);

	str = ini_get(config, section, "down");
	outMapping.kc_dpad_down = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_dpad_down);

	str = ini_get(config, section, "left");
	outMapping.kc_dpad_left = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_dpad_left);

	str = ini_get(config, section, "right");
	outMapping.kc_dpad_right = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_dpad_right);

	str = ini_get(config, section, "select");
	outMapping.kc_select = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_select);

	str = ini_get(config, section, "start");
	outMapping.kc_start = PsyX_LookupKeyboardMapping(str, defaultMapping.kc_start);
}

void ParseControllerMappings(ini_t* config, char* section, PsyXControllerMapping& outMapping)
{
	const PsyXControllerMapping& defaultMapping = g_cfg_controllerMapping;

	const char* str;

	str = ini_get(config, section, "square");
	outMapping.gc_square = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_square);

	str = ini_get(config, section, "circle");
	outMapping.gc_circle = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_circle);

	str = ini_get(config, section, "triangle");
	outMapping.gc_triangle = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_triangle);

	str = ini_get(config, section, "cross");
	outMapping.gc_cross = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_cross);

	str = ini_get(config, section, "l1");
	outMapping.gc_l1 = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_l1);

	str = ini_get(config, section, "l2");
	outMapping.gc_l2 = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_l2);

	str = ini_get(config, section, "l3");
	outMapping.gc_l3 = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_l3);

	str = ini_get(config, section, "r1");
	outMapping.gc_r1 = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_r1);

	str = ini_get(config, section, "r2");
	outMapping.gc_r2 = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_r2);

	str = ini_get(config, section, "r3");
	outMapping.gc_r3 = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_r3);

	str = ini_get(config, section, "up");
	outMapping.gc_dpad_up = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_dpad_up);

	str = ini_get(config, section, "down");
	outMapping.gc_dpad_down = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_dpad_down);

	str = ini_get(config, section, "left");
	outMapping.gc_dpad_left = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_dpad_left);

	str = ini_get(config, section, "right");
	outMapping.gc_dpad_right = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_dpad_right);

	str = ini_get(config, section, "select");
	outMapping.gc_select = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_select);

	str = ini_get(config, section, "start");
	outMapping.gc_start = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_start);

	str = ini_get(config, section, "axis_left_x");
	outMapping.gc_axis_left_x = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_axis_left_x);

	str = ini_get(config, section, "axis_left_y");
	outMapping.gc_axis_left_y = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_axis_left_y);

	str = ini_get(config, section, "axis_right_x");
	outMapping.gc_axis_right_x = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_axis_right_x);

	str = ini_get(config, section, "axis_right_y");
	outMapping.gc_axis_right_y = PsyX_LookupGameControllerMapping(str, defaultMapping.gc_axis_right_y);
}

PsyXKeyboardMapping g_kbGameMappings = { 0x123 };
PsyXKeyboardMapping g_kbMenuMappings = { 0x456 };

PsyXControllerMapping g_gcGameMappings = { 0x321 };
PsyXControllerMapping g_gcMenuMappings = { 0x654 };

void SwitchMappings(int menu)
{
	if(menu)
	{
		g_cfg_keyboardMapping = g_kbMenuMappings;
		g_cfg_controllerMapping = g_gcMenuMappings;
	}
	else
	{
		g_cfg_keyboardMapping = g_kbGameMappings;
		g_cfg_controllerMapping = g_gcGameMappings;
	}
}

int main(int argc, char** argv)
{
	ini_t* config;

#ifdef USE_CRT_MALLOC
	_overlay_buffer = (char*)malloc(0x50000);			// 0x1C0000
	_frontend_buffer = (char*)malloc(0x60000);			// 0xFB400
	_other_buffer = (char*)malloc(0x50000);				// 0xF3000
	_other_buffer2 = (char*)malloc(0x50000);			// 0xE7000
	_OT1 = (OTTYPE*)malloc(OTSIZE * sizeof(OTTYPE));	// 0xF3000
	_OT2 = (OTTYPE*)malloc(OTSIZE * sizeof(OTTYPE));	// 0xF7200
	_primTab1 = (char*)malloc(PRIMTAB_SIZE);			// 0xFB400
	_primTab2 = (char*)malloc(PRIMTAB_SIZE);			// 0x119400
	_sbank_buffer = (char*)malloc(0x80000);				// 0x180000
	_replay_buffer = (char*)malloc(0x50000);			// 0x1fabbc
	
#else
	_overlay_buffer = g_Overlay_buffer;		// 0x1C0000
	_frontend_buffer = g_Frontend_buffer;	// 0xFB400
	_other_buffer = g_Other_buffer;			// 0xF3000
	_other_buffer2 = g_Other_buffer2;		// 0xE7000
	_OT1 = g_OT1;							// 0xF3000
	_OT2 = g_OT2;							// 0xF7200
	_primTab1 = g_PrimTab1;					// 0xFB400
	_primTab2 = g_PrimTab2;					// 0x119400
	_sbank_buffer = g_SBank_buffer;			// 0x180000
	_replay_buffer = g_Replay_buffer;		// 0x1fABBC
#endif

#if defined(DEBUG_OPTIONS) || defined(_DEBUG)
	GPU_printf = printf;
#endif // _DEBUG

	
#if 0 // defined(__EMSCRIPTEN__)
	// mount the current folder as a NODEFS instance
	// inside of emscripten
	EM_ASM(
		FS.mkdir('/working');
		FS.mount(NODEFS, {}, '/working1');
	);
#endif

	const char* configFilename = "config.ini";
	const char* cdImageFileName = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-ini"))
		{
			i++;
			configFilename = argv[i];
		}
		else if(!strcmp(argv[i], "-cdimage"))
		{
			i++;
			cdImageFileName = argv[i];
		}
	}

	config = ini_load(configFilename);

	// best distance
	gDrawDistance = 600;

	int windowWidth = 800;
	int windowHeight = 600;
	int screenWidth = 800;
	int screenHeight = 600;
	int fullScreen = 0;
	int vsync = 0;
	int enableFreecamera = 0;

	extern int gUserLanguage;

	if (config)
	{
		extern int gDisableChicagoBridges;
		extern int gContentOverride;
		int newScrZ = gCameraDefaultScrZ;
		const char* dataFolderStr = ini_get(config, "fs", "dataFolder");
		const char* userReplaysStr = ini_get(config, "game", "userChases");

		// [A]
		extern int gSpeedoType;
		extern int gDisplaySpeedo;
		extern int gTextureChoice;
		extern int gDigitChoice;
		extern int gDisplayGears;
		extern int gDisplayRPM;
		extern int gTurnSignalColour;
		extern int gToggleBeamStrength;
		extern int gBigCityMP;
		extern int gHighLODDistance;
		extern int gCarLODDistance;
		extern int gTileLODDistance;
		extern int gSpriteShadowDist;

		if(!cdImageFileName)
			cdImageFileName = ini_get(config, "cdfs", "image");

		InitUserReplays(userReplaysStr);
		
		// configure Psy-X pads
		ini_sget(config, "pad", "pad1device", "%d", &g_cfg_controllerToSlotMapping[0]);
		ini_sget(config, "pad", "pad2device", "%d", &g_cfg_controllerToSlotMapping[1]);

		// configure Psy-X renderer
		ini_sget(config, "render", "windowWidth", "%d", &windowWidth);
		ini_sget(config, "render", "windowHeight", "%d", &windowHeight);
		ini_sget(config, "render", "screenWidth", "%d", &screenWidth);
		ini_sget(config, "render", "screenHeight", "%d", &screenHeight);
		ini_sget(config, "render", "fullscreen", "%d", &fullScreen);
		ini_sget(config, "render", "vsync", "%d", &g_cfg_swapInterval);
		ini_sget(config, "render", "pgxpTextureMapping", "%d", &g_cfg_pgxpTextureCorrection);
		ini_sget(config, "render", "pgxpZbuffer", "%d", &g_cfg_pgxpZBuffer);
		ini_sget(config, "render", "bilinearFiltering", "%d", &g_cfg_bilinearFiltering);

		// configure host game
		ini_sget(config, "game", "drawDistance", "%d", &gDrawDistance);
		ini_sget(config, "game", "dynamicLights", "%d", &gEnableDlights);
		ini_sget(config, "game", "disableChicagoBridges", "%d", &gDisableChicagoBridges);
		ini_sget(config, "game", "fieldOfView", "%d", &newScrZ);
		ini_sget(config, "game", "freeCamera", "%d", &enableFreecamera);
		ini_sget(config, "game", "driver1music", "%d", &gDriver1Music);
		ini_sget(config, "game", "widescreenOverlays", "%d", &gWidescreenOverlayAlign);
		ini_sget(config, "game", "fastLoadingScreens", "%d", &gFastLoadingScreens);
		ini_sget(config, "game", "languageId", "%d", &gUserLanguage);
		ini_sget(config, "game", "overrideContent", "%d", &gContentOverride);
		ini_sget(config, "game", "BigCityMP", "%d", &gBigCityMP);

		// configure game extras [A]
		ini_sget(config,"extras", "ToggleBeamStrength", "%d", & gToggleBeamStrength);
		ini_sget(config, "extras", "SpeedometerType", "%d", &gSpeedoType);
		ini_sget(config, "extras", "DisplaySpeedometer", "%d", &gDisplaySpeedo);
		ini_sget(config, "extras", "DisplayGears", "%d", &gDisplayGears);
		ini_sget(config, "extras", "DisplayRPM", "%d", &gDisplayRPM);
		ini_sget(config, "extras", "AmberSignals", "%d", &gTurnSignalColour);
		ini_sget(config, "extras", "FontChoice", "%d", &gTextureChoice);
		ini_sget(config, "extras", "DigitChoice", "%d", &gDigitChoice);
		ini_sget(config, "extras", "EnvLODDist", "%d", &gHighLODDistance);
		ini_sget(config, "extras", "CarLODDist", "%d", &gCarLODDistance);
		ini_sget(config, "extras", "SpriteShadowDist", "%d", &gSpriteShadowDist);
		ini_sget(config, "extras", "GroundLODDist", "%d", &gTileLODDistance);
		
	
		gCameraDefaultScrZ = MAX(MIN(newScrZ, 384), 128);
		
		if (dataFolderStr)
		{
			strcpy(gDataFolder, dataFolderStr);

			int len = strlen(gDataFolder);
			if (gDataFolder[len - 1] != '\\')
			{
				gDataFolder[len] = '\\';
				gDataFolder[len + 1] = '\0';
			}
		}

#if defined(DEBUG_OPTIONS)
		int unlockAll = 0;
		ini_sget(config, "game", "unlockAll", "%d", &unlockAll);

		if (unlockAll)
		{
			gFurthestMission = 40;
			AvailableCheats.cheat5 = 1;
			AvailableCheats.cheat6 = 1;
			AvailableCheats.cheat7 = 1;
			AvailableCheats.cheat8 = 1;
			AvailableCheats.cheat2 = 1;
			AvailableCheats.cheat11 = 1;
			AvailableCheats.cheat1 = 1;
			AvailableCheats.cheat3 = 1;
			AvailableCheats.cheat4 = 1;
		}
#endif
	}
#ifndef _DEBUG
	if (enableFreecamera)
	{
		g_dbg_gameDebugKeys = FreeCameraKeyboardHandler;
		g_dbg_gameDebugMouse = FreeCameraMouseHandler;
	}
#else

	g_dbg_gameDebugKeys = GameDebugKeys;
	g_dbg_gameDebugMouse = FreeCameraMouseHandler;

#endif

	PsyX_Initialise("REDRIVER2", fullScreen ? screenWidth : windowWidth, fullScreen ? screenHeight : windowHeight, fullScreen);

	char version_info[32];
	GetTimeStamp(version_info);
	PsyX_Log_Info("%s %s (%s)\n", GAME_VERSION, version_info, BUILD_CONFIGURATION_STRING);

	// configure Psy-X CD image reader
	if (cdImageFileName)
		PsyX_CDFS_Init(cdImageFileName, 0, 0);
	
	if (config)
	{
		ParseKeyboardMappings(config, "kbcontrols_game", g_kbGameMappings);
		ParseKeyboardMappings(config, "kbcontrols_menu", g_kbMenuMappings);

		ParseControllerMappings(config, "controls_game", g_gcGameMappings);
		ParseControllerMappings(config, "controls_menu", g_gcMenuMappings);
		
		ini_free(config);
	}

	// start with menu mapping
	SwitchMappings(1);

	redriver2_main(argc, argv);

	DeinitStringMng();

	PsyX_Shutdown();

	return 0;
}
