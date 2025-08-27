#ifndef PSYX_COMPAT_H
#define PSYX_COMPAT_H

// Psy-Cross compatibility header

// Necessary includes
#ifndef PSX
#include "PsyX/PsyX_public.h"
#include "PsyX/PsyX_globals.h"
#include "psx/libgte.h"
#include "psx/libgpu.h"
#endif

// Necessary types
// It's size should match P_LEN*4
#ifdef PSX
typedef int intptr_t;
typedef u_long OTTYPE;

typedef short VERTTYPE;

#define RECT16 RECT

// for portability, mainly 64 bit platforms
typedef int			intptr;
typedef u_int		u_intptr;

#else

#if defined(_M_X64) || defined(__amd64__)
typedef OT_TAG OTTYPE;
#else
typedef unsigned long long OTTYPE;
#endif

// for portability, mainly 64 bit platforms
typedef intptr_t	intptr;
typedef uintptr_t	u_intptr;

#endif

#endif // PSYX_COMPAT_H