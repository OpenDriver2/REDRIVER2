#include "THISDUST.H"
#include "DIRECTOR.H"

TEXTURE_DETAILS delcam; // address 0xC0EE0
TEXTURE_DETAILS incar; // address 0xBF950
TEXTURE_DETAILS lenschan; // address 0xC1DB0
TEXTURE_DETAILS lookcar; // address 0xC1CB0
TEXTURE_DETAILS movecam; // address 0xC1C18
TEXTURE_DETAILS movecampos; // address 0xC08C0
TEXTURE_DETAILS ok; // address 0xC1BD8
TEXTURE_DETAILS dir_pause; // address 0xBF970
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

REPLAY_ICON replay_icons[23] =
{
  { 20, 26, &dir_pause, "Pause", 20, 48 },
  { 20, 26, &playpause, "Resume", 20, 48 },
  { 44, 26, &autocam, "Auto director", 44, 48 },
  { 68, 26, &playcam, "Play camera", 68, 48 },
  { 92, 26, &frameadv, "Single frame", 92, 48 },
  { 116, 26, &restart, "Rewind", 116, 48 },
  { 140, 26, &addcam, "Add camera", 140, 48 },
  { 164, 26, &editcam, "Edit camera", 164, 48 },
  { 188, 26, &save2card, "Save replay", 188, 48 },
  { 212, 26, &ok, "OK", 212, 48 },
  { 140, 50, &incar, "Inside car", 164, 48 },
  { 140, 74, &chasecar, "Chase camera", 164, 72 },
  { 140, 98, &fixedcam, "Fixed camera", 164, 96 },
  { 140, 122, &ok, "Accept", 164, 120 },
  { 140, 122, &clock, "Move camera start", 164, 120 },
  { 140, 146, &delcam, "Delete camera", 164, 144 },
  { 140, 170, &ok, "Accept", 164, 168 },
  { 164, 50, &choosecar, "Choose target vehicle", 164, 72 },
  { 164, 74, &movecampos, "Move camera position", 164, 96 },
  { 164, 98, &movecampos, "Move camera position", 164, 120 },
  { 188, 98, &lookcar, "Look at target", 188, 120 },
  { 212, 98, &movecam, "Move camera", 212, 120 },
  { 236, 98, &lenschan, "Lens zoom", 236, 120 }
};

char menu0[] = { 0, 0xFF };

char menu1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xFF };

char menu2[] = { 0xA, 0xB, 0xC, 0xD, 0xFF };

char menu3[] = { 0x11, 0xFF };

char menu4[] = { 0x12, 0xFF };

char menu5[] = { 0x13, 0x14, 0x15, 0x16, 0xFF };

char menu6[] = { 0xA, 0xB, 0xC, 0xE, 0xF, 0x10, 0xFF };

int FastForward = 0;
int EditMode = 0;


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

