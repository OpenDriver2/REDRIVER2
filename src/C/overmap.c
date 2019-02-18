#include "../decomp_defs.h"

OVERMAP overlaidmaps[4] =
{
  { 197, 318, 384, 672, '\xFC', '\x99', 2145 },
  { 229, 85, 544, 352, '\xBB', '\x88', 2048 },
  { 68, 457, 288, 672, '\xBD', '\xBB', 1911 },
  { 159, 207, 416, 576, '\xFC', 'D', 2048 }
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

XYPAIR NVertex[4] = { { -2, 3 }, { -2, -3 }, { 2, 3 }, { 2, -3 } };

XYPAIR north[4] = { { 0, 20 }, { 0, 20 }, { 0, 20 }, { 0, 20 } };

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

/*
 * Offset 0x162E8
 * D:\driver2\game\C\OVERMAP.C (line 685)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawTargetBlip(struct VECTOR *pos /*$t0*/, unsigned char r /*$s2*/, unsigned char g /*$s3*/, unsigned char b /*$s4*/, unsigned long flags /*stack 16*/)
{ // line 1, address 0x162e8
	struct POLY_FT4 *poly; // $t0
	struct VECTOR vec; // stack address -40
	int ysize; // $a2
} // line 74, address 0x165c0
/*
 * Offset 0x165E0
 * D:\driver2\game\C\OVERMAP.C (line 815)
 * Stack frame base $sp, length 80
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawTargetArrow(struct VECTOR *pos /*$a2*/, unsigned long flags /*$s3*/)
{ // line 1, address 0x165e0
	struct VECTOR vec; // stack address -56
	struct VECTOR vec2; // stack address -40
	struct POLY_FT3 *null; // $t1
	struct POLY_G3 *poly; // $s2
	int dx; // $s1
	int dy; // $s0
} // line 60, address 0x1687c
/*
 * Offset 0x1687C
 * D:\driver2\game\C\OVERMAP.C (line 883)
 * Stack frame base $sp, length 192
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DrawPlayerDot(struct VECTOR *pos /*$a1*/, short rot /*$s2*/, unsigned char r /*$s5*/, unsigned char g /*$s4*/, int b /*stack 16*/, unsigned long flags /*stack 20*/)
{ // line 1, address 0x1687c
	struct MATRIX matrix; // stack address -168
	struct VECTOR direction; // stack address -136
	struct SVECTOR apos[3]; // stack address -120
	struct VECTOR opos[3]; // stack address -96
	struct POLY_F3 *poly; // $t0
	struct VECTOR vec; // stack address -48
} // line 63, address 0x16b2c
/*
 * Offset 0x16B50
 * D:\driver2\game\C\OVERMAP.C (line 954)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ProcessOverlayLump(char *lump_ptr /*$s1*/, int lump_size /*$s0*/)
{ // line 1, address 0x16b50
	struct TEXTURE_DETAILS info; // stack address -32
	int i; // $a1
	int x; // $v0
	int y; // $a0
} // line 32, address 0x16c74
/*
 * Offset 0x16C74
 * D:\driver2\game\C\OVERMAP.C (line 994)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: ra
 */
