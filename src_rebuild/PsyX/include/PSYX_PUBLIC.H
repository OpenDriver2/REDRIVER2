#ifndef EMULATOR_PUBLIC_H
#define EMULATOR_PUBLIC_H

#define CONTROLLER_MAP_FLAG_AXIS		0x4000
#define CONTROLLER_MAP_FLAG_INVERSE		0x8000

struct PsyXKeyboardMapping
{
	int id;

	int kc_square;
	int kc_circle;
	int kc_triangle;
	int kc_cross;

	int kc_l1;
	int kc_l2;
	int kc_l3;

	int kc_r1;
	int kc_r2;
	int kc_r3;

	int kc_start;
	int kc_select;

	int kc_dpad_left;
	int kc_dpad_right;
	int kc_dpad_up;
	int kc_dpad_down;
};

struct PsyXControllerMapping
{
	int id;

	// you can bind axis by adding CONTROLLER_MAP_AXIS_FLAG
	int gc_square;
	int gc_circle;
	int gc_triangle;
	int gc_cross;

	int gc_l1;
	int gc_l2;
	int gc_l3;

	int gc_r1;
	int gc_r2;
	int gc_r3;

	int gc_start;
	int gc_select;

	int gc_dpad_left;
	int gc_dpad_right;
	int gc_dpad_up;
	int gc_dpad_down;

	int gc_axis_left_x;
	int gc_axis_left_y;

	int gc_axis_right_x;
	int gc_axis_right_y;
};

typedef void(*GameDebugKeysHandlerFunc)(int nKey, bool down);
extern GameDebugKeysHandlerFunc gameDebugKeys;

typedef void(*GameDebugMouseHandlerFunc)(int x, int y);
extern GameDebugMouseHandlerFunc gameDebugMouse;

typedef void(*GameOnTextInputHandler)(const char* buf);
extern GameOnTextInputHandler gameOnTextInput;

//------------------------------------------------------------------------

/* Usually called at the beginning of main function */
extern void PsyX_Initialise(char* windowName, int screenWidth, int screenHeight, int fullscreen);

/* Cleans all resources and closes open instances */
extern void PsyX_Shutdown();

/* Returns the screen size dimensions */
extern void PsyX_GetScreenSize(int& screenWidth, int& screenHeight);

/* Sets mouse cursor position */
extern void PsyX_SetCursorPosition(int x, int y);

/* Usually called after ClearOTag/ClearOTagR */
extern bool PsyX_BeginScene();

/* Usually called after DrawOTag/DrawOTagEnv */
extern void PsyX_EndScene();

/* Explicitly updates emulator input loop */
extern void PsyX_UpdateInput();

/* Returns keyboard mapping index */
extern int PsyX_LookupKeyboardMapping(const char* str, int default_value);

/* Returns controller mapping index */
extern int PsyX_LookupGameControllerMapping(const char* str, int default_value);

/* Screen size of emulated PSX viewport with widescreen offsets */
extern void PsyX_GetPSXWidescreenMappedViewport(struct _RECT16* rect);

/* Waits for timer */
extern void PsyX_WaitForTimestep(int count);

/* Changes swap interval state */
extern void PsyX_EnableSwapInterval(int enable);

#endif