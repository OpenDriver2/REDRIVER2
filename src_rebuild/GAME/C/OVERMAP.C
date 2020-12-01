#include "DRIVER2.H"
#include "OVERMAP.H"
#include "TEXTURE.H"
#include "CARS.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "MDRAW.H"
#include "PLAYERS.H"
#include "OVERLAY.H"
#include "DEBRIS.H"
#include "MAP.H"
#include "CONVERT.H"
#include "DRAW.H"
#include "PRES.H"
#include "COP_AI.H"
#include "CAMERA.H"
#include "FELONY.H"
#include "PAD.H"
#include "../ASM/RNC_2.H"

#include "STRINGS.H"
#include "INLINE_C.H"


OVERMAP overlaidmaps[4] =
{
	{ 197, 318, 384, 672, 252, 153, 2145 },
	{ 229, 85, 544, 352, 187, 136, 2048 },
	{ 68, 457, 288, 672, 189, 187, 1911 },
	{ 159, 207, 416, 576, 252, 68, 2048 }
};

SXYPAIR MapSegmentPos[16] =
{
	{ 0, 0 },
	{ 8, 0 },
	{ 16, 0 },
	{ 24, 0 },
	{ 0, 32 },
	{ 8, 32 },
	{ 16, 32 },
	{ 24, 32 },
	{ 0, 64 },
	{ 8, 64 },
	{ 16, 64 },
	{ 24, 64 },
	{ 0, 96 },
	{ 8, 96 },
	{ 16, 96 },
	{ 24, 96 }
};

XYPAIR NVertex[4] = { 
	{ -2, 3 }, 
	{ -2, -3 }, 
	{ 2, 3 }, 
	{ 2, -3 } 
};

XYPAIR north[4] = { 
	{ 0, 20 },
	{ 0, 20 }, 
	{ 0, 20 }, 
	{ 0, 20 } 
};

static short big_north[] =
{
	2048,
	2048,
	2048,
	2048
};

VECTOR player_position = { 0, 0, 0, 0 };


MATRIX map_matrix;

char* MapBitMaps;
static char MapBuffer[520];
static unsigned short MapClut;
static RECT16 MapRect;

static int tilehnum = 0;
static char maptile[4][4];
static char tile_size = 0x20;

static int old_x_mod = 0;
static int old_y_mod = 0;

static int x_map = 0;
static int y_map = 0;

static int map_x_offset = 0;
static int map_z_offset = 0;
int map_x_shift = 0;
int map_z_shift = 0;


static unsigned short MapTPage = 0;

static int gUseRotatedMap = 0;

int gMapXOffset = 249;
int gMapYOffset = 181;

