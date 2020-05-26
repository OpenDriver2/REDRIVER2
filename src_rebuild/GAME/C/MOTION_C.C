#include "THISDUST.H"
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
PEDESTRIAN *pDrawingPed = NULL;

// [D] [A] change to VERTTYPE?
void DrawBodySprite(int boneId, long v1, long v2, int sz, int sy)
{
	uint uVar1;
	long lVar2;
	unsigned char bVar3;
	uint uVar4;
	int iVar5;
	uint uVar6;
	int iVar7;
	POLY_FT4 *prims;
	int iVar8;
	int iVar9;
	uint uVar10;
	TEXTURE_DETAILS *body_texture;
	int x;
	int y;
	int iVar11;
	uint uVar12;
	int iVar13;
	int y1;
	int z1;

	uVar12 = v1 & 0xffff0000;
	iVar11 = v1 * 0x10000;
	uVar1 = v2 & 0xffff0000;
	y = iVar11 + v2 * -0x10000;
	x = uVar12 - uVar1;
	uVar10 = boneId & 0x7f;
	body_texture = MainPed[uVar10].ptd;
	lVar2 = ratan2(y, x);

	if (bDoingShadow == 0) 
		iVar5 = gCurrentZ + (scr_z >> 2);
	else 
		iVar5 = sz + (scr_z >> 2);

	iVar13 = (scr_z << 0xc) / iVar5;

	if (uVar10 == 2) {
		iVar13 = iVar13 + ((int)((uint)*(ushort *)((int)rcossin_tbl +((pDrawingPed->dir.vy + camera_angle.vy) * 8 & 0x3ff8U) + 2) << 0x10) >> 0x16);
	}
	prims = (POLY_FT4 *)current->primptr;

	if (pDrawingPed->type == PED_ACTION_JUMP)
	{
		uVar6 = MainPed[uVar10].cWidth + 4;
	}
	else if (bDoingShadow == 0)
	{
		if ((pDrawingPed->flags & 0x8000U) == 0) 
		{
			if ((pDrawingPed->flags & 0x4000U) == 0)
				uVar6 = MainPed[uVar10].cWidth + 3;
			else 
				uVar6 = MainPed[uVar10].cWidth + 8;
		}
		else 
			uVar6 = MainPed[uVar10].cWidth - 3;
	}
	else
		uVar6 = MainPed[uVar10].cWidth;

	iVar7 = (int)(iVar13 * (int)rcossin_tbl[(-lVar2 & 0xfffU) * 2 + 1] * 3 * (uVar6 & 0x3f)) >> 9;
	bVar3 = MainPed[uVar10].cAdj & 0xf;
	iVar9 = y >> bVar3;
	iVar8 = x >> bVar3;
	iVar5 = (int)(iVar13 * rcossin_tbl[(-lVar2 & 0xfffU) * 2] * (uVar6 & 0x3f)) >> 8;

	if ((((uVar10 == 0x13) || (uVar10 == 0xf)) && (pDrawingPed->type != PED_ACTION_JUMP)) && (bDoingShadow == 0))
	{
		y = -y >> 3;
		x = -x >> 3;
	}
	else
	{
		uVar4 = (uint)(MainPed[uVar10].cAdj >> 4);
		y = y >> uVar4;
		x = x >> uVar4;
	}

	*(uint *)&prims->x0 = (uVar12 + iVar5 + iVar8 & 0xffff0000) + (iVar11 + iVar7 + iVar9 >> 0x10);
	*(uint *)&prims->x1 = ((uVar12 - iVar5) + iVar8 & 0xffff0000) + ((iVar11 - iVar7) + iVar9 >> 0x10);
	*(uint *)&prims->x2 = ((uVar1 + iVar5) - x & 0xffff0000) + ((v2 * 0x10000 + iVar7) - y >> 0x10);
	*(uint *)&prims->x3 = ((uVar1 - iVar5) - x & 0xffff0000) + ((v2 * 0x10000 - iVar7) - y >> 0x10);

	if (bDoingShadow == 0)
	{
		uVar12 = (uint)body_texture->tpageid << 0x10;
		if (MainPed[uVar10].texPal != NO_PAL) 
		{
			if (MainPed[uVar10].texPal == JEANS_PAL) 
			{
				bVar3 = pDrawingPed->pallet >> 4;
				uVar1 = (uint)bVar3;
			}
			else
			{
				bVar3 = pDrawingPed->pallet & 0xf;
				uVar1 = (uint)pDrawingPed->pallet & 0xf;
			}
			if (bVar3 != 0) 
			{
				uVar1 = (uint)civ_clut[body_texture->texture_number * 6 + uVar1] << 0x10;
				goto LAB_00065688;
			}
		}
		uVar1 = (uint)body_texture->clutid << 0x10;
	}
	else
	{
		uVar12 = gShadowTexturePage << 0x10;
		uVar1 = (uint)(ushort)texture_cluts[gShadowTexturePage * 0x20 + gShadowTextureNum] << 0x10;
	}
LAB_00065688:
	if (uVar10 == 4) 
	{
		if (bDoingShadow == 0)
		{
			x = (int)((int)camera_angle.vy + (int)(pDrawingPed->dir).vy & 0xfffU) >> 7;
			*(uint *)&prims->u0 = (*(ushort *)&body_texture->coords | uVar1) + x;
			*(uint *)&prims->u1 = (*(ushort *)&(body_texture->coords).u1 | uVar12) + x;
			*(uint *)&prims->u2 = (uint)*(ushort *)&(body_texture->coords).u2 + x;
			*(uint *)&prims->u3 = (uint)*(ushort *)&(body_texture->coords).u3 + x;
			goto LAB_000657dc;
		}
	}
	else 
	{
		if (bDoingShadow == 0) 
		{
			if (uVar10 == 2) {
				*(uint *)&prims->u0 = *(ushort *)&body_texture->coords | uVar1;
				*(uint *)&prims->u1 = *(ushort *)&(body_texture->coords).u1 | uVar12;
				*(uint *)&prims->u2 = (uint)*(ushort *)&(body_texture->coords).u2;
				*(uint *)&prims->u3 = (uint)*(ushort *)&(body_texture->coords).u3;
			}
			else {
				*(uint *)&prims->u0 = *(ushort *)&(body_texture->coords).u2 | uVar1;
				*(uint *)&prims->u1 = *(ushort *)&(body_texture->coords).u3 | uVar12;
				*(uint *)&prims->u2 = (uint)*(ushort *)&body_texture->coords;
				*(uint *)&prims->u3 = (uint)*(ushort *)&(body_texture->coords).u1;
			}
			goto LAB_000657dc;
		}
	}

	*(uint *)&prims->u0 = *(uint*)&shadowuv | uVar1;
	*(uint *)&prims->u1 = *(uint*)&shadowuv | uVar12;
	*(uint *)&prims->u2 = *(uint*)&shadowuv;
	*(uint *)&prims->u3 = *(uint*)&shadowuv;

LAB_000657dc:

	setPolyFT4(prims);

	if (gNight == 1) 
	{
		prims->r0 = 64;
		prims->g0 = 64;
	}
	else 
	{
		prims->r0 = (combointensity >> 0x10) & 0xFF;
		prims->g0 = (combointensity >> 8) & 0xFF;
	}

	prims->b0 = combointensity & 0xFF;

	if (bDoingShadow == 0)
	{
		x = sz + sy >> 4;
		addPrim(current->ot + x + ((int)uVar6 >> 5), prims);
	}
	else
		addPrim(current->ot + 0x107f, prims);

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
		else
		{
			pMVar5 = *pBVar2->pModel;
			local_a2_76 = (SVECTOR *)pMVar5->vertices;
			cTannerVNumbers[(uint)pBVar2->id & 0x7f] = iVar8;

			if (pMVar5->num_vertices != 0)
			{
				pSVar3 = vTannerList + iVar7;
				do {
					iVar8 = iVar8 + 1;
					iVar4 = iVar4 + 1;
					pSVar3->vx = local_a2_76->vx;
					iVar7 = iVar7 + 1;
					pSVar3->vy = local_a2_76->vy;
					psVar1 = &local_a2_76->vz;
					local_a2_76 = local_a2_76 + 1;
					pSVar3->vz = *psVar1;
					pSVar3 = pSVar3 + 1;
				} while (iVar4 < (int)(uint)pMVar5->num_vertices);
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
		local_t0_256 = *(MODEL **)((int)pmJerichoModels + iVar6);

		iVar7 = iVar7 + 1;
		if (local_t0_256 != NULL)
		{
			local_a2_308 = (SVECTOR *)local_t0_256->vertices;
			*(int *)((int)cJerichoVNumbers + iVar6) = iVar4;
			iVar6 = 0;

			if (local_t0_256->num_vertices != 0)
			{
				pSVar3 = vJerichoList + iVar8;
				do {
					iVar4 = iVar4 + 1;
					iVar6 = iVar6 + 1;
					pSVar3->vx = local_a2_308->vx;
					iVar8 = iVar8 + 1;
					pSVar3->vy = local_a2_308->vy;
					psVar1 = &local_a2_308->vz;
					local_a2_308 = local_a2_308 + 1;
					pSVar3->vz = *psVar1;
					pSVar3 = pSVar3 + 1;
				} while (iVar6 < (int)(uint)local_t0_256->num_vertices);
			}
		}
		iVar6 = iVar7 * 4;
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
void SetupTannerSkeleton(void)
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

	

	Skel[0].vOffset.vx = 0;
	Skel[0].vOffset.vy = 0;
	Skel[0].vOffset.vz = 0;
	Skel[0].vCurrPos.vz = -Skel[0].pvOrigPos->vz;

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

	SVECTOR_ARRAY_1f800008[0].vx = (Skel[1].pvOrigPos)->vx;
	SVECTOR_ARRAY_1f800008[0].vy = -(Skel[1].pvOrigPos)->vy;
	SVECTOR_ARRAY_1f800008[0].vz = -(Skel[1].pvOrigPos)->vz;

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

void newShowTanner(void)
{
	UNIMPLEMENTED();
	/*
	LIMBS LVar1;
	PEDESTRIAN *pPVar2;
	undefined4 in_zero;
	int iVar3;
	int zBias;
	short *psVar4;
	uint uVar5;
	int iVar6;
	int iVar7;
	MODEL *pMVar8;
	uint uVar9;
	BONE *pBVar10;
	VECTOR local_80;
	SVECTOR local_70;
	SVECTOR local_68;
	long local_60;
	long local_5c;
	int local_58;
	int local_54;
	undefined4 local_50;
	long local_4c;
	long local_48;
	int local_44;
	int local_40;
	undefined4 local_3c;
	long local_38;
	long local_34;
	int local_30;
	int local_2c;
	undefined4 local_28;

	DAT_1f800000 = (pDrawingPed->position).vx;
	DAT_1f800004 = (pDrawingPed->position).vy;
	DAT_1f800008 = (pDrawingPed->position).vz;
	DAT_1f800010 = camera_position.vx;
	DAT_1f800014 = camera_position.vy;
	DAT_1f800018 = camera_position.vz;
	DAT_1f800020 = (int)(Skel.pvOrigPos)->vx;
	DAT_1f800024 = -(int)(Skel.pvOrigPos)->vy;
	DAT_1f800028 = (int)(Skel.pvOrigPos)->vz;
	local_80.vz = 0;
	local_80.vy = 0;
	local_80.vx = 0;
	setCopControlWord(2, 0x2800, 0);
	setCopControlWord(2, 0x3000, 0);
	setCopControlWord(2, 0x3800, 0);
	zBias = 0;
	Skel.id = Skel.id | 0x80;
	iVar3 = 0;
	do {
		LVar1 = lRoutes[iVar3 + 1];
		iVar6 = 1;
		zBias = zBias + 1;
		pPVar2 = pDrawingPed;
		while (pDrawingPed = pPVar2, LVar1 != ROOT) {
			uVar5 = (uint)LVar1;
			pBVar10 = &Skel + uVar5;
			if (pBVar10->id < 0x7f) {
				uVar9 = (uint)*(byte *)((int)MissionName37 + iVar6 + iVar3 + 0x93);
				(&DAT_1f800020)[(uint)pBVar10->id * 4] =
					(&DAT_1f800020)[uVar9 * 4] + (&Skel)[uVar5].vCurrPos.vx;
				(&DAT_1f800024)[(uint)pBVar10->id * 4] =
					(&DAT_1f800024)[uVar9 * 4] + (&Skel)[uVar5].vCurrPos.vy;
				(&DAT_1f800028)[(uint)pBVar10->id * 4] =
					(&DAT_1f800028)[uVar9 * 4] + (&Skel)[uVar5].vCurrPos.vz;
				if ((pPVar2->pedType == TANNER_MODEL) && (pBVar10->id == HEAD)) {
					pPVar2->head_pos =
						(short)((ulonglong)((longlong)((&DAT_1f800024)[uVar9 * 4] + -0x5e) * 0x55555556) >>
							0x20) - (short)((&DAT_1f800024)[uVar9 * 4] + -0x5e >> 0x1f);
				}
				pMVar8 = *(&Skel)[uVar5].pModel;
				if (((((&Skel)[uVar5].pModel != (MODEL **)0x0) && (bDoingShadow == 0)) &&
					(pDrawingPed->pedType < OTHER_SPRITE)) && (player.cameraView != '\x02')) {
					psVar4 = (short *)pMVar8->vertices;
					iVar7 = 0;
					if (pMVar8->num_vertices != 0) {
						do {
							iVar7 = iVar7 + 1;
							*psVar4 = *psVar4 + ((*(short *)(&DAT_1f800020 + uVar9 * 4) + (short)DAT_1f800000) -
								(short)DAT_1f800010);
							psVar4[1] = psVar4[1] +
								((*(short *)(&DAT_1f800024 + uVar9 * 4) + (short)DAT_1f800004) -
								(short)DAT_1f800014);
							psVar4[2] = psVar4[2] +
								((*(short *)(&DAT_1f800028 + uVar9 * 4) + (short)DAT_1f800008) -
								(short)DAT_1f800018);
							psVar4 = psVar4 + 4;
						} while (iVar7 < (int)(uint)pMVar8->num_vertices);
					}
				}
				pBVar10->id = pBVar10->id | 0x80;
			}
			iVar6 = iVar6 + 1;
			LVar1 = lRoutes[iVar6 + iVar3];
			pPVar2 = pDrawingPed;
		}
		iVar3 = zBias * 8;
	} while (zBias < 5);
	pBVar10 = &BONE_000a0900;
	if (pPVar2->pedType < OTHER_SPRITE) {
		if ((player.cameraView != '\x02') || (bDoingShadow != 0)) {
			iVar3 = 0x14;
			do {
				uVar5 = (uint)pBVar10->id & 0x7f;
				if (bDoingShadow == 0) {
					if ((MODEL *)pBVar10->pModel != (MODEL *)0x0) {
						zBias = (uint)(uVar5 != 4) << 1;
						if (uVar5 == 2) {
							zBias = 1;
						}
						RenderModel(*(MODEL **)(MODEL *)pBVar10->pModel, (MATRIX *)0x0, &local_80, zBias, 0);
					}
				}
				else {
					if (((uVar5 != 5) && (uVar5 != 9)) &&
						((uVar5 != 0xd &&
						((((uVar5 != 1 && ((pBVar10->id & 0x7f) != 0)) && (uVar5 != 0x16)) &&
							((uVar5 != 0xe && (uVar5 != 0x12)))))))) {
						uVar9 = (uint)pBVar10->pParent->id & 0x7f;
						_DAT_1f800200 =
							CONCAT22(*(short *)(&DAT_1f800024 + uVar5 * 4) +
							(*(short *)&(pDrawingPed->position).vy - (short)camera_position.vy),
								*(short *)(&DAT_1f800020 + uVar5 * 4) +
								(*(short *)&(pDrawingPed->position).vx - (short)camera_position.vx));
						_DAT_1f800204 =
							_DAT_1f800204 & 0xffff0000 |
							(uint)(ushort)(*(short *)(&DAT_1f800028 + uVar5 * 4) +
							(*(short *)&(pDrawingPed->position).vz - (short)camera_position.vz));
						_DAT_1f800208 =
							CONCAT22(*(short *)(&DAT_1f800024 + uVar9 * 4) +
							(*(short *)&(pDrawingPed->position).vy - (short)camera_position.vy),
								*(short *)(&DAT_1f800020 + uVar9 * 4) +
								(*(short *)&(pDrawingPed->position).vx - (short)camera_position.vx));
						zBias = (uint)*(ushort *)&(pDrawingPed->position).vz - (camera_position.vz & 0xffffU);
						uVar5 = (uint)*(ushort *)(&DAT_1f800028 + uVar9 * 4) + zBias;
						_DAT_1f80020c = _DAT_1f80020c & 0xffff0000 | uVar5 & 0xffff;
						setCopReg(2, in_zero, _DAT_1f800200);
						setCopReg(2, 0x1f800000, _DAT_1f800204);
						setCopReg(2, zBias, _DAT_1f800208);
						setCopReg(2, uVar5, _DAT_1f80020c);
						copFunction(2, 0x280030);
						local_38 = getCopReg(2, 0xc);
						local_34 = getCopReg(2, 0xd);
						gCurrentZ = getCopReg(2, 0x11);
						local_2c = getCopReg(2, 0x12);
						local_28 = getCopReg(2, 0x13);
						local_30 = gCurrentZ;
						DrawBodySprite((uint)pBVar10->id, local_38, local_34, gCurrentZ, local_2c);
					}
				}
				iVar3 = iVar3 + -1;
				pBVar10 = pBVar10 + 1;
			} while (-1 < iVar3);
		}
	}
	else {
		iVar3 = 0x15;
		do {
			uVar5 = (uint)pBVar10->id & 0x7f;
			if ((((uVar5 != 5) && (uVar5 != 9)) &&
				((uVar5 != 4 && (((uVar5 != 0xd && (uVar5 != 1)) && ((pBVar10->id & 0x7f) != 0)))))) &&
				(((uVar5 != 0x16 && (uVar5 != 0xe)) && (uVar5 != 0x12)))) {
				uVar9 = (uint)pBVar10->pParent->id & 0x7f;
				_DAT_1f800200 =
					CONCAT22(*(short *)(&DAT_1f800024 + uVar5 * 4) +
					(*(short *)&(pDrawingPed->position).vy - (short)camera_position.vy),
						*(short *)(&DAT_1f800020 + uVar5 * 4) +
						(*(short *)&(pDrawingPed->position).vx - (short)camera_position.vx));
				_DAT_1f800204 =
					_DAT_1f800204 & 0xffff0000 |
					(uint)(ushort)(*(short *)(&DAT_1f800028 + uVar5 * 4) +
					(*(short *)&(pDrawingPed->position).vz - (short)camera_position.vz));
				_DAT_1f800208 =
					CONCAT22(*(short *)(&DAT_1f800024 + uVar9 * 4) +
					(*(short *)&(pDrawingPed->position).vy - (short)camera_position.vy),
						*(short *)(&DAT_1f800020 + uVar9 * 4) +
						(*(short *)&(pDrawingPed->position).vx - (short)camera_position.vx));
				zBias = (uint)*(ushort *)&(pDrawingPed->position).vz - (camera_position.vz & 0xffffU);
				uVar5 = (uint)*(ushort *)(&DAT_1f800028 + uVar9 * 4) + zBias;
				_DAT_1f80020c = _DAT_1f80020c & 0xffff0000 | uVar5 & 0xffff;
				setCopReg(2, in_zero, _DAT_1f800200);
				setCopReg(2, 0x1f800000, _DAT_1f800204);
				setCopReg(2, zBias, _DAT_1f800208);
				setCopReg(2, uVar5, _DAT_1f80020c);
				copFunction(2, 0x280030);
				local_60 = getCopReg(2, 0xc);
				local_5c = getCopReg(2, 0xd);
				gCurrentZ = getCopReg(2, 0x11);
				local_54 = getCopReg(2, 0x12);
				local_50 = getCopReg(2, 0x13);
				local_58 = gCurrentZ;
				DrawBodySprite((uint)pBVar10->id, local_60, local_5c, gCurrentZ, local_54);
			}
			iVar3 = iVar3 + -1;
			pBVar10 = pBVar10 + 1;
		} while (-1 < iVar3);
		if (switch_detail_distance >> 2 < gCurrentZ) {
			uVar5 = (uint)BONE_000a09cc.id & 0x7f;
			uVar9 = (uint)(BONE_000a09cc.pParent)->id & 0x7f;
			_DAT_1f800200 =
				CONCAT22(*(short *)(&DAT_1f800024 + uVar5 * 4) +
				(*(short *)&(pDrawingPed->position).vy - (short)camera_position.vy),
					*(short *)(&DAT_1f800020 + uVar5 * 4) +
					(*(short *)&(pDrawingPed->position).vx - (short)camera_position.vx));
			_DAT_1f800204 =
				_DAT_1f800204 & 0xffff0000 |
				(uint)(ushort)(*(short *)(&DAT_1f800028 + uVar5 * 4) +
				(*(short *)&(pDrawingPed->position).vz - (short)camera_position.vz));
			_DAT_1f800208 =
				CONCAT22(*(short *)(&DAT_1f800024 + uVar9 * 4) +
				(*(short *)&(pDrawingPed->position).vy - (short)camera_position.vy),
					*(short *)(&DAT_1f800020 + uVar9 * 4) +
					(*(short *)&(pDrawingPed->position).vx - (short)camera_position.vx));
			iVar3 = (uint)*(ushort *)&(pDrawingPed->position).vz - (camera_position.vz & 0xffffU);
			uVar5 = (uint)*(ushort *)(&DAT_1f800028 + uVar9 * 4) + iVar3;
			_DAT_1f80020c = _DAT_1f80020c & 0xffff0000 | uVar5 & 0xffff;
			setCopReg(2, in_zero, _DAT_1f800200);
			setCopReg(2, 0x1f800000, _DAT_1f800204);
			setCopReg(2, iVar3, _DAT_1f800208);
			setCopReg(2, uVar5, _DAT_1f80020c);
			copFunction(2, 0x280030);
			local_4c = getCopReg(2, 0xc);
			local_48 = getCopReg(2, 0xd);
			gCurrentZ = getCopReg(2, 0x11);
			local_40 = getCopReg(2, 0x12);
			local_3c = getCopReg(2, 0x13);
			local_44 = gCurrentZ;
			DrawBodySprite((uint)BONE_000a09cc.id, local_4c, local_48, gCurrentZ, local_40);
		}
		else {
			local_70.vx = *(short *)(&DAT_1f800020 + ((uint)BONE_000a09cc.id & 0x7f) * 4);
			local_70.vy = *(short *)(&DAT_1f800024 + ((uint)BONE_000a09cc.id & 0x7f) * 4);
			local_70.vz = *(short *)(&DAT_1f800028 + ((uint)BONE_000a09cc.id & 0x7f) * 4);
			local_68.vx = *(short *)(&DAT_1f800020 + ((uint)(BONE_000a09cc.pParent)->id & 0x7f) * 4);
			local_68.vy = *(short *)(&DAT_1f800024 + ((uint)(BONE_000a09cc.pParent)->id & 0x7f) * 4);
			local_68.vz = *(short *)(&DAT_1f800028 + ((uint)(BONE_000a09cc.pParent)->id & 0x7f) * 4);
			bAllreadyRotated = 1;
			DoCivHead(&local_68, &local_70);
			bAllreadyRotated = 0;
		}
	}
	pBVar10 = &Skel;
	iVar3 = 0x16;
	do {
		iVar3 = iVar3 + -1;
		pBVar10->id = pBVar10->id & 0x7f;
		pBVar10 = pBVar10 + 1;
	} while (-1 < iVar3);
	return;*/
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

void newRotateBones(BONE *poBone)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	LIMBS LVar2;
	undefined4 in_zero;
	undefined4 uVar3;
	SVECTOR *pSVar4;
	MODEL *pMVar5;
	int iVar6;
	int iVar7;
	short *psVar8;
	undefined4 *puVar9;
	ushort uVar10;
	int iVar11;
	int iVar12;
	uint uVar13;
	int iVar14;
	uint uVar15;
	int iVar16;
	uint uVar17;
	int iVar18;
	uint uVar19;
	undefined2 *puVar20;
	uint local_440[4];
	uint local_430;
	uint local_42c;
	uint local_428;
	uint local_424;
	uint auStack1056[248];
	uint local_40;
	uint local_3c;
	uint local_38;
	int local_30;

	DAT_1f800034 = SEXT24((Skel.pvOrigPos)->vx);
	DAT_1f800038 = SEXT24((Skel.pvOrigPos)->vy);
	DAT_1f80003c = SEXT24((Skel.pvOrigPos)->vz);
	local_40 = SEXT24((pDrawingPed->dir).vx);
	local_3c = SEXT24((pDrawingPed->dir).vy);
	local_38 = SEXT24((pDrawingPed->dir).vz);
	iVar6 = (int)rcossin_tbl[(local_3c & 0xfff) * 2 + 1];
	iVar18 = (int)rcossin_tbl[(local_38 & 0xfff) * 2];
	iVar16 = (int)rcossin_tbl[(local_38 & 0xfff) * 2 + 1];
	iVar14 = (int)rcossin_tbl[(local_40 & 0xfff) * 2 + 1];
	iVar11 = (int)rcossin_tbl[(local_40 & 0xfff) * 2];
	iVar12 = (int)rcossin_tbl[(local_3c & 0xfff) * 2];
	uVar13 = (iVar14 * iVar12 + 0x800 >> 0xc) +
		((iVar6 * iVar11 + 0x800 >> 0xc) * iVar18 + 0x800 >> 0xc);
	uVar17 = iVar6 * iVar16 + 0x800 >> 0xc;
	iVar7 = (int)(short)uVar17;
	uVar10 = -(short)(iVar16 * iVar11 + 0x800 >> 0xc);
	uVar15 = iVar14 * iVar16 + 0x800 >> 0xc;
	iVar6 = (-iVar14 * (iVar6 * iVar18 + 0x800 >> 0xc) + 0x800 >> 0xc) +
		(iVar11 * iVar12 + 0x800 >> 0xc);
	DAT_1f800020 = uVar17 & 0xffff | iVar6 * 0x10000;
	DAT_1f800024 = uVar13 & 0xffff | (uint)(ushort)rcossin_tbl[(local_38 & 0xfff) * 2] << 0x10;
	DAT_1f800028 = uVar15 & 0xffff | (uint)uVar10 << 0x10;
	DAT_1f80002c = CONCAT22((short)(((int)(uVar13 * 0x10000) >> 0x10) * iVar18 + 0x800 >> 0xc) -
		(short)(iVar7 * (short)uVar10 + 0x800 >> 0xc),
		-(short)(iVar12 * iVar16 + 0x800 >> 0xc));
	DAT_1f800030 = DAT_1f800030 & 0xffff0000 |
		(uint)(ushort)((short)(iVar7 * (short)uVar15 + 0x800 >> 0xc) -
		(short)((iVar6 * 0x10000 >> 0x10) * iVar18 + 0x800 >> 0xc));
	_DAT_1f800060 = CONCAT22((undefined2)Skel.vOffset.vy, (undefined2)Skel.vOffset.vx);
	_DAT_1f800064 = _DAT_1f800064 & 0xffff0000 | (uint)(ushort)Skel.vOffset.vz;
	local_440[3] = DAT_1f80002c;
	local_30 = 0;
	local_440[0] = DAT_1f800020;
	local_440[1] = DAT_1f800024;
	local_440[2] = DAT_1f800028;
	local_430 = DAT_1f800030;
	local_42c = DAT_1f800034;
	local_428 = DAT_1f800038;
	local_424 = DAT_1f80003c;
	do {
		iVar7 = local_30 * 8;
		iVar6 = 1;
		LVar2 = lRoutes[iVar7 + 1];
		local_30 = local_30 + 1;
		while (LVar2 != ROOT) {
			uVar13 = (uint)LVar2;
			_DAT_1f800060 =
				CONCAT22(*(undefined2 *)&(&Skel)[uVar13].vOffset.vy,
					*(undefined2 *)&(&Skel)[uVar13].vOffset.vx);
			_DAT_1f800064 = _DAT_1f800064 & 0xffff0000 | (uint)*(ushort *)&(&Skel)[uVar13].vOffset.vz;
			if ((bReverseYRotation == 0) || (((&Skel)[uVar13].pParent)->id != ROOT)) {
				DAT_1f80006a = ((&Skel)[uVar13].pParent)->pvRotation->vy;
				DAT_1f800068 = -((&Skel)[uVar13].pParent)->pvRotation->vx;
				DAT_1f80006c = ((&Skel)[uVar13].pParent)->pvRotation->vz;
			}
			else {
				DAT_1f80006a = -((&Skel)[uVar13].pParent)->pvRotation->vy;
				DAT_1f800068 = ((&Skel)[uVar13].pParent)->pvRotation->vx;
				DAT_1f80006c = ((&Skel)[uVar13].pParent)->pvRotation->vz;
			}
			if (LVar2 == HEAD) {
				DAT_1f80006a = DAT_1f80006a - pDrawingPed->head_rot;
			}
			DAT_1f800000._0_2_ = 0x1000;
			DAT_1f800004._2_2_ = 0;
			DAT_1f80000c = 0;
			DAT_1f800000._2_2_ = 0;
			DAT_1f800008._0_2_ = 0x1000;
			DAT_1f80000e = 0;
			DAT_1f800004._0_2_ = 0;
			DAT_1f800008._2_2_ = 0;
			DAT_1f800010._0_2_ = 0x1000;
			RotMatrixZYX_gte(&DAT_1f800068, 0x1f800000);
			DAT_1f800014 = (int)DAT_1f800060;
			DAT_1f800018 = (int)DAT_1f800062;
			DAT_1f80001c = (int)DAT_1f800064;
			uVar15 = (uint)((&Skel)[uVar13].pParent)->id & 0x7f;
			DAT_1f800020 = local_440[uVar15 * 8];
			DAT_1f800024 = local_440[uVar15 * 8 + 1];
			DAT_1f800028 = local_440[uVar15 * 8 + 2];
			DAT_1f80002c = local_440[uVar15 * 8 + 3];
			DAT_1f800030 = local_440[uVar15 * 8 + 4];
			DAT_1f800034 = local_440[uVar15 * 8 + 5];
			DAT_1f800038 = local_440[uVar15 * 8 + 6];
			DAT_1f80003c = local_440[uVar15 * 8 + 7];
			uVar3 = 0x1f800000;
			setCopControlWord(2, 0, DAT_1f800020);
			setCopControlWord(2, 0x800, DAT_1f800024);
			setCopControlWord(2, 0x1000, DAT_1f800028);
			setCopControlWord(2, 0x1800, DAT_1f80002c);
			setCopControlWord(2, 0x2000, DAT_1f800030);
			setCopReg(2, 0x4800, (uint)(ushort)DAT_1f800000);
			setCopReg(2, 0x5000, (uint)DAT_1f800004._2_2_);
			setCopReg(2, 0x5800, (uint)DAT_1f80000c);
			copFunction(2, 0x49e012);
			uVar15 = getCopReg(2, 0x4800);
			iVar12 = getCopReg(2, 0x5000);
			uVar19 = getCopReg(2, 0x5800);
			setCopReg(2, 0x4800, (uint)DAT_1f800000._2_2_);
			setCopReg(2, 0x5000, (uint)(ushort)DAT_1f800008);
			setCopReg(2, 0x5800, (uint)DAT_1f80000e);
			copFunction(2, 0x49e012);
			iVar11 = getCopReg(2, 0x4800);
			uVar17 = getCopReg(2, 0x5000);
			iVar14 = getCopReg(2, 0x5800);
			DAT_1f800040 = uVar15 & 0xffff | iVar11 << 0x10;
			DAT_1f80004c = uVar19 & 0xffff | iVar14 << 0x10;
			setCopReg(2, 0x4800, (uint)(ushort)DAT_1f800004);
			setCopReg(2, 0x5000, (uint)DAT_1f800008._2_2_);
			setCopReg(2, 0x5800, (uint)(ushort)DAT_1f800010);
			copFunction(2, 0x49e012);
			uVar15 = getCopReg(2, 0x4800);
			iVar11 = getCopReg(2, 0x5000);
			uVar19 = getCopReg(2, 0x5800);
			DAT_1f800044 = uVar15 & 0xffff | iVar12 << 0x10;
			DAT_1f800048 = uVar17 & 0xffff | iVar11 << 0x10;
			DAT_1f800050 = DAT_1f800050 & 0xffff0000 | uVar19 & 0xffff;
			setCopControlWord(2, 0x2800, DAT_1f800034);
			setCopControlWord(2, 0x3000, DAT_1f800038);
			setCopControlWord(2, 0x3800, DAT_1f80003c);
			setCopReg(2, 0, _DAT_1f800060);
			setCopReg(2, 0x1f800000, DAT_1f80001c);
			copFunction(2, 0x480012);
			DAT_1f800054 = getCopReg(2, 0x19);
			DAT_1f800058 = getCopReg(2, 0x1a);
			DAT_1f80005c = getCopReg(2, 0x1b);
			setCopControlWord(2, 0, DAT_1f800040);
			setCopControlWord(2, 0x800, DAT_1f800044);
			setCopControlWord(2, 0x1000, DAT_1f800048);
			setCopControlWord(2, 0x1800, DAT_1f80004c);
			setCopControlWord(2, 0x2000, DAT_1f800050);
			setCopReg(2, in_zero, _DAT_1f800060);
			setCopReg(2, 0x1f800000, _DAT_1f800064);
			copFunction(2, 0x486012);
			DAT_1f800070 = getCopReg(2, 0x19);
			DAT_1f800074 = getCopReg(2, 0x1a);
			DAT_1f800078 = getCopReg(2, 0x1b);
			LVar2 = (&Skel)[uVar13].id;
			(&Skel)[uVar13].vCurrPos.vx = DAT_1f800070;
			(&Skel)[uVar13].vCurrPos.vy = DAT_1f800074;
			(&Skel)[uVar13].vCurrPos.vz = DAT_1f800078;
			pSVar4 = GetModelVertPtr((uint)LVar2, 0);
			LVar2 = (&Skel)[uVar13].id;
			if (((((LVar2 & 0x7f) == 4) || (pDrawingPed->pedType < OTHER_SPRITE)) &&
				(-1 < (int)((uint)LVar2 << 0x18))) &&
				(((&Skel)[uVar13].pModel != (MODEL **)0x0 && (pSVar4 != (SVECTOR *)0x0)))) {
				pMVar5 = *(&Skel)[uVar13].pModel;
				uVar10 = pMVar5->num_vertices;
				uVar17 = (uint)uVar10;
				puVar20 = (undefined2 *)pMVar5->vertices;
				psVar8 = &DAT_1f800080;
				uVar15 = uVar17;
				if (uVar10 != 0) {
					do {
						*psVar8 = pSVar4->vx + DAT_1f800060;
						uVar15 = uVar15 - 1;
						psVar8[1] = pSVar4->vy + DAT_1f800062;
						psVar1 = &pSVar4->vz;
						pSVar4 = pSVar4 + 1;
						psVar8[2] = *psVar1 + DAT_1f800064;
						psVar8 = psVar8 + 4;
					} while (uVar15 != 0);
				}
				puVar9 = (undefined4 *)&DAT_1f800080;
				if (uVar10 != 0) {
					do {
						setCopReg(2, in_zero, *puVar9);
						setCopReg(2, uVar3, puVar9[1]);
						copFunction(2, 0x486012);
						DAT_1f800070 = getCopReg(2, 0x19);
						DAT_1f800074 = getCopReg(2, 0x1a);
						DAT_1f800078 = getCopReg(2, 0x1b);
						*puVar20 = (undefined2)DAT_1f800070;
						uVar17 = uVar17 - 1;
						puVar20[1] = (undefined2)DAT_1f800074;
						puVar9 = puVar9 + 2;
						puVar20[2] = (undefined2)DAT_1f800078;
						puVar20 = puVar20 + 4;
					} while (uVar17 != 0);
				}
			}
			iVar6 = iVar6 + 1;
			LVar2 = lRoutes[iVar6 + iVar7];
			local_440[uVar13 * 8] = DAT_1f800040;
			local_440[uVar13 * 8 + 1] = DAT_1f800044;
			local_440[uVar13 * 8 + 2] = DAT_1f800048;
			local_440[uVar13 * 8 + 3] = DAT_1f80004c;
			local_440[uVar13 * 8 + 4] = DAT_1f800050;
			local_440[uVar13 * 8 + 5] = DAT_1f800054;
			local_440[uVar13 * 8 + 6] = DAT_1f800058;
			local_440[uVar13 * 8 + 7] = DAT_1f80005c;
		}
	} while (local_30 < 5);
	return;*/
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
SVECTOR* GetModelVertPtr(int boneId, int modelType)
{
	int startVertex;

	if (pDrawingPed->pedType != OTHER_MODEL)
	{
		if (cTannerVNumbers[boneId & 0x7f] != -1) 
			return vTannerList + cTannerVNumbers[boneId & 0x7f];

		return NULL;
	}

	switch (boneId) {
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

int bAllreadyRotated = 0;

void DrawCiv(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	/*
	short *psVar1;
	bool bVar2;
	undefined4 in_zero;
	undefined4 in_at;
	undefined4 uVar3;
	undefined4 uVar4;
	undefined4 uVar5;
	undefined4 uVar6;
	int iVar7;
	int iVar8;
	SVECTOR *vert1;
	int iVar9;
	int iVar10;
	uint v1;
	short size;
	uint boneId;
	int iVar11;
	uint uVar12;
	uint uVar13;
	int iVar14;
	uint uVar15;
	uint uVar16;
	int iVar17;
	uint uVar18;
	int iVar19;
	MATRIX *pMVar20;
	SVECTOR *pLerpData;
	SVECTOR *vert2;
	SVECTOR *pSVar21;
	SVECTOR *pSVar22;
	MATRIX *pMVar23;
	SVECTOR *pSVar24;
	int *piVar25;
	int iVar26;
	SVECTOR pos;
	VECTOR pos1;
	SVECTOR temp1;
	SVECTOR temp2;
	MATRIX workmatrix;
	CVECTOR cv;
	VECTOR ppos;
	undefined4 uStack64;
	int local_38;
	CVECTOR *local_34;
	VECTOR *local_30;

	pSVar24 = &SVECTOR_1f800010;
	pSVar22 = &SVECTOR_1f800210;
	pMVar20 = &MATRIX_1f800090;
	local_38 = 0;
	vert1 = (SVECTOR *)pPed->motion;
	iVar26 = 0;
	boneId = (uint)((byte)pPed->frame1 >> 1);
	vert2 = vert1 + boneId * 0x1e;
	uVar13 = (uint)(*(byte *)((int)&pPed->flags + 1) >> 7);
	pDrawingPed = pPed;
	if ((pPed->frame1 & 1U) == 0) {
		iVar11 = 0x1e;
		do {
			pMVar20->m[0] = vert2->vx;
			iVar11 = iVar11 + -1;
			*(undefined2 *)pMVar20->m = (short)((int)vert2->vy >> uVar13);
			psVar1 = &vert2->vz;
			vert2 = vert2 + 1;
			*(short *)pMVar20->m = *psVar1;
			pMVar20 = (MATRIX *)(pMVar20->m + 4);
		} while (0 < iVar11);
	}
	else {
		if ((byte)pPed->frame1 < 0x1e) {
			vert1 = vert1 + (boneId + 1) * 0x1e;
		}
		iVar11 = 0x1e;
		pLerpData = (SVECTOR *)pMVar20;
		do {
			uVar3 = *(undefined4 *)vert1;
			uVar5 = *(undefined4 *)&vert1->vz;
			uVar4 = *(undefined4 *)vert2;
			uVar6 = *(undefined4 *)&vert2->vz;
			temp1.vx = (short)uVar3;
			temp2.vx = (short)uVar4;
			iVar11 = iVar11 + -1;
			pLerpData->vx = (short)((int)temp1.vx + (int)temp2.vx >> 1);
			temp1.vy = (short)((uint)uVar3 >> 0x10);
			temp2.vy = (short)((uint)uVar4 >> 0x10);
			vert1 = vert1 + 1;
			pLerpData->vy = (short)((int)temp1.vy + (int)temp2.vy >> uVar13 + 1);
			temp1.vz = (short)uVar5;
			temp2.vz = (short)uVar6;
			vert2 = vert2 + 1;
			pLerpData->vz = (short)((int)temp1.vz + (int)temp2.vz >> 1);
			pLerpData = pLerpData + 1;
		} while (0 < iVar11);
	}
	setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
	setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
	pos._0_4_ = CONCAT22(*(short *)&(pDrawingPed->position).vy - (short)camera_position.vy,
		*(short *)&(pDrawingPed->position).vx - (short)camera_position.vx);
	pos._4_4_ = pos._4_4_ & 0xffff0000 |
		(uint)(ushort)(*(short *)&(pDrawingPed->position).vz - (short)camera_position.vz);
	setCopReg(2, in_zero, pos._0_4_);
	setCopReg(2, in_at, pos._4_4_);
	copFunction(2, 0x486012);
	uVar3 = getCopReg(2, 0x19);
	uVar4 = getCopReg(2, 0x1a);
	uVar5 = getCopReg(2, 0x1b);
	setCopControlWord(2, 0x2800, uVar3);
	setCopControlWord(2, 0x3000, uVar4);
	setCopControlWord(2, 0x3800, uVar5);
	uVar12 = (uint)(ushort)(pDrawingPed->dir).vy & 0xfff;
	uVar13 = (uint)(ushort)(pDrawingPed->dir).vz & 0xfff;
	iVar9 = (int)rcossin_tbl[uVar12 * 2 + 1];
	iVar19 = (int)rcossin_tbl[uVar13 * 2];
	iVar17 = (int)rcossin_tbl[uVar13 * 2 + 1];
	boneId = (uint)(ushort)(pDrawingPed->dir).vx & 0xfff;
	iVar11 = (int)rcossin_tbl[boneId * 2 + 1];
	iVar14 = (int)rcossin_tbl[uVar12 * 2];
	iVar8 = (int)rcossin_tbl[boneId * 2];
	uVar16 = (iVar11 * iVar14 + 0x800 >> 0xc) +
		((iVar9 * iVar8 + 0x800 >> 0xc) * iVar19 + 0x800 >> 0xc);
	uVar18 = iVar9 * iVar17 + 0x800 >> 0xc;
	iVar10 = (int)(short)uVar18;
	boneId = -(iVar17 * iVar8 + 0x800 >> 0xc);
	uVar12 = iVar11 * iVar17 + 0x800 >> 0xc;
	iVar7 = (int)(short)uVar12;
	uVar15 = (-iVar11 * (iVar9 * iVar19 + 0x800 >> 0xc) + 0x800 >> 0xc) +
		(iVar8 * iVar14 + 0x800 >> 0xc);
	v1 = (iVar10 * iVar7 + 0x800 >> 0xc) -
		(((int)(uVar15 * 0x10000) >> 0x10) * iVar19 + 0x800 >> 0xc);
	setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
	setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
	setCopReg(2, 0x4800, uVar18 & 0xffff);
	setCopReg(2, 0x5000, (uint)(ushort)rcossin_tbl[uVar13 * 2]);
	setCopReg(2, 0x5800, (uint)(ushort)-(short)(iVar14 * iVar17 + 0x800 >> 0xc));
	copFunction(2, 0x49e012);
	uVar13 = getCopReg(2, 0x4800);
	iVar8 = getCopReg(2, 0x5000);
	uVar18 = getCopReg(2, 0x5800);
	setCopReg(2, 0x4800, uVar15 & 0xffff);
	setCopReg(2, 0x5000, uVar12 & 0xffff);
	setCopReg(2, 0x5800, (uint)(ushort)((short)(((int)(uVar16 * 0x10000) >> 0x10) * iVar19 + 0x800 >>
		0xc) - (short)(iVar10 * (short)boneId + 0x800 >> 0xc)))
		;
	copFunction(2, 0x49e012);
	iVar11 = getCopReg(2, 0x4800);
	uVar12 = getCopReg(2, 0x5000);
	iVar9 = getCopReg(2, 0x5800);
	workmatrix.m[0]._0_4_ = uVar13 & 0xffff | iVar11 << 0x10;
	workmatrix.m[2]._0_4_ = uVar18 & 0xffff | iVar9 << 0x10;
	setCopReg(2, 0x4800, uVar16 & 0xffff);
	setCopReg(2, 0x5000, boneId & 0xffff);
	setCopReg(2, 0x5800, v1 & 0xffff);
	copFunction(2, 0x49e012);
	uVar13 = getCopReg(2, 0x4800);
	iVar11 = getCopReg(2, 0x5000);
	uVar15 = getCopReg(2, 0x5800);
	workmatrix.m._4_4_ = iVar8 << 0x10 | uVar13 & 0xffff;
	workmatrix.m[1]._2_4_ = uVar12 & 0xffff | iVar11 << 0x10;
	workmatrix._16_4_ = workmatrix._16_4_ & 0xffff0000 | uVar15 & 0xffff;
	setCopControlWord(2, 0, workmatrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, workmatrix.m._4_4_);
	setCopControlWord(2, 0x1000, workmatrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, workmatrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, workmatrix._16_4_);
	setCopReg(2, in_zero, MATRIX_1f800090.m[0]._0_4_);
	setCopReg(2, in_at, MATRIX_1f800090.m._4_4_);
	setCopReg(2, 0x1f800090, MATRIX_1f800090.m[1]._2_4_);
	setCopReg(2, iVar7, MATRIX_1f800090.m[2]._0_4_);
	setCopReg(2, boneId, MATRIX_1f800090._16_4_);
	setCopReg(2, v1, MATRIX_1f800090.t[0]);
	copFunction(2, 0x280030);
	gCurrentZ = getCopReg(2, 0x13);
	local_30 = &ppos;
	SVECTOR_1f800210._0_4_ = gCurrentZ;
	if (gCurrentZ <= switch_detail_distance) {
		local_34 = &cv;
		piVar25 = boneIdvals;
		iVar11 = 0;
		pSVar21 = &SVECTOR_1f800210;
		vert2 = &SVECTOR_1f800010;
		iVar7 = 0xe;
		pMVar20 = &MATRIX_1f800090;
		do {
			if (iVar26 < 0x1e) {
				uVar3 = getCopReg(2, 0xc);
				*(undefined4 *)vert2 = uVar3;
				uVar3 = getCopReg(2, 0xd);
				*(undefined4 *)&vert2->vz = uVar3;
				uVar3 = getCopReg(2, 0xe);
				*(undefined4 *)(vert2 + 1) = uVar3;
				uVar3 = getCopReg(2, 0x11);
				*(undefined4 *)pSVar21 = uVar3;
				uVar3 = getCopReg(2, 0x12);
				*(undefined4 *)&pSVar21->vz = uVar3;
				uVar3 = getCopReg(2, 0x13);
				*(undefined4 *)(pSVar21 + 1) = uVar3;
			}
			bVar2 = iVar26 < 0x1b;
			pMVar23 = pMVar20;
			if (bVar2) {
				pMVar23 = (MATRIX *)(pMVar20->t + 1);
				pSVar21 = (SVECTOR *)&pSVar21[1].vz;
				vert2 = (SVECTOR *)&vert2[1].vz;
				iVar26 = iVar26 + 3;
				setCopReg(2, in_zero, *(undefined4 *)pMVar23->m);
				setCopReg(2, in_at, pMVar20->t[2]);
				setCopReg(2, (uint)bVar2, *(undefined4 *)pMVar20[1].m);
				setCopReg(2, iVar11, *(undefined4 *)(pMVar20[1].m + 2));
				setCopReg(2, boneId, *(undefined4 *)(pMVar20[1].m + 4));
				setCopReg(2, v1, *(undefined4 *)(pMVar20[1].m + 6));
				copFunction(2, 0x280030);
			}
			boneId = *piVar25;
			if ((boneId == 4) &&
				(v1 = 1, iVar11 = SVECTOR_1f800210._0_4_,
					SVECTOR_1f800210._0_4_ <= switch_detail_distance >> 1)) {
				local_38 = 1;
			}
			else {
				v1 = *(uint *)pSVar24;
				DrawBodySprite(boneId, v1, *(long *)&pSVar24->vz, *(int *)pSVar22, *(int *)&pSVar22->vz)
					;
			}
			pSVar24 = pSVar24 + 1;
			pSVar22 = pSVar22 + 1;
			iVar7 = iVar7 + -1;
			piVar25 = (int *)((uint *)piVar25 + 1);
			pMVar20 = pMVar23;
		} while (-1 < iVar7);
		if (local_38 != 0) {
			bAllreadyRotated = 0;
			DoCivHead((SVECTOR *)&DAT_1f8000b8, (SVECTOR *)&DAT_1f8000b0);
			uStack64 = 0;
			ppos.pad = 0;
			setCopControlWord(2, 0x2800, 0);
			setCopControlWord(2, 0x3000, 0);
			setCopControlWord(2, 0x3800, 0);
		}
		ppos.vx = (pPed->position).vx;
		ppos.vy = (pPed->position).vy;
		ppos.vz = (pPed->position).vz;
		boneId = (uint)(byte)pPed->frame1 & 0xf;
		uVar13 = boneId * 2;
		iVar26 = MapHeight(local_30);
		cv.b = '(';
		cv.g = '(';
		cv.r = '(';
		ppos.vx = ppos.vx - camera_position.vx;
		ppos.vy = (10 - iVar26) - camera_position.vy;
		ppos.vz = ppos.vz - camera_position.vz;
		if (uVar13 < 8) {
			size = (short)uVar13 + 0x50;
		}
		else {
			size = (short)boneId * -2 + 0x70;
		}
		RoundShadow(local_30, local_34, size);
	}*/
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
	if (type == 1) {
		Skel[2].pModel = &pmJerichoModels[0];
		Skel[4].pModel = &pmJerichoModels[1];
		Skel[6].pModel = &pmJerichoModels[2];
		Skel[7].pModel = &pmJerichoModels[3];
		Skel[10].pModel = &pmJerichoModels[4];
		Skel[11].pModel = &pmJerichoModels[5];
		Skel[14].pModel = NULL;
		return;
	}

	Skel[2].pModel = &pmTannerModels[0];
	Skel[4].pModel = &pmTannerModels[1];
	Skel[6].pModel = &pmTannerModels[8];
	Skel[7].pModel = &pmTannerModels[9];
	Skel[10].pModel = &pmTannerModels[2];
	Skel[11].pModel = &pmTannerModels[3];
	Skel[14].pModel = &pmTannerModels[15];
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


void DrawTanner(PEDESTRIAN *pPed)
{
	int iVar1;
	VECTOR v;
	CVECTOR cV;
	MATRIX mRotStore;
	MATRIX iMatrix;

	bDoingShadow = 0;

	gte_ReadRotMatrix(&mRotStore);
	gte_sttr(mRotStore.t);

	pDrawingPed = pPed;

	SetupTannerSkeleton();

	if (pPed->pedType == OTHER_MODEL) 
	{
		Skel[4].pModel = pmJerichoModels;
		Skel[6].pModel = pmJerichoModels + 2;
		Skel[2].pModel = pmJerichoModels;
		Skel[7].pModel = pmJerichoModels + 3;
		Skel[10].pModel = pmJerichoModels + 4;
		Skel[11].pModel = pmJerichoModels + 5;
		Skel[14].pModel = NULL;
	}
	else 
	{
		Skel[4].pModel = pmTannerModels;
		Skel[6].pModel = pmTannerModels + 8;
		Skel[7].pModel = pmTannerModels + 9;
		Skel[2].pModel = pmTannerModels;
		Skel[10].pModel = pmTannerModels + 2;
		Skel[11].pModel = pmTannerModels + 3;
		Skel[14].pModel = pmTannerModels + 0xf;
	}

	Skel[4].pModel = Skel[4].pModel + 1;
	newRotateBones(Skel + 1);

	gte_SetRotMatrix(&mRotStore);
	gte_SetTransMatrix(&mRotStore);

	iCurrBone = 0;
	newShowTanner();

	v.vx = (pPed->position.vx - camera_position.vx) + Skel[0].pvOrigPos->vx;
	v.vz = (pPed->position.vz - camera_position.vz) + Skel[0].pvOrigPos->vz;

	bDoingShadow = 1;
	v.vy = -camera_position.vy - MapHeight((VECTOR *)&pPed->position);

	if (pPed->padId == '\0') 
	{
		if (gTimeOfDay == 3)
		{
			cV.b = 12;
			cV.g = 12;
			cV.r = 12;
			TannerShadow(&v, moon_position + GameLevel, &cV, (pPed->dir).vy);
		}
		else {
			cV.b = ' ';
			cV.g = ' ';
			cV.r = ' ';
			TannerShadow(&v, sun_position + GameLevel, &cV, (pPed->dir).vy);
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

int DrawCharacter(PEDESTRIAN *pPed)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uint uVar1;
	int iVar2;
	ushort size;
	undefined4 uVar3;
	undefined4 uVar4;
	undefined4 uVar5;
	undefined4 uVar6;
	undefined4 uVar7;
	uint uVar8;
	CVECTOR local_40[2];
	VECTOR local_38;
	CVECTOR local_28[2];
	VECTOR local_20;

	uVar3 = getCopControlWord(2, 0);
	uVar5 = getCopControlWord(2, 0x800);
	uVar4 = getCopControlWord(2, 0x1000);
	uVar6 = getCopControlWord(2, 0x1800);
	uVar7 = getCopControlWord(2, 0x2000);
	getCopControlWord(2, 0x2800);
	getCopControlWord(2, 0x3000);
	getCopControlWord(2, 0x3800);
	pDrawingPed = pPed;
	SetupTannerSkeleton();
	newRotateBones(&BONE_000a0900);
	setCopControlWord(2, 0, uVar3);
	setCopControlWord(2, 0x800, uVar5);
	setCopControlWord(2, 0x1000, uVar4);
	setCopControlWord(2, 0x1800, uVar6);
	setCopControlWord(2, 0x2000, uVar7);
	iCurrBone = 0;
	newShowTanner();
	if ((pUsedPeds->pNext == (PEDESTRIAN *)0x0) && (pPed->pedType == TANNER_MODEL)) {
		local_38.vx = ((pPed->position).vx - camera_position.vx) + (int)(Skel.pvOrigPos)->vx;
		local_38.vz = ((pPed->position).vz - camera_position.vz) + (int)(Skel.pvOrigPos)->vz;
		local_38.vy = MapHeight((VECTOR *)&pPed->position);
		bDoingShadow = 1;
		local_38.vy = -camera_position.vy - local_38.vy;
		if (gTimeOfDay == 3) {
			local_40[0].b = '\f';
			local_40[0].g = '\f';
			local_40[0].r = '\f';
			TannerShadow(&local_38, moon_position + GameLevel, local_40, (pPed->dir).vy);
		}
		else {
			local_40[0].b = ' ';
			local_40[0].g = ' ';
			local_40[0].r = ' ';
			TannerShadow(&local_38, sun_position + GameLevel, local_40, (pPed->dir).vy);
		}
		bDoingShadow = 0;
	}
	else {
		if (pPed->pedType == CIVILIAN) {
			local_20.vx = (pPed->position).vx;
			local_20.vy = (pPed->position).vy;
			local_20.vz = (pPed->position).vz;
			uVar1 = (uint)(byte)pPed->frame1 & 7;
			uVar8 = uVar1 * 2;
			iVar2 = MapHeight(&local_20);
			local_28[0].b = '(';
			local_28[0].g = '(';
			local_28[0].r = '(';
			local_20.vx = local_20.vx - camera_position.vx;
			local_20.vy = (0x1e - iVar2) - camera_position.vy;
			local_20.vz = local_20.vz - camera_position.vz;
			if (uVar8 < 8) {
				size = (ushort)uVar8 | 0x50;
			}
			else {
				size = (short)uVar1 * -2 + 0x60;
			}
			RoundShadow(&local_20, local_28, size);
		}
	}
	return 1;*/
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
		
		rectTannerWindow.w = 0x40;
		rectTannerWindow.h = 0x80;
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

void TannerShadow(VECTOR *pPedPos, SVECTOR *pLightPos, CVECTOR *col, short angle)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	ushort uVar5;
	ushort uVar6;
	undefined4 uVar7;
	char cVar8;
	DB *pDVar9;
	long *plVar10;
	undefined4 in_zero;
	undefined4 in_at;
	int iVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	long z0;
	long z1;
	long z2;
	long z3;
	uint uVar15;
	ulong *puVar16;
	undefined4 *puVar17;
	uint *puVar18;
	undefined4 *puVar19;
	int iVar20;
	undefined4 local_110;
	undefined4 local_10c;
	undefined4 local_108;
	undefined4 local_104;
	undefined4 local_100;
	undefined4 local_fc;
	short local_f8;
	short local_f6;
	short local_f4;
	undefined4 local_f0;
	undefined4 local_ec;
	undefined4 local_e8;
	undefined auStack224[96];
	long local_80;
	long local_7c;
	long local_78;
	long local_74;
	undefined4 local_70;
	undefined4 local_6c;
	int local_68;
	int local_64;
	int local_60;
	VECTOR local_58;
	long local_48;
	long local_44;
	int local_40;
	long local_3c;
	long *local_38;
	long *local_34;
	long *local_30;
	undefined4 *local_2c;

	memset(&local_f0, 0, 0x10);
	memset(&local_58, 0, 0x10);
	SetDefDrawEnv(auStack224, 0, (int)(current->draw).clip.y, 0x140, 0x100);
	puVar18 = (uint *)current->primptr;
	SetDrawEnv(puVar18, auStack224);
	pDVar9 = current;
	*puVar18 = *puVar18 & 0xff000000 | current->ot[0x107f] & 0xffffff;
	pDVar9->ot[0x107f] = pDVar9->ot[0x107f] & 0xff000000 | (uint)puVar18 & 0xffffff;
	iVar20 = 3;
	pDVar9->primptr = pDVar9->primptr + 0x40;
	Tangle = ratan2(-(int)pLightPos->vx, (int)pLightPos->vz);
	local_38 = &local_48;
	local_34 = &local_44;
	local_2c = (undefined4 *)&local_f8;
	local_30 = &local_3c;
	puVar19 = &local_10c;
	puVar17 = &local_110;
	local_fc._0_2_ = 0x12;
	local_f4 = 0x12;
	local_100 = 0xff80;
	local_f8 = 0x80;
	local_f6 = 0;
	local_110 = 0xff80;
	local_10c._0_2_ = -0x140;
	local_108 = 0x80;
	local_104 = CONCAT22(local_104._2_2_, 0xfec0);
	do {
		iVar20 = iVar20 + -1;
		iVar11 = rcos(Tangle);
		iVar12 = rsin(Tangle);
		sVar1 = *(short *)puVar17;
		sVar2 = *(short *)puVar19;
		iVar13 = rsin(Tangle);
		iVar14 = rcos(Tangle);
		sVar3 = *(short *)puVar17;
		sVar4 = *(short *)puVar19;
		*(short *)puVar17 =
			(short)((uint)(((sVar1 * iVar11 >> 0xc) - (sVar2 * iVar12 >> 0xc)) * 0x10000) >> 0x10);
		puVar17 = puVar17 + 2;
		*(short *)puVar19 = (short)(sVar3 * iVar13 >> 0xc) + (short)(sVar4 * iVar14 >> 0xc);
		plVar10 = local_34;
		puVar19 = puVar19 + 2;
	} while (-1 < iVar20);
	uVar5 = *(ushort *)&pPedPos->vx;
	sVar1 = *(short *)&pPedPos->vy;
	local_100 = CONCAT22(local_100._2_2_ + sVar1, (short)local_100 + uVar5);
	uVar6 = *(ushort *)&pPedPos->vz;
	local_fc = CONCAT22(local_fc._2_2_, (short)local_fc + uVar6);
	local_f8 = local_f8 + uVar5;
	local_f6 = local_f6 + sVar1;
	local_f4 = local_f4 + uVar6;
	local_110 = CONCAT22(local_110._2_2_ + sVar1, (short)local_110 + uVar5);
	local_10c = CONCAT22(local_10c._2_2_, (short)local_10c + uVar6);
	uVar15 = (local_104 & 0xffff) + (uint)uVar6;
	local_108 = CONCAT22(local_108._2_2_ + sVar1, (short)local_108 + uVar5);
	local_104 = local_104 & 0xffff0000 | uVar15 & 0xffff;
	setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
	setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
	setCopControlWord(2, 0x2800, local_f0);
	setCopControlWord(2, 0x3000, local_ec);
	setCopControlWord(2, 0x3800, local_e8);
	setCopReg(2, in_zero, local_110);
	setCopReg(2, in_at, local_10c);
	setCopReg(2, &local_f0, local_108);
	setCopReg(2, uVar15, local_104);
	setCopReg(2, (uint)uVar6, local_100);
	setCopReg(2, (uint)uVar5, local_fc);
	copFunction(2, 0x280030);
	iVar20 = current->id;
	uVar7 = getCopReg(2, 0xc);
	*(undefined4 *)&ft4TannerShadow[iVar20].x0 = uVar7;
	uVar7 = getCopReg(2, 0xd);
	*(undefined4 *)&ft4TannerShadow[iVar20].x1 = uVar7;
	uVar7 = getCopReg(2, 0xe);
	*(undefined4 *)&ft4TannerShadow[iVar20].x2 = uVar7;
	z0 = getCopReg(2, 0x11);
	*local_38 = z0;
	z0 = getCopReg(2, 0x12);
	*plVar10 = z0;
	local_40 = getCopReg(2, 0x13);
	setCopReg(2, in_zero, *local_2c);
	setCopReg(2, in_at, local_2c[1]);
	copFunction(2, 0x180001);
	uVar7 = getCopReg(2, 0xe);
	*(undefined4 *)&ft4TannerShadow[current->id].x3 = uVar7;
	z0 = getCopReg(2, 0x13);
	*local_30 = z0;
	if (local_48 < local_44) {
		local_48 = (local_48 + local_44) / 2;
	}
	else {
		local_44 = (local_48 + local_44) / 2;
	}
	if (local_40 < local_3c) {
		local_40 = (local_40 + local_3c) / 2;
	}
	else {
		local_3c = (local_40 + local_3c) / 2;
	}
	z0 = 8;
	if (0x1c < local_48) {
		z0 = local_48 + -0x14;
	}
	z1 = 8;
	if (0x1c < local_44) {
		z1 = local_44 + -0x14;
	}
	z2 = 8;
	if (0x1c < local_40) {
		z2 = local_40 + -0x14;
	}
	z3 = 8;
	if (0x1c < local_3c) {
		z3 = local_3c + -0x14;
	}
	local_48 = z0;
	local_44 = z1;
	local_40 = z2;
	local_3c = z3;
	SubdivShadow(z0, z1, z2, z3, ft4TannerShadow + current->id);
	local_68 = (int)pLightPos->vx * 0x6e >> 0xc;
	local_7c = player.cameraPos.vy;
	local_78 = player.cameraPos.vz;
	local_74 = player.cameraPos.pad;
	local_80 = player.cameraPos.vx;
	local_70 = camera_angle._0_4_;
	local_6c = camera_angle._4_4_;
	local_64 = (int)pLightPos->vy * 0x6e >> 0xc;
	local_60 = (int)pLightPos->vz * 0x6e >> 0xc;
	camera_position.vx = (pDrawingPed->position).vx + local_68;
	camera_position.vy = (pDrawingPed->position).vy + local_64;
	camera_position.vz = (pDrawingPed->position).vz + local_60;
	local_58.vx = player.pos[0];
	local_58.vy = player.pos[1] + -0xac;
	local_58.vz = player.pos[2];
	player.cameraPos.vx = camera_position.vx;
	player.cameraPos.vy = camera_position.vy;
	player.cameraPos.vz = camera_position.vz;
	SetBasePos(&local_58);
	cVar8 = tracking_car;
	setCopControlWord(2, 0xc000, 0x200000);
	setCopControlWord(2, 0xc800, 0x800000);
	tracking_car = '\x01';
	PlaceCameraAtLocation(&player, 0);
	tracking_car = cVar8;
	newShowTanner();
	pDVar9 = current;
	camera_angle._0_4_ = local_70;
	camera_angle._4_4_ = local_6c;
	player.cameraPos.vx = local_80;
	player.cameraPos.vy = local_7c;
	player.cameraPos.vz = local_78;
	player.cameraPos.pad = local_74;
	camera_position.vx = local_80;
	camera_position.vy = local_7c;
	camera_position.vz = local_78;
	camera_position.pad = local_74;
	*(uint *)(&tileTannerClear + current->id * 0x10) =
		*(uint *)(&tileTannerClear + current->id * 0x10) & 0xff000000 |
		current->ot[0x107f] & 0xffffff;
	puVar16 = pDVar9->ot;
	puVar16[0x107f] =
		puVar16[0x107f] & 0xff000000 | (uint)(&tileTannerClear + pDVar9->id * 0x10) & 0xffffff;
	InitCamera(&player);
	setCopControlWord(2, 0xc000, 0xa00000);
	setCopControlWord(2, 0xc800, 0x800000);
	SetDefDrawEnv(auStack224, (int)rectTannerWindow.x, (int)rectTannerWindow.y, (int)rectTannerWindow.w,
		(int)rectTannerWindow.h);
	puVar18 = (uint *)current->primptr;
	SetDrawEnv(puVar18, auStack224);
	pDVar9 = current;
	*puVar18 = *puVar18 & 0xff000000 | current->ot[0x107f] & 0xffffff;
	pDVar9->ot[0x107f] = pDVar9->ot[0x107f] & 0xff000000 | (uint)puVar18 & 0xffffff;
	pDVar9->primptr = pDVar9->primptr + 0x40;
	return;*/
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

void DoCivHead(SVECTOR *vert1, SVECTOR *vert2)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	MODEL *model;
	int iVar3;
	undefined4 in_zero;
	undefined4 in_at;
	int local_b8;
	int local_b4;
	uint uVar4;
	ushort uVar5;
	ushort uVar6;
	ushort uVar7;
	int local_b0;
	int iVar8;
	uint uVar9;
	uint uVar10;
	uint uVar11;
	int iVar12;
	int iVar13;
	uint uVar14;
	int iVar15;
	uint uVar16;
	undefined4 local_a0;
	uint local_9c;
	uint local_98;
	uint local_94;
	uint local_90;
	uint local_8c;
	uint local_88;
	undefined4 local_78;
	undefined4 local_74;
	undefined4 local_70;
	undefined4 local_6c;
	undefined4 local_68;
	undefined4 local_64;
	undefined4 local_60;
	undefined4 local_5c;
	VECTOR local_58;
	uint local_48;
	uint local_44;
	uint local_40;
	uint local_3c;
	undefined4 local_38;

	iVar3 = combointensity;
	model = gPed1HeadModelPtr;
	if (gPed1HeadModelPtr != (MODEL *)0x0) {
		local_78 = getCopControlWord(2, 0);
		local_74 = getCopControlWord(2, 0x800);
		local_70 = getCopControlWord(2, 0x1000);
		local_6c = getCopControlWord(2, 0x1800);
		local_68 = getCopControlWord(2, 0x2000);
		local_64 = getCopControlWord(2, 0x2800);
		local_60 = getCopControlWord(2, 0x3000);
		local_5c = getCopControlWord(2, 0x3800);
		if ((pDrawingPed->pallet & 0xf) == 0) {
			palnumber = -1;
		}
		else {
			palnumber = (uint)civ_clut[(uint)(byte)texturePedHead.texture_number * 6 +
				((uint)pDrawingPed->pallet & 0xf)] << 0x10;
		}
		if (bAllreadyRotated == 0) {
			if (((pDrawingPed->dir).vx == 0) && ((pDrawingPed->dir).vz == 0)) {
				uVar5 = (pDrawingPed->dir).vy;
				if ((uVar5 & 0x3f) == 0) {
					uVar4 = ((uint)uVar5 & 0xfc0) >> 1;
					setCopControlWord(2, 0, *(undefined4 *)((int)matrixtable.m + uVar4));
					setCopControlWord(2, 0x800, *(undefined4 *)((int)matrixtable.m + uVar4 + 4));
					setCopControlWord(2, 0x1000, *(undefined4 *)((int)matrixtable.m + uVar4 + 8));
					setCopControlWord(2, 0x1800, *(undefined4 *)((int)matrixtable.m + uVar4 + 0xc));
					setCopControlWord(2, 0x2000, *(undefined4 *)((int)matrixtable.m + uVar4 + 0x10));
				}
				else {
					local_90 = 0x1000;
					local_88 = local_88 & 0xffff0000 |
						(uint)(ushort)rcossin_tbl
						[((uint)(ushort)(pDrawingPed->dir).vy & 0xfff) * 2 + 1];
					local_98 = (uint)(ushort)rcossin_tbl
						[((uint)(ushort)(pDrawingPed->dir).vy & 0xfff) * 2 + 1];
					local_94 = (uint)(ushort)rcossin_tbl[((uint)(ushort)(pDrawingPed->dir).vy & 0xfff) * 2];
					local_8c = (uint)(ushort)-rcossin_tbl[((uint)(ushort)(pDrawingPed->dir).vy & 0xfff) * 2];
					setCopControlWord(2, 0, local_98);
					setCopControlWord(2, 0x800, local_94);
					setCopControlWord(2, 0x1000, 0x1000);
					setCopControlWord(2, 0x1800, local_8c);
					setCopControlWord(2, 0x2000, local_88);
				}
			}
			else {
				uVar9 = (uint)(ushort)(pDrawingPed->dir).vy & 0xfff;
				uVar4 = (uint)(ushort)(pDrawingPed->dir).vz & 0xfff;
				local_b0 = (int)rcossin_tbl[uVar9 * 2 + 1];
				iVar15 = (int)rcossin_tbl[uVar4 * 2];
				iVar12 = (int)rcossin_tbl[uVar4 * 2 + 1];
				uVar14 = (uint)(ushort)(pDrawingPed->dir).vx & 0xfff;
				local_b8 = (int)rcossin_tbl[uVar14 * 2 + 1];
				iVar8 = (int)rcossin_tbl[uVar9 * 2];
				local_b4 = (int)rcossin_tbl[uVar14 * 2];
				uVar9 = (local_b8 * iVar8 + 0x800 >> 0xc) +
					((local_b0 * local_b4 + 0x800 >> 0xc) * iVar15 + 0x800 >> 0xc);
				uVar10 = local_b0 * iVar12 + 0x800 >> 0xc;
				iVar13 = (int)(short)uVar10;
				uVar5 = -(short)(iVar12 * local_b4 + 0x800 >> 0xc);
				uVar14 = local_b8 * iVar12 + 0x800 >> 0xc;
				local_b8 = (-local_b8 * (local_b0 * iVar15 + 0x800 >> 0xc) + 0x800 >> 0xc) +
					(local_b4 * iVar8 + 0x800 >> 0xc);
				local_98 = uVar10 & 0xffff | local_b8 * 0x10000;
				local_94 = uVar9 & 0xffff | (uint)(ushort)rcossin_tbl[uVar4 * 2] << 0x10;
				local_90 = uVar14 & 0xffff | (uint)uVar5 << 0x10;
				local_8c = CONCAT22((short)(((int)(uVar9 * 0x10000) >> 0x10) * iVar15 + 0x800 >> 0xc) -
					(short)(iVar13 * (short)uVar5 + 0x800 >> 0xc),
					-(short)(iVar8 * iVar12 + 0x800 >> 0xc));
				local_88 = local_88 & 0xffff0000 |
					(uint)(ushort)((short)(iVar13 * (short)uVar14 + 0x800 >> 0xc) -
					(short)((local_b8 * 0x10000 >> 0x10) * iVar15 + 0x800 >> 0xc));
				setCopControlWord(2, 0, local_98);
				setCopControlWord(2, 0x800, local_94);
				setCopControlWord(2, 0x1000, local_90);
				setCopControlWord(2, 0x1800, local_8c);
				setCopControlWord(2, 0x2000, local_88);
			}
			setCopReg(2, in_zero, *(undefined4 *)vert1);
			setCopReg(2, in_at, *(undefined4 *)&vert1->vz);
			copFunction(2, 0x486012);
			local_b8 = getCopReg(2, 0x19);
			local_b4 = getCopReg(2, 0x1a);
			local_b0 = getCopReg(2, 0x1b);
		}
		else {
			local_b8 = (int)vert1->vx;
			local_b4 = (int)vert1->vy;
			local_b0 = (int)vert1->vz;
		}
		setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
		setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
		setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
		setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
		setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
		local_a0 = CONCAT22((short)local_b4 +
			(*(short *)&(pDrawingPed->position).vy - (short)camera_position.vy),
			(short)local_b8 +
			(*(short *)&(pDrawingPed->position).vx - (short)camera_position.vx));
		local_9c = local_9c & 0xffff0000 |
			(uint)(ushort)((short)local_b0 +
			(*(short *)&(pDrawingPed->position).vz - (short)camera_position.vz));
		setCopReg(2, in_zero, local_a0);
		setCopReg(2, in_at, local_9c);
		copFunction(2, 0x486012);
		local_58.vx = getCopReg(2, 0x19);
		local_58.vy = getCopReg(2, 0x1a);
		local_58.vz = getCopReg(2, 0x1b);
		ratan2((int)vert1->vz - (int)vert2->vz, (int)vert1->vy - (int)vert2->vy);
		sVar1 = (pDrawingPed->dir).vy;
		sVar2 = pDrawingPed->head_rot;
		ratan2((int)vert1->vx - (int)vert2->vx, (int)vert1->vy - (int)vert2->vy, pDrawingPed,
			(int)vert1->vy, local_b8, local_b4, local_b0);
		iVar13 = (int)rcossin_tbl[0];
		uVar4 = (uint)(ushort)(sVar1 - sVar2) & 0xfff;
		local_b4 = (int)rcossin_tbl[1];
		local_b8 = rcossin_tbl[uVar4 * 2 + 1] * iVar13 + 0x800 >> 0xc;
		local_b0 = local_b4 * rcossin_tbl[uVar4 * 2] + 0x800 >> 0xc;
		uVar14 = local_b0 + (local_b8 * iVar13 + 0x800 >> 0xc);
		uVar10 = rcossin_tbl[uVar4 * 2 + 1] * local_b4 + 0x800 >> 0xc;
		uVar5 = -(short)(local_b4 * iVar13 + 0x800 >> 0xc);
		uVar11 = local_b4 * local_b4 + 0x800 >> 0xc;
		uVar9 = (-local_b4 * local_b8 + 0x800 >> 0xc) + (iVar13 * rcossin_tbl[uVar4 * 2] + 0x800 >> 0xc)
			;
		local_98 = uVar10 & 0xffff | uVar9 * 0x10000;
		uVar7 = -(short)local_b0;
		uVar4 = uVar14 & 0xffff;
		local_94 = uVar4 | (uint)(ushort)rcossin_tbl[0] << 0x10;
		local_90 = uVar11 & 0xffff | (uint)uVar5 << 0x10;
		uVar6 = (short)(((int)(uVar14 * 0x10000) >> 0x10) * iVar13 + 0x800 >> 0xc) -
			(short)((int)(short)uVar10 * (int)(short)uVar5 + 0x800 >> 0xc);
		local_8c = CONCAT22(uVar6, uVar7);
		uVar14 = (uint)(ushort)((short)((int)(short)uVar10 * (int)(short)uVar11 + 0x800 >> 0xc) -
			(short)(((int)(uVar9 * 0x10000) >> 0x10) * iVar13 + 0x800 >> 0xc));
		local_88 = local_88 & 0xffff0000 | uVar14;
		setCopControlWord(2, 0, local_98);
		setCopControlWord(2, 0x800, local_94);
		setCopControlWord(2, 0x1000, local_90);
		setCopControlWord(2, 0x1800, local_8c);
		setCopControlWord(2, 0x2000, local_88);
		if (gNight != 0) {
			combointensity = (int)&DAT_00404040;
		}
		setCopControlWord(2, 0x2800, local_58.vx);
		setCopControlWord(2, 0x3000, local_58.vy);
		setCopControlWord(2, 0x3800, local_58.vz);
		setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
		setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
		setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
		setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
		setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
		setCopReg(2, 0x4800, uVar10 & 0xffff);
		setCopReg(2, 0x5000, (uint)(ushort)rcossin_tbl[0]);
		setCopReg(2, 0x5800, (uint)uVar7);
		copFunction(2, 0x49e012);
		uVar10 = getCopReg(2, 0x4800);
		local_b4 = getCopReg(2, 0x5000);
		uVar16 = getCopReg(2, 0x5800);
		setCopReg(2, 0x4800, uVar9 & 0xffff);
		setCopReg(2, 0x5000, uVar11 & 0xffff);
		setCopReg(2, 0x5800, (uint)uVar6);
		copFunction(2, 0x49e012);
		local_b8 = getCopReg(2, 0x4800);
		uVar9 = getCopReg(2, 0x5000);
		local_b0 = getCopReg(2, 0x5800);
		local_48 = uVar10 & 0xffff | local_b8 << 0x10;
		local_3c = uVar16 & 0xffff | local_b0 << 0x10;
		setCopReg(2, 0x4800, uVar4);
		setCopReg(2, 0x5000, (uint)uVar5);
		setCopReg(2, 0x5800, uVar14);
		copFunction(2, 0x49e012);
		uVar4 = getCopReg(2, 0x4800);
		local_b8 = getCopReg(2, 0x5000);
		uVar14 = getCopReg(2, 0x5800);
		local_44 = uVar4 & 0xffff | local_b4 << 0x10;
		local_40 = uVar9 & 0xffff | local_b8 << 0x10;
		local_38 = uVar14 & 0xffff | (uint)local_38._2_2_ << 0x10;
		setCopControlWord(2, 0, local_48);
		setCopControlWord(2, 0x800, local_44);
		setCopControlWord(2, 0x1000, local_40);
		setCopControlWord(2, 0x1800, local_3c);
		setCopControlWord(2, 0x2000, local_38);
		DrawObject(model, (MATRIX *)&local_98, &local_58, 1);
		if (gNight != 0) {
			combointensity = iVar3;
		}
		setCopControlWord(2, 0, local_78);
		setCopControlWord(2, 0x800, local_74);
		setCopControlWord(2, 0x1000, local_70);
		setCopControlWord(2, 0x1800, local_6c);
		setCopControlWord(2, 0x2000, local_68);
		palnumber = -1;
	}
	return;*/
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





