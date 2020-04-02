#include "THISDUST.H"
#include "PEDEST.H"


MODEL* pmTannerModels[17] = { 0 };

typedef void(*pedFunc)(PEDESTRIAN *pPed);

void PedDoNothing(PEDESTRIAN *pPed);
void PedUserWalker(PEDESTRIAN *pPed);
void PedUserRunner(PEDESTRIAN *pPed);
void PedGetInCar(PEDESTRIAN *pPed);
void PedGetOutCar(PEDESTRIAN *pPed);
void PedCarryOutAnimation(PEDESTRIAN *pPed);
void CivPedDoNothing(PEDESTRIAN *pPed);
void CivPedWalk(PEDESTRIAN *pPed);
void CivPedSit(PEDESTRIAN *pPed);
void CivPedJump(PEDESTRIAN *pPed);
void PedPressButton(PEDESTRIAN *pPed);
void TannerSitDown(PEDESTRIAN *pPed);
void CopStand(PEDESTRIAN *pPed);
void CivGetIn(PEDESTRIAN *pPed);

pedFunc fpPedPersonalityFunctions[] = {
	PedDoNothing, PedUserWalker, PedUserRunner,
	PedGetInCar, PedGetOutCar,
	PedCarryOutAnimation,
	CivPedDoNothing, CivPedWalk, CivPedSit, CivPedJump,
	PedPressButton, TannerSitDown, CopStand, CivGetIn };

VECTOR tannerLookAngle = { 0, 0, 0, 0 };

long force[4] = { 0x9000, 0, 0, 0 };
long point[4] = { 0, 0, 0x5A, 0 };

// decompiled code
// original method signature: 
// void /*$ra*/ IHaveThePower()
 // line 1137, offset 0x0006dd34
	/* begin block 1 */
		// Start line: 1139
		// Start offset: 0x0006DD34
		// Variables:
	// 		struct _CAR_DATA *cp; // $t4

		/* begin block 1.1 */
			// Start line: 1152
			// Start offset: 0x0006DDB8
		/* end block 1.1 */
		// End offset: 0x0006DF20
		// End Line: 1170
	/* end block 1 */
	// End offset: 0x0006DF54
	// End Line: 1182

	/* begin block 2 */
		// Start line: 2274
	/* end block 2 */
	// End Line: 2275

	/* begin block 3 */
		// Start line: 2275
	/* end block 3 */
	// End Line: 2276

/* WARNING: Unknown calling convention yet parameter storage is locked */

void IHaveThePower(void)
{
	UNIMPLEMENTED();
	/*
	long lVar1;
	long lVar2;
	long lVar3;
	long lVar4;
	long lVar5;
	int iVar6;
	int iVar7;
	_CAR_DATA *p_Var8;
	int iVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;

	iVar6 = gWeather;
	lVar4 = point[0];
	lVar1 = force[0];
	p_Var8 = car_data;
	if (GameLevel != 1) {
		return;
	}
	if ((((player.pos[0] < -0x38ad3) || (-0x38945 < player.pos[0])) || (player.pos[2] < -0x39ac5)) ||
		(-0x39937 < player.pos[2])) {
		if (bPower != 0) {
			bPower = 0;
			gWeather = oldWeather;
		}
	}
	else {
		if ((tannerPad & 0x20) != 0) {
			if (bPower == 0) {
				bPower = GameLevel;
				gWeather = GameLevel;
				oldWeather = iVar6;
			}
			powerCounter = powerCounter + 1;
			if (powerCounter < 0x14) {
				do {
					lVar5 = point[1];
					lVar3 = force[2];
					lVar2 = force[1];
					if (p_Var8->controlType != '\0') {
						iVar9 = point[1] * force[2];
						iVar10 = point[2] * force[1];
						iVar11 = point[2] * lVar1;
						iVar12 = lVar4 * force[2];
						iVar13 = lVar4 * force[1];
						iVar7 = (p_Var8->hd).acc[1];
						(p_Var8->hd).acc[0] = (p_Var8->hd).acc[0] + lVar1;
						iVar6 = (p_Var8->hd).acc[2];
						(p_Var8->hd).acc[1] = iVar7 + lVar2;
						(p_Var8->hd).acc[2] = iVar6 + lVar3;
						(p_Var8->hd).aacc[0] = (p_Var8->hd).aacc[0] + ((iVar9 - iVar10) + 0x800 >> 0xc);
						(p_Var8->hd).aacc[1] = (p_Var8->hd).aacc[1] + ((iVar11 - iVar12) + 0x800 >> 0xc);
						(p_Var8->hd).aacc[2] = (p_Var8->hd).aacc[2] + ((iVar13 - lVar5 * lVar1) + 0x800 >> 0xc);
					}
					p_Var8 = p_Var8 + 1;
				} while (p_Var8 < (_CAR_DATA *)0xd4698);
			}
			if (0x30 < powerCounter) {
				powerCounter = 0;
				return;
			}
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessTannerPad(struct PEDESTRIAN *pPed /*$s1*/, unsigned long pad /*$a1*/, char PadSteer /*$a2*/, char use_analogue /*$a3*/)
 // line 1191, offset 0x0006df54
	/* begin block 1 */
		// Start line: 1192
		// Start offset: 0x0006DF54
		// Variables:
	// 		struct VECTOR vec; // stack offset -88
	// 		int mapheight; // $s2
	// 		struct VECTOR normal; // stack offset -72
	// 		struct VECTOR out; // stack offset -56
	// 		struct _sdPlane *SurfacePtr; // stack offset -24

		/* begin block 1.1 */
			// Start line: 1224
			// Start offset: 0x0006DFC8
			// Variables:
		// 		struct VECTOR tVec; // stack offset -40
		// 		struct _sdPlane *plane; // $v0
		// 		int mH; // $v1
		// 		int sI; // $a0
		/* end block 1.1 */
		// End offset: 0x0006E104
		// End Line: 1277

		/* begin block 1.2 */
			// Start line: 1359
			// Start offset: 0x0006E390
		/* end block 1.2 */
		// End offset: 0x0006E3F0
		// End Line: 1365
	/* end block 1 */
	// End offset: 0x0006E3F0
	// End Line: 1367

	/* begin block 2 */
		// Start line: 2378
	/* end block 2 */
	// End Line: 2379

	/* begin block 3 */
		// Start line: 2388
	/* end block 3 */
	// End Line: 2389

	/* begin block 4 */
		// Start line: 2397
	/* end block 4 */
	// End Line: 2398

