
#include "../decomp_defs.h"

char missionstarts[42] = { 
	0xFF, 0xFF, 0, 2, 4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	6, 8, 0xFF, 9, 0xFF, 0xC, 0xD, 0xFF, 0xE, 0xFF, 0x13,
	0x14, 0xFF, 0x15, 0x18, 0x1A, 0xFF, 0x1C, 0xFF, 0x1E,
	0x21, 0xFF, 0x25, 0x27, 0xFF, 0x29, 0xFF, 0xFF, 0xFF,
	0x2E, 0x30, 0x31 
};

io id_map[49] =
{
	{0, 0},
	{0, 1},
	{2, 0},
	{3, 1},
	{4, 0},
	{5, 1},
	{4, 0},
	{5, 1},
	{11, 0},
	{12, 0},
	{12, 1},
	{11, 2},
	{14, 0},
	{14, 0},
	{15, 0},
	{16, 1},
	{16, 2},
	{18, 3},
	{18, 4},
	{11, 0},
	{11, 0},
	{20, 0},
	{12, 1},
	{13, 2},
	{21, 0},
	{31, 1},
	{31, 0},
	{11, 1},
	{23, 0},
	{24, 1},
	{26, 0},
	{27, 1},
	{28, 2},
	{34, 0},
	{29, 1},
	{29, 2},
	{20, 3},
	{31, 0},
	{11, 1},
	{31, 0},
	{33, 1},
	{34, 0},
	{36, 1},
	{29, 2},
	{29, 3},
	{20, 4},
	{37, 0},
	{38, 1},
	{39, 0},
};

xa_request xa_data[26] = {
	{0x10, 0, 0, 1, 0},
	{0x19, 0, 1, 2, 0},
	{0x1E, 0, 2, 3, 0},
	{0x26, 0, 3, 4, 0},
	{0x10, 0, 4, 9, 0},
	{0x82, 0, 5, 0xA, 0},
	{0x5A, 0, 6, 0xD, 0},
	{0x10, 0, 7, 0xE, 0},
	{0x280, 1, 0, 0x12, 1},
	{0x10, 1, 1, 0x16, 0},
	{0x1C2, 1, 2, 0x17, 0},
	{0x10, 1, 3, 0x19, 0},
	{0x10, 1, 4, 0x1A, 0},
	{0x14, 1, 5, 0x1B, 0},
	{0x28, 1, 6, 0x1C, 0},
	{0x15E, 1, 7, 0x1D, 1},
	{0x10, 2, 0, 0x1D, 0},
	{0x10, 2, 1, 0x1E, 0},
	{0x96, 2, 2, 0x1F, 0},
	{0x10, 2, 3, 0x20, 0},
	{0x10, 2, 4, 0x22, 0},
	{0x19, 2, 5, 0x23, 0},
	{0x10, 2, 6, 0x25, 0},
	{0x10, 2, 7, 0x27, 0},
	{0x2EE, 3, 0, 0x21, 1},
	{0, 0, 0, 0xFF, 0},
};

/*
 * Offset 0x5D87C
 * D:\driver2\game\C\MC_SND.C (line 88)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
char /*$ra*/ GetMissionSound(char id /*$s1*/)
{ // line 1, address 0x5d87c
	char c; // $s0
	char start; // $s2
	char end; // $a0
	char rnd; // $t1
} // line 18, address 0x5d9b8
/*
 * Offset 0x5D9B8
 * D:\driver2\game\C\MC_SND.C (line 187)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ DoCutsceneSound()
{ // line 1, address 0x5d9b8
	{ // line 4, address 0x5da04
		{ // line 37, address 0x5daf0
			{ // line 39, address 0x5db18
				long *here; // $t0
			} // line 41, address 0x5db54
		} // line 42, address 0x5db54
		{ // line 57, address 0x5dc04
			{ // line 58, address 0x5dc14
				struct _CAR_DATA *you; // $s0
			} // line 61, address 0x5dc58
		} // line 63, address 0x5dc84
	} // line 82, address 0x5dd68
} // line 84, address 0x5dd78
/*
 * Offset 0x5DD78
 * D:\driver2\game\C\MC_SND.C (line 279)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ InitializeMissionSound()
{ // line 1, address 0x5dd78
	int i; // $a1
} // line 29, address 0x5e088
/*
 * Offset 0x5E088
 * D:\driver2\game\C\MC_SND.C (line 321)
 * Stack frame base $sp, length 128
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DoMissionSound()
{ // line 1, address 0x5e088
	int i; // $a2
	{ // line 79, address 0x5e24c
		long *pos; // $s5
		long *vel; // $s4
		{ // line 83, address 0x5e2c4
			int chan; // $s1
		} // line 83, address 0x5e2c4
	} // line 83, address 0x5e2c4
	{ // line 154, address 0x5e3b0
		struct VECTOR Q[3]; // stack address -96
		struct VECTOR P; // stack address -48
	} // line 157, address 0x5e478
	{ // line 159, address 0x5e48c
		int i; // $s0
	} // line 163, address 0x5e620
	{ // line 202, address 0x5e758
		struct VECTOR Q[3]; // stack address -96
		struct VECTOR P; // stack address -48
	} // line 205, address 0x5e820
	{ // line 207, address 0x5e834
		int i; // $s0
	} // line 211, address 0x5e9d0
	{ // line 236, address 0x5eadc
		long V[3]; // stack address -96
		long *C; // $a1
	} // line 245, address 0x5ec00
} // line 307, address 0x5ee68
/*
 * Offset 0x5EE68
 * D:\driver2\game\C\MC_SND.C (line 652)
 * Stack frame base $sp, length 0
 */
char /*$ra*/ SilenceThisCar(int car /*$a1*/)
{
}
/*
 * Offset 0x5F194
 * D:\driver2\game\C\MC_SND.C (line 145)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ RequestXA()
{ // line 1, address 0x5f194
} // line 12, address 0x5f21c
/*
 * Offset 0x5F21C
 * D:\driver2\game\C\MC_SND.C (line 164)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ HandleRequestedXA()
{ // line 2, address 0x5f21c
} // line 6, address 0x5f28c
/*
 * Offset 0x5F28C
 * D:\driver2\game\C\MC_SND.C (line 176)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitializeCutsceneSound(int cutscene /*$a0*/)
{ // line 1, address 0x5f28c
	int i; // $a0
} // line 5, address 0x5f2c4
/*
 * Offset 0x5F2C4
 * D:\driver2\game\C\MC_SND.C (line 636)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetMSoundVar(int var /*$a0*/, struct VECTOR *V /*$a1*/)
{
}
/*
 * Offset 0x5F2FC
 * D:\driver2\game\C\MC_SND.C (line 749)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ AdjustPlayerCarVolume()
{
}