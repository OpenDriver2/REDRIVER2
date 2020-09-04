#include "THISDUST.H"
#include "MISSION.H"
#include "SYSTEM.H"
#include "MGENERIC.H"
#include "DEBRIS.H"
#include "DR2ROADS.H"
#include "SPOOL.H"
#include "PAUSE.H"
#include "BOMBERMAN.H"
#include "CUTSCENE.H"
#include "CAMERA.H"
#include "OVERLAY.H"
#include "EVENT.H"
#include "CIV_AI.H"
#include "CARS.H"
#include "PLAYERS.H"
#include "REPLAYS.H"
#include "GLAUNCH.H"
#include "SCORES.H"
#include "AI.H"
#include "MAIN.H"
#include "MC_SND.H"
#include "COP_AI.H"
#include "GAMESND.H"
#include "PEDEST.H"
#include "OVERMAP.H"
#include "DENTING.H"
#include "LOADSAVE.H"

#include <string.h>

#ifndef PSX
#include <SDL.h>
#endif // PSX

char* MissionName[37] =
{
	// Chicago
	"Surveillance Tip Off",
	"Chase the Witness",
	"Train Pursuit",
	"Tailing the Drop",
	"Escape to the Safe House",
	"Chase the Intruder",
	"Caine's Compound",
	"Leaving Chicago",

	// Havana
	"Follow Up the Lead",
	"Hijack the Truck",
	"Stop the Truck",
	"Find the Clue",
	"Escape to Ferry",
	"To the Docks",
	"Back to Jones",
	"Tail Jericho",
	"Pursue Jericho",
	"Escape the Brazilians",

	// Vegas
	"Casino Getaway",
	"Beat the Train",
	"Car Bomb",
	"Car Bomb Getaway",
	"Bank Job",
	"Steal the Ambulance",
	"Stake Out",
	"Steal the Keys",
	"C4 Deal",
	"Destroy the Yard",

	// Rio
	"Bus Crash",
	"Steal the Cop Car",
	"Caine's Cash",
	"Save Jones",
	"Boat Jump",
	"Jones in Trouble",
	"Chase the Gunman",
	"Lenny Escaping",
	"Pink Lenny Gets Caught",
};

// decompiled code
// original method signature: 
// void /*$ra*/ InitialiseMissionDefaults()
 // line 1347, offset 0x0006084c
	/* begin block 1 */
		// Start line: 1349
		// Start offset: 0x0006084C
		// Variables:
	// 		int i; // $a0
	/* end block 1 */
	// End offset: 0x00060A74
	// End Line: 1435

	/* begin block 2 */
		// Start line: 2694
	/* end block 2 */
	// End Line: 2695

	/* begin block 3 */
		// Start line: 2695
	/* end block 3 */
	// End Line: 2696

	/* begin block 4 */
		// Start line: 2698
	/* end block 4 */
	// End Line: 2699

/* WARNING: Unknown calling convention yet parameter storage is locked */

int gCopDifficultyLevel = 1;
int gCopRespawnTime = 0;

GAMEMODE CurrentGameMode = GAMEMODE_NORMAL;
GAMEMODE WantedGameMode = GAMEMODE_NORMAL;

GAMETYPE StoredGameType;

int GameLevel = 0;
int gInvincibleCar = 0;
int gPlayerImmune = 0;
unsigned char NumPlayers = 1;
char NewLevel = 1;
GAMETYPE GameType = GAME_MISSION;
int gCurrentMissionNumber = 0;

int maxPlayerCars = 1;
int maxCivCars = 14;
int maxParkedCars = 7;
int maxCopCars = 4;

int gPlayerDamageFactor = 0;
int requestStationaryCivCar = 0;

int numPlayerCars = 0;
int numCivCars = 0;
int numParkedCars = 0;
int numCopCars = 0;

int gMinimumCops = 0;
int gCopDesiredSpeedScale = 0x1000;
int gCopMaxPowerScale = 0x1000;
int gCurrentResidentSlot = 0;
int gPuppyDogCop = 0;		// Driver 1 leftover
int CopsAllowed = 0;

int MaxPlayerDamage[2] = { 0x1f40 };
int prevCopsInPursuit = 0;
int gPlayerWithTheFlag = -1;
int g321GoDelay = 0;

int last_flag = -1;
int cop_adjust = 0;

int gLapTimes[2][5];
int gNumRaceTrackLaps = 3;
int lastsay = -1;

int gCarWithABerm = -1;
int gCantDrive = 0;
int gDontResetCarDamage = 0;
int bMissionTitleFade = 0;

char lockAllTheDoors = 0;
int gTannerActionNeeded = 0;
int gGotInStolenCar = 0;
int gCopCarTheftAttempted = 0;
int gLockPickingAttempted = 0;
int bStopTanner = 0;
int tannerDeathTimer = 0;
STOPCOPS gStopCops;

MR_MISSION Mission;
u_long MissionStack[16][16];
MR_THREAD MissionThreads[16];

unsigned char playercollected[2] = { 0, 0 };

const int TAIL_GETTINGCLOSE = 7000;
const int TAIL_GETTINGFAR = 12900;
const int TAIL_TOOCLOSE = 4000;
const int TAIL_TOOFAR = 15900;

#ifdef DEBUG_OPTIONS
#define MR_DebugPrint //printInfo
#define MR_DebugWarn printWarning
#else
#define MR_DebugPrint
#define MR_DebugWarn
#endif

// [D]
void InitialiseMissionDefaults(void)
{
	int i;

	if (NumPlayers == 2 || GameType > GAME_TAKEADRIVE)
	{
		lockAllTheDoors = 1;
	}
	else
	{
		lockAllTheDoors = 0;
	}

	maxPlayerCars = 1;
	maxCivCars = 14;
	maxParkedCars = 7;
	maxCopCars = 4;
	gPlayerDamageFactor = 4096;
	requestStationaryCivCar = 0;
	numPlayerCars = 0;
	numCivCars = 0;
	numParkedCars = 0;
	numCopCars = 0;
	gMinimumCops = 0;
	gCopDesiredSpeedScale = 4096;
	gCopMaxPowerScale = 4096;
	gCurrentResidentSlot = 0;
	CopsAllowed = 0;
	MaxPlayerDamage[0] = 22000;
	MaxPlayerDamage[1] = 22000;
	prevCopsInPursuit = 0;

	for (i = 0; i < 15; i++)
	{
		MissionThreads[i].initial_sp = MissionStack[i];
		MissionThreads[i].active = 0;
		MissionThreads[i].pc = NULL;
		MissionThreads[i].sp = NULL;
	}

	ClearMem((char *)&Mission, sizeof(MR_MISSION));

	Mission.active = 0;
	Mission.gameover_delay = -1;
	Mission.gameover_mode = PAUSEMODE_PAUSE;
	Mission.CarTarget = NULL;
	Mission.ChaseTarget = NULL;
	Mission.ChaseHitDelay = 0;
	Mission.StealMessage = NULL;
	Mission.PhantomCarId = -1;

	for (i = 0; i < 2; i++)
	{
		Mission.timer[i].flags = 0;
		Mission.message_priority[i] = 0;
		Mission.message_string[i] = NULL;
	}

	Driver2TempJunctionsPtr = (ulong *)_overlay_buffer;
	NumTempJunctions = 0;
	gPlayerWithTheFlag = -1;
	last_flag = -1;

	ClearMem((char *)reservedSlots, sizeof(reservedSlots));
	cop_adjust = 0;
	playercollected[0] = '\0';
	playercollected[1] = '\0';
	lastsay = -1;
	g321GoDelay = 0;

	for (i = 0; i < 5; i++)
	{
		gLapTimes[0][i] = -1;
		gLapTimes[1][i] = -1;
	}

	gCarWithABerm = -1;
	gCantDrive = 0;
	gGotInStolenCar = 0;
	gCopCarTheftAttempted = 0;
	gLockPickingAttempted = 0;
	gDontResetCarDamage = 0;
	gStopCops.radius = 0;
}


// decompiled code
// original method signature: 
// void /*$ra*/ LoadMission(int missionnum /*$s0*/)
 // line 1437, offset 0x00060a74
	/* begin block 1 */
		// Start line: 1438
		// Start offset: 0x00060A74
		// Variables:
	// 		char filename[32]; // stack offset -64
	// 		unsigned long header; // stack offset -32
	// 		unsigned long offset; // $s0
	// 		unsigned long length; // $s1
	// 		int size; // $t1
	// 		int i; // $v0

		/* begin block 1.1 */
			// Start line: 1677
			// Start offset: 0x00060D88
			// Variables:
		// 		int flags; // $a1
		// 		int time; // $a2
		/* end block 1.1 */
		// End offset: 0x00060E04
		// End Line: 1698

		/* begin block 1.2 */
			// Start line: 1767
			// Start offset: 0x00060F84
			// Variables:
		// 		struct _ROUTE_INFO *rinfo; // $s0
		/* end block 1.2 */
		// End offset: 0x00061024
		// End Line: 1793

		/* begin block 1.3 */
			// Start line: 1830
			// Start offset: 0x000610FC
			// Variables:
		// 		int num; // $v1
		/* end block 1.3 */
		// End offset: 0x00061128
		// End Line: 1841
	/* end block 1 */
	// End offset: 0x00061258
	// End Line: 1879

	/* begin block 2 */
		// Start line: 2949
	/* end block 2 */
	// End Line: 2950

	/* begin block 3 */
		// Start line: 2952
	/* end block 3 */
	// End Line: 2953

_MISSION* MissionLoadAddress;
_MISSION *MissionHeader;
STREAM_SOURCE* PlayerStartInfo[8];
int numPlayersToCreate = 0;
int gStartOnFoot = 0;
int gSinkingTimer = 100;
int gTimeInWater = 0x19;
char InWater = 0;
int gBobIndex = 0;
int gWeather = 0;
int gTimeOfDay = 0;
int gShowPlayerDamage = 0;
int gDontPingInCops = 0;
int gBatterPlayer = 1;

int wantedCar[2] = { -1, -1 };

_TARGET *MissionTargets;
unsigned long *MissionScript;
char *MissionStrings;
char* gMissionTitle = NULL;

int multiplayerregions[4];
int gMultiplayerLevels = 0;

// LEADAI
extern LEAD_PARAMETERS LeadValues;

static char NewLeadDelay = 0;

#define MISSIOH_IDENT (('D' << 24) | ('2' << 16) | ('M' << 8) | 'S' )

