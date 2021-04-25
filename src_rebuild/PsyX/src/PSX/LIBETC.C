#include "LIBETC.H"

#include "../PSYX_SETUP.H"
#include "PSYX_PUBLIC.H"

#include <SDL_timer.h>

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

char scratchData[1024];

extern unsigned int g_swapTime;
extern int PsyX_Sys_GetVBlankCount();
extern long PsyX_Sys_SetVMode(long mode);
extern long g_vmode;

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
	return PsyX_Sys_SetVMode(mode);
}

long GetVideoMode()
{
	return g_vmode;
}
