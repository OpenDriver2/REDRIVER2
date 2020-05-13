#include "THISDUST.H"
#include "MODELS.H"
#include "SYSTEM.H"
#include "SPOOL.H"
#include "MISSION.H"
#include "CARS.H"

#include <string.h>

MODEL dummyModel;

char* modelname_buffer = NULL;
char *car_models_lump = NULL;

MODEL* modelpointers[1536] = { 0 };
int num_models_in_pack = 0;

unsigned short *Low2HighDetailTable = NULL;
unsigned short *Low2LowerDetailTable = NULL;
MODEL* pLodModels[1536];

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

// [D]
void ProcessMDSLump(char *lump_file, int lump_size)
{
	int iVar1;
	MODEL **ppMVar2;
	char* ptr;
	MODEL *model;
	MODEL *parentmodel;
	int iVar4;
	int modelAmts;

	int i;

	modelAmts = *(int *)lump_file;
	ptr = (lump_file + 4);
	num_models_in_pack = modelAmts;

	// assign model pointers
	if (0 < modelAmts) 
	{
		ppMVar2 = modelpointers;
		iVar4 = modelAmts;

		for (i = 0; i < modelAmts; i++)
		{
			int size = *(int*)ptr;
			ptr += sizeof(int);

			if (size) // [A] bug fix. Use dummyModel for empty slot
				modelpointers[i] = (MODEL*)ptr;
			else
				modelpointers[i] = &dummyModel;

			ptr += size;
		}
	}

	if (0 < modelAmts)
	{
		ppMVar2 = modelpointers;
		iVar4 = modelAmts;

		// process parent instances
		do {
			model = *ppMVar2;

			if (model->instance_number != -1) 
			{
				parentmodel = modelpointers[model->instance_number];

				if (parentmodel->collision_block != 0)
					model->collision_block = (int)(char*)parentmodel + parentmodel->collision_block;

				// convert to real offsets
				model->vertices = (int)(char*)parentmodel + parentmodel->vertices;
				model->normals = (int)(char*)parentmodel + parentmodel->normals;
				model->point_normals = (int)(char*)parentmodel + parentmodel->point_normals;
			}

			iVar4--;
			ppMVar2++;
		} while (iVar4 != 0);
	}

	// process models without parents
	if (0 < modelAmts) 
	{
		ppMVar2 = modelpointers;
		do {
			model = *ppMVar2;

			if (model->instance_number == -1) 
			{
				if (model->collision_block != 0)
					model->collision_block += (int)(char*)model;

				model->vertices += (int)(char*)model;
				model->normals += (int)(char*)model;
				model->point_normals += (int)(char*)model;
			}

			model->poly_block += (int)(char*)model;

			modelAmts--;
			ppMVar2++;
		} while (modelAmts != 0);
	}
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

// [D]
int ProcessCarModelLump(char *lump_ptr, int lump_size)
{
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

	// compute size
	do {
		if (*piVar6 != -1)
		{
			iVar2 = piVar6[1];
			iVar4 = *(int *)(pcVar7 + *piVar6 + 0xb4);
			if (iVar2 != -1) 
			{
				iVar4 = iVar4 + *(int *)(pcVar7 + iVar2 + 0xb8);
			}

			iVar3 = piVar6[2];
			if (iVar3 != -1)
			{
				iVar4 = iVar4 + *(int *)(pcVar7 + iVar3 + 0xb4);
			}

			uVar5 = (iVar4 + 0x800U & 0xfffff800) + 0x800;
			if ((int)uVar9 < (int)uVar5) 
			{
				uVar9 = uVar5;
			}

			uVar5 = (iVar2 - *piVar6) + 0x800U & 0xfffff800;
			if ((int)uVar9 < (int)uVar5)
			{
				uVar9 = uVar5;
			}

			uVar5 = (iVar3 - iVar2) + 0x800U & 0xfffff800;
			if ((int)uVar9 < (int)uVar5) 
			{
				uVar9 = uVar5;
			}

			if ((iVar8 != 0xb) && (uVar5 = (piVar6[3] - iVar3) + 0x800U & 0xfffff800, (int)uVar9 < (int)uVar5)) 
			{
				uVar9 = uVar5;
			}
		}
		iVar8++;
		piVar6+=3;
	} while (iVar8 < 0xd);

	iVar8 = 0;

	ppMVar12 = gCarLowModelPtr;
	ppMVar11 = gCarDamModelPtr;
	ppMVar10 = gCarCleanModelPtr;

	do {
		*ppMVar10 = NULL;
		*ppMVar11 = NULL;
		*ppMVar12 = NULL;

		if (iVar8 == 4) 
		{
			specmallocptr = mallocptr;
			NOTIFY_MALLOC();
		}

		iVar4 = MissionHeader->residentModels[iVar8];

		if (iVar4 == 0xd) 
		{
			iVar4 = 10 - (MissionHeader->residentModels[0] + MissionHeader->residentModels[1] + MissionHeader->residentModels[2]);

			if (iVar4 < 1) 
			{
				iVar4 = 1;
			}
			else if (4 < iVar4)
			{
				iVar4 = 4;
			}
		}

		if (iVar4 != -1) 
		{
			piVar6 = (int *)(pcVar7 + iVar4 * 12);

			if (*piVar6 != -1) 
			{
				pMVar1 = GetCarModel(pcVar7 + *piVar6 + 0xa0, &mallocptr, 1);
				*ppMVar10 = pMVar1;
				NOTIFY_MALLOC();
			}

			if (piVar6[1] != -1) 
			{
				pMVar1 = GetCarModel(pcVar7 + piVar6[1] + 0xa0, &mallocptr, 0);
				*ppMVar11 = pMVar1;
				NOTIFY_MALLOC();
			}

			if (piVar6[2] != -1) 
			{
				pMVar1 = GetCarModel(pcVar7 + piVar6[2] + 160, &mallocptr, 1);
				*ppMVar12 = pMVar1;
				NOTIFY_MALLOC();
			}
		}

		ppMVar12++;
		ppMVar11++;
		ppMVar10++;
		iVar8++;
	} while (iVar8 < 5);


	mallocptr = specmallocptr + uVar9 + 2048; // [A] temporary here, fixes car model spooling
	specLoadBuffer = mallocptr - 2048;

	buildNewCars();

	return 0;
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

// [D]
MODEL* GetCarModel(char *src, char **dest, int KeepNormals)
{
	int size;
	MODEL *model;

	model = (MODEL *)*dest;

	char* mem = src;

	if (KeepNormals == 0)
		size = ((MODEL*)src)->normals;
	else 
		size = ((MODEL*)src)->poly_block;

	memcpy(*dest, src, size);

	if (KeepNormals == 0)
		size = model->normals;
	else 
		size = model->poly_block;
	
	*dest += size + 2;

	model->vertices += (int)model;
	model->normals += (int)model;
	model->poly_block = (int)src + model->poly_block;

	if (KeepNormals == 0)
		model->point_normals = 0;
	else
		model->point_normals += (int)model;

	return model;
}





