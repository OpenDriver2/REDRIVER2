#include "../decomp_defs.h"

SVECTOR day_vectors[4] =
{
  { 62404, 2520, 783, 0 },
  { 62404, 2520, 783, 0 },
  { 63172, 2364, 2364, 0 },
  { 62404, 2520, 783, 0 }
};

SVECTOR night_vectors[4] =
{
  { 3132, 2520, 783, 0 },
  { 3132, 2520, 783, 0 },
  { 63172, 2364, 63172, 0 },
  { 3132, 2520, 783, 0 }
};

SVECTOR day_colours[4] =
{
  { 3200, 3200, 3200, 0 },
  { 3200, 3200, 3200, 0 },
  { 3200, 3200, 3200, 0 },
  { 3200, 3200, 3200, 0 }
};

SVECTOR night_colours[4] =
{
  { 880, 880, 905, 0 },
  { 880, 880, 905, 0 },
  { 880, 880, 905, 0 },
  { 880, 880, 905, 0 }
};

MATRIX light_matrix =
{ { { 4096, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, { 0, 0, 0 } };

MATRIX colour_matrix =
{ { { 4032, 0, 0 }, { 3936, 0, 0 }, { 3520, 0, 0 } }, { 0, 0, 0 } };

int PolySizes[56] = { 
	8, 0xC, 0x10, 0x18, 0x14, 0x14, 0x1C, 0x20, 8, 0xC,
	0x10, 0x10, 0, 0, 0, 0, 0xC, 0xC, 0xC, 0x10, 0x14,
	0x14, 0x18, 0x18, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0xC,
	0x10, 0x18, 0x14, 0x14, 0x1C, 0x20, 0, 0, 0, 0, 0,
	0, 0, 0, 0xC, 0xC, 0xC, 0x10, 0x14, 0x14, 0x18, 0x18 
};

/*
 * Offset 0x20CFC
 * D:\driver2\game\C\CARS.C (line 834)
 * Stack frame base $sp, length 96
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ plotNewCarModel(struct CAR_MODEL *car /*$s0*/, int palette /*$s2*/)
{ // line 1, address 0x20cfc
	struct plotCarGlobals _pg; // stack address -72
	struct SVECTOR v0; // stack address -32
	unsigned long lightlevel; // stack address -24
} // line 74, address 0x20ef0
/*
 * Offset 0x20F08
 * D:\driver2\game\C\CARS.C (line 1125)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 s1
 */
void /*$ra*/ plotCarPolyGT3(int numTris /*$a0*/, struct CAR_POLY *src /*$t1*/, struct SVECTOR *vlist /*$s0*/, struct SVECTOR *nlist /*$a3*/, struct plotCarGlobals *pg /*stack 16*/, int palette /*stack 20*/)
{ // line 1, address 0x20f08
	struct POLY_GT3 *prim; // $t0
	long *ot; // $s1
	long GT3rgb; // stack address -24
	int i; // $t7
	int v0; // $t3
	int v1; // $t4
	int v2; // $t2
	int n0; // $t3
	int n1; // $a2
	int n2; // $a0
	int r0; // stack address -20
	int r1; // stack address -16
	int r2; // $v0
	int reg; // $a0
	int clut_uv0; // $a1
	int tpage_uv1; // $t6
	int uv3_uv2; // $t5
	unsigned short *clut_base; // $t9
	{ // line 1, address 0x20f08
		int ofse; // $v1
	} // line 1, address 0x20f08
	{ // line 106, address 0x210a8
		int ofse; // $v1
	} // line 106, address 0x210a8
} // line 126, address 0x21120
/*
 * Offset 0x21120
 * D:\driver2\game\C\CARS.C (line 1442)
 * Stack frame base $sp, length 344
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawCar(struct _CAR_DATA *cp /*$s3*/, int view /*$a1*/)
{ // line 1, address 0x21120
	int WheelSpeed; // $s0
	int model; // $fp
	struct _PLAYER *lp; // $a2
	{ // line 12, address 0x211dc
		struct CVECTOR col; // stack address -312
	} // line 50, address 0x212ac
	{ // line 54, address 0x212ac
		struct MATRIX temp_mat1; // stack address -304
		struct MATRIX temp_mat2; // stack address -272
		struct MATRIX final_mat; // stack address -240
		struct VECTOR pos; // stack address -208
		struct VECTOR pos1; // stack address -192
		struct SVECTOR temp_vec; // stack address -176
		int result; // $s4
		{ // line 77, address 0x212f8
			struct VECTOR corners[4]; // stack address -168
		} // line 96, address 0x213ec
		{ // line 100, address 0x213ec
			struct VECTOR d; // stack address -104
			struct VECTOR dist; // stack address -88
		} // line 117, address 0x21540
		{ // line 168, address 0x215b4
			int i; // $a0
		} // line 173, address 0x215d8
		{ // line 185, address 0x2160c
			struct MATRIX workmatrix; // stack address -104
			struct CAR_MODEL *CarModelPtr; // $s1
			{ // line 193, address 0x2166c
			} // line 195, address 0x21688
		} // line 197, address 0x21688
		{ // line 208, address 0x216dc
			int damage; // $v1
			{ // line 264, address 0x21824
				struct CAR_MODEL *CarModelPtr; // $s0
				{ // line 264, address 0x21824
					struct MATRIX workmatrix; // stack address -72
				} // line 293, address 0x21924
			} // line 294, address 0x21924
		} // line 295, address 0x21924
		{ // line 314, address 0x21984
		} // line 322, address 0x219ec
	} // line 346, address 0x21b30
} // line 347, address 0x21b30
/*
 * Offset 0x21B60
 * D:\driver2\game\C\CARS.C (line 1850)
 * Stack frame base $sp, length 160
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawCarWheels(struct _CAR_DATA *cp /*$fp*/, struct MATRIX *RearMatrix /*stack 4*/, struct VECTOR *pos /*stack 8*/, int zclip /*$a3*/)
{ // line 1, address 0x21b60
	struct CAR_COSMETICS *car_cos; // $s0
	struct MATRIX FrontMatrix; // stack address -144
	struct MODEL *WheelModel; // $s0
	struct MODEL *WheelModelBack; // stack address -56
	struct MODEL *WheelModelFront; // stack address -52
	int i; // $s4
	static short FrontWheelRotation[20]; // address 0x0
	static short BackWheelRotation[20]; // address 0x30
	short model; // $a0
	short wheelSize; // $s2
	{ // line 16, address 0x21c10
		int FrontWheelIncrement; // $a3
		int BackWheelIncrement; // $t0
	} // line 69, address 0x21d38
	{ // line 72, address 0x21d38
		int c; // $t2
		int s; // $t3
		int FW1z; // $v0
		int FW2z; // $a0
		int BW1z; // $v0
		int BW2z; // $a3
		struct SVECTOR *VertPtr; // $t6
	} // line 76, address 0x21d38
	{ // line 76, address 0x21d38
		struct MATRIX SteerMatrix; // stack address -112
	} // line 76, address 0x21d38
	{ // line 138, address 0x2200c
		struct SVECTOR *verts; // $s5
		{ // line 157, address 0x22060
			struct VECTOR WheelPos; // stack address -80
			struct SVECTOR sWheelPos; // stack address -64
		} // line 162, address 0x22090
	} // line 194, address 0x22180
} // line 196, address 0x221e8
/*
 * Offset 0x221E8
 * D:\driver2\game\C\CARS.C (line 2058)
 * Stack frame base $sp, length 8
 */
