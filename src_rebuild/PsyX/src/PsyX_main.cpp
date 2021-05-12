#include "PsyX_main.h"

#include "PsyX/PsyX_version.h"
#include "PsyX/PsyX_globals.h"
#include "PsyX/PsyX_public.h"
#include "PsyX/util/timer.h"

#include "gpu/PsyX_GPU.h"

#include "platform.h"
#include "util/crash_handler.h"

#include "psx/libetc.h"
#include "psx/libgte.h"
#include "psx/libgpu.h"
#include "psx/libspu.h"

#include <assert.h>
#include <string.h>

#define FIXED_TIME_STEP_NTSC		(1.0/60.0)		// 60 FPS clock
#define FIXED_TIME_STEP_PAL			(1.0/50.0)		// 50 FPS clock

#include <stdio.h>
#include <SDL.h>

#include "PsyX/PsyX_render.h"

#ifdef _WIN32
#include <pla.h>
#endif // _WIN32

#ifdef __EMSCRIPTEN__
int strcasecmp(const char* _l, const char* _r)
{
	const u_char* l = (u_char*)_l, * r = (u_char*)_r;
	for (; *l && *r && (*l == *r || tolower(*l) == tolower(*r)); l++, r++);
	return tolower(*l) - tolower(*r);
}
#elif !defined(_WIN32)
#include <strings.h>
#endif

SDL_Window* g_window = NULL;

#define SWAP_INTERVAL		1

int g_swapInterval = SWAP_INTERVAL;
int g_enableSwapInterval = 1;

PsyXKeyboardMapping g_keyboard_mapping;
PsyXControllerMapping g_controller_mapping;

timerCtx_t g_vblTimer;

enum EPsxCounters
{
	PsxCounter_VBLANK,

	PsxCounter_Num
};

volatile int g_psxSysCounters[PsxCounter_Num];

SDL_Thread* g_intrThread = NULL;
SDL_mutex* g_intrMutex = NULL;
volatile char g_stopIntrThread = 0;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void(*vsync_callback)(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

extern int	PsyX_Pad_InitSystem();
extern void PsyX_Pad_Event_ControllerRemoved(Sint32 deviceId);
extern void PsyX_Pad_Event_ControllerAdded(Sint32 deviceId);

extern int	GR_InitialisePSX();
extern int	GR_InitialiseRender(char* windowName, int width, int height, int fullscreen);

extern void GR_ResetDevice();
extern void GR_Shutdown();
extern void GR_BeginScene();
extern void GR_EndScene();

long g_vmode = -1;
int g_frameSkip = 0;

#ifdef __EMSCRIPTEN__

long g_emIntrInterval = -1;
long g_intrVMode = MODE_NTSC;
double g_emOldDate = 0;

void emIntrCallback(void* userData)
{
	double timestep = g_vmode == MODE_NTSC ? FIXED_TIME_STEP_NTSC : FIXED_TIME_STEP_PAL;

	int newVBlank = (Util_GetHPCTime(&g_vblTimer, 0) / timestep) + g_frameSkip;

	int diff = newVBlank - g_psxSysCounters[PsxCounter_VBLANK];

	while (diff--)
	{
		if (vsync_callback)
			vsync_callback();

		g_psxSysCounters[PsxCounter_VBLANK]++;
	}
}

EM_BOOL emIntrCallback2(double time, void* userData)
{
	emIntrCallback(userData);
	return g_stopIntrThread ? EM_FALSE : EM_TRUE;
}

#endif

long PsyX_Sys_SetVMode(long mode)
{
	long old = g_vmode;
	g_vmode = mode;

#ifdef __EMSCRIPTEN__
	if (old != g_vmode)
	{
		//if(g_emIntrInterval != -1)
		//	emscripten_clear_interval(g_emIntrInterval);
		g_stopIntrThread = 1;

		emscripten_sleep(100);

		g_stopIntrThread = 0;
		emscripten_set_timeout_loop(emIntrCallback2, 1.0, NULL);
	}
#endif

	return old;
}


int PsyX_Sys_GetVBlankCount()
{
	if (g_swapInterval == 0)
	{
		// extra speedup.
		// does not affect `vsync_callback` count
		g_psxSysCounters[PsxCounter_VBLANK] += 1;
		g_frameSkip++;
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
			double timestep = g_vmode == MODE_NTSC ? FIXED_TIME_STEP_NTSC : FIXED_TIME_STEP_PAL;			
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
			}
			
		}

		// TODO:...
		
	} while (!g_stopIntrThread);

	return 0;
}

