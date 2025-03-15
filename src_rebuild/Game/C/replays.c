#include "driver2.h"
#include "replays.h"
#include "map.h"
#include "spool.h"
#include "system.h"
#include "cutscene.h"
#include "players.h"
#include "glaunch.h"
#include "mission.h"
#include "director.h"
#include "camera.h"
#include "civ_ai.h"
#include "cutrecorder.h"

char AnalogueUnpack[16] = { 
	0, -51, -63, -75, -87, -99, -111, -123,
	0,  51,  63,  75,  87,  99,  111,  123
};

int gOutOfTape = 0;

REPLAY_PARAMETER_BLOCK *ReplayParameterPtr = NULL;

REPLAY_STREAM ReplayStreams[MAX_REPLAY_STREAMS];
int NumReplayStreams = 1;

char *ReplayStart;
char *replayptr = NULL;
int ReplaySize = 0;

int PingBufferPos = 0;
PING_PACKET *PingBuffer = NULL;

SXYPAIR *PlayerWayRecordPtr = NULL;
PLAYBACKCAMERA *PlaybackCamera = NULL;

int TimeToWay = 0;
short PlayerWaypoints = 0;
int way_distance = 0;
int gUseStoredPings = 1;
char ReplayMode = 0;

#define REPLAY_IDENT (('D' << 24) | ('2' << 16) | ('R' << 8) | 'P' )

// [D] [T]
void InitPadRecording(void)
{
	char *bufferEnd;

	int remain, cutsSize;
	int i;

	// initialize chases
	cutsSize = CalcInGameCutsceneSize();

	gOutOfTape = 0;

	if (gLoadedReplay == 0 && 
		CurrentGameMode != GAMEMODE_REPLAY &&
		CurrentGameMode != GAMEMODE_DIRECTOR)
	{
		NumReplayStreams = 0;

		ReplayStart = (char*)_replay_buffer;
		ReplayParameterPtr = (REPLAY_PARAMETER_BLOCK *)ReplayStart;

		PlayerWayRecordPtr = (SXYPAIR *)(ReplayParameterPtr + 1);

		PlaybackCamera = (PLAYBACKCAMERA *)(PlayerWayRecordPtr + MAX_REPLAY_WAYPOINTS);

		PingBuffer = (PING_PACKET *)(PlaybackCamera + MAX_REPLAY_CAMERAS);
		setMem8((u_char*)PingBuffer, -1, sizeof(PING_PACKET) * MAX_REPLAY_PINGS);

		replayptr = (char*)(PingBuffer + MAX_REPLAY_PINGS);

		// FIXME: is that correct?
		bufferEnd = replayptr-13380;
		remain = (int)(ReplayStart - bufferEnd) - cutsSize;

		for (i = 0; i < NumPlayers; i++)
		{
			AllocateReplayStream(&ReplayStreams[i], remain / sizeof(PADRECORD) / NumPlayers);
			NumReplayStreams++;
		}

		ReplaySize = (replayptr - ReplayStart);
	}
	else
	{
		// reset stream count as cutscene/chase can increase it
		NumReplayStreams = NumPlayers;
		
		for (i = 0; i < NumReplayStreams; i++)
		{
			ReplayStreams[i].playbackrun = 0;
			ReplayStreams[i].PadRecordBuffer = ReplayStreams[i].InitialPadRecordBuffer;
		}
	}

	TimeToWay = 150;
	PlayerWaypoints = 0;
	way_distance = 100;

	InitDirectorVariables();
	InitInGameCutsceneVariables();
}