void /*$ra*/ DrawWheelObject(struct MODEL *model /*$t2*/, struct SVECTOR *verts /*$t4*/, int transparent /*$a2*/, int wheelnum /*$a3*/)
{ // line 1, address 0x221e8
	struct POLY_FT4 *prims; // $t0
	struct POLYFT4LIT *src; // $t1
	int i; // $t2
	int Z; // stack address -4
	int clut; // $t8
	int tpage; // $t7
	unsigned long bright; // $t6
	unsigned long dim; // $t5
	{ // line 35, address 0x22300
		int flag1; // stack address -8
		long vl; // $a0
		{ // line 53, address 0x223b0
			int r2; // $v1
		} // line 53, address 0x223b0
	} // line 83, address 0x22498
} // line 85, address 0x224c0
/*
 * Offset 0x224C0
 * D:\driver2\game\C\CARS.C (line 2198)
 * Stack frame base $sp, length 112
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ComputeCarLightingLevels(struct _CAR_DATA *cp /*$s1*/, char detail /*$s3*/)
{ // line 1, address 0x224c0
	int light; // $s2
	struct SVECTOR lightsourcevector; // stack address -96
	struct SVECTOR colour; // stack address -88
	struct VECTOR lightValues; // stack address -80
	struct VECTOR *orient; // $s0
	{ // line 72, address 0x22774
		struct MODEL *model; // $v1
		struct SVECTOR *norms; // $a3
		struct SVECTOR *ppads; // $a2
		int num_norms; // $a1
		int count; // $a1
		struct CVECTOR c0; // stack address -64
		struct CVECTOR c1; // stack address -56
		struct CVECTOR c2; // stack address -48
		{ // line 78, address 0x22774
			long GT3rgb; // stack address -40
		} // line 78, address 0x22774
	} // line 114, address 0x2289c
} // line 118, address 0x228c8
/*
 * Offset 0x228C8
 * D:\driver2\game\C\CARS.C (line 2321)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ buildNewCars()
{
}
/*
 * Offset 0x229C8
 * D:\driver2\game\C\CARS.C (line 2357)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ buildNewCarFromModel(struct CAR_MODEL *car /*$s5*/, struct MODEL *model /*$s7*/, int first /*$a2*/)
{ // line 1, address 0x229c8
	char *polylist; // $s0
	int i; // $s2
	int j; // $s3
	int pass; // $s4
	{ // line 37, address 0x22b04
		struct CAR_POLY *p; // $s1
		char ptype; // $s6
		{ // line 46, address 0x22b4c
		} // line 48, address 0x22b4c
		{ // line 51, address 0x22b4c
		} // line 53, address 0x22b4c
		{ // line 57, address 0x22b4c
		} // line 59, address 0x22b4c
		{ // line 62, address 0x22b4c
		} // line 64, address 0x22b4c
		{ // line 69, address 0x22b4c
		} // line 77, address 0x22b4c
		{ // line 80, address 0x22b4c
		} // line 92, address 0x22b4c
		{ // line 96, address 0x22b4c
		} // line 104, address 0x22b84
		{ // line 107, address 0x22b84
		} // line 119, address 0x22be4
		{ // line 123, address 0x22be4
		} // line 125, address 0x22be4
		{ // line 129, address 0x22be4
		} // line 131, address 0x22be4
		{ // line 135, address 0x22be4
		} // line 147, address 0x22c78
		{ // line 150, address 0x22c78
		} // line 169, address 0x22d8c
		{ // line 173, address 0x22d8c
		} // line 191, address 0x22e94
		{ // line 194, address 0x22e94
		} // line 222, address 0x23044
	} // line 225, address 0x23044
} // line 236, address 0x23100
/*
 * Offset 0x23130
 * D:\driver2\game\C\CARS.C (line 2595)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MangleWheelModels()
{ // line 2, address 0x23130
	int i; // $v1
	struct MODEL *m; // $t0
	struct POLYFT4LIT *src; // $a0
	{ // line 15, address 0x23178
		int j; // $t1
	} // line 46, address 0x233bc
} // line 54, address 0x233f8
/*
 * Offset 0x233F8
 * D:\driver2\game\C\CARS.C (line 2697)
 * Stack frame base $sp, length 0
 */
