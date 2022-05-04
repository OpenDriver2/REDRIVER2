#include "driver2.h"
#include "cars.h"
#include "texture.h"
#include "overmap.h"
#include "draw.h"
#include "mission.h"
#include "system.h"
#include "debris.h"
#include "main.h"
#include "camera.h"
#include "handling.h"
#include "cosmetic.h"
#include "shadow.h"
#include "civ_ai.h"
#include "mc_snd.h"
#include "gamesnd.h"
#include "players.h"
#include "cutscene.h"
#include "convert.h"
#include "glaunch.h"
#include "ASM/rndrasm.h"
#include "pres.h"

#include "../utils/stb_truetype.h"
#include "../utils/targa.h"

#include "PsyX/PsyX_render.h"

TextureID gCarReflectionTexture = 0;

struct plotCarGlobals
{
	u_char* primptr;
	OTTYPE* ot;
	u_int intensity;
	u_short* pciv_clut;
	u_char* damageLevel;
};

int gCarLODDistance = 0;
int gCarReflectionMapping = 0;


#ifndef PSX
#define CAR_LOD_SWITCH_DISTANCE gCarLODDistance;
#else
#define CAR_LOD_SWITCH_DISTANCE 5500; // default 5500
#endif

MATRIX light_matrix =
{ 
	{ 
		{ 4096, 0, 0 }, 
		{ 0, 0, 0 }, 
		{ 0, 0, 0 }
	}, 
	{ 0, 0, 0 } 
};

MATRIX colour_matrix =
{ 
	{ 
		{ 4032, 0, 0 }, 
		{ 3936, 0, 0 }, 
		{ 3520, 0, 0 }
	}, 
	{ 0, 0, 0 } 
};

// PHYSICS
CAR_DATA car_data[MAX_CARS + 2];	// all cars + Tanner cbox + Camera cbox

HUBCAP gHubcap;

MODEL* gHubcapModelPtr;
MODEL* gCleanWheelModelPtr;
MODEL* gFastWheelModelPtr;
MODEL* gDamWheelModelPtr;

// active carsg
CAR_DATA* active_car_list[MAX_CARS];
BOUND_BOX bbox[MAX_CARS];
u_char lightsOnDelay[MAX_CARS];
short FrontWheelRotation[MAX_CARS]; // offset 0x0
short BackWheelRotation[MAX_CARS]; // offset 0x30

SVECTOR gTempCarVertDump[MAX_CARS][MAX_DENTING_VERTS];

DENTUVS *gTempCarUVPtr;
DENTUVS gTempHDCarUVDump[MAX_CARS][MAX_DENTING_UVS];
DENTUVS gTempLDCarUVDump[MAX_CARS][MAX_DENTING_LOD_UVS];

CAR_MODEL NewCarModel[MAX_CAR_MODELS];
CAR_MODEL NewLowCarModel[MAX_CAR_MODELS];

MODEL* gCarLowModelPtr[MAX_CAR_MODELS];
MODEL* gCarDamModelPtr[MAX_CAR_MODELS];
MODEL* gCarCleanModelPtr[MAX_CAR_MODELS];

// pedestrian palette at 0 and next are cars
// model_id, texture_number, palette
u_short civ_clut[8][32][6];

int whichCP = 0;
int baseSpecCP = 0;
CAR_POLY carPolyBuffer[2001];

char LeftLight = 0;
char RightLight = 0;
char TransparentObject = 0;
MATRIX reflection_matrix;

// Get Started
void InitCarReflection()
{
	char namebuffer[64];
	u_char* data;

	// init Reflections Interactive
	if (!gCarReflectionTexture)
	{
		int width, height, bpp;

		if (gCarReflectionMapping == 1)
		sprintf(namebuffer, "%s%s", gDataFolder, "GFX\\HQ\\REFLECTIONS.TGA");


		FS_FixPathSlashes(namebuffer);

		if (LoadTGAImage(namebuffer, &data, width, height, bpp))
		{
			if (bpp == 32)
			{
				gCarReflectionTexture = GR_CreateRGBATexture(width, height, data);
			}
			free(data);
		}
	}
}

// [A] attempt to restore D1 reflections on car.
// Working, needs to move though.

void SetCarReflection(int enabled, plotCarGlobals* pg, int otOfs)
{
	if (gCarReflectionTexture == 0)
	{
		return;
	}

	DR_PSYX_TEX* tex = (DR_PSYX_TEX*)pg->primptr;
	if (enabled)
		SetPsyXTexture(tex, gCarReflectionTexture, 360, 360);
	else
		SetPsyXTexture(tex, 0, 0, 0);

	addPrim(pg->ot + otOfs, tex);
	pg->primptr += sizeof(DR_PSYX_TEX);
}

// [D] [T]
void plotCarPolyFT3Reflection(CAR_DATA *cp,int numTris, CAR_POLY* src, SVECTOR* vlist, plotCarGlobals* pg)
{
	int indices;
	int ofse;
	SVECTOR* v2;
	SVECTOR* v1;
	SVECTOR* v0;
	int Z;
	POLY_FT3* prim;
	OTTYPE* ot;
	int FT3rgb;
	int reg;
	SVECTOR direction;
	int i; 
	VECTOR* carPos;

	cp = &car_data[i];
	carPos = (VECTOR*)cp->hd.direction;

	FT3rgb = pg->intensity | 0x24000000;
	ot = pg->ot;

	gte_ldrgb(&FT3rgb);

	while (numTris > 0)
	{
		indices = src->vindices;
		v0 = vlist + (indices & 0xff);
		v1 = vlist + (indices >> 8 & 0xff);
		v2 = vlist + (indices >> 16 & 0xff);

		gte_ldv3(v0, v1, v2);

		gte_rtpt();

		gte_nclip();
		gte_stopz(&Z);
		gte_avsz3();

		if (Z > -1)
		{
			VERTTYPE sxy0[2];
			VERTTYPE sxy1[2];
			VERTTYPE sxy2[2];

			gte_stsxy3(&sxy0, &sxy1, &sxy2);
			gte_stotz(&Z);

			SetCarReflection(0, pg, (Z >> 1));

			prim = (POLY_FT3*)pg->primptr;

			*(uint*)&prim->x0 = *(uint*)sxy0;
			*(uint*)&prim->x1 = *(uint*)sxy1;
			*(uint*)&prim->x2 = *(uint*)sxy2;

			*(uint*)&prim->r0 = 0x202020;

			*(u_int*)&prim->u0 = src->clut_uv0;
			*(u_int*)&prim->u1 = src->tpage_uv1;
			*(u_int*)&prim->u2 = src->uv3_uv2;
			// Handles reflection movement
			prim->u0 += cp->hd.where.t[0];
			prim->u1 += cp->hd.where.t[0];
			prim->u2 += cp->hd.where.t[0];
			prim->v0 += cp->hd.where.t[2];
			prim->v1 += cp->hd.where.t[2];
			prim->v2 += cp->hd.where.t[2];

			prim->tpage = 0x20;

			setPolyFT3(prim);
			setSemiTrans(prim, 1);
			addPrim(ot + (Z >> 1), prim);

			pg->primptr = (unsigned char*)(prim + 1);

			SetCarReflection(1, pg, (Z >> 1));
		}
		numTris--;
		src++;
	}
}

