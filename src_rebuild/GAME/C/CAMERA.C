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
#include "COSMETIC.H"
#include "CELL.H"
#include "MODELS.H"
#include "DRAW.H"

#include "INLINE_C.H"
#include "LIBGTE.H"


VECTOR CameraPos = { -45, -171, -125, 0 };
VECTOR camera_position = { 0, 380, 0, 0 };
SVECTOR camera_angle = { 0,0,0 };

MATRIX camera_matrix;

MATRIX face_camera_work =
{
	{ 
		{ 4096, 0, 0 }, 
		{ 0, 4096, 0 },
		{ 0, 0, 4096 } 
	},
	{ 0, 0, 0 } 
};

char old_camera_change = 0;
char camera_change = 0;

unsigned short paddCamera;
char cameraview = 0;
int CameraCnt = 0;

static long basePos[4]; // [A]
static long baseDir = 0;

char tracking_car = 0;

int gCameraAngle = 0x800; // offset 0xAA104

int TargetCar = 0;
int CameraCar = 0;

// [A] custom function - recalculates base camera position (separated from InitCamera)
void CalcCameraBasePos(_PLAYER* lp)
{
	CAR_COSMETICS* car_cos;
	_EVENT* event;
	SVECTOR boxDisp = { 0 };

	if (lp->cameraCarId < 0)
	{
		if (lp->cameraCarId < -1)
		{
			event = events.track[-2 - lp->cameraCarId];

			basePos[0] = event->position.vx;
			basePos[1] = -event->position.vy;
			basePos[2] = event->position.vz;
			baseDir = event->rotation + 0x400U & 0xfff;
		}
		else
		{
			basePos[0] = lp->pos[0];
			basePos[1] = lp->pos[1];
			basePos[2] = lp->pos[2];
			baseDir = lp->dir;
		}
	}
	else
	{
		// [A]
		gte_SetRotMatrix(&car_data[lp->cameraCarId].hd.where);
		gte_SetTransMatrix(&car_data[lp->cameraCarId].hd.where);

		// [A]
		car_cos = car_data[lp->cameraCarId].ap.carCos;
		if (car_cos)
		{
			boxDisp.vx = -car_cos->cog.vx;
			boxDisp.vy = -car_cos->cog.vy;
			boxDisp.vz = -car_cos->cog.vz;
		}

		gte_ldv0(&boxDisp);

		gte_rtv0tr();
		gte_stlvnl(basePos);

		baseDir = car_data[lp->cameraCarId].hd.direction;
	}
}

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

