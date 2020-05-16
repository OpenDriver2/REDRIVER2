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

int gCopDifficultyLevel = 0;

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
int CopsAllowed = 0;
int MaxPlayerDamage[2] = { 0x1f40 };
int prevCopsInPursuit = 0;
int gPlayerWithTheFlag = -1;
int g321GoDelay = 0;

int last_flag = -1;
int cop_adjust = 0;

int gLapTimes[5][2];
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

int TAIL_GETTINGCLOSE = 7000;
int TAIL_GETTINGFAR = 12900;
int TAIL_TOOCLOSE = 4000;
int TAIL_TOOFAR = 15900;

// [D]
void InitialiseMissionDefaults(void)
{
	int i;

	if ((NumPlayers == 2) || (GAME_TAKEADRIVE < GameType)) {
		lockAllTheDoors = '\x01';
	}
	else {
		lockAllTheDoors = '\0';
	}

	maxPlayerCars = 1;
	maxCivCars = 0xe;
	maxParkedCars = 7;
	maxCopCars = 4;
	gPlayerDamageFactor = 0x1000;
	requestStationaryCivCar = 0;
	numPlayerCars = 0;
	numCivCars = 0;
	numParkedCars = 0;
	numCopCars = 0;
	gMinimumCops = 0;
	gCopDesiredSpeedScale = 0x1000;
	gCopMaxPowerScale = 0x1000;
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

	ClearMem((char *)&Mission, 0x48);

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
		gLapTimes[i][0] = -1;
		gLapTimes[i][1] = -1;
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
LEAD_PARAMETERS LeadValues;

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
	char acStack64[32];
	unsigned long header;

	InitialiseMissionDefaults();

	MALLOC_BEGIN();

	if (NewLevel != 0) 
		MissionLoadAddress = (_MISSION *)mallocptr;

	sprintf(acStack64, "MISSIONS\\MISSIONS.BLK");

	iVar4 = FileExists(acStack64);

	if (iVar4 == 0)
	{
		return;
	}
	LoadfileSeg(acStack64, (char*)&header, missionnum << 2, 4);

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
	LoadfileSeg(acStack64, (char *)MissionLoadAddress, header & 0x7ffff, sizeof(_MISSION));

	MissionHeader = MissionLoadAddress;
	MissionTargets = (_TARGET *)((int)&MissionLoadAddress->id + MissionLoadAddress->size);
	MissionScript = (ulong *)(MissionTargets + 0x10);
	MissionStrings = (char *)(((_TARGET *)MissionScript)->data + MissionLoadAddress->strings);

	if ((MissionLoadAddress->route != 0) && (NewLevel == 0))
	{
		loadsize = (int)MissionStrings + (MissionLoadAddress->route - (int)MissionLoadAddress);
	}

	iVar4 = LoadfileSeg(acStack64, (char *)MissionLoadAddress, header & 0x7ffff, loadsize);

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

	piVar6 = &MissionHeader->region;
	bVar1 = *piVar6 == 0;
	MissionHeader->id = 0;
	p_Var3 = MissionHeader;
	if (!bVar1) {
		multiplayerregions[1] = -1;
		multiplayerregions[2] = -1;
		multiplayerregions[3] = -1;
		multiplayerregions[0] = *piVar6;
	}
	gMultiplayerLevels = (!bVar1);
	doSpooling = (bVar1);
	Mission.active = 1;
	GameLevel = MissionHeader->city;

	PlayerStartInfo[0]->position.vx = MissionHeader->playerStartPosition.x;
	PlayerStartInfo[0]->rotation = p_Var3->playerStartRotation;
	PlayerStartInfo[0]->position.vz = p_Var3->playerStartPosition.y;
	PlayerStartInfo[0]->model = p_Var3->playerCarModel;
	PlayerStartInfo[0]->palette = MissionHeader->playerCarColour;

	if (MissionHeader->maxDamage != 0) {
		MaxPlayerDamage[1] = MissionHeader->maxDamage;
		MaxPlayerDamage[0] = MissionHeader->maxDamage;
	}
	gTimeOfDay = MissionHeader->time;
	gWeather = MissionHeader->weather;
	if ((((gTimeOfDay == 1) || (gTimeOfDay < 2)) || (gTimeOfDay == 2)) || (gTimeOfDay != 3)) {
		gNight = 0;
	}
	else {
		gNight = 1;
	}
	if (MissionHeader->weather == 1) {
		gRainCount = 30;
		gEffectsTimer = 41;
	}
	else {
		gRainCount = 0;
		gEffectsTimer = 0;
	}
	Mission.timer[0].flags = '\0';
	Mission.timer[0].x = 0x7c;
	Mission.timer[1].x = 0x7c;
	Mission.timer[0].y = 0x10;
	Mission.timer[0].count = 0;
	Mission.timer[1].y = 0x88;
	Mission.timer[1].flags = '\0';
	Mission.timer[1].count = 0;
	sVar2 = MissionHeader->timer;
	if (((int)sVar2 != 0) || (((int)MissionHeader->timerFlags & 0x8000U) != 0)) {
		bVar7 = 1;
		if (((int)MissionHeader->timerFlags & 0x8000U) != 0) {
			bVar7 = 3;
		}
		if ((MissionHeader->timerFlags & 0x4000U) != 0) {
			bVar7 = bVar7 | 8;
		}
		if ((MissionHeader->timerFlags & 0x2000U) != 0) {
			bVar7 = bVar7 | 0x10;
		}
		loadsize = (uint)NumPlayers;
		if (NumPlayers != 0) {
			plVar9 = &Mission.timer[0].count;
			do {
				*(char *)(plVar9 + -1) = bVar7;
				*plVar9 = (int)sVar2 * 3000;
				loadsize = loadsize - 1;
				plVar9 = plVar9 + 3;
			} while (loadsize != 0);
		}
	}
	gMinimumCops = (MissionHeader->cops).min;
	maxCopCars = (MissionHeader->cops).max;
	if (maxCopCars == 4) {
		if (GameType == GAME_SURVIVAL) {
			gDontPingInCops = 0;
			gBatterPlayer = 1;
			goto LAB_00060e70;
		}
		gDontPingInCops = 1;
	}
	else {
		gDontPingInCops = 0;
	}
	gBatterPlayer = 0;
LAB_00060e70:
	gCopDesiredSpeedScale = (MissionHeader->cops).speed;
	gCopMaxPowerScale = (MissionHeader->cops).power;
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
		PlayerStartInfo[0]->type = '\x01';
	}
	else
	{
		PlayerStartInfo[0]->type = '\x02';
		PlayerStartInfo[0]->model = '\0';
	}

	if (NewLevel != 0) {
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

	sprintf(acStack64, "MISSIONS\\PATH%d.%d", gCurrentMissionNumber, 0);
	iVar4 = FileExists(acStack64);
	if (iVar4 != 0) {
		LoadfileSeg(acStack64, (char *)(MissionTargets + 4), 0, 0x280);
	}
	if ((MissionHeader->type & 1U) != 0) {
		RestoreStartData();
	}
	PreProcessTargets();
	if (gCurrentMissionNumber - 1U < 0x28) {
		loadsize = gCurrentMissionNumber;
		if (0x24 < gCurrentMissionNumber) {
			loadsize = gCurrentMissionNumber - 1U;
		}
		if (0xb < (int)loadsize) {
			loadsize = loadsize - 1;
		}
		if (7 < (int)loadsize) {
			loadsize = loadsize - 1;
		}
		gMissionTitle = MissionName[loadsize - 1];
	}
	else {
		gMissionTitle = NULL;
	}
	if (wantedCar[0] != -1) 
	{
		PlayerStartInfo[0]->model = wantedCar[0];

		if ((wantedCar[0] == 0) || (4 < wantedCar[0])) 
		{
			PlayerStartInfo[0]->palette = '\0';

			if (3 < wantedCar[0])
			{
				MissionHeader->residentModels[4] = wantedCar[0];
			}
		}
		else {
			MissionHeader->residentModels[0] = wantedCar[0];
		}
	}

	if (wantedCar[1] != -1)
	{
		PlayerStartInfo[1]->model = wantedCar[1];

		if ((wantedCar[1] == 0) || (4 < wantedCar[1]))
		{
			PlayerStartInfo[1]->palette = '\0';
		}
		else
		{
			MissionHeader->residentModels[1] = wantedCar[1];
		}
	}

	if (GameType == GAME_CAPTURETHEFLAG)
		ActivateNextFlag();

	MRInitialiseThread((MR_THREAD *)&MissionThreads, MissionScript, '\0');
	return;
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

	if (Mission.active == 0) {
		return;
	}
	if (gInGameCutsceneActive != 0) {
		return;
	}
	if (gInGameCutsceneDelay != 0) {
		return;
	}
	if (CameraCnt != 0) 
		goto LAB_00061388;

	if ((MissionHeader->type & 4U) != 0) {
		HandleMissionThreads();
		Mission.message_timer[0] = 0;
		Mission.message_timer[1] = 0;
		MRCommitThreadGenocide();
		MRInitialiseThread(MissionThreads, MissionScript, '\0');
	}

	uVar2 = MissionHeader->type & 0x30;
	if (uVar2 != 0x10) {
		if (uVar2 < 0x11) {
			if (uVar2 == 0) {
				FelonyBar.active = 1;
			}
			else {
				FelonyBar.active = 0;
			}
			goto LAB_00061388;
		}
		if (uVar2 == 0x20) {
			FelonyBar.active = 1;
			FelonyBar.flags = FelonyBar.flags | 2;
			goto LAB_00061388;
		}
	}
	FelonyBar.active = 0;

LAB_00061388:

	MRHandleCarRequests();

	if (((bMissionTitleFade == 0) && (iVar1 = Handle321Go(), iVar1 == 0)) && (iVar1 = HandleGameOver(), iVar1 == 0))
	{
		if (Mission.message_timer[0] != 0) {
			Mission.message_timer[0] = Mission.message_timer[0] + -1;
		}
		if (Mission.message_timer[1] != 0) {
			Mission.message_timer[1] = Mission.message_timer[1] + -1;
		}
		if (Mission.ChaseHitDelay != 0) {
			Mission.ChaseHitDelay = Mission.ChaseHitDelay + -1;
		}

		gTannerActionNeeded = 0;

		HandleTimer(Mission.timer);
		HandleTimer(Mission.timer + 1);
		HandleThrownBombs();
		HandleMissionThreads();

		if (gCopCarTheftAttempted != 0) {
			SetMissionMessage(MissionStrings + MissionHeader->msgPoliceCar, 2, 1);
			gCopCarTheftAttempted = 0;
		}

		if ((gLockPickingAttempted != 0) && (NumPlayers == 1)) {
			SetMissionMessage(MissionStrings + MissionHeader->msgDoorsLocked, 2, 1);
			gLockPickingAttempted = 0;
		}
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
	if ((bVar1 & 4) != 0) {
		return;
	}
	if ((bVar1 & 1) == 0) {
		return;
	}
	if ((bVar1 & 2) == 0) {
		iVar3 = timer->count + -100;
		timer->count = iVar3;
		if (iVar3 < 1) {
			if (((MissionHeader->timerFlags & 0x1000U) == 0) ||
				(iVar3 = DetonatorTimer(), iVar3 == 0)) {
				if ((timer->flags & 8) == 0) {
					if (Mission.gameover_delay == -1) {
						SetMissionFailed(FAILED_OUTOFTIME);
					}
					if ((timer->flags & 0x10) != 0) {
						events.cameraEvent = (_EVENT *)0x1;
						BombThePlayerToHellAndBack(gCarWithABerm);
					}
				}
				else {
					if (Mission.gameover_delay == -1) {
						SetMissionComplete();
						timer->count = 0;
						goto LAB_000615e0;
					}
				}
				timer->count = 0;
			}
			else {
				MissionHeader->timerFlags = MissionHeader->timerFlags & 0xefff;
				timer->count = 9000;
				timer->flags = timer->flags | 0x28;
			}
		}
	}
	else {
		iVar3 = timer->count + 100;
		timer->count = iVar3;
		if (10799999 < iVar3) {
			timer->count = 10799999;
		}
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

void RegisterChaseHit(int car1, int car2)
{
	UNIMPLEMENTED();
	/*
	int player;

	if ((DAT_000d7c40 != 0) && (DAT_000d7c48 == 0)) {
		if (gPlayerWithTheFlag == -1) {
			if ((car1 == *(int *)(DAT_000d7c40 + 0x18)) || (car2 == *(int *)(DAT_000d7c40 + 0x18))) {
				*(int *)(DAT_000d7c40 + 0x34) = *(int *)(DAT_000d7c40 + 0x34) + -1;
				DAT_000d7c48 = 0x14;
				DamageBar.position = DamageBar.position + 1;
			}
		}
		else {
			player = 1 - gPlayerWithTheFlag;
			gPlayerWithTheFlag = player;
			(&player)[player].targetCarId = -1;
			DAT_000d7c48 = 0x14;
			(&player)[1 - player].targetCarId = (char)gPlayerWithTheFlag;
			SetPlayerMessage(player, s_Ce_l_hai_fatta__00011808, 2, 1);
		}
	}
	return;
	*/
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

void PauseMissionTimer(int pause)
{
	UNIMPLEMENTED();
	/*
	if (pause == 0) {
		DAT_000d7c28 = DAT_000d7c28 & 0xfb;
		DAT_000d7c34 = DAT_000d7c34 & 0xfb;
	}
	else {
		DAT_000d7c28 = DAT_000d7c28 | 4;
		DAT_000d7c34 = DAT_000d7c34 | 4;
	}
	return;
	*/
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

void SetMissionMessage(char *message, int priority, int seconds)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	uint uVar2;
	char **ppcVar3;

	if (((message != MissionStrings + -1) && (message != (char *)0x0)) &&
		(uVar2 = (uint)NumPlayers, NumPlayers != 0)) {
		ppcVar3 = (char **)&DAT_000d7c1c;
		psVar1 = &DAT_000d7c16;
		do {
			if ((psVar1[-2] == 0) || (*psVar1 <= priority)) {
				*ppcVar3 = message;
				*psVar1 = (short)priority;
				if (seconds == 0) {
					psVar1[-2] = 5;
				}
				else {
					psVar1[-2] = (short)seconds * 0x1e;
				}
			}
			ppcVar3 = ppcVar3 + 1;
			uVar2 = uVar2 - 1;
			psVar1 = psVar1 + 1;
		} while (uVar2 != 0);
	}
	return;
	*/
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

void SetPlayerMessage(int player, char *message, int priority, int seconds)
{
	UNIMPLEMENTED();
	/*
	if ((message != MissionStrings + -1) && (message != (char *)0x0)) {
		if (((&DAT_000d7c12)[player] == 0) || ((short)(&DAT_000d7c16)[player] <= priority)) {
			*(char **)(&DAT_000d7c1c + player) = message;
			(&DAT_000d7c16)[player] = (short)priority;
			(&DAT_000d7c12)[player] = (short)seconds * 0x1e;
		}
	}
	return;
	*/
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

int TargetComplete(_TARGET *target, int player)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uint uVar1;
	uint uVar2;

	uVar2 = target->data[1];
	if (player == 0) {
		uVar1 = uVar2 & 2;
	}
	else {
		uVar1 = uVar2 & 0x100;
		if (player != 1) {
			if ((uVar2 & 0x102) == 0x102) {
				return 1;
			}
			return 0;
		}
	}
	if (uVar1 == 0) {
		return 0;
	}
	return 1;
	*/
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

int TargetActive(_TARGET *target, int player)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uint uVar1;
	uint uVar2;

	uVar2 = target->data[1];
	if (player == 0) {
		uVar1 = uVar2 & 1;
	}
	else {
		uVar1 = uVar2 & 0x800;
		if (player != 1) {
			if ((uVar2 & 0x801) == 0x801) {
				return 1;
			}
			return 0;
		}
	}
	if (uVar1 == 0) {
		return 0;
	}
	return 1;
	*/
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

int Swap2Cars(int curslot, int newslot)
{
	UNIMPLEMENTED();
	return 0;
	/*
	char cVar1;
	_CAR_DATA *p_Var2;
	_CAR_DATA *p_Var3;
	long *plVar4;
	long *plVar5;
	int iVar6;
	_CAR_DATA *p_Var7;
	undefined4 uVar8;
	char cVar9;
	int in_t2;
	int in_t3;
	long lVar10;
	undefined4 uVar11;
	long lVar12;
	undefined4 uVar13;
	long lVar14;
	_CAR_DATA *cp;
	char cVar15;
	int unaff_s4;
	int unaff_s5;
	long local_2c0[168];

	if (curslot == newslot) {
		return newslot;
	}
	if (car_data[curslot].controlType == '\x02') {
		if (*(int *)(car_data[curslot].ai + 8) == 0) {
			unaff_s4 = -1;
		}
		else {
			unaff_s4 = (*(int *)(car_data[curslot].ai + 8) + -0x1b0) - (int)(car_data + curslot) >> 4;
		}
		if (*(int *)(car_data[curslot].ai + 0xf4) == 0) {
			unaff_s5 = -1;
		}
		else {
			unaff_s5 = (*(int *)(car_data[curslot].ai + 0xf4) + -0x1b0) - (int)(car_data + curslot) >> 4;
		}
	}
	car_data[curslot].lowDetail = -1;
	car_data[curslot].ap.qy = 0;
	car_data[curslot].ap.qw = 0;
	if (car_data[newslot].controlType == '\x02') {
		if (*(int *)(car_data[newslot].ai + 8) == 0) {
			in_t2 = -1;
		}
		else {
			in_t2 = (*(int *)(car_data[newslot].ai + 8) + -0x1b0) - (int)(car_data + newslot) >> 4;
		}
		if (*(int *)(car_data[newslot].ai + 0xf4) == 0) {
			in_t3 = -1;
		}
		else {
			in_t3 = (*(int *)(car_data[newslot].ai + 0xf4) + -0x1b0) - (int)(car_data + newslot) >> 4;
		}
	}
	car_data[newslot].lowDetail = -1;
	car_data[newslot].ap.qy = 0;
	car_data[newslot].ap.qw = 0;
	cp = car_data + newslot;
	plVar5 = local_2c0;
	do {
		plVar4 = plVar5;
		p_Var2 = cp;
		lVar10 = *(long *)((p_Var2->hd).where.m + 2);
		lVar12 = *(long *)((p_Var2->hd).where.m + 4);
		lVar14 = *(long *)((p_Var2->hd).where.m + 6);
		*plVar4 = *(long *)(p_Var2->hd).where.m;
		plVar4[1] = lVar10;
		plVar4[2] = lVar12;
		plVar4[3] = lVar14;
		cp = (_CAR_DATA *)((p_Var2->hd).where.m + 8);
		plVar5 = plVar4 + 4;
	} while (cp != (_CAR_DATA *)&car_data[newslot].handbrake);
	lVar10 = (p_Var2->hd).where.t[0];
	lVar12 = (p_Var2->hd).where.t[1];
	plVar4[4] = *(long *)(cp->hd).where.m;
	plVar4[5] = lVar10;
	plVar4[6] = lVar12;
	cp = car_data + newslot;
	p_Var2 = car_data + curslot;
	do {
		p_Var7 = p_Var2;
		p_Var3 = cp;
		uVar8 = *(undefined4 *)((p_Var7->hd).where.m + 2);
		uVar11 = *(undefined4 *)((p_Var7->hd).where.m + 4);
		uVar13 = *(undefined4 *)((p_Var7->hd).where.m + 6);
		*(undefined4 *)(p_Var3->hd).where.m = *(undefined4 *)(p_Var7->hd).where.m;
		*(undefined4 *)((p_Var3->hd).where.m + 2) = uVar8;
		*(undefined4 *)((p_Var3->hd).where.m + 4) = uVar11;
		*(undefined4 *)((p_Var3->hd).where.m + 6) = uVar13;
		p_Var2 = (_CAR_DATA *)((p_Var7->hd).where.m + 8);
		cp = (_CAR_DATA *)((p_Var3->hd).where.m + 8);
	} while (p_Var2 != (_CAR_DATA *)&car_data[curslot].handbrake);
	lVar10 = (p_Var7->hd).where.t[0];
	lVar12 = (p_Var7->hd).where.t[1];
	*(undefined4 *)(cp->hd).where.m = *(undefined4 *)(p_Var2->hd).where.m;
	(p_Var3->hd).where.t[0] = lVar10;
	(p_Var3->hd).where.t[1] = lVar12;
	cp = car_data + curslot;
	plVar5 = local_2c0;
	do {
		plVar4 = plVar5;
		p_Var2 = cp;
		lVar14 = plVar4[1];
		lVar10 = plVar4[2];
		lVar12 = plVar4[3];
		*(long *)(p_Var2->hd).where.m = *plVar4;
		*(long *)((p_Var2->hd).where.m + 2) = lVar14;
		*(long *)((p_Var2->hd).where.m + 4) = lVar10;
		*(long *)((p_Var2->hd).where.m + 6) = lVar12;
		plVar5 = plVar4 + 4;
		cp = (_CAR_DATA *)((p_Var2->hd).where.m + 8);
	} while (plVar5 != local_2c0 + 0xa4);
	lVar10 = plVar4[5];
	lVar12 = plVar4[6];
	*(long *)(cp->hd).where.m = *plVar5;
	(p_Var2->hd).where.t[0] = lVar10;
	(p_Var2->hd).where.t[1] = lVar12;
	cVar15 = (char)newslot;
	car_data[newslot].id = cVar15;
	iVar6 = (int)player.cameraCarId;
	cVar9 = (char)curslot;
	car_data[curslot].id = cVar9;
	cVar1 = cVar15;
	if ((iVar6 == curslot) || (cVar1 = cVar9, iVar6 == newslot)) {
		player.cameraCarId = cVar1;
	}
	cVar1 = cVar15;
	if (((int)player.targetCarId != curslot) &&
		(cVar1 = player.targetCarId, (int)player.targetCarId == newslot)) {
		cVar1 = cVar9;
	}
	player.targetCarId = cVar1;
	cVar1 = cVar15;
	if (((int)player.playerCarId == curslot) || (cVar1 = cVar9, (int)player.playerCarId == newslot)) {
		player.playerCarId = cVar1;
	}
	if ((int)player.worldCentreCarId == newslot) {
		iVar6 = curslot * 0x29c;
		player.worldCentreCarId = cVar9;
	}
	else {
		if ((int)player.worldCentreCarId != curslot) goto LAB_00061b4c;
		iVar6 = newslot * 0x29c;
		player.worldCentreCarId = cVar15;
	}
	player.spoolXZ = (VECTOR *)((int)car_data[0].hd.where.t + iVar6);
LAB_00061b4c:
	gDontResetCarDamage = 1;
	cp = car_data + curslot;
	if (in_t2 == -1) {
		*(undefined4 *)(car_data[curslot].ai + 8) = 0;
	}
	else {
		*(byte **)(car_data[curslot].ai + 8) = cp->ai + in_t2 * 0x10 + 0x24;
	}
	if (in_t3 == -1) {
		*(undefined4 *)(car_data[curslot].ai + 0xf4) = 0;
	}
	else {
		*(byte **)(car_data[curslot].ai + 0xf4) = cp->ai + in_t3 * 0x10 + 0x24;
	}
	CreateDentableCar(cp);
	DentCar(cp);
	cp = car_data + newslot;
	if (unaff_s4 == -1) {
		*(undefined4 *)(car_data[newslot].ai + 8) = 0;
	}
	else {
		*(byte **)(car_data[newslot].ai + 8) = cp->ai + unaff_s4 * 0x10 + 0x24;
	}
	if (unaff_s5 == -1) {
		*(undefined4 *)(car_data[newslot].ai + 0xf4) = 0;
	}
	else {
		*(byte **)(car_data[newslot].ai + 0xf4) = cp->ai + unaff_s5 * 0x10 + 0x24;
	}
	CreateDentableCar(cp);
	DentCar(cp);
	gDontResetCarDamage = 0;
	return newslot;
	*/
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

void HandleMissionThreads(void)
{
	UNIMPLEMENTED();
	/*
	_TARGET *p_Var1;
	uint uVar2;
	int iVar3;
	int iVar4;
	uint fnc;
	MR_THREAD *thread;
	uint uVar5;

	iVar3 = 0xf;
	p_Var1 = MissionTargets;
	do {
		iVar3 = iVar3 + -1;
		p_Var1->data[1] = p_Var1->data[1] & 0xfffff9ff;
		p_Var1 = p_Var1 + 1;
	} while (-1 < iVar3);
	iVar4 = 0;
	iVar3 = 0;
	do {
		thread = (MR_THREAD *)(&MissionThreads + iVar3);
		uVar5 = (uint)thread->active;
		iVar4 = iVar4 + 1;
		if (((thread->active != 0) && (DAT_000d7c0c == -1)) && (gInGameCutsceneActive == 0)) {
			while (gInGameCutsceneDelay == 0) {
				fnc = **(uint **)((int)&DAT_000d7b10 + iVar3);
				uVar2 = fnc & 0xff000000;
				*(uint **)((int)&DAT_000d7b10 + iVar3) = *(uint **)((int)&DAT_000d7b10 + iVar3) + 1;
				if (uVar2 == 0x2000000) {
				LAB_00061db8:
					MRPush(thread, fnc);
				}
				else {
					if (uVar2 < 0x2000001) {
						if (uVar2 == 0) goto LAB_00061db8;
						if (uVar2 == 0x1000000) {
							uVar5 = MRCommand(thread, fnc);
						}
					}
					else {
						if (uVar2 == 0x4000000) {
							uVar5 = MRFunction(thread, fnc);
						}
						else {
							if (uVar2 < 0x4000001) {
								if (uVar2 == 0x3000000) {
									uVar5 = MROperator(thread, fnc);
								}
							}
							else {
								if (uVar2 == 0xff000000) goto LAB_00061db8;
							}
						}
					}
				}
				if (((uVar5 == 0) || (DAT_000d7c0c != -1)) || (gInGameCutsceneActive != 0)) break;
			}
		}
		iVar3 = iVar4 * 0x10;
		if (0xf < iVar4) {
			return;
		}
	} while (true);
	*/
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

int MRCommand(MR_THREAD *thread, ulong cmd)
{
	UNIMPLEMENTED();
	return 0;
	/*
	long cutscene;
	long seconds;
	int iVar1;
	ulong addr;
	short *psVar2;
	uint uVar3;

	if (cmd == 0x1000051) {
		CompleteAllActiveTargets((uint)thread->player);
		cutscene = MRPop(thread);
		TriggerInGameCutscene(cutscene);
		if ((gInGameCutsceneActive == 0) && (gCutsceneAtEnd == 0)) {
			return 1;
		}
		RequestXA();
		InitializeCutsceneSound(cutscene);
		return 1;
	}
	if (cmd < 0x1000052) {
		if (cmd == 0x1000021) {
			CompleteAllActiveTargets((uint)thread->player);
			return 1;
		}
		if (cmd < 0x1000022) {
			if (cmd == 0x1000010) {
				addr = MRPop(thread);
				cutscene = MRPop(thread);
				MRSetVariable(thread, addr, cutscene);
				return 1;
			}
			if (0x1000010 < cmd) {
				if (cmd != 0x1000011) {
					return 1;
				}
				cutscene = MRPop(thread);
				iVar1 = MRJump(thread, cutscene);
				return iVar1;
			}
			if (cmd != 0x1000000) {
				if (cmd != 0x1000001) {
					return 1;
				}
				cutscene = MRPop(thread);
				seconds = MRPop(thread);
				if (seconds != 0) {
					return 1;
				}
				iVar1 = MRJump(thread, cutscene);
				return iVar1;
			}
		}
		else {
			if (cmd == 0x1000040) {
				iVar1 = (uint)thread->player * 0xc;
				(&DAT_000d7c28)[iVar1] = (&DAT_000d7c28)[iVar1] | 2;
			}
			else {
				if (cmd < 0x1000041) {
					if (cmd == 0x1000022) {
						cutscene = MRPop(thread);
						MultiCarEvent(MissionTargets + cutscene);
						return 1;
					}
					if (cmd != 0x1000030) {
						return 1;
					}
					cutscene = MRPop(thread);
					iVar1 = (int)player.playerCarId;
					if (iVar1 != -1) {
						if (iVar1 < 0) {
							psVar2 = &pedestrianFelony;
						}
						else {
							psVar2 = &car_data[iVar1].felonyRating;
						}
						*psVar2 = (short)cutscene;
					}
				}
				else {
					if (cmd == 0x1000042) {
						MissionHeader->timerFlags = MissionHeader->timerFlags | 0x1000;
					}
					else {
						if (0x1000041 < cmd) {
							if (cmd != 0x1000050) {
								return 1;
							}
							cutscene = MRPop(thread);
							seconds = MRPop(thread);
							SetPlayerMessage((uint)thread->player, MissionStrings + cutscene, 0, seconds);
							return 1;
						}
						iVar1 = (uint)thread->player * 0xc;
						(&DAT_000d7c28)[iVar1] = (&DAT_000d7c28)[iVar1] & 0xfd;
					}
				}
			}
		}
	}
	else {
		if (cmd == 0x1000081) {
			gCantDrive = 1;
		}
		else {
			if (cmd < 0x1000082) {
				if (cmd == 0x1000070) {
					cutscene = MRPop(thread);
					TriggerEvent(cutscene);
					return 1;
				}
				if (0x1000070 < cmd) {
					if (cmd != 0x1000071) {
						if (cmd != 0x1000080) {
							return 1;
						}
						cutscene = MRPop(thread);
						lockAllTheDoors = (char)cutscene;
						return 1;
					}
					uVar3 = MRPop(thread);
					if ((uVar3 & 0x8000) != 0) {
						AvailableCheats._0_1_ = (byte)AvailableCheats | 1;
					}
					if ((uVar3 & 0x4000) != 0) {
						AvailableCheats._0_1_ = (byte)AvailableCheats | 2;
					}
					if ((uVar3 & 0x10000) != 0) {
						AvailableCheats._0_1_ = (byte)AvailableCheats | 4;
					}
					if ((uVar3 & 0x20000) != 0) {
						AvailableCheats._0_1_ = (byte)AvailableCheats | 8;
					}
					if ((uVar3 & 1) != 0) {
						AvailableCheats._0_1_ = (byte)AvailableCheats | 0x10;
					}
					if ((uVar3 & 0x10) != 0) {
						AvailableCheats._0_1_ = (byte)AvailableCheats | 0x40;
					}
					if ((uVar3 & 0x100) != 0) {
						AvailableCheats._1_1_ = AvailableCheats._1_1_ | 1;
					}
					if ((uVar3 & 0x1000) != 0) {
						AvailableCheats._1_1_ = AvailableCheats._1_1_ | 2;
					}
					if ((uVar3 & 0x2000) == 0) {
						return 1;
					}
					AvailableCheats._1_1_ = AvailableCheats._1_1_ | 4;
					return 1;
				}
				if (cmd == 0x1000054) {
					cutscene = MRPop(thread);
					DAT_000d7c4c = MissionStrings + cutscene;
				}
				else {
					if (cmd != 0x1000055) {
						return 1;
					}
					SetPlayerMessage(1, MissionStrings + MissionHeader->msgOutOfTime, 2, 2);
				}
			}
			else {
				if (cmd == 0x1001000) {
					iVar1 = MRStopThread(thread);
					return iVar1;
				}
				if (0x1001000 < cmd) {
					if (cmd == 0x1001002) {
						addr = MRPop(thread);
						MRStartThread(thread, addr, thread->player);
						return 1;
					}
					if (0x1001001 < cmd) {
						if (cmd != 0x1001003) {
							return 1;
						}
						addr = MRPop(thread);
						MRStartThread(thread, addr, '\x01');
						return 1;
					}
					SetMissionComplete();
					return 1;
				}
				if (cmd != 0x1000090) {
					if (cmd != 0x1000100) {
						return 1;
					}
					SpecialCamera(SPECIAL_CAMERA_SET, 0);
					return 1;
				}
				gWeather = 1;
			}
		}
	}
	return 1;
	*/
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

int MROperator(MR_THREAD *thread, ulong op)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	long lVar2;
	long lVar3;
	int iVar4;
	long value;

	value = 0;
	lVar2 = MRGetParam(thread);
	lVar3 = MRGetParam(thread);
	switch (op) {
	case 0x3000003:
		if (lVar2 == 0) break;
		goto LAB_0006451c;
	case 0x3000004:
		if (lVar2 != 0) goto LAB_00064534;
	LAB_0006451c:
		if (lVar3 != 0) {
			value = 1;
		}
		break;
	case 0x3000005:
		if (lVar2 == lVar3) break;
	LAB_00064534:
		value = 1;
		break;
	case 0x3000006:
		if (lVar2 == lVar3) {
			value = 1;
		}
		break;
	case 0x3000007:
		bVar1 = lVar3 < lVar2;
		goto LAB_00064558;
	case 0x3000008:
		bVar1 = lVar2 < lVar3;
	LAB_00064558:
		if (bVar1) {
			value = 1;
		}
		break;
	case 0x3000009:
		value = lVar2 + lVar3;
		break;
	default:
		iVar4 = MRStopThread(thread);
		return iVar4;
	}
	MRPush(thread, value);
	return 1;
	*/
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

int MRFunction(MR_THREAD *thread, ulong fnc)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int value;
	long lVar1;

	if (fnc == 0x4000020) {
		lVar1 = MRPop(thread);
		value = MRProcessTarget(thread, MissionTargets + lVar1);
		MRPush(thread, value);
		value = 1;
	}
	else {
		value = MRStopThread(thread);
	}
	return value;
	*/
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
	thread->active = '\x01';
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


void MRStartThread(MR_THREAD *callingthread, ulong addr, unsigned char player)
{
	UNIMPLEMENTED();
	return;
	/*
	int iVar1;
	MR_THREAD *thread;

	iVar1 = 0;
	thread = (MR_THREAD *)&MissionThreads;
	do {
		iVar1 = iVar1 + 1;
		if (thread->active == '\0') {
			MRInitialiseThread(thread, callingthread->pc + addr, player);
			return;
		}
		thread = thread + 1;
	} while (iVar1 < 0x10);
	return;*/
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
	thread->active = '\0';
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

void MRCommitThreadGenocide(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	MR_THREAD *thread;

	thread = (MR_THREAD *)&MissionThreads;
	iVar1 = 0xf;
	do {
		MRStopThread(thread);
		iVar1 = iVar1 + -1;
		thread = thread + 1;
	} while (-1 < iVar1);
	return;
	*/
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
	uint uVar1;

	if (jump + 2U < 3) {
		uVar1 = MRStopThread(thread);
	}
	else {
		uVar1 = (uint)~jump >> 0x1f;
		thread->pc = thread->pc + jump;
	}
	return uVar1;
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
	ulong *puVar1;

	puVar1 = thread->sp;
	*puVar1 = value;
	thread->sp = puVar1 + 1;
	return;
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
	ulong *puVar1;

	puVar1 = thread->sp;
	thread->sp = puVar1 + -1;
	return puVar1[-1];
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
	uint var;
	uint uVar1;

	var = MRPop(thread);
	uVar1 = var & 0xff000000;
	if (uVar1 == 0x2000000) {
		var = MRGetVariable(thread, var);
	}
	else {
		if (uVar1 < 0x2000001) {
			if (uVar1 != 0) {
				return 0;
			}
		}
		else {
			if (uVar1 != 0xff000000) {
				return 0;
			}
		}
	}
	return var;
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

long MRGetVariable(MR_THREAD *thread, ulong var)
{
	UNIMPLEMENTED();
	return 0;
	/*
	if (var == 0x2000101) {
		return gCopMaxPowerScale;
	}
	if (var < 0x2000102) {
		if (var == 0x2000008) {
			return (int)(&DAT_000d7c2c)[(uint)thread->player * 3] / 3000;
		}
		if (var == 0x2000100) {
			return gCopDesiredSpeedScale;
		}
	}
	else {
		if (var == 0x2000102) {
			return gMinimumCops;
		}
		if (var == 0x2000103) {
			return maxCopCars;
		}
	}
	return 0;
	*/
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

void MRSetVariable(MR_THREAD *thread, ulong var, long value)
{
	UNIMPLEMENTED();
	return;
	/*
	if (var == 0x2000101) {
		gCopMaxPowerScale = value;
		return;
	}
	if (var < 0x2000102) {
		if (var == 0x2000008) {
			(&DAT_000d7c2c)[(uint)thread->player * 3] = value * 3000;
			return;
		}
		if (var != 0x2000100) {
			return;
		}
		gCopDesiredSpeedScale = value;
		return;
	}
	if (var == 0x2000102) {
		gMinimumCops = value;
		return;
	}
	if (var != 0x2000103) {
		return;
	}
	if (value == 4) {
		if (GameType == GAME_SURVIVAL) {
			gDontPingInCops = 0;
			gBatterPlayer = 1;
			goto LAB_00064984;
		}
		gDontPingInCops = 1;
	}
	else {
		gDontPingInCops = 0;
	}
	gBatterPlayer = 0;
LAB_00064984:
	if (0 < value) {
		CopsAllowed = 1;
	}
	maxCopCars = value;
	return;*/
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

int MRProcessTarget(MR_THREAD *thread, _TARGET *target)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	uchar internalModel;
	byte bVar2;
	int iVar3;
	int iVar4;
	int direction;
	uint uVar5;
	ulong uVar6;
	undefined *puVar7;
	VECTOR *pVVar8;
	uint uVar9;
	char *message;
	int *piVar10;
	int iVar11;
	VECTOR local_60;
	VECTOR local_50;
	long local_40;
	int local_3c;
	long local_38;
	int local_30[2];

	iVar11 = 0;
	direction = TargetComplete(target, (uint)thread->player);
	if (direction != 0) {
		return 1;
	}
	if (thread->player == '\0') {
		uVar5 = target->data[1] | 0x201;
	}
	else {
		uVar5 = target->data[1] | 0xc00;
	}
	target->data[1] = uVar5;
	uVar5 = (uint)thread->player;
	local_50.vx = (&player)[uVar5].pos[0];
	local_50.vy = (&player)[uVar5].pos[1];
	local_50.vz = (&player)[uVar5].pos[2];
	direction = target->data[0];
	if (direction != 2) {
		if (2 < direction) {
			if (direction == 3) {
				if ((target->data[1] & 0x1000U) == 0) {
					pVVar8 = TriggerEvent(target->data[3]);
					*(VECTOR **)(target->data + 4) = pVVar8;
					target->data[1] = target->data[1] | 0x1000;
				}
				else {
					if ((target->data[0xe] != -1) &&
						(uVar6 = Long2DDistance((VECTOR *)target->data[4], &local_50), 30000 < uVar6)) {
						SetPlayerMessage((uint)thread->player, MissionStrings + target->data[0xe], 2, 2);
						SetMissionFailed(FAILED_MESSAGESET);
					}
				}
			}
			goto LAB_00063664;
		}
		if (direction != 1) goto LAB_00063664;
		uVar5 = target->data[1];
		if ((uVar5 & 0x100000) == 0) {
			if ((uVar5 & 0x200000) == 0) {
				local_60.vx = target->data[3];
				local_60.vz = target->data[4];
				local_60.vy = 0;
			}
			else {
				target->data[1] = uVar5 & 0xffdfffff;
				DAT_000d7c84 = target->data[5];
				gStopCops = target->data[3];
				DAT_000d7c7c = 0;
				DAT_000d7c80 = target->data[4];
			}
		}
		else {
			local_60.vx = target->data[10];
			local_60.vz = target->data[0xb];
			OffsetTarget(&local_60);
			target->data[3] = local_60.vx;
			target->data[4] = local_60.vz;
		}
		uVar6 = Long2DDistance(&local_60, &local_50);
		if ((uint)target->data[5] < uVar6) {
		LAB_00062684:
			target->data[9] = target->data[9] & 0xffff000f;
		}
		else {
			if (target->data[7] != 0) {
				uVar9 = target->data[6] + local_50.vy;
				uVar5 = -target->data[6] - local_50.vy;
				if (-1 < (int)uVar9) {
					uVar5 = uVar9;
				}
				if ((uint)target->data[7] < uVar5) goto LAB_00062684;
			}
			uVar5 = target->data[1] & 0x3000000;
			if (uVar5 == 0x1000000) {
				(&playercollected)[thread->player] = (&playercollected)[thread->player] | 2;
				return 0;
			}
			if (uVar5 < 0x1000001) {
				if ((uVar5 == 0) && (GameType == GAME_SECRET)) {
					(&playercollected)[thread->player] = (&playercollected)[thread->player] | 1;
					return 0;
				}
			}
			else {
				if (uVar5 == 0x2000000) {
					(&playercollected)[thread->player] = (&playercollected)[thread->player] | 4;
					return 0;
				}
				if (uVar5 == 0x3000000) {
					if ((&playercollected)[thread->player] != '\a') {
						return 0;
					}
					(&playercollected)[thread->player] = '\0';
					if (thread->player != '\0') {
						iVar11 = CalcLapTime(1, DAT_000d7c38, (int)gPlayerScore.P2items);
						direction = (int)gPlayerScore.P2items;
						gPlayerScore.P2items = gPlayerScore.P2items + 1;
						(&DAT_000d7c64)[direction] = iVar11;
						if ((int)gPlayerScore.P2items == gNumRaceTrackLaps) {
							SetMissionComplete();
							return 0;
						}
						return 0;
					}
					iVar11 = CalcLapTime(0, DAT_000d7c2c, (int)gPlayerScore.items);
					direction = (int)gPlayerScore.items;
					gPlayerScore.items = gPlayerScore.items + 1;
					(&gLapTimes)[direction] = iVar11;
					if ((int)gPlayerScore.items == gNumRaceTrackLaps) {
						SetMissionComplete();
						return 0;
					}
					return 0;
				}
			}
			uVar5 = target->data[1] & 0x30000;
			if (uVar5 == 0) {
				uVar5 = target->data[9];
				if (uVar5 == 0) {
					if ((target->data[8] == -1) || (copsAreInPursuit == 0)) {
						iVar11 = 1;
						prevCopsInPursuit = 0;
					}
					else {
						if ((DAT_000d7c12 == 0) && (prevCopsInPursuit == 0)) {
							SetPlayerMessage((uint)thread->player, MissionStrings + target->data[8], 2, 2);
							prevCopsInPursuit = copsAreInPursuit;
						}
					}
				}
				else {
					uVar9 = ((int)(uVar5 & 0xfff0) >> 4) + 1;
					if ((uVar5 & 0xf) <= uVar9 / 0x1e) {
						SetPlayerMessage((uint)thread->player, MissionStrings + ((int)uVar5 >> 0x10), 2, 0);
					}
					target->data[9] = ((int)uVar5 >> 0x10) << 0x10 | uVar9 * 0x10 | uVar5 & 0xf;
					gTannerActionNeeded = 1;
					direction = TannerActionHappening();
					if (direction != 0) {
						iVar11 = 1;
					}
				}
				if (iVar11 == 0) {
					return 0;
				}
				if ((target->data[1] & 0x400000U) != 0) {
					return 1;
				}
				if (((target->data[1] & 0x800000U) != 0) && ((&player)[thread->player].playerType != '\x01')
					) {
					iVar11 = 0;
				}
			}
			else {
				if (uVar5 == 0x20000) {
					if ((thread->player != 1) || (gPlayerWithTheFlag != (uint)thread->player))
						goto LAB_00063664;
					gPlayerScore.P2items = gPlayerScore.P2items + 1;
				}
				else {
					if (0x20000 < uVar5) {
						if ((uVar5 == 0x30000) && (gPlayerWithTheFlag == -1)) {
							DAT_000d7c40 = MissionTargets;
							gPlayerWithTheFlag = ZEXT14(thread->player);
							SetPlayerMessage((uint)thread->player, s_Ce_l_hai_fatta__00011808, 2, 1);
							(&player)[1 - gPlayerWithTheFlag].targetCarId = (char)gPlayerWithTheFlag;
						}
						goto LAB_00063664;
					}
					if (((uVar5 != 0x10000) || (thread->player != '\0')) || (gPlayerWithTheFlag != 0))
						goto LAB_00063664;
					gPlayerScore.items = gPlayerScore.items + 1;
				}
				gPlayerWithTheFlag = -1;
				SetPlayerMessage((uint)thread->player, s_Ben_fatto__00011818, 2, 1);
				player.targetCarId = -1;
				_PLAYER_ARRAY_000d979c[0].targetCarId = -1;
				ActivateNextFlag();
			}
		}
		goto LAB_00063664;
	}
	local_60.vx = target->data[3];
	local_60.vz = target->data[4];
	local_60.vy = 0;
	puVar7 = (undefined *)Long2DDistance(&local_60, &local_50);
	local_30[0] = target->data[6];
	if (local_30[0] == -1) {
		if ((puVar7 < &DAT_00003e1c) || ((target->data[9] == 3 && ((target->data[10] & 1U) == 0)))) {
			MRRequestCar(target);
		}
		else {
			MRCancelCarRequest(target);
		}
		goto LAB_00063664;
	}
	if ((target->data[1] & 0x40000000U) == 0) {
		bVar1 = gCarWithABerm == local_30[0];
		target->data[6] = -1;
		if (bVar1) {
			gCarWithABerm = -1;
		}
		if (target->data[9] == 1) goto LAB_00063664;
	LAB_000635bc:
		direction = 2;
		bVar2 = thread->player;
		message = MissionStrings + target->data[0xe];
	LAB_000635d0:
		SetPlayerMessage((uint)bVar2, message, 2, direction);
	LAB_000635d8:
		SetMissionFailed(FAILED_MESSAGESET);
	}
	else {
		direction = target->data[9];
		if (direction != 2) {
			if (direction < 3) {
				if (((direction == 1) && ((undefined *)target->data[0xc] != (undefined *)0x0)) &&
					(puVar7 < (undefined *)target->data[0xc])) {
					piVar10 = car_data[local_30[0]].inform;
					local_40 = car_data[local_30[0]].hd.where.t[0];
					local_3c = car_data[local_30[0]].hd.where.t[1];
					local_38 = car_data[local_30[0]].hd.where.t[2];
					car_data[local_30[0]].inform = (int *)0x0;
					direction = car_data[local_30[0]].hd.direction;
					internalModel = car_data[local_30[0]].ap.model;
					bVar2 = car_data[local_30[0]].ap.palette;
					PingOutCar(car_data + local_30[0]);
					local_30[0] = CreateCivCarWotDrivesABitThenStops
					(direction, (long(*)[4])&local_40, (long(*)[4])0x0, internalModel
						, (uint)bVar2);
					car_data[local_30[0]].inform = piVar10;
					target->data[6] = local_30[0];
					target->data[0xc] = 0;
				}
			}
			else {
				if (direction == 3) {
					if (((target->data[1] & 0x20U) == 0) && ((target->data[10] & 1U) != 0)) {
						if (target->data[0xb] == -1) {
							if (gInGameChaseActive == 0) {
								DAT_000d7c40 = (_TARGET *)0x0;
								player.targetCarId = -1;
								gBombTargetVehicle = (_CAR_DATA *)0x0;
								if ((target->data[10] & 0xf0U) != 0x20) {
									if ((target->data[10] & 0x10000U) == 0) {
										iVar11 = 1;
									}
									else {
										SetCarToBeStolen(target, (uint)thread->player);
									}
									goto LAB_00062dd0;
								}
							}
						}
						else {
							if (((undefined *)target->data[0xc] <= puVar7) || ((MissionHeader->type & 4U) != 0))
								goto LAB_00062dd0;
							TriggerChase(local_30, target->data[0xb]);
							target->data[0xb] = -1;
							target->data[6] = local_30[0];
							player.targetCarId = (char)local_30[0];
							DAT_000d7c40 = target;
						}
					}
					if ((target->data[10] & 4U) != 0) {
						gBombTargetVehicle = car_data + local_30[0];
					}
				}
			}
		}
	LAB_00062dd0:
		target->data[3] = car_data[local_30[0]].hd.where.t[0];
		target->data[4] = car_data[local_30[0]].hd.where.t[2];
		direction = gCurrentMissionNumber;
		if (((target->data[9] == 3) && ((target->data[1] & 0x20U) == 0)) &&
			((target->data[10] & 1U) == 0)) {
			if ((int)(uint)car_data[local_30[0]].totalDamage < target->data[0xd]) goto LAB_00063664;
			if (NewLeadDelay != '\x01') {
				if ((target->data[10] & 0x10000U) == 0) {
					iVar11 = 0;
					DamageBar.position = *(ushort *)(target->data + 0xd);
					car_data[local_30[0]].totalDamage = (ushort)MaxPlayerDamage - 1;
					SetConfusedCar(local_30[0]);
					NewLeadDelay = '\x01';
				}
				else {
					DamageBar.position = *(ushort *)(target->data + 0xd);
					car_data[local_30[0]].totalDamage = (ushort)MaxPlayerDamage;
					SetConfusedCar(local_30[0]);
					SetCarToBeStolen(target, (uint)thread->player);
					NewLeadDelay = '\x01';
				}
				goto LAB_00063664;
			}
		LAB_00063590:
			iVar11 = 1;
			goto LAB_00063664;
		}
		uVar5 = target->data[10] & 0xf0;
		if (uVar5 == 0x20) goto LAB_00063664;
		if (0x20 < uVar5) {
			if (uVar5 == 0x40) {
				if (copsAreInPursuit != 0) {
					iVar11 = 1;
				}
				goto LAB_00063664;
			}
			if (0x40 < uVar5) {
				if (uVar5 != 0x50) goto LAB_00063664;
				if (((target->data[1] & 0x20U) != 0) &&
					(INT_000aa714 = target->data[0xd], (uint)TAIL_TOOFAR < puVar7)) {
					if (GameType == GAME_COPSANDROBBERS) {
						SetMissionFailed(FAILED_CnR_LOSTHIM);
						goto LAB_00063664;
					}
					goto LAB_000635bc;
				}
				if (((int)(uint)car_data[local_30[0]].totalDamage < target->data[0xd]) ||
					(iVar11 = 1, (target->data[1] & 0x20U) != 0)) goto LAB_00063664;
				SetConfusedCar(local_30[0]);
				goto LAB_00063590;
			}
			if (uVar5 != 0x30) goto LAB_00063664;
			if ((((gCurrentMissionNumber == 0xb) || (gCurrentMissionNumber == 0xe)) ||
				(gCurrentMissionNumber == 0x13)) ||
				((gCurrentMissionNumber == 0x1c ||
				((int)(uint)car_data[local_30[0]].totalDamage < MaxPlayerDamage)))) {
				if ((int)player.playerCarId == local_30[0]) {
					car_data[(int)player.playerCarId].inform = (int *)0x0;
					if ((direction == 0xe) || (direction == 0x1c)) {
						car_data[local_30[0]].totalDamage = (ushort)MaxPlayerDamage;
					}
					iVar11 = 1;
					if (MaxPlayerDamage <= (int)(uint)car_data[local_30[0]].totalDamage) {
						gGotInStolenCar = 1;
					}
				}
				goto LAB_00063664;
			}
			direction = 1;
			bVar2 = thread->player;
			message = MissionStrings + MissionHeader->msgCarWrecked;
			goto LAB_000635d0;
		}
		if (uVar5 == 0) {
			if (DamageBar.active == 0) {
				if (target->data[0xd] != 0) {
					if ((gCurrentMissionNumber != 2) && (gCurrentMissionNumber != 6)) {
						EnablePercentageBar(&DamageBar, target->data[0xd]);
					}
					if (((gCurrentMissionNumber == 0xb) || (gCurrentMissionNumber == 0xd)) ||
						(gCurrentMissionNumber == 0x1a)) {
						direction = target->data[0xd] * 3;
						if (direction < 0) {
							direction = direction + 3;
						}
						target->data[0xd] = direction >> 2;
					}
					goto LAB_00062fd0;
				}
			LAB_00062fe0:
				ReleaseInGameCutscene();
				DAT_000d7c40 = (_TARGET *)0x0;
				player.targetCarId = -1;
				gBombTargetVehicle = (_CAR_DATA *)0x0;
				SetConfusedCar(local_30[0]);
				if ((target->data[10] & 0x100000U) != 0) {
					car_data[local_30[0]].controlFlags = car_data[local_30[0]].controlFlags & 0xfb;
					local_40 = car_data[local_30[0]].hd.where.t[0];
					local_38 = car_data[local_30[0]].hd.where.t[2];
					local_3c = -car_data[local_30[0]].hd.where.t[1];
					CreatePedAtLocation((long(*)[4])&local_40, 8);
				}
				if ((target->data[10] & 0x10000U) == 0) {
					iVar11 = 1;
				}
				else {
					SetCarToBeStolen(target, (uint)thread->player);
					if (((gCurrentMissionNumber == 0xb) || (gCurrentMissionNumber == 0xd)) ||
						(gCurrentMissionNumber == 0x1a)) {
						direction = MaxPlayerDamage * 3;
						if (direction < 0) {
							direction = direction + 3;
						}
						car_data[local_30[0]].totalDamage = (ushort)(direction >> 2);
					}
					else {
						car_data[local_30[0]].totalDamage = (ushort)MaxPlayerDamage;
					}
					DamageBar.active = 0;
				}
			}
			else {
			LAB_00062fd0:
				if (target->data[0xd] < 1) goto LAB_00062fe0;
			}
			if ((uint)TAIL_TOOFAR < puVar7) goto LAB_000635bc;
			if ((uint)TAIL_GETTINGFAR < puVar7) {
				direction = target->data[0xf];
				iVar3 = lastsay;
				iVar4 = TAIL_GETTINGFAR;
			joined_r0x00063190:
				if ((direction != 0xff) && (iVar4 != iVar3)) {
					MissionSay(direction);
					lastsay = TAIL_GETTINGFAR;
				}
				goto LAB_00063664;
			}
		}
		else {
			if (uVar5 != 0x10) goto LAB_00063664;
			ProxyBar.active = 1;
			ProxyBar.position = (ushort)puVar7;
			if (puVar7 < (uint)TAIL_TOOCLOSE) {
				uVar5 = target->data[0xd] >> 0xc & 0xfff;
				if (uVar5 != 0xfff) {
					SetPlayerMessage((uint)thread->player, MissionStrings + uVar5, 2, 1);
				}
				goto LAB_000635d8;
			}
			if (puVar7 < (uint)TAIL_GETTINGCLOSE) {
				uVar5 = target->data[0xd] & 0xfff;
				if (uVar5 != 0xfff) {
					SetPlayerMessage((uint)thread->player, MissionStrings + uVar5, 2, 1);
				}
				direction = (int)*(char *)((int)target->data + 0x37);
				if ((direction != 0xff) && (lastsay != TAIL_GETTINGCLOSE)) {
					MissionSay(direction);
					lastsay = TAIL_GETTINGCLOSE;
				}
				goto LAB_00063664;
			}
			if ((uint)TAIL_TOOFAR < puVar7) {
				uVar5 = target->data[0xe] >> 0xc & 0xfff;
				if (uVar5 != 0xfff) {
					SetPlayerMessage((uint)thread->player, MissionStrings + uVar5, 2, 1);
				}
				goto LAB_000635d8;
			}
			if ((uint)TAIL_GETTINGFAR < puVar7) {
				uVar5 = target->data[0xe] & 0xfff;
				if (uVar5 != 0xfff) {
					SetPlayerMessage((uint)thread->player, MissionStrings + uVar5, 2, 1);
				}
				direction = (int)*(char *)((int)target->data + 0x3b);
				iVar3 = TAIL_GETTINGFAR;
				iVar4 = lastsay;
				goto joined_r0x00063190;
			}
			if (puVar7 <= (undefined *)(TAIL_GETTINGCLOSE + 500)) goto LAB_00063664;
		}
		if (puVar7 < (undefined *)(TAIL_GETTINGFAR + -500)) {
			lastsay = -1;
		}
	}
LAB_00063664:
	if (iVar11 != 0) {
		if (thread->player == '\0') {
			uVar5 = target->data[1] & 0x102U | 2;
		}
		else {
			uVar5 = target->data[1] & 0x102U | 0x100;
		}
		target->data[1] = uVar5;
		if (GameType == GAME_CHECKPOINT) {
			if (thread->player == '\0') {
				gPlayerScore.items = gPlayerScore.items + 1;
			}
			else {
				gPlayerScore.P2items = gPlayerScore.P2items + 1;
			}
		}
	}
	return iVar11;*/
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

int MRRequestCar(_TARGET *target)
{
	UNIMPLEMENTED();
	return 0;
	/*
	if ((DAT_000d7c3c == (_TARGET *)0x0) && (GameType != GAME_SURVIVAL)) {
		DAT_000d7c3c = target;
		return 1;
	}
	return 0;*/
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

void MRHandleCarRequests(void)
{
	UNIMPLEMENTED();
	/*
	if (DAT_000d7c3c != (_TARGET *)0x0) {
		MRCreateCar(DAT_000d7c3c);
	}
	return;*/
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

int MRCreateCar(_TARGET *target)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	int curslot;
	uint uVar2;
	int newslot;
	long lVar3;
	int direction;
	uint uVar4;
	uint uVar5;
	long local_40;
	undefined *local_3c;
	int local_38;
	char local_30[8];

	local_40 = target->data[3];
	local_38 = target->data[4];
	uVar2 = target->data[10];
	local_3c = &DAT_00002710;
	bVar1 = (uVar2 & 8) != 0;
	direction = target->data[5];
	uVar4 = target->data[7];
	uVar5 = target->data[8];
	if (target->data[9] == 2) {
		curslot = PingInCivCar(0x29a);
		curslot = curslot + -1;
	}
	else {
		curslot = CreateStationaryCivCar
		(direction, 0, (uint)((uVar2 & 0x40000) != 0) << 10, (long(*)[4])&local_40,
			uVar4 & 0xff, uVar5 & 0xff, (uint)bVar1);
	}
	if (curslot < 0) {
		requestStationaryCivCar = 1;
		direction = 0;
	}
	else {
		if (bVar1) {
			newslot = NumReplayStreams + cop_adjust;
			cop_adjust = cop_adjust + 1;
			curslot = Swap2Cars(curslot, newslot);
		}
		DAT_000d7c3c = 0;
		requestStationaryCivCar = 0;
		if ((target->data[9] == 3) && ((target->data[10] & 1U) == 0)) {
			local_30[0] = -1;
			InitPlayer(_PLAYER_ARRAY_000d979c, car_data + curslot, '\x04', direction, (long(*)[4])&local_40,
				uVar4 & 0xff, uVar5 & 0xff, local_30);
			EnablePercentageBar(&DamageBar, target->data[0xd]);
			NewLeadDelay = '\0';
		}
		target->data[3] = car_data[curslot].hd.where.t[0];
		lVar3 = car_data[curslot].hd.where.t[2];
		target->data[6] = curslot;
		target->data[1] = target->data[1] | 0x40000000;
		target->data[4] = lVar3;
		car_data[curslot].inform = target->data + 1;
		if ((uVar2 & 0x80000) != 0) {
			car_data[curslot].totalDamage = 0xffff;
			car_data[curslot].ap.damage[0] = 0xfff;
			car_data[curslot].ap.damage[1] = 0xfff;
			car_data[curslot].ap.damage[2] = 0xfff;
			car_data[curslot].ap.damage[3] = 0xfff;
			car_data[curslot].ap.damage[4] = 0xfff;
			car_data[curslot].ap.damage[5] = 0xfff;
			car_data[curslot].ap.needsDenting = '\x01';
		}
		direction = 1;
		if ((target->data[10] & 0x200000U) != 0) {
			gCarWithABerm = curslot;
		}
	}
	return direction;
	*/
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

void MRCancelCarRequest(_TARGET *target)
{
	UNIMPLEMENTED();
	/*
	if (DAT_000d7c3c == target) {
		DAT_000d7c3c = (_TARGET *)0x0;
	}
	return;
	*/
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

void PreProcessTargets(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	_TARGET *p_Var2;
	int chase;

	chase = 0;
	if (0 < MissionHeader->nCutscenes) {
		do {
			PreLoadInGameCutscene(chase);
			chase = chase + 1;
		} while (chase < MissionHeader->nCutscenes);
	}
	chase = 0xf;
	p_Var2 = MissionTargets;
	do {
		iVar1 = p_Var2->data[0];
		if (iVar1 == 4) {
		LAB_00063a48:
			PlayerStartInfo8[1] = (STREAM_SOURCE *)(ReplayStreams + 1);
			ReplayStreams[1].SourceType.type = '\x01';
			ReplayStreams[1].SourceType.model = *(uchar *)(p_Var2->data + 7);
			ReplayStreams[1].SourceType.palette = *(uchar *)(p_Var2->data + 8);
			ReplayStreams[1].SourceType.controlType = '\x01';
			ReplayStreams[1].SourceType.flags = 0;
			ReplayStreams[1].SourceType.rotation = *(ushort *)(p_Var2->data + 5);
			ReplayStreams[1].SourceType.position.vx = p_Var2->data[3];
			ReplayStreams[1].SourceType.position.vy = 0;
			ReplayStreams[1].SourceType.position.vz = p_Var2->data[4];
			if ((p_Var2->data[9] & 3U) != 0) {
				p_Var2->data[0xb] = -1;
			}
			p_Var2->data[6] = 1;
			p_Var2->data[1] = p_Var2->data[1] | 0x40000000;
		}
		else {
			if (iVar1 == 2) {
				if ((p_Var2->data[1] & 0x20U) != 0) goto LAB_00063a48;
				if ((p_Var2->data[9] == 3) && ((p_Var2->data[10] & 1U) != 0)) {
					PreLoadInGameCutscene(gRandomChase);
				}
			}
			else {
				if (iVar1 == 1) {
					if ((p_Var2->data[1] & 0x30000U) == 0x30000) {
						p_Var2->data[1] = p_Var2->data[1] | 0x102;
					}
					if ((p_Var2->data[1] & 0x100000U) != 0) {
						p_Var2->data[10] = p_Var2->data[3];
						p_Var2->data[0xb] = p_Var2->data[4];
					}
				}
			}
		}
		chase = chase + -1;
		p_Var2 = p_Var2 + 1;
		if (chase < 0) {
			return;
		}
	} while (true);
	*/
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
	if ((MissionHeader->type & 4U) != 0) 
	{
		gStopPadReads = 1;
		g321GoDelay = g321GoDelay + 1;

		if (g321GoDelay == 0x60) 
		{
			gStopPadReads = 0;
			MissionHeader->type = MissionHeader->type & 0xfffffffb;
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

int HandleGameOver(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	uint uVar2;
	int iVar3;
	int player;
	uint uVar4;
	int iVar5;
	int iVar6;
	byte *pbVar7;

	if (DAT_000d7c0c != -1) {
		gStopPadReads = 1;
		if (DAT_000d7c0c != 0) {
			gStopPadReads = 1;
			DAT_000d7c0c = DAT_000d7c0c + -1;
			return 0;
		}
		if (DAT_000d7c12 == 0) {
			if (DAT_000d7c14 == 0) {
				if (DAT_000d7c10 == PAUSEMODE_COMPLETE) {
					StoreEndData();
				}
				EnablePause(DAT_000d7c10);
				return 1;
			}
			gStopPadReads = 1;
			return 0;
		}
		gStopPadReads = 1;
		return 0;
	}
	player = 0;
	uVar2 = (uint)NumPlayers;
	uVar4 = 0;
	if (NumPlayers != 0) {
		pbVar7 = &DAT_000d7c28;
		iVar6 = 0;
		iVar5 = 0;
		do {
			if ((&player.playerType)[iVar5] == '\x01') {
				if (((DAT_000d7c28 & 0x10) != 0) || (iVar3 = TannerStuckInCar(0), iVar3 != 0)) {
					iVar3 = (int)(&player.playerCarId)[iVar5];
					if (((&MaxPlayerDamage)[player] <= (int)(uint)car_data[iVar3].totalDamage) &&
						((&player.dying)[iVar5] == '\0')) {
						(&player.dying)[iVar5] = '\x01';
					}
					if (car_data[iVar3].hd.where.m[4] < 100) {
						bVar1 = (&player.upsideDown)[iVar5] + 1;
						(&player.upsideDown)[iVar5] = bVar1;
						if ((0xb4 < bVar1) &&
							(bVar1 = (&player.dying)[iVar5],
								car_data[iVar3].totalDamage = *(ushort *)((int)&MaxPlayerDamage + iVar6),
								bVar1 < 0x1e)) {
							(&player.dying)[iVar5] = '\x1e';
						}
					}
					else {
						(&player.upsideDown)[iVar5] = '\0';
					}
				}
			}
			else {
				if ((&player.playerType)[iVar5] == '\x02') {
					test42 = GetSurfaceIndex((VECTOR *)((int)player.pos + iVar5));
					if (((test42 == -0x1a) || (test42 == -0x17)) && ((&player.dying)[iVar5] == '\0')) {
						if ((GameLevel == 3) && (gCurrentMissionNumber != 0x23)) {
							tannerDeathTimer = tannerDeathTimer + 1;
						}
						else {
							tannerDeathTimer = 0x40;
						}
					}
					else {
						tannerDeathTimer = 0;
					}
				}
			}
			if (tannerDeathTimer == 0x40) {
				(&player.dying)[iVar5] = '\x01';
			}
			bVar1 = (&player.dying)[iVar5];
			if (bVar1 != 0) {
				if (gGotInStolenCar == 0) {
					if ((*pbVar7 & 0x10) != 0) {
						BombThePlayerToHellAndBack(gCarWithABerm);
					}
					if ((&player.playerType)[iVar5] == '\x02') {
						SetPlayerMessage(player, MissionStrings + MissionHeader->msgDrowned, 2, 2);
					}
					else {
						SetPlayerMessage(player, MissionStrings + MissionHeader->msgCarWrecked, 2, 2);
					}
					(&player.dying)[iVar5] = (&player.dying)[iVar5] + '\x01';
				}
				bVar1 = (&player.dying)[iVar5];
			}
			if (0x28 < bVar1) {
				uVar4 = uVar4 + 1;
			}
			pbVar7 = pbVar7 + 0xc;
			iVar6 = iVar6 + 4;
			uVar2 = (uint)NumPlayers;
			player = player + 1;
			iVar5 = iVar5 + 0x74;
		} while (player < (int)uVar2);
	}
	if (uVar4 == 0) {
		return 0;
	}
	if (GameType == GAME_CHECKPOINT) {
	LAB_00063eb0:
		if (NumPlayers != 1) {
			if (uVar4 != uVar2) {
				return 0;
			}
			goto LAB_00063ee4;
		}
	}
	else {
		if (GameType < GAME_TRAILBLAZER) {
			if (GameType == GAME_TAKEADRIVE) goto LAB_00063eb0;
		}
		else {
			if (GameType == GAME_SECRET) goto LAB_00063eb0;
		}
	}
	player = TannerStuckInCar(0);
	if (player == 0) {
		return 0;
	}
LAB_00063ee4:
	SetMissionOver(PAUSEMODE_GAMEOVER);
	return 0;
	*/
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

void CompleteAllActiveTargets(int player)
{
	UNIMPLEMENTED();
	/*
	_TARGET *p_Var1;
	int iVar2;
	uint uVar3;
	uint uVar4;

	uVar4 = 0x800;
	if (player == 0) {
		uVar4 = 1;
		uVar3 = 2;
	}
	else {
		uVar3 = 0x100;
	}
	iVar2 = 0xf;
	p_Var1 = MissionTargets;
	do {
		if (((p_Var1->data[0] < 4) && (0 < p_Var1->data[0])) && ((p_Var1->data[1] & uVar4) != 0)) {
			p_Var1->data[1] = p_Var1->data[1] | uVar3;
		}
		iVar2 = iVar2 + -1;
		p_Var1 = p_Var1 + 1;
	} while (-1 < iVar2);
	return;
	*/
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

void SetMissionComplete(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	switch (GameType) {
	case GAME_MISSION:
		if ((DAT_000d7c28 & 0x10) != 0) {
			DAT_000d7c28 = DAT_000d7c28 | 0x20;
			DetonatorTimer();
			return;
		}
		if (gFurthestMission < gCurrentMissionNumber) {
			gFurthestMission = gCurrentMissionNumber;
		}
	default:
		SetMissionMessage(MissionStrings + MissionHeader->msgComplete, 3, 2);
		break;
	case GAME_CHECKPOINT:
	case GAME_CAPTURETHEFLAG:
	case GAME_SECRET:
		if (NumPlayers < 2) {
			SetMissionMessage(MissionStrings + MissionHeader->msgComplete, 3, 2);
			break;
		}
		if (gPlayerScore.P2items <= gPlayerScore.items) {
			if (gPlayerScore.P2items == gPlayerScore.items) {
				SetPlayerMessage(0, s_Pareggio__00011824, 3, 2);
				SetPlayerMessage(1, s_Pareggio__00011824, 3, 2);
				break;
			}
			goto LAB_000640bc;
		}
		SetPlayerMessage(0, MissionStrings + MissionHeader->msgDrowned, 3, 2);
		iVar1 = MissionHeader->msgComplete;
		goto LAB_000640ec;
	case GAME_COPSANDROBBERS:
		if (Player2DamageBar.position < Player2DamageBar.max) {
			SetPlayerMessage(0, MissionStrings + MissionHeader->msgDrowned, 3, 2);
			iVar1 = MissionHeader->msgComplete;
		}
		else {
		LAB_000640bc:
			SetPlayerMessage(0, MissionStrings + MissionHeader->msgComplete, 3, 2);
			iVar1 = MissionHeader->msgDrowned;
		}
	LAB_000640ec:
		SetPlayerMessage(1, MissionStrings + iVar1, 3, 2);
	}
	SetMissionOver(PAUSEMODE_COMPLETE);
	return;*/
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

void SetMissionFailed(FAIL_REASON reason)
{
	UNIMPLEMENTED();
	/*
	if (reason == FAILED_CnR_LOSTHIM) {
		SetPlayerMessage(0, MissionStrings + MissionHeader->msgDrowned, 3, 2);
		SetPlayerMessage(1, MissionStrings + MissionHeader->msgComplete, 3, 2);
	}
	else {
		if ((reason < FAILED_MESSAGESET) && (reason == FAILED_OUTOFTIME)) {
			SetMissionMessage(MissionStrings + MissionHeader->msgOutOfTime, 3, 2);
		}
	}
	SetMissionOver(PAUSEMODE_GAMEOVER);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetMissionOver(enum PAUSEMODE mode /*$a0*/)
 // line 3704, offset 0x00064bd8
	/* begin block 1 */
		// Start line: 9950
	/* end block 1 */
	// End Line: 9951

void SetMissionOver(PAUSEMODE mode)
{
	UNIMPLEMENTED();
	/*
	ReleaseInGameCutscene();
	PauseMissionTimer(1);
	gBombTargetVehicle = (_CAR_DATA *)0x0;
	DAT_000d7c0c = 0x3c;
	DAT_000d7c10 = mode;
	DAT_000d7c40 = 0;
	return;
	*/
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

void ActivateNextFlag(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	_TARGET *p_Var2;
	int iVar3;
	int iVar4;

	if (last_flag == -1) {
		last_flag = 0;
	}
	else {
		MissionTargets[last_flag].data[1] = MissionTargets[last_flag].data[1] | 0x102;
	}
	iVar4 = 0;
	iVar3 = last_flag;
	while (true) {
		iVar3 = iVar3 + 1;
		iVar1 = iVar3;
		if (iVar3 < 0) {
			iVar1 = iVar4 + last_flag + 0x10;
		}
		iVar1 = iVar3 + (iVar1 >> 4) * -0x10;
		p_Var2 = MissionTargets + iVar1;
		if ((p_Var2->data[0] == 1) && ((p_Var2->data[1] & 0x30000U) == 0x30000)) break;
		iVar4 = iVar4 + 1;
		if (0xf < iVar4) {
			return;
		}
	}
	p_Var2->data[1] = p_Var2->data[1] & 0xfffffefd;
	last_flag = iVar1;
	return;
	*/
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

int CalcLapTime(int player, int time, int lap)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int *piVar2;
	int iVar3;

	iVar3 = 0;
	if (0 < lap) {
		piVar2 = &gLapTimes + player * 5;
		do {
			iVar1 = *piVar2;
			piVar2 = piVar2 + 1;
			lap = lap + -1;
			iVar3 = iVar3 + iVar1;
		} while (lap != 0);
	}
	return time - iVar3;*/
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

void SetCarToBeStolen(_TARGET *target, int player)
{
	UNIMPLEMENTED();
	/*
	if ((target->data[10] & 0x800000U) != 0) {
		MakePhantomCarEqualPlayerCar();
	}
	target->data[9] = 1;
	target->data[10] = 0x30;
	target->data[0xc] = 0;
	SetPlayerMessage(player, DAT_000d7c4c, 2, 2);
	return;
	*/
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

void MakePhantomCarEqualPlayerCar(void)
{
	UNIMPLEMENTED();
	/*
	if (player.playerType == '\x01') {
		DAT_000d7c44 = (int)player.playerCarId;
	}
	return;
	*/
}