unsigned long /*$ra*/ Long2DDistance(struct VECTOR *pPoint1 /*$a0*/, struct VECTOR *pPoint2 /*$a2*/)
{ // line 1, address 0x16c74
	struct VECTOR delta; // stack address -24
	unsigned int result; // $v0
	{ // line 7, address 0x16cb8
		int Theta; // $v1
		int tempTheta; // $v0
		{ // line 15, address 0x16cd8
			int cos; // $v1
		} // line 23, address 0x16d04
		{ // line 28, address 0x16d0c
			int sin; // $v1
		} // line 38, address 0x16d6c
	} // line 39, address 0x16d6c
} // line 42, address 0x16d7c
/*
 * Offset 0x16D7C
 * D:\driver2\game\C\OVERMAP.C (line 1077)
 * Stack frame base $sp, length 808
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawOverheadMap()
{ // line 2, address 0x16d7c
	int width; // $t5
	int height; // $t4
	int count; // $s2
	int count1; // $s3
	int tpage; // $t1
	int x_mod; // $s5
	int y_mod; // $fp
	int MeshWidth; // $s6
	int MeshHeight; // $s7
	long flag; // stack address -104
	struct SVECTOR MapMesh[5][5]; // stack address -784
	struct VECTOR MapMeshO[5][5]; // stack address -584
	struct MAPTEX MapTex[4]; // stack address -184
	struct SVECTOR direction; // stack address -152
	struct POLY_FT4 *spt; // $a3
	struct POLY_F4 *sptb; // $a0
	struct DR_AREA *draw_area; // $s2
	struct RECT clipped_size; // stack address -144
	struct VECTOR translate; // stack address -136
	{ // line 35, address 0x16e8c
		static int ptab[] = { 0xFF, 0xF0, 0xAA, 0x78, 0x50, 0x37, 0x26, 0x17, 0xD, 0xA, 0, 0, 0, 0, 0, 0 };
	} // line 36, address 0x16e8c
	{ // line 48, address 0x16f60
		static int ptab[] = { 0xFF, 0xFF, 0xF0, 0xAA, 0x78, 0x50, 0x37, 0x26, 0x17, 0xD, 0xA, 0 };
		int intens; // $a1
	} // line 58, address 0x17010
	{ // line 62, address 0x17010
		{ // line 62, address 0x17010
			struct VECTOR vec; // stack address -120
			struct TILE_1 *tile1; // $a0
		} // line 65, address 0x1715c
	} // line 65, address 0x1715c
	{ // line 69, address 0x1715c
		struct _CAR_DATA *cp; // $s0
	} // line 84, address 0x17280
	{ // line 91, address 0x172a8
	} // line 93, address 0x172a8
	{ // line 108, address 0x17328
	} // line 110, address 0x17328
	{ // line 125, address 0x173b4
	} // line 127, address 0x173b4
	{ // line 142, address 0x17448
	} // line 144, address 0x17448
} // line 290, address 0x17c68
/*
 * Offset 0x17C98
 * D:\driver2\game\C\OVERMAP.C (line 1374)
 * Stack frame base $sp, length 216
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawFullscreenMap()
{ // line 2, address 0x17c98
	struct TILE *polys; // $v0
	struct POLY_FT4 *back; // $a1
	struct POLY_FT3 *null; // $a2
	struct SVECTOR Mesh[4]; // stack address -192
	struct VECTOR MeshO[4]; // stack address -160
	struct VECTOR target; // stack address -96
	long flag; // stack address -64
	long count; // $s4
	int width; // stack address -60
	int height; // stack address -56
	int x; // $s7
	int y; // $s3
	int min_x; // $a0
	int max_x; // $v0
	int min_y; // $v1
	int max_y; // $v1
	{ // line 65, address 0x17e98
		int px; // $a2
		int pz; // $a1
	} // line 126, address 0x17ff0
	{ // line 180, address 0x1805c
		int clipped; // $s5
	} // line 232, address 0x18278
	{ // line 246, address 0x18318
		{ // line 246, address 0x18318
			struct VECTOR vec; // stack address -80
			struct TILE_1 *tile1; // $v1
		} // line 246, address 0x18318
	} // line 246, address 0x18318
} // line 263, address 0x18450
/*
 * Offset 0x18450
 * D:\driver2\game\C\OVERMAP.C (line 1645)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ DrawCopIndicators()
{ // line 2, address 0x18450
	static int ft[16]; // address 0x188
	struct _CAR_DATA *cp; // $s0
	int fade; // $s1
	int cc; // $s3
	int cs; // $s2
	{ // line 17, address 0x184e8
		int dx; // $a3
		int dz; // $a1
		int p; // $a1
		int q; // $a0
		int ap; // $v1
		{ // line 25, address 0x18578
		} // line 28, address 0x185d0
	} // line 29, address 0x185d0
} // line 31, address 0x18608
/*
 * Offset 0x18608
 * D:\driver2\game\C\OVERMAP.C (line 1697)
 * Stack frame base $sp, length 88
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawMultiplayerMap()
{ // line 2, address 0x18608
	struct POLY_FT4 *poly; // $a2
	struct LINE_F2 *line2; // $s1
	struct VECTOR target; // stack address -64
	int i; // $s3
	int y; // $s7
} // line 79, address 0x189e8
/*
 * Offset 0x189E8
 * D:\driver2\game\C\OVERMAP.C (line 2319)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ FlashOverheadMap(int r /*$a0*/, int g /*$a1*/, int b /*$a2*/)
{ // line 2, address 0x189e8
	struct TILE *tile; // $a3
} // line 22, address 0x18b08
/*
 * Offset 0x18B08
 * D:\driver2\game\C\OVERMAP.C (line 2350)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ LoadMapTile(int tpage /*$a0*/, int x /*$a1*/, int y /*$a2*/)
{ // line 1, address 0x18b08
	struct RECT MapSegment; // stack address -16
	int temp; // $a0
	int count; // $a2
	int idx; // $a3
} // line 33, address 0x18c5c
/*
 * Offset 0x18C5C
 * D:\driver2\game\C\OVERMAP.C (line 2405)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ draw_box()
{ // line 2, address 0x18c5c
	struct LINE_F4 *line4; // $s0
	struct LINE_F2 *line2; // $s1
} // line 22, address 0x18dbc
/*
 * Offset 0x18DBC
 * D:\driver2\game\C\OVERMAP.C (line 2435)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ DrawN(struct VECTOR *pScreenPosition /*$s2*/, int direct /*$s7*/)
{ // line 1, address 0x18dbc
	struct XYPAIR lastPoint; // stack address -48
	struct XYPAIR *pPoint; // $s0
	char loop; // $s4
	{ // line 11, address 0x18e2c
		struct LINE_F2 *pLine; // $a2
	} // line 34, address 0x18f2c
} // line 36, address 0x18f80
/*
 * Offset 0x18F80
 * D:\driver2\game\C\OVERMAP.C (line 2479)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawCompass()
{ // line 2, address 0x18f80
	struct VECTOR position[5]; // stack address -88
	struct XYPAIR *pNorth; // $a1
	int scale; // $a0
	{ // line 3, address 0x18f80
		char loop; // $t2
		struct VECTOR *pPosition; // $a3
		void *pot; // $s0
		{ // line 32, address 0x19120
			struct LINE_G2 *pLine; // $a0
		} // line 32, address 0x19120
	} // line 46, address 0x191fc
} // line 47, address 0x191fc
/*
 * Offset 0x191FC
 * D:\driver2\game\C\OVERMAP.C (line 2534)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ DrawBigCompass(struct VECTOR *root /*$a0*/, int angle /*$a1*/)
{ // line 1, address 0x191fc
	struct VECTOR position[5]; // stack address -96
	struct VECTOR *pPosition; // $s0
	char loop; // $s1
	{ // line 23, address 0x19368
		struct LINE_G2 *pLine; // $a1
	} // line 23, address 0x19368
} // line 35, address 0x1941c
/*
 * Offset 0x1941C
 * D:\driver2\game\C\OVERMAP.C (line 2577)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CopIndicator(int xpos /*$a3*/, int strength /*$a1*/)
{ // line 1, address 0x1941c
	struct POLY_F3 *tri; // $a2
	int str2; // $fp
	void *pot; // stack address -56
} // line 30, address 0x195fc
/*
 * Offset 0x195FC
 * D:\driver2\game\C\OVERMAP.C (line 2609)
 * Stack frame base $sp, length 184
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ DrawSightCone(struct COP_SIGHT_DATA *pCopSightData /*$a0*/, struct VECTOR *pPosition /*$a1*/, int direction /*$t6*/)
{ // line 1, address 0x195fc
	struct VECTOR vertex[9]; // stack address -160
	struct VECTOR *pVertex; // $t0
	int angle; // $a3
	int frontViewAngle; // $t1
	int negFrontViewAngle; // $a2
	int frontViewDistance; // $t4
	int surroundViewDistance; // $t3
	{ // line 15, address 0x19650
		int len; // $a1
		{ // line 27, address 0x19668
			int temp; // $v0
		} // line 27, address 0x19668
	} // line 27, address 0x19668
	{ // line 34, address 0x196d4
		struct VECTOR *pVertex; // $a2
		void *pot; // $a3
		{ // line 42, address 0x19720
			struct POLY_G3 *poly; // $a1
			struct VECTOR *pNextVertex; // $a0
		} // line 50, address 0x19744
	} // line 61, address 0x19824
} // line 62, address 0x19824
/*
 * Offset 0x19824
 * D:\driver2\game\C\OVERMAP.C (line 1043)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ InitOverheadMap()
{ // line 2, address 0x19824
	int tpage; // $s3
	int c; // $s2
	int d; // $s1
} // line 27, address 0x19924
/*
 * Offset 0x19948
 * D:\driver2\game\C\OVERMAP.C (line 1678)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ InitMultiplayerMap()
{ // line 2, address 0x19948
	struct RECT rect; // stack address -48
	char filename[32]; // stack address -40
} // line 17, address 0x199fc
/*
 * Offset 0x199FC
 * D:\driver2\game\C\OVERMAP.C (line 1778)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ WorldToMultiplayerMap(struct VECTOR *in /*$a3*/, struct VECTOR *out /*$a2*/)
{ // line 1, address 0x199fc
	int x; // $v1
	int z; // $a0
} // line 17, address 0x19ac8
/*
 * Offset 0x19AC8
 * D:\driver2\game\C\OVERMAP.C (line 2392)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetMapPos()
{
}
/*
 * Offset 0x19B58
 * D:\driver2\game\C\OVERMAP.C (line 2703)
 * Stack frame base $sp, length 96
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ WorldToOverheadMapPositions(struct VECTOR *pGlobalPosition /*$s1*/, struct VECTOR *pOverheadMapPosition /*$s3*/, int count /*$s2*/, char inputRelative /*$s5*/, int outputRelative /*stack 16*/)
{ // line 1, address 0x19b58
	struct MATRIX TempMatrix; // stack address -80
	int sin; // $a1
	int cos; // $a2
	int angle; // $v1
	int scale; // $s0
	{ // line 42, address 0x19c88
		struct SVECTOR tempVector; // stack address -48
		long flag; // stack address -40
	} // line 57, address 0x19d28
} // line 61, address 0x19d74
/*
 * Offset 0x19D74
 * D:\driver2\game\C\OVERMAP.C (line 2771)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetFullscreenMapMatrix()
{ // line 2, address 0x19d74
	struct VECTOR translate; // stack address -32
	struct SVECTOR direction; // stack address -16
} // line 16, address 0x19e50
/*
 * Offset 0x19E50
 * D:\driver2\game\C\OVERMAP.C (line 2794)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ WorldToFullscreenMap(struct VECTOR *in /*$a0*/, struct VECTOR *out /*$a1*/)
{
}
/*
 * Offset 0x19EE4
 * D:\driver2\game\C\OVERMAP.C (line 2806)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: ra
 */
void /*$ra*/ WorldToFullscreenMap2(struct VECTOR *in /*$a0*/, struct VECTOR *out /*$a1*/)
{ // line 1, address 0x19ee4
	struct SVECTOR pos; // stack address -24
	long flag; // stack address -16
} // line 13, address 0x19fac
/*
 * Offset 0x19FAC
 * D:\driver2\game\C\OVERMAP.C (line 1970)
 * Stack frame base $sp, length 696
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ ProcessPalletLump(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
{ // line 1, address 0x19fac
	int total_cluts; // $v0
	int clutValue; // $s1
	int tpageindex; // $s2
	int texnum; // $s3
	int palette; // $s4
	int clut_number; // $v1
	unsigned short clutTable[320]; // stack address -680
	char *buffPtr; // $s0
	{ // line 43, address 0x1a038
	} // line 43, address 0x1a038
} // line 64, address 0x1a0fc
/*
 * Offset 0x1A0FC
 * D:\driver2\game\C\OVERMAP.C (line 2043)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ load_civ_palettes(struct RECT *cluts /*$a0*/)
{
}