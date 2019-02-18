
// LEAD.BIN code...

#include "../decomp_defs.h"

/*
 * Offset 0xE7128
 * D:\driver2\game\C\LEADAI.C (line 278)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ InitLead(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0xe7128
	{ // line 41, address 0xe71a0
		struct DRIVER2_STRAIGHT *straight; // $a3
		struct DRIVER2_CURVE *curve; // $t0
		int i; // $a2
		int dx; // $a0
		int dz; // $a1
		int sqrdist; // $v1
		int min; // $t1
	} // line 74, address 0xe7310
} // line 100, address 0xe73e8
/*
 * Offset 0xE73E8
 * D:\driver2\game\C\LEADAI.C (line 382)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ LeadUpdateState(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0xe73e8
	int dif; // $t0
	int avel; // $s1
	{ // line 17, address 0xe7498
		struct VECTOR tmpStart; // stack address -48
	} // line 30, address 0xe74ec
	{ // line 124, address 0xe7768
		int dist; // $t1
	} // line 153, address 0xe792c
	{ // line 160, address 0xe7938
		struct VECTOR pos; // stack address -32
	} // line 175, address 0xe7980
} // line 182, address 0xe7980
/*
 * Offset 0xE7994
 * D:\driver2\game\C\LEADAI.C (line 566)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
unsigned long /*$ra*/ LeadPadResponse(struct _CAR_DATA *cp /*$t0*/)
{ // line 1, address 0xe7994
	int dif; // $t2
	int avel; // $t1
	unsigned long t0; // $s0
	{ // line 34, address 0xe7a4c
	} // line 60, address 0xe7b18
	{ // line 95, address 0xe7bc8
		int deltaVel; // $a1
		int deltaAVel; // $a3
		int deltaPos; // $a0
		int deltaTh; // $t2
		int steerDelta; // $a0
	} // line 122, address 0xe7d50
	{ // line 128, address 0xe7d58
		int diff; // $a0
	} // line 141, address 0xe7dd4
} // line 149, address 0xe7de8
/*
 * Offset 0xE7DE8
 * D:\driver2\game\C\LEADAI.C (line 718)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ FakeMotion(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, address 0xe7de8
	{ // line 6, address 0xe7e40
		struct DRIVER2_STRAIGHT *straight; // $t1
		static int d; // address 0x0
		static int toGo; // address 0x4
		static int angle; // address 0x8
		static int s; // address 0xc
		static int c; // address 0x10
		int dx; // $a2
		int dz; // $t3
		int nextJunction; // $t0
		{ // line 39, address 0xe7fa4
			struct DRIVER2_JUNCTION *junction; // $s0
		} // line 39, address 0xe7fa4
	} // line 60, address 0xe8010
	{ // line 63, address 0xe8010
		struct DRIVER2_CURVE *curve; // $s0
		int angle; // $a3
		int toGo; // $v0
		int radius; // $a2
		int dx; // $a0
		int dz; // $a1
		int nextJunction; // $a2
		{ // line 95, address 0xe8104
			struct DRIVER2_JUNCTION *junction; // $s0
		} // line 95, address 0xe8104
		{ // line 130, address 0xe81f0
			struct DRIVER2_JUNCTION *junction; // $s0
		} // line 130, address 0xe81f0
	} // line 156, address 0xe82e0
	{ // line 159, address 0xe82e0
		struct DRIVER2_JUNCTION *junction; // $s0
	} // line 167, address 0xe8338
} // line 170, address 0xe8338
/*
 * Offset 0xE834C
 * D:\driver2\game\C\LEADAI.C (line 932)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ PosToIndex(int *normal /*$t1*/, int *tangent /*$t4*/, int intention /*$a2*/, struct _CAR_DATA *cp /*$a3*/)
{ // line 1, address 0xe834c
	{ // line 18, address 0xe8398
		int dist; // $a1
	} // line 26, address 0xe8420
	{ // line 38, address 0xe84b0
		int w; // $t2
		int w80; // $t0
		int t; // $a1
		int t80; // $a3
		{ // line 47, address 0xe85f0
			int temp; // $v1
		} // line 47, address 0xe85f0
		{ // line 54, address 0xe8614
			int temp; // $a0
		} // line 56, address 0xe8614
		{ // line 66, address 0xe865c
		} // line 70, address 0xe8690
	} // line 113, address 0xe86b4
} // line 116, address 0xe86b4
/*
 * Offset 0xE86BC
 * D:\driver2\game\C\LEADAI.C (line 1053)
 * Stack frame base $sp, length 128
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ BlockToMap(struct MAP_DATA *data /*$s3*/)
{ // line 1, address 0xe86bc
	static int carLength; // address 0x14
	static int carWidth; // address 0x18
	static int length; // address 0x14
	static int width; // address 0x18
	static int left; // address 0x1c
	static int right; // address 0x20
	static int ldist; // address 0x24
	static int rdist; // address 0x28
	static struct MAP_DATA newdata; // address 0x30
	{ // line 21, address 0xe873c
		int dx; // $t4
		int dz; // $t3
		int v; // $v1
		int tangent; // $s0
		int normal; // $s1
	} // line 108, address 0xe8ab0
	{ // line 113, address 0xe8ab0
		struct DRIVER2_CURVE *curve; // $s1
		int dx; // $s6
		int dz; // $s5
		int v; // $a0
		int angle; // $a2
		int s; // $s4
		int c; // $s2
		int tangent; // $s0
		int normal; // $s1
	} // line 211, address 0xe8e48
	{ // line 218, address 0xe8e48
		int dx; // $s0
		int dz; // $s2
		int angle; // $s5
		int s; // $t3
		int c; // $t2
		int tangent; // $s1
		int normal; // $s0
		int i; // $s2
		{ // line 248, address 0xe8f7c
			int corners[4][3]; // stack address -112
			int diff; // $v0
			int overlap; // $s1
			int quad1; // $a1
			int quad2; // $v1
			{ // line 297, address 0xe9184
				int temp; // $v1
			} // line 301, address 0xe91b0
			{ // line 310, address 0xe921c
				int vx; // $a1
				int vz; // $t0
				int theta; // $v0
			} // line 328, address 0xe9324
		} // line 329, address 0xe9324
		{ // line 334, address 0xe9350
			int temp; // $a0
		} // line 354, address 0xe93f0
	} // line 358, address 0xe93f0
	{ // line 372, address 0xe9424
		int *nearest; // $s2
		int *furthest; // $s4
		int *ndist; // $s1
		int *fdist; // $s0
		{ // line 390, address 0xe94a4
			int temp; // stack address -64
			int tdist; // stack address -60
		} // line 414, address 0xe9560
	} // line 415, address 0xe9560
	{ // line 429, address 0xe95a0
		int locall; // stack address -56
		int localr; // stack address -48
		int localld; // stack address -52
		int localrd; // stack address -44
		{ // line 439, address 0xe9614
			int i; // $a2
		} // line 446, address 0xe9664
		{ // line 446, address 0xe9664
			int i; // $a0
		} // line 459, address 0xe96ec
	} // line 460, address 0xe96ec
	{ // line 469, address 0xe9734
		int tangent; // $a2
		int i; // $a1
	} // line 480, address 0xe97b0
	{ // line 493, address 0xe97b0
		int dtan; // $a3
		int tangent; // $a2
		int i; // $a1
	} // line 505, address 0xe9874
} // line 507, address 0xe9874
/*
 * Offset 0xE98A4
 * D:\driver2\game\C\LEADAI.C (line 1563)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ IsOnMap(int x /*$t0*/, int z /*$a1*/, struct VECTOR *basePos /*$a2*/, int intention /*$s4*/, struct _CAR_DATA *cp /*stack 16*/)
{ // line 1, address 0xe98a4
	int dx; // $s1
	int dz; // $s2
	{ // line 14, address 0xe9938
		int tangent; // stack address -44
		int normal; // stack address -48
	} // line 28, address 0xe99f4
	{ // line 33, address 0xe99f4
		struct DRIVER2_CURVE *curve; // $s0
		int tangent; // stack address -36
		int normal; // stack address -40
	} // line 59, address 0xe9b20
	{ // line 65, address 0xe9b20
		int tangent; // stack address -28
		int normal; // stack address -32
	} // line 79, address 0xe9b94
} // line 87, address 0xe9bb8
/*
 * Offset 0xE9BB8
 * D:\driver2\game\C\LEADAI.C (line 1657)
 * Stack frame base $sp, length 368
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ UpdateRoadPosition(struct _CAR_DATA *cp /*$s3*/, struct VECTOR *basePos /*stack 4*/, int intention /*stack 8*/)
{ // line 1, address 0xe9bb8
	int sindex; // $t0
	int i; // $s0
	int di; // $a2
	struct _CAR_DATA *lcp; // $s0
	int laneAvoid; // stack address -56
	{ // line 23, address 0xe9c4c
		int cell_x; // $s4
		int x1; // $a0
		{ // line 36, address 0xe9cb0
			int cell_z; // $s0
			int z1; // $s1
			{ // line 43, address 0xe9cfc
				int cbrx; // $a3
				int cbrz; // $a2
				int cbr; // $a0
				{ // line 57, address 0xe9d94
					struct CELL_OBJECT *cop; // $s1
					struct CELL_ITERATOR ci; // stack address -344
					{ // line 64, address 0xe9db0
						struct COLLISION_PACKET *collide; // $s0
						struct MODEL *model; // $a0
						int num_cb; // $a0
						int box_loop; // $s2
						{ // line 82, address 0xe9e4c
							struct MATRIX *mat; // $a1
							struct VECTOR address; // stack address -320
							struct VECTOR vel; // stack address -304
							struct VECTOR length; // stack address -288
							struct MAP_DATA data; // stack address -272
							{ // line 96, address 0xe9ef8
								int sb; // $t0
								int cb; // $a1
								int theta; // $v1
								int xsize; // $a0
								int zsize; // $a3
							} // line 110, address 0xe9fd8
						} // line 118, address 0xe9fd8
					} // line 138, address 0xea068
				} // line 140, address 0xea088
			} // line 141, address 0xea088
		} // line 142, address 0xea098
	} // line 143, address 0xea0ac
	{ // line 157, address 0xea0cc
		struct SVECTOR *colBox; // $a3
		struct VECTOR pos; // stack address -344
		struct VECTOR vel; // stack address -328
		struct VECTOR length; // stack address -312
		struct MAP_DATA data; // stack address -296
	} // line 188, address 0xea260
	{ // line 203, address 0xea2f4
		int left; // $a3
		int right; // $a2
	} // line 232, address 0xea3d8
	{ // line 247, address 0xea410
		int smallest; // $s1
	} // line 266, address 0xea4e0
	{ // line 274, address 0xea4ec
		int tmpMap[41]; // stack address -240
		{ // line 280, address 0xea528
			int count; // $t0
			int j; // $a1
		} // line 287, address 0xea594
	} // line 289, address 0xea5c4
	{ // line 349, address 0xea8ac
		int i; // stack address -68
		int penalty; // $a2
		int left; // stack address -72
		int right; // stack address -64
		int centre; // stack address -60
	} // line 389, address 0xeaaa0
	{ // line 412, address 0xead80
		int biggest; // $a3
		{ // line 433, address 0xeaeac
		} // line 433, address 0xeaeac
	} // line 442, address 0xeaee0
	{ // line 446, address 0xeaee0
		int biggest; // $a1
	} // line 456, address 0xeaf4c
	{ // line 477, address 0xeaffc
		int smallForward; // $a1
		int smallBack; // $v0
	} // line 494, address 0xeb060
	{ // line 569, address 0xeb0c4
		struct _CAR_DATA *cp; // $s3
		int sindex; // $a0
		int intention; // stack address 8
	} // line 569, address 0xeb1cc
} // line 582, address 0xeb1cc
/*
 * Offset 0xEB1FC
 * D:\driver2\game\C\LEADAI.C (line 2242)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CheckCurrentRoad(struct _CAR_DATA *cp /*$s3*/)
{ // line 1, address 0xeb1fc
	static int heading; // address 0x1c
	int cr; // $s5
	static int jdist; // address 0x20
	static int nextJunction; // address 0x50
	static struct VECTOR basePosition; // address 0x60
	int checkNext; // $s6
	{ // line 36, address 0xeb300
		struct DRIVER2_STRAIGHT *straight; // $t3
		static int d; // address 0x70
		static int toGo; // address 0x74
		static int angle; // address 0x78
		static int s; // address 0x7c
		static int c; // address 0x80
		int dx; // $t5
		int dz; // $t6
	} // line 77, address 0xeb578
	{ // line 86, address 0xeb5c4
		struct DRIVER2_CURVE *curve; // $s2
		static int angle; // address 0x84
		static int radius; // address 0x88
		static int dx; // address 0x8c
		static int dz; // address 0x90
		static int fixedThresh; // address 0x94
	} // line 144, address 0xeb8f8
	{ // line 173, address 0xeb974
		static int diff; // address 0x98
		{ // line 178, address 0xeb98c
			struct DRIVER2_JUNCTION *junction; // $s0
		} // line 186, address 0xeb9d4
		{ // line 198, address 0xeba14
			struct DRIVER2_STRAIGHT *straight; // $v1
		} // line 204, address 0xeba5c
		{ // line 207, address 0xeba5c
			struct DRIVER2_CURVE *curve; // $v1
			static int dx; // address 0x9c
			static int dz; // address 0xa0
		} // line 218, address 0xebae8
		{ // line 233, address 0xebb2c
			struct DRIVER2_STRAIGHT *straight; // $t1
			static int dx; // address 0xa4
			static int dz; // address 0xa8
			static int dist; // address 0xac
			static int offx; // address 0xb0
			static int offz; // address 0xb4
		} // line 233, address 0xebb2c
		{ // line 262, address 0xebc5c
			struct DRIVER2_CURVE *curve; // $s4
			static int angle; // address 0xb8
			int radius; // $s2
			static int dx; // address 0xbc
			static int dz; // address 0xc0
			static int basex; // address 0xc4
			static int basez; // address 0xc8
			static int dist; // address 0xcc
			static int offx; // address 0xd0
			static int offz; // address 0xd4
		} // line 302, address 0xebe44
	} // line 352, address 0xebfd0
	{ // line 387, address 0xec158
	} // line 388, address 0xec158
} // line 399, address 0xec194
/*
 * Offset 0xEC1C4
 * D:\driver2\game\C\LEADAI.C (line 2644)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ SetTarget(struct _CAR_DATA *cp /*$s1*/, int cr /*$a0*/, int heading /*$s4*/, int *nextJunction /*$s3*/)
{ // line 1, address 0xec1c4
	{ // line 13, address 0xec1fc
		static int dx; // address 0xd8
		static int dz; // address 0xdc
	} // line 24, address 0xec278
	{ // line 31, address 0xec298
		struct DRIVER2_STRAIGHT *straight; // $t5
		int dx; // $a1
		int dz; // $a0
		int rx; // $v1
		int rz; // $a2
		int ux; // $t0
		int uz; // $t4
		int d; // $v1
		int angle; // $v0
		int mul; // $v1
	} // line 51, address 0xec33c
	{ // line 76, address 0xec444
		struct DRIVER2_CURVE *curve; // $s0
		int angle; // $a1
		int radius; // $a2
	} // line 110, address 0xec5c4
} // line 116, address 0xec5c4
/*
 * Offset 0xEC5E4
 * D:\driver2\game\C\LEADAI.C (line 2763)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SelectExit(struct _CAR_DATA *cp /*$s3*/, struct DRIVER2_JUNCTION *junction /*$a3*/)
{ // line 1, address 0xec5e4
	int onward; // $s1
	int numExits; // $s2
	int el[4][2]; // stack address -56
	int tmp; // $a1
	int i; // $a2
	int total; // $s0
	{ // line 18, address 0xec6f4
	} // line 25, address 0xec71c
	{ // line 29, address 0xec79c
	} // line 36, address 0xec7c8
	{ // line 40, address 0xec844
	} // line 47, address 0xec870
} // line 80, address 0xec99c
/*
 * Offset 0xEC99C
 * D:\driver2\game\C\LEADAI.C (line 2848)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
unsigned long /*$ra*/ FreeRoamer(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, address 0xec99c
	{ // line 117, address 0xeca4c
		struct _CAR_DATA *pCar; // $v0
		{ // line 117, address 0xeca4c
			int seed; // $a0
			{ // line 117, address 0xeca4c
				int i; // $s0
			} // line 118, address 0xecb04
		} // line 118, address 0xecb04
	} // line 119, address 0xecb04
} // line 123, address 0xecb28
/*
 * Offset 0xECB28
 * D:\driver2\game\C\LEADAI.C (line 2993)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
unsigned long /*$ra*/ hypot(long x /*$s1*/, long y /*$a1*/)
{ // line 1, address 0xecb28
	{ // line 4, address 0xecb5c
		long t; // $v0
	} // line 4, address 0xecb64
	{ // line 8, address 0xecbb4
	} // line 13, address 0xecbe8
} // line 14, address 0xecbe8