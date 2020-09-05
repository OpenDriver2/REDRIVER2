#include "DRIVER2.H"
#include "TARGETS.H"
#include "CAMERA.H"
#include "MAIN.H"
#include "MISSION.H"
#include "MAP.H"
#include "SYSTEM.H"
#include "DEBRIS.H"
#include "DRAW.H"
#include "DR2ROADS.H"

#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"


SVECTOR targetArrowVerts[43] =
{
	{ 65491, 65266, 0, 0 },
	{ 45, 65266, 0, 0 },
	{ 45, 65446, 0, 0 },
	{ 90, 65446, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 65446, 65446, 0, 0 },
	{ 65491, 65446, 0, 0 },
	{ 65440, 64768, 0, 0 },
	{ 96, 64768, 0, 0 },
	{ 96, 65320, 0, 0 },
	{ 65440, 65320, 0, 0 },
	{ 88, 65476, 0, 0 },
	{ 36, 65528, 0, 0 },
	{ 65500, 65528, 0, 0 },
	{ 65448, 65476, 0, 0 },
	{ 65448, 65404, 0, 0 },
	{ 65500, 65352, 0, 0 },
	{ 36, 65352, 0, 0 },
	{ 88, 65404, 0, 0 },
	{ 177, 65417, 0, 0 },
	{ 73, 65521, 0, 0 },
	{ 65463, 65521, 0, 0 },
	{ 65359, 65417, 0, 0 },
	{ 65359, 65271, 0, 0 },
	{ 65463, 65167, 0, 0 },
	{ 73, 65167, 0, 0 },
	{ 177, 65271, 0, 0 },
	{ 65488, 65152, 0, 0 },
	{ 65488, 65104, 0, 0 },
	{ 65440, 65104, 0, 0 },
	{ 65440, 65056, 0, 0 },
	{ 96, 65056, 0, 0 },
	{ 96, 65104, 0, 0 },
	{ 48, 65104, 0, 0 },
	{ 48, 65152, 0, 0 },
	{ 221, 65387, 0, 0 },
	{ 91, 65517, 0, 0 },
	{ 65445, 65517, 0, 0 },
	{ 65315, 65387, 0, 0 },
	{ 65315, 65205, 0, 0 },
	{ 65445, 65075, 0, 0 },
	{ 91, 65075, 0, 0 },
	{ 221, 65205, 0, 0 }
};

char normalTargetArrowTris[] = { 0, 1, 2, 0, 2, 6, 5, 3, 4 };

char loseTailTargetArrowTris[] = { 7, 8, 9, 7, 9, 0xA, 0xB, 0xC, 0xD, 0xB, 0xD, 0xE };

char windowTargetArrowTris[] = {
	0x13, 0x14, 0x15, 0x13, 0x15, 0x16, 0x1A, 0x13, 0x16,
	0x1A, 0x16, 0x17, 0x19, 0x1A, 0x17, 0x19, 0x17, 0x18,
	0x1B, 0x1C, 0x22, 0x1C, 0x21, 0x22, 0x1D, 0x1E, 0x1F,
	0x1D, 0x1F, 0x20
};

char maxSpeedTargetArrowTris[] = {
	0x23, 0x24, 0x25, 0x23, 0x25, 0x26, 0x2A, 0x23, 0x26,
	0x2A, 0x26, 0x27, 0x29, 0x2A, 0x27, 0x29, 0x27, 0x28
};

TARGET_ARROW_MODEL targetArrowModel[4] =
{
	{ targetArrowVerts, normalTargetArrowTris, sizeof(normalTargetArrowTris) / 3 },
	{ targetArrowVerts, loseTailTargetArrowTris, sizeof(loseTailTargetArrowTris) / 3 },
	{ targetArrowVerts, windowTargetArrowTris, sizeof(windowTargetArrowTris) / 3 },
	{ targetArrowVerts, maxSpeedTargetArrowTris, sizeof(maxSpeedTargetArrowTris) / 3 }
};

int gDraw3DArrowBlue = 0;


// decompiled code
// original method signature: 
// void /*$ra*/ Draw3DTarget(struct VECTOR *position /*$s0*/, int flags /*$s2*/)
 // line 213, offset 0x0007fb44
	/* begin block 1 */
		// Start line: 214
		// Start offset: 0x0007FB44
		// Variables:
	// 		struct VECTOR pos; // stack offset -32
	// 		int shadow; // $s1
	/* end block 1 */
	// End offset: 0x0007FD48
	// End Line: 262

	/* begin block 2 */
		// Start line: 426
	/* end block 2 */
	// End Line: 427

