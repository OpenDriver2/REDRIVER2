#ifndef MC_SND_H
#define MC_SND_H

extern char es_mobile[1];
extern int jericho_in_back;

extern char GetMissionSound(char id); // 0x0005D814

extern void RequestXA(); // 0x0005F12C

extern void HandleRequestedXA(); // 0x0005F1B4

extern void InitializeCutsceneSound(int cutscene); // 0x0005F224

extern void DoCutsceneSound(); // 0x0005D950

extern void InitializeMissionSound(); // 0x0005DD10

extern void DoMissionSound(); // 0x0005E020

extern void SetMSoundVar(int var, VECTOR *V); // 0x0005F25C

extern char SilenceThisCar(int car); // 0x0005EE00

extern void AdjustPlayerCarVolume(); // 0x0005F294


#endif