char /*$ra*/ GetCarPalIndex(int tpage /*$a0*/)
{ // line 1, address 0x233f8
	int i; // $a1
} // line 16, address 0x2343c
/*
 * Offset 0x23444
 * D:\driver2\game\C\CARS.C (line 1793)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ DrawCarObject(struct CAR_MODEL *car /*$s0*/, struct MATRIX *matrix /*$a1*/, struct VECTOR *pos /*$a2*/, struct VECTOR *pos1 /*$a3*/, int palette /*stack 16*/, struct _CAR_DATA *cp /*stack 20*/, int detail /*stack 24*/)
{ // line 1, address 0x23444
	{ // line 1, address 0x23444
		struct SVECTOR cog; // stack address -40
		struct VECTOR modelLocation; // stack address -32
	} // line 1, address 0x23444
	{ // line 1, address 0x23444
		static unsigned long savedSP; // address 0x0
	} // line 40, address 0x23544
} // line 43, address 0x23544
/*
 * Offset 0x23544
 * D:\driver2\game\C\CARS.C (line 2152)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ PlayerCarFX(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x23544
	int WheelSpeed; // $s1
} // line 39, address 0x23660
/*
 * Offset 0x23660
 * D:\driver2\game\C\CARS.C (line 2656)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ setupLightingMatrices()
{
}
/*
 * Offset 0x237B8
 * D:\driver2\game\C\CARS.C (line 2685)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ restoreLightingMatrices()
{
}
/*
 * Offset 0x23820
 * D:\driver2\game\C\CARS.C (line 917)
 * Stack frame base $sp, length 8
 */
