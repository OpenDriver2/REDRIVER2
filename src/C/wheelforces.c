
#include "../decomp_defs.h"

HANDLING_TYPE handlingType[7] = {
	{0x20, 1, 0, 1},
	{0x1D, 0, 0, 0},
	{0x2D, 1, 1, 0},
	{0x37, 1, 1, 0},
	{0x44, 1, 1, 0},
	{0x20, 1, 0, 1},
	{0x1D, 0, 0, 0}
};


/*
 * Offset 0x811E0
 * D:\driver2\game\C\WHEELFORCES.C (line 98)
 * Stack frame base $sp, length 264
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ StepOneCar(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, address 0x811e0
	struct CAR_LOCALS _cl; // stack address -248
	struct CAR_LOCALS *cl; // $s3
	int i; // $s0
	int speed; // $v1
	struct _sdPlane *SurfacePtr; // stack address -48
	{ // line 24, address 0x8127c
		int a; // $v1
		int b; // $a0
	} // line 33, address 0x812e4
	{ // line 35, address 0x812e4
		long deepestNormal[4]; // stack address -208
		long deepestLever[4]; // stack address -192
		long deepestPoint[4]; // stack address -176
		int lift; // $s5
		int count; // $a0
		int friToUse; // $s6
		struct SVECTOR *carDisp; // $a1
		{ // line 58, address 0x8137c
			long pointPos[4]; // stack address -160
			long surfacePoint[4]; // stack address -144
			long surfaceNormal[4]; // stack address -128
			long lever[4]; // stack address -112
			int newLift; // $a0
		} // line 98, address 0x81478
		{ // line 103, address 0x81490
			long pointVel[4]; // stack address -112
			long reaction[4]; // stack address -96
			int strikeVel; // $a2
			int componant; // $t3
			static int frictionLimit[6] = { 4116480, 24698880, 4116480, 20582400, 123494400 }; // address 0x0
			{ // line 111, address 0x81490
				int lever_dot_n; // $v1
				int twistY; // $v0
				int displacementsquared; // $a0
				int denom; // $a0
			} // line 111, address 0x81490
			{ // line 128, address 0x81698
				int loss; // $v1
				int limit; // $a1
			} // line 132, address 0x816d4
			{ // line 137, address 0x81720
				{ // line 139, address 0x81734
					struct VECTOR direction; // stack address -80
				} // line 139, address 0x81734
				{ // line 144, address 0x81774
					struct VECTOR direction; // stack address -64
				} // line 146, address 0x817ac
			} // line 151, address 0x81804
		} // line 152, address 0x81804
		{ // line 158, address 0x818d4
			struct VECTOR address; // stack address -112
		} // line 171, address 0x819ac
	} // line 172, address 0x819ac
} // line 184, address 0x819f4
/*
 * Offset 0x819F4
 * D:\driver2\game\C\WHEELFORCES.C (line 288)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ GetFrictionScalesDriver1(struct _CAR_DATA *cp /*$t0*/, struct CAR_LOCALS *cl /*$a1*/, int *frontFS /*$a2*/, int *rearFS /*$a3*/)
{ // line 1, address 0x819f4
	struct _HANDLING_TYPE *hp; // $t2
	{ // line 18, address 0x81a84
		int q; // $v1
	} // line 26, address 0x81b00
	{ // line 99, address 0x81e30
		int traction; // $a0
	} // line 105, address 0x81e88
} // line 106, address 0x81e88
/*
 * Offset 0x81E88
 * D:\driver2\game\C\WHEELFORCES.C (line 412)
 * Stack frame base $sp, length 16
 */
void /*$ra*/ ConvertTorqueToAngularAcceleration(struct _CAR_DATA *cp /*$a0*/, struct CAR_LOCALS *cl /*$t5*/)
{ // line 1, address 0x81e88
	long nose[4]; // stack address -16
	int zd; // $a3
	int i; // $t4
	int twistY; // $t0
	int twistZ; // $v1
} // line 27, address 0x81fb8
/*
 * Offset 0x81FB8
 * D:\driver2\game\C\WHEELFORCES.C (line 442)
 * Stack frame base $sp, length 208
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddWheelForcesDriver1(struct _CAR_DATA *cp /*$s2*/, struct CAR_LOCALS *cl /*$s7*/)
{ // line 1, address 0x81fb8
	int oldSpeed; // $v1
	int frictionScale; // $fp
	int frontFS; // stack address -96
	int rearFS; // stack address -92
	int i; // stack address -84
	int cdx; // stack address -80
	int cdz; // stack address -76
	int sdx; // stack address -72
	int sdz; // stack address -68
	int friction_coef; // $s6
	struct CAR_COSMETICS *car_cos; // stack address -64
	struct _sdPlane *SurfacePtr; // stack address -88
	int player_id; // stack address -60
	{ // line 27, address 0x8210c
		int oldCompression; // $s5
		int newCompression; // $s3
		int susForce; // $s0
		long wheelPos[4]; // stack address -176
		long surfacePoint[4]; // stack address -160
		long surfaceNormal[4]; // stack address -144
		{ // line 46, address 0x821a8
			short typ; // $v1
		} // line 55, address 0x82240
		{ // line 71, address 0x822ec
			int chan; // $s1
		} // line 83, address 0x82384
		{ // line 95, address 0x823e8
			struct VECTOR force; // stack address -128
			long pointVel[4]; // stack address -112
			int lfx; // $a2
			int lfz; // $t2
			int sidevel; // $t0
			int slidevel; // $t1
			{ // line 112, address 0x824f4
			} // line 117, address 0x82558
			{ // line 150, address 0x82698
				int hack; // $v0
				int hx; // $v0
				int hz; // $v1
			} // line 150, address 0x82698
			{ // line 203, address 0x82958
				int a; // $v1
			} // line 206, address 0x82990
		} // line 229, address 0x82a6c
	} // line 237, address 0x82b44
} // line 252, address 0x82c38
/*
 * Offset 0x82C38
 * D:\driver2\game\C\WHEELFORCES.C (line 66)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ StepCars()
{ // line 2, address 0x82c38
	struct _CAR_DATA **ppCar; // $s0
	struct _CAR_DATA **end; // $s1
	{ // line 7, address 0x82c74
	} // line 10, address 0x82c74
	{ // line 14, address 0x82c9c
	} // line 15, address 0x82c9c
} // line 17, address 0x82ccc