static int PsyX_Sys_InitialiseCore()
{
#ifdef __EMSCRIPTEN__
	Util_InitHPCTimer(&g_vblTimer);
#else

	g_intrThread = SDL_CreateThread(intrThreadMain, "psyX_intr", NULL);

	if (NULL == g_intrThread)
	{
		eprinterr("SDL_CreateThread failed: %s\n", SDL_GetError());
		return 0;
	}
	
	g_intrMutex = SDL_CreateMutex();
	if (NULL == g_intrMutex)
	{
		eprinterr("SDL_CreateMutex failed: %s\n", SDL_GetError());
		return 0;
	}
#endif
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

	//----------------
	g_controller_mapping.gc_square = SDL_CONTROLLER_BUTTON_X;
	g_controller_mapping.gc_circle = SDL_CONTROLLER_BUTTON_B;
	g_controller_mapping.gc_triangle = SDL_CONTROLLER_BUTTON_Y;
	g_controller_mapping.gc_cross = SDL_CONTROLLER_BUTTON_A;

	g_controller_mapping.gc_l1 = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
	g_controller_mapping.gc_l2 = SDL_CONTROLLER_AXIS_TRIGGERLEFT | CONTROLLER_MAP_FLAG_AXIS;
	g_controller_mapping.gc_l3 = SDL_CONTROLLER_BUTTON_LEFTSTICK;

	g_controller_mapping.gc_r1 = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
	g_controller_mapping.gc_r2 = SDL_CONTROLLER_AXIS_TRIGGERRIGHT | CONTROLLER_MAP_FLAG_AXIS;
	g_controller_mapping.gc_r3 = SDL_CONTROLLER_BUTTON_RIGHTSTICK;

	g_controller_mapping.gc_dpad_up = SDL_CONTROLLER_BUTTON_DPAD_UP;
	g_controller_mapping.gc_dpad_down = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
	g_controller_mapping.gc_dpad_left = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
	g_controller_mapping.gc_dpad_right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;

	g_controller_mapping.gc_select = SDL_CONTROLLER_BUTTON_BACK;
	g_controller_mapping.gc_start = SDL_CONTROLLER_BUTTON_START;

	g_controller_mapping.gc_axis_left_x = SDL_CONTROLLER_AXIS_LEFTX | CONTROLLER_MAP_FLAG_AXIS;
	g_controller_mapping.gc_axis_left_y = SDL_CONTROLLER_AXIS_LEFTY | CONTROLLER_MAP_FLAG_AXIS;
	g_controller_mapping.gc_axis_right_x = SDL_CONTROLLER_AXIS_RIGHTX | CONTROLLER_MAP_FLAG_AXIS;
	g_controller_mapping.gc_axis_right_y = SDL_CONTROLLER_AXIS_RIGHTY | CONTROLLER_MAP_FLAG_AXIS;

	PsyX_Pad_InitSystem();
}

#ifdef __GNUC__
#define _stricmp(s1, s2) strcasecmp(s1, s2)
#endif

// Keyboard mapping lookup
int PsyX_LookupKeyboardMapping(const char* str, int default_value)
{
	const char* scancodeName;
	int i;

	if (str)
	{
		if (!_stricmp("NONE", str))
			return SDL_SCANCODE_UNKNOWN;

		for (i = 0; i < SDL_NUM_SCANCODES; i++)
		{
			scancodeName = SDL_GetScancodeName((SDL_Scancode)i);

			if (strlen(scancodeName) && !_stricmp(scancodeName, str))
			{
				return i;
			}
		}
	}

	return default_value;
}

