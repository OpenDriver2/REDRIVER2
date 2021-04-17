#ifndef FEMAIN_H
#define FEMAIN_H

extern int gInFrontend;
extern int bRedrawFrontend;

extern void InitFrontendDisplay();
extern void InitFrontend();

extern void State_FrontEnd(void* param); // 0x001C296C

extern void SetFEDrawMode();
extern void LoadFrontendScreens(int full);
extern void ReInitScreens(int returnToMain);

#endif
