#ifndef FS_H
#define FS_H

#ifdef _WIN32
#include <direct.h>
#define HOME_ENV "USERPROFILE"

#elif defined (__unix__)
#include <sys/stat.h>
#define HOME_ENV "HOME"

#define _mkdir(str)				mkdir(str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

struct FS_FINDDATA;

void FS_FixPathSlashes(char* pathbuff);

const char* FS_FindFirst(const char* wildcard, FS_FINDDATA** findData);
const char* FS_FindNext(FS_FINDDATA* findData);
void		FS_FindClose(FS_FINDDATA* findData);
bool		FS_FindIsDirectory(FS_FINDDATA* findData);

#endif