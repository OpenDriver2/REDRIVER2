#include "driver2.h"
#include "motion_c.h"
#include "pedest.h"
#include "system.h"
#include "mission.h"
#include "texture.h"
#include "camera.h"
#include "shadow.h"
#include "debris.h"
#include "draw.h"
#include "dr2roads.h"
#include "sky.h"
#include "players.h"
#include "main.h"

#include "cars.h"
#include "convert.h"

#ifdef USE_PGXP
#include <math.h>
#endif

enum LIMBS
{
	ROOT = 0,
	LOWERBACK = 1,
	JOINT_1 = 2,
	NECK = 3,
	HEAD = 4,
	LSHOULDER = 5,
	LELBOW = 6,
	LHAND = 7,
	LFINGERS = 8,
	RSHOULDER = 9,
	RELBOW = 10,
	RHAND = 11,
	RFINGERS = 12,
	HIPS = 13,
	LHIP = 14,
	LKNEE = 15,
	LFOOT = 16,
	LTOE = 17,
	RHIP = 18,
	RKNEE = 19,
	RFOOT = 20,
	RTOE = 21,
	JOINT = 22,
};

enum TEXTURE_PALS
{
	NO_PAL = 0,
	JEANS_PAL = 1,
	ARM_PAL = 2,
	CHEST_PAL = 3,
};

struct BONE
{
	LIMBS id;
	BONE* pParent;
	char numChildren;
	BONE(*pChildren[3]);
	SVECTOR_NOPAD* pvOrigPos;
	SVECTOR* pvRotation;
	VECTOR vOffset;
	VECTOR vCurrPos;
	MODEL** pModel;
};

struct PED_DATA
{
	char cWidth;
	u_char cAdj;
	TEXTURE_DETAILS* ptd;
	TEXTURE_PALS texPal;
};

#define NUM_BONES 23

LIMBS lRoutes[5][8] = {
	{
		ROOT,		LOWERBACK,
		HIPS,		LHIP,
		LKNEE,		LFOOT,
		LTOE,		ROOT
	},
	{
		HIPS,		RHIP,
		RKNEE,		RFOOT,
		RTOE,		ROOT,
		ROOT,		ROOT
	},
	{
		LOWERBACK,	JOINT_1,
		LSHOULDER,	LELBOW,
		LHAND,		LFINGERS,
		ROOT,		ROOT
	},
	{
		JOINT_1,	RSHOULDER,
		RELBOW,		RHAND,
		RFINGERS,	ROOT,
		ROOT,		ROOT
	},
	{
		JOINT_1,	NECK,
		HEAD,		ROOT,
		ROOT,		ROOT,
		ROOT,		ROOT
	},
};

