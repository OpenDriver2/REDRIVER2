#include "THISDUST.H"
#include "REPLAYS.H"
#include "MAP.H"
#include "SPOOL.H"
#include "SYSTEM.H"
#include "CUTSCENE.H"
#include "PLAYERS.H"
#include "GLAUNCH.H"
#include "MISSION.H"
#include "DIRECTOR.H"
#include "CAMERA.H"
#include "CIV_AI.H"

#include "STRINGS.H"

char AnalogueUnpack[16] = { 
	0, -51, -63, -75, -87, -99, -111, -123,
	0,  51,  63,  75,  87,  99,  111,  123
};

int gOutOfTape = 0;

REPLAY_PARAMETER_BLOCK *ReplayParameterPtr = NULL;

REPLAY_STREAM ReplayStreams[8];
int NumReplayStreams = 1;

char *ReplayStart;
char *replayptr = NULL;
int ReplaySize = 0;

unsigned long PingBufferPos = 0;
_PING_PACKET *PingBuffer = NULL;

SXYPAIR *PlayerWayRecordPtr = NULL;
PLAYBACKCAMERA *PlaybackCamera = NULL;

int TimeToWay = 0;
short PlayerWaypoints = 0;
int way_distance = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ InitPadRecording()
 // line 498, offset 0x0001a09c
	/* begin block 1 */
		// Start line: 500
		// Start offset: 0x0001A09C
		// Variables:
	// 		int i; // $s0
	// 		int remain; // $s0
	/* end block 1 */
	// End offset: 0x0001A234
	// End Line: 650

	/* begin block 2 */
		// Start line: 996
	/* end block 2 */
	// End Line: 997

	/* begin block 3 */
		// Start line: 997
	/* end block 3 */
	// End Line: 998

	/* begin block 4 */
		// Start line: 1001
	/* end block 4 */
	// End Line: 1002

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitPadRecording(void)
{
	char *pcVar1;
	char *pcVar2;

	int i;
	REPLAY_STREAM *stream;

	gOutOfTape = 0;

	if (gLoadedReplay == 0)
	{
		NumReplayStreams = 0;

		ReplayStart = _replay_buffer;
		ReplayParameterPtr = (REPLAY_PARAMETER_BLOCK *)ReplayStart;

		PlayerWayRecordPtr = (SXYPAIR *)(ReplayParameterPtr + 1);

		PlaybackCamera = (PLAYBACKCAMERA *)(PlayerWayRecordPtr + 150);

		PingBuffer = (_PING_PACKET *)(PlaybackCamera + 60);
		setMem8((u_char*)PingBuffer, -1, sizeof(_PING_PACKET) * 400);

		replayptr = (char*)(PingBuffer + 400);

		pcVar1 = ReplayStart;
		pcVar2 = replayptr-0x3444;

		int cutsceneSize = CalcInGameCutsceneSize();

		for (i = 0; i < NumPlayers; i++)
		{
			AllocateReplayStream(&ReplayStreams[i], ((int)(pcVar1 + (-cutsceneSize - (int)pcVar2)) / sizeof(PADRECORD)) / NumPlayers);
			NumReplayStreams++;
		}

		ReplaySize = (replayptr - ReplayStart);
	}
	else
	{
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



// decompiled code
// original method signature: 
// int /*$ra*/ SaveReplayToBuffer(char *buffer /*$s0*/)
 // line 657, offset 0x0001a234
	/* begin block 1 */
		// Start line: 658
		// Start offset: 0x0001A234
		// Variables:
	// 		struct REPLAY_SAVE_HEADER *header; // $s2
	// 		int i; // $a2
	// 		int size; // $s1
	// 		int numstreams; // $s6
	/* end block 1 */
	// End offset: 0x0001A798
	// End Line: 733

	/* begin block 2 */
		// Start line: 1340
	/* end block 2 */
	// End Line: 1341

	/* begin block 3 */
		// Start line: 1348
	/* end block 3 */
	// End Line: 1349

int SaveReplayToBuffer(char *buffer)
{
	UNIMPLEMENTED();
	return 0;
	/*
	char cVar1;
	byte bVar2;
	REPLAY_PARAMETER_BLOCK *pRVar3;
	long lVar4;
	SXYPAIR *pSVar5;
	PLAYBACKCAMERA *pPVar6;
	_PING_PACKET *p_Var7;
	long lVar8;
	SXYPAIR *pSVar9;
	PLAYBACKCAMERA *pPVar10;
	_PING_PACKET *p_Var11;
	int iVar12;
	int *piVar13;
	MISSION_DATA *pMVar14;
	SXYPAIR *pSVar15;
	int *piVar16;
	_PING_PACKET *p_Var17;
	long *plVar18;
	int iVar19;
	SXYPAIR SVar20;
	REPLAY_STREAM *pRVar21;
	_PING_PACKET _Var22;
	SXYPAIR SVar23;
	_PING_PACKET _Var24;
	long lVar25;
	SXYPAIR SVar26;
	_PING_PACKET _Var27;
	PADRECORD *pPVar28;
	uint __n;
	char *unaff_s2;
	int iVar29;
	uint uVar30;

	bVar2 = NumPlayers;
	uVar30 = (uint)NumPlayers;
	piVar13 = (int *)buffer;
	if (buffer != (char *)0x0) {
		*(undefined4 *)buffer = 0x14793209;
		buffer[4] = (char)GameLevel;
		buffer[5] = GameType;
		iVar19 = gCurrentMissionNumber;
		buffer[7] = bVar2;
		*(int *)(buffer + 0xfc) = iVar19;
		plVar18 = (long *)(buffer + 0xc);
		buffer[8] = NumPlayers;
		cVar1 = (char)gRandomChase;
		buffer[10] = -1;
		buffer[9] = cVar1;
		pMVar14 = &MissionEndData;
		buffer[0xb] = (char)gCopDifficultyLevel;
		*(undefined4 *)(buffer + 0xf0) = ActiveCheats;
		*(int *)(buffer + 0xf4) = wantedCar[0];
		piVar13 = (int *)(buffer + 0x11c);
		*(int *)(buffer + 0xf8) = wantedCar[1];
		do {
			lVar25 = (pMVar14->PlayerPos).vx;
			lVar4 = (pMVar14->PlayerPos).vy;
			lVar8 = (pMVar14->PlayerPos).vz;
			*plVar18 = *(long *)&pMVar14->PlayerPos;
			plVar18[1] = lVar25;
			plVar18[2] = lVar4;
			plVar18[3] = lVar8;
			pMVar14 = (MISSION_DATA *)&(pMVar14->PlayerPos).felony;
			plVar18 = plVar18 + 4;
		} while (pMVar14 != (MISSION_DATA *)&MissionEndData.CarPos[5].vz);
		*plVar18 = MissionEndData.CarPos[5].vz;
		unaff_s2 = buffer;
	}
	if (piVar13 != (int *)0x0) {
		iVar19 = 0;
		if (bVar2 != 0) {
			do {
				pRVar21 = ReplayStreams + iVar19;
				iVar29 = iVar19 + 1;
				pPVar28 = (PADRECORD *)
					((int)ReplayStreams[iVar19].PadRecordBufferEnd -
					(int)ReplayStreams[iVar19].InitialPadRecordBuffer);
				piVar16 = piVar13;
				do {
					iVar12 = *(int *)&(pRVar21->SourceType).flags;
					lVar8 = (pRVar21->SourceType).position.vx;
					lVar4 = (pRVar21->SourceType).position.vy;
					*piVar16 = *(int *)&pRVar21->SourceType;
					piVar16[1] = iVar12;
					piVar16[2] = lVar8;
					piVar16[3] = lVar4;
					pRVar21 = (REPLAY_STREAM *)&(pRVar21->SourceType).position.vz;
					piVar16 = piVar16 + 4;
				} while (pRVar21 != (REPLAY_STREAM *)&ReplayStreams[iVar19].InitialPadRecordBuffer);
				*(PADRECORD **)(piVar13 + 0xc) = pPVar28;
				__n = (uint)(pPVar28 + 1) & 0xfffffffc;
				piVar13[0xd] = ReplayStreams[iVar19].length;
				memcpy(piVar13 + 0xe, ReplayStreams[iVar19].InitialPadRecordBuffer, __n);
				piVar13 = (int *)((int)(piVar13 + 0xe) + __n);
				iVar19 = iVar29;
			} while (iVar29 < (int)uVar30);
		}
		pRVar3 = ReplayParameterPtr;
		iVar19 = (ReplayParameterPtr->lead_car_start).vx;
		iVar29 = (ReplayParameterPtr->lead_car_start).vy;
		iVar12 = (ReplayParameterPtr->lead_car_start).vz;
		*piVar13 = ReplayParameterPtr->RecordingEnd;
		piVar13[1] = iVar19;
		piVar13[2] = iVar29;
		piVar13[3] = iVar12;
		piVar13[4] = *(int *)&pRVar3->Lead_car_dir;
		pSVar15 = (SXYPAIR *)(piVar13 + 5);
		pSVar9 = PlayerWayRecordPtr;
		if ((((uint)PlayerWayRecordPtr | (uint)pSVar15) & 3) == 0) {
			pSVar5 = PlayerWayRecordPtr + 0x94;
			do {
				SVar23 = pSVar9[1];
				SVar26 = pSVar9[2];
				SVar20 = pSVar9[3];
				*pSVar15 = *pSVar9;
				pSVar15[1] = SVar23;
				pSVar15[2] = SVar26;
				pSVar15[3] = SVar20;
				pSVar9 = pSVar9 + 4;
				pSVar15 = pSVar15 + 4;
			} while (pSVar9 != pSVar5);
		}
		else {
			pSVar5 = PlayerWayRecordPtr + 0x94;
			do {
				SVar23 = pSVar9[1];
				SVar26 = pSVar9[2];
				SVar20 = pSVar9[3];
				*pSVar15 = *pSVar9;
				pSVar15[1] = SVar23;
				pSVar15[2] = SVar26;
				pSVar15[3] = SVar20;
				pSVar9 = pSVar9 + 4;
				pSVar15 = pSVar15 + 4;
			} while (pSVar9 != pSVar5);
		}
		piVar16 = piVar13 + 0x9b;
		SVar20 = pSVar9[1];
		*pSVar15 = *pSVar9;
		pSVar15[1] = SVar20;
		if ((((uint)PlaybackCamera | (uint)piVar16) & 3) == 0) {
			pPVar6 = PlaybackCamera + 0x3c;
			pPVar10 = PlaybackCamera;
			do {
				iVar19 = (pPVar10->position).vy;
				iVar29 = (pPVar10->position).vz;
				iVar12 = *(int *)&pPVar10->angle;
				*piVar16 = (pPVar10->position).vx;
				piVar16[1] = iVar19;
				piVar16[2] = iVar29;
				piVar16[3] = iVar12;
				pPVar10 = (PLAYBACKCAMERA *)&(pPVar10->angle).vz;
				piVar16 = piVar16 + 4;
			} while (pPVar10 != pPVar6);
		}
		else {
			pPVar6 = PlaybackCamera + 0x3c;
			pPVar10 = PlaybackCamera;
			do {
				iVar19 = (pPVar10->position).vy;
				iVar29 = (pPVar10->position).vz;
				iVar12 = *(int *)&pPVar10->angle;
				*piVar16 = (pPVar10->position).vx;
				piVar16[1] = iVar19;
				piVar16[2] = iVar29;
				piVar16[3] = iVar12;
				pPVar10 = (PLAYBACKCAMERA *)&(pPVar10->angle).vz;
				piVar16 = piVar16 + 4;
			} while (pPVar10 != pPVar6);
		}
		p_Var17 = (_PING_PACKET *)(piVar13 + 0x2b7);
		if ((((uint)PingBuffer | (uint)p_Var17) & 3) == 0) {
			p_Var7 = PingBuffer + 400;
			p_Var11 = PingBuffer;
			do {
				_Var22 = p_Var11[1];
				_Var24 = p_Var11[2];
				_Var27 = p_Var11[3];
				*p_Var17 = *p_Var11;
				p_Var17[1] = _Var22;
				p_Var17[2] = _Var24;
				p_Var17[3] = _Var27;
				p_Var11 = p_Var11 + 4;
				p_Var17 = p_Var17 + 4;
			} while (p_Var11 != p_Var7);
		}
		else {
			p_Var7 = PingBuffer + 400;
			p_Var11 = PingBuffer;
			do {
				_Var22 = p_Var11[1];
				_Var24 = p_Var11[2];
				_Var27 = p_Var11[3];
				*p_Var17 = *p_Var11;
				p_Var17[1] = _Var22;
				p_Var17[2] = _Var24;
				p_Var17[3] = _Var27;
				p_Var11 = p_Var11 + 4;
				p_Var17 = p_Var17 + 4;
			} while (p_Var11 != p_Var7);
		}
		piVar13 = piVar13 + 0x447;
		if (piVar13 != (int *)0x0) {
			*(undefined4 *)(unaff_s2 + 0x100) = 0x91827364;
			pMVar14 = &MissionStartData;
			if (((uint)piVar13 & 3) == 0) {
				do {
					iVar19 = (pMVar14->PlayerPos).vx;
					iVar29 = (pMVar14->PlayerPos).vy;
					iVar12 = (pMVar14->PlayerPos).vz;
					*piVar13 = *(int *)&pMVar14->PlayerPos;
					piVar13[1] = iVar19;
					piVar13[2] = iVar29;
					piVar13[3] = iVar12;
					pMVar14 = (MISSION_DATA *)&(pMVar14->PlayerPos).felony;
					piVar13 = piVar13 + 4;
				} while (pMVar14 != (MISSION_DATA *)&MissionStartData.CarPos[5].vz);
			}
			else {
				do {
					iVar19 = (pMVar14->PlayerPos).vx;
					iVar29 = (pMVar14->PlayerPos).vy;
					iVar12 = (pMVar14->PlayerPos).vz;
					*piVar13 = *(int *)&pMVar14->PlayerPos;
					piVar13[1] = iVar19;
					piVar13[2] = iVar29;
					piVar13[3] = iVar12;
					pMVar14 = (MISSION_DATA *)&(pMVar14->PlayerPos).felony;
					piVar13 = piVar13 + 4;
				} while (pMVar14 != (MISSION_DATA *)&MissionStartData.CarPos[5].vz);
			}
			*piVar13 = *(int *)&pMVar14->PlayerPos;
		}
	}
	return (int)&DAT_00003644;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadReplayFromBuffer(char *buffer /*$s1*/)
 // line 740, offset 0x0001a798
	/* begin block 1 */
		// Start line: 742
		// Start offset: 0x0001A798
		// Variables:
	// 		struct REPLAY_SAVE_HEADER *header; // $s3
	// 		struct REPLAY_STREAM_HEADER *sheader; // $t0
	// 		int i; // $a1
	// 		int size; // $s0
	/* end block 1 */
	// End offset: 0x0001AD50
	// End Line: 813

	/* begin block 2 */
		// Start line: 1574
	/* end block 2 */
	// End Line: 1575

	/* begin block 3 */
		// Start line: 1582
	/* end block 3 */
	// End Line: 1583

	/* begin block 4 */
		// Start line: 1583
	/* end block 4 */
	// End Line: 1584

	/* begin block 5 */
		// Start line: 1587
	/* end block 5 */
	// End Line: 1588

#ifdef CUTSCENE_RECORDER
int gCutsceneAsReplay = 0;
int gCutsceneAsReplay_PlayerId = 0;
int gCutsceneAsReplay_PlayerChanged = 0;
char gCutsceneRecorderPauseText[64] = { 0 };

void NextCutsceneRecorderPlayer(int dir)
{
	int old_player = gCutsceneAsReplay_PlayerId;

	if(dir > 0)
		gCutsceneAsReplay_PlayerId++;
	else if(dir < 0)
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

	NextCutsceneRecorderPlayer(0);

	CUTSCENE_HEADER header;
	char filename[64];

	if (gCutsceneAsReplay < 21)
		sprintf(filename, "REPLAYS\\CUT%d.R", gCutsceneAsReplay);
	else
		sprintf(filename, "REPLAYS\\A\\CUT%d.R", gCutsceneAsReplay);

	if (FileExists(filename))
	{
		LoadfileSeg(filename, (char *)&header, 0, sizeof(CUTSCENE_HEADER));

		if (header.data[subindex].offset != 0xffff)
		{
			offset = header.data[subindex].offset * 4;
			size = header.data[subindex].size;

			LoadfileSeg(filename, _other_buffer, offset, size);

			return LoadReplayFromBuffer(_other_buffer);
		}
	}

	printError("Invalid cutscene subindex or mission!\n");

	return 0;
}
#endif // CUTSCENE_RECORDER

// [D]
int LoadReplayFromBuffer(char *buffer)
{
	REPLAY_STREAM_HEADER *local_s1_516;

	REPLAY_SAVE_HEADER *header;
	REPLAY_STREAM_HEADER *sheader;

	char* pt = buffer;

	header = (REPLAY_SAVE_HEADER*)pt;

	if (header->magic != 0x14793209)
		return 0;

	ReplayStart = replayptr = _replay_buffer;

	GameLevel = header->GameLevel;
	GameType = (GAMETYPE)header->GameType;

#ifdef CUTSCENE_RECORDER
	if(gCutsceneAsReplay == 0)
#endif
		gCurrentMissionNumber = header->MissionNumber;

	NumReplayStreams = header->NumReplayStreams;
	NumPlayers = header->NumPlayers;
	gRandomChase = header->RandomChase;
	CutsceneEventTrigger = header->CutsceneEvent;
	gCopDifficultyLevel = header->gCopDifficultyLevel;
	ActiveCheats = header->ActiveCheats; // TODO: restore old value

	wantedCar[0] = header->wantedCar[0];
	wantedCar[1] = header->wantedCar[1];

	memcpy(&MissionEndData, &header->SavedData, sizeof(MISSION_DATA));

	pt = (char*)(header+1);

	int maxLength = 0;
	for (int i = 0; i < NumReplayStreams; i++)
	{
		sheader = (REPLAY_STREAM_HEADER *)pt;
		pt += sizeof(REPLAY_STREAM_HEADER);

		REPLAY_STREAM* destStream = &ReplayStreams[i];

		// copy source type
		memcpy(&destStream->SourceType, &sheader->SourceType, sizeof(STREAM_SOURCE));

		// init buffers
		destStream->InitialPadRecordBuffer = (PADRECORD*)replayptr;
		destStream->PadRecordBuffer = (PADRECORD*)replayptr;
		destStream->PadRecordBufferEnd = (PADRECORD *)(replayptr + sheader->Size);
		destStream->length = sheader->Length;

		if (sheader->Length > maxLength)
			maxLength = sheader->Length;

		int size = (sheader->Size + sizeof(PADRECORD)) & -4;

		// copy pad data and advance buffer
		memcpy(replayptr, pt, size);
		replayptr += size;

		pt += size;
	}

	ReplayParameterPtr = (REPLAY_PARAMETER_BLOCK *)replayptr;
#ifdef CUTSCENE_RECORDER
	if (gCutsceneAsReplay != 0)
	{
		memset(ReplayParameterPtr, 0, sizeof(REPLAY_PARAMETER_BLOCK));
		ReplayParameterPtr->RecordingEnd = maxLength;
	}
	else
#endif
	{
		memcpy(ReplayParameterPtr, pt, sizeof(REPLAY_PARAMETER_BLOCK));
		pt += sizeof(REPLAY_PARAMETER_BLOCK);
	}


	PlayerWayRecordPtr = (SXYPAIR *)(ReplayParameterPtr + 1);
#ifdef CUTSCENE_RECORDER
	if (gCutsceneAsReplay != 0)
	{
		memset(PlayerWayRecordPtr, 0, sizeof(SXYPAIR) * 150);
	}
	else
#endif
	{
		memcpy(PlayerWayRecordPtr, pt, sizeof(SXYPAIR) * 150);
		pt += sizeof(SXYPAIR) * 150;
	}
		

	PlaybackCamera = (PLAYBACKCAMERA *)(PlayerWayRecordPtr + 150);
	memcpy(PlaybackCamera, pt, sizeof(PLAYBACKCAMERA) * 60);
	pt += sizeof(PLAYBACKCAMERA) * 60;

	PingBufferPos = 0;
	PingBuffer = (_PING_PACKET *)(PlaybackCamera + 60);
	memcpy(PingBuffer, pt, sizeof(_PING_PACKET) * 400);
	pt += sizeof(_PING_PACKET) * 400;

	replayptr = (char*)(PingBuffer + 400);

	if (header->HaveStoredData == 0x91827364)	// -0x6e7d8c9c
	{
		memcpy(&MissionStartData, pt, sizeof(MISSION_DATA));
		gHaveStoredData = 1;
	}

	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadAttractReplay(int mission /*$a2*/)
 // line 1059, offset 0x0001b118
	/* begin block 1 */
		// Start line: 1060
		// Start offset: 0x0001B118
		// Variables:
	// 		char filename[32]; // stack offset -40
	/* end block 1 */
	// End offset: 0x0001B17C
	// End Line: 1071

	/* begin block 2 */
		// Start line: 2231
	/* end block 2 */
	// End Line: 2232

	/* begin block 3 */
		// Start line: 2118
	/* end block 3 */
	// End Line: 2119

// [D]
int LoadAttractReplay(int mission)
{
	char filename[32];

	sprintf(filename,"REPLAYS\\ATTRACT.%d", mission);

	if (!FileExists(filename))
		return 0;

	if (!Loadfile(filename, _other_buffer))
		return 0;

	return LoadReplayFromBuffer(_other_buffer);
}



// decompiled code
// original method signature: 
// char /*$ra*/ GetPingInfo(char *cookieCount /*$a2*/)
 // line 1182, offset 0x0001b090
	/* begin block 1 */
		// Start line: 1183
		// Start offset: 0x0001B090
		// Variables:
	// 		struct _PING_PACKET *pp; // $a1
	// 		char retCarId; // $v0
	/* end block 1 */
	// End offset: 0x0001B118
	// End Line: 1206

	/* begin block 2 */
		// Start line: 2864
	/* end block 2 */
	// End Line: 2865

	/* begin block 3 */
		// Start line: 2364
	/* end block 3 */
	// End Line: 2365

// [D]
char GetPingInfo(char *cookieCount)
{
	char cVar1;
	_PING_PACKET *p_Var2;

	p_Var2 = PingBuffer + PingBufferPos;

	if (PingBuffer != NULL && PingBufferPos < 400)
	{
		cVar1 = -1;
		if (p_Var2->frame != 0xffff) 
		{
			if ((CameraCnt - frameStart & 0xffffU) < p_Var2->frame) 
				return -1;

			cVar1 = p_Var2->carId;
			*cookieCount = p_Var2->cookieCount;
			PingBufferPos = PingBufferPos + 1;
		}
		return cVar1;
	}

	return -1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ valid_region(int x /*$a0*/, int z /*$a1*/)
 // line 1222, offset 0x0001af34
	/* begin block 1 */
		// Start line: 1224
		// Start offset: 0x0001AF34
		// Variables:
	// 		struct XYPAIR region_coords; // stack offset -8
	// 		int region; // $a0
	/* end block 1 */
	// End offset: 0x0001AFFC
	// End Line: 1269

	/* begin block 2 */
		// Start line: 2441
	/* end block 2 */
	// End Line: 2442

	/* begin block 3 */
		// Start line: 2828
	/* end block 3 */
	// End Line: 2829

	/* begin block 4 */
		// Start line: 2829
	/* end block 4 */
	// End Line: 2830

	/* begin block 5 */
		// Start line: 2832
	/* end block 5 */
	// End Line: 2833

// [D]
int valid_region(int x, int z)
{
	int iVar1;
	int iVar2;

	iVar1 = (x >> 0x10) + regions_across / 2;
	iVar2 = (z >> 0x10) + regions_down / 2;

	if (-1 < iVar1) {
		if (regions_across < iVar1)
			return 0;

		if (-1 < iVar2) 
		{
			if (regions_down < iVar2)
				return 0;

			iVar1 = iVar1 + iVar2 * regions_across;

			if (iVar1 != regions_unpacked[0])
			{
				if (iVar1 == regions_unpacked[1])
					return iVar1 + 1;
	
				if (iVar1 == regions_unpacked[2])
					return iVar1 + 1;

				if (iVar1 != regions_unpacked[3]) 
					return 0;
			}

			return iVar1 + 1;
		}
	}
	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ cjpPlay(int stream /*$a0*/, unsigned long *ppad /*$s2*/, char *psteer /*$s0*/, char *ptype /*$s1*/)
 // line 1271, offset 0x0001affc
	/* begin block 1 */
		// Start line: 1272
		// Start offset: 0x0001AFFC
		// Variables:
	// 		int ret; // $a0
	// 		unsigned long t0; // stack offset -24
	// 		int t1; // $v1
	/* end block 1 */
	// End offset: 0x0001B090
	// End Line: 1291

	/* begin block 2 */
		// Start line: 2928
	/* end block 2 */
	// End Line: 2929

	/* begin block 3 */
		// Start line: 2931
	/* end block 3 */
	// End Line: 2932

// [D]
int cjpPlay(int stream, ulong *ppad, char *psteer, char *ptype)
{
	int ret;
	int t1;
	ulong t0;

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



// decompiled code
// original method signature: 
// void /*$ra*/ cjpRecord(int stream /*$s1*/, unsigned long *ppad /*$s4*/, char *psteer /*$s2*/, char *ptype /*$s3*/)
 // line 1310, offset 0x0001ad50
	/* begin block 1 */
		// Start line: 1311
		// Start offset: 0x0001AD50
		// Variables:
	// 		unsigned long t0; // stack offset -32
	// 		int t1; // $s0
	/* end block 1 */
	// End offset: 0x0001AF14
	// End Line: 1370

	/* begin block 2 */
		// Start line: 2348
	/* end block 2 */
	// End Line: 2349

	/* begin block 3 */
		// Start line: 2846
	/* end block 3 */
	// End Line: 2847

char ReplayMode = 0;

void cjpRecord(int stream, ulong *ppad, char *psteer, char *ptype)
{
	REPLAY_PARAMETER_BLOCK *pRVar1;
	int iVar2;
	int iVar3;
	int t1;
	ulong t0;

	if (stream > -1 && stream < NumReplayStreams) 
	{
		iVar3 = (int)*psteer;

		RecordWaypoint();

		if ((*ptype & 4U) == 0) 
		{
			t1 = 0;
		}
		else 
		{
			if (iVar3 < -45) 
			{
				iVar2 = -45 - iVar3 >> 0x1f;
				t1 = (((-45 - iVar3) / 6 + iVar2 >> 1) - iVar2) + 1;
			}
			else if (iVar3 < 46)
			{
				t1 = 8;
			}
			else
			{
				iVar2 = iVar3 - 45 >> 0x1f;
				t1 = (((iVar3 - 45) / 6 + iVar2 >> 1) - iVar2) + 9;
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



// decompiled code
// original method signature: 
// void /*$ra*/ AllocateReplayStream(struct REPLAY_STREAM *stream /*$a0*/, int maxpad /*$a1*/)
 // line 1383, offset 0x0001b17c
	/* begin block 1 */
		// Start line: 3101
	/* end block 1 */
	// End Line: 3102

	/* begin block 2 */
		// Start line: 3414
	/* end block 2 */
	// End Line: 3415

	/* begin block 3 */
		// Start line: 3415
	/* end block 3 */
	// End Line: 3416

	/* begin block 4 */
		// Start line: 3417
	/* end block 4 */
	// End Line: 3418

// [D]
void AllocateReplayStream(REPLAY_STREAM *stream, int maxpad)
{
	stream->playbackrun = 0;
	stream->length = 0;

	stream->InitialPadRecordBuffer = (PADRECORD*)replayptr;
	stream->PadRecordBuffer = (PADRECORD*)replayptr;

	stream->PadRecordBufferEnd = (PADRECORD *)(replayptr + maxpad * sizeof(PADRECORD));

	if (NoPlayerControl == 0)
	{
		*replayptr = 0;

		stream->InitialPadRecordBuffer->analogue = 0;
		stream->InitialPadRecordBuffer->run = 0xEE;
	}

	replayptr = (char *)(((uint)replayptr + (maxpad+1) * sizeof(PADRECORD)) & -4);
}



// decompiled code
// original method signature: 
// int /*$ra*/ Get(int stream /*$a0*/, unsigned long *pt0 /*$a1*/)
 // line 1402, offset 0x0001b1f0
	/* begin block 1 */
		// Start line: 1403
		// Start offset: 0x0001B1F0
		// Variables:
	// 		struct REPLAY_STREAM *rstream; // $a2
	// 		unsigned long t0; // $a0
	/* end block 1 */
	// End offset: 0x0001B280
	// End Line: 1438

	/* begin block 2 */
		// Start line: 3459
	/* end block 2 */
	// End Line: 3460

	/* begin block 3 */
		// Start line: 3466
	/* end block 3 */
	// End Line: 3467

// [D]
int Get(int stream, ulong *pt0)
{
	REPLAY_STREAM* rstream;

	if (stream < NumReplayStreams)
	{
		rstream = &ReplayStreams[stream];

		if (rstream->PadRecordBuffer+1 <= rstream->PadRecordBufferEnd)
		{
			ulong t0 = (rstream->PadRecordBuffer->pad << 8) | rstream->PadRecordBuffer->analogue;
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



// decompiled code
// original method signature: 
// int /*$ra*/ Put(int stream /*$a0*/, unsigned long *pt0 /*$a1*/)
 // line 1440, offset 0x0001b280
	/* begin block 1 */
		// Start line: 1442
		// Start offset: 0x0001B280
		// Variables:
	// 		struct REPLAY_STREAM *rstream; // $a0
	// 		unsigned char **pstream; // $a3
	// 		unsigned long t0; // $a1
	/* end block 1 */
	// End offset: 0x0001B364
	// End Line: 1477

	/* begin block 2 */
		// Start line: 3534
	/* end block 2 */
	// End Line: 3535

	/* begin block 3 */
		// Start line: 3537
	/* end block 3 */
	// End Line: 3538

	/* begin block 4 */
		// Start line: 3538
	/* end block 4 */
	// End Line: 3539

	/* begin block 5 */
		// Start line: 3544
	/* end block 5 */
	// End Line: 3545

// [D]
int Put(int stream, ulong *pt0)
{
	REPLAY_STREAM *rstream;
	ulong t0;
	PADRECORD *padbuf;

	rstream = &ReplayStreams[stream];

	if (rstream->PadRecordBuffer+1 >= rstream->PadRecordBufferEnd)
		return 0;

	padbuf = rstream->PadRecordBuffer;
	t0 = *pt0;

	if (CameraCnt != 0 && padbuf->run != 0xEE)
	{
		if (padbuf->pad == ((t0 >> 8) & 0xff) &&
			padbuf->analogue == (t0 & 0xff) && 
			padbuf->run != 0x8F)
		{
			padbuf->run++;
			return 1;
		}

		padbuf++;

		padbuf->pad = (t0 >> 8) & 0xFF;
		padbuf->analogue = t0 & 0xFF;
		padbuf->run = 0;

		rstream->PadRecordBuffer = padbuf;

		return 1;
	}

	padbuf->pad = (t0 >> 8) & 0xFF;
	padbuf->analogue = t0 & 0xFF;
	padbuf->run = 0;

	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ RecordWaypoint()
 // line 1479, offset 0x0001b364
	/* begin block 1 */
		// Start line: 3613
	/* end block 1 */
	// End Line: 3614

	/* begin block 2 */
		// Start line: 3616
	/* end block 2 */
	// End Line: 3617

	/* begin block 3 */
		// Start line: 3617
	/* end block 3 */
	// End Line: 3618

/* WARNING: Unknown calling convention yet parameter storage is locked */

void RecordWaypoint(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	int iVar3;

	iVar2 = PlayerCar;
	if (TimeToWay == 0) {
		if (PlayerWaypoints < 0x96) {
			PlayerWaypoints = PlayerWaypoints + 1;
			iVar3 = car_data[PlayerCar].hd.where.t[0];
			iVar1 = iVar3 + 0x200;
			if (iVar1 < 0) {
				iVar1 = iVar3 + 0x5ff;
			}
			PlayerWayRecordPtr->x = (short)(iVar1 >> 10);
			TimeToWay = way_distance;
			iVar1 = car_data[iVar2].hd.where.t[2];
			iVar2 = iVar1 + 0x200;
			if (iVar2 < 0) {
				iVar2 = iVar1 + 0x5ff;
			}
			PlayerWayRecordPtr->y = (short)(iVar2 >> 10);
			PlayerWayRecordPtr = PlayerWayRecordPtr + 1;
		}
		return;
	}
	TimeToWay = TimeToWay + -1;
	return;
	*/
}





