#include "THISDUST.H"
#include "OVERMAP.H"
#include "TEXTURE.H"
#include "CARS.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "MDRAW.H"
#include "PLAYERS.H"

#include "STRINGS.H"

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

char* MapBitMaps;
static char MapBuffer[520];
static unsigned short MapClut;
static RECT16 MapRect;

static int tilehnum = 0;
static char maptile[4][4];
static int old_x_mod = 0;
static int old_y_mod = 0;

static int x_map = 0;
static int y_map = 0;

static int map_x_offset = 0;
static int map_z_offset = 0;
static unsigned short MapTPage = 0;


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

void DrawTargetBlip(VECTOR *pos, unsigned char r, unsigned char g, unsigned char b, ulong flags)
{
	UNIMPLEMENTED();
	/*
	DB *pDVar1;
	ushort uVar2;
	short sVar3;
	uint *puVar4;
	long local_28;
	long local_24;
	int local_20;
	long local_1c;

	if ((flags & 0x20) == 0) {
		if ((flags & 8) == 0) {
			if ((flags & 1) == 0) {
				WorldToFullscreenMap2(pos, (VECTOR *)&local_28);
			}
			else {
				WorldToOverheadMapPositions(pos, (VECTOR *)&local_28, 1, '\0', 0);
				if (0x5e < local_28 - 0xe9U) {
					return;
				}
				if (local_20 < 0xae) {
					return;
				}
				if (0xfa < local_20) {
					return;
				}
			}
		}
		else {
			local_28 = pos->vx;
			local_24 = pos->vy;
			local_20 = pos->vz;
			local_1c = pos->pad;
		}
		if ((flags & 1) == 0) {
			local_28 = local_28 + map_x_offset;
			local_20 = local_20 + map_z_offset;
		}
	}
	else {
		WorldToMultiplayerMap(pos, (VECTOR *)&local_28);
		local_28 = local_28 + 0xf0;
		local_20 = local_20 + 0x60;
	}
	if ((flags & 0x10) == 0) {
		sVar3 = 4;
		if ((flags & 2) != 0) {
			sVar3 = 3;
		}
	}
	else {
		sVar3 = (short)((int)(uint)(byte)OverlayFlashValue >> 1);
	}
	puVar4 = (uint *)current->primptr;
	*(char *)((int)puVar4 + 3) = '\t';
	*(char *)((int)puVar4 + 7) = '.';
	*(short *)(puVar4 + 2) = (short)local_28 - sVar3;
	*(short *)((int)puVar4 + 10) = (short)local_20 - sVar3;
	*(short *)(puVar4 + 4) = (short)local_28 + sVar3;
	*(short *)((int)puVar4 + 0x12) = (short)local_20 - sVar3;
	*(short *)(puVar4 + 6) = (short)local_28 - sVar3;
	*(short *)((int)puVar4 + 0x1a) = (short)local_20 + sVar3;
	*(short *)(puVar4 + 8) = (short)local_28 + sVar3;
	*(uchar *)(puVar4 + 1) = r;
	*(uchar *)((int)puVar4 + 5) = g;
	*(uchar *)((int)puVar4 + 6) = b;
	*(short *)((int)puVar4 + 0x22) = (short)local_20 + sVar3;
	*(uchar *)(puVar4 + 3) = light_texture.coords.u0;
	*(uchar *)((int)puVar4 + 0xd) = light_texture.coords.v0;
	*(uchar *)(puVar4 + 5) = light_texture.coords.u1;
	*(uchar *)((int)puVar4 + 0x15) = light_texture.coords.v1;
	*(uchar *)(puVar4 + 7) = light_texture.coords.u2;
	*(uchar *)((int)puVar4 + 0x1d) = light_texture.coords.v2;
	*(uchar *)(puVar4 + 9) = light_texture.coords.u3;
	*(uchar *)((int)puVar4 + 0x25) = light_texture.coords.v3;
	if ((flags & 2) == 0) {
		uVar2 = light_texture.tpageid | 0x20;
	}
	else {
		uVar2 = light_texture.tpageid | 0x40;
	}
	*(ushort *)((int)puVar4 + 0x16) = uVar2;
	*(ushort *)((int)puVar4 + 0xe) = light_texture.clutid;
	pDVar1 = current;
	if ((flags & 4) == 0) {
		*puVar4 = *puVar4 & 0xff000000 | *current->ot & 0xffffff;
		*pDVar1->ot = *pDVar1->ot & 0xff000000 | (uint)puVar4 & 0xffffff;
		pDVar1->primptr = pDVar1->primptr + 0x28;
	}
	else {
		DrawPrim(puVar4);
	}
	return;*/
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

void DrawTargetArrow(VECTOR *pos, ulong flags)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	DB *pDVar3;
	int iVar4;
	int iVar5;
	uint *puVar6;
	int local_38;
	long local_34;
	int local_30;
	long local_2c;
	int local_28;
	int local_20;

	if ((flags & 8) == 0) {
		if ((flags & 1) == 0) {
			WorldToFullscreenMap2(pos, (VECTOR *)&local_38);
		}
		else {
			WorldToOverheadMapPositions(pos, (VECTOR *)&local_38, 1, '\0', 0);
		}
	}
	else {
		local_38 = pos->vx;
		local_34 = pos->vy;
		local_30 = pos->vz;
		local_2c = pos->pad;
	}
	if ((flags & 1) == 0) {
		local_38 = local_38 + map_x_offset;
		local_30 = local_30 + map_z_offset;
		local_28 = map_x_offset + 0xa0;
		local_20 = map_z_offset + 0x80;
	}
	else {
		WorldToOverheadMapPositions((VECTOR *)&player, (VECTOR *)&local_28, 1, '\0', 0);
	}
	iVar5 = local_28 - local_38;
	iVar4 = local_20 - local_30;
	ratan2(iVar4, iVar5);
	puVar6 = (uint *)current->primptr;
	*(char *)((int)puVar6 + 3) = '\x06';
	*(char *)((int)puVar6 + 7) = '2';
	*(char *)(puVar6 + 1) = '\x18';
	*(char *)((int)puVar6 + 5) = '\x18';
	*(char *)((int)puVar6 + 6) = '\x18';
	*(char *)(puVar6 + 3) = '\x18';
	*(char *)((int)puVar6 + 0xd) = '\x18';
	*(char *)((int)puVar6 + 0xe) = '\x18';
	*(char *)(puVar6 + 5) = '@';
	*(char *)((int)puVar6 + 0x15) = '@';
	*(char *)((int)puVar6 + 0x16) = '@';
	sVar1 = (short)(iVar4 >> 3);
	*(short *)(puVar6 + 2) = (short)local_28 + sVar1;
	sVar2 = (short)(iVar5 >> 3);
	*(short *)((int)puVar6 + 10) = (short)local_20 - sVar2;
	*(short *)(puVar6 + 4) = (short)local_28 - sVar1;
	*(short *)((int)puVar6 + 0x12) = (short)local_20 + sVar2;
	*(undefined2 *)(puVar6 + 6) = (undefined2)local_38;
	*(undefined2 *)((int)puVar6 + 0x1a) = (undefined2)local_30;
	*(char *)((int)puVar6 + 0x1f) = '\a';
	*(char *)((int)puVar6 + 0x23) = '$';
	*(undefined2 *)(puVar6 + 9) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x26) = 0xffff;
	*(undefined2 *)(puVar6 + 0xb) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x2e) = 0xffff;
	*(undefined2 *)(puVar6 + 0xd) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x36) = 0xffff;
	*(undefined2 *)((int)puVar6 + 0x32) = 0x40;
	pDVar3 = current;
	if ((flags & 4) == 0) {
		*puVar6 = *puVar6 & 0xff000000 | *current->ot & 0xffffff;
		*pDVar3->ot = *pDVar3->ot & 0xff000000 | (uint)puVar6 & 0xffffff;
		puVar6[7] = puVar6[7] & 0xff000000 | *pDVar3->ot & 0xffffff;
		*pDVar3->ot = *pDVar3->ot & 0xff000000 | (uint)(puVar6 + 7) & 0xffffff;
		pDVar3->primptr = pDVar3->primptr + 0x3c;
	}
	else {
		DrawPrim(puVar6 + 7);
		DrawPrim(puVar6);
	}
	return;*/
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