// Game controller mapping lookup
// Available controller binds(refer to SDL2 game controller)
//
// Axes:
//	leftx lefty
//	rightx righty
//	lefttrigger righttrigger
//
// NOTE: adding `-` before axis names makes it inverse, so `-leftx` inverse left stick X axis
//
// Buttons:
// 	a, b, x, y
// 	back guide start
// 	leftstick rightstick
// 	leftshoulder rightshoulder
// 	dpup dpdown dpleft dpright

int PsyX_LookupGameControllerMapping(const char* str, int default_value)
{
	const char* axisStr;
	const char* buttonOrAxisName;
	int i, axisFlags;

	if (str)
	{
		axisFlags = CONTROLLER_MAP_FLAG_AXIS;
		axisStr = str;

		if (*axisStr == '-')
		{
			axisFlags |= CONTROLLER_MAP_FLAG_INVERSE;
			axisStr++;
		}

		if (!_stricmp("NONE", str))
			return SDL_CONTROLLER_BUTTON_INVALID;

		// check buttons
		for (i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
		{
			buttonOrAxisName = SDL_GameControllerGetStringForButton((SDL_GameControllerButton)i);

			if (strlen(buttonOrAxisName) && !_stricmp(buttonOrAxisName, str))
			{
				return i;
			}
		}

		// Check axes
		for (i = 0; i < SDL_CONTROLLER_AXIS_MAX; i++)
		{
			buttonOrAxisName = SDL_GameControllerGetStringForAxis((SDL_GameControllerAxis)i);

			if (strlen(buttonOrAxisName) && !_stricmp(buttonOrAxisName, axisStr))
			{
				return i | axisFlags;
			}
		}
	}

	return default_value;
}

char* g_appNameStr = NULL;

void PsyX_GetWindowName(char* buffer)
{
#ifdef _DEBUG
	sprintf(buffer, "%s | Debug", g_appNameStr);
#else
	sprintf(buffer, "%s", g_appNameStr);
#endif
}

FILE* g_logStream = NULL;

// intialise logging
void PsyX_Log_Initialise()
{
	char appLogFilename[128];
	sprintf(appLogFilename, "%s.log", g_appNameStr);

	g_logStream = fopen(appLogFilename, "wb");

	if (!g_logStream)
		eprinterr("Error - cannot create log file '%s'\n", appLogFilename);
}

void PsyX_Log_Finalise()
{
	PsyX_Log_Warning("---- LOG CLOSED ----\n");

	if (g_logStream)
		fclose(g_logStream);

	g_logStream = NULL;
}

void PsyX_Log_Flush()
{
	if (g_logStream)
		fflush(g_logStream);
}

// spew types
typedef enum
{
	SPEW_NORM,
	SPEW_INFO,
	SPEW_WARNING,
	SPEW_ERROR,
	SPEW_SUCCESS,
}SpewType_t;

#ifdef _WIN32
static unsigned short g_InitialColor = 0xFFFF;
static unsigned short g_LastColor = 0xFFFF;
static unsigned short g_BadColor = 0xFFFF;
static WORD g_BackgroundFlags = 0xFFFF;
CRITICAL_SECTION g_SpewCS;
char g_bSpewCSInitted = 0;

static void Spew_GetInitialColors()
{
	// Get the old background attributes.
	CONSOLE_SCREEN_BUFFER_INFO oldInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &oldInfo);
	g_InitialColor = g_LastColor = oldInfo.wAttributes & (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	g_BackgroundFlags = oldInfo.wAttributes & (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

	g_BadColor = 0;
	if (g_BackgroundFlags & BACKGROUND_RED)
		g_BadColor |= FOREGROUND_RED;
	if (g_BackgroundFlags & BACKGROUND_GREEN)
		g_BadColor |= FOREGROUND_GREEN;
	if (g_BackgroundFlags & BACKGROUND_BLUE)
		g_BadColor |= FOREGROUND_BLUE;
	if (g_BackgroundFlags & BACKGROUND_INTENSITY)
		g_BadColor |= FOREGROUND_INTENSITY;
}

static WORD Spew_SetConsoleTextColor(int red, int green, int blue, int intensity)
{
	WORD ret = g_LastColor;

	g_LastColor = 0;
	if (red)	g_LastColor |= FOREGROUND_RED;
	if (green) g_LastColor |= FOREGROUND_GREEN;
	if (blue)  g_LastColor |= FOREGROUND_BLUE;
	if (intensity) g_LastColor |= FOREGROUND_INTENSITY;

	// Just use the initial color if there's a match...
	if (g_LastColor == g_BadColor)
		g_LastColor = g_InitialColor;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), g_LastColor | g_BackgroundFlags);
	return ret;
}

