#ifndef CUTSCENE_H
#define CUTSCENE_H

#ifndef PSX
#define MAX_USER_REPLAYS 16

extern char gUserReplayFolderList[MAX_USER_REPLAYS][48];
extern int gNumUserChases;

extern void InitUserReplays(const char* str);

#endif

extern CUTSCENE_BUFFER CutsceneBuffer;

extern int NumCutsceneStreams;
extern int gSkipInGameCutscene;
extern int gInGameCutsceneID;
extern int gInGameCutsceneActive;
extern int gInGameCutsceneDelay;
extern int gInGameChaseActive;
extern int gInGameCutsceneID;
extern int gCutsceneAtEnd;
extern int gThePlayerCar;

extern int JustReturnedFromCutscene;
extern int CutsceneEventTrigger;

extern void InitInGameCutsceneVariables(); // 0x000325C0
extern void HandleInGameCutscene(); // 0x0003262C
extern void DrawInGameCutscene(); // 0x00031398

extern void TriggerChase(int *car, int cutscene); // 0x000314E8
extern void TriggerInGameCutscene(int cutscene); // 0x00032740
extern int TriggerInGameCutsceneSystem(int cutscene); // 0x00031A20

extern int CalcInGameCutsceneSize(); // 0x0003283C

extern int LoadInGameCutscene(int subindex); // 0x000329B4
extern int PreLoadInGameCutscene(int chase); // 0x000328C8
extern void ReleaseInGameCutscene(); // 0x000316EC

extern int CutsceneCameraChange(int cameracnt); // 0x000328E8


#endif
