#ifndef DRIVER2_H
#define DRIVER2_H

#include <stdbool.h>
#include <stdio.h>

#include "KERNEL.H"
#include "TYPES.H"
#include "LIBCD.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBSPU.H"

#include "psyx_compat.h"

#ifdef PSX
// TODO: Include PSX STUFF
#define trap(code) printf("ERROR OCCURED %d!\n", code)

#define printMsg					(void)
#define printInfo					(void)
#define printWarning				(void)
#define printError					(void)

#else

#define printMsg				PsyX_Log
#define printInfo				PsyX_Log_Info
#define printWarning			PsyX_Log_Warning
#define printError				PsyX_Log_Error

#if _MSC_VER >= 1400
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
