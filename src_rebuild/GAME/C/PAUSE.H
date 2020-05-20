#ifndef PAUSE_H
#define PAUSE_H

extern int gShowMap;
extern int pauseflag;
extern PAUSEMODE gMissionCompletionState;

extern int ShowPauseMenu(enum PAUSEMODE mode); // 0x0006BF50

extern void DrawPauseMenus(); // 0x0006DCD4

extern void SaveReplay(int direction); // 0x0006D9B0

extern void SaveGame(int direction); // 0x0006D9D4

extern void EnterName(); // 0x0006D9F8

extern int MaxMenuStringLength(struct MENU_HEADER *pMenu); // 0x0006DA18

extern void InitaliseMenu(enum PAUSEMODE mode); // 0x0006C2AC

extern void SetupMenu(struct MENU_HEADER *menu, int back); // 0x0006C6B8

extern void DrawVisibleMenus(); // 0x0006C7F4

extern void ControlMenu(); // 0x0006CBE8

extern void PauseMap(int direction); // 0x0006DAD0

extern void SfxVolume(int direction); // 0x0006DB34

extern void MusicVolume(int direction); // 0x0006DC04

extern void EnterScoreName(); // 0x0006D044

extern void CreateScoreNames(struct SCORE_ENTRY *table, struct PLAYER_SCORE *score, int position); // 0x0006D324

extern void DrawHighScoreMenu(int selection); // 0x0006D694


#endif
