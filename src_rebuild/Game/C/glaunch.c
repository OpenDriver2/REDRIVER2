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
#include "fmvplay.h"
#include "Frontend/FEmain.h"


#include "LIBETC.H"
#include "STRINGS.H"

MISSION_STEP MissionLadder[68] =
{
  { 1, 0, 1, 0 },
  { 1, 0, 2, 0 },
  { 2, 0, 1, 0 },
  { 2, 1, 2, 0 },
  { 2, 1, 3, 0 },
  { 1, 1, 3, 0 },
  { 1, 1, 4, 0 },
  { 2, 1, 4, 0 },
  { 1, 2, 5, 0 },
  { 2, 2, 5, 0 },
  { 1, 3, 6, 0 },
  { 2, 3, 6, 0 },
  { 1, 4, 7, 0 },
  { 2, 5, 7, 0 },
  { 6, 5, 0, 0 },
  { 2, 5, 9, 0 },
  { 1, 5, 8, 0 },
  { 1, 5, 9, 0 },
  { 2, 6, 10, 0 },
  { 1, 6, 10, 0 },
  { 1, 6, 11, 0 },
  { 2, 7, 11, 0 },
  { 6, 7, 0, 0 },
  { 2, 7, 13, 0 },
  { 2, 7, 14, 0 },
  { 1, 7, 12, 0 },
  { 2, 8, 15, 0 },
  { 2, 8, 16, 0 },
  { 1, 8, 13, 0 },
  { 2, 9, 17, 0 },
  { 2, 9, 18, 0 },
  { 1, 9, 14, 0 },
  { 2, 10, 19, 0 },
  { 1, 10, 15, 0 },
  { 2, 11, 20, 0 },
  { 1, 12, 16, 1 },
  { 1, 12, 17, 1 },
  { 2, 13, 21, 1 },
  { 2, 13, 22, 1 },
  { 2, 13, 23, 1 },
  { 2, 13, 24, 1 },
  { 1, 13, 18, 1 },
  { 2, 14, 25, 1 },
  { 2, 14, 26, 1 },
  { 1, 14, 19, 1 },
  { 2, 15, 27, 1 },
  { 2, 15, 28, 1 },
  { 2, 15, 29, 1 },
  { 2, 15, 30, 1 },
  { 1, 15, 20, 1 },
  { 1, 15, 21, 1 },
  { 2, 16, 31, 1 },
  { 2, 16, 32, 1 },
  { 2, 16, 33, 1 },
  { 2, 16, 34, 1 },
  { 1, 16, 22, 1 },
  { 2, 17, 35, 1 },
  { 6, 17, 0, 1 },
  { 2, 17, 37, 1 },
  { 1, 17, 23, 1 },
  { 2, 18, 38, 1 },
  { 2, 18, 39, 1 },
  { 1, 18, 24, 1 },
  { 2, 19, 40, 1 },
  { 1, 19, 25, 1 },
  { 1, 19, 26, 1 },
  { 1, 19, 27, 1 },
  { 4, 19, 28, 1 }
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

int gLastChase = 0;
int gChaseNumber = 0;
int gRandomChase = 0;
int gSubGameNumber = 0;

int gMissionLadderPos = 0;
int gFurthestMission = 0;

int gWantNight = 0;

// [D] [T]
void GameStart(void)
{
	int oldVibrationMode;
	int SurvivalCopSettingsBackup;

	if (GameType != GAME_CONTINUEMISSION &&
		GameType != GAME_MISSION &&
		GameType != GAME_REPLAYMISSION)
	{
		SetPleaseWait(NULL);
	}

	DrawSync(0);
	VSync(0);

	gInFrontend = 0;
	AttractMode = 0;

	FreeXM();

	SsSetSerialVol(0, 0, 0);

	SurvivalCopSettingsBackup = gCopDifficultyLevel;
	NewLevel = 1;

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

			LaunchGame();
			break;
		case GAME_IDLEDEMO:
			oldVibrationMode = gVibration;

			if (LoadAttractReplay(gCurrentMissionNumber))
			{
				gVibration = 0;
				CurrentGameMode = GAMEMODE_DEMO;
				gLoadedReplay = 1;

				LaunchGame();

				gLoadedReplay = 0;
				gVibration = oldVibrationMode;
			}

			break;
		case GAME_PURSUIT:
			gCurrentMissionNumber = 70 + GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();

			break;
		case GAME_GETAWAY:
			gCurrentMissionNumber = 102 + GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();

			break;
		case GAME_GATERACE:
			if (NumPlayers == 1)
				gCurrentMissionNumber = 134;
			else
				gCurrentMissionNumber = 164;

			gCurrentMissionNumber += GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();
			break;
		case GAME_CHECKPOINT:
			if (NumPlayers == 1)
				gCurrentMissionNumber = 196;
			else
				gCurrentMissionNumber = 228;

			gCurrentMissionNumber += GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();

			break;
		case GAME_TRAILBLAZER:
			gCurrentMissionNumber = GameLevel * 8 + 260 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();

			break;
		case GAME_SURVIVAL:
			gCopDifficultyLevel = 2;

			if (NumPlayers == 1)
				gCurrentMissionNumber = 292;
			else
				gCurrentMissionNumber = 324;

			gCurrentMissionNumber += GameLevel * 8 + gWantNight * 4 + gSubGameNumber;

			LaunchGame();

			gCopDifficultyLevel = SurvivalCopSettingsBackup;

			break;
		case GAME_REPLAYMISSION:
			GameType = GAME_MISSION;

			if (FindMissionLadderPos(gCurrentMissionNumber) != 0)
				RunMissionLadder(0);

			GameType = GAME_REPLAYMISSION;

			break;
		case GAME_COPSANDROBBERS:
			gCurrentMissionNumber = 420 + GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();

			break;
		case GAME_CAPTURETHEFLAG:
			gCurrentMissionNumber = 352 + GameLevel * 8 + gSubGameNumber;
			LaunchGame();

			break;
		case GAME_SECRET:
			if (NumPlayers == 1)
				gCurrentMissionNumber = 480;
			else
				gCurrentMissionNumber = 484;

			gCurrentMissionNumber += gWantNight + gSubGameNumber;
			LaunchGame();

			break;
		case GAME_CONTINUEMISSION:
			GameType = GAME_MISSION;
			RunMissionLadder(0);

			break;
		case GAME_LOADEDREPLAY:
			CurrentGameMode = GAMEMODE_DIRECTOR;
			gLoadedReplay = 1;
			GameType = StoredGameType;

			LaunchGame();

			gLoadedReplay = 0;

			break;
	}

	wantedCar[1] = -1;
	wantedCar[0] = -1;
	// [A]
	wantedWeather = -1;
	wantedTimeOfDay = -1;

	gHaveStoredData = 0;

	ReInitFrontend();
}


