#include "../decomp_defs.h"

LIMBS lRoutes[5][8] = {
	{ROOT, LOWERBACK, HIPS, LHIP, LKNEE, LFOOT, LTOE, ROOT},
	{HIPS, RHIP, RKNEE, RFOOT, RTOE, ROOT, ROOT, ROOT},
	{LOWERBACK, JOINT_1, LSHOULDER, LELBOW, LHAND, LFINGERS, ROOT, ROOT},
	{JOINT_1, RSHOULDER, RELBOW, RHAND, RFINGERS, ROOT, ROOT, ROOT},
	{JOINT_1, NECK, HEAD, ROOT, ROOT, ROOT, ROOT, ROOT},
};

PED_DATA MainPed[23] =
{
	{ 0, 68u, &chest1_texture, CHEST_PAL },
	{ 1, 68u, &chest1_texture, CHEST_PAL },
	{ 17, 36u, &chest1_texture, CHEST_PAL },
	{ 6, 68u, &forearm1_texture, ARM_PAL },
	{ 8, 68u, &head1_texture, NO_PAL },
	{ 6, 68u, &arm1_texture, CHEST_PAL },
	{ 8, 36u, &arm1_texture, CHEST_PAL },
	{ 7, 68u, &forearm1_texture, ARM_PAL },
	{ 3, 244u, &forearm1_texture, ARM_PAL },
	{ 6, 68u, &arm1_texture, CHEST_PAL },
	{ 8, 36u, &arm1_texture, CHEST_PAL },
	{ 7, 68u, &forearm1_texture, ARM_PAL },
	{ 3, 244u, &forearm1_texture, ARM_PAL },
	{ 1, 68u, &jeans_texture, NO_PAL },
	{ 6, 68u, &jeans_texture, NO_PAL },
	{ 13, 100u, &jeans_texture, JEANS_PAL },
	{ 11, 244u, &jeans_texture, JEANS_PAL },
	{ 6, 63u, &chest1_texture, JEANS_PAL },
	{ 6, 68u, &arm1_texture, NO_PAL },
	{ 13, 100u, &jeans_texture, JEANS_PAL },
	{ 11, 244u, &jeans_texture, JEANS_PAL },
	{ 6, 63u, &chest1_texture, JEANS_PAL },
	{ 2, 68u, &jeans_texture, JEANS_PAL }
};