// [D] [T]
void plotCarPolyB3(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg)
{
	int Z;
	int indices;
	u_int FT3rgb;
	SVECTOR *v2;
	SVECTOR *v1;
	SVECTOR *v0;
	POLY_F3 *prim;
	OTTYPE *ot;

	prim = (POLY_F3 *)pg->primptr;
	FT3rgb = pg->intensity;
	ot = pg->ot;

	while (numTris > 0)
	{
		indices = src->vindices;
		v0 = vlist + (indices & 0xff);
		v1 = vlist + (indices >> 8 & 0xff);
		v2 = vlist + (indices >> 16 & 0xff);

		gte_ldv3(v0, v1, v2);

		gte_rtpt();

		gte_nclip();
		gte_stopz(&Z);
		gte_avsz3();

		if (Z > -1) 
		{
			*(u_int*)&prim->r0 = FT3rgb | 0x20000000;

			gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);

			gte_stotz(&Z);

			setPolyF3(prim);
			addPrim(ot + (Z >> 1), prim);

			prim++;
		}

		numTris--;
		src++;
	}
	pg->primptr = (unsigned char*)prim;
}

// [D] [T]
void plotCarPolyFT3(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg)
{
	int indices;
	int ofse;
	SVECTOR *v2;
	SVECTOR *v1;
	SVECTOR *v0;
	int Z;
	POLY_FT3 *prim;
	OTTYPE *ot;
	int FT3rgb;
	int reg;

	prim = (POLY_FT3 *)pg->primptr;
	FT3rgb = pg->intensity | 0x24000000;
	ot = pg->ot;

	gte_ldrgb(&FT3rgb);

	while (numTris > 0)
	{
		indices = src->vindices;
		v0 = vlist + (indices & 0xff);
		v1 = vlist + (indices >> 8 & 0xff);
		v2 = vlist + (indices >> 16 & 0xff);

		gte_ldv3(v0, v1, v2);

		gte_rtpt();

		gte_nclip();
		gte_stopz(&Z);
		gte_avsz3();

		if (Z > -1) 
		{
			ofse = pg->damageLevel[src->originalindex];
			*(u_int*)&prim->r0 = FT3rgb;
			*(u_int*)&prim->u0 = src->clut_uv0 + ofse;
			*(u_int*)&prim->u1 = src->tpage_uv1 + ofse;
			*(u_int*)&prim->u2 = src->uv3_uv2 + ofse;

			gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);

			gte_stotz(&Z);

			setPolyFT3(prim);
			addPrim(ot + (Z >> 1), prim);

			prim++;
		}
		numTris--;
		src++;
	}
	pg->primptr = (unsigned char*)prim;
}

// [D] [T]
void plotCarPolyGT3(int numTris, CAR_POLY *src, SVECTOR *vlist, SVECTOR *nlist, plotCarGlobals *pg, int palette)
{
	int Z;
	int otz;	
	SVECTOR* v2;
	SVECTOR *v1;
	SVECTOR *v0;
	u_int indices;
	POLY_GT3 *prim;
	u_int r0,r1,r2;
	int ofse;

	prim = (POLY_GT3 *)pg->primptr;
	int GT3rgb = pg->intensity | 0x34000000;
	gte_ldrgb(&GT3rgb); 
	

	while (numTris > 0)
	{
		indices = src->vindices;

		v0 = vlist + (indices & 0xff);
		v1 = vlist + (indices >> 8 & 0xff);
		v2 = vlist + (indices >> 16 & 0xff);

		gte_ldv3(v0, v1, v2);

		gte_rtpt();
		gte_nclip();

		gte_stopz(&Z);

		gte_avsz3();
		
		gte_stotz(&otz);

		if (Z > -1 && otz > 0)
		{
			indices = src->nindices;
			
			
			r0 = (u_int)(ushort)nlist[indices & 0xff].pad;
			r1 = (u_int)(ushort)nlist[indices >> 8 & 0xff].pad;
			r2 = (u_int)(ushort)nlist[indices >> 16 & 0xff].pad;

			*(u_int*)&prim->r0 = (r0 & 0xff) << 0x10 | r0;
			*(u_int*)&prim->r1 = (r1 & 0xff) << 0x10 | r1;
			*(u_int*)&prim->r2 = (r2 & 0xff) << 0x10 | r2;

			ofse = pg->damageLevel[src->originalindex];

			*(u_int*)&prim->u0 = (src->clut_uv0 & 0xffffU | pg->pciv_clut[palette + (src->clut_uv0 >> 0x10)] << 0x10) + ofse;
			*(u_int*)&prim->u1 = src->tpage_uv1 + ofse;
			*(u_int*)&prim->u2 = src->uv3_uv2 + ofse;

			gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);
			
			setPolyGT3(prim);
			addPrim(pg->ot + (otz >> 1), prim);
			prim++;
			
		}
		src++;
		numTris--;
	}
		//
		pg->primptr = (unsigned char*)prim;

}


#ifdef DYNAMIC_LIGHTING
void plotCarPolyGT3Lit(int numTris, CAR_POLY* src, SVECTOR* vlist, SVECTOR* nlist, plotCarGlobals* pg, int palette)
{
	int Z;
	int otz;
	SVECTOR* v2;
	SVECTOR* v1;
	SVECTOR* v0;
	u_int indices;
	POLY_GT3* prim;
	u_int r0, r1, r2;
	int ofse;

	prim = (POLY_GT3*)pg->primptr;

	int GT3rgb = pg->intensity | 0x34000000;
	gte_ldrgb(&GT3rgb);

	while (numTris > 0)
	{
		indices = src->vindices;

		v0 = vlist + (indices & 0xff);
		v1 = vlist + (indices >> 8 & 0xff);
		v2 = vlist + (indices >> 16 & 0xff);

		gte_ldv3(v0, v1, v2);

		gte_rtpt();
		gte_nclip();

		gte_stopz(&Z);

		gte_avsz3();

		gte_stotz(&otz);

		if (Z > -1 && otz > 0)
		{
			indices = src->nindices;

			r0 = (u_int)(ushort)nlist[indices & 0xff].pad;
			r1 = (u_int)(ushort)nlist[indices >> 8 & 0xff].pad;
			r2 = (u_int)(ushort)nlist[indices >> 16 & 0xff].pad;

			*(u_int*)&prim->r0 = (r0 & 0xff) << 0x10 | r0;
			*(u_int*)&prim->r1 = (r1 & 0xff) << 0x10 | r1;
			*(u_int*)&prim->r2 = (r2 & 0xff) << 0x10 | r2;

			ofse = pg->damageLevel[src->originalindex];

			*(u_int*)&prim->u0 = (src->clut_uv0 & 0xffffU | pg->pciv_clut[palette + (src->clut_uv0 >> 0x10)] << 0x10) + ofse;
			*(u_int*)&prim->u1 = src->tpage_uv1 + ofse;
			*(u_int*)&prim->u2 = src->uv3_uv2 + ofse;

			gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);

			SVECTOR tmpPos;
			gte_ldv0(v0);
			gte_rtps();
			gte_stsv(&tmpPos);
			GetDLightLevel(&tmpPos, (u_int*)&prim->r0);

			gte_ldv0(v1);
			gte_rtps();
			gte_stsv(&tmpPos);
			GetDLightLevel(&tmpPos, (u_int*)&prim->r1);

			gte_ldv0(v2);
			gte_rtps();
			gte_stsv(&tmpPos);
			GetDLightLevel(&tmpPos, (u_int*)&prim->r2);

			setPolyGT3(prim);
			addPrim(pg->ot + (otz >> 1), prim);

			prim++;
		}
		src++;
		numTris--;
	}

	pg->primptr = (unsigned char*)prim;
}
#endif // DYNAMIC_LIGHTING


