#include "driver2.h"
#include "glaunch.h"

#include "system.h"
#include "main.h"
#include "E3stuff.h"
#include "pad.h"
#include "sound.h"
#include "replays.h"
#include "mission.h"
#include "gamesnd.h"
#include "camera.h"
#include "cutrecorder.h"
#include "fmvplay.h"
#include "state.h"
#include "xaplay.h"
#include "cutrecorder.h"

#include "Frontend/FEmain.h"

struct MISSION_STEP
{
	u_char flags : 3;
	u_char recap : 5;
	u_char data : 7;
	u_char disc : 1;
};

#define DML_FMV			1
#define DML_MISSION		2
#define DML_CREDITS		4
#define DML_RECAP		6

MISSION_STEP MissionLadder[] =
{
  { DML_FMV, 0, 1, 0 },
  { DML_FMV, 0, 2, 0 },
  { DML_MISSION, 0, 1, 0 },
  { DML_MISSION, 1, 2, 0 },
  { DML_MISSION, 1, 3, 0 },
  { DML_FMV, 1, 3, 0 },
  { DML_FMV, 1, 4, 0 },
  { DML_MISSION, 1, 4, 0 },
  { DML_FMV, 2, 5, 0 },
  { DML_MISSION, 2, 5, 0 },
  { DML_FMV, 3, 6, 0 },
  { DML_MISSION, 3, 6, 0 },
  { DML_FMV, 4, 7, 0 },
  { DML_MISSION, 5, 7, 0 },
  { DML_RECAP, 5, 0, 0 },
  { DML_MISSION, 5, 9, 0 },
  { DML_FMV, 5, 8, 0 },
  { DML_FMV, 5, 9, 0 },
  { DML_MISSION, 6, 10, 0 },
  { DML_FMV, 6, 10, 0 },
  { DML_FMV, 6, 11, 0 },
  { DML_MISSION, 7, 11, 0 },
  { DML_RECAP, 7, 0, 0 },
  { DML_MISSION, 7, 13, 0 },
  { DML_MISSION, 7, 14, 0 },
  { DML_FMV, 7, 12, 0 },
  { DML_MISSION, 8, 15, 0 },
  { DML_MISSION, 8, 16, 0 },
  { DML_FMV, 8, 13, 0 },
  { DML_MISSION, 9, 17, 0 },
  { DML_MISSION, 9, 18, 0 },
  { DML_FMV, 9, 14, 0 },
  { DML_MISSION, 10, 19, 0 },
  { DML_FMV, 10, 15, 0 },
  { DML_MISSION, 11, 20, 0 },
  { DML_FMV, 12, 16, 1 },
  { DML_FMV, 12, 17, 1 },
  { DML_MISSION, 13, 21, 1 },
  { DML_MISSION, 13, 22, 1 },
  { DML_MISSION, 13, 23, 1 },
  { DML_MISSION, 13, 24, 1 },
  { DML_FMV, 13, 18, 1 },
  { DML_MISSION, 14, 25, 1 },
  { DML_MISSION, 14, 26, 1 },
  { DML_FMV, 14, 19, 1 },
  { DML_MISSION, 15, 27, 1 },
  { DML_MISSION, 15, 28, 1 },
  { DML_MISSION, 15, 29, 1 },
  { DML_MISSION, 15, 30, 1 },
  { DML_FMV, 15, 20, 1 },
  { DML_FMV, 15, 21, 1 },
  { DML_MISSION, 16, 31, 1 },
  { DML_MISSION, 16, 32, 1 },
  { DML_MISSION, 16, 33, 1 },
  { DML_MISSION, 16, 34, 1 },
  { DML_FMV, 16, 22, 1 },
  { DML_MISSION, 17, 35, 1 },
  { DML_RECAP, 17, 0, 1 },
  { DML_MISSION, 17, 37, 1 },
  { DML_FMV, 17, 23, 1 },
  { DML_MISSION, 18, 38, 1 },
  { DML_MISSION, 18, 39, 1 },
  { DML_FMV, 18, 24, 1 },
  { DML_MISSION, 19, 40, 1 },
  { DML_FMV, 19, 25, 1 },
  { DML_FMV, 19, 26, 1 },
  { DML_FMV, 19, 27, 1 },
  { DML_CREDITS, 19, 28, 1 }
};

