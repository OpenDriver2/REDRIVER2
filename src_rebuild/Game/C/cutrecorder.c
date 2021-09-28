#ifdef PSX
#error This file is not applicable for PSX build
#endif

#ifdef CUTSCENE_RECORDER

#include "driver2.h"
#include "cutrecorder.h"

#include "main.h"
#include "pad.h"
#include "cop_ai.h"
#include "spool.h"
#include "civ_ai.h"
#include "cutscene.h"
#include "cars.h"
#include "camera.h"
#include "glaunch.h"
#include "mission.h"
#include "replays.h"
#include "state.h"
#include "system.h"
#include "pause.h"
#include "pres.h"
#include "players.h"

#include "../utils/ini.h"

typedef struct AutoTestStats
{
	int numHitCars;
	int numHitWalls;
	int stuck;
	int saved;
};

PING_PACKET NewPingBuffer[MAX_REPLAY_PINGS];
AutoTestStats gAutoTestStats[16];				// 16th is dummy

int gCutsceneChaseAutoTest = 0;
int gChaseStuckTimer = 0;

int gCutsceneAsReplay_ReChaseLoaded = 0;
int gCutsceneAsReplay = 0;
int gCutsceneAsReplay_NumReplayStreams = 0;
int gCutsceneAsReplay_PlayerId = 0;
int gCutsceneAsReplay_PlayerChanged = 0;
int gCutsceneAsReplay_ReserveSlots = 2;
char gCutsceneRecorderPauseText[64] = { 0 };
char gCurrentChasePauseText[64] = { 0 };

extern int gDieWithFade;

int CutRec_LoadCutsceneAsReplayFromBuffer(char* buffer);
void InitCutsceneRecorder(char* configFilename);
int LoadCutsceneAsReplay(int subindex);

void CutRec_Reset()
{
	if (gCutsceneChaseAutoTest != 0 && gCutsceneChaseAutoTest < 15)
	{
		gAutoTestStats[gCutsceneChaseAutoTest].numHitCars = 0;
		gAutoTestStats[gCutsceneChaseAutoTest].numHitWalls = 0;
		gAutoTestStats[gCutsceneChaseAutoTest].stuck = 0;
		gAutoTestStats[gCutsceneChaseAutoTest].saved = 0;
		gChaseStuckTimer = 0;
		
		return;
	}

	gCutsceneChaseAutoTest = 0;
	gCutsceneAsReplay = 0;

	gCutsceneAsReplay_PlayerId = 0;
	gCutsceneAsReplay_PlayerChanged = 0;
	gCutsceneAsReplay_ReserveSlots = 2;
}

void CutRec_NextChase(int dir)
{
	if (dir > 0)
		gChaseNumber++;
	else if (dir < 0)
		gChaseNumber--;

	if (gChaseNumber < 0)
		gChaseNumber = 0;

	if (gChaseNumber > 15)
		gChaseNumber = 15;

	sprintf(gCurrentChasePauseText, "Chase ID: %d", gChaseNumber);
}

int CutRec_GotoChase(int number)
{
	if (number < 2)
		return 0;

	if (number > 15)
		return 0;
	
	gCutsceneChaseAutoTest = number;
	
	// load next replay and restart
	if (LoadCutsceneAsReplay(gCutsceneChaseAutoTest))
	{
		State_GameComplete(NULL);

		gDrawPauseMenus = 0;
		gLoadedReplay = 1;
		CurrentGameMode = GAMEMODE_REPLAY;

		SetState(STATE_GAMELAUNCH);
		
		return 1;
	}
	return 0;
}

