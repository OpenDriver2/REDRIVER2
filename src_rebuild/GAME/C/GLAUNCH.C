#include "THISDUST.H"
#include "GLAUNCH.H"


#include "LIBETC.H"

#include "SYSTEM.H"
#include "MAIN.H"
#include "E3STUFF.H"
#include "PAD.H"
#include "SOUND.H"
#include "REPLAYS.H"
#include "MISSION.H"
#include "GAMESND.H"
#include "SYSTEM.H"
#include "CAMERA.H"
#include "FMVPLAY.H"
#include "../FRONTEND/FEMAIN.H"

#include <string.h>

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
	0x203, 0x2FC, 0x3C2, 0x496, 0x56D, 0x616, 0x6D4, 0x70E, 0x800, 0x8CD, 0x99A, 0x430, 0x550, 0x5E3, 0x67B, 0x96D, 0xA17, 0xAC9, 0xBB6
};

ACTIVE_CHEATS AvailableCheats = { 0 };
ACTIVE_CHEATS ActiveCheats = { 0 };

int gInFrontend = 0;
int AttractMode = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ GameStart()
 // line 834, offset 0x00052a28
	/* begin block 1 */
		// Start line: 836
		// Start offset: 0x00052A28
		// Variables:
	// 		struct RECT rect; // stack offset -16
	// 		int oldVMode; // $s0
	// 		int SurvivalCopSettingsBackup; // $s0
	/* end block 1 */
	// End offset: 0x00052E98
	// End Line: 1011

	/* begin block 2 */
		// Start line: 1668
	/* end block 2 */
	// End Line: 1669

	/* begin block 3 */
		// Start line: 1669
	/* end block 3 */
	// End Line: 1670

	/* begin block 4 */
		// Start line: 1674
	/* end block 4 */
	// End Line: 1675

/* WARNING: Unknown calling convention yet parameter storage is locked */

int gLoadedReplay = 0;
int gHaveStoredData = 0;

int gLastChase = 0;
int gChaseNumber = 0;
int gRandomChase = 0;
int gSubGameNumber = 0;

int gMissionLadderPos = 0;
int gFurthestMission = 0x28;	//0; // [A] temporary access to all

int gWantNight = 0;


