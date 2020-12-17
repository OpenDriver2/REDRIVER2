#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#include <SDL_gamecontroller.h>
#include "EMULATOR.H"

extern TextureID        g_whiteTexture;
extern TextureID        g_curVramTexture;

extern int screenWidth;
extern int screenHeight;
extern int g_windowWidth;
extern int g_windowHeight;
extern uint32_t DMAControlRegister;
extern int assetsLoaded;
extern int g_emulatorPaused;
extern int g_polygonSelected;

extern void InternalPadUpdates();

extern SDL_GameController* padHandle[];
extern unsigned char* padData[];

#endif