void CutRec_Step()
{
	if (gCutsceneChaseAutoTest != 0 && CutRec_IsPlaying())
	{
		// goto previous chase
		if (Pads[0].dirnew & CAR_PAD_LEFT)
		{
			CutRec_GotoChase(gCutsceneChaseAutoTest - 1);
			return;
		}

		// goto next chase
		if (Pads[0].dirnew & CAR_PAD_RIGHT)
		{
			CutRec_GotoChase(gCutsceneChaseAutoTest + 1);
			return;
		}

		if (!pauseflag)
		{
			int carId = player[gCutsceneAsReplay_PlayerId].playerCarId;

			if (car_data[carId].hd.speed < 5)
				gChaseStuckTimer++;
			else
				gChaseStuckTimer = 0;

			if (gChaseStuckTimer > 45)
			{
				gAutoTestStats[gCutsceneChaseAutoTest].stuck = 1;
				gChaseStuckTimer = 0;
			}

			return;
		}

		if (gCutsceneChaseAutoTest < 15 &&
			(NoPlayerControl && ReplayParameterPtr->RecordingEnd - 2 < CameraCnt || gDieWithFade))
		{
			gCutsceneChaseAutoTest++;

			// load next replay and restart
			if (!CutRec_GotoChase(gCutsceneChaseAutoTest))
			{
				printInfo("------- AUTOTEST RESULTS -------\n");
				for (int i = 0; i < 15; i++)
					printInfo("  chase %d - hit cars: %d, stuck: %d\n", i, gAutoTestStats[i].numHitCars, gAutoTestStats[i].stuck);
				printInfo("------- ---------------- -------\n");
			}
		}
	}
}

void CutRec_Draw()
{
	char text[64];

	if (gCutsceneAsReplay == 0)
		return;

	SetTextColour(128, 128, 128);

	if(gCutsceneChaseAutoTest)
	{
		sprintf(text, "Auto-test - chase %d %s", gCutsceneChaseAutoTest, gAutoTestStats[gCutsceneChaseAutoTest].saved ? "-SAVED-" : "");
		PrintString(text, 5, 10);
		
		if(gCutsceneAsReplay_ReChaseLoaded)
		{
			SetTextColour(32, 128, 32);
			PrintString("Re-recorded", 5, 20);
		}
		else
		{
			SetTextColour(128, 80, 32);
			PrintString("Reflections", 5, 20);
		}

		SetTextColour(128, 128, 128);
		
		sprintf(text, "Frame %d of %d", CameraCnt, ReplayParameterPtr->RecordingEnd);
		PrintString(text, 5, 215);
	}

	if(PingBufferPos >= MAX_REPLAY_PINGS-1)
		SetTextColour(128, 0, 0);

	sprintf(text, "Pings: %d", PingBufferPos);
	PrintString(text, 5, 205);

	SetTextColour(128, 128, 128);

	if (gAutoTestStats[gCutsceneChaseAutoTest].numHitCars > 0)
		SetTextColour(128, 0, 0);		

	sprintf(text, "Hit cars: %d", gAutoTestStats[gCutsceneChaseAutoTest].numHitCars);
	PrintString(text, 120, 205);

	if(gAutoTestStats[gCutsceneChaseAutoTest].stuck)
	{
		SetTextColour(128, 0, 0);
	
		sprintf(text, "Car is stuck!");
		PrintString(text, 5, 60);
	}
}

void CutRec_ReserveSlots()
{
	if (gCutsceneAsReplay == 0)
		return;

	for (int i = 0; i < gCutsceneAsReplay_ReserveSlots; i++)
		reservedSlots[i] = 1;
}

void CutRec_HandleCarRequest()
{
	if (gCutsceneAsReplay == 0)
		return;

	requestCopCar = 0;
	allowSpecSpooling = 0;
}

void CutRec_NextPlayer(int dir)
{
	int old_player = gCutsceneAsReplay_PlayerId;

	if (dir > 0)
		gCutsceneAsReplay_PlayerId++;
	else if (dir < 0)
		gCutsceneAsReplay_PlayerId--;

	if (gCutsceneAsReplay_PlayerId >= gCutsceneAsReplay_NumReplayStreams)
		gCutsceneAsReplay_PlayerId -= gCutsceneAsReplay_NumReplayStreams;
	else if (gCutsceneAsReplay_PlayerId < 0)
		gCutsceneAsReplay_PlayerId += gCutsceneAsReplay_NumReplayStreams;

	if (old_player != gCutsceneAsReplay_PlayerId)
		gCutsceneAsReplay_PlayerChanged = 1;

	sprintf(gCutsceneRecorderPauseText, "CUTSCENE PLAYER ID: %d", gCutsceneAsReplay_PlayerId);
}

