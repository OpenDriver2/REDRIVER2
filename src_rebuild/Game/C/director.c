#include "driver2.h"
#include "director.h"
#include "camera.h"
#include "players.h"
#include "event.h"
#include "overmap.h"
#include "replays.h"
#include "cutscene.h"
#include "cars.h"
#include "pause.h"
#include "main.h"
#include "glaunch.h"
#include "dr2roads.h"
#include "spool.h"
#include "objcoll.h"
#include "overlay.h"
#include "pres.h"
#include "sound.h"
#include "system.h"

struct REPLAY_ICON
{
	short x, y;
	TEXTURE_DETAILS* texture;
	char* TextPtr;
	short tx, ty;
};

TEXTURE_DETAILS delcam; // address 0xC0EE0
TEXTURE_DETAILS incar; // address 0xBF950
TEXTURE_DETAILS lenschan; // address 0xC1DB0
TEXTURE_DETAILS lookcar; // address 0xC1CB0
TEXTURE_DETAILS movecam; // address 0xC1C18
TEXTURE_DETAILS movecampos; // address 0xC08C0
TEXTURE_DETAILS ok; // address 0xC1BD8
TEXTURE_DETAILS pause; // address 0xBF970
TEXTURE_DETAILS playpause; // address 0xC2A28
TEXTURE_DETAILS clock; // address 0xBF940
TEXTURE_DETAILS choosecar; // address 0xC2A08
TEXTURE_DETAILS chasecar; // address 0xC1D60
TEXTURE_DETAILS addcam; // address 0xC0A50
TEXTURE_DETAILS autocam; // address 0xC1CA0
TEXTURE_DETAILS playcam; // address 0xC1C08
TEXTURE_DETAILS restart; // address 0xC1CD0
TEXTURE_DETAILS save2card; // address 0xC1F40
TEXTURE_DETAILS editcam; // address 0xC1BE8
TEXTURE_DETAILS fixedcam; // address 0xC1D70
TEXTURE_DETAILS frameadv; // address 0xC1D80

REPLAY_ICON replay_icons[] =
{
	{ 20, 26, &pause, G_LTXT_ID(GTXT_Pause), 20, 48 },
	{ 20, 26, &playpause, G_LTXT_ID(GTXT_Play), 20, 48 },
	{ 44, 26, &autocam, G_LTXT_ID(GTXT_AutoDirector), 44, 48 },
	{ 68, 26, &playcam, G_LTXT_ID(GTXT_FastForward), 68, 48 },
	{ 92, 26, &frameadv, G_LTXT_ID(GTXT_FrameAdvance), 92, 48 },
	{ 116, 26, &restart, G_LTXT_ID(GTXT_Rewindtobeginning), 116, 48 },
	{ 140, 26, &addcam, G_LTXT_ID(GTXT_AddCamera), 140, 48 },
	{ 164, 26, &editcam, G_LTXT_ID(GTXT_EditCamera), 164, 48 },
	{ 188, 26, &save2card, G_LTXT_ID(GTXT_SaveReplay), 188, 48 },
	{ 212, 26, &ok, G_LTXT_ID(GTXT_Exit), 212, 48 },
	{ 140, 50, &incar, G_LTXT_ID(GTXT_InCar), 164, 48 },
	{ 140, 74, &chasecar, G_LTXT_ID(GTXT_ChaseCamera), 164, 72 },
	{ 140, 98, &fixedcam, G_LTXT_ID(GTXT_TripodCamera), 164, 96 },
	{ 140, 122, &ok, G_LTXT_ID(GTXT_Accept), 164, 120 },
	{ 140, 122, &clock, G_LTXT_ID(GTXT_MoveCameraStart), 164, 120 },
	{ 140, 146, &delcam, G_LTXT_ID(GTXT_DeleteCamera), 164, 144 },
	{ 140, 170, &ok, G_LTXT_ID(GTXT_Accept), 164, 168 },
	{ 164, 50, &choosecar, G_LTXT_ID(GTXT_YouorPursuer), 164, 72 },
	{ 164, 74, &movecampos, G_LTXT_ID(GTXT_MoveCamera), 164, 96 },
	{ 164, 98, &movecampos, G_LTXT_ID(GTXT_MoveCamera), 164, 120 },
	{ 188, 98, &lookcar, G_LTXT_ID(GTXT_LocktoCar), 188, 120 },
	{ 212, 98, &movecam, G_LTXT_ID(GTXT_Rotate), 212, 120 },
	{ 236, 98, &lenschan, G_LTXT_ID(GTXT_Zoom), 236, 120 }
};

unsigned char menu0[] = { 0, 0xFF };

unsigned char menu1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xFF };

unsigned char menu2[] = { 0xA, 0xB, 0xC, 0xD, 0xFF };

unsigned char menu3[] = { 0x11, 0xFF };

unsigned char menu4[] = { 0x12, 0xFF };

unsigned char menu5[] = { 0x13, 0x14, 0x15, 0x16, 0xFF };

unsigned char menu6[] = { 0xA, 0xB, 0xC, 0xE, 0xF, 0x10, 0xFF };

int FastForward = 0;
int EditMode = 0;

PLAYBACKCAMERA* LastChange = NULL;
PLAYBACKCAMERA* ThisChange = NULL;
PLAYBACKCAMERA* NextChange = NULL;

int FastForwardCameraCnt = 0;
int PlayMode = 0;
int SetFastForward = 0;

int MenuOffset = 0;
int editing_existing_camera = 0;
int frame_advance_count = 0;

char gNoReplaySaveAllowed = 0;
int CursorY = 0;
int ReplayContinue = 0;
int MIN_TRIPOD_CAMERA_HEIGHT = 105;

extern short padd;		// system
extern int vblcounter;	// sound

int time_taken = 0;

char GreyIcons[24];
int CursorX = 0;
int ClearCameras = 0;
int DirectorMenuActive = 0;


void setCamera(PLAYBACKCAMERA* Change);
void deleteCamera(int count);
PLAYBACKCAMERA* FindFreeCamera();
void DoAutoDirect();
int SelectCameraCar(int current);
int NoMoreCamerasErrorMessage();
int FirstCamera();
void SetCameraReturnedFromCutscene(int CameraCnt);


// [D] [T]
void InitDirectorVariables(void)
{
	int count;

	PlayMode = 0;
	CameraChanged = NoPlayerControl != 0;

	DirectorMenuActive = 1;
	ClearCameras = 0;
	EditMode = 0;
	AutoDirect = 0;
	CursorX = 0;

	gCameraOffset.vx = 0;
	gCameraOffset.vy = 0;
	gCameraOffset.vz = 0;

	for (count = 0; count < 24; count++)
		GreyIcons[count] = 0;

	LastChange = NULL;
	FastForwardCameraCnt = 0;
}

// [D] [T]
void DeleteCurrentCamera(int CameraCnt)
{
	int prev;
	int next;
	PLAYBACKCAMERA* Change;

	prev = LastChange->prev;
	next = LastChange->next;

	if (prev != 0xff)
	{
		PlaybackCamera[prev].next = next;

		if (next != 254)
			PlaybackCamera[next].prev = prev;

		LastChange->FrameCnt = 100000;

		setCamera(PlaybackCamera + prev);
		LastChange = PlaybackCamera + prev;
	}
}

