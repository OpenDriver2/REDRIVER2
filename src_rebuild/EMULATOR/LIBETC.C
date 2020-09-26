#include "LIBETC.H"

#include "EMULATOR_PRIVATE.H"
#include "EMULATOR.H"

#if defined(_WINDOWS)
#include <d3d9.h>
#endif

#if defined(_WINDOWS) || defined(__MINGW32__) || defined (__ANDROID__)
#include <SDL_timer.h>
#elif defined(__APPLE__) || defined(__linux__) || defined(__EMSCRIPTEN__)
#include <SDL2/SDL_timer.h>
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

extern unsigned int g_swapTime;
extern int Emulator_DoVSyncCallback();

int VSync(int mode)
{
	if (mode < 0)
	{
		// don't wait but still return vblank count
		return Emulator_DoVSyncCallback(); 
	}

	if (mode == 0)
	{
		Emulator_WaitForTimestep(1);
	}
	else if (mode > 0)
	{
		// FIXME: wait many times?
	}

	return Emulator_DoVSyncCallback();
}

int VSyncCallback(void(*f)(void))
{
	vsync_callback = f;
	return 0;
}

long GetVideoMode(void)
{
#ifdef NTSC_VERSION
	return MODE_NTSC;
#else
	return MODE_PAL;
#endif
}

long SetVideoMode(long mode)
{
	UNIMPLEMENTED();

#ifdef NTSC_VERSION
	return MODE_NTSC;
#else
	return MODE_PAL;
#endif
}