int LoadCutsceneAsReplay(int subindex)
{
	int offset;
	int size;

	if (gCutsceneAsReplay_PlayerId > 0)
		gCutsceneAsReplay_PlayerChanged = 1;

	CUTSCENE_HEADER header;
	char filename[64];

	// Try loading existing ReChase
	sprintf(filename, "REPLAYS\\ReChases\\CUT%d_N.R", gCutsceneAsReplay);

	if(!FileExists(filename))
	{
		gCutsceneAsReplay_ReChaseLoaded = 0;
		printWarning("--- NO re-recorded chases available! ---\n");
		
		if (gCutsceneAsReplay < 21)
			sprintf(filename, "REPLAYS\\CUT%d.R", gCutsceneAsReplay);
		else
			sprintf(filename, "REPLAYS\\A\\CUT%d.R", gCutsceneAsReplay);
	}
	else
	{
		gCutsceneAsReplay_ReChaseLoaded = 1;
		printInfo("--- Re-recorded chases loaded ---\n");
	}

	if (FileExists(filename))
	{
		LoadfileSeg(filename, (char*)&header, 0, sizeof(CUTSCENE_HEADER));

		if (header.data[subindex].offset != 0xffff)
		{
			offset = header.data[subindex].offset * 4;
			size = header.data[subindex].size;

			LoadfileSeg(filename, (char*)_other_buffer, offset, size);

			int result = CutRec_LoadCutsceneAsReplayFromBuffer((char*)_other_buffer);

			return result;
		}
	}

	printError("Invalid cutscene subindex or mission!\n");

	return 0;
}

void InitChaseAutoTest(char* configFilename)
{
	gCutsceneChaseAutoTest = 2;
	InitCutsceneRecorder(configFilename);
}

void InitCutsceneRecorder(char* configFilename)
{
	ini_t* config;
	int loadExistingCutscene;
	int subindex;

	config = ini_load(configFilename);

	if (!config)
	{
		printError("Unable to open '%s'!\n", configFilename);
		return;
	}

	//const char* stream = ini_get(config, "fs", "dataFolder");

	loadExistingCutscene = 0;
	ini_sget(config, "settings", "loadExistingCutscene", "%d", &loadExistingCutscene);
	ini_sget(config, "settings", "mission", "%d", &gCutsceneAsReplay);
	ini_sget(config, "settings", "baseMission", "%d", &gCurrentMissionNumber);
	ini_sget(config, "settings", "player", "%d", &gCutsceneAsReplay_PlayerId);
	ini_sget(config, "settings", "reserveSlots", "%d", &gCutsceneAsReplay_ReserveSlots);
	ini_sget(config, "settings", "subindex", "%d", &subindex);

	// totally limited by streams
	if (gCutsceneAsReplay_ReserveSlots > 8)
		gCutsceneAsReplay_ReserveSlots = 8;

	if (loadExistingCutscene)
	{
		if(gCutsceneChaseAutoTest != 0)
		{
			subindex = gCutsceneChaseAutoTest;
		}
		
		if (!LoadCutsceneAsReplay(subindex))
		{
			ini_free(config);

			gLoadedReplay = 0;
			gCutsceneAsReplay = 0;
			return;
		}

		gCutsceneAsReplay_NumReplayStreams = NumReplayStreams;

		gLoadedReplay = 1;
		CurrentGameMode = GAMEMODE_REPLAY;
	}
	else
	{
		int i;
		char curStreamName[40];
		STREAM_SOURCE* stream;

		InitPadRecording();

		ini_sget(config, "settings", "streams", "%d", &gCutsceneAsReplay_NumReplayStreams);

		// initialize all streams
		for (i = 0; i < gCutsceneAsReplay_NumReplayStreams; i++)
		{
			stream = &ReplayStreams[i].SourceType;
			sprintf(curStreamName, "stream%d", i);

			stream->position.vy = 0;

			ini_sget(config, curStreamName, "type", "%hhd", &stream->type);
			ini_sget(config, curStreamName, "model", "%hhd", &stream->model);
			ini_sget(config, curStreamName, "palette", "%hhd", &stream->palette);
			ini_sget(config, curStreamName, "controlType", "%hhd", &stream->controlType);
			ini_sget(config, curStreamName, "startRot", "%d", &stream->rotation);
			ini_sget(config, curStreamName, "startPosX", "%d", &stream->position.vx);
			ini_sget(config, curStreamName, "startPosY", "%d", &stream->position.vy);
			ini_sget(config, curStreamName, "startPosZ", "%d", &stream->position.vz);
		}
	}

	GameType = GAME_TAKEADRIVE;
	CameraCnt = 0;
	ini_free(config);

	CutRec_NextChase(0);
	CutRec_NextPlayer(0);

	SetState(STATE_GAMELAUNCH);
}

