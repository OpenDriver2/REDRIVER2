#include "THISDUST.H"
#include "SKY.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "MODELS.H"
#include "DRAW.H"
#include "CAMERA.H"
#include "MAIN.H"

#include "LIBGTE.H"
#include "GTEREG.H"
#include "INLINE_C.H"

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

UV skytexuv[28] = { 0 };
short skyclut[28];
short skytpage[28];

// [D]
void LoadSky(void)
{
	bool bVar1;
	bool bVar2;
	unsigned char uVar3;
	unsigned char uVar4;
	u_short uVar5;
	unsigned char uVar6;
	uint uVar7;
	int iVar8;
	int uVar9;
	int iVar10;
	UV *uv;
	unsigned char *puVar12;
	unsigned char uVar13;
	int iVar14;
	uint uVar15;
	int x;
	RECT16 rect;
	char name[16];
	int offset;

	iVar10 = 0;
	uVar7 = 0;
	offset = 0;
	bVar1 = true;
	do {
		if (!bVar1) {
		switchD_00077628_caseD_0:
			iVar8 = 0;
			bVar1 = false;
			bVar2 = true;
			goto LAB_00077680;
		}
		switch (uVar7) {
		default:
			goto switchD_00077628_caseD_0;
		case 1:
			iVar8 = 0;
			bVar1 = false;
			break;
		case 2:
			iVar8 = 1;
			bVar1 = false;
			break;
		case 3:
			iVar8 = 1;
			goto LAB_00077678;
		case 4:
			iVar8 = 0;
			goto LAB_00077678;
		case 5:
			iVar8 = 2;
			bVar1 = false;
			break;
		case 6:
			iVar8 = 2;
		LAB_00077678:
			bVar1 = true;
		}
		bVar2 = false;
	LAB_00077680:
		iVar14 = 0;
		uVar7 = uVar7 + 1;
		x = 0x140;
		uVar15 = 0x140;
		uv = skytexuv + iVar10;
		uVar3 = (unsigned char)(iVar8 * 0x54);
		uVar13 = uVar3 + 'S';
		puVar12 = &skytexuv[0].u0 + (iVar10 * 8 | 6);
		do {
			uVar6 = (char)iVar14 * -0x80;
			if (bVar2) {
				uv->u0 = uVar6;
				uv->v0 = uVar3;
				uv->u1 = uVar6;
				uv->v1 = uVar3;
				uv->u2 = uVar6;
				puVar12[-1] = uVar3;
				*puVar12 = uVar6;
			LAB_00077748:
				uv->v3 = uVar3;
			}
			else {
				uVar4 = uVar6 + '\x7f';
				if (bVar1) 
				{
					uv->u0 = uVar6;
					uv->v0 = uVar13;
					uv->u1 = uVar4;
					uv->v1 = uVar13;
					uv->u2 = uVar6;
					puVar12[-1] = uVar3;
					*puVar12 = uVar4;
					goto LAB_00077748;
				}
				uv->u0 = uVar6;
				uv->v0 = uVar3;
				uv->u1 = uVar4;
				uv->v1 = uVar3;
				uv->u2 = uVar6;
				puVar12[-1] = uVar13;
				*puVar12 = uVar4;
				uv->v3 = uVar13;
			}
			uVar5 = GetTPage(0, 0, uVar15 & 0xffffffc0, iVar8 * 0x54 & 0x300);
			skytpage[iVar10] = uVar5;
			uVar5 = GetClut(x, iVar8 + 0xfc);
			uv = uv + 1;
			puVar12 = puVar12 + 8;
			x = x + 0x10;
			uVar15 = uVar15 + 0x20;
			iVar14 = iVar14 + 1;
			skyclut[iVar10] = uVar5;
			iVar10 = iVar10 + 1;
		} while (iVar14 < 4);
		bVar1 = uVar7 < 7;
	} while ((int)uVar7 < 7);

	if (GameLevel == 1) 
		uVar9 = 1;
	else if (GameLevel == 2)
		uVar9 = 2;
	else if (GameLevel == 3)
		uVar9 = 3;
	else
		uVar9 = 0;

	if (gWeather - 1U < 2) 
	{
		offset = 0x20000;
		iVar10 = offset;
		if (gTimeOfDay == 3)
		{
			offset = 0x10000;
			iVar10 = offset;
		}
	}
	else 
	{
		if (gTimeOfDay == 1) 
		{
			offset = 0;
			iVar10 = offset;
		}
		else 
		{
			if (gTimeOfDay < 2) 
			{
				if (gTimeOfDay != 0)
					goto LAB_000778d4;

				offset = 0x30000;
				iVar10 = offset;
			}
			else 
			{
				if (gTimeOfDay == 2)
				{
					iVar10 = 0x40000;
				}
				else 
				{
					iVar10 = 0x10000;

					if (gTimeOfDay != 3)
						goto LAB_000778d4;
				}
			}
		}
	}
	offset = iVar10;
LAB_000778d4:

	sprintf(name, "DATA\\SKY%d.RAW", uVar9);
	LoadfileSeg(name, _frontend_buffer, offset, 0x10000);

	rect.x = 0x140;
	rect.y = 0;
	rect.w = 0x80;
	rect.h = 0x100;

	LoadImage(&rect, (u_long *)_frontend_buffer);

	DrawSync(0);
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

// [D]
void DrawSkyDome(void)
{
	calc_sky_brightness();

	// [A] temporarily disabled angle checks

	//if ((camera_angle.vy - 1450 < 2251))
		PlotHorizonMDL(modelpointers[0], HorizonLookup[GameLevel][0]);

	//if (!(camera_angle.vy - 651 < 1799))
		PlotHorizonMDL(modelpointers[2], HorizonLookup[GameLevel][1]);

	//if (!(camera_angle.vy - 1701 < 1749))
		PlotHorizonMDL(modelpointers[3], HorizonLookup[GameLevel][2]);

	//if ((camera_angle.vy - 400 < 2301))
		PlotHorizonMDL(modelpointers[1], HorizonLookup[GameLevel][3]);
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

int gTunnelNum = -1;
int skyFade;
static long skyred = 0x80;
static long skygreen = 0x80;
static long skyblue = 0x80;

void TunnelSkyFade(void)
{
	UNIMPLEMENTED();
	skyFade = 0;

#if 0
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
	pVVar5 = NULL;
	if (gTunnelNum == -1) {
		return;
	}
	pVVar6 = NULL;
	if (((tunnelDir[iVar3 * 2] - (int)camera_angle.vy) + 0x800U & 0xfff) - 0x321 < 0x9bf) {
		pVVar6 = tunnelPos + iVar3 * 2;
	}
	if (((tunnelDir[iVar3 * 2 + 1] - (int)camera_angle.vy) + 0x800U & 0xfff) - 0x321 < 0x9bf) {
		pVVar5 = tunnelPos + iVar3 * 2 + 1;
	}
	if (pVVar6 == NULL) {
		if (pVVar5 == NULL) {
			skyFade = 0;
			return;
		}
		iVar4 = pVVar5->vx;
		iVar3 = pVVar5->vz;
	}
	else {
		if (pVVar5 != NULL) {
			iVar1 = pVVar6->vx - player[0].pos[0] >> 0xc;
			iVar3 = pVVar6->vz - player[0].pos[2] >> 0xc;
			iVar2 = pVVar5->vx - player[0].pos[0] >> 0xc;
			iVar4 = pVVar5->vz - player[0].pos[2] >> 0xc;
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
	iVar4 = iVar4 - player[0].pos[0] >> 0xc;
	iVar3 = iVar3 - player[0].pos[2] >> 0xc;
	iVar3 = iVar4 * iVar4 + iVar3 * iVar3;
LAB_00078940:
	if (0x80 < iVar3 * 4) {
		skyFade = 0;
		return;
	}
	skyFade = iVar3 * -4 + 0x80;
#endif
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

// [D]
void calc_sky_brightness(void)
{
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

// offset: 0x1f800020
extern _pct plotContext;

POLYFT4* scratchPad_skyPolygonsPtr;		// 1f80003c
DVECTOR scratchPad_skyVertices[256];	// 1f800044
short scratchPad_zbuff[256];

// [D]
void PlotSkyPoly(int skytexnum, unsigned char r, unsigned char g, unsigned char b, int offset)
{
	POLYFT4 *pPVar3;
	POLY_FT4 *local_t2_64;

	pPVar3 = scratchPad_skyPolygonsPtr;
	local_t2_64 = (POLY_FT4 *)current->primptr;

	if ((((((-1 < (int)((uint)(ushort)scratchPad_skyVertices[pPVar3->v0].vy << 0x10)) ||
		(-1 < (int)((uint)(ushort)scratchPad_skyVertices[pPVar3->v1].vy << 0x10))) ||
		(-1 < (int)((uint)(ushort)scratchPad_skyVertices[pPVar3->v2].vy << 0x10))) ||
		(-1 < (int)((uint)(ushort)scratchPad_skyVertices[pPVar3->v3].vy << 0x10))) &&
		(((-1 < scratchPad_skyVertices[pPVar3->v0].vx ||
		(-1 < scratchPad_skyVertices[pPVar3->v1].vx)) ||
		((-1 < scratchPad_skyVertices[pPVar3->v2].vx ||
		(-1 < scratchPad_skyVertices[pPVar3->v3].vx)))))) &&
		(((scratchPad_skyVertices[pPVar3->v0].vx < 0x141 ||
		(scratchPad_skyVertices[pPVar3->v1].vx < 0x141)) ||
		((scratchPad_skyVertices[pPVar3->v2].vx < 0x141 ||
		(scratchPad_skyVertices[pPVar3->v3].vx < 0x141)))))) 
	{
		setPolyFT4(local_t2_64);

		local_t2_64->r0 = r;
		local_t2_64->g0 = g;
		local_t2_64->b0 = b;
		local_t2_64->x0 = scratchPad_skyVertices[pPVar3->v0].vx;
		local_t2_64->y0 = scratchPad_skyVertices[pPVar3->v0].vy - offset;
		local_t2_64->x1 = scratchPad_skyVertices[pPVar3->v1].vx;
		local_t2_64->y1 = scratchPad_skyVertices[pPVar3->v1].vy - offset;
		local_t2_64->x2 = scratchPad_skyVertices[pPVar3->v3].vx;
		local_t2_64->y2 = scratchPad_skyVertices[pPVar3->v3].vy - offset;
		local_t2_64->x3 = scratchPad_skyVertices[pPVar3->v2].vx;
		local_t2_64->y3 = scratchPad_skyVertices[pPVar3->v2].vy - offset;
		local_t2_64->u0 = skytexuv[skytexnum].u2;
		local_t2_64->v0 = skytexuv[skytexnum].v2;
		local_t2_64->u1 = skytexuv[skytexnum].u3;
		local_t2_64->v1 = skytexuv[skytexnum].v3;
		local_t2_64->u2 = skytexuv[skytexnum].u0;
		local_t2_64->v2 = skytexuv[skytexnum].v0;
		local_t2_64->u3 = skytexuv[skytexnum].u1;
		local_t2_64->v3 = skytexuv[skytexnum].v1;
		local_t2_64->clut = skyclut[skytexnum];
		local_t2_64->tpage = skytpage[skytexnum];

		addPrim(current->ot + 0x107f, local_t2_64);

		current->primptr = current->primptr + sizeof(POLY_FT4);
	}
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

// [D] [A] WTF
void PlotHorizonMDL(MODEL *model, int horizontaboffset)
{
	unsigned char bVar1;

	uint uVar4;

	SVECTOR *pSVar6;
	
	DVECTOR *dv0;
	DVECTOR *dv1;
	DVECTOR *dv2;

	SVECTOR *v0;
	SVECTOR *v1;
	SVECTOR *v2;

	int iVar13;
	unsigned char *pbVar14;
	unsigned char *pbVar15;
	uint uVar16;
	uint uVar17;

	short *zbuff;
	int p;
	int flag;
	int z;

	pSVar6 = (SVECTOR *)model->vertices;
	uVar4 = (uint)model->num_vertices + 3;

	iVar13 = 0;

	if (uVar4 != 0) 
	{
		zbuff = scratchPad_zbuff;

		dv2 = scratchPad_skyVertices + 2;
		dv1 = scratchPad_skyVertices + 1;
		dv0 = scratchPad_skyVertices;

		v2 = pSVar6 + 2;
		v1 = pSVar6 + 1;
		v0 = pSVar6;

		do {
			
			gte_RotTransPers3(v0, v1, v2, dv0, dv1, dv2, &p, &flag, &z);

			dv2 += 3;
			dv1 += 3;
			dv0 += 3;

			v2 += 3;
			v1 += 3;
			v0 += 3;

			iVar13 += 3;

			zbuff[2] = z;
			zbuff[1] = z;
			zbuff[0] = z;

			zbuff += 3;
		} while (iVar13 < (int)((uint)model->num_vertices + 3));
	}

	if (0 < scratchPad_zbuff[16])
	{
		pbVar14 = (unsigned char *)model->poly_block;
		uVar17 = skyred;
		uVar16 = skygreen;

		//DAT_1f80001c = SHORT_ARRAY_1f800240;
		uVar4 = skyblue;
		iVar13 = 0;
		//DAT_1f800018 = model;

		if (model->num_polys != 0) 
		{
			pbVar15 = HorizonTextures + horizontaboffset;
			do {
				if (iVar13 == 0xc) {
					uVar17 = uVar17 >> 1;
					uVar16 = uVar16 >> 1;
					uVar4 = uVar4 >> 1;
				}
				bVar1 = *pbVar15;
				pbVar15 = pbVar15 + 1;


				scratchPad_skyPolygonsPtr = (POLYFT4*)pbVar14; //_DAT_1f80003c = pbVar14;

				PlotSkyPoly((uint)bVar1, uVar17, uVar16, uVar4, sky_y_offset[GameLevel]);

				iVar13 = iVar13 + 1;
				pbVar14 = pbVar14 + PolySizes[*pbVar14];
			} while (iVar13 < (int)(uint)model->num_polys);
		}
	}
}





