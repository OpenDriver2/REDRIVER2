#ifndef LIBSN_H
#define LIBSN_H

#include <stdint.h>

extern int PCinit();
extern uintptr_t PCopen(char* name, int flags, int perms);
extern int PCcreat(char* name, int perms);
extern int PClseek(uintptr_t fd, int offset, int mode);
extern int PCread(uintptr_t fd, char* buff, int len);
extern int PCwrite(uintptr_t fd, char* buff, int len);
extern int PCclose(uintptr_t fd);

#endif