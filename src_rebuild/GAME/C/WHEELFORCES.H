#ifndef WHEELFORCES_H
#define WHEELFORCES_H


extern void StepCars(); // 0x00082BD0

extern void StepOneCar(struct _CAR_DATA *cp); // 0x00081178

extern void GetFrictionScalesDriver1(struct _CAR_DATA *cp, struct CAR_LOCALS *cl, int *frontFS, int *rearFS); // 0x0008198C

extern void ConvertTorqueToAngularAcceleration(struct _CAR_DATA *cp, struct CAR_LOCALS *cl); // 0x00081E20

extern void AddWheelForcesDriver1(struct _CAR_DATA *cp, struct CAR_LOCALS *cl); // 0x00081F50


#endif
