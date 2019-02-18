#include "../decomp_defs.h"

int date_date = 0xA11;
int date_time = 0x27220B;

char specTpages[4][12] = {
	{ 0x36, 0x37, 0x42, 0x43, 0x38, 0x39, 0x44, 0x45, 0x3D, 0x40, 0x3D, 0x40},
	{ 0x26, 0x27, 0x26, 0x27, 0x2A, 0x2B, 0x2C, 0x2D, 0x30, 0x31, 0x30, 0x31},
	{ 0x12, 0x13, 0x41, 0x42, 0x43, 0x44, 0xB, 0xC, 0x3F, 0x40, 0x3F, 0x40},
	{ 0x42, 0x43, 0x4D, 0x4E, 0x49, 0x4A, 0x4B, 0x4C, 0x45, 0x46, 0x47, 0x48}
};

char carTpages[4][8] = {
	{1, 0x41, 0x3E, 0x32, 0x3F, 0x3A, 0x36, 0x37},
	{0xA, 0x23, 0x14, 0x25, 0x33, 0x24, 0x26, 0x27},
	{0x29, 0x36, 0x3E, 0x11, 0x20, 0x3B, 0x12, 0},
	{0x37, 0x39, 0x44, 0x3A, 0x3C, 0x3B, 0x42, 0x43}
};

int pvsSize[4] = { 0, 0, 0, 0 };

