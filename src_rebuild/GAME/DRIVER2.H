#ifndef DRIVER2_H
#define DRIVER2_H

#include <stdbool.h>

#include "KERNEL.H"
#include "LIBCD.H"
#include "LIBGPU.H"
#include "LIBSPU.H"
#include "LIBGTE.H"

// from redriver2_psxpc
void printMsg(char *fmt, ...);
void printInfo(char *fmt, ...);
void printWarning(char *fmt, ...);
void printError(char *fmt, ...);

#ifdef PSX
// TODO: Include PSX STUFF
#define trap(code) printf("ERROR OCCURED!\n")
#else

#if _MSC_VER >= 1400
#define trap(ode) {printError("EXCEPTION code: %x\n", ode); __debugbreak();}
#else
#define trap(ode) {_asm int 0x03}
#endif

// Emulator
#include <EMULATOR.H>
#include <EMULATOR_PRIVATE.H>
#include "EMULATOR_PLATFORM_SETUP.H"

#ifdef USE_32_BIT_ADDR
typedef uint64_t OTTYPE;
#else
typedef unsigned long OTTYPE;
#endif // USE_32_BIT_ADDR

#endif // PSX

#include "REVERSING.H"

#include "VERSION.H"
#include "DR2MATH.H"
#include "DR2LIMITS.H"
#include "DR2TYPES.H"

#endif // DRIVER2_H