// [D] [T]
void StartRender(int renderNum)
{
	PlayFMV(renderNum);
	ReInitFrontend();
}

// [D] [T]
void ReInitFrontend(void)
{
	RECT16 rect;

	old_camera_change = 0;
	camera_change = 0;

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

#ifdef PSX
	Loadfile("FRONTEND.BIN", 0x801C0000);
#endif // PSX

	SetFEDrawMode();
	DrawSync(0);
	EnableDisplay();

	setRECT(&rect, 0, 0, 320, 512);
	ClearImage(&rect, 0, 0, 0);

	DrawSync(0);
	LoadFrontendScreens(1);
	ReInitScreens();
	DrawSync(0);
	VSync(0);

	ClearOTagR((u_long*)MPBuff[0][0].ot, OTSIZE);
	ClearOTagR((u_long*)MPBuff[0][1].ot, OTSIZE);

	SetDispMask(1);

	//LoadedLevel = 0xff;
	bRedrawFrontend = 1;
}

// [D] [T]
void RunMissionLadder(int newgame)
{
	bool quit;
	MISSION_STEP* CurrentStep;
	RENDER_ARGS RenderArgs;

	quit = false;
	if (newgame != 0)
		gMissionLadderPos = 0;

	RenderArgs.nRenders = 0;
	CurrentStep = MissionLadder + gMissionLadderPos;

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
		if (CurrentStep->disc == 0)
		{
			CheckForCorrectDisc(0);
		}
		else
		{
#ifndef PSX
			extern int gImitateDiscSwap;
			extern int gImitateDiscSwapFrames;
			if (gImitateDiscSwap != -1)
			{
				gImitateDiscSwapFrames = VSync(-1);
				gImitateDiscSwap = 1;
			}
#endif
			CheckForCorrectDisc(1);
		}

		if (RenderArgs.nRenders == 4)
		{
			SetPleaseWait(NULL);
			PlayRender(&RenderArgs);
			RenderArgs.nRenders = 0;
			SetPleaseWait(NULL);
		}

		gMissionLadderPos = CurrentStep - MissionLadder;

		if (CurrentStep->flags == 2)
		{
			if (RenderArgs.nRenders != 0)
			{
				SetPleaseWait(NULL);
				PlayRender(&RenderArgs);
				RenderArgs.nRenders = 0;
			}

			SetPleaseWait(NULL);
			gCurrentMissionNumber = CurrentStep->data;
			LaunchGame();

			if (WantedGameMode == GAMEMODE_NEXTMISSION)
			{
				if (gFurthestMission < gCurrentMissionNumber)
					gFurthestMission = gCurrentMissionNumber;
			}
			else
			{
				quit = true;
			}
		}
		else if (CurrentStep->flags == 1)
		{
			RenderArgs.Args[RenderArgs.nRenders].render = CurrentStep->data;
			RenderArgs.Args[RenderArgs.nRenders].recap = 0;
			RenderArgs.Args[RenderArgs.nRenders].credits = 0;
			RenderArgs.nRenders++;
		}
		else if (CurrentStep->flags == 4)
		{
			SetPleaseWait(NULL);

			RenderArgs.Args[RenderArgs.nRenders].render = CurrentStep->data;
			RenderArgs.Args[RenderArgs.nRenders].recap = 0;
			RenderArgs.Args[RenderArgs.nRenders].credits = 1;
			RenderArgs.nRenders++;

			PlayRender(&RenderArgs);

			SetPleaseWait(NULL);

			quit = true;
			AvailableCheats.cheat5 = true;
		}

		CurrentStep++;
	} while (!quit);
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
		gRandomChase = VSync(-1) % 0xd + 2;

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

