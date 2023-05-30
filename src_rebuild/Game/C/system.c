#include "driver2.h"

#ifndef PSX
#include <stdint.h>
#include <SDL.h>
#endif // !PSX
#include "system.h"

#include "platform.h"
#include "xaplay.h"
#include "loadview.h"
#include "mission.h"
#include "glaunch.h"
#include "main.h"
#include "pad.h"
#include "draw.h"
#include "pause.h"

char gDataFolder[32] = "DRIVER2\\";

#ifdef PSX

/* those should be passed to linker script

------------------------------------------------------------------------------------
NAME					| OFFSET   | SIZE	 | DESCRIPTION
------------------------|----------|---------|--------------------------------------
_path_org				| 0xE7000  | 0xB7C8	 |
_otag1_org				| 0xF3000  | 0x4200	 |
_otag2_org				| 0xF7200  | 0x4200	 |
_primTab1_org			| 0xFB400  | 1E000	 |
_primTab2_org			| 0x119400 | 1E000	 |
_mallocTab_org			| 0x137400 | 0xD47BC |(this is bigger, real is 0xC37BC)
_frnt_org				| 0x1C0000 | no size | inside mallocTab
_sbnk_org				| 0x180000 | no size | inside mallocTab
_repl_org				| 0x1FABBC | 0x3444  | probably inside mallocTab

*/


#else

// Initialized in redriver2_main
volatile char* _frontend_buffer = NULL;		// 0xFB400
volatile char* _other_buffer = NULL;		// 0xF3000
volatile char* _other_buffer2 = NULL;		// 0xE7000
volatile OTTYPE* _OT1 = NULL;				// 0xF3000
volatile OTTYPE* _OT2 = NULL;				// 0xF7200
volatile char* _primTab1 = NULL;			// 0xFB400
volatile char* _primTab2 = NULL;			// 0x119400
volatile char* _sbank_buffer = NULL;		// 0x180000
volatile char* _overlay_buffer = NULL;		// 0x1C0000
volatile char* _replay_buffer = NULL;		// 0x1FABBC

#endif



#if defined(USE_CRT_MALLOC)

volatile char* mallocptr = NULL;
volatile char* malloctab = NULL;

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
#elif !defined(PSX)

char g_allocatedMem[0x200000];			// 0x137400 (_ramsize). TODO: use real malloc  size: 870332
volatile char* mallocptr = g_allocatedMem;
volatile char* malloctab = g_allocatedMem;

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
int gContentOverride = 1;		// use unpacked filesystem?
char g_CurrentLevelFileName[64];
char* g_CurrentLevelSpoolData = NULL;
#endif // !PSX

// TODO: to game vars

// [D] [T]
void ClearMem(char* mem, int size)
{
	// 16 bit aligned clear
#ifndef PSX
	memset(mem, 0, size);
#else
	char* end;
	end = mem + size;

	while ((((u_int)mem & 3) != 0 && (mem < end))) {
		*mem = 0;
		mem = (char*)((int)mem + 1);
	}

	while (mem <= end + -0x10) {
		*(u_int*)mem = 0;
		((u_int*)mem)[1] = 0;
		((u_int*)mem)[2] = 0;
		((u_int*)mem)[3] = 0;
		mem = (char*)((u_int*)mem + 4);
	}

	while (mem <= end + -4) {
		*(u_int*)mem = 0;
		mem = (char*)((u_int*)mem + 1);
	}

	while (mem < end) {
		*mem = 0;
		mem = (char*)((int)mem + 1);
	}
#endif // !PSX
}

// [D] [T]
void setMem8(unsigned char* mem, unsigned char val, int size)
{
	while (--size > 0)
		*mem++ = val;

	// TODO: check alignment/bounds?
}

// [D] [T]
void setMem16(ushort* mem, ushort val, int size)
{
	while (--size > 0)
		*mem++ = val;

	// TODO: check alignment/bounds?
}

