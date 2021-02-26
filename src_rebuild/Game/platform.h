#ifndef PLATFORM_H
#define PLATFORM_H

#include "STRINGS.H"

#ifndef PSX
#include "../utils/fs.h"
#endif

#ifdef __GNUC__
#define _stricmp(s1, s2) strcasecmp(s1, s2)
#endif

#endif // PLATFORM_H