void DrawPlayerDot(VECTOR *pos, short rot, unsigned char r, unsigned char g, int b, ulong flags)
{
	UNIMPLEMENTED();
	/*
	DB *pDVar1;
	int iVar2;
	int iVar3;
	uint *puVar4;
	short local_60;
	short local_58;
	short local_50;
	short local_48;
	short local_40;
	short local_38;
	VECTOR local_30;

	if ((flags & 0x20) == 0) {
		if ((flags & 8) == 0) {
			if ((flags & 1) == 0) {
				WorldToFullscreenMap2(pos, &local_30);
			}
			else {
				WorldToOverheadMapPositions(pos, &local_30, 1, '\0', 0);
				if (0x5e < local_30.vx - 0xe9U) {
					return;
				}
				if (local_30.vz < 0xae) {
					return;
				}
				if (0xfa < local_30.vz) {
					return;
				}
			}
		}
		else {
			local_30.vx = pos->vx;
			local_30.vy = pos->vy;
			local_30.vz = pos->vz;
			local_30.pad = pos->pad;
		}
		if ((flags & 1) == 0) {
			local_30.vx = local_30.vx + map_x_offset;
			local_30.vz = local_30.vz + map_z_offset;
		}
	}
	else {
		WorldToMultiplayerMap(pos, &local_30);
		local_30.vx = local_30.vx + 0xf0;
		local_30.vz = local_30.vz + 0x60;
	}
	iVar2 = (int)rcossin_tbl[((int)rot & 0xfffU) * 2];
	iVar3 = (int)rcossin_tbl[((int)rot & 0xfffU) * 2 + 1];
	local_40 = (short)local_30.vx;
	local_60 = local_40 + (short)(iVar2 * -3 + 0x800 >> 0xc);
	local_38 = (short)local_30.vz;
	local_58 = local_38 + (short)(iVar3 * -3 + 0x800 >> 0xc);
	local_50 = local_40 + (short)(iVar2 * 3 + iVar3 * -2 + 0x800 >> 0xc);
	local_48 = local_38 + (short)(iVar3 * 3 + iVar2 * 2 + 0x800 >> 0xc);
	local_40 = local_40 + (short)(iVar3 * 2 + iVar2 * 3 + 0x800 >> 0xc);
	local_38 = local_38 + (short)(iVar2 * -2 + iVar3 * 3 + 0x800 >> 0xc);
	puVar4 = (uint *)current->primptr;
	*(char *)((int)puVar4 + 3) = '\x04';
	*(char *)((int)puVar4 + 7) = ' ';
	*(uchar *)(puVar4 + 1) = r;
	*(uchar *)((int)puVar4 + 5) = g;
	*(char *)((int)puVar4 + 6) = (char)b;
	*(short *)(puVar4 + 2) = local_60;
	*(short *)((int)puVar4 + 10) = local_58;
	*(short *)(puVar4 + 3) = local_50;
	*(short *)((int)puVar4 + 0xe) = local_48;
	*(short *)(puVar4 + 4) = local_40;
	*(short *)((int)puVar4 + 0x12) = local_38;
	pDVar1 = current;
	if ((flags & 4) == 0) {
		*puVar4 = *puVar4 & 0xff000000 | *current->ot & 0xffffff;
		*pDVar1->ot = *pDVar1->ot & 0xff000000 | (uint)puVar4 & 0xffffff;
		pDVar1->primptr = pDVar1->primptr + 0x14;
	}
	else {
		DrawPrim(puVar4);
	}
	return;
	*/
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
	TEXTURE_DETAILS local_20;

	GetTextureDetails("OVERHEAD", &local_20);

	MapTPage = local_20.tpageid;
	MapClut = GetClut(mapclutpos.x, mapclutpos.y);

	uVar1 = 0;
	pSVar2 = MapSegmentPos;

	MapRect.w = 0x40;
	MapRect.h = 0x100;
	MapRect.x = (MapTPage & 0xf) << 6;
	MapRect.y = (MapTPage & 0x10) << 4;

	do {
		pSVar2->x = (((uVar1 & 3) * 32 + local_20.coords.u0) >> 2);
		pSVar2->y = local_20.coords.v0 + (uVar1 >> 2) * 32;

		uVar1++;
		pSVar2++;
	} while (uVar1 < 16);

	MapBitMaps = mallocptr;
	memcpy(mallocptr, lump_ptr, lump_size);
	mallocptr = mallocptr + lump_size;

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

ulong Long2DDistance(VECTOR *pPoint1, VECTOR *pPoint2)
{
	UNIMPLEMENTED();
	return 0;
	/*
	short sVar1;
	uint uVar2;
	int iVar3;
	int iVar4;
	ulong uVar5;

	iVar4 = pPoint1->vx - pPoint2->vx;
	if (iVar4 < 0) {
		iVar4 = pPoint2->vx - pPoint1->vx;
	}
	iVar3 = pPoint1->vz - pPoint2->vz;
	if (iVar3 < 0) {
		iVar3 = pPoint2->vz - pPoint1->vz;
	}
	uVar2 = ratan2();
	if ((uVar2 & 0x7ff) - 0x200 < 0x401) {
		sVar1 = rcossin_tbl[(uVar2 & 0xfff) * 2];
		iVar4 = iVar3;
	}
	else {
		sVar1 = rcossin_tbl[(uVar2 & 0xfff) * 2 + 1];
	}
	iVar3 = (int)sVar1;
	if (iVar4 < 0x80000) {
		uVar5 = (iVar4 << 0xc) / iVar3;
		if (iVar3 == 0) {
			trap(7);
		}
	}
	else {
		if (iVar3 == 0) {
			trap(7);
		}
		uVar5 = (iVar4 << 9) / iVar3 << 3;
	}
	return uVar5;*/
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

		if (tilehnum < 0) 
			tilehnum = tilehnum + 0x1f;

		tilehnum = tilehnum >> 5;

		iVar3 = 0;
		do {
			iVar2 = 0;
			iVar5 = iVar3 + 1;
			pcVar1 = maptile[iVar3];
			tpage = iVar4;

			do {
				*pcVar1 = (char)tpage;
				iVar4 = tpage + 1;
				pcVar1 = pcVar1 + 4;

				LoadMapTile(tpage, (x_map >> 5) + iVar2, (y_map >> 5) + iVar3);

				iVar2 = iVar2 + 1;
				tpage = iVar4;
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

void DrawOverheadMap(void)
{
	if (gMultiplayerLevels != 0)
	{
		DrawMultiplayerMap();
		return;
	}

	UNIMPLEMENTED();
	/*
	    byte bVar1;
    short sVar2;
    short sVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    ushort uVar7;
    ushort uVar8;
    DB *pDVar9;
    uchar uVar10;
    short *psVar11;
    TILE_1 *local_a0_864;
    POLY_F4 *local_a0_3412;
    int x;
    short *psVar12;
    int y;
    int y_00;
    short *psVar13;
    undefined2 *puVar14;
    POLY_F4 *local_a3_2816;
    POLY_FT4 *local_a3_3552;
    SVECTOR *pSVar15;
    long *plVar16;
    SVECTOR *pSVar17;
    long *plVar18;
    SVECTOR *pSVar19;
    char cVar20;
    SVECTOR *pSVar21;
    char cVar22;
    SVECTOR *v0;
    _CAR_DATA *p_Var23;
    char *pcVar24;
    byte *pbVar25;
    VECTOR *v1;
    DR_AREA *local_s2_676;
    int r;
    uint *puVar26;
    int iVar27;
    uint uVar28;
    int iVar29;
    uint uVar30;
    SVECTOR MapMesh [5] [5];
    VECTOR MapMeshO [5] [5];
    MAPTEX MapTex [4];
    SVECTOR direction;
    RECT clipped_size;
    VECTOR translate;
    VECTOR vec;
    long flag;
    
    uVar6 = DAT_00010408;
    uVar5 = DAT_00010404;
    uVar4 = DAT_00010400;
    if (gMultiplayerLevels != 0) {
        DrawMultiplayerMap();
        return;
    }
    if (1 < NumPlayers) {
        return;
    }
    SetMapPos();
    uVar28 = x_map & 0x1f;
    uVar30 = y_map & 0x1f;
    draw_box();
    if (0 < player_position_known) {
        if ((int)player[0].playerCarId < 0) {
            psVar11 = &pedestrianFelony;
        }
        else {
            psVar11 = &car_data[(int)player[0].playerCarId].felonyRating;
        }
        if (0x292 < *psVar11) {
            FlashOverheadMap(INT_ARRAY_0009baac[CameraCnt & 0xf],0,
                             INT_ARRAY_0009baac[CameraCnt + 8U & 0xf]);
            goto LAB_00016fac;
        }
    }
    if (player_position_known == -1) {
        if (flashtimer == 0) {
            if ((int)player[0].playerCarId < 0) {
                psVar11 = &pedestrianFelony;
            }
            else {
                psVar11 = &car_data[(int)player[0].playerCarId].felonyRating;
            }
            if (0x292 < *psVar11) {
                flashtimer = 0x30;
            }
            goto LAB_00016ee8;
        }
    }
    else {
LAB_00016ee8:
        if (flashtimer == 0) goto LAB_00016fac;
    }
    flashtimer = flashtimer + -1;
    r = -flashtimer;
    x = r + 0x2f;
    if (x < 0) {
        x = r + 0x32;
    }
    y = r + 0x30;
    if (y < 0) {
        y = r + 0x33;
    }
    y_00 = r + 0x31;
    if (y_00 < 0) {
        y_00 = r + 0x34;
    }
    iVar27 = r + 0x32;
    if (iVar27 < 0) {
        iVar27 = r + 0x35;
    }
    r = INT_ARRAY_0009baec[x >> 2] + INT_ARRAY_0009baec[y >> 2] + INT_ARRAY_0009baec[y_00 >> 2] +
        INT_ARRAY_0009baec[iVar27 >> 2];
    if (r < 0) {
        r = r + 3;
    }
    r = r >> 2;
    FlashOverheadMap(r,r,r);
LAB_00016fac:
    local_s2_676 = (DR_AREA *)current->primptr;
    SetDrawArea(local_s2_676,&current->draw);
    pDVar9 = current;
    local_s2_676->tag = local_s2_676->tag & 0xff000000 | *current->ot & 0xffffff;
    *pDVar9->ot = *pDVar9->ot & 0xff000000 | (uint)local_s2_676 & 0xffffff;
    pDVar9->primptr = pDVar9->primptr + 0xc;
    WorldToOverheadMapPositions((VECTOR *)player,&vec,1,'\0',0);
    if (((vec.vx - 0xe9U < 0x5f) && (0xad < vec.vz)) && (vec.vz < 0xfb)) {
        local_a0_864 = (TILE_1 *)current->primptr;
        *(undefined *)((int)&local_a0_864->tag + 3) = 2;
        local_a0_864->code = 'h';
        local_a0_864->r0 = -1;
        local_a0_864->g0 = -1;
        local_a0_864->b0 = -1;
        pDVar9 = current;
        local_a0_864->x0 = (short)vec.vx;
        local_a0_864->y0 = (short)vec.vz;
        local_a0_864->tag = local_a0_864->tag & 0xff000000 | *pDVar9->ot & 0xffffff;
        *pDVar9->ot = *pDVar9->ot & 0xff000000 | (uint)local_a0_864 & 0xffffff;
        pDVar9->primptr = pDVar9->primptr + 0xc;
    }
    DrawTargetBlip((VECTOR *)player,'@','@','@',3);
    DrawCompass();
    DrawOverheadTargets();
    p_Var23 = car_data;
    v0 = MapMesh + 5;
    sVar2 = -(short)uVar28;
    pSVar15 = MapMesh + 10;
    pSVar17 = MapMesh + 0xf;
    pSVar19 = MapMesh + 0x14;
    sVar3 = -(short)uVar30;
    if (true) {
        do {
            if (((p_Var23->controlType == '\x03') && (p_Var23->ai[0x13] == 0)) ||
               ((p_Var23->controlFlags & 1) != 0)) {
                DrawSightCone(&copSightData,(VECTOR *)(p_Var23->hd).where.t,(p_Var23->hd).direction)
                ;
            }
            p_Var23 = p_Var23 + 1;
        } while (p_Var23 < (_CAR_DATA *)0xd4698);
    }
    if ((uVar28 < 0x10) && (0x10 < old_x_mod)) {
        r = 0;
        pcVar24 = maptile;
        pbVar25 = (byte *)(maptile + 8);
        do {
            bVar1 = *pcVar24;
            x = x_map >> 5;
            y = y_map >> 5;
            *pcVar24 = pbVar25[-4];
            y = y + r;
            pbVar25[-4] = *pbVar25;
            r = r + 1;
            *pbVar25 = ((byte *)pcVar24)[0xc];
            ((byte *)pcVar24)[0xc] = bVar1;
            LoadMapTile((uint)bVar1,x + 3,y);
            pcVar24 = (char *)((byte *)pcVar24 + 1);
            pbVar25 = pbVar25 + 1;
        } while (r < 4);
    }
    if ((0x10 < uVar28) && (old_x_mod < 0x10)) {
        r = 0;
        pcVar24 = maptile;
        pbVar25 = (byte *)(maptile + 0xc);
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
            LoadMapTile((uint)bVar1,y,y_00);
            pcVar24 = (char *)((byte *)pcVar24 + 1);
        } while (r < 4);
    }
    if ((uVar30 < 0x10) && (0x10 < old_y_mod)) {
        r = 0;
        pcVar24 = maptile;
        pbVar25 = (byte *)(maptile + 1);
        do {
            y_00 = r * 4;
            bVar1 = *pcVar24;
            x = (x_map >> 5) + r;
            y = y_map >> 5;
            *pcVar24 = *pbVar25;
            r = r + 1;
            *pbVar25 = maptile[y_00 + 2];
            pbVar25 = pbVar25 + 4;
            maptile[y_00 + 2] = ((byte *)pcVar24)[3];
            ((byte *)pcVar24)[3] = bVar1;
            LoadMapTile((uint)bVar1,x,y + 3);
            pcVar24 = (char *)((byte *)pcVar24 + 4);
        } while (r < 4);
    }
    if ((0x10 < uVar30) && (old_y_mod < 0x10)) {
        r = 0;
        pcVar24 = maptile;
        pbVar25 = (byte *)(maptile + 3);
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
            LoadMapTile((uint)bVar1,x,y);
            pcVar24 = (char *)((byte *)pcVar24 + 4);
        } while (r < 4);
    }
    r = 3;
    if (uVar28 != 0) {
        r = 4;
    }
    x = 3;
    if (uVar30 != 0) {
        x = 4;
    }
    y_00 = 0;
    y = 0;
    pSVar21 = MapMesh;
    old_x_mod = uVar28;
    old_y_mod = uVar30;
    do {
        psVar12 = (short *)((int)&MapMesh[2].vz + y);
        psVar11 = (short *)((int)&MapMesh[1].vz + y);
        psVar13 = (short *)((int)&MapMesh[3].vz + y);
        y_00 = y_00 + 1;
        pSVar21->vx = -0x23;
        v0->vx = sVar2 + -0x10;
        v0 = v0 + 1;
        pSVar21 = pSVar21 + 1;
        pSVar15->vx = sVar2 + 0x10;
        pSVar17->vx = sVar2 + 0x30;
        pSVar19->vx = 0x23;
        pSVar19 = pSVar19 + 1;
        pSVar17 = pSVar17 + 1;
        pSVar15 = pSVar15 + 1;
        *(undefined2 *)((int)&MapMesh[0].vz + y) = 0xffdd;
        puVar14 = (undefined2 *)((int)&MapMesh[4].vz + y);
        y = y + 0x28;
        *psVar11 = sVar3 + -0x10;
        *psVar12 = sVar3 + 0x10;
        *psVar13 = sVar3 + 0x30;
        *puVar14 = 0x23;
    } while (y_00 < 5);
    MapTex[0].u = MapMesh[0][0].vx - MapMesh[1][0].vx;
    if ((int)MapMesh[0][0].vx - (int)MapMesh[1][0].vx < 0) {
        MapTex[0].u = MapMesh[1][0].vx - MapMesh[0][0].vx;
    }
    MapTex[0].u = 0x20 - MapTex[0].u;
    MapTex[0].w = MapMesh[0][0].vx - MapMesh[1][0].vx;
    if ((int)MapMesh[0][0].vx - (int)MapMesh[1][0].vx < 0) {
        MapTex[0].w = MapMesh[1][0].vx - MapMesh[0][0].vx;
    }
    MapTex[1].w = ZEXT12((byte)tile_size);
    MapTex[1].u = 0;
    MapTex[2].u = 0;
    MapTex[3].u = 0;
    MapTex[2].w = ZEXT12((byte)tile_size);
    if ((int)MapMesh[3][0].vx - (int)MapMesh[4][0].vx < 0) {
        MapTex[3].w = MapMesh[4][0].vx - MapMesh[3][0].vx;
    }
    else {
        MapTex[3].w = MapMesh[3][0].vx - MapMesh[4][0].vx;
    }
    if ((int)MapMesh[0][0].vz - (int)MapMesh[0][1].vz < 0) {
        MapTex[0].v = MapMesh[0][1].vz - MapMesh[0][0].vz;
    }
    else {
        MapTex[0].v = MapMesh[0][0].vz - MapMesh[0][1].vz;
    }
    MapTex[0].v = 0x20 - MapTex[0].v;
    MapTex[0].h = MapMesh[0][0].vz - MapMesh[0][1].vz;
    if ((int)MapMesh[0][0].vz - (int)MapMesh[0][1].vz < 0) {
        MapTex[0].h = MapMesh[0][1].vz - MapMesh[0][0].vz;
    }
    MapTex[1].h = ZEXT12((byte)tile_size);
    MapTex[1].v = 0;
    MapTex[2].v = 0;
    MapTex[3].v = 0;
    MapTex[2].h = ZEXT12((byte)tile_size);
    if ((int)MapMesh[0][3].vz - (int)MapMesh[0][4].vz < 0) {
        MapTex[3].h = MapMesh[0][4].vz - MapMesh[0][3].vz;
    }
    else {
        MapTex[3].h = MapMesh[0][3].vz - MapMesh[0][4].vz;
    }
    direction.vx = 0;
    direction.vz = 0;
    direction.vy = (ushort)player[0].dir & 0xfff;
    RotMatrixXYZ(&map_matrix,&direction);
    MulMatrix0(&aspect,&map_matrix,&map_matrix);
    setCopControlWord(2,0,map_matrix.m[0]._0_4_);
    setCopControlWord(2,0x800,map_matrix.m._4_4_);
    setCopControlWord(2,0x1000,map_matrix.m[1]._2_4_);
    setCopControlWord(2,0x1800,map_matrix.m[2]._0_4_);
    setCopControlWord(2,0x2000,map_matrix._16_4_);
    setCopControlWord(2,0x2800,uVar4);
    setCopControlWord(2,0x3000,uVar5);
    setCopControlWord(2,0x3800,uVar6);
    y = 0;
    if (true) {
        do {
            y_00 = y + 1;
            if (true) {
                v1 = MapMeshO + y * 5;
                iVar27 = x + 1;
                v0 = MapMesh + y * 5;
                do {
                    RotTrans(v0,v1,&flag);
                    v1 = v1 + 1;
                    iVar27 = iVar27 + -1;
                    v0 = v0 + 1;
                } while (iVar27 != 0);
            }
            y = y_00;
        } while (y_00 <= r);
    }
    y = 0;
    if (x != 0) {
        do {
            y_00 = 0;
            iVar27 = y + 1;
            if (r != 0) {
                pbVar25 = (byte *)(maptile + y);
                iVar29 = 0;
                plVar18 = &MapMeshO[5].vz + iVar27 * 4;
                plVar16 = &MapMeshO[5].vz + y * 4;
                psVar11 = &MapTex[0].w;
                do {
                    if (((&MapSegmentPos)[*pbVar25].x & 0x18U) == 0x18) {
                        cVar22 = (char)*psVar11 + -1;
                    }
                    else {
                        cVar22 = (char)*psVar11;
                    }
                    if (((&MapSegmentPos)[*pbVar25].y & 0x60U) == 0x60) {
                        cVar20 = (char)MapTex[y].h + -1;
                    }
                    else {
                        cVar20 = (char)MapTex[y].h;
                    }
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
                         *pcVar24 + *(char *)&(&MapSegmentPos)[*pbVar25].x * '\x04';
                    *(char *)((int)&local_a3_2816->x1 + 1) =
                         *(char *)psVar12 + *(char *)&(&MapSegmentPos)[*pbVar25].y;
                    *(char *)&local_a3_2816->x3 =
                         *pcVar24 + *(char *)&(&MapSegmentPos)[*pbVar25].x * '\x04' + cVar22;
                    *(char *)((int)&local_a3_2816->x3 + 1) =
                         *(char *)psVar12 + *(char *)&(&MapSegmentPos)[*pbVar25].y;
                    iVar29 = iVar29 + 8;
                    local_a3_2816[1].r0 = *pcVar24 + *(char *)&(&MapSegmentPos)[*pbVar25].x * '\x04'
                    ;
                    psVar11 = psVar11 + 4;
                    local_a3_2816[1].g0 =
                         *(char *)psVar12 + *(char *)&(&MapSegmentPos)[*pbVar25].y + cVar20;
                    y_00 = y_00 + 1;
                    *(char *)&local_a3_2816[1].x1 =
                         *pcVar24 + *(char *)&(&MapSegmentPos)[*pbVar25].x * '\x04' + cVar22;
                    plVar16 = plVar16 + 0x14;
                    *(char *)((int)&local_a3_2816[1].x1 + 1) =
                         *(char *)psVar12 + *(char *)&(&MapSegmentPos)[*pbVar25].y + cVar20;
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
    }
    local_a0_3412 = (POLY_F4 *)current->primptr;
    *(undefined *)((int)&local_a0_3412->tag + 3) = 5;
    local_a0_3412->r0 = '<';
    local_a0_3412->g0 = '<';
    local_a0_3412->b0 = '<';
    local_a0_3412->code = '*';
    pDVar9 = current;
    local_a0_3412->y0 = 0xb6;
    local_a0_3412->y1 = 0xb6;
    local_a0_3412->x0 = 0xf5;
    local_a0_3412->x1 = 0x13b;
    local_a0_3412->x2 = 0xf5;
    local_a0_3412->y2 = 0xf2;
    local_a0_3412->x3 = 0x13b;
    local_a0_3412->y3 = 0xf2;
    local_a0_3412->tag = local_a0_3412->tag & 0xff000000 | *pDVar9->ot & 0xffffff;
    *pDVar9->ot = *pDVar9->ot & 0xff000000 | (uint)local_a0_3412 & 0xffffff;
    local_a3_3552 = (POLY_FT4 *)pDVar9->primptr;
    *(POLY_FT4 **)&pDVar9->primptr = local_a3_3552 + 1;
    *(undefined *)((int)&local_a3_3552[1].tag + 3) = 7;
    local_a3_3552[1].code = '$';
    local_a3_3552[1].x0 = -1;
    local_a3_3552[1].y0 = -1;
    local_a3_3552[1].x1 = -1;
    local_a3_3552[1].y1 = -1;
    local_a3_3552[1].x2 = -1;
    local_a3_3552[1].y2 = -1;
    local_a3_3552[1].tpage = 0;
    pDVar9 = current;
    local_a3_3552[1].tag = local_a3_3552[1].tag & 0xff000000 | *current->ot & 0xffffff;
    *pDVar9->ot = *pDVar9->ot & 0xff000000 | (uint)(local_a3_3552 + 1) & 0xffffff;
    pDVar9->primptr = pDVar9->primptr + 0x20;
    clipped_size.x = 0xfa;
    clipped_size.w = 0x3c;
    clipped_size.h = 0x3c;
    clipped_size.y = (pDVar9->draw).clip.y + 0xb6;
    puVar26 = (uint *)pDVar9->primptr;
    SetDrawArea(puVar26,&clipped_size);
    pDVar9 = current;
    *puVar26 = *puVar26 & 0xff000000 | *current->ot & 0xffffff;
    *pDVar9->ot = *pDVar9->ot & 0xff000000 | (uint)puVar26 & 0xffffff;
    pDVar9->primptr = pDVar9->primptr + 0xc;*/
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
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	short sVar2;
	char *pcVar3;
	int iVar4;
	int iVar5;
	uint uVar6;
	uint *puVar7;
	uint *puVar8;
	short *psVar9;
	int y;
	int iVar10;
	int x;
	short local_c0;
	undefined2 local_be;
	short local_bc;
	short local_b8;
	undefined2 local_b6;
	short local_b4;
	short local_b0;
	undefined2 local_ae;
	short local_ac;
	short local_a8;
	undefined2 local_a6;
	short local_a4;
	uint local_a0[2];
	uint local_98[2];
	undefined2 local_90;
	undefined2 local_88;
	undefined2 local_80;
	undefined2 local_78;
	undefined2 local_70;
	undefined2 local_68;
	VECTOR local_60;
	int local_50;
	long local_4c;
	int local_48;
	long local_44;
	undefined auStack64[4];
	int local_3c;
	int local_38;
	int local_34;
	VECTOR *local_30;

	if ((Pads[0].dirnew & 0x20) != 0) {
		map_x_offset = 0;
		map_z_offset = 0;
		map_x_shift = 0;
		map_z_shift = 0;
		gUseRotatedMap = gUseRotatedMap ^ 1;
	}
	SetFullscreenMapMatrix();
	pcVar3 = current->primptr;
	pcVar3[3] = '\x03';
	pcVar3[7] = '`';
	pcVar3[4] = '\0';
	pcVar3[5] = '\0';
	pcVar3[6] = '\0';
	*(undefined2 *)(pcVar3 + 8) = 0;
	*(undefined2 *)(pcVar3 + 10) = 0;
	*(undefined2 *)(pcVar3 + 0xc) = 0x140;
	*(undefined2 *)(pcVar3 + 0xe) = 0x100;
	DrawPrim(pcVar3);
	DrawSync(0);
	local_3c = overlaidmaps[GameLevel].width;
	local_38 = overlaidmaps[GameLevel].height;
	WorldToFullscreenMap((VECTOR *)&player, &player_position);
	if (gUseRotatedMap != 0) {
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
	map_x_offset = (player_position.vx + 0xa0) - local_3c;
	if ((player_position.vx + 0xa0 <= local_3c) &&
		(map_x_offset = player_position.vx + -0xa0, -1 < map_x_offset)) {
		map_x_offset = 0;
	}
	map_z_offset = (player_position.vz + 0x80) - local_38;
	if ((player_position.vz + 0x80 <= local_38) &&
		(map_z_offset = player_position.vz + -0x80, -1 < map_z_offset)) {
		map_z_offset = 0;
	}
	if ((Pads[0].direct & 0x8000) == 0) {
		if (((Pads[0].direct & 0x2000) != 0) &&
			(iVar5 = map_x_shift + -8,
			((player_position.vx - map_x_offset) + 0xa0) - map_x_shift < local_3c)) goto LAB_00017f0c;
	}
	else {
		iVar5 = map_x_shift + 8;
		if (0 < ((player_position.vx - map_x_offset) + -0xa0) - map_x_shift) {
		LAB_00017f0c:
			map_x_shift = iVar5;
		}
	}
	if ((Pads[0].direct & 0x1000) == 0) {
		if (((Pads[0].direct & 0x4000) != 0) &&
			(iVar5 = map_z_shift + -8,
			((player_position.vz - map_z_offset) + 0x80) - map_z_shift < local_38)) goto LAB_00017f64;
	}
	else {
		iVar5 = map_z_shift + 8;
		if (0 < ((player_position.vz - map_z_offset) + -0x80) - map_z_shift) {
		LAB_00017f64:
			map_z_shift = iVar5;
		}
	}
	map_x_offset = map_x_offset + map_x_shift;
	map_z_offset = map_z_offset + map_z_shift;
LAB_00017f8c:
	pcVar3 = current->primptr;
	pcVar3[3] = '\a';
	pcVar3[7] = '$';
	uVar1 = MapTPage;
	*(undefined2 *)(pcVar3 + 8) = 0xffff;
	*(undefined2 *)(pcVar3 + 10) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x10) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x12) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x18) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x1a) = 0xffff;
	*(ushort *)(pcVar3 + 0x16) = uVar1;
	DrawPrim(pcVar3);
	DrawSync(0);
	local_30 = &local_60;
	iVar5 = 0;
	while (true) {
		x = iVar5;
		iVar5 = local_3c;
		if (local_3c < 0) {
			iVar5 = local_3c + 0x1f;
		}
		if (iVar5 >> 5 <= x) break;
		local_34 = x + 1;
		iVar5 = 0;
		while (true) {
			y = iVar5;
			iVar4 = local_38;
			if (local_38 < 0) {
				iVar4 = local_38 + 0x1f;
			}
			iVar10 = 0;
			iVar5 = local_34;
			if (iVar4 >> 5 <= y) break;
			puVar8 = (uint *)local_98;
			puVar7 = (uint *)local_a0;
			psVar9 = &local_c0;
			iVar5 = 3;
			local_be = 0;
			local_b6 = 0;
			local_ae = 0;
			local_a6 = 0;
			local_c0 = (short)x * 0x20 - (short)player_position.vx;
			local_b8 = local_c0 + 0x20;
			local_bc = (short)y * 0x20 - (short)player_position.vz;
			local_ac = local_bc + 0x20;
			local_b4 = local_bc;
			local_b0 = local_c0;
			local_a8 = local_b8;
			local_a4 = local_ac;
			do {
				RotTrans(psVar9, puVar7, auStack64);
				*puVar7 = *puVar7 + map_x_offset;
				uVar6 = *puVar8;
				*puVar8 = uVar6 + map_z_offset;
				if ((0x140 < *puVar7) || (0x100 < uVar6 + map_z_offset)) {
					iVar10 = iVar10 + 1;
				}
				puVar8 = puVar8 + 4;
				puVar7 = puVar7 + 4;
				iVar5 = iVar5 + -1;
				psVar9 = psVar9 + 4;
			} while (-1 < iVar5);
			iVar5 = y + 1;
			if (iVar10 != 4) {
				LoadMapTile(0, x, y);
				pcVar3 = current->primptr;
				pcVar3[3] = '\t';
				pcVar3[4] = 'X';
				pcVar3[5] = 'X';
				pcVar3[6] = 'X';
				pcVar3[7] = ',';
				*(undefined2 *)(pcVar3 + 8) = (undefined2)local_a0[0];
				*(undefined2 *)(pcVar3 + 10) = (undefined2)local_98[0];
				*(undefined2 *)(pcVar3 + 0x10) = local_90;
				*(undefined2 *)(pcVar3 + 0x12) = local_88;
				*(undefined2 *)(pcVar3 + 0x18) = local_80;
				*(undefined2 *)(pcVar3 + 0x1a) = local_78;
				*(undefined2 *)(pcVar3 + 0x20) = local_70;
				*(undefined2 *)(pcVar3 + 0x22) = local_68;
				pcVar3[0xc] = (char)MapSegmentPos.x << 2;
				pcVar3[0xd] = (char)MapSegmentPos.y;
				pcVar3[0x14] = (char)MapSegmentPos.x * '\x04' + '\x1f';
				pcVar3[0x15] = (char)MapSegmentPos.y;
				pcVar3[0x1c] = (char)MapSegmentPos.x << 2;
				pcVar3[0x1d] = (char)MapSegmentPos.y + '\x1f';
				pcVar3[0x24] = (char)MapSegmentPos.x * '\x04' + '\x1f';
				pcVar3[0x25] = (char)MapSegmentPos.y + '\x1f';
				*(ushort *)(pcVar3 + 0xe) = MapClut;
				DrawPrim(pcVar3);
				DrawSync(0);
			}
		}
	}
	local_60.vx = 0xa0;
	local_60.vz = 0x80;
	DrawFullscreenTargets();
	if (gUseRotatedMap == 0) {
		DrawBigCompass(local_30, 0);
	}
	else {
		DrawBigCompass(local_30, player.dir);
	}
	DrawTargetBlip(local_30, '@', '@', '@', 0xe);
	local_44 = local_60.pad;
	local_50 = local_60.vx + map_x_offset;
	local_4c = local_60.vy;
	local_48 = local_60.vz + map_z_offset;
	pcVar3 = current->primptr;
	pcVar3[3] = '\x02';
	pcVar3[7] = 'h';
	pcVar3[4] = -1;
	pcVar3[5] = -1;
	pcVar3[6] = -1;
	*(undefined2 *)(pcVar3 + 8) = (undefined2)local_50;
	*(undefined2 *)(pcVar3 + 10) = (undefined2)local_48;
	DrawPrim(pcVar3);
	pcVar3 = current->primptr;
	pcVar3[3] = '\a';
	pcVar3[7] = '$';
	sVar2 = fonttpage;
	*(undefined2 *)(pcVar3 + 8) = 0xffff;
	*(undefined2 *)(pcVar3 + 10) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x10) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x12) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x18) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x1a) = 0xffff;
	*(short *)(pcVar3 + 0x16) = sVar2;
	DrawPrim(pcVar3);
	DrawSync(0);
	SetTextColour(-0x80, -0x80, -0x80);
	PrintStringCentred(&DAT_00010410, 0xe2);
	return;*/
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