// [A] Stores ping info into replay buffer
int CutRec_StorePingInfo(int cookieCount, int carId)
{
	PING_PACKET* buffer;
	PING_PACKET* packet;

	if (!CutRec_IsRecording())
		return 0;

	if (PingBufferPos < MAX_REPLAY_PINGS-1)
	{
		packet = &NewPingBuffer[PingBufferPos++];
		packet->frame = CameraCnt - frameStart;
		packet->carId = carId;

		packet->cookieCount = cookieCount;

		PingBuffer[PingBufferPos - 1] = *packet;

		// always finalize last ping
		packet = &NewPingBuffer[PingBufferPos];
		packet->frame = 0xffff;
		packet->carId = -1;
		packet->cookieCount = -1;

		

		return 1;
	}

	return 0;
}

void CutRec_CheckInvalidatePing(int carId, int howHard)
{
	int pos;

	if (gCutsceneAsReplay == 0)
		return;

	if (howHard < 60000)
		return;

	gAutoTestStats[gCutsceneChaseAutoTest].numHitCars++;

	pos = PingBufferPos;

	while (pos >= 0)
	{
		pos--;
		if (PingBuffer[pos].carId == carId)
		{
			printWarning("Removing ping at %d\n", PingBuffer[pos].frame);
			PingBuffer[pos].carId = -1;
			NewPingBuffer[pos].carId = -1;

			PingOutCar(&car_data[carId]);
			break;
		}
	}
}

int CutRec_InitPlayers()
{
	STREAM_SOURCE* temp;
	if (gCutsceneAsReplay == 0)
		return 0;

	for (int i = 0; i < gCutsceneAsReplay_NumReplayStreams; i++)
	{
		PlayerStartInfo[i] = &ReplayStreams[i].SourceType;
		PlayerStartInfo[i]->controlType = CONTROL_TYPE_CUTSCENE;
	}

	temp = PlayerStartInfo[0];
	PlayerStartInfo[0] = PlayerStartInfo[gCutsceneAsReplay_PlayerId];
	PlayerStartInfo[gCutsceneAsReplay_PlayerId] = temp;
	
	PlayerStartInfo[0]->controlType = CONTROL_TYPE_PLAYER;

	NumReplayStreams = gCutsceneAsReplay_NumReplayStreams;
	numPlayersToCreate = gCutsceneAsReplay_NumReplayStreams;

	return 1;
}