void ProcessTannerPad(PEDESTRIAN *pPed, ulong pad, char PadSteer, char use_analogue)
{
	UNIMPLEMENTED();
	/*
	PED_ACTION_TYPE PVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	_sdPlane *p_Var5;
	SEATED_PEDESTRIANS *pSVar6;
	short sVar7;
	uint uVar8;
	VECTOR local_58;
	VECTOR local_48;
	VECTOR VStack56;
	VECTOR local_28;
	_sdPlane *local_18[2];

	local_18[0] = (_sdPlane *)0x0;
	tannerPad = pad;
	if (use_analogue != '\0') {
		tannerPad = pad;
		if (PadSteer < '\0') {
			tannerPad = pad | 0x8000;
		}
		if ('\0' < PadSteer) {
			tannerPad = tannerPad | 0x2000;
		}
	}
	if (bKillTanner != 0) {
		pPed->flags = pPed->flags | 4;
	}
	IHaveThePower();
	local_58.vx = (pPed->position).vx;
	local_58.vz = (pPed->position).vz;
	local_58.vy = -(pPed->position).vy;
	iVar2 = MapHeight(&local_58);
	uVar8 = (int)(pPed->dir).vy - 0x800U & 0xfff;
	local_28.vy = local_58.vy;
	local_28.pad = local_58.pad;
	iVar2 = -0x82 - iVar2;
	bStopTanner = 0;
	local_28.vx = local_58.vx + ((int)rcossin_tbl[uVar8 * 2] * 5 >> 9);
	local_28.vz = local_58.vz + ((int)rcossin_tbl[uVar8 * 2 + 1] * 5 >> 9);
	iVar3 = MapHeight(&local_28);
	iVar4 = (-0x82 - iVar3) - iVar2;
	if (iVar4 < 0) {
		iVar4 = iVar2 - (-0x82 - iVar3);
	}
	if (iVar4 < 0x3f3) {
		p_Var5 = sdGetCell(&local_28);
		sVar7 = -0x20;
		if (p_Var5 != (_sdPlane *)0x0) {
			sVar7 = p_Var5->surface;
		}
		uVar8 = ((int)((uint)(ushort)p_Var5->b << 0x10) >> 0x12) - 0x800U & 0xfff;
		iVar3 = uVar8 - 0x800;
		if (iVar3 < 0) {
			iVar3 = 0x800 - uVar8;
		}
		if ((((iVar3 < 0x44d) && (sVar7 != 6)) && (sVar7 != 9)) && (sVar7 != -0x20)) goto LAB_0006e104;
	}
	bStopTanner = 1;
LAB_0006e104:
	if ((pPed->type != PED_ACTION_SIT) && (bStopTanner == 0)) {
		(pPed->position).vy = iVar2;
	}
	if (((gInGameCutsceneActive == 0) || (gCurrentMissionNumber != 0x17)) ||
		((gInGameCutsceneID != 0 || ((CameraCnt != 0x1cb || (pPed->pedType == TANNER_MODEL)))))) {
		if ((tannerPad & 0x10) != 0) {
			if (((pPed->type != PED_ACTION_GETINCAR) && (pPed->type != PED_ACTION_GETOUTCAR)) &&
				(gCantDrive == 0)) {
				DeActivatePlayerPedestrian(pPed);
			}
			if ((((tannerPad & 0x10) != 0) && (PVar1 = pPed->type, PVar1 != PED_ACTION_GETINCAR)) &&
				((PVar1 != PED_ACTION_GETOUTCAR &&
				((PVar1 != PED_ACTION_SIT &&
					(pSVar6 = FindTannerASeat(pPed), pSVar6 != (SEATED_PEDESTRIANS *)0x0)))))) {
				SetupTannerSitDown(pPed);
			}
		}
		if ((((gTannerActionNeeded != 0) && ((tannerPad & 0x10) != 0)) &&
			(pPed->type != PED_ACTION_GETINCAR)) && (pPed->type != PED_ACTION_GETOUTCAR)) {
			SetupPressButton(pPed);
		}
		if (pPed != (PEDESTRIAN *)0x0) {
			if (pPed->fpAgitatedState == (_func_2 *)0x0) {
				(*pPed->fpRestState)(pPed);
			}
			else {
				(*pPed->fpAgitatedState)(pPed);
			}
			if ((player.cameraView == '\x02') && (pPed->type != PED_ACTION_GETINCAR)) {
				if (oldCamView != (uint)(byte)player.cameraView) {
					camAngle.vx = camera_angle.vx;
					camAngle.vz = camera_angle.vz;
				}
				camAngle.vy = player.headPos._2_2_ - (short)player.dir & 0xfff;
				TannerCameraHandler(pPed);
			}
			else {
				bTannerSitting = 0;
			}
			oldCamView = ZEXT14((byte)player.cameraView);
			TannerCollision(pPed);
			if (GameLevel == 0) {
				FindSurfaceD2((VECTOR *)&player, &local_48, &VStack56, local_18);
				if (((local_18[0]->surface != -1) && (local_18[0]->surface < 0x20)) &&
					((local_18[0]->surface & 0x10U) != 0)) {
					(pPed->position).vx = (pPed->position).vx + (local_48.vx >> 6);
					(pPed->position).vz = (pPed->position).vz + (local_48.vz >> 6);
				}
			}
		}
	}
	else {
		iVar2 = (int)pPed->padId;
		if (iVar2 < 0) {
			iVar2 = -iVar2;
		}
		(&player)[iVar2].pPed = (PEDESTRIAN *)0x0;
		DestroyPedestrian(pPed);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitTanner()
 // line 1375, offset 0x0006e408
	/* begin block 1 */
		// Start line: 1377
		// Start offset: 0x0006E408
	/* end block 1 */
	// End offset: 0x0006E5C4
	// End Line: 1433

	/* begin block 2 */
		// Start line: 2819
	/* end block 2 */
	// End Line: 2820

	/* begin block 3 */
		// Start line: 2820
	/* end block 3 */
	// End Line: 2821

	/* begin block 4 */
		// Start line: 2823
	/* end block 4 */
	// End Line: 2824

/* WARNING: Unknown calling convention yet parameter storage is locked */

void InitTanner(void)
{
	UNIMPLEMENTED();
	/*
	pmTannerModels17 = FindModelPtrWithName(s_TORSO_000aa890);
	PTR_000d96e4 = FindModelPtrWithName(&DAT_000aa898);
	PTR_000d96e8 = FindModelPtrWithName(s_U_ARM_RIGHT_00011b7c);
	PTR_000d96ec = FindModelPtrWithName(s_L_ARM_RIGHT_00011b88);
	PTR_000d96f0 = FindModelPtrWithName(s_HAND_RIGHT_00011b94);
	PTR_000d96f4 = FindModelPtrWithName(s_THIGH_RIGHT_00011ba0);
	PTR_000d96f8 = FindModelPtrWithName(s_CALF_RIGHT_00011bac);
	PTR_000d96fc = FindModelPtrWithName(s_FOOT_LEFT_00011bb8);
	PTR_000d9700 = FindModelPtrWithName(s_U_ARM_LEFT_00011bc4);
	PTR_000d9704 = FindModelPtrWithName(s_L_ARM_LEFT_00011bd0);
	PTR_000d9708 = FindModelPtrWithName(s_HAND_LEFT_00011bdc);
	PTR_000d970c = FindModelPtrWithName(s_THIGH_LEFT_00011be8);
	PTR_000d9710 = FindModelPtrWithName(s_CALF_LEFT_00011bf4);
	PTR_000d9714 = FindModelPtrWithName(s_FOOT_RIGHT_00011c00);
	PTR_000d9718 = FindModelPtrWithName(&DAT_000aa8a0);
	PTR_000d971c = FindModelPtrWithName(&DAT_000aa8a8);
	PTR_000d9720 = FindModelPtrWithName((char *)&PTR_DAT_000aa8b0);
	pmJerichoModels6 = FindModelPtrWithName(s_JERI_TORSO_00011c0c);
	PTR_000d95bc = FindModelPtrWithName(s_JERI_HEAD_00011c18);
	PTR_000d95c0 = FindModelPtrWithName(s_JERI_U_ARM_LEFT_00011c24);
	PTR_000d95c4 = FindModelPtrWithName(s_JERI_L_ARM_LEFT_00011c34);
	PTR_000d95c8 = FindModelPtrWithName(s_JERI_U_ARM_RIGHT_00011c44);
	PTR_000d95cc = FindModelPtrWithName(s_JERI_L_ARM_RIGHT_00011c58);
	SetSkelModelPointers(0);
	StoreVertexLists();
	numTannerPeds = 0;
	bTannerSitting = 0;
	bKillTanner = 0;
	bKilled = 0;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetTannerPosition(struct VECTOR *pVec /*$a0*/)
 // line 1440, offset 0x00072478
	/* begin block 1 */
		// Start line: 1441
		// Start offset: 0x00072478
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $a1
	/* end block 1 */
	// End offset: 0x00072500
	// End Line: 1459

	/* begin block 2 */
		// Start line: 11519
	/* end block 2 */
	// End Line: 11520

	/* begin block 3 */
		// Start line: 2880
	/* end block 3 */
	// End Line: 2881

	/* begin block 4 */
		// Start line: 11522
	/* end block 4 */
	// End Line: 11523

void SetTannerPosition(VECTOR *pVec)
{
	UNIMPLEMENTED();
	/*
	PEDESTRIAN **ppPVar1;
	PEDESTRIAN *pPVar2;

	pPVar2 = pUsedPeds;
	if (pUsedPeds != (PEDESTRIAN *)0x0) {
		do {
			if (pPVar2->pedType == TANNER_MODEL) {
				(pPVar2->position).vx = pVec->vx;
				(pPVar2->position).vy = -pVec->vy;
				(pPVar2->position).vz = pVec->vz;
				player.pos[0] = pVec->vx;
				player.pos[1] = pVec->vy;
				player.pos[2] = pVec->vz;
			}
			ppPVar1 = &pPVar2->pNext;
			pPVar2 = *ppPVar1;
		} while (*ppPVar1 != (PEDESTRIAN *)0x0);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitPedestrians()
 // line 1466, offset 0x0006e5c4
	/* begin block 1 */
		// Start line: 1468
		// Start offset: 0x0006E5C4
		// Variables:
	// 		int loop; // $a1
	// 		struct SEATED_PEDESTRIANS *seatedptr; // $s2
	/* end block 1 */
	// End offset: 0x0006E6C4
	// End Line: 1513

	/* begin block 2 */
		// Start line: 2973
	/* end block 2 */
	// End Line: 2974

	/* begin block 3 */
		// Start line: 3007
	/* end block 3 */
	// End Line: 3008

	/* begin block 4 */
		// Start line: 3008
	/* end block 4 */
	// End Line: 3009

	/* begin block 5 */
		// Start line: 3009
	/* end block 5 */
	// End Line: 3010

/* WARNING: Unknown calling convention yet parameter storage is locked */

void InitPedestrians(void)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	SEATED_PEDESTRIANS *pSVar2;
	int iVar3;
	undefined4 *puVar4;
	undefined4 *puVar5;
	undefined4 *puVar6;

	pSVar2 = seated_pedestrian;
	puVar5 = &pedestrians;
	memset(&pedestrians, 0, 0xa10);
	DestroyPedestrians();
	puVar6 = &DAT_000d8414;
	puVar4 = &DAT_000d8470;
	iVar3 = 0x19;
	pedestrians = &DAT_000d8414;
	do {
		*(undefined4 **)(puVar6 + 1) = puVar5;
		puVar5 = puVar5 + 0x17;
		*(undefined4 **)puVar6 = puVar4;
		puVar6 = puVar6 + 0x17;
		iVar3 = iVar3 + -1;
		puVar4 = puVar4 + 0x17;
	} while (-1 < iVar3);
	DAT_000d8d6c = 0;
	DAT_000d8d70 = &DAT_000d8d10;
	pUsedPeds = (PEDESTRIAN *)0x0;
	pFreePeds = (PEDESTRIAN *)&pedestrians;
	seated_count = 0;
	if (pSVar2 != (SEATED_PEDESTRIANS *)0x0) {
		sVar1 = pSVar2->rotation;
		while (sVar1 != 9999) {
			pSVar2->index = '\0';
			sVar1 = pSVar2[1].rotation;
			seated_count = seated_count + 1;
			pSVar2 = pSVar2 + 1;
		}
	}
	maxSeated = seated_count;
	numTannerPeds = 0;
	pinginPedAngle = 0;
	pPlayerPed = (PEDESTRIAN *)0x0;
	seated_count = 0;
	ping_in_pedestrians = '\x01';
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DestroyPedestrians()
 // line 1521, offset 0x00071f54
	/* begin block 1 */
		// Start line: 1523
		// Start offset: 0x00071F54
	/* end block 1 */
	// End offset: 0x00071FB4
	// End Line: 1534

	/* begin block 2 */
		// Start line: 3042
	/* end block 2 */
	// End Line: 3043

	/* begin block 3 */
		// Start line: 8489
	/* end block 3 */
	// End Line: 8490

	/* begin block 4 */
		// Start line: 8491
	/* end block 4 */
	// End Line: 8492

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DestroyPedestrians(void)
{
	UNIMPLEMENTED();
	/*
	if (pUsedPeds != (PEDESTRIAN *)0x0) {
		do {
			if (pUsedPeds->pedType == TANNER_MODEL) {
				numTannerPeds = numTannerPeds + -1;
			}
			DestroyPedestrian(pUsedPeds);
		} while (pUsedPeds != (PEDESTRIAN *)0x0);
	}
	num_pedestrians = 0;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DestroyCivPedestrians()
 // line 1541, offset 0x00072fd0
	/* begin block 1 */
		// Start line: 1543
		// Start offset: 0x00072FD0
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $v1
	// 		struct PEDESTRIAN *pHPed; // $s0
	/* end block 1 */
	// End offset: 0x00073038
	// End Line: 1559

	/* begin block 2 */
		// Start line: 3082
	/* end block 2 */
	// End Line: 3083

	/* begin block 3 */
		// Start line: 19292
	/* end block 3 */
	// End Line: 19293

	/* begin block 4 */
		// Start line: 19296
	/* end block 4 */
	// End Line: 19297

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DestroyCivPedestrians(void)
{
	UNIMPLEMENTED();
	/*
	PEDESTRIAN *pPVar1;
	PEDESTRIAN *pPVar2;

	pPVar1 = pUsedPeds;
	if (pUsedPeds != (PEDESTRIAN *)0x0) {
		do {
			pPVar2 = pPVar1->pNext;
			if (pPVar1->pedType == CIVILIAN) {
				DestroyPedestrian(pUsedPeds);
				num_pedestrians = num_pedestrians + -1;
			}
			pPVar1 = pPVar2;
		} while (pPVar2 != (PEDESTRIAN *)0x0);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DestroyPedestrian(struct PEDESTRIAN *pPed /*$a1*/)
 // line 1567, offset 0x00071fb4
	/* begin block 1 */
		// Start line: 1568
		// Start offset: 0x00071FB4

		/* begin block 1.1 */
			// Start line: 1605
			// Start offset: 0x00072064
			// Variables:
		// 		struct SEATED_PEDESTRIANS *seatedptr; // $a0
		/* end block 1.1 */
		// End offset: 0x00072090
		// End Line: 1608
	/* end block 1 */
	// End offset: 0x000720AC
	// End Line: 1616

	/* begin block 2 */
		// Start line: 8546
	/* end block 2 */
	// End Line: 8547

	/* begin block 3 */
		// Start line: 8580
	/* end block 3 */
	// End Line: 8581

void DestroyPedestrian(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	PEDESTRIAN *pPVar1;

	pPVar1 = pUsedPeds;
	if ((pPed->flags & 8U) != 0) {
		numCopPeds = numCopPeds + -1;
	}
	pPed->flags = 0;
	(pPed->dir).vz = 0;
	(pPed->dir).vy = 0;
	(pPed->dir).vx = 0;
	if (pPed == pPVar1) {
		pUsedPeds = pPed->pNext;
		pUsedPeds->pPrev = (PEDESTRIAN *)0x0;
		pPed->pNext = pFreePeds;
		pFreePeds->pPrev = pPed;
	}
	else {
		pPed->pPrev->pNext = pPed->pNext;
		if (pPed->pNext != (PEDESTRIAN *)0x0) {
			pPed->pNext->pPrev = pPed->pPrev;
		}
		pPed->pNext = pFreePeds;
		pFreePeds->pPrev = pPed;
		pPed->pPrev = (PEDESTRIAN *)0x0;
	}
	pFreePeds = pPed;
	if ((pPed->type == PED_ACTION_CIVSIT) && (seated_pedestrian[(byte)pPed->seat_index].index != '\0')
		) {
		seated_pedestrian[(byte)pPed->seat_index].index = '\0';
	}
	pPed->doing_turn = '\0';
	num_pedestrians = num_pedestrians + -1;
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ ActivatePlayerPedestrian(struct _CAR_DATA *pCar /*$s6*/, char *padId /*stack 4*/, int direction /*$a1*/, long (*position)[4] /*$a3*/, int playerType /*stack 16*/)
 // line 1623, offset 0x0006e6c4
	/* begin block 1 */
		// Start line: 1624
		// Start offset: 0x0006E6C4
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $s1
	// 		struct PEDESTRIAN *pSPed; // $a0
	// 		struct VECTOR v; // stack offset -72
	// 		int nx; // $s4
	// 		int nz; // $s2
	// 		long w; // $s0
	// 		long x; // $s5
	// 		long y; // stack offset -52
	// 		long z; // $s1
	// 		long d; // stack offset -48
	// 		int side; // $fp
	// 		int id; // $s3

		/* begin block 1.1 */
			// Start line: 1688
			// Start offset: 0x0006E7D4

			/* begin block 1.1.1 */
				// Start line: 1763
				// Start offset: 0x0006EA48
			/* end block 1.1.1 */
			// End offset: 0x0006EA48
			// End Line: 1763

			/* begin block 1.1.2 */
				// Start line: 1807
				// Start offset: 0x0006EB48
			/* end block 1.1.2 */
			// End offset: 0x0006EB48
			// End Line: 1807
		/* end block 1.1 */
		// End offset: 0x0006EB48
		// End Line: 1807
	/* end block 1 */
	// End offset: 0x0006EC88
	// End Line: 1835

	/* begin block 2 */
		// Start line: 3244
	/* end block 2 */
	// End Line: 3245

	/* begin block 3 */
		// Start line: 3355
	/* end block 3 */
	// End Line: 3356

	/* begin block 4 */
		// Start line: 3365
	/* end block 4 */
	// End Line: 3366

/* WARNING: Type propagation algorithm not settling */

int ActivatePlayerPedestrian(_CAR_DATA *pCar, char *padId, int direction, long(*position)[4], int playerType)
{
	UNIMPLEMENTED();
	return 0;
	/*
	undefined *puVar1;
	int iVar2;
	int side;
	PEDESTRIAN *pedptr;
	uint uVar3;
	int iVar4;
	long lVar5;
	int iVar6;
	long lVar7;
	int iVar8;
	VECTOR *pos;
	VECTOR local_48;
	uint local_38;
	long local_34;
	uint local_30;
	int local_2c;

	local_38 = playerType & 0xff;
	bReverseAnimation = 0;
	iIdleTimer = 0;
	if (padId == (char *)0x0) {
		iVar6 = 0;
	}
	else {
		iVar2 = (int)*padId;
		iVar6 = -iVar2;
		if (-1 < iVar2) {
			iVar6 = iVar2;
		}
		pedptr = pUsedPeds;
		if (pUsedPeds != (PEDESTRIAN *)0x0) {
			do {
				if ((int)pedptr->padId == iVar2) {
					(&player)[iVar6].pPed = pedptr;
					return 0;
				}
				pedptr = pedptr->pNext;
			} while (pedptr != (PEDESTRIAN *)0x0);
		}
	}
	if (pCar == (_CAR_DATA *)0x0) {
		iVar8 = (*position)[0];
		iVar4 = (*position)[2];
		iVar2 = 1;
		local_30 = direction;
	}
	else {
		local_34 = (pCar->hd).where.t[1];
		iVar8 = (pCar->hd).where.t[0];
		iVar4 = (pCar->hd).where.t[2];
		local_30 = (pCar->hd).direction;
		iVar2 = (int)car_cosmetics[(byte)(pCar->ap).model].colBox.vx;
	}
	iVar2 = iVar2 + 0x5a;
	if (7 < numTannerPeds) {
		bReverseAnimation = 0;
		iIdleTimer = 0;
		return 0;
	}
	uVar3 = local_30 & 0xfff;
	local_48.vy = local_34;
	lVar5 = iVar4 + (iVar2 * rcossin_tbl[uVar3 * 2] >> 0xc);
	lVar7 = iVar8 - (iVar2 * rcossin_tbl[uVar3 * 2 + 1] >> 0xc);
	local_2c = local_30 - 0x800;
	local_48.vx = lVar7;
	local_48.vz = lVar5;
	if (pCar != (_CAR_DATA *)0x0) {
		side = QuickBuildingCollisionCheck(&local_48, local_2c, 10, 10, 10);
		if ((side != 0) || (side = TannerCarCollisionCheck(&local_48, local_30, 1), side != 0)) {
			side = 1;
			local_48.vy = local_34;
			lVar7 = iVar8 - (-iVar2 * (int)rcossin_tbl[uVar3 * 2 + 1] >> 0xc);
			lVar5 = iVar4 + (-iVar2 * (int)rcossin_tbl[uVar3 * 2] >> 0xc);
			local_48.vx = lVar7;
			local_48.vz = lVar5;
			iVar2 = QuickBuildingCollisionCheck(&local_48, local_2c, 10, 10, 10);
			if (iVar2 != 0) {
				return 0;
			}
			iVar2 = TannerCarCollisionCheck(&local_48, local_30, 1);
			if (iVar2 != 0) {
				return 0;
			}
			goto LAB_0006e908;
		}
	}
	side = 0;
LAB_0006e908:
	pedptr = CreatePedestrian();
	numTannerPeds = numTannerPeds + 1;
	if (padId == (char *)0x0) {
		pedptr->padId = '\0';
	}
	else {
		pedptr->padId = *padId;
	}
	pos = (VECTOR *)&pedptr->position;
	if (pedptr == (PEDESTRIAN *)0x0) {
		pos = (VECTOR *)&DAT_00000014;
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	if (pCar == (_CAR_DATA *)0x0) {
		pedptr->type = PED_ACTION_BACK;
		puVar1 = fpPedPersonalityFunctions;
		pedptr->fpAgitatedState = (_func_2 *)0x0;
		pedptr->fpRestState = puVar1;
	}
	else {
		pedptr->type = PED_ACTION_GETOUTCAR;
		pedptr->fpRestState = fpPedPersonalityFunctions;
		pedptr->fpAgitatedState = PTR_PedGetOutCar_000a1680;
	}
	(pedptr->position).vx = lVar7;
	(pedptr->position).vz = lVar5;
	if (pCar != (_CAR_DATA *)0x0) {
		(pedptr->position).vy = (pCar->hd).where.t[1];
	}
	iVar2 = MapHeight(pos);
	(pedptr->position).vy = -0x82 - iVar2;
	(pedptr->dir).vz = 0;
	(pedptr->dir).vx = 0;
	pedptr->head_rot = 0;
	(pedptr->dir).vy = (short)local_2c;
	pPlayerPed = pedptr;
	(&player)[iVar6].headTimer = '\0';
	pedptr->pedType = (PED_MODEL_TYPES)local_38;
	SetupPedestrian(pedptr);
	if (pCar == (_CAR_DATA *)0x0) {
		(&player)[iVar6].cameraView = '\0';
		(&player)[iVar6].headPos = 0;
		(&player)[iVar6].headTarget = 0;
		(&player)[iVar6].headTimer = '\0';
		(&player)[iVar6].playerType = '\x02';
		(&player)[iVar6].cameraAngle = local_2c;
		(&player)[iVar6].cameraCarId = -1;
		(&player)[iVar6].worldCentreCarId = -1;
		(&player)[iVar6].pos[0] = (pedptr->position).vx;
		(&player)[iVar6].pos[1] = (pedptr->position).vy;
		lVar5 = (pedptr->position).vz;
		(&player)[iVar6].spoolXZ = pos;
		(&player)[iVar6].pPed = pedptr;
		(&player)[iVar6].onGrass = '\0';
		(&player)[iVar6].dir = local_30;
		(&player)[iVar6].pos[2] = lVar5;
		pedptr->frame1 = '\0';
		pedptr->speed = '\0';
		if (local_38 == 2) {
			if (gCurrentMissionNumber == 9) {
				pedptr->pallet = 'D';
			}
			else {
				lVar5 = Random2(0);
				lVar7 = Random2(0);
				pedptr->pallet =
					(char)lVar5 + (char)(lVar5 / 3) * -3 + ((char)lVar7 + (char)(lVar7 / 3) * -3) * '\x10';
			}
		}
	}
	else {
		MakeTheCarShutUp('\0');
		Start3DSoundVolPitch(-1, 6, 2, player.pos[0], player.pos[1], player.pos[2], 0, 0x1000);
		SetupGetOutCar(pedptr, pCar, side);
		pedptr->padId = '\0';
		player.pPed = pedptr;
		SetConfusedCar((int)player.playerCarId);
		StopPadVibration(0);
		StopPadVibration(1);
		player.onGrass = '\0';
	}
	iVar6 = gCurrentMissionNumber;
	tannerTurn = 0;
	gGotInStolenCar = 0;
	bKillTanner = 0;
	bKilled = 0;
	pedptr->flags = pedptr->flags & 0xfffffffb;
	if ((iVar6 == 0x17) && (local_38 != 0)) {
		tannerTurn = 0x10;
		(pedptr->dir).vy =
			((pedptr->dir).vy - ((short)tannerTurnMax + 0x10) * (short)tannerTurnStep) + 0x126;
	}
	return 1;*/
}



// decompiled code
// original method signature: 
// struct PEDESTRIAN * /*$ra*/ CreatePedestrian()
 // line 1842, offset 0x000720ac
	/* begin block 1 */
		// Start line: 1844
		// Start offset: 0x000720AC
	/* end block 1 */
	// End offset: 0x00072114
	// End Line: 1869

	/* begin block 2 */
		// Start line: 8911
	/* end block 2 */
	// End Line: 8912

	/* begin block 3 */
		// Start line: 9138
	/* end block 3 */
	// End Line: 9139

	/* begin block 4 */
		// Start line: 9139
	/* end block 4 */
	// End Line: 9140

	/* begin block 5 */
		// Start line: 9141
	/* end block 5 */
	// End Line: 9142

/* WARNING: Unknown calling convention yet parameter storage is locked */

PEDESTRIAN * CreatePedestrian(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	PEDESTRIAN *pPVar1;

	pPVar1 = pFreePeds;
	if (pFreePeds != (PEDESTRIAN *)0x0) {
		if (pFreePeds->pNext != (PEDESTRIAN *)0x0) {
			pFreePeds->pNext->pPrev = (PEDESTRIAN *)0x0;
		}
		pFreePeds = pFreePeds->pNext;
		if (pUsedPeds != (PEDESTRIAN *)0x0) {
			pUsedPeds->pPrev = pPVar1;
		}
		pPVar1->pPrev = (PEDESTRIAN *)0x0;
		pPVar1->pNext = pUsedPeds;
		num_pedestrians = num_pedestrians + 1;
		pUsedPeds = pPVar1;
		return pPVar1;
	}
	return (PEDESTRIAN *)0x0;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlaceRoadBlockCops()
 // line 1877, offset 0x0006ec88
	/* begin block 1 */
		// Start line: 1879
		// Start offset: 0x0006EC88
		// Variables:
	// 		struct _CAR_DATA *pCar; // $a0
	// 		struct _CAR_DATA (*pCopCars[16]); // stack offset -152
	// 		int numCops; // $fp

		/* begin block 1.1 */
			// Start line: 1896
			// Start offset: 0x0006ED1C
			// Variables:
		// 		int x; // $s2
		// 		int z; // $s0
		// 		int w; // $s0
		// 		int i; // $s7
		// 		int s1; // $s1
		// 		int s2; // $a3
		// 		struct VECTOR vert; // stack offset -88
		// 		long disp[4]; // stack offset -72
		// 		long dir[4]; // stack offset -56
		// 		int alpha; // $s1
		/* end block 1.1 */
		// End offset: 0x0006EFDC
		// End Line: 1966
	/* end block 1 */
	// End offset: 0x0006EFDC
	// End Line: 1968

	/* begin block 2 */
		// Start line: 4102
	/* end block 2 */
	// End Line: 4103

	/* begin block 3 */
		// Start line: 4145
	/* end block 3 */
	// End Line: 4146

	/* begin block 4 */
		// Start line: 4146
	/* end block 4 */
	// End Line: 4147

	/* begin block 5 */
		// Start line: 4150
	/* end block 5 */
	// End Line: 4151

/* WARNING: Unknown calling convention yet parameter storage is locked */

void PlaceRoadBlockCops(void)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	int iVar2;
	uint uVar3;
	_CAR_DATA **pp_Var4;
	_CAR_DATA *p_Var5;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	undefined4 uVar10;
	int *piVar11;
	int iVar12;
	int iVar13;
	_CAR_DATA *local_98[16];
	int local_58;
	undefined4 local_54;
	int local_50;
	long local_48;
	int local_44;
	int local_40;
	int local_38;
	undefined4 local_34;
	int local_30;

	iVar13 = 0;
	if (numCopPeds < 8) {
		p_Var5 = car_data;
		pp_Var4 = local_98;
		do {
			if ((p_Var5->controlFlags & 2) != 0) {
				*pp_Var4 = p_Var5;
				pp_Var4 = pp_Var4 + 1;
				iVar13 = iVar13 + 1;
			}
			p_Var5 = p_Var5 + 1;
		} while (p_Var5 < (_CAR_DATA *)0xd4698);
		if ((iVar13 != 0) && (iVar12 = 0, 0 < iVar13)) {
			iVar6 = 0;
			do {
				piVar11 = (int *)((int)local_98 + iVar6);
				uVar10 = *(undefined4 *)(*piVar11 + 0x68);
				local_54 = 0;
				local_58 = 0;
				local_50 = 0x1000;
				sVar1 = car_cosmetics[*(byte *)(*piVar11 + 0x177)].colBox.vx;
				iVar6 = rsin(uVar10);
				iVar6 = -(local_50 * iVar6 >> 0xc);
				iVar2 = rcos(uVar10);
				local_58 = iVar6;
				local_50 = local_50 * iVar2 >> 0xc;
				local_48 = *(int *)(*piVar11 + 0x14) - player.pos[0];
				local_34 = 0;
				local_44 = 0;
				local_38 = local_50;
				local_30 = iVar6;
				local_40 = *(int *)(*piVar11 + 0x1c) - player.pos[2];
				iVar8 = *piVar11;
				iVar2 = (int)sVar1 + 400;
				iVar9 = (int)car_cosmetics[*(byte *)(iVar8 + 0x177)].colBox.vz + -0x78;
				if (local_50 * local_48 + iVar6 * local_40 + 0x800 < 0) {
					iVar2 = -iVar2;
				}
				uVar3 = *(int *)(iVar8 + 0x68) + 0x800U & 0xfff;
				iVar7 = (int)rcossin_tbl[uVar3 * 2 + 1];
				iVar6 = (int)rcossin_tbl[uVar3 * 2];
				local_48 = *(int *)(iVar8 + 0x14) - ((iVar2 * iVar7 >> 0xc) - (iVar9 * iVar6 >> 0xc));
				local_44 = -*(int *)(*piVar11 + 0x18);
				local_40 = *(int *)(*piVar11 + 0x1c) + (iVar2 * iVar6 >> 0xc) + (iVar9 * iVar7 >> 0xc);
				iVar6 = CreatePedAtLocation((long(*)[4])&local_48, 0xc);
				if (iVar6 != 0) {
					numCopPeds = numCopPeds + 1;
				}
				iVar8 = (int)rcossin_tbl[uVar3 * 2 + 1];
				iVar6 = (int)rcossin_tbl[uVar3 * 2];
				local_48 = *(int *)(*piVar11 + 0x14) - ((iVar2 * iVar8 >> 0xc) - (-iVar9 * iVar6 >> 0xc));
				local_44 = -*(int *)(*piVar11 + 0x18);
				local_40 = *(int *)(*piVar11 + 0x1c) + (iVar2 * iVar6 >> 0xc) + (-iVar9 * iVar8 >> 0xc);
				iVar6 = CreatePedAtLocation((long(*)[4])&local_48, 0xd);
				if (iVar6 != 0) {
					numCopPeds = numCopPeds + 1;
				}
				iVar12 = iVar12 + 1;
				iVar6 = iVar12 * 4;
			} while (iVar12 < iVar13);
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CreatePedAtLocation(long (*pPos)[4] /*$s2*/, int pedType /*$s1*/)
 // line 1975, offset 0x0006f00c
	/* begin block 1 */
		// Start line: 1976
		// Start offset: 0x0006F00C
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $s0
	/* end block 1 */
	// End offset: 0x0006F16C
	// End Line: 2045

	/* begin block 2 */
		// Start line: 4495
	/* end block 2 */
	// End Line: 4496

int CreatePedAtLocation(long(*pPos)[4], int pedType)
{
	UNIMPLEMENTED();
	return 0;
	/*
	PEDESTRIAN *pPed;
	int iVar1;
	_func_1 *p_Var2;
	long lVar3;

	if (pedType - 0xcU < 2) {
		if (7 < numCopPeds) {
			return 0;
		}
	}
	else {
		if (0xf < num_pedestrians) {
			return 0;
		}
	}
	pPed = CreatePedestrian();
	if (pPed == (PEDESTRIAN *)0x0) {
		return 0;
	}
	(pPed->position).vx = (*pPos)[0];
	(pPed->position).vy = (*pPos)[1];
	lVar3 = (*pPos)[2];
	pPed->pedType = CIVILIAN;
	(pPed->dir).vz = 0;
	(pPed->dir).vx = 0;
	(pPed->dir).vy = 0;
	pPed->type = (PED_ACTION_TYPE)pedType;
	pPed->flags = 0;
	(pPed->position).vz = lVar3;
	p_Var2 = (_func_1 *)PTR_CopStand_000a16a0;
	if (pedType == 8) {
		pPed->flags = 0;
		p_Var2 = (_func_1 *)PTR_CivPedWalk_000a168c;
	}
	else {
		if (((pedType < 8) || (0xd < pedType)) || (pedType < 0xc)) goto LAB_0006f100;
		pPed->flags = 8;
		pPed->pallet = 'U';
	}
	pPed->fpRestState = p_Var2;
LAB_0006f100:
	pPed->fpAgitatedState = (_func_2 *)0x0;
	SetupPedMotionData(pPed);
	if (pPed->type == PED_ACTION_COPSTAND) {
		iVar1 = MapHeight((VECTOR *)&pPed->position);
		lVar3 = -0x62 - iVar1;
	}
	else {
		if (pPed->type != PED_ACTION_COPCROUCH) {
			return 1;
		}
		iVar1 = MapHeight((VECTOR *)&pPed->position);
		lVar3 = -0x3e - iVar1;
	}
	(pPed->position).vy = lVar3;
	return 1;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawAllPedestrians()
 // line 2052, offset 0x00072290
	/* begin block 1 */
		// Start line: 2054
		// Start offset: 0x00072290
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $s0
	// 		int pedType; // $s2
	// 		struct MATRIX mStore; // stack offset -56

		/* begin block 1.1 */
			// Start line: 2071
			// Start offset: 0x0007231C

			/* begin block 1.1.1 */
				// Start line: 2078
				// Start offset: 0x0007234C
			/* end block 1.1.1 */
			// End offset: 0x0007234C
			// End Line: 2078
		/* end block 1.1 */
		// End offset: 0x00072364
		// End Line: 2085

		/* begin block 1.2 */
			// Start line: 2101
			// Start offset: 0x000723D4
		/* end block 1.2 */
		// End offset: 0x00072400
		// End Line: 2106
	/* end block 1 */
	// End offset: 0x00072430
	// End Line: 2137

	/* begin block 2 */
		// Start line: 12025
	/* end block 2 */
	// End Line: 12026

	/* begin block 3 */
		// Start line: 4104
	/* end block 3 */
	// End Line: 4105

	/* begin block 4 */
		// Start line: 12026
	/* end block 4 */
	// End Line: 12027

	/* begin block 5 */
		// Start line: 12031
	/* end block 5 */
	// End Line: 12032

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DrawAllPedestrians(void)
{
	UNIMPLEMENTED();
	/*
	PED_ACTION_TYPE PVar1;
	PEDESTRIAN **ppPVar2;
	int iVar3;
	undefined4 in_a2;
	undefined4 in_a3;
	undefined4 local_38;
	undefined4 local_30;
	undefined4 local_24;
	undefined4 local_34;
	undefined4 local_2c;
	undefined4 local_20;
	undefined4 local_28;
	undefined4 local_1c;
	PEDESTRIAN *pPed;

	local_38 = getCopControlWord(2, 0);
	local_34 = getCopControlWord(2, 0x800);
	local_30 = getCopControlWord(2, 0x1000);
	local_2c = getCopControlWord(2, 0x1800);
	local_28 = getCopControlWord(2, 0x2000);
	local_24 = getCopControlWord(2, 0x2800);
	local_20 = getCopControlWord(2, 0x3000);
	local_1c = getCopControlWord(2, 0x3800);
	pPed = pUsedPeds;
	if (pUsedPeds != (PEDESTRIAN *)0x0) {
		do {
			PVar1 = pPed->type;
			if (((uint)pPed->pedType - 2 < 2) &&
				(iVar3 = PositionVisible((VECTOR *)&pPed->position), iVar3 != 0)) {
				iVar3 = FrustrumCheck((VECTOR *)&pPed->position, 0x3c, in_a2, in_a3, local_38, local_34, local_30,
					local_2c, local_28, local_24, local_20, local_1c);
				if (iVar3 != -1) {
					if ((uint)PVar1 - 8 < 6) {
						DrawCiv(pPed);
					}
					else {
						DrawCharacter(pPed);
					}
				}
			}
			ppPVar2 = &pPed->pNext;
			pPed = *ppPVar2;
		} while (*ppPVar2 != (PEDESTRIAN *)0x0);
	}
	setCopControlWord(2, 0, local_38);
	setCopControlWord(2, 0x800, local_34);
	setCopControlWord(2, 0x1000, local_30);
	setCopControlWord(2, 0x1800, local_2c);
	setCopControlWord(2, 0x2000, local_28);
	pPed = pUsedPeds;
	while (pPed != (PEDESTRIAN *)0x0) {
		if ((((pPed->pedType < OTHER_SPRITE) && ((pPed->flags & 4U) == 0)) &&
			(iVar3 = PositionVisible((VECTOR *)&pPed->position), iVar3 != 0)) &&
			(iVar3 = FrustrumCheck((VECTOR *)&pPed->position, 0x3c, in_a2, in_a3, local_38, local_34, local_30,
				local_2c, local_28, local_24, local_20, local_1c), iVar3 != -1)) {
			DrawTanner(pPed);
		}
		pPed = pPed->pNext;
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ TannerActionHappening()
 // line 2145, offset 0x00072430
	/* begin block 1 */
		// Start line: 2147
		// Start offset: 0x00072430
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $a0
	/* end block 1 */
	// End offset: 0x00072478
	// End Line: 2158

	/* begin block 2 */
		// Start line: 12203
	/* end block 2 */
	// End Line: 12204

	/* begin block 3 */
		// Start line: 12212
	/* end block 3 */
	// End Line: 12213

	/* begin block 4 */
		// Start line: 12213
	/* end block 4 */
	// End Line: 12214

	/* begin block 5 */
		// Start line: 12215
	/* end block 5 */
	// End Line: 12216

/* WARNING: Unknown calling convention yet parameter storage is locked */

int TannerActionHappening(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	if (player.pPed == (PEDESTRIAN *)0x0) {
		return 0;
	}
	iVar1 = 0;
	if (((player.pPed)->type == PED_ACTION_PRESSBUTTON) &&
		(iVar1 = 1, (player.pPed)->frame1 != '\x0e')) {
		iVar1 = 0;
	}
	return iVar1;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ControlPedestrians()
 // line 2168, offset 0x0006f16c
	/* begin block 1 */
		// Start line: 2170
		// Start offset: 0x0006F16C
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $s0
	// 		struct PEDESTRIAN *pPedNext; // $s2
	// 		struct _CAR_DATA *pCar; // $v0

		/* begin block 1.1 */
			// Start line: 2225
			// Start offset: 0x0006F26C
		/* end block 1.1 */
		// End offset: 0x0006F2B0
		// End Line: 2233
	/* end block 1 */
	// End offset: 0x0006F2DC
	// End Line: 2241

	/* begin block 2 */
		// Start line: 4773
	/* end block 2 */
	// End Line: 4774

	/* begin block 3 */
		// Start line: 4897
	/* end block 3 */
	// End Line: 4898

	/* begin block 4 */
		// Start line: 4898
	/* end block 4 */
	// End Line: 4899

	/* begin block 5 */
		// Start line: 4902
	/* end block 5 */
	// End Line: 4903

/* WARNING: Unknown calling convention yet parameter storage is locked */

void ControlPedestrians(void)
{
	UNIMPLEMENTED();
	/*
	_CAR_DATA *cp;
	int iVar1;
	PEDESTRIAN *pPed;
	PEDESTRIAN *pPed_00;
	PEDESTRIAN *pPVar2;

	pPed = pUsedPeds;
	pPed_00 = pUsedPeds;
	if (pUsedPeds != (PEDESTRIAN *)0x0) {
		do {
			pPVar2 = pPed->pNext;
			if (pPed->pedType == CIVILIAN) {
				CalculatePedestrianInterest(pPed);
				if (pPed->fpAgitatedState == (_func_2 *)0x0) {
					(*pPed->fpRestState)(pPed);
				}
				else {
					(*pPed->fpAgitatedState)(pPed);
				}
				if ((pPed->type != PED_ACTION_GETINCAR) && (cp = CheckForCar(pPed), cp != (_CAR_DATA *)0x0))
				{
					SetupCivJump(pPed, cp);
				}
				if (bAvoidTanner == 0) {
					if (bAvoidBomb != -1) {
						SetupCivJump(pPed, (_CAR_DATA *)0x0);
						bAvoidBomb = -1;
					}
				}
				else {
					SetupCivJump(pPed, (_CAR_DATA *)0x0);
					bAvoidTanner = 0;
				}
			}
			pPed = pPVar2;
			pPed_00 = pUsedPeds;
		} while (pPVar2 != (PEDESTRIAN *)0x0);
	}
	while (pPed_00 != (PEDESTRIAN *)0x0) {
		if ((pPed_00->pedType == CIVILIAN) &&
			((iVar1 = PingOutPed(pPed_00), iVar1 != 0 || ((pPed_00->flags & 1U) != 0)))) {
			pHold = pPed_00->pNext;
			DestroyPedestrian(pPed_00);
			pPed_00 = pHold;
		}
		else {
			pPed_00 = pPed_00->pNext;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDoNowt(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2256, offset 0x00073038
	/* begin block 1 */
		// Start line: 20024
	/* end block 1 */
	// End Line: 20025

	/* begin block 2 */
		// Start line: 20722
	/* end block 2 */
	// End Line: 20723

void SetupDoNowt(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	pPed->speed = '\0';
	(pPed->dir).vz = 0;
	pPed->doing_turn = '\0';
	pPed->type = PED_ACTION_BACK;
	SetupPedMotionData(pPed);
	pPed->flags = pPed->flags | 0x10;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupWalker(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2275, offset 0x0007307c
	/* begin block 1 */
		// Start line: 20767
	/* end block 1 */
	// End Line: 20768

void SetupWalker(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	pPed->type = PED_ACTION_WALK;
	pPed->speed = '\x14';
	SetupPedMotionData(pPed);
	pPed->flags = pPed->flags | 0x10;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupRunner(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2291, offset 0x000730b8
	/* begin block 1 */
		// Start line: 20802
	/* end block 1 */
	// End Line: 20803

void SetupRunner(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	pPed->type = PED_ACTION_RUN;
	pPed->frame1 = '\0';
	pPed->speed = '(';
	SetupPedMotionData(pPed);
	pPed->flags = pPed->flags | 0x10;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupBack(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2302, offset 0x000730fc
	/* begin block 1 */
		// Start line: 20826
	/* end block 1 */
	// End Line: 20827

void SetupBack(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	pPed->type = PED_ACTION_WALK;
	pPed->frame1 = '\0';
	pPed->speed = -10;
	SetupPedMotionData(pPed);
	pPed->flags = pPed->flags | 0x10;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivGetIn(struct PEDESTRIAN *pPed /*$s2*/)
 // line 2325, offset 0x00072dfc
	/* begin block 1 */
		// Start line: 2326
		// Start offset: 0x00072DFC
		// Variables:
	// 		struct DRIVER2_STRAIGHT *str; // $s1
	// 		struct DRIVER2_CURVE *crv; // $s0

		/* begin block 1.1 */
			// Start line: 2326
			// Start offset: 0x00072DFC
		/* end block 1.1 */
		// End offset: 0x00072EE4
		// End Line: 2345
	/* end block 1 */
	// End offset: 0x00072EE4
	// End Line: 2346

	/* begin block 2 */
		// Start line: 18692
	/* end block 2 */
	// End Line: 18693

	/* begin block 3 */
		// Start line: 4650
	/* end block 3 */
	// End Line: 4651

	/* begin block 4 */
		// Start line: 18693
	/* end block 4 */
	// End Line: 18694

void CivGetIn(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	uint uVar2;
	DRIVER2_CURVE *curve;
	DRIVER2_STRAIGHT *straight;

	straight = (DRIVER2_STRAIGHT *)0x0;
	InitCivState(pCivCarToGetIn, (char *)0x0);
	uVar2 = *(uint *)pCivCarToGetIn->ai;
	curve = (DRIVER2_CURVE *)0x0;
	if ((((uVar2 & 0xffffe000) == 0) && ((int)(uVar2 & 0x1fff) < NumDriver2Straights)) &&
		(-1 < (int)uVar2)) {
		straight = Driver2StraightsPtr + uVar2;
	}
	else {
		curve = Driver2CurvesPtr + *(int *)pCivCarToGetIn->ai + -0x4000;
	}
	iVar1 = CheckChangeLanes(straight, curve, *(int *)(pCivCarToGetIn->ai + 0x28), pCivCarToGetIn, 0);
	pCivCarToGetIn->ai[0xfb] = (byte)iVar1;
	DestroyPedestrian(pPed);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CopStand(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2353, offset 0x00072da0
	/* begin block 1 */
		// Start line: 2354
		// Start offset: 0x00072DA0
		// Variables:
	// 		struct VECTOR v; // stack offset -24
	/* end block 1 */
	// End offset: 0x00072DFC
	// End Line: 2377

	/* begin block 2 */
		// Start line: 18683
	/* end block 2 */
	// End Line: 18684

	/* begin block 3 */
		// Start line: 4706
	/* end block 3 */
	// End Line: 4707

void CopStand(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	short sVar1;

	pPed->frame1 = '\0';
	sVar1 = ratan2();
	(pPed->dir).vy = 0x400 - sVar1;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedDoNothing(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2385, offset 0x0006f2dc
	/* begin block 1 */
		// Start line: 5187
	/* end block 1 */
	// End Line: 5188

	/* begin block 2 */
		// Start line: 5332
	/* end block 2 */
	// End Line: 5333

void PedDoNothing(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	char cVar3;
	byte bVar4;
	int iVar5;
	short sVar6;

	pPed->speed = '\0';
	if ((pPed->flags & 0x10U) == 0) {
		SetupDoNowt(pPed);
		pPed->flags = pPed->flags | 0x10;
	}
	if ((tannerPad & 0x1040) != 0) {
		iIdleTimer = 0;
		pPed->flags = pPed->flags & 0xffffffef;
		pPed->fpAgitatedState = PTR_PedUserRunner_000a1678;
		SetupRunner(pPed);
		goto LAB_0006f530;
	}
	if ((tannerPad & 0x4080) != 0) {
		iIdleTimer = 0;
		pPed->flags = pPed->flags & 0xffffffef;
		pPed->fpAgitatedState = PTR_PedUserWalker_000a1674;
		SetupBack(pPed);
		goto LAB_0006f530;
	}
	sVar6 = (short)tannerTurnStep;
	sVar1 = (short)tannerTurnMax;
	if ((tannerPad & 0x2000) == 0) {
		if ((tannerPad & 0x8000) == 0) {
			pPed->frame1 = '\0';
			iIdleTimer = iIdleTimer + 1;
			iVar5 = tannerTurn + 2;
			if (tannerTurn < 0) {
				tannerTurn = iVar5;
				if (0 < iVar5) {
					tannerTurn = 0;
					goto LAB_0006f4a8;
				}
			}
			else {
			LAB_0006f4a8:
				iVar5 = tannerTurn + -2;
				if ((0 < tannerTurn) && (tannerTurn = iVar5, iVar5 < 0)) {
					tannerTurn = 0;
				}
			}
			if (tannerTurn != 0) {
				if (tannerTurn < 0) {
					sVar6 = ((pPed->dir).vy + 0x40) -
						((short)tannerTurn + (short)tannerTurnMax) * (short)tannerTurnStep;
				}
				else {
					sVar6 = (pPed->dir).vy + -0x40 +
						((short)tannerTurnMax - (short)tannerTurn) * (short)tannerTurnStep;
				}
				(pPed->dir).vy = sVar6;
			}
			goto LAB_0006f530;
		}
		iIdleTimer = 0;
		tannerTurn = tannerTurn + 2;
		if (tannerTurnMax < tannerTurn) {
			tannerTurn = tannerTurnMax;
		}
		sVar2 = (short)tannerTurn;
		bVar4 = pPed->frame1 + 1;
		pPed->frame1 = bVar4;
		(pPed->dir).vy = (pPed->dir).vy + -0x40 + (sVar1 - sVar2) * sVar6;
		if (0xf < bVar4) {
			pPed->frame1 = '\0';
		}
	}
	else {
		iIdleTimer = 0;
		tannerTurn = tannerTurn + -2;
		if (tannerTurn < -tannerTurnMax) {
			tannerTurn = -tannerTurnMax;
		}
		cVar3 = pPed->frame1;
		(pPed->dir).vy = ((pPed->dir).vy + 0x40) - ((short)tannerTurn + sVar1) * sVar6;
		if (cVar3 == '\0') {
			cVar3 = '\x0f';
		}
		else {
			cVar3 = cVar3 + -1;
		}
		pPed->frame1 = cVar3;
	}
	pPed->head_rot = 0;
LAB_0006f530:
	if (0x77 < iIdleTimer) {
		pPed->frame1 = '\0';
		pPed->type = PED_ACTION_TIME;
		SetupPedMotionData(pPed);
		pPed->flags = pPed->flags | 0x10;
		pPed->fpAgitatedState = PTR_PedCarryOutAnimation_000a1684;
		iIdleTimer = -2;
		if (pPed->type == PED_ACTION_TIME) {
			iAllowWatch = 3;
		}
		if (iAllowWatch != 0) {
			iAllowWatch = iAllowWatch + -1;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedUserRunner(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2523, offset 0x0006f5ac
	/* begin block 1 */
		// Start line: 2524
		// Start offset: 0x0006F5AC
	/* end block 1 */
	// End offset: 0x0006F80C
	// End Line: 2632

	/* begin block 2 */
		// Start line: 5640
	/* end block 2 */
	// End Line: 5641

void PedUserRunner(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	short sVar3;
	char cVar4;
	uint uVar5;
	int iVar6;
	char cVar7;
	short sVar8;

	if ((pPed->flags & 0x10U) == 0) {
		SetupRunner(pPed);
	}
	if ((tannerPad & 0x1040) == 0) {
		uVar5 = pPed->flags;
		pPed->doing_turn = '\0';
		(pPed->dir).vz = 0;
		pPed->speed = '\0';
		pPed->fpAgitatedState = (_func_2 *)0x0;
		pPed->flags = uVar5 & 0xffffffef;
	}
	else {
		if (bStopTanner == 0) {
			pPed->speed = '(' - (char)(tannerDeathTimer >> 1);
		}
		else {
			pPed->speed = '\0';
		}
	}
	if ((tannerPad & 0x2000) != 0) {
		if (-4 < pPed->doing_turn) {
			pPed->doing_turn = pPed->doing_turn + -1;
		}
		tannerTurn = tannerTurn + -2;
		if (tannerTurn < -tannerTurnMax) {
			tannerTurn = -tannerTurnMax;
		}
		sVar2 = (short)tannerTurn;
		sVar3 = (short)tannerTurnMax;
		sVar1 = (short)tannerTurnStep;
		sVar8 = (pPed->dir).vy;
		pPed->head_rot = 0;
		(pPed->dir).vz = (short)pPed->doing_turn * 0x14;
		sVar8 = (sVar8 + 0x40) - (sVar2 + sVar3) * sVar1;
		goto LAB_0006f7f0;
	}
	if ((tannerPad & 0x8000) != 0) {
		if (pPed->doing_turn < '\x04') {
			pPed->doing_turn = pPed->doing_turn + '\x01';
		}
		tannerTurn = tannerTurn + 2;
		if (tannerTurnMax < tannerTurn) {
			tannerTurn = tannerTurnMax;
		}
		sVar2 = (short)tannerTurn;
		sVar1 = (short)tannerTurnMax;
		sVar8 = (short)tannerTurnStep;
		pPed->head_rot = 0;
		(pPed->dir).vz = (short)pPed->doing_turn * 0x14;
		sVar8 = (pPed->dir).vy + -0x40 + (sVar1 - sVar2) * sVar8;
		goto LAB_0006f7f0;
	}
	cVar4 = pPed->doing_turn;
	cVar7 = pPed->doing_turn;
	if (cVar4 < '\0') {
		pPed->doing_turn = cVar7 + '\x02';
		cVar4 = pPed->doing_turn;
		cVar7 = pPed->doing_turn;
	}
	if ('\0' < cVar4) {
		pPed->doing_turn = cVar7 + -2;
	}
	if (tannerTurn < 0) {
		tannerTurn = tannerTurn + 2;
		if (0 < tannerTurn) {
			tannerTurn = 0;
			goto code_r0x0006f79c;
		}
	}
	else {
	code_r0x0006f79c:
		iVar6 = tannerTurn + -2;
		if ((0 < tannerTurn) && (tannerTurn = iVar6, iVar6 < 0)) {
			tannerTurn = 0;
		}
	}
	sVar2 = (short)tannerTurn;
	sVar1 = (short)tannerTurnMax;
	sVar8 = (short)tannerTurnStep;
	(pPed->dir).vz = (short)pPed->doing_turn * 0x14;
	sVar8 = (pPed->dir).vy + -0x40 + (sVar1 - sVar2) * sVar8;
LAB_0006f7f0:
	(pPed->dir).vy = sVar8;
	AnimatePed(pPed);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedUserWalker(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2639, offset 0x00072944
	/* begin block 1 */
		// Start line: 2640
		// Start offset: 0x00072944
		// Variables:
	// 		static int speed; // offset 0x80
	/* end block 1 */
	// End offset: 0x00072A10
	// End Line: 2694

	/* begin block 2 */
		// Start line: 17115
	/* end block 2 */
	// End Line: 17116

	/* begin block 3 */
		// Start line: 5278
	/* end block 3 */
	// End Line: 5279

void PedUserWalker(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	short sVar1;

	if ((pPed->flags & 0x10U) == 0) {
		SetupWalker(pPed);
	}
	if ((tannerPad & 0x4080) == 0) {
		pPed->type = PED_ACTION_STOPPING;
		pPed->frame1 = '\0';
		pPed->speed = '\0';
		pPed->fpAgitatedState = (_func_2 *)0x0;
		pPed->flags = pPed->flags & 0xffffffef;
	}
	else {
		pPed->speed = -10;
	}
	if ((tannerPad & 0x2000) != 0) {
		sVar1 = (pPed->dir).vy;
		pPed->head_rot = 0;
		(pPed->dir).vy = sVar1 + 0x14;
	}
	if ((tannerPad & 0x8000) != 0) {
		sVar1 = (pPed->dir).vy;
		pPed->head_rot = 0;
		(pPed->dir).vy = sVar1 + -0x14;
	}
	AnimatePed(pPed);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedCarryOutAnimation(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2702, offset 0x00072a10
	/* begin block 1 */
		// Start line: 17238
	/* end block 1 */
	// End Line: 17239

	/* begin block 2 */
		// Start line: 17247
	/* end block 2 */
	// End Line: 17248

void PedCarryOutAnimation(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	pPed->speed = '\0';
	if (tannerPad != 0) {
		pPed->frame1 = '\0';
		pPed->fpAgitatedState = (_func_2 *)0x0;
		pPed->flags = pPed->flags & 0xffffffef;
		bFreezeAnimation = 0;
		bReverseAnimation = 0;
		allreadydone = 0;
	}
	if (bFreezeAnimation == 0) {
		AnimatePed(pPed);
	}
	else {
		if (iFreezeTimer == 0) {
			bFreezeAnimation = 0;
			bReverseAnimation = 1;
			iFreezeTimer = 0;
		}
		iFreezeTimer = iFreezeTimer + -1;
	}
	if (bReverseAnimation == 0) {
		if ((0xe < (byte)pPed->frame1) && (bFreezeAnimation == 0)) {
			if (pPed->type == PED_ACTION_TIME) {
				bFreezeAnimation = 1;
				iFreezeTimer = 0xc;
			}
			else {
				pPed->frame1 = '\0';
				pPed->fpAgitatedState = (_func_2 *)0x0;
				pPed->flags = pPed->flags & 0xffffffef;
			}
		}
	}
	else {
		if (pPed->frame1 == '\0') {
			pPed->frame1 = '\0';
			pPed->fpAgitatedState = (_func_2 *)0x0;
			pPed->flags = pPed->flags & 0xffffffef;
			bFreezeAnimation = 0;
			bReverseAnimation = 0;
			allreadydone = 0;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedGetOutCar(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2796, offset 0x00072bec
	/* begin block 1 */
		// Start line: 17673
	/* end block 1 */
	// End Line: 17674

	/* begin block 2 */
		// Start line: 5592
	/* end block 2 */
	// End Line: 5593

void PedGetOutCar(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	short sVar1;

	player.pos[0] = (pPed->position).vx;
	pPed->speed = '\0';
	pPed->frame1 = pPed->frame1 + '\x01';
	player.pos[1] = -(pPed->position).vy;
	player.pos[2] = (pPed->position).vz;
	if (0xe < (byte)pPed->frame1) {
		ChangeCarPlayerToPed(0);
		sVar1 = *(short *)&(carToGetIn->hd).direction;
		pPed->speed = '\0';
		pPed->fpAgitatedState = (_func_2 *)0x0;
		pPed->flags = pPed->flags & 0xffffffef;
		(pPed->dir).vy = sVar1 + -0x800;
		bReverseYRotation = 0;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupGetOutCar(struct PEDESTRIAN *pPed /*$s5*/, struct _CAR_DATA *pCar /*$s3*/, int side /*$s7*/)
 // line 2827, offset 0x0006f80c
	/* begin block 1 */
		// Start line: 2828
		// Start offset: 0x0006F80C
		// Variables:
	// 		int alpha; // $s2
	// 		long disp[4]; // stack offset -80
	// 		long dir[4]; // stack offset -64
	// 		struct SVECTOR vert; // stack offset -48
	// 		int x; // $s4
	// 		int z; // $s0
	// 		int a; // $s6
	// 		int nx; // $a3
	// 		int nz; // $a1
	/* end block 1 */
	// End offset: 0x0006FA3C
	// End Line: 2891

	/* begin block 2 */
		// Start line: 6072
	/* end block 2 */
	// End Line: 6073

	/* begin block 3 */
		// Start line: 6268
	/* end block 3 */
	// End Line: 6269

void SetupGetOutCar(PEDESTRIAN *pPed, _CAR_DATA *pCar, int side)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	short sVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	int iVar7;

	lastCarCameraView = ZEXT14((byte)player.cameraView);
	iVar5 = (pCar->hd).direction;
	pPed->speed = '\0';
	iVar6 = (pCar->hd).direction;
	iVar3 = rsin(iVar6);
	sVar2 = rcos(iVar6);
	iVar7 = 400;
	bVar1 = -1 < (int)sVar2 * ((pCar->hd).where.t[0] - (pPed->position).vx) +
		(int)(short)-(short)(iVar3 * 0x1000 >> 0xc) *
		((pCar->hd).where.t[2] - (pPed->position).vz) + 0x800;
	if (bVar1) {
		sVar2 = (short)iVar6 + -0x400;
	}
	else {
		sVar2 = (short)iVar6 + 0x400;
	}
	bReverseYRotation = ZEXT14(!bVar1);
	(pPed->dir).vy = sVar2;
	if (side == 1) {
		iVar7 = -400;
	}
	uVar4 = iVar5 + 0x800U & 0xfff;
	if (NoPlayerControl == 0) {
		player.cameraView = '\x05';
		player.cameraPos.vx =
			(pCar->hd).where.t[0] -
			((iVar7 * (int)rcossin_tbl[uVar4 * 2 + 1] >> 0xc) -
			((int)rcossin_tbl[uVar4 * 2] * 800 >> 0xc));
		player.cameraPos.vy = -200 - (pCar->hd).where.t[1];
		player.cameraPos.vz =
			(pCar->hd).where.t[2] +
			(iVar7 * (int)rcossin_tbl[uVar4 * 2] >> 0xc) +
			((int)rcossin_tbl[uVar4 * 2 + 1] * 800 >> 0xc);
	}
	pPed->frame1 = '\0';
	carToGetIn = pCar;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupGetInCar(struct PEDESTRIAN *pPed /*$s2*/)
 // line 2898, offset 0x0006fa3c
	/* begin block 1 */
		// Start line: 2899
		// Start offset: 0x0006FA3C
		// Variables:
	// 		int alpha; // $s1
	// 		long disp[4]; // stack offset -72
	// 		long dir[4]; // stack offset -56
	// 		struct SVECTOR vert; // stack offset -40

		/* begin block 1.1 */
			// Start line: 2934
			// Start offset: 0x0006FB2C
			// Variables:
		// 		int x; // $t1
		// 		int z; // $t2
		// 		int a; // $a0
		// 		int nx; // $a3
		// 		int nz; // $a1
		/* end block 1.1 */
		// End offset: 0x0006FC24
		// End Line: 2957

		/* begin block 1.2 */
			// Start line: 2968
			// Start offset: 0x0006FC70
			// Variables:
		// 		long pos[4]; // stack offset -32
		/* end block 1.2 */
		// End offset: 0x0006FC70
		// End Line: 2969
	/* end block 1 */
	// End offset: 0x0006FD08
	// End Line: 2988

	/* begin block 2 */
		// Start line: 6510
	/* end block 2 */
	// End Line: 6511

	/* begin block 3 */
		// Start line: 6518
	/* end block 3 */
	// End Line: 6519

	/* begin block 4 */
		// Start line: 6525
	/* end block 4 */
	// End Line: 6526

void SetupGetInCar(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	_CAR_DATA *p_Var1;
	short sVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	long local_20;
	int local_1c;
	long local_18;

	bReverseAnimation = 0;
	pPed->speed = '\0';
	iVar6 = (carToGetIn->hd).direction;
	iVar3 = rsin(iVar6);
	sVar2 = rcos(iVar6);
	p_Var1 = carToGetIn;
	if ((int)sVar2 * ((carToGetIn->hd).where.t[0] - (pPed->position).vx) +
		(int)(short)-(short)(iVar3 * 0x1000 >> 0xc) *
		((carToGetIn->hd).where.t[2] - (pPed->position).vz) + 0x800 < 0) {
		iVar6 = iVar6 + 0x400;
	}
	else {
		iVar6 = iVar6 + -0x400;
	}
	iVar5 = 400;
	(pPed->dir).vy = (short)iVar6;
	iVar3 = (p_Var1->hd).direction;
	if (iVar3 < iVar6) {
		iVar5 = -400;
	}
	uVar4 = iVar3 + 0x800U & 0xfff;
	if ((NoPlayerControl == 0) && (gInGameCutsceneActive == 0)) {
		player.cameraView = '\x05';
		player.cameraPos.vx =
			(p_Var1->hd).where.t[0] -
			((iVar5 * (int)rcossin_tbl[uVar4 * 2 + 1] >> 0xc) -
			((int)rcossin_tbl[uVar4 * 2] * 800 >> 0xc));
		player.cameraPos.vy = -200 - (p_Var1->hd).where.t[1];
		player.cameraPos.vz =
			(p_Var1->hd).where.t[2] +
			(iVar5 * (int)rcossin_tbl[uVar4 * 2] >> 0xc) +
			((int)rcossin_tbl[uVar4 * 2 + 1] * 800 >> 0xc);
	}
	if ((carToGetIn->controlFlags & 4) == 0) {
		if (((carToGetIn->controlType == '\x02') && (carToGetIn->ai[0xf9] == 3)) &&
			(carToGetIn->ai[0xc] == 5)) {
			carToGetIn->controlFlags = carToGetIn->controlFlags | 4;
		}
		else {
			local_20 = player.pos[0];
			local_1c = -player.pos[1];
			local_18 = player.pos[2];
			CreatePedAtLocation((long(*)[4])&local_20, 8);
			Start3DSoundVolPitch(-1, 6, 5, local_20, local_1c, local_18, 0, 0x1000);
			carToGetIn->controlFlags = carToGetIn->controlFlags | 4;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedGetInCar(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2994, offset 0x00072b5c
	/* begin block 1 */
		// Start line: 2995
		// Start offset: 0x00072B5C
		// Variables:
	// 		long disp[4]; // stack offset -48
	// 		long dir[4]; // stack offset -32
	// 		struct SVECTOR vert; // stack offset -16
	/* end block 1 */
	// End offset: 0x00072BEC
	// End Line: 3018

	/* begin block 2 */
		// Start line: 17840
	/* end block 2 */
	// End Line: 17841

void PedGetInCar(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	_CAR_DATA *newCar;
	int playerID;

	pPed->speed = '\0';
	if ((byte)pPed->frame1 < 0xf) {
		AnimatePed(pPed);
	}
	else {
		playerID = (int)pPed->padId;
		pPed->speed = '\0';
		newCar = carToGetIn;
		pPed->fpAgitatedState = (_func_2 *)0x0;
		if (playerID < 0) {
			playerID = -playerID;
		}
		pPed->flags = pPed->flags & 0xffffffef;
		ChangePedPlayerToCar(playerID, newCar);
		DestroyPedestrian(pPed);
		pPlayerPed = (PEDESTRIAN *)0x0;
		bTannerSitting = 0;
		numTannerPeds = numTannerPeds + -1;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupPressButton(struct PEDESTRIAN *pPed /*$s0*/)
 // line 3026, offset 0x00072904
	/* begin block 1 */
		// Start line: 17494
	/* end block 1 */
	// End Line: 17495

	/* begin block 2 */
		// Start line: 6052
	/* end block 2 */
	// End Line: 6053

void SetupPressButton(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	undefined *puVar1;

	pPed->type = PED_ACTION_PRESSBUTTON;
	SetupPedMotionData(pPed);
	puVar1 = PTR_PedPressButton_000a1698;
	pPed->speed = '\0';
	pPed->frame1 = '\0';
	pPed->fpAgitatedState = puVar1;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedPressButton(struct PEDESTRIAN *pPed /*$v1*/)
 // line 3040, offset 0x00072c90
	/* begin block 1 */
		// Start line: 18175
	/* end block 1 */
	// End Line: 18176

void PedPressButton(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	if ((byte)pPed->frame1 < 0xf) {
		AnimatePed(pPed);
	}
	else {
		pPed->type = PED_ACTION_BACK;
		pPed->fpAgitatedState = (_func_2 *)0x0;
		pPed->frame1 = '\0';
		SetupPedMotionData(pPed);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupTannerSitDown(struct PEDESTRIAN *pPed /*$s0*/)
 // line 3060, offset 0x000728c8
	/* begin block 1 */
		// Start line: 6120
	/* end block 1 */
	// End Line: 6121

void SetupTannerSitDown(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	undefined *puVar1;

	pPed->type = PED_ACTION_SIT;
	SetupPedMotionData(pPed);
	puVar1 = PTR_TannerSitDown_000a169c;
	pPed->frame1 = '\0';
	pPed->fpAgitatedState = puVar1;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ TannerCameraHandler(struct PEDESTRIAN *pPed /*$a0*/)
 // line 3074, offset 0x0006fd08
	/* begin block 1 */
		// Start line: 3076
		// Start offset: 0x0006FD08
		// Variables:
	// 		int padsteer; // $a3
	// 		int maxY; // $t1
	// 		int maxX; // $t5
	// 		int range; // $t0
	// 		int minX; // $t4
	// 		int extra; // $a3
	/* end block 1 */
	// End offset: 0x0006FF48
	// End Line: 3150

	/* begin block 2 */
		// Start line: 6830
	/* end block 2 */
	// End Line: 6831

	/* begin block 3 */
		// Start line: 6917
	/* end block 3 */
	// End Line: 6918

	/* begin block 4 */
		// Start line: 6918
	/* end block 4 */
	// End Line: 6919

	/* begin block 5 */
		// Start line: 6927
	/* end block 5 */
	// End Line: 6928

/* WARNING: Removing unreachable block (ram,0x0006fe58) */
/* WARNING: Removing unreachable block (ram,0x0006fde0) */
/* WARNING: Removing unreachable block (ram,0x0006fe8c) */

void TannerCameraHandler(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	short sVar2;
	int iVar3;

	camera_position.vy = ((int)pPed->head_pos + -0x1c) - player.pos[1];
	if (Pads[player.padid].type == '\x04') {
		iVar3 = (int)Pads[player.padid].mapanalog[0];
		if ((iVar3 < -0x20) || (0x20 < iVar3)) {
			iVar1 = iVar3;
			if (iVar3 < 0) {
				iVar1 = -iVar3;
			}
			tannerLookAngle.vy = (iVar1 + -0x20) * 9;
			if (iVar3 < 0) {
				tannerLookAngle.vy = (iVar1 + -0x20) * -9;
			}
		}
		else {
			tannerLookAngle.vy = 0;
		}
		tannerLookAngle.vx = -(int)Pads[player.padid].mapanalog[1];
		if (tannerLookAngle.vx < -0x20) {
			tannerLookAngle.vx = tannerLookAngle.vx + -0x80;
		}
		else {
			if (tannerLookAngle.vx < 0x21) {
				tannerLookAngle.vx = 0;
			}
		}
	}
	else {
		tannerLookAngle.vx = 0;
		tannerLookAngle.vy = 0;
		tannerLookAngle.vz = 0;
	}
	if ((padd & 1U) == 0) {
		sVar2 = 0;
		if ((padd & 2U) != 0) {
			sVar2 = -0x400;
		}
	}
	else {
		sVar2 = 0x400;
		if ((padd & 2U) != 0) {
			sVar2 = 0x800;
		}
	}
	camera_position.vx = player.pos[0];
	camera_position.vz = player.pos[2];
	camera_angle.vx = camAngle.vx + (short)tannerLookAngle.vx;
	camera_angle.vy = (camAngle.vy - (short)tannerLookAngle.vy) + sVar2 & 0xfff;
	camera_angle.vz = camAngle.vz + (short)tannerLookAngle.vz;
	bTannerSitting = 1;
	tracking_car = '\0';
	player.cameraPos.vx = player.pos[0];
	player.cameraPos.vy = camera_position.vy;
	player.cameraPos.vz = player.pos[2];
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ TannerSitDown(struct PEDESTRIAN *pPed /*$a2*/)
 // line 3157, offset 0x0006ff48
	/* begin block 1 */
		// Start line: 3158
		// Start offset: 0x0006FF48
		// Variables:
	// 		struct VECTOR angle; // stack offset -24
	/* end block 1 */
	// End offset: 0x000700D0
	// End Line: 3219

	/* begin block 2 */
		// Start line: 7110
	/* end block 2 */
	// End Line: 7111

	/* begin block 3 */
		// Start line: 7118
	/* end block 3 */
	// End Line: 7119

void TannerSitDown(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;
	int iVar2;

	if ((oldCamView != 2) && (player.cameraView == '\x02')) {
		camAngle.vx = camera_angle.vx;
		camAngle.vy = camera_angle.vy;
		camAngle.vz = camera_angle.vz;
	}
	if (pPed->frame1 == '\x0f') {
		if (bReverseAnimation == 0) {
			oldCamView = ZEXT14((byte)player.cameraView);
			bFreezeAnimation = 1;
			if (player.cameraView == '\x02') {
				uVar1 = pPed->flags | 4;
			}
			else {
				bTannerSitting = 0;
				uVar1 = pPed->flags & 0xfffffffb;
			}
			pPed->flags = uVar1;
			if ((tannerPad & 0x10) == 0) {
				return;
			}
			tracking_car = '\x01';
			bReverseAnimation = 1;
			bFreezeAnimation = 0;
			bTannerSitting = 0;
			pPed->flags = pPed->flags & 0xfffffffb;
			oldCamView = -1;
			return;
		}
	LAB_00070054:
		if (pPed->frame1 == '\0') {
			pPed->frame1 = '\0';
			pPed->fpAgitatedState = (_func_2 *)0x0;
			pPed->flags = pPed->flags & 0xffffffef;
			tannerLookAngle.vx = 0;
			tannerLookAngle.vy = 0;
			tannerLookAngle.vz = 0;
			bFreezeAnimation = 0;
			bReverseAnimation = 0;
			return;
		}
		if (bReverseAnimation != 0) {
			iVar2 = (pPed->position).vy + -2;
			goto LAB_000700b4;
		}
	}
	else {
		if (bReverseAnimation != 0) goto LAB_00070054;
	}
	iVar2 = (pPed->position).vy + 2;
LAB_000700b4:
	(pPed->position).vy = iVar2;
	AnimatePed(pPed);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ AnimatePed(struct PEDESTRIAN *pPed /*$s0*/)
 // line 3227, offset 0x000700d0
	/* begin block 1 */
		// Start line: 3228
		// Start offset: 0x000700D0

		/* begin block 1.1 */
			// Start line: 3238
			// Start offset: 0x000700F0
			// Variables:
		// 		int mapheight; // $a3
		// 		int reverse; // $s1

			/* begin block 1.1.1 */
				// Start line: 3241
				// Start offset: 0x000700F0
				// Variables:
			// 		struct VECTOR vec; // stack offset -32
			/* end block 1.1.1 */
			// End offset: 0x0007015C
			// End Line: 3266

			/* begin block 1.1.2 */
				// Start line: 3330
				// Start offset: 0x0007030C
				// Variables:
			// 		int sfc; // $v1
			/* end block 1.1.2 */
			// End offset: 0x000703BC
			// End Line: 3335
		/* end block 1.1 */
		// End offset: 0x00070468
		// End Line: 3348
	/* end block 1 */
	// End offset: 0x00070468
	// End Line: 3350

	/* begin block 2 */
		// Start line: 7270
	/* end block 2 */
	// End Line: 7271

	/* begin block 3 */
		// Start line: 7279
	/* end block 3 */
	// End Line: 7280

	/* begin block 4 */
		// Start line: 7285
	/* end block 4 */
	// End Line: 7286

void AnimatePed(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	PED_ACTION_TYPE PVar2;
	ushort uVar3;
	bool bVar4;
	int iVar5;
	byte bVar6;
	uint uVar7;
	long lVar8;
	VECTOR local_20;

	if (pauseflag == 0) {
		local_20.vx = (pPed->position).vx;
		cVar1 = pPed->speed;
		local_20.vz = (pPed->position).vz;
		local_20.vy = -(pPed->position).vy;
		if ((pPed->pedType == CIVILIAN) && ((pPed->flags & 0x8000U) != 0)) {
			iVar5 = MapHeight(&local_20);
			lVar8 = -0x3c - iVar5;
		}
		else {
			iVar5 = MapHeight(&local_20);
			lVar8 = -0x82 - iVar5;
		}
		if (cVar1 < '\0') {
			uVar3 = (pPed->dir).vy;
			cVar1 = pPed->speed;
			(pPed->position).vx =
				(pPed->position).vx - ((int)cVar1 * (int)rcossin_tbl[((uint)uVar3 & 0xfff) * 2] >> 0xc);
			iVar5 = (pPed->position).vz -
				((int)cVar1 * (int)rcossin_tbl[(-(int)(short)uVar3 & 0xfffU) * 2 + 1] >> 0xc);
		}
		else {
			cVar1 = pPed->speed;
			uVar7 = (int)(pPed->dir).vy - 0x800U & 0xfff;
			(pPed->position).vx = (pPed->position).vx + ((int)cVar1 * (int)rcossin_tbl[uVar7 * 2] >> 0xc);
			iVar5 = (pPed->position).vz + ((int)cVar1 * (int)rcossin_tbl[uVar7 * 2 + 1] >> 0xc);
		}
		(pPed->position).vz = iVar5;
		PVar2 = pPed->type;
		if (((PVar2 != PED_ACTION_SIT) && (PVar2 != PED_ACTION_COPCROUCH)) &&
			(PVar2 != PED_ACTION_COPSTAND)) {
			(pPed->position).vy = lVar8;
			(pPed->velocity).vy = 10;
		}
		if ((bReverseAnimation == 0) || (pPed->pedType != TANNER_MODEL)) {
			bVar6 = pPed->frame1 + 1;
			pPed->frame1 = bVar6;
			if ((uint)pPed->type - 8 < 3) {
				bVar4 = bVar6 < 0x1f;
			}
			else {
				bVar4 = bVar6 < 0x10;
			}
			if (!bVar4) {
				pPed->frame1 = '\0';
			}
		}
		else {
			if (pPed->frame1 == '\0') {
				pPed->frame1 = '\x0f';
			}
			pPed->frame1 = pPed->frame1 + -1;
		}
		if (((pPed->pedType == TANNER_MODEL) && (pPed->type < PED_ACTION_BACK)) &&
			((iVar5 = PedSurfaceType((VECTOR *)&pPed->position), iVar5 != 4 &&
			(((iVar5 != 6 && (iVar5 != 0xb)) && (iVar5 != 9)))))) {
			if (pPed->frame1 == '\x03') {
				Start3DSoundVolPitch
				(-1, 6, 0, (pPed->position).vx, (pPed->position).vy, (pPed->position).vz, -5000, 0x1000);
			}
			if (pPed->frame1 == '\v') {
				Start3DSoundVolPitch
				(-1, 6, 1, (pPed->position).vx, (pPed->position).vy, (pPed->position).vz, -5000, 0x1000);
			}
		}
		if (pPed->pedType != CIVILIAN) {
			iVar5 = (int)pPed->padId;
			if (iVar5 < 0) {
				iVar5 = -iVar5;
			}
			(&player)[iVar5].pos[0] = (pPed->position).vx;
			iVar5 = (int)pPed->padId;
			if (iVar5 < 0) {
				iVar5 = -iVar5;
			}
			(&player)[iVar5].pos[1] = -(pPed->position).vy;
			iVar5 = (int)pPed->padId;
			if (iVar5 < 0) {
				iVar5 = -iVar5;
			}
			(&player)[iVar5].pos[2] = (pPed->position).vz;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DeActivatePlayerPedestrian(struct PEDESTRIAN *pPed /*$s3*/)
 // line 3357, offset 0x0007216c
	/* begin block 1 */
		// Start line: 3358
		// Start offset: 0x0007216C
		// Variables:
	// 		int distToCarSq; // stack offset -32
	// 		struct _CAR_DATA *closestCar; // $s1
	// 		struct _PLAYER *pPlayer; // $v0
	// 		struct VECTOR point; // stack offset -48
	// 		int getIn; // $s2

		/* begin block 1.1 */
			// Start line: 3384
			// Start offset: 0x0007221C
		/* end block 1.1 */
		// End offset: 0x00072274
		// End Line: 3395
	/* end block 1 */
	// End offset: 0x00072290
	// End Line: 3396

	/* begin block 2 */
		// Start line: 6714
	/* end block 2 */
	// End Line: 6715

void DeActivatePlayerPedestrian(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	_CAR_DATA *cp;
	int iVar1;
	int iVar2;
	int local_20[2];

	iVar2 = 0;
	iVar1 = (int)pPed->padId;
	if (iVar1 < 0) {
		iVar1 = -iVar1;
	}
	cp = FindClosestCar((&player)[iVar1].pos[0], (&player)[iVar1].pos[1], (&player)[iVar1].pos[2],
		local_20);
	if ((cp->ap).model == '\x04') {
		iVar2 = FindPointOfCollision(cp, (VECTOR *)&pPed->position);
	}
	else {
		if ((cp != (_CAR_DATA *)0x0) && (iVar1 = TannerCanEnterCar(cp, local_20[0]), iVar1 != 0)) {
			iVar2 = 1;
		}
	}
	if (iVar2 != 0) {
		carToGetIn = cp;
		pPed->type = PED_ACTION_GETINCAR;
		pPed->fpAgitatedState = PTR_PedGetInCar_000a167c;
		Start3DSoundVolPitch(-1, 6, 2, player.pos[0], player.pos[1], player.pos[2], 0, 0x1000);
		SetupPedestrian(pPed);
		SetupGetInCar(pPed);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivPedDoNothing(struct PEDESTRIAN *pPed /*$a0*/)
 // line 3402, offset 0x00072ce0
	/* begin block 1 */
		// Start line: 18899
	/* end block 1 */
	// End Line: 18900

	/* begin block 2 */
		// Start line: 18900
	/* end block 2 */
	// End Line: 18901

void CivPedDoNothing(PEDESTRIAN *pPed)
{
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupCivPedRouteData(struct VECTOR *pPos /*$s1*/)
 // line 3411, offset 0x0007313c
	/* begin block 1 */
		// Start line: 3412
		// Start offset: 0x0007313C
		// Variables:
	// 		struct VECTOR baseLoc; // stack offset -32
	/* end block 1 */
	// End offset: 0x000731F8
	// End Line: 3435

	/* begin block 2 */
		// Start line: 23047
	/* end block 2 */
	// End Line: 23048

void SetupCivPedRouteData(VECTOR *pPos)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	VECTOR local_20;

	local_20.vx = pPos->vx;
	local_20.vy = pPos->vy;
	local_20.vz = pPos->vz;
	iVar1 = GetSurfaceIndex(&local_20);
	pedestrian_roads.pos = (short)iVar1;
	local_20.vz = pPos->vz + -0x80;
	iVar1 = GetSurfaceIndex(&local_20);
	pedestrian_roads.north = (short)iVar1;
	local_20.vz = pPos->vz + 0x80;
	iVar1 = GetSurfaceIndex(&local_20);
	pedestrian_roads.south = (short)iVar1;
	local_20.vz = pPos->vz;
	local_20.vx = pPos->vx + -0x80;
	iVar1 = GetSurfaceIndex(&local_20);
	pedestrian_roads.east = (short)iVar1;
	local_20.vx = pPos->vx + 0x80;
	iVar1 = GetSurfaceIndex(&local_20);
	pedestrian_roads.west = (short)iVar1;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PingInPedestrians()
 // line 3447, offset 0x0007047c
	/* begin block 1 */
		// Start line: 3449
		// Start offset: 0x0007047C
		// Variables:
	// 		int bFound; // $s1
	// 		struct VECTOR randomLoc; // stack offset -88
	// 		struct VECTOR baseLoc; // stack offset -72
	// 		int i; // $s2
	// 		int pingInDist; // $a2
	// 		struct VECTOR position; // stack offset -56
	// 		struct VECTOR target; // stack offset -40
	// 		struct PEDESTRIAN *pedestrian; // $s1

		/* begin block 1.1 */
			// Start line: 3484
			// Start offset: 0x00070518

			/* begin block 1.1.1 */
				// Start line: 3502
				// Start offset: 0x000705F8
				// Variables:
			// 		struct PEDESTRIAN *pPed; // $a2

				/* begin block 1.1.1.1 */
					// Start line: 3520
					// Start offset: 0x00070628
					// Variables:
				// 		int x; // $v1
				// 		int z; // $v0
				// 		int radius; // $v1
				/* end block 1.1.1.1 */
				// End offset: 0x00070628
				// End Line: 3522
			/* end block 1.1.1 */
			// End offset: 0x00070674
			// End Line: 3524
		/* end block 1.1 */
		// End offset: 0x00070674
		// End Line: 3526

		/* begin block 1.2 */
			// Start line: 3534
			// Start offset: 0x000706AC

			/* begin block 1.2.1 */
				// Start line: 3583
				// Start offset: 0x000707F4
				// Variables:
			// 		int rval; // $v1
			/* end block 1.2.1 */
			// End offset: 0x00070858
			// End Line: 3622
		/* end block 1.2 */
		// End offset: 0x00070858
		// End Line: 3627
	/* end block 1 */
	// End offset: 0x00070858
	// End Line: 3632

	/* begin block 2 */
		// Start line: 7739
	/* end block 2 */
	// End Line: 7740

	/* begin block 3 */
		// Start line: 7740
	/* end block 3 */
	// End Line: 7741

	/* begin block 4 */
		// Start line: 7753
	/* end block 4 */
	// End Line: 7754

/* WARNING: Unknown calling convention yet parameter storage is locked */

void PingInPedestrians(void)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	undefined *puVar2;
	PED_ACTION_TYPE PVar3;
	SEATED_PEDESTRIANS *pSVar4;
	long lVar5;
	PEDESTRIAN *pPed;
	int iVar6;
	long lVar7;
	int iVar8;
	int step;
	VECTOR local_58;
	VECTOR local_48[3];

	bVar1 = false;
	if (((num_pedestrians < 0xf) && (pFreePeds != (PEDESTRIAN *)0x0)) &&
		(pFreePeds->pNext != (PEDESTRIAN *)0x0)) {
		local_48[0].vx = player.pos[0];
		local_48[0].vy = player.pos[1];
		local_48[0].vz = player.pos[2];
		if ((gWeather != 0) || (pSVar4 = FindSeated(), pSVar4 == (SEATED_PEDESTRIANS *)0x0)) {
			step = 0;
			do {
				lVar5 = Random2(0);
				lVar7 = lVar5;
				if (lVar5 < 0) {
					lVar7 = lVar5 + 0x7f;
				}
				pinginPedAngle = pinginPedAngle + 0x51;
				iVar8 = lVar5 + (lVar7 >> 7) * -0x80 + 0x600;
				local_58.vy = local_48[0].vy;
				local_58.vx = local_48[0].vx +
					iVar8 * ((int)rcossin_tbl[(pinginPedAngle & 0xfffU) * 2] * 8 + 0x800 >> 0xc);
				local_58.vz = local_48[0].vz +
					iVar8 * ((int)rcossin_tbl[(pinginPedAngle & 0xfffU) * 2 + 1] * 8 + 0x800 >>
						0xc);
				iVar8 = MapHeight(&local_58);
				local_58.vy = -iVar8;
				if (((local_48[0].vy + -0x200 <= iVar8) && (iVar8 <= local_48[0].vy + 0x200)) &&
					(iVar8 = IsPavement(local_58.vx, local_58.vy, local_58.vz, (PEDESTRIAN *)0x0), iVar8 != 0))
				{
					bVar1 = true;
					if (pUsedPeds == (PEDESTRIAN *)0x0) {
					LAB_0007068c:
						if (!bVar1) {
							return;
						}
						if (pFreePeds->pNext == (PEDESTRIAN *)0x0) {
							return;
						}
						pPed = CreatePedestrian();
						pPed->flags = 0;
						(pPed->position).vx = local_58.vx;
						(pPed->position).vy = local_58.vy;
						pPed->pedType = CIVILIAN;
						(pPed->dir).vz = 0;
						(pPed->dir).vx = 0;
						(pPed->dir).vy = 0;
						(pPed->position).vz = local_58.vz;
						local_48[0].vx = local_58.vx;
						local_48[0].vy = (pPed->position).vy;
						local_48[0].vz = (pPed->position).vz;
						local_48[0].vy = MapHeight(local_48);
						local_48[0].vy = -local_48[0].vy;
						SetupCivPedRouteData(local_48);
						PedestrianActionInit_WalkToTarget(pPed);
						step = -0x1c;
						PVar3 = PED_ACTION_CIVRUN;
						if ((((pedestrian_roads.north != -0x1c) &&
							(PVar3 = PED_ACTION_CIVRUN, pedestrian_roads.south != -0x1c)) &&
							(PVar3 = PED_ACTION_CIVRUN, pedestrian_roads.east != -0x1c)) &&
							(PVar3 = PED_ACTION_CIVWALK, pedestrian_roads.west == -0x1c)) {
							PVar3 = PED_ACTION_CIVRUN;
						}
						pPed->type = PVar3;
						lVar7 = Random2(-0x1c);
						lVar5 = Random2(step);
						pPed->pallet = (char)lVar7 + (char)(lVar7 / 5) * -5 +
							((char)lVar5 + (char)(lVar5 / 5) * -5) * '\x10';
						if (pPed->type == PED_ACTION_RUN) {
							pPed->speed = '\x1e';
						}
						SetupPedMotionData(pPed);
						puVar2 = PTR_CivPedWalk_000a168c;
						pPed->fpAgitatedState = (_func_2 *)0x0;
						(pPed->dir).vy = 0;
						pPed->fpRestState = puVar2;
						lVar7 = Random2(0);
						if ((lVar7 / 6) * 6 != lVar7 + -3) {
							return;
						}
						pPed->flags = pPed->flags | 0x4000;
						return;
					}
					iVar6 = (pUsedPeds->position).vx - local_58.vx;
					iVar8 = (pUsedPeds->position).vz;
					iVar6 = iVar6 * iVar6;
					pPed = pUsedPeds;
					while (bVar1 = true, 15999999 < iVar6 + (iVar8 - local_58.vz) * (iVar8 - local_58.vz)) {
						pPed = pPed->pNext;
						if (pPed == (PEDESTRIAN *)0x0) goto LAB_00070674;
						iVar6 = (pPed->position).vx - local_58.vx;
						iVar6 = iVar6 * iVar6;
						iVar8 = (pPed->position).vz;
					}
					bVar1 = false;
				}
			LAB_00070674:
				step = step + 1;
				if ((0x31 < step) || (bVar1)) goto LAB_0007068c;
			} while (true);
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ TannerCollision(struct PEDESTRIAN *pPed /*$s1*/)
 // line 3640, offset 0x00072ee4
	/* begin block 1 */
		// Start line: 3641
		// Start offset: 0x00072EE4
	/* end block 1 */
	// End offset: 0x00072FBC
	// End Line: 3675

	/* begin block 2 */
		// Start line: 20049
	/* end block 2 */
	// End Line: 20050

	/* begin block 3 */
		// Start line: 20050
	/* end block 3 */
	// End Line: 20051

	/* begin block 4 */
		// Start line: 21345
	/* end block 4 */
	// End Line: 21346

void TannerCollision(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	_CAR_DATA *p_Var2;
	long lVar3;

	if (pPed->type != PED_ACTION_SIT) {
		pcdTanner = car_data + 0x15;
		ClearMem((char *)(car_data + 0x15), 0x29c);
		pcdTanner->id = '\x15';
		pcdTanner->controlType = '\x06';
		p_Var2 = pcdTanner;
		(pcdTanner->hd).direction = (int)(pPed->dir).vy - 0x800U & 0xfff;
		lVar3 = (pPed->position).vx;
		(p_Var2->hd).oBox.location.vx = lVar3;
		(p_Var2->hd).where.t[0] = lVar3;
		iVar1 = -(pPed->position).vy;
		(p_Var2->hd).oBox.location.vy = iVar1;
		(p_Var2->hd).where.t[1] = iVar1;
		lVar3 = (pPed->position).vz;
		*(undefined4 *)(p_Var2->st + 0x1c) = 0;
		*(undefined4 *)(p_Var2->st + 0x20) = 0;
		*(undefined4 *)(p_Var2->st + 0x24) = 0;
		(p_Var2->hd).oBox.location.vz = lVar3;
		(p_Var2->hd).where.t[2] = lVar3;
		CheckScenaryCollisions(car_data + 0x15);
		TannerCarCollisionCheck((VECTOR *)&pPed->position, (int)(pPed->dir).vy, 0);
		p_Var2 = pcdTanner;
		(pPed->position).vx = (pcdTanner->hd).where.t[0];
		(pPed->position).vz = (p_Var2->hd).where.t[2];
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ FindPointOfCollision(struct _CAR_DATA *pCar /*$s3*/, struct VECTOR *pPos /*$a1*/)
 // line 3685, offset 0x00070878
	/* begin block 1 */
		// Start line: 3686
		// Start offset: 0x00070878
		// Variables:
	// 		int tb1; // $v1
	// 		int tb2; // $v0
	// 		int minX; // $a3
	// 		int maxX; // $t0
	// 		int minZ; // $v0
	// 		int maxZ; // $a0
	// 		int x; // $t1
	// 		int z; // $a1
	// 		int s1; // $a2
	// 		int s2; // $v1
	// 		int carLength[2]; // stack offset -40
	// 		static struct CRET2D collisionResult; // offset 0x0
	/* end block 1 */
	// End offset: 0x00070A9C
	// End Line: 3753

	/* begin block 2 */
		// Start line: 8376
	/* end block 2 */
	// End Line: 8377

	/* begin block 3 */
		// Start line: 8377
	/* end block 3 */
	// End Line: 8378

int FindPointOfCollision(_CAR_DATA *pCar, VECTOR *pPos)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	uint uVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	cd.length[0] = 0x78;
	cd.length[1] = 0xc;
	cd.x.vx = pPos->vx;
	cd.x.vz = pPos->vz;
	cd.theta = (int)((player.pPed)->dir).vy - 0x800U & 0xfff;
	CDATA2D_000d9554.length[0] = (int)car_cosmetics[(byte)(pCar->ap).model].colBox.vz;
	CDATA2D_000d9554.length[1] = (int)car_cosmetics[(byte)(pCar->ap).model].colBox.vx;
	CDATA2D_000d9554.x.vx = (pCar->hd).where.t[0];
	CDATA2D_000d9554.x.vz = (pCar->hd).where.t[2];
	CDATA2D_000d9554.theta = (pCar->hd).direction;
	iVar1 = bcollided2d(&cd, 1);
	if (iVar1 != 0) {
		bFindCollisionPoint(&cd, (CRET2D *)&collisionResult_124);
		uVar2 = (uint)(byte)(pCar->ap).model;
		iVar6 = (int)car_cosmetics[uVar2].colBox.vx;
		iVar4 = ((collisionResult_124 - CDATA2D_000d9554.x.vx) *
			(int)rcossin_tbl[(CDATA2D_000d9554.theta & 0xfffU) * 2 + 1] >> 0xc) -
			((DAT_000d9498 - CDATA2D_000d9554.x.vz) *
			(int)rcossin_tbl[(CDATA2D_000d9554.theta & 0xfffU) * 2] >> 0xc);
		iVar5 = iVar6 + 0x60;
		iVar3 = (int)car_cosmetics[uVar2].colBox.vz;
		iVar1 = ((collisionResult_124 - CDATA2D_000d9554.x.vx) *
			(int)rcossin_tbl[(CDATA2D_000d9554.theta & 0xfffU) * 2] >> 0xc) +
			((DAT_000d9498 - CDATA2D_000d9554.x.vz) *
			(int)rcossin_tbl[(CDATA2D_000d9554.theta & 0xfffU) * 2 + 1] >> 0xc);
		iVar6 = iVar6 + -0x60;
		if ((iVar3 + -0x1e0 < iVar1) && (iVar1 < iVar3 + -200)) {
			if ((iVar6 < iVar4) && (iVar4 < iVar5)) {
				return 1;
			}
			if ((iVar4 < -iVar6) && (-iVar5 < iVar4)) {
				return 1;
			}
		}
	}
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ TannerCarCollisionCheck(struct VECTOR *pPos /*$s5*/, int dir /*$a1*/, int bQuick /*stack 8*/)
 // line 3762, offset 0x00070a9c
	/* begin block 1 */
		// Start line: 3763
		// Start offset: 0x00070A9C
		// Variables:
	// 		int carLength[2]; // stack offset -120
	// 		struct _CAR_DATA *cp0; // $s0
	// 		struct _CAR_DATA *cp1; // $s1
	// 		static struct CRET2D collisionResult; // offset 0x30
	// 		unsigned int dNewLBODY[2]; // stack offset -112
	// 		int speed; // $v0

		/* begin block 1.1 */
			// Start line: 3798
			// Start offset: 0x00070B2C

			/* begin block 1.1.1 */
				// Start line: 3798
				// Start offset: 0x00070B2C
			/* end block 1.1.1 */
			// End offset: 0x00070B2C
			// End Line: 3798

			/* begin block 1.1.2 */
				// Start line: 3815
				// Start offset: 0x00070C04
				// Variables:
			// 		struct VECTOR velocity; // stack offset -104
			// 		long pointVel[4]; // stack offset -88
			// 		long reaction[4]; // stack offset -72
			// 		long lever[4]; // stack offset -56
			// 		int strikeVel; // $t1

				/* begin block 1.1.2.1 */
					// Start line: 3846
					// Start offset: 0x00070D84
				/* end block 1.1.2.1 */
				// End offset: 0x00070D84
				// End Line: 3857

				/* begin block 1.1.2.2 */
					// Start line: 3861
					// Start offset: 0x00070DB0
					// Variables:
				// 		int twistY; // $a2
				// 		int lever_dot_n; // $a0
				// 		int displacementsquared; // $a1
				// 		int denom; // $a0
				/* end block 1.1.2.2 */
				// End offset: 0x00070E8C
				// End Line: 3874
			/* end block 1.1.2 */
			// End offset: 0x00070FD8
			// End Line: 3895
		/* end block 1.1 */
		// End offset: 0x00071008
		// End Line: 3904
	/* end block 1 */
	// End offset: 0x00071054
	// End Line: 3907

	/* begin block 2 */
		// Start line: 8611
	/* end block 2 */
	// End Line: 8612

	/* begin block 3 */
		// Start line: 8621
	/* end block 3 */
	// End Line: 8622

	/* begin block 4 */
		// Start line: 8646
	/* end block 4 */
	// End Line: 8647

/* WARNING: Removing unreachable block (ram,0x00070ec8) */
/* WARNING: Type propagation algorithm not settling */

int TannerCarCollisionCheck(VECTOR *pPos, int dir, int bQuick)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	uint uVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	_CAR_DATA *p_Var13;

	cd.length[0] = 0x3c;
	cd.length[1] = 0x3c;
	cd.x.vx = pPos->vx;
	cd.x.vz = pPos->vz;
	p_Var13 = (_CAR_DATA *)0xd43fc;
	cd.theta = dir;
	do {
		uVar2 = (uint)(byte)(p_Var13->ap).model;
		CDATA2D_000d9554.x.vx = (p_Var13->hd).where.t[0];
		CDATA2D_000d9554.length[0] = (int)car_cosmetics[uVar2].colBox.vz;
		CDATA2D_000d9554.length[1] = (int)car_cosmetics[uVar2].colBox.vx;
		CDATA2D_000d9554.theta = (p_Var13->hd).direction;
		CDATA2D_000d9554.x.vz = (p_Var13->hd).where.t[2];
		if (p_Var13->controlType != '\0') {
			iVar3 = (p_Var13->hd).where.t[1] + pPos->vy;
			if (iVar3 < 0) {
				iVar3 = -iVar3;
			}
			if ((iVar3 < 500) && (iVar3 = bcollided2d(&cd, 1), iVar3 != 0)) {
				if (bQuick != 0) {
					return 1;
				}
				if (0x32 < (p_Var13->hd).wheel_speed + 0x800 >> 0xc) {
					return 1;
				}
				bFindCollisionPoint(&cd, (CRET2D *)&collisionResult_128);
				iVar3 = -DAT_000d94d8;
				iVar1 = -DAT_000d94d0;
				iVar10 = car_data[21].hd.where.t[2] + (DAT_000d94e0 * iVar3 + 0x800 >> 0xc);
				iVar12 = DAT_000d94c8 - iVar10;
				DAT_000d94c4 = car_data[21].hd.where.t[1] + 0x3c;
				iVar9 = DAT_000d94c4 - car_data[21].hd.where.t[1];
				iVar8 = car_data[21].hd.where.t[0] + (DAT_000d94e0 * iVar1 + 0x800 >> 0xc);
				iVar11 = collisionResult_128 - iVar8;
				DAT_000d94d4 = 0;
				iVar7 = ((car_data[21].st._44_4_ * iVar12 - car_data[21].st._48_4_ * iVar9) + 0x800 >> 0xc)
					+ car_data[21].st._28_4_;
				iVar5 = ((car_data[21].st._40_4_ * iVar9 - car_data[21].st._44_4_ * iVar11) + 0x800 >> 0xc)
					+ car_data[21].st._36_4_;
				if (iVar7 < 0) {
					iVar7 = iVar7 + 0xff;
				}
				iVar4 = iVar1;
				if (0 < DAT_000d94d0) {
					iVar4 = iVar1 + 0xf;
				}
				if (iVar5 < 0) {
					iVar5 = iVar5 + 0xff;
				}
				iVar6 = iVar3;
				if (0 < DAT_000d94d8) {
					iVar6 = iVar3 + 0xf;
				}
				iVar5 = (iVar7 >> 8) * (iVar4 >> 4) + (iVar5 >> 8) * (iVar6 >> 4);
				if (iVar5 < 0) {
					iVar7 = iVar11 * iVar1 + iVar12 * iVar3 + 0x800 >> 0xc;
					iVar7 = (((iVar11 * iVar11 + iVar12 * iVar12) - iVar7 * iVar7) *
						(int)car_cosmetics[(byte)car_data[21].ap.model].twistRateY + 0x800 >> 0xc) +
						0x1000;
					if (-iVar5 < 0x7f001) {
						iVar5 = (iVar5 * -0x1000) / iVar7;
						if (iVar7 == 0) {
							trap(7);
						}
					}
					else {
						if (iVar7 == 0) {
							trap(7);
						}
						iVar5 = -iVar5 / iVar7 << 0xc;
					}
					if (iVar5 < 0) {
						iVar5 = iVar5 + 0x3f;
					}
					iVar7 = iVar1;
					if (0 < DAT_000d94d0) {
						iVar7 = iVar1 + 0x3f;
					}
					iVar4 = (iVar5 >> 6) * (iVar7 >> 6);
					iVar7 = iVar3;
					if (0 < DAT_000d94d8) {
						iVar7 = iVar3 + 0x3f;
					}
					iVar5 = (iVar5 >> 6) * (iVar7 >> 6);
					car_data[21].st._28_4_ = car_data[21].st._28_4_ + iVar4;
					car_data[21].st._36_4_ = car_data[21].st._36_4_ + iVar5;
					car_data[21].hd.aacc[2] = car_data[21].hd.aacc[2] - (iVar9 * iVar4 + 0x800 >> 0xc);
					car_data[21].hd.aacc[0] = car_data[21].hd.aacc[0] + (iVar9 * iVar5 + 0x800 >> 0xc);
					car_data[21].hd.aacc[1] =
						(car_data[21].hd.aacc[1] + (iVar12 * iVar4 + 0x800 >> 0xc)) -
						(iVar11 * iVar5 + 0x800 >> 0xc);
					DAT_000d94c4 = -DAT_000d94c4;
				}
				car_data[21].hd.where.t[0] = iVar8 - (car_data[21].st._28_4_ + 0x800 >> 0xc);
				car_data[21].hd.where.t[2] = iVar10 - (car_data[21].st._36_4_ + 0x800 >> 0xc);
				DAT_000d94d0 = iVar1;
				DAT_000d94d8 = iVar3;
			}
		}
		p_Var13 = p_Var13 + -1;
		if (p_Var13 < car_data) {
			return 0;
		}
	} while (true);
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ PingOutPed(struct PEDESTRIAN *pPed /*$a2*/)
 // line 3915, offset 0x000731f8
	/* begin block 1 */
		// Start line: 3916
		// Start offset: 0x000731F8
		// Variables:
	// 		int px; // $a0
	// 		int pz; // $v1
	// 		int ps; // $a0
	/* end block 1 */
	// End offset: 0x00073270
	// End Line: 3938

	/* begin block 2 */
		// Start line: 23590
	/* end block 2 */
	// End Line: 23591

	/* begin block 3 */
		// Start line: 24071
	/* end block 3 */
	// End Line: 24072

int PingOutPed(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	return;
	/*
	int iVar1;
	int iVar2;

	iVar2 = (pPed->position).vx - player.pos[0];
	iVar1 = (pPed->position).vz - player.pos[2];
	if (iVar2 * iVar2 + iVar1 * iVar1 < 0x190a0101) {
		return (uint)(-player.pos[1] - (pPed->position).vy < 0x201) ^ 1;
	}
	return 1;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupCivJump(struct PEDESTRIAN *pPed /*$s1*/, struct _CAR_DATA *cp /*$s0*/)
 // line 3946, offset 0x00071054
	/* begin block 1 */
		// Start line: 3947
		// Start offset: 0x00071054
		// Variables:
	// 		long disp[4]; // stack offset -48
	// 		long dir[4]; // stack offset -32
	// 		int angle; // $s0

		/* begin block 1.1 */
			// Start line: 3960
			// Start offset: 0x000710C0
			// Variables:
		// 		short scale; // $a2
		/* end block 1.1 */
		// End offset: 0x000710E4
		// End Line: 3967

		/* begin block 1.2 */
			// Start line: 4008
			// Start offset: 0x000711E8
		/* end block 1.2 */
		// End offset: 0x000712AC
		// End Line: 4027
	/* end block 1 */
	// End offset: 0x00071324
	// End Line: 4040

	/* begin block 2 */
		// Start line: 9290
	/* end block 2 */
	// End Line: 9291

	/* begin block 3 */
		// Start line: 9330
	/* end block 3 */
	// End Line: 9331

void SetupCivJump(PEDESTRIAN *pPed, _CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	short scale;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;

	if (pPed->type != PED_ACTION_JUMP) {
		pPed->frame1 = '\0';
		pPed->speed = '\x1e';
		if (cp == car_data + player.playerCarId) {
			scale = 0x1000;
			if (player.horn.on != '\0') {
				scale = 0x800;
			}
			NoteFelony(&felonyData, '\x01', scale);
		}
	}
	pPed->type = PED_ACTION_JUMP;
	pPed->flags = pPed->flags | 0x10;
	pPed->fpAgitatedState = PTR_CivPedJump_000a1694;
	SetupPedMotionData(pPed);
	if (cp == (_CAR_DATA *)0x0) {
		if (bAvoidTanner == 0) {
			scale = ratan2((pPed->position).vx - explosion[bAvoidBomb].pos.vx,
				(pPed->position).vz - explosion[bAvoidBomb].pos.vz);
			uVar1 = scale - 0x800;
		}
		else {
			scale = 0x400;
			if ((-((int)(player.pPed)->speed *
				(int)rcossin_tbl[((int)((player.pPed)->dir).vy - 0x800U & 0xfff) * 2 + 1]) >> 0xc) *
				(((player.pPed)->position).vx - (pPed->position).vx) +
				((int)(player.pPed)->speed *
				(int)rcossin_tbl[((int)((player.pPed)->dir).vy - 0x800U & 0xfff) * 2] >> 0xc) *
					(((player.pPed)->position).vz - (pPed->position).vz) + 0x800 < 0) {
				scale = -0x400;
			}
			uVar1 = scale + ((player.pPed)->dir).vy;
		}
	}
	else {
		iVar5 = (cp->hd).where.t[0] - (pPed->position).vx;
		iVar4 = *(int *)(cp->st + 0x24);
		iVar3 = *(int *)(cp->st + 0x1c);
		iVar2 = (cp->hd).where.t[2] - (pPed->position).vz;
		if ((iVar4 == 0) && (-iVar3 == 0)) {
			uVar1 = ratan2(iVar2, iVar5);
		}
		else {
			scale = ratan2(*(undefined4 *)(cp->st + 0x24), *(undefined4 *)(cp->st + 0x1c));
			uVar1 = ((short)~(ushort)(iVar4 * iVar5 + -iVar3 * iVar2 + 0x800 >> 0x1c) >> 0xf & 0x800U) -
				scale;
		}
	}
	(pPed->dir).vy = uVar1 & 0xfff;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivPedJump(struct PEDESTRIAN *pPed /*$s0*/)
 // line 4047, offset 0x00072cf0
	/* begin block 1 */
		// Start line: 4048
		// Start offset: 0x00072CF0
	/* end block 1 */
	// End offset: 0x00072DA0
	// End Line: 4073

	/* begin block 2 */
		// Start line: 20349
	/* end block 2 */
	// End Line: 20350

	/* begin block 3 */
		// Start line: 8094
	/* end block 3 */
	// End Line: 8095

void CivPedJump(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	undefined *puVar2;

	cVar1 = pPed->frame1;
	if (cVar1 == '\x02') {
		pPed->speed = pPed->speed << 1;
		cVar1 = pPed->frame1;
	}
	if (cVar1 == '\x0e') {
		pPed->speed = pPed->speed >> 1;
	}
	AnimatePed(pPed);
	if (0x1d < (byte)pPed->frame1) {
		pPed->frame1 = '\0';
		puVar2 = PTR_CivPedWalk_000a168c;
		pPed->type = PED_ACTION_CIVWALK;
		pPed->fpRestState = puVar2;
		SetupPedMotionData(pPed);
		pPed->fpAgitatedState = (_func_2 *)0x0;
		pPed->flags = pPed->flags & 0xffffffef;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupCivPedWalk(struct PEDESTRIAN *pPed /*$s0*/)
 // line 4080, offset 0x00073270
	/* begin block 1 */
		// Start line: 24276
	/* end block 1 */
	// End Line: 24277

	/* begin block 2 */
		// Start line: 24419
	/* end block 2 */
	// End Line: 24420

void SetupCivPedWalk(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	char cVar1;

	pPed->flags = pPed->flags | 0x10;
	cVar1 = '\n';
	if (pPed->type == PED_ACTION_RUN) {
		cVar1 = '\x1e';
	}
	pPed->speed = cVar1;
	SetupPedMotionData(pPed);
	pPed->frame1 = '\0';
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivPedWalk(struct PEDESTRIAN *pPed /*$s0*/)
 // line 4101, offset 0x00071324
	/* begin block 1 */
		// Start line: 4102
		// Start offset: 0x00071324
		// Variables:
	// 		int turn; // $a1
	// 		int offset1; // $t0
	// 		int offset2; // $v1
	// 		int lookahead; // $s3
	// 		int speed; // $s1
	/* end block 1 */
	// End offset: 0x000715FC
	// End Line: 4182

	/* begin block 2 */
		// Start line: 9615
	/* end block 2 */
	// End Line: 9616

	/* begin block 3 */
		// Start line: 9677
	/* end block 3 */
	// End Line: 9678

void CivPedWalk(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	short sVar2;
	ushort uVar3;
	uint uVar4;
	int turn;
	int iVar5;

	if ((pPed->flags & 0x10U) == 0) {
		SetupCivPedWalk(pPed);
	}
	iVar5 = (int)pPed->speed;
	if ((*(uint *)&pPed->speed & 0xffff00) == 0x90000) {
		sVar2 = (pPed->dir).vy;
		uVar4 = (int)(pPed->dir).vy + 0x800;
	}
	else {
		sVar2 = (pPed->dir).vy;
		uVar4 = (int)(pPed->dir).vy + 0x73a;
	}
	if ((pPed->flags & 2U) == 0) {
		turn = IsPavement((pPed->position).vx + ((int)rcossin_tbl[(uVar4 & 0xfff) * 2] >> 5),
			(pPed->position).vy,
			(pPed->position).vz + ((int)rcossin_tbl[(uVar4 & 0xfff) * 2 + 1] >> 5), pPed);
		if (turn == 0) {
			if ((*(uint *)&pPed->speed & 0xffff00) == 0x90000) {
				uVar4 = (int)(pPed->dir).vy + 0xa00U & 0xfff;
				turn = IsPavement((pPed->position).vx + ((int)rcossin_tbl[uVar4 * 2] * 0x80 >> 0xc),
					(pPed->position).vy,
					(pPed->position).vz + ((int)rcossin_tbl[uVar4 * 2 + 1] * 0x80 >> 0xc),
					(PEDESTRIAN *)0x0);
				if (turn == 0) {
					uVar4 = pPed->flags & 0xffffdfff;
				}
				else {
					uVar4 = pPed->flags | 0x2000;
				}
				pPed->flags = uVar4;
			}
			turn = -0x80;
			if ((pPed->flags & 0x2000U) != 0) {
				turn = 0x80;
			}
			if (pPed->doing_turn < ' ') {
				SetPedestrianTurn(pPed, turn);
				pPed->doing_turn = pPed->doing_turn + '\x01';
			}
			else {
				uVar4 = (int)(pPed->dir).vy + 0x800U & 0xfff;
				(pPed->velocity).vx = (short)(iVar5 * rcossin_tbl[uVar4 * 2] >> 0xc);
				(pPed->velocity).vz = (short)(iVar5 * rcossin_tbl[uVar4 * 2 + 1] >> 0xc);
			}
			pPed->finished_turn = '\0';
		}
		else {
			cVar1 = pPed->finished_turn;
			pPed->doing_turn = '\0';
			pPed->finished_turn = cVar1 + '\x01';
			if ('\b' < cVar1) {
				uVar3 = (pPed->dir).vy + 0x200U & 0xfc00;
				(pPed->dir).vy = uVar3;
				uVar4 = (int)(short)uVar3 + 0x800U & 0xfff;
				(pPed->velocity).vx = (short)(iVar5 * rcossin_tbl[uVar4 * 2] >> 0xc);
				sVar2 = rcossin_tbl[uVar4 * 2 + 1];
				pPed->finished_turn = '\t';
				(pPed->velocity).vz = (short)(iVar5 * sVar2 >> 0xc);
			}
		}
	}
	else {
		pPed->speed = '\0';
		(pPed->dir).vy = sVar2 + pPed->head_rot;
	}
	AnimatePed(pPed);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivPedSit(struct PEDESTRIAN *pPed /*$a0*/)
 // line 4190, offset 0x00072ce8
	/* begin block 1 */
		// Start line: 4192
		// Start offset: 0x00072CE8
	/* end block 1 */
	// End offset: 0x00072CF0
	// End Line: 4208

	/* begin block 2 */
		// Start line: 20475
	/* end block 2 */
	// End Line: 20476

	/* begin block 3 */
		// Start line: 20476
	/* end block 3 */
	// End Line: 20477

	/* begin block 4 */
		// Start line: 20480
	/* end block 4 */
	// End Line: 20481

// [D]
void CivPedSit(PEDESTRIAN *pPed)
{
	pPed->frame1 = '\0';
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandlePedestrians()
 // line 4221, offset 0x0007211c
	/* begin block 1 */
		// Start line: 4223
		// Start offset: 0x0007211C
	/* end block 1 */
	// End offset: 0x0007215C
	// End Line: 4457

	/* begin block 2 */
		// Start line: 13906
	/* end block 2 */
	// End Line: 13907

	/* begin block 3 */
		// Start line: 13907
	/* end block 3 */
	// End Line: 13908

	/* begin block 4 */
		// Start line: 13925
	/* end block 4 */
	// End Line: 13926

/* WARNING: Unknown calling convention yet parameter storage is locked */

void HandlePedestrians(void)
{
	UNIMPLEMENTED();
	/*
	if ((gInGameCutsceneActive == 0) && (NumPlayers == 1)) {
		BuildCarCollisionBox();
		ControlPedestrians();
		PingInPedestrians();
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedestrianActionInit_WalkToTarget(struct PEDESTRIAN *pPed /*$s0*/)
 // line 4465, offset 0x0007283c
	/* begin block 1 */
		// Start line: 4466
		// Start offset: 0x0007283C
		// Variables:
	// 		int dir; // $v1
	/* end block 1 */
	// End offset: 0x000728B8
	// End Line: 4496

	/* begin block 2 */
		// Start line: 18892
	/* end block 2 */
	// End Line: 18893

	/* begin block 3 */
		// Start line: 8930
	/* end block 3 */
	// End Line: 8931

void PedestrianActionInit_WalkToTarget(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	iVar1 = CalcPedestrianDirection(0, (pPed->position).vx, (pPed->position).vz, &pPed->target);
	if (iVar1 != 0) {
		pPed->last_dir = (short)iVar1;
		if (iVar1 == 1) {
			(pPed->dir).vy = 0x400;
		}
		if (iVar1 == 2) {
			(pPed->dir).vy = 0xc00;
		}
		if (iVar1 == 4) {
			(pPed->dir).vy = 0;
		}
		if (iVar1 == 8) {
			(pPed->dir).vy = 0x800;
		}
		CorrectPathPosition(pPed, (VECTOR *)&pPed->position);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CorrectPathPosition(struct PEDESTRIAN *pedestrian /*$a0*/, struct VECTOR *position /*$a1*/)
 // line 4508, offset 0x000715fc
	/* begin block 1 */
		// Start line: 4510
		// Start offset: 0x000715FC
		// Variables:
	// 		struct VECTOR vec; // stack offset -16
	/* end block 1 */
	// End offset: 0x000715FC
	// End Line: 4610

	/* begin block 2 */
		// Start line: 10180
	/* end block 2 */
	// End Line: 10181

	/* begin block 3 */
		// Start line: 10507
	/* end block 3 */
	// End Line: 10508

	/* begin block 4 */
		// Start line: 10508
	/* end block 4 */
	// End Line: 10509

	/* begin block 5 */
		// Start line: 10608
	/* end block 5 */
	// End Line: 10609

// [D]
void CorrectPathPosition(PEDESTRIAN *pedestrian, VECTOR *position)
{
	return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CalcPedestrianDirection(int last_dir /*$a0*/, int wx /*$s5*/, int wz /*$s6*/, struct VECTOR *target /*$s3*/)
 // line 4619, offset 0x00071608
	/* begin block 1 */
		// Start line: 4620
		// Start offset: 0x00071608
		// Variables:
	// 		int dir; // $s2
	// 		int num; // $s1
	// 		int rx; // $v1
	// 		int rz; // $a0
	// 		int mask; // $s0

		/* begin block 1.1 */
			// Start line: 4669
			// Start offset: 0x000716C0
		/* end block 1.1 */
		// End offset: 0x0007170C
		// End Line: 4681
	/* end block 1 */
	// End offset: 0x000717AC
	// End Line: 4734

	/* begin block 2 */
		// Start line: 10729
	/* end block 2 */
	// End Line: 10730

	/* begin block 3 */
		// Start line: 10737
	/* end block 3 */
	// End Line: 10738

int CalcPedestrianDirection(int last_dir, int wx, int wz, VECTOR *target)
{
	UNIMPLEMENTED();
	return 0;
	/*
	long lVar1;
	int iVar2;
	uint uVar3;
	uint uVar4;
	uint uVar5;

	uVar5 = (uint)(pedestrian_roads.west == -0x14);
	uVar4 = (uint)(pedestrian_roads.west == -0x14);
	if (pedestrian_roads.east == -0x14) {
		uVar5 = uVar5 | 2;
		uVar4 = uVar4 + 1;
	}
	if (pedestrian_roads.north == -0x14) {
		uVar5 = uVar5 | 4;
		uVar4 = uVar4 + 1;
	}
	if (pedestrian_roads.south == -0x14) {
		uVar5 = uVar5 | 8;
		uVar4 = uVar4 + 1;
	}
	uVar3 = uVar5 & last_dir;
	if ((uVar3 == 0) && (uVar3 = uVar5, 1 < uVar4)) {
		lVar1 = Random2(0);
		uVar3 = 0x10;
		if (uVar4 == 0) {
			trap(7);
		}
		iVar2 = lVar1 % uVar4 + 1;
		while (iVar2 != 0) {
			uVar3 = (int)uVar3 >> 1;
			if ((uVar5 & uVar3) != 0) {
				iVar2 = iVar2 + -1;
			}
		}
		uVar3 = uVar5 & uVar3;
	}
	uVar4 = wx & 0xfffffc00;
	uVar5 = wz & 0xfffffc00;
	if (uVar3 == 2) {
		iVar2 = uVar4 + 0x600;
	}
	else {
		if (2 < uVar3) {
			if (uVar3 == 4) {
				iVar2 = uVar5 + 0x600;
			}
			else {
				iVar2 = uVar5 - 0x200;
				if (uVar3 != 8) goto LAB_0007177c;
			}
			target->vx = uVar4 + 0x200;
			target->vz = iVar2;
			goto LAB_0007177c;
		}
		iVar2 = uVar4 - 0x200;
		if (uVar3 != 1) goto LAB_0007177c;
	}
	target->vx = iVar2;
	target->vz = uVar5 + 0x200;
LAB_0007177c:
	target->vy = 0;
	return uVar3;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ IsPavement(int x /*$a0*/, int y /*$a1*/, int z /*$a2*/, struct PEDESTRIAN *pPed /*$s0*/)
 // line 4845, offset 0x000725b8
	/* begin block 1 */
		// Start line: 4846
		// Start offset: 0x000725B8
		// Variables:
	// 		struct VECTOR vec; // stack offset -24
	// 		int r; // $v1
	/* end block 1 */
	// End offset: 0x00072644
	// End Line: 4917

	/* begin block 2 */
		// Start line: 18844
	/* end block 2 */
	// End Line: 18845

	/* begin block 3 */
		// Start line: 9690
	/* end block 3 */
	// End Line: 9691

	/* begin block 4 */
		// Start line: 18854
	/* end block 4 */
	// End Line: 18855

int IsPavement(int x, int y, int z, PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	uint uVar2;
	VECTOR local_18;

	local_18.vy = -y;
	local_18.vx = x;
	local_18.vz = z;
	iVar1 = GetSurfaceIndex(&local_18);
	if (iVar1 == -0x14) {
		iVar1 = RoadInCell(&local_18);
		uVar2 = (uint)(iVar1 != 0);
	}
	else {
		if (pPed != (PEDESTRIAN *)0x0) {
			if (((iVar1 != -0x1a) && (iVar1 != -0x17)) && (iVar1 != -0x20)) {
				return 0;
			}
			pPed->flags = pPed->flags | 1;
		}
		uVar2 = 0;
	}
	return uVar2;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetPedestrianTurn(struct PEDESTRIAN *pedestrian /*$a0*/, int turn /*$a1*/)
 // line 4924, offset 0x00072500
	/* begin block 1 */
		// Start line: 4925
		// Start offset: 0x00072500
		// Variables:
	// 		int dir; // $a2
	// 		int speed; // $v1
	/* end block 1 */
	// End offset: 0x00072584
	// End Line: 4935

	/* begin block 2 */
		// Start line: 15021
	/* end block 2 */
	// End Line: 15022

	/* begin block 3 */
		// Start line: 18487
	/* end block 3 */
	// End Line: 18488

	/* begin block 4 */
		// Start line: 18488
	/* end block 4 */
	// End Line: 18489

void SetPedestrianTurn(PEDESTRIAN *pedestrian, int turn)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	short sVar2;
	short sVar3;
	int iVar4;
	int iVar5;
	uint uVar6;

	iVar4 = (pedestrian->position).vx;
	sVar2 = (pedestrian->velocity).vz;
	iVar5 = (pedestrian->position).vz;
	uVar6 = (pedestrian->dir).vy + turn & 0xfff;
	(pedestrian->dir).vy = (short)uVar6;
	uVar6 = uVar6 + 0x800 & 0xfff;
	sVar3 = (pedestrian->velocity).vx;
	(pedestrian->position).vz = iVar5 - sVar2;
	cVar1 = pedestrian->speed;
	(pedestrian->position).vx = iVar4 - sVar3;
	(pedestrian->velocity).vx = (short)((int)cVar1 * (int)rcossin_tbl[uVar6 * 2] >> 0xc);
	(pedestrian->velocity).vz = (short)((int)cVar1 * (int)rcossin_tbl[uVar6 * 2 + 1] >> 0xc);
	return;*/
}



// decompiled code
// original method signature: 
// struct SEATED_PEDESTRIANS * /*$ra*/ FindSeated()
 // line 4943, offset 0x00072644
	/* begin block 1 */
		// Start line: 4945
		// Start offset: 0x00072644
		// Variables:
	// 		struct SEATED_PEDESTRIANS *seatedptr; // $s0

		/* begin block 1.1 */
			// Start line: 4950
			// Start offset: 0x0007266C
			// Variables:
		// 		int dx; // $v1
		// 		int dz; // $v0
		// 		int distsqr; // $v1
		// 		int count1; // $a2
		/* end block 1.1 */
		// End offset: 0x00072724
		// End Line: 4975
	/* end block 1 */
	// End offset: 0x00072738
	// End Line: 4977

	/* begin block 2 */
		// Start line: 19027
	/* end block 2 */
	// End Line: 19028

	/* begin block 3 */
		// Start line: 19054
	/* end block 3 */
	// End Line: 19055

	/* begin block 4 */
		// Start line: 19055
	/* end block 4 */
	// End Line: 19056

/* WARNING: Unknown calling convention yet parameter storage is locked */

SEATED_PEDESTRIANS * FindSeated(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	int iVar3;
	SEATED_PEDESTRIANS *seatedptr;

	if (seated_pedestrian != (SEATED_PEDESTRIANS *)0x0) {
		if (seated_pedestrian->rotation == 9999) {
			return (SEATED_PEDESTRIANS *)0x0;
		}
		iVar3 = 3;
		do {
			seated_count = seated_count + 1;
			seatedptr = seated_pedestrian + seated_count;
			if (seated_pedestrian[seated_count].rotation == 9999) {
				seated_count = 0;
				seatedptr = seated_pedestrian;
			}
			if ((seatedptr->index == '\0') &&
				(iVar2 = seatedptr->x - player.pos[0] >> 0xc, iVar1 = seatedptr->z - player.pos[2] >> 0xc,
					iVar3 = iVar3 + -1, (iVar2 * iVar2 + iVar1 * iVar1) - 0xbU < 0x1d)) {
				add_seated(seatedptr, seated_count);
				return seatedptr;
			}
		} while (iVar3 != 0);
	}
	return (SEATED_PEDESTRIANS *)0x0;*/
}



// decompiled code
// original method signature: 
// struct SEATED_PEDESTRIANS * /*$ra*/ FindTannerASeat(struct PEDESTRIAN *pPed /*$t4*/)
 // line 4984, offset 0x000717ac
	/* begin block 1 */
		// Start line: 4985
		// Start offset: 0x000717AC
		// Variables:
	// 		struct SEATED_PEDESTRIANS *seatedptr; // $a2
	// 		struct SEATED_PEDESTRIANS *theOne; // $t1
	// 		int dx; // $a0
	// 		int dz; // $v1
	// 		int distsqr; // $v0
	// 		int bestSqr; // $t2
	/* end block 1 */
	// End offset: 0x000718C8
	// End Line: 5023

	/* begin block 2 */
		// Start line: 11491
	/* end block 2 */
	// End Line: 11492

	/* begin block 3 */
		// Start line: 11493
	/* end block 3 */
	// End Line: 11494

SEATED_PEDESTRIANS * FindTannerASeat(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	SEATED_PEDESTRIANS *pSVar3;
	SEATED_PEDESTRIANS *pSVar4;
	int iVar5;

	pSVar4 = (SEATED_PEDESTRIANS *)0x0;
	iVar5 = 0x1000;
	seated_count = 0;
	if (seated_pedestrian->rotation != 9999) {
		seated_count = 0;
		iVar1 = 0;
		do {
			pSVar3 = (SEATED_PEDESTRIANS *)(&seated_pedestrian->x + iVar1 + seated_count);
			iVar1 = pSVar3->x - player.pos[0];
			seated_count = seated_count + 1;
			if (iVar1 < 0) {
				iVar1 = player.pos[0] - pSVar3->x;
			}
			iVar2 = pSVar3->z - player.pos[2];
			if (iVar2 < 0) {
				iVar2 = player.pos[2] - pSVar3->z;
			}
			if (((iVar1 < 200) && (iVar2 < 200)) &&
				(iVar1 = iVar1 * iVar1 + iVar2 * iVar2 >> 0xc, iVar1 < iVar5)) {
				pSVar4 = pSVar3;
				iVar5 = iVar1;
			}
			iVar1 = seated_count * 2;
		} while (pSVar3->rotation != 9999);
	}
	if ((iVar5 < 6) && (pSVar4 != (SEATED_PEDESTRIANS *)0x0)) {
		(pPed->dir).vy = pSVar4->rotation;
		(pPed->position).vx = pSVar4->x;
		(pPed->position).vz = pSVar4->z;
		return pSVar4;
	}
	return (SEATED_PEDESTRIANS *)0x0;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ add_seated(struct SEATED_PEDESTRIANS *seatedptr /*$s0*/, int seat_index /*$s2*/)
 // line 5031, offset 0x000718c8
	/* begin block 1 */
		// Start line: 5032
		// Start offset: 0x000718C8
		// Variables:
	// 		struct PEDESTRIAN *pedestrian; // $s1
	// 		int index; // $v0
	/* end block 1 */
	// End offset: 0x00071A44
	// End Line: 5076

	/* begin block 2 */
		// Start line: 11581
	/* end block 2 */
	// End Line: 11582

	/* begin block 3 */
		// Start line: 11590
	/* end block 3 */
	// End Line: 11591

	/* begin block 4 */
		// Start line: 11596
	/* end block 4 */
	// End Line: 11597

void add_seated(SEATED_PEDESTRIANS *seatedptr, int seat_index)
{
	UNIMPLEMENTED();
	/*
	undefined *puVar1;
	PEDESTRIAN *pedptr;
	int iVar2;
	long lVar3;
	long lVar4;

	if ((num_pedestrians < 0x14) && (pedptr = CreatePedestrian(), pedptr != (PEDESTRIAN *)0x0)) {
		seatedptr->index = '\x02';
		pedptr->type = PED_ACTION_CIVSIT;
		pedptr->speed = '\0';
		(pedptr->velocity).vx = 0;
		(pedptr->velocity).vy = 0;
		(pedptr->velocity).vz = 0;
		(pedptr->dir).vy = seatedptr->rotation;
		(pedptr->position).vx = seatedptr->x;
		(pedptr->position).vz = seatedptr->z;
		(pedptr->position).vy = player.pos[1];
		iVar2 = MapHeight((VECTOR *)&pedptr->position);
		(pedptr->position).vy = -0x4b - iVar2;
		pedptr->index = 1;
		pedptr->seat_index = (char)seat_index;
		pedptr->pedType = CIVILIAN;
		SetupPedestrian(pedptr);
		puVar1 = PTR_CivPedSit_000a1690;
		pedptr->fpAgitatedState = (_func_2 *)0x0;
		pedptr->fpRestState = puVar1;
		lVar3 = Random2(0);
		lVar4 = Random2(0);
		pedptr->pallet =
			(char)lVar3 + (char)(lVar3 / 5) * -5 + ((char)lVar4 + (char)(lVar4 / 5) * -5) * '\x10';
		lVar3 = Random2(0);
		if ((lVar3 / 6) * 6 == lVar3 + -3) {
			pedptr->flags = pedptr->flags | 0x4000;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ set_coll_box(int index /*$t2*/, struct _CAR_DATA *cp /*$t0*/, int offset /*$t3*/)
 // line 5084, offset 0x00071a5c
	/* begin block 1 */
		// Start line: 5085
		// Start offset: 0x00071A5C
		// Variables:
	// 		struct VECTOR BoxCentre; // stack offset -16
	// 		int boxsize; // $t1
	/* end block 1 */
	// End offset: 0x00071B74
	// End Line: 5110

	/* begin block 2 */
		// Start line: 11714
	/* end block 2 */
	// End Line: 11715

void set_coll_box(int index, _CAR_DATA *cp, int offset)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;

	if (8 < index) {
		return;
	}
	iVar5 = 400;
	if (player.horn.on != '\0') {
		iVar5 = 0x104;
		if (cp != car_data + player.playerCarId) goto LAB_00071b00;
		iVar5 = 0x4b0;
	}
	if (cp != car_data + player.playerCarId) {
		iVar5 = iVar5 + -0x8c;
	}
LAB_00071b00:
	iVar1 = *(int *)(cp->st + 0x1c);
	iVar2 = (cp->hd).where.t[0];
	iVar4 = *(int *)(cp->st + 0x24);
	iVar3 = (cp->hd).where.t[2];
	collision_car_ptr8[index] = cp;
	iVar2 = iVar2 + (iVar1 >> (offset & 0x1fU));
	iVar3 = iVar3 + (iVar4 >> (offset & 0x1fU));
	(&collision_box)[index].min_x = iVar2 - iVar5;
	(&collision_box)[index].min_z = iVar3 - iVar5;
	(&collision_box)[index].max_x = iVar2 + iVar5;
	(&collision_box)[index].max_z = iVar3 + iVar5;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ BuildCarCollisionBox()
 // line 5118, offset 0x00071b7c
	/* begin block 1 */
		// Start line: 5120
		// Start offset: 0x00071B7C
		// Variables:
	// 		struct _CAR_DATA *cp; // $s3
	// 		int count1; // $s4
	// 		int i; // $t1

		/* begin block 1.1 */
			// Start line: 5146
			// Start offset: 0x00071CBC
			// Variables:
		// 		int x; // $a0
		// 		int z; // $a2
		/* end block 1.1 */
		// End offset: 0x00071D58
		// End Line: 5155
	/* end block 1 */
	// End offset: 0x00071E0C
	// End Line: 5171

	/* begin block 2 */
		// Start line: 11805
	/* end block 2 */
	// End Line: 11806

	/* begin block 3 */
		// Start line: 11806
	/* end block 3 */
	// End Line: 11807

	/* begin block 4 */
		// Start line: 11808
	/* end block 4 */
	// End Line: 11809

/* WARNING: Unknown calling convention yet parameter storage is locked */

void BuildCarCollisionBox(void)
{
	UNIMPLEMENTED();
	/*
	CAR_COLLISION_BOX *pCVar1;
	CAR_COLLISION_BOX *pCVar2;
	uint uVar3;
	int iVar4;
	int index;
	_ExOBJECT *p_Var5;
	_CAR_DATA *cp;

	iVar4 = (int)player.playerCarId;
	set_coll_box(0, car_data + iVar4, 8);
	set_coll_box(1, car_data + iVar4, 9);
	iVar4 = 2;
	cp = car_data + (CameraCnt & 3);
	index = iVar4;
	if (cp < car_data + 0x14) {
		do {
			iVar4 = index;
			if ((cp != car_data + player.playerCarId) && (cp->controlType != '\0')) {
				iVar4 = index + 1;
				set_coll_box(index, cp, 8);
			}
			cp = cp + 4;
			index = iVar4;
		} while (cp < car_data + 0x14);
	}
	if (player.playerType == '\x02') {
		uVar3 = (int)((player.pPed)->dir).vy - 0x800U & 0xfff;
		index = (int)(player.pPed)->speed * (int)rcossin_tbl[uVar3 * 2] * 4 >> 0xc;
		tanner_collision_box.min_x = ((player.pPed)->position).vx + index + -0x94;
		tanner_collision_box.max_x = ((player.pPed)->position).vx + index + 0x94;
		index = (int)(player.pPed)->speed * (int)rcossin_tbl[uVar3 * 2 + 1] * 4 >> 0xc;
		tanner_collision_box.min_z = ((player.pPed)->position).vz + index + -0x94;
		tanner_collision_box.max_z = ((player.pPed)->position).vz + index + 0x94;
	}
	num_extra_boxes_set = 0;
	p_Var5 = explosion;
	index = 4;
	collision_boxes_set = iVar4;
	do {
		if (0x7ff < p_Var5->time) {
			iVar4 = (p_Var5->pos).vx;
			extra_collision_boxes[num_extra_boxes_set].min_x = iVar4 + -0x7a0;
			extra_collision_boxes[num_extra_boxes_set].max_x = iVar4 + 0x7a0;
			pCVar1 = extra_collision_boxes + num_extra_boxes_set;
			pCVar2 = extra_collision_boxes + num_extra_boxes_set;
			iVar4 = (p_Var5->pos).vz;
			num_extra_boxes_set = num_extra_boxes_set + 1;
			pCVar1->min_z = iVar4 + -0x7a0;
			pCVar2->max_z = iVar4 + 0x7a0;
		}
		index = index + -1;
		p_Var5 = p_Var5 + 1;
	} while (-1 < index);
	return;*/
}



// decompiled code
// original method signature: 
// struct _CAR_DATA * /*$ra*/ CheckForCar(struct PEDESTRIAN *pedestrian /*$s3*/)
 // line 5178, offset 0x00072738
	/* begin block 1 */
		// Start line: 5179
		// Start offset: 0x00072738
		// Variables:
	// 		int count; // $s0

		/* begin block 1.1 */
			// Start line: 5183
			// Start offset: 0x00072770
		/* end block 1.1 */
		// End offset: 0x00072790
		// End Line: 5204

		/* begin block 1.2 */
			// Start line: 5206
			// Start offset: 0x000727B4
		/* end block 1.2 */
		// End offset: 0x000727B4
		// End Line: 5213

		/* begin block 1.3 */
			// Start line: 5217
			// Start offset: 0x00072800
		/* end block 1.3 */
		// End offset: 0x0007281C
		// End Line: 5221
	/* end block 1 */
	// End offset: 0x0007283C
	// End Line: 5223

	/* begin block 2 */
		// Start line: 19327
	/* end block 2 */
	// End Line: 19328

	/* begin block 3 */
		// Start line: 19529
	/* end block 3 */
	// End Line: 19530

	/* begin block 4 */
		// Start line: 19531
	/* end block 4 */
	// End Line: 19532

_CAR_DATA * CheckForCar(PEDESTRIAN *pedestrian)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	int iVar3;
	CAR_COLLISION_BOX *collision_box;
	_CAR_DATA **pp_Var4;

	iVar3 = 0;
	if (0 < collision_boxes_set) {
		pp_Var4 = collision_car_ptr8;
		collision_box = &collision_box;
		do {
			iVar1 = CheckForPlayerCar(pedestrian, collision_box);
			iVar3 = iVar3 + 1;
			if (iVar1 != 0) {
				return *pp_Var4;
			}
			pp_Var4 = pp_Var4 + 1;
			collision_box = collision_box + 1;
		} while (iVar3 < collision_boxes_set);
	}
	iVar3 = 0;
	while ((iVar1 = bAvoidBomb, iVar3 < num_extra_boxes_set &&
		(iVar2 = CheckForPlayerCar(pedestrian, extra_collision_boxes + iVar3), iVar1 = iVar3,
			iVar2 == 0))) {
		iVar3 = iVar3 + 1;
	}
	bAvoidBomb = iVar1;
	if ((player.playerType == '\x02') &&
		(iVar3 = CheckForPlayerCar(pedestrian, &tanner_collision_box), iVar3 != 0)) {
		bAvoidTanner = 1;
	}
	return (_CAR_DATA *)0x0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckForPlayerCar(struct PEDESTRIAN *pedestrian /*$a0*/, struct CAR_COLLISION_BOX *collision_box /*$a1*/)
 // line 5231, offset 0x000732c0
	/* begin block 1 */
		// Start line: 26722
	/* end block 1 */
	// End Line: 26723

	/* begin block 2 */
		// Start line: 26723
	/* end block 2 */
	// End Line: 26724

// [D]
int CheckForPlayerCar(PEDESTRIAN *pedestrian, CAR_COLLISION_BOX *collision_box)
{
	int iVar1;

	iVar1 = (pedestrian->position).vx;
	if ((collision_box->min_x <= iVar1) && (iVar1 <= collision_box->max_x)) {
		iVar1 = (pedestrian->position).vz;
		if (collision_box->min_z <= iVar1) {
			return (uint)(collision_box->max_z < iVar1) ^ 1;
		}
		return 0;
	}
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CalculatePedestrianInterest(struct PEDESTRIAN *pPed /*$s0*/)
 // line 5249, offset 0x00071e0c
	/* begin block 1 */
		// Start line: 5250
		// Start offset: 0x00071E0C
		// Variables:
	// 		int interest; // $a2
	// 		int dist; // $v1
	// 		struct _CAR_DATA *pCar; // $a2
	// 		struct VECTOR v1; // stack offset -40
	// 		struct VECTOR v2; // stack offset -24
	/* end block 1 */
	// End offset: 0x00071F44
	// End Line: 5318

	/* begin block 2 */
		// Start line: 12043
	/* end block 2 */
	// End Line: 12044

	/* begin block 3 */
		// Start line: 12122
	/* end block 3 */
	// End Line: 12123

	/* begin block 4 */
		// Start line: 12128
	/* end block 4 */
	// End Line: 12129

void CalculatePedestrianInterest(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint uVar5;
	int iVar6;
	undefined *puVar7;

	iVar6 = (int)player.playerCarId;
	basic_car_interest = (car_data[iVar6].hd.wheel_speed >> 10) + (uint)car_data[iVar6].totalDamage;
	iVar4 = (pPed->position).vx - car_data[iVar6].hd.where.t[0];
	iVar2 = (pPed->position).vz - car_data[iVar6].hd.where.t[2];
	iVar6 = iVar4;
	if (iVar4 < 0) {
		iVar6 = -iVar4;
	}
	iVar3 = iVar2;
	if (iVar2 < 0) {
		iVar3 = -iVar2;
	}
	if (iVar6 + iVar3 < 0x1771) {
		puVar7 = &DAT_00001770 + -(iVar6 + iVar3);
	}
	else {
		puVar7 = (undefined *)0x0;
	}
	if (pPed->type == PED_ACTION_JUMP) {
		sVar1 = ratan2(iVar2, iVar4);
		pPed->head_rot = (pPed->dir).vy + sVar1 + 0xc00U & 0xfff;
	}
	else {
		if (2999 < (int)(puVar7 + basic_car_interest)) {
			pPed->interest = (short)(puVar7 + basic_car_interest);
			iVar6 = ratan2(iVar2, iVar4);
			uVar5 = (uint)(ushort)(pPed->dir).vy + iVar6 + 0xc00 & 0xfff;
			pPed->head_rot = (short)uVar5;
			if (0x8fe < uVar5 - 0x381) {
				return;
			}
		}
		pPed->head_rot = 0;
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ PedSurfaceType(struct VECTOR *ped_pos /*$a0*/)
 // line 5325, offset 0x00072584
	/* begin block 1 */
		// Start line: 5330
		// Start offset: 0x00072584
		// Variables:
	// 		struct _sdPlane *sfc_ptr; // $v0
	/* end block 1 */
	// End offset: 0x000725B8
	// End Line: 5335

	/* begin block 2 */
		// Start line: 18922
	/* end block 2 */
	// End Line: 18923

	/* begin block 3 */
		// Start line: 19313
	/* end block 3 */
	// End Line: 19314

	/* begin block 4 */
		// Start line: 19317
	/* end block 4 */
	// End Line: 19318

int PedSurfaceType(VECTOR *ped_pos)
{
	UNIMPLEMENTED();
	return 0;
	/*
	_sdPlane *p_Var1;
	int iVar2;

	p_Var1 = sdGetCell(ped_pos);
	if (p_Var1 == (_sdPlane *)0x0) {
		iVar2 = 0;
	}
	else {
		iVar2 = (int)p_Var1->surface;
	}
	return iVar2;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessChairLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
 // line 5344, offset 0x00073328
	/* begin block 1 */
		// Start line: 26847
	/* end block 1 */
	// End Line: 26848

	/* begin block 2 */
		// Start line: 26951
	/* end block 2 */
	// End Line: 26952

	/* begin block 3 */
		// Start line: 26952
	/* end block 3 */
	// End Line: 26953

void ProcessChairLump(char *lump_file, int lump_size)
{
	UNIMPLEMENTED();
	/*
	seated_pedestrian = (SEATED_PEDESTRIANS *)lump_file;
	return;
}