static void Spew_RestoreConsoleTextColor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | g_BackgroundFlags);
	g_LastColor = color;
}

void Spew_ConDebugSpew(SpewType_t type, char* text)
{
	// Hopefully two threads won't call this simultaneously right at the start!
	if (!g_bSpewCSInitted)
	{
		Spew_GetInitialColors();
		InitializeCriticalSection(&g_SpewCS);
		g_bSpewCSInitted = 1;
	}

	WORD old;
	EnterCriticalSection(&g_SpewCS);
	{
		if (type == SPEW_NORM)
		{
			old = Spew_SetConsoleTextColor(1, 1, 1, 0);
		}
		else if (type == SPEW_WARNING)
		{
			old = Spew_SetConsoleTextColor(1, 1, 0, 1);
		}
		else if (type == SPEW_SUCCESS)
		{
			old = Spew_SetConsoleTextColor(0, 1, 0, 1);
		}
		else if (type == SPEW_ERROR)
		{
			old = Spew_SetConsoleTextColor(1, 0, 0, 1);
		}
		else if (type == SPEW_INFO)
		{
			old = Spew_SetConsoleTextColor(0, 1, 1, 1);
		}
		else
		{
			old = Spew_SetConsoleTextColor(1, 1, 1, 1);
		}

		OutputDebugStringA(text);
		printf("%s", text);

		Spew_RestoreConsoleTextColor(old);
	}
	LeaveCriticalSection(&g_SpewCS);
}
#endif

void PrintMessageToOutput(SpewType_t spewtype, char const* pMsgFormat, va_list args)
{
	static char pTempBuffer[4096];
	int len = 0;
	vsprintf(&pTempBuffer[len], pMsgFormat, args);

#ifdef WIN32
	Spew_ConDebugSpew(spewtype, pTempBuffer);
#else
	printf(pTempBuffer);
#endif

	if(g_logStream)
		fprintf(g_logStream, pTempBuffer);
}

void PsyX_Log(const char* fmt, ...)
{
	va_list		argptr;

	va_start(argptr, fmt);
	PrintMessageToOutput(SPEW_NORM, fmt, argptr);
	va_end(argptr);
}

void PsyX_Log_Info(const char* fmt, ...)
{
	va_list		argptr;

	va_start(argptr, fmt);
	PrintMessageToOutput(SPEW_INFO, fmt, argptr);
	va_end(argptr);
}

void PsyX_Log_Warning(const char* fmt, ...)
{
	va_list		argptr;

	va_start(argptr, fmt);
	PrintMessageToOutput(SPEW_WARNING, fmt, argptr);
	va_end(argptr);
}

void PsyX_Log_Error(const char* fmt, ...)
{
	va_list		argptr;

	va_start(argptr, fmt);
	PrintMessageToOutput(SPEW_ERROR, fmt, argptr);
	va_end(argptr);
}

void PsyX_Log_Success(const char* fmt, ...)
{
	va_list		argptr;

	va_start(argptr, fmt);
	PrintMessageToOutput(SPEW_SUCCESS, fmt, argptr);
	va_end(argptr);
}


void PsyX_Initialise(char* appName, int width, int height, int fullscreen)
{
	char windowNameStr[128];

	g_appNameStr = appName;

	InstallExceptionHandler();

	PsyX_Log_Initialise();
	PsyX_GetWindowName(windowNameStr);

	int test1 = 110;
	int test2 = 10;
	test1 += 500;
	test2 -= 10;

	eprintf("TEST MESSAGE %d\n", test1 / test2);

#if defined(_WIN32) && defined(_DEBUG)
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitleA(windowNameStr);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	}
#endif

	eprintinfo("Initialising Psy-X %d.%d\n", PSYX_MAJOR_VERSION, PSYX_MINOR_VERSION);
	eprintinfo("Build date: %s:%s\n", PSYX_COMPILE_DATE, PSYX_COMPILE_TIME);

