#include "PSYX_SETUP.H"

#include "PSYX_VERSION.H"
#include "PSYX_GLOBALS.H"
#include "PSYX_PUBLIC.H"

#include "UTIL/CRASHHANDLER.H"

#include "LIBETC.H"
#include "LIBGPU.H"

#include "UTIL/TIMER.H"

//#include <stdio.h>
//#include <string.h>
#if !defined(__ANDROID__)
//#include <thread>
#endif

#include <assert.h>

#define FIXED_TIME_STEP_NTSC		(1.0/60.0)		// 60 FPS clock
#define FIXED_TIME_STEP_PAL			(1.0/50.0)		// 50 FPS clock

#include <stdio.h>
#include <SDL.h>

#include "PSYX_RENDER.H"

SDL_Window* g_window = NULL;

#define SWAP_INTERVAL		1

int g_swapInterval = SWAP_INTERVAL;
int g_enableSwapInterval = 1;

extern SDL_GameController* padHandle[];
extern unsigned char* padData[];

PsyXKeyboardMapping g_keyboard_mapping;

timerCtx_t g_vblTimer;

enum EPsxCounters
{
	PsxCounter_VBLANK,

	PsxCounter_Num
};

volatile int g_psxSysCounters[PsxCounter_Num];

SDL_Thread* g_intrThread = NULL;
SDL_mutex* g_intrMutex = NULL;
volatile bool g_stopIntrThread = false;

extern void(*vsync_callback)(void);

int PsyX_Sys_GetVBlankCount()
{
	if (g_swapInterval == 0)
	{
		// extra speedup.
		// does not affect `vsync_callback` count
		g_psxSysCounters[PsxCounter_VBLANK] += 1;
	}
	
	return g_psxSysCounters[PsxCounter_VBLANK];
}

int intrThreadMain(void* data)
{
	Util_InitHPCTimer(&g_vblTimer);

	do
	{
		// step counters
		{
			const long vmode = GetVideoMode();
			const double timestep = vmode == MODE_NTSC ? FIXED_TIME_STEP_NTSC : FIXED_TIME_STEP_PAL;
			
			double vblDelta = Util_GetHPCTime(&g_vblTimer, 0);

			if (vblDelta > timestep)
			{
				SDL_LockMutex(g_intrMutex);
				
				if (vsync_callback)
					vsync_callback();
				
				SDL_UnlockMutex(g_intrMutex);
				
				// do vblank events
				g_psxSysCounters[PsxCounter_VBLANK]++;
			
				Util_GetHPCTime(&g_vblTimer, 1);
				//SDL_Delay(1);
			}
		}

		// TODO:...
		
	} while (!g_stopIntrThread);

	return 0;
}

static int PsyX_Sys_InitialiseCore()
{
	g_intrThread = SDL_CreateThread(intrThreadMain, "psyX_intr", NULL);

	if (NULL == g_intrThread)
	{
		eprintf("SDL_CreateThread failed: %s\n", SDL_GetError());
		return 0;
	}

	g_intrMutex = SDL_CreateMutex();
	if (NULL == g_intrMutex)
	{
		eprintf("SDL_CreateMutex failed: %s\n", SDL_GetError());
		return 0;
	}

	return 1;
}

static void PsyX_Sys_InitialiseInput()
{
	g_keyboard_mapping.kc_square = SDL_SCANCODE_X;
	g_keyboard_mapping.kc_circle = SDL_SCANCODE_V;
	g_keyboard_mapping.kc_triangle = SDL_SCANCODE_Z;
	g_keyboard_mapping.kc_cross = SDL_SCANCODE_C;

	g_keyboard_mapping.kc_l1 = SDL_SCANCODE_LSHIFT;
	g_keyboard_mapping.kc_l2 = SDL_SCANCODE_LCTRL;
	g_keyboard_mapping.kc_l3 = SDL_SCANCODE_LEFTBRACKET;

	g_keyboard_mapping.kc_r1 = SDL_SCANCODE_RSHIFT;
	g_keyboard_mapping.kc_r2 = SDL_SCANCODE_RCTRL;
	g_keyboard_mapping.kc_r3 = SDL_SCANCODE_RIGHTBRACKET;

	g_keyboard_mapping.kc_dpad_up = SDL_SCANCODE_UP;
	g_keyboard_mapping.kc_dpad_down = SDL_SCANCODE_DOWN;
	g_keyboard_mapping.kc_dpad_left = SDL_SCANCODE_LEFT;
	g_keyboard_mapping.kc_dpad_right = SDL_SCANCODE_RIGHT;

	g_keyboard_mapping.kc_select = SDL_SCANCODE_SPACE;
	g_keyboard_mapping.kc_start = SDL_SCANCODE_RETURN;
}