PED_DATA MainPed[NUM_BONES] =
{
	{ 0, 68u, &chest1_texture, CHEST_PAL },   
	{ 1, 68u, &chest1_texture, CHEST_PAL },
	{ 17, 36u, &chest1_texture, CHEST_PAL },
	{ 6, 68u, &forearm1_texture, ARM_PAL },
	{ 8, 22u, &head1_texture, NO_PAL },
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
BONE Skel[NUM_BONES] =
{
	{
		ROOT,
		NULL,
		2,
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
		&Skel[ROOT],
		2,
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

int boneIdvals[] = {
	// 1
	JOINT_1,
	NECK,
	HEAD,

	// 2
	LELBOW,
	LHAND,
	LFINGERS,

	// 3
	RELBOW,
	RHAND,
	RFINGERS,

	// 4
	LKNEE,
	LFOOT,
	LTOE,

	// 5
	RKNEE,
	RFOOT,
	RTOE
};

TEXTURE_DETAILS jeans_texture;
TEXTURE_DETAILS arm1_texture;
TEXTURE_DETAILS forearm1_texture;
TEXTURE_DETAILS chest1_texture;
TEXTURE_DETAILS head1_texture;

MODEL* gPed1HeadModelPtr;
MODEL* gPed2HeadModelPtr;
MODEL* gPed3HeadModelPtr;
MODEL* gPed4HeadModelPtr;

char* MotionCaptureData[MAX_MOTION_CAPTURE];	// [A] actually, pointers
int ThisMotion;

short cTannerVNumbers[24];
SVECTOR vTannerList[210];

short cJerichoVNumbers[7];
SVECTOR vJerichoList[102];

int vStored = 0;

// [D] [T]
void ProcessMotionLump(char* lump_ptr, int lump_size)
{
	if (ThisMotion < MAX_MOTION_CAPTURE)
	{
		int size = (lump_size + 3) & ~3;

		D_MALLOC_BEGIN();
		MotionCaptureData[ThisMotion] = D_MALLOC(size);
		D_MALLOC_END();

		memcpy((u_char*)MotionCaptureData[ThisMotion], (u_char*)lump_ptr, size);

		ThisMotion++;
	}
}

// [D] [T]
void SetupPedMotionData(LPPEDESTRIAN pPed)
{
	pPed->motion = MotionCaptureData[pPed->type];
}


// [D] [T]
void SetupPedestrian(LPPEDESTRIAN pedptr)
{
	pedptr->velocity.vy = 10;
	pedptr->speed = 10;

	pedptr->dir.vx = 0;
	pedptr->dir.vz = 0;

	pedptr->frame1 = 0;
	pedptr->motion = MotionCaptureData[pedptr->type];
}

int bDoingShadow = 0;
int gCurrentZ;

// [D] [T] [A]
void DrawBodySprite(LPPEDESTRIAN pDrawingPed, int boneId, VERTTYPE v1[2], VERTTYPE v2[2], int sz, int sy)
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
	int angle;
	char tmp;
	int tmp2;
	int dx1, dy1,dx2,dy2;
	int width;
	POLY_FT4* prims;
	LIMBS bone;
	TEXTURE_DETAILS* body_texture;
	int x, y, z, z2;
	int tpage;
	int pal;
	int cs, sn;

	bone = (LIMBS)(boneId & 0x7f);
	body_texture = MainPed[bone].ptd;
	
	if (bDoingShadow)
		z = sz + (scr_z / 2);
	else
		z = gCurrentZ + (scr_z / 2);

	z2 = ((scr_z * 4096) / z) * 25 >> 5;

	if (bone == JOINT_1)
	{
		// make ped thinner from side view
		u_int ang;
		ang = RCOS((pDrawingPed->dir.vy + camera_angle.vy) * 2) >> 6;

		z2 += ang;
	}

	if (pDrawingPed->type == PED_ACTION_JUMP)
	{
		width = MainPed[bone].cWidth + 4;
	}
	else
	{
		if (pDrawingPed->flags & 0x8000)
			width = MainPed[bone].cWidth - 3;
		else if (pDrawingPed->flags & 0x4000)
			width = MainPed[bone].cWidth + 8;
		else
			width = MainPed[bone].cWidth + 3;
	}

	if (bDoingShadow &&
		(bone == RKNEE || bone == LKNEE || 
		bone == LFOOT || bone == RFOOT))
	{
		width -= 5;
	}

	x = v1[0] - v2[0];
	y = v1[1] - v2[1];

	angle = -ratan2(y, x);
	
	cs = FIXEDH(z2 * RSIN(angle) * (width & 0x3f) * 2);
	sn = FIXEDH(z2 * RCOS(angle) * (width & 0x3f) * 2);

	tmp = MainPed[bone].cAdj & 0xf;

	dx2 = x >> tmp;
	dy2 = y >> tmp;

	if ((bone == RKNEE || bone == LKNEE) && pDrawingPed->type != PED_ACTION_JUMP && bDoingShadow == 0)
	{
		dx1 = -x >> 3;
		dy1 = -y >> 3;
	}
	else
	{
		tmp2 = MainPed[bone].cAdj >> 4;
		
		dx1 = x >>tmp2;
		dy1 = y >> tmp2;
	}

	prims = (POLY_FT4*)current->primptr;
	setPolyFT4(prims);

	current->primptr += sizeof(POLY_FT4);

	prims->x0 = v1[0] + FIXEDH(cs) + dx2;
	prims->y0 = v1[1] + FIXEDH(sn) + dy2;

	prims->x1 = v1[0] - FIXEDH(cs) + dx2;
	prims->y1 = v1[1] - FIXEDH(sn) + dy2;

	prims->x2 = v2[0] + FIXEDH(cs) - dx1;
	prims->y2 = v2[1] + FIXEDH(sn) - dy1;

	prims->x3 = v2[0] - FIXEDH(cs) - dx1;
	prims->y3 = v2[1] - FIXEDH(sn) - dy1;

#ifdef USE_PGXP
	if (!bDoingShadow) // [A] Psy-X is currently incorrectly offsets the offscreen PGXP geometry. We don't need it anyway.
	{
		ushort pgxpIdx = PGXP_GetIndex(0) - 64;
		PGXPVData vdata1, vdata2;
		PGXP_GetCacheData(&vdata1, PGXP_LOOKUP_VALUE(v1[0], v1[1]), pgxpIdx);
		PGXP_GetCacheData(&vdata2, PGXP_LOOKUP_VALUE(v2[0], v2[1]), pgxpIdx);

		{
			float len;

			x = (v1[0] - v2[0]) * 4.0f;
			y = (v1[1] - v2[1]) * 4.0f;

			// compute normalization lengths
			len = 1.0 / sqrtf(float(x*x) + float(y*y) + 1.0);

			angle = -ratan2(y, x);

			sn = RSIN(angle) * width;
			cs = RCOS(angle) * width;

			tmp = MainPed[bone].cAdj & 0xf;

			dx2 = sn >> tmp;
			dy2 = cs >> tmp;

			if ((bone == RKNEE || bone == LKNEE) && pDrawingPed->type != PED_ACTION_JUMP && bDoingShadow == 0)
			{
				dx1 = -sn >> 3;
				dy1 = -cs >> 3;
			}
			else
			{
				tmp2 = MainPed[bone].cAdj >> 4;

				dx1 = sn >> tmp2;
				dy1 = cs >> tmp2;
			}

			dx1 = FIXED(dx1);
			dx2 = FIXED(dx2);
			dy1 = FIXED(dy1) + 2;
			dy2 = FIXED(dy2) - 2;

			if (bone == HEAD)
			{
				dx1 >>= 1;
				dx2 >>= 1;
			}

			if (bone == JOINT_1)
			{
				dx1 -= 5;
				dy2 -= 10;
			}
		}

		PGXPVData v0data = { PGXP_LOOKUP_VALUE(prims->x0, prims->y0),
			vdata1.px + (FIXEDH(sn) - dx1) * 0.01f,
			vdata1.py + (FIXEDH(cs) + dy1) * 0.01f,
			vdata1.pz, vdata1.scr_h, vdata1.ofx, vdata1.ofy };


		PGXPVData v1data = { PGXP_LOOKUP_VALUE(prims->x1, prims->y1),
			vdata1.px - (FIXEDH(sn) - dx1) * 0.01f,
			vdata1.py - (FIXEDH(cs) - dy1) * 0.01f,
			vdata1.pz, vdata1.scr_h, vdata1.ofx, vdata1.ofy };


		PGXPVData v2data = { PGXP_LOOKUP_VALUE(prims->x2, prims->y2),
			vdata2.px + (FIXEDH(sn) + dx2) * 0.01f,
			vdata2.py + (FIXEDH(cs) - dy2) * 0.01f,
			vdata2.pz, vdata2.scr_h, vdata2.ofx, vdata2.ofy };


		PGXPVData v3data = { PGXP_LOOKUP_VALUE(prims->x3, prims->y3),
			vdata2.px - (FIXEDH(sn) + dx2) * 0.01f,
			vdata2.py - (FIXEDH(cs) + dy2) * 0.01f,
			vdata2.pz, vdata2.scr_h, vdata2.ofx, vdata2.ofy };

		PGXP_EmitCacheData(&v0data);
		PGXP_EmitCacheData(&v1data);
		PGXP_EmitCacheData(&v2data);
		PGXP_EmitCacheData(&v3data);
	}
#endif

	if (bDoingShadow)
	{
		tpage = texture_pages[gShadowTexturePage];
		clut = texture_cluts[gShadowTexturePage][gShadowTextureNum];
	}
	else
	{
		tpage = body_texture->tpageid;
		clut = body_texture->clutid;

		if (MainPed[bone].texPal != NO_PAL)
		{
			pal = MainPed[bone].texPal == JEANS_PAL ? (pDrawingPed->pallet >> 4) : (pDrawingPed->pallet & 0xf);

			if (pal != 0)
				clut = civ_clut[0][body_texture->texture_number][pal];
		}
		else if(bone == HEAD)
		{
			pal = (pDrawingPed->pallet & 0xf);

			if (pal != 0)
				clut = civ_clut[0][body_texture->texture_number][pal];
		}
	}

	prims->tpage = tpage;
	prims->clut = clut;

	if (bDoingShadow)
	{
		setSemiTrans(prims, 1);
		prims->tpage |= 0x20;

		*(ushort*)&prims->u0 = *(ushort*)&shadowuv.u0;
		*(ushort*)&prims->u1 = *(ushort*)&shadowuv.u1;
		*(ushort*)&prims->u2 = *(ushort*)&shadowuv.u2;
		*(ushort*)&prims->u3 = *(ushort*)&shadowuv.u3;
	}
	else
	{
		if (bone == HEAD)
		{
			x = (-camera_angle.vy - pDrawingPed->dir.vy & 0xfffU) >> 7;

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
			*(ushort*)&prims->u0 = *(ushort*)&body_texture->coords.u0;
			*(ushort*)&prims->u1 = *(ushort*)&body_texture->coords.u1;
			*(ushort*)&prims->u2 = *(ushort*)&body_texture->coords.u2;
			*(ushort*)&prims->u3 = *(ushort*)&body_texture->coords.u3;
		}
		else
		{
			*(ushort*)&prims->u0 = *(ushort*)&body_texture->coords.u2;
			*(ushort*)&prims->u1 = *(ushort*)&body_texture->coords.u3;
			*(ushort*)&prims->u2 = *(ushort*)&body_texture->coords.u0;
			*(ushort*)&prims->u3 = *(ushort*)&body_texture->coords.u1;
		}
	}

	if (bDoingShadow)
	{
		prims->r0 = 254;
		prims->g0 = 254;
		prims->b0 = 254;
	}
	else if (gNight)
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

	if (bDoingShadow != 0)
	{
		addPrim(current->ot + OTSIZE - 1, prims);
	}
	else
	{
		x = sz + sy >> 4;
		addPrim(current->ot + x + (width >> 6), prims);
	}
}

// [D] [T]
void StoreVertexLists(void)
{
	BONE* pBone;
	SVECTOR* destVerts;
	SVECTOR* srcVerts;
	MODEL* pModel;
	int i,j,counter;

	// store Tanner vertices
	counter = 0;
	for (i = 0; i < 23; i++)
	{
		pBone = &Skel[i];

		if (pBone->pModel == NULL)
		{
			cTannerVNumbers[i] = -1;
			continue;
		}

		pModel = *pBone->pModel;

		if (pModel == NULL)
		{
			cTannerVNumbers[i] = -1;
			continue;
		}
		
		// store start index
		cTannerVNumbers[i] = counter;

		destVerts = &vTannerList[counter];
		srcVerts = (SVECTOR*)pModel->vertices;

		for (j = 0; j < pModel->num_vertices; j++)
		{
			destVerts->vx = srcVerts->vx;
			destVerts->vy = srcVerts->vy;
			destVerts->vz = srcVerts->vz;

			srcVerts++;
			destVerts++;
			counter++;
		}
	}

	// Store Jericho vertices
	counter = 0;
	for (i = 0; i < 6; i++)
	{
		pModel = pmJerichoModels[i];

		if (pModel == NULL)
		{
			cJerichoVNumbers[i] = -1;
			continue;
		}

		srcVerts = (SVECTOR*)pModel->vertices;

		// store start index
		cJerichoVNumbers[i] = counter;

		destVerts = &vJerichoList[counter];

		for (j = 0; j < pModel->num_vertices; j++)
		{
			destVerts->vx = srcVerts->vx;
			destVerts->vy = srcVerts->vy;
			destVerts->vz = srcVerts->vz;

			srcVerts++;
			destVerts++;
			counter++;
		}
	}

	vStored = 1;
}

#define BODY_OFFSET 8
#define TORSO_OFFSET -2

#define JERICHO_BODY_OFFSET 6
#define JERICHO_TORSO_OFFSET -5

int bodyShiftEnabled = 1;

int bodyShiftValue = BODY_OFFSET;
int torsoShiftValue = TORSO_OFFSET;

// [D] [T]
void SetupTannerSkeleton(LPPEDESTRIAN pDrawingPed)
{
	int i;
	BONE* pBone;
	char* pC;
	SVECTOR* store;
	SVECTOR_NOPAD* pSVNP;

	Skel[ROOT].pvOrigPos = (SVECTOR_NOPAD*)(pDrawingPed->motion + pDrawingPed->frame1 * 144 + 146);
	Skel[ROOT].pvRotation = (SVECTOR*)(pDrawingPed->motion + pDrawingPed->frame1 * 144 + 152);

	Skel[ROOT].vCurrPos.vx = Skel[ROOT].pvOrigPos->vx;
	Skel[ROOT].vCurrPos.vy = -Skel[ROOT].pvOrigPos->vy;
	Skel[ROOT].vCurrPos.vz = -Skel[ROOT].pvOrigPos->vz;

	Skel[ROOT].vOffset.vx = 0;
	Skel[ROOT].vOffset.vy = 0;
	Skel[ROOT].vOffset.vz = 0;

	pC = (pDrawingPed->motion + pDrawingPed->frame1 * 144 + 158);
	pSVNP = (SVECTOR_NOPAD*)(pDrawingPed->motion + 14);

	for (i = 1; i < NUM_BONES; i++)
	{
		pBone = &Skel[i];

		pBone->pvRotation = (SVECTOR*)pC;
		pBone->pvOrigPos = &pSVNP[i - 1];

		pC += sizeof(SVECTOR_NOPAD);
	}

#ifdef PSX
	store = (SVECTOR*)((u_char*)getScratchAddr(0) + 0x200);
#else
	SVECTOR scratchVectors[64];
	store = scratchVectors;
#endif

	store[LOWERBACK].vx = Skel[LOWERBACK].pvOrigPos->vx;
	store[LOWERBACK].vy = -Skel[LOWERBACK].pvOrigPos->vy;
	store[LOWERBACK].vz = -Skel[LOWERBACK].pvOrigPos->vz;

	// start at the torso and traverse down
	for (i = 2; i < NUM_BONES; i++)
	{
		pBone = &Skel[i];

		store[i].vx = pBone->pvOrigPos->vx - pBone->pParent->pvOrigPos->vx;
		store[i].vy = pBone->pParent->pvOrigPos->vy - pBone->pvOrigPos->vy;
		store[i].vz = pBone->pParent->pvOrigPos->vz - pBone->pvOrigPos->vz;

		if (pBone->id == JOINT_1 && bodyShiftEnabled)
		{
			store[i].vy -= bodyShiftValue;
			store[i].vz -= torsoShiftValue;
		}
	}

	// start at the lower back and traverse down
	for (i = 1; i < NUM_BONES; i++)
	{
		pBone = &Skel[i];

		pBone->vCurrPos.vx = store[i].vx;
		pBone->vOffset.vx = store[i].vx;

		pBone->vCurrPos.vy = store[i].vy;
		pBone->vOffset.vy = store[i].vy;

		pBone->vCurrPos.vz = store[i].vz;
		pBone->vOffset.vz = store[i].vz;
	}

#if 0
	// Draw T POSE
	{
		extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
		extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

		CVECTOR bbcv = { 0, 0, 250 };
		CVECTOR rrcv = { 250, 0, 0 };
		CVECTOR yycv = { 250, 250, 0 };

		for (int i = 0; i < NUM_BONES; i++)
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

// [A] - was inlined in newShowTanner
void DrawSprite(LPPEDESTRIAN pDrawingPed, BONE* pBone, VECTOR* vJPos)
{
	VERTTYPE t0[2], t1[2]; // [A] was two longs
	int z, z1, z2;

#ifdef PSX
	SVECTOR* data = (SVECTOR*)((u_char*)getScratchAddr(0) + 0x200);
#else
	SVECTOR scratchVectors[64];
	SVECTOR* data = scratchVectors;
#endif

	data[0].vx = vJPos[pBone->id & 0x7f].vx + pDrawingPed->position.vx - camera_position.vx;
	data[0].vy = vJPos[pBone->id & 0x7f].vy + pDrawingPed->position.vy - camera_position.vy;
	data[0].vz = vJPos[pBone->id & 0x7f].vz + pDrawingPed->position.vz - camera_position.vz;

	data[1].vx = vJPos[pBone->pParent->id & 0x7f].vx + pDrawingPed->position.vx - camera_position.vx;
	data[1].vy = vJPos[pBone->pParent->id & 0x7f].vy + pDrawingPed->position.vy - camera_position.vy;
	data[1].vz = vJPos[pBone->pParent->id & 0x7f].vz + pDrawingPed->position.vz - camera_position.vz;

	gte_ldv0(&data[0]);
	gte_ldv1(&data[1]);

	gte_rtpt();
	gte_stsxy0(t0);
	gte_stsxy1(t1);

	gte_stsz3(&z, &z1, &z2);

	gCurrentZ = z;

	DrawBodySprite(pDrawingPed, pBone->id, t0, t1, z, z1);
}

int bAllreadyRotated = 0;

// [D] [T]
void newShowTanner(LPPEDESTRIAN pDrawingPed)
{
	int i, j;
	int draw;

#ifdef PSX
	VECTOR* spad = (VECTOR*)((u_char*)getScratchAddr(0) + 0x100);
#else
	VECTOR spad[64];
#endif

	VECTOR* playerPos = &spad[0];
	VECTOR* cameraPos = &spad[1];
	VECTOR* vJPos = &spad[2];

	playerPos->vx = pDrawingPed->position.vx;
	playerPos->vy = pDrawingPed->position.vy - 15;	// [A] elevate Tanner model a little bit so his legs are not in the ground (when Z-buffer enabled)
	playerPos->vz = pDrawingPed->position.vz;

	cameraPos->vx = camera_position.vx;
	cameraPos->vy = camera_position.vy;
	cameraPos->vz = camera_position.vz;

	vJPos[ROOT].vx = Skel[ROOT].pvOrigPos->vx;
	vJPos[ROOT].vy = -Skel[ROOT].pvOrigPos->vy;
	vJPos[ROOT].vz = Skel[ROOT].pvOrigPos->vz;

	VECTOR v = { 0, 0, 0 };

	gte_SetTransVector(&v);

	// do not draw the root
	Skel[ROOT].id = (LIMBS)(Skel[ROOT].id | 0x80);

	draw = (pDrawingPed->padId > -1 && pDrawingPed->padId == CurrentPlayerView)
		? player[pDrawingPed->padId].cameraView != 2
		: 1;

	for (i = 0; i < 5; i++)
	{
		for (j = 1; j < 8; j++)
		{
			int id;

			id = lRoutes[i][j];

			if (id == ROOT)
				break;

			BONE* pBone = &Skel[id];

			if (pBone->id < 0x7f)
			{
				int lval;

				lval = lRoutes[i][j - 1];

				vJPos[pBone->id].vx = vJPos[lval].vx + pBone->vCurrPos.vx;
				vJPos[pBone->id].vy = vJPos[lval].vy + pBone->vCurrPos.vy;
				vJPos[pBone->id].vz = vJPos[lval].vz + pBone->vCurrPos.vz;

				if (pDrawingPed->pedType == TANNER_MODEL && pBone->id == HEAD)
					pDrawingPed->head_pos = vJPos[lval].vy;

				if (pBone->pModel != NULL
					&& !bDoingShadow
					&& pDrawingPed->pedType < OTHER_SPRITE
					&& draw)
				{
					MODEL* model = *pBone->pModel;

					for (int c = 0; c < model->num_vertices; c++)
					{
						SVECTOR* mVerts = (SVECTOR*)model->vertices + c;

						mVerts->vx += (vJPos[lval].vx + playerPos->vx - cameraPos->vx);
						mVerts->vy += (vJPos[lval].vy + playerPos->vy - cameraPos->vy);
						mVerts->vz += (vJPos[lval].vz + playerPos->vz - cameraPos->vz);
					}
				}

				pBone->id = (LIMBS)(pBone->id | 0x80);
			}
		}
	}

	if(bDoingShadow || draw)
	{
		if (pDrawingPed->pedType < OTHER_SPRITE)
		{
			// draw LOWERBACK - RTOE
			for (i = 1; i < NUM_BONES - 1; i++)
			{
				int id;
				BONE* pBone;

				pBone = &Skel[i];
				id = pBone->id & 0x7f;

				if (bDoingShadow)
				{
					if (id != LSHOULDER
						&& id != RSHOULDER
						&& id != HIPS
						&& id != LOWERBACK
						&& id != ROOT
						&& id != JOINT
						&& id != LHIP
						&& id != RHIP)
					{
						DrawSprite(pDrawingPed, pBone, vJPos);
					}
				}
				else if (pBone->pModel != NULL)
				{
					MODEL* model = *pBone->pModel;

					int bias = 2;

					if (id == JOINT_1)
						bias = 1;
					else if (id == HEAD)
						bias = 0;
					
					RenderModel(model, NULL, &v, bias, PLOT_NO_SHADE, 0, 0);
				}

#if 0
				// DEBUG DRAW SKELETON
				{
					extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
					extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

					CVECTOR bbcv = { 0, 0, 250 };
					CVECTOR rrcv = { 250, 0, 0 };
					CVECTOR yycv = { 250, 250, 0 };

					VECTOR v0 = {
						vJPos[pBone->id & 0x7f].vx,
						-vJPos[pBone->id & 0x7f].vy,
						vJPos[pBone->id & 0x7f].vz
					};

					VECTOR v1 = {
						vJPos[pBone->pParent->id & 0x7f].vx,
						-vJPos[pBone->pParent->id & 0x7f].vy,
						vJPos[pBone->pParent->id & 0x7f].vz
					};

					VECTOR ofs = *(VECTOR*)&pDrawingPed->position;
					ofs.vy = -ofs.vy;
					//ofs.vy += 270;

					Debug_AddLineOfs(v0, v1, ofs, bbcv);
				}
#endif
			}
		}
		else
		{
			// draw LOWERBACK - RTOE
			for (i = 1; i < NUM_BONES - 1; i++)
			{
				BONE* pBone = &Skel[i];

				int id = pBone->id & 0x7f;

				if (id != LSHOULDER
					&& id != RSHOULDER
					&& id != HEAD
					&& id != HIPS
					&& id != LOWERBACK
					&& id != ROOT
					&& id != JOINT
					&& id != LHIP
					&& id != RHIP)
				{
					DrawSprite(pDrawingPed, pBone, vJPos);
				}
			}

			// draw HEAD
			BONE* pBone = &Skel[HEAD];

			if (switch_detail_distance >> 2 < gCurrentZ)
			{
				DrawSprite(pDrawingPed, pBone, vJPos);
			}
			else
			{
				SVECTOR v1, v2;

				v1.vx = vJPos[pBone->id & 0x7f].vx;
				v1.vy = vJPos[pBone->id & 0x7f].vy;
				v1.vz = vJPos[pBone->id & 0x7f].vz;

				v2.vx = vJPos[pBone->pParent->id & 0x7f].vx;
				v2.vy = vJPos[pBone->pParent->id & 0x7f].vy;
				v2.vz = vJPos[pBone->pParent->id & 0x7f].vz;

				bAllreadyRotated = 1;
				DoCivHead(pDrawingPed, &v2, &v1);
				bAllreadyRotated = 0;
			}
		}
	}

	// clear all id flags
	for (i = 0; i < NUM_BONES; i++)
		Skel[i].id = (LIMBS)(Skel[i].id & 0x7f);
}

// [D] [T]
SVECTOR* GetModelVertPtr(LPPEDESTRIAN pDrawingPed, int boneId, int modelType)
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
		case JOINT_1:
			startVertex = cJerichoVNumbers[0];
			break;
		case HEAD:
			startVertex = cJerichoVNumbers[1];
			break;
		case LELBOW:
			startVertex = cJerichoVNumbers[2];
			break;
		case LHAND:
			startVertex = cJerichoVNumbers[3];
			break;
		case RELBOW:
			startVertex = cJerichoVNumbers[4];
			break;
		case RHAND:
			startVertex = cJerichoVNumbers[5];
			break;
		default:
			return vTannerList + cTannerVNumbers[boneId & 0x7f];
	}

	return vJerichoList + startVertex;
}

// [D] [T]
void newRotateBones(LPPEDESTRIAN pDrawingPed, BONE* poBone)
{
	SVECTOR* pVerts;
	MODEL* pModel;
	MATRIX mStore[32];
	int i, j;

	MATRIX _sMatrix;
	MATRIX _pMatrix;
	MATRIX _oMatrix;

	SVECTOR _svBone[2];
	SVECTOR _pD[80];
	VECTOR _vBoneRotated;

	_pMatrix.t[0] = Skel[0].pvOrigPos->vx;
	_pMatrix.t[1] = Skel[0].pvOrigPos->vy;
	_pMatrix.t[2] = Skel[0].pvOrigPos->vz;

	// [A] it just happened to be bugged and weird implementation of YXZ rotation
	// replaced with regular RotMatrixYXZ
	SVECTOR r;
	r.vx = pDrawingPed->dir.vx & 0xfff;
	r.vy = pDrawingPed->dir.vy & 0xfff;
	r.vz = pDrawingPed->dir.vz & 0xfff;

	RotMatrixYXZ(&r, &_pMatrix);

	_svBone[0].vx = Skel[0].vOffset.vx;
	_svBone[0].vy = Skel[0].vOffset.vy;
	_svBone[0].vz = Skel[0].vOffset.vz;

	mStore[0] = _pMatrix;

	for (i = 0; i < 5; i++)
	{
		for (j = 1; j < 8; j++)
		{
			int id = lRoutes[i][j];

			if (id == ROOT)
				break;

			BONE* pBone = &Skel[id];

			_svBone[0].vx = pBone->vOffset.vx;
			_svBone[0].vy = pBone->vOffset.vy;
			_svBone[0].vz = pBone->vOffset.vz;

			if (bReverseYRotation == 0 || pBone->pParent->id != ROOT)
			{
				_svBone[1].vx = -pBone->pParent->pvRotation->vx;
				_svBone[1].vy = pBone->pParent->pvRotation->vy;
				_svBone[1].vz = pBone->pParent->pvRotation->vz;
			}
			else
			{
				_svBone[1].vx = pBone->pParent->pvRotation->vx;
				_svBone[1].vy = -pBone->pParent->pvRotation->vy;
				_svBone[1].vz = pBone->pParent->pvRotation->vz;
			}

			if (id == HEAD)
				_svBone[1].vy -= pDrawingPed->head_rot;

			RotMatrixZYX_gte(&_svBone[1], &_sMatrix);

			_sMatrix.t[0] = _svBone[0].vx;
			_sMatrix.t[1] = _svBone[0].vy;
			_sMatrix.t[2] = _svBone[0].vz;

			_pMatrix = mStore[pBone->pParent->id & 0x7f];

			gte_MulMatrix0(&_pMatrix, &_sMatrix, &_oMatrix);
			gte_SetRotMatrix(&_oMatrix);

			gte_ldv0(&_svBone[0]);
			gte_rtv0();

			gte_stlvnl(&_vBoneRotated);

			pBone->vCurrPos.vx = _vBoneRotated.vx;
			pBone->vCurrPos.vy = _vBoneRotated.vy;
			pBone->vCurrPos.vz = _vBoneRotated.vz;

			if (pBone->id < 0x7f)
			{
				pVerts = GetModelVertPtr(pDrawingPed, pBone->id, 0);

				if ((pDrawingPed->pedType < OTHER_SPRITE || pBone->id == HEAD)
					&& pBone->pModel != NULL
					&& pVerts != NULL)
				{
					pModel = *pBone->pModel;

					SVECTOR* pmVerts = (SVECTOR*)pModel->vertices;
					int numVerts = pModel->num_vertices;

					for (int c = 0; c < numVerts; c++)
					{
						_pD[c].vx = pVerts[c].vx + _svBone[0].vx;
						_pD[c].vy = pVerts[c].vy + _svBone[0].vy;
						_pD[c].vz = pVerts[c].vz + _svBone[0].vz;
					}

					for (int c = 0; c < numVerts; c++)
					{
						gte_ldv0(&_pD[c]);

						gte_rtv0();

						gte_stlvnl(&_vBoneRotated);

						pmVerts[c].vx = _vBoneRotated.vx;
						pmVerts[c].vy = _vBoneRotated.vy;
						pmVerts[c].vz = _vBoneRotated.vz;
					}
				}
			}

			mStore[id] = _oMatrix;
		}
	};
}


// [D] [T]
void DrawCiv(LPPEDESTRIAN pPed)
{
	SVECTOR* vert2;
	SVECTOR* vert1;
	short size;
	int shift;
	int boneId;
	int frame;
	int i, j;
	int phase;
	SVECTOR pos;
	VECTOR pos1;
	SVECTOR rot;
	MATRIX workmatrix;
	CVECTOR cv;
	VECTOR ppos;
	int bHeadModel;

	DVECTOR sxyList[40];
	int szList[40];
	SVECTOR srLerpData[40];

	bHeadModel = 0;

	frame = pPed->frame1 / 2;

	vert1 = (SVECTOR*)pPed->motion;

	// [A] alpha 1.6 bug fix
	if (!vert1)
		return;

	vert2 = vert1 + frame * 30;

	shift = (pPed->flags >> 15) & 0xFF; // HMMM?

	if (pPed->frame1 & 1)
	{
		if (pPed->frame1 < 30)
			vert1 += (frame + 1) * 30;

		// interpolate between frames
		for (i = 0; i < 31; i++)
		{
			srLerpData[i].vx = vert1->vx + vert2->vx >> 1;
			srLerpData[i].vy = vert1->vy + vert2->vy >> shift + 1;
			srLerpData[i].vz = vert1->vz + vert2->vz >> 1;

			vert1++;
			vert2++;
		}
	}
	else
	{
		for (i = 0; i < 31; i++)
		{
			srLerpData[i].vx = vert2->vx;
			srLerpData[i].vy = vert2->vy >> shift;
			srLerpData[i].vz = vert2->vz;

			vert2++;
		}
	}

	pos.vx = pPed->position.vx - camera_position.vx;
	pos.vy = pPed->position.vy - camera_position.vy;
	pos.vz = pPed->position.vz - camera_position.vz;

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_ldv0(&pos);
	gte_rtv0();

	gte_stlvnl(&pos1);
	gte_SetTransVector(&pos1);

	// [A] it just happened to be bugged and weird implementation of YXZ rotation
	// replaced with regular RotMatrixYXZ
	rot.vx = pPed->dir.vx & 0xfff;
	rot.vy = pPed->dir.vy & 0xfff;
	rot.vz = pPed->dir.vz & 0xfff;

	RotMatrixYXZ(&rot, &workmatrix);
	
	gte_MulMatrix0(&inv_camera_matrix, &workmatrix, &workmatrix);
	gte_SetRotMatrix(&workmatrix);

	gte_ldv3(&srLerpData[0], &srLerpData[1], &srLerpData[2]);
	gte_rtpt();
	gte_stsz(&gCurrentZ);

	szList[0] = gCurrentZ;

	if (gCurrentZ > switch_detail_distance)
		return;

	// translate bones to screen and draw sprites
	j = 0;
	for (i = 0; i < 15; i++)
	{
		if (j < 30)
		{
			gte_stsxy3(&sxyList[j], &sxyList[j+1], &sxyList[j+2]);
			gte_stsz3(&szList[j], &szList[j+1], &szList[j+2]);
		}

		if (j < 27)
		{
			j += 3;

			gte_ldv3(&srLerpData[j], &srLerpData[j+1], &srLerpData[j+2]);
			gte_rtpt();
		}

		boneId = boneIdvals[i];
		
		if (boneId == HEAD && szList[0] <= switch_detail_distance / 2)
			bHeadModel = 1;
		else
			DrawBodySprite(pPed, boneId, (VERTTYPE*)&sxyList[i*2], (VERTTYPE*)&sxyList[i*2 + 1], szList[i*2], szList[i*2+1]);
	}

	// show head
	if (bHeadModel)
	{
		bAllreadyRotated = 0;
		DoCivHead(pPed, &srLerpData[5], &srLerpData[4]);

		ppos.vx = 0;
		ppos.vy = 0;
		ppos.vz = 0;

		gte_SetTransVector(&ppos);
	}

	// make shadow
	ppos.vx = pPed->position.vx;
	ppos.vy = pPed->position.vy;
	ppos.vz = pPed->position.vz;

	phase = (pPed->frame1 & 15) * 2;

	cv.b = 40;
	cv.g = 40;
	cv.r = 40;

	ppos.vy = (10 - MapHeight(&ppos)) - camera_position.vy;
	ppos.vx = ppos.vx - camera_position.vx;
	ppos.vz = ppos.vz - camera_position.vz;

	if (phase < 8)
		size = phase + 80;
	else
		size = -phase + 112;

	RoundShadow(&ppos, &cv, size);
}

// [D] [T]
void SetSkelModelPointers(int type)
{
	if (type == OTHER_MODEL)
	{
		Skel[JOINT_1].pModel = &pmJerichoModels[0];
		Skel[HEAD].pModel = &pmJerichoModels[1];
		Skel[LELBOW].pModel = &pmJerichoModels[2];
		Skel[LHAND].pModel = &pmJerichoModels[3];
		Skel[RELBOW].pModel = &pmJerichoModels[4];
		Skel[RHAND].pModel = &pmJerichoModels[5];
		Skel[LHIP].pModel = NULL;

		bodyShiftValue = BODY_OFFSET + JERICHO_BODY_OFFSET;
		torsoShiftValue = TORSO_OFFSET + JERICHO_TORSO_OFFSET;
	}
	else
	{
		Skel[JOINT_1].pModel = &pmTannerModels[0];
		Skel[HEAD].pModel = &pmTannerModels[1];
		Skel[LELBOW].pModel = &pmTannerModels[8];
		Skel[LHAND].pModel = &pmTannerModels[9];
		Skel[RELBOW].pModel = &pmTannerModels[2];
		Skel[RHAND].pModel = &pmTannerModels[3];
		Skel[LHIP].pModel = &pmTannerModels[15]; // [A] Tanner looks better with no model here but let's keep it

		bodyShiftValue = BODY_OFFSET;
		torsoShiftValue = TORSO_OFFSET;
	}
}


int iCurrBone = 0;

// [D] [T]
void DrawTanner(LPPEDESTRIAN pPed)
{
	int iVar1;
	VECTOR v;
	CVECTOR cV;

	bDoingShadow = 0;

	SetSkelModelPointers(pPed->pedType);
	SetupTannerSkeleton(pPed);

	newRotateBones(pPed, &Skel[LOWERBACK]);

	// [A] I don't know but it works
	gte_SetRotMatrix(&inv_camera_matrix);

	iCurrBone = 0;
	newShowTanner(pPed);

	v.vx = pPed->position.vx;
	v.vy = -pPed->position.vy;
	v.vz = pPed->position.vz;
	
	v.vy = -camera_position.vy - MapHeight(&v);// - camera_position.vy;

	v.vx = (pPed->position.vx - camera_position.vx) + Skel[ROOT].pvOrigPos->vx;
	v.vz = (pPed->position.vz - camera_position.vz) + Skel[ROOT].pvOrigPos->vz;
	//v.vy = -camera_position.vy - MapHeight((VECTOR*)&pPed->position);

	bDoingShadow = 1;

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

// [D] [T]
int DrawCharacter(LPPEDESTRIAN pPed)
{
	int fr;
	short size;
	int phase;

	CVECTOR cV;
	VECTOR v;
	CVECTOR cv;
	VECTOR pos;

	SetSkelModelPointers(pPed->pedType);
	SetupTannerSkeleton(pPed);

	newRotateBones(pPed, &Skel[LOWERBACK]);

	gte_SetRotMatrix(&inv_camera_matrix);

	iCurrBone = 0;
	newShowTanner(pPed);

	if (pUsedPeds->pNext == NULL && pPed->pedType == TANNER_MODEL)
	{
		v.vx = (pPed->position.vx - camera_position.vx) + Skel[ROOT].pvOrigPos->vx;
		v.vz = (pPed->position.vz - camera_position.vz) + Skel[ROOT].pvOrigPos->vz;

		bDoingShadow = 1;
		v.vy = -camera_position.vy - MapHeight((VECTOR*)&pPed->position);

		if (gTimeOfDay == 3)
		{
			cV.b = cV.g = cV.r = 12;
			TannerShadow(pPed, &v, moon_position + GameLevel, &cV, pPed->dir.vy);
		}
		else
		{
			cV.b = cV.g = cV.r = 32;
			TannerShadow(pPed, &v, sun_position + GameLevel, &cV, pPed->dir.vy);
		}

		bDoingShadow = 0;
	}
	else if (pPed->pedType == CIVILIAN)
	{
		pos.vx = pPed->position.vx;
		pos.vy = pPed->position.vy;
		pos.vz = pPed->position.vz;

		fr = pPed->frame1 & 7;
		phase = fr * 2;

		pos.vy = (30 - MapHeight(&pos)) - camera_position.vy;

		pos.vx -= camera_position.vx;
		pos.vz -= camera_position.vz;

		if (phase < 8)
			size = phase + 80;
		else
			size = -phase + 96;

		cv.b = cv.g = cv.r = 40;
		
		RoundShadow(&pos, &cv, size);
	}

	return 1;
}


POLY_FT4 ft4TannerShadow[2];
TILE tileTannerClear[2];
extern TEXTURE_DETAILS tannerShadow_texture;
RECT16 rectTannerWindow;

// [D] [T]
void InitTannerShadow(void)
{
	u_char brightness;
	TILE* tile;
	POLY_FT4* poly;
	int i;

	if (gTimeOfDay == 3)
		brightness = 12;
	else
		brightness = 32;

	poly = ft4TannerShadow;
	tile = tileTannerClear;
	
	rectTannerWindow.w = 64;
	rectTannerWindow.h = 128;
	rectTannerWindow.x = tpagepos[nperms + 1].x;
	rectTannerWindow.y = tpagepos[nperms + 1].y + 128;

	for (i = 0; i < 2; i++)
	{
		int offs = 0;
		if(GameLevel == 2) // [A] bug fix for vegas
			offs = 18;
		
		poly->u0 = tannerShadow_texture.coords.u1 / 4 - 1;
		poly->v0 = tannerShadow_texture.coords.v1 + offs;
		
		poly->u1 = tannerShadow_texture.coords.u0 / 4 + 1;
		poly->v1 = tannerShadow_texture.coords.v0 + offs;
		
		poly->u2 = tannerShadow_texture.coords.u3 / 4 - 1;
		poly->v2 = tannerShadow_texture.coords.v3 + offs - 18;

		poly->u3 = tannerShadow_texture.coords.u2 / 4 + 1;
		poly->v3 = tannerShadow_texture.coords.v2 + offs - 18;

		poly->tpage = getTPage(2, 0, rectTannerWindow.x, rectTannerWindow.y);

		setPolyFT4(poly);
		setSemiTrans(poly, 1);

		poly->r0 = poly->g0 = poly->b0 = brightness;
		poly++;

		setTile(tile);

		tile->x0 = 0;
		tile->y0 = 0;
		tile->w = 64;
		tile->h = 128;
		tile->r0 = 0;
		tile->g0 = 0;
		tile->b0 = 0;
		tile++;
	}
}

// [D] [T]
void TannerShadow(LPPEDESTRIAN pDrawingPed, VECTOR* pPedPos, SVECTOR* pLightPos, CVECTOR* col, short angle)
{
	DR_ENV* dr_env;
	SVECTOR vert[4];
	VECTOR d;
	DRAWENV drEnv;

	VECTOR cp;
	SVECTOR ca;

	VECTOR myVector;
	int z0, z1, z2, z3;
	int i;
	int cn, sn;
	int vx, vz;

	int Tangle;

#ifndef PSX
	if (gDemoLevel)
		return;
#endif

#ifdef __EMSCRIPTEN__
	// since any WebGL isn't able to make it drawn...
	return;
#endif

	if (NumPlayers > 1)
		return;

	memset((u_char*)&d, 0, sizeof(VECTOR));

	SetDefDrawEnv(&drEnv, 0, current->draw.clip.y, 320, 256);

	dr_env = (DR_ENV*)current->primptr;
	SetDrawEnv(dr_env, &drEnv);

	addPrim(current->ot + OTSIZE - 1, dr_env);
	current->primptr += sizeof(DR_ENV);

	Tangle = ratan2(-pLightPos->vx, pLightPos->vz);

	SetVec(&vert[0], -128, 0, -320);
	SetVec(&vert[1], 128, 0, -320);
	SetVec(&vert[2], -128, 0, 40);
	SetVec(&vert[3], 128, 0, 40);

	for (i = 0; i < 4; i++)
	{
		cn = rcos(Tangle); sn = rsin(Tangle);

		vx = vert[i].vx; vz = vert[i].vz;

		vert[i].vx = FIXED(vx * cn) - FIXED(vz * sn);
		vert[i].vz = FIXED(vx * sn) + FIXED(vz * cn);

		VecAdd(&vert[i], &vert[i], pPedPos);
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

	addPrim(current->ot + (z0 * 2 + z3 * 6 >> 6), &ft4TannerShadow[current->id]);
	//SubdivShadow(z0, z1, z2, z3, ft4TannerShadow + current->id);
	
	{
		// store vectors
		cp = camera_position;
		ca = camera_angle;
		z1 = scr_z;

		// setup new camera
		SetVec(&camera_position,
			pDrawingPed->position.vx + (pLightPos->vx * 90 >> 0xc),
			pDrawingPed->position.vy + (pLightPos->vy * 90 >> 0xc),
			pDrawingPed->position.vz + (pLightPos->vz * 90 >> 0xc));

		SetVec(&myVector, pDrawingPed->position.vx, pDrawingPed->position.vy, pDrawingPed->position.vz);
		PointAtTarget(&camera_position, &myVector, &camera_angle);

		// build matrix
		gte_SetGeomOffset(32, 60);
		SetGeomScreen(scr_z = 200);
		BuildWorldMatrix();

		// clear to black and draw Tanner sprites
		newShowTanner(pDrawingPed);
		addPrim(current->ot + OTSIZE - 1, &tileTannerClear[current->id]);

		// restore vectors
		camera_position = cp;
		camera_angle = ca;
		scr_z = z1;

		// build matix
		gte_SetGeomOffset(160, 128);
		SetGeomScreen(scr_z);
		BuildWorldMatrix();
	}
	
	SetDefDrawEnv(&drEnv, rectTannerWindow.x, rectTannerWindow.y, rectTannerWindow.w, rectTannerWindow.h);
	drEnv.dfe = 0; // we're drawing into VRAM - don't draw on screen
	drEnv.dtd = 0; // [A] no need in dithering

	dr_env = (DR_ENV*)current->primptr;
	SetDrawEnv(dr_env, &drEnv);

	addPrim(current->ot + OTSIZE - 1, dr_env);
	current->primptr += sizeof(DR_ENV);
}

// [A] - totally custom function but it works pretty much same as original
void DoCivHead(LPPEDESTRIAN pPed, SVECTOR* vert1, SVECTOR* vert2)
{
	SVECTOR spos;
	VECTOR pos;
	SVECTOR headpos;
	MATRIX* pHeadRot;
	int oldcombointensity;

	if (gPed1HeadModelPtr == NULL)
		return;

	pHeadRot = (MATRIX*)&matrixtable[((pPed->dir.vy - pPed->head_rot) / 64) & 0x3F];

	if (bAllreadyRotated) // not needed to rotate vert1
	{
		headpos.vx = vert1->vx;
		headpos.vy = vert1->vy;
		headpos.vz = vert1->vz;
	}
	else
	{
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

	int flags = PLOT_NO_SHADE;

	if (pPed->pallet & 0xf)
	{
		flags |= PLOT_CUSTOM_PALETTE; // set custom palette flag
		plotContext.clut = civ_clut[0][texturePedHead.texture_number][pPed->pallet & 0xf] << 0x10;
	}

	oldcombointensity = combointensity;

	if (gNight)
		combointensity = 0x404040;

	RenderModel(gPed1HeadModelPtr, pHeadRot, &pos, 1, flags, 0, 0);

	combointensity = oldcombointensity;
}


