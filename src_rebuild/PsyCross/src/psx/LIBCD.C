#include "psx/libcd.h"

#include "../PsyX_main.h"
#include "../iso9660.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

#ifdef _WIN32
#include <direct.h>
#elif defined (__unix__)
#include <sys/stat.h>
#define _mkdir(str)				mkdir(str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

#if defined(__ANDROID__)///@FIXME Android include order is messed up, includes SPEC_PSXPC_N MALLOC.H rather than NDK version!
#define malloc SDL_malloc
#define free SDL_free
#endif

//-------------------------------------------------------
// Virtual stdio.h implementation

typedef struct _VFILE
{
	FILE*		fp;
	u_char*		basePtr;
	u_char*		curPtr;
	size_t		size;
} VFILE;

size_t vfread(void* _Buffer, size_t _ElementSize, size_t _ElementCount, VFILE* _Stream)
{
	if (_Stream->fp)
		return fread(_Buffer, _ElementSize, _ElementCount, _Stream->fp);

	size_t num_to_read = _ElementSize * _ElementCount;

	if ((_Stream->curPtr + num_to_read) - _Stream->basePtr > _Stream->size)
	{
		// subtract difference
		num_to_read -= ((_Stream->curPtr + num_to_read) - (_Stream->basePtr + _Stream->size));
	}

	memcpy(_Buffer, _Stream->curPtr, num_to_read);

	// don't forget to advance
	_Stream->curPtr += num_to_read;

	return _ElementCount;
}

int vfseek(VFILE* _Stream, long  _Offset, int   _Origin)
{
	if (_Stream->fp)
		return fseek(_Stream->fp, _Offset, _Origin);

	if (_Origin == SEEK_SET)
		_Stream->curPtr = _Stream->basePtr + _Offset;
	else if (_Origin == SEEK_CUR)
		_Stream->curPtr += _Offset;
	else if (_Origin == SEEK_END)
		_Stream->curPtr = _Stream->basePtr + _Stream->size + _Offset;

	return 0;
}

long vftell(VFILE* _Stream)
{
	if (_Stream->fp)
		return ftell(_Stream->fp);

	return _Stream->curPtr - _Stream->basePtr;
}

//-------------------------------------------------------

enum ReadMode
{
	RM_DATA,
	RM_XA_AUDIO
};

enum ReadMode readMode = RM_DATA;

int CD_Debug = 0;
VFILE g_imageFile = { NULL };

typedef struct commandQueue
{
	u_int mode;
	u_char* p;
	u_int processed;
	u_int count;
}commandQueue_s, *commandQueue_p;


#define COMMAND_QUEUE_SIZE 128

struct commandQueue g_cdComQueue[COMMAND_QUEUE_SIZE];
int g_cdComQueueIndex = 0;
int g_cdComQueueCount = 0;

int g_cdCurrentSector = 0;
int g_cdSectorSize = CD_SECTOR_SIZE_MODE2;	// default
int g_cdCurrentTrack = 1;					// default
int g_cdNumFrames = 0;
int g_CD_com = 0;

int g_cdReadDoneFlag = 1;

char g_cdImageBinaryFileName[2048] = { 0 };
int g_UseCDImage = 0;

int PsyX_IsCDImageInit()
{
	return g_imageFile.fp != NULL || g_imageFile.basePtr != NULL;
}

void PsyX_CDFS_Init(const char* imageFileName, int track /*= 0*/, int sectorSize /*= 0*/)
{
	g_UseCDImage = 1;

	strcpy(g_cdImageBinaryFileName, imageFileName);

	if (track > 0)
		g_cdCurrentTrack = track;
	
	if (sectorSize > 0)
		g_cdSectorSize = sectorSize;
}

void PsyX_CDFS_Init_Mem(const u_long* data, int size, int track /*= 0*/, int sectorSize /*= 0*/)
{
	g_UseCDImage = 1;

	strcpy(g_cdImageBinaryFileName, "_MEMORY");

	g_imageFile.fp = NULL;
	g_imageFile.basePtr = g_imageFile.curPtr = (u_char*)data;
	g_imageFile.size = size;

	if (track > 0)
		g_cdCurrentTrack = track;

	if (sectorSize > 0)
		g_cdSectorSize = sectorSize;
}

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

int PsyX_CD_CheckImageAvailable()
{
	if (g_UseCDImage)
	{
		if (!PsyX_IsCDImageInit())
			eprintwarn("WARNING - CD subsystem is not initialized yet!\n");
		else
			return 1;
	}

	return 0;
}

