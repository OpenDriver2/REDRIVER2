#include "driver2.h"
#include "mission.h"

#include "system.h"
#include "mgeneric.h"
#include "debris.h"
#include "dr2roads.h"
#include "spool.h"
#include "bomberman.h"
#include "cutscene.h"
#include "camera.h"
#include "overlay.h"
#include "event.h"
#include "civ_ai.h"
#include "cars.h"
#include "players.h"
#include "replays.h"
#include "glaunch.h"
#include "scores.h"
#include "ai.h"
#include "main.h"
#include "mc_snd.h"
#include "cop_ai.h"
#include "gamesnd.h"
#include "pedest.h"
#include "overmap.h"
#include "denting.h"
#include "loadsave.h"
#include "shadow.h"
#include "handling.h"
#include "cutrecorder.h"
#include "felony.h"

#ifndef PSX
#include <stdint.h>
#include <SDL.h>
#endif // PSX

char* MissionName[37] =
{
	// Chicago
	M_LTXT_ID(MTXT_Surveillancetipoff),
	M_LTXT_ID(MTXT_Chasethewitness),
	M_LTXT_ID(MTXT_Trainpursuit),
	M_LTXT_ID(MTXT_Tailingthedrop),
	M_LTXT_ID(MTXT_Escapetothesafehouse),
	M_LTXT_ID(MTXT_Chasetheintruder),
	M_LTXT_ID(MTXT_Cainescompound),
	M_LTXT_ID(MTXT_LeavingChicago),

	// Havana
	M_LTXT_ID(MTXT_Followupthelead),
	M_LTXT_ID(MTXT_Hijackthetruck),
	M_LTXT_ID(MTXT_Stopthetruck),
	M_LTXT_ID(MTXT_Findtheclue),
	M_LTXT_ID(MTXT_Escapetoferry),
	M_LTXT_ID(MTXT_Tothedocks),
	M_LTXT_ID(MTXT_BacktoJones),
	M_LTXT_ID(MTXT_TailJericho),
	M_LTXT_ID(MTXT_PursueJericho),
	M_LTXT_ID(MTXT_EscapetheBrazilians),

	// Vegas
	M_LTXT_ID(MTXT_Casinogetaway),
	M_LTXT_ID(MTXT_Beatthetrain),
	M_LTXT_ID(MTXT_Carbomb),
	M_LTXT_ID(MTXT_Carbombgetaway),
	M_LTXT_ID(MTXT_Bankjob),
	M_LTXT_ID(MTXT_Stealtheambulance),
	M_LTXT_ID(MTXT_StakeOut),
	M_LTXT_ID(MTXT_Stealthekeys),
	M_LTXT_ID(MTXT_C4deal),
	M_LTXT_ID(MTXT_Destroytheyard),

	// Rio
	M_LTXT_ID(MTXT_Buscrash),
	M_LTXT_ID(MTXT_Stealthecopcar),
	M_LTXT_ID(MTXT_Cainescash),
	M_LTXT_ID(MTXT_SaveJones),
	M_LTXT_ID(MTXT_Boatjump),
	M_LTXT_ID(MTXT_Jonesintrouble),
	M_LTXT_ID(MTXT_ChasetheGunMan),
	M_LTXT_ID(MTXT_Lennyescaping),
	M_LTXT_ID(MTXT_Lennygetscaught),
};

int gCopDifficultyLevel = 1;
int gCopRespawnTime = 0;

GAMEMODE CurrentGameMode = GAMEMODE_NORMAL;
GAMEMODE WantedGameMode = GAMEMODE_NORMAL;

GAMETYPE StoredGameType;

int GameLevel = 0;
int gInvincibleCar = 0;
int gPlayerImmune = 0;
u_char NumPlayers = 1;
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
int gCopDesiredSpeedScale = 4096;
int gCopMaxPowerScale = 4096;
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

MS_MISSION* MissionLoadAddress;
MS_MISSION* MissionHeader;
STREAM_SOURCE* PlayerStartInfo[8];
int numPlayersToCreate = 0;
int gStartOnFoot = 0;
int gWeather = WEATHER_NONE;
int gTimeOfDay = TIME_DAY;
int gShowPlayerDamage = 0;
int gDontPingInCops = 0;
int gBatterPlayer = 1;

int wantedCar[2] = { -1, -1 };

// [A]
int wantedTimeOfDay = -1;
int wantedWeather = -1;

MS_TARGET* MissionTargets;
u_int* MissionScript;
char* MissionStrings;
char* gMissionTitle = NULL;

int multiplayerregions[4];
int gMultiplayerLevels = 0;

// LEADAI
extern LEAD_PARAMETERS LeadValues;

static char NewLeadDelay = 0;

#define MISSION_IDENT		(('D' << 24) | ('2' << 16) | ('M' << 8) | 'S' )

MR_MISSION Mission;
u_int MissionStack[MAX_MISSION_THREADS][16];
MR_THREAD MissionThreads[MAX_MISSION_TARGETS];

unsigned char playercollected[2] = { 0, 0 };

const int TAIL_GETTINGCLOSE = 7000;
const int TAIL_GETTINGFAR = 12900;
const int TAIL_TOOCLOSE = 4000;
const int TAIL_TOOFAR = 15900;

#ifdef _DEBUG
#define MR_DebugPrint // printInfo
#define MR_DebugWarn printWarning
#else
#define MR_DebugPrint
#define MR_DebugWarn
#endif

int MRCommand(MR_THREAD * thread, u_int cmd);
int MROperator(MR_THREAD * thread, u_int op);
int MRFunction(MR_THREAD * thread, u_int fnc);
void MRInitialiseThread(MR_THREAD * thread, u_int * pc, u_char player);
void MRStartThread(MR_THREAD * callingthread, u_int addr, u_char player);
int MRStopThread(MR_THREAD * thread);
void MRCommitThreadGenocide();
int MRJump(MR_THREAD * thread, int jump);
void MRPush(MR_THREAD * thread, int value);
int MRPop(MR_THREAD * thread);
int MRGetParam(MR_THREAD * thread);
int MRGetVariable(MR_THREAD * thread, u_int var);
void MRSetVariable(MR_THREAD * thread, u_int var, int value);
int MRProcessTarget(MR_THREAD * thread, MS_TARGET * target);
int MRRequestCar(MS_TARGET * target);
void MRHandleCarRequests();
int MRCreateCar(MS_TARGET* target);
void MRCancelCarRequest(MS_TARGET * target);

void PreProcessTargets();
void CompleteAllActiveTargets(int player);

void SetMissionOver(PAUSEMODE mode);
void ActivateNextFlag();
int CalcLapTime(int player, int time, int lap);
void SetCarToBeStolen(MS_TARGET * target, int player);
void MakePhantomCarEqualPlayerCar();