// [D] [T]
void plotCarPolyGT3nolight(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg, int palette)
{
	int Z;
	int otz;
	SVECTOR* v2;
	SVECTOR* v1;
	SVECTOR* v0;
	u_int indices;
	POLY_FT3* prim;
	int ofse;

	prim = (POLY_FT3*)pg->primptr;

	int GT3rgb = pg->intensity | 0x34000000;
	gte_ldrgb(&GT3rgb);

	while (numTris > 0)
	{
		indices = src->vindices;

		v0 = vlist + (indices & 0xff);
		v1 = vlist + (indices >> 8 & 0xff);
		v2 = vlist + (indices >> 16 & 0xff);

		gte_ldv3(v0, v1, v2);

		gte_rtpt();
		gte_nclip();
		gte_stopz(&Z);

		gte_avsz3();
		gte_stotz(&otz);

		if (Z > -1 && otz > 0)
		{
			*(u_int*)&prim->r0 = GT3rgb;

			ofse = pg->damageLevel[src->originalindex];

			*(u_int*)&prim->u0 = (src->clut_uv0 & 0xffffU | pg->pciv_clut[palette + (src->clut_uv0 >> 0x10)] << 0x10) + ofse;
			*(u_int*)&prim->u1 = src->tpage_uv1 + ofse;
			*(u_int*)&prim->u2 = src->uv3_uv2 + ofse;

			gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);

			setPolyFT3(prim);
			addPrim(pg->ot + (otz >> 1), prim);

			prim++;
		}

		src++;
		numTris--;
	}

	pg->primptr = (unsigned char*)prim;
}

MATRIX save_colour_matrix;
MATRIX save_light_matrix;

// [D] [T]
void setupLightingMatrices(void)
{
	gte_ReadColorMatrix(&save_colour_matrix);
	gte_ReadLightMatrix(&save_light_matrix);

	gte_SetColorMatrix(&colour_matrix);
	gte_SetLightMatrix(&light_matrix);

	if (gTimeOfDay == TIME_NIGHT)
	{
		gte_SetBackColor(48, 48, 48);
	}
	else
	{
		gte_SetBackColor(140, 140, 140);
	}
}

// [D] [T]
void restoreLightingMatrices(void)
{
	gte_SetColorMatrix(&save_colour_matrix);
	gte_SetLightMatrix(&save_light_matrix);
}

// [D] [T]
void ComputeCarLightingLevels(CAR_DATA* cp, char detail)
{
#ifdef PSX
	MATRIX& scratchPadMat = *(MATRIX*)((u_char*)getScratchAddr(0) + 0x100);
#else
	MATRIX scratchPadMat;
#endif

	int doLight;
	int orW, orY;
	MODEL* model;
	int num_norms, count;
	SVECTOR* ppads;
	SVECTOR* norms;
	SVECTOR colour, lightsourcevector;
	CVECTOR c0, c1, c2;
	u_int GT3rgb;

	if (gTimeOfDay == TIME_NIGHT)
	{
		lightsourcevector = night_vectors[GameLevel];
		colour = night_colours[GameLevel];
	}
	else
	{
		lightsourcevector = day_vectors[GameLevel];
		colour = day_colours[GameLevel];
	}

	InvertMatrix(&cp->hd.where, &scratchPadMat);
	SetRotMatrix(&scratchPadMat);

	gte_ldv0(&lightsourcevector);
	gte_rtv0();
	gte_stsv(light_matrix.m[0]);

	colour_matrix.m[0][0] = colour.vx;
	colour_matrix.m[1][0] = colour.vy;
	colour_matrix.m[2][0] = colour.vz;

	orY = ABS(cp->st.n.orientation[1] - cp->ap.qy);
	orW = ABS(cp->st.n.orientation[3] - cp->ap.qw);

	doLight = 0;

	if ((orY + orW > 200) || (cp->lowDetail != (detail | lightning)))
		doLight = 1;

	if ((M_BIT(gTimeOfDay) & (M_BIT(TIME_DAWN) | M_BIT(TIME_DUSK))) && (cp->id & 15) == (CameraCnt & 15))
		doLight = 1;

	if (doLight)
	{
		setupLightingMatrices();

		GT3rgb = combointensity & 0xffffffU | 0x34000000;
		gte_ldrgb(&GT3rgb);

		cp->ap.qy = cp->st.n.orientation[1];
		cp->ap.qw = cp->st.n.orientation[3];
		cp->lowDetail = detail | lightning;

		if (detail == 0)
			model = gCarLowModelPtr[cp->ap.model];
		else
			model = gCarCleanModelPtr[cp->ap.model];

		num_norms = model->num_point_normals / 3;
		norms = (SVECTOR*)model->point_normals;

		ppads = gTempCarVertDump[cp->id];
		count = num_norms;// +1;

		while (count >= 0)
		{
			gte_ldv3(&norms[0], &norms[1], &norms[2]);
			gte_ncct();
			gte_strgb3(&c0, &c1, &c2);

			ppads[0].pad = *(short*)&c0;
			ppads[1].pad = *(short*)&c1;
			ppads[2].pad = *(short*)&c2;

			count--;
			norms += 3;
			ppads += 3;
		}

		restoreLightingMatrices();
	}
}

// [D] [T]
void DrawWheelObject(MODEL* model, SVECTOR* verts, int transparent, int wheelnum)
{
	ushort clut;
	ushort tpage;
	int i;
	int Z;
	int otZ;
	int combo;
	POLY_FT4* poly;
	POLYFT4* src;
	u_int dim;
	u_int bright;

	src = (POLYFT4*)model->poly_block;
	poly = (POLY_FT4*)current->primptr;

	clut = texture_cluts[src->texture_set][src->texture_id];
	tpage = texture_pages[src->texture_set] | 0x20;

	if (gTimeOfDay > -1)
	{
		if (gTimeOfDay < TIME_NIGHT)
		{
			bright = combointensity & 0xffffffU | 0x2c000000;
			dim = (combointensity & 0xfcfcfcU) >> 2 | 0x2c000000;
		}
		else if (gTimeOfDay == TIME_NIGHT)
		{
			combo = (combointensity & 0xffU) / 3;
			combo = combo << 0x10 | combo << 8 | combo;

			bright = combo | 0x2c000000;
			dim = (combo & 0xfcfcfc) >> 2 | 0x2c000000;
		}
	}

	i = model->num_polys;

	while (i-- != -1)
	{
		gte_ldv3(&verts[src->v0], &verts[src->v1], &verts[src->v2]);

		gte_rtpt();
		gte_nclip();

		gte_stopz(&Z);
		gte_stsxy0(&poly->x0);

		gte_ldv0(&verts[src->v3]);

		gte_rtps();
		gte_avsz4();

		gte_stotz(&otZ);

		if (otZ > 2)
		{
			setPolyFT4(poly);
			addPrim(current->ot + (otZ >> 1) + 5, poly);

			if (i < 2 || Z < 0)
				*(u_int*)&poly->r0 = 0x2c000000;
			else if (((i ^ wheelnum >> 1) & 1) == 0)
				*(u_int*)&poly->r0 = dim;
			else
				*(u_int*)&poly->r0 = bright;

			setSemiTrans(poly, transparent);

			gte_stsxy3(&poly->x1, &poly->x3, &poly->x2);

			*(u_short*)&poly->u0 = *(u_short*)&src->uv0;
			*(u_short*)&poly->u1 = *(u_short*)&src->uv1;
			*(u_short*)&poly->u2 = *(u_short*)&src->uv3;
			*(u_short*)&poly->u3 = *(u_short*)&src->uv2;
			poly->clut = clut;
			poly->tpage = tpage;

			poly++;
		}
		src++;
	}
	current->primptr = (char*)poly;
}