// [D] [T]
void setCamera(PLAYBACKCAMERA* Change)
{
	gCameraOffset.vy = Change->CameraPosvy;

	camera_angle.vx = Change->angle.vx;
	camera_angle.vy = Change->angle.vy;
	camera_angle.vz = Change->angle.vz;

	scr_z = Change->scr_z;
	gCameraMaxDistance = Change->gCameraMaxDistance;
	
	gCameraAngle = Change->gCameraAngle;
	cameraview = Change->cameraview & 7;

	tracking_car = (Change->cameraview & 8) >> 3;

	if(cameraview != 0 && cameraview != 2)
	{
		player[0].cameraPos.vx = Change->position.vx;
		player[0].cameraPos.vy = Change->position.vy;
		player[0].cameraPos.vz = Change->position.vz;
	}
	player[0].cameraCarId = Change->angle.pad;
}

// [D] [T]
void EditCamera(int CameraCnt)
{
	int prev;
	int next;
	int count;
	PLAYBACKCAMERA* camera;

	if (LastChange == NULL)
		LastChange = PlaybackCamera;

	ThisChange = LastChange;
	LastChange->cameraview = cameraview & 7 | tracking_car << 3;

	ThisChange->position.vx = player[0].cameraPos.vx;
	ThisChange->position.vy = player[0].cameraPos.vy;
	ThisChange->position.vz = player[0].cameraPos.vz;
	ThisChange->angle.vx = camera_angle.vx;
	ThisChange->angle.vy = camera_angle.vy;
	ThisChange->angle.vz = camera_angle.vz;
	ThisChange->angle.pad = player[0].cameraCarId;
	ThisChange->scr_z = scr_z;

	ThisChange->gCameraAngle = gCameraAngle;
	ThisChange->gCameraMaxDistance = gCameraMaxDistance;

	ThisChange->CameraPosvy = gCameraOffset.vy;

	count = 0;

	do {
		camera = &PlaybackCamera[count];

		if (camera != ThisChange && camera->FrameCnt == ThisChange->FrameCnt)
		{
			prev = camera->prev;
			next = camera->next;

			if (prev == 255)
			{
				*camera = *ThisChange;

				PlaybackCamera[ThisChange->next].idx = count;
				PlaybackCamera[ThisChange->next].prev = -1;

				if (ThisChange->next != 254)
					PlaybackCamera[ThisChange->next].prev = count;

				deleteCamera(ThisChange->idx);

				ThisChange = camera;
				LastChange = ThisChange;
			}
			else
			{
				PlaybackCamera[prev].next = next;

				if (next != 254)
					PlaybackCamera[next].prev = prev;

				deleteCamera(count);
			}
		}

		count++;
	} while (count < MAX_REPLAY_CAMERAS);
}

// [D] [T]
void RecordCamera(int CameraCnt)
{
	char cVar1;
	PLAYBACKCAMERA* TempChange;

	TempChange = FindFreeCamera();

	if (TempChange)
	{
		if (LastChange == NULL ||
			LastChange->cameraview != (cameraview & 7 | tracking_car << 3) ||
			player[0].cameraCarId != LastChange->angle.pad ||
			cameraview == 1 ||
			(cameraview & 7) == 5 ||
			LastChange->scr_z != scr_z ||
			LastChange->gCameraMaxDistance != gCameraMaxDistance ||
			LastChange->gCameraAngle != gCameraAngle ||
			LastChange->CameraPosvy != gCameraOffset.vy)
		{
			if (CameraCnt == 0)
			{
				ThisChange = PlaybackCamera;
			}
			else if (ThisChange == NULL || CameraCnt != ThisChange->FrameCnt)
			{
				TempChange->next = LastChange->next;
				TempChange->prev = LastChange->idx;
				LastChange->next = TempChange->idx;
				ThisChange = TempChange;

				if (TempChange->next != 254)
					PlaybackCamera[TempChange->next].prev = TempChange->idx;
			}

			LastChange = ThisChange;

			ThisChange->cameraview = cameraview & 7 | tracking_car << 3;

			LastChange->position.vx = player[0].cameraPos.vx;
			LastChange->position.vy = player[0].cameraPos.vy;
			LastChange->position.vz = player[0].cameraPos.vz;
			LastChange->angle.vx = camera_angle.vx;
			LastChange->angle.vy = camera_angle.vy;
			LastChange->angle.vz = camera_angle.vz;
			LastChange->angle.pad = player[0].cameraCarId;
			LastChange->scr_z = scr_z;
			LastChange->FrameCnt = CameraCnt;
			LastChange->gCameraMaxDistance = gCameraMaxDistance;
			LastChange->gCameraAngle = gCameraAngle;
			LastChange->CameraPosvy = gCameraOffset.vy;
		}
	}

	FindNextChange(CameraCnt);
}

// [D] [T]
void FindNextChange(int CameraCnt)
{
	bool found;
	PLAYBACKCAMERA* RestoreChange;
	int nextframe;
	int count;

	RestoreChange = NextChange;

	nextframe = 100001;
	found = false;
	count = 0;
	NextChange = PlaybackCamera;

	do {
		if (PlaybackCamera[count].FrameCnt >= CameraCnt && PlaybackCamera[count].FrameCnt < nextframe)
		{
			found = true;
			nextframe = PlaybackCamera[count].FrameCnt;
			NextChange = &PlaybackCamera[count];
		}

		count++;
	} while (count < MAX_REPLAY_CAMERAS);

	if (!found)
	{
		NextChange = RestoreChange;
		RestoreChange->next = -2;
	}
}

// [D] [T]
int CheckCameraChange(int CameraCnt)
{
	if (JustReturnedFromCutscene != 0)
	{
		JustReturnedFromCutscene = 0;
		SetCameraReturnedFromCutscene(CameraCnt);
	}

	if(CameraCnt != -1)
	{
		DoAutoDirect();

		if(gStopPadReads == 0 && InvalidCamera(player[0].cameraCarId) != 0)
		{
			RecordCamera(CameraCnt);
			return 0;
		}
	}
	
	if (NextChange->FrameCnt != CameraCnt)
	{
		if (CameraCnt < NextChange->FrameCnt)
		{
			IsMovingCamera(LastChange, NextChange, CameraCnt);
			return 0;
		}

		if (NextChange->next == 254)
		{
			return 0;
		}
	}

	SetPlaybackCamera(NextChange);

	if (InvalidCamera(player[0].cameraCarId) == 0)
	{
		LastChange = NextChange;
		FindNextChange(CameraCnt + 1);
	}

	if (PlayMode == 1 && CameraCnt != FastForwardCameraCnt)
	{
		SetFastForward = 0;
		FastForward = 0;
		pauseflag = PlayMode;
	}

	return 1;
}


// [D] [T]
void SetPlaybackCamera(PLAYBACKCAMERA* camera)
{
	gCameraOffset.vy = camera->CameraPosvy;
	camera_angle.vx = camera->angle.vx;
	camera_angle.vy = camera->angle.vy;
	camera_angle.vz = camera->angle.vz;

	if(gInGameCutsceneActive == 0) // [A] previously it was gCameraDistance so we don't change it in cutscenes
		scr_z = camera->scr_z;
	
	gCameraMaxDistance = camera->gCameraMaxDistance;
	gCameraAngle = camera->gCameraAngle;
	cameraview = camera->cameraview & 7;

	tracking_car = (camera->cameraview & 8) >> 3;

	CameraChanged = 1;

	if(cameraview != 0 && cameraview != 2)
	{
		player[0].cameraPos.vx = camera->position.vx;
		player[0].cameraPos.vy = camera->position.vy;
		player[0].cameraPos.vz = camera->position.vz;
	}

	player[0].cameraCarId = camera->angle.pad;
}


