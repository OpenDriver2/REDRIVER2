#include "driver2.h"

#ifndef PSX
#include <stdint.h>
#include <SDL.h>
#endif // !PSX

#include "pad.h"
#include "spool.h"
#include "map.h"
#include "system.h"
#include "main.h"
#include "xaplay.h"
#include "director.h"
#include "sound.h"
#include "texture.h"
#include "models.h"
#include "objanim.h"
#include "cars.h"
#include "cosmetic.h"
#include "denting.h"
#include "mission.h"
#include "civ_ai.h"
#include "camera.h"
#include "dr2roads.h"

struct SPOOLQ
{
	u_char type;
	u_char data;
	u_short nsectors;
	u_int sector;
	char* addr;
	void (*func)();
#ifdef _DEBUG
	const char* requestby;
	int requestbyline;
#endif
};

struct SPL_REGIONINFO
{
	u_short region_to_unpack;
	u_short target_barrel_region;
	int nsectors;
	char* cell_addr;
	char* roadm_addr;
};

struct AreaDataStr
{
	u_short gfx_offset;
	u_short model_offset;
	u_short music_offset;
	u_short ambient_offset;
	u_char model_size;
	u_char pad;
	u_char num_tpages;
	u_char ambient_size;
	u_char music_size;
	u_char music_samples_size;
	u_char music_id;
	u_char ambient_id;
};

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

typedef void(*spooledFuncPtr)();

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

int loadbank_read;
int loadbank_write;

volatile int spoolpos;
volatile int spoolpos_reading;
volatile int spoolpos_writing;

int allowSpecSpooling;
int startSpecSpool;

int unpack_roadmap_flag;
int unpack_cellptr_flag;

char *packed_cell_pointers;
SPL_REGIONINFO spool_regioninfo[8];

static int sectors_this_chunk;
static volatile int sectors_to_read;
static char *target_address;

static volatile int nTPchunks;
static volatile int nTPchunks_reading;
static volatile int nTPchunks_writing;

static volatile int ntpages;
static volatile int current_sector;
static volatile int switch_spooltype;

static volatile int endchunk;
int send_bank;
int sample_chunk;

volatile int chunk_complete;

int SpoolLumpOffset;

int new_area_location;
int LoadingArea = 0;
unsigned short *newmodels = NULL;

SPOOLQ spooldata[48];

// configure spooler
#if USE_PC_FILESYSTEM

#define SIMPLE_SPOOL
extern int gContentOverride;
#endif

#if defined(_DEBUG) || defined(PSX)
#define SPOOL_INFO printInfo
#define SPOOL_WARNING printWarning
#define SPOOL_ERROR printError
#else
#define SPOOL_INFO
#define SPOOL_WARNING
#define SPOOL_ERROR
#endif

// [D] [T]
int check_regions_present(void)
{
	int x, z;
	int region_to_unpack;
	int num_regions_to_unpack;
	int leftright_unpack;
	int topbottom_unpack;
	int retval;
	AREA_LOAD_INFO regions_to_unpack[3];

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

		if (region_x < regions_across)
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

		region_to_unpack = current_region + x + z * regions_across;

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
		if (new_area_location == 0)
		{
			if (current_barrel_region_zcell > 26)
				retval++;
		}
		else if (new_area_location == 1)
		{
			if (current_barrel_region_xcell > 26)
				retval++;
		}
		else if (new_area_location == 2)
		{
			if (current_barrel_region_xcell < 6)
				retval++;
		}
		else if(new_area_location == 3)
		{
			if(current_barrel_region_zcell < 6)
				retval++;
		}
	}

	return retval;
}

// [D] [T]
void stopgame(void)
{
	StopPadVibration(0);
	StopPadVibration(1);
	PauseSFX();
	DrawSync(0);
	PutDrawEnv(&last->draw);
}

// [D] [T]
void startgame(void)
{
	PutDrawEnv(&current->draw);
	UnPauseSFX();
}

int bCdIconSetup = 0;
POLY_FT4 cd_sprite;
extern u_short cd_icon[288];

