#include "LIBCD.H"

#include "EMULATOR_SETUP.H"
#include "EMULATOR.H"

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

enum ReadMode
{
	RM_DATA,
	RM_XA_AUDIO
};

enum ReadMode readMode = RM_DATA;

int CD_Debug = 0;

FILE* openFile = NULL;

typedef struct commandQueue
{
	unsigned int mode;
	unsigned char* p;
	unsigned int processed;
	unsigned int count;
}commandQueue_s, *commandQueue_p;

#define COMMAND_QUEUE_SIZE 128

struct commandQueue comQueue[COMMAND_QUEUE_SIZE];
int comQueueIndex = 0;
int comQueueCount = 0;
int currentSector = 0;
int sectorSize = 0;
int currentTrack = 0;
int numFrames = 0;
int CD_com = 0;

#pragma pack(push, 1)
struct TOC
{
	unsigned char tocEntryLength;
	unsigned char extEntryLength;
	unsigned int sectorPosition[2];
	unsigned int fileSize[2];
	unsigned char date[7];
	unsigned char flags;
	unsigned char fileUnitSize;
	unsigned char interleaveGapSize;
	unsigned short volSeqNum[2];
	unsigned char nameLength;
};

struct Sector
{
	unsigned char	sync[12];	/// Sync pattern (usually 00 FF FF FF FF FF FF FF FF FF FF 00)
	unsigned char	addr[3];	/// Sector address (see below for encoding details)
	unsigned char	mode;		/// Mode (usually 2 for Mode 2 Form 1/2 sectors)
	unsigned char	subHead[8];	/// Sub-header (00 00 08 00 00 00 08 00 for Form 1 data sectors)
	unsigned char	data[2048];	/// Data (form 1)
	unsigned char	edc[4];		/// Error-detection code (CRC32 of data area)
	unsigned char	ecc[276];	/// Error-correction code (uses Reed-Solomon ECC algorithm)
};

struct AudioSector
{
	unsigned char	sync[12];	/// Sync pattern (usually 00 FF FF FF FF FF FF FF FF FF FF 00)
	unsigned char	addr[3];	/// Sector address (a 24-bit big-endian integer. starts at 200, 201 an onwards)
	unsigned char	mode;		/// Mode (usually 2 for Mode 2 Form 1/2 sectors)
	unsigned char	data[2336];	/// 8 bytes Subheader, 2324 bytes Data (form 2), and 4 bytes ECC
};
#pragma pack(pop)

CdlFILE* CdSearchFile(CdlFILE* fp, char* name)
{
	memset(fp, 0, sizeof(CdlFILE));

	if (name[0] == '\\')
	{
		name++;
	}

	if (openFile != NULL)
	{
		fseek(openFile, 22 * sectorSize, SEEK_SET);

		int tocLocalOffset = 0;
        struct Sector sector;
		fread(&sector, sizeof(struct Sector), 1, openFile);
        struct TOC* toc = (struct TOC*)&sector.data[0];
		while (toc->tocEntryLength != 0)
		{
			if (strcmp((char*)&sector.data[tocLocalOffset + sizeof(struct TOC)], name) == 0)
			{
				memcpy(&fp->name[0], (char*)&sector.data[tocLocalOffset + sizeof(struct TOC)], strlen(name));
				fp->size = toc->fileSize[0];
				fseek(openFile, toc->sectorPosition[0] * sectorSize, SEEK_SET);
				fread(&sector, sizeof(struct Sector), 1, openFile);
				fp->pos.minute = sector.addr[0];
				fp->pos.second = sector.addr[1];
				fp->pos.sector = sector.addr[2];


#if _DEBUG
				eprintf("Found %s\n", name);
#endif
				return fp;
			}
			tocLocalOffset += toc->tocEntryLength;
			toc = (struct TOC*)&sector.data[tocLocalOffset];
		}
	}

	return NULL;
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

	if (openFile == NULL)
	{
		return 0;
	}

	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(cd)*sectorSize, SEEK_SET);
		break;
	case CdlReadS:
	{
		unsigned int filePos = ftell(openFile);
		CdlLOC currentLoc;
		CdIntToPos(filePos, &currentLoc);
		fseek(openFile, CdPosToInt(cd) * sectorSize, SEEK_SET);
		currentSector = CdPosToInt(cd);
		if (cd->sector != currentLoc.sector)
		{
			return 1;
		}
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
	CD_com = com;

	switch (com)
	{
	case CdlSetloc:
	{
		CdlLOC* cd = (CdlLOC*)param;
		fseek(openFile, CdPosToInt(cd) * sectorSize, SEEK_SET);
		readMode = RM_DATA;
		break;
	}
	case CdlSetfilter:
	{
		CdlFILTER* cdf = (CdlFILTER*)param;
		//TODO Set channel
		break;
	}
	default:
		eprinterr("Unhandled command 0x%02X!\n", com);
		break;
	}

	return 0;
}

