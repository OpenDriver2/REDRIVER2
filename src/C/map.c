#include "../decomp_defs.h"

/*
 * Offset 0x5C88C
 * D:\driver2\game\C\MAP.C (line 438)
 * Stack frame base $sp, length 120
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CheckUnpackNewRegions()
{ // line 2, address 0x5c88c
	struct AREA_LOAD_INFO regions_to_unpack[3]; // stack address -104
	int leftright_unpack; // $a1
	int topbottom_unpack; // $a2
	int num_regions_to_unpack; // $s5
	int x; // $a2
	int z; // $v1
	int loop; // $s6
	int barrel_region; // $s1
	int sortcount; // $s4
	int i; // $v1
	int j; // $a2
	struct SVECTOR sortregions[4]; // stack address -80
	unsigned short sortorder[4]; // stack address -48
	int force_load_boundary; // $a0
	{ // line 101, address 0x5ca5c
		int region_to_unpack; // $s0
		struct Spool *spoolptr; // $a1
		{ // line 121, address 0x5cadc
		} // line 141, address 0x5cb68
	} // line 142, address 0x5cb68
	{ // line 146, address 0x5cb90
	} // line 156, address 0x5cbfc
} // line 160, address 0x5cc68
/*
 * Offset 0x5CC68
 * D:\driver2\game\C\MAP.C (line 612)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ControlMap()
{ // line 2, address 0x5cc68
	int x; // $a2
	int z; // $a1
	{ // line 27, address 0x5cd4c
	} // line 28, address 0x5cd54
	{ // line 36, address 0x5cd78
	} // line 37, address 0x5cd88
} // line 42, address 0x5cde8
/*
 * Offset 0x5CDE8
 * D:\driver2\game\C\MAP.C (line 677)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ InitMap()
{ // line 2, address 0x5cde8
	int i; // $s0
	int tpage; // $v0
	char result[8]; // stack address -24
	{ // line 30, address 0x5ce98
		{ // line 39, address 0x5cef0
			int region; // $a3
			int barrel_region; // $a1
			struct Spool *spoolptr; // $v1
			{ // line 49, address 0x5cf5c
			} // line 55, address 0x5cf88
		} // line 56, address 0x5cf88
	} // line 65, address 0x5cff8
	{ // line 1, address 0x5cff8
	} // line 1, address 0x5d010
} // line 67, address 0x5d010
/*
 * Offset 0x5D010
 * D:\driver2\game\C\MAP.C (line 824)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ PVSDecode(char *output /*$s2*/, char *celldata /*$s3*/, unsigned short sz /*$s0*/, int havanaCorruptCellBodge /*$s4*/)
{ // line 1, address 0x5d010
	char *decodeBuf; // $s1
	{ // line 1, address 0x5d010
		int pixelIndex; // $t0
		int i; // $a0
		int ni; // $a3
		//0x8EC spod
		{ // line 11, address 0x5d05c
		} // line 11, address 0x5d05c
		{ // line 18, address 0x5d0a4
			int symIndex; // $a2
			int sym; // $a0
			{ // line 1, address 0x5d110
				unsigned char *pt; // $v0
			} // line 1, address 0x5d110
			{ // line 1, address 0x5d124
				unsigned char *pt; // $v0
			} // line 1, address 0x5d124
		} // line 45, address 0x5d16c
	} // line 48, address 0x5d178
	{ // line 49, address 0x5d178
		int i; // $a2
		int j; // $v1
		int sz; // $a3
		char *op; // $a1
	} // line 80, address 0x5d24c
	{ // line 82, address 0x5d24c
		int i; // $v1
	} // line 87, address 0x5d28c
} // line 89, address 0x5d28c
/*
 * Offset 0x5D28C
 * D:\driver2\game\C\MAP.C (line 928)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ GetPVSRegionCell2(int source_region /*$a0*/, int region /*$a1*/, int cell /*$t2*/, char *output /*$a3*/)
{ // line 1, address 0x5d28c
	char *bp; // $a2
	char *tbp; // $a1
	int j; // $v1
	unsigned short length; // $t0
	{ // line 17, address 0x5d304
		unsigned char *pt; // $a0
	} // line 17, address 0x5d304
	{ // line 17, address 0x5d304
	} // line 17, address 0x5d304
	{ // line 1, address 0x5d394
		char *output; // $a0
		{ // line 1, address 0x5d394
			int k; // $v1
		} // line 1, address 0x5d3c4
	} // line 1, address 0x5d3c4
} // line 35, address 0x5d3c4
/*
 * Offset 0x5D3D4
 * D:\driver2\game\C\MAP.C (line 311)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitCellData()
{ // line 2, address 0x5d3d4
	char *alloclist; // $a2
	int loop; // $v1
} // line 49, address 0x5d474
/*
 * Offset 0x5D474
 * D:\driver2\game\C\MAP.C (line 289)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
struct MODEL * /*$ra*/ FindModelPtrWithName(char *name /*$s4*/)
{ // line 1, address 0x5d474
	int dummy; // stack address -32
	{ // line 1, address 0x5d474
		char *name; // $s4
		int *num; // $s2
		{ // line 1, address 0x5d474
			int count; // $s1
			char *temp; // $s0
		} // line 1, address 0x5d50c
	} // line 1, address 0x5d50c
} // line 4, address 0x5d52c
/*
 * Offset 0x5D52C
 * D:\driver2\game\C\MAP.C (line 295)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ FindModelIdxWithName(char *name /*$s3*/)
{ // line 1, address 0x5d52c
	int i; // stack address -32
	{ // line 1, address 0x5d52c
		char *name; // $s3
		int *num; // $s2
		{ // line 1, address 0x5d52c
			int count; // $s1
			char *temp; // $s0
		} // line 1, address 0x5d5a8
	} // line 1, address 0x5d5a8
} // line 5, address 0x5d5c8
/*
 * Offset 0x5D5C8
 * D:\driver2\game\C\MAP.C (line 400)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ PositionVisible(struct VECTOR *pos /*$a0*/)
{ // line 1, address 0x5d5c8
	int dx; // $a1
	int dz; // $a0
	int cellx; // $v1
	int cellz; // $v0
} // line 20, address 0x5d684
/*
 * Offset 0x5D684
 * D:\driver2\game\C\MAP.C (line 378)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ newPositionVisible(struct VECTOR *pos /*$a0*/, char *pvs /*$a1*/, int ccx /*$a2*/, int ccz /*$a3*/)
{ // line 1, address 0x5d684
	int dx; // $a2
	int dz; // $a0
	int cellx; // $v1
	int cellz; // $v0
} // line 20, address 0x5d72c
/*
 * Offset 0x5D72C
 * D:\driver2\game\C\MAP.C (line 252)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessRoadsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x5D734
 * D:\driver2\game\C\MAP.C (line 247)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessJunctionsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x5D73C
 * D:\driver2\game\C\MAP.C (line 253)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessRoadBoundsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x5D744
 * D:\driver2\game\C\MAP.C (line 254)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessJuncBoundsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x5D74C
 * D:\driver2\game\C\MAP.C (line 756)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ GetVisSetAtPosition(struct VECTOR *pos /*$a0*/, char *tgt /*$t3*/, int *ccx /*$a1*/, int *ccz /*$a3*/)
{ // line 1, address 0x5d74c
	int x; // $t2
	int z; // $t1
	int cx; // $t0
	int cz; // $a2
	int rx; // $a3
	int rz; // $a0
	{ // line 11, address 0x5d7d4
		int barrel_region_x; // $v0
		int barrel_region_z; // $a0
	} // line 22, address 0x5d824
} // line 23, address 0x5d824
/*
 * Offset 0x5D824
 * D:\driver2\game\C\MAP.C (line 237)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ NewProcessRoadMapLump(struct ROAD_MAP_LUMP_DATA *pRoadMapLumpData /*$s0*/, char *pLumpFile /*$s1*/)
{ // line 1, address 0x5d824
} // line 6, address 0x5d87c