// [D] [T]
void InitialiseMissionDefaults(void)
{
	int i;

	if (NumPlayers == 2 || GameType > GAME_TAKEADRIVE)
		lockAllTheDoors = 1;
	else
		lockAllTheDoors = 0;

	tannerDeathTimer = 0;

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

	for (i = 0; i < MAX_MISSION_THREADS; i++)
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

	Driver2TempJunctionsPtr = (u_int*)_overlay_buffer;
	NumTempJunctions = 0;
	gPlayerWithTheFlag = -1;
	last_flag = -1;

	ClearMem((char *)reservedSlots, sizeof(reservedSlots));
	_CutRec_ReserveSlots();
	
	cop_adjust = 0;

	playercollected[0] = 0;
	playercollected[1] = 0;

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

// [A] function to properly place wanted car into resident models
void SetupResidentModels()
{
	int i, j;
	int takenSlots = 0;

	// check if start data is required
	if (MissionHeader->type & 1)
	{
		// check if start data is required
		RestoreStartData();

		if (PlayerStartInfo[0]->model > 4)
			MissionHeader->residentModels[4] = PlayerStartInfo[0]->model;
	}

	for(i = 0; i < 2; i++)
	{
		if (wantedCar[i] != -1)
		{
			int foundRM = -1;
			int singlePal;
			
			for (j = 0; j < 5; j++)
			{
				if (MissionHeader->residentModels[j] == wantedCar[i])
				{
					foundRM = j;
					break;
				}
			}
			
			PlayerStartInfo[i]->model = wantedCar[i];

			singlePal = (wantedCar[i] == 0 || wantedCar[i] > 4);
			
			// check if chosen cop car or special car
			if (wantedCar[i] > 4)// && NumPlayers == 1)
			{		
				MissionHeader->residentModels[4] = wantedCar[i];
			}
			else if(foundRM == -1)
			{
				MissionHeader->residentModels[takenSlots++] = wantedCar[i];
			}
			else
			{
				// this can make things ugly
				takenSlots = foundRM+1;
			}

			// force palette
			if (singlePal)
				PlayerStartInfo[i]->palette = 0;
		}
	}
}

// [D] [T]
void LoadMission(int missionnum)
{
	int missionSize;
	ROUTE_INFO* rinfo;
	u_int loadsize;
	char filename[32];
	u_int header;
	u_int length;
	u_int offset;

	InitialiseMissionDefaults();

#ifndef PSX
	// [A] try loading mission file alone (in case if developer has modified one)
	sprintf(filename, "MISSIONS\\M%d.D2MS", missionnum);

	if (FileExists(filename))
	{
		offset = 0;
		length = 0x7ffff;	// load full file
		header = 1;			// [A] hack
	}
	else
#endif
	{
		// load from BLK
		sprintf(filename, "MISSIONS\\MISSIONS.BLK");

		if (FileExists(filename) == 0)
			return;

		LoadfileSeg(filename, (char*)&header, missionnum * 4, sizeof(int));
		offset = header & 0x7ffff;
		length = header >> 19;
	}

	if (header == 0) 
	{
#if !defined(PSX) && !defined(__EMSCRIPTEN__)
		char errPrint[1024];
		sprintf(errPrint, "%d is not valid mission\n", missionnum);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
#endif // PSX
		return;
	}

	// begin memory allocation
	D_MALLOC_BEGIN();

	if (NewLevel != 0)
	{
		MissionLoadAddress = (MS_MISSION*)mallocptr;
	}
	
	LoadfileSeg(filename, (char *)MissionLoadAddress, offset, sizeof(MS_MISSION));

	MissionHeader = MissionLoadAddress;
	MissionTargets = (MS_TARGET *)((int)MissionLoadAddress + MissionLoadAddress->size);
	MissionScript = (u_int *)(MissionTargets + MAX_MISSION_TARGETS);
	MissionStrings = (char*)((int*)MissionScript + MissionLoadAddress->strings);
	
	if (MissionLoadAddress->route && !NewLevel)
		loadsize = (int)MissionStrings + (MissionLoadAddress->route - (int)MissionLoadAddress);
	else
		loadsize = length;

	missionSize = LoadfileSeg(filename, (char *)MissionLoadAddress, offset, loadsize);

	// check if mission header itself valid
	if (MissionHeader->id != MISSION_IDENT)
	{
#if !defined(PSX) && !defined(__EMSCRIPTEN__)
		char errPrint[1024];
		sprintf(errPrint, "Invalid mission %d identifier\n", missionnum);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
#endif // PSX

		Mission.active = 0;
		return;
	}

	MissionHeader->id = 0;

	// load specific multiplayerrr regions
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

	// player start position init
	if(!_CutRec_InitMission(filename))
	{
		PlayerStartInfo[0]->rotation = MissionHeader->playerStartRotation;
		PlayerStartInfo[0]->position.vx = MissionHeader->playerStartPosition.x;
		PlayerStartInfo[0]->position.vz = MissionHeader->playerStartPosition.y;
	
#ifdef DEBUG_OPTIONS
		if(gStartPos.x != 0 && gStartPos.z != 0)
		{
			PlayerStartInfo[0]->rotation = 0;
			PlayerStartInfo[0]->position.vx = gStartPos.x;
			PlayerStartInfo[0]->position.vz = gStartPos.z;
		}
#endif
	
		PlayerStartInfo[0]->model = MissionHeader->playerCarModel;
		PlayerStartInfo[0]->palette = MissionHeader->playerCarColour;
	}

	if (MissionHeader->maxDamage != 0) 
	{
		MaxPlayerDamage[1] = MissionHeader->maxDamage;
		MaxPlayerDamage[0] = MissionHeader->maxDamage;
	}

	// setup weather and time of day
	gTimeOfDay = MissionHeader->time;
	gWeather = MissionHeader->weather;

	// [A] custom time of day
	if(wantedTimeOfDay > -1)
		gTimeOfDay = wantedTimeOfDay;

	// [A] custom weather
	if (wantedWeather > -1)
		gWeather = wantedWeather;

	if (gTimeOfDay >= TIME_NIGHT)
		gNight = 1;
	else 
		gNight = 0;

	// setup weather
	if (gWeather == WEATHER_RAIN)
	{
		gRainCount = 30;
		gEffectsTimer = 41;
	}
	else 
	{
		gRainCount = 0;
		gEffectsTimer = 0;
	}

	Mission.timer[0].flags = Mission.timer[1].flags = 0;
	Mission.timer[0].count = Mission.timer[1].count = 0;

	Mission.timer[0].x = Mission.timer[1].x = 124;
	Mission.timer[0].y = 16;
	Mission.timer[1].y = SCREEN_H / 2 + 8;
	
	if (MissionHeader->timer || (MissionHeader->timerFlags & MISSIONTIMER_FLAG_COUNTER))
	{
		int flag;

		flag = TIMER_FLAG_ACTIVE;

		if (MissionHeader->timerFlags & MISSIONTIMER_FLAG_COUNTER)
			flag |= TIMER_FLAG_COUNTER;
	
		if (MissionHeader->timerFlags & MISSIONTIMER_FLAG_COMPLETE_ON_OUT)
			flag |= TIMER_FLAG_COMPLETE_ON_OUT;

		if (MissionHeader->timerFlags & MISSIONTIMER_FLAG_BOMB_COUNTDOWN)
			flag |= TIMER_FLAG_BOMB_COUNTDOWN;

		for (int i = 0; i < NumPlayers; i++)
		{
			Mission.timer[i].flags = flag;
			Mission.timer[i].count = MissionHeader->timer * 3000;
		}
	}

	// setup cops
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

	if (!_CutRec_IsOn())
	{
		// start on foot?
		if (MissionHeader->type & 2)
		{
			PlayerStartInfo[0]->type = 2;
			PlayerStartInfo[0]->model = 0;
		}
		else
		{
			PlayerStartInfo[0]->type = 1;
		}
	}

	// load specific AI for mission
	if (NewLevel) 
	{
		if (MissionHeader->route == 0)
		{
			mallocptr += (missionSize + 3U & 0xfffffffc);

			if(LOAD_OVERLAY("PATH.BIN", _other_buffer2))
				pathAILoaded = 1;

			leadAILoaded = 0;
		}
		else 
		{
			rinfo = (ROUTE_INFO *)(MissionStrings + MissionHeader->route);

			// store route info
			NumTempJunctions = rinfo->nJunctions;
			memcpy((u_char*)Driver2TempJunctionsPtr, (u_char*)rinfo->data, NumTempJunctions << 2);
			LeadValues = rinfo->parameters;
			
			mallocptr = MissionStrings + MissionHeader->route;

			if(LOAD_OVERLAY("LEAD.BIN", _other_buffer2))
				leadAILoaded = 1;

#ifdef DEBUG
			printInfo("---- LEAD VALUES ----\n");
			printInfo("%d %d %d %d %d %d %d %d\n",
				LeadValues.tEnd,
				LeadValues.tAvelLimit,
				LeadValues.tDist,
				LeadValues.tDistMul,
				LeadValues.tWidth,
				LeadValues.tWidthMul,
				LeadValues.tWidth80,
				LeadValues.tWidth80Mul);
			printInfo("%d %d %d %d %d %d %d %d\n",
				LeadValues.hEnd,
				LeadValues.dEnd,
				LeadValues.hDist,
				LeadValues.hDistMul,
				LeadValues.hWidth,
				LeadValues.hWidthMul,
				LeadValues.hWidth80,
				LeadValues.hWidth80Mul);
#endif
			pathAILoaded = 0;
			CopsAllowed = 0;
		}
	}

	D_MALLOC_END();

	// load helicopter path if exists
	sprintf(filename, "MISSIONS\\PATH%d.%d", gCurrentMissionNumber, 0);

	if (FileExists(filename))
	{
		LoadfileSeg(filename, (char*)(MissionTargets + 4), 0, 640);
	}

	PreProcessTargets();

	// assign story mission title
	if (gCurrentMissionNumber - 1U < 40)
	{
		int titleId = gCurrentMissionNumber;

		if (titleId > 36)
			titleId--;

		if (titleId > 11)
			titleId--;
		
		if (titleId > 7)
			titleId--;

		gMissionTitle = GET_MISSION_TXT(MissionName[titleId - 1]);
	}
	else
	{
		gMissionTitle = NULL;
	}

	SetupResidentModels();

	if (GameType == GAME_CAPTURETHEFLAG)
		ActivateNextFlag();

#if 0
	{
		// MISSION SCRIPT DUMP
		u_int* script = MissionScript;

		while (true)
		{
			u_int* value = script;

			int val1, val2;
			val1 = 0;
			val2 = 0;

			switch (*value & 0xff000000)
			{
				case 0x0:
				case 0x2000000:
				case 0xff000000:
				{
					//printInfo("MR: push %d\n", *value);
					break;
				}
				case 0x1000000:
				{
					printInfo("ADDR %.3d ", script - MissionScript);

					switch (*value)
					{
						case 0x1000051:				// PlayCutscene
						{
							val1 = *--value;

							printWarning("MR command: PlayCutscene(%d)\n", val1);

							break;
						}
						case 0x1000021:			// CompleteAllActiveTargets
						{
							printWarning("MR command: CompleteAllActiveTargets\n");

							break;
						}
						case 0x1000010:			// SetVariable
						{
							val1 = *--value;
							val2 = *--value;

							switch (val1)
							{
								case 0x2000008:
									printWarning("MR command: SetVariable(Timer, %d)\n", val2);
									break;
								case 0x2000100:
									printWarning("MR command: SetVariable(gCopDesiredSpeedScale, %d)\n", val2);
									break;
								case 0x2000101:
									printWarning("MR command: SetVariable(gCopMaxPowerScale, %d)\n", val2);
									break;
								case 0x2000102:
									printWarning("MR command: SetVariable(gMinimumCops, %d)\n", val2);
									break;
								case 0x2000103:
									printWarning("MR command: SetVariable(maxCopCars, %d)\n", val2);
									break;
							}

							break;
						}
						case 0x1000011:			// Jump
						{
							val1 = *--value;

							printWarning("MR command: Jump(%d)\n", val1);

							break;
						}
						case 0x1000001:			// BranchIf
						{
							val1 = *--value;
							val2 = *--value;

							printWarning("MR command: BranchIf result != 0 TO %d\n", val1, val2);

							break;
						}
						case 0x1000022:			// MultiCarEvent
						{
							val1 = *--value;

							printWarning("MR command: MultiCarEvent(%d)\n", val1);

							break;
						}
						case 0x1000030:			// SetPlayerFelony
						{
							val1 = *--value;

							printWarning("MR command: SetPlayerFelony(%d)\n", val1);

							break;
						}
						case 0x1000050:			// ShowPlayerMessage
						{
							val1 = *--value;
							val2 = *--value;

							printWarning("MR command: ShowPlayerMessage(%d, %d)\n", val1, val2);

							break;
						}
						case 0x1000070:			// TriggerEvent
						{
							val1 = *--value;

							printWarning("MR command: TriggerEvent(%d)\n", val1);

							break;
						}
						case 0x1000080:			// SetDoorsLocked
						{
							val1 = *--value;

							printWarning("MR command: SetDoorsLocked(%d)\n", val1);

							break;
						}
						case 0x1000054:			// SetStealMessage
						{
							val1 = *--value;

							printWarning("MR command: SetStealMessage(%d)\n", val1);

							break;
						}
						case 0x1000055:			// ShowOutOfTimeMessage
						{
							printWarning("MR command: ShowOutOfTimeMessage\n");

							break;
						}
						case 0x1001000:			// StopThread
						{
							printWarning("MR command: StopThread\n");

							break;
						}
						case 0x1001002:			// StartThreadForPlayer
						{
							val1 = *--value;

							printWarning("MR command: StartThreadForPlayer(%d)\n", (value - MissionScript) + val1 + 1);

							break;
						}
						case 0x1001003:			// StartThread2
						{
							val1 = *--value;

							printWarning("MR command: StartThread2(%d)\n", (value - MissionScript) + val1 + 1);

							break;
						}
						case 0x1000100:			// SetCameraEvent
						{
							printWarning("MR command: SetCameraEvent\n");
							break;
						}
						case 0x1000071:			// AwardPlayerCheat
						{
							val1 = *--value;
							printWarning("MR command: AwardPlayerCheat %d\n", val1);

							break;
						}
						case 0x1000090:			// SetRaining
						{
							printWarning("MR command: SetRaining\n");
							break;
						}
						case 0x1000040:
						{
							printWarning("MR command: player timer flag 2 set\n");
							break;
						}
						case 0x1000042:
						{
							printWarning("MR command: timer flag 0x1000 set\n");
							break;
						}
						case 0x1000041:
						{
							printWarning("MR command: player timer flag 2 removed\n");
							break;
						}
						case 0x1001001:
						{
							printWarning("MR command: SetMissionComplete\n");
							break;
						}
					}
					break;
				}
				case 0x3000000:
				{
					printInfo("ADDR %.3d ", script - MissionScript);

					char opValue1[32] = { 0 };
					char opValue2[32] = { 0 };

					val1 = *--value;

					// MRGetParam
					switch (val1 & 0xff000000)
					{
						case 0:
						case 0xff000000:
						{
							sprintf(opValue1, "%d", val1);
							break;
						}
						case 0x2000000:
						{
							// MRGetVariable
							switch (val1)
							{
								case 0x2000008:
									sprintf(opValue1, "Timer");
									break;
								case 0x2000100:
									sprintf(opValue1, "gCopDesiredSpeedScale");
									break;
								case 0x2000101:
									sprintf(opValue1, "gCopMaxPowerScale");
									break;
								case 0x2000102:
									sprintf(opValue1, "gMinimumCops");
									break;
								case 0x2000103:
									sprintf(opValue1, "maxCopCars");
									break;
							}
						}
						default:
							sprintf(opValue1, "result");
					}

					val2 = *--value;

					// MRGetParam
					switch (val2 & 0xff000000)
					{
						case 0:
						case 0xff000000:
						{
							sprintf(opValue2, "%d", val2);
							break;
						}
						case 0x2000000:
						{
							// MRGetVariable
							switch (val2)
							{
								case 0x2000008:
									sprintf(opValue2, "Timer");
									break;
								case 0x2000100:
									sprintf(opValue2, "gCopDesiredSpeedScale");
									break;
								case 0x2000101:
									sprintf(opValue2, "gCopMaxPowerScale");
									break;
								case 0x2000102:
									sprintf(opValue2, "gMinimumCops");
									break;
								case 0x2000103:
									sprintf(opValue2, "maxCopCars");
									break;
							}
						}
						default:
							sprintf(opValue2, "result");
					}

					value += 2;

					switch (*value)
					{
						case 0x3000003: // AND
							printWarning("MR: operator %s && %s\n", opValue1, opValue2);
							break;
						case 0x3000004:	// OR
							printWarning("MR: operator %s || %s\n", opValue1, opValue2);
							break;
						case 0x3000005:	// NEQ
							printWarning("MR: operator %s != %s\n", opValue1, opValue2);
							break;
						case 0x3000006:	// EQ
							printWarning("MR: operator %s == %s\n", opValue1, opValue2);
							break;
						case 0x3000007: // GT
							printWarning("MR: operator %s > %s\n", opValue1, opValue2);
							break;
						case 0x3000008:	// LT
							printWarning("MR: operator %s < %s\n", opValue1, opValue2);
							break;
						case 0x3000009: // ADD
							printWarning("MR: operator %s + %s\n", opValue1, opValue2);
							break;
						default:
							printWarning("MR: operator INVALID\n");
					}

					break;
				}
				case 0x4000000:
				{
					printInfo("ADDR %.3d ", script - MissionScript);

					if (*value == 0x4000020)
					{
						val1 = *--value;
						printWarning("MR: function MRProcessTarget %d\n", val1);
					}

					
					break;
				}
			}

			script++;
		}
	}
#endif
	

	MRInitialiseThread(&MissionThreads[0], MissionScript, 0);
}

// [D] [T]
void HandleTimer(MR_TIMER *timer)
{
	if (timer->flags & TIMER_FLAG_PAUSED)
		return;

	if (!(timer->flags & TIMER_FLAG_ACTIVE))
		return;

	if (timer->flags & TIMER_FLAG_COUNTER)
	{
		timer->count += 100;

		if (timer->count > 10799999)
			timer->count = 10799999;
	}
	else 
	{
		timer->count -= 100;

		if (timer->count < 1)
		{
			if ((MissionHeader->timerFlags & MISSIONTIMER_FLAG_BOMB_TIMER) && DetonatorTimer())
			{
				MissionHeader->timerFlags &= ~MISSIONTIMER_FLAG_BOMB_TIMER;

				timer->count = 9000;
				timer->flags |= 0x28;
			}
			else 
			{
				// do expolosions
				if (timer->flags & TIMER_FLAG_COMPLETE_ON_OUT)
				{
					if (Mission.gameover_delay == -1)
					{
						SetMissionComplete();	
					}

					timer->count = 0;
				}
				else
				{
					if (Mission.gameover_delay == -1)
					{
						SetMissionFailed(FAILED_OUTOFTIME);
					}

					if (timer->flags & TIMER_FLAG_BOMB_COUNTDOWN)
					{
						events.cameraEvent = (EVENT*)0x1;

						BombThePlayerToHellAndBack(gCarWithABerm);
					}

					timer->count = 0;
				}
			}
		}
	}

	timer->min = (timer->count / 180000);
	timer->sec = (timer->count / 3000) - timer->min * 60;
	timer->frac = (timer->count % 3000) / 30;
}


// [D] [T]
void RegisterChaseHit(int car1, int car2)
{
	int player_id;

	if (Mission.ChaseTarget && Mission.ChaseHitDelay == 0) 
	{
		if (gPlayerWithTheFlag == -1) 
		{
			if (car1 == Mission.ChaseTarget->s.car.slot || car2 == Mission.ChaseTarget->s.car.slot)
			{
				Mission.ChaseTarget->s.car.chasing.maxDamage--;
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

			SetPlayerMessage(player_id, G_LTXT(GTXT_YouGotTheFlag),2,1);
		}
	}
}


// [D] [T]
void PauseMissionTimer(int pause)
{
	if (pause == 0) 
	{
		Mission.timer[0].flags &= ~TIMER_FLAG_PAUSED;
		Mission.timer[1].flags &= ~TIMER_FLAG_PAUSED;
	}
	else 
	{
		Mission.timer[0].flags |= TIMER_FLAG_PAUSED;
		Mission.timer[1].flags |= TIMER_FLAG_PAUSED;
	}
}

// [D] [T]
void SetMissionMessage(char *message, int priority, int seconds)
{
	int i;

	if (message == MissionStrings - 1 || message == NULL || NumPlayers == 0)
		return;

	for (i = 0; i < NumPlayers; i++)
	{
		if (Mission.message_timer[i] == 0 || Mission.message_priority[i] <= priority)
		{
			Mission.message_string[i] = message;
			Mission.message_priority[i] = priority;
				
			if (seconds == 0) 
			{
				Mission.message_timer[i] = 5;
			}
			else 
			{
				Mission.message_timer[i] = seconds * 30;
			}
		}
	}
}

// [D] [T]
void SetPlayerMessage(int player, char *message, int priority, int seconds)
{
	if (message == MissionStrings-1 || message == NULL)
		return;

	if (Mission.message_timer[player] != 0 && Mission.message_priority[player] > priority)
		return;

	Mission.message_string[player] = message;
	Mission.message_priority[player] = priority;
	Mission.message_timer[player] = seconds * 30;
}

// [D] [T]
int TargetComplete(MS_TARGET *target, int player)
{
	u_int flag;

	if (player == 0) 
		flag = TARGET_FLAG_COMPLETED_P1;
	else if (player == 1)
		flag = TARGET_FLAG_COMPLETED_P2;
	else
		flag = TARGET_FLAG_COMPLETED_ALLP;

	return (target->s.target_flags & flag) == flag;
}


// [D] [T]
int TargetActive(MS_TARGET *target, int player)
{
	u_int flag;

	if (player == 0)
		flag = TARGET_FLAG_ACTIVE_P1;
	else if (player == 1)
		flag = TARGET_FLAG_ACTIVE_P2;
	else
		flag = TARGET_FLAG_ACTIVE_ALLP;

	return (target->s.target_flags & flag) == flag;
}

// [D] [T]
int Swap2Cars(int curslot, int newslot)
{
	CAR_DATA *cp;

	int ctrlNodeNewId;
	int pnodeNewId;
	int ctrlNodeCurId;
	int pnodeCurId;
	int tmp;

	CAR_DATA cd;

	if (curslot == newslot)
		return newslot;

	ctrlNodeNewId = -1;
	pnodeNewId = -1;

	ctrlNodeCurId = -1;
	pnodeCurId = -1;

	// hold cur slot nodes
	cp = &car_data[curslot];

	if (cp->controlType == CONTROL_TYPE_CIV_AI)
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
	if (cp->controlType == CONTROL_TYPE_CIV_AI)
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
	memcpy((u_char*)&cd, (u_char*)&car_data[newslot], sizeof(CAR_DATA));
	memcpy((u_char*)&car_data[newslot], (u_char*)&car_data[curslot], sizeof(CAR_DATA));
	memcpy((u_char*)&car_data[curslot], (u_char*)&cd, sizeof(CAR_DATA));

	// [A] event - swap cars on boat
	tmp = carsOnBoat & (1 << newslot);
	carsOnBoat &= ~(1 << newslot);

	if (carsOnBoat & (1 << curslot))
		carsOnBoat |= (1 << newslot);

	if(tmp)
		carsOnBoat |= (1 << curslot);

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

	ResetTyreTracks(cp, GetPlayerId(cp));

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

	ResetTyreTracks(cp, GetPlayerId(cp));

	gDontResetCarDamage = 0;

	// [A] swap cars in targets and fix "Bank Job" bug
	for (int i = 0; i < MAX_MISSION_TARGETS; i++)
	{
		MS_TARGET* swapTgt = &MissionTargets[i];

		if (swapTgt->type == Target_Car)
		{
			if (swapTgt->s.car.slot == curslot)
				swapTgt->s.car.slot = newslot;
			else if (swapTgt->s.car.slot == newslot)
				swapTgt->s.car.slot = curslot;
		}		
	}

	return newslot;
}

// [D] [T]
void SetConfusedCar(int slot)
{
	car_data[slot].controlType = CONTROL_TYPE_CIV_AI;

	car_data[slot].ai.c.thrustState = 3;
	car_data[slot].ai.c.ctrlState = 7;

	car_data[slot].ai.c.ctrlNode = NULL;

	if (slot == player[0].worldCentreCarId) // [A] Rev 1.1
	{
		if (player[0].playerCarId >= 0)
			player[0].worldCentreCarId = player[0].playerCarId;
	}
}


// [D] [T]
void HandleMissionThreads(void)
{
	int i;
	MR_THREAD* thread;
	int running;
	u_int value;

	for (i = 0; i < MAX_MISSION_TARGETS; i++)
		MissionTargets[i].s.target_flags &= ~TARGET_FLAG_VISIBLE_ALLP;

	for (i = 0; i < MAX_MISSION_THREADS; i++)
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

		// [A] handle car requets after each thread
		MRHandleCarRequests();
	}
}

// [D] [T]
int MRCommand(MR_THREAD *thread, u_int cmd)
{
	int val1;
	int val2;

	if (cmd == 0x1000051)				// PlayCutscene
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR %d command: PlayCutscene(%d)\n", thread-MissionThreads, val1);

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
		MR_DebugWarn("MR %d command: CompleteAllActiveTargets\n", thread - MissionThreads);

		CompleteAllActiveTargets(thread->player);
		return 1;
	}
	else if (cmd == 0x1000010)			// SetVariable
	{
		val1 = MRPop(thread);
		val2 = MRPop(thread);

		MR_DebugWarn("MR %d command: SetVariable(%08X, %d)\n", thread - MissionThreads, val1, val2);

		MRSetVariable(thread, val1, val2);

		return 1;
	}
	else if (cmd == 0x1000011)			// Jump
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR %d command: Jump(%d)\n", thread - MissionThreads, val1);

		return MRJump(thread, val1);
	}
	else if (cmd == 0x1000001)			// BranchIf
	{
		val1 = MRPop(thread);
		val2 = MRPop(thread);

		if (val2 != 0)
		{
			MR_DebugWarn("MR %d command: Goto(%d)\n", thread - MissionThreads, val1);
			return 1;
		}

		return MRJump(thread, val1);
	}
	else if (cmd == 0x1000022)			// MultiCarEvent
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR %d command: MultiCarEvent(%d)\n", thread - MissionThreads, val1);

		MultiCarEvent(&MissionTargets[val1]);
		return 1;
	}
	else if (cmd == 0x1000030)			// SetPlayerFelony
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR %d command: SetPlayerFelony(%d)\n", thread - MissionThreads, val1);

		if (player[0].playerCarId < 0)
			pedestrianFelony = val1;
		else
			car_data[player[0].playerCarId].felonyRating = val1;
	}
	else if (cmd == 0x1000050)			// ShowPlayerMessage
	{
		val1 = MRPop(thread);
		val2 = MRPop(thread);

		MR_DebugWarn("MR %d command: ShowPlayerMessage(%d, %d)\n", thread - MissionThreads, val1, val2);

		SetPlayerMessage(thread->player, MissionStrings + val1, 0, val2);

		return 1;
	}
	else if (cmd == 0x1000070)			// TriggerEvent
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR %d command: TriggerEvent(%d)\n", thread - MissionThreads, val1);

		TriggerEvent(val1);
		return 1;
	}
	else if (cmd == 0x1000080)			// SetDoorsLocked
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR %d command: SetDoorsLocked(%d)\n", thread - MissionThreads, val1);

		lockAllTheDoors = val1;
		return 1;
	}
	else if (cmd == 0x1000054)			// SetStealMessage
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR %d command: SetStealMessage(%d)\n", thread - MissionThreads, val1);

		Mission.StealMessage = MissionStrings + val1;
	}
	else if (cmd == 0x1000055)			// ShowOutOfTimeMessage
	{
		MR_DebugWarn("MR %d command: ShowOutOfTimeMessage\n", thread - MissionThreads);

		SetPlayerMessage(1, MissionStrings + MissionHeader->msgOutOfTime, 2, 2);
		return 1;
	}
	else if (cmd == 0x1001000)			// StopThread
	{
		MR_DebugWarn("MR %d command: StopThread\n", thread - MissionThreads);

		return MRStopThread(thread);
	}
	else if (cmd == 0x1001002)			// StartThreadForPlayer
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR %d command: StartThreadForPlayer(%d)\n", thread - MissionThreads, val1);

		MRStartThread(thread, val1, thread->player);
		return 1;
	}
	else if (cmd == 0x1001003)			// StartThread2
	{
		val1 = MRPop(thread);

		MR_DebugWarn("MR %d command: StartThread2(%d)\n", thread - MissionThreads, val1);

		MRStartThread(thread, val1, 1);
		return 1;
	}
	else if (cmd == 0x1000100)			// SetCameraEvent
	{
		MR_DebugWarn("MR %d command: SetCameraEvent\n", thread - MissionThreads);

		SetSpecialCamera(SPECIAL_CAMERA_SET, 0);
		return 1;
	}
	else if (cmd == 0x1000071)			// AwardPlayerCheat
	{
		MR_DebugWarn("MR %d command: AwardPlayerCheat\n", thread - MissionThreads);

		val1 = MRPop(thread);

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
		if ((val1 & 0x4000) != 0) {
			AvailableCheats.cheat2 = 1;
		}
		if ((val1 & 0x2000) != 0) {
			AvailableCheats.cheat11 = 1;
		}
		if ((val1 & 0x8000) != 0) {
			AvailableCheats.cheat1 = 1;
		}
		if ((val1 & 0x10000) != 0) {
			AvailableCheats.cheat3 = 1;
		}
		if ((val1 & 0x20000) != 0) {
			AvailableCheats.cheat4 = 1;
		}

#ifndef PSX
		SaveCurrentProfile(0);
#endif

		return 1;
	}
	else if (cmd == 0x1000090)			// SetRaining
	{
		MR_DebugWarn("MR %d command: SetRaining\n", thread - MissionThreads);
		gWeather = WEATHER_RAIN;
		return 1;
	}
	else if (cmd == 0x1000040)
	{
		MR_DebugWarn("MR %d command: player timer flag 2 set\n", thread - MissionThreads);
		Mission.timer[thread->player].flags |= TIMER_FLAG_COUNTER;
	}
	else  if (cmd == 0x1000042)
	{
		MR_DebugWarn("MR %d command: timer flag 0x1000 set\n", thread - MissionThreads);
		MissionHeader->timerFlags |= MISSIONTIMER_FLAG_BOMB_TIMER;
	}
	else if (cmd == 0x1000041)
	{
		MR_DebugWarn("MR %d command: player timer flag 2 removed\n", thread - MissionThreads);
		Mission.timer[thread->player].flags &= ~TIMER_FLAG_COUNTER;
		return 1;
	}
	else if (cmd == 0x1001001)
	{
		MR_DebugWarn("MR %d command: SetMissionComplete\n", thread - MissionThreads);
		SetMissionComplete();
		return 1;
	}

	return 1;
}

