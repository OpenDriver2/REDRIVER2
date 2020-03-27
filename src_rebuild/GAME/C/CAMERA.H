#ifndef CAMERA_H
#define CAMERA_H


extern void InitCamera(struct _PLAYER *lp); // 0x0001F5F4

extern void ModifyCamera(); // 0x0001FA20

extern int CameraCollisionCheck(); // 0x0001FC18

extern void TurnHead(struct _PLAYER *lp); // 0x00020A10

extern void PlaceCameraFollowCar(struct _PLAYER *lp); // 0x0002003C

extern void PlaceCameraAtLocation(struct _PLAYER *lp, int zoom); // 0x00020904

extern int PointAtTarget(struct VECTOR *pPosition, struct VECTOR *pTarget, struct SVECTOR *pAngleVec); // 0x00020B08

extern void PlaceCameraInCar(struct _PLAYER *lp, int BumperCam); // 0x0002050C

extern int OK_To_Zoom(); // 0x00020BC0

extern void SetBasePos(struct VECTOR *pVec); // 0x00020C70


#endif