unsigned short RecapFrameLength[19] = {
	515, 764, 962, 1174, 1389, 1558, 1748,
	1806, 2048, 2253, 2458, 1072, 1360,
	1507, 1659, 2413, 2583, 2761, 2998
};

ACTIVE_CHEATS AvailableCheats = { 0 };
ACTIVE_CHEATS ActiveCheats = { 0 };

int gInFrontend = 0;
int AttractMode = 0;

int gLoadedReplay = 0;
int gHaveStoredData = 0;

int gHaveExtraData = 0;

EXTRA_CONFIG_DATA gExtraConfig = { 0 };
SAVED_CAR_POS gSavedCars[2] = { 0 };

int gLastChase = 0;
int gChaseNumber = 0;
int gRandomChase = 0;
int gSubGameNumber = 0;

int gMissionLadderPos = 0;
int gFurthestMission = 0;

int gWantNight = 0;

int gOldVibrationMode;
int gSurvivalCopSettingsBackup;
ACTIVE_CHEATS gCheatsBackup;
EXTRA_CONFIG_DATA gExtraConfigBackup;

int vars_stored = 0;

void RestoreGameVars(int replay)
{
	if (vars_stored)
	{
		if (replay == 0)
		{
#ifdef DEBUG
			printInfo("**** Restoring game vars ****\n");
#endif
			gVibration = gOldVibrationMode;
			gCopDifficultyLevel = gSurvivalCopSettingsBackup;
			ActiveCheats = gCheatsBackup;

			vars_stored = 0;
		}
#ifdef DEBUG
		printInfo("**** Restoring extra data ****\n");
#endif
		gExtraConfig = gExtraConfigBackup;
		gHaveExtraData = (gExtraConfig.magic == EXTRA_DATA_MAGIC);
	}
}

void StoreGameVars(int replay)
{
	if (!vars_stored)
	{
#ifdef DEBUG
		printInfo("**** Backing up game vars (replay=%d) ****\n", replay);
#endif
		gOldVibrationMode = gVibration;
		gSurvivalCopSettingsBackup = gCopDifficultyLevel;
		gCheatsBackup = ActiveCheats;
		gExtraConfigBackup = gExtraConfig;

		vars_stored = 1;
	}

	if (replay != 0)
	{
		// clear all extra config data:
		// - any zero value means 'do backwards compatiblity'
		// - ensures older replays are fully backwards compatible
		// - newer replays always have this data stored (even if empty)
		memset(&gExtraConfig, 0, sizeof(EXTRA_CONFIG_DATA));
		gHaveExtraData = 0;

		// clear saved cars
		memset(&gSavedCars, 0, sizeof(gSavedCars));
	}
}

void LoadExtraData(EXTRA_CONFIG_DATA *extraData, int profile)
{
	if (extraData->magic == EXTRA_DATA_MAGIC)
	{
		memcpy(&gExtraConfig, extraData, sizeof(EXTRA_CONFIG_DATA));
		gHaveExtraData = 1;
	}

	if (profile)
	{
		if (gExtraConfig.sdType == 1)
		{
			// TODO: load profile overrides
		}

		// clear the data since we're done with it
		memset(&gExtraConfig.data, 0, sizeof(gExtraConfig.data));

		// initialize extra data for missions
		gExtraConfig.sdType = 2;
		gExtraConfig.m.AllowParkedTurnedWheels = 1;
	}
	else if (gExtraConfig.sdType == 2)
	{
		// load mission overrides
		REPLAY_SAVE_HEADER *header = (REPLAY_SAVE_HEADER*)((char*)&extraData[1] - sizeof(REPLAY_SAVE_HEADER));

		// resolve saved position slots
		for (int i = 0; i < 2; i++)
		{
			if (extraData->m.SavedSlot[i] != -1)
			{
				gSavedCars[i] = header->SavedData.CarPos[extraData->m.SavedSlot[i]];

				gExtraConfig.m.SavedPos[i] = &gSavedCars[i];
			}
			else
			{
				gExtraConfig.m.SavedPos[i] = NULL;
			}
		}
	}
	else if (gExtraConfig.sdType != 0)
	{
		// clear out invalid data
		gExtraConfig.cookie = 0;
		memset(&gExtraConfig.data, 0, sizeof(extraData->data));
	}
}

