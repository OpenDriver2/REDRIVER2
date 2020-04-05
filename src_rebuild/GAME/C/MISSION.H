#ifndef MISSION_H
#define MISSION_H

extern char* MissionName[37];

extern int GameLevel;
extern int gFurthestMission;
extern int gWantNight;
extern int gSubGameNumber;
extern int gInvincibleCar;
extern int gPlayerImmune;
extern unsigned char NumPlayers;
extern char NewLevel;
extern GAMETYPE GameType;
extern GAMETYPE StoredGameType;
extern GAMEMODE CurrentGameMode;
extern int gCurrentMissionNumber;
extern _MISSION *MissionHeader;
extern _PLAYER player[8];
extern STREAM_SOURCE* PlayerStartInfo[8];
extern int numPlayersToCreate;
extern int gStartOnFoot;
extern int gSinkingTimer;
extern int gTimeInWater;
extern char InWater;
extern int gBobIndex;
extern int gWeather;
extern int gTimeOfDay;
extern int gShowPlayerDamage;
extern int gDontPingInCops;
extern int gBatterPlayer;

extern int wantedCar[2];

extern COP_DATA gCopData;

extern _TARGET *MissionTargets;
extern unsigned long *MissionScript;
extern char *MissionStrings;

extern int gMultiplayerLevels;

extern void InitialiseMissionDefaults(); // 0x0006084C

extern void LoadMission(int missionnum); // 0x00060A74

extern void HandleMission(); // 0x00061274

extern void HandleTimer(struct MR_TIMER *timer); // 0x000614A4

extern void RegisterChaseHit(int car1, int car2); // 0x00061684

extern void PauseMissionTimer(int pause); // 0x00064268

extern void SetMissionMessage(char *message, int priority, int seconds); // 0x000642A8

extern void SetPlayerMessage(int player, char *message, int priority, int seconds); // 0x00064348

extern int TargetComplete(struct _TARGET *target, int player); // 0x000643C4

extern int TargetActive(struct _TARGET *target, int player); // 0x00064408

extern int Swap2Cars(int curslot, int newslot); // 0x00061784

extern void SetConfusedCar(int slot); // 0x0006444C

extern void HandleMissionThreads(); // 0x00061C5C

extern int MRCommand(struct MR_THREAD *thread, unsigned long cmd); // 0x00061E3C

extern int MROperator(struct MR_THREAD *thread, unsigned long op); // 0x00064498

extern int MRFunction(struct MR_THREAD *thread, unsigned long fnc); // 0x000645AC

extern void MRInitialiseThread(struct MR_THREAD *thread, unsigned long *pc, unsigned char player); // 0x00064614

extern void MRStartThread(struct MR_THREAD *callingthread, unsigned long addr, unsigned char player); // 0x00064630

extern int MRStopThread(struct MR_THREAD *thread); // 0x00064690

extern void MRCommitThreadGenocide(); // 0x0006469C

extern int MRJump(struct MR_THREAD *thread, long jump); // 0x000646E0

extern void MRPush(struct MR_THREAD *thread, long value); // 0x0006472C

extern long MRPop(struct MR_THREAD *thread); // 0x00064744

extern long MRGetParam(struct MR_THREAD *thread); // 0x00064760

extern long MRGetVariable(struct MR_THREAD *thread, unsigned long var); // 0x000647CC

extern void MRSetVariable(struct MR_THREAD *thread, unsigned long var, long value); // 0x000648B0

extern int MRProcessTarget(struct MR_THREAD *thread, struct _TARGET *target); // 0x00062470

extern int MRRequestCar(struct _TARGET *target); // 0x000649E4

extern void MRHandleCarRequests(); // 0x00064A24

extern int MRCreateCar(struct _TARGET *target); // 0x00063728

extern void MRCancelCarRequest(struct _TARGET *target); // 0x00064A50

extern void PreProcessTargets(); // 0x000639A0

extern int Handle321Go(); // 0x00064A74

extern int HandleGameOver(); // 0x00063B78

extern void CompleteAllActiveTargets(int player); // 0x00064AD0

extern void SetMissionComplete(); // 0x00063F84

extern void SetMissionFailed(enum FAIL_REASON reason); // 0x00064B38

extern void SetMissionOver(enum PAUSEMODE mode); // 0x00064BD8

extern void ActivateNextFlag(); // 0x000641A8

extern int CalcLapTime(int player, int time, int lap); // 0x00064C24

extern void SetCarToBeStolen(struct _TARGET *target, int player); // 0x00064C60

extern void MakePhantomCarEqualPlayerCar(); // 0x00064CD0


#endif
