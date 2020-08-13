#include "THISDUST.H"
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

char* palettedir[] = {
	"CHICAGO",
	"HAVANA",
	"VEGAS",
	"RIO",
	"CHICAGO",
	"HAVANA",
	"VEGAS",
	"RIO",
};

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


// decompiled code
// original method signature: 
// void /*$ra*/ DrawTargetBlip(struct VECTOR *pos /*$t0*/, unsigned char r /*$s2*/, unsigned char g /*$s3*/, unsigned char b /*$s4*/, unsigned long flags /*stack 16*/)
 // line 685, offset 0x00016280
	/* begin block 1 */
		// Start line: 686
		// Start offset: 0x00016280
		// Variables:
	// 		struct POLY_FT4 *poly; // $t0
	// 		struct VECTOR vec; // stack offset -40
	// 		int ysize; // $a2
	/* end block 1 */
	// End offset: 0x00016558
	// End Line: 759

	/* begin block 2 */
		// Start line: 1370
	/* end block 2 */
	// End Line: 1371

/* WARNING: Could not reconcile some variable overlaps */

// [D]
void DrawTargetBlip(VECTOR *pos, unsigned char r, unsigned char g, unsigned char b, ulong flags)
{
	int ysize;
	POLY_FT4 *poly;
	VECTOR vec;

	if ((flags & 0x20) == 0) 
	{
		if ((flags & 8) == 0)
		{
			if ((flags & 1) == 0)
			{
				WorldToFullscreenMap2(pos, &vec);
			}
			else 
			{
				WorldToOverheadMapPositions(pos, &vec, 1, 0, 0);
				if (0x5e < vec.vx - 0xe9U)
					return;

				if (vec.vz < 0xae) 
					return;
			
				if (0xfa < vec.vz)
					return;
				
			}
		}
		else {
			vec.vx = pos->vx;
			vec.vy = pos->vy;
			vec.vz = pos->vz;
			vec.pad = pos->pad;
		}
		if ((flags & 1) == 0) {
			vec.vx = vec.vx + map_x_offset;
			vec.vz = vec.vz + map_z_offset;
		}
	}
	else 
	{
		WorldToMultiplayerMap(pos, &vec);
		vec.vx += 240;
		vec.vz += 96;
	}

	if ((flags & 0x10) == 0) 
	{
		ysize = 4;

		if ((flags & 2) != 0) 
		{
			ysize = 3;
		}
	}
	else 
	{
		ysize = OverlayFlashValue >> 1;
	}

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
	
	poly->u0 = light_texture.coords.u0;
	poly->v0 = light_texture.coords.v0;
	poly->u1 = light_texture.coords.u1;
	poly->v1 = light_texture.coords.v1;
	poly->u2 = light_texture.coords.u2;
	poly->v2 = light_texture.coords.v2;
	poly->u3 = light_texture.coords.u3;
	poly->v3 = light_texture.coords.v3;

	if ((flags & 2) == 0)
		poly->tpage = light_texture.tpageid | 0x20;
	else
		poly->tpage = light_texture.tpageid | 0x40;

	poly->clut = light_texture.clutid;

	if ((flags & 4) == 0)
	{
		addPrim(current->ot, poly);
		current->primptr += sizeof(POLY_FT4);
	}
	else
	{
		DrawPrim(poly);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTargetArrow(struct VECTOR *pos /*$a2*/, unsigned long flags /*$s3*/)
 // line 815, offset 0x00016578
	/* begin block 1 */
		// Start line: 816
		// Start offset: 0x00016578
		// Variables:
	// 		struct VECTOR vec; // stack offset -56
	// 		struct VECTOR vec2; // stack offset -40
	// 		struct POLY_FT3 *null; // $t1
	// 		struct POLY_G3 *poly; // $s2
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

// [D]
void DrawTargetArrow(VECTOR *pos, ulong flags)
{
	short sVar1;
	short sVar2;
	int y;
	int x;
	POLY_G3 *poly;
	VECTOR vec;
	VECTOR vec2;

	if ((flags & 8) == 0) 
	{
		if ((flags & 1) == 0)
		{
			WorldToFullscreenMap2(pos, &vec);
		}
		else 
		{
			WorldToOverheadMapPositions(pos, &vec, 1, 0, 0);
		}
	}
	else 
	{
		vec.vx = pos->vx;
		vec.vy = pos->vy;
		vec.vz = pos->vz;
		vec.pad = pos->pad;
	}

	if ((flags & 1) == 0) 
	{
		vec.vx = vec.vx + map_x_offset;
		vec.vz = vec.vz + map_z_offset;
		vec2.vx = map_x_offset + 0xa0;
		vec2.vz = map_z_offset + 0x80;
	}
	else 
	{
		WorldToOverheadMapPositions((VECTOR *)player, &vec2, 1, '\0', 0);
	}

	x = vec2.vx - vec.vx;
	y = vec2.vz - vec.vz;

	poly = (POLY_G3 *)current->primptr;

	setPolyG3(poly);
	setSemiTrans(poly, 1);

	poly->r0 = 24;
	poly->g0 = 24;
	poly->b0 = 24;
	poly->r1 = 24;
	poly->g1 = 24;
	poly->b1 = 24;

	poly->r2 = 64;
	poly->g2 = 64;
	poly->b2 = 64;

	sVar1 = (y >> 3);
	sVar2 = (x >> 3);

	poly->x0 = vec2.vx + sVar1;
	poly->y0 = vec2.vz - sVar2;
	poly->x1 = vec2.vx - sVar1;
	poly->y1 = vec2.vz + sVar2;
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
	
	if ((flags & 4) == 0)
	{
		addPrim(current->ot, poly);
		addPrim(current->ot, null);
		current->primptr += sizeof(POLY_G3) + sizeof(POLY_FT3);
	}
	else
	{
		DrawPrim(null);
		DrawPrim(poly);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawPlayerDot(struct VECTOR *pos /*$a1*/, short rot /*$s2*/, unsigned char r /*$s5*/, unsigned char g /*$s4*/, int b /*stack 16*/, unsigned long flags /*stack 20*/)
 // line 883, offset 0x00016814
	/* begin block 1 */
		// Start line: 884
		// Start offset: 0x00016814
		// Variables:
	// 		struct MATRIX matrix; // stack offset -168
	// 		struct VECTOR direction; // stack offset -136
	// 		struct SVECTOR apos[3]; // stack offset -120
	// 		struct VECTOR opos[3]; // stack offset -96
	// 		struct POLY_F3 *poly; // $t0
	// 		struct VECTOR vec; // stack offset -48
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

// [D]
void DrawPlayerDot(VECTOR *pos, short rot, unsigned char r, unsigned char g, int b, ulong flags)
{
	int iVar2;
	int iVar3;
	POLY_F3 *poly;
	VECTOR direction;
	SVECTOR apos[3];
	VECTOR opos[3];
	VECTOR vec;

	if ((flags & 0x20) == 0) 
	{
		if ((flags & 8) == 0) 
		{
			if ((flags & 1) == 0)
			{
				WorldToFullscreenMap2(pos, &vec);
			}
			else
			{
				WorldToOverheadMapPositions(pos, &vec, 1, 0, 0);
				if (0x5e < vec.vx - 0xe9U)
					return;

				if (vec.vz < 0xae)
					return;
			
				if (0xfa < vec.vz)
					return;

			}
		}
		else 
		{
			vec.vx = pos->vx;
			vec.vy = pos->vy;
			vec.vz = pos->vz;
			vec.pad = pos->pad;
		}

		if ((flags & 1) == 0) 
		{
			vec.vx = vec.vx + map_x_offset;
			vec.vz = vec.vz + map_z_offset;
		}
	}
	else 
	{
		WorldToMultiplayerMap(pos, &vec);
		vec.vx += 240;
		vec.vz += 96;
	}

	iVar2 = rcossin_tbl[(rot & 0xfffU) * 2];
	iVar3 = rcossin_tbl[(rot & 0xfffU) * 2 + 1];

	opos[2].vx = vec.vx;
	opos[2].vz = vec.vz;

	opos[0].vx = opos[2].vx + (iVar2 * -3 + 0x800 >> 0xc);
	opos[0].vz = opos[2].vz + FIXED(iVar3 * -3);

	opos[1].vx = opos[2].vx + FIXED(iVar2 * 3 + iVar3 * -2);
	opos[1].vz = opos[2].vz + FIXED(iVar3 * 3 + iVar2 * 2);

	opos[2].vx = opos[2].vx + FIXED(iVar3 * 2 + iVar2 * 3);
	opos[2].vz = opos[2].vz + FIXED(iVar2 * -2 + iVar3 * 3);

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

	if ((flags & 4) == 0) 
	{
		addPrim(current->ot, poly);
		current->primptr += sizeof(POLY_F3);
	}
	else 
	{
		DrawPrim(poly);
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
	// 		struct TEXTURE_DETAILS info; // stack offset -32
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

// [D]
void ProcessOverlayLump(char *lump_ptr, int lump_size)
{
	uint uVar1;
	SXYPAIR *pSVar2;
	TEXTURE_DETAILS info;

	GetTextureDetails("OVERHEAD", &info);

	MapTPage = info.tpageid;
	MapClut = GetClut(mapclutpos.x, mapclutpos.y);

	uVar1 = 0;
	pSVar2 = MapSegmentPos;

	MapRect.w = 0x40;
	MapRect.h = 0x100;
	MapRect.x = (MapTPage & 0xf) << 6;
	MapRect.y = (MapTPage & 0x10) << 4;

	do {
		pSVar2->x = (((uVar1 & 3) * 32 + info.coords.u0) >> 2);
		pSVar2->y = info.coords.v0 + (uVar1 >> 2) * 32;

		uVar1++;
		pSVar2++;
	} while (uVar1 < 16);

	MALLOC_BEGIN()

	MapBitMaps = D_MALLOC(lump_size);
	memcpy(MapBitMaps, lump_ptr, lump_size);

	MALLOC_END();

	LoadImage(&mapclutpos, (u_long *)(MapBitMaps + 0x200));
	DrawSync(0);
}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ Long2DDistance(struct VECTOR *pPoint1 /*$a0*/, struct VECTOR *pPoint2 /*$a2*/)
 // line 994, offset 0x00016c0c
	/* begin block 1 */
		// Start line: 995
		// Start offset: 0x00016C0C
		// Variables:
	// 		struct VECTOR delta; // stack offset -24
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

// [D]
ulong Long2DDistance(VECTOR *pPoint1, VECTOR *pPoint2)
{
	short sVar1;
	int iVar2;
	uint uVar3;
	long y;
	int x;
	ulong uVar4;

	x = pPoint1->vx - pPoint2->vx;

	if (x < 0)
		x = pPoint2->vx - pPoint1->vx;

	y = pPoint1->vz - pPoint2->vz;

	if (y < 0) 
		y = pPoint2->vz - pPoint1->vz;

	uVar3 = ratan2(y, x);
	if ((uVar3 & 0x7ff) - 0x200 < 0x401)
	{
		sVar1 = rcossin_tbl[(uVar3 & 0xfff) * 2];
		x = y;
	}
	else 
	{
		sVar1 = rcossin_tbl[(uVar3 & 0xfff) * 2 + 1];
	}

	iVar2 = sVar1;

	if (x < 0x80000) 
		uVar4 = (x << 0xc) / iVar2;
	else 
		uVar4 = (x << 9) / iVar2 << 3;

	return uVar4;
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

// [D]
void InitOverheadMap(void)
{
	char *pcVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int tpage;
	int iVar5;

	iVar4 = 0;

	if (gMultiplayerLevels == 0) 
	{
		SetMapPos();

		tilehnum = overlaidmaps[GameLevel].width;
		tilehnum = tilehnum >> 5;

		iVar3 = 0;
		do {
			iVar2 = 0;
			iVar5 = iVar3 + 1;
			pcVar1 = maptile[iVar3];
			tpage = iVar4;

			do {
				maptile[iVar3][iVar2] = tpage;
				//*pcVar1 = tpage;
				iVar4 = tpage + 1;
				//pcVar1 = pcVar1 + 4;

				LoadMapTile(tpage, (x_map >> 5) + iVar2, (y_map >> 5) + iVar3);

				tpage++;
				iVar2++;
			} while (iVar2 < 4);

			iVar3 = iVar5;

		} while (iVar5 < 4);

		old_x_mod = x_map & 0x1f;
		old_y_mod = y_map & 0x1f;
	}
	else 
	{
		InitMultiplayerMap();
	}
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
	// 		struct SVECTOR MapMesh[5][5]; // stack offset -784
	// 		struct VECTOR MapMeshO[5][5]; // stack offset -584
	// 		struct MAPTEX MapTex[4]; // stack offset -184
	// 		struct SVECTOR direction; // stack offset -152
	// 		struct POLY_FT4 *spt; // $a3
	// 		struct POLY_F4 *sptb; // $a0
	// 		struct DR_AREA *draw_area; // $s2
	// 		struct RECT clipped_size; // stack offset -144
	// 		struct VECTOR translate; // stack offset -136

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
			// 		struct VECTOR vec; // stack offset -120
			// 		struct TILE_1 *tile1; // $a0
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
		// 		struct _CAR_DATA *cp; // $s0
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

// [D] [A] partially decompiled due to complexity
void DrawOverheadMap(void)
{
	unsigned char bVar1;
	short sVar2;
	short sVar3;
	ushort uVar7;
	ushort uVar8;
	unsigned char uVar10;
	short *psVar11;
	TILE_1 *tile1;
	POLY_F4 *polyf4;
	int x;
	short *psVar12;
	int y;
	int y_00;
	short *psVar13;
	short *puVar14;
	POLY_F4 *local_a3_2816;
	POLY_FT3 *null;
	SVECTOR *pSVar15;
	long *plVar16;
	SVECTOR *pSVar17;
	long *plVar18;
	SVECTOR *pSVar19;
	char cVar20;
	SVECTOR *pSVar21;
	char cVar22;
	SVECTOR *v0;
	_CAR_DATA *cp;
	char *pcVar24;
	char *pbVar25;
	VECTOR *v1;
	DR_AREA *drarea;
	int r;
	uint *puVar26;
	int iVar27;
	uint uVar28;
	int iVar29;
	uint uVar30;
	SVECTOR MapMesh[5][5];
	VECTOR MapMeshO[5][5];
	MAPTEX MapTex[4];
	SVECTOR direction;
	RECT16 clipped_size;
	VECTOR vec;
	long flag;

	static int flashtimer = 0;
	static int ptab[] = {
		 0xFF, 0xF0, 0xAA, 0x78,
		 0x50, 0x37, 0x26, 0x17,
		 0xD,  0xA,  0x0,  0x0,
		 0x0,  0x0,  0x0,  0x0,
	};

	static int ptab2[] = {
		0xFF, 0xFF, 0xF0, 0xAA,
		0x78, 0x50, 0x37, 0x26,
		0x17, 0xD,  0xA,  0x0, 
		0x0
	};

	VECTOR translate = { 280, 0, 212 };

	if (gMultiplayerLevels != 0)
	{
		DrawMultiplayerMap();
		return;
	}
	if (1 < NumPlayers)
		return;

	SetMapPos();
	uVar28 = x_map & 0x1f;
	uVar30 = y_map & 0x1f;
	draw_box();

	if (0 < player_position_known) 
	{
		if (player[0].playerCarId < 0)
			psVar11 = &pedestrianFelony;
		else 
			psVar11 = &car_data[player[0].playerCarId].felonyRating;

		if (0x292 < *psVar11)
		{
			FlashOverheadMap(ptab[CameraCnt & 0xf], 0, ptab[CameraCnt + 8U & 0xf]);
			goto LAB_00016fac;
		}
	}

	if (player_position_known == -1)
	{
		if (flashtimer == 0)
		{
			if (player[0].playerCarId < 0) 
				psVar11 = &pedestrianFelony;
			else
				psVar11 = &car_data[player[0].playerCarId].felonyRating;

			if (0x292 < *psVar11)
				flashtimer = 0x30;

			goto LAB_00016ee8;
		}
	}
	else 
	{
	LAB_00016ee8:
		if (flashtimer == 0) 
			goto LAB_00016fac;
	}


	flashtimer--;
	r = -flashtimer;

	r = ptab2[r + 47 >> 2] + ptab2[r + 48 >> 2] + ptab2[r + 49 >> 2] + ptab2[r + 50 >> 2];
	r = r >> 2;

	FlashOverheadMap(r, r, r);

LAB_00016fac:

	drarea = (DR_AREA *)current->primptr;
	SetDrawArea(drarea, &current->draw.clip);

	addPrim(current->ot, drarea);
	current->primptr += sizeof(DR_AREA);

	WorldToOverheadMapPositions((VECTOR *)player->pos, &vec, 1, 0, 0);

	if (((vec.vx - 0xe9U < 0x5f) && (0xad < vec.vz)) && (vec.vz < 0xfb)) 
	{
		tile1 = (TILE_1 *)current->primptr;
		setTile1(tile1);

		tile1->r0 = -1;
		tile1->g0 = -1;
		tile1->b0 = -1;

		tile1->x0 = vec.vx;
		tile1->y0 = vec.vz;

		addPrim(current->ot, tile1);
		current->primptr += sizeof(TILE_1);
	}

	DrawTargetBlip((VECTOR *)player, 64, 64, 64, 3);
	DrawCompass();
	DrawOverheadTargets();

	sVar3 = -uVar30;

	cp = car_data;
	do {
		if (cp->controlType == 3 && cp->ai.p.dying == 0 || (cp->controlFlags & 1) != 0)
			DrawSightCone(&copSightData, (VECTOR *)(cp->hd).where.t, cp->hd.direction);

		cp++;
	} while (cp <= &car_data[20]);

	sVar2 = -uVar28;

	UNIMPLEMENTED();

	/*
	if ((uVar28 < 0x10) && (0x10 < old_x_mod))
	{
		r = 0;
		pcVar24 = maptile;
		pbVar25 = maptile + 8;
		do {
			bVar1 = *pcVar24;
			x = x_map >> 5;
			y = y_map >> 5;
			*pcVar24 = pbVar25[-4];
			y = y + r;
			pbVar25[-4] = *pbVar25;
			r = r + 1;
			*pbVar25 = pcVar24[0xc];
			pcVar24[0xc] = bVar1;

			LoadMapTile(bVar1, x + 3, y);

			pcVar24++;
			pbVar25++;
		} while (r < 4);
	}

	if ((0x10 < uVar28) && (old_x_mod < 0x10)) 
	{
		r = 0;
		pcVar24 = maptile;
		pbVar25 = maptile + 0xc;
		do {
			x = r + 4;
			bVar1 = *pbVar25;
			y = x_map >> 5;
			y_00 = (y_map >> 5) + r;
			*pbVar25 = maptile[r + 8];
			pbVar25 = pbVar25 + 1;
			maptile[r + 8] = maptile[x];
			r = r + 1;
			maptile[x] = *pcVar24;
			*pcVar24 = bVar1;
			LoadMapTile(bVar1, y, y_00);
			pcVar24++;
		} while (r < 4);
	}

	if ((uVar30 < 0x10) && (0x10 < old_y_mod))
	{
		r = 0;
		pcVar24 = maptile;
		pbVar25 = maptile + 1;
		do {
			y_00 = r * 4;
			bVar1 = *pcVar24;
			x = (x_map >> 5) + r;
			y = y_map >> 5;
			*pcVar24 = *pbVar25;
			r = r + 1;
			*pbVar25 = maptile[y_00 + 2];
			pbVar25 = pbVar25 + 4;
			maptile[y_00 + 2] = pcVar24[3];
			pcVar24[3] = bVar1;

			LoadMapTile(bVar1, x, y + 3);
			pcVar24++;
		} while (r < 4);
	}

	if ((0x10 < uVar30) && (old_y_mod < 0x10))
	{
		r = 0;
		pcVar24 = maptile;
		pbVar25 = maptile + 3;
		do {
			y_00 = r * 4;
			bVar1 = *pbVar25;
			x = (x_map >> 5) + r;
			y = y_map >> 5;
			*pbVar25 = maptile[y_00 + 2];
			pbVar25 = pbVar25 + 4;
			maptile[y_00 + 2] = maptile[y_00 + 1];
			r = r + 1;
			maptile[y_00 + 1] = *pcVar24;
			*pcVar24 = bVar1;
			LoadMapTile(bVar1, x, y);
			pcVar24++;
		} while (r < 4);
	}
	*/

	old_x_mod = uVar28;
	old_y_mod = uVar30;

	r = 3;
	if (uVar28 != 0)
		r = 4;

	x = 3;

	if (uVar30 != 0)
		x = 4;

	y_00 = 0;
	y = 0;

	/*
	pSVar21 = MapMesh;
	v0 = MapMesh + 5;
	pSVar15 = MapMesh + 10;
	pSVar17 = MapMesh + 15;
	pSVar19 = MapMesh + 20;

	do {
		*(short *)((int)&MapMesh[0].vz + y) = -0x23;
		psVar11 = (short *)((int)&MapMesh[1].vz + y);
		psVar12 = (short *)((int)&MapMesh[2].vz + y);
		psVar13 = (short *)((int)&MapMesh[3].vz + y);
		puVar14 = (short *)((int)&MapMesh[4].vz + y);

		y_00++;
		
		pSVar21->vx = -35;
		v0->vx = sVar2 - 16;
		pSVar15->vx = sVar2 + 16;
		pSVar17->vx = sVar2 + 48;
		pSVar19->vx = 35;


		*psVar11 = sVar3 - 16;
		*psVar12 = sVar3 + 16;
		*psVar13 = sVar3 + 48;
		*puVar14 = 35;

		pSVar21++;
		v0++;
		pSVar15++;
		pSVar17++;
		pSVar19++;

		y = y + 0x28;
	} while (y_00 < 5);*/

	MapTex[0].u = MapMesh[0][0].vx - MapMesh[1][0].vx;

	if (MapMesh[0][0].vx - MapMesh[1][0].vx < 0) 
		MapTex[0].u = MapMesh[1][0].vx - MapMesh[0][0].vx;

	MapTex[0].u = 0x20 - MapTex[0].u;
	MapTex[0].w = MapMesh[0][0].vx - MapMesh[1][0].vx;

	if (MapMesh[0][0].vx - MapMesh[1][0].vx < 0)
		MapTex[0].w = MapMesh[1][0].vx - MapMesh[0][0].vx;

	MapTex[1].w = tile_size;
	MapTex[1].u = 0;
	MapTex[2].u = 0;
	MapTex[3].u = 0;
	MapTex[2].w = tile_size;

	if (MapMesh[3][0].vx - MapMesh[4][0].vx < 0)
		MapTex[3].w = MapMesh[4][0].vx - MapMesh[3][0].vx;
	else
		MapTex[3].w = MapMesh[3][0].vx - MapMesh[4][0].vx;

	if (MapMesh[0][0].vz - MapMesh[0][1].vz < 0)
		MapTex[0].v = MapMesh[0][1].vz - MapMesh[0][0].vz;
	else
		MapTex[0].v = MapMesh[0][0].vz - MapMesh[0][1].vz;

	MapTex[0].v = 0x20 - MapTex[0].v;
	MapTex[0].h = MapMesh[0][0].vz - MapMesh[0][1].vz;

	if (MapMesh[0][0].vz - MapMesh[0][1].vz < 0)
		MapTex[0].h = MapMesh[0][1].vz - MapMesh[0][0].vz;

	MapTex[1].h = tile_size;
	MapTex[1].v = 0;
	MapTex[2].v = 0;
	MapTex[3].v = 0;
	MapTex[2].h = tile_size;

	if (MapMesh[0][3].vz - MapMesh[0][4].vz < 0)
		MapTex[3].h = MapMesh[0][4].vz - MapMesh[0][3].vz;
	else
		MapTex[3].h = MapMesh[0][3].vz - MapMesh[0][4].vz;

	direction.vx = 0;
	direction.vz = 0;
	direction.vy = player[0].dir & 0xfff;

	RotMatrixXYZ(&map_matrix, &direction);
	MulMatrix0(&aspect, &map_matrix, &map_matrix);

	gte_SetRotMatrix(&map_matrix);
	gte_SetTransVector(&translate);

	y = 0;
	while (y <= r)
	{
		v1 = MapMeshO[y];
		v0 = MapMesh[y];

		iVar27 = x + 1;
		while (iVar27 != 0)
		{
			RotTrans(v0, v1, &flag);

			v1++;
			v0++;

			iVar27--;
		}
		y++;
	}
	/*
	y = 0;
	if (x != 0) {
		do {
			y_00 = 0;
			iVar27 = y + 1;
			if (r != 0) {
				pbVar25 = maptile + y;
				iVar29 = 0;
				plVar18 = &MapMeshO[5].vz + iVar27 * 4;
				plVar16 = &MapMeshO[5].vz + y * 4;
				psVar11 = &MapTex[0].w;
				do {
					if ((MapSegmentPos[*pbVar25].x & 0x18U) == 0x18)
						cVar22 = (char)*psVar11 + -1;
					else
						cVar22 = (char)*psVar11;
	
					if ((MapSegmentPos[*pbVar25].y & 0x60U) == 0x60)
						cVar20 = (char)MapTex[y].h + -1;
					else
						cVar20 = (char)MapTex[y].h;

					local_a3_2816 = (POLY_F4 *)current->primptr;
					*(undefined *)((int)&local_a3_2816->tag + 3) = 9;
					local_a3_2816->code = ',';
					uVar10 = 'd';
					if (gTimeOfDay == 3) {
						uVar10 = '2';
					}
					local_a3_2816->r0 = uVar10;
					local_a3_2816->g0 = uVar10;
					local_a3_2816->b0 = uVar10;
					local_a3_2816->code = local_a3_2816->code | 2;
					uVar8 = MapClut;
					local_a3_2816->x0 = *(short *)(plVar16 + -0x16);
					local_a3_2816->y0 = *(short *)(plVar16 + -0x14);
					local_a3_2816->x2 = *(short *)(plVar16 + -2);
					local_a3_2816->y2 = *(short *)plVar16;
					*(short *)&local_a3_2816[1].tag = *(short *)(plVar18 + -0x16);
					*(short *)((int)&local_a3_2816[1].tag + 2) = *(short *)(plVar18 + -0x14);
					uVar7 = MapTPage;
					pcVar24 = (char *)((int)&MapTex[0].u + iVar29);
					local_a3_2816[1].x0 = *(short *)(plVar18 + -2);
					sVar2 = *(short *)plVar18;
					local_a3_2816->y1 = uVar8;
					local_a3_2816->y3 = uVar7;

					local_a3_2816[1].y0 = sVar2;
					psVar12 = &MapTex[y].v;
					*(char *)&local_a3_2816->x1 =
						*pcVar24 + *(char *)&MapSegmentPos[*pbVar25].x * '\x04';
					*(char *)((int)&local_a3_2816->x1 + 1) =
						*(char *)psVar12 + *(char *)&MapSegmentPos[*pbVar25].y;
					*(char *)&local_a3_2816->x3 =
						*pcVar24 + *(char *)&MapSegmentPos[*pbVar25].x * '\x04' + cVar22;
					*(char *)((int)&local_a3_2816->x3 + 1) =
						*(char *)psVar12 + *(char *)&MapSegmentPos[*pbVar25].y;
					iVar29 = iVar29 + 8;
					local_a3_2816[1].r0 = *pcVar24 + *(char *)&MapSegmentPos[*pbVar25].x * '\x04';
					psVar11 = psVar11 + 4;
					local_a3_2816[1].g0 =
						*(char *)psVar12 + *(char *)&MapSegmentPos[*pbVar25].y + cVar20;
					y_00 = y_00 + 1;
					*(char *)&local_a3_2816[1].x1 =
						*pcVar24 + *(char *)&MapSegmentPos[*pbVar25].x * '\x04' + cVar22;
					plVar16 = plVar16 + 0x14;
					*(char *)((int)&local_a3_2816[1].x1 + 1) =
						*(char *)psVar12 + *(char *)&MapSegmentPos[*pbVar25].y + cVar20;
					pDVar9 = current;
					plVar18 = plVar18 + 0x14;
					local_a3_2816->tag = local_a3_2816->tag & 0xff000000 | *current->ot & 0xffffff;
					pbVar25 = pbVar25 + 4;
					*pDVar9->ot = *pDVar9->ot & 0xff000000 | (uint)local_a3_2816 & 0xffffff;
					pDVar9->primptr = pDVar9->primptr + 0x28;
				} while (y_00 < r);
			}
			y = iVar27;
		} while (iVar27 < x);
	}*/

	polyf4 = (POLY_F4 *)current->primptr;

	setPolyF4(polyf4);

	polyf4->r0 = 60;
	polyf4->g0 = 60;
	polyf4->b0 = 60;

	polyf4->y0 = 0xb6;
	polyf4->y1 = 0xb6;
	polyf4->x0 = 0xf5;
	polyf4->x1 = 0x13b;
	polyf4->x2 = 0xf5;
	polyf4->y2 = 0xf2;
	polyf4->x3 = 0x13b;
	polyf4->y3 = 0xf2;

	addPrim(current->ot, polyf4);
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

	clipped_size.x = 250;
	clipped_size.w = 60;
	clipped_size.h = 60;
	clipped_size.y = (current->draw).clip.y + 181;

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
	// 		struct TILE *polys; // $v0
	// 		struct POLY_FT4 *back; // $a1
	// 		struct POLY_FT3 *null; // $a2
	// 		struct SVECTOR Mesh[4]; // stack offset -192
	// 		struct VECTOR MeshO[4]; // stack offset -160
	// 		struct VECTOR target; // stack offset -96
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
			// 		struct VECTOR vec; // stack offset -80
			// 		struct TILE_1 *tile1; // $v1
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

void DrawFullscreenMap(void)
{
	ushort uVar1;
	short sVar2;
	TILE *polys;
	int iVar3;
	TILE_1 *tile1;
	uint uVar4;
	POLY_FT4 *back;
	POLY_FT3 *null;
	VECTOR *v1;
	uint *puVar5;
	SVECTOR *v0;
	int y;
	int iVar6;
	int x;
	SVECTOR mesh[4];
	VECTOR meshO[4];
	VECTOR target;
	VECTOR vec;
	long flag;
	int width;
	int height;
	int local_34;
	VECTOR *local_30;

	if ((Pads[0].dirnew & 0x20) != 0) 
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

	WorldToFullscreenMap((VECTOR *)player, &player_position);

	if (gUseRotatedMap != 0) 
	{
		if ((Pads[0].direct & 0x8000) == 0) {
			if ((Pads[0].direct & 0x2000) != 0) {
				map_x_offset = map_x_offset + -8;
			}
		}
		else {
			map_x_offset = map_x_offset + 8;
		}
		if ((Pads[0].direct & 0x1000) == 0) {
			if ((Pads[0].direct & 0x4000) != 0) {
				map_z_offset = map_z_offset + -8;
			}
		}
		else {
			map_z_offset = map_z_offset + 8;
		}
		if (map_x_offset < -0x80) {
			map_x_offset = -0x80;
		}
		if (0x80 < map_x_offset) {
			map_x_offset = 0x80;
		}
		if (map_z_offset < -0x80) {
			map_z_offset = -0x80;
		}
		if (0x80 < map_z_offset) {
			map_z_offset = 0x80;
		}
		map_x_shift = 0;
		map_z_shift = 0;
		goto LAB_00017f8c;
	}

	map_x_offset = (player_position.vx + 0xa0) - width;

	if ((player_position.vx + 0xa0 <= width) &&
		(map_x_offset = player_position.vx + -0xa0, -1 < map_x_offset))
	{
		map_x_offset = 0;
	}

	map_z_offset = (player_position.vz + 0x80) - height;

	if ((player_position.vz + 0x80 <= height) && (map_z_offset = player_position.vz + -0x80, -1 < map_z_offset)) 
	{
		map_z_offset = 0;
	}
	if ((Pads[0].direct & 0x8000) == 0)
	{
		if (((Pads[0].direct & 0x2000) != 0) &&
			(iVar3 = map_x_shift + -8,
			((player_position.vx - map_x_offset) + 0xa0) - map_x_shift < width)) 
			goto LAB_00017f0c;
	}
	else
	{
		iVar3 = map_x_shift + 8;
		if (0 < ((player_position.vx - map_x_offset) + -0xa0) - map_x_shift) {
		LAB_00017f0c:
			map_x_shift = iVar3;
		}
	}

	if ((Pads[0].direct & 0x1000) == 0) 
	{
		if (((Pads[0].direct & 0x4000) != 0) &&
			(iVar3 = map_z_shift + -8,
			((player_position.vz - map_z_offset) + 0x80) - map_z_shift < height)) goto LAB_00017f64;
	}
	else 
	{
		iVar3 = map_z_shift + 8;
		if (0 < ((player_position.vz - map_z_offset) + -0x80) - map_z_shift) {
		LAB_00017f64:
			map_z_shift = iVar3;
		}
	}

	map_x_offset = map_x_offset + map_x_shift;
	map_z_offset = map_z_offset + map_z_shift;
LAB_00017f8c:

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

	local_30 = &target;
	local_34 = 0;
	while (true) {
		x = local_34;
		iVar3 = width;

		if (iVar3 >> 5 <= x)
			break;

		local_34 = x + 1;
		iVar3 = 0;

		while (true) 
		{
			y = iVar3;
			iVar3 = height;

			iVar6 = 0;

			if (iVar3 >> 5 <= y)
				break;

			puVar5 = (uint *)&meshO[0].vz;
			v1 = meshO;
			v0 = mesh;
			iVar3 = 3;
			mesh[0].vy = 0;
			mesh[1].vy = 0;
			mesh[2].vy = 0;
			mesh[3].vy = 0;
			mesh[0].vx = (short)x * 0x20 - (short)player_position.vx;
			mesh[1].vx = mesh[0].vx + 0x20;
			mesh[0].vz = (short)y * 0x20 - (short)player_position.vz;
			mesh[2].vz = mesh[0].vz + 0x20;
			mesh[1].vz = mesh[0].vz;
			mesh[2].vx = mesh[0].vx;
			mesh[3].vx = mesh[1].vx;
			mesh[3].vz = mesh[2].vz;

			do {
				RotTrans(v0, v1, &flag);
				v1->vx = v1->vx + map_x_offset;
				uVar4 = *puVar5;
				*puVar5 = uVar4 + map_z_offset;

				if ((0x140 < v1->vx) || (0x100 < uVar4 + map_z_offset)) {
					iVar6 = iVar6 + 1;
				}

				puVar5 = puVar5 + 4;
				v1 = v1 + 1;
				iVar3 = iVar3 + -1;
				v0 = v0 + 1;
			} while (-1 < iVar3);

			iVar3 = y + 1;

			if(iVar6 != 4) 
			{
				LoadMapTile(0, x, y);

				back = (POLY_FT4 *)current->primptr;
				setPolyFT4(back);

				back->r0 = 88;
				back->g0 = 88;
				back->b0 = 88;

				back->x0 = meshO[0].vx;
				back->y0 = meshO[0].vz;
				back->x1 = meshO[1].vx;
				back->y1 = meshO[1].vz;
				back->x2 = meshO[2].vx;
				back->y2 = meshO[2].vz;
				back->x3 = meshO[3].vx;
				back->y3 = meshO[3].vz;
				back->u0 = MapSegmentPos[0].x << 2;
				back->v0 = MapSegmentPos[0].y;
				back->u1 = MapSegmentPos[0].x * '\x04' + '\x1f';
				back->v1 = MapSegmentPos[0].y;
				back->u2 = MapSegmentPos[0].x << 2;
				back->v2 = MapSegmentPos[0].y + '\x1f';
				back->u3 = MapSegmentPos[0].x * '\x04' + '\x1f';
				back->v3 = MapSegmentPos[0].y + '\x1f';
				back->clut = MapClut;
				back->tpage = MapTPage;

				DrawPrim(back);
				DrawSync(0);
			}
		}
	}

	target.vx = 160;
	target.vz = 128;

	DrawFullscreenTargets();

	if (gUseRotatedMap == 0)
		DrawBigCompass(local_30, 0);
	else 
		DrawBigCompass(local_30, player[0].dir);

	DrawTargetBlip(local_30, 64, 64, 64, 14);

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

	SetTextColour(0x80, 0x80, 0x80);

	PrintStringCentred("\x80 Exit \x81 Rotation \x8a Move", 0xe2);
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
	// 		struct _CAR_DATA *cp; // $s0
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

// [D]
void DrawCopIndicators(void)
{
	short sVar1;
	short sVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	_CAR_DATA *cp;

	sVar1 = rcossin_tbl[(player[0].dir & 0xfffU) * 2 + 1];
	sVar2 = rcossin_tbl[(player[0].dir & 0xfffU) * 2];

	cp = car_data;
	do {
		if ((cp->controlType == 3) && (cp->ai.p.dying == 0))
		{
			iVar6 = cp->hd.where.t[0] - player[0].pos[0];
			iVar4 = cp->hd.where.t[2] - player[0].pos[2];

			iVar5 = FIXED(iVar6 * sVar1 - iVar4 * sVar2) * 3;

			iVar5 = iVar5 >> 2;
			iVar3 = FIXED(iVar6 * sVar2 + iVar4 * sVar1);

			iVar4 = -iVar3;
			iVar6 = iVar5;

			if (iVar5 < 0)
				iVar6 = -iVar5;
			
			if (iVar6 < iVar4)
			{
				iVar5 = (iVar5 * 0x10a) / iVar4;
				iVar4 = (iVar4 >> 3) + 600;

				CopIndicator(iVar5 + 0xa0, 0x3fff0 / iVar4);
			}
		}
		cp++;
	} while (cp <= &car_data[20]);
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitMultiplayerMap()
 // line 1678, offset 0x000198e0
	/* begin block 1 */
		// Start line: 1680
		// Start offset: 0x000198E0
		// Variables:
	// 		struct RECT rect; // stack offset -48
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

// [D]
void InitMultiplayerMap(void)
{
	RECT16 rect;
	char filename[32];

	if (MissionHeader->region != 0)
	{
		sprintf(filename, "MAPS\\REG%d.%d", MissionHeader->region, GameLevel);

		if (FileExists(filename) != 0)
		{
			Loadfile(filename, MapBitMaps);
			rect.w = 0x10;
			rect.h = 0x40;
			rect.x = MapRect.x + MapSegmentPos[0].x;
			rect.y = MapRect.y + MapSegmentPos[0].y;
			LoadImage(&rect, (u_long *)MapBitMaps);

			DrawSync(0);
		}
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
	// 		struct POLY_FT4 *poly; // $a2
	// 		struct LINE_F2 *line2; // $s1
	// 		struct VECTOR target; // stack offset -64
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

// [D]
void DrawMultiplayerMap(void)
{
	short uVar1;
	ushort uVar2;
	ulong *puVar4;
	POLY_FT4 *poly;
	char *pcVar5;
	_PLAYER *pPVar6;
	int iVar7;
	char *pcVar8;
	unsigned char g;
	unsigned char r;
	int iVar9;
	short sVar10;
	int yPos;
	VECTOR target;
	int local_30;
	int local_2c;

	map_x_offset = 0;
	map_z_offset = 0;
	yPos = 96;

	if (NumPlayers == 1)
		yPos = 172;

	if (MissionHeader->region != 0) 
	{
		iVar7 = 0;
		DrawMultiplayerTargets();

		local_2c = yPos + 64;
		local_30 = yPos - 1;

		if (NumPlayers != 0) 
		{
			pPVar6 = player;
			r = -1;
			g = 0;
			do {
				target.vx = pPVar6->pos[0];
				target.vz = pPVar6->pos[2];
				iVar7 ++;
				target.vy = 0;

				WorldToMultiplayerMap(&target, &target);

				target.vx += 240;
				target.vz += yPos;

				DrawPlayerDot(&target, -pPVar6->dir, r, g, 0, 8);

				pPVar6++;
				r++;
				g--;
			} while (iVar7 < (int)(uint)NumPlayers);
		}

		poly = (POLY_FT4 *)current->primptr;
		setPolyFT4(poly);
		setSemiTrans(poly, 1);
		poly->x0 = 0xf0;
		poly->y0 = yPos;
		poly->x1 = 0x130;
		poly->y1 = yPos;
		poly->x2 = 0xf0;
		poly->x3 = 0x130;
		poly->y2 = local_2c;
		poly->y3 = local_2c;
		poly->u0 = MapSegmentPos[0].x << 2;
		poly->v0 = MapSegmentPos[0].y;
		poly->u1 = MapSegmentPos[0].x * '\x04' + '?';
		poly->v1 = MapSegmentPos[0].y;
		poly->u2 = MapSegmentPos[0].x << 2;
		poly->v2 = MapSegmentPos[0].y + '?';
		poly->u3 = MapSegmentPos[0].x * '\x04' + '?';
		poly->v3 = MapSegmentPos[0].y + '?';
		poly->clut = MapClut;
		poly->tpage = MapTPage;

		r = 100;
		if (gTimeOfDay == 3) 
			r = 50;

		poly->r0 = r;
		poly->g0 = r;
		poly->b0 = r;

		addPrim(current->ot, poly);
		current->primptr += sizeof(POLY_FT4);

		LINE_F4* linef4 = (LINE_F4*)current->primptr;
		setLineF4(linef4);
		
		linef4->r0 = 0;
		linef4->g0 = 0;
		linef4->b0 = 0x80;

		linef4->x0 = 239;
		linef4->y0 = yPos - 1;
		linef4->x1 = 304;
		linef4->x2 = 304;
		linef4->y1 = yPos - 1;
		linef4->x3 = 240;
		linef4->y2 = yPos + 64;
		linef4->y3 = yPos + 64;

		addPrim(current->ot+1, linef4);
		current->primptr += sizeof(LINE_F4);

		LINE_F2* linef2 = (LINE_F2*)current->primptr;
		setLineF2(linef2);

		linef2->r0 = 0;
		linef2->g0 = 0;
		linef2->b0 = 0x80;

		linef2->x0 = 239;
		linef2->y0 = yPos;
		linef2->x1 = 239;
		linef2->y1 = yPos + 64;

		addPrim(current->ot + 1, linef2);
		current->primptr += sizeof(LINE_F2);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToMultiplayerMap(struct VECTOR *in /*$a3*/, struct VECTOR *out /*$a2*/)
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

// [D]
void WorldToMultiplayerMap(VECTOR *in, VECTOR *out)
{
	int iVar1;
	int iVar2;
	int iVar3;

	if (MissionHeader->region != 0)
	{
		iVar3 = MissionHeader->region / regions_across;
		iVar2 = in->vx - ((MissionHeader->region % regions_across) * 0x10000 - cells_across * 1024);
		iVar1 = cells_down * -1024;

		out->vx = iVar2 >> 0xb;

		iVar1 = in->vz - ((iVar3-1) * 0x10000 + iVar1);

		out->vz = 64 - (iVar1 >> 0xb);
		return;
	}

	out->vx = 32;
	out->vz = 32;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessPalletLump(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
 // line 1970, offset 0x00019f44
	/* begin block 1 */
		// Start line: 1971
		// Start offset: 0x00019F44
		// Variables:
	// 		int total_cluts; // $v0
	// 		int clutValue; // $s1
	// 		int tpageindex; // $s2
	// 		int texnum; // $s3
	// 		int palette; // $s4
	// 		int clut_number; // $v1
	// 		unsigned short clutTable[320]; // stack offset -680
	// 		char *buffPtr; // $s0

		/* begin block 1.1 */
			// Start line: 2013
			// Start offset: 0x00019FD0
		/* end block 1.1 */
		// End offset: 0x00019FD0
		// End Line: 2013
	/* end block 1 */
	// End offset: 0x0001A094
	// End Line: 2034

	/* begin block 2 */
		// Start line: 8209
	/* end block 2 */
	// End Line: 8210

	/* begin block 3 */
		// Start line: 3940
	/* end block 3 */
	// End Line: 3941

unsigned short civ_clut[8][32][6];

// [D]
void ProcessPalletLump(char *lump_ptr, int lump_size)
{
	extern bool gDriver1Level;
	if (gDriver1Level)
		return;

	char cVar1;
	ushort uVar2;
	int *local_s0_96;
	int *local_s0_228;
	int iVar3;
	int iVar4;
	u_short *puVar5;
	unsigned short clutTable[320];

	if ((*(int *)lump_ptr != 0) && (*(int *)(lump_ptr + 4) != -1)) 
	{
		local_s0_96 = (int *)(lump_ptr + 4);

		puVar5 = (u_short *)clutTable;
		do {
			iVar4 = *local_s0_96;
			iVar3 = local_s0_96[1];

			cVar1 = GetCarPalIndex(local_s0_96[2]);

			local_s0_228 = local_s0_96 + 4;

			if (local_s0_96[3] == -1) {
				LoadImage(&clutpos, (u_long *)local_s0_228);

				local_s0_228 = local_s0_96 + 12;

				uVar2 = GetClut((int)clutpos.x, (int)clutpos.y);

				*puVar5 = uVar2;
				puVar5 = puVar5 + 1;
				IncrementClutNum(&clutpos);
			}
			else {
				uVar2 = clutTable[local_s0_96[3]];
			}

			civ_clut[cVar1][iVar3][iVar4 + 1] = uVar2;

			local_s0_96 = local_s0_228;

		} while (*local_s0_228 != -1);
	}

	//Emulator_SaveVRAM("VRAM_CLUTS.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
}



// decompiled code
// original method signature: 
// void /*$ra*/ load_civ_palettes(struct RECT *cluts /*$a0*/)
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
	// 		struct TILE *tile; // $a3
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

// [D]
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

	prim->x0 = 0xfa;
	prim->y0 = 0xb6;
	prim->w = 0x3c;
	prim->h = 0x3c;

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
	// 		struct RECT MapSegment; // stack offset -16
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

void LoadMapTile(int tpage, int x, int y)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	char *pcVar2;
	int iVar3;
	short local_10;
	short local_e;
	undefined2 local_c;
	undefined2 local_a;

	local_c = 8;
	local_a = 0x20;
	local_e = MapRect.y + (&MapSegmentPos)[tpage].y;
	local_10 = MapRect.x + (&MapSegmentPos)[tpage].x;
	iVar3 = x + y * tilehnum;
	if ((((iVar3 < (int)(uint)(byte)overlaidmaps[GameLevel].toptile) && (-1 < iVar3)) && (-1 < x << 5)
		) && (x << 5 < overlaidmaps[GameLevel].width)) {
		UnpackRNC(MapBitMaps + *(ushort *)(MapBitMaps + iVar3 * 2), MapBuffer);
	}
	else {
		iVar3 = 0x1ff;
		pcVar2 = CHAR_ARRAY_000aba47;
		cVar1 = overlaidmaps[GameLevel].dummy;
		do {
			*pcVar2 = cVar1;
			iVar3 = iVar3 + -1;
			pcVar2 = pcVar2 + -1;
		} while (-1 < iVar3);
	}
	DrawSync(0);
	LoadImage(&local_10, MapBuffer);
	DrawSync(0);
	return;*/
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

// [D]
void SetMapPos(void)
{
	int iVar1;

	iVar1 = overlaidmaps[GameLevel].scale;

	x_map = overlaidmaps[GameLevel].x_offset + player[0].pos[0] / iVar1;
	y_map = overlaidmaps[GameLevel].y_offset - player[0].pos[2] / iVar1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ draw_box()
 // line 2405, offset 0x00018bf4
	/* begin block 1 */
		// Start line: 2407
		// Start offset: 0x00018BF4
		// Variables:
	// 		struct LINE_F4 *line4; // $s0
	// 		struct LINE_F2 *line2; // $s1
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

// [D]
void draw_box(void)
{
	LINE_F4* linef4 = (LINE_F4*)current->primptr;
	setLineF4(linef4);

	linef4->r0 = 0;
	linef4->g0 = 0;
	linef4->b0 = 128;

	linef4->x0 = 249;
	linef4->y0 = 181;

	linef4->x1 = 310;
	linef4->x2 = 310;

	linef4->y1 = 181;
	linef4->x3 = 249;

	linef4->y2 = 241;
	linef4->y3 = 241;

	addPrim(current->ot + 1, linef4);
	current->primptr += sizeof(LINE_F4);

	LINE_F2* linef2 = (LINE_F2*)current->primptr;
	setLineF2(linef2);

	linef2->r0 = 0;
	linef2->g0 = 0;
	linef2->b0 = 128;

	linef2->x0 = 249;
	linef2->y0 = 181;
	linef2->x1 = 249;
	linef2->y1 = 241;

	addPrim(current->ot + 1, linef2);
	current->primptr += sizeof(LINE_F2);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawN(struct VECTOR *pScreenPosition /*$s2*/, int direct /*$s7*/)
 // line 2435, offset 0x00018d54
	/* begin block 1 */
		// Start line: 2436
		// Start offset: 0x00018D54
		// Variables:
	// 		struct XYPAIR lastPoint; // stack offset -48
	// 		struct XYPAIR *pPoint; // $s0
	// 		char loop; // $s4

		/* begin block 1.1 */
			// Start line: 2446
			// Start offset: 0x00018DC4
			// Variables:
		// 		struct LINE_F2 *pLine; // $a2
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

// [D]
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
	// 		struct VECTOR position[5]; // stack offset -88
	// 		struct XYPAIR *pNorth; // $a1
	// 		int scale; // $a0

		/* begin block 1.1 */
			// Start line: 2482
			// Start offset: 0x00018F18
			// Variables:
		// 		char loop; // $t2
		// 		struct VECTOR *pPosition; // $a3
		// 		void *pot; // $s0

			/* begin block 1.1.1 */
				// Start line: 2511
				// Start offset: 0x000190B8
				// Variables:
			// 		struct LINE_G2 *pLine; // $a0
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

// [D]
void DrawCompass(void)
{
	int i;
	LINE_G2 *lineg2;
	VECTOR *pPosition;
	OTTYPE *potz;
	VECTOR position[5];

	position[1].vx = north[GameLevel].x * overlaidmaps[GameLevel].scale;
	position[1].vz = north[GameLevel].y * overlaidmaps[GameLevel].scale;
	position[0].vx = position[1].vx * 0x14 + 8 >> 4;
	position[2].vx = position[1].vx + 2 >> 2;
	position[0].vz = position[1].vz * 0x14 + 8 >> 4;
	position[2].vz = position[1].vz + 2 >> 2;
	position[3].vx = (position[1].vz - position[1].vx) * 0xab >> 10;
	position[3].vz = (-position[1].vx - position[1].vz) * 0xab >> 10;
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
	i = 0;
	do {
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
		i++;
	} while (i < 3);

	DrawN(position, 0);

	TransparencyOn(potz, 0x20);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawBigCompass(struct VECTOR *root /*$a0*/, int angle /*$a1*/)
 // line 2534, offset 0x00019194
	/* begin block 1 */
		// Start line: 2535
		// Start offset: 0x00019194
		// Variables:
	// 		struct VECTOR position[5]; // stack offset -96
	// 		struct VECTOR *pPosition; // $s0
	// 		char loop; // $s1

		/* begin block 1.1 */
			// Start line: 2557
			// Start offset: 0x00019300
			// Variables:
		// 		struct LINE_G2 *pLine; // $a1
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

// [D]
void DrawBigCompass(VECTOR *root, int angle)
{
	int i;
	uint uVar3;
	LINE_G2 *lineg2;
	int uVar4;
	int uVar5;
	VECTOR *pPosition;
	VECTOR position[5];

	uVar4 = big_north[GameLevel] + angle & 0xfff;

	position[2].vx = root->vx + map_x_offset;
	position[2].vy = root->vz + map_z_offset;
	position[1].vx = position[2].vx + (rcossin_tbl[uVar4 * 2] * 0x19 >> 0xc);
	position[0].vx = position[2].vx + (rcossin_tbl[uVar4 * 2] * 0xf >> 0xb);

	uVar3 = uVar4 - 200 & 0xfff;
	uVar5 = uVar4 + 200 & 0xfff;

	position[1].vy = position[2].vy + (rcossin_tbl[uVar4 * 2 + 1] * 0x19 >> 0xc);
	position[0].vz = position[2].vy + (rcossin_tbl[uVar4 * 2 + 1] * 0xf >> 0xb);
	position[3].vx = position[2].vx + (rcossin_tbl[uVar3 * 2] * 5 >> 10);
	position[3].vy = position[2].vy + (rcossin_tbl[uVar3 * 2 + 1] * 5 >> 10);
	position[4].vx = position[2].vx + (rcossin_tbl[uVar5 * 2] * 5 >> 10);
	position[4].vy = position[2].vy + (rcossin_tbl[uVar5 * 2 + 1] * 5 >> 10);

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
	// 		struct POLY_F3 *tri; // $a2
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

// [D] [A] colour values might be wrong
void CopIndicator(int xpos, int strength)
{
	int str2;
	POLY_F3 *poly;
	int iVar5;

	if (strength > 255)
		strength = 255;

	iVar5 = strength * (strength + 0x100);
	poly = (POLY_F3 *)current->primptr;

	setPolyF3(poly);
	setSemiTrans(poly, 1);

	poly->r0 = strength;

	str2 = (strength >> 2);

	poly->g0 = str2;
	poly->b0 = str2;
	poly->x0 = xpos - 0xc;
	poly->y0 = 0x100;
	poly->x1 = xpos;
	poly->y1 = 0xe2;
	poly->x2 = xpos + 0xc;
	poly->y2 = 0x100;

	addPrim(current->ot + 1, poly);
	current->primptr += sizeof(POLY_F3);

	TransparencyOn(current->ot + 1, 0x20);

	poly = (POLY_F3 *)current->primptr;

	setPolyF3(poly);
	setSemiTrans(poly, 1);

	str2 = (iVar5 >> 9);

	poly->r0 = str2;
	poly->g0 = str2;
	poly->b0 = str2;

	poly->x0 = xpos - 0xc;
	poly->y0 = 0x100;
	poly->y1 = 0xe2;
	poly->x2 = xpos + 0xc;
	poly->y2 = 0x100;
	poly->x1 = xpos;

	addPrim(current->ot + 1, poly);
	current->primptr += sizeof(POLY_F3);

	TransparencyOn(current->ot + 1, 0x40);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSightCone(struct COP_SIGHT_DATA *pCopSightData /*$a0*/, struct VECTOR *pPosition /*$a1*/, int direction /*$t6*/)
 // line 2609, offset 0x00019594
	/* begin block 1 */
		// Start line: 2610
		// Start offset: 0x00019594
		// Variables:
	// 		struct VECTOR vertex[9]; // stack offset -160
	// 		struct VECTOR *pVertex; // $t0
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
		// 		struct VECTOR *pVertex; // $a2
		// 		void *pot; // $a3

			/* begin block 1.2.1 */
				// Start line: 2651
				// Start offset: 0x000196B8
				// Variables:
			// 		struct POLY_G3 *poly; // $a1
			// 		struct VECTOR *pNextVertex; // $a0
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

// [D]
void DrawSightCone(COP_SIGHT_DATA *pCopSightData, VECTOR *pPosition, int direction)
{
	short sVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	int uVar7;
	VECTOR *pVVar8;
	VECTOR *pNextVertex;
	POLY_G3 *poly;
	int iVar9;
	ulong *potz;
	VECTOR *pVertex;
	VECTOR *pVVar10;
	VECTOR vertex[9];

	
	
	sVar1 = pCopSightData->frontViewDistance;
	sVar2 = pCopSightData->surroundViewDistance;
	sVar3 = pCopSightData->frontViewAngle;
	vertex[0].vx = pPosition->vx;
	vertex[0].vz = pPosition->vz;

	pVVar10 = vertex + 1;
	pVertex = pVVar10;
	
	iVar9 = 0;
	do {
		if ((iVar9 <= sVar3) || (sVar4 = sVar2, 0x1000 - sVar3 <= iVar9)) 
		{
			sVar4 = sVar1;
		}

		uVar7 = iVar9 + direction & 0xfff;

		iVar9 = iVar9 + 0x200;
		pVertex->vx = vertex[0].vx + FIXED(rcossin_tbl[uVar7 * 2] * sVar4);
		pVertex->vz = vertex[0].vz + FIXED(rcossin_tbl[uVar7 * 2 + 1] * sVar4);
		pVertex = pVertex + 1;
	} while (iVar9 < 0x1000);

	WorldToOverheadMapPositions(vertex, vertex, 9, 0, 0);

	pVertex = pVVar10;

	while (pVertex < &vertex[9])
	{
		pVVar8 = pVertex + 1;
		
		pNextVertex = pVVar8;

		if (vertex + 8 < pVVar8)
			pNextVertex = pVVar10;
	
		poly = (POLY_G3 *)current->primptr;
		setPolyG3(poly);
		setSemiTrans(poly, 1);

		poly->x0 = vertex[0].vx;
		poly->y0 = vertex[0].vz;
		poly->x1 = pVertex->vx;
		poly->y1 = pVertex->vz;
		poly->x2 = pNextVertex->vx;
		poly->y2 = pNextVertex->vz;

		poly->r0 = 96;
		poly->g0 = 96;
		poly->b0 = 96;
		poly->r1 = 0;
		poly->g1 = 0;
		poly->b1 = 0;
		poly->r2 = 0;
		poly->g2 = 0;
		poly->b2 = 0;
		
		addPrim(current->ot, poly);

		current->primptr += sizeof(POLY_G3);
		pVertex = pVVar8;
	}

	TransparencyOn(current->ot, 0x20);
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToOverheadMapPositions(struct VECTOR *pGlobalPosition /*$s1*/, struct VECTOR *pOverheadMapPosition /*$s3*/, int count /*$s2*/, char inputRelative /*$s5*/, int outputRelative /*stack 16*/)
 // line 2703, offset 0x00019af0
	/* begin block 1 */
		// Start line: 2704
		// Start offset: 0x00019AF0
		// Variables:
	// 		struct MATRIX TempMatrix; // stack offset -80
	// 		int sin; // $a1
	// 		int cos; // $a2
	// 		int angle; // $v1
	// 		int scale; // $s0

		/* begin block 1.1 */
			// Start line: 2745
			// Start offset: 0x00019C20
			// Variables:
		// 		struct SVECTOR tempVector; // stack offset -48
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

// [D]
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
		tempMatrix.t[0] = 280;
		tempMatrix.t[2] = 212;
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
	// 		struct VECTOR translate; // stack offset -32
	// 		struct SVECTOR direction; // stack offset -16
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

// [D]
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
	MulMatrix0(&aspect, &map_matrix, &map_matrix);

	gte_SetRotMatrix(&map_matrix);
	gte_SetTransVector(&translate);
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToFullscreenMap(struct VECTOR *in /*$a0*/, struct VECTOR *out /*$a1*/)
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

// [D]
void WorldToFullscreenMap(VECTOR *in, VECTOR *out)
{
	out->vy = 0;
	out->vx = overlaidmaps[GameLevel].x_offset + in->vx / overlaidmaps[GameLevel].scale + 49;
	out->vz = overlaidmaps[GameLevel].y_offset - (in->vz / overlaidmaps[GameLevel].scale - 49);
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToFullscreenMap2(struct VECTOR *in /*$a0*/, struct VECTOR *out /*$a1*/)
 // line 2806, offset 0x00019e7c
	/* begin block 1 */
		// Start line: 2807
		// Start offset: 0x00019E7C
		// Variables:
	// 		struct SVECTOR pos; // stack offset -24
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

// [D]
void WorldToFullscreenMap2(VECTOR *in, VECTOR *out)
{
	SVECTOR pos;
	long flag;

	pos.vy = 0;
	pos.vx = (overlaidmaps[GameLevel].x_offset + (in->vx / overlaidmaps[GameLevel].scale) + 49) - player_position.vx;
	pos.vz = (overlaidmaps[GameLevel].y_offset - ((in->vz / overlaidmaps[GameLevel].scale) - 49)) - player_position.vz;

	RotTrans(&pos, out, &flag);
}





