#include "driver2.h"

#include "draw.h"
#include "main.h"
#include "map.h"
#include "models.h"
#include "system.h"
#include "camera.h"
#include "mission.h"
#include "cell.h"
#include "tile.h"
#include "objanim.h"
#include "texture.h"
#include "cars.h"
#include "debris.h"
#include "ASM/rndrasm.h"
#include "event.h"

#ifdef PSX
#pragma GCC optimization ("O3")
#endif

MATRIX aspect =
{
	{
		{ 6553, 0, 0 },
		{ 0, 4096, 0 },
		{ 0, 0, 4096 }
	},
	{ 0, 0, 0 }
};

MATRIX identity =
{
	{
		{ 4096, 0, 0 },
		{ 0, 4096, 0 },
		{ 0, 0, 4096 }
	},
	{ 0, 0, 0 }
};

int PolySizes[56] = {
	8,  12, 16, 24,
	20, 20, 28, 32,
	8,  12, 16, 16,
	0,  0,  0,  0,
	12, 12, 12, 16,
	20, 20, 24, 24,
	0,  0,  0,  0,
	0,  0,  0,  0,
	8,  12, 16, 24,
	20, 24, 28, 32,
	0,  0,  0,  0,
	0,  0,  0,  0,
	12, 12, 12, 16,
	20, 20, 24, 24,
};

SVECTOR day_vectors[4] =
{
  { -3132, 2520, 783, 0 },
  { -3132, 2520, 783, 0 },
  { -2364, 2364, 2364, 0 },
  { -3132, 2520, 783, 0 }
};

SVECTOR night_vectors[4] =
{
  { 3132, 2520, 783, 0 },
  { 3132, 2520, 783, 0 },
  { -2364, 2364, -2364, 0 },
  { 3132, 2520, 783, 0 }
};

SVECTOR day_colours[4] =
{
  { 3200, 3200, 3200, 0 },
  { 3200, 3200, 3200, 0 },
  { 3200, 3200, 3200, 0 },
  { 3200, 3200, 3200, 0 }
};

SVECTOR night_colours[4] =
{
  { 880, 880, 905, 0 },
  { 880, 880, 905, 0 },
  { 880, 880, 905, 0 },
  { 880, 880, 905, 0 }
};

void* model_object_ptrs[MAX_DRAWN_BUILDINGS];
void* model_tile_ptrs[MAX_DRAWN_TILES];
void* anim_obj_buffer[MAX_DRAWN_ANIMATING];
void* spriteList[MAX_DRAWN_SPRITES];

MATRIX inv_camera_matrix;
MATRIX face_camera;
MATRIX2 CompoundMatrix[64];

u_int farClip2Player = 36000;

#ifdef PSX
int goFaster = 1;
#else
int goFaster = 0;	// [A] was 1
#endif
int fasterToggle = 0;

int combointensity;

char CurrentPVS[PVS_CELL_COUNT * PVS_CELL_COUNT + 3]; // 20*20+4
MATRIX2 matrixtable[64];
int setupYet = 0;

int gDrawDistance = PVS_CELL_COUNT * PVS_CELL_COUNT;

#ifndef PSX
_pct& plotContext = *(_pct*)((u_char*)getScratchAddr(0) + 1024 - sizeof(_pct));	// orig offset: 0x1f800020
#endif

struct MVERTEX5x5
{
	MVERTEX verts[5][5];
};

// [D] [T] [A]
void addSubdivSpriteShadow(POLYFT4* src, SVECTOR* verts, int z)
{
	int m;

	m = 4;

#if 0 //def PSX
	MVERTEX5x5& subdiVerts = *(MVERTEX5x5*)(u_char*)getScratchAddr(0);
#else
	MVERTEX5x5 subdiVerts;
#endif

	plotContext.colour = 0x2E000000;
	plotContext.flags = PLOT_INV_CULL;
	plotContext.clut = texture_cluts[src->texture_set][src->texture_id];
	plotContext.tpage = texture_pages[src->texture_set];

	if (z > 3200)
		m = 1; //2;

	plotContext.ot += 28;

	copyVector(&subdiVerts.verts[0][0], &verts[src->v0]);
	subdiVerts.verts[0][0].uv.val = *(ushort*)&src->uv0;

	copyVector(&subdiVerts.verts[0][1], &verts[src->v1]);
	subdiVerts.verts[0][1].uv.val = *(ushort*)&src->uv1;

	copyVector(&subdiVerts.verts[0][2], &verts[src->v3]);
	subdiVerts.verts[0][2].uv.val = *(ushort*)&src->uv3;

	copyVector(&subdiVerts.verts[0][3], &verts[src->v2]);
	subdiVerts.verts[0][3].uv.val = *(ushort*)&src->uv2;

	makeMesh((MVERTEX(*)[5][5])subdiVerts.verts, m, m);
	drawMesh((MVERTEX(*)[5][5])subdiVerts.verts, m, m, &plotContext);

	plotContext.ot -= 28;
}

