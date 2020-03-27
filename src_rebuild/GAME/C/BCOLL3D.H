#ifndef BCOLL3D_H
#define BCOLL3D_H


extern void PointFaceCheck(struct _CAR_DATA *cp0, struct _CAR_DATA *cp1, int i, struct TestResult *least, int nSign); // 0x0001C160

extern int collided3d(struct _CAR_DATA *cp0, struct _CAR_DATA *cp1, struct TestResult *least); // 0x0001C408

extern int CarCarCollision3(struct _CAR_DATA *c0, struct _CAR_DATA *c1, int *depth, struct VECTOR *where, struct VECTOR *normal); // 0x0001C380


#endif
