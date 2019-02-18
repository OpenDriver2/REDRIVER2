
#include "../decomp_defs.h"

/*
 * Offset 0x53884
 * D:\driver2\game\C\HANDLING.C (line 998)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ InitCarPhysics(struct _CAR_DATA *cp /*$s0*/, long *startpos[4] /*$t0*/, int direction /*$a2*/)
{ // line 1, address 0x53884
	int ty; // $v1
	int dz; // $s1
	int odz; // $a3
	{ // line 6, address 0x538f8
		unsigned long *dst; // $a1
	} // line 6, address 0x538f8
} // line 42, address 0x53a50
/*
 * Offset 0x53A50
 * D:\driver2\game\C\HANDLING.C (line 1055)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ TempBuildHandlingMatrix(struct _CAR_DATA *cp /*$s0*/, int init /*$a1*/)
{ // line 1, address 0x53a50
	int ty; // $v1
	int dz; // $a3
} // line 20, address 0x53b70
/*
 * Offset 0x53B70
 * D:\driver2\game\C\HANDLING.C (line 1079)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ UpdateCarPoints(struct CAR_COSMETICS *carCos /*$a0*/)
{ // line 1, address 0x53b70
	struct SVECTOR *groundCollPoints; // $a1
	struct SVECTOR *wheelPoints; // $a3
	int i; // $a2
} // line 24, address 0x53c68
/*
 * Offset 0x53C68
 * D:\driver2\game\C\HANDLING.C (line 1192)
 * Stack frame base $sp, length 272
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ GlobalTimeStep()
{ // line 2, address 0x53c68
	int i; // $fp
	int RKstep; // stack address -84
	int subframe; // stack address -80
	struct _CAR_DATA *c0; // $s0
	static union RigidBodyState _tp[20]; // address 0x0
	static union RigidBodyState _d0[20]; // address 0x410
	static union RigidBodyState _d1[20]; // address 0x820
	{ // line 76, address 0x53cd4
		struct _CAR_DATA *c0; // $t2
		union RigidBodyState *st; // $t1
		{ // line 91, address 0x53d94
			int s; // $v0
		} // line 101, address 0x53df8
		{ // line 109, address 0x53e80
			long AV[4]; // stack address -248
			long delta_orientation[4]; // stack address -232
		} // line 129, address 0x54060
	} // line 130, address 0x54060
	{ // line 142, address 0x5408c
		union RigidBodyState *thisDelta; // stack address -76
		{ // line 148, address 0x540a0
			struct _CAR_DATA *c0; // $s4
			{ // line 156, address 0x540fc
				union RigidBodyState *thisState_i; // $s6
				int j; // stack address -72
				{ // line 1, address 0x54154
					union RigidBodyState *state; // $s6
					union RigidBodyState *delta; // $a3
					struct _CAR_DATA *cp; // $s4
					{ // line 1, address 0x54154
						long AV[4]; // stack address -248
					} // line 1, address 0x54154
				} // line 1, address 0x54154
				{ // line 175, address 0x54340
					struct _CAR_DATA *c1; // $s3
					union RigidBodyState *thisState_j; // $s0
					{ // line 183, address 0x543a8
						int strength; // $s5
						long centre0[4]; // stack address -248
						long centre1[4]; // stack address -232
						long normal[4]; // stack address -216
						long collisionpoint[4]; // stack address -200
						{ // line 186, address 0x543a8
							struct BOUND_BOX *bb1; // $a2
							struct BOUND_BOX *bb2; // $a0
						} // line 217, address 0x544a8
						{ // line 222, address 0x544a8
							int depth; // stack address -88
						} // line 227, address 0x544c8
						{ // line 227, address 0x544c8
							long lever0[4]; // stack address -184
							long lever1[4]; // stack address -168
							long torque[4]; // stack address -152
							long pointVel0[4]; // stack address -136
							long pointVel1[4]; // stack address -120
							int strikeVel; // stack address -68
							{ // line 227, address 0x544c8
								int is; // $v0
								int wanted; // $v1
							} // line 227, address 0x544c8
							{ // line 295, address 0x548d8
								struct VECTOR velocity; // stack address -104
								{ // line 314, address 0x5498c
									int debris1; // $s0
									int debris2; // $s2
								} // line 326, address 0x549e4
							} // line 327, address 0x549e4
							{ // line 334, address 0x54a24
								int do1; // $a0
								int do2; // $t5
								int m1; // $t3
								int m2; // $a1
								{ // line 356, address 0x54ab8
									long force[4]; // stack address -104
									int strength1; // $a0
									int twistY; // $t4
								} // line 385, address 0x54d08
								{ // line 389, address 0x54d10
									long force[4]; // stack address -104
									int strength2; // $a1
									int twistY; // $t2
								} // line 418, address 0x54f44
							} // line 419, address 0x54f44
						} // line 426, address 0x54fc0
					} // line 427, address 0x54fc0
				} // line 428, address 0x54fc0
			} // line 429, address 0x54fe4
		} // line 430, address 0x54fe4
		{ // line 434, address 0x5500c
			struct _CAR_DATA *c0; // $a1
			{ // line 438, address 0x5502c
				union RigidBodyState *st; // $t2
				union RigidBodyState *tp; // $a0
				union RigidBodyState *d0; // $a2
				union RigidBodyState *d1; // $v1
				int j; // $t1
			} // line 454, address 0x55118
		} // line 455, address 0x55118
	} // line 456, address 0x55130
	{ // line 460, address 0x5515c
		int carsDentedThisFrame; // $s2
		{ // line 463, address 0x5516c
			{ // line 464, address 0x5516c
				unsigned long *dst; // $a1
			} // line 464, address 0x5516c
			{ // line 478, address 0x551f0
			} // line 481, address 0x55200
		} // line 483, address 0x55200
	} // line 487, address 0x55254
} // line 507, address 0x55254
/*
 * Offset 0x55254
 * D:\driver2\game\C\HANDLING.C (line 1704)
 * Stack frame base $sp, length 120
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SetShadowPoints(struct _CAR_DATA *c0 /*$s4*/)
{ // line 1, address 0x55254
	int j; // $s2
	struct CAR_COSMETICS *car_cos; // $v1
	struct _sdPlane *surfacePtr; // stack address -48
	{ // line 14, address 0x55310
		struct SVECTOR disp; // stack address -104
		struct VECTOR pointPos; // stack address -96
		struct VECTOR surfaceNormal; // stack address -80
		struct VECTOR surfacePoint; // stack address -64
	} // line 35, address 0x553f0
} // line 37, address 0x55434
/*
 * Offset 0x55434
 * D:\driver2\game\C\HANDLING.C (line 1753)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ LongQuaternion2Matrix(long *qua[4] /*$a0*/, struct MATRIX *m /*$a1*/)
{ // line 1, address 0x55434
	int xx; // $t3
	int xy; // $a3
	int xz; // $t2
	int xw; // $t0
	int yy; // $t7
	int yz; // $a2
	int yw; // $t5
	int zz; // $v1
	int zw; // $a0
} // line 25, address 0x55558
/*
 * Offset 0x55558
 * D:\driver2\game\C\HANDLING.C (line 1802)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ initOBox(struct _CAR_DATA *cp /*$a2*/)
{ // line 1, address 0x55558
	struct SVECTOR *boxDisp; // $a0
	{ // line 1, address 0x55558
		int length; // $a1
	} // line 40, address 0x55748
} // line 42, address 0x55748
/*
 * Offset 0x55748
 * D:\driver2\game\C\HANDLING.C (line 1930)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ CheckCarToCarCollisions()
{ // line 2, address 0x55748
	struct _CAR_DATA *cp; // $t2
	struct BOUND_BOX *bp; // $t1
	struct BOUND_BOX *bb1; // $t0
	struct BOUND_BOX *bb2; // $a1
	int lbod; // $v1
	int wbod; // $a0
	int hbod; // $t0
	struct SVECTOR *colBox; // $a1
	int loop1; // $t4
	int loop2; // $a3
	{ // line 17, address 0x55774
		int wx; // $v1
		int wz; // $a2
	} // line 52, address 0x55994
} // line 84, address 0x55afc
/*
 * Offset 0x55B04
 * D:\driver2\game\C\HANDLING.C (line 2027)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ProcessCarPad(struct _CAR_DATA *cp /*$s0*/, unsigned long pad /*$s3*/, char PadSteer /*$s4*/, char use_analogue /*$s5*/)
{ // line 1, address 0x55b04
	int player_id; // $s1
	{ // line 131, address 0x55d40
		int int_steer; // $v0
		int analog_angle; // $v1
	} // line 153, address 0x55df8
	{ // line 233, address 0x55f58
		int rws; // $v0
	} // line 243, address 0x55fe8
	{ // line 255, address 0x5604c
		int playerCar; // $v0
		int dist; // $a0
		int dx; // $a0
		int dz; // $v0
	} // line 272, address 0x560e8
	{ // line 276, address 0x560f8
		int targetCarId; // $v1
		{ // line 293, address 0x5613c
			struct _CAR_DATA *tp; // $a1
			int cx; // $v1
			int cz; // $v0
			int chase_square_dist; // $v0
			{ // line 300, address 0x56174
				int averagePower; // $a0
			} // line 302, address 0x561b0
		} // line 313, address 0x562c0
	} // line 315, address 0x562c0
} // line 348, address 0x56314
/*
 * Offset 0x56314
 * D:\driver2\game\C\HANDLING.C (line 2397)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ TerminateSkidding(int player_id /*$a0*/)
{
}
/*
 * Offset 0x563B8
 * D:\driver2\game\C\HANDLING.C (line 2414)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ CheckCarEffects(struct _CAR_DATA *cp /*$s2*/, int player_id /*$s3*/)
{ // line 1, address 0x563b8
	int skidsound; // $s1
	int cnt; // $a0
	int wheels_on_ground; // $s5
	char lay_down_tracks; // $s7
	char desired_skid; // $a1
	char desired_wheel; // $a1
	{ // line 86, address 0x56650
		int pitch; // $v0
	} // line 90, address 0x566ac
	{ // line 93, address 0x566c8
		int wnse; // $a0
	} // line 96, address 0x56710
	{ // line 119, address 0x56810
		int pitch; // $t0
	} // line 123, address 0x56878
	{ // line 132, address 0x568a8
	} // line 136, address 0x568d0
} // line 146, address 0x56914
/*
 * Offset 0x56940
 * D:\driver2\game\C\HANDLING.C (line 2575)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ jump_debris(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, address 0x56940
	int count; // $a1
	{ // line 24, address 0x569cc
		struct VECTOR position; // stack address -48
		struct VECTOR velocity; // stack address -32
	} // line 28, address 0x56a60
} // line 29, address 0x56a60
/*
 * Offset 0x56A74
 * D:\driver2\game\C\HANDLING.C (line 1875)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ StepCarPhysics(struct _CAR_DATA *cp /*$a2*/)
{ // line 1, address 0x56a74
	struct _HANDLING_TYPE *hp; // $v0
} // line 24, address 0x56acc
/*
 * Offset 0x56AD4
 * D:\driver2\game\C\HANDLING.C (line 1911)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitialiseCarHandling()
{
}
/*
 * Offset 0x56ADC
 * D:\driver2\game\C\HANDLING.C (line 2607)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ nose_down(struct _CAR_DATA *cp /*$a0*/)
{
}
/*
 * Offset 0x56B4C
 * D:\driver2\game\C\HANDLING.C (line 1854)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ RebuildCarMatrix(union RigidBodyState *st /*$a2*/, struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x56b4c
	{ // line 1, address 0x56b4c
		int sm; // $v1
		{ // line 5, address 0x56bf4
			int osm; // $v0
		} // line 5, address 0x56c68
	} // line 5, address 0x56c68
} // line 8, address 0x56c8c
/*
 * Offset 0x56C8C
 * D:\driver2\game\C\HANDLING.C (line 1106)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ FixCarCos(struct CAR_COSMETICS *carCos /*$s0*/, int externalModelNumber /*$a1*/)
{ // line 1, address 0x56c8c
	int current; // $v0
} // line 24, address 0x56d20
/*
 * Offset 0x56D20
 * D:\driver2\game\C\HANDLING.C (line 2389)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitSkidding()
{ // line 1, address 0x56d20
	int i; // $a0
} // line 6, address 0x56d54
/*
 * Offset 0x56D54
 * D:\driver2\game\C\HANDLING.C (line 2664)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetPlayerId(struct _CAR_DATA *cp /*$a0*/)
{ // line 1, address 0x56d54
	int i; // $a1
	int p_id; // $a3
} // line 5, address 0x56dbc