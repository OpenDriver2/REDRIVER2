#include "../decomp_defs.h"

MATRIX aspect =
{ { { 6553, 0, 0 }, { 0, 4096, 0 }, { 0, 0, 4096 } }, { 0, 0, 0 } };


/*
 * Offset 0x3EDE4
 * D:\driver2\game\C\DRAW.C (line 651)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ addSubdivSpriteShadow(struct POLYFT4LIT *src /*$t3*/, struct SVECTOR *verts /*$t2*/, int z /*$a2*/)
{ // line 1, address 0x3ede4
	unsigned long word0; // $a0
	unsigned long vidx; // $t1
	struct _pct *pc; // $t0
	int w; // $s0
} // line 19, address 0x3efcc
/*
 * Offset 0x3EFCC
 * D:\driver2\game\C\DRAW.C (line 675)
 * Stack frame base $sp, length 96
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawSprites(int numFound /*$a2*/)
{ // line 1, address 0x3efcc
	struct XZPAIR near; // stack address -80
	struct PACKED_CELL_OBJECT **list; // stack address -64
	unsigned long spriteColour; // stack address -60
	int numShadows; // stack address -56
	{ // line 1, address 0x3efcc
		struct SVECTOR result; // stack address -72
		unsigned char lightLevel; // $a1
	} // line 41, address 0x3f164
	{ // line 41, address 0x3f164
		int i; // $t0
	} // line 54, address 0x3f1dc
	{ // line 68, address 0x3f258
		struct PACKED_CELL_OBJECT *ppco; // $fp
		struct MODEL *model; // $s4
		int z; // stack address -52
		int yang; // $a0
		{ // line 95, address 0x3f310
		} // line 95, address 0x3f310
		{ // line 101, address 0x3f358
			struct POLYFT4LIT *src; // $s0
			struct SVECTOR *verts; // $s3
			int i; // $s1
			{ // line 106, address 0x3f3a0
				unsigned long vidx; // $a3
			} // line 107, address 0x3f3a0
		} // line 119, address 0x3f504
	} // line 132, address 0x3f604
} // line 134, address 0x3f658
/*
 * Offset 0x3F658
 * D:\driver2\game\C\DRAW.C (line 813)
 * Stack frame base $sp, length 0
 */
