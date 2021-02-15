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

#include "LIBETC.H"
#include "STRINGS.H"

#ifdef PSX

char* _overlay_buffer	= 0x801C0000;
char* _frontend_buffer	= 0x800FB400;
char* _other_buffer		= 0x800F3000;
char* _other_buffer2	= 0x800E7000;
OTTYPE* _OT1			= 0x800F3000;
OTTYPE* _OT2			= 0x800F7200;
char* _primTab1			= 0x800FB400;
char* _primTab2			= 0x80119400;
char* _replay_buffer	= 0x801FABBC;

#else

// Initialized in redriver2_main
char* _overlay_buffer = NULL;		// 0x1C0000
char* _frontend_buffer = NULL;		// 0xFB400
char* _other_buffer = NULL;			// 0xF3000
char* _other_buffer2 = NULL;		// 0xE7000
OTTYPE* _OT1 = NULL;				// 0xF3000
OTTYPE* _OT2 = NULL;				// 0xF7200
char* _primTab1 = NULL;				// 0xFB400
char* _primTab2 = NULL;				// 0x119400
char* _replay_buffer = NULL;		// 0x1FABBC

#endif

char gDataFolder[32] = "DRIVER2\\";

#ifdef USE_CRT_MALLOC

char* mallocptr = NULL;
const char* malloctab = NULL;

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
#elif defined(PSX)

char* mallocptr;
const char* malloctab = 0x800137400;

#else

char g_allocatedMem[0x200000];			// 0x137400 (_ramsize). TODO: use real malloc  size: 870332
char* mallocptr = g_allocatedMem;
const char* malloctab = g_allocatedMem;

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
	SwitchMappings(pauseflag || CurrentGameMode == GAMEMODE_DIRECTOR);
#endif
}

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

// [D] [T]
void SetupDrawBufferData(int num_players)
{
	int i;
	int j;
	int x[2];
	int y[2];
	int width, height;
	int toggle;

	if (num_players == 1)
	{
		width = 320;
		height = 256;
		x[0] = 0;
		y[0] = 0;
		x[1] = 0;
		y[1] = 0;
	}
	else if (num_players == 2)
	{
		width = 320;
		height = 127;
		x[0] = 0;
		y[0] = 0;
		x[1] = 0;
		y[1] = 128;
	}
	else
	{
		do {
			trap(0x400);
		} while (FrameCnt != 0x78654321);
	}

	SetGeomOffset(width / 2, height / 2);

	toggle = 0;

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < num_players; j++)
		{
			u_long* otpt;
			u_char* primpt;
			u_char* PRIMpt;

			if (toggle)
			{
				otpt = (u_long*)_OT2;
				primpt = PRIMpt = (u_char*)_primTab2;
			}
			else
			{
				otpt = (u_long*)_OT1;
				primpt = PRIMpt = (u_char*)_primTab1;
			}

			toggle ^= 1;
			InitaliseDrawEnv(MPBuff[j], x[j], y[j], width, height);
	
			MPBuff[j][i].primtab = (char*)primpt;
			MPBuff[j][i].primptr = (char*)PRIMpt;
			MPBuff[j][i].ot = (OTTYPE*)otpt;
		}
	}

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

// [D] [T]
void InitaliseDrawEnv(DB* pBuff, int x, int y, int w, int h)
{
	SetDefDrawEnv(&pBuff[0].draw, x, y + 256, w, h);
	SetDefDrawEnv(&pBuff[1].draw, x, y, w, h);

	pBuff[0].id = 0;
	pBuff[0].draw.dfe = 1;

	pBuff[1].id = 1;
	pBuff[1].draw.dfe = 1;

#ifdef USE_PGXP
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

// [D] [T]
int FileExists(char* filename)
{
	if(*filename == '\0')
		return 0;
	
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

#ifndef PSX
int gImitateDiscSwap = 0;
int gImitateDiscSwapFrames = 0;
#endif

// [D] [T]
CDTYPE DiscSwapped(char* filename)
{
#ifndef PSX
	// Fancy sequence in homage of PS1 version
	// any button press will skip it
	ReadControllers();

	if (Pads[0].mapnew)
		gImitateDiscSwap = -1;

	if (gImitateDiscSwap > 0)
	{
		int numFrames = 80;

		if(gImitateDiscSwap == 4)
			numFrames = 28;

		if (VSync(-1) - gImitateDiscSwapFrames > numFrames)
		{
			gImitateDiscSwap++;
			gImitateDiscSwapFrames = VSync(-1);
		}

		if(gImitateDiscSwap == 1)
			return CDTYPE_WRONGDISC;
		else if (gImitateDiscSwap == 2 || gImitateDiscSwap == 3)
			return CDTYPE_SHELLOPEN;
		else if (gImitateDiscSwap == 4)
			return CDTYPE_DISCERROR;
		else
			gImitateDiscSwap = -1;
	}

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
