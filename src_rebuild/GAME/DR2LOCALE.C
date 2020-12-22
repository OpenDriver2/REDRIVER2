#include "DR2LOCALE.H"

#ifndef PSX
#include <stdio.h>
#include <malloc.h>
#endif

int gUserLanguage = 0;

char* gMisssionLanguageBuffer = NULL;
char* gGameLanguageBuffer = NULL;

char* gGameLangTable[MAX_LANGUAGE_TEXT];
char* gMissionLangTable[MAX_LANGUAGE_TEXT];

char* LanguageNames[5] =
{
	"ENGLISH",
	"ITALIAN",
	"GERMAN",
	"FRENCH",
	"SPANISH",
};

#ifndef PSX
// [D] Driver 1 PC function
void InitStringMng()
{
	char filename[32];

	if (gUserLanguage < 0 || gUserLanguage >= 6)
		gUserLanguage = 0;

	sprintf(filename, "%s_GAME.LTXT", LanguageNames[gUserLanguage]);
	InitStringLanguage(filename, 0);
	
	sprintf(filename, "%s_MISSION.LTXT", LanguageNames[gUserLanguage]);
	InitStringLanguage(filename, 1);
}

void DeinitStringMng()
{
	if (gGameLanguageBuffer)
		free(gGameLanguageBuffer);

	if (gMisssionLanguageBuffer)
		free(gMisssionLanguageBuffer);

	gGameLanguageBuffer = NULL;
	gMisssionLanguageBuffer = NULL;
}

// [D] Driver 1 PC function
int InitStringLanguage(char *filename, int mission)
{
	char *buffer;
	char *cptr;
	char *ln;
	int i;
	int size;

	FILE* fp = fopen(filename, "rb");
	if(!fp)
		return -1;

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buffer = (char*)malloc(size);
	fread(buffer, 1, size, fp);
	fclose(fp);
	
	if (mission)
		gMisssionLanguageBuffer = buffer;
	else
		gGameLanguageBuffer = buffer;

	cptr = buffer;
	for (i = 0; i < MAX_LANGUAGE_TEXT; i++)
	{	
		if (size <= 0)
		{
			if (mission)
				gMissionLangTable[i] = "Mission.? missing!";
			else
				gGameLangTable[i] = "Lang.? missing!";
		}
		else
		{
			if (mission)
				gMissionLangTable[i] = cptr;
			else
				gGameLangTable[i] = cptr;

			// go to next line
			ln = cptr;
			do
			{
				if (*cptr == '\n' || *cptr == '\r')
				{
					while(*cptr == '\r')
					{
						*cptr++;
						size--;
					}
			
					break;
				}
				
				if (*cptr >= 32)
					ln = cptr + 1;
				
				size--;
				cptr++;
			} while (size > 1);
	
			*ln = 0; // zero on end of the line
			
			cptr++;
			size--;
		}
	}

	return i;
}
#endif