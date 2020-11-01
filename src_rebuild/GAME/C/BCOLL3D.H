#ifndef BCOLL3D_H
#define BCOLL3D_H


extern void PointFaceCheck(CAR_DATA *cp0, CAR_DATA *cp1, int i, TestResult *least, int nSign); // 0x0001C160

extern int collided3d(CAR_DATA *cp0, CAR_DATA *cp1, TestResult *least); // 0x0001C408

extern int CarCarCollision3(CAR_DATA *c0, CAR_DATA *c1, int *depth, VECTOR *where, VECTOR *normal); // 0x0001C380


#endif
