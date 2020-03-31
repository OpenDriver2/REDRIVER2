#include "LIBETC.H"

#include "EMULATOR_PRIVATE.H"
#include "EMULATOR.H"

#if defined(_WINDOWS)
#include <d3d9.h>
#endif

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
	///static int startTime = SDL_GetTicks();

	if (mode == 0)
	{
		if (vsync_callback != NULL)
		{
			vsync_callback();
		}

		Emulator_EndScene();
		///return (SDL_GetTicks() - startTime / 1000);
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
		///return (SDL_GetTicks() / 1000);
	}

	return 0;//Assert?
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
