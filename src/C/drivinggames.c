#include "../decomp_defs.h"


/*
 * Offset 0x43174
 * D:\driver2\game\C\DRIVINGGAMES.C (line 231)
 * Stack frame base $sp, length 88
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitDrivingGames()
{ // line 2, address 0x43174
	char filename[64]; // stack address -72
	int i; // $a0
	int j; // $v1
} // line 57, address 0x432d4
/*
 * Offset 0x432D4
 * D:\driver2\game\C\DRIVINGGAMES.C (line 290)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ HandleDrivingGames()
{ // line 2, address 0x432d4
	struct _CAR_DATA *cp; // $a2
	struct VECTOR vel; // stack address -96
	int i; // $s3
	int j; // $v1
	int k; // $a0
	int id; // $s2
	int dist; // $a1
	{ // line 61, address 0x433bc
		struct VECTOR pos1; // stack address -80
		struct VECTOR pos2; // stack address -64
		int x; // $t0
		int z; // $a1
		int r; // $v0
		int side; // $s1
		int radius; // $a0
	} // line 123, address 0x436c0
	{ // line 145, address 0x43768
		struct VECTOR pos; // stack address -80
	} // line 166, address 0x43868
} // line 185, address 0x43944
/*
 * Offset 0x43944
 * D:\driver2\game\C\DRIVINGGAMES.C (line 477)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DrawDrivingGames()
{ // line 2, address 0x43944
	struct VECTOR wpos; // stack address -24
	int i; // $s0
} // line 49, address 0x43a64
/*
 * Offset 0x43A64
 * D:\driver2\game\C\DRIVINGGAMES.C (line 545)
 * Stack frame base $sp, length 232
 * Saved registers at address -8: ra
 */
int /*$ra*/ CarConeCollision(struct VECTOR *pPos /*$a0*/, int car /*$a1*/)
{ // line 1, address 0x43a64
	struct CDATA2D cd[2]; // stack address -216
	struct _CAR_DATA *cp1; // $t0
	int carLength[2]; // stack address -16
	{ // line 20, address 0x43b3c
	} // line 20, address 0x43b3c
} // line 21, address 0x43b50
/*
 * Offset 0x43B50
 * D:\driver2\game\C\DRIVINGGAMES.C (line 578)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ SetSmashedCone(int cone /*$s1*/, struct VECTOR *velocity /*$a1*/, int player /*$s2*/, int side /*$a3*/)
{ // line 1, address 0x43b50
	struct SMASHED_CONE *sc; // $s0
	int chan; // $s0
} // line 43, address 0x43d48
/*
 * Offset 0x43D48
 * D:\driver2\game\C\DRIVINGGAMES.C (line 628)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MoveSmashedCones()
{ // line 2, address 0x43d48
	int i; // $t0
} // line 27, address 0x43e4c
/*
 * Offset 0x43E54
 * D:\driver2\game\C\DRIVINGGAMES.C (line 730)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ DrawSmashedCone(struct SMASHED_CONE *sc /*$s0*/, struct VECTOR *wpos /*$s1*/)
{ // line 1, address 0x43e54
	struct MATRIX object_matrix; // stack address -64
	struct MATRIX *finalmatrix; // $s2
	struct VECTOR pos; // stack address -32
} // line 20, address 0x43f9c
/*
 * Offset 0x43F9C
 * D:\driver2\game\C\DRIVINGGAMES.C (line 757)
 * Stack frame base $sp, length 16
 */
void /*$ra*/ GetConePos(int cone /*$a0*/, struct VECTOR *pos /*$t2*/, int side /*$a2*/)
{ // line 1, address 0x43f9c
	struct VECTOR address; // stack address -16
	int x; // $t3
	int z; // $t4
	int r; // $v1
	int radius; // $a1
} // line 35, address 0x4409c
/*
 * Offset 0x4409C
 * D:\driver2\game\C\DRIVINGGAMES.C (line 703)
 * Stack frame base $sp, length 88
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ DrawCone(struct VECTOR *position /*$s0*/, int cone /*$s1*/)
{ // line 1, address 0x4409c
	struct MATRIX matrix; // stack address -64
	struct VECTOR pos; // stack address -32
	{ // line 10, address 0x440cc
		{ // line 12, address 0x440ec
		} // line 18, address 0x441bc
	} // line 19, address 0x441bc
} // line 20, address 0x441bc
/*
 * Offset 0x441D0
 * D:\driver2\game\C\DRIVINGGAMES.C (line 662)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawSmashedCones()
{ // line 2, address 0x441d0
	struct SMASHED_CONE *sc; // $s0
	struct VECTOR wpos; // stack address -40
	int i; // $s1
} // line 34, address 0x44290