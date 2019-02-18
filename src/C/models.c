#include "../decomp_defs.h"

/*
 * Offset 0x64D64
 * D:\driver2\game\C\MODELS.C (line 33)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessMDSLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{ // line 1, address 0x64d64
	int i; // $a2
	int length; // $v0
	int modelamt; // $a3
	char *mdsfile; // $a0
	struct MODEL *model; // $a0
	struct MODEL *parentmodel; // $a1
} // line 61, address 0x64ed4
/*
 * Offset 0x64ED4
 * D:\driver2\game\C\MODELS.C (line 212)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ ProcessCarModelLump(char *lump_ptr /*$s2*/, int lump_size /*$a1*/)
{ // line 2, address 0x64ed4
	int address; // $a0
	int i; // $s3
	int car_model; // $a0
	int specMemReq; // $s4
	{ // line 19, address 0x64f18
		struct MODEL *model; // $v0
		int mem; // $a1
	} // line 74, address 0x64ff0
} // line 136, address 0x6519c
/*
 * Offset 0x6519C
 * D:\driver2\game\C\MODELS.C (line 391)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
struct MODEL * /*$ra*/ GetCarModel(char *src /*$s2*/, char **dest /*$s1*/, int KeepNormals /*$s3*/)
{ // line 1, address 0x6519c
	struct MODEL *model; // $s0
	int length; // $a2
	char *mem; // $v1
	{ // line 28, address 0x65204
	} // line 38, address 0x65254
} // line 41, address 0x65274