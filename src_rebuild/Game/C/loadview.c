#include "driver2.h"
#include "loadview.h"

#include "E3stuff.h"
#include "system.h"
#include "glaunch.h"
#include "mission.h"
#include "camera.h"
#include "pause.h"
#include "pres.h"
#include "main.h"
#include "cutscene.h"

#include "LIBETC.H"

DRAWENV load_draw = { 0 };
DISPENV load_disp = { 0 };

int load_steps = 0;
int loading_bar_pos = 0;
int gFastLoadingScreens = 0;

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
	PsyX_EndScene();
#endif
}

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
		PsyX_EndScene();
#endif
	}
	else
	{
		FadingScreen = 0;
	}
}

// [D] [T]
void ShowLoadingScreen(char *screen_name, int effect, int loading_steps)
{
	int done;

	SPRT *sprt;
	POLY_FT3 *null;

	u_int tp;
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
	PsyX_EnableSwapInterval((gFastLoadingScreens == 0));

	load_draw.clip.x = 0;
	load_draw.clip.y = 0;
	load_draw.clip.w = 320;
	load_draw.clip.h = 512;
	load_disp.isinter = 1;
#endif

	PutDispEnv(&load_disp);
	PutDrawEnv(&load_draw);

	Loadfile(screen_name, (char*)_other_buffer);
	LoadClut((u_long*)&_other_buffer[20], 320, 511);

	DrawSync(0);

	setRECT(&dest, 320, 0, 160, 511);
	LoadImage(&dest, (u_long *)&_other_buffer[544]);

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
		PsyX_EndScene();
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
		PsyX_EndScene();
#endif

		if (h > 255) 
			done = true;

		h += speed;

	} while (!done);

	ClearOTagR((u_long*)current->ot, OTSIZE);
	ClearOTagR((u_long*)last->ot, OTSIZE);

	SetDispMask(0);
}


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

// [D] [T]
void DisplayMissionTitle(void)
{
	if (bWantFade && CameraCnt == 1) 
	{
		bWantFade = 0;
		bMissionTitleFade = CameraCnt;
	}

	if (bMissionTitleFade && !pauseflag) 
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
				PrintStringCentred(gMissionTitle, 120);
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





