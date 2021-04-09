#include "LIBCD.H"

#include "../PSYX_SETUP.H"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

#if defined(__ANDROID__)///@FIXME Android include order is messed up, includes SPEC_PSXPC_N MALLOC.H rather than NDK version!
#define malloc SDL_malloc
#define free SDL_free
#endif

#define CD_ROOT_DIRECTORY_SECTOR	22
#define CD_SECTOR_SIZE				2048
#define CD_SECTOR_SIZE_MODE2		2352		// MODE2/2352

enum ReadMode
{
	RM_DATA,
	RM_XA_AUDIO
};

enum ReadMode readMode = RM_DATA;

int CD_Debug = 0;

FILE* g_imageFp = NULL;

typedef struct commandQueue
{
	u_int mode;
	u_char* p;
	u_int processed;
	u_int count;
}commandQueue_s, *commandQueue_p;

#define COMMAND_QUEUE_SIZE 128

struct commandQueue comQueue[COMMAND_QUEUE_SIZE];
int comQueueIndex = 0;
int comQueueCount = 0;
int currentSector = 0;
int g_sectorSize = 0;
int currentTrack = 0;
int numFrames = 0;
int CD_com = 0;

#pragma pack(push, 1)
struct TOC
{
	u_char tocEntryLength;
	u_char extEntryLength;
	u_int sectorPosition[2];
	u_int fileSize[2];
	u_char date[7];
	u_char flags;
	u_char fileUnitSize;
	u_char interleaveGapSize;
	u_short volSeqNum[2];
	u_char nameLength;
};

struct Sector
{
	u_char	sync[12];	/// Sync pattern (usually 00 FF FF FF FF FF FF FF FF FF FF 00)
	u_char	addr[3];	/// Sector address (see below for encoding details)
	u_char	mode;		/// Mode (usually 2 for Mode 2 Form 1/2 sectors)
	u_char	subHead[8];	/// Sub-header (00 00 08 00 00 00 08 00 for Form 1 data sectors)
	u_char	data[2048];	/// Data (form 1)
	u_char	edc[4];		/// Error-detection code (CRC32 of data area)
	u_char	ecc[276];	/// Error-correction code (uses Reed-Solomon ECC algorithm)
};

struct AudioSector
{
	u_char	sync[12];	/// Sync pattern (usually 00 FF FF FF FF FF FF FF FF FF FF 00)
	u_char	addr[3];	/// Sector address (a 24-bit big-endian integer. starts at 200, 201 an onwards)
	u_char	mode;		/// Mode (usually 2 for Mode 2 Form 1/2 sectors)
	u_char	data[2336];	/// 8 bytes Subheader, 2324 bytes Data (form 2), and 4 bytes ECC
};
#pragma pack(pop)


// utility function
int GetCurrentDirName(char* dest, char* src)
{
	char* str;

	str = dest;
	
	// start with folders
	strncpy(str, src, 16);
	
	while (*str)
	{
		if (*str == '\\')
		{
			*str = 0;
			break;
		}
		str++;
	}

	return str - dest;
}

//----------------------------------------------------------

typedef void(*CdlDataCB)(void);

void _eCdGetSector(char* dest, int count);
CdlDataCB _eCdDataCallback(CdlDataCB cb);
CdlCB _eCdReadyCallback(CdlCB cb);

void _eCdControlF_ReadS(int sector);
void _eCdControlF_Pause();

//----------------------------------------------------------

