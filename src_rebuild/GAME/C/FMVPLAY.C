#include "DRIVER2.H"
#include "FMVPLAY.H"

#include "LIBETC.H"
#include "LIBSPU.H"
#include "LIBGPU.H"
#include "LIBMCRD.H"

#include "SYSTEM.H"
#include "PAD.H"
#include "SOUND.H"
#include "FMVPLAY.H"
#include "E3STUFF.H"
#include "GAMESND.H"
#include "SCORES.H"
#include "MAIN.H"

// FMV
int gSubtitles = 0;
int gNoFMV = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ ReInitSystem()
 // line 23, offset 0x0004d478
	/* begin block 1 */
		// Start line: 25
		// Start offset: 0x0004D478
	/* end block 1 */
	// End offset: 0x0004D518
	// End Line: 48

	/* begin block 2 */
		// Start line: 46
	/* end block 2 */
	// End Line: 47

	/* begin block 3 */
		// Start line: 47
	/* end block 3 */
	// End Line: 48

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void ReInitSystem(void)
{
	StopCallback();
	ResetCallback();
	ResetGraph(1);
	SetVideoMode(video_mode);
	InitGeom();
	SetGeomOffset(0xa0, 0x80);
	scr_z = 0x100;
	SetGeomScreen(0x100);
	MemCardInit(1);
	InitControllers();
	CdInit();
	InitSound();
	SetMasterVolume(gMasterVolume);
	SetXMVolume(gMusicVolume);
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlayFMV(unsigned char render /*$s0*/)
 // line 68, offset 0x0004d518
	/* begin block 1 */
		// Start line: 69
		// Start offset: 0x0004D518
		// Variables:
	// 		RENDER_ARGS args; // stack offset -40

		/* begin block 1.1 */
			// Start line: 75
			// Start offset: 0x0004D544
		/* end block 1.1 */
		// End offset: 0x0004D544
		// End Line: 75

		/* begin block 1.2 */
			// Start line: 80
			// Start offset: 0x0004D570
		/* end block 1.2 */
		// End offset: 0x0004D578
		// End Line: 81
	/* end block 1 */
	// End offset: 0x0004D5D0
	// End Line: 96

	/* begin block 2 */
		// Start line: 133
	/* end block 2 */
	// End Line: 134

	/* begin block 3 */
		// Start line: 136
	/* end block 3 */
	// End Line: 137

// [D]
void PlayFMV(unsigned char render)
{
	RENDER_ARGS args;
	
	if ((render - 16 < 13) || (render == 97))
	{
		CheckForCorrectDisc(1);
	}
	else if (((render - 1 & 0xff) < 0xf) || (render == 98))
	{
		CheckForCorrectDisc(0);
	}

	args.nRenders = 1;
	args.Args[0].credits = render == 28;
	args.Args[0].recap = 0;
	args.Args[0].render = render;

	PlayRender(&args);

	if ((render - 1 & 0xff) < 0x62)
		SetPleaseWait(NULL);
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlayRender(RENDER_ARGS *args /*$s0*/)
 // line 107, offset 0x0004d5d0
	/* begin block 1 */
		// Start line: 108
		// Start offset: 0x0004D5D0
		// Variables:
	// 		static unsigned long oldsp; // offset 0x0

		/* begin block 1.1 */
			// Start line: 129
			// Start offset: 0x0004D634
		/* end block 1.1 */
		// End offset: 0x0004D678
		// End Line: 138
	/* end block 1 */
	// End offset: 0x0004D690
	// End Line: 141

	/* begin block 2 */
		// Start line: 210
	/* end block 2 */
	// End Line: 211

	/* begin block 3 */
		// Start line: 222
	/* end block 3 */
	// End Line: 223

extern int FMV_main(RENDER_ARGS* args);

// [D] [A]
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