// [D] [T]
void InitCamera(_PLAYER *lp)
{
	if (events.cameraEvent == NULL) 
	{
		paddCamera = Pads[lp->padid].mapped;

		if (NoPlayerControl != 0 || gInGameCutsceneActive != 0)
		{
			lp->cameraView = cameraview;
		}

		CalcCameraBasePos(lp);

		if (lp->cameraView == 0)
		{
			if (FrameCnt == 0) 
			{
				lp->cameraDist = 1000;

				gCameraAngle = 2048;
				CameraPos.vx = -45;
				CameraPos.vy = -171;
				CameraPos.vz = -125;
			}
			else
			{
				PlaceCameraFollowCar(lp);
			}
		}
		else if (lp->cameraView == 1)
		{
			if (NoPlayerControl == 0 && gInGameCutsceneActive == 0)
				tracking_car = 1;

			PlaceCameraAtLocation(lp, 1);
		}
		else if (lp->cameraView == 2)
		{
			PlaceCameraInCar(lp, 0);
		}
		else if (lp->cameraView == 5)
		{
			if (NoPlayerControl == 0)
			{
				if (gInGameCutsceneActive == 0)
					tracking_car = 1;

				TargetCar = 0;
			}

			PlaceCameraAtLocation(lp, 0);
		}

		if (gCurrentMissionNumber == 22 && lp->cameraPos.vx < 0 && lp->cameraPos.vz < 0xc1c47 && lp->cameraPos.vz > 700000)
		{
			SpecialCamera(SPECIAL_CAMERA_SET, 0);
		}

		camera_position.vx = lp->cameraPos.vx;
		camera_position.vy = lp->cameraPos.vy;
		camera_position.vz = lp->cameraPos.vz;

		CameraCar = lp->cameraCarId;

		lp->snd_cam_ang = camera_angle.vy;
	}
	else 
	{
		BuildWorldMatrix();
	}

#ifndef PSX
	extern void BuildFreeCameraMatrix();
	BuildFreeCameraMatrix();
#endif
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

// [D] [T]
void ModifyCamera(void)
{
	// camera types which can be chosen during game
	static char inGameCamera[4] = {
		1,0,2,1
	};

	_PLAYER *lp;
	char *pNextCameraView;
	int angle;
	int length;

	int i;

	if (NoPlayerControl == 0 && cameraview != 6 && events.cameraEvent == NULL);// && NumPlayers == 1)	// [A] allow switching cameras in multiplayer
	{
		for(i = 0; i < NumPlayers; i++)
		{
			lp = &player[i];

			if ((Pads[i].mapped & 0x100) != 0)
			{
				if (lp->viewChange != FrameCnt-1) 
				{
					pNextCameraView = inGameCamera;

					while (*pNextCameraView++ != lp->cameraView)
					{
						if (pNextCameraView > inGameCamera + 2)
							break;
					}
					lp->cameraView = *pNextCameraView;
				}

				lp->viewChange = FrameCnt;

				if (lp->cameraView == 1)
				{
					if (lp->cameraCarId < 1)
						length = 360;
					else
						length = car_data[lp->cameraCarId].ap.carCos->colBox.vz;

					CalcCameraBasePos(lp);

					angle = baseDir + 0x800 & 0xfff;
					lp->cameraPos.vx = basePos[0] + FIXED(rcossin_tbl[angle * 2] * (length - 60));
					lp->cameraPos.vz = basePos[2] + FIXED(rcossin_tbl[angle * 2 + 1] * (length - 60));
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

// [D] [T]
int CameraCollisionCheck(void)
{
	int sphere;
	PACKED_CELL_OBJECT *ppco;
	CELL_OBJECT *cop;
	MODEL *model;
	MATRIX2* mat;
	int zd;
	int sizey;
	int xd;
	int *boxptr;
	int sizez;
	int sizex;
	COLLISION_PACKET *collide;
	int count;
	CELL_ITERATOR ci;
	int box_loop;
	int num_cb;
	int cellx;
	int cellz;

	count = 0;
	sphere = scr_z * 3 - 382;

	do {
		cellx = camera_position.vx + (count % 3) * 1024 - 1024 + units_across_halved >> 11;
		cellz = camera_position.vz + (count / 3) * 1024 - 1024 + units_down_halved >> 11;

		if (gCameraDistance > 0)
		{
			ppco = GetFirstPackedCop(cellx, cellz, &ci, 0);
			cop = UnpackCellObject(ppco, &ci.nearCell);

			while (cop != NULL) 
			{
				model = modelpointers[cop->type];
				boxptr = (int *)model->collision_block;

				if (boxptr != NULL && (model->flags2 & 0x800) == 0) 
				{
					xd = cop->pos.vx - camera_position.vx;
					if (xd < 0)
						xd = camera_position.vx - cop->pos.vx;

					zd = cop->pos.vz - camera_position.vz;
					if (zd < 0)
						zd = camera_position.vz - cop->pos.vz;
						

					num_cb = *boxptr;
					collide = (COLLISION_PACKET *)(boxptr + 1);
					if (xd * xd + zd * zd < model->bounding_sphere * model->bounding_sphere + sphere * sphere) 
					{
						box_loop = 0;

						while (box_loop < num_cb)
						{
							VECTOR cam_vec;
							VECTOR offset;

							cam_vec.vx = camera_position.vx - cop->pos.vx;
							cam_vec.vy = camera_position.vy - cop->pos.vy;
							cam_vec.vz = camera_position.vz - cop->pos.vz;

							mat = &matrixtable[cop->yang];

							offset.vx = (cam_vec.vx * mat->m[0][0] + cam_vec.vz * mat->m[2][0] >> 0xc) - collide->xpos;
							offset.vy = cam_vec.vy - collide->ypos;
							offset.vz = (cam_vec.vx * mat->m[0][2] + cam_vec.vz * mat->m[2][2] >> 0xc) - collide->zpos;

							if (collide->yang != 0)
							{
								mat = &matrixtable[collide->yang];
								offset.vx = offset.vx * mat->m[0][0] + offset.vz * mat->m[2][0];
								offset.vz = offset.vx * mat->m[0][2] + offset.vz * mat->m[2][2];
							}

							if (collide->xsize < 500 && collide->zsize < 500)
								break;

							sizex = (collide->xsize >> 1) + sphere;
							sizey = (collide->ysize >> 1) + sphere;
							sizez = (collide->zsize >> 1) + sphere;

							if (-sizex < offset.vx && offset.vx < sizex &&
								-sizez < offset.vz && offset.vz < sizez &&
								-sizey < offset.vy && offset.vy < sizey)
							{
								return 1;
							}

							box_loop++;
							collide++;
						}
					}
				}
				ppco = GetNextPackedCop(&ci);
				cop = UnpackCellObject(ppco, &ci.nearCell);
			}
		}
		count++;

		if (8 < count)
			break;

	} while (true);

	return 0;
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

// [D] [T]
void TurnHead(_PLAYER *lp)
{
	if ((paddCamera & 3) == 3) 
	{
		if (pPlayerPed != NULL)
			pPlayerPed->head_rot = 0;
	}
	else if ((paddCamera & 1) == 0) 
	{
		if ((paddCamera & 2) == 0) // look back
		{
			if (pPlayerPed != NULL)
				pPlayerPed->head_rot = 0;

			lp->headTimer = 0;
			lp->headTarget = 0;
		}
		else
		{
			if (pPlayerPed != NULL)
				pPlayerPed->head_rot = -512;

			if (lp->headTimer > 1)
				lp->headTarget = -0x4000000;
			else
				lp->headTimer++;
		}
	}
	else
	{
		if (pPlayerPed != NULL) 
			pPlayerPed->head_rot = 512;

		if (lp->headTimer > 1)
			lp->headTarget = 0x4000000;
		else
			lp->headTimer++;
	}

	lp->headPos += (lp->headTarget - lp->headPos) / 2;
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
int switch_detail_distance = 10000;

// [D] [T]
void PlaceCameraFollowCar(_PLAYER *lp)
{
	CAR_COSMETICS *car_cos;
	int camAngle;
	int cdist;
	int sdist;
	int carheight;
	int camExpandSpeed;
	int angleDelta;
	int cammapht;
	int camPosVy;

	if (lp->cameraCarId < 0)
	{
		maxCameraDist = 850;
		carheight = -220;
		camExpandSpeed = 10;
	}
	else 
	{
		_CAR_DATA* camCar;
		int carSpeed;
		camCar = &car_data[lp->cameraCarId];

		car_cos = camCar->ap.carCos;

		if(car_cos)
		{
			carheight = car_cos->colBox.vy * -3 + 0x55;
			maxCameraDist = car_cos->colBox.vz * 2 + car_cos->colBox.vy + 248;

			carSpeed = FIXED(camCar->hd.wheel_speed);

			if (carSpeed < 0)
				carSpeed = -carSpeed;

			camExpandSpeed = 10;

			if (carSpeed > 9 && (gCameraDistance + 30 <= maxCameraDist))
				camExpandSpeed = 20;
		}
		else
		{
			maxCameraDist = 850;
			carheight = -220;
			camExpandSpeed = 10;
		}
	}

	if (pauseflag == 0)
		TurnHead(lp);

	camera_angle.vx = 25;
	camAngle = lp->cameraAngle - (lp->headPos >> 16) & 0xfff;

	if (pauseflag == 0 || EditMode == 2)
	{
		if ((paddCamera & 3) == 3)
		{
			camAngle = baseDir & 0xfff;
		}
		else
		{
			angleDelta = (((baseDir + gCameraAngle) - lp->cameraAngle) + 0x800U & 0xfff) - 0x800;
			lp->cameraAngle += (angleDelta >> 3) & 0xfff;
		}
	}

	lp->cameraPos.vx = basePos[0] + FIXED(rcossin_tbl[camAngle * 2] * lp->cameraDist);
	lp->cameraPos.vz = basePos[2] + FIXED(rcossin_tbl[camAngle * 2 + 1] * lp->cameraDist);

	lp->cameraPos.vy = basePos[1];
	camPosVy = MapHeight(&lp->cameraPos);
	lp->cameraPos.vy = carheight - basePos[1];

	cammapht = (carheight - camPosVy) -100;

	if (lp->cameraPos.vy > cammapht)
	{
		int height, tmp;
		height = MapHeight((VECTOR*)basePos);

		tmp = height - camPosVy;

		if (tmp < 0)
			tmp = camPosVy - height;

		if (tmp < 900)
		{
			camera_angle.vx = (lp->cameraPos.vy - cammapht >> 1) + 25;
			lp->cameraPos.vy = cammapht;
		}
	}

	jcam = &car_data[20];
	ClearMem((char *)jcam, sizeof(_CAR_DATA));

	jcam->controlType = 5;

	gCameraDistance = maxCameraDist;

	if (lp->cameraCarId < 0) 
		jcam->ap.carCos = &dummyCosmetics;
	else 
		jcam->ap.carCos = car_data[lp->cameraCarId].ap.carCos;

	jcam->hd.direction = camAngle;
	
	sdist = maxCameraDist * rcossin_tbl[camAngle * 2] + 0x800;
	cdist = maxCameraDist * rcossin_tbl[camAngle * 2 + 1] + 0x800;

	jcam->hd.oBox.location.vx = jcam->hd.where.t[0] = basePos[0] + ((sdist >> 0xc) - (sdist >> 0x1f) >> 1);
	jcam->hd.oBox.location.vy = jcam->hd.where.t[1] = -lp->cameraPos.vy;
	jcam->hd.oBox.location.vz = jcam->hd.where.t[2] = basePos[2] + ((cdist >> 0xc) - (cdist >> 0x1f) >> 1);

	CheckScenaryCollisions(jcam);

	lp->cameraDist += camExpandSpeed;

	if (lp->cameraDist > gCameraDistance)
		lp->cameraDist = gCameraDistance;

	jcam->hd.direction = jcam->hd.direction & 0xfff;

	lp->cameraPos.vy = -jcam->hd.where.t[1];
	lp->cameraPos.vx = basePos[0] + FIXED(lp->cameraDist * rcossin_tbl[jcam->hd.direction * 2]);
	lp->cameraPos.vz = basePos[2] + FIXED(lp->cameraDist * rcossin_tbl[jcam->hd.direction * 2 + 1]);

	camera_angle.vy = -ratan2(basePos[0] - lp->cameraPos.vx, basePos[2] - lp->cameraPos.vz) & 0xfff;
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

// [D] [T]
void PlaceCameraAtLocation(_PLAYER *lp, int zoom)
{
	int d;
	VECTOR temp;

	d = 0;

	if (tracking_car != 0) 
	{
		CalcCameraBasePos(lp);

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
			scr_z = 256;
		}
		else 
		{
			scr_z = (d >> 4) + 256;

			if (scr_z > 800)
				scr_z = 800;
		}
	}

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

// [D] [T]
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

// [D] [T]
void PlaceCameraInCar(_PLAYER *lp, int BumperCam)
{
	int angle;
	_CAR_DATA *cp;

	cp = NULL;

	if (lp->cameraCarId > -1)
		cp = car_data + lp->cameraCarId;

	viewer_position.vx = 0;

	if (cp == NULL) 
	{
		viewer_position.vz = 0;
		viewer_position.vy = viewer_position.vy + 42 + lp->pPed->head_pos;
	}
	else if (cp->ap.carCos != NULL) // [A] prevent crash from happening
	{
		viewer_position.vy = 7;
		viewer_position.vz = cp->ap.carCos->colBox.vz - 80;
	}

	if ((paddCamera & 3) == 3)
		viewer_position.vz = 0;

	angle = baseDir & 0xfff;

	lp->cameraPos.vx = basePos[0] + FIXED(rcossin_tbl[angle * 2] * viewer_position.vz);
	lp->cameraPos.vy = viewer_position.vy - basePos[1];
	lp->cameraPos.vz = basePos[2] + FIXED(rcossin_tbl[angle * 2 + 1] * viewer_position.vz);

	TurnHead(lp);

	if ((paddCamera & 3) == 3)
		camera_angle.vy = 0x800 - baseDir & 0xfff;
	else
		camera_angle.vy = (lp->headPos >> 16) - baseDir & 0xfff;

	SetGeomScreen(256);
	scr_z = 256;

	if (cp == NULL)
	{
		ClearMem((char *)&inv_camera_matrix, sizeof(MATRIX));

		angle = 0x800U - baseDir & 0xfff;

		inv_camera_matrix.m[0][0] = rcossin_tbl[angle * 2 + 1];
		inv_camera_matrix.m[0][2] = rcossin_tbl[angle * 2];
		inv_camera_matrix.m[1][1] = 0x1000;
		inv_camera_matrix.m[2][0] = -inv_camera_matrix.m[0][2];
		inv_camera_matrix.m[2][2] = inv_camera_matrix.m[0][0];
	}
	else
	{
		InvertMatrix(&cp->hd.drawCarMat, &inv_camera_matrix);
	}

	if ((paddCamera & 3) == 3) 
	{
		if (cp != NULL)
			viewer_position.vz = 170;
	}
	else 
	{
		_RotMatrixY(&inv_camera_matrix, 0x800);
		_RotMatrixY(&inv_camera_matrix, (lp->headPos >> 16));

		if (cp != NULL) 
			viewer_position.vz = -170;
	}

	MulMatrix0(&aspect, &inv_camera_matrix, &inv_camera_matrix);
	InvertMatrix(&inv_camera_matrix, &camera_matrix);

	face_camera_work.m[0][0] = 0x1000;
	face_camera_work.m[0][2] = 0;
	face_camera_work.m[2][0] = 0;
	face_camera_work.m[2][2] = 0x1000;

	RotMatrixY(-camera_angle.vy & 0xfff, &face_camera_work);
	MulMatrix0(&inv_camera_matrix, &face_camera_work, &face_camera);

	viewer_position.vy = -40;

	SetRotMatrix(&camera_matrix);
	_MatrixRotate(&viewer_position);

	lp->cameraPos.vx += viewer_position.vx;
	lp->cameraPos.vy += viewer_position.vy;
	lp->cameraPos.vz += viewer_position.vz;

	switch_detail_distance = 10000;
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

// [D] [T]
int OK_To_Zoom(void)
{
	int old_z;
	VECTOR temp;

	old_z = scr_z;

	temp.vx = player[0].pos[0];
	temp.vy = -player[0].pos[1];
	temp.vz = player[0].pos[2];

	scr_z = (dist(&camera_position, &temp) >> 4) + 256;

	if (800 < scr_z)
		scr_z = 800;

	if (scr_z < 256)
		scr_z = 256;

	scr_z = old_z;
	return CameraCollisionCheck() == 0;
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

// [D] [T]
void SetBasePos(VECTOR *pVec)
{
	basePos[0] = pVec->vx;
	basePos[1] = pVec->vy;
	basePos[2] = pVec->vz;
}





