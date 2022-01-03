#include "driver2.h"
#include "players.h"

#include "system.h"
#include "mission.h"
#include "civ_ai.h"
#include "cop_ai.h"
#include "pedest.h"
#include "cutscene.h"
#include "cars.h"
#include "glaunch.h"
#include "gamesnd.h"
#include "sound.h"
#include "felony.h"
#include "shadow.h"

PLAYER player[MAX_PLAYERS];

// [D] [T]
void InitPlayer(PLAYER *locPlayer, CAR_DATA *cp, char carCtrlType, int direction, LONGVECTOR4* startPos, int externModel, int palette, char *padid)
{
	int playerId;
	int model;
	u_int playerType;

	playerType = externModel & 0xFF;
	ClearMem((char *)locPlayer, sizeof(PLAYER));

	playerId = locPlayer - player;

	if (gStartOnFoot == 0 || carCtrlType == CONTROL_TYPE_LEAD_AI)
	{
		model = 0xFF;

		if (MissionHeader->residentModels[0] == playerType) 
			model = 0;
		else if(MissionHeader->residentModels[1] == playerType)
			model = 1;
		else if (MissionHeader->residentModels[2] == playerType)
			model = 2;
		else if (MissionHeader->residentModels[3] == playerType)
			model = 3;
		else if (MissionHeader->residentModels[4] == playerType)
			model = 4;

		InitCar(cp, direction, startPos, carCtrlType, model, palette & 0xff, &locPlayer->padid);

		ResetTyreTracks(cp, playerId);

		cp->controlFlags |= CONTROL_FLAG_WAS_PARKED | CONTROL_FLAG_PLAYER_START_CAR; // [A] car is owned by player
		
		locPlayer->worldCentreCarId = cp->id;
		locPlayer->cameraView = 0;// (NumPlayers == 2) << 1; // [A]
		locPlayer->playerCarId = cp->id;
		locPlayer->playerType = 1;
		locPlayer->spoolXZ = (VECTOR *)cp->hd.where.t;
		locPlayer->cameraCarId = cp->id;
		locPlayer->car_is_sounding = 0;
		
		locPlayer->pos[1] = cp->hd.where.t[1];
	}
	else 
	{
		LPPEDESTRIAN pPlayerPed;
		ActivatePlayerPedestrian(NULL, padid, direction, startPos, (PED_MODEL_TYPES)playerType);

		pPlayerPed = locPlayer->pPed;

		locPlayer->playerType = 2;
		locPlayer->spoolXZ = (VECTOR *)&pPlayerPed->position;
		locPlayer->playerCarId = -1;
		locPlayer->car_is_sounding = 2;
		locPlayer->cameraView = 0;
		
		locPlayer->pos[1] = -pPlayerPed->position.vy;
	}

	locPlayer->pos[0] = (*startPos)[0];
	locPlayer->pos[2] = (*startPos)[2];

	locPlayer->cameraAngle = 2048;
	locPlayer->headPos = 0;
	locPlayer->headTarget = 0;
	locPlayer->headTimer = 0;
	locPlayer->targetCarId = -1;
	locPlayer->car_sound_timer = -1;
	locPlayer->wheelnoise.chan = -1;
	locPlayer->wheelnoise.sound = -1;
	locPlayer->skidding.chan = -1;
	locPlayer->skidding.sound = -1;

	locPlayer->padid = *padid;
}

// [D] [T]
void ChangeCarPlayerToPed(int playerID)
{
	PLAYER* locPlayer;
	CAR_DATA* lcp;
	
	locPlayer = &player[playerID];
	lcp = &car_data[locPlayer->playerCarId];

	//my_sly_var = playerID;
	locPlayer->headTimer = 0;
	locPlayer->cameraView = 0;
	locPlayer->cameraAngle = (NoPlayerControl == 0) ? (lcp->hd.direction + 1536) : 4096;
	locPlayer->headTimer = 0;
	locPlayer->playerType = 2;
	locPlayer->headPos = 0;
	locPlayer->headTarget = 0;
	locPlayer->playerCarId = -1;
	locPlayer->cameraCarId = -1;
	locPlayer->targetCarId = -1;

	if (gInGameCutsceneActive == 0 && gInGameChaseActive == 0)
	{
		LPPEDESTRIAN pPlayerPed;
		pPlayerPed = locPlayer->pPed;

		locPlayer->worldCentreCarId = -1;
		locPlayer->spoolXZ = (VECTOR *)&pPlayerPed->position;
	}

	lcp->controlType = CONTROL_TYPE_CIV_AI;
	lcp->wheel_angle = 0;
	lcp->ai.c.thrustState = 3;
	lcp->ai.c.ctrlState = 7;

	// stop skidding for P1 or P2
	StopChannel(playerID != 0 ? 4 : 1);

	StopChannel(locPlayer->skidding.chan);
	UnlockChannel(locPlayer->skidding.chan);

	StopChannel(locPlayer->wheelnoise.chan);
	UnlockChannel(locPlayer->wheelnoise.chan);

	locPlayer->wheelnoise.chan = -1;
	locPlayer->wheelnoise.sound = -1;
	locPlayer->skidding.chan = -1;
	locPlayer->skidding.sound = -1;

	Start3DSoundVolPitch(-1, SOUND_BANK_TANNER, 3, lcp->hd.where.t[0], lcp->hd.where.t[1], lcp->hd.where.t[2], 0, 4096);

	first_offence = 1;

	if (CarHasSiren(lcp->ap.model))
		locPlayer->horn.on = 0;

	// [A] carry over felony from car to Tanner if cops see player
	// don't clear player felony in Destroy the Yard
	if (CopsCanSeePlayer || gCurrentMissionNumber == 30)
		pedestrianFelony = lcp->felonyRating;
	else
		pedestrianFelony = 0;
}

