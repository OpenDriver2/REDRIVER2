#ifndef TARGETS_H
#define TARGETS_H


extern void Draw3DTarget(struct VECTOR *position, int flags); // 0x0007FB44

extern void DrawTargetArrowModel(struct TARGET_ARROW_MODEL *pTargetArrowModel, struct VECTOR *pPosition, int shadow, int invert); // 0x0007FD48

extern void DrawStopZone(struct VECTOR *pPosition); // 0x000800F8

extern void WorldToCameraPositions(struct VECTOR *pGlobalPositionIn, struct VECTOR *pCameraPositionOut, int count); // 0x0008047C


#endif
