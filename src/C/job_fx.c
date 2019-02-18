
#include "../decomp_defs.h"

MATRIX SS = {0};

/*
 * Offset 0x56DBC
 * D:\driver2\game\C\JOB_FX.C (line 129)
 * Stack frame base $sp, length 8
 * Saved registers at address -8: s0
 */
void /*$ra*/ AddExplosion(struct VECTOR pos /*stack 0*/, int type /*stack 16*/)
{ // line 1, address 0x56dbc
	int i; // $t1
} // line 40, address 0x56eac
/*
 * Offset 0x56EAC
 * D:\driver2\game\C\JOB_FX.C (line 178)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ HandleExplosion()
{ // line 2, address 0x56eac
	int i; // $s5
	struct _CAR_DATA *cp; // $s0
	{ // line 34, address 0x56fb4
	} // line 42, address 0x56fec
} // line 45, address 0x56ffc
/*
 * Offset 0x57028
 * D:\driver2\game\C\JOB_FX.C (line 557)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ initExplosion()
{ // line 2, address 0x57028
	int i; // $t0
} // line 25, address 0x57310
/*
 * Offset 0x57310
 * D:\driver2\game\C\JOB_FX.C (line 588)
 * Stack frame base $sp, length 152
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawExplosion(int time /*stack 0*/, struct VECTOR position /*stack 4*/, int hscale /*stack 20*/, int rscale /*stack 24*/)
{ // line 1, address 0x57310
	int i; // $t1
	int j; // $s3
	struct POLY_FT4 *poly; // $a2
	struct SVECTOR *src; // $t0
	struct VECTOR v; // stack address -136
	int rgb; // $s0
	int z; // stack address -56
	int sf1; // $t0
	int sf2; // $a0
	unsigned long u0; // $s2
	unsigned long u1; // $s1
	unsigned long u2; // $s5
	unsigned long u3; // $s4
	{ // line 1, address 0x57310
		int transparency; // $t2
		int green; // $t1
		int blue; // $v1
	} // line 1, address 0x57310
	{ // line 43, address 0x57458
		struct MATRIX workmatrix; // stack address -120
		int sf; // $v0
		int s; // $v1
		int c; // $a3
	} // line 50, address 0x574ac
	{ // line 97, address 0x57788
		int transparency; // $a0
		int red; // $a1
		int green; // $a2
		int blue; // $v1
	} // line 97, address 0x57788
	{ // line 110, address 0x5780c
		struct MATRIX workmatrix; // stack address -88
		int sf; // $v0
		int s; // $v1
		int c; // $a3
	} // line 119, address 0x57860
} // line 167, address 0x57b74
/*
 * Offset 0x57B74
 * D:\driver2\game\C\JOB_FX.C (line 110)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitExObjects()
{ // line 2, address 0x57b74
	int i; // $v1
} // line 11, address 0x57bb8
/*
 * Offset 0x57BB8
 * D:\driver2\game\C\JOB_FX.C (line 232)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawAllExplosions()
{ // line 2, address 0x57bb8
	int i; // $s1
	{ // line 8, address 0x57bfc
		int hscale; // $v1
		int rscale; // $a0
	} // line 12, address 0x57c28
} // line 14, address 0x57c58
/*
 * Offset 0xE70A0
 * D:\driver2\game\C\LEADAI.C (line 205)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ leadRand()
{
}