// [D] [T]
void DrawCarWheels(CAR_DATA *cp, MATRIX *RearMatrix, VECTOR *pos, int zclip)
{
	short wheelSize;
	int FW1z, FW2z;
	int BW1z, BW2z;
	int FrontWheelIncrement, BackWheelIncrement;
	int sizeScale;
	int wheelnum;
	SVECTOR* VertPtr;
	SVECTOR* wheelDisp;
	WHEEL* wheel;
	int car_id;
	MODEL* WheelModelBack;
	MODEL* WheelModelFront;
	MODEL* model;

#ifdef PSX
	MATRIX& FrontMatrix = *(MATRIX*)(u_char*)getScratchAddr(0);
	MATRIX& SteerMatrix = *(MATRIX*)((u_char*)getScratchAddr(0) + sizeof(MATRIX));
	VECTOR& WheelPos = *(VECTOR*)((u_char*)getScratchAddr(0) + sizeof(MATRIX) * 2);
	SVECTOR& sWheelPos = *(SVECTOR*)((u_char*)getScratchAddr(0) + sizeof(MATRIX) * 2 + sizeof(VECTOR));
	static_assert(sizeof(MATRIX) * 2 + sizeof(VECTOR) + sizeof(SVECTOR) * 25 < 1024 - sizeof(_pct), "Scratchpad overflow");
#else
	MATRIX FrontMatrix;
	MATRIX SteerMatrix;
	VECTOR WheelPos;
	SVECTOR sWheelPos;
#endif

	D_CHECK_ERROR(cp < car_data, "Invalid car");

	car_id = CAR_INDEX(cp);

	BackWheelIncrement = FrontWheelIncrement = cp->hd.wheel_speed >> 8;

	if (cp->wheelspin != 0)
		BackWheelIncrement = 700;

	if (cp->hd.wheel[0].locked != 0)
		FrontWheelIncrement = 0;

	if (cp->hd.wheel[3].locked != 0)
		BackWheelIncrement = 0;

	if (FrontWheelIncrement + 400U < 801)
		WheelModelFront = gCleanWheelModelPtr;
	else
		WheelModelFront = gFastWheelModelPtr;

	if (BackWheelIncrement + 400U < 801)
		WheelModelBack = gCleanWheelModelPtr;
	else
		WheelModelBack = gFastWheelModelPtr;

	wheelSize = car_cosmetics[cp->ap.model].wheelSize;
	
	sizeScale = (wheelSize * 14142) / 10000;

	// rotate wheel verts

	FW1z = FIXEDH(RSIN(FrontWheelRotation[car_id]) * sizeScale);
	FW2z = FIXEDH(RCOS(FrontWheelRotation[car_id]) * sizeScale);

	VertPtr = (SVECTOR*)WheelModelFront->vertices;

	VertPtr[8].vz = FW1z;
	VertPtr[15].vz = FW1z;
	VertPtr[11].vy = FW1z;
	VertPtr[12].vy = FW1z;

	VertPtr[9].vy = -FW1z;
	VertPtr[14].vy = -FW1z;
	VertPtr[10].vz = -FW1z;
	VertPtr[13].vz = -FW1z;

	VertPtr[8].vy = FW2z;
	VertPtr[15].vy = FW2z;
	VertPtr[9].vz = FW2z;
	VertPtr[14].vz = FW2z;

	VertPtr[10].vy = -FW2z;
	VertPtr[13].vy = -FW2z;
	VertPtr[11].vz = -FW2z;
	VertPtr[12].vz = -FW2z;

	VertPtr[23].vz = 0;
	VertPtr[22].vz = 0;
	VertPtr[21].vy = 0;
	VertPtr[20].vy = 0;
	VertPtr[19].vy = 0;
	VertPtr[18].vy = 0;
	VertPtr[17].vz = 0;
	VertPtr[16].vz = 0;

	VertPtr[23].vy = wheelSize;
	VertPtr[22].vy = wheelSize;
	VertPtr[21].vz = wheelSize;
	VertPtr[20].vz = wheelSize;

	VertPtr[19].vz = -wheelSize;
	VertPtr[18].vz = -wheelSize;
	VertPtr[17].vy = -wheelSize;
	VertPtr[16].vy = -wheelSize;

	BW1z = FIXEDH(RSIN(BackWheelRotation[car_id]) * sizeScale);
	BW2z = FIXEDH(RCOS(BackWheelRotation[car_id]) * sizeScale);

	VertPtr = (SVECTOR *)WheelModelBack->vertices;
	
	VertPtr[8].vz = BW1z;
	VertPtr[15].vz = BW1z;
	VertPtr[11].vy = BW1z;
	VertPtr[12].vy = BW1z;

	VertPtr[9].vy = -BW1z;
	VertPtr[14].vy = -BW1z;
	VertPtr[10].vz = -BW1z;
	VertPtr[13].vz = -BW1z;

	VertPtr[8].vy = BW2z;
	VertPtr[15].vy = BW2z;
	VertPtr[9].vz = BW2z;
	VertPtr[14].vz = BW2z;

	VertPtr[10].vy = -BW2z;
	VertPtr[13].vy = -BW2z;
	VertPtr[11].vz = -BW2z;
	VertPtr[12].vz = -BW2z;

	VertPtr[23].vz = 0;
	VertPtr[22].vz = 0;
	VertPtr[21].vy = 0;
	VertPtr[20].vy = 0;
	VertPtr[19].vy = 0;
	VertPtr[18].vy = 0;
	VertPtr[17].vz = 0;
	VertPtr[16].vz = 0;

	VertPtr[23].vy = wheelSize;
	VertPtr[22].vy = wheelSize;
	VertPtr[21].vz = wheelSize;
	VertPtr[20].vz = wheelSize;

	VertPtr[19].vz = -wheelSize;
	VertPtr[18].vz = -wheelSize;
	VertPtr[17].vy = -wheelSize;
	VertPtr[16].vy = -wheelSize;

	SteerMatrix.m[0][0] = RCOS(cp->wheel_angle);
	SteerMatrix.m[0][2] = RSIN(cp->wheel_angle);
	SteerMatrix.m[1][1] = ONE;
	SteerMatrix.m[2][1] = 0;
	SteerMatrix.m[1][2] = 0;
	SteerMatrix.m[1][0] = 0;
	SteerMatrix.m[0][1] = 0;
	SteerMatrix.m[2][0] = -SteerMatrix.m[0][2];
	SteerMatrix.m[2][2] = SteerMatrix.m[0][0];

	MulMatrix0(RearMatrix, &SteerMatrix, &FrontMatrix);

	wheelDisp = car_cosmetics[cp->ap.model].wheelDisp;
	wheel = cp->hd.wheel;
	wheelnum = 0;

	do {
		if ((wheelnum & 1) != 0)
			model = WheelModelBack;
		else
			model = WheelModelFront;

		VertPtr = (SVECTOR*)model->vertices;

		if (cp->ap.flags & (1 << wheelnum)) // [A] used appearance flags to store hubcap presence
		{
			model = gDamWheelModelPtr;
		}

		if ((wheelnum & 2) == 0) 
			sWheelPos.vx = 17 - wheelDisp->vx;
		else
			sWheelPos.vx = -17 - wheelDisp->vx;

		sWheelPos.vz = -wheelDisp->vz;
		sWheelPos.vy = (-wheelSize - wheelDisp->vy) - wheel->susCompression + 14;

		gte_SetRotMatrix(RearMatrix);
		gte_ldv0(&sWheelPos);

		gte_rtv0();

		gte_stlvl(&WheelPos);

		WheelPos.vx += pos->vx;
		WheelPos.vy += pos->vy;
		WheelPos.vz += pos->vz;

		gte_SetTransVector(&WheelPos);

		if ((wheelnum & 1) == 0) 
		{
			gte_SetRotMatrix(&FrontMatrix);
		}

		DrawWheelObject(model, VertPtr, TransparentObject, wheelnum);

		wheelDisp++;
		wheel++;
		wheelnum++;
	} while (wheelnum < 4);
}

