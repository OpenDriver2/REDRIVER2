
#include "../decomp_defs.h"

SVECTOR targetArrowVerts[43] =
{
  { 65491, 65266, 0, 0 },
  { 45, 65266, 0, 0 },
  { 45, 65446, 0, 0 },
  { 90, 65446, 0, 0 },
  { 0, 0, 0, 0 },
  { 65446, 65446, 0, 0 },
  { 65491, 65446, 0, 0 },
  { 65440, 64768, 0, 0 },
  { 96, 64768, 0, 0 },
  { 96, 65320, 0, 0 },
  { 65440, 65320, 0, 0 },
  { 88, 65476, 0, 0 },
  { 36, 65528, 0, 0 },
  { 65500, 65528, 0, 0 },
  { 65448, 65476, 0, 0 },
  { 65448, 65404, 0, 0 },
  { 65500, 65352, 0, 0 },
  { 36, 65352, 0, 0 },
  { 88, 65404, 0, 0 },
  { 177, 65417, 0, 0 },
  { 73, 65521, 0, 0 },
  { 65463, 65521, 0, 0 },
  { 65359, 65417, 0, 0 },
  { 65359, 65271, 0, 0 },
  { 65463, 65167, 0, 0 },
  { 73, 65167, 0, 0 },
  { 177, 65271, 0, 0 },
  { 65488, 65152, 0, 0 },
  { 65488, 65104, 0, 0 },
  { 65440, 65104, 0, 0 },
  { 65440, 65056, 0, 0 },
  { 96, 65056, 0, 0 },
  { 96, 65104, 0, 0 },
  { 48, 65104, 0, 0 },
  { 48, 65152, 0, 0 },
  { 221, 65387, 0, 0 },
  { 91, 65517, 0, 0 },
  { 65445, 65517, 0, 0 },
  { 65315, 65387, 0, 0 },
  { 65315, 65205, 0, 0 },
  { 65445, 65075, 0, 0 },
  { 91, 65075, 0, 0 },
  { 221, 65205, 0, 0 }
};

char normalTargetArrowTris[] = { 0, 1, 2, 0, 2, 6, 5, 3, 4 };

char loseTailTargetArrowTris[] = { 7, 8, 9, 7, 9, 0xA, 0xB, 0xC, 0xD, 0xB, 0xD, 0xE };

char windowTargetArrowTris[] = { 
	0x13, 0x14, 0x15, 0x13, 0x15, 0x16, 0x1A, 0x13, 0x16,
	0x1A, 0x16, 0x17, 0x19, 0x1A, 0x17, 0x19, 0x17, 0x18,
	0x1B, 0x1C, 0x22, 0x1C, 0x21, 0x22, 0x1D, 0x1E, 0x1F,
	0x1D, 0x1F, 0x20 
};

char maxSpeedTargetArrowTris[] = {
	0x23, 0x24, 0x25, 0x23, 0x25, 0x26, 0x2A, 0x23, 0x26,
	0x2A, 0x26, 0x27, 0x29, 0x2A, 0x27, 0x29, 0x27, 0x28 
};

TARGET_ARROW_MODEL targetArrowModel[4] =
{
  { &targetArrowVerts, &normalTargetArrowTris, sizeof(normalTargetArrowTris) / 3 },
  { &targetArrowVerts, &loseTailTargetArrowTris, sizeof(loseTailTargetArrowTris) / 3 },
  { &targetArrowVerts, &windowTargetArrowTris, sizeof(windowTargetArrowTris) / 3 },
  { &targetArrowVerts, &maxSpeedTargetArrowTris, sizeof(maxSpeedTargetArrowTris) / 3 }
};


/*
 * Offset 0x7FBAC
 * D:\driver2\game\C\TARGETS.C (line 213)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ Draw3DTarget(struct VECTOR *position /*$s0*/, int flags /*$s2*/)
{ // line 1, address 0x7fbac
	struct VECTOR pos; // stack address -32
	int shadow; // $s1
} // line 49, address 0x7fdb0
/*
 * Offset 0x7FDB0
 * D:\driver2\game\C\TARGETS.C (line 267)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawTargetArrowModel(struct TARGET_ARROW_MODEL *pTargetArrowModel /*$s1*/, struct VECTOR *pPosition /*$s2*/, int shadow /*$s4*/, int invert /*$s3*/)
{ // line 1, address 0x7fdb0
	{ // line 4, address 0x7fe04
		struct VECTOR tempVec; // stack address -56
		struct SVECTOR *pVerts; // $s0
		struct SVECTOR temp; // stack address -40
		char *pVertIndex; // $a3
		{ // line 16, address 0x7fe94
			struct POLY_F3 *poly; // $t0
			int z; // stack address -32
		} // line 56, address 0x800ac
	} // line 62, address 0x80140
} // line 63, address 0x80160
/*
 * Offset 0x80160
 * D:\driver2\game\C\TARGETS.C (line 412)
 * Stack frame base $sp, length 144
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawStopZone(struct VECTOR *pPosition /*$s5*/)
{ // line 1, address 0x80160
	struct VECTOR *pVector; // $s0
	struct VECTOR pStopZonePt[4]; // stack address -128
	struct POLY_FT4 *pPoly; // $s1
	long *pOut; // $s2
	long sz; // stack address -48
	{ // line 18, address 0x80264
		struct SVECTOR temp; // stack address -64
		long p; // stack address -56
		long flag; // stack address -52
	} // line 53, address 0x80374
} // line 77, address 0x804e4
/*
 * Offset 0x804E4
 * D:\driver2\game\C\TARGETS.C (line 496)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ WorldToCameraPositions(struct VECTOR *pGlobalPositionIn /*$s1*/, struct VECTOR *pCameraPositionOut /*$s0*/, int count /*$s2*/)
{ // line 1, address 0x804e4
	{ // line 4, address 0x80520
		struct VECTOR temp; // stack address -48
	} // line 6, address 0x80520
} // line 15, address 0x80590