void SaveExtraData(EXTRA_CONFIG_DATA *extraData, int profile)
{
	// always save extra data, even if it's empty;
	// this will make future backwards compat. efforts easier ;)
	memcpy(extraData, &gExtraConfig, sizeof(EXTRA_CONFIG_DATA));
	extraData->magic = EXTRA_DATA_MAGIC;

	int invalid = 0;

	if (profile)
	{
		if (extraData->sdType != 1)
		{
			// don't save non-profile data
			invalid = 1;
		}
	}
	else if (extraData->sdType == 2)
	{
		REPLAY_SAVE_HEADER *header = (REPLAY_SAVE_HEADER*)((char*)&extraData[1] - sizeof(REPLAY_SAVE_HEADER));

		if (extraData->mfStartPos)
		{
			int slot = 0;

			if (header->HaveStoredData != 0)
			{
				do
				{
					// find first free slot
					if (!header->SavedData.CarPos[slot].active)
						break;
				} while (++slot < 6);
			}

			// fixup pointers; store info in first free saved car slot
			// if no free slots are available, well.. sorry!
			for (int i = 0; i < 2; i++)
			{
				if (extraData->m.SavedPos[i] == NULL)
				{
					extraData->m.SavedSlot[i] = -1;
					continue;
				}

				if (slot >= 6)
				{
					printWarning("Couldn't save player %d start position - no more slots available!\n", i + 1);
					continue;
				}

				header->SavedData.CarPos[slot] = *extraData->m.SavedPos[i];
				extraData->m.SavedSlot[i] = slot++;
			}
		}
	}
	else
	{
		// don't save non-mission data
		invalid = 1;
	}

	if (invalid)
	{
		// clear out invalid data
		extraData->cookie = 0;
		memset(&extraData->data, 0, sizeof(extraData->data));
	}
}

int GetSavedCar(STREAM_SOURCE *player, int slot)
{
	if (slot > 1 || !gExtraConfig.mfStartPos)
		return -1;

	if (gExtraConfig.m.SavedPos[slot] == NULL)
		return 0;

	player->model = gExtraConfig.m.SavedPos[slot]->model;
	player->palette = gExtraConfig.m.SavedPos[slot]->palette;
	player->rotation = gExtraConfig.m.SavedPos[slot]->direction & 0xfff;
	player->position.vx = gExtraConfig.m.SavedPos[slot]->vx;
	player->position.vz = gExtraConfig.m.SavedPos[slot]->vz;

	return 1;
}

int SetSavedCar(int slot, STREAM_SOURCE *player)
{
	if (slot > 1)
		return -1;

	if (gExtraConfig.m.SavedPos[slot] == NULL)
	{
		gExtraConfig.mfStartPos = 1;
		gExtraConfig.m.SavedPos[slot] = &gSavedCars[slot];
	}

	gExtraConfig.m.SavedPos[slot]->model = player->model;
	gExtraConfig.m.SavedPos[slot]->palette = player->palette;
	gExtraConfig.m.SavedPos[slot]->direction = player->rotation & 0xfff;
	gExtraConfig.m.SavedPos[slot]->vx = player->position.vx;
	gExtraConfig.m.SavedPos[slot]->vz = player->position.vz;

	return 1;
}

