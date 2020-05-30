#ifndef OVERMAP_H
#define OVERMAP_H

extern unsigned short civ_clut[8][32][6];
extern int map_x_shift;
extern int map_z_shift;

extern void DrawTargetBlip(VECTOR *pos, unsigned char r, unsigned char g, unsigned char b, unsigned long flags); // 0x00016280

extern void DrawTargetArrow(VECTOR *pos, unsigned long flags); // 0x00016578

extern void DrawPlayerDot(VECTOR *pos, short rot, unsigned char r, unsigned char g, int b, unsigned long flags); // 0x00016814

extern void ProcessOverlayLump(char *lump_ptr, int lump_size); // 0x00016AE8

extern unsigned long Long2DDistance(VECTOR *pPoint1, VECTOR *pPoint2); // 0x00016C0C

extern void InitOverheadMap(); // 0x000197BC

extern void DrawOverheadMap(); // 0x00016D14

extern void DrawFullscreenMap(); // 0x00017C30

extern void DrawCopIndicators(); // 0x000183E8

extern void InitMultiplayerMap(); // 0x000198E0

extern void DrawMultiplayerMap(); // 0x000185A0

extern void WorldToMultiplayerMap(VECTOR *in, VECTOR *out); // 0x00019994

extern void ProcessPalletLump(char *lump_ptr, int lump_size); // 0x00019F44

extern void load_civ_palettes(RECT16 *cluts); // 0x0001A094

extern void FlashOverheadMap(int r, int g, int b); // 0x00018980

extern void LoadMapTile(int tpage, int x, int y); // 0x00018AA0

extern void SetMapPos(); // 0x00019A60

extern void draw_box(); // 0x00018BF4

extern void DrawN(VECTOR *pScreenPosition, int direct); // 0x00018D54

extern void DrawCompass(); // 0x00018F18

extern void DrawBigCompass(VECTOR *root, int angle); // 0x00019194

extern void CopIndicator(int xpos, int strength); // 0x000193B4

extern void DrawSightCone(COP_SIGHT_DATA *pCopSightData, VECTOR *pPosition, int direction); // 0x00019594

extern void WorldToOverheadMapPositions(VECTOR *pGlobalPosition, VECTOR *pOverheadMapPosition, int count, char inputRelative, int outputRelative); // 0x00019AF0

extern void SetFullscreenMapMatrix(); // 0x00019D0C

extern void WorldToFullscreenMap(VECTOR *in, VECTOR *out); // 0x00019DE8

extern void WorldToFullscreenMap2(VECTOR *in, VECTOR *out); // 0x00019E7C


#endif
