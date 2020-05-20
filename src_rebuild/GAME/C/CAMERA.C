#include "THISDUST.H"
#include "CAMERA.H"
#include "CONVERT.H"
#include "EVENT.H"
#include "MISSION.H"
#include "GLAUNCH.H"
#include "CUTSCENE.H"
#include "MAIN.H"
#include "CARS.H"
#include "PAUSE.H"
#include "DIRECTOR.H"
#include "DR2ROADS.H"
#include "SYSTEM.H"
#include "OBJCOLL.H"
#include "PAD.H"
#include "PLAYERS.H"
#include "PEDEST.H"
#include "DRAW.H"

#include "INLINE_C.H"
#include "LIBGTE.H"
#include "GTEREG.H"


VECTOR CameraPos =
{ -45, -171, -125, 0 };

VECTOR camera_position =
{ 0, 380, 0, 0 };

MATRIX face_camera_work =
{ { { 4096, 0, 0 }, { 0, 4096, 0 }, { 0, 0, 4096 } }, { 0, 0, 0 } };

char old_camera_change = 0;
char camera_change = 0;

MATRIX camera_matrix;

// decompiled code
// original method signature: 
// void /*$ra*/ InitCamera(struct _PLAYER *lp /*$s0*/)
 // line 422, offset 0x0001f5f4
	/* begin block 1 */
		// Start line: 423
		// Start offset: 0x0001F5F4
		// Variables:
	// 		struct SVECTOR boxDisp; // stack offset -16

		/* begin block 1.1 */
			// Start line: 428
			// Start offset: 0x0001F61C
		/* end block 1.1 */
		// End offset: 0x0001F61C
		// End Line: 428

		/* begin block 1.2 */
			// Start line: 441
			// Start offset: 0x0001F6AC
			// Variables:
		// 		struct _CAR_DATA *lcp; // $a0
		/* end block 1.2 */
		// End offset: 0x0001F6AC
		// End Line: 441

		/* begin block 1.3 */
			// Start line: 454
			// Start offset: 0x0001F794
			// Variables:
		// 		struct _EVENT *event; // $a1
		/* end block 1.3 */
		// End offset: 0x0001F794
		// End Line: 455
	/* end block 1 */
	// End offset: 0x0001FA20
	// End Line: 544

	/* begin block 2 */
		// Start line: 844
	/* end block 2 */
	// End Line: 845

extern STREAM_SOURCE* PlayerStartInfo[8];

unsigned short paddCamera;
char cameraview = 0;
int CameraCnt = 0;

static long basePos[4]; // [A]
static long baseDir = 0;

char tracking_car = 0;

int gCameraAngle = 0x800; // offset 0xAA104

int TargetCar = 0;
int CameraCar = 0;

SVECTOR camera_angle = { 0,0,0 };