// [D] [T]
void InitCdIcon(void)
{
	ushort* palette;
	RECT16 rect;

	palette = cd_icon + 10;

	for (int i = 0; i < 14; i++)
	{
		*palette &= 0x7fff;
		palette++;
	}

	cd_icon[10] = 0;

	rect.x = 960;
	rect.y = 434;
	rect.w = 8;
	rect.h = 32;

	cd_icon[24] |= 0x8000;
	cd_icon[25] |= 0x8000;

	LoadImage(&rect, (u_long*)(cd_icon + 24));

	setPolyFT4(&cd_sprite);
	setRGB0(&cd_sprite, 128, 128, 128);
	setUVWH(&cd_sprite, 0, 179, 32, 31);
	setXYWH(&cd_sprite, 80, 38, 38, 21);
	setClut(&cd_sprite, 960, 433);
	setTPage(&cd_sprite, 0, 0, 960, 256);

	bCdIconSetup = 1;
}

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

	setRECT(&dest, 960, 433, 16, 1);
	LoadImage(&dest, (u_long*)(cd_icon + 10));

	DrawPrim(&cd_sprite);
	DrawSync(0);
}

// [D] [T]
#ifdef _DEBUG
void _RequestSpool(int type, int data, int offset, int loadsize, char *address, spooledFuncPtr func, const char* requestby, int line)
#define RequestSpool(type, data, offset, loadsize, loadaddr, func) _RequestSpool(type, data, offset, loadsize, loadaddr, func, __FUNCTION__, __LINE__)
#else
void RequestSpool(int type, int data, int offset, int loadsize, char *address, spooledFuncPtr func)
#endif // _DEBUG
{
	if (!(spoolcounter < 48))
		trap(0x400);

	SPOOLQ *next;

	next = &spooldata[spoolcounter];

	next->type = type;
	next->data = data;
	next->sector = (SpoolLumpOffset / CDSECTOR_SIZE) + offset;
	next->nsectors = loadsize;
	next->addr = address;
	next->func = func;

#if 0
	char* nameType;
	switch (next->type)
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
	
	SPOOL_WARNING("spool type=%s cb=%d sec=%d cnt=%d id=%d\n", nameType, next->func ? 1 : 0, next->sector, next->nsectors, spoolcounter);
#endif
	
#ifdef _DEBUG
	next->requestby = requestby;
	next->requestbyline = line;
#endif // _DEBUG

	spoolcounter++;
}

// [D] [T]
void InitSpooling(void)
{
	for (int i = 0; i < 4; i++)
	{
		loading_region[i] = -1;
		ClearRegion(i);
	}

	CleanSpooledModelSlots();
	InitCdIcon();

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
	unpack_cellptr_flag = 0;
}

int tsetinfo[32];

// [D] [T]
void SendTPage(void)
{
	unsigned char old;
	u_int*clutptr;
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

			clutptr = (u_int*)(texture_cluts[tpage2send]);
			i = 0;

			while (i < npalettes)
			{
				clutptr[0] = getClut(cluts.x + 16, cluts.y) << 0x10 | getClut(cluts.x, cluts.y);
				clutptr[1] = getClut(cluts.x + 48, cluts.y) << 0x10 | getClut(cluts.x + 32, cluts.y);

				clutptr += 2;

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

#if USE_PC_FILESYSTEM
			if(gContentOverride)
			{
				// [A] try override
				LoadTPageFromTIMs(tpage2send);
			}
#endif
		}
	}

	//extern void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer);
	//Emulator_SaveVRAM("VRAM_CLUTS_TPAGES.TGA", 0, 0, 1024, 512, 1);
}

