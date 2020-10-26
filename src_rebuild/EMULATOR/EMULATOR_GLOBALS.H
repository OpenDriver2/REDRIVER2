#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#include <SDL_gamecontroller.h>
#include <EMULATOR.H>

extern TextureID        whiteTexture;
extern TextureID        vramTexture;

extern int screenWidth;
extern int screenHeight;
extern int windowWidth;
extern int windowHeight;
extern uint32_t DMAControlRegister;
extern int assetsLoaded;
extern int g_emulatorPaused;
extern int g_polygonSelected;

extern void InternalPadUpdates();

extern SDL_GameController* padHandle[];
extern unsigned char* padData[];

#endif