CdlFILE* CdSearchFile(CdlFILE* fp, char* name)
{
	char pathPart[16];
	int tocLocalOffset;
	TOC* toc;
	int pathOfs;
	int dirLevel;

	Sector sector;

	memset(fp, 0, sizeof(CdlFILE));

	if (g_imageFp == NULL)
	{
		eprintwarn("WARNING - CD subsystem is not initialized yet!\n");
		return NULL;
	}

#ifdef _DEBUG
	eprintf("CdSearchFile: %s\n", name);
#endif
	
	dirLevel = 0;
	
	// go to sector 22
	fseek(g_imageFp, CD_ROOT_DIRECTORY_SECTOR * g_sectorSize, SEEK_SET);
	fread(&sector, sizeof(Sector), 1, g_imageFp);
	
	toc = (TOC*)&sector.data[0];
	tocLocalOffset = 0;

	if (name[0] == '\\')
		name++;

	pathOfs = GetCurrentDirName(pathPart, name);

	while (toc->tocEntryLength != 0)
	{
		char* itemNameStr = (char*)&sector.data[tocLocalOffset + sizeof(TOC)];

		// skip . and .. for now
		if (*itemNameStr == 0 || *itemNameStr == 1)
		{
			tocLocalOffset += toc->tocEntryLength;
			toc = (TOC*)&sector.data[tocLocalOffset];
			
			continue;
		}
		
		if (!strcmp(itemNameStr, pathPart))
		{
			if(toc->flags & 2) // is directory
			{
				// get next directory name
				pathOfs += GetCurrentDirName(pathPart, name + pathOfs + 1) + 1;

				// read the needed sector with directory contents
				dirLevel++;
				fseek(g_imageFp, toc->sectorPosition[0] * g_sectorSize, SEEK_SET);
				fread(&sector, sizeof(Sector), 1, g_imageFp);

				tocLocalOffset = 0;;
				toc = (TOC*)&sector.data[tocLocalOffset];
				continue;
			}
			
			memcpy(fp->name, itemNameStr, toc->nameLength);
			
			fp->size = toc->fileSize[0];
			
			fseek(g_imageFp, toc->sectorPosition[0] * g_sectorSize, SEEK_SET);
			fread(&sector, sizeof(struct Sector), 1, g_imageFp);
			
			fp->pos.minute = sector.addr[0];
			fp->pos.second = sector.addr[1];
			fp->pos.sector = sector.addr[2];

#if _DEBUG
			eprintf("Found\n");
#endif
			return fp;
		}

		tocLocalOffset += toc->tocEntryLength;
		toc = (TOC*)&sector.data[tocLocalOffset];
	}

	return NULL;
}

int CdReadFile(char* file, u_long* addr, int nbyte)
{
	CdlFILE fp;

	if (CdSearchFile(&fp, file) != NULL)
	{
		int nSectors;
		nSectors = (fp.size / (SECTOR_SIZE * 4)) + 1;
		
		CdControlB(CdlSetloc, (u_char*)&fp.pos, NULL);
		CdRead(nSectors, (u_long*)addr, 0);

		if (nbyte == 0)
			nbyte = fp.size;

		return nbyte;
	}

	return -1;
}

CdlLOC* CdIntToPos(int i, CdlLOC* p)
{
	i += 150;
	p->sector = ENCODE_BCD(i % 75);
	int rem = i / 75;
	p->second = ENCODE_BCD(rem % 60);
	p->minute = ENCODE_BCD(rem / 60);
	return p;
}

int CdControl(u_char com, u_char * param, u_char * result)
{
	CdlLOC* cd = (CdlLOC*)param;

	CD_com = com;

	if (g_imageFp == NULL)
		return 0;

	switch (com)
	{
	case CdlSetloc:
		fseek(g_imageFp, CdPosToInt(cd)*g_sectorSize, SEEK_SET);
		break;
	case CdlReadS:
	{
		unsigned int filePos = ftell(g_imageFp);
		
		CdlLOC currentLoc;
		CdIntToPos(filePos, &currentLoc);
		
		fseek(g_imageFp, CdPosToInt(cd) * g_sectorSize, SEEK_SET);
		
		currentSector = CdPosToInt(cd);
		
		if (cd->sector != currentLoc.sector)
			return 1;

		break;
	}
	default:
		eprinterr("Unhandled command 0x%02X!\n", com);
		break;
	}

	return 0;
}

int CdControlB(u_char com, u_char* param, u_char* result)
{
	int ret;

	ret = 0;

	switch (com)
	{
	case CdlSetloc:
	{
		CdlLOC* cd = (CdlLOC*)param;
		fseek(g_imageFp, CdPosToInt(cd) * g_sectorSize, SEEK_SET);
		readMode = RM_DATA;
		ret = 1;
		break;
	}
	case CdlSetfilter:
	{
		CdlFILTER* cdf = (CdlFILTER*)param;
		// TODO: set channel. Primarily used for CDDA/XA
		break;
	}
	case CdlSetmode:
	{
		// TODO: CdlModeSize0 and CdlModeSize1 can change things

		eprinterr("Unimplemented 'CdlSetmode'!\n");

		ret = 1;
		break;
	}
	default:
		eprinterr("Unhandled command 0x%02X!\n", com);
		break;
	}

	if(ret)
		CD_com = com;

	return ret;
}