// [D] [T] [A]
void DrawSprites(PACKED_CELL_OBJECT** sprites, int numFound)
{
	int i;
	int z;
	u_int spriteColour, lightdd;
	u_char lightLevel;
	MODEL* model;
	PACKED_CELL_OBJECT* pco;
	PACKED_CELL_OBJECT** list;
	int numShadows;

#if 0 //def PSX
	MVERTEX5x5& subdiVerts = *(MVERTEX5x5*)(u_char*)getScratchAddr(0);
	MATRIX shadowMatrix = *(MATRIX*)((u_char*)getScratchAddr(0) + sizeof(MVERTEX5x5));
#else
	MVERTEX5x5 subdiVerts;
	MATRIX shadowMatrix;
#endif
	SVECTOR* lightVec;

	lightVec = (gTimeOfDay == TIME_NIGHT) ? night_vectors : day_vectors;

	lightdd =	FIXEDH(camera_matrix.m[2][0] * lightVec[GameLevel].vx) +
				FIXEDH(camera_matrix.m[2][1] * lightVec[GameLevel].vy) +
				FIXEDH(camera_matrix.m[2][2] * lightVec[GameLevel].vz) + ONE * 3072;

	lightLevel = (lightdd >> 18) + 32 & 255;

	if (gWeather > WEATHER_NONE && gTimeOfDay == TIME_DAY || (M_BIT(gTimeOfDay) & (M_BIT(TIME_DAWN) | M_BIT(TIME_DUSK))))
	{
		lightLevel = (lightLevel * 2 * NightAmbient) >> 8;
	}
	if (gTimeOfDay == TIME_NIGHT)
	{
		if (GameLevel == 0)
			lightLevel *= 2;	// [A] level bug - Chicago trees lit wrong
		else
			lightLevel /= 3;
	}

	spriteColour = lightLevel << 0x10 | lightLevel << 8 | lightLevel | 0x2c000000;

	for (i = 0; i < 3; i++) 
	{
		shadowMatrix.m[i][0] = inv_camera_matrix.m[i][2];
		shadowMatrix.m[i][1] = -inv_camera_matrix.m[i][0];
		shadowMatrix.m[i][2] = inv_camera_matrix.m[i][0];
	}

	plotContext.primptr = current->primptr;
	plotContext.ptexture_pages = (ushort(*)[128])texture_pages;
	plotContext.ptexture_cluts = (ushort(*)[128][32])texture_cluts;
	plotContext.polySizes = PolySizes;
	plotContext.ot = current->ot;
	plotContext.colour = spriteColour;
	plotContext.current = current;

	list = sprites;
	numShadows = 0;

	while (numFound--)
	{
		int modelnumber;
		pco = *list;
		list++;

		modelnumber = (pco->value >> 6) | (pco->pos.vy & 1) << 10;
		model = modelpointers[modelnumber];

		if ((pco->value & 63) == 63 || litSprites[modelnumber >> 5] & 1 << (modelnumber & 31))  // [A] multiple sprites lighting fixes
		{
			plotContext.colour = 0x2c808080;
		}
		else
		{
			plotContext.colour = spriteColour;
		}

		plotContext.scribble[0] = pco->pos.vx;
		plotContext.scribble[1] = (pco->pos.vy << 0x10) >> 0x11;
		plotContext.scribble[2] = pco->pos.vz;

		z = Apply_InvCameraMatrixAndSetMatrix((VECTOR_NOPAD*)plotContext.scribble, (MATRIX2*)&face_camera);

		if (z < 1000)
		{
			POLYFT4* src;
			SVECTOR* verts;
			int numPolys;

			numPolys = (u_int)model->num_polys;
			src = GET_MODEL_DATA(POLYFT4, model, poly_block);
			verts = GET_MODEL_DATA(SVECTOR, model, vertices);

			plotContext.flags |= PLOT_NO_CULL;

			while (numPolys--, numPolys >= 0)
			{
				plotContext.clut = texture_cluts[src->texture_set][src->texture_id];
				plotContext.tpage = texture_pages[src->texture_set];

				copyVector(&subdiVerts.verts[0][0], &verts[src->v0]);
				subdiVerts.verts[0][0].uv.val = *(ushort*)&src->uv0;

				copyVector(&subdiVerts.verts[0][1], &verts[src->v1]);
				subdiVerts.verts[0][1].uv.val = *(ushort*)&src->uv1;

				copyVector(&subdiVerts.verts[0][2], &verts[src->v3]);
				subdiVerts.verts[0][2].uv.val = *(ushort*)&src->uv3;

				copyVector(&subdiVerts.verts[0][3], &verts[src->v2]);
				subdiVerts.verts[0][3].uv.val = *(ushort*)&src->uv2;

				makeMesh((MVERTEX(*)[5][5])subdiVerts.verts, 4, 4);
				drawMesh((MVERTEX(*)[5][5])subdiVerts.verts, 4, 4, &plotContext);

				src++;
			}

			plotContext.flags &= ~PLOT_NO_CULL;
		}
		else
		{
			plotContext.ot -= 133;

			Tile1x1(model);

			plotContext.ot += 133;
		}

#ifdef PSX
#define MAX_TREE_SHADOW_DISTANCE 7000
#else
#define MAX_TREE_SHADOW_DISTANCE 14000
#endif
		
		if (wetness == 0 && gTimeOfDay != TIME_NIGHT &&
			(pco->value & 32) == 0 && 
			z < MAX_TREE_SHADOW_DISTANCE &&
			numShadows < 40)
		{
			gte_SetRotMatrix(&shadowMatrix);

			addSubdivSpriteShadow(GET_MODEL_DATA(POLYFT4, model, poly_block), GET_MODEL_DATA(SVECTOR, model, vertices), z);

			if (model->num_polys == 2)
				addSubdivSpriteShadow(GET_MODEL_DATA(POLYFT4, model, poly_block) + 1, GET_MODEL_DATA(SVECTOR, model, vertices), z);

			gte_SetRotMatrix(&face_camera);

			numShadows++;
		}
	}
	current->primptr = plotContext.primptr;
}

// [D] [T]
void SetupPlaneColours(u_int ambient)
{
	u_int r, g, b;

	if (gWeather == 0 && (M_BIT(gTimeOfDay) & (M_BIT(TIME_DAWN) | M_BIT(TIME_DUSK))) == 0)
	{
		if (gTimeOfDay == TIME_DAY)
		{
			b = ambient & 255;
			g = ambient >> 8 & 255;
			r = ambient >> 16 & 255;
			
			plotContext.planeColours[1] = (r * 120 >> 7) << 16 | (g * 120 >> 7) << 8 | b * 120 >> 7;
			plotContext.planeColours[2] = (r * 103 >> 7) << 16 | (g * 103 >> 7) << 8 | b * 103 >> 7;
			plotContext.planeColours[3] = (r * 13 >> 5) << 16 | (g * 13 >> 5) << 8 | b * 13 >> 5;
			plotContext.planeColours[0] = r << 16 | g << 8 | b;
			plotContext.planeColours[4] = (r * 3 >> 3) << 16 | (g * 3 >> 3) << 8 | b * 3 >> 3;
			plotContext.planeColours[5] = plotContext.planeColours[3];
			plotContext.planeColours[6] = plotContext.planeColours[2];
			plotContext.planeColours[7] = plotContext.planeColours[1];
			return;
		}

		plotContext.planeColours[0] = ambient;
		plotContext.planeColours[1] = ambient;
		plotContext.planeColours[2] = ambient;
		plotContext.planeColours[3] = ambient;
		plotContext.planeColours[4] = ambient;
		plotContext.planeColours[5] = ambient;
		plotContext.planeColours[6] = ambient;
		plotContext.planeColours[7] = ambient;
		return;
	}

	plotContext.planeColours[0] = ambient;
	plotContext.planeColours[1] = ambient + 0x10101;
	plotContext.planeColours[2] = ambient + 0x30303;
	plotContext.planeColours[3] = ambient + 0x80808;
	plotContext.planeColours[4] = ambient + 0xa0a0a;
	plotContext.planeColours[5] = ambient + 0x80808;
	plotContext.planeColours[6] = ambient + 0x30303;
	plotContext.planeColours[7] = ambient + 0x10101;
}