int fakeOtherPlayer = 0;
int gMissionCompletionState = 0;
char NoPlayerControl = 0;

// TODO: REPLAYS.C
int quick_replay = 0;
int AutoDirect = 0;
int lead_car = 0;

MISSION_DATA MissionStartData;
MISSION_DATA MissionEndData;

// [D] [T]
void LaunchGame(void)
{
	int quit;
	RECT16 rect{ 0, 0, 512, 512 };

	fakeOtherPlayer = 0;

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
	else
	{
		AttractMode = 0;
		NoPlayerControl = 0;

		if (CurrentGameMode < GAMEMODE_NEXTMISSION)
		{
			if (CurrentGameMode == GAMEMODE_REPLAY)
			{
				AttractMode = 0;
				NoPlayerControl = 1;
				quick_replay = 1;
			}
		}
		else if (CurrentGameMode == GAMEMODE_DEMO)
		{
			AttractMode = 1;
			NoPlayerControl = 1;
		}
	}

	AutoDirect = 0;
	NewLevel = 1;

	quit = 0;

	do {
		GameInit();
		GameLoop();

		switch (WantedGameMode)
		{
			case GAMEMODE_NORMAL:
			case GAMEMODE_QUIT:
			case GAMEMODE_DEMO:
			{
				FadeScreen(255);
				quit = 1;
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
				quit = 1;

				NoPlayerControl = 0;
				quick_replay = 0;
				AutoDirect = 0;
			}
		}

		CurrentGameMode = WantedGameMode;
	} while (!quit);

	lead_car = 0;
	NoPlayerControl = 0;
	SetDispMask(0);
	EnableDisplay();

	ClearImage(&rect, 0, 0, 0);

	DrawSync(0);
	SetDispMask(1);
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