void /*$ra*/ plotCarPolyB3(int numTris /*$a0*/, struct CAR_POLY *src /*$a1*/, struct SVECTOR *vlist /*$a2*/, struct plotCarGlobals *pg /*$a3*/)
{ // line 1, address 0x23820
	struct POLY_F3 *prim; // $t0
	int i; // $t1
	long *ot; // $t3
	long F3rgb; // $t4
	{ // line 10, address 0x23848
		int reg; // stack address -8
	} // line 50, address 0x23914
} // line 53, address 0x2392c
/*
 * Offset 0x2392C
 * D:\driver2\game\C\CARS.C (line 976)
 * Stack frame base $sp, length 8
 */
void /*$ra*/ plotCarPolyFT3(int numTris /*$a0*/, struct CAR_POLY *src /*$t1*/, struct SVECTOR *vlist /*$t4*/, struct plotCarGlobals *pg /*$t5*/)
{ // line 1, address 0x2392c
	struct POLY_FT3 *prim; // $t0
	long *ot; // $t6
	long FT3rgb; // stack address -8
	int i; // $t2
	{ // line 16, address 0x2396c
		int reg; // stack address -4
		int clut_uv0; // $a2
		int tpage_uv1; // $a3
		int uv3_uv2; // $a1
		{ // line 22, address 0x2396c
			int ofse; // $v1
		} // line 22, address 0x2396c
	} // line 76, address 0x23a70
} // line 79, address 0x23a88
/*
 * Offset 0x23A88
 * D:\driver2\game\C\CARS.C (line 1349)
 * Stack frame base $sp, length 8
 */
void /*$ra*/ plotCarPolyGT3nolight(int numTris /*$a0*/, struct CAR_POLY *src /*$t3*/, struct SVECTOR *vlist /*$t6*/, struct plotCarGlobals *pg /*$a3*/, int palette /*stack 16*/)
{ // line 1, address 0x23a88
	struct POLY_FT3 *prim; // $t0
	long *ot; // $t7
	long GT3rgb; // stack address -8
	int i; // $t4
	unsigned short *clut_base; // $t8
	{ // line 17, address 0x23ad0
		int reg; // stack address -4
		int clut_uv0; // $a0
		int tpage_uv1; // $t1
		int uv3_uv2; // $t2
		{ // line 22, address 0x23ad0
			int ofse; // $v1
		} // line 22, address 0x23ad0
	} // line 76, address 0x23bfc
} // line 79, address 0x23c14