int current_pvs_cell;


// [D] [T]
void SetupDrawMapPSX(void)
{
	int cell_x, cell_z;
	int theta;
	int pvs_cell;

	if (setupYet != 0)
	{
		return;
	}

	cell_x = (camera_position.vx + units_across_halved) / MAP_CELL_SIZE;
	cell_z = (camera_position.vz + units_down_halved) / MAP_CELL_SIZE;

	current_cell_x = cell_x;
	current_cell_z = cell_z;

	pvs_cell = (cell_z % MAP_REGION_SIZE) * MAP_REGION_SIZE + (cell_x % MAP_REGION_SIZE);
	if (pvs_cell != current_pvs_cell)
	{
		int region_x1, region_z1;
		int current_barrel_region_x1, current_barrel_region_z1;

		region_x1 = cell_x / MAP_REGION_SIZE;
		region_z1 = cell_z / MAP_REGION_SIZE;

		current_barrel_region_x1 = (region_x1 & 1);
		current_barrel_region_z1 = (region_z1 & 1);

		current_pvs_cell = pvs_cell;
		GetPVSRegionCell2(
			current_barrel_region_x1 + current_barrel_region_z1 * 2,
			region_x1 + region_z1 * regions_across,
			pvs_cell, CurrentPVS);
	}

	InitFrustrumMatrix();
	SetFrustrumMatrix();

	setupYet = 1;
}

MATRIX frustrum_matrix;

// [D] [T]
void InitFrustrumMatrix(void)
{
	int a, t;

	a = -camera_angle.vy;

	frustrum_matrix.m[0][1] = 0;
	frustrum_matrix.m[0][0] = RSIN(a);
	frustrum_matrix.m[0][2] = RCOS(a);

	a = (FrAng - 1024) - camera_angle.vy;

	frustrum_matrix.m[1][1] = 0;
	frustrum_matrix.m[1][0] = RSIN(a);
	frustrum_matrix.m[1][2] = RCOS(a);

	a = -(FrAng - 1024) - camera_angle.vy;

	frustrum_matrix.m[2][1] = 0;
	frustrum_matrix.m[2][0] = RSIN(a);
	frustrum_matrix.m[2][2] = RCOS(a);
}

// [D] [T]
void SetFrustrumMatrix(void)
{
	gte_SetLightMatrix(&frustrum_matrix);
}

// [D] [T]
void Set_Inv_CameraMatrix(void)
{
	gte_SetColorMatrix(&inv_camera_matrix);
}


// [D] [T] [A]
void CalcObjectRotationMatrices(void)
{
	int i;
	int angle;
	MATRIX* m;

	angle = 0;

	for (i = 0; i < 64; i++)
	{
		// simpler and faster method
		m = (MATRIX*)&matrixtable[i];

		InitMatrix(*m);
		RotMatrixY(angle, m);

		angle += 64;
	}
}

// [D] [T]
void PlotMDL_less_than_128(MODEL* model)
{
	RenderModel(model, NULL, NULL, 0, 0, 0, 0);
}

// [D] [T]
int PositionVisible(VECTOR* pos)
{
	return newPositionVisible(pos, CurrentPVS, current_cell_x, current_cell_z);
}

int gForceLowDetailCars = 0;
int num_cars_drawn = 0;

// [D] [T]
void DrawAllTheCars(int view)
{
	static int car_distance[MAX_CARS]; // offset 0x0
	CAR_DATA* cars_to_draw[MAX_CARS];

	int dx, dz;
	int dist;
	int i, j;
	CAR_DATA* cp;
	int num_cars_to_draw;
	int spacefree;
	

	num_cars_drawn = 0;
	num_cars_to_draw = 0;

	cp = &car_data[MAX_CARS - 1];
	do {
		if (cp->controlType != CONTROL_TYPE_NONE && 
			PositionVisible((VECTOR*)cp->hd.where.t))
		{
			// XZ distance estimation
			dx = ABS(camera_position.vx - cp->hd.where.t[0]);
			dz = ABS(camera_position.vz - cp->hd.where.t[2]);

			if (dx < dz)
				dist = dz + dx / 2;
			else
				dist = dx + dz / 2;

			if (dist < VIEW_DRAW_DISTANCE)
			{
				car_distance[num_cars_to_draw] = dx + dz;
				cars_to_draw[num_cars_to_draw] = cp;
				num_cars_to_draw++;
			}
		}

		cp--;
	} while (cp >= car_data);

	if (num_cars_to_draw != 0)
	{
		gForceLowDetailCars = 0;

		// insertion sort of cars by distance
		for (i = 1; i < num_cars_to_draw; i++)
		{
			cp = cars_to_draw[i];
			dist = car_distance[i];

			j = i - 1;

			while (j >= 0 && dist < car_distance[j])
			{
				car_distance[i] = car_distance[j];
				cars_to_draw[i] = cars_to_draw[j];
				j--;
			}
			
			cars_to_draw[j+1] = cp;
			car_distance[j+1] = dist;
		}

		spacefree = (num_cars_to_draw - 1) * 2000;

		for (i = 0; i < num_cars_to_draw; i++)
		{
			// Don't exceed draw buffers
			if ((int)(current->primtab + (-3000 - (int)(current->primptr - PRIMTAB_SIZE))) < 5800)
				return;

			// make cars look uglier
			if ((int)(current->primtab + (-3000 - (int)(current->primptr - PRIMTAB_SIZE)) - spacefree) < 5800)
				gForceLowDetailCars = 1;

			if (cars_to_draw[i]->controlType == CONTROL_TYPE_PLAYER)
				gForceLowDetailCars = 0;

			DrawCar(cars_to_draw[i], view);
			
			spacefree -= 2000;
		}
	}
}


