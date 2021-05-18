#ifndef EMULATOR_SETUP_H
#define EMULATOR_SETUP_H

#include "platform.h"

//Disc image filename to load for disc image builds
#define DISC_CUE_FILENAME "IMAGE.CUE"

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern unsigned int g_swapTime;
extern long g_vmode;
extern int g_activeKeyboardControllers;

extern int PsyX_Sys_GetVBlankCount();
extern long PsyX_Sys_SetVMode(long mode);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif