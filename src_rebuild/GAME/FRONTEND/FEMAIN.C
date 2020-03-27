#include "THISDUST.H"
#include "FEMAIN.H"

#include "LIBGPU.H"
#include "LIBETC.H"

#include "../C/SYSTEM.H"
#include "../C/GLAUNCH.H"

// decompiled code
// original method signature: 
// void /*$ra*/ SetVariable(int var /*$a0*/)
 // line 1205, offset 0x001c0974
	/* begin block 1 */
		// Start line: 1206
		// Start offset: 0x001C0974
		// Variables:
	// 		int code; // $v1
	// 		int value; // $a2
	/* end block 1 */
	// End offset: 0x001C0C1C
	// End Line: 1362

	/* begin block 2 */
		// Start line: 2410
	/* end block 2 */
	// End Line: 2411

	/* begin block 3 */
		// Start line: 2414
	/* end block 3 */
	// End Line: 2415

void SetVariable(int var)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	byte bVar2;
	GAMETYPE GVar3;
	uint uVar4;

	iVar1 = ScreenDepth;
	uVar4 = var & 0xff;
	if (0xc < (var >> 8) - 1U) {
		return;
	}
	GVar3 = (GAMETYPE)uVar4;
	switch (var >> 8) {
	case 1:
		GameLevel = uVar4;
		break;
	case 2:
		GameType = GVar3;
		if (uVar4 != 0xb) {
			return;
		}
		goto LAB_FRNT__001c0a08;
	case 3:
		NumPlayers = GVar3 + GAME_TAKEADRIVE;
		break;
	case 4:
		if (uVar4 != 0) {
			gWantNight = 1;
			return;
		}
	LAB_FRNT__001c0a08:
		gWantNight = 0;
		break;
	case 5:
		gCurrentMissionNumber = 1;
		GameType = GAME_MISSION;
		break;
	case 6:
		pScreenStack10[ScreenDepth] = pCurrScreen;
		pButtonStack10[iVar1] = pCurrButton;
		if (uVar4 != 1) {
			CallMemoryCard(0x81, 0);
			ReInitFrontend();
			SetMasterVolume(gMasterVolume);
			SetXMVolume(gMusicVolume);
			return;
		}
		iVar1 = CallMemoryCard(0x11, 0);
		GVar3 = GameType;
		if (iVar1 != 0) {
			GameType = GAME_LOADEDREPLAY;
			StoredGameType = GVar3;
			GameStart();
			return;
		}
		goto LAB_FRNT__001c0a68;
	case 7:
		pScreenStack10[ScreenDepth] = pCurrScreen;
		pButtonStack10[iVar1] = pCurrButton;
		if (uVar4 == 0) {
			CallMemoryCard(0x80, 0);
		}
		else {
			iVar1 = CallMemoryCard(0x21, 0);
			if (iVar1 != 0) {
				GameType = GAME_CONTINUEMISSION;
				GameStart();
				return;
			}
		}
	LAB_FRNT__001c0a68:
		ReInitFrontend();
		break;
	case 8:
		gSubGameNumber = uVar4;
		break;
	case 9:
		if (uVar4 == 0) {
			gSubtitles = 0;
		}
		else {
			gSubtitles = 1;
		}
		break;
	case 10:
		bVar2 = (byte)((var & 1U) << 2);
		ActiveCheats._0_1_ = (byte)ActiveCheats & 0xfb;
		gInvincibleCar = uVar4;
		goto LAB_FRNT__001c0bbc;
	case 0xb:
		bVar2 = (byte)((var & 1U) << 3);
		ActiveCheats._0_1_ = (byte)ActiveCheats & 0xf7;
		gPlayerImmune = uVar4;
	LAB_FRNT__001c0bbc:
		ActiveCheats._0_1_ = (byte)ActiveCheats | bVar2;
		break;
	case 0xc:
		GameLevel = 3;
		if (uVar4 == 0) {
			gSubGameNumber = 2;
		}
		else {
			gSubGameNumber = 0;
		}
		break;
	case 0xd:
		GameType = GAME_IDLEDEMO;
		gCurrentMissionNumber = uVar4 + 400;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadFrontendScreens()
 // line 1371, offset 0x001c0c1c
	/* begin block 1 */
		// Start line: 1373
		// Start offset: 0x001C0C1C
		// Variables:
	// 		int iTpage; // $s0
	// 		int iNumScreens; // $t6
	// 		int i; // $t0
	// 		int j; // $a3
	// 		struct RECT rect; // stack offset -40
	// 		char *ptr; // $a2
	/* end block 1 */
	// End offset: 0x001C0F24
	// End Line: 1454

	/* begin block 2 */
		// Start line: 2740
	/* end block 2 */
	// End Line: 2741

	/* begin block 3 */
		// Start line: 2750
	/* end block 3 */
	// End Line: 2751

	/* begin block 4 */
		// Start line: 2751
	/* end block 4 */
	// End Line: 2752

	/* begin block 5 */
		// Start line: 2761
	/* end block 5 */
	// End Line: 2762

/* WARNING: Unknown calling convention yet parameter storage is locked */

void LoadFrontendScreens(void)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	int iVar2;
	undefined4 *puVar3;
	undefined4 *puVar4;
	undefined4 *puVar5;
	int iVar6;
	int offset;
	undefined4 uVar7;
	int iVar8;
	uint uVar9;
	undefined4 uVar10;
	int iVar11;
	undefined4 uVar12;
	short sVar13;
	short local_28;
	undefined2 local_26;
	undefined2 local_24;
	undefined2 local_22;

	ShowLoadingScreen(s_GFX_FELOAD_TIM_FRNT__001c07d4, 1, 0xc);
	ShowLoading();
	Loadfile(s_DATA_SCRS_BIN_FRNT__001c07e4, &DAT_000fb400);
	puVar5 = (undefined4 *)&DAT_000fb414;
	uVar9 = (uint)DAT_000fb410;
	if (DAT_000fb410 != 0) {
		offset = 0;
		iVar11 = 0;
		do {
			cVar1 = *(char *)puVar5;
			iVar6 = 0;
			iVar2 = (offset * 8 + iVar11 * -7) * 4;
			iVar8 = iVar11 + 1;
			(&DAT_FRNT__001c6d51)[iVar2] = cVar1;
			(&DAT_FRNT__001c6d52)[iVar2] = *(char *)((int)puVar5 + 1);
			puVar5 = (undefined4 *)((int)puVar5 + 2);
			if (cVar1 != '\0') {
				iVar2 = 0;
				do {
					puVar3 = &DAT_FRNT__001c6d54 + offset * 8 + iVar11 * -7 + (iVar2 - iVar6);
					puVar4 = puVar5;
					if (((uint)puVar5 & 3) == 0) {
						do {
							uVar7 = puVar4[1];
							uVar10 = puVar4[2];
							uVar12 = puVar4[3];
							*puVar3 = *puVar4;
							puVar3[1] = uVar7;
							puVar3[2] = uVar10;
							puVar3[3] = uVar12;
							puVar4 = puVar4 + 4;
							puVar3 = puVar3 + 4;
						} while (puVar4 != puVar5 + 0xc);
					}
					else {
						do {
							uVar7 = puVar4[1];
							uVar10 = puVar4[2];
							uVar12 = puVar4[3];
							*puVar3 = *puVar4;
							puVar3[1] = uVar7;
							puVar3[2] = uVar10;
							puVar3[3] = uVar12;
							puVar4 = puVar4 + 4;
							puVar3 = puVar3 + 4;
						} while (puVar4 != puVar5 + 0xc);
					}
					puVar5 = puVar5 + 0xf;
					iVar6 = iVar6 + 1;
					uVar7 = puVar4[1];
					uVar10 = puVar4[2];
					*puVar3 = *puVar4;
					puVar3[1] = uVar7;
					puVar3[2] = uVar10;
					iVar2 = iVar6 * 0x10;
				} while (iVar6 < (int)(uint)(byte)(&DAT_FRNT__001c6d51)[(offset * 8 + iVar11 * -7) * 4]);
			}
			offset = iVar8 * 0x10;
			iVar11 = iVar8;
		} while (iVar8 < (int)uVar9);
	}
	local_24 = 0x40;
	local_22 = 0x100;
	ShowLoading();
	LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
	sVar13 = 0x280;
	offset = 0x30000;
	iVar11 = 1;
	do {
		iVar11 = iVar11 + -1;
		ShowLoading();
		LoadfileSeg(s_DATA_GFX_RAW_FRNT__001c07f4, &DAT_000fb400, offset, 0x8000);
		local_26 = 0x100;
		local_28 = sVar13;
		LoadImage(&local_28, &DAT_000fb400);
		DrawSync(0);
		sVar13 = sVar13 + 0x40;
		offset = offset + 0x8000;
	} while (-1 < iVar11);
	ShowLoading();
	LoadfileSeg(s_DATA_GFX_RAW_FRNT__001c07f4, &DAT_000fb400, 0x58000, 0x8000);
	local_28 = 0x3c0;
	local_26 = 0x100;
	LoadImage(&local_28, &DAT_000fb400);
	DrawSync(0);
	Loadfile(s_DATA_FEFONT_BNK_FRNT__001c0804, &DAT_FRNT__001cbdd8);
	PadChecks();
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadBackgroundFile(char *name /*$s4*/)
 // line 1461, offset 0x001c0f24
	/* begin block 1 */
		// Start line: 1462
		// Start offset: 0x001C0F24
		// Variables:
	// 		int iTpage; // $s2
	// 		struct RECT rect; // stack offset -72
	// 		int p; // $s0
	// 		int pages[7]; // stack offset -64
	/* end block 1 */
	// End offset: 0x001C10F4
	// End Line: 1509

	/* begin block 2 */
		// Start line: 2951
	/* end block 2 */
	// End Line: 2952

	/* begin block 3 */
		// Start line: 2959
	/* end block 3 */
	// End Line: 2960

void LoadBackgroundFile(char *name)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	int *piVar3;
	short local_48;
	short local_46;
	undefined2 local_44;
	undefined2 local_42;
	int local_40[4];
	undefined4 local_30;
	undefined4 local_2c;
	int local_28;

	local_40[0] = DAT_FRNT__001c0814;
	local_40[1] = DAT_FRNT__001c0818;
	local_40[2] = DAT_FRNT__001c081c;
	local_40[3] = DAT_FRNT__001c0820;
	local_30 = DAT_FRNT__001c0824;
	local_2c = DAT_FRNT__001c0828;
	local_28 = DAT_FRNT__001c082c;
	iVar1 = strcmp(name, s_DATA_GFX_RAW_FRNT__001c07f4);
	DAT_FRNT__001c6ac4 = (uint)(iVar1 == 0);
	piVar3 = local_40;
	iVar1 = 5;
	local_44 = 0x40;
	local_42 = 0x100;
	do {
		FEDrawCDicon();
		iVar2 = *piVar3;
		LoadfileSeg(name, &DAT_000fb400, iVar2 << 0xf, 0x8000);
		piVar3 = piVar3 + 1;
		FEDrawCDicon();
		iVar1 = iVar1 + -1;
		local_46 = (short)(iVar2 / 6);
		local_48 = ((short)iVar2 + local_46 * -6) * 0x40 + 0x280;
		local_46 = local_46 * 0x100;
		LoadImage(&local_48, &DAT_000fb400);
		FEDrawCDicon();
		iVar2 = local_28;
	} while (-1 < iVar1);
	LoadfileSeg(name, &DAT_000fb400, local_28 << 0xf, 0x800);
	FEDrawCDicon();
	local_42 = 1;
	local_46 = (short)(iVar2 / 6);
	local_48 = ((short)iVar2 + local_46 * -6) * 0x40 + 0x280;
	local_46 = local_46 * 0x100;
	LoadImage(&local_48, &DAT_000fb400);
	DrawSync(0);
	SetupBackgroundPolys();
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupBackgroundPolys()
 // line 1516, offset 0x001c10f4
	/* begin block 1 */
		// Start line: 1518
		// Start offset: 0x001C10F4
		// Variables:
	// 		int i; // $v1
	// 		int tpage; // $t3
	/* end block 1 */
	// End offset: 0x001C132C
	// End Line: 1580

	/* begin block 2 */
		// Start line: 3110
	/* end block 2 */
	// End Line: 3111

	/* begin block 3 */
		// Start line: 3118
	/* end block 3 */
	// End Line: 3119

	/* begin block 4 */
		// Start line: 3119
	/* end block 4 */
	// End Line: 3120

	/* begin block 5 */
		// Start line: 3122
	/* end block 5 */
	// End Line: 3123

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SetupBackgroundPolys(void)
{
	UNIMPLEMENTED();
	/*
	undefined4 *puVar1;
	int iVar2;

	puVar1 = &DAT_FRNT__001cbcc0;
	iVar2 = 5;
	do {
		*(undefined *)((int)puVar1 + 3) = 9;
		*(undefined *)(puVar1 + 1) = 0x80;
		*(undefined *)((int)puVar1 + 5) = 0x80;
		*(undefined *)((int)puVar1 + 6) = 0x80;
		*(undefined *)((int)puVar1 + 7) = 0x2c;
		iVar2 = iVar2 + -1;
		puVar1 = puVar1 + 10;
	} while (-1 < iVar2);
	DAT_FRNT__001cbcc8 = 0;
	DAT_FRNT__001cbcca = 0;
	DAT_FRNT__001cbccc = 0;
	DAT_FRNT__001cbccd = 1;
	DAT_FRNT__001cbcce = 0x403c;
	DAT_FRNT__001cbcd0 = 0x100;
	DAT_FRNT__001cbcd2 = 0;
	DAT_FRNT__001cbcd4 = 0xff;
	DAT_FRNT__001cbcd5 = 1;
	DAT_FRNT__001cbcd6 = 10;
	DAT_FRNT__001cbcd8 = 0;
	DAT_FRNT__001cbcda = 0x100;
	DAT_FRNT__001cbcdc = 0;
	DAT_FRNT__001cbcdd = 0xff;
	DAT_FRNT__001cbce0 = 0x100;
	DAT_FRNT__001cbce2 = 0x100;
	DAT_FRNT__001cbce4 = 0xff;
	DAT_FRNT__001cbce5 = 0xff;
	DAT_FRNT__001cbcf0 = 0x100;
	DAT_FRNT__001cbcf2 = 0;
	DAT_FRNT__001cbcf4 = 0;
	DAT_FRNT__001cbcf5 = 1;
	DAT_FRNT__001cbcf6 = 0x403c;
	DAT_FRNT__001cbcf8 = 0x200;
	DAT_FRNT__001cbcfa = 0;
	DAT_FRNT__001cbcfc = 0xff;
	DAT_FRNT__001cbcfd = 1;
	DAT_FRNT__001cbcfe = 0xb;
	DAT_FRNT__001cbd00 = 0x100;
	DAT_FRNT__001cbd02 = 0x100;
	DAT_FRNT__001cbd04 = 0;
	DAT_FRNT__001cbd05 = 0xff;
	DAT_FRNT__001cbd08 = 0x200;
	DAT_FRNT__001cbd0a = 0x100;
	DAT_FRNT__001cbd0c = 0xff;
	DAT_FRNT__001cbd0d = 0xff;
	DAT_FRNT__001cbd18 = 0x200;
	DAT_FRNT__001cbd1a = 0;
	DAT_FRNT__001cbd1c = 0;
	DAT_FRNT__001cbd1d = 1;
	DAT_FRNT__001cbd1e = 0x403c;
	DAT_FRNT__001cbd20 = 0x280;
	DAT_FRNT__001cbd22 = 0;
	DAT_FRNT__001cbd24 = 0x80;
	DAT_FRNT__001cbd25 = 1;
	DAT_FRNT__001cbd26 = 0xc;
	DAT_FRNT__001cbd28 = 0x200;
	DAT_FRNT__001cbd2a = 0x100;
	DAT_FRNT__001cbd2c = 0;
	DAT_FRNT__001cbd2d = 0xff;
	DAT_FRNT__001cbd30 = 0x280;
	DAT_FRNT__001cbd32 = 0x100;
	DAT_FRNT__001cbd34 = 0x80;
	DAT_FRNT__001cbd35 = 0xff;
	DAT_FRNT__001cbd40 = 0;
	DAT_FRNT__001cbd42 = 0x100;
	DAT_FRNT__001cbd44 = 0;
	DAT_FRNT__001cbd45 = 0;
	DAT_FRNT__001cbd46 = 0x403c;
	DAT_FRNT__001cbd48 = 0x100;
	DAT_FRNT__001cbd4a = 0x100;
	DAT_FRNT__001cbd4c = 0xff;
	DAT_FRNT__001cbd4d = 0;
	DAT_FRNT__001cbd4e = 0xd;
	DAT_FRNT__001cbd50 = 0;
	DAT_FRNT__001cbd52 = 0x200;
	DAT_FRNT__001cbd54 = 0;
	DAT_FRNT__001cbd55 = 0xff;
	DAT_FRNT__001cbd58 = 0x100;
	DAT_FRNT__001cbd5a = 0x200;
	DAT_FRNT__001cbd5c = 0xff;
	DAT_FRNT__001cbd5d = 0xff;
	DAT_FRNT__001cbd68 = 0x100;
	DAT_FRNT__001cbd6a = 0x100;
	DAT_FRNT__001cbd6c = 0;
	DAT_FRNT__001cbd6d = 0;
	DAT_FRNT__001cbd6e = 0x403c;
	DAT_FRNT__001cbd70 = 0x200;
	DAT_FRNT__001cbd72 = 0x100;
	DAT_FRNT__001cbd74 = 0xff;
	DAT_FRNT__001cbd75 = 0;
	DAT_FRNT__001cbd76 = 0xe;
	DAT_FRNT__001cbd78 = 0x100;
	DAT_FRNT__001cbd7a = 0x200;
	DAT_FRNT__001cbd7c = 0;
	DAT_FRNT__001cbd7d = 0xff;
	DAT_FRNT__001cbd80 = 0x200;
	DAT_FRNT__001cbd82 = 0x200;
	DAT_FRNT__001cbd84 = 0xff;
	DAT_FRNT__001cbd85 = 0xff;
	DAT_FRNT__001cbd90 = 0x200;
	DAT_FRNT__001cbd92 = 0x100;
	DAT_FRNT__001cbd94 = 0;
	DAT_FRNT__001cbd95 = 0;
	DAT_FRNT__001cbd96 = 0x403c;
	DAT_FRNT__001cbd98 = 0x280;
	DAT_FRNT__001cbd9a = 0x100;
	DAT_FRNT__001cbd9c = 0x80;
	DAT_FRNT__001cbd9d = 0;
	DAT_FRNT__001cbd9e = 0xf;
	DAT_FRNT__001cbda0 = 0x200;
	DAT_FRNT__001cbda2 = 0x200;
	DAT_FRNT__001cbda4 = 0;
	DAT_FRNT__001cbda5 = 0xff;
	DAT_FRNT__001cbda8 = 0x280;
	DAT_FRNT__001cbdaa = 0x200;
	DAT_FRNT__001cbdac = 0x80;
	DAT_FRNT__001cbdad = 0xff;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupScreenSprts(struct PSXSCREEN *pScr /*$a0*/)
 // line 1588, offset 0x001c132c
	/* begin block 1 */
		// Start line: 1589
		// Start offset: 0x001C132C
		// Variables:
	// 		int tpage; // $a1
	// 		struct POLY_FT3 *null; // $v0
	/* end block 1 */
	// End offset: 0x001C147C
	// End Line: 1650

	/* begin block 2 */
		// Start line: 3344
	/* end block 2 */
	// End Line: 3345

	/* begin block 3 */
		// Start line: 3353
	/* end block 3 */
	// End Line: 3354

	/* begin block 4 */
		// Start line: 3363
	/* end block 4 */
	// End Line: 3364

void SetupScreenSprts(PSXSCREEN *pScr)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	DAT_FRNT__001cc590._3_1_ = 4;
	DAT_FRNT__001cc594 = 0x80;
	DAT_FRNT__001cc595 = 0x80;
	DAT_FRNT__001cc596 = 0x80;
	DAT_FRNT__001cc597 = 100;
	DAT_FRNT__001cc598 = 0x16c;
	DAT_FRNT__001cc59a = 0xc6;
	DAT_FRNT__001cc5a0 = 0x100;
	DAT_FRNT__001cc59c = 0;
	DAT_FRNT__001cc59d = 0;
	DAT_FRNT__001cc5a2 = 0x24;
	DAT_FRNT__001cc59e = 0x40bc;
	DAT_FRNT__001cc5a8._3_1_ = 7;
	DAT_FRNT__001cc5af = 0x24;
	DAT_FRNT__001cc5b0 = 0xffff;
	DAT_FRNT__001cc5b2 = 0xffff;
	DAT_FRNT__001cc5b8 = 0xffff;
	DAT_FRNT__001cc5ba = 0xffff;
	DAT_FRNT__001cc5c0 = 0xffff;
	DAT_FRNT__001cc5c2 = 0xffff;
	DAT_FRNT__001cc5be = 0x1b;
	DAT_FRNT__001c6d48 = 0;
	pCurrScreen = pScr;
	if (pScr->userFunctionNum == 0) {
		if (DAT_FRNT__001cbcb8 == (PSXBUTTON *)0x0) {
			pCurrButton = pScr->buttons;
		}
		else {
			pCurrButton = DAT_FRNT__001cbcb8;
			DAT_FRNT__001cbcb8 = (PSXBUTTON *)0x0;
		}
	}
	else {
		iVar1 = (*(code *)(&PTR_CentreScreen_FRNT__001c6a20)[(uint)(byte)pScr->userFunctionNum - 1])(1);
		if (iVar1 == 0) {
			if (DAT_FRNT__001cbcb8 == (PSXBUTTON *)0x0) {
				pCurrButton = pCurrScreen->buttons;
			}
			else {
				pCurrButton = DAT_FRNT__001cbcb8;
				DAT_FRNT__001cbcb8 = (PSXBUTTON *)0x0;
			}
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawScreen(struct PSXSCREEN *pScr /*stack 0*/)
 // line 1658, offset 0x001c147c
	/* begin block 1 */
		// Start line: 1659
		// Start offset: 0x001C147C
		// Variables:
	// 		int i; // $s1
	// 		char version_info[32]; // stack offset -88
	// 		int numBtnsToDraw; // stack offset -56
	/* end block 1 */
	// End offset: 0x001C18B4
	// End Line: 1760

	/* begin block 2 */
		// Start line: 3516
	/* end block 2 */
	// End Line: 3517

	/* begin block 3 */
		// Start line: 3525
	/* end block 3 */
	// End Line: 3526

void DrawScreen(PSXSCREEN *pScr)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	DB *pDVar2;
	uint *puVar3;
	uint uVar4;
	int local_68;
	char *string;
	uint *puVar5;
	PSXSCREEN *pPVar6;
	int iVar7;
	PSXBUTTON *pPVar8;
	char *pcVar9;
	char *pcVar10;
	char *string_00;
	char *pcVar11;
	int local_64;
	int local_60;
	char acStack88[32];
	uint local_38;
	int local_34;
	char *local_30;

	pDVar2 = current;
	puVar5 = &DAT_FRNT__001cbcc0;
	iVar7 = 5;
	do {
		*puVar5 = *puVar5 & 0xff000000 | *(uint *)pDVar2->ot[0xb] & 0xffffff;
		iVar7 = iVar7 + -1;
		puVar3 = (uint *)pDVar2->ot[0xb];
		uVar4 = (uint)puVar5 & 0xffffff;
		puVar5 = puVar5 + 10;
		*puVar3 = *puVar3 & 0xff000000 | uVar4;
	} while (-1 < iVar7);
	if (pScr == (PSXSCREEN *)0x0) {
		EndFrame();
	}
	else {
		GetTimeStamp(acStack88);
		if ((DAT_FRNT__001c69a4 == 0) || (0x27 < gFurthestMission)) {
			local_38 = (uint)pScr->numButtons;
		}
		else {
			local_38 = (uint)pScr->numButtons - 1;
		}
		iVar7 = 0;
		if (0 < (int)local_38) {
			local_34 = 0;
			pcVar9 = pScr->buttons[0].Name;
			pPVar8 = pScr->buttons;
			pPVar6 = pScr;
			pcVar10 = pcVar9;
			string_00 = pcVar9;
			pcVar11 = pcVar9;
			local_30 = pcVar9;
			do {
				local_68 = *(int *)((int)&pScr->buttons[0].action + local_34) >> 8;
				if (local_68 != 5) {
					if (pPVar8 == pCurrButton) {
						string = pcVar10;
						if (local_68 == 3) {
						LAB_FRNT__001c16a8:
							sVar1 = pPVar6->buttons[0].x;
							local_68 = 0x20;
							local_64 = 0x20;
							local_60 = 0x20;
						}
						else {
							string = pcVar11;
							if ((((DAT_FRNT__001c6ab0 != 0) && ((iVar7 == 0 || (iVar7 == 5)))) ||
								((DAT_FRNT__001c6a88 != 0 && ((iVar7 == 0 || (iVar7 == 2)))))) ||
								((DAT_FRNT__001c6a80 != 0 && ((iVar7 == 0 || (iVar7 == 2)))))) {
							LAB_FRNT__001c174c:
								FEPrintString(string, (int)pPVar6->buttons[0].x * 2 + (int)pPVar6->buttons[0].w,
									(int)pPVar6->buttons[0].y, 4, 0x7c, 0x6c, 0x28);
								goto LAB_FRNT__001c17ac;
							}
							sVar1 = pPVar6->buttons[0].x;
							local_68 = 0x80;
							local_64 = 0x80;
							local_60 = 0x80;
							string = pcVar9;
						}
						FEPrintString(string, (int)sVar1 * 2 + (int)pPVar6->buttons[0].w,
							(int)pPVar6->buttons[0].y, 4, local_68, local_64, local_60);
					}
					else {
						if (local_68 == 3) {
							string = pPVar8->Name;
							goto LAB_FRNT__001c16a8;
						}
						string = local_30;
						if ((((DAT_FRNT__001c6ab0 != 0) && ((iVar7 == 0 || (iVar7 == 5)))) ||
							((DAT_FRNT__001c6a88 != 0 && ((iVar7 == 0 || (iVar7 == 2)))))) ||
							((DAT_FRNT__001c6a80 != 0 && ((iVar7 == 0 || (iVar7 == 2))))))
							goto LAB_FRNT__001c174c;
						FEPrintString(string_00, (int)pPVar6->buttons[0].x * 2 + (int)pPVar6->buttons[0].w,
							(int)pPVar6->buttons[0].y, 4, 0x80, 0x80, 0x80);
					}
				}
			LAB_FRNT__001c17ac:
				pPVar6 = (PSXSCREEN *)(pPVar6->buttons[0].Name + 0x1c);
				string_00 = string_00 + 0x3c;
				pcVar9 = pcVar9 + 0x3c;
				pcVar11 = pcVar11 + 0x3c;
				pcVar10 = pcVar10 + 0x3c;
				pPVar8 = pPVar8 + 1;
				iVar7 = iVar7 + 1;
				local_34 = local_34 + 0x3c;
				local_30 = local_30 + 0x3c;
			} while (iVar7 < (int)local_38);
		}
		SetTextColour(-0x80, '\0', '\0');
		DisplayOnScreenText();
		pDVar2 = current;
		if (DAT_FRNT__001c6a90 != 0) {
			DAT_FRNT__001cc5c8 = DAT_FRNT__001cc5c8 & 0xff000000 | *(uint *)current->ot[2] & 0xffffff;
			*(uint *)current->ot[2] = *(uint *)current->ot[2] & 0xff000000 | 0x1cc5c8;
			DAT_FRNT__001cbdb8 = DAT_FRNT__001cbdb8 & 0xff000000 | *(uint *)pDVar2->ot[3] & 0xffffff;
			puVar5 = (uint *)pDVar2->ot[3];
			*puVar5 = *puVar5 & 0xff000000 | 0x1cbdb8;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayOnScreenText()
 // line 1769, offset 0x001c18e4
	/* begin block 1 */
		// Start line: 1771
		// Start offset: 0x001C18E4
		// Variables:
	// 		int i; // $s0
	// 		char text[32]; // stack offset -64

		/* begin block 1.1 */
			// Start line: 1795
			// Start offset: 0x001C19DC

			/* begin block 1.1.1 */
				// Start line: 1797
				// Start offset: 0x001C19E4
			/* end block 1.1.1 */
			// End offset: 0x001C19EC
			// End Line: 1798
		/* end block 1.1 */
		// End offset: 0x001C19EC
		// End Line: 1799

		/* begin block 1.2 */
			// Start line: 1807
			// Start offset: 0x001C1A4C
			// Variables:
		// 		int extraVal; // $t1
		/* end block 1.2 */
		// End offset: 0x001C1AAC
		// End Line: 1810
	/* end block 1 */
	// End offset: 0x001C1AD0
	// End Line: 1847

	/* begin block 2 */
		// Start line: 3804
	/* end block 2 */
	// End Line: 3805

	/* begin block 3 */
		// Start line: 3805
	/* end block 3 */
	// End Line: 3806

	/* begin block 4 */
		// Start line: 3809
	/* end block 4 */
	// End Line: 3810

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DisplayOnScreenText(void)
{
	UNIMPLEMENTED();
	/*
	uint transparent;
	char *__src;
	int iVar1;
	char **ppcVar2;

	sprintf(&DAT_FRNT__001cc1e0, &DAT_FRNT__001c0830);
	if (DAT_FRNT__001c6abc == 0) {
		transparent = (uint)Pads[0].type;
		if (Pads[0].type == '\0') {
			__src = s_Inserisci_un_controller_nell_ing_FRNT__001c0834;
			transparent = 1;
		}
		else {
			if (Pads[0].type != '\x01') {
				return;
			}
			__src = s_Errore_nell_ingresso_controller_1_FRNT__001c085c;
		}
		FEPrintStringSized(__src, 0x28, 400, 0xc00, transparent, 0x40, 0x40, 0x40);
	}
	else {
		if ((DAT_FRNT__001c699c == 0) && (iVar1 = 0, DAT_FRNT__001c6a88 == 0)) {
			if (0 < ScreenDepth) {
				ppcVar2 = ScreenNames12;
				do {
					if (0 < iVar1) {
						strcat(&DAT_FRNT__001cc1e0, (char *)&PTR_DAT_FRNT__001c0880);
					}
					__src = *ppcVar2;
					ppcVar2 = ppcVar2 + 1;
					strcat(&DAT_FRNT__001cc1e0, __src);
					iVar1 = iVar1 + 1;
				} while (iVar1 < ScreenDepth);
			}
			FEPrintStringSized(&DAT_FRNT__001cc1e0, 0x28, 400, 0xc00, 1, 0x40, 0x40, 0x40);
		}
		if (DAT_FRNT__001c6a80 != 0) {
			FEPrintStringSized((&PTR_s_Il_fiume_rosso_FRNT__001c0408_FRNT__001c6888)
				[DAT_FRNT__001c69a0 +
				*(int *)(&DAT_FRNT__001c69cc + DAT_FRNT__001c6a70 * 4)], 100, 0xe2, 0xc00, 1,
				0x60, 0x60, 0x60);
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupExtraPoly(char *fileName /*$s5*/, int offset /*$s1*/, int offset2 /*$s0*/)
 // line 1855, offset 0x001c1ad0
	/* begin block 1 */
		// Start line: 1856
		// Start offset: 0x001C1AD0
		// Variables:
	// 		int i; // $s0
	// 		int tpage; // $v1
	// 		struct RECT rect; // stack offset -40
	/* end block 1 */
	// End offset: 0x001C1CF4
	// End Line: 1916

	/* begin block 2 */
		// Start line: 3983
	/* end block 2 */
	// End Line: 3984

	/* begin block 3 */
		// Start line: 3992
	/* end block 3 */
	// End Line: 3993

	/* begin block 4 */
		// Start line: 3996
	/* end block 4 */
	// End Line: 3997

void SetupExtraPoly(char *fileName, int offset, int offset2)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	undefined **ppuVar3;
	undefined4 local_28;
	undefined4 local_24;

	local_28 = DAT_FRNT__001c0884;
	local_24 = DAT_FRNT__001c0888;
	FEDrawCDicon();
	Loadfile(fileName, &DAT_0013f400 + offset2);
	DAT_FRNT__001cc5c8._3_1_ = 4;
	DAT_FRNT__001cc5cf = 100;
	DAT_FRNT__001cc5d0 = 100;
	DAT_FRNT__001cc5d8 = 0xff;
	DAT_FRNT__001cc5d2 = 0xe2;
	DAT_FRNT__001cc5cc = 0x80;
	DAT_FRNT__001cc5cd = 0x80;
	DAT_FRNT__001cc5ce = 0x80;
	DAT_FRNT__001cc5d4 = 0;
	DAT_FRNT__001cc5d5 = 0;
	uRam001cc5da = 0xdb;
	DAT_FRNT__001cc5d6 = 0x403c;
	local_28 = 0x1000380;
	local_24 = 0xdb0040;
	LoadImage(&local_28, &DAT_0013f400 + offset2 + offset * 0x8000);
	DrawSync(0);
	VSync(0);
	DAT_FRNT__001cbdb8._3_1_ = 7;
	DAT_FRNT__001cbdbf = 0x24;
	DAT_FRNT__001cbdc0 = 0xffff;
	DAT_FRNT__001cbdc2 = 0xffff;
	DAT_FRNT__001cbdc8 = 0xffff;
	DAT_FRNT__001cbdca = 0xffff;
	DAT_FRNT__001cbdd0 = 0xffff;
	DAT_FRNT__001cbdd2 = 0xffff;
	DAT_FRNT__001cbdce = 0x1e;
	DAT_FRNT__001c6a90 = 1;
	iVar1 = strcmp(fileName, s_DATA_CITY_RAW_FRNT__001c088c);
	if (iVar1 == 0) {
		DAT_FRNT__001c6a78 = 1;
		DAT_FRNT__001c6a79 = 0xff;
	}
	iVar1 = 0;
	ppuVar3 = &PTR_s_DATA_CARS_CCARS_RAW_FRNT__001c078c_FRNT__001c6a10;
	do {
		iVar2 = strcmp(fileName, *ppuVar3);
		if (iVar2 == 0) {
			DAT_FRNT__001c6a78 = 0xff;
			DAT_FRNT__001c6a79 = (undefined)iVar1;
			DAT_FRNT__001c6a7a = 0xff;
		}
		iVar1 = iVar1 + 1;
		ppuVar3 = ppuVar3 + 1;
	} while (iVar1 < 4);
	iVar1 = 0;
	ppuVar3 = &PTR_s_DATA_CUTS_CCUTS_RAW_FRNT__001c073c_FRNT__001c69a8;
	do {
		iVar2 = strcmp(fileName, *ppuVar3);
		if (iVar2 == 0) {
			DAT_FRNT__001c6a79 = 0xff;
			DAT_FRNT__001c6a7a = (undefined)iVar1;
		}
		iVar1 = iVar1 + 1;
		ppuVar3 = ppuVar3 + 1;
	} while (iVar1 < 4);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReInitScreens()
 // line 1941, offset 0x001c1cf4
	/* begin block 1 */
		// Start line: 4221
	/* end block 1 */
	// End Line: 4222

	/* begin block 2 */
		// Start line: 4247
	/* end block 2 */
	// End Line: 4248

	/* begin block 3 */
		// Start line: 4248
	/* end block 3 */
	// End Line: 4249

/* WARNING: Unknown calling convention yet parameter storage is locked */

void ReInitScreens(void)
{
	UNIMPLEMENTED();
	/*
	if (DAT_FRNT__001c6ac8 == 0) {
		FEInitCdIcon();
	}
	if (bReturnToMain == 0) {
		bReturnToMain = 1;
	}
	else {
		ScreenDepth = 0;
		NumPlayers = 1;
		gWantNight = 0;
		gNight = 0;
		gTimeOfDay = 1;
		gSubGameNumber = 0;
		feVariableSave[3] = 0xffffffff;
		feVariableSave[2] = 0xffffffff;
		feVariableSave[1] = 0xffffffff;
		feVariableSave[0] = 0xffffffff;
		if (DAT_FRNT__001c6ac4 == 0) {
			DAT_FRNT__001c6a90 = 0;
			LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
		}
	}
	pCurrScreen = pScreenStack10[ScreenDepth];
	DAT_FRNT__001cbcb8 = pButtonStack10[ScreenDepth];
	SetupScreenSprts(pCurrScreen);
	SetupBackgroundPolys();
	DAT_FRNT__001cbdb0 = VSync(0xffffffff);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ NewSelection(short dir /*$s3*/)
 // line 1991, offset 0x001c1e18
	/* begin block 1 */
		// Start line: 1992
		// Start offset: 0x001C1E18
		// Variables:
	// 		struct RECT rect; // stack offset -48
	// 		struct PSXBUTTON *pNewB; // $s2
	/* end block 1 */
	// End offset: 0x001C227C
	// End Line: 2085

	/* begin block 2 */
		// Start line: 4367
	/* end block 2 */
	// End Line: 4368

	/* begin block 3 */
		// Start line: 4369
	/* end block 3 */
	// End Line: 4370

void NewSelection(short dir)
{
	UNIMPLEMENTED();
	/*
	DB *pDVar1;
	PSXBUTTON *pPVar2;
	PSXBUTTON *pPVar3;
	uint uVar4;
	short local_30;
	short local_2e;
	undefined2 local_2c;
	undefined2 local_2a;

	pPVar2 = pCurrButton;
	uVar4 = SEXT24(dir);
	if (pCurrScreen->numButtons == '\0') {
		return;
	}
	if (uVar4 != 0) {
		SetDrawMove(&DAT_FRNT__001cc550, &DAT_FRNT__001c6a98, (int)pCurrButton->s_x, (int)pCurrButton->s_y)
			;
		DAT_FRNT__001cc550 = DAT_FRNT__001cc550 & 0xff000000 | *(uint *)current->ot[9] & 0xffffff;
		*(uint *)current->ot[9] = *(uint *)current->ot[9] & 0xff000000 | 0x1cc550;
	}
	pPVar3 = pPVar2;
	if ((uVar4 & 0x1000) == 0) {
		if ((uVar4 & 0x4000) == 0) {
			if ((uVar4 & 0x8000) == 0) {
				pPVar3 = pCurrButton;
				if (((uVar4 & 0x2000) == 0) || (pPVar3 = pPVar2, pCurrButton->r == '\0'))
					goto LAB_FRNT__001c1ff4;
				FESound(3);
				uVar4 = (uint)pCurrButton->r;
			}
			else {
				if (pCurrButton->l == '\0') goto LAB_FRNT__001c1ff4;
				FESound(3);
				uVar4 = (uint)pCurrButton->l;
			}
		}
		else {
			if (pCurrButton->d == '\0') goto LAB_FRNT__001c1ff4;
			FESound(3);
			uVar4 = (uint)pCurrButton->d;
		}
	}
	else {
		if (pCurrButton->u == '\0') goto LAB_FRNT__001c1ff4;
		FESound(3);
		uVar4 = (uint)pCurrButton->u;
	}
	pPVar3 = (PSXBUTTON *)&pCurrScreen[-1].buttons[uVar4 + 7].w;
LAB_FRNT__001c1ff4:
	local_30 = pPVar3->s_x;
	local_2e = pPVar3->s_y;
	local_2c = 0xff;
	local_2a = 0x24;
	SetDrawMove(&DAT_FRNT__001cc570, &local_30, (int)DAT_FRNT__001c6a98, (int)DAT_FRNT__001c6a9a);
	pDVar1 = current;
	DAT_FRNT__001cc570 = DAT_FRNT__001cc570 & 0xff000000 | *(uint *)current->ot[8] & 0xffffff;
	*(uint *)current->ot[8] = *(uint *)current->ot[8] & 0xff000000 | 0x1cc570;
	DAT_FRNT__001cc598 = pPVar3->s_x;
	DAT_FRNT__001cc59a = pPVar3->s_y;
	DAT_FRNT__001cc590 = DAT_FRNT__001cc590 & 0xff000000 | *(uint *)pDVar1->ot[6] & 0xffffff;
	pCurrButton = pPVar3;
	*(uint *)pDVar1->ot[6] = *(uint *)pDVar1->ot[6] & 0xff000000 | 0x1cc590;
	DAT_FRNT__001cc5a8 = DAT_FRNT__001cc5a8 & 0xff000000 | *(uint *)pDVar1->ot[7] & 0xffffff;
	*(uint *)pDVar1->ot[7] = *(uint *)pDVar1->ot[7] & 0xff000000 | 0x1cc5a8;
	if (pPVar3->action >> 8 == 3) {
		FEPrintString(pPVar3->Name, (int)pPVar3->x * 2 + (int)pPVar3->w, (int)pPVar3->y, 4, 0x20, 0x20, 0x20);
	}
	else {
		if ((((DAT_FRNT__001c6a88 == 0) ||
			((pPVar3 != pCurrScreen->buttons && (pPVar3 != pCurrScreen->buttons + 2)))) &&
			((DAT_FRNT__001c6ab0 == 0 ||
			((pPVar3 != pCurrScreen->buttons && (pPVar3 != pCurrScreen->buttons + 5)))))) &&
				((DAT_FRNT__001c6a80 == 0 ||
			((pPVar3 != pCurrScreen->buttons && (pPVar3 != pCurrScreen->buttons + 2)))))) {
			FEPrintString(pCurrButton->Name, (int)pCurrButton->x * 2 + (int)pCurrButton->w,
				(int)pCurrButton->y, 4, 0x80, 0x80, 0x80);
		}
		else {
			FEPrintString(pCurrButton->Name, (int)pCurrButton->x * 2 + (int)pCurrButton->w,
				(int)pCurrButton->y, 4, 0x7c, 0x6c, 0x28);
		}
	}
	EndFrame();
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ HandleKeyPress()
 // line 2093, offset 0x001c22a8
	/* begin block 1 */
		// Start line: 2095
		// Start offset: 0x001C22A8

		/* begin block 1.1 */
			// Start line: 2112
			// Start offset: 0x001C2340
			// Variables:
		// 		int action; // $s0

			/* begin block 1.1.1 */
				// Start line: 2141
				// Start offset: 0x001C244C
			/* end block 1.1.1 */
			// End offset: 0x001C2510
			// End Line: 2166
		/* end block 1.1 */
		// End offset: 0x001C2564
		// End Line: 2186
	/* end block 1 */
	// End offset: 0x001C2668
	// End Line: 2232

	/* begin block 2 */
		// Start line: 4610
	/* end block 2 */
	// End Line: 4611

	/* begin block 3 */
		// Start line: 4611
	/* end block 3 */
	// End Line: 4612

	/* begin block 4 */
		// Start line: 4613
	/* end block 4 */
	// End Line: 4614

/* WARNING: Unknown calling convention yet parameter storage is locked */

int HandleKeyPress(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	PSXBUTTON *pPVar2;
	int iVar3;
	PSXBUTTON **ppPVar4;

	if ((pCurrScreen == (PSXSCREEN *)0x0) || (pCurrButton == (PSXBUTTON *)0x0)) {
		iVar3 = 0;
	}
	else {
		if ((pCurrScreen->userFunctionNum != '\0') &&
			(iVar3 = (*(code *)(&PTR_CentreScreen_FRNT__001c6a20)
				[(uint)(byte)pCurrScreen->userFunctionNum - 1])(0), iVar3 != 0)) {
			uRam001cc5dc = 0;
		}
		if ((uRam001cc5dc & 0x40) == 0) {
			if ((uRam001cc5dc & 0x10) == 0) {
				if ((((uRam001cc5dc & 0x5000) == 0) && ((uRam001cc5dc & 0x8000) == 0)) &&
					((uRam001cc5dc & 0x2000) == 0)) {
					return 1;
				}
				NewSelection(uRam001cc5dc);
			}
			else {
				if (0 < ScreenDepth) {
					if (DAT_FRNT__001c6aac == 0) {
						FESound(0);
					}
					else {
						DAT_FRNT__001c6aac = 0;
					}
					ScreenDepth = ScreenDepth + -1;
					if (ScreenDepth == 0) {
						gWantNight = 0;
						gSubGameNumber = 0;
						NumPlayers = 1;
					}
					DAT_FRNT__001c6d48 = pScreenStack10[ScreenDepth];
					DAT_FRNT__001cbcb8 = pButtonStack10[ScreenDepth];
				}
			}
		}
		else {
			iVar3 = pCurrButton->action >> 8;
			if (iVar3 != 3) {
				FESound(2);
				if (pCurrButton->var != -1) {
					SetVariable(pCurrButton->var);
				}
				iVar1 = ScreenDepth;
				if (iVar3 == 2) {
					if (((NumPlayers == 2) && (DAT_FRNT__001c6a88 != 0)) && (DAT_FRNT__001c6a84 == 2)) {
						(*(code *)(&PTR_CentreScreen_FRNT__001c6a20)
							[(uint)(byte)pCurrScreen->userFunctionNum - 1])(1);
						DAT_FRNT__001c6aa0 = 1;
					}
					else {
						ppPVar4 = pButtonStack10 + ScreenDepth;
						pScreenStack10[ScreenDepth] = pCurrScreen;
						pPVar2 = pCurrButton;
						*ppPVar4 = pCurrButton;
						ScreenNames12[iVar1] = pPVar2->Name;
						GameStart();
					}
				}
				else {
					if (iVar3 < 3) {
						if (iVar3 == 1) {
							pScreenStack10[ScreenDepth] = pCurrScreen;
							pPVar2 = pCurrButton;
							pButtonStack10[ScreenDepth] = pCurrButton;
							ScreenNames12[ScreenDepth] = pPVar2->Name;
							iVar3 = 10;
							if (ScreenDepth < 0xb) {
								iVar3 = ScreenDepth + 1;
							}
							DAT_FRNT__001c6d48 =
								(PSXSCREEN *)(&DAT_FRNT__001c6d50 + (uint)*(byte *)&pPVar2->action * 0x1e4);
							ScreenDepth = iVar3;
						}
					}
					else {
						if ((iVar3 == 4) && (iVar3 = ScreenDepth + -1, 0 < ScreenDepth)) {
							if (iVar3 == 0) {
								NumPlayers = 1;
							}
							DAT_FRNT__001c6d48 = pScreenStack10[iVar3];
							DAT_FRNT__001cbcb8 = pButtonStack10[iVar3];
							ScreenDepth = iVar3;
						}
					}
				}
			}
		}
		DAT_FRNT__001cbdb0 = VSync(0xffffffff);
		iVar3 = 1;
	}
	return iVar3;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PadChecks()
 // line 2300, offset 0x001c2668
	/* begin block 1 */
		// Start line: 2302
		// Start offset: 0x001C2668
		// Variables:
	// 		int i; // $a2
	// 		int oldnum; // $s2
	/* end block 1 */
	// End offset: 0x001C296C
	// End Line: 2417

	/* begin block 2 */
		// Start line: 4977
	/* end block 2 */
	// End Line: 4978

	/* begin block 3 */
		// Start line: 5046
	/* end block 3 */
	// End Line: 5047

	/* begin block 4 */
		// Start line: 5047
	/* end block 4 */
	// End Line: 5048

	/* begin block 5 */
		// Start line: 5048
	/* end block 5 */
	// End Line: 5049

/* WARNING: Unknown calling convention yet parameter storage is locked */

void PadChecks(void)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;
	undefined4 *puVar2;
	int iVar3;
	byte *pbVar4;

	uVar1 = DAT_FRNT__001c6ab8;
	ReadControllers();
	puVar2 = &DAT_FRNT__001c6abc;
	pbVar4 = &Pads[0].type;
	iVar3 = 1;
	DAT_FRNT__001c6ab8 = 0;
	uRam001cc5dc = Pads[0].mapnew;
	do {
		if (*pbVar4 < 2) {
			*puVar2 = 0;
		}
		else {
			*puVar2 = 1;
			DAT_FRNT__001c6ab8 = DAT_FRNT__001c6ab8 + 1;
		}
		puVar2 = puVar2 + 1;
		iVar3 = iVar3 + -1;
		pbVar4 = pbVar4 + 0x48;
	} while (-1 < iVar3);
	if ((uVar1 != DAT_FRNT__001c6ab8) &&
		(((uVar1 == 2 || (DAT_FRNT__001c6ab8 == 2)) && (ScreenDepth == 0)))) {
		DAT_FRNT__001c6aa0 = 1;
		MainScreen(1);
	}
	iVar3 = DAT_FRNT__001c6ab4;
	if (((Pads[0].dualshock == '\0') || (DAT_FRNT__001c6abc == 0)) &&
		((Pads[1].dualshock == '\0' || (DAT_FRNT__001c6ac0 == 0)))) {
		if ((DAT_FRNT__001c6ab4 == 1) &&
			(DAT_FRNT__001c6ab4 = 0, pCurrScreen->userFunctionNum == '\x12')) {
			DAT_FRNT__001c6aa0 = iVar3;
			GamePlayScreen(1);
		}
	}
	else {
		if ((DAT_FRNT__001c6ab4 == 0) &&
			(DAT_FRNT__001c6ab4 = 1, pCurrScreen->userFunctionNum == '\x12')) {
			DAT_FRNT__001c6aa0 = 1;
			GamePlayScreen(1);
		}
	}
	if ((uVar1 != DAT_FRNT__001c6ab8) &&
		((((NumPlayers == 2 && (DAT_FRNT__001c6ab8 != (uint)NumPlayers)) || (DAT_FRNT__001c6ab8 == 0))
			|| (DAT_FRNT__001c6abc == 0)))) {
		bReturnToMain = 1;
		DAT_FRNT__001c6aa0 = 1;
		uRam001cc5dc = 0x10;
		if (pCurrScreen->userFunctionNum != '\0') {
			(*(code *)(&PTR_CentreScreen_FRNT__001c6a20)[(uint)(byte)pCurrScreen->userFunctionNum - 1])(0)
				;
		}
		uRam001cc5dc = 0;
		if (ScreenDepth != 0) {
			ReInitScreens();
		}
	}
	if (((DAT_FRNT__001c6aa0 == 0) && (DAT_FRNT__001c6ab8 != uVar1)) &&
		((gInFrontend != 0 &&
		((pCurrScreen != (PSXSCREEN *)0x0 && (pCurrScreen->userFunctionNum != '\0')))))) {
		(*(code *)(&PTR_CentreScreen_FRNT__001c6a20)[(uint)(byte)pCurrScreen->userFunctionNum - 1])(1);
		DAT_FRNT__001c6aa0 = 1;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoFrontEnd()
 // line 2423, offset 0x001c296c
	/* begin block 1 */
		// Start line: 2425
		// Start offset: 0x001C296C
		// Variables:
	// 		static unsigned char result[8]; // offset 0x0
	/* end block 1 */
	// End offset: 0x001C2C2C
	// End Line: 2588

	/* begin block 2 */
		// Start line: 5332
	/* end block 2 */
	// End Line: 5333

	/* begin block 3 */
		// Start line: 5339
	/* end block 3 */
	// End Line: 5340

	/* begin block 4 */
		// Start line: 5340
	/* end block 4 */
	// End Line: 5341

	/* begin block 5 */
		// Start line: 5346
	/* end block 5 */
	// End Line: 5347

/* WARNING: Unknown calling convention yet parameter storage is locked */

int bRedrawFrontend = 0;
int gInFrontend = 0;
int idle_timer = 0;
int currPlayer = 0;
int fePad = 0;
int ScreenDepth = 0;


GAMETYPE GameType = GAME_MISSION;
int gCurrentMissionNumber = 0;
int gIdleReplay = 0;

PSXSCREEN* pCurrScreen = NULL;
PSXSCREEN* pNewScreen = NULL;
PSXBUTTON* pCurrButton = NULL;

PSXSCREEN PsxScreens[42];
struct PSXSCREEN (*pScreenStack[10]);
struct PSXBUTTON (*pButtonStack[10]);
char (*ScreenNames[12]);

void DoFrontEnd(void)
{
	UNIMPLEMENTED();
	int iVar1;

	ResetGraph(1);
	SetDispMask(0);
	PadChecks();
	bRedrawFrontend = 0;
	gInFrontend = 1;
	idle_timer = VSync(0xffffffff);
	LoadFrontendScreens();
	pCurrScreen = PsxScreens;
	pCurrButton = PsxScreens[0].buttons;
	SetupBackgroundPolys();
	SetupScreenSprts(pCurrScreen);
	SetDispMask(0);
	ResetGraph(0);
	SetFEDrawMode();
	SetVideoMode(1);
	EnableDisplay();
	DrawScreen(pCurrScreen);
	EndFrame();
	NewSelection(0);
	EndFrame();
	EndFrame();
	EndFrame();
	EndFrame();
	EndFrame();
	EndFrame();
	SetDispMask(1);
	FEInitCdIcon();
	do {
		PadChecks();
		if (currPlayer == 2) {
			if (Pads[1].type < 2) {
				if ((fePad & 0x10U) == 0) {
					fePad = 0;
				}
				else {
					fePad = 0x10;
				}
			}
			else {
				fePad = Pads[1].mapnew;
			}
		}
		iVar1 = HandleKeyPress();
		if ((iVar1 != 0) && (pNewScreen != NULL)) {
			SetupScreenSprts(pNewScreen);
			DrawScreen(pCurrScreen);
			EndFrame();
			NewSelection(0);
		}
		if (bRedrawFrontend != 0) {
			DrawScreen(pCurrScreen);
			EndFrame();
			NewSelection(0);
			bRedrawFrontend = 0;
		}
		iVar1 = VSync(0xffffffff);
		if (0x708 < iVar1 - idle_timer) {
			if (ScreenDepth == 0) {
				GameType = GAME_IDLEDEMO;
				gCurrentMissionNumber = gIdleReplay + 400;
				gIdleReplay = gIdleReplay + 1;
				if (gIdleReplay == 4) {
					gIdleReplay = 0;
				}
				pScreenStack[0] = pCurrScreen;
				pButtonStack[0] = pCurrButton;
				ScreenNames[0] = pCurrButton->Name;
				GameStart();
				pCurrScreen = pScreenStack[ScreenDepth];
				bRedrawFrontend = 1;
				ScreenDepth = 0;
			}
			idle_timer = VSync(0xffffffff);
		}
	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetFEDrawMode()
 // line 2630, offset 0x001c2c2c
	/* begin block 1 */
		// Start line: 2632
		// Start offset: 0x001C2C2C
		// Variables:
	// 		struct DRAW_MODE *dm; // $s3
	/* end block 1 */
	// End offset: 0x001C2D90
	// End Line: 2687

	/* begin block 2 */
		// Start line: 5839
	/* end block 2 */
	// End Line: 5840

	/* begin block 3 */
		// Start line: 5882
	/* end block 3 */
	// End Line: 5883

	/* begin block 4 */
		// Start line: 5883
	/* end block 4 */
	// End Line: 5884

	/* begin block 5 */
		// Start line: 5893
	/* end block 5 */
	// End Line: 5894

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SetFEDrawMode(void)
{
	UNIMPLEMENTED();
	/*
	SetVideoMode(1);
	SetDefDrawEnv(0xe08c8, (int)draw_mode_pal.x1, (int)draw_mode_pal.y1, 0x280, 0x200);
	SetDefDispEnv(0xe0924, (int)draw_mode_pal.x1, (int)draw_mode_pal.y1, 0x280, 0x200);
	SetDefDrawEnv(0xe0948, (int)draw_mode_pal.x1, (int)draw_mode_pal.y1, 0x280, 0x200);
	SetDefDispEnv(0xe09a4, (int)draw_mode_pal.x1, (int)draw_mode_pal.y1, 0x280, 0x200);
	MPBuff.draw.isbg = '\0';
	MPBuff.disp.isinter = '\x01';
	MPBuff.draw.dfe = '\x01';
	MPBuff.disp.screen.h = 0x100;
	MPBuff.primtab = &DAT_000fb400;
	MPBuff.primptr = &DAT_000fb400;
	MPBuff.ot = (ulong *)&DAT_000f3000;
	DB_000e0938.draw.isbg = '\0';
	DB_000e0938.disp.isinter = '\x01';
	DB_000e0938.draw.dfe = '\x01';
	DB_000e0938.disp.screen.h = 0x100;
	DB_000e0938.primtab = &DAT_00119400;
	DB_000e0938.primptr = &DAT_00119400;
	DB_000e0938.ot = (ulong *)&DAT_000f7200;
	last = &DB_000e0938;
	current = &MPBuff;
	MPBuff.disp.screen.x = draw_mode_pal.framex << 1;
	MPBuff.disp.screen.y = draw_mode_pal.framey;
	DB_000e0938.disp.screen.y = draw_mode_pal.framey;
	DB_000e0938.disp.screen.x = MPBuff.disp.screen.x;
	PutDispEnv(&MPBuff.disp);
	PutDrawEnv(&current->draw);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ EndFrame()
 // line 2695, offset 0x001c6378
	/* begin block 1 */
		// Start line: 2697
		// Start offset: 0x001C6378
		// Variables:
	// 		struct DB *db_hold; // $a1
	/* end block 1 */
	// End offset: 0x001C6404
	// End Line: 2716

	/* begin block 2 */
		// Start line: 8781
	/* end block 2 */
	// End Line: 8782

	/* begin block 3 */
		// Start line: 5390
	/* end block 3 */
	// End Line: 5391

	/* begin block 4 */
		// Start line: 8782
	/* end block 4 */
	// End Line: 8783

	/* begin block 5 */
		// Start line: 8784
	/* end block 5 */
	// End Line: 8785

/* WARNING: Unknown calling convention yet parameter storage is locked */

void EndFrame(void)
{
	UNIMPLEMENTED();
	/*
	char **ppcVar1;
	DB *pDVar2;
	DB *pDVar3;

	DrawSync(0);
	VSync(0);
	PutDispEnv(&current->disp);
	PutDrawEnv(&current->draw);
	pDVar3 = last;
	pDVar2 = current;
	ppcVar1 = &last->primtab;
	current = last;
	last = pDVar2;
	pDVar3->primptr = *ppcVar1;
	DrawOTag(pDVar2->ot + 0x10);
	ClearOTagR(current->ot, 0x10);
	VSync(0);
	return;*/
}



// autogenerated function stub: 
// void carSelectPlayerText() /* carSelectPlayerText method signature is not contained in the debug symbol data. This is likely either a library function or the game was compiled without debug symbols. Please refer to the TDR documentation for additional guidance. */
void carSelectPlayerText()
{ // line 2737, offset 0x001c676c
	UNIMPLEMENTED();
//	return null;
}


// decompiled code
// original method signature: 
// int /*$ra*/ FEPrintString(char *string /*$t1*/, int x /*$t2*/, int y /*$s4*/, int justification /*$a3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/)
 // line 2745, offset 0x001c2d90
	/* begin block 1 */
		// Start line: 2746
		// Start offset: 0x001C2D90
		// Variables:
	// 		struct FE_CHARDATA *pFontInfo; // $a0
	// 		struct SPRT *font; // $t0
	// 		unsigned char let; // $a0
	// 		int counter; // $t4

		/* begin block 1.1 */
			// Start line: 2746
			// Start offset: 0x001C2DEC
			// Variables:
		// 		char *pString; // $a1

			/* begin block 1.1.1 */
				// Start line: 2746
				// Start offset: 0x001C2DEC
				// Variables:
			// 		char let; // $v1
			// 		int w; // $a2
			/* end block 1.1.1 */
			// End offset: 0x001C2E38
			// End Line: 2746
		/* end block 1.1 */
		// End offset: 0x001C2E38
		// End Line: 2746

		/* begin block 1.2 */
			// Start line: 2792
			// Start offset: 0x001C2F28
			// Variables:
		// 		int tpage; // $v1
		/* end block 1.2 */
		// End offset: 0x001C2F28
		// End Line: 2792
	/* end block 1 */
	// End offset: 0x001C2FD8
	// End Line: 2809

	/* begin block 2 */
		// Start line: 6177
	/* end block 2 */
	// End Line: 6178

	/* begin block 3 */
		// Start line: 6236
	/* end block 3 */
	// End Line: 6237

int FEPrintString(char *string, int x, int y, int justification, int r, int g, int b)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	byte bVar2;
	char cVar3;
	DB *pDVar4;
	int iVar5;
	uint uVar6;
	uint uVar7;
	int iVar8;
	ulong *puVar9;
	byte *pbVar10;
	uint *puVar11;
	byte *pbVar12;
	int iVar13;

	iVar13 = 0;
	iVar5 = -1;
	if (current != (DB *)0x0) {
		puVar11 = (uint *)current->primptr;
		bVar1 = *string;
		uVar7 = (uint)bVar1;
		pbVar12 = (byte *)(string + 1);
		iVar5 = x;
		if ((justification & 4U) != 0) {
			iVar5 = 0;
			uVar6 = uVar7;
			pbVar10 = pbVar12;
			bVar2 = bVar1;
			while (bVar2 != 0) {
				if (uVar6 == 0x20) {
					iVar5 = iVar5 + 4;
				}
				else {
					iVar5 = iVar5 + (uint)(byte)(&DAT_FRNT__001cbdde)[uVar6 * 4];
				}
				bVar2 = *pbVar10;
				uVar6 = (uint)bVar2;
				pbVar10 = pbVar10 + 1;
			}
			iVar5 = x - iVar5;
		}
		if (bVar1 != 0) {
			do {
				iVar8 = uVar7 * 4;
				if (uVar7 == 0x20) {
					iVar5 = iVar5 + 4;
				}
				else {
					bVar1 = (&DAT_FRNT__001cbdde)[iVar8];
					*(char *)((int)puVar11 + 3) = '\x04';
					*(char *)((int)puVar11 + 7) = 'f';
					*(char *)(puVar11 + 1) = (char)r;
					*(char *)((int)puVar11 + 5) = (char)g;
					*(char *)((int)puVar11 + 6) = (char)b;
					*(short *)(puVar11 + 2) = (short)iVar5;
					*(undefined2 *)((int)puVar11 + 10) = (short)y;
					*(undefined *)(puVar11 + 3) = (&DAT_FRNT__001cbddc)[iVar8];
					cVar3 = (&DAT_FRNT__001cbddd)[iVar8];
					*(ushort *)(puVar11 + 4) = (ushort)bVar1;
					*(char *)((int)puVar11 + 0xd) = cVar3;
					pDVar4 = current;
					bVar2 = (&DAT_FRNT__001cbddf)[iVar8];
					iVar5 = iVar5 + (uint)bVar1;
					*(undefined2 *)((int)puVar11 + 0xe) = 0x407c;
					*(ushort *)((int)puVar11 + 0x12) = (ushort)bVar2;
					*puVar11 = *puVar11 & 0xff000000 | pDVar4->ot[1] & 0xffffff;
					puVar9 = pDVar4->ot;
					uVar7 = (uint)puVar11 & 0xffffff;
					puVar11 = puVar11 + 5;
					puVar9[1] = puVar9[1] & 0xff000000 | uVar7;
				}
				iVar13 = iVar13 + 1;
				bVar1 = *pbVar12;
				uVar7 = (uint)bVar1;
				pbVar12 = pbVar12 + 1;
			} while ((bVar1 != 0) && (iVar13 < 0x20));
		}
		*(uint **)&current->primptr = puVar11;
		*(char *)((int)puVar11 + 3) = '\a';
		*(char *)((int)puVar11 + 7) = '&';
		pDVar4 = current;
		*(undefined2 *)(puVar11 + 2) = 0xffff;
		*(undefined2 *)((int)puVar11 + 10) = 0xffff;
		*(undefined2 *)(puVar11 + 4) = 0xffff;
		*(undefined2 *)((int)puVar11 + 0x12) = 0xffff;
		*(undefined2 *)(puVar11 + 6) = 0xffff;
		*(undefined2 *)((int)puVar11 + 0x1a) = 0xffff;
		*(undefined2 *)((int)puVar11 + 0x16) = 0x1a;
		*puVar11 = *puVar11 & 0xff000000 | pDVar4->ot[1] & 0xffffff;
		pDVar4->ot[1] = pDVar4->ot[1] & 0xff000000 | (uint)puVar11 & 0xffffff;
		pDVar4->primptr = pDVar4->primptr + 0x20;
	}
	return iVar5;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ FEPrintStringSized(char *string /*$t2*/, int x /*$t1*/, int y /*$t7*/, int scale /*$a3*/, int transparent /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
 // line 2817, offset 0x001c2fd8
	/* begin block 1 */
		// Start line: 2818
		// Start offset: 0x001C2FD8
		// Variables:
	// 		struct POLY_FT4 *font; // $t0
	// 		struct FE_CHARDATA *pFontInfo; // $a2
	// 		char let; // $v1
	// 		int tpage; // $v0
	// 		int w; // $t3
	// 		int h; // $t4
	/* end block 1 */
	// End offset: 0x001C31FC
	// End Line: 2880

	/* begin block 2 */
		// Start line: 6457
	/* end block 2 */
	// End Line: 6458

	/* begin block 3 */
		// Start line: 6466
	/* end block 3 */
	// End Line: 6467

int FEPrintStringSized(char *string, int x, int y, int scale, int transparent, int r, int g, int b)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	byte bVar2;
	char cVar3;
	short sVar4;
	DB *pDVar5;
	char cVar6;
	int iVar7;
	int iVar8;
	short sVar9;
	uint uVar10;
	char *pcVar11;
	uint *puVar12;

	iVar7 = -1;
	if (current != (DB *)0x0) {
		bVar1 = *string;
		puVar12 = (uint *)current->primptr;
		iVar7 = x;
		while (bVar1 != 0) {
			bVar1 = *string;
			string = (char *)((byte *)string + 1);
			iVar8 = iVar7;
			if (bVar1 != 10) {
				iVar8 = (uint)bVar1 * 4;
				if (bVar1 == 0x20) {
					iVar8 = iVar7 + 4;
				}
				else {
					pcVar11 = &DAT_FRNT__001cbddc + iVar8;
					bVar1 = (&DAT_FRNT__001cbdde)[iVar8];
					bVar2 = (&DAT_FRNT__001cbddf)[iVar8];
					*(char *)((int)puVar12 + 3) = '\t';
					*(char *)((int)puVar12 + 7) = ',';
					*(undefined2 *)((int)puVar12 + 0x16) = 0x1a;
					cVar6 = ',';
					if (transparent != 0) {
						cVar6 = '.';
					}
					*(char *)((int)puVar12 + 7) = cVar6;
					*(char *)(puVar12 + 1) = -0x80;
					*(char *)((int)puVar12 + 5) = -0x80;
					*(char *)((int)puVar12 + 6) = -0x80;
					*(char *)(puVar12 + 3) = *pcVar11;
					*(char *)((int)puVar12 + 0xd) = (&DAT_FRNT__001cbddd)[iVar8];
					*(char *)(puVar12 + 5) = (&DAT_FRNT__001cbdde)[iVar8] + *pcVar11 + -1;
					*(char *)((int)puVar12 + 0x15) = (&DAT_FRNT__001cbddd)[iVar8];
					*(char *)(puVar12 + 7) = *pcVar11;
					*(char *)((int)puVar12 + 0x1d) =
						(&DAT_FRNT__001cbddf)[iVar8] + (&DAT_FRNT__001cbddd)[iVar8] + -1;
					*(char *)(puVar12 + 9) = (&DAT_FRNT__001cbdde)[iVar8] + *pcVar11 + -1;
					cVar6 = (&DAT_FRNT__001cbddd)[iVar8];
					cVar3 = (&DAT_FRNT__001cbddf)[iVar8];
					iVar8 = iVar7 + ((int)((uint)bVar1 * scale) >> 0xc);
					sVar4 = (short)y;
					sVar9 = sVar4 + (short)((int)((uint)bVar2 * scale) >> 0xc);
					*(short *)(puVar12 + 2) = (short)iVar7;
					*(short *)((int)puVar12 + 10) = sVar4;
					*(short *)(puVar12 + 4) = (short)iVar8;
					*(short *)((int)puVar12 + 0x12) = sVar4;
					*(short *)(puVar12 + 6) = (short)iVar7;
					*(short *)((int)puVar12 + 0x1a) = sVar9;
					*(short *)(puVar12 + 8) = (short)iVar8;
					*(short *)((int)puVar12 + 0x22) = sVar9;
					*(undefined2 *)((int)puVar12 + 0xe) = 0x407c;
					*(char *)(puVar12 + 1) = (char)r;
					*(char *)((int)puVar12 + 0x25) = cVar3 + cVar6 + -1;
					*(char *)((int)puVar12 + 5) = (char)g;
					*(char *)((int)puVar12 + 6) = (char)b;
					pDVar5 = current;
					*puVar12 = *puVar12 & 0xff000000 | current->ot[1] & 0xffffff;
					uVar10 = (uint)puVar12 & 0xffffff;
					puVar12 = puVar12 + 10;
					pDVar5->ot[1] = pDVar5->ot[1] & 0xff000000 | uVar10;
				}
			}
			bVar1 = *string;
			iVar7 = iVar8;
		}
		*(uint **)&current->primptr = puVar12;
	}
	return iVar7;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CentreScreen(int bSetup /*$a0*/)
 // line 2894, offset 0x001c31fc
	/* begin block 1 */
		// Start line: 6662
	/* end block 1 */
	// End Line: 6663

	/* begin block 2 */
		// Start line: 6677
	/* end block 2 */
	// End Line: 6678

	/* begin block 3 */
		// Start line: 6678
	/* end block 3 */
	// End Line: 6679

int CentreScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	DB *pDVar1;
	DB *pDVar2;
	short sVar3;

	pDVar2 = last;
	pDVar1 = current;
	if (bSetup != 0) {
		return 0;
	}
	if (DAT_FRNT__001c6a94 == 0) {
		DAT_FRNT__001c6a94 = 1;
	}
	if ((uRam001cc5dc & 0x2000) == 0) {
		if ((uRam001cc5dc & 0x8000) == 0) {
			if ((uRam001cc5dc & 0x1000) == 0) {
				if ((uRam001cc5dc & 0x4000) == 0) {
					if ((uRam001cc5dc & 0x40) != 0) {
						draw_mode_pal.framex = (current->disp).screen.x >> 1;
						draw_mode_pal.framey = (current->disp).screen.y;
						draw_mode_ntsc.framex = (current->disp).screen.x >> 1;
						draw_mode_ntsc.framey = (current->disp).screen.y;
						return 0;
					}
					if ((uRam001cc5dc & 0x10) == 0) {
						return 0;
					}
					(current->disp).screen.x = draw_mode_pal.framex << 1;
					(pDVar1->disp).screen.y = draw_mode_pal.framey;
					pDVar1 = last;
					(last->disp).screen.x = draw_mode_pal.framex << 1;
					(pDVar1->disp).screen.y = draw_mode_pal.framey;
					return 0;
				}
				if ((current->disp).screen.y < DAT_FRNT__001c6992) {
					(current->disp).screen.y = (current->disp).screen.y + 1;
					sVar3 = (pDVar2->disp).screen.y + 1;
					goto LAB_FRNT__001c3360;
				}
			}
			else {
				if (DAT_FRNT__001c698e < (current->disp).screen.y) {
					(current->disp).screen.y = (current->disp).screen.y + -1;
					sVar3 = (pDVar2->disp).screen.y + -1;
				LAB_FRNT__001c3360:
					(pDVar2->disp).screen.y = sVar3;
					FESound(3);
					return 0;
				}
			}
		}
		else {
			if (DAT_FRNT__001c698c < (current->disp).screen.x) {
				(current->disp).screen.x = (current->disp).screen.x + -1;
				sVar3 = (pDVar2->disp).screen.x + -1;
				goto LAB_FRNT__001c32c0;
			}
		}
	}
	else {
		if ((current->disp).screen.x < DAT_FRNT__001c6990) {
			(current->disp).screen.x = (current->disp).screen.x + 1;
			sVar3 = (pDVar2->disp).screen.x + 1;
		LAB_FRNT__001c32c0:
			(pDVar2->disp).screen.x = sVar3;
			FESound(3);
			return 0;
		}
	}
	FESound(1);
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CarSelectScreen(int bSetup /*$a0*/)
 // line 3029, offset 0x001c3430
	/* begin block 1 */
		// Start line: 3031
		// Start offset: 0x001C3430
		// Variables:
	// 		int i; // $a0
	// 		struct RECT rect; // stack offset -32

		/* begin block 1.1 */
			// Start line: 3145
			// Start offset: 0x001C373C
			// Variables:
		// 		int lastVal; // $a3

			/* begin block 1.1.1 */
				// Start line: 3030
				// Start offset: 0x001C37BC

				/* begin block 1.1.1.1 */
					// Start line: 3030
					// Start offset: 0x001C37BC
					// Variables:
				// 		struct RECT rect; // stack offset -24
				/* end block 1.1.1.1 */
				// End offset: 0x001C37BC
				// End Line: 3030
			/* end block 1.1.1 */
			// End offset: 0x001C37BC
			// End Line: 3030
		/* end block 1.1 */
		// End offset: 0x001C37BC
		// End Line: 3030

		/* begin block 1.2 */
			// Start line: 3164
			// Start offset: 0x001C37D0
			// Variables:
		// 		int lastVal; // $a3

			/* begin block 1.2.1 */
				// Start line: 3030
				// Start offset: 0x001C3858

				/* begin block 1.2.1.1 */
					// Start line: 3030
					// Start offset: 0x001C3858
					// Variables:
				// 		struct RECT rect; // stack offset -24
				/* end block 1.2.1.1 */
				// End offset: 0x001C3858
				// End Line: 3030
			/* end block 1.2.1 */
			// End offset: 0x001C3858
			// End Line: 3030
		/* end block 1.2 */
		// End offset: 0x001C3858
		// End Line: 3030
	/* end block 1 */
	// End offset: 0x001C3A60
	// End Line: 3212

	/* begin block 2 */
		// Start line: 6955
	/* end block 2 */
	// End Line: 6956

	/* begin block 3 */
		// Start line: 6956
	/* end block 3 */
	// End Line: 6957

	/* begin block 4 */
		// Start line: 6957
	/* end block 4 */
	// End Line: 6958

int CarSelectScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	DB *pDVar2;
	undefined4 *puVar3;
	int iVar4;
	int iVar5;
	uint *puVar6;
	undefined4 local_20;
	undefined4 local_1c;
	undefined4 local_18;
	undefined4 local_14;

	iVar5 = DAT_FRNT__001c6a0c;
	local_20 = DAT_FRNT__001c0884;
	local_1c = DAT_FRNT__001c0888;
	if (bSetup == 0) {
		if ((uRam001cc5dc & 0x10) == 0) {
			if ((uRam001cc5dc & 0x40) != 0) {
				if (DAT_FRNT__001c6a8c == 0) {
					iVar4 = 9;
					if (DAT_FRNT__001c6a0c != 0) {
						iVar4 = DAT_FRNT__001c6a0c + -1;
					}
					while ((DAT_FRNT__001c6a0c = iVar4,
						*(int *)(&DAT_FRNT__001c6af4 + DAT_FRNT__001c6a0c * 4 + GameLevel * 0x28) == 0 &&
						(DAT_FRNT__001c6a0c != iVar5))) {
						iVar4 = DAT_FRNT__001c6a0c + -1;
						if (DAT_FRNT__001c6a0c + -1 == -1) {
							DAT_FRNT__001c6a0c = 9;
							iVar4 = DAT_FRNT__001c6a0c;
						}
					}
				}
				else {
					if (DAT_FRNT__001c6a8c != 2) {
						if (DAT_FRNT__001c6a84 == 1) {
							feVariableSave[0] = DAT_FRNT__001c6a0c;
							wantedCar[0] = ZEXT14((byte)(&DAT_FRNT__001c6acc)[DAT_FRNT__001c6a0c + GameLevel * 10]
							);
						}
						else {
							wantedCar[1] = ZEXT14((byte)(&DAT_FRNT__001c6acc)[DAT_FRNT__001c6a0c + GameLevel * 10]
							);
						}
						if (NumPlayers == 2) {
							DAT_FRNT__001c6a84 = DAT_FRNT__001c6a84 + 1;
							return 0;
						}
						return 0;
					}
					if (DAT_FRNT__001c6a0c == 9) {
						DAT_FRNT__001c6a0c = 0;
					}
					else {
						DAT_FRNT__001c6a0c = DAT_FRNT__001c6a0c + 1;
					}
					while ((*(int *)(&DAT_FRNT__001c6af4 + DAT_FRNT__001c6a0c * 4 + GameLevel * 0x28) == 0 &&
						(iVar4 = DAT_FRNT__001c6a0c + 1, DAT_FRNT__001c6a0c != iVar5))) {
						DAT_FRNT__001c6a0c = iVar4;
						if (iVar4 == 10) {
							DAT_FRNT__001c6a0c = 0;
						}
					}
				}
				local_18 = DAT_FRNT__001c0884;
				local_14 = DAT_FRNT__001c0888;
				LoadImage(&local_18, &DAT_0013f400 + DAT_FRNT__001c6a0c * 0x8000);
				DrawSync(0);
				DisplayOnScreenText();
				pDVar2 = current;
				DAT_FRNT__001cc5c8 = DAT_FRNT__001cc5c8 & 0xff000000 | *(uint *)current->ot[2] & 0xffffff;
				*(uint *)current->ot[2] = *(uint *)current->ot[2] & 0xff000000 | 0x1cc5c8;
				DAT_FRNT__001cbdb8 = DAT_FRNT__001cbdb8 & 0xff000000 | *(uint *)pDVar2->ot[3] & 0xffffff;
				puVar6 = (uint *)pDVar2->ot[3];
				*puVar6 = *puVar6 & 0xff000000 | 0x1cbdb8;
				EndFrame();
				return 0;
			}
			if ((uRam001cc5dc & 0x1000) == 0) {
				if ((uRam001cc5dc & 0x4000) == 0) {
					return 0;
				}
				bVar1 = pCurrButton->d;
			}
			else {
				bVar1 = pCurrButton->u;
			}
			DAT_FRNT__001c6a8c = (uint)bVar1 - 1;
		}
		else {
			FESound(0);
			DAT_FRNT__001c6aac = 1;
			LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
			DAT_FRNT__001c6a84 = 1;
			DAT_FRNT__001c6a90 = 0;
			DAT_FRNT__001c6a88 = 0;
		}
		return 0;
	}
	DAT_FRNT__001c6a88 = 1;
	if (NumPlayers == 1) {
		DAT_FRNT__001c6b18 = (uint)((byte)AvailableCheats >> 4) & 1;
		DAT_FRNT__001c6b40 = (uint)((byte)AvailableCheats >> 6) & 1;
		DAT_FRNT__001c6b68 = (uint)AvailableCheats._1_1_ & 1;
		DAT_FRNT__001c6b90 = (uint)(AvailableCheats._1_1_ >> 1) & 1;
	}
	if ((gFurthestMission == 0x28) && (NumPlayers == 1)) {
		iVar5 = 4;
		puVar3 = &DAT_FRNT__001c6b04;
		do {
			if (iVar5 != 8) {
				*puVar3 = 1;
			}
			puVar3[10] = 1;
			puVar3[0x14] = 1;
			puVar3[0x1e] = 1;
			iVar5 = iVar5 + 1;
			puVar3 = puVar3 + 1;
		} while (iVar5 < 9);
	}
	else {
		puVar3 = &DAT_FRNT__001c6b04;
		iVar5 = 4;
		do {
			*puVar3 = 0;
			puVar3[10] = 0;
			puVar3[0x14] = 0;
			puVar3[0x1e] = 0;
			iVar5 = iVar5 + -1;
			puVar3 = puVar3 + 1;
		} while (-1 < iVar5);
	}
	if (DAT_FRNT__001c6a84 != 1) {
		if (NumPlayers == 2) {
			FEPrintStringSized(PTR_s_Giocatore_2_FRNT__001c0000_FRNT__001c6770, 400, 0x104, 0xc00, 0, 0x80, 0x80
				, 0x80);
			return 0;
		}
		return 0;
	}
	if (feVariableSave[0] == -1) {
		DAT_FRNT__001c6a0c = 0;
		if ((int)DAT_FRNT__001c6a79 == GameLevel) {
			DAT_FRNT__001c6a90 = DAT_FRNT__001c6a84;
			LoadImage(&local_20, &DAT_0013f400);
		}
		else {
			SetupExtraPoly((&PTR_s_DATA_CARS_CCARS_RAW_FRNT__001c078c_FRNT__001c6a10)[GameLevel], 0, 0);
			DAT_FRNT__001c6a7b = (undefined)GameLevel;
		}
	}
	else {
		DAT_FRNT__001c6a0c = feVariableSave[0];
		SetupExtraPoly((&PTR_s_DATA_CARS_CCARS_RAW_FRNT__001c078c_FRNT__001c6a10)[GameLevel],
			feVariableSave[0], 0);
	}
	LoadBackgroundFile(s_DATA_CARS_CARBACK_RAW_FRNT__001c089c);
	feVariableSave[0] = 0xffffffff;
	feVariableSave[1] = 0xffffffff;
	feVariableSave[2] = 0xffffffff;
	feVariableSave[3] = 0xffffffff;
	DAT_FRNT__001c6a7c = 0xff;
	DAT_FRNT__001c6a8c = 1;
	pCurrButton = pCurrScreen->buttons + 1;
	return 1;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CopDiffLevelScreen(int bSetup /*$a0*/)
 // line 3220, offset 0x001c6404
	/* begin block 1 */
		// Start line: 5153
	/* end block 1 */
	// End Line: 5154

	/* begin block 2 */
		// Start line: 10615
	/* end block 2 */
	// End Line: 10616

	/* begin block 3 */
		// Start line: 10616
	/* end block 3 */
	// End Line: 10617

/* WARNING: Control flow encountered bad instruction data */

int CopDiffLevelScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;

	/* WARNING: Bad instruction - Truncating control flow here */
	//halt_baddata();
}



// decompiled code
// original method signature: 
// int /*$ra*/ VibroOnOffScreen(int bSetup /*$a0*/)
 // line 3256, offset 0x001c3a60
	/* begin block 1 */
		// Start line: 7415
	/* end block 1 */
	// End Line: 7416

	/* begin block 2 */
		// Start line: 7460
	/* end block 2 */
	// End Line: 7461

	/* begin block 3 */
		// Start line: 7461
	/* end block 3 */
	// End Line: 7462

/* WARNING: Control flow encountered bad instruction data */

int VibroOnOffScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*

	/* WARNING: Bad instruction - Truncating control flow here */
	//halt_baddata();
}



// decompiled code
// original method signature: 
// int /*$ra*/ MissionSelectScreen(int bSetup /*$a0*/)
 // line 3394, offset 0x001c3b1c
	/* begin block 1 */
		// Start line: 3396
		// Start offset: 0x001C3B1C
		// Variables:
	// 		int i; // $a1

		/* begin block 1.1 */
			// Start line: 3423
			// Start offset: 0x001C3BDC
			// Variables:
		// 		int usedB; // $s2
		// 		int done; // $t0
		// 		int bP; // $a3
		// 		int bN; // $s5
		// 		int shift; // $a3
		/* end block 1.1 */
		// End offset: 0x001C40D8
		// End Line: 3552
	/* end block 1 */
	// End offset: 0x001C4338
	// End Line: 3625

	/* begin block 2 */
		// Start line: 7783
	/* end block 2 */
	// End Line: 7784

	/* begin block 3 */
		// Start line: 7784
	/* end block 3 */
	// End Line: 7785

	/* begin block 4 */
		// Start line: 7791
	/* end block 4 */
	// End Line: 7792

int MissionSelectScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*

	byte bVar1;
	bool bVar2;
	bool bVar3;
	uchar uVar4;
	PSXSCREEN *pPVar5;
	int *piVar6;
	int iVar7;
	int iVar8;

	if (bSetup == 0) {
		if ((uRam001cc5dc & 0x40) == 0) {
			if ((uRam001cc5dc & 0x10) == 0) {
				if ((uRam001cc5dc & 0x1000) == 0) {
					if ((uRam001cc5dc & 0x4000) == 0) {
						return 0;
					}
					bVar1 = pCurrButton->d;
				}
				else {
					bVar1 = pCurrButton->u;
				}
				DAT_FRNT__001c6a8c = (uint)bVar1 - 1;
			}
			else {
				DAT_FRNT__001c6a74 = 0;
				DAT_FRNT__001c6ab0 = 0;
			}
		}
		else {
			if (DAT_FRNT__001c6a8c == 5) {
				iVar7 = DAT_FRNT__001cc54c + 4;
				if ((iVar7 < *(int *)(DAT_FRNT__001c6a70 * 8 + 0x1c6b9c)) && (iVar7 < gFurthestMission)) {
				LAB_FRNT__001c41fc:
					DAT_FRNT__001cc54c = iVar7;
					FESound(3);
					(*(code *)(&PTR_CentreScreen_FRNT__001c6a20)[(uint)(byte)pCurrScreen->userFunctionNum - 1]
						)(1);
					DAT_FRNT__001c6aa0 = 1;
					return 1;
				}
			}
			else {
				if (DAT_FRNT__001c6a8c == 0) {
					if (*(int *)(&DAT_FRNT__001c6b98 + DAT_FRNT__001c6a70 * 8) < DAT_FRNT__001cc54c) {
						iVar7 = DAT_FRNT__001cc54c + -4;
						goto LAB_FRNT__001c41fc;
					}
				}
				else {
					bReturnToMain = 0;
					GameType = GAME_REPLAYMISSION;
					feVariableSave[1] = DAT_FRNT__001c6a8c;
					feVariableSave[0] = DAT_FRNT__001cc54c;
					feVariableSave[2] = DAT_FRNT__001c6a70;
					gCurrentMissionNumber =
						(&DAT_FRNT__001c6bb8)[(DAT_FRNT__001cc54c + DAT_FRNT__001c6a8c + -1) * 2];
				}
			}
		}
		return 0;
	}
	DAT_FRNT__001c6ab0 = 1;
	if (DAT_FRNT__001c6a74 == 0) {
		DAT_FRNT__001cc54c = *(int *)(&DAT_FRNT__001c6b98 + DAT_FRNT__001c6a70 * 8);
		DAT_FRNT__001c6a8c = 0;
		if (GameType == GAME_REPLAYMISSION) {
			LoadBackgroundFile(s_DATA_CITYBACK_RAW_FRNT__001c08b4);
		}
	}
	pPVar5 = pCurrScreen;
	if (feVariableSave[0] != -1) {
		DAT_FRNT__001cc54c = feVariableSave[0];
		DAT_FRNT__001c6a8c = feVariableSave[1];
		DAT_FRNT__001c6a70 = feVariableSave[2];
	}
	iVar8 = 0;
	bVar2 = false;
	bVar3 = false;
	iVar7 = 0;
	piVar6 = &DAT_FRNT__001c6bb8 + DAT_FRNT__001cc54c * 2;
	do {
		if (((gFurthestMission < *piVar6) ||
			(*(int *)(DAT_FRNT__001c6a70 * 8 + 0x1c6b9c) < iVar7 + DAT_FRNT__001cc54c)) ||
			(0x24 < iVar7 + DAT_FRNT__001cc54c)) {
			bVar2 = true;
		}
		else {
			iVar8 = iVar8 + 1;
		}
		iVar7 = iVar7 + 1;
		piVar6 = piVar6 + 2;
	} while ((iVar7 < 4) && (!bVar2));
	uVar4 = (uchar)iVar8;
	if (iVar8 == 1) {
		pCurrScreen->buttons[1].d = '\x02';
		pPVar5->buttons[1].u = '\x02';
		sprintf(pCurrScreen->buttons[1].Name,
			(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)[DAT_FRNT__001cc54c]);
		sprintf(pCurrScreen->buttons[2].Name, &DAT_FRNT__001c0830);
		sprintf(pCurrScreen->buttons[3].Name, &DAT_FRNT__001c0830);
	LAB_FRNT__001c3e3c:
		sprintf(pCurrScreen->buttons[4].Name, &DAT_FRNT__001c0830);
	}
	else {
		if (iVar8 == 2) {
			pCurrScreen->buttons[1].u = '\x03';
			pCurrScreen->buttons[1].d = '\x03';
			pCurrScreen->buttons[2].u = uVar4;
			pCurrScreen->buttons[2].d = uVar4;
			sprintf(pCurrScreen->buttons[1].Name,
				(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)[DAT_FRNT__001cc54c]);
			sprintf(pCurrScreen->buttons[2].Name,
				(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)
				[DAT_FRNT__001cc54c + 1]);
			sprintf(pCurrScreen->buttons[3].Name, &DAT_FRNT__001c0830);
			goto LAB_FRNT__001c3e3c;
		}
		if (iVar8 == 3) {
			pCurrScreen->buttons[1].u = '\x04';
			pCurrScreen->buttons[1].d = uVar4;
			pCurrScreen->buttons[2].u = '\x02';
			pCurrScreen->buttons[2].d = '\x04';
			pCurrScreen->buttons[3].u = uVar4;
			pCurrScreen->buttons[3].d = '\x02';
			sprintf(pCurrScreen->buttons[1].Name,
				(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)[DAT_FRNT__001cc54c]);
			sprintf(pCurrScreen->buttons[2].Name,
				(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)
				[DAT_FRNT__001cc54c + 1]);
			sprintf(pCurrScreen->buttons[3].Name,
				(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)
				[DAT_FRNT__001cc54c + 2]);
			goto LAB_FRNT__001c3e3c;
		}
		if (iVar8 == 4) {
			pCurrScreen->buttons[1].u = '\x05';
			pCurrScreen->buttons[1].d = '\x03';
			pCurrScreen->buttons[2].u = '\x02';
			pCurrScreen->buttons[2].d = uVar4;
			pCurrScreen->buttons[3].u = '\x03';
			pCurrScreen->buttons[3].d = '\x05';
			pCurrScreen->buttons[4].u = uVar4;
			pCurrScreen->buttons[4].d = '\x02';
			sprintf(pCurrScreen->buttons[1].Name,
				(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)[DAT_FRNT__001cc54c]);
			sprintf(pCurrScreen->buttons[2].Name,
				(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)
				[DAT_FRNT__001cc54c + 1]);
			sprintf(pCurrScreen->buttons[3].Name,
				(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)
				[DAT_FRNT__001cc54c + 2]);
			sprintf(pCurrScreen->buttons[4].Name,
				(&PTR_s_Informazioni_sorveglianza_FRNT__001c06e4_FRNT__001c68f8)
				[DAT_FRNT__001cc54c + 3]);
		}
	}
	pPVar5 = pCurrScreen;
	if (((iVar8 == 4) &&
		((int)(&DAT_FRNT__001c6bb8)[(DAT_FRNT__001cc54c + 4) * 2] <= gFurthestMission)) &&
		(DAT_FRNT__001cc54c + 4 != *(int *)(DAT_FRNT__001c6a70 * 8 + 0x1c6b9c))) {
		bVar3 = true;
	}
	if (bVar3) {
		if (DAT_FRNT__001cc54c == *(int *)(&DAT_FRNT__001c6b98 + DAT_FRNT__001c6a70 * 8)) {
		LAB_FRNT__001c406c:
			if (bVar3) {
				pCurrScreen->buttons[1].u = '\x06';
				pCurrScreen->buttons[4].d = '\x06';
				pCurrScreen->buttons[5].u = '\x05';
				pCurrScreen->buttons[5].d = '\x02';
				pPVar5 = pCurrScreen;
				pCurrScreen->buttons[5].action = 0;
				pPVar5->buttons[0].action = 0x500;
			}
			else {
				pCurrScreen->buttons[0].action = 0x500;
				pPVar5->buttons[5].action = 0x500;
			}
			pCurrButton = pPVar5->buttons + 1;
			DAT_FRNT__001c6a8c = 1;
			goto LAB_FRNT__001c40d8;
		}
		pCurrScreen->buttons[0].u = '\x06';
		pCurrScreen->buttons[0].d = '\x02';
		pCurrScreen->buttons[5].u = '\x05';
		pCurrScreen->buttons[5].d = '\x01';
		pCurrScreen->buttons[1].u = '\x01';
		pCurrScreen->buttons[4].d = '\x06';
		pPVar5 = pCurrScreen;
		pCurrScreen->buttons[0].action = 0;
		pPVar5->buttons[5].action = 0;
	}
	else {
		if (DAT_FRNT__001cc54c == *(int *)(&DAT_FRNT__001c6b98 + DAT_FRNT__001c6a70 * 8))
			goto LAB_FRNT__001c406c;
		pCurrScreen->buttons[0].u = uVar4 + '\x01';
		pCurrScreen->buttons[0].d = '\x02';
		pCurrScreen->buttons[1].u = '\x01';
		pCurrScreen->buttons[iVar8].d = '\x01';
		pPVar5 = pCurrScreen;
		pCurrScreen->buttons[0].action = 0;
		pPVar5->buttons[5].action = 0x500;
	}
	pCurrButton = pPVar5->buttons;
	DAT_FRNT__001c6a8c = 0;
LAB_FRNT__001c40d8:
	if (DAT_FRNT__001c6a78 == -1) {
		SetupExtraPoly(s_DATA_CITY_RAW_FRNT__001c088c, DAT_FRNT__001c6a70, 0);
	}
	else {
		DAT_FRNT__001c6a90 = 1;
	}
	feVariableSave[0] = 0xffffffff;
	feVariableSave[1] = 0xffffffff;
	feVariableSave[2] = 0xffffffff;
	feVariableSave[3] = 0xffffffff;
	DAT_FRNT__001c6a74 = 1;
	return 1;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ MissionCityScreen(int bSetup /*$a0*/)
 // line 3632, offset 0x001c4338
	/* begin block 1 */
		// Start line: 3638
		// Start offset: 0x001C4338

		/* begin block 1.1 */
			// Start line: 3703
			// Start offset: 0x001C449C

			/* begin block 1.1.1 */
				// Start line: 3703
				// Start offset: 0x001C449C
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.1.1 */
			// End offset: 0x001C449C
			// End Line: 3703
		/* end block 1.1 */
		// End offset: 0x001C449C
		// End Line: 3703

		/* begin block 1.2 */
			// Start line: 3709
			// Start offset: 0x001C44C4

			/* begin block 1.2.1 */
				// Start line: 3709
				// Start offset: 0x001C44C4
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.2.1 */
			// End offset: 0x001C44C4
			// End Line: 3709
		/* end block 1.2 */
		// End offset: 0x001C44C4
		// End Line: 3709
	/* end block 1 */
	// End offset: 0x001C4600
	// End Line: 3720

	/* begin block 2 */
		// Start line: 8321
	/* end block 2 */
	// End Line: 8322

	/* begin block 3 */
		// Start line: 8329
	/* end block 3 */
	// End Line: 8330

	/* begin block 4 */
		// Start line: 8334
	/* end block 4 */
	// End Line: 8335

int MissionCityScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*

	byte bVar1;
	DB *pDVar2;
	PSXSCREEN *pPVar3;
	int iVar4;
	uint *puVar5;
	undefined4 local_10;
	undefined4 local_c;

	pPVar3 = pCurrScreen;
	if (bSetup == 0) {
		if ((uRam001cc5dc & 0x10) != 0) {
			DAT_FRNT__001c6a90 = 0;
			FESound(0);
			DAT_FRNT__001c6aac = 1;
			LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
			return 0;
		}
		if ((uRam001cc5dc & 0x1000) == 0) {
			if ((uRam001cc5dc & 0x4000) == 0) {
				DAT_FRNT__001c6a70 = (uint)pCurrButton->u & 3;
				return 0;
			}
			bVar1 = pCurrButton->d;
		}
		else {
			bVar1 = pCurrButton->u;
		}
		local_10 = DAT_FRNT__001c0884;
		local_c = DAT_FRNT__001c0888;
		DAT_FRNT__001c6a70 = (uint)bVar1 - 1;
		LoadImage(&local_10, &DAT_0013f400 + DAT_FRNT__001c6a70 * 0x8000);
		DrawSync(0);
		DisplayOnScreenText();
		pDVar2 = current;
		DAT_FRNT__001cc5c8 = DAT_FRNT__001cc5c8 & 0xff000000 | *(uint *)current->ot[2] & 0xffffff;
		*(uint *)current->ot[2] = *(uint *)current->ot[2] & 0xff000000 | 0x1cc5c8;
		DAT_FRNT__001cbdb8 = DAT_FRNT__001cbdb8 & 0xff000000 | *(uint *)pDVar2->ot[3] & 0xffffff;
		puVar5 = (uint *)pDVar2->ot[3];
		*puVar5 = *puVar5 & 0xff000000 | 0x1cbdb8;
		EndFrame();
		return 0;
	}
	GameType = GAME_MISSION;
	if (gFurthestMission == 0) {
		iVar4 = 0x300;
	LAB_FRNT__001c43f4:
		pCurrScreen->buttons[0].action = iVar4;
		pPVar3->buttons[1].action = iVar4;
		pPVar3->buttons[2].action = iVar4;
	}
	else {
		if (gFurthestMission < 10) {
			pCurrScreen->buttons[0].action = 0x113;
			pPVar3->buttons[1].action = 0x300;
			pPVar3->buttons[2].action = 0x300;
			pPVar3->buttons[3].action = 0x300;
			goto LAB_FRNT__001c4404;
		}
		if (gFurthestMission < 0x15) {
			pCurrScreen->buttons[0].action = 0x113;
			pPVar3->buttons[1].action = 0x113;
			pPVar3->buttons[2].action = 0x300;
			pPVar3->buttons[3].action = 0x300;
			goto LAB_FRNT__001c4404;
		}
		if (0x1e < gFurthestMission) {
			iVar4 = 0x113;
			goto LAB_FRNT__001c43f4;
		}
		iVar4 = 0x300;
		pCurrScreen->buttons[0].action = 0x113;
		pPVar3->buttons[1].action = 0x113;
		pPVar3->buttons[2].action = 0x113;
	}
	pPVar3->buttons[3].action = iVar4;
LAB_FRNT__001c4404:
	LoadBackgroundFile(s_DATA_CITYBACK_RAW_FRNT__001c08b4);
	if (DAT_FRNT__001c6a78 == -1) {
		SetupExtraPoly(s_DATA_CITY_RAW_FRNT__001c088c, 0, 0);
	}
	else {
		DAT_FRNT__001c6a90 = 1;
	}
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CutSceneSelectScreen(int bSetup /*$a0*/)
 // line 3728, offset 0x001c4600
	/* begin block 1 */
		// Start line: 3730
		// Start offset: 0x001C4600
		// Variables:
	// 		struct RENDER_ARGS renderArgs; // stack offset -48
	// 		int extraVal; // $a0
	// 		struct RECT rect; // stack offset -24

		/* begin block 1.1 */
			// Start line: 3789
			// Start offset: 0x001C4798

			/* begin block 1.1.1 */
				// Start line: 3789
				// Start offset: 0x001C4798
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.1.1 */
			// End offset: 0x001C4798
			// End Line: 3789
		/* end block 1.1 */
		// End offset: 0x001C4798
		// End Line: 3789

		/* begin block 1.2 */
			// Start line: 3729
			// Start offset: 0x001C4844
			// Variables:
		// 		int offset; // $a1

			/* begin block 1.2.1 */
				// Start line: 3729
				// Start offset: 0x001C4844
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.2.1 */
			// End offset: 0x001C4844
			// End Line: 3729
		/* end block 1.2 */
		// End offset: 0x001C4844
		// End Line: 3729

		/* begin block 1.3 */
			// Start line: 3808
			// Start offset: 0x001C4900

			/* begin block 1.3.1 */
				// Start line: 3808
				// Start offset: 0x001C4900
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.3.1 */
			// End offset: 0x001C4900
			// End Line: 3808
		/* end block 1.3 */
		// End offset: 0x001C4900
		// End Line: 3808

		/* begin block 1.4 */
			// Start line: 3813
			// Start offset: 0x001C4940

			/* begin block 1.4.1 */
				// Start line: 3813
				// Start offset: 0x001C4940
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.4.1 */
			// End offset: 0x001C4940
			// End Line: 3813
		/* end block 1.4 */
		// End offset: 0x001C4940
		// End Line: 3813
	/* end block 1 */
	// End offset: 0x001C4B30
	// End Line: 3847

	/* begin block 2 */
		// Start line: 8520
	/* end block 2 */
	// End Line: 8521

	/* begin block 3 */
		// Start line: 8529
	/* end block 3 */
	// End Line: 8530

	/* begin block 4 */
		// Start line: 8530
	/* end block 4 */
	// End Line: 8531

	/* begin block 5 */
		// Start line: 8534
	/* end block 5 */
	// End Line: 8535

int CutSceneSelectScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	DB *pDVar2;
	PSXBUTTON *pPVar3;
	int iVar4;
	uint *puVar5;
	PSXBUTTON **ppPVar6;
	undefined *puVar7;
	undefined4 local_18;
	undefined4 local_14;
	undefined4 local_10;
	undefined4 local_c;

	iVar4 = ScreenDepth;
	local_18 = DAT_FRNT__001c0884;
	local_14 = DAT_FRNT__001c0888;
	if (bSetup == 0) {
		if ((uRam001cc5dc & 0x10) == 0) {
			if ((uRam001cc5dc & 0x40) != 0) {
				if (DAT_FRNT__001c6a8c == 0) {
					if (DAT_FRNT__001c69a0 == 0) {
						DAT_FRNT__001c69a0 = *(int *)(&DAT_FRNT__001c69b8 + (DAT_FRNT__001c6a70 + 1) * 4) - 1U;
						if ((int)(uint)(byte)(&DAT_FRNT__001c69e0)[gFurthestMission] <
							(int)((*(int *)(&DAT_FRNT__001c69b8 + (DAT_FRNT__001c6a70 + 1) * 4) - 1U) +
								*(int *)(&DAT_FRNT__001c69cc + DAT_FRNT__001c6a70 * 4) + 1)) {
							DAT_FRNT__001c69a0 = (uint)(byte)(&DAT_FRNT__001c69e0)[gFurthestMission];
						}
						puVar7 = &DAT_0015f400 + DAT_FRNT__001c69a0 * 0x8000;
					}
					else {
						DAT_FRNT__001c69a0 = DAT_FRNT__001c69a0 - 1;
						puVar7 = &DAT_0015f400 + DAT_FRNT__001c69a0 * 0x8000;
					}
				}
				else {
					if (DAT_FRNT__001c6a8c != 2) {
						bReturnToMain = 0;
						ppPVar6 = pButtonStack10 + ScreenDepth;
						pScreenStack10[ScreenDepth] = pCurrScreen;
						pPVar3 = pCurrButton;
						feVariableSave[1] = DAT_FRNT__001c6a70;
						feVariableSave[0] = DAT_FRNT__001c69a0;
						*ppPVar6 = pCurrButton;
						ScreenNames12[iVar4] = pPVar3->Name;
						StartRender(feVariableSave[0] +
							*(int *)(&DAT_FRNT__001c69cc + feVariableSave[1] * 4) + 1);
						return 0;
					}
					if ((DAT_FRNT__001c69a0 ==
						*(int *)(&DAT_FRNT__001c69b8 + (DAT_FRNT__001c6a70 + 1) * 4) + -1) ||
						((int)(uint)(byte)(&DAT_FRNT__001c69e0)[gFurthestMission] <=
						(int)(DAT_FRNT__001c69a0 + *(int *)(&DAT_FRNT__001c69cc + DAT_FRNT__001c6a70 * 4) + 1)
							)) {
						puVar7 = &DAT_0015f400;
						DAT_FRNT__001c69a0 = 0;
					}
					else {
						DAT_FRNT__001c69a0 = DAT_FRNT__001c69a0 + 1;
						puVar7 = &DAT_0015f400 + DAT_FRNT__001c69a0 * 0x8000;
					}
				}
				local_c = DAT_FRNT__001c0888;
				local_10 = DAT_FRNT__001c0884;
				LoadImage(&local_10, puVar7);
				DrawSync(0);
				DisplayOnScreenText();
				pDVar2 = current;
				DAT_FRNT__001cc5c8 = DAT_FRNT__001cc5c8 & 0xff000000 | *(uint *)current->ot[2] & 0xffffff;
				*(uint *)current->ot[2] = *(uint *)current->ot[2] & 0xff000000 | 0x1cc5c8;
				DAT_FRNT__001cbdb8 = DAT_FRNT__001cbdb8 & 0xff000000 | *(uint *)pDVar2->ot[3] & 0xffffff;
				puVar5 = (uint *)pDVar2->ot[3];
				*puVar5 = *puVar5 & 0xff000000 | 0x1cbdb8;
				EndFrame();
				return 0;
			}
			if ((uRam001cc5dc & 0x1000) == 0) {
				if ((uRam001cc5dc & 0x4000) == 0) {
					return 0;
				}
				bVar1 = pCurrButton->d;
			}
			else {
				bVar1 = pCurrButton->u;
			}
			DAT_FRNT__001c6a8c = (uint)bVar1 - 1;
		}
		else {
			DAT_FRNT__001c6a90 = 0;
			DAT_FRNT__001c6a80 = 0;
		}
		iVar4 = 0;
	}
	else {
		LoadBackgroundFile(s_DATA_CUTS_CUTBACK_RAW_FRNT__001c08c8);
		DAT_FRNT__001c6a70 = feVariableSave[1];
		if (feVariableSave[0] == -1) {
			DAT_FRNT__001c69a0 = 0;
			DAT_FRNT__001c6a70 = GameLevel;
		}
		else {
			DAT_FRNT__001c69a0 = feVariableSave[0];
			feVariableSave[3] = 0xffffffff;
			feVariableSave[2] = 0xffffffff;
			feVariableSave[1] = -1;
			feVariableSave[0] = -1;
		}
		if ((int)DAT_FRNT__001c6a7a == GameLevel) {
			DAT_FRNT__001c6a90 = 1;
			LoadImage(&local_18, &DAT_0015f400);
			DrawSync(0);
		}
		else {
			SetupExtraPoly((&PTR_s_DATA_CUTS_CCUTS_RAW_FRNT__001c073c_FRNT__001c69a8)[GameLevel],
				DAT_FRNT__001c69a0, 0x20000);
		}
		iVar4 = 1;
		DAT_FRNT__001c6a80 = 1;
		DAT_FRNT__001c6a8c = 1;
		DAT_FRNT__001c69a4 = 1;
		pCurrButton = pCurrScreen->buttons + 1;
	}
	return iVar4;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CutSceneCitySelectScreen(int bSetup /*$a0*/)
 // line 3855, offset 0x001c4b30
	/* begin block 1 */
		// Start line: 3857
		// Start offset: 0x001C4B30
		// Variables:
	// 		struct RECT rect; // stack offset -24

		/* begin block 1.1 */
			// Start line: 3856
			// Start offset: 0x001C4E6C

			/* begin block 1.1.1 */
				// Start line: 3856
				// Start offset: 0x001C4E6C
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.1.1 */
			// End offset: 0x001C4E6C
			// End Line: 3856
		/* end block 1.1 */
		// End offset: 0x001C4E6C
		// End Line: 3856

		/* begin block 1.2 */
			// Start line: 3856
			// Start offset: 0x001C4E6C

			/* begin block 1.2.1 */
				// Start line: 3856
				// Start offset: 0x001C4E6C
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.2.1 */
			// End offset: 0x001C4E6C
			// End Line: 3856
		/* end block 1.2 */
		// End offset: 0x001C4E6C
		// End Line: 3856

		/* begin block 1.3 */
			// Start line: 3856
			// Start offset: 0x001C4EB4

			/* begin block 1.3.1 */
				// Start line: 3856
				// Start offset: 0x001C4EB4
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.3.1 */
			// End offset: 0x001C4EB4
			// End Line: 3856
		/* end block 1.3 */
		// End offset: 0x001C4EB4
		// End Line: 3856

		/* begin block 1.4 */
			// Start line: 3856
			// Start offset: 0x001C4FAC

			/* begin block 1.4.1 */
				// Start line: 3856
				// Start offset: 0x001C4FAC
				// Variables:
			// 		struct RECT rect; // stack offset -16
			/* end block 1.4.1 */
			// End offset: 0x001C50A0
			// End Line: 3856
		/* end block 1.4 */
		// End offset: 0x001C50A0
		// End Line: 3856
	/* end block 1 */
	// End offset: 0x001C50B0
	// End Line: 3995

	/* begin block 2 */
		// Start line: 8827
	/* end block 2 */
	// End Line: 8828

	/* begin block 3 */
		// Start line: 8836
	/* end block 3 */
	// End Line: 8837

	/* begin block 4 */
		// Start line: 8837
	/* end block 4 */
	// End Line: 8838

int CutSceneCitySelectScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	DB *pDVar1;
	PSXSCREEN *pPVar2;
	PSXBUTTON *pPVar3;
	PSXBUTTON **ppPVar4;
	uint *puVar5;
	int offset;
	undefined *puVar6;
	undefined4 local_18;
	undefined4 local_14;
	undefined4 local_10;
	undefined4 local_c;

	offset = ScreenDepth;
	local_18 = DAT_FRNT__001c0884;
	local_14 = DAT_FRNT__001c0888;
	if (bSetup != 0) {
		LoadBackgroundFile(s_DATA_CITYBACK_RAW_FRNT__001c08b4);
		if (feVariableSave[0] == -1) {
			if (DAT_FRNT__001c69a4 == 0) {
				DAT_FRNT__001c6a70 = 0;
				DAT_FRNT__001c69a4 = 1;
			}
		}
		else {
			DAT_FRNT__001c6a70 = feVariableSave[0];
			feVariableSave[3] = 0xffffffff;
			feVariableSave[2] = 0xffffffff;
			feVariableSave[1] = 0xffffffff;
			feVariableSave[0] = -1;
		}
		pCurrScreen->buttons[3].d = '\x01';
		pCurrScreen->buttons[0].u = '\x04';
		pPVar2 = pCurrScreen;
		offset = gFurthestMission;
		if (gFurthestMission == 0) {
			pCurrScreen->buttons[0].action = 0x300;
			pPVar2->buttons[1].action = 0x300;
			pPVar2->buttons[2].action = 0x300;
			pPVar2->buttons[3].action = 0x300;
		}
		else {
			if (gFurthestMission < 10) {
				pCurrScreen->buttons[0].action = 0x116;
				pPVar2->buttons[1].action = 0x300;
				pPVar2->buttons[2].action = 0x300;
				pPVar2->buttons[3].action = 0x300;
			}
			else {
				if (gFurthestMission < 0x15) {
					pCurrScreen->buttons[0].action = 0x116;
					pPVar2->buttons[1].action = 0x116;
					pPVar2->buttons[2].action = 0x300;
					pPVar2->buttons[3].action = 0x300;
				}
				else {
					if (gFurthestMission < 0x1f) {
						pCurrScreen->buttons[0].action = 0x116;
						pPVar2->buttons[1].action = 0x116;
						pPVar2->buttons[2].action = 0x116;
						pPVar2->buttons[3].action = 0x300;
					}
					else {
						pCurrScreen->buttons[0].action = 0x116;
						pPVar2->buttons[1].action = 0x116;
						pPVar2->buttons[2].action = 0x116;
						pPVar2->buttons[3].action = 0x116;
						if (offset == 0x28) {
							pPVar2->buttons[3].d = '\x05';
							pCurrScreen->buttons[0].u = '\x05';
						}
					}
				}
			}
		}
		if (DAT_FRNT__001c6a78 == -1) {
			offset = DAT_FRNT__001c6a70;
			if (DAT_FRNT__001c6a70 == 4) {
				offset = 0;
			}
			SetupExtraPoly(s_DATA_CITY_RAW_FRNT__001c088c, offset, 0);
			return 0;
		}
		DAT_FRNT__001c6a90 = 1;
		if (DAT_FRNT__001c6a70 == 4) {
			LoadImage(&local_18, &DAT_0013f400);
		}
		else {
			LoadImage(&local_18, &DAT_0013f400 + DAT_FRNT__001c6a70 * 0x8000);
		}
		DrawSync(0);
		return 0;
	}
	if ((uRam001cc5dc & 0x40) != 0) {
		DAT_FRNT__001c6a7b = 0xff;
		DAT_FRNT__001c6a7c = (undefined)GameLevel;
		if (GameLevel != 4) {
			DAT_FRNT__001c6a7b = 0xff;
			return 0;
		}
		bReturnToMain = 0;
		ppPVar4 = pButtonStack10 + ScreenDepth;
		pScreenStack10[ScreenDepth] = pCurrScreen;
		pPVar3 = pCurrButton;
		*ppPVar4 = pCurrButton;
		ScreenNames12[offset] = pPVar3->Name;
		feVariableSave[0] = DAT_FRNT__001c6a70;
		StartRender(0x60);
		return 0;
	}
	if ((uRam001cc5dc & 0x10) != 0) {
		FESound(0);
		DAT_FRNT__001c6aac = 1;
		LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
		DAT_FRNT__001c69a4 = 0;
		DAT_FRNT__001c6a90 = 0;
		return 0;
	}
	if ((uRam001cc5dc & 0x1000) == 0) {
		if ((uRam001cc5dc & 0x4000) == 0) {
			return 0;
		}
		GameLevel = (uint)pCurrButton->d - 1;
		DAT_FRNT__001c6a70 = GameLevel;
		if (GameLevel != 4) {
			local_10 = DAT_FRNT__001c0884;
			local_c = DAT_FRNT__001c0888;
			LoadImage(&local_10, &DAT_0013f400 + GameLevel * 0x8000);
			DrawSync(0);
			DisplayOnScreenText();
			pDVar1 = current;
			DAT_FRNT__001cc5c8 = DAT_FRNT__001cc5c8 & 0xff000000 | *(uint *)current->ot[2] & 0xffffff;
			*(uint *)current->ot[2] = *(uint *)current->ot[2] & 0xff000000 | 0x1cc5c8;
			DAT_FRNT__001cbdb8 = DAT_FRNT__001cbdb8 & 0xff000000 | *(uint *)pDVar1->ot[3] & 0xffffff;
			puVar5 = (uint *)pDVar1->ot[3];
			*puVar5 = *puVar5 & 0xff000000 | 0x1cbdb8;
			EndFrame();
			return 0;
		}
	}
	else {
		DAT_FRNT__001c6a70 = (uint)pCurrButton->u - 1;
		if (DAT_FRNT__001c6a70 != 4) {
			puVar6 = &DAT_0013f400 + DAT_FRNT__001c6a70 * 0x8000;
			goto LAB_FRNT__001c4ec0;
		}
	}
	puVar6 = &DAT_0013f400;
LAB_FRNT__001c4ec0:
	local_10 = DAT_FRNT__001c0884;
	local_c = DAT_FRNT__001c0888;
	GameLevel = DAT_FRNT__001c6a70;
	LoadImage(&local_10, puVar6);
	DrawSync(0);
	DisplayOnScreenText();
	pDVar1 = current;
	DAT_FRNT__001cc5c8 = DAT_FRNT__001cc5c8 & 0xff000000 | *(uint *)current->ot[2] & 0xffffff;
	*(uint *)current->ot[2] = *(uint *)current->ot[2] & 0xff000000 | 0x1cc5c8;
	DAT_FRNT__001cbdb8 = DAT_FRNT__001cbdb8 & 0xff000000 | *(uint *)pDVar1->ot[3] & 0xffffff;
	puVar5 = (uint *)pDVar1->ot[3];
	*puVar5 = *puVar5 & 0xff000000 | 0x1cbdb8;
	EndFrame();
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ SetVolumeScreen(int bSetup /*$a0*/)
 // line 4005, offset 0x001c50b0
	/* begin block 1 */
		// Start line: 4007
		// Start offset: 0x001C50B0
		// Variables:
	// 		int last; // $s2
	// 		char text[4]; // stack offset -48
	// 		int ypos[2]; // stack offset -40
	// 		struct RECT rect; // stack offset -32

		/* begin block 1.1 */
			// Start line: 4048
			// Start offset: 0x001C5254

			/* begin block 1.1.1 */
				// Start line: 4048
				// Start offset: 0x001C5254
				// Variables:
			// 		struct DB *db_hold; // $a1
			/* end block 1.1.1 */
			// End offset: 0x001C5254
			// End Line: 4048
		/* end block 1.1 */
		// End offset: 0x001C5254
		// End Line: 4048

		/* begin block 1.2 */
			// Start line: 4070
			// Start offset: 0x001C5284

			/* begin block 1.2.1 */
				// Start line: 4070
				// Start offset: 0x001C5284
				// Variables:
			// 		struct DB *db_hold; // $a1
			/* end block 1.2.1 */
			// End offset: 0x001C5284
			// End Line: 4070
		/* end block 1.2 */
		// End offset: 0x001C5284
		// End Line: 4070

		/* begin block 1.3 */
			// Start line: 4097
			// Start offset: 0x001C52CC

			/* begin block 1.3.1 */
				// Start line: 4097
				// Start offset: 0x001C52CC
				// Variables:
			// 		struct DB *db_hold; // $a1
			/* end block 1.3.1 */
			// End offset: 0x001C52CC
			// End Line: 4097
		/* end block 1.3 */
		// End offset: 0x001C52CC
		// End Line: 4097

		/* begin block 1.4 */
			// Start line: 4119
			// Start offset: 0x001C5420

			/* begin block 1.4.1 */
				// Start line: 4119
				// Start offset: 0x001C5420
				// Variables:
			// 		struct DB *db_hold; // $a1
			/* end block 1.4.1 */
			// End offset: 0x001C5530
			// End Line: 4122
		/* end block 1.4 */
		// End offset: 0x001C5530
		// End Line: 4122
	/* end block 1 */
	// End offset: 0x001C55F8
	// End Line: 4148

	/* begin block 2 */
		// Start line: 9157
	/* end block 2 */
	// End Line: 9158

	/* begin block 3 */
		// Start line: 9168
	/* end block 3 */
	// End Line: 9169

	/* begin block 4 */
		// Start line: 9169
	/* end block 4 */
	// End Line: 9170

	/* begin block 5 */
		// Start line: 9172
	/* end block 5 */
	// End Line: 9173

int SetVolumeScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*

	char **ppcVar1;
	byte bVar2;
	int iVar3;
	int iVar4;
	DB *pDVar5;
	DB *pDVar6;
	char acStack48[8];
	int local_28;
	int local_24;
	undefined4 local_20;
	undefined4 local_1c;

	iVar4 = gMasterVolume;
	iVar3 = gMusicVolume;
	local_28 = DAT_FRNT__001c08e0;
	local_24 = DAT_FRNT__001c08e4;
	local_20 = DAT_FRNT__001c0884;
	local_1c = DAT_FRNT__001c0888;
	if (bSetup != 0) {
		DAT_FRNT__001c6a8c = 0;
		DAT_FRNT__001cc260 = gMasterVolume;
		DAT_FRNT__001cc588 = gMusicVolume;
		LoadBackgroundFile(s_DATA_VOL_RAW_FRNT__001c08e8);
		sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + gMasterVolume) / 100);
		FEPrintString(acStack48, 0x98, local_28, 2, 0x80, 0x80, 0x80);
		sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + gMusicVolume) / 100);
		FEPrintString(acStack48, 0x98, local_24, 2, 0x80, 0x80, 0x80);
		return 0;
	}
	bVar2 = pCurrButton->u;
	DAT_FRNT__001c6a8c = (uint)bVar2 & 3;
	if (((int)(short)uRam001cc5dc & 0x8000U) == 0) {
		if ((uRam001cc5dc & 0x2000) == 0) {
			if ((uRam001cc5dc & 0x10) != 0) {
				FESound(0);
				DAT_FRNT__001c6aac = 1;
				gMasterVolume = DAT_FRNT__001cc260;
				gMusicVolume = DAT_FRNT__001cc588;
				LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
				SetMasterVolume(gMasterVolume);
				SetXMVolume(gMusicVolume);
				return 0;
			}
			if ((uRam001cc5dc & 0x40) == 0) {
				return 0;
			}
			if (DAT_FRNT__001c6a8c != 2) {
				return 0;
			}
			LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
			return 0;
		}
		if ((bVar2 & 3) != 0) {
			if (DAT_FRNT__001c6a8c != 1) goto LAB_FRNT__001c5530;
			gMusicVolume = gMusicVolume + 100;
			if (gMusicVolume < 1) goto LAB_FRNT__001c5418;
			gMusicVolume = 0;
		LAB_FRNT__001c5408:
			FESound(1);
			goto LAB_FRNT__001c5424;
		}
		gMasterVolume = gMasterVolume + 100;
		if (gMasterVolume < 1) goto LAB_FRNT__001c52c4;
		gMasterVolume = 0;
	LAB_FRNT__001c52b4:
		FESound(1);
	}
	else {
		if ((bVar2 & 3) != 0) {
			if (DAT_FRNT__001c6a8c != 1) goto LAB_FRNT__001c5530;
			gMusicVolume = gMusicVolume + -100;
			if (gMusicVolume < -10000) {
				gMusicVolume = -10000;
				goto LAB_FRNT__001c5408;
			}
		LAB_FRNT__001c5418:
			FESound(3);
		LAB_FRNT__001c5424:
			sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + gMusicVolume) / 100);
			FEPrintString(acStack48, 0x98, local_24, 2, 0x80, 0x80, 0x80);
			sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + iVar3) / 100);
			FEPrintString(acStack48, 0x98, local_24, 2, 0, 0, 0);
			DrawSync(0);
			VSync(0);
			PutDispEnv(&current->disp);
			PutDrawEnv(&current->draw);
			pDVar6 = last;
			pDVar5 = current;
			ppcVar1 = &last->primtab;
			current = last;
			last = pDVar5;
			pDVar6->primptr = *ppcVar1;
			DrawOTag(pDVar5->ot + 0x10);
			ClearOTagR(current->ot, 0x10);
			VSync(0);
			goto LAB_FRNT__001c5530;
		}
		gMasterVolume = gMasterVolume + -100;
		if (gMasterVolume < -10000) {
			gMasterVolume = -10000;
			goto LAB_FRNT__001c52b4;
		}
	LAB_FRNT__001c52c4:
		FESound(3);
	}
	sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + gMasterVolume) / 100);
	FEPrintString(acStack48, 0x98, local_28, 2, 0x80, 0x80, 0x80);
	sprintf(acStack48, (char *)&PTR_DAT_FRNT__001c08f8, (int)(&DAT_00002710 + iVar4) / 100);
	FEPrintString(acStack48, 0x98, local_28, 2, 0, 0, 0);
	DrawSync(0);
	VSync(0);
	PutDispEnv(&current->disp);
	PutDrawEnv(&current->draw);
	pDVar6 = last;
	pDVar5 = current;
	ppcVar1 = &last->primtab;
	current = last;
	last = pDVar5;
	pDVar6->primptr = *ppcVar1;
	DrawOTag(pDVar5->ot + 0x10);
	ClearOTagR(current->ot, 0x10);
	VSync(0);