int SavePlayerCarSpawn(int slot)
{
	if (slot > 1)
		return -1;

	if (gExtraConfig.m.SavedPos[slot] == NULL)
	{
		gExtraConfig.mfStartPos = 1;
		gExtraConfig.m.SavedPos[slot] = &gSavedCars[slot];
	}

	extern PLAYER player[];
	extern CAR_DATA car_data[];

	PLAYER *plr = &player[slot];

	if (plr->cameraCarId == -1)
		return 0;

	CAR_DATA *lcp = &car_data[plr->cameraCarId];

	gExtraConfig.m.SavedPos[slot]->direction = lcp->hd.direction & 0xfff;
	gExtraConfig.m.SavedPos[slot]->vx = lcp->hd.where.t[0];
	gExtraConfig.m.SavedPos[slot]->vz = lcp->hd.where.t[2];

	return 1;
}

extern int ResetPlayerCarSpawn(int slot)
{
	if (slot > 1)
		return -1;

	if (gExtraConfig.m.SavedPos[slot] != NULL)
	{
		gExtraConfig.m.SavedPos[slot] = NULL;
		gExtraConfig.mfStartPos = gExtraConfig.m.SavedPos[slot ^ 1] != NULL;
	}

	return 1;
}

// [D] [T]
void State_GameStart(void* param)
{
	if (GameType != GAME_CONTINUEMISSION &&
		GameType != GAME_MISSION &&
		GameType != GAME_REPLAYMISSION)
	{
		SetPleaseWait(NULL);
	}

	DrawSync(0);
	VSync(0);

	FreeXM();
	SsSetSerialVol(0, 0, 0);
	
	gInFrontend = 0;
	AttractMode = 0;
	NewLevel = 1;

	StoreGameVars(0);

	switch (GameType)
	{
		case GAME_MISSION:
			RunMissionLadder(1);
			break;
		case GAME_TAKEADRIVE:

			if (NumPlayers == 1)
				gCurrentMissionNumber = 50;
			else
				gCurrentMissionNumber = 58;

			gCurrentMissionNumber += GameLevel * 2 + gWantNight + gSubGameNumber * 440;

			SetState(STATE_GAMELAUNCH);
		
			break;
		case GAME_IDLEDEMO:
			if (LoadAttractReplay(gCurrentMissionNumber))
			{
				gVibration = 0;
				CurrentGameMode = GAMEMODE_DEMO;
				gLoadedReplay = 1;

				SetState(STATE_GAMELAUNCH);
			}

			break;
		case GAME_PURSUIT:
			gCurrentMissionNumber = 70 + GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			SetState(STATE_GAMELAUNCH);

			break;
		case GAME_GETAWAY:
			gCurrentMissionNumber = 102 + GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			SetState(STATE_GAMELAUNCH);

			break;
		case GAME_GATERACE:
			if (NumPlayers == 1)
				gCurrentMissionNumber = 134;
			else
				gCurrentMissionNumber = 164;

			gCurrentMissionNumber += GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			SetState(STATE_GAMELAUNCH);
		
			break;
		case GAME_CHECKPOINT:
			if (NumPlayers == 1)
				gCurrentMissionNumber = 196;
			else
				gCurrentMissionNumber = 228;

			gCurrentMissionNumber += GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			SetState(STATE_GAMELAUNCH);

			break;
		case GAME_TRAILBLAZER:
			gCurrentMissionNumber = GameLevel * 8 + 260 + gWantNight * 4 + gSubGameNumber;
			SetState(STATE_GAMELAUNCH);

			break;
		case GAME_SURVIVAL:
			gCopDifficultyLevel = 2;

			if (NumPlayers == 1)
				gCurrentMissionNumber = 292;
			else
				gCurrentMissionNumber = 324;

			gCurrentMissionNumber += GameLevel * 8 + gWantNight * 4 + gSubGameNumber;

			SetState(STATE_GAMELAUNCH);
			break;
		case GAME_REPLAYMISSION:
			GameType = GAME_MISSION;

			if (FindMissionLadderPos(gCurrentMissionNumber))
				RunMissionLadder(0);

			//GameType = GAME_REPLAYMISSION;

			break;
		case GAME_COPSANDROBBERS:
			gCurrentMissionNumber = 420 + GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			SetState(STATE_GAMELAUNCH);

			break;
		case GAME_CAPTURETHEFLAG:
			gCurrentMissionNumber = 352 + GameLevel * 8 + gSubGameNumber;
			SetState(STATE_GAMELAUNCH);

			break;
		case GAME_SECRET:
			if (NumPlayers == 1)
				gCurrentMissionNumber = 480;
			else
				gCurrentMissionNumber = 484;

			gCurrentMissionNumber += gWantNight + gSubGameNumber;
			SetState(STATE_GAMELAUNCH);

			break;
		case GAME_CONTINUEMISSION:
			GameType = GAME_MISSION;
			RunMissionLadder(0);

			break;
		case GAME_LOADEDREPLAY:
			CurrentGameMode = GAMEMODE_DIRECTOR;
			gLoadedReplay = 1;
			GameType = StoredGameType;

			SetState(STATE_GAMELAUNCH);
		
			break;
	}
}

