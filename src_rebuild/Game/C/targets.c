#include "driver2.h"
#include "targets.h"
#include "camera.h"
#include "main.h"
#include "mission.h"
#include "map.h"
#include "system.h"
#include "debris.h"
#include "draw.h"
#include "dr2roads.h"

#include "ASM/rndrasm.h"

struct TARGET_ARROW_MODEL
{
	SVECTOR* pVerts;
	char* pTris;
	char numTris;
};

SVECTOR targetArrowVerts[] = 
{
	{  -45, -270,  0,  0 },
	{  45,  -270,  0,  0 },
	{  45,  -90,  0,  0 },
	{  90,  -90,  0,  0 },
	{  0,  0,  0,  0 },
	{  -90,  -90,  0,  0 },
	{  -45,  -90,  0,  0 },
	{  -96,  -768,  0,  0 },
	{  96,  -768,  0,  0 },
	{  96,  -216,  0,  0 },
	{  -96,  -216,  0,  0 },
	{  88,  -60,  0,  0 },
	{  36,  -8,  0,  0 },
	{  -36,  -8,  0,  0 },
	{  -88,  -60,  0,  0 },
	{  -88,  -132,  0,  0 },
	{  -36,  -184,  0,  0 },
	{  36,  -184,  0,  0 },
	{  88,  -132,  0,  0 },
	{  177,  -119,  0,  0 },
	{  73,  -15,  0,  0 },
	{  -73,  -15,  0,  0 },
	{  -177,  -119,  0,  0 },
	{  -177,  -265,  0,  0 },
	{  -73,  -369,  0,  0 },
	{  73,  -369,  0,  0 },
	{  177,  -265,  0,  0 },
	{  -48,  -384,  0,  0 },
	{  -48,  -432,  0,  0 },
	{  -96,  -432,  0,  0 },
	{  -96,  -480,  0,  0 },
	{  96,  -480,  0,  0 },
	{  96,  -432,  0,  0 },
	{  48,  -432,  0,  0 },
	{  48,  -384,  0,  0 },
	{  221,  -149,  0,  0 },
	{  91,  -19,  0,  0 },
	{  -91,  -19,  0,  0 },
	{  -221,  -149,  0,  0 },
	{  -221,  -331,  0,  0 },
	{  -91,  -461,  0,  0 },
	{  91,  -461,  0,  0 },
	{  221,  -331,  0,  0 }
};;

char normalTargetArrowTris[] = { 0, 1, 2, 0, 2, 6, 5, 3, 4 };

char loseTailTargetArrowTris[] = { 7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14 };

char windowTargetArrowTris[] = {
	19, 20, 21, 19, 21, 22, 26, 19, 22,
	26, 22, 23, 25, 26, 23, 25, 23, 24,
	27, 28, 34, 28, 33, 34, 29, 30, 31,
	29, 31, 32
};

char maxSpeedTargetArrowTris[] = {
	35, 36, 37, 35, 37, 38, 42, 35, 38,
	42, 38, 39, 41, 42, 39, 41, 39, 40
};

TARGET_ARROW_MODEL targetArrowModel[4] =
{
	{ targetArrowVerts, normalTargetArrowTris, sizeof(normalTargetArrowTris) / 3 },
	{ targetArrowVerts, loseTailTargetArrowTris, sizeof(loseTailTargetArrowTris) / 3 },
	{ targetArrowVerts, windowTargetArrowTris, sizeof(windowTargetArrowTris) / 3 },
	{ targetArrowVerts, maxSpeedTargetArrowTris, sizeof(maxSpeedTargetArrowTris) / 3 }
};

int gDraw3DArrowBlue = 0;

// [D] [T]
void WorldToCameraPositions(VECTOR* pGlobalPositionIn, VECTOR* pCameraPositionOut, int count)
{
	while (count)
	{
		count--;
		pCameraPositionOut->vx = pGlobalPositionIn->vx - camera_position.vx;
		pCameraPositionOut->vy = pGlobalPositionIn->vy - camera_position.vy;
		pCameraPositionOut->vz = pGlobalPositionIn->vz - camera_position.vz;

		Apply_Inv_CameraMatrix(pCameraPositionOut);

		pGlobalPositionIn++;
		pCameraPositionOut++;
	}
}

// [D] [T]
void DrawTargetArrowModel(TARGET_ARROW_MODEL *pTargetArrowModel, VECTOR *pPosition, int shadow, int invert)
{
	u_int numTris;
	VECTOR *cameraPos;

	char *tri_indices;
	POLY_F3 *poly;
	SVECTOR *pVerts;
	VECTOR tempVec;
	SVECTOR temp;
	int z;

	if (PositionVisible(pPosition) == 0)
		return;

	cameraPos = &tempVec;

	if (FrustrumCheck(pPosition, 800) == -1)
		return;

	pVerts = pTargetArrowModel->pVerts;
	WorldToCameraPositions(pPosition, cameraPos, 1);

	gte_SetRotMatrix(&identity);
	gte_SetTransVector(&tempVec);

	numTris = pTargetArrowModel->numTris;
	tri_indices = pTargetArrowModel->pTris;

	while (tri_indices < pTargetArrowModel->pTris + numTris*3)
	{
		poly = (POLY_F3 *)current->primptr;

		if (invert == 0) 
		{
			gte_ldv3(&pVerts[tri_indices[0]], &pVerts[tri_indices[1]], &pVerts[tri_indices[2]]);
		}
		else
		{
			temp.vx = pVerts[tri_indices[0]].vx;
			temp.vy = -pVerts[tri_indices[0]].vy;
			temp.vz = pVerts[tri_indices[0]].vz;

			gte_ldv0(&temp);

			temp.vx = pVerts[tri_indices[1]].vx;
			temp.vy = -pVerts[tri_indices[1]].vy;
			temp.vz = pVerts[tri_indices[1]].vz;

			gte_ldv1(&temp);

			temp.vx = pVerts[tri_indices[2]].vx;
			temp.vy = -pVerts[tri_indices[2]].vy;
			temp.vz = pVerts[tri_indices[2]].vz;

			gte_ldv2(&temp);
		}

		tri_indices += 3;
		gte_rtpt();

		setPolyF3(poly);

		if (gDraw3DArrowBlue == 0) 
		{
			poly->r0 = 255;
			poly->g0 = 0;
		}
		else
		{
			poly->r0 = 0;
			poly->g0 = 255;
		}

		poly->b0 = 0;

		gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);
		gte_stszotz(&z);

		z = z >> 1;

		if (z < 9)
			z = 9;

		addPrim(current->ot + z, poly);

		current->primptr += sizeof(POLY_F3);
	}

	if (shadow != 0) 
		DrawStopZone(pPosition);
}

