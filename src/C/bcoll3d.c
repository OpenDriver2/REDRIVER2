
#include "../decomp_defs.h"

/*
 * Offset 0x1C1C8
 * D:\driver2\game\C\BCOLL3D.C (line 83)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0
 */
void /*$ra*/ PointFaceCheck(struct _CAR_DATA *cp0 /*$t7*/, struct _CAR_DATA *cp1 /*$t8*/, int i /*$t9*/, struct TestResult *least /*$a3*/, int nSign /*stack 16*/)
{ // line 1, address 0x1c1c8
	int k; // $t5
	struct VECTOR normal; // stack address -56
	struct VECTOR diff; // stack address -40
	struct VECTOR point; // stack address -24
	int depth; // $t0
	{ // line 23, address 0x1c2b8
		int partialDepth; // $v1
	} // line 36, address 0x1c354
} // line 47, address 0x1c3e8
/*
 * Offset 0x1C3E8
 * D:\driver2\game\C\BCOLL3D.C (line 153)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ CarCarCollision3(struct _CAR_DATA *c0 /*$a0*/, struct _CAR_DATA *c1 /*$a1*/, int *depth /*$s2*/, struct VECTOR *where /*$s0*/, struct VECTOR *normal /*stack 16*/)
{ // line 1, address 0x1c3e8
	struct TestResult tr; // stack address -56
	int res; // $t1
} // line 12, address 0x1c470
/*
 * Offset 0x1C470
 * D:\driver2\game\C\BCOLL3D.C (line 133)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ collided3d(struct _CAR_DATA *cp0 /*$s3*/, struct _CAR_DATA *cp1 /*$s2*/, struct TestResult *least /*$s1*/)
{ // line 1, address 0x1c470
	int i; // $s0
} // line 18, address 0x1c584