void State_InitFrontEnd(void* param)
{
	if ((int)param == 2)
	{
		InitFrontend();
		InitFrontendDisplay();
	}
	else
	{
		ReInitFrontend((int)param == 0);
	}

	SetState(STATE_FRONTEND);
}

// [D] [T]
void State_FMVPlay(void* param)
{
	PlayFMV((int)param);
	SetState(STATE_INITFRONTEND, (void*)1);
}

// [D] [T]
void ReInitFrontend(int returnToMain)
{
	RECT16 rect;

	old_camera_change = 0;
	camera_change = 0;

	wantedCar[1] = -1;
	wantedCar[0] = -1;

	wantedWeather = -1;
	wantedTimeOfDay = -1;

	gHaveStoredData = 0;

	EnableDisplay();
	DrawSync(0);
	VSync(0);

	gInFrontend = 1;

	SetDispMask(0);

	StopDualShockMotors();
	FreeXM();

	SpuSetReverbVoice(0, SPU_ALLCH);
	UnPauseSound();

	LoadSoundBankDynamic((char*)0x0, 0, 0);
	LoadBankFromLump(1, 0);
	
	// load frontend
	LOAD_OVERLAY("FRONTEND.BIN", _overlay_buffer);

	// switch to state STATE_INITFRONTEND

	SetFEDrawMode();
	DrawSync(0);
	EnableDisplay();

	setRECT(&rect, 0, 0, 320, 512);
	ClearImage(&rect, 0, 0, 0);

	DrawSync(0);

	LoadFrontendScreens(1);
	ReInitScreens(returnToMain);
	
	DrawSync(0);
	VSync(0);

	ClearOTagR((u_long*)MPBuff[0][0].ot, OTSIZE);
	ClearOTagR((u_long*)MPBuff[0][1].ot, OTSIZE);

	SetDispMask(1);

	bRedrawFrontend = 1;
}

