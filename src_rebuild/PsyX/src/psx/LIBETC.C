#include "psx/libetc.h"

#include "../PsyX_main.h"
#include "PsyX/PsyX_public.h"

#include <SDL_timer.h>

#ifdef DEBUG
char scratchData[4096 + 8];
char* _scratchData = scratchData + 4;
#else
char scratchData[4096];
char* _scratchData = scratchData;
#endif

void(*vsync_callback)(void) = NULL;

int StopCallback(void)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int ResetCallback(void)
{
	int old = (int)vsync_callback;
	vsync_callback = NULL;
	return old;
}

int VSync(int mode)
{
	if (mode < 0)
	{
		// don't wait but still return vblank count
		return PsyX_Sys_GetVBlankCount();
	}

	if (mode == 0)
	{
		PsyX_WaitForTimestep(1);
	}
	else if (mode > 0)
	{
		// FIXME: wait many times?
	}

	return PsyX_Sys_GetVBlankCount();
}

int VSyncCallback(void(*f)(void))
{
	int old = (int)vsync_callback;
	vsync_callback = f;
	return old;
}

long SetVideoMode(long mode)
{
#ifdef DEBUG
	// debug marks for overflow cheks
	*(uint*)&scratchData[0] = 0xdeadb33f;
	*(uint*)&scratchData[4096 + 4] = 0xdeadb33f;
#endif
	
	return PsyX_Sys_SetVMode(mode);
}

long GetVideoMode()
{
	return g_vmode;
}

void PadInit(int mode)
{
	PSYX_UNIMPLEMENTED();

	// TODO: call PadInitDirect
}

u_long PadRead(int id)
{
	PSYX_UNIMPLEMENTED();
	
	// TODO: return pad data as u_long
}

void PadStop(void)
{
	PSYX_UNIMPLEMENTED();

	// TODO: stop pad reads
}