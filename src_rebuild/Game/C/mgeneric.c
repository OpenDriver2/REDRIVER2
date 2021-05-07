#include "driver2.h"
#include "mgeneric.h"
#include "mission.h"
#include "glaunch.h"
#include "cars.h"
#include "players.h"
#include "cop_ai.h"
#include "replays.h"
#include "system.h"

// [D] [T]
void StorePlayerPosition(SAVED_PLAYER_POS *data)
{
	CAR_DATA* cp;
	ushort type;
	int slot;

	slot = player[0].playerCarId;

	cp = &car_data[slot];

	if (player[0].playerType == 1)
		type = ((MissionHeader->residentModels[cp->ap.model] & 0xfff) << 4) | 1 | cp->ap.palette << 8;
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
		data->felony = cp->felonyRating;

	if (player[0].playerType == 1)
	{
		data->totaldamage = cp->totalDamage;
	
		data->damage[0] = cp->ap.damage[0];
		data->damage[1] = cp->ap.damage[1];
		data->damage[2] = cp->ap.damage[2];
		data->damage[3] = cp->ap.damage[3];
		data->damage[4] = cp->ap.damage[4];
		data->damage[5] = cp->ap.damage[5];
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
	CAR_DATA* cp;

	// if target is a swapable, make sure it gonna be previous player car
	if (target->s.car.flags & CARTARGET_FLAG_BACK_TO_PLAYERCAR)
		slot = Mission.PhantomCarId;
	else
		slot = target->s.car.slot;

	if (slot == -1)
		return;

	if (slot == player[0].playerCarId)
		return;

	cp = &car_data[slot];

	data->model = MissionHeader->residentModels[cp->ap.model];

	data->palette = cp->ap.palette;
	data->totaldamage = cp->totalDamage;

	data->damage[0] = cp->ap.damage[0];
	data->damage[1] = cp->ap.damage[1];
	data->damage[2] = cp->ap.damage[2];
	data->damage[3] = cp->ap.damage[3];
	data->damage[4] = cp->ap.damage[4];
	data->damage[5] = cp->ap.damage[5];

	data->vx = cp->hd.where.t[0];
	data->vy = cp->hd.where.t[1];
	data->vz = cp->hd.where.t[2];

	data->direction = cp->hd.direction;

	data->active = 1;
	
	if (target->s.target_flags & TARGET_FLAG_CAR_SWAPPED)
		data->active |= 0x80;
}


// [D] [T]
void RestoreCarPosition(SAVED_CAR_POS *data)
{
	REPLAY_STREAM* stream;
	STREAM_SOURCE* playerStart;

	if(!data->active)
		return;
	
	stream = &ReplayStreams[numPlayersToCreate];

	stream->InitialPadRecordBuffer = (PADRECORD*)ReplayStart;
	stream->PadRecordBuffer = (PADRECORD*)ReplayStart;
	stream->PadRecordBufferEnd = (PADRECORD*)ReplayStart;

	stream->playbackrun = 0;
	stream->length = 0;

	PlayerStartInfo[numPlayersToCreate] = &stream->SourceType;

	if (data->active & 0x80) 
	{
		memcpy((u_char*)PlayerStartInfo[numPlayersToCreate], (u_char*)PlayerStartInfo[0], sizeof(STREAM_SOURCE));

		// switch his car
		playerStart = PlayerStartInfo[numPlayersToCreate];

		playerStart->type = 3;
		playerStart->controlType = CONTROL_TYPE_CUTSCENE;

		// switch to first player
		playerStart = PlayerStartInfo[0];

		playerStart->type = 1;
		playerStart->model = data->model;
		playerStart->palette = data->palette;
		playerStart->position.vx = data->vx;
		playerStart->position.vy = data->vy;
		playerStart->position.vz = data->vz;
		playerStart->rotation = data->direction & 0xfff;
		playerStart->totaldamage = data->totaldamage;
		playerStart->damage[0] = data->damage[0];
		playerStart->damage[1] = data->damage[1];
		playerStart->damage[2] = data->damage[2];
		playerStart->damage[3] = data->damage[3];
		playerStart->damage[4] = data->damage[4];
		playerStart->damage[5] = data->damage[5];
	}
	else 
	{
		stream->SourceType.type = 1;
		stream->SourceType.model = data->model;
		stream->SourceType.palette = data->palette;
		stream->SourceType.position.vy = data->vy;
		stream->SourceType.position.vx = data->vx;
		stream->SourceType.position.vz = data->vz;
		stream->SourceType.rotation = data->direction & 0xfff;
		stream->SourceType.totaldamage = data->totaldamage;
		stream->SourceType.damage[0] = data->damage[0];
		stream->SourceType.damage[1] = data->damage[1];
		stream->SourceType.damage[2] = data->damage[2];
		stream->SourceType.damage[3] = data->damage[3];
		stream->SourceType.damage[4] = data->damage[4];
		stream->SourceType.damage[5] = data->damage[5];
	}
	numPlayersToCreate++;
}

// [D] [T]
void StoreEndData(void)
{
	int numStored;
	MS_TARGET* target;
	int i;
	SAVED_CAR_POS* carpos;

	ClearMem((char*)&MissionEndData, sizeof(MissionEndData));
	
	if (gCurrentMissionNumber > 40)
		return;

	numStored = 0;
	StorePlayerPosition(&MissionEndData.PlayerPos);

	for(i = 0; i < MAX_MISSION_TARGETS && numStored < 6; i++)
	{
		target = &MissionTargets[i];
		carpos = &MissionEndData.CarPos[numStored];

		if (target->type == Target_Car &&
			(target->s.target_flags & TARGET_FLAG_CAR_SAVED))
		{
			StoreCarPosition(target, carpos);

			if(carpos->active)
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
