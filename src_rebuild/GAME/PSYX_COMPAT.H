#ifndef PSYX_COMPAT_H
#define PSYX_COMPAT_H

// Psy-Cross compatibility header

// Necessary includes
#ifndef PSX
#include "EMULATOR_PRIVATE.H"
#endif

// Necessary types
#ifdef PSX
typedef u_long OTTYPE;
#else
typedef unsigned long long OTTYPE;
#endif

#endif PSYX_COMPAT_H