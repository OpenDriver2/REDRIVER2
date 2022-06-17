#include "driver2.h"
#include "cutscene.h"

#include "mission.h"
#include "cars.h"
#include "players.h"
#include "replays.h"
#include "gamesnd.h"
#include "glaunch.h"
#include "civ_ai.h"
#include "pedest.h"
#include "pres.h"
#include "system.h"
#include "camera.h"
#include "main.h"
#include "mc_snd.h"
#include "handling.h"
#include "event.h"
#include "denting.h"
#include "pause.h"
#include "overmap.h"
#include "director.h"
#include "xaplay.h"
#include "overlay.h"

struct CUTSCENE_BUFFER
{
	int numResident;
	u_char residentCutscenes[4];
	char(*residentPointers[4]);

	char* buffer;
	char* currentPointer;

	int bytesFree;
	int reservedSize;
	// char buffer[32*1024];				// was 8192, but we have some free mem now even for PSX. Using malloc.
};

int gSkipInGameCutscene = 0;

int gInGameCutsceneActive = 0;
int gInGameCutsceneDelay = 0;
int gInGameChaseActive = 0;
int gInGameCutsceneID = -1;
int gCutsceneAtEnd = 0;
int gThePlayerCar = -1;

static int CutsceneStreamIndex = 0;
int CutsceneFrameCnt = 0;
int NumCutsceneStreams = 0;
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

// [A]
CUTSCENE_HEADER CutsceneHeader;
CUTSCENE_HEADER ChaseHeader;
int gReChaseAvailable = 0;

static PLAYBACKCAMERA *CutLastChange;
static PLAYBACKCAMERA *CutNextChange;
PLAYBACKCAMERA *CutsceneCamera = NULL;

static int CutsceneCameraOffset = 0;

int LoadInGameCutscene(int subindex);
int TriggerInGameCutsceneSystem(int cutscene);
void SetNullPlayer(int plr);
void SetNullPlayerDontKill(int plr);
void DestroyPlayer(int plr, int fully);
void FindNextCutChange(int cameracnt);
int LoadCutsceneToReplayBuffer(int residentCutscene);
int LoadCutsceneToBuffer(int subindex);
void ShowCutsceneError();
int LoadCutsceneInformation(int cutscene);
void FreeCutsceneBuffer();
int IsCutsceneResident(int cutscene);


#ifndef PSX
char gUserReplayFolderList[MAX_USER_REPLAYS][48];
int gNumUserChases = 0;
int gUserChaseLoaded = -1;

// [A] user replay folders initialization
void InitUserReplays(const char* str)
{
	int quit;
	char* ptr;
	char* strStart;
	gNumUserChases = 0;

	if (!str)
		return;

	ptr = (char*)str;
	strStart = NULL;
	memset(gUserReplayFolderList, 0, sizeof(gUserReplayFolderList));

	quit = 0;

	while(true)
	{
		if (strStart == NULL)
			strStart = ptr;

		// if we're encountered string end go on
		if(*ptr == ',' || *ptr == ' ' || *ptr == '\0')
		{
			if (*ptr == '\0')
				quit = 1;

			*ptr = '\0';
			strcpy(gUserReplayFolderList[gNumUserChases++], strStart);
			strStart = NULL;
		}

		ptr++;

		if (quit)
			break;
	}
}


#endif


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
	CutsceneReplayStart = NULL;
	CutsceneCamera = NULL;
	CutsceneInReplayBuffer = 0;
	CutsceneEventTrigger = 0;
	CutsceneLength = 0;
	BlackBorderHeight = 0;
	gInGameCutsceneDelay = 0;
	gInGameCutsceneID = -1;
	gCutsceneAtEnd = 0;
	JustReturnedFromCutscene = 0;

	gSkipInGameCutscene = 0;

#ifndef PSX
	gUserChaseLoaded = -1;
#endif

	FreeCutsceneBuffer();
}

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
		gSkipInGameCutscene = 0;
		
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

