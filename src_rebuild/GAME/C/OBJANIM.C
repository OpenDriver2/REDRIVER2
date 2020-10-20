#include "DRIVER2.H"
#include "OBJANIM.H"
#include "MAP.H"
#include "MODELS.H"
#include "TEXTURE.H"
#include "DEBRIS.H"
#include "CIV_AI.H"
#include "MAIN.H"
#include "MISSION.H"
#include "CARS.H"
#include "PLAYERS.H"
#include "COP_AI.H"
#include "FELONY.H"
#include "SPOOL.H"
#include "SYSTEM.H"
#include "PAUSE.H"
#include "STRINGS.H"

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
	9, 
	5, 
	5, 
	4
};

VECTOR gMissionDoorPosition = { 108000, 0, 4294575046, 0 };

SMASHABLE_OBJECT smashable[] =
{
	{ 0, "CONE_TASTIC", 5, 0, 800 },
	{ 0, "BOX_TASTIC", 4, -6000, 4096 },
	{ 0, "BOX2_TASTIC", 4, -6000, 4096 },
	{ 0, "BOX3_TASTIC", 4, -6000, 4096 },
	{ 0, "CONE1_TASTIC", 5, 0, 800 },
	{ 0, "CONE2_TASTIC", 5, 0, 800 },
	{ 0, "BIN_TASTIC", 7, -6500, 3200 },
	{ 0, "BARRIER_TASTIC", 7, -6500, 3200 },
	{ 0, "BARREL_TASTIC", 6, -3300, 2400 },
	{ 0, "BARREL1_TASTIC", 6, -3300, 2400 },
	{ 0, "BARREL2_TASTIC", 6, -3300, 2400 },
	{ 0, "TABLE_TASTIC", 7, -6500, 3200 },
	{ 0, "BENCH_TASTIC", 7, -6500, 3200 },
	{ 0, "CHAIR_TASTIC", 7, -6500, 3200 },
	{ 0, "CHAIR1_TASTIC", 7, -6500, 3200 },
	{ 0, "CHAIR2_TASTIC", 7, -6500, 3200 },
	{ 0, "UMBRELLA_TASTIC", 7, -6500, 3200 },
	{ 0, "UMBRELLA1_TASTIC", 7, -6500, 3200 },
	{ 0, "PHONE_TASTIC", 6, -3300, 3600 },
	{ 0, "PHONE1_TASTIC", 6, -3300, 3600 },
	{ 0, "SIGN00_TASTIC", 7, -6500, 3200 },
	{ 0, "NEWS_TASTIC", 7, -6500, 3200 },
	{ 0, "PARKING_TASTIC", 6, -7500, 4096 },
	{ 0, "DRINKS_TASTIC", 6, -3300, 3600 },
	{ 0, "FENCE_TASTIC", 7, -6500, 3200 },
	{ 0, "FENCE00_TASTIC", 7, -6500, 3200 },
	{ 0, "FENCE01_TASTIC", 7, -6500, 3200 },
	{ 0, "FENCE02_TASTIC", 7, -6500, 3200 },
	{ 0, "FENCE03_TASTIC", 7, -6500, 3200 },
	{ 0, "FENCE04_TASTIC", 7, -6500, 3200 },
	{ 0, "CONE_TASTIC1", 5, 0, 800 },
	{ 0, "CONE_TASTIC2", 5, 0, 800 },
	{ 0, "CONE_TASTIC3", 5, 0, 800 },
	{ 0, "CONE_TASTIC4", 5, 0, 800 },
	{ 0, "TRAININGCONES1", 5, 0, 800 },
	{ 0, "TRAININGCONES2", 5, 0, 800 },
	{ 0, "TRAININGCONES3", 5, 0, 800 },
	{ 0, 0, 0, 0, 0 }
};


int num_anim_objects = 0;
int num_cycle_obj = 0;

TEXTURE_DETAILS cycle_tex[12];
DR_LOAD cyclecluts[12];

int cycle_phase = 0;
int cycle_timer = 0;


