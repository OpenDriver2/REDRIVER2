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
extern MS_MISSION*MissionHeader;
extern STREAM_SOURCE* PlayerStartInfo[8];
extern int numPlayersToCreate;
extern int gStartOnFoot;

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
extern int wantedColour[2];
extern int wantedTimeOfDay;
extern int wantedWeather;
extern int wantedStartPos;

extern int multiplayerregions[4];
extern int MaxPlayerDamage[2];

extern COP_DATA gCopData;

extern MS_TARGET *MissionTargets;
extern u_int*MissionScript;
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

extern void RegisterChaseHit(int car1, int car2); // 0x00061684

extern void SetMissionComplete(void);
extern void SetMissionFailed(FAIL_REASON reason);
extern void SetMissionMessage(char *message, int priority, int seconds); // 0x000642A8
extern void SetPlayerMessage(int player, char *message, int priority, int seconds); // 0x00064348

extern int TargetComplete(MS_TARGET *target, int player); // 0x000643C4
extern int TargetActive(MS_TARGET *target, int player); // 0x00064408

extern int Swap2Cars(int curslot, int newslot); // 0x00061784

extern void SetConfusedCar(int slot); // 0x0006444C

extern void DrawMission(void);

#endif
