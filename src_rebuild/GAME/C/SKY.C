#include "DRIVER2.H"
#include "SKY.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "MODELS.H"
#include "DRAW.H"
#include "CAMERA.H"
#include "MAIN.H"
#include "DEBRIS.H"
#include "PLAYERS.H"

#include "LIBGTE.H"
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


SVECTOR sun_position[4] = {
	{-32000,-11000,-5000},
	{-32000,-11000,-5000},
	{-32000,-11000,-5000},
	{-32000,-11000,-5000}
};

SVECTOR moon_position[4] = {
	{-32000,-11500,-18000},
	{-32000,-11500,-18000,},
	{-32000,-11500,-18000,},
	{-32000,-11500,-18000,}
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
	{
		{0x0,0x0,0x5a},0x10, 0x30
	},
	{
		{0x50,0x28,0x4},0x30,0x48
	},
	{
		{0x5a,0x0,0x0},0x30,0x60
	},
	{
		{0x0,0x5a,0x0},0x10,0x90
	},
	{
		{0x0,0x0,0x5a,},0x40,0xa0
	},
	{
		{0x5a,0x5a,0x0},0x20,0xb8
	},
	{
		{0x5a,0x0,0x0},0x20,0xd0
	},
	{
		{0x0,0x0,0x5a},0x30,0xf
	}
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

// [D]
#ifdef PGXP
void DisplaySun(DVECTORF *pos, CVECTOR *col, int flare_col)
#else
void DisplaySun(DVECTOR *pos, CVECTOR *col, int flare_col)
#endif
{
	short sVar1;
	short sVar2;
	int iVar3;

	POLY_FT4 *polys;
	POLY_FT3 *null;

	int uVar5;
	int uVar6;
	int uVar7;
	int uVar8;

	short local_20;
	short local_1c;

	uVar5 = sun_texture.coords.u1;
	uVar7 = sun_texture.coords.u0;
	uVar6 = sun_texture.coords.v2;
	uVar8 = sun_texture.coords.v0;

	null = (POLY_FT3 *)current->primptr;
	setPolyFT3(null);

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = 0;

	addPrim(current->ot + 0x1079, null);
	current->primptr += sizeof(POLY_FT3);

	polys = (POLY_FT4 *)current->primptr;
	setPolyFT4(polys);
	setSemiTrans(polys, 1);

	polys->r0 = col->r;
	polys->g0 = col->g;
	polys->b0 = col->b;
	
	sVar1 = (((uVar5 - (uVar7 - 1)) / 2) * 3 >> 2);
	sVar2 = (((uVar6 - (uVar8 - 1)) / 2) * 3 >> 2);

	polys->x0 = pos->vx - sVar1;
	polys->y0 = pos->vy - sVar2;
	polys->x1 = pos->vx + sVar1;
	polys->y1 = pos->vy - sVar2;
	polys->x2 = pos->vx - sVar1;
	polys->y2 = pos->vy + sVar2;
	polys->x3 = pos->vx + sVar1;
	polys->y3 = pos->vy + sVar2;
	polys->u0 = sun_texture.coords.u0;
	polys->v0 = sun_texture.coords.v0;
	polys->u1 = sun_texture.coords.u1;
	polys->v1 = sun_texture.coords.v1;
	polys->u2 = sun_texture.coords.u2;
	polys->v2 = sun_texture.coords.v2;
	polys->u3 = sun_texture.coords.u3;
	polys->v3 = sun_texture.coords.v3;
	polys->clut = sun_texture.clutid;
	polys->tpage = sun_texture.tpageid | 0x20;

	addPrim(current->ot + 0x1079, polys);
	current->primptr += sizeof(POLY_FT4);

	sVar1 = rcossin_tbl[(camera_angle.vy & 0x1ffe) + 1];
	sVar2 = rcossin_tbl[camera_angle.vy & 0x1ffe];
	iVar3 = -(((flare_texture.coords.u1 - (flare_texture.coords.u0 - 1)) / 2) * 3 >> 2);

	polys = (POLY_FT4 *)current->primptr;
	setPolyFT4(polys);
	setSemiTrans(polys, 1);

	polys->r0 = (flare_col >> 1);
	polys->g0 = (flare_col >> 1);
	polys->b0 = (flare_col >> 2);

	local_20 = ((sVar1 - sVar2) * iVar3 >> 0xc);
	local_1c = ((sVar2 + sVar1) * iVar3 >> 0xc);

	polys->x0 = pos->vx + local_20;
	polys->y0 = pos->vy + local_1c;
	polys->x1 = pos->vx - local_1c;
	polys->y1 = pos->vy + local_20;
	polys->x2 = pos->vx + local_1c;
	polys->y2 = pos->vy - local_20;
	polys->x3 = pos->vx - local_20;
	polys->y3 = pos->vy - local_1c;
	polys->u0 = flare_texture.coords.u0;
	polys->v0 = flare_texture.coords.v0;
	polys->u1 = flare_texture.coords.u1;
	polys->v1 = flare_texture.coords.v1;
	polys->u2 = flare_texture.coords.u2;
	polys->v2 = flare_texture.coords.v2;
	polys->u3 = flare_texture.coords.u3;
	polys->v3 = flare_texture.coords.v3;
	polys->clut = flare_texture.clutid;
	polys->tpage = flare_texture.tpageid | 0x20;

	addPrim(current->ot + 0x1078, polys);
	current->primptr += sizeof(POLY_FT4);
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

// [D]
#ifdef PGXP
void DisplayMoon(DVECTORF *pos, CVECTOR *col, int flip)
#else
void DisplayMoon(DVECTOR *pos, CVECTOR *col, int flip)
#endif
{
	short sVar2;
	int uVar4;
	int uVar5;
	POLY_FT3 *null;
	POLY_FT4 *polys;
	short sVar6;

	sVar6 = (moon_texture.coords.v2 - (moon_texture.coords.v0 - 1)) / 2;
	uVar5 = moon_texture.coords.u0;
	uVar4 = moon_texture.coords.u1;

	if (flip != 0)
		sVar6 = -sVar6;

	null = (POLY_FT3 *)current->primptr;
	setPolyFT3(null);

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = 0;

	addPrim(current->ot + 0x1079, null);

	current->primptr += sizeof(POLY_FT3);

	polys = (POLY_FT4*)current->primptr;

	setPolyFT4(polys);
	setSemiTrans(polys, 1);

	polys->r0 = col->r;
	polys->g0 = col->g;
	polys->b0 = col->b;

	sVar2 = (uVar4 - (uVar5 - 1)) / 2;

	polys->x0 = pos->vx - sVar2;
	polys->y0 = pos->vy - sVar6;
	polys->x1 = pos->vx + sVar2;
	polys->y1 = pos->vy - sVar6;
	polys->x2 = pos->vx - sVar2;
	polys->y2 = pos->vy + sVar6;
	polys->x3 = pos->vx + sVar2;
	polys->y3 = pos->vy + sVar6;

	polys->u0 = moon_texture.coords.u0;
	polys->v0 = moon_texture.coords.v0;
	polys->u1 = moon_texture.coords.u1;
	polys->v1 = moon_texture.coords.v1;
	polys->u2 = moon_texture.coords.u2;
	polys->v2 = moon_texture.coords.v2;
	polys->u3 = moon_texture.coords.u3;
	polys->v3 = moon_texture.coords.v3;

	polys->clut = moon_texture.clutid;
	polys->tpage = moon_texture.tpageid | 0x20;

	addPrim(current->ot + 0x1079, polys);
	current->primptr += sizeof(POLY_FT4);
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

extern VECTOR dummy;

// [D]
void DrawLensFlare(void)
{
	static char last_attempt_failed; // offset 0x0
	static short buffer[160];

	unsigned char bVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	short sVar5;
	long lVar6;
	int iVar7;
	int iVar8;
	POLY_FT4 *poly;
	FLAREREC *pFlareInfo;
	short *puVar9;
	short *psVar10;
	DR_MOVE *sample_sun;
	int flare_col;
	int iVar11;
	short sVar13;
	int iVar12;

#ifdef PGXP
	DVECTORF sun_pers_conv_position;
#else
	DVECTOR sun_pers_conv_position;
#endif
	CVECTOR col;
	int flarez;

	RECT16 source = {
		1008,
		456,
		16,
		10
	};

	if (gTimeOfDay != 0 && gTimeOfDay != 2)
	{
		col.r = -1;

		if (gTimeOfDay == 3)
			col.r = -0x80;

		flare_col = 0;

		col.g = col.r;
		col.b = col.r;

		if (gTimeOfDay != 3 && last_attempt_failed == 0)
		{
			puVar9 = buffer;
			StoreImage(&source, (u_long*)buffer);
			iVar7 = 0;

			do {
				iVar7 = iVar7 + 1;
				iVar8 = 0xb;

				do {
					psVar10 = puVar9;

					if ((*psVar10 == -1) || (*psVar10 == 0x7fff))
						flare_col++;

					iVar8--;
					puVar9 = psVar10 + 1;
				} while (-1 < iVar8);

				puVar9 = psVar10 + 5;
			} while (iVar7 < 10);
		}

		gte_SetRotMatrix(&inv_camera_matrix);
		gte_SetTransVector(&dummy);

		if (gTimeOfDay == 3)
		{
			gte_ldv0(&moon_position[GameLevel]);
		}
		else
		{
			gte_ldv0(&sun_position[GameLevel]);
		}

		gte_rtps();

		gte_stsxy(&sun_pers_conv_position);

		gte_stszotz(&iVar7);


		iVar11 = sun_pers_conv_position.vx - 160;
		iVar8 = sun_pers_conv_position.vy - 128;
		lVar6 = SquareRoot0(iVar11 * iVar11 + iVar8 * iVar8);

		if (gTimeOfDay == 3)
		{
			if (lVar6 < 500)
			{
				DisplayMoon(&sun_pers_conv_position, &col, 0);

				col.r = 64;
				col.b = 64;
				col.g = 64;

				gte_ldv0(&moon_shadow_position[GameLevel]);

				gte_rtps();

				gte_stsxy(&sun_pers_conv_position);

				DisplayMoon(&sun_pers_conv_position, &col, 1);
			}
		}
		else
		{
			if ((0 < iVar7) && (lVar6 < 500))
			{
				DisplaySun(&sun_pers_conv_position, &col, flare_col);

				iVar7 = (0x3c - (lVar6 >> 1)) * flare_col;

				add_haze((iVar7 / 6 + (iVar7 >> 0x1f) >> 3) - (iVar7 >> 0x1f), iVar7 >> 6, 7);

				iVar7 = flare_col / 3 - (lVar6 * 0x50) / 500;

				if (iVar7 > -1 && flare_col != 0)
				{
					pFlareInfo = flare_info;

					do {
						flare_col = (128 - pFlareInfo->gapmod) * 2;
						iVar12 = iVar11 * flare_col;

						flare_col = iVar8 * flare_col;

						poly = (POLY_FT4 *)current->primptr;
						setPolyFT4(poly);
						setSemiTrans(poly, 1);

						bVar1 = pFlareInfo->size;

						sVar5 = (bVar1 >> 1);
						sVar4 = ((iVar12 >> 8) + 0xa0) - sVar5;
						sVar5 = ((flare_col >> 8) + 0x80) - sVar5;

						poly->y0 = sVar5;
						poly->y1 = sVar5;
						poly->x0 = sVar4;
						poly->x1 = sVar4 + bVar1;
						poly->x2 = sVar4;
						poly->y2 = sVar5 + bVar1;
						poly->x3 = sVar4 + bVar1;
						poly->y3 = sVar5 + bVar1;

						poly->r0 = (pFlareInfo->transparency.r * iVar7 >> 6);
						poly->g0 = (pFlareInfo->transparency.g * iVar7 >> 6);
						poly->b0 = (pFlareInfo->transparency.b * iVar7 >> 6);

						poly->u0 = lensflare_texture.coords.u0;
						poly->v0 = lensflare_texture.coords.v0;
						poly->u1 = lensflare_texture.coords.u1;
						poly->v1 = lensflare_texture.coords.v1;
						poly->u2 = lensflare_texture.coords.u2;
						poly->v2 = lensflare_texture.coords.v2 - 4;
						poly->u3 = lensflare_texture.coords.u3;
						poly->v3 = lensflare_texture.coords.v3 - 4;
						poly->clut = lensflare_texture.clutid;

						poly->tpage = lensflare_texture.tpageid | 0x20;

						addPrim(current->ot + 10, poly);
						current->primptr += sizeof(POLY_FT4);

						pFlareInfo++;

					} while (pFlareInfo < flare_info + 8);
				}
			}
			sun_pers_conv_position.vx = sun_pers_conv_position.vx - 8;
			sun_pers_conv_position.vy = sun_pers_conv_position.vy - 4;

			if (-1 < sun_pers_conv_position.vx)
			{
				if (((-1 < sun_pers_conv_position.vy) &&
					(sun_pers_conv_position.vx + 0x10 < 0x141)) &&
					(sun_pers_conv_position.vy + 10 < 0x101))
				{
					last_attempt_failed = 0;

					source.x = sun_pers_conv_position.vx;
					source.y = sun_pers_conv_position.vy + last->disp.disp.y;

					sample_sun = (DR_MOVE *)current->primptr;
					SetDrawMove(sample_sun, &source, 1008, 456);

					addPrim(current->ot + 0x20, sample_sun);
					current->primptr += sizeof(DR_MOVE);

					return;
				}
			}

			last_attempt_failed = 0;
		}
	}
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

int tunnelDir[3][2]=
{
	{0x7D0, 0xBF8},
	{0x800, 0x0},
	{0x800, 0xFFF}
};

// [D]
void TunnelSkyFade(void)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	VECTOR *pVVar5;
	VECTOR *pVVar6;

	iVar3 = 2;

	if (GameLevel != 3)
		iVar3 = gTunnelNum;

	pVVar5 = NULL;

	if (gTunnelNum == -1)
		return;

	pVVar6 = NULL;

	if (((tunnelDir[iVar3][0] - camera_angle.vy) + 0x800U & 0xfff) - 0x321 < 0x9bf)
		pVVar6 = &tunnelPos[iVar3][0];

	if (((tunnelDir[iVar3][1] - camera_angle.vy) + 0x800U & 0xfff) - 0x321 < 0x9bf)
		pVVar5 = &tunnelPos[iVar3][1];

	if (pVVar6 == NULL) 
	{
		if (pVVar5 == NULL) 
		{
			skyFade = 0;
			return;
		}

		iVar4 = pVVar5->vx;
		iVar3 = pVVar5->vz;
	}
	else
	{
		if (pVVar5 != NULL) 
		{
			iVar1 = FIXED(pVVar6->vx - player[0].pos[0]);
			iVar3 = FIXED(pVVar6->vz - player[0].pos[2]);

			iVar2 = FIXED(pVVar5->vx - player[0].pos[0]);
			iVar4 = FIXED(pVVar5->vz - player[0].pos[2]);

			iVar3 = iVar1 * iVar1 + iVar3 * iVar3;
			iVar4 = iVar2 * iVar2 + iVar4 * iVar4;

			if (iVar4 <= iVar3)
				iVar3 = iVar4;

			goto LAB_00078940;
		}

		iVar4 = pVVar6->vx;
		iVar3 = pVVar6->vz;
	}

	iVar4 = FIXED(iVar4 - player[0].pos[0]);
	iVar3 = FIXED(iVar3 - player[0].pos[2]);

	iVar3 = iVar4 * iVar4 + iVar3 * iVar3;

LAB_00078940:

	if (0x80 < iVar3 * 4) 
	{
		skyFade = 0;
		return;
	}

	skyFade = iVar3 * -4 + 128;
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
	else 
	{
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

	if (skyblue < 0x1a)
		skyblue = 0x1a;
	else if (0x80 < skyblue)
		skyblue = 0x80;

LAB_00078a68:
	if ((((gTunnelNum != -1) && (GameLevel != 0)) && (GameLevel != 2)) &&
		(((GameLevel != 3 || (gTunnelNum == 1)) && ((GameLevel != 1 || (gTunnelNum != 2)))))) 
	{
		TunnelSkyFade();
		if (skyFade < skyred)
			skyred = skyFade;
	
		if (skyFade < skygreen)
			skygreen = skyFade;
	
		if (skyFade < skyblue)
			skyblue = skyFade;
	
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

#ifdef PGXP
DVECTORF scratchPad_skyVertices[256];	// 1f800044
#else
DVECTOR scratchPad_skyVertices[256];	// 1f800044
#endif

short scratchPad_zbuff[256];

// [D]
void PlotSkyPoly(int skytexnum, unsigned char r, unsigned char g, unsigned char b, int offset)
{
	POLYFT4 *src;
	POLY_FT4 *poly;

	src = scratchPad_skyPolygonsPtr;
	poly = (POLY_FT4 *)current->primptr;

#ifdef PGXP
	DVECTORF *outpoints = scratchPad_skyVertices;
#else
	DVECTOR *outpoints = scratchPad_skyVertices;
#endif

#ifdef PSX
	if ((outpoints[src->v0].vy > -1 || outpoints[src->v1].vy > -1 || outpoints[src->v2].vy > -1 || outpoints[src->v3].vy > -1) && 
		(outpoints[src->v0].vx > -1 || outpoints[src->v1].vx > -1 || outpoints[src->v2].vx > -1 || outpoints[src->v3].vx > -1) &&
		(outpoints[src->v0].vx < 321 || outpoints[src->v1].vx < 321 || outpoints[src->v2].vx < 321 || outpoints[src->v3].vx < 321))
#endif
	{
		setPolyFT4(poly);

		poly->r0 = r;
		poly->g0 = g;
		poly->b0 = b;


		poly->x0 = outpoints[src->v0].vx;
		poly->y0 = outpoints[src->v0].vy;
		poly->x1 = outpoints[src->v1].vx;
		poly->y1 = outpoints[src->v1].vy;
		poly->x2 = outpoints[src->v3].vx;
		poly->y2 = outpoints[src->v3].vy;
		poly->x3 = outpoints[src->v2].vx;
		poly->y3 = outpoints[src->v2].vy;

		poly->u0 = skytexuv[skytexnum].u2;
		poly->v0 = skytexuv[skytexnum].v2;
		poly->u1 = skytexuv[skytexnum].u3;
		poly->v1 = skytexuv[skytexnum].v3;
		poly->u2 = skytexuv[skytexnum].u0;
		poly->v2 = skytexuv[skytexnum].v0;
		poly->u3 = skytexuv[skytexnum].u1;
		poly->v3 = skytexuv[skytexnum].v1;
		poly->clut = skyclut[skytexnum];
		poly->tpage = skytpage[skytexnum];

		addPrim(current->ot + 0x107f, poly);

#ifdef PGXP
		poly->pgxp_index = 0xFFFF;
#endif 

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
	
#ifdef PGXP
	DVECTORF *dv0;
	DVECTORF *dv1;
	DVECTORF *dv2;
#else
	DVECTOR *dv0;
	DVECTOR *dv1;
	DVECTOR *dv2;
#endif

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

		dv0 = scratchPad_skyVertices;
		dv1 = scratchPad_skyVertices + 1;
		dv2 = scratchPad_skyVertices + 2;

		v0 = pSVar6;
		v1 = pSVar6 + 1;
		v2 = pSVar6 + 2;

		do {
			SVECTOR sv0 = *v0;
			SVECTOR sv1 = *v1;
			SVECTOR sv2 = *v2;

			sv0.vy -= sky_y_offset[GameLevel];
			sv1.vy -= sky_y_offset[GameLevel];
			sv2.vy -= sky_y_offset[GameLevel];

			gte_ldv3(&sv0, &sv1, &sv2);
			gte_rtpt();
			gte_stsxy3(dv0, dv1, dv2);

			gte_stszotz(&z);

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
		} while (iVar13 < model->num_vertices + 3);
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

				PlotSkyPoly(bVar1, uVar17, uVar16, uVar4, 0);

				iVar13 = iVar13 + 1;
				pbVar14 = pbVar14 + PolySizes[*pbVar14];
			} while (iVar13 < model->num_polys);
		}
	}
}





