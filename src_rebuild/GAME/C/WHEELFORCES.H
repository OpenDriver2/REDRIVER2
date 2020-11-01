#ifndef WHEELFORCES_H
#define WHEELFORCES_H

extern _HANDLING_TYPE handlingType[7];

extern void StepCars(); // 0x00082BD0

extern void StepOneCar(CAR_DATA *cp); // 0x00081178

extern void GetFrictionScalesDriver1(CAR_DATA *cp, CAR_LOCALS *cl, int *frontFS, int *rearFS); // 0x0008198C

extern void ConvertTorqueToAngularAcceleration(CAR_DATA *cp, CAR_LOCALS *cl); // 0x00081E20

extern void AddWheelForcesDriver1(CAR_DATA *cp, CAR_LOCALS *cl); // 0x00081F50


#endif
