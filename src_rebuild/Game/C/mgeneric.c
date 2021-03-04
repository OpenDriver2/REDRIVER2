#include "driver2.h"
#include "mgeneric.h"
#include "mission.h"
#include "glaunch.h"
#include "cars.h"
#include "players.h"
#include "cop_ai.h"
#include "replays.h"
#include "system.h"

#include "STRINGS.H"

// [D] [T] [A] returns player car slot
int StorePlayerPosition(SAVED_PLAYER_POS *data)
{
	ushort type;
	int slot;

	slot = player[0].playerCarId;

	if (player[0].playerType == 1)
		type = ((MissionHeader->residentModels[car_data[slot].ap.model] & 0xfff) << 4) | 1 | car_data[slot].ap.palette << 8;
	else
		type = 0;

	data->type = type;
	data->direction = player[0].dir;
	data->vx = player[0].pos[0];
	data->vy = player[0].pos[1];
	data->vz = player[0].pos[2];

	if (slot < 0)
		data->felony = pedestrianFelony;
	else
		data->felony = car_data[slot].felonyRating;

	if (player[0].playerType == 1)
	{
		data->totaldamage = car_data[slot].totalDamage;
	
		data->damage[0] = car_data[slot].ap.damage[0];
		data->damage[1] = car_data[slot].ap.damage[1];
		data->damage[2] = car_data[slot].ap.damage[2];
		data->damage[3] = car_data[slot].ap.damage[3];
		data->damage[4] = car_data[slot].ap.damage[4];
		data->damage[5] = car_data[slot].ap.damage[5];
	}
	else
	{
		data->totaldamage = 0;
	
		data->damage[0] = 0;
		data->damage[1] = 0;
		data->damage[2] = 0;
		data->damage[3] = 0;
		data->damage[4] = 0;
		data->damage[5] = 0;
	}

	return slot;
}


// [D] [T]
void RestorePlayerPosition(SAVED_PLAYER_POS *data)
{
	if ((data->type & 0xf) == 1) 
	{
		PlayerStartInfo[0]->type = 1;
		PlayerStartInfo[0]->model = (data->type >> 4) & 15;
		PlayerStartInfo[0]->palette = (data->type >> 8) & 15;
	}
	else 
		PlayerStartInfo[0]->type = 2;

	if (gCurrentMissionNumber != 16) 
	{
		PlayerStartInfo[0]->position.vx = data->vx;
		PlayerStartInfo[0]->position.vy = data->vy;
		PlayerStartInfo[0]->position.vz = data->vz;
		PlayerStartInfo[0]->rotation = data->direction & 0xfff;
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

// [D] [T]
void StoreCarPosition(MS_TARGET *target, SAVED_CAR_POS *data)
{
	int slot;

	if (target->car.flags & 0x400000)
		slot = Mission.PhantomCarId;
	else
		slot = target->car.slot;

	if (slot == -1)
		return;

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

	data->active = 1;
	
	if (target->target_flags & TARGET_FLAG_CAR_SWAPPED)
		data->active |= 0x80;
}


// [D] [T]
void RestoreCarPosition(SAVED_CAR_POS *data)
{
	if(!data->active)
		return;
	
	ReplayStreams[numPlayersToCreate].InitialPadRecordBuffer = (PADRECORD*)ReplayStart;
	ReplayStreams[numPlayersToCreate].PadRecordBuffer = (PADRECORD*)ReplayStart;
	ReplayStreams[numPlayersToCreate].PadRecordBufferEnd = (PADRECORD*)ReplayStart;

	ReplayStreams[numPlayersToCreate].playbackrun = 0;
	ReplayStreams[numPlayersToCreate].length = 0;

	PlayerStartInfo[numPlayersToCreate] = &ReplayStreams[numPlayersToCreate].SourceType;

	if (data->active & 0x80) 
	{
		memcpy((u_char*)PlayerStartInfo[numPlayersToCreate], (u_char*)PlayerStartInfo[0], sizeof(STREAM_SOURCE));

		PlayerStartInfo[numPlayersToCreate]->type = 3;
		PlayerStartInfo[numPlayersToCreate]->controlType = CONTROL_TYPE_CIV_AI;

		PlayerStartInfo[0]->type = 1;
		PlayerStartInfo[0]->model = data->model;
		PlayerStartInfo[0]->palette = data->palette;
		PlayerStartInfo[0]->position.vx = data->vx;
		PlayerStartInfo[0]->position.vy = data->vy;
		PlayerStartInfo[0]->position.vz = data->vz;
		PlayerStartInfo[0]->rotation = data->direction & 0xfff;
		PlayerStartInfo[0]->totaldamage = data->totaldamage;
		PlayerStartInfo[0]->damage[0] = data->damage[0];
		PlayerStartInfo[0]->damage[1] = data->damage[1];
		PlayerStartInfo[0]->damage[2] = data->damage[2];
		PlayerStartInfo[0]->damage[3] = data->damage[3];
		PlayerStartInfo[0]->damage[4] = data->damage[4];
		PlayerStartInfo[0]->damage[5] = data->damage[5];
	}
	else 
	{
		ReplayStreams[numPlayersToCreate].SourceType.type = 1;
		ReplayStreams[numPlayersToCreate].SourceType.model = data->model;
		ReplayStreams[numPlayersToCreate].SourceType.palette = data->palette;
		ReplayStreams[numPlayersToCreate].SourceType.position.vy = data->vy;
		ReplayStreams[numPlayersToCreate].SourceType.position.vx = data->vx;
		ReplayStreams[numPlayersToCreate].SourceType.position.vz = data->vz;
		ReplayStreams[numPlayersToCreate].SourceType.rotation = data->direction & 0xfff;
		ReplayStreams[numPlayersToCreate].SourceType.totaldamage = data->totaldamage;
		ReplayStreams[numPlayersToCreate].SourceType.damage[0] = data->damage[0];
		ReplayStreams[numPlayersToCreate].SourceType.damage[1] = data->damage[1];
		ReplayStreams[numPlayersToCreate].SourceType.damage[2] = data->damage[2];
		ReplayStreams[numPlayersToCreate].SourceType.damage[3] = data->damage[3];
		ReplayStreams[numPlayersToCreate].SourceType.damage[4] = data->damage[4];
		ReplayStreams[numPlayersToCreate].SourceType.damage[5] = data->damage[5];
	}
	numPlayersToCreate++;
}

// [D] [T]
void StoreEndData(void)
{
	int playerCarId;
	int numStored;
	MS_TARGET* target;
	int i;
	SAVED_CAR_POS* carpos;

	ClearMem((char*)&MissionEndData, sizeof(MissionEndData));
	
	if (gCurrentMissionNumber > 40)
		return;

	numStored = 0;
	playerCarId = StorePlayerPosition(&MissionEndData.PlayerPos);

	for(i = 0; i < 16 && numStored < 6; i++)
	{
		target = &MissionTargets[i];
		carpos = &MissionEndData.CarPos[numStored];

		if (target->type == Target_Car &&
			playerCarId != target->car.slot &&
			(target->target_flags & TARGET_FLAG_CAR_SAVED))
		{
			StoreCarPosition(target, carpos);
			numStored++;
		}
	}
}

// [D] [T]
void RestoreStartData(void)
{
	SAVED_CAR_POS* data;
	int i;

	if (!gHaveStoredData)
		return;

	RestorePlayerPosition(&MissionStartData.PlayerPos);

	for (i = 0; i < 6; i++)
	{
		RestoreCarPosition(&MissionStartData.CarPos[i]);
	}
}
