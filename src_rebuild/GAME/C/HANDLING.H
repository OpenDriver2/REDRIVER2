#ifndef HANDLING_H
#define HANDLING_H


extern void InitCarPhysics(_CAR_DATA *cp, long (*startpos)[4], int direction); // 0x0005381C

extern void TempBuildHandlingMatrix(_CAR_DATA *cp, int init); // 0x000539E8

extern void UpdateCarPoints(CAR_COSMETICS *carCos); // 0x00053B08

extern void FixCarCos(CAR_COSMETICS *carCos, int externalModelNumber); // 0x00056C24

extern void GlobalTimeStep(); // 0x00053C00

extern void SetShadowPoints(_CAR_DATA *c0); // 0x000551EC

extern void LongQuaternion2Matrix(long (*qua)[4], MATRIX *m); // 0x000553CC

extern void initOBox(_CAR_DATA *cp); // 0x000554F0

extern void RebuildCarMatrix(union RigidBodyState *st, _CAR_DATA *cp); // 0x00056AE4

extern void StepCarPhysics(_CAR_DATA *cp); // 0x00056A0C

extern void InitialiseCarHandling(); // 0x00056A6C

extern void CheckCarToCarCollisions(); // 0x000556E0

extern void ProcessCarPad(_CAR_DATA *cp, unsigned long pad, char PadSteer, char use_analogue); // 0x00055A9C

extern void InitSkidding(); // 0x00056CB8

extern void TerminateSkidding(int player_id); // 0x000562AC

extern void CheckCarEffects(_CAR_DATA *cp, int player_id); // 0x00056350

extern void jump_debris(_CAR_DATA *cp); // 0x000568D8

extern void nose_down(_CAR_DATA *cp); // 0x00056A74

extern int GetPlayerId(_CAR_DATA *cp); // 0x00056CEC


#endif