void State_MissionLadder(void* param)
{
	int quit;
	int newgame;
	MISSION_STEP* CurrentStep;
	RENDER_ARGS RenderArgs;

	newgame = (int)param;
	quit = 0;

	RenderArgs.nRenders = 0;
	CurrentStep = &MissionLadder[gMissionLadderPos];

	if (newgame == 0 && CurrentStep->flags != 0)
	{
		RenderArgs.Args[0].render = 97;

		if (CurrentStep->recap > 11)
			RenderArgs.Args[0].render = 98;

		RenderArgs.Args[0].credits = 0;
		RenderArgs.Args[0].recap = RecapFrameLength[CurrentStep->recap - 1];

		RenderArgs.nRenders = 1;
	}

	do {
		CheckForCorrectDisc(CurrentStep->disc);

		if (RenderArgs.nRenders == 4)
		{
			SetPleaseWait(NULL);
			
			PlayRender(&RenderArgs);
			RenderArgs.nRenders = 0;
			
			SetPleaseWait(NULL);
		}

		if (CurrentStep->flags == DML_MISSION)
		{
			if (RenderArgs.nRenders != 0)
			{
				SetPleaseWait(NULL);
				PlayRender(&RenderArgs);
				RenderArgs.nRenders = 0;
			}

			SetPleaseWait(NULL);
			
			gCurrentMissionNumber = CurrentStep->data;
			SetState(STATE_GAMELAUNCH);
			
			quit = 1;
		}
		else if (CurrentStep->flags == DML_FMV) // any render
		{
			RenderArgs.Args[RenderArgs.nRenders].render = CurrentStep->data;
			RenderArgs.Args[RenderArgs.nRenders].recap = 0;
			RenderArgs.Args[RenderArgs.nRenders].credits = 0;
			RenderArgs.nRenders++;
		}
		else if (CurrentStep->flags == DML_CREDITS) // ending
		{
			SetPleaseWait(NULL);

			RenderArgs.Args[RenderArgs.nRenders].render = CurrentStep->data;
			RenderArgs.Args[RenderArgs.nRenders].recap = 0;
			RenderArgs.Args[RenderArgs.nRenders].credits = 1;
			RenderArgs.nRenders++;

			PlayRender(&RenderArgs);

			SetPleaseWait(NULL);
			AvailableCheats.cheat5 = true;
			
			SetState(STATE_INITFRONTEND);

			quit = 1;
		}
		
		CurrentStep++;
		gMissionLadderPos = CurrentStep - MissionLadder;
	} while (!quit);
}

// [D] [T]
void RunMissionLadder(int newgame)
{
	if (newgame)
		gMissionLadderPos = 0;
	
	SetState(STATE_LADDER, (void*)newgame);
}

// [D] [T]
void GetRandomChase(void)
{
	int bump;

	// [A] debug
	if (gChaseNumber != 0)
	{
		gRandomChase = gChaseNumber;
		return;
	}

	if (gLoadedReplay == 0)
	{
		gRandomChase = VSync(-1) % 13 + 2;

		bump = 0;

		while (gRandomChase == gLastChase)
		{
			gRandomChase = (VSync(-1) + bump) % 13 + 2;
			bump++;
		}

		gLastChase = gRandomChase;
	}
}

// [D] [T]
int FindPrevMissionFromLadderPos(int pos)
{
	MISSION_STEP* step = &MissionLadder[pos];
	while (pos-- > 0)
	{
		if (step->flags == 2)
		{
			int mission = step->data;

			if (gFurthestMission < mission)
				gFurthestMission = mission;

			return 1;
		}

		step--;
	}

	return 0;
}

int gMissionCompletionState = 0;
char NoPlayerControl = 0;

// TODO: REPLAYS.C
int quick_replay = 0;
int AutoDirect = 0;
int lead_car = 0;

MISSION_DATA MissionStartData;
MISSION_DATA MissionEndData;

// [D] [T]
void State_LaunchGame(void* param)
{
	int quit;
	
	// STATE_GAMELAUNCH
	
	ResetGraph(1);
	SetVideoMode(video_mode);

	gMissionCompletionState = PAUSEMODE_GAMEOVER;

	gInvincibleCar = ActiveCheats.cheat3;
	gPlayerImmune = ActiveCheats.cheat4;

	quick_replay = 0;

	if (gLoadedReplay == 0)
		GetRandomChase();

	if (CurrentGameMode == GAMEMODE_DIRECTOR)
	{
		AttractMode = 0;
		NoPlayerControl = 1;
	}
	else if (CurrentGameMode == GAMEMODE_REPLAY)
	{
		AttractMode = 0;
		NoPlayerControl = 1;
		quick_replay = 1;
	}
	else if (CurrentGameMode == GAMEMODE_DEMO)
	{
		AttractMode = 1;
		NoPlayerControl = 1;
	}
	else
	{
		AttractMode = 0;
		NoPlayerControl = 0;
	}

	AutoDirect = 0;
	NewLevel = 1;

	// switch to STATE_GAMEINIT
	SetState(STATE_GAMEINIT);
}