// [D] [T]
void PlayerCarFX(CAR_DATA *cp)
{
	int WheelSpeed;
	WheelSpeed = cp->hd.wheel_speed;

	if (WheelSpeed + 199U < 0x4b0c7)
	{
		if (cp->wheel_angle < -200)
			AddIndicatorLight(cp, 0);
		else if (cp->wheel_angle > 200)
			AddIndicatorLight(cp, 1);
	}

	if( WheelSpeed < 0 && cp->thrust > 0 ||
		WheelSpeed > 0 && cp->thrust < 0)
	{
		AddBrakeLight(cp);
	}

	if (WheelSpeed < 0 && cp->thrust < 0)
		AddReverseLight(cp);
}

// [D] [T]
void plotNewCarModel(CAR_MODEL* car, CAR_DATA* cp, int palette)
{
#ifdef PSX
	plotCarGlobals& _pg = *(plotCarGlobals*)((u_char*)getScratchAddr(0) + 1024 - sizeof(plotCarGlobals) - sizeof(_pct));
#else
	plotCarGlobals _pg;
#endif

	u_int lightlevel;
	u_int underIntensity;
	SVECTOR v = { 0, -4096, 0 };

	lightlevel = combointensity | 0x3000000;

	if (car == NULL)
		return;

	if (gTimeOfDay > -1)
	{
		if (gTimeOfDay < TIME_NIGHT)
			lightlevel = combointensity | 0x30000000;
		else if (gTimeOfDay == TIME_NIGHT)
			lightlevel = 0x302a2a2a;
	}

	setupLightingMatrices();

	gte_ldv0(&v);
	gte_ldrgb(&lightlevel);

	gte_nccs();

	_pg.primptr = (u_char*)current->primptr;
	_pg.intensity = 0;
	_pg.pciv_clut = (u_short*)&civ_clut[1];
	_pg.damageLevel = (u_char*)gTempCarUVPtr;

	_pg.ot = (OTTYPE*)(current->ot + 28);

	gte_strgb(&underIntensity);

	// draw wheel arcs
	plotCarPolyB3(car->numB3, car->pB3, car->vlist, &_pg);
	_pg.intensity = underIntensity & 0xffffff;

	// draw car bottom
	_pg.ot = (OTTYPE*)(current->ot + 16);
	plotCarPolyFT3(car->numFT3, car->pFT3, car->vlist, &_pg);

	// draw car body
	_pg.ot = (OTTYPE*)(current->ot + 4);
	if (gTimeOfDay == TIME_NIGHT)
	{
		_pg.intensity = (combointensity & 0xfcfcf0U) >> 2;
#ifdef DYNAMIC_LIGHTING
		(gEnableDlights ? plotCarPolyGT3Lit : plotCarPolyGT3)(car->numGT3, car->pGT3, car->vlist, car->nlist, &_pg, palette);
#else
		plotCarPolyGT3nolight(car->numGT3, car->pGT3, car->vlist, &_pg, palette);
#endif // DYNAMIC_LIGHTING
	}
	else
	{
		_pg.intensity = combointensity & 0xffffff;
#ifdef DYNAMIC_LIGHTING
		(gEnableDlights ? plotCarPolyGT3Lit : plotCarPolyGT3)(car->numGT3, car->pGT3, car->vlist, car->nlist, &_pg, palette);
#else
		plotCarPolyGT3(car->numGT3, car->pGT3, car->vlist, car->nlist, &_pg, palette);
#endif
	}

	if (gCarReflectionMapping == 1)
	{
		_pg.ot = (OTTYPE*)(current->ot - 4);
		plotCarPolyFT3Reflection(cp, car->numGT3, car->pGT3, car->vlist, &_pg);
	}

	current->primptr = (char*)_pg.primptr;

	restoreLightingMatrices();
}

// [D] [T]
void buildNewCars(void)
{
	buildNewCarFromModel(&NewCarModel[0], gCarCleanModelPtr[0], 1);
	buildNewCarFromModel(&NewLowCarModel[0], gCarLowModelPtr[0], 0);

	buildNewCarFromModel(&NewCarModel[1], gCarCleanModelPtr[1], 0);
	buildNewCarFromModel(&NewLowCarModel[1], gCarLowModelPtr[1], 0);

	buildNewCarFromModel(&NewCarModel[2], gCarCleanModelPtr[2], 0);
	buildNewCarFromModel(&NewLowCarModel[2], gCarLowModelPtr[2], 0);

	buildNewCarFromModel(&NewCarModel[3], gCarCleanModelPtr[3], 0);
	buildNewCarFromModel(&NewLowCarModel[3], gCarLowModelPtr[3], 0);

	// build special car
	baseSpecCP = whichCP;
	buildNewCarFromModel(&NewCarModel[4], gCarCleanModelPtr[4], 0);
	buildNewCarFromModel(&NewLowCarModel[4], gCarLowModelPtr[4], 0);
}

