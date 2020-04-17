#ifndef CUTSCENE_H
#define CUTSCENE_H

extern int gInGameCutsceneActive;
extern int gInGameCutsceneDelay;
extern int gInGameChaseActive;
extern int gInGameCutsceneID;
extern int gThePlayerCar;

extern void InitInGameCutsceneVariables(); // 0x000325C0

extern void HandleInGameCutscene(); // 0x0003262C

extern void DrawInGameCutscene(); // 0x00031398

extern void TriggerChase(int *car, int cutscene); // 0x000314E8

extern void TriggerInGameCutscene(int cutscene); // 0x00032740

extern int CalcInGameCutsceneSize(); // 0x0003283C

extern void ReleaseInGameCutscene(); // 0x000316EC

extern int PreLoadInGameCutscene(int chase); // 0x000328C8

extern int CutsceneCameraChange(int cameracnt); // 0x000328E8

extern int LoadInGameCutscene(int subindex); // 0x000329B4

extern int TriggerInGameCutsceneSystem(int cutscene); // 0x00031A20

extern void SetNullPlayer(int plr); // 0x00031EDC

extern void SetNullPlayerDontKill(int plr); // 0x00031F60

extern void DestroyPlayer(int plr, int fully); // 0x00031FE0

extern void FindNextCutChange(int cameracnt); // 0x00032A34

extern int LoadCutsceneToReplayBuffer(int residentCutscene); // 0x00032118

extern int LoadCutsceneToBuffer(int subindex); // 0x0003243C

extern void ShowCutsceneError(); // 0x00032C08

extern int LoadCutsceneInformation(int cutscene); // 0x00032A98

extern void FreeCutsceneBuffer(); // 0x00032B54

extern int IsCutsceneResident(int cutscene); // 0x00032BC0


#endif