// [D] [T]
void Draw3DTarget(VECTOR* position, int flags)
{
	int shadow;
	VECTOR pos;

	shadow = (flags & 2);

	// arrow
	if (flags & 0x1)
	{
		pos.vx = position->vx;
		pos.vz = position->vz;
		pos.pad = position->pad;
		pos.vy = position->vy - 300 + (CameraCnt & 0xfU) * 16;

		if (CurrentPlayerView != 1 || GameType != GAME_COPSANDROBBERS)
		{
			DrawTargetArrowModel(&targetArrowModel[0], &pos, shadow, 0);
		}
	}

	// flipped carrow
	if (flags & 0x20)
	{
		pos.vx = position->vx;
		pos.vz = position->vz;
		pos.pad = position->pad;
		pos.vy = position->vy + 900 - (CameraCnt & 0xfU) * 16;

		if (CurrentPlayerView != 1 || GameType != GAME_COPSANDROBBERS)
		{
			DrawTargetArrowModel(&targetArrowModel[0], &pos, shadow, 1);
		}
	}

	// exclamation mark
	if (flags & 0x4)
	{
		pos.vx = position->vx;
		pos.vz = position->vz;
		pos.pad = position->pad;
		pos.vy = position->vy - 300;

		DrawTargetArrowModel(&targetArrowModel[1], &pos, shadow, 0);
	}

	// timer
	if (flags & 8)
	{
		pos.vx = position->vx;
		pos.vz = position->vz;
		pos.pad = position->pad;
		pos.vy = position->vy - 300;

		DrawTargetArrowModel(&targetArrowModel[2], &pos, shadow, 0);
	}

	// stop zone
	if (flags & 0x10)
	{
		pos.vx = position->vx;
		pos.vz = position->vz;
		pos.pad = position->pad;
		pos.vy = position->vy - 300;

		DrawTargetArrowModel(&targetArrowModel[3], &pos, shadow, 0);
	}
}

// [D] [T]
void DrawStopZone(VECTOR *pPosition)
{
	VECTOR* pVector;
	POLY_FT4* pPoly;
	long* pOut;
	SVECTOR temp;
	long p;
	long flag;
	long sz;
	int flash;
	int height;

	VECTOR pStopZonePt[4] = {
		{-256, 0, 256},
		{256, 0, 256},
		{-256, 0, -256},
		{256, 0, -256},
	};

	flash = -CameraCnt % 16;

	pVector = pStopZonePt;

	pPoly = (POLY_FT4*)current->primptr;
	pOut = (long*)&pPoly->x0;

	gte_SetRotMatrix(&identity);
	gte_SetTransVector(&dummy);

	setPolyFT4(pPoly);
	setSemiTrans(pPoly, 1);

	height = MapHeight(pPosition);

	while (pVector < &pStopZonePt[4])
	{
		pVector->vy = pPosition->vy;

		pVector->vx = (pVector->vx * flash >> 4) + pPosition->vx;
		pVector->vz = (pVector->vz * flash >> 4) + pPosition->vz;
		pVector->vy = -camera_position.vy - height;

		pVector->vx = pVector->vx - camera_position.vx;
		pVector->vz = pVector->vz - camera_position.vz;

		Apply_Inv_CameraMatrix(pVector);

		temp.vx = pVector->vx;
		temp.vy = pVector->vy;
		temp.vz = pVector->vz;

		RotTransPers(&temp, pOut, &p, &flag);

		if (pOut == (long*)&pPoly->x0) 
			pOut = (long*)&pPoly->x1;
		else if (pOut == (long*)&pPoly->x1)
			pOut = (long*)&pPoly->x2;
		else
			pOut = (long*)&pPoly->x3;

		pVector++;
	}

	gte_stsz(&sz);

	pPoly->r0 = 64;
	pPoly->g0 = 64;
	pPoly->b0 = 64;

	*(ushort*)&pPoly->u0 = *(ushort*)&light_texture.coords.u0;
	*(ushort*)&pPoly->u1 = *(ushort*)&light_texture.coords.u1;
	*(ushort*)&pPoly->u2 = *(ushort*)&light_texture.coords.u2;
	*(ushort*)&pPoly->u3 = *(ushort*)&light_texture.coords.u3;

	if (gTimeOfDay == 3)
		pPoly->tpage = light_texture.tpageid | 0x20;
	else
		pPoly->tpage = light_texture.tpageid | 0x40;

	pPoly->clut = light_texture.clutid;

	addPrim(current->ot + (sz + 400 >> 3), pPoly);

	current->primptr += sizeof(POLY_FT4);
}






