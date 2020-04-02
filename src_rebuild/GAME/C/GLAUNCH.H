#ifndef GLAUNCH_H
#define GLAUNCH_H

extern ACTIVE_CHEATS AvailableCheats;
extern ACTIVE_CHEATS ActiveCheats;

extern int gFurthestMission;
extern int GameLevel;

extern int wantedCar[2];
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
extern int gCurrentMissionNumber;
extern int gInFrontend;
extern int AttractMode;
extern char NoPlayerControl;

extern int gCopDifficultyLevel;

extern void GameStart(); // 0x00052A28

extern void StartRender(int renderNum); // 0x000536B0

extern void ReInitFrontend(); // 0x00052E98

extern void RunMissionLadder(int newgame); // 0x00052FE8

extern void GetRandomChase(); // 0x000535D8

extern int FindPrevMissionFromLadderPos(int pos); // 0x000536D8

extern void LaunchGame(); // 0x000532B8

extern int FindMissionLadderPos(int mission); // 0x00053740


#endif