struct PACKED_CELL_OBJECT * /*$ra*/ GetNextPackedCop(struct CELL_ITERATOR *pci /*$a0*/)
{ // line 1, address 0x3f658
	struct PACKED_CELL_OBJECT *ppco; // $a3
	unsigned short num; // $a1
} // line 40, address 0x3f718
/*
 * Offset 0x3F718
 * D:\driver2\game\C\DRAW.C (line 883)
 * Stack frame base $sp, length 200
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawMapPSX(int *comp_val /*$t1*/)
{ // line 1, address 0x3f718
	struct CELL_ITERATOR ci; // stack address -184
	struct PACKED_CELL_OBJECT *ppco; // $s0
	int i; // $s1
	int dir; // $s7
	int cellxpos; // $a0
	int cellzpos; // $a1
	int hloop; // $s4
	int vloop; // $s5
	int camx; // stack address -112
	int camz; // stack address -108
	char *PVS_ptr; // stack address -104
	int tiles_found; // stack address -100
	int other_models_found; // stack address -96
	int anim_objs; // $s6
	struct MATRIX mRotStore; // stack address -160
	int rightcos; // stack address -92
	int rightsin; // stack address -88
	int leftcos; // stack address -84
	int leftsin; // stack address -80
	int backcos; // stack address -76
	int backsin; // stack address -72
	int rightPlane; // stack address -68
	int leftPlane; // stack address -64
	int backPlane; // $fp
	unsigned int farClipLimit; // stack address -60
	{ // line 84, address 0x3f9cc
		struct MODEL *model; // $s2
		{ // line 92, address 0x3fa1c
			int model_shape_flags; // $s1
			{ // line 103, address 0x3fa78
				struct CELL_OBJECT *cop; // $a2
				{ // line 1, address 0x3fa78
					struct PACKED_CELL_OBJECT *ppco; // $s0
					{ // line 1, address 0x3fa78
						struct CELL_OBJECT *pco; // $a1
					} // line 1, address 0x3fb20
				} // line 1, address 0x3fb20
			} // line 105, address 0x3fb2c
			{ // line 110, address 0x3fb5c
				struct CELL_OBJECT *cop; // $a2
				{ // line 1, address 0x3fb5c
					struct PACKED_CELL_OBJECT *ppco; // $s0
					{ // line 1, address 0x3fb5c
						struct CELL_OBJECT *pco; // $a1
					} // line 1, address 0x3fc04
				} // line 1, address 0x3fc04
			} // line 111, address 0x3fc04
			{ // line 119, address 0x3fc50
				int yang; // $a1
			} // line 127, address 0x3fd38
			{ // line 135, address 0x3fd74
				struct CELL_OBJECT *cop; // $a2
				{ // line 1, address 0x3fd74
					struct PACKED_CELL_OBJECT *ppco; // $s0
					{ // line 1, address 0x3fd74
						struct CELL_OBJECT *pco; // $a1
					} // line 1, address 0x3fe1c
				} // line 1, address 0x3fe1c
			} // line 138, address 0x3fe68
			{ // line 149, address 0x3fe9c
				struct CELL_OBJECT *cop; // $a2
				{ // line 1, address 0x3fe9c
					struct PACKED_CELL_OBJECT *ppco; // $s0
					{ // line 1, address 0x3fe9c
						struct CELL_OBJECT *pco; // $a1
					} // line 1, address 0x3ff44
				} // line 1, address 0x3ff44
			} // line 159, address 0x3ff9c
		} // line 162, address 0x3ff9c
	} // line 163, address 0x3ff9c
	{ // line 188, address 0x40134
	} // line 189, address 0x4013c
	{ // line 198, address 0x4014c
	} // line 200, address 0x40174
	{ // line 206, address 0x401a0
		struct VECTOR newpos; // stack address -128
		struct CELL_OBJECT *cop; // $s0
	} // line 207, address 0x401a0
} // line 240, address 0x40280
/*
 * Offset 0x40280
 * D:\driver2\game\C\DRAW.C (line 1125)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupPlaneColours(unsigned long ambient /*$a3*/)
{ // line 1, address 0x40280
	{ // line 15, address 0x4031c
		unsigned long r; // $t4
		unsigned long g; // $t2
		unsigned long b; // $a0
	} // line 15, address 0x4031c
} // line 34, address 0x40470
/*
 * Offset 0x40470
 * D:\driver2\game\C\DRAW.C (line 1162)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SetupDrawMapPSX()
{ // line 3, address 0x40470
	{ // line 4, address 0x404d0
		int region_x1; // $t0
		int region_z1; // $a0
		int current_barrel_region_x1; // $v0
		int current_barrel_region_z1; // $a0
	} // line 16, address 0x404f4
	{ // line 16, address 0x404f4
		int theta; // $s2
	} // line 34, address 0x40568
} // line 38, address 0x4059c
/*
 * Offset 0x4059C
 * D:\driver2\game\C\DRAW.C (line 1209)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ InitFrustrumMatrix()
{
}
/*
 * Offset 0x40670
 * D:\driver2\game\C\DRAW.C (line 1425)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ProcessMapLump(char *lump_ptr /*$v0*/, int lump_size /*$a1*/)
{ // line 1, address 0x40670
	char *cellptr; // $s0
	int cell_size; // $a3
	int region_size; // $t0
} // line 53, address 0x40840
/*
 * Offset 0x40840
 * D:\driver2\game\C\DRAW.C (line 1711)
 * Stack frame base $sp, length 128
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ DrawAllTheCars(int view /*$s6*/)
{ // line 1, address 0x40840
	int loop; // $s0
	int x; // $s2
	int z; // $s1
	int xd; // $a0
	int zd; // $v1
	struct _CAR_DATA *cars_to_draw[20]; // stack address -112
	int num_cars_to_draw; // $s4
	static int car_distance[20]; // address 0x0
	static int temp; // address 0x0
	{ // line 1, address 0x40840
		struct _CAR_DATA *lcp; // $s0
		{ // line 27, address 0x408c8
			int dist; // $v0
		} // line 37, address 0x40948
	} // line 40, address 0x40958
	{ // line 46, address 0x40960
		int i; // $a0
		{ // line 51, address 0x40988
			struct _CAR_DATA *car; // $t4
			int dist; // $t0
			int j; // $a3
		} // line 60, address 0x40a08
	} // line 63, address 0x40a28
	{ // line 79, address 0x40a4c
		int spacefree; // $a1
	} // line 87, address 0x40a94
} // line 113, address 0x40ad0
/*
 * Offset 0x40AF8
 * D:\driver2\game\C\DRAW.C (line 1857)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ PlotBuildingModelSubdivNxN(struct MODEL *model /*$t0*/, int rot /*stack 4*/, struct _pct *pc /*$s2*/, int n /*stack 12*/)
{ // line 1, address 0x40af8
	struct SVECTOR *verts; // $s4
	struct PL_POLYFT4 *polys; // $s1
	int i; // $s7
	int asdf; // $fp
	{ // line 19, address 0x40ba8
		unsigned long word0; // $s0
		{ // line 29, address 0x40c04
			int Z; // stack address -48
			unsigned int vidx; // $s3
			{ // line 39, address 0x40c38
				unsigned long th; // $v1
			} // line 45, address 0x40c78
			{ // line 83, address 0x40e98
				int diff; // $a1
				int min; // $a2
				{ // line 88, address 0x40e98
					int max; // $v1
				} // line 92, address 0x40f0c
				{ // line 113, address 0x40f78
					int w; // $s0
				} // line 116, address 0x40fa4
				{ // line 126, address 0x410c8
					struct POLY_FT4 *prims; // $t2
					int uv0; // $v1
					int uv1; // $a2
					int uv2; // $t3
					int uv3; // $t1
					{ // line 137, address 0x41110
						unsigned int r; // $a2
					} // line 137, address 0x41110
					{ // line 137, address 0x41110
						int r2; // $v1
					} // line 137, address 0x41110
				} // line 162, address 0x411a8
			} // line 164, address 0x411a8
		} // line 169, address 0x411c0
	} // line 176, address 0x411e0
} // line 183, address 0x4125c
/*
 * Offset 0x4125C
 * D:\driver2\game\C\DRAW.C (line 2053)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ DrawAllBuildings(unsigned long *objects /*$t3*/, int num_buildings /*$s5*/, struct DB *disp /*$a2*/)
{ // line 1, address 0x4125c
	int i; // $s3
	int model_number; // $v0
	int prev_mat; // $s4
	struct MODEL *model; // $a0
	struct CELL_OBJECT *building; // $s0
	{ // line 38, address 0x41394
		int spacefree; // $a0
		{ // line 81, address 0x413c4
		} // line 82, address 0x413cc
		{ // line 85, address 0x413cc
			int zBias; // $v0
			unsigned long *savedOT; // $s1
		} // line 97, address 0x41400
	} // line 97, address 0x41400
} // line 126, address 0x414a4
/*
 * Offset 0x414A4
 * D:\driver2\game\C\DRAW.C (line 2181)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ RenderModel(struct MODEL *model /*$s2*/, struct MATRIX *matrix /*$a1*/, struct VECTOR *pos /*$a2*/, int zBias /*$s0*/, int flags /*stack 16*/)
{ // line 1, address 0x414a4
	int i; // $t0
	unsigned long *savedOT; // $s1
	{ // line 10, address 0x414d0
		struct MATRIX comb; // stack address -48
	} // line 15, address 0x41500
	{ // line 29, address 0x415a0
		int spacefree; // $a0
	} // line 41, address 0x41628
} // line 43, address 0x4164c
/*
 * Offset 0x4164C
 * D:\driver2\game\C\DRAW.C (line 2267)
 * Stack frame base $sp, length 16
 */