// [D] [T]
void buildNewCarFromModel(CAR_MODEL *car, MODEL *model, int first)
{
	u_char ptype, clut;
	u_char *polyList;
	CAR_POLY *cp;

	int newNumPolys;

	int i, pass;

	if (first) 
		whichCP = 0;

	if (model == NULL || (model->shape_flags & 0xfffffff) > 0x800000)
	{
		car->numGT3 = 0;
		car->numFT3 = 0;
		car->numB3 = 0;
	}
	else 
	{
		car->vlist = (SVECTOR *)model->vertices;
		car->nlist = (SVECTOR *)model->point_normals;

		for (pass = 0; pass < 3; pass++)
		{
			polyList = (u_char *)model->poly_block;

			if (pass == 1)
				car->pFT3 = carPolyBuffer + whichCP;
			else if (pass == 0)
				car->pGT3 = carPolyBuffer + whichCP;
			else if (pass == 2)
				car->pB3 = carPolyBuffer + whichCP;

			newNumPolys = whichCP;

			for (i = 0; newNumPolys < 2000 && i < model->num_polys; i++)
			{
				ptype = *polyList;

				cp = carPolyBuffer + newNumPolys;

				switch (ptype & 0x1f) 
				{
					case 0:
					case 18:
						if (pass == 2)	// F3
						{
							cp->vindices = M_INT_4R(polyList[1], polyList[2], polyList[3], 0);
							cp->originalindex = i;

							newNumPolys++;
						}
						break;
					case 1:
					case 19:
						if (pass == 2)	// F4
						{
							cp->vindices = M_INT_4R(polyList[4], polyList[5], polyList[6], 0); 
							cp->originalindex = i;

							cp++;

							cp->vindices = M_INT_4R(polyList[4], polyList[6], polyList[7], 0);
							cp->originalindex = i;

							newNumPolys += 2;
						}
						break;
					case 20:
						if (pass == 1)	// FT3
						{
							POLYFT3* pft3 = (POLYFT3*)polyList;
									
							cp->vindices = M_INT_4R(pft3->v0, pft3->v1, pft3->v2, 0);
							cp->clut_uv0 = M_INT_2(texture_cluts[pft3->texture_set][pft3->texture_id], *(ushort*)&pft3->uv0);
							cp->tpage_uv1 = M_INT_2(texture_pages[pft3->texture_set], *(ushort*)&pft3->uv1);
							cp->uv3_uv2 = *(ushort*)&pft3->uv2;
							cp->originalindex = i;

							newNumPolys++;
						}
						break;
					case 21:
						if (pass == 1)	// FT4
						{
							POLYFT4* pft4 = (POLYFT4*)polyList;

							cp->vindices = M_INT_4R(pft4->v0, pft4->v1, pft4->v2, 0);
							cp->clut_uv0 = M_INT_2(texture_cluts[pft4->texture_set][pft4->texture_id], *(ushort *)&pft4->uv0);
							cp->tpage_uv1 = M_INT_2(texture_pages[pft4->texture_set], *(ushort*)&pft4->uv1);
							cp->uv3_uv2 = *(ushort*)&pft4->uv2;
							cp->originalindex = i;

							cp++;
						
							cp->vindices = M_INT_4R(pft4->v0, pft4->v2, pft4->v3, 0);
							cp->clut_uv0 = M_INT_2(texture_cluts[polyList[1]][polyList[2]], *(ushort*)&pft4->uv0);
							cp->tpage_uv1 = M_INT_2(texture_pages[polyList[1]], *(ushort*)&pft4->uv2);
							cp->uv3_uv2 = *(ushort*)&pft4->uv3;
							cp->originalindex = i;

							newNumPolys += 2;
						}
						break;
					case 22:
						if (pass == 0) // GT3
						{
							POLYGT3* pgt3 = (POLYGT3*)polyList;
							
							clut = GetCarPalIndex(pgt3->texture_set);
							civ_clut[clut][pgt3->texture_id][0] = texture_cluts[pgt3->texture_set][pgt3->texture_id];
						
							cp->vindices = M_INT_4R(pgt3->v0, pgt3->v1, pgt3->v2, 0);
							cp->nindices = M_INT_4R(pgt3->n0, pgt3->n1, pgt3->n2, 0);
							cp->clut_uv0 = M_INT_2((clut * 384 + pgt3->texture_id * 12 - 384) >> 1, * (ushort*)&pgt3->uv0);
							cp->tpage_uv1 = M_INT_2(texture_pages[pgt3->texture_set], *(ushort *)&pgt3->uv1);
							cp->uv3_uv2 = *(ushort *)&pgt3->uv2;
							cp->originalindex = i;

							newNumPolys++;
						}
						break;
					case 23:
						if (pass == 0)  // GT4
						{
							POLYGT4* pgt4 = (POLYGT4*)polyList;

							clut = GetCarPalIndex(pgt4->texture_set);
							civ_clut[clut][pgt4->texture_id][0] = texture_cluts[pgt4->texture_set][pgt4->texture_id];

							cp->vindices = M_INT_4R(pgt4->v0, pgt4->v1, pgt4->v2, 0);
							cp->nindices = M_INT_4R(pgt4->n0, pgt4->n1, pgt4->n2, 0);
							cp->clut_uv0 = M_INT_2((clut * 384 + pgt4->texture_id * 12 - 384) >> 1, *(ushort*)&pgt4->uv0);
							cp->tpage_uv1 = M_INT_2(texture_pages[pgt4->texture_set], *(ushort*)&pgt4->uv1);
							cp->uv3_uv2 = *(ushort*)&pgt4->uv2;
							cp->originalindex = i;

							cp++;

							cp->vindices = M_INT_4R(pgt4->v0, pgt4->v2, pgt4->v3, 0);
							cp->nindices = M_INT_4R(pgt4->n0, pgt4->n2, pgt4->n3, 0);
							cp->clut_uv0 = M_INT_2((clut * 384 + pgt4->texture_id * 12 - 384) >> 1, *(ushort*)&pgt4->uv0);
							cp->tpage_uv1 = M_INT_2(texture_pages[pgt4->texture_set], *(ushort *)&pgt4->uv2);
							cp->uv3_uv2 = *(ushort *)&pgt4->uv3;
							cp->originalindex = i;

							newNumPolys += 2;
						}
				}

				polyList += PolySizes[ptype & 0x1f];
			}

			if (pass == 1) 
				car->numFT3 = newNumPolys - whichCP;
			else if (pass == 0)
				car->numGT3 = newNumPolys - whichCP;
			else if (pass == 2) 
				car->numB3 = newNumPolys - whichCP;

			whichCP = newNumPolys;
		}
	}
}

