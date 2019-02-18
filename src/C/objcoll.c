
#include "../decomp_defs.h"

/*
 * Offset 0x69C0C
 * D:\driver2\game\C\OBJCOLL.C (line 63)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
char /*$ra*/ CellEmpty(struct VECTOR *pPosition /*$s1*/, int radius /*$s2*/)
{ // line 1, address 0x69c0c
	struct CELL_ITERATOR ci; // stack address -48
	int cell_x; // $a0
	struct CELL_OBJECT *pCellObject; // $a2
	struct MODEL *pModel; // $a3
	{ // line 37, address 0x69cc8
		int sphere_sq; // $v0
		int xd; // $t5
		int zd; // $t4
		{ // line 51, address 0x69d2c
			int box_loop; // $t3
			int num_cb; // $t6
			struct COLLISION_PACKET *collide; // $t0
			{ // line 56, address 0x69d50
				unsigned int zs; // $t2
				unsigned int xs; // $t1
				int cs; // $a2
				int sn; // $a0
			} // line 75, address 0x69e30
		} // line 76, address 0x69e40
	} // line 78, address 0x69e40
} // line 90, address 0x69e84
/*
 * Offset 0x69E84
 * D:\driver2\game\C\OBJCOLL.C (line 217)
 * Stack frame base $sp, length 24
 */