LAB_FRNT__001c5530:
	SetMasterVolume(gMasterVolume);
	SetXMVolume(gMusicVolume);
	return 0;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayScoreTable()
 // line 4165, offset 0x001c55f8
	/* begin block 1 */
		// Start line: 4167
		// Start offset: 0x001C55F8
		// Variables:
	// 		int offset; // $a2
	// 		int i; // $s4
	// 		char text[32]; // stack offset -80
	// 		struct SCORE_ENTRY *pSE; // stack offset -48
	// 		int min; // $v1
	// 		int frac; // $t0
	/* end block 1 */
	// End offset: 0x001C59A0
	// End Line: 4221

	/* begin block 2 */
		// Start line: 9490
	/* end block 2 */
	// End Line: 9491

	/* begin block 3 */
		// Start line: 9508
	/* end block 3 */
	// End Line: 9509

	/* begin block 4 */
		// Start line: 9509
	/* end block 4 */
	// End Line: 9510

	/* begin block 5 */
		// Start line: 9517
	/* end block 5 */
	// End Line: 9518

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DisplayScoreTable(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	int y;
	int iVar3;
	char acStack80[32];
	SCORE_ENTRY *local_30[2];

	gSubGameNumber = DAT_FRNT__001c6ce8;
	OnScoreTable(local_30);
	sprintf(acStack80, ScreenNames12[ScreenDepth + -1]);
	FEPrintString(acStack80, 0x14, 200, 2, (uint)DAT_FRNT__001c6d00, (uint)DAT_FRNT__001c6d01,
		(uint)DAT_FRNT__001c6d02);
	sprintf(acStack80, (&PTR_s_Chicago_FRNT__001c0910_FRNT__001c6cec)[GameLevel]);
	FEPrintString(acStack80, 0x118, 200, 2, (uint)DAT_FRNT__001c6d00, (uint)DAT_FRNT__001c6d01,
		(uint)DAT_FRNT__001c6d02);
	iVar2 = ((uint)GameType - 4) * 8;
	if ((GameType == GAME_TAKEADRIVE) && (NumPlayers == 2)) {
		iVar2 = 0x30;
	}
	if (GameType == GAME_COPSANDROBBERS) {
		iVar2 = 0x20;
	}
	if (GameType == GAME_CAPTURETHEFLAG) {
		iVar2 = 0x28;
	}
	if ((GameType != GAME_PURSUIT) && (GameType != GAME_SURVIVAL)) {
		sprintf(acStack80, (char *)&PTR_DAT_FRNT__001c0918,
			(&PTR_s_Downtown_FRNT__001c019c_FRNT__001c6774)
			[iVar2 + GameLevel * 2 + DAT_FRNT__001c6ce8]);
		FEPrintStringSized(acStack80, 0x1a4, 0xce, 0xc00, 2, (uint)DAT_FRNT__001c6d00,
			(uint)DAT_FRNT__001c6d01, (uint)DAT_FRNT__001c6d02);
	}
	y = 0xf0;
	iVar2 = 0;
	iVar3 = 4;
	do {
		sprintf(acStack80, local_30[0]->name + iVar2);
		FEPrintString(acStack80, 0x14, y, 2, (uint)DAT_FRNT__001c6cfc, (uint)DAT_FRNT__001c6cfd,
			(uint)DAT_FRNT__001c6cfe);
		if ((GameType == GAME_GATERACE) || (GameType == GAME_TRAILBLAZER)) {
			if (*(short *)((int)&local_30[0]->items + iVar2) != -1) {
				sprintf(acStack80, (char *)&PTR_DAT_FRNT__001c08f8);
				FEPrintString(acStack80, 0x8c, y, 2, (uint)DAT_FRNT__001c6cfc, (uint)DAT_FRNT__001c6cfd,
					(uint)DAT_FRNT__001c6cfe);
			}
		}
		iVar1 = *(int *)((int)&local_30[0]->time + iVar2);
		if (iVar1 != -1) {
			sprintf(acStack80, s__d__02d__02d_FRNT__001c091c, iVar1 / 180000,
				iVar1 / 3000 + (iVar1 / 180000) * -0x3c, (iVar1 % 3000) / 0x1e);
			FEPrintString(acStack80, 0x118, y, 2, (uint)DAT_FRNT__001c6cfc, (uint)DAT_FRNT__001c6cfd,
				(uint)DAT_FRNT__001c6cfe);
		}
		y = y + 0x24;
		iVar3 = iVar3 + -1;
		iVar2 = iVar2 + 0xc;
	} while (-1 < iVar3);
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ ScoreScreen(int bSetup /*$a0*/)
 // line 4227, offset 0x001c59a0
	/* begin block 1 */
		// Start line: 9657
	/* end block 1 */
	// End Line: 9658

	/* begin block 2 */
		// Start line: 9664
	/* end block 2 */
	// End Line: 9665

	/* begin block 3 */
		// Start line: 9666
	/* end block 3 */
	// End Line: 9667

int ScoreScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	if (bSetup != 0) {
		GameLevel = 0;
		DisplayScoreTable();
		DAT_FRNT__001c699c = 1;
		DAT_FRNT__001c6a8c = 0;
		return 0;
	}
	if ((uRam001cc5dc & 0x40) == 0) {
		if ((uRam001cc5dc & 0x10) != 0) {
			DAT_FRNT__001c699c = 0;
			return 0;
		}
		if (((uRam001cc5dc & 0x1000) == 0) && ((uRam001cc5dc & 0x4000) == 0)) {
			return 0;
		}
		DAT_FRNT__001c6a8c = DAT_FRNT__001c6a8c ^ 1;
		return 0;
	}
	if (DAT_FRNT__001c6a8c == 0) {
		if ((GameType != GAME_SURVIVAL) && (GameType != GAME_PURSUIT)) {
			if (DAT_FRNT__001c6ce8 == 1) {
				DAT_FRNT__001c6ce8 = 0;
			}
			else {
				DAT_FRNT__001c6ce8 = 1;
				GameLevel = GameLevel + -1;
				if (GameLevel < 0) {
					GameLevel = 3;
				}
			}
		LAB_FRNT__001c5ab0:
			DisplayScoreTable();
			DAT_FRNT__001c6aa0 = 1;
			return 0;
		}
		GameLevel = GameLevel + -1;
		if (GameLevel < 0) {
			GameLevel = 3;
		}
	}
	else {
		if (((GameType != GAME_SURVIVAL) && (GameType != GAME_PURSUIT)) && (DAT_FRNT__001c6ce8 == 0)) {
			DAT_FRNT__001c6ce8 = 1;
			goto LAB_FRNT__001c5ab0;
		}
		GameLevel = GameLevel + 1;
		if (3 < GameLevel) {
			GameLevel = 0;
		}
	}
	DAT_FRNT__001c6ce8 = 0;
	DisplayScoreTable();
	DAT_FRNT__001c6aa0 = 1;
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ SubtitlesOnOffScreen(int bSetup /*$a0*/)
 // line 4322, offset 0x001c64b0
	/* begin block 1 */
		// Start line: 12820
	/* end block 1 */
	// End Line: 12821

	/* begin block 2 */
		// Start line: 12821
	/* end block 2 */
	// End Line: 12822

/* WARNING: Control flow encountered bad instruction data */

int SubtitlesOnOffScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/* WARNING: Bad instruction - Truncating control flow here */
	//halt_baddata();
}



