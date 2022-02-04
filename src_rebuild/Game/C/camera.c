#include "driver2.h"
#include "camera.h"
#include "convert.h"
#include "event.h"
#include "mission.h"
#include "glaunch.h"
#include "cutscene.h"
#include "main.h"
#include "cars.h"
#include "pause.h"
#include "director.h"
#include "dr2roads.h"
#include "system.h"
#include "objcoll.h"
#include "pad.h"
#include "players.h"
#include "draw.h"
#include "cell.h"
#include "models.h"
#include "map.h"
#include "pedest.h"
#include "cell.h"

VECTOR gCameraOffset = { 0};
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

static LONGVECTOR4 basePos; // [A]
static int baseDir = 0;

char tracking_car = 0;

int gCameraAngle = 2048; // offset 0xAA104

int TargetCar = 0;
int CameraCar = 0;

// [A] custom function - recalculates base camera position (separated from InitCamera)
void CalcCameraBasePos(PLAYER* lp)
{
	CAR_COSMETICS* car_cos;
	EVENT* event;
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

			EventCameraOffset(&boxDisp);	// [A]

			basePos[0] += boxDisp.vx;
			basePos[1] += boxDisp.vy - gCameraOffset.vy;
			basePos[2] += boxDisp.vz;
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

		if(gInGameCutsceneActive == 0)
			basePos[1] -= gCameraOffset.vy;

		baseDir = car_data[lp->cameraCarId].hd.direction;
	}
}