int CdControlF(u_char com, u_char * param)
{
	// TODO: CdControlF() waits for the previous command to complete execution before issuing the new command
	
	CD_com = com;

	switch (com)
	{
		case CdlSetloc:
		{
			CdlLOC* cd = (CdlLOC*)param;
			fseek(g_imageFp, CdPosToInt(cd) * g_sectorSize, SEEK_SET);
			break;
		}
		case CdlSetfilter:
		{
			CdlFILTER* cdf = (CdlFILTER*)param;
			
			// TODO: set channel. Primarily used for CDDA/XA
			
			break;
		}
		case CdlGetlocP:
		{
			readMode = RM_XA_AUDIO;
			break;
		}
		case CdlReadS:
		{
			// start reading sectors
			CdlLOC* cd = (CdlLOC*)param;
			_eCdControlF_ReadS(CdPosToInt(cd));
			
			break;
		}
		case CdlPause:
		{
			// pause thread
			_eCdControlF_Pause();
			break;
		}
		default:
		{
			eprinterr("Unhandled command 0x%02X!\n", com);
			break;
		}
	}

	return 0;
}

int CdPosToInt(CdlLOC* p)
{
	return (75 * (60 * DECODE_BCD(p->minute) + DECODE_BCD(p->second))) + DECODE_BCD(p->sector) - 150;
}

int CdRead(int sectors, u_long* buf, int mode)
{
	int ret;

	ret = 0;

	for (int i = 0; i < COMMAND_QUEUE_SIZE; i++)
	{
		if (comQueue[i].processed == 1)
		{
			comQueue[i].mode = mode;	//  CdlMode*
			comQueue[i].p = (unsigned char*)buf;
			comQueue[i].processed = 0;
			comQueue[i].count = sectors;

			ret = 1;
			break;
		}
	}

	if(ret == 0)
		eprinterr("out of command queue\n");

	return ret;
}

int CdReadSync(int mode, u_char* result)
{
	int i;

	for (i = 0; i < COMMAND_QUEUE_SIZE; i++)
	{
		if (comQueue[i].processed == 0)
		{
			do
			{
				if (readMode == RM_DATA)
				{
					Sector sector;

					fread(&sector, sizeof(Sector), 1, g_imageFp);

					memcpy(comQueue[i].p, &sector.data[0], sizeof(sector.data));
					comQueue[i].p += sizeof(sector.data);
				}
				else if (readMode == RM_XA_AUDIO)
				{
					AudioSector sector;

					fread(&sector, sizeof(AudioSector), 1, g_imageFp);

					memcpy(comQueue[i].p, &sector.data[0], sizeof(sector.data));
					comQueue[i].p += sizeof(sector.data);
				}
				else
				{
					assert(0);
				}
				
				if (--comQueue[i].count == 0)
					comQueue[i].processed = 1;

				// in mode 1 it doesn't wait until read is completed
				if (mode == 1)
					break;
				
			} while (comQueue[i].count > 0);
			
			// returns number of sectors remaining
			// on mode == 0 it's always greater than 0
			return comQueue[i].count;
		}
	}

	return -1;
}

int CdSetDebug(int level)
{
	int lastLevel = CD_Debug;
	CD_Debug = level;
	return lastLevel;
}

int CdSync(int mode, u_char * result)
{
	CdlLOC* loc = (CdlLOC*)result;
	switch (mode)
	{
	case 0:
		PSYX_UNIMPLEMENTED();
		assert(0);
		break;
	case 1:

		switch (CdLastCom())
		{
		case CdlGetlocP:
			CdlLOC locP;
			CdIntToPos(currentSector+=20, &locP);
			result[0] = currentTrack;
			result[1] = 1;//index, usually 1
			result[2] = locP.minute;
			result[3] = locP.second;
			result[4] = locP.sector;
			result[5] = locP.minute + ENCODE_BCD(numFrames);
			result[6] = locP.second + ENCODE_BCD(numFrames);
			result[7] = locP.sector + ENCODE_BCD(numFrames);
			
			//Dirty, for now read the audio data
			if (readMode == RM_XA_AUDIO)
			{
				char xaAudioData[2336];
				CdRead(1, (unsigned long*)&xaAudioData[0], CdlReadS);
				CdReadSync(CdlReadS, NULL);

				//Sector should be read now
				xaAudioData[0] = 0;
			}

			break;
		}
		return CdlComplete;
		break;
	}

	return 0;
}