// [D] [T]
u_int normalIndex(SVECTOR* verts, u_int vidx)
{
	SVECTOR* v0, *v1, *v2;
	int x, y;
	int th23;

	int nx, ny, nz;

	SVECTOR p, q;

	v0 = verts + (vidx & 255);
	v1 = verts + (vidx >> 8 & 255);
	v2 = verts + (vidx >> 16 & 255);

	p.vz = v1->vz - v0->vz;
	q.vz = v2->vz - v0->vz;

	p.vy = v1->vy - v0->vy;
	q.vy = v2->vy - v0->vy;

	p.vx = v1->vx - v0->vx;
	q.vx = v2->vx - v0->vx;

	nx = p.vy * q.vz - p.vz * q.vy;
	nz = p.vx * q.vy - p.vy * q.vx;

	x = nx + (nz >> 3);
	y = nz - (x >> 2);

	x += (y >> 3);

	if (x < y)
	{
		if (x + y < 1)
			th23 = y < 0 ? 5 : 4;
		else
			th23 = x < 0 ? 3 : 2;
	}
	else
	{
		if (x + y < 1)
			th23 = x < 0 ? 6 : 7;
		else
			th23 = y > 0 ? 1 : 0;
	}

	th23 *= 4;

	ny = p.vz * q.vx - p.vx * q.vz;

	nx = ABS(nx);
	nz = ABS(nz);

	if (nx + nz < ny)
		th23 += 1;

	if (nx + nz < -ny)
		th23 = th23 & 31 | 2;
	else
		th23 = th23 & 31;

	return th23 | 0x80;
}

// [A]
void ConvertPolygonTypes(MODEL* model, _pct* pc)
{
	SVECTOR* srcVerts;
	PL_POLYFT4* polys;
	u_char temp, ptype;
	int i;

	// [A] we are storing the processing flag here
	if (model->tri_verts & 0x80)
	{
		return;
	}
	
	model->tri_verts |= 0x80;

	srcVerts = GET_MODEL_DATA(SVECTOR, model, vertices);
	polys = GET_MODEL_DATA(PL_POLYFT4, model, poly_block);
	i = model->num_polys;

	// pre-process vertices
	while (i-- > 0)
	{
		ptype = polys->id & 31;

		// convert poly types
		if ((ptype & 1) == 0 && ptype != 8) // is FT3 triangle?
		{
			temp = polys->uv2.v;
			polys->uv3.u = polys->uv2.u;
			polys->uv3.v = temp;

			polys->v3 = polys->v2;

			polys->id |= 1;
			ptype |= 1;
		}

		if (ptype != 11 && ptype != 21 && ptype != 23)
		{
			polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
			continue;
		}

		// also precalculate normal index
		if (ptype != 21 && (polys->th & 0x80) == 0)
		{
			polys->th = normalIndex(srcVerts, *(u_int*)&polys->v0);
		}
		polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
	}
}

void PlotBuildingModel(MODEL* model, int rot, _pct* pc)
{
	int opz, Z, r;
	PL_POLYFT4* polys;
	int i;
	u_char ptype;
	POLY_FT4* prims;
	SVECTOR* srcVerts;
	int combo;

	srcVerts = GET_MODEL_DATA(SVECTOR, model, vertices);
	polys = GET_MODEL_DATA(PL_POLYFT4, model, poly_block);

	combo = combointensity;

	ConvertPolygonTypes(model, pc);

	r = (rot >> 3) * 4;

	i = model->num_polys;
	while (i-- > 0)
	{
		ptype = polys->id & 31;

		// skip certain polygons
		if (ptype != 11 && ptype != 21 && ptype != 23)
		{
			polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
			continue;
		}

		// perform transform
		gte_ldv3(&srcVerts[polys->v0], &srcVerts[polys->v1], &srcVerts[polys->v3]);
		gte_rtpt();

		// get culling value
		gte_nclip();
		gte_stopz(&opz);

		if (ptype == 21)
		{
			pc->colour = combo & 0x2ffffff | 0x2c000000;
		}
		else
		{
			pc->colour = pc->f4colourTable[r - polys->th & 31];
		}

		if (opz > 0)
		{
			pc->tpage = (*pc->ptexture_pages)[polys->texture_set];
			pc->clut = (*pc->ptexture_cluts)[polys->texture_set][polys->texture_id];

			prims = (POLY_FT4*)pc->primptr;

			setPolyFT4(prims);
			*(u_int*)&prims->r0 = pc->colour;

			// retrieve first three verts
			gte_stsxy3(&prims->x0, &prims->x1, &prims->x2);

			// translate 4th vert and get OT Z value
			gte_ldv0(&srcVerts[polys->v2]);
			gte_rtps();
			gte_avsz4();

			gte_stotz(&Z);

			gte_stsxy(&prims->x3);

			prims->tpage = pc->tpage;
			prims->clut = pc->clut;

			*(ushort*)&prims->u0 = *(ushort*)&polys->uv0;
			*(ushort*)&prims->u1 = *(ushort*)&polys->uv1;
			*(ushort*)&prims->u2 = *(ushort*)&polys->uv3;
			*(ushort*)&prims->u3 = *(ushort*)&polys->uv2;

			addPrim(pc->ot + (Z >> 1), prims);

			pc->primptr += sizeof(POLY_FT4);
		}

		polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
	}
}

