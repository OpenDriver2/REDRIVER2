#include "THISDUST.H"
#include "DIRECTOR.H"
#include "CAMERA.H"
#include "PLAYERS.H"
#include "EVENT.H"
#include "OVERMAP.H"
#include "REPLAYS.H"
#include "CUTSCENE.H"
#include "CARS.H"
#include "PAUSE.H"
#include "MAIN.H"
#include "GLAUNCH.H"
#include "DR2ROADS.H"
#include "ROADBITS.H"
#include "SPOOL.H"
#include "MODELS.H"
#include "OBJCOLL.H"
#include "PRES.H"
#include "SOUND.H"
#include "SYSTEM.H"
#include "../MEMCARD/MAIN.H"

#include "STRINGS.H"
#include <stdlib.h>

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
	{ 20, 26, &pause, "Pause", 20, 48 },
	{ 20, 26, &playpause, "Play", 20, 48 },
	{ 44, 26, &autocam, "Auto Director", 44, 48 },
	{ 68, 26, &playcam, "Fast Forward", 68, 48 },
	{ 92, 26, &frameadv, "Frame Advance", 92, 48 },
	{ 116, 26, &restart, "Rewind to beginning", 116, 48 },
	{ 140, 26, &addcam, "Add Camera", 140, 48 },
	{ 164, 26, &editcam, "Edit Camera", 164, 48 },
	{ 188, 26, &save2card, "Save Replay", 188, 48 },
	{ 212, 26, &ok, "Exit", 212, 48 },
	{ 140, 50, &incar, "In Car", 164, 48 },
	{ 140, 74, &chasecar, "Chase Camera", 164, 72 },
	{ 140, 98, &fixedcam, "Tripod Camera", 164, 96 },
	{ 140, 122, &ok, "Accept", 164, 120 },
	{ 140, 122, &clock, "Move Camera Start", 164, 120 },
	{ 140, 146, &delcam, "Delete Camera", 164, 144 },
	{ 140, 170, &ok, "Accept", 164, 168 },
	{ 164, 50, &choosecar, "You or Pursuer", 164, 72 },
	{ 164, 74, &movecampos, "Move Camera", 164, 96 },
	{ 164, 98, &movecampos, "Move Camera", 164, 120 },
	{ 188, 98, &lookcar, "Lock to Car", 188, 120 },
	{ 212, 98, &movecam, "Rotate", 212, 120 },
	{ 236, 98, &lenschan, "Zoom", 236, 120 }
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

PLAYBACKCAMERA *LastChange = NULL;
PLAYBACKCAMERA *ThisChange = NULL;
PLAYBACKCAMERA *NextChange = NULL;

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

// decompiled code
// original method signature: 
// void /*$ra*/ InitDirectorVariables()
 // line 445, offset 0x0003e79c
	/* begin block 1 */
		// Start line: 447
		// Start offset: 0x0003E79C
		// Variables:
	// 		int count; // $a0
	/* end block 1 */
	// End offset: 0x0003E808
	// End Line: 467

	/* begin block 2 */
		// Start line: 3194
	/* end block 2 */
	// End Line: 3195

	/* begin block 3 */
		// Start line: 890
	/* end block 3 */
	// End Line: 891

	/* begin block 4 */
		// Start line: 3195
	/* end block 4 */
	// End Line: 3196

	/* begin block 5 */
		// Start line: 3199
	/* end block 5 */
	// End Line: 3200

/* WARNING: Unknown calling convention yet parameter storage is locked */

char GreyIcons[24];
int CursorX = 0;
int ClearCameras = 0;
int menuactive = 0;

// [D]
void InitDirectorVariables(void)
{
	char *pcVar1;
	int count;

	PlayMode = 0;
	CameraChanged = NoPlayerControl != 0;
	
	menuactive = 1;
	ClearCameras = 0;
	EditMode = 0;
	AutoDirect = 0;
	CursorX = 0;

	count = 23;
	do {
		GreyIcons[count--] = 0;
	} while (-1 < count);

	LastChange = NULL;
	FastForwardCameraCnt = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DeleteCurrentCamera(int CameraCnt /*$a0*/)
 // line 476, offset 0x0003e808
	/* begin block 1 */
		// Start line: 478
		// Start offset: 0x0003E808
		// Variables:
	// 		int prev; // $a1
	// 		int next; // $a0
	/* end block 1 */
	// End offset: 0x0003E88C
	// End Line: 491

	/* begin block 2 */
		// Start line: 3255
	/* end block 2 */
	// End Line: 3256

	/* begin block 3 */
		// Start line: 3265
	/* end block 3 */
	// End Line: 3266

	/* begin block 4 */
		// Start line: 3266
	/* end block 4 */
	// End Line: 3267

// [D]
void DeleteCurrentCamera(int CameraCnt)
{
	int prev;
	int next;
	PLAYBACKCAMERA *Change;

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



// decompiled code
// original method signature: 
// void /*$ra*/ setCamera(struct PLAYBACKCAMERA *Change /*$a0*/)
 // line 493, offset 0x0003e89c
	/* begin block 1 */
		// Start line: 3304
	/* end block 1 */
	// End Line: 3305

	/* begin block 2 */
		// Start line: 3305
	/* end block 2 */
	// End Line: 3306

// [D]
void setCamera(PLAYBACKCAMERA *Change)
{
	CameraPos.vy = Change->CameraPosvy;

	camera_angle.vx = Change->angle.vx;
	camera_angle.vy = Change->angle.vy;
	camera_angle.vz = Change->angle.vz;

	gCameraDistance = Change->gCameraDistance;
	gCameraMaxDistance = Change->gCameraMaxDistance;
	gCameraAngle = Change->gCameraAngle;
	cameraview = Change->cameraview & 7;

	tracking_car = (Change->cameraview & 8) >> 3;

	player[0].cameraPos.vx = Change->position.vx;
	player[0].cameraPos.vy = Change->position.vy;
	player[0].cameraPos.vz = Change->position.vz;
	player[0].cameraCarId = Change->angle.pad;
}



// decompiled code
// original method signature: 
// void /*$ra*/ EditCamera(int CameraCnt /*$a0*/)
 // line 513, offset 0x0003b2e4
	/* begin block 1 */
		// Start line: 515
		// Start offset: 0x0003B2E4
		// Variables:
	// 		int count; // $t0

		/* begin block 1.1 */
			// Start line: 543
			// Start offset: 0x0003B414
			// Variables:
		// 		int prev; // $a2
		// 		int next; // $v1
		/* end block 1.1 */
		// End offset: 0x0003B51C
		// End Line: 570
	/* end block 1 */
	// End offset: 0x0003B548
	// End Line: 572

	/* begin block 2 */
		// Start line: 1026
	/* end block 2 */
	// End Line: 1027

	/* begin block 3 */
		// Start line: 1027
	/* end block 3 */
	// End Line: 1028

	/* begin block 4 */
		// Start line: 1029
	/* end block 4 */
	// End Line: 1030

// [D]
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
	ThisChange->gCameraDistance = gCameraDistance;

	ThisChange->gCameraAngle = gCameraAngle;
	ThisChange->gCameraMaxDistance = gCameraMaxDistance;

	ThisChange->CameraPosvy = CameraPos.vy;

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
	} while (count < 60);
}



// decompiled code
// original method signature: 
// void /*$ra*/ RecordCamera(int CameraCnt /*$s0*/)
 // line 574, offset 0x0003b548
	/* begin block 1 */
		// Start line: 575
		// Start offset: 0x0003B548
		// Variables:
	// 		struct PLAYBACKCAMERA *TempChange; // $a1
	/* end block 1 */
	// End offset: 0x0003B794
	// End Line: 632

	/* begin block 2 */
		// Start line: 1208
	/* end block 2 */
	// End Line: 1209

	/* begin block 3 */
		// Start line: 1211
	/* end block 3 */
	// End Line: 1212

	/* begin block 4 */
		// Start line: 1214
	/* end block 4 */
	// End Line: 1215

// [D]
void RecordCamera(int CameraCnt)
{
	char cVar1;
	PLAYBACKCAMERA *TempChange;

	TempChange = FindFreeCamera();

	if (TempChange)
	{
		if (LastChange == NULL ||
			LastChange->cameraview != (cameraview & 7 | tracking_car << 3) ||
			player[0].cameraCarId != LastChange->angle.pad ||
			cameraview == 1 ||
			(cameraview & 7) == 5 ||
			LastChange->gCameraDistance != gCameraDistance ||
			LastChange->gCameraMaxDistance != gCameraMaxDistance ||
			LastChange->gCameraAngle != gCameraAngle ||
			LastChange->CameraPosvy != CameraPos.vy)
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
			LastChange->gCameraDistance = gCameraDistance;
			LastChange->FrameCnt = CameraCnt;
			LastChange->gCameraMaxDistance = gCameraMaxDistance;
			LastChange->gCameraAngle = gCameraAngle;
			LastChange->CameraPosvy = CameraPos.vy;
		}
	}

	FindNextChange(CameraCnt);
}



