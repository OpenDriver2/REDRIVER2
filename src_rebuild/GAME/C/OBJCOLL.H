#ifndef OBJCOLL_H
#define OBJCOLL_H


extern char CellEmpty(struct VECTOR *pPosition, int radius); // 0x00069BA4

extern int GlobalPositionToCellNumber(struct VECTOR *pPosition); // 0x0006B2EC

extern char CellAtPositionEmpty(struct VECTOR *pPosition, int radius); // 0x0006B3E4

extern int RaySlabsIntersection(struct tRay *ray, struct tAABB *bbox); // 0x00069E1C

extern char lineClear(struct VECTOR *v1, struct VECTOR *v2); // 0x00069FB4

extern void SetCopListCell(int x, int z); // 0x0006B430

extern void BuildCollisionCopList(int *count); // 0x0006B45C

extern void CollisionCopList(struct XZPAIR *pos, int *count); // 0x0006A498

extern void CheckScenaryCollisions(struct _CAR_DATA *cp); // 0x0006A64C

extern int QuickBuildingCollisionCheck(struct VECTOR *pPos, int dir, int l, int w, int extra); // 0x0006ADBC

extern void DoScenaryCollisions(); // 0x0006B220


#endif
