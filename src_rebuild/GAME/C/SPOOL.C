#include "DRIVER2.H"

#ifndef PSX
#include <stdint.h>
#include <SDL.h>
#endif // !PSX

#include <STRINGS.H>

#include "LIBETC.H"
#include "PAD.H"
#include "SPOOL.H"
#include "MAP.H"
#include "SYSTEM.H"
#include "MAIN.H"
#include "XAPLAY.H"
#include "DIRECTOR.H"
#include "SOUND.H"
#include "TEXTURE.H"
#include "MODELS.H"
#include "OBJANIM.H"
#include "GLAUNCH.H"
#include "CARS.H"
#include "COSMETIC.H"
#include "DENTING.H"
#include "HANDLING.H"
#include "MISSION.H"
#include "CIV_AI.H"
#include "CAMERA.H"
#include "DR2ROADS.H"

int date_date = 0xA11;
int date_time = 0x27220B;

int SpecialByRegion[4][20] = {
	{5, 1, 3, 3, 2, 2, 2, 3, 3, 3, 3, 1, 1, 1, 2, 3, 2, 2, 3, 0},
	{2, 4, 1, 1, 4, 4, 3, 3, 3, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{2, 4, 1, 1, 1, 1, 1, 1, 4, 2, 3, 3, 5, 0, 0, 0, 0, 0, 0, 0},
	{2, 5, 4, 1, 2, 1, 4, 3, 2, 2, 2, 2, 3, 3, 3, 0, 0, 0, 0, 0},
};

char* model_spool_buffer = NULL;

int cell_objects_add[5];
int cell_slots_add[5];

SXYPAIR* Music_And_AmbientOffsets;

AreaDataStr* AreaData;
unsigned char* AreaTPages;	// 16 per area
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
volatile int spoolactive;	// volatile is required at least for PC
volatile int quickSpool;
int models_ready;

short specspooldata[3] = { 20, 10, 4 };

int tsetcounter;
int tsetpos;

int spoolcounter;
int spoolseek;		// Probably UNUSED

int loadbank_read;
int loadbank_write;

int spoolpos;
int spoolpos_reading;
int spoolpos_writing;

int allowSpecSpooling;
int startSpecSpool;

int unpack_roadmap_flag;
int unpack_cellptr_flag;

char *packed_cell_pointers;
SPL_REGIONINFO spool_regioninfo[8];

static int sectors_this_chunk;
static volatile int sectors_to_read;
static char *target_address;

static int nTPchunks;
static int nTPchunks_reading;
static int nTPchunks_writing;

static int ntpages;
static int current_sector;
static int switch_spooltype;

static int endchunk;
int send_bank;
int sample_chunk;
int chunk_complete;

int new_area_location;
int LoadingArea = 0;
unsigned short *newmodels = NULL;

SPOOLQ spooldata[48];

#ifdef _DEBUG
#define SPOOL_INFO printInfo
#define SPOOL_WARNING printWarning
#define SPOOL_ERROR printError
#else
#define SPOOL_INFO
#define SPOOL_WARNING
#define SPOOL_ERROR
#endif

#if !defined(PSX) && !defined(SIMPLE_SPOOL)
#include <assert.h>

typedef void(*data_callbackFn)(void);
typedef void(*ready_callbackFn)(unsigned char intr, unsigned char *result);

data_callbackFn g_dataCallbackPC = NULL;
ready_callbackFn g_readyCallbackPC = NULL;
char g_sectorData[2048] = { 0 };
bool g_isSectorDataRead = false;
bool g_spoolDoneFlag = false;

extern char g_CurrentLevelFileName[64];

SDL_Thread* levelSpoolerPCThread = NULL;
SDL_mutex* levelSpoolerPCMutex = NULL;
volatile int levelSpoolerSeekCmd = 0;

//-----------------------------------------------------
// copies read sector data to addr
//-----------------------------------------------------
void getLevSectorPC(char* dest, int count)
{
	count *= 4;

#ifdef _DEBUG
	SPOOLQ* which = &spooldata[spoolpos_reading];
	sectors_this_chunk;
	current_sector;
	sectors_to_read;
#endif // _DEBUG

	assert(count <= 2048);
	assert(dest);
	assert(sectors_to_read > 0);

	//SDL_LockMutex(levelSpoolerPCMutex);

	memcpy(dest, g_sectorData, count);
	g_isSectorDataRead = true;

	//SDL_UnlockMutex(levelSpoolerPCMutex);
}

void levelSpoolerPCDataCallback(data_callbackFn cb)
{
	SDL_LockMutex(levelSpoolerPCMutex);
	g_dataCallbackPC = cb;
	SDL_UnlockMutex(levelSpoolerPCMutex);
}

void levelSpoolerPCReadyCallback(ready_callbackFn cb)
{
	SDL_LockMutex(levelSpoolerPCMutex);
	g_readyCallbackPC = cb;
	SDL_UnlockMutex(levelSpoolerPCMutex);
}

// Main spooler thread function
int levelSpoolerPCFunc(void* data)
{
	//Print incoming data
	SPOOL_WARNING("Running SPOOL thread...\n");

	g_spoolDoneFlag = false;
	g_isSectorDataRead = false;

	ready_callbackFn readyCb = g_readyCallbackPC;
	data_callbackFn dataCb = g_dataCallbackPC;

	FILE* fp = fopen(g_CurrentLevelFileName, "rb");
	if (!fp)
	{
		char errPrint[1024];
		sprintf(errPrint, "Cannot open '%s'\n", g_CurrentLevelFileName);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);

		if (readyCb)
			readyCb(0, { 0x0 });

		return -1;
	}

	do
	{
		SDL_LockMutex(levelSpoolerPCMutex);

		if (levelSpoolerSeekCmd != 0)
		{
			int sector = levelSpoolerSeekCmd;

			if (sector == -1)
			{
				SPOOL_INFO("SPOOL thread recieved 'CdlPause'\n", sector);

				levelSpoolerSeekCmd = 0;
				g_spoolDoneFlag = true;
			}
			else
			{
				SPOOL_INFO("SPOOL thread recieved 'CdlReadS' at %d\n", sector);

				// seek
				fseek(fp, sector * 2048, SEEK_SET);
				levelSpoolerSeekCmd = 0;
			}
		}

		dataCb = g_dataCallbackPC;
		readyCb = g_readyCallbackPC;

		SDL_UnlockMutex(levelSpoolerPCMutex);

		// clear sector before proceed
		ClearMem(g_sectorData, sizeof(g_sectorData));
		fread(g_sectorData, 1, 2048, fp);

		g_isSectorDataRead = false;

		if (readyCb)
		{
			readyCb(1, { 0x0 });
			
			if (g_isSectorDataRead && dataCb)
				dataCb();
		}
		else
			break;

	} while (!g_spoolDoneFlag);

	SPOOL_INFO("SPOOLER thread work done.\n");

	fclose(fp);

	return 0;
}

//-----------------------------------------------------
// reads sector from LEV file
//-----------------------------------------------------
void startReadLevSectorsPC(int sector)
{
	if (!levelSpoolerPCMutex)
		levelSpoolerPCMutex = SDL_CreateMutex();

	SDL_LockMutex(levelSpoolerPCMutex);
	levelSpoolerSeekCmd = sector;
	SDL_UnlockMutex(levelSpoolerPCMutex);

	if (levelSpoolerPCThread && g_spoolDoneFlag)
	{
		int returnValue;
		SDL_WaitThread(levelSpoolerPCThread, &returnValue);

		levelSpoolerPCThread = NULL;
	}

	if (!levelSpoolerPCThread)
	{
		levelSpoolerPCThread = SDL_CreateThread(levelSpoolerPCFunc, "Spooler", NULL);

		if (NULL == levelSpoolerPCThread)
		{
			SPOOL_ERROR("SDL_CreateThread failed: %s\n", SDL_GetError());
		}
	}
}
#endif // !PSX

// decompiled code
// original method signature: 
// void /*$ra*/ test_changemode()
 // line 532, offset 0x0007b228
	/* begin block 1 */
		// Start line: 534
		// Start offset: 0x0007B228
		// Variables:
	// 		SPOOLQ *current; // $a3
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

