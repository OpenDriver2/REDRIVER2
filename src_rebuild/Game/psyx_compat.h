#ifndef PSYX_COMPAT_H
#define PSYX_COMPAT_H

// Psy-Cross compatibility header

// Necessary includes
#ifndef PSX
#include "PSYX_PUBLIC.H"
#endif

// Necessary types
// It's size should match P_LEN*4
#ifdef PSX
typedef int intptr_t;
typedef u_long OTTYPE;

typedef short VERTTYPE;

#define RECT16 RECT

#else

#if defined(_M_X64) || defined(__amd64__)
typedef OT_TAG OTTYPE;
#else
typedef unsigned long long OTTYPE;
#endif

#endif

#endif PSYX_COMPAT_H