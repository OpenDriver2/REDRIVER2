#ifndef FEMAIN_H
#define FEMAIN_H

#define BG_WIDTH 64
#define BG_HEIGHT 256
#define BG_SPLICE_SIZE (BG_WIDTH * BG_HEIGHT)
#define CLUT_OFFSET 0x58000

extern int gInFrontend;
extern int bRedrawFrontend;

extern void InitFrontendDisplay();
extern void InitFrontend();

extern void State_FrontEnd(void* param); // 0x001C296C

extern void SetFEDrawMode();
extern void LoadFrontendScreens(int full);
extern void ReInitScreens(int returnToMain);

#endif