// [D] [T]
int IsMovingCamera(PLAYBACKCAMERA* lastcam, PLAYBACKCAMERA* nextcam, int cameracnt)
{
	unsigned char type;
	int xdist;
	int ydist;
	int zdist;
	int t, f, s;
	int xangle;
	int yangle;
	int zangle;
	PLAYBACKCAMERA cam;

	if (lastcam == NULL)
		return 0;

	if (cameraview != 5 && cameraview != 1)
		return 0;

	type = nextcam->cameraview & 0x87;

	if (type != 133 && type != 129)
		return 0;

	cameracnt -= lastcam->FrameCnt;
	f = nextcam->FrameCnt - lastcam->FrameCnt;
	s = (cameracnt * 2048) / f;
	t = (RCOS(s*3) - RCOS(s) * 9 >> 4) + 2048;

	
	xdist = FixHalfRound((nextcam->position.vx - lastcam->position.vx) * 64 * t, 18);
	ydist = FixHalfRound((nextcam->position.vy - lastcam->position.vy) * 64 * t, 18);
	zdist = FixHalfRound((nextcam->position.vz - lastcam->position.vz) * 64 * t, 18);

	xangle = nextcam->angle.vx - lastcam->angle.vx;
	yangle = nextcam->angle.vy - lastcam->angle.vy;
	zangle = nextcam->angle.vz - lastcam->angle.vz;

	if (xangle < -2048)
		xangle += 4096;

	if (xangle > 2048)
		xangle -= 4096;

	if (yangle < -2048)
		yangle += 4096;

	if (yangle > 2048)
		yangle -= 4096;

	if (zangle < -2048)
		zangle += 4096;

	if (zangle > 2048)
		zangle -= 4096;

	memcpy((u_char*)&cam, (u_char*)lastcam, sizeof(PLAYBACKCAMERA));

	cam.position.vx = lastcam->position.vx + xdist;
	cam.position.vy = lastcam->position.vy + ydist;
	cam.position.vz = lastcam->position.vz + zdist;

	cam.angle.vx = lastcam->angle.vx + ((xangle << 6) / f * cameracnt >> 6);
	cam.angle.vy = lastcam->angle.vy + ((yangle << 6) / f * cameracnt >> 6);
	cam.angle.vz = lastcam->angle.vz + ((zangle << 6) / f * cameracnt >> 6);

	SetPlaybackCamera(&cam);

	return 1;
}


// [D] [T]
void CameraBar(int CameraCnt)
{
	int x;
	int bar_x;
	POLY_G4* camera;
	LINE_F2* bar;
	int max_x;
	int min_x;
	int frame;
	int red;
	int green;
	int blue;
	int first;
	int last;
	int idx;

	red = 0;
	green = 0;
	blue = 0;
	last = 1;
	first = 1;

	bar = (LINE_F2*)current->primptr;

	setLineF2(bar);

	bar->r0 = 0;
	bar->g0 = 0;
	bar->b0 = 0;
	bar->y0 = 12;
	bar->x0 = 160;
	bar->x1 = 160;
	bar->y1 = 22;

	addPrim(current->ot, bar);
	current->primptr += sizeof(LINE_F2);

	if (PlaybackCamera->FrameCnt == 100000)
		return;

	idx = 0;

	do {
		if (PlaybackCamera[idx].next < MAX_REPLAY_CAMERAS)
			max_x = PlaybackCamera[PlaybackCamera[idx].next].FrameCnt;
		else
			max_x = 200000;

		bar_x = ReplayParameterPtr->RecordingEnd + 1;

		if (bar_x < max_x)
		{
			last = 2;
			max_x = bar_x;
		}

		frame = PlaybackCamera[idx].FrameCnt + 160;

		min_x = frame - CameraCnt;
		bar_x = (frame - (frame & 0x1f)) - CameraCnt;
		max_x = (max_x + 160) - CameraCnt;

		if (first && min_x > 30 && min_x < 290)
		{
			bar = (LINE_F2*)current->primptr;

			setLineF2(bar);

			bar->r0 = 0;
			bar->g0 = 0;
			bar->b0 = 0;
			bar->x0 = min_x;
			bar->y0 = 15;
			bar->x1 = min_x;
			bar->y1 = 19;

			addPrim(current->ot, bar);
			current->primptr += sizeof(LINE_F2);
		}

		x = 0;

		while (x < last)
		{
			if (max_x - 31U < 259)
			{
				bar = (LINE_F2*)current->primptr;
				setLineF2(bar);

				bar->r0 = 0;
				bar->g0 = 0;
				bar->b0 = 0;

				bar->x0 = max_x + x;
				bar->y0 = 15;
				bar->x1 = max_x + x;
				bar->y1 = 19;

				addPrim(current->ot, bar);
				current->primptr += sizeof(LINE_F2);
			}

			x++;
		}

		while (bar_x < max_x)
		{
			if (bar_x - 31U < 259)
			{
				bar = (LINE_F2*)current->primptr;
				setLineF2(bar);

				bar->r0 = 0;
				bar->g0 = 0;
				bar->b0 = 0;

				bar->x0 = bar_x;
				bar->y0 = 17;
				bar->x1 = bar_x;
				bar->y1 = 19;

				addPrim(current->ot, bar);
				current->primptr += sizeof(LINE_F2);
			}
			bar_x += 32;
		}

		switch(PlaybackCamera[idx].cameraview & 7)
		{
			case 1:
			{
				red = 0;
				green = 255;
				blue = 0;
				break;
			}
			case 0:
			{
				red = 255;
				green = 0;
				blue = 0;
				break;
			}
			case 2:
			{
				red = 70;

				if (PlaybackCamera[idx].angle.pad == 0)
				{
					green = 70;
					blue = 255;
				}
				else
				{
					green = 255;
					blue = 255;
				}
	
				break;
			}
			case 5:
			{
				red = 255;
				green = 255;
				blue = 0;
				break;
			}
		}

		camera = (POLY_G4*)current->primptr;

		setPolyG4(camera);

		camera->r1 = (red >> 1);
		camera->b1 = (blue >> 1);
		camera->g1 = (green >> 1);

		camera->r2 = (red >> 2);
		camera->g2 = (green >> 2);
		camera->b2 = (blue >> 2);
		
		camera->r0 = red;
		camera->g0 = green;
		camera->b0 = blue;

		camera->r3 = (red >> 2);
		camera->g3 = (green >> 2);
		camera->b3 = (blue >> 2);
		
		idx = PlaybackCamera[idx].next;

		if (min_x > 290)
			return;

		if (max_x > 290)
			max_x = 290;

		if (max_x > 29)
		{
			if (min_x < 30)
				min_x = 30;

			camera->x0 = min_x;
			camera->y0 = 15;
			camera->x1 = max_x;
			camera->y1 = 15;
			camera->x2 = min_x;
			camera->y2 = 20;
			camera->x3 = max_x;
			camera->y3 = 20;

			addPrim(current->ot, camera);
			current->primptr += sizeof(POLY_G4);

			first = 0;
		}

		if (PlaybackCamera[idx].FrameCnt == 100000 || idx == 0)
			return;

	} while (idx < MAX_REPLAY_CAMERAS);
}