// decompiled code
// original method signature: 
// void /*$ra*/ FindNextChange(int CameraCnt /*$a0*/)
 // line 634, offset 0x0003e94c
	/* begin block 1 */
		// Start line: 635
		// Start offset: 0x0003E94C
		// Variables:
	// 		int count; // $a3
	// 		int nextframe; // $a2
	// 		int found; // $t0
	// 		struct PLAYBACKCAMERA *RestoreChange; // $t1
	/* end block 1 */
	// End offset: 0x0003E9B8
	// End Line: 655

	/* begin block 2 */
		// Start line: 3594
	/* end block 2 */
	// End Line: 3595

	/* begin block 3 */
		// Start line: 3595
	/* end block 3 */
	// End Line: 3596

// [D]
void FindNextChange(int CameraCnt)
{
	bool bVar1;
	PLAYBACKCAMERA *restoreChange;
	int iVar3;
	PLAYBACKCAMERA *pPVar4;
	int iVar5;
	int iVar6;

	restoreChange = NextChange;

	iVar5 = 0x186a1;
	bVar1 = false;
	iVar6 = 0x3b;
	NextChange = PlaybackCamera;
	pPVar4 = PlaybackCamera;
	do {
		iVar3 = pPVar4->FrameCnt;
		if ((CameraCnt <= iVar3) && (iVar3 < iVar5)) 
		{
			bVar1 = true;
			iVar5 = iVar3;
			NextChange = pPVar4;
		}

		iVar6 = iVar6 + -1;
		pPVar4 = pPVar4 + 1;
	} while (-1 < iVar6);

	if (!bVar1) 
	{
		NextChange = restoreChange;
		restoreChange->next = -2;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckCameraChange(int CameraCnt /*$s0*/)
 // line 658, offset 0x0003b794
	/* begin block 1 */
		// Start line: 1371
	/* end block 1 */
	// End Line: 1372

	/* begin block 2 */
		// Start line: 1398
	/* end block 2 */
	// End Line: 1399

	/* begin block 3 */
		// Start line: 1400
	/* end block 3 */
	// End Line: 1401


// [D]
int CheckCameraChange(int CameraCnt)
{
	if (JustReturnedFromCutscene != 0) 
	{
		JustReturnedFromCutscene = 0;
		SetCameraReturnedFromCutscene(CameraCnt);
	}

	if (((CameraCnt != -1) && (DoAutoDirect(), gStopPadReads == 0)) &&
		(InvalidCamera(player[0].cameraCarId) != 0))
	{
		RecordCamera(CameraCnt);
		return 0;
	}

	if (NextChange->FrameCnt != CameraCnt)
	{
		if (CameraCnt < NextChange->FrameCnt) 
		{
			IsMovingCamera(LastChange, NextChange, CameraCnt);
			return 0;
		}

		if (NextChange->next == -2) 
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

	if ((PlayMode == 1) && (CameraCnt != FastForwardCameraCnt))
	{
		SetFastForward = 0;
		FastForward = 0;
		pauseflag = PlayMode;
	}

	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetPlaybackCamera(struct PLAYBACKCAMERA *camera /*$a0*/)
 // line 710, offset 0x0003ec0c
	/* begin block 1 */
		// Start line: 5354
	/* end block 1 */
	// End Line: 5355

	/* begin block 2 */
		// Start line: 1420
	/* end block 2 */
	// End Line: 1421

	/* begin block 3 */
		// Start line: 5355
	/* end block 3 */
	// End Line: 5356

// [D]
void SetPlaybackCamera(PLAYBACKCAMERA *camera)
{
	CameraPos.vy = camera->CameraPosvy;
	camera_angle.vx = (camera->angle).vx;
	camera_angle.vy = (camera->angle).vy;
	camera_angle.vz = (camera->angle).vz;
	gCameraDistance = camera->gCameraDistance;
	gCameraMaxDistance = camera->gCameraMaxDistance;
	gCameraAngle = camera->gCameraAngle;
	cameraview = camera->cameraview & 7;

	tracking_car = (camera->cameraview & 8) >> 3;

	CameraChanged = 1;

	player[0].cameraPos.vx = (camera->position).vx;
	player[0].cameraPos.vy = (camera->position).vy;
	player[0].cameraPos.vz = (camera->position).vz;
	player[0].cameraCarId = camera->angle.pad;
}



// decompiled code
// original method signature: 
// int /*$ra*/ IsMovingCamera(struct PLAYBACKCAMERA *lastcam /*$t3*/, struct PLAYBACKCAMERA *nextcam /*$t0*/, int cameracnt /*$a2*/)
 // line 731, offset 0x0003b8c8
	/* begin block 1 */
		// Start line: 732
		// Start offset: 0x0003B8C8
		// Variables:
	// 		struct PLAYBACKCAMERA cam; // stack offset -56
	// 		long xdist; // $t5
	// 		long ydist; // $t6
	// 		long zdist; // $t4
	// 		long xangle; // $a3
	// 		long yangle; // $t1
	// 		long zangle; // $t2
	// 		int s; // $a0
	// 		int e; // $v1
	// 		int f; // $t8
	// 		int t; // $a2
	// 		int nextcview; // $a0
	/* end block 1 */
	// End offset: 0x0003BBA8
	// End Line: 792

	/* begin block 2 */
		// Start line: 1546
	/* end block 2 */
	// End Line: 1547

// [D]
int IsMovingCamera(PLAYBACKCAMERA *lastcam, PLAYBACKCAMERA *nextcam, int cameracnt)
{
	int iVar1;
	PLAYBACKCAMERA *pPVar2;
	int iVar3;
	int iVar4;
	unsigned char bVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	PLAYBACKCAMERA *pPVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	long lVar15;
	long lVar16;
	uint uVar17;
	uint uVar18;
	PLAYBACKCAMERA cam;

	if (lastcam == NULL)
		return 0;

	if (cameraview != 5 && cameraview != 1)
		return 0;

	bVar5 = nextcam->cameraview & 0x87;

	if ((bVar5 == 133) || (bVar5 == 129))
	{
		cameracnt = cameracnt - lastcam->FrameCnt;
		iVar14 = nextcam->FrameCnt - lastcam->FrameCnt;
		uVar18 = (cameracnt * 0x800) / iVar14;

		iVar7 = nextcam->position.vx;
		iVar6 = nextcam->position.vy;
		iVar10 = (rcossin_tbl[(uVar18 * 3 & 0xfff) * 2 + 1] + rcossin_tbl[(uVar18 & 0xfff) * 2 + 1] * -9 >> 4) + 0x800;

		iVar3 = lastcam->position.vx;
		iVar1 = lastcam->position.vy;
		iVar8 = nextcam->position.vz;
		iVar4 = lastcam->position.vz;

		iVar11 = nextcam->angle.vx - lastcam->angle.vx;
		iVar12 = nextcam->angle.vy - lastcam->angle.vy;
		iVar13 = nextcam->angle.vz - lastcam->angle.vz;

		if (iVar11 < -0x800) {
			iVar11 = iVar11 + 0x1000;
		}
		if (0x800 < iVar11) {
			iVar11 = iVar11 + -0x1000;
		}
		if (iVar12 < -0x800) {
			iVar12 = iVar12 + 0x1000;
		}
		if (0x800 < iVar12) {
			iVar12 = iVar12 + -0x1000;
		}
		if (iVar13 < -0x800) {
			iVar13 = iVar13 + 0x1000;
		}
		if (0x800 < iVar13) {
			iVar13 = iVar13 + -0x1000;
		}

		memcpy(&cam, lastcam, sizeof(PLAYBACKCAMERA));

		cam.position.vx = lastcam->position.vx;
		cam.position.vx = lastcam->position.vx + ((iVar7 - iVar3) * 0x40 * iVar10 + 0x20000 >> 0x12);
		cam.position.vy = lastcam->position.vy + ((iVar6 - iVar1) * 0x40 * iVar10 + 0x20000 >> 0x12);
		cam.position.vz = lastcam->position.vz + ((iVar8 - iVar4) * 0x40 * iVar10 + 0x20000 >> 0x12);

		cam.angle.vx = lastcam->angle.vx + (short)(((iVar11 << 6) / iVar14) * cameracnt >> 6);
		cam.angle.vy = lastcam->angle.vy + (short)(((iVar12 << 6) / iVar14) * cameracnt >> 6);
		cam.angle.vz = lastcam->angle.vz + (short)(((iVar13 << 6) / iVar14) * cameracnt >> 6);

		SetPlaybackCamera(&cam);

		return 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CameraBar(int CameraCnt /*stack 0*/)
 // line 794, offset 0x0003bba8
	/* begin block 1 */
		// Start line: 795
		// Start offset: 0x0003BBA8
		// Variables:
	// 		struct POLY_G4 *camera; // $a2
	// 		struct LINE_F2 *bar; // $t2
	// 		int x; // $a2
	// 		int min_x; // $t1
	// 		int max_x; // $t0
	// 		int min_y; // $s3
	// 		char red; // $s0
	// 		char green; // $s4
	// 		char blue; // $fp
	// 		int bar_x; // $s1
	// 		int first; // stack offset -48
	// 		int last; // $s7
	// 		unsigned long idx; // $t9
	/* end block 1 */
	// End offset: 0x0003C184
	// End Line: 927

	/* begin block 2 */
		// Start line: 1690
	/* end block 2 */
	// End Line: 1691

	/* begin block 3 */
		// Start line: 1693
	/* end block 3 */
	// End Line: 1694

	/* begin block 4 */
		// Start line: 1697
	/* end block 4 */
	// End Line: 1698

// [D] please process it and refactor; It works fines
void CameraBar(int CameraCnt)
{
	bool bVar1;
	unsigned char uVar2;
	short sVar3;
	int iVar4;
	unsigned  bVar5;
	PLAYBACKCAMERA* local_v1_272;
	int iVar6;
	unsigned  uVar7;
	PLAYBACKCAMERA* local_a0_1024;
	int iVar8;
	POLY_G4* camera;
	LINE_F2* bar;
	short sVar9;
	int iVar10;
	short sVar11;
	uint uVar12;
	
	uint uVar13;
	uint uVar14;
	int iVar15;
	uint uVar16;
	uint uVar17;

	uVar13 = 0;
	uVar14 = 0;
	uVar17 = 0;
	iVar15 = 1;
	
	bVar1 = true;

	bar = (LINE_F2*)current->primptr;

	setLineF2(bar);

	bar->r0 = 0;
	bar->g0 = 0;
	bar->b0 = 0;
	bar->y0 = 0xc;
	bar->x0 = 0xa0;
	bar->x1 = 0xa0;
	bar->y1 = 0x16;

	addPrim(current->ot, bar);
	current->primptr += sizeof(LINE_F2);

	if (PlaybackCamera->FrameCnt == 100000)
		return;

	iVar4 = 0;
	uVar16 = 0;

	do {
		local_v1_272 = &PlaybackCamera[uVar16]; //(PLAYBACKCAMERA*)(&(PlaybackCamera->position).vx + iVar4 + uVar16);

		if (local_v1_272->next < 60)
			iVar10 = PlaybackCamera[local_v1_272->next].FrameCnt;
		else
			iVar10 = 200000;

		iVar6 = ReplayParameterPtr->RecordingEnd + 1;

		if (iVar6 < iVar10) 
		{
			iVar15 = 2;
			iVar10 = iVar6;
		}

		uVar12 = local_v1_272->FrameCnt + 0xa0;

		sVar11 = uVar12 - CameraCnt;
		iVar6 = (uVar12 - (uVar12 & 0x1f)) - CameraCnt;
		iVar10 = (iVar10 + 0xa0) - CameraCnt;
		sVar9 = (short)iVar10;

		if (((bVar1) && (0x1e < sVar11)) && (sVar11 < 0x122))
		{
			bar = (LINE_F2*)current->primptr;

			setLineF2(bar);

			bar->r0 = 0;
			bar->g0 = 0;
			bar->b0 = 0;
			bar->x0 = sVar11;
			bar->y0 = 0xf;
			bar->x1 = sVar11;
			bar->y1 = 0x13;

			addPrim(current->ot, bar);
			current->primptr += sizeof(LINE_F2);
		}

		iVar8 = 0;

		if (iVar15 != 0) 
		{
			do {
				if (iVar10 - 31 < 259)
				{
					bar = (LINE_F2*)current->primptr;
					setLineF2(bar);

					bar->r0 = 0;
					bar->g0 = 0;
					bar->b0 = 0;

					sVar3 = sVar9 + iVar8;

					bar->x0 = sVar3;
					bar->y0 = 0xf;
					bar->x1 = sVar3;
					bar->y1 = 0x13;

					addPrim(current->ot, bar);
					current->primptr += sizeof(LINE_F2);
				}

				iVar8++;
			} while (iVar8 < iVar15);
		}

		while (iVar6 < iVar10) 
		{
			if (iVar6 - 0x1fU < 0x103)
			{
				bar = (LINE_F2*)current->primptr;
				setLineF2(bar);

				bar->r0 = 0;
				bar->g0 = 0;
				bar->b0 = 0;

				bar->x0 = iVar6;
				bar->y0 = 0x11;
				bar->x1 = iVar6;
				bar->y1 = 0x13;

				addPrim(current->ot, bar);
				current->primptr += sizeof(LINE_F2);
			}
			iVar6 = iVar6 + 0x20;
		}

		local_a0_1024 = &PlaybackCamera[uVar16]; // (PLAYBACKCAMERA*)(&(PlaybackCamera->position).vx + iVar4 + uVar16);
		bVar5 = local_a0_1024->cameraview & 7;

		if (bVar5 == 1)
		{
			uVar13 = 0;
		LAB_0003c030:
			uVar14 = 0xff;
		LAB_0003c034:
			uVar17 = 0;
		}
		else if (bVar5 == 0)
		{
			uVar13 = 0xff;
			uVar14 = 0;
			goto LAB_0003c034;
		}
		else if (bVar5 == 2)
		{
			uVar13 = 0x46;

			if ((local_a0_1024->angle).pad == 0)
			{
				uVar14 = 0x46;
				uVar17 = 0xff;
			}
			else
			{
				uVar14 = 0xff;
				uVar17 = 0xff;
			}
		}
		else if (bVar5 == 5)
		{
			uVar13 = 0xff;
			goto LAB_0003c030;
		}

		camera = (POLY_G4*)current->primptr;

		setPolyG4(camera);

		camera->r1 = (uVar13 >> 1);
		camera->b1 = (uVar17 >> 1);
		camera->g1 = (uVar14 >> 1);
		uVar2 = (uVar14 >> 2);
		camera->g2 = uVar2;
		camera->g3 = uVar2;
		camera->r0 = uVar13;
		camera->g0 = uVar14;
		camera->b0 = uVar17;
		uVar7 = (uVar13 >> 2);
		camera->r2 = uVar7;
		uVar2 = (uVar17 >> 2);
		camera->b2 = uVar2;
		camera->r3 = uVar7;
		camera->b3 = uVar2;

		bVar5 = PlaybackCamera[uVar16].next;//(&PlaybackCamera->next)[(iVar4 + uVar16) * 4];
		uVar16 = (uint)bVar5;

		if (0x122 < sVar11)
			return;

		if (0x122 < iVar10)
			sVar9 = 0x122;

		if (0x1d < iVar10) 
		{
			if (sVar11 < 0x1e)
				sVar11 = 0x1e;

			camera->x0 = sVar11;
			camera->y0 = 0xf;
			camera->x1 = sVar9;
			camera->y1 = 0xf;
			camera->x2 = sVar11;
			camera->y2 = 0x14;
			camera->x3 = sVar9;
			camera->y3 = 0x14;

			addPrim(current->ot, camera);

			bVar1 = false;
			current->primptr += sizeof(POLY_G4);
		}

		if (PlaybackCamera[uVar16].FrameCnt == 100000)
			return;
	
		iVar4 = uVar16 << 3;

		if (0x3b < bVar5)
			return;

	} while (true);
}



// decompiled code
// original method signature: 
// struct PLAYBACKCAMERA * /*$ra*/ FindFreeCamera()
 // line 929, offset 0x0003e9b8
	/* begin block 1 */
		// Start line: 931
		// Start offset: 0x0003E9B8
		// Variables:
	// 		int count; // $a1
	/* end block 1 */
	// End offset: 0x0003E9F8
	// End Line: 941

	/* begin block 2 */
		// Start line: 3920
	/* end block 2 */
	// End Line: 3921

	/* begin block 3 */
		// Start line: 4195
	/* end block 3 */
	// End Line: 4196

	/* begin block 4 */
		// Start line: 4196
	/* end block 4 */
	// End Line: 4197

	/* begin block 5 */
		// Start line: 4198
	/* end block 5 */
	// End Line: 4199

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
PLAYBACKCAMERA * FindFreeCamera(void)
{
	int count;

	count = 0;

	do {
		if (PlaybackCamera[count].FrameCnt == 100000)
			return &PlaybackCamera[count];

		count++;
	} while (count < 60);

	return NULL;
}



// decompiled code
// original method signature: 
// void /*$ra*/ deleteCamera(int count /*$a0*/)
 // line 943, offset 0x0003e9f8
	/* begin block 1 */
		// Start line: 4224
	/* end block 1 */
	// End Line: 4225

	/* begin block 2 */
		// Start line: 4227
	/* end block 2 */
	// End Line: 4228

	/* begin block 3 */
		// Start line: 4228
	/* end block 3 */
	// End Line: 4229

// [D]
void deleteCamera(int count)
{
	PlaybackCamera[count].idx = count;
	PlaybackCamera[count].prev = -1;
	PlaybackCamera[count].FrameCnt = 100000;
	PlaybackCamera[count].next = -2;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DeleteAllCameras()
 // line 951, offset 0x0003ea40
	/* begin block 1 */
		// Start line: 953
		// Start offset: 0x0003EA40
		// Variables:
	// 		struct PLAYBACKCAMERA nextcamera; // stack offset -48
	// 		int count; // $s0
	/* end block 1 */
	// End offset: 0x0003EAA4
	// End Line: 964

	/* begin block 2 */
		// Start line: 4248
	/* end block 2 */
	// End Line: 4249

	/* begin block 3 */
		// Start line: 4249
	/* end block 3 */
	// End Line: 4250

	/* begin block 4 */
		// Start line: 4252
	/* end block 4 */
	// End Line: 4253

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DeleteAllCameras(void)
{
	int count;

	count = 0;
	do {
		deleteCamera(count);
		count++;
	} while (count < 60);

	LastChange = NULL;

	RecordCamera(0);
	CheckCameraChange(-1);

	LastChange->prev = -1;
	LastChange->next = -2;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ShowIcons(char *menu /*$s3*/, int selected /*stack 4*/, int x_offset /*$s7*/)
 // line 966, offset 0x0003c1b0
	/* begin block 1 */
		// Start line: 967
		// Start offset: 0x0003C1B0
		// Variables:
	// 		static int FlashCnt; // offset 0x0
	// 		struct REPLAY_ICON *IconPtr; // $s0
	// 		struct SPRT *icon; // $a2
	// 		int count; // $s6

		/* begin block 1.1 */
			// Start line: 1027
			// Start offset: 0x0003C340
			// Variables:
		// 		struct TEXTURE_DETAILS *Icon_texture; // $s1
		// 		int min_x; // $v1
		// 		int min_y; // $a0

			/* begin block 1.1.1 */
				// Start line: 1035
				// Start offset: 0x0003C364
			/* end block 1.1.1 */
			// End offset: 0x0003C384
			// End Line: 1037

			/* begin block 1.1.2 */
				// Start line: 1048
				// Start offset: 0x0003C3E4
				// Variables:
			// 		int ramp; // $a0
			/* end block 1.1.2 */
			// End offset: 0x0003C448
			// End Line: 1059
		/* end block 1.1 */
		// End offset: 0x0003C470
		// End Line: 1066
	/* end block 1 */
	// End offset: 0x0003C5BC
	// End Line: 1096

	/* begin block 2 */
		// Start line: 2127
	/* end block 2 */
	// End Line: 2128

	/* begin block 3 */
		// Start line: 2136
	/* end block 3 */
	// End Line: 2137

// [D]
void ShowIcons(unsigned char *menu, int selected, int x_offset)
{
	static int FlashCnt = 0;

	unsigned int cVar5;
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

	if (tracking_car == 0 || OK_To_Zoom() == 0)
		GreyIcons[22] = 1;
	else
		GreyIcons[22] = 0;

	GreyIcons[14] = FirstCamera() != 0;
	GreyIcons[15] = GreyIcons[14];

	while (*menu != 0xff) 
	{
		Icon_texture = replay_icons[*menu].texture;

		if (selected == count)
		{
			SetTextColour(128, 128, 64);
			PrintStringBoxed(replay_icons[*menu].TextPtr, replay_icons[*menu].tx + x_offset + 1, replay_icons[*menu].ty);
		}

		icon = (SPRT*)current->primptr;
		setSprt(icon);

		if (GreyIcons[*menu] == 0) 
		{
			if (selected == count) 
			{
				cVar5 = (FlashCnt & 0xf);

				if ((FlashCnt & 0xf) < 8) 
					cVar5 = 7 - cVar5;
				else
					cVar5 -= 7;

				if (EditMode == 0) 
				{
					icon->r0 = -1;
					icon->g0 = -1;
					icon->b0 = -1;
					FlashCnt = 0;
				}
				else 
				{
					icon->r0 = icon->g0 = icon->b0 = cVar5 * 28 + 30;;
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



// decompiled code
// original method signature: 
// void /*$ra*/ ShowReplayOptions()
 // line 1098, offset 0x0003eaa4
	/* begin block 1 */
		// Start line: 1100
		// Start offset: 0x0003EAA4
		// Variables:
	// 		static int toggle_icons; // offset 0x6c
	/* end block 1 */
	// End offset: 0x0003EAE0
	// End Line: 1133

	/* begin block 2 */
		// Start line: 4409
	/* end block 2 */
	// End Line: 4410

	/* begin block 3 */
		// Start line: 4544
	/* end block 3 */
	// End Line: 4545

	/* begin block 4 */
		// Start line: 4545
	/* end block 4 */
	// End Line: 4546

	/* begin block 5 */
		// Start line: 4550
	/* end block 5 */
	// End Line: 4551

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void ShowReplayOptions(void)
{
	if (gInGameCutsceneActive == 0 && quick_replay == 0) 
	{
		ShowReplayMenu();
		CameraBar(CameraCnt);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ShowReplayMenu()
 // line 1135, offset 0x0003c5bc
	/* begin block 1 */
		// Start line: 1137
		// Start offset: 0x0003C5BC

		/* begin block 1.1 */
			// Start line: 1139
			// Start offset: 0x0003C5E4
		/* end block 1.1 */
		// End offset: 0x0003C608
		// End Line: 1143

		/* begin block 1.2 */
			// Start line: 1147
			// Start offset: 0x0003C620
		/* end block 1.2 */
		// End offset: 0x0003C63C
		// End Line: 1151

		/* begin block 1.3 */
			// Start line: 1178
			// Start offset: 0x0003C750
			// Variables:
		// 		int strobe; // $v0
		/* end block 1.3 */
		// End offset: 0x0003C798
		// End Line: 1182
	/* end block 1 */
	// End offset: 0x0003C7A8
	// End Line: 1184

	/* begin block 2 */
		// Start line: 2486
	/* end block 2 */
	// End Line: 2487

	/* begin block 3 */
		// Start line: 2526
	/* end block 3 */
	// End Line: 2527

	/* begin block 4 */
		// Start line: 2527
	/* end block 4 */
	// End Line: 2528

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void ShowReplayMenu(void)
{
	unsigned char *menu;
	uint uVar1;
	int selected;

	if (menuactive < 1 && PlayMode != 2 && PlayMode != 3) 
	{
		UnPauseSound();
		ShowIcons(menu0, 0, 0);
	}
	else 
	{
		PauseSound();

		selected = CursorX;

		if (menuactive != 1)
			selected = 99;

		ShowIcons(menu1, selected, 0);
	}

	if (menuactive > 1) 
	{
		if (MenuOffset == 0) 
		{
			if (menuactive != 2)
			{
				ShowIcons(menu2, 99, 0);
				goto LAB_0003c6c4;
			}

			menu = menu2;
			selected = 0;
		}
		else 
		{
			if (menuactive != 2)
			{
				ShowIcons(menu6, 99, MenuOffset);
				goto LAB_0003c6c4;
			}

			menu = menu6;
			selected = MenuOffset;
		}

		ShowIcons(menu, CursorY + -1, selected);
	}

LAB_0003c6c4:
	if (menuactive == 3) 
	{
		ShowIcons(menu3, CursorX - 6, MenuOffset);
	}
	else if (menuactive == 4)
	{
		ShowIcons(menu4, CursorX - 6, MenuOffset);
	}
	else if (menuactive == 5)
	{
		ShowIcons(menu5, CursorX - 6, MenuOffset);
	}

	if ((AutoDirect != 0) && (pauseflag == 0))
	{
		uVar1 = CameraCnt & 0x1f;

		if (0xf < uVar1)
			uVar1 = 0x20 - uVar1;
	
		SetTextColour((uVar1 << 3), 0, 0);
		PrintString("Auto direct", 100, 0x1e);
	}
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ControlReplay()
 // line 1186, offset 0x0003c7a8
	/* begin block 1 */
		// Start line: 1188
		// Start offset: 0x0003C7A8
		// Variables:
	// 		static int debounce; // offset 0x70
	// 		static int first_time; // offset 0x74
	// 		int move; // $s0

		/* begin block 1.1 */
			// Start line: 1271
			// Start offset: 0x0003CA00
			// Variables:
		// 		int speed; // $s2

			/* begin block 1.1.1 */
				// Start line: 1281
				// Start offset: 0x0003CA68
			/* end block 1.1.1 */
			// End offset: 0x0003CA8C
			// End Line: 1285

			/* begin block 1.1.2 */
				// Start line: 1288
				// Start offset: 0x0003CAA4
				// Variables:
			// 		int prev; // $v1
			/* end block 1.1.2 */
			// End offset: 0x0003CADC
			// End Line: 1291

			/* begin block 1.1.3 */
				// Start line: 1327
				// Start offset: 0x0003CC34
				// Variables:
			// 		struct ROUTE_DATA routeData; // stack offset -96
			// 		int road_height; // $s1
			/* end block 1.1.3 */
			// End offset: 0x0003CCB0
			// End Line: 1338

			/* begin block 1.1.4 */
				// Start line: 1347
				// Start offset: 0x0003CCBC
				// Variables:
			// 		struct VECTOR old_camera; // stack offset -88
			// 		int x; // $s5
			// 		int z; // $s4
			// 		int d; // $s3
			// 		int angle; // $s1
			// 		char cameraCar; // $a0
			// 		int dx; // $s1
			// 		int dz; // $s0
			// 		struct VECTOR basePos; // stack offset -72
			// 		struct VECTOR tmpPos; // stack offset -56

				/* begin block 1.1.4.1 */
					// Start line: 1372
					// Start offset: 0x0003CD38
					// Variables:
				// 		struct _EVENT *event; // $a1
				/* end block 1.1.4.1 */
				// End offset: 0x0003CD68
				// End Line: 1376

				/* begin block 1.1.4.2 */
					// Start line: 1410
					// Start offset: 0x0003CE64
					// Variables:
				// 		int temp; // $v0
				/* end block 1.1.4.2 */
				// End offset: 0x0003CE70
				// End Line: 1414

				/* begin block 1.1.4.3 */
					// Start line: 1431
					// Start offset: 0x0003CF28
				/* end block 1.1.4.3 */
				// End offset: 0x0003CF74
				// End Line: 1450

				/* begin block 1.1.4.4 */
					// Start line: 1454
					// Start offset: 0x0003CF74
					// Variables:
				// 		struct ROUTE_DATA routeData; // stack offset -40
				// 		int road_height; // $s1
				/* end block 1.1.4.4 */
				// End offset: 0x0003D064
				// End Line: 1475
			/* end block 1.1.4 */
			// End offset: 0x0003D088
			// End Line: 1477
		/* end block 1.1 */
		// End offset: 0x0003D1C8
		// End Line: 1506

		/* begin block 1.2 */
			// Start line: 1560
			// Start offset: 0x0003D50C

			/* begin block 1.2.1 */
				// Start line: 1682
				// Start offset: 0x0003D808
			/* end block 1.2.1 */
			// End offset: 0x0003D808
			// End Line: 1682

			/* begin block 1.2.2 */
				// Start line: 1791
				// Start offset: 0x0003DA6C
				// Variables:
			// 		int prev1; // $a1
			/* end block 1.2.2 */
			// End offset: 0x0003DAAC
			// End Line: 1801
		/* end block 1.2 */
		// End offset: 0x0003DE0C
		// End Line: 1975
	/* end block 1 */
	// End offset: 0x0003DE38
	// End Line: 1988

	/* begin block 2 */
		// Start line: 2625
	/* end block 2 */
	// End Line: 2626

	/* begin block 3 */
		// Start line: 2628
	/* end block 3 */
	// End Line: 2629

	/* begin block 4 */
		// Start line: 2629
	/* end block 4 */
	// End Line: 2630

	/* begin block 5 */
		// Start line: 2636
	/* end block 5 */
	// End Line: 2637

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void ControlReplay(void)
{
	static int debounce; // offset 0x70
	static int first_time; // offset 0x74

	unsigned char bVar1;
	unsigned char bVar2;
	long lVar3;
	int iVar4;
	PLAYBACKCAMERA *pPVar5;
	GAMEMODE mode;
	int y;
	uint dir;
	int x;
	int iVar6;
	int iVar7;
	ROUTE_DATA routeData1;
	VECTOR old_camera;
	VECTOR basePos;
	VECTOR tmpPos;
	ROUTE_DATA routeData;

	dir = 0;
	if (gInGameCutsceneActive != 0)
		return;


	if ((quick_replay != 0) || (AttractMode != 0)) 
	{
		if (((padd != 0) || (ReplayParameterPtr->RecordingEnd <= CameraCnt)) && (2 < CameraCnt)) 
		{
			ReleaseInGameCutscene();

			if (AttractMode == 0) 
				EnablePause(gMissionCompletionState);
			else
				EndGame(GAMEMODE_QUIT);

			time_taken = vblcounter;
			return;
		}
		pauseflag = 0;
		return;
	}

	if (((padd & 0x8000U) != 0) && (debounce == 0)) 
	{
		dir = 2;
		debounce = 1;
	}
	if (((padd & 0x2000U) != 0) && (debounce == 0))
	{
		dir = 1;
		debounce = 1;
	}
	if (((padd & 0x1000U) != 0) && (debounce == 0)) 
	{
		dir = 3;
		debounce = 1;
	}
	if (((padd & 0x4000U) != 0) && (debounce == 0)) 
	{
		dir = 4;
		debounce = 1;
	}
	if (((padd & 0x40U) != 0) && (debounce == 0)) 
	{
		if (menuactive == 0)
			pauseflag = 1;
		else
			dir = 5;

		FastForward = 0;
		SetFastForward = 0;
		debounce = 1;
	}

	if (((padd & 0x8000U) == 0) && ((padd & 0x7040U) == 0)) 
	{
		debounce = 0;
	}

	if ((EditMode != 0) && (dir != 5)) 
	{
		iVar6 = 1;
		if ((padd & 8U) != 0) 
		{
			iVar6 = 8;
		}
		if (EditMode == 2)
		{
			if (((padd & 0x1000U) != 0) && (1000 < gCameraDistance)) 
			{
				gCameraDistance = gCameraDistance + iVar6 * -0x10;
				gCameraMaxDistance = gCameraMaxDistance + iVar6 * -0x10;
			}

			if (((padd & 0x4000U) != 0) && (gCameraDistance < 4000)) 
			{
				gCameraDistance = gCameraDistance + iVar6 * 0x10;
				gCameraMaxDistance = gCameraMaxDistance + iVar6 * 0x10;
			}

			if (((int)padd & 0x8000U) != 0)
				gCameraAngle = gCameraAngle + iVar6 * 0x10;

			if ((padd & 0x2000U) != 0)
				gCameraAngle = gCameraAngle + iVar6 * -0x10;

			if (((padd & 4U) != 0) && (-0x348 < CameraPos.vy))
				CameraPos.vy = CameraPos.vy + iVar6 * -0x10;
		
			if (((padd & 1U) != 0) && (CameraPos.vy < -0x38))
				CameraPos.vy = CameraPos.vy + iVar6 * 0x10;

			iVar6 = MapHeight(&player[0].cameraPos);
			ROADS_GetRouteData(player[0].cameraPos.vx, player[0].cameraPos.vz, &routeData1);

			if ((modelpointers[routeData1.type]->flags2 & 0x100) != 0)
			{
				iVar6 = -0x1c2 - iVar6;
				player[0].cameraPos.vy = CameraPos.vy - player[0].pos[1];

				if (CameraPos.vy - player[0].pos[1] < iVar6)
				{
					CameraPos.vy = iVar6 + player[0].pos[1];
					player[0].cameraPos.vy = iVar6;
				}
			}
		LAB_0003d1c4:
			dir = 0;
		}
		else 
		{
			if (EditMode < 3) 
			{
				dir = 0;
				if (EditMode == 1)
				{
					if (((padd & 0x2000U) != 0) && (LastChange->FrameCnt < CameraCnt)) 
					{
						LastChange->FrameCnt = LastChange->FrameCnt + 1;
					}

					dir = 0;

					if ((((int)padd & 0x8000U) != 0) &&
						(PlaybackCamera[LastChange->prev].FrameCnt < LastChange->FrameCnt)) 
					{
						LastChange->FrameCnt = LastChange->FrameCnt + -1;
					}
				}
			}
			else if (EditMode == 3)
			{
				iVar7 = 0;
				iVar4 = 0;
				y = (int)player[0].cameraCarId;
				if (y < 0)
				{
					if (y == -1)
					{
						basePos.vx = player[0].pos[0];
						basePos.vz = player[0].pos[2];
					}
					else
					{
						basePos.vx = (events.track[y * 0x3fffffff + -2]->position).vx;
						basePos.vz = (events.track[y * 0x3fffffff + -2]->position).vz;
					}
				}
				else
				{
					basePos.vx = car_data[y].hd.where.t[0];
					basePos.vz = car_data[y].hd.where.t[2];
				}

				x = basePos.vx - player[0].cameraPos.vx;
				y = basePos.vz - player[0].cameraPos.vz;
				old_camera.vx = player[0].cameraPos.vx;
				old_camera.vz = player[0].cameraPos.vz;
				old_camera.vy = player[0].cameraPos.vy;
				lVar3 = SquareRoot0(x * x + y * y);

				if (tracking_car == 0)
					dir = camera_angle.vy;
				else
					dir = ratan2(y, x);

				if (((padd & 0x1000U) != 0) && ((tracking_car == 0 || (500 < lVar3))))
					iVar7 = iVar6 * -0x10;

				if ((padd & 0x4000U) != 0)
					iVar7 = iVar6 << 4;

				if (((padd & 0x8000U) != 0) && ((tracking_car == 0 || (500 < lVar3))))
					iVar4 = iVar6 * -0x10;

				if ((padd & 0x2000U) != 0)
					iVar4 = iVar6 << 4;

				y = iVar7;

				if (tracking_car == 0)
				{
					y = -iVar4;
					iVar4 = iVar7;
				}

				player[0].cameraPos.vx = (player[0].cameraPos.vx + (iVar4 * rcossin_tbl[(dir & 0xfff) * 2] >> 0xc)) - (y * rcossin_tbl[(dir & 0xfff) * 2 + 1] >> 0xc);
				player[0].cameraPos.vz = (player[0].cameraPos.vz - (iVar4 * rcossin_tbl[(dir & 0xfff) * 2 + 1] >> 0xc)) - (y * rcossin_tbl[(dir & 0xfff) * 2] >> 0xc);

				iVar4 = dist(player[0].spoolXZ, &player[0].cameraPos);

				if (iVar4 < 0x4801)
				{
					tmpPos.vx = player[0].cameraPos.vx;
					tmpPos.vy = -player[0].cameraPos.vy;
					tmpPos.vz = player[0].cameraPos.vz;

					if (QuickBuildingCollisionCheck(&tmpPos, dir, 10, 10, 10) != 0)
						goto LAB_0003cf74;
				}
				else
				{
					player[0].cameraPos.vy = old_camera.vy;
				LAB_0003cf74:
					player[0].cameraPos.vx = old_camera.vx;
					player[0].cameraPos.vz = old_camera.vz;
				}

				iVar4 = -MapHeight(&player[0].cameraPos);

				if ((padd & 4U) != 0)
				{
					player[0].cameraPos.vy = player[0].cameraPos.vy + iVar6 * -0x10;
				}

				if ((padd & 1U) != 0)
				{
					player[0].cameraPos.vy = player[0].cameraPos.vy + iVar6 * 0x10;
				}

				if (iVar4 - MIN_TRIPOD_CAMERA_HEIGHT < player[0].cameraPos.vy)
					player[0].cameraPos.vy = iVar4 - MIN_TRIPOD_CAMERA_HEIGHT;

				if (player[0].cameraPos.vy < iVar4 + -0x41a)
					player[0].cameraPos.vy = iVar4 + -0x41a;


				ROADS_GetRouteData(player[0].cameraPos.vx, player[0].cameraPos.vz, &routeData);

				if (((modelpointers[routeData.type]->flags2 & 0x100) != 0) && (player[0].cameraPos.vy < iVar4 + -0x1c2))
					player[0].cameraPos.vy = iVar4 + -0x1c2;

				dir = 0;

				if ((cameraview == 1) && (OK_To_Zoom() == 0))
				{
					cameraview = 5;
				}
			}
			else
			{
				dir = 0;
				if (EditMode == 4)
				{
					if (((padd & 0x1000U) != 0) &&
						(iVar4 = camera_angle.vx + iVar6 * 4,
							camera_angle.vx = (short)iVar4, (iVar4 - 300U & 0xffff) < 0x6d5))
					{
						camera_angle.vx = 300;
					}

					if (((padd & 0x4000U) != 0) &&
						(iVar4 = camera_angle.vx + iVar6 * -4,
							camera_angle.vx = (short)iVar4, (iVar4 - 0x800U & 0xffff) < 0x73d))
					{
						camera_angle.vx = 0xf3c;
					}

					if ((padd & 0x8000U) != 0)
					{
						camera_angle.vy = camera_angle.vy + (short)iVar6 * 4;
					}

					if ((padd & 0x2000U) != 0)
					{
						camera_angle.vy = camera_angle.vy + (short)iVar6 * -4;
					}

					camera_angle.vx = camera_angle.vx & 0xfff;
					camera_angle.vy = camera_angle.vy & 0xfff;
					camera_angle.vz = camera_angle.vz & 0xfff;
					goto LAB_0003d1c4;
				}
			}
		}
	}

	if (dir == 1)
	{
		CursorX = CursorX + 1;
		if ((((CameraCnt < ReplayParameterPtr->RecordingEnd) || (menuactive != 1)) ||
			(iVar6 = 7, CursorX != 5)) &&
			(((pPVar5 = FindFreeCamera(), iVar6 = CursorX, pPVar5 == NULL &&
				(menuactive == 1)) && (CursorX == 5))))
		{
			iVar6 = 6;
		}

		CursorX = iVar6;

		if (((CursorX == 7) && (menuactive == 1)) && (gNoReplaySaveAllowed != 0))
		{
			CursorX = 8;
		}
	}
	else if (dir == 2)
	{
		CursorX = CursorX + -1;
		if (((CursorX == 7) && (menuactive == 1)) && (gNoReplaySaveAllowed != 0)) 
		{
			CursorX = 6;
		}

		if ((((ReplayParameterPtr->RecordingEnd <= CameraCnt) && (menuactive == 1)) && (CursorX == 6)) ||
			(((FindFreeCamera() == NULL && (menuactive == 1)) && (CursorX == 5))))
		{
			CursorX = 4;
		}
	}
	else if (dir == 3)
	{
		CursorY--;

		if ((((FirstCamera() != 0) && (menuactive == 2)) && (MenuOffset != 0)) && (CursorY == 5)) 
		{
			CursorY = dir;
		}
	}
	else if (dir == 4)
	{
		CursorY++;

		if (((FirstCamera() != 0) && (menuactive == 2)) && ((MenuOffset != 0 && (CursorY == 4))))
		{
			CursorY = 6;
		}
	}

	if ((debounce == 0) && (PlayMode == 3)) 
	{
		pauseflag = 1;
	}

	if (pauseflag == 0) 
	{
		if (PlayMode == 2) 
		{
			first_time = 1;
			pauseflag = 1;
			menuactive = 0;
			return;
		}
		first_time = 1;
		menuactive = 0;
		return;
	}

	if (first_time != 0)
	{
		if ((ReplayParameterPtr->RecordingEnd <= CameraCnt) && ((CursorX < 4 || (CursorX == 5))))
		{
			CursorX = 4;
		}
		menuactive = 1;
	}

	first_time = 0;
	ReplayContinue = 0;

	switch (menuactive) 
	{
		case 1:
			CursorY = 0;
			if (CameraCnt < ReplayParameterPtr->RecordingEnd)
			{
				if (CursorX < 0)
					CursorX = 8;

				if (8 < CursorX)
					CursorX = 0;
			}
			else 
			{
				if (CursorX < 4)
					CursorX = 4;

				if (8 < CursorX)
					CursorX = 4;

			}

			switch (CursorX)
			{
				case 0:
					if (dir != 5) 
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						return;
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
						return;
					}
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					return;
				case 1:
					if (dir != 5)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						return;
					}

					if (CameraCnt < ReplayParameterPtr->RecordingEnd)
					{
						first_time = 0;
						pauseflag = 0;
						CursorY = 0;
						PlayMode = 0;
						ReplayContinue = 1;
						AutoDirect = 1;
						return;
					}
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					return;
				case 2:
					if (dir != 5) 
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						return;
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
						return;
					}
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					return;
				case 3:
					if (ReplayParameterPtr->RecordingEnd <= CameraCnt)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						return;
					}

					if (dir == 5)
					{
						first_time = 0;
						pauseflag = 0;
						CursorY = 0;
						PlayMode = 2;
						ReplayContinue = 0;
						frame_advance_count = 10;
						AutoDirect = 0;
						return;
					}

					if ((padd & 0x40U) == 0) 
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						return;
					}
					if (frame_advance_count == 0)
					{
						first_time = 0;
						pauseflag = 0;
						CursorY = 0;
						PlayMode = 3;
						ReplayContinue = 1;
						return;
					}
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					frame_advance_count = frame_advance_count + -1;
					return;
				case 4:
					mode = GAMEMODE_DIRECTOR;
					if (dir != 5)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						return;
					}
					break;
				case 5:
					if (ReplayParameterPtr->RecordingEnd <= CameraCnt)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						return;
					}

					if (dir == 5) 
					{
						editing_existing_camera = 0;
						first_time = 0;
						MenuOffset = 0;
						menuactive = 2;
						CursorY = 1;
						ReplayContinue = 0;
						return;
					}

					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					return;
				case 6:
					if (dir == 5) 
					{
						editing_existing_camera = 1;
						first_time = 0;
						MenuOffset = 0x18;
						menuactive = 2;
						CursorY = 1;
						ReplayContinue = 0;
						return;
					}

					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					return;
				case 7:
					if (dir == 5) 
					{
						//SetDispMask(0); // [A]
						SpoolSYNC();
						CallMemoryCard(0x10, 1);
						return;
					}

					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					return;
				case 8:
					if (dir != 5)
					{
						first_time = 0;
						CursorY = 0;
						ReplayContinue = 0;
						return;
					}

					mode = GAMEMODE_QUIT;

					if (gLoadedReplay == 0)
					{
						NoPlayerControl = 0;
						EnablePause(gMissionCompletionState);
						NoPlayerControl = 1;
						PlayMode = 0;
						return;
					}
					break;
				default:
					first_time = 0;
					CursorY = 0;
					ReplayContinue = 0;
					return;
			}
			EndGame(mode);
			PlayMode = 0;
			return;
		case 2:
			CursorX = 5;
			switch (CursorY) 
			{
				case 0:
					menuactive = 1;
					if (MenuOffset != 0)
						CursorX = 6;

					if (LastChange == NULL) 
						setCamera(PlaybackCamera);
					else 
						setCamera(LastChange);

					break;
				case 1:
					if (dir != 5) break;
					menuactive = 3;
					cameraview = 2;
					goto LAB_0003d980;
				case 2:
					if (dir != 5) break;
					menuactive = 4;
					gCameraAngle = 0x800;
					CameraPos.vx = -0x2d;
					gCameraDistance = 0x640;
					gCameraMaxDistance = 0x640;
					cameraview = 0;
					CameraPos.vy = -0xdc;
					CameraPos.vz = -0x7d;
				LAB_0003d980:
					CursorX = 6;
					break;
				case 3:
					if (dir == 5) 
					{
						if (cameraview == 2) 
						{
							cameraview = 0;
							InitCamera((_PLAYER *)player);
						}

						if ((cameraview != 5) && (cameraview != 1))
						{
							cameraview = 1;
						}
						menuactive = 5;
						CursorX = CursorX + 1;
					}
					break;
				case 4:
					if (MenuOffset != 0) 
					{
						if ((LastChange->prev != -1) && (dir == 5)) 
						{
							if (EditMode == 0)
							{
								EditMode = 1;
							}
							else
							{
								bVar1 = LastChange->prev;
								pPVar5 = PlaybackCamera + bVar1;
								if (LastChange->FrameCnt == pPVar5->FrameCnt) 
								{
									bVar2 = pPVar5->prev;
									if (bVar2 != 0xff)
									{
										PlaybackCamera[bVar2].next = pPVar5->next;
										LastChange->prev = bVar2;
										PlaybackCamera[bVar1].FrameCnt = 100000;
									}
								}
								EditMode = 0;
							}
						}
						break;
					}

					if (dir != 5) 
						break;

					menuactive = 1;
					if (editing_existing_camera == 0) 
					{
						RecordCamera(CameraCnt);

						if (NoMoreCamerasErrorMessage() != 0)
							CursorX = 6;

						break;
					}
					goto LAB_0003db6c;
				case 5:
					if (dir == 5) 
					{
						CursorX = 6;
						DeleteCurrentCamera(CameraCnt);
						iVar6 = FirstCamera();
						if (iVar6 != 0) {
							CursorY = 6;
						}
					}
					break;
				case 6:
					if (dir != 5) break;
					menuactive = 1;
					CursorX = 6;
					if (editing_existing_camera == 0)
					{
						RecordCamera(CameraCnt);
						break;
					}
				LAB_0003db6c:
					menuactive = 1;
					EditCamera(CameraCnt);
			}

			if (MenuOffset == 0) 
			{
				if (4 < CursorY) 
				{
					CursorY = 4;
					return;
				}
				return;
			}

			if (6 < CursorY) 
			{
				CursorY = 6;
				return;
			}
			return;
		case 3:
			CursorY = 1;
			if (CursorX == 5) 
			{
				menuactive = 2;
			}
			else if ((CursorX == 6) && (dir == 5))
			{
				iVar6 = SelectCameraCar((int)player[0].cameraCarId);
				player[0].cameraCarId = (char)iVar6;
			}

			break;
		case 4:
			CursorY = 2;
			if (CursorX == 5) 
			{
				menuactive = 2;
			}
			else if ((CursorX == 6) && (dir == 5))
			{
				if (EditMode == 0)
				{
					EditMode = 2;
				}
				else
				{
					EditMode = 0;
				}
			}
			break;
		case 5:
			CursorY = 3;

			switch (CursorX) 
			{
				case 5:
					menuactive = 2;
					break;
				case 6:
					if (dir == 5) 
					{
						if (EditMode == 0)
						{
							EditMode = 3;
						}
						else 
						{
						LAB_0003dd5c:
							EditMode = 0;
						}
					}
					break;
				case 7:
					if (dir == 5)
					{
						tracking_car = 1;
					}
					break;
				case 8:
					if (dir == 5) 
					{
						tracking_car = 0;
						if (EditMode != 0) goto LAB_0003dd5c;
						EditMode = 4;
					}
					break;
				case 9:
					if (tracking_car != 0) 
					{
						if (dir == 5)
						{
							if (cameraview == 1) 
								cameraview = 5;
							else
								cameraview = 1;
						}
						break;
					}
					goto LAB_0003ddf8;
			}

			if (tracking_car == 0 || OK_To_Zoom() == 0) 
			{
			LAB_0003ddf8:
				if (7 < CursorX) 
				{
					CursorX = 8;
				}
			}
			else 
			{
				if (8 < CursorX)
				{
					CursorX = 9;
				}
			}

		default:
			goto switchD_0003d504_caseD_5;
	}

	if (6 < CursorX) 
	{
		CursorX = 6;
	}
switchD_0003d504_caseD_5:
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoAutoDirect()
 // line 1990, offset 0x0003de60
	/* begin block 1 */
		// Start line: 1992
		// Start offset: 0x0003DE60
		// Variables:
	// 		struct VECTOR pos; // stack offset -40

		/* begin block 1.1 */
			// Start line: 1998
			// Start offset: 0x0003DEFC
			// Variables:
		// 		int new_view; // $v1

			/* begin block 1.1.1 */
				// Start line: 2015
				// Start offset: 0x0003DF94
			/* end block 1.1.1 */
			// End offset: 0x0003DF9C
			// End Line: 2025

			/* begin block 1.1.2 */
				// Start line: 2048
				// Start offset: 0x0003E058
				// Variables:
			// 		int tmp; // $v0
			/* end block 1.1.2 */
			// End offset: 0x0003E0D0
			// End Line: 2057

			/* begin block 1.1.3 */
				// Start line: 2059
				// Start offset: 0x0003E0D0
				// Variables:
			// 		int tmp; // $v0
			/* end block 1.1.3 */
			// End offset: 0x0003E0F4
			// End Line: 2065
		/* end block 1.1 */
		// End offset: 0x0003E2C4
		// End Line: 2095
	/* end block 1 */
	// End offset: 0x0003E328
	// End Line: 2106

	/* begin block 2 */
		// Start line: 4340
	/* end block 2 */
	// End Line: 4341

	/* begin block 3 */
		// Start line: 4341
	/* end block 3 */
	// End Line: 4342

	/* begin block 4 */
		// Start line: 4342
	/* end block 4 */
	// End Line: 4343

/* WARNING: Unknown calling convention yet parameter storage is locked */

long* savemapinfo = NULL;
static int mapstuff = 0;
static int cammapht2 = 0;

// [D]
void DoAutoDirect(void)
{
	int height;
	int tmp;

	if (((((quick_replay != 0) || (AutoDirect != 0)) && (gStopPadReads == 0)) &&
		((tracking_car = 1, TimeToWay == way_distance / 2 + 0xf &&
		(PlayerWayRecordPtr->x != 0x7fff)))) && (PlayerWayRecordPtr->y != 0x7fff)) 
	{
		switch (rand() & 7)
		{
			case 0:
				cameraview = 0;
				gCameraAngle = rand() & 0xfff;
				CameraPos.vy = -((rand() & 0xff) + 100);
				gCameraDistance = (rand() & 0x7e7) + 1000;
				gCameraMaxDistance = gCameraDistance;
				break;
			case 1:
			case 2:
				cameraview = 1;
				break;
			case 3:
			case 4:
				cameraview = 1;
				break;
			case 5:
				cameraview = 2;
				player[0].cameraCarId = player[0].playerCarId;
				break;
			case 6:
			case 7:
				cameraview = 5;
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
			player[0].cameraPos.vy = cammapht2 + -100;

		MapHeight(&player[0].cameraPos);

		if (savemapinfo != NULL)
			mapstuff = *savemapinfo;


		if ((valid_region(PlayerWayRecordPtr->x << 10, PlayerWayRecordPtr->y << 10) == 0) ||
			((((cameraview != 2 && (cameraview != 0)) &&
				((savemapinfo != NULL && ((*savemapinfo & 0x3c000000U) == 0x3c000000)))) ||
				(CameraCollisionCheck() != 0))))
		{
			cameraview = (rand() & 2);

			if (cameraview == 0)
			{
				gCameraAngle = rand() & 0xfff;
				CameraPos.vy = -((rand() & 0xff) + 100);
				gCameraDistance = (rand() & 0x7e7) + 1000;
				gCameraMaxDistance = gCameraDistance;
			}

			player[0].cameraCarId = -1;

			if (player[0].playerType != 2)
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
			CameraPos.vy = -((rand() & 0xff) + 100);
			gCameraDistance = (rand() & 0x7e7) + 1000;
			gCameraMaxDistance = gCameraDistance;
		}

		PlayerWayRecordPtr->x = 0x7fff;
		PlayerWayRecordPtr->y = 0x7fff;
	}

	if (TimeToWay-- == 0)
	{
		PlayerWayRecordPtr++;
		TimeToWay = way_distance;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ SelectCameraCar(int current /*$t1*/)
 // line 2108, offset 0x0003e328
	/* begin block 1 */
		// Start line: 2109
		// Start offset: 0x0003E328
		// Variables:
	// 		int count; // $a2

		/* begin block 1.1 */
			// Start line: 2123
			// Start offset: 0x0003E3A0
			// Variables:
		// 		struct _EVENT *event; // $a0
		// 		struct _CAR_DATA *car; // $a3
		// 		struct XZPAIR pos; // stack offset -16

			/* begin block 1.1.1 */
				// Start line: 2168
				// Start offset: 0x0003E484
				// Variables:
			// 		int dist; // $v0
			// 		int dx; // $a1
			// 		int dz; // $a0
			/* end block 1.1.1 */
			// End offset: 0x0003E50C
			// End Line: 2180
		/* end block 1.1 */
		// End offset: 0x0003E50C
		// End Line: 2181
	/* end block 1 */
	// End offset: 0x0003E53C
	// End Line: 2184

	/* begin block 2 */
		// Start line: 4589
	/* end block 2 */
	// End Line: 4590

	/* begin block 3 */
		// Start line: 4592
	/* end block 3 */
	// End Line: 4593

// [D]
int SelectCameraCar(int current)
{
	int count;

	_EVENT* event;
	int dz;
	int dx;
	_CAR_DATA* car;
	XZPAIR pos;

	if (current < 0x14)
	{
		if (current < -1)
			current = 18 - current;

		count = current + 1;

		if (count != current) 
		{
			do {
				event = NULL;
				car = NULL;

				if (count < 20)
				{
					car = &car_data[count];

					if (car->controlType == 3)
					{
						pos.x = car->hd.where.t[0];
						pos.z = car->hd.where.t[2];
					}
					else 
					{
						if (car->controlType == 1)
						{
							if (player[1].playerCarId == car->id)
								return player[1].playerCarId;

							return player[0].playerCarId;
						}

						car = NULL;

						if (count == -1 && (player[0].playerType == 2))
							return -1;
					}
				}
				else 
				{
					event = events.track[count - 20];

					if (event == NULL) 
					{
						count = -1;

						if (player[0].playerType == 2) 
						{
							count = -2;
						}
					}
					else 
					{
						pos.x = event->position.vx;
						pos.z = event->position.vz;
					}
				}

				if (car != NULL || event != NULL)
				{
					dx = player[0].pos[0] - pos.x;

					if (dx < 0)
						dx = -dx;

					dz = player[0].pos[2] - pos.z;

					if (dx < 15000)
					{
						if (dz < 0)
							dz = -dz;

						if (dz < 15000 && (dx * dx + dz * dz < 225000000))
						{
							if (car != NULL) 
							{
								return car->id;
							}

							return 18 - count;
						}
					}
				}

				count++;
			} while (count != current);
		}

		printf("ERROR:_SelectCameraCar\n");

		count = player[0].playerCarId;
	}
	else
	{
		count = 0;
	}

	return count;
}



// decompiled code
// original method signature: 
// int /*$ra*/ InvalidCamera(int car_num /*$a2*/)
 // line 2186, offset 0x0003e53c
	/* begin block 1 */
		// Start line: 2187
		// Start offset: 0x0003E53C

		/* begin block 1.1 */
			// Start line: 2193
			// Start offset: 0x0003E568
			// Variables:
		// 		char invalidCamera; // $a3

			/* begin block 1.1.1 */
				// Start line: 2200
				// Start offset: 0x0003E5D0
				// Variables:
			// 		char numEventModels; // $a0
			// 		struct _EVENT *event; // $v1
			// 		struct XZPAIR pos; // stack offset -24

				/* begin block 1.1.1.1 */
					// Start line: 2208
					// Start offset: 0x0003E628
					// Variables:
				// 		int dist; // $v0
				// 		int dx; // $v1
				// 		int dz; // $a0
				/* end block 1.1.1.1 */
				// End offset: 0x0003E6C0
				// End Line: 2224
			/* end block 1.1.1 */
			// End offset: 0x0003E6C0
			// End Line: 2225
		/* end block 1.1 */
		// End offset: 0x0003E6F8
		// End Line: 2236
	/* end block 1 */
	// End offset: 0x0003E79C
	// End Line: 2260

	/* begin block 2 */
		// Start line: 4846
	/* end block 2 */
	// End Line: 4847

	/* begin block 3 */
		// Start line: 4849
	/* end block 3 */
	// End Line: 4850

	/* begin block 4 */
		// Start line: 4851
	/* end block 4 */
	// End Line: 4852

// [D]
int InvalidCamera(int car_num)
{
	bool bVar1;
	uint uVar2;
	ulong uVar3;
	int iVar4;
	int iVar5;
	uint uVar6;
	int iVar7;

	if (cameraview != 0)
	{
		if (cameraview != 2)
		{
			uVar3 = Long2DDistance(player[0].spoolXZ, &player[0].cameraPos);
			if (11000 < uVar3) 
			{
				player[0].cameraCarId = -1;

				if (player[0].playerType != 2)
					player[0].cameraCarId = player[0].playerCarId;

				CameraPos.vy = -300;
				cameraview = 0;
				return 1;
			}

			iVar4 = valid_region(player[0].cameraPos.vx, player[0].cameraPos.vz);

			if (iVar4 != 0)
				return 0;

			player[0].cameraCarId = -1;

			if (player[0].playerType != 2)
				player[0].cameraCarId = player[0].playerCarId;

			cameraview = 2;
			return 1;
		}

		bVar1 = false;

		if (-1 < car_num)
			bVar1 = car_data[car_num].controlType == 0;

		if (car_num == -1 && player[0].playerType != 2) 
			bVar1 = true;

		uVar6 = 0;

		if (car_num < -1)
		{
			if (*events.track != NULL)
			{
				uVar2 = 1;
				do {
					uVar6 = uVar2 & 0xff;
					uVar2 = uVar6 + 1;
				} while (events.track[uVar6] != NULL);
			}

			if (-2 - car_num < uVar6)
				bVar1 = true;

			iVar5 = player[0].pos[0] - (events.track[car_num * 0x3fffffff + -2]->position).vx;
			iVar4 = iVar5;

			if (iVar5 < 0)
				iVar4 = -iVar5;

			iVar7 = player[0].pos[2] - (events.track[car_num * 0x3fffffff + -2]->position).vz;

			if (iVar4 < 15000) 
			{
				iVar4 = iVar7;
				if (iVar7 < 0)
					iVar4 = -iVar7;
	
				if (iVar4 < 15000 && (iVar5 * iVar5 + iVar7 * iVar7 < 225000000)) 
					bVar1 = true;
			}
		}

		if (bVar1)
		{
			player[0].cameraCarId = -1;

			if (player[0].playerType != 2) 
				player[0].cameraCarId = player[0].playerCarId;

			CameraPos.vy = -300;
			return 1;
		}
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ NoMoreCamerasErrorMessage()
 // line 2263, offset 0x0003eaf0
	/* begin block 1 */
		// Start line: 2265
		// Start offset: 0x0003EAF0

		/* begin block 1.1 */
			// Start line: 2267
			// Start offset: 0x0003EB08
			// Variables:
		// 		int strobe; // $v0
		/* end block 1.1 */
		// End offset: 0x0003EB5C
		// End Line: 2272
	/* end block 1 */
	// End offset: 0x0003EB6C
	// End Line: 2275

	/* begin block 2 */
		// Start line: 6874
	/* end block 2 */
	// End Line: 6875

	/* begin block 3 */
		// Start line: 6875
	/* end block 3 */
	// End Line: 6876

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
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



// decompiled code
// original method signature: 
// int /*$ra*/ FirstCamera()
 // line 2279, offset 0x0003eb6c
	/* begin block 1 */
		// Start line: 2281
		// Start offset: 0x0003EB6C
	/* end block 1 */
	// End offset: 0x0003EB9C
	// End Line: 2287

	/* begin block 2 */
		// Start line: 6901
	/* end block 2 */
	// End Line: 6902

	/* begin block 3 */
		// Start line: 6906
	/* end block 3 */
	// End Line: 6907

	/* begin block 4 */
		// Start line: 6907
	/* end block 4 */
	// End Line: 6908

	/* begin block 5 */
		// Start line: 6909
	/* end block 5 */
	// End Line: 6910

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
int FirstCamera(void)
{
	if (LastChange && LastChange->prev != -1) 
		return 0;

	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ dist(struct VECTOR *pos1 /*$a0*/, struct VECTOR *pos2 /*$a1*/)
 // line 2289, offset 0x0003eb9c
	/* begin block 1 */
		// Start line: 2290
		// Start offset: 0x0003EB9C
		// Variables:
	// 		int dx; // $v0
	// 		int dz; // $a0
	/* end block 1 */
	// End offset: 0x0003EC0C
	// End Line: 2296

	/* begin block 2 */
		// Start line: 6923
	/* end block 2 */
	// End Line: 6924

	/* begin block 3 */
		// Start line: 6926
	/* end block 3 */
	// End Line: 6927

	/* begin block 4 */
		// Start line: 6928
	/* end block 4 */
	// End Line: 6929

// [D]
int dist(VECTOR *pos1, VECTOR *pos2)
{
	int dx;
	int dz;

	dx = (pos1->vx - pos2->vx) >> 4;
	dz = (pos1->vz - pos2->vz) >> 4;

	return SquareRoot0(dx * dx + dz * dz) << 4;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetCameraReturnedFromCutscene(int CameraCnt /*$s0*/)
 // line 2303, offset 0x0003ecc4
	/* begin block 1 */
		// Start line: 2304
		// Start offset: 0x0003ECC4
		// Variables:
	// 		struct PLAYBACKCAMERA *next; // $a1
	// 		int count; // $a2
	/* end block 1 */
	// End offset: 0x0003ED7C
	// End Line: 2331

	/* begin block 2 */
		// Start line: 6966
	/* end block 2 */
	// End Line: 6967

	/* begin block 3 */
		// Start line: 8545
	/* end block 3 */
	// End Line: 8546

	/* begin block 4 */
		// Start line: 8546
	/* end block 4 */
	// End Line: 8547

// [D]
void SetCameraReturnedFromCutscene(int CameraCnt)
{
	PLAYBACKCAMERA *next;
	int count;

	count = 0;
	next = PlaybackCamera;

	while ((NextChange = next, count < 60 &&
		((NextChange = PlaybackCamera + count, CameraCnt < NextChange->FrameCnt ||
		((NextChange->next != -2 && (next = PlaybackCamera + NextChange->next, next->FrameCnt <= CameraCnt)))))))
	{
		count++;
	}

	LastChange = NextChange;

	SetPlaybackCamera(NextChange);
	FindNextChange(CameraCnt + 1);
}