// [D]
void InitCamera(_PLAYER *lp)
{
	unsigned char bVar1;
	//undefined4 in_zero;
	//undefined4 in_at;
	int iVar2;
	CAR_COSMETICS *pCVar3;
	_EVENT *p_Var4;
	SVECTOR boxDisp = { 0 };

	if (events.cameraEvent == NULL) 
	{
		if (NumPlayers == 2)
		{
			lp->cameraView = 0x2;
		}

		paddCamera = Pads[lp->padid].mapped;

		if ((NoPlayerControl != 0) || (gInGameCutsceneActive != 0))
		{
			lp->cameraView = cameraview;
		}

		iVar2 = (int)lp->cameraCarId;

		if (iVar2 < 0)
		{
			if (iVar2 < -1)
			{
				p_Var4 = events.track[-2 - iVar2];
				basePos[0] = (p_Var4->position).vx;
				basePos[1] = -(p_Var4->position).vy;
				basePos[2] = (p_Var4->position).vz;
				baseDir = (int)p_Var4->rotation + 0x400U & 0xfff;
			}
			else 
			{
				basePos[0] = lp->pos[0];
				basePos[1] = lp->pos[1];
				basePos[2] = lp->pos[2];
				//DAT_000aca9c = lp->pos[3]; // memcpy used?
				baseDir = lp->dir;
			}
		}
		else 
		{
			// [A]
			gte_SetRotMatrix(&car_data[iVar2].hd.where);
			gte_SetTransMatrix(&car_data[iVar2].hd.where);

			// [A]
			pCVar3 = car_data[iVar2].ap.carCos;
			if (pCVar3)
			{
				boxDisp.vx = -pCVar3->cog.vx;
				boxDisp.vy = -pCVar3->cog.vy;
				boxDisp.vz = -pCVar3->cog.vz;
			}

			gte_ldv0(&boxDisp);

			docop2(0x480012);

			basePos[0] = MAC1;
			basePos[1] = MAC2;
			basePos[2] = MAC3;

			baseDir = car_data[iVar2].hd.direction;			
		}

		bVar1 = lp->cameraView;
		if (bVar1 == 1) {
			if ((NoPlayerControl == 0) && (gInGameCutsceneActive == 0))
			{
				tracking_car = '\x01';
			}
			PlaceCameraAtLocation(lp, 1);
		}
		else {
			if (bVar1 < 2) {
				if (bVar1 == 0) {
					if (FrameCnt == 0) {
						lp->cameraDist = 1000;
						gCameraAngle = 0x800;
						CameraPos.vx = -0x2d;
						CameraPos.vy = -0xab;
						CameraPos.vz = -0x7d;
					}
					else {
						PlaceCameraFollowCar(lp);
					}
				}
			}
			else {
				if (bVar1 == 2) {
					if (bTannerSitting == 0) {
						PlaceCameraInCar(lp, 0);
					}
					else {
						PlaceCameraAtLocation(lp, 0);
					}
				}
				else {
					if (bVar1 == 5) {
						if (NoPlayerControl == 0) {
							if (gInGameCutsceneActive == 0) {
								tracking_car = '\x01';
							}
							TargetCar = 0;
						}
						PlaceCameraAtLocation(lp, 0);
					}
				}
			}
		}
		if ((((gCurrentMissionNumber == 0x16) && ((lp->cameraPos).vx < 0)) &&
			(iVar2 = (lp->cameraPos).vz, iVar2 < 0xc1c47)) && (700000 < iVar2)) {
			SpecialCamera(SPECIAL_CAMERA_SET, 0);
		}
		camera_position.vx = (lp->cameraPos).vx;
		camera_position.vy = (lp->cameraPos).vy;
		camera_position.vz = (lp->cameraPos).vz;
		CameraCar = lp->cameraCarId;
		lp->snd_cam_ang = camera_angle.vy;
	}
	else {
		BuildWorldMatrix();
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ModifyCamera()
 // line 553, offset 0x0001fa20
	/* begin block 1 */
		// Start line: 555
		// Start offset: 0x0001FA20
		// Variables:
	// 		struct PAD *locPad; // $a3
	// 		struct _PLAYER *lp; // $a2

		/* begin block 1.1 */
			// Start line: 568
			// Start offset: 0x0001FAFC
			// Variables:
		// 		char *pNextCameraview; // $a0
		/* end block 1.1 */
		// End offset: 0x0001FB48
		// End Line: 578

		/* begin block 1.2 */
			// Start line: 585
			// Start offset: 0x0001FB64
			// Variables:
		// 		int cam_ang; // $a0
		// 		int length; // $a1
		/* end block 1.2 */
		// End offset: 0x0001FC04
		// End Line: 593
	/* end block 1 */
	// End offset: 0x0001FC10
	// End Line: 596

	/* begin block 2 */
		// Start line: 1106
	/* end block 2 */
	// End Line: 1107

	/* begin block 3 */
		// Start line: 1116
	/* end block 3 */
	// End Line: 1117

	/* begin block 4 */
		// Start line: 1117
	/* end block 4 */
	// End Line: 1118

	/* begin block 5 */
		// Start line: 1120
	/* end block 5 */
	// End Line: 1121

/* WARNING: Unknown calling convention yet parameter storage is locked */

char inGameCamera[4] = {
	1,0,2,1
};

// [D] [A] - wierd addresses but must be decompiled OK
void ModifyCamera(void)
{
	ushort *puVar1;
	unsigned char bVar2;
	_PLAYER *lp;
	char *pCamType;
	uint uVar5;
	int iVar6;

	int i;

	if (NoPlayerControl == 0 && cameraview != 6 && events.cameraEvent == NULL && NumPlayers == 1) 
	{
		for(i = 0; i < NumPlayers; i++)
		{
			lp = &player[i];

			if ((Pads[i].mapped & 0x100) != 0)
			{
				if ((lp->viewChange != FrameCnt + -1)) 
				{
					pCamType = inGameCamera;
					bVar2 = inGameCamera[0];

					while (pCamType++, bVar2 != lp->cameraView)
					{
						if (inGameCamera + 2 < pCamType)
							goto LAB_0001fb48;

						bVar2 = *pCamType;
					}

					lp->cameraView = *pCamType;
				}

			LAB_0001fb48:
				lp->viewChange = FrameCnt;

				if (lp->cameraView == 1)
				{
					if (lp->cameraCarId < 1)
						iVar6 = 360;
					else
						iVar6 = car_data[lp->cameraCarId].ap.carCos->colBox.vz;

					uVar5 = baseDir + 0x800 & 0xfff;
					lp->cameraPos.vx = basePos[0] + FIXED(rcossin_tbl[uVar5 * 2] * (iVar6 - 60));
					lp->cameraPos.vz = basePos[2] + FIXED(rcossin_tbl[uVar5 * 2 + 1] * (iVar6 - 60));
				}
			}
		}
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ CameraCollisionCheck()
 // line 609, offset 0x0001fc18
	/* begin block 1 */
		// Start line: 611
		// Start offset: 0x0001FC18
		// Variables:
	// 		struct MODEL *model; // $v1
	// 		struct COLLISION_PACKET *collide; // $t2
	// 		struct CELL_OBJECT *cop; // $t3
	// 		struct CELL_ITERATOR ci; // stack offset -168
	// 		struct VECTOR nearpoint; // stack offset -144
	// 		struct VECTOR surfacenormal; // stack offset -128
	// 		struct VECTOR surfacepoint; // stack offset -112
	// 		int cell_x; // $a0
	// 		int cell_z; // $a1
	// 		int xd; // $v1
	// 		int zd; // $a0
	// 		int num_cb; // $t5
	// 		int box_loop; // $t4
	// 		int sphere_sq; // $a2
	// 		int camera_size; // $s0
	// 		int count; // $s1
	// 		struct VECTOR temp_cam; // stack offset -96

		/* begin block 1.1 */
			// Start line: 659
			// Start offset: 0x0001FDF4
			// Variables:
		// 		struct MATRIX *mat; // $a2
		// 		struct VECTOR offset; // stack offset -80
		// 		struct VECTOR cam_vec; // stack offset -64
		// 		struct VECTOR normal; // stack offset -48
		// 		int xmin; // $a0
		// 		int xmax; // $a3
		// 		int ymin; // $t0
		// 		int ymax; // $v1
		// 		int zmin; // $a1
		// 		int zmax; // $a2
		// 		int tx; // $a3
		// 		int tz; // $a1
		/* end block 1.1 */
		// End offset: 0x0001FFD0
		// End Line: 694
	/* end block 1 */
	// End offset: 0x0002003C
	// End Line: 702

	/* begin block 2 */
		// Start line: 1273
	/* end block 2 */
	// End Line: 1274

	/* begin block 3 */
		// Start line: 1274
	/* end block 3 */
	// End Line: 1275

	/* begin block 4 */
		// Start line: 1291
	/* end block 4 */
	// End Line: 1292

/* WARNING: Unknown calling convention yet parameter storage is locked */

int CameraCollisionCheck(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	PACKED_CELL_OBJECT *ppco;
	CELL_OBJECT *pCVar2;
	uint uVar3;
	MODEL *pMVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int *piVar8;
	int iVar9;
	int *piVar10;
	int iVar11;
	CELL_ITERATOR aCStack168[3];
	int local_60;
	int local_58;
	int local_50;
	int local_4c;
	int local_48;

	iVar11 = 0;
	iVar1 = scr_z * 3 + -0x17e;
	do {
		local_60 = camera_position.vx + (iVar11 % 3) * 0x400 + -0x400;
		iVar7 = local_60 + units_across_halved;
		local_58 = camera_position.vz + (iVar11 / 3) * 0x400 + -0x400;
		if (iVar7 < 0) {
			iVar7 = iVar7 + 0x7ff;
		}
		iVar5 = local_58 + units_down_halved;
		if (iVar5 < 0) {
			iVar5 = iVar5 + 0x7ff;
		}
		if (0 < gCameraDistance) {
			ppco = GetFirstPackedCop(iVar7 >> 0xb, iVar5 >> 0xb, aCStack168, 0);
			pCVar2 = UnpackCellObject(ppco, &aCStack168[0].nearCell);
			while (pCVar2 != (CELL_OBJECT *)0x0) {
				pMVar4 = modelpointers1536[pCVar2->type];
				piVar8 = (int *)pMVar4->collision_block;
				if ((piVar8 != (int *)0x0) && ((pMVar4->flags2 & 0x800) == 0)) {
					iVar5 = (pCVar2->pos).vx;
					iVar7 = iVar5 - camera_position.vx;
					if (iVar7 < 0) {
						iVar7 = camera_position.vx - iVar5;
					}
					iVar6 = (pCVar2->pos).vz;
					iVar5 = iVar6 - camera_position.vz;
					if (iVar5 < 0) {
						iVar5 = camera_position.vz - iVar6;
					}
					piVar10 = piVar8 + 1;
					if (iVar7 * iVar7 + iVar5 * iVar5 <
						(int)pMVar4->bounding_sphere * (int)pMVar4->bounding_sphere + iVar1 * iVar1) {
						iVar7 = 0;
						if (0 < *piVar8) {
							do {
								uVar3 = (uint)pCVar2->yang;
								iVar9 = camera_position.vx - (pCVar2->pos).vx;
								iVar6 = camera_position.vz - (pCVar2->pos).vz;
								iVar5 = iVar9 * (&matrixtable)[uVar3].m[0] + iVar6 * (&matrixtable)[uVar3].m[6];
								if (iVar5 < 0) {
									iVar5 = iVar5 + 0xfff;
								}
								iVar6 = iVar9 * (&matrixtable)[uVar3].m[2] + iVar6 * (&matrixtable)[uVar3].m[8];
								if (iVar6 < 0) {
									iVar6 = iVar6 + 0xfff;
								}
								iVar9 = (iVar5 >> 0xc) - (int)*(short *)((int)piVar10 + 2);
								local_4c = (camera_position.vy - (pCVar2->pos).vy) - (int)*(short *)(piVar10 + 1);
								local_48 = (iVar6 >> 0xc) - (int)*(short *)((int)piVar10 + 6);
								iVar5 = (int)*(short *)((int)piVar10 + 10);
								local_50 = iVar9;
								if (iVar5 != 0) {
									local_50 = iVar9 * (&matrixtable)[iVar5].m[0] +
										local_48 * (&matrixtable)[iVar5].m[6];
									local_48 = iVar9 * (&matrixtable)[iVar5].m[2] +
										local_48 * (&matrixtable)[iVar5].m[8];
								}
								iVar5 = (uint)*(ushort *)((int)piVar10 + 0xe) << 0x10;
								if ((iVar5 >> 0x10 < 500) && ((short)*(ushort *)((int)piVar10 + 0x12) < 500)) break;
								iVar9 = (iVar5 >> 0x11) + iVar1;
								iVar6 = ((int)((uint)*(ushort *)((int)piVar10 + 0x12) << 0x10) >> 0x11) + iVar1;
								iVar5 = ((int)((uint)*(ushort *)(piVar10 + 4) << 0x10) >> 0x11) + iVar1;
								if (((-iVar9 < local_50) &&
									(((local_50 < iVar9 && (-iVar6 < local_48)) && (local_48 < iVar6)))) &&
									((-iVar5 < local_4c && (local_4c < iVar5)))) {
									return 1;
								}
								iVar7 = iVar7 + 1;
								piVar10 = piVar10 + 5;
							} while (iVar7 < *piVar8);
						}
					}
				}
				ppco = GetNextPackedCop(aCStack168);
				pCVar2 = UnpackCellObject(ppco, &aCStack168[0].nearCell);
			}
		}
		iVar11 = iVar11 + 1;
		if (8 < iVar11) {
			return 0;
		}
	} while (true);*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ TurnHead(struct _PLAYER *lp /*$a0*/)
 // line 716, offset 0x00020a10
	/* begin block 1 */
		// Start line: 717
		// Start offset: 0x00020A10
	/* end block 1 */
	// End offset: 0x00020B08
	// End Line: 757

	/* begin block 2 */
		// Start line: 1432
	/* end block 2 */
	// End Line: 1433

	/* begin block 3 */
		// Start line: 2114
	/* end block 3 */
	// End Line: 2115

// [D]
void TurnHead(_PLAYER *lp)
{
	unsigned char bVar1;

	if ((paddCamera & 3) == 3) 
	{
		if (pPlayerPed != NULL)
			pPlayerPed->head_rot = 0;

		goto LAB_00020ae8;
	}

	if ((paddCamera & 1) == 0) 
	{
		if ((paddCamera & 2) == 0)
		{
			if (pPlayerPed != NULL)
				pPlayerPed->head_rot = 0;

			lp->headTimer = '\0';
			lp->headTarget = 0;
			goto LAB_00020ae8;
		}

		if (pPlayerPed != NULL) 
			pPlayerPed->head_rot = -0x200;

		bVar1 = lp->headTimer;
		if (1 < bVar1) 
		{
			lp->headTarget = -0x4000000;
			goto LAB_00020ae8;
		}
	}
	else
	{
		if (pPlayerPed != NULL) 
			pPlayerPed->head_rot = 0x200;

		bVar1 = lp->headTimer;
		if (1 < bVar1) 
		{
			lp->headTarget = 0x4000000;
			goto LAB_00020ae8;
		}
	}

	lp->headTimer = bVar1 + 1;
LAB_00020ae8:
	lp->headPos = lp->headPos + (lp->headTarget - lp->headPos >> 1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlaceCameraFollowCar(struct _PLAYER *lp /*$s2*/)
 // line 777, offset 0x0002003c
	/* begin block 1 */
		// Start line: 778
		// Start offset: 0x0002003C
		// Variables:
	// 		int carheight; // $a0
	// 		int minimum_height; // $s1
	// 		int cammapht; // $s0
	// 		int new_angle; // $a0
	// 		int camPosVy; // $s1
	// 		struct VECTOR locCameraPos; // stack offset -48
	// 		int lbody; // $a0
	// 		int hbody; // $a3
	// 		int camExpandSpeed; // $s6

		/* begin block 1.1 */
			// Start line: 800
			// Start offset: 0x00020088
			// Variables:
		// 		struct _CAR_DATA *camCar; // $v1
		/* end block 1.1 */
		// End offset: 0x0002011C
		// End Line: 810
	/* end block 1 */
	// End offset: 0x0002050C
	// End Line: 893

	/* begin block 2 */
		// Start line: 1667
	/* end block 2 */
	// End Line: 1668

	/* begin block 3 */
		// Start line: 1743
	/* end block 3 */
	// End Line: 1744

int maxCameraDist;
short gCameraDistance = 0x3e8;
short gCameraMaxDistance = 0x3e8;

_CAR_DATA *jcam = NULL;
int switch_detail_distance = 0x2710;

// [D]
void PlaceCameraFollowCar(_PLAYER *lp)
{
	_CAR_DATA *p_Var1;
	short sVar2;
	int iVar3;
	int iVar4;
	CAR_COSMETICS *pCVar5;
	uint uVar6;
	uint uVar7;
	int iVar8;
	int iVar9;
	int iVar10;

	iVar3 = lp->cameraCarId;

	if (iVar3 < 0) 
	{
		maxCameraDist = 850;
		iVar9 = -220;
		iVar10 = 10;
	}
	else 
	{
		pCVar5 = car_data[iVar3].ap.carCos;

		if(pCVar5)
		{
			iVar10 = pCVar5->colBox.vy;

			iVar9 = iVar10 * -3 + 0x55;
			maxCameraDist = pCVar5->colBox.vz * 2 + iVar10 + 248;
			iVar3 = FIXED(car_data[iVar3].hd.wheel_speed);

			if (iVar3 < 0)
				iVar3 = -iVar3;

			iVar10 = 10;

			if (iVar3 > 9 && (gCameraDistance + 30 <= maxCameraDist))
				iVar10 = 0x14;
		}
		else
		{
			maxCameraDist = 850;
			iVar9 = -220;
			iVar10 = 10;
		}
	}

	if (pauseflag == 0)
		TurnHead(lp);

	camera_angle.vx = 25;
	uVar7 = lp->cameraAngle - (int)*(short *)((int)&lp->headPos + 2);

	if (pauseflag == 0) 
	{
		if ((paddCamera & 3) == 3)
		{
			uVar7 = baseDir & 0xfff;
			goto LAB_000201cc;
		}
	}
	else 
	{
		if (EditMode != 2)
			goto LAB_000201cc;
	}

	uVar6 = ((baseDir + gCameraAngle) - lp->cameraAngle) + 0x800U & 0xfff;
	iVar3 = uVar6 - 0x800;

	lp->cameraAngle += (iVar3 >> 3) & 0xfff;

LAB_000201cc:
	uVar7 = uVar7 & 0xfff;
	iVar8 = lp->cameraDist;

	iVar3 = rcossin_tbl[uVar7 * 2] * iVar8;
	(lp->cameraPos).vx = basePos[0] + FIXED(iVar3);

	iVar8 = rcossin_tbl[uVar7 * 2 + 1] * iVar8;
	(lp->cameraPos).vz = basePos[2] + FIXED(iVar8);

	(lp->cameraPos).vy = basePos[1];
	iVar3 = MapHeight(&lp->cameraPos);
	(lp->cameraPos).vy = iVar9 - basePos[1];

	iVar8 = (iVar9 - iVar3) -100;
	iVar9 = MapHeight((VECTOR *)basePos);

	if (iVar8 < (lp->cameraPos).vy)
	{
		iVar4 = iVar9 - iVar3;
		if (iVar4 < 0) 
			iVar4 = iVar3 - iVar9;

		if (iVar4 < 900)
		{
			camera_angle.vx = (lp->cameraPos.vy - iVar8 >> 1) + 25;
			lp->cameraPos.vy = iVar8;
		}
	}

	jcam = car_data + 20;
	ClearMem((char *)jcam, sizeof(_CAR_DATA));

	jcam->controlType = 5;

	p_Var1 = jcam;
	iVar3 = maxCameraDist;
	gCameraDistance = iVar3;

	if (lp->cameraCarId < 0) 
	{
		pCVar5 = NULL;
	}
	else 
	{
		pCVar5 = car_data[lp->cameraCarId].ap.carCos;
	}

	(jcam->ap).carCos = pCVar5;
	(p_Var1->hd).direction = uVar7;
	
	iVar9 = iVar3 * rcossin_tbl[uVar7 * 2] + 0x800;
	iVar9 = basePos[0] + ((iVar9 >> 0xc) - (iVar9 >> 0x1f) >> 1);
	(p_Var1->hd).where.t[0] = iVar9;
	(p_Var1->hd).oBox.location.vx = iVar9;
	iVar9 = -(lp->cameraPos).vy;
	(p_Var1->hd).where.t[1] = iVar9;

	(p_Var1->hd).oBox.location.vy = iVar9;
	iVar3 = iVar3 * rcossin_tbl[uVar7 * 2 + 1] + 0x800;
	iVar3 = basePos[2] + ((iVar3 >> 0xc) - (iVar3 >> 0x1f) >> 1);
	(p_Var1->hd).where.t[2] = iVar3;
	(p_Var1->hd).oBox.location.vz = iVar3;

	CheckScenaryCollisions(car_data + 20);
	p_Var1 = jcam;

	iVar10 = lp->cameraDist + iVar10;
	iVar3 = gCameraDistance;

	if (iVar10 < gCameraDistance)
		iVar3 = iVar10;

	lp->cameraDist = iVar3;
	iVar3 = -(p_Var1->hd).where.t[1];
	(p_Var1->hd).where.t[1] = iVar3;
	(lp->cameraPos).vy = iVar3;

	uVar7 = (p_Var1->hd).direction & 0xfff;
	(p_Var1->hd).direction = uVar7;

	iVar3 = lp->cameraDist;

	iVar10 = basePos[0] + FIXED(iVar3 * rcossin_tbl[uVar7 * 2]);
	iVar3 = basePos[2] + FIXED(iVar3 * rcossin_tbl[((p_Var1->hd).direction & 0xfffU) * 2 + 1]);

	lp->cameraPos.vz = iVar3;
	lp->cameraPos.vx = iVar10;

	sVar2 = ratan2(basePos[0] - iVar10, basePos[2] - iVar3);

	camera_angle.vy = -sVar2 & 0xfff;
	camera_angle.vz = 0;

	SetGeomScreen(0x100);
	scr_z = 0x100;
	switch_detail_distance = 10000;

	BuildWorldMatrix();
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlaceCameraAtLocation(struct _PLAYER *lp /*$s1*/, int zoom /*$s2*/)
 // line 904, offset 0x00020904
	/* begin block 1 */
		// Start line: 905
		// Start offset: 0x00020904
		// Variables:
	// 		int d; // $s0

		/* begin block 1.1 */
			// Start line: 911
			// Start offset: 0x00020930
			// Variables:
		// 		struct VECTOR temp; // stack offset -32
		/* end block 1.1 */
		// End offset: 0x00020930
		// End Line: 913
	/* end block 1 */
	// End offset: 0x000209F8
	// End Line: 950

	/* begin block 2 */
		// Start line: 2237
	/* end block 2 */
	// End Line: 2238

	/* begin block 3 */
		// Start line: 1808
	/* end block 3 */
	// End Line: 1809

	/* begin block 4 */
		// Start line: 2240
	/* end block 4 */
	// End Line: 2241

// [D]
void PlaceCameraAtLocation(_PLAYER *lp, int zoom)
{
	int iVar1;
	int d;
	VECTOR temp;

	d = 0;

	if (tracking_car != 0) 
	{
		temp.vx = basePos[0];
		temp.vy = -basePos[1];
		temp.vz = basePos[2];

		d = PointAtTarget(&lp->cameraPos, &temp, &camera_angle);

		if (16000 < d)
		{
			lp->cameraView = 0;
			return;
		}

		if (zoom == 0) 
		{
			scr_z = iVar1 = 256;
		}
		else 
		{
			scr_z = (d >> 4) + 256;
			iVar1 = 800;
			if (scr_z < 801) 
				goto LAB_000209b0;
		}

		scr_z = iVar1;
	}

LAB_000209b0:
	if (scr_z < 256)
		scr_z = 256;

	SetGeomScreen(scr_z);
	switch_detail_distance = 10000 + d * 4;
	BuildWorldMatrix();
}



// decompiled code
// original method signature: 
// int /*$ra*/ PointAtTarget(struct VECTOR *pPosition /*$a0*/, struct VECTOR *pTarget /*$a1*/, struct SVECTOR *pAngleVec /*$s0*/)
 // line 960, offset 0x00020b08
	/* begin block 1 */
		// Start line: 961
		// Start offset: 0x00020B08
		// Variables:
	// 		struct VECTOR delta; // stack offset -32
	// 		int d; // $s1
	/* end block 1 */
	// End offset: 0x00020BC0
	// End Line: 976

	/* begin block 2 */
		// Start line: 2394
	/* end block 2 */
	// End Line: 2395

	/* begin block 3 */
		// Start line: 2598
	/* end block 3 */
	// End Line: 2599

	/* begin block 4 */
		// Start line: 2602
	/* end block 4 */
	// End Line: 2603

// [D]
int PointAtTarget(VECTOR *pPosition, VECTOR *pTarget, SVECTOR *pAngleVec)
{
	VECTOR delta;

	delta.vx = pTarget->vx - pPosition->vx;
	delta.vy = pTarget->vy - pPosition->vy;
	delta.vz = pTarget->vz - pPosition->vz;

	int d = SquareRoot0(delta.vx * delta.vx + delta.vz * delta.vz);

	pAngleVec->vx = 1024 - ratan2(d, delta.vy) & 0xfff;
	pAngleVec->vy = -ratan2(delta.vx, delta.vz) & 0xfff;
	pAngleVec->vz = 0;

	return d;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlaceCameraInCar(struct _PLAYER *lp /*$s3*/, int BumperCam /*$a1*/)
 // line 987, offset 0x0002050c
	/* begin block 1 */
		// Start line: 988
		// Start offset: 0x0002050C
		// Variables:
	// 		struct _CAR_DATA *cp; // $s2

		/* begin block 1.1 */
			// Start line: 1044
			// Start offset: 0x000207BC
		/* end block 1.1 */
		// End offset: 0x000207CC
		// End Line: 1045

		/* begin block 1.2 */
			// Start line: 1049
			// Start offset: 0x000207E0
		/* end block 1.2 */
		// End offset: 0x00020800
		// End Line: 1052
	/* end block 1 */
	// End offset: 0x00020904
	// End Line: 1077

	/* begin block 2 */
		// Start line: 2104
	/* end block 2 */
	// End Line: 2105

	/* begin block 3 */
		// Start line: 2199
	/* end block 3 */
	// End Line: 2200

VECTOR viewer_position;

// [D]
void PlaceCameraInCar(_PLAYER *lp, int BumperCam)
{
	ushort uVar1;
	uint uVar2;
	_CAR_DATA *p_Var3;
	int iVar4;

	p_Var3 = (_CAR_DATA *)0x0;
	if (-1 < (int)lp->cameraCarId) {
		p_Var3 = car_data + (int)lp->cameraCarId;
	}
	viewer_position.vx = 0;
	if (p_Var3 == (_CAR_DATA *)0x0) {
		viewer_position.vz = 0;
		viewer_position.vy = viewer_position.vy + 0x2a + (int)lp->pPed->head_pos;
	}
	else {
		viewer_position.vy = 7;
		viewer_position.vz = (int)(((p_Var3->ap).carCos)->colBox).vz + -0x50;
	}
	if ((paddCamera & 3) == 3) {
		viewer_position.vz = 0;
	}
	if (p_Var3 == (_CAR_DATA *)0x0) {
		uVar2 = baseDir & 0xfff;
		(lp->cameraPos).vx = basePos[0];
		(lp->cameraPos).vy = -basePos[1];
		(lp->cameraPos).vz = basePos[2];
		(lp->cameraPos).vx = basePos[0] + (rcossin_tbl[uVar2 * 2] * viewer_position.vz + 0x800 >> 0xc);
		(lp->cameraPos).vy = viewer_position.vy - basePos[1];
		iVar4 = rcossin_tbl[uVar2 * 2 + 1] * viewer_position.vz;
	}
	else {
		uVar2 = baseDir & 0xfff;
		(lp->cameraPos).vx = basePos[0] + (rcossin_tbl[uVar2 * 2] * viewer_position.vz + 0x800 >> 0xc);
		(lp->cameraPos).vy = viewer_position.vy - basePos[1];
		iVar4 = rcossin_tbl[uVar2 * 2 + 1] * viewer_position.vz;
	}
	(lp->cameraPos).vz = basePos[2] + (iVar4 + 0x800 >> 0xc);
	TurnHead(lp);
	if ((paddCamera & 3) == 3) {
		uVar1 = 0x800 - (short)baseDir;
	}
	else {
		uVar1 = *(short *)((int)&lp->headPos + 2) - (short)baseDir;
	}
	camera_angle.vy = uVar1 & 0xfff;
	SetGeomScreen(0x100);
	scr_z = 0x100;
	if (p_Var3 == (_CAR_DATA *)0x0) {
		ClearMem((char *)&inv_camera_matrix, 0x20);
		uVar2 = 0x800U - baseDir & 0xfff;
		inv_camera_matrix.m[0][0] = rcossin_tbl[uVar2 * 2 + 1];
		inv_camera_matrix.m[0][2] = rcossin_tbl[uVar2 * 2];
		inv_camera_matrix.m[1][1] = 0x1000;
		inv_camera_matrix.m[2][0] = -inv_camera_matrix.m[0][2];
		inv_camera_matrix.m[2][2] = inv_camera_matrix.m[0][0];
	}
	else {
		InvertMatrix(&(p_Var3->hd).drawCarMat, &inv_camera_matrix);
	}
	if ((paddCamera & 3) == 3) {
		if (p_Var3 != (_CAR_DATA *)0x0) {
			viewer_position.vz = 0xaa;
		}
	}
	else {
		_RotMatrixY(&inv_camera_matrix, 0x800);
		_RotMatrixY(&inv_camera_matrix, *(short *)((int)&lp->headPos + 2));
		if (p_Var3 != (_CAR_DATA *)0x0) {
			viewer_position.vz = -0xaa;
		}
	}
	MulMatrix0(&aspect, &inv_camera_matrix, &inv_camera_matrix);
	InvertMatrix(&inv_camera_matrix, &camera_matrix);
	face_camera_work.m[0][0] = 0x1000;
	face_camera_work.m[0][2] = 0;
	face_camera_work.m[2][0] = 0;
	face_camera_work.m[2][2] = 0x1000;
	RotMatrixY(-(int)camera_angle.vy & 0xfff, &face_camera_work);
	MulMatrix0(&inv_camera_matrix, &face_camera_work, &face_camera);
	viewer_position.vy = -0x28;
	SetRotMatrix(&camera_matrix);
	_MatrixRotate(&viewer_position);
	(lp->cameraPos).vx = (lp->cameraPos).vx + viewer_position.vx;
	(lp->cameraPos).vy = (lp->cameraPos).vy + viewer_position.vy;
	(lp->cameraPos).vz = (lp->cameraPos).vz + viewer_position.vz;
	switch_detail_distance = 0x2710;
}



// decompiled code
// original method signature: 
// int /*$ra*/ OK_To_Zoom()
 // line 1083, offset 0x00020bc0
	/* begin block 1 */
		// Start line: 1085
		// Start offset: 0x00020BC0
		// Variables:
	// 		int old_z; // $s0
	// 		struct VECTOR temp; // stack offset -24
	/* end block 1 */
	// End offset: 0x00020C70
	// End Line: 1114

	/* begin block 2 */
		// Start line: 2753
	/* end block 2 */
	// End Line: 2754

	/* begin block 3 */
		// Start line: 2861
	/* end block 3 */
	// End Line: 2862

	/* begin block 4 */
		// Start line: 2862
	/* end block 4 */
	// End Line: 2863

	/* begin block 5 */
		// Start line: 2872
	/* end block 5 */
	// End Line: 2873

/* WARNING: Unknown calling convention yet parameter storage is locked */

int OK_To_Zoom(void)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	VECTOR local_18;

	iVar1 = scr_z;
	local_18.vx = player.pos[0];
	local_18.vy = -player.pos[1];
	local_18.vz = player.pos[2];
	iVar2 = dist(&camera_position, &local_18);
	scr_z = (iVar2 >> 4) + 0x100;
	if (800 < scr_z) {
		scr_z = 800;
	}
	if (scr_z < 0x100) {
		scr_z = 0x100;
	}
	iVar2 = CameraCollisionCheck();
	scr_z = iVar1;
	return (uint)(iVar2 == 0);*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetBasePos(struct VECTOR *pVec /*$a0*/)
 // line 1119, offset 0x00020c70
	/* begin block 1 */
		// Start line: 2945
	/* end block 1 */
	// End Line: 2946

	/* begin block 2 */
		// Start line: 2951
	/* end block 2 */
	// End Line: 2952

	/* begin block 3 */
		// Start line: 2952
	/* end block 3 */
	// End Line: 2953

// [D]
void SetBasePos(VECTOR *pVec)
{
	basePos[0] = pVec->vx;
	basePos[1] = pVec->vy;
	basePos[2] = pVec->vz;
}





