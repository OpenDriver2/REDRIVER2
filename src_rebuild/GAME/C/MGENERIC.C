#include "THISDUST.H"
#include "MGENERIC.H"


// decompiled code
// original method signature: 
// void /*$ra*/ StoreEndData()
 // line 62, offset 0x00060740
	/* begin block 1 */
		// Start line: 64
		// Start offset: 0x00060740
		// Variables:
	// 		struct _TARGET *target; // $s0
	// 		struct SAVED_CAR_POS *carpos; // $s2
	// 		int i; // $s1
	/* end block 1 */
	// End offset: 0x000607E4
	// End Line: 84

	/* begin block 2 */
		// Start line: 124
	/* end block 2 */
	// End Line: 125

	/* begin block 3 */
		// Start line: 347
	/* end block 3 */
	// End Line: 348

	/* begin block 4 */
		// Start line: 351
	/* end block 4 */
	// End Line: 352

/* WARNING: Unknown calling convention yet parameter storage is locked */

void StoreEndData(void)
{
	UNIMPLEMENTED();
	/*
	_TARGET *target;
	int iVar1;
	SAVED_CAR_POS *data;

	if (gCurrentMissionNumber < 0x28) {
		StorePlayerPosition((SAVED_PLAYER_POS *)&MissionEndData);
		data = MissionEndData.CarPos;
		iVar1 = 0xf;
		target = MissionTargets;
		do {
			if ((target->data[0] == 2) && ((target->data[1] & 0x10U) != 0)) {
				StoreCarPosition(target, data);
				data = data + 1;
			}
			iVar1 = iVar1 + -1;
			target = target + 1;
		} while (-1 < iVar1);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ RestoreStartData()
 // line 86, offset 0x000607e4
	/* begin block 1 */
		// Start line: 88
		// Start offset: 0x000607E4
		// Variables:
	// 		struct SAVED_CAR_POS *carpos; // $s0
	// 		int i; // $s1
	/* end block 1 */
	// End offset: 0x00060838
	// End Line: 104

	/* begin block 2 */
		// Start line: 396
	/* end block 2 */
	// End Line: 397

	/* begin block 3 */
		// Start line: 399
	/* end block 3 */
	// End Line: 400

	/* begin block 4 */
		// Start line: 400
	/* end block 4 */
	// End Line: 401

	/* begin block 5 */
		// Start line: 403
	/* end block 5 */
	// End Line: 404

/* WARNING: Unknown calling convention yet parameter storage is locked */

void RestoreStartData(void)
{
	UNIMPLEMENTED();
	/*
	SAVED_CAR_POS *data;
	int iVar1;

	if (gHaveStoredData != 0) {
		RestorePlayerPosition((SAVED_PLAYER_POS *)&MissionStartData);
		data = MissionStartData.CarPos;
		iVar1 = 5;
		do {
			if (data->active != '\0') {
				RestoreCarPosition(data);
			}
			iVar1 = iVar1 + -1;
			data = data + 1;
		} while (-1 < iVar1);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ StorePlayerPosition(struct SAVED_PLAYER_POS *data /*$a2*/)
 // line 109, offset 0x0005ffac
	/* begin block 1 */
		// Start line: 110
		// Start offset: 0x0005FFAC
		// Variables:
	// 		unsigned short type; // $a0
	/* end block 1 */
	// End offset: 0x00060248
	// End Line: 148

	/* begin block 2 */
		// Start line: 218
	/* end block 2 */
	// End Line: 219

void StorePlayerPosition(SAVED_PLAYER_POS *data)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	ushort uVar2;

	uVar2 = (ushort)(byte)player.playerType;
	if (player.playerType == '\x01') {
		uVar2 = (ushort)(((uint)*(ushort *)
			(MissionHeader->residentModels +
			(byte)car_data[player.playerCarId].ap.model) & 0xfff) << 4) | 1 |
				(ushort)(byte)car_data[player.playerCarId].ap.palette << 8;
	}
	data->type = uVar2;
	data->direction = (short)player.dir;
	data->vx = player.pos[0];
	data->vy = player.pos[1];
	data->vz = player.pos[2];
	if ((int)player.playerCarId < 0) {
		psVar1 = &pedestrianFelony;
	}
	else {
		psVar1 = &car_data[(int)player.playerCarId].felonyRating;
	}
	data->felony = (int)*psVar1;
	if (player.playerType == '\x01') {
		data->totaldamage = car_data[player.playerCarId].totalDamage;
		data->damage[0] = car_data[player.playerCarId].ap.damage[0];
		data->damage[1] = car_data[player.playerCarId].ap.damage[1];
		data->damage[2] = car_data[player.playerCarId].ap.damage[2];
		data->damage[3] = car_data[player.playerCarId].ap.damage[3];
		data->damage[4] = car_data[player.playerCarId].ap.damage[4];
		data->damage[5] = car_data[player.playerCarId].ap.damage[5];
		return;
	}
	data->totaldamage = 0;
	data->damage[0] = 0;
	data->damage[1] = 0;
	data->damage[2] = 0;
	data->damage[3] = 0;
	data->damage[4] = 0;
	data->damage[5] = 0;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ RestorePlayerPosition(struct SAVED_PLAYER_POS *data /*$a2*/)
 // line 150, offset 0x00060248
	/* begin block 1 */
		// Start line: 151
		// Start offset: 0x00060248
	/* end block 1 */
	// End offset: 0x000603B0
	// End Line: 178

	/* begin block 2 */
		// Start line: 300
	/* end block 2 */
	// End Line: 301

	/* begin block 3 */
		// Start line: 303
	/* end block 3 */
	// End Line: 304

void RestorePlayerPosition(SAVED_PLAYER_POS *data)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;

	if ((data->type & 0xf) == 1) {
		PlayerStartInfo8[0]->type = '\x01';
		PlayerStartInfo8[0]->model = (byte)(data->type >> 4) & 0xf;
		PlayerStartInfo8[0]->palette = (byte)(data->type >> 8) & 0xf;
	}
	else {
		PlayerStartInfo8[0]->type = '\x02';
	}
	if (gCurrentMissionNumber != 0x10) {
		(PlayerStartInfo8[0]->position).vx = data->vx;
		(PlayerStartInfo8[0]->position).vz = data->vz;
		PlayerStartInfo8[0]->rotation = data->direction;
	}
	PlayerStartInfo8[0]->totaldamage = (uint)data->totaldamage;
	PlayerStartInfo8[0]->damage[0] = (int)data->damage[0];
	PlayerStartInfo8[0]->damage[1] = (int)data->damage[1];
	PlayerStartInfo8[0]->damage[2] = (int)data->damage[2];
	PlayerStartInfo8[0]->damage[3] = (int)data->damage[3];
	PlayerStartInfo8[0]->damage[4] = (int)data->damage[4];
	PlayerStartInfo8[0]->damage[5] = (int)data->damage[5];
	if ((int)player.playerCarId < 0) {
		psVar1 = &pedestrianFelony;
	}
	else {
		psVar1 = &car_data[(int)player.playerCarId].felonyRating;
	}
	*psVar1 = *(short *)&data->felony;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ StoreCarPosition(struct _TARGET *target /*$t1*/, struct SAVED_CAR_POS *data /*$t0*/)
 // line 180, offset 0x000603b0
	/* begin block 1 */
		// Start line: 181
		// Start offset: 0x000603B0
		// Variables:
	// 		int slot; // $v1
	/* end block 1 */
	// End offset: 0x000604DC
	// End Line: 212

	/* begin block 2 */
		// Start line: 365
	/* end block 2 */
	// End Line: 366

	/* begin block 3 */
		// Start line: 368
	/* end block 3 */
	// End Line: 369

void StoreCarPosition(_TARGET *target, SAVED_CAR_POS *data)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	iVar1 = DAT_000d7c44;
	if ((target->data[10] & 0x400000U) == 0) {
		iVar1 = target->data[6];
	}
	if (iVar1 != -1) {
		data->active = '\x01';
		data->model = *(uchar *)(MissionHeader->residentModels + (byte)car_data[iVar1].ap.model);
		data->palette = car_data[iVar1].ap.palette;
		data->totaldamage = car_data[iVar1].totalDamage;
		data->damage[0] = car_data[iVar1].ap.damage[0];
		data->damage[1] = car_data[iVar1].ap.damage[1];
		data->damage[2] = car_data[iVar1].ap.damage[2];
		data->damage[3] = car_data[iVar1].ap.damage[3];
		data->damage[4] = car_data[iVar1].ap.damage[4];
		data->damage[5] = car_data[iVar1].ap.damage[5];
		data->vx = car_data[iVar1].hd.where.t[0];
		data->vy = car_data[iVar1].hd.where.t[1];
		data->vz = car_data[iVar1].hd.where.t[2];
		data->direction = *(short *)&car_data[iVar1].hd.direction;
		if ((target->data[1] & 0x40U) != 0) {
			data->active = -0x7f;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ RestoreCarPosition(struct SAVED_CAR_POS *data /*$a3*/)
 // line 214, offset 0x000604e4
	/* begin block 1 */
		// Start line: 439
	/* end block 1 */
	// End Line: 440

	/* begin block 2 */
		// Start line: 441
	/* end block 2 */
	// End Line: 442

void RestoreCarPosition(SAVED_CAR_POS *data)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	char *pcVar2;
	REPLAY_STREAM *pRVar3;
	STREAM_SOURCE *pSVar4;
	STREAM_SOURCE *pSVar5;
	undefined4 uVar6;
	long lVar7;
	long lVar8;

	pcVar2 = ReplayStart;
	iVar1 = numPlayersToCreate;
	*(char **)&ReplayStreams[numPlayersToCreate].InitialPadRecordBuffer = ReplayStart;
	*(char **)&ReplayStreams[iVar1].PadRecordBuffer = pcVar2;
	pRVar3 = ReplayStreams + iVar1;
	*(char **)&ReplayStreams[iVar1].PadRecordBufferEnd = pcVar2;
	ReplayStreams[iVar1].playbackrun = '\0';
	ReplayStreams[iVar1].length = 0;
	*(REPLAY_STREAM **)(PlayerStartInfo8 + iVar1) = pRVar3;
	if ((data->active & 0x80U) == 0) {
		(pRVar3->SourceType).type = '\x01';
		ReplayStreams[iVar1].SourceType.model = data->model;
		ReplayStreams[iVar1].SourceType.palette = data->palette;
		lVar7 = data->vx;
		ReplayStreams[iVar1].SourceType.position.vy = 0;
		ReplayStreams[iVar1].SourceType.position.vx = lVar7;
		ReplayStreams[iVar1].SourceType.position.vz = data->vz;
		ReplayStreams[iVar1].SourceType.rotation = data->direction;
		ReplayStreams[iVar1].SourceType.totaldamage = (uint)data->totaldamage;
		ReplayStreams[iVar1].SourceType.damage[0] = (uint)data->damage[0];
		ReplayStreams[iVar1].SourceType.damage[1] = (uint)data->damage[1];
		ReplayStreams[iVar1].SourceType.damage[2] = (uint)data->damage[2];
		ReplayStreams[iVar1].SourceType.damage[3] = (uint)data->damage[3];
		ReplayStreams[iVar1].SourceType.damage[4] = (uint)data->damage[4];
		ReplayStreams[iVar1].SourceType.damage[5] = (uint)data->damage[5];
	}
	else {
		pSVar5 = PlayerStartInfo8[0] + 1;
		pSVar4 = PlayerStartInfo8[0];
		do {
			uVar6 = *(undefined4 *)&pSVar4->flags;
			lVar7 = (pSVar4->position).vx;
			lVar8 = (pSVar4->position).vy;
			*(undefined4 *)&pRVar3->SourceType = *(undefined4 *)pSVar4;
			*(undefined4 *)&(pRVar3->SourceType).flags = uVar6;
			(pRVar3->SourceType).position.vx = lVar7;
			(pRVar3->SourceType).position.vy = lVar8;
			pSVar4 = (STREAM_SOURCE *)&(pSVar4->position).vz;
			pRVar3 = (REPLAY_STREAM *)&(pRVar3->SourceType).position.vz;
		} while (pSVar4 != pSVar5);
		PlayerStartInfo8[numPlayersToCreate]->type = '\x03';
		PlayerStartInfo8[0]->type = '\x01';
		PlayerStartInfo8[0]->model = data->model;
		PlayerStartInfo8[0]->palette = data->palette;
		(PlayerStartInfo8[0]->position).vx = data->vx;
		(PlayerStartInfo8[0]->position).vy = 0;
		(PlayerStartInfo8[0]->position).vz = data->vz;
		PlayerStartInfo8[0]->rotation = data->direction;
		PlayerStartInfo8[0]->totaldamage = (uint)data->totaldamage;
		PlayerStartInfo8[0]->damage[0] = (uint)data->damage[0];
		PlayerStartInfo8[0]->damage[1] = (uint)data->damage[1];
		PlayerStartInfo8[0]->damage[2] = (uint)data->damage[2];
		PlayerStartInfo8[0]->damage[3] = (uint)data->damage[3];
		PlayerStartInfo8[0]->damage[4] = (uint)data->damage[4];
		PlayerStartInfo8[0]->damage[5] = (uint)data->damage[5];
	}
	numPlayersToCreate = numPlayersToCreate + 1;
	return;
	*/
}