extern int lastCarCameraView;

// [D] [T]
void ChangePedPlayerToCar(int playerID, CAR_DATA *newCar)
{
	int carParked;

	PLAYER* lPlayer;

	lPlayer = &player[playerID];

	if (newCar->controlType == CONTROL_TYPE_CIV_AI && 
		newCar->ai.c.thrustState == 3 && (newCar->ai.c.ctrlState == 7 || newCar->ai.c.ctrlState == 5) || 
		newCar->controlType == CONTROL_TYPE_CUTSCENE)
	{
		carParked = 1;
	}
	else
	{
		carParked = 0;
	}

	lPlayer->playerType = 1;
	lPlayer->playerCarId = newCar->id;
	lPlayer->cameraCarId = newCar->id;

	if (gInGameCutsceneActive == 0 && gInGameChaseActive == 0)
	{
		lPlayer->spoolXZ = (VECTOR *)newCar->hd.where.t;
		lPlayer->worldCentreCarId = newCar->id;
	}

	lPlayer->cameraView = lastCarCameraView;

	if (NoPlayerControl == 0)
		lPlayer->cameraAngle = newCar->hd.direction + 1536;
	else
		lPlayer->cameraAngle = 4096;

	lPlayer->headPos = 0;
	lPlayer->headTarget = 0;
	lPlayer->headTimer = 0;
	lPlayer->pPed = NULL;

	// only allow non-cutscene players to get into cars
	if(lPlayer->padid >= 0)
	{
		newCar->controlType = CONTROL_TYPE_PLAYER;
		newCar->ai.padid = &lPlayer->padid;
		newCar->hndType = 0;

		if (playerID == 0 &&
			!(newCar->controlFlags & CONTROL_FLAG_PLAYER_START_CAR))	// [A] bug fix: don't give felony if player owns his cop car
		{
			// [A] Rev 1.1 removes felony override for "Steal the cop car"
			if (gCurrentMissionNumber != 32 && MissionHeader->residentModels[newCar->ap.model] == 0)
			{
				NoteFelony(&felonyData, 11, 4096);
			}
		}

		if (gCurrentMissionNumber == 33 && newCar->ap.model == 4)
		{
			makeLimoPullOver = 0;
		}

		StartPlayerCarSounds(playerID, newCar->ap.model, (VECTOR*)newCar->hd.where.t);

		if (carParked)
			RequestSlightPauseBeforeCarSoundStarts(playerID);
		else
			HaveCarSoundStraightAway(playerID);

		// [A] carry over felony from Tanner to car if cops see player. Force in Destroy the yard
		if (CopsCanSeePlayer || gCurrentMissionNumber == 30)
		{
			if (newCar->felonyRating < pedestrianFelony)
				newCar->felonyRating = pedestrianFelony;
		}
		else
			pedestrianFelony = 0;
	}

	// play door close sound
	Start3DSoundVolPitch(-1, SOUND_BANK_TANNER, 3, newCar->hd.where.t[0], newCar->hd.where.t[1], newCar->hd.where.t[2], 0, 0x1000);
}

// [D] [T]
void UpdatePlayers(void)
{
	int carId;
	PEDESTRIAN *ped;
	PLAYER *locPlayer;
	CAR_DATA* cp;

	if(CopsAllowed == 0)
		pedestrianFelony = 0;

	locPlayer = player;

	do {
		if (gInGameCutsceneActive == 0)
			locPlayer->playerType = (locPlayer->pPed != NULL) ? 2 : 1;

		if (locPlayer->playerType == 1)
		{
			carId = locPlayer->playerCarId;

			if(locPlayer->worldCentreCarId >= 0)
				locPlayer->spoolXZ = (VECTOR *)car_data[locPlayer->worldCentreCarId].hd.where.t;

			if (carId >= 0)
			{
				cp = &car_data[carId];
				
				locPlayer->pos[0] = cp->hd.where.t[0];
				locPlayer->pos[1] = cp->hd.where.t[1];
				locPlayer->pos[2] = cp->hd.where.t[2];
				locPlayer->dir = cp->hd.direction;
			}
		}
		else if (locPlayer->playerType == 2) 
		{
			ped = locPlayer->pPed;
			
			locPlayer->pos[0] = ped->position.vx;
			locPlayer->pos[1] = -ped->position.vy;
			locPlayer->pos[2] = ped->position.vz;
			locPlayer->dir = ped->dir.vy + -0x800;
		}

		locPlayer++;
	} while (locPlayer <= &player[7]);
}

// [D] [T]
void RequestSlightPauseBeforeCarSoundStarts(char player_id)
{
	player[player_id].car_is_sounding = 2;
	player[player_id].car_sound_timer = 10;
	player[player_id].idlevol = -10000;
	player[player_id].revsvol = -10000;
}

// [D] [T]
void HaveCarSoundStraightAway(char player_id)
{
	player[player_id].car_is_sounding = 0;
	player[player_id].car_sound_timer = -1;
}

// [D] [T]
void MakeTheCarShutUp(char player_id)
{
	player[player_id].car_is_sounding = 1;
	player[player_id].car_sound_timer = -1;
}





