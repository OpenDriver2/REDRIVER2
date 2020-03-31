#ifndef EMULATOR_PRIVATE_H
#define EMULATOR_PRIVATE_H

/* Usually called when loading game textures to tell the emulator how to form an atlas for faster drawing */
extern void Emulator_HintTextureAtlas(unsigned short tpage, unsigned short clut, unsigned char u0, unsigned char v0, unsigned char u1, unsigned char v1, unsigned char u2, unsigned char v2, unsigned char u3, unsigned char v3, unsigned short bIsQuad);

/* Usually called at the beginning of main function */
extern void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight);

/* Usually called after ClearOTag/ClearOTagR */
extern void Emulator_BeginScene();

/* Usually called after DrawOTag/DrawOTagEnv */
extern void Emulator_EndScene();

/* Explicitly updates emulator input loop */
extern void Emulator_UpdateInput();

/* Usually called at the end if main function */
extern void Emulator_ShutDown();

/* Placeholder, can inject a TIM file into vram */
extern void Emulator_InjectTIM(char* fileName, unsigned short texTpage, unsigned short texClut, unsigned char u0, unsigned char v0, unsigned char u1, unsigned char v1, unsigned char u2, unsigned char v2, unsigned char u3, unsigned char v3);

/* Usually called when loading a game level to specifically delete all emulator textures for optimisation purposes */
extern void Emulator_DestroyAllTextures();

/* Sets the maximum vertex count value for PGXP vertex caching */
extern void Emulator_SetPGXPVertexCount(int vertexCount);

#endif