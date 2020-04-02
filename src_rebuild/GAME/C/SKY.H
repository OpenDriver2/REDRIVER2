#ifndef SKY_H
#define SKY_H


extern void LoadSky(); // 0x000775C8

extern void DrawSkyDome(); // 0x0007795C

extern void DrawLensFlare(); // 0x00077A8C

extern void DisplaySun(DVECTOR *pos, CVECTOR *col, int flare_col); // 0x000780BC

extern void DisplayMoon(DVECTOR *pos, CVECTOR *col, int flip); // 0x00078544

extern void TunnelSkyFade(); // 0x000787B0

extern void calc_sky_brightness(); // 0x00078964

extern void PlotSkyPoly(int skytexnum, unsigned char r, unsigned char g, unsigned char b, int offset); // 0x00078B18

extern void PlotHorizonMDL(struct MODEL *model, int horizontaboffset); // 0x00078EC4


#endif
