#include "DRIVER2.H"
#include "PLAYERS.H"

#include "SYSTEM.H"
#include "MISSION.H"
#include "CIV_AI.H"
#include "COP_AI.H"
#include "PEDEST.H"
#include "CUTSCENE.H"
#include "CARS.H"
#include "GLAUNCH.H"
#include "GAMESND.H"
#include "SOUND.H"
#include "FELONY.H"

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

PEDESTRIAN *pPlayerPed = NULL;
_PLAYER player[8];

// [D] [T]
void InitPlayer(_PLAYER *locPlayer, _CAR_DATA *cp, char carCtrlType, int direction, long(*startPos)[4], int externModel, int palette, char *padid)
{
	int model;
	uint playerType;

	playerType = externModel & 0xFF;
	ClearMem((char *)locPlayer, sizeof(_PLAYER));

	if (gStartOnFoot == 0 || carCtrlType == 4)
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

		cp->controlFlags |= CONTROL_FLAG_WAS_PARKED;
		
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
		ActivatePlayerPedestrian(NULL, padid, direction, startPos, (PED_MODEL_TYPES)playerType);

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

// [D] [T]
void ChangeCarPlayerToPed(int playerID)
{
	_CAR_DATA *lcp = &car_data[player[playerID].playerCarId];

	//my_sly_var = playerID;
	player[playerID].headTimer = 0;
	player[playerID].cameraView = 0;
	player[playerID].cameraAngle = (NoPlayerControl == 0) ? (lcp->hd.direction + 1536) : 4096;
	player[playerID].headTimer = 0;
	player[playerID].playerType = 2;
	player[playerID].headPos = 0;
	player[playerID].headTarget = 0;
	player[playerID].playerCarId = -1;
	player[playerID].cameraCarId = -1;
	player[playerID].targetCarId = -1;

	if (gInGameCutsceneActive == 0 && gInGameChaseActive == 0)
	{
		player[playerID].worldCentreCarId = -1;
		player[playerID].spoolXZ = (VECTOR *)&pPlayerPed->position;
	}

	lcp->controlType = CONTROL_TYPE_CIV_AI;
	lcp->wheel_angle = 0;
	lcp->ai.c.thrustState = 3;
	lcp->ai.c.ctrlState = 7;

	// stop skidding for P1 or P2
	StopChannel(playerID != 0 ? 4 : 1);
	player[playerID].skidding.sound = -1;

	StopChannel(player[playerID].skidding.chan);
	UnlockChannel(player[playerID].skidding.chan);

	player[playerID].wheelnoise.sound = -1;

	StopChannel(player[playerID].wheelnoise.chan);
	UnlockChannel(player[playerID].wheelnoise.chan);

	Start3DSoundVolPitch(-1, 6, 3, lcp->hd.where.t[0], lcp->hd.where.t[1], lcp->hd.where.t[2], 0, 0x1000);

	first_offence = 1;

	if (CarHasSiren(lcp->ap.model) != 0)
		player[playerID].horn.on = 0;
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

extern int lastCarCameraView;

// [D] [T]
void ChangePedPlayerToCar(int playerID, _CAR_DATA *newCar)
{
	int carParked;
	int siren;
	int channel;
	int carSampleId;

	_PLAYER* lPlayer;

	lPlayer = &player[playerID];

	siren = CarHasSiren(newCar->ap.model);

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


	newCar->controlType = CONTROL_TYPE_PLAYER;
	newCar->ai.padid = &lPlayer->padid;
	newCar->hndType = 0;

	if (playerID == 0)
	{
		if (gCurrentMissionNumber != 32 && MissionHeader->residentModels[newCar->ap.model] == 0)
		{
			NoteFelony(&felonyData, 11, 4096);
		}
	}

	if (gCurrentMissionNumber == 33 && newCar->ap.model == 4) 
	{
		makeLimoPullOver = 0;
	}

	// door close sound
	Start3DSoundVolPitch(-1, 6, 3, newCar->hd.where.t[0], newCar->hd.where.t[1], newCar->hd.where.t[2], 0, 0x1000);

	if (newCar->ap.model == 4)
		carSampleId = ResidentModelsBodge();
	else if (newCar->ap.model < 3)
		carSampleId = newCar->ap.model;
	else
		carSampleId = newCar->ap.model - 1;

	// start idle sound
	channel = playerID == 0 ? 1 : 4;	
	Start3DSoundVolPitch(channel, 3, carSampleId * 3 + 1, newCar->hd.where.t[0], newCar->hd.where.t[1], newCar->hd.where.t[2], -10000, 0x1000);

	// rev sound
	channel = playerID == 0 ? 0 : 3;	
	Start3DSoundVolPitch(channel, 3, carSampleId * 3, newCar->hd.where.t[0], newCar->hd.where.t[1], newCar->hd.where.t[2], -10000, 0x1000);

	if (siren != 0) 
	{
		channel = playerID == 0 ? 2 : 5;
		Start3DSoundVolPitch(channel, (siren & 0xff00) >> 8, siren & 0xff, newCar->hd.where.t[0], newCar->hd.where.t[1], newCar->hd.where.t[2], -10000, 129);
	}

	if (carParked)
		RequestSlightPauseBeforeCarSoundStarts(playerID);
	else
		HaveCarSoundStraightAway(playerID);
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

// [D] [T]
void UpdatePlayers(void)
{
	int carId;
	PEDESTRIAN *ped;
	_PLAYER *locPlayer;
	_CAR_DATA* cp;

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

// [D] [T]
void RequestSlightPauseBeforeCarSoundStarts(char player_id)
{
	player[player_id].car_is_sounding = 2;
	player[player_id].car_sound_timer = 10;
	player[player_id].idlevol = -10000;
	player[player_id].revsvol = -10000;
}



// decompiled code
// original method signature: 
// void /*$ra*/ HaveCarSoundStraightAway(char player_id /*$a0*/)
 // line 305, offset 0x00073c54
	/* begin block 1 */
		// Start line: 960
	/* end block 1 */
	// End Line: 961

// [D] [T]
void HaveCarSoundStraightAway(char player_id)
{
	player[player_id].car_is_sounding = 0;
	player[player_id].car_sound_timer = -1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MakeTheCarShutUp(char player_id /*$a0*/)
 // line 310, offset 0x00073c8c
	/* begin block 1 */
		// Start line: 971
	/* end block 1 */
	// End Line: 972

// [D] [T]
void MakeTheCarShutUp(char player_id)
{
	player[player_id].car_is_sounding = 1;
	player[player_id].car_sound_timer = -1;
}





