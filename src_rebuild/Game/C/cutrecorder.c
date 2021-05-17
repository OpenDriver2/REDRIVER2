#ifdef PSX
#error This file is not applicable for PSX build
#endif
#ifdef CUTSCENE_RECORDER

#include "driver2.h"

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

#include "../utils/ini.h"

int gCutsceneAsReplay = 0;
int gCutsceneAsReplay_PlayerId = 0;
int gCutsceneAsReplay_PlayerChanged = 0;
int gCutsceneAsReplay_ReserveSlots = 2;
char gCutsceneRecorderPauseText[64] = { 0 };
char gCurrentChasePauseText[64] = { 0 };

int CutRec_LoadCutsceneAsReplayFromBuffer(char* buffer);

void CutRec_Reset()
{
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

void CutRec_ReserveSlots()
{
	// [A] reserve slots to avoid their use for chases
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

	if (gCutsceneAsReplay_PlayerId >= NumReplayStreams)
		gCutsceneAsReplay_PlayerId -= NumReplayStreams;
	else if (gCutsceneAsReplay_PlayerId < 0)
		gCutsceneAsReplay_PlayerId += NumReplayStreams;

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

	if (gCutsceneAsReplay < 21)
		sprintf(filename, "REPLAYS\\CUT%d.R", gCutsceneAsReplay);
	else
		sprintf(filename, "REPLAYS\\A\\CUT%d.R", gCutsceneAsReplay);

	if (FileExists(filename))
	{
		LoadfileSeg(filename, (char*)&header, 0, sizeof(CUTSCENE_HEADER));

		if (header.data[subindex].offset != 0xffff)
		{
			offset = header.data[subindex].offset * 4;
			size = header.data[subindex].size;

			printWarning("cutscene size: %d\n", size);

			LoadfileSeg(filename, (char*)_other_buffer, offset, size);

			int result = CutRec_LoadCutsceneAsReplayFromBuffer((char*)_other_buffer);

			return result;
		}
	}

	printError("Invalid cutscene subindex or mission!\n");

	return 0;
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
		if (!LoadCutsceneAsReplay(subindex))
		{
			ini_free(config);

			gLoadedReplay = 0;
			gCutsceneAsReplay = 0;
			return;
		}

		gLoadedReplay = 1;
		CurrentGameMode = GAMEMODE_REPLAY;
	}
	else
	{
		int i;
		char curStreamName[40];
		STREAM_SOURCE* stream;

		InitPadRecording();

		ini_sget(config, "settings", "streams", "%d", &NumReplayStreams);

		// initialize all streams
		for (i = 0; i < NumReplayStreams; i++)
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
	PING_PACKET* packet;

	if (gCutsceneAsReplay == 0)
		return 0;

	if (CurrentGameMode == GAMEMODE_REPLAY || gInGameChaseActive != 0)
		return 0;

	if (PingBuffer != NULL && PingBufferPos < MAX_REPLAY_PINGS)
	{
		packet = &PingBuffer[PingBufferPos++];
		packet->frame = CameraCnt - frameStart;
		packet->carId = carId;

		packet->cookieCount = cookieCount;

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

	pos = PingBufferPos;

	while (pos >= 0)
	{
		pos--;
		if (PingBuffer[pos].carId == carId)
		{
			printWarning("Removing ping at %d\n", PingBuffer[pos].frame);
			PingBuffer[pos].carId = -1;

			PingOutCar(&car_data[carId]);
			break;
		}
	}
}

int CutRec_InitPlayers()
{
	if (gCutsceneAsReplay == 0)
		return 0;
	
	for (int i = 0; i < NumReplayStreams; i++)
	{
		PlayerStartInfo[i] = &ReplayStreams[i].SourceType;
	}

	numPlayersToCreate = NumReplayStreams;

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

	return 1;
}

// Loads original cutscene replay inside CUT*.R
int CutRec_LoadCutsceneAsReplayFromBuffer(char* buffer)
{
	REPLAY_SAVE_HEADER* header;
	REPLAY_STREAM_HEADER* sheader;

	char* pt = buffer;

	header = (REPLAY_SAVE_HEADER*)pt;

	if (header->magic != DRIVER2_REPLAY_MAGIC)
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

		destStream->length = sheader->Length;

		if (sheader->Length > maxLength)
			maxLength = sheader->Length;
	}

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

	memcpy((u_char*)pt, (u_char*)PingBuffer, sizeof(PING_PACKET) * MAX_REPLAY_PINGS);
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

int CutRec_RecordPad(CAR_DATA* cp, uint* t0, char* t1, char* t2)
{
	if (gCutsceneAsReplay == 0 || NoPlayerControl || cp->id != gCutsceneAsReplay_PlayerId)
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

#endif // CUTSCENE_RECORDER