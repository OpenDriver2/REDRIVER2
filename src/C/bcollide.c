#include "../decomp_defs.h"

/*
 * Offset 0x1C584
 * D:\driver2\game\C\BCOLLIDE.C (line 120)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 fp
 */
int /*$ra*/ bcollided2d(struct CDATA2D *body /*$t4*/, int needOverlap /*$fp*/)
{ // line 1, address 0x1c584
	struct VECTOR delta; // stack address -56
	int dtheta; // $v1
	int ac; // $s6
	int as; // $s5
	int i; // $t7
	int j; // $a2
	int k; // $t5
	{ // line 40, address 0x1c7a0
		int xover; // $t0
		int zover; // $a0
		int tmp2; // $a2
		int FE; // $a3
	} // line 63, address 0x1c8f8
} // line 65, address 0x1c928
/*
 * Offset 0x1C928
 * D:\driver2\game\C\BCOLLIDE.C (line 195)
 * Stack frame base $sp, length 8
 * Saved registers at address -4: s0 s1
 */
void /*$ra*/ bFindCollisionPoint(struct CDATA2D *body /*$t6*/, struct CRET2D *collisionResult /*$s0*/)
{ // line 1, address 0x1c928
	int carBarrierCollision; // $s1
	int i; // $a3
	int j; // $v1
	int k; // $t0
	int smallest; // $t4
	int besti; // $t5
	int bestk; // $t7
	int sign; // $t3
	int sign0; // $t0
	int sign1; // $a3
	{ // line 17, address 0x1c9cc
		int upper; // $a1
		int lower; // $v1
	} // line 33, address 0x1ca24
	{ // line 40, address 0x1ca58
		int upper; // $a1
		int lower; // $a0
	} // line 54, address 0x1cac8
} // line 78, address 0x1cc98
/*
 * Offset 0x1CC98
 * D:\driver2\game\C\BCOLLIDE.C (line 275)
 * Stack frame base $sp, length 264
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ bFindCollisionTime(struct CDATA2D *cd /*$s5*/, struct CRET2D *collisionResult /*stack 4*/)
{ // line 1, address 0x1cc98
	int i; // $s4
	int q; // $s0
	int hit; // $t2
	int neverfree; // $fp
	int time; // $s1
	int step; // $s3
	struct CDATA2D original[2]; // stack address -248
} // line 82, address 0x1cf54
/*
 * Offset 0x1CF54
 * D:\driver2\game\C\BCOLLIDE.C (line 384)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ApplyDamage(struct _CAR_DATA *cp /*$a0*/, char region /*$a1*/, int value /*$a2*/, char fakeDamage /*$a3*/)
{ // line 1, address 0x1cf54
	short *pRegion; // $t0
} // line 81, address 0x1d118
/*
 * Offset 0x1D118
 * D:\driver2\game\C\BCOLLIDE.C (line 470)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ DamageCar3D(struct _CAR_DATA *cp /*$s1*/, long *delta[4] /*$t4*/, int strikeVel /*$t6*/, struct _CAR_DATA *pOtherCar /*$s2*/)
{ // line 1, address 0x1d118
	int l; // $v1
	int w; // $v0
	int region; // $a1
	long nose[4]; // stack address -56
	long door[4]; // stack address -40
	int impact; // $s3
	int QQQ; // $t7
	{ // line 79, address 0x1d3f0
		char fakeDamage; // $a3
		char player_id; // $s0
		char kludge; // $a3
	} // line 98, address 0x1d48c
} // line 102, address 0x1d4bc
/*
 * Offset 0x1D4BC
 * D:\driver2\game\C\BCOLLIDE.C (line 587)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DamageCar(struct _CAR_DATA *cp /*$s2*/, struct CDATA2D *cd /*$s1*/, struct CRET2D *collisionResult /*$s3*/, int strikeVel /*$s0*/)
{ // line 1, address 0x1d4bc
	struct VECTOR delta; // stack address -48
	int l; // $v1
	int w; // $v0
	int region; // $a1
	int damage; // $a2
	char player_id; // $s5
	int impact; // $s4
	int QQQ; // $t0
} // line 46, address 0x1d6d0
/*
 * Offset 0x1D6F4
 * D:\driver2\game\C\BCOLLIDE.C (line 839)
 * Stack frame base $sp, length 200
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CarBuildingCollision(struct _CAR_DATA *cp /*$s3*/, struct BUILDING_BOX *building /*$s2*/, struct CELL_OBJECT *cop /*$s6*/, int mightBeABarrier /*$s1*/)
{ // line 1, address 0x1d6f4
	static struct CDATA2D cd[2]; // address 0x0
	static struct CRET2D collisionResult; // address 0xd0
	int debris_colour; // stack address -48
	struct VECTOR tempwhere; // stack address -168
	struct MODEL *pModel; // $s5
	int player_id; // stack address -44
	{ // line 27, address 0x1d7fc
		struct SVECTOR boxDisp; // stack address -152
		{ // line 69, address 0x1d95c
			int wbod; // $a1
		} // line 79, address 0x1da0c
	} // line 81, address 0x1da0c
	{ // line 138, address 0x1dacc
		{ // line 138, address 0x1dacc
			struct VECTOR velocity; // stack address -144
			long pointVel[4]; // stack address -128
			long reaction[4]; // stack address -112
			long lever[4]; // stack address -96
			int strikeVel; // $s1
			{ // line 175, address 0x1dcc0
				short scale; // $a2
			} // line 195, address 0x1dd0c
			{ // line 211, address 0x1dd6c
				{ // line 219, address 0x1dd90
					struct SMASHABLE_OBJECT *sip; // $a1
					struct SMASHABLE_OBJECT *match; // $s0
					int chan; // $s1
					int adjust; // $s2
				} // line 240, address 0x1dea4
			} // line 254, address 0x1df2c
			{ // line 259, address 0x1df5c
				struct VECTOR LeafPosition; // stack address -80
			} // line 259, address 0x1df5c
			{ // line 277, address 0x1dfb8
				{ // line 280, address 0x1dff8
					struct VECTOR lamp_velocity; // stack address -64
				} // line 284, address 0x1e02c
			} // line 285, address 0x1e02c
			{ // line 304, address 0x1e0c0
				int twistY; // $a1
				int lever_dot_n; // $a0
				int displacementsquared; // $v1
				int denom; // $v1
			} // line 316, address 0x1e1d8
		} // line 345, address 0x1e3e4
	} // line 349, address 0x1e3ec
} // line 356, address 0x1e450