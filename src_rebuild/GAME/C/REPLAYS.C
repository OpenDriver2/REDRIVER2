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

char AnalogueUnpack[] = { 0, 0xCD, 0xC1, 0xB5, 0xA9, 0x9D, 0x91, 0x85, 0, 0x33, 0x3F, 0x4B, 0x57, 0x63, 0x6F, 0x7B };

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

		PlayerWayRecordPtr = (SXYPAIR *)(ReplayStart + sizeof(REPLAY_PARAMETER_BLOCK));

		PlaybackCamera = (PLAYBACKCAMERA *)((char*)PlayerWayRecordPtr + sizeof(SXYPAIR) * 150);

		PingBuffer = (_PING_PACKET *)((char*)PlaybackCamera + sizeof(PLAYBACKCAMERA) * 60);
		setMem8((u_char*)PingBuffer, -1, sizeof(_PING_PACKET) * 400);

		replayptr = (char*)PingBuffer + sizeof(_PING_PACKET) * 400;

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
			ReplayStreams[i].PadRecordBuffer = ReplayStreams[0].InitialPadRecordBuffer;
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

int LoadReplayFromBuffer(char *buffer)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	char *__dest;
	int iVar2;
	REPLAY_STREAM *pRVar3;
	undefined4 *puVar4;
	SXYPAIR *pSVar5;
	long *plVar6;
	_PING_PACKET *p_Var7;
	undefined4 uVar8;
	MISSION_DATA *pMVar9;
	undefined4 uVar10;
	SXYPAIR *pSVar11;
	PLAYBACKCAMERA *pPVar12;
	_PING_PACKET *p_Var13;
	_PING_PACKET _Var14;
	SXYPAIR SVar15;
	_PING_PACKET _Var16;
	long lVar17;
	SXYPAIR SVar18;
	_PING_PACKET _Var19;
	long lVar20;
	undefined4 uVar21;
	SXYPAIR SVar22;
	long lVar23;
	uint __n;
	undefined4 *puVar24;
	int iVar25;

	replayptr = &DAT_001fabbc;
	ReplayStart = &DAT_001fabbc;
	iVar2 = 0;
	if (*(int *)buffer == 0x14793209) {
		GameLevel = ZEXT14((byte)buffer[4]);
		GameType = buffer[5];
		gCurrentMissionNumber = *(int *)(buffer + 0xfc);
		NumReplayStreams = ZEXT14((byte)buffer[7]);
		NumPlayers = buffer[8];
		gRandomChase = ZEXT14((byte)buffer[9]);
		CutsceneEventTrigger = ZEXT14((byte)buffer[10]);
		pMVar9 = &MissionEndData;
		gCopDifficultyLevel = ZEXT14((byte)buffer[0xb]);
		puVar4 = (undefined4 *)(buffer + 0xc);
		ActiveCheats = *(undefined4 *)(buffer + 0xf0);
		wantedCar[0] = *(int *)(buffer + 0xf4);
		wantedCar[1] = *(int *)(buffer + 0xf8);
		puVar24 = (undefined4 *)(buffer + 0x11c);
		do {
			lVar17 = puVar4[1];
			lVar20 = puVar4[2];
			lVar23 = puVar4[3];
			*(undefined4 *)&pMVar9->PlayerPos = *puVar4;
			(pMVar9->PlayerPos).vx = lVar17;
			(pMVar9->PlayerPos).vy = lVar20;
			(pMVar9->PlayerPos).vz = lVar23;
			puVar4 = puVar4 + 4;
			pMVar9 = (MISSION_DATA *)&(pMVar9->PlayerPos).felony;
		} while (puVar4 != (undefined4 *)(buffer + 0xec));
		iVar2 = 0;
		bVar1 = 0 < NumReplayStreams;
		*(undefined4 *)&pMVar9->PlayerPos = *puVar4;
		if (bVar1) {
			do {
				pRVar3 = ReplayStreams + iVar2;
				iVar25 = iVar2 + 1;
				puVar4 = puVar24;
				do {
					uVar21 = puVar4[1];
					lVar17 = puVar4[2];
					lVar20 = puVar4[3];
					*(undefined4 *)&pRVar3->SourceType = *puVar4;
					*(undefined4 *)&(pRVar3->SourceType).flags = uVar21;
					(pRVar3->SourceType).position.vx = lVar17;
					(pRVar3->SourceType).position.vy = lVar20;
					__dest = replayptr;
					puVar4 = puVar4 + 4;
					pRVar3 = (REPLAY_STREAM *)&(pRVar3->SourceType).position.vz;
				} while (puVar4 != puVar24 + 0xc);
				*(char **)&ReplayStreams[iVar2].InitialPadRecordBuffer = replayptr;
				*(char **)&ReplayStreams[iVar2].PadRecordBuffer = __dest;
				ReplayStreams[iVar2].PadRecordBufferEnd = (PADRECORD *)(__dest + puVar24[0xc]);
				ReplayStreams[iVar2].length = puVar24[0xd];
				ReplayStreams[iVar2].playbackrun = '\0';
				__n = puVar24[0xc] + 3 & 0xfffffffc;
				memcpy(__dest, puVar24 + 0xe, __n);
				replayptr = replayptr + __n;
				puVar24 = (undefined4 *)((int)(puVar24 + 0xe) + __n);
				iVar2 = iVar25;
			} while (iVar25 < NumReplayStreams);
		}
		__dest = replayptr;
		ReplayParameterPtr = (REPLAY_PARAMETER_BLOCK *)replayptr;
		uVar21 = puVar24[1];
		uVar8 = puVar24[2];
		uVar10 = puVar24[3];
		*(undefined4 *)replayptr = *puVar24;
		*(undefined4 *)(__dest + 4) = uVar21;
		*(undefined4 *)(__dest + 8) = uVar8;
		*(undefined4 *)(__dest + 0xc) = uVar10;
		*(undefined4 *)(__dest + 0x10) = puVar24[4];
		pSVar5 = (SXYPAIR *)(puVar24 + 5);
		pSVar11 = (SXYPAIR *)(replayptr + 0x14);
		PlayerWayRecordPtr = pSVar11;
		replayptr = (char *)pSVar11;
		if ((((uint)pSVar5 | (uint)pSVar11) & 3) == 0) {
			do {
				SVar22 = pSVar5[1];
				SVar15 = pSVar5[2];
				SVar18 = pSVar5[3];
				*pSVar11 = *pSVar5;
				pSVar11[1] = SVar22;
				pSVar11[2] = SVar15;
				pSVar11[3] = SVar18;
				pSVar5 = pSVar5 + 4;
				pSVar11 = pSVar11 + 4;
			} while (pSVar5 != (SXYPAIR *)(puVar24 + 0x99));
		}
		else {
			do {
				SVar15 = pSVar5[1];
				SVar18 = pSVar5[2];
				SVar22 = pSVar5[3];
				*pSVar11 = *pSVar5;
				pSVar11[1] = SVar15;
				pSVar11[2] = SVar18;
				pSVar11[3] = SVar22;
				pSVar5 = pSVar5 + 4;
				pSVar11 = pSVar11 + 4;
			} while (pSVar5 != (SXYPAIR *)(puVar24 + 0x99));
		}
		plVar6 = puVar24 + 0x9b;
		SVar15 = pSVar5[1];
		*pSVar11 = *pSVar5;
		pSVar11[1] = SVar15;
		pPVar12 = (PLAYBACKCAMERA *)(replayptr + 600);
		replayptr = (char *)pPVar12;
		PlaybackCamera = pPVar12;
		if ((((uint)plVar6 | (uint)pPVar12) & 3) == 0) {
			do {
				lVar17 = plVar6[1];
				lVar20 = plVar6[2];
				lVar23 = plVar6[3];
				(pPVar12->position).vx = *plVar6;
				(pPVar12->position).vy = lVar17;
				(pPVar12->position).vz = lVar20;
				*(long *)&pPVar12->angle = lVar23;
				plVar6 = plVar6 + 4;
				pPVar12 = (PLAYBACKCAMERA *)&(pPVar12->angle).vz;
			} while (plVar6 != puVar24 + 0x2b7);
		}
		else {
			do {
				lVar17 = plVar6[1];
				lVar20 = plVar6[2];
				lVar23 = plVar6[3];
				(pPVar12->position).vx = *plVar6;
				(pPVar12->position).vy = lVar17;
				(pPVar12->position).vz = lVar20;
				*(long *)&pPVar12->angle = lVar23;
				plVar6 = plVar6 + 4;
				pPVar12 = (PLAYBACKCAMERA *)&(pPVar12->angle).vz;
			} while (plVar6 != puVar24 + 0x2b7);
		}
		p_Var13 = (_PING_PACKET *)(puVar24 + 0x2b7);
		PingBufferPos = 0;
		p_Var7 = (_PING_PACKET *)(replayptr + 0x870);
		replayptr = (char *)p_Var7;
		PingBuffer = p_Var7;
		if ((((uint)p_Var13 | (uint)p_Var7) & 3) == 0) {
			do {
				_Var16 = p_Var13[1];
				_Var19 = p_Var13[2];
				_Var14 = p_Var13[3];
				*p_Var7 = *p_Var13;
				p_Var7[1] = _Var16;
				p_Var7[2] = _Var19;
				p_Var7[3] = _Var14;
				p_Var13 = p_Var13 + 4;
				p_Var7 = p_Var7 + 4;
			} while (p_Var13 != (_PING_PACKET *)(puVar24 + 0x447));
		}
		else {
			do {
				_Var14 = p_Var13[1];
				_Var16 = p_Var13[2];
				_Var19 = p_Var13[3];
				*p_Var7 = *p_Var13;
				p_Var7[1] = _Var14;
				p_Var7[2] = _Var16;
				p_Var7[3] = _Var19;
				p_Var13 = p_Var13 + 4;
				p_Var7 = p_Var7 + 4;
			} while (p_Var13 != (_PING_PACKET *)(puVar24 + 0x447));
		}
		puVar4 = puVar24 + 0x447;
		replayptr = replayptr + 0x640;
		iVar2 = 1;
		if (*(int *)(buffer + 0x100) == -0x6e7d8c9c) {
			pMVar9 = &MissionStartData;
			if (((uint)puVar4 & 3) == 0) {
				do {
					lVar17 = puVar4[1];
					lVar20 = puVar4[2];
					lVar23 = puVar4[3];
					*(undefined4 *)&pMVar9->PlayerPos = *puVar4;
					(pMVar9->PlayerPos).vx = lVar17;
					(pMVar9->PlayerPos).vy = lVar20;
					(pMVar9->PlayerPos).vz = lVar23;
					puVar4 = puVar4 + 4;
					pMVar9 = (MISSION_DATA *)&(pMVar9->PlayerPos).felony;
				} while (puVar4 != puVar24 + 0x47f);
			}
			else {
				do {
					lVar17 = puVar4[1];
					lVar20 = puVar4[2];
					lVar23 = puVar4[3];
					*(undefined4 *)&pMVar9->PlayerPos = *puVar4;
					(pMVar9->PlayerPos).vx = lVar17;
					(pMVar9->PlayerPos).vy = lVar20;
					(pMVar9->PlayerPos).vz = lVar23;
					puVar4 = puVar4 + 4;
					pMVar9 = (MISSION_DATA *)&(pMVar9->PlayerPos).felony;
				} while (puVar4 != puVar24 + 0x47f);
			}
			*(undefined4 *)&pMVar9->PlayerPos = *puVar4;
			gHaveStoredData = 1;
			iVar2 = 1;
		}
	}
	return iVar2;*/
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

