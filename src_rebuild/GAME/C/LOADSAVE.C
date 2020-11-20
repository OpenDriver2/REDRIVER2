#include "DRIVER2.H"
#include "LOADSAVE.H"
#include "REPLAYS.H"
#include "SYSTEM.H"
#include "GLAUNCH.H"
#include "STRINGS.H"
#include "FMVPLAY.H"
#include "SOUND.H"
#include "PAD.H"
#include "MISSION.H"
#include "SCORES.H"
#include "LIBGPU.H"
#include "LIBETC.H"
#include "E3STUFF.H"
#include "PRES.H"
#include "PAUSE.H"

#ifndef PSX
#include <stdlib.h>
#include <PLATFORM.H>

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
	Emulator_BeginScene();
	SetDispMask(1);
#endif

	gShowMap = 1;
	PrintStringCentred(message, 128 + height);
	gShowMap = 0;

	VSync(0);

#ifndef PSX
	Emulator_EndScene();
	Emulator_WaitForTimestep(40);
#endif // PSX
}

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

// [A] loads current game config
void LoadCurrentProfile()
{
	char filePath[2048];
	int fileSize;
	int error;

	GetGameProfilePath(filePath);

	strcat(filePath, "/config.dat");

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
	ShowSavingWaitMessage("Loading configuration...", 0);

	{
		RECT16 rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 320;
		rect.h = 512;

		ClearImage(&rect, 0, 0, 0);
		DrawSync(0);
	}

	error = 1;

	// load config
	FILE* fp = fopen(filePath, "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		fread(_other_buffer, 1, fileSize, fp);

		fclose(fp);

		if (fileSize <= CalcConfigDataSize())
		{
			LoadConfigData(_other_buffer);
			error = 0;
		}
	}
	else
	{
		ShowSavingWaitMessage("No saved data", 0);
	}

	if (error)
	{
		SetTextColour(128, 0, 0);
		ShowSavingWaitMessage("Loading error", 0);
	}
	else
	{
		ShowSavingWaitMessage("OK", 0);
	}

	SetMasterVolume(gMasterVolume);
}

// [A] saves config to file
void SaveCurrentProfile()
{
	int dataSize;
	char filePath[2048];
	int error;

	GetGameProfilePath(filePath);

	strcat(filePath, "/config.dat");

	SetTextColour(128, 128, 64);
	ShowSavingWaitMessage("Saving configuration...", 0);

	dataSize = 0;
	if (SaveConfigData(_other_buffer))
		dataSize = CalcConfigDataSize();

	error = 1;

	// load config
	FILE* fp = fopen(filePath, "wb");
	if (fp)
	{
		fwrite(_other_buffer, 1, dataSize, fp);
		fclose(fp);

		error = 0;
	}

	if (error)
	{
		SetTextColour(128, 0, 0);
		ShowSavingWaitMessage("Saving error", 0);
	}
	else
	{
		ShowSavingWaitMessage("OK", 0);
	}
}

// [A] loads current game progress
int LoadCurrentGame()
{
	char filePath[2048];
	int fileSize;

	GetGameProfilePath(filePath);

	strcat(filePath, "/progress.dat");

	SetTextColour(128, 128, 64);
	ShowSavingWaitMessage("Loading progress...", 0);

	// load config
	FILE* fp = fopen(filePath, "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		fread(_other_buffer, 1, fileSize, fp);

		fclose(fp);

		if (fileSize <= CalcGameDataSize())
		{
			LoadGameData(_other_buffer);
			return 1;
		}
	}

	return 0;
}

// [A] saves current game progress
void SaveCurrentGame()
{
	int dataSize = 0;
	char filePath[2048];

	GetGameProfilePath(filePath);

	strcat(filePath, "/progress.dat");

	SetTextColour(128, 128, 64);
	ShowSavingWaitMessage("Saving progress...", 0);

	dataSize = 0;
	if (SaveGameData(_other_buffer))
		dataSize = CalcGameDataSize();

	// load config
	FILE* fp = fopen(filePath, "wb");
	if (fp)
	{
		fwrite(_other_buffer, 1, dataSize, fp);
		fclose(fp);
	}
}

