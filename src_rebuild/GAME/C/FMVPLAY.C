#include "DRIVER2.H"
#include "FMVPLAY.H"

#include "LIBETC.H"
#include "LIBSPU.H"
#include "LIBGPU.H"
#include "LIBMCRD.H"

#include "SYSTEM.H"
#include "PAD.H"
#include "SOUND.H"
#include "E3STUFF.H"
#include "MAIN.H"

// FMV
int gSubtitles = 0;
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
	if (Loadfile("FMV\\FMV.EXE", &DAT_800ff800) != 0)
	{
		oldsp = GetSp();
		EnterCriticalSection();
		FlushCache();
		ExitCriticalSection();
		Exec(&DAT_800ff810, 1, args);
		SetSp(oldsp);
	}
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