int CutRec_InitMission(char* filename)
{
	int header;

	if (gCutsceneAsReplay == 0)
		return 0;
	
	LoadfileSeg(filename, (char*)&header, gCutsceneAsReplay * 4, 4);

	if (header == 0)
		return 0;

	// load some data from target cutscene mission
	MS_MISSION missionTempHeader;

	LoadfileSeg(filename, (char*)&missionTempHeader, header & 0x7ffff, sizeof(MS_MISSION));

	memcpy((u_char*)MissionHeader->residentModels, (u_char*)missionTempHeader.residentModels, sizeof(missionTempHeader.residentModels));
	MissionHeader->time = missionTempHeader.time;
	MissionHeader->weather = missionTempHeader.weather;
	MissionHeader->cops = missionTempHeader.cops;

	if(gCutsceneChaseAutoTest == 0)
		ClearMem((char*)gAutoTestStats, sizeof(gAutoTestStats));

	return 1;
}

// Loads original cutscene replay inside CUT*.R
int CutRec_LoadCutsceneAsReplayFromBuffer(char* buffer)
{
	REPLAY_SAVE_HEADER* header;
	REPLAY_STREAM_HEADER* sheader;

	char* pt = buffer;

	header = (REPLAY_SAVE_HEADER*)pt;

	if (header->magic != DRIVER2_REPLAY_MAGIC &&
		header->magic != REDRIVER2_CHASE_MAGIC ||	// [A]
		header->NumReplayStreams == 0)
		return 0;

	ReplayStart = replayptr = (char*)_replay_buffer;

	GameLevel = header->GameLevel;
	GameType = (GAMETYPE)header->GameType;

	NumReplayStreams = header->NumReplayStreams;
	NumPlayers = header->NumPlayers;
	gRandomChase = header->RandomChase;
	CutsceneEventTrigger = header->CutsceneEvent;
	gCopDifficultyLevel = header->gCopDifficultyLevel;
	ActiveCheats = header->ActiveCheats; // TODO: restore old value

	wantedCar[0] = header->wantedCar[0];
	wantedCar[1] = header->wantedCar[1];

	memcpy((u_char*)&MissionEndData, (u_char*)&header->SavedData, sizeof(MISSION_DATA));

	pt = (char*)(header + 1);

	int maxLength = 0;
	for (int i = 0; i < NumReplayStreams; i++)
	{
		sheader = (REPLAY_STREAM_HEADER*)pt;
		pt += sizeof(REPLAY_STREAM_HEADER);

		REPLAY_STREAM* destStream = &ReplayStreams[i];

		// copy source type
		memcpy((u_char*)&destStream->SourceType, (u_char*)&sheader->SourceType, sizeof(STREAM_SOURCE));

		int size = (sheader->Size + sizeof(PADRECORD)) & -4;

		// init buffers
		AllocateReplayStream(destStream, 4000);

		// copy pad data and advance buffer
		memcpy((u_char*)destStream->PadRecordBuffer, pt, size);

		pt += size;

		destStream->padCount = size / sizeof(PADRECORD);
		destStream->length = sheader->Length;

		if (sheader->Length > maxLength)
			maxLength = sheader->Length;
	}

#if 0
	ReplayParameterPtr = (REPLAY_PARAMETER_BLOCK*)replayptr;
	memset((u_char*)ReplayParameterPtr, 0, sizeof(REPLAY_PARAMETER_BLOCK));
	ReplayParameterPtr->RecordingEnd = maxLength;

	PlayerWayRecordPtr = (SXYPAIR*)(ReplayParameterPtr + 1);
	memset(PlayerWayRecordPtr, 0, sizeof(SXYPAIR) * MAX_REPLAY_WAYPOINTS);

	PlaybackCamera = (PLAYBACKCAMERA*)(PlayerWayRecordPtr + MAX_REPLAY_WAYPOINTS);
	memcpy((u_char*)PlaybackCamera, (u_char*)pt, sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS);
	pt += sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS;

	PingBufferPos = 0;
	PingBuffer = (PING_PACKET*)(PlaybackCamera + MAX_REPLAY_CAMERAS);
	memcpy((u_char*)PingBuffer, (u_char*)pt, sizeof(PING_PACKET) * MAX_REPLAY_PINGS);
	pt += sizeof(PING_PACKET) * MAX_REPLAY_PINGS;

	replayptr = (char*)(PingBuffer + MAX_REPLAY_PINGS);

	if (header->HaveStoredData == 0x91827364)	// -0x6e7d8c9c
	{
		memcpy((u_char*)&MissionStartData, (u_char*)pt, sizeof(MISSION_DATA));
		gHaveStoredData = 1;
	}
#else
	// [A] REDRIVER2 chase replays skip cameras
	if (header->magic == REDRIVER2_CHASE_MAGIC)
	{
		ReplayParameterPtr = (REPLAY_PARAMETER_BLOCK*)replayptr;
		memset((u_char*)ReplayParameterPtr, 0, sizeof(REPLAY_PARAMETER_BLOCK));
		ReplayParameterPtr->RecordingEnd = maxLength;

		PlayerWayRecordPtr = (SXYPAIR*)(ReplayParameterPtr + 1);
		PlaybackCamera = (PLAYBACKCAMERA*)(PlayerWayRecordPtr + MAX_REPLAY_WAYPOINTS);
	}
	else
	{
		ReplayParameterPtr = (REPLAY_PARAMETER_BLOCK*)replayptr;
		memset((u_char*)ReplayParameterPtr, 0, sizeof(REPLAY_PARAMETER_BLOCK));
		ReplayParameterPtr->RecordingEnd = maxLength;

		PlayerWayRecordPtr = (SXYPAIR*)(ReplayParameterPtr + 1);
		memset(PlayerWayRecordPtr, 0, sizeof(SXYPAIR) * MAX_REPLAY_WAYPOINTS);

		PlaybackCamera = (PLAYBACKCAMERA*)(PlayerWayRecordPtr + MAX_REPLAY_WAYPOINTS);
		memcpy((u_char*)PlaybackCamera, (u_char*)pt, sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS);
		pt += sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS;
	}

	PingBufferPos = 0;
	PingBuffer = (PING_PACKET*)(PlaybackCamera + MAX_REPLAY_CAMERAS);
	memcpy((u_char*)PingBuffer, (u_char*)pt, sizeof(PING_PACKET) * MAX_REPLAY_PINGS);
	memcpy((u_char*)NewPingBuffer, (u_char*)pt, sizeof(PING_PACKET) * MAX_REPLAY_PINGS);
	pt += sizeof(PING_PACKET) * MAX_REPLAY_PINGS;
	
	replayptr = (char*)(PingBuffer + MAX_REPLAY_PINGS);

	if (header->HaveStoredData == 0x91827364)	// -0x6e7d8c9c
	{
		memcpy((u_char*)&MissionStartData, (u_char*)pt, sizeof(MISSION_DATA));
		gHaveStoredData = 1;
	}
#endif
	return 1;
}