// [D] [T]
PLAYBACKCAMERA* FindFreeCamera(void)
{
	int count;

	count = 0;

	do {
		if (PlaybackCamera[count].FrameCnt == 100000)
			return &PlaybackCamera[count];

		count++;
	} while (count < MAX_REPLAY_CAMERAS);

	return NULL;
}

// [D] [T]
void deleteCamera(int count)
{
	PlaybackCamera[count].idx = count;
	PlaybackCamera[count].prev = -1;
	PlaybackCamera[count].FrameCnt = 100000;
	PlaybackCamera[count].next = -2;
}

// [D] [T]
void DeleteAllCameras(void)
{
	int count;

	count = 0;
	do {
		deleteCamera(count);
		count++;
	} while (count < MAX_REPLAY_CAMERAS);

	LastChange = NULL;

	RecordCamera(0);
	CheckCameraChange(-1);

	LastChange->prev = -1;
	LastChange->next = -2;
}


// [D] [T]
void ShowIcons(unsigned char* menu, int selected, int x_offset)
{
	static int FlashCnt = 0;

	unsigned int ramp;
	SPRT* icon;
	POLY_FT3* null;
	TEXTURE_DETAILS* Icon_texture;
	int count;

	count = 0;

	if (CameraCnt < ReplayParameterPtr->RecordingEnd)
	{
		GreyIcons[1] = 0;
		GreyIcons[4] = 0;
		GreyIcons[7] = 0;
		GreyIcons[2] = 0;

		if (NoMoreCamerasErrorMessage() == 0)
			GreyIcons[6] = 0;
		else
			GreyIcons[6] = 1;
	}
	else
	{
		ReleaseInGameCutscene();

		if (time_taken == 0)
			time_taken = vblcounter;

		SetFastForward = 0;
		FastForward = 0;
		GreyIcons[1] = 1;
		GreyIcons[3] = 1;
		GreyIcons[4] = 1;
		GreyIcons[6] = 1;
		GreyIcons[7] = 1;
		GreyIcons[2] = 1;
	}

	GreyIcons[8] = gNoReplaySaveAllowed != 0;

	if (tracking_car == 1 && !OK_To_Zoom())
		GreyIcons[22] = 1;
	else
		GreyIcons[22] = 0;

	GreyIcons[14] = FirstCamera() != 0;
	GreyIcons[15] = GreyIcons[14];

	while (*menu != 255)
	{
		Icon_texture = replay_icons[*menu].texture;

		if (selected == count)
		{
			SetTextColour(128, 128, 64);
			PrintStringBoxed(GET_GAME_TXT(replay_icons[*menu].TextPtr), replay_icons[*menu].tx + x_offset + 1, replay_icons[*menu].ty);
		}

		icon = (SPRT*)current->primptr;
		setSprt(icon);

		if (GreyIcons[*menu] == 0)
		{
			if (selected == count)
			{
				ramp = (FlashCnt & 0xf);

				if ((FlashCnt & 0xf) < 8)
					ramp = 7 - ramp;
				else
					ramp -= 7;

				if (EditMode == 0)
				{
					icon->r0 = -1;
					icon->g0 = -1;
					icon->b0 = -1;
					FlashCnt = 0;
				}
				else
				{
					icon->r0 = icon->g0 = icon->b0 = ramp * 28 + 30;
					FlashCnt++;
				}
			}
			else
			{
				icon->r0 = 100;
				icon->g0 = 100;
				icon->b0 = 100;
			}
		}
		else
		{
			setSemiTrans(icon, 1);
			icon->r0 = 32;
			icon->g0 = 32;
			icon->b0 = 32;
		}

		icon->x0 = replay_icons[*menu].x + (x_offset + 1);
		icon->y0 = replay_icons[*menu].y;

		icon->w = 20;
		icon->h = 20;
		icon->u0 = Icon_texture->coords.u0;
		icon->v0 = Icon_texture->coords.v0;
		icon->clut = Icon_texture->clutid;

		addPrim(current->ot, icon);
		current->primptr += sizeof(SPRT);

		null = (POLY_FT3*)current->primptr;
		setPolyFT3(null);

		null->x0 = -1;
		null->y0 = -1;
		null->x1 = -1;
		null->y1 = -1;
		null->x2 = -1;
		null->y2 = -1;
		null->tpage = Icon_texture->tpageid;
		addPrim(current->ot, null);

		current->primptr += sizeof(POLY_FT3);

		menu++;
		count++;
	}
}

// [D] [T]
void ShowReplayMenu(void)
{
	int strobe;
	int selected;

	if (DirectorMenuActive < 1 && PlayMode != 2 && PlayMode != 3)
	{
		ShowIcons(menu0, 0, 0);
	}
	else
	{
		if (DirectorMenuActive == 1)
			selected = CursorX;
		else
			selected = 99;

		ShowIcons(menu1, selected, 0);
	}

	if (DirectorMenuActive > 1)
	{
		if (MenuOffset == 0)
		{
			if (DirectorMenuActive == 2)
			{
				ShowIcons(menu2, CursorY - 1, 0);
			}
			else
			{
				ShowIcons(menu2, 99, 0);
			}
		}
		else
		{
			if (DirectorMenuActive == 2)
			{
				ShowIcons(menu6, CursorY - 1, MenuOffset);
			}
			else
			{
				ShowIcons(menu6, 99, MenuOffset);
			}
		}		
	}

	if (DirectorMenuActive == 3)
	{
		ShowIcons(menu3, CursorX - 6, MenuOffset);
	}
	else if (DirectorMenuActive == 4)
	{
		ShowIcons(menu4, CursorX - 6, MenuOffset);
	}
	else if (DirectorMenuActive == 5)
	{
		ShowIcons(menu5, CursorX - 6, MenuOffset);
	}

	if (AutoDirect && !pauseflag)
	{
		strobe = CameraCnt & 0x1f;

		if (strobe > 15)
			strobe = 32 - strobe;

		SetTextColour((strobe << 3), 0, 0);
		PrintString(G_LTXT(GTXT_Autodirect), 100, 30);
	}
}

// [D] [T]
void ShowReplayOptions(void)
{
	if (gInGameCutsceneActive || quick_replay)
		return;

	// [A] handle sound here
	if (DirectorMenuActive)	// not a FastForward
		PauseSound();
	else if (PlayMode != 2 && PlayMode != 3)
		UnPauseSound();

	if (!gDoOverlays && (!DirectorMenuActive || EditMode > 0))
		return;

	ShowReplayMenu();
	CameraBar(CameraCnt);
}