void DrawCopIndicators(void)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	_CAR_DATA *p_Var7;

	p_Var7 = car_data;
	sVar1 = rcossin_tbl[(player.dir & 0xfffU) * 2 + 1];
	sVar2 = rcossin_tbl[(player.dir & 0xfffU) * 2];
	do {
		if ((p_Var7->controlType == '\x03') && (p_Var7->ai[0x13] == 0)) {
			iVar6 = (p_Var7->hd).where.t[0] - player.pos[0];
			iVar4 = (p_Var7->hd).where.t[2] - player.pos[2];
			iVar5 = ((iVar6 * sVar1 - iVar4 * sVar2) + 0x800 >> 0xc) * 3;
			if (iVar5 < 0) {
				iVar5 = iVar5 + 3;
			}
			iVar5 = iVar5 >> 2;
			iVar3 = iVar6 * sVar2 + iVar4 * sVar1 + 0x800 >> 0xc;
			iVar4 = -iVar3;
			iVar6 = iVar5;
			if (iVar5 < 0) {
				iVar6 = -iVar5;
			}
			if (iVar6 < iVar4) {
				iVar5 = (iVar5 * 0x10a) / iVar4;
				if (iVar4 == 0) {
					trap(7);
				}
				if (0 < iVar3) {
					iVar4 = iVar4 + 7;
				}
				iVar4 = (iVar4 >> 3) + 600;
				if (iVar4 == 0) {
					trap(7);
				}
				CopIndicator(iVar5 + 0xa0, 0x3fff0 / iVar4);
			}
		}
		p_Var7 = p_Var7 + 1;
	} while (p_Var7 < (_CAR_DATA *)0xd4698);
	return;*/
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
	DB *pDVar3;
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
	VECTOR local_40;
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
				local_40.vx = pPVar6->pos[0];
				local_40.vz = pPVar6->pos[2];
				iVar7 ++;
				local_40.vy = 0;

				WorldToMultiplayerMap(&local_40, &local_40);

				local_40.vx = local_40.vx + 0xf0;
				local_40.vz = local_40.vz + yPos;

				DrawPlayerDot(&local_40, -*(short *)&pPVar6->dir, r, g, 0, 8);

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

