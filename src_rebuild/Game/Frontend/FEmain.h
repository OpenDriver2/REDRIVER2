#ifndef FEMAIN_H
#define FEMAIN_H

extern int gInFrontend;
extern int bRedrawFrontend;

extern void DoFrontEnd(); // 0x001C296C
extern void SetFEDrawMode();
extern void LoadFrontendScreens(int full);
extern void ReInitScreens();

#endif