// [T]
void Init_FileSystem(void)
{
	CdInit();
	VSync(3);

	// Driver 1 were looking up level files on CD...
}

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

// loads whole file into buffer
// [D] [T]
int Loadfile(char* name, char* addr)
{
	int nread;
	unsigned char res[8];
	char namebuffer[64];

#if USE_PC_FILESYSTEM
	int fileSize;

	sprintf(namebuffer, "%s%s", gDataFolder, name);
	FS_FixPathSlashes(namebuffer);

	FILE* fptr = fopen(namebuffer, "rb");
	if (fptr)
	{
		fseek(fptr, 0, SEEK_END);
		fileSize = ftell(fptr);

		fseek(fptr, 0, SEEK_SET);
		int numRead = fread(addr, 1, fileSize, fptr);

		fclose(fptr);

		//SDL_Delay(200); // [A] PSX-like CD delay

		return numRead;
	}
#endif

#if USE_CD_FILESYSTEM
	return LoadfileSeg(name, addr, 0, -1);
#endif
}

// [D] [T]
int FileExists(char* filename)
{
	char namebuffer[128];
	
	if (*filename == '\0')
		return 0;

#if USE_PC_FILESYSTEM
	sprintf(namebuffer, "%s%s", gDataFolder, filename);
	FS_FixPathSlashes(namebuffer);

	FILE* fp = fopen(namebuffer, "rb");
	if (fp)
	{
		fclose(fp);
		return 1;
	}
#endif // USE_PC_FILESYSTEM

#if USE_CD_FILESYSTEM
	int retries;
	CdlFILE cdfile;

	sprintf(namebuffer, "\\%s%s;1", gDataFolder, filename);

#ifdef PSX
	retries = 9;
	do {

		if (CdSearchFile(&cdfile, namebuffer) != NULL)
			return 1;

		retries--;
		DoCDRetry();
	} while (retries >= 0);

#else
	// don't retry or we'll have problems
	if(CdSearchFile(&cdfile, namebuffer) != NULL)
		return 1;
#endif
	
#endif // USE_CD_FILESYSTEM

	return 0;
}

// loads file partially into buffer
// [D] [T]
int LoadfileSeg(char* name, char* addr, int offset, int loadsize)
{
	char namebuffer[64];

#if USE_PC_FILESYSTEM
	int fileSize;

	sprintf(namebuffer, "%s%s", gDataFolder, name);
	FS_FixPathSlashes(namebuffer);

	FILE* fptr = fopen(namebuffer, "rb");
	if (fptr)
	{
		fseek(fptr, 0, SEEK_END);
		fileSize = ftell(fptr);

		if (loadsize == -1 || loadsize > fileSize)
			loadsize = fileSize;

		fseek(fptr, offset, SEEK_SET);
		int numRead = fread(addr, 1, loadsize, fptr);

		fclose(fptr);

		//SDL_Delay(200); // [A] PSX-like CD delay

		return numRead;
	}
#endif // USE_PC_FILESYSTEM

#if USE_CD_FILESYSTEM
	char* readPtr;
	char* sectorPtr;
	int remainingBytes;
	int remainingOffset;
	int sector;
	u_char result[8];
	char sectorbuffer[CDSECTOR_SIZE];
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

	if (loadsize == -1)
		loadsize = currentfileinfo.size - offset;

	remainingOffset = offset & 0x7ff;
	remainingBytes = loadsize;

	// seek to the sector
	sector = offset / CDSECTOR_SIZE + CdPosToInt(&currentfileinfo.pos);
		
	// start reading sectors from CD
	while(remainingBytes > 0)
	{
		// start reading if we getting to desired offset
		CdIntToPos(sector, &pos);

		// if we don't have offset or we have more than 2048 bytes
		//   - we can read into buffer directly (which is faster)
		if (remainingBytes >= CDSECTOR_SIZE && remainingOffset == 0)
			sectorPtr = addr;
		else
			sectorPtr = sectorbuffer;

		// read sector
		do
		{
			if (CdDiskReady(0) != CdlComplete)
				DoCDRetry();

		} while (CdControlB(CdlSetloc, (u_char*)&pos, NULL) == 0 ||
			CdRead(1, (u_long*)sectorPtr, CdlModeSpeed) == 0 ||
			CdReadSync(0, result) != 0);

		// non-direct reads must be handled
		if(sectorPtr == sectorbuffer)
		{
			// fetch
			readPtr = sectorbuffer + remainingOffset;

			// copy bytes
			while (remainingBytes > 0 &&
				readPtr - sectorbuffer < CDSECTOR_SIZE)	// don't leave boundary
			{
				*addr++ = *readPtr++;
				remainingBytes--;
			}

			remainingOffset = 0;
		}
		else
		{
			addr += CDSECTOR_SIZE;
			remainingBytes -= CDSECTOR_SIZE;
		}

		// go to next sector
		sector++;
	}
	
	return loadsize;
#elif USE_PC_FILESYSTEM && !defined(__EMSCRIPTEN__)
	char errPrint[1024];
	sprintf(errPrint, "Cannot open '%s'\n", namebuffer);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
	return 0;
#endif
}


