#ifndef MAP_H
#define MAP_H

#ifdef PSX

// original Driver 2 definition

#define MAP_REGION_SIZE		32
#define MAP_CELL_SIZE		2048

#else

extern OUT_CELL_FILE_HEADER cell_header;

// universal definition

// size in cells
#define MAP_REGION_SIZE			cell_header.region_size

// cell size
#define MAP_CELL_SIZE			cell_header.cell_size

#endif

extern int cells_across; // offset 0xAA67C
extern int cells_down; // offset 0xAA680

extern int current_region;
extern int old_region;

extern int LoadedArea;
extern int initarea;

extern char *map_lump;
extern PACKED_CELL_OBJECT** pcoplist;
extern CELL_OBJECT** coplist;
extern unsigned short *cell_ptrs;
extern PACKED_CELL_OBJECT* cell_objects;
extern int sizeof_cell_object_computed_values;
extern CELL_DATA* cells;
extern int num_straddlers;

extern int current_cell_x;
extern int current_cell_z;

extern int region_x;
extern int region_z;

extern int current_barrel_region_xcell;
extern int current_barrel_region_zcell;

extern char* PVS_Buffers[4];
extern int pvsSize[4];

extern int num_regions;
extern int view_dist;
extern int pvs_square;
extern int pvs_square_sq;

extern int units_across_halved;
extern int units_down_halved;

extern int regions_across;
extern int regions_down;

extern void NewProcessRoadMapLump(ROAD_MAP_LUMP_DATA *pRoadMapLumpData, char *pLumpFile); // 0x0005D7BC

extern void ProcessJunctionsLump(char *lump_file, int lump_size); // 0x0005D6CC

extern void ProcessRoadsLump(char *lump_file, int lump_size); // 0x0005D6C4

extern void ProcessRoadBoundsLump(char *lump_file, int lump_size); // 0x0005D6D4

extern void ProcessJuncBoundsLump(char *lump_file, int lump_size); // 0x0005D6DC

extern struct MODEL * FindModelPtrWithName(char *name); // 0x0005D40C

extern int FindModelIdxWithName(char *name); // 0x0005D4C4

extern void InitCellData(); // 0x0005D36C

extern int newPositionVisible(VECTOR *pos, char *pvs, int ccx, int ccz); // 0x0005D61C

extern int PositionVisible(VECTOR *pos); // 0x0005D560

extern int CheckUnpackNewRegions(); // 0x0005C824

extern void ControlMap(); // 0x0005CC00

extern void InitMap(); // 0x0005CD80

extern void GetVisSetAtPosition(VECTOR *pos, char *tgt, int *ccx, int *ccz); // 0x0005D6E4

extern void PVSDecode(char *output, char *celldata, unsigned short sz, int havanaCorruptCellBodge); // 0x0005CFA8

extern void GetPVSRegionCell2(int source_region, int region, int cell, char *output); // 0x0005D224


#endif