// [D] [T]
int MROperator(MR_THREAD *thread, u_int op)
{
	int val1;
	int val2;
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

// [D] [T]
int MRFunction(MR_THREAD *thread, u_int fnc)
{
	int value;

	if (fnc == 0x4000020) 
	{
		value = MRPop(thread);
		value = MRProcessTarget(thread, &MissionTargets[value]);

		MRPush(thread, value);

		return 1;
	}

	return MRStopThread(thread);
}

// [D] [T]
void MRInitialiseThread(MR_THREAD *thread, u_int *pc, u_char player)
{
	thread->active = 1;
	thread->pc = pc;
	thread->player = player;
	thread->sp = thread->initial_sp;
}


// [D] [T]
void MRStartThread(MR_THREAD *callingthread, u_int addr, unsigned char player)
{
	int i;
	for (i = 0; i < MAX_MISSION_THREADS; i++)
	{
		if (!MissionThreads[i].active)
		{
			MRInitialiseThread(&MissionThreads[i], callingthread->pc + addr, player);
			break;
		}
	}
}

// [D] [T]
int MRStopThread(MR_THREAD *thread)
{
	thread->active = 0;
	return 0;
}

// [D] [T]
void MRCommitThreadGenocide(void)
{
	int i;
	for (i = 0; i < MAX_MISSION_THREADS; i++)
		MRStopThread(&MissionThreads[i]);
}

// [D] [T]
int MRJump(MR_THREAD *thread, int jump)
{
	if ((jump + 2U) < 3)
		return MRStopThread(thread);

	thread->pc += jump;
	return ~jump >> 31;
}

// [D] [T]
void MRPush(MR_THREAD *thread, int value)
{
	*thread->sp = value;
	thread->sp++;
}

// [D] [T]
int MRPop(MR_THREAD *thread)
{
	thread->sp--;
	return *thread->sp;
}

// [D] [T]
int MRGetParam(MR_THREAD *thread)
{
	int value;

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

// [D] [T]
int MRGetVariable(MR_THREAD *thread, u_int var)
{
	switch (var)
	{
		case 0x2000008: 
			return Mission.timer[thread->player].count / 3000;
		case 0x2000100:
			return gCopDesiredSpeedScale;
		case 0x2000101:
			return gCopMaxPowerScale;
		case 0x2000102:
			return gMinimumCops;
		case 0x2000103:
			return maxCopCars;
	}
	
	return 0;
}

// [D] [T]
void MRSetVariable(MR_THREAD *thread, u_int var, int value)
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

// [D] [T]
int MRProcessTarget(MR_THREAD *thread, MS_TARGET *target)
{
	int phrase;
	int playerId;
	u_int dist;
	char *message;
	int ret;
	VECTOR tv;
	VECTOR pv;
	LONGVECTOR4 pos;
	int slot;

	ret = 0;

	if (TargetComplete(target, thread->player)) 
		return 1;

	if (thread->player == 0) 
		target->s.target_flags |= (TARGET_FLAG_VISIBLE_P1 | TARGET_FLAG_ACTIVE_P1);
	else 
		target->s.target_flags |= (TARGET_FLAG_VISIBLE_P2 | TARGET_FLAG_ACTIVE_P2);

	playerId = thread->player;
	pv.vx = player[playerId].pos[0];
	pv.vy = player[playerId].pos[1];
	pv.vz = player[playerId].pos[2];

	switch(target->type)
	{
		case Target_Point: // point target
		{
			if (target->s.target_flags & TARGET_FLAG_POINT_ON_BOAT)
			{
				tv.vx = target->s.point.boatOffsetX;
				tv.vz = target->s.point.boatOffsetZ;

				OffsetTarget(&tv);

				target->s.point.posX = tv.vx;
				target->s.point.posZ = tv.vz;
			}
			else if (target->s.target_flags & TARGET_FLAG_POINT_STOP_COPS_TRIGGER)	// set stop cops
			{
				target->s.target_flags &= ~TARGET_FLAG_POINT_STOP_COPS_TRIGGER;

				gStopCops.radius = target->s.point.radius;
				gStopCops.pos.vx = target->s.point.posX;
				gStopCops.pos.vy = 0;
				gStopCops.pos.vz = target->s.point.posZ;
			}
			else
			{
				tv.vx = target->s.point.posX;
				tv.vz = target->s.point.posZ;
				tv.vy = 0;
			}
			
			if (Long2DDistance(&tv, &pv) <= target->s.point.radius)
			{
				if (target->s.point.height != 0) // if target is at height (Train pursuit)
				{
					if (target->s.point.height < ABS(target->s.point.posY + pv.vy))
						target->s.point.actionFlag &= ~0xFFF0;
				}

				if (GameType == GAME_SECRET)
				{
					switch(target->s.target_flags & (TARGET_FLAG_POINT_SECRET_POINT1 | TARGET_FLAG_POINT_SECRET_POINT2 | TARGET_FLAG_POINT_SECRET_STARTFINISH))
					{
						case 0: // TARGET_FLAG_POINT_SECRET_POINT0
						{
							playercollected[thread->player] |= 0x1;
							break;
						}
						case TARGET_FLAG_POINT_SECRET_POINT1:
						{
							playercollected[thread->player] |= 0x2;
							break;
						}
						case TARGET_FLAG_POINT_SECRET_POINT2:
						{
							playercollected[thread->player] |= 0x4;
							break;
						}
						case TARGET_FLAG_POINT_SECRET_STARTFINISH:
						{
							if (playercollected[thread->player] == 0x7)
							{
								playercollected[thread->player] = 0;

								if (thread->player == 0)
								{
									gLapTimes[thread->player][gPlayerScore.items] = CalcLapTime(0, Mission.timer[0].count, gPlayerScore.items);
									gPlayerScore.items++;

									if (gPlayerScore.items == gNumRaceTrackLaps)
									{
										SetMissionComplete();
									}
								}
								else
								{
									gLapTimes[thread->player][gPlayerScore.P2items] = CalcLapTime(1, Mission.timer[1].count, gPlayerScore.P2items);
									gPlayerScore.P2items++;

									if (gPlayerScore.P2items == gNumRaceTrackLaps)
									{
										SetMissionComplete();
									}
								}
							}
							break;
						}
					}
					
					return 0;
				}

				switch (target->s.target_flags & (TARGET_FLAG_POINT_CTF_BASE_P1 | TARGET_FLAG_POINT_CTF_BASE_P2 | TARGET_FLAG_POINT_CTF_FLAG))
				{
					case 0:
					{
						int actionFlag;
						actionFlag = target->s.point.actionFlag;

						if (actionFlag)
						{
							// Tanner action (planting bombs, garage doors)
							int val;
							val = ((actionFlag & 0xfff0) >> 4) + 1;

							if ((actionFlag & 0xf) <= val / 30)
							{
								message = MissionStrings + (actionFlag >> 0x10);
								SetPlayerMessage(thread->player, message, 2, 0);
							}

							target->s.point.actionFlag = (actionFlag >> 0x10) << 0x10 | (val << 4) | actionFlag & 0xf;
							gTannerActionNeeded = 1;

							if (TannerActionHappening())
							{
								ret = 1;
							}
						}
						else
						{
							// Handling of Lose Tail message
							if (target->s.point.loseTailMessage != -1 && copsAreInPursuit)
							{
								if (Mission.message_timer[0] == 0 && prevCopsInPursuit == 0)
								{
									// lose tail
									SetPlayerMessage(thread->player, MissionStrings + target->s.point.loseTailMessage, 2, 2);
									prevCopsInPursuit = copsAreInPursuit;
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

						if (target->s.target_flags & 0x400000)
							return 1;

						if ((target->s.target_flags & TARGET_FLAG_POINT_PLAYER_MUSTHAVE_CAR) && player[thread->player].playerType != 1)
							ret = 0;

						break;
					}
					case TARGET_FLAG_POINT_CTF_BASE_P1: // CTF mode (multiplayer)
					case TARGET_FLAG_POINT_CTF_BASE_P2:
					{
						if (gPlayerWithTheFlag == thread->player)
						{
							int correctZone;

							correctZone =	(target->s.target_flags & TARGET_FLAG_POINT_CTF_BASE_P1) && thread->player == 0 ||
											(target->s.target_flags & TARGET_FLAG_POINT_CTF_BASE_P2) && thread->player == 1;

							if(correctZone)
							{
								if (thread->player == 0)
								{
									gPlayerScore.items++;
								}
								else if (thread->player == 1)
								{
									gPlayerScore.P2items++;
								}

								gPlayerWithTheFlag = -1;

								SetPlayerMessage(thread->player, G_LTXT(GTXT_WellDone), 2, 1);

								player[0].targetCarId = -1;
								player[1].targetCarId = -1;

								ActivateNextFlag();
							}
						}
						break;
					}
					case TARGET_FLAG_POINT_CTF_FLAG:
					{
						if (gPlayerWithTheFlag == -1)
						{
							Mission.ChaseTarget = MissionTargets;
							gPlayerWithTheFlag = thread->player;

							SetPlayerMessage(thread->player, G_LTXT(GTXT_YouGotTheFlag), 2, 1);

							player[1 - gPlayerWithTheFlag].targetCarId = gPlayerWithTheFlag;
						}
						break;
					}

				}
			}
			else
			{
				target->s.point.actionFlag &= ~0xFFF0;
			}

			break;
		}
		case Target_Car: // car target
		{
			CAR_DATA* cp;
			tv.vx = target->s.car.posX;
			tv.vz = target->s.car.posZ;
			tv.vy = 0;
	
			dist = Long2DDistance(&tv, &pv);
			slot = target->s.car.slot;

			if (slot == -1)
			{
				if (dist < 18000 || target->s.car.type == 3 && !(target->s.car.flags & CARTARGET_FLAG_RANDOMCHASE))
					MRRequestCar(target);
				else
					MRCancelCarRequest(target);
				
				break;
			}

			cp = &car_data[slot];

			if (target->s.target_flags & TARGET_FLAG_CAR_PINGED_IN)
			{
				target->s.car.posX = cp->hd.where.t[0];
				target->s.car.posZ = cp->hd.where.t[2];

				// make Caine's Compound vans moving
				if (target->s.car.type == 1)
				{
					if (target->s.car.maxDistance != 0 && dist < target->s.car.maxDistance)
					{
						int direction, model, palette;
						int *inform;

						direction = cp->hd.direction;
						model = cp->ap.model;
						palette = cp->ap.palette;
						inform = cp->inform;

						pos[0] = cp->hd.where.t[0];
						pos[1] = cp->hd.where.t[1];
						pos[2] = cp->hd.where.t[2];

						cp->inform = NULL;

						PingOutCar(&car_data[slot]);
						slot = CreateCivCarWotDrivesABitThenStops(direction, &pos, NULL, model, palette);

						cp->inform = inform;

						target->s.car.slot = slot;
						target->s.car.maxDistance = 0;
					}
				}
				else if (target->s.car.type == 3)
				{
					if((target->s.target_flags & TARGET_FLAG_CAR_PLAYERCONTROLLED) == 0)
					{
						if(target->s.car.flags & CARTARGET_FLAG_RANDOMCHASE)
						{
							if (target->s.car.cutscene == -1)
							{
								if (gInGameChaseActive == 0)
								{
									Mission.ChaseTarget = NULL;
									player[0].targetCarId = -1;
									gBombTargetVehicle = NULL;

									if ((target->s.car.flags & 0xf0) != CARTARGET_FLAG_STEAL_TARGET)
									{
										if (target->s.car.flags & CARTARGET_FLAG_TO_BE_STOLEN)
											SetCarToBeStolen(target, thread->player);
										else
											ret = 1;
									}
								}
							}
							else
							{
								if (dist < target->s.car.maxDistance && (MissionHeader->type & 4) == 0)
								{
									TriggerChase(&slot, target->s.car.cutscene);

									target->s.car.cutscene = -1;
									target->s.car.slot = slot;

									player[0].targetCarId = slot;
									Mission.ChaseTarget = target;
								}
							}
						}
						else
						{
							if (cp->totalDamage >= target->s.car.chasing.maxDamage)
							{
								if (NewLeadDelay != 1)
								{
									if (target->s.car.flags & CARTARGET_FLAG_TO_BE_STOLEN)
									{
										DamageBar.position = target->s.car.chasing.maxDamage;

										cp->totalDamage = MaxPlayerDamage[0];

										SetConfusedCar(slot);
										SetCarToBeStolen(target, thread->player);

										NewLeadDelay = 1;
									}
									else
									{
										ret = 0;

										DamageBar.position = target->s.car.chasing.maxDamage;

										cp->totalDamage = MaxPlayerDamage[0] - 1;
										SetConfusedCar(slot);

										NewLeadDelay = 1;
									}

									break;
								}

								ret = 1;
							}
						}
					}

					if (target->s.car.flags & CARTARGET_FLAG_THROWS_BOMBS)
					{
						gBombTargetVehicle = &car_data[slot];
					}
				}

				switch(target->s.car.flags & 0xf0)
				{
					case 0:
					{
						// check damage
						if (target->s.car.chasing.maxDamage > 0)
						{
							// first we init damage bar
							if (DamageBar.active == 0)
							{
								if (gCurrentMissionNumber != 2 &&
									gCurrentMissionNumber != 6)
								{
									EnablePercentageBar(&DamageBar, target->s.car.chasing.maxDamage);
								}

								if (gCurrentMissionNumber == 11 ||
									gCurrentMissionNumber == 13 ||
									gCurrentMissionNumber == 26)
								{
									target->s.car.chasing.maxDamage = (target->s.car.chasing.maxDamage * 3) / 4;
								}
							}
						}
						else
						{
							ReleaseInGameCutscene();

							Mission.ChaseTarget = NULL;
							player[0].targetCarId = -1;

							gBombTargetVehicle = NULL;

							SetConfusedCar(slot);

							if (target->s.car.flags & CARTARGET_FLAG_PED_ESCAPES)
							{
								cp->controlFlags &= ~CONTROL_FLAG_WAS_PARKED;

								pos[0] = cp->hd.where.t[0];
								pos[2] = cp->hd.where.t[2];
								pos[1] = -cp->hd.where.t[1];

								CreatePedAtLocation(&pos, 8);
							}

							if (target->s.car.flags & CARTARGET_FLAG_TO_BE_STOLEN)
							{
								SetCarToBeStolen(target, thread->player);

								if (gCurrentMissionNumber == 11 || gCurrentMissionNumber == 13 || gCurrentMissionNumber == 26)
									cp->totalDamage = (MaxPlayerDamage[0] * 3) / 4;
								else
									cp->totalDamage = MaxPlayerDamage[0];

								DamageBar.active = 0;
							}
							else
							{
								ret = 1;
							}
						}

						// check distance
						if (dist > TAIL_TOOFAR)
						{
							message = MissionStrings + target->s.car.chasing.tooFarMessage;

							SetPlayerMessage(thread->player, message, 2, 2);
							SetMissionFailed(FAILED_MESSAGESET);

							break;
						}

						if (dist > TAIL_GETTINGFAR)
						{
							if (target->s.car.chasing.gettingFarMessage != 255 && TAIL_GETTINGFAR != lastsay)
							{
								MissionSay(target->s.car.chasing.gettingFarMessage);
								lastsay = TAIL_GETTINGFAR;
							}

							break;
						}

						if (dist < TAIL_GETTINGFAR - 500)
						{
							lastsay = -1;
						}
						
						break;
					}
					case CATTARGET_FLAG_PROXIMITY_TARGET:	// proximity extended messages
					{
						ProxyBar.active = 1;
						ProxyBar.position = dist;

						if (dist < TAIL_TOOCLOSE)
						{
							int messageId;
							messageId = target->s.car.tail.closeMessages >> 0xc & 0xfff;

							if (messageId != 0xfff)
							{
								message = MissionStrings + messageId;
								SetPlayerMessage(thread->player, message, 2, 1);
							}

							SetMissionFailed(FAILED_MESSAGESET);

							break;
						}

						if (dist < TAIL_GETTINGCLOSE)
						{
							int messageId;
							messageId = target->s.car.tail.closeMessages & 0xfff;

							if (messageId != 0xfff)
							{
								message = MissionStrings + messageId;
								SetPlayerMessage(thread->player, message, 2, 1);
							}

							phrase = target->s.car.tail.closeMessages >> 24 & 0xFF;

							if (phrase != 0xff && lastsay != TAIL_GETTINGCLOSE)
							{
								MissionSay(phrase);
								lastsay = TAIL_GETTINGCLOSE;
							}

							break;
						}

						if (dist > TAIL_TOOFAR)
						{
							int messageId;
							messageId = target->s.car.tail.farMessages >> 0xc & 0xfff;

							if (messageId != 0xfff)
							{
								message = MissionStrings + messageId;
								SetPlayerMessage(thread->player, message, 2, 1);
							}

							SetMissionFailed(FAILED_MESSAGESET);

							break;
						}

						if (dist > TAIL_GETTINGFAR)
						{
							int messageId;
							messageId = target->s.car.tail.farMessages & 0xfff;

							if (messageId != 0xfff)
							{
								message = MissionStrings + messageId;
								SetPlayerMessage(thread->player, message, 2, 1);
							}

							phrase = target->s.car.tail.farMessages >> 24 & 0xFF;

							if (phrase != 0xff && lastsay != TAIL_GETTINGFAR)
							{
								MissionSay(phrase);
								lastsay = TAIL_GETTINGFAR;
							}

							break;
						}

						if (dist <= TAIL_GETTINGCLOSE + 500)
						{
							break;
						}

						if (dist < TAIL_GETTINGFAR - 500)
						{
							lastsay = -1;
						}
						
						break;
					}
					case 0x20:
					{
						break;
					}
					case CARTARGET_FLAG_STEAL_TARGET:
					{
						// Find the Clue and Steal the keys
						int failIfDamaged;

						failIfDamaged = (gCurrentMissionNumber != 14 && gCurrentMissionNumber != 19 && gCurrentMissionNumber != 28);

						// check if player entered the car
						if (player[0].playerCarId == slot)
						{
							// signal to mission about stolen car so Find the Clue/Steal the keys can progress
							if (!failIfDamaged)
							{
								gGotInStolenCar = 1;
								cp->totalDamage = MaxPlayerDamage[0];
							}

							ret = 1;
						}

						// check if target car is damaged
						if(failIfDamaged && cp->totalDamage >= MaxPlayerDamage[0])
						{
							message = MissionStrings + MissionHeader->msgCarWrecked;

							SetPlayerMessage(thread->player, message, 2, 1);
							SetMissionFailed(FAILED_MESSAGESET);
						}
						break;
					}
					case CARTARGET_FLAG_ESCAPE_TARGET:
					{
						if (copsAreInPursuit)
							ret = 1;

						break;
					}
					case CARTARGET_FLAG_CnR_TARGET:
					{
						if(target->s.target_flags & TARGET_FLAG_CAR_PLAYERCONTROLLED)
						{
							MaxPlayerDamage[1] = target->s.car.chasing.maxDamage;

							if (dist > TAIL_TOOFAR)
							{
								if (GameType == GAME_COPSANDROBBERS)
								{
									SetMissionFailed(FAILED_CnR_LOSTHIM);
									break;
								}

								message = MissionStrings + target->s.car.chasing.tooFarMessage;

								SetPlayerMessage(thread->player, message, 2, 2);
								SetMissionFailed(FAILED_MESSAGESET);
								break;
							}
						}

						if (cp->totalDamage >= target->s.car.chasing.maxDamage)
						{
							ret = 1;

							// idk what it makes
							if (!(target->s.target_flags & TARGET_FLAG_CAR_PLAYERCONTROLLED))
							{
								SetConfusedCar(slot);
							}
						}

						break;
					}
				}
			}
			else
			{
				target->s.car.slot = -1;

				if (gCarWithABerm == slot)
					gCarWithABerm = -1;

				if (target->s.car.type != 1)
				{
					message = MissionStrings + target->s.car.chasing.tooFarMessage;
					SetPlayerMessage(thread->player, message, 2, 2);
					SetMissionFailed(FAILED_MESSAGESET);
				}
			}
			
			break;
		}
		case Target_Event: // event target
		{
			if (target->s.target_flags & TARGET_FLAG_EVENT_TRIGGERED)
			{
				// [A] Ahhhh, 32 bit pointers... for future full-scale refactoring
				if (target->s.event.loseMessage != -1 && Long2DDistance(target->s.event.eventPos, &pv) > 30000)
				{
					message = MissionStrings + target->s.event.loseMessage;
					SetPlayerMessage(thread->player, message, 2, 2);
					SetMissionFailed(FAILED_MESSAGESET);
				}
			}
			else
			{
				target->s.event.eventPos = TriggerEvent(target->s.event.eventId);
				target->s.target_flags |= TARGET_FLAG_EVENT_TRIGGERED;
			}

			break;
		}
	}

	if (ret)
	{
		// keep only those flags
		target->s.target_flags &= ~TARGET_FLAG_COMPLETED_ALLP;
		
		if (thread->player == 0)
			target->s.target_flags |= TARGET_FLAG_COMPLETED_P1;
		else
			target->s.target_flags |= TARGET_FLAG_COMPLETED_P2;

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

// [D] [T]
int MRRequestCar(MS_TARGET *target)
{
	if (Mission.CarTarget || GameType == GAME_SURVIVAL)
		return 0;

	Mission.CarTarget = target;
	
	return 1;
}

// [D] [T]
void MRCancelCarRequest(MS_TARGET* target)
{
	if (Mission.CarTarget == target)
		Mission.CarTarget = NULL;
}

// [D] [T]
void MRHandleCarRequests(void)
{
	if (_CutRec_IsOn())
		return;
	
	if (Mission.CarTarget)
		MRCreateCar(Mission.CarTarget);
}

// [D] [T]
int MRCreateCar(MS_TARGET *target)
{
	int curslot;
	int newslot;
	LONGVECTOR4 pos;
	char playerid;

	pos[0] = target->s.car.posX;
	pos[2] = target->s.car.posZ;
	pos[1] = 10000;

	if (target->s.car.type == 2)
	{
		curslot = PingInCivCar(666);	// put Rio limo
		curslot--;
	}
	else
	{
		curslot = CreateStationaryCivCar(target->s.car.rotation, 0,
			((target->s.car.flags & CARTARGET_FLAG_FLIPPED) != 0) << 10, &pos,
			target->s.car.model, target->s.car.palette, (target->s.car.flags & CARTARGET_FLAG_ISCOP) != 0);
	}

	if (curslot < 0)
	{
		requestStationaryCivCar = 1;
		return 0;
	}

	if (target->s.car.flags & CARTARGET_FLAG_ISCOP)
	{
		newslot = NumReplayStreams + cop_adjust;
		cop_adjust++;

		curslot = Swap2Cars(curslot, newslot);
	}

	Mission.CarTarget = NULL;
	requestStationaryCivCar = 0;

	if (target->s.car.type == 3 && !(target->s.car.flags & CARTARGET_FLAG_RANDOMCHASE))
	{
		playerid = 0xFF;

		InitPlayer(&player[1], &car_data[curslot],
			CONTROL_TYPE_LEAD_AI, target->s.car.rotation, &pos,
			target->s.car.model, target->s.car.palette, (char *)&playerid);

		EnablePercentageBar(&DamageBar, target->s.car.chasing.maxDamage);
		NewLeadDelay = 0;
	}

	target->s.car.posX = car_data[curslot].hd.where.t[0];
	target->s.car.posZ = car_data[curslot].hd.where.t[2];

	target->s.car.slot = curslot;

	target->s.target_flags |= TARGET_FLAG_CAR_PINGED_IN;
	
	car_data[curslot].inform = &target->s.target_flags;

	// make fully damaged (Car bomb escape)
	if (target->s.car.flags & CARTARGET_FLAG_DAMAGED)
	{
		car_data[curslot].totalDamage = 65535;
		car_data[curslot].ap.damage[0] = 4095;
		car_data[curslot].ap.damage[1] = 4095;
		car_data[curslot].ap.damage[2] = 4095;
		car_data[curslot].ap.damage[3] = 4095;
		car_data[curslot].ap.damage[4] = 4095;
		car_data[curslot].ap.damage[5] = 4095;
		car_data[curslot].ap.needsDenting = 1;
	}

	if (target->s.car.flags & CARTARGET_FLAG_DETONATOR)
		gCarWithABerm = curslot;

	return 1;
}


// [D] [T]
void PreProcessTargets(void)
{
	MS_TARGET *target;
	int i;

	for (i = 0; i < MissionHeader->nCutscenes; i++)
	{
		PreLoadInGameCutscene(i);
	}

	for (i = 0; i < MAX_MISSION_TARGETS; i++)
	{
		target = &MissionTargets[i];

		if (target->type == Target_Player2Start || 
			target->type == Target_Car && (target->s.target_flags & TARGET_FLAG_CAR_PLAYERCONTROLLED))
		{
			PlayerStartInfo[1] = &ReplayStreams[1].SourceType;

			ReplayStreams[1].SourceType.type = 1;
			ReplayStreams[1].SourceType.position.vx = target->s.car.posX;
			ReplayStreams[1].SourceType.position.vy = 0;
			ReplayStreams[1].SourceType.position.vz = target->s.car.posZ;
			ReplayStreams[1].SourceType.rotation = target->s.car.rotation;
			ReplayStreams[1].SourceType.model = target->s.car.model;
			ReplayStreams[1].SourceType.palette = target->s.car.palette;
			ReplayStreams[1].SourceType.controlType = CONTROL_TYPE_PLAYER;
			ReplayStreams[1].SourceType.flags = 0;

			if (target->s.car.type & 0x3)
				target->s.car.cutscene = -1;
	
			target->s.car.slot = 1;
			target->s.target_flags |= TARGET_FLAG_CAR_PINGED_IN;
		}

		if (target->type == Target_Point)
		{
			if ((target->s.target_flags & TARGET_FLAG_POINT_CTF_FLAG) == TARGET_FLAG_POINT_CTF_FLAG)
			{
				target->s.target_flags |= TARGET_FLAG_COMPLETED_ALLP;
			}

			if (target->s.target_flags & TARGET_FLAG_POINT_ON_BOAT)
			{
				target->s.point.boatOffsetX = target->s.point.posX;
				target->s.point.boatOffsetZ = target->s.point.posZ;
			}
		}
		else if (target->type == Target_Car)
		{
			if ((target->s.target_flags & TARGET_FLAG_CAR_PLAYERCONTROLLED) == 0)
			{
				if (target->s.car.type == 3 && (target->s.car.flags & CARTARGET_FLAG_RANDOMCHASE))
				{
					PreLoadInGameCutscene(gRandomChase);
				}
			}
		}
	}
}

extern int gStopPadReads;

// [D] [T]
int Handle321Go(void)
{
	if (MissionHeader->type & 0x4) 
	{
		gStopPadReads = 1;
		
		if (++g321GoDelay == 96) 
		{
			gStopPadReads = 0;
			MissionHeader->type &= ~0x4;
		}

		return 1;
	}
	return 0;
}


extern int test42;	// why 42?

// [D] [T]
int HandleGameOver(void)
{
	int player_id;
	int playersdead;

	PLAYER* lp;
	CAR_DATA *cp;

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
					if(GameType == GAME_MISSION)
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
	playersdead = 0;

	while (player_id < NumPlayers)
	{
		lp = &player[player_id];

		if (lp->playerType == 1)
		{
			if ((Mission.timer[0].flags & TIMER_FLAG_BOMB_COUNTDOWN) || 
				TannerStuckInCar(0, player_id))
			{
				cp = &car_data[lp->playerCarId];
				
				if (MaxPlayerDamage[player_id] <= cp->totalDamage && lp->dying == 0)
				{
					lp->dying = 1;
				}

				if (cp->hd.where.m[1][1] < 100)
				{
					lp->upsideDown++;

					if (lp->upsideDown > 180)
					{
						cp->totalDamage = MaxPlayerDamage[player_id];

						if(lp->dying < 30)
							lp->dying = 30;
					}
				}
				else 
				{
					lp->upsideDown = 0;
				}
			}

			// reset timer
			tannerDeathTimer = 0;
		}
		else if (lp->playerType == 2)
		{
			int surf = GetSurfaceIndex((VECTOR*)lp->pos);

			if ((surf == -26 || surf == -23) && lp->dying == 0)
				tannerDeathTimer++;	// allow to soak Tanner's ass in Rio De Janeiro a little bit
			else
				tannerDeathTimer = 0;
		}

		// check player death
		if (tannerDeathTimer == 64)
			lp->dying = 1;

		if (lp->dying && !gGotInStolenCar)
		{
			if (Mission.timer[player_id].flags & TIMER_FLAG_BOMB_COUNTDOWN)
				BombThePlayerToHellAndBack(gCarWithABerm);

			if (lp->playerType == 2) 
				SetPlayerMessage(player_id, MissionStrings + MissionHeader->msgDrowned, 2, 2);
			else 
				SetPlayerMessage(player_id, MissionStrings + MissionHeader->msgCarWrecked, 2, 2);

			lp->dying++;
		}

		if (lp->dying > 40)
			playersdead++;

		player_id++;
	}

	if (playersdead)
	{
		// allow one of players to be dead in those modes
		if (GameType == GAME_CHECKPOINT ||
			GameType == GAME_TAKEADRIVE ||
			GameType == GAME_SECRET)
		{
			if (NumPlayers != 1)
			{
				if (playersdead == NumPlayers)
					SetMissionOver(PAUSEMODE_GAMEOVER);
				
				return 0;
			}
		}

		if (TannerStuckInCar(0, 0))
			SetMissionOver(PAUSEMODE_GAMEOVER);
	}

	return 0;
}

// [D] [T]
void CompleteAllActiveTargets(int player)
{
	MS_TARGET *pTarget;
	int i;
	int flag2;
	int flag1;

	if (player == 0) 
	{
		flag1 = TARGET_FLAG_ACTIVE_P1;
		flag2 = TARGET_FLAG_COMPLETED_P1;
	}
	else
	{
		flag1 = TARGET_FLAG_ACTIVE_P2;
		flag2 = TARGET_FLAG_COMPLETED_P2;
	}

	for (i = 0; i < MAX_MISSION_TARGETS; i++)
	{
		pTarget = &MissionTargets[i];

		if (pTarget->type >= Target_Point && 
			pTarget->type <= Target_Event && (pTarget->s.target_flags & flag1))
		{
			pTarget->s.target_flags |= flag2;
		}
	}
}

// [D] [T]
void SetMissionComplete(void)
{
	switch (GameType) 
	{
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
					SetPlayerMessage(0, G_LTXT(GTXT_Draw), 3, 2);
					SetPlayerMessage(1, G_LTXT(GTXT_Draw), 3, 2);
					break;
				}

				SetPlayerMessage(0, MissionStrings + MissionHeader->msgComplete, 3, 2);
				break;
			}

			SetPlayerMessage(0, MissionStrings + MissionHeader->msgDrowned, 3, 2);
			SetPlayerMessage(1, MissionStrings + MissionHeader->msgComplete, 3, 2);
			break;
		case GAME_COPSANDROBBERS:
			if (Player2DamageBar.position < Player2DamageBar.max)
			{
				SetPlayerMessage(0, MissionStrings + MissionHeader->msgDrowned, 3, 2);
				SetPlayerMessage(1, MissionStrings + MissionHeader->msgComplete, 3, 2);
			}
			else 
			{
				SetPlayerMessage(0, MissionStrings + MissionHeader->msgComplete, 3, 2);
				SetPlayerMessage(1, MissionStrings + MissionHeader->msgDrowned, 3, 2);
			}
			break;
		case GAME_MISSION:
			if (Mission.timer[0].flags & TIMER_FLAG_BOMB_COUNTDOWN)
			{
				Mission.timer[0].flags |= TIMER_FLAG_BOMB_TRIGGERED;
				
				DetonatorTimer();
				return;
			}

			if (gFurthestMission < gCurrentMissionNumber)
				gFurthestMission = gCurrentMissionNumber;

		default:
			SetMissionMessage(MissionStrings + MissionHeader->msgComplete, 3, 2);
			break;
	}

	SetMissionOver(PAUSEMODE_COMPLETE);
}


// [D] [T]
void SetMissionFailed(FAIL_REASON reason)
{
	if (reason == FAILED_CnR_LOSTHIM) 
	{
		SetPlayerMessage(0,MissionStrings + MissionHeader->msgDrowned,3,2);
		SetPlayerMessage(1,MissionStrings + MissionHeader->msgComplete,3,2);
	}
	else if(reason == FAILED_OUTOFTIME) 
	{
		SetMissionMessage(MissionStrings + MissionHeader->msgOutOfTime,3,2);
	}

	SetMissionOver(PAUSEMODE_GAMEOVER);
}


// [D] [T]
void SetMissionOver(PAUSEMODE mode)
{
	ReleaseInGameCutscene();
	PauseMissionTimer(1);

	gBombTargetVehicle = NULL;

	Mission.gameover_delay = 60;
	Mission.gameover_mode = mode;
	Mission.ChaseTarget = NULL;
}

// [D] [T]
void ActivateNextFlag(void)
{
	int j;
	MS_TARGET *target;
	int i;

	if (last_flag == -1)
		last_flag = 0;
	else
		MissionTargets[last_flag].s.target_flags |= TARGET_FLAG_COMPLETED_ALLP;

	j = last_flag;
	
	for (i = 0; i < MAX_MISSION_TARGETS; i++)
	{
		j++;

		j = j % MAX_MISSION_TARGETS;

		target = &MissionTargets[j];

		if (target->type == Target_Point && (target->s.target_flags & TARGET_FLAG_POINT_CTF_FLAG) == TARGET_FLAG_POINT_CTF_FLAG)
			break;
	}

	target->s.target_flags &= ~TARGET_FLAG_COMPLETED_ALLP;
	last_flag = j;
}

// [D] [T]
int CalcLapTime(int player, int time, int lap)
{
	int i;
	int ptime;

	ptime = 0;

	i = 0;
	while (i < lap)
	{
		ptime += gLapTimes[player][i];
		i++;
	}

	return time - ptime;
}

// [D] [T]
void MakePhantomCarEqualPlayerCar(void)
{
	// store player car id
	if (player[0].playerType == 1)
		Mission.PhantomCarId = player[0].playerCarId;
}

// [D] [T]
void SetCarToBeStolen(MS_TARGET *target, int player)
{
	if (target->s.car.flags & CARTARGET_FLAG_SET_PLAYERCAR)
	{
		MakePhantomCarEqualPlayerCar();
		target->s.target_flags |= TARGET_FLAG_CAR_SAVED;
	}

	target->s.car.type = 1;
	target->s.car.flags = CARTARGET_FLAG_STEAL_TARGET;
	target->s.car.maxDistance = 0;

	SetPlayerMessage(player, Mission.StealMessage, 2, 2);
}

// [D] [T]
void HandleMission(void)
{
	if (!Mission.active)
		return;

	if (gInGameCutsceneActive)
		return;

	if (gInGameCutsceneDelay)
		return;

	// init frame
	if (CameraCnt == 0)
	{
		// mission has countdown
		if (MissionHeader->type & 4)
		{
			HandleMissionThreads();

			Mission.message_timer[0] = 0;
			Mission.message_timer[1] = 0;

			MRCommitThreadGenocide();
			MRInitialiseThread(&MissionThreads[0], MissionScript, 0);
		}

		switch (MissionHeader->type & 0x30)
		{
		case 0x20:
			FelonyBar.flags |= 0x2;
		case 0:
			FelonyBar.active = 0x1;
			break;
		case 0x10:
			FelonyBar.active = 0;
		default:
			FelonyBar.active = 0;
		}
	}

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

	if (gCopCarTheftAttempted)
	{
		SetMissionMessage(MissionStrings + MissionHeader->msgPoliceCar, 2, 1);
		gCopCarTheftAttempted = 0;
	}

	if (gLockPickingAttempted && NumPlayers == 1)
	{
		SetMissionMessage(MissionStrings + MissionHeader->msgDoorsLocked, 2, 1);
		gLockPickingAttempted = 0;
	}
}