// decompiled code
// original method signature: 
// int /*$ra*/ CityCutOffScreen(int bSetup /*$a0*/)
 // line 4345, offset 0x001c64fc
	/* begin block 1 */
		// Start line: 12866
	/* end block 1 */
	// End Line: 12867

	/* begin block 2 */
		// Start line: 12867
	/* end block 2 */
	// End Line: 12868

/* WARNING: Control flow encountered bad instruction data */

int CityCutOffScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/* WARNING: Bad instruction - Truncating control flow here */
	//halt_baddata();
}



// decompiled code
// original method signature: 
// int /*$ra*/ ControllerScreen(int bSetup /*$a0*/)
 // line 4378, offset 0x001c6548
	/* begin block 1 */
		// Start line: 12932
	/* end block 1 */
	// End Line: 12933

	/* begin block 2 */
		// Start line: 12933
	/* end block 2 */
	// End Line: 12934

int ControllerScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	if (bSetup == 0) {
		if ((uRam001cc5dc & 0x40) == 0) {
			if ((uRam001cc5dc & 0x10) != 0) {
				DAT_FRNT__001c699c = 0;
				LoadBackgroundFile(s_DATA_GFX_RAW_FRNT__001c07f4);
			}
		}
		else {
			DAT_FRNT__001c6a8c = DAT_FRNT__001c6a8c ^ 1;
			LoadBackgroundFile((&PTR_s_DATA_CARCONT_RAW_FRNT__001c0940_FRNT__001c6d04)[DAT_FRNT__001c6a8c]
			);
			DAT_FRNT__001c6aa0 = 1;
		}
	}
	else {
		DAT_FRNT__001c699c = 1;
		DAT_FRNT__001c6a8c = 0;
		pCurrScreen->numButtons = '\0';
		LoadBackgroundFile((&PTR_s_DATA_CARCONT_RAW_FRNT__001c0940_FRNT__001c6d04)[DAT_FRNT__001c6a8c]);
	}
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ MainScreen(int bSetup /*$a0*/)
 // line 4412, offset 0x001c6614
	/* begin block 1 */
		// Start line: 13006
	/* end block 1 */
	// End Line: 13007

	/* begin block 2 */
		// Start line: 13007
	/* end block 2 */
	// End Line: 13008

int MainScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	if (bSetup != 0) {
		if (DAT_FRNT__001c6ab8 == 2) {
			pCurrScreen->buttons[3].action = 0x106;
		}
		else {
			pCurrScreen->buttons[3].action = 0x300;
		}
	}
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheatScreen(int bSetup /*$a0*/)
 // line 4434, offset 0x001c5b4c
	/* begin block 1 */
		// Start line: 4436
		// Start offset: 0x001C5B4C
		// Variables:
	// 		int numOpen; // $s5
	// 		int i; // $s1
	// 		int k; // $s6
	// 		int *uc; // $s2
	// 		unsigned char cheatOn[12]; // stack offset -104
	// 		int hackLookup1[4]; // stack offset -88
	// 		int hackLookup2[4]; // stack offset -72

		/* begin block 1.1 */
			// Start line: 4473
			// Start offset: 0x001C5C6C
			// Variables:
		// 		int evilRuss[4]; // stack offset -56
		/* end block 1.1 */
		// End offset: 0x001C606C
		// End Line: 4560
	/* end block 1 */
	// End offset: 0x001C60A0
	// End Line: 4568

	/* begin block 2 */
		// Start line: 10082
	/* end block 2 */
	// End Line: 10083

	/* begin block 3 */
		// Start line: 10083
	/* end block 3 */
	// End Line: 10084

	/* begin block 4 */
		// Start line: 10087
	/* end block 4 */
	// End Line: 10088

int CheatScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	PSXSCREEN *pPVar1;
	PSXSCREEN *pPVar2;
	int iVar3;
	int iVar4;
	uint *puVar5;
	int iVar6;
	byte bVar7;
	int iVar8;
	int iVar9;
	byte local_68[16];
	int local_58[4];
	int local_48[4];
	uint local_38[4];

	local_58[0] = DAT_FRNT__001c0954;
	local_58[1] = DAT_FRNT__001c0958;
	local_58[2] = DAT_FRNT__001c095c;
	local_58[3] = DAT_FRNT__001c0960;
	local_48[0] = DAT_FRNT__001c0964;
	local_48[1] = DAT_FRNT__001c0968;
	local_48[2] = DAT_FRNT__001c096c;
	local_48[3] = DAT_FRNT__001c0970;
	if (bSetup == 0) {
		return 0;
	}
	if (gFurthestMission == 0x28) {
		bVar7 = 4;
	}
	else {
		bVar7 = ((byte)AvailableCheats & 1) + ((byte)AvailableCheats >> 1 & 1) +
			((byte)AvailableCheats >> 2 & 1) + ((byte)AvailableCheats >> 3 & 1);
	}
	if (bVar7 == 0) {
		pCurrScreen->buttons[0].u = '\x01';
		pCurrScreen->buttons[0].d = '\x01';
		pCurrScreen->numButtons = '\x01';
		pPVar1 = pCurrScreen;
		pCurrScreen->buttons[0].action = 0x400;
		sprintf(pPVar1->buttons[0].Name, PTR_s_Non_ci_sono_segreti_FRNT__001c01e4_FRNT__001c6874);
		return 0;
	}
	puVar5 = local_38;
	iVar4 = 0;
	pCurrScreen->numButtons = bVar7;
	local_38[0] = (uint)(byte)AvailableCheats & 1;
	local_38[1] = (uint)((byte)AvailableCheats >> 1) & 1;
	local_38[2] = (uint)((byte)AvailableCheats >> 2) & 1;
	local_38[3] = (uint)((byte)AvailableCheats >> 3) & 1;
	iVar3 = 4;
	iVar8 = 0;
	do {
		if ((*puVar5 == 1) || (iVar6 = iVar3, iVar9 = iVar8, gFurthestMission == 0x28)) {
			iVar6 = iVar3 + 0x3c;
			sprintf((char *)((int)&pCurrScreen->buttons[0].var + iVar3),
				(&PTR_s_Non_ci_sono_segreti_FRNT__001c01e4_FRNT__001c6874)[iVar4 + 1]);
			iVar9 = iVar8 + 1;
			local_68[iVar8] = (byte)iVar4;
		}
		pPVar1 = pCurrScreen;
		iVar4 = iVar4 + 1;
		puVar5 = puVar5 + 1;
		iVar3 = iVar6;
		iVar8 = iVar9;
	} while (iVar4 < 4);
	if (bVar7 == 2) {
		pCurrScreen->buttons[0].action = local_58[local_68[0]];
		pPVar1->buttons[1].action = local_58[local_68[1]];
		pPVar1->buttons[0].var = local_48[local_68[0]];
		iVar3 = local_48[local_68[1]];
		pPVar1->buttons[0].d = '\x02';
		pPVar2 = pCurrScreen;
		pPVar1->buttons[1].var = iVar3;
		pPVar2->buttons[0].u = '\x02';
		pCurrScreen->buttons[1].d = '\x01';
		pCurrScreen->buttons[1].u = '\x01';
		DAT_FRNT__001c6a8c = 0;
		return 0;
	}
	if (bVar7 < 3) {
		if (bVar7 == 1) {
			pCurrScreen->buttons[0].action = local_58[local_68[0]];
			iVar3 = local_48[local_68[0]];
			pPVar1->buttons[0].d = '\x01';
			pPVar2 = pCurrScreen;
			pPVar1->buttons[0].var = iVar3;
			pPVar2->buttons[0].u = '\x01';
			DAT_FRNT__001c6a8c = 0;
			return 0;
		}
	}
	else {
		if (bVar7 == 3) {
			pCurrScreen->buttons[0].action = local_58[local_68[0]];
			pPVar1->buttons[1].action = local_58[local_68[1]];
			pPVar1->buttons[2].action = local_58[local_68[2]];
			pPVar1->buttons[0].var = local_48[local_68[0]];
			pPVar1->buttons[1].var = local_48[local_68[1]];
			iVar3 = local_48[local_68[2]];
			pPVar1->buttons[0].d = '\x02';
			pPVar2 = pCurrScreen;
			pPVar1->buttons[2].var = iVar3;
			pPVar2->buttons[0].u = '\x03';
			pCurrScreen->buttons[1].d = '\x03';
			pCurrScreen->buttons[1].u = '\x01';
			pCurrScreen->buttons[2].d = '\x01';
			pCurrScreen->buttons[2].u = '\x02';
			DAT_FRNT__001c6a8c = 0;
			return 0;
		}
		if (bVar7 == 4) {
			pCurrScreen->buttons[0].action = local_58[local_68[0]];
			pPVar1->buttons[1].action = local_58[local_68[1]];
			pPVar1->buttons[2].action = local_58[local_68[2]];
			pPVar1->buttons[3].action = local_58[local_68[3]];
			pPVar1->buttons[0].var = local_48[local_68[0]];
			pPVar1->buttons[1].var = local_48[local_68[1]];
			pPVar1->buttons[2].var = local_48[local_68[2]];
			iVar3 = local_48[local_68[3]];
			pPVar1->buttons[0].d = '\x02';
			pPVar2 = pCurrScreen;
			pPVar1->buttons[3].var = iVar3;
			pPVar2->buttons[0].u = '\x04';
			pCurrScreen->buttons[1].d = '\x03';
			pCurrScreen->buttons[1].u = '\x01';
			pCurrScreen->buttons[2].d = '\x04';
			pCurrScreen->buttons[2].u = '\x02';
			pCurrScreen->buttons[3].d = '\x01';
			pCurrScreen->buttons[3].u = '\x03';
			DAT_FRNT__001c6a8c = 0;
			return 0;
		}
	}
	pCurrScreen->numButtons = '\0';
	DAT_FRNT__001c6a8c = 0;
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ ImmunityOnOffScreen(int bSetup /*$a0*/)
 // line 4575, offset 0x001c6654
	/* begin block 1 */
		// Start line: 13332
	/* end block 1 */
	// End Line: 13333

	/* begin block 2 */
		// Start line: 13333
	/* end block 2 */
	// End Line: 13334