// [D] [T]
void ControlReplay(void)
{
	static int debounce; // offset 0x70
	static int first_time; // offset 0x74

	PLAYBACKCAMERA* pCam;
	GAMEMODE new_mode;
	VECTOR old_camera;
	VECTOR basePos;
	VECTOR tmpPos;
	int speed;
	int move;

	move = 0;
	
	if (gInGameCutsceneActive)
		return;

	if (quick_replay || AttractMode)
	{
		if ((padd != 0 || ReplayParameterPtr->RecordingEnd <= CameraCnt) && CameraCnt > 2)
		{
			ReleaseInGameCutscene();

			if (AttractMode == 0)
				EnablePause((PAUSEMODE)gMissionCompletionState);
			else
				EndGame(GAMEMODE_QUIT);

			time_taken = vblcounter;
			return;
		}
		
		//pauseflag = 0;
		return;
	}

	// register pads
	if ((padd & 0x8000) && debounce == 0)
	{
		move = 2;
		debounce = 1;
	}
	if ((padd & 0x2000) && debounce == 0)
	{
		move = 1;
		debounce = 1;
	}
	if ((padd & 0x1000) && debounce == 0)
	{
		move = 3;
		debounce = 1;
	}
	if ((padd & 0x4000) && debounce == 0)
	{
		move = 4;
		debounce = 1;
	}
	if ((padd & 0x40) && debounce == 0)
	{
		if (DirectorMenuActive == 0)
			pauseflag = 1;
		else
			move = 5;

		FastForward = 0;
		SetFastForward = 0;
		debounce = 1;
	}

	if ((padd & 0x100) && debounce == 0)
	{
		// Retro: Press Select to toggle overlays
		gDoOverlays ^= 1;
		debounce = 1;
	}
	
	if ((padd & 0x8000) == 0 && (padd & 0x7140) == 0)
	{
		debounce = 0;
	}

	// apply editing
	if (EditMode != 0 && move != 5)
	{
		move = 0;
		speed = 1;
	
		if (padd & 8)
			speed = 8;

		// control camera position and rotation
		// depending on edit modes
		if (EditMode == 1)
		{
			// edit start time
			if ((padd & 0x2000U) != 0 && LastChange->FrameCnt < CameraCnt)
			{
				LastChange->FrameCnt++;
			}

			if ((padd & 0x8000U) != 0 && PlaybackCamera[LastChange->prev].FrameCnt < LastChange->FrameCnt)
			{
				LastChange->FrameCnt--;
			}
		}
		else if (EditMode == 2)
		{
			// Chase camera angle
			if ((padd & 0x1000) != 0 && gCameraDistance > 500)
			{
				gCameraDistance -= speed * 16;		// [A] restore
				gCameraMaxDistance -= speed * 16;
				player[0].cameraDist = gCameraDistance;
			}

			if ((padd & 0x4000) != 0 && gCameraDistance < 2750)
			{
				gCameraDistance += speed * 16;		// [A] restore
				gCameraMaxDistance += speed * 16;
				player[0].cameraDist = gCameraDistance;
			}

			if ((padd & 0x8000) != 0)
				gCameraAngle = gCameraAngle + speed * 16;

			if ((padd & 0x2000) != 0)
				gCameraAngle = gCameraAngle - speed * 16;

			if ((padd & 4) && gCameraOffset.vy > -840)
				gCameraOffset.vy -= speed * 16;

			if ((padd & 1) && gCameraOffset.vy < 50)
				gCameraOffset.vy += speed * 16;

			// OBSOLETE DRIVER 1 CODE
			/*
			ROADS_GetRouteData(player[0].cameraPos.vx, player[0].cameraPos.vz, &routeData1);

			if (modelpointers[routeData1.type]->flags2 & MODEL_FLAG_INDOORS)
			{
				int road_height;
				road_height = -450 - MapHeight(&player[0].cameraPos);

				player[0].cameraPos.vy = gCameraOffset.vy - player[0].pos[1];

				if (road_height > gCameraOffset.vy - player[0].pos[1])
				{
					gCameraOffset.vy = road_height + player[0].pos[1];
					player[0].cameraPos.vy = road_height;
				}
			}
			*/
		}
		else if (EditMode == 3)
		{
			// Move camera
			int cameraCar;
			int height;
			int dx, dz;
			int x, z;
			int d;
			int dir;

			x = 0;
			z = 0;

			cameraCar = player[0].cameraCarId;

			if (cameraCar >= 0)
			{
				basePos.vx = car_data[cameraCar].hd.where.t[0];
				basePos.vz = car_data[cameraCar].hd.where.t[2];
			}
			else if (cameraCar == -1)
			{
				basePos.vx = player[0].pos[0];
				basePos.vz = player[0].pos[2];
			}
			else
			{
				EVENT* ev;
				ev = events.track[-2 - cameraCar];
				
				basePos.vx = ev->position.vx;
				basePos.vz = ev->position.vz;
			}

			dx = basePos.vx - player[0].cameraPos.vx;
			dz = basePos.vz - player[0].cameraPos.vz;
	
			old_camera.vx = player[0].cameraPos.vx;
			old_camera.vz = player[0].cameraPos.vz;
			old_camera.vy = player[0].cameraPos.vy;

			d = SquareRoot0(dx * dx + dz * dz);

			if (tracking_car == 0)
				dir = camera_angle.vy;
			else
				dir = ratan2(dz, dx);

			if (padd & 2)
			{
				if ((padd & 0x1000U) && gCameraOffset.vy > -150)
					gCameraOffset.vy -= speed * 16;

				if ((padd & 0x4000) && gCameraOffset.vy < 150)
					gCameraOffset.vy += speed * 16;
			}
			else
			{
				if ((padd & 0x1000) != 0 && (tracking_car == 0 || d > 500))
					x = speed * -16;

				if ((padd & 0x4000) != 0)
					x = speed * 16;
			}


			if ((padd & 0x8000) != 0 && (tracking_car == 0 || d > 500))
				z = speed * -16;

			if ((padd & 0x2000) != 0)
				z = speed * 16;

			if (tracking_car == 0)
			{
				d = z;
				
				z = x;
				x = -d;
			}

			player[0].cameraPos.vx = (player[0].cameraPos.vx + FIXED(z * RSIN(dir))) - FIXED(x * RCOS(dir));
			player[0].cameraPos.vz = (player[0].cameraPos.vz - FIXED(z * RCOS(dir))) - FIXED(x * RSIN(dir));

			tmpPos.vx = player[0].cameraPos.vx;
			tmpPos.vy = -player[0].cameraPos.vy;
			tmpPos.vz = player[0].cameraPos.vz;

			if ( dist(player[0].spoolXZ, &player[0].cameraPos) < 18433)
			{
				if (QuickBuildingCollisionCheck(&tmpPos, dir, 10, 10, 10) != 0)
				{
					player[0].cameraPos.vx = old_camera.vx;
					player[0].cameraPos.vz = old_camera.vz;
				}
			}
			else
			{
				player[0].cameraPos.vy = old_camera.vy;
				player[0].cameraPos.vx = old_camera.vx;
				player[0].cameraPos.vz = old_camera.vz;
			}
			
			if (padd & 4)
				player[0].cameraPos.vy -= speed * 16;

			if (padd & 1)
				player[0].cameraPos.vy += speed * 16;	

			height = -MapHeight(&tmpPos);
			
			if (player[0].cameraPos.vy > height - MIN_TRIPOD_CAMERA_HEIGHT)
				player[0].cameraPos.vy = height - MIN_TRIPOD_CAMERA_HEIGHT;

			if (player[0].cameraPos.vy < height - 1050)
				player[0].cameraPos.vy = height - 1050;

			// OBSOLETE DRIVER 1 CODE
			/*
			ROADS_GetRouteData(player[0].cameraPos.vx, player[0].cameraPos.vz, &routeData);

			if ((modelpointers[routeData.type]->flags2 & MODEL_FLAG_INDOORS) && player[0].cameraPos.vy < height - 450)
			{
				player[0].cameraPos.vy = height - 450;
			}*/

			if (cameraview == 1 && OK_To_Zoom() == 0)
			{
				cameraview = 5;
			}
		}
		else if (EditMode == 4)
		{
			// Tripod camera angle
			
			if(padd & 0x1000)
			{
				camera_angle.vx += speed * 4;

				if((camera_angle.vx - 300U & 0xffff) < 1749)
					camera_angle.vx = 300;
			}

			if (padd & 0x4000)
			{
				camera_angle.vx -= speed * 4;

				if((camera_angle.vx - 0x800U & 0xffff) < 1853)
					camera_angle.vx = 3900;
			}

			if (padd & 0x8000)
				camera_angle.vy += speed * 4;

			if (padd & 0x2000)
				camera_angle.vy -= speed * 4;

			camera_angle.vx = camera_angle.vx & 0xfff;
			camera_angle.vy = camera_angle.vy & 0xfff;
			camera_angle.vz = camera_angle.vz & 0xfff;
		}
		else if (EditMode == 5)
		{
			if(padd & 0x1000)
			{
				scr_z += speed * 4;

				if (scr_z > 1000)
					scr_z = 1000;
			}

			if (padd & 0x4000)
			{
				scr_z -= speed * 4;
				
				if (scr_z < 256)
					scr_z = 256;
			}
		}
	}

	// move director menu cursor
	if (move == 1)
	{
		CursorX++;

		if(CameraCnt < ReplayParameterPtr->RecordingEnd || DirectorMenuActive != 1 || CursorX != 5)
		{
			if(FindFreeCamera() == NULL && DirectorMenuActive == 1 && CursorX == 5)
			{
				CursorX = 6;
			}
		}
		else
			CursorX = 7;

		if (CursorX == 7 && DirectorMenuActive == 1 && gNoReplaySaveAllowed != 0)
		{
			CursorX = 8;
		}
	}
	else if (move == 2)
	{
		CursorX--;

		if (CursorX == 7 && DirectorMenuActive == 1 && gNoReplaySaveAllowed != 0)
		{
			CursorX = 6;
		}

		if (ReplayParameterPtr->RecordingEnd <= CameraCnt && DirectorMenuActive == 1 && CursorX == 6 ||
			FindFreeCamera() == NULL && DirectorMenuActive == 1 && CursorX == 5)
		{
			CursorX = 4;
		}
	}
	else if (move == 3)
	{
		CursorY--;

		if (FirstCamera() != 0 && DirectorMenuActive == 2 && MenuOffset != 0 && CursorY == 5)
		{
			CursorY = 3;
		}
	}
	else if (move == 4)
	{
		CursorY++;

		if (FirstCamera() != 0 && DirectorMenuActive == 2 && (MenuOffset != 0 && CursorY == 4))
		{
			CursorY = 6;
		}
	}

	if (debounce == 0 && PlayMode == 3)
	{
		pauseflag = 1;
	}

	if (pauseflag == 0)
	{
		if (PlayMode == 2)
		{
			first_time = 1;
			pauseflag = 1;
			DirectorMenuActive = 0;
			return;
		}
	
		first_time = 1;
		DirectorMenuActive = 0;
		return;
	}

	if (first_time != 0)
	{
		if (ReplayParameterPtr->RecordingEnd <= CameraCnt && (CursorX < 4 || CursorX == 5))
		{
			CursorX = 4;
		}
		DirectorMenuActive = 1;
	}

	first_time = 0;
	ReplayContinue = 0;

	// move another director menu cursor
	switch (DirectorMenuActive)
	{
		case 1:
		{
			CursorY = 0;
			if (CameraCnt < ReplayParameterPtr->RecordingEnd)
			{
				if (CursorX < 0)
					CursorX = 8;

				if (CursorX > 8)
					CursorX = 0;
			}
			else
			{
				if (CursorX < 4)
					CursorX = 8;

				if (CursorX > 8)
					CursorX = 4;
			}

			switch (CursorX)
			{
				case 0:
				{
					if (move != 5)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						break;
					}

					if (CameraCnt < ReplayParameterPtr->RecordingEnd)
					{
						first_time = 0;
						pauseflag = 0;
						CursorY = 0;
						PlayMode = 0;
						ReplayContinue = 1;
						AutoDirect = 0;
						vblcounter = 0;
						break;
					}
					
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					break;
				}
				case 1:
				{
					if (move != 5)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						break;
					}

					if (CameraCnt < ReplayParameterPtr->RecordingEnd)
					{
						first_time = 0;
						pauseflag = 0;
						CursorY = 0;
						PlayMode = 0;
						ReplayContinue = 1;
						AutoDirect = 1;
						break;
					}
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					break;
				}
				case 2:
					if (move != 5)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						break;
					}

					if (CameraCnt < ReplayParameterPtr->RecordingEnd)
					{
						FastForward = 1;
						FastForwardCameraCnt = CameraCnt;
						first_time = 0;
						pauseflag = 0;
						CursorY = 0;
						PlayMode = 1;
						ReplayContinue = 1;
						AutoDirect = 0;
						break;
					}
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					break;
				case 3:
					if (ReplayParameterPtr->RecordingEnd <= CameraCnt)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						break;
					}

					if (move == 5)
					{
						first_time = 0;
						pauseflag = 0;
						CursorY = 0;
						PlayMode = 2;
						ReplayContinue = 0;
						frame_advance_count = 10;
						AutoDirect = 0;
						break;
					}

					if ((padd & 0x40U) == 0)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						break;
					}
				
					if (frame_advance_count == 0)
					{
						first_time = 0;
						pauseflag = 0;
						CursorY = 0;
						PlayMode = 3;
						ReplayContinue = 1;
						break;
					}
				
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					frame_advance_count = frame_advance_count + -1;
				
					break;
				case 4:
					new_mode = GAMEMODE_DIRECTOR;
					if (move != 5)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						break;
					}
				
					EndGame(new_mode);
					PlayMode = 0;
				
					break;
				case 5:
					if (ReplayParameterPtr->RecordingEnd <= CameraCnt)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						break;
					}

					if (move == 5)
					{
						editing_existing_camera = 0;
						first_time = 0;
						MenuOffset = 0;
						DirectorMenuActive = 2;
						CursorY = 1;
						ReplayContinue = 0;
						break;
					}

					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					break;
				case 6:
					if (move == 5)
					{
						editing_existing_camera = 1;
						first_time = 0;
						MenuOffset = 0x18;
						DirectorMenuActive = 2;
						CursorY = 1;
						ReplayContinue = 0;
						break;
					}

					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					break;
				case 7:
					if (move == 5)
					{
						SpoolSYNC();
						SaveReplay(0);
						break;
					}

					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					break;
				case 8:
					if (move != 5)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						break;
					}

					if (gLoadedReplay)
					{
						EndGame(GAMEMODE_QUIT);
						PlayMode = 0;
					}

					// force pause
					NoPlayerControl = 0;
					pauseflag = 0;
					
					EnablePause((PAUSEMODE)gMissionCompletionState);

					pauseflag = 1;
					NoPlayerControl = 1;
					PlayMode = 0;
					quick_replay = 1;
				
					break;
				default:
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					break;
			}
			break;
		}
		case 2:
		{
			CursorX = 5;
			switch (CursorY)
			{
				case 0:
				{
					DirectorMenuActive = 1;
					if (MenuOffset != 0)
						CursorX = 6;

					if (LastChange == NULL)
						setCamera(PlaybackCamera);
					else
						setCamera(LastChange);

					break;
				}
				case 1:
				{
					if (move == 5)
					{
						DirectorMenuActive = 3;
						gCameraOffset.vy = 0;
						cameraview = 2;
						CursorX = 6;
					}
					break;
				}
				case 2:
				{
					if (move == 5)
					{
						DirectorMenuActive = 4;
						gCameraAngle = 2048;
						
						gCameraDistance = 1600;
						gCameraMaxDistance = 1600;
						cameraview = 0;
						
						gCameraOffset.vx = 0;
						gCameraOffset.vy = 0;
						gCameraOffset.vz = 0;
						CursorX = 6;
					}
					break;
				}
				case 3:
				{
					if (move == 5)
					{
						if (cameraview == 2)
						{
							cameraview = 0;
							InitCamera(&player[0]);
						}

						if (cameraview != 5 && cameraview != 1)
						{
							cameraview = 1;
						}
						DirectorMenuActive = 5;
						CursorX++;
					}
					break;
				}
				case 4:
				{
					if (MenuOffset != 0)
					{
						if (LastChange->prev != 0xFF && move == 5)
						{
							if (EditMode == 0)
							{
								EditMode = 1;
							}
							else
							{
								pCam = &PlaybackCamera[LastChange->prev];
								if (LastChange->FrameCnt == pCam->FrameCnt)
								{
									if (pCam->prev != 0xff)
									{
										PlaybackCamera[pCam->prev].next = pCam->next;
										LastChange->prev = pCam->prev;
										pCam->FrameCnt = 100000;
									}
								}
								EditMode = 0;
							}
						}
						break;
					}

					if (move == 5)
					{
						DirectorMenuActive = 1;
						if (editing_existing_camera == 0)
						{
							RecordCamera(CameraCnt);

							if (NoMoreCamerasErrorMessage() != 0)
								CursorX = 6;

							break;
						}

						DirectorMenuActive = 1;
						EditCamera(CameraCnt);
					}
					break;
				}
				case 5:
				{
					if (move == 5)
					{
						CursorX = 6;
						DeleteCurrentCamera(CameraCnt);

						if (FirstCamera())
							CursorY = 6;
					}
					break;
				}
				case 6:
				{
					if (move == 5)
					{
						DirectorMenuActive = 1;
						CursorX = 6;

						if (editing_existing_camera == 0)
						{
							RecordCamera(CameraCnt);
							break;
						}

						DirectorMenuActive = 1;
						EditCamera(CameraCnt);
					}
					break;
				}
			}

			if (MenuOffset == 0)
			{
				if (CursorY > 4)
					CursorY = 4;
			}
			else
			{
				if (CursorY > 6)
					CursorY = 6;
			}

			break;
		}
		case 3:
		{
			CursorY = 1;
	
			if (CursorX == 5)
				DirectorMenuActive = 2;
			else if (CursorX == 6 && move == 5)
				player[0].cameraCarId = SelectCameraCar(player[0].cameraCarId);

			if (CursorX > 6)
				CursorX = 6;
			
			break;
		}
		case 4:
		{
			CursorY = 2;
			if (CursorX == 5)
			{
				DirectorMenuActive = 2;
			}
			else if (CursorX == 6 && move == 5)
			{
				if (EditMode == 0)
					EditMode = 2;
				else
					EditMode = 0;
			}

			if (CursorX > 6)
				CursorX = 6;
			
			break;
		}
		case 5:
		{
			CursorY = 3;

			switch (CursorX)
			{
				case 5:
					DirectorMenuActive = 2;
					break;
				case 6:
					if (move == 5)
					{
						if (EditMode == 0)
							EditMode = 3;
						else
							EditMode = 0;
					}
					break;
				case 7:
					if (move == 5)
					{
						tracking_car = 1;
					}
					break;
				case 8:
					if (move == 5)
					{
						tracking_car = 0;

						if (EditMode != 0)
							EditMode = 0;
						else
							EditMode = 4;
					}
					break;
				case 9:
					if (tracking_car != 0)
					{
						if(move == 5)
						{
							if (cameraview == 1)
								cameraview = 5;
							else
								cameraview = 1;
						}
					}
					else
					{
						if(move == 5)
						{
							if (EditMode != 0)
								EditMode = 0;
							else
								EditMode = 5;
						}
					}
				
					break;
			}

			if (tracking_car == 1 && !OK_To_Zoom())
			{
				if (CursorX > 7)
					CursorX = 8;
			}
			else
			{
				if (CursorX > 8)
					CursorX = 9;
			}
			break;
		}
	}
}

