#ifndef DR2ROADS_H
#define DR2ROADS_H


extern void ProcessStraightsDriver2Lump(char *lump_file, int lump_size); // 0x000136C0

extern void ProcessCurvesDriver2Lump(char *lump_file, int lump_size); // 0x000136F4

extern void ProcessJunctionsDriver2Lump(char *lump_file, int lump_size, int fix); // 0x00013728

extern int MapHeight(struct VECTOR *pos); // 0x000137CC

extern int FindSurfaceD2(struct VECTOR *pos, struct VECTOR *normal, struct VECTOR *out, struct _sdPlane **plane); // 0x00012EF4

extern int sdHeightOnPlane(struct VECTOR *pos, struct _sdPlane *plane); // 0x000130D4

extern int GetSurfaceIndex(struct VECTOR *pos); // 0x0001380C

extern struct _sdPlane * FindRoadInBSP(struct _sdNode *node, struct _sdPlane *base); // 0x000138F0

extern int RoadInCell(struct VECTOR *pos); // 0x0001322C

extern struct _sdPlane * sdGetCell(struct VECTOR *pos); // 0x0001346C

extern short * sdGetBSP(struct _sdNode *node, struct XYPAIR *pos); // 0x00013848


#endif