/* WARNING: Control flow encountered bad instruction data */

int ImmunityOnOffScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/* WARNING: Bad instruction - Truncating control flow here */
	//halt_baddata();
}



// decompiled code
// original method signature: 
// int /*$ra*/ InvincibleOnOffScreen(int bSetup /*$a0*/)
 // line 4597, offset 0x001c66a0
	/* begin block 1 */
		// Start line: 13376
	/* end block 1 */
	// End Line: 13377

	/* begin block 2 */
		// Start line: 13377
	/* end block 2 */
	// End Line: 13378

/* WARNING: Control flow encountered bad instruction data */

int InvincibleOnOffScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/* WARNING: Bad instruction - Truncating control flow here */
	//halt_baddata();
}



// decompiled code
// original method signature: 
// int /*$ra*/ GamePlayScreen(int bSetup /*$a0*/)
 // line 4619, offset 0x001c66ec
	/* begin block 1 */
		// Start line: 13420
	/* end block 1 */
	// End Line: 13421

	/* begin block 2 */
		// Start line: 13421
	/* end block 2 */
	// End Line: 13422

int GamePlayScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*

	int iVar1;

	if (bSetup != 0) {
		if (DAT_FRNT__001c6ab4 == 0) {
			iVar1 = 0x300;
		}
		else {
			iVar1 = 0x111;
		}
		pCurrScreen->buttons[2].action = iVar1;
	}
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ GameNameScreen(int bSetup /*$a0*/)
 // line 4642, offset 0x001c60a0
	/* begin block 1 */
		// Start line: 4644
		// Start offset: 0x001C60A0
		// Variables:
	// 		int offset; // $s3
	/* end block 1 */
	// End offset: 0x001C61AC
	// End Line: 4656

	/* begin block 2 */
		// Start line: 10496
	/* end block 2 */
	// End Line: 10497

	/* begin block 3 */
		// Start line: 10571
	/* end block 3 */
	// End Line: 10572

	/* begin block 4 */
		// Start line: 10572
	/* end block 4 */
	// End Line: 10573

	/* begin block 5 */
		// Start line: 10573
	/* end block 5 */
	// End Line: 10574

