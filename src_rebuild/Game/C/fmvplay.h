#ifndef FMVPLAY_H
#define FMVPLAY_H

struct RENDER_ARG
{
	u_char render;
	u_char credits;
	u_short recap;
};

struct RENDER_ARGS
{
	u_char nRenders;
	u_char subtitle;
	char screenx;
	char screeny;
	RENDER_ARG Args[4];
};

extern int gSubtitles;
extern int gNoFMV;

extern void ReInitSystem(); // 0x0004D478
extern void PlayFMV(unsigned char render); // 0x0004D518
extern void PlayRender(RENDER_ARGS* args);

#endif