// [D] [T]
void test_changemode(void)
{
#ifndef SIMPLE_SPOOL
	SPOOLQ *current = &spooldata[spoolpos_reading];

	if (spoolpos_reading == spoolcounter)
	{
		switch_spooltype = 0;

#ifdef PSX
		CdReadyCallback(0);
		CdControlF(CdlPause, 0);
#else
		levelSpoolerPCReadyCallback(NULL);
		levelSpoolerSeekCmd = -1;
#endif // PSX
	}
	else if (current_sector == current->sector)
	{
		target_address = current->addr;
		switch_spooltype = 1;

		if (current->type == 0)
		{
			sectors_to_read = spool_regioninfo[spool_regionpos + 1].nsectors;
			sectors_this_chunk = (current->nsectors);
#ifdef PSX
			CdReadyCallback(ready_cb_regions);
#else
			levelSpoolerPCReadyCallback(ready_cb_regions);
#endif // PSX
		}
		else if (current->type == 1)
		{
			sectors_to_read = 17;
			target_address += 0x4000;
			nTPchunks_reading = 0;
			nTPchunks_writing = 0;
			ntpages = tsetcounter;
			sectors_this_chunk = 1;
#ifdef PSX
			CdReadyCallback(ready_cb_textures);
#else
			levelSpoolerPCReadyCallback(ready_cb_textures);
#endif // PSX
		}
		else if (current->type == 2)
		{
			sectors_to_read = (current->nsectors);
			send_bank = (current->data);
			sample_chunk = 0;
			nTPchunks_reading = 0;
			nTPchunks_writing = 0;
			target_address = target_address + (loadbank_read & 1U) * 0x1000;
			sectors_this_chunk = 2;

#ifdef PSX
			CdReadyCallback(ready_cb_soundbank);
#else
			levelSpoolerPCReadyCallback(ready_cb_soundbank);
#endif // PSX
		}
		else if (current->type == 3)
		{
			sectors_to_read = (current->nsectors);
#ifdef PSX
			CdReadyCallback(ready_cb_misc);
#else
			levelSpoolerPCReadyCallback(ready_cb_misc);
#endif // PSX
		}
	}
	else
	{
		switch_spooltype = 0;

#ifdef PSX
		CdReadyCallback(0);
#else
		levelSpoolerPCReadyCallback(NULL);
#endif // PSX
	}
#endif // SIMPLE_SPOOL
}



// decompiled code
// original method signature: 
// void /*$ra*/ changemode(SPOOLQ *current /*$a0*/)
 // line 591, offset 0x0007e1a8
	/* begin block 1 */
		// Start line: 1182
	/* end block 1 */
	// End Line: 1183

	/* begin block 2 */
		// Start line: 5397
	/* end block 2 */
	// End Line: 5398

// [D] [T]
void changemode(SPOOLQ *current)
{
#ifndef SIMPLE_SPOOL
	switch_spooltype = 0;
	endchunk = 0;

	switch (current->type)
	{
		case 0:
		{
#ifdef PSX
			CdDataCallback(data_cb_regions);
#else
			levelSpoolerPCDataCallback(data_cb_regions);
#endif // PSX
			break;
		}
		case 1:
		{
#ifdef PSX
			CdDataCallback(data_cb_textures);
#else
			levelSpoolerPCDataCallback(data_cb_textures);
#endif // PSX
			break;
		}
		case 2:
		{
#ifdef PSX
			CdDataCallback(data_cb_soundbank);
#else
			levelSpoolerPCDataCallback(data_cb_soundbank);
#endif // PSX
			break;
		}
		case 3:
		{
#ifdef PSX
			CdDataCallback(data_cb_misc);
#else
			levelSpoolerPCDataCallback(data_cb_misc);
#endif // PSX
			break;
		}
	}
#endif // SIMPLE_SPOOL
}



// decompiled code
// original method signature: 
// int /*$ra*/ check_regions_present()
 // line 625, offset 0x0007b3c4
	/* begin block 1 */
		// Start line: 627
		// Start offset: 0x0007B3C4
		// Variables:
	// 		AREA_LOAD_INFO regions_to_unpack[3]; // stack offset -160
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

