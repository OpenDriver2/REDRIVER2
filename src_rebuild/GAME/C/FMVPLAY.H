#ifndef FMVPLAY_H
#define FMVPLAY_H

extern int gSubtitles;
extern int gNoFMV;

extern void ReInitSystem(); // 0x0004D478

extern void PlayFMV(unsigned char render); // 0x0004D518

extern void PlayRender(struct RENDER_ARGS *args); // 0x0004D5D0


#endif
