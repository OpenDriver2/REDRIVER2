#include "THISDUST.H"
#include "MGENERIC.H"
#include "MISSION.H"
#include "GLAUNCH.H"
#include "CARS.H"
#include "PLAYERS.H"
#include "COP_AI.H"
#include "REPLAYS.H"

#include "STRINGS.H"

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

// [D]
void StoreEndData(void)
{
	_TARGET *target;
	int i;
	SAVED_CAR_POS *carpos;

	if (gCurrentMissionNumber < 40) 
	{
		StorePlayerPosition(&MissionEndData.PlayerPos);

		i = 15;

		target = MissionTargets;
		carpos = MissionEndData.CarPos;

		do {
			if ((target->data[0] == 2) && ((target->data[1] & 0x10) != 0))
			{
				StoreCarPosition(target, carpos);
				carpos++;
			}
			i--;
			target++;
		} while (-1 < i);
	}
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

// [D]
void RestoreStartData(void)
{
	SAVED_CAR_POS *data;
	int i;

	if (gHaveStoredData != 0) 
	{
		RestorePlayerPosition(&MissionStartData.PlayerPos);

		data = MissionStartData.CarPos;
		i = 5;
		do {
			if (data->active != 0)
				RestoreCarPosition(data);

			i--;
			data++;
		} while (-1 < i);
	}
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

// [D]
void StorePlayerPosition(SAVED_PLAYER_POS *data)
{
	ushort type;

	if (player[0].playerType == 1)
		type = ((MissionHeader->residentModels[car_data[player[0].playerCarId].ap.model] & 0xfff) << 4) | 1 | car_data[player[0].playerCarId].ap.palette << 8;
	else
		type = 0;

	data->type = type;
	data->direction = player[0].dir;
	data->vx = player[0].pos[0];
	data->vy = player[0].pos[1];
	data->vz = player[0].pos[2];

	if (player[0].playerCarId < 0)
		data->felony = pedestrianFelony;
	else
		data->felony = car_data[player[0].playerCarId].felonyRating;

	if (player[0].playerType == 1)
	{
		data->totaldamage = car_data[player[0].playerCarId].totalDamage;
		data->damage[0] = car_data[player[0].playerCarId].ap.damage[0];
		data->damage[1] = car_data[player[0].playerCarId].ap.damage[1];
		data->damage[2] = car_data[player[0].playerCarId].ap.damage[2];
		data->damage[3] = car_data[player[0].playerCarId].ap.damage[3];
		data->damage[4] = car_data[player[0].playerCarId].ap.damage[4];
		data->damage[5] = car_data[player[0].playerCarId].ap.damage[5];
		return;
	}

	data->totaldamage = 0;
	data->damage[0] = 0;
	data->damage[1] = 0;
	data->damage[2] = 0;
	data->damage[3] = 0;
	data->damage[4] = 0;
	data->damage[5] = 0;
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

// [D]
void RestorePlayerPosition(SAVED_PLAYER_POS *data)
{
	if ((data->type & 0xf) == 1) 
	{
		PlayerStartInfo[0]->type = 1;
		PlayerStartInfo[0]->model = (data->type >> 4) & 0xf;
		PlayerStartInfo[0]->palette = (data->type >> 8) & 0xf;
	}
	else 
		PlayerStartInfo[0]->type = 2;

	if (gCurrentMissionNumber != 0x10) 
	{
		PlayerStartInfo[0]->position.vx = data->vx;
		PlayerStartInfo[0]->position.vz = data->vz;
		PlayerStartInfo[0]->rotation = data->direction;
	}

	PlayerStartInfo[0]->totaldamage = data->totaldamage;
	PlayerStartInfo[0]->damage[0] = data->damage[0];
	PlayerStartInfo[0]->damage[1] = data->damage[1];
	PlayerStartInfo[0]->damage[2] = data->damage[2];
	PlayerStartInfo[0]->damage[3] = data->damage[3];
	PlayerStartInfo[0]->damage[4] = data->damage[4];
	PlayerStartInfo[0]->damage[5] = data->damage[5];

	if (player[0].playerCarId < 0)
		pedestrianFelony = data->felony;
	else
		car_data[player[0].playerCarId].felonyRating = data->felony;
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

// [D]
void StoreCarPosition(_TARGET *target, SAVED_CAR_POS *data)
{
	int slot;

	slot = Mission.PhantomCarId;

	if ((target->data[10] & 0x400000U) == 0)
		slot = target->data[6];

	if (slot == -1)
		return;

	data->active = 1;
	data->model = MissionHeader->residentModels[car_data[slot].ap.model];

	data->palette = car_data[slot].ap.palette;
	data->totaldamage = car_data[slot].totalDamage;

	data->damage[0] = car_data[slot].ap.damage[0];
	data->damage[1] = car_data[slot].ap.damage[1];
	data->damage[2] = car_data[slot].ap.damage[2];
	data->damage[3] = car_data[slot].ap.damage[3];
	data->damage[4] = car_data[slot].ap.damage[4];
	data->damage[5] = car_data[slot].ap.damage[5];

	data->vx = car_data[slot].hd.where.t[0];
	data->vy = car_data[slot].hd.where.t[1];
	data->vz = car_data[slot].hd.where.t[2];

	data->direction = car_data[slot].hd.direction;

	if ((target->data[1] & 0x40U) != 0)
		data->active = -0x7f;
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

// [D]
void RestoreCarPosition(SAVED_CAR_POS *data)
{
	ReplayStreams[numPlayersToCreate].InitialPadRecordBuffer = (PADRECORD*)ReplayStart;
	ReplayStreams[numPlayersToCreate].PadRecordBuffer = (PADRECORD*)ReplayStart;
	ReplayStreams[numPlayersToCreate].PadRecordBufferEnd = (PADRECORD*)ReplayStart;

	ReplayStreams[numPlayersToCreate].playbackrun = 0;
	ReplayStreams[numPlayersToCreate].length = 0;

	PlayerStartInfo[numPlayersToCreate] = &ReplayStreams[numPlayersToCreate].SourceType;

	if ((data->active & 0x80U) == 0) 
	{
		ReplayStreams[numPlayersToCreate].SourceType.type = 1;
		ReplayStreams[numPlayersToCreate].SourceType.model = data->model;
		ReplayStreams[numPlayersToCreate].SourceType.palette = data->palette;
		ReplayStreams[numPlayersToCreate].SourceType.position.vy = 0;
		ReplayStreams[numPlayersToCreate].SourceType.position.vx = data->vx;
		ReplayStreams[numPlayersToCreate].SourceType.position.vz = data->vz;
		ReplayStreams[numPlayersToCreate].SourceType.rotation = data->direction;
		ReplayStreams[numPlayersToCreate].SourceType.totaldamage = data->totaldamage;
		ReplayStreams[numPlayersToCreate].SourceType.damage[0] = data->damage[0];
		ReplayStreams[numPlayersToCreate].SourceType.damage[1] = data->damage[1];
		ReplayStreams[numPlayersToCreate].SourceType.damage[2] = data->damage[2];
		ReplayStreams[numPlayersToCreate].SourceType.damage[3] = data->damage[3];
		ReplayStreams[numPlayersToCreate].SourceType.damage[4] = data->damage[4];
		ReplayStreams[numPlayersToCreate].SourceType.damage[5] = data->damage[5];
	}
	else 
	{
		memcpy(&ReplayStreams[numPlayersToCreate].SourceType, PlayerStartInfo[0], sizeof(STREAM_SOURCE));

		PlayerStartInfo[numPlayersToCreate]->type = 3;

		PlayerStartInfo[0]->type = 1;
		PlayerStartInfo[0]->model = data->model;
		PlayerStartInfo[0]->palette = data->palette;
		PlayerStartInfo[0]->position.vx = data->vx;
		PlayerStartInfo[0]->position.vy = 0;
		PlayerStartInfo[0]->position.vz = data->vz;
		PlayerStartInfo[0]->rotation = data->direction;
		PlayerStartInfo[0]->totaldamage = (uint)data->totaldamage;
		PlayerStartInfo[0]->damage[0] = (uint)data->damage[0];
		PlayerStartInfo[0]->damage[1] = (uint)data->damage[1];
		PlayerStartInfo[0]->damage[2] = (uint)data->damage[2];
		PlayerStartInfo[0]->damage[3] = (uint)data->damage[3];
		PlayerStartInfo[0]->damage[4] = (uint)data->damage[4];
		PlayerStartInfo[0]->damage[5] = (uint)data->damage[5];
	}
	numPlayersToCreate++;
}