// [D] [T]
int check_regions_present(void)
{
	int barrel_region;
	int x, z;
	int region_to_unpack;
	int num_regions_to_unpack;
	int leftright_unpack;
	int topbottom_unpack;
	int retval;
	AREA_LOAD_INFO regions_to_unpack[3];
	char textbuf[128];

	leftright_unpack = 0;
	topbottom_unpack = 0;
	num_regions_to_unpack = 0;

	if (current_barrel_region_xcell < 9) 
	{
		regions_to_unpack[0].xoffset = -1;
		if (region_x != 0) 
		{
			leftright_unpack = 1;
			num_regions_to_unpack = 1;
			regions_to_unpack[0].zoffset = 0;
		}
	}
	else if (current_barrel_region_xcell > 23)
	{
		regions_to_unpack[0].xoffset = 1;

		if (region_x < (cells_across >> 5))
		{
			leftright_unpack = 2;
			num_regions_to_unpack = 1;
			regions_to_unpack[0].zoffset = 0;
		}
	}

	if (current_barrel_region_zcell < 9 && region_z != 0)
	{
		topbottom_unpack = 1;

		regions_to_unpack[num_regions_to_unpack].xoffset = 0;
		regions_to_unpack[num_regions_to_unpack].zoffset = -1;
		num_regions_to_unpack++;
	}
	else if(current_barrel_region_zcell > 23 && region_z != 0)
	{
		topbottom_unpack = 2;

		regions_to_unpack[num_regions_to_unpack].xoffset = 0;
		regions_to_unpack[num_regions_to_unpack].zoffset = 1;
		num_regions_to_unpack++;
	}

	if (num_regions_to_unpack == 2) 
	{
		num_regions_to_unpack = 3;

		if (topbottom_unpack == 1) 
		{
			if (leftright_unpack == 1)
			{
				regions_to_unpack[2].xoffset = -1;
				regions_to_unpack[2].zoffset = -1;
			}
			else 
			{
				regions_to_unpack[2].xoffset = 1;
				regions_to_unpack[2].zoffset = -1;
			}
		}
		else 
		{
			if (leftright_unpack == 1) 
				regions_to_unpack[2].xoffset = -1;
			else 
				regions_to_unpack[2].xoffset = 1;

			regions_to_unpack[2].zoffset = 1;
		}
	}

	retval = 0;
	while (num_regions_to_unpack != 0) 
	{
		x = regions_to_unpack[retval].xoffset;
		z = regions_to_unpack[retval].zoffset;

		region_to_unpack = current_region + x + z * (cells_across >> 5);

		if (loading_region[(region_x + x & 1U) + (region_z + z & 1U) * 2] != -1 &&
			spoolinfo_offsets[region_to_unpack] != 0xffff &&
			loading_region[(region_x + x & 1U) + (region_z + z & 1U) * 2] == region_to_unpack)
		{
			retval++;
		}
		num_regions_to_unpack--;
	}

	if (LoadingArea != 0) 
	{
		if (new_area_location == 1)
		{
			if (current_barrel_region_xcell > 26)
			{
				retval++;
			}
		}
		else
		{
			if (new_area_location < 2) 
			{
				if (new_area_location == 0 && current_barrel_region_zcell > 26)
				{
					retval++;
				}
			}
			else
			{
				barrel_region = current_barrel_region_zcell;
				if ((new_area_location == 2 ||
					(barrel_region = current_barrel_region_xcell, new_area_location == 3)) &&
					barrel_region < 6) 
				{
					retval++;
				}
			}
		}
	}

	return retval;
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

// [D] [T]
void stopgame(void)
{
	StopPadVibration(0);
	StopPadVibration(1);
	PauseSFX();
	DrawSync(0);
	PutDrawEnv(&last->draw);
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

// [D] [T]
void startgame(void)
{
	PutDrawEnv(&current->draw);
	UnPauseSFX();
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
	// 		RECT dest; // stack offset -16
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

extern POLY_FT4 cd_sprite;
extern unsigned short cd_icon[288];

// [D] [T]
void DrawCDicon(void)
{
	ushort *palette;
	RECT16 dest;

	cd_icon[23] = cd_icon[11];

	palette = &cd_icon[10];

	for (int i = 0; i < 12; i++)
	{
		palette[1] = palette[2];
		palette++;
	}

	setRECT16(&dest, 960, 433, 16, 1);
	LoadImage(&dest, (u_long *)palette);

	DrawPrim(&cd_sprite);
	DrawSync(0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckValidSpoolData()
 // line 859, offset 0x0007e2cc
	/* begin block 1 */
		// Start line: 861
		// Start offset: 0x0007E2CC
		// Variables:
	// 		RECT dest; // stack offset -16
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

// [D] [T]
void CheckValidSpoolData(void)
{
	if (models_ready)
		init_spooled_models();

	if (spoolactive)
	{
		if (check_regions_present())
		{
			stopgame();

			while (spoolactive)
			{
				DrawCDicon();
				VSync(0);
			}

			startgame();
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateSpool()
 // line 925, offset 0x0007b6c4
	/* begin block 1 */
		// Start line: 927
		// Start offset: 0x0007B6C4
		// Variables:
	// 		SPOOLQ *current; // $s0
	// 		CdlLOC pos; // stack offset -16
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

// [D] [T]
void UpdateSpool(void)
{
#ifdef SIMPLE_SPOOL
	extern char g_CurrentLevelFileName[64];

	FILE* fp = fopen(g_CurrentLevelFileName, "rb");

	if (!fp)
	{
		char errPrint[1024];
		sprintf(errPrint, "Cannot open '%s'\n", g_CurrentLevelFileName);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", errPrint, NULL);
		return;
	}

	for (; spoolpos_reading < spoolcounter; spoolpos_reading++)
	{
		SPOOLQ *current = &spooldata[spoolpos_reading];

#ifdef _DEBUG
		char* nameType;
		switch (current->type)
		{
		case 0:	// regions
			nameType = "REGION"; 
			break;
		case 1:	// textures
			nameType = "TPAGE";
			break;
		case 2:	// sbk
			nameType = "SBK";
			break;
		case 3:	// misc
			nameType = "MISC";
			break;
		}

		SPOOL_WARNING("spool type=%s cb=%d sec=%d cnt=%d id=%d\n", nameType, current->func ? 1 : 0, current->sector, current->nsectors, spoolpos_reading);
#endif // _DEBUG

		// seek to required sector
		fseek(fp, current->sector * 2048, SEEK_SET);

		switch (current->type)
		{
		case 0:	// regions
			fread(current->addr, 2048, current->nsectors, fp);

			if (current->func)
				current->func();

			break;
		case 1:	// textures

			// read cluts
			nTPchunks = 0;
			fread(current->addr + 0x4000, 2048, 1, fp);
			SendTPage();

			nTPchunks++;

			// read tpage (4 sectors 4 times = 16)
			for (int i = 0; i < 4; i++)
			{
				fread(current->addr + (loadbank_write & 1U) * 256 * 32, 2048, 4, fp);
				SendTPage();

				nTPchunks++;
			}

			break;
		case 2:	// sbk
			// nothing to do with this
			break;
		case 3:	// misc
			fread(current->addr, 2048, current->nsectors, fp);

			if (current->func)
				current->func();

			break;
		}
	}

	spoolcounter = 0;
	spoolpos_reading = 0;
	spoolactive = 0;

	fclose(fp);
	
#else
	char bVar1;
	CdlLOC pos;

	SPOOLQ *current = &spooldata[spoolpos_reading];

	if (!XAPrepared())
	{
		target_address = current->addr;
		bVar1 = current->type;
		
		if (bVar1 == 0) // SPOOLTYPE_REGIONS
		{
			sectors_this_chunk = (current->nsectors);
			sectors_to_read = spool_regioninfo[spool_regionpos].nsectors;

			spoolseek = 5;
#ifdef PSX
			CdDataCallback(data_cb_regions);
			CdReadyCallback(ready_cb_regions);
#else
			levelSpoolerPCDataCallback(data_cb_regions);
			levelSpoolerPCReadyCallback(ready_cb_regions);
#endif // PSX
		}
		else if (bVar1 == 1) // SPOOLTYPE_TEXTURES
		{
			spoolseek = 5;

			nTPchunks_reading = 0;
			nTPchunks_writing = 0;
			sectors_to_read = 17;
			ntpages = tsetcounter;
			sectors_this_chunk = 1;

#ifdef PSX
			CdDataCallback(data_cb_textures);
			CdReadyCallback(ready_cb_textures);
#else
			levelSpoolerPCDataCallback(data_cb_textures);
			levelSpoolerPCReadyCallback(ready_cb_textures);
#endif // PSX

			target_address = target_address + 0x4000;
		}
		else if (bVar1 == 2) // SPOOLTYPE_SOUNDBANK
		{
			sectors_to_read = (current->nsectors);

			send_bank = (current->data);
			spoolseek = 5;
			sample_chunk = 0;
			nTPchunks_reading = 0;
			nTPchunks_writing = 0;
			sectors_this_chunk = 2;

#ifdef PSX
			CdDataCallback(data_cb_soundbank);
			CdReadyCallback(ready_cb_soundbank);
#else
			levelSpoolerPCDataCallback(data_cb_soundbank);
			levelSpoolerPCReadyCallback(ready_cb_soundbank);
#endif // PSX

			target_address = target_address + (loadbank_read & 1U) * 0x1000;
		}
		else if (bVar1 == 3)  // SPOOLTYPE_MISC
		{
			sectors_to_read = (current->nsectors);

			spoolseek = 5;
#ifdef PSX
			CdDataCallback(data_cb_misc);
			CdReadyCallback(ready_cb_misc);
#else
			levelSpoolerPCDataCallback(data_cb_misc);
			levelSpoolerPCReadyCallback(ready_cb_misc);
#endif // PSX
		}

		current_sector = current->sector;
		endchunk = 0;
		switch_spooltype = 0;

		// run sector reading
#ifdef PSX
		CdIntToPos(current_sector, &pos);
		CdControlF(CdlReadS, (u_char*)&pos);
#else
		startReadLevSectorsPC(current_sector);
#endif // PSX
	}
#endif
}



// decompiled code
// original method signature: 
// void /*$ra*/ RequestSpool(int type /*$a0*/, int data /*$a1*/, int offset /*$a2*/, int loadsize /*$a3*/, char *address /*stack 16*/, TDRFuncPtr_RequestSpool5func func /*stack 20*/)
 // line 1104, offset 0x0007e36c
	/* begin block 1 */
		// Start line: 1105
		// Start offset: 0x0007E36C
		// Variables:
	// 		SPOOLQ *next; // $t0
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

// [D] [T]
#ifdef _DEBUG
void _RequestSpool(int type, int data, int offset, int loadsize, char *address, spooledFuncPtr func, const char* requestby, int line)
#define RequestSpool(type, data, offset, loadsize, loadaddr, func) _RequestSpool(type, data, offset, loadsize, loadaddr, func, __FUNCTION__, __LINE__)
#else
void RequestSpool(int type, int data, int offset, int loadsize, char *address, spooledFuncPtr func)
#endif _DEBUG
{
	if (!(spoolcounter < 48))
		trap(0x400);

	SPOOLQ *next;

	next = &spooldata[spoolcounter];

	next->type = type;
	next->data = data;
	next->sector = (citylumps[GameLevel][CITYLUMP_SPOOL].x / 2048) + offset;
	next->nsectors = loadsize;
	next->addr = address;
	next->func = func;

#ifdef _DEBUG
	next->requestby = requestby;
	next->requestbyline = line;
#endif // _DEBUG

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
	// 		CdlLOC pos; // stack offset -24
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

// [D] [T]
void InitSpooling(void)
{
	for (int i = 0; i < 4; i++)
	{
		loading_region[i] = -1;
		ClearRegion(i);
	}

	CleanSpooledModelSlots();

	newmodels = NULL;
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
		// 		RECT cluts; // stack offset -32
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

int tsetinfo[32];

// [D] [T]
void SendTPage(void)
{
	unsigned char old;
	ulong *clutptr;
	int slot;
	int npalettes;
	int tpage2send;
	int i;
	RECT16 cluts;

	tpage2send = tsetinfo[tsetpos * 2];
	slot = tsetinfo[tsetpos * 2 + 1];

	if (tpage2send == 0xFF || slot == 0xFF)	// [A] bug fix
		return;

	if (nTPchunks == 0) 
	{
		if (slot != tpageloaded[tpage2send] - 1)
		{
			npalettes = *(int *)(model_spool_buffer + 0xE000);

			tpage.w = 64;
			tpage.h = 64;
			cluts.w = 64;

			tpage.x = slot_tpagepos[slot].vx;
			tpage.y = slot_tpagepos[slot].vy;

			cluts.y = slot_clutpos[slot].vy;
			cluts.x = slot_clutpos[slot].vx;

			cluts.h = npalettes / 4 + 1;

			LoadImage(&cluts, (u_long *)(model_spool_buffer + 0xE000 + 4));

			clutptr = (ulong *)(texture_cluts[tpage2send]);
			i = 0;

			while (i < npalettes)
			{
				clutptr[0] = getClut(cluts.x + 16, cluts.y) << 0x10 | getClut(cluts.x, cluts.y);
				clutptr[1] = getClut(cluts.x + 48, cluts.y) << 0x10 | getClut(cluts.x + 32, cluts.y);

				clutptr+=2;

				cluts.y++;

				i += 4;
			}

			texture_pages[tpage2send] = getTPage(0, 0, tpage.x, tpage.y);
		}
	}
	else 
	{
		if (slot != tpageloaded[tpage2send] - 1) 
		{
			LoadImage(&tpage, (u_long *)(model_spool_buffer + 0xA000 + (loadbank_write % 2) * 256 * 32));
			tpage.y = tpage.y + tpage.h;
		}

		if (nTPchunks == 4)
		{
			old = tpageslots[slot];
			tpageslots[slot] = tpage2send;

			if(old != 0xFF)	// [A] bug fix
				tpageloaded[old] = 0;

			tpageloaded[tpage2send] = slot + 1;

			tsetpos++;

			if (tsetpos == tsetcounter)
			{
				tsetcounter = 0;
				tsetpos = 0;
			}

#ifndef PSX
			// [A] try override
			LoadTPageFromTIMs(tpage2send);
#endif
		}
	}

	//extern void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer);
	//Emulator_SaveVRAM("VRAM_CLUTS_TPAGES.TGA", 0, 0, 1024, 512, 1);
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

// [D] [T]
void SpoolSYNC(void)
{
	do {
	} while (spoolactive != 0);
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

// [D] [T]
void LoadInAreaTSets(int area)
{
	int offset;
	int i;

	int slot;

	unsigned char *tpages;
	int ntpages_to_load;
	int navailable;

	char *loadaddr;
	int availableslots[16];

	tpages = AreaTPages + area * 16;
	ntpages_to_load = AreaData[area].num_tpages;

	if (!ntpages_to_load)
		return;

	loadaddr = model_spool_buffer + 0xA000;
	navailable = 0;

	slot = slotsused;

	// get available slots
	for (slot = slotsused; slot < 19; slot++)
	{
		// use free slot immediately
		if (tpageslots[slot] == 0xff)
		{
			availableslots[navailable++] = slot;
			continue;
		}

		for (i = 0; i < ntpages_to_load; i++)
		{
			// check if needed tpages are not already loaded
			if (tpageslots[slot] != tpages[i])
			{
				availableslots[navailable++] = slot;
				break;
			}
		}
	}

	offset = AreaData[area].gfx_offset;

	i = 0;
	for (slot = 0; slot < navailable; slot++)
	{
		if (i < ntpages_to_load)
		{
			tsetinfo[tsetcounter * 2 + 1] = availableslots[slot];
			tsetinfo[tsetcounter * 2] = tpages[i];

			RequestSpool(1, 0, offset, 17, loadaddr, SendTPage);
			offset += 17;

			tsetcounter++;
			i++;
		}
		else
			break;
	}
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
	// 		MODEL *parentmodel; // $a1

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

// [D] [T]
void init_spooled_models(void)
{
	int nmodels;
	ushort lod;
	int model_number;
	MODEL *parentmodel;
	char *addr;
	MODEL *model;
	int i;
	int size;

	addr = model_spool_buffer;
	models_ready = 0;

	nmodels = *newmodels;

	SPOOL_INFO("loading %d model slots\n", nmodels);

	unsigned short* new_model_numbers = newmodels + 1;

	for (i = 0; i < nmodels; i++)
	{
		model_number = new_model_numbers[i];

		size = *(int *)addr;
		model = (MODEL *)(addr + 4);

		lod = Low2LowerDetailTable[model_number];

		if (lod != 0xffff && lod != model_number)
			pLodModels[model_number] = modelpointers[lod];

		if (model->instance_number == -1)
		{
			if (model->collision_block != 0)
				model->collision_block += (int)model;

			model->vertices += (int)model;
			model->normals += (int)model;
			model->point_normals += (int)model;

			InitSpooledAnimObj(model_number);
		}
		else
		{
			parentmodel = modelpointers[model->instance_number];

			if (parentmodel->collision_block != 0)
				model->collision_block = parentmodel->collision_block;

			model->vertices = parentmodel->vertices;
			model->normals = parentmodel->normals;
			model->point_normals = parentmodel->point_normals;

			InitSpooledAnimObj(parentmodel->instance_number);
		}
	
		model->poly_block += (int)model;

		modelpointers[model_number] = model;
		pLodModels[model_number] = model;

		addr += size + 4;
	}

	LoadingArea = 0;
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

// [D] [T]
void SetupModels(void)
{
	if (old_region == -1)
		init_spooled_models();
	else
		models_ready = 1;
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

// [D] [T]
void LoadInAreaModels(int area)
{
	int num_freed;

	// [A] invalidate previously used spooled slots
	num_freed = CleanSpooledModelSlots();

	SPOOL_INFO("freed %d model slots\n", num_freed);

	int length = AreaData[area].model_size;
	newmodels = (ushort *)(model_spool_buffer + (length-1) * 2048);

	RequestSpool(3, 0, AreaData[area].model_offset, length, model_spool_buffer, SetupModels);
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
	// 		Spool *spoolptr; // $t1
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

// [D] [T]
void CheckLoadAreaData(int cellx, int cellz)
{
	int nAreas;
	int load;
	int force_load_boundary;
	int i;
	Spool *spoolptr;

	if (spoolinfo_offsets[current_region] == 0xffff)
		return;

	spoolptr = (Spool *)(RegionSpoolInfo + spoolinfo_offsets[current_region]);

#ifndef PSX
	if (LoadedArea != spoolptr->super_region && spoolptr->super_region != 0xFF && old_region != -1)
	{
		LoadedArea = spoolptr->super_region;
	}
	else
#endif
	if (old_region == -1 && spoolptr->super_region != 0xFF)
	{
		// just load the area if no
		LoadedArea = spoolptr->super_region;
	}
	else
	{
		nAreas = spoolptr->num_connected_areas;

		if (old_region == -1)
		{
			LoadedArea = -1;
		}
		else
		{
			//if (spoolptr->super_region == 0xFF)		// [A] if this is on, it stops spool. You still may want to load connected areas
			//	return;

			if (nAreas == 0)
				return;
		}

		force_load_boundary = (lead_car == 0) ? 15 : 13;

		// check area bounds
		for (i = 0; i < nAreas; i++)
		{
			load = spoolptr->connected_areas[i] >> 6;

			if (LoadedArea != (spoolptr->connected_areas[i] & 0x3f))
			{
				new_area_location = load;

				// [A] bounds?
				if (load == 0 && (cellz > MAP_REGION_SIZE - force_load_boundary))
				{
					break;
				}
				else if (load == 1 && (cellx > MAP_REGION_SIZE - force_load_boundary))
				{
					break;
				}
				else if (load == 2 && (cellz < force_load_boundary))
				{
					break;
				}
				else if (load == 3 && (cellx < force_load_boundary))
				{
					break;
				}
			}
		}

		if (nAreas == i)
		{
			if (LoadedArea != -1)
				return;

			LoadedArea = initarea;

			if (initarea == -1)
				return;
		}
		else
		{
			LoadedArea = spoolptr->connected_areas[i] & 0x3f;
		}
	}

	LoadingArea = 1;

	LoadInAreaTSets(LoadedArea);
	LoadInAreaModels(LoadedArea);
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

// [D] [T]
void ClearRegion(int target_region)
{
	long *pvsptr;
	ushort *cell_ptrs_s;
	int loop;

	loop = 1024;
	cell_ptrs_s = cell_ptrs + target_region * 1024;
	pvsptr = (long *)PVS_Buffers[target_region];

	do {
		*cell_ptrs_s++ = 0xffff;
		*pvsptr++ = 0;
	} while (--loop != 0);

	ClearMem(PVS_Buffers[target_region]-4, pvsSize[target_region]);

	RoadMapDataRegions[target_region] = (short*)PVS_Buffers[0];
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
	// 		Spool *spoolptr; // $s1
	// 		char *roadmap_buffer; // $s6
	// 		char *cell_buffer; // $s3
	/* end block 1 */
	// End offset: 0x0007C464
	// End Line: 1776

	/* begin block 2 */
		// Start line: 3836
	/* end block 2 */
	// End Line: 3837


// [D] [T]
int LoadRegionData(int region, int target_region)
{
	char *cell_buffer;
	ushort *spofs;
	int offset;
	Spool *spoolptr;
	char *roadmap_buffer;	// D1 leftover?

	roadmap_buffer = NULL; // [A]

	spofs = (spoolinfo_offsets + region);

	if (*spofs == 0xFFFF)	// has region offset?
		return 0;

	loading_region[target_region] = region;
	cell_buffer = packed_cell_pointers;
	spoolptr = (Spool *)(RegionSpoolInfo + *spofs);

	offset = spoolptr->offset;

#ifndef PSX
	if (gDemoLevel)
	{
		RequestSpool(0, 0, offset, spoolptr->roadm_size, PVS_Buffers[target_region], NULL);
		offset += spoolptr->roadm_size;

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[1], packed_cell_pointers, NULL);
		offset += spoolptr->cell_data_size[1];

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[0], (char *)(cells + cell_slots_add[target_region]), NULL);
		offset += spoolptr->cell_data_size[0];

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[2], (char *)(cell_objects + num_straddlers + cell_objects_add[target_region]), GotRegion);
		offset += spoolptr->cell_data_size[2];

		//offset -= spoolptr->roadm_size; // [A] if PVS_Buffers loading temporarily disabled this should be uncommented
	}
	else if (gDriver1Level)
	{
		// TODO: ....

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[0], (char *)(cell_objects + num_straddlers + cell_objects_add[target_region]), NULL);
		offset += spoolptr->cell_data_size[0];

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[1], (char *)(cells + cell_slots_add[target_region]), NULL);
		offset += spoolptr->cell_data_size[1];

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[2], packed_cell_pointers, GotRegion);
		offset += spoolptr->cell_data_size[2];

	}
	else
#endif
	{
		RequestSpool(0, 0, offset, spoolptr->cell_data_size[1], packed_cell_pointers, NULL);
		offset += spoolptr->cell_data_size[1];

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[0], (char *)(cells + cell_slots_add[target_region]), NULL);
		offset += spoolptr->cell_data_size[0];

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[2], (char *)(cell_objects + num_straddlers + cell_objects_add[target_region]), NULL);
		offset += spoolptr->cell_data_size[2];

		RequestSpool(0, 0, offset, spoolptr->roadm_size, PVS_Buffers[target_region] - 4, GotRegion);
		offset += spoolptr->roadm_size;
	}

	spool_regioninfo[spool_regioncounter].nsectors = offset - spoolptr->offset;

	spool_regioninfo[spool_regioncounter].region_to_unpack = region;
	spool_regioninfo[spool_regioncounter].target_barrel_region = target_region;
	spool_regioninfo[spool_regioncounter].cell_addr = cell_buffer;
	spool_regioninfo[spool_regioncounter].roadm_addr = roadmap_buffer;

	return 1;
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

// [D] [T]
void UnpackRegion(int region_to_unpack, int target_barrel_region)
{
	if (loading_region[target_barrel_region] == -1) 
	{
		if (LoadRegionData(region_to_unpack, target_barrel_region))
			spool_regioncounter++;

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

inline int _getIntAdv(char** ptr)
{
	int value = *(int*)*ptr;
	*ptr += 4;
	return value;
}

#define getIntAdv(ptr) _getIntAdv(&ptr)

// [D] [T]
void ProcessSpoolInfoLump(char *lump_ptr, int lump_size)
{
	int i;
	int size;
	char *alloclist;

	pvsSize[0] = 0;
	pvsSize[1] = 0;
	pvsSize[2] = 0;
	pvsSize[3] = 0;

	char* ptr = lump_ptr;

	size = getIntAdv(ptr) * 2048;

	if (size < 0x10000)
		size = 0x10000;	// smaller still should be fixed to 64k

	MALLOC_BEGIN();
	model_spool_buffer = D_MALLOC(size);
	MALLOC_END();

	cell_slots_add[4] = 0;
	cell_objects_add[4] = 0;

	int music_and_ambients_size = getIntAdv(ptr);
	Music_And_AmbientOffsets = (SXYPAIR *)ptr;	// [A] seems to be UNUSED
	ptr += music_and_ambients_size;

	NumAreas = getIntAdv(ptr);
	AreaData = (AreaDataStr *)ptr; 
	ptr += sizeof(AreaDataStr) * NumAreas;

	AreaTPages = (unsigned char *)ptr;
	ptr += NumAreas * 16;

	// get the pointers
	int* slots_add = (int *)ptr;
	ptr += sizeof(int) * 4;

	int* objects_add = (int *)ptr;
	ptr += sizeof(int) * 4;

	int* pvsSizes = (int *)ptr;
	ptr += sizeof(int) * 4;

	for (i = 0; i < 4; i++)
	{
		int slots_count = slots_add[i];
		int objects_count = objects_add[i];

		// set last totals
		cell_objects_add[i] = cell_objects_add[4];
		cell_slots_add[i] = cell_slots_add[4];
		
		// increment totals
		cell_slots_add[4] += slots_count;
		cell_objects_add[4] += objects_count;

		// by the fact it's a roadmap size + pvs size
		pvsSize[i] = pvsSizes[i] + 0x7ffU & 0xfffff800;

		MALLOC_BEGIN();
		alloclist = D_MALLOC(pvsSize[i]);
		MALLOC_END();

		PVS_Buffers[i] = alloclist + 4;		// +4 for -1 cases
	}

	int num_of_regions = getIntAdv(ptr);
	spoolinfo_offsets = (ushort*)ptr;
	ptr += sizeof(ushort) * num_of_regions;

	int spoolinfo_size = getIntAdv(ptr);
	RegionSpoolInfo = ptr;
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

// [D] [T]
void WaitCloseLid(void)
{
#ifdef PSX
	void (*old)();
	int loop;

	old = (void(*)())CdReadyCallback(0);
	stopgame();

	while (loop = CdDiskReady(1), loop != 2) 
	{
		DrawCDicon();
		VSync(0);
	}

	startgame();

	CdReadyCallback((CdlCB)old);
#endif // PSX
}



// decompiled code
// original method signature: 
// void /*$ra*/ FoundError(char *name /*$a0*/, unsigned char intr /*$a1*/, unsigned char *result /*$a2*/)
 // line 1945, offset 0x0007e6d8
	/* begin block 1 */
		// Start line: 1947
		// Start offset: 0x0007E6D8
		// Variables:
	// 		CdlLOC p; // stack offset -16
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

// [D] [T]
void FoundError(char *name, unsigned char intr, unsigned char *result)
{
#ifndef SIMPLE_SPOOL
	CdlLOC p;

#ifdef PSX
	if ((*result & 0x10) != 0)
	{
		WaitCloseLid();
	}
#endif // PSX


#ifdef _DEBUG
	SPOOL_ERROR("FoundError: %s, intr: %d\n", name, intr);
#endif // _DEBUG

	spoolerror = 0x3c;
#ifdef PSX
	CdIntToPos(current_sector, &p);
	CdControlF(CdlReadS, (u_char*)&p);
#else
	UNIMPLEMENTED();
#endif
#endif // SIMPLE_SPOOL
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

// [D] [T]
void GotRegion(void)
{
	uint target_barrel_reg;

	Unpack_CellPtrs();

	target_barrel_reg = spool_regioninfo[spool_regionpos].target_barrel_region;
	spool_regionpos++;

	char* pvs = PVS_Buffers[target_barrel_reg];

	loading_region[target_barrel_reg] = -1;

	int cbr = *(int *)(pvs - 4);
	RoadMapDataRegions[target_barrel_reg] = (short*)(pvs + cbr);

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

// [D] [T]
void data_cb_textures(void)
{
#ifndef SIMPLE_SPOOL
	//printf("data_cb_textures remaining: %d\n", sectors_to_read);

	if (chunk_complete != 0) 
	{
		chunk_complete = 0;
		nTPchunks = nTPchunks_writing;

		SendTPage();

		if (nTPchunks != 0)
			loadbank_write++;

		nTPchunks_writing++;

		if (nTPchunks_writing == 5)
		{
			nTPchunks_writing = 0;
			spoolpos_writing++;

			if (ntpages == 0)
			{
				if (switch_spooltype == 0)
				{
#ifdef PSX
					CdDataCallback(0);
#else
					levelSpoolerPCDataCallback(NULL);
#endif // PSX

					if (spoolpos_writing == spoolcounter)
					{
						SPOOL_WARNING("All SPOOL requests (%d) completed successfully on TEXTURES\n", spoolcounter);	// [A]

						spoolcounter = 0;
						spoolpos_writing = 0;
						spoolpos_reading = 0;
						spoolactive = 0;
					}
					else
					{
						UpdateSpool();
					}
				}
				else
				{
					changemode(spooldata + spoolpos_writing);
				}
			}
		}
	}
#endif // SIMPLE_SPOOL
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
		// 		SPOOLQ *current; // $a2
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

// [D] [T]
void ready_cb_textures(unsigned char intr, unsigned char *result)
{
#ifndef SIMPLE_SPOOL
	if (intr == 1)
	{
#ifdef PSX
		CdGetSector(target_address, 0x200);
#else
		getLevSectorPC(target_address, 0x200);
#endif // PSX

		target_address = target_address + 0x800;
		sectors_this_chunk--;
		current_sector++;
		sectors_to_read--;

		if (sectors_this_chunk == 0) 
		{
			if (nTPchunks_reading != 0)
				loadbank_read++;

			nTPchunks_reading++;
			chunk_complete = intr;

			if (sectors_to_read == 0)
			{
				ntpages--;

				if (ntpages == 0)
				{
					spoolpos_reading++;
					test_changemode();
				}
				else
				{
					nTPchunks_reading = 0;
					sectors_to_read = 17;

					target_address = spooldata[spoolpos_reading].addr + 0x4000;
					spoolpos_reading++;

					sectors_this_chunk = intr;
				}
			}
			else 
			{
				sectors_this_chunk = 4;
				target_address = spooldata[spoolpos_reading].addr + (loadbank_read & 1U) * 0x2000;
			}
		}
	}
	else 
		FoundError("ready_cb_textures", intr, result);
#endif // SIMPLE_SPOOL
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
		// 		SPOOLQ *current; // $v1
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

// [D] [T]
void ready_cb_regions(unsigned char intr, unsigned char *result)
{
#ifndef SIMPLE_SPOOL
	if (intr == 1) 
	{
#ifdef PSX
		CdGetSector(target_address, 0x200);
#else
		getLevSectorPC(target_address, 0x200);
#endif // PSX

		target_address = target_address + 0x800;
		sectors_this_chunk--;
		current_sector++;
		sectors_to_read--;

		if (sectors_this_chunk == 0) 
		{
			spoolpos_reading++;
			chunk_complete = intr;

			if (sectors_to_read == 0)
			{
				endchunk = intr;
				test_changemode();
			}
			else 
			{
				target_address = spooldata[spoolpos_reading].addr;
				sectors_this_chunk = (spooldata[spoolpos_reading].nsectors);
			}
		}
	}
	else 
		FoundError("ready_cb_regions", intr, result);
#endif // SIMPLE_SPOOL
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
		// 		SPOOLQ *current; // $v0
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

// [D] [T]
void data_cb_regions(void)
{
#ifndef SIMPLE_SPOOL
	//printf("data_cb_regions remaining: %d\n", sectors_to_read);

	SPOOLQ* current = &spooldata[spoolpos_writing];

	if (chunk_complete != 0) 
	{
		chunk_complete = 0;

		if (current->func != NULL)
			(current->func)();

		spoolpos_writing++;

		if (endchunk != 0)
		{
			if (switch_spooltype == 0) 
			{
#ifdef PSX
				CdDataCallback(0);
#else
				levelSpoolerPCDataCallback(NULL);
#endif // PSX

				if (spoolpos_writing == spoolcounter) 
				{
					SPOOL_WARNING("All SPOOL requests (%d) completed successfully on REGIONS\n", spoolcounter);	// [A]

					spoolcounter = 0;
					spoolpos_writing = 0;
					spoolpos_reading = 0;
					spoolactive = 0;
				}
				else 
				{
					UpdateSpool();
				}
			}
			else 
			{
				changemode(&spooldata[spoolpos_writing]);
			}
		}
	}
#endif // SIMPLE_SPOOL
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
#ifndef SIMPLE_SPOOL
	if (chunk_complete != 0) {
		chunk_complete = 0;
		SendSBK();
		loadbank_write++;
		if (endchunk != 0) {
			spoolpos_writing++;
			if (switch_spooltype == 0) {
#ifdef PSX
				CdDataCallback(0);
#else
				levelSpoolerPCDataCallback(NULL);
#endif // PSX
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
#endif
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
		// 		SPOOLQ *current; // $a0
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
#ifndef SIMPLE_SPOOL
	if (intr == 1) {
#ifdef PSX
		CdGetSector(target_address, 0x200);
#else
		getLevSectorPC(target_address, 0x200);
#endif // PSX

		target_address = target_address + 0x800;
		sectors_this_chunk--;
		current_sector++;
		sectors_to_read--;
		if (sectors_this_chunk == 0) {
			loadbank_read++;
			nTPchunks_reading++;
			chunk_complete = intr;
			if (sectors_to_read == 0) {
				spoolpos_reading++;
				endchunk = intr;
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
		FoundError("ready_cb_soundbank", intr, result);
	}
#endif
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
		// 		SPOOLQ *current; // $v0
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

// [D] [T]
void data_cb_misc(void)
{
#ifndef SIMPLE_SPOOL
	//printf("data_cb_misc remaining: %d\n", sectors_to_read);

	SPOOLQ *current = &spooldata[spoolpos_writing];

	if (chunk_complete != 0) 
	{
		chunk_complete = 0;

		if (current->func != NULL)
			(*current->func)();

		spoolpos_writing++;

		if (switch_spooltype == 0)
		{
#ifdef PSX
			CdDataCallback(0);
#else
			levelSpoolerPCDataCallback(NULL);
#endif // PSX
			if (spoolpos_writing == spoolcounter)
			{
				SPOOL_WARNING("All SPOOL requests (%d) completed successfully on MISC\n", spoolcounter);	// [A]

				spoolcounter = 0;
				spoolpos_writing = 0;
				spoolpos_reading = 0;
				spoolactive = 0;
			}
			else
			{
				UpdateSpool();
			}
		}
		else
		{
			changemode(spooldata + spoolpos_writing);
		}
	}
#endif // SIMPLE_SPOOL
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

// [D] [T]
void ready_cb_misc(unsigned char intr, unsigned char *result)
{
#ifndef SIMPLE_SPOOL
	if (intr == 1) 
	{
#ifdef PSX
		CdGetSector(target_address, 0x200);
#else
		getLevSectorPC(target_address, 0x200);
#endif // PSX

		target_address += 0x800;
		sectors_to_read--;
		current_sector++;

		if (sectors_to_read == 0) 
		{
			spoolpos_reading++;
			chunk_complete = intr;
			test_changemode();
		}
	}
	else 
	{
		FoundError("ready_cb_misc", intr, result);
	}
#endif // SIMPLE_SPOOL
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

// [D] [T]
void StartSpooling(void)
{
	if (spoolcounter == 0 || spoolactive)
		return;

	if (XAPrepared())
		return;

#ifdef PSX
			static unsigned char param[8];
			static unsigned char result[8];

			param[0] = CdlModeSize0 | CdlModeSize1 | CdlModeSpeed;
			CdControlB(CdlSetmode, param, result);

			if ((result[0] & (CdlStatError | CdlStatShellOpen)) != 0)
			{
				WaitCloseLid();
			}
#endif // PSX
	spoolactive = 1;
	UpdateSpool();

	if (FastForward)
		SpoolSYNC();
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

// [D] [T] [A] - altered declaration
void unpack_cellpointers(int region_to_unpack, int target_barrel_region, char* cell_addr)
{
	ushort cell;
	ushort* short_ptr;
	ushort* source_packed_data;
	int loop;
	uint bitpos;
	uint pcode;

	int packtype;
	
	unpack_cellptr_flag = 0;
	packtype = *(int *)(cell_addr + 4);
	source_packed_data = (ushort *)(cell_addr + 8);

	if (packtype == 0)
	{
		short_ptr = cell_ptrs + target_barrel_region * 1024;

		for (loop = 0; loop < 1024; loop++)
			*short_ptr++ = 0xffff;
	}
	else if (packtype == 1)
	{
		short_ptr = cell_ptrs + target_barrel_region * 1024;

		for (loop = 0; loop < 1024; loop++)
		{
			cell = *source_packed_data++;

			if (cell != 0xffff)
				cell += cell_slots_add[target_barrel_region];

			*short_ptr++ = cell;
		}
	}
	else if (packtype == 2)
	{
		bitpos = 0x8000;
		pcode = (uint)*source_packed_data;
		source_packed_data++;
		short_ptr = cell_ptrs + target_barrel_region * 1024;

		for (loop = 0; loop < 1024; loop++)
		{
			if (pcode & bitpos)
			{
				cell = *source_packed_data++;
				cell += cell_slots_add[target_barrel_region];

			}
			else
				cell = 0xffff;

			bitpos >>= 1;
			*short_ptr++ = cell;

			if (bitpos == 0)
			{
				bitpos = 0x8000;
				pcode = *source_packed_data++;
			}
		}
	}
	else 
	{
		printError("BAD PACKED CELL POINTER DATA, region = %d\n", region_to_unpack);

		do {
			trap(0x400);
		} while (FrameCnt != 0x78654321);

		unpack_cellptr_flag = 0;
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

// [D] [T] [A] altered unpack_cellpointers
void Unpack_CellPtrs(void)
{
	SPL_REGIONINFO* spool = &spool_regioninfo[spool_regionpos];

	unpack_cellpointers(spool->region_to_unpack, spool->target_barrel_region, spool->cell_addr);
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
	// 		RECT specCluts; // stack offset -48

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

// [D] [T] [A]
void SpecClutsSpooled(void)
{
	char *loadaddr;
	RECT16 specCluts;

	specCluts.x = slot_clutpos[specialSlot].vx;
	specCluts.y = slot_clutpos[specialSlot].vy;
	specCluts.w = 16;
	specCluts.h = 1;

	loadaddr = specLoadBuffer;

	for (int i = 0; i < 2; i++)
	{
		int index = specialSlot + i;
		int tpage = specTpages[GameLevel][(specspooldata[2]-1) * 2 + i];

		carTpages[GameLevel][i + 6] = tpageslots[index] = tpage;
		tpageloaded[tpage] = specialSlot + i + 1;

		slot_tpagepos[index].vx = tpagepos[index].x;
		slot_tpagepos[index].vy = tpagepos[index].y;

		texture_pages[tpage] = GetTPage(0, 0, slot_tpagepos[index].vx, slot_tpagepos[index].vy);
		
		for (int j = 0; j < tpage_texamts[tpage]; j++)
		{
			LoadImage2(&specCluts, (u_long*)loadaddr);
			loadaddr += 32;

			texture_cluts[tpage][j] = GetClut(specCluts.x, specCluts.y);
			IncrementClutNum(&specCluts);
		}
	}

	if (quickSpool != 1)
	{
		DrawSyncCallback(SpecialStartNextBlock);
	}
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

int *modelMemory;

int lengthLowBlock;
int lastCleanBlock;
int lengthDamBlock;

int firstLowBlock;
int firstDamBlock;

int specBlocksToLoad = 0;
int specialState = 0;
char specModelValid = 1;
int specSpoolComplete;

// [D] [T]
void CleanModelSpooled(void)
{
	int *loadaddr;
	int *mem;

	loadaddr = (int *)specLoadBuffer;
	
	if (specBlocksToLoad == lastCleanBlock-1) 
	{
		loadaddr = (int *)(specLoadBuffer + 12);

		modelMemory = (int *)specmallocptr;
		gCarCleanModelPtr[4] = (MODEL *)modelMemory;
	}

	// memcpy
	while (loadaddr < (int*)(specLoadBuffer + 2048))
		*modelMemory++ = *loadaddr++;

	mem = (int*)((int)gCarCleanModelPtr[4] + gCarCleanModelPtr[4]->poly_block);	// [A] pls check, might be invalid

	if (specBlocksToLoad == 0 || mem < modelMemory)
	{
#ifndef PSX
		// [A] vertices
		LoadCarModelFromFile((char*)gCarCleanModelPtr[4], MissionHeader->residentModels[4], CAR_MODEL_CLEAN);
#endif
		
		specBlocksToLoad = 0;
		modelMemory = mem;

		gCarCleanModelPtr[4]->vertices += (int)gCarCleanModelPtr[4];
		gCarCleanModelPtr[4]->normals += (int)gCarCleanModelPtr[4];
		gCarCleanModelPtr[4]->point_normals += (int)gCarCleanModelPtr[4];
		gCarCleanModelPtr[4]->poly_block += (int)gCarCleanModelPtr[4];

		NewCarModel[4].nlist = (SVECTOR *)gCarCleanModelPtr[4]->point_normals;
		NewCarModel[4].vlist = (SVECTOR *)gCarCleanModelPtr[4]->vertices;
	}

	if (quickSpool != 1)
		DrawSyncCallback(SpecialStartNextBlock);
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

int damOffset;

// [D] [T]
void DamagedModelSpooled(void)
{
	int *loadaddr;
	int *mem;

	loadaddr = (int *)specLoadBuffer;

	if (specBlocksToLoad == lengthDamBlock-1) 
	{
		loadaddr = (int *)(specLoadBuffer + damOffset);

		gCarDamModelPtr[4] = (MODEL *)modelMemory;
	}
	
	// memcpy
	while (loadaddr < (int*)(specLoadBuffer + 2048))
		*modelMemory++ = *loadaddr++;

	mem = (int*)((int)gCarDamModelPtr[4] + gCarDamModelPtr[4]->poly_block);	// [A] pls check, might be invalid

	if (specBlocksToLoad == 0 || mem < modelMemory)
	{
#ifndef PSX
		// [A] vertices
		LoadCarModelFromFile((char*)gCarDamModelPtr[4], MissionHeader->residentModels[4], CAR_MODEL_DAMAGED);
#endif
		
		specBlocksToLoad = 0;
		modelMemory = mem;

		gCarDamModelPtr[4]->vertices += (int)gCarDamModelPtr[4];
		gCarDamModelPtr[4]->normals += (int)gCarDamModelPtr[4];
		gCarDamModelPtr[4]->poly_block += (int)gCarDamModelPtr[4];
		gCarDamModelPtr[4]->point_normals += (int)gCarDamModelPtr[4];
	}

	if (quickSpool != 1)
		DrawSyncCallback(SpecialStartNextBlock);

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

int lowOffset;

// [D] [T]
void LowModelSpooled(void)
{
	int *loadaddr;
	int *mem;

	loadaddr = (int *)specLoadBuffer;

	if (specBlocksToLoad == lengthLowBlock - 1) 
	{
		loadaddr = (int *)(specLoadBuffer + lowOffset);

		gCarLowModelPtr[4] = (MODEL *)modelMemory;
	}
	
	// memcpy
	while (loadaddr < (int*)(specLoadBuffer + 2048))
		*modelMemory++ = *loadaddr++;

	mem = (int*)((int)gCarLowModelPtr[4] + gCarLowModelPtr[4]->poly_block);	// [A] pls check, might be invalid

	if (specBlocksToLoad == 0 || mem < modelMemory)
	{
#ifndef PSX
		// [A] vertices
		LoadCarModelFromFile((char*)gCarLowModelPtr[4], MissionHeader->residentModels[4], CAR_MODEL_LOWDETAIL);
#endif
		
		specBlocksToLoad = 0;
		modelMemory = mem;

		gCarLowModelPtr[4]->vertices += (int)gCarLowModelPtr[4];
		gCarLowModelPtr[4]->normals += (int)gCarLowModelPtr[4];
		gCarLowModelPtr[4]->poly_block += (int)gCarLowModelPtr[4];
		gCarLowModelPtr[4]->point_normals += (int)gCarLowModelPtr[4];

		NewLowCarModel[4].nlist = (SVECTOR *)gCarLowModelPtr[4]->point_normals;
		NewLowCarModel[4].vlist = (SVECTOR *)gCarLowModelPtr[4]->vertices;
	}

	if (quickSpool != 1) {
		DrawSyncCallback(SpecialStartNextBlock);
	}
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
		// 		MODEL *tempModel; // $a1
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

// [D] [T] [A]
void CleanSpooled(void)
{
	MODEL *model;

	if (specBlocksToLoad == 6)
	{
		// [A] for readability sake
		int size_1 = ((int *)specmallocptr)[0];
		int size_2 = ((int *)specmallocptr)[1];
		int size_3 = ((int *)specmallocptr)[2];

		lastCleanBlock = size_1 + 2048 + 11;
		lastCleanBlock >>= 11;

		firstDamBlock = size_1 + 12;
		firstDamBlock >>= 11;

		firstLowBlock = size_1 + size_2 + 12;
		firstLowBlock >>= 11;

		int lastDamBlock = size_1 + size_2 + 2048 + 11;
		lastDamBlock >>= 11;

		lengthDamBlock = lastDamBlock - firstDamBlock;
		damOffset = size_1 - (firstDamBlock * 2048 - 12);

		int lastLowBlock = size_1 + size_2 + size_3 + 2048 + 11;
		lastLowBlock >>= 11;

		lengthLowBlock = lastLowBlock - firstLowBlock;
		lowOffset = size_1 + size_2 - (firstLowBlock * 2048 - 12);
	}

	model = (MODEL *)(specmallocptr + 12);

	if (specBlocksToLoad == 7-lastCleanBlock) 
	{
#ifndef PSX
		// [A] polygons
		LoadCarModelFromFile((char*)model, MissionHeader->residentModels[4], CAR_MODEL_CLEAN);
#endif
		
		model->vertices += (int)model;
		model->poly_block += (int)model;
		model->normals += (int)model;
		model->point_normals += (int)model;

		whichCP = baseSpecCP;

		buildNewCarFromModel(&NewCarModel[4], model, 0);
		specBlocksToLoad = 0;
	}

	if (quickSpool != 1)
		DrawSyncCallback(SpecialStartNextBlock);
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
		// 		MODEL *tempModel; // $a1
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

// [D] [T]
void LowSpooled(void)
{
	MODEL *model;

	if (specBlocksToLoad == 0) 
	{
		model = (MODEL *)(specmallocptr + lowOffset);

#ifndef PSX
		// [A] loads car model from file
		LoadCarModelFromFile((char*)model, MissionHeader->residentModels[4], CAR_MODEL_LOWDETAIL);
#endif
		
		model->vertices += (int)model;
		model->normals += (int)model;
		model->poly_block += (int)model;
		model->point_normals += (int)model;

		buildNewCarFromModel(&NewLowCarModel[4], model, 0);
	}

	if (quickSpool != 1) 
		DrawSyncCallback(SpecialStartNextBlock);
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
		// 		RECT tpage; // stack offset -32
		// 		int spec_tpage; // $a0
		/* end block 1.1 */
		// End offset: 0x0007D018
		// End Line: 2764

		/* begin block 1.2 */
			// Start line: 2767
			// Start offset: 0x0007D018
			// Variables:
		// 		RECT tpage; // stack offset -24
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

// [D] [T]
void Tada(void)
{
	int spec_tpage;
	RECT16 tpagerect;

	if (specialState == 2)
	{
		tpagerect.w = 64;
		tpagerect.h = 16;

		spec_tpage = specialSlot + 1;
		tpagerect.x = tpagepos[spec_tpage].x;
		tpagerect.y = tpagepos[spec_tpage].y + (15 - specBlocksToLoad) * 16;

		if (specBlocksToLoad == 15) 
			update_slotinfo(specTpages[GameLevel][specspooldata[2]-1], specialSlot, &tpagerect);

		LoadImage(&tpagerect, (u_long *)specLoadBuffer);

#ifndef PSX
		if(specBlocksToLoad == 0)
		{
			for (int i = 0; i < 2; i++)
			{
				int tpage = specTpages[GameLevel][(specspooldata[2] - 1) * 2 + i];

				// [A] try override
				LoadTPageFromTIMs(tpage);
			}
		}
#endif
	}
	else
	{
		if (specialState > 2) 
		{
			if (specialState != 4)
				return;

			SetupSpecCosmetics(specLoadBuffer);
			FixCarCos(&car_cosmetics[4], MissionHeader->residentModels[4]);
			SetupSpecDenting(specLoadBuffer + sizeof(CAR_COSMETICS));

			if (quickSpool == 1)
				return;

			DrawSyncCallback(SpecialStartNextBlock);
			return;
		}

		if (specialState != 1)
			return;

		spec_tpage = specialSlot;
		tpagerect.w = 64;
		tpagerect.h = 16;

		tpagerect.x = tpagepos[spec_tpage].x;
		tpagerect.y = tpagepos[spec_tpage].y + (15 - specBlocksToLoad) * 16;

		if (specBlocksToLoad == 15) 
			update_slotinfo(specTpages[GameLevel][specspooldata[2]-1], spec_tpage, &tpagerect);

		LoadImage(&tpagerect, (u_long *)specLoadBuffer);
	}

	if (quickSpool != 1)
		DrawSyncCallback(SpecialStartNextBlock);
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

// [D] [T]
void SpecialStartNextBlock(void)
{
	char *loadaddr;
	int fileSector;
	spooledFuncPtr spoolFunc;

	loadaddr = specLoadBuffer;
	DrawSyncCallback(0);

	// if previous state blocks are fully loaded, start next state
	if (specBlocksToLoad == 0)
	{
		switch (specialState) 
		{
			case 0:
			case 1:
				specBlocksToLoad = 16;
				break;
			case 2:
			case 3:
				specBlocksToLoad = 1;
				break;
			case 4:
				specBlocksToLoad = 7;
				break;
			case 5:
			case 8:
				specBlocksToLoad = lengthLowBlock;
				break;
			case 6:
				specBlocksToLoad = lastCleanBlock;
				break;
			case 7:
				specBlocksToLoad = lengthDamBlock;
				break;
			default:
				specBlocksToLoad = 0;
		}

		specialState++;
	}

	fileSector = 0x1400 + (citystart[GameLevel] - citylumps[GameLevel][CITYLUMP_SPOOL].x / 2048) + (specspooldata[2]-1) * 42;

	switch (specialState)
	{
		case 1:
			spoolFunc = Tada;
			fileSector += (17 - specBlocksToLoad);
			break;
		case 2:
			spoolFunc = Tada;
			fileSector += (33 - specBlocksToLoad);
			break;
		case 3:
			spoolFunc = SpecClutsSpooled;
			break;
		case 4:
			fileSector += 33;
			spoolFunc = Tada;
			break;
		case 5:
			spoolFunc = CleanSpooled;
			fileSector += (41 - specBlocksToLoad);
			loadaddr = specmallocptr + (7 - specBlocksToLoad) * 2048;
			break;
		case 6:
			spoolFunc = LowSpooled;
			fileSector += ((firstLowBlock + lengthLowBlock) - specBlocksToLoad) + 34;
			loadaddr = specmallocptr + (lengthLowBlock - specBlocksToLoad) * 2048;
			break;
		case 7:
			spoolFunc = CleanModelSpooled;
			fileSector += (lastCleanBlock - specBlocksToLoad) + 34;
			break;
		case 8:
			spoolFunc = DamagedModelSpooled;
			fileSector += ((firstDamBlock + lengthDamBlock) - specBlocksToLoad) + 34;
			break;
		case 9:
			spoolFunc = LowModelSpooled;
			fileSector += ((firstLowBlock + lengthLowBlock) - specBlocksToLoad) + 34;
			break;
		default:
			if (quickSpool == 1)
			{
				specModelValid = 1;
				specialState = 0;
				quickSpool = 0;
				specSpoolComplete = 0;
				return;
			}

			specSpoolComplete = 1;
			return;
	}

	RequestSpool(3, 0, fileSector, 1, loadaddr, spoolFunc);
	specBlocksToLoad--;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckSpecialSpool()
 // line 2956, offset 0x0007d4e0
	/* begin block 1 */
		// Start line: 2958
		// Start offset: 0x0007D4E0
		// Variables:
	// 		CAR_DATA *lcp; // $a0
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

// [D] [T]
void CheckSpecialSpool(void)
{
	int ret;
	int iVar2;
	CAR_DATA *lcp;

	if (startSpecSpool != -1 && startSpecSpool+400 < CameraCnt) 
	{
		while (specSpoolComplete == 0)
		{
			SpoolSYNC();

			if (DrawSync(1) == 0)
				SpecialStartNextBlock();

			StartSpooling();
		}

		specModelValid = 1;
		specialState = 0;
		specBlocksToLoad = 0;
		specSpoolComplete = 0;
		startSpecSpool = -1;
	}

	if (allowSpecSpooling && 
		specSpoolComplete != 1 && 
		GameType != GAME_PURSUIT &&
		LoadedArea != -1 &&
		SpecialByRegion[GameLevel][LoadedArea] != MissionHeader->residentModels[4]-7) 
	{
		lcp = car_data;

		// if there are cars that still using special models, deny spooling
		do	// [A]
		{
			if (MissionHeader->residentModels[lcp->ap.model] > 4)
				return;

			lcp++;
		} while (lcp < &car_data[MAX_CARS]);


		specModelValid = 0;
		startSpecSpool = CameraCnt;

		gCarDamModelPtr[4] = NULL;
		gCarCleanModelPtr[4] = NULL;
		gCarLowModelPtr[4] = NULL;

		specspooldata[2] = SpecialByRegion[GameLevel][LoadedArea];
		MissionHeader->residentModels[4] = SpecialByRegion[GameLevel][LoadedArea] + 7;

		if (specialState == 0)
			SpecialStartNextBlock();
	}
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

// [D] [T]
void QuickSpoolSpecial(void)
{
	quickSpool = 1;
	specialState = 0;
	specBlocksToLoad = 0;

	gCarCleanModelPtr[4] = NULL;
	gCarDamModelPtr[4] = NULL;
	gCarLowModelPtr[4] = NULL;

	specspooldata[2] = MissionHeader->residentModels[4]-7;

	do {
		SpoolSYNC();
		DrawSync(0);
		SpecialStartNextBlock();
		StartSpooling();
	} while (quickSpool == 1);
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

// [D] [T]
void PrepareSecretCar(void)
{
	allowSpecSpooling = 0;
	PingOutAllSpecialCivCars();

	gCarDamModelPtr[4] = NULL;
	gCarCleanModelPtr[4] = NULL;
	gCarLowModelPtr[4] = NULL;

	specspooldata[2] = 5;
	specModelValid = 0;
	startSpecSpool = CameraCnt;
	MissionHeader->residentModels[4] = 12;
	specialState = 0;
	specBlocksToLoad = 0;
	SpecialStartNextBlock();
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

// [D] [T]
void InitSpecSpool(void)
{
	switch (gCurrentMissionNumber)
	{
		case 2: 
		case 4:
		case 6:
		case 7:
		case 10:
		case 11:
		case 12:
		case 13:
		case 16:
		case 18:
		case 19:
		case 20:
		case 24:
		case 26:
		case 27:
		case 29:
		case 30:
		case 31:
		case 33:
		case 35:
		case 38:
		case 39:
		case 40:
		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63:
		case 64:
		case 65:
		case 70:
		case 78:
		case 86:
		case 94:
		case 228:
		case 229:
		case 236:
		case 237:
		case 244:
		case 245:
		case 252:
		case 253:
		case 352:
		case 353:
		case 360:
		case 169:
		case 368:
		case 369:
		case 376:
		case 377:
		case 420:
		case 421:
		case 428:
		case 429:
		case 436:
		case 437:
		case 444:
		case 445:
		case 480:
		case 481:
		case 482:
		case 483:
		case 484:
		case 485:
		case 486:
		case 487:
		case 498:
		case 499:
		case 500:
		case 501:
		case 502:
		case 503:
		case 504:
		case 505:
			allowSpecSpooling = 0;
			break;
		default:
			allowSpecSpooling = 1;
	}

#ifndef PSX
	if(gDemoLevel || gDriver1Level)
		allowSpecSpooling = 0;
#endif

	specModelValid = 1;
	specialState = 0;
	specBlocksToLoad = 0;
	quickSpool = 0;
	specSpoolComplete = 0;
	startSpecSpool = -1;
}