// [D] [T]
int CutRec_SaveReplayToBuffer(char* buffer)
{
	REPLAY_STREAM_HEADER* sheader;
	REPLAY_SAVE_HEADER* header;

	if (buffer == NULL)
		return 0x3644;

	char* pt = buffer;
	header = (REPLAY_SAVE_HEADER*)pt;
	pt += sizeof(REPLAY_SAVE_HEADER);

	header->magic = DRIVER2_REPLAY_MAGIC;
	header->GameLevel = GameLevel;
	header->GameType = GameType;
	header->MissionNumber = gCurrentMissionNumber;

	header->NumReplayStreams = NumReplayStreams - NumCutsceneStreams;
	header->NumPlayers = NumPlayers;
	header->CutsceneEvent = -1;
	header->RandomChase = gRandomChase;

	header->gCopDifficultyLevel = gCopDifficultyLevel;
	header->ActiveCheats = ActiveCheats;

	header->wantedCar[0] = wantedCar[0];
	header->wantedCar[1] = wantedCar[1];

	memcpy((u_char*)&header->SavedData, (u_char*)&MissionEndData, sizeof(MISSION_DATA));
	
	// write each stream data
	for (int i = 0; i < NumReplayStreams; i++)
	{
		sheader = (REPLAY_STREAM_HEADER*)pt;
		pt += sizeof(REPLAY_STREAM_HEADER);

		REPLAY_STREAM* srcStream = &ReplayStreams[i];

		// copy source type
		memcpy((u_char*)&sheader->SourceType, (u_char*)&srcStream->SourceType, sizeof(STREAM_SOURCE));
		sheader->Size = srcStream->padCount * sizeof(PADRECORD);
		sheader->Length = srcStream->length;

		int size = (sheader->Size + sizeof(PADRECORD)) & -4;

		// copy pad data to write buffer
		memcpy((u_char*)pt, (u_char*)srcStream->InitialPadRecordBuffer, size);

		pt += size;
	}

	memcpy((u_char*)pt, (u_char*)PlaybackCamera, sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS);
	pt += sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS;

	memcpy((u_char*)pt, (u_char*)NewPingBuffer, sizeof(PING_PACKET) * MAX_REPLAY_PINGS);
	pt += sizeof(PING_PACKET) * MAX_REPLAY_PINGS;

	// [A] is that ever valid?
	if (gHaveStoredData)
	{
		header->HaveStoredData = 0x91827364;	// -0x6e7d8c9c
		memcpy((u_char*)pt, (u_char*)&MissionStartData, sizeof(MISSION_DATA));
	}

	return pt - buffer;
}