// TODO: don't rely on cue sheet
// use this https://gist.github.com/ceritium/139577 to detect Mode 1 or Mode 2

int ParseCueSheet()
{
	int cdMode;
	char* binFileName = NULL;
	g_imageFp = fopen(DISC_IMAGE_FILENAME, "rb");

	if (g_imageFp == NULL)
	{
		eprinterr("%s not found.\n", DISC_IMAGE_FILENAME);
		return 0;
	}

	fseek(g_imageFp, 0, SEEK_END);

	unsigned int cueSheetFileLength = ftell(g_imageFp);
	char* cueSheet = (char*)malloc(cueSheetFileLength);
	
	fseek(g_imageFp, 0, SEEK_SET);
	fread(cueSheet, cueSheetFileLength, 1, g_imageFp);

	//Null terminated
	char* string = &cueSheet[0];
	if (!strncmp(string, "FILE", 4))
	{
		//Read the binary name since it's a file
		string += 5;
		if (isspace(string[0]))
		{
			string++;
		}

		//Get file name length
		char* afterFileName = string;
		char fileNameLength = 0;
		//While
		while (!isspace(afterFileName[0]))
		{
			afterFileName++;
			fileNameLength++;
		}

		if (string[0] == '"')
		{
			string[fileNameLength - 1] = 0;
			string++;
		}

		binFileName = string;
		string = afterFileName;

		if (isspace(string[0]))
			string++;

		/* Get Type of BIN file */
		assert(!strncmp(string, "BINARY", 6));
		string += 6;

		while (isspace(string[0]))
			string++;

		/* Get Track of BIN file */
		assert(!strncmp(string, "TRACK", 5));
		string += 5;

		while (isspace(string[0]))
			string++;

		currentTrack = atoi(string);

		string += 2;

		while (isspace(string[0]))
			string++;

		assert(!strncmp(string, "MODE", 4));
		string += 4;

		cdMode = atoi(string);
		string++;

		assert(string[0] == '/');
		string++;

		g_sectorSize = atoi(string);

		assert(g_sectorSize == CD_SECTOR_SIZE_MODE2);

		fclose(g_imageFp);
		g_imageFp = fopen(binFileName, "rb");

		eprintinfo("CUE: '%s' is Mode %d image\n", binFileName, cdMode);

		if (!g_imageFp)
		{
			eprinterr("%s not found.\n", binFileName);
			free(cueSheet);
			return 0;
		}

		fseek(g_imageFp, 0, SEEK_END);
		unsigned int binFileLength = ftell(g_imageFp);
		numFrames = binFileLength / g_sectorSize;
		
		assert(numFrames != 0);

		fseek(g_imageFp, 0, SEEK_SET);
		free(cueSheet);
	}

	return 1;
}

int CdInit(void)
{
	currentSector = 0;

	//Read the cue sheet and obtain properties from it.
	if (!ParseCueSheet())
		return 0;

	memset(&comQueue, 0, sizeof(comQueue));
	for (int i = 0; i < COMMAND_QUEUE_SIZE; i++)
	{
		comQueue[i].processed = 1;
	}

	return 1;
}

int CdLastCom(void)
{
	return CD_com;
}

int CdGetSector(void *madr, int size)
{
	_eCdGetSector((char*)madr, size);
	return 1;
}

CdlCB CdReadyCallback(CdlCB func)
{
	return _eCdReadyCallback(func);
}

void* CdDataCallback(void(*func)())
{
	return _eCdDataCallback(func);
}

int CdDiskReady(int mode)
{
	//PSYX_UNIMPLEMENTED();
	return CdlComplete;
}

//--------------------------------------------------------------------------------

#include <assert.h>

