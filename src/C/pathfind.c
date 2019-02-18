
#include "../decomp_defs.h"

/*
 * Offset 0xE7000
 * D:\driver2\game\C\PATHFIND.C (line 314)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 s1
 */
struct tNode /*$ra*/ popNode()
{ // line 1, address 0xe7000
	unsigned int lNumHeapEntries; // $s0
	struct tNode res; // stack address -24
	unsigned short f; // $t8
	unsigned int child; // $a1
	unsigned int here; // $t5
	{ // line 11, address 0xe7058
		unsigned int lastEntry; // $t4
		{ // line 15, address 0xe7070
			int d; // $t3
			int d2; // $t2
			int d3; // $a3
			int d4; // $t1
		} // line 32, address 0xe70b8
	} // line 33, address 0xe7110
	{ // line 35, address 0xe7110
		int d; // $a2
		int d2; // $a3
		int d3; // $t1
		int d4; // $t2
	} // line 44, address 0xe715c
} // line 47, address 0xe715c
/*
 * Offset 0xE7194
 * D:\driver2\game\C\PATHFIND.C (line 426)
 * Stack frame base $sp, length 104
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ WunCell(struct VECTOR *pbase /*$s0*/)
{ // line 1, address 0xe7194
	int i; // $s2
	int j; // $s4
	struct VECTOR v[2]; // stack address -88
	struct VECTOR pos; // stack address -56
	{ // line 14, address 0xe723c
		{ // line 14, address 0xe723c
			int z; // $a1
			int x; // $a2
		} // line 20, address 0xe72c8
	} // line 20, address 0xe72c8
} // line 24, address 0xe735c
/*
 * Offset 0xE735C
 * D:\driver2\game\C\PATHFIND.C (line 453)
 * Stack frame base $sp, length 16
 */
void /*$ra*/ InvalidateMap()
{ // line 2, address 0xe735c
	struct VECTOR bPos; // stack address -16
	int count; // $t4
	int dir; // $t1
	int p; // $t2
	int q; // $t3
	{ // line 12, address 0xe73a8
		int tile; // $a0
		int mask; // $a1
		int diff; // $a1
		int i; // $v0
	} // line 15, address 0xe73a8
} // line 34, address 0xe74b0
/*
 * Offset 0xE74B0
 * D:\driver2\game\C\PATHFIND.C (line 495)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ BloodyHell()
{ // line 2, address 0xe74b0
	struct VECTOR bPos; // stack address -48
	int count; // $s4
	int dir; // $s0
	int p; // $s1
	int q; // $s2
	unsigned int howMany; // $s3
	//0x69C raa
	{ // line 22, address 0xe755c
		int tile; // $a0
		int mask; // $a1
		int diff; // $v0
		int i; // $v0
	} // line 42, address 0xe75e4
} // line 70, address 0xe76c4
/*
 * Offset 0xE76C4
 * D:\driver2\game\C\PATHFIND.C (line 567)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: ra
 */
