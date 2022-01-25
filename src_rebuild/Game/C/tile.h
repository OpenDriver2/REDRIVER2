#ifndef TILE_H
#define TILE_H

struct MVERTEX
{
	short vx;
	short vy;
	short vz;
	union {
		short val;
		struct {
			u_char u0;
			u_char v0;
		}s;
	}uv;
};

struct VERTEX
{
	DVECTOR coord;
	UV_INFO uv_coord;
	u_char pad[2];
};

extern void DrawTILES(PACKED_CELL_OBJECT** tiles, int tile_amount); // 0x00041D7C

extern void Tile1x1(MODEL *model); // 0x00041B10

extern void makeMesh(MVERTEX (*VSP)[5][5], int m, int n); // 0x000420B0
extern void drawMesh(MVERTEX (*VSP)[5][5], int m, int n, _pct *pc); // 0x00042650

extern void SubdivNxM(char *polys, int n, int m, int ofse); // 0x00042AEC
extern void TileNxN(MODEL *model, int levels, int Dofse); // 0x00042F40

extern void ProcessSubDivisionLump(char *lump_ptr, int lump_size); // 0x00042F34
extern void ProcessLowDetailTable(char *lump_ptr, int lump_size); // 0x00043090


#endif