// [D] [T]
void ReportMode(int on)
{
	static u_char param[8];

	if (XAPrepared() == 0)
	{
		if (on)
			param[0] = CdlModeSpeed | CdlModeRept;
		else
			param[0] = CdlModeSpeed;

		CdControlB(CdlSetmode, param, 0);
	}
}

static volatile u_char endread = 0;
static volatile u_char load_complete = 0;

// [D] [T]
void data_ready(void)
{
	if (endread)
	{
		CdDataCallback(NULL);
		load_complete = 1;
	}
}

static int current_sector = 0; // offset 0xAB27C
static char* current_address = NULL; // offset 0xAB288
static int sectors_left = 0; // offset 0xAB280

// [D] [T]
void sector_ready(u_char intr, u_char* result)
{
	CdlLOC p;

	if (intr == 1)
	{
		// read sector data
		CdGetSector(current_address, SECTOR_SIZE);

		current_address += CDSECTOR_SIZE;
		current_sector++;
		sectors_left--;

		if (sectors_left == 0)
		{
			endread = 1;
			
			CdReadyCallback(NULL);
			CdControlF(CdlPause, 0);
		}
	}
	else
	{
		if (*result & CdlStatShellOpen)
		{
			CdReadyCallback(NULL);
			
			do {
			} while (CdDiskReady(1) != CdlComplete);

			CdReadyCallback(sector_ready);
		}

		CdIntToPos(current_sector, &p);
		CdControlF(CdlReadS, (u_char*)&p);
	}
}

#if USE_PC_FILESYSTEM

// It has to be this way
int loadsectorsPC(char* addr, int sector, int nsectors)
{
	char namebuffer[64];

	if (g_CurrentLevelFileName[0] == 0)
		return 0;

	strcpy(namebuffer, g_CurrentLevelFileName);
	FS_FixPathSlashes(namebuffer);

	FILE* fp = fopen(namebuffer, "rb");

	if (fp)
	{
		// constrain nsectors to the maximum that can be read from the file
		int maxSectors;
		fseek(fp, 0, SEEK_END);
		maxSectors = (ftell(fp) - (sector * CDSECTOR_SIZE)) / CDSECTOR_SIZE;
		nsectors = MIN(nsectors, maxSectors);

		fseek(fp, sector * CDSECTOR_SIZE, SEEK_SET);
		fread(addr, CDSECTOR_SIZE, nsectors, fp);

		fclose(fp);

		ShowLoading();
		return 1;
	}

#if USE_PC_FILESYSTEM && !defined(__EMSCRIPTEN__)
	char errPrint[512];
	sprintf(errPrint, "loadsectorsPC: failed to open '%s'\n", namebuffer);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
#endif // USE_PC_FILESYSTEM && !PSX
	return 0;
}

