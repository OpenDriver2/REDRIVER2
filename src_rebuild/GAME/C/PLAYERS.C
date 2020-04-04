#include "THISDUST.H"
#include "PLAYERS.H"


// decompiled code
// original method signature: 
// void /*$ra*/ InitPlayer(struct _PLAYER *locPlayer /*$s1*/, struct _CAR_DATA *cp /*$s2*/, char carCtrlType /*$s3*/, int direction /*$s6*/, long (*startPos)[4] /*stack 16*/, int externModel /*stack 20*/, int palette /*stack 24*/, char *padid /*stack 28*/)
 // line 75, offset 0x000739d8
	/* begin block 1 */
		// Start line: 76
		// Start offset: 0x000739D8
	/* end block 1 */
	// End offset: 0x00073C0C
	// End Line: 127

	/* begin block 2 */
		// Start line: 454
	/* end block 2 */
	// End Line: 455

	/* begin block 3 */
		// Start line: 150
	/* end block 3 */
	// End Line: 151

void InitPlayer(_PLAYER *locPlayer, _CAR_DATA *cp, char carCtrlType, int direction, long(*startPos)[4], int externModel, int palette, char *padid)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	PEDESTRIAN *pPVar2;
	int model;
	long lVar3;
	uint playerType;

	playerType = externModel & 0xff;
	ClearMem((char *)locPlayer, 0x74);
	if ((gStartOnFoot == 0) || (carCtrlType == '\x04')) {
		if (MissionHeader->residentModels[0] == playerType) {
			model = 0;
		}
		else {
			if (MissionHeader->residentModels[1] == playerType) {
				model = 1;
			}
			else {
				if (MissionHeader->residentModels[2] == playerType) {
					model = 2;
				}
				else {
					if (MissionHeader->residentModels[3] == playerType) {
						model = 3;
					}
					else {
						model = 0xff;
						if (MissionHeader->residentModels[4] == playerType) {
							model = 4;
						}
					}
				}
			}
		}
		InitCar(cp, direction, startPos, carCtrlType, model, palette & 0xff, &locPlayer->padid);
		cp->controlFlags = cp->controlFlags | 4;
		locPlayer->worldCentreCarId = cp->id;
		locPlayer->cameraView = (NumPlayers == 2) << 1;
		locPlayer->playerCarId = cp->id;
		cVar1 = cp->id;
		locPlayer->playerType = '\x01';
		locPlayer->spoolXZ = (VECTOR *)(cp->hd).where.t;
		locPlayer->cameraCarId = cVar1;
		lVar3 = (cp->hd).where.t[1];
		locPlayer->car_is_sounding = '\0';
		locPlayer->pos[1] = lVar3;
	}
	else {
		ActivatePlayerPedestrian((_CAR_DATA *)0x0, padid, direction, startPos, playerType);
		locPlayer->playerType = '\x02';
		pPVar2 = pPlayerPed;
		locPlayer->spoolXZ = (VECTOR *)&pPlayerPed->position;
		model = (pPVar2->position).vy;
		locPlayer->playerCarId = -1;
		locPlayer->car_is_sounding = '\x02';
		locPlayer->cameraView = '\0';
		locPlayer->pos[1] = -model;
	}
	locPlayer->pos[0] = (*startPos)[0];
	lVar3 = (*startPos)[2];
	locPlayer->cameraAngle = 0x800;
	locPlayer->headPos = 0;
	locPlayer->headTarget = 0;
	locPlayer->headTimer = '\0';
	locPlayer->pos[2] = lVar3;
	cVar1 = *padid;
	locPlayer->targetCarId = -1;
	locPlayer->car_sound_timer = -1;
	(locPlayer->wheelnoise).chan = -1;
	(locPlayer->wheelnoise).sound = -1;
	(locPlayer->skidding).chan = -1;
	(locPlayer->skidding).sound = -1;
	locPlayer->padid = cVar1;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ChangeCarPlayerToPed(int playerID /*$s0*/)
 // line 130, offset 0x00073334
	/* begin block 1 */
		// Start line: 131
		// Start offset: 0x00073334
		// Variables:
	// 		struct _CAR_DATA *lcp; // $s2
	/* end block 1 */
	// End offset: 0x0007350C
	// End Line: 181

	/* begin block 2 */
		// Start line: 260
	/* end block 2 */
	// End Line: 261

