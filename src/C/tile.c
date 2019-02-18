
/*
 * Offset 0x41B78
 * D:\driver2\game\C\TILE.C (line 79)
 * Stack frame base $sp, length 16
 * Saved registers at address -8: s0
 */
void /*$ra*/ Tile1x1(struct MODEL *model /*$a0*/)
{ // line 1, address 0x41b78
	int i; // $t3
	unsigned char *polys; // $t0
	struct SVECTOR *verts; // $t1
	struct POLY_FT4 *prims; // $a2
	unsigned long clut; // $t6
	unsigned long tpage; // $a1
	{ // line 14, address 0x41bb4
		unsigned long indices; // $a3
		unsigned long texInfo; // $t2
		{ // line 14, address 0x41bb4
			long *ot; // $t8
			{ // line 14, address 0x41bb4
				int Z; // stack address -16
				unsigned long uv_01; // $t4
				unsigned long uv_23; // $t5
				//0x1B4 otherhalf
				{ // line 65, address 0x41d2c
					int r2; // $a0
				} // line 65, address 0x41d2c
			} // line 82, address 0x41db0
		} // line 83, address 0x41db0
	} // line 84, address 0x41db0
} // line 87, address 0x41de4
/*
 * Offset 0x41DE4
 * D:\driver2\game\C\TILE.C (line 180)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ DrawTILES(int tile_amount /*$s2*/)
{ // line 1, address 0x41de4
	{ // line 21, address 0x41eec
	} // line 24, address 0x41f24
	{ // line 28, address 0x41f24
		struct PACKED_CELL_OBJECT **tilePointers; // $s3
		int previous_matrix; // $s4
		{ // line 40, address 0x41f9c
			int model_number; // $s0
			int z; // $a1
			{ // line 43, address 0x41f9c
				int yang; // $a1
				struct PACKED_CELL_OBJECT *ppco; // $a0
			} // line 61, address 0x42020
			{ // line 90, address 0x42094
				struct MODEL *model; // $a0
			} // line 99, address 0x420c8
		} // line 102, address 0x420c8
	} // line 105, address 0x42118
} // line 107, address 0x42118
/*
 * Offset 0x42118
 * D:\driver2\game\C\TILE.C (line 292)
 * Stack frame base $sp, length 8
 * Saved registers at address -8: s0
 */
void /*$ra*/ makeMesh(struct MVERTEX *VSP[5][5] /*$t4*/, int m /*$t2*/, int n /*$a2*/)
{ // line 1, address 0x42118
	{ // line 21, address 0x42130
		int a; // $t0
		int b; // $t1
	} // line 21, address 0x42130
	{ // line 21, address 0x42130
		int a; // $a3
	} // line 21, address 0x42130
	{ // line 21, address 0x42130
		int a; // $a0
		int b; // $a1
	} // line 21, address 0x42130
	{ // line 28, address 0x4221c
		int a; // $t0
		int b; // $t1
	} // line 28, address 0x4221c
	{ // line 28, address 0x4221c
		int a; // $a3
	} // line 28, address 0x4221c
	{ // line 28, address 0x4221c
		int a; // $a0
		int b; // $a1
	} // line 28, address 0x4221c
	{ // line 34, address 0x422f4
		int k; // $s0
		{ // line 35, address 0x422f4
			int a; // $t0
			int b; // $t1
		} // line 35, address 0x422f4
		{ // line 35, address 0x422f4
			int a; // $a3
		} // line 35, address 0x422f4
		{ // line 35, address 0x422f4
			int a; // $a0
			int b; // $a1
		} // line 35, address 0x422f4
		{ // line 40, address 0x423e0
			int a; // $t0
			int b; // $t1
		} // line 40, address 0x423e0
		{ // line 40, address 0x423e0
			int a; // $a3
		} // line 40, address 0x423e0
		{ // line 40, address 0x423e0
			int a; // $a0
			int b; // $a1
		} // line 40, address 0x423e0
	} // line 44, address 0x424c0
	{ // line 48, address 0x424c8
		int a; // $t1
		int b; // $t5
	} // line 48, address 0x424c8
	{ // line 51, address 0x42538
		int a; // $v0
		int b; // $a1
	} // line 51, address 0x42538
	{ // line 55, address 0x42594
		int a; // $t0
		int b; // $t2
	} // line 55, address 0x42594
	{ // line 55, address 0x42594
		int a; // $t3
		int b; // $v0
	} // line 55, address 0x42594
	{ // line 55, address 0x42594
		int a; // $a2
	} // line 55, address 0x42594
	{ // line 55, address 0x42594
		int a; // $t8
		int b; // $a1
	} // line 58, address 0x426ac
} // line 61, address 0x426b8
/*
 * Offset 0x426B8
 * D:\driver2\game\C\TILE.C (line 359)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 s1 s2 s3
 */
void /*$ra*/ drawMesh(struct MVERTEX *VSP[5][5] /*$s2*/, int m /*$s3*/, int n /*$s1*/, struct _pct *pc /*$a3*/)
{ // line 1, address 0x426b8
	int j; // $t6
	int k; // $t9
	struct POLY_FT4 *prims; // $t1
	{ // line 11, address 0x42720
		int Z1; // stack address -24
		int Z2; // stack address -20
		struct MVERTEX *VST[5][5]; // $t2
		long *ot; // $t7
		{ // line 23, address 0x4277c
			int r2; // $v0
		} // line 23, address 0x4277c
		{ // line 103, address 0x42a98
			int r2; // $v0
		} // line 121, address 0x42b1c
	} // line 124, address 0x42b1c
} // line 127, address 0x42b54
/*
 * Offset 0x42B54
 * D:\driver2\game\C\TILE.C (line 489)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ SubdivNxM(char *polys /*$t4*/, unsigned long n /*$s1*/, unsigned long m /*$s0*/, int ofse /*$s2*/)
{ // line 1, address 0x42b54
	struct MVERTEX *VSP[5][5]; // $t3
	struct _pct *pc; // $t2
	{ // line 1, address 0x42b54
		unsigned long indices; // $a0
		struct SVECTOR *v0; // $t1
		struct SVECTOR *v1; // $a1
		struct SVECTOR *v2; // $t0
	} // line 1, address 0x42b54
	{ // line 1, address 0x42b54
		unsigned long uv_01; // $v1
		unsigned long uv_23; // $a2
	} // line 1, address 0x42b54
	{ // line 58, address 0x42e54
		int Z; // stack address -24
		{ // line 73, address 0x42ec8
			unsigned long texInfo; // $a0
		} // line 80, address 0x42f3c
	} // line 86, address 0x42f6c
} // line 88, address 0x42f9c
/*
 * Offset 0x42F9C
 * D:\driver2\game\C\TILE.C (line 641)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessSubDivisionLump(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x42FA8
 * D:\driver2\game\C\TILE.C (line 581)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ TileNxN(struct MODEL *model /*$s4*/, int levels /*$s2*/, int Dofse /*$s6*/)
{ // line 1, address 0x42fa8
	int i; // $s3
	char *polys; // $s0
	char ttype; // $a3
	unsigned long tiletypes; // $s1
	int baseOffset; // $s5
} // line 50, address 0x430f8
/*
 * Offset 0x430F8
 * D:\driver2\game\C\TILE.C (line 651)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessLowDetailTable(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
{ // line 1, address 0x430f8
	int i; // $a1
} // line 23, address 0x43174