#if defined(__EMSCRIPTEN__)
	SDL_SetHint(SDL_HINT_EMSCRIPTEN_ASYNCIFY, "0");
#endif
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		eprinterr("Failed to initialise SDL\n");
		PsyX_Shutdown();
		return;
	}
	
	if (!GR_InitialiseRender(windowNameStr, width, height, fullscreen))
	{
		eprinterr("Failed to Intialise Window\n");
		PsyX_Shutdown();
		return;
	}

	if (!PsyX_Sys_InitialiseCore())
	{
		eprinterr("Failed to Intialise Psy-X Core.\n");
		PsyX_Shutdown();
		return;
	}

	if (!GR_InitialisePSX())
	{
		eprinterr("Failed to Intialise PSX.\n");
		PsyX_Shutdown();
		return;
	}

	PsyX_Sys_InitialiseInput();

	// set shutdown function (PSX apps usualy don't exit)
	atexit(PsyX_Shutdown);

	// disable cursor visibility
	SDL_ShowCursor(0);
}

void PsyX_GetScreenSize(int* screenWidth, int* screenHeight)
{
	SDL_GetWindowSize(g_window, screenWidth, screenHeight);
}

void PsyX_SetCursorPosition(int x, int y)
{
	SDL_WarpMouseInWindow(g_window, x, y);
}

void PsyX_Sys_DoDebugKeys(int nKey, char down); // forward decl
void PsyX_Sys_DoDebugMouseMotion(int x, int y);

void PsyX_Exit();

GameDebugKeysHandlerFunc gameDebugKeys = NULL;
GameDebugMouseHandlerFunc gameDebugMouse = NULL;
GameOnTextInputHandler gameOnTextInput = NULL;

int g_activeKeyboardControllers = 0x1;
int g_altKeyState = 0;

void PsyX_Sys_DoPollEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_CONTROLLERDEVICEADDED:
				PsyX_Pad_Event_ControllerAdded(event.cdevice.which);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				PsyX_Pad_Event_ControllerRemoved(event.cdevice.which);
				break;
			case SDL_QUIT:
				PsyX_Exit();
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
					PsyX_Exit();
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

				if (nKey == SDL_SCANCODE_RALT)
				{
					g_altKeyState = (event.type == SDL_KEYDOWN);
				}
				else if (nKey == SDL_SCANCODE_RETURN)
				{
					if (g_altKeyState && event.type == SDL_KEYDOWN)
					{
						int fullscreen = SDL_GetWindowFlags(g_window) & SDL_WINDOW_FULLSCREEN > 0;

						SDL_SetWindowFullscreen(g_window, fullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);

						SDL_GetWindowSize(g_window, &g_windowWidth, &g_windowHeight);
						GR_ResetDevice();
					}
					break;
				}

				// lshift/right shift
				if (nKey == SDL_SCANCODE_RSHIFT)
					nKey = SDL_SCANCODE_LSHIFT;
				else if (nKey == SDL_SCANCODE_RCTRL)
					nKey = SDL_SCANCODE_LCTRL;
				else if (nKey == SDL_SCANCODE_RALT)
					nKey = SDL_SCANCODE_LALT;

				if (gameOnTextInput && nKey == SDL_SCANCODE_BACKSPACE && event.type == SDL_KEYDOWN)
				{
					(gameOnTextInput)(NULL);
				}

				PsyX_Sys_DoDebugKeys(nKey, (event.type == SDL_KEYUP) ? 0 : 1);
				break;
			}
			case SDL_TEXTINPUT:
			{
				if(gameOnTextInput)
					(gameOnTextInput)(event.text.text);
				break;
			}			
		}
	}
}

char begin_scene_flag = 0;

char PsyX_BeginScene()
{
	PsyX_Sys_DoPollEvent();

	if (begin_scene_flag)
		return 0;

	assert(!begin_scene_flag);

	GR_BeginScene();

	begin_scene_flag = 1;

	PsyX_Log_Flush();

	return 1;
}

uint PsyX_CalcFPS();

