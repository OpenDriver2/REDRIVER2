#include "THISDUST.H"

#include "LIBETC.H"

#include "SYSTEM.H"
#include "XAPLAY.H"
#include "LOADVIEW.H"

#include <string.h>

char _overlay_buffer[0x50000];		// 0x1C0000
char _frontend_buffer[0x50000];		// 0xFB400

char* LevelFiles[] = {
	"LEVELS\\CHICAGO.LEV",
	"LEVELS\\HAVANA.LEV",
	"LEVELS\\VEGAS.LEV",
	"LEVELS\\RIO.LEV",
};

char* LoadingScreenNames[] = {
	"GFX\\LOADCHIC.TIM",
	"GFX\\LOADHAVA.TIM",
	"GFX\\LOADVEGA.TIM",
	"GFX\\LOADRIO.TIM",
};

CdlFILE currentfileinfo;
char currentfilename[128] = { 0 };

DRAW_MODE draw_mode_pal =
{ 0, 0, 0, 0, 512, 256, 0, 16 };

DRAW_MODE draw_mode_ntsc =
{ 0, 0, 0, 8, 512, 240, 0, 0 };

DB MPBuff[2][2];
DB* last;
DB* current;

u_long _tempOT1[OTSIZE];
u_long _tempOT2[OTSIZE];

char _tempPrimTab1[0x8000];		// 0xFB400
char _tempPrimTab2[0x8000];		// 0x119400

// TODO: to game vars


// decompiled code
// original method signature: 
// void /*$ra*/ ClearMem(char *mem /*$a0*/, int size /*$a1*/)
 // line 389, offset 0x0007f3e8
	/* begin block 1 */
		// Start line: 390
		// Start offset: 0x0007F3E8
		// Variables:
	// 		char *end; // $v1
	/* end block 1 */
	// End offset: 0x0007F47C
	// End Line: 416

	/* begin block 2 */
		// Start line: 2270
	/* end block 2 */
	// End Line: 2271

	/* begin block 3 */
		// Start line: 778
	/* end block 3 */
	// End Line: 779

	/* begin block 4 */
		// Start line: 2273
	/* end block 4 */
	// End Line: 2274

void ClearMem(char *mem, int size)
{
	UNIMPLEMENTED();
	/*
	int *puVar1;

	puVar1 = (int *)(mem + size);
	while ((((uint)mem & 3) != 0 && (mem < puVar1))) {
		*mem = 0;
		mem = (char *)((int)mem + 1);
	}
	while (mem <= puVar1 + -4) {
		*(int *)mem = 0;
		((int *)mem)[1] = 0;
		((int *)mem)[2] = 0;
		((int *)mem)[3] = 0;
		mem = (char *)((int *)mem + 4);
	}
	while (mem <= puVar1 + -1) {
		*(int *)mem = 0;
		mem = (char *)((int *)mem + 1);
	}
	while (mem < puVar1) {
		*mem = 0;
		mem = (char *)((int)mem + 1);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ setMem8(unsigned char *mem /*$a0*/, unsigned char val /*$a1*/, int size /*$a2*/)
 // line 427, offset 0x0007f47c
	/* begin block 1 */
		// Start line: 428
		// Start offset: 0x0007F47C
		// Variables:
	// 		unsigned char *end; // $v1
	// 		unsigned long lval; // $a3
	/* end block 1 */
	// End offset: 0x0007F524
	// End Line: 459

	/* begin block 2 */
		// Start line: 2334
	/* end block 2 */
	// End Line: 2335

	/* begin block 3 */
		// Start line: 2346
	/* end block 3 */
	// End Line: 2347

void setMem8(unsigned char *mem, unsigned char val, int size)
{
	UNIMPLEMENTED();
	/*
	int *puVar1;
	int uVar2;

	uVar2 = CONCAT22(CONCAT11(val, val), CONCAT11(val, val));
	puVar1 = (int *)(mem + size);
	while ((((uint)mem & 3) != 0 && (mem < puVar1))) {
		*mem = val;
		mem = (unsigned char *)((int)mem + 1);
	}
	while (mem <= puVar1 + -4) {
		*(int *)mem = uVar2;
		((int *)mem)[1] = uVar2;
		((int *)mem)[2] = uVar2;
		((int *)mem)[3] = uVar2;
		mem = (unsigned char *)((int *)mem + 4);
	}
	while (mem <= puVar1 + -1) {
		*(int *)mem = uVar2;
		mem = (unsigned char *)((int *)mem + 1);
	}
	while (mem < puVar1) {
		*mem = val;
		mem = (unsigned char *)((int)mem + 1);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ setMem16(unsigned short *mem /*$a0*/, unsigned short val /*$a1*/, int size /*$a2*/)
 // line 469, offset 0x0007f524
	/* begin block 1 */
		// Start line: 470
		// Start offset: 0x0007F524
		// Variables:
	// 		unsigned short *end; // $a3
	// 		unsigned long lval; // $a2
	/* end block 1 */
	// End offset: 0x0007F5B4
	// End Line: 495

	/* begin block 2 */
		// Start line: 2424
	/* end block 2 */
	// End Line: 2425

	/* begin block 3 */
		// Start line: 2435
	/* end block 3 */
	// End Line: 2436

