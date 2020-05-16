#include "THISDUST.H"
#include "COP_AI.H"

COP_DATA gCopData = { 0, 0, 0, 2048, 0, 4096, 2048, 3000000, { 0, 0, 0, 0, 0 } };

int speed1[] = { 0xCB, 0xD2, 0xD9 };
int speed2[] = { 0xEE, 0x10A, 0x126 };

char sqtbl[] = {
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x81, 0x81, 0x81, 0x82, 0x82, 0x83, 0x83, 0x83, 0x84,
	0x84, 0x85, 0x86, 0x86, 0x87, 0x88, 0x88, 0x89, 0x8A,
	0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x90, 0x91,
	0x92, 0x93, 0x94, 0x95, 0x96, 0x98, 0x99, 0x9A, 0x9B,
	0x9C, 0x9D, 0x9E, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA6,
	0xA7, 0xA8, 0xAA, 0xAB, 0xAC, 0xAE, 0xAF, 0xB0, 0xB2,
	0xB3, 0xB5 };

int CopsCanSeePlayer = 0;
short pedestrianFelony = 0;

int numRoadblockCars = 0;
int roadblockCount = 0;
int copsAreInPursuit = 0;
int requestRoadblock = 0;
int roadblockDelay = 0xfa;
int roadblockDelayDiff = 0x5dc;
int requestCopCar = 0;
int cop_respawn_timer = 0;
char first_offence = 0;


// decompiled code
// original method signature: 
// void /*$ra*/ InitCopState(struct _CAR_DATA *cp /*$s0*/, char *extraData /*$a1*/)
 // line 577, offset 0x0002f680
	/* begin block 1 */
		// Start line: 2675
	/* end block 1 */
	// End Line: 2676

	/* begin block 2 */
		// Start line: 1154
	/* end block 2 */
	// End Line: 1155

void InitCopState(_CAR_DATA *cp, char *extraData)
{
	UNIMPLEMENTED();
	/*
	uchar uVar1;

	ClearMem((char *)cp->ai, 0x28);
	cp->controlType = '\x03';
	cp->controlFlags = '\0';
	cp->ai[0x11] = 1;
	if (gCopDifficultyLevel == 1) {
		cp->hndType = '\x03';
	}
	else {
		uVar1 = '\x04';
		if (gCopDifficultyLevel < 2) {
			if (gCopDifficultyLevel != 0) {
				cp->hndType = '\x04';
				return;
			}
			uVar1 = '\x02';
		}
		cp->hndType = uVar1;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ WibbleDownTheRoad(struct VECTOR *from /*$a0*/, int distance /*$s1*/, struct VECTOR *to /*$s5*/)
 // line 593, offset 0x0002d78c
	/* begin block 1 */
		// Start line: 594
		// Start offset: 0x0002D78C
		// Variables:
	// 		int th; // $s0
	// 		int j; // $s3
	// 		int thl[4]; // stack offset -136
	// 		struct VECTOR pos; // stack offset -120
	// 		struct VECTOR dir; // stack offset -104

		/* begin block 1.1 */
			// Start line: 604
			// Start offset: 0x0002D810
			// Variables:
		// 		struct VECTOR p2; // stack offset -88
		// 		struct VECTOR d2; // stack offset -72
		// 		int colour[3]; // stack offset -56
		/* end block 1.1 */
		// End offset: 0x0002D89C
		// End Line: 614
	/* end block 1 */
	// End offset: 0x0002D99C
	// End Line: 639

	/* begin block 2 */
		// Start line: 1186
	/* end block 2 */
	// End Line: 1187

