/*
#include "mips_hw_intpret.h"
#include "decomp_defs.h"

void ProcessSpoolInfoLump1(char *lump_ptr, int lump_size)
{
	int i; // _t2
	int length; // _v1
	int slots_count; // _t0
	int objects_count; // _t1
	int num_of_regions; // _v0
	char *alloclist; // _a3

	move(_a2, _a0);
	//lui(_v0, 0xA);
	//addiu(_a1, _v0, pvsSize);0
	la(_a1, pvsSize);
	sw(_zero, (ubyte*)pvsSize);
	sw(_zero, (ubyte*)pvsSize + 4);
	sw(_zero, (ubyte*)pvsSize + 8);
	sw(_zero, (ubyte*)pvsSize + 0xC);
	la(_v1, lump_ptr);
	li(_v0, -1);
	la(_a0, mallocptr);
	sll(_v1, _v1, 0xB);
	slt(_v0, _v0, _v1);
	sw(_a0, model_spool_buffer);
	addiu(_a2, _a2, 4);
	if (bnez(_v0))
	{
		lui(_v1, 1);
	}
	addu(_v1, _a0, _v1);
	move(_a3, _v1);
	move(_t0, _zero);
	move(_t1, _zero);
	li(_t7, -0x800);
	move(_t6, _a1);

	la(_t9, cell_objects_add);
	la(_t4, cell_slots_add);
	la(_t3, PVS_Buffers);
	li(_t2, 3);

	sw(_v1, mallocptr);
	lw(_v1, (uint32*)uregv(_a2));
	addiu(_v0, _a2, 4);
	sw(_v0, &Music_And_AmbientOffsets);
	addiu(_v1, _v1, 4);
	addu(_a2, _a2, _v1);
	lw(_a0, (uint32*)uregv(_a2));
	addiu(_v0, _a2, 4);
	sw(_v0, &AreaData);
	sll(_v1, _a0, 4);
	addiu(_v0, _v1, 4);
	addu(_a2, _a2, _v0);
	sw(_a2, &AreaTPages);
	addu(_a2, _a2, _v1);
	move(_a1, _a2);
	sw(_a0, &NumAreas);
}
*/

#include "decomp_defs.h"
#include "mips_hw_intpret.h"

uint32 _registers[allregs] = { 0 };

int levelstartpos[8][4] = {
	{0x12B1, 0xFFFFFC00, 0xFFFC9794, 0},
	{0xFFFC74AC, 0x800, 0xFFFC6961, 0},
	{0x383CB, 0xFFFFFC00, 0xABE1E, 0},
	{0x165EF, 0xFFFFFC00, 0xFFFAB3D9, 0},
	{0x24548, 0x1813, 0xFFFE4A80, 0},
	{ 0xFFFD67F0, 0x1813, 0x58228, 0},
	{ 0xFFFFD6FC, 0xFFFFE7ED, 0xFFFFA980, 0},
	{ 0xFFFFDCDD, 0xFFFFE7ED, 0xF8A7, 0},
};


