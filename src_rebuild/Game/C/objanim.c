#include "driver2.h"
#include "objanim.h"
#include "map.h"
#include "models.h"
#include "texture.h"
#include "debris.h"
#include "civ_ai.h"
#include "main.h"
#include "mission.h"
#include "cars.h"
#include "players.h"
#include "cop_ai.h"
#include "felony.h"
#include "spool.h"
#include "system.h"
#include "pause.h"

struct ANIMATED_OBJECT
{
	int internal_id;
	int model_num;
	char* name;
	char LitPoly;
};

struct GARAGE_DOOR
{
	CELL_OBJECT* cop;
	VECTOR_NOPAD old_pos;
	VECTOR_NOPAD pos;
	short rotation;
	char yang;
};

struct CYCLE_OBJECT
{
	char* name;
	short vx, vy;
	short start1, stop1, speed1;
	short start2, stop2, speed2;
};

CYCLE_OBJECT Lev0[2] =
{
	{ "REDRVR", 0, 0, 6, 10, 2, 11, 15, 2 },
	{ "NAVPIR34", 0, 0, 0, 6, 0, 7, 13, 0 }
};

CYCLE_OBJECT Lev1[] = {
	{ "DOOR11", 0, 0, 1, 7, 2, 8, 14, 3 },
};

CYCLE_OBJECT Lev2[12] =
{
	{ "DTSYN01", 0, 0, 0, 3, 0, 4, 14, 0 },
	{ "DTSYN02", 0, 0, 0, 15, 0, -1, -1, 0 },
	{ "F-MTSYN2", 0, 0, 0, 3, 0, 10, 14, 0 },
	{ "DTSYN03", 0, 0, 0, 3, 0, -1, -1, 0 },
	{ "SYN-CAS1", 0, 0, 0, 3, 0, 4, 14, 0 },
	{ "SYNSLOT", 0, 0, 0, 3, 0, 4, 7, 0 },
	{ "ENT1B", 0, 0, 0, 15, 0, -1, -1, 0 },
	{ "FLAMINGO", 0, 0, 0, 3, 0, 9, 12, 0 },
	{ "CYCLE-01", 0, 0, 0, 5, 1, 6, 11, 1 },
	{ "CYCLE-02", 0, 0, 0, 3, 3, -1, -1, 0 },
	{ "CYCLE-03", 0, 0, 0, 6, 7, 7, 13, 7 },
	{ "CYCLE-04", 0, 0, 0, 6, 15, 7, 13, 15 }
};

CYCLE_OBJECT Lev3[] = {
	{ "FWING11", 0, 0, 1, 7, 2, 8, 14, 3 }
};


CYCLE_OBJECT* Lev_CycleObjPtrs[] = {
	Lev0,
	Lev1,
	Lev2,
	Lev3
};

int Num_LevCycleObjs[] = { 2, 0, 12, 0 };

ANIMATED_OBJECT Lev0AnimObjects[9] =
{
	{ 0, 0, "TLIGHT01", 0 },
	{ 1, 0, "TLIGHT02", 0 },
	{ 2, 0, "SLIGHT01", 1 },
	{ 3, 0, "LOW_SLIGHT01", 1 },
	{ 4, 0, "DLIGHT01", 1 },
	{ 5, 0, "STRUT", 0 },
	{ 6, 0, "NPLIGHT", 0 },
	{ 7, 0, "TLIGHT01_LOW", 0 },
	{ 8, 0, "TLIGHT02_LOW", 0 }
};

ANIMATED_OBJECT Lev1AnimObjects[5] =
{
	{ 0, 0, "TLIGHT1", 0 },
	{ 1, 0, "TLIGHT2", 0 },
	{ 2, 0, "SLIGHT1", 1 },
	{ 3, 0, "SLIGHT2", 1 },
	{ 4, 0, "DLIGHT1", 1 }
};

ANIMATED_OBJECT Lev2AnimObjects[5] =
{
	{ 0, 0, "TLIGHT01", 0 },
	{ 1, 0, "TLIGHT02", 0 },
	{ 2, 0, "SLIGHT01", 1 },
	{ 3, 0, "DLIGHT01", 1 },
	{ 4, 0, "SLIGHT02", 1 }
};

ANIMATED_OBJECT Lev3AnimObjects[4] =
{
	{ 0, 0, "TLIGHT01", 0 },
	{ 1, 0, "TLIGHT02", 0 },
	{ 2, 0, "SLIGHT01", 0 },
	{ 3, 0, "MLIGHT01", 0 }
};