int LoadAttractReplay(int mission)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	char acStack40[32];

	sprintf(acStack40, s_REPLAYS_ATTRACT__d_00010448, mission);
	iVar1 = FileExists(acStack40);
	if ((iVar1 == 0) || (iVar1 = Loadfile(acStack40, &DAT_000f3000), iVar1 == 0)) {
		iVar1 = 0;
	}
	else {
		iVar1 = LoadReplayFromBuffer(&DAT_000f3000);
	}
	return iVar1;
	*/
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

int cjpPlay(int stream, ulong *ppad, char *psteer, char *ptype)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	uint uVar2;
	ulong local_18[2];

	iVar1 = Get(stream, local_18);
	uVar2 = local_18[0] >> 8 & 0xf;
	if (uVar2 == 0) {
		*psteer = '\0';
		*ptype = '\0';
	}
	else {
		*psteer = AnalogueUnpack[uVar2];
		*ptype = '\x04';
	}
	*ppad = local_18[0] & 0xf0fc;
	return iVar1;
	*/
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

void cjpRecord(int stream, ulong *ppad, char *psteer, char *ptype)
{
	UNIMPLEMENTED();
	/*
	REPLAY_PARAMETER_BLOCK *pRVar1;
	int iVar2;
	int iVar3;
	uint uVar4;
	ulong local_20[2];

	if ((-1 < stream) && (stream < NumReplayStreams)) {
		local_20[0] = *ppad;
		iVar3 = (int)*psteer;
		RecordWaypoint();
		if ((*ptype & 4U) == 0) {
			uVar4 = 0;
		}
		else {
			if (iVar3 < -0x2d) {
				iVar2 = -0x2d - iVar3 >> 0x1f;
				uVar4 = (((-0x2d - iVar3) / 6 + iVar2 >> 1) - iVar2) + 1;
			}
			else {
				if (iVar3 < 0x2e) {
					uVar4 = 8;
				}
				else {
					iVar2 = iVar3 + -0x2d >> 0x1f;
					uVar4 = (((iVar3 + -0x2d) / 6 + iVar2 >> 1) - iVar2) + 9;
				}
			}
		}
		local_20[0] = local_20[0] & 0xf0fc | (uVar4 & 0xf) << 8;
		iVar2 = Put(stream, local_20);
		iVar3 = CameraCnt;
		pRVar1 = ReplayParameterPtr;
		if (iVar2 == 0) {
			gOutOfTape = 1;
		}
		else {
			if (((NoPlayerControl == 0) && (ClearCameras = 1, ReplayMode != 3)) && (ReplayMode != 8)) {
				ReplayStreams[stream].length = CameraCnt;
				pRVar1->RecordingEnd = iVar3;
			}
		}
		uVar4 = local_20[0] >> 8 & 0xf;
		if (uVar4 == 0) {
			*psteer = '\0';
			*ptype = '\0';
		}
		else {
			*psteer = AnalogueUnpack[uVar4];
			*ptype = '\x04';
		}
		*ppad = local_20[0] & 0xf0fc;
	}
	return;
	*/
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

	replayptr = (char *)(stream->PadRecordBufferEnd+1);
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

int Get(int stream, ulong *pt0)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uchar uVar1;
	char cVar2;
	PADRECORD *pPVar3;

	if (stream < NumReplayStreams) {
		pPVar3 = ReplayStreams[stream].PadRecordBuffer;
		if (pPVar3 + 1 <= ReplayStreams[stream].PadRecordBufferEnd) {
			uVar1 = pPVar3->pad;
			cVar2 = pPVar3->analogue;
			if (ReplayStreams[stream].playbackrun < pPVar3->run) {
				ReplayStreams[stream].playbackrun = ReplayStreams[stream].playbackrun + 1;
			}
			else {
				ReplayStreams[stream].PadRecordBuffer = pPVar3 + 1;
				ReplayStreams[stream].playbackrun = '\0';
			}
			*pt0 = (uint)CONCAT11(uVar1, cVar2);
			return 1;
		}
	}
	*pt0 = 0x10;
	return 0;
	*/
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

int Put(int stream, ulong *pt0)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uchar uVar1;
	uchar uVar2;
	uint uVar3;
	PADRECORD *pPVar4;
	PADRECORD **ppPVar5;

	pPVar4 = ReplayStreams[stream].PadRecordBuffer;
	uVar3 = *pt0;
	ppPVar5 = &ReplayStreams[stream].PadRecordBuffer;
	if (ReplayStreams[stream].PadRecordBufferEnd <= pPVar4 + 1) {
		return 0;
	}
	uVar2 = (uchar)(uVar3 >> 8);
	if (CameraCnt != 0) {
		uVar1 = pPVar4->run;
		if (uVar1 != -0x12) {
			if ((((uint)pPVar4->pad == (uVar3 >> 8 & 0xff)) &&
				((uint)(byte)pPVar4->analogue == (uVar3 & 0xff))) && (uVar1 != -0x71)) {
				pPVar4->run = uVar1 + '\x01';
				return 1;
			}
			pPVar4 = *ppPVar5;
			*ppPVar5 = pPVar4 + 1;
			pPVar4[1].pad = uVar2;
			(*ppPVar5)->analogue = (char)uVar3;
			(*ppPVar5)->run = '\0';
			return 1;
		}
	}
	pPVar4->pad = uVar2;
	(ReplayStreams[stream].PadRecordBuffer)->analogue = (char)uVar3;
	(ReplayStreams[stream].PadRecordBuffer)->run = '\0';
	return 1;
	*/
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