void setMem16(ushort *mem, ushort val, int size)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	int uVar2;
	int *puVar3;

	puVar3 = (int *)(mem + size);
	uVar2 = CONCAT22(val, val);
	if (((uint)mem & 2) != 0) {
		bVar1 = mem < puVar3;
		do {
			if (!bVar1) break;
			*mem = val;
			mem = (ushort *)((int)mem + 2);
			bVar1 = mem < puVar3;
		} while (((uint)mem & 2) != 0);
	}
	while (mem <= puVar3 + -4) {
		*(int *)mem = uVar2;
		((int *)mem)[1] = uVar2;
		((int *)mem)[2] = uVar2;
		((int *)mem)[3] = uVar2;
		mem = (ushort *)((int *)mem + 4);
	}
	while (mem < puVar3) {
		*mem = val;
		mem = (ushort *)((int)mem + 2);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ Init_FileSystem()
 // line 580, offset 0x0007f848
	/* begin block 1 */
		// Start line: 1160
	/* end block 1 */
	// End Line: 1161

	/* begin block 2 */
		// Start line: 4149
	/* end block 2 */
	// End Line: 4150

/* WARNING: Unknown calling convention yet parameter storage is locked */

void Init_FileSystem(void)
{
	CdInit();
	VSync(3);
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoCDRetry()
 // line 622, offset 0x0007f870
	/* begin block 1 */
		// Start line: 624
		// Start offset: 0x0007F870
		// Variables:
	// 		static int retries; // offset 0xc
	// 		unsigned char result[8]; // stack offset -16
	/* end block 1 */
	// End offset: 0x0007F8B8
	// End Line: 633

	/* begin block 2 */
		// Start line: 4231
	/* end block 2 */
	// End Line: 4232

	/* begin block 3 */
		// Start line: 4232
	/* end block 3 */
	// End Line: 4233

	/* begin block 4 */
		// Start line: 4235
	/* end block 4 */
	// End Line: 4236

/* WARNING: Unknown calling convention yet parameter storage is locked */

int gNumCDRetries = 0;

void DoCDRetry(void)
{
	bool bVar1;
	int iVar2;

	iVar2 = gNumCDRetries + 1;
	bVar1 = 9 < gNumCDRetries;
	gNumCDRetries = iVar2;
	if (bVar1) {
		CdInit();
		VSync(3);
		gNumCDRetries = 0;
	}
	return;
}

// decompiled code
// original method signature: 
// int /*$ra*/ Loadfile(char *name /*$a2*/, char *addr /*$s2*/)
 // line 646, offset 0x0007f354
	/* begin block 1 */
		// Start line: 647
		// Start offset: 0x0007F354
		// Variables:
	// 		char namebuffer[64]; // stack offset -88
	// 		unsigned char result[8]; // stack offset -24
	// 		int nread; // $s0
	/* end block 1 */
	// End offset: 0x0007F3E8
	// End Line: 670

	/* begin block 2 */
		// Start line: 1292
	/* end block 2 */
	// End Line: 1293

// loads whole file into buffer
int Loadfile(char *name, char *addr)
{
	char namebuffer[64];
#ifndef PSX
	int fileSize = 0;

	sprintf(namebuffer, "DRIVER2\\%s", name);

	FILE* fptr = fopen(namebuffer, "rb");
	if (!fptr)
	{
		eprinterr("Cannot open %s!\n", namebuffer);
		return 0;
	}

	fseek(fptr, 0, SEEK_END);
	fileSize = ftell(fptr);

	fseek(fptr, 0, SEEK_SET);
	int numRead = fread(addr, 1, fileSize, fptr);

	fclose(fptr);

	return numRead;
#else // PSX
	UNIMPLEMENTED();
	return 0;

	/*
	int status;
	int rstatus;
	char filename[64];
	unsigned char res[8];

	sprintf(filename, "\\DRIVER2\\%s;1", name);
	do {
		status = CdReadFile(filename, addr, 0);
		if (status != 0) {
			rstatus = CdReadSync(0, res);
			if (rstatus == 0) {
				return status;
			}
		}
		status = CdDiskReady(0);
		if (status != 2) {
			DoCDRetry();
		}
	} while (true);
	*/
#endif // PSX
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadfileSeg(char *name /*$v0*/, char *addr /*$s1*/, int offset /*$s5*/, int loadsize /*$fp*/)
 // line 759, offset 0x0007e9d0
	/* begin block 1 */
		// Start line: 760
		// Start offset: 0x0007E9D0
		// Variables:
	// 		char namebuffer[64]; // stack offset -2192
	// 		unsigned char result[8]; // stack offset -2128
	// 		int sector; // $s2
	// 		int nsectors; // $s5
	// 		char sectorbuffer[2048]; // stack offset -2120
	// 		struct CdlFILE info; // stack offset -72
	// 		struct CdlLOC pos; // stack offset -48
	// 		int i; // $a2
	// 		int toload; // $s4
	// 		int first; // $a0
	/* end block 1 */
	// End offset: 0x0007ECF0
	// End Line: 879

	/* begin block 2 */
		// Start line: 1518
	/* end block 2 */
	// End Line: 1519


// loads file partially into buffer
int LoadfileSeg(char *name, char *addr, int offset, int loadsize)
{
	char namebuffer[64];
#ifndef PSX
	int fileSize = 0;

	sprintf(namebuffer, "DRIVER2\\%s", name);

	FILE* fptr = fopen(namebuffer, "rb");
	if (!fptr)
	{
		eprinterr("Cannot open %s!\n", namebuffer);
		return 0;
	}

	fseek(fptr, 0, SEEK_END);
	fileSize = ftell(fptr);

	if (loadsize > fileSize)
		loadsize = fileSize;

	fseek(fptr, offset, SEEK_SET);
	int numRead = fread(addr, 1, loadsize, fptr);

	fclose(fptr);

	return numRead;
#else // PSX
	UNIMPLEMENTED();

	sprintf(namebuffer, "\\DRIVER2\\%s;1", name);

	/*

	int iVar1;
	CdlFILE *pCVar2;
	int iVar3;
	char *pcVar4;
	int iVar5;
	int iVar6;
	uint uVar7;
	char acStack2192[64];
	unsigned char auStack2128[8];
	char local_848[2072];
	CdlLOC auStack48;

	sprintf(acStack2192, "\\DRIVER2\\%s;1", name);
	iVar1 = strcmp(currentfilename, acStack2192);
	if (iVar1 != 0) {
		strcpy(currentfilename, acStack2192);
		while (pCVar2 = CdSearchFile(&currentfileinfo, acStack2192), pCVar2 == (CdlFILE *)0x0) {
			DoCDRetry();
		}
	}
	iVar1 = offset;
	if (offset < 0) {
		iVar1 = offset + 0x7ff;
	}
	iVar3 = CdPosToInt((CdlLOC *)&currentfileinfo);
	iVar3 = (iVar1 >> 0xb) + iVar3;
	uVar7 = offset & 0x7ff;
	iVar1 = loadsize;
	if (uVar7 != 0) {
		CdIntToPos(iVar3, &auStack48);
		do {
			iVar1 = CdDiskReady(0);
			if (iVar1 != 2) {
				DoCDRetry();
			}
			iVar1 = CdControlB(2, &auStack48, 0);
		} while (((iVar1 == 0) || (iVar1 = CdRead(1, local_848, 0x80), iVar1 == 0)) ||
			(iVar1 = CdReadSync(0, auStack2128), iVar1 != 0));
		if (loadsize <= (int)(0x800 - uVar7)) {
			iVar1 = uVar7 + loadsize;
			while ((int)uVar7 < iVar1) {
				pcVar4 = local_848 + uVar7;
				uVar7 = uVar7 + 1;
				*addr = *pcVar4;
				addr = addr + 1;
			}
			return loadsize;
		}
		iVar1 = loadsize - (0x800 - uVar7);
		iVar3 = iVar3 + 1;
		if (uVar7 < 0x800) {
			do {
				pcVar4 = local_848 + uVar7;
				uVar7 = uVar7 + 1;
				*addr = *pcVar4;
				addr = addr + 1;
			} while ((int)uVar7 < 0x800);
		}
	}
	iVar6 = iVar1;
	if (iVar1 < 0) {
		iVar6 = iVar1 + 0x7ff;
	}
	iVar6 = iVar6 >> 0xb;
	if (iVar6 != 0) {
		CdIntToPos(iVar3, &auStack48);
		iVar3 = iVar3 + iVar6;
		do {
			iVar5 = CdDiskReady(0);
			if (iVar5 != 2) {
				DoCDRetry();
			}
			iVar5 = CdControlB(2, &auStack48, 0);
		} while (((iVar5 == 0) || (iVar5 = CdRead(iVar6, addr, 0x80), iVar5 == 0)) ||
			(iVar5 = CdReadSync(0, auStack2128), iVar5 != 0));
		addr = addr + iVar6 * 0x800;
		iVar1 = iVar1 + iVar6 * -0x800;
	}
	if (0 < iVar1) {
		CdIntToPos(iVar3, &auStack48);
		do {
			iVar3 = CdDiskReady(0);
			if (iVar3 != 2) {
				DoCDRetry();
			}
			iVar3 = CdControlB(2, &auStack48, 0);
		} while (((iVar3 == 0) || (iVar3 = CdRead(1, local_848, 0x80), iVar3 == 0)) ||
			(iVar3 = CdReadSync(0, auStack2128), iVar3 != 0));
		iVar3 = 0;
		if (0 < iVar1) {
			do {
				pcVar4 = local_848 + iVar3;
				iVar3 = iVar3 + 1;
				*addr = *pcVar4;
				addr = addr + 1;
			} while (iVar3 < iVar1);
		}
	}
	return loadsize;
	*/
#endif // PSX
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReportMode(int on /*$s0*/)
 // line 952, offset 0x0007f8b8
	/* begin block 1 */
		// Start line: 953
		// Start offset: 0x0007F8B8
		// Variables:
	// 		static unsigned char param[8]; // offset 0x0
	/* end block 1 */
	// End offset: 0x0007F8F4
	// End Line: 967

	/* begin block 2 */
		// Start line: 4571
	/* end block 2 */
	// End Line: 4572

	/* begin block 3 */
		// Start line: 4891
	/* end block 3 */
	// End Line: 4892

void ReportMode(int on)
{
	UNIMPLEMENTED();
	/*
	static char param_25 = 0;

	int iVar1;

	iVar1 = XAPrepared();
	if (iVar1 == 0) {
		param_25 = 0x80;
		if (on != 0) {
			param_25 = 0x84;
		}
		CdControlB(0xe, &param_25, 0);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ data_ready()
 // line 978, offset 0x0007fa44
	/* begin block 1 */
		// Start line: 5546
	/* end block 1 */
	// End Line: 5547

	/* begin block 2 */
		// Start line: 1956
	/* end block 2 */
	// End Line: 1957

	/* begin block 3 */
		// Start line: 5547
	/* end block 3 */
	// End Line: 5548

/* WARNING: Unknown calling convention yet parameter storage is locked */

static unsigned char endread = 0;
static unsigned char load_complete = 0;

void data_ready(void)
{
	UNIMPLEMENTED();
	/*
	if (endread != '\0') {
		CdDataCallback(0);
		load_complete = '\x01';
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ sector_ready(unsigned char intr /*$a0*/, unsigned char *result /*$a1*/)
 // line 987, offset 0x0007fa74
	/* begin block 1 */
		// Start line: 988
		// Start offset: 0x0007FA74

		/* begin block 1.1 */
			// Start line: 1004
			// Start offset: 0x0007FAE4
			// Variables:
		// 		struct CdlLOC p; // stack offset -16
		/* end block 1.1 */
		// End offset: 0x0007FB34
		// End Line: 1014
	/* end block 1 */
	// End offset: 0x0007FB44
	// End Line: 1015

	/* begin block 2 */
		// Start line: 5564
	/* end block 2 */
	// End Line: 5565

static int current_sector = 0; // offset 0xAB27C
static char *current_address = NULL; // offset 0xAB288
static int sectors_left = 0; // offset 0xAB280
static int sectors_read = 0; // offset 0xAB284
static int sectors_this_chunk = 0; // offset 0xAB174
static int sectors_to_read = 0; // offset 0xAB170

void sector_ready(unsigned char intr, unsigned char *result)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	CdlLOC auStack16;

	if (intr == '\x01') {
		CdGetSector(current_address, 0x200);
		current_address = current_address + 0x800;
		current_sector = current_sector + 1;
		sectors_left = sectors_left + -1;
		if (sectors_left == 0) {
			endread = '\x01';
			CdReadyCallback(0);
			CdControlF(9, 0);
		}
	}
	else {
		if ((*result & 0x10) != 0) {
			CdReadyCallback(0);
			do {
				iVar1 = CdDiskReady(1);
			} while (iVar1 != 2);
			CdReadyCallback(sector_ready);
		}
		CdIntToPos(current_sector, &auStack16);
		CdControlF(0x1b, &auStack16);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ loadsectors(char *addr /*$a0*/, int sector /*$v0*/, int nsectors /*$a2*/)
 // line 1017, offset 0x0007f904
	/* begin block 1 */
		// Start line: 1018
		// Start offset: 0x0007F904
		// Variables:
	// 		struct CdlLOC pos; // stack offset -16
	/* end block 1 */
	// End offset: 0x0007F984
	// End Line: 1035

	/* begin block 2 */
		// Start line: 5021
	/* end block 2 */
	// End Line: 5022

	/* begin block 3 */
		// Start line: 5026
	/* end block 3 */
	// End Line: 5027

void loadsectors(char *addr, int sector, int nsectors)
{
	UNIMPLEMENTED();
	/*

	CdlLOC auStack16;

	load_complete = '\0';
	endread = '\0';
	current_sector = sector;
	sectors_left = nsectors;
	current_address = addr;
	CdIntToPos(sector, &auStack16);
	CdControlF(0x1b, &auStack16);
	CdDataCallback(data_ready);
	CdReadyCallback(sector_ready);
	do {
	} while (load_complete == '\0');
	ShowLoading();
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ EnableDisplay()
 // line 1221, offset 0x0007f984
	/* begin block 1 */
		// Start line: 1223
		// Start offset: 0x0007F984
		// Variables:
	// 		int i; // $s1
	/* end block 1 */
	// End offset: 0x0007F9F0
	// End Line: 1230

	/* begin block 2 */
		// Start line: 5256
	/* end block 2 */
	// End Line: 5257

	/* begin block 3 */
		// Start line: 5443
	/* end block 3 */
	// End Line: 5444

	/* begin block 4 */
		// Start line: 5444
	/* end block 4 */
	// End Line: 5445

	/* begin block 5 */
		// Start line: 5446
	/* end block 5 */
	// End Line: 5447

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void EnableDisplay(void)
{
	int i;

	i = 0;
	if (NumPlayers)
	{
		for (i = 0; i < NumPlayers; i++)
		{
			ClearOTagR(MPBuff[i][0].ot, 0x1080);
			ClearOTagR(MPBuff[i][1].ot, 0x1080);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisableDisplay()
 // line 1239, offset 0x0007f9f0
	/* begin block 1 */
		// Start line: 5472
	/* end block 1 */
	// End Line: 5473

	/* begin block 2 */
		// Start line: 5482
	/* end block 2 */
	// End Line: 5483

	/* begin block 3 */
		// Start line: 5483
	/* end block 3 */
	// End Line: 5484

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DisableDisplay(void)
{
	SetDispMask(0);
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SwapDrawBuffers()
 // line 1253, offset 0x0007f6fc
	/* begin block 1 */
		// Start line: 1255
		// Start offset: 0x0007F6FC
	/* end block 1 */
	// End offset: 0x0007F7C0
	// End Line: 1303

	/* begin block 2 */
		// Start line: 4524
	/* end block 2 */
	// End Line: 4525

	/* begin block 3 */
		// Start line: 2506
	/* end block 3 */
	// End Line: 2507

	/* begin block 4 */
		// Start line: 4525
	/* end block 4 */
	// End Line: 4526

	/* begin block 5 */
		// Start line: 4535
	/* end block 5 */
	// End Line: 4536

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SwapDrawBuffers(void)
{
	UNIMPLEMENTED();

	/*
	DrawSync(0);
	if (DoNotSwap == 0) {
		PutDispEnv(&current->disp);
		PutDrawEnv(&current->draw);
	}
	DoNotSwap = 0;
	PutDrawEnv(&current->draw);
	DrawOTag(current->ot + 0x107f);
	if ((FrameCnt & 1U) == 0) {
		current = &DB_000e0938;
		last = &MPBuff;
	}
	else {
		current = &MPBuff;
		last = &DB_000e0938;
	}
	ClearOTagR(current->ot, (int)&DAT_00001080);
	current->primptr = current->primtab;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SwapDrawBuffers2(int player /*$s0*/)
 // line 1310, offset 0x0007ecf0
	/* begin block 1 */
		// Start line: 1311
		// Start offset: 0x0007ECF0
		// Variables:
	// 		int toggle; // $v1
	/* end block 1 */
	// End offset: 0x0007EDDC
	// End Line: 1340

	/* begin block 2 */
		// Start line: 2221
	/* end block 2 */
	// End Line: 2222

	/* begin block 3 */
		// Start line: 2653
	/* end block 3 */
	// End Line: 2654

void SwapDrawBuffers2(int player)
{
	UNIMPLEMENTED();

	/*
	uint uVar1;

	DrawSync(0);
	if (player == 0) {
		PutDispEnv(&current->disp);
	}
	PutDrawEnv(&current->draw);
	DrawOTag(current->ot + 0x107f);
	if (player == 1) {
		uVar1 = FrameCnt & 1;
		MPcurrent2 = &MPBuff + (1 - uVar1);
		MPlast2 = &MPBuff + uVar1;
		PTR_000ab2b4 = (DB *)(&DAT_000e09b8 + (1 - uVar1) * 0x80);
		PTR_000ab29c = (DB *)(&DAT_000e09b8 + uVar1 * 0x80);
	}
	current = (&MPcurrent2)[1 - player];
	last = (&MPlast2)[1 - player];
	ClearOTagR(current->ot, (int)&DAT_00001080);
	current->primptr = current->primtab;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdatePadData()
 // line 1349, offset 0x0007fa10
	/* begin block 1 */
		// Start line: 5702
	/* end block 1 */
	// End Line: 5703

	/* begin block 2 */
		// Start line: 5703
	/* end block 2 */
	// End Line: 5704

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdatePadData(void)
{
	UNIMPLEMENTED();
	/*
	ReadControllers();
	paddp = Pads[0].mapnew;
	padd = Pads[0].mapped;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDrawBuffers()
 // line 1364, offset 0x0007eddc
	/* begin block 1 */
		// Start line: 1366
		// Start offset: 0x0007EDDC
		// Variables:
	// 		struct RECT rect; // stack offset -24
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x0007EF0C
	// End Line: 1411

	/* begin block 2 */
		// Start line: 2745
	/* end block 2 */
	// End Line: 2746

	/* begin block 3 */
		// Start line: 2770
	/* end block 3 */
	// End Line: 2771

	/* begin block 4 */
		// Start line: 2771
	/* end block 4 */
	// End Line: 2772

	/* begin block 5 */
		// Start line: 2775
	/* end block 5 */
	// End Line: 2776

/* WARNING: Unknown calling convention yet parameter storage is locked */

void SetupDrawBuffers(void)
{
	UNIMPLEMENTED();

	/*
	DB *pDVar1;
	int iVar2;
	DB **ppDVar3;
	DB *pDVar4;
	DB **ppDVar5;
	undefined2 local_18;
	undefined2 local_16;
	undefined2 local_14;
	undefined2 local_12;

	SetDefDispEnv(0xe0924, 0, 0x100, 0x140, 0x100);
	SetDefDispEnv(0xe09a4, 0, 0, 0x140, 0x100);
	MPBuff.disp.screen.h = 0x100;
	DB_000e0938.disp.screen.h = 0x100;
	MPBuff.disp.screen.x = draw_mode_pal.framex;
	DB_000e0938.disp.screen.x = draw_mode_pal.framex;
	MPBuff.disp.screen.y = draw_mode_pal.framey;
	DB_000e0938.disp.screen.y = draw_mode_pal.framey;
	if (NoPlayerControl == 0) {
		SetupDrawBufferData((uint)NumPlayers);
	}
	else {
		SetupDrawBufferData(1);
	}
	ppDVar5 = &MPlast2;
	pDVar1 = &MPBuff;
	pDVar4 = &DB_000e0938;
	ppDVar3 = &MPcurrent2;
	iVar2 = 1;
	do {
		*ppDVar5 = pDVar4;
		ppDVar5 = ppDVar5 + 1;
		pDVar4 = pDVar4 + 2;
		*ppDVar3 = pDVar1;
		ppDVar3 = ppDVar3 + 1;
		iVar2 = iVar2 + -1;
		pDVar1 = pDVar1 + 2;
	} while (-1 < iVar2);
	local_14 = 0x140;
	local_18 = 0;
	local_16 = 0;
	local_12 = 0x200;
	current = MPcurrent2;
	last = MPlast2;
	ClearImage(&local_18, 0, 0, 0);
	DrawSync(0);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDrawBufferData(int num_players /*stack 0*/)
 // line 1429, offset 0x0007ef0c
	/* begin block 1 */
		// Start line: 1430
		// Start offset: 0x0007EF0C
		// Variables:
	// 		unsigned long *otpt; // $s2
	// 		unsigned char *primpt; // $s1
	// 		unsigned char *PRIMpt; // $fp
	// 		int x[2]; // stack offset -72
	// 		int y[2]; // stack offset -64
	// 		int i; // $s3
	// 		int j; // $s6
	// 		int toggle; // $s7
	// 		int height; // stack offset -56
	/* end block 1 */
	// End offset: 0x0007F118
	// End Line: 1523

	/* begin block 2 */
		// Start line: 2915
	/* end block 2 */
	// End Line: 2916

	/* begin block 3 */
		// Start line: 2934
	/* end block 3 */
	// End Line: 2935

void SetupDrawBufferData(int num_players)
{
	UNIMPLEMENTED();

	/*
	bool bVar1;
	char *pcVar2;
	undefined *puVar3;
	int iVar4;
	DB *pBuff;
	int iVar5;
	int local_48[6];
	int local_30;

	if (num_players == 1) {
		local_48[4] = 0x100;
		local_48[0] = 0;
		local_48[2] = 0;
		local_48[1] = 0;
		local_48[3] = 0;
	}
	else {
		if (num_players == 2) {
			local_48[3] = 0x80;
			local_48[4] = 0x7f;
			local_48[0] = 0;
			local_48[2] = 0;
			local_48[1] = 0;
		}
		else {
			while (FrameCnt != 0x78654321) {
				trap(0x400);
			}
		}
	}
	SetGeomOffset(0xa0, local_48[4] >> 1);
	bVar1 = false;
	iVar5 = 0;
	do {
		iVar4 = 0;
		local_48[5] = iVar5 + 1;
		if (0 < num_players) {
			pBuff = &MPBuff;
			local_30 = 0xe08bc;
			do {
				if (bVar1) {
					puVar3 = &DAT_000f7200;
					pcVar2 = &DAT_00119400;
				}
				else {
					puVar3 = &DAT_000f3000;
					pcVar2 = &DAT_000fb400;
				}
				bVar1 = (bool)(bVar1 ^ 1);
				InitaliseDrawEnv(pBuff, local_48[iVar4], local_48[iVar4 + 2], 0x140, local_48[4]);
				(&MPBuff)[iVar4 * 2 + iVar5].primtab = pcVar2;
				(&MPBuff)[iVar4 * 2 + iVar5].primptr = pcVar2;
				*(undefined **)(iVar5 * 0x80 + iVar4 * 0x100 + local_30) = puVar3;
				iVar4 = iVar4 + 1;
				pBuff = pBuff + 2;
			} while (iVar4 < num_players);
		}
		iVar5 = local_48[5];
	} while (local_48[5] < 2);
	aspect.m[0][0] = 0x1000;
	aspect.m[0][1] = 0;
	aspect.m[0][2] = 0;
	aspect.m[1][0] = 0;
	aspect.m[1][1] = 0x1266;
	aspect.m[1][2] = 0;
	aspect.m[2][0] = 0;
	aspect.m[2][1] = 0;
	aspect.m[2][2] = 0x1000;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitaliseDrawEnv(struct DB *pBuff /*$s0*/, int x /*$s4*/, int y /*$s3*/, int w /*$s1*/, int h /*stack 16*/)
 // line 1535, offset 0x0007f7c0
	/* begin block 1 */
		// Start line: 4857
	/* end block 1 */
	// End Line: 4858

	/* begin block 2 */
		// Start line: 5090
	/* end block 2 */
	// End Line: 5091

void InitaliseDrawEnv(DB *pBuff, int x, int y, int w, int h)
{
	UNIMPLEMENTED();
	/*
	SetDefDrawEnv(&pBuff->draw);
	SetDefDrawEnv(&pBuff[1].draw, x, y + 0x100, w, h);
	pBuff->id = 0;
	pBuff[1].id = 1;
	(pBuff->draw).dfe = 1;
	pBuff[1].draw.dfe = 1;
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ResetCityType()
 // line 1566, offset 0x0007f5b4
	/* begin block 1 */
		// Start line: 3557
	/* end block 1 */
	// End Line: 3558

	/* begin block 2 */
		// Start line: 4629
	/* end block 2 */
	// End Line: 4630

	/* begin block 3 */
		// Start line: 4630
	/* end block 3 */
	// End Line: 4631

/* WARNING: Unknown calling convention yet parameter storage is locked */

void ResetCityType(void)
{
	UNIMPLEMENTED();

	//lasttype = 0xff;
	//lastcity = 0xff;
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetCityType(enum CITYTYPE type /*$a0*/)
 // line 1577, offset 0x0007f118
	/* begin block 1 */
		// Start line: 1578
		// Start offset: 0x0007F118
		// Variables:
	// 		struct CdlFILE cdfile; // stack offset -120
	// 		struct XYPAIR *info; // $s2
	// 		char namebuffer[64]; // stack offset -96
	// 		unsigned char result[8]; // stack offset -32
	// 		int i; // $a2
	// 		int sector; // $s0
	/* end block 1 */
	// End offset: 0x0007F338
	// End Line: 1655

	/* begin block 2 */
		// Start line: 3260
	/* end block 2 */
	// End Line: 3261

	/* begin block 3 */
		// Start line: 3315
	/* end block 3 */
	// End Line: 3316

	/* begin block 4 */
		// Start line: 3317
	/* end block 4 */
	// End Line: 3318

void SetCityType(CITYTYPE type)
{
	UNIMPLEMENTED();

	/*
	int *piVar1;
	CdlFILE *pCVar2;
	int levOfs;
	int iVar3;
	XYPAIR *cdp;
	char *__format;
	int *piVar4;
	CdlFILE fp;
	char filename[64];
	uchar result[8];

	piVar4 = &DAT_000f3008;
	if ((type == lasttype) && (GameLevel == (uint)lastcity)) {
		return;
	}
	lastcity = (byte)GameLevel;
	lasttype = type;
	if (type == CITYTYPE_NIGHT) {
		__format = s__DRIVER2_N_s_1_00011de4;
	}
	else {
		if (type < CITYTYPE_MULTI_DAY) {
			if (type != CITYTYPE_DAY) goto LAB_0007f244;
			__format = s__DRIVER2__s_1_00011dd4;
		}
		else {
			if (type != CITYTYPE_MULTI_DAY) {
				if (type == CITYTYPE_MULTI_NIGHT) {
					sprintf(filename, s__DRIVER2_MN_s_1_00011e04, LevelFiles4[GameLevel]);
				}
				goto LAB_0007f244;
			}
			__format = s__DRIVER2_M_s_1_00011df4;
		}
	}
	sprintf(filename, __format, LevelFiles4[GameLevel]);
LAB_0007f244:
	pCVar2 = CdSearchFile(&fp, filename);
	while (pCVar2 == (CdlFILE *)0x0) {
		DoCDRetry();
		pCVar2 = CdSearchFile(&fp, filename);
	}
	levOfs = CdPosToInt((CdlLOC *)&fp);
	citystart[GameLevel] = levOfs;
	do {
		do {
			iVar3 = CdDiskReady(0);
			if (iVar3 != 2) {
				DoCDRetry();
			}
			iVar3 = CdControlB(2, &fp, 0);
		} while ((iVar3 == 0) || (iVar3 = CdRead(1, &DAT_000f3000, 0x80), iVar3 == 0));
		iVar3 = CdReadSync(0, result);
	} while (iVar3 != 0);
	iVar3 = 3;
	cdp = citylumps + GameLevel * 4;
	do {
		iVar3 = iVar3 + -1;
		cdp->x = *piVar4 + levOfs * 0x800;
		piVar1 = piVar4 + 1;
		piVar4 = piVar4 + 2;
		cdp->y = *piVar1;
		cdp = cdp + 1;
	} while (-1 < iVar3);
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ FileExists(char *filename /*$a2*/)
 // line 1682, offset 0x0007f5c8
	/* begin block 1 */
		// Start line: 1683
		// Start offset: 0x0007F5C8
		// Variables:
	// 		struct CdlFILE cdfile; // stack offset -176
	// 		char namebuffer[128]; // stack offset -152
	// 		unsigned char result[8]; // stack offset -24
	// 		int retries; // $s1
	/* end block 1 */
	// End offset: 0x0007F640
	// End Line: 1708

	/* begin block 2 */
		// Start line: 4861
	/* end block 2 */
	// End Line: 4862

int FileExists(char *filename)
{
	CdlFILE *pCVar1;
	int iVar2;
	CdlFILE CStack176;
	char acStack152[136];

	sprintf(acStack152, "\\DRIVER2\\%s;1", filename);
	iVar2 = 9;
	do {
		pCVar1 = CdSearchFile(&CStack176, acStack152);
		if (pCVar1 != (CdlFILE *)0x0) {
			return 1;
		}
		iVar2 = iVar2 + -1;
		DoCDRetry();
	} while (iVar2 != -1);
	return 0;
}



// decompiled code
// original method signature: 
// enum CDTYPE /*$ra*/ DiscSwapped(char *filename /*$s1*/)
 // line 1723, offset 0x0007f640
	/* begin block 1 */
		// Start line: 1724
		// Start offset: 0x0007F640
		// Variables:
	// 		struct CdlFILE cdfile; // stack offset -40
	// 		int ret; // $v1
	/* end block 1 */
	// End offset: 0x0007F6FC
	// End Line: 1762

	/* begin block 2 */
		// Start line: 4934
	/* end block 2 */
	// End Line: 4935

	/* begin block 3 */
		// Start line: 4950
	/* end block 3 */
	// End Line: 4951

int handle = 0;

CDTYPE DiscSwapped(char *filename)
{
	UNIMPLEMENTED();
	return CDTYPE_CORRECTDISC;

	/*
	CDTYPE CVar1;
	int iVar2;
	CdlFILE CStack40;

	iVar2 = CdDiskReady(1);
	if (iVar2 == 2) {
		iVar2 = CdGetDiskType();
		if (iVar2 != 1) {
			if (iVar2 < 2) {
				if (iVar2 != 0) {
					return CDTYPE_DISCERROR;
				}
				return CDTYPE_NODISC;
			}
			if (iVar2 != 2) goto LAB_0007f66c;
			handle = (int)CdSearchFile(&CStack40, filename);
			if ((CdlFILE *)handle != (CdlFILE *)0x0) {
				return CDTYPE_CORRECTDISC;
			}
		}
		CVar1 = CDTYPE_WRONGDISC;
	}
	else {
	LAB_0007f66c:
		CVar1 = CDTYPE_DISCERROR;
		if (iVar2 == 0x10) {
			CVar1 = CDTYPE_SHELLOPEN;
		}
	}
	return CVar1;*/
}