int /*$ra*/ RaySlabsIntersection(struct tRay *ray /*$t5*/, struct tAABB *bbox /*$t4*/)
{ // line 1, address 0x69e84
	int i; // $t1
	struct tRange inside; // stack address -24
	{ // line 9, address 0x69ea8
		struct tRange cabbage; // stack address -16
		struct tRange scaledCabbage; // stack address -8
		int dir; // $a2
	} // line 36, address 0x69ffc
} // line 38, address 0x6a01c
/*
 * Offset 0x6A01C
 * D:\driver2\game\C\OBJCOLL.C (line 259)
 * Stack frame base $sp, length 200
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
char /*$ra*/ lineClear(struct VECTOR *v1 /*stack 0*/, struct VECTOR *v2 /*stack 4*/)
{ // line 1, address 0x6a01c
	int we; // stack address -56
	int ocx; // $t2
	int ocz; // $t3
	struct VECTOR pos; // stack address -184
	struct VECTOR va; // stack address -168
	struct VECTOR vb; // stack address -152
	{ // line 20, address 0x6a0dc
		int cell_x; // $fp
		int cell_z; // $s7
		struct CELL_ITERATOR ci; // stack address -136
		struct CELL_OBJECT *pCellObject; // $s4
		{ // line 40, address 0x6a19c
			struct MODEL *pModel; // $a1
			{ // line 48, address 0x6a1d8
				int sphere_sq; // $v0
				int xd; // $a0
				int zd; // $v1
				{ // line 59, address 0x6a23c
					int box_loop; // $s5
					int num_cb; // $s6
					struct COLLISION_PACKET *collide; // $s3
					{ // line 64, address 0x6a258
						struct MATRIX *mat; // $a0
						int cx; // $v1
						int cy; // $a2
						int cz; // $v0
						int cs; // $t1
						int sn; // $t5
						{ // line 64, address 0x6a258
							struct tRay ray; // stack address -112
							struct tAABB box; // stack address -80
						} // line 88, address 0x6a47c
					} // line 89, address 0x6a47c
				} // line 90, address 0x6a48c
			} // line 92, address 0x6a48c
		} // line 93, address 0x6a48c
	} // line 96, address 0x6a4ac
} // line 101, address 0x6a500
/*
 * Offset 0x6A500
 * D:\driver2\game\C\OBJCOLL.C (line 391)
 * Stack frame base $sp, length 88
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ CollisionCopList(struct XZPAIR *pos /*$a0*/, int *count /*$s0*/)
{ // line 1, address 0x6a500
	static struct XZPAIR initial; // address 0x0
	{ // line 11, address 0x6a550
		struct XZPAIR cell; // stack address -72
		int i; // $a0
		int j; // $t1
		{ // line 20, address 0x6a570
			struct CELL_ITERATOR ci; // stack address -64
			struct XZPAIR cbr; // stack address -40
			int barrelRegion; // $v0
			struct CELL_OBJECT *cop; // $a0
		} // line 38, address 0x6a660
	} // line 40, address 0x6a690
} // line 41, address 0x6a6b4
/*
 * Offset 0x6A6B4
 * D:\driver2\game\C\OBJCOLL.C (line 439)
 * Stack frame base $sp, length 168
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CheckScenaryCollisions(struct _CAR_DATA *cp /*$s7*/)
{ // line 1, address 0x6a6b4
	struct MODEL *model; // stack address -76
	struct CELL_OBJECT *cop; // $s5
	struct VECTOR player_pos; // stack address -152
	struct COLLISION_PACKET *collide; // $s1
	int cell_x; // $a0
	int xd; // $v1
	int zd; // $a0
	int num_cb; // stack address -72
	int box_loop; // $s6
	int sphere_sq; // $v0
	int x1; // stack address -68
	struct BUILDING_BOX bbox; // stack address -136
	int mdcount; // stack address -80
	int coll_test_count; // $t0
	struct XZPAIR box; // stack address -104
	int lbody; // stack address -64
	int extraDist; // stack address -60
	{ // line 80, address 0x6a99c
		struct BUILDING_BOX *pbox; // $s4
		struct MATRIX *mat; // $a1
		struct VECTOR address; // stack address -96
	} // line 152, address 0x6adb0
} // line 158, address 0x6adf4
/*
 * Offset 0x6AE24
 * D:\driver2\game\C\OBJCOLL.C (line 609)
 * Stack frame base $sp, length 128
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ QuickBuildingCollisionCheck(struct VECTOR *pPos /*$s5*/, int dir /*stack 4*/, int l /*stack 8*/, int w /*$fp*/, int extra /*stack 16*/)
{ // line 1, address 0x6ae24
	struct MODEL *model; // $a1
	struct CELL_OBJECT *cop; // $s3
	struct VECTOR player_pos; // stack address -112
	struct COLLISION_PACKET *collide; // $s0
	int cell_x; // $a0
	int xd; // $v1
	int zd; // $a0
	int num_cb; // $s7
	int box_loop; // $s4
	int sphere_sq; // $v0
	int x1; // $s6
	struct BUILDING_BOX bbox; // stack address -96
	int mdcount; // stack address -48
	{ // line 60, address 0x6b00c
		struct BUILDING_BOX *pbox; // $s1
		struct MATRIX *mat; // $a1
		struct VECTOR address; // stack address -64
		{ // line 76, address 0x6b158
		} // line 103, address 0x6b224
	} // line 105, address 0x6b224
} // line 112, address 0x6b288
/*
 * Offset 0x6B288
 * D:\driver2\game\C\OBJCOLL.C (line 735)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ DoScenaryCollisions()
{ // line 2, address 0x6b288
	struct _CAR_DATA *lcp; // $s0
} // line 18, address 0x6b354
/*
 * Offset 0x6B354
 * D:\driver2\game\C\OBJCOLL.C (line 155)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GlobalPositionToCellNumber(struct VECTOR *pPosition /*$a0*/)
{ // line 1, address 0x6b354
	int cellX; // $a3
	int cellZ; // $a1
	int cbrX; // $t1
	int cbrZ; // $t0
	int cbr; // $t2
	int xOff; // $a3
	int yOff; // $a0
} // line 20, address 0x6b44c
/*
 * Offset 0x6B44C
 * D:\driver2\game\C\OBJCOLL.C (line 183)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
char /*$ra*/ CellAtPositionEmpty(struct VECTOR *pPosition /*$s0*/, int radius /*$s1*/)
{ // line 1, address 0x6b44c
} // line 22, address 0x6b498
/*
 * Offset 0x6B498
 * D:\driver2\game\C\OBJCOLL.C (line 377)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetCopListCell(int x /*$a0*/, int z /*$a1*/)
{ // line 2, address 0x6b498
	struct XZPAIR cell; // stack address -16
} // line 7, address 0x6b4c4
/*
 * Offset 0x6B4C4
 * D:\driver2\game\C\OBJCOLL.C (line 386)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ BuildCollisionCopList(int *count /*$a1*/)
{
}