// decompiled code
// original method signature: 
// void /*$ra*/ DrawTargetBlip(VECTOR *pos /*$t0*/, unsigned char r /*$s2*/, unsigned char g /*$s3*/, unsigned char b /*$s4*/, unsigned long flags /*stack 16*/)
 // line 685, offset 0x00016280
	/* begin block 1 */
		// Start line: 686
		// Start offset: 0x00016280
		// Variables:
	// 		POLY_FT4 *poly; // $t0
	// 		VECTOR vec; // stack offset -40
	// 		int ysize; // $a2
	/* end block 1 */
	// End offset: 0x00016558
	// End Line: 759

	/* begin block 2 */
		// Start line: 1370
	/* end block 2 */
	// End Line: 1371

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void DrawTargetBlip(VECTOR *pos, unsigned char r, unsigned char g, unsigned char b, ulong flags)
{
	int ysize;
	POLY_FT4 *poly;
	VECTOR vec;

	int map_minX, map_maxX;
	int map_minY, map_maxY;
	
	map_minX = gMapXOffset;
	map_maxX = gMapXOffset + MAP_SIZE_W;
	map_minY = gMapYOffset;
	map_maxY = gMapYOffset + MAP_SIZE_H;

	if (flags & 0x20) 
	{
		WorldToMultiplayerMap(pos, &vec);

		vec.vx += gMapXOffset;
		vec.vz += 96;
	}
	else if (flags & 0x8)
	{
		vec.vx = pos->vx;
		vec.vz = pos->vz;
	}
	else if (flags & 0x1)
	{
		WorldToOverheadMapPositions(pos, &vec, 1, 0, 0);

		if (vec.vx <= map_minX || vec.vx >= map_maxX || vec.vz <= map_minY || vec.vz >= map_maxY)
		{
			return;
		}
	}
	else 
	{
		WorldToFullscreenMap2(pos, &vec);
	}

	if ((flags & 1) == 0) 
	{
		vec.vx += map_x_offset;
		vec.vz += map_z_offset;
	}

	if (flags & 0x10) 
		ysize = OverlayFlashValue / 2;
	else if (flags & 0x2) 
		ysize = 3;
	else
		ysize = 4;

	poly = (POLY_FT4 *)current->primptr;

	setPolyFT4(poly);
	setSemiTrans(poly, 1);

	poly->x0 = vec.vx - ysize;
	poly->y0 = vec.vz - ysize;

	poly->x1 = vec.vx + ysize;
	poly->y1 = vec.vz - ysize;

	poly->x2 = vec.vx - ysize;
	poly->y2 = vec.vz + ysize;

	poly->x3 = vec.vx + ysize;
	poly->y3 = vec.vz + ysize;

	poly->r0 = r;
	poly->g0 = g;
	poly->b0 = b;
	
	*(ushort*)&poly->u0 = *(ushort*)&light_texture.coords.u0;
	*(ushort*)&poly->u1 = *(ushort*)&light_texture.coords.u1;
	*(ushort*)&poly->u2 = *(ushort*)&light_texture.coords.u2;
	*(ushort*)&poly->u3 = *(ushort*)&light_texture.coords.u3;

	if (flags & 0x2)
		poly->tpage = light_texture.tpageid | 0x40;
	else
		poly->tpage = light_texture.tpageid | 0x20;

	poly->clut = light_texture.clutid;

	if (flags & 0x4)
	{
		// fullscreen map mode
		DrawPrim(poly);
	}
	else
	{
		addPrim(current->ot, poly);
		current->primptr += sizeof(POLY_FT4);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTargetArrow(VECTOR *pos /*$a2*/, unsigned long flags /*$s3*/)
 // line 815, offset 0x00016578
	/* begin block 1 */
		// Start line: 816
		// Start offset: 0x00016578
		// Variables:
	// 		VECTOR vec; // stack offset -56
	// 		VECTOR vec2; // stack offset -40
	// 		POLY_FT3 *null; // $t1
	// 		POLY_G3 *poly; // $s2
	// 		int dx; // $s1
	// 		int dy; // $s0
	/* end block 1 */
	// End offset: 0x00016814
	// End Line: 875

	/* begin block 2 */
		// Start line: 1642
	/* end block 2 */
	// End Line: 1643

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void DrawTargetArrow(VECTOR *pos, ulong flags)
{
	int dy;
	int dx;
	POLY_G3 *poly;
	VECTOR vec;
	VECTOR vec2;

	if (flags & 0x8) 
	{
		vec.vx = pos->vx;
		vec.vz = pos->vz;
	}
	else if (flags & 0x1)
	{
		WorldToOverheadMapPositions(pos, &vec, 1, 0, 0);
	}
	else 
	{
		WorldToFullscreenMap2(pos, &vec);
	}

	if (flags & 0x1) 
	{
		WorldToOverheadMapPositions((VECTOR *)player, &vec2, 1, '\0', 0);
	}
	else 
	{
		vec.vx = vec.vx + map_x_offset;
		vec.vz = vec.vz + map_z_offset;

		vec2.vx = map_x_offset + 160;
		vec2.vz = map_z_offset + 128;
	}

	// target arrow perpendicular
	dx = (vec2.vx - vec.vx) / 8;
	dy = (vec2.vz - vec.vz) / 8;

	poly = (POLY_G3 *)current->primptr;

	setPolyG3(poly);
	setSemiTrans(poly, 1);

	poly->r0 = poly->r1 = 24;
	poly->g0 = poly->g1 = 24;
	poly->b0 = poly->b1 = 24;

	poly->r2 = 64;
	poly->g2 = 64;
	poly->b2 = 64;

	poly->x0 = vec2.vx + dy;
	poly->y0 = vec2.vz - dx;
	
	poly->x1 = vec2.vx - dy;
	poly->y1 = vec2.vz + dx;

	poly->x2 = vec.vx;
	poly->y2 = vec.vz;

	POLY_FT3* null = (POLY_FT3*)(poly + 1);

	setPolyFT3(null);
	setSemiTrans(null, 1);

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;

	null->tpage = 0x40;
	
	if (flags & 0x4)
	{
		// fullscreen map
		DrawPrim(null);
		DrawPrim(poly);
	}
	else
	{
		addPrim(current->ot, poly);
		addPrim(current->ot, null);

		current->primptr += sizeof(POLY_G3) + sizeof(POLY_FT3);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawPlayerDot(VECTOR *pos /*$a1*/, short rot /*$s2*/, unsigned char r /*$s5*/, unsigned char g /*$s4*/, int b /*stack 16*/, unsigned long flags /*stack 20*/)
 // line 883, offset 0x00016814
	/* begin block 1 */
		// Start line: 884
		// Start offset: 0x00016814
		// Variables:
	// 		MATRIX matrix; // stack offset -168
	// 		VECTOR direction; // stack offset -136
	// 		SVECTOR apos[3]; // stack offset -120
	// 		VECTOR opos[3]; // stack offset -96
	// 		POLY_F3 *poly; // $t0
	// 		VECTOR vec; // stack offset -48
	/* end block 1 */
	// End offset: 0x00016AC4
	// End Line: 946

	/* begin block 2 */
		// Start line: 1812
	/* end block 2 */
	// End Line: 1813

	/* begin block 3 */
		// Start line: 1821
	/* end block 3 */
	// End Line: 1822

// [D] [T]
void DrawPlayerDot(VECTOR *pos, short rot, unsigned char r, unsigned char g, int b, ulong flags)
{
	int sn;
	int cs;
	POLY_F3 *poly;
	VECTOR opos[3];
	VECTOR vec;

	if (flags & 0x20) 
	{
		WorldToMultiplayerMap(pos, &vec);
	
		vec.vx += gMapXOffset;
		vec.vz += 96;
	}
	else 
	{
		if (flags & 0x8) 
		{
			vec.vx = pos->vx;
			vec.vz = pos->vz;
		}
		else if (flags & 0x1)
		{
			WorldToOverheadMapPositions(pos, &vec, 1, 0, 0);
			
			if (vec.vx - 233U > 94)
				return;

			if (vec.vz < 174 || vec.vz > 250)
				return;
		}
		else
		{
			WorldToFullscreenMap2(pos, &vec);
		}
	}

	if ((flags & 0x1) == 0) 
	{
		vec.vx += map_x_offset;
		vec.vz += map_z_offset;
	}

	sn = rcossin_tbl[(rot & 0xfffU) * 2];
	cs = rcossin_tbl[(rot & 0xfffU) * 2 + 1];

	opos[2].vx = vec.vx;
	opos[2].vz = vec.vz;

	opos[0].vx = vec.vx + FIXEDH(sn * -3);
	opos[0].vz = vec.vz + FIXEDH(cs * -3);

	opos[1].vx = vec.vx + FIXEDH(sn * 3 + cs * -2);
	opos[1].vz = vec.vz + FIXEDH(cs * 3 + sn * 2);

	opos[2].vx = vec.vx + FIXEDH(cs * 2 + sn * 3);
	opos[2].vz = vec.vz + FIXEDH(sn * -2 + cs * 3);

	poly = (POLY_F3 *)current->primptr;
	setPolyF3(poly);

	poly->r0 = r;
	poly->g0 = g;
	poly->b0 = b;

	poly->x0 = opos[0].vx;
	poly->y0 = opos[0].vz;
	
	poly->x1 = opos[1].vx;
	poly->y1 = opos[1].vz;
	
	poly->x2 = opos[2].vx;
	poly->y2 = opos[2].vz;

	if (flags & 0x4) 
	{
		DrawPrim(poly);
	}
	else 
	{
		addPrim(current->ot, poly);
		current->primptr += sizeof(POLY_F3);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessOverlayLump(char *lump_ptr /*$s1*/, int lump_size /*$s0*/)
 // line 954, offset 0x00016ae8
	/* begin block 1 */
		// Start line: 955
		// Start offset: 0x00016AE8
		// Variables:
	// 		TEXTURE_DETAILS info; // stack offset -32
	// 		int i; // $a1
	// 		int x; // $v0
	// 		int y; // $a0
	/* end block 1 */
	// End offset: 0x00016C0C
	// End Line: 986

	/* begin block 2 */
		// Start line: 1982
	/* end block 2 */
	// End Line: 1983

// [D] [T]
void ProcessOverlayLump(char *lump_ptr, int lump_size)
{
	int i;
	TEXTURE_DETAILS info;

	GetTextureDetails("OVERHEAD", &info);

	MapTPage = info.tpageid;
	MapClut = GetClut(mapclutpos.x, mapclutpos.y);

	MapRect.w = 64;
	MapRect.h = 256;
	MapRect.x = (MapTPage & 15) << 6;
	MapRect.y = (MapTPage & 16) << 4;

	i = 0;
	do {
		MapSegmentPos[i].x = ((i & 3) * 32 + info.coords.u0) / 4;
		MapSegmentPos[i].y = info.coords.v0 + (i / 4) * 32;

		i++;
	} while (i < 16);

	MALLOC_BEGIN()

	MapBitMaps = D_MALLOC(lump_size);
	memcpy(MapBitMaps, lump_ptr, lump_size);

	MALLOC_END();

	// load CLUT
	LoadImage(&mapclutpos, (u_long *)(MapBitMaps + 512));
	DrawSync(0);
}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ Long2DDistance(VECTOR *pPoint1 /*$a0*/, VECTOR *pPoint2 /*$a2*/)
 // line 994, offset 0x00016c0c
	/* begin block 1 */
		// Start line: 995
		// Start offset: 0x00016C0C
		// Variables:
	// 		VECTOR delta; // stack offset -24
	// 		unsigned int result; // $v0

		/* begin block 1.1 */
			// Start line: 1001
			// Start offset: 0x00016C50
			// Variables:
		// 		int Theta; // $v1
		// 		int tempTheta; // $v0

			/* begin block 1.1.1 */
				// Start line: 1009
				// Start offset: 0x00016C70
				// Variables:
			// 		int cos; // $v1
			/* end block 1.1.1 */
			// End offset: 0x00016C9C
			// End Line: 1017

			/* begin block 1.1.2 */
				// Start line: 1022
				// Start offset: 0x00016CA4
				// Variables:
			// 		int sin; // $v1
			/* end block 1.1.2 */
			// End offset: 0x00016D04
			// End Line: 1032
		/* end block 1.1 */
		// End offset: 0x00016D04
		// End Line: 1033
	/* end block 1 */
	// End offset: 0x00016D14
	// End Line: 1036

	/* begin block 2 */
		// Start line: 2090
	/* end block 2 */
	// End Line: 2091

	/* begin block 3 */
		// Start line: 2099
	/* end block 3 */
	// End Line: 2100

// [D] [T]
ulong Long2DDistance(VECTOR *pPoint1, VECTOR *pPoint2)
{
	int tempTheta;
	int theta;
	ulong result;
	VECTOR delta;

	delta.vx = ABS(pPoint1->vx - pPoint2->vx);
	delta.vz = ABS(pPoint1->vz - pPoint2->vz);

	theta = ratan2(delta.vz, delta.vx);

	if ((theta & 0x7ff) - 512U <= 1024)
	{
		tempTheta = rcossin_tbl[(theta & 0xfff) * 2];
		result = delta.vz;
	}
	else 
	{
		tempTheta = rcossin_tbl[(theta & 0xfff) * 2 + 1];
		result = delta.vx;
	}

	if (result < 0x80000) 
		result = (result << 12) / tempTheta;
	else 
		result = (result << 9) / tempTheta << 3;

	return result;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitOverheadMap()
 // line 1043, offset 0x000197bc
	/* begin block 1 */
		// Start line: 1045
		// Start offset: 0x000197BC
		// Variables:
	// 		int tpage; // $s3
	// 		int c; // $s2
	// 		int d; // $s1
	/* end block 1 */
	// End offset: 0x000198BC
	// End Line: 1070

	/* begin block 2 */
		// Start line: 2086
	/* end block 2 */
	// End Line: 2087

	/* begin block 3 */
		// Start line: 5402
	/* end block 3 */
	// End Line: 5403

	/* begin block 4 */
		// Start line: 5405
	/* end block 4 */
	// End Line: 5406

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitOverheadMap(void)
{
	int d;
	int c;
	int tpage;

	if (gMultiplayerLevels) 
	{
		InitMultiplayerMap();
		return;
	}

	SetMapPos();
	tilehnum = overlaidmaps[GameLevel].width / 32;

	tpage = 0;
	
	for (c = 0; c < 4; c++) 
	{
		for (d = 0; d < 4; d++)
		{
			maptile[d][c] = tpage;

			LoadMapTile(tpage, (x_map >> 5) + d, (y_map >> 5) + c);
			tpage++;
		}
	}

	old_x_mod = x_map & 0x1f;
	old_y_mod = y_map & 0x1f;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawOverheadMap()
 // line 1077, offset 0x00016d14
	/* begin block 1 */
		// Start line: 1079
		// Start offset: 0x00016D14
		// Variables:
	// 		int width; // $t5
	// 		int height; // $t4
	// 		int count; // $s2
	// 		int count1; // $s3
	// 		int tpage; // $t1
	// 		int x_mod; // $s5
	// 		int y_mod; // $fp
	// 		int MeshWidth; // $s6
	// 		int MeshHeight; // $s7
	// 		long flag; // stack offset -104
	// 		SVECTOR MapMesh[5][5]; // stack offset -784
	// 		VECTOR MapMeshO[5][5]; // stack offset -584
	// 		MAPTEX MapTex[4]; // stack offset -184
	// 		SVECTOR direction; // stack offset -152
	// 		POLY_FT4 *spt; // $a3
	// 		POLY_F4 *sptb; // $a0
	// 		DR_AREA *draw_area; // $s2
	// 		RECT clipped_size; // stack offset -144
	// 		VECTOR translate; // stack offset -136

		/* begin block 1.1 */
			// Start line: 1112
			// Start offset: 0x00016E24
			// Variables:
		// 		static int ptab[16]; // offset 0x118
		/* end block 1.1 */
		// End offset: 0x00016E24
		// End Line: 1113

		/* begin block 1.2 */
			// Start line: 1125
			// Start offset: 0x00016EF8
			// Variables:
		// 		static int ptab[12]; // offset 0x158
		// 		int intens; // $a1
		/* end block 1.2 */
		// End offset: 0x00016FA8
		// End Line: 1135

		/* begin block 1.3 */
			// Start line: 1139
			// Start offset: 0x00016FA8

			/* begin block 1.3.1 */
				// Start line: 1139
				// Start offset: 0x00016FA8
				// Variables:
			// 		VECTOR vec; // stack offset -120
			// 		TILE_1 *tile1; // $a0
			/* end block 1.3.1 */
			// End offset: 0x000170F4
			// End Line: 1142
		/* end block 1.3 */
		// End offset: 0x000170F4
		// End Line: 1142

		/* begin block 1.4 */
			// Start line: 1146
			// Start offset: 0x000170F4
			// Variables:
		// 		CAR_DATA *cp; // $s0
		/* end block 1.4 */
		// End offset: 0x00017218
		// End Line: 1161

		/* begin block 1.5 */
			// Start line: 1168
			// Start offset: 0x00017240
		/* end block 1.5 */
		// End offset: 0x00017240
		// End Line: 1170

		/* begin block 1.6 */
			// Start line: 1185
			// Start offset: 0x000172C0
		/* end block 1.6 */
		// End offset: 0x000172C0
		// End Line: 1187

		/* begin block 1.7 */
			// Start line: 1202
			// Start offset: 0x0001734C
		/* end block 1.7 */
		// End offset: 0x0001734C
		// End Line: 1204

		/* begin block 1.8 */
			// Start line: 1219
			// Start offset: 0x000173E0
		/* end block 1.8 */
		// End offset: 0x000173E0
		// End Line: 1221
	/* end block 1 */
	// End offset: 0x00017C00
	// End Line: 1367

	/* begin block 2 */
		// Start line: 2231
	/* end block 2 */
	// End Line: 2232

	/* begin block 3 */
		// Start line: 2273
	/* end block 3 */
	// End Line: 2274

	/* begin block 4 */
		// Start line: 2274
	/* end block 4 */
	// End Line: 2275

	/* begin block 5 */
		// Start line: 2286
	/* end block 5 */
	// End Line: 2287

/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawOverheadMap(void)
{
	u_char tmp;
	short *playerFelony;
	TILE_1 *tile1;
	POLY_F4 *sptb;
	POLY_FT4 *spt;
	POLY_FT3 *null;
	CAR_DATA *cp;
	DR_AREA *drarea;
	int intens;
	SVECTOR MapMesh[5][5];
	VECTOR MapMeshO[5][5];
	MAPTEX MapTex[4];
	SVECTOR direction;
	RECT16 clipped_size;
	VECTOR vec;
	long flag;
	int i, j;
	int width; 
	int height;
	int x_mod;
	int y_mod;
	int MeshWidth;
	int MeshHeight;
	int map_minX, map_maxX;
	int map_minY, map_maxY;

	static int flashtimer = 0;
	static u_char ptab[] = {
		255, 240, 170, 120,
		80, 55, 38, 23,
		13,  10,  0,  0,
		0,  0,  0,  0,
	};

	static u_char ptab2[] = {
		255, 255, 240, 170,
		120, 80, 55, 38,
		23, 13,  10,  0, 
		0
	};

	map_minX = gMapXOffset;
	map_maxX = gMapXOffset + MAP_SIZE_W;
	map_minY = gMapYOffset;
	map_maxY = gMapYOffset + MAP_SIZE_H;

	VECTOR translate = {
		map_minX + MAP_SIZE_W/2,
		0,
		map_minY + MAP_SIZE_H/2
	};

	if (gMultiplayerLevels)
	{
		DrawMultiplayerMap();
		return;
	}

	if (NumPlayers > 1)
		return;

	SetMapPos();	
	draw_box(map_minY, MAP_SIZE_H);

	// flash the overhead map
	if (player_position_known > 0) 
	{
		if (player[0].playerCarId < 0)
			playerFelony = &pedestrianFelony;
		else 
			playerFelony = &car_data[player[0].playerCarId].felonyRating;

		if (*playerFelony > FELONY_MIN_VALUE)
			FlashOverheadMap(ptab[CameraCnt & 0xf], 0, ptab[CameraCnt + 8U & 0xf]);
	}
	else 
	{
		if (player_position_known == -1)
		{
			if (flashtimer == 0)
			{
				if (player[0].playerCarId < 0) 
					playerFelony = &pedestrianFelony;
				else
					playerFelony = &car_data[player[0].playerCarId].felonyRating;

				if (*playerFelony > FELONY_MIN_VALUE)
					flashtimer = 48;
			}
		}
		
		if (flashtimer)
		{
			flashtimer--;
			intens = -flashtimer;

			intens = ptab2[intens + 47 >> 2] + ptab2[intens + 48 >> 2] + ptab2[intens + 49 >> 2] + ptab2[intens + 50 >> 2] >> 2;
			FlashOverheadMap(intens, intens, intens);
		}
	}

	// for restoring
	drarea = (DR_AREA *)current->primptr;
	SetDrawArea(drarea, &current->draw.clip);

	addPrim(current->ot, drarea);
	current->primptr += sizeof(DR_AREA);

	WorldToOverheadMapPositions((VECTOR *)player->pos, &vec, 1, 0, 0);

	// draw map center
	if (vec.vx > map_minX && vec.vx < map_maxX && vec.vz > map_minY && vec.vz < map_maxY) 
	{
		tile1 = (TILE_1 *)current->primptr;
		setTile1(tile1);

		tile1->r0 = 255;
		tile1->g0 = 255;
		tile1->b0 = 255;

		tile1->x0 = vec.vx;
		tile1->y0 = vec.vz;

		addPrim(current->ot, tile1);
		current->primptr += sizeof(TILE_1);
	}

	DrawTargetBlip((VECTOR *)player->pos, 64, 64, 64, 3);
	
	DrawCompass();

	DrawOverheadTargets();

	// draw cop sight
	cp = car_data;
	do {
		if (cp->controlType == CONTROL_TYPE_PURSUER_AI && cp->ai.p.dying == 0 || (cp->controlFlags & CONTROL_FLAG_COP))
			DrawSightCone(&copSightData, (VECTOR *)cp->hd.where.t, cp->hd.direction);

		cp++;
	} while (cp <= &car_data[MAX_CARS]);

	x_mod = x_map & 31;
	y_mod = y_map & 31;

	// next code loads map tiles depending on player position changes
	
	// X axis
	if (x_mod < 16 && old_x_mod > 16)
	{
		// left
		for (i = 0; i < 4; i++)
		{
			tmp = maptile[0][i];

			maptile[0][i] = maptile[1][i];
			maptile[1][i] = maptile[2][i];
			maptile[2][i] = maptile[3][i];
			maptile[3][i] = tmp;

			LoadMapTile(tmp, (x_map >> 5) + 3, (y_map >> 5) + i);
		}
	}

	if (x_mod > 16 && old_x_mod < 16) 
	{
		// right
		for (i = 0; i < 4; i++)
		{
			tmp = maptile[3][i];

			maptile[3][i] = maptile[2][i];
			maptile[2][i] = maptile[1][i];
			maptile[1][i] = maptile[0][i];
			maptile[0][i] = tmp;

			LoadMapTile(tmp, (x_map >> 5), (y_map >> 5) + i);
		}
	}

	// Z axis
	if (y_mod < 16 && old_y_mod > 16)
	{
		// down
		for (i = 0; i < 4; i++)
		{
			tmp = maptile[i][0];

			maptile[i][0] = maptile[i][1];
			maptile[i][1] = maptile[i][2];
			maptile[i][2] = maptile[i][3];
			maptile[i][3] = tmp;

			LoadMapTile(tmp, (x_map >> 5) + i, (y_map >> 5) + 3);
		}
	}

	if (y_mod > 16 && old_y_mod < 16)
	{
		// up
		for (i = 0; i < 4; i++)
		{
			tmp = maptile[i][3];

			maptile[i][3] = maptile[i][2];
			maptile[i][2] = maptile[i][1];
			maptile[i][1] = maptile[i][0];
			maptile[i][0] = tmp;

			LoadMapTile(tmp, (x_map >> 5) + i, (y_map >> 5));
		}
	}
	
	old_x_mod = x_mod;
	old_y_mod = y_mod;

	// make grid coordinates
	for (i = 0; i < 5; i++)
	{

		MapMesh[0][i].vx = -35;
		MapMesh[i][0].vz = -35;

		MapMesh[1][i].vx = -x_mod - 16;
		MapMesh[i][1].vz = -y_mod - 16;

		MapMesh[2][i].vx = -x_mod + 16;
		MapMesh[i][2].vz = -y_mod + 16;

		MapMesh[3][i].vx = -x_mod + 48;
		MapMesh[i][3].vz = -y_mod + 48;

		MapMesh[4][i].vx = 35;
		MapMesh[i][4].vz = 35;
	}

	MapTex[1].w = MapTex[2].w = tile_size;
	MapTex[1].u = MapTex[2].u = MapTex[3].u = 0;

	MapTex[1].h = MapTex[2].h = tile_size;
	MapTex[1].v = MapTex[2].v = MapTex[3].v = 0;
	
	MapTex[0].u = 32 - ABS(MapMesh[0][0].vx - MapMesh[1][0].vx);
	MapTex[0].w = ABS(MapMesh[0][0].vx - MapMesh[1][0].vx);

	MapTex[3].w = ABS(MapMesh[3][0].vx - MapMesh[4][0].vx);
	MapTex[0].v = 32 - ABS(MapMesh[0][0].vz - MapMesh[0][1].vz);
	
	MapTex[0].h = ABS(MapMesh[0][0].vz - MapMesh[0][1].vz);
	MapTex[3].h = ABS(MapMesh[0][3].vz - MapMesh[0][4].vz);

	direction.vx = 0;
	direction.vz = 0;
	direction.vy = player[0].dir & 0xfff;

	RotMatrixXYZ(&map_matrix, &direction);
	MulMatrix0(&identity, &map_matrix, &map_matrix);

	gte_SetRotMatrix(&map_matrix);
	gte_SetTransVector(&translate);

	if (x_mod != 0)
		MeshWidth = 4;
	else
		MeshWidth = 3;

	if (y_mod != 0)
		MeshHeight = 4;
	else
		MeshHeight = 3;
	
	// transform the map mesh
	for (i = 0; i <= MeshWidth; i++)
	{
		for(j = 0; j <= MeshHeight; j++)
		{
			RotTrans(&MapMesh[i][j], &MapMeshO[i][j], &flag);
		}
	}

	// draw map mesh booooi
	for (i = 0; i < MeshHeight; i++)
	{
		for (j = 0; j < MeshWidth; j++)
		{
			int tile;
			tile = maptile[j][i];
			
			if ((MapSegmentPos[tile].x & 24) == 24)
				width = MapTex[j].w - 1;
			else
				width = MapTex[j].w;
	
			if ((MapSegmentPos[tile].y & 96) == 96)
				height = MapTex[i].h - 1;
			else
				height = MapTex[i].h;

			spt = (POLY_FT4*)current->primptr;

			setPolyFT4(spt);
			setSemiTrans(spt, 1);
			
			if (gTimeOfDay == 3) 
				spt->r0 = spt->g0 = spt->b0 = 50;
			else
				spt->r0 = spt->g0 = spt->b0 = 100;

			spt->clut = MapClut;
			spt->tpage = MapTPage;

			spt->x0 = MapMeshO[j][i].vx;
			spt->y0 = MapMeshO[j][i].vz;

			spt->x1 = MapMeshO[j+1][i].vx;
			spt->y1 = MapMeshO[j+1][i].vz;

			spt->x2 = MapMeshO[j][i+1].vx;
			spt->y2 = MapMeshO[j][i+1].vz;

			spt->x3 = MapMeshO[j+1][i+1].vx;
			spt->y3 = MapMeshO[j+1][i+1].vz;

			spt->u0 = MapTex[j].u + MapSegmentPos[tile].x * 4;
			spt->v0 = MapTex[i].v + MapSegmentPos[tile].y;

			spt->u1 = MapTex[j].u + MapSegmentPos[tile].x * 4 + width;
			spt->v1 = MapTex[i].v + MapSegmentPos[tile].y;

			spt->u2 = MapTex[j].u + MapSegmentPos[tile].x * 4;
			spt->v2 = MapTex[i].v + MapSegmentPos[tile].y + height;

			spt->u3 = MapTex[j].u + MapSegmentPos[tile].x * 4 + width;
			spt->v3 = MapTex[i].v + MapSegmentPos[tile].y + height;

			addPrim(current->ot, spt);

			current->primptr += sizeof(POLY_FT4);
		}
	}

	sptb = (POLY_F4 *)current->primptr;

	setPolyF4(sptb);

	sptb->r0 = 60;
	sptb->g0 = 60;
	sptb->b0 = 60;

	sptb->y0 = map_minY;
	sptb->y1 = map_minY;
	sptb->x0 = map_minX;
	sptb->x1 = map_maxX;
	sptb->x2 = map_minX;
	sptb->y2 = map_maxY;
	sptb->x3 = map_maxX;
	sptb->y3 = map_maxY;

	addPrim(current->ot, sptb);
	current->primptr += sizeof(POLY_F4);

	null = (POLY_FT3 *)current->primptr;
	setPolyFT3(null);

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = 0;

	addPrim(current->ot, null);
	current->primptr += sizeof(POLY_FT3);

	clipped_size.x = map_minX + 1;
	clipped_size.w = MAP_SIZE_W - 1;
	clipped_size.h = MAP_SIZE_H - 1;
	clipped_size.y = current->draw.clip.y + map_minY + 1;

	drarea = (DR_AREA*)current->primptr;

	SetDrawArea(drarea, &clipped_size);

	addPrim(current->ot, drarea);
	current->primptr += sizeof(DR_AREA);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawFullscreenMap()
 // line 1374, offset 0x00017c30
	/* begin block 1 */
		// Start line: 1376
		// Start offset: 0x00017C30
		// Variables:
	// 		TILE *polys; // $v0
	// 		POLY_FT4 *back; // $a1
	// 		POLY_FT3 *null; // $a2
	// 		SVECTOR Mesh[4]; // stack offset -192
	// 		VECTOR MeshO[4]; // stack offset -160
	// 		VECTOR target; // stack offset -96
	// 		long flag; // stack offset -64
	// 		long count; // $s4
	// 		int width; // stack offset -60
	// 		int height; // stack offset -56
	// 		int x; // $s7
	// 		int y; // $s3
	// 		int min_x; // $a0
	// 		int max_x; // $v0
	// 		int min_y; // $v1
	// 		int max_y; // $v1

		/* begin block 1.1 */
			// Start line: 1439
			// Start offset: 0x00017E30
			// Variables:
		// 		int px; // $a2
		// 		int pz; // $a1
		/* end block 1.1 */
		// End offset: 0x00017F88
		// End Line: 1500

		/* begin block 1.2 */
			// Start line: 1554
			// Start offset: 0x00017FF4
			// Variables:
		// 		int clipped; // $s5
		/* end block 1.2 */
		// End offset: 0x00018210
		// End Line: 1606

		/* begin block 1.3 */
			// Start line: 1620
			// Start offset: 0x000182B0

			/* begin block 1.3.1 */
				// Start line: 1620
				// Start offset: 0x000182B0
				// Variables:
			// 		VECTOR vec; // stack offset -80
			// 		TILE_1 *tile1; // $v1
			/* end block 1.3.1 */
			// End offset: 0x000182B0
			// End Line: 1620
		/* end block 1.3 */
		// End offset: 0x000182B0
		// End Line: 1620
	/* end block 1 */
	// End offset: 0x000183E8
	// End Line: 1637

	/* begin block 2 */
		// Start line: 3464
	/* end block 2 */
	// End Line: 3465

	/* begin block 3 */
		// Start line: 3465
	/* end block 3 */
	// End Line: 3466

	/* begin block 4 */
		// Start line: 3475
	/* end block 4 */
	// End Line: 3476

/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawFullscreenMap(void)
{
	TILE *polys;
	TILE_1 *tile1;
	POLY_FT4 *back;
	POLY_FT3 *null;
	int x, y;
	int clipped;
	int px, py;
	SVECTOR mesh[4];
	VECTOR meshO[4];
	VECTOR target;
	VECTOR vec;
	long flag;
	int width;
	int height;
	int count;

	// toggle rotated map
	if (Pads[0].dirnew & 0x20) 
	{
		map_x_offset = 0;
		map_z_offset = 0;
		map_x_shift = 0;
		map_z_shift = 0;

		gUseRotatedMap ^= 1;
	}

	SetFullscreenMapMatrix();

	polys = (TILE *)current->primptr;

	setTile(polys);

	polys->r0 = 0;
	polys->g0 = 0;
	polys->b0 = 0;

	polys->x0 = 0;
	polys->y0 = 0;
	polys->w = 320;
	polys->h = 256;

	DrawPrim(polys);
	DrawSync(0);

	width = overlaidmaps[GameLevel].width;
	height = overlaidmaps[GameLevel].height;

	WorldToFullscreenMap((VECTOR *)player->pos, &player_position);

	// do map movement
	if (gUseRotatedMap) 
	{
		if (Pads[0].direct & 0x8000)
			map_x_offset += 8;
		else if (Pads[0].direct & 0x2000)
			map_x_offset -= 8;
		
		if (Pads[0].direct & 0x1000) 
			map_z_offset += 8;
		else if (Pads[0].direct & 0x4000)
			map_z_offset -= 8;

		if (map_x_offset < -128)
			map_x_offset = -128;

		if (map_x_offset > 128)
			map_x_offset = 128;

		if (map_z_offset < -128)
			map_z_offset = -128;

		if (map_z_offset > 128)
			map_z_offset = 128;

		map_x_shift = 0;
		map_z_shift = 0;
	}
	else
	{
		if(player_position.vx + 160 <= width)
		{
			map_x_offset = player_position.vx - 160;
			
			if(map_x_offset > -1)
				map_x_offset = 0;
		}
		else
		{
			map_x_offset = (player_position.vx + 160) - width;
		}

		if(player_position.vz + 128 <= height)
		{
			map_z_offset = player_position.vz - 128;
			
			if (map_z_offset > -1) 
				map_z_offset = 0;
		}
		else
		{
			map_z_offset = (player_position.vz + 128) - height;
		}

		if (Pads[0].direct & 0x8000)
		{
			if (player_position.vx - map_x_offset - 160 - map_x_shift > 0) 
			{
				map_x_shift += 8;
			}
		}
		else if(Pads[0].direct & 0x2000)
		{
			if (player_position.vx - map_x_offset + 160 - map_x_shift < width)
			{
				map_x_shift -= 8;
			}
		}

		if (Pads[0].direct & 0x1000) 
		{
			if (player_position.vz - map_z_offset - 128 - map_z_shift > 0)
			{
				map_z_shift += 8;
			}
		}
		else if(Pads[0].direct & 0x4000)
		{
			if (player_position.vz - map_z_offset + 128 - map_z_shift < height)
			{
				map_z_shift -= 8;
			}
		}

		map_x_offset += map_x_shift;
		map_z_offset += map_z_shift;
	}


	null = (POLY_FT3 *)current->primptr;

	setPolyFT3(null);
	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = MapTPage;

	DrawPrim(null);
	DrawSync(0);

	width >>= 5;
	height >>= 5;

	px = MapSegmentPos[0].x * 4;
	py = MapSegmentPos[0].y;

#ifndef PSX
	RECT16 emuViewport;
	Emulator_GetPSXWidescreenMappedViewport(&emuViewport);
#endif

	for(x = 0; x < width; x++)
	{
		for(y = 0; y < height; y++)
		{
			mesh[0].vy = 0;
			mesh[1].vy = 0;
			mesh[2].vy = 0;
			mesh[3].vy = 0;
			mesh[0].vx = x * 32 - player_position.vx;
			mesh[1].vx = mesh[0].vx + 32;
			mesh[0].vz = y * 32 - player_position.vz;
			mesh[2].vz = mesh[0].vz + 32;
			mesh[1].vz = mesh[0].vz;
			mesh[2].vx = mesh[0].vx;
			mesh[3].vx = mesh[1].vx;
			mesh[3].vz = mesh[2].vz;

			// rotate and clip polygons
			clipped = 0;

			for (count = 0; count < 4; count++)
			{
				RotTrans(&mesh[count], &meshO[count], &flag);

				meshO[count].vx += map_x_offset;
				meshO[count].vz += map_z_offset;

#ifndef PSX
				if (meshO[count].vx > emuViewport.w || meshO[count].vz > emuViewport.w ||
					meshO[count].vx < emuViewport.x || meshO[count].vz < emuViewport.y)
				{
					clipped++;
				}
#else
				if (meshO[count].vx > 320 || meshO[count].vz > 256 ||
					meshO[count].vx < 0 || meshO[count].vz < 0)
				{
					clipped++;
				}
#endif
			}

			if(clipped == 4)
				continue;
			
			LoadMapTile(0, x, y);

			back = (POLY_FT4 *)current->primptr;
			setPolyFT4(back);

			back->r0 = back->g0 = back->b0 = 88;

			back->x0 = meshO[0].vx;
			back->y0 = meshO[0].vz;
			
			back->x1 = meshO[1].vx;
			back->y1 = meshO[1].vz;
			
			back->x2 = meshO[2].vx;
			back->y2 = meshO[2].vz;
			
			back->x3 = meshO[3].vx;
			back->y3 = meshO[3].vz;

			back->u0 = px;
			back->v0 = py;
			
			back->u1 = px + 32;
			back->v1 = py;
			
			back->u2 = px;
			back->v2 = py + 32;
			
			back->u3 = px + 32;
			back->v3 = py + 32;
			
			back->clut = MapClut;
			back->tpage = MapTPage;

			DrawPrim(back);
			DrawSync(0);
		}
	}

	target.vx = 160;
	target.vz = 128;

	DrawFullscreenTargets();

	if (gUseRotatedMap)
		DrawBigCompass(&target, player[0].dir);
	else 
		DrawBigCompass(&target, 0);

	DrawTargetBlip(&target, 64, 64, 64, 14);

	vec.vx = target.vx + map_x_offset;
	vec.vz = target.vz + map_z_offset;

	tile1 = (TILE_1 *)current->primptr;
	setTile1(tile1);

	tile1->r0 = -1;
	tile1->g0 = -1;
	tile1->b0 = -1;
	tile1->x0 = vec.vx;
	tile1->y0 = vec.vz;

	DrawPrim(tile1);

	null = (POLY_FT3 *)current->primptr;
	setPolyFT3(null);

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = fonttpage;

	DrawPrim(null);
	DrawSync(0);

	SetTextColour(128, 128, 128);

	// print string with special characters representing some images inserted into it
	PrintStringCentred("\x80 Exit \x81 Rotation \x8a Move", 226);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCopIndicators()
 // line 1645, offset 0x000183e8
	/* begin block 1 */
		// Start line: 1647
		// Start offset: 0x000183E8
		// Variables:
	// 		static int ft[16]; // offset 0x188
	// 		CAR_DATA *cp; // $s0
	// 		int fade; // $s1
	// 		int cc; // $s3
	// 		int cs; // $s2

		/* begin block 1.1 */
			// Start line: 1662
			// Start offset: 0x00018480
			// Variables:
		// 		int dx; // $a3
		// 		int dz; // $a1
		// 		int p; // $a1
		// 		int q; // $a0
		// 		int ap; // $v1

			/* begin block 1.1.1 */
				// Start line: 1670
				// Start offset: 0x00018510
			/* end block 1.1.1 */
			// End offset: 0x00018568
			// End Line: 1673
		/* end block 1.1 */
		// End offset: 0x00018568
		// End Line: 1674
	/* end block 1 */
	// End offset: 0x000185A0
	// End Line: 1676

	/* begin block 2 */
		// Start line: 4171
	/* end block 2 */
	// End Line: 4172

	/* begin block 3 */
		// Start line: 4180
	/* end block 3 */
	// End Line: 4181

	/* begin block 4 */
		// Start line: 4181
	/* end block 4 */
	// End Line: 4182

	/* begin block 5 */
		// Start line: 4190
	/* end block 5 */
	// End Line: 4191

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawCopIndicators(void)
{
	int cc, cs;
	int dx, dz;
	int p, q;
	CAR_DATA *cp;

	cc = rcossin_tbl[(player[0].dir & 0xfffU) * 2 + 1];
	cs = rcossin_tbl[(player[0].dir & 0xfffU) * 2];

	cp = car_data;
	do {
		if (cp->controlType == CONTROL_TYPE_PURSUER_AI && cp->ai.p.dying == 0)
		{
			dx = cp->hd.where.t[0] - player[0].pos[0];
			dz = cp->hd.where.t[2] - player[0].pos[2];

			p = FIXEDH(dx * cc - dz * cs) * 3 >> 2;
			q = -FIXEDH(dx * cs + dz * cc);
			
			if (ABS(p) < q)
			{
				CopIndicator((p * 266) / q + 160, 0x3fff0 / ((q >> 3) + 600));
			}
		}
		cp++;
	} while (cp <= &car_data[MAX_CARS]);
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitMultiplayerMap()
 // line 1678, offset 0x000198e0
	/* begin block 1 */
		// Start line: 1680
		// Start offset: 0x000198E0
		// Variables:
	// 		RECT rect; // stack offset -48
	// 		char filename[32]; // stack offset -40
	/* end block 1 */
	// End offset: 0x00019994
	// End Line: 1695

	/* begin block 2 */
		// Start line: 6693
	/* end block 2 */
	// End Line: 6694

	/* begin block 3 */
		// Start line: 6694
	/* end block 3 */
	// End Line: 6695

	/* begin block 4 */
		// Start line: 6697
	/* end block 4 */
	// End Line: 6698

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitMultiplayerMap(void)
{
	RECT16 rect;
	char filename[32];

	if (MissionHeader->region == 0)
		return;

	// multiplayer maps loaded externally
	sprintf(filename, "MAPS\\REG%d.%d", MissionHeader->region, GameLevel);

	if (FileExists(filename))
	{
		Loadfile(filename, MapBitMaps);
						
		rect.x = MapRect.x + MapSegmentPos[0].x;
		rect.y = MapRect.y + MapSegmentPos[0].y;
		rect.w = 16;
		rect.h = 64;
	
		LoadImage(&rect, (u_long *)MapBitMaps);

		DrawSync(0);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawMultiplayerMap()
 // line 1697, offset 0x000185a0
	/* begin block 1 */
		// Start line: 1699
		// Start offset: 0x000185A0
		// Variables:
	// 		POLY_FT4 *poly; // $a2
	// 		LINE_F2 *line2; // $s1
	// 		VECTOR target; // stack offset -64
	// 		int i; // $s3
	// 		int y; // $s7
	/* end block 1 */
	// End offset: 0x00018980
	// End Line: 1776

	/* begin block 2 */
		// Start line: 4309
	/* end block 2 */
	// End Line: 4310

	/* begin block 3 */
		// Start line: 4331
	/* end block 3 */
	// End Line: 4332

	/* begin block 4 */
		// Start line: 4332
	/* end block 4 */
	// End Line: 4333

	/* begin block 5 */
		// Start line: 4339
	/* end block 5 */
	// End Line: 4340

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawMultiplayerMap(void)
{
	POLY_FT4 *poly;
	PLAYER *pl;
	int i;
	u_char g;
	u_char r;
	int yPos;
	VECTOR target;
	int px, py;

	map_x_offset = 0;
	map_z_offset = 0;

	if (NumPlayers == 1)
		yPos = gMapYOffset;
	else
		yPos = 96;

	if (MissionHeader->region == 0)
		return;

	DrawMultiplayerTargets();

	pl = player;
	r = 255;
	g = 0;

	i = 0;
	do {
		target.vx = pl->pos[0];
		target.vz = pl->pos[2];
		
		target.vy = 0;

		WorldToMultiplayerMap(&target, &target);

		target.vx += gMapXOffset;
		target.vz += yPos;

		DrawPlayerDot(&target, -pl->dir, r, g, 0, 0x8);

		pl++;
	
		r++;
		g--;
	
		i++;
	} while (i < NumPlayers);

	draw_box(yPos, 64);

	// draw map image
	poly = (POLY_FT4 *)current->primptr;
	setPolyFT4(poly);
	setSemiTrans(poly, 1);
	
	poly->x0 = gMapXOffset;
	poly->y0 = yPos;
	poly->x1 = gMapXOffset + MAP_SIZE_W;
	poly->y1 = yPos;
	poly->x2 = gMapXOffset;
	poly->x3 = gMapXOffset + MAP_SIZE_W;
	poly->y2 = yPos + 64;
	poly->y3 = yPos + 64;

	px = MapSegmentPos[0].x * 4;
	py = MapSegmentPos[0].y;
	
	poly->u0 = px;
	poly->v0 = py;
	poly->u1 = px + 63;
	poly->v1 = py;
	poly->u2 = px;
	poly->v2 = py + 63;
	poly->u3 = px + 63;
	poly->v3 = py + 63;

	poly->clut = MapClut;
	poly->tpage = MapTPage;

	if (gTimeOfDay == 3) 
		r = 50;
	else
		r = 100;

	poly->r0 = poly->g0 = poly->b0 = r;
	
	addPrim(current->ot + 1, poly);
	current->primptr += sizeof(POLY_FT4);
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToMultiplayerMap(VECTOR *in /*$a3*/, VECTOR *out /*$a2*/)
 // line 1778, offset 0x00019994
	/* begin block 1 */
		// Start line: 1779
		// Start offset: 0x00019994
		// Variables:
	// 		int x; // $v1
	// 		int z; // $a0
	/* end block 1 */
	// End offset: 0x00019A60
	// End Line: 1795

	/* begin block 2 */
		// Start line: 6811
	/* end block 2 */
	// End Line: 6812

	/* begin block 3 */
		// Start line: 6895
	/* end block 3 */
	// End Line: 6896

	/* begin block 4 */
		// Start line: 6898
	/* end block 4 */
	// End Line: 6899

// [D] [T]
void WorldToMultiplayerMap(VECTOR *in, VECTOR *out)
{
	int z;
	int x;

	if (MissionHeader->region == 0)
	{
		out->vx = 32;
		out->vz = 32;
		return;
	}

	x = in->vx - (((MissionHeader->region % regions_across) << 16) - cells_across * MAP_CELL_SIZE/2);
	z = in->vz - (((MissionHeader->region / regions_across) << 16) - cells_down * MAP_CELL_SIZE/2);

	out->vx = x / MAP_CELL_SIZE;
	out->vz = MAP_REGION_SIZE - z / MAP_CELL_SIZE;
}






// decompiled code
// original method signature: 
// void /*$ra*/ load_civ_palettes(RECT *cluts /*$a0*/)
 // line 2043, offset 0x0001a094
	/* begin block 1 */
		// Start line: 8350
	/* end block 1 */
	// End Line: 8351

	/* begin block 2 */
		// Start line: 8360
	/* end block 2 */
	// End Line: 8361

	/* begin block 3 */
		// Start line: 8510
	/* end block 3 */
	// End Line: 8511

void load_civ_palettes(RECT16 *cluts)
{
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FlashOverheadMap(int r /*$a0*/, int g /*$a1*/, int b /*$a2*/)
 // line 2319, offset 0x00018980
	/* begin block 1 */
		// Start line: 2321
		// Start offset: 0x00018980
		// Variables:
	// 		TILE *tile; // $a3
	/* end block 1 */
	// End offset: 0x00018AA0
	// End Line: 2341

	/* begin block 2 */
		// Start line: 5094
	/* end block 2 */
	// End Line: 5095

	/* begin block 3 */
		// Start line: 5638
	/* end block 3 */
	// End Line: 5639

	/* begin block 4 */
		// Start line: 5639
	/* end block 4 */
	// End Line: 5640

	/* begin block 5 */
		// Start line: 5650
	/* end block 5 */
	// End Line: 5651

// [D] [T]
void FlashOverheadMap(int r, int g, int b)
{
	TILE *prim;
	POLY_FT3 *null;

	prim = (TILE *)current->primptr;
	setTile(prim);
	setSemiTrans(prim, 1);

	prim->r0 = r;
	prim->g0 = g;
	prim->b0 = b;

	prim->x0 = gMapXOffset;
	prim->y0 = gMapYOffset;
	prim->w = MAP_SIZE_W;
	prim->h = MAP_SIZE_H;


	addPrim(current->ot, prim);

	current->primptr += sizeof(TILE);

	null = (POLY_FT3 *)current->primptr;
	setPolyFT3(null);

	null = (POLY_FT3 *)current->primptr;
	setPolyFT3(null);
	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = 0x20;		// [A] correct me if I'm wrong

	addPrim(current->ot, null);

	current->primptr += sizeof(POLY_FT3);
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadMapTile(int tpage /*$a0*/, int x /*$a1*/, int y /*$a2*/)
 // line 2350, offset 0x00018aa0
	/* begin block 1 */
		// Start line: 2351
		// Start offset: 0x00018AA0
		// Variables:
	// 		RECT MapSegment; // stack offset -16
	// 		int temp; // $a0
	// 		int count; // $a2
	// 		int idx; // $a3
	/* end block 1 */
	// End offset: 0x00018BF4
	// End Line: 2383

	/* begin block 2 */
		// Start line: 5724
	/* end block 2 */
	// End Line: 5725

	/* begin block 3 */
		// Start line: 5734
	/* end block 3 */
	// End Line: 5735

	/* begin block 4 */
		// Start line: 5742
	/* end block 4 */
	// End Line: 5743

// [D] [T]
void LoadMapTile(int tpage, int x, int y)
{
	int temp; // $a0
	int count; // $a2
	int idx; // $a3
	RECT16 MapSegment;

	MapSegment.w = 8;
	MapSegment.h = 32;
	MapSegment.y = MapRect.y + MapSegmentPos[tpage].y;
	MapSegment.x = MapRect.x + MapSegmentPos[tpage].x;

	idx = x + y * tilehnum;
	temp = x << 5;

	if (idx > -1 && idx < overlaidmaps[GameLevel].toptile &&
		temp > -1 && (temp < overlaidmaps[GameLevel].width))
	{
		UnpackRNC(MapBitMaps + *((ushort*)MapBitMaps + idx), MapBuffer);
	}
	else 
	{
		count = 0;

		do {
			MapBuffer[count++] = overlaidmaps[GameLevel].dummy;
		} while (count < 512);
	}

	DrawSync(0);
	LoadImage(&MapSegment, (u_long*)MapBuffer);
	DrawSync(0);

}



// decompiled code
// original method signature: 
// void /*$ra*/ SetMapPos()
 // line 2392, offset 0x00019a60
	/* begin block 1 */
		// Start line: 7532
	/* end block 1 */
	// End Line: 7533

	/* begin block 2 */
		// Start line: 8130
	/* end block 2 */
	// End Line: 8131

	/* begin block 3 */
		// Start line: 8131
	/* end block 3 */
	// End Line: 8132

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void SetMapPos(void)
{
	int scale;

	scale = overlaidmaps[GameLevel].scale;

	x_map = overlaidmaps[GameLevel].x_offset + player[0].pos[0] / scale;
	y_map = overlaidmaps[GameLevel].y_offset - player[0].pos[2] / scale;
}



// decompiled code
// original method signature: 
// void /*$ra*/ draw_box()
 // line 2405, offset 0x00018bf4
	/* begin block 1 */
		// Start line: 2407
		// Start offset: 0x00018BF4
		// Variables:
	// 		LINE_F4 *line4; // $s0
	// 		LINE_F2 *line2; // $s1
	/* end block 1 */
	// End offset: 0x00018D54
	// End Line: 2427

	/* begin block 2 */
		// Start line: 5860
	/* end block 2 */
	// End Line: 5861

	/* begin block 3 */
		// Start line: 5883
	/* end block 3 */
	// End Line: 5884

	/* begin block 4 */
		// Start line: 5884
	/* end block 4 */
	// End Line: 5885

	/* begin block 5 */
		// Start line: 5887
	/* end block 5 */
	// End Line: 5888

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void draw_box(int yPos, int h)
{
	LINE_F4* linef4 = (LINE_F4*)current->primptr;
	setLineF4(linef4);

	linef4->r0 = 0;
	linef4->g0 = 0;
	linef4->b0 = 128;

	linef4->x0 = gMapXOffset;
	linef4->y0 = yPos;

	linef4->x1 = gMapXOffset + MAP_SIZE_W;
	linef4->x2 = gMapXOffset + MAP_SIZE_W;

	linef4->y1 = yPos;
	linef4->x3 = gMapXOffset;

	linef4->y2 = yPos + h;
	linef4->y3 = yPos + h;

	addPrim(current->ot + 1, linef4);
	current->primptr += sizeof(LINE_F4);

	LINE_F2* linef2 = (LINE_F2*)current->primptr;
	setLineF2(linef2);

	linef2->r0 = 0;
	linef2->g0 = 0;
	linef2->b0 = 128;

	linef2->x0 = gMapXOffset;
	linef2->y0 = yPos;

	linef2->x1 = gMapXOffset;
	linef2->y1 = yPos + h;

	addPrim(current->ot + 1, linef2);
	current->primptr += sizeof(LINE_F2);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawN(VECTOR *pScreenPosition /*$s2*/, int direct /*$s7*/)
 // line 2435, offset 0x00018d54
	/* begin block 1 */
		// Start line: 2436
		// Start offset: 0x00018D54
		// Variables:
	// 		XYPAIR lastPoint; // stack offset -48
	// 		XYPAIR *pPoint; // $s0
	// 		char loop; // $s4

		/* begin block 1.1 */
			// Start line: 2446
			// Start offset: 0x00018DC4
			// Variables:
		// 		LINE_F2 *pLine; // $a2
		/* end block 1.1 */
		// End offset: 0x00018EC4
		// End Line: 2469
	/* end block 1 */
	// End offset: 0x00018F18
	// End Line: 2471

	/* begin block 2 */
		// Start line: 5969
	/* end block 2 */
	// End Line: 5970

	/* begin block 3 */
		// Start line: 5978
	/* end block 3 */
	// End Line: 5979

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void DrawN(VECTOR *pScreenPosition, int direct)
{
	int i;

	LINE_F2 *linef2;
	XYPAIR *pPoint;
	XYPAIR lastPoint;

	pPoint = NVertex;
	i = 0;

	lastPoint.x = NVertex[0].x + pScreenPosition->vx;
	lastPoint.y = NVertex[0].y + pScreenPosition->vz;

	do {
		pPoint++;
		linef2 = (LINE_F2 *)current->primptr;

		setLineF2(linef2);

		linef2->x0 = lastPoint.x;
		linef2->y0 = lastPoint.y;

		lastPoint.x = pPoint->x + pScreenPosition->vx;
		lastPoint.y = pPoint->y + pScreenPosition->vz;

		linef2->x1 = lastPoint.x;
		linef2->y1 = lastPoint.y;

		if (gTimeOfDay == 3)
		{
			linef2->r0 = 75;
			linef2->g0 = 75;
			linef2->b0 = 75;
		}
		else 
		{
			linef2->r0 = 96;
			linef2->g0 = 96;
			linef2->b0 = 96;
		}

		setSemiTrans(linef2, 1);
		linef2->code = linef2->code | 2;

		if (direct == 0) 
		{
			addPrim(current->ot, linef2);
			current->primptr += sizeof(LINE_F2);
		}
		else
		{
			DrawPrim(linef2);
		}

		

		i++;
	} while (i < 3);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCompass()
 // line 2479, offset 0x00018f18
	/* begin block 1 */
		// Start line: 2481
		// Start offset: 0x00018F18
		// Variables:
	// 		VECTOR position[5]; // stack offset -88
	// 		XYPAIR *pNorth; // $a1
	// 		int scale; // $a0

		/* begin block 1.1 */
			// Start line: 2482
			// Start offset: 0x00018F18
			// Variables:
		// 		char loop; // $t2
		// 		VECTOR *pPosition; // $a3
		// 		void *pot; // $s0

			/* begin block 1.1.1 */
				// Start line: 2511
				// Start offset: 0x000190B8
				// Variables:
			// 		LINE_G2 *pLine; // $a0
			/* end block 1.1.1 */
			// End offset: 0x000190B8
			// End Line: 2511
		/* end block 1.1 */
		// End offset: 0x00019194
		// End Line: 2525
	/* end block 1 */
	// End offset: 0x00019194
	// End Line: 2526

	/* begin block 2 */
		// Start line: 6209
	/* end block 2 */
	// End Line: 6210

	/* begin block 3 */
		// Start line: 6218
	/* end block 3 */
	// End Line: 6219

	/* begin block 4 */
		// Start line: 6219
	/* end block 4 */
	// End Line: 6220

	/* begin block 5 */
		// Start line: 6220
	/* end block 5 */
	// End Line: 6221

/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawCompass(void)
{
	int i;
	LINE_G2 *lineg2;
	VECTOR *pPosition;
	OTTYPE *potz;
	VECTOR position[5];

	position[1].vx = north[GameLevel].x * overlaidmaps[GameLevel].scale;
	position[1].vz = north[GameLevel].y * overlaidmaps[GameLevel].scale;
	position[0].vx = position[1].vx * 20 + 8 >> 4;
	position[2].vx = position[1].vx + 2 >> 2;
	position[0].vz = position[1].vz * 20 + 8 >> 4;
	position[2].vz = position[1].vz + 2 >> 2;
	position[3].vx = (position[1].vz - position[1].vx) * 171 >> 10;
	position[3].vz = (-position[1].vx - position[1].vz) * 171 >> 10;
	position[4].vz = -position[3].vx;
	position[4].vx = position[3].vz;

	WorldToOverheadMapPositions(position, position, 3, 1, 0);
	WorldToOverheadMapPositions(position + 3, position + 3, 2, 1, 1);

	position[3].vx = position[3].vx + position[1].vx;
	position[3].vz = position[3].vz + position[1].vz;
	position[4].vx = position[4].vx + position[1].vx;
	position[4].vz = position[4].vz + position[1].vz;

	potz = current->ot;

	pPosition = position + 2;

	for (i = 0; i < 3; i++)
	{
		lineg2 = (LINE_G2 *)current->primptr;

		setLineG2(lineg2);
		setSemiTrans(lineg2, 1);

		lineg2->x0 = position[1].vx;
		lineg2->y0 = position[1].vz;

		lineg2->x1 = pPosition->vx;
		lineg2->y1 = pPosition->vz;


		lineg2->r0 = 96;
		lineg2->g0 = 96;
		lineg2->b0 = 96;

		lineg2->r1 = 0;
		lineg2->g1 = 0;
		lineg2->b1 = 0;

		addPrim(potz, lineg2);

		current->primptr += sizeof(LINE_G2);

		pPosition++;
	}

	DrawN(position, 0);

	TransparencyOn(potz, 0x20);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawBigCompass(VECTOR *root /*$a0*/, int angle /*$a1*/)
 // line 2534, offset 0x00019194
	/* begin block 1 */
		// Start line: 2535
		// Start offset: 0x00019194
		// Variables:
	// 		VECTOR position[5]; // stack offset -96
	// 		VECTOR *pPosition; // $s0
	// 		char loop; // $s1

		/* begin block 1.1 */
			// Start line: 2557
			// Start offset: 0x00019300
			// Variables:
		// 		LINE_G2 *pLine; // $a1
		/* end block 1.1 */
		// End offset: 0x00019300
		// End Line: 2557
	/* end block 1 */
	// End offset: 0x000193B4
	// End Line: 2569

	/* begin block 2 */
		// Start line: 6432
	/* end block 2 */
	// End Line: 6433

	/* begin block 3 */
		// Start line: 6433
	/* end block 3 */
	// End Line: 6434

	/* begin block 4 */
		// Start line: 6442
	/* end block 4 */
	// End Line: 6443

	/* begin block 5 */
		// Start line: 6444
	/* end block 5 */
	// End Line: 6445

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void DrawBigCompass(VECTOR *root, int angle)
{
	int i;
	uint ang2;
	LINE_G2 *lineg2;
	int ang;
	int ang3;
	VECTOR *pPosition;
	VECTOR position[5];

	ang = big_north[GameLevel] + angle & 0xfff;

	position[2].vx = root->vx + map_x_offset;
	position[2].vy = root->vz + map_z_offset;
	position[1].vx = position[2].vx + (rcossin_tbl[ang * 2] * 0x19 >> 0xc);
	position[0].vx = position[2].vx + (rcossin_tbl[ang * 2] * 0xf >> 0xb);

	ang2 = ang - 200 & 0xfff;
	ang3 = ang + 200 & 0xfff;

	position[1].vy = position[2].vy + (rcossin_tbl[ang * 2 + 1] * 0x19 >> 0xc);
	position[0].vz = position[2].vy + (rcossin_tbl[ang * 2 + 1] * 0xf >> 0xb);
	position[3].vx = position[2].vx + (rcossin_tbl[ang2 * 2] * 5 >> 10);
	position[3].vy = position[2].vy + (rcossin_tbl[ang2 * 2 + 1] * 5 >> 10);
	position[4].vx = position[2].vx + (rcossin_tbl[ang3 * 2] * 5 >> 10);
	position[4].vy = position[2].vy + (rcossin_tbl[ang3 * 2 + 1] * 5 >> 10);

	i = 0;
	pPosition = position + 2;
	do {
		
		lineg2 = (LINE_G2 *)current->primptr;

		setLineG2(lineg2);
		setSemiTrans(lineg2, 1);

		lineg2->x0 = position[1].vx;
		lineg2->y0 = position[1].vy;

		lineg2->x1 = pPosition->vx;
		lineg2->y1 = pPosition->vy;

		lineg2->r0 = 96;
		lineg2->g0 = 96;
		lineg2->b0 = 96;

		lineg2->r1 = 0;
		lineg2->g1 = 0;
		lineg2->b1 = 0;

		DrawPrim(lineg2);

		pPosition++;
		//current->primptr += sizeof(LINE_G2);

		i++;
	} while (i < 3);

	DrawN(position, 1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CopIndicator(int xpos /*$a3*/, int strength /*$a1*/)
 // line 2577, offset 0x000193b4
	/* begin block 1 */
		// Start line: 2578
		// Start offset: 0x000193B4
		// Variables:
	// 		POLY_F3 *tri; // $a2
	// 		int str2; // $fp
	// 		void *pot; // stack offset -56
	/* end block 1 */
	// End offset: 0x00019594
	// End Line: 2607

	/* begin block 2 */
		// Start line: 6667
	/* end block 2 */
	// End Line: 6668

	/* begin block 3 */
		// Start line: 6676
	/* end block 3 */
	// End Line: 6677

	/* begin block 4 */
		// Start line: 6680
	/* end block 4 */
	// End Line: 6681

// [D] [T]
void CopIndicator(int xpos, int strength)
{
	int str2;
	POLY_F3 *poly;

	if (strength > 255)
		strength = 255;

	poly = (POLY_F3 *)current->primptr;

	setPolyF3(poly);
	setSemiTrans(poly, 1);

	poly->r0 = strength;

	str2 = (strength >> 2);

	poly->g0 = str2;
	poly->b0 = str2;
	poly->x0 = xpos - 12;
	poly->y0 = 256;
	poly->x1 = xpos;
	poly->y1 = 226;
	poly->x2 = xpos + 12;
	poly->y2 = 256;

	addPrim(current->ot + 1, poly);
	current->primptr += sizeof(POLY_F3);

	TransparencyOn(current->ot + 1, 0x20);

	poly = (POLY_F3 *)current->primptr;

	setPolyF3(poly);
	setSemiTrans(poly, 1);

	str2 = strength * (strength + 256) >> 9;

	poly->r0 = str2;
	poly->g0 = str2;
	poly->b0 = str2;

	poly->x0 = xpos - 12;
	poly->y0 = 256;
	poly->y1 = 226;
	poly->x2 = xpos + 12;
	poly->y2 = 256;
	poly->x1 = xpos;

	addPrim(current->ot + 1, poly);
	current->primptr += sizeof(POLY_F3);

	TransparencyOn(current->ot + 1, 0x40);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSightCone(COP_SIGHT_DATA *pCopSightData /*$a0*/, VECTOR *pPosition /*$a1*/, int direction /*$t6*/)
 // line 2609, offset 0x00019594
	/* begin block 1 */
		// Start line: 2610
		// Start offset: 0x00019594
		// Variables:
	// 		VECTOR vertex[9]; // stack offset -160
	// 		VECTOR *pVertex; // $t0
	// 		int angle; // $a3
	// 		int frontViewAngle; // $t1
	// 		int negFrontViewAngle; // $a2
	// 		int frontViewDistance; // $t4
	// 		int surroundViewDistance; // $t3

		/* begin block 1.1 */
			// Start line: 2624
			// Start offset: 0x000195E8
			// Variables:
		// 		int len; // $a1

			/* begin block 1.1.1 */
				// Start line: 2636
				// Start offset: 0x00019600
				// Variables:
			// 		int temp; // $v0
			/* end block 1.1.1 */
			// End offset: 0x00019600
			// End Line: 2636
		/* end block 1.1 */
		// End offset: 0x00019600
		// End Line: 2636

		/* begin block 1.2 */
			// Start line: 2643
			// Start offset: 0x0001966C
			// Variables:
		// 		VECTOR *pVertex; // $a2
		// 		void *pot; // $a3

			/* begin block 1.2.1 */
				// Start line: 2651
				// Start offset: 0x000196B8
				// Variables:
			// 		POLY_G3 *poly; // $a1
			// 		VECTOR *pNextVertex; // $a0
			/* end block 1.2.1 */
			// End offset: 0x000196DC
			// End Line: 2659
		/* end block 1.2 */
		// End offset: 0x000197BC
		// End Line: 2670
	/* end block 1 */
	// End offset: 0x000197BC
	// End Line: 2671

	/* begin block 2 */
		// Start line: 6761
	/* end block 2 */
	// End Line: 6762

	/* begin block 3 */
		// Start line: 6764
	/* end block 3 */
	// End Line: 6765

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void DrawSightCone(COP_SIGHT_DATA *pCopSightData, VECTOR *pPosition, int direction)
{
	short temp;
	int dir;
	VECTOR *pVVar8;
	VECTOR *pNextVertex;
	POLY_G3 *poly;
	VECTOR *pVertex;
	VECTOR vertex[9];
	int angle; 
	int frontViewAngle;
	int frontViewDistance;
	int surroundViewDistance;
	
	
	frontViewDistance = pCopSightData->frontViewDistance;
	surroundViewDistance = pCopSightData->surroundViewDistance;
	frontViewAngle = pCopSightData->frontViewAngle;

	vertex[0].vx = pPosition->vx;
	vertex[0].vz = pPosition->vz;

	pVertex = vertex + 1;
	
	angle = 0;
	do {

		if(angle > frontViewAngle && angle < 4096 - frontViewAngle)
			temp = surroundViewDistance;
		else
			temp = frontViewDistance;

		dir = angle + direction & 0xfff;

		angle += 512;
		pVertex->vx = vertex[0].vx + FIXEDH(rcossin_tbl[dir * 2] * temp);
		pVertex->vz = vertex[0].vz + FIXEDH(rcossin_tbl[dir * 2 + 1] * temp);
		
		pVertex++;
	
	} while (angle < 4096);

	WorldToOverheadMapPositions(vertex, vertex, 9, 0, 0);

	pVertex = vertex + 1;

	while (pVertex < &vertex[9])
	{
		pNextVertex = pVertex + 1;

		if (pNextVertex > vertex + 8)
			pNextVertex = vertex + 1;
	
		poly = (POLY_G3 *)current->primptr;
		setPolyG3(poly);
		setSemiTrans(poly, 1);

		poly->x0 = vertex[0].vx;
		poly->y0 = vertex[0].vz;
		poly->x1 = pVertex->vx;
		poly->y1 = pVertex->vz;
		poly->x2 = pNextVertex->vx;
		poly->y2 = pNextVertex->vz;

		poly->r0 = poly->g0 = poly->b0 = 96;
		poly->r1 = poly->g1 = poly->b1 = 0;
		poly->r2 = poly->g2 = poly->b2 = 0;

		addPrim(current->ot, poly);

		current->primptr += sizeof(POLY_G3);
		pVertex++;
	}

	TransparencyOn(current->ot, 0x20);
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToOverheadMapPositions(VECTOR *pGlobalPosition /*$s1*/, VECTOR *pOverheadMapPosition /*$s3*/, int count /*$s2*/, char inputRelative /*$s5*/, int outputRelative /*stack 16*/)
 // line 2703, offset 0x00019af0
	/* begin block 1 */
		// Start line: 2704
		// Start offset: 0x00019AF0
		// Variables:
	// 		MATRIX TempMatrix; // stack offset -80
	// 		int sin; // $a1
	// 		int cos; // $a2
	// 		int angle; // $v1
	// 		int scale; // $s0

		/* begin block 1.1 */
			// Start line: 2745
			// Start offset: 0x00019C20
			// Variables:
		// 		SVECTOR tempVector; // stack offset -48
		// 		long flag; // stack offset -40
		/* end block 1.1 */
		// End offset: 0x00019CC0
		// End Line: 2760
	/* end block 1 */
	// End offset: 0x00019D0C
	// End Line: 2764

	/* begin block 2 */
		// Start line: 8754
	/* end block 2 */
	// End Line: 8755

// [D] [T]
void WorldToOverheadMapPositions(VECTOR *pGlobalPosition, VECTOR *pOverheadMapPosition, int count, char inputRelative,int outputRelative)
{
	int scale;
	MATRIX tempMatrix = {0};
	SVECTOR tempVector;
	long flag;

	tempMatrix.m[0][1] = 0;
	tempMatrix.m[1][0] = 0;
	tempMatrix.m[1][2] = 0;
	tempMatrix.m[2][1] = 0;
	
	tempMatrix.m[0][0] = rcossin_tbl[(player[0].dir & 0xfffU) * 2 + 1];
	tempMatrix.m[2][2] = rcossin_tbl[(player[0].dir & 0xfffU) * 2 + 1];

	tempMatrix.m[2][0] = -rcossin_tbl[(player[0].dir & 0xfffU) * 2];
	tempMatrix.m[0][2] = rcossin_tbl[(player[0].dir & 0xfffU) * 2];
	
	tempMatrix.t[1] = 0;

	if (outputRelative == 0)
	{
		tempMatrix.t[0] = gMapXOffset + MAP_SIZE_W/2;
		tempMatrix.t[2] = gMapYOffset + MAP_SIZE_H/2;
	}
	else
	{
		tempMatrix.t[0] = 0;
		tempMatrix.t[2] = 0;
	}

	gte_SetRotMatrix(&tempMatrix);
	gte_SetTransMatrix(&tempMatrix);

	count--;

	scale = overlaidmaps[GameLevel].scale;

	while (count != -1) 
	{
		tempVector.vy = 0;
		if (inputRelative == 0) 
		{
			tempVector.vx = (pGlobalPosition->vx - player[0].pos[0]) / scale;
			tempVector.vz = (player[0].pos[2] - pGlobalPosition->vz) / scale;
		}
		else 
		{
			tempVector.vx = pGlobalPosition->vx / scale;
			tempVector.vz = -pGlobalPosition->vz / scale;
		}

		RotTrans(&tempVector, pOverheadMapPosition, &flag);

		count--;
		pGlobalPosition++;
		pOverheadMapPosition++;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetFullscreenMapMatrix()
 // line 2771, offset 0x00019d0c
	/* begin block 1 */
		// Start line: 2773
		// Start offset: 0x00019D0C
		// Variables:
	// 		VECTOR translate; // stack offset -32
	// 		SVECTOR direction; // stack offset -16
	/* end block 1 */
	// End offset: 0x00019DE8
	// End Line: 2787

	/* begin block 2 */
		// Start line: 8933
	/* end block 2 */
	// End Line: 8934

	/* begin block 3 */
		// Start line: 8941
	/* end block 3 */
	// End Line: 8942

	/* begin block 4 */
		// Start line: 8942
	/* end block 4 */
	// End Line: 8943

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void SetFullscreenMapMatrix(void)
{
	VECTOR translate = { 160, 0, 128 };
	SVECTOR direction;

	direction.vx = 0;

	if (gUseRotatedMap == 0)
		direction.vy = 0;
	else
		direction.vy = player[0].dir & 0xfff;

	direction.vz = 0;

	RotMatrixXYZ(&map_matrix, &direction);		// Why, Reflections? Why? You could have used RotMatrixY
	MulMatrix0(&identity, &map_matrix, &map_matrix);

	gte_SetRotMatrix(&map_matrix);
	gte_SetTransVector(&translate);
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToFullscreenMap(VECTOR *in /*$a0*/, VECTOR *out /*$a1*/)
 // line 2794, offset 0x00019de8
	/* begin block 1 */
		// Start line: 8983
	/* end block 1 */
	// End Line: 8984

	/* begin block 2 */
		// Start line: 8991
	/* end block 2 */
	// End Line: 8992

	/* begin block 3 */
		// Start line: 8992
	/* end block 3 */
	// End Line: 8993

// [D] [T]
void WorldToFullscreenMap(VECTOR *in, VECTOR *out)
{
	out->vy = 0;
	out->vx = overlaidmaps[GameLevel].x_offset + in->vx / overlaidmaps[GameLevel].scale + 49;
	out->vz = overlaidmaps[GameLevel].y_offset - (in->vz / overlaidmaps[GameLevel].scale - 49);
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToFullscreenMap2(VECTOR *in /*$a0*/, VECTOR *out /*$a1*/)
 // line 2806, offset 0x00019e7c
	/* begin block 1 */
		// Start line: 2807
		// Start offset: 0x00019E7C
		// Variables:
	// 		SVECTOR pos; // stack offset -24
	// 		long flag; // stack offset -16
	/* end block 1 */
	// End offset: 0x00019F44
	// End Line: 2819

	/* begin block 2 */
		// Start line: 9016
	/* end block 2 */
	// End Line: 9017

	/* begin block 3 */
		// Start line: 9020
	/* end block 3 */
	// End Line: 9021

// [D] [T]
void WorldToFullscreenMap2(VECTOR *in, VECTOR *out)
{
	SVECTOR pos;
	long flag;

	pos.vy = 0;
	pos.vx = overlaidmaps[GameLevel].x_offset + (in->vx / overlaidmaps[GameLevel].scale + 49) - player_position.vx;
	pos.vz = overlaidmaps[GameLevel].y_offset - (in->vz / overlaidmaps[GameLevel].scale - 49) - player_position.vz;

	RotTrans(&pos, out, &flag);
}