// [D] [T]
void MangleWheelModels(void)
{
	UV_INFO tmpUV2;
	u_char tmpUV;
	u_int v0, v1, v2;
	POLYFT4*src;
	MODEL *m;
	int i, j;

	for (i = 0; i < 3; i++)
	{
		if (i == 1)
			m = gFastWheelModelPtr;
		else if (i == 2)
			m = gDamWheelModelPtr;
		else
			m = gCleanWheelModelPtr;

		// do some fuckery swaps
		src = (POLYFT4*)m->poly_block;
		
		v0 = *(u_int *)&src[2].v0;
		v1 = *(u_int *)&src[2].uv0;
		v2 = *(u_int *)&src[2].uv2;
		*(u_int *)src = *(u_int *)(src + 2);
		*(u_int *)&src->v0 = v0;
		*(u_int *)&src->uv0 = v1;
		*(u_int *)&src->uv2 = v2;
		src->color = src[2].color;

		v0 = *(u_int *)&src[3].v0;
		v1 = *(u_int *)&src[3].uv0;
		v2 = *(u_int *)&src[3].uv2;
		*(u_int *)(src + 1) = *(u_int *)(src + 3);
		*(u_int *)&src[1].v0 = v0;
		*(u_int *)&src[1].uv0 = v1;
		*(u_int *)&src[1].uv2 = v2;
		src[1].color = src[3].color;

		v0 = *(u_int *)&src[4].v0;
		v1 = *(u_int *)&src[4].uv0;
		v2 = *(u_int *)&src[4].uv2;
		*(u_int *)(src + 2) = *(u_int *)(src + 4);
		*(u_int *)&src[2].v0 = v0;
		*(u_int *)&src[2].uv0 = v1;
		*(u_int *)&src[2].uv2 = v2;
		src[2].color = src[4].color;

		v0 = *(u_int *)&src[6].v0;
		v1 = *(u_int *)&src[6].uv0;
		v2 = *(u_int *)&src[6].uv2;
		*(u_int *)(src + 3) = *(u_int *)(src + 6);
		*(u_int *)&src[3].v0 = v0;
		*(u_int *)&src[3].uv0 = v1;
		*(u_int *)&src[3].uv2 = v2;
		src[3].color = src[6].color;

		src[2].v2 = 23;
		src[2].v3 = 22;
		src[3].v0 = 21;
		src[3].v1 = 20;
		src[3].v2 = 19;
		src[3].v3 = 18;
		src[2].v1 = 17;
		src[2].v0 = 16;

		tmpUV = (src->uv0.u + src->uv2.u) / 2;
		src[3].uv3.u = tmpUV;
		src[3].uv2.u = tmpUV;
		src[3].uv1.u = tmpUV;
		src[3].uv0.u = tmpUV;
		src[2].uv3.u = tmpUV;
		src[2].uv2.u = tmpUV;
		src[2].uv1.u = tmpUV;
		src[2].uv0.u = tmpUV;

		tmpUV = (src->uv0.v + src->uv2.v) / 2;
		src[3].uv3.v = tmpUV;
		src[3].uv2.v = tmpUV;
		src[3].uv1.v = tmpUV;
		src[3].uv0.v = tmpUV;
		src[2].uv3.v = tmpUV;
		src[2].uv2.v = tmpUV;
		src[2].uv1.v = tmpUV;
		src[2].uv0.v = tmpUV;

		m->num_polys = 4;

		for (j = 0; j < 2; j++)
		{
			tmpUV2 = src->uv0;
			
			src->uv0 = src->uv1;
			src->uv1 = src->uv2;
			src->uv2 = src->uv3;
			src->uv3 = tmpUV2;

			src++;
		}

	} while (++i < 3);

	// HACK: Show clean model only in Rio.
	//if (GameLevel == 3) 
	//	gFastWheelModelPtr = gCleanWheelModelPtr;
}

// [D] [T]
void ProcessPalletLump(char *lump_ptr, int lump_size)
{
	ushort clutValue;
	int *buffPtr;
	int texnum;
	int palette;
	u_short *clutTablePtr;
	u_short clutTable[320];
	int tpageindex;
	int total_cluts;
	int clut_number;

	total_cluts = *(int*)lump_ptr;
	
	if (total_cluts == 0)
		return;

	buffPtr = (int*)(lump_ptr + 4);
	clutTablePtr = (u_short*)clutTable;

	while (*buffPtr != -1)
	{
		palette = buffPtr[0];
		texnum = buffPtr[1];
		tpageindex = buffPtr[2];
		clut_number = buffPtr[3];

		if (clut_number == -1)
		{
			// store clut
			LoadImage(&clutpos, (u_long*)(buffPtr + 4));

			clutValue = GetClut(clutpos.x, clutpos.y);
			*clutTablePtr++ = clutValue;

			IncrementClutNum(&clutpos);

			buffPtr += 12;
		}
		else
		{
			// use stored clut
			clutValue = clutTable[clut_number];
			buffPtr += 4;
		}

		civ_clut[GetCarPalIndex(tpageindex)][texnum][palette + 1] = clutValue;
	}
}

// [D] [T]
void DrawCarObject(CAR_MODEL* car, MATRIX* matrix, VECTOR* pos, int palette, CAR_DATA* cp, int detail)
{
	VECTOR modelLocation;
	SVECTOR cog;

	cog = cp->ap.carCos->cog;

	// [A] mini cars correct position
	if (ActiveCheats.cheat13 != 0)
	{
		cog.vx <<= 1;
		cog.vy <<= 1;
		cog.vz <<= 1;
	}

	gte_SetRotMatrix(matrix);
	gte_SetTransVector(pos);

	gte_ldv0(&cog);

	gte_rtv0tr();

	gte_stlvnl(&modelLocation);

	gte_SetTransVector(&modelLocation);

	plotNewCarModel(car, cp, palette);
}

