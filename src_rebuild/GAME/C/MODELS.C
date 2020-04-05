#include "THISDUST.H"
#include "MODELS.H"

char* modelname_buffer = NULL;
char *car_models_lump = NULL;

// decompiled code
// original method signature: 
// void /*$ra*/ ProcessMDSLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
 // line 33, offset 0x00064cfc
	/* begin block 1 */
		// Start line: 34
		// Start offset: 0x00064CFC
		// Variables:
	// 		int i; // $a2
	// 		int size; // $v0
	// 		int modelamt; // $a3
	// 		char *mdsfile; // $a0
	// 		struct MODEL *model; // $a0
	// 		struct MODEL *parentmodel; // $a1
	/* end block 1 */
	// End offset: 0x00064E6C
	// End Line: 94

	/* begin block 2 */
		// Start line: 66
	/* end block 2 */
	// End Line: 67

	/* begin block 3 */
		// Start line: 78
	/* end block 3 */
	// End Line: 79

void ProcessMDSLump(char *lump_file, int lump_size)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	MODEL **ppMVar2;
	int *piVar3;
	MODEL *pMVar4;
	MODEL *pMVar5;
	int iVar6;
	int iVar7;

	iVar7 = *(int *)lump_file;
	piVar3 = (int *)(lump_file + 4);
	num_models_in_pack = iVar7;
	if (0 < iVar7) {
		ppMVar2 = modelpointers1536;
		iVar6 = iVar7;
		do {
			iVar1 = *piVar3;
			*ppMVar2 = (MODEL *)(piVar3 + 1);
			ppMVar2 = ppMVar2 + 1;
			iVar6 = iVar6 + -1;
			piVar3 = (int *)((int)&((MODEL *)(piVar3 + 1))->shape_flags + iVar1);
		} while (iVar6 != 0);
	}
	if (0 < iVar7) {
		ppMVar2 = modelpointers1536;
		iVar6 = iVar7;
		do {
			pMVar4 = *ppMVar2;
			if ((pMVar4[-1].collision_block != 0) && ((int)pMVar4->instance_number != -1)) {
				pMVar5 = modelpointers1536[(int)pMVar4->instance_number];
				if (pMVar5->collision_block != 0) {
					pMVar4->collision_block = (int)&pMVar5->shape_flags + pMVar5->collision_block;
				}
				pMVar4->vertices = (int)&pMVar5->shape_flags + pMVar5->vertices;
				pMVar4->normals = (int)&pMVar5->shape_flags + pMVar5->normals;
				pMVar4->point_normals = (int)&pMVar5->shape_flags + pMVar5->point_normals;
			}
			iVar6 = iVar6 + -1;
			ppMVar2 = ppMVar2 + 1;
		} while (iVar6 != 0);
	}
	if (0 < iVar7) {
		ppMVar2 = modelpointers1536;
		do {
			pMVar4 = *ppMVar2;
			if (pMVar4[-1].collision_block != 0) {
				if (pMVar4->instance_number == -1) {
					if (pMVar4->collision_block != 0) {
						pMVar4->collision_block = (int)&pMVar4->shape_flags + pMVar4->collision_block;
					}
					pMVar4->vertices = (int)&pMVar4->shape_flags + pMVar4->vertices;
					pMVar4->normals = (int)&pMVar4->shape_flags + pMVar4->normals;
					pMVar4->point_normals = (int)&pMVar4->shape_flags + pMVar4->point_normals;
				}
				pMVar4->poly_block = (int)&pMVar4->shape_flags + pMVar4->poly_block;
			}
			iVar7 = iVar7 + -1;
			ppMVar2 = ppMVar2 + 1;
		} while (iVar7 != 0);
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ ProcessCarModelLump(char *lump_ptr /*$s2*/, int lump_size /*$a1*/)
 // line 212, offset 0x00064e6c
	/* begin block 1 */
		// Start line: 214
		// Start offset: 0x00064E6C
		// Variables:
	// 		int offset; // $a0
	// 		int i; // $s3
	// 		int car_model; // $a0
	// 		int specMemReq; // $s4

		/* begin block 1.1 */
			// Start line: 231
			// Start offset: 0x00064EB0
			// Variables:
		// 		struct MODEL *model; // $v0
		// 		int mem; // $a1
		/* end block 1.1 */
		// End offset: 0x00064F88
		// End Line: 286
	/* end block 1 */
	// End offset: 0x00065134
	// End Line: 348

	/* begin block 2 */
		// Start line: 381
	/* end block 2 */
	// End Line: 382

	/* begin block 3 */
		// Start line: 456
	/* end block 3 */
	// End Line: 457

	/* begin block 4 */
		// Start line: 457
	/* end block 4 */
	// End Line: 458

	/* begin block 5 */
		// Start line: 459
	/* end block 5 */
	// End Line: 460

int ProcessCarModelLump(char *lump_ptr, int lump_size)
{
	UNIMPLEMENTED();
	return 0;
	/*
	MODEL *pMVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint uVar5;
	int *piVar6;
	char *pcVar7;
	int iVar8;
	uint uVar9;
	MODEL **ppMVar10;
	MODEL **ppMVar11;
	MODEL **ppMVar12;

	uVar9 = 0;
	iVar8 = 8;
	pcVar7 = lump_ptr + 4;
	piVar6 = (int *)(lump_ptr + 100);
	do {
		if (*piVar6 != -1) {
			iVar2 = piVar6[1];
			iVar4 = *(int *)(pcVar7 + *piVar6 + 0xb4);
			if (iVar2 != -1) {
				iVar4 = iVar4 + *(int *)(pcVar7 + iVar2 + 0xb8);
			}
			iVar3 = piVar6[2];
			if (iVar3 != -1) {
				iVar4 = iVar4 + *(int *)(pcVar7 + iVar3 + 0xb4);
			}
			uVar5 = (iVar4 + 0x800U & 0xfffff800) + 0x800;
			if ((int)uVar9 < (int)uVar5) {
				uVar9 = uVar5;
			}
			uVar5 = (iVar2 - *piVar6) + 0x800U & 0xfffff800;
			if ((int)uVar9 < (int)uVar5) {
				uVar9 = uVar5;
			}
			uVar5 = (iVar3 - iVar2) + 0x800U & 0xfffff800;
			if ((int)uVar9 < (int)uVar5) {
				uVar9 = uVar5;
			}
			if ((iVar8 != 0xb) &&
				(uVar5 = (piVar6[3] - iVar3) + 0x800U & 0xfffff800, (int)uVar9 < (int)uVar5)) {
				uVar9 = uVar5;
			}
		}
		iVar8 = iVar8 + 1;
		piVar6 = piVar6 + 3;
	} while (iVar8 < 0xd);
	iVar8 = 0;
	ppMVar12 = gCarLowModelPtr5;
	ppMVar11 = gCarDamModelPtr5;
	ppMVar10 = gCarCleanModelPtr5;
	iVar2 = 0;
	do {
		*ppMVar10 = (MODEL *)0x0;
		*ppMVar11 = (MODEL *)0x0;
		*ppMVar12 = (MODEL *)0x0;
		if (iVar8 == 4) {
			specmallocptr = mallocptr;
		}
		iVar4 = *(int *)((int)MissionHeader->residentModels + iVar2);
		if (iVar4 == 0xd) {
			iVar4 = 10 - (MissionHeader->residentModels[0] + MissionHeader->residentModels[1] +
				MissionHeader->residentModels[2]);
			if (iVar4 < 1) {
				iVar4 = 1;
			}
			else {
				if (4 < iVar4) {
					iVar4 = 4;
				}
			}
		}
		if (iVar4 != -1) {
			piVar6 = (int *)(pcVar7 + iVar4 * 0xc);
			if (*piVar6 != -1) {
				pMVar1 = GetCarModel(pcVar7 + *piVar6 + 0xa0, &mallocptr, 1);
				*ppMVar10 = pMVar1;
			}
			if (piVar6[1] != -1) {
				pMVar1 = GetCarModel(pcVar7 + piVar6[1] + 0xa0, &mallocptr, 0);
				*ppMVar11 = pMVar1;
			}
			if (piVar6[2] != -1) {
				pMVar1 = GetCarModel(pcVar7 + piVar6[2] + 0xa0, &mallocptr, 1);
				*ppMVar12 = pMVar1;
			}
		}
		ppMVar12 = ppMVar12 + 1;
		ppMVar11 = ppMVar11 + 1;
		ppMVar10 = ppMVar10 + 1;
		iVar8 = iVar8 + 1;
		iVar2 = iVar2 + 4;
	} while (iVar8 < 5);
	mallocptr = specmallocptr + uVar9;
	specLoadBuffer = mallocptr + -0x800;
	buildNewCars();
	return 0;*/
}



// decompiled code
// original method signature: 
// struct MODEL * /*$ra*/ GetCarModel(char *src /*$s2*/, char **dest /*$s1*/, int KeepNormals /*$s3*/)
 // line 391, offset 0x00065134
	/* begin block 1 */
		// Start line: 392
		// Start offset: 0x00065134
		// Variables:
	// 		struct MODEL *model; // $s0
	// 		int size; // $a2
	// 		char *mem; // $v1

		/* begin block 1.1 */
			// Start line: 419
			// Start offset: 0x0006519C
		/* end block 1.1 */
		// End offset: 0x000651EC
		// End Line: 429
	/* end block 1 */
	// End offset: 0x0006520C
	// End Line: 432

	/* begin block 2 */
		// Start line: 513
	/* end block 2 */
	// End Line: 514

	/* begin block 3 */
		// Start line: 1174
	/* end block 3 */
	// End Line: 1175

MODEL * GetCarModel(char *src, char **dest, int KeepNormals)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	size_t __n;
	MODEL *pMVar2;

	pMVar2 = (MODEL *)*dest;
	if (KeepNormals == 0) {
		__n = *(size_t *)(src + 0x18);
	}
	else {
		__n = *(size_t *)(src + 0x14);
	}
	memcpy(*dest, src, __n);
	if (KeepNormals == 0) {
		iVar1 = pMVar2->normals;
	}
	else {
		iVar1 = pMVar2->poly_block;
	}
	*dest = (char *)((int)&pMVar2->flags2 + iVar1 + 1 & 0xfffffffc);
	pMVar2->vertices = (int)&pMVar2->shape_flags + pMVar2->vertices;
	pMVar2->normals = (int)&pMVar2->shape_flags + pMVar2->normals;
	*(char **)&pMVar2->poly_block = src + pMVar2->poly_block;
	if (KeepNormals == 0) {
		pMVar2->point_normals = 0;
	}
	else {
		pMVar2->point_normals = (int)&pMVar2->shape_flags + pMVar2->point_normals;
	}
	return pMVar2;
	*/
}