unsigned long /*$ra*/ normalIndex(struct SVECTOR *verts /*$a0*/, unsigned int vidx /*$a1*/)
{ // line 1, address 0x4164c
	int th23; // $a0
	int nx; // $t4
	int ny; // $v1
	int nz; // $a2
	struct SVECTOR p; // stack address -16
	struct SVECTOR q; // stack address -8
	{ // line 1, address 0x4164c
		int x; // $a1
		int y; // $a0
	} // line 8, address 0x4178c
} // line 19, address 0x4180c
/*
 * Offset 0x4180C
 * D:\driver2\game\C\DRAW.C (line 1219)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetFrustrumMatrix()
{
}
/*
 * Offset 0x41844
 * D:\driver2\game\C\DRAW.C (line 1224)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ Set_Inv_CameraMatrix()
{
}
/*
 * Offset 0x4187C
 * D:\driver2\game\C\DRAW.C (line 1324)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ CalcObjectRotationMatrices()
{ // line 2, address 0x4187c
	int i; // $s1
	int j; // $a0
	struct SVECTOR ang; // stack address -56
	struct MATRIX mat; // stack address -48
} // line 17, address 0x41924
/*
 * Offset 0x41924
 * D:\driver2\game\C\DRAW.C (line 1344)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ PlotMDL_less_than_128(struct MODEL *model /*$a0*/)
{
}
/*
 * Offset 0x41950
 * D:\driver2\game\C\DRAW.C (line 854)
 * Stack frame base $sp, length 0
 */
struct CELL_OBJECT * /*$ra*/ UnpackCellObject(struct PACKED_CELL_OBJECT *ppco /*$a3*/, struct XZPAIR *near /*$t0*/)
{ // line 1, address 0x41950
	struct CELL_OBJECT *pco; // $a2
} // line 16, address 0x41a10