#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#if defined(_WINDOWS) || defined(__MINGW32__) || defined (__ANDROID__)
#include <SDL_gamecontroller.h>
#elif defined(__APPLE__) || defined(__linux__) || defined(__EMSCRIPTEN__)
#include <SDL2/SDL_gamecontroller.h>
#endif

#include <EMULATOR.H>

#if defined(D3D9)
extern LPDIRECT3DVERTEXBUFFER9 g_vertexBufferObject;
#endif


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

extern unsigned short UpdateGameControllerInput(SDL_GameController* pad);
extern unsigned short UpdateKeyboardInput();

extern SDL_GameController* padHandle[];
extern unsigned char* padData[];

#endif