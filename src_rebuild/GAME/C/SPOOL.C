#include "THISDUST.H"
#include "SPOOL.H"
#include "MAP.H"
#include "SYSTEM.H"
#include "MAIN.H"
#include "XAPLAY.H"
#include "DIRECTOR.H"

int date_date = 0xA11;
int date_time = 0x27220B;

int pvsSize[4] = { 0, 0, 0, 0 };

int SpecialByRegion[4][20] = {
	{5, 1, 3, 3, 2, 2, 2, 3, 3, 3, 3, 1, 1, 1, 2, 3, 2, 2, 3, 0},
	{2, 4, 1, 1, 4, 4, 3, 3, 3, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{2, 4, 1, 1, 1, 1, 1, 1, 4, 2, 3, 3, 5, 0, 0, 0, 0, 0, 0, 0},
	{2, 5, 4, 1, 2, 1, 4, 3, 2, 2, 2, 2, 3, 3, 3, 0, 0, 0, 0, 0},
};

char* PVS_Buffers[4];

char* model_spool_buffer = NULL;

int cell_objects_add[5];
int cell_slots_add[5];

SXYPAIR* Music_And_AmbientOffsets;

AreaDataStr* AreaData;
unsigned char* AreaTPages;
int NumAreas;

char* RegionSpoolInfo;
unsigned short *spoolinfo_offsets;

char* specmallocptr;
char *specLoadBuffer;

int doSpooling = 1;

short loading_region[4];
int regions_unpacked[4];

int spool_regioncounter;
int spoolerror;	// UNUSED
int spool_regionpos;
int spoolactive;
int models_ready;

int tsetcounter;
int tsetpos;

int spoolcounter;
int spoolseek;		// Probably UNUSED

int loadbank_read;
int loadbank_write;

int spoolpos;
int spoolpos_reading;
int spoolpos_writing;

int unpack_roadmap_flag;
int unpack_cellptr_flag;

char *packed_cell_pointers;
SPL_REGIONINFO spool_regioninfo[8];
unsigned long unpack_cellptr_tbl[3];

// decompiled code
// original method signature: 
// void /*$ra*/ test_changemode()
 // line 532, offset 0x0007b228
	/* begin block 1 */
		// Start line: 534
		// Start offset: 0x0007B228
		// Variables:
	// 		struct SPOOLQ *current; // $a3
	/* end block 1 */
	// End offset: 0x0007B3B4
	// End Line: 588

	/* begin block 2 */
		// Start line: 1064
	/* end block 2 */
	// End Line: 1065

	/* begin block 3 */
		// Start line: 1065
	/* end block 3 */
	// End Line: 1066

	/* begin block 4 */
		// Start line: 1067
	/* end block 4 */
	// End Line: 1068

/* WARNING: Unknown calling convention yet parameter storage is locked */

void test_changemode(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;

	if (spoolpos_reading == spoolcounter) {
		switch_spooltype = 0;
		CdReadyCallback(0);
		CdControlF(9, 0);
	}
	else {
		if (current_sector == spooldata[spoolpos_reading].sector) {
			target_address = spooldata[spoolpos_reading].addr;
			bVar1 = spooldata[spoolpos_reading].type;
			switch_spooltype = 1;
			if (bVar1 == 1) {
				sectors_to_read = 0x11;
				target_address = target_address + 0x4000;
				nTPchunks_reading = 0;
				nTPchunks_writing = 0;
				ntpages = tsetcounter;
				sectors_this_chunk = (uint)bVar1;
				CdReadyCallback(ready_cb_textures);
			}
			else {
				if (bVar1 < 2) {
					if (bVar1 == 0) {
						sectors_to_read = spool_regioninfo[spool_regionpos + 1].nsectors;
						sectors_this_chunk = ZEXT24(spooldata[spoolpos_reading].nsectors);
						CdReadyCallback(ready_cb_regions);
					}
				}
				else {
					if (bVar1 == 2) {
						sectors_to_read = ZEXT24(spooldata[spoolpos_reading].nsectors);
						send_bank = ZEXT14(spooldata[spoolpos_reading].data);
						sample_chunk = 0;
						nTPchunks_reading = 0;
						nTPchunks_writing = 0;
						target_address = target_address + (loadbank_read & 1U) * 0x1000;
						sectors_this_chunk = (uint)bVar1;
						CdReadyCallback(ready_cb_soundbank);
					}
					else {
						if (bVar1 == 3) {
							sectors_to_read = ZEXT24(spooldata[spoolpos_reading].nsectors);
							CdReadyCallback(ready_cb_misc);
						}
					}
				}
			}
		}
		else {
			switch_spooltype = 0;
			CdReadyCallback(0);
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ changemode(struct SPOOLQ *current /*$a0*/)
 // line 591, offset 0x0007e1a8
	/* begin block 1 */
		// Start line: 1182
	/* end block 1 */
	// End Line: 1183

	/* begin block 2 */
		// Start line: 5397
	/* end block 2 */
	// End Line: 5398

void changemode(SPOOLQ *current)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;

	switch_spooltype = 0;
	endchunk = 0;
	bVar1 = current->type;
	if (bVar1 == 1) {
		CdDataCallback(data_cb_textures);
	}
	else {
		if (bVar1 < 2) {
			if (bVar1 == 0) {
				CdDataCallback(data_cb_regions);
			}
		}
		else {
			if (bVar1 == 2) {
				CdDataCallback(data_cb_soundbank);
			}
			else {
				if (bVar1 == 3) {
					CdDataCallback(data_cb_misc);
				}
			}
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ check_regions_present()
 // line 625, offset 0x0007b3c4
	/* begin block 1 */
		// Start line: 627
		// Start offset: 0x0007B3C4
		// Variables:
	// 		struct AREA_LOAD_INFO regions_to_unpack[3]; // stack offset -160
	// 		int leftright_unpack; // $a2
	// 		int topbottom_unpack; // $a3
	// 		int num_regions_to_unpack; // $a1
	// 		int x; // $v1
	// 		int z; // $v0
	// 		int loop; // $t1
	// 		int retval; // $a3
	// 		int region_to_unpack; // $a0
	// 		int barrel_region; // $v1
	// 		char textbuf[128]; // stack offset -136
	/* end block 1 */
	// End offset: 0x0007B6C4
	// End Line: 771

	/* begin block 2 */
		// Start line: 1267
	/* end block 2 */
	// End Line: 1268

	/* begin block 3 */
		// Start line: 1268
	/* end block 3 */
	// End Line: 1269

	/* begin block 4 */
		// Start line: 1269
	/* end block 4 */
	// End Line: 1270

/* WARNING: Unknown calling convention yet parameter storage is locked */

int check_regions_present(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int *piVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int *piVar6;
	int local_a0[5];
	undefined4 local_8c;

	piVar6 = local_a0;
	iVar4 = 0;
	iVar5 = 0;
	iVar3 = 0;
	if (current_barrel_region_xcell < 9) {
		local_a0[0] = -1;
		if (region_x != 0) {
			iVar4 = 1;
		LAB_0007b44c:
			iVar3 = 1;
			local_a0[1] = 0;
		}
	}
	else {
		if (0x17 < current_barrel_region_xcell) {
			iVar2 = cells_across;
			if (cells_across < 0) {
				iVar2 = cells_across + 0x1f;
			}
			local_a0[0] = 1;
			if (region_x < iVar2 >> 5) {
				iVar4 = 2;
				goto LAB_0007b44c;
			}
		}
	}
	if (current_barrel_region_zcell < 9) {
		if (region_z == 0) goto LAB_0007b4e0;
		iVar5 = 1;
		piVar1 = local_a0 + iVar3 * 2 + 1;
		local_a0[iVar3 * 2] = 0;
		iVar2 = -1;
	}
	else {
		if ((current_barrel_region_zcell < 0x18) || (region_z == 0)) goto LAB_0007b4e0;
		iVar5 = 2;
		piVar1 = local_a0 + iVar3 * 2 + 1;
		local_a0[iVar3 * 2] = 0;
		iVar2 = 1;
	}
	iVar3 = iVar3 + 1;
	*piVar1 = iVar2;
LAB_0007b4e0:
	if (iVar3 == 2) {
		if (iVar5 == 1) {
			iVar3 = 3;
			if (iVar4 == 1) {
				local_a0[4] = 0xffffffff;
				local_8c = 0xffffffff;
			}
			else {
				local_a0[4] = 1;
				local_8c = 0xffffffff;
			}
		}
		else {
			iVar3 = 3;
			if (iVar4 == 1) {
				local_a0[4] = 0xffffffff;
			}
			else {
				local_a0[4] = 1;
			}
			local_8c = 1;
		}
	}
	iVar4 = 0;
	while (iVar3 != 0) {
		iVar5 = cells_across;
		if (cells_across < 0) {
			iVar5 = cells_across + 0x1f;
		}
		iVar5 = current_region + *piVar6 + piVar6[1] * (iVar5 >> 5);
		if ((((int)loading_region[(region_x + *piVar6 & 1U) + (region_z + piVar6[1] & 1U) * 2] != -1) &&
			(spoolinfo_offsets[iVar5] != 0xffff)) &&
			((int)loading_region[(region_x + *piVar6 & 1U) + (region_z + piVar6[1] & 1U) * 2] == iVar5))
		{
			iVar4 = iVar4 + 1;
		}
		iVar3 = iVar3 + -1;
		piVar6 = piVar6 + 2;
	}
	if (LoadingArea != 0) {
		if (new_area_location == 1) {
			if (0x1a < current_barrel_region_xcell) {
				iVar4 = iVar4 + 1;
			}
		}
		else {
			if (new_area_location < 2) {
				if ((new_area_location == 0) && (0x1a < current_barrel_region_zcell)) {
					iVar4 = iVar4 + 1;
				}
			}
			else {
				iVar3 = current_barrel_region_zcell;
				if (((new_area_location == 2) ||
					(iVar3 = current_barrel_region_xcell, new_area_location == 3)) && (iVar3 < 6)) {
					iVar4 = iVar4 + 1;
				}
			}
		}
	}
	return iVar4;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ stopgame()
 // line 818, offset 0x0007e958
	/* begin block 1 */
		// Start line: 822
		// Start offset: 0x0007E958
	/* end block 1 */
	// End offset: 0x0007E9A0
	// End Line: 827

	/* begin block 2 */
		// Start line: 1636
	/* end block 2 */
	// End Line: 1637

	/* begin block 3 */
		// Start line: 8809
	/* end block 3 */
	// End Line: 8810

/* WARNING: Unknown calling convention yet parameter storage is locked */

void stopgame(void)
{
	UNIMPLEMENTED();
	/*
	StopPadVibration(0);
	StopPadVibration(1);
	PauseSFX();
	DrawSync(0);
	PutDrawEnv(&last->draw);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ startgame()
 // line 829, offset 0x0007e9a0
	/* begin block 1 */
		// Start line: 831
		// Start offset: 0x0007E9A0
	/* end block 1 */
	// End offset: 0x0007E9D0
	// End Line: 833

	/* begin block 2 */
		// Start line: 8825
	/* end block 2 */
	// End Line: 8826

	/* begin block 3 */
		// Start line: 8828
	/* end block 3 */
	// End Line: 8829

	/* begin block 4 */
		// Start line: 8829
	/* end block 4 */
	// End Line: 8830

/* WARNING: Unknown calling convention yet parameter storage is locked */

void startgame(void)
{
	UNIMPLEMENTED();
	/*
	PutDrawEnv(&current->draw);
	UnPauseSFX();
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCDicon()
 // line 836, offset 0x0007e24c
	/* begin block 1 */
		// Start line: 838
		// Start offset: 0x0007E24C
		// Variables:
	// 		unsigned short *palette; // $a1
	// 		int temp; // $a2
	// 		int i; // $a0
	// 		struct RECT dest; // stack offset -16
	/* end block 1 */
	// End offset: 0x0007E2CC
	// End Line: 856

	/* begin block 2 */
		// Start line: 5885
	/* end block 2 */
	// End Line: 5886

	/* begin block 3 */
		// Start line: 5886
	/* end block 3 */
	// End Line: 5887

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DrawCDicon(void)
{
	UNIMPLEMENTED();
	/*
	undefined2 *puVar1;
	int iVar2;
	undefined2 local_10;
	undefined2 local_e;
	undefined2 local_c;
	undefined2 local_a;

	DAT_0009bba2 = DAT_0009bb8a;
	iVar2 = 0xb;
	puVar1 = &DAT_0009bb88;
	do {
		iVar2 = iVar2 + -1;
		puVar1[1] = puVar1[2];
		puVar1 = puVar1 + 1;
	} while (-1 < iVar2);
	local_10 = 0x3c0;
	local_e = 0x1b1;
	local_c = 0x10;
	local_a = 1;
	LoadImage(&local_10);
	DrawPrim(&cd_sprite);
	DrawSync(0);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckValidSpoolData()
 // line 859, offset 0x0007e2cc
	/* begin block 1 */
		// Start line: 861
		// Start offset: 0x0007E2CC
		// Variables:
	// 		struct RECT dest; // stack offset -16
	/* end block 1 */
	// End offset: 0x0007E35C
	// End Line: 918

	/* begin block 2 */
		// Start line: 5946
	/* end block 2 */
	// End Line: 5947

	/* begin block 3 */
		// Start line: 5950
	/* end block 3 */
	// End Line: 5951

	/* begin block 4 */
		// Start line: 5951
	/* end block 4 */
	// End Line: 5952

	/* begin block 5 */
		// Start line: 5962
	/* end block 5 */
	// End Line: 5963

/* WARNING: Unknown calling convention yet parameter storage is locked */

void CheckValidSpoolData(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	if (models_ready != 0) {
		init_spooled_models();
	}
	if ((spoolactive != 0) && (iVar1 = check_regions_present(), iVar1 != 0)) {
		stopgame();
		while (spoolactive != 0) {
			DrawCDicon();
			VSync(0);
		}
		startgame();
		PutDrawEnv(&current->draw);
		UnPauseSFX();
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateSpool()
 // line 925, offset 0x0007b6c4
	/* begin block 1 */
		// Start line: 927
		// Start offset: 0x0007B6C4
		// Variables:
	// 		struct SPOOLQ *current; // $s0
	// 		struct CdlLOC pos; // stack offset -16
	/* end block 1 */
	// End offset: 0x0007B87C
	// End Line: 977

	/* begin block 2 */
		// Start line: 1793
	/* end block 2 */
	// End Line: 1794

	/* begin block 3 */
		// Start line: 1903
	/* end block 3 */
	// End Line: 1904

	/* begin block 4 */
		// Start line: 1904
	/* end block 4 */
	// End Line: 1905

	/* begin block 5 */
		// Start line: 1908
	/* end block 5 */
	// End Line: 1909

/* WARNING: Unknown calling convention yet parameter storage is locked */

static int sectors_this_chunk;
static int sectors_to_read;
static char *target_address;

static int nTPchunks_reading;
static int nTPchunks_writing;
static int ntpages;
static int current_sector;
static int switch_spooltype;

static int endchunk;
int send_bank;
int sample_chunk;

struct SPOOLQ spooldata[48];

// [D]
void UpdateSpool(void)
{
	char bVar1;
	int iVar2;
	int iVar3;
	CdlLOC pos;

	iVar3 = XAPrepared();
	iVar2 = spoolpos_reading;

	if (iVar3 != 1) 
	{
		target_address = spooldata[spoolpos_reading].addr;
		bVar1 = spooldata[spoolpos_reading].type;

		if (bVar1 == 0) // SPOOLTYPE_REGIONS
		{
			sectors_this_chunk = (spooldata[spoolpos_reading].nsectors);
			sectors_to_read = spool_regioninfo[spool_regionpos].nsectors;

			spoolseek = 5;
			CdDataCallback(data_cb_regions);
			CdReadyCallback(ready_cb_regions);
		}
		else if (bVar1 == 1) // SPOOLTYPE_TEXTURES
		{
			spoolseek = 5;

			nTPchunks_reading = 0;
			nTPchunks_writing = 0;
			sectors_to_read = 0x11;
			ntpages = tsetcounter;
			sectors_this_chunk = (uint)bVar1;

			CdDataCallback(data_cb_textures);
			CdReadyCallback(ready_cb_textures);

			target_address = target_address + 0x4000;
		}
		else if (bVar1 == 2) // SPOOLTYPE_SOUNDBANK
		{
			sectors_to_read = (spooldata[spoolpos_reading].nsectors);

			send_bank = (spooldata[spoolpos_reading].data);
			spoolseek = 5;
			sample_chunk = 0;
			nTPchunks_reading = 0;
			nTPchunks_writing = 0;
			sectors_this_chunk = (uint)bVar1;

			CdDataCallback(data_cb_soundbank);
			CdReadyCallback(ready_cb_soundbank);

			target_address = target_address + (loadbank_read & 1U) * 0x1000;
		}
		else if (bVar1 == 3)  // SPOOLTYPE_REGIONS
		{
			sectors_to_read = (spooldata[spoolpos_reading].nsectors);

			spoolseek = 5;
			CdDataCallback(data_cb_misc);
			CdReadyCallback(ready_cb_misc);
		}

		current_sector = spooldata[iVar2].sector;
		endchunk = 0;
		switch_spooltype = 0;

		CdIntToPos(current_sector, &pos);
		CdControlF(0x1b, (u_char*)&pos);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ RequestSpool(int type /*$a0*/, int data /*$a1*/, int offset /*$a2*/, int loadsize /*$a3*/, char *address /*stack 16*/, TDRFuncPtr_RequestSpool5func func /*stack 20*/)
 // line 1104, offset 0x0007e36c
	/* begin block 1 */
		// Start line: 1105
		// Start offset: 0x0007E36C
		// Variables:
	// 		struct SPOOLQ *next; // $t0
	// 		int sector; // $v0
	/* end block 1 */
	// End offset: 0x0007E3E4
	// End Line: 1126

	/* begin block 2 */
		// Start line: 6440
	/* end block 2 */
	// End Line: 6441

	/* begin block 3 */
		// Start line: 6447
	/* end block 3 */
	// End Line: 6448

// [D]
void RequestSpool(int type, int data, int offset, int loadsize, char *address, spooledFuncPtr func)
{
	int iVar2;
	SPOOLQ *next;

	iVar2 = citylumps[GameLevel][3].x;

	if (iVar2 < 0) {
		iVar2 = iVar2 + 0x7ff;
	}

	next = &spooldata[spoolcounter];

	next->type = (unsigned char)type;
	next->data = (unsigned char)data;
	next->sector = (iVar2 >> 0xb) + offset;
	next->nsectors = (ushort)loadsize;
	next->addr = address;
	next->func = func;

	spoolcounter++;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitSpooling()
 // line 1129, offset 0x0007e494
	/* begin block 1 */
		// Start line: 1131
		// Start offset: 0x0007E494
		// Variables:
	// 		int i; // $s0
	// 		char namebuffer[128]; // stack offset -152
	// 		struct CdlLOC pos; // stack offset -24
	/* end block 1 */
	// End offset: 0x0007E528
	// End Line: 1158

	/* begin block 2 */
		// Start line: 7099
	/* end block 2 */
	// End Line: 7100

	/* begin block 3 */
		// Start line: 2258
	/* end block 3 */
	// End Line: 2259

	/* begin block 4 */
		// Start line: 7100
	/* end block 4 */
	// End Line: 7101

	/* begin block 5 */
		// Start line: 7105
	/* end block 5 */
	// End Line: 7106

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitSpooling(void)
{
	int target_region;
	short *psVar1;

	target_region = 0;
	psVar1 = loading_region;

	do {
		*psVar1 = -1;

		ClearRegion(target_region);

		target_region = target_region + 1;
		psVar1 = psVar1 + 1;
	} while (target_region < 4);

	spool_regioncounter = 0;
	spoolerror = 0;
	spool_regionpos = 0;
	spoolactive = 0;
	tsetcounter = 0;
	models_ready = 0;
	tsetpos = 0;
	spoolcounter = 0;
	loadbank_read = 0;
	spoolpos = 0;
	unpack_roadmap_flag = 0;
	loadbank_write = 0;
	spoolseek = 0;
	unpack_cellptr_flag = 0;

	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SendTPage()
 // line 1161, offset 0x0007b88c
	/* begin block 1 */
		// Start line: 1163
		// Start offset: 0x0007B88C
		// Variables:
	// 		int tpage2send; // $s2
	// 		int slot; // $s0
	// 		int old; // $v1
	// 		char *tpageaddress; // $t0

		/* begin block 1.1 */
			// Start line: 1176
			// Start offset: 0x0007B900
			// Variables:
		// 		struct RECT cluts; // stack offset -32
		// 		int npalettes; // $s1
		// 		int i; // $a3
		// 		unsigned long *clutptr; // $a1
		/* end block 1.1 */
		// End offset: 0x0007BA24
		// End Line: 1208
	/* end block 1 */
	// End offset: 0x0007BB14
	// End Line: 1235

	/* begin block 2 */
		// Start line: 2385
	/* end block 2 */
	// End Line: 2386

	/* begin block 3 */
		// Start line: 2386
	/* end block 3 */
	// End Line: 2387

	/* begin block 4 */
		// Start line: 2390
	/* end block 4 */
	// End Line: 2391

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SendTPage(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	int iVar2;
	uint uVar3;
	uint *puVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	ushort local_20;
	ushort local_1e;
	undefined2 local_1c;
	short local_1a;

	iVar7 = tsetinfo[tsetpos * 2];
	iVar5 = *(int *)((int)tsetinfo + (tsetpos << 3 | 4U));
	if (nTPchunks == 0) {
		if (iVar5 != (uint)tpageloaded[iVar7] - 1) {
			iVar6 = *(int *)(model_spool_buffer + 0xe000);
			tpage.w = 0x40;
			tpage.h = 0x40;
			local_1c = 0x40;
			tpage.y = (&slot_tpagepos)[iVar5].vy;
			local_1e = slot_clutpos[iVar5].vy;
			tpage.x = (&slot_tpagepos)[iVar5].vx;
			local_20 = slot_clutpos[iVar5].vx;
			iVar5 = iVar6;
			if (iVar6 < 0) {
				iVar5 = iVar6 + 3;
			}
			local_1a = (short)(iVar5 >> 2) + 1;
			LoadImage(&local_20, model_spool_buffer + 0xe004);
			puVar4 = (uint *)(&texture_cluts + iVar7 * 0x20);
			iVar5 = 0;
			if (0 < iVar6) {
				iVar2 = (int)((uint)local_20 << 0x10) >> 0x10;
				do {
					uVar3 = (int)((uint)local_1e << 0x10) >> 10;
					*puVar4 = (uVar3 | iVar2 + 0x10 >> 4 & 0x3fU) << 0x10 |
						uVar3 | (int)((uint)local_20 << 0x10) >> 0x14 & 0x3fU;
					puVar4[1] = (uVar3 | iVar2 + 0x30 >> 4 & 0x3fU) << 0x10 |
						uVar3 | iVar2 + 0x20 >> 4 & 0x3fU;
					puVar4 = puVar4 + 2;
					local_1e = local_1e + 1;
					iVar5 = iVar5 + 4;
				} while (iVar5 < iVar6);
			}
			(&texture_pages)[iVar7] =
				(short)(tpage.y & 0x100U) >> 4 | (ushort)(((uint)(ushort)tpage.x & 0x3ff) >> 6) |
				(ushort)(((uint)(ushort)tpage.y & 0x200) << 2);
		}
	}
	else {
		if (iVar5 != (uint)tpageloaded[iVar7] - 1) {
			LoadImage(&tpage, model_spool_buffer + (int)(&DAT_0000a000 + (loadbank_write & 1U) * 0x2000));
			tpage.y = tpage.y + tpage.h;
		}
		if (nTPchunks == 4) {
			bVar1 = (&tpageslots)[iVar5];
			(&tpageslots)[iVar5] = (byte)iVar7;
			tpageloaded[bVar1] = '\0';
			tpageloaded[iVar7] = (char)iVar5 + 1;
			tsetpos = tsetpos + 1;
			if (tsetpos == tsetcounter) {
				tsetcounter = 0;
				tsetpos = 0;
			}
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SpoolSYNC()
 // line 1239, offset 0x0007e528
	/* begin block 1 */
		// Start line: 7247
	/* end block 1 */
	// End Line: 7248

	/* begin block 2 */
		// Start line: 7329
	/* end block 2 */
	// End Line: 7330

	/* begin block 3 */
		// Start line: 7345
	/* end block 3 */
	// End Line: 7346

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SpoolSYNC(void)
{
	UNIMPLEMENTED();
	/*
	do {
	} while (spoolactive != 0);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadInAreaTSets(int area /*$t4*/)
 // line 1262, offset 0x0007bb14
	/* begin block 1 */
		// Start line: 1263
		// Start offset: 0x0007BB14
		// Variables:
	// 		unsigned char *tpages; // $s1
	// 		int ntpages_to_load; // $s3
	// 		int i; // $s0
	// 		int slot; // $a0
	// 		int j; // $a1
	// 		int offset; // $s4
	// 		int availableslots[16]; // stack offset -104
	// 		int navailable; // $s2
	// 		char *loadaddr; // $fp
	/* end block 1 */
	// End offset: 0x0007BD84
	// End Line: 1333

	/* begin block 2 */
		// Start line: 2620
	/* end block 2 */
	// End Line: 2621

	/* begin block 3 */
		// Start line: 2648
	/* end block 3 */
	// End Line: 2649

	/* begin block 4 */
		// Start line: 2660
	/* end block 4 */
	// End Line: 2661

void LoadInAreaTSets(int area)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	byte bVar2;
	uint uVar3;
	int iVar4;
	uint offset;
	int *piVar5;
	int iVar6;
	byte *pbVar7;
	int iVar8;
	uint uVar9;
	char *address;
	int local_68[16];

	pbVar7 = AreaTPages + area * 0x10;
	bVar2 = AreaData[area].num_tpages;
	uVar9 = (uint)bVar2;
	address = model_spool_buffer + 0xa000;
	iVar8 = 0;
	if (slotsused < 0x13) {
		piVar5 = local_68;
		iVar6 = slotsused;
		do {
			offset = 0;
			if ((&tpageslots)[iVar6] == 0xff) {
				*piVar5 = iVar6;
				piVar5 = piVar5 + 1;
				iVar8 = iVar8 + 1;
			}
			else {
				if ((bVar2 != 0) && ((&tpageslots)[iVar6] != *pbVar7)) {
					uVar3 = 1;
					do {
						offset = uVar3;
						if ((int)uVar9 <= (int)offset) break;
						uVar3 = offset + 1;
					} while ((&tpageslots)[iVar6] != pbVar7[offset]);
				}
				if (offset == uVar9) {
					*piVar5 = iVar6;
					piVar5 = piVar5 + 1;
					iVar8 = iVar8 + 1;
				}
			}
			iVar6 = iVar6 + 1;
		} while (iVar6 < 0x13);
	}
	offset = (uint)AreaData[area].gfx_offset;
	iVar6 = 0;
	if (bVar2 != 0) {
		uVar3 = (uint)*pbVar7;
		if (tpageloaded[uVar3] != '\0') goto LAB_0007bc94;
		bVar1 = 0 < iVar8;
		iVar8 = iVar8 + -1;
		if (bVar1) {
			iVar4 = local_68[iVar8];
			while (true) {
				*(int *)((int)tsetinfo + (tsetcounter << 3 | 4U)) = iVar4;
				while (true) {
					RequestSpool(1, 0, offset, 0x11, address, 0x8c);
					offset = offset + 0x11;
					iVar6 = iVar6 + 1;
					iVar4 = tsetcounter * 2;
					tsetcounter = tsetcounter + 1;
					tsetinfo[iVar4] = (uint)*pbVar7;
					pbVar7 = pbVar7 + 1;
					if ((int)uVar9 <= iVar6) {
						return;
					}
					uVar3 = (uint)*pbVar7;
					if (tpageloaded[uVar3] == '\0') break;
				LAB_0007bc94:
					*(int *)((int)tsetinfo + (tsetcounter << 3 | 4U)) = (uint)tpageloaded[uVar3] - 1;
				}
				bVar1 = iVar8 < 1;
				iVar8 = iVar8 + -1;
				if (bVar1) break;
				iVar4 = local_68[iVar8];
			}
		}
	}
	return;
	*/\
}



// decompiled code
// original method signature: 
// void /*$ra*/ SendSBK()
 // line 1337, offset 0x0007bd84
	/* begin block 1 */
		// Start line: 1339
		// Start offset: 0x0007BD84
		// Variables:
	// 		char *address; // $s0
	// 		int slength; // $s1
	// 		int i; // $a1
	// 		unsigned long *source; // $v0
	// 		unsigned long *dest; // $a0
	/* end block 1 */
	// End offset: 0x0007BEBC
	// End Line: 1380

	/* begin block 2 */
		// Start line: 2921
	/* end block 2 */
	// End Line: 2922

	/* begin block 3 */
		// Start line: 2926
	/* end block 3 */
	// End Line: 2927

	/* begin block 4 */
		// Start line: 2927
	/* end block 4 */
	// End Line: 2928

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SendSBK(void)
{
	UNIMPLEMENTED();
	/*
	ulong uVar1;
	uint uVar2;
	SAMPLE_DATA *pSVar3;
	ulong *puVar4;
	uint uVar5;
	int *piVar6;
	int iVar7;

	piVar6 = (int *)(model_spool_buffer + (loadbank_write & 1U) * 0x1000 + 0x8000);
	if (sample_chunk == 0) {
		if (Song_ID != -1) {
			StopXM();
			FreeXM();
		}
		uVar5 = 0;
		pSVar3 = samples;
		num_samples = piVar6[1];
		uVar2 = num_samples << 2;
		puVar4 = (ulong *)(piVar6 + 2);
		if (uVar2 != 0) {
			do {
				uVar1 = *puVar4;
				puVar4 = puVar4 + 1;
				uVar5 = uVar5 + 1;
				pSVar3->address = uVar1;
				pSVar3 = (SAMPLE_DATA *)&pSVar3->length;
			} while (uVar5 < uVar2);
		}
		piVar6 = piVar6 + 1 + num_samples * 4 + 1;
		spuaddress = (&bankaddr)[send_bank];
		iVar7 = num_samples * -0x10 + 0xff8;
	}
	else {
		iVar7 = 0x1000;
	}
	SpuSetTransferMode(0);
	SpuSetTransferStartAddr(spuaddress);
	SpuWrite(piVar6, iVar7 + 0x3fU & 0xffffffc0);
	spuaddress = spuaddress + iVar7;
	sample_chunk = sample_chunk + 1;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ init_spooled_models()
 // line 1484, offset 0x0007bebc
	/* begin block 1 */
		// Start line: 1486
		// Start offset: 0x0007BEBC
		// Variables:
	// 		int i; // $s1
	// 		int nmodels; // $s4
	// 		int size; // $s2
	// 		int model_number; // $a1
	// 		char *addr; // $s0
	// 		struct MODEL *parentmodel; // $a1

		/* begin block 1.1 */
			// Start line: 1519
			// Start offset: 0x0007BFBC
		/* end block 1.1 */
		// End offset: 0x0007BFD0
		// End Line: 1521

		/* begin block 1.2 */
			// Start line: 1528
			// Start offset: 0x0007C004
		/* end block 1.2 */
		// End offset: 0x0007C048
		// End Line: 1536
	/* end block 1 */
	// End offset: 0x0007C08C
	// End Line: 1543

	/* begin block 2 */
		// Start line: 3131
	/* end block 2 */
	// End Line: 3132

	/* begin block 3 */
		// Start line: 3236
	/* end block 3 */
	// End Line: 3237

	/* begin block 4 */
		// Start line: 3237
	/* end block 4 */
	// End Line: 3238

	/* begin block 5 */
		// Start line: 3246
	/* end block 5 */
	// End Line: 3247

/* WARNING: Unknown calling convention yet parameter storage is locked */

void init_spooled_models(void)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	ushort uVar2;
	ushort *puVar3;
	MODEL **ppMVar4;
	uint model_number;
	MODEL *pMVar5;
	int *piVar6;
	MODEL *pMVar7;
	int iVar8;
	int iVar9;

	piVar6 = (int *)model_spool_buffer;
	ppMVar4 = modelpointers1536;
	iVar8 = 0x5ff;
	models_ready = 0;
	uVar1 = *newmodels;
	newmodels = newmodels + 1;
	do {
		if (piVar6 <= *ppMVar4) {
			*ppMVar4 = &dummyModel;
		}
		iVar8 = iVar8 + -1;
		ppMVar4 = ppMVar4 + 1;
	} while (-1 < iVar8);
	iVar8 = 0;
	if (uVar1 != 0) {
		do {
			puVar3 = Low2LowerDetailTable;
			model_number = (uint)newmodels[iVar8];
			iVar9 = *piVar6;
			pMVar7 = (MODEL *)(piVar6 + 1);
			modelpointers1536[model_number] = pMVar7;
			pLodModels1536[model_number] = pMVar7;
			uVar2 = puVar3[model_number];
			if ((uVar2 != 0xffff) && ((uint)uVar2 != model_number)) {
				pLodModels1536[model_number] = modelpointers1536[(uint)uVar2];
			}
			if ((int)*(short *)(piVar6 + 2) == -1) {
				if (piVar6[9] != 0) {
					piVar6[9] = (int)&pMVar7->shape_flags + piVar6[9];
				}
				piVar6[5] = (int)&pMVar7->shape_flags + piVar6[5];
				piVar6[7] = (int)&pMVar7->shape_flags + piVar6[7];
				piVar6[8] = (int)&pMVar7->shape_flags + piVar6[8];
				InitSpooledAnimObj(model_number);
			}
			else {
				pMVar5 = modelpointers1536[(int)*(short *)(piVar6 + 2)];
				if (pMVar5->collision_block != 0) {
					piVar6[9] = pMVar5->collision_block;
				}
				piVar6[5] = pMVar5->vertices;
				piVar6[7] = pMVar5->normals;
				piVar6[8] = pMVar5->point_normals;
				InitSpooledAnimObj((int)*(short *)(piVar6 + 2));
			}
			iVar8 = iVar8 + 1;
			piVar6[6] = (int)&pMVar7->shape_flags + piVar6[6];
			piVar6 = (int *)((int)&pMVar7->shape_flags + iVar9);
		} while (iVar8 < (int)(uint)uVar1);
	}
	LoadingArea = 0;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupModels()
 // line 1545, offset 0x0007e540
	/* begin block 1 */
		// Start line: 7941
	/* end block 1 */
	// End Line: 7942

	/* begin block 2 */
		// Start line: 7945
	/* end block 2 */
	// End Line: 7946

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SetupModels(void)
{
	UNIMPLEMENTED();
	/*
	if (old_region == -1) {
		init_spooled_models();
	}
	else {
		models_ready = 1;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadInAreaModels(int area /*$a0*/)
 // line 1559, offset 0x0007e580
	/* begin block 1 */
		// Start line: 1561
		// Start offset: 0x0007E580
		// Variables:
	// 		int offset; // $a2
	// 		int length; // $a3
	/* end block 1 */
	// End offset: 0x0007E5DC
	// End Line: 1571

	/* begin block 2 */
		// Start line: 7969
	/* end block 2 */
	// End Line: 7970

	/* begin block 3 */
		// Start line: 7970
	/* end block 3 */
	// End Line: 7971

	/* begin block 4 */
		// Start line: 7974
	/* end block 4 */
	// End Line: 7975

void LoadInAreaModels(int area)
{
	UNIMPLEMENTED();
	/*
	uint loadsize;

	loadsize = (uint)AreaData[area].model_size;
	newmodels = (ushort *)(model_spool_buffer + (loadsize - 1) * 0x800);
	RequestSpool(3, 0, (uint)AreaData[area].model_offset, loadsize, model_spool_buffer, 0x40);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckLoadAreaData(int cellx /*$t9*/, int cellz /*$a1*/)
 // line 1574, offset 0x0007c08c
	/* begin block 1 */
		// Start line: 1575
		// Start offset: 0x0007C08C
		// Variables:
	// 		int i; // $a2
	// 		int nAreas; // $t0
	// 		struct Spool *spoolptr; // $t1
	// 		int load; // $a3
	// 		int force_load_boundary; // $a0
	/* end block 1 */
	// End offset: 0x0007C27C
	// End Line: 1666

	/* begin block 2 */
		// Start line: 3485
	/* end block 2 */
	// End Line: 3486

	/* begin block 3 */
		// Start line: 3517
	/* end block 3 */
	// End Line: 3518

	/* begin block 4 */
		// Start line: 3522
	/* end block 4 */
	// End Line: 3523

void CheckLoadAreaData(int cellx, int cellz)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte bVar2;
	bool bVar3;
	byte *pbVar4;
	uint uVar5;
	int iVar6;
	uint area;
	char *pcVar7;

	bVar3 = false;
	if (spoolinfo_offsets[current_region] != 0xffff) {
		pcVar7 = RegionSpoolInfo + spoolinfo_offsets[current_region];
		if ((old_region == -1) && (pcVar7[8] != -1)) {
			area = (uint)(byte)pcVar7[8];
		}
		else {
			bVar1 = pcVar7[9];
			if (old_region == -1) {
				LoadedArea = old_region;
			}
			else {
				if (pcVar7[8] != -1) {
					return;
				}
				if (bVar1 == 0) {
					return;
				}
			}
			iVar6 = 0xd;
			if (lead_car == 0) {
				iVar6 = 0xf;
			}
			area = 0;
			if (bVar1 != 0) {
				pbVar4 = (byte *)(pcVar7 + 2);
				do {
					bVar2 = *pbVar4 >> 6;
					uVar5 = (uint)bVar2;
					if (LoadedArea != ((uint)*pbVar4 & 0x3f)) {
						new_area_location = uVar5;
						if (bVar2 == 1) {
							if (0x20 - iVar6 < cellx) {
								bVar3 = true;
							}
						}
						else {
							if (bVar2 < 2) {
								if ((bVar2 == 0) && (0x20 - iVar6 < cellz)) {
									bVar3 = true;
								}
							}
							else {
								if (bVar2 == 2) {
									if (cellz < iVar6) {
										bVar3 = true;
									}
								}
								else {
									if ((bVar2 == 3) && (cellx < iVar6)) {
										bVar3 = true;
									}
								}
							}
						}
					}
					if (bVar3) break;
					area = area + 1;
					pbVar4 = (byte *)(pcVar7 + 2 + area);
				} while ((int)area < (int)(uint)bVar1);
			}
			if (area == (uint)bVar1) {
				if (LoadedArea != -1) {
					return;
				}
				area = initarea;
				if (initarea == -1) {
					return;
				}
			}
			else {
				area = (uint)(byte)pcVar7[area + 2] & 0x3f;
			}
		}
		LoadingArea = 1;
		LoadedArea = area;
		LoadInAreaTSets(area);
		LoadInAreaModels(LoadedArea);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ClearRegion(int target_region /*$a0*/)
 // line 1670, offset 0x0007e3e4
	/* begin block 1 */
		// Start line: 1671
		// Start offset: 0x0007E3E4
		// Variables:
	// 		int loop; // $a1
	// 		unsigned short *cell_ptrs_s; // $v1
	// 		unsigned long *pvsptr; // $v0
	/* end block 1 */
	// End offset: 0x0007E494
	// End Line: 1711

	/* begin block 2 */
		// Start line: 7049
	/* end block 2 */
	// End Line: 7050

	/* begin block 3 */
		// Start line: 7594
	/* end block 3 */
	// End Line: 7595

	/* begin block 4 */
		// Start line: 7604
	/* end block 4 */
	// End Line: 7605

short* RoadMapDataRegions[4];

// [D]
void ClearRegion(int target_region)
{
	long *pvsptr;
	ushort *cell_ptrs_s;
	int iVar1;

	iVar1 = 0x400;
	cell_ptrs_s = cell_ptrs + target_region * 0x400;

	do {
		*cell_ptrs_s = 0xffff;
		iVar1 = iVar1 + -1;
		cell_ptrs_s = cell_ptrs_s + 1;
	} while (iVar1 != 0);

	pvsptr = (long *)PVS_Buffers[target_region];
	iVar1 = 0x400;

	do {
		*pvsptr = 0;
		iVar1 = iVar1 + -1;
		pvsptr = pvsptr + 1;
	} while (iVar1 != 0);

	ClearMem(PVS_Buffers[target_region] + -4, pvsSize[target_region]);
	*(char **)(RoadMapDataRegions + target_region) = PVS_Buffers[0];
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadRegionData(int region /*$s4*/, int target_region /*$s5*/)
 // line 1713, offset 0x0007c28c
	/* begin block 1 */
		// Start line: 1714
		// Start offset: 0x0007C28C
		// Variables:
	// 		int offset; // $s0
	// 		char *target_unpacked_data; // $t1
	// 		struct Spool *spoolptr; // $s1
	// 		char *roadmap_buffer; // $s6
	// 		char *cell_buffer; // $s3
	/* end block 1 */
	// End offset: 0x0007C464
	// End Line: 1776

	/* begin block 2 */
		// Start line: 3836
	/* end block 2 */
	// End Line: 3837

// [D]
int LoadRegionData(int region, int target_region)
{
	short sVar1;
	ushort uVar2;
	int iVar3;
	char *cell_buffer;
	short *spofs;
	SPL_REGIONINFO *pSVar4;
	int offset;
	Spool *spoolptr;
	char *roadmap_buffer;	// D1 leftover?

	roadmap_buffer = NULL; // [A]

	spofs = (short *)(spoolinfo_offsets + region);
	sVar1 = *spofs;

	if (sVar1 != -1) 
	{
		loading_region[target_region] = (ushort)region;
		cell_buffer = packed_cell_pointers;
		spoolptr = (Spool *)(RegionSpoolInfo + (ushort)*spofs);

		uVar2 = spoolptr->offset;
		RequestSpool(0, 0, (uint)uVar2, (uint)spoolptr->cell_data_size[1], packed_cell_pointers, NULL);

		offset = (uint)uVar2 + (uint)spoolptr->cell_data_size[1];
		RequestSpool(0, 0, offset, (uint)spoolptr->cell_data_size[0],(char *)(cells + cell_slots_add[target_region]), NULL);

		offset = offset + (uint)spoolptr->cell_data_size[0];
		RequestSpool(0, 0, offset, (uint)spoolptr->cell_data_size[2], (char *)(cell_objects + num_straddlers + cell_objects_add[target_region]), NULL);

		offset = offset + (uint)spoolptr->cell_data_size[2];
		RequestSpool(0, 0, offset, (uint)spoolptr->roadm_size, PVS_Buffers[target_region] + -4, GotRegion);

		iVar3 = spool_regioncounter;
		pSVar4 = spool_regioninfo + spool_regioncounter;

		spool_regioninfo[spool_regioncounter].nsectors = (offset + (uint)spoolptr->roadm_size) - (uint)spoolptr->offset;

		pSVar4->region_to_unpack = (ushort)region;

		spool_regioninfo[iVar3].target_barrel_region = (ushort)target_region;
		spool_regioninfo[iVar3].cell_addr = cell_buffer;
		spool_regioninfo[iVar3].roadm_addr = roadmap_buffer;
	}

	return (sVar1 != -1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ UnpackRegion(int region_to_unpack /*$s1*/, int target_barrel_region /*$s0*/)
 // line 1779, offset 0x0007e5dc
	/* begin block 1 */
		// Start line: 1780
		// Start offset: 0x0007E5DC
	/* end block 1 */
	// End offset: 0x0007E658
	// End Line: 1812

	/* begin block 2 */
		// Start line: 8208
	/* end block 2 */
	// End Line: 8209

	/* begin block 3 */
		// Start line: 8417
	/* end block 3 */
	// End Line: 8418

int RoadMapRegions[4];

// [D]
void UnpackRegion(int region_to_unpack, int target_barrel_region)
{
	int iVar1;

	if (loading_region[target_barrel_region] == -1) 
	{
		iVar1 = LoadRegionData(region_to_unpack, target_barrel_region);

		if (iVar1 != 0)
			spool_regioncounter = spool_regioncounter + 1;

		regions_unpacked[target_barrel_region] = region_to_unpack;
		RoadMapRegions[target_barrel_region] = region_to_unpack;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessSpoolInfoLump(char *lump_ptr /*$a2*/, int lump_size /*$a1*/)
 // line 1815, offset 0x0007c464
	/* begin block 1 */
		// Start line: 1816
		// Start offset: 0x0007C464
		// Variables:
	// 		int i; // $t2
	// 		int size; // $v1
	// 		int slots_count; // $t0
	// 		int objects_count; // $t1
	// 		int num_of_regions; // $v0
	// 		char *alloclist; // $a3
	/* end block 1 */
	// End offset: 0x0007C5C0
	// End Line: 1918

	/* begin block 2 */
		// Start line: 4141
	/* end block 2 */
	// End Line: 4142

	/* begin block 3 */
		// Start line: 4181
	/* end block 3 */
	// End Line: 4182

// [D]
void ProcessSpoolInfoLump(char *lump_ptr, int lump_size)
{
	int *piVar1;
	int iVar2;
	int *piVar3;
	int *piVar4;
	int *piVar5;
	char **ppcVar6;
	int *piVar7;
	int *piVar8;

	piVar3 = pvsSize;
	pvsSize[0] = 0;
	pvsSize[1] = 0;
	pvsSize[2] = 0;
	pvsSize[3] = 0;

	iVar2 = *(int *)lump_ptr << 0xb;

	model_spool_buffer = mallocptr;

	if (iVar2 < 0x10000) {
		iVar2 = 0x10000;
	}

	mallocptr = mallocptr + iVar2;

	cell_slots_add[4] = 0;
	cell_objects_add[4] = 0;

	piVar8 = cell_objects_add;
	piVar7 = cell_slots_add;
	ppcVar6 = PVS_Buffers;
	iVar2 = 3;
	Music_And_AmbientOffsets = (SXYPAIR *)(lump_ptr + 8);
	piVar4 = (int *)((int)(lump_ptr + 4) + *(int *)(lump_ptr + 4) + 4);

	NumAreas = *piVar4;
	AreaData = (AreaDataStr *)(piVar4 + 1);
	AreaTPages = (unsigned char *)(piVar4 + NumAreas * 4 + 1);

	piVar5 = (int *)AreaTPages + NumAreas * 4;
	piVar4 = piVar5;

	do {
		*piVar8 = cell_objects_add[4];
		piVar8 = piVar8 + 1;
		*piVar7 = cell_slots_add[4];
		piVar7 = piVar7 + 1;
		*ppcVar6 = mallocptr + 4;
		ppcVar6 = ppcVar6 + 1;
		iVar2 = iVar2 + -1;
		cell_slots_add[4] = cell_slots_add[4] + *piVar4;
		cell_objects_add[4] = cell_objects_add[4] + piVar4[4];
		*piVar3 = piVar4[8] + 0x7ffU & 0xfffff800;
		piVar3 = (int *)((uint *)piVar3 + 1);
		piVar1 = piVar4 + 8;
		piVar4 = piVar4 + 1;
		mallocptr = mallocptr + (*piVar1 + 0x7ffU & 0xfffff800);
	} while (-1 < iVar2);

	RegionSpoolInfo = (char *)((int)(piVar5 + 0xc) + piVar5[0xc] * 2 + 8);
	spoolinfo_offsets = (ushort *)(piVar5 + 0xd);
}



// decompiled code
// original method signature: 
// void /*$ra*/ WaitCloseLid()
 // line 1928, offset 0x0007e66c
	/* begin block 1 */
		// Start line: 1930
		// Start offset: 0x0007E66C
		// Variables:
	// 		void (*old)(); // $s1
	/* end block 1 */
	// End offset: 0x0007E6D8
	// End Line: 1942

	/* begin block 2 */
		// Start line: 8731
	/* end block 2 */
	// End Line: 8732

	/* begin block 3 */
		// Start line: 8732
	/* end block 3 */
	// End Line: 8733

	/* begin block 4 */
		// Start line: 8733
	/* end block 4 */
	// End Line: 8734

/* WARNING: Unknown calling convention yet parameter storage is locked */

void WaitCloseLid(void)
{
	UNIMPLEMENTED();
	/*
	undefined4 uVar1;
	int iVar2;

	uVar1 = CdReadyCallback(0);
	stopgame();
	while (iVar2 = CdDiskReady(1), iVar2 != 2) {
		DrawCDicon();
		VSync(0);
	}
	startgame();
	CdReadyCallback(uVar1);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ FoundError(char *name /*$a0*/, unsigned char intr /*$a1*/, unsigned char *result /*$a2*/)
 // line 1945, offset 0x0007e6d8
	/* begin block 1 */
		// Start line: 1947
		// Start offset: 0x0007E6D8
		// Variables:
	// 		struct CdlLOC p; // stack offset -16
	/* end block 1 */
	// End offset: 0x0007E724
	// End Line: 1963

	/* begin block 2 */
		// Start line: 8761
	/* end block 2 */
	// End Line: 8762

	/* begin block 3 */
		// Start line: 8765
	/* end block 3 */
	// End Line: 8766

	/* begin block 4 */
		// Start line: 8766
	/* end block 4 */
	// End Line: 8767

	/* begin block 5 */
		// Start line: 8768
	/* end block 5 */
	// End Line: 8769

void FoundError(char *name, unsigned char intr, unsigned char *result)
{
	UNIMPLEMENTED();
	/*
	undefined auStack16[8];

	if ((*result & 0x10) != 0) {
		WaitCloseLid();
	}
	spoolerror = 0x3c;
	CdIntToPos(current_sector, auStack16);
	CdControlF(0x1b, auStack16);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ GotRegion()
 // line 1970, offset 0x0007d9cc
	/* begin block 1 */
		// Start line: 1972
		// Start offset: 0x0007D9CC
		// Variables:
	// 		int cbr; // $a1
	/* end block 1 */
	// End offset: 0x0007DA60
	// End Line: 1990

	/* begin block 2 */
		// Start line: 6109
	/* end block 2 */
	// End Line: 6110

	/* begin block 3 */
		// Start line: 3940
	/* end block 3 */
	// End Line: 3941

	/* begin block 4 */
		// Start line: 6110
	/* end block 4 */
	// End Line: 6111

	/* begin block 5 */
		// Start line: 6113
	/* end block 5 */
	// End Line: 6114

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void GotRegion(void)
{
	char *pcVar2;
	uint target_barrel_reg;

	Unpack_CellPtrs();

	target_barrel_reg = (uint)spool_regioninfo[spool_regionpos].target_barrel_region;
	spool_regionpos++;

	pcVar2 = PVS_Buffers[target_barrel_reg];
	loading_region[target_barrel_reg] = -1;

	*(char **)(RoadMapDataRegions + target_barrel_reg) = pcVar2 + *(int *)(pcVar2 + -4);

	if (spool_regionpos == spool_regioncounter)
	{
		spool_regioncounter = 0;
		spool_regionpos = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ data_cb_textures()
 // line 1993, offset 0x0007df64
	/* begin block 1 */
		// Start line: 1995
		// Start offset: 0x0007DF64

		/* begin block 1.1 */
			// Start line: 1997
			// Start offset: 0x0007DF78
		/* end block 1.1 */
		// End offset: 0x0007E068
		// End Line: 2033
	/* end block 1 */
	// End offset: 0x0007E078
	// End Line: 2034

	/* begin block 2 */
		// Start line: 6680
	/* end block 2 */
	// End Line: 6681

	/* begin block 3 */
		// Start line: 3986
	/* end block 3 */
	// End Line: 3987

	/* begin block 4 */
		// Start line: 6681
	/* end block 4 */
	// End Line: 6682

/* WARNING: Unknown calling convention yet parameter storage is locked */

void data_cb_textures(void)
{
	UNIMPLEMENTED();
	/*
	if (chunk_complete != 0) {
		chunk_complete = 0;
		nTPchunks = nTPchunks_writing;
		SendTPage();
		if (nTPchunks != 0) {
			loadbank_write = loadbank_write + 1;
		}
		nTPchunks_writing = nTPchunks_writing + 1;
		if (nTPchunks_writing == 5) {
			nTPchunks_writing = 0;
			spoolpos_writing = spoolpos_writing + 1;
			if (ntpages == 0) {
				if (switch_spooltype == 0) {
					CdDataCallback(0);
					if (spoolpos_writing == spoolcounter) {
						spoolcounter = 0;
						spoolpos_writing = 0;
						spoolpos_reading = 0;
						spoolactive = 0;
					}
					else {
						UpdateSpool();
					}
				}
				else {
					changemode(spooldata + spoolpos_writing);
				}
			}
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ready_cb_textures(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
 // line 2036, offset 0x0007e078
	/* begin block 1 */
		// Start line: 2037
		// Start offset: 0x0007E078

		/* begin block 1.1 */
			// Start line: 2050
			// Start offset: 0x0007E0D8
			// Variables:
		// 		struct SPOOLQ *current; // $a2
		/* end block 1.1 */
		// End offset: 0x0007E188
		// End Line: 2080
	/* end block 1 */
	// End offset: 0x0007E198
	// End Line: 2086

	/* begin block 2 */
		// Start line: 6770
	/* end block 2 */
	// End Line: 6771

	/* begin block 3 */
		// Start line: 6773
	/* end block 3 */
	// End Line: 6774

void ready_cb_textures(unsigned char intr, unsigned char *result)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;

	uVar1 = (uint)intr;
	if (intr == '\x01') {
		CdGetSector(target_address, 0x200);
		target_address = target_address + 0x800;
		sectors_this_chunk = sectors_this_chunk + -1;
		current_sector = current_sector + 1;
		sectors_to_read = sectors_to_read + -1;
		if (sectors_this_chunk == 0) {
			if (nTPchunks_reading != 0) {
				loadbank_read = loadbank_read + 1;
			}
			nTPchunks_reading = nTPchunks_reading + 1;
			chunk_complete = uVar1;
			if (sectors_to_read == 0) {
				ntpages = ntpages + -1;
				if (ntpages == 0) {
					spoolpos_reading = spoolpos_reading + 1;
					test_changemode();
				}
				else {
					nTPchunks_reading = 0;
					sectors_to_read = 0x11;
					target_address = spooldata[spoolpos_reading].addr + 0x4000;
					spoolpos_reading = spoolpos_reading + 1;
					sectors_this_chunk = uVar1;
				}
			}
			else {
				sectors_this_chunk = 4;
				target_address = spooldata[spoolpos_reading].addr + (loadbank_read & 1U) * 0x2000;
			}
		}
	}
	else {
		FoundError(s_ready_cb_textures_00011d34, intr, result);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ready_cb_regions(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
 // line 2090, offset 0x0007de90
	/* begin block 1 */
		// Start line: 2091
		// Start offset: 0x0007DE90

		/* begin block 1.1 */
			// Start line: 2110
			// Start offset: 0x0007DF08
			// Variables:
		// 		struct SPOOLQ *current; // $v1
		/* end block 1.1 */
		// End offset: 0x0007DF08
		// End Line: 2110
	/* end block 1 */
	// End offset: 0x0007DF64
	// End Line: 2129

	/* begin block 2 */
		// Start line: 6728
	/* end block 2 */
	// End Line: 6729

	/* begin block 3 */
		// Start line: 4180
	/* end block 3 */
	// End Line: 4181

void ready_cb_regions(unsigned char intr, unsigned char *result)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;

	uVar1 = (uint)intr;
	if (intr == '\x01') {
		CdGetSector(target_address, 0x200);
		target_address = target_address + 0x800;
		sectors_this_chunk = sectors_this_chunk + -1;
		current_sector = current_sector + 1;
		sectors_to_read = sectors_to_read + -1;
		if (sectors_this_chunk == 0) {
			spoolpos_reading = spoolpos_reading + 1;
			chunk_complete = uVar1;
			if (sectors_to_read == 0) {
				endchunk = uVar1;
				test_changemode();
			}
			else {
				target_address = spooldata[spoolpos_reading].addr;
				sectors_this_chunk = ZEXT24(spooldata[spoolpos_reading].nsectors);
			}
		}
	}
	else {
		FoundError(s_ready_cb_regions_00011d48, intr, result);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ data_cb_regions()
 // line 2132, offset 0x0007dda8
	/* begin block 1 */
		// Start line: 2134
		// Start offset: 0x0007DDA8

		/* begin block 1.1 */
			// Start line: 2136
			// Start offset: 0x0007DDBC
			// Variables:
		// 		struct SPOOLQ *current; // $v0
		/* end block 1.1 */
		// End offset: 0x0007DE80
		// End Line: 2167
	/* end block 1 */
	// End offset: 0x0007DE90
	// End Line: 2168

	/* begin block 2 */
		// Start line: 4264
	/* end block 2 */
	// End Line: 4265

	/* begin block 3 */
		// Start line: 6733
	/* end block 3 */
	// End Line: 6734

/* WARNING: Unknown calling convention yet parameter storage is locked */

void data_cb_regions(void)
{
	UNIMPLEMENTED();
	/*
	if (chunk_complete != 0) {
		chunk_complete = 0;
		if (spooldata[spoolpos_writing].func != (_func_11 *)0x0) {
			(*spooldata[spoolpos_writing].func)();
		}
		spoolpos_writing = spoolpos_writing + 1;
		if (endchunk != 0) {
			if (switch_spooltype == 0) {
				CdDataCallback(0);
				if (spoolpos_writing == spoolcounter) {
					spoolcounter = 0;
					spoolpos_writing = 0;
					spoolpos_reading = 0;
					spoolactive = 0;
				}
				else {
					UpdateSpool();
				}
			}
			else {
				changemode(spooldata + spoolpos_writing);
			}
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ data_cb_soundbank()
 // line 2171, offset 0x0007dbcc
	/* begin block 1 */
		// Start line: 2173
		// Start offset: 0x0007DBCC

		/* begin block 1.1 */
			// Start line: 2175
			// Start offset: 0x0007DBE0
		/* end block 1.1 */
		// End offset: 0x0007DC94
		// End Line: 2200
	/* end block 1 */
	// End offset: 0x0007DCA4
	// End Line: 2201

	/* begin block 2 */
		// Start line: 4342
	/* end block 2 */
	// End Line: 4343

	/* begin block 3 */
		// Start line: 6666
	/* end block 3 */
	// End Line: 6667

/* WARNING: Unknown calling convention yet parameter storage is locked */

void data_cb_soundbank(void)
{
	UNIMPLEMENTED();
	/*
	if (chunk_complete != 0) {
		chunk_complete = 0;
		SendSBK();
		loadbank_write = loadbank_write + 1;
		if (endchunk != 0) {
			spoolpos_writing = spoolpos_writing + 1;
			if (switch_spooltype == 0) {
				CdDataCallback(0);
				if (spoolpos_writing == spoolcounter) {
					spoolcounter = 0;
					spoolpos_writing = 0;
					spoolpos_reading = 0;
					spoolactive = 0;
				}
				else {
					UpdateSpool();
				}
			}
			else {
				changemode(spooldata + spoolpos_writing);
			}
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ready_cb_soundbank(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
 // line 2203, offset 0x0007dca4
	/* begin block 1 */
		// Start line: 2204
		// Start offset: 0x0007DCA4

		/* begin block 1.1 */
			// Start line: 2217
			// Start offset: 0x0007DD04
			// Variables:
		// 		struct SPOOLQ *current; // $a0
		/* end block 1.1 */
		// End offset: 0x0007DD70
		// End Line: 2237
	/* end block 1 */
	// End offset: 0x0007DD98
	// End Line: 2244

	/* begin block 2 */
		// Start line: 6729
	/* end block 2 */
	// End Line: 6730

	/* begin block 3 */
		// Start line: 6732
	/* end block 3 */
	// End Line: 6733

void ready_cb_soundbank(unsigned char intr, unsigned char *result)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;

	uVar1 = (uint)intr;
	if (intr == '\x01') {
		CdGetSector(target_address, 0x200);
		target_address = target_address + 0x800;
		sectors_this_chunk = sectors_this_chunk + -1;
		current_sector = current_sector + 1;
		sectors_to_read = sectors_to_read + -1;
		if (sectors_this_chunk == 0) {
			loadbank_read = loadbank_read + 1;
			nTPchunks_reading = nTPchunks_reading + 1;
			chunk_complete = uVar1;
			if (sectors_to_read == 0) {
				spoolpos_reading = spoolpos_reading + 1;
				endchunk = uVar1;
				test_changemode();
			}
			else {
				sectors_this_chunk = 2;
				if (sectors_to_read < 2) {
					sectors_this_chunk = sectors_to_read;
				}
				target_address = spooldata[spoolpos_reading].addr + (loadbank_read & 1U) * 0x1000;
			}
		}
	}
	else {
		FoundError(s_ready_cb_soundbank_00011d5c, intr, result);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ data_cb_misc()
 // line 2246, offset 0x0007da60
	/* begin block 1 */
		// Start line: 2248
		// Start offset: 0x0007DA60

		/* begin block 1.1 */
			// Start line: 2250
			// Start offset: 0x0007DA74
			// Variables:
		// 		struct SPOOLQ *current; // $v0
		/* end block 1.1 */
		// End offset: 0x0007DB28
		// End Line: 2275
	/* end block 1 */
	// End offset: 0x0007DB38
	// End Line: 2276

	/* begin block 2 */
		// Start line: 6421
	/* end block 2 */
	// End Line: 6422

	/* begin block 3 */
		// Start line: 6678
	/* end block 3 */
	// End Line: 6679

	/* begin block 4 */
		// Start line: 6679
	/* end block 4 */
	// End Line: 6680

/* WARNING: Unknown calling convention yet parameter storage is locked */

void data_cb_misc(void)
{
	UNIMPLEMENTED();
	/*
	if (chunk_complete != 0) {
		chunk_complete = 0;
		if (spooldata[spoolpos_writing].func != (_func_11 *)0x0) {
			(*spooldata[spoolpos_writing].func)();
		}
		spoolpos_writing = spoolpos_writing + 1;
		if (switch_spooltype == 0) {
			CdDataCallback(0);
			if (spoolpos_writing == spoolcounter) {
				spoolcounter = 0;
				spoolpos_writing = 0;
				spoolpos_reading = 0;
				spoolactive = 0;
			}
			else {
				UpdateSpool();
			}
		}
		else {
			changemode(spooldata + spoolpos_writing);
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ready_cb_misc(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
 // line 2278, offset 0x0007db38
	/* begin block 1 */
		// Start line: 6744
	/* end block 1 */
	// End Line: 6745

	/* begin block 2 */
		// Start line: 6747
	/* end block 2 */
	// End Line: 6748

void ready_cb_misc(unsigned char intr, unsigned char *result)
{
	UNIMPLEMENTED();
	/*
	if (intr == '\x01') {
		CdGetSector(target_address, 0x200);
		target_address = target_address + 0x800;
		sectors_to_read = sectors_to_read + -1;
		current_sector = current_sector + 1;
		if (sectors_to_read == 0) {
			spoolpos_reading = spoolpos_reading + 1;
			chunk_complete = (uint)intr;
			test_changemode();
		}
	}
	else {
		FoundError(s_ready_cb_misc_00011d70, intr, result);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ StartSpooling()
 // line 2302, offset 0x0007e724
	/* begin block 1 */
		// Start line: 2304
		// Start offset: 0x0007E724
	/* end block 1 */
	// End offset: 0x0007E7B0
	// End Line: 2321

	/* begin block 2 */
		// Start line: 9140
	/* end block 2 */
	// End Line: 9141

	/* begin block 3 */
		// Start line: 9480
	/* end block 3 */
	// End Line: 9481

	/* begin block 4 */
		// Start line: 9481
	/* end block 4 */
	// End Line: 9482

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void StartSpooling(void)
{
	static unsigned char param[8];
	static unsigned char result[8];

	int iVar1;

	if ((spoolcounter != 0) && (spoolactive == 0))
	{
		iVar1 = XAPrepared();

		if (iVar1 == 0)
		{
#ifdef PSX
			param[0] = -0x80;
			CdControlB(0xe, param, result);

			if ((result[0] & 0x15) != 0)
			{
				WaitCloseLid();
			}
#endif // PSX
			spoolactive = 1;
			UpdateSpool();

			if (FastForward != 0)
			{
				SpoolSYNC();
			}
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ unpack_cellpointers()
 // line 2351, offset 0x0007c5c0
	/* begin block 1 */
		// Start line: 2353
		// Start offset: 0x0007C5C0
		// Variables:
	// 		int target_barrel_region; // $t0
	// 		char *source_packed_data; // $v0
	// 		int bitpos; // $a3
	// 		int loop; // $a2
	// 		int packtype; // $a0
	// 		unsigned short cell; // $a0
	// 		unsigned short *short_ptr; // $a1
	// 		unsigned short pcode; // $t1
	/* end block 1 */
	// End offset: 0x0007C74C
	// End Line: 2437

	/* begin block 2 */
		// Start line: 4939
	/* end block 2 */
	// End Line: 4940

	/* begin block 3 */
		// Start line: 5373
	/* end block 3 */
	// End Line: 5374

	/* begin block 4 */
		// Start line: 5374
	/* end block 4 */
	// End Line: 5375

	/* begin block 5 */
		// Start line: 5383
	/* end block 5 */
	// End Line: 5384

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void unpack_cellpointers(void)
{
	ushort *puVar1;
	ushort *puVar2;
	ushort uVar3;
	int iVar4;
	int *piVar5;
	uint uVar6;
	uint uVar7;

	unpack_cellptr_flag = 0;
	iVar4 = *(int *)(unpack_cellptr_tbl[2] + 4);
	puVar1 = (ushort *)(unpack_cellptr_tbl[2] + 8);

	if (iVar4 == 0) 
	{
		iVar4 = 0x3ff;
		puVar1 = cell_ptrs + unpack_cellptr_tbl[1] * 0x400 + 0x3ff;
		do {
			*puVar1 = 0xffff;
			iVar4 = iVar4 + -1;
			puVar1 = puVar1 + -1;
		} while (-1 < iVar4);
	}
	else {
		if (iVar4 == 1)
		{
			piVar5 = cell_slots_add + unpack_cellptr_tbl[1];
			iVar4 = 0x3ff;
			puVar2 = cell_ptrs + unpack_cellptr_tbl[1] * 0x400;
			do {
				uVar3 = *puVar1;
				puVar1 = puVar1 + 1;
				if (uVar3 != 0xffff) {
					uVar3 = uVar3 + *(short *)piVar5;
				}
				*puVar2 = uVar3;
				iVar4 = iVar4 + -1;
				puVar2 = puVar2 + 1;
			} while (-1 < iVar4);
			return;
		}

		if (iVar4 == 2)
		{
			uVar6 = 0x8000;
			uVar7 = (uint)*puVar1;
			puVar2 = (ushort *)(unpack_cellptr_tbl[2] + 10);
			piVar5 = cell_slots_add + unpack_cellptr_tbl[1];
			iVar4 = 0x3ff;
			puVar1 = cell_ptrs + unpack_cellptr_tbl[1] * 0x400;
			do {
				if ((uVar7 & uVar6) == 0) {
					uVar3 = 0xffff;
				}
				else {
					uVar3 = *puVar2;
					puVar2 = puVar2 + 1;
					uVar3 = uVar3 + *(short *)piVar5;
				}
				uVar6 = (int)uVar6 >> 1;
				*puVar1 = uVar3;
				if (uVar6 == 0) {
					uVar6 = 0x8000;
					uVar7 = (uint)*puVar2;
					puVar2 = puVar2 + 1;
				}
				iVar4 = iVar4 + -1;
				puVar1 = puVar1 + 1;
			} while (-1 < iVar4);

			return;
		}

		if (FrameCnt != 0x78654321)
		{
			do {
				//trap(0x400);
			} while (FrameCnt != 0x78654321);

			unpack_cellptr_flag = 0;
			return;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ Unpack_CellPtrs()
 // line 2442, offset 0x0007d978
	/* begin block 1 */
		// Start line: 2444
		// Start offset: 0x0007D978
		// Variables:
	// 		int region_to_unpack; // $a1
	// 		int target_barrel_region; // $a1
	// 		char *source_packed_data; // $v1
	/* end block 1 */
	// End offset: 0x0007D9CC
	// End Line: 2469

	/* begin block 2 */
		// Start line: 4884
	/* end block 2 */
	// End Line: 4885

	/* begin block 3 */
		// Start line: 6539
	/* end block 3 */
	// End Line: 6540

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void Unpack_CellPtrs(void)
{
	unpack_cellptr_tbl[0] = (ulong)spool_regioninfo[spool_regionpos].region_to_unpack;
	unpack_cellptr_tbl[1] = (ulong)spool_regioninfo[spool_regionpos].target_barrel_region;
	unpack_cellptr_tbl[2] = (ulong)spool_regioninfo[spool_regionpos].cell_addr;

	unpack_cellpointers();
}



// decompiled code
// original method signature: 
// void /*$ra*/ SpecClutsSpooled()
 // line 2509, offset 0x0007c74c
	/* begin block 1 */
		// Start line: 2511
		// Start offset: 0x0007C74C
		// Variables:
	// 		char *loadaddr; // $s4
	// 		int i; // $s1
	// 		int j; // $s2
	// 		int tpage; // $s0
	// 		struct RECT specCluts; // stack offset -48

		/* begin block 1.1 */
			// Start line: 2522
			// Start offset: 0x0007C7F4
			// Variables:
		// 		int index; // $a3

			/* begin block 1.1.1 */
				// Start line: 2537
				// Start offset: 0x0007C91C
			/* end block 1.1.1 */
			// End offset: 0x0007C91C
			// End Line: 2537
		/* end block 1.1 */
		// End offset: 0x0007C95C
		// End Line: 2542
	/* end block 1 */
	// End offset: 0x0007C9B8
	// End Line: 2546

	/* begin block 2 */
		// Start line: 5647
	/* end block 2 */
	// End Line: 5648

	/* begin block 3 */
		// Start line: 5720
	/* end block 3 */
	// End Line: 5721

	/* begin block 4 */
		// Start line: 5721
	/* end block 4 */
	// End Line: 5722

	/* begin block 5 */
		// Start line: 5730
	/* end block 5 */
	// End Line: 5731

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SpecClutsSpooled(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	short sVar2;
	short sVar3;
	u_short uVar4;
	int iVar5;
	int iVar6;
	uint uVar7;
	u_short *puVar8;
	int iVar9;
	int iVar10;
	char *pcVar11;
	DVECTOR local_30;
	undefined4 local_2c;

	iVar9 = 0;
	local_30 = slot_clutpos[specialSlot];
	local_2c = DAT_000aa998;
	pcVar11 = specLoadBuffer;
	do {
		iVar5 = 7;
		if (iVar9 == 0) {
			iVar5 = 6;
		}
		iVar10 = 0;
		bVar1 = specTpages[((int)SHORT_000aa9bc + -1) * 2 + iVar9 + GameLevel * 0xc];
		uVar7 = (uint)bVar1;
		iVar6 = specialSlot + iVar9;
		carTpages[iVar5 + GameLevel * 8] = bVar1;
		(&tpageslots)[iVar6] = bVar1;
		tpageloaded[uVar7] = (char)specialSlot + (char)iVar9 + '\x01';
		sVar2 = (&tpagepos)[iVar6].x;
		(&slot_tpagepos)[iVar6].vx = sVar2;
		sVar3 = (&tpagepos)[iVar6].y;
		(&slot_tpagepos)[iVar6].vy = sVar3;
		uVar4 = GetTPage(0, 0, (int)sVar2, (int)sVar3);
		(&texture_pages)[uVar7] = uVar4;
		iVar9 = iVar9 + 1;
		if (0 < (&tpage_texamts)[uVar7]) {
			puVar8 = &texture_cluts + uVar7 * 0x20;
			do {
				LoadImage2(&local_30, pcVar11);
				pcVar11 = pcVar11 + 0x20;
				iVar10 = iVar10 + 1;
				uVar4 = GetClut((int)local_30.vx, (int)local_30.vy);
				*puVar8 = uVar4;
				IncrementClutNum((RECT *)&local_30);
				puVar8 = puVar8 + 1;
			} while (iVar10 < (&tpage_texamts)[uVar7]);
		}
	} while (iVar9 < 2);
	if (quickSpool != 1) {
		DrawSyncCallback(SpecialStartNextBlock);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CleanModelSpooled()
 // line 2549, offset 0x0007c9b8
	/* begin block 1 */
		// Start line: 2552
		// Start offset: 0x0007C9B8
		// Variables:
	// 		int *loadaddr; // $a1
	// 		int *mem; // $a3

		/* begin block 1.1 */
			// Start line: 2576
			// Start offset: 0x0007CA80
		/* end block 1.1 */
		// End offset: 0x0007CAD0
		// End Line: 2587
	/* end block 1 */
	// End offset: 0x0007CAFC
	// End Line: 2591

	/* begin block 2 */
		// Start line: 5870
	/* end block 2 */
	// End Line: 5871

	/* begin block 3 */
		// Start line: 5874
	/* end block 3 */
	// End Line: 5875

	/* begin block 4 */
		// Start line: 5876
	/* end block 4 */
	// End Line: 5877

	/* begin block 5 */
		// Start line: 5880
	/* end block 5 */
	// End Line: 5881

/* WARNING: Unknown calling convention yet parameter storage is locked */

void CleanModelSpooled(void)
{
	UNIMPLEMENTED();
	/*
	int *piVar1;
	ushort *puVar2;
	MODEL *pMVar3;
	int iVar4;
	int *piVar5;
	int *in_a3;

	piVar5 = (int *)specLoadBuffer;
	if (specBlocksToLoad == lastCleanBlock + -1) {
		piVar5 = (int *)(specLoadBuffer + 0xc);
		modelMemory = (int *)specmallocptr;
		gCarCleanModelPtr5[4] = (MODEL *)specmallocptr;
	}
	if (piVar5 < specLoadBuffer + 0x800) {
		do {
			iVar4 = *piVar5;
			piVar5 = piVar5 + 1;
			*modelMemory = iVar4;
			modelMemory = modelMemory + 1;
		} while (piVar5 < specLoadBuffer + 0x800);
	}
	pMVar3 = gCarCleanModelPtr5[4];
	if (&gCarCleanModelPtr5[4][1].poly_block < modelMemory) {
		in_a3 = (int *)((int)&gCarCleanModelPtr5[4]->shape_flags + gCarCleanModelPtr5[4]->poly_block);
	}
	if ((specBlocksToLoad == 0) || (in_a3 < modelMemory)) {
		piVar5 = &gCarCleanModelPtr5[4]->normals;
		piVar1 = &gCarCleanModelPtr5[4]->point_normals;
		specBlocksToLoad = 0;
		puVar2 = &gCarCleanModelPtr5[4]->shape_flags;
		modelMemory = in_a3;
		gCarCleanModelPtr5[4]->vertices =
			(int)&gCarCleanModelPtr5[4]->shape_flags + gCarCleanModelPtr5[4]->vertices;
		CAR_MODEL_000acbe8.nlist = (SVECTOR *)((int)&pMVar3->shape_flags + *piVar1);
		pMVar3->normals = (int)puVar2 + *piVar5;
		*(SVECTOR **)&pMVar3->point_normals = CAR_MODEL_000acbe8.nlist;
		pMVar3->poly_block = (int)&pMVar3->shape_flags + pMVar3->poly_block;
		CAR_MODEL_000acbe8.vlist = (SVECTOR *)pMVar3->vertices;
	}
	if (quickSpool != 1) {
		DrawSyncCallback(SpecialStartNextBlock);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DamagedModelSpooled()
 // line 2594, offset 0x0007cafc
	/* begin block 1 */
		// Start line: 2596
		// Start offset: 0x0007CAFC
		// Variables:
	// 		int *loadaddr; // $a1
	// 		int *mem; // $a3

		/* begin block 1.1 */
			// Start line: 2620
			// Start offset: 0x0007CBC0
		/* end block 1.1 */
		// End offset: 0x0007CBF8
		// End Line: 2629
	/* end block 1 */
	// End offset: 0x0007CC24
	// End Line: 2633

	/* begin block 2 */
		// Start line: 5981
	/* end block 2 */
	// End Line: 5982

	/* begin block 3 */
		// Start line: 5985
	/* end block 3 */
	// End Line: 5986

	/* begin block 4 */
		// Start line: 5986
	/* end block 4 */
	// End Line: 5987

	/* begin block 5 */
		// Start line: 5990
	/* end block 5 */
	// End Line: 5991

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DamagedModelSpooled(void)
{
	UNIMPLEMENTED();
	/*
	MODEL *pMVar1;
	int iVar2;
	int *piVar3;
	int *in_a3;

	piVar3 = (int *)specLoadBuffer;
	if (specBlocksToLoad == lengthDamBlock + -1) {
		piVar3 = (int *)(specLoadBuffer + damOffset);
		gCarDamModelPtr5[4] = (MODEL *)modelMemory;
	}
	if (piVar3 < specLoadBuffer + 0x800) {
		do {
			iVar2 = *piVar3;
			piVar3 = piVar3 + 1;
			*modelMemory = iVar2;
			modelMemory = modelMemory + 1;
		} while (piVar3 < specLoadBuffer + 0x800);
	}
	pMVar1 = gCarDamModelPtr5[4];
	if (&gCarDamModelPtr5[4][1].poly_block < modelMemory) {
		in_a3 = (int *)((int)&gCarDamModelPtr5[4]->shape_flags + gCarDamModelPtr5[4]->normals);
	}
	if ((specBlocksToLoad == 0) || (in_a3 < modelMemory)) {
		piVar3 = &gCarDamModelPtr5[4]->normals;
		specBlocksToLoad = 0;
		modelMemory = in_a3;
		gCarDamModelPtr5[4]->vertices =
			(int)&gCarDamModelPtr5[4]->shape_flags + gCarDamModelPtr5[4]->vertices;
		pMVar1->normals = (int)&pMVar1->shape_flags + *piVar3;
		pMVar1->poly_block = (int)&pMVar1->shape_flags + pMVar1->poly_block;
		pMVar1->point_normals = (int)&pMVar1->shape_flags + pMVar1->point_normals;
	}
	if (quickSpool != 1) {
		DrawSyncCallback(SpecialStartNextBlock);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ LowModelSpooled()
 // line 2635, offset 0x0007cc24
	/* begin block 1 */
		// Start line: 2637
		// Start offset: 0x0007CC24
		// Variables:
	// 		int *loadaddr; // $a1
	// 		int *mem; // $a3

		/* begin block 1.1 */
			// Start line: 2661
			// Start offset: 0x0007CCE8
		/* end block 1.1 */
		// End offset: 0x0007CD38
		// End Line: 2672
	/* end block 1 */
	// End offset: 0x0007CD64
	// End Line: 2676

	/* begin block 2 */
		// Start line: 6081
	/* end block 2 */
	// End Line: 6082

	/* begin block 3 */
		// Start line: 6084
	/* end block 3 */
	// End Line: 6085

	/* begin block 4 */
		// Start line: 6085
	/* end block 4 */
	// End Line: 6086

	/* begin block 5 */
		// Start line: 6089
	/* end block 5 */
	// End Line: 6090

/* WARNING: Unknown calling convention yet parameter storage is locked */

void LowModelSpooled(void)
{
	UNIMPLEMENTED();
	/*
	int *piVar1;
	ushort *puVar2;
	MODEL *pMVar3;
	int iVar4;
	int *piVar5;
	int *in_a3;

	piVar5 = (int *)specLoadBuffer;
	if (specBlocksToLoad == lengthLowBlock + -1) {
		piVar5 = (int *)(specLoadBuffer + lowOffset);
		gCarLowModelPtr5[4] = (MODEL *)modelMemory;
	}
	if (piVar5 < specLoadBuffer + 0x800) {
		do {
			iVar4 = *piVar5;
			piVar5 = piVar5 + 1;
			*modelMemory = iVar4;
			modelMemory = modelMemory + 1;
		} while (piVar5 < specLoadBuffer + 0x800);
	}
	pMVar3 = gCarLowModelPtr5[4];
	if (&gCarLowModelPtr5[4][1].poly_block < modelMemory) {
		in_a3 = (int *)((int)&gCarLowModelPtr5[4]->shape_flags + gCarLowModelPtr5[4]->poly_block);
	}
	if ((specBlocksToLoad == 0) || (in_a3 < modelMemory)) {
		piVar5 = &gCarLowModelPtr5[4]->normals;
		piVar1 = &gCarLowModelPtr5[4]->point_normals;
		specBlocksToLoad = 0;
		puVar2 = &gCarLowModelPtr5[4]->shape_flags;
		modelMemory = in_a3;
		gCarLowModelPtr5[4]->vertices =
			(int)&gCarLowModelPtr5[4]->shape_flags + gCarLowModelPtr5[4]->vertices;
		CAR_MODEL_000b8840.nlist = (SVECTOR *)((int)&pMVar3->shape_flags + *piVar1);
		pMVar3->normals = (int)puVar2 + *piVar5;
		*(SVECTOR **)&pMVar3->point_normals = CAR_MODEL_000b8840.nlist;
		pMVar3->poly_block = (int)&pMVar3->shape_flags + pMVar3->poly_block;
		CAR_MODEL_000b8840.vlist = (SVECTOR *)pMVar3->vertices;
	}
	if (quickSpool != 1) {
		DrawSyncCallback(SpecialStartNextBlock);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CleanSpooled()
 // line 2680, offset 0x0007cd64
	/* begin block 1 */
		// Start line: 2683
		// Start offset: 0x0007CD64
		// Variables:
	// 		char *loadaddr; // $a1

		/* begin block 1.1 */
			// Start line: 2702
			// Start offset: 0x0007CE8C
			// Variables:
		// 		struct MODEL *tempModel; // $a1
		/* end block 1.1 */
		// End offset: 0x0007CEE0
		// End Line: 2713
	/* end block 1 */
	// End offset: 0x0007CF0C
	// End Line: 2717

	/* begin block 2 */
		// Start line: 6189
	/* end block 2 */
	// End Line: 6190

	/* begin block 3 */
		// Start line: 6194
	/* end block 3 */
	// End Line: 6195

	/* begin block 4 */
		// Start line: 6196
	/* end block 4 */
	// End Line: 6197

	/* begin block 5 */
		// Start line: 6198
	/* end block 5 */
	// End Line: 6199

/* WARNING: Unknown calling convention yet parameter storage is locked */

void CleanSpooled(void)
{
	UNIMPLEMENTED();
	/*
	int *piVar1;
	char *pcVar2;
	int iVar3;
	int iVar4;
	MODEL *model;

	pcVar2 = specmallocptr;
	if (specBlocksToLoad == 6) {
		lastCleanBlock = *(int *)specmallocptr + 0x80b;
		if (lastCleanBlock < 0) {
			lastCleanBlock = *(int *)specmallocptr + 0x100a;
		}
		lastCleanBlock = lastCleanBlock >> 0xb;
		firstLowBlock = *(int *)specmallocptr + *(int *)(specmallocptr + 4) + 0xc;
		if (firstLowBlock < 0) {
			firstLowBlock = *(int *)specmallocptr + *(int *)(specmallocptr + 4) + 0x80b;
		}
		firstLowBlock = firstLowBlock >> 0xb;
		iVar4 = *(int *)specmallocptr + *(int *)(specmallocptr + 4) + *(int *)(specmallocptr + 8);
		iVar3 = iVar4 + 0x80b;
		if (iVar3 < 0) {
			iVar3 = iVar4 + 0x100a;
		}
		lengthLowBlock = (iVar3 >> 0xb) - firstLowBlock;
		lowOffset = (*(int *)specmallocptr + *(int *)(specmallocptr + 4)) -
			(firstLowBlock * 0x800 + -0xc);
		firstDamBlock = *(int *)specmallocptr + 0xc;
		if (firstDamBlock < 0) {
			firstDamBlock = *(int *)specmallocptr + 0x80b;
		}
		firstDamBlock = firstDamBlock >> 0xb;
		iVar3 = *(int *)specmallocptr + *(int *)(specmallocptr + 4) + 0x80b;
		if (iVar3 < 0) {
			iVar3 = *(int *)specmallocptr + *(int *)(specmallocptr + 4) + 0x100a;
		}
		lengthDamBlock = (iVar3 >> 0xb) - firstDamBlock;
		damOffset = *(int *)specmallocptr - (firstDamBlock * 0x800 + -0xc);
	}
	model = (MODEL *)(specmallocptr + 0xc);
	if (specBlocksToLoad == 7 - lastCleanBlock) {
		iVar3 = *(int *)(specmallocptr + 0x24);
		piVar1 = (int *)(specmallocptr + 0x20);
		*(int *)(specmallocptr + 0x1c) = (int)&model->shape_flags + *(int *)(specmallocptr + 0x1c);
		*(int *)(pcVar2 + 0x20) = (int)&model->shape_flags + *piVar1;
		*(int *)(pcVar2 + 0x24) = (int)&model->shape_flags + iVar3;
		whichCP = baseSpecCP;
		*(int *)(pcVar2 + 0x28) = (int)&model->shape_flags + *(int *)(pcVar2 + 0x28);
		buildNewCarFromModel(&CAR_MODEL_000acbe8, model, 0);
		specBlocksToLoad = 0;
	}
	if (quickSpool != 1) {
		DrawSyncCallback(SpecialStartNextBlock);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ LowSpooled()
 // line 2720, offset 0x0007e7c0
	/* begin block 1 */
		// Start line: 2723
		// Start offset: 0x0007E7C0
		// Variables:
	// 		char *loadaddr; // $v1

		/* begin block 1.1 */
			// Start line: 2728
			// Start offset: 0x0007E7D8
			// Variables:
		// 		struct MODEL *tempModel; // $a1
		/* end block 1.1 */
		// End offset: 0x0007E820
		// End Line: 2737
	/* end block 1 */
	// End offset: 0x0007E84C
	// End Line: 2741

	/* begin block 2 */
		// Start line: 10317
	/* end block 2 */
	// End Line: 10318

	/* begin block 3 */
		// Start line: 10319
	/* end block 3 */
	// End Line: 10320

	/* begin block 4 */
		// Start line: 10321
	/* end block 4 */
	// End Line: 10322

/* WARNING: Unknown calling convention yet parameter storage is locked */

void LowSpooled(void)
{
	UNIMPLEMENTED();
	/*
	MODEL *model;

	if (specBlocksToLoad == 0) {
		model = (MODEL *)(specmallocptr + lowOffset);
		model->vertices = (int)&model->shape_flags + model->vertices;
		model->normals = (int)&model->shape_flags + model->normals;
		model->poly_block = (int)&model->shape_flags + model->poly_block;
		model->point_normals = (int)&model->shape_flags + model->point_normals;
		buildNewCarFromModel(&CAR_MODEL_000b8840, model, 0);
	}
	if (quickSpool != 1) {
		DrawSyncCallback(SpecialStartNextBlock);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ Tada()
 // line 2744, offset 0x0007cf0c
	/* begin block 1 */
		// Start line: 2746
		// Start offset: 0x0007CF0C
		// Variables:
	// 		char *loadaddr; // $s1

		/* begin block 1.1 */
			// Start line: 2751
			// Start offset: 0x0007CF60
			// Variables:
		// 		struct RECT tpage; // stack offset -32
		// 		int spec_tpage; // $a0
		/* end block 1.1 */
		// End offset: 0x0007D018
		// End Line: 2764

		/* begin block 1.2 */
			// Start line: 2767
			// Start offset: 0x0007D018
			// Variables:
		// 		struct RECT tpage; // stack offset -24
		// 		int spec_tpage; // $a0
		/* end block 1.2 */
		// End offset: 0x0007D0EC
		// End Line: 2780

		/* begin block 1.3 */
			// Start line: 2783
			// Start offset: 0x0007D0EC
		/* end block 1.3 */
		// End offset: 0x0007D130
		// End Line: 2789
	/* end block 1 */
	// End offset: 0x0007D144
	// End Line: 2793

	/* begin block 2 */
		// Start line: 6312
	/* end block 2 */
	// End Line: 6313

	/* begin block 3 */
		// Start line: 6340
	/* end block 3 */
	// End Line: 6341

	/* begin block 4 */
		// Start line: 6341
	/* end block 4 */
	// End Line: 6342

	/* begin block 5 */
		// Start line: 6342
	/* end block 5 */
	// End Line: 6343

/* WARNING: Unknown calling convention yet parameter storage is locked */

void Tada(void)
{
	UNIMPLEMENTED();
	/*
	char *pcVar1;
	int slot;
	RECT local_20;
	RECT local_18;

	pcVar1 = specLoadBuffer;
	if (specialState == 2) {
		local_18.w = 0x40;
		slot = (int)specialSlot + 1;
		local_18.x = (&tpagepos)[slot].x;
		local_18.h = 0x10;
		local_18.y = (&tpagepos)[slot].y + (0xf - (short)specBlocksToLoad) * 0x10;
		if (specBlocksToLoad == 0xf) {
			update_slotinfo((uint)(byte)specTpages[((int)SHORT_000aa9bc + -1) * 2 + GameLevel * 0xc + 1],
				(int)specialSlot, &local_18);
		}
		LoadImage(&local_18, pcVar1);
	}
	else {
		if (2 < specialState) {
			if (specialState != 4) {
				return;
			}
			SetupSpecCosmetics(specLoadBuffer);
			FixCarCos(car_cosmetics + 4, MissionHeader->residentModels[4]);
			SetupSpecDenting(pcVar1 + 0xec);
			if (quickSpool == 1) {
				return;
			}
			DrawSyncCallback(SpecialStartNextBlock);
			return;
		}
		if (specialState != 1) {
			return;
		}
		slot = (int)specialSlot;
		local_20.w = 0x40;
		local_20.x = (&tpagepos)[slot].x;
		local_20.h = 0x10;
		local_20.y = (&tpagepos)[slot].y + (0xf - (short)specBlocksToLoad) * 0x10;
		if (specBlocksToLoad == 0xf) {
			update_slotinfo((uint)(byte)specTpages[((int)SHORT_000aa9bc + -1) * 2 + GameLevel * 0xc], slot,
				&local_20);
		}
		LoadImage(&local_20, pcVar1);
	}
	if (quickSpool != 1) {
		DrawSyncCallback(SpecialStartNextBlock);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SpecialStartNextBlock()
 // line 2799, offset 0x0007d144
	/* begin block 1 */
		// Start line: 2801
		// Start offset: 0x0007D144
		// Variables:
	// 		char *loadaddr; // $s0
	// 		int fileSector; // $t0
	/* end block 1 */
	// End offset: 0x0007D4D0
	// End Line: 2925

	/* begin block 2 */
		// Start line: 6482
	/* end block 2 */
	// End Line: 6483

	/* begin block 3 */
		// Start line: 6489
	/* end block 3 */
	// End Line: 6490

	/* begin block 4 */
		// Start line: 6490
	/* end block 4 */
	// End Line: 6491

	/* begin block 5 */
		// Start line: 6493
	/* end block 5 */
	// End Line: 6494

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SpecialStartNextBlock(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	char *local_10;
	undefined *offset;
	undefined func;

	local_10 = specLoadBuffer;
	DrawSyncCallback(0);
	if (specBlocksToLoad == 0) {
		iVar1 = specialState + 1;
		switch (specialState) {
		case 0:
		case 1:
			specBlocksToLoad = 0x10;
			specialState = iVar1;
			break;
		case 2:
		case 3:
			specBlocksToLoad = 1;
			specialState = iVar1;
			break;
		case 4:
			specBlocksToLoad = 7;
			specialState = iVar1;
			break;
		case 5:
		case 8:
			specBlocksToLoad = lengthLowBlock;
			specialState = iVar1;
			break;
		case 6:
			specBlocksToLoad = lastCleanBlock;
			specialState = iVar1;
			break;
		case 7:
			specBlocksToLoad = lengthDamBlock;
			specialState = iVar1;
			break;
		default:
			specBlocksToLoad = 0;
			specialState = iVar1;
		}
	}
	iVar1 = citylumps[GameLevel * 4 + 3].x;
	if (iVar1 < 0) {
		iVar1 = iVar1 + 0x7ff;
	}
	offset = &DAT_00001400 +
		(citystart[GameLevel] - (iVar1 >> 0xb)) + ((int)SHORT_000aa9bc + -1) * 0x2a;
	switch (specialState) {
	case 1:
		func = 0xc;
		offset = offset + (0x11 - specBlocksToLoad);
		break;
	case 2:
		func = 0xc;
		offset = offset + (0x21 - specBlocksToLoad);
		break;
	case 3:
		func = 0x4c;
		break;
	case 4:
		offset = offset + 0x21;
		func = 0xc;
		break;
	case 5:
		func = 100;
		iVar2 = 7;
		iVar1 = 0x29 - specBlocksToLoad;
		goto LAB_0007d470;
	case 6:
		func = 0xc0;
		iVar1 = ((firstLowBlock + lengthLowBlock) - specBlocksToLoad) + 0x22;
		iVar2 = lengthLowBlock;
	LAB_0007d470:
		offset = offset + iVar1;
		local_10 = specmallocptr + (iVar2 - specBlocksToLoad) * 0x800;
		break;
	case 7:
		func = 0xb8;
		offset = offset + (lastCleanBlock - specBlocksToLoad) + 0x22;
		break;
	case 8:
		func = 0xfc;
		offset = offset + ((firstDamBlock + lengthDamBlock) - specBlocksToLoad) + 0x22;
		break;
	case 9:
		func = 0x24;
		offset = offset + ((firstLowBlock + lengthLowBlock) - specBlocksToLoad) + 0x22;
		break;
	default:
		if (quickSpool == 1) {
			specModelValid = '\x01';
			specialState = 0;
			quickSpool = 0;
			specSpoolComplete = 0;
			return;
		}
		specSpoolComplete = 1;
		return;
	}
	RequestSpool(3, 0, (int)offset, 1, local_10, func);
	specBlocksToLoad = specBlocksToLoad + -1;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckSpecialSpool()
 // line 2956, offset 0x0007d4e0
	/* begin block 1 */
		// Start line: 2958
		// Start offset: 0x0007D4E0
		// Variables:
	// 		struct _CAR_DATA *lcp; // $a0
	// 		int ret; // $a3

		/* begin block 1.1 */
			// Start line: 2965
			// Start offset: 0x0007D51C
		/* end block 1.1 */
		// End offset: 0x0007D53C
		// End Line: 2969
	/* end block 1 */
	// End offset: 0x0007D6C8
	// End Line: 3022

	/* begin block 2 */
		// Start line: 6827
	/* end block 2 */
	// End Line: 6828

	/* begin block 3 */
		// Start line: 6828
	/* end block 3 */
	// End Line: 6829

	/* begin block 4 */
		// Start line: 6831
	/* end block 4 */
	// End Line: 6832

/* WARNING: Unknown calling convention yet parameter storage is locked */

void CheckSpecialSpool(void)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	int iVar2;
	uint uVar3;

	if ((startSpecSpool != -1) && (startSpecSpool + 400 < CameraCnt)) {
		if (specSpoolComplete == 0) {
			do {
				SpoolSYNC();
				iVar2 = DrawSync(1);
				if (iVar2 == 0) {
					SpecialStartNextBlock();
				}
				StartSpooling();
			} while (specSpoolComplete == 0);
		}
		specModelValid = '\x01';
		specialState = 0;
		specBlocksToLoad = 0;
		specSpoolComplete = 0;
		startSpecSpool = -1;
	}
	if ((((allowSpecSpooling != 0) && (specSpoolComplete != 1)) && (GameType != GAME_PURSUIT)) &&
		(SpecialByRegion[GameLevel * 0x14 + LoadedArea] != MissionHeader->residentModels[4] + -7)) {
		specModelValid = '\0';
		uVar3 = 0xd43fc;
		bVar1 = false;
		do {
			if (4 < MissionHeader->residentModels[*(byte *)(uVar3 + 0x177)]) {
				bVar1 = true;
			}
			uVar3 = uVar3 - 0x29c;
		} while (0xd1267 < uVar3);
		if (!bVar1) {
			startSpecSpool = CameraCnt;
			gCarDamModelPtr5[4] = (MODEL *)0x0;
			gCarCleanModelPtr5[4] = (MODEL *)0x0;
			SHORT_000aa9bc = *(short *)(SpecialByRegion + GameLevel * 0x14 + LoadedArea);
			gCarLowModelPtr5[4] = (MODEL *)0x0;
			bVar1 = specialState == 0;
			MissionHeader->residentModels[4] = SpecialByRegion[GameLevel * 0x14 + LoadedArea] + 7;
			if (bVar1) {
				SpecialStartNextBlock();
			}
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ QuickSpoolSpecial()
 // line 3025, offset 0x0007e84c
	/* begin block 1 */
		// Start line: 10949
	/* end block 1 */
	// End Line: 10950

	/* begin block 2 */
		// Start line: 10950
	/* end block 2 */
	// End Line: 10951

/* WARNING: Unknown calling convention yet parameter storage is locked */

void QuickSpoolSpecial(void)
{
	UNIMPLEMENTED();
	/*
	quickSpool = 1;
	gCarCleanModelPtr5[4] = (MODEL *)0x0;
	specialState = 0;
	specBlocksToLoad = 0;
	gCarDamModelPtr5[4] = (MODEL *)0x0;
	gCarLowModelPtr5[4] = (MODEL *)0x0;
	SHORT_000aa9bc = *(short *)(MissionHeader->residentModels + 4) + -7;
	do {
		SpoolSYNC();
		DrawSync(0);
		SpecialStartNextBlock();
		StartSpooling();
	} while (quickSpool == 1);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PrepareSecretCar()
 // line 3046, offset 0x0007e8dc
	/* begin block 1 */
		// Start line: 11011
	/* end block 1 */
	// End Line: 11012

	/* begin block 2 */
		// Start line: 11012
	/* end block 2 */
	// End Line: 11013

/* WARNING: Unknown calling convention yet parameter storage is locked */

void PrepareSecretCar(void)
{
	UNIMPLEMENTED();
	/*
	allowSpecSpooling = 0;
	PingOutAllSpecialCivCars();
	gCarDamModelPtr5[4] = (MODEL *)0x0;
	gCarCleanModelPtr5[4] = (MODEL *)0x0;
	gCarLowModelPtr5[4] = (MODEL *)0x0;
	SHORT_000aa9bc = 5;
	specModelValid = '\0';
	startSpecSpool = CameraCnt;
	MissionHeader->residentModels[4] = 0xc;
	specialState = 0;
	specBlocksToLoad = 0;
	SpecialStartNextBlock();
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitSpecSpool()
 // line 3063, offset 0x0007d6d8
	/* begin block 1 */
		// Start line: 7058
	/* end block 1 */
	// End Line: 7059

	/* begin block 2 */
		// Start line: 7059
	/* end block 2 */
	// End Line: 7060

	/* begin block 3 */
		// Start line: 7064
	/* end block 3 */
	// End Line: 7065

/* WARNING: Unknown calling convention yet parameter storage is locked */

void InitSpecSpool(void)
{
	UNIMPLEMENTED();
	/*
	if (((((((gCurrentMissionNumber == 2) || (gCurrentMissionNumber == 4)) ||
		(gCurrentMissionNumber == 6)) ||
		((((gCurrentMissionNumber == 7 || (gCurrentMissionNumber == 10)) ||
		((gCurrentMissionNumber == 0xb ||
			((gCurrentMissionNumber == 0xc || (gCurrentMissionNumber == 0xd)))))) ||
			(gCurrentMissionNumber == 0x10)))) ||
			(((((gCurrentMissionNumber == 0x12 || (gCurrentMissionNumber == 0x13)) ||
		(gCurrentMissionNumber == 0x14)) ||
				((gCurrentMissionNumber == 0x18 || (gCurrentMissionNumber == 0x1a)))) ||
				((gCurrentMissionNumber == 0x1b ||
				((gCurrentMissionNumber == 0x1d || (gCurrentMissionNumber == 0x1e)))))))) ||
					(((((gCurrentMissionNumber == 0x1f ||
		(((((gCurrentMissionNumber == 0x21 || (gCurrentMissionNumber == 0x23)) ||
						(gCurrentMissionNumber == 0x26)) ||
			((gCurrentMissionNumber == 0x27 || (gCurrentMissionNumber == 0x28)))) ||
			(gCurrentMissionNumber == 0x3a)))) ||
			((((gCurrentMissionNumber == 0x3b || (gCurrentMissionNumber == 0x3c)) ||
						((gCurrentMissionNumber == 0x3d ||
				(((gCurrentMissionNumber == 0x3e || (gCurrentMissionNumber == 0x3f)) ||
							(gCurrentMissionNumber == 0x40)))))) ||
					(((gCurrentMissionNumber == 0x41 || (gCurrentMissionNumber == 0x46)) ||
				(gCurrentMissionNumber == 0x4e)))))) ||
						(((gCurrentMissionNumber == 0x56 || (gCurrentMissionNumber == 0x5e)) ||
						((gCurrentMissionNumber == 0x1f2 ||
							(((gCurrentMissionNumber == 499 || (gCurrentMissionNumber == 500)) ||
							(gCurrentMissionNumber == 0x1f5)))))))) ||
								(((gCurrentMissionNumber == 0x1f6 || (gCurrentMissionNumber == 0x1f7)) ||
						((gCurrentMissionNumber == 0x1f8 ||
									((((gCurrentMissionNumber == 0x1f9 || (gCurrentMissionNumber == 0xe4)) ||
							((gCurrentMissionNumber == 0xe5 ||
										((((gCurrentMissionNumber == 0xec || (gCurrentMissionNumber == 0xed)) ||
								(gCurrentMissionNumber == 0xf4)) ||
											((gCurrentMissionNumber == 0xf5 || (gCurrentMissionNumber == 0xfc)))))))) ||
											(gCurrentMissionNumber == 0xfd)))))))))) ||
										(((gCurrentMissionNumber == 0x1a4 || (gCurrentMissionNumber == 0x1a5)) ||
		((((((gCurrentMissionNumber == 0x1ac ||
											(((gCurrentMissionNumber == 0x1ad || (gCurrentMissionNumber == 0x1b4)) ||
			(gCurrentMissionNumber == 0x1b5)))) ||
												(((gCurrentMissionNumber == 0x1bc || (gCurrentMissionNumber == 0x1bd)) ||
			(gCurrentMissionNumber == 0x160)))) ||
													((gCurrentMissionNumber == 0x161 || (gCurrentMissionNumber == 0x168)))) ||
			((gCurrentMissionNumber == 0x169 ||
			(((gCurrentMissionNumber == 0x170 || (gCurrentMissionNumber == 0x171)) ||
				(gCurrentMissionNumber == 0x178)))))) ||
				((((gCurrentMissionNumber == 0x179 || (gCurrentMissionNumber == 0x1e0)) ||
			(gCurrentMissionNumber == 0x1e1)) ||
					(((gCurrentMissionNumber == 0x1e2 || (gCurrentMissionNumber == 0x1e3)) ||
					((gCurrentMissionNumber == 0x1e4 ||
						(((gCurrentMissionNumber == 0x1e5 || (gCurrentMissionNumber == 0x1e6)) ||
						(gCurrentMissionNumber == 0x1e7)))))))))))))) {
		allowSpecSpooling = 0;
	}
	else {
		allowSpecSpooling = 1;
	}
	specModelValid = '\x01';
	specialState = 0;
	specBlocksToLoad = 0;
	quickSpool = 0;
	specSpoolComplete = 0;
	startSpecSpool = -1;
	return;
	*/
}





