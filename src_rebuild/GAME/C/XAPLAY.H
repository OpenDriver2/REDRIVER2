#ifndef XAPLAY_H
#define XAPLAY_H

extern void PrintXASubtitles();

extern void GetMissionXAData(int number); // 0x00082EC0

extern void GetXAData(int number); // 0x00082D60

extern void SetXAVolume(int volume); // 0x00082F18

extern void PrepareXA(); // 0x00082DAC

extern void PlayXA(int num, int index); // 0x00082C64

extern int XAPrepared(); // 0x000830F0

extern void UnprepareXA(); // 0x00082E68

extern void StopXA(); // 0x00082F78

extern void cbready(int intr, unsigned char *result); // 0x000830FC

extern void ResumeXA(); // 0x00082FC4

extern void PauseXA(); // 0x00083078


#endif
