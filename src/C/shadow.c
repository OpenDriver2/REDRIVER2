#include "../decomp_defs.h"

/*
 * Offset 0x75470
 * D:\driver2\game\C\SHADOW.C (line 272)
 * Stack frame base $sp, length 104
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ GetTyreTrackPositions(struct _CAR_DATA *cp /*$s3*/, int player_id /*$s7*/)
{ // line 1, address 0x75470
	struct CAR_COSMETICS *car_cos; // $s4
	struct VECTOR WheelPos; // stack address -88
	struct VECTOR target_pos; // stack address -72
	struct VECTOR normal; // stack address -56
	int loop; // $s2
	{ // line 11, address 0x754c0
	} // line 16, address 0x754e8
} // line 26, address 0x755a8
/*
 * Offset 0x755A8
 * D:\driver2\game\C\SHADOW.C (line 330)
 * Stack frame base $sp, length 200
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ AddTyreTrack(int wheel /*$s2*/, int tracksAndSmoke /*$s6*/, int padid /*$s0*/)
{ // line 1, address 0x755a8
	struct VECTOR New1; // stack address -168
	struct VECTOR New2; // stack address -152
	struct VECTOR New3; // stack address -136
	struct VECTOR New4; // stack address -120
	struct VECTOR *old; // $s5
	struct VECTOR *newt; // $s3
	struct TYRE_TRACK *tt_p; // $s1
	int x; // $v1
	int z; // $a1
	int c; // $t1
	int s; // $t0
	unsigned int index; // $a2
	static int Cont[4]; // address 0x0
	struct VECTOR psxoffset; // stack address -104
	struct VECTOR SmokeDrift; // stack address -88
	struct VECTOR SmokePosition; // stack address -72
	char trackSurface; // $s0
	{ // line 34, address 0x75678
		struct ROUTE_DATA routeData; // stack address -56
		struct _sdPlane *SurfaceDataPtr; // $v0
	} // line 69, address 0x75704
	{ // line 74, address 0x75710
	} // line 81, address 0x75738
	{ // line 91, address 0x75794
		struct VECTOR grass_vector; // stack address -48
	} // line 91, address 0x75794
} // line 176, address 0x75a20
/*
 * Offset 0x75A48
 * D:\driver2\game\C\SHADOW.C (line 517)
 * Stack frame base $sp, length 136
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6
 */
void /*$ra*/ DrawTyreTracks()
{ // line 2, address 0x75a48
	struct VECTOR p[4]; // stack address -136
	struct SVECTOR ps[4]; // stack address -72
	struct TYRE_TRACK *tt_p; // $t0
	int z; // stack address -40
	int temp; // $a2
	int loop; // $t7
	int wheel_loop; // $s0
	int index; // $t2
	char last_duff; // $s1
	struct POLY_FT4 *poly; // $a3
	struct POLY_FT4 *lasttyre; // $t8
} // line 128, address 0x75f9c
/*
 * Offset 0x75F9C
 * D:\driver2\game\C\SHADOW.C (line 659)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ InitShadow()
{ // line 2, address 0x75f9c
	struct TPAN pos; // stack address -16
	struct TEXINF *texinf; // $v0
	int i; // $a2
	int j; // $a3
	{ // line 23, address 0x760f8
	} // line 25, address 0x760f8
} // line 38, address 0x76170
/*
 * Offset 0x76170
 * D:\driver2\game\C\SHADOW.C (line 717)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SubdivShadow(long z0 /*$t7*/, long z1 /*$t9*/, long z2 /*$t8*/, long z3 /*$t6*/, struct POLY_FT4 *sps /*stack 16*/)
{ // line 1, address 0x76170
	struct POLY_FT4 *spd; // $t3
	int i; // $t4
	{ // line 18, address 0x76220
		unsigned long A0; // $v1
		unsigned long A1; // $a1
		unsigned long E0; // $a3
		unsigned long E1; // $t0
		unsigned long C0; // $a0
		unsigned long C1; // $a2
		unsigned long B0; // $v1
		unsigned long B1; // $a1
		unsigned long D0; // $a0
		unsigned long D1; // $a2
	} // line 18, address 0x76220
	{ // line 18, address 0x76220
		unsigned long A0; // $a1
		unsigned long A1; // $a2
		unsigned long E0; // $a3
		unsigned long E1; // $t0
		unsigned long C0; // $a0
		unsigned long C1; // $v1
		unsigned long B0; // $a1
		unsigned long B1; // $a2
		unsigned long D0; // $a0
		unsigned long D1; // $v1
	} // line 18, address 0x76220
} // line 144, address 0x76734
/*
 * Offset 0x76734
 * D:\driver2\game\C\SHADOW.C (line 864)
 * Stack frame base $sp, length 88
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ PlaceShadowForCar(struct VECTOR *shadowPoints /*$t0*/, int slot /*$s0*/, struct VECTOR *CarPos /*$a2*/, int zclip /*$a3*/)
{ // line 1, address 0x76734
	struct SVECTOR points[4]; // stack address -64
	long z; // $a0
	long z0; // stack address -32
	long z1; // stack address -28
	long z2; // stack address -24
	long z3; // stack address -20
	struct POLY_FT4 *spt; // $a3
} // line 69, address 0x76aa8
/*
 * Offset 0x76AA8
 * D:\driver2\game\C\SHADOW.C (line 1038)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ clipAgainstZ()
{ // line 2, address 0x76aa8
	int srccount; // $t4
	int dstcount; // $t5
	struct SVECTOR *current; // $t2
	struct SVECTOR *previous; // $t1
	struct SVECTOR *dst; // $a3
	int flags; // $t3
	{ // line 19, address 0x76b28
		int q; // $a2
	} // line 19, address 0x76b28
	{ // line 25, address 0x76c20
		int q; // $a2
	} // line 25, address 0x76c20
} // line 41, address 0x76d3c
/*
 * Offset 0x76D3C
 * D:\driver2\game\C\SHADOW.C (line 1081)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ clippedPoly()
{ // line 2, address 0x76d3c
	int i; // $a3
	int j; // $t0
	int z1; // $v1
	struct POLY_G3 *pg3; // $s0
	int z[3]; // stack address -24
} // line 75, address 0x77190
/*
 * Offset 0x771A0
 * D:\driver2\game\C\SHADOW.C (line 1160)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ sQuad(struct SVECTOR *v0 /*$a0*/, struct SVECTOR *v1 /*$s5*/, struct SVECTOR *v2 /*$s6*/, struct SVECTOR *v3 /*$s4*/)
{ // line 1, address 0x771a0
	int z1; // $v0
	int z[4]; // stack address -48
	{ // line 8, address 0x7721c
		struct POLY_G4 *pf4; // $t2
	} // line 30, address 0x7731c
} // line 62, address 0x7758c
/*
 * Offset 0x7758C
 * D:\driver2\game\C\SHADOW.C (line 253)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitTyreTracks()
{ // line 2, address 0x7758c
	int loop; // $a0
} // line 9, address 0x775c0
/*
 * Offset 0x775C0
 * D:\driver2\game\C\SHADOW.C (line 306)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetTyreTrackOldPositions(int player_id /*$a0*/)
{
}