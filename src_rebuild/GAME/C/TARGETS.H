#ifndef TARGETS_H
#define TARGETS_H

extern int gDraw3DArrowBlue;

extern void Draw3DTarget(VECTOR *position, int flags); // 0x0007FB44

extern void DrawTargetArrowModel(TARGET_ARROW_MODEL *pTargetArrowModel, VECTOR *pPosition, int shadow, int invert); // 0x0007FD48

extern void DrawStopZone(VECTOR *pPosition); // 0x000800F8

extern void WorldToCameraPositions(VECTOR *pGlobalPositionIn, VECTOR *pCameraPositionOut, int count); // 0x0008047C


#endif
