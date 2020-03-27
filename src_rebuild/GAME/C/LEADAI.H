#ifndef LEADAI_H
#define LEADAI_H


extern int leadRand(); // 0x000E70A0

extern void InitLead(struct _CAR_DATA *cp); // 0x000E7128

extern void LeadUpdateState(struct _CAR_DATA *cp); // 0x000E73E8

extern unsigned long LeadPadResponse(struct _CAR_DATA *cp); // 0x000E7994

extern void FakeMotion(struct _CAR_DATA *cp); // 0x000E7DE8

extern void PosToIndex(int *normal, int *tangent, int intention, struct _CAR_DATA *cp); // 0x000E834C

extern void BlockToMap(struct MAP_DATA *data); // 0x000E86BC

extern int IsOnMap(int x, int z, struct VECTOR *basePos, int intention, struct _CAR_DATA *cp); // 0x000E98A4

extern void UpdateRoadPosition(struct _CAR_DATA *cp, struct VECTOR *basePos, int intention); // 0x000E9BB8

extern void slowWallTests() ; // 0x000E913C

extern void asf() ; // 0x000E9158

extern void DoExtraWorkForNFrames() ; // 0x000E99AC

extern void searchTarget() ; // 0x000E9AB8

extern void CheckCurrentRoad(struct _CAR_DATA *cp); // 0x000EB1FC

extern void SetTarget(struct _CAR_DATA *cp, int cr, int heading, int *nextJunction); // 0x000EC1C4

extern void SelectExit(struct _CAR_DATA *cp, struct DRIVER2_JUNCTION *junction); // 0x000EC5E4

extern unsigned long FreeRoamer(struct _CAR_DATA *cp); // 0x000EC99C

extern unsigned long hypot(long x, long y); // 0x000ECB28


#endif
