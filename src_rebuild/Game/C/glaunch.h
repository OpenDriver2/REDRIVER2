#ifndef GLAUNCH_H
#define GLAUNCH_H

extern ACTIVE_CHEATS AvailableCheats;
extern ACTIVE_CHEATS ActiveCheats;

extern int gLastChase;
extern int gChaseNumber;
extern int gRandomChase;
extern int gSubGameNumber;

extern int gLoadedReplay;
extern int gHaveStoredData;

// [A]
extern int gHaveExtraData;
extern EXTRA_CONFIG_DATA gExtraConfig;

extern int gMissionLadderPos;
extern int gFurthestMission;
extern int gWantNight;

extern int lead_car;
extern GAMEMODE WantedGameMode;

extern int lead_car;
extern int wantedCar[2];
extern int gInFrontend;
extern int AttractMode;
extern char NoPlayerControl;

extern int quick_replay;
extern int AutoDirect;

extern int quick_replay;

extern MISSION_DATA MissionStartData;
extern MISSION_DATA MissionEndData;

extern void State_InitFrontEnd(void* param);
extern void State_GameStart(void* param); // 0x00052A28
extern void State_GameComplete(void* param);
extern void State_MissionLadder(void* param);
extern void State_LaunchGame(void* param); // 0x000532B8

extern void State_FMVPlay(void* param); // 0x000536B0

extern void ReInitFrontend(int returnToMain); // 0x00052E98

extern void RunMissionLadder(int newgame); // 0x00052FE8

extern void StoreGameVars(int replay);
extern void RestoreGameVars(int replay);

extern void LoadExtraData(EXTRA_CONFIG_DATA *extraData, int profile);
extern void SaveExtraData(EXTRA_CONFIG_DATA *extraData, int profile);

extern void GetRandomChase(); // 0x000535D8

extern int FindPrevMissionFromLadderPos(int pos); // 0x000536D8

extern int FindMissionLadderPos(int mission); // 0x00053740


#endif