void WibbleDownTheRoad(VECTOR *from, int distance, VECTOR *to)
{
	UNIMPLEMENTED();
	/*
	undefined4 uVar1;
	undefined4 uVar2;
	uint val;
	uint uVar3;
	uint *puVar4;
	int iVar5;
	uint local_88[4];
	long local_78;
	long local_74;
	long local_70;
	long local_6c;
	int local_68;
	int local_64;
	int local_60;
	undefined4 local_38;
	undefined4 local_34;
	undefined4 local_30;

	uVar2 = DAT_0001053c;
	uVar1 = DAT_00010534;
	local_78 = from->vx;
	local_74 = from->vy;
	local_70 = from->vz;
	local_6c = from->pad;
	if (distance < 0) {
		distance = distance + 3;
	}
	iVar5 = 0;
	puVar4 = local_88;
	do {
		local_38 = uVar1;
		local_30 = uVar2;
		local_34 = DAT_00010538;
		ReplayLog_Fnarr_He_Said_Log(local_78);
		ReplayLog_Fnarr_He_Said_Log(local_74);
		ReplayLog_Fnarr_He_Said_Log(local_70);
		val = getHeadingToPlayer(local_78, local_74, local_70);
		ReplayLog_Fnarr_He_Said_Log(val);
		if (iVar5 == 0) {
			uVar3 = distLogIndex & 7;
			distLogIndex = distLogIndex + 1;
			distanceReturnedLog[uVar3] = lastDistanceFound;
		}
		iVar5 = iVar5 + 1;
		local_64 = 0;
		local_68 = (distance >> 2) * (int)rcossin_tbl[(val & 0xfff) * 2] + 0x800 >> 0xc;
		local_60 = (distance >> 2) * (int)rcossin_tbl[(val & 0xfff) * 2 + 1] + 0x800 >> 0xc;
		*puVar4 = val;
		local_78 = local_78 + local_68;
		puVar4 = puVar4 + 1;
		local_74 = local_74 + local_64;
		local_70 = local_70 + local_60;
	} while (iVar5 < 4);
	to->vx = local_78;
	to->vy = local_74;
	to->vz = local_70;
	to->pad = local_6c;
	if (((local_88[3] - local_88[0]) + 200 & 0xfff) < 400) {
		pathStraight = 1;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitCops()
 // line 643, offset 0x0002d99c
	/* begin block 1 */
		// Start line: 1381
	/* end block 1 */
	// End Line: 1382

	/* begin block 2 */
		// Start line: 1386
	/* end block 2 */
	// End Line: 1387

	/* begin block 3 */
		// Start line: 1387
	/* end block 3 */
	// End Line: 1388

/* WARNING: Unknown calling convention yet parameter storage is locked */

void InitCops(void)
{
	UNIMPLEMENTED();
	/*
	targetVehicle = car_data;
	requestCopCar = 0;
	InitFelonySystem();
	InitPathFinding();
	felonyData.pursuitFelonyScale = 3000;
	gCopDesiredSpeedScale = 0x1000;
	gCopMaxPowerScale = 0x1000;
	gPuppyDogCop = 0;
	copsAreInPursuit = 0;
	player_position_known = 2;
	OutOfSightCount = 0;
	UpdateCopSightData();
	gCopData.autoMaxPowerScaleLimit = 0;
	gCopData.autoDesiredSpeedScaleLimit = 0;
	if (GameType == GAME_GETAWAY) {
		gCopRespawnTime = (int)&DAT_00002710;
	}
	else {
		if (GameType == GAME_SURVIVAL) {
			gCopRespawnTime = 0;
			gCopDesiredSpeedScale = (int)&DAT_000011f4;
			gCopMaxPowerScale = (int)&DAT_000011f4;
			gCopData.autoMaxPowerScaleLimit = 0x400;
			gCopData.autoDesiredSpeedScaleLimit = 0x400;
		}
		else {
			gCopRespawnTime = 0x140;
			if (gCurrentMissionNumber < 0x28) {
				gCopRespawnTime = gCurrentMissionNumber * -4 + 0x140;
			}
		}
	}
	LastHeading = -1;
	CarTail.vx = 0;
	pathStraight = 0;
	numActiveCops = 0;
	OutOfSightCount = 0;
	cop_respawn_timer = 0;
	CopsCanSeePlayer = 0;
	CarTail.vy = 0;
	CarTail.vz = 0;
	lastKnownPosition.vx = 0x7fffffff;
	lastKnownPosition.vy = 0x7fffffff;
	lastKnownPosition.vz = 0x7fffffff;
	InitCopData(&gCopData);
	copsAreInPursuit = 0;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ControlCops()
 // line 708, offset 0x0002dad8
	/* begin block 1 */
		// Start line: 710
		// Start offset: 0x0002DAD8

		/* begin block 1.1 */
			// Start line: 726
			// Start offset: 0x0002DB34
			// Variables:
		// 		int playerID; // $v1
		/* end block 1.1 */
		// End offset: 0x0002DB74
		// End Line: 729

		/* begin block 1.2 */
			// Start line: 749
			// Start offset: 0x0002DC6C
			// Variables:
		// 		int heading; // $s1
		// 		int rnd; // $s0
		/* end block 1.2 */
		// End offset: 0x0002DD9C
		// End Line: 774

		/* begin block 1.3 */
			// Start line: 784
			// Start offset: 0x0002DDFC
			// Variables:
		// 		int copsWereInPursuit; // $a1
		/* end block 1.3 */
		// End offset: 0x0002DE9C
		// End Line: 798

		/* begin block 1.4 */
			// Start line: 801
			// Start offset: 0x0002DEAC
		/* end block 1.4 */
		// End offset: 0x0002DEE0
		// End Line: 807
	/* end block 1 */
	// End offset: 0x0002DEE0
	// End Line: 809

	/* begin block 2 */
		// Start line: 1551
	/* end block 2 */
	// End Line: 1552

	/* begin block 3 */
		// Start line: 1552
	/* end block 3 */
	// End Line: 1553

	/* begin block 4 */
		// Start line: 1555
	/* end block 4 */
	// End Line: 1556

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void ControlCops(void)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	undefined3 extraout_var;
	long lVar2;
	long lVar3;
	short *psVar4;
	int direction;
	int iVar5;

	gCopData.autoBatterPlayerTrigger = 0x800;
	if ((CopsAllowed == 0) || (gInGameCutsceneActive != 0)) {
		player_position_known = 0;
		CopsCanSeePlayer = 0;
		requestCopCar = 0;
		direction = copsAreInPursuit;
	}
	else {
		if (-1 < (int)player.playerCarId) {
			targetVehicle = car_data + (int)player.playerCarId;
		}
		if (0 < player_position_known) {
			lastKnownPosition.vx = player.pos[0];
			lastKnownPosition.vy = player.pos[1];
			lastKnownPosition.vz = player.pos[2];
			lastKnownPosition.pad = player.pos[3];
		}
		UpdateCopMap();
		direction = LastHeading;
		if (((first_offence == '\0') && (CopsCanSeePlayer != 0)) && (numActiveCops != 0)) {
			if ((int)player.playerCarId < 0) {
				psVar4 = &pedestrianFelony;
			}
			else {
				psVar4 = &car_data[(int)player.playerCarId].felonyRating;
			}
			if (((0x292 < *psVar4) && (0x2d0 < TimeSinceLastSpeech)) && (0x14 < (targetVehicle->hd).speed)
				) {
				cVar1 = GetCarDirectionOfTravel(targetVehicle);
				direction = CONCAT31(extraout_var, cVar1);
				lVar2 = Random2(1);
				if (direction != LastHeading) {
					iVar5 = MaxPlayerDamage * 3;
					if (iVar5 < 0) {
						iVar5 = iVar5 + 3;
					}
					if (iVar5 >> 2 < (int)(uint)car_data[player.playerCarId].totalDamage) {
						lVar3 = lVar2;
						if (lVar2 < 0) {
							lVar3 = lVar2 + 3;
						}
						iVar5 = (lVar3 >> 2) * -4;
					}
					else {
						iVar5 = (lVar2 / 3) * -3;
					}
					iVar5 = lVar2 + iVar5;
					if (((first_offence == '\0') && (_last_cop_phrase != iVar5)) &&
						(0x2d0 < TimeSinceLastSpeech)) {
						if (iVar5 < 3) {
							CopSay(iVar5 + 0xf, direction);
							_last_cop_phrase = iVar5;
						}
						else {
							CopSay(6, 0);
							_last_cop_phrase = iVar5;
						}
					}
				}
			}
		}
		LastHeading = direction;
		if ((int)player.playerCarId < 0) {
			psVar4 = &pedestrianFelony;
		}
		else {
			psVar4 = &car_data[(int)player.playerCarId].felonyRating;
		}
		if (gCopData.autoBatterPlayerTrigger <= *psVar4) {
			gBatterPlayer = 1;
		}
		ControlCopDetection();
		AdjustFelony(&felonyData);
		ControlNumberOfCops();
		direction = 0;
		if (0 < player_position_known) {
			if ((int)player.playerCarId < 0) {
				psVar4 = &pedestrianFelony;
			}
			else {
				psVar4 = &car_data[(int)player.playerCarId].felonyRating;
			}
			if (0x292 < *psVar4) {
				direction = 1;
			}
		}
		if (direction != 0) {
			if (copsAreInPursuit == 0) {
				Pads[0].alarmShakeCounter = '\f';
			}
			if ((direction != 0) &&
				(copsAreInPursuit = direction, FunkUpDaBGMTunez(1), direction = copsAreInPursuit,
					first_offence != '\0')) {
				CopSay(9, 0);
				first_offence = '\0';
				said_picked_up = 1;
				direction = copsAreInPursuit;
			}
		}
	}
	copsAreInPursuit = direction;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CopControl(struct _CAR_DATA *cp /*$s1*/)
 // line 824, offset 0x0002f60c
	/* begin block 1 */
		// Start line: 825
		// Start offset: 0x0002F60C
	/* end block 1 */
	// End offset: 0x0002F680
	// End Line: 842

	/* begin block 2 */
		// Start line: 2903
	/* end block 2 */
	// End Line: 2904

	/* begin block 3 */
		// Start line: 1648
	/* end block 3 */
	// End Line: 1649

void CopControl(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;

	CopControl1(cp);
	bVar1 = cp->ai[0x13];
	CheckPingOut(cp);
	if ((bVar1 == 0) && (cp->controlType == '\0')) {
		numActiveCops = numActiveCops + -1;
		numCopCars = numCopCars + -1;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CopControl1(struct _CAR_DATA *cp /*$s1*/)
 // line 845, offset 0x0002defc
	/* begin block 1 */
		// Start line: 846
		// Start offset: 0x0002DEFC
		// Variables:
	// 		int currentSpeed; // $s7
	// 		int desiredSteerAngle; // $s4

		/* begin block 1.1 */
			// Start line: 893
			// Start offset: 0x0002DFC4
			// Variables:
		// 		int dx; // $a1
		// 		int dz; // $a0

			/* begin block 1.1.1 */
				// Start line: 897
				// Start offset: 0x0002E018
			/* end block 1.1.1 */
			// End offset: 0x0002E058
			// End Line: 905
		/* end block 1.1 */
		// End offset: 0x0002E058
		// End Line: 906

		/* begin block 1.2 */
			// Start line: 912
			// Start offset: 0x0002E070
			// Variables:
		// 		struct VECTOR pos; // stack offset -88
		/* end block 1.2 */
		// End offset: 0x0002E23C
		// End Line: 922

		/* begin block 1.3 */
			// Start line: 935
			// Start offset: 0x0002E23C
			// Variables:
		// 		enum AIZone targetZone; // $a0
		// 		struct VECTOR doordir; // stack offset -72
		// 		int targetFound; // $a1
		// 		int cx; // $s5
		// 		int cz; // $s6
		// 		int dvx; // $s0
		// 		int dvz; // $s3
		// 		int dist; // $s2
		// 		int framesToImpact; // $a1

			/* begin block 1.3.1 */
				// Start line: 984
				// Start offset: 0x0002E360
				// Variables:
			// 		int dz; // $a1
			// 		int idvx; // $v1
			// 		int idvz; // $v0
			/* end block 1.3.1 */
			// End offset: 0x0002E360
			// End Line: 984

			/* begin block 1.3.2 */
				// Start line: 1049
				// Start offset: 0x0002E5E4
				// Variables:
			// 		struct iVectNT path[2]; // stack offset -56
			// 		int slidevel; // $a3

				/* begin block 1.3.2.1 */
					// Start line: 1105
					// Start offset: 0x0002E8E8
					// Variables:
				// 		int plcrspd; // $a1
				/* end block 1.3.2.1 */
				// End offset: 0x0002E954
				// End Line: 1108
			/* end block 1.3.2 */
			// End offset: 0x0002EA28
			// End Line: 1124

			/* begin block 1.3.3 */
				// Start line: 1140
				// Start offset: 0x0002EA78
				// Variables:
			// 		int b; // $a0
			/* end block 1.3.3 */
			// End offset: 0x0002EAC0
			// End Line: 1145

			/* begin block 1.3.4 */
				// Start line: 1149
				// Start offset: 0x0002EAC0
				// Variables:
			// 		int steerdif; // $v1
			// 		int speeddif; // $a2
			// 		int maxPower; // $a1

				/* begin block 1.3.4.1 */
					// Start line: 1175
					// Start offset: 0x0002EBB8
					// Variables:
				// 		int sf; // $v1
				/* end block 1.3.4.1 */
				// End offset: 0x0002EBD0
				// End Line: 1177
			/* end block 1.3.4 */
			// End offset: 0x0002EC64
			// End Line: 1188
		/* end block 1.3 */
		// End offset: 0x0002EC64
		// End Line: 1188

		/* begin block 1.4 */
			// Start line: 1197
			// Start offset: 0x0002EC84
		/* end block 1.4 */
		// End offset: 0x0002ECAC
		// End Line: 1201
	/* end block 1 */
	// End offset: 0x0002ECAC
	// End Line: 1203

	/* begin block 2 */
		// Start line: 1831
	/* end block 2 */
	// End Line: 1832

void CopControl1(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	short sVar2;
	bool bVar3;
	char cVar4;
	short sVar5;
	int dvx;
	undefined3 extraout_var;
	undefined3 extraout_var_00;
	int iVar6;
	int *piVar7;
	short *psVar8;
	uint uVar9;
	int iVar10;
	undefined2 uVar11;
	int x;
	int dvz;
	int unaff_s4;
	int z;
	uint uVar12;
	VECTOR local_58;
	int local_48;
	int local_44;
	int local_40;
	uint local_30;
	int local_2c;

	dvx = (cp->hd).wheel_speed;
	cp->wheelspin = '\0';
	uVar12 = dvx + 0x800 >> 0xc;
	if (CopsAllowed == 0) {
	LAB_0002e048:
		cp->thrust = 0;
		cp->handbrake = '\x01';
		return;
	}
	bVar1 = cp->ai[0x13];
	if ((bVar1 != 0) || ((27000 < cp->totalDamage && (gCopData.immortal == 0)))) {
		cp->thrust = 0;
		if (0x55 < bVar1) {
			return;
		}
		if (bVar1 == 0) {
			numActiveCops = numActiveCops + -1;
		}
		cp->ai[0x13] = cp->ai[0x13] + 1;
		return;
	}
	if (DAT_000d7c84 != 0) {
		dvx = (cp->hd).where.t[0];
		dvz = dvx - gStopCops;
		if (dvz < 0) {
			dvz = gStopCops - dvx;
		}
		dvx = (cp->hd).where.t[2];
		x = dvx - DAT_000d7c80;
		if (x < 0) {
			x = DAT_000d7c80 - dvx;
		}
		if ((dvz + x < DAT_000d7c84 * 3 >> 1) &&
			(dvx = SquareRoot0(dvz * dvz + x * x), dvx < DAT_000d7c84)) goto LAB_0002e048;
	}
	if ((CameraCnt & 7U) == 0) {
		local_58.vx = (cp->hd).where.t[0] +
			((int)(cp->hd).where.m[2] * 400 + (int)(cp->hd).where.m[0] * -0x96 + 0x800 >> 0xc)
			;
		local_58.vy = (cp->hd).where.t[1] +
			((int)(cp->hd).where.m[5] * 400 + (int)(cp->hd).where.m[3] * -0x96 + 0x800 >> 0xc)
			;
		local_58.vz = (cp->hd).where.t[2] +
			((int)(cp->hd).where.m[8] * 400 + (int)(cp->hd).where.m[6] * -0x96 + 0x800 >> 0xc)
			;
		cVar4 = CellAtPositionEmpty(&local_58, 0x50);
		sVar5 = (cp->hd).where.m[2];
		sVar2 = (cp->hd).where.m[0];
		*(short *)(cp->ai + 0x22) = (short)CONCAT31(extraout_var, cVar4);
		local_58.vx = (cp->hd).where.t[0] + ((int)sVar5 * 400 + (int)sVar2 * 0x96 + 0x800 >> 0xc);
		local_58.vy = (cp->hd).where.t[1] +
			((int)(cp->hd).where.m[5] * 400 + (int)(cp->hd).where.m[3] * 0x96 + 0x800 >> 0xc);
		local_58.vz = (cp->hd).where.t[2] +
			((int)(cp->hd).where.m[8] * 400 + (int)(cp->hd).where.m[6] * 0x96 + 0x800 >> 0xc);
		cVar4 = CellAtPositionEmpty(&local_58, 0x50);
		*(short *)(cp->ai + 0x24) = (short)CONCAT31(extraout_var_00, cVar4);
	}
	local_48 = (int)(cp->hd).where.m[0];
	x = (cp->hd).where.t[0];
	z = (cp->hd).where.t[2];
	local_40 = (int)(cp->hd).where.m[6];
	local_44 = (int)(cp->hd).where.m[3];
	pathStraight = 0;
	dvx = *(int *)(targetVehicle->st + 0x1c) - *(int *)(cp->st + 0x1c);
	dvz = *(int *)(targetVehicle->st + 0x24) - *(int *)(cp->st + 0x24);
	if (((cp->hd).speed < 6) && (*(short *)(cp->ai + 0x16) != 0)) {
		*(short *)(cp->ai + 0x1a) = *(short *)(cp->ai + 0x1a) + 1;
	}
	else {
		*(undefined2 *)(cp->ai + 0x1a) = 0;
	}
	if ((10 < *(short *)(cp->ai + 0x1a)) && (*(short *)(cp->ai + 0x1e) == 0)) {
		uVar11 = 0xff38;
		*(undefined2 *)(cp->ai + 0x1e) = 0x16;
		uVar9 = (uint)*(ushort *)(cp->ai + 0x1c) & 7;
		*(short *)(cp->ai + 0x1c) = (short)uVar9;
		if (*(short *)(cp->ai + 0x16) < 0) {
			uVar11 = 200;
		}
		unaff_s4 = ((uVar9 * 5 & 6) - 3) * 0x80;
		*(undefined2 *)(cp->ai + 0x16) = uVar11;
		*(undefined2 *)(cp->ai + 0x1a) = 0;
	}
	iVar6 = FindCost(x, z, dvx, dvz);
	*(bool *)(cp->ai + 0x12) = iVar6 < 0xaf0;
	bVar3 = false;
	if (*(short *)(cp->ai + 0x1e) < 1) {
		if (iVar6 < 0x20d0) {
			iVar10 = dvx + 0x800 >> 0xc;
			dvx = dvz + 0x800 >> 0xc;
			dvz = iVar10 * iVar10 + dvx * dvx + 1;
			dvx = ((x - (targetVehicle->hd).where.t[0]) * iVar10 -
				((targetVehicle->hd).where.t[2] - z) * dvx) / dvz;
			if (dvz == 0) {
				trap(7);
			}
			if (gBatterPlayer == 0) {
				dvz = dvx * 3;
				dvx = dvz >> 2;
				if (dvz < 0) {
					dvx = dvz + 3 >> 2;
				}
			}
			if (dvx < 0) {
				dvx = 0;
			}
			else {
				if (0x3c < dvx) {
					dvx = 0x3c;
				}
			}
			dvz = (targetVehicle->hd).where.t[0] +
				(*(int *)(targetVehicle->st + 0x1c) * dvx + 0x800 >> 0xc);
			dvx = (targetVehicle->hd).where.t[2] +
				(*(int *)(targetVehicle->st + 0x24) * dvx + 0x800 >> 0xc);
			if (gBatterPlayer == 0) {
				iVar10 = (int)(targetVehicle->hd).where.m[2] * 5;
				if (iVar10 < 0) {
					iVar10 = iVar10 + 0x7f;
				}
				CarTail.vx = dvz - (iVar10 >> 7);
				dvz = (int)(targetVehicle->hd).where.m[8] * 5;
				if (dvz < 0) {
					dvz = dvz + 0x7f;
				}
				CarTail.vz = dvx - (dvz >> 7);
			}
			else {
				iVar10 = (int)(targetVehicle->hd).where.m[0] * 5;
				if (iVar10 < 0) {
					iVar10 = iVar10 + 0xff;
				}
				CarTail.vx = dvz + (iVar10 >> 8);
				dvz = (int)(targetVehicle->hd).where.m[6] * 5;
				if (dvz < 0) {
					dvz = dvz + 0xff;
				}
				CarTail.vz = dvx + (dvz >> 8);
			}
		}
		else {
			CarTail.vx = (targetVehicle->hd).where.t[0];
			CarTail.vz = (targetVehicle->hd).where.t[2];
		}
		if (cp->ai[0x12] == 0) {
			WibbleDownTheRoad((VECTOR *)(cp->hd).where.t, (cp->hd).speed * 10 + 0x2a8, &targetPoint);
		}
		else {
			targetPoint.vx = CarTail.vx;
			targetPoint.vz = CarTail.vz;
		}
		bVar3 = true;
		*(undefined4 *)(cp->ai + 8) = *(undefined4 *)cp->ai;
		*(undefined4 *)(cp->ai + 0xc) = *(undefined4 *)(cp->ai + 4);
		*(long *)cp->ai = targetPoint.vx;
		*(long *)(cp->ai + 4) = targetPoint.vz;
	}
	else {
		*(short *)(cp->ai + 0x1e) = *(short *)(cp->ai + 0x1e) + -1;
	}
	if (gTimeInWater == 0) {
		bVar3 = false;
	}
	if (bVar3) {
		dvz = local_48 * *(int *)(cp->st + 0x1c) + local_40 * *(int *)(cp->st + 0x24) + 0x800 >> 0xc;
		local_2c = (x - targetPoint.vx) * local_40 + (targetPoint.vz - z) * local_48 >> 0xc;
		dvx = ((targetPoint.vx - x) * local_48 + (targetPoint.vz - z) * local_40 >> 0xc) - dvz / 0x8c;
		if (dvx < 1) {
			if ((dvx * -2 < local_2c) && (*(short *)(cp->ai + 0x22) != 0)) goto LAB_0002e728;
			uVar9 = 2;
			bVar3 = -dvx < local_2c << 2;
		LAB_0002e708:
			if ((bVar3) && (cp->ai[0x12] != 0)) {
				uVar9 = 1;
			}
		}
		else {
			if ((local_2c <= dvx * 2) || (*(short *)(cp->ai + 0x24) == 0)) {
				uVar9 = 3;
				bVar3 = dvx < local_2c << 2;
				goto LAB_0002e708;
			}
		LAB_0002e728:
			uVar9 = 0;
		}
		local_30 = dvx + dvz / 0x8c;
		if (uVar9 == 1) {
			*(undefined2 *)(cp->ai + 0x16) = 0xffba;
			unaff_s4 = 0x11c;
			if ((int)(local_30 ^ uVar12) < 0) {
				unaff_s4 = -0x11c;
			}
		}
		else {
			if (uVar9 < 2) {
				if (uVar9 == 0) {
					if (pathStraight == 0) {
						piVar7 = &speed1;
					}
					else {
						piVar7 = &speed2;
					}
					*(undefined2 *)(cp->ai + 0x16) = *(undefined2 *)(piVar7 + gCopDifficultyLevel);
					if (gCopData.cutOffDistance < (int)(uint)*(ushort *)(cp->ai + 0x14)) {
						sVar5 = *(short *)(cp->ai + 0x16);
						if ((int)player.playerCarId < 0) {
							psVar8 = &pedestrianFelony;
						}
						else {
							psVar8 = &car_data[(int)player.playerCarId].felonyRating;
						}
						sVar2 = *psVar8;
						dvx = gCopData.cutOffPowerScale;
					}
					else {
						sVar5 = *(short *)(cp->ai + 0x16);
						if ((int)player.playerCarId < 0) {
							psVar8 = &pedestrianFelony;
						}
						else {
							psVar8 = &car_data[(int)player.playerCarId].felonyRating;
						}
						sVar2 = *psVar8;
						dvx = gCopDesiredSpeedScale;
					}
					*(short *)(cp->ai + 0x16) =
						(short)((int)sVar5 * (dvx + (sVar2 * gCopData.autoDesiredSpeedScaleLimit >> 0xc)) >>
							0xc);
					if ((gPuppyDogCop != 0) && (cp->ai[0x12] != 0)) {
						dvx = (targetVehicle->hd).speed + 10;
						if (iVar6 < 0xfa1) {
							*(short *)(cp->ai + 0x16) = *(short *)&(targetVehicle->hd).speed + 10;
						}
						else {
							dvz = (*(short *)(cp->ai + 0x16) - dvx) * (iVar6 + -4000);
							*(short *)(cp->ai + 0x16) =
								(short)dvx +
								((short)((ulonglong)((longlong)dvz * 0x10624dd3) >> 0x28) - (short)(dvz >> 0x1f))
								;
						}
					}
					unaff_s4 = (int)(local_30 * 0x200) / local_2c;
					if (local_2c == 0) {
						trap(7);
					}
				}
			}
			else {
				if (uVar9 < 4) {
					*(undefined2 *)(cp->ai + 0x16) = 0x6e;
					if ((*(short *)(cp->ai + 0x22) == 0) || (*(short *)(cp->ai + 0x24) == 0)) {
						*(undefined2 *)(cp->ai + 0x16) = 0xff88;
					}
					else {
						if (((uVar9 == 2) && (-0x82 < *(int *)(cp->st + 0x2c))) ||
							((uVar9 == 3 && (*(int *)(cp->st + 0x2c) < 0x82)))) {
							cp->wheelspin = '\x01';
						}
					}
					unaff_s4 = 0x200;
					if ((int)(local_30 ^ uVar12) < 0) {
						unaff_s4 = -0x200;
					}
				}
			}
		}
	}
	else {
		if (*(short *)(cp->ai + 0x1e) < 1) {
			*(undefined2 *)(cp->ai + 0x16) = 0;
			unaff_s4 = 0;
		}
	}
	if (((iVar6 < 0x1000) && (0 < (int)*(short *)(cp->ai + 0x16))) && (gBatterPlayer == 0)) {
		dvx = (targetVehicle->hd).speed + -0x14;
		if (dvx < 0x14) {
			dvx = 0x14;
		}
		*(short *)(cp->ai + 0x16) =
			(short)(iVar6 * (int)*(short *)(cp->ai + 0x16) + (0x1000 - iVar6) * dvx + 0x800 >> 0xc);
	}
	dvx = (gCopDifficultyLevel + 8) * 0x400;
	dvz = (int)*(short *)(cp->ai + 0x16) - uVar12;
	if (pathStraight != 0) {
		dvx = dvx + (gCopDifficultyLevel + 4) * 0x400;
	}
	if ((int)player.playerCarId < 0) {
		psVar8 = &pedestrianFelony;
	}
	else {
		psVar8 = &car_data[(int)player.playerCarId].felonyRating;
	}
	dvx = dvx * (gCopMaxPowerScale + (*psVar8 * gCopData.autoMaxPowerScaleLimit >> 0xc)) >> 0xc;
	sVar5 = (short)dvx;
	if (dvz < -0x32) {
		sVar5 = -sVar5;
	}
	else {
		if (0x32 < dvz) {
			cp->thrust = sVar5;
			goto LAB_0002eba4;
		}
		sVar5 = (short)((dvz * dvx) / 0x32);
	}
	cp->thrust = sVar5;
LAB_0002eba4:
	dvx = (cp->hd).speed;
	if (dvx < 0x30) {
		cp->thrust = (short)((int)cp->thrust * (dvx + 0x50) >> 7);
	}
	if (handlingType[cp->hndType].fourWheelDrive == '\x01') {
		cp->thrust = cp->thrust >> 1;
	}
	cp->thrust = (short)(((int)cp->thrust * 7) / 10);
	dvx = ((unaff_s4 + 0x800U & 0xfff) - 0x800) - (int)cp->wheel_angle;
	sVar5 = (short)dvx;
	if (dvx < -200) {
		sVar5 = -200;
	}
	else {
		if (200 < dvx) {
			sVar5 = 200;
		}
	}
	bVar1 = cp->ai[0x11];
	cp->wheel_angle = cp->wheel_angle + sVar5;
	if (bVar1 == 1) {
		dvx = getHeadingToPlayer((cp->hd).where.t[0], (cp->hd).where.t[1], (cp->hd).where.t[2]);
		(cp->hd).direction = dvx;
		TempBuildHandlingMatrix(cp, 0);
		cp->ai[0x11] = 0;
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ FindCost(int x /*$a0*/, int z /*$a1*/, int dvx /*$a2*/, int dvz /*$a3*/)
 // line 1231, offset 0x0002f8dc
	/* begin block 1 */
		// Start line: 1232
		// Start offset: 0x0002F8DC
		// Variables:
	// 		int tx; // $v0
	// 		int tz; // $v0
	// 		int dx; // $a2
	// 		int dz; // $v1
	// 		int d; // $v0
	/* end block 1 */
	// End offset: 0x0002F994
	// End Line: 1244

	/* begin block 2 */
		// Start line: 2048
	/* end block 2 */
	// End Line: 2049

	/* begin block 3 */
		// Start line: 4800
	/* end block 3 */
	// End Line: 4801

	/* begin block 4 */
		// Start line: 4802
	/* end block 4 */
	// End Line: 4803

int FindCost(int x, int z, int dvx, int dvz)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	if (dvx < 0) {
		dvx = dvx + 0xff;
	}
	if (dvz < 0) {
		dvz = dvz + 0xff;
	}
	x = x - ((targetVehicle->hd).where.t[0] + (dvx >> 8));
	if (x < 0) {
		x = -x;
	}
	z = z - ((targetVehicle->hd).where.t[2] + (dvz >> 8));
	if (z < 0) {
		z = -z;
	}
	iVar1 = z;
	if (x < z) {
		iVar1 = x;
		x = z;
	}
	if (x != 0) {
		if (x == 0) {
			trap(7);
		}
		x = x * (uint)(byte)sqtbl[(iVar1 << 6) / x];
		if (x < 0) {
			x = x + 0x7f;
		}
		return x >> 7;
	}
	return 0;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitCopData(struct COP_DATA *pCopData /*$a0*/)
 // line 1267, offset 0x0002f7f8
	/* begin block 1 */
		// Start line: 1268
		// Start offset: 0x0002F7F8
		// Variables:
	// 		short *pTrigger; // $v1
	// 		short trigger; // $a2
	/* end block 1 */
	// End offset: 0x0002F844
	// End Line: 1281

	/* begin block 2 */
		// Start line: 4374
	/* end block 2 */
	// End Line: 4375

	/* begin block 3 */
		// Start line: 2534
	/* end block 3 */
	// End Line: 2535

	/* begin block 4 */
		// Start line: 4378
	/* end block 4 */
	// End Line: 4379

void InitCopData(COP_DATA *pCopData)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	int iVar2;
	int iVar3;

	psVar1 = pCopData->trigger;
	iVar3 = 0;
	if (psVar1 < pCopData->trigger + 4) {
		iVar2 = 0x3330000;
		do {
			*psVar1 = (short)iVar3;
			iVar3 = iVar2 >> 0x10;
			psVar1 = psVar1 + 1;
			iVar2 = iVar2 + 0x3330000;
		} while (psVar1 < pCopData->trigger + 4);
	}
	*psVar1 = 0x7fff;
	said_picked_up = 0;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateCopSightData()
 // line 1308, offset 0x0002f844
	/* begin block 1 */
		// Start line: 1310
		// Start offset: 0x0002F844
		// Variables:
	// 		int angry; // $v1
	/* end block 1 */
	// End offset: 0x0002F8DC
	// End Line: 1314

	/* begin block 2 */
		// Start line: 4431
	/* end block 2 */
	// End Line: 4432

	/* begin block 3 */
		// Start line: 4459
	/* end block 3 */
	// End Line: 4460

	/* begin block 4 */
		// Start line: 4460
	/* end block 4 */
	// End Line: 4461

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdateCopSightData(void)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;

	if ((int)player.playerCarId < 0) {
		psVar1 = &pedestrianFelony;
	}
	else {
		psVar1 = &car_data[(int)player.playerCarId].felonyRating;
	}
	if (*psVar1 < 0x293) {
		copSightData.surroundViewDistance = 0xaa0;
		copSightData.frontViewDistance = 0x1e8c;
		copSightData.frontViewAngle = 0x200;
		return;
	}
	copSightData.surroundViewDistance = 0x1540;
	copSightData.frontViewDistance = 0x3fc0;
	copSightData.frontViewAngle = 0x400;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ControlCopDetection()
 // line 1368, offset 0x0002ecd8
	/* begin block 1 */
		// Start line: 1382
		// Start offset: 0x0002ECD8
		// Variables:
	// 		int dx; // $v1
	// 		int dz; // $a0
	// 		struct VECTOR vec; // stack offset -64
	// 		int ccx; // stack offset -32
	// 		int ccz; // stack offset -28
	// 		char *scratch; // $s4
	// 		struct _CAR_DATA *lcp; // $s1

		/* begin block 1.1 */
			// Start line: 1385
			// Start offset: 0x0002ECD8

			/* begin block 1.1.1 */
				// Start line: 1385
				// Start offset: 0x0002ECD8
				// Variables:
			// 		int angry; // $v1
			/* end block 1.1.1 */
			// End offset: 0x0002EDA8
			// End Line: 1391
		/* end block 1.1 */
		// End offset: 0x0002EDA8
		// End Line: 1391

		/* begin block 1.2 */
			// Start line: 1416
			// Start offset: 0x0002EDFC
			// Variables:
		// 		int dx; // $v1
		// 		int dz; // $v0
		/* end block 1.2 */
		// End offset: 0x0002EE7C
		// End Line: 1426

		/* begin block 1.3 */
			// Start line: 1434
			// Start offset: 0x0002EED0
			// Variables:
		// 		int distanceToPlayer; // $s0
		// 		int active; // $s2

			/* begin block 1.3.1 */
				// Start line: 1369
				// Start offset: 0x0002EF70
				// Variables:
			// 		struct _CAR_DATA *cp; // $s1
			// 		int distanceToPlayer; // $s0

				/* begin block 1.3.1.1 */
					// Start line: 1369
					// Start offset: 0x0002EF70
					// Variables:
				// 		int farDist; // $v1
				// 		int nearDist; // $v0
				// 		char result; // $s2

					/* begin block 1.3.1.1.1 */
						// Start line: 1369
						// Start offset: 0x0002EF90
						// Variables:
					// 		int theta; // $v1
					// 		struct VECTOR delta; // stack offset -48

						/* begin block 1.3.1.1.1.1 */
							// Start line: 1369
							// Start offset: 0x0002F030
						/* end block 1.3.1.1.1.1 */
						// End offset: 0x0002F034
						// End Line: 1369
					/* end block 1.3.1.1.1 */
					// End offset: 0x0002F034
					// End Line: 1369
				/* end block 1.3.1.1 */
				// End offset: 0x0002F034
				// End Line: 1369
			/* end block 1.3.1 */
			// End offset: 0x0002F034
			// End Line: 1369
		/* end block 1.3 */
		// End offset: 0x0002F050
		// End Line: 1452

		/* begin block 1.4 */
			// Start line: 1478
			// Start offset: 0x0002F164
		/* end block 1.4 */
		// End offset: 0x0002F164
		// End Line: 1478

		/* begin block 1.5 */
			// Start line: 1491
			// Start offset: 0x0002F190

			/* begin block 1.5.1 */
				// Start line: 1498
				// Start offset: 0x0002F1B8
			/* end block 1.5.1 */
			// End offset: 0x0002F228
			// End Line: 1518
		/* end block 1.5 */
		// End offset: 0x0002F238
		// End Line: 1520

		/* begin block 1.6 */
			// Start line: 1525
			// Start offset: 0x0002F25C
			// Variables:
		// 		int rnd; // $s0
		// 		int dir; // $s1
		/* end block 1.6 */
		// End offset: 0x0002F2C8
		// End Line: 1529

		/* begin block 1.7 */
			// Start line: 1534
			// Start offset: 0x0002F2FC
			// Variables:
		// 		int rnd; // $s0
		// 		int dir; // $s1
		/* end block 1.7 */
		// End offset: 0x0002F394
		// End Line: 1536
	/* end block 1 */
	// End offset: 0x0002F3CC
	// End Line: 1542

	/* begin block 2 */
		// Start line: 3020
	/* end block 2 */
	// End Line: 3021

	/* begin block 3 */
		// Start line: 3033
	/* end block 3 */
	// End Line: 3034

	/* begin block 4 */
		// Start line: 3036
	/* end block 4 */
	// End Line: 3037

	/* begin block 5 */
		// Start line: 3042
	/* end block 5 */
	// End Line: 3043

/* WARNING: Unknown calling convention yet parameter storage is locked */

void ControlCopDetection(void)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	char cVar2;
	short sVar3;
	int iVar4;
	short *psVar5;
	long lVar6;
	undefined3 extraout_var;
	undefined3 extraout_var_00;
	int direction;
	uint uVar7;
	VECTOR local_40;
	int local_30;
	int local_28;
	int local_20;
	int local_1c;

	local_40.vx = player.pos[0];
	local_40.vz = player.pos[2];
	GetVisSetAtPosition(&local_40, CopWorkMem, &local_20, &local_1c);
	if ((int)player.playerCarId < 0) {
		psVar5 = &pedestrianFelony;
	}
	else {
		psVar5 = &car_data[(int)player.playerCarId].felonyRating;
	}
	bVar1 = 0x292 < *psVar5;
	copSightData.surroundViewDistance = 0xaa0;
	if (bVar1) {
		copSightData.surroundViewDistance = 0x1540;
	}
	copSightData.frontViewDistance = 0x1e8c;
	if (bVar1) {
		copSightData.frontViewDistance = 0x3fc0;
	}
	copSightData.frontViewAngle = 0x200;
	if (bVar1) {
		copSightData.frontViewAngle = 0x400;
	}
	bVar1 = player_position_known < 1;
	player_position_known = 2;
	if (bVar1) {
		player_position_known = 1;
	}
	CopsCanSeePlayer = 0;
	if ((player.playerType != '\x02') && (-1 < player.playerCarId)) {
		if (numRoadblockCars != 0) {
			direction = roadblockLoc.vx - player.pos[0];
			if (direction < 0) {
				direction = -direction;
			}
			iVar4 = roadblockLoc.vz - player.pos[2];
			if (iVar4 < 0) {
				iVar4 = -iVar4;
			}
			if (((direction >> 8) * (direction >> 8) + (iVar4 >> 8) * (iVar4 >> 8) < 0x668) &&
				(direction = newPositionVisible(&roadblockLoc, CopWorkMem, local_20, local_1c), direction != 0
					)) {
				CopsCanSeePlayer = 1;
			}
		}
		if (CopsCanSeePlayer == 0) {
			uVar7 = 0xd43fc;
			while (0xd1267 < uVar7) {
				cVar2 = *(char *)(uVar7 + 0x189);
				if (cVar2 == '\x03') {
					if (*(char *)(uVar7 + 0x19f) == '\0') goto LAB_0002eed0;
				}
				else {
					if ((*(byte *)(uVar7 + 0x18a) & 1) != 0) {
					LAB_0002eed0:
						local_40.vx = *(long *)(uVar7 + 0x14);
						local_40.vz = *(long *)(uVar7 + 0x1c);
						direction = *(int *)(uVar7 + 0x14) - player.pos[0];
						if (direction < 0) {
							direction = player.pos[0] - *(int *)(uVar7 + 0x14);
						}
						iVar4 = *(int *)(uVar7 + 0x1c) - player.pos[2];
						if (iVar4 < 0) {
							iVar4 = player.pos[2] - *(int *)(uVar7 + 0x1c);
						}
						direction = SquareRoot0(direction * direction + iVar4 * iVar4);
						if ((cVar2 == '\x03') &&
							(*(undefined2 *)(uVar7 + 0x1a0) = (short)direction, *(char *)(uVar7 + 0x19e) != '\0')
							) {
						LAB_0002f040:
							CopsCanSeePlayer = 1;
							break;
						}
						iVar4 = newPositionVisible(&local_40, CopWorkMem, local_20, local_1c);
						if (iVar4 != 0) {
							if (direction < copSightData.surroundViewDistance) {
							LAB_0002f030:
								bVar1 = true;
							}
							else {
								bVar1 = false;
								if (direction < copSightData.frontViewDistance) {
									local_30 = (targetVehicle->hd).where.t[0] - *(int *)(uVar7 + 0x14);
									local_28 = (targetVehicle->hd).where.t[2] - *(int *)(uVar7 + 0x1c);
									direction = ratan2(local_30, local_28);
									if (direction - *(int *)(uVar7 + 0x68) < 0) {
										direction = ratan2(local_30, local_28);
										direction = *(int *)(uVar7 + 0x68) - direction;
									}
									else {
										direction = ratan2(local_30, local_28);
										direction = direction - *(int *)(uVar7 + 0x68);
									}
									if ((direction < (int)copSightData.frontViewAngle) ||
										(bVar1 = false, direction < (int)copSightData.frontViewAngle + 0x200))
										goto LAB_0002f030;
								}
							}
							if (bVar1) goto LAB_0002f040;
						}
					}
				}
				uVar7 = uVar7 - 0x29c;
			}
		}
	}
	if (((numActiveCops == 0) && (OutOfSightCount < 0x100)) && (8 < CameraCnt)) {
		OutOfSightCount = 0x100;
	}
	if (CopsCanSeePlayer == 0) {
		direction = OutOfSightCount + 1;
		if (0xff < OutOfSightCount) {
			if (OutOfSightCount == 0x100) {
				player_position_known = -1;
				OutOfSightCount = 0x101;
				if ((int)player.playerCarId < 0) {
					psVar5 = &pedestrianFelony;
				}
				else {
					psVar5 = &car_data[(int)player.playerCarId].felonyRating;
				}
				direction = OutOfSightCount;
				if ((0x292 < *psVar5) && (first_offence == '\0')) {
					CopSay(0xc, 0);
					FunkUpDaBGMTunez(0);
					direction = OutOfSightCount;
				}
			}
			else {
				player_position_known = 0;
				direction = OutOfSightCount;
			}
		}
	}
	else {
		OutOfSightCount = 0;
		direction = OutOfSightCount;
	}
	OutOfSightCount = direction;
	if (player_position_known < 1) {
		uVar7 = 0xd43fc;
		do {
			if (*(char *)(uVar7 + 0x189) == '\x03') {
				local_40.vx = *(long *)(uVar7 + 0x14);
				local_40.vz = *(long *)(uVar7 + 0x1c);
				direction = newPositionVisible(&local_40, CopWorkMem, local_20, local_1c);
				if ((direction == 0) &&
					(sVar3 = *(short *)(uVar7 + 0x1ac) + 1, *(short *)(uVar7 + 0x1ac) = sVar3, 0x32 < sVar3))
				{
					*(undefined *)(uVar7 + 0x189) = 0;
					*(undefined2 *)(uVar7 + 0x1ac) = 0;
					*(undefined2 *)(uVar7 + 0x28c) = 0;
					numCopCars = numCopCars + -1;
				}
			}
			uVar7 = uVar7 - 0x29c;
		} while (0xd1267 < uVar7);
	}
	direction = player_position_known;
	if ((player_position_known == 1) && (first_offence == '\0')) {
		lVar6 = Random2(2);
		cVar2 = GetCarDirectionOfTravel(car_data + player.playerCarId);
		CopSay(lVar6 % 2 + 10, CONCAT31(extraout_var, cVar2));
		said_picked_up = direction;
		LastHeading = CONCAT31(extraout_var, cVar2);
	}
	if (CopsCanSeePlayer == 0) {
		said_picked_up = 0;
	}
	else {
		if ((first_offence == '\0') && (said_picked_up == 0)) {
			lVar6 = Random2(2);
			cVar2 = GetCarDirectionOfTravel(car_data + player.playerCarId);
			direction = CONCAT31(extraout_var_00, cVar2);
			if ((lVar6 == (lVar6 / 5) * 5) && (direction != LastHeading)) {
				CopSay(lVar6 % 2 + 10, direction);
			}
			said_picked_up = 1;
			LastHeading = direction;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PassiveCopTasks(struct _CAR_DATA *cp /*$s0*/)
 // line 1562, offset 0x0002f6fc
	/* begin block 1 */
		// Start line: 1563
		// Start offset: 0x0002F6FC

		/* begin block 1.1 */
			// Start line: 1563
			// Start offset: 0x0002F76C
			// Variables:
		// 		struct _CAR_DATA *cp; // $s0
		/* end block 1.1 */
		// End offset: 0x0002F7C4
		// End Line: 1563
	/* end block 1 */
	// End offset: 0x0002F7F8
	// End Line: 1576

	/* begin block 2 */
		// Start line: 4648
	/* end block 2 */
	// End Line: 4649

	/* begin block 3 */
		// Start line: 4654
	/* end block 3 */
	// End Line: 4655

void PassiveCopTasks(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	uchar uVar1;
	short *psVar2;

	if ((int)player.playerCarId < 0) {
		psVar2 = &pedestrianFelony;
	}
	else {
		psVar2 = &car_data[(int)player.playerCarId].felonyRating;
	}
	if (*psVar2 < 0x293) {
		return;
	}
	if (player_position_known < 1) {
		return;
	}
	ClearMem((char *)cp->ai, 0x28);
	cp->controlType = '\x03';
	cp->controlFlags = '\0';
	cp->ai[0x11] = 1;
	if (gCopDifficultyLevel == 1) {
		cp->hndType = '\x03';
	}
	else {
		uVar1 = '\x04';
		if (gCopDifficultyLevel < 2) {
			if (gCopDifficultyLevel != 0) {
				cp->hndType = '\x04';
				goto LAB_0002f7c4;
			}
			uVar1 = '\x02';
		}
		cp->hndType = uVar1;
	}
LAB_0002f7c4:
	cp->ai[0x11] = 0;
	numCivCars = numCivCars + -1;
	numActiveCops = numActiveCops + 1;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ControlNumberOfCops()
 // line 1583, offset 0x0002f3cc
	/* begin block 1 */
		// Start line: 1585
		// Start offset: 0x0002F3CC
		// Variables:
	// 		int numWantedCops; // $t2

		/* begin block 1.1 */
			// Start line: 1588
			// Start offset: 0x0002F3CC
			// Variables:
		// 		short *pTrigger; // $a2
		/* end block 1.1 */
		// End offset: 0x0002F454
		// End Line: 1596

		/* begin block 1.2 */
			// Start line: 1609
			// Start offset: 0x0002F4A0
			// Variables:
		// 		int temp; // $a1
		/* end block 1.2 */
		// End offset: 0x0002F54C
		// End Line: 1624

		/* begin block 1.3 */
			// Start line: 1633
			// Start offset: 0x0002F570
			// Variables:
		// 		int num_closer; // $a2
		// 		int cutOffDistance; // $a1

			/* begin block 1.3.1 */
				// Start line: 1638
				// Start offset: 0x0002F580
				// Variables:
			// 		struct _CAR_DATA *lcp; // $a0
			// 		int tempDist; // $a3

				/* begin block 1.3.1.1 */
					// Start line: 1647
					// Start offset: 0x0002F5AC
					// Variables:
				// 		int copDist; // $v1
				/* end block 1.3.1.1 */
				// End offset: 0x0002F5CC
				// End Line: 1658
			/* end block 1.3.1 */
			// End offset: 0x0002F5DC
			// End Line: 1661
		/* end block 1.3 */
		// End offset: 0x0002F5E8
		// End Line: 1664
	/* end block 1 */
	// End offset: 0x0002F60C
	// End Line: 1671

	/* begin block 2 */
		// Start line: 3514
	/* end block 2 */
	// End Line: 3515

	/* begin block 3 */
		// Start line: 3556
	/* end block 3 */
	// End Line: 3557

	/* begin block 4 */
		// Start line: 3557
	/* end block 4 */
	// End Line: 3558

	/* begin block 5 */
		// Start line: 3560
	/* end block 5 */
	// End Line: 3561

/* WARNING: Unknown calling convention yet parameter storage is locked */

void ControlNumberOfCops(void)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short *psVar2;
	short *psVar3;
	uint uVar4;
	_CAR_DATA *p_Var5;
	uint uVar6;
	int iVar7;
	int iVar8;

	psVar2 = gCopData.trigger;
	iVar8 = 0;
	while (true) {
		sVar1 = *psVar2;
		psVar2 = psVar2 + 1;
		if ((int)player.playerCarId < 0) {
			psVar3 = &pedestrianFelony;
		}
		else {
			psVar3 = &car_data[(int)player.playerCarId].felonyRating;
		}
		if (*psVar3 < sVar1) break;
		iVar8 = iVar8 + 1;
	}
	iVar7 = gMinimumCops;
	if ((iVar8 < gMinimumCops) || (iVar7 = maxCopCars, maxCopCars < iVar8)) {
		iVar8 = iVar7;
	}
	if ((numCopCars < iVar8) && (gDontPingInCops == 0)) {
		iVar8 = gCopRespawnTime;
		if (Roadblock.status == '\x02') {
			iVar8 = Roadblock.copRespawnTime;
		}
		if ((int)player.playerCarId < 0) {
			psVar2 = &pedestrianFelony;
		}
		else {
			psVar2 = &car_data[(int)player.playerCarId].felonyRating;
		}
		if (iVar8 * (0x1000 - (*psVar2 * gCopData.autoRespawnScaleLimit >> 0xc)) >> 0xc <
			cop_respawn_timer + 1) {
			requestCopCar = 1;
		}
		cop_respawn_timer = cop_respawn_timer + 1;
		return;
	}
	if (iVar8 < numCopCars) {
		uVar6 = 0x7fffffff;
		do {
			gCopData.cutOffDistance = 0;
			p_Var5 = car_data;
			iVar7 = 0;
			do {
				if (p_Var5->controlType == '\x03') {
					uVar4 = (uint)*(ushort *)(p_Var5->ai + 0x14);
					if ((uVar4 < uVar6) && (iVar7 = iVar7 + 1, (uint)gCopData.cutOffDistance < uVar4)) {
						gCopData.cutOffDistance = uVar4;
					}
				}
				p_Var5 = p_Var5 + 1;
			} while (p_Var5 < (_CAR_DATA *)0xd4698);
			uVar6 = gCopData.cutOffDistance;
		} while (iVar8 < iVar7);
		cop_respawn_timer = 0;
		return;
	}
	gCopData.cutOffDistance = 0x7fffffff;
	cop_respawn_timer = 0;
	return;
	*/
}