void PsyX_EndScene()
{
	if (!begin_scene_flag)
		return;

	assert(begin_scene_flag);
	begin_scene_flag = 0;

	GR_EndScene();
	
	GR_StoreFrameBuffer(activeDispEnv.disp.x, activeDispEnv.disp.y, activeDispEnv.disp.w, activeDispEnv.disp.h);

	GR_SwapWindow();
}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
void PsyX_TakeScreenshot()
{
	u_char* pixels = (u_char*)malloc(g_windowWidth * g_windowHeight * 4);
	
#if defined(RENDERER_OGL)
	glReadPixels(0, 0, g_windowWidth, g_windowHeight, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
#elif defined(RENDERER_OGLES)
	glReadPixels(0, 0, g_windowWidth, g_windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels);	// FIXME: is that correct format?
#endif

	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, g_windowWidth, g_windowHeight, 8 * 4, g_windowWidth * 4, 0, 0, 0, 0);

	SDL_SaveBMP(surface, "SCREENSHOT.BMP");
	SDL_FreeSurface(surface);

	free(pixels);
}
#endif

void PsyX_Sys_DoDebugMouseMotion(int x, int y)
{
	if (gameDebugMouse)
		gameDebugMouse(x, y);
}

void PsyX_Sys_DoDebugKeys(int nKey, char down)
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
			eprintwarn("wireframe mode: %d\n", g_wireframeMode);
			break;

		case SDL_SCANCODE_F2:
			g_texturelessMode ^= 1;
			eprintwarn("textureless mode: %d\n", g_texturelessMode);
			break;
		case SDL_SCANCODE_UP:
		case SDL_SCANCODE_DOWN:
			if (g_emulatorPaused)
			{
				g_polygonSelected += (nKey == SDL_SCANCODE_UP) ? 3 : -3;
			}
			break;
		case SDL_SCANCODE_F10:
			eprintwarn("saving VRAM.TGA\n");
			GR_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, 1);
			break;
#endif
#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
		case SDL_SCANCODE_F12:
			eprintwarn("Saving screenshot...\n");
			PsyX_TakeScreenshot();
			break;
#endif
		case SDL_SCANCODE_F3:
			g_bilinearFiltering ^= 1;
			eprintwarn("filtering mode: %d\n", g_bilinearFiltering);
			break;
		case SDL_SCANCODE_F4:

			g_activeKeyboardControllers++;
			g_activeKeyboardControllers = g_activeKeyboardControllers % 4;

			if (g_activeKeyboardControllers == 0)
				g_activeKeyboardControllers++;

			eprintwarn("Active keyboard controller: %d\n", g_activeKeyboardControllers);
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

	if(!g_altKeyState)
		PsyX_Pad_InternalPadUpdates();
}

uint PsyX_CalcFPS()
{
#define FPS_INTERVAL 1.0

	static unsigned int lastTime = 0;
	static unsigned int currentFps = 0;
	static unsigned int passedFrames = 0;

	lastTime = SDL_GetTicks();

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
#if 0 // defined(RENDERER_OGL) || defined(RENDERER_OGLES)
	glFinish(); // best time to complete GPU drawing
#endif

	// wait for vblank
	if (g_swapInterval > 0)
	{	
		static int swapLastVbl = 0;

		int vbl;
		do
		{
#ifdef __EMSCRIPTEN__
			emscripten_sleep(0);
#endif
			vbl = PsyX_Sys_GetVBlankCount();
		}
		while (vbl - swapLastVbl < count);

		swapLastVbl = PsyX_Sys_GetVBlankCount();
	}
}

void PsyX_Exit()
{
	exit(0);
}

void PsyX_Shutdown()
{
	if (!g_window)
		return;

	// quit vblank thread
	if (g_intrThread)
	{
		g_stopIntrThread = 1;

		int returnValue;
		SDL_WaitThread(g_intrThread, &returnValue);
	}

	if (g_intrMutex)
		SDL_DestroyMutex(g_intrMutex);

	GR_Shutdown();
	SpuQuit();

	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	SDL_Quit();

	PsyX_Log_Finalise();

	UnInstallExceptionHandler();
}