// [D]
void Draw3DTarget(VECTOR *position, int flags)
{
	uint shadow;
	VECTOR local_20;

	shadow = (uint)((flags & 2U) != 0);
	if ((flags & 1U) != 0)
	{
		local_20.vx = position->vx;
		local_20.vz = position->vz;
		local_20.pad = position->pad;
		local_20.vy = position->vy + -300 + (CameraCnt & 0xfU) * 0x10;
		if ((CurrentPlayerView != 1) || (GameType != GAME_COPSANDROBBERS)) 
		{
			DrawTargetArrowModel(&targetArrowModel[0], &local_20, shadow, 0);
		}
	}
	else if ((flags & 0x20U) != 0)
	{
		local_20.vx = position->vx;
		local_20.vz = position->vz;
		local_20.pad = position->pad;
		local_20.vy = position->vy + 900 + (CameraCnt & 0xfU) * -0x10;
		if ((CurrentPlayerView != 1) || (GameType != GAME_COPSANDROBBERS)) 
		{
			DrawTargetArrowModel(&targetArrowModel[0], &local_20, shadow, 1);
		}
	}
	else if ((flags & 4U) != 0)
	{
		local_20.vx = position->vx;
		local_20.vz = position->vz;
		local_20.pad = position->pad;
		local_20.vy = position->vy + -300;

		DrawTargetArrowModel(&targetArrowModel[1], &local_20, shadow, 0);
	}
	else if ((flags & 8U) != 0)
	{
		local_20.vx = position->vx;
		local_20.vz = position->vz;
		local_20.pad = position->pad;
		local_20.vy = position->vy + -300;

		DrawTargetArrowModel(&targetArrowModel[2], &local_20, shadow, 0);
	}
	else  if ((flags & 0x10U) != 0) {
		local_20.vx = position->vx;
		local_20.vz = position->vz;
		local_20.pad = position->pad;
		local_20.vy = position->vy + -300;

		DrawTargetArrowModel(&targetArrowModel[3], &local_20, shadow, 0);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTargetArrowModel(struct TARGET_ARROW_MODEL *pTargetArrowModel /*$s1*/, struct VECTOR *pPosition /*$s2*/, int shadow /*$s4*/, int invert /*$s3*/)
 // line 267, offset 0x0007fd48
	/* begin block 1 */
		// Start line: 268
		// Start offset: 0x0007FD48

		/* begin block 1.1 */
			// Start line: 271
			// Start offset: 0x0007FD9C
			// Variables:
		// 		struct VECTOR tempVec; // stack offset -56
		// 		struct SVECTOR *pVerts; // $s0
		// 		struct SVECTOR temp; // stack offset -40
		// 		char *pVertIndex; // $a3

			/* begin block 1.1.1 */
				// Start line: 283
				// Start offset: 0x0007FE2C
				// Variables:
			// 		struct POLY_F3 *poly; // $t0
			// 		int z; // stack offset -32
			/* end block 1.1.1 */
			// End offset: 0x00080044
			// End Line: 323
		/* end block 1.1 */
		// End offset: 0x000800D8
		// End Line: 329
	/* end block 1 */
	// End offset: 0x000800F8
	// End Line: 330

	/* begin block 2 */
		// Start line: 555
	/* end block 2 */
	// End Line: 556

	/* begin block 3 */
		// Start line: 561
	/* end block 3 */
	// End Line: 562

// [D]
void DrawTargetArrowModel(TARGET_ARROW_MODEL *pTargetArrowModel, VECTOR *pPosition, int shadow, int invert)
{
	ushort uVar1;
	uint uVar3;
	int iVar5;
	SVECTOR *pSVar6;
	VECTOR *pVVar7;
	uint numTris;
	VECTOR *cameraPos;

	char *tri_indices;
	POLY_F3 *poly;
	SVECTOR *pSVar10;
	VECTOR tempVec;
	SVECTOR temp;
	int z;

	if (PositionVisible(pPosition) != 0)
	{
		cameraPos = &tempVec;

		if (FrustrumCheck(pPosition, 800) != -1)
		{
			pSVar10 = pTargetArrowModel->pVerts;
			WorldToCameraPositions(pPosition, cameraPos, 1);

			gte_SetRotMatrix(&aspect);
			gte_SetTransVector(&tempVec);

			pVVar7 = &tempVec;

			numTris = pTargetArrowModel->numTris;
			tri_indices = pTargetArrowModel->pTris;

			if (tri_indices < tri_indices + numTris * 3) 
			{
				do {
					poly = (POLY_F3 *)current->primptr;

					if (invert == 0) 
					{
						gte_ldv3(&pSVar10[tri_indices[0]], &pSVar10[tri_indices[1]], &pSVar10[tri_indices[2]]);
					}
					else
					{
						temp.vx = pSVar10[*tri_indices].vx;
						temp.vy = -pSVar10[*tri_indices].vy;
						temp.vz = pSVar10[*tri_indices].vz;

						gte_ldv0(&temp);

						temp.vx = pSVar10[*tri_indices + 1].vx;
						temp.vy = -pSVar10[*tri_indices + 1].vy;
						temp.vz = pSVar10[*tri_indices + 1].vz;

						gte_ldv1(&temp);

						temp.vx = pSVar10[*tri_indices + 2].vx;
						temp.vy = -pSVar10[*tri_indices + 2].vy;
						temp.vz = pSVar10[*tri_indices + 2].vz;

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
					else {
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
				} while (tri_indices < pTargetArrowModel->pTris + numTris*3);
			}

			if (shadow != 0) 
				DrawStopZone(pPosition);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawStopZone(struct VECTOR *pPosition /*$s5*/)
 // line 412, offset 0x000800f8
	/* begin block 1 */
		// Start line: 413
		// Start offset: 0x000800F8
		// Variables:
	// 		struct VECTOR *pVector; // $s0
	// 		struct VECTOR pStopZonePt[4]; // stack offset -128
	// 		struct POLY_FT4 *pPoly; // $s1
	// 		long *pOut; // $s2
	// 		long sz; // stack offset -48

		/* begin block 1.1 */
			// Start line: 430
			// Start offset: 0x000801FC
			// Variables:
		// 		struct SVECTOR temp; // stack offset -64
		// 		long p; // stack offset -56
		// 		long flag; // stack offset -52
		/* end block 1.1 */
		// End offset: 0x0008030C
		// End Line: 465
	/* end block 1 */
	// End offset: 0x0008047C
	// End Line: 489

	/* begin block 2 */
		// Start line: 890
	/* end block 2 */
	// End Line: 891

	/* begin block 3 */
		// Start line: 899
	/* end block 3 */
	// End Line: 900

// [D]
void DrawStopZone(VECTOR *pPosition)
{
	int iVar4;
	VECTOR* pVector;
	int iVar6;
	POLY_FT4* pPoly;
	long* pOut;
	SVECTOR temp;
	long p;
	long flag;
	long sz;

	VECTOR pStopZonePt[4] = {
		{-500, 0, 500},
		{500, 0, 500},
		{-500, 0, -500},
		{500, 0, -500},
	};

	pVector = pStopZonePt;

	pPoly = (POLY_FT4*)current->primptr;
	pOut = (long*)&pPoly->x0;

	gte_SetRotMatrix(&aspect);
	gte_SetTransVector(&dummy);

	setPolyFT4(pPoly);
	setSemiTrans(pPoly, 1);

	while (pVector < &pStopZonePt[4])
	{
		iVar6 = -CameraCnt;
		iVar4 = iVar6;

		iVar6 = iVar6 + (iVar4 >> 4) * -0x10;

		iVar4 = pVector->vx * iVar6;
		iVar6 = pVector->vz * iVar6;

		pVector->vx = iVar4 >> 4;
		pVector->vy = pPosition->vy;

		pVector->vx = (iVar4 >> 4) + pPosition->vx;
		pVector->vz = (iVar6 >> 4) + pPosition->vz;
		pVector->vy = -camera_position.vy - MapHeight(pVector);

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

		pVector = pVector + 1;
	}

	gte_stsz(&sz);

	pPoly->r0 = 64;
	pPoly->g0 = 64;
	pPoly->b0 = 64;

	pPoly->u0 = light_texture.coords.u0;
	pPoly->v0 = light_texture.coords.v0;
	pPoly->u1 = light_texture.coords.u1;
	pPoly->v1 = light_texture.coords.v1;
	pPoly->u2 = light_texture.coords.u2;
	pPoly->v2 = light_texture.coords.v2;
	pPoly->u3 = light_texture.coords.u3;
	pPoly->v3 = light_texture.coords.v3;

	if (gTimeOfDay == 3)
		pPoly->tpage = light_texture.tpageid | 0x20;
	else
		pPoly->tpage = light_texture.tpageid | 0x40;

	pPoly->clut = light_texture.clutid;

	addPrim(current->ot + (sz >> 4) + 0x200, pPoly);

	current->primptr += sizeof(POLY_FT4);
}



// decompiled code
// original method signature: 
// void /*$ra*/ WorldToCameraPositions(struct VECTOR *pGlobalPositionIn /*$s1*/, struct VECTOR *pCameraPositionOut /*$s0*/, int count /*$s2*/)
 // line 496, offset 0x0008047c
	/* begin block 1 */
		// Start line: 497
		// Start offset: 0x0008047C

		/* begin block 1.1 */
			// Start line: 500
			// Start offset: 0x000804B8
			// Variables:
		// 		struct VECTOR temp; // stack offset -48
		/* end block 1.1 */
		// End offset: 0x000804B8
		// End Line: 502
	/* end block 1 */
	// End offset: 0x00080528
	// End Line: 511

	/* begin block 2 */
		// Start line: 1144
	/* end block 2 */
	// End Line: 1145

	/* begin block 3 */
		// Start line: 1152
	/* end block 3 */
	// End Line: 1153

// [D]
void WorldToCameraPositions(VECTOR *pGlobalPositionIn, VECTOR *pCameraPositionOut, int count)
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





