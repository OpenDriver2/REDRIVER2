#include "../decomp_defs.h"

sdPlane sea = { 9, 0, 16384, 0, 2048 };



/*
 * Offset 0x12F5C
 * D:\driver2\game\C\DR2ROADS.C (line 164)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ FindSurfaceD2(struct VECTOR *pos /*$s0*/, struct VECTOR *normal /*$s1*/, struct VECTOR *out /*$s3*/, struct _sdPlane **plane /*$s2*/)
{
}
/*
 * Offset 0x1313C
 * D:\driver2\game\C\DR2ROADS.C (line 205)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ sdHeightOnPlane(struct VECTOR *pos /*$t0*/, struct _sdPlane *plane /*$a1*/)
{ // line 1, address 0x1313c
	{ // line 11, address 0x1319c
		int angle; // $v0
		int i; // $v0
		struct DRIVER2_CURVE *curve; // $s0
	} // line 23, address 0x13204
	{ // line 26, address 0x13204
		int val; // $a3
		{ // line 35, address 0x13224
			int lx; // $v0
			int ly; // $v1
		} // line 39, address 0x13280
	} // line 42, address 0x13294
} // line 43, address 0x13294
/*
 * Offset 0x13294
 * D:\driver2\game\C\DR2ROADS.C (line 295)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ RoadInCell(struct VECTOR *pos /*$s5*/)
{ // line 1, address 0x13294
	char *buffer; // $s2
	struct XYPAIR cellPos; // stack address -48
	struct XYPAIR cell; // stack address -40
	short *surface; // $a0
	struct _sdPlane *plane; // $s0
	{ // line 36, address 0x13380
		int moreLevels; // $s3
		short *check; // $s1
		struct _sdPlane *base; // $s4
	} // line 77, address 0x1344c
} // line 94, address 0x134d4
/*
 * Offset 0x134D4
 * D:\driver2\game\C\DR2ROADS.C (line 400)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
struct _sdPlane * /*$ra*/ sdGetCell(struct VECTOR *pos /*$s3*/)
{ // line 1, address 0x134d4
	char *buffer; // $s1
	short *surface; // $s0
	int nextLevel; // $s2
	struct _sdPlane *plane; // $a1
	struct XYPAIR cell; // stack address -40
	struct XYPAIR cellPos; // stack address -32
	{ // line 41, address 0x135c4
		int y; // $a0
	} // line 56, address 0x13620
	{ // line 63, address 0x13634
		short *BSPsurface; // $a0
	} // line 81, address 0x1369c
} // line 102, address 0x13728
/*
 * Offset 0x13728
 * D:\driver2\game\C\DR2ROADS.C (line 64)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ProcessStraightsDriver2Lump(char *lump_file /*$s0*/, int lump_size /*$a1*/)
{ // line 1, address 0x13728
} // line 5, address 0x1375c
/*
 * Offset 0x1375C
 * D:\driver2\game\C\DR2ROADS.C (line 80)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ProcessCurvesDriver2Lump(char *lump_file /*$s0*/, int lump_size /*$a1*/)
{ // line 1, address 0x1375c
} // line 5, address 0x13790
/*
 * Offset 0x13790
 * D:\driver2\game\C\DR2ROADS.C (line 94)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ProcessJunctionsDriver2Lump(char *lump_file /*$s1*/, int lump_size /*$a1*/, int fix /*$s0*/)
{ // line 1, address 0x13790
	{ // line 8, address 0x137c4
		int loop; // $v1
		struct OLD_DRIVER2_JUNCTION *old; // $a1
		struct DRIVER2_JUNCTION *p; // $a0
		{ // line 13, address 0x137e0
			int i; // $a1
		} // line 19, address 0x1380c
	} // line 20, address 0x13820
} // line 21, address 0x13834
/*
 * Offset 0x13834
 * D:\driver2\game\C\DR2ROADS.C (line 146)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ MapHeight(struct VECTOR *pos /*$s0*/)
{ // line 1, address 0x13834
	int height; // $v0
	struct _sdPlane *plane; // $v0
} // line 16, address 0x13874
/*
 * Offset 0x13874
 * D:\driver2\game\C\DR2ROADS.C (line 250)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ GetSurfaceIndex(struct VECTOR *pos /*$a0*/)
{ // line 2, address 0x13874
	struct _sdPlane *plane; // $v0
} // line 10, address 0x138b0
/*
 * Offset 0x138B0
 * D:\driver2\game\C\DR2ROADS.C (line 505)
 * Stack frame base $sp, length 0
 */
short * /*$ra*/ sdGetBSP(struct _sdNode *node /*$a3*/, struct XYPAIR *pos /*$a1*/)
{ // line 1, address 0x138b0
	{ // line 4, address 0x138d8
		int dot; // $a0
	} // line 17, address 0x1393c
} // line 19, address 0x13958


/*
 * Offset 0x13958
 * D:\driver2\game\C\DR2ROADS.C (line 266)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
struct _sdPlane * /*$ra*/ FindRoadInBSP(struct _sdNode *node /*$s0*/, struct _sdPlane *base /*$s1*/)
{ // line 2, address 0x13970
	struct _sdPlane *plane; // $v0
} // line 27, address 0x139e8