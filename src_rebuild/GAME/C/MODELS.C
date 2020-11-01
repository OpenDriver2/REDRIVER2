#include "DRIVER2.H"
#include "MODELS.H"
#include "SYSTEM.H"
#include "SPOOL.H"
#include "MISSION.H"
#include "CARS.H"

#include <string.h>

MODEL dummyModel = { 0 };

char* modelname_buffer = NULL;
char *car_models_lump = NULL;

MODEL* modelpointers[1536] = { NULL };
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
	// 		MODEL *model; // $a0
	// 		MODEL *parentmodel; // $a1
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
		for (i = 0; i < 1536; i++) // [A] bug fix. Init with dummyModel
			modelpointers[i] = &dummyModel;

		ppMVar2 = modelpointers;
		iVar4 = modelAmts;

		for (i = 0; i < modelAmts; i++)
		{
			int size = *(int*)ptr;
			ptr += sizeof(int);

			if (size) 
				modelpointers[i] = (MODEL*)ptr;

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
		// 		MODEL *model; // $v0
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
	
	int size;
	int *offsets;
	char *models_offset;


	MODEL *model;
	int model_number;
	int i;

	int specMemReq;

	specMemReq = 0;

	models_offset = lump_ptr + 4 + 160;	// also skip model count
	offsets = (int*)(lump_ptr + 100);

	// compute special memory requirement for spooling
	for (i = 8; i < 13; i++)
	{
		int cleanOfs = offsets[0];
		int damOfs = offsets[1];
		int lowOfs = offsets[2];

		if (cleanOfs != -1)
		{
			size = ((MODEL*)(models_offset + cleanOfs))->poly_block;

			if (damOfs != -1)
				size += ((MODEL*)(models_offset + damOfs))->normals;

			if (lowOfs != -1)
				size += ((MODEL*)(models_offset + lowOfs))->poly_block;

			size = (size + 2048) + 2048;
			if (size > specMemReq)
				specMemReq = size;

			size = (damOfs - cleanOfs) + 2048;
			if (size > specMemReq)
				specMemReq = size;

			size = (lowOfs - damOfs) + 2048;
			if (size > specMemReq)
				specMemReq = size;

			if (i != 11)	// what the fuck is this hack about?
			{
				// next model offset?
				size = (offsets[3] - lowOfs) + 2048;

				if(size > specMemReq)
					specMemReq = size;
			}
		}

		offsets += 3;
	}

	for (i = 0; i < 5; i++)
	{
		gCarCleanModelPtr[i] = NULL;
		gCarDamModelPtr[i] = NULL;
		gCarLowModelPtr[i] = NULL;

		if (i == 4)
			specmallocptr = mallocptr;

		model_number = MissionHeader->residentModels[i];

		if (model_number == 13)
		{
			model_number = 10 - (MissionHeader->residentModels[0] + MissionHeader->residentModels[1] + MissionHeader->residentModels[2]);

			if (model_number < 1)
				model_number = 1;
			else if (model_number > 4)
				model_number = 4;
		}

		if (model_number != -1)
		{
			offsets = (int *)(lump_ptr + 4 + model_number * sizeof(int)*3);

			int cleanOfs = offsets[0];
			int damOfs = offsets[1];
			int lowOfs = offsets[2];

			if (cleanOfs != -1)
			{
				MALLOC_BEGIN();
				model = GetCarModel(models_offset + cleanOfs, &mallocptr, 1);
				gCarCleanModelPtr[i] = model;
				MALLOC_END();
			}

			if (damOfs != -1)
			{
				MALLOC_BEGIN();
				model = GetCarModel(models_offset + damOfs, &mallocptr, 0);
				gCarDamModelPtr[i] = model;
				MALLOC_END();
			}

			if (lowOfs != -1)
			{
				MALLOC_BEGIN();
				model = GetCarModel(models_offset + lowOfs, &mallocptr, 1);
				gCarLowModelPtr[i] = model;
				MALLOC_END();
			}
		}
	}

	MALLOC_BEGIN();
	mallocptr = specmallocptr + specMemReq;
	specLoadBuffer = specmallocptr + specMemReq - 2048;
	MALLOC_END();

	buildNewCars();

	return 0;
}



// decompiled code
// original method signature: 
// MODEL * /*$ra*/ GetCarModel(char *src /*$s2*/, char **dest /*$s1*/, int KeepNormals /*$s3*/)
 // line 391, offset 0x00065134
	/* begin block 1 */
		// Start line: 392
		// Start offset: 0x00065134
		// Variables:
	// 		MODEL *model; // $s0
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





