#ifndef DRIVER2_H
#define DRIVER2_H

#include <types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>
#include <libspu.h>
#include <libmcrd.h>
#include <libmath.h>
#include <libetc.h>
#include <libapi.h>

#include <inline_c.h>
#include <gtemac.h>

#include <strings.h>
#include <rand.h>
#include <stdio.h>
#include <limits.h>

#include "platform.h"

#define USE_PC_FILESYSTEM !defined(PSX)		// PC filesystem is prioritized over CD
#define USE_CD_FILESYSTEM 1					// use always

#ifdef PSX
// TODO: Include PSX STUFF
#define trap(code)

#define printMsg					printf
#define printInfo					printf
#define printWarning				printf
#define printError					printf

#define LOAD_OVERLAY(filename, addr) Loadfile(filename, (char*)addr)

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

#define LOAD_OVERLAY(filename, addr) 1

#endif // PSX

#define D_CHECK_ERROR(expr, message) if(expr){ printError("%s - %s\n", FUNCNAME, message); while (FrameCnt != 0x78654321) trap(0x400); }

#include "reversing.h"

#include "version.h"
#include "dr2math.h"
#include "dr2limits.h"
#include "dr2types.h"
#include "dr2locale.h"

#endif // DRIVER2_H