/*
 * Offset 0x58C70
 * D:\driver2\game\C\MAIN.C (line 2672)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ ProcessLumps(char *lump_ptr /*$s1*/, int lump_size /*$a1*/)
{ // line 1, address 0x58c70
	int quit; // $s3
	int lump_type; // $v1
	int seg_size; // $s0
	{ // line 14, address 0x58dfc
		{ // line 173, address 0x58fe4
			struct DRIVER2_JUNCTION *dst; // $a0
			unsigned long *src; // $a2
			int i; // $v1
		} // line 186, address 0x5902c
		{ // line 193, address 0x59034
			struct DRIVER2_JUNCTION *dst; // $a0
			unsigned long *src; // $a2
			int i; // $v1
		} // line 206, address 0x59080
	} // line 218, address 0x5908c
} // line 222, address 0x590b8
/*
 * Offset 0x590B8
 * D:\driver2\game\C\MAIN.C (line 2896)
 * Stack frame base $sp, length 112
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ LoadGameLevel()
{ // line 2, address 0x590b8
	int sector; // stack address -32
	int nsectors; // $s1
	char name[64]; // stack address -96
	char *malloc_lump; // $s2
} // line 71, address 0x592a0
/*
 * Offset 0x592A0
 * D:\driver2\game\C\MAIN.C (line 3003)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ InitModelNames()
{ // line 2, address 0x592a0
} // line 64, address 0x59398
/*
 * Offset 0x59398
 * D:\driver2\game\C\MAIN.C (line 3114)
 * Stack frame base $sp, length 80
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ GameInit()
{ // line 8, address 0x59398
	{ // line 112, address 0x59528
	} // line 114, address 0x5953c
	{ // line 149, address 0x5961c
	} // line 149, address 0x5961c
	{ // line 157, address 0x59644
	} // line 163, address 0x5966c
	{ // line 191, address 0x59718
		struct STREAM_SOURCE *pinfo; // $s0
		char padid; // stack address -48
		int i; // $s2
	} // line 245, address 0x59874
	{ // line 328, address 0x599ac
		int loop; // $s0
		{ // line 331, address 0x599b4
		} // line 331, address 0x599b4
	} // line 333, address 0x599d4
	{ // line 341, address 0x599f4
		int i; // $v1
	} // line 346, address 0x59a20
	{ // line 350, address 0x59a20
	} // line 361, address 0x59a20
	{ // line 390, address 0x59a74
	} // line 392, address 0x59a7c
} // line 395, address 0x59aac
/*
 * Offset 0x59AAC
 * D:\driver2\game\C\MAIN.C (line 3555)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ StepSim()
{ // line 2, address 0x59aac
	static unsigned long t0; // address 0x0
	static char t1; // address 0x4
	static char t2; // address 0x5
	static int oldsp; // address 0x8
	struct _CAR_DATA *lcp; // $s0
	int i; // $s2
	{ // line 78, address 0x59cd8
		int eekTimer; // $s0
		{ // line 84, address 0x59d2c
		} // line 86, address 0x59d2c
	} // line 90, address 0x59d88
	{ // line 94, address 0x59dd4
	} // line 98, address 0x59dd4
	{ // line 1, address 0x5a040
	} // line 1, address 0x5a040
	{ // line 283, address 0x5a288
		int padsteer; // $a1
		{ // line 313, address 0x5a388
		} // line 317, address 0x5a3a4
		{ // line 324, address 0x5a3dc
		} // line 324, address 0x5a3dc
	} // line 324, address 0x5a3dc
	{ // line 331, address 0x5a3fc
	} // line 333, address 0x5a430
	{ // line 428, address 0x5a6b8
		int i; // $s1
		int j; // $s0
		static int stupid_logic[4]; // address 0x0
		{ // line 448, address 0x5a7ac
		} // line 450, address 0x5a7fc
	} // line 451, address 0x5a818
	{ // line 478, address 0x5a8fc
	} // line 481, address 0x5a914
} // line 484, address 0x5a944
/*
 * Offset 0x5A944
 * D:\driver2\game\C\MAIN.C (line 4046)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ GameLoop()
{ // line 2, address 0x5a944
	int i; // $s0
	struct RECT dest; // stack address -24
	{ // line 79, address 0x5aa94
		static struct POLY_FT3 buffer[2]; // address 0x10
		static struct POLY_FT3 *null; // address 0xc
	} // line 94, address 0x5ab00
} // line 142, address 0x5ab90
/*
 * Offset 0x5AB90
 * D:\driver2\game\C\MAIN.C (line 4196)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ StepGame()
{ // line 2, address 0x5ab90
	{ // line 42, address 0x5abc8
	} // line 44, address 0x5abd8
	{ // line 56, address 0x5ac40
		int i; // $a1
	} // line 66, address 0x5aca4
	{ // line 140, address 0x5ae88
	} // line 149, address 0x5aeb8
	{ // line 165, address 0x5af28
	} // line 172, address 0x5af38
	{ // line 199, address 0x5afd4
		int strobe; // $v0
	} // line 202, address 0x5b020
	{ // line 340, address 0x5b34c
	} // line 342, address 0x5b384
} // line 351, address 0x5b3ec
/*
 * Offset 0x5B3EC
 * D:\driver2\game\C\MAIN.C (line 4767)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: ra
 */
