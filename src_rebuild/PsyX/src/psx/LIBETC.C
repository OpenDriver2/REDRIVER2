#include "psx/libetc.h"

#include "../PsyX_main.h"
#include "PsyX/PsyX_public.h"

#include <SDL_timer.h>

char scratchData[1024];
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
	return PsyX_Sys_SetVMode(mode);
}

long GetVideoMode()
{
	return g_vmode;
}