ANIMATED_OBJECT* Level_AnimatingObjectPtrs[] = {
	Lev0AnimObjects,
	Lev1AnimObjects,
	Lev2AnimObjects,
	Lev3AnimObjects
};

int Level_NumAnimatedObjects[] = {
	numberOf(Lev0AnimObjects),
	numberOf(Lev1AnimObjects),
	numberOf(Lev2AnimObjects),
	numberOf(Lev3AnimObjects)
};

// sound ids for SOUND_BANK_SFX
SMASHABLE_OBJECT smashable[] =
{
	{ 0, "", 1, 0, 800 },		// default
	{ 0, "CONE_TASTIC", 1, 0, 1400 },
	{ 0, "CONE1_TASTIC", 1, 0, 1400 },
	{ 0, "CONE2_TASTIC", 1, 0, 1400 },
	{ 0, "BOX_TASTIC", 0, -6000, 4096 },
	{ 0, "BOX2_TASTIC", 0, -6000, 4096 },
	{ 0, "BOX3_TASTIC", 0, -6000, 4096 },
	{ 0, "BIN_TASTIC", 3, -6500, 3200 },
	{ 0, "BARRIER_TASTIC", 3, -6500, 3200 },
	{ 0, "BARRIER1_TASTIC", 3, -6500, 3200 },
	{ 0, "BARREL_TASTIC", 2, -3300, 2400 },
	{ 0, "BARREL1_TASTIC", 2, -3300, 2400 },
	{ 0, "BARREL2_TASTIC", 2, -3300, 2400 },
	{ 0, "TABLE_TASTIC", 3, -6500, 3200 },
	{ 0, "BENCH_TASTIC", 3, -6500, 3200 },
	{ 0, "CHAIR_TASTIC", 3, -6500, 3200 },
	{ 0, "CHAIR1_TASTIC", 3, -6500, 3200 },
	{ 0, "CHAIR2_TASTIC", 3, -6500, 3200 },
	{ 0, "UMBRELLA_TASTIC", 3, -6500, 3200 },
	{ 0, "UMBRELLA1_TASTIC", 3, -6500, 3200 },
	{ 0, "PHONE_TASTIC", 2, -3300, 3600 },
	{ 0, "PHONE1_TASTIC", 2, -3300, 3600 },
	{ 0, "SIGN00_TASTIC", 3, -6500, 3200 },
	{ 0, "NEWS_TASTIC", 3, -6500, 3200 },
	{ 0, "PARKING_TASTIC", 2, -7500, 4096 },
	{ 0, "DRINKS_TASTIC", 2, -3300, 3600 },
	{ 0, "FENCE_TASTIC", 3, -6500, 3200 },
	{ 0, "FENCE00_TASTIC", 3, -6500, 3200 },
	{ 0, "FENCE01_TASTIC", 3, -6500, 3200 },
	{ 0, "FENCE02_TASTIC", 3, -6500, 3200 },
	{ 0, "FENCE03_TASTIC", 3, -6500, 3200 },
	{ 0, "FENCE04_TASTIC", 3, -6500, 3200 },
	{ 0, "CONE_TASTIC1", 1, 0, 800 },
	{ 0, "CONE_TASTIC2", 1, 0, 800 },
	{ 0, "CONE_TASTIC3", 1, 0, 800 },
	{ 0, "CONE_TASTIC4", 1, 0, 800 },
	{ 0, 0, 0, 0, 0 }
};


int num_anim_objects = 0;
int num_cycle_obj = 0;

TEXTURE_DETAILS cycle_tex[12];
DR_LOAD cyclecluts[12];

int cycle_phase = 0;
int cycle_timer = 0;

// [D] [T]
void InitCyclingPals(void)
{
	int i;

	// only enabled at Night
	if (gTimeOfDay != 3)
	{
		num_cycle_obj = 0;
		return;
	}
	
	num_cycle_obj = Num_LevCycleObjs[GameLevel];
	CYCLE_OBJECT* cyc = Lev_CycleObjPtrs[GameLevel];

	for (i = 0; i < num_cycle_obj; i++)
	{
		GetTextureDetails(cyc->name, &cycle_tex[i]);
		cyc++;
	}

	cycle_phase = 0;
	cycle_timer = 0;
}

