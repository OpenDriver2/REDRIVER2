#include "driver2.h"
#include "models.h"
#include "system.h"
#include "spool.h"
#include "mission.h"
#include "cars.h"

#if USE_PC_FILESYSTEM
extern int gContentOverride;
#endif

MODEL dummyModel = { 0 };

char* modelname_buffer = NULL;
char *car_models_lump = NULL;

MODEL* modelpointers[MAX_MODEL_SLOTS];
MODEL* pLodModels[MAX_MODEL_SLOTS];

int num_models_in_pack = 0;

u_short *Low2HighDetailTable = NULL;
u_short *Low2LowerDetailTable = NULL;

// [A]
int permanentModelSlotBitfield[MAX_MODEL_SLOTS / 32];
int litSprites[MAX_MODEL_SLOTS / 32];

// [A] returns freed slot count
int CleanSpooledModelSlots()
{
	int i;
	int num_freed;

	num_freed = 0;

	// assign model pointers
	for (i = 0; i < MAX_MODEL_SLOTS; i++) // [A] bug fix. Init with dummyModel
	{
		// if bit does not indicate usage - reset to dummy model
		if((permanentModelSlotBitfield[i >> 5] & 1 << (i & 31)) == 0)
		{
			if(modelpointers[i] != &dummyModel)
			{
				modelpointers[i] = &dummyModel;
				pLodModels[i] = &dummyModel;
				litSprites[i >> 5] &= ~(1 << (i & 31));

				num_freed++;
			}
		}
	}

	return num_freed;
}

// [A]
void ProcessModel(int modelIdx)
{
	MODEL* model;

	model = modelpointers[modelIdx];
	model->tri_verts = 0; // [A] this is used as additional flags for animated models and triangle processing

	if (gTimeOfDay == TIME_NIGHT)
	{
		if (model->shape_flags & SHAPE_FLAG_SPRITE)
		{
			if (modelIdx != 1223 && (!(model->flags2 & MODEL_FLAG_TREE) || modelIdx == 945 || modelIdx == 497))
				litSprites[modelIdx >> 5] |= 1 << (modelIdx & 31);
		}
	}
}

// [D] [T]
void ProcessMDSLump(char *lump_file, int lump_size)
{
	char* mdsfile;
	MODEL *model;
	MODEL *parentmodel;
	int modelAmts;
	int i, size;
	int litModel;

	modelAmts = *(int *)lump_file;
	mdsfile = (lump_file + 4);
	num_models_in_pack = modelAmts;

	// [A] usage bits
	ClearMem((char*)permanentModelSlotBitfield, sizeof(permanentModelSlotBitfield));
	ClearMem((char*)litSprites, sizeof(litSprites));

	// assign model pointers
	for (i = 0; i < MAX_MODEL_SLOTS; i++) // [A] bug fix. Init with dummyModel
	{
		modelpointers[i] = &dummyModel;
		pLodModels[i] = &dummyModel;
	}

	for (i = 0; i < modelAmts; i++)
	{
		size = *(int*)mdsfile;
		mdsfile += sizeof(int);

		if (size)
		{
			// add the usage bit
			permanentModelSlotBitfield[i >> 5] |= 1 << (i & 31);
			
			model = (MODEL*)mdsfile;
			modelpointers[i] = model;

			ProcessModel(i);
		}

		mdsfile += size;
	}

	// process parent instances
	for (i = 0; i < modelAmts; i++)
	{
		model = modelpointers[i];
		if (model->instance_number != -1) 
		{
			parentmodel = modelpointers[model->instance_number];
#if MODEL_RELOCATE_POINTERS
			// convert to real offsets
			model->vertices = (int)(char*)parentmodel + parentmodel->vertices;
			model->normals = (int)(char*)parentmodel + parentmodel->normals;
			model->point_normals = (int)(char*)parentmodel + parentmodel->point_normals;
			if (parentmodel->collision_block != 0)
				model->collision_block = (int)(char*)parentmodel + parentmodel->collision_block;
#endif
		}
	}

#if MODEL_RELOCATE_POINTERS
	// process models without parents
	for (i = 0; i < modelAmts; i++)
	{
		model = modelpointers[i];
		model->poly_block += (int)(char*)model;

		if (model->instance_number == -1) 
		{
			model->vertices += (int)model;
			model->normals += (int)model;
			model->point_normals += (int)model;

			if (model->collision_block != 0)
				model->collision_block += (int)model;
		}
	}
#endif
}

