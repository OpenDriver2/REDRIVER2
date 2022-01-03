#ifndef PLAYERS_H
#define PLAYERS_H

#define MAX_PLAYERS 8

extern PLAYER player[MAX_PLAYERS];

extern void InitPlayer(PLAYER *locPlayer, CAR_DATA *cp, char carCtrlType, int direction, LONGVECTOR4* startPos, int externModel, int palette, char *padid); // 0x000739D8

extern void ChangeCarPlayerToPed(int playerID); // 0x00073334
extern void ChangePedPlayerToCar(int playerID, CAR_DATA *newCar); // 0x0007350C

extern void UpdatePlayers(); // 0x00073898

extern void RequestSlightPauseBeforeCarSoundStarts(char player_id); // 0x00073C0C
extern void HaveCarSoundStraightAway(char player_id); // 0x00073C54

extern void MakeTheCarShutUp(char player_id); // 0x00073C8C


#endif
