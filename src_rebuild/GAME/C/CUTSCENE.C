#include "DRIVER2.H"
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
#include "SYSTEM.H"
#include "CAMERA.H"
#include "MAIN.H"
#include "MC_SND.H"
#include "HANDLING.H"
#include "EVENT.H"
#include "DENTING.H"
#include "PAUSE.H"
#include "OVERMAP.H"
#include "DIRECTOR.H"

#include "LIBETC.H"
#include "STRINGS.H"
#include "XAPLAY.H"

int gSkipInGameCutscene = 0;

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
static int CutsceneInReplayBuffer = 0;
static int CutsceneLength = 0;
static int BlackBorderHeight = 0;
int JustReturnedFromCutscene = 0;
int CutsceneEventTrigger = 0;

CUTSCENE_BUFFER CutsceneBuffer = { 0 };

static PLAYBACKCAMERA *CutLastChange;
static PLAYBACKCAMERA *CutNextChange;
PLAYBACKCAMERA *CutsceneCamera = NULL;

static int CutsceneCameraOffset = 0;

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

// [D] [T]
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

	gSkipInGameCutscene = 0;

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

// [D] [T]
void HandleInGameCutscene(void)
{
	if (gInGameCutsceneDelay != 0) 
	{
		BlackBorderHeight = gInGameCutsceneDelay;
		gInGameCutsceneDelay++;

		if (gInGameCutsceneDelay > 27)
		{
			TriggerInGameCutscene(gInGameCutsceneID);
			gInGameCutsceneDelay = 0;
			BlackBorderHeight = 28;
		}
	}

	if (gHaveInGameCutscene == 0)
		return;

	if (pauseflag != 0)
		return;

	if (CameraCnt < 2)
		BlackBorderHeight = 28;

	if (CutsceneLength-28 < CutsceneFrameCnt) 
	{
		// disable cutscene skip when it's about to end
		if (gSkipInGameCutscene)
		{
			FastForward = 0;
			gSkipInGameCutscene = 0;
		}
		
		if (BlackBorderHeight > 0)
			BlackBorderHeight--;
	}
	else 
	{
		if (BlackBorderHeight < 28)
			BlackBorderHeight++;
	}

	CutsceneFrameCnt++;

	if (gSkipInGameCutscene)
	{
		// fast forward and stop XA
		FastForward = 1;
		StopXA();
		UnprepareXA();
	}

	if (CutsceneFrameCnt == CutsceneLength) 
	{
		gSkipInGameCutscene = 0;
		gHaveInGameCutscene = 0;

		if (gInGameCutsceneActive != 0)
			JustReturnedFromCutscene = 1;

		ReleaseInGameCutscene();
		InitOverheadMap();
	}
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

// [D] [T]
void DrawInGameCutscene(void)
{
	TILE *tile;

	if (gInGameCutsceneActive == 0 && gInGameCutsceneDelay == 0)
		return;

	tile = (TILE *)current->primptr;
	SetTile(tile);
	tile->r0 = 0;
	tile->g0 = 0;
	tile->b0 = 0;

#ifdef PSX
	tile->x0 = 0;
	tile->w = 320;
#else
	tile->x0 = -500;
	tile->w = 1200;
#endif

	tile->y0 = 0;
	tile->h = BlackBorderHeight;

	addPrim(current->ot, tile);
	tile++;

	SetTile(tile);
	tile->r0 = 0;
	tile->g0 = 0;
	tile->b0 = 0;

#ifdef PSX
	tile->x0 = 0;
	tile->w = 320;
#else
	tile->x0 = -500;
	tile->w = 1200;
#endif

	tile->y0 = 256 - BlackBorderHeight;
	tile->h = BlackBorderHeight;

	addPrim(current->ot, tile);

	current->primptr += sizeof(TILE) * 2;
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

// [D] [T]
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

static int SavedCameraView = 0;
static int SavedWorldCentreCarId = 0;
static VECTOR *SavedSpoolXZ = NULL;
static int SavedCameraCarId = 0;
static int SavedCameraAngle = 0;

// [D] [T]
void TriggerInGameCutscene(int cutscene)
{
	if (IsCutsceneResident(cutscene) == 0)
		return;

	gInGameCutsceneID = cutscene;

	if (CameraCnt < 3 || 27 < gInGameCutsceneDelay)
	{
		SavedCameraCarId = player[0].cameraCarId;
		SavedCameraView = cameraview;
		SavedWorldCentreCarId = player[0].worldCentreCarId;
		SavedCameraAngle = gCameraAngle;
		SavedSpoolXZ = player[0].spoolXZ;

		gInGameCutsceneActive = TriggerInGameCutsceneSystem(cutscene);

		if (gInGameCutsceneActive != 0) 
		{
			TerminateSkidding(0);
			TerminateSkidding(1);

			gStopPadReads = 1;
			scr_z = 0x100;

			if (gCSDestroyPlayer) 
			{
				DestroyPlayer(0, 1);
			}
		}
	}
	else 
	{
		gCutsceneAtEnd = 1;
		gInGameCutsceneDelay = gInGameCutsceneDelay + 1;
	}
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

// [D] [T]
int CalcInGameCutsceneSize(void)
{
	CUTSCENE_HEADER header;
	char filename[64];

	if (gCurrentMissionNumber < 21)
		sprintf(filename, "REPLAYS\\CUT%d.R", gCurrentMissionNumber);
	else 
		sprintf(filename, "REPLAYS\\A\\CUT%d.R", gCurrentMissionNumber);

	if (FileExists(filename) == 0)
		return 0;

	LoadfileSeg(filename, (char *)&header, 0, sizeof(CUTSCENE_HEADER));

	return header.maxsize;
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

// [D] [T]
void ReleaseInGameCutscene(void)
{
	int i;

	if (gInGameChaseActive != 0 && Mission.ChaseTarget != NULL) 
	{
		player[1].padid = -128;
	}

	if (gInGameCutsceneActive != 0)
	{
		PingOutAllCivCarsAndCopCars();
		InitCivCars();

		for (i = CutsceneStreamIndex; i < NumReplayStreams; i++)
		{
			if (PlayerStartInfo[i]->flags & 4)
			{
				memcpy(&player[0], &player[i], sizeof(_PLAYER));

				if (player[0].playerType == 2)
				{
					player[0].pPed->padId = 0;
					SavedWorldCentreCarId = -1;
					SavedSpoolXZ = (VECTOR *)&player[0].pPed->position;
				}
				else
				{
					Swap2Cars(player[0].playerCarId, 0);
					SavedWorldCentreCarId = player[0].playerCarId;

					SavedSpoolXZ = (VECTOR *)car_data[SavedWorldCentreCarId].hd.where.t;

					car_data[SavedWorldCentreCarId].ai.padid = &player[0].padid;
				}

				SavedCameraCarId = SavedWorldCentreCarId;

				DestroyPlayer(i, 0);
			}
			else 
			{
				DestroyPlayer(i, 1);
			}
		}

		gThePlayerCar = -1;
		player[0].targetCarId = -1;

		DestroyCivPedestrians();
		AdjustPlayerCarVolume();

		i = player[0].playerCarId;

		player[0].padid = 0;
		player[0].worldCentreCarId = SavedWorldCentreCarId;
		player[0].spoolXZ = SavedSpoolXZ;
		player[0].cameraCarId = SavedCameraCarId;

		if (i != -1) 
		{
			car_data[i].ai.padid = &player[0].padid;
			car_data[i].controlType = CONTROL_TYPE_PLAYER;
		}

		cameraview = SavedCameraView;
		gCameraAngle = SavedCameraAngle;

		InitCamera(&player[0]);

		player[0].cameraAngle = 0;
		player[0].cameraDist = 1000;

		CutsceneEventTrigger = 0;
	}

	if (CutsceneReplayStart != NULL) 
		replayptr = CutsceneReplayStart;

	NumReplayStreams -= NumCutsceneStreams;

	CutsceneReplayStart = NULL;
	CutsceneStreamIndex = 0;
	NumCutsceneStreams = 0;
	PreLoadedCutscene = -1;
	gHaveInGameCutscene = 0;
	gCSDestroyPlayer = 0;
	CutsceneLength = 0;
	BlackBorderHeight = 0;
	CutsceneCamera = NULL;
	gInGameChaseActive = 0;
	gInGameCutsceneActive = 0;
	CutsceneFrameCnt = 0;
	gInGameCutsceneDelay = 0;
	gStopPadReads = 0;

	xa_timeout = 120;
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

// [D] [T]
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

// [D] [T]
int CutsceneCameraChange(int cameracnt)
{
	cameracnt -= CutsceneCameraOffset;

	if (CutNextChange->FrameCnt != cameracnt) 
	{
		if (cameracnt < CutNextChange->FrameCnt) 
		{
			IsMovingCamera(CutLastChange, CutNextChange, cameracnt);
			return 0;
		}

		if (CutNextChange->next == -2) 
			return 0;
	}

	if (CutLastChange != CutNextChange && -1 < CutNextChange->angle.pad)
		CutNextChange->angle.pad += CutsceneStreamIndex;

	SetPlaybackCamera(CutNextChange);

	if (-1 < cameracnt) 
	{
		InvalidCamera(player[0].cameraCarId);

		CutLastChange = CutNextChange;
		FindNextCutChange(cameracnt + 1);
	}

	return 1;
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

// [D] [T]
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

// [D] [T]
int TriggerInGameCutsceneSystem(int cutscene)
{
	static char padid[8];

	int iVar4;
	_CAR_DATA *cp;
	REPLAY_STREAM *stream;
	int player_id;
	int bDamageOverride;

	bDamageOverride = 0;

	if (cutscene > -1 && (gHaveInGameCutscene = LoadCutsceneInformation(cutscene), gHaveInGameCutscene != 0)) 
	{
		PingOutAllCivCarsAndCopCars();
		InitCivCars();
		DestroyCivPedestrians();

		if (CutsceneStreamIndex <= player[0].playerCarId)
		{
			Swap2Cars(player[0].playerCarId, 0);
			SavedCameraCarId = player[0].cameraCarId;
			SavedWorldCentreCarId = player[0].playerCarId;
			SavedSpoolXZ = player[0].spoolXZ;
		}

		if (CutsceneEventTrigger != 0) 
		{
			TriggerEvent(CutsceneEventTrigger);
		}

		gThePlayerCar = -1;

		if (CutsceneStreamIndex < NumReplayStreams)
		{
			stream = ReplayStreams + CutsceneStreamIndex;
			player_id = CutsceneStreamIndex;

			do {
				PlayerStartInfo[player_id] = &stream->SourceType;

				if ((stream->SourceType.flags & 4) != 0)
				{
					gCSDestroyPlayer = 1;

					if (stream->SourceType.type == 1)
					{
						gThePlayerCar = player_id;

						if (gCutsceneAtEnd != 0 && player[0].playerType == 1)
						{
							stream->SourceType.palette = car_data[player[0].playerCarId].ap.palette;
							stream->SourceType.model = MissionHeader->residentModels[car_data[player[0].playerCarId].ap.model];

							bDamageOverride = 1;
							gCutsceneAtEnd = 0;
						}
					}
				}

				padid[player_id] = -player_id;
				gStartOnFoot = stream->SourceType.type == 2;

				if (gStartOnFoot || (stream->SourceType.flags & 1) == 0)
				{
					TerminateSkidding(player_id);

					cp = &car_data[player_id];

					InitPlayer(&player[player_id], cp,
						stream->SourceType.controlType, 
						stream->SourceType.rotation,
						(long(*)[4])&stream->SourceType.position,
						stream->SourceType.model,
						stream->SourceType.palette,
						&padid[player_id]);

					if (bDamageOverride != 0) 
					{
						iVar4 = player[0].playerCarId;

						cp->ap.needsDenting = 1;
						cp->ap.damage[0] = car_data[iVar4].ap.damage[0];
						cp->ap.damage[1] = car_data[iVar4].ap.damage[1];
						cp->ap.damage[2] = car_data[iVar4].ap.damage[2];
						cp->ap.damage[3] = car_data[iVar4].ap.damage[3];
						cp->ap.damage[4] = car_data[iVar4].ap.damage[4];
						cp->ap.damage[5] = car_data[iVar4].ap.damage[5];

						bDamageOverride = 0;

						cp->totalDamage = car_data[iVar4].totalDamage;
						DentCar(cp);
					}
				}
				else 
				{
					iVar4 = CreateStationaryCivCar(stream->SourceType.rotation, 0, 1024, 
						(long(*)[4])&stream->SourceType.position,
						stream->SourceType.model, 
						stream->SourceType.palette, 0);

					if (iVar4 != -1) 
					{
						player[player_id].playerCarId = iVar4;
						SetNullPlayer(player_id);
					}
				}

				if (player_id == CutsceneStreamIndex)
				{
					if (gStartOnFoot == 0) 
					{
						player[0].spoolXZ = (VECTOR *)car_data[player_id].hd.where.t;
						player[0].worldCentreCarId = CutsceneStreamIndex;
					}
					else 
					{
						player[0].worldCentreCarId = -1;
						player[0].spoolXZ = (VECTOR *)&player[player_id].pPed->position;
					}
				}

				if (CutsceneLength < stream->length)
					CutsceneLength = stream->length;

				stream++;
				player_id++;

			} while (player_id < NumReplayStreams);
		}

		CutsceneCameraOffset = CameraCnt + 1;
		CutNextChange = CutsceneCamera;
		CutLastChange = NULL;

		return 1;
	}

	ShowCutsceneError();
	return 0;
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

// [D] [T]
void SetNullPlayer(int plr)
{
	int carId = player[plr].playerCarId;

	if (carId != -1) 
	{
		car_data[carId].controlType = CONTROL_TYPE_CIV_AI;
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

// [D] [T]
void SetNullPlayerDontKill(int plr)
{
	int carId = player[plr].playerCarId;

	if (carId != -1)
	{
		car_data[carId].controlType = CONTROL_TYPE_CUTSCENE;
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

// [D] [T]
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

// [D] [T]
void FindNextCutChange(int cameracnt)
{
	bool found;
	int nextframe;
	int count;

	found = false;
	nextframe = 100001;
	count = 0;

	do {
		if (cameracnt <= CutsceneCamera[count].FrameCnt && 
			CutsceneCamera[count].FrameCnt < nextframe)
		{
			found = true;
			nextframe = CutsceneCamera[count].FrameCnt;
			CutNextChange = &CutsceneCamera[count];
		}

		count++;
	} while (count < 60);

	if (!found)
		CutNextChange->next = -2;
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

// [D] [T]
int LoadCutsceneToReplayBuffer(int residentCutscene)
{
	REPLAY_SAVE_HEADER *rheader;
	REPLAY_STREAM_HEADER *sheader;
	char *pt;

	rheader = (REPLAY_SAVE_HEADER *)CutsceneBuffer.residentPointers[residentCutscene];

	if (rheader == NULL || rheader && (rheader->magic != 0x14793209 || rheader->NumReplayStreams == 0) )
	{
		ShowCutsceneError();
		return 0;
	}

	CutsceneStreamIndex = NumReplayStreams;
	NumCutsceneStreams = rheader->NumReplayStreams;
	
	CutsceneReplayStart = replayptr;
	CutsceneEventTrigger = rheader->CutsceneEvent;

	pt = (char *)(rheader + 1);
	
	// add to existing replay streams
	for (int i = NumReplayStreams; i < (NumReplayStreams + rheader->NumReplayStreams); i++)
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
		destStream->padCount = sheader->Size;
		destStream->length = sheader->Length;
		destStream->playbackrun = 0;

		int size = (sheader->Size + sizeof(PADRECORD)) & -4;

		// copy pad data and advance buffer
		memcpy(replayptr, pt, size);
		replayptr += size;

		pt += size;
	}

	NumReplayStreams += rheader->NumReplayStreams;

	// copy cutscene cameras and pings
	CutsceneCamera = (PLAYBACKCAMERA *)replayptr;

	memcpy(CutsceneCamera, pt, sizeof(PLAYBACKCAMERA) * 60);		// MAX_CUTSCENE_CAMERAS
	replayptr += sizeof(PLAYBACKCAMERA) * 60;

	pt += sizeof(PLAYBACKCAMERA) * 60;

	memcpy(PingBuffer, pt, sizeof(_PING_PACKET) * 400);				// MAX_REPLAY_PINGS

	PingBufferPos = 0;

	return 1;
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

// [D] [T]
int LoadCutsceneToBuffer(int subindex)
{
	int offset;
	int size;

	CUTSCENE_HEADER header;
	char filename[64];
	char customFilename[64];

	if (gCurrentMissionNumber < 21) 
		sprintf(filename, "REPLAYS\\CUT%d.R", gCurrentMissionNumber);
	else 
		sprintf(filename, "REPLAYS\\A\\CUT%d.R", gCurrentMissionNumber);

	printInfo("Loading cutscene '%s' (%d)\n", filename, subindex);

	if (FileExists(filename))
	{
		LoadfileSeg(filename, (char *)&header, 0, sizeof(CUTSCENE_HEADER));

		if (header.data[subindex].offset != 0xffff)
		{
			offset = header.data[subindex].offset * 4;
			size = header.data[subindex].size;

			// [A] REDRIVER2 - custom cutcenes or chases
			sprintf(customFilename, "REPLAYS\\CUT%d\\%d.D2RP", gCurrentMissionNumber, subindex);

			if (CutsceneBuffer.bytesFree < size) 
			{
				// load into lead/path AI buffer
				leadAILoaded = 0;
				pathAILoaded = 0;

				CutsceneBuffer.currentPointer = _other_buffer2;
				CutsceneBuffer.bytesFree = 0xc000;

				if (FileExists(customFilename))
				{
					printInfo("Custom cutscene replay file loaded\n");
					LoadfileSeg(customFilename, _other_buffer2, 0, size);
				}
				else
					LoadfileSeg(filename, _other_buffer2, offset, size);				
			}
			else 
			{
				if (FileExists(customFilename))
				{
					printInfo("Custom cutscene replay file loaded\n");
					LoadfileSeg(customFilename, _other_buffer2, 0, size);
				}
				else
					LoadfileSeg(filename, CutsceneBuffer.currentPointer, offset, size);
			}

			CutsceneBuffer.residentCutscenes[CutsceneBuffer.numResident] = subindex;
			CutsceneBuffer.residentPointers[CutsceneBuffer.numResident] = CutsceneBuffer.currentPointer;
			CutsceneBuffer.numResident++;
			CutsceneBuffer.currentPointer += size;
			CutsceneBuffer.bytesFree -= size;

			return 1;
		}
	}

	ShowCutsceneError();

	return 0;
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

// [D] [T]
int LoadCutsceneInformation(int cutscene)
{
	int i;

	if (cutscene == PreLoadedCutscene) 
	{
		PreLoadedCutscene = -1;
		return 1;
	}

	ReleaseInGameCutscene();

	for(i = 0; i < 4; i++)
	{
		if (cutscene == CutsceneBuffer.residentCutscenes[i])
		{
			if (LoadCutsceneToReplayBuffer(i))
			{
				CutsceneBuffer.residentCutscenes[i] = 0xFF;
				CutsceneBuffer.residentPointers[i] = NULL;
				return 1;
			}
		}
	};

	return 0;
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

// [D] [T]
void FreeCutsceneBuffer(void)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		CutsceneBuffer.residentCutscenes[i] = -1;
		CutsceneBuffer.residentPointers[i] = NULL;
	}

	CutsceneBuffer.numResident = 0;
	CutsceneBuffer.currentPointer = CutsceneBuffer.buffer;

	CutsceneBuffer.bytesFree = sizeof(CutsceneBuffer.buffer);
	ClearMem(CutsceneBuffer.buffer, sizeof(CutsceneBuffer.buffer));
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

// [D] [T]
int IsCutsceneResident(int cutscene)
{
	int i;

	if (cutscene == PreLoadedCutscene)
		return 1;

	for (i = 0; i < 4; i++)
	{
		if (CutsceneBuffer.residentCutscenes[i] == cutscene)
			return 1;
	}

	return 0;
}