// [D]
void LoadMission(int missionnum)
{
	bool bVar1;
	short sVar2;
	_MISSION *p_Var3;
	int iVar4;
	LEAD_PARAMETERS *pLVar5;
	int *piVar6;
	char bVar7;
	int iVar8;
	long *plVar9;
	int iVar10;
	int *piVar11;
	uint loadsize;
	char filename[32];
	unsigned long header;

	InitialiseMissionDefaults();

	MALLOC_BEGIN();

	if (NewLevel != 0) 
		MissionLoadAddress = (_MISSION *)mallocptr;

	sprintf(filename, "MISSIONS\\MISSIONS.BLK");

	if (FileExists(filename) == 0)
		return;

	LoadfileSeg(filename, (char*)&header, missionnum * 4, 4);

	if (header == 0) 
	{
#ifndef PSX
		char errPrint[1024];
		sprintf(errPrint, "%d is not valid mission\n", missionnum);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
#endif // PSX
		return;
	}

	loadsize = header >> 0x13;
	LoadfileSeg(filename, (char *)MissionLoadAddress, header & 0x7ffff, sizeof(_MISSION));

	MissionHeader = MissionLoadAddress;
	MissionTargets = (_TARGET *)((int)&MissionLoadAddress->id + MissionLoadAddress->size);
	MissionScript = (ulong *)(MissionTargets + 0x10);
	MissionStrings = (char *)(((_TARGET *)MissionScript)->data + MissionLoadAddress->strings);

	if ((MissionLoadAddress->route != 0) && (NewLevel == 0))
	{
		loadsize = (int)MissionStrings + (MissionLoadAddress->route - (int)MissionLoadAddress);
	}

	iVar4 = LoadfileSeg(filename, (char *)MissionLoadAddress, header & 0x7ffff, loadsize);

	if (MissionHeader->id != MISSIOH_IDENT) 
	{
#ifndef PSX
		char errPrint[1024];
		sprintf(errPrint, "Invalid mission %d identifier\n", missionnum);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
#endif // PSX

		Mission.active = 0;
		return;
	}


	MissionHeader->id = 0;

	if (MissionHeader->region != 0)
	{
		multiplayerregions[1] = -1;
		multiplayerregions[2] = -1;
		multiplayerregions[3] = -1;
		multiplayerregions[0] = MissionHeader->region;
	}

	gMultiplayerLevels = (MissionHeader->region != 0);
	doSpooling = (MissionHeader->region == 0);
	Mission.active = 1;
	GameLevel = MissionHeader->city;

#ifdef CUTSCENE_RECORDER
	// load some data from target cutscene mission
	extern int gCutsceneAsReplay;
	if(gCutsceneAsReplay)
	{
		LoadfileSeg(filename, (char*)&header, gCutsceneAsReplay * 4, 4);

		if (header == 0)
			return;

		_MISSION missionTempHeader;

		loadsize = header >> 0x13;
		LoadfileSeg(filename, (char *)&missionTempHeader, header & 0x7ffff, sizeof(_MISSION));

		memcpy(MissionHeader->residentModels, missionTempHeader.residentModels, sizeof(missionTempHeader.residentModels));
		MissionHeader->time = missionTempHeader.time;
		MissionHeader->weather = missionTempHeader.weather;
	}
	
	if (gCutsceneAsReplay == 0)
#endif
	{
		PlayerStartInfo[0]->position.vx = MissionHeader->playerStartPosition.x;
		PlayerStartInfo[0]->rotation = MissionHeader->playerStartRotation;
		PlayerStartInfo[0]->position.vz = MissionHeader->playerStartPosition.y;
		PlayerStartInfo[0]->model = MissionHeader->playerCarModel;
		PlayerStartInfo[0]->palette = MissionHeader->playerCarColour;
	}

	if (MissionHeader->maxDamage != 0) 
	{
		MaxPlayerDamage[1] = MissionHeader->maxDamage;
		MaxPlayerDamage[0] = MissionHeader->maxDamage;
	}

	gTimeOfDay = MissionHeader->time;
	gWeather = MissionHeader->weather;

	if (gTimeOfDay == 1 || gTimeOfDay < 2 || gTimeOfDay == 2 || gTimeOfDay != 3) 
	{
		gNight = 0;
	}
	else 
	{
		gNight = 1;
	}

	if (MissionHeader->weather == 1) 
	{
		gRainCount = 30;
		gEffectsTimer = 41;
	}
	else 
	{
		gRainCount = 0;
		gEffectsTimer = 0;
	}

	Mission.timer[0].flags = 0;
	Mission.timer[0].x = 124;
	Mission.timer[1].x = 124;
	Mission.timer[0].y = 16;
	Mission.timer[0].count = 0;
	Mission.timer[1].y = 136;
	Mission.timer[1].flags = 0;
	Mission.timer[1].count = 0;

	if (MissionHeader->timer != 0 || (MissionHeader->timerFlags & 0x8000U) != 0)
	{
		bVar7 = 1;

		if ((MissionHeader->timerFlags & 0x8000U) != 0)
			bVar7 = 3;
	
		if ((MissionHeader->timerFlags & 0x4000U) != 0)
			bVar7 = bVar7 | 8;

		if ((MissionHeader->timerFlags & 0x2000U) != 0)
			bVar7 = bVar7 | 0x10;

		for (int i = 0; i < NumPlayers; i++)
		{
			Mission.timer[i].flags = bVar7;
			Mission.timer[i].count = MissionHeader->timer * 3000;
		}
	}

	gMinimumCops = MissionHeader->cops.min;
	maxCopCars = MissionHeader->cops.max;

	if (maxCopCars == 4)
	{
		if (GameType == GAME_SURVIVAL) 
		{
			gDontPingInCops = 0;
			gBatterPlayer = 1;

		}
		else
		{
			gDontPingInCops = 1;
			gBatterPlayer = 0;
		}
	}
	else 
	{
		gDontPingInCops = 0;
		gBatterPlayer = 0;
	}

	gCopDesiredSpeedScale = MissionHeader->cops.speed;
	gCopMaxPowerScale = MissionHeader->cops.power;
	CopsAllowed = (maxCopCars != 0);

	if (GameType == GAME_SURVIVAL)
	{
		gCopData.immortal = 1;
	}
	else if (GameType == GAME_GETAWAY)
	{
		gDontPingInCops = 1;
		gCopData.immortal = 1;
	}
	else if (GameType == GAME_SECRET)
	{
		maxCivCars = 10;
		maxParkedCars = 5;
	}
	else
	{
		gCopData.immortal = 0;
	}

	if ((MissionHeader->type & 2U) == 0) 
	{
		PlayerStartInfo[0]->type = 1;
	}
	else
	{
		PlayerStartInfo[0]->type = 2;
		PlayerStartInfo[0]->model = 0;
	}

	if (NewLevel != 0) 
	{
		if (MissionHeader->route == 0)
		{
			mallocptr = mallocptr + (iVar4 + 3U & 0xfffffffc);
#ifdef PSX
			Loadfile("PATH.BIN", (char *)popNode);
#endif // PSX
			leadAILoaded = 0;
			pathAILoaded = 1;
		}
		else 
		{
			piVar11 = (int *)(MissionStrings + MissionHeader->route);
			NumTempJunctions = *piVar11;
			memcpy(Driver2TempJunctionsPtr, piVar11 + 1, NumTempJunctions << 2);
			mallocptr = MissionStrings + MissionHeader->route;
#ifdef PSX
			Loadfile("LEAD.BIN", (char *)popNode);
#endif // PSX

			// I think it's wrong...
			pLVar5 = &LeadValues;
			piVar6 = piVar11 + 0x3e9;
			leadAILoaded = 1;
			pathAILoaded = 0;

			do {
				pLVar5->tEnd = piVar6[0];
				pLVar5->tAvelLimit = piVar6[1];
				pLVar5->tDist = piVar6[2];
				pLVar5->tDistMul = piVar6[3];
				piVar6 = piVar6 + 4;
				pLVar5 = (LEAD_PARAMETERS *)&pLVar5->tWidth;
			} while (piVar6 != piVar11 + 0x3f9);
			CopsAllowed = 0;
		}
	}

	MALLOC_END();

	sprintf(filename, "MISSIONS\\PATH%d.%d", gCurrentMissionNumber, 0);

	if (FileExists(filename))
		LoadfileSeg(filename, (char *)(MissionTargets + 4), 0, 0x280);

	if ((MissionHeader->type & 1U) != 0) 
		RestoreStartData();

	PreProcessTargets();

	if (gCurrentMissionNumber - 1U < 0x28)
	{
		loadsize = gCurrentMissionNumber;

		if (0x24 < gCurrentMissionNumber) 
			loadsize = gCurrentMissionNumber - 1U;

		if (0xb < loadsize) 
			loadsize = loadsize - 1;
		if (7 < loadsize) 
			loadsize = loadsize - 1;

		gMissionTitle = MissionName[loadsize - 1];
	}
	else
	{
		gMissionTitle = NULL;
	}

	if (wantedCar[0] != -1) 
	{
		PlayerStartInfo[0]->model = wantedCar[0];

		if ((wantedCar[0] == 0) || (4 < wantedCar[0])) 
		{
			PlayerStartInfo[0]->palette = 0;

			if (3 < wantedCar[0])
				MissionHeader->residentModels[4] = wantedCar[0];
		}
		else 
			MissionHeader->residentModels[0] = wantedCar[0];
	}

	if (wantedCar[1] != -1)
	{
		PlayerStartInfo[1]->model = wantedCar[1];

		if ((wantedCar[1] == 0) || (4 < wantedCar[1]))
			PlayerStartInfo[1]->palette = 0;
		else
			MissionHeader->residentModels[1] = wantedCar[1];
	}

	if (GameType == GAME_CAPTURETHEFLAG)
		ActivateNextFlag();

	MRInitialiseThread(&MissionThreads[0], MissionScript, 0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandleMission()
 // line 1881, offset 0x00061274
	/* begin block 1 */
		// Start line: 4184
	/* end block 1 */
	// End Line: 4185

	/* begin block 2 */
		// Start line: 4188
	/* end block 2 */
	// End Line: 4189

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void HandleMission(void)
{
	int iVar1;
	uint uVar2;

	if (!Mission.active)
		return;

	if(gInGameCutsceneActive)
		return;

	if(gInGameCutsceneDelay)
		return;

	// init frame
	if (CameraCnt == 0)
	{
		if ((MissionHeader->type & 4U) != 0)
		{
			HandleMissionThreads();
			Mission.message_timer[0] = 0;
			Mission.message_timer[1] = 0;

			MRCommitThreadGenocide();
			MRInitialiseThread(&MissionThreads[0], MissionScript, 0);
		}

		uVar2 = MissionHeader->type & 0x30;

		FelonyBar.active = 0;

		if (uVar2 != 0x10)
		{
			if (uVar2 < 0x11)
			{
				if (uVar2 == 0)
				{
					FelonyBar.active = 1;
				}
				else
				{
					FelonyBar.active = 0;
				}
			}

			if (uVar2 == 0x20)
			{
				FelonyBar.active = 1;
				FelonyBar.flags |= 2;
			}
		}
	}

	MRHandleCarRequests();

	if (bMissionTitleFade)
		return;

	if (Handle321Go())
		return;

	if (HandleGameOver())
		return;

	if (Mission.message_timer[0] != 0)
		Mission.message_timer[0]--;

	if (Mission.message_timer[1] != 0)
		Mission.message_timer[1]--;

	if (Mission.ChaseHitDelay != 0)
		Mission.ChaseHitDelay--;

	gTannerActionNeeded = 0;

	HandleTimer(&Mission.timer[0]);
	HandleTimer(&Mission.timer[1]);

	HandleThrownBombs();
	HandleMissionThreads();

	if(gCopCarTheftAttempted != 0) 
	{
		SetMissionMessage(MissionStrings + MissionHeader->msgPoliceCar, 2, 1);
		gCopCarTheftAttempted = 0;
	}

	if(gLockPickingAttempted != 0 && NumPlayers == 1)
	{
		SetMissionMessage(MissionStrings + MissionHeader->msgDoorsLocked, 2, 1);
		gLockPickingAttempted = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandleTimer(struct MR_TIMER *timer /*$s0*/)
 // line 1962, offset 0x000614a4
	/* begin block 1 */
		// Start line: 4347
	/* end block 1 */
	// End Line: 4348

// [D]
void HandleTimer(MR_TIMER *timer)
{
	unsigned char bVar1;
	unsigned char uVar2;
	int iVar3;

	bVar1 = timer->flags;

	if ((bVar1 & 4) != 0) 
		return;

	if ((bVar1 & 1) == 0) 
		return;

	if ((bVar1 & 2) == 0) 
	{
		iVar3 = timer->count + -100;
		timer->count = iVar3;
		if (iVar3 < 1) 
		{
			if (((MissionHeader->timerFlags & 0x1000U) == 0) || DetonatorTimer() == 0)
			{
				if ((timer->flags & 8) == 0)
				{
					if (Mission.gameover_delay == -1)
						SetMissionFailed(FAILED_OUTOFTIME);

					if ((timer->flags & 0x10) != 0) 
					{
						events.cameraEvent = (_EVENT *)0x1;
						BombThePlayerToHellAndBack(gCarWithABerm);
					}
				}
				else if (Mission.gameover_delay == -1)
				{
					SetMissionComplete();
					timer->count = 0;
					goto LAB_000615e0;
				}

				timer->count = 0;
			}
			else 
			{
				MissionHeader->timerFlags = MissionHeader->timerFlags & 0xefff;
				timer->count = 9000;
				timer->flags = timer->flags | 0x28;
			}
		}
	}
	else {
		iVar3 = timer->count + 100;
		timer->count = iVar3;

		if (10799999 < iVar3)
			timer->count = 10799999;

	}

LAB_000615e0:
	iVar3 = timer->count;
	uVar2 = (iVar3 / 180000);

	timer->min = uVar2;
	timer->sec = (iVar3 / 3000) + uVar2 * -0x3c;
	timer->frac = ((iVar3 % 3000) / 0x1e);
}



// decompiled code
// original method signature: 
// void /*$ra*/ RegisterChaseHit(int car1 /*$a0*/, int car2 /*$a1*/)
 // line 2015, offset 0x00061684
	/* begin block 1 */
		// Start line: 4464
	/* end block 1 */
	// End Line: 4465

	/* begin block 2 */
		// Start line: 4465
	/* end block 2 */
	// End Line: 4466

// [D]
void RegisterChaseHit(int car1, int car2)
{
	int player_id;

	if (Mission.ChaseTarget && Mission.ChaseHitDelay == 0) 
	{
		if (gPlayerWithTheFlag == -1) 
		{
			if (car1 == Mission.ChaseTarget->data[6] || car2 == Mission.ChaseTarget->data[6]) 
			{
				Mission.ChaseTarget->data[0xd]--;
				Mission.ChaseHitDelay = 20;
				DamageBar.position++;
			}
		}
		else 
		{
			player_id = 1 - gPlayerWithTheFlag;
			gPlayerWithTheFlag = player_id;

			player[player_id].targetCarId = -1;
			Mission.ChaseHitDelay = 20;
			player[1 - player_id].targetCarId = gPlayerWithTheFlag;

			SetPlayerMessage(player_id, "You got the flag!",2,1);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PauseMissionTimer(int pause /*$a0*/)
 // line 2046, offset 0x00064268
	/* begin block 1 */
		// Start line: 6575
	/* end block 1 */
	// End Line: 6576

	/* begin block 2 */
		// Start line: 4092
	/* end block 2 */
	// End Line: 4093

	/* begin block 3 */
		// Start line: 6576
	/* end block 3 */
	// End Line: 6577

// [D]
void PauseMissionTimer(int pause)
{
	if (pause == 0) 
	{
		Mission.timer[0].flags &= ~4;
		Mission.timer[1].flags &= ~4;
	}
	else 
	{
		Mission.timer[0].flags |= 4;
		Mission.timer[1].flags |= 4;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetMissionMessage(char *message /*$a0*/, int priority /*$a1*/, int seconds /*$a2*/)
 // line 2060, offset 0x000642a8
	/* begin block 1 */
		// Start line: 2061
		// Start offset: 0x000642A8
		// Variables:
	// 		int i; // $a3
	/* end block 1 */
	// End offset: 0x00064340
	// End Line: 2079

	/* begin block 2 */
		// Start line: 6606
	/* end block 2 */
	// End Line: 6607

	/* begin block 3 */
		// Start line: 6609
	/* end block 3 */
	// End Line: 6610

// [D]
void SetMissionMessage(char *message, int priority, int seconds)
{
	short *psVar1;
	uint uVar2;
	char **ppcVar3;

	uVar2 = (uint)NumPlayers;
	if (message != MissionStrings - 1 && message != NULL && NumPlayers != 0) 
	{
		ppcVar3 = Mission.message_string;
		psVar1 = Mission.message_priority;

		do {
			if ((psVar1[-2] == 0) || (*psVar1 <= priority)) 
			{
				*ppcVar3 = message;
				*psVar1 = priority;

				if (seconds == 0) 
				{
					psVar1[-2] = 5;
				}
				else 
				{
					psVar1[-2] = seconds * 30;
				}
			}

			ppcVar3++;
			uVar2--;
			psVar1++;
		} while (uVar2 != 0);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetPlayerMessage(int player /*$a0*/, char *message /*$a1*/, int priority /*$a2*/, int seconds /*$a3*/)
 // line 2081, offset 0x00064348
	/* begin block 1 */
		// Start line: 6657
	/* end block 1 */
	// End Line: 6658

	/* begin block 2 */
		// Start line: 6658
	/* end block 2 */
	// End Line: 6659

// [D]
void SetPlayerMessage(int player, char *message, int priority, int seconds)
{
	if (message != MissionStrings-1 && message != NULL) 
	{
		if (Mission.message_timer[player] == 0 || 
			Mission.message_priority[player] <= priority)
		{
			Mission.message_string[player] = message;
			Mission.message_priority[player] = priority;
			Mission.message_timer[player] = seconds * 30;
		}
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ TargetComplete(struct _TARGET *target /*$a0*/, int player /*$a1*/)
 // line 2094, offset 0x000643c4
	/* begin block 1 */
		// Start line: 2095
		// Start offset: 0x000643C4
		// Variables:
	// 		unsigned long complete; // $a0
	/* end block 1 */
	// End offset: 0x00064408
	// End Line: 2115

	/* begin block 2 */
		// Start line: 6685
	/* end block 2 */
	// End Line: 6686

	/* begin block 3 */
		// Start line: 6688
	/* end block 3 */
	// End Line: 6689

// [D]
int TargetComplete(_TARGET *target, int player)
{
	unsigned long complete;

	if (player == 0) 
	{
		complete = target->data[1] & 2;
	}
	else 
	{
		complete = target->data[1] & 0x100;

		if (player != 1) 
		{
			if ((target->data[1] & 0x102) == 0x102)
				return 1;

			return 0;
		}
	}

	if (complete == 0)
		return 0;

	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ TargetActive(struct _TARGET *target /*$a0*/, int player /*$a1*/)
 // line 2117, offset 0x00064408
	/* begin block 1 */
		// Start line: 2118
		// Start offset: 0x00064408
		// Variables:
	// 		unsigned long active; // $a0
	/* end block 1 */
	// End offset: 0x0006444C
	// End Line: 2138

	/* begin block 2 */
		// Start line: 6728
	/* end block 2 */
	// End Line: 6729

	/* begin block 3 */
		// Start line: 6731
	/* end block 3 */
	// End Line: 6732

	/* begin block 4 */
		// Start line: 6734
	/* end block 4 */
	// End Line: 6735

// [D]
int TargetActive(_TARGET *target, int player)
{
	unsigned long active;
	uint uVar2;

	if (player == 0) 
	{
		active = target->data[1] & 1;
	}
	else 
	{
		active = target->data[1] & 0x800;

		if (player != 1) 
		{
			if ((target->data[1] & 0x801) == 0x801)
				return 1;

			return 0;
		}
	}

	if (active == 0)
		return 0;

	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ Swap2Cars(int curslot /*$a3*/, int newslot /*$s1*/)
 // line 2140, offset 0x00061784
	/* begin block 1 */
		// Start line: 2141
		// Start offset: 0x00061784
		// Variables:
	// 		struct _CAR_DATA cd; // stack offset -704
	// 		struct _CAR_DATA *cp; // $s0
	// 		int ctrlNodeCurId; // $s4
	// 		int pnodeCurId; // $s5
	// 		int ctrlNodeNewId; // $t2
	// 		int pnodeNewId; // $t3
	/* end block 1 */
	// End offset: 0x00061C5C
	// End Line: 2221

	/* begin block 2 */
		// Start line: 4728
	/* end block 2 */
	// End Line: 4729

/* WARNING: Type propagation algorithm not settling */

// [D]
int Swap2Cars(int curslot, int newslot)
{
	_CAR_DATA *cp;

	int ctrlNodeNewId;
	int pnodeNewId;
	int ctrlNodeCurId;
	int pnodeCurId;

	_CAR_DATA cd;

	if (curslot == newslot)
		return newslot;

	ctrlNodeNewId = -1;
	pnodeNewId = -1;

	ctrlNodeCurId = -1;
	pnodeCurId = -1;

	// hold cur slot nodes
	cp = &car_data[curslot];
	if (cp->controlType == 2)
	{
		if (cp->ai.c.ctrlNode == NULL)
			ctrlNodeCurId = -1;
		else
			ctrlNodeCurId = cp->ai.c.ctrlNode - cp->ai.c.targetRoute;	// [A]

		if (cp->ai.c.pnode == NULL)
			pnodeCurId = -1;
		else 
			pnodeCurId = cp->ai.c.pnode - cp->ai.c.targetRoute;	// [A]
	}

	cp->lowDetail = -1;
	cp->ap.qy = 0;
	cp->ap.qw = 0;

	// hold new slot nodes
	cp = &car_data[newslot];
	if (cp->controlType == 2)
	{
		if (cp->ai.c.ctrlNode == NULL)
			ctrlNodeNewId = -1;
		else
			ctrlNodeNewId = cp->ai.c.ctrlNode - cp->ai.c.targetRoute;	// [A]

		if (cp->ai.c.pnode == NULL)
			pnodeNewId = -1;
		else
			pnodeNewId = cp->ai.c.pnode - cp->ai.c.targetRoute;	// [A]
	}

	cp->lowDetail = -1;
	cp->ap.qy = 0;
	cp->ap.qw = 0;

	cp = &car_data[newslot];

	// do data swap
	memcpy(&cd, &car_data[newslot], sizeof(_CAR_DATA));
	memcpy(&car_data[newslot], &car_data[curslot], sizeof(_CAR_DATA));
	memcpy(&car_data[curslot], &cd, sizeof(_CAR_DATA));

	// swap ids
	car_data[newslot].id = newslot;
	car_data[curslot].id = curslot;

	// swap target car id
	if (player[0].cameraCarId == newslot)
		player[0].cameraCarId = curslot;
	else if (player[0].cameraCarId == curslot)
		player[0].cameraCarId = newslot;

	// swap target car id
	if (player[0].targetCarId == newslot)
		player[0].targetCarId = curslot;
	else if (player[0].targetCarId == curslot)
		player[0].targetCarId = newslot;

	// swap player car id
	if (player[0].playerCarId == newslot)
		player[0].playerCarId = curslot;
	else if (player[0].playerCarId == curslot)
		player[0].playerCarId = newslot;

	// swap world center car
	if (player[0].worldCentreCarId == newslot) 
	{
		player[0].spoolXZ = (VECTOR *)car_data[curslot].hd.where.t;
		player[0].worldCentreCarId = curslot;
	}
	else if (player[0].worldCentreCarId == curslot)
	{
		player[0].spoolXZ = (VECTOR *)car_data[newslot].hd.where.t;
		player[0].worldCentreCarId = newslot;
	}

	gDontResetCarDamage = 1;

	// setup old slot nodes and reinit car
	cp = &car_data[curslot];

	if (ctrlNodeNewId == -1) 
		cp->ai.c.ctrlNode = 0;
	else 
		cp->ai.c.ctrlNode = &cp->ai.c.targetRoute[ctrlNodeNewId];

	if (pnodeNewId == -1) 
		cp->ai.c.pnode = 0;
	else 
		cp->ai.c.pnode = &cp->ai.c.targetRoute[pnodeNewId];

	CreateDentableCar(cp);
	DentCar(cp);

	// setup new slot nodes and reinit car
	cp = &car_data[newslot];

	if (ctrlNodeCurId == -1)
		cp->ai.c.ctrlNode = 0;
	else
		cp->ai.c.ctrlNode = &cp->ai.c.targetRoute[ctrlNodeCurId];

	if (pnodeCurId == -1)
		cp->ai.c.pnode = 0;
	else
		cp->ai.c.pnode = &cp->ai.c.targetRoute[pnodeCurId];

	CreateDentableCar(cp);
	DentCar(cp);

	gDontResetCarDamage = 0;

	return newslot;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetConfusedCar(int slot /*$a0*/)
 // line 2223, offset 0x0006444c
	/* begin block 1 */
		// Start line: 6857
	/* end block 1 */
	// End Line: 6858

	/* begin block 2 */
		// Start line: 6943
	/* end block 2 */
	// End Line: 6944

	/* begin block 3 */
		// Start line: 6944
	/* end block 3 */
	// End Line: 6945

// [D]
void SetConfusedCar(int slot)
{
	car_data[slot].controlType = 2;
	car_data[slot].ai.c.thrustState = 3;
	car_data[slot].ai.c.ctrlState = 7;
	car_data[slot].ai.c.ctrlNode = NULL;
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandleMissionThreads()
 // line 2234, offset 0x00061c5c
	/* begin block 1 */
		// Start line: 2236
		// Start offset: 0x00061C5C
		// Variables:
	// 		struct MR_THREAD *thread; // $s0
	// 		int running; // $s1
	// 		unsigned long value; // $a1
	// 		int i; // $a0
	/* end block 1 */
	// End offset: 0x00061E3C
	// End Line: 2277

	/* begin block 2 */
		// Start line: 4922
	/* end block 2 */
	// End Line: 4923

	/* begin block 3 */
		// Start line: 4936
	/* end block 3 */
	// End Line: 4937

	/* begin block 4 */
		// Start line: 4937
	/* end block 4 */
	// End Line: 4938

	/* begin block 5 */
		// Start line: 4943
	/* end block 5 */
	// End Line: 4944

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void HandleMissionThreads(void)
{
	MR_THREAD* thread;
	int running;
	unsigned long value;

	for (int i = 0; i < 16; i++)
		MissionTargets[i].data[1] &= ~0x600;

	for (int i = 0; i < 16; i++)
	{
		thread = &MissionThreads[i];
		running = thread->active;

		while (running && (Mission.gameover_delay == -1)
			&& (!gInGameCutsceneActive && gInGameCutsceneDelay == 0))
		{
			value = *thread->pc++;

			switch (value & 0xff000000)
			{
			case 0x0:
			case 0x2000000:
			case 0xff000000:
				MR_DebugPrint("MR: push %d\n", value);
				MRPush(thread, value);
				break;
			case 0x1000000:
				MR_DebugPrint("MR: command %x\n", value);
				running = MRCommand(thread, value);
				break;
			case 0x3000000:
				MR_DebugPrint("MR: operator %x\n", value);
				running = MROperator(thread, value);
				break;
			case 0x4000000:
				MR_DebugPrint("MR: function %x\n", value);
				running = MRFunction(thread, value);
				break;
			}
		}
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ MRCommand(struct MR_THREAD *thread /*$s1*/, unsigned long cmd /*$a1*/)
 // line 2279, offset 0x00061e3c
	/* begin block 1 */
		// Start line: 2280
		// Start offset: 0x00061E3C
		// Variables:
	// 		unsigned long val1; // $s0
	// 		unsigned long val2; // $s0
	/* end block 1 */
	// End offset: 0x00062470
	// End Line: 2439

	/* begin block 2 */
		// Start line: 5054
	/* end block 2 */
	// End Line: 5055

	/* begin block 3 */
		// Start line: 5057
	/* end block 3 */
	// End Line: 5058

	/* begin block 4 */
		// Start line: 5060
	/* end block 4 */
	// End Line: 5061

// [D]
int MRCommand(MR_THREAD *thread, ulong cmd)
{
	long val1;
	long val2;

	if (cmd == 0x1000051)				// PlayCutscene
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR command: PlayCutscene(%d)\n", val1);

		CompleteAllActiveTargets(thread->player);
		TriggerInGameCutscene(val1);

		if (gInGameCutsceneActive || gCutsceneAtEnd)
		{
			RequestXA();
			InitializeCutsceneSound(val1);
		}

		return 1;
	}
	else if (cmd == 0x1000021)			// CompleteAllActiveTargets
	{
		MR_DebugWarn("MR command: CompleteAllActiveTargets\n");

		CompleteAllActiveTargets(thread->player);
		return 1;
	}
	else if (cmd == 0x1000010)			// SetVariable
	{
		val1 = MRPop(thread);
		val2 = MRPop(thread);

		MR_DebugWarn("MR command: SetVariable(%08X, %d)\n", val1, val2);

		MRSetVariable(thread, val1, val2);

		return 1;
	}
	else if (cmd == 0x1000011)			// Jump
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR command: Jump(%d)\n", val1);

		return MRJump(thread, val1);
	}
	else if (cmd == 0x1000001)			// BranchIf
	{
		val1 = MRPop(thread);
		val2 = MRPop(thread);

		if (val2 != 0)
		{
			MR_DebugWarn("MR command: BranchIf(%d, %d)\n", val1, val2);
			return 1;
		}

		return MRJump(thread, val1);
	}
	else if (cmd == 0x1000022)			// MultiCarEvent
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR command: MultiCarEvent(%d)\n", val1);

		MultiCarEvent(MissionTargets + val1);
		return 1;
	}
	else if (cmd == 0x1000030)			// SetPlayerFelony
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR command: SetPlayerFelony(%d)\n", val1);

		if (player[0].playerCarId < 0)
			pedestrianFelony = val1;
		else
			car_data[player[0].playerCarId].felonyRating = val1;
	}
	else if (cmd == 0x1000050)			// ShowPlayerMessage
	{
		val1 = MRPop(thread);
		val2 = MRPop(thread);

		MR_DebugWarn("MR command: ShowPlayerMessage(%d, %d)\n", val1, val2);

		SetPlayerMessage(thread->player, MissionStrings + val1, 0, val2);

		return 1;
	}
	else if (cmd == 0x1000070)			// TriggerEvent
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR command: TriggerEvent(%d)\n", val1);

		TriggerEvent(val1);
		return 1;
	}
	else if (cmd == 0x1000080)			// SetDoorsLocked
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR command: SetDoorsLocked(%d)\n", val1);

		lockAllTheDoors = val1;
		return 1;
	}
	else if (cmd == 0x1000054)			// SetStealMessage
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR command: SetStealMessage(%d)\n", val1);

		Mission.StealMessage = MissionStrings + val1;
	}
	else if (cmd == 0x1000055)			// ShowOutOfTimeMessage
	{
		MR_DebugWarn("MR command: ShowOutOfTimeMessage\n");

		SetPlayerMessage(1, MissionStrings + MissionHeader->msgOutOfTime, 2, 2);
		return 1;
	}
	else if (cmd == 0x1001000)			// StopThread
	{
		MR_DebugWarn("MR command: StopThread\n");

		return MRStopThread(thread);
	}
	else if (cmd == 0x1001002)			// StartThreadForPlayer
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR command: StartThreadForPlayer(%d)\n", val1);

		MRStartThread(thread, val1, thread->player);
		return 1;
	}
	else if (cmd == 0x1001003)			// StartThread2
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR command: StartThread2(%d)\n", val1);

		MRStartThread(thread, val1, 1);
		return 1;
	}
	else if (cmd == 0x1000100)			// SetCameraEvent
	{
		MR_DebugWarn("MR command: SetCameraEvent\n");

		SpecialCamera(SPECIAL_CAMERA_SET, 0);
		return 1;
	}
	else if (cmd == 0x1000071)			// AwardPlayerCheat
	{
		MR_DebugWarn("MR command: AwardPlayerCheat\n");

		val1 = MRPop(thread);

		if ((val1 & 0x8000) != 0) {
			AvailableCheats.cheat1 = 1;
		}
		if ((val1 & 0x4000) != 0) {
			AvailableCheats.cheat2 = 1;
		}
		if ((val1 & 0x10000) != 0) {
			AvailableCheats.cheat3 = 1;
		}
		if ((val1 & 0x20000) != 0) {
			AvailableCheats.cheat4 = 1;
		}
		if ((val1 & 1) != 0) {
			AvailableCheats.cheat5 = 1;
		}
		if ((val1 & 0x10) != 0) {
			AvailableCheats.cheat6 = 1;
		}
		if ((val1 & 0x100) != 0) {
			AvailableCheats.cheat7 = 1;
		}
		if ((val1 & 0x1000) != 0) {
			AvailableCheats.cheat8 = 1;
		}
		if ((val1 & 0x2000) != 0) {
			AvailableCheats.cheat11 = 1;
		}

		return 1;
	}
	else if (cmd == 0x1000090)			// SetRaining
	{
		MR_DebugWarn("MR command: SetRaining\n");
		gWeather = 1;
		return 1;
	}
	else if (cmd == 0x1000040)
	{
		MR_DebugWarn("MR command: player timer flag 2 set\n");
		Mission.timer[thread->player].flags |= 2;
	}
	else  if (cmd == 0x1000042)
	{
		MR_DebugWarn("MR command: timer flag 0x1000 set\n");
		MissionHeader->timerFlags |= 0x1000;
	}
	else if (cmd == 0x1000041)
	{
		MR_DebugWarn("MR command: player timer flag 2 removed\n");
		Mission.timer[thread->player].flags &= ~2;
		return 1;
	}
	else if (cmd == 0x1001001)
	{
		MR_DebugWarn("MR command: SetMissionComplete\n");
		SetMissionComplete();
		return 1;
	}
	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ MROperator(struct MR_THREAD *thread /*$s3*/, unsigned long op /*$s0*/)
 // line 2441, offset 0x00064498
	/* begin block 1 */
		// Start line: 2442
		// Start offset: 0x00064498
		// Variables:
	// 		int result; // $s2
	// 		long val1; // $s1
	// 		long val2; // $a1
	/* end block 1 */
	// End offset: 0x000645AC
	// End Line: 2492

	/* begin block 2 */
		// Start line: 7382
	/* end block 2 */
	// End Line: 7383

	/* begin block 3 */
		// Start line: 7383
	/* end block 3 */
	// End Line: 7384

// [D]
int MROperator(MR_THREAD *thread, ulong op)
{
    long val1;
    long val2;
    int result;
    
    result = 0;

    val1 = MRGetParam(thread);
    val2 = MRGetParam(thread);

    switch(op) 
	{
		case 0x3000003: // AND
			if (val1 != 0 && val2 != 0)
				result = 1;
			break;
		case 0x3000004:	// OR
			if (val1 != 0 || val2 != 0)
				result = 1;
			break;
		case 0x3000005:	// NEQ
			if (val1 != val2)
				result = 1;
			break;
		case 0x3000006:	// EQ
			if (val1 == val2)
				result = 1;
			break;
		case 0x3000007: // GT
			if(val1 > val2)
				result = 1;
			break;
		case 0x3000008:	// LT
			if (val1 < val2)
				result = 1;
			break;
		case 0x3000009: // ADD
			result = val1 + val2;
			break;
		default:
			return MRStopThread(thread);
    }

    MRPush(thread, result);
    return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ MRFunction(struct MR_THREAD *thread /*$s0*/, unsigned long fnc /*$a1*/)
 // line 2494, offset 0x000645ac
	/* begin block 1 */
		// Start line: 2495
		// Start offset: 0x000645AC
	/* end block 1 */
	// End offset: 0x00064614
	// End Line: 2511

	/* begin block 2 */
		// Start line: 7489
	/* end block 2 */
	// End Line: 7490

	/* begin block 3 */
		// Start line: 7492
	/* end block 3 */
	// End Line: 7493

	/* begin block 4 */
		// Start line: 7495
	/* end block 4 */
	// End Line: 7496

// [D]
int MRFunction(MR_THREAD *thread, ulong fnc)
{
	long value;

	if (fnc == 0x4000020) 
	{
		value = MRPop(thread);
		value = MRProcessTarget(thread, MissionTargets + value);

		MRPush(thread, value);

		return 1;
	}

	return MRStopThread(thread);
}



// decompiled code
// original method signature: 
// void /*$ra*/ MRInitialiseThread(struct MR_THREAD *thread /*$a0*/, unsigned long *pc /*$a1*/, unsigned char player /*$a2*/)
 // line 2514, offset 0x00064614
	/* begin block 1 */
		// Start line: 7538
	/* end block 1 */
	// End Line: 7539

	/* begin block 2 */
		// Start line: 7542
	/* end block 2 */
	// End Line: 7543

	/* begin block 3 */
		// Start line: 7545
	/* end block 3 */
	// End Line: 7546

// [D]
void MRInitialiseThread(MR_THREAD *thread, ulong *pc, unsigned char player)
{
	thread->active = 1;
	thread->pc = pc;
	thread->player = player;
	thread->sp = thread->initial_sp;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MRStartThread(struct MR_THREAD *callingthread /*$t0*/, unsigned long addr /*$a1*/, unsigned char player /*$a2*/)
 // line 2526, offset 0x00064630
	/* begin block 1 */
		// Start line: 2527
		// Start offset: 0x00064630
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x00064680
	// End Line: 2543

	/* begin block 2 */
		// Start line: 7561
	/* end block 2 */
	// End Line: 7562

	/* begin block 3 */
		// Start line: 7569
	/* end block 3 */
	// End Line: 7570

// [D]
void MRStartThread(MR_THREAD *callingthread, ulong addr, unsigned char player)
{
	for (int i = 0; i < 16; i++)
	{
		if (!MissionThreads[i].active)
		{
			MRInitialiseThread(&MissionThreads[i], callingthread->pc + addr, player);
			break;
		}
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ MRStopThread(struct MR_THREAD *thread /*$a0*/)
 // line 2545, offset 0x00064690
	/* begin block 1 */
		// Start line: 7613
	/* end block 1 */
	// End Line: 7614

	/* begin block 2 */
		// Start line: 7614
	/* end block 2 */
	// End Line: 7615

// [D]
int MRStopThread(MR_THREAD *thread)
{
	thread->active = 0;
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MRCommitThreadGenocide()
 // line 2551, offset 0x0006469c
	/* begin block 1 */
		// Start line: 2553
		// Start offset: 0x0006469C
		// Variables:
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x000646E0
	// End Line: 2557

	/* begin block 2 */
		// Start line: 7625
	/* end block 2 */
	// End Line: 7626

	/* begin block 3 */
		// Start line: 7626
	/* end block 3 */
	// End Line: 7627

	/* begin block 4 */
		// Start line: 7628
	/* end block 4 */
	// End Line: 7629

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void MRCommitThreadGenocide(void)
{
	for (int i = 0; i < 16; i++)
		MRStopThread(&MissionThreads[i]);
}



// decompiled code
// original method signature: 
// int /*$ra*/ MRJump(struct MR_THREAD *thread /*$a2*/, long jump /*$a1*/)
 // line 2560, offset 0x000646e0
	/* begin block 1 */
		// Start line: 7640
	/* end block 1 */
	// End Line: 7641

	/* begin block 2 */
		// Start line: 7644
	/* end block 2 */
	// End Line: 7645

// [D]
int MRJump(MR_THREAD *thread, long jump)
{
	if ((jump + 2u) < 3)
		return MRStopThread(thread);

	thread->pc += jump;
	return ~jump >> 0x1f;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MRPush(struct MR_THREAD *thread /*$a0*/, long value /*$a1*/)
 // line 2575, offset 0x0006472c
	/* begin block 1 */
		// Start line: 7678
	/* end block 1 */
	// End Line: 7679

	/* begin block 2 */
		// Start line: 7682
	/* end block 2 */
	// End Line: 7683

	/* begin block 3 */
		// Start line: 7688
	/* end block 3 */
	// End Line: 7689

// [D]
void MRPush(MR_THREAD *thread, long value)
{
	*thread->sp = value;
	thread->sp++;
}



// decompiled code
// original method signature: 
// long /*$ra*/ MRPop(struct MR_THREAD *thread /*$a0*/)
 // line 2585, offset 0x00064744
	/* begin block 1 */
		// Start line: 2586
		// Start offset: 0x00064744
	/* end block 1 */
	// End offset: 0x00064760
	// End Line: 2597

	/* begin block 2 */
		// Start line: 7702
	/* end block 2 */
	// End Line: 7703

	/* begin block 3 */
		// Start line: 7705
	/* end block 3 */
	// End Line: 7706

// [D]
long MRPop(MR_THREAD *thread)
{
	thread->sp--;
	return *thread->sp;
}



// decompiled code
// original method signature: 
// long /*$ra*/ MRGetParam(struct MR_THREAD *thread /*$s0*/)
 // line 2600, offset 0x00064760
	/* begin block 1 */
		// Start line: 2601
		// Start offset: 0x00064760
		// Variables:
	// 		long value; // $a1
	/* end block 1 */
	// End offset: 0x000647CC
	// End Line: 2620

	/* begin block 2 */
		// Start line: 7728
	/* end block 2 */
	// End Line: 7729

	/* begin block 3 */
		// Start line: 7732
	/* end block 3 */
	// End Line: 7733

// [D]
long MRGetParam(MR_THREAD *thread)
{
	long value;

	value = MRPop(thread);

	switch (value & 0xff000000)
	{
	case 0:
	case 0xff000000:
		return value;
	case 0x2000000:
		return MRGetVariable(thread, value);
	}
	
	return 0;
}



// decompiled code
// original method signature: 
// long /*$ra*/ MRGetVariable(struct MR_THREAD *thread /*$a2*/, unsigned long var /*$a1*/)
 // line 2622, offset 0x000647cc
	/* begin block 1 */
		// Start line: 7773
	/* end block 1 */
	// End Line: 7774

	/* begin block 2 */
		// Start line: 7776
	/* end block 2 */
	// End Line: 7777

	/* begin block 3 */
		// Start line: 7777
	/* end block 3 */
	// End Line: 7778

// [D]
long MRGetVariable(MR_THREAD *thread, ulong var)
{
	switch (var)
	{
	case 0x2000008: return Mission.timer[thread->player].count / 3000;
	case 0x2000100: return gCopDesiredSpeedScale;
	case 0x2000101: return gCopMaxPowerScale;
	case 0x2000102: return gMinimumCops;
	case 0x2000103: return maxCopCars;
	}
	
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MRSetVariable(struct MR_THREAD *thread /*$v1*/, unsigned long var /*$a1*/, long value /*$a2*/)
 // line 2648, offset 0x000648b0
	/* begin block 1 */
		// Start line: 7828
	/* end block 1 */
	// End Line: 7829

	/* begin block 2 */
		// Start line: 7829
	/* end block 2 */
	// End Line: 7830

// [D]
void MRSetVariable(MR_THREAD *thread, ulong var, long value)
{
	switch (var)
	{
	case 0x2000008:
		Mission.timer[thread->player].count = value * 3000;
		break;
	case 0x2000100:
		gCopDesiredSpeedScale = value;
		break;
	case 0x2000101:
		gCopMaxPowerScale = value;
		break;
	case 0x2000102:
		gMinimumCops = value;
		break;
	case 0x2000103:
		if (value == 4)
		{
			if (GameType == GAME_SURVIVAL)
			{
				gDontPingInCops = 0;
				gBatterPlayer = 1;
			}
			else
			{
				gDontPingInCops = 1;
				gBatterPlayer = 0;
			}
		}
		else
		{
			gDontPingInCops = 0;
			gBatterPlayer = 0;
		}

		if (value > 0)
			CopsAllowed = 1;

		maxCopCars = value;
		break;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ MRProcessTarget(struct MR_THREAD *thread /*$s7*/, struct _TARGET *target /*$s5*/)
 // line 2701, offset 0x00062470
	/* begin block 1 */
		// Start line: 2702
		// Start offset: 0x00062470
		// Variables:
	// 		struct VECTOR tv; // stack offset -96
	// 		struct VECTOR pv; // stack offset -80
	// 		int ret; // $fp
	// 		unsigned long dist; // $s6
	// 		int slot; // stack offset -48
	// 		int message; // $v0
	// 		int sample; // $a0

		/* begin block 1.1 */
			// Start line: 2859
			// Start offset: 0x000629BC
			// Variables:
		// 		unsigned long message; // $s1
		// 		unsigned long timer; // $s0
		// 		unsigned long delay; // $s2
		/* end block 1.1 */
		// End offset: 0x00062A2C
		// End Line: 2874

		/* begin block 1.2 */
			// Start line: 2934
			// Start offset: 0x00062BFC
			// Variables:
		// 		int direction; // $s0
		// 		long pos[4]; // stack offset -64
		// 		int *inform; // $s4
		// 		struct _CAR_DATA *cp; // $v0
		/* end block 1.2 */
		// End offset: 0x00062BFC
		// End Line: 2940

		/* begin block 1.3 */
			// Start line: 3069
			// Start offset: 0x00063028
			// Variables:
		// 		long pos[4]; // stack offset -64
		/* end block 1.3 */
		// End offset: 0x00063090
		// End Line: 3076

		/* begin block 1.4 */
			// Start line: 3104
			// Start offset: 0x0006319C
		/* end block 1.4 */
		// End offset: 0x0006319C
		// End Line: 3104

		/* begin block 1.5 */
			// Start line: 3135
			// Start offset: 0x00063254
		/* end block 1.5 */
		// End offset: 0x00063254
		// End Line: 3135

		/* begin block 1.6 */
			// Start line: 3158
			// Start offset: 0x00063318
		/* end block 1.6 */
		// End offset: 0x00063318
		// End Line: 3158
	/* end block 1 */
	// End offset: 0x00063728
	// End Line: 3294

	/* begin block 2 */
		// Start line: 5641
	/* end block 2 */
	// End Line: 5642

	/* begin block 3 */
		// Start line: 5904
	/* end block 3 */
	// End Line: 5905

	/* begin block 4 */
		// Start line: 5906
	/* end block 4 */
	// End Line: 5907

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Could not reconcile some variable overlaps */

// [D]
int MRProcessTarget(MR_THREAD *thread, _TARGET *target)
{
	int iVar3;
	int iVar4;
	int direction;
	uint uVar5;
	unsigned long dist;
	uint uVar9;
	int ret;
	VECTOR tv;
	VECTOR pv;
	long pos[4];
	int slot;
	int message;

	ret = 0;

	if (TargetComplete(target, thread->player)) 
		return 1;

	target->data[1] |= (thread->player == 0) ? 0x201 : 0xC00;

	pv.vx = player[thread->player].pos[0];
	pv.vy = player[thread->player].pos[1];
	pv.vz = player[thread->player].pos[2];

	direction = target->data[0];

	if (direction == 1)
	{
		if ((target->data[1] & 0x100000) != 0)
		{
			tv.vx = target->data[10];
			tv.vz = target->data[11];

			OffsetTarget(&tv);

			target->data[3] = tv.vx;
			target->data[4] = tv.vz;
		}
		else if ((target->data[1] & 0x200000) != 0)
		{
			target->data[1] &= ~0x200000;

			gStopCops.pos.vx = target->data[3];
			gStopCops.pos.vz = target->data[4];
			gStopCops.pos.vy = 0;
			gStopCops.radius = target->data[5];
		}
		else
		{
			tv.vx = target->data[3];
			tv.vz = target->data[4];
			tv.vy = 0;
		}

		if (target->data[5] < Long2DDistance(&tv, &pv))
		{
			target->data[9] &= ~0xFFF0;
		}
		else
		{
			if (target->data[7] != 0)
			{
				uVar9 = target->data[6] + pv.vy;
				uVar5 = -target->data[6] - pv.vy;

				if (-1 < uVar9)
					uVar5 = uVar9;

				if (target->data[7] < uVar5)
					target->data[9] &= ~0xFFF0;
			}

			switch (target->data[1] & 0x3000000)
			{
			case 0:
				if (GameType == GAME_SECRET)
				{
					playercollected[thread->player] |= 1;
					return 0;
				}
				break;
			case 0x1000000:
				playercollected[thread->player] |= 2;
				return 0;
			case 0x2000000:
				playercollected[thread->player] |= 4;
				return 0;
			case 0x3000000:
				if (playercollected[thread->player] == 7)
				{
					playercollected[thread->player] = 0;

					if (thread->player == 0)
					{
						gLapTimes[0][gPlayerScore.items++] = CalcLapTime(0, Mission.timer[0].count, gPlayerScore.items);

						if (gPlayerScore.items == gNumRaceTrackLaps)
							SetMissionComplete();
					}
					else
					{
						// [A] huh, is that first index supposed to be zero? :thonk:
						gLapTimes[0][gPlayerScore.P2items++] = CalcLapTime(1, Mission.timer[1].count, gPlayerScore.P2items);

						if (gPlayerScore.P2items == gNumRaceTrackLaps)
							SetMissionComplete();
					}
				}

				return 0;
			}

			switch (target->data[1] & 0x30000)
			{
			case 0:
				message = target->data[9];

				if (message != 0)
				{
					uVar9 = ((int)(message & 0xfff0) >> 4) + 1;

					if ((message & 0xf) <= uVar9 / 0x1e)
						SetPlayerMessage(thread->player, MissionStrings + ((int)message >> 0x10), 2, 0);

					target->data[9] = ((int)message >> 0x10) << 0x10 | uVar9 * 0x10 | message & 0xf;

					gTannerActionNeeded = 1;

					if (TannerActionHappening())
						ret = 1;
				}
				else
				{
					message = target->data[8];

					if ((message != -1) && copsAreInPursuit)
					{
						if ((Mission.message_timer[0] == 0) && !prevCopsInPursuit)
						{
							SetPlayerMessage(thread->player, &MissionStrings[message], 2, 2);
							prevCopsInPursuit = 1;
						}
					}
					else
					{
						ret = 1;
						prevCopsInPursuit = 0;
					}
				}
				
				if (ret == 0)
					return 0;

				if ((target->data[1] & 0x400000) != 0)
					return 1;

				if ((target->data[1] & 0x800000) != 0 && player[thread->player].playerType != 1)
					ret = 0;

				break;
			case 0x10000:
				if ((thread->player == 0) && (gPlayerWithTheFlag == 0))
				{
					gPlayerScore.items++;
					goto CnR_COMPLETE;
				}
				break;
			case 0x20000:
				if ((thread->player == 1) && (gPlayerWithTheFlag == 1))
				{
					gPlayerScore.P2items++;
					goto CnR_COMPLETE;
				}
				break;
			CnR_COMPLETE:
				gPlayerWithTheFlag = -1;
				SetPlayerMessage(thread->player, "Well done!", 2, 1);

				player[0].targetCarId = -1;
				player[1].targetCarId = -1;

				ActivateNextFlag();
				break;
			case 0x30000:
				if (gPlayerWithTheFlag == -1)
				{
					Mission.ChaseTarget = MissionTargets;
					gPlayerWithTheFlag = thread->player;

					SetPlayerMessage(thread->player, "You got the flag!", 2, 1);

					player[1 - gPlayerWithTheFlag].targetCarId = gPlayerWithTheFlag;
				}
				break;
			}
		}
	}
	else if (direction == 2)
	{
		tv.vx = target->data[3];
		tv.vz = target->data[4];
		tv.vy = 0;
		
		dist = Long2DDistance(&tv, &pv);
		
		slot = target->data[6];

		if (slot == -1)
		{
			if ((dist > TAIL_TOOFAR) || ((target->data[9] != 3 && ((target->data[10] & 1) != 0))))
			{
				MRCancelCarRequest(target);
			}
			else
			{
				MRRequestCar(target);
			}
		}
		else if ((target->data[1] & 0x40000000) == 0)
		{
			target->data[6] = -1;

			if (gCarWithABerm == slot)
				gCarWithABerm = -1;

			if (target->data[9] != 1)
			{
				SetPlayerMessage(thread->player, &MissionStrings[target->data[14]], 2, 2);
				SetMissionFailed(FAILED_MESSAGESET);
			}
		}
		else
		{
			direction = target->data[9];

			if (direction == 1)
			{
				if ((target->data[12] != 0) && (dist < target->data[12]))
				{
					_CAR_DATA *cp = &car_data[slot];
					int *inform = cp->inform;

					pos[0] = cp->hd.where.t[0];
					pos[1] = cp->hd.where.t[1];
					pos[2] = cp->hd.where.t[2];

					cp->inform = NULL;

					PingOutCar(cp);

					slot = CreateCivCarWotDrivesABitThenStops(cp->hd.direction, &pos, NULL, cp->ap.model, cp->ap.palette);

					car_data[slot].inform = inform;

					target->data[6] = slot;
					target->data[12] = 0;
				}
			}
			else if (direction == 3)
			{
				if ((target->data[1] & 0x20) != 0)
				{
					if ((target->data[10] & 4) != 0)
						gBombTargetVehicle = &car_data[slot];
				}
				else
				{
					if ((target->data[10] & 1) != 0)
					{
						if ((target->data[11] == -1) && !gInGameChaseActive)
						{
							Mission.ChaseTarget = NULL;
							player[0].targetCarId = -1;
							gBombTargetVehicle = NULL;

							if ((target->data[10] & 0xf0) != 0x20)
							{
								if ((target->data[10] & 0x10000) != 0)
								{
									SetCarToBeStolen(target, (uint)thread->player);
								}
								else
								{
									ret = 1;
								}
							}
						}
						else
						{
							if ((target->data[12] > dist) && ((MissionHeader->type & 4) == 0))
							{
								TriggerChase(&slot, target->data[11]);

								target->data[11] = -1;
								target->data[6] = slot;

								player[0].targetCarId = (char)slot;
								Mission.ChaseTarget = target;
							}
						}
					}
				}
			}

			target->data[3] = car_data[slot].hd.where.t[0];
			target->data[4] = car_data[slot].hd.where.t[2];

			if ((target->data[9] == 3 && (target->data[1] & 0x20) == 0) && (target->data[10] & 1) == 0)
			{
				if (car_data[slot].totalDamage >= target->data[13])
				{
					if (NewLeadDelay != 1)
					{
						DamageBar.position = target->data[13];

						car_data[slot].totalDamage = MaxPlayerDamage[0];

						SetConfusedCar(slot);

						if ((target->data[10] & 0x10000) != 0)
						{
							SetCarToBeStolen(target, thread->player);	
						}
						else
						{
							car_data[slot].totalDamage--;
							ret = 0;
						}

						NewLeadDelay = 1;
					}
					else
					{
						ret = 1;
					}
				}
			}
			else
			{
				switch (target->data[10] & 0xf0)
				{
				case 0:
					if (DamageBar.active == 0)
					{
						if (target->data[13] != 0)
						{
							if ((gCurrentMissionNumber != 2) && (gCurrentMissionNumber != 6))
								EnablePercentageBar(&DamageBar, target->data[13]);

							if (gCurrentMissionNumber == 11 || gCurrentMissionNumber == 13 || gCurrentMissionNumber == 26)
								target->data[13] = (target->data[13] * 3) / 4;
						}
					}

					if (target->data[13] < 1)
					{
						ReleaseInGameCutscene();

						player[0].targetCarId = -1;
						Mission.ChaseTarget = NULL;
						gBombTargetVehicle = NULL;

						SetConfusedCar(slot);

						if ((target->data[10] & 0x100000) != 0)
						{
							car_data[slot].controlFlags &= ~4;

							pos[0] = car_data[slot].hd.where.t[0];
							pos[2] = car_data[slot].hd.where.t[2];
							pos[1] = -car_data[slot].hd.where.t[1];

							CreatePedAtLocation(&pos, PED_ACTION_CIVWALK);
						}

						if ((target->data[10] & 0x10000) != 0)
						{
							SetCarToBeStolen(target, thread->player);

							if (gCurrentMissionNumber == 11 || gCurrentMissionNumber == 13 || gCurrentMissionNumber == 26)
							{
								car_data[slot].totalDamage = ((MaxPlayerDamage[0] * 3) / 4);
							}
							else
							{
								car_data[slot].totalDamage = MaxPlayerDamage[0];
							}

							DamageBar.active = 0;
						}
						else
						{
							ret = 1;
						}
					}

					if (dist > TAIL_TOOFAR)
					{
						SetPlayerMessage(thread->player, &MissionStrings[target->data[14]], 2, 2);
						SetMissionFailed(FAILED_MESSAGESET);
					}
					else if (dist > TAIL_GETTINGFAR)
					{
						direction = target->data[15];
						
						if (direction != 0xff && lastsay != TAIL_GETTINGFAR)
						{
							MissionSay(direction);
							lastsay = TAIL_GETTINGFAR;
						}
					}
					break;
				case 0x10:
					ProxyBar.active = 1;
					ProxyBar.position = dist;

					if (dist > TAIL_TOOCLOSE)
					{
						uVar5 = target->data[13] >> 12 & 0xfff;

						if (uVar5 != 0xfff)
							SetPlayerMessage(thread->player, MissionStrings + uVar5, 2, 1);

						SetMissionFailed(FAILED_MESSAGESET);
					}
					else if (dist > TAIL_GETTINGCLOSE)
					{
						uVar5 = target->data[13] & 0xfff;

						if (uVar5 != 0xfff)
							SetPlayerMessage(thread->player, MissionStrings + uVar5, 2, 1);

						direction = (int)*(char *)((int)target->data + 0x37); // WTF?

						if (direction != 0xff && lastsay != TAIL_GETTINGCLOSE)
						{
							MissionSay(direction);
							lastsay = TAIL_GETTINGCLOSE;
						}
					}
					else if (dist > TAIL_TOOFAR)
					{
						uVar5 = target->data[14] >> 12 & 0xfff;

						if (uVar5 != 0xfff)
							SetPlayerMessage(thread->player, MissionStrings + uVar5, 2, 1);

						SetMissionFailed(FAILED_MESSAGESET);
					}
					else if (dist > TAIL_GETTINGFAR)
					{
						uVar5 = target->data[14] & 0xfff;

						if (uVar5 != 0xfff)
							SetPlayerMessage(thread->player, MissionStrings + uVar5, 2, 1);

						direction = (int)*(char *)((int)target->data + 0x3b); // it must be wrong, isnt it?

						if (direction != 0xff && lastsay != TAIL_GETTINGFAR)
						{
							MissionSay(direction);
							lastsay = TAIL_GETTINGFAR;
						}
					}
					else if (dist > (TAIL_GETTINGCLOSE + 500))
					{
						if (dist < (TAIL_GETTINGFAR - 500))
							lastsay = -1;
					}

					break;
				case 0x20:
					break;
				case 0x30:
					if (gCurrentMissionNumber == 11 ||
						gCurrentMissionNumber == 14 ||
						gCurrentMissionNumber == 19 ||
						gCurrentMissionNumber == 28 ||
						car_data[slot].totalDamage < MaxPlayerDamage[0])
					{
						if (player[0].playerCarId == slot)
						{
							car_data[player[0].playerCarId].inform = NULL;

							if (gCurrentMissionNumber == 14 || gCurrentMissionNumber == 28)
								car_data[slot].totalDamage = MaxPlayerDamage[0];

							ret = 1;

							if (car_data[slot].totalDamage >= MaxPlayerDamage[0])
								gGotInStolenCar = 1;
						}
					}
					else
					{
						SetPlayerMessage(thread->player, &MissionStrings[MissionHeader->msgCarWrecked], 2, 1);
						SetMissionFailed(FAILED_MESSAGESET);
					}
					break;
				case 0x40:
					if (copsAreInPursuit)
						ret = 1;
					break;
				case 0x50:
					if ((target->data[1] & 0x20) != 0)
					{
						MaxPlayerDamage[1] = target->data[13];

						if (dist > TAIL_TOOFAR)
						{
							if (GameType == GAME_COPSANDROBBERS)
							{
								SetMissionFailed(FAILED_CnR_LOSTHIM);
							}
							else
							{
								SetPlayerMessage(thread->player, &MissionStrings[target->data[14]], 2, 2);
								SetMissionFailed(FAILED_MESSAGESET);
							}
						}
					}
					else
					{
						if (car_data[slot].totalDamage >= target->data[13])
							SetConfusedCar(slot);

						ret = 1;
					}
					break;
				}
			}
		}
	}
	else if (direction == 3)
	{
		if ((target->data[1] & 0x1000) != 0)
		{
			int message = target->data[14];

			if (message != -1 && Long2DDistance((VECTOR *)target->data[4], &pv) > 30000)
			{
				SetPlayerMessage(thread->player, &MissionStrings[message], 2, 2);
				SetMissionFailed(FAILED_MESSAGESET);
			}
		}
		else
		{
			target->data[4] = (int)TriggerEvent(target->data[3]);
			target->data[1] |= 0x1000;
		}
	}
	
	if (ret != 0)
	{
		target->data[1] &= 0x102; // [A] are these supposed to be permanently set?
		target->data[1] |= (thread->player == 0) ? 2 : 0x100 | 2;

		if (GameType == GAME_CHECKPOINT) 
		{
			if (thread->player == 0)
				gPlayerScore.items++;
			else
				gPlayerScore.P2items++;
		}
	}

	return ret;
}



// decompiled code
// original method signature: 
// int /*$ra*/ MRRequestCar(struct _TARGET *target /*$a0*/)
 // line 3296, offset 0x000649e4
	/* begin block 1 */
		// Start line: 9124
	/* end block 1 */
	// End Line: 9125

	/* begin block 2 */
		// Start line: 9125
	/* end block 2 */
	// End Line: 9126

// [D]
int MRRequestCar(_TARGET *target)
{
	if (Mission.CarTarget == NULL && GameType != GAME_SURVIVAL) 
	{
		Mission.CarTarget = target;
		return 1;
	}
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MRHandleCarRequests()
 // line 3305, offset 0x00064a24
	/* begin block 1 */
		// Start line: 9142
	/* end block 1 */
	// End Line: 9143

	/* begin block 2 */
		// Start line: 9143
	/* end block 2 */
	// End Line: 9144

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void MRHandleCarRequests(void)
{
	if (Mission.CarTarget)
		MRCreateCar(Mission.CarTarget);
}



// decompiled code
// original method signature: 
// int /*$ra*/ MRCreateCar(struct _TARGET *target /*$s1*/)
 // line 3311, offset 0x00063728
	/* begin block 1 */
		// Start line: 3312
		// Start offset: 0x00063728
		// Variables:
	// 		long pos[4]; // stack offset -64
	// 		int actAsCop; // $s2
	// 		int damaged; // $s7
	// 		int model; // $s4
	// 		int palette; // $s5
	// 		int dir; // $s3
	// 		int rot; // $a2
	// 		int id; // $s0
	// 		char playerid; // stack offset -48
	/* end block 1 */
	// End offset: 0x000639A0
	// End Line: 3390

	/* begin block 2 */
		// Start line: 7197
	/* end block 2 */
	// End Line: 7198

	/* begin block 3 */
		// Start line: 7215
	/* end block 3 */
	// End Line: 7216

// [D]
int MRCreateCar(_TARGET *target)
{
	bool bVar1;
	int curslot;
	uint uVar2;
	int newslot;
	long lVar3;
	int direction;
	uint uVar4;
	uint uVar5;
	long pos[4];
	char playerid;

	pos[0] = target->data[3];
	pos[2] = target->data[4];
	pos[1] = 10000;

	uVar2 = target->data[10];
	
	bVar1 = (uVar2 & 8) != 0;
	direction = target->data[5];
	uVar4 = target->data[7];
	uVar5 = target->data[8];

	if (target->data[9] == 2) 
	{
		curslot = PingInCivCar(666);
		curslot--;
	}
	else
	{
		curslot = CreateStationaryCivCar(direction, 0, (uint)((uVar2 & 0x40000) != 0) << 10, (long(*)[4])pos, target->data[7], target->data[8], (uint)bVar1);
	}

	if (curslot < 0)
	{
		requestStationaryCivCar = 1;
		direction = 0;
	}
	else 
	{
		if (bVar1)
		{
			newslot = NumReplayStreams + cop_adjust;
			cop_adjust++;
			curslot = Swap2Cars(curslot, newslot);
		}

		Mission.CarTarget = NULL;
		requestStationaryCivCar = 0;

		if ((target->data[9] == 3) && ((target->data[10] & 1U) == 0))
		{
			playerid = 0xff;

			InitPlayer((_PLAYER *)(player + 1), car_data + curslot, 4, direction, (long(*)[4])pos, target->data[7], target->data[8], (char *)&playerid);

			EnablePercentageBar(&DamageBar, target->data[0xd]);
			NewLeadDelay = 0;
		}

		target->data[3] = car_data[curslot].hd.where.t[0];
		target->data[6] = curslot;
		target->data[1] = target->data[1] | 0x40000000;
		target->data[4] = car_data[curslot].hd.where.t[2];

		car_data[curslot].inform = target->data + 1;

		if ((uVar2 & 0x80000) != 0)
		{
			car_data[curslot].totalDamage = 0xffff;
			car_data[curslot].ap.damage[0] = 0xfff;
			car_data[curslot].ap.damage[1] = 0xfff;
			car_data[curslot].ap.damage[2] = 0xfff;
			car_data[curslot].ap.damage[3] = 0xfff;
			car_data[curslot].ap.damage[4] = 0xfff;
			car_data[curslot].ap.damage[5] = 0xfff;
			car_data[curslot].ap.needsDenting = 1;
		}

		direction = 1;

		if ((target->data[10] & 0x200000U) != 0) 
			gCarWithABerm = curslot;
	}

	return direction;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MRCancelCarRequest(struct _TARGET *target /*$a0*/)
 // line 3392, offset 0x00064a50
	/* begin block 1 */
		// Start line: 9316
	/* end block 1 */
	// End Line: 9317

	/* begin block 2 */
		// Start line: 9317
	/* end block 2 */
	// End Line: 9318

// [D]
void MRCancelCarRequest(_TARGET *target)
{
	if (Mission.CarTarget == target)
		Mission.CarTarget = NULL;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PreProcessTargets()
 // line 3398, offset 0x000639a0
	/* begin block 1 */
		// Start line: 3400
		// Start offset: 0x000639A0
		// Variables:
	// 		struct _TARGET *target; // $s0
	// 		int i; // $s1
	/* end block 1 */
	// End offset: 0x00063B78
	// End Line: 3450

	/* begin block 2 */
		// Start line: 7449
	/* end block 2 */
	// End Line: 7450

	/* begin block 3 */
		// Start line: 7458
	/* end block 3 */
	// End Line: 7459

	/* begin block 4 */
		// Start line: 7459
	/* end block 4 */
	// End Line: 7460

	/* begin block 5 */
		// Start line: 7462
	/* end block 5 */
	// End Line: 7463

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void PreProcessTargets(void)
{
	int iVar1;
	_TARGET *target;
	int i;

	for (i = 0; i < MissionHeader->nCutscenes; i++)
	{
		PreLoadInGameCutscene(i);
	}

	i = 15;

	target = MissionTargets;
	do {
		iVar1 = target->data[0];

		if (iVar1 == 4) 
		{
		LAB_00063a48:
			PlayerStartInfo[1] = &ReplayStreams[1].SourceType;

			ReplayStreams[1].SourceType.type = 1;
			ReplayStreams[1].SourceType.model = target->data[7];
			ReplayStreams[1].SourceType.palette = target->data[8];
			ReplayStreams[1].SourceType.controlType = 1;
			ReplayStreams[1].SourceType.flags = 0;
			ReplayStreams[1].SourceType.rotation = target->data[5];
			ReplayStreams[1].SourceType.position.vx = target->data[3];
			ReplayStreams[1].SourceType.position.vy = 0;
			ReplayStreams[1].SourceType.position.vz = target->data[4];

			if ((target->data[9] & 3U) != 0)
				target->data[11] = -1;
	
			target->data[6] = 1;
			target->data[1] |= 0x40000000;
		}
		else if (iVar1 == 2)
		{
			if ((target->data[1] & 0x20U) != 0) 
				goto LAB_00063a48;

			if ((target->data[9] == 3) && ((target->data[10] & 1U) != 0)) 
			{
				PreLoadInGameCutscene(gRandomChase);
			}
		}
		else if (iVar1 == 1)
		{
			if ((target->data[1] & 0x30000U) == 0x30000)
			{
				target->data[1] |= 0x102;
			}

			if ((target->data[1] & 0x100000U) != 0) 
			{
				target->data[10] = target->data[3];
				target->data[11] = target->data[4];
			}
		}

		i--;
		target++;

		if (i < 0)
			return;
	
	} while (true);
}



// decompiled code
// original method signature: 
// int /*$ra*/ Handle321Go()
 // line 3452, offset 0x00064a74
	/* begin block 1 */
		// Start line: 3454
		// Start offset: 0x00064A74
	/* end block 1 */
	// End offset: 0x00064AD0
	// End Line: 3467

	/* begin block 2 */
		// Start line: 9436
	/* end block 2 */
	// End Line: 9437

	/* begin block 3 */
		// Start line: 9437
	/* end block 3 */
	// End Line: 9438

	/* begin block 4 */
		// Start line: 9439
	/* end block 4 */
	// End Line: 9440

/* WARNING: Unknown calling convention yet parameter storage is locked */

extern int gStopPadReads;

// [D]
int Handle321Go(void)
{
	if ((MissionHeader->type & 4) != 0) 
	{
		gStopPadReads = 1;
		
		if (++g321GoDelay == 96) 
		{
			gStopPadReads = 0;
			MissionHeader->type &= ~4;
		}

		return 1;
	}
	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ HandleGameOver()
 // line 3469, offset 0x00063b78
	/* begin block 1 */
		// Start line: 3472
		// Start offset: 0x00063B78

		/* begin block 1.1 */
			// Start line: 3474
			// Start offset: 0x00063BB8
			// Variables:
		// 		struct _PLAYER *lp; // $s0
		// 		struct _CAR_DATA *cp; // $a2
		// 		int i; // $s2
		// 		int playersdead; // $s3

			/* begin block 1.1.1 */
				// Start line: 3510
				// Start offset: 0x00063CE4
				// Variables:
			// 		int surfInd; // $v1
			/* end block 1.1.1 */
			// End offset: 0x00063D7C
			// End Line: 3522
		/* end block 1.1 */
		// End offset: 0x00063EE4
		// End Line: 3565
	/* end block 1 */
	// End offset: 0x00063F84
	// End Line: 3589

	/* begin block 2 */
		// Start line: 7627
	/* end block 2 */
	// End Line: 7628

	/* begin block 3 */
		// Start line: 7647
	/* end block 3 */
	// End Line: 7648

	/* begin block 4 */
		// Start line: 7649
	/* end block 4 */
	// End Line: 7650

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Unknown calling convention yet parameter storage is locked */

extern int test42;	// why 42?

// [D]
int HandleGameOver(void)
{
	uint uVar2;
	int iVar3;
	int player_id;
	uint uVar4;

	_PLAYER* lp;
	_CAR_DATA *cp;

	int iVar6;

	if (Mission.gameover_delay != -1) 
	{
		gStopPadReads = 1;

		if (Mission.gameover_delay != 0)
		{
			gStopPadReads = 1;
			Mission.gameover_delay--;
			return 0;
		}

		if (Mission.message_timer[0] == 0) 
		{
			if (Mission.message_timer[1] == 0) 
			{
				if (Mission.gameover_mode == PAUSEMODE_COMPLETE)
				{
					StoreEndData();
#ifndef PSX
					SaveCurrentGame();
#endif
				}

				EnablePause(Mission.gameover_mode);
				return 1;
			}

			gStopPadReads = 1;
			return 0;
		}

		gStopPadReads = 1;
		return 0;
	}

	player_id = 0;
	uVar2 = (uint)NumPlayers;
	uVar4 = 0;

	if (NumPlayers != 0)
	{
		do {
			lp = &player[player_id];

			if (lp->playerType == 1)
			{
				if ((Mission.timer[0].flags & 0x10) != 0 || TannerStuckInCar(0, player_id) != 0)
				{
					iVar3 = lp->playerCarId;

					if (MaxPlayerDamage[player_id] <= car_data[iVar3].totalDamage && lp->dying == 0)
					{
						lp->dying = 1;
					}

					if (car_data[iVar3].hd.where.m[1][1] < 100) 
					{
						lp->upsideDown++;

						if (0xb4 < lp->upsideDown)
						{
							car_data[iVar3].totalDamage = MaxPlayerDamage[player_id];

							if(lp->dying < 30)
								lp->dying = 30;
						}
					}
					else 
					{
						lp->upsideDown = 0;
					}
				}
			}
			else
			{
				if (lp->playerType == 2)
				{
					test42 = GetSurfaceIndex((VECTOR *)lp->pos);

					if (((test42 == -26) || (test42 == -23)) &&(lp->dying == '\0'))
					{
						if ((GameLevel == 3) && (gCurrentMissionNumber != 0x23))
							tannerDeathTimer = tannerDeathTimer + 1;
						else 
							tannerDeathTimer = 0x40;
					}
					else
						tannerDeathTimer = 0;
				}
			}
			if (tannerDeathTimer == 64)
				lp->dying = 1;

			if (lp->dying != 0)
			{
				if (gGotInStolenCar == 0) 
				{
					if ((Mission.timer[player_id].flags & 0x10) != 0)
						BombThePlayerToHellAndBack(gCarWithABerm);

					if (lp->playerType == 2) 
						SetPlayerMessage(player_id, MissionStrings + MissionHeader->msgDrowned, 2, 2);
					else 
						SetPlayerMessage(player_id, MissionStrings + MissionHeader->msgCarWrecked, 2, 2);

					lp->dying++;
				}
			}

			if (0x28 < lp->dying)
				uVar4 = uVar4 + 1;

			player_id++;

		} while (player_id < NumPlayers);
	}

	if (uVar4 == 0)
		return 0;

	if (GameType == GAME_CHECKPOINT) 
	{
	LAB_00063eb0:
		if (NumPlayers != 1)
		{
			if (uVar4 != uVar2) 
				return 0;

			goto LAB_00063ee4;
		}
	}
	else 
	{
		if (GameType < GAME_TRAILBLAZER) 
		{
			if (GameType == GAME_TAKEADRIVE) 
				goto LAB_00063eb0;
		}
		else
		{
			if (GameType == GAME_SECRET) 
				goto LAB_00063eb0;
		}
	}

	if (TannerStuckInCar(0, 0) == 0)
		return 0;

LAB_00063ee4:
	SetMissionOver(PAUSEMODE_GAMEOVER);
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CompleteAllActiveTargets(int player /*$a0*/)
 // line 3591, offset 0x00064ad0
	/* begin block 1 */
		// Start line: 3593
		// Start offset: 0x00064AD0
		// Variables:
	// 		int i; // $a1
	// 		int flag1; // $a3
	// 		int flag2; // $a2
	/* end block 1 */
	// End offset: 0x00064B38
	// End Line: 3621

	/* begin block 2 */
		// Start line: 9591
	/* end block 2 */
	// End Line: 9592

	/* begin block 3 */
		// Start line: 9716
	/* end block 3 */
	// End Line: 9717

	/* begin block 4 */
		// Start line: 9717
	/* end block 4 */
	// End Line: 9718

	/* begin block 5 */
		// Start line: 9719
	/* end block 5 */
	// End Line: 9720

// [D]
void CompleteAllActiveTargets(int player)
{
	_TARGET *p_Var1;
	int iVar2;
	uint uVar3;
	uint uVar4;

	uVar4 = 0x800;

	if (player == 0) 
	{
		uVar4 = 1;
		uVar3 = 2;
	}
	else 
		uVar3 = 256;

	iVar2 = 15;
	p_Var1 = MissionTargets;
	do {
		if ((p_Var1->data[0] < 4) && (0 < p_Var1->data[0]) && (p_Var1->data[1] & uVar4) != 0) 
			p_Var1->data[1] |= uVar3;

		iVar2--;
		p_Var1++;
	} while (-1 < iVar2);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetMissionComplete()
 // line 3623, offset 0x00063f84
	/* begin block 1 */
		// Start line: 7986
	/* end block 1 */
	// End Line: 7987

	/* begin block 2 */
		// Start line: 8021
	/* end block 2 */
	// End Line: 8022

	/* begin block 3 */
		// Start line: 8022
	/* end block 3 */
	// End Line: 8023

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void SetMissionComplete(void)
{
	int iVar1;

	switch (GameType) 
	{
	case GAME_MISSION:
		if ((Mission.timer[0].flags & 0x10) != 0)
		{
			Mission.timer[0].flags = Mission.timer[0].flags | 0x20;
			DetonatorTimer();
			return;
		}

		if (gFurthestMission < gCurrentMissionNumber) 
		{
			gFurthestMission = gCurrentMissionNumber;
		}

	default:
		SetMissionMessage(MissionStrings + MissionHeader->msgComplete, 3, 2);
		break;
	case GAME_CHECKPOINT:
	case GAME_CAPTURETHEFLAG:
	case GAME_SECRET:
		if (NumPlayers < 2) 
		{
			SetMissionMessage(MissionStrings + MissionHeader->msgComplete, 3, 2);
			break;
		}

		if (gPlayerScore.P2items <= gPlayerScore.items)
		{
			if (gPlayerScore.P2items == gPlayerScore.items)
			{
				SetPlayerMessage(0, "Draw!", 3, 2);
				SetPlayerMessage(1, "Draw!", 3, 2);
				break;
			}

			goto LAB_000640bc;
		}

		SetPlayerMessage(0, MissionStrings + MissionHeader->msgDrowned, 3, 2);
		iVar1 = MissionHeader->msgComplete;

		goto LAB_000640ec;
	case GAME_COPSANDROBBERS:
		if (Player2DamageBar.position < Player2DamageBar.max)
		{
			SetPlayerMessage(0, MissionStrings + MissionHeader->msgDrowned, 3, 2);
			iVar1 = MissionHeader->msgComplete;
		}
		else 
		{
	LAB_000640bc:
			SetPlayerMessage(0, MissionStrings + MissionHeader->msgComplete, 3, 2);
			iVar1 = MissionHeader->msgDrowned;
		}
	LAB_000640ec:
		SetPlayerMessage(1, MissionStrings + iVar1, 3, 2);
	}

	SetMissionOver(PAUSEMODE_COMPLETE);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetMissionFailed(enum FAIL_REASON reason /*$a0*/)
 // line 3684, offset 0x00064b38
	/* begin block 1 */
		// Start line: 9846
	/* end block 1 */
	// End Line: 9847

	/* begin block 2 */
		// Start line: 9910
	/* end block 2 */
	// End Line: 9911

// [D]
void SetMissionFailed(FAIL_REASON reason)
{
	switch (reason)
	{
	case FAILED_OUTOFTIME:
		SetMissionMessage(&MissionStrings[MissionHeader->msgOutOfTime], 3, 2);
		break;
	case FAILED_CnR_LOSTHIM:
		SetPlayerMessage(0, &MissionStrings[MissionHeader->msgDrowned], 3, 2);
		SetPlayerMessage(1, &MissionStrings[MissionHeader->msgComplete], 3, 2);
		break;
	case FAILED_MESSAGESET:
		SetMissionOver(PAUSEMODE_GAMEOVER);
		break;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetMissionOver(enum PAUSEMODE mode /*$a0*/)
 // line 3704, offset 0x00064bd8
	/* begin block 1 */
		// Start line: 9950
	/* end block 1 */
	// End Line: 9951


// [D]
void SetMissionOver(PAUSEMODE mode)
{
	ReleaseInGameCutscene();
	PauseMissionTimer(1);

	gBombTargetVehicle = NULL;

	Mission.gameover_delay = 0x3c;
	Mission.gameover_mode = mode;
	Mission.ChaseTarget = NULL;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ActivateNextFlag()
 // line 3716, offset 0x000641a8
	/* begin block 1 */
		// Start line: 3718
		// Start offset: 0x000641A8
		// Variables:
	// 		int i; // $a3
	// 		int j; // $a1
	/* end block 1 */
	// End offset: 0x00064268
	// End Line: 3739

	/* begin block 2 */
		// Start line: 8207
	/* end block 2 */
	// End Line: 8208

	/* begin block 3 */
		// Start line: 8208
	/* end block 3 */
	// End Line: 8209

	/* begin block 4 */
		// Start line: 8211
	/* end block 4 */
	// End Line: 8212

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void ActivateNextFlag(void)
{
	int iVar1;
	_TARGET *target;
	int iVar3;
	int iVar4;

	if (last_flag == -1)
		last_flag = 0;
	else
		MissionTargets[last_flag].data[1] |= 0x102;

	iVar4 = 0;
	iVar3 = last_flag;

	while (true) 
	{
		iVar3 = iVar3 + 1;
		iVar1 = iVar3;

		if (iVar3 < 0) 
		{
			iVar1 = iVar4 + last_flag + 0x10;
		}

		iVar1 = iVar3 + (iVar1 >> 4) * -0x10;
		target = MissionTargets + iVar1;

		if ((target->data[0] == 1) && ((target->data[1] & 0x30000U) == 0x30000))
			break;

		iVar4++;

		if (0xf < iVar4) 
			return;
	}

	target->data[1] = target->data[1] & 0xfffffefd;
	last_flag = iVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CalcLapTime(int player /*$a0*/, int time /*$a1*/, int lap /*$a2*/)
 // line 3760, offset 0x00064c24
	/* begin block 1 */
		// Start line: 3761
		// Start offset: 0x00064C24
		// Variables:
	// 		int i; // $a2
	// 		int ptime; // $a3
	/* end block 1 */
	// End offset: 0x00064C60
	// End Line: 3768

	/* begin block 2 */
		// Start line: 10067
	/* end block 2 */
	// End Line: 10068

	/* begin block 3 */
		// Start line: 10070
	/* end block 3 */
	// End Line: 10071

// [D]
int CalcLapTime(int player, int time, int lap)
{
	int i;
	int ptime;

	ptime = 0;

	if (0 < lap) 
	{
		do {
			ptime += gLapTimes[player][lap];
			lap--;
		} while (lap != 0);
	}

	return time - ptime;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetCarToBeStolen(struct _TARGET *target /*$s0*/, int player /*$s1*/)
 // line 3770, offset 0x00064c60
	/* begin block 1 */
		// Start line: 10085
	/* end block 1 */
	// End Line: 10086

	/* begin block 2 */
		// Start line: 10088
	/* end block 2 */
	// End Line: 10089

// [D]
void SetCarToBeStolen(_TARGET *target, int player)
{
	if ((target->data[10] & 0x800000U) != 0)
		MakePhantomCarEqualPlayerCar();

	target->data[9] = 1;
	target->data[10] = 48;
	target->data[12] = 0;

	SetPlayerMessage(player, Mission.StealMessage, 2, 2);
}



// decompiled code
// original method signature: 
// void /*$ra*/ MakePhantomCarEqualPlayerCar()
 // line 3781, offset 0x00064cd0
	/* begin block 1 */
		// Start line: 10113
	/* end block 1 */
	// End Line: 10114

	/* begin block 2 */
		// Start line: 10114
	/* end block 2 */
	// End Line: 10115

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void MakePhantomCarEqualPlayerCar(void)
{
	if (player[0].playerType == 1)
		Mission.PhantomCarId = player[0].playerCarId;
}
