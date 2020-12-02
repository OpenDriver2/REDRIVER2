#include "DRIVER2.H"
#include "LOADVIEW.H"

#include "E3STUFF.H"
#include "SYSTEM.H"
#include "LIBETC.H"
#include "GLAUNCH.H"
#include "MISSION.H"
#include "CAMERA.H"
#include "PAUSE.H"
#include "PRES.H"
#include "MAIN.H"
#include "CUTSCENE.H"

#include "../FRONTEND/FEMAIN.H"

DRAWENV load_draw = { 0 };
DISPENV load_disp = { 0 };

int load_steps = 0;
int loading_bar_pos = 0;
int gFastLoadingScreens = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ ShowLoading()
 // line 200, offset 0x0005816c
	/* begin block 1 */
		// Start line: 202
		// Start offset: 0x0005816C
		// Variables:
	// 		POLY_G4 poly; // stack offset -56
	// 		int col; // $s0
	/* end block 1 */
	// End offset: 0x00058298
	// End Line: 236

	/* begin block 2 */
		// Start line: 400
	/* end block 2 */
	// End Line: 401

	/* begin block 3 */
		// Start line: 401
	/* end block 3 */
	// End Line: 402

	/* begin block 4 */
		// Start line: 404
	/* end block 4 */
	// End Line: 405

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void ShowLoading(void)
{
	POLY_G4 poly;

	if (NewLevel == 0 && gInFrontend == 0)
		return;

	int col = (VERTTYPE)(++loading_bar_pos * load_steps);
		
	if (col > 120)
		col = 120;

	SetPolyG4(&poly);

	setRGB0(&poly, 30, 11, 11);
	setRGB1(&poly, 122, 11, 11);
	setRGB2(&poly, 30, 11, 11);
	setRGB3(&poly, 122, 11, 11);

	setXYWH(&poly, 176, 435, col, 25);

	DrawPrim(&poly);
	VSync(0);
	DrawSync(0);
	PutDrawEnv(&load_draw);
	PutDispEnv(&load_disp);

	DrawPrim(&poly);
	VSync(0);
	DrawSync(0);
	PutDrawEnv(&load_draw);
	PutDispEnv(&load_disp);

#ifndef PSX
	Emulator_EndScene();
#endif
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupScreenFade(int start /*$a0*/, int end /*$a1*/, int speed /*$a2*/)
 // line 248, offset 0x000589b0
	/* begin block 1 */
		// Start line: 1028
	/* end block 1 */
	// End Line: 1029

	/* begin block 2 */
		// Start line: 496
	/* end block 2 */
	// End Line: 497

	/* begin block 3 */
		// Start line: 1029
	/* end block 3 */
	// End Line: 1030

	/* begin block 4 */
		// Start line: 1033
	/* end block 4 */
	// End Line: 1034

int FadingScreen = 0;
int screen_fade_value = 0;
int screen_fade_start = 0;
int screen_fade_end = 0;
int screen_fade_speed = 0;

// [D] [T]
void SetupScreenFade(int start, int end, int speed)
{
	screen_fade_value = start;
	screen_fade_start = start;
	screen_fade_end = end;
	screen_fade_speed = speed;
	FadingScreen = 1;
}

// decompiled code
// original method signature: 
// void /*$ra*/ FadeGameScreen(int flag /*$t0*/, int speed /*$t1*/)
 // line 268, offset 0x000582ac
	/* begin block 1 */
		// Start line: 269
		// Start offset: 0x000582AC
		// Variables:
	// 		static POLY_F4 poly; // offset 0x0
	// 		static POLY_FT4 p; // offset 0x20
	// 		int do_fade; // $v0

		/* begin block 1.1 */
			// Start line: 291
			// Start offset: 0x000582EC
			// Variables:
		// 		int val; // $a3
		/* end block 1.1 */
		// End offset: 0x000583C8
		// End Line: 310
	/* end block 1 */
	// End offset: 0x000583F4
	// End Line: 315

	/* begin block 2 */
		// Start line: 565
	/* end block 2 */
	// End Line: 566

// [D] [T]
void FadeGameScreen(int flag)
{
	static POLY_F4 poly; // offset 0x0
	static POLY_FT4 p; // offset 0x20

	bool do_fade;

	if (flag == 0)
		do_fade = screen_fade_value < screen_fade_end;
	else
		do_fade = screen_fade_end < screen_fade_value;

	if (do_fade)
	{
		int val = screen_fade_value;

		if (val < 0) 
		{
			val = 0;
		}
		else if (val > 255)
		{
			val = 255;
		}

		setPolyF4(&poly);
		setSemiTrans(&poly, 1);
		setRGB0(&poly, val, val, val);

#ifdef PSX
		setXYWH(&poly, 0, 0, 320, 256);
#else
		setXYWH(&poly, -500, 0, 1200, 256);
#endif

		if (flag == 0)
			screen_fade_value += screen_fade_speed;
		else
			screen_fade_value -= screen_fade_speed;

		setPolyFT4(&p);
		setSemiTrans(&p, 1);
		setXY4(&p, -1, -1, 0, -1, -1, 0, 0, 0);
		setTPage(&p, 0, 2, 0, 0);

		DrawPrim(&p);
		DrawPrim(&poly);

#ifndef PSX
		Emulator_EndScene();
#endif
	}
	else
	{
		FadingScreen = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ShowLoadingScreen(char *screen_name /*$fp*/, int effect /*$s7*/, int loading_steps /*$a2*/)
 // line 327, offset 0x000583f4
	/* begin block 1 */
		// Start line: 328
		// Start offset: 0x000583F4
		// Variables:
	// 		int fcount; // $s0
	// 		int j; // $s2
	// 		int done; // $fp
	// 		RECT dest; // stack offset -264
	// 		SPRT prims[4]; // stack offset -256
	// 		POLY_FT3 nulls[4]; // stack offset -176
	// 		int fade; // $s5
	// 		int fade_step; // stack offset -48
	/* end block 1 */
	// End offset: 0x00058794
	// End Line: 469

	/* begin block 2 */
		// Start line: 681
	/* end block 2 */
	// End Line: 682

	/* begin block 3 */
		// Start line: 694
	/* end block 3 */
	// End Line: 695

	/* begin block 4 */
		// Start line: 703
	/* end block 4 */
	// End Line: 704

// [D] [T]
void ShowLoadingScreen(char *screen_name, int effect, int loading_steps)
{
	int done;

	SPRT *sprt;
	POLY_FT3 *null;

	uint tp;
	int i;
	int j;
	int fade;

	RECT16 dest;
	SPRT prims[4];
	POLY_FT3 nulls[4];
	int fade_step;

	if (effect == 1) 
		SetDispMask(0);

	SetupDefDrawEnv(&load_draw, 0, 0, 320, 512);
	SetupDefDispEnv(&load_disp, 0, 0, 320, 512);

	load_draw.dfe = 1;
#ifndef PSX
	extern int g_enableSwapInterval; // Psy-X var
	g_enableSwapInterval = (gFastLoadingScreens == 0);

	load_draw.clip.x = 0;
	load_draw.clip.y = 0;
	load_draw.clip.w = 320;
	load_draw.clip.h = 512;
	load_disp.isinter = 1;
#endif

	PutDispEnv(&load_disp);
	PutDrawEnv(&load_draw);

	Loadfile(screen_name, _frontend_buffer);
	LoadClut((u_long*)&_frontend_buffer[20], 320, 511);

	DrawSync(0);

	setRECT16(&dest, 320, 0, 160, 511);
	LoadImage(&dest, (u_long *)&_frontend_buffer[544]);

	DrawSync(0);

	done = 0;
	
	tp = 320;
	
	null = nulls;
	sprt = prims;

	i = 0;
	while (i < 2)
	{
		setSprt(sprt);
		sprt->x0 = (i << 8);
		sprt->y0 = 0;
		sprt->u0 = 0;
		sprt->v0 = 0;
		sprt->w = 256;
		sprt->h = 256;
		sprt->clut = getClut(320, 511);

		setPolyFT3(null);
		null->x0 = -1;
		null->y0 = -1;
		null->x1 = -1;
		null->y1 = -1;
		null->x2 = -1;
		null->y2 = -1;
		null->tpage = getTPage(1, 0, tp, 0);
	
		null++;
		sprt++;

		tp += 128;

		i++;
	}

	i = 0;
	tp = 320;

	while (i < 2)
	{
		setSprt(sprt);
		sprt->x0 = (i << 8);
		sprt->y0 = 256;
		sprt->u0 = 0;
		sprt->v0 = 0;
		sprt->w = 256;
		sprt->h = 256;
		sprt->clut = getClut(320, 511);

		setPolyFT3(null);
		null->x0 = -1;
		null->y0 = -1;
		null->x1 = -1;
		null->y1 = -1;
		null->x2 = -1;
		null->y2 = -1;
		null->tpage = getTPage(1, 0, tp, 256);

		null++;
		sprt++;
		
		tp += 128;
		
		i++;
	}

#define FADE_STEP 2

	if (effect == 1) 
	{
		fade = 8;
		fade_step = FADE_STEP;
	}
	else if (effect == 2)
	{
		fade = 128;
		fade_step = -FADE_STEP;
	}
	else
	{
		fade = 255;
		fade_step = -FADE_STEP * 2;
	}

	i = 0;
	do {

		if (i == 2)
			SetDispMask(1);
	
		i++;

		for (j = 0; j < 4; j++)
		{
			prims[j].r0 = fade;
			prims[j].g0 = fade;
			prims[j].b0 = fade;
		}

		for (j = 0; j < 4; j++)
		{
			DrawPrim(&nulls[j]);
			DrawPrim(&prims[j]);
		}
		
		DrawSync(0);

		// [A]
		if(gFastLoadingScreens == 0)
			VSync(0);
	
#ifndef PSX
		Emulator_EndScene();
#endif

		PutDispEnv(&load_disp);
		PutDrawEnv(&load_draw);

		fade += fade_step;
		
		if (effect == 1) 
		{
			if (fade > 127)
				done = 1;
		}
		else if (effect == 2)
		{
			if(fade < 0)
				done = 1;
		}
	
	} while (!done);

	load_steps = 24;

	if (gInFrontend == 0) 
		load_steps = 20;

	loading_bar_pos = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CloseShutters(int speed /*$s5*/, int width /*$s1*/, int height /*$s4*/)
 // line 482, offset 0x000589d0
	/* begin block 1 */
		// Start line: 483
		// Start offset: 0x000589D0
		// Variables:
	// 		POLY_F4 poly[2]; // stack offset -80
	// 		int h; // $s0
	// 		int done; // $s2
	/* end block 1 */
	// End offset: 0x00058B08
	// End Line: 513

	/* begin block 2 */
		// Start line: 1500
	/* end block 2 */
	// End Line: 1501

// [D] [T]
void CloseShutters(int speed, int width, int height)
{
	bool done;
	int h;
	POLY_F4 poly[2];

	h = 0;
	done = false;

	setPolyF4(&poly[0]);
	setPolyF4(&poly[1]);

	setRGB0(&poly[0], 0, 0, 0);
	setRGB0(&poly[1], 0, 0, 0);

	do {
		setXYWH(&poly[0], 0, 0, width, h);
		setXYWH(&poly[1], 0, (height - h), width, h);

		DrawPrim(&poly[0]);
		DrawPrim(&poly[1]);

		VSync(0);
#ifndef PSX
		Emulator_EndScene();
#endif

		if (h > 255) 
			done = true;

		h += speed;

	} while (!done);

	ClearOTagR((u_long*)current->ot, OTSIZE);
	ClearOTagR((u_long*)last->ot, OTSIZE);

	SetDispMask(0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupFadePolys()
 // line 527, offset 0x00058794
	/* begin block 1 */
		// Start line: 530
		// Start offset: 0x00058794
		// Variables:
	// 		int i; // $a1
	/* end block 1 */
	// End offset: 0x00058824
	// End Line: 549

	/* begin block 2 */
		// Start line: 1170
	/* end block 2 */
	// End Line: 1171

	/* begin block 3 */
		// Start line: 1229
	/* end block 3 */
	// End Line: 1230

	/* begin block 4 */
		// Start line: 1231
	/* end block 4 */
	// End Line: 1232

	/* begin block 5 */
		// Start line: 1237
	/* end block 5 */
	// End Line: 1238

/* WARNING: Unknown calling convention yet parameter storage is locked */

POLY_G4 fade_g4[2];
POLY_GT4 fade_gt4[2];

static int fadeVal = 0xFF;
static int bWantFade = 0;

// [D] [T]
void SetupFadePolys(void)
{
	int i;

	for (i = 0; i < 2; i++)
	{
		setPolyG4(&fade_g4[i]);
		setSemiTrans(&fade_g4[i], 1);

		setPolyGT4(&fade_gt4[i]);
		setSemiTrans(&fade_gt4[i], 1);

		setXYWH(&fade_gt4[i], -1, -1, 1, 1);
		setTPage(&fade_gt4[i], 0, 2, 0, 0);
	}

	bWantFade = 1;
	fadeVal = 255;
	gStopPadReads = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawFadePoly()
 // line 556, offset 0x00058824
	/* begin block 1 */
		// Start line: 558
		// Start offset: 0x00058824
		// Variables:
	// 		POLY_G4 *fl_g4; // $a2
	/* end block 1 */
	// End offset: 0x000589B0
	// End Line: 577

	/* begin block 2 */
		// Start line: 1292
	/* end block 2 */
	// End Line: 1293

	/* begin block 3 */
		// Start line: 1300
	/* end block 3 */
	// End Line: 1301

	/* begin block 4 */
		// Start line: 1301
	/* end block 4 */
	// End Line: 1302

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawFadePoly(void)
{
	if (fadeVal < 0) 
	{
		bMissionTitleFade = 0;
		
		if (!gInGameCutsceneActive)
			gStopPadReads = 0;

		fadeVal = 0;
	}

	POLY_G4 *fl_g4 = &fade_g4[current->id];


#ifdef PSX
	setXYWH(fl_g4, 0, 0, 320, 256);
#else
	setXYWH(fl_g4, -500, 0, 1200, 256);
#endif

	setRGB0(fl_g4, fadeVal, fadeVal, fadeVal);
	setRGB1(fl_g4, fadeVal, fadeVal, fadeVal);
	setRGB2(fl_g4, fadeVal, fadeVal, fadeVal);
	setRGB3(fl_g4, fadeVal, fadeVal, fadeVal);

	addPrim(&current->ot[1], fl_g4);
	addPrim(&current->ot[1], &fade_gt4[current->id]);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayMissionTitle()
 // line 585, offset 0x00058b08
	/* begin block 1 */
		// Start line: 587
		// Start offset: 0x00058B08

		/* begin block 1.1 */
			// Start line: 602
			// Start offset: 0x00058B88
		/* end block 1.1 */
		// End offset: 0x00058BB8
		// End Line: 606
	/* end block 1 */
	// End offset: 0x00058C08
	// End Line: 622

	/* begin block 2 */
		// Start line: 1651
	/* end block 2 */
	// End Line: 1652

	/* begin block 3 */
		// Start line: 1724
	/* end block 3 */
	// End Line: 1725

	/* begin block 4 */
		// Start line: 1725
	/* end block 4 */
	// End Line: 1726

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DisplayMissionTitle(void)
{
	if (bWantFade != 0 && CameraCnt == 1) 
	{
		bWantFade = 0;
		bMissionTitleFade = CameraCnt;
	}

	if (bMissionTitleFade != 0 && pauseflag == 0) 
	{
		fadeVal -= 6;

		if (NoPlayerControl != 0)
		{
			if (fadeVal < 0) 
			{
				bMissionTitleFade = 0;
				
				if (gInGameCutsceneActive == 0)
					gStopPadReads = 0;

				gShowMap = 0;
				fadeVal = 0;
			}
		}
		else 
		{
			if (gMissionTitle) 
			{
#ifdef PSX
				gShowMap = 1;
				SetTextColour(124, 108, 40);
				PrintStringCentred(gMissionTitle, 0x78);
				gShowMap = 0;
#else
				SetTextColour(124, 108, 40);
				PrintStringCentred(gMissionTitle, 120);
#endif
			}

			DrawFadePoly();
		}
	}
}