// [D] [T]
void ColourCycle(void)
{
	ushort temp;
	ushort* bufaddr;
	CYCLE_OBJECT* cyc;
	int i;
	RECT16 vram;

	if (!num_cycle_obj)
		return;

	if (LoadingArea != 0)
	{
		cycle_phase = 0;
		return;
	}

	vram.w = 16;
	vram.h = 1;
	cyc = Lev_CycleObjPtrs[GameLevel];
		
	for (i = 0; i < num_cycle_obj; i++)
	{
		bufaddr = (u_short*)cyclecluts[i].p;

		if (tpageloaded[cycle_tex[i].texture_page] != 0)
		{
			if (cycle_phase == 0)
			{
				// initialize
				temp = texture_cluts[cycle_tex[i].texture_page][cycle_tex[i].texture_number];

				cyc->vx = vram.x = (temp & 0x3f) << 4;
				cyc->vy = vram.y = (temp >> 6);

				StoreImage(&vram, (u_long*)bufaddr);
			}
			else
			{
				if ((cycle_timer & cyc->speed1) == 0)
				{
					if (cyc->start1 != -1)
					{
						temp = bufaddr[cyc->start1];
						memmove((u_char*)(bufaddr + cyc->start1), (u_char*)(bufaddr + cyc->start1 + 1), (cyc->stop1 - cyc->start1) << 1);

						bufaddr[cyc->stop1] = temp;
					}
				}

				if ((cycle_timer & cyc->speed2) == 0)
				{
					if (cyc->start2 != -1)
					{
						temp = bufaddr[cyc->start2];
						memmove((u_char*)(bufaddr + cyc->start2), (u_char*)(bufaddr + cyc->start2 + 1), (cyc->stop2 - cyc->start2) << 1);

						bufaddr[cyc->stop2] = temp;
					}
				}

				vram.x = cyc->vx;
				vram.y = cyc->vy;

				SetDrawLoad(&cyclecluts[i], &vram);

				addPrim(current->ot, &cyclecluts[i]);
			}
		}

		cyc++;
	}

	if (cycle_phase != 0)
		cycle_timer++;

	cycle_phase ^= 1;
}


// [D] [T]
void FindSmashableObjects(void)
{
	SMASHABLE_OBJECT* sip;

	sip = smashable;
	while (sip->name != NULL)
	{
		sip->modelIdx = FindModelIdxWithName(sip->name);
		sip++;
	}
}

// [D] [T]
void InitAnimatingObjects(void)
{
	ANIMATED_OBJECT* aop;

	int loop;
	MODEL* modelPtr;

	num_anim_objects = Level_NumAnimatedObjects[GameLevel];
	aop = Level_AnimatingObjectPtrs[GameLevel];

	for (loop = 0; loop < num_anim_objects; loop++)
	{
		// My way
		int model_idx = FindModelIdxWithName(aop->name);

		if (model_idx != -1 && modelpointers[model_idx] != &dummyModel)
		{
			modelPtr = modelpointers[model_idx];
			modelPtr->flags2 |= MODEL_FLAG_ANIMOBJ;

			if (aop->LitPoly)
				modelPtr->flags2 |= MODEL_FLAG_LAMP;
			
			aop->model_num = model_idx;

			// [A] store animated object number in normals pointer
			// after all it was always unused
			modelPtr->normals = loop;

			if (modelPtr->instance_number != -1 &&
				modelpointers[modelPtr->instance_number] != &dummyModel)
			{
				modelPtr = modelpointers[modelPtr->instance_number];
				modelPtr->flags2 |= MODEL_FLAG_ANIMOBJ;

				if (aop->LitPoly)
					modelPtr->flags2 |= MODEL_FLAG_LAMP;

				// [A] store animated object number in normals pointer
				// after all it was always unused
				modelPtr->normals = loop;
			}
		}
		else
			aop->model_num = -1;

		aop++;
	}

	FindSmashableObjects();
}

// [D] [T]
void InitSpooledAnimObj(int model_number)
{
	int i;
	ANIMATED_OBJECT* aop;
	MODEL* modelPtr;

	if (model_number == -1)
		return;

	aop = Level_AnimatingObjectPtrs[GameLevel];

	// Reflections way
	for (i = 0; i < num_anim_objects; i++)
	{
		if (aop->model_num == model_number)
		{
			modelPtr = modelpointers[model_number];
			modelPtr->flags2 |= MODEL_FLAG_ANIMOBJ;

			if (aop->LitPoly)
				modelPtr->flags2 |= MODEL_FLAG_LAMP;

			// [A] store animated object number in normals pointer
			// after all it was always unused
			modelPtr->normals = i;
			
			break;
		}
		aop++;
	}
}

GARAGE_DOOR CurrentGarage;