int* savemapinfo = NULL;
static int mapstuff = 0;
static int cammapht2 = 0;

// [D] [T]
void DoAutoDirect(void)
{
	int height;

	// [A] disable auto director even in quick replay
	if (AutoDirect != 0 && gStopPadReads == 0)
	{
		tracking_car = 1;

		if (TimeToWay == way_distance / 2 + 15 &&
			PlayerWayRecordPtr->x != 0x7fff && PlayerWayRecordPtr->y != 0x7fff)
		{
			switch (rand() & 7)
			{
				case 0:
					cameraview = 0;
					gCameraAngle = rand() & 0xfff;
					gCameraOffset.vy = -((rand() & 0xff) + 100);
					gCameraDistance = (rand() & 0x7e7) + 500;
					gCameraMaxDistance = gCameraDistance;
					break;
				case 1:
				case 2:
					cameraview = 1;
					break;
				case 3:
				case 4:
					gCameraOffset.vy = 0;
					cameraview = 1;
					break;
				case 5:
					gCameraOffset.vy = 0;
					cameraview = 2;
					player[0].cameraCarId = player[0].playerCarId;
					break;
				case 6:
				case 7:
					cameraview = 5;
					break;
			}

			if (ReplayParameterPtr->RecordingEnd < CameraCnt + way_distance)
			{
				cameraview = 0;
				player[0].cameraCarId = -1;

				if (player[0].playerType != 2)
					player[0].cameraCarId = player[0].playerCarId;

			}
			else
			{
				player[0].cameraPos.vx = PlayerWayRecordPtr->x << 10;
				player[0].cameraPos.vz = PlayerWayRecordPtr->y << 10;
			}

			player[0].cameraPos.vy = (-70 - MapHeight(&player[0].cameraPos)) - (rand() & 0x3ff);

			height = MapHeight((VECTOR*)car_data[player[0].cameraCarId].hd.where.t);

			if (-height < player[0].cameraPos.vy)
			{
				player[0].cameraPos.vy = -height - 100;
			}

			cammapht2 = MapHeight(&player[0].cameraPos);
			cammapht2 = -cammapht2;

			if (cammapht2 < player[0].cameraPos.vy)
				player[0].cameraPos.vy = cammapht2 - 100;

			MapHeight(&player[0].cameraPos);

			if (savemapinfo != NULL)
				mapstuff = *savemapinfo;


			if (valid_region(PlayerWayRecordPtr->x << 10, PlayerWayRecordPtr->y << 10) == 0 ||
				(cameraview != 2 && cameraview != 0 &&
					savemapinfo != NULL && (*savemapinfo & 0x3c000000U) == 0x3c000000 || CameraCollisionCheck() != 0))
			{
				cameraview = (rand() & 2);

				if (cameraview == 0)
				{
					gCameraAngle = rand() & 0xfff;
					gCameraDistance = (rand() & 0x7e7) + 500;
					gCameraMaxDistance = gCameraDistance;

					gCameraOffset.vy = -((rand() & 0xff) + 100);
				}
				else if (cameraview == 1 || cameraview == 5)
				{
					gCameraOffset.vy = -((rand() & 0xff) + 100);
				}
				else
					gCameraOffset.vy = 0;

				if (player[0].playerType == 2)
					player[0].cameraCarId = -1;
				else
					player[0].cameraCarId = player[0].playerCarId;
			}

			if (NoMoreCamerasErrorMessage() == 0)
			{
				RecordCamera(CameraCnt);
			}
			else
			{
				cameraview = 0;
				gCameraAngle = rand() & 0xfff;
				gCameraOffset.vy = -((rand() & 0xff) + 100);
				gCameraDistance = (rand() & 0x7e7) + 1000;
				gCameraMaxDistance = gCameraDistance;
			}

			PlayerWayRecordPtr->x = 0x7fff;
			PlayerWayRecordPtr->y = 0x7fff;
		}
	}

	if (TimeToWay-- == 0)
	{
		PlayerWayRecordPtr++;
		TimeToWay = way_distance;
	}
}

