#include "THISDUST.H"
#include "LOADVIEW.H"

#include "E3STUFF.H"
#include "SYSTEM.H"
#include "LIBETC.H"
#include "GLAUNCH.H"
#include "MISSION.H"
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

void SetupScreenFade(int start, int end, int speed)
{
	/*
	screen_fade_value = start;
	screen_fade_start = start;
	screen_fade_end = end;
	screen_fade_speed = speed;
	FadingScreen = 1;
	return;*/
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

void FadeGameScreen(int flag, int speed)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;

	if (flag == 0) {
		bVar1 = screen_fade_value < screen_fade_end;
	}
	else {
		bVar1 = screen_fade_end < screen_fade_value;
	}
	if (bVar1) {
		if (screen_fade_value < 0) {
			DAT_000d54dc = 0;
		}
		else {
			DAT_000d54dc = (undefined)screen_fade_value;
			if (0xff < screen_fade_value) {
				DAT_000d54dc = 0xff;
			}
		}
		DAT_000d54fb = 9;
		DAT_000d5500 = 0xffff;
		DAT_000d5502 = 0xffff;
		DAT_000d550a = 0xffff;
		DAT_000d5510 = 0xffff;
		DAT_000d54ff = 0x2e;
		DAT_000d5508 = 0;
		DAT_000d5512 = 0;
		DAT_000d5518 = 0;
		DAT_000d551a = 0;
		DAT_000d550e = 0x40;
		DAT_000d54db = 5;
		DAT_000d54ea = 0x100;
		DAT_000d54ee = 0x100;
		DAT_000d54e0 = 0;
		DAT_000d54e2 = 0;
		DAT_000d54e4 = 0x140;
		DAT_000d54e6 = 0;
		DAT_000d54e8 = 0;
		DAT_000d54ec = 0x140;
		DAT_000d54df = 0x2a;
		if (flag == 0) {
			screen_fade_value = screen_fade_value + speed;
		}
		else {
			screen_fade_value = screen_fade_value - speed;
		}
		DAT_000d54dd = DAT_000d54dc;
		DAT_000d54de = DAT_000d54dc;
		DrawPrim(&p_10);
		DrawPrim(&poly_9);
	}
	else {
		FadingScreen = 0;
	}
	return;
	*/
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

void CloseShutters(int speed, int width, int height)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	int iVar2;
	undefined auStack80[3];
	undefined local_4d;
	undefined local_4c;
	undefined local_4b;
	undefined local_4a;
	undefined local_49;
	undefined2 local_48;
	undefined2 local_46;
	undefined2 local_44;
	undefined2 local_42;
	undefined2 local_40;
	short local_3e;
	undefined2 local_3c;
	short local_3a;
	undefined auStack56[3];
	undefined local_35;
	undefined local_34;
	undefined local_33;
	undefined local_32;
	undefined local_31;
	undefined2 local_30;
	short local_2e;
	undefined2 local_2c;
	short local_2a;
	undefined2 local_28;
	short local_26;
	undefined2 local_24;
	short local_22;

	iVar2 = 0;
	bVar1 = false;
	local_4d = 5;
	local_49 = 0x28;
	local_35 = 5;
	local_31 = 0x28;
	local_4c = 0;
	local_4b = 0;
	local_4a = 0;
	local_34 = 0;
	local_33 = 0;
	local_32 = 0;
	do {
		local_3e = (short)iVar2;
		local_2e = (short)height - local_3e;
		local_26 = local_2e + local_3e;
		local_48 = 0;
		local_46 = 0;
		local_44 = (undefined2)width;
		local_42 = 0;
		local_40 = 0;
		local_30 = 0;
		local_28 = 0;
		local_3c = local_44;
		local_3a = local_3e;
		local_2c = local_44;
		local_2a = local_2e;
		local_24 = local_44;
		local_22 = local_26;
		DrawPrim(auStack80);
		DrawPrim(auStack56);
		iVar2 = iVar2 + speed;
		if (0xff < iVar2) {
			bVar1 = true;
		}
	} while (!bVar1);
	ClearOTagR(current->ot, (int)&DAT_00001080);
	ClearOTagR(last->ot, (int)&DAT_00001080);
	SetDispMask(0);
	return;
	*/
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

void SetupFadePolys(void)
{
	UNIMPLEMENTED();
	/*
	POLY_G4 *pPVar1;
	POLY_GT4 *pPVar2;
	int iVar3;

	pPVar1 = fade_g4;
	pPVar2 = fade_gt4;
	iVar3 = 1;
	do {
		*(undefined *)((int)&pPVar1->tag + 3) = 8;
		pPVar1->code = ':';
		pPVar1 = pPVar1 + 1;
		*(undefined *)((int)&pPVar2->tag + 3) = 0xc;
		pPVar2->code = '>';
		pPVar2->x0 = -1;
		pPVar2->y0 = -1;
		pPVar2->x1 = 0;
		pPVar2->y1 = -1;
		pPVar2->x2 = -1;
		pPVar2->y2 = 0;
		pPVar2->x3 = 0;
		pPVar2->y3 = 0;
		pPVar2->tpage = 0x40;
		iVar3 = iVar3 + -1;
		pPVar2 = pPVar2 + 1;
	} while (-1 < iVar3);
	bWantFade = 1;
	fadeVal = 0xff;
	gStopPadReads = 1;
	return;*/
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

void DrawFadePoly(void)
{
	UNIMPLEMENTED();
	/*
	DB *pDVar1;
	int iVar2;
	POLY_G4 *pPVar3;

	iVar2 = current->id;
	pPVar3 = fade_g4 + iVar2;
	if (fadeVal < 0) {
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
	fade_g4[iVar2].r0 = (uchar)fadeVal;
	fade_g4[iVar2].g0 = (uchar)fadeVal;
	fade_g4[iVar2].b0 = (uchar)fadeVal;
	fade_g4[iVar2].r1 = (uchar)fadeVal;
	fade_g4[iVar2].g1 = (uchar)fadeVal;
	fade_g4[iVar2].b1 = (uchar)fadeVal;
	fade_g4[iVar2].r2 = (uchar)fadeVal;
	fade_g4[iVar2].g2 = (uchar)fadeVal;
	fade_g4[iVar2].b2 = (uchar)fadeVal;
	fade_g4[iVar2].r3 = (uchar)fadeVal;
	fade_g4[iVar2].g3 = (uchar)fadeVal;
	fade_g4[iVar2].b3 = (uchar)fadeVal;
	pPVar3->tag = pPVar3->tag & 0xff000000 | *(uint *)pDVar1->ot[1] & 0xffffff;
	*(uint *)pDVar1->ot[1] = *(uint *)pDVar1->ot[1] & 0xff000000 | (uint)pPVar3 & 0xffffff;
	fade_gt4[pDVar1->id].tag =
		fade_gt4[pDVar1->id].tag & 0xff000000 | *(uint *)pDVar1->ot[1] & 0xffffff;
	*(uint *)pDVar1->ot[1] =
		*(uint *)pDVar1->ot[1] & 0xff000000 | (uint)(fade_gt4 + pDVar1->id) & 0xffffff;
	return;*/
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

void DisplayMissionTitle(void)
{
	UNIMPLEMENTED();
	/*
	if ((bWantFade != 0) && (CameraCnt == 1)) {
		bWantFade = 0;
		bMissionTitleFade = CameraCnt;
	}
	if ((bMissionTitleFade != 0) && (pauseflag == 0)) {
		fadeVal = fadeVal + -6;
		if (NoPlayerControl == 0) {
			if (gMissionTitle != (char *)0x0) {
				gShowMap = 1;
				SetTextColour('|', 'l', '(');
				PrintStringCentred(gMissionTitle, 0x78);
				gShowMap = 0;
			}
			DrawFadePoly();
		}
		else {
			if (fadeVal < 0) {
				bMissionTitleFade = 0;
				if (gInGameCutsceneActive == 0) {
					gStopPadReads = 0;
				}
				gShowMap = 0;
				fadeVal = 0;
			}
		}
	}
	return;
	*/
}





