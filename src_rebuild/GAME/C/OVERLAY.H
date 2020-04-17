#ifndef OVERLAY_H
#define OVERLAY_H

extern _PERCENTAGE_BAR ProxyBar;

extern void InitOverlays(); // 0x00014A58

extern void DisplayOverlays(); // 0x00014C3C

extern void SetFullscreenDrawing(); // 0x00015E70

extern void InitPercentageBar(struct _PERCENTAGE_BAR *bar, int size, struct COLOUR_BAND *pColourBand, char *tag); // 0x00015F20

extern void EnablePercentageBar(struct _PERCENTAGE_BAR *bar, int max); // 0x00015F58

extern void DrawPercentageBar(struct _PERCENTAGE_BAR *bar); // 0x00014DA8

extern void DrawProximityBar(struct _PERCENTAGE_BAR *bar); // 0x000152D4

extern void SetColourByValue(struct COLOUR_BAND *pColourBand, int value, struct CVECTOR *pOut); // 0x00015F6C

extern void TransparencyOn(void *potz, unsigned short tpage); // 0x00016098

extern void UpdateFlashValue(); // 0x00016114

extern void DrawDrivingGameOverlays(); // 0x000157F4

extern void PrintScoreTableTime(int x, int y, int time); // 0x00016184


#endif