// [D] [T] [A] custom
void PlotBuildingModelSubdivNxN(MODEL* model, int rot, _pct* pc, int n)
{
	int opz, Z, r;
	int diff, minZ, maxZ;
	PL_POLYFT4* polys;
	int i;
	u_char ptype;
	POLY_FT4* prims;
	SVECTOR* srcVerts;
	int combo;

#if 0//def PSX
	MVERTEX5x5& subdiVerts = *(MVERTEX5x5*)(u_char*)getScratchAddr(0);
#else
	MVERTEX5x5 subdiVerts;
#endif

	srcVerts = GET_MODEL_DATA(SVECTOR, model, vertices);
	polys = GET_MODEL_DATA(PL_POLYFT4, model, poly_block);

	combo = combointensity;

	ConvertPolygonTypes(model, pc);

	r = (rot >> 3) * 4;

	i = model->num_polys;
	while (i-- > 0)
	{
		// iterate through polygons
		// with skipping
		ptype = polys->id & 31;

		if (ptype != 11 && ptype != 21 && ptype != 23)
		{
			polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
			continue;
		}

		// perform transform
		gte_ldv3(&srcVerts[polys->v0], &srcVerts[polys->v1], &srcVerts[polys->v3]);
		gte_rtpt();

		// get culling value
		gte_nclip();
		gte_stopz(&opz);

		if (ptype == 21)
		{
			pc->colour = combo & 0x2ffffffU | 0x2c000000;
		}
		else
		{
			pc->colour = pc->f4colourTable[r - polys->th & 31];
		}

		if (opz > 0)
		{
			gte_stsz3(&pc->scribble[0], &pc->scribble[1], &pc->scribble[2]);

			pc->tpage = (*pc->ptexture_pages)[polys->texture_set];
			pc->clut = (*pc->ptexture_cluts)[polys->texture_set][polys->texture_id];

			minZ = pc->scribble[2];
			if (pc->scribble[1] < minZ)
				minZ = pc->scribble[1];

			if (pc->scribble[0] < minZ)
				minZ = pc->scribble[0];

			maxZ = pc->scribble[2];
			if (maxZ < pc->scribble[1])
				maxZ = pc->scribble[1];

			diff = maxZ - minZ;
			if (maxZ < pc->scribble[0])
				diff = pc->scribble[0] - minZ;

			ushort uv0, uv1, uv2, uv3;

			// [A] special case
			if(ptype == 23)
			{
				POLYGT4* pgt4 = (POLYGT4*)polys;
				uv0 = *(ushort*)&pgt4->uv0;
				uv1 = *(ushort*)&pgt4->uv1;
				uv2 = *(ushort*)&pgt4->uv2;
				uv3 = *(ushort*)&pgt4->uv3;
			}
			else
			{
				uv0 = *(ushort*)&polys->uv0;
				uv1 = *(ushort*)&polys->uv1;
				uv2 = *(ushort*)&polys->uv2;
				uv3 = *(ushort*)&polys->uv3;
			}

			if (n == 0 || diff << 2 <= minZ - 350)
			{
				prims = (POLY_FT4*)pc->primptr;

				setPolyFT4(prims);
				*(u_int*)&prims->r0 = pc->colour;

				// retrieve first three verts
				gte_stsxy3(&prims->x0, &prims->x1, &prims->x2);

				// translate 4th vert and get OT Z value
				gte_ldv0(&srcVerts[polys->v2]);
				gte_rtps();
				gte_avsz4();

				gte_stotz(&Z);

				gte_stsxy(&prims->x3);

				prims->tpage = pc->tpage;
				prims->clut = pc->clut;

				*(ushort*)&prims->u0 = uv0;
				*(ushort*)&prims->u1 = uv1;
				*(ushort*)&prims->u2 = uv3;
				*(ushort*)&prims->u3 = uv2;

				addPrim(pc->ot + (Z >> 1), prims);

				pc->primptr += sizeof(POLY_FT4);
			}
			else
			{
				int sub;
				sub = n;
				if (n == 1)
				{
					if (minZ - 150 < (diff << 1))
						sub = 4;
					else
						sub = 2;
				}

				copyVector(&subdiVerts.verts[0][0], &srcVerts[polys->v0]);
				subdiVerts.verts[0][0].uv.val = uv0;

				copyVector(&subdiVerts.verts[0][1], &srcVerts[polys->v1]);
				subdiVerts.verts[0][1].uv.val = uv1;

				copyVector(&subdiVerts.verts[0][2], &srcVerts[polys->v3]);
				subdiVerts.verts[0][2].uv.val = uv3;

				copyVector(&subdiVerts.verts[0][3], &srcVerts[polys->v2]);
				subdiVerts.verts[0][3].uv.val = uv2;

				makeMesh((MVERTEX(*)[5][5])subdiVerts.verts, sub, sub);
				drawMesh((MVERTEX(*)[5][5])subdiVerts.verts, sub, sub, pc);
			}
		}

		polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
	}
}


// [D] [T]
int DrawAllBuildings(CELL_OBJECT** objects, int num_buildings)
{
	int i, mat, prev_mat;
	int Z, zbias;
	int drawlimit;
	MODEL* model;
	OTTYPE* ot;
	CELL_OBJECT* cop;

	prev_mat = -1;
	
	for (i = 0; i < 8; i++)
	{
		plotContext.f4colourTable[i * 4 + 0] = plotContext.planeColours[i] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 1] = plotContext.planeColours[0] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 2] = plotContext.planeColours[5] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 3] = plotContext.planeColours[0] | 0x2C000000; // default: 0x2C00F0F0
	}

	plotContext.current = current;
	plotContext.ptexture_pages = &texture_pages;
	plotContext.ptexture_cluts = &texture_cluts;
	plotContext.polySizes = PolySizes;
	plotContext.flags = 0;
	plotContext.primptr = plotContext.current->primptr;

	ot = plotContext.current->ot + 8;

	while (num_buildings--)
	{
		cop = (CELL_OBJECT*)*objects;
		mat = cop->yang;

		if (prev_mat == mat)
		{
			Z = Apply_InvCameraMatrixSetTrans(&cop->pos);
		}
		else
		{
			Z = Apply_InvCameraMatrixAndSetMatrix(&cop->pos, &CompoundMatrix[prev_mat = mat]);
		}

		model = Z > DRAW_LOD_DIST_LOW ? pLodModels[cop->type] : modelpointers[cop->type];

		zbias = model->zBias - 64;

		if (zbias < 0)
			zbias = 0;

		plotContext.ot = ot + zbias * 4;

		if(Z <= DRAW_LOD_DIST_HIGH)
			PlotBuildingModelSubdivNxN(model, cop->yang, &plotContext, 1);
		else
			PlotBuildingModel(model, cop->yang, &plotContext);

		drawlimit = (int)(current->primptr - current->primtab);

		if (PRIMTAB_SIZE - drawlimit < 60000)
			break;
		objects++;
	}

	// advance primitive buffer
	current->primptr = plotContext.primptr;

	return 0;
}