extern int GR_InitialisePSX();
extern int GR_InitialiseRender(char* windowName, int width, int height, int fullscreen);
extern void GR_Shutdown();
extern void GR_BeginScene();
extern void GR_EndScene();

void PsyX_Initialise(char* windowName, int width, int height, int fullscreen)
{
	eprintf("Initialising Psy-X %d.%d\n", PSYX_MAJOR_VERSION, PSYX_MINOR_VERSION);
	eprintf("Build date: %s:%s\n", PSYX_COMPILE_DATE, PSYX_COMPILE_TIME);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		eprinterr("Failed to initialise SDL\n");
		PsyX_ShutDown();
		return;
	}
	
	if (!GR_InitialiseRender(windowName, width, height, fullscreen))
	{
		eprinterr("Failed to Intialise Window\n");
		PsyX_ShutDown();
		return;
	}

	if (!PsyX_Sys_InitialiseCore())
	{
		eprinterr("Failed to Intialise Psy-X Core.\n");
		PsyX_ShutDown();
		return;
	}

	if (!GR_InitialisePSX())
	{
		eprinterr("Failed to Intialise PSX.\n");
		PsyX_ShutDown();
		return;
	}

	PsyX_Sys_InitialiseInput();
}

void PsyX_GetScreenSize(int& screenWidth, int& screenHeight)
{
	SDL_GetWindowSize(g_window, &screenWidth, &screenHeight);
}

void PsyX_SetCursorPosition(int x, int y)
{
	SDL_WarpMouseInWindow(g_window, x, y);
}

void PsyX_Sys_DoDebugKeys(int nKey, bool down); // forward decl
void PsyX_Sys_DoDebugMouseMotion(int x, int y);
void GR_ResetDevice();

void PsyX_Sys_DoPollEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_CONTROLLERDEVICEADDED:
			padHandle[event.jbutton.which] = SDL_GameControllerOpen(event.cdevice.which);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			SDL_GameControllerClose(padHandle[event.cdevice.which]);
			break;
		case SDL_QUIT:
			PsyX_ShutDown();
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				g_windowWidth = event.window.data1;
				g_windowHeight = event.window.data2;
				GR_ResetDevice();
				break;
			case SDL_WINDOWEVENT_CLOSE:
				PsyX_ShutDown();
				break;
			}
			break;
		case SDL_MOUSEMOTION:

			PsyX_Sys_DoDebugMouseMotion(event.motion.x, event.motion.y);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		{
			int nKey = event.key.keysym.scancode;

			// lshift/right shift
			if (nKey == SDL_SCANCODE_RSHIFT)
				nKey = SDL_SCANCODE_LSHIFT;
			else if (nKey == SDL_SCANCODE_RCTRL)
				nKey = SDL_SCANCODE_LCTRL;
			else if (nKey == SDL_SCANCODE_RALT)
				nKey = SDL_SCANCODE_LALT;

			PsyX_Sys_DoDebugKeys(nKey, (event.type == SDL_KEYUP) ? false : true);
			break;
		}
		}
	}
}

bool begin_scene_flag = false;

bool PsyX_BeginScene()
{
	PsyX_Sys_DoPollEvent();

	if (begin_scene_flag)
		return false;

	assert(!begin_scene_flag);

	GR_BeginScene();

	begin_scene_flag = true;

	return true;
}

void PsyX_EndScene()
{
	if (!begin_scene_flag)
		return;

	assert(begin_scene_flag);
	begin_scene_flag = false;

	GR_EndScene();
	
	GR_StoreFrameBuffer(activeDispEnv.disp.x, activeDispEnv.disp.y, activeDispEnv.disp.w, activeDispEnv.disp.h);

	GR_SwapWindow();
}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
void PsyX_TakeScreenshot()
{
	unsigned char* pixels = new unsigned char[g_windowWidth * g_windowHeight * 4];
	
#if defined(RENDERER_OGL) || defined(OGLES)
	glReadPixels(0, 0, g_windowWidth, g_windowHeight, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
#endif

	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, g_windowWidth, g_windowHeight, 8 * 4, g_windowWidth * 4, 0, 0, 0, 0);

	SDL_SaveBMP(surface, "SCREENSHOT.BMP");
	SDL_FreeSurface(surface);

	delete[] pixels;
}
#endif