// [D] [T]
void int_garage_door(void)
{
	CurrentGarage.cop = NULL;
}

// [A] [T]
void DrawAllAnimatingObjects(CELL_OBJECT** objects, int num_animated)
{
	ANIMATED_OBJECT* aop;
	CELL_OBJECT* cop;
	MODEL* model;
	int i, j;
	int type;

	aop = Level_AnimatingObjectPtrs[GameLevel];

	for (i = 0; i < num_animated; i++)
	{
		cop = objects[i];
		type = cop->type;
		model = modelpointers[type];

		// [A] optimized
		animate_object(cop, aop[model->normals].internal_id);
		
#if 0
		type = model->instance_number == -1 ? type : model->instance_number;
		for (j = 0; j < num_anim_objects; j++)
		{
			if (type == aop->model_num)
			{
				animate_object(cop, aop->internal_id);
				aop -= j;
				break;
			}

			aop++;
		}
#endif
	}
}

// [D] [T]
void animate_object(CELL_OBJECT* cop, int type)
{
	char phase;
	int yang;

	yang = cop->yang * 64;

	// [A] Rev 1.1 has less of those types

	if (GameLevel == 0)
	{
		switch (type)
		{
			case 0:
			case 7:
				yang += 1024;
				phase = junctionLightsPhase[yang + 128 >> 10 & 1];

				if (phase == 1)
				{
					AddTrafficLight(cop, 0, -0x2c4, -0x2d, 0x200, yang);
				}
				else if (phase == 2)
				{
					AddTrafficLight(cop, 0,  -0x284, -0x2d, 0x400, yang);
				}
				else if (phase == 3)
				{
					AddTrafficLight(cop, 0, -0x244, -0x2d, 0x800, yang);
				}
				break;
			case 1:
			case 8:
				phase = junctionLightsPhase[yang + 128 >> 10 & 1];

				if (phase == 1)
				{
					AddTrafficLight(cop, 0x196, -0x2c4, -0x2e, 0x200, yang);
				}
				else if (phase == 2)
				{
					AddTrafficLight(cop, 0x196, -0x292, -0x2e, 0x400, yang);
				}
				else if (phase == 3)
				{
					AddTrafficLight(cop,  0x196, -0x252, -0x2e, 0x800, yang);
				}
				break;
			case 2:
			case 3:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, 0x1ad, -0x4d2, 0, 0, 3);
				break;
			case 4:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, -0x1b0, -0x4d9, 0, 0, 3);
				AddLightEffect(cop, 0x1b0, -0x4d9, 0, 0, 3);
				break;
			case 5:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, 0, -0x50, 0, 2, 2);
				break;
			case 6:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, 0xea, -0x47a, 0, 0, 3);
				AddLightEffect(cop,  -0xea, -0x47a, 0, 0, 3);
		}
	}
	else if (GameLevel == 1)
	{
		switch (type)
		{
			case 0:
				phase = junctionLightsPhase[yang + 128 >> 10 & 1];

				if (phase == 2)
				{
					AddTrafficLight(cop, -0x1a1, -800, -0x1e, 0x400, yang);
				}
				else if (phase == 1)
				{
					AddTrafficLight(cop, -0x1ea, -800, -0x1e, 0x200, yang);
				}
				else if (phase == 3)
				{
					AddTrafficLight(cop, -0x157, -800, -0x1e, 0x800, yang);
				}

				break;
			case 2:
				if (gLightsOn == 0)
					break;

				AddSmallStreetLight(cop, 0xe6, -0x442, 0, 0);
				break;
			case 3:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, -0x265, -0x7d2, 0, 0, 3);
				break;
			case 4:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, -0x250, -2000, 0, 0, 3);
				AddLightEffect(cop, 0x252, -2000, 0, 0, 3);
				break;
		}
	}
	else if (GameLevel == 2)
	{
		switch (type)
		{
			case 0:
				phase = junctionLightsPhase[yang + 128 >> 10 & 1];
			
				if (phase == 1)
				{
					AddTrafficLight(cop, -0x857, -0x458, -0x44, 0x200, yang);
					AddTrafficLight(cop, -0x520, -0x421, -0x44, 0x200, yang);
					AddTrafficLight(cop, -0x202, -0x400, -0x44, 0x200, yang);
				}
				else if (phase == 2)
				{
					AddTrafficLight(cop, -0x85c, -0x3fd, -0x41, 0x400, yang);
					AddTrafficLight(cop, -0x51e, -0x3d4, -0x41, 0x400, yang);
					AddTrafficLight(cop, -0x208, -0x3ab, -0x41, 0x400, yang);
				}
				else if (phase == 3)
				{
					AddTrafficLight(cop, -0x85a, -0x3a9, -0x3e, 0x800, yang);
					AddTrafficLight(cop, -0x51d, -0x381, -0x3e, 0x800, yang);
					AddTrafficLight(cop, -0x206, -0x353, -0x3e, 0x800, yang);
				}
				break;
			case 1:
				phase = junctionLightsPhase[yang + 128 >> 10 & 1];

				if (phase == 1)
				{
					AddTrafficLight(cop, -4, -0x219, -0x29, 0x200, yang);
				}
				else if (phase == 2)
				{
					AddTrafficLight(cop, -4, -0x1d2, -0x29, 0x400, yang);
				}
				else if (phase == 3)
				{
					AddTrafficLight(cop, -4, -0x18b, -0x29, 0x800, yang);
				}
				break;
			case 2:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, -0x348, -0x7b4, -0x3d, 0, 3);
				break;
			case 3:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, -0x361, -0x8c9, 0, 0, 3);
				AddLightEffect(cop, 0x361, -0x8c9, 0, 0, 3);
				break;
			case 4:
				if (gLightsOn == 0)
					break;

				if (cop->pos.vx - 137190U < 50687 && cop->pos.vz > 713372 && cop->pos.vz < 719516)
				{
					AddSmallStreetLight(cop, -0x26c, -0x65, 0, 0);
					break;
				}
			
				AddLightEffect(cop, -0x26c, -0x652, 0, 0, 3);
				break;
		}
	}
	else if (GameLevel == 3)
	{
		switch (type)
		{
			case 0:
				phase = junctionLightsPhase[yang + 128 >> 10 & 1];
			
				if (phase == 1)
				{
					AddTrafficLight(cop, -0x2cf, -0x38a, -0x16, 0x200, yang);
				}
				else if (phase == 2)
				{
					AddTrafficLight(cop, -0x2cf, -0x345, -0x16, 0x400, yang);
				}
				else if (phase == 3)
				{
					AddTrafficLight(cop, -0x2cf, -0x2fa, -0x16, 0x800, yang);
				}
				break;
			case 1:
				phase = junctionLightsPhase[yang + 128 >> 10 & 1];

				if (phase == 1)
				{
					AddTrafficLight(cop, 0, -0x28e, -0x15, 0x200, yang);
				}
				else if (phase == 2)
				{
					AddTrafficLight(cop, 0, -0x242, -0x15, 0x400, yang);
				}
				else if (phase == 3)
				{
					AddTrafficLight(cop, 0, -0x1fd, -0x15, 0x800, yang);
				}
				break;
			case 2:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, -0x1f1, -0x59d, 0, 0, 3);

				break;
			case 3:
				if (gLightsOn == 0)
					break;

				AddLightEffect(cop, 0,  -0xaa7, 0, 0, 3);
			
				break;
			case 4:
				if (gLightsOn == 0)
					break;

				AddSmallStreetLight(cop, 0, -0x492, 0, 1);
				break;
		}
	}
}