// FIXME: could be incorrect
BONE Skel[23] =
{
  {
	ROOT,
	NULL,
	1,
	{ &Skel[LOWERBACK], &Skel[HIPS], NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	NULL
  },
  {
	LOWERBACK,
	&Skel[ROOT],
	3,
	{ &Skel[JOINT_1], &Skel[LHIP], &Skel[RHIP] },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	NULL
  },
  {
	JOINT_1,
	&Skel[LOWERBACK],
	3,
	{ &Skel[NECK], &Skel[LSHOULDER], &Skel[RSHOULDER] },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[0]
  },
  {
	NECK,
	&Skel[JOINT_1],
	1,
	{ &Skel[HEAD], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[14]
  },
  {
	HEAD,
	&Skel[NECK],
	0,
	{ NULL, NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[1]
  },
  {
	LSHOULDER,
	&Skel[JOINT_1],
	1,
	{ &Skel[LELBOW], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	NULL
  },
  {
	LELBOW,
	&Skel[LSHOULDER],
	1,
	{ &Skel[LHAND], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[8]
  },
  {
	LHAND,
	&Skel[LELBOW],
	1,
	{ &Skel[LFINGERS], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[9]
  },
  {
	LFINGERS,
	&Skel[LHAND],
	0,
	{ NULL, NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[10]
  },
  {
	RSHOULDER,
	&Skel[JOINT_1],
	1,
	{ &Skel[RELBOW], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	NULL
  },
  {
	RELBOW,
	&Skel[RSHOULDER],
	1,
	{ &Skel[RHAND], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[2]
  },
  {
	RHAND,
	&Skel[RELBOW],
	1,
	{ &Skel[RFINGERS], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[3]
  },
  {
	RFINGERS,
	&Skel[RHAND],
	0,
	{ NULL, NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[4]
  },
  {
	HIPS,
	&Skel[0],
	0,
	{ &Skel[RHIP], &Skel[LHIP], NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	NULL
  },
  {
	LHIP,
	&Skel[HIPS],
	1,
	{ &Skel[LKNEE], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[15]
  },
  {
	LKNEE,
	&Skel[LHIP],
	1,
	{ &Skel[LFOOT], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[11]
  },
  {
	LFOOT,
	&Skel[LKNEE],
	1,
	{ &Skel[LTOE], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[12]
  },
  {
	LTOE,
	&Skel[LFOOT],
	0,
	{ NULL, NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[13]
  },
  {
	RHIP,
	&Skel[HIPS],
	1,
	{ &Skel[RKNEE], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	NULL
  },
  {
	RKNEE,
	&Skel[RHIP],
	1,
	{ &Skel[RFOOT], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[5]
  },
  {
	RFOOT,
	&Skel[RKNEE],
	1,
	{ &Skel[RFOOT], NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[6]
  },
  {
	RTOE,
	&Skel[RFOOT],
	0,
	{ NULL, NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	&pmTannerModels[7]
  },
  {
	JOINT,
	&Skel[LOWERBACK],
	0,
	{ NULL, NULL, NULL },
	NULL,
	NULL,
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	NULL
  }
};

int boneIdvals[15] = { 2, 3, 4, 6, 7, 8, 0xA, 0xB, 0xC, 0xF, 0x10, 0x11, 0x13, 0x14, 0x15 };



/*
 * Offset 0x65274
 * D:\driver2\game\C\MOTION_C.C (line 978)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawBodySprite(int boneId /*$s1*/, long v1 /*$a1*/, long v2 /*$a2*/, int sz /*$s7*/, int sy /*stack 16*/)
{ // line 1, address 0x65274
	struct TEXTURE_DETAILS *body_texture; // $s2
	int x0; // $s5
	int x1; // $s6
	int y0; // $fp
	int y1; // stack address -48
	int dx1; // $s4
	int dy1; // $s3
	int z; // $a3
	int z2; // $a3
	int dx2; // $t5
	int dy2; // $t3
	int width; // $t0
	int sort_fix; // $a3
	int angle; // $t3
	int c; // $t0
	int s; // $a2
	int clut; // $a2
	int tpage; // $t0
	struct POLY_FT4 *prims; // $t2
	int z1; // stack address -44
	int pal; // $v1
	{ // line 125, address 0x65618
		int tp; // $v1
	} // line 155, address 0x656b4
} // line 231, address 0x659b4
/*
 * Offset 0x659B4
 * D:\driver2\game\C\MOTION_C.C (line 1289)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ StoreVertexLists()
{ // line 2, address 0x659b4
	int i; // $t1
	int j; // $a3
	int numVerts; // $t3
	struct MODEL *pModel; // $t0
	struct SVECTOR *pVerts; // $a2
	int counter; // $t4
	struct BONE *pBone; // $a0
} // line 57, address 0x65b40
/*
 * Offset 0x65B40
 * D:\driver2\game\C\MOTION_C.C (line 1355)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupTannerSkeleton()
{ // line 2, address 0x65b40
	int i; // $t1
	struct BONE *pBone; // $a3
	char *pC; // $v0
	struct SVECTOR *store; // $t4
	struct SVECTOR_NOPAD *pSVNP; // $v1
} // line 58, address 0x65d40
/*
 * Offset 0x65D40
 * D:\driver2\game\C\MOTION_C.C (line 1421)
 * Stack frame base $sp, length 152
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ newShowTanner()
{ // line 2, address 0x65d40
	struct VECTOR *playerPos; // $a2
	struct VECTOR *camPos; // $a1
	struct VECTOR *vJPos; // $s1
	struct VECTOR v; // stack address -128
	struct MODEL *pModel; // $t0
	struct SVECTOR *mVerts; // $a1
	int i; // $s2
	int j; // $a3
	int c; // $a3
	int id; // $a2
	int limbs; // $a0
	struct BONE *pBone; // $s0
	int lval; // $t1
	{ // line 109, address 0x66108
		struct BONE *pBone; // $s0
		struct VECTOR *v1; // $a2
		struct VECTOR *v2; // $a1
		{ // line 109, address 0x66108
			struct SVECTOR *data; // $t1
			long t1; // stack address -92
			long t0; // stack address -96
			int z2; // stack address -80
			int z1; // stack address -84
			int z; // stack address -88
		} // line 109, address 0x6622c
	} // line 109, address 0x6622c
	{ // line 115, address 0x66260
		struct BONE *pBone; // $s0
		struct VECTOR *v1; // $a0
		struct VECTOR *v2; // $a2
		{ // line 115, address 0x66260
			struct SVECTOR *data; // $t0
			long t1; // stack address -72
			long t0; // stack address -76
			int z2; // stack address -60
			int z1; // stack address -64
			int z; // stack address -68
		} // line 115, address 0x66260
	} // line 115, address 0x66260
	{ // line 121, address 0x66398
		struct SVECTOR v1; // stack address -112
		struct SVECTOR v2; // stack address -104
	} // line 123, address 0x66398
	{ // line 148, address 0x664f4
		struct BONE *pBone; // $s0
		struct VECTOR *v1; // $a2
		struct VECTOR *v2; // $a1
		{ // line 148, address 0x664f4
			struct SVECTOR *data; // $t1
			long t1; // stack address -52
			long t0; // stack address -56
			int z2; // stack address -40
			int z1; // stack address -44
			int z; // stack address -48
		} // line 148, address 0x664f4
	} // line 148, address 0x664f4
	{ // line 154, address 0x66630
		int bias; // $a3
	} // line 167, address 0x6665c
} // line 178, address 0x666b0
/*
 * Offset 0x666B0
 * D:\driver2\game\C\MOTION_C.C (line 1606)
 * Stack frame base $sp, length 1104
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ newRotateBones(struct BONE *poBone /*$a0*/)
{ // line 2, address 0x666b0
	struct MATRIX mStore[32]; // stack address -1088
	struct MATRIX *pMatrix; // $s2
	struct MATRIX *oMatrix; // $s5
	struct SVECTOR *svBone; // $s6
	struct VECTOR *vBoneRotated; // $s3
	struct BONE *pBone; // $s1
	int id; // $s0
	struct SVECTOR *pVerts; // $a3
	struct SVECTOR *pmVerts; // $s0
	int numVerts; // $t0
	struct MODEL *pModel; // $v0
	int i; // $a2
	struct SVECTOR *pD; // $a0
	int c; // $s4
	int j; // $a1
	struct VECTOR sv; // stack address -64
	{ // line 3, address 0x666b0
		int cx; // $t2
		int sx; // $a3
		int cy; // $a0
		int sy; // $t0
		int cz; // $t3
		int sz; // $t6
		int stmp; // $v0
	} // line 3, address 0x666b0
} // line 160, address 0x67020
/*
 * Offset 0x67020
 * D:\driver2\game\C\MOTION_C.C (line 1774)
 * Stack frame base $sp, length 0
 */
struct SVECTOR * /*$ra*/ GetModelVertPtr(int boneId /*$a1*/, int modelType /*$a1*/)
{
}
/*
 * Offset 0x67134
 * D:\driver2\game\C\MOTION_C.C (line 1834)
 * Stack frame base $sp, length 184
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawCiv(struct PEDESTRIAN *pPed /*$fp*/)
{ // line 1, address 0x67134
	int i; // $s5
	struct DVECTOR *outpoints; // $t9
	long *outlongs; // $s5
	struct SVECTOR *psrLerpData; // $t8
	long *zbuff; // $s4
	struct SVECTOR *pLerpData; // $s0
	struct SVECTOR pos; // stack address -160
	struct VECTOR pos1; // stack address -152
	struct SVECTOR *vert1; // $a1
	struct SVECTOR *vert2; // $a0
	struct SVECTOR temp1; // stack address -136
	struct SVECTOR temp2; // stack address -128
	int cnt3; // $a2
	int bHeadModel; // stack address -56
	int shift; // $t0
	int frame; // $a2
	struct MATRIX workmatrix; // stack address -120
	int j; // $s7
	{ // line 74, address 0x67320
		int cx; // $v1
		int sx; // $a0
		int cy; // $a1
		int sy; // $t0
		int cz; // $t3
		int sz; // $t6
		int stmp; // $t7
	} // line 74, address 0x67320
	{ // line 130, address 0x67828
		struct SVECTOR sV; // stack address -88
		struct SVECTOR sV2; // stack address -80
		struct VECTOR v; // stack address -72
	} // line 142, address 0x67864
	{ // line 151, address 0x67864
		struct CVECTOR cv; // stack address -88
		struct VECTOR pos; // stack address -80
		int phase; // $s0
	} // line 164, address 0x67908
} // line 167, address 0x67908
/*
 * Offset 0x67938
 * D:\driver2\game\C\MOTION_C.C (line 2041)
 * Stack frame base $sp, length 128
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawTanner(struct PEDESTRIAN *pPed /*$s2*/)
{ // line 1, address 0x67938
	struct VECTOR v; // stack address -112
	struct CVECTOR cV; // stack address -96
	struct MATRIX mRotStore; // stack address -88
	struct MATRIX iMatrix; // stack address -56
	{ // line 1, address 0x67938
	} // line 20, address 0x67a48
	{ // line 26, address 0x67a48
		int cx; // $a2
		int sx; // $t0
		int cy; // $a0
		int sy; // $t2
		int cz; // $t5
		int sz; // $s0
		int stmp; // $v1
	} // line 26, address 0x67a48
} // line 72, address 0x67dac
/*
 * Offset 0x67DAC
 * D:\driver2\game\C\MOTION_C.C (line 2120)
 * Stack frame base $sp, length 144
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ DrawCharacter(struct PEDESTRIAN *pPed /*$s1*/)
{ // line 1, address 0x67dac
	struct MATRIX mRotStore; // stack address -128
	struct MATRIX iMatrix; // stack address -96
	struct CVECTOR cV; // stack address -64
	struct VECTOR v; // stack address -56
	{ // line 1, address 0x67dac
		int cx; // $t0
		int sx; // $a3
		int cy; // $a0
		int sy; // $t2
		int cz; // $a2
		int sz; // $t7
		int stmp; // $v1
	} // line 1, address 0x67dac
	{ // line 55, address 0x6819c
		struct CVECTOR cv; // stack address -40
		struct VECTOR pos; // stack address -32
		int phase; // $s0
	} // line 69, address 0x68238
} // line 73, address 0x68254
/*
 * Offset 0x68254
 * D:\driver2\game\C\MOTION_C.C (line 2201)
 * Stack frame base $sp, length 8
 */
void /*$ra*/ InitTannerShadow()
{ // line 2, address 0x68254
	struct CVECTOR cV; // stack address -8
	int i; // $a3
} // line 46, address 0x683c0
/*
 * Offset 0x683C0
 * D:\driver2\game\C\MOTION_C.C (line 2258)
 * Stack frame base $sp, length 296
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ TannerShadow(struct VECTOR *pPedPos /*$s6*/, struct SVECTOR *pLightPos /*$s7*/, struct CVECTOR *col /*$a2*/, short angle /*$a3*/)
{ // line 1, address 0x683c0
	int z; // $a1
	int z0; // stack address -72
	int z1; // stack address -68
	int z2; // stack address -64
	int z3; // stack address -60
	struct SVECTOR vert[4]; // stack address -272
	struct VECTOR d; // stack address -240
	struct DR_ENV *pDE; // $s3
	struct DRAWENV drEnv; // stack address -224
	struct VECTOR cp; // stack address -128
	struct SVECTOR ca; // stack address -112
	struct VECTOR v1; // stack address -104
	int i; // $s4
	struct VECTOR myVector; // stack address -88
	int avalue2; // $v0
	int w; // $v1
	{ // line 117, address 0x68880
	} // line 117, address 0x68880
} // line 176, address 0x68b94
/*
 * Offset 0x68B94
 * D:\driver2\game\C\MOTION_C.C (line 2442)
 * Stack frame base $sp, length 200
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ DoCivHead(struct SVECTOR *vert1 /*$s1*/, struct SVECTOR *vert2 /*$s3*/)
{ // line 1, address 0x68b94
	struct VECTOR headpos; // stack address -184
	struct SVECTOR final_rotation; // stack address -168
	struct SVECTOR spos1; // stack address -160
	struct MODEL *model; // $s5
	struct MATRIX work2matrix; // stack address -152
	struct MATRIX mRotStore; // stack address -120
	struct VECTOR pos1; // stack address -88
	int pal; // $v1
	int ci; // $s6
	{ // line 53, address 0x68da0
		int cx; // $v1
		int sx; // $a0
		int cy; // $a1
		int sy; // $t0
		int cz; // $t3
		int sz; // $t6
		int stmp; // $a3
	} // line 53, address 0x68da0
	{ // line 65, address 0x69000
		int cx; // $v1
		int sx; // $t3
		int cy; // $t1
		int sy; // $a3
		int stmp; // $v0
	} // line 65, address 0x69000
	{ // line 93, address 0x692dc
		struct MATRIX comb; // stack address -72
	} // line 95, address 0x692dc
} // line 112, address 0x69474
/*
 * Offset 0x694A0
 * D:\driver2\game\C\MOTION_C.C (line 2562)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawObject(struct MODEL *model /*$t8*/, struct MATRIX *matrix /*$a1*/, struct VECTOR *pos /*$a2*/, int z_correct /*$a3*/)
{ // line 1, address 0x694a0
	struct DVECTOR *outpoints; // $t7
	short *zbuff; // $t5
	struct SVECTOR *verts; // $t6
	char *polys; // $s0
	int cnt3; // $t1
	int i; // $s1
	int z0; // stack address -40
	int z1; // stack address -36
	int z2; // stack address -32
	long *outlongs; // $s2
	int z; // stack address -28
	{ // line 92, address 0x6983c
	} // line 101, address 0x698a8
} // line 121, address 0x698dc
/*
 * Offset 0x698DC
 * D:\driver2\game\C\MOTION_C.C (line 2690)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ wjmDraw3()
{ // line 2, address 0x698dc
	struct POLYFT3 *src; // $a3
	short *zbuff; // $t2
	long *outlongs; // $a2
	struct POLY_FT3 *prims; // $t1
	unsigned long clut; // $t0
	unsigned long tpage; // $a1
	int z; // $a2
} // line 34, address 0x69aa0
/*
 * Offset 0x69AA0
 * D:\driver2\game\C\MOTION_C.C (line 853)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ProcessMotionLump(char *lump_ptr /*$a0*/, int lump_size /*$s0*/)
{
}
/*
 * Offset 0x69B20
 * D:\driver2\game\C\MOTION_C.C (line 944)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupPedMotionData(struct PEDESTRIAN *pPed /*$a0*/)
{
}
/*
 * Offset 0x69B40
 * D:\driver2\game\C\MOTION_C.C (line 2011)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetSkelModelPointers(int type /*$a0*/)
{
}
/*
 * Offset 0x69BD4
 * D:\driver2\game\C\MOTION_C.C (line 955)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupPedestrian(struct PEDESTRIAN *pedptr /*$a0*/)
{
}