// saves chase to file
int CutRec_SaveReplayToFile(char* filename)
{
	int size = CutRec_SaveReplayToBuffer((char*)_other_buffer);

	FILE* fp = fopen(filename, "wb");
	if (fp)
	{
		fwrite((char*)_other_buffer, 1, size, fp);
		fclose(fp);
		return 1;
	}

	return 0;
}

int CutRec_SaveChase()
{
	char filename[64];
	FILE* temp;
	int cnt;
	cnt = 2;

	// put files to folder
	sprintf(filename, "CUT%d", gCutsceneAsReplay);
	_mkdir(filename);

	// find suitable filename
	while (cnt < 14)
	{
		sprintf(filename, "CUT%d/CUT%d_%d.D2RP", gCutsceneAsReplay, gCutsceneAsReplay, cnt);

		if ((temp = fopen(filename, "rb")) != NULL)
		{
			fclose(temp);
			cnt++;
		}
		else
			break;
	}

	if (cnt > 14)
		return 0;


	if(CutRec_SaveReplayToFile(filename))
	{
		printInfo("Chase replay '%s' saved\n", filename);

		if (gCutsceneChaseAutoTest != 0)
			gAutoTestStats[gCutsceneChaseAutoTest].saved = 1;
		
		return 1;
	}

	return 0;
}

int CutRec_RecordPad(CAR_DATA* cp, uint* t0, char* t1, char* t2)
{
	if (gCutsceneAsReplay == 0 || NoPlayerControl || (char)cp->ai.padid != gCutsceneAsReplay_PlayerId)
		return 0;

	*t0 = Pads[0].mapped;	// [A] padid might be wrong
	*t1 = Pads[0].mapanalog[2];
	*t2 = Pads[0].type & 4;

	if (gStopPadReads != 0)
	{
		*t0 = CAR_PAD_BRAKE;

		if (cp->hd.wheel_speed <= 0x9000)
			*t0 = CAR_PAD_HANDBRAKE;

		*t1 = 0;
		*t2 = 1;
	}

	cjpRecord(-*cp->ai.padid, t0, t1, t2);

	return 1;
}

int	CutRec_IsRecording()
{
	if (gCutsceneAsReplay == 0)
		return 0;

	return CurrentGameMode != GAMEMODE_REPLAY;
}

int	CutRec_IsPlaying()
{
	if (gCutsceneAsReplay == 0)
		return 0;

	return CurrentGameMode == GAMEMODE_REPLAY;
}

#endif // CUTSCENE_RECORDER