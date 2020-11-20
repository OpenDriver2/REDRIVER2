#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32

#include <direct.h>

#define HOME_ENV "USERPROFILE"

inline void FixPathSlashes(char* pathbuff)
{
    while (*pathbuff)
    {
        if (*pathbuff == '/') // make windows-style path
            *pathbuff = '\\';
        pathbuff++;
    }
}

#elif defined (__unix__)

#include <sys/stat.h>

#define HOME_ENV "HOME"
#define _mkdir(str) mkdir(str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)

inline void FixPathSlashes(char* pathbuff)
{
    while (*pathbuff)
    {
        if (*pathbuff == '\\') // make unix-style path
            *pathbuff = '/';
        pathbuff++;
    }
}
#endif

#ifdef __GNUC__
#include <string.h>
#define _stricmp(s1, s2) strcasecmp(s1, s2)
#endif

#endif // PLATFORM_H