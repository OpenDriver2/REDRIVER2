#ifndef BCOLLIDE_H
#define BCOLLIDE_H

extern int boxOverlap;

extern int bcollided2d(CDATA2D *body, int needOverlap); // 0x0001C51C

extern void bFindCollisionPoint(CDATA2D *body, CRET2D *collisionResult); // 0x0001C8C0

extern int bFindCollisionTime(CDATA2D *cd, CRET2D *collisionResult); // 0x0001CC30

extern void ApplyDamage(CAR_DATA *cp, char region, int value, char fakeDamage); // 0x0001CEEC

extern int DamageCar3D(CAR_DATA *cp, LONGVECTOR* delta, int strikeVel, CAR_DATA *pOtherCar); // 0x0001D0B0

extern void DamageCar(CAR_DATA *cp, CDATA2D *cd, CRET2D *collisionResult, int strikeVel); // 0x0001D454

extern int CarBuildingCollision(CAR_DATA *cp, BUILDING_BOX *building, CELL_OBJECT *cop, int flags); // 0x0001D68C


#endif
