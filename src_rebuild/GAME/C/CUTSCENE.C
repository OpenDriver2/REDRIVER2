#include "THISDUST.H"
#include "CUTSCENE.H"
#include "MISSION.H"
#include "CARS.H"
#include "PLAYERS.H"
#include "REPLAYS.H"
#include "GAMESND.H"
#include "GLAUNCH.H"
#include "CIV_AI.H"
#include "PEDEST.H"
#include "PRES.H"

#include "LIBETC.H"

int gInGameCutsceneActive = 0;
int gInGameCutsceneDelay = 0;
int gInGameChaseActive = 0;
int gInGameCutsceneID = -1;
int gCutsceneAtEnd = 0;
int gThePlayerCar = -1;

static int CutsceneStreamIndex = 0;
int CutsceneFrameCnt = 0;
static int NumCutsceneStreams = 0;
static int gHaveInGameCutscene = 0;
static int gCSDestroyPlayer = 0;
static int PreLoadedCutscene = -1;
static char *CutsceneReplayStart = NULL;
PLAYBACKCAMERA *CutsceneCamera = NULL;
static int CutsceneInReplayBuffer = 0;
int CutsceneEventTrigger = 0;
static int CutsceneLength = 0;
static int BlackBorderHeight = 0;
int JustReturnedFromCutscene = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ InitInGameCutsceneVariables()
 // line 566, offset 0x000325c0
	/* begin block 1 */
		// Start line: 2383
	/* end block 1 */
	// End Line: 2384

	/* begin block 2 */
		// Start line: 1132
	/* end block 2 */
	// End Line: 1133

	/* begin block 3 */
		// Start line: 2384
	/* end block 3 */
	// End Line: 2385

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitInGameCutsceneVariables(void)
{
	CutsceneStreamIndex = 0;
	CutsceneFrameCnt = 0;
	NumCutsceneStreams = 0;
	gHaveInGameCutscene = 0;
	gInGameChaseActive = 0;
	gInGameCutsceneActive = 0;
	gCSDestroyPlayer = 0;
	PreLoadedCutscene = -1;
	CutsceneReplayStart = (char *)0x0;
	CutsceneCamera = (PLAYBACKCAMERA *)0x0;
	CutsceneInReplayBuffer = 0;
	CutsceneEventTrigger = 0;
	CutsceneLength = 0;
	BlackBorderHeight = 0;
	gInGameCutsceneDelay = 0;
	gInGameCutsceneID = -1;
	gCutsceneAtEnd = 0;
	JustReturnedFromCutscene = 0;

	FreeCutsceneBuffer();
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandleInGameCutscene()
 // line 594, offset 0x0003262c
	/* begin block 1 */
		// Start line: 596
		// Start offset: 0x0003262C

		/* begin block 1.1 */
			// Start line: 631
			// Start offset: 0x0003270C
		/* end block 1.1 */
		// End offset: 0x00032730
		// End Line: 642
	/* end block 1 */
	// End offset: 0x00032740
	// End Line: 644

	/* begin block 2 */
		// Start line: 2446
	/* end block 2 */
	// End Line: 2447

	/* begin block 3 */
		// Start line: 2447
	/* end block 3 */
	// End Line: 2448

	/* begin block 4 */
		// Start line: 2452
	/* end block 4 */
	// End Line: 2453

/* WARNING: Unknown calling convention yet parameter storage is locked */

void HandleInGameCutscene(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	if (gInGameCutsceneDelay != 0) {
		BlackBorderHeight = gInGameCutsceneDelay;
		gInGameCutsceneDelay = gInGameCutsceneDelay + 1;
		if (0x1b < gInGameCutsceneDelay) {
			TriggerInGameCutscene(gInGameCutsceneID);
			gInGameCutsceneDelay = 0;
			BlackBorderHeight = 0x1c;
		}
	}
	if (gHaveInGameCutscene == 0) {
		return;
	}
	if (pauseflag != 0) {
		return;
	}
	if (CameraCnt < 2) {
		BlackBorderHeight = 0x1c;
	}
	if (CutsceneLength + -0x1c < CutsceneFrameCnt) {
		iVar1 = BlackBorderHeight + -1;
		if (BlackBorderHeight < 1) goto LAB_000326f4;
	}
	else {
		iVar1 = BlackBorderHeight + 1;
		if (0x1b < BlackBorderHeight) goto LAB_000326f4;
	}
	BlackBorderHeight = iVar1;
LAB_000326f4:
	CutsceneFrameCnt = CutsceneFrameCnt + 1;
	if (CutsceneFrameCnt == CutsceneLength) {
		gHaveInGameCutscene = 0;
		if (gInGameCutsceneActive != 0) {
			JustReturnedFromCutscene = 1;
		}
		ReleaseInGameCutscene();
		InitOverheadMap();
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawInGameCutscene()
 // line 646, offset 0x00031398
	/* begin block 1 */
		// Start line: 648
		// Start offset: 0x00031398
		// Variables:
	// 		struct TILE *tile; // $s0
	/* end block 1 */
	// End offset: 0x000314E8
	// End Line: 676

	/* begin block 2 */
		// Start line: 1292
	/* end block 2 */
	// End Line: 1293

	/* begin block 3 */
		// Start line: 1293
	/* end block 3 */
	// End Line: 1294

	/* begin block 4 */
		// Start line: 1300
	/* end block 4 */
	// End Line: 1301

/* WARNING: Unknown calling convention yet parameter storage is locked */

void DrawInGameCutscene(void)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	DB *pDVar2;
	ulong *puVar3;
	uint *puVar4;
	uint *puVar5;

	if ((gInGameCutsceneActive != 0) || (gInGameCutsceneDelay != 0)) {
		puVar4 = (uint *)current->primptr;
		SetTile(puVar4);
		*(char *)(puVar4 + 1) = '\0';
		*(char *)((int)puVar4 + 5) = '\0';
		*(char *)((int)puVar4 + 6) = '\0';
		pDVar2 = current;
		sVar1 = (short)BlackBorderHeight;
		*(undefined2 *)(puVar4 + 2) = 0;
		*(undefined2 *)((int)puVar4 + 10) = 0;
		*(undefined2 *)(puVar4 + 3) = 0x140;
		*(short *)((int)puVar4 + 0xe) = sVar1;
		*puVar4 = *puVar4 & 0xff000000 | *pDVar2->ot & 0xffffff;
		puVar3 = pDVar2->ot;
		puVar5 = puVar4 + 4;
		*puVar3 = *puVar3 & 0xff000000 | (uint)puVar4 & 0xffffff;
		SetTile(puVar5);
		*(char *)(puVar4 + 5) = '\0';
		*(char *)((int)puVar4 + 0x15) = '\0';
		*(char *)((int)puVar4 + 0x16) = '\0';
		pDVar2 = current;
		sVar1 = (short)BlackBorderHeight;
		*(undefined2 *)(puVar4 + 6) = 0;
		*(undefined2 *)(puVar4 + 7) = 0x140;
		*(short *)((int)puVar4 + 0x1a) = 0x100 - sVar1;
		*(short *)((int)puVar4 + 0x1e) = sVar1;
		*puVar5 = *puVar5 & 0xff000000 | *pDVar2->ot & 0xffffff;
		*pDVar2->ot = *pDVar2->ot & 0xff000000 | (uint)puVar5 & 0xffffff;
		pDVar2->primptr = pDVar2->primptr + 0x20;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ TriggerChase(int *car /*$s2*/, int cutscene /*$a1*/)
 // line 683, offset 0x000314e8
	/* begin block 1 */
		// Start line: 684
		// Start offset: 0x000314E8
		// Variables:
	// 		void *inform; // $s3
	// 		int i; // $a0
	// 		int length; // $s1

		/* begin block 1.1 */
			// Start line: 695
			// Start offset: 0x00031558
		/* end block 1.1 */
		// End offset: 0x000316A4
		// End Line: 721
	/* end block 1 */
	// End offset: 0x000316EC
	// End Line: 725

	/* begin block 2 */
		// Start line: 1380
	/* end block 2 */
	// End Line: 1381

	/* begin block 3 */
		// Start line: 1388
	/* end block 3 */
	// End Line: 1389

// [D]
void TriggerChase(int *car, int cutscene)
{
	int *inform;
	int i;
	int length;

	inform = car_data[*car].inform;
	car_data[*car].inform = NULL;

	gInGameChaseActive = TriggerInGameCutsceneSystem(gRandomChase);

	if (gInGameChaseActive)
	{
		length = 0;

		// find maximum length of cutscene
		for (i = CutsceneStreamIndex; i < NumReplayStreams; i++)
		{
			if (ReplayStreams[i].length > length)
				length = ReplayStreams[i].length;
		}

		switch (gCurrentMissionNumber)
		{
			case 2:
			case 4:
			case 6:
			case 10:
			case 18:
				Mission.timer[0].count = (15000 + (length / 30) * 3000);
				break;
			default:
				Mission.timer[0].count = (length / 30) * 3000 - 15000;
		}

		Mission.timer[0].flags = 1;

		*car = CutsceneStreamIndex;
		player[0].targetCarId = CutsceneStreamIndex;

		InitLeadHorn();
	}

	car_data[*car].inform = inform;
}



// decompiled code
// original method signature: 
// void /*$ra*/ TriggerInGameCutscene(int cutscene /*$s0*/)
 // line 732, offset 0x00032740
	/* begin block 1 */
		// Start line: 733
		// Start offset: 0x00032740

		/* begin block 1.1 */
			// Start line: 762
			// Start offset: 0x000327F0
		/* end block 1.1 */
		// End offset: 0x0003282C
		// End Line: 769
	/* end block 1 */
	// End offset: 0x0003282C
	// End Line: 770

	/* begin block 2 */
		// Start line: 2637
	/* end block 2 */
	// End Line: 2638

	/* begin block 3 */
		// Start line: 2726
	/* end block 3 */
	// End Line: 2727

void TriggerInGameCutscene(int cutscene)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	iVar1 = IsCutsceneResident(cutscene);
	if (iVar1 != 0) {
		gInGameCutsceneID = cutscene;
		if ((CameraCnt < 3) || (0x1b < gInGameCutsceneDelay)) {
			SavedCameraCarId = (int)player.cameraCarId;
			SavedCameraView = ZEXT14(cameraview);
			SavedWorldCentreCarId = (int)player.worldCentreCarId;
			SavedCameraAngle = gCameraAngle;
			SavedSpoolXZ = player.spoolXZ;
			gInGameCutsceneActive = TriggerInGameCutsceneSystem(cutscene);
			if (gInGameCutsceneActive != 0) {
				TerminateSkidding(0);
				TerminateSkidding(1);
				gStopPadReads = 1;
				scr_z = 0x100;
				if (gCSDestroyPlayer != 0) {
					DestroyPlayer(0, 1);
				}
			}
		}
		else {
			gCutsceneAtEnd = 1;
			gInGameCutsceneDelay = gInGameCutsceneDelay + 1;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CalcInGameCutsceneSize()
 // line 778, offset 0x0003283c
	/* begin block 1 */
		// Start line: 817
		// Start offset: 0x0003283C
		// Variables:
	// 		struct CUTSCENE_HEADER header; // stack offset -136
	// 		char filename[64]; // stack offset -72
	/* end block 1 */
	// End offset: 0x000328C8
	// End Line: 830

	/* begin block 2 */
		// Start line: 2827
	/* end block 2 */
	// End Line: 2828

	/* begin block 3 */
		// Start line: 2865
	/* end block 3 */
	// End Line: 2866

	/* begin block 4 */
		// Start line: 2868
	/* end block 4 */
	// End Line: 2869

/* WARNING: Unknown calling convention yet parameter storage is locked */

int CalcInGameCutsceneSize(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int local_88[16];
	char acStack72[64];

	if (gCurrentMissionNumber < 0x15) {
		sprintf(acStack72, s_REPLAYS_CUT_d_R_0001058c);
	}
	else {
		sprintf(acStack72, s_REPLAYS_A_CUT_d_R_0001059c);
	}
	iVar1 = FileExists(acStack72);
	if (iVar1 == 0) {
		local_88[0] = 0;
	}
	else {
		LoadfileSeg(acStack72, (char *)local_88, 0, 0x40);
	}
	return local_88[0];
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReleaseInGameCutscene()
 // line 838, offset 0x000316ec
	/* begin block 1 */
		// Start line: 840
		// Start offset: 0x000316EC

		/* begin block 1.1 */
			// Start line: 845
			// Start offset: 0x00031748
			// Variables:
		// 		struct STREAM_SOURCE *pinfo; // $a0
		// 		int i; // $s0
		/* end block 1.1 */
		// End offset: 0x00031978
		// End Line: 917
	/* end block 1 */
	// End offset: 0x00031A20
	// End Line: 943

	/* begin block 2 */
		// Start line: 1601
	/* end block 2 */
	// End Line: 1602

	/* begin block 3 */
		// Start line: 1715
	/* end block 3 */
	// End Line: 1716

	/* begin block 4 */
		// Start line: 1716
	/* end block 4 */
	// End Line: 1717

/* WARNING: Unknown calling convention yet parameter storage is locked */

void ReleaseInGameCutscene(void)
{
	UNIMPLEMENTED();
	/*
	PEDESTRIAN *pPVar1;
	_PLAYER *p_Var2;
	_PLAYER *p_Var3;
	long lVar4;
	long lVar5;
	long lVar6;
	int plr;

	if ((gInGameChaseActive != 0) && (DAT_000d7c40 != 0)) {
		_PLAYER_ARRAY_000d979c[0].padid = -0x80;
	}
	if (gInGameCutsceneActive != 0) {
		PingOutAllCivCarsAndCopCars();
		InitCivCars();
		if (CutsceneStreamIndex < NumReplayStreams) {
			plr = CutsceneStreamIndex;
			do {
				if ((PlayerStartInfo8[plr]->flags & 4) == 0) {
					DestroyPlayer(plr, 1);
				}
				else {
					p_Var2 = &player + plr;
					p_Var3 = &player;
					do {
						lVar4 = p_Var2->pos[1];
						lVar5 = p_Var2->pos[2];
						lVar6 = p_Var2->pos[3];
						p_Var3->pos[0] = p_Var2->pos[0];
						p_Var3->pos[1] = lVar4;
						p_Var3->pos[2] = lVar5;
						p_Var3->pos[3] = lVar6;
						p_Var2 = (_PLAYER *)&p_Var2->dir;
						p_Var3 = (_PLAYER *)&p_Var3->dir;
					} while (p_Var2 != (_PLAYER *)&(&player)[plr].crash_timer);
					p_Var3->pos[0] = p_Var2->pos[0];
					if (player.playerType == '\x02') {
						(player.pPed)->padId = '\0';
						SavedWorldCentreCarId = -1;
						pPVar1 = player.pPed;
					}
					else {
						Swap2Cars((int)player.playerCarId, 0);
						SavedWorldCentreCarId = (int)player.playerCarId;
						pPVar1 = (PEDESTRIAN *)&car_data[SavedWorldCentreCarId].hd.where;
						*(undefined4 *)car_data[SavedWorldCentreCarId].ai = 0xd9772;
					}
					SavedSpoolXZ = (VECTOR *)&pPVar1->position;
					SavedCameraCarId = SavedWorldCentreCarId;
					DestroyPlayer(plr, 0);
				}
				plr = plr + 1;
			} while (plr < NumReplayStreams);
		}
		gThePlayerCar = -1;
		player.targetCarId = -1;
		DestroyCivPedestrians();
		AdjustPlayerCarVolume();
		plr = (int)player.playerCarId;
		player.padid = '\0';
		player.worldCentreCarId = (char)SavedWorldCentreCarId;
		player.spoolXZ = SavedSpoolXZ;
		player.cameraCarId = (char)SavedCameraCarId;
		if (plr != -1) {
			*(undefined4 *)car_data[plr].ai = 0xd9772;
			car_data[plr].controlType = '\x01';
		}
		cameraview = (byte)SavedCameraView;
		gCameraAngle = SavedCameraAngle;
		InitCamera(&player);
		player.cameraAngle = 0;
		player.cameraDist = 1000;
		CutsceneEventTrigger = 0;
	}
	if (CutsceneReplayStart != (char *)0x0) {
		replayptr = CutsceneReplayStart;
	}
	NumReplayStreams = NumReplayStreams - NumCutsceneStreams;
	CutsceneReplayStart = (char *)0x0;
	CutsceneStreamIndex = 0;
	NumCutsceneStreams = 0;
	PreLoadedCutscene = -1;
	gHaveInGameCutscene = 0;
	gCSDestroyPlayer = 0;
	CutsceneLength = 0;
	BlackBorderHeight = 0;
	CutsceneCamera = (PLAYBACKCAMERA *)0x0;
	gInGameChaseActive = 0;
	gInGameCutsceneActive = 0;
	CutsceneFrameCnt = 0;
	gInGameCutsceneDelay = 0;
	gStopPadReads = 0;
	xa_timeout = 0x46;
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ PreLoadInGameCutscene(int chase /*$a0*/)
 // line 951, offset 0x000328c8
	/* begin block 1 */
		// Start line: 3054
	/* end block 1 */
	// End Line: 3055

	/* begin block 2 */
		// Start line: 3176
	/* end block 2 */
	// End Line: 3177

	/* begin block 3 */
		// Start line: 3177
	/* end block 3 */
	// End Line: 3178

// [D]
int PreLoadInGameCutscene(int chase)
{
	return LoadInGameCutscene(chase) != 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CutsceneCameraChange(int cameracnt /*$s0*/)
 // line 965, offset 0x000328e8
	/* begin block 1 */
		// Start line: 3204
	/* end block 1 */
	// End Line: 3205

	/* begin block 2 */
		// Start line: 3212
	/* end block 2 */
	// End Line: 3213

int CutsceneCameraChange(int cameracnt)
{
	UNIMPLEMENTED();
	return 0;
	/*
	cameracnt = cameracnt - CutsceneCameraOffset;
	if (CutNextChange->FrameCnt != cameracnt) {
		if (cameracnt < CutNextChange->FrameCnt) {
			IsMovingCamera(CutLastChange, CutNextChange, cameracnt);
			return 0;
		}
		if (CutNextChange->next == -2) {
			return 0;
		}
	}
	if ((CutLastChange != CutNextChange) && (-1 < (CutNextChange->angle).pad)) {
		(CutNextChange->angle).pad = (CutNextChange->angle).pad + (short)CutsceneStreamIndex;
	}
	SetPlaybackCamera(CutNextChange);
	if (-1 < cameracnt) {
		InvalidCamera((int)player.cameraCarId);
		CutLastChange = CutNextChange;
		FindNextCutChange(cameracnt + 1);
	}
	return 1;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadInGameCutscene(int subindex /*$s1*/)
 // line 1010, offset 0x000329b4
	/* begin block 1 */
		// Start line: 1011
		// Start offset: 0x000329B4
		// Variables:
	// 		int ret; // $s0
	/* end block 1 */
	// End offset: 0x00032A34
	// End Line: 1033

	/* begin block 2 */
		// Start line: 3298
	/* end block 2 */
	// End Line: 3299

	/* begin block 3 */
		// Start line: 3301
	/* end block 3 */
	// End Line: 3302

// [D]
int LoadInGameCutscene(int subindex)
{
	if (CutsceneInReplayBuffer)
		return LoadCutsceneToBuffer(subindex);

	if (LoadCutsceneToBuffer(subindex) != 0)
	{
		if (LoadCutsceneToReplayBuffer(0) != 0)
		{
			CutsceneInReplayBuffer = 1;
			PreLoadedCutscene = subindex;
		}

		FreeCutsceneBuffer();
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ TriggerInGameCutsceneSystem(int cutscene /*$a0*/)
 // line 1040, offset 0x00031a20
	/* begin block 1 */
		// Start line: 1041
		// Start offset: 0x00031A20
		// Variables:
	// 		static char padid[8]; // offset 0x0
	// 		int bDamageOverride; // stack offset -64
	// 		int i; // $s2
	// 		int id; // $v1

		/* begin block 1.1 */
			// Start line: 1058
			// Start offset: 0x00031A64

			/* begin block 1.1.1 */
				// Start line: 1094
				// Start offset: 0x00031BC4
				// Variables:
			// 		int car; // $v1
			// 		int model; // $v1
			// 		int palette; // $a1
			/* end block 1.1.1 */
			// End offset: 0x00031C1C
			// End Line: 1105

			/* begin block 1.1.2 */
				// Start line: 1125
				// Start offset: 0x00031CAC

				/* begin block 1.1.2.1 */
					// Start line: 1130
					// Start offset: 0x00031D0C
					// Variables:
				// 		int car; // $v1
				/* end block 1.1.2.1 */
				// End offset: 0x00031D90
				// End Line: 1144
			/* end block 1.1.2 */
			// End offset: 0x00031D90
			// End Line: 1152
		/* end block 1.1 */
		// End offset: 0x00031EA0
		// End Line: 1186
	/* end block 1 */
	// End offset: 0x00031EDC
	// End Line: 1191

	/* begin block 2 */
		// Start line: 2105
	/* end block 2 */
	// End Line: 2106

	/* begin block 3 */
		// Start line: 2203
	/* end block 3 */
	// End Line: 2204

	/* begin block 4 */
		// Start line: 2209
	/* end block 4 */
	// End Line: 2210

int TriggerInGameCutsceneSystem(int cutscene)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uchar uVar1;
	ushort uVar2;
	bool bVar3;
	int iVar4;
	_CAR_DATA *cp;
	REPLAY_STREAM *pRVar5;
	int player_id;
	long(*startPos)[4];
	int iVar6;
	int iVar7;
	int local_40;
	int local_3c;
	int local_38;
	char *local_34;
	long(*local_30)[4];
	int local_2c;

	if ((-1 < cutscene) &&
		(gHaveInGameCutscene = LoadCutsceneInformation(cutscene), gHaveInGameCutscene != 0)) {
		PingOutAllCivCarsAndCopCars();
		InitCivCars();
		DestroyCivPedestrians();
		if (CutsceneStreamIndex <= (int)player.playerCarId) {
			Swap2Cars((int)player.playerCarId, 0);
			SavedCameraCarId = (int)player.cameraCarId;
			SavedWorldCentreCarId = (int)player.playerCarId;
			SavedSpoolXZ = player.spoolXZ;
		}
		if (CutsceneEventTrigger != 0) {
			TriggerEvent(CutsceneEventTrigger);
		}
		gThePlayerCar = -1;
		local_2c = CutsceneStreamIndex * 4;
		if (CutsceneStreamIndex < NumReplayStreams) {
			local_3c = CutsceneStreamIndex * 0x29c;
			iVar6 = CutsceneStreamIndex * 0x74;
			startPos = (long(*)[4])&ReplayStreams[CutsceneStreamIndex].SourceType.position;
			pRVar5 = ReplayStreams + CutsceneStreamIndex;
			local_34 = &(&player)[CutsceneStreamIndex].playerCarId;
			player_id = CutsceneStreamIndex;
			iVar7 = iVar6;
			local_38 = local_3c;
			local_30 = startPos;
			do {
				uVar2 = (pRVar5->SourceType).flags;
				*(REPLAY_STREAM **)((int)PlayerStartInfo8 + local_2c) = pRVar5;
				if (((((uVar2 & 4) != 0) && (gCSDestroyPlayer = 1, (pRVar5->SourceType).type == '\x01')) &&
					(gThePlayerCar = player_id, gCutsceneAtEnd != 0)) && (player.playerType == '\x01')) {
					uVar1 = *(uchar *)(MissionHeader->residentModels +
						(byte)car_data[player.playerCarId].ap.model);
					local_40 = 1;
					(pRVar5->SourceType).palette = car_data[player.playerCarId].ap.palette;
					gCutsceneAtEnd = 0;
					(pRVar5->SourceType).model = uVar1;
				}
				uVar1 = (pRVar5->SourceType).type;
				(&padid_33)[player_id] = -(char)player_id;
				bVar3 = uVar1 == '\x02';
				gStartOnFoot = ZEXT14(bVar3);
				if ((bVar3) || (((pRVar5->SourceType).flags & 1) == 0)) {
					TerminateSkidding(player_id);
					cp = (_CAR_DATA *)((int)car_data[0].hd.where.m + local_38);
					InitPlayer((_PLAYER *)((int)player.pos + iVar6), cp, (pRVar5->SourceType).controlType,
						(uint)(pRVar5->SourceType).rotation, startPos, (uint)(pRVar5->SourceType).model,
						(uint)(pRVar5->SourceType).palette, &padid_33 + player_id);
					if (local_40 != 0) {
						iVar4 = (int)player.playerCarId;
						(&car_data[0].ap.needsDenting)[local_38] = '\x01';
						*(short *)((int)car_data[0].ap.damage + local_38) = car_data[iVar4].ap.damage[0];
						*(short *)((int)car_data[0].ap.damage + local_38 + 2) = car_data[iVar4].ap.damage[1];
						*(short *)((int)car_data[0].ap.damage + local_38 + 4) = car_data[iVar4].ap.damage[2];
						*(short *)((int)car_data[0].ap.damage + local_38 + 6) = car_data[iVar4].ap.damage[3];
						*(short *)((int)car_data[0].ap.damage + local_38 + 8) = car_data[iVar4].ap.damage[4];
						*(short *)((int)car_data[0].ap.damage + local_38 + 10) = car_data[iVar4].ap.damage[5];
						local_40 = 0;
						*(ushort *)((int)&car_data[0].totalDamage + local_38) = car_data[iVar4].totalDamage;
						DentCar(cp);
					}
				}
				else {
					iVar4 = CreateStationaryCivCar
					((uint)(pRVar5->SourceType).rotation, 0, 0x400, local_30,
						(uint)(pRVar5->SourceType).model, (uint)(pRVar5->SourceType).palette, 0);
					if (iVar4 != -1) {
						*local_34 = (char)iVar4;
						SetNullPlayer(player_id);
					}
				}
				if (player_id == CutsceneStreamIndex) {
					if (gStartOnFoot == 0) {
						player.spoolXZ = (VECTOR *)((int)car_data[0].hd.where.t + local_3c);
						player.worldCentreCarId = (char)CutsceneStreamIndex;
					}
					else {
						player.worldCentreCarId = -1;
						player.spoolXZ = (VECTOR *)(*(int *)((int)&player.pPed + iVar7) + 0x14);
					}
				}
				if (CutsceneLength < pRVar5->length) {
					CutsceneLength = pRVar5->length;
				}
				iVar7 = iVar7 + 0x74;
				startPos = (long(*)[4])(startPos + 4 + 1);
				iVar6 = iVar6 + 0x74;
				pRVar5 = pRVar5 + 1;
				player_id = player_id + 1;
				local_3c = local_3c + 0x29c;
				local_38 = local_38 + 0x29c;
				local_34 = local_34 + 0x74;
				local_30 = (long(*)[4])(local_30 + 4 + 1);
				local_2c = local_2c + 4;
			} while (player_id < NumReplayStreams);
		}
		CutsceneCameraOffset = CameraCnt + 1;
		CutNextChange = CutsceneCamera;
		CutLastChange = (PLAYBACKCAMERA *)0x0;
		return 1;
	}
	ShowCutsceneError();
	return 0;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetNullPlayer(int plr /*$a0*/)
 // line 1199, offset 0x00031edc
	/* begin block 1 */
		// Start line: 1200
		// Start offset: 0x00031EDC
	/* end block 1 */
	// End offset: 0x00031F60
	// End Line: 1213

	/* begin block 2 */
		// Start line: 2628
	/* end block 2 */
	// End Line: 2629

	/* begin block 3 */
		// Start line: 2637
	/* end block 3 */
	// End Line: 2638

	/* begin block 4 */
		// Start line: 2640
	/* end block 4 */
	// End Line: 2641

// [D]
void SetNullPlayer(int plr)
{
	int carId = player[plr].playerCarId;

	if (carId != -1) 
	{
		car_data[carId].controlType = 2;
		car_data[carId].ai.c.thrustState = 3;
		car_data[carId].ai.c.ctrlState = 7;
		car_data[carId].ai.c.ctrlNode = NULL;
		player[plr].playerCarId = -1;
	}

	player[plr].playerType = 3;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetNullPlayerDontKill(int plr /*$a0*/)
 // line 1221, offset 0x00031f60
	/* begin block 1 */
		// Start line: 1222
		// Start offset: 0x00031F60
	/* end block 1 */
	// End offset: 0x00031FE0
	// End Line: 1235

	/* begin block 2 */
		// Start line: 2675
	/* end block 2 */
	// End Line: 2676

	/* begin block 3 */
		// Start line: 2684
	/* end block 3 */
	// End Line: 2685

	/* begin block 4 */
		// Start line: 2687
	/* end block 4 */
	// End Line: 2688

// [D]
void SetNullPlayerDontKill(int plr)
{
	int carId = player[plr].playerCarId;

	if (carId != -1)
	{
		car_data[carId].controlType = 7;
		car_data[carId].ai.c.thrustState = 3;
		car_data[carId].ai.c.ctrlState = 7;
		car_data[carId].ai.c.ctrlNode = NULL;
		player[plr].playerCarId = -1;
	}

	player[plr].playerType = 3;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DestroyPlayer(int plr /*$s0*/, int fully /*$a1*/)
 // line 1244, offset 0x00031fe0
	/* begin block 1 */
		// Start line: 2723
	/* end block 1 */
	// End Line: 2724

	/* begin block 2 */
		// Start line: 2733
	/* end block 2 */
	// End Line: 2734

void DestroyPlayer(int plr, int fully)
{
	if (PlayerStartInfo[plr]->flags & 2)
	{
		SetNullPlayerDontKill(plr);
		return;
	}

	if (fully) 
	{
		if (player[plr].playerType == 1 && player[plr].playerCarId != gThePlayerCar) 
			PingOutCar(&car_data[player[plr].playerCarId]);

		if (player[plr].pPed != NULL) 
			DestroyPedestrian(player[plr].pPed);
	}

	player[plr].playerType = 3;
	player[plr].playerCarId = -1;
	player[plr].pPed = NULL;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FindNextCutChange(int cameracnt /*$a0*/)
 // line 1274, offset 0x00032a34
	/* begin block 1 */
		// Start line: 1275
		// Start offset: 0x00032A34
		// Variables:
	// 		int found; // $t0
	// 		int count; // $a3
	// 		int nextframe; // $a2
	/* end block 1 */
	// End offset: 0x00032A98
	// End Line: 1291

	/* begin block 2 */
		// Start line: 3587
	/* end block 2 */
	// End Line: 3588

	/* begin block 3 */
		// Start line: 3829
	/* end block 3 */
	// End Line: 3830

	/* begin block 4 */
		// Start line: 3830
	/* end block 4 */
	// End Line: 3831

void FindNextCutChange(int cameracnt)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	int iVar2;
	PLAYBACKCAMERA *pPVar3;
	int iVar4;
	int iVar5;

	bVar1 = false;
	iVar4 = 0x186a1;
	iVar5 = 0x3b;
	pPVar3 = CutsceneCamera;
	do {
		iVar2 = pPVar3->FrameCnt;
		if ((cameracnt <= iVar2) && (iVar2 < iVar4)) {
			bVar1 = true;
			iVar4 = iVar2;
			CutNextChange = pPVar3;
		}
		iVar5 = iVar5 + -1;
		pPVar3 = pPVar3 + 1;
	} while (-1 < iVar5);
	if (!bVar1) {
		CutNextChange->next = -2;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadCutsceneToReplayBuffer(int residentCutscene /*$a0*/)
 // line 1299, offset 0x00032118
	/* begin block 1 */
		// Start line: 1301
		// Start offset: 0x00032118
		// Variables:
	// 		struct REPLAY_SAVE_HEADER *rheader; // $a1
	// 		struct REPLAY_STREAM_HEADER *sheader; // $t1
	// 		char filename[64]; // stack offset -88
	// 		char *pt; // $s1
	// 		int i; // $a0
	// 		int size; // $s0
	/* end block 1 */
	// End offset: 0x0003243C
	// End Line: 1355

	/* begin block 2 */
		// Start line: 2846
	/* end block 2 */
	// End Line: 2847

	/* begin block 3 */
		// Start line: 2847
	/* end block 3 */
	// End Line: 2848

	/* begin block 4 */
		// Start line: 2852
	/* end block 4 */
	// End Line: 2853

int LoadCutsceneToReplayBuffer(int residentCutscene)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	char *__dest;
	int iVar2;
	REPLAY_STREAM *pRVar3;
	int iVar4;
	int *piVar5;
	_PING_PACKET *p_Var6;
	_PING_PACKET *p_Var7;
	int *piVar8;
	_PING_PACKET _Var9;
	_PING_PACKET _Var10;
	_PING_PACKET _Var11;
	int iVar12;
	long lVar13;
	long lVar14;
	uint __n;
	int *piVar15;

	piVar15 = (int *)CutsceneBuffer.residentPointers[residentCutscene];
	if (((piVar15 == (int *)0x0) || (*piVar15 != 0x14793209)) ||
		(*(_func_4 *)((int)piVar15 + 7) == (_func_4)0x0)) {
		ShowCutsceneError();
		iVar2 = 0;
	}
	else {
		CutsceneStreamIndex = NumReplayStreams;
		NumCutsceneStreams = ZEXT14((byte)*(_func_4 *)((int)piVar15 + 7));
		iVar4 = NumReplayStreams + (uint)(byte)*(_func_4 *)((int)piVar15 + 7);
		CutsceneReplayStart = replayptr;
		CutsceneEventTrigger = ZEXT14((byte)*(_func_4 *)((int)piVar15 + 10));
		bVar1 = NumReplayStreams < iVar4;
		piVar15 = piVar15 + 0x47;
		iVar2 = NumReplayStreams;
		NumReplayStreams = iVar4;
		if (bVar1) {
			do {
				pRVar3 = ReplayStreams + iVar2;
				iVar4 = iVar2 + 1;
				piVar5 = piVar15;
				do {
					iVar12 = piVar5[1];
					lVar13 = piVar5[2];
					lVar14 = piVar5[3];
					*(int *)&pRVar3->SourceType = *piVar5;
					*(int *)&(pRVar3->SourceType).flags = iVar12;
					(pRVar3->SourceType).position.vx = lVar13;
					(pRVar3->SourceType).position.vy = lVar14;
					__dest = replayptr;
					piVar5 = piVar5 + 4;
					pRVar3 = (REPLAY_STREAM *)&(pRVar3->SourceType).position.vz;
				} while (piVar5 != piVar15 + 0xc);
				*(char **)&ReplayStreams[iVar2].InitialPadRecordBuffer = replayptr;
				*(char **)&ReplayStreams[iVar2].PadRecordBuffer = __dest;
				ReplayStreams[iVar2].PadRecordBufferEnd = (PADRECORD *)(__dest + piVar15[0xc]);
				ReplayStreams[iVar2].length = piVar15[0xd];
				ReplayStreams[iVar2].playbackrun = '\0';
				__n = piVar15[0xc] + 3U & 0xfffffffc;
				memcpy(__dest, piVar15 + 0xe, __n);
				replayptr = replayptr + __n;
				piVar15 = (int *)((int)(piVar15 + 0xe) + __n);
				iVar2 = iVar4;
			} while (iVar4 < NumReplayStreams);
		}
		CutsceneCamera = (PLAYBACKCAMERA *)replayptr;
		if ((((uint)piVar15 | (uint)replayptr) & 3) == 0) {
			piVar5 = piVar15;
			piVar8 = (int *)replayptr;
			do {
				iVar4 = piVar5[1];
				iVar12 = piVar5[2];
				iVar2 = piVar5[3];
				*piVar8 = *piVar5;
				piVar8[1] = iVar4;
				piVar8[2] = iVar12;
				piVar8[3] = iVar2;
				piVar5 = piVar5 + 4;
				piVar8 = piVar8 + 4;
			} while (piVar5 != piVar15 + 0x21c);
		}
		else {
			piVar5 = piVar15;
			piVar8 = (int *)replayptr;
			do {
				iVar2 = piVar5[1];
				iVar4 = piVar5[2];
				iVar12 = piVar5[3];
				*piVar8 = *piVar5;
				piVar8[1] = iVar2;
				piVar8[2] = iVar4;
				piVar8[3] = iVar12;
				piVar5 = piVar5 + 4;
				piVar8 = piVar8 + 4;
			} while (piVar5 != piVar15 + 0x21c);
		}
		p_Var7 = (_PING_PACKET *)(piVar15 + 0x21c);
		replayptr = replayptr + 0x870;
		p_Var6 = PingBuffer;
		if ((((uint)p_Var7 | (uint)PingBuffer) & 3) == 0) {
			do {
				_Var10 = p_Var7[1];
				_Var11 = p_Var7[2];
				_Var9 = p_Var7[3];
				*p_Var6 = *p_Var7;
				p_Var6[1] = _Var10;
				p_Var6[2] = _Var11;
				p_Var6[3] = _Var9;
				p_Var7 = p_Var7 + 4;
				p_Var6 = p_Var6 + 4;
			} while (p_Var7 != (_PING_PACKET *)(piVar15 + 0x3ac));
		}
		else {
			do {
				_Var9 = p_Var7[1];
				_Var10 = p_Var7[2];
				_Var11 = p_Var7[3];
				*p_Var6 = *p_Var7;
				p_Var6[1] = _Var9;
				p_Var6[2] = _Var10;
				p_Var6[3] = _Var11;
				p_Var7 = p_Var7 + 4;
				p_Var6 = p_Var6 + 4;
			} while (p_Var7 != (_PING_PACKET *)(piVar15 + 0x3ac));
		}
		PingBufferPos = 0;
		iVar2 = 1;
	}
	return iVar2;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadCutsceneToBuffer(int subindex /*$s3*/)
 // line 1362, offset 0x0003243c
	/* begin block 1 */
		// Start line: 1363
		// Start offset: 0x0003243C
		// Variables:
	// 		struct CUTSCENE_HEADER header; // stack offset -440
	// 		struct REPLAY_SAVE_HEADER rheader; // stack offset -376
	// 		char filename[64]; // stack offset -88
	// 		int offset; // $a2
	// 		int size; // $s0
	/* end block 1 */
	// End offset: 0x000325C0
	// End Line: 1440

	/* begin block 2 */
		// Start line: 3041
	/* end block 2 */
	// End Line: 3042

	/* begin block 3 */
		// Start line: 3049
	/* end block 3 */
	// End Line: 3050

	/* begin block 4 */
		// Start line: 3090
	/* end block 4 */
	// End Line: 3091

int LoadCutsceneToBuffer(int subindex)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int offset;
	uint loadsize;
	char acStack440[4];
	ushort auStack436[174];
	char acStack88[64];

	if (gCurrentMissionNumber < 0x15) {
		sprintf(acStack88, s_REPLAYS_CUT_d_R_0001058c);
	}
	else {
		sprintf(acStack88, s_REPLAYS_A_CUT_d_R_0001059c);
	}
	offset = FileExists(acStack88);
	if (offset != 0) {
		LoadfileSeg(acStack88, acStack440, 0, 0x40);
		if (auStack436[subindex * 2] != 0xffff) {
			offset = (uint)auStack436[subindex * 2] << 2;
			loadsize = (uint)auStack436[subindex * 2 + 1];
			if (CutsceneBuffer.bytesFree < (int)loadsize) {
				leadAILoaded = 0;
				pathAILoaded = 0;
				CutsceneBuffer.currentPointer = popNode;
				CutsceneBuffer.bytesFree = 0xc000;
				LoadfileSeg(acStack88, (char *)popNode, offset, loadsize);
			}
			else {
				LoadfileSeg(acStack88, (char *)CutsceneBuffer.currentPointer, offset, loadsize);
			}
			CutsceneBuffer.residentCutscenes[CutsceneBuffer.numResident] = (uchar)subindex;
			CutsceneBuffer.residentPointers[CutsceneBuffer.numResident] = CutsceneBuffer.currentPointer;
			CutsceneBuffer.numResident = CutsceneBuffer.numResident + 1;
			CutsceneBuffer.currentPointer = (code *)((char *)CutsceneBuffer.currentPointer + loadsize);
			CutsceneBuffer.bytesFree = CutsceneBuffer.bytesFree - loadsize;
			return 1;
		}
	}
	ShowCutsceneError();
	return 0;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ShowCutsceneError()
 // line 1442, offset 0x00032c08
	/* begin block 1 */
		// Start line: 4288
	/* end block 1 */
	// End Line: 4289

	/* begin block 2 */
		// Start line: 2884
	/* end block 2 */
	// End Line: 2885

	/* begin block 3 */
		// Start line: 4309
	/* end block 3 */
	// End Line: 4310

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [A] From Code Review
void ShowCutsceneError(void)
{
	RECT16 rect;

	printf("Cutscene initialisation error!\n");
	SetDispMask(0);
	DrawSync(0);

	rect.x = 0;
	rect.y = 0;
	rect.w = 320;
	rect.h = 256;

	ClearImage2(&rect, 0,0,0);
	DrawSync(0);

	SetTextColour(128, 0, 0);
	PrintStringCentred("CUTSCENE ERROR!", 0x78);

	DrawSync(0);
	SetDispMask(1);

	VSync(20);
}



// decompiled code
// original method signature: 
// int /*$ra*/ LoadCutsceneInformation(int cutscene /*$s2*/)
 // line 1471, offset 0x00032a98
	/* begin block 1 */
		// Start line: 1472
		// Start offset: 0x00032A98
		// Variables:
	// 		int i; // $s1
	/* end block 1 */
	// End offset: 0x00032B54
	// End Line: 1498

	/* begin block 2 */
		// Start line: 4048
	/* end block 2 */
	// End Line: 4049

	/* begin block 3 */
		// Start line: 4229
	/* end block 3 */
	// End Line: 4230

	/* begin block 4 */
		// Start line: 4232
	/* end block 4 */
	// End Line: 4233

int LoadCutsceneInformation(int cutscene)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int residentCutscene;
	int iVar1;
	byte *pbVar2;

	if (cutscene == PreLoadedCutscene) {
		PreLoadedCutscene = -1;
		residentCutscene = 1;
	}
	else {
		ReleaseInGameCutscene();
		pbVar2 = CutsceneBuffer.residentCutscenes;
		residentCutscene = 0;
		do {
			if ((cutscene == (uint)*pbVar2) &&
				(iVar1 = LoadCutsceneToReplayBuffer(residentCutscene), iVar1 != 0)) {
				*pbVar2 = 0xff;
				CutsceneBuffer.residentPointers[residentCutscene] = (_func_4 *)0x0;
				return 1;
			}
			iVar1 = residentCutscene + 1;
			pbVar2 = CutsceneBuffer.residentCutscenes + residentCutscene + 1;
			residentCutscene = iVar1;
		} while (iVar1 < 4);
		residentCutscene = 0;
	}
	return residentCutscene;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ FreeCutsceneBuffer()
 // line 1505, offset 0x00032b54
	/* begin block 1 */
		// Start line: 1507
		// Start offset: 0x00032B54
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x00032BC0
	// End Line: 1518

	/* begin block 2 */
		// Start line: 4307
	/* end block 2 */
	// End Line: 4308

	/* begin block 3 */
		// Start line: 4315
	/* end block 3 */
	// End Line: 4316

	/* begin block 4 */
		// Start line: 4316
	/* end block 4 */
	// End Line: 4317

	/* begin block 5 */
		// Start line: 4318
	/* end block 5 */
	// End Line: 4319

/* WARNING: Unknown calling convention yet parameter storage is locked */

void FreeCutsceneBuffer(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	_func_4 **pp_Var2;

	iVar1 = 0;
	pp_Var2 = CutsceneBuffer.residentPointers;
	do {
		CutsceneBuffer.residentCutscenes[iVar1] = -1;
		*pp_Var2 = (_func_4 *)0x0;
		iVar1 = iVar1 + 1;
		pp_Var2 = pp_Var2 + 1;
	} while (iVar1 < 4);
	CutsceneBuffer.numResident = 0;
	CutsceneBuffer.currentPointer = CutsceneBuffer.buffer;
	CutsceneBuffer.bytesFree = 0x2000;
	ClearMem(CutsceneBuffer.buffer, 0x2000);
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ IsCutsceneResident(int cutscene /*$a0*/)
 // line 1520, offset 0x00032bc0
	/* begin block 1 */
		// Start line: 1521
		// Start offset: 0x00032BC0
		// Variables:
	// 		int i; // $a1
	/* end block 1 */
	// End offset: 0x00032C08
	// End Line: 1533

	/* begin block 2 */
		// Start line: 4349
	/* end block 2 */
	// End Line: 4350

	/* begin block 3 */
		// Start line: 4352
	/* end block 3 */
	// End Line: 4353

	/* begin block 4 */
		// Start line: 4355
	/* end block 4 */
	// End Line: 4356

int IsCutsceneResident(int cutscene)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte *pbVar1;
	int iVar2;
	int iVar3;

	if (cutscene != PreLoadedCutscene) {
		pbVar1 = CutsceneBuffer.residentCutscenes;
		iVar2 = 0;
		while (iVar3 = iVar2 + 1, cutscene != (uint)*pbVar1) {
			pbVar1 = CutsceneBuffer.residentCutscenes + iVar2 + 1;
			iVar2 = iVar3;
			if (3 < iVar3) {
				return 0;
			}
		}
	}
	return 1;
	*/
}