void WorldToMultiplayerMap(VECTOR *in, VECTOR *out)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	int iVar3;

	iVar1 = MissionHeader->region;
	if (iVar1 != 0) {
		iVar3 = iVar1 / regions_across;
		if (regions_across == 0) {
			trap(7);
		}
		if (regions_across == 0) {
			trap(7);
		}
		iVar2 = in->vx - ((iVar1 % regions_across) * 0x10000 + cells_across * -0x400);
		iVar1 = cells_down * -0x400;
		if (iVar2 < 0) {
			iVar2 = iVar2 + 0x7ff;
		}
		out->vx = iVar2 >> 0xb;
		iVar1 = in->vz - ((iVar3 + -1) * 0x10000 + iVar1);
		if (iVar1 < 0) {
			iVar1 = iVar1 + 0x7ff;
		}
		out->vz = 0x40 - (iVar1 >> 0xb);
		return;
	}
	out->vx = 0x20;
	out->vz = 0x20;
	return;
	*/
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

void FlashOverheadMap(int r, int g, int b)
{
	UNIMPLEMENTED();
	/*
	DB *pDVar1;
	uint *puVar2;
	char *pcVar3;

	puVar2 = (uint *)current->primptr;
	*(char *)((int)puVar2 + 3) = '\x03';
	*(char *)(puVar2 + 1) = (char)r;
	*(char *)((int)puVar2 + 5) = (char)g;
	*(char *)((int)puVar2 + 6) = (char)b;
	*(char *)((int)puVar2 + 7) = 'b';
	pDVar1 = current;
	*(undefined2 *)(puVar2 + 2) = 0xfa;
	*(undefined2 *)((int)puVar2 + 10) = 0xb6;
	*(undefined2 *)(puVar2 + 3) = 0x3c;
	*(undefined2 *)((int)puVar2 + 0xe) = 0x3c;
	*puVar2 = *puVar2 & 0xff000000 | *pDVar1->ot & 0xffffff;
	*pDVar1->ot = *pDVar1->ot & 0xff000000 | (uint)puVar2 & 0xffffff;
	pcVar3 = pDVar1->primptr;
	pDVar1->primptr = pcVar3 + 0x10;
	pcVar3[0x13] = '\a';
	pcVar3[0x17] = '$';
	pDVar1 = current;
	*(undefined2 *)(pcVar3 + 0x18) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x1a) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x20) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x22) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x28) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x2a) = 0xffff;
	*(undefined2 *)(pcVar3 + 0x26) = 0x20;
	*(uint *)(pcVar3 + 0x10) = *(uint *)(pcVar3 + 0x10) & 0xff000000 | *pDVar1->ot & 0xffffff;
	*pDVar1->ot = *pDVar1->ot & 0xff000000 | (uint)(pcVar3 + 0x10) & 0xffffff;
	pDVar1->primptr = pDVar1->primptr + 0x20;
	return;
	*/
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

void SetMapPos(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	iVar1 = overlaidmaps[GameLevel].scale;
	if (iVar1 == 0) {
		trap(7);
	}
	if (iVar1 == 0) {
		trap(7);
	}
	x_map = overlaidmaps[GameLevel].x_offset + player.pos[0] / iVar1;
	y_map = overlaidmaps[GameLevel].y_offset - player.pos[2] / iVar1;
	return;*/
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

void draw_box(void)
{
	UNIMPLEMENTED();
	/*
	DB *pDVar1;
	ulong *puVar2;
	uint *puVar3;

	puVar3 = (uint *)current->primptr;
	SetLineF4(puVar3);
	*(char *)(puVar3 + 1) = '\0';
	*(char *)((int)puVar3 + 5) = '\0';
	*(char *)((int)puVar3 + 6) = -0x80;
	pDVar1 = current;
	*(undefined2 *)(puVar3 + 2) = 0xf9;
	*(undefined2 *)((int)puVar3 + 10) = 0xb5;
	*(undefined2 *)(puVar3 + 3) = 0x136;
	*(undefined2 *)((int)puVar3 + 0xe) = 0xb5;
	*(undefined2 *)(puVar3 + 4) = 0x136;
	*(undefined2 *)((int)puVar3 + 0x12) = 0xf2;
	*(undefined2 *)(puVar3 + 5) = 0xf9;
	*(undefined2 *)((int)puVar3 + 0x16) = 0xf2;
	*puVar3 = *puVar3 & 0xff000000 | pDVar1->ot[1] & 0xffffff;
	puVar2 = pDVar1->ot;
	puVar2[1] = puVar2[1] & 0xff000000 | (uint)puVar3 & 0xffffff;
	SetLineF2(puVar3 + 7);
	*(char *)(puVar3 + 8) = '\0';
	*(char *)((int)puVar3 + 0x21) = '\0';
	*(char *)((int)puVar3 + 0x22) = -0x80;
	pDVar1 = current;
	*(undefined2 *)(puVar3 + 9) = 0xf9;
	*(undefined2 *)((int)puVar3 + 0x26) = 0xb5;
	*(undefined2 *)(puVar3 + 10) = 0xf9;
	*(undefined2 *)((int)puVar3 + 0x2a) = 0xf2;
	puVar3[7] = puVar3[7] & 0xff000000 | pDVar1->ot[1] & 0xffffff;
	pDVar1->ot[1] = pDVar1->ot[1] & 0xff000000 | (uint)(puVar3 + 7) & 0xffffff;
	pDVar1->primptr = pDVar1->primptr + 0x2c;
	return;
	*/
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

void DrawN(VECTOR *pScreenPosition, int direct)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	DB *pDVar2;
	byte bVar3;
	uint *puVar4;
	XYPAIR *pXVar5;
	int local_30;
	int local_2c;

	pXVar5 = &XYPAIR_0009ba3c;
	bVar3 = 0;
	local_30 = NVertex.x + pScreenPosition->vx;
	local_2c = NVertex.y + pScreenPosition->vz;
	do {
		puVar4 = (uint *)current->primptr;
		*(char *)((int)puVar4 + 3) = '\x03';
		*(char *)((int)puVar4 + 7) = '@';
		*(undefined2 *)(puVar4 + 2) = (undefined2)local_30;
		*(undefined2 *)((int)puVar4 + 10) = (undefined2)local_2c;
		local_30 = pXVar5->x + pScreenPosition->vx;
		local_2c = pXVar5->y + pScreenPosition->vz;
		*(undefined2 *)(puVar4 + 3) = (undefined2)local_30;
		iVar1 = gTimeOfDay;
		*(undefined2 *)((int)puVar4 + 0xe) = (undefined2)local_2c;
		if (iVar1 == 3) {
			*(char *)(puVar4 + 1) = 'K';
			*(char *)((int)puVar4 + 5) = 'K';
			*(char *)((int)puVar4 + 6) = 'K';
		}
		else {
			*(char *)(puVar4 + 1) = '`';
			*(char *)((int)puVar4 + 5) = '`';
			*(char *)((int)puVar4 + 6) = '`';
		}
		*(byte *)((int)puVar4 + 7) = *(byte *)((int)puVar4 + 7) | 2;
		pDVar2 = current;
		if (direct == 0) {
			*puVar4 = *puVar4 & 0xff000000 | *current->ot & 0xffffff;
			*pDVar2->ot = *pDVar2->ot & 0xff000000 | (uint)puVar4 & 0xffffff;
		}
		else {
			DrawPrim(puVar4);
		}
		bVar3 = bVar3 + 1;
		pXVar5 = pXVar5 + 1;
		current->primptr = current->primptr + 0x10;
	} while (bVar3 < 3);
	return;
	*/
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

void DrawCompass(void)
{
	UNIMPLEMENTED();
	/*
	undefined2 uVar1;
	DB *pDVar2;
	byte bVar3;
	uint *puVar4;
	int *piVar5;
	ulong *potz;
	VECTOR local_58;
	int local_48;
	int local_40;
	int local_38[2];
	int local_30;
	VECTOR local_28;
	int local_18;
	int local_10;

	local_48 = north[GameLevel].x * overlaidmaps[GameLevel].scale;
	local_40 = north[GameLevel].y * overlaidmaps[GameLevel].scale;
	local_58.vx = local_48 * 0x14 + 8 >> 4;
	local_38[0] = local_48 + 2 >> 2;
	local_58.vz = local_40 * 0x14 + 8 >> 4;
	local_30 = local_40 + 2 >> 2;
	local_28.vx = (local_40 - local_48) * 0xab >> 10;
	local_28.vz = (-local_48 - local_40) * 0xab >> 10;
	local_10 = -local_28.vx;
	local_18 = local_28.vz;
	WorldToOverheadMapPositions(&local_58, &local_58, 3, '\x01', 0);
	WorldToOverheadMapPositions(&local_28, &local_28, 2, '\x01', 1);
	piVar5 = local_38;
	bVar3 = 0;
	local_28.vx = local_28.vx + local_48;
	local_28.vz = local_28.vz + local_40;
	local_18 = local_18 + local_48;
	local_10 = local_10 + local_40;
	potz = current->ot;
	do {
		puVar4 = (uint *)current->primptr;
		*(char *)((int)puVar4 + 3) = '\x04';
		*(char *)((int)puVar4 + 7) = 'P';
		*(undefined2 *)(puVar4 + 2) = (undefined2)local_48;
		*(undefined2 *)((int)puVar4 + 10) = (undefined2)local_40;
		*(undefined2 *)(puVar4 + 4) = *(undefined2 *)piVar5;
		uVar1 = *(undefined2 *)(piVar5 + 2);
		piVar5 = piVar5 + 4;
		*(char *)(puVar4 + 1) = '`';
		*(char *)((int)puVar4 + 5) = '`';
		*(char *)((int)puVar4 + 6) = '`';
		*(char *)(puVar4 + 3) = '\0';
		*(char *)((int)puVar4 + 0xd) = '\0';
		*(char *)((int)puVar4 + 0xe) = '\0';
		*(char *)((int)puVar4 + 7) = 'R';
		*(undefined2 *)((int)puVar4 + 0x12) = uVar1;
		pDVar2 = current;
		bVar3 = bVar3 + 1;
		*puVar4 = *puVar4 & 0xff000000 | *potz & 0xffffff;
		*potz = *potz & 0xff000000 | (uint)puVar4 & 0xffffff;
		pDVar2->primptr = pDVar2->primptr + 0x14;
	} while (bVar3 < 3);
	DrawN(&local_58, 0);
	TransparencyOn(potz, 0x20);
	return;*/
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

void DrawBigCompass(VECTOR *root, int angle)
{
	UNIMPLEMENTED();
	/*
	undefined2 uVar1;
	byte bVar2;
	uint uVar3;
	char *pcVar4;
	uint uVar5;
	uint uVar6;
	int *piVar7;
	VECTOR local_60;
	int local_50;
	int local_4c;
	int local_40;
	int local_3c;
	int local_30;
	int local_2c;
	int local_20;
	int local_1c;

	piVar7 = &local_40;
	bVar2 = 0;
	local_40 = root->vx + map_x_offset;
	uVar5 = big_north[GameLevel] + angle & 0xfff;
	local_3c = root->vz + map_z_offset;
	local_50 = local_40 + ((int)rcossin_tbl[uVar5 * 2] * 0x19 >> 0xc);
	local_60.vx = local_40 + ((int)rcossin_tbl[uVar5 * 2] * 0xf >> 0xb);
	uVar3 = uVar5 - 200 & 0xfff;
	uVar6 = uVar5 + 200 & 0xfff;
	local_4c = local_3c + ((int)rcossin_tbl[uVar5 * 2 + 1] * 0x19 >> 0xc);
	local_60.vz = local_3c + ((int)rcossin_tbl[uVar5 * 2 + 1] * 0xf >> 0xb);
	local_30 = local_40 + ((int)rcossin_tbl[uVar3 * 2] * 5 >> 10);
	local_2c = local_3c + ((int)rcossin_tbl[uVar3 * 2 + 1] * 5 >> 10);
	local_20 = local_40 + ((int)rcossin_tbl[uVar6 * 2] * 5 >> 10);
	local_1c = local_3c + ((int)rcossin_tbl[uVar6 * 2 + 1] * 5 >> 10);
	do {
		pcVar4 = current->primptr;
		pcVar4[3] = '\x04';
		pcVar4[7] = 'P';
		*(undefined2 *)(pcVar4 + 8) = (undefined2)local_50;
		*(undefined2 *)(pcVar4 + 10) = (undefined2)local_4c;
		*(undefined2 *)(pcVar4 + 0x10) = *(undefined2 *)piVar7;
		uVar1 = *(undefined2 *)(piVar7 + 1);
		piVar7 = piVar7 + 4;
		pcVar4[4] = '`';
		pcVar4[5] = '`';
		pcVar4[6] = '`';
		pcVar4[0xc] = '\0';
		pcVar4[0xd] = '\0';
		pcVar4[0xe] = '\0';
		pcVar4[7] = 'R';
		*(undefined2 *)(pcVar4 + 0x12) = uVar1;
		DrawPrim(pcVar4);
		bVar2 = bVar2 + 1;
		current->primptr = current->primptr + 0x14;
	} while (bVar2 < 3);
	DrawN(&local_60, 1);
	return;*/
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

void CopIndicator(int xpos, int strength)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	DB *pDVar2;
	char cVar3;
	uint *puVar4;
	ulong *puVar5;
	int iVar6;

	puVar5 = current->ot;
	if (0xff < strength) {
		strength = 0xff;
	}
	iVar6 = strength * (strength + 0x100);
	puVar4 = (uint *)current->primptr;
	*(char *)((int)puVar4 + 3) = '\x04';
	*(char *)((int)puVar4 + 7) = ' ';
	*(char *)(puVar4 + 1) = (char)strength;
	if (strength < 0) {
		strength = strength + 3;
	}
	cVar3 = (char)(strength >> 2);
	*(char *)((int)puVar4 + 5) = cVar3;
	sVar1 = (short)xpos;
	*(char *)((int)puVar4 + 6) = cVar3;
	*(short *)(puVar4 + 2) = sVar1 + -0xc;
	*(undefined2 *)((int)puVar4 + 10) = 0x100;
	*(short *)(puVar4 + 3) = sVar1;
	*(undefined2 *)((int)puVar4 + 0xe) = 0xe2;
	*(short *)(puVar4 + 4) = sVar1 + 0xc;
	*(undefined2 *)((int)puVar4 + 0x12) = 0x100;
	*(char *)((int)puVar4 + 7) = '\"';
	*puVar4 = *puVar4 & 0xff000000 | puVar5[1] & 0xffffff;
	pDVar2 = current;
	puVar5[1] = puVar5[1] & 0xff000000 | (uint)puVar4 & 0xffffff;
	pDVar2->primptr = pDVar2->primptr + 0x14;
	TransparencyOn(puVar5 + 1, 0x20);
	puVar4 = (uint *)current->primptr;
	*(char *)((int)puVar4 + 3) = '\x04';
	cVar3 = (char)(iVar6 >> 9);
	*(char *)(puVar4 + 1) = cVar3;
	*(char *)((int)puVar4 + 5) = cVar3;
	*(char *)((int)puVar4 + 6) = cVar3;
	*(short *)(puVar4 + 2) = sVar1 + -0xc;
	*(undefined2 *)((int)puVar4 + 10) = 0x100;
	*(undefined2 *)((int)puVar4 + 0xe) = 0xe2;
	*(short *)(puVar4 + 4) = sVar1 + 0xc;
	*(undefined2 *)((int)puVar4 + 0x12) = 0x100;
	*(char *)((int)puVar4 + 7) = '\"';
	*(short *)(puVar4 + 3) = sVar1;
	*puVar4 = *puVar4 & 0xff000000 | puVar5[1] & 0xffffff;
	pDVar2 = current;
	puVar5[1] = puVar5[1] & 0xff000000 | (uint)puVar4 & 0xffffff;
	pDVar2->primptr = pDVar2->primptr + 0x14;
	TransparencyOn(puVar5 + 1, 0x40);
	return;*/
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

void DrawSightCone(COP_SIGHT_DATA *pCopSightData, VECTOR *pPosition, int direction)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	short sVar5;
	undefined2 uVar6;
	DB *pDVar7;
	uint uVar8;
	int *piVar9;
	int *piVar10;
	uint *puVar11;
	int iVar12;
	ulong *potz;
	int *piVar13;
	int local_a0;
	int local_98;
	int local_90[2];
	int local_88[26];
	int aiStack32[4];

	iVar12 = 0;
	sVar1 = pCopSightData->frontViewDistance;
	sVar2 = pCopSightData->surroundViewDistance;
	sVar3 = pCopSightData->frontViewAngle;
	local_a0 = pPosition->vx;
	local_98 = pPosition->vz;
	piVar13 = local_90;
	do {
		if ((iVar12 <= (int)sVar3) || (sVar4 = sVar2, 0x1000 - (int)sVar3 <= iVar12)) {
			sVar4 = sVar1;
		}
		uVar8 = iVar12 + direction & 0xfff;
		sVar5 = rcossin_tbl[uVar8 * 2 + 1];
		iVar12 = iVar12 + 0x200;
		*piVar13 = local_a0 + ((int)rcossin_tbl[uVar8 * 2] * (int)sVar4 + 0x800 >> 0xc);
		piVar13[2] = local_98 + ((int)sVar5 * (int)sVar4 + 0x800 >> 0xc);
		piVar13 = piVar13 + 4;
	} while (iVar12 < 0x1000);
	WorldToOverheadMapPositions((VECTOR *)&local_a0, (VECTOR *)&local_a0, 9, '\0', 0);
	potz = current->ot;
	piVar13 = local_90;
	while (piVar13 < &stack0xfffffff0) {
		piVar9 = piVar13 + 4;
		puVar11 = (uint *)current->primptr;
		piVar10 = piVar9;
		if (aiStack32 < piVar9) {
			piVar10 = local_90;
		}
		*(char *)((int)puVar11 + 3) = '\x06';
		*(char *)((int)puVar11 + 7) = '0';
		*(undefined2 *)(puVar11 + 2) = (undefined2)local_a0;
		*(undefined2 *)((int)puVar11 + 10) = (undefined2)local_98;
		*(undefined2 *)(puVar11 + 4) = *(undefined2 *)piVar13;
		*(undefined2 *)((int)puVar11 + 0x12) = *(undefined2 *)(piVar13 + 2);
		*(undefined2 *)(puVar11 + 6) = *(undefined2 *)piVar10;
		uVar6 = *(undefined2 *)(piVar10 + 2);
		*(char *)(puVar11 + 1) = '`';
		*(char *)((int)puVar11 + 5) = '`';
		*(char *)((int)puVar11 + 6) = '`';
		*(char *)(puVar11 + 3) = '\0';
		*(char *)((int)puVar11 + 0xd) = '\0';
		*(char *)((int)puVar11 + 0xe) = '\0';
		*(char *)(puVar11 + 5) = '\0';
		*(char *)((int)puVar11 + 0x15) = '\0';
		*(char *)((int)puVar11 + 0x16) = '\0';
		*(char *)((int)puVar11 + 7) = '2';
		*(undefined2 *)((int)puVar11 + 0x1a) = uVar6;
		*puVar11 = *puVar11 & 0xff000000 | *potz & 0xffffff;
		pDVar7 = current;
		*potz = *potz & 0xff000000 | (uint)puVar11 & 0xffffff;
		pDVar7->primptr = pDVar7->primptr + 0x1c;
		piVar13 = piVar9;
	}
	TransparencyOn(potz, 0x20);
	return;*/
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

void WorldToOverheadMapPositions(VECTOR *pGlobalPosition, VECTOR *pOverheadMapPosition, int count, char inputRelative,int outputRelative)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	uint local_50;
	uint local_4c;
	uint local_44;
	uint local_40;
	undefined4 local_3c;
	undefined4 local_34;
	undefined2 local_30;
	undefined2 local_2e;
	undefined2 local_2c;
	undefined auStack40[8];

	local_4c = (uint)(ushort)rcossin_tbl[(player.dir & 0xfffU) * 2];
	local_50 = (uint)(ushort)rcossin_tbl[(player.dir & 0xfffU) * 2 + 1];
	local_44 = (uint)(ushort)-rcossin_tbl[(player.dir & 0xfffU) * 2];
	local_40 = local_40 & 0xffff0000 | (uint)(ushort)rcossin_tbl[(player.dir & 0xfffU) * 2 + 1];
	if ((char)outputRelative == '\0') {
		local_3c = 0x118;
		local_34 = 0xd4;
	}
	else {
		local_3c = 0;
		local_34 = 0;
	}
	setCopControlWord(2, 0, local_50);
	setCopControlWord(2, 0x800, local_4c);
	setCopControlWord(2, 0x1000, 0x1000);
	setCopControlWord(2, 0x1800, local_44);
	setCopControlWord(2, 0x2000, local_40);
	setCopControlWord(2, 0x2800, local_3c);
	setCopControlWord(2, 0x3000, 0);
	setCopControlWord(2, 0x3800, local_34);
	count = count + -1;
	iVar1 = overlaidmaps[GameLevel].scale;
	while (count != -1) {
		local_2e = 0;
		if (inputRelative == '\0') {
			if (iVar1 == 0) {
				trap(7);
			}
			local_30 = (undefined2)((pGlobalPosition->vx - player.pos[0]) / iVar1);
			if (iVar1 == 0) {
				trap(7);
			}
			local_2c = (undefined2)((player.pos[2] - pGlobalPosition->vz) / iVar1);
		}
		else {
			if (iVar1 == 0) {
				trap(7);
			}
			local_30 = (undefined2)(pGlobalPosition->vx / iVar1);
			if (iVar1 == 0) {
				trap(7);
			}
			local_2c = (undefined2)(-pGlobalPosition->vz / iVar1);
		}
		RotTrans(&local_30, pOverheadMapPosition, auStack40);
		count = count + -1;
		pGlobalPosition = pGlobalPosition + 1;
		pOverheadMapPosition = pOverheadMapPosition + 1;
	}
	return;*/
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

void SetFullscreenMapMatrix(void)
{
	UNIMPLEMENTED();
	/*
	undefined4 uVar1;
	undefined4 uVar2;
	undefined4 uVar3;
	SVECTOR local_10;

	uVar3 = DAT_00010440;
	uVar2 = DAT_0001043c;
	uVar1 = DAT_00010438;
	local_10.vx = 0;
	if (gUseRotatedMap == 0) {
		local_10.vy = 0;
	}
	else {
		local_10.vy = (ushort)player.dir & 0xfff;
	}
	local_10.vz = 0;
	RotMatrixXYZ(&map_matrix, &local_10);
	MulMatrix0(&aspect, &map_matrix, &map_matrix);
	setCopControlWord(2, 0, map_matrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, map_matrix.m._4_4_);
	setCopControlWord(2, 0x1000, map_matrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, map_matrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, map_matrix._16_4_);
	setCopControlWord(2, 0x2800, uVar1);
	setCopControlWord(2, 0x3000, uVar2);
	setCopControlWord(2, 0x3800, uVar3);
	return;
	*/
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

void WorldToFullscreenMap(VECTOR *in, VECTOR *out)
{
	UNIMPLEMENTED();
	/*
	OVERMAP *pOVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;

	iVar2 = GameLevel;
	iVar5 = in->vx;
	pOVar1 = overlaidmaps + GameLevel;
	iVar3 = pOVar1->scale;
	if (iVar3 == 0) {
		trap(7);
	}
	iVar4 = overlaidmaps[GameLevel].x_offset;
	out->vy = 0;
	out->vx = iVar4 + iVar5 / iVar3 + 0x31;
	iVar3 = pOVar1->scale;
	if (iVar3 == 0) {
		trap(7);
	}
	out->vz = overlaidmaps[iVar2].y_offset - (in->vz / iVar3 + -0x31);
	return;*/
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

void WorldToFullscreenMap2(VECTOR *in, VECTOR *out)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	short local_18;
	undefined2 local_16;
	short local_14;
	undefined auStack16[8];

	iVar1 = overlaidmaps[GameLevel].scale;
	if (iVar1 == 0) {
		trap(7);
	}
	local_16 = 0;
	if (iVar1 == 0) {
		trap(7);
	}
	local_18 = (*(short *)&overlaidmaps[GameLevel].x_offset + (short)(in->vx / iVar1) + 0x31) -
		(short)player_position.vx;
	local_14 = (*(short *)&overlaidmaps[GameLevel].y_offset - ((short)(in->vz / iVar1) + -0x31)) -
		(short)player_position.vz;
	RotTrans(&local_18, out, auStack16);
	return;*/
}





