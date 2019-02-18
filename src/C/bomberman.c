#include "../decomp_defs.h"

/*
 * Offset 0x1E450
 * D:\driver2\game\C\BOMBERMAN.C (line 245)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ HandleThrownBombs()
{ // line 2, address 0x1e450
	struct BOMB *bomb; // $s1
	struct VECTOR velocity; // stack address -48
	struct _CAR_DATA *cp; // $s0
	int i; // $s5
	int y; // $a0
	{ // line 13, address 0x1e494
	} // line 56, address 0x1e630
	{ // line 74, address 0x1e6d8
		int len; // $v1
	} // line 85, address 0x1e750
} // line 112, address 0x1e850
/*
 * Offset 0x1E878
 * D:\driver2\game\C\BOMBERMAN.C (line 381)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DrawThrownBombs()
{ // line 2, address 0x1e878
	struct MATRIX object_matrix; // stack address -80
	struct MATRIX *finalmatrix; // $s2
	struct BOMB *bomb; // $s0
	struct VECTOR pos; // stack address -48
	int i; // $s3
	{ // line 16, address 0x1e8d4
	} // line 33, address 0x1ea00
	{ // line 39, address 0x1ea1c
	} // line 43, address 0x1ea44
} // line 44, address 0x1ea44
/*
 * Offset 0x1EA68
 * D:\driver2\game\C\BOMBERMAN.C (line 432)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ BombThePlayerToHellAndBack(int car /*$s3*/)
{ // line 1, address 0x1ea68
	struct BOMB *bomb; // $t3
} // line 54, address 0x1eca4
/*
 * Offset 0x1ECC0
 * D:\driver2\game\C\BOMBERMAN.C (line 496)
 * Stack frame base $sp, length 232
 * Saved registers at address -8: ra
 */
int /*$ra*/ BombCollisionCheck(struct _CAR_DATA *cp /*$a0*/, struct VECTOR *pPos /*$a1*/)
{ // line 1, address 0x1ecc0
	struct CDATA2D cd[2]; // stack address -216
	int carLength[2]; // stack address -16
	{ // line 1, address 0x1ecc0
	} // line 1, address 0x1ecc0
} // line 27, address 0x1ed80
/*
 * Offset 0x1ED80
 * D:\driver2\game\C\BOMBERMAN.C (line 534)
 * Stack frame base $sp, length 368
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ ExplosionCollisionCheck(struct _CAR_DATA *cp /*$s1*/, struct _ExOBJECT *pE /*$s3*/)
{ // line 1, address 0x1ed80
	struct CDATA2D cd[2]; // stack address -352
	int carLength[2]; // stack address -152
	static int setUsed; // address 0x28
	int tanner; // $s6
	{ // line 12, address 0x1eddc
		{ // line 12, address 0x1eddc
		} // line 12, address 0x1eddc
		{ // line 19, address 0x1ee74
		} // line 24, address 0x1eee8
		{ // line 27, address 0x1eee8
			int x; // $a1
			int z; // $v1
			struct VECTOR *pos; // $v0
		} // line 66, address 0x1efbc
		{ // line 89, address 0x1effc
			struct CRET2D collisionResult; // stack address -144
			{ // line 92, address 0x1effc
				struct VECTOR velocity; // stack address -104
				long pointVel[4]; // stack address -88
				long reaction[4]; // stack address -72
				long lever[4]; // stack address -56
				int strikeVel; // $s0
				{ // line 154, address 0x1f278
				} // line 161, address 0x1f2b8
				{ // line 164, address 0x1f2b8
					int twistY; // $a1
					int lever_dot_n; // $a0
					int displacementsquared; // $v1
					int denom; // $v1
				} // line 176, address 0x1f3c8
			} // line 198, address 0x1f510
		} // line 199, address 0x1f510
	} // line 200, address 0x1f510
} // line 206, address 0x1f55c
/*
 * Offset 0x1F55C
 * D:\driver2\game\C\BOMBERMAN.C (line 747)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ AddFlash(struct VECTOR *pos /*$a0*/)
{ // line 1, address 0x1f55c
	int dist; // $a0
} // line 14, address 0x1f5d8
/*
 * Offset 0x1F5D8
 * D:\driver2\game\C\BOMBERMAN.C (line 222)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitThrownBombs()
{ // line 2, address 0x1f5d8
	int i; // $v1
} // line 13, address 0x1f65c