// [D] [T] [A] custom
void PlotModelSubdivNxN(MODEL* model, int rot, _pct* pc, int n)
{
	int opz, Z, r, pr, nr;
	int diff, minZ, maxZ;
	PL_POLYFT4* polys;
	int i;
	u_char ptype;
	POLY_FT4* prims;
	SVECTOR* srcVerts;
	int combo;

#if 0//def PSX
	MVERTEX5x5& subdiVerts = *(MVERTEX5x5*)(u_char*)getScratchAddr(0);
#else
	MVERTEX5x5 subdiVerts;
#endif

	ConvertPolygonTypes(model, pc);

	srcVerts = GET_MODEL_DATA(SVECTOR, model, vertices);
	polys = GET_MODEL_DATA(PL_POLYFT4, model, poly_block);

	combo = combointensity;

	pr = (rot >> 3) * 4;
	nr = ((rot + 32 & 63) >> 3) * 4;

	// transparent object flag
	if (pc->flags & PLOT_TRANSPARENT)
		combo |= 0x2000000;

	i = model->num_polys;
	while (i > 0)
	{
		// iterate through polygons
		// with skipping
		ptype = polys->id & 31;

		if (ptype != 11 && ptype != 21 && ptype != 23)
		{
			polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
			i--;
			continue;
		}

		// perform transform
		gte_ldv3(&srcVerts[polys->v0], &srcVerts[polys->v1], &srcVerts[polys->v3]);
		gte_rtpt();

		// get culling value
		gte_nclip();
		gte_stopz(&opz);

		r = pr;

		if (pc->flags & (PLOT_INV_CULL | PLOT_NO_CULL))
		{
			if (opz < 0)
				r = nr;

			if (pc->flags & PLOT_NO_CULL)
				opz = 1;		// no culling
			else // PLOT_FRONT_CULL
				opz = -opz;		// front face
		}

		if (ptype == 21 || (pc->flags & PLOT_NO_SHADE))
		{
			pc->colour = combo & 0x2ffffffU | 0x2c000000;
		}
		else
		{
			pc->colour = pc->f4colourTable[r - polys->th & 31];
		}

		if (opz > 0)
		{
			gte_stsz3(&pc->scribble[0], &pc->scribble[1], &pc->scribble[2]);

			pc->tpage = (*pc->ptexture_pages)[polys->texture_set];

			if ((pc->flags & PLOT_CUSTOM_PALETTE) == 0) // [A] custom palette flag - for pedestrian heads
				pc->clut = (*pc->ptexture_cluts)[polys->texture_set][polys->texture_id];

			minZ = pc->scribble[2];
			if (pc->scribble[1] < minZ)
				minZ = pc->scribble[1];

			if (pc->scribble[0] < minZ)
				minZ = pc->scribble[0];

			maxZ = pc->scribble[2];
			if (maxZ < pc->scribble[1])
				maxZ = pc->scribble[1];

			diff = maxZ - minZ;
			if (maxZ < pc->scribble[0])
				diff = pc->scribble[0] - minZ;

			ushort uv0, uv1, uv2, uv3;

			// [A] special case
			if (ptype == 23)
			{
				POLYGT4* pgt4 = (POLYGT4*)polys;
				uv0 = *(ushort*)&pgt4->uv0;
				uv1 = *(ushort*)&pgt4->uv1;
				uv2 = *(ushort*)&pgt4->uv2;
				uv3 = *(ushort*)&pgt4->uv3;
			}
			else
			{
				uv0 = *(ushort*)&polys->uv0;
				uv1 = *(ushort*)&polys->uv1;
				uv2 = *(ushort*)&polys->uv2;
				uv3 = *(ushort*)&polys->uv3;
			}

			if (n == 0 || diff << 2 <= minZ - 350)
			{
				prims = (POLY_FT4*)pc->primptr;

				setPolyFT4(prims);
				*(u_int*)&prims->r0 = pc->colour;

				// retrieve first three verts
				gte_stsxy3(&prims->x0, &prims->x1, &prims->x2);

				// translate 4th vert and get OT Z value
				gte_ldv0(&srcVerts[polys->v2]);
				gte_rtps();
				gte_avsz4();

				gte_stotz(&Z);

				gte_stsxy(&prims->x3);

				prims->tpage = pc->tpage;
				prims->clut = pc->clut;

				*(ushort*)&prims->u0 = uv0;
				*(ushort*)&prims->u1 = uv1;
				*(ushort*)&prims->u2 = uv3;
				*(ushort*)&prims->u3 = uv2;

				addPrim(pc->ot + (Z >> 1), prims);

				pc->primptr += sizeof(POLY_FT4);
			}
			else
			{
				r = n;
				if (n == 1)
				{
					if (minZ - 150 < (diff << 1))
						r = 4;
					else
						r = 2;
				}

				copyVector(&subdiVerts.verts[0][0], &srcVerts[polys->v0]);
				subdiVerts.verts[0][0].uv.val = uv0;

				copyVector(&subdiVerts.verts[0][1], &srcVerts[polys->v1]);
				subdiVerts.verts[0][1].uv.val = uv1;

				copyVector(&subdiVerts.verts[0][2], &srcVerts[polys->v3]);
				subdiVerts.verts[0][2].uv.val = uv3;

				copyVector(&subdiVerts.verts[0][3], &srcVerts[polys->v2]);
				subdiVerts.verts[0][3].uv.val = uv2;

				makeMesh((MVERTEX(*)[5][5])subdiVerts.verts, r, r);
				drawMesh((MVERTEX(*)[5][5])subdiVerts.verts, r, r, pc);
			}
		}

		polys = (PL_POLYFT4*)((char*)polys + pc->polySizes[ptype]);
		i--;
	}
}


// [D] [T]
void RenderModel(MODEL* model, MATRIX* matrix, VECTOR* pos, int zBias, int flags, int subdiv, int nrot)
{
	int i;

	if (matrix != NULL)
	{
		MATRIX comb;
		gte_SetTransVector(pos);

		MulMatrix0(&inv_camera_matrix, matrix, &comb);
		SetRotMatrix(&comb);
	}

	zBias /= 8;
	zBias += (model->zBias - 64);

	plotContext.ot = current->ot;

	if (zBias > 0)
		plotContext.ot += (zBias * 4);

	for (i = 0; i < 8; i++)
	{
		plotContext.f4colourTable[i * 4 + 0] = plotContext.planeColours[i] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 1] = plotContext.planeColours[0] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 2] = plotContext.planeColours[5] | 0x2C000000;
		plotContext.f4colourTable[i * 4 + 3] = plotContext.planeColours[0] | 0x2C000000; // default: 0x2C00F0F0
	}

	plotContext.ptexture_pages = &texture_pages;
	plotContext.ptexture_cluts = &texture_cluts;
	plotContext.polySizes = PolySizes;
	plotContext.flags = flags;
	plotContext.current = current;
	
	plotContext.primptr = plotContext.current->primptr;

	if ((current->primtab - (current->primptr - PRIMTAB_SIZE)) > 56000)
	{
		PlotModelSubdivNxN(model, nrot, &plotContext, subdiv);
	}

	// advance primitive buffer
	current->primptr = plotContext.primptr;
}

