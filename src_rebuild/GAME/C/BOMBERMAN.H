#ifndef BOMBERMAN_H
#define BOMBERMAN_H

extern MODEL* gBombModel;
extern CAR_DATA *gBombTargetVehicle;

extern void InitThrownBombs(); // 0x0001F570
extern void HandleThrownBombs(); // 0x0001E3E8
extern void DrawThrownBombs(); // 0x0001E810

extern void BombThePlayerToHellAndBack(int car); // 0x0001EA00
extern void ExplosionCollisionCheck(CAR_DATA *cp, EXOBJECT *pE); // 0x0001ED18

#endif
