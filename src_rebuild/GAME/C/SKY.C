#include "THISDUST.H"
#include "SKY.H"

int sky_y_offset[4] = { 14, 14, 14, 14 };

unsigned char HorizonLookup[4][4] = {
	{0, 0, 0x14, 0x14},
	{0x14, 0x14, 0, 0},
	{0, 0, 0x14, 0x14},
	{0, 0, 0x14, 0x14},
};

unsigned char HorizonTextures[40] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB,
	0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13,
	0, 1, 2, 3, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1A, 0x1B, 0x10, 0x11, 0x12, 0x13
};

SVECTOR sun_position[4] =
{
	{ 33536, 54536, 60536, 0 },
	{ 33536, 54536, 60536, 0 },
	{ 33536, 54536, 60536, 0 },
	{ 33536, 54536, 60536, 0 }
};

SVECTOR moon_position[4] =
{
	{ 33536, 54036, 47536, 0 },
	{ 33536, 54036, 47536, 0 },
	{ 33536, 54036, 47536, 0 },
	{ 33536, 54036, 47536, 0 }
};

SVECTOR moon_shadow_position[4] =
{
	{ 33536, 54036, 47536, 0 },
	{ 33536, 54036, 47536, 0 },
	{ 33536, 54036, 47536, 0 },
	{ 33536, 10500, 47536, 0 }
};

FLAREREC flare_info[8] =
{
	{ { 0, 0, 90, 0 }, '\x10', 12288 },
	{ { 20480, 10240, 1024, 0 }, '\0', 48 },
	{ { 72, 90, 0, 0 }, '\0', 12288 },
	{ { 24576, 0, 23040, 0 }, '\0', 0 },
	{ { 16, 144, 0, 0 }, 'Z', 0 },
	{ { 16384, 40960, 23040, 23040 }, '\0', 0 },
	{ { 0, 32, 184, 90 }, '\0', 0 },
	{ { 0, 8192, 53248, 0 }, '\0', 0 }
};

VECTOR tunnelPos[3][2] =
{
	{
		{ 4294568646, 0, 4294806296, 0 },
		{ 4294626996, 2000, 4294864296, 0 }
	},
	{
		{ 272800, 0, 41200, 0 },
		{ 271963, 2000, 168187, 0 }
	},

	{
		{ 4294852196, 0, 4294774096, 0 },
		{ 4294853996, 4294966896, 4294834796, 0 }
	}
};


// decompiled code
// original method signature: 
// void /*$ra*/ LoadSky()
 // line 145, offset 0x000775c8
	/* begin block 1 */
		// Start line: 147
		// Start offset: 0x000775C8
		// Variables:
	// 		struct RECT rect; // stack offset -96
	// 		char name[16]; // stack offset -88
	// 		int x; // $s6
	// 		int y; // $a1
	// 		int i; // $t1
	// 		int u; // $v1
	// 		int v; // $s2
	// 		int skynum; // $a2
	// 		int offset; // stack offset -72

		/* begin block 1.1 */
			// Start line: 156
			// Start offset: 0x00077608
			// Variables:
		// 		int flipped; // $t0
		// 		int single; // $s5
		// 		int ry; // $a2
		/* end block 1.1 */
		// End offset: 0x000777D0
		// End Line: 258
	/* end block 1 */
	// End offset: 0x0007795C
	// End Line: 319

	/* begin block 2 */
		// Start line: 290
	/* end block 2 */
	// End Line: 291

	/* begin block 3 */
		// Start line: 291
	/* end block 3 */
	// End Line: 292

	/* begin block 4 */
		// Start line: 294
	/* end block 4 */
	// End Line: 295

/* WARNING: Unknown calling convention yet parameter storage is locked */

