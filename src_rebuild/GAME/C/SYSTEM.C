#include "DRIVER2.H"

#ifndef PSX
#include <stdint.h>
#include <SDL.h>
#endif // !PSX

#include "LIBETC.H"

#include "SYSTEM.H"
#include "PLATFORM.H"
#include "XAPLAY.H"
#include "LOADVIEW.H"
#include "MISSION.H"
#include "GLAUNCH.H"
#include "MAIN.H"
#include "PAD.H"
#include "DRAW.H"
#include "PAUSE.H"
#include "STRINGS.H"
#include "PLATFORM.H"

// Initialized in redriver2_main
char* _overlay_buffer = NULL;		// 0x1C0000
char* _frontend_buffer = NULL;	// 0xFB400
char* _other_buffer = NULL;		// 0xF3000
char* _other_buffer2 = NULL;		// 0xE7000
OTTYPE* _OT1 = NULL;				// 0xF3000
OTTYPE* _OT2 = NULL;				// 0xF7200
char* _primTab1 = NULL;			// 0xFB400
char* _primTab2 = NULL;			// 0x119400
char* _replay_buffer = NULL;		// 0x1FABBC
char gDataFolder[32] = "DRIVER2\\";

#ifdef USE_CRT_MALLOC

char* mallocptr = NULL;
const char* mallocptr_start = NULL;

void* g_dynamicAllocs[1024] = { 0 };
int g_numDynamicAllocs = 0;

char* sys_malloc(int size, char* funcname, int line)
{
	if (g_numDynamicAllocs & 0x10000)
		sys_tempfree();

#ifdef _DEBUG
	printWarning("CRT malloc(%d) in %s, line %d\n", size, funcname, __LINE__);
#endif // _DEBUG

	void* ptr = malloc(size);
	g_dynamicAllocs[g_numDynamicAllocs++] = ptr;

	return (char*)ptr;
}

void sys_freeall()
{
	int numAlloc = g_numDynamicAllocs & 0xfff;

	for (int i = 0; i < numAlloc; i++)
	{
		free(g_dynamicAllocs[i]);
		g_dynamicAllocs[i] = NULL;
	}

	g_numDynamicAllocs = 0;
}

char* sys_tempalloc(int size)
{
	if (g_numDynamicAllocs & 0x10000)
	{
		printError("sys_tempalloc: another alloc in use!\n");
		trap(1000);
		return NULL;
	}

	char* tmp_ptr = (char*)malloc(size);

	g_dynamicAllocs[g_numDynamicAllocs] = tmp_ptr;
	g_numDynamicAllocs |= 0x10000;

	return tmp_ptr;
}

void sys_tempfree()
{
	g_numDynamicAllocs &= ~0x10000;
	free(g_dynamicAllocs[g_numDynamicAllocs]);
	g_dynamicAllocs[g_numDynamicAllocs] = NULL;
}
#else

char g_allocatedMem[0x200000];			// 0x137400 (_ramsize). TODO: use real malloc
char* mallocptr = g_allocatedMem;
const char* mallocptr_start = g_allocatedMem;

#endif

int leadAIRequired = 0;
int leadAILoaded = 0;
int pathAILoaded = 0;

char* LevelNames[] = {
	"CHICAGO",
	"HAVANA",
	"VEGAS",
	"RIO",
};

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

static CITYTYPE lasttype = (CITYTYPE)-1;
static int lastcity = -1;

int citystart[8];
XYPAIR citylumps[8][4];

#ifndef PSX
char g_CurrentLevelFileName[64];
#endif // !PSX

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