int LoadReplayFromFile(char* fileName)
{
	FILE* fp = fopen(fileName, "rb");
	if (fp)
	{
		int replay_size = 0;
		fseek(fp, 0, SEEK_END);
		replay_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		fread(_other_buffer, replay_size, 1, fp);
		fclose(fp);

		if (LoadReplayFromBuffer(_other_buffer))
		{
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

#endif

// decompiled code
// original method signature: 
// int /*$ra*/ CalcReplayDataSize()
 // line 37, offset 0x00057fd4
	/* begin block 1 */
		// Start line: 39
		// Start offset: 0x00057FD4
	/* end block 1 */
	// End offset: 0x00057FF4
	// End Line: 46

	/* begin block 2 */
		// Start line: 279
	/* end block 2 */
	// End Line: 280

	/* begin block 3 */
		// Start line: 74
	/* end block 3 */
	// End Line: 75

	/* begin block 4 */
		// Start line: 280
	/* end block 4 */
	// End Line: 281

	/* begin block 5 */
		// Start line: 282
	/* end block 5 */
	// End Line: 283

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
int CalcReplayDataSize(void)
{
	return SaveReplayToBuffer(NULL);
}



// decompiled code
// original method signature: 
// int /*$ra*/ SaveReplayData(char *buffer /*$a0*/)
 // line 48, offset 0x00057ff4
	/* begin block 1 */
		// Start line: 50
		// Start offset: 0x00057FF4
	/* end block 1 */
	// End offset: 0x00058014
	// End Line: 54

	/* begin block 2 */
		// Start line: 298
	/* end block 2 */
	// End Line: 299

	/* begin block 3 */
		// Start line: 301
	/* end block 3 */
	// End Line: 302

	/* begin block 4 */
		// Start line: 302
	/* end block 4 */
	// End Line: 303

	/* begin block 5 */
		// Start line: 304
	/* end block 5 */
	// End Line: 305

// [D] [T]
int SaveReplayData(char* buffer)
{
	return SaveReplayToBuffer(buffer);
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadReplayData(char *buffer /*$a0*/)
 // line 56, offset 0x00058014
	/* begin block 1 */
		// Start line: 314
	/* end block 1 */
	// End Line: 315

	/* begin block 2 */
		// Start line: 317
	/* end block 2 */
	// End Line: 318

	/* begin block 3 */
		// Start line: 318
	/* end block 3 */
	// End Line: 319

// [D] [T]
int LoadReplayData(char* buffer)
{
	return LoadReplayFromBuffer(buffer);
}



// decompiled code
// original method signature: 
// int /*$ra*/ CalcGameDataSize()
 // line 62, offset 0x00058034
	/* begin block 1 */
		// Start line: 329
	/* end block 1 */
	// End Line: 330

	/* begin block 2 */
		// Start line: 332
	/* end block 2 */
	// End Line: 333

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
int CalcGameDataSize(void)
{
	return sizeof(GAME_SAVE_HEADER);
}



// decompiled code
// original method signature: 
// int /*$ra*/ SaveGameData(char *buffer /*$s0*/)
 // line 69, offset 0x0005803c
	/* begin block 1 */
		// Start line: 70
		// Start offset: 0x0005803C
	/* end block 1 */
	// End offset: 0x000580CC
	// End Line: 83

	/* begin block 2 */
		// Start line: 343
	/* end block 2 */
	// End Line: 344

// [D] [T]
int SaveGameData(char* buffer)
{
	GAME_SAVE_HEADER* saveHeader;

	saveHeader = (GAME_SAVE_HEADER*)buffer;

	ClearMem((char*)saveHeader, sizeof(GAME_SAVE_HEADER));

	saveHeader->magic = 0x54876421;
	saveHeader->gMissionLadderPos = gMissionLadderPos + 1;
	
	saveHeader->SavedData = MissionEndData;

	return sizeof(GAME_SAVE_HEADER);
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadGameData(char *buffer /*$a0*/)
 // line 85, offset 0x000580cc
	/* begin block 1 */
		// Start line: 86
		// Start offset: 0x000580CC
		// Variables:
	// 		GAME_SAVE_HEADER *header; // $a0
	/* end block 1 */
	// End offset: 0x00058164
	// End Line: 99

	/* begin block 2 */
		// Start line: 379
	/* end block 2 */
	// End Line: 380

	/* begin block 3 */
		// Start line: 382
	/* end block 3 */
	// End Line: 383

	/* begin block 4 */
		// Start line: 386
	/* end block 4 */
	// End Line: 387

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



// decompiled code
// original method signature: 
// int /*$ra*/ CalcConfigDataSize()
 // line 102, offset 0x00058164
	/* begin block 1 */
		// Start line: 417
	/* end block 1 */
	// End Line: 418

	/* begin block 2 */
		// Start line: 421
	/* end block 2 */
	// End Line: 422

	/* begin block 3 */
		// Start line: 424
	/* end block 3 */
	// End Line: 425

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
int CalcConfigDataSize(void)
{
	return sizeof(CONFIG_SAVE_HEADER);
}



// decompiled code
// original method signature: 
// int /*$ra*/ SaveConfigData(char *buffer /*$a0*/)
 // line 109, offset 0x00057bf0
	/* begin block 1 */
		// Start line: 110
		// Start offset: 0x00057BF0
		// Variables:
	// 		CONFIG_SAVE_HEADER *header; // $s0
	// 		int i; // $t0
	/* end block 1 */
	// End offset: 0x00057DF0
	// End Line: 138

	/* begin block 2 */
		// Start line: 218
	/* end block 2 */
	// End Line: 219

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



// decompiled code
// original method signature: 
// int /*$ra*/ LoadConfigData(char *buffer /*$a0*/)
 // line 140, offset 0x00057df0
	/* begin block 1 */
		// Start line: 141
		// Start offset: 0x00057DF0
		// Variables:
	// 		CONFIG_SAVE_HEADER *header; // $t3
	// 		int i; // $t4
	/* end block 1 */
	// End offset: 0x00057FD4
	// End Line: 168

	/* begin block 2 */
		// Start line: 307
	/* end block 2 */
	// End Line: 308

	/* begin block 3 */
		// Start line: 310
	/* end block 3 */
	// End Line: 311

	/* begin block 4 */
		// Start line: 315
	/* end block 4 */
	// End Line: 316

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