// [D] [T]
int SelectCameraCar(int current)
{
	int count;

	EVENT* event;
	int dz;
	int dx;
	CAR_DATA* car;
	XZPAIR pos;

	if (current >= MAX_CARS)
		return 0;

	if (current < -1)
		current = (MAX_CARS - 2) - current;

	count = current + 1;

	while (count != current)
	{
		event = NULL;
		car = NULL;

		if (count < MAX_CARS)
		{
			car = &car_data[count];

			if (car->controlType == CONTROL_TYPE_PURSUER_AI)
			{
				pos.x = car->hd.where.t[0];
				pos.z = car->hd.where.t[2];
			}
			else
			{
				if (car->controlType == CONTROL_TYPE_PLAYER)
				{
					if (player[1].playerCarId == car->id)
						return player[1].playerCarId;

					return player[0].playerCarId;
				}

				car = NULL;

				if (count == -1 && player[0].playerType == 2)
					return -1;
			}
		}
		else
		{
			event = events.track[count - MAX_CARS];

			if (event == NULL)
			{
				if (player[0].playerType == 2)
					count = -2;
				else
					count = -1;
			}
			else
			{
				pos.x = event->position.vx;
				pos.z = event->position.vz;
			}
		}

		if (car != NULL || event != NULL)
		{
			dx = ABS(player[0].pos[0] - pos.x);
			dz = ABS(player[0].pos[2] - pos.z);

			if (dx < 15000 && dz < 15000 &&
				dx * dx + dz * dz < 225000000)
			{
				if (car != NULL)
					return car->id;

				return (MAX_CARS - 2) - count;
			}
		}

		count++;
	}

	printError("ERROR:_SelectCameraCar\n");

	return player[0].playerCarId;
}

