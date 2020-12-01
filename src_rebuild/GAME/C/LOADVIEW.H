#ifndef LOADVIEW_H
#define LOADVIEW_H

extern int FadingScreen;
extern int gFastLoadingScreens;

extern void ShowLoading(); // 0x0005816C

extern void SetupScreenFade(int start, int end, int speed); // 0x000589B0

extern void FadeGameScreen(int flag); // 0x000582AC

extern void ShowLoadingScreen(char *screen_name, int effect, int loading_steps); // 0x000583F4

extern void CloseShutters(int speed, int width, int height); // 0x000589D0

extern void SetupFadePolys(); // 0x00058794

extern void DrawFadePoly(); // 0x00058824

extern void DisplayMissionTitle(); // 0x00058B08


#endif