void LoadSky(void)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	uchar uVar2;
	uchar uVar3;
	u_short uVar4;
	uchar uVar5;
	int iVar6;
	undefined4 uVar7;
	int iVar8;
	UV *pUVar9;
	uchar *puVar10;
	uchar uVar11;
	int iVar12;
	uint uVar13;
	int x;
	undefined2 local_60;
	undefined2 local_5e;
	undefined2 local_5c;
	undefined2 local_5a;
	char acStack88[16];
	int local_48;
	uint local_44;
	uint local_40;
	int local_3c;
	char *local_38;
	int local_30;
	int local_2c;

	iVar8 = 0;
	local_40 = 0;
	local_38 = acStack88;
	local_48 = 0;
	bVar1 = true;
	do {
		if (!bVar1) {
		switchD_00077628_caseD_0:
			iVar6 = 0;
			local_30 = 0;
			bVar1 = true;
			goto LAB_00077680;
		}
		switch (local_40) {
		default:
			goto switchD_00077628_caseD_0;
		case 1:
			iVar6 = 0;
			local_30 = 0;
			break;
		case 2:
			iVar6 = 1;
			local_30 = 0;
			break;
		case 3:
			iVar6 = 1;
			goto LAB_00077678;
		case 4:
			iVar6 = 0;
			goto LAB_00077678;
		case 5:
			iVar6 = 2;
			local_30 = 0;
			break;
		case 6:
			iVar6 = 2;
		LAB_00077678:
			local_30 = 1;
		}
		bVar1 = false;
	LAB_00077680:
		iVar12 = 0;
		local_3c = iVar6 + 0xfc;
		local_40 = local_40 + 1;
		x = 0x140;
		uVar13 = 0x140;
		pUVar9 = skytexuv + iVar8;
		local_44 = iVar6 * 0x54;
		uVar2 = (uchar)local_44;
		uVar11 = uVar2 + 'S';
		puVar10 = &skytexuv[0].u0 + (iVar8 * 8 | 6);
		do {
			uVar5 = (char)iVar12 * -0x80;
			if (bVar1) {
				pUVar9->u0 = uVar5;
				pUVar9->v0 = uVar2;
				pUVar9->u1 = uVar5;
				pUVar9->v1 = uVar2;
				pUVar9->u2 = uVar5;
				puVar10[-1] = uVar2;
				*puVar10 = uVar5;
			LAB_00077748:
				pUVar9->v3 = uVar2;
			}
			else {
				uVar3 = uVar5 + '\x7f';
				if (local_30 != 0) {
					pUVar9->u0 = uVar5;
					pUVar9->v0 = uVar11;
					pUVar9->u1 = uVar3;
					pUVar9->v1 = uVar11;
					pUVar9->u2 = uVar5;
					puVar10[-1] = uVar2;
					*puVar10 = uVar3;
					goto LAB_00077748;
				}
				pUVar9->u0 = uVar5;
				pUVar9->v0 = uVar2;
				pUVar9->u1 = uVar3;
				pUVar9->v1 = uVar2;
				pUVar9->u2 = uVar5;
				puVar10[-1] = uVar11;
				*puVar10 = uVar3;
				pUVar9->v3 = uVar11;
			}
			local_2c = iVar8;
			uVar4 = GetTPage(0, 0, uVar13 & 0xffffffc0, local_44 & 0x300);
			iVar8 = local_2c;
			skytpage[local_2c] = uVar4;
			uVar4 = GetClut(x, local_3c);
			pUVar9 = pUVar9 + 1;
			puVar10 = puVar10 + 8;
			x = x + 0x10;
			uVar13 = uVar13 + 0x20;
			iVar12 = iVar12 + 1;
			skyclut[iVar8] = uVar4;
			iVar8 = local_2c + 1;
		} while (iVar12 < 4);
		bVar1 = local_40 < 7;
	} while ((int)local_40 < 7);
	if (GameLevel == 1) {
		uVar7 = 1;
	}
	else {
		uVar7 = 0;
		if (1 < GameLevel) {
			if (GameLevel == 2) {
				uVar7 = 2;
			}
			else {
				if (GameLevel == 3) {
					uVar7 = 3;
				}
			}
		}
	}
	if (gWeather - 1U < 2) {
		local_48 = 0x20000;
		iVar8 = local_48;
		if (gTimeOfDay == 3) {
			local_48 = 0x10000;
			iVar8 = local_48;
		}
	}
	else {
		if (gTimeOfDay == 1) {
			local_48 = 0;
			iVar8 = local_48;
		}
		else {
			if (gTimeOfDay < 2) {
				if (gTimeOfDay != 0) goto LAB_000778d4;
				local_48 = 0x30000;
				iVar8 = local_48;
			}
			else {
				if (gTimeOfDay == 2) {
					iVar8 = 0x40000;
				}
				else {
					iVar8 = 0x10000;
					if (gTimeOfDay != 3) goto LAB_000778d4;
				}
			}
		}
	}
	local_48 = iVar8;
