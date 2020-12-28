#ifndef COP_AI_H
#define COP_AI_H

extern COP_DATA gCopData;
extern COP_SIGHT_DATA copSightData;
extern VECTOR roadblockLoc;

extern int CopsCanSeePlayer;
extern short pedestrianFelony;

extern int numRoadblockCars;
extern int roadblockCount;
extern int copsAreInPursuit;
extern int requestRoadblock;
extern int roadblockDelay;
extern int roadblockDelayDiff[3];
extern int  requestCopCar;
extern int cop_respawn_timer;

extern int pathStraight;
extern VECTOR lastKnownPosition;

extern char last_cop_phrase;

extern char first_offence;

extern int player_position_known;
extern int numActiveCops;

extern void InitCopState(CAR_DATA *cp, char *extraData); // 0x0002F680
extern void InitCops(); // 0x0002D99C

extern void ControlCops(); // 0x0002DAD8
extern void CopControl(CAR_DATA *cp); // 0x0002F60C

extern void PassiveCopTasks(CAR_DATA *cp); // 0x0002F6FC

extern int ReplayLog_Fnarr_He_Said_Log(int val);

#endif