CdlFILE* CdSearchFile(CdlFILE* fp, char* name)
{
	char pathPart[16];
	int tocLocalOffset;
	TOC* toc;
	int pathOfs;
	int dirLevel;

	Sector sector;

	memset(fp, 0, sizeof(CdlFILE));

	if (!PsyX_CD_CheckImageAvailable())
		return NULL;

	assert(g_cdReadDoneFlag == 1);
	
	if (!g_cdReadDoneFlag)
	{
		// deny request
		eprintwarn("CdSearchFile called while in 'CdlReadS'\n");
		return NULL;
	}

#ifdef _DEBUG
	eprintf("CdSearchFile: %s\n", name);
#endif
	
	dirLevel = 0;
	
	// go to sector 22
	vfseek(&g_imageFile, CD_ROOT_DIRECTORY_SECTOR * g_cdSectorSize, SEEK_SET);
	vfread(&sector, sizeof(Sector), 1, &g_imageFile);
	
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
				vfseek(&g_imageFile, toc->sectorPosition[0] * g_cdSectorSize, SEEK_SET);
				vfread(&sector, sizeof(Sector), 1, &g_imageFile);

				tocLocalOffset = 0;;
				toc = (TOC*)&sector.data[tocLocalOffset];
				continue;
			}
			
			memcpy(fp->name, itemNameStr, toc->nameLength);
			
			fp->size = toc->fileSize[0];
			
			vfseek(&g_imageFile, toc->sectorPosition[0] * g_cdSectorSize, SEEK_SET);
			vfread(&sector, sizeof(Sector), 1, &g_imageFile);
			
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

	g_CD_com = com;

	if (!PsyX_CD_CheckImageAvailable())
		return 0;

	switch (com)
	{
	case CdlSetloc:
		vfseek(&g_imageFile, CdPosToInt(cd)*g_cdSectorSize, SEEK_SET);
		break;
	case CdlReadS:
	{
		unsigned int filePos = vftell(&g_imageFile);
		
		CdlLOC currentLoc;
		CdIntToPos(filePos, &currentLoc);
		
		vfseek(&g_imageFile, CdPosToInt(cd) * g_cdSectorSize, SEEK_SET);
		
		g_cdCurrentSector = CdPosToInt(cd);
		
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

	if (!PsyX_CD_CheckImageAvailable())
		return 0;

	ret = 0;

	switch (com)
	{
	case CdlSetloc:
	{
		CdlLOC* cd = (CdlLOC*)param;
		vfseek(&g_imageFile, CdPosToInt(cd) * g_cdSectorSize, SEEK_SET);
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
		g_CD_com = com;

	return ret;
}

int CdControlF(u_char com, u_char * param)
{
	// TODO: CdControlF() waits for the previous command to complete execution before issuing the new command
	
	g_CD_com = com;

	if (!PsyX_CD_CheckImageAvailable())
		return 0;

	switch (com)
	{
		case CdlSetloc:
		{
			CdlLOC* cd = (CdlLOC*)param;
			vfseek(&g_imageFile, CdPosToInt(cd) * g_cdSectorSize, SEEK_SET);
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
		if (g_cdComQueue[i].processed == 1)
		{
			g_cdComQueue[i].mode = mode;	//  CdlMode*
			g_cdComQueue[i].p = (unsigned char*)buf;
			g_cdComQueue[i].processed = 0;
			g_cdComQueue[i].count = sectors;

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
		if (g_cdComQueue[i].processed == 0)
		{
			do
			{
				if (readMode == RM_DATA)
				{
					Sector sector;

					vfread(&sector, sizeof(Sector), 1, &g_imageFile);

					memcpy(g_cdComQueue[i].p, &sector.data[0], sizeof(sector.data));
					g_cdComQueue[i].p += sizeof(sector.data);
				}
				else if (readMode == RM_XA_AUDIO)
				{
					AudioSector sector;

					vfread(&sector, sizeof(AudioSector), 1, &g_imageFile);

					memcpy(g_cdComQueue[i].p, &sector.data[0], sizeof(sector.data));
					g_cdComQueue[i].p += sizeof(sector.data);
				}
				else
				{
					assert(0);
				}
				
				if (--g_cdComQueue[i].count == 0)
					g_cdComQueue[i].processed = 1;

				// in mode 1 it doesn't wait until read is completed
				if (mode == 1)
					break;
				
			} while (g_cdComQueue[i].count > 0);
			
			// returns number of sectors remaining
			// on mode == 0 it's always greater than 0
			return g_cdComQueue[i].count;
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
	CdlLOC locP;
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
			
			CdIntToPos(g_cdCurrentSector+=20, &locP);
			result[0] = g_cdCurrentTrack;
			result[1] = 1;//index, usually 1
			result[2] = locP.minute;
			result[3] = locP.second;
			result[4] = locP.sector;
			result[5] = locP.minute + ENCODE_BCD(g_cdNumFrames);
			result[6] = locP.second + ENCODE_BCD(g_cdNumFrames);
			result[7] = locP.sector + ENCODE_BCD(g_cdNumFrames);
			
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

int OpenBinaryImageFile()
{
	// already open?
	// TODO: it has to be closed
	// FIXME: what if Psy-X users want to swap CDs?
	//if (g_UseCDImage)
	//	return 0;

	if (!g_imageFile.basePtr)
	{
		// open Binary
		g_imageFile.fp = fopen(g_cdImageBinaryFileName, "rb");

		if (!g_imageFile.fp)
		{
			eprinterr("CD image '%s' not found.\n", g_cdImageBinaryFileName);
			return 0;
		}
	}

	vfseek(&g_imageFile, 0, SEEK_END);
	unsigned int binFileLength = vftell(&g_imageFile);
	g_cdNumFrames = binFileLength / g_cdSectorSize;

	assert(g_cdNumFrames != 0);

	vfseek(&g_imageFile, 0, SEEK_SET);

	eprintinfo("Using '%s' image, sector size: %d, frames: %d\n", g_cdImageBinaryFileName, g_cdSectorSize, g_cdNumFrames);

	/*{
	 *
		Sector sector;
		fseek(g_imageFp, CD_ROOT_DIRECTORY_SECTOR * g_cdSectorSize, SEEK_SET);
		fread(&sector, sizeof(Sector), 1, g_imageFp);
		DumpFiles_r(&sector, "");
	}*/
	
	return 1;
}

// TODO: don't just rely on cue sheet
// use this https://gist.github.com/ceritium/139577 to detect Mode 1 or Mode 2
int ParseCueSheet()
{
	if(g_imageFile.basePtr || strlen(g_cdImageBinaryFileName))
	{
		OpenBinaryImageFile();
		return 1;
	}
	
	int cdMode;
	char* binFileName = NULL;
	FILE* cueFp = fopen(DISC_CUE_FILENAME, "rb");

	if (cueFp == NULL)
	{
		eprinterr("%s not found.\n", DISC_CUE_FILENAME);
		return 0;
	}

	fseek(cueFp, 0, SEEK_END);

	unsigned int cueSheetFileLength = ftell(cueFp);
	char* cueSheet = (char*)malloc(cueSheetFileLength);
	
	fseek(cueFp, 0, SEEK_SET);
	fread(cueSheet, cueSheetFileLength, 1, cueFp);

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

		g_cdCurrentTrack = atoi(string);

		string += 2;

		while (isspace(string[0]))
			string++;

		assert(!strncmp(string, "MODE", 4));
		string += 4;

		cdMode = atoi(string);
		string++;

		assert(string[0] == '/');
		string++;

		g_cdSectorSize = atoi(string);

		assert(g_cdSectorSize == CD_SECTOR_SIZE_MODE2);

		fclose(cueFp);

		// copy file name
		strcpy(g_cdImageBinaryFileName, binFileName);
		
		free(cueSheet);

		eprintinfo("CUE: '%s' is Mode %d image\n", g_cdImageBinaryFileName, cdMode);
		
		OpenBinaryImageFile();
	}

	return 1;
}

int CdInit(void)
{
	g_cdCurrentSector = 0;

	if(g_UseCDImage)
	{
		//Read the cue sheet and obtain properties from it.
		if (!ParseCueSheet())
			return 0;
	}
	else
	{
		// TODO: explicitly PC FS or CD DRIVE?
	}

	memset(&g_cdComQueue, 0, sizeof(g_cdComQueue));
	for (int i = 0; i < COMMAND_QUEUE_SIZE; i++)
		g_cdComQueue[i].processed = 1;

	return 1;
}

int CdLastCom(void)
{
	return g_CD_com;
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
	return (void*)_eCdDataCallback(func);
}

int CdDiskReady(int mode)
{
	//PSYX_UNIMPLEMENTED();
	return CdlComplete;
}

//--------------------------------------------------------------------------------

CdlDataCB g_dataCallback = NULL;
CdlCB g_readyCallback = NULL;

//char g_cdSectorData[SECTOR_SIZE * 4] = { 0 };

Sector g_cdSectorData;

int g_isCdSectorDataRead = 0;

#ifndef __EMSCRIPTEN__
SDL_Thread* g_cdSpoolerPCThread = NULL;
SDL_mutex* g_cdSpoolerMutex = NULL;

#define CD_LOCK_MUTEX()			SDL_LockMutex(g_cdSpoolerMutex)
#define CD_UNLOCK_MUTEX()		SDL_UnlockMutex(g_cdSpoolerMutex)

#else

#define CD_LOCK_MUTEX()
#define CD_UNLOCK_MUTEX()

#endif // __EMSCRIPTEN__

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
	g_isCdSectorDataRead = 1;
}

CdlDataCB _eCdDataCallback(CdlDataCB cb)
{
	CdlDataCB old = g_dataCallback;
	CD_LOCK_MUTEX();
	g_dataCallback = cb;
	CD_UNLOCK_MUTEX();
	return old;
}

CdlCB _eCdReadyCallback(CdlCB cb)
{
	CdlCB old = g_readyCallback;
	
	CD_LOCK_MUTEX();
	g_readyCallback = cb;
	CD_UNLOCK_MUTEX();

	return old;
}

int _eCdSpoolerFunc()
{
	static u_char zero_bytes[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

	CdlCB readyCb;
	CdlDataCB dataCb;

	CD_LOCK_MUTEX();

	if (g_cdSpoolerSeekCmd != 0)
	{
		int sector = g_cdSpoolerSeekCmd;

		if (sector == -1)
		{
			eprintinfo("CD: 'CdlPause'\n");

			g_cdSpoolerSeekCmd = 0;
			g_cdReadDoneFlag = 1;
		}
		else
		{
			eprintinfo("CD: 'CdlReadS' at %d\n", sector);

			// seek
			vfseek(&g_imageFile, sector * g_cdSectorSize, SEEK_SET);
			g_cdSpoolerSeekCmd = 0;
		}
	}

	dataCb = g_dataCallback;
	readyCb = g_readyCallback;

	CD_UNLOCK_MUTEX();

	// clear sector before proceed
	memset(&g_cdSectorData, 0, sizeof(g_cdSectorData));
	vfread(&g_cdSectorData, sizeof(Sector), 1, &g_imageFile);

	g_isCdSectorDataRead = 0;

	if (readyCb)
	{
		readyCb(1, zero_bytes);

		if (g_isCdSectorDataRead && dataCb)
			dataCb();
	}
	else
		return 0;

	return 1;
}

// Main spooler thread function
int _eCdSpoolerThreadFunc(void* data)
{
	//Print incoming data
	eprintwarn("Running CD thread...\n");

	g_cdReadDoneFlag = 0;
	g_isCdSectorDataRead = 0;

	do
	{
		if (_eCdSpoolerFunc() == 0)
			break;
	} while (!g_cdReadDoneFlag);

	eprintinfo("CD thread work done.\n");

	return 0;
}

#ifdef __EMSCRIPTEN__
volatile int g_emCDSpoolerRunning = 0;

EM_BOOL emCDSpoolerCallback(double time, void* userData)
{
	int result;

	result = _eCdSpoolerFunc();

	if (result == 0)
	{
		eprintinfo("CD thread work done.\n");
		g_emCDSpoolerRunning = 0;
		return EM_FALSE;
	}

	return EM_TRUE;
}
#endif

//-----------------------------------------------------
// reads sector from LEV file
//-----------------------------------------------------
void _eCdControlF_ReadS(int sector)
{
#ifdef __EMSCRIPTEN__
	g_cdSpoolerSeekCmd = sector;

	if (g_cdReadDoneFlag)
	{
		while (g_emCDSpoolerRunning)
		{
			emscripten_sleep(0);
		}
	}

	//Print incoming data
	if (g_emCDSpoolerRunning == 0)
	{
		g_emCDSpoolerRunning = 1;
		eprintwarn("Running CD thread...\n");

		g_cdReadDoneFlag = 0;
		g_isCdSectorDataRead = 0;

		emscripten_set_timeout_loop(emCDSpoolerCallback, 1.0, NULL);
	}
#else
	if (!g_cdSpoolerMutex)
		g_cdSpoolerMutex = SDL_CreateMutex();

	CD_LOCK_MUTEX();
	g_cdSpoolerSeekCmd = sector;
	CD_UNLOCK_MUTEX();

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
#endif // EMSCRIPTEN
}

void _eCdControlF_Pause()
{
	g_cdSpoolerSeekCmd = -1;
}