LAB_000778d4:
	sprintf(local_38, s_DATA_SKY_d_RAW_00011cf4, uVar7);
	LoadfileSeg(local_38, &DAT_000fb400, local_48, 0x10000);
	local_60 = 0x140;
	local_5e = 0;
	local_5c = 0x80;
	local_5a = 0x100;
	LoadImage(&local_60, &DAT_000fb400);
	DrawSync(0);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSkyDome()
 // line 327, offset 0x0007795c
	/* begin block 1 */
		// Start line: 852
	/* end block 1 */
	// End Line: 853

	/* begin block 2 */
		// Start line: 861
	/* end block 2 */
	// End Line: 862

	/* begin block 3 */
		// Start line: 862
	/* end block 3 */
	// End Line: 863

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DrawSkyDome(void)
{
	UNIMPLEMENTED();
	/*
	calc_sky_brightness();
	if (0x8ca < (uint)(ushort)camera_angle.vy - 0x5aa) {
		PlotHorizonMDL(modelpointers1536[0], (uint)(&HorizonLookup)[GameLevel * 4]);
	}
	if ((uint)(ushort)camera_angle.vy - 0x28b < 0x707) {
		PlotHorizonMDL(modelpointers1536[2], (uint)(&UCHAR_00h_000a18ed)[GameLevel * 4]);
	}
	if ((uint)(ushort)camera_angle.vy - 0x6a5 < 0x6d5) {
		PlotHorizonMDL(modelpointers1536[3], (uint)(&UCHAR_14h_000a18ee)[GameLevel * 4]);
	}
	if (0x8fc < (uint)(ushort)camera_angle.vy - 400) {
		PlotHorizonMDL(modelpointers1536[1], (uint)(&UCHAR_14h_000a18ef)[GameLevel * 4]);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawLensFlare()
 // line 351, offset 0x00077a8c
	/* begin block 1 */
		// Start line: 353
		// Start offset: 0x00077A8C
		// Variables:
	// 		static char last_attempt_failed; // offset 0x0
	// 		static short buffer[160]; // offset 0x0
	// 		struct DVECTOR sun_pers_conv_position; // stack offset -64
	// 		struct RECT source; // stack offset -56
	// 		struct DR_MOVE *sample_sun; // $s0
	// 		int distance_to_sun; // $s0
	// 		int xpos; // $t1
	// 		int ypos; // $v0
	// 		int xgap; // $s4
	// 		int ygap; // $s2
	// 		int flarez; // stack offset -40
	// 		int shade; // $t4
	// 		int sun_intensity; // $s3
	// 		struct POLY_FT4 *polys; // $a1
	// 		struct CVECTOR col; // stack offset -48
	// 		int r; // $a2
	// 		int g; // $a3
	// 		int b; // $a0

		/* begin block 1.1 */
			// Start line: 387
			// Start offset: 0x00077B58
			// Variables:
		// 		int bufferX; // $a0
		// 		int bufferY; // $v1
		// 		unsigned short *pwBuffer; // $s0
		/* end block 1.1 */
		// End offset: 0x00077BC0
		// End Line: 405

		/* begin block 1.2 */
			// Start line: 446
			// Start offset: 0x00077D34
			// Variables:
		// 		int temp; // $v0

			/* begin block 1.2.1 */
				// Start line: 458
				// Start offset: 0x00077DD0
				// Variables:
			// 		struct FLAREREC *pFlareInfo; // $t3
			// 		int flaresize; // $t0
			/* end block 1.2.1 */
			// End offset: 0x00077FAC
			// End Line: 495
		/* end block 1.2 */
		// End offset: 0x00077FAC
		// End Line: 496
	/* end block 1 */
	// End offset: 0x00078098
	// End Line: 518

	/* begin block 2 */
		// Start line: 909
	/* end block 2 */
	// End Line: 910

	/* begin block 3 */
		// Start line: 910
	/* end block 3 */
	// End Line: 911

	/* begin block 4 */
		// Start line: 923
	/* end block 4 */
	// End Line: 924

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DrawLensFlare(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	DB *pDVar5;
	undefined4 in_zero;
	undefined4 in_at;
	short sVar6;
	int iVar7;
	int iVar8;
	uint *puVar9;
	FLAREREC *pFVar10;
	short *psVar11;
	short *psVar12;
	int flare_col;
	int iVar13;
	short sVar15;
	short sVar16;
	int iVar14;
	DVECTOR local_40[2];
	undefined4 local_38;
	undefined4 local_34;
	CVECTOR local_30[2];
	int local_28;

	local_38 = DAT_000aa928;
	local_34 = DAT_000aa92c;
	if (((1 < gWeather - 1U) && (gTimeOfDay != 0)) && (gTimeOfDay != 2)) {
		local_30[0].r = -1;
		if (gTimeOfDay == 3) {
			local_30[0].r = -0x80;
		}
		flare_col = 0;
		local_30[0].g = local_30[0].r;
		local_30[0].b = local_30[0].r;
		if ((gTimeOfDay != 3) && (last_attempt_failed_9 == '\0')) {
			psVar11 = &buffer_10;
			StoreImage(&local_38, &buffer_10);
			iVar7 = 0;
			do {
				iVar7 = iVar7 + 1;
				iVar8 = 0xb;
				do {
					psVar12 = psVar11;
					if ((*psVar12 == -1) || (*psVar12 == 0x7fff)) {
						flare_col = flare_col + 1;
					}
					iVar8 = iVar8 + -1;
					psVar11 = psVar12 + 1;
				} while (-1 < iVar8);
				psVar11 = psVar12 + 5;
			} while (iVar7 < 10);
		}
		setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
		setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
		setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
		setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
		setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
		setCopControlWord(2, 0x2800, dummy.vx);
		setCopControlWord(2, 0x3000, dummy.vy);
		setCopControlWord(2, 0x3800, dummy.vz);
		if (gTimeOfDay == 3) {
			setCopReg(2, in_zero, *(undefined4 *)(moon_position + GameLevel));
			setCopReg(2, in_at, *(undefined4 *)&moon_position[GameLevel].vz);
		}
		else {
			setCopReg(2, in_zero, *(undefined4 *)(sun_position + GameLevel));
			setCopReg(2, in_at, *(undefined4 *)&sun_position[GameLevel].vz);
		}
		copFunction(2, 0x180001);
		local_40[0] = getCopReg(2, 0xe);
		local_28 = getCopReg(2, 0x13);
		iVar13 = (int)local_40[0].vx + -0xa0;
		local_40[0].vy = (short)((uint)local_40[0] >> 0x10);
		iVar8 = (int)local_40[0].vy + -0x80;
		iVar7 = SquareRoot0(iVar13 * iVar13 + iVar8 * iVar8);
		if (gTimeOfDay == 3) {
			if (iVar7 < 500) {
				DisplayMoon(local_40, local_30, 0);
				local_30[0].r = '@';
				local_30[0].b = '@';
				local_30[0].g = '@';
				setCopReg(2, in_zero, *(undefined4 *)(moon_shadow_position + GameLevel));
				setCopReg(2, in_at, *(undefined4 *)&moon_shadow_position[GameLevel].vz);
				copFunction(2, 0x180001);
				local_40[0] = getCopReg(2, 0xe);
				DisplayMoon(local_40, local_30, 1);
			}
		}
		else {
			if ((0 < local_28) && (iVar7 < 500)) {
				DisplaySun(local_40, local_30, flare_col);
				iVar14 = (0x3c - (iVar7 >> 1)) * flare_col;
				add_haze((iVar14 / 6 + (iVar14 >> 0x1f) >> 3) - (iVar14 >> 0x1f), iVar14 >> 6, 7);
				iVar7 = flare_col / 3 - (iVar7 * 0x50) / 500;
				if ((-1 < iVar7) && (flare_col != 0)) {
					pFVar10 = flare_info;
					do {
						flare_col = (0x80 - (int)pFVar10->gapmod) * 2;
						iVar14 = iVar13 * flare_col;
						sVar15 = (short)((uint)iVar14 >> 8);
						flare_col = iVar8 * flare_col;
						sVar16 = (short)((uint)flare_col >> 8);
						if (iVar14 < 0) {
							sVar15 = (short)((uint)(iVar14 + 0xff) >> 8);
						}
						if (flare_col < 0) {
							sVar16 = (short)((uint)(flare_col + 0xff) >> 8);
						}
						bVar1 = pFVar10->size;
						puVar9 = (uint *)current->primptr;
						*(char *)((int)puVar9 + 3) = '\t';
						*(char *)((int)puVar9 + 7) = '.';
						sVar2 = (pFVar10->transparency).r;
						sVar3 = (pFVar10->transparency).g;
						sVar6 = (short)((int)(uint)bVar1 >> 1);
						sVar4 = (sVar15 + 0xa0) - sVar6;
						sVar6 = (sVar16 + 0x80) - sVar6;
						sVar15 = (pFVar10->transparency).b;
						*(short *)((int)puVar9 + 10) = sVar6;
						*(short *)((int)puVar9 + 0x12) = sVar6;
						*(short *)(puVar9 + 2) = sVar4;
						*(ushort *)(puVar9 + 4) = sVar4 + (ushort)bVar1;
						*(short *)(puVar9 + 6) = sVar4;
						*(short *)((int)puVar9 + 0x1a) = sVar6 + (ushort)bVar1;
						*(ushort *)(puVar9 + 8) = sVar4 + (ushort)bVar1;
						*(short *)((int)puVar9 + 0x22) = sVar6 + (ushort)bVar1;
						*(char *)(puVar9 + 1) = (char)(sVar2 * iVar7 >> 6);
						*(char *)((int)puVar9 + 5) = (char)(sVar3 * iVar7 >> 6);
						*(char *)((int)puVar9 + 6) = (char)(sVar15 * iVar7 >> 6);
						*(uchar *)(puVar9 + 3) = lensflare_texture.coords.u0;
						*(uchar *)((int)puVar9 + 0xd) = lensflare_texture.coords.v0;
						*(uchar *)(puVar9 + 5) = lensflare_texture.coords.u1;
						*(uchar *)((int)puVar9 + 0x15) = lensflare_texture.coords.v1;
						*(uchar *)(puVar9 + 7) = lensflare_texture.coords.u2;
						*(char *)((int)puVar9 + 0x1d) = lensflare_texture.coords.v2 + -4;
						*(uchar *)(puVar9 + 9) = lensflare_texture.coords.u3;
						*(char *)((int)puVar9 + 0x25) = lensflare_texture.coords.v3 + -4;
						*(ushort *)((int)puVar9 + 0xe) = lensflare_texture.clutid;
						pDVar5 = current;
						*(ushort *)((int)puVar9 + 0x16) = lensflare_texture.tpageid | 0x20;
						*puVar9 = *puVar9 & 0xff000000 | pDVar5->ot[10] & 0xffffff;
						pFVar10 = pFVar10 + 1;
						pDVar5->ot[10] = pDVar5->ot[10] & 0xff000000 | (uint)puVar9 & 0xffffff;
						pDVar5->primptr = pDVar5->primptr + 0x28;
					} while (pFVar10 < &tunnelDir);
				}
			}
			local_40[0].vx = local_40[0].vx + -8;
			local_40[0].vy = local_40[0].vy + -4;
			if (-1 < (int)local_40[0].vx) {
				if (((-1 < (int)local_40[0].vy) && ((int)local_40[0].vx + 0x10 < 0x141)) &&
					((int)local_40[0].vy + 10 < 0x101)) {
					last_attempt_failed_9 = 0;
					local_38 = CONCAT22(local_40[0].vy + (last->disp).disp.y, local_40[0].vx);
					puVar9 = (uint *)current->primptr;
					SetDrawMove(puVar9, &local_38, 0x3f0, 0x1c8);
					pDVar5 = current;
					*puVar9 = *puVar9 & 0xff000000 | current->ot[0x20] & 0xffffff;
					pDVar5->ot[0x20] = pDVar5->ot[0x20] & 0xff000000 | (uint)puVar9 & 0xffffff;
					pDVar5->primptr = pDVar5->primptr + 0x18;
					return;
				}
			}
			last_attempt_failed_9 = '\x01';
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplaySun(struct DVECTOR *pos /*$a0*/, struct CVECTOR *col /*$a1*/, int flare_col /*$a2*/)
 // line 527, offset 0x000780bc
	/* begin block 1 */
		// Start line: 528
		// Start offset: 0x000780BC
		// Variables:
	// 		struct POLY_FT4 *polys; // $a1
	// 		struct POLY_FT3 *null; // $a3
	// 		struct VECTOR output; // stack offset -32
	// 		int width; // $t5
	// 		int height; // $t4
	/* end block 1 */
	// End offset: 0x00078544
	// End Line: 600

	/* begin block 2 */
		// Start line: 1431
	/* end block 2 */
	// End Line: 1432

	/* begin block 3 */
		// Start line: 1452
	/* end block 3 */
	// End Line: 1453

void DisplaySun(DVECTOR *pos, CVECTOR *col, int flare_col)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	int iVar3;
	DB *pDVar4;
	char cVar5;
	uint *puVar6;
	uint uVar7;
	uint uVar8;
	uint uVar9;
	uint uVar10;
	char *pcVar11;
	short local_20;
	short local_1c;

	uVar7 = (uint)sun_texture.coords.u1;
	uVar9 = (uint)sun_texture.coords.u0;
	uVar8 = (uint)sun_texture.coords.v2;
	uVar10 = (uint)sun_texture.coords.v0;
	puVar6 = (uint *)current->primptr;
	*(char *)((int)puVar6 + 3) = '\a';
	*(char *)((int)puVar6 + 7) = '$';
	pDVar4 = current;
	*(undefined2 *)(puVar6 + 2) = 0xffff;
	*(undefined2 *)((int)puVar6 + 10) = 0xffff;
	*(undefined2 *)(puVar6 + 4) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x12) = 0xffff;
	*(undefined2 *)(puVar6 + 6) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x1a) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x16) = 0;
	*puVar6 = *puVar6 & 0xff000000 | pDVar4->ot[0x1079] & 0xffffff;
	pDVar4->ot[0x1079] = pDVar4->ot[0x1079] & 0xff000000 | (uint)puVar6 & 0xffffff;
	pcVar11 = pDVar4->primptr;
	pDVar4->primptr = pcVar11 + 0x20;
	pcVar11[0x23] = '\t';
	pcVar11[0x27] = ',';
	pcVar11[0x24] = col->r;
	pcVar11[0x25] = col->g;
	pcVar11[0x26] = col->b;
	pcVar11[0x27] = '.';
	sVar1 = (short)(((int)(uVar7 - (uVar9 - 1)) / 2) * 3 >> 2);
	*(short *)(pcVar11 + 0x28) = pos->vx - sVar1;
	sVar2 = (short)(((int)(uVar8 - (uVar10 - 1)) / 2) * 3 >> 2);
	*(short *)(pcVar11 + 0x2a) = pos->vy - sVar2;
	*(short *)(pcVar11 + 0x30) = pos->vx + sVar1;
	*(short *)(pcVar11 + 0x32) = pos->vy - sVar2;
	*(short *)(pcVar11 + 0x38) = pos->vx - sVar1;
	*(short *)(pcVar11 + 0x3a) = pos->vy + sVar2;
	*(short *)(pcVar11 + 0x40) = pos->vx + sVar1;
	*(short *)(pcVar11 + 0x42) = pos->vy + sVar2;
	pcVar11[0x2c] = sun_texture.coords.u0;
	pcVar11[0x2d] = sun_texture.coords.v0;
	pcVar11[0x34] = sun_texture.coords.u1;
	pcVar11[0x35] = sun_texture.coords.v1;
	pcVar11[0x3c] = sun_texture.coords.u2;
	pcVar11[0x3d] = sun_texture.coords.v2;
	pcVar11[0x44] = sun_texture.coords.u3;
	pcVar11[0x45] = sun_texture.coords.v3;
	*(ushort *)(pcVar11 + 0x2e) = sun_texture.clutid;
	pDVar4 = current;
	*(ushort *)(pcVar11 + 0x36) = sun_texture.tpageid | 0x20;
	*(uint *)(pcVar11 + 0x20) = *(uint *)(pcVar11 + 0x20) & 0xff000000 | pDVar4->ot[0x1079] & 0xffffff
		;
	pDVar4->ot[0x1079] = pDVar4->ot[0x1079] & 0xff000000 | (uint)(pcVar11 + 0x20) & 0xffffff;
	pDVar4->primptr = pDVar4->primptr + 0x28;
	sVar1 = rcossin_tbl[((uint)(ushort)camera_angle.vy & 0x1ffe) + 1];
	sVar2 = rcossin_tbl[(uint)(ushort)camera_angle.vy & 0x1ffe];
	iVar3 = -(((int)((uint)flare_texture.coords.u1 - ((uint)flare_texture.coords.u0 - 1)) / 2) * 3 >>
		2);
	puVar6 = (uint *)pDVar4->primptr;
	*(char *)((int)puVar6 + 3) = '\t';
	*(char *)((int)puVar6 + 7) = '.';
	cVar5 = (char)(flare_col >> 1);
	*(char *)(puVar6 + 1) = cVar5;
	*(char *)((int)puVar6 + 5) = cVar5;
	*(char *)((int)puVar6 + 6) = (char)(flare_col >> 2);
	local_20 = (short)(((int)sVar1 - (int)sVar2) * iVar3 >> 0xc);
	*(short *)(puVar6 + 2) = pos->vx + local_20;
	local_1c = (short)(((int)sVar2 + (int)sVar1) * iVar3 >> 0xc);
	*(short *)((int)puVar6 + 10) = pos->vy + local_1c;
	*(short *)(puVar6 + 4) = pos->vx - local_1c;
	*(short *)((int)puVar6 + 0x12) = pos->vy + local_20;
	*(short *)(puVar6 + 6) = pos->vx + local_1c;
	*(short *)((int)puVar6 + 0x1a) = pos->vy - local_20;
	*(short *)(puVar6 + 8) = pos->vx - local_20;
	*(short *)((int)puVar6 + 0x22) = pos->vy - local_1c;
	*(uchar *)(puVar6 + 3) = flare_texture.coords.u0;
	*(uchar *)((int)puVar6 + 0xd) = flare_texture.coords.v0;
	*(uchar *)(puVar6 + 5) = flare_texture.coords.u1;
	*(uchar *)((int)puVar6 + 0x15) = flare_texture.coords.v1;
	*(uchar *)(puVar6 + 7) = flare_texture.coords.u2;
	*(uchar *)((int)puVar6 + 0x1d) = flare_texture.coords.v2;
	*(uchar *)(puVar6 + 9) = flare_texture.coords.u3;
	*(uchar *)((int)puVar6 + 0x25) = flare_texture.coords.v3;
	*(ushort *)((int)puVar6 + 0xe) = flare_texture.clutid;
	*(ushort *)((int)puVar6 + 0x16) = flare_texture.tpageid | 0x20;
	pDVar4 = current;
	*puVar6 = *puVar6 & 0xff000000 | current->ot[0x1078] & 0xffffff;
	pDVar4->ot[0x1078] = pDVar4->ot[0x1078] & 0xff000000 | (uint)puVar6 & 0xffffff;
	pDVar4->primptr = pDVar4->primptr + 0x28;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayMoon(struct DVECTOR *pos /*$t4*/, struct CVECTOR *col /*$t6*/, int flip /*$a2*/)
 // line 609, offset 0x00078544
	/* begin block 1 */
		// Start line: 610
		// Start offset: 0x00078544
		// Variables:
	// 		struct POLY_FT3 *null; // $a0
	// 		struct VECTOR output; // stack offset -16
	// 		int width; // $t5
	// 		int height; // $t3
	/* end block 1 */
	// End offset: 0x000787B0
	// End Line: 649

	/* begin block 2 */
		// Start line: 1774
	/* end block 2 */
	// End Line: 1775

	/* begin block 3 */
		// Start line: 1784
	/* end block 3 */
	// End Line: 1785

	/* begin block 4 */
		// Start line: 1792
	/* end block 4 */
	// End Line: 1793

void DisplayMoon(DVECTOR *pos, CVECTOR *col, int flip)
{
	UNIMPLEMENTED();
	/*
	uchar uVar1;
	short sVar2;
	DB *pDVar3;
	uint uVar4;
	uint uVar5;
	uint *puVar6;
	char *pcVar7;
	short sVar8;

	sVar8 = (short)((int)((uint)moon_texture.coords.v2 - ((uint)moon_texture.coords.v0 - 1)) / 2);
	uVar5 = (uint)moon_texture.coords.u0;
	uVar4 = (uint)moon_texture.coords.u1;
	if (flip != 0) {
		sVar8 = -sVar8;
	}
	puVar6 = (uint *)current->primptr;
	*(char *)((int)puVar6 + 3) = '\a';
	*(char *)((int)puVar6 + 7) = '$';
	pDVar3 = current;
	*(undefined2 *)(puVar6 + 2) = 0xffff;
	*(undefined2 *)((int)puVar6 + 10) = 0xffff;
	*(undefined2 *)(puVar6 + 4) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x12) = 0xffff;
	*(undefined2 *)(puVar6 + 6) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x1a) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x16) = 0;
	*puVar6 = *puVar6 & 0xff000000 | pDVar3->ot[0x1079] & 0xffffff;
	pDVar3->ot[0x1079] = pDVar3->ot[0x1079] & 0xff000000 | (uint)puVar6 & 0xffffff;
	pcVar7 = pDVar3->primptr;
	pDVar3->primptr = pcVar7 + 0x20;
	pcVar7[0x23] = '\t';
	pcVar7[0x27] = ',';
	pcVar7[0x24] = col->r;
	pcVar7[0x25] = col->g;
	uVar1 = col->b;
	pcVar7[0x27] = '.';
	pcVar7[0x26] = uVar1;
	sVar2 = (short)((int)(uVar4 - (uVar5 - 1)) / 2);
	*(short *)(pcVar7 + 0x28) = pos->vx - sVar2;
	*(short *)(pcVar7 + 0x2a) = pos->vy - sVar8;
	*(short *)(pcVar7 + 0x30) = pos->vx + sVar2;
	*(short *)(pcVar7 + 0x32) = pos->vy - sVar8;
	*(short *)(pcVar7 + 0x38) = pos->vx - sVar2;
	*(short *)(pcVar7 + 0x3a) = pos->vy + sVar8;
	*(short *)(pcVar7 + 0x40) = pos->vx + sVar2;
	*(short *)(pcVar7 + 0x42) = pos->vy + sVar8;
	pcVar7[0x2c] = moon_texture.coords.u0;
	pcVar7[0x2d] = moon_texture.coords.v0;
	pcVar7[0x34] = moon_texture.coords.u1;
	pcVar7[0x35] = moon_texture.coords.v1;
	pcVar7[0x3c] = moon_texture.coords.u2;
	pcVar7[0x3d] = moon_texture.coords.v2;
	pcVar7[0x44] = moon_texture.coords.u3;
	pcVar7[0x45] = moon_texture.coords.v3;
	*(ushort *)(pcVar7 + 0x2e) = moon_texture.clutid;
	pDVar3 = current;
	*(ushort *)(pcVar7 + 0x36) = moon_texture.tpageid | 0x20;
	*(uint *)(pcVar7 + 0x20) = *(uint *)(pcVar7 + 0x20) & 0xff000000 | pDVar3->ot[0x1079] & 0xffffff;
	pDVar3->ot[0x1079] = pDVar3->ot[0x1079] & 0xff000000 | (uint)(pcVar7 + 0x20) & 0xffffff;
	pDVar3->primptr = pDVar3->primptr + 0x28;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ TunnelSkyFade()
 // line 679, offset 0x000787b0
	/* begin block 1 */
		// Start line: 681
		// Start offset: 0x000787B0
		// Variables:
	// 		int tun; // $a3

		/* begin block 1.1 */
			// Start line: 695
			// Start offset: 0x000787D8
			// Variables:
		// 		int diffX; // $v1
		// 		int diffZ; // $v0
		// 		int dX; // $v1
		// 		int dZ; // $v0
		// 		int len; // $a1
		// 		struct VECTOR *v1; // $t1
		// 		struct VECTOR *v2; // $t0

			/* begin block 1.1.1 */
				// Start line: 725
				// Start offset: 0x00078874
				// Variables:
			// 		int l2; // $v1
			/* end block 1.1.1 */
			// End offset: 0x000788E8
			// End Line: 745
		/* end block 1.1 */
		// End offset: 0x0007895C
		// End Line: 776
	/* end block 1 */
	// End offset: 0x0007895C
	// End Line: 777

	/* begin block 2 */
		// Start line: 1921
	/* end block 2 */
	// End Line: 1922

	/* begin block 3 */
		// Start line: 1952
	/* end block 3 */
	// End Line: 1953

	/* begin block 4 */
		// Start line: 1953
	/* end block 4 */
	// End Line: 1954

	/* begin block 5 */
		// Start line: 1955
	/* end block 5 */
	// End Line: 1956

/* WARNING: Unknown calling convention yet parameter storage is locked */

void TunnelSkyFade(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	VECTOR *pVVar5;
	VECTOR *pVVar6;

	iVar3 = 2;
	if (GameLevel != 3) {
		iVar3 = gTunnelNum;
	}
	pVVar5 = (VECTOR *)0x0;
	if (gTunnelNum == -1) {
		return;
	}
	pVVar6 = (VECTOR *)0x0;
	if ((((&tunnelDir)[iVar3 * 2] - (int)camera_angle.vy) + 0x800U & 0xfff) - 0x321 < 0x9bf) {
		pVVar6 = &tunnelPos + iVar3 * 2;
	}
	if ((((&INT_000a19e8)[iVar3 * 2] - (int)camera_angle.vy) + 0x800U & 0xfff) - 0x321 < 0x9bf) {
		pVVar5 = VECTOR_ARRAY_000a1a0c + iVar3 * 2;
	}
	if (pVVar6 == (VECTOR *)0x0) {
		if (pVVar5 == (VECTOR *)0x0) {
			skyFade = 0;
			return;
		}
		iVar4 = pVVar5->vx;
		iVar3 = pVVar5->vz;
	}
	else {
		if (pVVar5 != (VECTOR *)0x0) {
			iVar1 = pVVar6->vx - player.pos[0] >> 0xc;
			iVar3 = pVVar6->vz - player.pos[2] >> 0xc;
			iVar2 = pVVar5->vx - player.pos[0] >> 0xc;
			iVar4 = pVVar5->vz - player.pos[2] >> 0xc;
			iVar3 = iVar1 * iVar1 + iVar3 * iVar3;
			iVar4 = iVar2 * iVar2 + iVar4 * iVar4;
			if (iVar4 <= iVar3) {
				iVar3 = iVar4;
			}
			goto LAB_00078940;
		}
		iVar4 = pVVar6->vx;
		iVar3 = pVVar6->vz;
	}
	iVar4 = iVar4 - player.pos[0] >> 0xc;
	iVar3 = iVar3 - player.pos[2] >> 0xc;
	iVar3 = iVar4 * iVar4 + iVar3 * iVar3;
LAB_00078940:
	if (0x80 < iVar3 * 4) {
		skyFade = 0;
		return;
	}
	skyFade = iVar3 * -4 + 0x80;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ calc_sky_brightness()
 // line 785, offset 0x00078964
	/* begin block 1 */
		// Start line: 2223
	/* end block 1 */
	// End Line: 2224

	/* begin block 2 */
		// Start line: 2224
	/* end block 2 */
	// End Line: 2225

/* WARNING: Unknown calling convention yet parameter storage is locked */

void calc_sky_brightness(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	long lVar2;

	iVar1 = DawnCount >> 5;
	if (gTimeOfDay == 0) {
		skyred = iVar1 + 0x29;
		skyblue = iVar1 + 0x1c;
	}
	else {
		if (gTimeOfDay != 2) {
			skyblue = 0x80;
			skygreen = 0x80;
			skyred = 0x80;
			goto LAB_00078a68;
		}
		skyred = 0x8f - iVar1;
		skyblue = 0x80 - iVar1;
	}
	lVar2 = 0x1a;
	if ((skyred < 0x1a) || (lVar2 = 0x80, 0x80 < skyred)) {
		skyred = lVar2;
	}
	lVar2 = 0x1a;
	if ((skyblue < 0x1a) || (lVar2 = 0x80, skygreen = skyblue, 0x80 < skyblue)) {
		skygreen = lVar2;
	}
	if (skyblue < 0x1a) {
		skyblue = 0x1a;
	}
	else {
		if (0x80 < skyblue) {
			skyblue = 0x80;
		}
	}
LAB_00078a68:
	if ((((gTunnelNum != -1) && (GameLevel != 0)) && (GameLevel != 2)) &&
		(((GameLevel != 3 || (gTunnelNum == 1)) && ((GameLevel != 1 || (gTunnelNum != 2)))))) {
		TunnelSkyFade();
		if (skyFade < skyred) {
			skyred = skyFade;
		}
		if (skyFade < skygreen) {
			skygreen = skyFade;
		}
		if (skyFade < skyblue) {
			skyblue = skyFade;
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlotSkyPoly(int skytexnum /*$t5*/, unsigned char r /*$a1*/, unsigned char g /*$a2*/, unsigned char b /*$a3*/, int offset /*stack 16*/)
 // line 855, offset 0x00078b18
	/* begin block 1 */
		// Start line: 856
		// Start offset: 0x00078B18
		// Variables:
	// 		struct POLYFT4 *src; // $t1
	// 		struct DVECTOR *outpoints; // $t0
	// 		struct POLY_FT4 *prims; // $t2
	/* end block 1 */
	// End offset: 0x00078EBC
	// End Line: 894

	/* begin block 2 */
		// Start line: 2366
	/* end block 2 */
	// End Line: 2367

	/* begin block 3 */
		// Start line: 2369
	/* end block 3 */
	// End Line: 2370

void PlotSkyPoly(int skytexnum, unsigned char r, unsigned char g, unsigned char b, int offset)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	DB *pDVar2;
	int iVar3;
	uint *puVar4;

	iVar3 = DAT_1f80003c;
	puVar4 = (uint *)current->primptr;
	if ((((((-1 < (int)((uint)*(ushort *)
		((int)&DAT_1f800044 + (uint)*(byte *)(DAT_1f80003c + 4) * 4 + 2) <<
		0x10)) ||
		(-1 < (int)((uint)*(ushort *)
		((int)&DAT_1f800044 + (uint)*(byte *)(DAT_1f80003c + 5) * 4 + 2) << 0x10
			))) ||
			(-1 < (int)((uint)*(ushort *)
		((int)&DAT_1f800044 + (uint)*(byte *)(DAT_1f80003c + 6) * 4 + 2) << 0x10)
				)) || (-1 < (int)((uint)*(ushort *)
				((int)&DAT_1f800044 + (uint)*(byte *)(DAT_1f80003c + 7) * 4 + 2) <<
					0x10))) &&
					(((-1 < *(short *)(&DAT_1f800044 + *(byte *)(DAT_1f80003c + 4)) ||
		(-1 < *(short *)(&DAT_1f800044 + *(byte *)(DAT_1f80003c + 5)))) ||
						((-1 < *(short *)(&DAT_1f800044 + *(byte *)(DAT_1f80003c + 6)) ||
						(-1 < *(short *)(&DAT_1f800044 + *(byte *)(DAT_1f80003c + 7)))))))) &&
							(((*(short *)(&DAT_1f800044 + *(byte *)(DAT_1f80003c + 4)) < 0x141 ||
		(*(short *)(&DAT_1f800044 + *(byte *)(DAT_1f80003c + 5)) < 0x141)) ||
								((*(short *)(&DAT_1f800044 + *(byte *)(DAT_1f80003c + 6)) < 0x141 ||
								(*(short *)(&DAT_1f800044 + *(byte *)(DAT_1f80003c + 7)) < 0x141)))))) {
		*(char *)((int)puVar4 + 3) = '\t';
		*(char *)((int)puVar4 + 7) = ',';
		*(uchar *)(puVar4 + 1) = r;
		*(uchar *)((int)puVar4 + 5) = g;
		*(uchar *)((int)puVar4 + 6) = b;
		*(undefined2 *)(puVar4 + 2) = *(undefined2 *)(&DAT_1f800044 + *(byte *)(iVar3 + 4));
		sVar1 = (short)offset;
		*(short *)((int)puVar4 + 10) =
			*(short *)((int)&DAT_1f800044 + (uint)*(byte *)(iVar3 + 4) * 4 + 2) - sVar1;
		*(undefined2 *)(puVar4 + 4) = *(undefined2 *)(&DAT_1f800044 + *(byte *)(iVar3 + 5));
		*(short *)((int)puVar4 + 0x12) =
			*(short *)((int)&DAT_1f800044 + (uint)*(byte *)(iVar3 + 5) * 4 + 2) - sVar1;
		*(undefined2 *)(puVar4 + 6) = *(undefined2 *)(&DAT_1f800044 + *(byte *)(iVar3 + 7));
		*(short *)((int)puVar4 + 0x1a) =
			*(short *)((int)&DAT_1f800044 + (uint)*(byte *)(iVar3 + 7) * 4 + 2) - sVar1;
		*(undefined2 *)(puVar4 + 8) = *(undefined2 *)(&DAT_1f800044 + *(byte *)(iVar3 + 6));
		*(short *)((int)puVar4 + 0x22) =
			*(short *)((int)&DAT_1f800044 + (uint)*(byte *)(iVar3 + 6) * 4 + 2) - sVar1;
		*(uchar *)(puVar4 + 3) = skytexuv[skytexnum].u2;
		*(uchar *)((int)puVar4 + 0xd) = skytexuv[skytexnum].v2;
		*(uchar *)(puVar4 + 5) = skytexuv[skytexnum].u3;
		*(uchar *)((int)puVar4 + 0x15) = skytexuv[skytexnum].v3;
		*(uchar *)(puVar4 + 7) = skytexuv[skytexnum].u0;
		*(uchar *)((int)puVar4 + 0x1d) = skytexuv[skytexnum].v0;
		*(uchar *)(puVar4 + 9) = skytexuv[skytexnum].u1;
		*(uchar *)((int)puVar4 + 0x25) = skytexuv[skytexnum].v1;
		pDVar2 = current;
		*(short *)((int)puVar4 + 0xe) = skyclut[skytexnum];
		*(short *)((int)puVar4 + 0x16) = skytpage[skytexnum];
		*puVar4 = *puVar4 & 0xff000000 | pDVar2->ot[0x107f] & 0xffffff;
		pDVar2->ot[0x107f] = pDVar2->ot[0x107f] & 0xff000000 | (uint)puVar4 & 0xffffff;
		pDVar2->primptr = pDVar2->primptr + 0x28;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlotHorizonMDL(struct MODEL *model /*$s6*/, int horizontaboffset /*$a1*/)
 // line 896, offset 0x00078ec4
	/* begin block 1 */
		// Start line: 897
		// Start offset: 0x00078EC4
		// Variables:
	// 		struct SVECTOR *verts; // $v1
	// 		char *polys; // $s1
	// 		int i; // $s0
	// 		int p; // stack offset -56
	// 		int flag; // stack offset -52
	// 		short *zbuff; // $t5
	// 		int z; // stack offset -48
	// 		unsigned char r; // $s5
	// 		unsigned char g; // $s4
	// 		unsigned char b; // $s3
	/* end block 1 */
	// End offset: 0x000790B4
	// End Line: 945

	/* begin block 2 */
		// Start line: 2514
	/* end block 2 */
	// End Line: 2515

	/* begin block 3 */
		// Start line: 2520
	/* end block 3 */
	// End Line: 2521

void PlotHorizonMDL(MODEL *model, int horizontaboffset)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	bool bVar2;
	undefined4 uVar3;
	undefined4 in_zero;
	undefined4 in_at;
	uint uVar4;
	undefined2 uVar5;
	undefined4 *puVar6;
	undefined2 *puVar7;
	undefined4 *puVar8;
	undefined4 *puVar9;
	undefined4 *puVar10;
	undefined4 *puVar11;
	undefined4 *puVar12;
	undefined4 *puVar13;
	int iVar14;
	int iVar15;
	byte *pbVar16;
	byte *pbVar17;
	uint uVar18;
	uint uVar19;

	puVar6 = (undefined4 *)model->vertices;
	uVar4 = (uint)model->num_vertices + 3;
	iVar15 = 0;
	if (uVar4 != 0) {
		puVar7 = &DAT_1f800240;
		puVar10 = &DAT_1f80004c;
		puVar9 = &DAT_1f800048;
		puVar8 = &DAT_1f800044;
		puVar13 = puVar6 + 4;
		puVar12 = puVar6 + 2;
		puVar11 = puVar6;
		do {
			setCopReg(2, in_zero, *puVar11);
			setCopReg(2, in_at, puVar11[1]);
			setCopReg(2, uVar4, *puVar12);
			setCopReg(2, puVar6, puVar12[1]);
			setCopReg(2, puVar7, *puVar13);
			setCopReg(2, horizontaboffset, puVar13[1]);
			copFunction(2, 0x280030);
			uVar3 = getCopReg(2, 0xc);
			*puVar8 = uVar3;
			uVar3 = getCopReg(2, 0xd);
			*puVar9 = uVar3;
			uVar3 = getCopReg(2, 0xe);
			*puVar10 = uVar3;
			getCopReg(2, 8);
			getCopControlWord(2, 0xf800);
			iVar14 = getCopReg(2, 0x9800);
			puVar10 = puVar10 + 3;
			puVar9 = puVar9 + 3;
			puVar8 = puVar8 + 3;
			puVar13 = puVar13 + 6;
			puVar12 = puVar12 + 6;
			puVar11 = puVar11 + 6;
			iVar15 = iVar15 + 3;
			puVar6 = (undefined4 *)(&DAT_00001080 + -(iVar14 >> 2 & 0xffffU));
			uVar5 = SUB42(puVar6, 0);
			puVar7[2] = uVar5;
			puVar7[1] = uVar5;
			*puVar7 = uVar5;
			bVar2 = iVar15 < (int)((uint)model->num_vertices + 3);
			uVar4 = (uint)bVar2;
			puVar7 = puVar7 + 3;
		} while (bVar2);
	}
	if (-1 < DAT_1f800254) {
		pbVar16 = (byte *)model->poly_block;
		uVar19 = (uint)(byte)skyred;
		uVar18 = (uint)(byte)skygreen;
		DAT_1f80001c = &DAT_1f800240;
		uVar4 = (uint)(byte)skyblue;
		iVar15 = 0;
		DAT_1f800018 = model;
		if (model->num_polys != 0) {
			pbVar17 = HorizonTextures + horizontaboffset;
			do {
				if (iVar15 == 0xc) {
					uVar19 = uVar19 >> 1;
					uVar18 = uVar18 >> 1;
					uVar4 = uVar4 >> 1;
				}
				bVar1 = *pbVar17;
				pbVar17 = pbVar17 + 1;
				DAT_1f80003c = pbVar16;
				PlotSkyPoly((uint)bVar1, (uchar)uVar19, (uchar)uVar18, (uchar)uVar4, sky_y_offset[GameLevel]);
				iVar15 = iVar15 + 1;
				pbVar16 = pbVar16 + PolySizes[*pbVar16];
			} while (iVar15 < (int)(uint)model->num_polys);
		}
	}
	return;*/
}