// [D] [T]
void SpoolSYNC(void)
{
	do {
#ifdef __EMSCRIPTEN__
		emscripten_sleep(0);
#endif // __EMSCRIPTEN__
	} while (spoolactive != 0);
}

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

		modelpointers[model_number] = model;
		pLodModels[model_number] = model;

		lod = Low2LowerDetailTable[model_number];

		if (lod != 0xffff && lod != model_number)
			pLodModels[model_number] = modelpointers[lod];

		ProcessModel(model_number);

		if (model->instance_number == -1)
		{
			if ((uint)model->collision_block != 0)
				model->collision_block += (int)model;

			model->vertices += (int)model;
			model->normals += (int)model;
			model->point_normals += (int)model;

			InitSpooledAnimObj(model_number);
		}
		else
		{
			parentmodel = modelpointers[model->instance_number];

			if ((uint)parentmodel->collision_block != 0)
				model->collision_block = parentmodel->collision_block;

			model->vertices = parentmodel->vertices;
			model->normals = parentmodel->normals;
			model->point_normals = parentmodel->point_normals;

			InitSpooledAnimObj(parentmodel->instance_number);
		}
	
		model->poly_block += (int)model;
		addr += size + 4;
	}

	LoadingArea = 0;
}

// [D] [T]
void SetupModels(void)
{
	if (old_region == -1)
		init_spooled_models();
	else
		models_ready = 1;
}

// [D] [T]
void CheckValidSpoolData(void)
{
	if (models_ready)
		init_spooled_models();
	
	if (spoolactive && check_regions_present())
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
	// [A] this fixes spooling not activated bug (reversing bug?)
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
			LoadedArea = -1;
		else if (/*spoolptr->super_region == 0xFF ||*/ nAreas == 0)
			return;

#define BOUNDARY_MIN 15
#define BOUNDARY_MAX 17

		// check area bounds
		for (i = 0; i < nAreas; i++)
		{
			load = spoolptr->connected_areas[i] >> 6;

			if (LoadedArea != (spoolptr->connected_areas[i] & 0x3f))
			{
				new_area_location = load;

				// [A] bounds?
				if (load == 0 && (cellz > BOUNDARY_MAX))
				{
					break;
				}
				else if (load == 1 && (cellx > BOUNDARY_MAX))
				{
					break;
				}
				else if (load == 2 && (cellz < BOUNDARY_MIN))
				{
					break;
				}
				else if (load == 3 && (cellx < BOUNDARY_MIN))
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

// [D] [T]
void ClearRegion(int target_region)
{
	int *pvsptr;
	ushort *cell_ptrs_s;
	int loop;

	cell_ptrs_s = cell_ptrs + target_region * 1024;
	pvsptr = (int *)PVS_Buffers[target_region];

	for (loop = 0; loop < 1024; loop++)
	{
		*cell_ptrs_s++ = 0xffff;
		*pvsptr++ = 0;
	}

	ClearMem(PVS_Buffers[target_region]-4, pvsSize[target_region]);

	RoadMapDataRegions[target_region] = (short*)PVS_Buffers[target_region];
}

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

	D_MALLOC_BEGIN();
	model_spool_buffer = D_MALLOC(size);
	D_MALLOC_END();

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
		// FIXME: is that even correct? maybe use MAX instead?
		pvsSize[i] = pvsSizes[i] + 0x7ffU & 0xfffff800;

		D_MALLOC_BEGIN();
		alloclist = D_MALLOC(pvsSize[i]);
		D_MALLOC_END();

		PVS_Buffers[i] = alloclist + 4;		// +4 for -1 cases
	}

	int num_of_regions = getIntAdv(ptr);
	spoolinfo_offsets = (ushort*)ptr;
	ptr += sizeof(ushort) * num_of_regions;

	int spoolinfo_size = getIntAdv(ptr);
	RegionSpoolInfo = ptr;

	// [A] bug fix for VEGAS. This doesn't happen in OpenDriverEngine since region loading is better
	if (GameLevel == 2)
	{
		Spool* spoolptr;
		spoolptr = (Spool*)(RegionSpoolInfo + spoolinfo_offsets[624]);

		spoolptr->super_region = 4;
	}
}

// [D] [T]
void WaitCloseLid(void)
{
#ifdef PSX
	void (*old)();
	int loop;

	old = (void(*)())CdReadyCallback(NULL);
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

// [D] [T]
void FoundError(char *name, unsigned char intr, unsigned char *result)
{
	CdlLOC p;

	if (*result & CdlStatShellOpen)
		WaitCloseLid();

#ifdef _DEBUG
	SPOOL_ERROR("FoundError: %s, intr: %d\n", name, intr);
#endif // _DEBUG

	spoolerror = 60;

	CdIntToPos(current_sector, &p);
	CdControlF(CdlReadS, (u_char*)&p);
}

void test_changemode(void);
void changemode(SPOOLQ *current);

// [D] [T]
void data_cb_textures(void)
{
	if (chunk_complete) 
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
				if (!switch_spooltype)
				{
					CdDataCallback(NULL);

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
					changemode(&spooldata[spoolpos_writing]);
				}
			}
		}
	}
}

