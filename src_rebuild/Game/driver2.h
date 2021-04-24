#ifndef DRIVER2_H
#define DRIVER2_H

#include "KERNEL.H"
#include "TYPES.H"
#include "LIBCD.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBSPU.H"

#include <stdio.h>

#include "platform.h"

#define USE_PC_FILESYSTEM !defined(PSX)		// PC filesystem is prioritized over CD
#define USE_CD_FILESYSTEM 1					// use always

#ifdef PSX
// TODO: Include PSX STUFF
#define trap(code) printf("ERROR OCCURED %s %d!\n", FUNCNAME, code)

#define printMsg					printf
#define printInfo					printf
#define printWarning				printf
#define printError					printf

#else

#include <stdbool.h>
#include <stdio.h>

#define printMsg				PsyX_Log
#define printInfo				PsyX_Log_Info
#define printWarning			PsyX_Log_Warning
#define printError				PsyX_Log_Error

#ifdef __EMSCRIPTEN__
#define trap(ode) {printError("EXCEPTION code: %x\n", ode);}
#elif _MSC_VER >= 1400
#define trap(ode) {printError("EXCEPTION code: %x\n", ode); __debugbreak();}
#elif defined(__GNUC__)
#define trap(ode) {__asm__("int3");}
#else
#define trap(ode) {_asm int 0x03}
#endif

#endif // PSX

#include "reversing.h"

#include "version.h"
#include "dr2math.h"
#include "dr2limits.h"
#include "dr2types.h"
#include "dr2locale.h"

#endif // DRIVER2_H
