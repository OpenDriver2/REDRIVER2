#include "DRIVER2.H"
#include "CARS.H"
#include "TEXTURE.H"
#include "OVERMAP.H"
#include "DRAW.H"
#include "MISSION.H"
#include "SYSTEM.H"
#include "DEBRIS.H"
#include "MAIN.H"
#include "CAMERA.H"
#include "HANDLING.H"
#include "COSMETIC.H"
#include "SHADOW.H"
#include "CIV_AI.H"
#include "MC_SND.H"
#include "GAMESND.H"
#include "PLAYERS.H"
#include "CUTSCENE.H"
#include "CONVERT.H"
#include "GLAUNCH.H"
#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"
#include "LIBAPI.H"

#ifndef PSX
#define CAR_LOD_SWITCH_DISTANCE switch_detail_distance
#else
#define CAR_LOD_SWITCH_DISTANCE 5500
#endif

MATRIX light_matrix =
{ { { 4096, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, { 0, 0, 0 } };

MATRIX colour_matrix =
{ { { 4032, 0, 0 }, { 3936, 0, 0 }, { 3520, 0, 0 } }, { 0, 0, 0 } };

// PHYSICS
CAR_DATA car_data[MAX_CARS + 2];	// all cars + Tanner cbox + Camera cbox

HUBCAP gHubcap;

// active cars
CAR_DATA* active_car_list[MAX_CARS];
BOUND_BOX bbox[MAX_CARS];
u_char lightsOnDelay[MAX_CARS];
u_short civ_clut[8][32][6];


// decompiled code
// original method signature: 
// void /*$ra*/ plotNewCarModel(CAR_MODEL *car /*$s0*/, int palette /*$s2*/)
 // line 834, offset 0x00020c94
	/* begin block 1 */
		// Start line: 835
		// Start offset: 0x00020C94
		// Variables:
	// 		plotCarGlobals _pg; // stack offset -72
	// 		SVECTOR v0; // stack offset -32
	// 		unsigned long lightlevel; // stack offset -24
	/* end block 1 */
	// End offset: 0x00020E88
	// End Line: 908

	/* begin block 2 */
		// Start line: 1668
	/* end block 2 */
	// End Line: 1669

	/* begin block 3 */
		// Start line: 1670
	/* end block 3 */
	// End Line: 1671

SVECTOR gTempCarVertDump[MAX_CARS][MAX_DENTING_VERTS];

DENTUVS *gTempCarUVPtr;
DENTUVS gTempHDCarUVDump[MAX_CARS][MAX_DENTING_UVS];
DENTUVS gTempLDCarUVDump[MAX_CARS][MAX_DENTING_LOD_UVS];

CAR_MODEL NewCarModel[MAX_CAR_MODELS];
CAR_MODEL NewLowCarModel[MAX_CAR_MODELS];

MODEL* gCarLowModelPtr[MAX_CAR_MODELS];
MODEL* gCarDamModelPtr[MAX_CAR_MODELS];
MODEL* gCarCleanModelPtr[MAX_CAR_MODELS];

int whichCP = 0;
int baseSpecCP = 0;
CAR_POLY carPolyBuffer[2001];

// [D] [T]
void plotNewCarModel(CAR_MODEL *car, int palette)
{
	plotCarGlobals _pg;
	u_int lightlevel;
	u_int underIntensity;
	SVECTOR v = { 0, -4096, 0 };

	lightlevel = combointensity | 0x3000000;

	if (car == NULL)
		return;

	if (gTimeOfDay > -1) 
	{
		if (gTimeOfDay < 3)
			lightlevel = combointensity | 0x30000000;
		else if (gTimeOfDay == 3)
			lightlevel = 0x302a2a2a;
	}

	setupLightingMatrices();

	gte_ldv0(&v);
	gte_ldrgb(&lightlevel);

	gte_nccs();

	_pg.primptr = (unsigned char*)current->primptr;
	_pg.intensity = 0;
	_pg.pciv_clut = (unsigned short *)&civ_clut[1];
	_pg.damageLevel = (unsigned char *)gTempCarUVPtr;

	_pg.ot = (OTTYPE *)(current->ot + 0x1c);

	gte_strgb(&underIntensity);

	// draw wheel arcs
	plotCarPolyB3(car->numB3, car->pB3, car->vlist, &_pg);
	_pg.intensity = underIntensity & 0xffffff;

	// draw car bottom
	_pg.ot = (OTTYPE *)(current->ot + 16);
	plotCarPolyFT3(car->numFT3, car->pFT3, car->vlist, &_pg);

	// draw car body
	_pg.ot = (OTTYPE *)(current->ot + 4);
	if (gTimeOfDay == 3)
	{
		_pg.intensity = (combointensity & 0xfcfcf0U) >> 2;
		plotCarPolyGT3nolight(car->numGT3, car->pGT3, car->vlist, &_pg, palette);	
	}
	else
	{
		_pg.intensity = combointensity & 0xffffff;
		plotCarPolyGT3(car->numGT3, car->pGT3, car->vlist, car->nlist, &_pg, palette);
	}

	current->primptr = (char*)_pg.primptr;

	restoreLightingMatrices();
}



// decompiled code
// original method signature: 
// void /*$ra*/ plotCarPolyB3(int numTris /*$a0*/, CAR_POLY *src /*$a1*/, SVECTOR *vlist /*$a2*/, plotCarGlobals *pg /*$a3*/)
 // line 917, offset 0x000237b8
	/* begin block 1 */
		// Start line: 918
		// Start offset: 0x000237B8
		// Variables:
	// 		POLY_F3 *prim; // $t0
	// 		int i; // $t1
	// 		long *ot; // $t3
	// 		long F3rgb; // $t4

		/* begin block 1.1 */
			// Start line: 927
			// Start offset: 0x000237E0
			// Variables:
		// 		int reg; // stack offset -8
		/* end block 1.1 */
		// End offset: 0x000238AC
		// End Line: 967
	/* end block 1 */
	// End offset: 0x000238C4
	// End Line: 970

	/* begin block 2 */
		// Start line: 1834
	/* end block 2 */
	// End Line: 1835

	/* begin block 3 */
		// Start line: 6230
	/* end block 3 */
	// End Line: 6231

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
			*(uint*)&prim->r0 = FT3rgb | 0x20000000;

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



// decompiled code
// original method signature: 
// void /*$ra*/ plotCarPolyFT3(int numTris /*$a0*/, CAR_POLY *src /*$t1*/, SVECTOR *vlist /*$t4*/, plotCarGlobals *pg /*$t5*/)
 // line 976, offset 0x000238c4
	/* begin block 1 */
		// Start line: 977
		// Start offset: 0x000238C4
		// Variables:
	// 		POLY_FT3 *prim; // $t0
	// 		long *ot; // $t6
	// 		long FT3rgb; // stack offset -8
	// 		int i; // $t2

		/* begin block 1.1 */
			// Start line: 992
			// Start offset: 0x00023904
			// Variables:
		// 		int reg; // stack offset -4
		// 		int clut_uv0; // $a2
		// 		int tpage_uv1; // $a3
		// 		int uv3_uv2; // $a1

			/* begin block 1.1.1 */
				// Start line: 998
				// Start offset: 0x00023904
				// Variables:
			// 		int ofse; // $v1
			/* end block 1.1.1 */
			// End offset: 0x00023904
			// End Line: 998
		/* end block 1.1 */
		// End offset: 0x00023A08
		// End Line: 1052
	/* end block 1 */
	// End offset: 0x00023A20
	// End Line: 1055

	/* begin block 2 */
		// Start line: 6385
	/* end block 2 */
	// End Line: 6386

	/* begin block 3 */
		// Start line: 6392
	/* end block 3 */
	// End Line: 6393

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
			*(uint*)&prim->r0 = FT3rgb;
			*(uint*)&prim->u0 = src->clut_uv0 + ofse;
			*(uint*)&prim->u1 = src->tpage_uv1 + ofse;
			*(uint*)&prim->u2 = src->uv3_uv2 + ofse;

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



// decompiled code
// original method signature: 
// void /*$ra*/ plotCarPolyGT3(int numTris /*$a0*/, CAR_POLY *src /*$t1*/, SVECTOR *vlist /*$s0*/, SVECTOR *nlist /*$a3*/, plotCarGlobals *pg /*stack 16*/, int palette /*stack 20*/)
 // line 1125, offset 0x00020ea0
	/* begin block 1 */
		// Start line: 1126
		// Start offset: 0x00020EA0
		// Variables:
	// 		POLY_GT3 *prim; // $t0
	// 		long *ot; // $s1
	// 		long GT3rgb; // stack offset -24
	// 		int i; // $t7
	// 		int v0; // $t3
	// 		int v1; // $t4
	// 		int v2; // $t2
	// 		int n0; // $t3
	// 		int n1; // $a2
	// 		int n2; // $a0
	// 		int r0; // stack offset -20
	// 		int r1; // stack offset -16
	// 		int r2; // $v0
	// 		int reg; // $a0
	// 		int clut_uv0; // $a1
	// 		int tpage_uv1; // $t6
	// 		int uv3_uv2; // $t5
	// 		unsigned short *clut_base; // $t9

		/* begin block 1.1 */
			// Start line: 1126
			// Start offset: 0x00020EA0
			// Variables:
		// 		int ofse; // $v1
		/* end block 1.1 */
		// End offset: 0x00020EA0
		// End Line: 1126

		/* begin block 1.2 */
			// Start line: 1231
			// Start offset: 0x00021040
			// Variables:
		// 		int ofse; // $v1
		/* end block 1.2 */
		// End offset: 0x00021040
		// End Line: 1231
	/* end block 1 */
	// End offset: 0x000210B8
	// End Line: 1251

	/* begin block 2 */
		// Start line: 2294
	/* end block 2 */
	// End Line: 2295

// [D] [T]
void plotCarPolyGT3(int numTris, CAR_POLY *src, SVECTOR *vlist, SVECTOR *nlist, plotCarGlobals *pg, int palette)
{
	int Z;
	int otz;	
	SVECTOR* v2;
	SVECTOR *v1;
	SVECTOR *v0;
	uint indices;
	POLY_GT3 *prim;
	uint r0,r1,r2;
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

			r0 = (uint)(ushort)nlist[indices & 0xff].pad;
			r1 = (uint)(ushort)nlist[indices >> 8 & 0xff].pad;
			r2 = (uint)(ushort)nlist[indices >> 16 & 0xff].pad;

			*(uint*)&prim->r0 = (r0 & 0xff) << 0x10 | r0;
			*(uint*)&prim->r1 = (r1 & 0xff) << 0x10 | r1;
			*(uint*)&prim->r2 = (r2 & 0xff) << 0x10 | r2;

			ofse = pg->damageLevel[src->originalindex];

			*(uint*)&prim->u0 = (src->clut_uv0 & 0xffffU | pg->pciv_clut[palette + (src->clut_uv0 >> 0x10)] << 0x10) + ofse;
			*(uint*)&prim->u1 = src->tpage_uv1 + ofse;
			*(uint*)&prim->u2 = src->uv3_uv2 + ofse;

			gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);

			setPolyGT3(prim);
			addPrim(pg->ot + (otz >> 1), prim);

			prim++;
		}

		src++;
		numTris--;
	}

	pg->primptr = (unsigned char*)prim;
}