// [D] [T]
void ready_cb_textures(unsigned char intr, unsigned char *result)
{
	if (intr == 1)
	{
		CdGetSector(target_address, SECTOR_SIZE);

		target_address += CDSECTOR_SIZE;
		sectors_this_chunk--;
		current_sector++;
		sectors_to_read--;

		if (sectors_this_chunk == 0) 
		{
			if (nTPchunks_reading)
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
}

// [D] [T]
void ready_cb_regions(unsigned char intr, unsigned char *result)
{
	if (intr == 1) 
	{
		CdGetSector(target_address, SECTOR_SIZE);

		target_address += CDSECTOR_SIZE;
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
				sectors_this_chunk = spooldata[spoolpos_reading].nsectors;
			}
		}
	}
	else 
		FoundError("ready_cb_regions", intr, result);
}

// [D] [T]
void data_cb_regions(void)
{
	SPOOLQ* current = &spooldata[spoolpos_writing];

	if (chunk_complete) 
	{
		chunk_complete = 0;

		if (current->func != NULL)
			(current->func)();

		spoolpos_writing++;

		if (endchunk)
		{
			if (!switch_spooltype) 
			{
				CdDataCallback(NULL);

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
}


// [D] [T]
void data_cb_misc(void)
{
	SPOOLQ *current = &spooldata[spoolpos_writing];

	if (chunk_complete) 
	{
		chunk_complete = 0;

		if (current->func != NULL)
			(*current->func)();

		spoolpos_writing++;

		if (!switch_spooltype)
		{
			CdDataCallback(NULL);
			
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
			changemode(&spooldata[spoolpos_writing]);
		}
	}
}

// [D] [T]
void ready_cb_misc(unsigned char intr, unsigned char *result)
{
	if (intr == 1) 
	{
		CdGetSector(target_address, SECTOR_SIZE);

		target_address += CDSECTOR_SIZE;
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
}

// [D] [T]
void test_changemode(void)
{
	SPOOLQ *current = &spooldata[spoolpos_reading];

	if (spoolpos_reading == spoolcounter)
	{
		switch_spooltype = 0;

		CdReadyCallback(NULL);
		CdControlF(CdlPause, 0);
	}
	else if (current_sector == current->sector)
	{
		target_address = current->addr;

		switch_spooltype = 1;

		if (current->type == 0)
		{
			sectors_to_read = spool_regioninfo[spool_regionpos + 1].nsectors;
			sectors_this_chunk = (current->nsectors);

			CdReadyCallback(ready_cb_regions);
		}
		else if (current->type == 1)
		{
			sectors_to_read = 17;
			target_address += 0x4000;
			nTPchunks_reading = 0;
			nTPchunks_writing = 0;
			ntpages = tsetcounter;
			sectors_this_chunk = 1;

			CdReadyCallback(ready_cb_textures);
		}
		else if (current->type == 3)
		{
			sectors_to_read = (current->nsectors);

			CdReadyCallback(ready_cb_misc);
		}
	}
	else
	{
		switch_spooltype = 0;

		CdReadyCallback(NULL);
	}
}

// [D] [T]
void changemode(SPOOLQ *current)
{
	switch_spooltype = 0;
	endchunk = 0;

	switch (current->type)
	{
		case 0:
		{
			CdDataCallback(data_cb_regions);
			break;
		}
		case 1:
		{
			CdDataCallback(data_cb_textures);
			break;
		}
		case 3:
		{
			CdDataCallback(data_cb_misc);
			break;
		}
	}
}

// [D] [T]
void StartSpooling(void)
{
	static u_char param[8];
	static u_char result[8];
	
	if (spoolcounter == 0 || spoolactive)
		return;

	if (XAPrepared())
		return;

	param[0] = CdlModeSpeed;
	CdControlB(CdlSetmode, param, result);

	if (*result & (CdlStatError | CdlStatShellOpen))
		WaitCloseLid();
	
	spoolactive = 1;
	UpdateSpool();

	if (FastForward)
		SpoolSYNC();
}

// [D] [T] [A] - altered declaration
void unpack_cellpointers(int region_to_unpack, int target_barrel_region, char* cell_addr)
{
	ushort cell;
	ushort* short_ptr;
	ushort* source_packed_data;
	int loop;
	u_int bitpos;
	u_int pcode;

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
		pcode = (u_int)*source_packed_data;
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
		printError("BAD PACKED CELL POINTER DATA, region = %d, packtype = %d\n", region_to_unpack, packtype);

		D_CHECK_ERROR(true, "Bad cell pointer data");

		unpack_cellptr_flag = 0;
	}
}

// [D] [T]
void GotRegion(void)
{
	u_int target_barrel_reg;
	SPL_REGIONINFO* spool;

	spool = &spool_regioninfo[spool_regionpos];

	unpack_cellpointers(spool->region_to_unpack, spool->target_barrel_region, spool->cell_addr);

	target_barrel_reg = spool->target_barrel_region;
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

#if defined(SIMPLE_SPOOL)
extern char g_CurrentLevelFileName[64];
extern char* g_CurrentLevelSpoolData;

int UpdateSpoolPC(void)
{
	if (g_CurrentLevelFileName[0] == 0)
		return 0;

	// read entire spool data
	if (g_CurrentLevelSpoolData == NULL)
	{
		int SpoolLumpSize;
		SpoolLumpSize = 16 * 1024 * 1024; // allocate 16 MB of RAM for spoolable data
		g_CurrentLevelSpoolData = (char*)malloc(16 * 1024 * 1024);

		loadsectors(g_CurrentLevelSpoolData, SpoolLumpOffset / CDSECTOR_SIZE, SpoolLumpSize);
	}

	for (; spoolpos_reading < spoolcounter; spoolpos_reading++)
	{
		char* spoolDataPtr;
		SPOOLQ* current;
		current = &spooldata[spoolpos_reading];

#define SPL_READ(dest, nsectors) \
		{ \
			int readSize = (nsectors)*CDSECTOR_SIZE; \
			memcpy(dest, spoolDataPtr, readSize); \
			spoolDataPtr += readSize; \
		}

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
		spoolDataPtr = g_CurrentLevelSpoolData - SpoolLumpOffset + current->sector * CDSECTOR_SIZE;

		switch (current->type)
		{
		case 0:	// regions
		case 3: // misc
			SPL_READ(current->addr, current->nsectors);

			if (current->func)
				current->func();

			break;
		case 1:	// textures

			// read cluts
			nTPchunks = 0;
			SPL_READ(current->addr + CDSECTOR_SIZE * 2 * 4, 1);
			SendTPage();

			nTPchunks++;

			// read tpage (4 sectors 4 times = 16)
			for (int i = 0; i < 4; i++)
			{
				SPL_READ(current->addr + (loadbank_write & 1U) * 256 * 32, 4);
				SendTPage();

				nTPchunks++;
			}

			break;
		default:
			break;
		}

#undef SPL_READ
	}

	spoolcounter = 0;
	spoolpos_reading = 0;
	spoolactive = 0;

	return 1;
}
#endif

// [D] [T]
void UpdateSpool(void)
{
	CdlLOC pos;
	SPOOLQ* current;

#if defined(SIMPLE_SPOOL)
	if (UpdateSpoolPC())
		return;
#endif

	if (XAPrepared())
		return;

	current = &spooldata[spoolpos_reading];
	target_address = current->addr;

	if (current->type == 0) // SPOOLTYPE_REGIONS
	{
		sectors_this_chunk = current->nsectors;
		sectors_to_read = spool_regioninfo[spool_regionpos].nsectors;

		CdDataCallback(data_cb_regions);
		CdReadyCallback(ready_cb_regions);
	}
	else if (current->type == 1) // SPOOLTYPE_TEXTURES
	{
		nTPchunks_reading = 0;
		nTPchunks_writing = 0;
		sectors_to_read = 17;
		ntpages = tsetcounter;
		sectors_this_chunk = 1;

		CdDataCallback(data_cb_textures);
		CdReadyCallback(ready_cb_textures);

		target_address += 0x4000;
	}
	else if (current->type == 3)  // SPOOLTYPE_MISC
	{
		sectors_to_read = (current->nsectors);

		CdDataCallback(data_cb_misc);
		CdReadyCallback(ready_cb_misc);
	}

	current_sector = current->sector;
	endchunk = 0;
	switch_spooltype = 0;

	// run sector reading
	CdIntToPos(current_sector, &pos);
	CdControlF(CdlReadS, (u_char*)&pos);
}

// [D] [T]
int LoadRegionData(int region, int target_region)
{
	char *cell_buffer;
	ushort spofs;
	int offset;
	Spool *spoolptr;
	char *roadmap_buffer;	// D1 leftover?

	roadmap_buffer = NULL; // [A]

	spofs = spoolinfo_offsets[region];

	if (spofs == 0xFFFF)	// has region offset?
		return 0;

	loading_region[target_region] = region;
	cell_buffer = packed_cell_pointers;
	spoolptr = (Spool *)(RegionSpoolInfo + spofs);

	offset = spoolptr->offset;

#ifndef PSX
	if (gDemoLevel)
	{
		RequestSpool(0, 0, offset, spoolptr->roadm_size, PVS_Buffers[target_region], NULL);
		offset += spoolptr->roadm_size;

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[1], cell_buffer, NULL);
		offset += spoolptr->cell_data_size[1];

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[0], (char *)(cells + cell_slots_add[target_region]), NULL);
		offset += spoolptr->cell_data_size[0];

		RequestSpool(0, 0, offset, spoolptr->cell_data_size[2], (char *)(cell_objects + num_straddlers + cell_objects_add[target_region]), GotRegion);
		offset += spoolptr->cell_data_size[2];
	}
	else
#endif
	{
		RequestSpool(0, 0, offset, spoolptr->cell_data_size[1], cell_buffer, NULL);
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

int RoadMapRegions[4];

// [D] [T]
void UnpackRegion(int region_to_unpack, int target_barrel_region)
{
	if (loading_region[target_barrel_region] != -1)
	{
		return;
	}

	if (LoadRegionData(region_to_unpack, target_barrel_region))
		spool_regioncounter++;

	regions_unpacked[target_barrel_region] = region_to_unpack;
	RoadMapRegions[target_barrel_region] = region_to_unpack;
}


//---------------------------------------------------------------------

void SpecialStartNextBlock(void);

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

#if USE_PC_FILESYSTEM
		if (gContentOverride)
		{
			// [A] try override
			LoadTPageFromTIMs(tpage);
		}
#endif
	}

	if (quickSpool != 1)
		DrawSyncCallback(SpecialStartNextBlock);
}

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
	while (loadaddr < (int*)(specLoadBuffer + CDSECTOR_SIZE))
		*modelMemory++ = *loadaddr++;

	mem = (int*)((int)gCarCleanModelPtr[4] + gCarCleanModelPtr[4]->poly_block);	// [A] pls check, might be invalid

	if (specBlocksToLoad == 0 || mem < modelMemory)
	{
#if USE_PC_FILESYSTEM
		if (gContentOverride)
		{
			// [A] vertices
			LoadCarModelFromFile((char*)gCarCleanModelPtr[4], MissionHeader->residentModels[4], CAR_MODEL_CLEAN);
		}
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
	while (loadaddr < (int*)(specLoadBuffer + CDSECTOR_SIZE))
		*modelMemory++ = *loadaddr++;

	mem = (int*)((int)gCarDamModelPtr[4] + gCarDamModelPtr[4]->poly_block);	// [A] pls check, might be invalid

	if (specBlocksToLoad == 0 || mem < modelMemory)
	{
#if USE_PC_FILESYSTEM
		if (gContentOverride)
		{
			// [A] vertices
			LoadCarModelFromFile((char*)gCarDamModelPtr[4], MissionHeader->residentModels[4], CAR_MODEL_DAMAGED);
		}
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
	while (loadaddr < (int*)(specLoadBuffer + CDSECTOR_SIZE))
		*modelMemory++ = *loadaddr++;

	mem = (int*)((int)gCarLowModelPtr[4] + gCarLowModelPtr[4]->poly_block);	// [A] pls check, might be invalid

	if (specBlocksToLoad == 0 || mem < modelMemory)
	{
#if USE_PC_FILESYSTEM
		if (gContentOverride)
		{
			// [A] vertices
			LoadCarModelFromFile((char*)gCarLowModelPtr[4], MissionHeader->residentModels[4], CAR_MODEL_LOWDETAIL);
		}
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

	if (quickSpool != 1)
		DrawSyncCallback(SpecialStartNextBlock);
}


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

		lastCleanBlock = size_1 + CDSECTOR_SIZE + 11;
		lastCleanBlock >>= 11;

		firstDamBlock = size_1 + 12;
		firstDamBlock >>= 11;

		firstLowBlock = size_1 + size_2 + 12;
		firstLowBlock >>= 11;

		int lastDamBlock = size_1 + size_2 + CDSECTOR_SIZE + 11;
		lastDamBlock >>= 11;

		lengthDamBlock = lastDamBlock - firstDamBlock;
		damOffset = size_1 - (firstDamBlock * CDSECTOR_SIZE - 12);

		int lastLowBlock = size_1 + size_2 + size_3 + CDSECTOR_SIZE + 11;
		lastLowBlock >>= 11;

		lengthLowBlock = lastLowBlock - firstLowBlock;
		lowOffset = size_1 + size_2 - (firstLowBlock * CDSECTOR_SIZE - 12);
	}

	model = (MODEL *)(specmallocptr + 12);

	if (specBlocksToLoad == 7-lastCleanBlock) 
	{
#if USE_PC_FILESYSTEM
		if (gContentOverride)
		{
			// [A] vertices
			LoadCarModelFromFile((char*)model, MissionHeader->residentModels[4], CAR_MODEL_CLEAN);
		}
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


// [D] [T]
void LowSpooled(void)
{
	MODEL *model;

	if (specBlocksToLoad == 0) 
	{
		model = (MODEL *)(specmallocptr + lowOffset);

#if USE_PC_FILESYSTEM
		if (gContentOverride)
		{
			// [A] vertices
			LoadCarModelFromFile((char*)model, MissionHeader->residentModels[4], CAR_MODEL_LOWDETAIL);
		}
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
	}
	else
	{
		if (specialState > 2) 
		{
			if (specialState != 4)
				return;

			SetupSpecCosmetics(specLoadBuffer);
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

	fileSector = 0x1400 + (citystart[GameLevel] - SpoolLumpOffset / CDSECTOR_SIZE) + (specspooldata[2]-1) * 42;

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
			loadaddr = specmallocptr + (7 - specBlocksToLoad) * CDSECTOR_SIZE;
			break;
		case 6:
			spoolFunc = LowSpooled;
			fileSector += ((firstLowBlock + lengthLowBlock) - specBlocksToLoad) + 34;
			loadaddr = specmallocptr + (lengthLowBlock - specBlocksToLoad) * CDSECTOR_SIZE;
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
	if(gDemoLevel)
		allowSpecSpooling = 0;
#endif

	specModelValid = 1;
	specialState = 0;
	specBlocksToLoad = 0;
	quickSpool = 0;
	specSpoolComplete = 0;
	startSpecSpool = -1;
}





