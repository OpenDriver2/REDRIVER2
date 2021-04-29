#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

extern int g_windowWidth;
extern int g_windowHeight;
extern int g_wireframeMode;
extern int g_texturelessMode;
extern int g_enableSwapInterval;
extern int g_pgxpZBuffer;
extern int g_bilinearFiltering;

extern float g_pgxpZNear;
extern float g_pgxpZFar;

extern int g_emulatorPaused;
extern int g_polygonSelected;
extern int g_pgxpTextureCorrection;
extern int g_controllerToSlotMapping[2];

extern void PsyX_Pad_InternalPadUpdates();

// logging functions
extern void PsyX_Log(const char* fmt, ...);
extern void PsyX_Log_Info(const char* fmt, ...);
extern void PsyX_Log_Warning(const char* fmt, ...);
extern void PsyX_Log_Error(const char* fmt, ...);
extern void PsyX_Log_Success(const char* fmt, ...);

#endif