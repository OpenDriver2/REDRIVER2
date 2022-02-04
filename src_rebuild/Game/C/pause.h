#ifndef PAUSE_H
#define PAUSE_H

enum EXIT_VALUE
{
	MENU_QUIT_NONE = 0,
	MENU_QUIT_CONTINUE = 1,
	MENU_QUIT_QUIT = 2,
	MENU_QUIT_RESTART = 3,
	MENU_QUIT_DIRECTOR = 4,
	MENU_QUIT_QUICKREPLAY = 5,
	MENU_QUIT_BACKMENU = 6,
	MENU_QUIT_NEXTMISSION = 7,
};

extern int gShowMap;
extern int gDrawPauseMenus;
extern int pauseflag;
extern int gMissionCompletionState;

extern int UpdatePauseMenu(PAUSEMODE mode);
extern void ShowPauseMenu(PAUSEMODE mode);

extern void DrawPauseMenus();
extern void ControlMenu();

void SaveReplay(int direction);


#endif
