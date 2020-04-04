#include "THISDUST.H"
#include "OBJANIM.H"


CYCLE_OBJECT Lev0[2] =
{
  { "REDRVR", 0, 0, 6, 10, 2, 11, 15, 2 },
  { "NAVPIR34", 0, 0, 0, 6, 0, 7, 13, 0 }
};

CYCLE_OBJECT Lev1[] = {
	{ "DOOR11", 0, 0, 1, 7, 2, 8, 14, 3 } ,
};

CYCLE_OBJECT Lev2[12] =
{
  { "DTSYN01", 0, 0, 0, 3, 0, 4, 14, 0 },
  { "DTSYN02", 0, 0, 0, 15, 0, 65535, 65535, 0 },
  { "F-MTSYN2", 0, 0, 0, 3, 0, 10, 14, 0 },
  { "DTSYN03", 0, 0, 0, 3, 0, 65535, 65535, 0 },
  { "SYN-CAS1", 0, 0, 0, 3, 0, 4, 14, 0 },
  { "SYNSLOT", 0, 0, 0, 3, 0, 4, 7, 0 },
  { "ENT1B", 0, 0, 0, 15, 0, 65535, 65535, 0 },
  { "FLAMINGO", 0, 0, 0, 3, 0, 9, 12, 0 },
  { "CYCLE-01", 0, 0, 0, 5, 1, 6, 11, 1 },
  { "CYCLE-02", 0, 0, 0, 3, 3, 65535, 65535, 0 },
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
  { 0, 0, "TLIGHT01", '\0' },
  { 1, 0, "TLIGHT02", '\0' },
  { 2, 0, "SLIGHT01", '\x01' },
  { 3, 0, "LOW_SLIGHT01", '\x01' },
  { 4, 0, "DLIGHT01", '\x01' },
  { 5, 0, "STRUT", '\0' },
  { 6, 0, "NPLIGHT", '\0' },
  { 7, 0, "TLIGHT01_LOW", '\0' },
  { 8, 0, "TLIGHT02_LOW", '\0' }
};

ANIMATED_OBJECT Lev1AnimObjects[5] =
{
  { 0, 0, "TLIGHT1", '\0' },
  { 1, 0, "TLIGHT2", '\0' },
  { 2, 0, "SLIGHT1", '\x01' },
  { 3, 0, "SLIGHT2", '\x01' },
  { 4, 0, "DLIGHT1", '\x01' }
};

ANIMATED_OBJECT Lev2AnimObjects[5] =
{
  { 0, 0, "TLIGHT01", '\0' },
  { 1, 0, "TLIGHT02", '\0' },
  { 2, 0, "SLIGHT01", '\x01' },
  { 3, 0, "DLIGHT01", '\x01' },
  { 4, 0, "SLIGHT02", '\x01' }
};

ANIMATED_OBJECT Lev3AnimObjects[4] =
{
  { 0, 0, "TLIGHT01", '\0' },
  { 1, 0, "TLIGHT02", '\0' },
  { 2, 0, "SLIGHT01", '\x01' },
  { 3, 0, "MLIGHT01", '\x01' }
};

ANIMATED_OBJECT* Level_AnimatingObjectPtrs[] = { Lev0AnimObjects, Lev1AnimObjects, Lev2AnimObjects, Lev3AnimObjects };

VECTOR gMissionDoorPosition = { 108000, 0, 4294575046, 0 };