char* _MDL_GETTER_vertices(MODEL* mdl)
{
	if (mdl->instance_number != -1)
		mdl = modelpointers[mdl->instance_number];
	return (char*)mdl + mdl->vertices;
}

char* _MDL_GETTER_normals(MODEL* mdl)
{
	if (mdl->instance_number != -1)
		mdl = modelpointers[mdl->instance_number];
	return (char*)mdl + mdl->normals;
}

char* _MDL_GETTER_point_normals(MODEL* mdl)
{
	if (mdl->instance_number != -1)
		mdl = modelpointers[mdl->instance_number];
	return (char*)mdl + mdl->point_normals;
}

char* _MDL_GETTER_collision_block(MODEL* mdl)
{
	if (mdl->instance_number != -1)
		mdl = modelpointers[mdl->instance_number];
	return (char*)mdl + mdl->collision_block;
}

// [D] [T]
int ProcessCarModelLump(char *lump_ptr, int lump_size)
{
	int size;
	int* offsets;
	char* models_offset;
	char* mem;
	MODEL* model;
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

	startBuildNewCars(0);

	for (i = 0; i < MAX_CAR_MODELS; i++)
	{
		gCarCleanModelPtr[i] = NULL;
		gCarDamModelPtr[i] = NULL;
		gCarLowModelPtr[i] = NULL;

		if (i == MAX_CAR_MODELS-1)
		{
			startBuildNewCars(1);
			specmallocptr = (char*)mallocptr;
		}

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

#if USE_PC_FILESYSTEM
			if (gContentOverride)
			{
				if (mem = LoadCarModelFromFile(NULL, model_number, CAR_MODEL_CLEAN))
				{
					D_MALLOC_BEGIN();
					model = GetCarModel(mem, (char**)&mallocptr, 1);
					D_MALLOC_END();

					gCarCleanModelPtr[i] = model;
					buildNewCarFromModel(i, 0, mem, model);
					cleanOfs = -1; // skip loading
				}

				if (mem = LoadCarModelFromFile(NULL, model_number, CAR_MODEL_DAMAGED))
				{
					D_MALLOC_BEGIN();
					model = GetCarModel(mem, (char**)&mallocptr, 1);
					D_MALLOC_END();

					gCarDamModelPtr[i] = model;
					damOfs = -1; // skip loading
				}

				if (mem = LoadCarModelFromFile(NULL, model_number, CAR_MODEL_LOWDETAIL))
				{
					D_MALLOC_BEGIN();
					model = GetCarModel(mem, (char**)&mallocptr, 1);
					D_MALLOC_END();

					gCarLowModelPtr[i] = model;
					buildNewCarFromModel(i, 0, mem, model);
					lowOfs = -1; // skip loading
				}
			}
#endif
			
			if (cleanOfs != -1)
			{
				D_MALLOC_BEGIN();
				mem = models_offset + cleanOfs;
				model = GetCarModel(mem, (char**)&mallocptr, 1);

				gCarCleanModelPtr[i] = model;
				buildNewCarFromModel(i, 1, mem, model);

				D_MALLOC_END();
			}

			if (damOfs != -1)
			{
				D_MALLOC_BEGIN();
				mem = models_offset + damOfs;
				model = GetCarModel(mem, (char**)&mallocptr, 0);

				gCarDamModelPtr[i] = model;
				D_MALLOC_END();
			}
			
			if (lowOfs != -1)
			{
				D_MALLOC_BEGIN();
				mem = models_offset + lowOfs;
				model = GetCarModel(mem, (char**)&mallocptr, 1);

				gCarLowModelPtr[i] = model;
				buildNewCarFromModel(i, 0, mem, model);
				D_MALLOC_END();
			}
		}
	}

	D_MALLOC_BEGIN();

#if USE_PC_FILESYSTEM
	if (gContentOverride)
	{
		// extra spool memory needed
		specMemReq += 4096;
	}
#endif

	mallocptr = specmallocptr + specMemReq;
	specLoadBuffer = specmallocptr + specMemReq - 2048;
	D_MALLOC_END();

	return 0;
}

// [D] [T]
MODEL* FindModelPtrWithName(char *name)
{
	int idx;
	idx = FindModelIdxWithName(name);

	return idx >= 0 ? modelpointers[idx] : NULL;
}

// [D] [T]
int FindModelIdxWithName(char *name)
{
	char *str;
	int i;

	i = 0;
	str = modelname_buffer;

	while (i < num_models_in_pack)
	{
		if (!strcmp(str, name))
			return i;

		while (*str++) {} // go to next string

		i++;
	}

	return -1;
}
