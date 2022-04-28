#ifndef OVERMAP_H
#define OVERMAP_H

#define MAP_SIZE_W	64 // default 64
#define MAP_SIZE_H	60 // default 60

extern int gMapXOffset;
extern int gMapYOffset;

extern int map_x_shift;
extern int map_z_shift;

extern void InitOverheadMap(); // 0x000197BC
extern void ProcessOverlayLump(char *lump_ptr, int lump_size); // 0x00016AE8

extern void DrawTargetBlip(VECTOR *pos, u_char r, u_char g, u_char b, int flags); // 0x00016280
extern void DrawTargetArrow(VECTOR *pos, int flags); // 0x00016578

extern void DrawCopIndicators(void);

extern void DrawOverheadMap(); // 0x00016D14
extern void DrawFullscreenMap();

extern u_int Long2DDistance(VECTOR *pPoint1, VECTOR *pPoint2); // 0x00016C0C

#endif