SMASHABLE_OBJECT smashable[] =
{
  { 0, "CONE_TASTIC", 5, 0, 800 },
  { 0, "BOX_TASTIC", 4, 4294961296, 4096 },
  { 0, "BOX2_TASTIC", 4, 4294961296, 4096 },
  { 0, "BOX3_TASTIC", 4, 4294961296, 4096 },
  { 0, "CONE1_TASTIC", 5, 0, 800 },
  { 0, "CONE2_TASTIC", 5, 0, 800 },
  { 0, "BIN_TASTIC", 7, 4294960796, 3200 },
  { 0, "BARRIER_TASTIC", 7, 4294960796, 3200 },
  { 0, "BARREL_TASTIC", 6, 4294963996, 2400 },
  { 0, "BARREL1_TASTIC", 6, 4294963996, 2400 },
  { 0, "BARREL2_TASTIC", 6, 4294963996, 2400 },
  { 0, "TABLE_TASTIC", 7, 4294960796, 3200 },
  { 0, "BENCH_TASTIC", 7, 4294960796, 3200 },
  { 0, "CHAIR_TASTIC", 7, 4294960796, 3200 },
  { 0, "CHAIR1_TASTIC", 7, 4294960796, 3200 },
  { 0, "CHAIR2_TASTIC", 7, 4294960796, 3200 },
  { 0, "UMBRELLA_TASTIC", 7, 4294960796, 3200 },
  { 0, "UMBRELLA1_TASTIC", 7, 4294960796, 3200 },
  { 0, "PHONE_TASTIC", 6, 4294963996, 3600 },
  { 0, "PHONE1_TASTIC", 6, 4294963996, 3600 },
  { 0, "SIGN00_TASTIC", 7, 4294960796, 3200 },
  { 0, "NEWS_TASTIC", 7, 4294960796, 3200 },
  { 0, "PARKING_TASTIC", 6, 4294959796, 4096 },
  { 0, "DRINKS_TASTIC", 6, 4294963996, 3600 },
  { 0, "FENCE_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE00_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE01_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE02_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE03_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE04_TASTIC", 7, 4294960796, 3200 },
  { 0, "CONE_TASTIC1", 5, 0, 800 },
  { 0, "CONE_TASTIC2", 5, 0, 800 },
  { 0, "CONE_TASTIC3", 5, 0, 800 },
  { 0, "CONE_TASTIC4", 5, 0, 800 },
  { 0, "TRAININGCONES1", 5, 0, 800 },
  { 0, "TRAININGCONES2", 5, 0, 800 },
  { 0, "TRAININGCONES3", 5, 0, 800 },
  { 0, 0, 0, 0, 0 }
};


int Level_NumAnimatedObjects[] = { 9, 5, 5, 4, 0, 6, 0, 0 };

char* texture_pages = 0;	// some big empty array
char* texture_cluts = 0;	// some big empty array


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