// [D] [T]
int SaveReplayToBuffer(char *buffer)
{
	REPLAY_STREAM_HEADER *sheader;
	REPLAY_SAVE_HEADER *header;

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

	header->SavedData = MissionEndData;

	// write each stream data
	for (int i = 0; i < NumPlayers; i++)
	{
		sheader = (REPLAY_STREAM_HEADER *)pt;
		pt += sizeof(REPLAY_STREAM_HEADER);

		REPLAY_STREAM* srcStream = &ReplayStreams[i];

		// copy source type
		sheader->SourceType = srcStream->SourceType;
		sheader->Size = srcStream->padCount * sizeof(PADRECORD); // srcStream->PadRecordBufferEnd - srcStream->InitialPadRecordBuffer;
		sheader->Length = srcStream->length;

		int size = (sheader->Size + sizeof(PADRECORD)) & -4;

		// copy pad data to write buffer
		memcpy((u_char*)pt, (u_char*)srcStream->InitialPadRecordBuffer, size);

		pt += size;
	}

	memcpy((u_char*)pt, (u_char*)ReplayParameterPtr, sizeof(REPLAY_PARAMETER_BLOCK));
	pt += sizeof(REPLAY_PARAMETER_BLOCK);

	memcpy((u_char*)pt, (u_char*)PlayerWayRecordPtr, sizeof(SXYPAIR) * MAX_REPLAY_WAYPOINTS);
	pt += sizeof(SXYPAIR) * MAX_REPLAY_WAYPOINTS;

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

#ifdef PSX
	return 0x3644;		// size?
#else
	return pt - buffer;
#endif
}