// [D] [T] [A]
void DrawCar(CAR_DATA* cp, int view)
{
	int yVal;
	int maxDamage;
	int WheelSpeed;
	int oboxLenSq;
	CAR_MODEL* CarModelPtr;
	int model;
	CVECTOR col;
	SVECTOR d;
	VECTOR pos, dist;
	VECTOR corners[4];
	MATRIX workmatrix;

	D_CHECK_ERROR(cp < car_data, "Invalid car");

	model = cp->ap.model;

	// draw car lights in for InCar camera
	if (player[view].cameraView == 2 && cp->id == player[view].cameraCarId)
	{
		if (cp->ap.damage[0] < 500)
			LeftLight = 2;
		else if (cp->ap.damage[0] < 1000)
			LeftLight = 1;
		else
			LeftLight = 0;

		if (cp->ap.damage[1] < 500)
			RightLight = 2;
		else if (cp->ap.damage[1] < 1000)
			RightLight = 1;
		else
			RightLight = 0;

		if (gLightsOn == 0)
			return;

		if (lightsOnDelay[cp->id])
			return;

		col.r = 128;
		col.g = 120;
		col.b = 110;

		PlacePoolForCar(cp, &col, 1, 1);
		return;
	}

	pos.vx = cp->hd.where.t[0];
	pos.vz = cp->hd.where.t[2];
	pos.vy = -cp->hd.where.t[1];

	SetFrustrumMatrix();

	if (FrustrumCheck(&pos, 800) == -1)
		return;

	// corners for frustrum checking of big cars
	corners[0].vx = corners[1].vx = pos.vx + cp->hd.oBox.radii[0].vx;
	corners[0].vx += cp->hd.oBox.radii[2].vx;
	corners[1].vx -= cp->hd.oBox.radii[2].vx;

	corners[2].vx = corners[3].vx = pos.vx - cp->hd.oBox.radii[0].vx;
	corners[2].vx += cp->hd.oBox.radii[2].vx;
	corners[3].vx -= cp->hd.oBox.radii[2].vx;

	corners[0].vz = corners[1].vz = pos.vz + cp->hd.oBox.radii[0].vz;
	corners[0].vz += cp->hd.oBox.radii[2].vz;
	corners[1].vz -= cp->hd.oBox.radii[2].vz;

	corners[2].vz = corners[3].vz = pos.vz - cp->hd.oBox.radii[0].vz;
	corners[2].vz += cp->hd.oBox.radii[2].vz;
	corners[3].vz -= cp->hd.oBox.radii[2].vz;

	corners[3].vy = pos.vy;
	corners[2].vy = pos.vy;
	corners[1].vy = pos.vy;
	corners[0].vy = pos.vy;

	if (FrustrumCheck(corners, 0) == -1 &&
		FrustrumCheck(corners + 1, 0) == -1 &&
		FrustrumCheck(corners + 2, 0) == -1 &&
		FrustrumCheck(corners + 3, 0) == -1)
	{
		return;
	}

	d.vx = cp->hd.oBox.location.vx - camera_position.vx;
	d.vy = -camera_position.vy - cp->hd.oBox.location.vy;
	d.vz = cp->hd.oBox.location.vz - camera_position.vz;

	dist.vx = d.vx * cp->hd.oBox.radii[0].vx + d.vy * cp->hd.oBox.radii[0].vy + d.vz * cp->hd.oBox.radii[0].vz;

	if (dist.vx < 0)
		dist.vx = -dist.vx;

	dist.vy = d.vx * cp->hd.oBox.radii[1].vx + d.vy * cp->hd.oBox.radii[1].vy + d.vz * cp->hd.oBox.radii[1].vz;
	if (dist.vy < 0)
		dist.vy = -dist.vy;

	dist.vz = d.vx * cp->hd.oBox.radii[2].vx + d.vy * cp->hd.oBox.radii[2].vy + d.vz * cp->hd.oBox.radii[2].vz;
	if (dist.vz < 0)
		dist.vz = -dist.vz;

	oboxLenSq = cp->hd.oBox.length[0];

	if (dist.vx < oboxLenSq * oboxLenSq)
	{
		oboxLenSq = cp->hd.oBox.length[1];

		if (dist.vy < oboxLenSq * oboxLenSq)
		{
			oboxLenSq = cp->hd.oBox.length[2];

			if (dist.vz < oboxLenSq * oboxLenSq)
				return;
		}
	}

	pos.vx -= camera_position.vx;
	pos.vy -= camera_position.vy;
	pos.vz -= camera_position.vz;

	Apply_Inv_CameraMatrix(&pos);

	num_cars_drawn++;

	MulMatrix0(&inv_camera_matrix, &cp->hd.drawCarMat, &workmatrix);

	// [A] there was mini cars cheat
	// we need full blown mini cars with physics support
	if (ActiveCheats.cheat13 != 0)
	{
		int i;
		for (i = 0; i < 3; i++)
		{
			workmatrix.m[i][0] >>= 1;
			workmatrix.m[i][1] >>= 1;
			workmatrix.m[i][2] >>= 1;
		}
	}

	// to check if car is flipped
	yVal = cp->hd.where.m[1][1];

	// LOD switching [A] Give player control over car LODs?
	if (pos.vz <= gCarLODDistance && gForceLowDetailCars == 0 || cp->controlType == CONTROL_TYPE_PLAYER)
	{
		int doSmoke = 0;

		WheelSpeed = cp->hd.speed * 8192;
		maxDamage = MaxPlayerDamage[0];

		if (cp->controlType == CONTROL_TYPE_PLAYER)
		{
			if(*cp->ai.padid >= 0 && *cp->ai.padid < 2)
				maxDamage = MaxPlayerDamage[*cp->ai.padid];
		}

		if (cp->totalDamage >= maxDamage)
		{
			if (WheelSpeed + 59999U < 119999)
				AddFlamingEngine(cp);

			doSmoke = 2;
		}
		else
		{
			if (cp->ap.damage[0] > 2000 || cp->ap.damage[1] > 2000)
			{
				if (cp->ap.damage[0] > 3000 || cp->ap.damage[1] > 3000)
					doSmoke = 2;
				else
					doSmoke = 1;
			}
		}

		if (doSmoke && WheelSpeed + 399999U < 1199999)
			AddSmokingEngine(cp, doSmoke - 1, WheelSpeed);

		AddExhaustSmoke(cp, doSmoke > 1, WheelSpeed);

		SetShadowPoints(cp, corners);
		PlaceShadowForCar(corners, 4, 10, yVal < 0 ? 0 : 2);

		ComputeCarLightingLevels(cp, 1);

		gTempCarUVPtr = gTempHDCarUVDump[cp->id];
		CarModelPtr = &NewCarModel[model];
		CarModelPtr->vlist = gTempCarVertDump[cp->id];
		CarModelPtr->nlist = gTempCarVertDump[cp->id];

		FindCarLightFade(&workmatrix);

		DrawCarObject(CarModelPtr, &workmatrix, &pos, cp->ap.palette, cp, 1);

		if (ActiveCheats.cheat13 != 0)
		{
			MulMatrix0(&inv_camera_matrix, &cp->hd.drawCarMat, &workmatrix);
		}

		DrawCarWheels(cp, &workmatrix, &pos, view);
	}
	else
	{
		CarModelPtr = &NewLowCarModel[model];
		CarModelPtr->nlist = gTempCarVertDump[cp->id];

		gTempCarUVPtr = gTempLDCarUVDump[cp->id];

		if (pos.vz < 8000)
		{
			SetShadowPoints(cp, corners);
			PlaceShadowForCar(corners, 0, 0, yVal < 0 ? 0 : 2);
		}

		ComputeCarLightingLevels(cp, 0);

		FindCarLightFade(&workmatrix);

		DrawCarObject(CarModelPtr, &workmatrix, &pos, cp->ap.palette, cp, 0);
	}

	TransparentObject = 0;

	if (cp->controlType == CONTROL_TYPE_PLAYER)
		PlayerCarFX(cp);
	else if (cp->controlType == CONTROL_TYPE_CIV_AI)
		CivCarFX(cp);

	if (gLightsOn && !lightsOnDelay[cp->id])
	{
		if (cp->controlType == CONTROL_TYPE_CIV_AI)
		{
			if (cp->ai.c.thrustState != 3 || (cp->ai.c.ctrlState != 5 && cp->ai.c.ctrlState != 7 && cp->ai.c.ctrlState != 8))
				AddNightLights(cp);
		}
		else if (SilenceThisCar(cp->id) == 0)
			AddNightLights(cp);
	}

	if(CarHasSiren(cp->ap.model))
	{
		if ((IS_ROADBLOCK_CAR(cp) || cp->controlType == CONTROL_TYPE_PURSUER_AI) ||		// any regular cop car including roadblock
			gInGameCutsceneActive && cp->controlType == CONTROL_TYPE_CUTSCENE && force_siren[CAR_INDEX(cp)] != 0 ||		// any car with siren in cutscene
			gCurrentMissionNumber == 26 && cp->controlType == CONTROL_TYPE_CUTSCENE && cp->ap.model == 4)				// Vegas ambulance
		{
			if (cp->ai.p.dying < 75)
				AddCopCarLight(cp);
		}
	}
}

// [D] [T]
char GetCarPalIndex(int tpage)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		if (tpage == carTpages[GameLevel][i])
			return i;
	}

	return 0;
}