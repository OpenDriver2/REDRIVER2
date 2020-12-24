#ifndef EMULATOR_PUBLIC_H
#define EMULATOR_PUBLIC_H

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

typedef void(*GameDebugKeysHandlerFunc)(int nKey, bool down);
extern GameDebugKeysHandlerFunc gameDebugKeys;

typedef void(*GameDebugMouseHandlerFunc)(int x, int y);
extern GameDebugMouseHandlerFunc gameDebugMouse;

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

/* Usually called at the end if main function */
extern void PsyX_ShutDown();

/* Screen size of emulated PSX viewport with widescreen offsets */
extern void PsyX_GetPSXWidescreenMappedViewport(struct _RECT16* rect);

/* Waits for timer */
extern void PsyX_WaitForTimestep(int count);

/* Changes swap interval state */
extern void PsyX_EnableSwapInterval(int enable);

#endif