// [D] [T]
void DrawInGameCutscene(void)
{
	TILE *tile;

#ifndef PSX
	PrintXASubtitles(SCREEN_H - 28);
#endif
	
	if (gInGameCutsceneActive == 0 && gInGameCutsceneDelay == 0)
	{
#ifndef PSX
		if(gInGameChaseActive && gUserChaseLoaded != -1 && (CameraCnt - frameStart) < 200)
		{
			// [A] print user chaser name on screen
			char tempStr[80];

			sprintf(tempStr, "%s %s", G_LTXT(GTXT_GetawayIs), gUserReplayFolderList[gUserChaseLoaded]);

			SetTextColour(128, 128, 64);
			PrintString(tempStr, gOverlayXPos, 230);
		}
#endif
		return;
	}

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

	tile->y0 = SCREEN_H - BlackBorderHeight;
	tile->h = BlackBorderHeight;

	addPrim(current->ot, tile);

	current->primptr += sizeof(TILE) * 2;
}

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

		Mission.timer[0].flags = TIMER_FLAG_ACTIVE;

		*car = CutsceneStreamIndex;
		player[0].targetCarId = CutsceneStreamIndex;

		InitLeadHorn();
	}

	car_data[*car].inform = inform;
}

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

	if (CameraCnt < 3 || gInGameCutsceneDelay > 27)
	{
		SavedCameraCarId = player[0].cameraCarId;
		SavedCameraView = cameraview;
		SavedWorldCentreCarId = player[0].worldCentreCarId;
		SavedCameraAngle = gCameraAngle;
		SavedSpoolXZ = player[0].spoolXZ;

		gInGameCutsceneActive = TriggerInGameCutsceneSystem(cutscene);

		if (gInGameCutsceneActive) 
		{
			TerminateSkidding(0);
			TerminateSkidding(1);

			gStopPadReads = 1;
			scr_z = 256;

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

// [A] Function detects user chases and re-chases
int SelectCutsceneFile(char* filename, int init, int subindex)
{
	filename[0] = '\0';

	if (init)
	{
		// try load replacement bundle
#ifndef PSX
		int userId = -1;

		// [A] REDRIVER2 PC - custom user chases
		if (gNumUserChases)
		{
			userId = rand() % (gNumUserChases + 1);

			// if random decides to have no user chase - get og or replacement one
			if (userId == gNumUserChases)
				userId = -1;
		}

		// try loading user chase
		if (userId != -1)
			sprintf(filename, "REPLAYS\\UserChases\\%s\\CUT%d_N.R", (char*)gUserReplayFolderList[userId], gCurrentMissionNumber);

		if (FileExists(filename))
		{
			gUserChaseLoaded = userId;
			gReChaseAvailable = 0;
		}
		else
#endif
		{
			sprintf(filename, "REPLAYS\\ReChases\\CUT%d_N.R", gCurrentMissionNumber);
			gReChaseAvailable = FileExists(filename);
		}
	}

	if (subindex >= 2)
	{
		if (gReChaseAvailable == 1)
		{
			sprintf(filename, "REPLAYS\\ReChases\\CUT%d_N.R", gCurrentMissionNumber);
		}
#ifndef PSX
		else if (gUserChaseLoaded != -1)
		{
			sprintf(filename, "REPLAYS\\UserChases\\%s\\CUT%d_N.R", (char*)gUserReplayFolderList[gUserChaseLoaded], gCurrentMissionNumber);
		}
#endif
	}
	else
	{
		if (gCurrentMissionNumber < 21)
			sprintf(filename, "REPLAYS\\CUT%d.R", gCurrentMissionNumber);
		else
			sprintf(filename, "REPLAYS\\A\\CUT%d.R", gCurrentMissionNumber);
	}

	return FileExists(filename);
}

// [D] [T]
int CalcInGameCutsceneSize(void)
{
	int i, maxSize;
	char filename[64];

	if (NewLevel)
	{
		ClearMem((char*)&CutsceneHeader, sizeof(CUTSCENE_HEADER));
		ClearMem((char*)&ChaseHeader, sizeof(CUTSCENE_HEADER));
		
		// init user/re-chases and load cutscene file header
		if(SelectCutsceneFile(filename, 1, 0))
			LoadfileSeg(filename, (char*)&CutsceneHeader, 0, sizeof(CUTSCENE_HEADER));

		// load re-chase file header
		if(SelectCutsceneFile(filename, 0, 2))
			LoadfileSeg(filename, (char*)&ChaseHeader, 0, sizeof(CUTSCENE_HEADER));

		maxSize = 0;
		for (i = 2; i < 15; i++)
		{
			if (ChaseHeader.data[i].size > maxSize)
				maxSize = ChaseHeader.data[i].size;
		}

		maxSize += MAX(CutsceneHeader.data[0].size, CutsceneHeader.data[1].size);

		CutsceneBuffer.reservedSize = maxSize;
		CutsceneBuffer.buffer = D_MALLOC(CutsceneBuffer.reservedSize);
	}

	ClearMem(CutsceneBuffer.buffer, CutsceneBuffer.reservedSize);

	return CutsceneHeader.maxsize;
}

// [D] [T]
void ReleaseInGameCutscene(void)
{
	int i;

	if (gInGameChaseActive && Mission.ChaseTarget) 
	{
		player[1].padid = -128;
	}

	if (gInGameCutsceneActive != 0)
	{
		RestoreGameVars(-1);

		PingOutAllCivCarsAndCopCars();
		InitCivCars();

		for (i = CutsceneStreamIndex; i < NumReplayStreams; i++)
		{
			if (PlayerStartInfo[i]->flags & 4)
			{
				player[0] = player[i];

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
	NumCutsceneStreams = 0;

	CutsceneReplayStart = NULL;
	CutsceneStreamIndex = 0;
	
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

	gCameraOffset.vx = 0;
	gCameraOffset.vy = 0;
	gCameraOffset.vz = 0;
	gCameraMaxDistance = 0;

	xa_timeout = 120;
}

// [D] [T]
int PreLoadInGameCutscene(int chase)
{
	return LoadInGameCutscene(chase) != 0;
}

// [D] [T]
int CutsceneCameraChange(int cameracnt)
{
	cameracnt -= CutsceneCameraOffset;

	if (CutNextChange->FrameCnt != cameracnt) 
	{
		if (CutNextChange->FrameCnt > cameracnt) 
		{
			IsMovingCamera(CutLastChange, CutNextChange, cameracnt);
			return 0;
		}

		if (CutNextChange->next == 254) 
			return 0;
	}

	if (CutLastChange != CutNextChange && CutNextChange->angle.pad > -1)
		CutNextChange->angle.pad += CutsceneStreamIndex;

	SetPlaybackCamera(CutNextChange);

	if (cameracnt > -1) 
	{
		InvalidCamera(player[0].cameraCarId);

		CutLastChange = CutNextChange;
		FindNextCutChange(cameracnt + 1);
	}

	return 1;
}

// [D] [T]
int LoadInGameCutscene(int subindex)
{
	if (CutsceneInReplayBuffer)
		return LoadCutsceneToBuffer(subindex);

	// first cutscene (intro) always goes to replay buffer
	if (LoadCutsceneToBuffer(subindex))
	{
		if (LoadCutsceneToReplayBuffer(0))
		{
			CutsceneInReplayBuffer = 1;
			PreLoadedCutscene = subindex;
		}

		FreeCutsceneBuffer();
		return 1;
	}

	return 0;
}

// [D] [T]
int TriggerInGameCutsceneSystem(int cutscene)
{
	static char padid[8];

	int slot;
	CAR_DATA *cp;
	REPLAY_STREAM *stream;
	int player_id;
	int bDamageOverride;

	bDamageOverride = 0;

	if(cutscene > -1)
	{
		gHaveInGameCutscene = LoadCutsceneInformation(cutscene);

		if (gHaveInGameCutscene != 0) 
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
							(LONGVECTOR4* )&stream->SourceType.position,
							stream->SourceType.model,
							stream->SourceType.palette,
							&padid[player_id]);

						if (bDamageOverride) 
						{
							slot = player[0].playerCarId;

							cp->ap.needsDenting = 1;
							cp->ap.damage[0] = car_data[slot].ap.damage[0];
							cp->ap.damage[1] = car_data[slot].ap.damage[1];
							cp->ap.damage[2] = car_data[slot].ap.damage[2];
							cp->ap.damage[3] = car_data[slot].ap.damage[3];
							cp->ap.damage[4] = car_data[slot].ap.damage[4];
							cp->ap.damage[5] = car_data[slot].ap.damage[5];

							bDamageOverride = 0;

							cp->totalDamage = car_data[slot].totalDamage;
							DentCar(cp);
						}
					}
					else 
					{
						slot = CreateStationaryCivCar(stream->SourceType.rotation, 0, 1024, 
							(LONGVECTOR4* )&stream->SourceType.position,
							stream->SourceType.model, 
							stream->SourceType.palette, 0);

						if (slot != -1) 
						{
							player[player_id].playerCarId = slot;
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
	}



	ShowCutsceneError();
	return 0;
}

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
	} while (count < MAX_REPLAY_CAMERAS);

	if (!found)
		CutNextChange->next = -2;
}

// [D] [T]
int LoadCutsceneToReplayBuffer(int residentCutscene)
{
	REPLAY_SAVE_HEADER *rheader;
	REPLAY_STREAM_HEADER *sheader;
	char *pt;

	rheader = (REPLAY_SAVE_HEADER *)CutsceneBuffer.residentPointers[residentCutscene];

	if (rheader == NULL || 
		rheader && (rheader->magic != DRIVER2_REPLAY_MAGIC && 
					rheader->magic != REDRIVER2_CHASE_MAGIC ||	// [A]
					rheader->NumReplayStreams == 0) )
	{
		ShowCutsceneError();
		return 0;
	}

	StoreGameVars(-1);

	LoadExtraData(&rheader->ExtraData, 0);

	CutsceneStreamIndex = NumReplayStreams; //rheader->NumReplayStreams;
	NumCutsceneStreams = rheader->NumReplayStreams;
	
	CutsceneReplayStart = replayptr;
	CutsceneEventTrigger = rheader->CutsceneEvent;

	pt = (char *)(rheader + 1);
	
	// add to existing replay streams
	for (int i = NumReplayStreams; i < (NumReplayStreams + rheader->NumReplayStreams); i++)
	{
		int size;
		sheader = (REPLAY_STREAM_HEADER *)pt;
		pt += sizeof(REPLAY_STREAM_HEADER);

		REPLAY_STREAM* destStream = &ReplayStreams[i];

		// copy source type
		destStream->SourceType = sheader->SourceType;

		// init buffers
		destStream->InitialPadRecordBuffer = (PADRECORD*)replayptr;
		destStream->PadRecordBuffer = (PADRECORD*)replayptr;
		destStream->PadRecordBufferEnd = (PADRECORD *)(replayptr + sheader->Size);
		destStream->padCount = sheader->Size;
		destStream->length = sheader->Length;
		destStream->playbackrun = 0;

		size = (sheader->Size + sizeof(PADRECORD)) & -4;

		// copy pad data and advance buffer
		memcpy((u_char*)replayptr, (u_char*)pt, size);
		replayptr += size;

		pt += size;
	}

	NumReplayStreams += NumCutsceneStreams;

	// [A] REDRIVER2 chase replays skip cameras
	if (rheader->magic == REDRIVER2_CHASE_MAGIC)
	{
		CutsceneCamera = NULL;
	}
	else
	{
		// copy cutscene cameras and pings
		CutsceneCamera = (PLAYBACKCAMERA*)replayptr;

		memcpy((u_char*)CutsceneCamera, (u_char*)pt, sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS);
		replayptr += sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS;
		pt += sizeof(PLAYBACKCAMERA) * MAX_REPLAY_CAMERAS;
	}

	memcpy((u_char*)PingBuffer, (u_char*)pt, sizeof(PING_PACKET) * MAX_REPLAY_PINGS);
	PingBufferPos = 0;

	return 1;
}

// [D] [T]
int LoadCutsceneToBuffer(int subindex)
{
	int offset;
	int size;

	CUTSCENE_HEADER header;
	char filename[64];
	
	SelectCutsceneFile(filename, 0, subindex);
	
	printInfo("Loading cutscene '%s' (%d)\n", filename, subindex);

	if (FileExists(filename))
	{
		LoadfileSeg(filename, (char *)&header, 0, sizeof(CUTSCENE_HEADER));

		if (header.data[subindex].offset != 0xffff)
		{
			offset = header.data[subindex].offset * 4;
			size = header.data[subindex].size;

			// [A] if starting game - allocate new buffer
			if (CutsceneBuffer.currentPointer == NULL)
			{
				if(CutsceneInReplayBuffer)
				{
					CutsceneBuffer.currentPointer = CutsceneBuffer.buffer;
					CutsceneBuffer.bytesFree = CutsceneBuffer.reservedSize;
				}
				else
				{
					// obtain temp buffer
					CutsceneBuffer.currentPointer = D_TEMPALLOC(size);
					CutsceneBuffer.bytesFree = size;
					CutsceneBuffer.reservedSize = size;
				}
			}

			/*

			WE DON'T NEED IT ANYMORE! EVEN ON PSX!

			// we keep fallback here
			if (size > CutsceneBuffer.bytesFree)
			{
				printWarning("WARNING - Using leadAI/pathAI buffer for cutscene!\n");

				// load into lead/path AI buffer
				leadAILoaded = 0;
				pathAILoaded = 0;

				CutsceneBuffer.currentPointer = (char*)_other_buffer2;
				CutsceneBuffer.bytesFree = 0xC000;	
			}*/

			LoadfileSeg(filename, CutsceneBuffer.currentPointer, offset, size);

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

// [A] From Code Review
void ShowCutsceneError(void)
{
	RECT16 rect;

	printError("Cutscene initialisation error!\n");
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
	}

	return 0;
}

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
	CutsceneBuffer.bytesFree = CutsceneBuffer.reservedSize;
}

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