int /*$ra*/ blocked(struct tNode *v1 /*$a3*/, struct tNode *v2 /*$a2*/)
{ // line 1, address 0xe76c4
	struct VECTOR pos; // stack address -24
	int res; // $a0
	{ // line 8, address 0xe76e0
		{ // line 8, address 0xe76e0
			int z; // $a2
			int x; // $v1
		} // line 11, address 0xe774c
	} // line 11, address 0xe774c
	{ // line 18, address 0xe7790
		{ // line 18, address 0xe7790
			int z; // $v1
			int x; // $a0
		} // line 18, address 0xe7790
	} // line 18, address 0xe7790
} // line 23, address 0xe7814
/*
 * Offset 0xE7814
 * D:\driver2\game\C\PATHFIND.C (line 712)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ iterate()
{ // line 2, address 0xe7814
	int dir; // $s2
	struct tNode itHere; // stack address -48
	struct tNode *nbr; // $s4
	{ // line 12, address 0xe7870
		int nearBy; // $v1
		int computed; // $s1
		{ // line 14, address 0xe7870
			int dx; // $v0
			int dz; // $a0
		} // line 15, address 0xe7870
		{ // line 15, address 0xe7870
			{ // line 15, address 0xe7870
				int res; // $a0
			} // line 15, address 0xe7870
		} // line 15, address 0xe7870
	} // line 51, address 0xe797c
	{ // line 56, address 0xe79b4
		int nr; // $a0
		int nl; // $v1
		{ // line 58, address 0xe7a08
			unsigned int a; // $v1
			{ // line 58, address 0xe7a08
				{ // line 1, address 0xe7a44
					unsigned int r; // $v0
				} // line 1, address 0xe7a68
			} // line 1, address 0xe7a68
		} // line 1, address 0xe7a68
		{ // line 61, address 0xe7aac
			struct tNode *pnode; // $s0
			{ // line 61, address 0xe7aac
				unsigned int parent; // $a2
				unsigned int i; // $a3
			} // line 61, address 0xe7b98
		} // line 61, address 0xe7b98
	} // line 62, address 0xe7b98
} // line 64, address 0xe7ba8
/*
 * Offset 0xE7BD0
 * D:\driver2\game\C\PATHFIND.C (line 801)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitPathFinding()
{ // line 2, address 0xe7bd0
	int i; // $a0
	{ // line 1, address 0xe7bd0
	} // line 1, address 0xe7bd0
	{ // line 1, address 0xe7bd0
	} // line 1, address 0xe7bd0
} // line 18, address 0xe7ca8
/*
 * Offset 0xE7CA8
 * D:\driver2\game\C\PATHFIND.C (line 821)
 * Stack frame base $sp, length 88
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ getInterpolatedDistance(struct VECTOR *pos /*$s2*/)
{ // line 1, address 0xe7ca8
	struct tNode n; // stack address -72
	int fx; // $s4
	int fz; // $s5
	int a; // $s3
	int b; // $s2
	int c; // $v1
	int min; // $s0
	int flag; // $fp
	{ // line 1, address 0xe7ca8
		struct VECTOR *where; // $s2
		struct tNode *node; // $s0
		{ // line 1, address 0xe7ca8
			int x; // $v1
			{ // line 1, address 0xe7ca8
				struct tNode *pos; // $s0
				{ // line 1, address 0xe7ca8
					struct VECTOR sp; // stack address -56
					{ // line 1, address 0xe7ca8
						{ // line 1, address 0xe7ca8
							int z; // $v0
							int x; // $a0
						} // line 1, address 0xe7ca8
					} // line 1, address 0xe7ca8
					{ // line 1, address 0xe7d78
						int res; // $v0
					} // line 1, address 0xe7d9c
				} // line 1, address 0xe7da0
			} // line 1, address 0xe7da0
		} // line 1, address 0xe7da0
	} // line 1, address 0xe7da0
	{ // line 1, address 0xe7da0
		{ // line 1, address 0xe7da0
			int res; // $v0
		} // line 1, address 0xe7da0
	} // line 1, address 0xe7da0
	{ // line 1, address 0xe7da0
		{ // line 1, address 0xe7da0
			struct VECTOR sp; // stack address -56
			{ // line 1, address 0xe7da0
				{ // line 1, address 0xe7da0
					int x; // $a3
					int z; // $v0
				} // line 1, address 0xe7da0
			} // line 1, address 0xe7da0
			{ // line 1, address 0xe7e84
				int res; // $v0
			} // line 1, address 0xe7ea8
		} // line 1, address 0xe7eac
	} // line 1, address 0xe7eac
	{ // line 18, address 0xe7eac
		{ // line 18, address 0xe7eac
			int res; // $a0
		} // line 18, address 0xe7eac
	} // line 18, address 0xe7eac
	{ // line 27, address 0xe7f28
		{ // line 27, address 0xe7f28
			struct VECTOR sp; // stack address -56
			{ // line 27, address 0xe7f28
				{ // line 27, address 0xe7f28
					int x; // $v1
					int z; // $v0
				} // line 27, address 0xe7f28
			} // line 27, address 0xe7f28
			{ // line 1, address 0xe7f8c
				int res; // $v0
			} // line 1, address 0xe7fb0
		} // line 1, address 0xe7fb4
	} // line 1, address 0xe7fb4
	{ // line 29, address 0xe7fb4
		{ // line 29, address 0xe7fb4
			int res; // $a0
		} // line 29, address 0xe7fb4
	} // line 29, address 0xe7fb4
	{ // line 43, address 0xe807c
		{ // line 43, address 0xe807c
			struct VECTOR sp; // stack address -56
			{ // line 43, address 0xe807c
				{ // line 43, address 0xe807c
					int x; // $v1
					int z; // $v0
				} // line 43, address 0xe807c
			} // line 43, address 0xe807c
			{ // line 1, address 0xe80d8
				int res; // $v0
			} // line 1, address 0xe80fc
		} // line 1, address 0xe8100
	} // line 1, address 0xe8100
	{ // line 44, address 0xe8100
		{ // line 44, address 0xe8100
			int res; // $a0
		} // line 44, address 0xe8100
	} // line 44, address 0xe8100
} // line 59, address 0xe822c
/*
 * Offset 0xE822C
 * D:\driver2\game\C\PATHFIND.C (line 891)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ addCivs()
{ // line 2, address 0xe822c
	struct _CAR_DATA *cp; // $t5
	{ // line 7, address 0xe8260
		int where; // $a3
		{ // line 9, address 0xe8260
			int vx; // $a3
			int vz; // $a1
			int x; // $a3
			int z; // $t0
		} // line 9, address 0xe8260
		{ // line 9, address 0xe8260
			int vx; // $t1
			int vz; // $t2
			int x; // $t1
			int z; // $a1
		} // line 31, address 0xe8354
	} // line 32, address 0xe8354
} // line 34, address 0xe836c
/*
 * Offset 0xE836C
 * D:\driver2\game\C\PATHFIND.C (line 933)
 * Stack frame base $sp, length 88
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ UpdateCopMap()
{ // line 2, address 0xe836c
	{ // line 6, address 0xe83c0
	} // line 6, address 0xe83c0
	{ // line 13, address 0xe83fc
		struct tNode startNode; // stack address -72
		{ // line 19, address 0xe843c
			struct _CAR_DATA *cp; // $a0
		} // line 19, address 0xe843c
		{ // line 1, address 0xe8500
			{ // line 1, address 0xe8500
				{ // line 1, address 0xe8500
					{ // line 1, address 0xe8500
						int i; // $a1
						{ // line 1, address 0xe8524
							int d; // $v0
						} // line 1, address 0xe8554
					} // line 1, address 0xe8564
				} // line 1, address 0xe8564
			} // line 1, address 0xe8564
		} // line 1, address 0xe8564
		{ // line 1, address 0xe8564
			{ // line 1, address 0xe8564
				int x; // $v0
				{ // line 1, address 0xe8564
					{ // line 1, address 0xe8564
						struct VECTOR sp; // stack address -56
						{ // line 1, address 0xe8564
							{ // line 1, address 0xe8564
								int z; // $v0
								int x; // $v1
							} // line 1, address 0xe8564
						} // line 1, address 0xe8564
						{ // line 1, address 0xe8604
							int res; // $v0
						} // line 1, address 0xe8628
					} // line 1, address 0xe862c
				} // line 1, address 0xe862c
			} // line 1, address 0xe862c
		} // line 1, address 0xe862c
		{ // line 1, address 0xe862c
			struct tNode n; // stack address -56
			int fx; // $v1
			int fz; // $v0
			{ // line 1, address 0xe8660
				{ // line 1, address 0xe8660
					int dz; // $a0
					int dx; // $v0
				} // line 1, address 0xe8660
			} // line 1, address 0xe8660
			{ // line 1, address 0xe8660
				{ // line 1, address 0xe8660
					unsigned int parent; // $a2
					unsigned int i; // $a3
				} // line 1, address 0xe8774
			} // line 1, address 0xe8774
			{ // line 53, address 0xe8774
				{ // line 53, address 0xe8774
					int dz; // $a0
					int dx; // $v0
				} // line 53, address 0xe8774
			} // line 53, address 0xe8774
			{ // line 53, address 0xe8774
				{ // line 53, address 0xe8774
					unsigned int parent; // $a2
					unsigned int i; // $a3
				} // line 54, address 0xe88b4
			} // line 54, address 0xe88b4
			{ // line 56, address 0xe88b4
				{ // line 56, address 0xe88b4
					int dz; // $a0
					int dx; // $v0
				} // line 56, address 0xe88b4
			} // line 56, address 0xe88b4
			{ // line 56, address 0xe88b4
				{ // line 56, address 0xe88b4
					unsigned int parent; // $a2
					unsigned int i; // $a3
				} // line 57, address 0xe89bc
			} // line 57, address 0xe89bc
			{ // line 1, address 0xe89c4
				{ // line 1, address 0xe89c4
					int dz; // $a0
					int dx; // $v0
				} // line 1, address 0xe89c4
			} // line 1, address 0xe89c4
			{ // line 1, address 0xe89c4
				{ // line 1, address 0xe89c4
					unsigned int parent; // $a2
					unsigned int i; // $a3
				} // line 1, address 0xe8ad8
			} // line 1, address 0xe8ad8
			{ // line 63, address 0xe8ad8
				{ // line 63, address 0xe8ad8
					int dz; // $a0
					int dx; // $v0
				} // line 63, address 0xe8ad8
			} // line 63, address 0xe8ad8
			{ // line 63, address 0xe8ad8
				{ // line 63, address 0xe8ad8
					unsigned int parent; // $a2
					unsigned int i; // $a3
				} // line 64, address 0xe8c18
			} // line 64, address 0xe8c18
			{ // line 66, address 0xe8c18
				{ // line 66, address 0xe8c18
					int dz; // $a0
					int dx; // $v0
				} // line 66, address 0xe8c18
			} // line 66, address 0xe8c18
			{ // line 66, address 0xe8c18
				{ // line 66, address 0xe8c18
					unsigned int parent; // $a2
					unsigned int i; // $a3
				} // line 66, address 0xe8d18
			} // line 66, address 0xe8d18
		} // line 66, address 0xe8d18
	} // line 66, address 0xe8d18
	{ // line 77, address 0xe8d54
		int i; // $s0
		{ // line 1, address 0xe8df4
		} // line 1, address 0xe8dfc
	} // line 91, address 0xe8dfc
	{ // line 94, address 0xe8dfc
		int i; // $a1
		int maxRet; // $a0
	} // line 105, address 0xe8e70
	{ // line 108, address 0xe8e70
		int dx; // $a0
		int dy; // $v1
		int dz; // $v0
	} // line 112, address 0xe8f00
} // line 113, address 0xe8f00
/*
 * Offset 0xE8F00
 * D:\driver2\game\C\PATHFIND.C (line 1050)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ getHeadingToPlayer(int vx /*$s4*/, int vy /*$a1*/, int vz /*$s3*/)
{ // line 1, address 0xe8f00
	int d1; // $s2
	int d2; // $s1
	int d3; // $s0
	struct VECTOR pos; // stack address -48
	{ // line 1, address 0xe8f00
		int dx; // $a3
		int dy; // $v1
		int dz; // $v0
		int playerHereDistSq; // $a3
		{ // line 21, address 0xe8f98
		} // line 23, address 0xe8f98
	} // line 24, address 0xe8f98
	{ // line 48, address 0xe8ff8
	} // line 50, address 0xe9024
	{ // line 52, address 0xe9030
	} // line 60, address 0xe9058
	{ // line 56, address 0xe9058
	} // line 61, address 0xe90a4
} // line 62, address 0xe90a4
/*
 * Offset 0xE90A4
 * D:\driver2\game\C\PATHFIND.C (line 659)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ setDistance(struct tNode *n /*$a0*/, unsigned short dist /*$a1*/)
{
}