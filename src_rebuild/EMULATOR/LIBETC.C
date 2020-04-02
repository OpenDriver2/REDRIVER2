#include "LIBETC.H"

#include "EMULATOR_PRIVATE.H"
#include "EMULATOR.H"

#if defined(_WINDOWS)
#include <d3d9.h>
#endif

#include <SDL_timer.h>

void(*vsync_callback)(void) = NULL;

int StopCallback(void)
{
	UNIMPLEMENTED();
	return 0;
}

int ResetCallback(void)
{
	vsync_callback = NULL;
	return 0;
}

int VSync(int mode)
{
	if (mode == 0)
	{
		if (vsync_callback != NULL)
		{
			vsync_callback();
		}
		Emulator_EndScene();
	}
	else if (mode > 0)
	{
		while (mode--)
		{
			//vblank
		}
		Emulator_EndScene();
	}
	else if (mode < 0)
	{
		//Unimplemented
	}

	return SDL_GetTicks();
}

int VSyncCallback(void(*f)(void))
{
	vsync_callback = f;
	return 0;
}

long GetVideoMode(void)
{
	return MODE_NTSC;
}

long SetVideoMode(long mode)
{
	UNIMPLEMENTED();
	return MODE_NTSC;
}
