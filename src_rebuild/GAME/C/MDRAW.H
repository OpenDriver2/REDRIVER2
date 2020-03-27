#ifndef MDRAW_H
#define MDRAW_H


extern void DrawMission(); // 0x0005F2FC

extern void DrawTimer(struct MR_TIMER *timer); // 0x0005FA88

extern void DisplayPlayerPosition(); // 0x0005FB7C

extern void DrawMessage(int y, char *string); // 0x0005FBC4

extern void DrawWorldTargets(); // 0x0005FC3C

extern void DrawOverheadTargets(); // 0x0005FC8C

extern void DrawFullscreenTargets(); // 0x0005FCDC

extern void DrawMultiplayerTargets(); // 0x0005FD2C

extern void DrawOverheadTarget(struct _TARGET *target); // 0x0005FD7C

extern void DrawFullscreenTarget(struct _TARGET *target); // 0x0005FE94

extern void DrawWorldTarget(struct _TARGET *target); // 0x0005F56C

extern void DrawMultiplayerTarget(struct _TARGET *target); // 0x0005F864


#endif