// decompiled code
// original method signature: 
// void /*$ra*/ plotCarPolyGT3nolight(int numTris /*$a0*/, CAR_POLY *src /*$t3*/, SVECTOR *vlist /*$t6*/, plotCarGlobals *pg /*$a3*/, int palette /*stack 16*/)
 // line 1349, offset 0x00023a20
	/* begin block 1 */
		// Start line: 1350
		// Start offset: 0x00023A20
		// Variables:
	// 		POLY_FT3 *prim; // $t0
	// 		long *ot; // $t7
	// 		long GT3rgb; // stack offset -8
	// 		int i; // $t4
	// 		unsigned short *clut_base; // $t8

		/* begin block 1.1 */
			// Start line: 1366
			// Start offset: 0x00023A68
			// Variables:
		// 		int reg; // stack offset -4
		// 		int clut_uv0; // $a0
		// 		int tpage_uv1; // $t1
		// 		int uv3_uv2; // $t2

			/* begin block 1.1.1 */
				// Start line: 1371
				// Start offset: 0x00023A68
				// Variables:
			// 		int ofse; // $v1
			/* end block 1.1.1 */
			// End offset: 0x00023A68
			// End Line: 1371
		/* end block 1.1 */
		// End offset: 0x00023B94
		// End Line: 1425
	/* end block 1 */
	// End offset: 0x00023BAC
	// End Line: 1428

	/* begin block 2 */
		// Start line: 6934
	/* end block 2 */
	// End Line: 6935

	/* begin block 3 */
		// Start line: 7229
	/* end block 3 */
	// End Line: 7230

