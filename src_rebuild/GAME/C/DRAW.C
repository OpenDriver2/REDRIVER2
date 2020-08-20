#include "THISDUST.H"

#include "INLINE_C.H"

#include "DRAW.H"
#include "MAIN.H"
#include "MAP.H"
#include "MODELS.H"
#include "SYSTEM.H"
#include "CAMERA.H"
#include "MISSION.H"
#include "CELL.H"
#include "TILE.H"
#include "OBJANIM.H"
#include "TEXTURE.H"
#include "CARS.H"
#include "DEBRIS.H"
#include "../ASM/ASMTEST.H"

#include <string.h>

MATRIX aspect =
{ 
	{ 
		{ 6553, 0, 0 }, 
		{ 0, 4096, 0 }, 
		{ 0, 0, 4096 } 
	}, 
	{ 0, 0, 0 } 
};

int PolySizes[56] = {
	8,  12, 16, 24,
	20, 20, 28, 32,
	8,  12, 16, 16,
	0,  0,  0,  0,
	12, 12, 12, 16,
	20, 20, 24, 24,
	0,  0,  0,  0,
	0,  0,  0,  0,
	8,  12, 16, 24,
	20, 24, 28, 32,
	0,  0,  0,  0,
	0,  0,  0,  0,
	12, 12, 12, 16,
	20, 20, 24, 24,
};

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

unsigned long planeColours[8];

MATRIX inv_camera_matrix;
MATRIX face_camera;
MATRIX2 CompoundMatrix[64];


uint farClip2Player = 0x8ca0;

static int treecount = 0;
int numSpritesFound = 0;
static int alleycount = 0;

int goFaster = 1;
int fasterToggle = 0;

int current_object_computed_value = 0;

int combointensity;

int buildingsFound = 0;
int cell_object_index = 0;

CELL_OBJECT cell_object_buffer[1024];
CELL_OBJECT* model_object_ptrs[512];
CELL_OBJECT* anim_obj_buffer[20];

unsigned long *tile_overflow_buffer;

PACKED_CELL_OBJECT *spriteList[75];

#ifndef PSX
OUT_CELL_FILE_HEADER cell_header;
#endif // PSX

char CurrentPVS[444]; // 20*20+4
MATRIX2 matrixtable[64];
int setupYet = 0;

int gDrawDistance = 441;

// offset: 0x1f800020
_pct plotContext;

// decompiled code
// original method signature: 
// void /*$ra*/ addSubdivSpriteShadow(struct POLYFT4LIT *src /*$t3*/, struct SVECTOR *verts /*$t2*/, int z /*$a2*/)
 // line 651, offset 0x0003ed7c
	/* begin block 1 */
		// Start line: 652
		// Start offset: 0x0003ED7C
		// Variables:
	// 		unsigned long word0; // $a0
	// 		unsigned long vidx; // $t1
	// 		struct _pct *pc; // $t0
	// 		int w; // $s0
	/* end block 1 */
	// End offset: 0x0003EF64
	// End Line: 670

	/* begin block 2 */
		// Start line: 1302
	/* end block 2 */
	// End Line: 1303

	/* begin block 3 */
		// Start line: 1305
	/* end block 3 */
	// End Line: 1306

MVERTEX MVERTEX_ARRAY_1f800228[5][5];

// [D] [A]
void addSubdivSpriteShadow(POLYFT4LIT *src, SVECTOR *verts, int z)
{
	uint puVar1;
	uint uVar2;
	uint uVar3;
	uint uVar4;
	int m;

	m = 4;
	uVar3 = *(uint *)&src->v0;

	plotContext.colour = 0x2e000000;


	plotContext.clut = texture_cluts[src->texture_set][src->texture_id];// << 0x10;
	plotContext.tpage = (texture_pages[src->texture_set]);// << 0x10;

	if (3200 < z) 
		m = 2;

#if 1 // [A] this is temporary code to draw shadow sprites
	{
		gte_ldv3(&verts[src->v0], &verts[src->v1], &verts[src->v2]);

		gte_rtpt();

		int ZZ;
		gte_stopz(&ZZ);

		gte_avsz3();

		int Z;
		gte_stotz(&Z);

		if (0 < Z && ZZ < 0)
		{
			POLY_FT4* poly = (POLY_FT4*)plotContext.primptr;

			*(uint*)&poly->r0 = plotContext.colour;

			setPolyFT4(poly);
			setSemiTrans(poly, 1);

			poly->clut = plotContext.clut;
			poly->tpage = plotContext.tpage;

			gte_stsxy3(&poly->x0, &poly->x1, &poly->x3);

			gte_ldv0(&verts[src->v3]);
			gte_rtps();

			gte_stsxy(&poly->x2);

			*(u_short*)&poly->u0 = *(u_short*)&src->uv1;
			*(u_short*)&poly->u1 = *(u_short*)&src->uv0;
			*(u_short*)&poly->u2 = *(u_short*)&src->uv2;
			*(u_short*)&poly->u3 = *(u_short*)&src->uv3;

			addPrim(plotContext.ot + (Z >> 1) , poly);

			plotContext.primptr += sizeof(POLY_FT4);
		}
	}
#else
	plotContext.ot += 28;

	copyVector(&MVERTEX_ARRAY_1f800228[0][0], &verts[src->v0]);
	MVERTEX_ARRAY_1f800228[0][0].uv.val = *(ushort*)&src->uv0;

	copyVector(&MVERTEX_ARRAY_1f800228[0][1], &verts[src->v1]);
	MVERTEX_ARRAY_1f800228[0][1].uv.val = *(ushort*)&src->uv1;

	copyVector(&MVERTEX_ARRAY_1f800228[0][2], &verts[src->v3]);
	MVERTEX_ARRAY_1f800228[0][2].uv.val = *(ushort*)&src->uv3;

	copyVector(&MVERTEX_ARRAY_1f800228[0][3], &verts[src->v2]);
	MVERTEX_ARRAY_1f800228[0][3].uv.val = *(ushort*)&src->uv2;

	makeMesh((MVERTEX(*)[5][5])MVERTEX_ARRAY_1f800228, m, m);
	drawMesh((MVERTEX(*)[5][5])MVERTEX_ARRAY_1f800228, m, m, &plotContext);
	
	plotContext.ot -= 28;
#endif


}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSprites(int numFound /*$a2*/)
 // line 675, offset 0x0003ef64
	/* begin block 1 */
		// Start line: 676
		// Start offset: 0x0003EF64
		// Variables:
	// 		struct XZPAIR near; // stack offset -80
	// 		struct PACKED_CELL_OBJECT **list; // stack offset -64
	// 		unsigned long spriteColour; // stack offset -60
	// 		int numShadows; // stack offset -56

		/* begin block 1.1 */
			// Start line: 676
			// Start offset: 0x0003EF64
			// Variables:
		// 		struct SVECTOR result; // stack offset -72
		// 		unsigned char lightLevel; // $a1
		/* end block 1.1 */
		// End offset: 0x0003F0FC
		// End Line: 716

		/* begin block 1.2 */
			// Start line: 716
			// Start offset: 0x0003F0FC
			// Variables:
		// 		int i; // $t0
		/* end block 1.2 */
		// End offset: 0x0003F174
		// End Line: 729

		/* begin block 1.3 */
			// Start line: 743
			// Start offset: 0x0003F1F0
			// Variables:
		// 		struct PACKED_CELL_OBJECT *ppco; // $fp
		// 		struct MODEL *model; // $s4
		// 		int z; // stack offset -52
		// 		int yang; // $a0

			/* begin block 1.3.1 */
				// Start line: 770
				// Start offset: 0x0003F2A8
			/* end block 1.3.1 */
			// End offset: 0x0003F2A8
			// End Line: 770

			/* begin block 1.3.2 */
				// Start line: 776
				// Start offset: 0x0003F2F0
				// Variables:
			// 		struct POLYFT4LIT *src; // $s0
			// 		struct SVECTOR *verts; // $s3
			// 		int i; // $s1

				/* begin block 1.3.2.1 */
					// Start line: 781
					// Start offset: 0x0003F338
					// Variables:
				// 		unsigned long vidx; // $a3
				/* end block 1.3.2.1 */
				// End offset: 0x0003F338
				// End Line: 782
			/* end block 1.3.2 */
			// End offset: 0x0003F49C
			// End Line: 794
		/* end block 1.3 */
		// End offset: 0x0003F59C
		// End Line: 807
	/* end block 1 */
	// End offset: 0x0003F5F0
	// End Line: 809

	/* begin block 2 */
		// Start line: 1384
	/* end block 2 */
	// End Line: 1385

	/* begin block 3 */
		// Start line: 1390
	/* end block 3 */
	// End Line: 1391

	/* begin block 4 */
		// Start line: 1401
	/* end block 4 */
	// End Line: 1402

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

MATRIX shadowMatrix;