// decompiled code
// original method signature: 
// void /*$ra*/ InitCyclingPals()
 // line 260, offset 0x000149b4
	/* begin block 1 */
		// Start line: 262
		// Start offset: 0x000149B4
		// Variables:
	// 		int i; // $s0
	// 		struct CYCLE_OBJECT *cyc; // $s1
	// 		struct RECT vram; // stack offset -24
	/* end block 1 */
	// End offset: 0x00014A58
	// End Line: 278

	/* begin block 2 */
		// Start line: 520
	/* end block 2 */
	// End Line: 521

	/* begin block 3 */
		// Start line: 1571
	/* end block 3 */
	// End Line: 1572

	/* begin block 4 */
		// Start line: 1575
	/* end block 4 */
	// End Line: 1576

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitCyclingPals(void)
{
	int i;

	num_cycle_obj = Num_LevCycleObjs[GameLevel];
	CYCLE_OBJECT *cyc = Lev_CycleObjPtrs[GameLevel];

	for (i = 0; i < num_cycle_obj; i++)
	{
		GetTextureDetails(cyc->name, &cycle_tex[i]);
		cyc++;
	}

	cycle_phase = 0;
	cycle_timer = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ColourCycle()
 // line 362, offset 0x00013980
	/* begin block 1 */
		// Start line: 365
		// Start offset: 0x00013980
		// Variables:
	// 		int i; // $s5
	// 		struct CYCLE_OBJECT *cyc; // $s2
	// 		struct RECT vram; // stack offset -56
	// 		unsigned short *bufaddr; // $s0
	// 		unsigned short length; // $v0
	// 		unsigned short temp; // $s1

		/* begin block 1.1 */
			// Start line: 388
			// Start offset: 0x00013A4C
			// Variables:
		// 		int tnum; // $a1

			/* begin block 1.1.1 */
				// Start line: 401
				// Start offset: 0x00013AA4
			/* end block 1.1.1 */
			// End offset: 0x00013AEC
			// End Line: 410

			/* begin block 1.1.2 */
				// Start line: 415
				// Start offset: 0x00013B18
			/* end block 1.1.2 */
			// End offset: 0x00013B60
			// End Line: 424
		/* end block 1.1 */
		// End offset: 0x00013C20
		// End Line: 443
	/* end block 1 */
	// End offset: 0x00013C7C
	// End Line: 450

	/* begin block 2 */
		// Start line: 724
	/* end block 2 */
	// End Line: 725

	/* begin block 3 */
		// Start line: 726
	/* end block 3 */
	// End Line: 727

	/* begin block 4 */
		// Start line: 732
	/* end block 4 */
	// End Line: 733

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void ColourCycle(void)
{
	ushort temp;
	ushort* bufaddr;
	CYCLE_OBJECT* cyc;
	int i;
	RECT16 vram;

	if (LoadingArea == 0)
	{
		if ((pauseflag == 0) && (gTimeOfDay == 3))
		{
			vram.w = 16;
			vram.h = 1;
			cyc = Lev_CycleObjPtrs[GameLevel];

			if (num_cycle_obj != 0)
			{
				i = 0;

				while (i < num_cycle_obj)
				{
					bufaddr = (unsigned short*)cyclecluts[i].p;

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
									memmove(bufaddr + cyc->start1, bufaddr + cyc->start1 + 1, (cyc->stop1 - cyc->start1) << 1);

									bufaddr[cyc->stop1] = temp;
								}
							}

							if ((cycle_timer & cyc->speed2) == 0) 
							{
								if (cyc->start2 != -1)
								{
									temp = bufaddr[cyc->start2];
									memmove(bufaddr + cyc->start2, bufaddr + cyc->start2 + 1, (cyc->stop2 - cyc->start2) << 1);

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
					i++;
				}

				if (cycle_phase != 0) 
					cycle_timer++;

				cycle_phase = cycle_phase ^ 1;
			}
		}
	}
	else
	{
		cycle_phase = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ FindSmashableObjects()
 // line 460, offset 0x00014950
	/* begin block 1 */
		// Start line: 462
		// Start offset: 0x00014950
		// Variables:
	// 		struct SMASHABLE_OBJECT *sip; // $s0
	/* end block 1 */
	// End offset: 0x000149A8
	// End Line: 468

	/* begin block 2 */
		// Start line: 1661
	/* end block 2 */
	// End Line: 1662

	/* begin block 3 */
		// Start line: 920
	/* end block 3 */
	// End Line: 921

	/* begin block 4 */
		// Start line: 1662
	/* end block 4 */
	// End Line: 1663

	/* begin block 5 */
		// Start line: 1663
	/* end block 5 */
	// End Line: 1664

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void FindSmashableObjects(void)
{
	SMASHABLE_OBJECT *sip;

	sip = smashable;
	while (sip->name != NULL)
	{
		sip->modelIdx = FindModelIdxWithName(sip->name);
		sip++;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitAnimatingObjects()
 // line 481, offset 0x00013cac
	/* begin block 1 */
		// Start line: 483
		// Start offset: 0x00013CAC
		// Variables:
	// 		struct ANIMATED_OBJECT *aop; // $s1
	// 		int loop; // $s0
	// 		int count1; // $a0
	// 		int count; // $a2
	// 		struct MODEL *modelPtr; // $a0
	/* end block 1 */
	// End offset: 0x00013DF8
	// End Line: 528

	/* begin block 2 */
		// Start line: 1060
	/* end block 2 */
	// End Line: 1061

	/* begin block 3 */
		// Start line: 1061
	/* end block 3 */
	// End Line: 1062

	/* begin block 4 */
		// Start line: 1065
	/* end block 4 */
	// End Line: 1066

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitAnimatingObjects(void)
{
	ANIMATED_OBJECT *aop;

	int loop;
	int count1;
	int count;
	MODEL *modelPtr;

	num_anim_objects = Level_NumAnimatedObjects[GameLevel];
	aop = Level_AnimatingObjectPtrs[GameLevel];

	for (loop = 0; loop < num_anim_objects; loop++)
	{
#if 0
		// Reflections way
		modelPtr = FindModelPtrWithName(aop->name);

		if (modelPtr == NULL)
		{
			aop->model_num = -1;
		}
		else
		{
			// find model number in model pointers
			count = 0;
			while (modelPtr != modelpointers[count])
				count++;

			aop->model_num = count;
			modelPtr->flags2 |= 1;

			for (count1 = num_models_in_pack; count1 != 0; count1--)
			{
				if (modelpointers[count1]->instance_number == count)
					modelpointers[count1]->flags2 |= 1;
			}
		}

		aop++;
#else
		// My way
		int model_idx = FindModelIdxWithName(aop->name);

		if (model_idx != -1 && modelpointers[model_idx] != &dummyModel)
		{
			modelPtr = modelpointers[model_idx];
			modelPtr->flags2 |= 1;

			aop->model_num = model_idx;

			if (modelPtr->instance_number != -1 &&
				modelpointers[modelPtr->instance_number] != &dummyModel)
			{
				modelPtr = modelpointers[modelPtr->instance_number];
				modelPtr->flags2 |= 1;
			}
		}
		else
			aop->model_num = -1;

		aop++;
#endif
	}

#if 1
	char *streetLamps[] = {
		"SLIGHT01",
		NULL,
	};

	int lamp = 0;
	while (streetLamps[lamp] != NULL)
	{
		int model_idx = FindModelIdxWithName(streetLamps[lamp]);

		if (model_idx != -1 && modelpointers[model_idx] != &dummyModel)
		{
			modelPtr = modelpointers[model_idx];
			modelPtr->flags2 |= 0x1000;

			if (modelPtr->instance_number != -1 &&
				modelpointers[modelPtr->instance_number] != &dummyModel)
			{
				modelPtr = modelpointers[modelPtr->instance_number];
				modelPtr->flags2 |= 0x1000;
			}
		}

		lamp++;
	}
#endif

	FindSmashableObjects();
	InitCyclingPals();
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitSpooledAnimObj(int model_number /*$a0*/)
 // line 536, offset 0x00014828
	/* begin block 1 */
		// Start line: 537
		// Start offset: 0x00014828
		// Variables:
	// 		struct ANIMATED_OBJECT *aop; // $a1
	// 		int i; // $a2
	/* end block 1 */
	// End offset: 0x00014898
	// End Line: 551

	/* begin block 2 */
		// Start line: 1072
	/* end block 2 */
	// End Line: 1073

	/* begin block 3 */
		// Start line: 1639
	/* end block 3 */
	// End Line: 1640

// [D]
void InitSpooledAnimObj(int model_number)
{
	int i;
	ANIMATED_OBJECT *aop;

	if (model_number == -1)
		return;

	aop = Level_AnimatingObjectPtrs[GameLevel];

	// Reflections way
	for (i = 0; i < num_anim_objects; i++)
	{
		if (aop->model_num == model_number)
		{
			modelpointers[model_number]->flags2 |= 1;
			break;
		}
		aop++;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ int_garage_door()
 // line 565, offset 0x000149a8
	/* begin block 1 */
		// Start line: 1776
	/* end block 1 */
	// End Line: 1777

	/* begin block 2 */
		// Start line: 1874
	/* end block 2 */
	// End Line: 1875

	/* begin block 3 */
		// Start line: 1875
	/* end block 3 */
	// End Line: 1876

/* WARNING: Unknown calling convention yet parameter storage is locked */

GARAGE_DOOR CurrentGarage;

// [D]
void int_garage_door(void)
{
	CurrentGarage.cop = NULL;
}



// decompiled code
// original method signature: 
// int /*$ra*/ DrawAnimatingObject(struct MODEL *model /*$a0*/, struct CELL_OBJECT *cop /*$s3*/, struct VECTOR *pos /*$a2*/)
 // line 578, offset 0x000148a0
	/* begin block 1 */
		// Start line: 579
		// Start offset: 0x000148A0
		// Variables:
	// 		struct ANIMATED_OBJECT *aop; // $s1
	// 		int loop; // $s2
	// 		int type; // $s0
	/* end block 1 */
	// End offset: 0x00014950
	// End Line: 605

	/* begin block 2 */
		// Start line: 1730
	/* end block 2 */
	// End Line: 1731

	/* begin block 3 */
		// Start line: 1734
	/* end block 3 */
	// End Line: 1735

// [D]
int DrawAnimatingObject(MODEL *model, CELL_OBJECT *cop, VECTOR *pos)
{
	int loop;
	int type;
	ANIMATED_OBJECT *aop;

	aop = Level_AnimatingObjectPtrs[GameLevel];
	type = model->instance_number == -1 ? cop->type : model->instance_number;

	for (loop = 0; loop < num_anim_objects; loop++)
	{
		if (type == aop->model_num)
		{
			animate_object(cop, aop->internal_id);
			break;
		}
		aop++;
	}

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ animate_object(struct CELL_OBJECT *cop /*$s2*/, int type /*$a1*/)
 // line 613, offset 0x00013df8
	/* begin block 1 */
		// Start line: 614
		// Start offset: 0x00013DF8
		// Variables:
	// 		short yang; // $s1
	// 		char phase; // $a0
	/* end block 1 */
	// End offset: 0x000146A4
	// End Line: 896

	/* begin block 2 */
		// Start line: 1268
	/* end block 2 */
	// End Line: 1269

	/* begin block 3 */
		// Start line: 1354
	/* end block 3 */
	// End Line: 1355

// [D]
void animate_object(CELL_OBJECT *cop, int type)
{
	char phase;
	int colour;
	int y;
	int z;
	int x;
	int yang;

	x = (uint)cop->yang * 0x40;

	if (GameLevel == 1) 
	{
		switch (type)
		{
			case 0:
				phase = junctionLightsPhase[x + 0x80U >> 10 & 1];

				if (phase == 2)
				{
					z = -0x1a1;
					colour = -800;
					yang = -0x1e;
					y = 0x400;
				}
				else
				{
					if (2 < phase)
					{
						if (phase != 3) 
						{
							return;
						}

						z = -0x157;
						colour = -800;
						yang = -0x1e;

						goto LAB_000145f0;
					}

					if (phase != 1) 
					{
						return;
					}

					z = -0x1ea;
					colour = -800;
					yang = -0x1e;
					y = 0x200;
				}
				break;
			default:
				return;
			case 2:
				if (gLightsOn == 0)
				{
					return;
				}

				x = 0xe6;
				y = -0x442;
			LAB_00014490:
				AddSmallStreetLight(cop, x, y, 0, 0);
				return;
			case 3:
				if (gLightsOn == 0) 
				{
					return;
				}
				x = -0x265;
				y = -0x7d2;
				goto LAB_00014644;
			case 4:
				if (gLightsOn == 0) 
				{
					return;
				}

				AddLightEffect(cop, -0x250, -2000, 0, 0, 3);
				x = 0x252;
				y = -2000;
				goto LAB_00014418;
		}
		goto LAB_000145f8;
	}

	if (1 < GameLevel)
	{
		if (GameLevel == 2) 
		{
			switch (type)
			{
			case 0:
				phase = junctionLightsPhase[x + 0x80U >> 10 & 1];
				if (phase == 2)
				{
					AddTrafficLight(cop, -0x85c, -0x3fd, -0x41, 0x400, x);
					AddTrafficLight(cop, -0x51e, -0x3d4, -0x41, 0x400, x);
					z = -0x208;
					colour = -0x3ab;
					yang = -0x41;
					y = 0x400;
				}
				else 
				{
					if (phase < 3)
					{
						if (phase != 1)
						{
							return;
						}

						AddTrafficLight(cop, -0x857, -0x458, -0x44, 0x200, x);
						AddTrafficLight(cop, -0x520, -0x421, -0x44, 0x200, x);
						z = -0x202;
						colour = -0x400;
						yang = -0x44;
						y = 0x200;
					}
					else 
					{
						if (phase != 3) 
						{
							return;
						}

						AddTrafficLight(cop, -0x85a, -0x3a9, -0x3e, 0x800, x);
						AddTrafficLight(cop, -0x51d, -0x381, -0x3e, 0x800, x);
						z = -0x206;
						colour = -0x353;
						yang = -0x3e;
						y = 0x800;
					}
				}
				break;
			case 1:
				phase = junctionLightsPhase[x + 0x80U >> 10 & 1];
				if (phase == 2)
				{
					z = -4;
					colour = -0x1d2;
					yang = -0x29;
					y = 0x400;
				}
				else 
				{
					if (2 < phase) 
					{
						if (phase != 3) 
						{
							return;
						}

						z = -4;
						colour = -0x18b;
						yang = -0x29;
						goto LAB_000145f0;
					}
					if (phase != 1) 
					{
						return;
					}

					z = -4;
					colour = -0x219;
					yang = -0x29;
					y = 0x200;
				}
				break;
			case 2:
				if (gLightsOn == 0)
				{
					return;
				}

				x = -0x348;
				y = -0x7b4;
				z = -0x3d;
				goto LAB_00014648;
			case 3:
				if (gLightsOn == 0)
				{
					return;
				}

				AddLightEffect(cop, -0x361, -0x8c9, 0, 0, 3);
				x = 0x361;
				y = -0x8c9;
				goto LAB_00014418;
			case 4:
				if (gLightsOn == 0) 
				{
					return;
				}
				if ((((cop->pos).vx - 0x217e6U < 0xc5ff) && (x = (cop->pos).vz, 0xae29c < x)) && (x < 0xafa9c))
				{
					x = -0x26c;
					y = -0x652;
					goto LAB_00014490;
				}
				x = -0x26c;
				y = -0x652;
				goto LAB_00014644;
			default:
				return;
			}
			goto LAB_000145f8;
		}

		if (GameLevel != 3) 
		{
			return;
		}

		switch (type)
		{
		case 0:
			phase = junctionLightsPhase[x + 0x80U >> 10 & 1];
			if (phase == 2) 
			{
				z = -0x2cf;
				colour = -0x345;
				yang = -0x16;
				y = 0x400;
			}
			else 
			{
				if (2 < phase) 
				{
					if (phase != 3)
					{
						return;
					}

					z = -0x2cf;
					colour = -0x2fa;
					yang = -0x16;
					goto LAB_000145f0;
				}

				if (phase != 1) 
				{
					return;
				}
				z = -0x2cf;
				colour = -0x38a;
				yang = -0x16;
				y = 0x200;
			}
			break;
		case 1:
			phase = junctionLightsPhase[x + 0x80U >> 10 & 1];
			if (phase == 2) 
			{
				z = 0;
				colour = -0x242;
				yang = -0x15;
				y = 0x400;
			}
			else 
			{
				if (2 < phase)
				{
					if (phase != 3) 
					{
						return;
					}
					z = 0;
					colour = -0x1fd;
					yang = -0x15;
					goto LAB_000145f0;
				}
				if (phase != 1)
				{
					return;
				}
				z = 0;
				colour = -0x28e;
				yang = -0x15;
				y = 0x200;
			}
			break;
		case 2:
			if (gLightsOn == 0) 
			{
				return;
			}

			x = -0x1f1;
			y = -0x59d;
			goto LAB_00014644;
		case 3:
			if (gLightsOn == 0) 
			{
				return;
			}

			x = 0;
			y = -0xaa7;
		LAB_00014644:
			z = 0;
		LAB_00014648:
			colour = 3;
			yang = 0;
		LAB_00014650:
			AddLightEffect(cop, x, y, z, yang, colour);
			return;
		case 4:
			if (gLightsOn != 0) 
			{
				AddSmallStreetLight(cop, 0, -0x492, 0, 1);
			}
		default:
			return;
		}
		goto LAB_000145f8;
	}

	if (GameLevel != 0)
	{
		return;
	}

	switch (type) 
	{
	case 0:
	case 7:
		x = (x + 0x400) * 0x10000 >> 0x10;
		phase = junctionLightsPhase[x + 0x80U >> 10 & 1];
		if (phase == 2)
		{
			z = 0;
			colour = -0x284;
			yang = -0x2d;
			y = 0x400;
		}
		else 
		{
			if (phase < 3) 
			{
				if (phase != 1) 
				{
					return;
				}
				z = 0;
				colour = -0x2c4;
				yang = -0x2d;
				y = 0x200;
			}
			else 
			{
				if (phase != 3)
				{
					return;
				}

				z = 0;
				colour = -0x244;
				yang = -0x2d;
			LAB_000145f0:
				y = 0x800;
			}
		}
		break;
	case 1:
	case 8:
		phase = junctionLightsPhase[x + 0x80U >> 10 & 1];
		if (phase == 2) {
			z = 0x196;
			colour = -0x292;
			yang = -0x2e;
			y = 0x400;
		}
		else 
		{
			if (2 < phase) 
			{
				if (phase != 3) 
				{
					return;
				}
				z = 0x196;
				colour = -0x252;
				yang = -0x2e;
				goto LAB_000145f0;
			}

			if (phase != 1)
			{
				return;
			}
			z = 0x196;
			colour = -0x2c4;
			yang = -0x2e;
			y = 0x200;
		}
		break;
	case 2:
	case 3:
		if (gLightsOn == 0)
		{
			return;
		}
		x = 0x1ad;
		y = -0x4d2;
		AddSmallStreetLight(cop, x, y, 0, 1);
		return;
	case 4:
		if (gLightsOn == 0)
		{
			return;
		}
		AddLightEffect(cop, -0x1b0, -0x4d9, 0, 0, 3);
		x = 0x1b0;
		y = -0x4d9;
		goto LAB_00014418;
	case 5:
		if (gLightsOn == 0) 
		{
			return;
		}
		x = 0;
		y = -0x50;
		z = 0;
		colour = 2;
		yang = 2;
		goto LAB_00014650;
	case 6:
		if (gLightsOn == 0)
		{
			return;
		}
		AddLightEffect(cop, 0xea, -0x47a, 0, 0, 3);
		x = -0xea;
		y = -0x47a;
	LAB_00014418:
		AddLightEffect(cop, x, y, 0, 0, 3);
	default:
		return;
	}
LAB_000145f8:
	AddTrafficLight(cop, z, colour, yang, y, x);

}



// decompiled code
// original method signature: 
// void /*$ra*/ animate_garage_door()
 // line 931, offset 0x000146a4
	/* begin block 1 */
		// Start line: 933
		// Start offset: 0x000146A4
		// Variables:
	// 		int dx; // $a0
	// 		int dz; // $v1
	// 		int dist; // $a0
	/* end block 1 */
	// End offset: 0x00014820
	// End Line: 965

	/* begin block 2 */
		// Start line: 1997
	/* end block 2 */
	// End Line: 1998

	/* begin block 3 */
		// Start line: 1998
	/* end block 3 */
	// End Line: 1999

	/* begin block 4 */
		// Start line: 1999
	/* end block 4 */
	// End Line: 2000

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void animate_garage_door(void)
{
	short* psVar1;
	int dz;
	int dx;

	if (CurrentGarage.cop == NULL)
		return;

	int playerCarId = player[0].playerCarId;

	if (gCurrentMissionNumber != 53 && CopsCanSeePlayer != 0)
	{
		if (playerCarId < 0)
			psVar1 = &pedestrianFelony;
		else 
			psVar1 = &car_data[playerCarId].felonyRating;

		if (*psVar1 > FELONY_MIN_VALUE) 
		{
			CurrentGarage.cop->pos = CurrentGarage.old_pos;
			CurrentGarage.cop = NULL;
			return;
		}
	}

	dx = CurrentGarage.old_pos.vx - car_data[playerCarId].hd.where.t[0]; // [A] bug fixe
	dz = CurrentGarage.old_pos.vz - car_data[playerCarId].hd.where.t[2];

	if (dx < 0)
		dx = -dx;

	if (dz < 0)
		dz = -dz;

	if ((dx + dz < 6001) && (gStopPadReads == 0))
	{
		if ((dx + dz < 4000) && (CurrentGarage.old_pos.vy - 400 < CurrentGarage.pos.vy)) 
		{
			CurrentGarage.rotation = CurrentGarage.rotation + 25;
			CurrentGarage.pos.vy = CurrentGarage.pos.vy - 12;
		}
	}
	else if (CurrentGarage.pos.vy < CurrentGarage.old_pos.vy) 
	{
		CurrentGarage.pos.vy = CurrentGarage.pos.vy + 12;
		CurrentGarage.rotation = CurrentGarage.rotation - 25;
	}
}





