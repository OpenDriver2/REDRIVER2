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
	{0, 0, 20, 20},
	{20, 20, 0, 0},
	{0, 0, 20, 20},
	{0, 0, 20, 20},
};

unsigned char HorizonTextures[40] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	0, 1, 2, 3, 4, 5, 6, 7,
	20, 21, 22, 23, 24, 25, 26, 27,
	16, 17, 18, 19
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
		{0,0,90},16, 48
	},
	{
		{80,40,4},48,72
	},
	{
		{90,0,0},48,96
	},
	{
		{0,90,0},16,144
	},
	{
		{0,0,90},64,160
	},
	{
		{90,90,0},32,184
	},
	{
		{90,0,0},32,208
	},
	{
		{0,0,90},48,15
	}
};

VECTOR tunnelPos[3][2] =
{
	{
		{ -398650, 0, -161000, 0 },
		{ -340300, 2000, -103000, 0 }
	},
	{
		{ 272800, 0, 41200, 0 },
		{ 271963, 2000, 168187, 0 }
	},

	{
		{ -115100, 0, -193200, 0 },
		{ -113300, -400, -132501, 0 }
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

// [D] [T]
void LoadSky(void)
{
	int skyNum;
	RECT16 rect;
	char name[16];
	int offset;

	int flipped;
	int single;

	int v;
	int u;
	int y;
	int x;
	int ry;
	int i;

	int tp_x;
	int clut_x;

	i = 0;
	y = 0;
	offset = 0;
	flipped = 1;

	do {
		if (flipped) 
		{
			switch(y)
			{
				default:
					ry = 0;
					flipped = 0;
					single = 1;
					break;
				case 1:
					ry = 0;
					flipped = 0;
					single = 0;
					break;
				case 2:
					ry = 1;
					flipped = 0;
					single = 0;
					break;
				case 3:
					ry = 1;
					flipped = 1;
					single = 0;
					break;
				case 4:
					ry = 0;
					flipped = 1;
					single = 0;
					break;
				case 5:
					ry = 2;
					flipped = 0;
					single = 0;
					break;
				case 6:
					ry = 2;
					flipped = 1;
					single = 0;
					break;
			}
		}
		else
		{
			ry = 0;
			flipped = 0;
			single = 1;
		}

		x = 0;
		y++;

		clut_x = 320;
		tp_x = 320;

		v = ry * 84;

		do {
			u = x * 128;
		
			if (single)
			{
				skytexuv[i].u0 = u;
				skytexuv[i].v0 = v;
				skytexuv[i].u1 = u;
				skytexuv[i].v1 = v;
				skytexuv[i].u2 = u;
				skytexuv[i].v2 = v;
				skytexuv[i].u3 = u;
				skytexuv[i].v3 = v;
			}
			else if (flipped) 
			{
				skytexuv[i].u0 = u;
				skytexuv[i].v0 = v + 83;
				skytexuv[i].u1 = u + 127;
				skytexuv[i].v1 = v + 83;
				skytexuv[i].u2 = u;
				skytexuv[i].v2 = v;
				skytexuv[i].u3 = u + 127;
				skytexuv[i].v3 = v;
			}
			else
			{
				skytexuv[i].u0 = u;
				skytexuv[i].v0 = v;
				skytexuv[i].u1 = u + 127;
				skytexuv[i].v1 = v;
				skytexuv[i].u2 = u;
				skytexuv[i].v2 = v + 83;
				skytexuv[i].u3 = u + 127;
				skytexuv[i].v3 = v + 83;
			}
	
			skytpage[i] = GetTPage(0,0,tp_x & 0xffffffc0,ry * 84 & 768);
			skyclut[i] = GetClut(clut_x,ry + 252);

			tp_x += 32;
			clut_x += 16;

			x++;
			i++;
		} while (x < 4);
	
		flipped = (y < 7);
		
	} while (y < 7);

	if (GameLevel == 1)
		skyNum = 1;
	else if (GameLevel == 2)
		skyNum = 2;
	else if (GameLevel == 3)
		skyNum = 3;
	else
		skyNum = 0;

	if (gWeather - 1U < 2)
	{
		if (gTimeOfDay == 3)
			offset = 0x10000;
		else
			offset = 0x20000;
	}
	else
	{
		if (gTimeOfDay == 0)
			offset = 0x30000;
		else if (gTimeOfDay == 1)
			offset = 0;
		else if (gTimeOfDay == 2)
			offset = 0x40000;
		else if (gTimeOfDay == 3)
			offset = 0x10000;
	}

	sprintf(name, "DATA\\SKY%d.RAW", skyNum);
	LoadfileSeg(name, _frontend_buffer, offset, 0x10000);

	rect.x = 320;
	rect.y = 0;
	rect.w = 128;
	rect.h = 256;

	LoadImage(&rect, (u_long*)_frontend_buffer);

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

// [D] [T]
void DrawSkyDome(void)
{
	calc_sky_brightness();

	if (((camera_angle.vy - 1450U) & 0xFFF) > 2250)
		PlotHorizonMDL(modelpointers[0],HorizonLookup[GameLevel][0]);

	if (((camera_angle.vy - 651U) & 0xFFF) < 1799)
		PlotHorizonMDL(modelpointers[2],HorizonLookup[GameLevel][1]);

	if (((camera_angle.vy - 1701U) & 0xFFF) < 1749)
		PlotHorizonMDL(modelpointers[3],HorizonLookup[GameLevel][2]);

	if (((camera_angle.vy - 400U) & 0xFFF) > 2300)
		PlotHorizonMDL(modelpointers[1],HorizonLookup[GameLevel][3]);

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

// [D] [T]
#ifdef PGXP
void DisplaySun(DVECTORF* pos, CVECTOR* col, int flare_col)
#else
void DisplaySun(DVECTOR* pos, CVECTOR* col, int flare_col)
#endif
{
	short cs;
	short sn;
	int sz;

	POLY_FT4* polys;
	POLY_FT3* null;

	int u1;
	int v2;
	int u0;
	int v0;

	short width;
	short height;

	u0 = sun_texture.coords.u0;
	u1 = sun_texture.coords.u1;
	v0 = sun_texture.coords.v0;
	v2 = sun_texture.coords.v2;

	null = (POLY_FT3*)current->primptr;
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

	width = (((u1 - (u0 - 1)) / 2) * 3) / 4;
	height = (((v2 - (v0 - 1)) / 2) * 3) / 4;

	polys->x0 = pos->vx - width;
	polys->y0 = pos->vy - height;
	polys->x1 = pos->vx + width;
	polys->y1 = pos->vy - height;
	polys->x2 = pos->vx - width;
	polys->y2 = pos->vy + height;
	polys->x3 = pos->vx + width;
	polys->y3 = pos->vy + height;

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

	cs = rcossin_tbl[(camera_angle.vy & 0x1ffe) + 1];
	sn = rcossin_tbl[camera_angle.vy & 0x1ffe];

	sz = -(((flare_texture.coords.u1 - (flare_texture.coords.u0 - 1)) / 2) * 3) / 4;

	polys = (POLY_FT4*)current->primptr;
	setPolyFT4(polys);
	setSemiTrans(polys, 1);

	polys->r0 = (flare_col / 2);
	polys->g0 = (flare_col / 2);
	polys->b0 = (flare_col / 2);

	width = (cs - sn) * sz >> 0xc;
	height = (sn + cs) * sz >> 0xc;

	polys->x0 = pos->vx + width;
	polys->y0 = pos->vy + height;
	polys->x1 = pos->vx - height;
	polys->y1 = pos->vy + width;
	polys->x2 = pos->vx + height;
	polys->y2 = pos->vy - width;
	polys->x3 = pos->vx - width;
	polys->y3 = pos->vy - height;
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

// [D] [T]
#ifdef PGXP
void DisplayMoon(DVECTORF* pos, CVECTOR* col, int flip)
#else
void DisplayMoon(DVECTOR* pos, CVECTOR* col, int flip)
#endif
{
	short width;
	short height;
	
	POLY_FT3* null;
	POLY_FT4* polys;
	
	null = (POLY_FT3*)current->primptr;
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

	width = (moon_texture.coords.u1 - (moon_texture.coords.u0 - 1)) / 2;
	height = (moon_texture.coords.v2 - (moon_texture.coords.v0 - 1)) / 2;

	if (flip != 0)
		height = -height;

	polys->x0 = pos->vx - width;
	polys->y0 = pos->vy - height;
	polys->x1 = pos->vx + width;
	polys->y1 = pos->vy - height;
	polys->x2 = pos->vx - width;
	polys->y2 = pos->vy + height;
	polys->x3 = pos->vx + width;
	polys->y3 = pos->vy + height;

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

// [D] [T]
void DrawLensFlare(void)
{
	static char last_attempt_failed; // offset 0x0
	static short buffer[160];

	int flarez;
	long distance_to_sun;
	int bufferY;
	int bufferX;
	POLY_FT4 *poly;
	FLAREREC *pFlareInfo;
	int shade;
	short *pwBuffer;
	DR_MOVE* sample_sun;
	int ygap;
	int xgap;
	int flare_col;
	int flaresize;
	
	int haze_col;

#ifdef PGXP
	DVECTORF sun_pers_conv_position;
#else
	DVECTOR sun_pers_conv_position;
#endif
	
	RECT16 source;
	CVECTOR col;

	source = {
		1008,
		456,
		16,
		10
	};

	if (gWeather - 1U <= 1 || gTimeOfDay == 0 || gTimeOfDay == 2)
		return;
	
	if (gTimeOfDay == 3)
		col.r = 128;
	else
		col.r = 254;

	flare_col = 0;

	col.g = col.r;
	col.b = col.r;

	// get the sun brightness from framebuffer copy
	if (gTimeOfDay != 3 && last_attempt_failed == 0)
	{
		pwBuffer = buffer;
		StoreImage(&source, (u_long*)buffer);
		bufferY = 0;
		do
		{
			bufferY++;
			bufferX = 0;

			do
			{

				if (*pwBuffer == -1 || *pwBuffer == 0x7fff)
					flare_col++;

				bufferX++;
				pwBuffer++;
			}
			while (bufferX < 12);

			pwBuffer += 5;
		}
		while (bufferY < 10);
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

	gte_stszotz(&flarez);
	
	xgap = sun_pers_conv_position.vx - 160;
	ygap = sun_pers_conv_position.vy - 128;

	//sun_pers_conv_position.vy = (short)((uint)sun_pers_conv_position >> 0x10);
	
	distance_to_sun = SquareRoot0(xgap * xgap + ygap * ygap);

	if (gTimeOfDay == 3)
	{
		if (distance_to_sun < 500)
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
		if (flarez > 0 && distance_to_sun < 500)
		{
			DisplaySun(&sun_pers_conv_position, &col, flare_col);
			
			haze_col = (60 - (distance_to_sun / 2)) * flare_col;
			
			add_haze((haze_col / 6 + (haze_col >> 0x1f) >> 3) - (haze_col >> 0x1f), haze_col >> 6, 7);
			shade = flare_col / 3 - (distance_to_sun * 80) / 500;
	
			if (shade > -1 && flare_col != 0)
			{
				pFlareInfo = flare_info;
				
				do
				{
					int xpos, ypos, gapmod;
					
					gapmod = (128 - pFlareInfo->gapmod) * 2;
					flaresize = (pFlareInfo->size / 2);
					
					xpos = (xgap * gapmod) / 256;
					ypos = (ygap * gapmod) / 256;

					poly = (POLY_FT4*)current->primptr;
					setPolyFT4(poly);
					setSemiTrans(poly, 1);

					poly->x0 = poly->x2 = (xpos + 160) - flaresize;
					poly->y0 = poly->y1 = (ypos + 128) - flaresize;

					poly->x1 = poly->x3 = poly->x0 + pFlareInfo->size;
					poly->y2 = poly->y3 = poly->y0 + pFlareInfo->size;

					poly->r0 = (pFlareInfo->transparency.r * shade >> 6);
					poly->g0 = (pFlareInfo->transparency.g * shade >> 6);
					poly->b0 = (pFlareInfo->transparency.b * shade >> 6);
					
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
				}
				while (pFlareInfo < flare_info + 8);
			}
		}
		sun_pers_conv_position.vx = sun_pers_conv_position.vx + -8;
		sun_pers_conv_position.vy = sun_pers_conv_position.vy + -4;

		// store framebuffer image of sun separately in VRAM
		if (sun_pers_conv_position.vx > -1 && 
			sun_pers_conv_position.vy > -1 &&
			sun_pers_conv_position.vx + 16 < 321 &&
			sun_pers_conv_position.vy + 10 < 257)
		{
			last_attempt_failed = 0;


			source.x = sun_pers_conv_position.vx;
			source.y = sun_pers_conv_position.vy + last->disp.disp.y;

			sample_sun = (DR_MOVE*)current->primptr;
			SetDrawMove(sample_sun, &source, 1008, 456);

			addPrim(current->ot + 0x20, sample_sun);
			current->primptr += sizeof(DR_MOVE);
		}
		else
		{
			last_attempt_failed = 1;
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
static long skyred = 128;
static long skygreen = 128;
static long skyblue = 128;

int tunnelDir[3][2] =
{
	{2000, 3064},
	{2048, 0},
	{2048, 4095}
};

// [D] [T]
void TunnelSkyFade(void)
{
	int dZ;
	int diffZ;
	int dX;
	int diffX;
	int l2;
	int len;
	VECTOR* v2;
	VECTOR* v1;
	int tun;

	if (GameLevel != 3)
		tun = gTunnelNum;
	else
		tun = 2;

	if (gTunnelNum == -1)
		return;

	v1 = NULL;
	v2 = NULL;

	if (((tunnelDir[tun][0] - camera_angle.vy) + 0x800U & 0xfff) - 801 < 2495)
		v1 = &tunnelPos[tun][0];

	if (((tunnelDir[tun][1] - camera_angle.vy) + 0x800U & 0xfff) - 801 < 2495)
		v2 = &tunnelPos[tun][1];

	if(v1 && v2)
	{
		dX = (v1->vx - player[0].pos[0]) >> 5;		// [A] smooth sky fade
		dZ = (v1->vz - player[0].pos[2]) >> 5;

		diffX = (v2->vx - player[0].pos[0]) >> 5;
		diffZ = (v2->vz - player[0].pos[2]) >> 5;

		len = (dX * dX + dZ * dZ);
		l2 = (diffX * diffX + diffZ * diffZ);

		if (l2 <= len)
			len = l2;
	}
	else if(v2)
	{
		diffX = (v2->vx - player[0].pos[0]) >> 5;
		diffZ = (v2->vz - player[0].pos[2]) >> 5;

		len = (diffX * diffX + diffZ * diffZ);
	}
	else if(v1)
	{
		diffX = (v1->vx - player[0].pos[0]) >> 5;
		diffZ = (v1->vz - player[0].pos[2]) >> 5;

		len = (diffX * diffX + diffZ * diffZ);
	}
	else
	{
		skyFade = 0;
		return;
	}

	// [A] smooth sky fade
	len >>= 12;

	if (len <= 128)
		skyFade = -len + 128;
	else
		skyFade = 0;
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

// [D] [T]
void calc_sky_brightness(void)
{
	int dawn;
	
#ifdef PSX
	if(gTimeOfDay == 0 || gTimeOfDay == 2)
#else
	if (DawnCount != 0)
#endif
	{
		dawn = DawnCount >> 5;

		if (gTimeOfDay == 0)
		{
			skyred = dawn + 41;
			skyblue = dawn + 28;
		}
		else if (gTimeOfDay == 2)
		{
			skyred = 143 - dawn;
			skyblue = 128 - dawn;
		}
#if !defined(PSX)
		else if (gTimeOfDay == 1)
		{
			if (day_vectors[GameLevel].vx < 0)
			{
				skyred = dawn + 41;
				skyblue = dawn + 28;
			}
			else
			{
				if (skyred > 26)
					skyred -= dawn;
			}
		}
#endif
		if (skyred < 26)
			skyred = 26;
		else if (skyred > 128)
			skyred = 128;

		if (skyblue < 26)
			skyblue = 26;
		else if (skyblue > 128)
			skyblue = 128;

		skygreen = skyblue;
	}
	else
	{
		skyblue = 128;
		skygreen = 128;
		skyred = 128;
	}
	
	if (gTunnelNum == -1 || 
		GameLevel == 0 ||
		GameLevel == 1 && gTunnelNum == 2 ||
		GameLevel == 2 ||
		GameLevel == 3 && gTunnelNum != 1)
		return;

	TunnelSkyFade();

	if (skyred > skyFade)
		skyred = skyFade;

	if (skygreen > skyFade)
		skygreen = skyFade;

	if (skyblue > skyFade)
		skyblue = skyFade;
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

// [D] [T]
void PlotSkyPoly(int skytexnum, unsigned char r, unsigned char g, unsigned char b, int offset)
{
	POLYFT4* src;
	POLY_FT4* poly;

	src = scratchPad_skyPolygonsPtr;
	poly = (POLY_FT4*)current->primptr;

#ifdef PGXP
	DVECTORF* outpoints = scratchPad_skyVertices;
#else
	DVECTOR* outpoints = scratchPad_skyVertices;
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

		*(uint*)&poly->x0 = *(uint*)&outpoints[src->v0].vx;
		*(uint*)&poly->x1 = *(uint*)&outpoints[src->v1].vx;
		*(uint*)&poly->x2 = *(uint*)&outpoints[src->v3].vx;
		*(uint*)&poly->x3 = *(uint*)&outpoints[src->v2].vx;
	
		*(ushort*)&poly->u0 = *(ushort*)&skytexuv[skytexnum].u2;
		*(ushort*)&poly->u1 = *(ushort*)&skytexuv[skytexnum].u3;
		*(ushort*)&poly->u2 = *(ushort*)&skytexuv[skytexnum].u0;
		*(ushort*)&poly->u3 = *(ushort*)&skytexuv[skytexnum].u1;
		
		poly->clut = skyclut[skytexnum];
		poly->tpage = skytpage[skytexnum];

		addPrim(current->ot + 0x107f, poly);

#ifdef PGXP
		poly->pgxp_index = 0xFFFF;
#endif 

		current->primptr += sizeof(POLY_FT4);
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

// [D] [T]
void PlotHorizonMDL(MODEL* model, int horizontaboffset)
{
	SVECTOR* verts;

#ifdef PGXP
	DVECTORF* dv0;
	DVECTORF* dv1;
	DVECTORF* dv2;
#else
	DVECTOR* dv0;
	DVECTOR* dv1;
	DVECTOR* dv2;
#endif

	SVECTOR* v0;
	SVECTOR* v1;
	SVECTOR* v2;

	int count;

	unsigned char* polys;

	int green;
	int red;
	int blue;

	short* zbuff;
	int z;

	verts = (SVECTOR*)model->vertices;
	blue = (uint)model->num_vertices + 3;

	count = 0;

	if (blue != 0)
	{
		zbuff = scratchPad_zbuff;

		dv0 = scratchPad_skyVertices;
		dv1 = scratchPad_skyVertices + 1;
		dv2 = scratchPad_skyVertices + 2;

		v0 = verts;
		v1 = verts + 1;
		v2 = verts + 2;

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

			count += 3;

			zbuff[2] = z;
			zbuff[1] = z;
			zbuff[0] = z;

			zbuff += 3;
		} while (count < model->num_vertices + 3);
	}

	if (scratchPad_zbuff[16] > 0)
	{
		polys = (unsigned char*)model->poly_block;

		red = skyred;
		green = skygreen;
		blue = skyblue;
		
		count = 0;

		while (count < model->num_polys)
		{
			if (count == 12)
			{
				red /= 2;
				green /= 2;
				blue /= 2;
			}
			
			scratchPad_skyPolygonsPtr = (POLYFT4*)polys;

			PlotSkyPoly(HorizonTextures[horizontaboffset + count], red, green, blue, 0);

			polys += PolySizes[*polys];
			count++;
		}
	}
}