// [D] [T]
void plotCarPolyGT3nolight(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg, int palette)
{
	int Z;
	int otz;
	SVECTOR* v2;
	SVECTOR* v1;
	SVECTOR* v0;
	uint indices;
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
			*(uint*)&prim->r0 = GT3rgb;

			ofse = pg->damageLevel[src->originalindex];

			*(uint*)&prim->u0 = (src->clut_uv0 & 0xffffU | pg->pciv_clut[palette + (src->clut_uv0 >> 0x10)] << 0x10) + ofse;
			*(uint*)&prim->u1 = src->tpage_uv1 + ofse;
			*(uint*)&prim->u2 = src->uv3_uv2 + ofse;

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



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCar(CAR_DATA *cp /*$s3*/, int view /*$a1*/)
 // line 1442, offset 0x000210b8
	/* begin block 1 */
		// Start line: 1443
		// Start offset: 0x000210B8
		// Variables:
	// 		int WheelSpeed; // $s0
	// 		int model; // $fp
	// 		PLAYER *lp; // $a2

		/* begin block 1.1 */
			// Start line: 1454
			// Start offset: 0x00021174
			// Variables:
		// 		CVECTOR col; // stack offset -312
		/* end block 1.1 */
		// End offset: 0x00021244
		// End Line: 1492

		/* begin block 1.2 */
			// Start line: 1496
			// Start offset: 0x00021244
			// Variables:
		// 		MATRIX temp_mat1; // stack offset -304
		// 		MATRIX temp_mat2; // stack offset -272
		// 		MATRIX final_mat; // stack offset -240
		// 		VECTOR pos; // stack offset -208
		// 		VECTOR pos1; // stack offset -192
		// 		SVECTOR temp_vec; // stack offset -176
		// 		int result; // $s4

			/* begin block 1.2.1 */
				// Start line: 1519
				// Start offset: 0x00021290
				// Variables:
			// 		VECTOR corners[4]; // stack offset -168
			/* end block 1.2.1 */
			// End offset: 0x00021384
			// End Line: 1538

			/* begin block 1.2.2 */
				// Start line: 1542
				// Start offset: 0x00021384
				// Variables:
			// 		VECTOR d; // stack offset -104
			// 		VECTOR dist; // stack offset -88
			/* end block 1.2.2 */
			// End offset: 0x000214D8
			// End Line: 1559

			/* begin block 1.2.3 */
				// Start line: 1610
				// Start offset: 0x0002154C
				// Variables:
			// 		int i; // $a0
			/* end block 1.2.3 */
			// End offset: 0x00021570
			// End Line: 1615

			/* begin block 1.2.4 */
				// Start line: 1627
				// Start offset: 0x000215A4
				// Variables:
			// 		MATRIX workmatrix; // stack offset -104
			// 		CAR_MODEL *CarModelPtr; // $s1

				/* begin block 1.2.4.1 */
					// Start line: 1635
					// Start offset: 0x00021604
				/* end block 1.2.4.1 */
				// End offset: 0x00021620
				// End Line: 1637
			/* end block 1.2.4 */
			// End offset: 0x00021620
			// End Line: 1639

			/* begin block 1.2.5 */
				// Start line: 1650
				// Start offset: 0x00021674
				// Variables:
			// 		int damage; // $v1

				/* begin block 1.2.5.1 */
					// Start line: 1706
					// Start offset: 0x000217BC
					// Variables:
				// 		CAR_MODEL *CarModelPtr; // $s0

					/* begin block 1.2.5.1.1 */
						// Start line: 1706
						// Start offset: 0x000217BC
						// Variables:
					// 		MATRIX workmatrix; // stack offset -72
					/* end block 1.2.5.1.1 */
					// End offset: 0x000218BC
					// End Line: 1735
				/* end block 1.2.5.1 */
				// End offset: 0x000218BC
				// End Line: 1736
			/* end block 1.2.5 */
			// End offset: 0x000218BC
			// End Line: 1737

			/* begin block 1.2.6 */
				// Start line: 1756
				// Start offset: 0x0002191C
			/* end block 1.2.6 */
			// End offset: 0x00021984
			// End Line: 1764
		/* end block 1.2 */
		// End offset: 0x00021AC8
		// End Line: 1788
	/* end block 1 */
	// End offset: 0x00021AC8
	// End Line: 1789

	/* begin block 2 */
		// Start line: 2921
	/* end block 2 */
	// End Line: 2922

	/* begin block 3 */
		// Start line: 3113
	/* end block 3 */
	// End Line: 3114

char LeftLight = 0;
char RightLight = 0;
char TransparentObject = 0;

// [D] [T] [A]
void DrawCar(CAR_DATA *cp, int view)
{
	int yVal;
	int maxDamage;
	int WheelSpeed;
	int oboxLenSq;
	CAR_MODEL* CarModelPtr;
	int model;
	CVECTOR col;
	VECTOR pos;
	VECTOR corners[4];
	VECTOR d;
	VECTOR dist;
	MATRIX workmatrix;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

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
		else if(cp->ap.damage[1] < 1000)
			RightLight = 1;
		else
			RightLight = 0;

		if (gLightsOn == 0) 
			return;

		if (lightsOnDelay[cp->id] != 0) 
			return;

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

	dist.vz = d.vx * cp->hd.oBox.radii[2].vx + d.vy * cp->hd.oBox.radii[2].vy +d.vz * cp->hd.oBox.radii[2].vz;
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
	
	// LOD switching
	if (pos.vz <= CAR_LOD_SWITCH_DISTANCE && gForceLowDetailCars == 0 || cp->controlType == CONTROL_TYPE_PLAYER) 
	{
		int doSmoke = 0;

		WheelSpeed = cp->hd.speed * 0x2000;
		maxDamage = MaxPlayerDamage[0];

		if (cp->controlType == CONTROL_TYPE_PLAYER)
		{
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

		//gTimeInWater = 25;
		//gSinkingTimer = 100;

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
	
	if (gLightsOn != 0 && lightsOnDelay[cp->id] == 0)
	{
		if (cp->controlType == CONTROL_TYPE_CIV_AI)
		{
			if(cp->ai.c.thrustState != 3 || (cp->ai.c.ctrlState != 5 && cp->ai.c.ctrlState != 7 && cp->ai.c.ctrlState != 8))
				AddNightLights(cp);
		}
		else if (SilenceThisCar(cp->id) == 0)
			AddNightLights(cp);
	}

	if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
	{
		if (MissionHeader->residentModels[3] == 0)
		{
			if (cp->ai.p.dying < 75)
				AddCopCarLight(cp);

			return;
		}
	}
	
	// optimzed check for hndType, controlType, controlFlags
	if (!IS_ROADBLOCK_CAR(cp) && (gInGameCutsceneActive == 0 || cp->controlType != CONTROL_TYPE_CUTSCENE || force_siren[CAR_INDEX(cp)] == 0 ))
	{
		if (gCurrentMissionNumber != 26 || cp->ap.model != 4 || cp->controlType != CONTROL_TYPE_CUTSCENE)
			return;
	}

	if (cp->ai.p.dying < 75)
		AddCopCarLight(cp);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCarObject(CAR_MODEL *car /*$s0*/, MATRIX *matrix /*$a1*/, VECTOR *pos /*$a2*/, VECTOR *pos1 /*$a3*/, int palette /*stack 16*/, CAR_DATA *cp /*stack 20*/, int detail /*stack 24*/)
 // line 1793, offset 0x000233dc
	/* begin block 1 */
		// Start line: 1794
		// Start offset: 0x000233DC

		/* begin block 1.1 */
			// Start line: 1794
			// Start offset: 0x000233DC
			// Variables:
		// 		SVECTOR cog; // stack offset -40
		// 		VECTOR modelLocation; // stack offset -32
		/* end block 1.1 */
		// End offset: 0x000233DC
		// End Line: 1794

		/* begin block 1.2 */
			// Start line: 1794
			// Start offset: 0x000233DC
			// Variables:
		// 		static unsigned long savedSP; // offset 0x0
		/* end block 1.2 */
		// End offset: 0x000234DC
		// End Line: 1833
	/* end block 1 */
	// End offset: 0x000234DC
	// End Line: 1836

	/* begin block 2 */
		// Start line: 3586
	/* end block 2 */
	// End Line: 3587

// [D] [T]
void DrawCarObject(CAR_MODEL *car, MATRIX *matrix, VECTOR *pos, int palette, CAR_DATA *cp, int detail)
{
	static unsigned long savedSP;

	VECTOR modelLocation;
	SVECTOR cog;

	cog = cp->ap.carCos->cog;

	gte_SetRotMatrix(matrix);
	gte_SetTransVector(pos);

	gte_ldv0(&cog);

	gte_rtv0tr();

	gte_stlvnl(&modelLocation);

	gte_SetTransVector(&modelLocation);

	savedSP = SetSp(0x1f800308);

	plotNewCarModel(car, palette);

	SetSp(savedSP);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCarWheels(CAR_DATA *cp /*$fp*/, MATRIX *RearMatrix /*stack 4*/, VECTOR *pos /*stack 8*/, int zclip /*$a3*/)
 // line 1850, offset 0x00021af8
	/* begin block 1 */
		// Start line: 1851
		// Start offset: 0x00021AF8
		// Variables:
	// 		CAR_COSMETICS *car_cos; // $s0
	// 		MATRIX FrontMatrix; // stack offset -144
	// 		MODEL *WheelModel; // $s0
	// 		MODEL *WheelModelBack; // stack offset -56
	// 		MODEL *WheelModelFront; // stack offset -52
	// 		int i; // $s4
	// 		static short FrontWheelRotation[20]; // offset 0x0
	// 		static short BackWheelRotation[20]; // offset 0x30
	// 		short model; // $a0
	// 		short wheelSize; // $s2

		/* begin block 1.1 */
			// Start line: 1866
			// Start offset: 0x00021BA8
			// Variables:
		// 		int FrontWheelIncrement; // $a3
		// 		int BackWheelIncrement; // $t0
		/* end block 1.1 */
		// End offset: 0x00021CD0
		// End Line: 1919

		/* begin block 1.2 */
			// Start line: 1922
			// Start offset: 0x00021CD0
			// Variables:
		// 		int c; // $t2
		// 		int s; // $t3
		// 		int FW1z; // $v0
		// 		int FW2z; // $a0
		// 		int BW1z; // $v0
		// 		int BW2z; // $a3
		// 		SVECTOR *VertPtr; // $t6
		/* end block 1.2 */
		// End offset: 0x00021CD0
		// End Line: 1926

		/* begin block 1.3 */
			// Start line: 1926
			// Start offset: 0x00021CD0
			// Variables:
		// 		MATRIX SteerMatrix; // stack offset -112
		/* end block 1.3 */
		// End offset: 0x00021CD0
		// End Line: 1926

		/* begin block 1.4 */
			// Start line: 1988
			// Start offset: 0x00021FA4
			// Variables:
		// 		SVECTOR *verts; // $s5

			/* begin block 1.4.1 */
				// Start line: 2007
				// Start offset: 0x00021FF8
				// Variables:
			// 		VECTOR WheelPos; // stack offset -80
			// 		SVECTOR sWheelPos; // stack offset -64
			/* end block 1.4.1 */
			// End offset: 0x00022028
			// End Line: 2012
		/* end block 1.4 */
		// End offset: 0x00022118
		// End Line: 2044
	/* end block 1 */
	// End offset: 0x00022180
	// End Line: 2046

	/* begin block 2 */
		// Start line: 4181
	/* end block 2 */
	// End Line: 4182

	/* begin block 3 */
		// Start line: 4192
	/* end block 3 */
	// End Line: 4193

MODEL *gHubcapModelPtr;
MODEL *gCleanWheelModelPtr;
MODEL *gFastWheelModelPtr;
MODEL *gDamWheelModelPtr;

short FrontWheelRotation[MAX_CARS]; // offset 0x0
short BackWheelRotation[MAX_CARS]; // offset 0x30

// [D] [T]
void DrawCarWheels(CAR_DATA *cp, MATRIX *RearMatrix, VECTOR *pos, int zclip)
{
	short wheelSize;
	int FW1z;
	int FW2z;
	int BW1z;
	int BW2z;
	int FrontWheelIncrement;
	int BackWheelIncrement;
	int sizeScale;
	int wheelnum;
	SVECTOR* VertPtr;
	MODEL* model;
	SVECTOR* wheelDisp;
	WHEEL* wheel;
	int car_id;
	MATRIX FrontMatrix;
	MATRIX SteerMatrix;
	VECTOR WheelPos;
	SVECTOR sWheelPos;
	MODEL *WheelModelBack;
	MODEL *WheelModelFront;

	if (cp < car_data) 
	{
		while (FrameCnt != 0x78654321) 
		{
			trap(0x400);
		}
	}

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

	FW1z = FIXEDH(rcossin_tbl[(FrontWheelRotation[car_id] & 0xfff) * 2] * sizeScale);
	FW2z = FIXEDH(rcossin_tbl[(FrontWheelRotation[car_id] & 0xfff) * 2 + 1] * sizeScale);

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

	BW1z = FIXEDH(rcossin_tbl[(BackWheelRotation[car_id] & 0xfff) * 2] * sizeScale);
	BW2z = FIXEDH(rcossin_tbl[(BackWheelRotation[car_id] & 0xfff) * 2 + 1] * sizeScale);

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

	SteerMatrix.m[0][0] = rcossin_tbl[(cp->wheel_angle & 0xfff) * 2 + 1];
	SteerMatrix.m[0][2] = rcossin_tbl[(cp->wheel_angle & 0xfff) * 2];
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



// decompiled code
// original method signature: 
// void /*$ra*/ DrawWheelObject(MODEL *model /*$t2*/, SVECTOR *verts /*$t4*/, int transparent /*$a2*/, int wheelnum /*$a3*/)
 // line 2058, offset 0x00022180
	/* begin block 1 */
		// Start line: 2059
		// Start offset: 0x00022180
		// Variables:
	// 		POLY_FT4 *prims; // $t0
	// 		POLYFT4LIT *src; // $t1
	// 		int i; // $t2
	// 		int Z; // stack offset -4
	// 		int clut; // $t8
	// 		int tpage; // $t7
	// 		unsigned long bright; // $t6
	// 		unsigned long dim; // $t5

		/* begin block 1.1 */
			// Start line: 2093
			// Start offset: 0x00022298
			// Variables:
		// 		int flag1; // stack offset -8
		// 		long vl; // $a0

			/* begin block 1.1.1 */
				// Start line: 2111
				// Start offset: 0x00022348
				// Variables:
			// 		int r2; // $v1
			/* end block 1.1.1 */
			// End offset: 0x00022348
			// End Line: 2111
		/* end block 1.1 */
		// End offset: 0x00022430
		// End Line: 2141
	/* end block 1 */
	// End offset: 0x00022458
	// End Line: 2143

	/* begin block 2 */
		// Start line: 5075
	/* end block 2 */
	// End Line: 5076

	/* begin block 3 */
		// Start line: 5088
	/* end block 3 */
	// End Line: 5089

// [D] [T]
void DrawWheelObject(MODEL *model, SVECTOR *verts, int transparent, int wheelnum)
{
	ushort clut;
	ushort tpage;
	int i;
	int Z;
	int otZ;
	int combo;
	POLY_FT4 *poly;
	POLYFT4 *src;
	u_int dim;
	u_int bright;

	src = (POLYFT4*)model->poly_block;
	poly = (POLY_FT4 *)current->primptr;

	clut = texture_cluts[src->texture_set][src->texture_id];
	tpage = texture_pages[src->texture_set];

	if (gTimeOfDay > -1) 
	{
		if (gTimeOfDay < 3) 
		{
			bright = combointensity & 0xffffffU | 0x2c000000;
			dim = (combointensity & 0xfcfcfcU) >> 2 | 0x2c000000;
		}
		else if (gTimeOfDay == 3)
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
				*(uint *)&poly->r0 = 0x2c000000;
			else if (((i ^ wheelnum >> 1) & 1) == 0)
				*(uint *)&poly->r0 = dim;
			else
				*(uint *)&poly->r0 = bright;

			setSemiTrans(poly, transparent);

			gte_stsxy3(&poly->x1, &poly->x3, &poly->x2);

			poly->u0 = src->uv0.u;
			poly->v0 = src->uv0.v;
			poly->clut = clut;

			poly->u1 = src->uv1.u;
			poly->v1 = src->uv1.v;
			poly->tpage = tpage | 0x20;

			poly->u2 = src->uv3.u;
			poly->v2 = src->uv3.v;

			poly->u3 = src->uv2.u;
			poly->v3 = src->uv2.v;

			poly++;
		}
		src++;
	}
	current->primptr = (char*)poly;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlayerCarFX(CAR_DATA *cp /*$s0*/)
 // line 2152, offset 0x000234dc
	/* begin block 1 */
		// Start line: 2153
		// Start offset: 0x000234DC
		// Variables:
	// 		int WheelSpeed; // $s1
	/* end block 1 */
	// End offset: 0x000235F8
	// End Line: 2191

	/* begin block 2 */
		// Start line: 6600
	/* end block 2 */
	// End Line: 6601

	/* begin block 3 */
		// Start line: 6603
	/* end block 3 */
	// End Line: 6604

	/* begin block 4 */
		// Start line: 6920
	/* end block 4 */
	// End Line: 6921

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



// decompiled code
// original method signature: 
// void /*$ra*/ ComputeCarLightingLevels(CAR_DATA *cp /*$s1*/, char detail /*$s3*/)
 // line 2198, offset 0x00022458
	/* begin block 1 */
		// Start line: 2199
		// Start offset: 0x00022458
		// Variables:
	// 		int light; // $s2
	// 		SVECTOR lightsourcevector; // stack offset -96
	// 		SVECTOR colour; // stack offset -88
	// 		VECTOR lightValues; // stack offset -80
	// 		VECTOR *orient; // $s0

		/* begin block 1.1 */
			// Start line: 2270
			// Start offset: 0x0002270C
			// Variables:
		// 		MODEL *model; // $v1
		// 		SVECTOR *norms; // $a3
		// 		SVECTOR *ppads; // $a2
		// 		int num_norms; // $a1
		// 		int count; // $a1
		// 		CVECTOR c0; // stack offset -64
		// 		CVECTOR c1; // stack offset -56
		// 		CVECTOR c2; // stack offset -48

			/* begin block 1.1.1 */
				// Start line: 2276
				// Start offset: 0x0002270C
				// Variables:
			// 		long GT3rgb; // stack offset -40
			/* end block 1.1.1 */
			// End offset: 0x0002270C
			// End Line: 2276
		/* end block 1.1 */
		// End offset: 0x00022834
		// End Line: 2312
	/* end block 1 */
	// End offset: 0x00022860
	// End Line: 2316

	/* begin block 2 */
		// Start line: 5387
	/* end block 2 */
	// End Line: 5388

	/* begin block 3 */
		// Start line: 5443
	/* end block 3 */
	// End Line: 5444

	/* begin block 4 */
		// Start line: 5453
	/* end block 4 */
	// End Line: 5454

/* WARNING: Could not reconcile some variable overlaps */


// [D] [T]
void ComputeCarLightingLevels(CAR_DATA *cp, char detail)
{
	MATRIX scratchPadMat; // 0x1f800344

	int doLight;
	int orW;
	int orY;
	MODEL *model;
	int num_norms;
	int count;
	SVECTOR *ppads;
	SVECTOR *norms;
	SVECTOR lightsourcevector;
	SVECTOR colour;
	VECTOR lightValues;
	CVECTOR c0;
	CVECTOR c1;
	CVECTOR c2;
	int GT3rgb;

	if (gTimeOfDay > -1)
	{
		if (gTimeOfDay < 3)
		{
			lightsourcevector = day_vectors[GameLevel];
			colour = day_colours[GameLevel];
		}
		else if (gTimeOfDay == 3)
		{
			lightsourcevector = night_vectors[GameLevel];
			colour = night_colours[GameLevel];
		}
	}

	InvertMatrix(&cp->hd.where, &scratchPadMat);
	SetRotMatrix(&scratchPadMat);

	gte_ldv0(&lightsourcevector);
	gte_rtv0();

	gte_stsv(light_matrix.m[0]);

	doLight = 0;

	colour_matrix.m[0][0] = colour.vx;
	colour_matrix.m[1][0] = colour.vy;
	colour_matrix.m[2][0] = colour.vz;

	if (gTimeOfDay != 3)
	{
		orY = cp->st.n.orientation[1] - cp->ap.qy;

		if (orY < 1) 
			orY = cp->ap.qy - cp->st.n.orientation[1];

		orW = cp->st.n.orientation[3] - cp->ap.qw;

		if (orW < 1) 
			orW = cp->ap.qw - cp->st.n.orientation[3];

		if ((200 < orY + orW) || (cp->lowDetail != (detail | lightning)))
			doLight = 1;

		if ((gTimeOfDay == 0 || gTimeOfDay == 2) && (cp->id & 0xf) == (CameraCnt & 0xfU)) 
			doLight = 1;

		setupLightingMatrices();

		if (doLight) 
		{
			uint rgbval = combointensity & 0xffffffU | 0x34000000;
			gte_ldrgb(&rgbval);

			cp->ap.qy = cp->st.n.orientation[1];
			cp->ap.qw = cp->st.n.orientation[3];
			cp->lowDetail = detail | lightning;

			if (detail == 0) 
				model = gCarLowModelPtr[cp->ap.model];
			else 
				model = gCarCleanModelPtr[cp->ap.model];

			num_norms = model->num_point_normals / 3;
			norms = (SVECTOR *)model->point_normals;

			ppads = gTempCarVertDump[cp->id];
			count = num_norms +1;

			while (count >= 0)
			{
				gte_ldv3(&norms[0], &norms[1], &norms[2]);

				gte_ncct();

				gte_strgb3(&c0,&c1,&c2);

				ppads[0].pad = *(short*)&c0;
				ppads[1].pad = *(short*)&c1;
				ppads[2].pad = *(short*)&c2;

				count--;
				norms += 3;
				ppads += 3;

			}
		}

		restoreLightingMatrices();
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ buildNewCars()
 // line 2321, offset 0x00022860
	/* begin block 1 */
		// Start line: 5768
	/* end block 1 */
	// End Line: 5769

	/* begin block 2 */
		// Start line: 5774
	/* end block 2 */
	// End Line: 5775

	/* begin block 3 */
		// Start line: 5785
	/* end block 3 */
	// End Line: 5786

/* WARNING: Unknown calling convention yet parameter storage is locked */

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



// decompiled code
// original method signature: 
// void /*$ra*/ buildNewCarFromModel(CAR_MODEL *car /*$s5*/, MODEL *model /*$s7*/, int first /*$a2*/)
 // line 2357, offset 0x00022960
	/* begin block 1 */
		// Start line: 2358
		// Start offset: 0x00022960
		// Variables:
	// 		char *polylist; // $s0
	// 		int i; // $s2
	// 		int j; // $s3
	// 		int pass; // $s4

		/* begin block 1.1 */
			// Start line: 2394
			// Start offset: 0x00022A9C
			// Variables:
		// 		CAR_POLY *p; // $s1
		// 		char ptype; // $s6

			/* begin block 1.1.1 */
				// Start line: 2403
				// Start offset: 0x00022AE4
			/* end block 1.1.1 */
			// End offset: 0x00022AE4
			// End Line: 2405

			/* begin block 1.1.2 */
				// Start line: 2408
				// Start offset: 0x00022AE4
			/* end block 1.1.2 */
			// End offset: 0x00022AE4
			// End Line: 2410

			/* begin block 1.1.3 */
				// Start line: 2414
				// Start offset: 0x00022AE4
			/* end block 1.1.3 */
			// End offset: 0x00022AE4
			// End Line: 2416

			/* begin block 1.1.4 */
				// Start line: 2419
				// Start offset: 0x00022AE4
			/* end block 1.1.4 */
			// End offset: 0x00022AE4
			// End Line: 2421

			/* begin block 1.1.5 */
				// Start line: 2426
				// Start offset: 0x00022AE4
			/* end block 1.1.5 */
			// End offset: 0x00022AE4
			// End Line: 2434

			/* begin block 1.1.6 */
				// Start line: 2437
				// Start offset: 0x00022AE4
			/* end block 1.1.6 */
			// End offset: 0x00022AE4
			// End Line: 2449

			/* begin block 1.1.7 */
				// Start line: 2453
				// Start offset: 0x00022AE4
			/* end block 1.1.7 */
			// End offset: 0x00022B1C
			// End Line: 2461

			/* begin block 1.1.8 */
				// Start line: 2464
				// Start offset: 0x00022B1C
			/* end block 1.1.8 */
			// End offset: 0x00022B7C
			// End Line: 2476

			/* begin block 1.1.9 */
				// Start line: 2480
				// Start offset: 0x00022B7C
			/* end block 1.1.9 */
			// End offset: 0x00022B7C
			// End Line: 2482

			/* begin block 1.1.10 */
				// Start line: 2486
				// Start offset: 0x00022B7C
			/* end block 1.1.10 */
			// End offset: 0x00022B7C
			// End Line: 2488

			/* begin block 1.1.11 */
				// Start line: 2492
				// Start offset: 0x00022B7C
			/* end block 1.1.11 */
			// End offset: 0x00022C10
			// End Line: 2504

			/* begin block 1.1.12 */
				// Start line: 2507
				// Start offset: 0x00022C10
			/* end block 1.1.12 */
			// End offset: 0x00022D24
			// End Line: 2526

			/* begin block 1.1.13 */
				// Start line: 2530
				// Start offset: 0x00022D24
			/* end block 1.1.13 */
			// End offset: 0x00022E2C
			// End Line: 2548

			/* begin block 1.1.14 */
				// Start line: 2551
				// Start offset: 0x00022E2C
			/* end block 1.1.14 */
			// End offset: 0x00022FDC
			// End Line: 2579
		/* end block 1.1 */
		// End offset: 0x00022FDC
		// End Line: 2582
	/* end block 1 */
	// End offset: 0x00023098
	// End Line: 2593

	/* begin block 2 */
		// Start line: 5848
	/* end block 2 */
	// End Line: 5849

// [D] [T]
void buildNewCarFromModel(CAR_MODEL *car, MODEL *model, int first)
{
	unsigned char ptype;
	unsigned char clut;
	unsigned char *polyList;
	CAR_POLY *cp;

	int newNumPolys;

	int i;
	int pass;

	if (first != 0) 
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

		pass = 0;

		do {
			
			polyList = (unsigned char *)model->poly_block;

			if (pass == 1)
				car->pFT3 = carPolyBuffer + whichCP;
			else if (pass == 0)
				car->pGT3 = carPolyBuffer + whichCP;
			else if (pass == 2)
				car->pB3 = carPolyBuffer + whichCP;

			i = 0;
			newNumPolys = whichCP;

			while (newNumPolys < 2000 && i < model->num_polys)
			{
				ptype = *polyList;

				cp = carPolyBuffer + newNumPolys;

				switch (ptype & 0x1f) 
				{
					case 0:
					case 18:
						if (pass == 2)	// F3
						{
							cp->vindices = (uint)polyList[1] | ((uint)polyList[2] | (uint)polyList[3] << 8) << 8;
							cp->originalindex = i;

							newNumPolys++;
						}
						break;
					case 1:
					case 19:
						if (pass == 2)	// F4
						{
							cp->vindices = (uint)polyList[4] | ((uint)polyList[5] | (uint)polyList[6] << 8) << 8;
							cp->originalindex = i;

							cp = carPolyBuffer + newNumPolys + 1;

							cp->vindices = (uint)polyList[4] | ((uint)polyList[6] | (uint)polyList[7] << 8) << 8;
							cp->originalindex = i;

							newNumPolys += 2;
						}
						break;
					case 20:
						if (pass == 1)	// FT3
						{
							POLYFT3* pft3 = (POLYFT3*)polyList;
									
							cp->vindices = pft3->v0 | (pft3->v1 | pft3->v2 << 8) << 8;
							cp->clut_uv0 = SW_INT(texture_cluts[pft3->texture_set][pft3->texture_id], *(ushort*)&pft3->uv0);
							cp->tpage_uv1 = SW_INT(texture_pages[pft3->texture_set], *(ushort*)&pft3->uv1);
							cp->uv3_uv2 = *(ushort*)&pft3->uv2;
							cp->originalindex = i;

							newNumPolys++;
						}
						break;
					case 21:
						if (pass == 1)	// FT4
						{
							POLYFT4* pft4 = (POLYFT4*)polyList;

							cp->vindices = pft4->v0 | (pft4->v1 | pft4->v2 << 8) << 8;
							cp->clut_uv0 = SW_INT(texture_cluts[pft4->texture_set][pft4->texture_id], *(ushort *)&pft4->uv0);
							cp->tpage_uv1 = SW_INT(texture_pages[pft4->texture_set], *(ushort*)&pft4->uv1);
							cp->uv3_uv2 = *(ushort*)&pft4->uv2;
							cp->originalindex = i;

							cp = carPolyBuffer + newNumPolys + 1;

							cp->vindices = pft4->v0 | (pft4->v2 | pft4->v3 << 8) << 8;
							cp->clut_uv0 = SW_INT(texture_cluts[polyList[1]][polyList[2]], *(ushort*)&pft4->uv0);
							cp->tpage_uv1 = SW_INT(texture_pages[polyList[1]], *(ushort*)&pft4->uv2);
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
						
							cp->vindices = pgt3->v0 | (pgt3->v1 | pgt3->v2 << 8) << 8;
							cp->nindices = pgt3->n0 | (pgt3->n1 | pgt3->n2 << 8) << 8;
							cp->clut_uv0 = ((int)(clut * 384 + pgt3->texture_id * 12 - 384) >> 1) << 0x10 | *(ushort *)&pgt3->uv0;
							cp->tpage_uv1 = SW_INT(texture_pages[pgt3->texture_set], *(ushort *)&pgt3->uv1);
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

							cp->vindices = pgt4->v0 | (pgt4->v1 | pgt4->v2 << 8) << 8;
							cp->nindices = pgt4->n0 | (pgt4->n1 | pgt4->n2 << 8) << 8;
							cp->clut_uv0 = ((int)(clut * 384 + pgt4->texture_id * 12 - 384) >> 1) << 0x10 | *(ushort*)&pgt4->uv0;
							cp->tpage_uv1 = SW_INT(texture_pages[pgt4->texture_set], *(ushort*)&pgt4->uv1);
							cp->uv3_uv2 = *(ushort*)&pgt4->uv2;
							cp->originalindex = i;

							cp = carPolyBuffer + newNumPolys + 1;

							cp->vindices = pgt4->v0 | (pgt4->v2 | pgt4->v3 << 8) << 8;
							cp->nindices = pgt4->n0 | (pgt4->n2 | pgt4->n3 << 8) << 8;
							cp->clut_uv0 = ((int)(clut * 384 + pgt4->texture_id * 12 - 384) >> 1) << 0x10 | *(ushort*)&pgt4->uv0;
							cp->tpage_uv1 = SW_INT(texture_pages[pgt4->texture_set], *(ushort *)&pgt4->uv2);
							cp->uv3_uv2 = *(ushort *)&pgt4->uv3;
							cp->originalindex = i;

							newNumPolys += 2;
						}
				}

				polyList += PolySizes[ptype & 0x1f];
				i++;
			}

			if (pass == 1) 
				car->numFT3 = newNumPolys - whichCP;
			else if (pass == 0)
				car->numGT3 = newNumPolys - whichCP;
			else if (pass == 2) 
				car->numB3 = newNumPolys - whichCP;

			whichCP = newNumPolys;

			pass++;
		} while (pass < 3);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ MangleWheelModels()
 // line 2595, offset 0x000230c8
	/* begin block 1 */
		// Start line: 2597
		// Start offset: 0x000230C8
		// Variables:
	// 		int i; // $v1
	// 		MODEL *m; // $t0
	// 		POLYFT4LIT *src; // $a0

		/* begin block 1.1 */
			// Start line: 2610
			// Start offset: 0x00023110
			// Variables:
		// 		int j; // $t1
		/* end block 1.1 */
		// End offset: 0x00023354
		// End Line: 2641
	/* end block 1 */
	// End offset: 0x00023390
	// End Line: 2649

	/* begin block 2 */
		// Start line: 6754
	/* end block 2 */
	// End Line: 6755

	/* begin block 3 */
		// Start line: 6755
	/* end block 3 */
	// End Line: 6756

	/* begin block 4 */
		// Start line: 6759
	/* end block 4 */
	// End Line: 6760

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void MangleWheelModels(void)
{
	UV_INFO tmpUV2;
	unsigned char tmpUV;
	int i;
	uint v0;
	uint v1;
	uint v2;
	POLYFT4*src;
	MODEL *m;
	int j;

	i = 0;
	do {

		if (i == 1)
			m = gFastWheelModelPtr;
		else if (i == 2)
			m = gDamWheelModelPtr;
		else
			m = gCleanWheelModelPtr;

		// do some fuckery swaps
		src = (POLYFT4*)m->poly_block;
		
		v0 = *(uint *)&src[2].v0;
		v1 = *(uint *)&src[2].uv0;
		v2 = *(uint *)&src[2].uv2;
		*(uint *)src = *(uint *)(src + 2);
		*(uint *)&src->v0 = v0;
		*(uint *)&src->uv0 = v1;
		*(uint *)&src->uv2 = v2;
		src->color = src[2].color;

		v0 = *(uint *)&src[3].v0;
		v1 = *(uint *)&src[3].uv0;
		v2 = *(uint *)&src[3].uv2;
		*(uint *)(src + 1) = *(uint *)(src + 3);
		*(uint *)&src[1].v0 = v0;
		*(uint *)&src[1].uv0 = v1;
		*(uint *)&src[1].uv2 = v2;
		src[1].color = src[3].color;

		v0 = *(uint *)&src[4].v0;
		v1 = *(uint *)&src[4].uv0;
		v2 = *(uint *)&src[4].uv2;
		*(uint *)(src + 2) = *(uint *)(src + 4);
		*(uint *)&src[2].v0 = v0;
		*(uint *)&src[2].uv0 = v1;
		*(uint *)&src[2].uv2 = v2;
		src[2].color = src[4].color;

		v0 = *(uint *)&src[6].v0;
		v1 = *(uint *)&src[6].uv0;
		v2 = *(uint *)&src[6].uv2;
		*(uint *)(src + 3) = *(uint *)(src + 6);
		*(uint *)&src[3].v0 = v0;
		*(uint *)&src[3].uv0 = v1;
		*(uint *)&src[3].uv2 = v2;
		src[3].color = src[6].color;

		src[2].v0 = 16;
		src[2].v1 = 17;
		src[2].v2 = 23;
		src[2].v3 = 22;
		src[3].v0 = 21;
		src[3].v1 = 20;
		src[3].v2 = 19;
		src[3].v3 = 18;

		tmpUV = (src->uv0.u >> 1) + (src->uv2.u >> 1);
		src[3].uv3.u = tmpUV;
		src[3].uv2.u = tmpUV;
		src[3].uv1.u = tmpUV;
		src[3].uv0.u = tmpUV;
		src[2].uv3.u = tmpUV;
		src[2].uv2.u = tmpUV;
		src[2].uv1.u = tmpUV;
		src[2].uv0.u = tmpUV;

		tmpUV = (src->uv0.v >> 1) + (src->uv2.v >> 1);
		src[3].uv3.v = tmpUV;
		src[3].uv2.v = tmpUV;
		src[3].uv1.v = tmpUV;
		src[3].uv0.v = tmpUV;
		src[2].uv3.v = tmpUV;
		src[2].uv2.v = tmpUV;
		src[2].uv1.v = tmpUV;
		src[2].uv0.v = tmpUV;

		m->num_polys = 4;

		j = 0;
		do {
			tmpUV2 = src->uv0;
			
			src->uv0 = src->uv1;
			src->uv1 = src->uv2;
			src->uv2 = src->uv3;
			src->uv3 = tmpUV2;

			src++;
		} while (++j < 2);

	} while (++i < 3);

	// HACK: Show clean model only in Rio.
	if (GameLevel == 3) 
	{
		gFastWheelModelPtr = gCleanWheelModelPtr;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ setupLightingMatrices()
 // line 2656, offset 0x000235f8
	/* begin block 1 */
		// Start line: 7465
	/* end block 1 */
	// End Line: 7466

	/* begin block 2 */
		// Start line: 7931
	/* end block 2 */
	// End Line: 7932

	/* begin block 3 */
		// Start line: 7933
	/* end block 3 */
	// End Line: 7934

/* WARNING: Unknown calling convention yet parameter storage is locked */

MATRIX save_colour_matrix;
MATRIX save_light_matrix;

// [D] [T]
void setupLightingMatrices(void)
{
	gte_ReadColorMatrix(&save_colour_matrix);
	gte_ReadLightMatrix(&save_light_matrix);

	gte_SetColorMatrix(&colour_matrix);
	gte_SetLightMatrix(&light_matrix);

	if (gTimeOfDay == 3) 
	{
		gte_ldbkdir(0x400, 0x400, 0x400);
		return;
	}

	gte_ldbkdir(0x8c0, 0x8c0, 0x8c0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ restoreLightingMatrices()
 // line 2685, offset 0x00023750
	/* begin block 1 */
		// Start line: 7989
	/* end block 1 */
	// End Line: 7990

	/* begin block 2 */
		// Start line: 7990
	/* end block 2 */
	// End Line: 7991

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void restoreLightingMatrices(void)
{
	gte_SetColorMatrix(&save_colour_matrix);
	gte_SetLightMatrix(&save_light_matrix);
}



// decompiled code
// original method signature: 
// char /*$ra*/ GetCarPalIndex(int tpage /*$a0*/)
 // line 2697, offset 0x00023390
	/* begin block 1 */
		// Start line: 2698
		// Start offset: 0x00023390
		// Variables:
	// 		int i; // $a1
	/* end block 1 */
	// End offset: 0x000233D4
	// End Line: 2713

	/* begin block 2 */
		// Start line: 7024
	/* end block 2 */
	// End Line: 7025

	/* begin block 3 */
		// Start line: 7073
	/* end block 3 */
	// End Line: 7074

	/* begin block 4 */
		// Start line: 7076
	/* end block 4 */
	// End Line: 7077

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


// decompiled code
// original method signature: 
// void /*$ra*/ ProcessPalletLump(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
 // line 1970, offset 0x00019f44
	/* begin block 1 */
		// Start line: 1971
		// Start offset: 0x00019F44
		// Variables:
	// 		int total_cluts; // $v0
	// 		int clutValue; // $s1
	// 		int tpageindex; // $s2
	// 		int texnum; // $s3
	// 		int palette; // $s4
	// 		int clut_number; // $v1
	// 		unsigned short clutTable[320]; // stack offset -680
	// 		char *buffPtr; // $s0

		/* begin block 1.1 */
			// Start line: 2013
			// Start offset: 0x00019FD0
		/* end block 1.1 */
		// End offset: 0x00019FD0
		// End Line: 2013
	/* end block 1 */
	// End offset: 0x0001A094
	// End Line: 2034

	/* begin block 2 */
		// Start line: 8209
	/* end block 2 */
	// End Line: 8210

	/* begin block 3 */
		// Start line: 3940
	/* end block 3 */
	// End Line: 3941


// [D]
void ProcessPalletLump(char *lump_ptr, int lump_size)
{
	if (gDriver1Level)	// [A]
		return;	// TODO: load Driver 1 civ palettes

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