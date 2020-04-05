#ifndef DR2ROADS_H
#define DR2ROADS_H

extern ROAD_MAP_LUMP_DATA roadMapLumpData;
extern int NumTempJunctions;
extern DRIVER2_JUNCTION *Driver2JunctionsPtr;
extern ulong *Driver2TempJunctionsPtr;

extern void ProcessStraightsDriver2Lump(char *lump_file, int lump_size); // 0x000136C0

extern void ProcessCurvesDriver2Lump(char *lump_file, int lump_size); // 0x000136F4

extern void ProcessJunctionsDriver2Lump(char *lump_file, int lump_size, int fix); // 0x00013728

extern int MapHeight(VECTOR *pos); // 0x000137CC

extern int FindSurfaceD2(VECTOR *pos, VECTOR *normal, VECTOR *out, _sdPlane **plane); // 0x00012EF4

extern int sdHeightOnPlane(VECTOR *pos, _sdPlane *plane); // 0x000130D4

extern int GetSurfaceIndex(VECTOR *pos); // 0x0001380C

extern _sdPlane * FindRoadInBSP(_sdNode *node, _sdPlane *base); // 0x000138F0

extern int RoadInCell(VECTOR *pos); // 0x0001322C

extern _sdPlane * sdGetCell(VECTOR *pos); // 0x0001346C

extern short * sdGetBSP(_sdNode *node, XYPAIR *pos); // 0x00013848


#endif