void InitCyclingPals(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	char **ppcVar2;
	TEXTURE_DETAILS *info;

	num_cycle_obj = Num_LevCycleObjs[GameLevel];
	ppcVar2 = (char **)Lev_CycleObjPtrs4[GameLevel];
	if ((num_cycle_obj != 0) && (iVar1 = 0, 0 < num_cycle_obj)) {
		info = &cycle_tex;
		do {
			iVar1 = iVar1 + 1;
			GetTextureDetails(*ppcVar2, info);
			ppcVar2 = ppcVar2 + 5;
			info = info + 1;
		} while (iVar1 < num_cycle_obj);
	}
	cycle_phase = 0;
	cycle_timer = 0;
	return;
	*/
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

void ColourCycle(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte bVar2;
	undefined2 uVar3;
	DB *pDVar4;
	undefined2 *__dest;
	int iVar5;
	int iVar6;
	uint *puVar7;
	undefined *puVar8;
	TEXTURE_DETAILS *pTVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	undefined2 local_38;
	ushort local_36;
	undefined2 local_34;
	undefined2 local_32;
	int local_30;

	if (LoadingArea == 0) {
		if ((pauseflag == 0) && (gTimeOfDay == 3)) {
			local_34 = 0x10;
			local_32 = 1;
			puVar8 = Lev_CycleObjPtrs4[GameLevel];
			if (num_cycle_obj != 0) {
				iVar10 = 0;
				if (0 < num_cycle_obj) {
					iVar11 = 0xab3b0;
					local_30 = 0;
					iVar13 = 0;
					iVar12 = 0;
					pTVar9 = &cycle_tex;
					do {
						bVar1 = pTVar9->texture_page;
						bVar2 = pTVar9->texture_number;
						if (tpageloaded[(uint)bVar1] != '\0') {
							if (cycle_phase == 0) {
								local_38 = (undefined2)
									(((uint)(ushort)(&texture_cluts)[(uint)bVar1 * 0x20 + (uint)bVar2] & 0x3f
										) << 4);
								*(undefined2 *)(puVar8 + 4) = local_38;
								local_36 = (ushort)(&texture_cluts)[(uint)bVar1 * 0x20 + (uint)bVar2] >> 6 & 0x1ff;
								*(ushort *)(puVar8 + 6) = local_36;
								StoreImage(&local_38, iVar11);
							}
							else {
								if ((cycle_timer & *(ushort *)(puVar8 + 0xc)) == 0) {
									if ((int)*(short *)(puVar8 + 8) != -1) {
										iVar6 = iVar12 + 0xab3b0;
										iVar5 = (int)*(short *)(puVar8 + 8) * 2;
										__dest = (undefined2 *)(iVar5 + iVar6);
										uVar3 = *__dest;
										memmove(__dest, (void *)(iVar6 + iVar5 + 2),
											((uint)*(ushort *)(puVar8 + 10) - (uint)*(ushort *)(puVar8 + 8) & 0xffff
												) << 1);
										*(undefined2 *)((int)*(short *)(puVar8 + 10) * 2 + iVar6) = uVar3;
									}
								}
								if ((cycle_timer & *(ushort *)(puVar8 + 0x12)) == 0) {
									if ((int)*(short *)(puVar8 + 0xe) != -1) {
										iVar6 = iVar13 + 0xab3b0;
										iVar5 = (int)*(short *)(puVar8 + 0xe) * 2;
										__dest = (undefined2 *)(iVar5 + iVar6);
										uVar3 = *__dest;
										memmove(__dest, (void *)(iVar6 + iVar5 + 2),
											((uint)*(ushort *)(puVar8 + 0x10) - (uint)*(ushort *)(puVar8 + 0xe) &
												0xffff) << 1);
										*(undefined2 *)((int)*(short *)(puVar8 + 0x10) * 2 + iVar6) = uVar3;
									}
								}
								local_38 = *(undefined2 *)(puVar8 + 4);
								puVar7 = (uint *)((int)&cyclecluts[0].tag + local_30);
								local_36 = *(ushort *)(puVar8 + 6);
								SetDrawLoad(puVar7, &local_38);
								pDVar4 = current;
								*puVar7 = *puVar7 & 0xff000000 | *current->ot & 0xffffff;
								*pDVar4->ot = *pDVar4->ot & 0xff000000 | (uint)puVar7 & 0xffffff;
							}
						}
						iVar11 = iVar11 + 0x44;
						iVar13 = iVar13 + 0x44;
						iVar12 = iVar12 + 0x44;
						pTVar9 = pTVar9 + 1;
						iVar10 = iVar10 + 1;
						local_30 = local_30 + 0x44;
						puVar8 = puVar8 + 0x14;
					} while (iVar10 < num_cycle_obj);
				}
				if (cycle_phase != 0) {
					cycle_timer = cycle_timer + 1;
				}
				cycle_phase = cycle_phase ^ 1;
			}
		}
	}
	else {
		cycle_phase = 0;
	}
	return;*/
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

void FindSmashableObjects(void)
{
	UNIMPLEMENTED();
	/*
	SMASHABLE_OBJECT *pSVar1;
	int iVar2;
	SMASHABLE_OBJECT *pSVar3;

	pSVar3 = &smashable;
	if (smashable.name != (char *)0x0) {
		do {
			iVar2 = FindModelIdxWithName(pSVar3->name);
			pSVar3->modelIdx = iVar2;
			pSVar1 = pSVar3 + 1;
			pSVar3 = pSVar3 + 1;
		} while (pSVar1->name != (char *)0x0);
	}
	return;
	*/
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

void InitAnimatingObjects(void)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	MODEL *pMVar2;
	MODEL **ppMVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	undefined *puVar7;

	num_anim_objects = Level_NumAnimatedObjects[GameLevel];
	if (num_anim_objects != 0) {
		puVar7 = Level_AnimatingObjectPtrs4[GameLevel];
		iVar6 = 0;
		if (0 < num_anim_objects) {
			do {
				pMVar2 = FindModelPtrWithName(*(char **)(puVar7 + 8));
				iVar5 = 0;
				if (pMVar2 == (MODEL *)0x0) {
					*(undefined4 *)(puVar7 + 4) = 0xffffffff;
				}
				else {
					if (pMVar2 != modelpointers1536[0]) {
						ppMVar3 = modelpointers1536;
						do {
							ppMVar3 = ppMVar3 + 1;
							iVar5 = iVar5 + 1;
						} while (pMVar2 != *ppMVar3);
					}
					*(int *)(puVar7 + 4) = iVar5;
					iVar4 = num_models_in_pack;
					bVar1 = 0 < num_models_in_pack;
					pMVar2->flags2 = pMVar2->flags2 | 1;
					if (bVar1) {
						ppMVar3 = modelpointers1536;
						do {
							pMVar2 = *ppMVar3;
							if ((int)pMVar2->instance_number == iVar5) {
								pMVar2->flags2 = pMVar2->flags2 | 1;
							}
							iVar4 = iVar4 + -1;
							ppMVar3 = ppMVar3 + 1;
						} while (iVar4 != 0);
					}
				}
				iVar6 = iVar6 + 1;
				puVar7 = puVar7 + 0x10;
			} while (iVar6 < num_anim_objects);
		}
	}
	FindSmashableObjects();
	InitCyclingPals();
	return;
	*/
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

void InitSpooledAnimObj(int model_number)
{
	UNIMPLEMENTED();
	/*
	undefined *puVar1;
	int iVar2;

	puVar1 = Level_AnimatingObjectPtrs4[GameLevel];
	iVar2 = 0;
	if (0 < num_anim_objects) {
		do {
			iVar2 = iVar2 + 1;
			if (*(int *)(puVar1 + 4) == model_number) {
				modelpointers1536[model_number]->flags2 = modelpointers1536[model_number]->flags2 | 1;
				return;
			}
			puVar1 = puVar1 + 0x10;
		} while (iVar2 < num_anim_objects);
	}
	return;
	*/
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

void int_garage_door(void)
{
	UNIMPLEMENTED();
	/*
	CurrentGarage.cop = (CELL_OBJECT *)0x0;
	return;*/
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

int DrawAnimatingObject(MODEL *model, CELL_OBJECT *cop, VECTOR *pos)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uint type;
	uint *puVar1;
	int iVar2;

	type = SEXT24(model->instance_number);
	puVar1 = (uint *)Level_AnimatingObjectPtrs4[GameLevel];
	if (type == 0xffffffff) {
		type = (uint)cop->type;
	}
	iVar2 = 0;
	if (0 < num_anim_objects) {
		do {
			if (type == puVar1[1]) {
				type = *puVar1;
				animate_object(cop, type);
			}
			iVar2 = iVar2 + 1;
			puVar1 = puVar1 + 4;
		} while (iVar2 < num_anim_objects);
	}
	return 0;
	*/
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

void animate_object(CELL_OBJECT *cop, int type)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	int colour;
	int y;
	int z;
	int x;
	int local_18;

	x = (uint)cop->yang * 0x40;
	if (GameLevel == 1) {
		switch (type) {
		case 0:
			bVar1 = (&junctionLightsPhase)[x + 0x80U >> 10 & 1];
			if (bVar1 == 2) {
				z = -0x1a1;
				colour = -800;
				local_18 = -0x1e;
				y = 0x400;
			}
			else {
				if (2 < bVar1) {
					if (bVar1 != 3) {
						return;
					}
					z = -0x157;
					colour = -800;
					local_18 = -0x1e;
					goto LAB_000145f0;
				}
				if (bVar1 != 1) {
					return;
				}
				z = -0x1ea;
				colour = -800;
				local_18 = -0x1e;
				y = 0x200;
			}
			break;
		default:
			goto switchD_0001409c_caseD_1;
		case 2:
			if (gLightsOn == 0) {
				return;
			}
			x = 0xe6;
			y = -0x442;
		LAB_00014490:
			AddSmallStreetLight(cop, x, y, 0, 0);
			return;
		case 3:
			if (gLightsOn == 0) {
				return;
			}
			x = -0x265;
			y = -0x7d2;
			goto LAB_00014644;
		case 4:
			if (gLightsOn == 0) {
				return;
			}
			AddLightEffect(cop, -0x250, -2000, 0, 0, 3);
			x = 0x252;
			y = -2000;
			goto LAB_00014418;
		}
		goto LAB_000145f8;
	}
	if (1 < GameLevel) {
		if (GameLevel == 2) {
			switch (type) {
			case 0:
				bVar1 = (&junctionLightsPhase)[x + 0x80U >> 10 & 1];
				if (bVar1 == 2) {
					AddTrafficLight(cop, -0x85c, -0x3fd, -0x41, 0x400, x);
					AddTrafficLight(cop, -0x51e, -0x3d4, -0x41, 0x400, x);
					z = -0x208;
					colour = -0x3ab;
					local_18 = -0x41;
					y = 0x400;
				}
				else {
					if (bVar1 < 3) {
						if (bVar1 != 1) {
							return;
						}
						AddTrafficLight(cop, -0x857, -0x458, -0x44, 0x200, x);
						AddTrafficLight(cop, -0x520, -0x421, -0x44, 0x200, x);
						z = -0x202;
						colour = -0x400;
						local_18 = -0x44;
						y = 0x200;
					}
					else {
						if (bVar1 != 3) {
							return;
						}
						AddTrafficLight(cop, -0x85a, -0x3a9, -0x3e, 0x800, x);
						AddTrafficLight(cop, -0x51d, -0x381, -0x3e, 0x800, x);
						z = -0x206;
						colour = -0x353;
						local_18 = -0x3e;
						y = 0x800;
					}
				}
				break;
			case 1:
				bVar1 = (&junctionLightsPhase)[x + 0x80U >> 10 & 1];
				if (bVar1 == 2) {
					z = -4;
					colour = -0x1d2;
					local_18 = -0x29;
					y = 0x400;
				}
				else {
					if (2 < bVar1) {
						if (bVar1 != 3) {
							return;
						}
						z = -4;
						colour = -0x18b;
						local_18 = -0x29;
						goto LAB_000145f0;
					}
					if (bVar1 != 1) {
						return;
					}
					z = -4;
					colour = -0x219;
					local_18 = -0x29;
					y = 0x200;
				}
				break;
			case 2:
				if (gLightsOn == 0) {
					return;
				}
				x = -0x348;
				y = -0x7b4;
				z = -0x3d;
				goto LAB_00014648;
			case 3:
				if (gLightsOn == 0) {
					return;
				}
				AddLightEffect(cop, -0x361, -0x8c9, 0, 0, 3);
				x = 0x361;
				y = -0x8c9;
				goto LAB_00014418;
			case 4:
				if (gLightsOn == 0) {
					return;
				}
				if ((((cop->pos).vx - 0x217e6U < 0xc5ff) && (x = (cop->pos).vz, 0xae29c < x)) &&
					(x < 0xafa9c)) {
					x = -0x26c;
					y = -0x652;
					goto LAB_00014490;
				}
				x = -0x26c;
				y = -0x652;
				goto LAB_00014644;
			default:
				goto switchD_0001409c_caseD_1;
			}
			goto LAB_000145f8;
		}
		if (GameLevel != 3) {
			return;
		}
		switch (type) {
		case 0:
			bVar1 = (&junctionLightsPhase)[x + 0x80U >> 10 & 1];
			if (bVar1 == 2) {
				z = -0x2cf;
				colour = -0x345;
				local_18 = -0x16;
				y = 0x400;
			}
			else {
				if (2 < bVar1) {
					if (bVar1 != 3) {
						return;
					}
					z = -0x2cf;
					colour = -0x2fa;
					local_18 = -0x16;
					goto LAB_000145f0;
				}
				if (bVar1 != 1) {
					return;
				}
				z = -0x2cf;
				colour = -0x38a;
				local_18 = -0x16;
				y = 0x200;
			}
			break;
		case 1:
			bVar1 = (&junctionLightsPhase)[x + 0x80U >> 10 & 1];
			if (bVar1 == 2) {
				z = 0;
				colour = -0x242;
				local_18 = -0x15;
				y = 0x400;
			}
			else {
				if (2 < bVar1) {
					if (bVar1 != 3) {
						return;
					}
					z = 0;
					colour = -0x1fd;
					local_18 = -0x15;
					goto LAB_000145f0;
				}
				if (bVar1 != 1) {
					return;
				}
				z = 0;
				colour = -0x28e;
				local_18 = -0x15;
				y = 0x200;
			}
			break;
		case 2:
			if (gLightsOn == 0) {
				return;
			}
			x = -0x1f1;
			y = -0x59d;
			goto LAB_00014644;
		case 3:
			if (gLightsOn == 0) {
				return;
			}
			x = 0;
			y = -0xaa7;
		LAB_00014644:
			z = 0;
		LAB_00014648:
			colour = 3;
			local_18 = 0;
		LAB_00014650:
			AddLightEffect(cop, x, y, z, local_18, colour);
			return;
		case 4:
			if (gLightsOn != 0) {
				AddSmallStreetLight(cop, 0, -0x492, 0, 1);
			}
		default:
			goto switchD_0001409c_caseD_1;
		}
		goto LAB_000145f8;
	}
	if (GameLevel != 0) {
		return;
	}
	switch (type) {
	case 0:
	case 7:
		x = (x + 0x400) * 0x10000 >> 0x10;
		bVar1 = (&junctionLightsPhase)[x + 0x80U >> 10 & 1];
		if (bVar1 == 2) {
			z = 0;
			colour = -0x284;
			local_18 = -0x2d;
			y = 0x400;
		}
		else {
			if (bVar1 < 3) {
				if (bVar1 != 1) {
					return;
				}
				z = 0;
				colour = -0x2c4;
				local_18 = -0x2d;
				y = 0x200;
			}
			else {
				if (bVar1 != 3) {
					return;
				}
				z = 0;
				colour = -0x244;
				local_18 = -0x2d;
			LAB_000145f0:
				y = 0x800;
			}
		}
		break;
	case 1:
	case 8:
		bVar1 = (&junctionLightsPhase)[x + 0x80U >> 10 & 1];
		if (bVar1 == 2) {
			z = 0x196;
			colour = -0x292;
			local_18 = -0x2e;
			y = 0x400;
		}
		else {
			if (2 < bVar1) {
				if (bVar1 != 3) {
					return;
				}
				z = 0x196;
				colour = -0x252;
				local_18 = -0x2e;
				goto LAB_000145f0;
			}
			if (bVar1 != 1) {
				return;
			}
			z = 0x196;
			colour = -0x2c4;
			local_18 = -0x2e;
			y = 0x200;
		}
		break;
	case 2:
	case 3:
		if (gLightsOn == 0) {
			return;
		}
		x = 0x1ad;
		y = -0x4d2;
		goto LAB_00014644;
	case 4:
		if (gLightsOn == 0) {
			return;
		}
		AddLightEffect(cop, -0x1b0, -0x4d9, 0, 0, 3);
		x = 0x1b0;
		y = -0x4d9;
		goto LAB_00014418;
	case 5:
		if (gLightsOn == 0) {
			return;
		}
		x = 0;
		y = -0x50;
		z = 0;
		colour = 2;
		local_18 = 2;
		goto LAB_00014650;
	case 6:
		if (gLightsOn == 0) {
			return;
		}
		AddLightEffect(cop, 0xea, -0x47a, 0, 0, 3);
		x = -0xea;
		y = -0x47a;
	LAB_00014418:
		AddLightEffect(cop, x, y, 0, 0, 3);
	default:
		goto switchD_0001409c_caseD_1;
	}
LAB_000145f8:
	AddTrafficLight(cop, z, colour, local_18, y, x);
switchD_0001409c_caseD_1:
	return;*/
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

void animate_garage_door(void)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	int iVar2;
	int iVar3;

	if (CurrentGarage.cop != (CELL_OBJECT *)0x0) {
		if ((gCurrentMissionNumber != 0x35) && (CopsCanSeePlayer != 0)) {
			if ((int)player.playerCarId < 0) {
				psVar1 = &pedestrianFelony;
			}
			else {
				psVar1 = &car_data[(int)player.playerCarId].felonyRating;
			}
			if (0x292 < *psVar1) {
				((CurrentGarage.cop)->pos).vx = CurrentGarage.old_pos.vx;
				((CurrentGarage.cop)->pos).vy = CurrentGarage.old_pos.vy;
				((CurrentGarage.cop)->pos).vz = CurrentGarage.old_pos.vz;
				CurrentGarage.cop = (CELL_OBJECT *)0x0;
				return;
			}
		}
		iVar3 = CurrentGarage.old_pos.vx - car_data[0].hd.where.t[0];
		iVar2 = CurrentGarage.old_pos.vz - car_data[0].hd.where.t[2];
		if (iVar3 < 0) {
			iVar3 = -iVar3;
		}
		if (iVar2 < 0) {
			iVar2 = -iVar2;
		}
		if ((iVar3 + iVar2 < 0x1771) && (gStopPadReads == 0)) {
			if ((iVar3 + iVar2 < 4000) && (CurrentGarage.old_pos.vy + -400 < CurrentGarage.pos.vy)) {
				CurrentGarage.rotation = CurrentGarage.rotation + 0x19;
				CurrentGarage.pos.vy = CurrentGarage.pos.vy + -0xc;
			}
		}
		else {
			if (CurrentGarage.pos.vy < CurrentGarage.old_pos.vy) {
				CurrentGarage.pos.vy = CurrentGarage.pos.vy + 0xc;
				CurrentGarage.rotation = CurrentGarage.rotation + -0x19;
				return;
			}
		}
	}
	return;
	*/
}





