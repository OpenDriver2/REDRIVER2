#include "../PSYX_SETUP.H"
#include "libmcrd.h"
#include <stdio.h>
#include <string.h>

#define MC_HEADER_FRAME_INDEX (0)

#pragma pack(push,1)
typedef struct MemoryCardFrame
{
	unsigned int attr;
	unsigned int size;
	unsigned short unknown;
	char name[20];
	char padding[98];
} MemoryCardFrame_s, *MemoryCardFrame_p;
#pragma pack(pop)

int bIsInitialised = 0;
int bCanUseMemoryCardFuncs = 0;
int memoryCardStatus = -1;

FILE* memoryCards[2];
int memoryCardsNew[2];

int memoryCardCmds = -1;
int memoryCardResult = -1;
int openFrameIndex = 0;
int currentlyOpenedMemoryCard = -1;

void MemCardInit(long val)
{
	bIsInitialised = 1;
	bCanUseMemoryCardFuncs = 0;
	memoryCardStatus = -1;
	memoryCardCmds = -1;
	memoryCardResult = -1;
	memoryCardsNew[0] = 1;
	memoryCardsNew[1] = 1;
}

void MemCardEnd()
{
	if (!bCanUseMemoryCardFuncs)
		return;

}

void MemCardStart()
{
	bCanUseMemoryCardFuncs = 1;
}

void MemCardStop()
{
	if (!bCanUseMemoryCardFuncs)
		return;

	bCanUseMemoryCardFuncs = 0;
	memoryCardStatus = -1;
	memoryCardCmds = -1;
	memoryCardResult = -1;
	memoryCardsNew[0] = 1;
	memoryCardsNew[1] = 1;

	if (memoryCards[0] != NULL)
	{
		fclose(memoryCards[0]);
	}

	if (memoryCards[1] != NULL)
	{
		fclose(memoryCards[1]);
	}
}

long MemCardExist(long chan)
{
	if (!bCanUseMemoryCardFuncs)
		return 0;

	char buf[16];
	sprintf(&buf[0], "%ld.MCD", chan);
	memoryCards[chan] = fopen(&buf[0], "rb");

	memoryCardCmds = McFuncExist;

	if (memoryCards[chan] == NULL)
	{
		memoryCardStatus = -1;//CHECKME
		memoryCardResult = McErrCardNotExist;//CHECKME
		return 0;
	}
	else
	{
		fclose(memoryCards[chan]);

		if (memoryCardResult == McErrNewCard)
		{
			memoryCardResult = McErrNone;
			memoryCardStatus = 0;
		}
		else
		{
			memoryCardResult = McErrNewCard;
			memoryCardStatus = 1;
		}
	}

	
	return 1;
}

long MemCardAccept(long chan)
{
	if (!bCanUseMemoryCardFuncs)
		return 0;

	char buf[16];
	sprintf(&buf[0], "%ld.MCD", chan);
	memoryCards[chan] = fopen(&buf[0], "rb");
	memoryCardCmds = McFuncAccept;

	unsigned int fileMagic = 0;
	fread(&fileMagic, 4, 1, memoryCards[chan]);
	fclose(memoryCards[chan]);

	//Is this card formatted?
	if (fileMagic != 0x0000434D)
	{
		//If not, this is a new card!
		memoryCardResult = McErrNewCard;
		memoryCardsNew[chan] = 0;
		return 0;
	}

	memoryCardResult = 3;
	memoryCardStatus = 1;
	return 1;
}
long MemCardOpen(long chan, char* file, long flag)
{
	if (!bCanUseMemoryCardFuncs)
		return 0;

	char buf[16];
	sprintf(&buf[0], "%ld.MCD", chan);

	switch (flag)
	{
	case 1:
		memoryCards[chan] = fopen(&buf[0], "rb");
		break;
	case 2://Unchecked
		memoryCards[chan] = fopen(&buf[0], "wb");
		break;
	}
	
	fseek(memoryCards[chan], 0, SEEK_SET);
	currentlyOpenedMemoryCard = chan;

	for (int i = 0; i < 16; i++)
	{
		struct MemoryCardFrame frame;
		fread(&frame, sizeof(struct MemoryCardFrame), 1, memoryCards[chan]);

		if (i > MC_HEADER_FRAME_INDEX && frame.name[0] != '\0')
		{
			if (strcmp(&frame.name[0], file) == 0)
			{
				break;
			}

			openFrameIndex += frame.attr & 0x7;
		}
	}

	return 0;
}

void MemCardClose()
{
	openFrameIndex = -1;
	fclose(memoryCards[currentlyOpenedMemoryCard]);
}

long MemCardReadData(unsigned long* adrs, long ofs, long bytes)
{
	memoryCardCmds = McFuncReadData;
	if (bytes % 128)
	{
		return 0;
	}

	fseek(memoryCards[currentlyOpenedMemoryCard], (64 * 128) + (openFrameIndex * 16384) + ofs, SEEK_SET);
	fread(adrs, bytes, 1, memoryCards[currentlyOpenedMemoryCard]);

	return 1;
}

long MemCardReadFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
	memoryCardCmds = McFuncReadFile;
	return 0;
}

long MemCardWriteData(unsigned long* adrs, long ofs, long bytes)
{
	memoryCardCmds = McFuncWriteData;
	return 0;
}

long MemCardWriteFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
	memoryCardCmds = McFuncWriteFile;

	return 0;
}

long MemCardCreateFile(long chan, char* file, long blocks)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long MemCardDeleteFile(long chan, char* file)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long MemCardFormat(long chan)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long MemCardUnformat(long chan)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long MemCardSync(long mode, long* cmds, long* rslt)
{
	static int timesCalled = 0;

	//if (timesCalled++ >= 4) //Doesn't work o.o
	{
		timesCalled = 0;

		if (memoryCardCmds != -1)
		{
			*cmds = memoryCardCmds;
		}

		if (memoryCardResult != -1)
		{
			*rslt = memoryCardResult;
		}

		if (mode == 1)
		{
			return memoryCardStatus;
		}
	}

	return -1;
}

MemCB MemCardCallback(MemCB func)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long MemCardGetDirentry(long chan, char* name, struct DIRENTRY* dir, long* files, long ofs, long max)
{
	char buf[16];
	sprintf(&buf[0], "%ld.MCD", chan);
	memoryCards[chan] = fopen(&buf[0], "rb");///@FIXME potential bug, if this is called twice then we can open a card twice. Maybe add a flag for whether memcard is open or not if original SDK did this.
	fseek(memoryCards[chan], 0, SEEK_SET);

	if (strcmp(name, "*") == 0)
	{
		for (int i = 0, head = -64; i < 16; i++, head += 128)
		{
			struct MemoryCardFrame frame;
			fread(&frame, sizeof(struct MemoryCardFrame), 1, memoryCards[chan]);

			if (i > MC_HEADER_FRAME_INDEX && frame.name[0] != '\0')
			{
				memcpy(dir->name, &frame.name[0], 20);
				dir->attr = frame.attr & 0xF0;
				dir->size = frame.size;
				dir->next = (struct DIRENTRY*)9;
				dir->head = head;
				dir->system[0] = 9;
				dir++;
				files[0]++;
			}
		}
	}
	memoryCardCmds = McFuncExist;
	memoryCardResult = 0;
	memoryCardStatus = 1;

	return 0;
}
