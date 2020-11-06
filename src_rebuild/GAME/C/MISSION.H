#ifndef MISSION_H
#define MISSION_H

extern char* MissionName[37];

extern int GameLevel;
extern int gInvincibleCar;
extern int gPlayerImmune;
extern unsigned char NumPlayers;
extern char NewLevel;
extern GAMETYPE GameType;
extern GAMETYPE StoredGameType;
extern GAMEMODE CurrentGameMode;
extern GAMEMODE WantedGameMode;
extern int gCurrentMissionNumber;
extern _MISSION *MissionHeader;
extern STREAM_SOURCE* PlayerStartInfo[8];
extern int numPlayersToCreate;
extern int gStartOnFoot;
//extern int gSinkingTimer;
//extern int gTimeInWater;
extern char InWater;
extern int gBobIndex;
extern int gWeather;
extern int gTimeOfDay;
extern int gShowPlayerDamage;
extern int gDontPingInCops;
extern int gBatterPlayer;
extern int bMissionTitleFade;
extern int g321GoDelay;
extern int gTannerActionNeeded;
extern int gGotInStolenCar;
extern int gCopCarTheftAttempted;
extern int gLockPickingAttempted;
extern char lockAllTheDoors;
extern int bStopTanner;
extern int tannerDeathTimer;
extern int gCantDrive;
extern int gPlayerDamageFactor;
extern int gCarWithABerm;

extern int gPlayerWithTheFlag;

extern int requestStationaryCivCar;
extern int numCivCars;
extern int maxCivCars;
extern int numParkedCars;
extern int maxParkedCars;

extern int gCopDifficultyLevel;
extern int gCopRespawnTime;

extern int maxCopCars;

extern int gMinimumCops;
extern int gCopDesiredSpeedScale;
extern int gCopMaxPowerScale;
extern int gCurrentResidentSlot;
extern int gPuppyDogCop;
extern int CopsAllowed;
extern STOPCOPS gStopCops;

extern MR_MISSION Mission;

extern int wantedCar[2];
extern int wantedTimeOfDay;
extern int wantedWeather;

extern int multiplayerregions[4];
extern int MaxPlayerDamage[2];

extern COP_DATA gCopData;

extern MS_TARGET *MissionTargets;
extern unsigned long *MissionScript;
extern char *MissionStrings;

extern char *gMissionTitle;

extern int gMultiplayerLevels;

extern const int TAIL_GETTINGCLOSE;
extern const int TAIL_GETTINGFAR;
extern const int TAIL_TOOCLOSE;
extern const int TAIL_TOOFAR;

extern int numCopCars;

extern int gDontResetCarDamage;

extern int gLapTimes[2][5];
extern int gNumRaceTrackLaps;

extern void InitialiseMissionDefaults(); // 0x0006084C

extern void LoadMission(int missionnum); // 0x00060A74

extern void HandleMission(); // 0x00061274

extern void HandleTimer(MR_TIMER *timer); // 0x000614A4

extern void RegisterChaseHit(int car1, int car2); // 0x00061684

extern void PauseMissionTimer(int pause); // 0x00064268

extern void SetMissionMessage(char *message, int priority, int seconds); // 0x000642A8

extern void SetPlayerMessage(int player, char *message, int priority, int seconds); // 0x00064348

extern int TargetComplete(MS_TARGET *target, int player); // 0x000643C4

extern int TargetActive(MS_TARGET *target, int player); // 0x00064408

extern int Swap2Cars(int curslot, int newslot); // 0x00061784

extern void SetConfusedCar(int slot); // 0x0006444C

extern void HandleMissionThreads(); // 0x00061C5C

extern int MRCommand(MR_THREAD *thread, unsigned long cmd); // 0x00061E3C

extern int MROperator(MR_THREAD *thread, unsigned long op); // 0x00064498

extern int MRFunction(MR_THREAD *thread, unsigned long fnc); // 0x000645AC

extern void MRInitialiseThread(MR_THREAD *thread, unsigned long *pc, unsigned char player); // 0x00064614

extern void MRStartThread(MR_THREAD *callingthread, unsigned long addr, unsigned char player); // 0x00064630

extern int MRStopThread(MR_THREAD *thread); // 0x00064690

extern void MRCommitThreadGenocide(); // 0x0006469C

extern int MRJump(MR_THREAD *thread, long jump); // 0x000646E0

extern void MRPush(MR_THREAD *thread, long value); // 0x0006472C

extern long MRPop(MR_THREAD *thread); // 0x00064744

extern long MRGetParam(MR_THREAD *thread); // 0x00064760

extern long MRGetVariable(MR_THREAD *thread, unsigned long var); // 0x000647CC

extern void MRSetVariable(MR_THREAD *thread, unsigned long var, long value); // 0x000648B0

extern int MRProcessTarget(MR_THREAD *thread, MS_TARGET *target); // 0x00062470

extern int MRRequestCar(MS_TARGET *target); // 0x000649E4

extern void MRHandleCarRequests(); // 0x00064A24

extern int MRCreateCar(MS_TARGET *target); // 0x00063728

extern void MRCancelCarRequest(MS_TARGET *target); // 0x00064A50

extern void PreProcessTargets(); // 0x000639A0

extern int Handle321Go(); // 0x00064A74

extern int HandleGameOver(); // 0x00063B78

extern void CompleteAllActiveTargets(int player); // 0x00064AD0

extern void SetMissionComplete(); // 0x00063F84

extern void SetMissionFailed(FAIL_REASON reason); // 0x00064B38

extern void SetMissionOver(PAUSEMODE mode); // 0x00064BD8

extern void ActivateNextFlag(); // 0x000641A8

extern int CalcLapTime(int player, int time, int lap); // 0x00064C24

extern void SetCarToBeStolen(MS_TARGET *target, int player); // 0x00064C60

extern void MakePhantomCarEqualPlayerCar(); // 0x00064CD0

extern void DrawMission(void);

#endif