int SpecialByRegion[4][20] = {
	{5, 1, 3, 3, 2, 2, 2, 3, 3, 3, 3, 1, 1, 1, 2, 3, 2, 2, 3, 0},
	{2, 4, 1, 1, 4, 4, 3, 3, 3, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{2, 4, 1, 1, 1, 1, 1, 1, 4, 2, 3, 3, 5, 0, 0, 0, 0, 0, 0, 0},
	{2, 5, 4, 1, 2, 1, 4, 3, 2, 2, 2, 2, 3, 3, 3, 0, 0, 0, 0, 0},
};

/*
 * Offset 0x7B290
 * D:\driver2\game\C\SPOOL.C (line 532)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ test_changemode()
{ // line 2, address 0x7b290
	struct SPOOLQ *current; // $a3
} // line 56, address 0x7b41c
/*
 * Offset 0x7B42C
 * D:\driver2\game\C\SPOOL.C (line 625)
 * Stack frame base $sp, length 160
 * Saved registers at address -8: s0
 */
int /*$ra*/ check_regions_present()
{ // line 2, address 0x7b42c
	struct AREA_LOAD_INFO regions_to_unpack[3]; // stack address -160
	int leftright_unpack; // $a2
	int topbottom_unpack; // $a3
	int num_regions_to_unpack; // $a1
	int x; // $v1
	int z; // $v0
	int loop; // $t1
	int retval; // $a3
	int region_to_unpack; // $a0
	int barrel_region; // $v1
	char textbuf[128]; // stack address -136
} // line 146, address 0x7b72c
/*
 * Offset 0x7B72C
 * D:\driver2\game\C\SPOOL.C (line 925)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ UpdateSpool()
{ // line 2, address 0x7b72c
	struct SPOOLQ *current; // $s0
	struct CdlLOC pos; // stack address -16
} // line 52, address 0x7b8e4
/*
 * Offset 0x7B8F4
 * D:\driver2\game\C\SPOOL.C (line 1161)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SendTPage()
{ // line 2, address 0x7b8f4
	int tpage2send; // $s2
	int slot; // $s0
	int old; // $v1
	char *tpageaddress; // $t0
	{ // line 15, address 0x7b968
		struct RECT cluts; // stack address -32
		int npalettes; // $s1
		int i; // $a3
		unsigned long *clutptr; // $a1
	} // line 47, address 0x7ba8c
} // line 74, address 0x7bb7c
/*
 * Offset 0x7BB7C
 * D:\driver2\game\C\SPOOL.C (line 1262)
 * Stack frame base $sp, length 128
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ LoadInAreaTSets(int area /*$t4*/)
{ // line 1, address 0x7bb7c
	unsigned char *tpages; // $s1
	int ntpages_to_load; // $s3
	int i; // $s0
	int slot; // $a0
	int j; // $a1
	int address; // $s4
	int availableslots[16]; // stack address -104
	int navailable; // $s2
	char *loadaddr; // $fp
} // line 71, address 0x7bdec
/*
 * Offset 0x7BDEC
 * D:\driver2\game\C\SPOOL.C (line 1337)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ SendSBK()
{ // line 2, address 0x7bdec
	char *address; // $s0
	int slength; // $s1
	int i; // $a1
	unsigned long *source; // $v0
	unsigned long *dest; // $a0
} // line 43, address 0x7bf24
/*
 * Offset 0x7BF24
 * D:\driver2\game\C\SPOOL.C (line 1484)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ init_spooled_models()
{ // line 2, address 0x7bf24
	int i; // $s1
	int nmodels; // $s4
	int length; // $s2
	int model_number; // $a1
	char *addr; // $s0
	struct MODEL *parentmodel; // $a1
	{ // line 35, address 0x7c024
	} // line 37, address 0x7c038
	{ // line 44, address 0x7c06c
	} // line 52, address 0x7c0b0
} // line 59, address 0x7c0f4
/*
 * Offset 0x7C0F4
 * D:\driver2\game\C\SPOOL.C (line 1574)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ CheckLoadAreaData(int cellx /*$t9*/, int cellz /*$a1*/)
{ // line 1, address 0x7c0f4
	int i; // $a2
	int nAreas; // $t0
	struct Spool *spoolptr; // $t1
	int load; // $a3
	int force_load_boundary; // $a0
} // line 92, address 0x7c2e4
/*
 * Offset 0x7C2F4
 * D:\driver2\game\C\SPOOL.C (line 1713)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ LoadRegionData(int region /*$s4*/, int target_region /*$s5*/)
{ // line 1, address 0x7c2f4
	int address; // $s0
	char *target_unpacked_data; // $t1
	struct Spool *spoolptr; // $s1
	char *roadmap_buffer; // $s6
	char *cell_buffer; // $s3
} // line 63, address 0x7c4cc
/*
 * Offset 0x7C4CC
 * D:\driver2\game\C\SPOOL.C (line 1815)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessSpoolInfoLump(char *lump_ptr /*$a2*/, int lump_size /*$a1*/)
{ // line 1, address 0x7c4cc
	int i; // $t2
	int length; // $v1
	int slots_count; // $t0
	int objects_count; // $t1
	int num_of_regions; // $v0
	char *alloclist; // $a3
} // line 103, address 0x7c628
/*
 * Offset 0x7C628
 * D:\driver2\game\C\SPOOL.C (line 2351)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ unpack_cellpointers()
{ // line 2, address 0x7c628
	int target_barrel_region; // $t0
	char *source_packed_data; // $v0
	int bitpos; // $a3
	int loop; // $a2
	int packtype; // $a0
	unsigned short cell; // $a0
	unsigned short *short_ptr; // $a1
	unsigned short pcode; // $t1
} // line 86, address 0x7c7b4
/*
 * Offset 0x7C7B4
 * D:\driver2\game\C\SPOOL.C (line 2509)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SpecClutsSpooled()
{ // line 2, address 0x7c7b4
	char *loadaddr; // $s4
	int i; // $s1
	int j; // $s2
	int tpage; // $s0
	struct RECT specCluts; // stack address -48
	{ // line 13, address 0x7c85c
		int index; // $a3
		{ // line 28, address 0x7c984
		} // line 28, address 0x7c984
	} // line 33, address 0x7c9c4
} // line 37, address 0x7ca20
/*
 * Offset 0x7CA20
 * D:\driver2\game\C\SPOOL.C (line 2549)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ CleanModelSpooled()
{ // line 3, address 0x7ca20
	int *loadaddr; // $a1
	int *mem; // $a3
	{ // line 27, address 0x7cae8
	} // line 38, address 0x7cb38
} // line 42, address 0x7cb64
/*
 * Offset 0x7CB64
 * D:\driver2\game\C\SPOOL.C (line 2594)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DamagedModelSpooled()
{ // line 2, address 0x7cb64
	int *loadaddr; // $a1
	int *mem; // $a3
	{ // line 26, address 0x7cc28
	} // line 35, address 0x7cc60
} // line 39, address 0x7cc8c
/*
 * Offset 0x7CC8C
 * D:\driver2\game\C\SPOOL.C (line 2635)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ LowModelSpooled()
{ // line 2, address 0x7cc8c
	int *loadaddr; // $a1
	int *mem; // $a3
	{ // line 26, address 0x7cd50
	} // line 37, address 0x7cda0
} // line 41, address 0x7cdcc
/*
 * Offset 0x7CDCC
 * D:\driver2\game\C\SPOOL.C (line 2680)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ CleanSpooled()
{ // line 3, address 0x7cdcc
	char *loadaddr; // $a1
	{ // line 22, address 0x7cef4
		struct MODEL *tempModel; // $a1
	} // line 33, address 0x7cf48
} // line 37, address 0x7cf74
/*
 * Offset 0x7CF74
 * D:\driver2\game\C\SPOOL.C (line 2744)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ Tada()
{ // line 2, address 0x7cf74
	char *loadaddr; // $s1
	{ // line 7, address 0x7cfc8
		struct RECT tpage; // stack address -32
		int spec_tpage; // $a0
	} // line 20, address 0x7d080
	{ // line 23, address 0x7d080
		struct RECT tpage; // stack address -24
		int spec_tpage; // $a0
	} // line 36, address 0x7d154
	{ // line 39, address 0x7d154
	} // line 45, address 0x7d198
} // line 49, address 0x7d1ac
/*
 * Offset 0x7D1AC
 * D:\driver2\game\C\SPOOL.C (line 2799)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SpecialStartNextBlock()
{ // line 2, address 0x7d1ac
	char *loadaddr; // $s0
	int fileSector; // $t0
} // line 126, address 0x7d538
/*
 * Offset 0x7D548
 * D:\driver2\game\C\SPOOL.C (line 2956)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ CheckSpecialSpool()
{ // line 2, address 0x7d548
	struct _CAR_DATA *lcp; // $a0
	int ret; // $a3
	{ // line 9, address 0x7d584
	} // line 13, address 0x7d5a4
} // line 66, address 0x7d730
/*
 * Offset 0x7D740
 * D:\driver2\game\C\SPOOL.C (line 3063)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitSpecSpool()
{
}
/*
 * Offset 0x7D9E0
 * D:\driver2\game\C\SPOOL.C (line 2442)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ Unpack_CellPtrs()
{ // line 2, address 0x7d9e0
	int region_to_unpack; // $a1
	int target_barrel_region; // $a1
	char *source_packed_data; // $v1
} // line 27, address 0x7da34
/*
 * Offset 0x7DA34
 * D:\driver2\game\C\SPOOL.C (line 1970)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ GotRegion()
{ // line 2, address 0x7da34
	int cbr; // $a1
} // line 20, address 0x7dac8
/*
 * Offset 0x7DAC8
 * D:\driver2\game\C\SPOOL.C (line 2246)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ data_cb_misc()
{ // line 2, address 0x7dac8
	{ // line 4, address 0x7dadc
		struct SPOOLQ *current; // $v0
	} // line 29, address 0x7db90
} // line 30, address 0x7dba0
/*
 * Offset 0x7DBA0
 * D:\driver2\game\C\SPOOL.C (line 2278)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ready_cb_misc(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
{
}
/*
 * Offset 0x7DC34
 * D:\driver2\game\C\SPOOL.C (line 2171)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ data_cb_soundbank()
{ // line 2, address 0x7dc34
	{ // line 4, address 0x7dc48
	} // line 29, address 0x7dcfc
} // line 30, address 0x7dd0c
/*
 * Offset 0x7DD0C
 * D:\driver2\game\C\SPOOL.C (line 2203)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ready_cb_soundbank(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
{ // line 1, address 0x7dd0c
	{ // line 14, address 0x7dd6c
		struct SPOOLQ *current; // $a0
	} // line 34, address 0x7ddd8
} // line 41, address 0x7de00
/*
 * Offset 0x7DE10
 * D:\driver2\game\C\SPOOL.C (line 2132)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ data_cb_regions()
{ // line 2, address 0x7de10
	{ // line 4, address 0x7de24
		struct SPOOLQ *current; // $v0
	} // line 35, address 0x7dee8
} // line 36, address 0x7def8
/*
 * Offset 0x7DEF8
 * D:\driver2\game\C\SPOOL.C (line 2090)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ready_cb_regions(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
{ // line 1, address 0x7def8
	{ // line 20, address 0x7df70
		struct SPOOLQ *current; // $v1
	} // line 20, address 0x7df70
} // line 39, address 0x7dfcc
/*
 * Offset 0x7DFCC
 * D:\driver2\game\C\SPOOL.C (line 1993)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ data_cb_textures()
{ // line 2, address 0x7dfcc
	{ // line 4, address 0x7dfe0
	} // line 40, address 0x7e0d0
} // line 41, address 0x7e0e0
/*
 * Offset 0x7E0E0
 * D:\driver2\game\C\SPOOL.C (line 2036)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ready_cb_textures(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
{ // line 1, address 0x7e0e0
	{ // line 14, address 0x7e140
		struct SPOOLQ *current; // $a2
	} // line 44, address 0x7e1f0
} // line 50, address 0x7e200
/*
 * Offset 0x7E210
 * D:\driver2\game\C\SPOOL.C (line 591)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ changemode(struct SPOOLQ *current /*$a0*/)
{
}
/*
 * Offset 0x7E2B4
 * D:\driver2\game\C\SPOOL.C (line 836)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ DrawCDicon()
{ // line 2, address 0x7e2b4
	unsigned short *palette; // $a1
	int temp; // $a2
	int i; // $a0
	struct RECT dest; // stack address -16
} // line 20, address 0x7e334
/*
 * Offset 0x7E334
 * D:\driver2\game\C\SPOOL.C (line 859)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ CheckValidSpoolData()
{ // line 2, address 0x7e334
	struct RECT dest; // stack address -16
} // line 59, address 0x7e3c4
/*
 * Offset 0x7E3D4
 * D:\driver2\game\C\SPOOL.C (line 1104)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ RequestSpool(int type /*$a0*/, int data /*$a1*/, int offset /*$a2*/, int loadsize /*$a3*/, char *address /*stack 16*/, void(*func)() /*stack 20*/)
{ // line 1, address 0x7e3d4
	struct SPOOLQ *next; // $t0
	int sector; // $v0
} // line 22, address 0x7e44c
/*
 * Offset 0x7E44C
 * D:\driver2\game\C\SPOOL.C (line 1670)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ ClearRegion(int target_region /*$a0*/)
{ // line 1, address 0x7e44c
	int loop; // $a1
	unsigned short *cell_ptrs_s; // $v1
	unsigned long *pvsptr; // $v0
} // line 41, address 0x7e4fc
/*
 * Offset 0x7E4FC
 * D:\driver2\game\C\SPOOL.C (line 1129)
 * Stack frame base $sp, length 168
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ InitSpooling()
{ // line 2, address 0x7e4fc
	int i; // $s0
	char namebuffer[128]; // stack address -152
	struct CdlLOC pos; // stack address -24
} // line 29, address 0x7e590
/*
 * Offset 0x7E590
 * D:\driver2\game\C\SPOOL.C (line 1239)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SpoolSYNC()
{
}
/*
 * Offset 0x7E5A8
 * D:\driver2\game\C\SPOOL.C (line 1545)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetupModels()
{
}
/*
 * Offset 0x7E5E8
 * D:\driver2\game\C\SPOOL.C (line 1559)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ LoadInAreaModels(int area /*$a0*/)
{ // line 2, address 0x7e5e8
	int address; // $a2
	int length; // $a3
} // line 12, address 0x7e644
/*
 * Offset 0x7E644
 * D:\driver2\game\C\SPOOL.C (line 1779)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ UnpackRegion(int region_to_unpack /*$s1*/, int target_barrel_region /*$s0*/)
{ // line 1, address 0x7e644
} // line 33, address 0x7e6c0
/*
 * Offset 0x7E6D4
 * D:\driver2\game\C\SPOOL.C (line 1928)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ WaitCloseLid()
{ // line 2, address 0x7e6d4
	void(*old)(); // $s1
} // line 14, address 0x7e740
/*
 * Offset 0x7E740
 * D:\driver2\game\C\SPOOL.C (line 1945)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ FoundError(char *name /*$a0*/, unsigned char intr /*$a1*/, unsigned char *result /*$a2*/)
{ // line 2, address 0x7e740
	struct CdlLOC p; // stack address -16
} // line 18, address 0x7e78c
/*
 * Offset 0x7E78C
 * D:\driver2\game\C\SPOOL.C (line 2302)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ StartSpooling()
{ // line 2, address 0x7e78c
} // line 19, address 0x7e818
/*
 * Offset 0x7E828
 * D:\driver2\game\C\SPOOL.C (line 2720)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ LowSpooled()
{ // line 3, address 0x7e828
	char *loadaddr; // $v1
	{ // line 8, address 0x7e840
		struct MODEL *tempModel; // $a1
	} // line 17, address 0x7e888
} // line 21, address 0x7e8b4
/*
 * Offset 0x7E8B4
 * D:\driver2\game\C\SPOOL.C (line 3025)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ QuickSpoolSpecial()
{
}
/*
 * Offset 0x7E944
 * D:\driver2\game\C\SPOOL.C (line 3046)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ PrepareSecretCar()
{
}
/*
 * Offset 0x7E9C0
 * D:\driver2\game\C\SPOOL.C (line 818)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ stopgame()
{ // line 4, address 0x7e9c0
} // line 9, address 0x7ea08
/*
 * Offset 0x7EA08
 * D:\driver2\game\C\SPOOL.C (line 829)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ startgame()
{ // line 2, address 0x7ea08
} // line 4, address 0x7ea38