#include "driver2.h"
#include "loadsave.h"
#include "replays.h"
#include "system.h"
#include "glaunch.h"
#include "fmvplay.h"
#include "sound.h"
#include "pad.h"
#include "mission.h"
#include "scores.h"
#include "E3stuff.h"
#include "pres.h"
#include "pause.h"
#include "platform.h"

#ifndef PSX
#include <stdlib.h>		// getenv
#endif // PSX

// [A]
void ShowSavingWaitMessage(char *message, int height)
{
	char *filename;
	DISPENV disp;
	DRAWENV draw;

	DrawSync(0);
	VSync(0);
	SetDispMask(0);
	SetupDefDrawEnv(&draw, 0, 0, 320, 256);
	SetupDefDispEnv(&disp, 0, 0, 320, 256);

	draw.dfe = 1;

	PutDrawEnv(&draw);
	PutDispEnv(&disp);

	LoadFont(NULL);

#ifndef PSX
	PsyX_BeginScene();
	SetDispMask(1);
#endif

	gShowMap = 1;
	PrintStringCentred(message, 128 + height);
	gShowMap = 0;

	VSync(0);

#ifndef PSX
	PsyX_EndScene();
	PsyX_WaitForTimestep(40);
#endif // PSX
}

#ifndef PSX
void GetGameProfilePath(char* str)
{
	char* homepath;

	homepath = getenv(HOME_ENV); // "USERPROFILE"

	if (homepath)
	{
		strcpy(str, homepath);
		strcat(str, "/.driver2");

		// create Driver 2 home dir
		_mkdir(str);
	}
	else
	{
		str[0] = 0;
	}
}
#endif // PSX

// [A] loads current game config
void LoadCurrentProfile(int init)
{
	int error;

	if(init)
	{
		RECT16 rect;

		SetupDrawBuffers();

		rect.x = 0;
		rect.y = 0;
		rect.w = 320;
		rect.h = 512;

		ClearImage(&rect, 0, 0, 0);
		DrawSync(0);
	}

	SetTextColour(128, 128, 64);
	ShowSavingWaitMessage(G_LTXT(GTXT_LoadingConfiguration), 0);
	/*
	{
		RECT16 rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 320;
		rect.h = 512;

		ClearImage(&rect, 0, 0, 0);
		DrawSync(0);
	}
	*/
	error = 1;

#ifndef PSX

	char filePath[2048];
	int fileSize;
	
	GetGameProfilePath(filePath);
	strcat(filePath, "/config.dat");
	
	// load config
	FILE* fp = fopen(filePath, "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		fread((char*)_other_buffer, 1, fileSize, fp);

		fclose(fp);

		if (fileSize <= CalcConfigDataSize())
		{
			LoadConfigData((char*)_other_buffer);
			error = 0;
		}
	}
	else
	{
		ShowSavingWaitMessage(G_LTXT(GTXT_NoSavedData), 0);
		return;
	}
#else
	// TODO: PSX memory card code
#endif

	if (error)
	{
		SetTextColour(128, 0, 0);
		ShowSavingWaitMessage(G_LTXT(GTXT_LoadingError), 0);
	}
	else
	{
		ShowSavingWaitMessage(G_LTXT(GTXT_OK), 0);
	}

	SetMasterVolume(gMasterVolume);
}

// [A] saves config to file
void SaveCurrentProfile()
{
#ifndef PSX
	int dataSize;
	char filePath[2048];
	int error;

	GetGameProfilePath(filePath);

	strcat(filePath, "/config.dat");

	SetTextColour(128, 128, 64);
	ShowSavingWaitMessage(G_LTXT(GTXT_SavingConfiguration), 0);

	dataSize = 0;
	if (SaveConfigData((char*)_other_buffer))
		dataSize = CalcConfigDataSize();

	error = 1;

	// load config
	FILE* fp = fopen(filePath, "wb");
	if (fp)
	{
		fwrite((char*)_other_buffer, 1, dataSize, fp);
		fclose(fp);

		error = 0;
	}

	if (error)
	{
		SetTextColour(128, 0, 0);
		ShowSavingWaitMessage(G_LTXT(GTXT_SavingError), 0);
	}
	else
	{
		ShowSavingWaitMessage(G_LTXT(GTXT_OK), 0);
	}
#else
	// TODO: PSX memory card code
#endif
}

// [A] loads current game progress
int LoadCurrentGame()
{
#ifndef PSX
	char filePath[2048];
	int fileSize;

	GetGameProfilePath(filePath);

	strcat(filePath, "/progress.dat");

	SetTextColour(128, 128, 64);
	ShowSavingWaitMessage(G_LTXT(GTXT_LoadingProgress), 0);

	// load config
	FILE* fp = fopen(filePath, "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		fread((char*)_other_buffer, 1, fileSize, fp);

		fclose(fp);

		if (fileSize <= CalcGameDataSize())
		{
			LoadGameData((char*)_other_buffer);
			return 1;
		}
	}
#else
	// TODO: PSX memory card code
#endif

	return 0;
}

// [A] saves current game progress
void SaveCurrentGame()
{
#ifndef PSX
	int dataSize = 0;
	char filePath[2048];

	GetGameProfilePath(filePath);

	strcat(filePath, "/progress.dat");

	SetTextColour(128, 128, 64);
	ShowSavingWaitMessage(G_LTXT(GTXT_SavingProgress), 0);

	dataSize = 0;
	if (SaveGameData((char*)_other_buffer))
		dataSize = CalcGameDataSize();

	// load config
	FILE* fp = fopen(filePath, "wb");
	if (fp)
	{
		fwrite((char*)_other_buffer, 1, dataSize, fp);
		fclose(fp);
	}
#else
	// TODO: PSX memory card code
#endif
}