CdlDataCB g_dataCallback = NULL;
CdlCB g_readyCallback = NULL;

//char g_cdSectorData[SECTOR_SIZE * 4] = { 0 };

Sector g_cdSectorData;

bool g_isCdSectorDataRead = false;
bool g_cdReadDoneFlag = false;

SDL_Thread* g_cdSpoolerPCThread = NULL;
SDL_mutex* g_cdSpoolerMutex = NULL;
volatile int g_cdSpoolerSeekCmd = 0;

//-----------------------------------------------------
// copies read sector data to addr
//-----------------------------------------------------
void _eCdGetSector(char* dest, int count)
{
	count *= 4;

	assert(count <= SECTOR_SIZE * 4);
	assert(dest);

	memcpy(dest, g_cdSectorData.data, count);
	g_isCdSectorDataRead = true;
}

CdlDataCB _eCdDataCallback(CdlDataCB cb)
{
	CdlDataCB old = g_dataCallback;
	SDL_LockMutex(g_cdSpoolerMutex);
	g_dataCallback = cb;
	SDL_UnlockMutex(g_cdSpoolerMutex);
	return old;
}

CdlCB _eCdReadyCallback(CdlCB cb)
{
	CdlCB old = g_readyCallback;
	
	SDL_LockMutex(g_cdSpoolerMutex);
	g_readyCallback = cb;
	SDL_UnlockMutex(g_cdSpoolerMutex);

	return old;
}

// Main spooler thread function
int _eCdSpoolerThreadFunc(void* data)
{
	//Print incoming data
	eprintwarn("Running CD thread...\n");

	g_cdReadDoneFlag = false;
	g_isCdSectorDataRead = false;

	CdlCB readyCb = g_readyCallback;
	CdlDataCB dataCb = g_dataCallback;

	do
	{
		SDL_LockMutex(g_cdSpoolerMutex);

		if (g_cdSpoolerSeekCmd != 0)
		{
			int sector = g_cdSpoolerSeekCmd;

			if (sector == -1)
			{
				eprintinfo("CD: 'CdlPause'\n", sector);

				g_cdSpoolerSeekCmd = 0;
				g_cdReadDoneFlag = true;
			}
			else
			{
				eprintinfo("CD: 'CdlReadS' at %d\n", sector);

				// seek
				fseek(g_imageFp, sector * g_sectorSize, SEEK_SET);
				g_cdSpoolerSeekCmd = 0;
			}
		}

		dataCb = g_dataCallback;
		readyCb = g_readyCallback;

		SDL_UnlockMutex(g_cdSpoolerMutex);

		// clear sector before proceed
		memset(&g_cdSectorData, 0, sizeof(g_cdSectorData));
		fread(&g_cdSectorData, sizeof(Sector), 1, g_imageFp);

		g_isCdSectorDataRead = false;

		if (readyCb)
		{
			readyCb(1, { 0x0 });

			if (g_isCdSectorDataRead && dataCb)
				dataCb();
		}
		else
			break;

	} while (!g_cdReadDoneFlag);

	eprintinfo("CD thread work done.\n");

	return 0;
}

//-----------------------------------------------------
// reads sector from LEV file
//-----------------------------------------------------
void _eCdControlF_ReadS(int sector)
{
	if (!g_cdSpoolerMutex)
		g_cdSpoolerMutex = SDL_CreateMutex();

	SDL_LockMutex(g_cdSpoolerMutex);
	g_cdSpoolerSeekCmd = sector;
	SDL_UnlockMutex(g_cdSpoolerMutex);

	if (g_cdSpoolerPCThread && g_cdReadDoneFlag)
	{
		int returnValue;
		SDL_WaitThread(g_cdSpoolerPCThread, &returnValue);

		g_cdSpoolerPCThread = NULL;
	}

	if (!g_cdSpoolerPCThread)
	{
		g_cdSpoolerPCThread = SDL_CreateThread(_eCdSpoolerThreadFunc, "CDSpooler", NULL);

		if (NULL == g_cdSpoolerPCThread)
		{
			eprinterr("SDL_CreateThread failed: %s\n", SDL_GetError());
		}
	}
}

void _eCdControlF_Pause()
{
	g_cdSpoolerSeekCmd = -1;
}