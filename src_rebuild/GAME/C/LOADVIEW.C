#include "THISDUST.H"
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

// decompiled code
// original method signature: 
// void /*$ra*/ ShowLoading()
 // line 200, offset 0x0005816c
	/* begin block 1 */
		// Start line: 202
		// Start offset: 0x0005816C
		// Variables:
	// 		struct POLY_G4 poly; // stack offset -56
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

// [D]
void ShowLoading(void)
{
	POLY_G4 poly;

	if ((NewLevel != 0) || (gInFrontend != 0)) {
		loading_bar_pos = loading_bar_pos + 1;
		poly.x1 = (short)(loading_bar_pos * load_steps);
		if (120 < loading_bar_pos * load_steps) {
			poly.x1 = 120;
		}

		SetPolyG4(&poly);
		poly.r0 = 30;
		poly.r2 = 30;
		poly.g0 = 11;
		poly.b0 = 11;
		poly.g2 = 11;
		poly.b2 = 11;
		poly.g1 = 11;
		poly.b1 = 11;
		poly.g3 = 11;
		poly.b3 = 11;
		poly.r1 = 122;
		poly.r3 = 122;
        poly.x1 = poly.x1 + 0xb0;
        poly.y0 = 435;
        poly.y1 = 435;
        poly.x0 = 176;
        poly.x2 = 176;
        poly.y2 = 460;
        poly.y3 = 460;
        poly.x3 = poly.x1;
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

// [D]
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
	// 		static struct POLY_F4 poly; // offset 0x0
	// 		static struct POLY_FT4 p; // offset 0x20
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

// [D]
void FadeGameScreen(int flag, int speed)
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
		if (screen_fade_value < 0) 
		{
			poly.r0 = 0;
		}
		else 
		{
			poly.r0 = screen_fade_value;

			if (0xff < screen_fade_value)
			{
				poly.r0 = -1;
			}
		}

		poly.g0 = poly.b0 = poly.r0;

		setPolyF4(&poly);
		setSemiTrans(&poly, 1);
		poly.y2 = 256;
		poly.y3 = 256;
		poly.x0 = 0;
		poly.y0 = 0;
		poly.x1 = 320;
		poly.y1 = 0;
		poly.x2 = 0;
		poly.x3 = 320;

		if (flag == 0)
			screen_fade_value = screen_fade_value + speed;
		else
			screen_fade_value = screen_fade_value - speed;

		setPolyFT4(&p);
		setSemiTrans(&p, 1);
		p.x0 = -1;
		p.y0 = -1;
		p.y1 = -1;
		p.x2 = -1;
		p.x1 = 0;
		p.y2 = 0;
		p.x3 = 0;
		p.y3 = 0;
		p.tpage = 0x40;

		DrawPrim(&p);
		DrawPrim(&poly);
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
	// 		struct RECT dest; // stack offset -264
	// 		struct SPRT prims[4]; // stack offset -256
	// 		struct POLY_FT3 nulls[4]; // stack offset -176
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

// [D]
void ShowLoadingScreen(char *screen_name, int effect, int loading_steps)
{
	bool bVar1;
	char local_a0_424;
	uint uVar2;
	SPRT *pSVar3;
	SPRT *pSVar4;
	POLY_FT3 *pPVar5;
	POLY_FT3 *pPVar6;
	uint uVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	unsigned char uVar11;
	int iVar12;
	RECT16 dest;
	SPRT prims[4];
	POLY_FT3 nulls[4];
	int fade_step;

	iVar12 = 0xff;
	fade_step = -4;
	if (effect == 1) {
		SetDispMask(0);
	}
	SetupDefDrawEnv(&load_draw, 0, 0, 320, 512);
	SetupDefDispEnv(&load_disp, 0, 0, 320, 512);
	load_draw.dfe = '\x01';
	PutDispEnv(&load_disp);
	PutDrawEnv(&load_draw);

	Loadfile(screen_name, _frontend_buffer);
	LoadClut((u_long*)&_frontend_buffer[20], 320, 511);

	DrawSync(0);
	dest.x = 320;
	dest.y = 0;
	dest.w = 160;
	dest.h = 511;
	LoadImage(&dest, (u_long *)&_frontend_buffer[544]);

	DrawSync(0);

	bVar1 = false;
	iVar8 = 0;
	pSVar4 = prims + 2;
	pPVar6 = nulls + 2;
	uVar7 = 320;
	pPVar5 = nulls;
	pSVar3 = prims;
	do {
		uVar2 = uVar7 & 0x3ff;
		uVar7 = uVar7 + 0x80;
		setSprt(pSVar3);
		pSVar3->x0 = (short)(iVar8 << 8);
		pSVar3->y0 = 0;
		pSVar3->u0 = '\0';
		pSVar3->v0 = '\0';
		pSVar3->w = 0x100;
		pSVar3->h = 0x100;
		pSVar3->clut = 0x7fd4;

		setPolyFT3(pPVar5);
		pPVar5->x0 = -1;
		pPVar5->y0 = -1;
		pPVar5->x1 = -1;
		pPVar5->y1 = -1;
		pPVar5->x2 = -1;
		pPVar5->y2 = -1;
		pPVar5->tpage = (ushort)((int)uVar2 >> 6) | 0x80;
		pPVar5 = pPVar5 + 1;
		iVar8 = iVar8 + 1;
		pSVar3 = pSVar3 + 1;
	} while (iVar8 < 2);

	iVar8 = 0;
	uVar7 = 0x140;

	do {
		uVar2 = uVar7 & 0x3ff;
		uVar7 = uVar7 + 0x80;
		setSprt(pSVar4);
		pSVar4->x0 = (short)(iVar8 << 8);
		pSVar4->y0 = 0x100;
		pSVar4->u0 = '\0';
		pSVar4->v0 = '\0';
		pSVar4->w = 0x100;
		pSVar4->h = 0x100;
		pSVar4->clut = 0x7fd4;

		setPolyFT3(pPVar6);
		pPVar6->x0 = -1;
		pPVar6->y0 = -1;
		pPVar6->x1 = -1;
		pPVar6->y1 = -1;
		pPVar6->x2 = -1;
		pPVar6->y2 = -1;
		pPVar6->tpage = (ushort)((int)uVar2 >> 6) | 0x90;
		pPVar6 = pPVar6 + 1;
		iVar8 = iVar8 + 1;
		pSVar4 = pSVar4 + 1;
	} while (iVar8 < 2);

	if (effect == 1) {
		iVar12 = 8;
		fade_step = 2;
	}
	else {
		if (effect == 2) {
			iVar12 = 128;
			fade_step = -2;
		}
	}
	iVar8 = 0;
	do {
		if (iVar8 == 2) {
			SetDispMask(1);
		}
		pPVar5 = nulls;
		pSVar4 = prims;
		iVar8 = iVar8 + 1;
		iVar9 = 3;
		iVar10 = iVar12 + fade_step;
		pSVar3 = pSVar4;
		do {
			uVar11 = (unsigned char)iVar12;
			pSVar3->r0 = uVar11;
			pSVar3->g0 = uVar11;
			pSVar3->b0 = uVar11;
			iVar9 = iVar9 + -1;
			pSVar3 = pSVar3 + 1;
		} while (-1 < iVar9);
		iVar12 = 3;
		do {
			DrawPrim(pPVar5);
			DrawPrim(pSVar4);
			pSVar4 = pSVar4 + 1;
			iVar12 = iVar12 + -1;
			pPVar5 = pPVar5 + 1;
		} while (-1 < iVar12);

		DrawSync(0);
		VSync(0);

#ifndef PSX
		Emulator_EndScene();
#endif

		PutDispEnv(&load_disp);
		PutDrawEnv(&load_draw);
		if (effect == 1) {
			if (0x7f < iVar10) {
				bVar1 = true;
			}
		}
		else {
			if ((effect == 2) && (iVar10 < 0)) {
				bVar1 = true;
			}
		}
		iVar12 = iVar10;
	} while (!bVar1);
	load_steps = 0x18;
	if (gInFrontend == 0) {
		load_steps = 20;
	}
	loading_bar_pos = 0;
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CloseShutters(int speed /*$s5*/, int width /*$s1*/, int height /*$s4*/)
 // line 482, offset 0x000589d0
	/* begin block 1 */
		// Start line: 483
		// Start offset: 0x000589D0
		// Variables:
	// 		struct POLY_F4 poly[2]; // stack offset -80
	// 		int h; // $s0
	// 		int done; // $s2
	/* end block 1 */
	// End offset: 0x00058B08
	// End Line: 513

	/* begin block 2 */
		// Start line: 1500
	/* end block 2 */
	// End Line: 1501

// [D]
void CloseShutters(int speed, int width, int height)
{
	bool done;
	int h;
	POLY_F4 poly[2];

	h = 0;
	done = false;

	setPolyF4(&poly[0]);
	setPolyF4(&poly[1]);

	poly[0].r0 = 0;
	poly[0].g0 = 0;
	poly[0].b0 = 0;
	poly[1].r0 = 0;
	poly[1].g0 = 0;
	poly[1].b0 = 0;

	do {
		poly[0].y2 = (short)h;
		poly[1].y0 = (short)height - poly[0].y2;
		poly[1].y2 = poly[1].y0 + poly[0].y2;
		poly[0].x0 = 0;
		poly[0].y0 = 0;
		poly[0].x1 = (short)width;
		poly[0].y1 = 0;
		poly[0].x2 = 0;
		poly[1].x0 = 0;
		poly[1].x2 = 0;
		poly[0].x3 = poly[0].x1;
		poly[0].y3 = poly[0].y2;
		poly[1].x1 = poly[0].x1;
		poly[1].y1 = poly[1].y0;
		poly[1].x3 = poly[0].x1;
		poly[1].y3 = poly[1].y2;

		DrawPrim(poly);
		DrawPrim(poly + 1);

#ifndef PSX
		Emulator_EndScene();
#endif

		if (0xff < h) 
			done = true;

		h += speed;

	} while (!done);

	ClearOTagR((u_long*)current->ot, 0x1080);
	ClearOTagR((u_long*)last->ot, 0x1080);

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

// [D]
void SetupFadePolys(void)
{
	int i;

	i = 0;

	while (i < 2)
	{
		setPolyG4(&fade_g4[i]);
		setSemiTrans(&fade_g4[i], 1);

		setPolyGT4(&fade_gt4[i]);
		setSemiTrans(&fade_gt4[i], 1);

		fade_gt4[i].x0 = -1;
		fade_gt4[i].y0 = -1;
		fade_gt4[i].x1 = 0;
		fade_gt4[i].y1 = -1;
		fade_gt4[i].x2 = -1;
		fade_gt4[i].y2 = 0;
		fade_gt4[i].x3 = 0;
		fade_gt4[i].y3 = 0;
		fade_gt4[i].tpage = 0x40;

		i++;
	};

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
	// 		struct POLY_G4 *fl_g4; // $a2
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

// [D]
void DrawFadePoly(void)
{
	DB *pDVar1;
	int iVar2;
	POLY_G4 *pPVar3;

	iVar2 = current->id;
	pPVar3 = fade_g4 + iVar2;

	if (fadeVal < 0) 
	{
		bMissionTitleFade = 0;
		if (gInGameCutsceneActive == 0) {
			gStopPadReads = 0;
		}
		fadeVal = 0;
	}

	fade_g4[iVar2].x0 = 0;
	fade_g4[iVar2].y0 = 0;
	fade_g4[iVar2].x1 = 0x140;
	fade_g4[iVar2].y1 = 0;
	fade_g4[iVar2].x2 = 0;

	pDVar1 = current;

	fade_g4[iVar2].y2 = 0x100;
	fade_g4[iVar2].x3 = 0x140;
	fade_g4[iVar2].y3 = 0x100;

	fade_g4[iVar2].r0 = fadeVal;
	fade_g4[iVar2].g0 = fadeVal;
	fade_g4[iVar2].b0 = fadeVal;
	fade_g4[iVar2].r1 = fadeVal;
	fade_g4[iVar2].g1 = fadeVal;
	fade_g4[iVar2].b1 = fadeVal;
	fade_g4[iVar2].r2 = fadeVal;
	fade_g4[iVar2].g2 = fadeVal;
	fade_g4[iVar2].b2 = fadeVal;
	fade_g4[iVar2].r3 = fadeVal;
	fade_g4[iVar2].g3 = fadeVal;
	fade_g4[iVar2].b3 = fadeVal;

	// [A] might be incorrect still
	addPrim(pDVar1->ot + 1, pPVar3);
	addPrim(pDVar1->ot + 1, &fade_gt4[pDVar1->id]);

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

// [D]
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
		if (NoPlayerControl == 0)
		{
			if (gMissionTitle != (char *)0x0) 
			{
#ifdef PSX
				gShowMap = 1;
				SetTextColour(124, 108, 40);
				PrintStringCentred(gMissionTitle, 0x78);
				gShowMap = 0;
#else
				SetTextColour(124, 108, 40);
				PrintStringCentred(gMissionTitle, 0x78);
#endif
			}

			DrawFadePoly();
		}
		else 
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
	}
}





