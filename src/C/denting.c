#include "../decomp_defs.h"

char* DentingFiles[] =
{
	"LEVELS\\CHICAGO.DEN",
	"LEVELS\\HAVANA.DEN",
	"LEVELS\\VEGAS.DEN",
	"LEVELS\\RIO.DEN",
};

/*
 * Offset 0x3A378
 * D:\driver2\game\C\DENTING.C (line 288)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: s0 s1 s2 s3 s4
 */
void /*$ra*/ DentCar(struct _CAR_DATA *cp /*$t7*/)
{ // line 1, address 0x3a378
	struct SVECTOR *VertPtr; // $t0
	int MaxDamage; // $s0
	unsigned char VertIndex; // $v0
	unsigned char PolyIndex; // $v0
	struct DENTUVS *dentptr; // $t1
	unsigned char *DamPtr; // $a2
	int model; // $t5
	int Poly; // $a1
	int Damage; // $v1
	int Zone; // $a3
	int VertNo; // $a2
	short *tempDamage; // $t1
	struct SVECTOR *DamVertPtr; // $a3
	struct SVECTOR *CleanVertPtr; // $a1
	struct MODEL *pCleanModel; // $t3
	{ // line 133, address 0x3a6f8
	} // line 135, address 0x3a6f8
} // line 140, address 0x3a74c
/*
 * Offset 0x3A74C
 * D:\driver2\game\C\DENTING.C (line 458)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ CreateDentableCar(struct _CAR_DATA *cp /*$t2*/)
{ // line 1, address 0x3a74c
	struct DENTUVS *dentptr; // $a3
	int Zone; // $v1
	int count; // $a2
	int model; // $t3
	{ // line 20, address 0x3a778
		struct SVECTOR *dst; // $a2
		struct SVECTOR *src; // $a3
		int count; // $t0
		{ // line 26, address 0x3a7b0
			int x; // $v0
			int y; // $v1
			int z; // $a0
		} // line 26, address 0x3a7b0
	} // line 35, address 0x3a7d8
} // line 76, address 0x3a8dc
/*
 * Offset 0x3A8DC
 * D:\driver2\game\C\DENTING.C (line 549)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitHubcap()
{ // line 3, address 0x3a8dc
} // line 24, address 0x3a960
/*
 * Offset 0x3A960
 * D:\driver2\game\C\DENTING.C (line 600)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ LoseHubcap(int Hubcap /*$s3*/, int Velocity /*$a1*/)
{ // line 1, address 0x3a960
	struct _CAR_DATA *car_data_pt; // $s1
	struct SVECTOR InitialLocalAngle; // stack address -64
	{ // line 71, address 0x3aaec
		struct VECTOR R; // stack address -56
		struct VECTOR VW; // stack address -40
		long AY; // $t0
	} // line 81, address 0x3ab48
} // line 94, address 0x3ab94
/*
 * Offset 0x3ABB4
 * D:\driver2\game\C\DENTING.C (line 706)
 * Stack frame base $sp, length 104
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ MoveHubcap()
{ // line 2, address 0x3abb4
	struct _CAR_DATA *car_data_pt; // $a1
	struct VECTOR Position; // stack address -80
	struct MATRIX Orientation; // stack address -64
	struct CVECTOR col; // stack address -32
	int VelocityMagnitude; // $s0
	int CurrentMapHeight; // $a0
	int savecombo; // $s0
	{ // line 25, address 0x3ac60
	} // line 28, address 0x3ac80
	{ // line 32, address 0x3ac90
	} // line 35, address 0x3acc0
	{ // line 56, address 0x3ad0c
	} // line 74, address 0x3ad8c
} // line 99, address 0x3aeac
/*
 * Offset 0x3AEC8
 * D:\driver2\game\C\DENTING.C (line 838)
 * Stack frame base $sp, length 16
 * Saved registers at address -4: s0 s1 s2 s3
 */
void /*$ra*/ ProcessDentLump(char *lump_ptr /*$t2*/, int lump_size /*$a1*/)
{ // line 1, address 0x3aec8
	int i; // $a3
	int model; // $a0
	int address; // $a0
} // line 30, address 0x3b228
/*
 * Offset 0x3B228
 * D:\driver2\game\C\DENTING.C (line 267)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitialiseDenting()
{
}
/*
 * Offset 0x3B258
 * D:\driver2\game\C\DENTING.C (line 815)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ LoadDenting(int level /*$a0*/)
{ // line 2, address 0x3b258
} // line 15, address 0x3b2a8
/*
 * Offset 0x3B2A8
 * D:\driver2\game\C\DENTING.C (line 877)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupSpecDenting(char *loadbuffer /*$a0*/)
{ // line 1, address 0x3b2a8
	char *from; // $a0
	char *to; // $v1
	char *limit; // $a1
} // line 34, address 0x3b34c