// [D] [A]
void DrawSprites(int numFound)
{
	ushort *puVar1;
	short sVar2;
	short *psVar3;
	int z;
	uint *puVar4;
	uint *puVar5;
	uint uVar6;
	MATRIX *pMVar7;
	MATRIX *pMVar8;
	uint uVar9;
	int iVar10;
	uint uVar11;
	int iVar12;
	MODEL *model;
	PACKED_CELL_OBJECT *pco;
	PACKED_CELL_OBJECT **local_40;
	int local_38;
	int local_2c;

	z = FIXED(camera_matrix.m[2][0] * day_vectors[GameLevel].vx) +
		FIXED(camera_matrix.m[2][1] * day_vectors[GameLevel].vy) +
		FIXED(camera_matrix.m[2][2] * day_vectors[GameLevel].vz) + 0x1000 * 0xc00;

	uVar6 = (z >> 0x12) + 0x20U & 0xff;

	if (gTimeOfDay == 1) 
		goto LAB_0003f0c4;

	if (gTimeOfDay < 2) 
	{
		if (gTimeOfDay != 0)
			goto LAB_0003f0c4;
	LAB_0003f0a8:
		uVar6 = (int)(uVar6 * 2 * NightAmbient) >> 8;
	}
	else 
	{
		if (gTimeOfDay == 2)
			goto LAB_0003f0a8;

		if (gTimeOfDay != 3)
			goto LAB_0003f0c4;

		uVar6 = uVar6 / 3;
	}

	uVar6 = uVar6 & 0xff;

LAB_0003f0c4:
	if (gWeather - 1U < 2) 
	{
		uVar6 = (int)(uVar6 * 2 * NightAmbient) >> 8 & 0xff;
	}

	uVar6 = uVar6 << 0x10 | uVar6 << 8 | 0x2c000000 | uVar6;
	
	pMVar8 = &inv_camera_matrix;
	pMVar7 = &shadowMatrix;
	z = 2;

	do {
		shadowMatrix.m[z][0] = inv_camera_matrix.m[z][2];
		shadowMatrix.m[z][1] = -inv_camera_matrix.m[z][0];
		shadowMatrix.m[z][2] = inv_camera_matrix.m[z][0];
		z--;
	} while (-1 < z);

	local_38 = 0;
	plotContext.primptr = current->primptr;
	plotContext.ptexture_pages = (ushort(*)[128])texture_pages;
	plotContext.ptexture_cluts = (ushort(*)[128][32])texture_cluts;
	plotContext.ot = current->ot;

	local_40 = spriteList;

	plotContext.colour = uVar6;
	plotContext.current = current;

	local_2c = numFound - 1;
	while (local_2c != -1)
	{
		pco = *local_40;
		local_40++;

		int modelnumber = (pco->value >> 6) | (pco->pos.vy & 1) << 10;

		model = modelpointers[modelnumber];
		plotContext.colour = uVar6;

		if ((pco->value & 0x3f) == 0x3f) 
			plotContext.colour = 0x2c808080;

		plotContext.scribble[0] = pco->pos.vx;
		plotContext.scribble[1] = (pco->pos.vy << 0x10) >> 0x11;
		plotContext.scribble[2] = pco->pos.vz;

		z = Apply_InvCameraMatrixAndSetMatrix((VECTOR_NOPAD *)plotContext.scribble, (MATRIX2 *)&face_camera);
#if 0
		if(z < 1001)
		{
			uVar11 = (uint)model->num_polys;
			iVar10 = model->poly_block;
			iVar12 = model->vertices;

			while (uVar11 = uVar11 - 1, uVar11 != 0xffffffff) 
			{
				UNIMPLEMENTED();
				/*
				uVar9 = *(uint *)(iVar10 + 4);
				plotContext.clut =(uint)(ushort)texture_cluts[(uint)*(unsigned char *)(iVar10 + 1) * 0x20 + (uint)*(unsigned char *)(iVar10 + 2)] << 0x10;
				puVar4 = (uint *)((uVar9 & 0xff) * 8 + iVar12);
				plotContext.tpage = (uint)(ushort)texture_pages[(uint)*(unsigned char *)(iVar10 + 1)] << 0x10;
				MVERTEX_ARRAY_1f800228[0]_0_4_ = *puVar4;
				puVar5 = (uint *)((uVar9 >> 5 & 0x7f8) + iVar12);
				MVERTEX_ARRAY_1f800228[0]._4_4_ =
					puVar4[1] & 0xffff | (uint)*(ushort *)(iVar10 + 8) << 0x10;
				MVERTEX_ARRAY_1f800228[4]._0_4_ = *puVar5;
				puVar4 = (uint *)((uVar9 >> 0x18) * 8 + iVar12);
				MVERTEX_ARRAY_1f800228[4]._4_4_ =
					puVar5[1] & 0xffff | (uint)*(ushort *)(iVar10 + 10) << 0x10;
				MVERTEX_ARRAY_1f800228[20]._0_4_ = *puVar4;
				puVar5 = (uint *)((uVar9 >> 0xd & 0x7f8) + iVar12);
				MVERTEX_ARRAY_1f800228[20]._4_4_ =
					puVar4[1] & 0xffff | (uint)*(ushort *)(iVar10 + 0xe) << 0x10;
				MVERTEX_ARRAY_1f800228[24]._0_4_ = *puVar5;
				puVar1 = (ushort *)(iVar10 + 0xc);
				iVar10 = iVar10 + 0x14;
				MVERTEX_ARRAY_1f800228[24]._4_4_ = puVar5[1] & 0xffff | (uint)*puVar1 << 0x10;

				makeMesh((MVERTEX(*)[5][5])MVERTEX_ARRAY_1f800228, 4, 4);
				drawMesh((MVERTEX(*)[5][5])MVERTEX_ARRAY_1f800228, 4, 4, (_pct *)&plotContext);
				*/
			}
		}
		else 
#else
		if (z > 0)
#endif
		{
			plotContext.ot -= 133;

			Tile1x1(model);

			plotContext.ot += 133;
		}

		local_2c--;

		if ((((wetness == 0) && (gTimeOfDay != 3)) && ((pco->value & 0x20) == 0)) &&
			((z < 7000 && (local_38 = local_38 + 1, local_38 < 0x28)))) 
		{
			gte_SetRotMatrix(&shadowMatrix);

			addSubdivSpriteShadow((POLYFT4LIT *)model->poly_block, (SVECTOR *)model->vertices, z);

			if (model->num_polys == 2)
			{
				addSubdivSpriteShadow((POLYFT4LIT *)(model->poly_block + sizeof(POLYFT4LIT)), (SVECTOR *)model->vertices, z);
			}

			gte_SetRotMatrix(&face_camera);
		}
	}
	current->primptr = plotContext.primptr;
}



// decompiled code
// original method signature: 
// struct PACKED_CELL_OBJECT * /*$ra*/ GetNextPackedCop(struct CELL_ITERATOR *pci /*$a0*/)
 // line 813, offset 0x0003f5f0
	/* begin block 1 */
		// Start line: 814
		// Start offset: 0x0003F5F0
		// Variables:
	// 		struct PACKED_CELL_OBJECT *ppco; // $a3
	// 		unsigned short num; // $a1
	/* end block 1 */
	// End offset: 0x0003F6B0
	// End Line: 853

	/* begin block 2 */
		// Start line: 1812
	/* end block 2 */
	// End Line: 1813

	/* begin block 3 */
		// Start line: 1817
	/* end block 3 */
	// End Line: 1818

	/* begin block 4 */
		// Start line: 1821
	/* end block 4 */
	// End Line: 1822

// [D]
PACKED_CELL_OBJECT * GetNextPackedCop(CELL_ITERATOR *pci)
{
	unsigned char bVar1;
	ushort uVar2;
	PACKED_CELL_OBJECT *pPVar3;
	CELL_DATA *pCVar4;
	uint uVar5;
	uint uVar6;
	PACKED_CELL_OBJECT *pPVar7;

	pPVar3 = cell_objects;
	do {
		do {
			pCVar4 = pci->pcd;
			if ((pCVar4->num & 0x8000) != 0) 
				return NULL;

			pci->pcd = pCVar4 + 1;
			uVar2 = pCVar4[1].num;
			uVar6 = (uint)uVar2 & 0x3fff;

			if ((uVar2 & 0x4000) != 0)
				return NULL;

			pPVar7 = pPVar3 + uVar6;
		} while ((pPVar7->value == 0xffff) && (((pPVar7->pos).vy & 1) != 0));

		if (pci->use_computed == 0)
			goto LAB_0003f6a4;

		bVar1 = cell_object_computed_values[uVar6 >> 3];
		uVar5 = 1 << ((uint)uVar2 & 7) & 0xffff;

	} while ((bVar1 & uVar5) != 0);

	cell_object_computed_values[uVar6 >> 3] = bVar1 | (unsigned char)uVar5;

LAB_0003f6a4:
	pci->ppco = pPVar7;
	return pPVar7;
}



// decompiled code
// original method signature: 
// struct CELL_OBJECT * /*$ra*/ UnpackCellObject(struct PACKED_CELL_OBJECT *ppco /*$a3*/, struct XZPAIR *near /*$t0*/)
 // line 854, offset 0x000418e8
	/* begin block 1 */
		// Start line: 855
		// Start offset: 0x000418E8
		// Variables:
	// 		struct CELL_OBJECT *pco; // $a2
	/* end block 1 */
	// End offset: 0x000419A8
	// End Line: 870

	/* begin block 2 */
		// Start line: 4699
	/* end block 2 */
	// End Line: 4700

	/* begin block 3 */
		// Start line: 1708
	/* end block 3 */
	// End Line: 1709