// [D] [T]
void InitCamera(PLAYER *lp)
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
				gCameraMaxDistance = 0;
				
				gCameraOffset.vx = 0;
				gCameraOffset.vy = 0;
				gCameraOffset.vz = 0;
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

		// "Beat the Train" hack
		if (gCurrentMissionNumber == 22 && 
			lp->cameraPos.vx < 0 && 
			lp->cameraPos.vz < 793671 && lp->cameraPos.vz > 700000)
		{
			SetSpecialCamera(SPECIAL_CAMERA_SET, 0);
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

// [D] [T]
void ModifyCamera(void)
{
	// camera types which can be chosen during game
	static char inGameCamera[4] = {
		1,0,2,1
	};

	PLAYER *lp;
	char *pNextCameraView;
	int angle;
	int length;

	int i;

	if (NoPlayerControl || cameraview == 6 || events.cameraEvent != NULL) // || NumPlayers > 1)	// [A] allow switching cameras in multiplayer
		return;

	for(i = 0; i < NumPlayers; i++)
	{
		lp = &player[i];

		if (Pads[i].mapped & 0x100)
		{
			// [A] if only new button is pressed
			if (lp->viewChange != FrameCnt-1 && (Pads[i].mapnew & 0x100))
			{
				pNextCameraView = inGameCamera;

				while (*pNextCameraView++ != lp->cameraView)
				{
					if (pNextCameraView > inGameCamera + 2)
						break;
				}
			
				lp->cameraView = *pNextCameraView;
				lp->viewChange = FrameCnt;
			}

			if (lp->cameraView == 1)
			{
				if (lp->cameraCarId < 1)
					length = 360;
				else
					length = car_data[lp->cameraCarId].ap.carCos->colBox.vz;

				CalcCameraBasePos(lp);

				angle = baseDir + 2048;
				lp->cameraPos.vx = basePos[0] + FIXEDH(RSIN(angle) * (length - 60));
				lp->cameraPos.vz = basePos[2] + FIXEDH(RCOS(angle) * (length - 60));
			}
		}
	}
}

// [D] [T]
int CameraCollisionCheck(void)
{
	int sphere;
	PACKED_CELL_OBJECT *ppco;
	CELL_OBJECT tempCO;
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
	int cellLevel;

	count = 0;
	sphere = scr_z * 3 - 382;

	cellLevel = events.camera ? events.draw : -1;

	do {
		cellx = (camera_position.vx + (count % 3) * MAP_REGION_SIZE*MAP_REGION_SIZE - MAP_REGION_SIZE*MAP_REGION_SIZE + units_across_halved) / MAP_CELL_SIZE;
		cellz = (camera_position.vz + (count / 3) * MAP_REGION_SIZE*MAP_REGION_SIZE - MAP_REGION_SIZE*MAP_REGION_SIZE + units_down_halved) / MAP_CELL_SIZE;

		if (gCameraDistance > 0)
		{
			ppco = GetFirstPackedCop(cellx, cellz, &ci, 0, cellLevel);
			
			while (ppco) 
			{
				int type = (ppco->value >> 6) | ((ppco->pos.vy & 1) << 10);

				model = modelpointers[type];
				boxptr = (int *)model->collision_block;

				if (boxptr != NULL && (model->flags2 & MODEL_FLAG_SMASHABLE) == 0)
				{
					QuickUnpackCellObject(ppco, &ci.nearCell, &tempCO);

					xd = ABS(tempCO.pos.vx - camera_position.vx);
					zd = ABS(tempCO.pos.vz - camera_position.vz);

					num_cb = *boxptr;
					collide = (COLLISION_PACKET *)(boxptr + 1);
					if (xd * xd + zd * zd < model->bounding_sphere * model->bounding_sphere + sphere * sphere) 
					{
						box_loop = 0;

						while (box_loop < num_cb)
						{
							VECTOR cam_vec;
							VECTOR offset;

							cam_vec.vx = camera_position.vx - tempCO.pos.vx;
							cam_vec.vy = camera_position.vy - tempCO.pos.vy;
							cam_vec.vz = camera_position.vz - tempCO.pos.vz;

							mat = &matrixtable[tempCO.yang];

							offset.vx = FIXED(cam_vec.vx * mat->m[0][0] + cam_vec.vz * mat->m[2][0]) - collide->xpos;
							offset.vy = cam_vec.vy - collide->ypos;
							offset.vz = FIXED(cam_vec.vx * mat->m[0][2] + cam_vec.vz * mat->m[2][2]) - collide->zpos;

							if (collide->yang != 0)
							{
								mat = &matrixtable[collide->yang];
								offset.vx = offset.vx * mat->m[0][0] + offset.vz * mat->m[2][0];
								offset.vz = offset.vx * mat->m[0][2] + offset.vz * mat->m[2][2];
							}

							if (collide->xsize < 500 && collide->zsize < 500)
								break;

							sizex = (collide->xsize / 2) + sphere;
							sizey = (collide->ysize / 2) + sphere;
							sizez = (collide->zsize / 2) + sphere;

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
			}
		}
		count++;

		if (count > 8)
			break;

	} while (true);

	return 0;
}

// [D] [T]
void TurnHead(PLAYER *lp)
{
	LPPEDESTRIAN pPlayerPed;
	
	pPlayerPed = lp->pPed;

	// [A] handle REDRIVER2 dedicated look back button
	if ((paddCamera & CAMERA_PAD_LOOK_BACK) == CAMERA_PAD_LOOK_BACK || (paddCamera & CAMERA_PAD_LOOK_BACK_DED))
	{
		if (pPlayerPed != NULL)  // look back
			pPlayerPed->head_rot = 0;
	}
	else if (paddCamera & CAMERA_PAD_LOOK_LEFT)
	{
		if (pPlayerPed != NULL)
			pPlayerPed->head_rot = 512;

		if (lp->headTimer > 1)
			lp->headTarget = 0x4000000;
		else
			lp->headTimer++;
	}
	else if (paddCamera & CAMERA_PAD_LOOK_RIGHT)
	{
		if (pPlayerPed != NULL)
			pPlayerPed->head_rot = -512;

		if (lp->headTimer > 1)
			lp->headTarget = -0x4000000;
		else
			lp->headTimer++;
	}
	else
	{
		if (pPlayerPed != NULL)
			pPlayerPed->head_rot = 0;

		lp->headTimer = 0;
		lp->headTarget = 0;
	}

	lp->headPos += (lp->headTarget - lp->headPos) / 2;
}

short gCameraDistance = 1000;
short gCameraMaxDistance = 0;

#ifdef PSX
#define gCameraDefaultScrZ 256
#else
short gCameraDefaultScrZ = 256;
#endif


CAR_DATA *jcam = NULL;
int switch_detail_distance = 10000;

// [D] [T]
void PlaceCameraFollowCar(PLAYER *lp)
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
	int maxCameraDist;

	maxCameraDist = 850;
	carheight = -220;
	camExpandSpeed = 10;
	
	if (lp->cameraCarId >= 0)
	{
		CAR_DATA* camCar;
		int carSpeed;
		camCar = &car_data[lp->cameraCarId];

		car_cos = camCar->ap.carCos;

		if(car_cos)
		{
			int addDist;

			carheight = car_cos->colBox.vy * -3 + 85;

			// [A] default just adds 248, but it's too close for big vehicles
			addDist = MAX(248, car_cos->colBox.vy * 3);

			if (gCameraMaxDistance == 0)
				maxCameraDist = car_cos->colBox.vz * 2 + car_cos->colBox.vy + addDist;
			else
				maxCameraDist = gCameraMaxDistance;

			carSpeed = FIXEDH(camCar->hd.wheel_speed);

			if (ABS(carSpeed) > 9 && (gCameraDistance + 30 <= maxCameraDist))
				camExpandSpeed = 20;
		}
	}

	if (pauseflag == 0)
		TurnHead(lp);

	camera_angle.vx = 25;

	camAngle = lp->cameraAngle - (lp->headPos >> 16);

	if (pauseflag == 0 || EditMode == 2)
	{
		// [A] handle REDRIVER2 dedicated look back button
		if ((paddCamera & CAMERA_PAD_LOOK_BACK) == CAMERA_PAD_LOOK_BACK || (paddCamera & CAMERA_PAD_LOOK_BACK_DED))
		{
			camAngle = baseDir; // look back
		}
		else
		{
			angleDelta = DIFF_ANGLES(lp->cameraAngle, baseDir + gCameraAngle); // (((baseDir + gCameraAngle) - lp->cameraAngle) + 2048U & 0xfff) - 2048;

			lp->cameraAngle += (angleDelta >> 3) & 0xfff;
		}
	}

	lp->cameraPos.vx = basePos[0] + FIXEDH(RSIN(camAngle) * lp->cameraDist);
	lp->cameraPos.vz = basePos[2] + FIXEDH(RCOS(camAngle) * lp->cameraDist);

	lp->cameraPos.vy = basePos[1];
	camPosVy = MapHeight(&lp->cameraPos);
	lp->cameraPos.vy = carheight - basePos[1];

	cammapht = (carheight - camPosVy) - 100 + gCameraOffset.vy;

	if (lp->cameraPos.vy > cammapht)
	{
		int height;
		height = MapHeight((VECTOR*)basePos);

		if (ABS(height - camPosVy) < 900)
		{
			camera_angle.vx = (lp->cameraPos.vy - cammapht >> 1) + 25;
			lp->cameraPos.vy = cammapht;
		}
	}

	jcam = &car_data[CAMERA_COLLIDER_CARID];
	ClearMem((char *)jcam, sizeof(CAR_DATA));

	jcam->controlType = CONTROL_TYPE_CAMERACOLLIDER;

	gCameraDistance = maxCameraDist;

	if (lp->cameraCarId >= 0) 
		jcam->ap.carCos = car_data[lp->cameraCarId].ap.carCos;

	jcam->hd.direction = camAngle & 0xfff;
	
	sdist = maxCameraDist * RSIN(camAngle) + 2048;
	cdist = maxCameraDist * RCOS(camAngle) + 2048;

	jcam->hd.oBox.location.vx = jcam->hd.where.t[0] = basePos[0] + (sdist >> 13);
	jcam->hd.oBox.location.vy = jcam->hd.where.t[1] = -lp->cameraPos.vy;
	jcam->hd.oBox.location.vz = jcam->hd.where.t[2] = basePos[2] + (cdist >> 13);

	CheckScenaryCollisions(jcam);

	lp->cameraDist += camExpandSpeed;

	if (lp->cameraDist > gCameraDistance)
		lp->cameraDist = gCameraDistance;

	lp->cameraPos.vy = -jcam->hd.where.t[1];
	lp->cameraPos.vx = basePos[0] + FIXEDH(lp->cameraDist * RSIN(jcam->hd.direction));
	lp->cameraPos.vz = basePos[2] + FIXEDH(lp->cameraDist * RCOS(jcam->hd.direction));

	if (lp->cameraCarId < 0)
		camera_angle.vy = -(jcam->hd.direction + 2048);
	else
		camera_angle.vy = -ratan2(basePos[0] - lp->cameraPos.vx, basePos[2] - lp->cameraPos.vz) & 0xfff;
	
	camera_angle.vz = 0;

	SetGeomScreen(scr_z = gCameraDefaultScrZ);
	switch_detail_distance = 10000;

	BuildWorldMatrix();
}


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

// [D] [T]
void PlaceCameraInCar(PLAYER *lp, int BumperCam)
{
	VECTOR viewer_position;
	int angle;
	CAR_DATA *cp;

	cp = NULL;

	if (lp->cameraCarId > -1)
		cp = &car_data[lp->cameraCarId];

	viewer_position.vx = 0;
	viewer_position.vy = 0;
	viewer_position.vz = 0;

	TurnHead(lp);

	// [A] handle REDRIVER2 dedicated look back button
	if ((paddCamera & CAMERA_PAD_LOOK_BACK) == CAMERA_PAD_LOOK_BACK || (paddCamera & CAMERA_PAD_LOOK_BACK_DED))
		camera_angle.vy = 2048 - baseDir & 0xfff;
	else
		camera_angle.vy = (lp->headPos >> 16) - baseDir & 0xfff;

	if (cp)
	{
		// build custom matrix using car draw matrix
		InvertMatrix(&cp->hd.drawCarMat, &inv_camera_matrix);

		viewer_position.vy = -40;

		if (!((paddCamera & CAMERA_PAD_LOOK_BACK) == CAMERA_PAD_LOOK_BACK || (paddCamera & CAMERA_PAD_LOOK_BACK_DED)))
		{
			viewer_position.vz -= cp->ap.carCos->colBox.vz - 250;

			// rotate vector on vehicle
			SetRotMatrix(&cp->hd.drawCarMat);
			_MatrixRotate(&viewer_position);

			// rotate head
			_RotMatrixY(&inv_camera_matrix, 2048 + (lp->headPos >> 16));
		}

		MulMatrix0(&aspect, &inv_camera_matrix, &inv_camera_matrix);
		InvertMatrix(&inv_camera_matrix, &camera_matrix);

		face_camera_work.m[0][0] = ONE;
		face_camera_work.m[0][2] = 0;
		face_camera_work.m[2][0] = 0;
		face_camera_work.m[2][2] = ONE;

		RotMatrixY(-(camera_angle.vy & 0xfff), &face_camera_work);
		MulMatrix0(&inv_camera_matrix, &face_camera_work, &face_camera);

		lp->cameraPos.vx = basePos[0] + viewer_position.vx;
		lp->cameraPos.vy = viewer_position.vy - basePos[1];
		lp->cameraPos.vz = basePos[2] + viewer_position.vz;
	}
	else
	{
		camera_angle.vx = -tannerLookAngle.vx;

		// pedestrian camera is much simpler
		BuildWorldMatrix();

		viewer_position.vy += lp->pPed->head_pos - 25;
		//viewer_position.vz += 45;

		angle = -baseDir;

		lp->cameraPos.vx = basePos[0] + FIXEDH(RSIN(angle) * viewer_position.vz);
		lp->cameraPos.vy = viewer_position.vy - basePos[1];
		lp->cameraPos.vz = basePos[2] - FIXEDH(RCOS(angle) * viewer_position.vz);
	}

	SetGeomScreen(scr_z = gCameraDefaultScrZ);

	switch_detail_distance = 10000;
}

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

	if (scr_z > 800)
		scr_z = 800;

	if (scr_z < gCameraDefaultScrZ)
		scr_z = gCameraDefaultScrZ;

	scr_z = old_z;
	return CameraCollisionCheck() == 0;
}

// [D] [T]
void SetBasePos(VECTOR *pVec)
{
	basePos[0] = pVec->vx;
	basePos[1] = pVec->vy;
	basePos[2] = pVec->vz;
}

// [D] [T]
void PlaceCameraAtLocation(PLAYER* lp, int zoom)
{
	int d;
	VECTOR temp;

	d = 0;

	if (tracking_car)
	{
		CalcCameraBasePos(lp);

		temp.vx = basePos[0];
		temp.vy = -basePos[1];
		temp.vz = basePos[2];

		d = PointAtTarget(&lp->cameraPos, &temp, &camera_angle);

		if (d > 16000)
		{
			lp->cameraView = 0;
			return;
		}

		if (zoom == 0)
		{
			scr_z = gCameraDefaultScrZ;
		}
		else
		{
			scr_z = (d >> 4) + gCameraDefaultScrZ;

			if (scr_z > 800)
				scr_z = 800;
		}
	}

	if (scr_z < gCameraDefaultScrZ)
		scr_z = gCameraDefaultScrZ;

	SetGeomScreen(scr_z);
	switch_detail_distance = 10000 + (d >> 1);
	BuildWorldMatrix();
}