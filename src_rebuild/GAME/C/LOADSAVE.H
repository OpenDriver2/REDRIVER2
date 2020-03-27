#ifndef LOADSAVE_H
#define LOADSAVE_H


extern int CalcReplayDataSize(); // 0x00057FD4

extern int SaveReplayData(char *buffer); // 0x00057FF4

extern int LoadReplayData(char *buffer); // 0x00058014

extern int CalcGameDataSize(); // 0x00058034

extern int SaveGameData(char *buffer); // 0x0005803C

extern int LoadGameData(char *buffer); // 0x000580CC

extern int CalcConfigDataSize(); // 0x00058164

extern int SaveConfigData(char *buffer); // 0x00057BF0

extern int LoadConfigData(char *buffer); // 0x00057DF0


#endif
