#ifndef E3STUFF_H
#define E3STUFF_H


extern void ShowHiresScreens(char **names, int delay, int wait); // 0x00044CE0

extern void FadeInHiresScreen(char *filename); // 0x00044244

extern void FadeOutHiresScreen(); // 0x000445F4

extern void SetupDefDrawEnv(DRAWENV *env, int x, int y, int w, int h); // 0x00044E40

extern void SetupDefDispEnv(DISPENV *env, int x, int y, int w, int h); // 0x00044DA0

extern void SetPleaseWait(char *buffer); // 0x000448CC

extern void CheckForCorrectDisc(int disc); // 0x00044A40


#endif