struct DrawMapData
{
	int rightPlane;
	int leftPlane;
	int backPlane;

	int farClipLimit;

	int current_object_computed_value;
	int cellLevel;

	int cellxpos, cellzpos;

	short backAng;
	short leftAng;
	short rightAng;

	short rightcos;
	short rightsin;
	short leftcos;
	short leftsin;
	short backcos;
	short backsin;

	u_short tiles_found;
	u_short other_models_found;
	u_short sprites_found;
	u_short anim_objs_found;
};

// [D] [T]
void DrawMapPSX(int* comp_val)
{
	CELL_OBJECT* cop;
	PACKED_CELL_OBJECT* ppco;
	MODEL* model;
	int dir;
	int distScale;
	int cellx, cellz;
	int hloop, vloop;

#ifdef PSX
	CELL_ITERATOR& ci = *(CELL_ITERATOR*)(u_char*)getScratchAddr(0);
	MATRIX& mRotStore = *(MATRIX*)((u_char*)getScratchAddr(0) + sizeof(CELL_ITERATOR));
	DrawMapData& drawData = *(DrawMapData*)((u_char*)getScratchAddr(0) + sizeof(CELL_ITERATOR) + sizeof(MATRIX));
	static_assert(sizeof(CELL_ITERATOR) + sizeof(MATRIX) + sizeof(DrawMapData) < 1024 - sizeof(_pct), "scratchpad overflow");
#else
	CELL_ITERATOR ci;
	MATRIX mRotStore;
	DrawMapData drawData;
#endif

	char* PVS_ptr;
	int i;

	static int treecount = 0;
	static int alleycount = 0;

	SetupDrawMapPSX();

	// clean cell cache
	ClearCopUsage();

	drawData.cellLevel = events.camera ? events.draw : -1;

	drawData.backPlane = 6144;
	drawData.rightPlane = -6144;
	drawData.leftPlane = 6144;

	// setup planes
	drawData.rightAng = camera_angle.vy - FrAng;
	drawData.leftAng = camera_angle.vy + FrAng;
	drawData.backAng = camera_angle.vy + 1024;

	drawData.rightcos = RCOS(drawData.rightAng);
	drawData.rightsin = RSIN(drawData.rightAng);

	drawData.leftcos = RCOS(drawData.leftAng);
	drawData.leftsin = RSIN(drawData.leftAng);

	drawData.backcos = RCOS(drawData.backAng);
	drawData.backsin = RSIN(drawData.backAng);

#ifdef PSX
	if (NumPlayers == 2)
		drawData.farClipLimit = farClip2Player;
	else
		drawData.farClipLimit = 60000;
#else
	drawData.farClipLimit = 125000;
#endif

	drawData.tiles_found = 0;
	drawData.sprites_found = 0;
	drawData.current_object_computed_value = (*comp_val & 4095) | drawData.cellLevel << 16;
	drawData.other_models_found = 0;
	drawData.anim_objs_found = 0;
	
	drawData.cellzpos = current_cell_z;
	drawData.cellxpos = current_cell_x;

	PVS_ptr = CurrentPVS + 220;

	vloop = 0;
	hloop = 0;
	dir = 0;

	goFaster ^= fasterToggle;

	if (NumPlayers == 2)
		distScale = goFaster & 31 | 1;
	else
		distScale = goFaster & 31;

	i = (gDrawDistance >> distScale);		// [A]

	// walk through all cells
	do
	{
		if (ABS(hloop) + ABS(vloop) < PVS_CELL_COUNT)
		{
			// clamped vis values
			int vis_h = MIN(MAX(hloop, -9), PVS_CELL_COUNT / 2);
			int vis_v = MIN(MAX(vloop, -9), PVS_CELL_COUNT / 2);

			cellx = drawData.cellxpos + hloop;
			cellz = drawData.cellzpos + vloop;

			if (drawData.rightPlane < 0 &&
				drawData.leftPlane > 0 &&
				drawData.backPlane < drawData.farClipLimit &&  // check planes
				cellx > -1 && cellx < cells_across &&							// check cell ranges
				cellz > -1 && cellz < cells_down &&
				PVS_ptr[vis_v * pvs_square + vis_h]) // check PVS table
			{
				// walk each cell object in cell
				for (ppco = GetFirstPackedCop(cellx, cellz, &ci, 1, drawData.cellLevel); ppco; ppco = GetNextPackedCop(&ci))
				{
					model = modelpointers[(ppco->value >> 6) | ((ppco->pos).vy & 1) << 10];

					if (FrustrumCheck16(ppco, model->bounding_sphere) != -1)
					{
						// sprity type
						if (model->shape_flags & SHAPE_FLAG_SPRITE)
						{
							if (drawData.sprites_found < MAX_DRAWN_SPRITES)
								spriteList[drawData.sprites_found++] = ppco;

							if ((model->flags2 & MODEL_FLAG_ANIMOBJ) && drawData.anim_objs_found < MAX_DRAWN_ANIMATING)
							{
								cop = UnpackCellObject(ppco, &ci.nearCell);
								anim_obj_buffer[drawData.anim_objs_found++] = cop;
							}

							if (model->flags2 & MODEL_FLAG_TREE)
							{
								if (treecount == 0)
								{
									QuickUnpackCellObject(ppco, &ci.nearCell, &ground_debris[groundDebrisIndex]);

									if (groundDebrisIndex < MAX_GROUND_DEBRIS - 1)
										groundDebrisIndex++;
									else
										groundDebrisIndex = 0;
								}

								if (treecount < 15)
									treecount++;
								else
									treecount = 0;
							}
						}
						else
						{
							int yang;
							MATRIX2* cmat;

							yang = ppco->value & 63;
							cmat = &CompoundMatrix[yang];

							if (cmat->computed != drawData.current_object_computed_value)
							{
								cmat->computed = drawData.current_object_computed_value;
								if (yang > 0)
									MulMatrix0(&inv_camera_matrix, (MATRIX*)&matrixtable[yang], (MATRIX*)cmat);
								else
									*(MATRIX*)cmat = inv_camera_matrix;
							}

							if ((model->shape_flags & (SHAPE_FLAG_WATER | SHAPE_FLAG_TILE)) || 
								(model->flags2 & (MODEL_FLAG_PATH | MODEL_FLAG_GRASS)))
							{
								if (model->flags2 & MODEL_FLAG_ALLEY)
								{
									alleycount++;

									if (alleycount == 13)
									{
										QuickUnpackCellObject(ppco, &ci.nearCell, &ground_debris[groundDebrisIndex]);

										if (groundDebrisIndex < MAX_GROUND_DEBRIS - 1)
											groundDebrisIndex++;
										else
											groundDebrisIndex = 0;

										alleycount = 0;
									}
								}

								if (drawData.tiles_found < MAX_DRAWN_TILES)
									model_tile_ptrs[drawData.tiles_found++] = ppco;
							}
							else
							{
								cop = UnpackCellObject(ppco, &ci.nearCell);

								if (drawData.other_models_found < MAX_DRAWN_BUILDINGS)
									model_object_ptrs[drawData.other_models_found++] = cop;

								if (drawData.anim_objs_found < MAX_DRAWN_ANIMATING && (model->flags2 & MODEL_FLAG_ANIMOBJ))
									anim_obj_buffer[drawData.anim_objs_found++] = cop;
							}
						}
					}
				}
			}
		}

		if (dir == 0)
		{
			drawData.leftPlane += drawData.leftcos;
			drawData.backPlane += drawData.backcos;
			drawData.rightPlane += drawData.rightcos;
			dir = (++hloop + vloop == 1) ? 1 : dir;
		}
		else if (dir == 1)
		{
			drawData.leftPlane += drawData.leftsin;
			drawData.backPlane += drawData.backsin;
			drawData.rightPlane += drawData.rightsin;
			//PVS_ptr += pvs_square;
			dir = (hloop == ++vloop) ? 2 : dir;
		}
		else if (dir == 2)
		{
			drawData.leftPlane -= drawData.leftcos;
			drawData.backPlane -= drawData.backcos;
			drawData.rightPlane -= drawData.rightcos;
			dir = (--hloop + vloop == 0) ? 3 : dir;
		}
		else
		{
			drawData.leftPlane -= drawData.leftsin;
			drawData.backPlane -= drawData.backsin;
			drawData.rightPlane -= drawData.rightsin;
			//PVS_ptr -= pvs_square;
			dir = (hloop == --vloop) ? 0 : dir;
		}
	}while (i-- > 0);

#if 0
	char tempBuf[512];

	SetTextColour(255, 255, 0);

	sprintf(tempBuf, "Buildings: %d", drawData.other_models_found);
	PrintString(tempBuf, 10, 60);

	sprintf(tempBuf, "Sprites: %d", drawData.sprites_found);
	PrintString(tempBuf, 10, 75);

	sprintf(tempBuf, "Tiles: %d", drawData.tiles_found);
	PrintString(tempBuf, 10, 90);

	sprintf(tempBuf, "Anims: %d", drawData.anim_objs_found);
	PrintString(tempBuf, 10, 105);

	sprintf(tempBuf, "TOTAL: %d", drawData.other_models_found + drawData.sprites_found + drawData.tiles_found + drawData.anim_objs_found);
	PrintString(tempBuf, 10, 120);
#endif

	SetupPlaneColours(combointensity);

	if (drawData.anim_objs_found)
		DrawAllAnimatingObjects((CELL_OBJECT**)anim_obj_buffer, drawData.anim_objs_found);

	if (drawData.sprites_found)
		DrawSprites((PACKED_CELL_OBJECT**)spriteList, drawData.sprites_found);

	if (drawData.tiles_found)
		DrawTILES((PACKED_CELL_OBJECT**)model_tile_ptrs, drawData.tiles_found);

	if (drawData.other_models_found)
		DrawAllBuildings((CELL_OBJECT**)model_object_ptrs, drawData.other_models_found);

	setupYet = 0;
}