#endif // USE_PC_FILESYSTEM

// [D] [T]
void loadsectors(char* addr, int sector, int nsectors)
{
	CdlLOC pos;

	// [A]
	if (nsectors == 0)
		return;

#if USE_PC_FILESYSTEM
	if (loadsectorsPC(addr, sector, nsectors))
		return;
#endif

	load_complete = 0;
	endread = 0;

	current_sector = sector;
	sectors_left = nsectors;
	current_address = addr;

	CdDataCallback(data_ready);
	CdReadyCallback(sector_ready);

	// start asynchronous reading...
	CdIntToPos(sector, &pos);
	CdControlF(CdlReadS, (u_char*)&pos);

	// ... but wait synchronously
	do {
#ifdef __EMSCRIPTEN__
		emscripten_sleep(0);
#endif // __EMSCRIPTEN__
	} while (load_complete == 0);

	ShowLoading();
}

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

// [D] [T]
void DisableDisplay(void)
{
	SetDispMask(0);
}

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
	DrawOTag((u_long*)(current->ot + OTSIZE-1));

	if ((FrameCnt & 1) != 0)
	{
		current = &MPBuff[0][0];
		last = &MPBuff[0][1];
	}
	else
	{
		current = &MPBuff[0][1];
		last = &MPBuff[0][0];
	}

	ClearCurrentDrawBuffers();
}

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
	DrawOTag((u_long*)(current->ot + OTSIZE - 1));

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
	SwitchMappings(pauseflag || CurrentGameMode == GAMEMODE_DIRECTOR);	// FIXME: maybe gDrawPauseMenus instead of pauseflag?
#endif
}

// [D] [T]
void SetupDrawBuffers(void)
{
	int i;
	RECT16 rect;

	// PAL: 256
	// NTSC: 240

	SetDefDispEnv(&MPBuff[0][0].disp, 0, 256, 320, SCREEN_H);
	SetDefDispEnv(&MPBuff[0][1].disp, 0, 0, 320, SCREEN_H);

	MPBuff[0][0].disp.screen.h = SCREEN_H;
	MPBuff[0][1].disp.screen.h = SCREEN_H;
	MPBuff[0][0].disp.screen.x = draw_mode.framex;
	MPBuff[0][1].disp.screen.x = draw_mode.framex;

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

// [D] [T]
void SetupDrawBufferData(int num_players)
{
	int i, j;
	int x[2], y[2];
	int height;
	int toggle;

	if (num_players == 1)
	{
		height = SCREEN_H; // 240 on NTSC
		x[0] = 0;
		y[0] = 0;
		x[1] = 0;
		y[1] = 0;
	}
	else if (num_players == 2)
	{
		height = (SCREEN_H / 2 - 1); // 127; // 119 on NTSC
		x[0] = 0;
		y[0] = 0;
		x[1] = 0;
		y[1] = SCREEN_H / 2;	  // 120 on NTSC
	}
	else
	{
		D_CHECK_ERROR(true, "Erm... too many players selected. FATAL!");
	}

	SetGeomOffset(320 / 2, height / 2);

	toggle = 0;

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < num_players; j++)
		{
			u_long* otpt;
			u_char* primpt;

			if (toggle)
			{
				otpt = (u_long*)_OT2;
				primpt = (u_char*)_primTab2; // _primTab1 + PRIMTAB_SIZE
			}
			else
			{
				otpt = (u_long*)_OT1;
				primpt = (u_char*)_primTab1;
			}

			toggle ^= 1;
			InitaliseDrawEnv(MPBuff[j], x[j], y[j], 320, height);
	
			MPBuff[i][j].primtab = (char*)primpt;
			MPBuff[i][j].primptr = (char*)primpt;
			MPBuff[i][j].ot = (OTTYPE*)otpt;
		}
	}

