#ifndef FMVPLAY_H
#define FMVPLAY_H

extern int gSubtitles;
extern int gNoFMV;

extern void ReInitSystem(); // 0x0004D478
extern void PlayFMV(unsigned char render); // 0x0004D518
extern void PlayRender(RENDER_ARGS* args);

#endif