#ifdef DYNAMIC_LIGHTING
struct DLIGHT
{
	SVECTOR position;
	CVECTOR color;
};

int gEnableDlights = 0;

int gNumDlights = 0;
DLIGHT gLights[MAX_DLIGHTS];

void AddDlight(VECTOR* position, CVECTOR* color, int radius)
{
	DLIGHT* pLight;
	VECTOR lightPos;
	if (gNumDlights + 1 >= MAX_DLIGHTS)
	{
		return;
	}

	pLight = &gLights[gNumDlights++];

	lightPos = *position;
	VecCopy(&pLight->position, &lightPos);
	pLight->position.pad = ABS(radius);

	pLight->color = *color;
}

void GetDLightLevel(SVECTOR* position, u_int* inOutColor)
{
	DLIGHT* pLight;
	int dx, dy, dz, dist, light;
	u_int lightR, lightG, lightB;

	lightR = (*inOutColor & 255);
	lightG = (*inOutColor >> 8 & 255);
	lightB = (*inOutColor >> 16 & 255);

	for (int i = 0; i < gNumDlights; i++)
	{
		int radius;
		pLight = &gLights[i];

		dx = (int)position->vx - (int)pLight->position.vx;
		dy = (int)position->vy - (int)pLight->position.vy;
		dz = (int)position->vz - (int)pLight->position.vz;

		dist = SquareRoot0(dx * dx + dy * dy + dz * dz);

		radius = pLight->position.pad;

		if (dist > radius) {
			continue;
		}

		light = radius - dist;

		lightR += pLight->color.r * light >> 13;
		lightG += pLight->color.g * light >> 13;
		lightB += pLight->color.b * light >> 13;
	}

	*inOutColor = MIN(lightB, 255) << 16 | MIN(lightG, 255) << 8 | MIN(lightR, 255) | (*inOutColor & 0xFF000000);
}

#endif // DYNAMIC_LIGHTING