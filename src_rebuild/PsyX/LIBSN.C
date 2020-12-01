#include "EMULATOR.H"
#include "LIBSN.H"
#include <stdio.h>

uintptr_t fileHandle = 0;

#define INVALID_FILE_HANDLE (-1)

int PCinit()
{
	//PSYX_UNIMPLEMENTED();
	return 0;
}

uintptr_t PCopen(char* name, int flags, int perms)
{
	//TOMB5 hack for CUTSEQ.JIZ
	if (name[0] == '\\')
	{
		++name;
	}

#if defined(__ANDROID__)
	char buff[64];
	sprintf(&buff[0], "/storage/emulated/0/TOMB5/%s", name);
	name = &buff[0];
#endif

	switch (flags)
	{
	case 0:
		fileHandle = (uintptr_t)fopen(name, "rb");
		break;
	case 1:
		fileHandle = (uintptr_t)fopen(name, "wb");
		break;
	case 2:
		fileHandle = (uintptr_t)fopen(name, "rwb");
		break;
	}

	return fileHandle == 0 ? INVALID_FILE_HANDLE : fileHandle;
}

int PCcreat(char* name, int perms)
{
	//PSYX_UNIMPLEMENTED();
	return 0;
}

int PClseek(uintptr_t fd, int offset, int mode)
{
	fseek((FILE*)fd, offset, mode);
	return ftell((FILE*)fd);
}

int PCread(uintptr_t fd, char* buff, int len)
{
 	return fread(buff, len, 1, (FILE*)fd);
}

int PCwrite(uintptr_t fd, char* buff, int len)
{
	return fwrite(buff, len, 1, (FILE*)fd);
}

int PCclose(uintptr_t fd)
{
	return fclose((FILE*)fd);
}