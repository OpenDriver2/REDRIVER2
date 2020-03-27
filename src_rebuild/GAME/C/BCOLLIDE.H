#ifndef BCOLLIDE_H
#define BCOLLIDE_H


extern int bcollided2d(struct CDATA2D *body, int needOverlap); // 0x0001C51C

extern void bFindCollisionPoint(struct CDATA2D *body, struct CRET2D *collisionResult); // 0x0001C8C0

extern int bFindCollisionTime(struct CDATA2D *cd, struct CRET2D *collisionResult); // 0x0001CC30

extern void ApplyDamage(struct _CAR_DATA *cp, char region, int value, char fakeDamage); // 0x0001CEEC

extern int DamageCar3D(struct _CAR_DATA *cp, long (*delta)[4], int strikeVel, struct _CAR_DATA *pOtherCar); // 0x0001D0B0

extern void DamageCar(struct _CAR_DATA *cp, struct CDATA2D *cd, struct CRET2D *collisionResult, int strikeVel); // 0x0001D454

extern int CarBuildingCollision(struct _CAR_DATA *cp, struct BUILDING_BOX *building, struct CELL_OBJECT *cop, int mightBeABarrier); // 0x0001D68C


#endif
