#ifndef EMULATOR_PRIVATE_H
#define EMULATOR_PRIVATE_H

struct KeyboardMapping
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
extern void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight, int fullscreen);

/* Returns the screen size dimensions */
extern void Emulator_GetScreenSize(int& screenWidth, int& screenHeight);

/* Sets mouse cursor position */
extern void Emulator_SetCursorPosition(int x, int y);

/* Called inside VSync / DrawSync */
extern void Emulator_SwapDelay(int intervals);

/* Usually called after ClearOTag/ClearOTagR */
extern bool Emulator_BeginScene();

/* Usually called after DrawOTag/DrawOTagEnv */
extern void Emulator_EndScene();

/* Explicitly updates emulator input loop */
extern void Emulator_UpdateInput();

/* Usually called at the end if main function */
extern void Emulator_ShutDown();

/* Screen size of emulated PSX viewport with widescreen offsets */
extern void Emulator_GetPSXWidescreenMappedViewport(RECT16* rect);

/* Waits for timer */
extern void Emulator_WaitForTimestep(int count);

#endif