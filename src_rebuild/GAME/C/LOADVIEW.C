#include "THISDUST.H"
#include "LOADVIEW.H"


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

void ShowLoading(void)
{
	UNIMPLEMENTED();
	/*
	undefined auStack56[4];
	undefined local_34;
	undefined local_33;
	undefined local_32;
	undefined2 local_30;
	undefined2 local_2e;
	undefined local_2c;
	undefined local_2b;
	undefined local_2a;
	short local_28;
	undefined2 local_26;
	undefined local_24;
	undefined local_23;
	undefined local_22;
	undefined2 local_20;
	undefined2 local_1e;
	undefined local_1c;
	undefined local_1b;
	undefined local_1a;
	short local_18;
	undefined2 local_16;

	if ((NewLevel != 0) || (gInFrontend != 0)) {
		loading_bar_pos = loading_bar_pos + 1;
		local_28 = (short)(loading_bar_pos * load_steps);
		if (0x78 < loading_bar_pos * load_steps) {
			local_28 = 0x78;
		}
		SetPolyG4(auStack56);
		local_34 = 0x1e;
		local_24 = 0x1e;
		local_33 = 0xb;
		local_32 = 0xb;
		local_23 = 0xb;
		local_22 = 0xb;
		local_2b = 0xb;
		local_2a = 0xb;
		local_1b = 0xb;
		local_1a = 0xb;
		local_2c = 0x86;
		local_1c = 0x86;
		local_28 = local_28 + 0xb0;
		local_2e = 0x1b3;
		local_26 = 0x1b3;
		local_30 = 0xb0;
		local_20 = 0xb0;
		local_1e = 0x1cc;
		local_16 = 0x1cc;
		local_18 = local_28;
		DrawPrim(auStack56);
		VSync(0);
		DrawSync(0);
		PutDrawEnv(&load_draw);
		PutDispEnv(&load_disp);
		DrawPrim(auStack56);
		VSync(0);
		DrawSync(0);
		PutDrawEnv(&load_draw);
		PutDispEnv(&load_disp);
	}
	return;
	*/
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

void ShowLoadingScreen(char *screen_name, int effect, int loading_steps)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	uint uVar2;
	undefined *puVar3;
	undefined *puVar4;
	undefined *puVar5;
	undefined *puVar6;
	uint uVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	undefined uVar11;
	int iVar12;
	undefined2 local_108;
	undefined2 local_106;
	undefined2 local_104;
	undefined2 local_102;
	undefined auStack256[40];
	undefined auStack216[40];
	undefined auStack176[3];
	undefined local_ad[4];
	undefined local_a9;
	ushort local_a8[28];
	undefined auStack112[3];
	undefined local_6d[4];
	undefined local_69;
	ushort local_68[28];
	int local_30;

	iVar12 = 0xff;
	local_30 = -4;
	if (effect == 1) {
		SetDispMask(0);
	}
	SetupDefDrawEnv(&load_draw, 0, 0, 0x140, 0x200);
	SetupDefDispEnv(&load_disp, 0, 0, 0x140, 0x200);
	load_draw.dfe = '\x01';
	PutDispEnv(&load_disp);
	PutDrawEnv(&load_draw);
	Loadfile(screen_name, &DAT_000f3000);
	LoadClut(&DAT_000f3014, 0x140, 0x1ff);
	DrawSync(0);
	local_108 = 0x140;
	local_106 = 0;
	local_104 = 0xa0;
	local_102 = 0x1ff;
	LoadImage(&local_108, &DAT_000f3220);
	DrawSync(0);
	bVar1 = false;
	iVar8 = 0;
	puVar4 = auStack216;
	puVar6 = auStack112;
	uVar7 = 0x140;
	puVar5 = auStack176;
	puVar3 = auStack256;
	do {
		uVar2 = uVar7 & 0x3ff;
		uVar7 = uVar7 + 0x80;
		puVar3[3] = 4;
		puVar3[7] = 100;
		*(short *)(puVar3 + 8) = (short)(iVar8 << 8);
		*(undefined2 *)(puVar3 + 10) = 0;
		puVar3[0xc] = 0;
		puVar3[0xd] = 0;
		*(undefined2 *)(puVar3 + 0x10) = 0x100;
		*(undefined2 *)(puVar3 + 0x12) = 0x100;
		*(undefined2 *)(puVar3 + 0xe) = 0x7fd4;
		puVar5[3] = 7;
		*(undefined2 *)(puVar5 + 8) = 0xffff;
		*(undefined2 *)(puVar5 + 10) = 0xffff;
		*(undefined2 *)(puVar5 + 0x10) = 0xffff;
		*(undefined2 *)(puVar5 + 0x12) = 0xffff;
		*(undefined2 *)(puVar5 + 0x18) = 0xffff;
		*(undefined2 *)(puVar5 + 0x1a) = 0xffff;
		puVar5[7] = 0x24;
		*(ushort *)(puVar5 + 0x16) = (ushort)((int)uVar2 >> 6) | 0x80;
		puVar5 = puVar5 + 0x20;
		iVar8 = iVar8 + 1;
		puVar3 = puVar3 + 0x14;
	} while (iVar8 < 2);
	iVar8 = 0;
	uVar7 = 0x140;
	do {
		uVar2 = uVar7 & 0x3ff;
		uVar7 = uVar7 + 0x80;
		puVar4[3] = 4;
		puVar4[7] = 100;
		*(short *)(puVar4 + 8) = (short)(iVar8 << 8);
		*(undefined2 *)(puVar4 + 10) = 0x100;
		puVar4[0xc] = 0;
		puVar4[0xd] = 0;
		*(undefined2 *)(puVar4 + 0x10) = 0x100;
		*(undefined2 *)(puVar4 + 0x12) = 0x100;
		*(undefined2 *)(puVar4 + 0xe) = 0x7fd4;
		puVar6[3] = 7;
		*(undefined2 *)(puVar6 + 8) = 0xffff;
		*(undefined2 *)(puVar6 + 10) = 0xffff;
		*(undefined2 *)(puVar6 + 0x10) = 0xffff;
		*(undefined2 *)(puVar6 + 0x12) = 0xffff;
		*(undefined2 *)(puVar6 + 0x18) = 0xffff;
		*(undefined2 *)(puVar6 + 0x1a) = 0xffff;
		puVar6[7] = 0x24;
		*(ushort *)(puVar6 + 0x16) = (ushort)((int)uVar2 >> 6) | 0x90;
		puVar6 = puVar6 + 0x20;
		iVar8 = iVar8 + 1;
		puVar4 = puVar4 + 0x14;
	} while (iVar8 < 2);
	if (effect == 1) {
		iVar12 = 8;
		local_30 = 2;
	}
	else {
		if (effect == 2) {
			iVar12 = 0x80;
			local_30 = -2;
		}
	}
	iVar8 = 0;
	do {
		if (iVar8 == 2) {
			SetDispMask(1);
		}
		puVar4 = auStack176;
		puVar5 = auStack256;
		iVar8 = iVar8 + 1;
		iVar9 = 3;
		iVar10 = iVar12 + local_30;
		puVar3 = puVar5;
		do {
			uVar11 = (undefined)iVar12;
			puVar3[4] = uVar11;
			puVar3[5] = uVar11;
			puVar3[6] = uVar11;
			iVar9 = iVar9 + -1;
			puVar3 = puVar3 + 0x14;
		} while (-1 < iVar9);
		iVar12 = 3;
		do {
			DrawPrim(puVar4);
			DrawPrim(puVar5);
			puVar5 = puVar5 + 0x14;
			iVar12 = iVar12 + -1;
			puVar4 = puVar4 + 0x20;
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
		load_steps = 0x14;
	}
	loading_bar_pos = 0;
	return;
	*/
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





