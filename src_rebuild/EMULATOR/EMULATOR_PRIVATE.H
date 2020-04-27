#ifndef EMULATOR_PRIVATE_H
#define EMULATOR_PRIVATE_H

/* Usually called at the beginning of main function */
extern void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight);

/* Returns the screen size dimensions */
extern void Emulator_GetScreenSize(int& screenWidth, int& screenHeight);

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

/* Sets the maximum vertex count value for PGXP vertex caching */
extern void Emulator_SetPGXPVertexCount(int vertexCount);

/* Waits for timer */
extern void Emulator_WaitForTimestep(int count);

#endif