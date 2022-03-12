#ifndef DIRECTOR_H
#define DIRECTOR_H

extern TEXTURE_DETAILS icon_addcam;
extern TEXTURE_DETAILS icon_frameadv;
extern TEXTURE_DETAILS icon_autocam;
extern TEXTURE_DETAILS icon_chasecar;
extern TEXTURE_DETAILS icon_choosecar;
extern TEXTURE_DETAILS icon_clock;
extern TEXTURE_DETAILS icon_delcam;
extern TEXTURE_DETAILS icon_editcam;
extern TEXTURE_DETAILS icon_fixedcam;
extern TEXTURE_DETAILS icon_incar;
extern TEXTURE_DETAILS icon_lenschan;
extern TEXTURE_DETAILS icon_lookcar;
extern TEXTURE_DETAILS icon_movecam;
extern TEXTURE_DETAILS icon_movecampos;
extern TEXTURE_DETAILS icon_ok;
extern TEXTURE_DETAILS icon_pause;
extern TEXTURE_DETAILS icon_playcam;
extern TEXTURE_DETAILS icon_playpause;
extern TEXTURE_DETAILS icon_save2card;
extern TEXTURE_DETAILS icon_restart;

extern int FastForward;
extern int EditMode;
extern int ClearCameras;

extern void InitDirectorVariables(); // 0x0003E79C
extern void DeleteAllCameras(); // 0x0003EA40

extern void ShowReplayOptions(); // 0x0003EAA4
extern void ControlReplay(); // 0x0003C7A8

extern void SetPlaybackCamera(PLAYBACKCAMERA* camera); // 0x0003EC0C
extern int InvalidCamera(int car_num); // 0x0003E53C
extern void FindNextChange(int CameraCnt); // 0x0003E94C
extern int CheckCameraChange(int CameraCnt); // 0x0003B794

extern int dist(VECTOR* pos1, VECTOR* pos2);

extern int IsMovingCamera(PLAYBACKCAMERA* lastcam, PLAYBACKCAMERA* nextcam, int cameracnt); // 0x0003B8C8

#endif