void ChangeCarPlayerToPed(int playerID)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	PEDESTRIAN *pPVar2;
	int channel;
	int iVar3;

	iVar3 = (int)(&player)[playerID].playerCarId;
	my_sly_var = playerID;
	(&player)[playerID].headTimer = '\0';
	(&player)[playerID].cameraView = '\0';
	channel = 0x1000;
	if (NoPlayerControl == 0) {
		channel = car_data[iVar3].hd.direction + 0x600;
	}
	(&player)[playerID].cameraAngle = channel;
	(&player)[playerID].headTimer = '\0';
	(&player)[playerID].playerType = '\x02';
	channel = gInGameCutsceneActive;
	(&player)[playerID].headPos = 0;
	(&player)[playerID].headTarget = 0;
	(&player)[playerID].playerCarId = -1;
	(&player)[playerID].cameraCarId = -1;
	(&player)[playerID].targetCarId = -1;
	pPVar2 = pPlayerPed;
	if ((channel == 0) && (gInGameChaseActive == 0)) {
		(&player)[playerID].worldCentreCarId = -1;
		(&player)[playerID].spoolXZ = (VECTOR *)&pPVar2->position;
	}
	channel = 1;
	car_data[iVar3].controlType = '\x02';
	car_data[iVar3].wheel_angle = 0;
	car_data[iVar3].ai[0xf9] = 3;
	car_data[iVar3].ai[0xc] = 7;
	if (playerID != 0) {
		channel = 4;
	}
	StopChannel(channel);
	cVar1 = (&player)[playerID].skidding.chan;
	(&player)[playerID].skidding.sound = -1;
	StopChannel((int)cVar1);
	UnlockChannel((int)(&player)[playerID].skidding.chan);
	cVar1 = (&player)[playerID].wheelnoise.chan;
	(&player)[playerID].wheelnoise.sound = -1;
	StopChannel((int)cVar1);
	UnlockChannel((int)(&player)[playerID].wheelnoise.chan);
	Start3DSoundVolPitch
	(-1, 6, 3, car_data[iVar3].hd.where.t[0], car_data[iVar3].hd.where.t[1],
		car_data[iVar3].hd.where.t[2], 0, 0x1000);
	first_offence = '\x01';
	channel = CarHasSiren((uint)(byte)car_data[iVar3].ap.model);
	if (channel != 0) {
		(&player)[playerID].horn.on = '\0';
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ChangePedPlayerToCar(int playerID /*$s4*/, struct _CAR_DATA *newCar /*$s2*/)
 // line 184, offset 0x0007350c
	/* begin block 1 */
		// Start line: 185
		// Start offset: 0x0007350C
		// Variables:
	// 		struct _PLAYER *lPlayer; // $s1
	// 		int siren; // $s5
	// 		long *pos; // $s3
	// 		int carParked; // $s6
	/* end block 1 */
	// End offset: 0x00073898
	// End Line: 244

	/* begin block 2 */
		// Start line: 400
	/* end block 2 */
	// End Line: 401

	/* begin block 3 */
		// Start line: 404
	/* end block 3 */
	// End Line: 405

	/* begin block 4 */
		// Start line: 408
	/* end block 4 */
	// End Line: 409

void ChangePedPlayerToCar(int playerID, _CAR_DATA *newCar)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	char cVar2;
	byte bVar3;
	bool bVar4;
	uint uVar5;
	int channel;
	uint uVar6;
	int channel_00;
	long *plVar7;

	bVar4 = false;
	uVar5 = CarHasSiren((uint)(byte)(newCar->ap).model);
	plVar7 = (newCar->hd).where.t;
	if ((((newCar->controlType != '\x02') && (newCar->controlType != '\a')) || (newCar->ai[0xf9] != 3)
		) || ((newCar->ai[0xc] != 7 && (newCar->ai[0xc] != 5)))) {
		bVar4 = true;
	}
	(&player)[playerID].playerType = '\x01';
	(&player)[playerID].playerCarId = newCar->id;
	bVar1 = gInGameCutsceneActive == 0;
	(&player)[playerID].cameraCarId = newCar->id;
	if ((bVar1) && (gInGameChaseActive == 0)) {
		cVar2 = newCar->id;
		(&player)[playerID].spoolXZ = (VECTOR *)(newCar->hd).where.t;
		(&player)[playerID].worldCentreCarId = cVar2;
	}
	bVar3 = NoPlayerControl;
	(&player)[playerID].cameraView = (char)lastCarCameraView;
	channel = 0x1000;
	if (bVar3 == 0) {
		channel = (newCar->hd).direction + 0x600;
	}
	(&player)[playerID].cameraAngle = channel;
	(&player)[playerID].headPos = 0;
	(&player)[playerID].headTarget = 0;
	(&player)[playerID].headTimer = '\0';
	(&player)[playerID].padid = '\0';
	(&player)[playerID].pPed = (PEDESTRIAN *)0x0;
	if (playerID * 0x74 == 0) {
		newCar->controlType = '\x01';
		*(undefined4 *)newCar->ai = 0xd9772;
		newCar->hndType = '\0';
		if ((gCurrentMissionNumber != 0x20) &&
			(MissionHeader->residentModels[(byte)(newCar->ap).model] == 0)) {
			NoteFelony(&felonyData, '\v', 0x1000);
		}
	}
	if ((gCurrentMissionNumber == 0x21) && ((newCar->ap).model == '\x04')) {
		makeLimoPullOver = '\0';
	}
	Start3DSoundVolPitch(-1, 6, 3, *plVar7, (newCar->hd).where.t[1], (newCar->hd).where.t[2], 0, 0x1000);
	bVar3 = (newCar->ap).model;
	if (bVar3 == 4) {
		uVar6 = ResidentModelsBodge();
	}
	else {
		if (bVar3 < 3) {
			uVar6 = (uint)(byte)(newCar->ap).model;
		}
		else {
			uVar6 = (uint)(byte)(newCar->ap).model - 1;
		}
	}
	channel = 1;
	if (playerID != 0) {
		channel = 4;
	}
	Start3DSoundVolPitch
	(channel, 3, uVar6 * 3 + 1, *plVar7, (newCar->hd).where.t[1], (newCar->hd).where.t[2], -10000,
		0x1000);
	bVar3 = (newCar->ap).model;
	if (bVar3 == 4) {
		channel_00 = ResidentModelsBodge();
		channel = channel_00 << 1;
	}
	else {
		if (bVar3 < 3) {
			channel = (uint)(byte)(newCar->ap).model * 3;
			goto LAB_000737d4;
		}
		channel_00 = (uint)(byte)(newCar->ap).model - 1;
		channel = channel_00 * 2;
	}
	channel = channel + channel_00;
LAB_000737d4:
	channel_00 = 0;
	if (playerID != 0) {
		channel_00 = 3;
	}
	Start3DSoundVolPitch
	(channel_00, 3, channel, *plVar7, (newCar->hd).where.t[1], (newCar->hd).where.t[2], -10000,
		0x1000);
	if (uVar5 != 0) {
		channel = 2;
		if (playerID != 0) {
			channel = 5;
		}
		Start3DSoundVolPitch
		(channel, (uVar5 & 0xff00) >> 8, uVar5 & 0xff, *plVar7, (newCar->hd).where.t[1],
			(newCar->hd).where.t[2], -10000, 0x81);
	}
	if (bVar4) {
		HaveCarSoundStraightAway((char)playerID);
	}
	else {
		RequestSlightPauseBeforeCarSoundStarts((char)playerID);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdatePlayers()
 // line 247, offset 0x00073898
	/* begin block 1 */
		// Start line: 249
		// Start offset: 0x00073898
		// Variables:
	// 		struct _PLAYER *locPlayer; // $t0
	// 		struct _CAR_DATA *cp; // $v1
	/* end block 1 */
	// End offset: 0x000739D8
	// End Line: 286

	/* begin block 2 */
		// Start line: 550
	/* end block 2 */
	// End Line: 551

	/* begin block 3 */
		// Start line: 554
	/* end block 3 */
	// End Line: 555

	/* begin block 4 */
		// Start line: 555
	/* end block 4 */
	// End Line: 556

	/* begin block 5 */
		// Start line: 561
	/* end block 5 */
	// End Line: 562

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdatePlayers(void)
{
	UNIMPLEMENTED();
	/*
	uchar uVar1;
	int iVar2;
	long lVar3;
	long lVar4;
	long lVar5;
	TEXTURE_DETAILS *pTVar6;

	pedestrianFelony = 0;
	if ((gInGameCutsceneActive == 0) && (player.playerType = '\x01', player.pPed != (PEDESTRIAN *)0x0)
		) {
		player.playerType = '\x02';
	}
	pTVar6 = &button_textures;
	do {
		uVar1 = pTVar6[5].coords.u0;
		if (uVar1 == '\x01') {
			iVar2 = (int)(char)pTVar6[5].coords.u1;
			lVar3 = car_data[iVar2].hd.where.t[0];
			lVar4 = car_data[iVar2].hd.where.t[1];
			lVar5 = car_data[iVar2].hd.where.t[2];
			iVar2 = car_data[iVar2].hd.direction;
			*(int *)&pTVar6[1].coords.u3 = (int)(char)pTVar6[5].coords.v0 * 0x29c + 0xd127c;
			*(long *)&pTVar6->coords = lVar3;
			*(long *)&(pTVar6->coords).u2 = lVar4;
			*(long *)&pTVar6->tpageid = lVar5;
			*(int *)&pTVar6[1].coords.u1 = iVar2;
		}
		else {
			if (uVar1 == '\x02') {
				iVar2 = *(int *)&pTVar6[7].clutid;
				*(undefined4 *)&pTVar6->coords = *(undefined4 *)(iVar2 + 0x14);
				*(int *)&(pTVar6->coords).u2 = -*(int *)(iVar2 + 0x18);
				*(undefined4 *)&pTVar6->tpageid = *(undefined4 *)(iVar2 + 0x1c);
				*(int *)&pTVar6[1].coords.u1 = (int)*(short *)(iVar2 + 0x22) + -0x800;
			}
		}
		pTVar6 = (TEXTURE_DETAILS *)&pTVar6[-9].clutid;
	} while ((TEXTURE_DETAILS *)0xd9727 < pTVar6);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ RequestSlightPauseBeforeCarSoundStarts(char player_id /*$a0*/)
 // line 298, offset 0x00073c0c
	/* begin block 1 */
		// Start line: 771
	/* end block 1 */
	// End Line: 772

	/* begin block 2 */
		// Start line: 943
	/* end block 2 */
	// End Line: 944

void RequestSlightPauseBeforeCarSoundStarts(char player_id)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;

	uVar1 = (uint)(byte)player_id;
	(&player)[uVar1].car_is_sounding = '\x02';
	(&player)[uVar1].car_sound_timer = 10;
	(&player)[uVar1].idlevol = -10000;
	(&player)[uVar1].revsvol = -10000;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ HaveCarSoundStraightAway(char player_id /*$a0*/)
 // line 305, offset 0x00073c54
	/* begin block 1 */
		// Start line: 960
	/* end block 1 */
	// End Line: 961

void HaveCarSoundStraightAway(char player_id)
{
	UNIMPLEMENTED();
	/*
	(&player)[(byte)player_id].car_is_sounding = '\0';
	(&player)[(byte)player_id].car_sound_timer = -1;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ MakeTheCarShutUp(char player_id /*$a0*/)
 // line 310, offset 0x00073c8c
	/* begin block 1 */
		// Start line: 971
	/* end block 1 */
	// End Line: 972

void MakeTheCarShutUp(char player_id)
{
	UNIMPLEMENTED();
	/*
	(&player)[(byte)player_id].car_is_sounding = '\x01';
	(&player)[(byte)player_id].car_sound_timer = -1;
	return;
	*/
}