int /*$ra*/ main()
{ // line 1, address 0x5b3ec
	{ // line 1, address 0x5b3ec
		{ // line 1, address 0x5b3ec
			char *PALScreenNames[4]; // stack address -24
			char *NTSCScreenNames[4]; // stack address -40
			char *OPMScreenNames[4]; // stack address -56
		} // line 1, address 0x5b3ec
	} // line 1, address 0x5b3ec
} // line 101, address 0x5b5b4
/*
 * Offset 0x5B5B4
 * D:\driver2\game\C\MAIN.C (line 4893)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ UpdatePlayerInformation()
{ // line 2, address 0x5b5b4
	struct _CAR_DATA *cp; // $s1
	int count; // $s0
	int scale; // $v1
	int wheel; // $t1
	int wheelsonwater; // $t2
} // line 79, address 0x5b8f0
/*
 * Offset 0x5B8F0
 * D:\driver2\game\C\MAIN.C (line 5021)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ RenderGame2(int view /*$s3*/)
{ // line 1, address 0x5b8f0
	int spaceFree; // $a1
	int notInDreaAndStevesEvilLair; // $s0
	{ // line 46, address 0x5ba0c
		int strobe; // $v0
	} // line 49, address 0x5ba54
	{ // line 52, address 0x5ba54
		int i; // $s1
	} // line 56, address 0x5baec
	{ // line 69, address 0x5bb4c
		struct POLY_F4 *poly; // $v1
		int col; // $a1
	} // line 92, address 0x5bc88
	{ // line 100, address 0x5bca8
	} // line 104, address 0x5bcf0
} // line 111, address 0x5bd4c
/*
 * Offset 0x5BD4C
 * D:\driver2\game\C\MAIN.C (line 5272)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ InitGameVariables()
{ // line 2, address 0x5bd4c
} // line 69, address 0x5bfdc
/*
 * Offset 0x5BFDC
 * D:\driver2\game\C\MAIN.C (line 5345)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ DealWithHorn(char *hr /*$s2*/, int i /*$s1*/)
{ // line 1, address 0x5bfdc
	struct _CAR_DATA *car; // $s0
	{ // line 3, address 0x5c07c
	} // line 18, address 0x5c18c
} // line 20, address 0x5c1bc
/*
 * Offset 0x5C1D4
 * D:\driver2\game\C\MAIN.C (line 5367)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ Havana3DOcclusion(void(*func)() /*$a3*/, int *param /*$fp*/)
{ // line 1, address 0x5c1d4
	int outside; // $s6
	int otAltered; // $s5
	{ // line 12, address 0x5c270
		int draw; // $s2
		int loop; // $s0
	} // line 106, address 0x5c47c
} // line 113, address 0x5c4c0
/*
 * Offset 0x5C4C0
 * D:\driver2\game\C\MAIN.C (line 4549)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DrawGame()
{ // line 2, address 0x5c4c0
	static unsigned long frame; // address 0xc8
	{ // line 6, address 0x5c4e8
	} // line 12, address 0x5c538
	{ // line 18, address 0x5c554
	} // line 28, address 0x5c5bc
} // line 34, address 0x5c5dc
/*
 * Offset 0x5C5DC
 * D:\driver2\game\C\MAIN.C (line 4586)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ EndGame(enum GAMEMODE mode /*$a0*/)
{
}
/*
 * Offset 0x5C5F8
 * D:\driver2\game\C\MAIN.C (line 4593)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ EnablePause(enum PAUSEMODE mode /*$a0*/)
{
}
/*
 * Offset 0x5C638
 * D:\driver2\game\C\MAIN.C (line 4602)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ CheckForPause()
{ // line 2, address 0x5c638
	{ // line 1, address 0x5c64c
	} // line 1, address 0x5c67c
} // line 16, address 0x5c6d0
/*
 * Offset 0x5C6D0
 * D:\driver2\game\C\MAIN.C (line 4870)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ FadeScreen(int end_value /*$a1*/)
{ // line 1, address 0x5c6d0
	int tmp2; // $s1
} // line 18, address 0x5c748
/*
 * Offset 0x5C748
 * D:\driver2\game\C\MAIN.C (line 5260)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ RenderGame()
{ // line 2, address 0x5c748
	{ // line 2, address 0x5c748
		{ // line 2, address 0x5c748
			static unsigned long frame; // address 0xc8
			{ // line 1, address 0x5c77c
			} // line 1, address 0x5c7cc
			{ // line 1, address 0x5c7e8
			} // line 1, address 0x5c850
		} // line 1, address 0x5c850
	} // line 1, address 0x5c850
} // line 9, address 0x5c884
/*
 * Offset 0x5C884
 * D:\driver2\game\C\MAIN.C (line 2973)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ ReplayLog_Fnarr_He_Said_Log(int val /*$a0*/)
{
}