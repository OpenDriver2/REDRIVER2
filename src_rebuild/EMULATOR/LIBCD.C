#include "LIBCD.H"

#include "EMULATOR_SETUP.H"
#include "EMULATOR.H"

#include <stdio.h>
#include <string.h>

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
int sectorSize = 2352;//TODO obtain properly from cue sheet
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
	CdlFILE* cd = (CdlFILE*)param;

	CD_com = com;

	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(&cd->pos)*sectorSize, SEEK_SET);
		break;
	default:
		eprinterr("Unhandled command 0x%02X!\n", com);
		break;
	}

	return 0;
}

int CdControlB(u_char com, u_char* param, u_char* result)
{
	CdlFILE* cd = (CdlFILE*)param;

	CD_com = com;

	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(&cd->pos)*sectorSize, SEEK_SET);
		break;
	default:
		eprinterr("Unhandled command 0x%02X!\n", com);
		break;
	}

	return 0;
}

int CdControlF(u_char com, u_char * param)
{
	CdlFILE* cd = (CdlFILE*)param;

	CD_com = com;

	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(&cd->pos)*sectorSize, SEEK_SET);
		break;
	case CdlSetfilter:
		//fseek(openFile, CdPosToInt(&cd->pos) * sectorSize, SEEK_SET);
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
			comQueue[i].mode = CdlReadS;
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
            struct Sector sector;
			fread(&sector, sizeof(struct Sector), 1, openFile);

			memcpy(comQueue[i].p, &sector.data[0], 2048);
			comQueue[i].p += 2048;

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
	UNIMPLEMENTED();
	return 0;
}

int CdInit(void)
{
	memset(&comQueue, 0, sizeof(comQueue));
	currentSector = 0;
	openFile = fopen(DISC_IMAGE_FILENAME, "rb");

	if (openFile == NULL)
	{
		eprinterr("Failed to open disc image file! %s\n", DISC_IMAGE_FILENAME);
		return 0;
	}

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
