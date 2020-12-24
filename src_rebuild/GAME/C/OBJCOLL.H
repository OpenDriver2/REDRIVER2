#ifndef OBJCOLL_H
#define OBJCOLL_H

extern char CellEmpty(VECTOR *pPosition, int radius); // 0x00069BA4
extern char CellAtPositionEmpty(VECTOR *pPosition, int radius); // 0x0006B3E4

extern char lineClear(VECTOR *v1, VECTOR *v2); // 0x00069FB4
extern void CheckScenaryCollisions(CAR_DATA *cp); // 0x0006A64C
extern int QuickBuildingCollisionCheck(VECTOR *pPos, int dir, int l, int w, int extra); // 0x0006ADBC

extern void DoScenaryCollisions(); // 0x0006B220

#endif
