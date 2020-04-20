#ifndef DRAW_H
#define DRAW_H

extern MATRIX aspect;

extern int units_across_halved;
extern int units_down_halved;
extern int pvs_square;
extern int pvs_square_sq;
extern int PolySizes[56];
extern ulong* tile_overflow_buffer;

extern MATRIX inv_camera_matrix;
extern MATRIX2 CompoundMatrix[64];

extern int combointensity;

extern int gForceLowDetailCars;
extern int num_cars_drawn;


extern void addSubdivSpriteShadow(struct POLYFT4LIT *src, struct SVECTOR *verts, int z); // 0x0003ED7C

extern void DrawSprites(int numFound); // 0x0003EF64

extern struct PACKED_CELL_OBJECT * GetNextPackedCop(struct CELL_ITERATOR *pci); // 0x0003F5F0

extern struct CELL_OBJECT * UnpackCellObject(struct PACKED_CELL_OBJECT *ppco, struct XZPAIR *near); // 0x000418E8

extern void DrawMapPSX(int *comp_val); // 0x0003F6B0

extern void SetupPlaneColours(unsigned long ambient); // 0x00040218

extern void SetupDrawMapPSX(); // 0x00040408

extern void InitFrustrumMatrix(); // 0x00040534

extern void SetFrustrumMatrix(); // 0x000417A4

extern void Set_Inv_CameraMatrix(); // 0x000417DC

extern void CalcObjectRotationMatrices(); // 0x00041814

extern void PlotMDL_less_than_128(struct MODEL *model); // 0x000418BC

extern void ProcessMapLump(char *lump_ptr, int lump_size); // 0x00040608

extern void DrawAllTheCars(int view); // 0x000407D8

extern void PlotBuildingModelSubdivNxN(MODEL *model, int rot, struct _pct *pc, int n); // 0x00040A90

extern int DrawAllBuildings(unsigned long *objects, int num_buildings, DB *disp); // 0x000411F4

extern void RenderModel(MODEL *model, MATRIX *matrix, VECTOR *pos, int zBias, int flags); // 0x0004143C

extern unsigned long normalIndex(SVECTOR *verts, unsigned int vidx); // 0x000415E4


#endif
