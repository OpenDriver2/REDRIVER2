#include "platform.h"
#include <libcd.h>
/*
// TEMP
#ifndef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE
#endif // EMSCRIPTEN_KEEPALIVE
*/

extern bool DumpImageFile(const char* data, unsigned int size);

extern "C" {

	void EMSCRIPTEN_KEEPALIVE WebLoadCDImage(char* data, int size) 
	{
		PsyX_CDFS_Init_Mem((u_long*)data, size, 0, 0);
	}
}