CELL_OBJECT* UnpackCellObject(PACKED_CELL_OBJECT *ppco, XZPAIR *near)
{
	CELL_OBJECT *pco;

	if (ppco == NULL)
		return NULL;

	pco = &cell_object_buffer[cell_object_index];
	cell_object_index = cell_object_index + 1U & 0x3ff;

	pco->pos.vx = near->x + (((ppco->pos.vx - near->x) << 0x10) >> 0x10);
	pco->pos.vz = near->z + (((ppco->pos.vz - near->z) << 0x10) >> 0x10);

	pco->pos.vy = (ppco->pos.vy << 0x10) >> 0x11;
	pco->yang = ppco->value & 0x3f;
	pco->type = (ppco->value >> 6) | ((ppco->pos.vy & 1) << 10);

	return pco;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawMapPSX(int *comp_val /*$t1*/)
 // line 883, offset 0x0003f6b0
	/* begin block 1 */
		// Start line: 884
		// Start offset: 0x0003F6B0
		// Variables:
	// 		struct CELL_ITERATOR ci; // stack offset -184
	// 		struct PACKED_CELL_OBJECT *ppco; // $s0
	// 		int i; // $s1
	// 		int dir; // $s7
	// 		int cellxpos; // $a0
	// 		int cellzpos; // $a1
	// 		int hloop; // $s4
	// 		int vloop; // $s5
	// 		int camx; // stack offset -112
	// 		int camz; // stack offset -108
	// 		char *PVS_ptr; // stack offset -104
	// 		int tiles_found; // stack offset -100
	// 		int other_models_found; // stack offset -96
	// 		int anim_objs; // $s6
	// 		struct MATRIX mRotStore; // stack offset -160
	// 		int rightcos; // stack offset -92
	// 		int rightsin; // stack offset -88
	// 		int leftcos; // stack offset -84
	// 		int leftsin; // stack offset -80
	// 		int backcos; // stack offset -76
	// 		int backsin; // stack offset -72
	// 		int rightPlane; // stack offset -68
	// 		int leftPlane; // stack offset -64
	// 		int backPlane; // $fp
	// 		unsigned int farClipLimit; // stack offset -60

		/* begin block 1.1 */
			// Start line: 967
			// Start offset: 0x0003F964
			// Variables:
		// 		struct MODEL *model; // $s2

			/* begin block 1.1.1 */
				// Start line: 975
				// Start offset: 0x0003F9B4
				// Variables:
			// 		int model_shape_flags; // $s1

				/* begin block 1.1.1.1 */
					// Start line: 986
					// Start offset: 0x0003FA10
					// Variables:
				// 		struct CELL_OBJECT *cop; // $a2

					/* begin block 1.1.1.1.1 */
						// Start line: 884
						// Start offset: 0x0003FA10
						// Variables:
					// 		struct PACKED_CELL_OBJECT *ppco; // $s0

						/* begin block 1.1.1.1.1.1 */
							// Start line: 884
							// Start offset: 0x0003FA10
							// Variables:
						// 		struct CELL_OBJECT *pco; // $a1
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x0003FAB8
						// End Line: 884
					/* end block 1.1.1.1.1 */
					// End offset: 0x0003FAB8
					// End Line: 884
				/* end block 1.1.1.1 */
				// End offset: 0x0003FAC4
				// End Line: 988

				/* begin block 1.1.1.2 */
					// Start line: 993
					// Start offset: 0x0003FAF4
					// Variables:
				// 		struct CELL_OBJECT *cop; // $a2

					/* begin block 1.1.1.2.1 */
						// Start line: 884
						// Start offset: 0x0003FAF4
						// Variables:
					// 		struct PACKED_CELL_OBJECT *ppco; // $s0

						/* begin block 1.1.1.2.1.1 */
							// Start line: 884
							// Start offset: 0x0003FAF4
							// Variables:
						// 		struct CELL_OBJECT *pco; // $a1
						/* end block 1.1.1.2.1.1 */
						// End offset: 0x0003FB9C
						// End Line: 884
					/* end block 1.1.1.2.1 */
					// End offset: 0x0003FB9C
					// End Line: 884
				/* end block 1.1.1.2 */
				// End offset: 0x0003FB9C
				// End Line: 994

				/* begin block 1.1.1.3 */
					// Start line: 1002
					// Start offset: 0x0003FBE8
					// Variables:
				// 		int yang; // $a1
				/* end block 1.1.1.3 */
				// End offset: 0x0003FCD0
				// End Line: 1010

				/* begin block 1.1.1.4 */
					// Start line: 1018
					// Start offset: 0x0003FD0C
					// Variables:
				// 		struct CELL_OBJECT *cop; // $a2

					/* begin block 1.1.1.4.1 */
						// Start line: 884
						// Start offset: 0x0003FD0C
						// Variables:
					// 		struct PACKED_CELL_OBJECT *ppco; // $s0

						/* begin block 1.1.1.4.1.1 */
							// Start line: 884
							// Start offset: 0x0003FD0C
							// Variables:
						// 		struct CELL_OBJECT *pco; // $a1
						/* end block 1.1.1.4.1.1 */
						// End offset: 0x0003FDB4
						// End Line: 884
					/* end block 1.1.1.4.1 */
					// End offset: 0x0003FDB4
					// End Line: 884
				/* end block 1.1.1.4 */
				// End offset: 0x0003FE00
				// End Line: 1021

				/* begin block 1.1.1.5 */
					// Start line: 1032
					// Start offset: 0x0003FE34
					// Variables:
				// 		struct CELL_OBJECT *cop; // $a2

					/* begin block 1.1.1.5.1 */
						// Start line: 884
						// Start offset: 0x0003FE34
						// Variables:
					// 		struct PACKED_CELL_OBJECT *ppco; // $s0

						/* begin block 1.1.1.5.1.1 */
							// Start line: 884
							// Start offset: 0x0003FE34
							// Variables:
						// 		struct CELL_OBJECT *pco; // $a1
						/* end block 1.1.1.5.1.1 */
						// End offset: 0x0003FEDC
						// End Line: 884
					/* end block 1.1.1.5.1 */
					// End offset: 0x0003FEDC
					// End Line: 884
				/* end block 1.1.1.5 */
				// End offset: 0x0003FF34
				// End Line: 1042
			/* end block 1.1.1 */
			// End offset: 0x0003FF34
			// End Line: 1045
		/* end block 1.1 */
		// End offset: 0x0003FF34
		// End Line: 1046

		/* begin block 1.2 */
			// Start line: 1071
			// Start offset: 0x000400CC
		/* end block 1.2 */
		// End offset: 0x000400D4
		// End Line: 1072

		/* begin block 1.3 */
			// Start line: 1081
			// Start offset: 0x000400E4
		/* end block 1.3 */
		// End offset: 0x0004010C
		// End Line: 1083

		/* begin block 1.4 */
			// Start line: 1089
			// Start offset: 0x00040138
			// Variables:
		// 		struct VECTOR newpos; // stack offset -128
		// 		struct CELL_OBJECT *cop; // $s0
		/* end block 1.4 */
		// End offset: 0x00040138
		// End Line: 1090
	/* end block 1 */
	// End offset: 0x00040218
	// End Line: 1123

	/* begin block 2 */
		// Start line: 1930
	/* end block 2 */
	// End Line: 1931

	/* begin block 3 */
		// Start line: 1961
	/* end block 3 */
	// End Line: 1962

	/* begin block 4 */
		// Start line: 1980
	/* end block 4 */
	// End Line: 1981

// [D]
void DrawMapPSX(int *comp_val)
{
	ushort uVar1;
	CELL_OBJECT *pCVar2;

	uint uVar4;
	PACKED_CELL_OBJECT *ppco;
	CELL_OBJECT **ppCVar6;
	int iVar7;
	PACKED_CELL_OBJECT **ppPVar8;
	uint uVar9;
	int cellx;
	int cellz;
	CELL_OBJECT *cop;
	//undefined4 uVar10;
	long lVar11;
	//undefined4 uVar12;
	long lVar13;
	//undefined4 uVar14;
	long lVar15;
	MODEL *model;
	int iVar19;
	int iVar20;
	uint backPlane;
	CELL_ITERATOR ci;
	MATRIX mRotStore;
	VECTOR newpos;
	int camx;
	int camz;
	char *PVS_ptr;
	int tiles_found;
	int other_models_found;
	int rightcos;
	int rightsin;
	int leftcos;
	int leftsin;
	int backcos;
	int backsin;
	int rightPlane;
	int leftPlane;
	uint farClipLimit;

	int local_34;
	int anim_objs;

	backPlane = 0x1800;	// backPlane
	rightPlane = -0x1800;
	leftPlane = 0x1800;

	iVar7 = (int)camera_angle.vy;
	farClipLimit = 80000;

	uVar9 = iVar7 - FrAng & 0xfff;
	uVar4 = iVar7 + FrAng & 0xfff;
	rightcos = (int)rcossin_tbl[uVar9 * 2 + 1];
	rightsin = (int)rcossin_tbl[uVar9 * 2];

	uVar9 = iVar7 + 0x400U & 0xfff;
	leftcos = (int)rcossin_tbl[uVar4 * 2 + 1];
	leftsin = (int)rcossin_tbl[uVar4 * 2];
	backcos = (int)rcossin_tbl[uVar9 * 2 + 1];
	backsin = (int)rcossin_tbl[uVar9 * 2];

	if (NumPlayers == 2) 
	{
		farClipLimit = farClip2Player;
	}

	tiles_found = 0;
	treecount = 0;
	numSpritesFound = 0;
	goFaster = goFaster ^ fasterToggle;
	current_object_computed_value = *comp_val;
	other_models_found = 0;

	anim_objs = 0;

	if (setupYet == 0)
	{
		SetupDrawMapPSX();
		setupYet = 0;
	}

	camz = current_cell_z;
	camx = current_cell_x;

	ClearCopUsage();

	iVar20 = 0;
	iVar19 = 0;
	PVS_ptr = CurrentPVS + 220;
	uVar4 = 0;

	if (NumPlayers == 2) 
		uVar9 = goFaster & 31 | 1;
	else
		uVar9 = goFaster & 31;

	local_34 = (gDrawDistance >> uVar9) - 1;		// [A]

	do 
	{
		while (true)
		{
			while (true)
			{
				if (local_34 == -1) 
				{
					if (numSpritesFound != 0)
					{
						DrawSprites(numSpritesFound);
					}

					if (tiles_found != 0) 
					{
						DrawTILES(tiles_found);
					}

					if (other_models_found != 0)
					{
						SetupPlaneColours(combointensity);
						DrawAllBuildings(model_object_ptrs, other_models_found, current);
					}

					while (anim_objs > 0)
					{
						anim_objs--;
						cop = anim_obj_buffer[anim_objs];

						newpos.vx = cop->pos.vx - camera_position.vx;
						newpos.vy = cop->pos.vy - camera_position.vy;
						newpos.vz = cop->pos.vz - camera_position.vz;
						Apply_Inv_CameraMatrix(&newpos);

						gte_SetRotMatrix(&matrixtable[cop->yang]);
						DrawAnimatingObject(modelpointers[cop->type], cop, &newpos);
					}

					buildingsFound = other_models_found;

					return;
				}

				cellx = iVar19;
				if (iVar19 < 0)
					cellx = -iVar19;

				cellz = iVar20;

				if (iVar20 < 0) 
					cellz = -iVar20;

				local_34--;

				if (cellx + cellz < 16) // < 16)
				{
					cellx = camx + iVar19;
					cellz = camz + iVar20;

					if( rightPlane < 0 && 
						leftPlane > 0 && 
						backPlane < farClipLimit &&  // check planes
						cellx > -1 && cellx < cells_across &&							// check cell ranges
						cellz > -1 && cellz < cells_down &&
						PVS_ptr[iVar19]) // check PVS table		// [A] please enable after PVSDecode will work properly
					{
						ppco = GetFirstPackedCop(cellx, cellz, &ci, 1);

						while (ppco != NULL)
						{
							model = modelpointers[(ppco->value >> 6) | ((uint)(ppco->pos).vy & 1) << 10];

							if (FrustrumCheck16(ppco, model->bounding_sphere) != -1)
							{
								uVar1 = model->shape_flags;

								if ((uVar1 & 0x4000) == 0)
								{
									uVar9 = (uint)ppco->value & 0x3f;

									if ((ppco->value & 0xf) != 0)
									{
										if ((int)CompoundMatrix[uVar9].computed != current_object_computed_value)
										{
											CompoundMatrix[uVar9].computed = (short)current_object_computed_value;

											gte_ReadRotMatrix(&mRotStore);

											gte_sttr(mRotStore.t);

											MulMatrix0(&inv_camera_matrix, (MATRIX *)(matrixtable + uVar9), (MATRIX *)(CompoundMatrix + uVar9));

											gte_SetRotMatrix(&mRotStore);
											//TRX = pMVar3->t[0];
											//TRY = pMVar3->t[1]; ??
											//TRZ = pMVar3->t[2];
										}
									}

									if (((uVar1 & 0x480) == 0) && ((model->flags2 & 0xc000) == 0))
									{
										cop = UnpackCellObject(ppco, &ci.nearCell);


										if (((model->flags2 & 1) != 0) && (anim_objs < 20))
										{
											anim_obj_buffer[anim_objs++] = cop;
										}

										if (other_models_found < 192)
											model_object_ptrs[other_models_found++] = cop;
									}
									else
									{
										if (((model->flags2 & 0x80) != 0) && (alleycount++, alleycount == 13))
										{
											cop = UnpackCellObject(ppco, &ci.nearCell);
											ground_debris[groundDebrisIndex++] = *cop;
											groundDebrisIndex = groundDebrisIndex % 16;

											alleycount = 0;
										}

										if (tiles_found < 0x100)
										{
											*(PACKED_CELL_OBJECT **)(tile_overflow_buffer + tiles_found) = ppco;
											tiles_found++;
										}
									}
								}
								else
								{
									if (numSpritesFound < 75)
										spriteList[numSpritesFound++] = ppco;

									if (((model->flags2 & 1) != 0) && (anim_objs < 20))
									{
										cop = UnpackCellObject(ppco, &ci.nearCell);

										anim_obj_buffer[anim_objs++] = cop;
									}

									if (((model->flags2 & 0x2000) != 0) && (uVar9 = treecount & 0xf, treecount++, uVar9 == 0))
									{
										cop = UnpackCellObject(ppco, &ci.nearCell);
										ground_debris[groundDebrisIndex++] = *cop;
										groundDebrisIndex = groundDebrisIndex % 16;
									}
								}
							}

							ppco = GetNextPackedCop(&ci);
						}
					}
				}

				if (uVar4 != 1) 
					break;

				leftPlane += leftsin;
				backPlane += backsin;
				rightPlane += rightsin;
				iVar20++;

				PVS_ptr += pvs_square;

				if (iVar19 == iVar20)
					uVar4 = 2;
			}

			if (1 < uVar4)
				break;

			if (uVar4 == 0)
			{
				leftPlane += leftcos;
				backPlane += backcos;
				rightPlane += rightcos;

				iVar19++;
				
				if (iVar19 + iVar20 == 1) 
					uVar4 = 1;
			}
			else
			{
			LAB_0004004c:
				leftPlane -= leftsin;
				backPlane -= backsin;
				rightPlane -= rightsin;
				iVar20--;
				PVS_ptr -= pvs_square;

				if (iVar19 == iVar20)
					uVar4 = 0;
			}
		}

		if (uVar4 != 2)
			goto LAB_0004004c;

		iVar19--;
		leftPlane -= leftcos;
		backPlane -= backcos;
		rightPlane -= rightcos;

		if (iVar19 + iVar20 == 0) 
			uVar4 = 3;
	} while (true);
}

// decompiled code
// original method signature: 
// void /*$ra*/ SetupPlaneColours(unsigned long ambient /*$a3*/)
 // line 1125, offset 0x00040218
	/* begin block 1 */
		// Start line: 1126
		// Start offset: 0x00040218

		/* begin block 1.1 */
			// Start line: 1140
			// Start offset: 0x000402B4
			// Variables:
		// 		unsigned long r; // $t4
		// 		unsigned long g; // $t2
		// 		unsigned long b; // $a0
		/* end block 1.1 */
		// End offset: 0x000402B4
		// End Line: 1140
	/* end block 1 */
	// End offset: 0x00040408
	// End Line: 1159

	/* begin block 2 */
		// Start line: 2705
	/* end block 2 */
	// End Line: 2706

	/* begin block 3 */
		// Start line: 2708
	/* end block 3 */
	// End Line: 2709

	/* begin block 4 */
		// Start line: 2709
	/* end block 4 */
	// End Line: 2710

// [D]
void SetupPlaneColours(ulong ambient)
{
	unsigned long r;
	unsigned long g;
	unsigned long b;

	if ((gWeather - 1U > 1) && gTimeOfDay != 0 && gTimeOfDay != 2) 
	{
		if (gTimeOfDay == 1) 
		{
			b = ambient & 0xff;
			g = ambient >> 8 & 0xff;
			r = ambient >> 0x10 & 0xff;
			planeColours[1] = (r * 0x78 >> 7) << 0x10 | (g * 0x78 >> 7) << 8 | b * 0x78 >> 7;
			planeColours[2] = (r * 0x67 >> 7) << 0x10 | (g * 0x67 >> 7) << 8 | b * 0x67 >> 7;
			planeColours[3] = (r * 0xd >> 5) << 0x10 | (g * 0xd >> 5) << 8 | b * 0xd >> 5;
			planeColours[0] = r << 0x10 | g << 8 | b;
			planeColours[4] = (r * 3 >> 3) << 0x10 | (g * 3 >> 3) << 8 | b * 3 >> 3;
			planeColours[5] = planeColours[3];
			planeColours[6] = planeColours[2];
			planeColours[7] = planeColours[1];
			return;
		}

		planeColours[0] = ambient;
		planeColours[1] = ambient;
		planeColours[2] = ambient;
		planeColours[3] = ambient;
		planeColours[4] = ambient;
		planeColours[5] = ambient;
		planeColours[6] = ambient;
		planeColours[7] = ambient;
		return;
	}

	planeColours[0] = ambient;
	planeColours[1] = ambient + 0x10101;
	planeColours[2] = ambient + 0x30303;
	planeColours[3] = ambient + 0x80808;
	planeColours[4] = ambient + 0xa0a0a;
	planeColours[5] = ambient + 0x80808;
	planeColours[6] = ambient + 0x30303;
	planeColours[7] = ambient + 0x10101;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDrawMapPSX()
 // line 1162, offset 0x00040408
	/* begin block 1 */
		// Start line: 1165
		// Start offset: 0x00040408

		/* begin block 1.1 */
			// Start line: 1166
			// Start offset: 0x00040468
			// Variables:
		// 		int region_x1; // $t0
		// 		int region_z1; // $a0
		// 		int current_barrel_region_x1; // $v0
		// 		int current_barrel_region_z1; // $a0
		/* end block 1.1 */
		// End offset: 0x0004048C
		// End Line: 1178

		/* begin block 1.2 */
			// Start line: 1178
			// Start offset: 0x0004048C
			// Variables:
		// 		int theta; // $s2
		/* end block 1.2 */
		// End offset: 0x00040500
		// End Line: 1196
	/* end block 1 */
	// End offset: 0x00040534
	// End Line: 1200

	/* begin block 2 */
		// Start line: 2788
	/* end block 2 */
	// End Line: 2789

	/* begin block 3 */
		// Start line: 2792
	/* end block 3 */
	// End Line: 2793

	/* begin block 4 */
		// Start line: 2794
	/* end block 4 */
	// End Line: 2795

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void SetupDrawMapPSX(void)
{
	int region_x1; 
	int region_z1;
	int current_barrel_region_x1;
	int current_barrel_region_z1;

	int theta;

	current_cell_x = (camera_position.vx + units_across_halved) / 2048;// cell_header.cell_size
	current_cell_z = (camera_position.vz + units_down_halved) / 2048;

	region_x1 = current_cell_x / 32; // cell_header.region_size;
	region_z1 = current_cell_z / 32; // cell_header.region_size;

	current_barrel_region_x1 = (region_x1 & 1);
	current_barrel_region_z1 = (region_z1 & 1);

	GetPVSRegionCell2(
		current_barrel_region_x1 + current_barrel_region_z1 * 2,
		region_x1 + region_z1 * cells_across / 32,
		(current_cell_z % 32) * 32 + (current_cell_x % 32), 
		CurrentPVS);

	for (theta = 0; theta < 64; theta++)
		MulMatrix0(&inv_camera_matrix, (MATRIX*)&matrixtable[theta], (MATRIX*)&CompoundMatrix[theta]);

	InitFrustrumMatrix();
	SetFrustrumMatrix();

	setupYet = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitFrustrumMatrix()
 // line 1209, offset 0x00040534
	/* begin block 1 */
		// Start line: 2912
	/* end block 1 */
	// End Line: 2913

	/* begin block 2 */
		// Start line: 2922
	/* end block 2 */
	// End Line: 2923

	/* begin block 3 */
		// Start line: 2923
	/* end block 3 */
	// End Line: 2924

/* WARNING: Unknown calling convention yet parameter storage is locked */

MATRIX frustrum_matrix;

// [D]
void InitFrustrumMatrix(void)
{
    int iVar1;
    uint a;
    
    frustrum_matrix.m[0][1] = 0;
    frustrum_matrix.m[0][0] = rcossin_tbl[(-(int)camera_angle.vy & 0xfffU) * 2];
    iVar1 = rcos(-(int)camera_angle.vy);
    frustrum_matrix.m[0][2] = (short)iVar1;
    frustrum_matrix.m[1][1] = 0;
    a = (FrAng + -0x400) - (int)camera_angle.vy;
    frustrum_matrix.m[1][0] = rcossin_tbl[(a & 0xfff) * 2];
    iVar1 = rcos(a);
    frustrum_matrix.m[1][2] = (short)iVar1;
    frustrum_matrix.m[2][1] = 0;
    a = -(FrAng + -0x400) - (int)camera_angle.vy;
    frustrum_matrix.m[2][0] = rcossin_tbl[(a & 0xfff) * 2];
    iVar1 = rcos(a);
    frustrum_matrix.m[2][2] = (short)iVar1;
    frustrum_matrix.t[0] = -0x50;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetFrustrumMatrix()
 // line 1219, offset 0x000417a4
	/* begin block 1 */
		// Start line: 4751
	/* end block 1 */
	// End Line: 4752

	/* begin block 2 */
		// Start line: 2438
	/* end block 2 */
	// End Line: 2439

	/* begin block 3 */
		// Start line: 4752
	/* end block 3 */
	// End Line: 4753

/* WARNING: Unknown calling convention yet parameter storage is locked */

// TODO: INLINE_C or GTEMAC

// [D]
void SetFrustrumMatrix(void)
{
	gte_SetLightMatrix(&frustrum_matrix);
}

// decompiled code
// original method signature: 
// void /*$ra*/ Set_Inv_CameraMatrix()
 // line 1224, offset 0x000417dc
	/* begin block 1 */
		// Start line: 4761
	/* end block 1 */
	// End Line: 4762

	/* begin block 2 */
		// Start line: 4762
	/* end block 2 */
	// End Line: 4763

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void Set_Inv_CameraMatrix(void)
{
	gte_SetColorMatrix(&inv_camera_matrix);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CalcObjectRotationMatrices()
 // line 1324, offset 0x00041814
	/* begin block 1 */
		// Start line: 1326
		// Start offset: 0x00041814
		// Variables:
	// 		int i; // $s1
	// 		int j; // $a0
	// 		struct SVECTOR ang; // stack offset -56
	// 		struct MATRIX mat; // stack offset -48
	/* end block 1 */
	// End offset: 0x000418BC
	// End Line: 1341

	/* begin block 2 */
		// Start line: 4961
	/* end block 2 */
	// End Line: 4962

	/* begin block 3 */
		// Start line: 4962
	/* end block 3 */
	// End Line: 4963

	/* begin block 4 */
		// Start line: 4968
	/* end block 4 */
	// End Line: 4969

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [A]
void CalcObjectRotationMatrices(void)
{
	SVECTOR ang;
	MATRIX mat;

	ang.vz = 0;
	ang.vy = 0;
	ang.vx = 0;

	for (int i = 0; i < 64; i++)
	{
		RotMatrix(&ang, &mat);

		for (int j = 0; j < 3; j++)
		{
			matrixtable[i].m[j][0] = mat.m[j][0];
			matrixtable[i].m[j][1] = mat.m[j][1];
			matrixtable[i].m[j][2] = mat.m[j][2];
		}

		ang.vy = ang.vy + 64;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlotMDL_less_than_128(struct MODEL *model /*$a0*/)
 // line 1344, offset 0x000418bc
	/* begin block 1 */
		// Start line: 5018
	/* end block 1 */
	// End Line: 5019

	/* begin block 2 */
		// Start line: 5022
	/* end block 2 */
	// End Line: 5023

	/* begin block 3 */
		// Start line: 5023
	/* end block 3 */
	// End Line: 5024

// [D]
void PlotMDL_less_than_128(MODEL *model)
{
	RenderModel(model, (MATRIX *)0x0, (VECTOR *)0x0, 0, 0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessMapLump(char *lump_ptr /*$v0*/, int lump_size /*$a1*/)
 // line 1425, offset 0x00040608
	/* begin block 1 */
		// Start line: 1426
		// Start offset: 0x00040608
		// Variables:
	// 		char *cellptr; // $s0
	// 		int cell_size; // $a3
	// 		int region_size; // $t0
	/* end block 1 */
	// End offset: 0x000407D8
	// End Line: 1478

	/* begin block 2 */
		// Start line: 3346
	/* end block 2 */
	// End Line: 3347

	/* begin block 3 */
		// Start line: 3357
	/* end block 3 */
	// End Line: 3358


// [D]
void ProcessMapLump(char *lump_ptr, int lump_size)
{
#ifdef PSX
	cells_across = *(int *)lump_ptr;
	cells_down = *(int *)(lump_ptr + 4);
	num_regions = *(int *)(lump_ptr + 0xc);
	view_dist = 10;

	pvs_square = 21;
	pvs_square_sq = 21*21;

	units_across_halved = cells_across / 2 << 0xb;
	units_down_halved = cells_down / 2 << 0xb;
	regions_across = cells_across;

	if (cells_across < 0) {
		regions_across = cells_across + 0x1f;
	}
	regions_across = regions_across >> 5;
	regions_down = cells_down;
	if (cells_down < 0) {
		regions_down = cells_down + 0x1f;
	}
	regions_down = regions_down >> 5;
	if (0x400 < num_regions) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	num_straddlers = *(int *)(lump_ptr + 0x2c);
	if (*(int *)(lump_ptr + 8) != 0x800) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	if (*(int *)(lump_ptr + 0x10) != 0x20) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	InitCellData();
	memcpy(cell_objects, lump_ptr + 0x30, num_straddlers << 3);

#else

	memcpy(&cell_header, lump_ptr, sizeof(OUT_CELL_FILE_HEADER));

	cells_across = cell_header.cells_across;
	cells_down = cell_header.cells_down;
	num_regions = cell_header.num_regions;

	view_dist = 10;
	pvs_square = 21;
	pvs_square_sq = 21 * 21;

	units_across_halved = cells_across / 2 * cell_header.cell_size;
	units_down_halved = cells_down / 2 * cell_header.cell_size;

	regions_across = cells_across / cell_header.region_size;
	regions_down = cells_down / cell_header.region_size;

	lump_ptr += sizeof(OUT_CELL_FILE_HEADER);

	num_straddlers = *(int*)lump_ptr;

	InitCellData();
	memcpy(cell_objects, lump_ptr + 4, num_straddlers * sizeof(PACKED_CELL_OBJECT));
#endif
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawAllTheCars(int view /*$s6*/)
 // line 1711, offset 0x000407d8
	/* begin block 1 */
		// Start line: 1712
		// Start offset: 0x000407D8
		// Variables:
	// 		int loop; // $s0
	// 		int x; // $s2
	// 		int z; // $s1
	// 		int xd; // $a0
	// 		int zd; // $v1
	// 		struct _CAR_DATA (*cars_to_draw[20]); // stack offset -112
	// 		int num_cars_to_draw; // $s4
	// 		static int car_distance[20]; // offset 0x0
	// 		static int temp; // offset 0x0

		/* begin block 1.1 */
			// Start line: 1712
			// Start offset: 0x000407D8
			// Variables:
		// 		struct _CAR_DATA *lcp; // $s0

			/* begin block 1.1.1 */
				// Start line: 1738
				// Start offset: 0x00040860
				// Variables:
			// 		int dist; // $v0
			/* end block 1.1.1 */
			// End offset: 0x000408E0
			// End Line: 1748
		/* end block 1.1 */
		// End offset: 0x000408F0
		// End Line: 1751

		/* begin block 1.2 */
			// Start line: 1757
			// Start offset: 0x000408F8
			// Variables:
		// 		int i; // $a0

			/* begin block 1.2.1 */
				// Start line: 1762
				// Start offset: 0x00040920
				// Variables:
			// 		struct _CAR_DATA *car; // $t4
			// 		int dist; // $t0
			// 		int j; // $a3
			/* end block 1.2.1 */
			// End offset: 0x000409A0
			// End Line: 1771
		/* end block 1.2 */
		// End offset: 0x000409C0
		// End Line: 1774

		/* begin block 1.3 */
			// Start line: 1790
			// Start offset: 0x000409E4
			// Variables:
		// 		int spacefree; // $a1
		/* end block 1.3 */
		// End offset: 0x00040A2C
		// End Line: 1798
	/* end block 1 */
	// End offset: 0x00040A68
	// End Line: 1824

	/* begin block 2 */
		// Start line: 3945
	/* end block 2 */
	// End Line: 3946

	/* begin block 3 */
		// Start line: 3970
	/* end block 3 */
	// End Line: 3971

	/* begin block 4 */
		// Start line: 3974
	/* end block 4 */
	// End Line: 3975

int gForceLowDetailCars = 0;
int num_cars_drawn = 0;

// [A]
void DrawAllTheCars(int view)
{
	static int car_distance[20]; // offset 0x0
	static int temp; // offset 0x0

	long lVar1;
	long lVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int *puVar6;
	_CAR_DATA **pp_Var7;
	_CAR_DATA *p_Var8;
	int iVar9;
	int *piVar10;
	int iVar11;
	_CAR_DATA *cars_to_draw[20];

	lVar2 = camera_position.vz;
	lVar1 = camera_position.vx;
	p_Var8 = car_data + 18;
	num_cars_drawn = 0;
	iVar11 = 0;


	piVar10 = car_distance;
	iVar9 = iVar11;
	do {
		iVar11 = iVar9;

		if ((p_Var8->controlType != 0) && PositionVisible((VECTOR *)p_Var8->hd.where.t))
		{
			// XZ distance estimation
			iVar3 = p_Var8->hd.where.t[0];
			iVar5 = lVar1 - iVar3;

			if (iVar5 < 0) 
				iVar5 = iVar3 - lVar1;

			iVar3 = p_Var8->hd.where.t[2];
			iVar4 = lVar2 - iVar3;

			if (iVar4 < 0) 
				iVar4 = iVar3 - lVar2;

			if (iVar5 < iVar4) 
				iVar3 = iVar4 + iVar5 / 2;
			else
				iVar3 = iVar5 + iVar4 / 2;

			if (iVar3 < 16000) 
			{
				*piVar10 = iVar5 + iVar4;
				piVar10 = piVar10 + 1;
				iVar11 = iVar9 + 1;
				cars_to_draw[iVar9] = p_Var8;
			}
		}

		p_Var8 = p_Var8 + -1;
		iVar9 = iVar11;

	} while (p_Var8 >= car_data);

	if (iVar11 != 0) 
	{
		gForceLowDetailCars = 0;

		if (1 < iVar11) 
		{
			iVar9 = 1;
			do {
				p_Var8 = cars_to_draw[iVar9];
				iVar3 = car_distance[iVar9];

				iVar5 = iVar9 + 1;

				if (iVar9 != 0) 
				{
					if (iVar3 < car_distance[iVar9 + -1])
					{
						pp_Var7 = cars_to_draw + iVar9;
						puVar6 = &car_distance[iVar9];
						iVar4 = iVar9 + -1;

						do {
							iVar9 = iVar4;
							*puVar6 = puVar6[-1];
							*pp_Var7 = pp_Var7[-1];
							pp_Var7 = pp_Var7 + -1;
							if (iVar9 == 0) break;
							piVar10 = puVar6 + -2;
							puVar6 = puVar6 + -1;
							iVar4 = iVar9 + -1;
						} while (iVar3 < *piVar10);
					}
				}

				cars_to_draw[iVar9] = p_Var8;
				car_distance[iVar9] = iVar3;
				iVar9 = iVar5;

			} while (iVar5 < iVar11);
		}

		iVar9 = 0;

		if (0 < iVar11)
		{
			iVar3 = (iVar11 + -1) * 2000;

			do {
				// Don't exceed draw buffers
				if ((int)(current->primtab + (-3000 - (int)(current->primptr-0x1a180))) < 5800)
					return;

				// try reducing detail level
				// this looks really ugly
				if ((int)(current->primtab + (-3000 - (int)(current->primptr-0x1a180)) + -iVar3) < 5800) 
					gForceLowDetailCars = 1;

				if (cars_to_draw[iVar9]->controlType == 1)
					gForceLowDetailCars = 0;

				DrawCar(cars_to_draw[iVar9], view);

				iVar9 = iVar9 + 1;
				iVar3 = iVar3 + -2000;

			} while (iVar9 < iVar11);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlotBuildingModelSubdivNxN(struct MODEL *model /*$t0*/, int rot /*stack 4*/, struct _pct *pc /*$s2*/, int n /*stack 12*/)
 // line 1857, offset 0x00040a90
	/* begin block 1 */
		// Start line: 1858
		// Start offset: 0x00040A90
		// Variables:
	// 		struct SVECTOR *verts; // $s4
	// 		struct PL_POLYFT4 *polys; // $s1
	// 		int i; // $s7
	// 		int asdf; // $fp

		/* begin block 1.1 */
			// Start line: 1876
			// Start offset: 0x00040B40
			// Variables:
		// 		unsigned long word0; // $s0

			/* begin block 1.1.1 */
				// Start line: 1886
				// Start offset: 0x00040B9C
				// Variables:
			// 		int Z; // stack offset -48
			// 		unsigned int vidx; // $s3

				/* begin block 1.1.1.1 */
					// Start line: 1896
					// Start offset: 0x00040BD0
					// Variables:
				// 		unsigned long th; // $v1
				/* end block 1.1.1.1 */
				// End offset: 0x00040C10
				// End Line: 1902

				/* begin block 1.1.1.2 */
					// Start line: 1940
					// Start offset: 0x00040E30
					// Variables:
				// 		int diff; // $a1
				// 		int min; // $a2

					/* begin block 1.1.1.2.1 */
						// Start line: 1945
						// Start offset: 0x00040E30
						// Variables:
					// 		int max; // $v1
					/* end block 1.1.1.2.1 */
					// End offset: 0x00040EA4
					// End Line: 1949

					/* begin block 1.1.1.2.2 */
						// Start line: 1970
						// Start offset: 0x00040F10
						// Variables:
					// 		int w; // $s0
					/* end block 1.1.1.2.2 */
					// End offset: 0x00040F3C
					// End Line: 1973

					/* begin block 1.1.1.2.3 */
						// Start line: 1983
						// Start offset: 0x00041060
						// Variables:
					// 		struct POLY_FT4 *prims; // $t2
					// 		int uv0; // $v1
					// 		int uv1; // $a2
					// 		int uv2; // $t3
					// 		int uv3; // $t1

						/* begin block 1.1.1.2.3.1 */
							// Start line: 1994
							// Start offset: 0x000410A8
							// Variables:
						// 		unsigned int r; // $a2
						/* end block 1.1.1.2.3.1 */
						// End offset: 0x000410A8
						// End Line: 1994

						/* begin block 1.1.1.2.3.2 */
							// Start line: 1994
							// Start offset: 0x000410A8
							// Variables:
						// 		int r2; // $v1
						/* end block 1.1.1.2.3.2 */
						// End offset: 0x000410A8
						// End Line: 1994
					/* end block 1.1.1.2.3 */
					// End offset: 0x00041140
					// End Line: 2019
				/* end block 1.1.1.2 */
				// End offset: 0x00041140
				// End Line: 2021
			/* end block 1.1.1 */
			// End offset: 0x00041158
			// End Line: 2026
		/* end block 1.1 */
		// End offset: 0x00041178
		// End Line: 2033
	/* end block 1 */
	// End offset: 0x000411F4
	// End Line: 2040

	/* begin block 2 */
		// Start line: 4392
	/* end block 2 */
	// End Line: 4393

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void PlotBuildingModelSubdivNxN(MODEL *model, int rot, _pct *pc, int n)
{
	unsigned char uVar1;
	UV_INFO UVar2;
	UV_INFO UVar3;
	int in_zero;
	int in_at;
	int iVar4;
	SVECTOR *pSVar5;
	int *puVar6;
	uint uVar7;
	ulong uVar8;
	SVECTOR *local_v1_404;
	int iVar9;
	SVECTOR *pSVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	uint uVar14;
	uint uVar15;
	uint uVar16;
	int uVar17;
	POLY_FT4 *local_t2_1500;
	uint uVar18;
	PL_POLYFT4 *polys;
	ushort *vidx;
	SVECTOR *verts;
	uint uVar19;
	uint uVar20;
	int Z;

	verts = (SVECTOR *)model->vertices;
	uVar20 = 0xffffffff;
	pc->ot = pc->current->ot;
	pc->primptr = pc->current->primptr;

	if ((pc->flags & 1U) != 0) {
		combointensity = combointensity | 0x2000000;
		in_at = 0xb0000;
	}

	iVar4 = rot >> 3;
	uVar19 = (uint)model->num_polys;
	polys = (PL_POLYFT4 *)model->poly_block;
	do {
		while (true)
		{
			uVar19 = uVar19 - 1;
			if (uVar19 == 0xffffffff)
			{
				pc->current->primptr = pc->primptr;
				if ((pc->flags & 1U) != 0)
					combointensity = combointensity & 0xfdffffff;

				return;
			}
			uVar18 = *(uint *)polys;

			if ((uVar18 & 1) == 0) {
				uVar1 = (polys->uv2).v;
				(polys->uv3).u = (polys->uv2).u;
				(polys->uv3).v = uVar1;
				polys->id = polys->id ^ 1;
				uVar18 = *(uint *)polys;
				polys->v3 = polys->v2;
			}

			uVar7 = uVar18 & 0x1f;

			if ((uVar7 == 0xb) || (uVar7 == 0x15))
				break;

			polys = (PL_POLYFT4 *)(&polys->id + pc->polySizes[uVar7]);
		}
		vidx = *(ushort **)&polys->v0;
		uVar8 = uVar18 >> 0x18;

		if (uVar7 == 0x15)
		{
			pc->colour = combointensity & 0x2ffffffU | 0x2c000000;
		}
		else
		{
			if ((uVar8 & 0x80) == 0)
			{
				rot = (int)vidx;
				uVar8 = normalIndex(verts, (uint)vidx);
				polys->th = (unsigned char)uVar8;
			}

			pc->colour = pc->f4colourTable[iVar4 * 4 - uVar8 & 0x1f];
		}

		pSVar10 = verts + ((uint)vidx & 0xff);
		local_v1_404 = (SVECTOR *)((int)&verts->vx + ((uint)vidx >> 5 & 0x7f8));
		pSVar5 = verts + ((uint)vidx >> 0x18);
		puVar6 = (int*)((int)&verts->vx + ((uint)vidx >> 0xd & 0x7f8));

		gte_ldv3(pSVar10, local_v1_404, pSVar5);
		gte_rtpt();

		if (((uVar20 ^ uVar18) & 0xffff00) != 0)
		{
			uVar20 = uVar18 >> 8 & 0xff;
			rot = (int)(*pc->ptexture_pages + uVar20);

			pc->tpage = (uint)*(ushort *)rot << 0x10;

			if ((pc->flags & 16U) == 0) // [A] custom palette flag
				pc->clut = (uint)*(ushort *)((int)*pc->ptexture_cluts + (uVar18 >> 0xf & 0x1fe) + uVar20 * 0x40) << 0x10;

			uVar20 = uVar18;
		}

		gte_nclip();

		uint DAT_1f800208;
		uint DAT_1f80020c;
		uint DAT_1f800210;

		gte_stsxy3(&DAT_1f800208, &DAT_1f80020c, &DAT_1f800210);

		//if (((0x13f < DAT_1f800208) && (0x13f < DAT_1f80020c)) && (0x13f < DAT_1f800210))
		//{
		//	if (DAT_1f80020c << 0x10 < 0)
		//	{
		//		DAT_1f800208 = DAT_1f800208 ^ 1;
		//	}
		//	if (DAT_1f800208 != 0)
		//		goto LAB_00040d6c;

		//	if (DAT_1f800210 << 0x10 < 0)
		//	{
		//		if (DAT_1f80020c != 1)
		//			goto LAB_00040d6c;
		//	}
		//	else
		//	{
		//		if (DAT_1f80020c != 0)
		//			goto LAB_00040d6c;
		//	}

		//	goto LAB_00041140;
		//}

	LAB_00040d6c:
		ushort DAT_1f80020a = (ushort)((uint)DAT_1f800208 >> 0x10);
		ushort DAT_1f80020e;

		//if((DAT_1f80020a < 0x100) || (DAT_1f80020e = (ushort)((uint)DAT_1f80020c >> 0x10), DAT_1f80020e < 0x100)) 
		{
		LAB_00040e34:

			gte_stsz3(&pc->scribble[0], &pc->scribble[1], &pc->scribble[2]);

			iVar13 = pc->scribble[1];
			iVar11 = pc->scribble[2];
			if (iVar13 < pc->scribble[2])
				iVar11 = iVar13;

			iVar12 = pc->scribble[0];
			if (iVar12 < iVar11)
				iVar11 = iVar12;

			iVar9 = pc->scribble[2];
			if (pc->scribble[2] < iVar13)
				iVar9 = iVar13;

			rot = iVar9 - iVar11;
			if (iVar9 < iVar12)
				rot = iVar12 - iVar11;

			gte_stopz(&iVar13);
			Z = iVar13;

			if (((pc->flags & 6U) != 0) && (Z = 1, (pc->flags & 4U) == 0))
				Z = -iVar13;

			if (Z > 0)
			{
				if ((n == 0) || (rot << 2 <= iVar11 + -0xfa))
				{					
					local_t2_1500 = (POLY_FT4 *)pc->primptr;

					gte_ldv0(puVar6);

					gte_rtps();
					gte_avsz4();

					UVar2 = polys->uv3;

					gte_stotz(&iVar11);

					rot = 0xff0000;
					if (0 < iVar11)
					{
						rot = 0xffffff;
						UVar3 = polys->uv2;
						uVar14 = *(uint *)&polys->uv0;
						uVar15 = pc->clut;
						uVar16 = pc->tpage;
						uVar18 = pc->ot[iVar11 >> 1];

						setPolyFT4(local_t2_1500);
						addPrim(pc->ot + (iVar11 >> 1), local_t2_1500);

						//pc->ot[iVar11 >> 1] = (uint)local_t2_1500 & 0xffffff;

						//local_t2_1500->tag = uVar18 & 0xffffff | 0x9000000;

						uVar17 = DAT_1f800208;
						*(uint *)&local_t2_1500->u0 = uVar14 & 0xffff | uVar15;
						*(uint *)&local_t2_1500->x0 = uVar17;

						gte_stsxy3(&local_t2_1500->x1, &local_t2_1500->x2, &local_t2_1500->x3);
						*(uint *)&local_t2_1500->u1 = uVar14 >> 0x10 | uVar16;
						*(uint *)&local_t2_1500->u2 = (uint)(ushort)&UVar2;
						*(uint *)&local_t2_1500->u3 = (uint)(ushort)&UVar3;

						local_t2_1500->u0 = polys->uv0.u;
						local_t2_1500->v0 = polys->uv0.v;

						local_t2_1500->u1 = polys->uv1.u;
						local_t2_1500->v1 = polys->uv1.v;

						local_t2_1500->u2 = polys->uv3.u;
						local_t2_1500->v2 = polys->uv3.v;

						local_t2_1500->u3 = polys->uv2.u;
						local_t2_1500->v3 = polys->uv2.v;

						*(ulong *)&local_t2_1500->r0 = pc->colour;

						pc->primptr = (char*)(local_t2_1500 + 1);
					}
				}
				else
				{
					SVECTOR* v0 = pSVar10;
					SVECTOR* v1 = local_v1_404;
					SVECTOR* v2 = pSVar5;
					SVECTOR* v3 = (SVECTOR*)puVar6;

					copyVector(&MVERTEX_ARRAY_1f800228[0][0], v0);
					MVERTEX_ARRAY_1f800228[0][0].uv.val = *(ushort*)&polys->uv0;

					copyVector(&MVERTEX_ARRAY_1f800228[0][1], v1);
					MVERTEX_ARRAY_1f800228[0][1].uv.val = *(ushort*)&polys->uv1;

					copyVector(&MVERTEX_ARRAY_1f800228[0][2], v2);
					MVERTEX_ARRAY_1f800228[0][2].uv.val = *(ushort*)&polys->uv3;

					copyVector(&MVERTEX_ARRAY_1f800228[0][3], v3);
					MVERTEX_ARRAY_1f800228[0][3].uv.val = *(ushort*)&polys->uv2;

					makeMesh((MVERTEX(*)[5][5])MVERTEX_ARRAY_1f800228, rot, rot);
					drawMesh((MVERTEX(*)[5][5])MVERTEX_ARRAY_1f800228, rot, rot, pc);

					/*
					iVar13 = rot << 1;
					rot = n;
					if ((n == 1) && (rot = (int)(ushort *)0x2, iVar11 + -0x96 < iVar13))
						rot = 0x4;
					MVERTEX_ARRAY_1f800228[0]._0_4_ = *(undefined4 *)(verts + ((uint)vidx & 0xff));
					MVERTEX_ARRAY_1f800228[0]._4_4_ =
						*(uint *)&verts[(uint)vidx & 0xff].vz & 0xffff |
						(uint)(ushort)local_s1_1728->uv0 << 0x10;
					uVar17 = *(undefined4 *)&verts[(uint)vidx >> 8 & 0xff].vz;
					*(undefined4 *)(MVERTEX_ARRAY_1f800228 + rot) =
						*(undefined4 *)(verts + ((uint)vidx >> 8 & 0xff));
					*(undefined4 *)&MVERTEX_ARRAY_1f800228[rot].vz = uVar17;
					*(UV_INFO *)&MVERTEX_ARRAY_1f800228[rot].uv = local_s1_1728->uv1;
					uVar17 = *(undefined4 *)&verts[(uint)vidx >> 0x18].vz;
					*(undefined4 *)(MVERTEX_ARRAY_1f800228 + rot * 5) =
						*(undefined4 *)(verts + ((uint)vidx >> 0x18));
					*(undefined4 *)&MVERTEX_ARRAY_1f800228[rot * 5].vz = uVar17;
					puVar6 = (undefined4 *)((int)&verts->vx + ((uint)vidx >> 0xd & 0x7f8));
					*(UV_INFO *)&MVERTEX_ARRAY_1f800228[rot * 5].uv = local_s1_1728->uv3;
					uVar17 = puVar6[1];
					*(undefined4 *)(MVERTEX_ARRAY_1f800228 + rot * 6) = *puVar6;
					*(undefined4 *)&MVERTEX_ARRAY_1f800228[rot * 6].vz = uVar17;
					*(UV_INFO *)&MVERTEX_ARRAY_1f800228[rot * 6].uv = local_s1_1728->uv2;
					makeMesh((MVERTEX(*)[5][5])MVERTEX_ARRAY_1f800228, rot, rot);
					drawMesh((MVERTEX(*)[5][5])MVERTEX_ARRAY_1f800228, rot, rot, pc);
					*/
				}
			}
		}
		/*	else
		{

				DAT_1f800210._2_2_ = (ushort)((uint)DAT_1f800210 >> 0x10);
				rot = (DAT_1f800210._2_2_);
				if (DAT_1f800210._2_2_ < 0x100) goto LAB_00040e34;
				iVar11 = (int)(short)DAT_1f80020a;
				if (((int)(short)DAT_1f80020e - iVar11) + (int)(short)DAT_1f800210._2_2_ + 8U < 0x110)
					goto LAB_00040e34;
				if (-1 < (int)(short)DAT_1f80020e)
				{
					if (iVar11 == 0)
						goto LAB_00040dfc;
					goto LAB_00040e34;
				}
				if (iVar11 != 1)
					goto LAB_00040e34;*/
					/*	LAB_00040dfc:

						if ((int)((uint)DAT_1f800210._2_2_ << 0x10) < 0)
						{
							if (DAT_1f80020e != 1)
								goto LAB_00040e34;
						}
						else
						{
							if (DAT_1f80020e != 0)
								goto LAB_00040e34;
						}
						
		}*/

	LAB_00041140:
		if (uVar7 == 0x15)
		{
			polys = (PL_POLYFT4 *)&polys[1].v0; // 0x14
		}
		else
		{
			polys = polys + 1;
		}
	} while (true);
}



// decompiled code
// original method signature: 
// int /*$ra*/ DrawAllBuildings(unsigned long *objects /*$t3*/, int num_buildings /*$s5*/, struct DB *disp /*$a2*/)
 // line 2053, offset 0x000411f4
	/* begin block 1 */
		// Start line: 2054
		// Start offset: 0x000411F4
		// Variables:
	// 		int i; // $s3
	// 		int model_number; // $v0
	// 		int prev_mat; // $s4
	// 		struct MODEL *model; // $a0
	// 		struct CELL_OBJECT *building; // $s0

		/* begin block 1.1 */
			// Start line: 2091
			// Start offset: 0x0004132C
			// Variables:
		// 		int spacefree; // $a0

			/* begin block 1.1.1 */
				// Start line: 2134
				// Start offset: 0x0004135C
			/* end block 1.1.1 */
			// End offset: 0x00041364
			// End Line: 2135

			/* begin block 1.1.2 */
				// Start line: 2138
				// Start offset: 0x00041364
				// Variables:
			// 		int zBias; // $v0
			// 		unsigned long *savedOT; // $s1
			/* end block 1.1.2 */
			// End offset: 0x00041398
			// End Line: 2150
		/* end block 1.1 */
		// End offset: 0x00041398
		// End Line: 2150
	/* end block 1 */
	// End offset: 0x0004143C
	// End Line: 2179

	/* begin block 2 */
		// Start line: 5011
	/* end block 2 */
	// End Line: 5012

	/* begin block 3 */
		// Start line: 5025
	/* end block 3 */
	// End Line: 5026

// [D]
int DrawAllBuildings(CELL_OBJECT **objects, int num_buildings, DB *disp)
{
	/*
	it contains prettier yet bugged code

	int prev_mat = -1;

	for (int i = 0; i < 8; i++) {
		plotContext.f4colourTable[i + 0] = planeColours[i] | 0x2C000000;
		plotContext.f4colourTable[i + 1] = planeColours[0] | 0x2C000000;
		plotContext.f4colourTable[i + 2] = planeColours[5] | 0x2C000000;
		plotContext.f4colourTable[i + 3] = planeColours[0] | 0x2C000000; // default: 0x2C00F0F0
	}

	current->ot += 8;

	plotContext.ptexture_pages = &texture_pages;
	plotContext.ptexture_cluts = &texture_cluts;
	plotContext.polySizes = PolySizes;
	plotContext.flags = 0;
	plotContext.current = current;

	if (num_buildings > 0) {
		int model_number = GetModelNumber();

		if (model_number > 55999) {
			for (int i = 0; i < num_buildings, model_number > 55999; i++, model_number = GetModelNumber()) 
			{
				CELL_OBJECT *building = (CELL_OBJECT *)objects[i];
				
				int mat = building->yang;

				if (mat == prev_mat) {
					Apply_InvCameraMatrixSetTrans(&building->pos);
				}
				else {
					Apply_InvCameraMatrixAndSetMatrix(&building->pos, &CompoundMatrix[mat]);
					prev_mat = mat;
				}

				MODEL *model = modelpointers[building->type];

				OTTYPE *savedOT = current->ot;

				int zBias = (model->zBias - 64);

				if (zBias < 0)
					zBias = 0;

				current->ot += (zBias * 4);

				PlotBuildingModelSubdivNxN(model, building->yang, &plotContext, 1);

				current->ot = savedOT;
			}
		}
	}
	
	current->ot -= 8;

	return 0;
	*/

	DB *pDVar1;
	ulong uVar2;
	uint uVar3;
	int iVar4;
	char *pcVar5;
	MODEL *model;
	uint *puVar6;
	ulong *puVar7;
	OTTYPE* savedOT;
	CELL_OBJECT *local_s0_312;
	int iVar8;
	uint uVar9;

	uVar9 = 0xffffffff;
	puVar6 = (uint *)(plotContext.f4colourTable + 3);
	puVar7 = planeColours;
	iVar8 = 7;
	do {
		puVar6[-3] = *puVar7 | 0x2c000000;
		puVar6[-1] = planeColours[4] | 0x2c000000;
		uVar2 = planeColours[0];
		puVar7 = puVar7 + 1;
		*puVar6 = 0x2c00f0f0;
		puVar6[-2] = uVar2 | 0x2c000000;
		iVar8 = iVar8 + -1;
		*puVar6 = planeColours[0] | 0x2c000000;
		plotContext.current = current;
		puVar6 = puVar6 + 4;
	} while (-1 < iVar8);

	current->ot = current->ot + 8;

	plotContext.ptexture_pages = &texture_pages;
	plotContext.ptexture_cluts = &texture_cluts;
	plotContext.polySizes = PolySizes;
	plotContext.flags = 0;
	iVar8 = 0;

	if (0 < num_buildings) 
	{
		pcVar5 = (plotContext.current)->primtab + -(int)((plotContext.current)->primptr + -0x1e000);

		while (55999 < (int)pcVar5) 
		{
			local_s0_312 = (CELL_OBJECT *)*objects;
			uVar3 = (uint)local_s0_312->yang;

			if (uVar9 == uVar3) 
			{
				Apply_InvCameraMatrixSetTrans(&local_s0_312->pos);
			}
			else 
			{
				Apply_InvCameraMatrixAndSetMatrix(&local_s0_312->pos, CompoundMatrix + uVar3);
				uVar9 = uVar3;
			}

			model = modelpointers[local_s0_312->type];
			savedOT = current->ot;
			iVar4 = model->zBias - 64;
			if (iVar4 < 0)
				iVar4 = 0;

			objects++;
			current->ot = savedOT + iVar4 * 4;

			PlotBuildingModelSubdivNxN(model, local_s0_312->yang, &plotContext, 1);

			pDVar1 = current;
			iVar8 = iVar8 + 1;
			current->ot = savedOT;

			if (num_buildings <= iVar8) 
				break;

			pcVar5 = pDVar1->primtab + -(int)(pDVar1->primptr + -0x1e000);
		}
	}
	current->ot = current->ot + -8;
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ RenderModel(struct MODEL *model /*$s2*/, struct MATRIX *matrix /*$a1*/, struct VECTOR *pos /*$a2*/, int zBias /*$s0*/, int flags /*stack 16*/)
 // line 2181, offset 0x0004143c
	/* begin block 1 */
		// Start line: 2182
		// Start offset: 0x0004143C
		// Variables:
	// 		int i; // $t0
	// 		unsigned long *savedOT; // $s1

		/* begin block 1.1 */
			// Start line: 2191
			// Start offset: 0x00041468
			// Variables:
		// 		struct MATRIX comb; // stack offset -48
		/* end block 1.1 */
		// End offset: 0x00041498
		// End Line: 2196

		/* begin block 1.2 */
			// Start line: 2210
			// Start offset: 0x00041538
			// Variables:
		// 		int spacefree; // $a0
		/* end block 1.2 */
		// End offset: 0x000415C0
		// End Line: 2222
	/* end block 1 */
	// End offset: 0x000415E4
	// End Line: 2224

	/* begin block 2 */
		// Start line: 5547
	/* end block 2 */
	// End Line: 5548

	/* begin block 3 */
		// Start line: 5550
	/* end block 3 */
	// End Line: 5551

	/* begin block 4 */
		// Start line: 5555
	/* end block 4 */
	// End Line: 5556

// [D]
void RenderModel(MODEL *model, MATRIX *matrix, VECTOR *pos, int zBias, int flags)
{
	OTTYPE *savedOT = current->ot;
	
	if (matrix != NULL)
	{
		MATRIX comb;
		gte_SetTransVector(pos);

		MulMatrix0(&inv_camera_matrix, matrix, &comb);
		SetRotMatrix(&comb);
	}

	int spacefree = (zBias >> 3) + (model->zBias - 64);

	if (spacefree < 0)
		spacefree = 0;
	
	current->ot += (spacefree * 4);

	for (int i = 0; i < 8; i++) {
		plotContext.f4colourTable[i + 0] = planeColours[i] | 0x2C000000;
		plotContext.f4colourTable[i + 1] = planeColours[0] | 0x2C000000;
		plotContext.f4colourTable[i + 2] = planeColours[5] | 0x2C000000;
		plotContext.f4colourTable[i + 3] = planeColours[0] | 0x2C000000; // default: 0x2C00F0F0
	}

	plotContext.ptexture_pages = &texture_pages;
	plotContext.ptexture_cluts = &texture_cluts;
	plotContext.polySizes = PolySizes;
	plotContext.flags = flags;
	plotContext.current = current;

	if (56000 < (current->primtab-(current->primptr-0x1e000)))
		PlotBuildingModelSubdivNxN(model, 0, &plotContext, 1);

	current->ot = savedOT;
}



// decompiled code
// original method signature: 
// unsigned long /*$ra*/ normalIndex(struct SVECTOR *verts /*$a0*/, unsigned int vidx /*$a1*/)
 // line 2267, offset 0x000415e4
	/* begin block 1 */
		// Start line: 2268
		// Start offset: 0x000415E4
		// Variables:
	// 		int th23; // $a0
	// 		int nx; // $t4
	// 		int ny; // $v1
	// 		int nz; // $a2
	// 		struct SVECTOR p; // stack offset -16
	// 		struct SVECTOR q; // stack offset -8

		/* begin block 1.1 */
			// Start line: 2268
			// Start offset: 0x000415E4
			// Variables:
		// 		int x; // $a1
		// 		int y; // $a0
		/* end block 1.1 */
		// End offset: 0x00041724
		// End Line: 2275
	/* end block 1 */
	// End offset: 0x000417A4
	// End Line: 2286

	/* begin block 2 */
		// Start line: 5723
	/* end block 2 */
	// End Line: 5724

	/* begin block 3 */
		// Start line: 5767
	/* end block 3 */
	// End Line: 5768

	/* begin block 4 */
		// Start line: 5771
	/* end block 4 */
	// End Line: 5772

// [D]
ulong normalIndex(SVECTOR *verts, uint vidx)
{
	int iVar1;
	uint uVar2;
	uint uVar3;
	SVECTOR *v0;
	int iVar4;
	int iVar5;
	SVECTOR *v2;
	int iVar6;
	SVECTOR *v1;
	int iVar7;
	int iVar8;
	int iVar9;
	int iVar10;

	SVECTOR p;
	SVECTOR q;

	v1 = (SVECTOR *)((int)&verts->vx + (vidx >> 5 & 0x7f8));
	v0 = verts + (vidx & 0xff);
	v2 = (SVECTOR *)((int)&verts->vx + (vidx >> 0xd & 0x7f8));

	iVar10 = (uint)(ushort)v2->vz - (uint)(ushort)v0->vz;
	iVar8 = (int)(((uint)(ushort)v1->vy - (uint)(ushort)v0->vy) * 0x10000) >> 0x10;
	iVar7 = (uint)(ushort)v1->vz - (uint)(ushort)v0->vz;
	iVar1 = (int)(((uint)(ushort)v2->vy - (uint)(ushort)v0->vy) * 0x10000) >> 0x10;
	iVar5 = (uint)(ushort)v1->vx - (uint)(ushort)v0->vx;
	iVar4 = (uint)(ushort)v2->vx - (uint)(ushort)v0->vx;

	iVar9 = iVar8 * (iVar10 * 0x10000 >> 0x10) - (iVar7 * 0x10000 >> 0x10) * iVar1;
	iVar1 = (iVar5 * 0x10000 >> 0x10) * iVar1 - iVar8 * (iVar4 * 0x10000 >> 0x10);
	iVar6 = iVar9 + (iVar1 >> 3);
	iVar8 = iVar1 - (iVar6 >> 2);
	iVar6 = iVar6 + (iVar8 >> 3);

	if (iVar6 < iVar8) 
	{
		if (iVar6 + iVar8 < 1) 
		{
			uVar2 = 4;

			if (iVar8 < 0)
				uVar2 = 5;
		}
		else 
		{
			uVar2 = 2;
			if (iVar6 < 0)
				uVar2 = 3;
		}
	}
	else 
	{
		uVar2 = (0 < iVar8);

		if ((iVar6 + iVar8 < 1) && (uVar2 = 7, iVar6 < 0))
			uVar2 = 6;
	}

	uVar2 = uVar2 * 4;
	iVar4 = (int)(short)iVar7 * (int)(short)iVar4 - (int)(short)iVar5 * (int)(short)iVar10;

	if (iVar9 < 0)
		iVar9 = -iVar9;

	if (iVar1 < 0)
		iVar1 = -iVar1;

	if (iVar9 + iVar1 < iVar4)
		uVar2 = uVar2 + 1;

	uVar3 = uVar2 & 0x1f;
	if (iVar9 + iVar1 < -iVar4)
		uVar3 = uVar2 & 0x1f | 2;

	return uVar3 | 0x80;
}