#ifndef PSX

char gCurrentReplayFilename[64] = { 0 };

int LoadReplayFromFile(char* fileName)
{
	FILE* fp = fopen(fileName, "rb");
	if (fp)
	{
		int replay_size = 0;
		fseek(fp, 0, SEEK_END);
		replay_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		fread((char*)_other_buffer, replay_size, 1, fp);
		fclose(fp);

		if (LoadReplayFromBuffer((char*)_other_buffer))
		{
			char* sub, *tmp;

			// only filename
			sub = fileName;
			do
			{
				tmp = strchr(sub+1, '/');
				if (tmp)
					sub = tmp+1;
			}while(tmp);

			strcpy(gCurrentReplayFilename, sub);

			sub = strchr(gCurrentReplayFilename, '.');
			if (sub)
				*sub = 0;

			return 1;
		}
		else
		{
			printError("Error loading replay file '%s'!\n", fileName);
		}
	}
	else
	{
		printError("Cannot open replay '%s'!\n", fileName);
		return -1;
	}

	return 0;
}

int SaveReplayToFile(char* filename)
{
	int size = SaveReplayToBuffer((char*)_other_buffer);

	FILE* fp = fopen(filename, "wb");
	if (fp)
	{
		fwrite((char*)_other_buffer, 1, size, fp);
		fclose(fp);
		return 1;
	}

	return 0;
}

#endif

// [D] [T]
int CalcReplayDataSize(void)
{
	return SaveReplayToBuffer(NULL);
}

// [D] [T]
int SaveReplayData(char* buffer)
{
	return SaveReplayToBuffer(buffer);
}


// [D] [T]
int LoadReplayData(char* buffer)
{
	return LoadReplayFromBuffer(buffer);
}

// [D] [T]
int CalcGameDataSize(void)
{
	return sizeof(GAME_SAVE_HEADER);
}

// [D] [T]
int SaveGameData(char* buffer)
{
	GAME_SAVE_HEADER* saveHeader;

	saveHeader = (GAME_SAVE_HEADER*)buffer;

	ClearMem((char*)saveHeader, sizeof(GAME_SAVE_HEADER));

	saveHeader->magic = 0x54876421;
	saveHeader->gMissionLadderPos = gMissionLadderPos;
	
	saveHeader->SavedData = MissionEndData;

	return sizeof(GAME_SAVE_HEADER);
}

// [D] [T]
int LoadGameData(char* buffer)
{
	GAME_SAVE_HEADER* header;
	
	header = (GAME_SAVE_HEADER*)buffer;

	if (header->magic != 0x54876421)
		return 0;

	gMissionLadderPos = header->gMissionLadderPos;
	gHaveStoredData = 1;

	MissionStartData = header->SavedData;

	FindPrevMissionFromLadderPos(gMissionLadderPos);

	return 1;
}

// [D] [T]
int CalcConfigDataSize(void)
{
	return sizeof(CONFIG_SAVE_HEADER);
}

// [D] [T]
int SaveConfigData(char* buffer)
{
	CONFIG_SAVE_HEADER* header;
	
	header = (CONFIG_SAVE_HEADER*)buffer;

	ClearMem((char*)buffer, sizeof(CONFIG_SAVE_HEADER));

	header->magic = 0x36132479;
	header->gMasterVolume = gMasterVolume;
	header->gMusicVolume = gMusicVolume;
	header->gSoundMode = gSoundMode;
	header->gVibration = gVibration;
	header->gCopDifficultyLevel = gCopDifficultyLevel;
	header->gFurthestMission = gFurthestMission;
	
	header->PALAdjustX = draw_mode_pal.framex;
	header->PALAdjustY = draw_mode_pal.framey;
	header->NTSCAdjustX = draw_mode_ntsc.framex;
	header->NTSCAdjustY = draw_mode_ntsc.framey;
	header->gSubtitles = gSubtitles;

	header->AvailableCheats = AvailableCheats;

	header->PadMapping[0] = Pads[0].mappings;
	header->PadMapping[1] = Pads[1].mappings;

	header->ScoreTables = ScoreTables;

	return sizeof(CONFIG_SAVE_HEADER);
}

// [D] [T]
int LoadConfigData(char* buffer)
{
	CONFIG_SAVE_HEADER* header;

	header = (CONFIG_SAVE_HEADER*)buffer;

	if (header->magic != 0x36132479)
		return 0;

	gMasterVolume = header->gMasterVolume;
	gMusicVolume = header->gMusicVolume;
	gSoundMode = header->gSoundMode;
	gVibration = header->gVibration;
	gCopDifficultyLevel = header->gCopDifficultyLevel;
	gFurthestMission = header->gFurthestMission;
	draw_mode_pal.framex = header->PALAdjustX;
	draw_mode_pal.framey = header->PALAdjustY;
	draw_mode_ntsc.framex = header->NTSCAdjustX;
	draw_mode_ntsc.framey = header->NTSCAdjustY;
	gSubtitles = header->gSubtitles;
	AvailableCheats = header->AvailableCheats;

	Pads[0].mappings = header->PadMapping[0];
	Pads[1].mappings = header->PadMapping[1];

	ScoreTables = header->ScoreTables;

	return 1;
}