// [D] [T]
void ClearMem(char* mem, int size)
{
	// 16 bit aligned clear
#ifndef PSX
	memset(mem, 0, size);
#else
	char* end;
	end = mem + size;

	while ((((uint)mem & 3) != 0 && (mem < end))) {
		*mem = 0;
		mem = (char*)((int)mem + 1);
	}

	while (mem <= end + -0x10) {
		*(uint*)mem = 0;
		((uint*)mem)[1] = 0;
		((uint*)mem)[2] = 0;
		((uint*)mem)[3] = 0;
		mem = (char*)((uint*)mem + 4);
	}

	while (mem <= end + -4) {
		*(uint*)mem = 0;
		mem = (char*)((uint*)mem + 1);
	}

	while (mem < end) {
		*mem = 0;
		mem = (char*)((int)mem + 1);
	}
#endif // !PSX
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

// [D] [T]
void setMem8(unsigned char* mem, unsigned char val, int size)
{
	while (--size > 0)
		*mem++ = val;

	// TODO: check alignment/bounds?
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

// [D] [T]
void setMem16(ushort* mem, ushort val, int size)
{
	while (--size > 0)
		*mem++ = val;

	// TODO: check alignment/bounds?
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

// [T]
void Init_FileSystem(void)
{
	CdInit();
	VSync(3);

	// Driver 1 were looking up level files on CD...
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

// [D] [T]
void DoCDRetry(void)
{
	if (gNumCDRetries++ > 9)
	{
		CdInit();
		VSync(3);

		gNumCDRetries = 0;
	}
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
// [D] [T]
int Loadfile(char* name, char* addr)
{
	char namebuffer[64];
#ifndef PSX
	int fileSize;

	sprintf(namebuffer, "%s%s", gDataFolder, name);
	FixPathSlashes(namebuffer);

	FILE* fptr = fopen(namebuffer, "rb");
	if (!fptr)
	{
		char errPrint[1024];
		sprintf(errPrint, "Cannot open '%s'\n", namebuffer);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
		return 0;
	}

	fseek(fptr, 0, SEEK_END);
	fileSize = ftell(fptr);

	fseek(fptr, 0, SEEK_SET);
	int numRead = fread(addr, 1, fileSize, fptr);

	fclose(fptr);

	//SDL_Delay(200); // [A] PSX-like CD delay

	return numRead;
#else // PSX
	int nread;
	unsigned char res[8];

	sprintf(namebuffer, "\\%s%s;1", gDataFolder, name);

	do {
		nread = CdReadFile(namebuffer, (u_long*)addr, 0);

		if (nread != 0)
		{
			if (CdReadSync(0, res) == 0)
				return nread;
		}

		if (CdDiskReady(0) != 2)
			DoCDRetry();

	} while (true);

	return 0;
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
	// 		CdlFILE info; // stack offset -72
	// 		CdlLOC pos; // stack offset -48
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
// [D] [T]
int LoadfileSeg(char* name, char* addr, int offset, int loadsize)
{
	char namebuffer[64];
#ifndef PSX
	int fileSize;

	sprintf(namebuffer, "%s%s", gDataFolder, name);
	FixPathSlashes(namebuffer);

	FILE* fptr = fopen(namebuffer, "rb");
	if (!fptr)
	{
		char errPrint[1024];
		sprintf(errPrint, "Cannot open '%s'\n", namebuffer);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
		return 0;
	}

	fseek(fptr, 0, SEEK_END);
	fileSize = ftell(fptr);

	if (loadsize > fileSize)
		loadsize = fileSize;

	fseek(fptr, offset, SEEK_SET);
	int numRead = fread(addr, 1, loadsize, fptr);

	fclose(fptr);

	//SDL_Delay(200); // [A] PSX-like CD delay

	return numRead;
#else // PSX

	char* pcVar2;
	int first;
	int i;
	int sector;
	int toload;
	int nsectors;
	char namebuffer[64];
	u_char result[8];
	char sectorbuffer[2048];
	CdlLOC pos;

	sprintf(namebuffer, "\\%s%s;1", gDataFolder, name);

	if (strcmp(currentfilename, namebuffer) != 0)
	{
		strcpy(currentfilename, namebuffer);

		while (CdSearchFile(&currentfileinfo, namebuffer) == NULL)
		{
			DoCDRetry();
		}
	}

	sector = offset / 2048 + CdPosToInt((CdlLOC*)&currentfileinfo);
	nsectors = offset & 0x7ff;
	toload = loadsize;

	if (nsectors != 0)
	{
		CdIntToPos(sector, &pos);
		do
		{
			if (CdDiskReady(0) != 2)
				DoCDRetry();
		} while (CdControlB(CdlSetloc, (u_char*)&pos, 0) == 0 ||
			CdRead(1, (u_long*)sectorbuffer, CdlModeSpeed) == 0 ||
			CdReadSync(0, result) != 0);

		if (loadsize <= 2048 - nsectors)
		{
			while (nsectors < nsectors + loadsize)
			{
				*addr++ = sectorbuffer[nsectors++];
			}

			return loadsize;
		}

		toload = loadsize - (2048 - nsectors);
		sector++;

		while (nsectors < 2048)
		{
			*addr++ = sectorbuffer[nsectors++];
		}
	}

	first = toload / 2048;

	if (first != 0)
	{
		CdIntToPos(sector, &pos);
		sector = sector + first;

		do
		{
			if (CdDiskReady(0) != 2)
				DoCDRetry();
		} while (CdControlB(CdlSetloc, (u_char*)&pos, 0) == 0 ||
			CdRead(first, (u_long*)addr, CdlModeSpeed) == 0 ||
			CdReadSync(0, result) != 0);

		addr += first * 2048;
		toload -= first * 2048;
	}

	if (toload > 0)
	{
		CdIntToPos(sector, &pos);

		do
		{
			if (CdDiskReady(0) != 2)
				DoCDRetry();
		} while (CdControlB(2, (u_char*)&pos, 0) == 0 ||
			CdRead(1, (u_long*)sectorbuffer, 0x80) == 0 ||
			CdReadSync(0, result) != 0);
		i = 0;

		while (i < toload)
		{
			*addr++ = sectorbuffer[i++];

		}
	}
	return loadsize;
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

// [D] [T]
void ReportMode(int on)
{
	static unsigned char param[8];

	if (XAPrepared() == 0)
	{
		if (on != 0)
			param[0] = CdlModeSpeed | CdlModeRept;
		else
			param[0] = CdlModeSpeed;

		CdControlB(CdlSetmode, param, 0);
	}
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

// [D] [T]
void data_ready(void)
{
	if (endread != 0)
	{
		CdDataCallback(0);
		load_complete = 1;
	}
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
		// 		CdlLOC p; // stack offset -16
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
static char* current_address = NULL; // offset 0xAB288
static int sectors_left = 0; // offset 0xAB280
static int sectors_read = 0; // offset 0xAB284
static int sectors_this_chunk = 0; // offset 0xAB174
static int sectors_to_read = 0; // offset 0xAB170

// [D] [T]
void sector_ready(unsigned char intr, unsigned char* result)
{
	CdlLOC p;

	if (intr == 1)
	{
		CdGetSector(current_address, 512); // and then it's multiplied by 4

		current_address = current_address + 2048;
		current_sector = current_sector + 1;
		sectors_left = sectors_left + -1;

		if (sectors_left == 0)
		{
			endread = 1;
			CdReadyCallback(0);
			CdControlF(CdlPause, 0);
		}
	}
	else
	{
		if ((*result & CdlStatShellOpen) != 0)
		{
			CdReadyCallback(0);

			do {
			} while (CdDiskReady(1) != 2);

			CdReadyCallback(sector_ready);
		}

		CdIntToPos(current_sector, &p);
		CdControlF(CdlReadS, (unsigned char*)&p);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ loadsectors(char *addr /*$a0*/, int sector /*$v0*/, int nsectors /*$a2*/)
 // line 1017, offset 0x0007f904
	/* begin block 1 */
		// Start line: 1018
		// Start offset: 0x0007F904
		// Variables:
	// 		CdlLOC pos; // stack offset -16
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
#ifdef PSX
// [D] [T]
void loadsectors(char* addr, int sector, int nsectors)
{
	CdlLOC pos;

	load_complete = 0;
	endread = 0;

	current_sector = sector;
	sectors_left = nsectors;
	current_address = addr;

	CdIntToPos(sector, &pos);
	CdControlF(CdlReadS, (unsigned char*)&pos);
	CdDataCallback(data_ready);
	CdReadyCallback(sector_ready);

	do {
	} while (load_complete == 0);

	ShowLoading();
}
#else
// It has to be this way
void loadsectorsPC(char* filename, char* addr, int sector, int nsectors)
{
	char namebuffer[64];
	strcpy(namebuffer, filename);
	FixPathSlashes(namebuffer);


	FILE* fp = fopen(namebuffer, "rb");

	if (!fp)
	{
		char errPrint[512];
		sprintf(errPrint, "loadsectorsPC: failed to open '%s'\n", namebuffer);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
		return;
	}

	fseek(fp, sector * CDSECTOR_SIZE, SEEK_SET);
	fread(addr, CDSECTOR_SIZE, nsectors, fp);

	fclose(fp);

	ShowLoading();
}
#endif // PSX



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

// [D] [T]
void EnableDisplay(void)
{
	int i;

	for (i = 0; i < NumPlayers; i++)		// [A]
	{
		ClearOTagR((u_long*)MPBuff[i][0].ot, OTSIZE);
		ClearOTagR((u_long*)MPBuff[i][1].ot, OTSIZE);
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

// [D] [T]
void DisableDisplay(void)
{
	SetDispMask(0);
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

int DoNotSwap = 0;
DB* MPlast[2];
DB* MPcurrent[2];

// [A]
void ClearCurrentDrawBuffers()
{
	ClearOTagR((u_long*)current->ot, OTSIZE);
	current->primptr = current->primtab;
}

// [D] [T]
void SwapDrawBuffers(void)
{
	DrawSync(0);

	if (DoNotSwap == 0)
	{
		PutDispEnv(&current->disp);
	}

	DoNotSwap = 0;

	PutDrawEnv(&current->draw);
	DrawOTag((u_long*)(current->ot + 0x107f));

	if ((FrameCnt & 1U) == 0)
	{
		current = &MPBuff[0][1];
		last = &MPBuff[0][0];
	}
	else
	{
		current = &MPBuff[0][0];
		last = &MPBuff[0][1];
	}

	ClearCurrentDrawBuffers();
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

// [D] [T]
void SwapDrawBuffers2(int player)
{
	int toggle;

	DrawSync(0);

	if (player == 0) 
	{
		PutDispEnv(&current->disp);
	}

	PutDrawEnv(&current->draw);
	DrawOTag((u_long*)(current->ot + 0x107f));

	if (player == 1)
	{
		toggle = FrameCnt & 1;

		// [A] i guess it should work as intended
		MPcurrent[0] = &MPBuff[0][-toggle + 1];
		MPlast[0] = &MPBuff[0][toggle];

		MPcurrent[1] = &MPBuff[1][-toggle + 1];
		MPlast[1] = &MPBuff[1][toggle];
	}

	current = MPcurrent[1 - player];
	last = MPlast[1 - player];

	ClearOTagR((u_long*)current->ot, OTSIZE);
	current->primptr = current->primtab;
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

short paddp;
short padd;

// [D] [T]
void UpdatePadData(void)
{	
	ReadControllers();

	paddp = Pads[0].mapnew;
	padd = Pads[0].mapped;

#ifndef PSX
	extern void SwitchMappings(int menu);
	SwitchMappings(pauseflag || CurrentGameMode == GAMEMODE_DIRECTOR);
#endif
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDrawBuffers()
 // line 1364, offset 0x0007eddc
	/* begin block 1 */
		// Start line: 1366
		// Start offset: 0x0007EDDC
		// Variables:
	// 		RECT rect; // stack offset -24
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

// [D] [T]
void SetupDrawBuffers(void)
{
	int i;
	RECT16 rect;

	SetDefDispEnv(&MPBuff[0][0].disp, 0, 256, 320, 256);
	SetDefDispEnv(&MPBuff[0][1].disp, 0, 0, 320, 256);

	MPBuff[0][0].disp.screen.h = 256;
	MPBuff[0][1].disp.screen.h = 256;
	MPBuff[0][0].disp.screen.x = draw_mode.framex;
	MPBuff[0][1].disp.screen.x = draw_mode.framex;
	MPBuff[0][0].disp.screen.y = draw_mode.framey;
	MPBuff[0][1].disp.screen.y = draw_mode.framey;

	if (NoPlayerControl == 0)
		SetupDrawBufferData(NumPlayers);
	else
		SetupDrawBufferData(1);

	for (i = 0; i < 2; i++)
	{
		MPlast[i] = &MPBuff[i][1];
		MPcurrent[i] = &MPBuff[i][0];
	}

	rect.w = 320;
	rect.h = 512;
	rect.x = 0;
	rect.y = 0;

	current = MPcurrent[0];
	last = MPlast[0];

	ClearImage(&rect, 0, 0, 0);
	DrawSync(0);
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

// [D] [T]
void SetupDrawBufferData(int num_players)
{
	int i;
	int j;
	int x[2];
	int y[2];
	int height;
	int toggle;

	if (num_players == 1)
	{
		height = 256;
		x[0] = 0;
		y[0] = 0;
		x[1] = 0;
		y[1] = 0;
	}
	else if (num_players == 2)
	{
		x[0] = 0;
		y[0] = 0;
		x[1] = 0;
		y[1] = 128;
		height = 127;
	}
	else
	{
		do {
			trap(0x400);
		} while (FrameCnt != 0x78654321);
	}

	SetGeomOffset(160, height / 2);

	toggle = 0;

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < num_players; j++)
		{
			u_long* otpt;
			unsigned char* primpt;
			unsigned char* PRIMpt;

			if (toggle)
			{
				otpt = (u_long*)_OT2;
				primpt = PRIMpt = (unsigned char*)_primTab2;
			}
			else
			{
				otpt = (u_long*)_OT1;
				primpt = PRIMpt = (unsigned char*)_primTab1;
			}

			toggle ^= 1;
			InitaliseDrawEnv(MPBuff[j], x[j], y[j], 320, height);
			MPBuff[j][i].primtab = (char*)primpt;
			MPBuff[j][i].primptr = (char*)PRIMpt;
			MPBuff[j][i].ot = (OTTYPE*)otpt;
		}
	};

	aspect.m[0][0] = 4096;
	aspect.m[0][1] = 0;
	aspect.m[0][2] = 0;

	aspect.m[1][0] = 0;
	aspect.m[1][1] = 4710;
	aspect.m[1][2] = 0;

	aspect.m[2][0] = 0;
	aspect.m[2][1] = 0;
	aspect.m[2][2] = 4096;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitaliseDrawEnv(DB *pBuff /*$s0*/, int x /*$s4*/, int y /*$s3*/, int w /*$s1*/, int h /*stack 16*/)
 // line 1535, offset 0x0007f7c0
	/* begin block 1 */
		// Start line: 4857
	/* end block 1 */
	// End Line: 4858

	/* begin block 2 */
		// Start line: 5090
	/* end block 2 */
	// End Line: 5091

// [D] [T]
void InitaliseDrawEnv(DB* pBuff, int x, int y, int w, int h)
{
	RECT16 clipRect;

	SetDefDrawEnv(&pBuff[0].draw, x, y + 256, w, h);
	SetDefDrawEnv(&pBuff[1].draw, x, y, w, h);

	pBuff[0].id = 0;
	pBuff[0].draw.dfe = 1;

	pBuff[1].id = 1;
	pBuff[1].draw.dfe = 1;
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

// [D] [T]
void ResetCityType(void)
{
	lasttype = (CITYTYPE)-1;
	lastcity = -1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetCityType(CITYTYPE type /*$a0*/)
 // line 1577, offset 0x0007f118
	/* begin block 1 */
		// Start line: 1578
		// Start offset: 0x0007F118
		// Variables:
	// 		CdlFILE cdfile; // stack offset -120
	// 		XYPAIR *info; // $s2
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

// [D] [T]
void SetCityType(CITYTYPE type)
{
	char* format;
	char filename[64];
	unsigned char result[8];

	if (type == lasttype && GameLevel == lastcity)
		return;

	lastcity = GameLevel;
	lasttype = type;

#ifndef PSX
	// PC code

	switch (type)
	{
		case CITYTYPE_NIGHT:
			format = "%sN%s";
			break;
		case CITYTYPE_MULTI_DAY:
			format = "%sM%s";
			break;
		case CITYTYPE_MULTI_NIGHT:
			format = "%sMN%s";
			break;
		default:
			format = "%s%s";
			break;
	}

	sprintf(filename, format, gDataFolder, LevelFiles[GameLevel]);
	FixPathSlashes(filename);

	FILE* levFp = fopen(filename, "rb");

	if (!levFp)
	{
		char errPrint[1024];
		sprintf(errPrint, "SetCityType: cannot open level '%s'\n", filename);
	
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
		return;
	}

	// store level name as it's required by loadsectorsPC
	strcpy(g_CurrentLevelFileName, filename);

	citystart[GameLevel] = 0;

	// skip LUMP type (37) and size, it's already hardcoded
	fseek(levFp, 8, SEEK_CUR);

	fread(citylumps[GameLevel], 1, sizeof(citylumps[GameLevel]), levFp);

	fclose(levFp);
#else
	CdlFILE cdfile;
	XYPAIR* info;
	int i;
	int sector;
	int* data;
	
	switch (type)
	{
		case CITYTYPE_NIGHT:
			format = "\\%sN%s;1";
			break;
		case CITYTYPE_MULTI_DAY:
			format = "\\%sM%s;1";
			break;
		case CITYTYPE_MULTI_NIGHT:
			format = "\\%sMN%s;1";
			break;
		default:
			format = "\\%s%s;1";
			break;
	}

	sprintf(filename, format, gDataFolder, LevelFiles[GameLevel]);

	while (CdSearchFile(&cdfile, filename) == NULL)
	{
		DoCDRetry();
	}

	sector = CdPosToInt((CdlLOC*)&cdfile);
	citystart[GameLevel] = sector;

	do {
		do {

			if (CdDiskReady(0) != 2)
				DoCDRetry();

		} while (CdControlB(2, (u_char*)&cdfile, 0) == 0 ||
				 CdRead(1, (u_long*)_OT1, 0x80) == 0);

	} while (CdReadSync(0, result) != 0);

	data = (int*)_OT1 + 2;
	
	for (i = 0; i < 4; i++)
	{
		citylumps[GameLevel][i].x = data[0] + sector * 2048;
		citylumps[GameLevel][i].y = data[1];

		data += 2;
	}
#endif // PSX
}



// decompiled code
// original method signature: 
// int /*$ra*/ FileExists(char *filename /*$a2*/)
 // line 1682, offset 0x0007f5c8
	/* begin block 1 */
		// Start line: 1683
		// Start offset: 0x0007F5C8
		// Variables:
	// 		CdlFILE cdfile; // stack offset -176
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

// [D] [T]
int FileExists(char* filename)
{
#ifdef PSX
	int retries;
	CdlFILE cdfile;
	char namebuffer[128];

	sprintf(namebuffer, "\\%s%s;1", gDataFolder, filename);

	retries = 9;
	do {

		if (CdSearchFile(&cdfile, namebuffer) != NULL)
			return 1;

		retries--;
		DoCDRetry();
	} while (retries >= 0);

	return 0;
#else
	char namebuffer[128];

	sprintf(namebuffer, "%s%s", gDataFolder, filename);
	FixPathSlashes(namebuffer);

	FILE* fp = fopen(namebuffer, "rb");
	if (fp)
	{
		fclose(fp);
		return 1;
	}

	return 0;
#endif // PSX
}



// decompiled code
// original method signature: 
// CDTYPE /*$ra*/ DiscSwapped(char *filename /*$s1*/)
 // line 1723, offset 0x0007f640
	/* begin block 1 */
		// Start line: 1724
		// Start offset: 0x0007F640
		// Variables:
	// 		CdlFILE cdfile; // stack offset -40
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

// [D] [T]
CDTYPE DiscSwapped(char* filename)
{
#ifndef PSX
	return CDTYPE_CORRECTDISC;
#else
	CDTYPE ret;
	CdlFILE cdfile;

	switch(CdDiskReady(1))
	{
		case CdlStatStandby:
		{
			switch(CdGetDiskType())
			{
				case CdlStatNoDisk:
					ret = CDTYPE_NODISC;
					break;
				case CdlOtherFormat:
					ret = CDTYPE_WRONGDISC;
					break;
				case CdlCdromFormat:
				{
					if (CdSearchFile(&cdfile, filename) != NULL)
						ret = CDTYPE_CORRECTDISC;
					else
						ret = CDTYPE_DISCERROR;
					
					break;
				}
			}
			break;
		}
		case CdlStatShellOpen:
			ret = CDTYPE_SHELLOPEN;
			break;
		default:
			ret = CDTYPE_DISCERROR;
	}

	return ret;
#endif
}





