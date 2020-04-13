#include "THISDUST.H"
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
#include "../ASM/ASMTEST.H"

#include <string.h>

MATRIX aspect =
{ { { 6553, 0, 0 }, { 0, 4096, 0 }, { 0, 0, 4096 } }, { 0, 0, 0 } };

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

unsigned long planeColours[8];

inline int GetModelNumber()
{
	return current->primtab - (current->primptr - 0x1E000);
}

MATRIX inv_camera_matrix;
MATRIX2 CompoundMatrix[64];

uint16_t texture_pages[128];
uint16_t texture_cluts[128][32];

// offset: 0x1f800020
static plotContext context;

void Apply_InvCameraMatrixSetTrans(VECTOR_NOPAD *pos)
{
	UNIMPLEMENTED();
}

void Apply_InvCameraMatrixAndSetMatrix(VECTOR_NOPAD *pos, MATRIX2 *mtx)
{
	UNIMPLEMENTED();
}

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

void addSubdivSpriteShadow(POLYFT4LIT *src, SVECTOR *verts, int z)
{
	UNIMPLEMENTED();
	/*
	undefined4 *puVar1;
	uint uVar2;
	uint uVar3;
	undefined4 uVar4;
	int m;

	m = 4;
	uVar3 = *(uint *)&src->v0;
	DAT_1f8000c0 = 0x2e000000;
	DAT_1f8000b4 = DAT_1f8000b4 + 0x70;
	uVar2 = *(uint *)src >> 8 & 0xff;
	DAT_1f8000b8 = (uint)*(ushort *)
		((int)&texture_cluts + (*(uint *)src >> 0xf & 0x1fe) + uVar2 * 0x40) << 0x10
		;
	DAT_1f8000bc = (uint)(ushort)(&texture_pages)[uVar2] << 0x10;
	if (0xc80 < z) {
		m = 2;
	}
	DAT_1f800228 = *(undefined4 *)(verts + (uVar3 & 0xff));
	puVar1 = (undefined4 *)((int)&verts->vx + (uVar3 >> 5 & 0x7f8));
	DAT_1f80022c = *(uint *)&verts[uVar3 & 0xff].vz & 0xffff | (uint)(ushort)src->uv0 << 0x10;
	uVar4 = puVar1[1];
	(&DAT_1f800228)[m * 2] = *puVar1;
	(&DAT_1f80022c)[m * 2] = uVar4;
	*(UV_INFO *)((int)&DAT_1f80022c + m * 8 + 2) = src->uv1;
	uVar4 = *(undefined4 *)&verts[uVar3 >> 0x18].vz;
	(&DAT_1f800228)[m * 10] = *(undefined4 *)(verts + (uVar3 >> 0x18));
	(&DAT_1f80022c)[m * 10] = uVar4;
	puVar1 = (undefined4 *)((int)&verts->vx + (uVar3 >> 0xd & 0x7f8));
	*(UV_INFO *)((int)&DAT_1f80022c + m * 0x28 + 2) = src->uv3;
	uVar4 = puVar1[1];
	(&DAT_1f800228)[m * 0xc] = *puVar1;
	(&DAT_1f80022c)[m * 0xc] = uVar4;
	*(UV_INFO *)((int)&DAT_1f80022c + m * 0x30 + 2) = src->uv2;
	makeMesh((MVERTEX(*)[5][5])&DAT_1f800228, m, m);
	drawMesh((MVERTEX(*)[5][5])&DAT_1f800228, m, m, (_pct *)&DAT_1f800020);
	DAT_1f8000b4 = DAT_1f8000b4 + -0x70;
	return;*/
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

void DrawSprites(int numFound)
{
	UNIMPLEMENTED();
	/*
	ushort *puVar1;
	short sVar2;
	short *psVar3;
	int z;
	undefined4 *puVar4;
	undefined4 *puVar5;
	uint uVar6;
	MATRIX *pMVar7;
	MATRIX *pMVar8;
	uint uVar9;
	int iVar10;
	uint uVar11;
	int iVar12;
	MODEL *model;
	PACKED_CELL_OBJECT *pPVar13;
	PACKED_CELL_OBJECT **local_40;
	int local_38;
	int local_2c;

	z = ((int)(short)((int)camera_matrix.m[2][0] * (int)day_vectors[GameLevel].vx >> 0xc) +
		(int)(short)((int)camera_matrix.m[2][1] * (int)day_vectors[GameLevel].vy >> 0xc) +
		(int)(short)((int)camera_matrix.m[2][2] * (int)day_vectors[GameLevel].vz >> 0xc) + 0x1000) *
		0xc00;
	if (z < 0) {
		z = z + 0xfff;
	}
	uVar6 = (z >> 0x12) + 0x20U & 0xff;
	if (gTimeOfDay == 1) goto LAB_0003f0c4;
	if (gTimeOfDay < 2) {
		if (gTimeOfDay != 0) goto LAB_0003f0c4;
	LAB_0003f0a8:
		uVar6 = (int)(uVar6 * 2 * NightAmbient) >> 8;
	}
	else {
		if (gTimeOfDay == 2) goto LAB_0003f0a8;
		if (gTimeOfDay != 3) goto LAB_0003f0c4;
		uVar6 = uVar6 / 3;
	}
	uVar6 = uVar6 & 0xff;
LAB_0003f0c4:
	if (gWeather - 1U < 2) {
		uVar6 = (int)(uVar6 * 2 * NightAmbient) >> 8 & 0xff;
	}
	uVar6 = uVar6 << 0x10 | uVar6 << 8 | 0x2c000000 | uVar6;
	local_2c = numFound + -1;
	pMVar8 = &inv_camera_matrix;
	pMVar7 = &shadowMatrix;
	z = 2;
	do {
		psVar3 = pMVar8->m;
		sVar2 = pMVar8->m[0];
		pMVar8 = (MATRIX *)(pMVar8->m + 3);
		z = z + -1;
		pMVar7->m[0] = psVar3[2];
		pMVar7->m[1] = -sVar2;
		pMVar7->m[2] = sVar2;
		pMVar7 = (MATRIX *)(pMVar7->m + 3);
	} while (-1 < z);
	local_38 = 0;
	DAT_1f8000b0 = current->primptr;
	DAT_1f800024 = &texture_pages;
	DAT_1f800028 = &texture_cluts;
	DAT_1f8000b4 = current->ot;
	local_40 = &spriteList75;
	DAT_1f8000c0 = uVar6;
	DAT_1f800020 = current;
	while (local_2c != -1) {
		pPVar13 = *local_40;
		local_40 = local_40 + 1;
		model = modelpointers1536[(uint)(pPVar13->value >> 6) | ((uint)(pPVar13->pos).vy & 1) << 10];
		DAT_1f8000c0 = uVar6;
		if ((pPVar13->value & 0x3f) == 0x3f) {
			DAT_1f8000c0 = 0x2c808080;
		}
		DAT_1f8000d0 = (uint)(pPVar13->pos).vx;
		DAT_1f8000d4 = (int)((uint)(pPVar13->pos).vy << 0x10) >> 0x11;
		DAT_1f8000d8 = (uint)(pPVar13->pos).vz;
		z = Apply_InvCameraMatrixAndSetMatrix(&DAT_1f8000d0, &face_camera);
		if (z < 0x3e9) {
			uVar11 = (uint)model->num_polys;
			iVar10 = model->poly_block;
			iVar12 = model->vertices;
			while (uVar11 = uVar11 - 1, uVar11 != 0xffffffff) {
				uVar9 = *(uint *)(iVar10 + 4);
				DAT_1f8000b8 = (uint)(ushort)(&texture_cluts)
					[(uint)*(byte *)(iVar10 + 1) * 0x20 +
					(uint)*(byte *)(iVar10 + 2)] << 0x10;
				puVar4 = (undefined4 *)((uVar9 & 0xff) * 8 + iVar12);
				DAT_1f8000bc = (uint)(ushort)(&texture_pages)[(uint)*(byte *)(iVar10 + 1)] << 0x10;
				DAT_1f800228 = *puVar4;
				puVar5 = (undefined4 *)((uVar9 >> 5 & 0x7f8) + iVar12);
				DAT_1f80022c = puVar4[1] & 0xffff | (uint)*(ushort *)(iVar10 + 8) << 0x10;
				_DAT_1f800248 = *puVar5;
				puVar4 = (undefined4 *)((uVar9 >> 0x18) * 8 + iVar12);
				DAT_1f80024c = puVar5[1] & 0xffff | (uint)*(ushort *)(iVar10 + 10) << 0x10;
				DAT_1f8002c8 = *puVar4;
				puVar5 = (undefined4 *)((uVar9 >> 0xd & 0x7f8) + iVar12);
				DAT_1f8002cc = puVar4[1] & 0xffff | (uint)*(ushort *)(iVar10 + 0xe) << 0x10;
				DAT_1f8002e8 = *puVar5;
				puVar1 = (ushort *)(iVar10 + 0xc);
				iVar10 = iVar10 + 0x14;
				DAT_1f8002ec = puVar5[1] & 0xffff | (uint)*puVar1 << 0x10;
				makeMesh((MVERTEX(*)[5][5])&DAT_1f800228, 4, 4);
				drawMesh((MVERTEX(*)[5][5])&DAT_1f800228, 4, 4, (_pct *)&DAT_1f800020);
			}
		}
		else {
			DAT_1f8000b4 = DAT_1f8000b4 + -0x85;
			Tile1x1(model);
			DAT_1f8000b4 = DAT_1f8000b4 + 0x85;
		}
		local_2c = local_2c + -1;
		if ((((wetness == 0) && (gTimeOfDay != 3)) && ((pPVar13->value & 0x20) == 0)) &&
			((z < 7000 && (local_38 = local_38 + 1, local_38 < 0x28)))) {
			setCopControlWord(2, 0, shadowMatrix.m[0]._0_4_);
			setCopControlWord(2, 1, shadowMatrix.m._4_4_);
			setCopControlWord(2, 2, shadowMatrix.m[1]._2_4_);
			setCopControlWord(2, 3, shadowMatrix.m[2]._0_4_);
			setCopControlWord(2, 4, shadowMatrix._16_4_);
			addSubdivSpriteShadow((POLYFT4LIT *)model->poly_block, (SVECTOR *)model->vertices, z);
			if (model->num_polys == 2) {
				addSubdivSpriteShadow((POLYFT4LIT *)(model->poly_block + 0x14), (SVECTOR *)model->vertices, z)
					;
			}
			setCopControlWord(2, 0, face_camera.m[0]._0_4_);
			setCopControlWord(2, 1, face_camera.m._4_4_);
			setCopControlWord(2, 2, face_camera.m[1]._2_4_);
			setCopControlWord(2, 3, face_camera.m[2]._0_4_);
			setCopControlWord(2, 4, face_camera._16_4_);
		}
	}
	current->primptr = DAT_1f8000b0;
	return;*/
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

CELL_OBJECT * UnpackCellObject(PACKED_CELL_OBJECT *ppco, XZPAIR *near)
{
	UNIMPLEMENTED();
	return 0;
	/*
	CELL_OBJECT *returnObject0;
	int iVar1;
	CELL_OBJECT *returnObject;

	iVar1 = cell_object_index;
	if (ppco != (PACKED_CELL_OBJECT *)0x0) {
		returnObject = cell_object_buffer + cell_object_index;
		(returnObject->pos).vx =
			near->x + ((int)(((uint)(ppco->pos).vx - (uint)*(ushort *)&near->x) * 0x10000) >> 0x10);
		cell_object_buffer[cell_object_index].pos.vy = (int)((uint)(ppco->pos).vy << 0x10) >> 0x11;
		returnObject0 = cell_object_buffer + cell_object_index;
		cell_object_index = cell_object_index + 1U & 0x3ff;
		(returnObject0->pos).vz =
			near->z + ((int)(((uint)(ppco->pos).vz - (uint)*(ushort *)&near->z) * 0x10000) >> 0x10);
		*(uint *)&cell_object_buffer[iVar1].pad =
			((uint)(ppco->value >> 6) | ((uint)(ppco->pos).vy & 1) << 10) << 0x10 |
			((uint)ppco->value & 0x3f) << 8;
		return returnObject;
	}
	return (CELL_OBJECT *)0x0;*/
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

SVECTOR camera_angle = { 0,0,0 };
uint farClip2Player = 0x8ca0;

static int treecount = 0;
int numSpritesFound = 0;
static int alleycount = 0;

int groundDebrisIndex = 0;

int goFaster = 1;
int fasterToggle = 0;

int current_object_computed_value = 0;

int combointensity;

unsigned long model_object_ptrs[512];
unsigned long anim_obj_buffer[20];

int buildingsFound = 0;
int cell_object_index = 0;
CELL_OBJECT cell_object_buffer[1024];

unsigned long *tile_overflow_buffer;

CELL_OBJECT ground_debris[16];
PACKED_CELL_OBJECT *spriteList[75];

char CurrentPVS[444]; // 21*21+4
MATRIX2 matrixtable[64];
int setupYet = 0;

int num_regions;
int view_dist;
int pvs_square;
int pvs_square_sq;

int units_across_halved;
int units_down_halved;

int regions_across;
int regions_down;

OUT_CELL_FILE_HEADER* cell_header;

// [D] [A]
void DrawMapPSX(int *comp_val)
{
	ushort uVar1;
	CELL_OBJECT *pCVar2;
	MATRIX *pMVar3;
	uint uVar4;
	PACKED_CELL_OBJECT *pPVar5;
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
	MODEL *pMVar16;
	CELL_OBJECT **ppCVar17;
	ulong *puVar18;
	int iVar19;
	int iVar20;
	uint uVar21;
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
	MATRIX *local_38;
	int local_34;

	uVar21 = 0x1800;	// backPlane
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
	iVar7 = 0;

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

	local_34 = (441 >> uVar9) + -1;

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

					if (0 < iVar7) 
					{
						puVar18 = anim_obj_buffer;
						do {
							UNIMPLEMENTED();
							/*
							cop = (CELL_OBJECT *)*puVar18;
							newpos.vx = (cop->pos).vx - camera_position.vx;
							newpos.vy = (cop->pos).vy - camera_position.vy;
							newpos.vz = (cop->pos).vz - camera_position.vz;
							Apply_Inv_CameraMatrix(&newpos);
							uVar21 = (uint)cop->yang;
							setCopControlWord(2, 0, *(undefined4 *)matrixtable[uVar21].m);
							setCopControlWord(2, 0x800, *(undefined4 *)(matrixtable[uVar21].m + 2));
							setCopControlWord(2, 0x1000, *(undefined4 *)(matrixtable[uVar21].m + 4));
							setCopControlWord(2, 0x1800, *(undefined4 *)(matrixtable[uVar21].m + 6));
							setCopControlWord(2, 0x2000, *(undefined4 *)(matrixtable[uVar21].m + 8));
							*/
							puVar18 = (ulong *)((CELL_OBJECT **)puVar18 + 1);
							iVar7 = iVar7 + -1;
							DrawAnimatingObject(modelpointers[cop->type], cop, &newpos);
							
						} while (iVar7 != 0);
					}

					buildingsFound = other_models_found;

					// [A] show stats
					printf("------ DrawMapPSX stats ------\n");
					printf("\tbuildingsFound: %d\n", buildingsFound);
					printf("\ttreecount: %d\n", treecount);
					printf("\tnumSpritesFound: %d\n", numSpritesFound);
					printf("\talleycount: %d\n", alleycount);
					printf("\ttiles_found: %d\n", tiles_found);
					printf("\tother_models_found: %d\n", other_models_found);

					return;
				}

				cellx = iVar19;
				if (iVar19 < 0)
					cellx = -iVar19;

				cellz = iVar20;

				if (iVar20 < 0) 
					cellz = -iVar20;

				local_34 = local_34 + -1;

				if (cellx + cellz < 0x10)
				{
					cellx = camx + iVar19;
					cellz = camz + iVar20;

					if ((((((rightPlane < 0) && (0 < leftPlane)) && (uVar21 < farClipLimit)) &&
						((-1 < cellx && (-1 < cellz)))) &&
						((cellx < cells_across &&
						((cellz < cells_down && (PVS_ptr[iVar19] != '\0')))))) &&
						(pPVar5 = GetFirstPackedCop(cellx, cellz, &ci, 1), pPVar5 != NULL)) 
					{
						ppCVar17 = (CELL_OBJECT **)(&anim_obj_buffer + iVar7);
						local_38 = &mRotStore;

						do {
							pMVar3 = local_38;
							pMVar16 = modelpointers[(uint)(pPVar5->value >> 6) | ((uint)(pPVar5->pos).vy & 1) << 10];

							cellx = FrustrumCheck16(pPVar5, (int)pMVar16->bounding_sphere);

							if (cellx != -1) 
							{
								uVar1 = pMVar16->shape_flags;
								if ((uVar1 & 0x4000) == 0)
								{

									uVar9 = (uint)pPVar5->value & 0x3f;

									if ((pPVar5->value & 0xf) != 0) 
									{
										if ((int)CompoundMatrix[uVar9].computed != current_object_computed_value) 
										{
											UNIMPLEMENTED();
											
											CompoundMatrix[uVar9].computed = (short)current_object_computed_value;
											/*
											uVar10 = getCopControlWord(2, 0);
											uVar12 = getCopControlWord(2, 0x800);
											*(undefined4 *)local_38->m = uVar10;
											*(undefined4 *)(pMVar3->m + 2) = uVar12;
											uVar10 = getCopControlWord(2, 0x1000);
											uVar12 = getCopControlWord(2, 0x1800);
											uVar14 = getCopControlWord(2, 0x2000);
											*(undefined4 *)(pMVar3->m + 4) = uVar10;
											*(undefined4 *)(pMVar3->m + 6) = uVar12;
											*(undefined4 *)(pMVar3->m + 8) = uVar14;
											lVar11 = getCopControlWord(2, 0x2800);
											lVar13 = getCopControlWord(2, 0x3000);
											lVar15 = getCopControlWord(2, 0x3800);
											pMVar3->t[0] = lVar11;
											pMVar3->t[1] = lVar13;
											pMVar3->t[2] = lVar15;

											MulMatrix0(&inv_camera_matrix,
												(MATRIX *)(matrixtable + uVar9),
												(MATRIX *)(CompoundMatrix + uVar9));

											setCopControlWord(2, 0, *(undefined4 *)local_38->m);
											setCopControlWord(2, 0x800, *(undefined4 *)(local_38->m + 2));
											setCopControlWord(2, 0x1000, *(undefined4 *)(local_38->m + 4));
											setCopControlWord(2, 0x1800, *(undefined4 *)(local_38->m + 6));
											setCopControlWord(2, 0x2000, *(undefined4 *)(local_38->m + 8));
											*/
										}
									}
									cellx = cell_object_index;
									if (((uVar1 & 0x480) == 0) && ((pMVar16->flags2 & 0xc000) == 0))
									{
										cop = NULL;

										if (pPVar5 != NULL) 
										{
											cop = cell_object_buffer + cell_object_index;
											(cop->pos).vx = ci.near.x + ((int)(((uint)(pPVar5->pos).vx - (ci.near.x & 0xffffU)) * 0x10000) >> 0x10);

											cell_object_buffer[cell_object_index].pos.vy = (int)((uint)(pPVar5->pos).vy << 0x10) >> 0x11;
											pCVar2 = cell_object_buffer + cell_object_index;
											cell_object_index = cell_object_index + 1U & 0x3ff;

											(pCVar2->pos).vz =
												ci.near.z +
												((int)(((uint)(pPVar5->pos).vz -
												(ci.near.z & 0xffffU)) * 0x10000) >>
													0x10);
											*(uint *)&cell_object_buffer[cellx].pad =
												((uint)(pPVar5->value >> 6) |
												((uint)(pPVar5->pos).vy & 1) << 10) << 0x10 |
													((uint)pPVar5->value & 0x3f) << 8;
										}

										if (((pMVar16->flags2 & 1) != 0) && (iVar7 < 0x14))
										{
											*ppCVar17 = cop;
											ppCVar17 = ppCVar17 + 1;
											iVar7 = iVar7 + 1;
										}

										if (other_models_found < 0xc0)
										{
											ppCVar6 = (CELL_OBJECT **)(model_object_ptrs + other_models_found);
											other_models_found = other_models_found + 1;
											*ppCVar6 = cop;
										}
									}
									else 
									{
										if (((pMVar16->flags2 & 0x80) != 0) && (alleycount = alleycount + 1, alleycount == 0xd)) 
										{
											cop = NULL;

											if (pPVar5 != NULL)
											{
												cop = cell_object_buffer + cell_object_index;
												(cop->pos).vx =
													ci.near.x +
													((int)(((uint)(pPVar5->pos).vx -
													(ci.near.x & 0xffffU)) * 0x10000) >>
														0x10);
												cell_object_buffer[cell_object_index].pos.vy =
													(int)((uint)(pPVar5->pos).vy << 0x10) >> 0x11;
												pCVar2 = cell_object_buffer + cell_object_index;
												cell_object_index = cell_object_index + 1U & 0x3ff;
												(pCVar2->pos).vz =
													ci.near.z +
													((int)(((uint)(pPVar5->pos).vz -
													(ci.near.z & 0xffffU)) * 0x10000) >>
														0x10);
												*(uint *)&cell_object_buffer[cellx].pad =
													((uint)(pPVar5->value >> 6) |
													((uint)(pPVar5->pos).vy & 1) << 10) << 0x10 |
														((uint)pPVar5->value & 0x3f) << 8;
											}

											uVar9 = groundDebrisIndex & 0xf;
											ground_debris[uVar9].pos.vx = (cop->pos).vx;
											ground_debris[uVar9].pos.vy = (cop->pos).vy;
											ground_debris[uVar9].pos.vz = (cop->pos).vz;
											groundDebrisIndex = groundDebrisIndex + 1;
											alleycount = 0;
											ground_debris[uVar9].pad = cop->pad;
										}

										if (tiles_found < 0x100) 
										{
											*(PACKED_CELL_OBJECT **)(tile_overflow_buffer + tiles_found) = pPVar5;
											tiles_found = tiles_found + 1;
										}
									}
								}
								else 
{
									if (numSpritesFound < 0x4b) 
									{
										ppPVar8 = spriteList + numSpritesFound;
										numSpritesFound = numSpritesFound + 1;
										*ppPVar8 = pPVar5;
									}

									cellx = cell_object_index;

									if (((pMVar16->flags2 & 1) != 0) && (iVar7 < 0x14)) 
									{
										cop = NULL;

										if (pPVar5 != NULL) 
										{
											cop = cell_object_buffer + cell_object_index;

											(cop->pos).vx = ci.near.x + ((int)(((uint)(pPVar5->pos).vx - (ci.near.x & 0xffffU)) * 0x10000) >> 0x10);
											cell_object_buffer[cell_object_index].pos.vy = (int)((uint)(pPVar5->pos).vy << 0x10) >> 0x11;

											pCVar2 = cell_object_buffer + cell_object_index;
											cell_object_index = cell_object_index + 1U & 0x3ff;

											(pCVar2->pos).vz = ci.near.z + ((int)(((uint)(pPVar5->pos).vz - (ci.near.z & 0xffffU)) * 0x10000) >> 0x10);
											*(uint *)&cell_object_buffer[cellx].pad = ((uint)(pPVar5->value >> 6) | ((uint)(pPVar5->pos).vy & 1) << 10) << 0x10 | ((uint)pPVar5->value & 0x3f) << 8;
										}

										*ppCVar17 = cop;
										ppCVar17 = ppCVar17 + 1;
										iVar7 = iVar7 + 1;
									}
									cellx = cell_object_index;

									if (((pMVar16->flags2 & 0x2000) != 0) && (uVar9 = treecount & 0xf, treecount = treecount + 1, uVar9 == 0))
									{
										cop = NULL;
										if (pPVar5 != NULL) {
											cop = cell_object_buffer + cell_object_index;
											(cop->pos).vx =
												ci.near.x +
												((int)(((uint)(pPVar5->pos).vx -
												(ci.near.x & 0xffffU)) * 0x10000) >>
													0x10);
											cell_object_buffer[cell_object_index].pos.vy =
												(int)((uint)(pPVar5->pos).vy << 0x10) >> 0x11;
											pCVar2 = cell_object_buffer + cell_object_index;
											cell_object_index = cell_object_index + 1U & 0x3ff;
											(pCVar2->pos).vz =
												ci.near.z +
												((int)(((uint)(pPVar5->pos).vz -
												(ci.near.z & 0xffffU)) * 0x10000) >>
													0x10);
											*(uint *)&cell_object_buffer[cellx].pad =
												((uint)(pPVar5->value >> 6) |
												((uint)(pPVar5->pos).vy & 1) << 10) << 0x10 |
													((uint)pPVar5->value & 0x3f) << 8;
										}
										uVar9 = groundDebrisIndex & 0xf;
										ground_debris[uVar9].pos.vx = (cop->pos).vx;
										ground_debris[uVar9].pos.vy = (cop->pos).vy;
										ground_debris[uVar9].pos.vz = (cop->pos).vz;
										groundDebrisIndex = groundDebrisIndex + 1;
										ground_debris[uVar9].pad = cop->pad;
									}
								}
							}
							pPVar5 = GetNextPackedCop(&ci);
						} while (pPVar5 != NULL);
					}
				}

				if (uVar4 != 1) 
					break;

				leftPlane = leftPlane + leftsin;
				uVar21 = uVar21 + backsin;
				rightPlane = rightPlane + rightsin;
				iVar20 = iVar20 + 1;

				PVS_ptr = PVS_ptr + pvs_square;

				if (iVar19 == iVar20)
					uVar4 = 2;
			}

			if (1 < uVar4)
				break;

			if (uVar4 == 0)
			{
				leftPlane = leftPlane + leftcos;
				uVar21 = uVar21 + backcos;
				iVar19 = iVar19 + 1;
				rightPlane = rightPlane + rightcos;
				if (iVar19 + iVar20 == 1) 
				{
					uVar4 = 1;
				}
			}
			else
			{
			LAB_0004004c:
				leftPlane = leftPlane - leftsin;
				uVar21 = uVar21 - backsin;
				rightPlane = rightPlane - rightsin;
				iVar20 = iVar20 + -1;
				PVS_ptr = PVS_ptr + -pvs_square;
				if (iVar19 == iVar20)
				{
					uVar4 = 0;
				}
			}
		}
		if (uVar4 != 2)
			goto LAB_0004004c;

		iVar19 = iVar19 + -1;
		leftPlane = leftPlane - leftcos;
		uVar21 = uVar21 - backcos;
		rightPlane = rightPlane - rightcos;

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

void SetupPlaneColours(ulong ambient)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;
	uint uVar2;
	uint uVar3;

	if (((1 < gWeather - 1U) && (gTimeOfDay != 0)) && (gTimeOfDay != 2)) {
		if (gTimeOfDay == 1) {
			uVar3 = ambient & 0xff;
			uVar2 = ambient >> 8 & 0xff;
			uVar1 = ambient >> 0x10 & 0xff;
			ULONG_000cc81c = (uVar1 * 0x78 >> 7) << 0x10 | (uVar2 * 0x78 >> 7) << 8 | uVar3 * 0x78 >> 7;
			ULONG_000cc820 = (uVar1 * 0x67 >> 7) << 0x10 | (uVar2 * 0x67 >> 7) << 8 | uVar3 * 0x67 >> 7;
			ULONG_000cc824 = (uVar1 * 0xd >> 5) << 0x10 | (uVar2 * 0xd >> 5) << 8 | uVar3 * 0xd >> 5;
			planeColours = uVar1 << 0x10 | uVar2 << 8 | uVar3;
			ULONG_000cc828 = (uVar1 * 3 >> 3) << 0x10 | (uVar2 * 3 >> 3) << 8 | uVar3 * 3 >> 3;
			ULONG_000cc82c = ULONG_000cc824;
			ULONG_000cc830 = ULONG_000cc820;
			ULONG_000cc834 = ULONG_000cc81c;
			return;
		}
		planeColours = ambient;
		ULONG_000cc81c = ambient;
		ULONG_000cc820 = ambient;
		ULONG_000cc824 = ambient;
		ULONG_000cc828 = ambient;
		ULONG_000cc82c = ambient;
		ULONG_000cc830 = ambient;
		ULONG_000cc834 = ambient;
		return;
	}
	planeColours = ambient;
	ULONG_000cc81c = ambient + 0x10101;
	ULONG_000cc820 = ambient + 0x30303;
	ULONG_000cc824 = ambient + 0x80808;
	ULONG_000cc828 = ambient + 0xa0a0a;
	ULONG_000cc82c = ambient + 0x80808;
	ULONG_000cc830 = ambient + 0x30303;
	ULONG_000cc834 = ambient + 0x10101;
	return;*/
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
	int iVar1;
	MATRIX2 *pMVar2;
	MATRIX2 *pMVar3;
	int iVar4;

	current_cell_x = camera_position.vx + units_across_halved;
	if (current_cell_x < 0)
		current_cell_x = current_cell_x + 0x7ff;

	current_cell_x = current_cell_x >> 0xb;
	current_cell_z = camera_position.vz + units_down_halved;

	if (current_cell_z < 0)
		current_cell_z = current_cell_z + 0x7ff;

	current_cell_z = current_cell_z >> 0xb;
	iVar1 = cells_across;
	if (cells_across < 0)
		iVar1 = cells_across + 0x1f;

	iVar4 = 0x30;

	GetPVSRegionCell2(
		(uint)current_cell_x >> 5 & 1 | ((uint)current_cell_z >> 5 & 1) << 1,
		((uint)current_cell_x >> 5) + ((uint)current_cell_z >> 5) * (iVar1 >> 5),
		(current_cell_z & 0x1fU) << 5 | current_cell_x & 0x1fU, CurrentPVS);

	pMVar3 = CompoundMatrix;
	pMVar2 = matrixtable;

	do {
		MulMatrix0(&inv_camera_matrix, (MATRIX*)pMVar2, (MATRIX*)pMVar3);

		pMVar3 = pMVar3 + 0x10;
		iVar4 = iVar4 + -0x10;
		pMVar2 = pMVar2 + 0x10;
	} while (-1 < iVar4);

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

void InitFrustrumMatrix(void)
{
	UNIMPLEMENTED();
	/*
	frustrum_matrix.m[0][1] = 0;
	frustrum_matrix.m[0][0] = rcossin_tbl[(-(int)camera_angle.vy & 0xfffU) * 2];
	frustrum_matrix.m[0][2] = rcos();
	frustrum_matrix.m[1][1] = 0;
	frustrum_matrix.m[1][0] = rcossin_tbl[((FrAng + -0x400) - (int)camera_angle.vy & 0xfffU) * 2];
	frustrum_matrix.m[1][2] = rcos();
	frustrum_matrix.m[2][1] = 0;
	frustrum_matrix.m[2][0] = rcossin_tbl[(-(FrAng + -0x400) - (int)camera_angle.vy & 0xfffU) * 2];
	frustrum_matrix.m[2][2] = rcos();
	frustrum_matrix.t[0] = -0x50;
	return;*/
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

void SetFrustrumMatrix(void)
{
	UNIMPLEMENTED();
	/*
	setCopControlWord(2, 8, frustrum_matrix.m[0]._0_4_);
	setCopControlWord(2, 9, frustrum_matrix.m._4_4_);
	setCopControlWord(2, 10, frustrum_matrix.m[1]._2_4_);
	setCopControlWord(2, 11, frustrum_matrix.m[2]._0_4_);
	setCopControlWord(2, 12, frustrum_matrix._16_4_);
	return;*/
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

void Set_Inv_CameraMatrix(void)
{
	UNIMPLEMENTED();
	/*
	setCopControlWord(2, 16, inv_camera_matrix.m[0]._0_4_);
	setCopControlWord(2, 17, inv_camera_matrix.m._4_4_);
	setCopControlWord(2, 18, inv_camera_matrix.m[1]._2_4_);
	setCopControlWord(2, 19, inv_camera_matrix.m[2]._0_4_);
	setCopControlWord(2, 20, inv_camera_matrix._16_4_);
	return;
	*/
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

void CalcObjectRotationMatrices(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	short sVar2;
	int iVar3;
	MATRIX2 *pMVar4;
	int iVar5;
	undefined2 local_38;
	short local_36;
	undefined2 local_34;

	iVar5 = 0;
	local_34 = 0;
	local_36 = 0;
	local_38 = 0;
	do {
		pMVar4 = &matrixtable + iVar5;
		RotMatrix(&local_38, pMVar4);
		iVar5 = iVar5 + 1;
		iVar3 = 8;
		do {
			iVar1 = (int)pMVar4->m[0] * 0x101;
			sVar2 = (short)((uint)iVar1 >> 8);
			if (iVar1 < 0) {
				sVar2 = (short)((uint)(iVar1 + 0xff) >> 8);
			}
			pMVar4->m[0] = sVar2;
			iVar3 = iVar3 + -2;
			pMVar4 = (MATRIX2 *)(pMVar4->m + 2);
		} while (-1 < iVar3);
		local_36 = local_36 + 0x40;
	} while (iVar5 < 0x40);
	return;*/
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
			//trap(0x400);
		}
	}
	num_straddlers = *(int *)(lump_ptr + 0x2c);
	if (*(int *)(lump_ptr + 8) != 0x800) {
		while (FrameCnt != 0x78654321) {
			//trap(0x400);
		}
	}
	if (*(int *)(lump_ptr + 0x10) != 0x20) {
		while (FrameCnt != 0x78654321) {
			//trap(0x400);
		}
	}
	cell_header = (OUT_CELL_FILE_HEADER *)lump_ptr;
	InitCellData();
	memcpy(cell_objects, lump_ptr + 0x30, num_straddlers << 3);
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

void DrawAllTheCars(int view)
{
	UNIMPLEMENTED();
	/*
	long lVar1;
	long lVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	undefined4 *puVar6;
	_CAR_DATA **pp_Var7;
	_CAR_DATA *p_Var8;
	int iVar9;
	int *piVar10;
	int iVar11;
	_CAR_DATA *local_70[20];

	lVar2 = camera_position.vz;
	lVar1 = camera_position.vx;
	p_Var8 = (_CAR_DATA *)0xd4160;
	num_cars_drawn = 0;
	piVar10 = &car_distance_60;
	iVar9 = 0;
	do {
		iVar11 = iVar9;
		if ((p_Var8->controlType != '\0') &&
			(iVar3 = PositionVisible((VECTOR *)(p_Var8->hd).where.t), iVar3 == 1)) {
			iVar3 = (p_Var8->hd).where.t[0];
			iVar5 = lVar1 - iVar3;
			if (iVar5 < 0) {
				iVar5 = iVar3 - lVar1;
			}
			iVar3 = (p_Var8->hd).where.t[2];
			iVar4 = lVar2 - iVar3;
			if (iVar4 < 0) {
				iVar4 = iVar3 - lVar2;
			}
			if (iVar5 < iVar4) {
				iVar3 = iVar4 + iVar5 / 2;
			}
			else {
				iVar3 = iVar5 + iVar4 / 2;
			}
			if (iVar3 < 16000) {
				*piVar10 = iVar5 + iVar4;
				piVar10 = piVar10 + 1;
				iVar11 = iVar9 + 1;
				local_70[iVar9] = p_Var8;
			}
		}
		p_Var8 = p_Var8 + -1;
		iVar9 = iVar11;
	} while ((_CAR_DATA *)0xd1267 < p_Var8);
	if (iVar11 != 0) {
		gForceLowDetailCars = 0;
		if (1 < iVar11) {
			iVar9 = 1;
			do {
				p_Var8 = local_70[iVar9];
				iVar3 = (&car_distance_60)[iVar9];
				iVar5 = iVar9 + 1;
				if (iVar9 != 0) {
					if (iVar3 < (int)(&car_distance_60)[iVar9 + -1]) {
						pp_Var7 = local_70 + iVar9;
						puVar6 = &car_distance_60 + iVar9;
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
				local_70[iVar9] = p_Var8;
				(&car_distance_60)[iVar9] = iVar3;
				iVar9 = iVar5;
			} while (iVar5 < iVar11);
		}
		iVar9 = 0;
		if (0 < iVar11) {
			iVar3 = (iVar11 + -1) * 2000;
			do {
				if ((int)(current->primtab + (-3000 - (int)(current->primptr + -0x1a180))) < 0x16a8) {
					return;
				}
				if ((int)(current->primtab + (-3000 - (int)(current->primptr + -0x1a180)) + -iVar3) < 0x16a8
					) {
					gForceLowDetailCars = 1;
				}
				if (local_70[iVar9]->controlType == '\x01') {
					gForceLowDetailCars = 0;
				}
				DrawCar(local_70[iVar9], view);
				iVar9 = iVar9 + 1;
				iVar3 = iVar3 + -2000;
			} while (iVar9 < iVar11);
		}
	}
	return;*/
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
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	ushort uVar2;
	undefined4 in_zero;
	CAR_POLY *in_at;
	int iVar3;
	SVECTOR *pSVar4;
	uint uVar5;
	ulong uVar6;
	undefined4 *puVar7;
	int iVar8;
	DB *pDVar9;
	SVECTOR *pSVar10;
	int iVar11;
	int iVar12;
	uint *puVar13;
	int iVar14;
	uint uVar15;
	uint uVar16;
	uint uVar17;
	undefined4 uVar18;
	uint *puVar19;
	uint uVar20;
	uint *puVar21;
	ushort *vidx;
	SVECTOR *verts;
	uint uVar22;
	uint uVar23;
	int local_30;

	pDVar9 = pc->current;
	verts = (SVECTOR *)model->vertices;
	uVar23 = 0xffffffff;
	*(ulong **)(pc->ptexture_pages + 0x48) = pDVar9->ot;
	*(char **)(pc->ptexture_pages + 0x46) = pDVar9->primptr;
	if ((*(uint *)(pc->ptexture_pages + 0x50) & 1) != 0) {
		combointensity = combointensity | 0x2000000;
		in_at = CAR_POLY_ARRAY_000b0000;
	}
	iVar3 = rot >> 3;
	uVar22 = (uint)model->num_polys;
	puVar21 = (uint *)model->poly_block;
	do {
		while (true) {
			uVar22 = uVar22 - 1;
			if (uVar22 == 0xffffffff) {
				pc->current->primptr = *(char **)(pc->ptexture_pages + 0x46);
				if ((*(uint *)(pc->ptexture_pages + 0x50) & 1) != 0) {
					combointensity = combointensity & 0xfdffffff;
				}
				return;
			}
			uVar20 = *puVar21;
			if ((uVar20 & 1) == 0) {
				*(byte *)((int)puVar21 + 0xe) = *(byte *)(puVar21 + 3);
				*(byte *)((int)puVar21 + 0xf) = *(byte *)((int)puVar21 + 0xd);
				*(byte *)puVar21 = *(byte *)puVar21 ^ 1;
				uVar20 = *puVar21;
				*(byte *)((int)puVar21 + 7) = *(byte *)((int)puVar21 + 6);
			}
			uVar5 = uVar20 & 0x1f;
			if ((uVar5 == 0xb) || (uVar5 == 0x15)) break;
			puVar21 = (uint *)((int)puVar21 + *(int *)(uVar5 * 4 + *(int *)(pc->ptexture_pages + 0x44)));
		}
		vidx = (ushort *)puVar21[1];
		uVar6 = uVar20 >> 0x18;
		if (uVar5 == 0x15) {
			*(uint *)(pc->ptexture_pages + 0x4e) = combointensity & 0x2ffffffU | 0x2c000000;
		}
		else {
			if ((uVar6 & 0x80) == 0) {
				rot = (int)vidx;
				uVar6 = normalIndex(verts, (uint)vidx);
				*(byte *)((int)puVar21 + 3) = (byte)uVar6;
			}
			*(undefined4 *)(pc->ptexture_pages + 0x4e) =
				*(undefined4 *)(pc->ptexture_pages + (iVar3 * 4 - uVar6 & 0x1f) * 2 + 4);
		}
		pSVar10 = verts + ((uint)vidx & 0xff);
		puVar7 = (undefined4 *)((int)&verts->vx + ((uint)vidx >> 5 & 0x7f8));
		pSVar4 = verts + ((uint)vidx >> 0x18);
		setCopReg(2, 0, *(undefined4 *)pSVar10);
		setCopReg(2, 1, *(undefined4 *)&pSVar10->vz);
		setCopReg(2, 2, *puVar7);
		setCopReg(2, 3, puVar7[1]);
		setCopReg(2, 4, *(undefined4 *)pSVar4);
		setCopReg(2, 5, *(undefined4 *)&pSVar4->vz);
		copFunction(2, 0x280030);
		if (((uVar23 ^ uVar20) & 0xffff00) != 0) {
			uVar23 = uVar20 >> 8 & 0xff;
			rot = uVar23 * 2 + *(int *)pc->ptexture_pages;
			*(uint *)(pc->ptexture_pages + 0x4a) =
				(uint)*(ushort *)
				((uVar20 >> 0xf & 0x1fe) + uVar23 * 0x40 + *(int *)(pc->ptexture_pages + 2)) <<
				0x10;
			*(uint *)(pc->ptexture_pages + 0x4c) = (uint)*(ushort *)rot << 0x10;
			uVar23 = uVar20;
		}
		copFunction(2, 0x1400006);
		_DAT_1f800208 = getCopReg(2, 12);
		_DAT_1f80020c = getCopReg(2, 13);
		DAT_1f800210 = getCopReg(2, 14);
		if (((0x13f < DAT_1f800208) && (0x13f < DAT_1f80020c)) && (0x13f < (ushort)DAT_1f800210)) {
			if (_DAT_1f80020c << 0x10 < 0) {
				DAT_1f800208 = DAT_1f800208 ^ 1;
			}
			if (DAT_1f800208 != 0) goto LAB_00040d6c;
			if (DAT_1f800210 << 0x10 < 0) {
				if (DAT_1f80020c != 1) goto LAB_00040d6c;
			}
			else {
				if (DAT_1f80020c != 0) goto LAB_00040d6c;
			}
			goto LAB_00041140;
		}
	LAB_00040d6c:
		DAT_1f80020a = (ushort)(_DAT_1f800208 >> 0x10);
		if ((DAT_1f80020a < 0x100) ||
			(DAT_1f80020e = (ushort)((uint)_DAT_1f80020c >> 0x10), DAT_1f80020e < 0x100)) {
		LAB_00040e34:
			uVar18 = getCopReg(2, 17);
			*(undefined4 *)(pc->ptexture_pages + 0x56) = uVar18;
			uVar18 = getCopReg(2, 18);
			*(undefined4 *)(pc->ptexture_pages + 0x58) = uVar18;
			uVar18 = getCopReg(2, 19);
			*(undefined4 *)(pc->ptexture_pages + 0x5a) = uVar18;
			iVar14 = *(int *)(pc->ptexture_pages + 0x58);
			iVar11 = *(int *)(pc->ptexture_pages + 0x5a);
			if (iVar14 < *(int *)(pc->ptexture_pages + 0x5a)) {
				iVar11 = iVar14;
			}
			iVar12 = *(int *)(pc->ptexture_pages + 0x56);
			if (iVar12 < iVar11) {
				iVar11 = iVar12;
			}
			iVar8 = *(int *)(pc->ptexture_pages + 0x5a);
			if (*(int *)(pc->ptexture_pages + 0x5a) < iVar14) {
				iVar8 = iVar14;
			}
			rot = iVar8 - iVar11;
			if (iVar8 < iVar12) {
				rot = iVar12 - iVar11;
			}
			iVar14 = getCopReg(2, 24);
			local_30 = iVar14;
			if (((*(uint *)(pc->ptexture_pages + 0x50) & 6) != 0) &&
				(local_30 = 1, (*(uint *)(pc->ptexture_pages + 0x50) & 4) == 0)) {
				local_30 = -iVar14;
			}
			if (0 < local_30) {
				if ((n == 0) || (rot << 2 <= iVar11 + -0xfa)) {
					puVar7 = (undefined4 *)((int)&verts->vx + ((uint)vidx >> 0xd & 0x7f8));
					puVar19 = *(uint **)(pc->ptexture_pages + 0x46);
					setCopReg(2, 0, *puVar7);
					setCopReg(2, 1, puVar7[1]);
					copFunction(2, 0x180001);
					copFunction(2, 0x168002e);
					uVar1 = *(ushort *)((int)puVar21 + 0xe);
					iVar11 = getCopReg(2, 7);
					rot = 0xff0000;
					if (-1 < iVar11) {
						rot = 0xffffff;
						uVar2 = *(ushort *)(puVar21 + 3);
						puVar13 = (uint *)(*(int *)(pc->ptexture_pages + 0x48) + (iVar11 >> 1) * 4);
						uVar15 = puVar21[2];
						uVar16 = *(uint *)(pc->ptexture_pages + 0x4a);
						uVar17 = *(uint *)(pc->ptexture_pages + 0x4c);
						uVar20 = *puVar13;
						*puVar13 = (uint)puVar19 & 0xffffff;
						*puVar19 = uVar20 & 0xffffff | 0x9000000;
						puVar19[1] = *(uint *)(pc->ptexture_pages + 0x4e);
						uVar20 = _DAT_1f800208;
						puVar19[3] = uVar15 & 0xffff | uVar16;
						puVar19[2] = uVar20;
						uVar20 = getCopReg(2, 12);
						puVar19[4] = uVar20;
						puVar19[5] = uVar15 >> 0x10 | uVar17;
						uVar20 = getCopReg(2, 13);
						puVar19[6] = uVar20;
						puVar19[7] = (uint)uVar1;
						uVar20 = getCopReg(2, 14);
						puVar19[8] = uVar20;
						puVar19[9] = (uint)uVar2;
						*(uint **)(pc->ptexture_pages + 0x46) = puVar19 + 10;
					}
				}
				else {
					iVar14 = rot << 1;
					rot = n;
					if ((n == 1) && (rot = (int)(ushort *)0x2, iVar11 + -0x96 < iVar14)) {
						rot = (int)&DAT_00000004;
					}
					DAT_1f800228 = *(undefined4 *)(verts + ((uint)vidx & 0xff));
					DAT_1f80022c = *(uint *)&verts[(uint)vidx & 0xff].vz & 0xffff |
						(uint)*(ushort *)(puVar21 + 2) << 0x10;
					uVar18 = *(undefined4 *)&verts[(uint)vidx >> 8 & 0xff].vz;
					(&DAT_1f800228)[rot * 2] = *(undefined4 *)(verts + ((uint)vidx >> 8 & 0xff));
					(&DAT_1f80022c)[rot * 2] = uVar18;
					*(undefined2 *)((int)&DAT_1f80022c + rot * 8 + 2) = *(undefined2 *)((int)puVar21 + 10);
					uVar18 = *(undefined4 *)&verts[(uint)vidx >> 0x18].vz;
					(&DAT_1f800228)[rot * 10] = *(undefined4 *)(verts + ((uint)vidx >> 0x18));
					(&DAT_1f80022c)[rot * 10] = uVar18;
					puVar7 = (undefined4 *)((int)&verts->vx + ((uint)vidx >> 0xd & 0x7f8));
					*(undefined2 *)((int)&DAT_1f80022c + rot * 0x28 + 2) = *(undefined2 *)((int)puVar21 + 0xe)
						;
					uVar18 = puVar7[1];
					(&DAT_1f800228)[rot * 0xc] = *puVar7;
					(&DAT_1f80022c)[rot * 0xc] = uVar18;
					*(undefined2 *)((int)&DAT_1f80022c + rot * 0x30 + 2) = *(undefined2 *)(puVar21 + 3);
					makeMesh((MVERTEX(*)[5][5])&DAT_1f800228, rot, rot);
					drawMesh((MVERTEX(*)[5][5])&DAT_1f800228, rot, rot, pc);
				}
			}
		}
		else {
			DAT_1f800210._2_2_ = (ushort)((uint)DAT_1f800210 >> 0x10);
			rot = ZEXT24(DAT_1f800210._2_2_);
			if (DAT_1f800210._2_2_ < 0x100) goto LAB_00040e34;
			iVar11 = (int)(short)DAT_1f80020a;
			if (((int)(short)DAT_1f80020e - iVar11) + (int)(short)DAT_1f800210._2_2_ + 8U < 0x110)
				goto LAB_00040e34;
			if (-1 < (int)(short)DAT_1f80020e) {
				if (iVar11 == 0) goto LAB_00040dfc;
				goto LAB_00040e34;
			}
			if (iVar11 != 1) goto LAB_00040e34;
		LAB_00040dfc:
			if ((int)((uint)DAT_1f800210._2_2_ << 0x10) < 0) {
				if (DAT_1f80020e != 1) goto LAB_00040e34;
			}
			else {
				if (DAT_1f80020e != 0) goto LAB_00040e34;
			}
		}
	LAB_00041140:
		if (uVar5 == 0x15) {
			puVar21 = puVar21 + 5;
		}
		else {
			puVar21 = puVar21 + 4;
		}
	} while (true);
	*/
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
int DrawAllBuildings(unsigned long *objects, int num_buildings, DB *disp)
{
	int prev_mat = -1;

	for (int i = 0; i < 8; i++) {
		context.f4colourTable[i + 0] = planeColours[i] | 0x2C000000;
		context.f4colourTable[i + 1] = planeColours[0] | 0x2C000000;
		context.f4colourTable[i + 2] = planeColours[5] | 0x2C000000;
		context.f4colourTable[i + 3] = planeColours[0] | 0x2C000000; // default: 0x2C00F0F0
	}

	current->ot += 8;

	context.ptexture_pages = &texture_pages;
	context.ptexture_cluts = &texture_cluts;
	context.polySizes = PolySizes;
	context.flags = 0;
	context.current = current;

	if (num_buildings > 0) {
		int model_number = GetModelNumber();

		if (model_number < 55999) {
			for (int i = 0; i < num_buildings, model_number < 55999; i++, model_number = GetModelNumber()) {
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

				PlotBuildingModelSubdivNxN(model, building->yang, &context, 1);

				current->ot = savedOT;
			}
		}
	}
	
	current->ot -= 8;

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

void RenderModel(MODEL *model, MATRIX *matrix, VECTOR *pos, int zBias, int flags)
{
	OTTYPE *savedOT = current->ot;

	if (matrix != NULL) {
		MATRIX comb;

		setCopControlWord(2, 5, pos->vx);
		setCopControlWord(2, 6, pos->vy);
		setCopControlWord(2, 7, pos->vz);

		MulMatrix0(&inv_camera_matrix, matrix, &comb);
		SetRotMatrix(&comb);
	}

	int spacefree = (zBias >> 3) + (model->zBias - 64);

	if (spacefree < 0)
		spacefree = 0;
	
	current->ot += (spacefree * 4);

	for (int i = 0; i < 8; i++) {
		context.f4colourTable[i + 0] = planeColours[i] | 0x2C000000;
		context.f4colourTable[i + 1] = planeColours[0] | 0x2C000000;
		context.f4colourTable[i + 2] = planeColours[5] | 0x2C000000;
		context.f4colourTable[i + 3] = planeColours[0] | 0x2C000000; // default: 0x2C00F0F0
	}

	context.ptexture_pages = &texture_pages;
	context.ptexture_cluts = &texture_cluts;
	context.polySizes = PolySizes;
	context.flags = flags;
	context.current = current;

	if (GetModelNumber() < 56000)
		PlotBuildingModelSubdivNxN(model, 0, &context, 1);

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
	SVECTOR *pSVar4;
	int iVar5;
	int iVar6;
	ushort *puVar7;
	int iVar8;
	ushort *puVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;

	puVar9 = (ushort *)((int)&verts->vx + (vidx >> 5 & 0x7f8));
	pSVar4 = verts + (vidx & 0xff);
	puVar7 = (ushort *)((int)&verts->vx + (vidx >> 0xd & 0x7f8));
	iVar13 = (uint)puVar7[2] - (uint)(ushort)pSVar4->vz;
	iVar11 = (int)(((uint)puVar9[1] - (uint)(ushort)pSVar4->vy) * 0x10000) >> 0x10;
	iVar10 = (uint)puVar9[2] - (uint)(ushort)pSVar4->vz;
	iVar1 = (int)(((uint)puVar7[1] - (uint)(ushort)pSVar4->vy) * 0x10000) >> 0x10;
	iVar6 = (uint)*puVar9 - (uint)(ushort)pSVar4->vx;
	iVar5 = (uint)*puVar7 - (uint)(ushort)pSVar4->vx;
	iVar12 = iVar11 * (iVar13 * 0x10000 >> 0x10) - (iVar10 * 0x10000 >> 0x10) * iVar1;
	iVar1 = (iVar6 * 0x10000 >> 0x10) * iVar1 - iVar11 * (iVar5 * 0x10000 >> 0x10);
	iVar8 = iVar12 + (iVar1 >> 3);
	iVar11 = iVar1 - (iVar8 >> 2);
	iVar8 = iVar8 + (iVar11 >> 3);
	if (iVar8 < iVar11) {
		if (iVar8 + iVar11 < 1) {
			uVar2 = 4;
			if (iVar11 < 0) {
				uVar2 = 5;
			}
		}
		else {
			uVar2 = 2;
			if (iVar8 < 0) {
				uVar2 = 3;
			}
		}
	}
	else {
		uVar2 = (uint)(0 < iVar11);
		if ((iVar8 + iVar11 < 1) && (uVar2 = 7, iVar8 < 0)) {
			uVar2 = 6;
		}
	}
	uVar2 = uVar2 * 4;
	iVar5 = (int)(short)iVar10 * (int)(short)iVar5 - (int)(short)iVar6 * (int)(short)iVar13;
	if (iVar12 < 0) {
		iVar12 = -iVar12;
	}
	if (iVar1 < 0) {
		iVar1 = -iVar1;
	}
	if (iVar12 + iVar1 < iVar5) {
		uVar2 = uVar2 + 1;
	}
	uVar3 = uVar2 & 0x1f;
	if (iVar12 + iVar1 < -iVar5) {
		uVar3 = uVar2 & 0x1f | 2;
	}
	return uVar3 | 0x80;
}





