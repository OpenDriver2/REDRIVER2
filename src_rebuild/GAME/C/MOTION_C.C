#include "DRIVER2.H"
#include "MOTION_C.H"
#include "PEDEST.H"
#include "SYSTEM.H"
#include "STRINGS.H"
#include "MISSION.H"
#include "TEXTURE.H"
#include "OVERMAP.H"
#include "CAMERA.H"
#include "SHADOW.H"
#include "DEBRIS.H"
#include "DRAW.H"
#include "DR2ROADS.H"
#include "SKY.H"
#include "PLAYERS.H"
#include "MAIN.H"
#include "MOTION_C.H"
#include "CONVERT.H"

#include "INLINE_C.H"


LIMBS lRoutes[5][8] = {
	{ROOT, LOWERBACK, HIPS, LHIP, LKNEE, LFOOT, LTOE, ROOT},
	{HIPS, RHIP, RKNEE, RFOOT, RTOE, ROOT, ROOT, ROOT},
	{LOWERBACK, JOINT_1, LSHOULDER, LELBOW, LHAND, LFINGERS, ROOT, ROOT},
	{JOINT_1, RSHOULDER, RELBOW, RHAND, RFINGERS, ROOT, ROOT, ROOT},
	{JOINT_1, NECK, HEAD, ROOT, ROOT, ROOT, ROOT, ROOT},
};

PED_DATA MainPed[23] =
{
	{ 0, 68u, &chest1_texture, CHEST_PAL },
	{ 1, 68u, &chest1_texture, CHEST_PAL },
	{ 17, 36u, &chest1_texture, CHEST_PAL },
	{ 6, 68u, &forearm1_texture, ARM_PAL },
	{ 8, 68u, &head1_texture, NO_PAL },
	{ 6, 68u, &arm1_texture, CHEST_PAL },
	{ 8, 36u, &arm1_texture, CHEST_PAL },
	{ 7, 68u, &forearm1_texture, ARM_PAL },
	{ 3, 244u, &forearm1_texture, ARM_PAL },
	{ 6, 68u, &arm1_texture, CHEST_PAL },
	{ 8, 36u, &arm1_texture, CHEST_PAL },
	{ 7, 68u, &forearm1_texture, ARM_PAL },
	{ 3, 244u, &forearm1_texture, ARM_PAL },
	{ 1, 68u, &jeans_texture, NO_PAL },
	{ 6, 68u, &jeans_texture, NO_PAL },
	{ 13, 100u, &jeans_texture, JEANS_PAL },
	{ 11, 244u, &jeans_texture, JEANS_PAL },
	{ 6, 63u, &chest1_texture, JEANS_PAL },
	{ 6, 68u, &arm1_texture, NO_PAL },
	{ 13, 100u, &jeans_texture, JEANS_PAL },
	{ 11, 244u, &jeans_texture, JEANS_PAL },
	{ 6, 63u, &chest1_texture, JEANS_PAL },
	{ 2, 68u, &jeans_texture, JEANS_PAL }
};


