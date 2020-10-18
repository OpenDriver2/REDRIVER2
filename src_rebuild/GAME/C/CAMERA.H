#ifndef CAMERA_H
#define CAMERA_H

extern VECTOR camera_position;
extern char old_camera_change;
extern char camera_change;

extern MATRIX face_camera_work;
extern MATRIX camera_matrix;

extern char cameraview;
extern char tracking_car;
extern int CameraCnt;

extern int TargetCar;
extern int CameraCar;

extern SVECTOR camera_angle;
extern int gCameraAngle;
extern short gCameraDistance;
extern short gCameraMaxDistance;
extern VECTOR gCameraOffset;

extern int switch_detail_distance;

extern void InitCamera(_PLAYER *lp); // 0x0001F5F4

extern void ModifyCamera(); // 0x0001FA20

extern int CameraCollisionCheck(); // 0x0001FC18

extern void TurnHead(_PLAYER *lp); // 0x00020A10

extern void PlaceCameraFollowCar(_PLAYER *lp); // 0x0002003C

extern void PlaceCameraAtLocation(_PLAYER *lp, int zoom); // 0x00020904

extern int PointAtTarget(VECTOR *pPosition, VECTOR *pTarget, SVECTOR *pAngleVec); // 0x00020B08

extern void PlaceCameraInCar(_PLAYER *lp, int BumperCam); // 0x0002050C

extern int OK_To_Zoom(); // 0x00020BC0

extern void SetBasePos(VECTOR *pVec); // 0x00020C70


#endif
