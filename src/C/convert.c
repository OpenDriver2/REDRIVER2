#include "../decomp_defs.h"


/*
 * Offset 0x2D36C
 * D:\driver2\game\C\CONVERT.C (line 272)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ BuildWorldMatrix()
{ // line 2, address 0x2d36c
	struct MATRIX newmatrix; // stack address -48
} // line 17, address 0x2d460
/*
 * Offset 0x2D460
 * D:\driver2\game\C\CONVERT.C (line 149)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ Calc_Object_MatrixYZX(struct MATRIX *mat /*$s0*/, struct SVECTOR *angles /*$s1*/)
{
}
/*
 * Offset 0x2D4D8
 * D:\driver2\game\C\CONVERT.C (line 182)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ _RotMatrixX(struct MATRIX *m /*$v0*/, short ang /*$a1*/)
{
}
/*
 * Offset 0x2D504
 * D:\driver2\game\C\CONVERT.C (line 187)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ _RotMatrixY(struct MATRIX *m /*$v0*/, short ang /*$a1*/)
{
}
/*
 * Offset 0x2D530
 * D:\driver2\game\C\CONVERT.C (line 192)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ _RotMatrixZ(struct MATRIX *m /*$v0*/, short ang /*$a1*/)
{
}
/*
 * Offset 0x2D55C
 * D:\driver2\game\C\CONVERT.C (line 199)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ RotMatrixXYZ(struct MATRIX *m /*$v0*/, struct SVECTOR *r /*$a1*/)
{
}
/*
 * Offset 0x2D584
 * D:\driver2\game\C\CONVERT.C (line 205)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ _MatrixRotate(struct VECTOR *pos /*$s0*/)
{ // line 1, address 0x2d584
	struct VECTOR temp; // stack address -24
} // line 9, address 0x2d5c4
/*
 * Offset 0x2D5C4
 * D:\driver2\game\C\CONVERT.C (line 240)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InvertMatrix(struct MATRIX *a /*$a0*/, struct MATRIX *b /*$a1*/)
{
}
/*
 * Offset 0x2D630
 * D:\driver2\game\C\CONVERT.C (line 334)
 * Stack frame base $sp, length 176
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ScaleCamera()
{ // line 2, address 0x2d630
	struct MATRIX temp; // stack address -160
	struct MATRIX temp2; // stack address -128
	struct MATRIX scale; // stack address -96
	struct MATRIX scaledcammat; // stack address -64
	struct VECTOR pos; // stack address -32
	struct SVECTOR tempang; // stack address -16
} // line 27, address 0x2d6e0
/*
 * Offset 0x2D6E0
 * D:\driver2\game\C\CONVERT.C (line 365)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ Getlong(char *dest /*$a0*/, char *source /*$a1*/)
{
}
/*
 * Offset 0x2D710
 * D:\driver2\game\C\CONVERT.C (line 387)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ RandomInit(long i1 /*$a0*/, long i2 /*$a1*/)
{ // line 2, address 0x2d710
	int count; // $s0
} // line 15, address 0x2d78c
/*
 * Offset 0x2D78C
 * D:\driver2\game\C\CONVERT.C (line 414)
 * Stack frame base $sp, length 0
 */
long /*$ra*/ Random2(int step /*$a0*/)
{ // line 2, address 0x2d78c
	unsigned int seed; // $a0
} // line 6, address 0x2d7f4