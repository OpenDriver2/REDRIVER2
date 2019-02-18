#include "../decomp_defs.h"

char* CosmeticFiles[] ={
	"LEVELS\\CHICAGO.LCF",
	"LEVELS\\HAVANA.LCF",
	"LEVELS\\VEGAS.LCF",
	"LEVELS\\RIO.LCF",
};

/*
 * Offset 0x2F9FC
 * D:\driver2\game\C\COSMETIC.C (line 252)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ AddReverseLight(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, address 0x2f9fc
	struct CAR_COSMETICS *car_cos; // $a1
	struct SVECTOR v1; // stack address -32
	struct CVECTOR col; // stack address -24
	short cogOffset; // $s2
} // line 31, address 0x2fb54
/*
 * Offset 0x2FB54
 * D:\driver2\game\C\COSMETIC.C (line 325)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ AddIndicatorLight(struct _CAR_DATA *cp /*$s0*/, int Type /*$s6*/)
{ // line 1, address 0x2fb54
	struct CAR_COSMETICS *car_cos; // $a1
	struct CVECTOR col; // stack address -56
	struct SVECTOR vfrnt; // stack address -48
	struct SVECTOR vback; // stack address -40
	char tempcol; // $s1
	char *life; // $a0
	char *life2; // $s3
	short cogOffset; // $s2
} // line 72, address 0x2fe24
/*
 * Offset 0x2FE4C
 * D:\driver2\game\C\COSMETIC.C (line 407)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddBrakeLight(struct _CAR_DATA *cp /*$s5*/)
{ // line 1, address 0x2fe4c
	struct CAR_COSMETICS *car_cos; // $a1
	struct SVECTOR v1; // stack address -88
	struct SVECTOR v2; // stack address -80
	struct SVECTOR vec; // stack address -72
	struct CVECTOR col; // stack address -64
	char *life2; // $s2
	short doubleFlag; // stack address -56
	short verticalFlag; // stack address -52
	short address; // $s1
	short loop; // $fp
	short damIndex; // $v0
	short cogOffset; // $a3
} // line 97, address 0x30180
/*
 * Offset 0x301B0
 * D:\driver2\game\C\COSMETIC.C (line 514)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddCopCarLight(struct _CAR_DATA *cp /*$t0*/)
{ // line 1, address 0x301b0
	int length; // $a3
	int light; // $s1
	int pos; // $s3
	int side; // $s4
	int num_lights; // $t5
	int count_speed; // $t4
	char col1; // $a2
	char col2; // $a1
	static char xpos1[8] = { 0x30, 0x20, 0x10, 0, 0, 0x10, 0x20, 0x30 };
	int sign; // $t1
	char *coplife; // $s2
	struct SVECTOR v1; // stack address -88
	struct CVECTOR col; // stack address -80
	struct CAR_COSMETICS *car_cos; // $s0
	short cogOffset; // $fp
} // line 130, address 0x3057c
/*
 * Offset 0x305AC
 * D:\driver2\game\C\COSMETIC.C (line 653)
 * Stack frame base $sp, length 128
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddNightLights(struct _CAR_DATA *cp /*$s6*/)
{ // line 1, address 0x305ac
	static struct MATRIX work_matrix; // address 0x0
	struct CAR_COSMETICS *car_cos; // $fp
	struct SVECTOR Position1; // stack address -104
	struct SVECTOR Position2; // stack address -96
	struct SVECTOR vec; // stack address -88
	struct CVECTOR col; // stack address -80
	int lit; // stack address -72
	int lightFlag; // $t0
	char *life2; // stack address -68
	short damIndex; // $s5
	short loop; // stack address -64
	short address; // $s2
	short doubleFlag; // stack address -60
	short verticalFlag; // stack address -56
	short cogOffset; // stack address -52
} // line 266, address 0x30e04
/*
 * Offset 0x30E04
 * D:\driver2\game\C\COSMETIC.C (line 989)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ AddSmokingEngine(struct _CAR_DATA *cp /*$s0*/, int black_smoke /*$s2*/, int WheelSpeed /*$s3*/)
{ // line 1, address 0x30e04
	struct VECTOR SmokePos; // stack address -64
	struct CAR_COSMETICS *car_cos; // $a0
	struct VECTOR Drift; // stack address -48
	struct SVECTOR svec; // stack address -32
} // line 49, address 0x30ff8
/*
 * Offset 0x31014
 * D:\driver2\game\C\COSMETIC.C (line 1048)
 * Stack frame base $sp, length 88
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ AddFlamingEngine(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, address 0x31014
	struct VECTOR SmokePos; // stack address -56
	struct SVECTOR svec; // stack address -40
	struct CAR_COSMETICS *car_cos; // $a0
	struct VECTOR Drift; // stack address -32
} // line 36, address 0x311b4
/*
 * Offset 0x311C8
 * D:\driver2\game\C\COSMETIC.C (line 188)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ LoadCosmetics(int level /*$a0*/)
{ // line 2, address 0x311c8
} // line 15, address 0x31218
/*
 * Offset 0x31218
 * D:\driver2\game\C\COSMETIC.C (line 213)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ ProcessCosmeticsLump(char *lump_ptr /*$s2*/, int lump_size /*$a1*/)
{ // line 1, address 0x31218
	int i; // $t0
	int model; // $a1
	int address; // $a0
	{ // line 23, address 0x312a0
	} // line 27, address 0x313a0
} // line 30, address 0x313c8
/*
 * Offset 0x313C8
 * D:\driver2\game\C\COSMETIC.C (line 293)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupSpecCosmetics(char *loadbuffer /*$a0*/)
{ // line 5, address 0x313c8
	int *to; // $a1
	int *from; // $a0
	int *end; // $v1
} // line 18, address 0x31400