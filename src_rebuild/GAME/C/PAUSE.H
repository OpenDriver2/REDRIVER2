#ifndef PAUSE_H
#define PAUSE_H

extern int gShowMap;
extern int gDrawPauseMenus;
extern int pauseflag;
extern int gMissionCompletionState;

extern int ShowPauseMenu(PAUSEMODE mode);
extern void DrawPauseMenus();
extern void ControlMenu();

void SaveReplay(int direction);


#endif