// FIXME: could be incorrect
BONE Skel[23] =
{
	{
		ROOT,
		NULL,
		1,
		{ &Skel[LOWERBACK], &Skel[HIPS], NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		NULL
	},
	{
		LOWERBACK,
		&Skel[ROOT],
		3,
		{ &Skel[JOINT_1], &Skel[LHIP], &Skel[RHIP] },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		NULL
	},
	{
		JOINT_1,
		&Skel[LOWERBACK],
		3,
		{ &Skel[NECK], &Skel[LSHOULDER], &Skel[RSHOULDER] },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[0]
	},
	{
		NECK,
		&Skel[JOINT_1],
		1,
		{ &Skel[HEAD], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[14]
	},
	{
		HEAD,
		&Skel[NECK],
		0,
		{ NULL, NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[1]
	},
	{
		LSHOULDER,
		&Skel[JOINT_1],
		1,
		{ &Skel[LELBOW], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		NULL
	},
	{
		LELBOW,
		&Skel[LSHOULDER],
		1,
		{ &Skel[LHAND], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[8]
	},
	{
		LHAND,
		&Skel[LELBOW],
		1,
		{ &Skel[LFINGERS], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[9]
	},
	{
		LFINGERS,
		&Skel[LHAND],
		0,
		{ NULL, NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[10]
	},
	{
		RSHOULDER,
		&Skel[JOINT_1],
		1,
		{ &Skel[RELBOW], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		NULL
	},
	{
		RELBOW,
		&Skel[RSHOULDER],
		1,
		{ &Skel[RHAND], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[2]
	},
	{
		RHAND,
		&Skel[RELBOW],
		1,
		{ &Skel[RFINGERS], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[3]
	},
	{
		RFINGERS,
		&Skel[RHAND],
		0,
		{ NULL, NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[4]
	},
	{
		HIPS,
		&Skel[0],
		0,
		{ &Skel[RHIP], &Skel[LHIP], NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		NULL
	},
	{
		LHIP,
		&Skel[HIPS],
		1,
		{ &Skel[LKNEE], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[15]
	},
	{
		LKNEE,
		&Skel[LHIP],
		1,
		{ &Skel[LFOOT], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[11]
	},
	{
		LFOOT,
		&Skel[LKNEE],
		1,
		{ &Skel[LTOE], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[12]
	},
	{
		LTOE,
		&Skel[LFOOT],
		0,
		{ NULL, NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[13]
	},
	{
		RHIP,
		&Skel[HIPS],
		1,
		{ &Skel[RKNEE], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		NULL
	},
	{
		RKNEE,
		&Skel[RHIP],
		1,
		{ &Skel[RFOOT], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[5]
	},
	{
		RFOOT,
		&Skel[RKNEE],
		1,
		{ &Skel[RTOE], NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[6]
	},
	{
		RTOE,
		&Skel[RFOOT],
		0,
		{ NULL, NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		&pmTannerModels[7]
	},
	{
		JOINT,
		&Skel[LOWERBACK],
		0,
		{ NULL, NULL, NULL },
		NULL,
		NULL,
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		NULL
	}
};

int boneIdvals[15] = { 2, 3, 4, 6, 7, 8, 0xA, 0xB, 0xC, 0xF, 0x10, 0x11, 0x13, 0x14, 0x15 };

TEXTURE_DETAILS jeans_texture;
TEXTURE_DETAILS arm1_texture;
TEXTURE_DETAILS forearm1_texture;
TEXTURE_DETAILS chest1_texture;
TEXTURE_DETAILS head1_texture;

MODEL* gPed1HeadModelPtr;
MODEL* gPed2HeadModelPtr;
MODEL* gPed3HeadModelPtr;
MODEL* gPed4HeadModelPtr;

char* MotionCaptureData[24];	// [A] actually, pointers
int ThisMotion;

int cTannerVNumbers[24];
SVECTOR vTannerList[210];

int cJerichoVNumbers[7];
SVECTOR vJerichoList[102];

int vStored = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ ProcessMotionLump(char *lump_ptr /*$a0*/, int lump_size /*$s0*/)
 // line 853, offset 0x00069a38
	/* begin block 1 */
		// Start line: 5200
	/* end block 1 */
	// End Line: 5201

	/* begin block 2 */
		// Start line: 1706
	/* end block 2 */
	// End Line: 1707

	/* begin block 3 */
		// Start line: 5202
	/* end block 3 */
	// End Line: 5203
// [D]
void ProcessMotionLump(char *lump_ptr, int lump_size)
{
	if (ThisMotion < 24) 
	{
		int size = (lump_size + 3U & 0xfffffffc);

		MALLOC_BEGIN();
		MotionCaptureData[ThisMotion] = D_MALLOC(size);
		MALLOC_END();

		memcpy(MotionCaptureData[ThisMotion], lump_ptr, lump_size);

		ThisMotion++;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupPedMotionData(struct PEDESTRIAN *pPed /*$a0*/)
 // line 944, offset 0x00069ab8
	/* begin block 1 */
		// Start line: 5388
	/* end block 1 */
	// End Line: 5389

	/* begin block 2 */
		// Start line: 5389
	/* end block 2 */
	// End Line: 5390

// [D]
void SetupPedMotionData(PEDESTRIAN *pPed)
{
	pPed->motion = MotionCaptureData[pPed->type];
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupPedestrian(struct PEDESTRIAN *pedptr /*$a0*/)
 // line 955, offset 0x00069b6c
	/* begin block 1 */
		// Start line: 2236
	/* end block 1 */
	// End Line: 2237

	/* begin block 2 */
		// Start line: 1910
	/* end block 2 */
	// End Line: 1911

	/* begin block 3 */
		// Start line: 6507
	/* end block 3 */
	// End Line: 6508

	/* begin block 4 */
		// Start line: 6512
	/* end block 4 */
	// End Line: 6513

// [D]
void SetupPedestrian(PEDESTRIAN *pedptr)
{
	pedptr->velocity.vy = 10;
	pedptr->speed = 10;

	pedptr->dir.vx = 0;
	pedptr->dir.vz = 0;

	pedptr->frame1 = 0;
	pedptr->motion = MotionCaptureData[pedptr->type];
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawBodySprite(int boneId /*$s1*/, long v1 /*$a1*/, long v2 /*$a2*/, int sz /*$s7*/, int sy /*stack 16*/)
 // line 978, offset 0x0006520c
	/* begin block 1 */
		// Start line: 979
		// Start offset: 0x0006520C
		// Variables:
	// 		struct TEXTURE_DETAILS *body_texture; // $s2
	// 		int x0; // $s5
	// 		int x1; // $s6
	// 		int y0; // $fp
	// 		int y1; // stack offset -48
	// 		int dx1; // $s4
	// 		int dy1; // $s3
	// 		int z; // $a3
	// 		int z2; // $a3
	// 		int dx2; // $t5
	// 		int dy2; // $t3
	// 		int width; // $t0
	// 		int sort_fix; // $a3
	// 		int angle; // $t3
	// 		int c; // $t0
	// 		int s; // $a2
	// 		int clut; // $a2
	// 		int tpage; // $t0
	// 		struct POLY_FT4 *prims; // $t2
	// 		int z1; // stack offset -44
	// 		int pal; // $v1

		/* begin block 1.1 */
			// Start line: 1103
			// Start offset: 0x000655B0
			// Variables:
		// 		int tp; // $v1
		/* end block 1.1 */
		// End offset: 0x0006564C
		// End Line: 1133
	/* end block 1 */
	// End offset: 0x0006594C
	// End Line: 1209

	/* begin block 2 */
		// Start line: 1956
	/* end block 2 */
	// End Line: 1957

	/* begin block 3 */
		// Start line: 1974
	/* end block 3 */
	// End Line: 1975

int bDoingShadow = 0;
int gCurrentZ;
//PEDESTRIAN *pDrawingPed = NULL;

// [D] [A] changed to VERTTYPE
void DrawBodySprite(PEDESTRIAN *pDrawingPed, int boneId, VERTTYPE v1[2], VERTTYPE v2[2], int sz, int sy)
{
#if 0
	// debug code
	{
		LINE_F2* line = (LINE_F2*)current->primptr;
		setLineF2(line);
		setSemiTrans(line, 1);

		line->x0 = v1[0];
		line->y0 = v1[1];
		line->x1 = v2[0];
		line->y1 = v2[1];

		line->r0 = 255;
		line->g0 = 0;
		line->b0 = 0;

		addPrim(current->ot + 2, line);
		current->primptr += sizeof(LINE_F2);
	}
#endif

	int clut;
	long lVar2;
	char bVar3;
	int uVar4;
	int iVar5;
	int width;
	int iVar7;
	POLY_FT4 *prims;
	int iVar8;
	int iVar9;
	LIMBS bone;
	TEXTURE_DETAILS *body_texture;
	int x;
	int y;
	int iVar11;
	int tpage;
	int pal;
	int iVar13;
	int y1;
	int z1;

	x = v1[0] - v2[0];
	y = v1[1] - v2[1];

	bone = (LIMBS)(boneId & 0x7f);

	body_texture = MainPed[bone].ptd;
	lVar2 = ratan2(y, x);

	if (bDoingShadow == 0)
	iVar5 = gCurrentZ + (scr_z / 2);
	else
	iVar5 = sz + (scr_z / 2);

	iVar13 = (scr_z * 4096) / iVar5;

	if (bone == JOINT_1)
	iVar13 = iVar13 + ((int)((uint)*(ushort *)((int)rcossin_tbl + (((int)(pDrawingPed->dir).vy + (int)camera_angle.vy) * 8 & 0x3ff8U) + 2) << 0x10) >> 0x16);

	if (pDrawingPed->type == PED_ACTION_JUMP)
	{
		width = MainPed[bone].cWidth + 4;
	}
	else if (bDoingShadow == 0)
	{
		if ((pDrawingPed->flags & 0x8000U) == 0)
		{
			if ((pDrawingPed->flags & 0x4000U) == 0)
				width = MainPed[bone].cWidth + 3;
			else
				width = MainPed[bone].cWidth + 8;
		}
		else
		{
			width = MainPed[bone].cWidth - 3;
		}
	}
	else
	{
		width = MainPed[bone].cWidth;
	}

	iVar5 = FIXEDH(iVar13 * rcossin_tbl[(-lVar2 & 0xfffU) * 2] * 2 * (width & 0x3f));
	iVar7 = FIXEDH(iVar13 * rcossin_tbl[(-lVar2 & 0xfffU) * 2 + 1] * 2 * (width & 0x3f));

	bVar3 = MainPed[bone].cAdj & 0xf;
	iVar9 = y >> bVar3;
	iVar8 = x >> bVar3;

	if ((bone == RKNEE || bone == LKNEE) && pDrawingPed->type != PED_ACTION_JUMP && bDoingShadow == 0)
	{
		y = -y >> 3;
		x = -x >> 3;
	}
	else
	{
		uVar4 = MainPed[bone].cAdj >> 4;
		y = y >> uVar4;
		x = x >> uVar4;
	}

	prims = (POLY_FT4 *)current->primptr;
	setPolyFT4(prims);

	prims->x0 = v1[0] + FIXEDH(iVar5) + iVar8;
	prims->y0 = v1[1] + FIXEDH(iVar7) + iVar9;

	prims->x1 = (v1[0] - FIXEDH(iVar5)) + iVar8;
	prims->y1 = (v1[1] - FIXEDH(iVar7)) + iVar9;

	prims->x2 = (v2[0] + FIXEDH(iVar5)) - x;
	prims->y2 = (v2[1] + FIXEDH(iVar7)) - y;

	prims->x3 = (v2[0] - FIXEDH(iVar5)) - x;
	prims->y3 = (v2[1] - FIXEDH(iVar7)) - y;

	if (bDoingShadow == 0)
	{
		tpage = body_texture->tpageid;
		clut = body_texture->clutid;

		if (MainPed[bone].texPal != NO_PAL)
		{
			pal = MainPed[bone].texPal == JEANS_PAL ? (pDrawingPed->pallet >> 4) : (pDrawingPed->pallet & 0xf);

			if (pal != 0)
				clut = civ_clut[0][body_texture->texture_number][pal];
		}
	}
	else
	{
		tpage = gShadowTexturePage;
		clut = texture_cluts[gShadowTexturePage][gShadowTextureNum];
	}

	prims->tpage = tpage;
	prims->clut = clut;

	if (bDoingShadow == 0)
	{
		if (bone == 4)
		{
			x = (camera_angle.vy + pDrawingPed->dir.vy & 0xfffU) >> 7;

			prims->u0 = body_texture->coords.u0 + x;
			prims->v0 = body_texture->coords.v0;

			prims->u1 = body_texture->coords.u1 + x;
			prims->v1 = body_texture->coords.v1;

			prims->u2 = body_texture->coords.u2 + x;
			prims->v2 = body_texture->coords.v2;

			prims->u3 = body_texture->coords.u3 + x;
			prims->v3 = body_texture->coords.v3;
		}
		else if (bone == 2)
		{
			prims->u0 = body_texture->coords.u0;
			prims->v0 = body_texture->coords.v0;

			prims->u1 = body_texture->coords.u1;
			prims->v1 = body_texture->coords.v1;

			prims->u2 = body_texture->coords.u2;
			prims->v2 = body_texture->coords.v2;

			prims->u3 = body_texture->coords.u3;
			prims->v3 = body_texture->coords.v3;
		}
		else
		{
			prims->u0 = body_texture->coords.u2;
			prims->v0 = body_texture->coords.v2;

			prims->u1 = body_texture->coords.u3;
			prims->v1 = body_texture->coords.v3;

			prims->u2 = body_texture->coords.u0;
			prims->v2 = body_texture->coords.v0;

			prims->u3 = body_texture->coords.u1;
			prims->v3 = body_texture->coords.v1;
		}
	}
	else
	{
		prims->u0 = shadowuv.u0;
		prims->v0 = shadowuv.v0;

		prims->u1 = shadowuv.u1;
		prims->v1 = shadowuv.v1;

		prims->u2 = shadowuv.u2;
		prims->v2 = shadowuv.v2;

		prims->u3 = shadowuv.u3;
		prims->v3 = shadowuv.v3;
	}

	if (gNight == 1)
	{
		prims->r0 = 64;
		prims->g0 = 64;
		prims->b0 = 64;
	}
	else
	{
		prims->r0 = (combointensity >> 0x10) & 0xFF;
		prims->g0 = (combointensity >> 8) & 0xFF;
		prims->b0 = combointensity & 0xFF;
	}

	if (bDoingShadow == 0)
	{
		x = sz + sy >> 4;
		addPrim(current->ot + x + ((int)width >> 6), prims);
	}
	else
	{
		addPrim(current->ot + 0x107f, prims);
	}

	current->primptr += sizeof(POLY_FT4);
}



// decompiled code
// original method signature: 
// void /*$ra*/ StoreVertexLists()
 // line 1289, offset 0x0006594c
	/* begin block 1 */
		// Start line: 1291
		// Start offset: 0x0006594C
		// Variables:
	// 		int i; // $t1
	// 		int j; // $a3
	// 		int numVerts; // $t3
	// 		struct MODEL *pModel; // $t0
	// 		struct SVECTOR *pVerts; // $a2
	// 		int counter; // $t4
	// 		struct BONE *pBone; // $a0
	/* end block 1 */
	// End offset: 0x00065AD8
	// End Line: 1346

	/* begin block 2 */
		// Start line: 2632
	/* end block 2 */
	// End Line: 2633

	/* begin block 3 */
		// Start line: 2713
	/* end block 3 */
	// End Line: 2714

	/* begin block 4 */
		// Start line: 2714
	/* end block 4 */
	// End Line: 2715

	/* begin block 5 */
		// Start line: 2720
	/* end block 5 */
	// End Line: 2721

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void StoreVertexLists(void)
{
	short *psVar1;
	BONE *pBVar2;
	SVECTOR *pSVar3;
	SVECTOR *local_a2_76;
	SVECTOR *local_a2_308;
	int iVar4;
	MODEL *pMVar5;
	MODEL *local_t0_256;
	int iVar6;
	int iVar7;
	int iVar8;

	iVar7 = 0;
	iVar8 = 0;
	pBVar2 = Skel;
	iVar6 = 21;

	do {
		iVar4 = 0;

		if (pBVar2->pModel == NULL)
		{
			cTannerVNumbers[pBVar2->id] = -1;
		}
		else if(*pBVar2->pModel != NULL)
		{
			pMVar5 = *pBVar2->pModel;
			local_a2_76 = (SVECTOR *)pMVar5->vertices;
			cTannerVNumbers[pBVar2->id] = iVar8;

			if (pMVar5->num_vertices != 0)
			{
				pSVar3 = vTannerList + iVar7;
				do {
					iVar8++;
					iVar4++;
					iVar7++;

					pSVar3->vx = local_a2_76->vx;
					pSVar3->vy = local_a2_76->vy;
					pSVar3->vz = local_a2_76->vz;

					local_a2_76++;
					pSVar3++;
				} while (iVar4 < pMVar5->num_vertices);
			}
		}
		pBVar2 = pBVar2 + 1;
		iVar6 = iVar6 + -1;
	} while (-1 < iVar6);

	iVar4 = 0;
	iVar8 = 0;
	iVar7 = 0;
	iVar6 = 0;

	do {
		local_t0_256 = pmJerichoModels[iVar7];

		
		if (local_t0_256 != NULL)
		{
			local_a2_308 = (SVECTOR *)local_t0_256->vertices;
			cJerichoVNumbers[iVar7] = iVar4;
			iVar6 = 0;

			if (local_t0_256->num_vertices != 0)
			{
				pSVar3 = vJerichoList + iVar8;
				do {
					iVar4++;
					iVar6++;
					iVar8++;

					pSVar3->vx = local_a2_308->vx;
					pSVar3->vy = local_a2_308->vy;
					pSVar3->vz = local_a2_308->vz;

					local_a2_308++;
					pSVar3++;
				} while (iVar6 < local_t0_256->num_vertices);
			}
		}
		iVar7++;

	} while (iVar7 < 6);

	vStored = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupTannerSkeleton()
 // line 1355, offset 0x00065ad8
	/* begin block 1 */
		// Start line: 1357
		// Start offset: 0x00065AD8
		// Variables:
	// 		int i; // $t1
	// 		struct BONE *pBone; // $a3
	// 		char *pC; // $v0
	// 		struct SVECTOR *store; // $t4
	// 		struct SVECTOR_NOPAD *pSVNP; // $v1
	/* end block 1 */
	// End offset: 0x00065CD8
	// End Line: 1413

	/* begin block 2 */
		// Start line: 2892
	/* end block 2 */
	// End Line: 2893

	/* begin block 3 */
		// Start line: 2902
	/* end block 3 */
	// End Line: 2903

	/* begin block 4 */
		// Start line: 2903
	/* end block 4 */
	// End Line: 2904

	/* begin block 5 */
		// Start line: 2913
	/* end block 5 */
	// End Line: 2914

/* WARNING: Unknown calling convention yet parameter storage is locked */

int bodyShiftValue = 0;

// [D]
void SetupTannerSkeleton(PEDESTRIAN *pDrawingPed)
{
	short sVar1;
	SVECTOR_NOPAD *local_v0_180;
	SVECTOR_NOPAD *pSVar2;
	SVECTOR *local_a0_448;
	short sVar3;
	BONE *pBone;
	BONE *pBone1;
	SVECTOR *local_t0_244;
	int i;

	Skel[0].pvOrigPos = (SVECTOR_NOPAD *)(pDrawingPed->motion + pDrawingPed->frame1 * 144 + 146);
	Skel[0].pvRotation = (SVECTOR *)(pDrawingPed->motion + pDrawingPed->frame1 * 144 + 152);

	Skel[0].vCurrPos.vx = Skel[0].pvOrigPos->vx;
	Skel[0].vCurrPos.vy = -Skel[0].pvOrigPos->vy;
	Skel[0].vCurrPos.vz = -Skel[0].pvOrigPos->vz;

	Skel[0].vOffset.vx = 0;
	Skel[0].vOffset.vy = 0;
	Skel[0].vOffset.vz = 0;

	local_v0_180 = (SVECTOR_NOPAD *)(pDrawingPed->motion + pDrawingPed->frame1 * 144 + 158);
	pSVar2 = (SVECTOR_NOPAD *)(pDrawingPed->motion + 14);

	i = 21;
	pBone = Skel;
	do {
		i--;
		pBone[1].pvRotation = (SVECTOR*)local_v0_180;
		pBone[1].pvOrigPos = pSVar2;

		local_v0_180++;
		pSVar2++;
		pBone++;
	} while (-1 < i);

	SVECTOR SVECTOR_ARRAY_1f800008[24];

	i = 20;

	SVECTOR_ARRAY_1f800008[0].vx = Skel[1].pvOrigPos->vx;
	SVECTOR_ARRAY_1f800008[0].vy = -Skel[1].pvOrigPos->vy;
	SVECTOR_ARRAY_1f800008[0].vz = -Skel[1].pvOrigPos->vz;

	local_t0_244 = SVECTOR_ARRAY_1f800008;
	pBone = Skel + 1;

	do {
		SVECTOR* _prev = local_t0_244;
		local_t0_244++;

		local_t0_244->vx = pBone[1].pvOrigPos->vx - pBone[1].pParent->pvOrigPos->vx;
		local_t0_244->vy = pBone[1].pParent->pvOrigPos->vy - pBone[1].pvOrigPos->vy;
		local_t0_244->vz = pBone[1].pParent->pvOrigPos->vz - pBone[1].pvOrigPos->vz;

		if (pBone[1].id == JOINT_1) 
			local_t0_244->vy -= bodyShiftValue;

		i--;
		pBone++;
	} while (-1 < i);

	pBone1 = Skel;
	local_a0_448 = SVECTOR_ARRAY_1f800008;
	i = 21;
	do {
		pBone1++;

		pBone1->vCurrPos.vx = local_a0_448->vx;
		pBone1->vOffset.vx = local_a0_448->vx;

		pBone1->vCurrPos.vy = local_a0_448->vy;
		pBone1->vOffset.vy = local_a0_448->vy;

		pBone1->vCurrPos.vz = local_a0_448->vz;
		pBone1->vOffset.vz = local_a0_448->vz;

		local_a0_448++;
		i--;
	} while (-1 < i);

#if 0
		// Draw T POSE
	{
		extern void Debug_AddLine(VECTOR& pointA, VECTOR& pointB, CVECTOR& color);
		extern void Debug_AddLineOfs(VECTOR& pointA, VECTOR& pointB, VECTOR& ofs, CVECTOR& color);

		CVECTOR bbcv = { 0, 0, 250 };
		CVECTOR rrcv = { 250, 0, 0 };
		CVECTOR yycv = { 250, 250, 0 };

		for (int i = 0; i < 23; i++)
		{
			pBone = &Skel[i];

			for (int j = 0; j < pBone->numChildren; j++)
			{
				VECTOR v0 = {
					pBone->pvOrigPos->vx,
					pBone->pvOrigPos->vy,
					pBone->pvOrigPos->vz };

				VECTOR v1 = {
					pBone->pChildren[j]->pvOrigPos->vx,
					pBone->pChildren[j]->pvOrigPos->vy,
					pBone->pChildren[j]->pvOrigPos->vz };

				VECTOR ofs = *(VECTOR*)&pDrawingPed->position;
				ofs.vy = -ofs.vy;
				//ofs.vy += 270;

				Debug_AddLineOfs(v0, v1, ofs, bbcv);
			}

		}
	}
#endif
}



// decompiled code
// original method signature: 
// void /*$ra*/ newShowTanner()
 // line 1421, offset 0x00065cd8
	/* begin block 1 */
		// Start line: 1423
		// Start offset: 0x00065CD8
		// Variables:
	// 		struct VECTOR *playerPos; // $a2
	// 		struct VECTOR *camPos; // $a1
	// 		struct VECTOR *vJPos; // $s1
	// 		struct VECTOR v; // stack offset -128
	// 		struct MODEL *pModel; // $t0
	// 		struct SVECTOR *mVerts; // $a1
	// 		int i; // $s2
	// 		int j; // $a3
	// 		int c; // $a3
	// 		int id; // $a2
	// 		int limbs; // $a0
	// 		struct BONE *pBone; // $s0
	// 		int lval; // $t1

		/* begin block 1.1 */
			// Start line: 1530
			// Start offset: 0x000660A0
			// Variables:
		// 		struct BONE *pBone; // $s0
		// 		struct VECTOR *v1; // $a2
		// 		struct VECTOR *v2; // $a1

			/* begin block 1.1.1 */
				// Start line: 1530
				// Start offset: 0x000660A0
				// Variables:
			// 		struct SVECTOR *data; // $t1
			// 		long t1; // stack offset -92
			// 		long t0; // stack offset -96
			// 		int z2; // stack offset -80
			// 		int z1; // stack offset -84
			// 		int z; // stack offset -88
			/* end block 1.1.1 */
			// End offset: 0x000661C4
			// End Line: 1530
		/* end block 1.1 */
		// End offset: 0x000661C4
		// End Line: 1530

		/* begin block 1.2 */
			// Start line: 1536
			// Start offset: 0x000661F8
			// Variables:
		// 		struct BONE *pBone; // $s0
		// 		struct VECTOR *v1; // $a0
		// 		struct VECTOR *v2; // $a2

			/* begin block 1.2.1 */
				// Start line: 1536
				// Start offset: 0x000661F8
				// Variables:
			// 		struct SVECTOR *data; // $t0
			// 		long t1; // stack offset -72
			// 		long t0; // stack offset -76
			// 		int z2; // stack offset -60
			// 		int z1; // stack offset -64
			// 		int z; // stack offset -68
			/* end block 1.2.1 */
			// End offset: 0x000661F8
			// End Line: 1536
		/* end block 1.2 */
		// End offset: 0x000661F8
		// End Line: 1536

		/* begin block 1.3 */
			// Start line: 1542
			// Start offset: 0x00066330
			// Variables:
		// 		struct SVECTOR v1; // stack offset -112
		// 		struct SVECTOR v2; // stack offset -104
		/* end block 1.3 */
		// End offset: 0x00066330
		// End Line: 1544

		/* begin block 1.4 */
			// Start line: 1569
			// Start offset: 0x0006648C
			// Variables:
		// 		struct BONE *pBone; // $s0
		// 		struct VECTOR *v1; // $a2
		// 		struct VECTOR *v2; // $a1

			/* begin block 1.4.1 */
				// Start line: 1569
				// Start offset: 0x0006648C
				// Variables:
			// 		struct SVECTOR *data; // $t1
			// 		long t1; // stack offset -52
			// 		long t0; // stack offset -56
			// 		int z2; // stack offset -40
			// 		int z1; // stack offset -44
			// 		int z; // stack offset -48
			/* end block 1.4.1 */
			// End offset: 0x0006648C
			// End Line: 1569
		/* end block 1.4 */
		// End offset: 0x0006648C
		// End Line: 1569

		/* begin block 1.5 */
			// Start line: 1575
			// Start offset: 0x000665C8
			// Variables:
		// 		int bias; // $a3
		/* end block 1.5 */
		// End offset: 0x000665F4
		// End Line: 1588
	/* end block 1 */
	// End offset: 0x00066648
	// End Line: 1599

	/* begin block 2 */
		// Start line: 3093
	/* end block 2 */
	// End Line: 3094

	/* begin block 3 */
		// Start line: 3102
	/* end block 3 */
	// End Line: 3103

	/* begin block 4 */
		// Start line: 3103
	/* end block 4 */
	// End Line: 3104

	/* begin block 5 */
		// Start line: 3114
	/* end block 5 */
	// End Line: 3115

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int bAllreadyRotated = 0;

// [D]
void newShowTanner(PEDESTRIAN *pDrawingPed)
{
	LIMBS LVar1;
	VERTTYPE v1_00[2];
	VERTTYPE v2_00[2];

	int iVar3;
	int sy;
	BONE *pBone;
	int vvar1;
	SVECTOR *mVerts;
	uint uVar4;
	int iVar5;
	MODEL *model;
	uint uVar6;
	VECTOR v;
	SVECTOR v1;
	SVECTOR v2;
	long t0;
	long t1;
	int z;
	int z1;
	int z2;
	long _t0;
	long _t1;
	int _z;
	int _z1;
	int _z2;
	long __t0;
	long __t1;
	int __z;
	int __z1;
	int __z2;
	int draw;

	VECTOR VECTOR_1f800000;
	VECTOR VECTOR_1f800010;
	VECTOR VECTOR_ARRAY_1f800020[64];
	SVECTOR SVECTOR_1f800200;
	SVECTOR SVECTOR_1f800208;

	VECTOR_1f800000.vx = (pDrawingPed->position).vx;
	VECTOR_1f800000.vy = (pDrawingPed->position).vy;
	VECTOR_1f800000.vz = (pDrawingPed->position).vz;
	VECTOR_1f800010.vx = camera_position.vx;
	VECTOR_1f800010.vy = camera_position.vy;
	VECTOR_1f800010.vz = camera_position.vz;
	VECTOR_ARRAY_1f800020[0].vx = (long)(Skel[0].pvOrigPos)->vx;
	VECTOR_ARRAY_1f800020[0].vy = -(int)(Skel[0].pvOrigPos)->vy;
	VECTOR_ARRAY_1f800020[0].vz = (long)(Skel[0].pvOrigPos)->vz;

	v.vz = 0;
	v.vy = 0;
	v.vx = 0;

	gte_SetTransVector(&v);

	vvar1 = 0;
	Skel[0].id = (LIMBS)(Skel[0].id | 0x80);
	sy = 0;

	draw = (pDrawingPed->padId > -1 && pDrawingPed->padId == CurrentPlayerView) ? player[pDrawingPed->padId].cameraView != 2 : 1;

	do {
		LVar1 = lRoutes[vvar1][1];
		iVar5 = 1;

		while (LVar1 != ROOT) 
		{
			LVar1 = lRoutes[vvar1][iVar5];
			uVar4 = (uint)LVar1;
			pBone = Skel + uVar4;
			if (pBone->id < 0x7f)
			{
				uVar6 = lRoutes[vvar1][iVar5-1];//  (uint)*(byte *)((int)MissionName37 + iVar5 + sy + 0x93);
				VECTOR_ARRAY_1f800020[pBone->id].vx = VECTOR_ARRAY_1f800020[uVar6].vx + Skel[uVar4].vCurrPos.vx;
				VECTOR_ARRAY_1f800020[pBone->id].vy = VECTOR_ARRAY_1f800020[uVar6].vy + Skel[uVar4].vCurrPos.vy;
				VECTOR_ARRAY_1f800020[pBone->id].vz = VECTOR_ARRAY_1f800020[uVar6].vz + Skel[uVar4].vCurrPos.vz;
				
				if ((pDrawingPed->pedType == TANNER_MODEL) && (pBone->id == HEAD)) 
				{
					iVar3 = VECTOR_ARRAY_1f800020[uVar6].vy - 94;
					pDrawingPed->head_pos = iVar3 / 3;
				}

				if (Skel[uVar4].pModel != NULL && bDoingShadow == 0 && pDrawingPed->pedType < OTHER_SPRITE && draw)
				{
					model = *Skel[uVar4].pModel;

					mVerts = (SVECTOR *)model->vertices;
					iVar3 = 0;
					if (model->num_vertices != 0) 
					{
						do {
							iVar3 = iVar3 + 1;
							mVerts->vx = mVerts->vx + ((*(short *)&VECTOR_ARRAY_1f800020[uVar6].vx + (short)VECTOR_1f800000.vx) - (short)VECTOR_1f800010.vx);
							mVerts->vy = mVerts->vy + ((*(short *)&VECTOR_ARRAY_1f800020[uVar6].vy + (short)VECTOR_1f800000.vy) - (short)VECTOR_1f800010.vy);
							mVerts->vz = mVerts->vz + ((*(short *)&VECTOR_ARRAY_1f800020[uVar6].vz + (short)VECTOR_1f800000.vz) - (short)VECTOR_1f800010.vz);
							mVerts = mVerts + 1;
						} while (iVar3 < model->num_vertices);
					}
				}
				pBone->id = (LIMBS)(pBone->id | 0x80);
			}
			iVar5++;
			
		}
		vvar1++;
		sy = vvar1 * 8;
	} while (vvar1 < 5);

	pBone = Skel + 1;

	if (pDrawingPed->pedType < OTHER_SPRITE)
	{
		if (draw || bDoingShadow != 0)
		{
			sy = 20;
			do {
				uVar4 = (uint)pBone->id & 0x7f;
				if (bDoingShadow == 0) 
				{
					if (pBone->pModel != NULL)
					{
						vvar1 = (uint)(uVar4 != 4) << 1;

						if (uVar4 == 2)
							vvar1 = 1;

						RenderModel(*pBone->pModel, NULL, &v, vvar1, 0, 0);
					}
				}
				else 
				{
					if (((uVar4 != 5) && (uVar4 != 9)) &&
						((uVar4 != 0xd &&
						((((uVar4 != 1 && ((pBone->id & 0x7f) != 0)) && (uVar4 != 0x16)) &&
						((uVar4 != 0xe && (uVar4 != 0x12)))))))) 
					{
						uVar6 = pBone->pParent->id & 0x7f;

						SVECTOR_1f800200.vx = VECTOR_ARRAY_1f800020[uVar4].vx + pDrawingPed->position.vx - camera_position.vx;
						SVECTOR_1f800200.vy = VECTOR_ARRAY_1f800020[uVar4].vy + pDrawingPed->position.vy - camera_position.vy;
						SVECTOR_1f800200.vz = VECTOR_ARRAY_1f800020[uVar4].vz + pDrawingPed->position.vz - camera_position.vz;

						SVECTOR_1f800208.vx = VECTOR_ARRAY_1f800020[uVar6].vx + pDrawingPed->position.vx - camera_position.vx;
						SVECTOR_1f800208.vy = VECTOR_ARRAY_1f800020[uVar6].vy + pDrawingPed->position.vy - camera_position.vy;
						SVECTOR_1f800208.vz = VECTOR_ARRAY_1f800020[uVar6].vz + pDrawingPed->position.vz - camera_position.vz;

						gte_ldv0(&SVECTOR_1f800200);
						gte_ldv1(&SVECTOR_1f800208);

						gte_rtpt();
						gte_stsxy0(&v1_00[0]);
						gte_stsxy1(&v2_00[0]);

						gte_stsz3(&z, &z1, &z2);

						gCurrentZ = z1;

						DrawBodySprite(pDrawingPed, pBone->id, v1_00, v2_00, z, z1);
					}
				}

#if 0
				// DEBUG DRAW SKELETON
				{
					uVar6 = (uint)pBone->pParent->id & 0x7f;

					extern void Debug_AddLine(VECTOR& pointA, VECTOR& pointB, CVECTOR& color);
					extern void Debug_AddLineOfs(VECTOR& pointA, VECTOR& pointB, VECTOR& ofs, CVECTOR& color);

					CVECTOR bbcv = { 0, 0, 250 };
					CVECTOR rrcv = { 250, 0, 0 };
					CVECTOR yycv = { 250, 250, 0 };

					VECTOR v0 = {
						VECTOR_ARRAY_1f800020[uVar4].vx,
						-VECTOR_ARRAY_1f800020[uVar4].vy,
						VECTOR_ARRAY_1f800020[uVar4].vz
					};

					VECTOR v1 = {
						VECTOR_ARRAY_1f800020[uVar6].vx,
						-VECTOR_ARRAY_1f800020[uVar6].vy,
						VECTOR_ARRAY_1f800020[uVar6].vz
					};

					VECTOR ofs = *(VECTOR*)&pDrawingPed->position;
					ofs.vy = -ofs.vy;
					//ofs.vy += 270;

					Debug_AddLineOfs(v0, v1, ofs, bbcv);
				}
#endif

				sy = sy + -1;
				pBone = pBone + 1;
			} while (-1 < sy);
		}
	}
	else 
	{
		sy = 21;
		do {
			uVar4 = (uint)pBone->id & 0x7f;
			if ((((uVar4 != 5) && (uVar4 != 9)) && ((uVar4 != 4 && (((uVar4 != 0xd && (uVar4 != 1)) && ((pBone->id & 0x7f) != 0))))))
				&& (((uVar4 != 0x16 && (uVar4 != 0xe)) && (uVar4 != 0x12))))
			{
				uVar6 = (uint)pBone->pParent->id & 0x7f;

				SVECTOR_1f800200.vx = VECTOR_ARRAY_1f800020[uVar4].vx + pDrawingPed->position.vx - camera_position.vx;
				SVECTOR_1f800200.vy = VECTOR_ARRAY_1f800020[uVar4].vy + pDrawingPed->position.vy - camera_position.vy;
				SVECTOR_1f800200.vz = VECTOR_ARRAY_1f800020[uVar4].vz + pDrawingPed->position.vz - camera_position.vz;

				SVECTOR_1f800208.vx = VECTOR_ARRAY_1f800020[uVar6].vx + pDrawingPed->position.vx - camera_position.vx;
				SVECTOR_1f800208.vy = VECTOR_ARRAY_1f800020[uVar6].vy + pDrawingPed->position.vy - camera_position.vy;
				SVECTOR_1f800208.vz = VECTOR_ARRAY_1f800020[uVar6].vz + pDrawingPed->position.vz - camera_position.vz;

				gte_ldv0(&SVECTOR_1f800200);
				gte_ldv1(&SVECTOR_1f800208);

				gte_rtpt();
				gte_stsxy0(v1_00);
				gte_stsxy1(v2_00);

				gte_stsz3(&z, &z1, &z2);

				gCurrentZ = z1;

				DrawBodySprite(pDrawingPed, pBone->id, v1_00, v2_00, z, z1);
			}
			sy = sy + -1;
			pBone = pBone + 1;
		} while (-1 < sy);

		if (switch_detail_distance >> 2 < gCurrentZ) 
		{
			uVar4 = (uint)Skel[4].id & 0x7f;
			uVar6 = (uint)(Skel[4].pParent)->id & 0x7f;

			SVECTOR_1f800200.vx = VECTOR_ARRAY_1f800020[uVar4].vx + pDrawingPed->position.vx - camera_position.vx;
			SVECTOR_1f800200.vy = VECTOR_ARRAY_1f800020[uVar4].vy + pDrawingPed->position.vy - camera_position.vy;
			SVECTOR_1f800200.vz = VECTOR_ARRAY_1f800020[uVar4].vz + pDrawingPed->position.vz - camera_position.vz;

			SVECTOR_1f800208.vx = VECTOR_ARRAY_1f800020[uVar6].vx + pDrawingPed->position.vx - camera_position.vx;
			SVECTOR_1f800208.vy = VECTOR_ARRAY_1f800020[uVar6].vy + pDrawingPed->position.vy - camera_position.vy;
			SVECTOR_1f800208.vz = VECTOR_ARRAY_1f800020[uVar6].vz + pDrawingPed->position.vz - camera_position.vz;

			gte_ldv0(&SVECTOR_1f800200);
			gte_ldv1(&SVECTOR_1f800208);

			gte_rtpt();
			gte_stsxy0(v1_00);
			gte_stsxy1(v2_00);

			gte_stsz3(&z, &z1, &z2);

			gCurrentZ = z1;

			DrawBodySprite(pDrawingPed, Skel[4].id, v1_00, v2_00, z, z1);
		}
		else 
		{
			v1.vx = *(short *)&VECTOR_ARRAY_1f800020[(uint)Skel[4].id & 0x7f].vx;
			v1.vy = *(short *)&VECTOR_ARRAY_1f800020[(uint)Skel[4].id & 0x7f].vy;
			v1.vz = *(short *)&VECTOR_ARRAY_1f800020[(uint)Skel[4].id & 0x7f].vz;
			v2.vx = *(short *)&VECTOR_ARRAY_1f800020[(uint)(Skel[4].pParent)->id & 0x7f].vx;
			v2.vy = *(short *)&VECTOR_ARRAY_1f800020[(uint)(Skel[4].pParent)->id & 0x7f].vy;
			v2.vz = *(short *)&VECTOR_ARRAY_1f800020[(uint)(Skel[4].pParent)->id & 0x7f].vz;

			bAllreadyRotated = 1;
			DoCivHead(pDrawingPed, &v2, &v1);
			bAllreadyRotated = 0;
		}
	}

	pBone = Skel;
	sy = 0;
	do {
		sy++;
		pBone->id = (LIMBS)(pBone->id & 0x7f);
		pBone++;
	} while (sy < 23);
}


// decompiled code
// original method signature: 
// struct SVECTOR * /*$ra*/ GetModelVertPtr(int boneId /*$a1*/, int modelType /*$a1*/)
 // line 1774, offset 0x00066fb8
	/* begin block 1 */
		// Start line: 4462
	/* end block 1 */
	// End Line: 4463

	/* begin block 2 */
		// Start line: 4471
	/* end block 2 */
	// End Line: 4472

	/* begin block 3 */
		// Start line: 4472
	/* end block 3 */
	// End Line: 4473

// [D]
SVECTOR* GetModelVertPtr(PEDESTRIAN *pDrawingPed, int boneId, int modelType)
{
	int startVertex;

	if (pDrawingPed->pedType != OTHER_MODEL)
	{
		if (cTannerVNumbers[boneId & 0x7f] != -1)
			return vTannerList + cTannerVNumbers[boneId & 0x7f];

		return NULL;
	}

	switch (boneId)
	{
		case 2:
			startVertex = cJerichoVNumbers[0];
			break;
		case 4:
			startVertex = cJerichoVNumbers[1];
			break;
		case 6:
			startVertex = cJerichoVNumbers[2];
			break;
		case 7:
			startVertex = cJerichoVNumbers[3];
			break;
		case 10:
			startVertex = cJerichoVNumbers[4];
			break;
		case 11:
			startVertex = cJerichoVNumbers[5];
		default:
			return vTannerList + cTannerVNumbers[boneId & 0x7f];
	}

	return vJerichoList + startVertex;
}


// decompiled code
// original method signature: 
// void /*$ra*/ newRotateBones(struct BONE *poBone /*$a0*/)
 // line 1606, offset 0x00066648
	/* begin block 1 */
		// Start line: 1608
		// Start offset: 0x00066648
		// Variables:
	// 		struct MATRIX mStore[32]; // stack offset -1088
	// 		struct MATRIX *pMatrix; // $s2
	// 		struct MATRIX *oMatrix; // $s5
	// 		struct SVECTOR *svBone; // $s6
	// 		struct VECTOR *vBoneRotated; // $s3
	// 		struct BONE *pBone; // $s1
	// 		int id; // $s0
	// 		struct SVECTOR *pVerts; // $a3
	// 		struct SVECTOR *pmVerts; // $s0
	// 		int numVerts; // $t0
	// 		struct MODEL *pModel; // $v0
	// 		int i; // $a2
	// 		struct SVECTOR *pD; // $a0
	// 		int c; // $s4
	// 		int j; // $a1
	// 		struct VECTOR sv; // stack offset -64

		/* begin block 1.1 */
			// Start line: 1609
			// Start offset: 0x00066648
			// Variables:
		// 		int cx; // $t2
		// 		int sx; // $a3
		// 		int cy; // $a0
		// 		int sy; // $t0
		// 		int cz; // $t3
		// 		int sz; // $t6
		// 		int stmp; // $v0
		/* end block 1.1 */
		// End offset: 0x00066648
		// End Line: 1609
	/* end block 1 */
	// End offset: 0x00066FB8
	// End Line: 1766

	/* begin block 2 */
		// Start line: 3674
	/* end block 2 */
	// End Line: 3675

	/* begin block 3 */
		// Start line: 3682
	/* end block 3 */
	// End Line: 3683

	/* begin block 4 */
		// Start line: 3683
	/* end block 4 */
	// End Line: 3684

	/* begin block 5 */
		// Start line: 3684
	/* end block 5 */
	// End Line: 3685

	/* begin block 6 */
		// Start line: 3685
	/* end block 6 */
	// End Line: 3686

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

// [D] [A] it's fucked up... maybe
void newRotateBones(PEDESTRIAN *pDrawingPed, BONE *poBone)
{
	short *psVar1;
	LIMBS LVar2;
	uint uVar4;
	SVECTOR *verts;
	MODEL *pMVar5;
	int iVar6;
	int iVar7;
	SVECTOR *pSVar8;
	ushort uVar9;
	uint uVar10;
	uint uVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	int iVar15;
	uint uVar16;
	int iVar17;
	short *psVar18;
	MATRIX mStore[32];
	VECTOR sv;
	int local_30;

	MATRIX MATRIX_1f800000;
	MATRIX MATRIX_1f800020;
	MATRIX MATRIX_1f800040;
	
	SVECTOR SVECTOR_ARRAY_1f800060[2];
	SVECTOR SVECTOR_ARRAY_1f800080[80];
	VECTOR VECTOR_1f800070;

	SVECTOR* local_s0_2092;

	MATRIX_1f800020.t[0] = Skel[0].pvOrigPos->vx;
	MATRIX_1f800020.t[1] = Skel[0].pvOrigPos->vy;
	MATRIX_1f800020.t[2] = Skel[0].pvOrigPos->vz;

	// RotMatrix inline?
	// TODO: pretty it
	{
		uVar11 = (int)(pDrawingPed->dir).vx & 0xfff;
		uVar10 = (int)(pDrawingPed->dir).vy & 0xfff;
		uVar4 = (int)(pDrawingPed->dir).vz & 0xfff;

		iVar6 = (int)rcossin_tbl[uVar10 * 2 + 1];
		iVar17 = (int)rcossin_tbl[uVar4 * 2];
		iVar15 = (int)rcossin_tbl[uVar4 * 2 + 1];
		iVar14 = (int)rcossin_tbl[uVar11 * 2 + 1];
		iVar12 = (int)rcossin_tbl[uVar11 * 2];
		iVar13 = (int)rcossin_tbl[uVar10 * 2];

		uVar10 = FIXEDH(iVar14 * iVar13) + FIXEDH(FIXEDH(iVar6 * iVar12) * iVar17);
		uVar16 = FIXEDH(iVar6 * iVar15);
		iVar7 = uVar16;
		uVar9 = -FIXEDH(iVar15 * iVar12);
		uVar11 = FIXEDH(iVar14 * iVar15);
		iVar6 = FIXEDH(-iVar14 * FIXEDH(iVar6 * iVar17)) + FIXEDH(iVar12 * iVar13);

		MATRIX_1f800020.m[0][0] = uVar16;
		MATRIX_1f800020.m[0][1] = iVar6;
		MATRIX_1f800020.m[0][2] = uVar10;

		MATRIX_1f800020.m[1][0] = rcossin_tbl[uVar4 * 2];
		MATRIX_1f800020.m[1][1] = uVar11;
		MATRIX_1f800020.m[1][2] = uVar9;

		MATRIX_1f800020.m[2][0] = -FIXEDH(iVar13 * iVar15);
		MATRIX_1f800020.m[2][1] = FIXEDH(uVar10 * iVar17) - FIXEDH(iVar7 * uVar9);
		MATRIX_1f800020.m[2][2] = FIXEDH(iVar7 * uVar11) - FIXEDH(iVar6 * iVar17);
	}

	SVECTOR_ARRAY_1f800060[0].vx = Skel[0].vOffset.vx;
	SVECTOR_ARRAY_1f800060[0].vy = Skel[0].vOffset.vy;
	SVECTOR_ARRAY_1f800060[0].vz = Skel[0].vOffset.vz;

	mStore[0] = MATRIX_1f800020;

	local_30 = 0;
	do {
		iVar7 = local_30 * 8;
		iVar6 = 1;
		LVar2 = lRoutes[local_30][iVar6];

		while (LVar2 != ROOT) 
		{
			uVar4 = (uint)LVar2;
			SVECTOR_ARRAY_1f800060[0].vx = Skel[uVar4].vOffset.vx;
			SVECTOR_ARRAY_1f800060[0].vy = Skel[uVar4].vOffset.vy;
			SVECTOR_ARRAY_1f800060[0].vz = Skel[uVar4].vOffset.vz;

			if (bReverseYRotation == 0 || Skel[uVar4].pParent->id != ROOT) 
			{
				SVECTOR_ARRAY_1f800060[1].vx = -Skel[uVar4].pParent->pvRotation->vx;
				SVECTOR_ARRAY_1f800060[1].vy = Skel[uVar4].pParent->pvRotation->vy;
				SVECTOR_ARRAY_1f800060[1].vz = Skel[uVar4].pParent->pvRotation->vz;
			}
			else 
			{
				SVECTOR_ARRAY_1f800060[1].vx = Skel[uVar4].pParent->pvRotation->vx;
				SVECTOR_ARRAY_1f800060[1].vy = -Skel[uVar4].pParent->pvRotation->vy;
				SVECTOR_ARRAY_1f800060[1].vz = Skel[uVar4].pParent->pvRotation->vz;
			}

			if (LVar2 == HEAD) 
			{
				SVECTOR_ARRAY_1f800060[1].vy -= pDrawingPed->head_rot;
			}

			RotMatrixZYX_gte(&SVECTOR_ARRAY_1f800060[1], &MATRIX_1f800000);

			MATRIX_1f800000.t[0] = SVECTOR_ARRAY_1f800060[0].vx;
			MATRIX_1f800000.t[1] = SVECTOR_ARRAY_1f800060[0].vy;
			MATRIX_1f800000.t[2] = SVECTOR_ARRAY_1f800060[0].vz;

			uVar10 = Skel[uVar4].pParent->id & 0x7f;

			MATRIX_1f800020 = mStore[uVar10];

			gte_MulMatrix0(&MATRIX_1f800020, &MATRIX_1f800000, &MATRIX_1f800040);

			gte_SetRotMatrix(&MATRIX_1f800040);

			gte_ldv0(&SVECTOR_ARRAY_1f800060[0]);

			//setCopReg(2, in_zero, SVECTOR_ARRAY_1f800060[0]._0_4_);
			//setCopReg(2, 0x1f800000, SVECTOR_ARRAY_1f800060[0]._4_4_);

			gte_rtv0();

			gte_stlvnl(&VECTOR_1f800070);

			LVar2 = Skel[uVar4].id;
			Skel[uVar4].vCurrPos.vx = VECTOR_1f800070.vx;
			Skel[uVar4].vCurrPos.vy = VECTOR_1f800070.vy;
			Skel[uVar4].vCurrPos.vz = VECTOR_1f800070.vz;

			verts = GetModelVertPtr(pDrawingPed, LVar2, 0);
			LVar2 = Skel[uVar4].id;

			/**/
            if (((((LVar2 & 0x7f) == 4) || (pDrawingPed->pedType < OTHER_SPRITE)) &&
                (-1 < (int)((uint)LVar2 << 0x18))) &&
               ((Skel[uVar4].pModel != NULL && (verts != NULL))))
			{
                pMVar5 = *Skel[uVar4].pModel;
                uVar9 = pMVar5->num_vertices;
                uVar11 = (uint)uVar9;
                local_s0_2092 = (SVECTOR *)pMVar5->vertices;
                pSVar8 = SVECTOR_ARRAY_1f800080;
                uVar10 = uVar11;

                if (uVar9 != 0) 
				{
                    do {
                        pSVar8->vx = verts->vx + SVECTOR_ARRAY_1f800060[0].vx;
                        pSVar8->vy = verts->vy + SVECTOR_ARRAY_1f800060[0].vy;
                        pSVar8->vz = verts->vz + SVECTOR_ARRAY_1f800060[0].vz;

						verts = verts + 1;
						uVar10 = uVar10 - 1;
                        pSVar8 = pSVar8 + 1;
                    } while (uVar10 != 0);
                }

                verts = SVECTOR_ARRAY_1f800080;

                if (uVar9 != 0)
				{
                    do {
						gte_ldv0(verts);

						gte_rtv0();

						gte_stlvnl(&VECTOR_1f800070);

                        local_s0_2092->vx = VECTOR_1f800070.vx;
                        local_s0_2092->vy = VECTOR_1f800070.vy;
                        local_s0_2092->vz = VECTOR_1f800070.vz;

                        local_s0_2092 = local_s0_2092 + 1;
						verts = verts + 1;
						uVar11 = uVar11 - 1;
                    } while (uVar11 != 0);
                }
            }

			iVar6 = iVar6 + 1;
			LVar2 = lRoutes[local_30][iVar6];

			mStore[uVar4] = MATRIX_1f800040;
		}

		local_30 = local_30 + 1;
	} while (local_30 < 5);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCiv(struct PEDESTRIAN *pPed /*$fp*/)
 // line 1834, offset 0x000670cc
	/* begin block 1 */
		// Start line: 1835
		// Start offset: 0x000670CC
		// Variables:
	// 		int i; // $s5
	// 		struct DVECTOR *outpoints; // $t9
	// 		long *outlongs; // $s5
	// 		struct SVECTOR *psrLerpData; // $t8
	// 		long *zbuff; // $s4
	// 		struct SVECTOR *pLerpData; // $s0
	// 		struct SVECTOR pos; // stack offset -160
	// 		struct VECTOR pos1; // stack offset -152
	// 		struct SVECTOR *vert1; // $a1
	// 		struct SVECTOR *vert2; // $a0
	// 		struct SVECTOR temp1; // stack offset -136
	// 		struct SVECTOR temp2; // stack offset -128
	// 		int cnt3; // $a2
	// 		int bHeadModel; // stack offset -56
	// 		int shift; // $t0
	// 		int frame; // $a2
	// 		struct MATRIX workmatrix; // stack offset -120
	// 		int j; // $s7

		/* begin block 1.1 */
			// Start line: 1908
			// Start offset: 0x000672B8
			// Variables:
		// 		int cx; // $v1
		// 		int sx; // $a0
		// 		int cy; // $a1
		// 		int sy; // $t0
		// 		int cz; // $t3
		// 		int sz; // $t6
		// 		int stmp; // $t7
		/* end block 1.1 */
		// End offset: 0x000672B8
		// End Line: 1908

		/* begin block 1.2 */
			// Start line: 1964
			// Start offset: 0x000677C0
			// Variables:
		// 		struct SVECTOR sV; // stack offset -88
		// 		struct SVECTOR sV2; // stack offset -80
		// 		struct VECTOR v; // stack offset -72
		/* end block 1.2 */
		// End offset: 0x000677FC
		// End Line: 1976

		/* begin block 1.3 */
			// Start line: 1985
			// Start offset: 0x000677FC
			// Variables:
		// 		struct CVECTOR cv; // stack offset -88
		// 		struct VECTOR pos; // stack offset -80
		// 		int phase; // $s0
		/* end block 1.3 */
		// End offset: 0x000678A0
		// End Line: 1998
	/* end block 1 */
	// End offset: 0x000678A0
	// End Line: 2001

	/* begin block 2 */
		// Start line: 4582
	/* end block 2 */
	// End Line: 4583

	/* begin block 3 */
		// Start line: 4595
	/* end block 3 */
	// End Line: 4596

	/* begin block 4 */
		// Start line: 4601
	/* end block 4 */
	// End Line: 4602

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

// [D]
void DrawCiv(PEDESTRIAN *pPed)
{
	short *psVar1;
	bool bVar2;
	long lVar3;
	int iVar8;
	long lVar9;
	SVECTOR *vert2;
	int iVar10;
	SVECTOR *vert1;
	int iVar11;
	int iVar12;
	uint v1;
	short size;
	uint boneId;
	int iVar13;
	uint uVar14;
	uint uVar15;
	int iVar16;
	uint uVar17;
	uint uVar18;
	int iVar19;
	uint uVar20;
	int iVar21;
	SVECTOR *psrLerpData;
	long *plVar22;
	long *plVar23;
	SVECTOR *pSVar24;

	long *zbuff;
	long *outlongs;
	int *piVar25;
	int iVar26;
	SVECTOR pos;
	VECTOR pos1;
	SVECTOR temp1;
	SVECTOR temp2;
	MATRIX workmatrix;
	CVECTOR cv;
	VECTOR ppos;
	int local_38;
	CVECTOR *_cv;
	VECTOR *_ppos;

	long LONG_ARRAY_1f800010[64];
	long LONG_ARRAY_1f800210[64];
	SVECTOR SVECTOR_ARRAY_1f800090[64];

	outlongs = LONG_ARRAY_1f800010;
	zbuff = LONG_ARRAY_1f800210;
	psrLerpData = SVECTOR_ARRAY_1f800090;

	local_38 = 0;
	vert1 = (SVECTOR *)pPed->motion;
	iVar26 = 0;
	boneId = (uint)(pPed->frame1 >> 1);
	vert2 = vert1 + boneId * 0x1e;
	uVar15 = pPed->head_pos;// (uint)(*(char *)((int)&pPed->flags + 1) >> 7);	// [A] scale? height offset?

	if ((pPed->frame1 & 1U) == 0)
	{
		iVar13 = 30;
		do {
			psrLerpData->vx = vert2->vx;
			psrLerpData->vy = (vert2->vy >> uVar15);
			psrLerpData->vz = vert2->vz;

			iVar13--;
			psrLerpData++;
			vert2++;
		} while (0 < iVar13);
	}
	else 
	{
		if (pPed->frame1 < 30)
			vert1 += (boneId + 1) * 30;
	
		iVar13 = 30;
		do {
			// WTF?
			temp1.vx = vert1->vx;
			temp2.vx = vert2->vx;

			temp1.vy = vert1->vy;
			temp2.vy = vert2->vy;

			temp1.vz = vert1->vz;
			temp2.vz = vert2->vz;
		
			psrLerpData->vx = (temp1.vx + temp2.vx >> 1);
			psrLerpData->vy = (temp1.vy + temp2.vy >> uVar15 + 1);
			psrLerpData->vz = (temp1.vz + temp2.vz >> 1);

			iVar13--;
			vert1++;
			vert2++;
			psrLerpData++;
		} while (0 < iVar13);
	}

	pos.vx = pPed->position.vx - camera_position.vx;
	pos.vy = pPed->position.vy - camera_position.vy;
	pos.vz = pPed->position.vz - camera_position.vz;

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_ldv0(&pos);
	gte_rtv0(); // short vector transform

	gte_stlvnl(&pos1);
	gte_SetTransVector(&pos1);

	// RotMatrix inline?
	// TODO: pretty it
	{
		int uVar11, uVar10, uVar4, iVar6, iVar14, iVar15, iVar17, uVar16, iVar7, uVar9;

		uVar11 = (int)(pPed->dir).vx & 0xfff;
		uVar10 = (int)(pPed->dir).vy & 0xfff;
		uVar4 = (int)(pPed->dir).vz & 0xfff;

		iVar6 = (int)rcossin_tbl[uVar10 * 2 + 1];
		iVar17 = (int)rcossin_tbl[uVar4 * 2];
		iVar15 = (int)rcossin_tbl[uVar4 * 2 + 1];
		iVar14 = (int)rcossin_tbl[uVar11 * 2 + 1];
		iVar12 = (int)rcossin_tbl[uVar11 * 2];
		iVar13 = (int)rcossin_tbl[uVar10 * 2];

		uVar10 = FIXEDH(iVar14 * iVar13) + FIXEDH(FIXEDH(iVar6 * iVar12) * iVar17);
		uVar16 = FIXEDH(iVar6 * iVar15);
		iVar7 = uVar16;
		uVar9 = -FIXEDH(iVar15 * iVar12);
		uVar11 = FIXEDH(iVar14 * iVar15);
		iVar6 = FIXEDH(-iVar14 * FIXEDH(iVar6 * iVar17)) + FIXEDH(iVar12 * iVar13);

		workmatrix.m[0][0] = uVar16;
		workmatrix.m[0][1] = iVar6;
		workmatrix.m[0][2] = uVar10;

		workmatrix.m[1][0] = rcossin_tbl[uVar4 * 2];
		workmatrix.m[1][1] = uVar11;
		workmatrix.m[1][2] = uVar9;

		workmatrix.m[2][0] = -FIXEDH(iVar13 * iVar15);
		workmatrix.m[2][1] = FIXEDH(uVar10 * iVar17) - FIXEDH(iVar7 * uVar9);
		workmatrix.m[2][2] = FIXEDH(iVar7 * uVar11) - FIXEDH(iVar6 * iVar17);
	}

	gte_MulMatrix0(&inv_camera_matrix, &workmatrix, &workmatrix);

	gte_SetRotMatrix(&workmatrix);

	gte_ldv3(&SVECTOR_ARRAY_1f800090[0], &SVECTOR_ARRAY_1f800090[1], &SVECTOR_ARRAY_1f800090[2]);

	gte_rtpt();

	gte_stsz(&gCurrentZ);
	//gCurrentZ = getCopReg(2, 0x13);

	LONG_ARRAY_1f800210[0] = gCurrentZ;

	if (gCurrentZ <= switch_detail_distance)
	{
		_cv = &cv;
		piVar25 = boneIdvals;
		lVar9 = 0;

		plVar23 = LONG_ARRAY_1f800210;
		plVar22 = LONG_ARRAY_1f800010;
		vert2 = SVECTOR_ARRAY_1f800090;

		iVar13 = 0xe;
		do {
			if (iVar26 < 30) 
			{
				gte_stsxy3(&plVar22[0], &plVar22[1], &plVar22[2]);
				gte_stsz3(&plVar23[0], &plVar23[1], &plVar23[2]);

				/*
				lVar3 = getCopReg(2, 0xc);
				*plVar22 = lVar3;
				lVar3 = getCopReg(2, 0xd);
				plVar22[1] = lVar3;
				lVar3 = getCopReg(2, 0xe);
				plVar22[2] = lVar3;
				4
				lVar3 = getCopReg(2, 0x11);
				*plVar23 = lVar3;
				lVar3 = getCopReg(2, 0x12);
				plVar23[1] = lVar3;
				lVar3 = getCopReg(2, 0x13);
				plVar23[2] = lVar3;
				*/
			}

			if (iVar26 < 27)
			{
				vert2 += 3;

				plVar23 = plVar23 + 3;
				plVar22 = plVar22 + 3;
				iVar26 = iVar26 + 3;

				gte_ldv3(&vert2[0], &vert2[1], &vert2[2]);
				gte_rtpt();

				/*
				setCopReg(2, in_zero, *(undefined4 *)pSVar24);
				setCopReg(2, in_at, *(undefined4 *)&vert2[3].vz);

				setCopReg(2, (uint)bVar2, *(undefined4 *)(vert2 + 4));
				setCopReg(2, lVar9, *(undefined4 *)&vert2[4].vz);

				setCopReg(2, boneId, *(undefined4 *)(vert2 + 5));
				setCopReg(2, v1, *(undefined4 *)&vert2[5].vz);

				copFunction(2, 0x280030);
				*/
			}

			boneId = *piVar25;
			if ((boneId == 4) &&
				(v1 = 1, lVar9 = LONG_ARRAY_1f800210[0],
				LONG_ARRAY_1f800210[0] <= switch_detail_distance >> 1))
			{
				local_38 = 1;
			}
			else
			{
				DrawBodySprite(pPed, boneId, (VERTTYPE*)&outlongs[0], (VERTTYPE*)&outlongs[1], *zbuff, zbuff[1]);
			}

			outlongs += 2;;
			zbuff += 2;
			iVar13--;
			piVar25++;
		} while (-1 < iVar13);

		if (local_38 != 0) 
		{
			bAllreadyRotated = 0;
			DoCivHead(pPed, SVECTOR_ARRAY_1f800090 + 5, SVECTOR_ARRAY_1f800090 + 4);

			ppos.vx = 0;
			ppos.vy = 0;
			ppos.vz = 0;

			gte_SetTransVector(&ppos);
		}

		ppos.vx = (pPed->position).vx;
		ppos.vy = (pPed->position).vy;
		ppos.vz = (pPed->position).vz;
		boneId = pPed->frame1 & 0xf;
		uVar15 = boneId * 2;
		iVar26 = MapHeight(&ppos);

		cv.b = 40;
		cv.g = 40;
		cv.r = 40;

		ppos.vx = ppos.vx - camera_position.vx;
		ppos.vy = (10 - iVar26) - camera_position.vy;
		ppos.vz = ppos.vz - camera_position.vz;

		if (uVar15 < 8)
			size = uVar15 + 0x50;
		else
			size = boneId * -2 + 0x70;

		RoundShadow(&ppos, _cv, size);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetSkelModelPointers(int type /*$a0*/)
 // line 2011, offset 0x00069ad8
	/* begin block 1 */
		// Start line: 7522
	/* end block 1 */
	// End Line: 7523

	/* begin block 2 */
		// Start line: 7524
	/* end block 2 */
	// End Line: 7525

// [D]
void SetSkelModelPointers(int type)
{
	if (type == OTHER_MODEL) 
	{
		Skel[2].pModel = &pmJerichoModels[0];
		Skel[4].pModel = &pmJerichoModels[1];
		Skel[6].pModel = &pmJerichoModels[2];
		Skel[7].pModel = &pmJerichoModels[3];
		Skel[10].pModel = &pmJerichoModels[4];
		Skel[11].pModel = &pmJerichoModels[5];
		Skel[14].pModel = NULL;
	}
	else
	{
		Skel[2].pModel = &pmTannerModels[0];
		Skel[4].pModel = &pmTannerModels[1];
		Skel[6].pModel = &pmTannerModels[8];
		Skel[7].pModel = &pmTannerModels[9];
		Skel[10].pModel = &pmTannerModels[2];
		Skel[11].pModel = &pmTannerModels[3];
		Skel[14].pModel = &pmTannerModels[15];
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawTanner(struct PEDESTRIAN *pPed /*$s2*/)
 // line 2041, offset 0x000678d0
	/* begin block 1 */
		// Start line: 2042
		// Start offset: 0x000678D0
		// Variables:
	// 		struct VECTOR v; // stack offset -112
	// 		struct CVECTOR cV; // stack offset -96
	// 		struct MATRIX mRotStore; // stack offset -88
	// 		struct MATRIX iMatrix; // stack offset -56

		/* begin block 1.1 */
			// Start line: 2042
			// Start offset: 0x000678D0
		/* end block 1.1 */
		// End offset: 0x000679E0
		// End Line: 2061

		/* begin block 1.2 */
			// Start line: 2067
			// Start offset: 0x000679E0
			// Variables:
		// 		int cx; // $a2
		// 		int sx; // $t0
		// 		int cy; // $a0
		// 		int sy; // $t2
		// 		int cz; // $t5
		// 		int sz; // $s0
		// 		int stmp; // $v1
		/* end block 1.2 */
		// End offset: 0x000679E0
		// End Line: 2067
	/* end block 1 */
	// End offset: 0x00067D44
	// End Line: 2113

	/* begin block 2 */
		// Start line: 5129
	/* end block 2 */
	// End Line: 5130

int iCurrBone = 0;

// [D]
void DrawTanner(PEDESTRIAN *pPed)
{
	int iVar1;
	VECTOR v;
	CVECTOR cV;

	bDoingShadow = 0;

	SetupTannerSkeleton(pPed);

	SetSkelModelPointers(pPed->pedType);

	//Skel[4].pModel = Skel[4].pModel + 1;
	newRotateBones(pPed, Skel + 1);

	// [A] I don't know but it works
	gte_SetRotMatrix(&inv_camera_matrix);

	iCurrBone = 0;
	newShowTanner(pPed);

	v.vx = (pPed->position.vx - camera_position.vx) + Skel[0].pvOrigPos->vx;
	v.vz = (pPed->position.vz - camera_position.vz) + Skel[0].pvOrigPos->vz;

	bDoingShadow = 1;
	v.vy = -camera_position.vy - MapHeight((VECTOR *)&pPed->position);

	if (pPed->padId == 0) 
	{
		if (gTimeOfDay == 3)
		{
			cV.b = 12;
			cV.g = 12;
			cV.r = 12;
			TannerShadow(pPed, &v, moon_position + GameLevel, &cV, pPed->dir.vy);
		}
		else 
		{
			cV.b = 32;
			cV.g = 32;
			cV.r = 32;
			TannerShadow(pPed, &v, sun_position + GameLevel, &cV, pPed->dir.vy);
		}
	}
	bDoingShadow = 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ DrawCharacter(struct PEDESTRIAN *pPed /*$s1*/)
 // line 2120, offset 0x00067d44
	/* begin block 1 */
		// Start line: 2121
		// Start offset: 0x00067D44
		// Variables:
	// 		struct MATRIX mRotStore; // stack offset -128
	// 		struct MATRIX iMatrix; // stack offset -96
	// 		struct CVECTOR cV; // stack offset -64
	// 		struct VECTOR v; // stack offset -56

		/* begin block 1.1 */
			// Start line: 2121
			// Start offset: 0x00067D44
			// Variables:
		// 		int cx; // $t0
		// 		int sx; // $a3
		// 		int cy; // $a0
		// 		int sy; // $t2
		// 		int cz; // $a2
		// 		int sz; // $t7
		// 		int stmp; // $v1
		/* end block 1.1 */
		// End offset: 0x00067D44
		// End Line: 2121

		/* begin block 1.2 */
			// Start line: 2175
			// Start offset: 0x00068134
			// Variables:
		// 		struct CVECTOR cv; // stack offset -40
		// 		struct VECTOR pos; // stack offset -32
		// 		int phase; // $s0
		/* end block 1.2 */
		// End offset: 0x000681D0
		// End Line: 2189
	/* end block 1 */
	// End offset: 0x000681EC
	// End Line: 2193

	/* begin block 2 */
		// Start line: 5336
	/* end block 2 */
	// End Line: 5337

	/* begin block 3 */
		// Start line: 5344
	/* end block 3 */
	// End Line: 5345

// [D]
int DrawCharacter(PEDESTRIAN *pPed)
{
	int iVar1;
	uint uVar2;
	ushort size;
	uint uVar8;

	CVECTOR cV;
	VECTOR v;
	CVECTOR cv;
	VECTOR pos;

	SetupTannerSkeleton(pPed);
	SetSkelModelPointers(pPed->pedType);
	newRotateBones(pPed, Skel + 1);

	// [A] I don't know but it works
	gte_SetRotMatrix(&inv_camera_matrix);

	iCurrBone = 0;
	newShowTanner(pPed);

	if (pUsedPeds->pNext == NULL && pPed->pedType == TANNER_MODEL)
	{
		v.vx = (pPed->position.vx - camera_position.vx) + Skel[0].pvOrigPos->vx;
		v.vz = (pPed->position.vz - camera_position.vz) + Skel[0].pvOrigPos->vz;

		bDoingShadow = 1;
		v.vy = -camera_position.vy - MapHeight((VECTOR *)&pPed->position);

		if (gTimeOfDay == 3)
		{
			cV.b = 12;
			cV.g = 12;
			cV.r = 12;
			TannerShadow(pPed, &v, moon_position + GameLevel, &cV, (pPed->dir).vy);
		}
		else 
		{
			cV.b = 32;
			cV.g = 32;
			cV.r = 32;
			TannerShadow(pPed, &v, sun_position + GameLevel, &cV, (pPed->dir).vy);
		}

		bDoingShadow = 0;
	}
	else if (pPed->pedType == CIVILIAN)
	{
		pos.vx = pPed->position.vx;
		pos.vy = pPed->position.vy;
		pos.vz = pPed->position.vz;

		uVar2 = pPed->frame1 & 7;
		uVar8 = uVar2 * 2;

		cv.b = 40;
		cv.g = 40;
		cv.r = 40;
		pos.vx = pos.vx - camera_position.vx;
		pos.vy = (0x1e - MapHeight(&pos)) - camera_position.vy;
		pos.vz = pos.vz - camera_position.vz;

		if (uVar8 < 8) 
			size = uVar8 | 0x50;
		else
			size = uVar2 * -2 + 0x60;

		RoundShadow(&pos, &cv, size);
	}

	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitTannerShadow()
 // line 2201, offset 0x000681ec
	/* begin block 1 */
		// Start line: 2203
		// Start offset: 0x000681EC
		// Variables:
	// 		struct CVECTOR cV; // stack offset -8
	// 		int i; // $a3
	/* end block 1 */
	// End offset: 0x00068358
	// End Line: 2247

	/* begin block 2 */
		// Start line: 5576
	/* end block 2 */
	// End Line: 5577

	/* begin block 3 */
		// Start line: 5585
	/* end block 3 */
	// End Line: 5586

	/* begin block 4 */
		// Start line: 5586
	/* end block 4 */
	// End Line: 5587

	/* begin block 5 */
		// Start line: 5589
	/* end block 5 */
	// End Line: 5590

/* WARNING: Unknown calling convention yet parameter storage is locked */

POLY_FT4 ft4TannerShadow[2];
extern TEXTURE_DETAILS tannerShadow_texture;
RECT16 rectTannerWindow;
TILE tileTannerClear[2];

// [D]
void InitTannerShadow(void)
{
	ushort uVar1;
	ushort uVar2;
	unsigned char uVar3;
	unsigned char brightness;
	TILE *tile;
	POLY_FT4 *poly;
	int i;
	uint uVar5;
	unsigned char uVar6;
	unsigned char uVar7;
	unsigned char uVar8;

	if (gTimeOfDay == 3)
		brightness = 12;
	else
		brightness = 32;

	poly = ft4TannerShadow;
	i = 1;

	uVar3 = tannerShadow_texture.coords.u0;
	uVar8 = tannerShadow_texture.coords.u0 + 63;
	uVar7 = tannerShadow_texture.coords.v0 + 127;
	uVar6 = tannerShadow_texture.coords.v0 + 32;

	uVar1 = tpagepos[nperms + 1].x;
	uVar5 = (uint)(ushort)tpagepos[nperms + 1].y + 128;
	uVar2 = (ushort)uVar5;

	do {
		
		rectTannerWindow.w = 64;
		rectTannerWindow.h = 128;
		rectTannerWindow.x = uVar1;
		rectTannerWindow.y = uVar2;

		poly->u0 = uVar8;
		poly->v0 = uVar6;
		poly->u1 = uVar3;
		poly->v1 = uVar6;
		poly->u2 = uVar8;
		poly->v2 = uVar7;
		poly->u3 = uVar3;
		poly->v3 = uVar7;

		poly->tpage = (short)(uVar2 & 0x100) >> 4 | (ushort)(((uint)uVar1 & 0x3ff) >> 6) | 0x100 | (ushort)((uVar5 & 0x200) << 2);

		setPolyFT4(poly);
		setSemiTrans(poly, 1);

		poly->r0 = brightness;
		poly->g0 = brightness;
		poly->b0 = brightness;

		poly++;
		i--;
	} while (-1 < i);

	tile = tileTannerClear;
	i = 1;
	do {

		setTile(tile);

		tile->x0 = 0;
		tile->y0 = 0;
		tile->w = 0x40;
		tile->h = 0x80;
		tile->r0 = 0;
		tile->g0 = 0;
		tile->b0 = 0;
		i--;
		tile++;
	} while (-1 < i);
}



// decompiled code
// original method signature: 
// void /*$ra*/ TannerShadow(struct VECTOR *pPedPos /*$s6*/, struct SVECTOR *pLightPos /*$s7*/, struct CVECTOR *col /*$a2*/, short angle /*$a3*/)
 // line 2258, offset 0x00068358
	/* begin block 1 */
		// Start line: 2259
		// Start offset: 0x00068358
		// Variables:
	// 		int z; // $a1
	// 		int z0; // stack offset -72
	// 		int z1; // stack offset -68
	// 		int z2; // stack offset -64
	// 		int z3; // stack offset -60
	// 		struct SVECTOR vert[4]; // stack offset -272
	// 		struct VECTOR d; // stack offset -240
	// 		struct DR_ENV *pDE; // $s3
	// 		struct DRAWENV drEnv; // stack offset -224
	// 		struct VECTOR cp; // stack offset -128
	// 		struct SVECTOR ca; // stack offset -112
	// 		struct VECTOR v1; // stack offset -104
	// 		int i; // $s4
	// 		struct VECTOR myVector; // stack offset -88
	// 		int avalue2; // $v0
	// 		int w; // $v1

		/* begin block 1.1 */
			// Start line: 2375
			// Start offset: 0x00068818
		/* end block 1.1 */
		// End offset: 0x00068818
		// End Line: 2375
	/* end block 1 */
	// End offset: 0x00068B2C
	// End Line: 2434

	/* begin block 2 */
		// Start line: 5725
	/* end block 2 */
	// End Line: 5726

	/* begin block 3 */
		// Start line: 5737
	/* end block 3 */
	// End Line: 5738

/* WARNING: Could not reconcile some variable overlaps */

// [D]
void TannerShadow(PEDESTRIAN* pDrawingPed, VECTOR *pPedPos, SVECTOR *pLightPos, CVECTOR *col, short angle)
{
	char cVar9;
	DR_ENV* dr_env;
	SVECTOR vert[4];
	VECTOR d;
	DRAWENV drEnv;
	VECTOR cp;
	SVECTOR ca;
	VECTOR v1;
	VECTOR myVector;
	int z0;
	int z1;
	int z2;
	int z3;
	SVECTOR* local_2c;
	static int Tangle = 0;
	int i;
	int cn, sn;
	int vx, vz;

	// [A] not supported by emulator
	// proposed change: double buffering of VRAM (one used as render target, second as texture)
	return;

	memset(&d, 0, sizeof(VECTOR));
	memset(&myVector, 0, sizeof(VECTOR));

	SetDefDrawEnv(&drEnv, 0, current->draw.clip.y, 320, 256);

	dr_env = (DR_ENV*)current->primptr;
	SetDrawEnv(dr_env, &drEnv);
	
	addPrim(current->ot + 0x107f, dr_env);
	current->primptr += sizeof(DR_ENV);

	Tangle = ratan2(-pLightPos->vx, pLightPos->vz);

	vert[0].vx = -128;
	vert[0].vy = 0;
	vert[0].vz = -320;

	vert[1].vx = 128;
	vert[1].vy = 0;
	vert[1].vz = -320;

	vert[2].vx = -128;
	vert[2].vy = 0;
	vert[2].vz = 18;

	vert[3].vx = 128;
	vert[3].vy = 0;
	vert[3].vz = 18;

	for (i = 0; i < 4; i++)
	{
		cn = rcos(Tangle);
		sn = rsin(Tangle);

		vx = vert[i].vx;
		vz = vert[i].vz;

		vert[i].vx = (vx * cn >> 0xc) - (vz * sn >> 0xc);
		vert[i].vz = (vx * sn >> 0xc) + (vz * cn >> 0xc);

		vert[i].vx += pPedPos->vx;
		vert[i].vy += pPedPos->vy;
		vert[i].vz += pPedPos->vz;
	}

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&d);

	gte_ldv3(&vert[0], &vert[1], &vert[2]);

	gte_rtpt();

	gte_stsxy3(&ft4TannerShadow[current->id].x0, &ft4TannerShadow[current->id].x1, &ft4TannerShadow[current->id].x2);

	gte_stsz3(&z0, &z1, &z2);

	gte_ldv0(&vert[3]);

	gte_rtps();

	gte_stsxy(&ft4TannerShadow[current->id].x3);

	gte_stsz(&z3);

	if (z0 < z1)
		z0 = (z0 + z1) / 2;
	else
		z1 = (z0 + z1) / 2;

	if (z2 < z3)
		z2 = (z2 + z3) / 2;
	else
		z3 = (z2 + z3) / 2;

	if (z0 > 28)
		z0 = z0 - 20;
	else
		z0 = 8;

	if (z1 > 28)
		z1 = z1 - 20;
	else
		z1 = 8;

	if (z2 > 28)
		z2 = z2 - 20;
	else
		z2 = 8;

	if (z3 > 28)
		z3 = z3 - 20;
	else
		z3 = 8;

	SubdivShadow(z0, z1, z2, z3, ft4TannerShadow + current->id);

	cp = camera_position;
	ca = camera_angle;

	camera_position.vx = pDrawingPed->position.vx + (pLightPos->vx * 110 >> 0xc);
	camera_position.vy = pDrawingPed->position.vy + (pLightPos->vy * 110 >> 0xc);
	camera_position.vz = pDrawingPed->position.vz + (pLightPos->vz * 110 >> 0xc);

	myVector.vx = player[0].pos[0];
	myVector.vy = player[0].pos[1] - 172;
	myVector.vz = player[0].pos[2];

	player[0].cameraPos.vx = camera_position.vx;
	player[0].cameraPos.vy = camera_position.vy;
	player[0].cameraPos.vz = camera_position.vz;

	SetBasePos(&myVector);
	cVar9 = tracking_car;

	setCopControlWord(2, 0xc000, 0x200000); // hmmmm?
	setCopControlWord(2, 0xc800, 0x800000);

	tracking_car = 1;
	PlaceCameraAtLocation(&player[0], 0);
	tracking_car = cVar9;

	newShowTanner(pDrawingPed);

	addPrim(current->ot + 0x107f, &tileTannerClear[current->id]);

	camera_position = cp;
	camera_angle = ca;
	player[0].cameraPos = cp;

	// restore camera
	BuildWorldMatrix();
	InitCamera(&player[0]);

	setCopControlWord(2, 0xc000, 0xa00000);
	setCopControlWord(2, 0xc800, 0x800000);

	SetDefDrawEnv(&drEnv, rectTannerWindow.x, rectTannerWindow.y, rectTannerWindow.w, rectTannerWindow.h);
	dr_env = (DR_ENV*)current->primptr;
	SetDrawEnv(dr_env, &drEnv);
	
	addPrim(current->ot + 0x107f, dr_env);
	current->primptr += sizeof(DR_ENV);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoCivHead(struct SVECTOR *vert1 /*$s1*/, struct SVECTOR *vert2 /*$s3*/)
 // line 2442, offset 0x00068b2c
	/* begin block 1 */
		// Start line: 2443
		// Start offset: 0x00068B2C
		// Variables:
	// 		struct VECTOR headpos; // stack offset -184
	// 		struct SVECTOR final_rotation; // stack offset -168
	// 		struct SVECTOR spos1; // stack offset -160
	// 		struct MODEL *model; // $s5
	// 		struct MATRIX work2matrix; // stack offset -152
	// 		struct MATRIX mRotStore; // stack offset -120
	// 		struct VECTOR pos1; // stack offset -88
	// 		int pal; // $v1
	// 		int ci; // $s6

		/* begin block 1.1 */
			// Start line: 2495
			// Start offset: 0x00068D38
			// Variables:
		// 		int cx; // $v1
		// 		int sx; // $a0
		// 		int cy; // $a1
		// 		int sy; // $t0
		// 		int cz; // $t3
		// 		int sz; // $t6
		// 		int stmp; // $a3
		/* end block 1.1 */
		// End offset: 0x00068D38
		// End Line: 2495

		/* begin block 1.2 */
			// Start line: 2507
			// Start offset: 0x00068F98
			// Variables:
		// 		int cx; // $v1
		// 		int sx; // $t3
		// 		int cy; // $t1
		// 		int sy; // $a3
		// 		int stmp; // $v0
		/* end block 1.2 */
		// End offset: 0x00068F98
		// End Line: 2507

		/* begin block 1.3 */
			// Start line: 2535
			// Start offset: 0x00069274
			// Variables:
		// 		struct MATRIX comb; // stack offset -72
		/* end block 1.3 */
		// End offset: 0x00069274
		// End Line: 2537
	/* end block 1 */
	// End offset: 0x0006940C
	// End Line: 2554

	/* begin block 2 */
		// Start line: 6379
	/* end block 2 */
	// End Line: 6380

	/* begin block 3 */
		// Start line: 6388
	/* end block 3 */
	// End Line: 6389

	/* begin block 4 */
		// Start line: 6400
	/* end block 4 */
	// End Line: 6401

/* WARNING: Could not reconcile some variable overlaps */

extern _pct plotContext;

// [A]
void DoCivHead(PEDESTRIAN *pPed, SVECTOR *vert1, SVECTOR *vert2)
{
	SVECTOR spos;
	VECTOR pos;
	SVECTOR headpos;
	MATRIX* pHeadRot;
	int oldcombointensity;

	if (gPed1HeadModelPtr == NULL)
		return;

	if (bAllreadyRotated) // not needed to rotate vert1
	{
		pHeadRot = (MATRIX*)&matrixtable[((pPed->dir.vy - pPed->head_rot) / 64) & 0x3F];
		headpos.vx = vert1->vx;
		headpos.vy = vert1->vy;
		headpos.vz = vert1->vz;
	}
	else
	{
		pHeadRot = (MATRIX*)&matrixtable[((pPed->dir.vy - pPed->head_rot) / 64) & 0x3F];
		gte_SetRotMatrix(&matrixtable[((pPed->dir.vy) / 64) & 0x3F]);

		gte_ldv0(vert1);
		gte_rtv0();

		gte_stsv(&headpos);
	}

	spos.vx = headpos.vx + pPed->position.vx - camera_position.vx;
	spos.vy = headpos.vy + pPed->position.vy - camera_position.vy;
	spos.vz = headpos.vz + pPed->position.vz - camera_position.vz;

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_ldv0(&spos);
	gte_rtv0();

	gte_stlvnl(&pos);

	gte_SetTransVector(&pos);

	int flags = 0;

	if ((pPed->pallet & 0xf))
	{
		flags = 0x10; // set custom palette flag
		plotContext.clut = civ_clut[0][texturePedHead.texture_number][pPed->pallet & 0xf] << 0x10;
	}
	
	oldcombointensity = combointensity;

	if (gNight != 0)
		combointensity = 0x404040;

	RenderModel(gPed1HeadModelPtr, pHeadRot, &pos, 1, flags, 0);

	combointensity = oldcombointensity;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawObject(struct MODEL *model /*$t8*/, struct MATRIX *matrix /*$a1*/, struct VECTOR *pos /*$a2*/, int z_correct /*$a3*/)
 // line 2562, offset 0x00069438
	/* begin block 1 */
		// Start line: 2563
		// Start offset: 0x00069438
		// Variables:
	// 		struct DVECTOR *outpoints; // $t7
	// 		short *zbuff; // $t5
	// 		struct SVECTOR *verts; // $t6
	// 		char *polys; // $s0
	// 		int cnt3; // $t1
	// 		int i; // $s1
	// 		int z0; // stack offset -40
	// 		int z1; // stack offset -36
	// 		int z2; // stack offset -32
	// 		long *outlongs; // $s2
	// 		int z; // stack offset -28

		/* begin block 1.1 */
			// Start line: 2654
			// Start offset: 0x000697D4
		/* end block 1.1 */
		// End offset: 0x00069840
		// End Line: 2663
	/* end block 1 */
	// End offset: 0x00069874
	// End Line: 2683

	/* begin block 2 */
		// Start line: 6676
	/* end block 2 */
	// End Line: 6677

// [A] - not needed anymore
void DrawObject(MODEL *model, MATRIX *matrix, VECTOR *pos, int z_correct)
{
	UNIMPLEMENTED();
	/*
	undefined4 uVar1;
	int iVar2;
	short sVar3;
	short sVar4;
	short sVar5;
	short sVar6;
	undefined4 in_zero;
	undefined4 in_at;
	uint uVar7;
	uint uVar8;
	undefined2 *puVar9;
	int iVar10;
	undefined4 *puVar11;
	undefined4 *puVar12;
	undefined4 *puVar13;
	uint uVar14;
	undefined4 *puVar15;
	undefined4 *puVar16;
	undefined4 *puVar17;
	undefined4 *puVar18;
	uint uVar19;
	int local_28;
	int local_24;
	uint local_20;

	uVar7 = 0xaaaaaaab;
	puVar18 = (undefined4 *)model->vertices;
	uVar8 = (uint)model->num_vertices / 3;
	uVar19 = 0;
	sVar3 = (short)z_correct;
	if (uVar8 != 0) {
		puVar13 = &DAT_1f80004c;
		puVar12 = &DAT_1f800048;
		puVar11 = &DAT_1f800044;
		puVar9 = &DAT_1f800240;
		puVar17 = puVar18 + 4;
		puVar16 = puVar18 + 2;
		uVar14 = uVar8;
		puVar15 = puVar18;
		do {
			setCopReg(2, in_zero, *puVar15);
			setCopReg(2, in_at, puVar15[1]);
			setCopReg(2, uVar7, *puVar16);
			setCopReg(2, uVar8, puVar16[1]);
			setCopReg(2, puVar9, *puVar17);
			setCopReg(2, puVar11, puVar17[1]);
			copFunction(2, 0x280030);
			puVar9[-3] = (short)(local_28 >> 3) + sVar3;
			puVar9[-2] = (short)(local_24 >> 3) + sVar3;
			puVar9[-1] = (short)((int)local_20 >> 3) + sVar3;
			uVar1 = getCopReg(2, 0xc);
			*puVar11 = uVar1;
			uVar1 = getCopReg(2, 0xd);
			*puVar12 = uVar1;
			uVar1 = getCopReg(2, 0xe);
			*puVar13 = uVar1;
			local_28 = getCopReg(2, 0x11);
			local_24 = getCopReg(2, 0x12);
			uVar8 = getCopReg(2, 0x13);
			if (zVal < local_28) {
				zVal = local_28;
			}
			if (zVal < local_24) {
				zVal = local_24;
			}
			uVar7 = (uint)(zVal < (int)uVar8);
			if (zVal < (int)uVar8) {
				zVal = uVar8;
			}
			uVar14 = uVar14 - 1;
			puVar13 = puVar13 + 3;
			puVar12 = puVar12 + 3;
			puVar11 = puVar11 + 3;
			puVar9 = puVar9 + 3;
			puVar17 = puVar17 + 6;
			puVar16 = puVar16 + 6;
			puVar15 = puVar15 + 6;
			uVar19 = uVar19 + 3;
			local_20 = uVar8;
		} while (0 < (int)uVar14);
	}
	iVar10 = (uint)model->num_vertices - uVar19;
	sVar4 = (short)(local_28 >> 3);
	sVar5 = (short)(local_24 >> 3);
	sVar6 = (short)((int)local_20 >> 3);
	if (iVar10 == 1) {
		setCopReg(2, in_zero, puVar18[uVar19 * 2]);
		setCopReg(2, in_at, (puVar18 + uVar19 * 2)[1]);
		copFunction(2, 0x180001);
		(&DAT_1f80023a)[uVar19] = sVar4 + sVar3;
		(&DAT_1f80023c)[uVar19] = sVar5 + sVar3;
		(&DAT_1f80023e)[uVar19] = sVar6 + sVar3;
		uVar1 = getCopReg(2, 0xe);
		(&DAT_1f800044)[uVar19] = uVar1;
		iVar10 = getCopReg(2, 0x13);
		if (zVal < iVar10) {
			zVal = iVar10;
		}
		(&DAT_1f800240)[uVar19] = (short)(iVar10 >> 3);
	}
	else {
		if (iVar10 < 2) {
			if ((uint)model->num_vertices == uVar19) {
				(&DAT_1f80023a)[uVar19] = sVar4 + sVar3;
				(&DAT_1f80023c)[uVar19] = sVar5 + sVar3;
				(&DAT_1f80023e)[uVar19] = sVar6 + sVar3;
			}
		}
		else {
			if (iVar10 == 2) {
				setCopReg(2, in_zero, puVar18[uVar19 * 2]);
				setCopReg(2, in_at, (puVar18 + uVar19 * 2)[1]);
				copFunction(2, 0x180001);
				(&DAT_1f80023a)[uVar19] = sVar4 + sVar3;
				(&DAT_1f80023c)[uVar19] = sVar5 + sVar3;
				(&DAT_1f80023e)[uVar19] = sVar6 + sVar3;
				uVar1 = getCopReg(2, 0xe);
				(&DAT_1f800044)[uVar19] = uVar1;
				iVar10 = getCopReg(2, 0x13);
				if (zVal < iVar10) {
					zVal = iVar10;
				}
				(&DAT_1f800240)[uVar19] = (short)(iVar10 >> 3) + sVar3;
				setCopReg(2, in_zero, puVar18[uVar19 * 2 + 2]);
				setCopReg(2, in_at, (puVar18 + uVar19 * 2 + 2)[1]);
				copFunction(2, 0x180001);
				uVar1 = getCopReg(2, 0xe);
				(&DAT_1f800048)[uVar19] = uVar1;
				iVar10 = getCopReg(2, 0x13);
				if (zVal < iVar10) {
					zVal = iVar10;
				}
				(&DAT_1f800242)[uVar19] = (short)(iVar10 >> 3) + sVar3;
			}
		}
	}
	iVar10 = model->poly_block;
	DAT_1f80001c = &DAT_1f800240;
	uVar8 = (uint)model->num_polys;
	DAT_1f800018 = model;
	while (uVar8 = uVar8 - 1, uVar8 != 0xffffffff) {
		setCopReg(2, 0x6000, (&DAT_1f800044)[*(byte *)(iVar10 + 4)]);
		setCopReg(2, 0x7000, (&DAT_1f800044)[*(byte *)(iVar10 + 6)]);
		setCopReg(2, 0x6800, (&DAT_1f800044)[*(byte *)(iVar10 + 5)]);
		copFunction(2, 0x1400006);
		iVar2 = getCopReg(2, 0x18);
		DAT_1f80003c = iVar10;
		if (0 < iVar2) {
			wjmDraw3();
		}
		iVar10 = iVar10 + 0x14;
	}
	TransparentObject = '\0';
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ wjmDraw3()
 // line 2690, offset 0x00069874
	/* begin block 1 */
		// Start line: 2692
		// Start offset: 0x00069874
		// Variables:
	// 		struct POLYFT3 *src; // $a3
	// 		short *zbuff; // $t2
	// 		long *outlongs; // $a2
	// 		struct POLY_FT3 *prims; // $t1
	// 		unsigned long clut; // $t0
	// 		unsigned long tpage; // $a1
	// 		int z; // $a2
	/* end block 1 */
	// End offset: 0x00069A38
	// End Line: 2724

	/* begin block 2 */
		// Start line: 6971
	/* end block 2 */
	// End Line: 6972

	/* begin block 3 */
		// Start line: 6979
	/* end block 3 */
	// End Line: 6980

	/* begin block 4 */
		// Start line: 6980
	/* end block 4 */
	// End Line: 6981

	/* begin block 5 */
		// Start line: 6982
	/* end block 5 */
	// End Line: 6983

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [A] - not needed anymore
void wjmDraw3(void)
{
	UNIMPLEMENTED();
	/*
	undefined2 uVar1;
	int iVar2;
	DB *pDVar3;
	int i;
	uint uVar5;
	uint uVar6;
	uint *puVar7;

	i = DAT_1f80003c;
	iVar2 = DAT_1f80001c;
	puVar7 = (uint *)current->primptr;
	puVar7[1] = combointensity;
	*(char *)((int)puVar7 + 3) = '\a';
	*(char *)((int)puVar7 + 7) = '$';
	if (palnumber == -1) {
		uVar5 = (uint)*(byte *)(i + 1);
		uVar6 = (uint)(ushort)(&texture_cluts)[uVar5 * 0x20 + (uint)*(byte *)(i + 2)] << 0x10;
	}
	else {
		uVar5 = (uint)*(byte *)(i + 1);
		uVar6 = palnumber;
	}
	uVar1 = (&texture_pages)[uVar5];
	puVar7[2] = (&DAT_1f800044)[*(byte *)(i + 4)];
	puVar7[3] = *(ushort *)(i + 8) | uVar6;
	puVar7[4] = (&DAT_1f800044)[*(byte *)(i + 5)];
	puVar7[5] = CONCAT22(uVar1, *(undefined2 *)(i + 10));
	puVar7[6] = (&DAT_1f800044)[*(byte *)(i + 6)];
	puVar7[7] = (uint)*(ushort *)(i + 0xc);
	pDVar3 = current;
	iVar2 = ((int)*(short *)((uint)*(byte *)(i + 4) * 2 + iVar2) +
		(int)*(short *)((uint)*(byte *)(i + 5) * 2 + iVar2) +
		(int)*(short *)((uint)*(byte *)(i + 6) * 2 + iVar2)) / 3;
	*puVar7 = *puVar7 & 0xff000000 | current->ot[iVar2] & 0xffffff;
	pDVar3->ot[iVar2] = pDVar3->ot[iVar2] & 0xff000000 | (uint)puVar7 & 0xffffff;
	pDVar3->primptr = pDVar3->primptr + 0x20;
	return;
	*/
}





