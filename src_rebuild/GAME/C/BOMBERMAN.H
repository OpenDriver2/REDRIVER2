#ifndef BOMBERMAN_H
#define BOMBERMAN_H

extern MODEL* gBombModel;

extern void InitThrownBombs(); // 0x0001F570

extern void HandleThrownBombs(); // 0x0001E3E8

extern void DrawThrownBombs(); // 0x0001E810

extern void BombThePlayerToHellAndBack(int car); // 0x0001EA00

extern int BombCollisionCheck(_CAR_DATA *cp, VECTOR *pPos); // 0x0001EC58

extern void ExplosionCollisionCheck(_CAR_DATA *cp, _ExOBJECT *pE); // 0x0001ED18

extern void AddFlash(VECTOR *pos); // 0x0001F4F4


#endif