// [D] [T]
int LoadReplayFromBuffer(char *buffer)
{
	REPLAY_SAVE_HEADER *header;
	REPLAY_STREAM_HEADER *sheader;

	char* pt = buffer;

	header = (REPLAY_SAVE_HEADER*)pt;

	if (header->magic != DRIVER2_REPLAY_MAGIC)
		return 0;

	ReplayStart = replayptr = (char*)_replay_buffer;

	GameLevel = header->GameLevel;
	GameType = (GAMETYPE)header->GameType;

	gCurrentMissionNumber = header->MissionNumber;

	NumReplayStreams = header->NumReplayStreams;
	NumPlayers = header->NumPlayers;
	gRandomChase = header->RandomChase;
	CutsceneEventTrigger = header->CutsceneEvent;
	gCopDifficultyLevel = header->gCopDifficultyLevel;
	ActiveCheats = header->ActiveCheats; // TODO: restore old value

	wantedCar[0] = header->wantedCar[0];
	wantedCar[1] = header->wantedCar[1];

	MissionEndData = header->SavedData;

	pt = (char*)(header+1);

	int maxLength = 0;
	for (int i = 0; i < NumReplayStreams; i++)
	{
		sheader = (REPLAY_STREAM_HEADER *)pt;
		pt += sizeof(REPLAY_STREAM_HEADER);

		REPLAY_STREAM* destStream = &ReplayStreams[i];
		
		// copy source type
		destStream->SourceType = sheader->SourceType;

		int size = (sheader->Size + sizeof(PADRECORD)) & -4;
		
		// init buffers
		destStream->InitialPadRecordBuffer = (PADRECORD*)replayptr;
		destStream->PadRecordBuffer = (PADRECORD*)replayptr;
		destStream->PadRecordBufferEnd = (PADRECORD*)(replayptr + size);
		destStream->playbackrun = 0;
		destStream->padCount = sheader->Size / sizeof(PADRECORD);

		// copy pad data and advance buffer
		memcpy((u_char*)replayptr, (u_char*)pt, size);
		replayptr += size;

		pt += size;

		destStream->length = sheader->Length;

		if (sheader->Length > maxLength)
			maxLength = sheader->Length;
	}

	ReplayParameterPtr = (REPLAY_PARAMETER_BLOCK *)replayptr;
	memcpy((u_char*)ReplayParameterPtr, (u_char*)pt, sizeof(REPLAY_PARAMETER_BLOCK));
	pt += sizeof(REPLAY_PARAMETER_BLOCK);

	PlayerWayRecordPtr = (SXYPAIR *)(ReplayParameterPtr + 1);
	memcpy((u_char*)PlayerWayRecordPtr, (u_char*)pt, sizeof(SXYPAIR) * MAX_REPLAY_WAYPOINTS);
	pt += sizeof(SXYPAIR) * MAX_REPLAY_WAYPOINTS;
		
	PlaybackCamera = (PLAYBACKCAMERA *)(PlayerWayRecordPtr + MAX_REPLAY_WAYPOINTS);
	memcpy((u_char*)PlaybackCamera, (u_char*)pt, sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS);
	pt += sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS;

	PingBufferPos = 0;
	PingBuffer = (PING_PACKET *)(PlaybackCamera + MAX_REPLAY_CAMERAS);
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
int LoadAttractReplay(int mission)
{
	char filename[32];

	sprintf(filename, "REPLAYS\\ATTRACT.%d", mission);

	if (!FileExists(filename))
		return 0;

	if (!Loadfile(filename, (char*)_other_buffer))
		return 0;

	return LoadReplayFromBuffer((char*)_other_buffer);
}

// [D] [T]
char GetPingInfo(char *cookieCount)
{
	char retCarId;
	PING_PACKET *pp;

	retCarId = -1;

	if (PingBuffer && PingBufferPos < MAX_REPLAY_PINGS)
	{
		pp = &PingBuffer[PingBufferPos];
		
		// accept only valid car pings
		if (pp->frame != 0xFFFF)
		{
			if (CameraCnt - frameStart < pp->frame) 
				return -1;

			retCarId = pp->carId;
			*cookieCount = pp->cookieCount;
		}

		PingBufferPos++;
	}

	return retCarId;
}

// [A] returns 1 if can use ping buffer
int IsPingInfoAvailable()
{
	if (!_CutRec_IsPlaying() && (gUseStoredPings == 0 || gInGameChaseActive == 0))// && gLoadedReplay == 0)
		return 0;
	
	return PingBuffer != NULL && PingBufferPos < MAX_REPLAY_PINGS;
}

// [D] [T]
int valid_region(int x, int z)
{
	XYPAIR region_coords;

	int region;

	region_coords.x = (x >> 16) + regions_across / 2;
	region_coords.y = (z >> 16) + regions_down / 2;

	if (region_coords.x >= 0 && region_coords.x <= regions_across && 
		region_coords.y >= 0 && region_coords.y <= regions_down) 
	{
		region = region_coords.x + region_coords.y * regions_across;

		if (region != regions_unpacked[0])
		{
			if (region == regions_unpacked[1])
				return region + 1;

			if (region == regions_unpacked[2])
				return region + 1;

			if (region != regions_unpacked[3])
				return 0;
		}

		return region + 1;
	}

	return 0;
}

// [D] [T]
int Get(int stream, u_int *pt0)
{
	REPLAY_STREAM* rstream;

	if (stream < NumReplayStreams)
	{
		rstream = &ReplayStreams[stream];

		if (rstream->PadRecordBuffer + 1 <= rstream->PadRecordBufferEnd)
		{
			u_int t0 = (rstream->PadRecordBuffer->pad << 8) | rstream->PadRecordBuffer->analogue;
			*pt0 = t0;

			if (rstream->playbackrun < rstream->PadRecordBuffer->run)
			{
				rstream->playbackrun++;
			}
			else
			{
				rstream->PadRecordBuffer++;
				rstream->playbackrun = 0;
			}

			return 1;
		}
	}

	*pt0 = 0x10;

	return 0;
}

// [D] [T]
int Put(int stream, u_int*pt0)
{
	REPLAY_STREAM *rstream;
	u_int t0;
	PADRECORD *padbuf;

	rstream = &ReplayStreams[stream];

	if (rstream->PadRecordBuffer + 1 >= rstream->PadRecordBufferEnd)
		return 0;

	padbuf = rstream->PadRecordBuffer;
	t0 = *pt0;

	if (CameraCnt != 0 && padbuf->run != 0xEE)
	{
		if (padbuf->pad == ((t0 >> 8) & 0xff) &&
			padbuf->analogue == (t0 & 0xff) &&
			padbuf->run != 143)
		{
			padbuf->run++;
			return 1;
		}

		padbuf++;

		padbuf->pad = (t0 >> 8) & 0xFF;
		padbuf->analogue = t0 & 0xFF;
		padbuf->run = 0;

		rstream->PadRecordBuffer = padbuf;
		rstream->padCount++;

		return 1;
	}

	padbuf->pad = (t0 >> 8) & 0xFF;
	padbuf->analogue = t0 & 0xFF;
	padbuf->run = 0;

	return 1;
}

// [D] [T]
int cjpPlay(int stream, u_int *ppad, char *psteer, char *ptype)
{
	int ret;
	int t1;
	u_int t0;

#ifdef CUTSCENE_RECORDER
	if (stream < 0)
		stream = -stream;
#endif

	ret = Get(stream, &t0);

	t1 = (t0 >> 8) & 0xF;

	*ppad = t0 & 0xF0FC;

	if (t1 == 0) 
	{
		*psteer = 0;
		*ptype = 0;
	}
	else 
	{
		*psteer = AnalogueUnpack[t1];
		*ptype = 4;
	}

	return ret;
}

// [D] [T]
void cjpRecord(int stream, u_int *ppad, char *psteer, char *ptype)
{
	int tmp;
	int t1;
	u_int t0;

	if (stream > -1 && stream < NumReplayStreams) 
	{
		RecordWaypoint();

		if ((*ptype & 4U) == 0) 
		{
			t1 = 0;
		}
		else 
		{
			if (*psteer < -45) 
			{
				tmp = -45 - *psteer >> 0x1f;	// [A] still need to figure out this
				t1 = (((-45 - *psteer) / 6 + tmp >> 1) - tmp) + 1;
			}
			else if (*psteer < 46)
			{
				t1 = 8;
			}
			else
			{
				tmp = *psteer - 45 >> 0x1f;	// [A] still need to figure out this
				t1 = (((*psteer - 45) / 6 + tmp >> 1) - tmp) + 9;
			}
		}

		t0 = (t1 & 0xF) << 8 | *ppad & 0xF0FC;

		if (Put(stream, &t0) == 0)
		{
			gOutOfTape = 1;
		}
		else if(NoPlayerControl == 0)
		{
			ClearCameras = 1;

			if (ReplayMode != 3 && ReplayMode != 8)
			{
				ReplayStreams[stream].length = CameraCnt;
				ReplayParameterPtr->RecordingEnd = CameraCnt;
			}
		}

		t1 = (t0 >> 8) & 0xF;

		if (t1 == 0) 
		{
			*psteer = 0;
			*ptype = 0;
		}
		else 
		{
			*psteer = AnalogueUnpack[t1];
			*ptype = 4;
		}

		*ppad = t0 & 0xF0FC;
	}
}

// [D] [T]
void AllocateReplayStream(REPLAY_STREAM *stream, int maxpad)
{
	stream->playbackrun = 0;
	stream->length = 0;
	stream->padCount = 0;

	stream->InitialPadRecordBuffer = (PADRECORD*)replayptr;
	stream->PadRecordBuffer = (PADRECORD*)replayptr;

	stream->PadRecordBufferEnd = (PADRECORD *)(replayptr + maxpad * sizeof(PADRECORD));

	if (NoPlayerControl == 0)
	{
		*replayptr = 0;

		stream->InitialPadRecordBuffer->analogue = 0;
		stream->InitialPadRecordBuffer->run = 238;
	}

	replayptr = (char *)(((intptr)replayptr + (maxpad+1) * sizeof(PADRECORD)) & -4);
}

// [D] [T]
void RecordWaypoint(void)
{
	if (TimeToWay > 0)
	{
		TimeToWay--;
		return;
	}

	if (PlayerWaypoints < MAX_REPLAY_WAYPOINTS)
	{
		TimeToWay = way_distance;

		PlayerWayRecordPtr->x = (player[0].pos[0] >> 10);
		PlayerWayRecordPtr->y = (player[0].pos[2] >> 10);

		PlayerWayRecordPtr++;
		PlayerWaypoints++;
	}
}