GameDebugKeysHandlerFunc gameDebugKeys = NULL;
GameDebugMouseHandlerFunc gameDebugMouse = NULL;
int activeControllers = 0x1;

void PsyX_Sys_DoDebugMouseMotion(int x, int y)
{
	if (gameDebugMouse)
		gameDebugMouse(x, y);
}

void PsyX_Sys_DoDebugKeys(int nKey, bool down)
{
	if (gameDebugKeys)
		gameDebugKeys(nKey, down);

	if (nKey == SDL_SCANCODE_BACKSPACE)
	{
		if (down)
		{
			if (g_swapInterval != 0)
			{
				g_swapInterval = 0;
				GR_ResetDevice();
			}
		}
		else
		{
			if (g_swapInterval != SWAP_INTERVAL)
			{
				g_swapInterval = SWAP_INTERVAL;
				GR_ResetDevice();
			}
		}
	}

	if (!down)
	{
		switch (nKey)
		{
#ifdef _DEBUG
		case SDL_SCANCODE_F1:
			g_wireframeMode ^= 1;
			eprintf("wireframe mode: %d\n", g_wireframeMode);
			break;

		case SDL_SCANCODE_F2:
			g_texturelessMode ^= 1;
			eprintf("textureless mode: %d\n", g_texturelessMode);
			break;

		case SDL_SCANCODE_F3:
			g_emulatorPaused ^= 1;
			break;

		case SDL_SCANCODE_UP:
		case SDL_SCANCODE_DOWN:
			if (g_emulatorPaused)
			{
				g_polygonSelected += (nKey == SDL_SCANCODE_UP) ? 3 : -3;
			}
			break;
		case SDL_SCANCODE_F10:
			eprintf("saving VRAM.TGA\n");
			GR_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, 1);
			break;
#endif
#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
		case SDL_SCANCODE_F12:
			eprintf("Saving screenshot\n");
			PsyX_TakeScreenshot();
			break;
#endif
		case SDL_SCANCODE_F4:

			activeControllers++;
			activeControllers = activeControllers % 4;

			if (activeControllers == 0)
				activeControllers++;

			eprintf("Active keyboard controller: %d\n", activeControllers);
			break;
		case SDL_SCANCODE_F5:
			g_pgxpTextureCorrection ^= 1;
			break;
		case SDL_SCANCODE_F6:
			g_pgxpZBuffer ^= 1;
			break;

		}
	}
}

void PsyX_UpdateInput()
{
	// also poll events here
	PsyX_Sys_DoPollEvent();

	InternalPadUpdates();
}

unsigned int PsyX_CalcFPS()
{
#define FPS_INTERVAL 1.0

	static unsigned int lastTime = SDL_GetTicks();
	static unsigned int currentFps = 0;
	static unsigned int passedFrames = 0;

	passedFrames++;
	if (lastTime < SDL_GetTicks() - FPS_INTERVAL * 1000)
	{
		lastTime = SDL_GetTicks();
		currentFps = passedFrames;
		passedFrames = 0;
	}

	return currentFps;
}

void PsyX_WaitForTimestep(int count)
{
	SDL_LockMutex(g_intrMutex);
	SDL_UnlockMutex(g_intrMutex);
	
#if defined(RENDERER_OGL) || defined(OGLES)
	glFinish(); // best time to complete GPU drawing
#endif
	
	// wait for vblank
	if (g_swapInterval > 0)
	{
		//SDL_Delay(1);
	
		static int swapLastVbl = 0;

		do
		{
		}while (g_psxSysCounters[PsxCounter_VBLANK] - swapLastVbl < count);

		swapLastVbl = g_psxSysCounters[PsxCounter_VBLANK];
	}
}

void PsyX_ShutDown()
{
	// quit vblank thread
	if (g_intrThread)
	{
		g_stopIntrThread = true;

		int returnValue;
		SDL_WaitThread(g_intrThread, &returnValue);
	}

	if (g_intrMutex)
		SDL_DestroyMutex(g_intrMutex);

	GR_Shutdown();

	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

	SDL_DestroyWindow(g_window);
	SDL_Quit();

	exit(0);
}
