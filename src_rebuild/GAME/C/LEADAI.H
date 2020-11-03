#ifndef LEADAI_H
#define LEADAI_H


extern int leadRand(); // 0x000E70A0

extern void InitLead(CAR_DATA *cp); // 0x000E7128

extern void LeadUpdateState(CAR_DATA *cp); // 0x000E73E8

extern unsigned long LeadPadResponse(CAR_DATA *cp); // 0x000E7994

extern void FakeMotion(CAR_DATA *cp); // 0x000E7DE8

extern void PosToIndex(int *normal, int *tangent, int intention, CAR_DATA *cp); // 0x000E834C

extern void BlockToMap(MAP_DATA *data); // 0x000E86BC

extern int IsOnMap(int x, int z, VECTOR *basePos, int intention, CAR_DATA *cp); // 0x000E98A4

extern void UpdateRoadPosition(CAR_DATA *cp, VECTOR *basePos, int intention); // 0x000E9BB8

extern void slowWallTests() ; // 0x000E913C

extern void asf() ; // 0x000E9158

extern void DoExtraWorkForNFrames() ; // 0x000E99AC

extern void searchTarget() ; // 0x000E9AB8

extern void CheckCurrentRoad(CAR_DATA *cp); // 0x000EB1FC

extern void SetTarget(CAR_DATA *cp, int cr, int heading, int *nextJunction); // 0x000EC1C4

extern void SelectExit(CAR_DATA *cp, DRIVER2_JUNCTION *junction); // 0x000EC5E4

extern unsigned long FreeRoamer(CAR_DATA *cp); // 0x000EC99C

extern unsigned long hypot(long x, long y); // 0x000ECB28


#endif