void InitDirectorVariables(void)
{
	UNIMPLEMENTED();
	/*
	char *pcVar1;
	int iVar2;

	PlayMode = 0;
	CameraChanged = NoPlayerControl != 0;
	iVar2 = 0x17;
	pcVar1 = &CHAR____000cbe27;
	menuactive = 1;
	ClearCameras = 0;
	EditMode = 0;
	AutoDirect = 0;
	CursorX = 0;
	do {
		*pcVar1 = '\0';
		iVar2 = iVar2 + -1;
		pcVar1 = pcVar1 + -1;
	} while (-1 < iVar2);
	LastChange = (PLAYBACKCAMERA *)0x0;
	FastForwardCameraCnt = 0;
	return;*/
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

void DeleteCurrentCamera(int CameraCnt)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte bVar2;
	PLAYBACKCAMERA *Change;
	uint uVar3;

	bVar1 = LastChange->prev;
	uVar3 = (uint)bVar1;
	bVar2 = LastChange->next;
	if (bVar1 != 0xff) {
		PlaybackCamera[uVar3].next = bVar2;
		if (bVar2 != 0xfe) {
			PlaybackCamera[bVar2].prev = bVar1;
		}
		Change = PlaybackCamera + uVar3;
		LastChange->FrameCnt = 100000;
		setCamera(Change);
		LastChange = PlaybackCamera + uVar3;
	}
	return;*/
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

void setCamera(PLAYBACKCAMERA *Change)
{
	UNIMPLEMENTED();
	/*
	CameraPos.vy = (int)Change->CameraPosvy;
	camera_angle.vx = (Change->angle).vx;
	camera_angle.vy = (Change->angle).vy;
	camera_angle.vz = (Change->angle).vz;
	gCameraDistance = (int)Change->gCameraDistance;
	gCameraMaxDistance = (int)Change->gCameraMaxDistance;
	gCameraAngle = (int)Change->gCameraAngle;
	cameraview = Change->cameraview & 7;
	tracking_car = (char)(((uint)(byte)Change->cameraview & 8) >> 3);
	player.cameraPos.vx = (Change->position).vx;
	player.cameraPos.vy = (Change->position).vy;
	player.cameraPos.vz = (Change->position).vz;
	player.cameraCarId = *(char *)&(Change->angle).pad;
	return;
	*/
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

void EditCamera(int CameraCnt)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte bVar2;
	short sVar3;
	short sVar4;
	short sVar5;
	char cVar6;
	PLAYBACKCAMERA *pPVar7;
	int iVar8;
	PLAYBACKCAMERA *pPVar9;
	PLAYBACKCAMERA *pPVar10;
	long lVar11;
	long lVar12;
	int count;
	undefined4 uVar13;
	int iVar14;
	int iVar15;

	if (LastChange == (PLAYBACKCAMERA *)0x0) {
		LastChange = PlaybackCamera;
	}
	ThisChange = LastChange;
	LastChange->cameraview = cameraview & 7 | tracking_car << 3;
	pPVar9 = ThisChange;
	(ThisChange->position).vx = player.cameraPos.vx;
	(pPVar9->position).vy = player.cameraPos.vy;
	(pPVar9->position).vz = player.cameraPos.vz;
	(pPVar9->angle).vx = camera_angle.vx;
	(pPVar9->angle).vy = camera_angle.vy;
	sVar3 = (short)gCameraDistance;
	(pPVar9->angle).vz = camera_angle.vz;
	cVar6 = player.cameraCarId;
	sVar5 = (short)gCameraAngle;
	sVar4 = (short)gCameraMaxDistance;
	pPVar9->gCameraDistance = sVar3;
	pPVar9->gCameraMaxDistance = sVar4;
	pPVar9->gCameraAngle = sVar5;
	(pPVar9->angle).pad = (short)cVar6;
	pPVar9->CameraPosvy = (short)CameraPos.vy;
	iVar8 = 0;
	count = 0;
	do {
		pPVar9 = (PLAYBACKCAMERA *)(&(PlaybackCamera->position).vx + iVar8 + count);
		iVar15 = count + 1;
		if ((pPVar9 != ThisChange) && (pPVar9->FrameCnt == ThisChange->FrameCnt)) {
			bVar1 = pPVar9->prev;
			bVar2 = pPVar9->next;
			if (bVar1 == 0xff) {
				pPVar10 = (PLAYBACKCAMERA *)&ThisChange->cameraview;
				pPVar7 = ThisChange;
				do {
					lVar11 = (pPVar7->position).vy;
					lVar12 = (pPVar7->position).vz;
					uVar13 = *(undefined4 *)&pPVar7->angle;
					(pPVar9->position).vx = (pPVar7->position).vx;
					(pPVar9->position).vy = lVar11;
					(pPVar9->position).vz = lVar12;
					*(undefined4 *)&pPVar9->angle = uVar13;
					pPVar7 = (PLAYBACKCAMERA *)&(pPVar7->angle).vz;
					pPVar9 = (PLAYBACKCAMERA *)&(pPVar9->angle).vz;
				} while (pPVar7 != pPVar10);
				(pPVar9->position).vx = (pPVar7->position).vx;
				iVar14 = (iVar8 + count) * 4;
				(&PlaybackCamera->idx)[iVar14] = (char)count;
				(&PlaybackCamera->prev)[iVar14] = -1;
				if (ThisChange->next != 0xfe) {
					PlaybackCamera[(byte)ThisChange->next].prev = (char)count;
				}
				deleteCamera((uint)(byte)ThisChange->idx);
				ThisChange = (PLAYBACKCAMERA *)(&(PlaybackCamera->position).vx + iVar8 + count);
				LastChange = ThisChange;
			}
			else {
				PlaybackCamera[bVar1].next = bVar2;
				if (bVar2 != 0xfe) {
					PlaybackCamera[bVar2].prev = bVar1;
				}
				deleteCamera(count);
			}
		}
		iVar8 = iVar15 * 8;
		count = iVar15;
	} while (iVar15 < 0x3c);
	return;*/
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

void RecordCamera(int CameraCnt)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	PLAYBACKCAMERA *pPVar2;

	if (((((((LastChange == (PLAYBACKCAMERA *)0x0) ||
		((uint)(byte)LastChange->cameraview !=
		((uint)cameraview & 7 | (uint)(byte)tracking_car << 3))) ||
			((int)player.cameraCarId != (int)(LastChange->angle).pad)) ||
		((cameraview == 1 || (((uint)cameraview & 7) == 5)))) ||
		(((int)LastChange->gCameraDistance != gCameraDistance ||
		(((int)LastChange->gCameraMaxDistance != gCameraMaxDistance ||
			((int)LastChange->gCameraAngle != gCameraAngle)))))) ||
			((int)LastChange->CameraPosvy != CameraPos.vy)) &&
		(pPVar2 = FindFreeCamera(), pPVar2 != (PLAYBACKCAMERA *)0x0)) {
		if (CameraCnt == 0) {
			ThisChange = PlaybackCamera;
		}
		else {
			if ((ThisChange == (PLAYBACKCAMERA *)0x0) || (CameraCnt != ThisChange->FrameCnt)) {
				pPVar2->next = LastChange->next;
				pPVar2->prev = LastChange->idx;
				LastChange->next = pPVar2->idx;
				ThisChange = pPVar2;
				if (pPVar2->next != 0xfe) {
					PlaybackCamera[(byte)pPVar2->next].prev = pPVar2->idx;
				}
			}
		}
		ThisChange->cameraview = cameraview & 7 | tracking_car << 3;
		LastChange = ThisChange;
		(ThisChange->position).vx = player.cameraPos.vx;
		(LastChange->position).vy = player.cameraPos.vy;
		(LastChange->position).vz = player.cameraPos.vz;
		(LastChange->angle).vx = camera_angle.vx;
		(LastChange->angle).vy = camera_angle.vy;
		(LastChange->angle).vz = camera_angle.vz;
		cVar1 = player.cameraCarId;
		LastChange->gCameraDistance = (short)gCameraDistance;
		LastChange->FrameCnt = CameraCnt;
		LastChange->gCameraMaxDistance = (short)gCameraMaxDistance;
		LastChange->gCameraAngle = (short)gCameraAngle;
		(LastChange->angle).pad = (short)cVar1;
		LastChange->CameraPosvy = (short)CameraPos.vy;
	}
	FindNextChange(CameraCnt);
	return;
	*/
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

void FindNextChange(int CameraCnt)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	PLAYBACKCAMERA *pPVar2;
	int iVar3;
	PLAYBACKCAMERA *pPVar4;
	int iVar5;
	int iVar6;

	pPVar2 = NextChange;
	iVar5 = 0x186a1;
	bVar1 = false;
	iVar6 = 0x3b;
	NextChange = PlaybackCamera;
	pPVar4 = PlaybackCamera;
	do {
		iVar3 = pPVar4->FrameCnt;
		if ((CameraCnt <= iVar3) && (iVar3 < iVar5)) {
			bVar1 = true;
			iVar5 = iVar3;
			NextChange = pPVar4;
		}
		iVar6 = iVar6 + -1;
		pPVar4 = pPVar4 + 1;
	} while (-1 < iVar6);
	if (!bVar1) {
		NextChange = pPVar2;
		pPVar2->next = -2;
	}
	return;*/
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

int CheckCameraChange(int CameraCnt)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;

	if (JustReturnedFromCutscene != 0) {
		JustReturnedFromCutscene = 0;
		SetCameraReturnedFromCutscene(CameraCnt);
	}
	if (((CameraCnt != -1) && (DoAutoDirect(), gStopPadReads == 0)) &&
		(iVar1 = InvalidCamera((int)player.cameraCarId), iVar1 != 0)) {
		RecordCamera(CameraCnt);
		return 0;
	}
	if (NextChange->FrameCnt != CameraCnt) {
		if (CameraCnt < NextChange->FrameCnt) {
			IsMovingCamera(LastChange, NextChange, CameraCnt);
			return 0;
		}
		if (NextChange->next == -2) {
			return 0;
		}
	}
	SetPlaybackCamera(NextChange);
	iVar1 = InvalidCamera((int)player.cameraCarId);
	if (iVar1 == 0) {
		LastChange = NextChange;
		FindNextChange(CameraCnt + 1);
	}
	if ((PlayMode == 1) && (CameraCnt != FastForwardCameraCnt)) {
		SetFastForward = 0;
		FastForward = 0;
		pauseflag = PlayMode;
	}
	return 1;*/
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

void SetPlaybackCamera(PLAYBACKCAMERA *camera)
{
	UNIMPLEMENTED();
	/*
	CameraPos.vy = (int)camera->CameraPosvy;
	camera_angle.vx = (camera->angle).vx;
	camera_angle.vy = (camera->angle).vy;
	camera_angle.vz = (camera->angle).vz;
	gCameraDistance = (int)camera->gCameraDistance;
	gCameraMaxDistance = (int)camera->gCameraMaxDistance;
	gCameraAngle = (int)camera->gCameraAngle;
	cameraview = camera->cameraview & 7;
	tracking_car = (char)(((uint)(byte)camera->cameraview & 8) >> 3);
	CameraChanged = '\x01';
	player.cameraPos.vx = (camera->position).vx;
	player.cameraPos.vy = (camera->position).vy;
	player.cameraPos.vz = (camera->position).vz;
	player.cameraCarId = *(char *)&(camera->angle).pad;
	return;*/
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

int IsMovingCamera(PLAYBACKCAMERA *lastcam, PLAYBACKCAMERA *nextcam, int cameracnt)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	PLAYBACKCAMERA *pPVar2;
	int iVar3;
	int iVar4;
	byte bVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	long *plVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	long lVar15;
	long lVar16;
	long lVar17;
	uint uVar18;
	long local_38;
	long local_34;
	long local_30;
	short local_2c;
	short sStack42;
	short local_28;

	if (lastcam != (PLAYBACKCAMERA *)0x0) {
		if ((cameraview != 5) && (cameraview != 1)) {
			return 0;
		}
		bVar5 = nextcam->cameraview & 0x87;
		if ((bVar5 == 0x85) || (bVar5 == 0x81)) {
			cameracnt = cameracnt - lastcam->FrameCnt;
			iVar14 = nextcam->FrameCnt - lastcam->FrameCnt;
			uVar18 = (cameracnt * 0x800) / iVar14;
			if (iVar14 == 0) {
				trap(7);
			}
			iVar7 = (nextcam->position).vx;
			iVar6 = (nextcam->position).vy;
			iVar10 = ((int)rcossin_tbl[(uVar18 * 3 & 0xfff) * 2 + 1] +
				(int)rcossin_tbl[(uVar18 & 0xfff) * 2 + 1] * -9 >> 4) + 0x800;
			iVar3 = (lastcam->position).vx;
			iVar1 = (lastcam->position).vy;
			iVar8 = (nextcam->position).vz;
			iVar4 = (lastcam->position).vz;
			iVar11 = (int)(nextcam->angle).vx - (int)(lastcam->angle).vx;
			iVar12 = (int)(nextcam->angle).vy - (int)(lastcam->angle).vy;
			iVar13 = (int)(nextcam->angle).vz - (int)(lastcam->angle).vz;
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
			plVar9 = (long *)&local_38;
			pPVar2 = lastcam;
			do {
				lVar15 = (pPVar2->position).vy;
				lVar16 = (pPVar2->position).vz;
				lVar17 = *(long *)&pPVar2->angle;
				*plVar9 = (pPVar2->position).vx;
				plVar9[1] = lVar15;
				plVar9[2] = lVar16;
				plVar9[3] = lVar17;
				pPVar2 = (PLAYBACKCAMERA *)&(pPVar2->angle).vz;
				plVar9 = plVar9 + 4;
			} while (pPVar2 != (PLAYBACKCAMERA *)&lastcam->cameraview);
			*plVar9 = (pPVar2->position).vx;
			local_38 = (lastcam->position).vx + ((iVar7 - iVar3) * 0x40 * iVar10 + 0x20000 >> 0x12);
			local_34 = (lastcam->position).vy + ((iVar6 - iVar1) * 0x40 * iVar10 + 0x20000 >> 0x12);
			local_30 = (lastcam->position).vz + ((iVar8 - iVar4) * 0x40 * iVar10 + 0x20000 >> 0x12);
			if (iVar14 == 0) {
				trap(7);
			}
			local_2c = (lastcam->angle).vx + (short)(((iVar11 << 6) / iVar14) * cameracnt >> 6);
			if (iVar14 == 0) {
				trap(7);
			}
			sStack42 = (lastcam->angle).vy + (short)(((iVar12 << 6) / iVar14) * cameracnt >> 6);
			if (iVar14 == 0) {
				trap(7);
			}
			local_28 = (lastcam->angle).vz + (short)(((iVar13 << 6) / iVar14) * cameracnt >> 6);
			SetPlaybackCamera((PLAYBACKCAMERA *)&local_38);
			return 1;
		}
	}
	return 0;*/
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

void CameraBar(int CameraCnt)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	bool bVar2;
	DB *pDVar3;
	char cVar4;
	short sVar5;
	int iVar6;
	byte bVar7;
	long *plVar8;
	int iVar9;
	char cVar10;
	int iVar11;
	PLAYBACKCAMERA *pPVar12;
	short sVar13;
	int iVar14;
	undefined2 uVar15;
	uint uVar16;
	uint *puVar17;
	uint uVar18;
	uint uVar19;
	int iVar20;
	uint uVar21;
	uint uVar22;

	uVar18 = 0;
	uVar19 = 0;
	uVar22 = 0;
	iVar20 = 1;
	uVar21 = 0;
	bVar2 = true;
	puVar17 = (uint *)current->primptr;
	*(char *)((int)puVar17 + 3) = '\x03';
	*(char *)((int)puVar17 + 7) = '@';
	*(char *)(puVar17 + 1) = '\0';
	*(char *)((int)puVar17 + 5) = '\0';
	*(char *)((int)puVar17 + 6) = '\0';
	pDVar3 = current;
	*(undefined2 *)((int)puVar17 + 10) = 0xc;
	*(undefined2 *)(puVar17 + 2) = 0xa0;
	*(undefined2 *)(puVar17 + 3) = 0xa0;
	*(undefined2 *)((int)puVar17 + 0xe) = 0x16;
	*puVar17 = *puVar17 & 0xff000000 | *pDVar3->ot & 0xffffff;
	*pDVar3->ot = *pDVar3->ot & 0xff000000 | (uint)puVar17 & 0xffffff;
	pPVar12 = PlaybackCamera;
	pDVar3->primptr = pDVar3->primptr + 0x10;
	if (pPVar12->FrameCnt == 100000) {
		return;
	}
	iVar6 = 0;
	do {
		plVar8 = &(pPVar12->position).vx + iVar6 + uVar21;
		if (*(byte *)((int)plVar8 + 0x21) < 0x3c) {
			iVar14 = pPVar12[*(byte *)((int)plVar8 + 0x21)].FrameCnt;
		}
		else {
			iVar14 = 200000;
		}
		iVar9 = ReplayParameterPtr->RecordingEnd + 1;
		if (iVar9 < iVar14) {
			iVar20 = 2;
			iVar14 = iVar9;
		}
		uVar16 = plVar8[5] + 0xa0;
		_uVar15 = uVar16 - CameraCnt;
		uVar15 = (undefined2)_uVar15;
		iVar9 = (uVar16 - (uVar16 & 0x1f)) - CameraCnt;
		iVar14 = (iVar14 + 0xa0) - CameraCnt;
		sVar13 = (short)iVar14;
		if (((bVar2) && (0x1e < _uVar15)) && (_uVar15 < 0x122)) {
			puVar17 = (uint *)current->primptr;
			*(char *)((int)puVar17 + 3) = '\x03';
			*(char *)((int)puVar17 + 7) = '@';
			*(char *)(puVar17 + 1) = '\0';
			*(char *)((int)puVar17 + 5) = '\0';
			*(char *)((int)puVar17 + 6) = '\0';
			pDVar3 = current;
			*(undefined2 *)(puVar17 + 2) = uVar15;
			*(undefined2 *)((int)puVar17 + 10) = 0xf;
			*(undefined2 *)(puVar17 + 3) = uVar15;
			*(undefined2 *)((int)puVar17 + 0xe) = 0x13;
			*puVar17 = *puVar17 & 0xff000000 | *pDVar3->ot & 0xffffff;
			*pDVar3->ot = *pDVar3->ot & 0xff000000 | (uint)puVar17 & 0xffffff;
			pDVar3->primptr = pDVar3->primptr + 0x10;
		}
		iVar11 = 0;
		if (iVar20 != 0) {
			do {
				if (iVar14 - 0x1fU < 0x103) {
					puVar17 = (uint *)current->primptr;
					*(char *)((int)puVar17 + 3) = '\x03';
					*(char *)((int)puVar17 + 7) = '@';
					*(char *)(puVar17 + 1) = '\0';
					*(char *)((int)puVar17 + 5) = '\0';
					*(char *)((int)puVar17 + 6) = '\0';
					pDVar3 = current;
					sVar5 = sVar13 + (short)iVar11;
					*(short *)(puVar17 + 2) = sVar5;
					*(undefined2 *)((int)puVar17 + 10) = 0xf;
					*(short *)(puVar17 + 3) = sVar5;
					*(undefined2 *)((int)puVar17 + 0xe) = 0x13;
					*puVar17 = *puVar17 & 0xff000000 | *pDVar3->ot & 0xffffff;
					*pDVar3->ot = *pDVar3->ot & 0xff000000 | (uint)puVar17 & 0xffffff;
					pDVar3->primptr = pDVar3->primptr + 0x10;
				}
				iVar11 = iVar11 + 1;
			} while (iVar11 < iVar20);
		}
		while (iVar9 < iVar14) {
			if (iVar9 - 0x1fU < 0x103) {
				puVar17 = (uint *)current->primptr;
				*(char *)((int)puVar17 + 3) = '\x03';
				*(char *)((int)puVar17 + 7) = '@';
				*(char *)(puVar17 + 1) = '\0';
				*(char *)((int)puVar17 + 5) = '\0';
				*(char *)((int)puVar17 + 6) = '\0';
				pDVar3 = current;
				*(short *)(puVar17 + 2) = (short)iVar9;
				*(undefined2 *)((int)puVar17 + 10) = 0x11;
				*(short *)(puVar17 + 3) = (short)iVar9;
				*(undefined2 *)((int)puVar17 + 0xe) = 0x13;
				*puVar17 = *puVar17 & 0xff000000 | *pDVar3->ot & 0xffffff;
				*pDVar3->ot = *pDVar3->ot & 0xff000000 | (uint)puVar17 & 0xffffff;
				pDVar3->primptr = pDVar3->primptr + 0x10;
			}
			iVar9 = iVar9 + 0x20;
		}
		plVar8 = &(PlaybackCamera->position).vx + iVar6 + uVar21;
		bVar1 = *(byte *)(plVar8 + 8);
		bVar7 = bVar1 & 7;
		if (bVar7 == 1) {
			uVar18 = 0;
		LAB_0003c030:
			uVar19 = 0xff;
		LAB_0003c034:
			uVar22 = 0;
		}
		else {
			if (bVar7 < 2) {
				if ((bVar1 & 7) == 0) {
					uVar18 = 0xff;
					uVar19 = 0;
					goto LAB_0003c034;
				}
			}
			else {
				if (bVar7 == 2) {
					uVar18 = 0x46;
					if (*(short *)((int)plVar8 + 0x12) == 0) {
						uVar19 = 0x46;
						uVar22 = 0xff;
					}
					else {
						uVar19 = 0xff;
						uVar22 = 0xff;
					}
				}
				else {
					if (bVar7 == 5) {
						uVar18 = 0xff;
						goto LAB_0003c030;
					}
				}
			}
		}
		puVar17 = (uint *)current->primptr;
		*(char *)((int)puVar17 + 7) = '8';
		*(char *)((int)puVar17 + 3) = '\b';
		*(char *)(puVar17 + 3) = (char)(uVar18 >> 1);
		*(char *)((int)puVar17 + 0xe) = (char)(uVar22 >> 1);
		*(char *)((int)puVar17 + 0xd) = (char)(uVar19 >> 1);
		cVar4 = (char)(uVar19 >> 2);
		*(char *)((int)puVar17 + 0x15) = cVar4;
		*(char *)((int)puVar17 + 0x1d) = cVar4;
		*(char *)(puVar17 + 1) = (char)uVar18;
		*(char *)((int)puVar17 + 5) = (char)uVar19;
		*(char *)((int)puVar17 + 6) = (char)uVar22;
		cVar10 = (char)(uVar18 >> 2);
		*(char *)(puVar17 + 5) = cVar10;
		cVar4 = (char)(uVar22 >> 2);
		*(char *)((int)puVar17 + 0x16) = cVar4;
		*(char *)(puVar17 + 7) = cVar10;
		*(char *)((int)puVar17 + 0x1e) = cVar4;
		pDVar3 = current;
		bVar1 = (&PlaybackCamera->next)[(iVar6 + uVar21) * 4];
		uVar21 = (uint)bVar1;
		if (0x122 < _uVar15) {
			return;
		}
		if (0x122 < iVar14) {
			sVar13 = 0x122;
		}
		if (0x1d < iVar14) {
			if (_uVar15 < 0x1e) {
				uVar15 = 0x1e;
			}
			*(undefined2 *)(puVar17 + 2) = uVar15;
			*(undefined2 *)((int)puVar17 + 10) = 0xf;
			*(short *)(puVar17 + 4) = sVar13;
			*(undefined2 *)((int)puVar17 + 0x12) = 0xf;
			*(undefined2 *)(puVar17 + 6) = uVar15;
			*(undefined2 *)((int)puVar17 + 0x1a) = 0x14;
			*(short *)(puVar17 + 8) = sVar13;
			*(undefined2 *)((int)puVar17 + 0x22) = 0x14;
			*puVar17 = *puVar17 & 0xff000000 | *pDVar3->ot & 0xffffff;
			*pDVar3->ot = *pDVar3->ot & 0xff000000 | (uint)puVar17 & 0xffffff;
			bVar2 = false;
			pDVar3->primptr = pDVar3->primptr + 0x24;
		}
		if (PlaybackCamera[uVar21].FrameCnt == 100000) {
			return;
		}
		iVar6 = uVar21 << 3;
		pPVar12 = PlaybackCamera;
		if (0x3b < bVar1) {
			return;
		}
	} while (true);*/
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

PLAYBACKCAMERA * FindFreeCamera(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	PLAYBACKCAMERA *pPVar1;
	int iVar2;

	iVar2 = 0;
	pPVar1 = PlaybackCamera;
	do {
		iVar2 = iVar2 + 1;
		if (pPVar1->FrameCnt == 100000) {
			return pPVar1;
		}
		pPVar1 = pPVar1 + 1;
	} while (iVar2 < 0x3c);
	return (PLAYBACKCAMERA *)0x0;
	*/
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

void deleteCamera(int count)
{
	UNIMPLEMENTED();
	/*
	PLAYBACKCAMERA *pPVar1;
	PLAYBACKCAMERA *pPVar2;

	PlaybackCamera[count].idx = (char)count;
	pPVar2 = PlaybackCamera + count;
	pPVar2->prev = -1;
	pPVar1 = PlaybackCamera;
	pPVar2->FrameCnt = 100000;
	pPVar1[count].next = -2;
	return;*/
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

void DeleteAllCameras(void)
{
	UNIMPLEMENTED();
	/*
	int count;

	count = 0;
	do {
		deleteCamera(count);
		count = count + 1;
	} while (count < 0x3c);
	LastChange = (PLAYBACKCAMERA *)0x0;
	RecordCamera(0);
	CheckCameraChange(-1);
	LastChange->prev = -1;
	LastChange->next = -2;
	return;
	*/
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

void ShowIcons(char *menu, int selected, int x_offset)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	short sVar2;
	short sVar3;
	DB *pDVar4;
	int iVar5;
	char cVar6;
	uint uVar7;
	uint *puVar8;
	char *pcVar9;
	TEXTURE_DETAILS *pTVar10;
	int iVar11;

	iVar11 = 0;
	if (CameraCnt < ReplayParameterPtr->RecordingEnd) {
		CHAR____000cbe11 = '\0';
		CHAR_ARRAY_000cbe14[0] = '\0';
		CHAR____000cbe17 = '\0';
		CHAR____000cbe12 = '\0';
		iVar5 = NoMoreCamerasErrorMessage();
		if (iVar5 == 0) {
			CHAR____000cbe16 = '\0';
		}
		else {
			CHAR____000cbe16 = '\x01';
		}
	}
	else {
		ReleaseInGameCutscene();
		if (time_taken == 0) {
			time_taken = vblcounter;
		}
		SetFastForward = 0;
		FastForward = 0;
		CHAR____000cbe11 = '\x01';
		CHAR____000cbe13 = '\x01';
		CHAR_ARRAY_000cbe14[0] = '\x01';
		CHAR____000cbe16 = '\x01';
		CHAR____000cbe17 = '\x01';
		CHAR____000cbe12 = '\x01';
	}
	CHAR_ARRAY_000cbe18[0] = gNoReplaySaveAllowed != '\0';
	if ((tracking_car == '\0') || (iVar5 = OK_To_Zoom(), iVar5 == 0)) {
		CHAR____000cbe26 = '\x01';
	}
	else {
		CHAR____000cbe26 = '\0';
	}
	iVar5 = FirstCamera();
	CHAR____000cbe1e = iVar5 != 0;
	bVar1 = *menu;
	CHAR_ARRAY_000cbe1f[0] = CHAR____000cbe1e;
	while (bVar1 != 0xff) {
		uVar7 = (uint)(byte)*menu;
		pTVar10 = replay_icons[uVar7].texture;
		if (selected == iVar11) {
			SetTextColour(-0x80, -0x80, '@');
			PrintStringBoxed(replay_icons[uVar7].TextPtr, (int)replay_icons[uVar7].tx + x_offset + 1,
				(int)replay_icons[uVar7].ty);
		}
		puVar8 = (uint *)current->primptr;
		*(char *)((int)puVar8 + 3) = '\x04';
		*(char *)((int)puVar8 + 7) = 'd';
		if ((&GreyIcons)[(byte)*menu] == '\0') {
			if (selected == iVar11) {
				cVar6 = (char)(FlashCnt_42 & 0xf);
				if ((FlashCnt_42 & 0xf) < 8) {
					cVar6 = '\a' - cVar6;
				}
				else {
					cVar6 = cVar6 + -7;
				}
				if (EditMode == 0) {
					*(char *)(puVar8 + 1) = -1;
					*(char *)((int)puVar8 + 5) = -1;
					*(char *)((int)puVar8 + 6) = -1;
					FlashCnt_42 = 0;
				}
				else {
					cVar6 = cVar6 * '\x1c' + '\x1e';
					*(char *)(puVar8 + 1) = cVar6;
					*(char *)((int)puVar8 + 5) = cVar6;
					*(char *)((int)puVar8 + 6) = cVar6;
					FlashCnt_42 = FlashCnt_42 + 1;
				}
			}
			else {
				*(char *)(puVar8 + 1) = 'd';
				*(char *)((int)puVar8 + 5) = 'd';
				*(char *)((int)puVar8 + 6) = 'd';
			}
		}
		else {
			*(char *)((int)puVar8 + 7) = 'f';
			*(char *)(puVar8 + 1) = ' ';
			*(char *)((int)puVar8 + 5) = ' ';
			*(char *)((int)puVar8 + 6) = ' ';
		}
		sVar2 = replay_icons[uVar7].x;
		sVar3 = replay_icons[uVar7].y;
		*(undefined2 *)(puVar8 + 4) = 0x14;
		*(undefined2 *)((int)puVar8 + 0x12) = 0x14;
		*(short *)(puVar8 + 2) = sVar2 + (short)(x_offset + 1);
		*(short *)((int)puVar8 + 10) = sVar3;
		*(uchar *)(puVar8 + 3) = (pTVar10->coords).u0;
		*(uchar *)((int)puVar8 + 0xd) = (pTVar10->coords).v0;
		pDVar4 = current;
		*(ushort *)((int)puVar8 + 0xe) = pTVar10->clutid;
		*puVar8 = *puVar8 & 0xff000000 | *pDVar4->ot & 0xffffff;
		*pDVar4->ot = *pDVar4->ot & 0xff000000 | (uint)puVar8 & 0xffffff;
		pcVar9 = pDVar4->primptr;
		pDVar4->primptr = pcVar9 + 0x14;
		pcVar9[0x17] = '\a';
		pcVar9[0x1b] = '$';
		*(undefined2 *)(pcVar9 + 0x1c) = 0xffff;
		*(undefined2 *)(pcVar9 + 0x1e) = 0xffff;
		*(undefined2 *)(pcVar9 + 0x24) = 0xffff;
		*(undefined2 *)(pcVar9 + 0x26) = 0xffff;
		*(undefined2 *)(pcVar9 + 0x2c) = 0xffff;
		*(undefined2 *)(pcVar9 + 0x2e) = 0xffff;
		pDVar4 = current;
		*(ushort *)(pcVar9 + 0x2a) = pTVar10->tpageid;
		*(uint *)(pcVar9 + 0x14) = *(uint *)(pcVar9 + 0x14) & 0xff000000 | *pDVar4->ot & 0xffffff;
		*pDVar4->ot = *pDVar4->ot & 0xff000000 | (uint)(pcVar9 + 0x14) & 0xffffff;
		menu = (char *)((byte *)menu + 1);
		pDVar4->primptr = pDVar4->primptr + 0x20;
		bVar1 = *menu;
		iVar11 = iVar11 + 1;
	}
	return;*/
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

void ShowReplayOptions(void)
{
	UNIMPLEMENTED();
	/*
	if ((gInGameCutsceneActive == 0) && (quick_replay == 0)) {
		ShowReplayMenu();
		CameraBar(CameraCnt);
	}
	return;*/
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

void ShowReplayMenu(void)
{
	UNIMPLEMENTED();
	/*
	char *menu;
	uint uVar1;
	int selected;

	if (((menuactive < 1) && (PlayMode != 2)) && (PlayMode != 3)) {
		UnPauseSound();
		ShowIcons(menu0, 0, 0);
	}
	else {
		PauseSound();
		selected = CursorX;
		if (menuactive != 1) {
			selected = 99;
		}
		ShowIcons(menu1, selected, 0);
	}
	if (1 < menuactive) {
		if (MenuOffset == 0) {
			if (menuactive != 2) {
				ShowIcons(menu2, 99, 0);
				goto LAB_0003c6c4;
			}
			menu = menu2;
			selected = 0;
		}
		else {
			if (menuactive != 2) {
				ShowIcons(menu6, 99, MenuOffset);
				goto LAB_0003c6c4;
			}
			menu = menu6;
			selected = MenuOffset;
		}
		ShowIcons(menu, CursorY + -1, selected);
	}
LAB_0003c6c4:
	if (menuactive == 3) {
		ShowIcons(menu3, CursorX + -6, MenuOffset);
	}
	if (menuactive == 4) {
		ShowIcons(menu4, CursorX + -6, MenuOffset);
	}
	if (menuactive == 5) {
		ShowIcons(menu5, CursorX + -6, MenuOffset);
	}
	if ((AutoDirect != 0) && (pauseflag == 0)) {
		uVar1 = CameraCnt & 0x1f;
		if (0xf < uVar1) {
			uVar1 = 0x20 - uVar1;
		}
		SetTextColour((uchar)(uVar1 << 3), '\0', '\0');
		PrintString(s_Regia_automatica_0001077c, 100, 0x1e);
	}
	return;
	*/
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

void ControlReplay(void)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte bVar2;
	int iVar3;
	PLAYBACKCAMERA *pPVar4;
	GAMEMODE mode;
	int iVar5;
	uint dir;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	ROUTE_DATA local_60;
	long local_58;
	long local_54;
	long local_50;
	long local_48;
	long local_40;
	VECTOR local_38;
	ROUTE_DATA local_28;

	dir = 0;
	if (gInGameCutsceneActive != 0) {
		return;
	}
	if ((quick_replay != 0) || (AttractMode != 0)) {
		if (((padd != 0) || (ReplayParameterPtr->RecordingEnd <= CameraCnt)) && (2 < CameraCnt)) {
			ReleaseInGameCutscene();
			if (AttractMode == 0) {
				EnablePause(gMissionCompletionState);
			}
			else {
				EndGame(GAMEMODE_QUIT);
			}
			time_taken = vblcounter;
			return;
		}
		pauseflag = 0;
		return;
	}
	if ((((int)padd & 0x8000U) != 0) && (DAT_000aa414 == 0)) {
		dir = 2;
		DAT_000aa414 = 1;
	}
	if (((padd & 0x2000U) != 0) && (DAT_000aa414 == 0)) {
		dir = 1;
		DAT_000aa414 = 1;
	}
	if (((padd & 0x1000U) != 0) && (DAT_000aa414 == 0)) {
		dir = 3;
		DAT_000aa414 = 1;
	}
	if (((padd & 0x4000U) != 0) && (DAT_000aa414 == 0)) {
		dir = 4;
		DAT_000aa414 = 1;
	}
	if (((padd & 0x40U) != 0) && (DAT_000aa414 == 0)) {
		if (menuactive == 0) {
			pauseflag = 1;
		}
		else {
			dir = 5;
		}
		FastForward = 0;
		SetFastForward = 0;
		DAT_000aa414 = 1;
	}
	if ((((int)padd & 0x8000U) == 0) && ((padd & 0x7040U) == 0)) {
		DAT_000aa414 = 0;
	}
	if ((EditMode != 0) && (dir != 5)) {
		iVar8 = 1;
		if ((padd & 8U) != 0) {
			iVar8 = 8;
		}
		if (EditMode == 2) {
			if (((padd & 0x1000U) != 0) && (1000 < gCameraDistance)) {
				gCameraDistance = gCameraDistance + iVar8 * -0x10;
				gCameraMaxDistance = gCameraMaxDistance + iVar8 * -0x10;
			}
			if (((padd & 0x4000U) != 0) && (gCameraDistance < 4000)) {
				gCameraDistance = gCameraDistance + iVar8 * 0x10;
				gCameraMaxDistance = gCameraMaxDistance + iVar8 * 0x10;
			}
			if (((int)padd & 0x8000U) != 0) {
				gCameraAngle = gCameraAngle + iVar8 * 0x10;
			}
			if ((padd & 0x2000U) != 0) {
				gCameraAngle = gCameraAngle + iVar8 * -0x10;
			}
			if (((padd & 4U) != 0) && (-0x348 < CameraPos.vy)) {
				CameraPos.vy = CameraPos.vy + iVar8 * -0x10;
			}
			if (((padd & 1U) != 0) && (CameraPos.vy < -0x38)) {
				CameraPos.vy = CameraPos.vy + iVar8 * 0x10;
			}
			iVar8 = MapHeight(&player.cameraPos);
			ROADS_GetRouteData(player.cameraPos.vx, player.cameraPos.vz, &local_60);
			if ((modelpointers1536[local_60.type]->flags2 & 0x100) != 0) {
				iVar8 = -0x1c2 - iVar8;
				player.cameraPos.vy = CameraPos.vy - player.pos[1];
				if (CameraPos.vy - player.pos[1] < iVar8) {
					CameraPos.vy = iVar8 + player.pos[1];
					player.cameraPos.vy = iVar8;
				}
			}
		LAB_0003d1c4:
			dir = 0;
		}
		else {
			if (EditMode < 3) {
				dir = 0;
				if (EditMode == 1) {
					if (((padd & 0x2000U) != 0) && (LastChange->FrameCnt < CameraCnt)) {
						LastChange->FrameCnt = LastChange->FrameCnt + 1;
					}
					dir = 0;
					if ((((int)padd & 0x8000U) != 0) &&
						(PlaybackCamera[(byte)LastChange->prev].FrameCnt < LastChange->FrameCnt)) {
						LastChange->FrameCnt = LastChange->FrameCnt + -1;
					}
				}
			}
			else {
				if (EditMode == 3) {
					iVar9 = 0;
					iVar3 = 0;
					iVar5 = (int)player.cameraCarId;
					if (iVar5 < 0) {
						if (iVar5 == -1) {
							local_48 = player.pos[0];
							local_40 = player.pos[2];
						}
						else {
							local_48 = (events.track[iVar5 * 0x3fffffff + -2]->position).vx;
							local_40 = (events.track[iVar5 * 0x3fffffff + -2]->position).vz;
						}
					}
					else {
						local_48 = car_data[iVar5].hd.where.t[0];
						local_40 = car_data[iVar5].hd.where.t[2];
					}
					iVar7 = local_48 - player.cameraPos.vx;
					iVar6 = local_40 - player.cameraPos.vz;
					local_58 = player.cameraPos.vx;
					local_50 = player.cameraPos.vz;
					local_54 = player.cameraPos.vy;
					iVar5 = SquareRoot0(iVar7 * iVar7 + iVar6 * iVar6);
					if (tracking_car == '\0') {
						dir = SEXT24(camera_angle.vy);
					}
					else {
						dir = ratan2(iVar6, iVar7);
					}
					if (((padd & 0x1000U) != 0) && ((tracking_car == '\0' || (500 < iVar5)))) {
						iVar9 = iVar8 * -0x10;
					}
					if ((padd & 0x4000U) != 0) {
						iVar9 = iVar8 << 4;
					}
					if (((padd & 0x8000U) != 0) && ((tracking_car == '\0' || (500 < iVar5)))) {
						iVar3 = iVar8 * -0x10;
					}
					if ((padd & 0x2000U) != 0) {
						iVar3 = iVar8 << 4;
					}
					iVar5 = iVar9;
					if (tracking_car == '\0') {
						iVar5 = -iVar3;
						iVar3 = iVar9;
					}
					player.cameraPos.vx =
						(player.cameraPos.vx + (iVar3 * rcossin_tbl[(dir & 0xfff) * 2] >> 0xc)) -
						(iVar5 * rcossin_tbl[(dir & 0xfff) * 2 + 1] >> 0xc);
					player.cameraPos.vz =
						(player.cameraPos.vz - (iVar3 * rcossin_tbl[(dir & 0xfff) * 2 + 1] >> 0xc)) -
						(iVar5 * rcossin_tbl[(dir & 0xfff) * 2] >> 0xc);
					iVar3 = dist(player.spoolXZ, &player.cameraPos);
					if (iVar3 < 0x4801) {
						local_38.vx = player.cameraPos.vx;
						local_38.vy = -player.cameraPos.vy;
						local_38.vz = player.cameraPos.vz;
						iVar3 = QuickBuildingCollisionCheck(&local_38, dir, 10, 10, 10);
						if (iVar3 != 0) goto LAB_0003cf74;
					}
					else {
						player.cameraPos.vy = local_54;
					LAB_0003cf74:
						player.cameraPos.vx = local_58;
						player.cameraPos.vz = local_50;
					}
					iVar3 = MapHeight(&player.cameraPos);
					iVar3 = -iVar3;
					if ((padd & 4U) != 0) {
						player.cameraPos.vy = player.cameraPos.vy + iVar8 * -0x10;
					}
					if ((padd & 1U) != 0) {
						player.cameraPos.vy = player.cameraPos.vy + iVar8 * 0x10;
					}
					if (iVar3 - MIN_TRIPOD_CAMERA_HEIGHT < player.cameraPos.vy) {
						player.cameraPos.vy = iVar3 - MIN_TRIPOD_CAMERA_HEIGHT;
					}
					if (player.cameraPos.vy < iVar3 + -0x41a) {
						player.cameraPos.vy = iVar3 + -0x41a;
					}
					ROADS_GetRouteData(player.cameraPos.vx, player.cameraPos.vz, &local_28);
					if (((modelpointers1536[local_28.type]->flags2 & 0x100) != 0) &&
						(player.cameraPos.vy < iVar3 + -0x1c2)) {
						player.cameraPos.vy = iVar3 + -0x1c2;
					}
					dir = 0;
					if ((cameraview == 1) && (iVar8 = OK_To_Zoom(), iVar8 == 0)) {
						cameraview = 5;
					}
				}
				else {
					dir = 0;
					if (EditMode == 4) {
						if (((padd & 0x1000U) != 0) &&
							(iVar3 = (uint)(ushort)camera_angle.vx + iVar8 * 4, camera_angle.vx = (short)iVar3,
							(iVar3 - 300U & 0xffff) < 0x6d5)) {
							camera_angle.vx = 300;
						}
						if (((padd & 0x4000U) != 0) &&
							(iVar3 = (uint)(ushort)camera_angle.vx + iVar8 * -4, camera_angle.vx = (short)iVar3,
							(iVar3 - 0x800U & 0xffff) < 0x73d)) {
							camera_angle.vx = 0xf3c;
						}
						if (((int)padd & 0x8000U) != 0) {
							camera_angle.vy = camera_angle.vy + (short)iVar8 * 4;
						}
						if ((padd & 0x2000U) != 0) {
							camera_angle.vy = camera_angle.vy + (short)iVar8 * -4;
						}
						camera_angle.vx = camera_angle.vx & 0xfff;
						camera_angle.vy = camera_angle.vy & 0xfff;
						camera_angle.vz = camera_angle.vz & 0xfff;
						goto LAB_0003d1c4;
					}
				}
			}
		}
	}
	if (dir == 2) {
		CursorX = CursorX + -1;
		if (((CursorX == 7) && (menuactive == 1)) && (gNoReplaySaveAllowed != '\0')) {
			CursorX = 6;
		}
		if ((((ReplayParameterPtr->RecordingEnd <= CameraCnt) && (menuactive == 1)) && (CursorX == 6))
			|| (((pPVar4 = FindFreeCamera(), pPVar4 == (PLAYBACKCAMERA *)0x0 && (menuactive == 1)) &&
			(CursorX == 5)))) {
			CursorX = 4;
		}
	}
	else {
		if (dir < 3) {
			if (dir == 1) {
				CursorX = CursorX + 1;
				if ((((CameraCnt < ReplayParameterPtr->RecordingEnd) || (menuactive != 1)) ||
					(iVar8 = 7, CursorX != 5)) &&
					(((pPVar4 = FindFreeCamera(), iVar8 = CursorX, pPVar4 == (PLAYBACKCAMERA *)0x0 &&
					(menuactive == 1)) && (CursorX == 5)))) {
					iVar8 = 6;
				}
				CursorX = iVar8;
				if (((CursorX == 7) && (menuactive == 1)) && (gNoReplaySaveAllowed != '\0')) {
					CursorX = 8;
				}
			}
		}
		else {
			if (dir == 3) {
				CursorY = CursorY + -1;
				iVar8 = FirstCamera();
				if ((((iVar8 != 0) && (menuactive == 2)) && (MenuOffset != 0)) && (CursorY == 5)) {
					CursorY = dir;
				}
			}
			else {
				if (dir == 4) {
					CursorY = CursorY + 1;
					iVar8 = FirstCamera();
					if (((iVar8 != 0) && (menuactive == 2)) && ((MenuOffset != 0 && (CursorY == 4)))) {
						CursorY = 6;
					}
				}
			}
		}
	}
	if ((DAT_000aa414 == 0) && (PlayMode == 3)) {
		pauseflag = 1;
	}
	if (pauseflag == 0) {
		if (PlayMode == 2) {
			DAT_000aa418 = 1;
			pauseflag = 1;
			menuactive = 0;
			return;
		}
		DAT_000aa418 = 1;
		menuactive = 0;
		return;
	}
	if (DAT_000aa418 != 0) {
		if ((ReplayParameterPtr->RecordingEnd <= CameraCnt) && ((CursorX < 4 || (CursorX == 5)))) {
			CursorX = 4;
		}
		menuactive = 1;
	}
	DAT_000aa418 = 0;
	ReplayContinue = 0;
	switch (menuactive) {
	case 1:
		CursorY = 0;
		if (CameraCnt < ReplayParameterPtr->RecordingEnd) {
			if (CursorX < 0) {
				CursorX = 8;
			}
			if (8 < CursorX) {
				CursorX = 0;
			}
		}
		else {
			if (CursorX < 4) {
				CursorX = 4;
			}
			if (8 < CursorX) {
				CursorX = 4;
			}
		}
		switch (CursorX) {
		case 0:
			if (dir != 5) {
				DAT_000aa418 = 0;
				CursorY = 0;
				ReplayContinue = 0;
				return;
			}
			if (CameraCnt < ReplayParameterPtr->RecordingEnd) {
				DAT_000aa418 = 0;
				pauseflag = 0;
				CursorY = 0;
				PlayMode = 0;
				ReplayContinue = 1;
				AutoDirect = 0;
				vblcounter = 0;
				return;
			}
			DAT_000aa418 = 0;
			CursorY = 0;
			ReplayContinue = 0;
			return;
		case 1:
			if (dir != 5) {
				DAT_000aa418 = 0;
				CursorY = 0;
				ReplayContinue = 0;
				return;
			}
			if (CameraCnt < ReplayParameterPtr->RecordingEnd) {
				DAT_000aa418 = 0;
				pauseflag = 0;
				CursorY = 0;
				PlayMode = 0;
				ReplayContinue = 1;
				AutoDirect = 1;
				return;
			}
			DAT_000aa418 = 0;
			CursorY = 0;
			ReplayContinue = 0;
			return;
		case 2:
			if (dir != 5) {
				DAT_000aa418 = 0;
				CursorY = 0;
				ReplayContinue = 0;
				return;
			}
			if (CameraCnt < ReplayParameterPtr->RecordingEnd) {
				FastForward = 1;
				FastForwardCameraCnt = CameraCnt;
				DAT_000aa418 = 0;
				pauseflag = 0;
				CursorY = 0;
				PlayMode = 1;
				ReplayContinue = 1;
				AutoDirect = 0;
				return;
			}
			DAT_000aa418 = 0;
			CursorY = 0;
			ReplayContinue = 0;
			return;
		case 3:
			if (ReplayParameterPtr->RecordingEnd <= CameraCnt) {
				DAT_000aa418 = 0;
				CursorY = 0;
				ReplayContinue = 0;
				return;
			}
			if (dir == 5) {
				DAT_000aa418 = 0;
				pauseflag = 0;
				CursorY = 0;
				PlayMode = 2;
				ReplayContinue = 0;
				frame_advance_count = 10;
				AutoDirect = 0;
				return;
			}
			if ((padd & 0x40U) == 0) {
				DAT_000aa418 = 0;
				CursorY = 0;
				ReplayContinue = 0;
				return;
			}
			if (frame_advance_count == 0) {
				DAT_000aa418 = 0;
				pauseflag = 0;
				CursorY = 0;
				PlayMode = 3;
				ReplayContinue = 1;
				return;
			}
			DAT_000aa418 = 0;
			CursorY = 0;
			ReplayContinue = 0;
			frame_advance_count = frame_advance_count + -1;
			return;
		case 4:
			mode = GAMEMODE_DIRECTOR;
			if (dir != 5) {
				DAT_000aa418 = 0;
				CursorY = 0;
				ReplayContinue = 0;
				return;
			}
			break;
		case 5:
			if (ReplayParameterPtr->RecordingEnd <= CameraCnt) {
				DAT_000aa418 = 0;
				CursorY = 0;
				ReplayContinue = 0;
				return;
			}
			if (dir == 5) {
				editing_existing_camera = 0;
				DAT_000aa418 = 0;
				MenuOffset = 0;
				menuactive = 2;
				CursorY = 1;
				ReplayContinue = 0;
				return;
			}
			DAT_000aa418 = 0;
			CursorY = 0;
			ReplayContinue = 0;
			return;
		case 6:
			if (dir == 5) {
				editing_existing_camera = 1;
				DAT_000aa418 = 0;
				MenuOffset = 0x18;
				menuactive = 2;
				CursorY = 1;
				ReplayContinue = 0;
				return;
			}
			DAT_000aa418 = 0;
			CursorY = 0;
			ReplayContinue = 0;
			return;
		case 7:
			if (dir == 5) {
				SetDispMask(0);
				SpoolSYNC();
				CallMemoryCard(0x10, 1);
				return;
			}
			DAT_000aa418 = 0;
			CursorY = 0;
			ReplayContinue = 0;
			return;
		case 8:
			if (dir != 5) {
				DAT_000aa418 = 0;
				CursorY = 0;
				ReplayContinue = 0;
				return;
			}
			mode = GAMEMODE_QUIT;
			if (gLoadedReplay == 0) {
				NoPlayerControl = 0;
				EnablePause(gMissionCompletionState);
				NoPlayerControl = 1;
				PlayMode = 0;
				return;
			}
			break;
		default:
			DAT_000aa418 = 0;
			CursorY = 0;
			ReplayContinue = 0;
			return;
		}
		EndGame(mode);
		PlayMode = 0;
		return;
	case 2:
		CursorX = 5;
		switch (CursorY) {
		case 0:
			menuactive = 1;
			if (MenuOffset != 0) {
				CursorX = 6;
			}
			if (LastChange == (PLAYBACKCAMERA *)0x0) {
				setCamera(PlaybackCamera);
			}
			else {
				setCamera(LastChange);
			}
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
			if (dir == 5) {
				if (cameraview == 2) {
					cameraview = 0;
					InitCamera(&player);
				}
				if ((cameraview != 5) && (cameraview != 1)) {
					cameraview = 1;
				}
				menuactive = 5;
				CursorX = CursorX + 1;
			}
			break;
		case 4:
			if (MenuOffset != 0) {
				if ((LastChange->prev != -1) && (dir == 5)) {
					if (EditMode == 0) {
						EditMode = 1;
					}
					else {
						bVar1 = LastChange->prev;
						pPVar4 = PlaybackCamera + bVar1;
						if (LastChange->FrameCnt == pPVar4->FrameCnt) {
							bVar2 = pPVar4->prev;
							if (bVar2 != 0xff) {
								PlaybackCamera[bVar2].next = pPVar4->next;
								LastChange->prev = bVar2;
								PlaybackCamera[bVar1].FrameCnt = 100000;
							}
						}
						EditMode = 0;
					}
				}
				break;
			}
			if (dir != 5) break;
			menuactive = 1;
			if (editing_existing_camera == 0) {
				RecordCamera(CameraCnt);
				iVar8 = NoMoreCamerasErrorMessage();
				if (iVar8 != 0) {
					CursorX = 6;
				}
				break;
			}
			goto LAB_0003db6c;
		case 5:
			if (dir == 5) {
				CursorX = 6;
				DeleteCurrentCamera(CameraCnt);
				iVar8 = FirstCamera();
				if (iVar8 != 0) {
					CursorY = 6;
				}
			}
			break;
		case 6:
			if (dir != 5) break;
			menuactive = 1;
			CursorX = 6;
			if (editing_existing_camera == 0) {
				RecordCamera(CameraCnt);
				break;
			}
		LAB_0003db6c:
			menuactive = 1;
			EditCamera(CameraCnt);
		}
		if (MenuOffset == 0) {
			if (4 < CursorY) {
				CursorY = 4;
				return;
			}
			return;
		}
		if (6 < CursorY) {
			CursorY = 6;
			return;
		}
		return;
	case 3:
		CursorY = 1;
		if (CursorX == 5) {
			menuactive = 2;
		}
		else {
			if ((CursorX == 6) && (dir == 5)) {
				iVar8 = SelectCameraCar((int)player.cameraCarId);
				player.cameraCarId = (char)iVar8;
			}
		}
		break;
	case 4:
		CursorY = 2;
		if (CursorX == 5) {
			menuactive = 2;
		}
		else {
			if ((CursorX == 6) && (dir == 5)) {
				if (EditMode == 0) {
					EditMode = 2;
				}
				else {
					EditMode = 0;
				}
			}
		}
		break;
	case 5:
		CursorY = 3;
		switch (CursorX) {
		case 5:
			menuactive = 2;
			break;
		case 6:
			if (dir == 5) {
				if (EditMode == 0) {
					EditMode = 3;
				}
				else {
				LAB_0003dd5c:
					EditMode = 0;
				}
			}
			break;
		case 7:
			if (dir == 5) {
				tracking_car = '\x01';
			}
			break;
		case 8:
			if (dir == 5) {
				tracking_car = '\0';
				if (EditMode != 0) goto LAB_0003dd5c;
				EditMode = 4;
			}
			break;
		case 9:
			if (tracking_car != '\0') {
				if (dir == 5) {
					if (cameraview == 1) {
						cameraview = 5;
					}
					else {
						cameraview = 1;
					}
				}
				break;
			}
			goto LAB_0003ddf8;
		}
		if ((tracking_car == '\0') || (iVar8 = OK_To_Zoom(), iVar8 == 0)) {
		LAB_0003ddf8:
			if (7 < CursorX) {
				CursorX = 8;
			}
		}
		else {
			if (8 < CursorX) {
				CursorX = 9;
			}
		}
	default:
		goto switchD_0003d504_caseD_5;
	}
	if (6 < CursorX) {
		CursorX = 6;
	}
switchD_0003d504_caseD_5:
	return;*/
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

void DoAutoDirect(void)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	SXYPAIR *pSVar2;
	uint uVar3;
	int iVar4;

	if (((((quick_replay != 0) || (AutoDirect != 0)) && (gStopPadReads == 0)) &&
		((tracking_car = '\x01', TimeToWay == way_distance / 2 + 0xf &&
		(PlayerWayRecordPtr->x != 0x7fff)))) && (PlayerWayRecordPtr->y != 0x7fff)) {
		uVar3 = rand();
		switch (uVar3 & 7) {
		case 0:
			cameraview = 0;
			uVar3 = rand();
			gCameraAngle = uVar3 & 0xfff;
			uVar3 = rand();
			CameraPos.vy = -((uVar3 & 0xff) + 100);
			uVar3 = rand();
			gCameraDistance = (uVar3 & 0x7e7) + 1000;
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
			player.cameraCarId = player.playerCarId;
			break;
		case 6:
		case 7:
			cameraview = 5;
		}
		if (ReplayParameterPtr->RecordingEnd < CameraCnt + way_distance) {
			cameraview = 0;
			player.cameraCarId = -1;
			if (player.playerType != '\x02') {
				player.cameraCarId = player.playerCarId;
			}
		}
		else {
			player.cameraPos.vx = (int)PlayerWayRecordPtr->x << 10;
			player.cameraPos.vz = (int)PlayerWayRecordPtr->y << 10;
		}
		iVar4 = MapHeight(&player.cameraPos);
		uVar3 = rand();
		player.cameraPos.vy = (-0x46 - iVar4) - (uVar3 & 0x3ff);
		iVar4 = MapHeight((VECTOR *)car_data[player.cameraCarId].hd.where.t);
		if (-iVar4 < player.cameraPos.vy) {
			player.cameraPos.vy = -iVar4 + -100;
		}
		cammapht2 = MapHeight(&player.cameraPos);
		cammapht2 = -cammapht2;
		if (cammapht2 < player.cameraPos.vy) {
			player.cameraPos.vy = cammapht2 + -100;
		}
		MapHeight(&player.cameraPos);
		if (savemapinfo != (long *)0x0) {
			mapstuff = *savemapinfo;
		}
		iVar4 = valid_region((int)PlayerWayRecordPtr->x << 10, (int)PlayerWayRecordPtr->y << 10);
		test555 = ZEXT14(iVar4 == 0);
		if ((iVar4 == 0) ||
			((((cameraview != 2 && (cameraview != 0)) &&
			((savemapinfo != (long *)0x0 && ((*savemapinfo & 0x3c000000U) == 0x3c000000)))) ||
				(test42 = CameraCollisionCheck(), test42 != 0)))) {
			uVar3 = rand();
			cameraview = (byte)(uVar3 & 2);
			if ((uVar3 & 2) == 0) {
				uVar3 = rand();
				gCameraAngle = uVar3 & 0xfff;
				uVar3 = rand();
				CameraPos.vy = -((uVar3 & 0xff) + 100);
				uVar3 = rand();
				gCameraDistance = (uVar3 & 0x7e7) + 1000;
				gCameraMaxDistance = gCameraDistance;
			}
			player.cameraCarId = -1;
			if (player.playerType != '\x02') {
				player.cameraCarId = player.playerCarId;
			}
		}
		iVar4 = NoMoreCamerasErrorMessage();
		if (iVar4 == 0) {
			RecordCamera(CameraCnt);
		}
		else {
			cameraview = 0;
			uVar3 = rand();
			gCameraAngle = uVar3 & 0xfff;
			uVar3 = rand();
			CameraPos.vy = -((uVar3 & 0xff) + 100);
			uVar3 = rand();
			gCameraDistance = (uVar3 & 0x7e7) + 1000;
			gCameraMaxDistance = gCameraDistance;
		}
		pSVar2 = PlayerWayRecordPtr;
		PlayerWayRecordPtr->x = 0x7fff;
		pSVar2->y = 0x7fff;
	}
	bVar1 = TimeToWay == 0;
	TimeToWay = TimeToWay + -1;
	if (bVar1) {
		PlayerWayRecordPtr = PlayerWayRecordPtr + 1;
		TimeToWay = way_distance;
	}
	return;*/
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

int SelectCameraCar(int current)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	_EVENT *p_Var3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	long local_10;
	long local_c;

	if (current < 0x14) {
		if (current < -1) {
			current = 0x12 - current;
		}
		iVar1 = current + 1;
		if (iVar1 != current) {
			iVar7 = iVar1 * 0x29c;
			do {
				p_Var3 = (_EVENT *)0x0;
				iVar6 = 0;
				if (iVar1 < 0x14) {
					iVar6 = (int)car_data[0].hd.where.m + iVar7;
					if ((&car_data[0].controlType)[iVar7] == '\x03') {
						local_10 = *(int *)((int)car_data[0].hd.where.t + iVar7);
						local_c = *(int *)((int)car_data[0].hd.where.t + iVar7 + 8);
					}
					else {
						if ((&car_data[0].controlType)[iVar7] == '\x01') {
							if ((int)_PLAYER_ARRAY_000d979c[0].playerCarId == (uint)(byte)(&car_data[0].id)[iVar7]
								) {
								return (int)_PLAYER_ARRAY_000d979c[0].playerCarId;
							}
							return (int)player.playerCarId;
						}
						iVar6 = 0;
						if ((iVar1 == -1) && (player.playerType == '\x02')) {
							return -1;
						}
					}
				}
				else {
					p_Var3 = events.track[iVar1 + -0x14];
					if (p_Var3 == (_EVENT *)0x0) {
						iVar7 = -0x29c;
						iVar1 = -1;
						if (player.playerType == '\x02') {
							iVar7 = -0x538;
							iVar1 = -2;
						}
					}
					else {
						local_10 = (p_Var3->position).vx;
						local_c = (p_Var3->position).vz;
					}
				}
				if ((iVar6 != 0) || (p_Var3 != (_EVENT *)0x0)) {
					iVar5 = player.pos[0] - local_10;
					iVar2 = iVar5;
					if (iVar5 < 0) {
						iVar2 = -iVar5;
					}
					iVar4 = player.pos[2] - local_c;
					if (iVar2 < 15000) {
						iVar2 = iVar4;
						if (iVar4 < 0) {
							iVar2 = -iVar4;
						}
						if ((iVar2 < 15000) && (iVar5 * iVar5 + iVar4 * iVar4 < 225000000)) {
							if (iVar6 != 0) {
								return (uint)*(byte *)(iVar6 + 0x18b);
							}
							return 0x12 - iVar1;
						}
					}
				}
				iVar1 = iVar1 + 1;
				iVar7 = iVar7 + 0x29c;
			} while (iVar1 != current);
		}
		printf(s_ERROR__SelectCameraCar_00010790);
		iVar1 = (int)player.playerCarId;
	}
	else {
		iVar1 = 0;
	}
	return iVar1;*/
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

int InvalidCamera(int car_num)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	uint uVar2;
	ulong uVar3;
	int iVar4;
	int iVar5;
	uint uVar6;
	int iVar7;

	if (cameraview != 0) {
		if (cameraview != 2) {
			uVar3 = Long2DDistance(player.spoolXZ, &player.cameraPos);
			if (11000 < (int)uVar3) {
				player.cameraCarId = -1;
				if (player.playerType != '\x02') {
					player.cameraCarId = player.playerCarId;
				}
				CameraPos.vy = -300;
				cameraview = 0;
				return 1;
			}
			iVar4 = valid_region(player.cameraPos.vx, player.cameraPos.vz);
			if (iVar4 != 0) {
				return 0;
			}
			player.cameraCarId = -1;
			if (player.playerType != '\x02') {
				player.cameraCarId = player.playerCarId;
			}
			cameraview = 2;
			return 1;
		}
		bVar1 = false;
		if (-1 < car_num) {
			bVar1 = car_data[car_num].controlType == '\0';
		}
		if ((car_num == -1) && (player.playerType != '\x02')) {
			bVar1 = true;
		}
		uVar6 = 0;
		if (car_num < -1) {
			if (*events.track != (_EVENT *)0x0) {
				uVar2 = 1;
				do {
					uVar6 = uVar2 & 0xff;
					uVar2 = uVar6 + 1;
				} while (events.track[uVar6] != (_EVENT *)0x0);
			}
			if (-2 - car_num < (int)uVar6) {
				bVar1 = true;
			}
			iVar5 = player.pos[0] - (events.track[car_num * 0x3fffffff + -2]->position).vx;
			iVar4 = iVar5;
			if (iVar5 < 0) {
				iVar4 = -iVar5;
			}
			iVar7 = player.pos[2] - (events.track[car_num * 0x3fffffff + -2]->position).vz;
			if (iVar4 < 15000) {
				iVar4 = iVar7;
				if (iVar7 < 0) {
					iVar4 = -iVar7;
				}
				if ((iVar4 < 15000) && (iVar5 * iVar5 + iVar7 * iVar7 < 225000000)) {
					bVar1 = true;
				}
			}
		}
		if (bVar1) {
			player.cameraCarId = -1;
			if (player.playerType != '\x02') {
				player.cameraCarId = player.playerCarId;
			}
			CameraPos.vy = -300;
			return 1;
		}
	}
	return 0;
	*/
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

int NoMoreCamerasErrorMessage(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	PLAYBACKCAMERA *pPVar1;
	int iVar2;
	uint uVar3;

	pPVar1 = FindFreeCamera();
	iVar2 = 0;
	if (pPVar1 == (PLAYBACKCAMERA *)0x0) {
		if ((FrameCnt & 0x1fU) < 0x10) {
			uVar3 = FrameCnt & 0x1f;
		}
		else {
			uVar3 = 0x20 - (FrameCnt & 0x1fU);
		}
		SetTextColour((uchar)(uVar3 << 3), '\0', '\0');
		iVar2 = 1;
	}
	return iVar2;
	*/
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

int FirstCamera(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	if ((LastChange != (PLAYBACKCAMERA *)0x0) && (LastChange->prev != -1)) {
		return 0;
	}
	return 1;*/
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

int dist(VECTOR *pos1, VECTOR *pos2)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;

	iVar2 = pos1->vx - pos2->vx;
	if (iVar2 < 0) {
		iVar2 = iVar2 + 0xf;
	}
	iVar1 = pos1->vz - pos2->vz;
	if (iVar1 < 0) {
		iVar1 = iVar1 + 0xf;
	}
	iVar2 = SquareRoot0((iVar2 >> 4) * (iVar2 >> 4) + (iVar1 >> 4) * (iVar1 >> 4));
	return iVar2 << 4;
	*/
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

void SetCameraReturnedFromCutscene(int CameraCnt)
{
	UNIMPLEMENTED();
	/*
	PLAYBACKCAMERA *pPVar1;
	int iVar2;

	iVar2 = 0;
	pPVar1 = PlaybackCamera;
	while ((NextChange = pPVar1, iVar2 < 0x3c &&
		((NextChange = PlaybackCamera + iVar2, CameraCnt < NextChange->FrameCnt ||
		((NextChange->next != -2 &&
			(pPVar1 = PlaybackCamera + (byte)NextChange->next, pPVar1->FrameCnt <= CameraCnt))))))) {
		iVar2 = iVar2 + 1;
	}
	LastChange = NextChange;
	SetPlaybackCamera(NextChange);
	FindNextChange(CameraCnt + 1);
	return;*/
}