#ifdef PAL_VERSION
	InitMatrix(aspect);
	aspect.m[1][1] = 4300;
#else
	InitMatrix(aspect);
	aspect.m[1][1] = 4096;
#endif
}

// [D] [T]
void InitaliseDrawEnv(DB* pBuff, int x, int y, int w, int h)
{
#ifdef PSX
#define DB1 pBuff[0]
#define DB2 pBuff[1]
#else
// on PsyX we have to prevent flicker
#define DB1 pBuff[1]
#define DB2 pBuff[0]
#endif

	SetDefDrawEnv(&DB1.draw, x, y, w, h);
	SetDefDrawEnv(&DB2.draw, x, y + 256, w, h);

	pBuff[0].id = 0;
	pBuff[0].draw.dfe = 1;

	pBuff[1].id = 1;
	pBuff[1].draw.dfe = 1;

#if USE_PGXP
	if(NumPlayers == 2)
	{
		pBuff[0].draw.clip.x -= 256;
		pBuff[0].draw.clip.w += 512;

		pBuff[1].draw.clip.x -= 256;
		pBuff[1].draw.clip.w += 512;
	}
#endif
}

// [D] [T]
void ResetCityType(void)
{
	lasttype = (CITYTYPE)-1;
	lastcity = -1;

#ifndef PSX
	free(g_CurrentLevelSpoolData);
	g_CurrentLevelSpoolData = NULL;
#endif // PSX
}

// [A]
CITYTYPE GetCityType()
{
	return lasttype;
}

// [D] [T]
void SetCityType(CITYTYPE type)
{
	char* format;
	char filename[64];
	unsigned char result[8];

	if (type == lasttype && GameLevel == lastcity)
		return;

	ResetCityType();

	lastcity = GameLevel;
	lasttype = type;

#if USE_PC_FILESYSTEM
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
	FS_FixPathSlashes(filename);

	FILE* levFp = fopen(filename, "rb");

	if (levFp)
	{
		// store level name as it's required by loadsectorsPC
		strcpy(g_CurrentLevelFileName, filename);

		// spool position is forced to 0
		citystart[GameLevel] = 0;

		// skip LUMP type (37) and size, it's already hardcoded
		fseek(levFp, 8, SEEK_CUR);
		fread(citylumps[GameLevel], 1, sizeof(citylumps[GameLevel]), levFp);

		fclose(levFp);

		return;
	}
#endif // USE_PC_FILESYSTEM

#if USE_CD_FILESYSTEM
	CdlFILE cdfile;
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
#if USE_PC_FILESYSTEM
#ifndef __EMSCRIPTEN__
		char errPrint[512];
		sprintf(errPrint, "SetCityType: failed to open '%s'\n", filename);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
		exit(0);
#endif // !__EMSCRIPTEN__
#else
		DoCDRetry();
#endif // USE_PC_FILESYSTEM
	}

	sector = CdPosToInt((CdlLOC*)&cdfile);
	citystart[GameLevel] = sector;

	do {
		do {

			if (CdDiskReady(0) != CdlComplete)
				DoCDRetry();

		} while (CdControlB(CdlSetloc, (u_char*)&cdfile, 0) == 0 ||
				 CdRead(1, (u_long*)_OT1, CdlModeSpeed) == 0);

	} while (CdReadSync(0, result) != 0);

	data = (int*)_OT1 + 2;
	
	for (i = 0; i < 4; i++)
	{
		citylumps[GameLevel][i].x = data[0] + sector * CDSECTOR_SIZE;
		citylumps[GameLevel][i].y = data[1];

		data += 2;
	}
#elif USE_PC_FILESYSTEM && !defined(__EMSCRIPTEN__)
	char errPrint[1024];
	sprintf(errPrint, "SetCityType: cannot open level '%s'\n", filename);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
#endif // PSX
}

// [D] [T]
CDTYPE DiscSwapped(char* filename)
{
#if 1//ndef PSX
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