// [D]
void GameStart(void)
{
	int iVar1;
	int SurvivalCopSettingsBackup;

	if( GameType != GAME_CONTINUEMISSION && 
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
				iVar1 = 50;
			else
				iVar1 = 58;

			gCurrentMissionNumber = iVar1 + GameLevel * 2 + gWantNight + gSubGameNumber * 440;
			LaunchGame();
			break;
		case GAME_IDLEDEMO:
			iVar1 = gVibration;
			if (LoadAttractReplay(gCurrentMissionNumber))
			{
				gVibration = 0;
				CurrentGameMode = GAMEMODE_DEMO;
				gLoadedReplay = 1;

				LaunchGame();

				gLoadedReplay = 0;
				gVibration = iVar1;
			}
			break;
		case GAME_PURSUIT:
			gCurrentMissionNumber = GameLevel * 8 + 70 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();
			break;
		case GAME_GETAWAY:
			gCurrentMissionNumber = GameLevel * 8 + 102 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();
			break;
		case GAME_GATERACE:
			if (NumPlayers == 1)
				iVar1 = 134;
			else
				iVar1 = 164;

			gCurrentMissionNumber = iVar1 + GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();
			break;
		case GAME_CHECKPOINT:
			if (NumPlayers == 1)
				iVar1 = 196;
			else
				iVar1 = 228;

			gCurrentMissionNumber = iVar1 + GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();
			break;
		case GAME_TRAILBLAZER:
			gCurrentMissionNumber = GameLevel * 8 + 260 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();
			break;
		case GAME_SURVIVAL:
			gCopDifficultyLevel = 2;
			
			if (NumPlayers == 1)
				iVar1 = 292;
			else
				iVar1 = 324;

			gCurrentMissionNumber = iVar1 + GameLevel * 8 + gWantNight * 4 + gSubGameNumber;
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
			gCurrentMissionNumber = GameLevel * 8 + 420 + gWantNight * 4 + gSubGameNumber;
			LaunchGame();
			break;
		case GAME_CAPTURETHEFLAG:
			gCurrentMissionNumber = GameLevel * 8 + 352 + gSubGameNumber;
			LaunchGame();
			break;
		case GAME_SECRET:
			if (NumPlayers == 1)
				iVar1 = 480;
			else
				iVar1 = 484;

			gCurrentMissionNumber = iVar1 + gWantNight + gSubGameNumber;
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

	gHaveStoredData = 0;

	ReInitFrontend();
}


// decompiled code
// original method signature: 
// void /*$ra*/ StartRender(int renderNum /*$a0*/)
 // line 1018, offset 0x000536b0
	/* begin block 1 */
		// Start line: 2036
	/* end block 1 */
	// End Line: 2037

	/* begin block 2 */
		// Start line: 2537
	/* end block 2 */
	// End Line: 2538

// [D]
void StartRender(int renderNum)
{
	PlayFMV(renderNum);
	ReInitFrontend();
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReInitFrontend()
 // line 1030, offset 0x00052e98
	/* begin block 1 */
		// Start line: 1032
		// Start offset: 0x00052E98
		// Variables:
	// 		struct RECT rect; // stack offset -24
	/* end block 1 */
	// End offset: 0x00052FE8
	// End Line: 1103

	/* begin block 2 */
		// Start line: 2068
	/* end block 2 */
	// End Line: 2069

	/* begin block 3 */
		// Start line: 2088
	/* end block 3 */
	// End Line: 2089

	/* begin block 4 */
		// Start line: 2089
	/* end block 4 */
	// End Line: 2090

	/* begin block 5 */
		// Start line: 2091
	/* end block 5 */
	// End Line: 2092

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
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
	SpuSetReverbVoice(0, 0xffffff);
	UnPauseSound();

	LoadSoundBankDynamic((char *)0x0, 0, 0);
	LoadBankFromLump(1, 0);

#ifdef PSX
	Loadfile("FRONTEND.BIN", &DAT_001c0000);
#endif // PSX

	SetFEDrawMode();
	DrawSync(0);
	EnableDisplay();
	rect.x = 0;
	rect.y = 0;
	rect.w = 0x140;
	rect.h = 0x200;
	ClearImage(&rect, 0, 0, 0);
	DrawSync(0);
	LoadFrontendScreens();
	ReInitScreens();
	DrawSync(0);
	VSync(0);
	ClearOTagR((u_long*)MPBuff[0][0].ot, 0x1080);
	ClearOTagR((u_long*)MPBuff[0][1].ot, 0x1080);
	SetDispMask(1);
	//LoadedLevel = 0xff;
	bRedrawFrontend = 1;
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ RunMissionLadder(int newgame /*$a1*/)
 // line 1105, offset 0x00052fe8
	/* begin block 1 */
		// Start line: 1106
		// Start offset: 0x00052FE8
		// Variables:
	// 		struct MISSION_STEP *CurrentStep; // $s0
	// 		struct RENDER_ARGS RenderArgs; // stack offset -48
	// 		int quit; // $s3

		/* begin block 1.1 */
			// Start line: 1143
			// Start offset: 0x000530A4
		/* end block 1.1 */
		// End offset: 0x000530A4
		// End Line: 1143

		/* begin block 1.2 */
			// Start line: 1148
			// Start offset: 0x000530B4
		/* end block 1.2 */
		// End offset: 0x000530BC
		// End Line: 1149

		/* begin block 1.3 */
			// Start line: 1153
			// Start offset: 0x000530CC
		/* end block 1.3 */
		// End offset: 0x000530E8
		// End Line: 1157

		/* begin block 1.4 */
			// Start line: 1163
			// Start offset: 0x00053134

			/* begin block 1.4.1 */
				// Start line: 1172
				// Start offset: 0x00053198
			/* end block 1.4.1 */
			// End offset: 0x000531AC
			// End Line: 1175
		/* end block 1.4 */
		// End offset: 0x0005328C
		// End Line: 1212
	/* end block 1 */
	// End offset: 0x000532B8
	// End Line: 1215

	/* begin block 2 */
		// Start line: 2243
	/* end block 2 */
	// End Line: 2244

	/* begin block 3 */
		// Start line: 2246
	/* end block 3 */
	// End Line: 2247

	/* begin block 4 */
		// Start line: 2249
	/* end block 4 */
	// End Line: 2250

// [D]
void RunMissionLadder(int newgame)
{
	bool quit;
	MISSION_STEP *CurrentStep;
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
			CheckForCorrectDisc(0);
		else 
			CheckForCorrectDisc(1);

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



// decompiled code
// original method signature: 
// void /*$ra*/ GetRandomChase()
 // line 1222, offset 0x000535d8
	/* begin block 1 */
		// Start line: 1224
		// Start offset: 0x000535D8
		// Variables:
	// 		int bump; // $s1
	/* end block 1 */
	// End offset: 0x0005369C
	// End Line: 1250

	/* begin block 2 */
		// Start line: 2708
	/* end block 2 */
	// End Line: 2709

	/* begin block 3 */
		// Start line: 2444
	/* end block 3 */
	// End Line: 2445

	/* begin block 4 */
		// Start line: 2709
	/* end block 4 */
	// End Line: 2710

	/* begin block 5 */
		// Start line: 2711
	/* end block 5 */
	// End Line: 2712

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void GetRandomChase(void)
{
	int bump = 0;

	if (gLoadedReplay == 0)
	{
		gRandomChase = VSync(-1) % 0xd + 2;

		if (gRandomChase == gLastChase)
		{
			do {
				gRandomChase = (VSync(-1) + bump) % 0xd + 2;
				bump++;
			} while (gRandomChase == gLastChase);
		}

		gLastChase = gRandomChase;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ FindPrevMissionFromLadderPos(int pos /*$a0*/)
 // line 1252, offset 0x000536d8
	/* begin block 1 */
		// Start line: 1254
		// Start offset: 0x000536D8
	/* end block 1 */
	// End offset: 0x00053740
	// End Line: 1268

	/* begin block 2 */
		// Start line: 3004
	/* end block 2 */
	// End Line: 3005

	/* begin block 3 */
		// Start line: 3005
	/* end block 3 */
	// End Line: 3006

	/* begin block 4 */
		// Start line: 3007
	/* end block 4 */
	// End Line: 3008

// [D]
int FindPrevMissionFromLadderPos(int pos)
{
	if (pos-- > 0)
	{
		MISSION_STEP *step = &MissionLadder[pos];
		do {
			if (step->flags == 2) {
				int mission = step->data;

				if (gFurthestMission < mission)
					gFurthestMission = mission;

				return 1;
			}
			
			step--;
		} while (pos-- > 0);
	}

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ LaunchGame()
 // line 1279, offset 0x000532b8
	/* begin block 1 */
		// Start line: 1281
		// Start offset: 0x000532B8
		// Variables:
	// 		struct RECT rect; // stack offset -16
	// 		int quit; // $s0
	/* end block 1 */
	// End offset: 0x000535D8
	// End Line: 1415

	/* begin block 2 */
		// Start line: 2544
	/* end block 2 */
	// End Line: 2545

	/* begin block 3 */
		// Start line: 2609
	/* end block 3 */
	// End Line: 2610

	/* begin block 4 */
		// Start line: 2610
	/* end block 4 */
	// End Line: 2611

	/* begin block 5 */
		// Start line: 2617
	/* end block 5 */
	// End Line: 2618

/* WARNING: Unknown calling convention yet parameter storage is locked */

int fakeOtherPlayer = 0;
int gMissionCompletionState = 0;
char NoPlayerControl = 0;

// TODO: REPLAYS.C
int quick_replay = 0;
int AutoDirect = 0;
int lead_car = 0;

MISSION_DATA MissionStartData;
MISSION_DATA MissionEndData;

// [D]
void LaunchGame(void)
{
	fakeOtherPlayer = 0;

	ResetGraph(1);
	SetVideoMode(1);

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

	bool quit = false;

	do {
		GameInit();
		GameLoop();

		switch (WantedGameMode)
		{
			case GAMEMODE_NORMAL:
			case GAMEMODE_QUIT:
			case GAMEMODE_DEMO:
			{
				FadeScreen(0xff);
				quit = true;
				break;
			}
			case GAMEMODE_RESTART:
			{
				FadeScreen(0xff);
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
					FadeScreen(0xff);

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
				FadeScreen(0xff);
				quit = true;
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

	RECT16 rect { 0, 0, 512, 512 };
	ClearImage(&rect, 0, 0, 0);

	DrawSync(0);
	SetDispMask(1);
}

// decompiled code
// original method signature: 
// int /*$ra*/ FindMissionLadderPos(int mission /*$a0*/)
 // line 1417, offset 0x00053740
	/* begin block 1 */
		// Start line: 1418
		// Start offset: 0x00053740
		// Variables:
	// 		struct MISSION_STEP *step; // $a1
	// 		int pos; // $a2
	/* end block 1 */
	// End offset: 0x00053814
	// End Line: 1457

	/* begin block 2 */
		// Start line: 3184
	/* end block 2 */
	// End Line: 3185

	/* begin block 3 */
		// Start line: 3334
	/* end block 3 */
	// End Line: 3335

	/* begin block 4 */
		// Start line: 3336
	/* end block 4 */
	// End Line: 3337

// [D]
int FindMissionLadderPos(int mission)
{
	MISSION_STEP *step = MissionLadder;
	int pos = 0;
	bool end = false;

	do {
		switch (step->flags) {
		case 1:
		case 6:
			{
				step++;
				pos++;
			} break;
		case 2:
			{
				if (step->data == mission)
				{
					if (pos > 0) {
						step--;
						if (step->flags != 2)
						{
							do {
								if (--pos <= 0)
									break;

								step--;
							} while (step->flags != 2);
						}
					}

					gMissionLadderPos = pos;
					return 1;
				}

				step++;
				pos++;
			} break;
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





