#ifndef TILE_H
#define TILE_H

extern void Tile1x1(MODEL *model); // 0x00041B10

extern void DrawTILES(PACKED_CELL_OBJECT** tiles, int tile_amount); // 0x00041D7C

extern void makeMesh(MVERTEX (*VSP)[5][5], int m, int n); // 0x000420B0

extern void drawMesh(MVERTEX (*VSP)[5][5], int m, int n, _pct *pc); // 0x00042650

extern void SubdivNxM(char *polys, int n, int m, int ofse); // 0x00042AEC

extern void TileNxN(MODEL *model, int levels, int Dofse); // 0x00042F40

extern void ProcessSubDivisionLump(char *lump_ptr, int lump_size); // 0x00042F34

extern void ProcessLowDetailTable(char *lump_ptr, int lump_size); // 0x00043090


#endif