// [D] [T]
void animate_garage_door(void)
{
	short* felony;
	int dz;
	int dx;

	if (CurrentGarage.cop == NULL)
		return;

	int playerCarId = player[0].playerCarId;

	if (gCurrentMissionNumber != 53 && CopsCanSeePlayer)
	{
		if (playerCarId < 0)
			felony = &pedestrianFelony;
		else
			felony = &car_data[playerCarId].felonyRating;

		if (*felony > FELONY_PURSUIT_MIN_VALUE)
		{
			CurrentGarage.cop->pos = CurrentGarage.old_pos;
			CurrentGarage.cop = NULL;
			return;
		}
	}

	dx = ABS(CurrentGarage.old_pos.vx - car_data[playerCarId].hd.where.t[0]); // [A] bug fix
	dz = ABS(CurrentGarage.old_pos.vz - car_data[playerCarId].hd.where.t[2]);

	if (dx + dz > 6000 || gStopPadReads != 0)
	{
		if (CurrentGarage.pos.vy < CurrentGarage.old_pos.vy)
		{
			CurrentGarage.rotation -= 25;
			CurrentGarage.pos.vy += 12;
		}
	}
	else
	{
		if (dx + dz < 4000 && CurrentGarage.pos.vy > CurrentGarage.old_pos.vy - 400)
		{
			CurrentGarage.rotation += 25;
			CurrentGarage.pos.vy -= 12;
		}
	}
}