int GameNameScreen(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	if (bSetup != 0) {
		iVar1 = ((uint)GameType - 4) * 8;
		if ((GameType == GAME_TAKEADRIVE) && (NumPlayers == 2)) {
			iVar1 = 0x30;
		}
		if (GameType == GAME_COPSANDROBBERS) {
			iVar1 = 0x20;
		}
		if (GameType == GAME_CAPTURETHEFLAG) {
			iVar1 = 0x28;
		}
		if ((GameType == GAME_CHECKPOINT) && (NumPlayers == 2)) {
			iVar1 = 0x38;
		}
		sprintf(pCurrScreen->buttons[0].Name,
			(&PTR_s_Downtown_FRNT__001c019c_FRNT__001c6774)[iVar1 + GameLevel * 2]);
		sprintf(pCurrScreen->buttons[1].Name,
			(&PTR_s_Downtown_FRNT__001c019c_FRNT__001c6774)[iVar1 + GameLevel * 2 + 1]);
	}
	return 0;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ FEInitCdIcon()
 // line 4671, offset 0x001c61ac
	/* begin block 1 */
		// Start line: 4673
		// Start offset: 0x001C61AC
		// Variables:
	// 		int i; // $a0
	// 		struct RECT dest; // stack offset -24
	// 		unsigned short *palette; // $a2
	/* end block 1 */
	// End offset: 0x001C62F8
	// End Line: 4709

	/* begin block 2 */
		// Start line: 10614
	/* end block 2 */
	// End Line: 10615

	/* begin block 3 */
		// Start line: 10630
	/* end block 3 */
	// End Line: 10631

	/* begin block 4 */
		// Start line: 10631
	/* end block 4 */
	// End Line: 10632

	/* begin block 5 */
		// Start line: 10633
	/* end block 5 */
	// End Line: 10634

/* WARNING: Unknown calling convention yet parameter storage is locked */

void FEInitCdIcon(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	ushort *puVar2;
	undefined2 local_18;
	undefined2 local_16;
	undefined2 local_14;
	undefined2 local_12;

	puVar2 = &DAT_0009bb88;
	iVar1 = 0xd;
	do {
		iVar1 = iVar1 + -1;
		*puVar2 = *puVar2 & 0x7fff;
		puVar2 = puVar2 + 1;
	} while (-1 < iVar1);
	DAT_0009bb88 = 0;
	local_18 = 0x3c0;
	local_16 = 0x1b2;
	local_14 = 8;
	local_12 = 0x20;
	DAT_0009bba4 = DAT_0009bba4 | 0x8000;
	DAT_0009bba6 = DAT_0009bba6 | 0x8000;
	LoadImage(&local_18, &DAT_0009bba4);
	DAT_FRNT__001c6d23 = 9;
	DAT_FRNT__001c6d24 = 0x80;
	DAT_FRNT__001c6d25 = 0x80;
	DAT_FRNT__001c6d26 = 0x80;
	DAT_FRNT__001c6d2d = 0xb3;
	DAT_FRNT__001c6d35 = 0xb3;
	DAT_FRNT__001c6d27 = 0x2e;
	DAT_FRNT__001c6d2c = 0;
	DAT_FRNT__001c6d34 = 0x20;
	DAT_FRNT__001c6d3c = 0;
	DAT_FRNT__001c6d3d = 0xd3;
	DAT_FRNT__001c6d44 = 0x20;
	DAT_FRNT__001c6d45 = 0xd3;
	DAT_FRNT__001c6d2e = GetClut(0x3c0, 0x1b1);
	DAT_FRNT__001c6d36 = GetTPage(0, 0, 0x3c0, 0x100);
	DAT_FRNT__001c6ac8 = 1;
	DAT_FRNT__001c6d28 = 0x50;
	DAT_FRNT__001c6d2a = 0x26;
	DAT_FRNT__001c6d30 = 0x76;
	DAT_FRNT__001c6d32 = 0x26;
	DAT_FRNT__001c6d38 = 0x50;
	DAT_FRNT__001c6d3a = 0x3b;
	DAT_FRNT__001c6d40 = 0x76;
	DAT_FRNT__001c6d42 = 0x3b;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ FEDrawCDicon()
 // line 4716, offset 0x001c62f8
	/* begin block 1 */
		// Start line: 4718
		// Start offset: 0x001C62F8
		// Variables:
	// 		unsigned short *palette; // $a1
	// 		int temp; // $a2
	// 		int i; // $a0
	// 		struct RECT dest; // stack offset -16
	/* end block 1 */
	// End offset: 0x001C6378
	// End Line: 4735

	/* begin block 2 */
		// Start line: 10758
	/* end block 2 */
	// End Line: 10759

	/* begin block 3 */
		// Start line: 10766
	/* end block 3 */
	// End Line: 10767

	/* begin block 4 */
		// Start line: 10767
	/* end block 4 */
	// End Line: 10768

/* WARNING: Unknown calling convention yet parameter storage is locked */

void FEDrawCDicon(void)
{
	UNIMPLEMENTED();
	/*
	undefined2 *puVar1;
	int iVar2;
	undefined2 local_10;
	undefined2 local_e;
	undefined2 local_c;
	undefined2 local_a;

	DAT_0009bba2 = DAT_0009bb8a;
	iVar2 = 0xb;
	puVar1 = &DAT_0009bb88;
	do {
		iVar2 = iVar2 + -1;
		puVar1[1] = puVar1[2];
		puVar1 = puVar1 + 1;
	} while (-1 < iVar2);
	local_10 = 0x3c0;
	local_e = 0x1b1;
	local_c = 0x10;
	local_a = 1;
	LoadImage(&local_10);
	DrawPrim(&DAT_FRNT__001c6d20);
	DrawSync(0);
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheatNumlayerSelect(int bSetup /*$a0*/)
 // line 4742, offset 0x001c6724
	/* begin block 1 */
		// Start line: 13666
	/* end block 1 */
	// End Line: 13667

	/* begin block 2 */
		// Start line: 13667
	/* end block 2 */
	// End Line: 13668

/* WARNING: Control flow encountered bad instruction data */

int CheatNumlayerSelect(int bSetup)
{
	UNIMPLEMENTED();
	return 0;
	/* WARNING: Bad instruction - Truncating control flow here */
	//halt_baddata();
}