// [D] [T]
int InvalidCamera(int car_num)
{
	bool invalidCamera;
	int dx;
	int dz;
	int numEventModels;

	// [A] bug fix of invalid player camera
	if (CameraCnt < 3)
		return 0;
	
	// check if camera is not too far
	if (cameraview != 2)
	{
		if (Long2DDistance(player[0].spoolXZ, &player[0].cameraPos) > 20000)
		{
			if (player[0].playerType == 2)
				player[0].cameraCarId = -1;
			else
				player[0].cameraCarId = player[0].playerCarId;

			gCameraOffset.vy = 0;
			cameraview = 0;
			return 1;
		}

		if (valid_region(player[0].cameraPos.vx, player[0].cameraPos.vz) != 0)
			return 0;

		player[0].cameraCarId = -1;

		if (player[0].playerType != 2)
			player[0].cameraCarId = player[0].playerCarId;

		// change it to the default view
		cameraview = 2;
		gCameraOffset.vy = 0;
		return 1;
	}

	invalidCamera = false;

	// check for invalid car
	if (car_num > -1)
		invalidCamera = (car_data[car_num].controlType == CONTROL_TYPE_NONE);

	// check if player is incorrect (pedestrian)
	if (car_num == -1 && player[0].playerType != 2)
		invalidCamera = true;

	// check events
	if (car_num < -1)
	{
		EVENT* event;
		XZPAIR pos;

		numEventModels = 0;

		if (*events.track != NULL)
		{
			do {
			} while (events.track[numEventModels++] != NULL);
		}

		if (-2 - car_num > numEventModels)
			invalidCamera = true;

		event = events.track[-2 - car_num];
		pos.x = event->position.vx;
		pos.z = event->position.vx;

		dx = ABS(player[0].pos[0] - pos.x);
		dz = ABS(player[0].pos[2] - pos.z);

		if (dx < 15000 && dz < 15000 &&
			dx * dx + dz * dz < 225000000)
		{
			invalidCamera = true;
		}
	}

	if (invalidCamera)
	{
		if (player[0].playerType == 2)
			player[0].cameraCarId = -1;
		else
			player[0].cameraCarId = player[0].playerCarId;

		gCameraOffset.vy = 0;
		return 1;
	}

	return 0;
}

// [D] [T]
int NoMoreCamerasErrorMessage(void)
{
	int strobe;

	if (FindFreeCamera())
		return 0;

	if ((FrameCnt & 0x1fU) < 16)
		strobe = FrameCnt & 0x1f;
	else
		strobe = 32 - (FrameCnt & 0x1fU);

	SetTextColour((strobe << 3), 0, 0);

	return 1;
}

// [D] [T]
int FirstCamera(void)
{
	if (LastChange && LastChange->prev != 255)
		return 0;

	return 1;
}


// [D] [T]
int dist(VECTOR* pos1, VECTOR* pos2)
{
	int dx;
	int dz;

	dx = (pos1->vx - pos2->vx) >> 4;
	dz = (pos1->vz - pos2->vz) >> 4;

	return SquareRoot0(dx * dx + dz * dz) << 4;
}


// [D] [T]
void SetCameraReturnedFromCutscene(int CameraCnt)
{
	PLAYBACKCAMERA* next;
	int count;

	count = 0;
	next = &PlaybackCamera[0];

	// how the fuck I'm supposed to untangle this logic?
	while (NextChange = next, 
		count < MAX_REPLAY_CAMERAS && 
		(NextChange = &PlaybackCamera[count], CameraCnt < NextChange->FrameCnt || NextChange->next != 254 && 
		(next = &PlaybackCamera[NextChange->next], next->FrameCnt <= CameraCnt)))
	{
		count++;
	}

	LastChange = NextChange;

	SetPlaybackCamera(NextChange);
	FindNextChange(CameraCnt + 1);
}





