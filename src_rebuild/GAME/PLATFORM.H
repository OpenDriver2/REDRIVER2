#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
#include <direct.h>
#elif defined (__unix__)
#include <sys/stat.h>
#define _mkdir(str) mkdir(str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)

inline void fixslashes(char* pathbuff)
{
    while (*pathbuff)
    {
        if (*pathbuff == '\\') *pathbuff = '/';
        pathbuff++;
    }
}
#endif

#ifdef __GNUC__
#include <string.h>
#define _stricmp(s1, s2) strcasecmp(s1, s2)
#endif

#endif // PLATFORM_H