// [A] state function
void State_GameComplete(void* param)
{
	GameStates nextState;
	int stateParam;
	RECT16 rect;

	if (NoPlayerControl == 0)
	{
		ReplayParameterPtr->RecordingEnd = CameraCnt;
	}

	StopPadVibration(0);
	StopPadVibration(1);
	StopAllChannels();
	FreeXM();

	if (XAPrepared())
	{
		StopXA();
		UnprepareXA();
	}

	// restart is default
	nextState = STATE_GAMEINIT;
	stateParam = 0;

	switch (WantedGameMode)
	{
		case GAMEMODE_NORMAL:
		case GAMEMODE_QUIT:
		case GAMEMODE_DEMO:
		{
			FadeScreen(255);
			nextState = STATE_INITFRONTEND;
			break;
		}
		case GAMEMODE_RESTART:
		{
			FadeScreen(255);

			NoPlayerControl = 0;
			quick_replay = 0;
			AutoDirect = 0;
			WantedGameMode = GAMEMODE_NORMAL;
			NewLevel = 0;

			GetRandomChase();

			break;
		}
		case GAMEMODE_REPLAY:
		case GAMEMODE_DIRECTOR:
		{
			if (CurrentGameMode < GAMEMODE_NEXTMISSION)
				FadeScreen(255);

			NoPlayerControl = 1;
			AutoDirect = (WantedGameMode == GAMEMODE_REPLAY);
			quick_replay = (WantedGameMode == GAMEMODE_REPLAY);
			NewLevel = 0;
			break;
		}
		case GAMEMODE_NEXTMISSION:
		{
			MissionStartData = MissionEndData;
			gHaveStoredData = 1;

			FadeScreen(255);

			if(GameType == GAME_MISSION)
			{
				nextState = STATE_LADDER;
				stateParam = 2; // don't do recap
			}
			else
				nextState = STATE_INITFRONTEND;
			
			NoPlayerControl = 0;
			quick_replay = 0;
			AutoDirect = 0;
		}
	}
	
	CurrentGameMode = WantedGameMode;

	SetState(nextState, (void*)stateParam);

	if(nextState == STATE_INITFRONTEND)
	{
		_CutRec_Reset();

		gLoadedReplay = 0;

		RestoreGameVars(0);
		
		lead_car = 0;
		NoPlayerControl = 0;
		
		SetDispMask(0);
		EnableDisplay();

		setRECT(&rect, 0, 0, 512, 512);

		ClearImage(&rect, 0, 0, 0);

		DrawSync(0);
		SetDispMask(1);
	}

#ifndef PSX
	// set to 60 FPS VSync
	PsyX_SetSwapInterval(1);
	PsyX_EnableSwapInterval(1);
#endif
}

// [D] [T]
int FindMissionLadderPos(int mission)
{
	MISSION_STEP* step = MissionLadder;
	int pos = 0;
	bool end = false;

	do {
		switch (step->flags)
		{
			case 1:
			case 6:
			{
				step++;
				pos++;
				break;
			}
			case 2:
			{
				if (step->data == mission)
				{
					if (pos > 0)
					{
						step--;

						while (step->flags != 2)
						{
							if (--pos <= 0)
								break;

							step--;
						}
					}

					gMissionLadderPos = pos;
					return 1;
				}

				step++;
				pos++;
				break;
			}
			case 4:
				// end of ladder
				end = true;
				break;
			default:
				// unhandled
				return 0;
		}
	} while (!end);

	return 0;
}