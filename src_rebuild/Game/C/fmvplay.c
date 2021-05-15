#include "driver2.h"
#include "fmvplay.h"

#include "system.h"
#include "pad.h"
#include "sound.h"
#include "E3stuff.h"
#include "main.h"


// FMV
int gSubtitles = 1;
int gNoFMV = 0;

// [D] [T]
void ReInitSystem(void)
{
	StopCallback();
	ResetCallback();
	ResetGraph(1);
	SetVideoMode(video_mode);
	InitGeom();
	SetGeomOffset(160, 128);
	scr_z = 256;
	SetGeomScreen(256);
	MemCardInit(1);
	InitControllers();
	CdInit();
	InitSound();
	SetMasterVolume(gMasterVolume);
	SetXMVolume(gMusicVolume);
}

extern int FMV_main(RENDER_ARGS* args);

volatile char* _fmv_memory = (char*)0x800ff800; // there was no 0x800

// [D] [T]
void PlayRender(RENDER_ARGS *args)
{
	static unsigned long oldsp;

	StopAllChannels();

	FreeXM();
	SpuQuit();

	args->screenx = draw_mode_pal.framex;
	args->screeny = draw_mode_pal.framey;
	args->subtitle = gSubtitles;
#ifdef PSX

#if 0
	
	if (Loadfile("FMV\\FMV.EXE", (char*)_fmv_memory) != 0)
	{
		oldsp = GetSp();
		EnterCriticalSection();
		FlushCache();
		ExitCriticalSection();
		Exec((EXEC*)_fmv_memory, 1, (char**)args);
		SetSp(oldsp);
	}
#endif
	
#else

	if (gNoFMV == 1)
		return;
	
	FMV_main(args);
#endif
	ReInitSystem();

}

// [D] [T]
void PlayFMV(unsigned char render)
{
	RENDER_ARGS args;

	if (render - 16U < 13 || render == 97)
	{
		CheckForCorrectDisc(1);
	}
	else if ((render - 1U & 0xff) < 15 || render == 98)
	{
		CheckForCorrectDisc(0);
	}

	args.nRenders = 1;
	args.Args[0].credits = render == 28;
	args.Args[0].recap = 0;
	args.Args[0].render = render;

	PlayRender(&args);

	if ((render - 1 & 0xff) < 98)
		SetPleaseWait(NULL);
}