int CdControlF(u_char com, u_char * param)
{
	CD_com = com;

	switch (com)
	{
	case CdlSetloc:
	{
		CdlLOC* cd = (CdlLOC*)param;
		fseek(openFile, CdPosToInt(cd) * sectorSize, SEEK_SET);
		break;
	}
	case CdlSetfilter:
	{
		CdlFILTER* cdf = (CdlFILTER*)param;
		//TODO Set channel
		break;
	}
	case CdlGetlocP:
		readMode = RM_XA_AUDIO;
		break;
	default:
		eprinterr("Unhandled command 0x%02X!\n", com);
		break;
	}

	return 0;
}

int CdPosToInt(CdlLOC* p)
{
	return (75 * (60 * DECODE_BCD(p->minute) + DECODE_BCD(p->second))) + DECODE_BCD(p->sector) - 150;
}

int CdRead(int sectors, u_long* buf, int mode)
{
	for (int i = 0; i < COMMAND_QUEUE_SIZE; i++)
	{
		if (comQueue[i].processed == 1)
		{
			comQueue[i].mode = CdlReadS;///@TODO really mode
			comQueue[i].p = (unsigned char*)buf;
			comQueue[i].processed = 0;
			comQueue[i].count = sectors;
			break;
		}
	}
	return 0;
}

int CdReadSync(int mode, u_char* result)
{
	for (int i = 0; i < COMMAND_QUEUE_SIZE; i++)
	{
		if (comQueue[i].processed == 0)
		{
			if (readMode == RM_DATA)
			{
				struct Sector sector;
				fread(&sector, sizeof(struct Sector), 1, openFile);

				memcpy(comQueue[i].p, &sector.data[0], sizeof(sector.data));
				comQueue[i].p += sizeof(sector.data);
			}
			else if (readMode == RM_XA_AUDIO)
			{
				struct AudioSector sector;
				fread(&sector, sizeof(struct AudioSector), 1, openFile);

				memcpy(comQueue[i].p, &sector.data[0], sizeof(sector.data));
				comQueue[i].p += sizeof(sector.data);
			}
			else
			{
				assert(FALSE);
			}

			if (--comQueue[i].count == 0)
			{
				comQueue[i].processed = 1;
				break;
			}

			return 1;
		}
	}
	return 0;
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
		assert(FALSE);
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

int ParseCueSheet()
{
	char* binFileName = NULL;
	openFile = fopen(DISC_IMAGE_FILENAME, "rb");

	if (openFile == NULL)
	{
		eprinterr("Failed to open disc image file! %s\n", DISC_IMAGE_FILENAME);
		return 0;
	}

	fseek(openFile, 0, SEEK_END);
	unsigned int cueSheetFileLength = ftell(openFile);
	char* cueSheet = (char*)malloc(cueSheetFileLength);
	fseek(openFile, 0, SEEK_SET);
	fread(cueSheet, cueSheetFileLength, 1, openFile);

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

		assert(!strncmp(string, "MODE1", 5));
		string += 5;

		assert(string[0] == '/');
		string++;

		sectorSize = atoi(string);

		assert(sectorSize == 2352);

		fclose(openFile);
		openFile = fopen(binFileName, "rb");
		fseek(openFile, 0, SEEK_END);
		unsigned int binFileLength = ftell(openFile);
		numFrames = binFileLength / sectorSize;
		assert(numFrames != 0);
		fseek(openFile, 0, SEEK_SET);
		free(cueSheet);
	}

	return 1;
}

int CdInit(void)
{
	currentSector = 0;

	//Read the cue sheet and obtain properties from it.
	if (!ParseCueSheet())
	{
		eprinterr("Failed to read cue sheet!");
		return 0;
	}

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
	PSYX_UNIMPLEMENTED();
	return 0;
}

CdlCB CdReadyCallback(CdlCB func)
{
	PSYX_UNIMPLEMENTED();
	return func;
}

void* CdDataCallback(void(*func)())
{
	PSYX_UNIMPLEMENTED();
	return NULL;
}

int CdDiskReady(int mode)
{
	PSYX_UNIMPLEMENTED();
	return NULL;
}