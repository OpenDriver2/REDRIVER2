#include "THISDUST.H"
#include "CARS.H"
#include "TEXTURE.H"
#include "OVERMAP.H"
#include "DRAW.H"
#include "MISSION.H"
#include "SYSTEM.H"
#include "DEBRIS.H"
#include "MAIN.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "HANDLING.H"
#include "COSMETIC.H"
#include "DENTING.H"
#include "SHADOW.H"
#include "CIV_AI.H"
#include "COP_AI.H"
#include "MC_SND.H"
#include "CUTSCENE.H"
#include "CONVERT.H"
#include "../ASM/ASMTEST.H"

#include "GTEREG.H"
#include "INLINE_C.H"
#include "LIBAPI.H"


SVECTOR day_vectors[4] =
{
  { 62404, 2520, 783, 0 },
  { 62404, 2520, 783, 0 },
  { 63172, 2364, 2364, 0 },
  { 62404, 2520, 783, 0 }
};

SVECTOR night_vectors[4] =
{
  { 3132, 2520, 783, 0 },
  { 3132, 2520, 783, 0 },
  { 63172, 2364, 63172, 0 },
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

MATRIX light_matrix =
{ { { 4096, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, { 0, 0, 0 } };

MATRIX colour_matrix =
{ { { 4032, 0, 0 }, { 3936, 0, 0 }, { 3520, 0, 0 } }, { 0, 0, 0 } };

// PHYSICS
_CAR_DATA car_data[22];	// all cars

// active cars
_CAR_DATA* active_car_list[20];
BOUND_BOX bbox[20];
unsigned char lightsOnDelay[20];

char force_siren[8] = { 0 };

// decompiled code
// original method signature: 
// void /*$ra*/ plotNewCarModel(struct CAR_MODEL *car /*$s0*/, int palette /*$s2*/)
 // line 834, offset 0x00020c94
	/* begin block 1 */
		// Start line: 835
		// Start offset: 0x00020C94
		// Variables:
	// 		struct plotCarGlobals _pg; // stack offset -72
	// 		struct SVECTOR v0; // stack offset -32
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

unsigned long gUnderIntensity = 0;
struct DENTUVS *gTempCarUVPtr;
DENTUVS gTempHDCarUVDump[20][255];
SVECTOR gTempCarVertDump[20][132];
DENTUVS gTempLDCarUVDump[20][134];
CAR_MODEL NewCarModel[5];
CAR_MODEL NewLowCarModel[5];

MODEL* gCarLowModelPtr[5];
MODEL* gCarDamModelPtr[5];
MODEL* gCarCleanModelPtr[5];

int whichCP = 0;
int baseSpecCP = 0;

CAR_POLY carPolyBuffer[2001];

// idk if it's global or not
SVECTOR carLightD = { 0, 0xF000, 0, 0 }; // 0xAA130 yet not defined in symbols

// [D]
void plotNewCarModel(CAR_MODEL *car, int palette)
{
	//undefined4 uVar1;
	//undefined4 uVar2;
	//undefined4 in_zero;
	//undefined4 in_at;
	int iVar3;
	plotCarGlobals _pg;
	ulong lightlevel;

	//uVar2 = DAT_000aa134;
	//uVar1 = DAT_000aa130;
	lightlevel = combointensity | 0x3000000;
	if (car != NULL) {
		if (-1 < gTimeOfDay) {
			if (gTimeOfDay < 3) {
				lightlevel = combointensity | 0x30000000;
			}
			else {
				if (gTimeOfDay == 3) {
					lightlevel = 0x302a2a2a;
				}
			}
		}
		iVar3 = combointensity;
		setupLightingMatrices();

		gte_ldv0(&carLightD);
		MTC2(lightlevel, 6);

		docop2(0x108041b);

		_pg.primptr = (unsigned char*)current->primptr;
		_pg.intensity = 0;
		_pg.pciv_clut = (unsigned short *)civ_clut + 0xc0;
		_pg.damageLevel = (unsigned char *)gTempCarUVPtr;

		_pg.ot = (OTTYPE *)(current->ot + 0x1c);

		gUnderIntensity = MFC2(22); //getCopReg(2, 0x16);

		plotCarPolyB3(car->numB3, car->pB3, car->vlist, &_pg);
		_pg.intensity = gUnderIntensity & 0xffffff;

		_pg.ot = (OTTYPE *)(current->ot + 16);
		plotCarPolyFT3(car->numFT3, car->pFT3, car->vlist, &_pg);
		_pg.ot = (OTTYPE *)(current->ot + 4);

		if (gTimeOfDay == 3)
		{
			_pg.intensity = (int)(combointensity & 0xfcfcf0U) >> 2;
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
}



// decompiled code
// original method signature: 
// void /*$ra*/ plotCarPolyB3(int numTris /*$a0*/, struct CAR_POLY *src /*$a1*/, struct SVECTOR *vlist /*$a2*/, struct plotCarGlobals *pg /*$a3*/)
 // line 917, offset 0x000237b8
	/* begin block 1 */
		// Start line: 918
		// Start offset: 0x000237B8
		// Variables:
	// 		struct POLY_F3 *prim; // $t0
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

// [D]
void plotCarPolyB3(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg)
{
	int iVar1;
	uint uVar2;
	uint uVar3;
	SVECTOR *v2;
	uint uVar4;
	SVECTOR *v1;
	SVECTOR *v0;
	POLY_F3 *prim;
	OTTYPE *ot;

	prim = (POLY_F3 *)pg->primptr;
	uVar4 = pg->intensity;
	ot = pg->ot;
	if (0 < numTris) 
	{
		do {
			uVar3 = src->vindices;
			v0 = vlist + (uVar3 & 0xff);
			v1 = (SVECTOR *)((int)&vlist->vx + ((int)uVar3 >> 5 & 0x7f8U));
			v2 = (SVECTOR *)((int)&vlist->vx + ((int)uVar3 >> 0xd & 0x7f8U));

			gte_ldv3(v0, v1, v2);

			docop2(0x280030);

			*(uint *)&prim->r0 = uVar4 | 0x20000000;

			docop2(0x1400006);
			iVar1 = MAC0;  //getCopReg(2, 0x18);
			docop2(0x158002d);

			if (-1 < iVar1) 
			{
				uVar2 = SXY0; // getCopReg(2, 0xc);
				*(uint *)&prim->x0 = uVar2;
				uVar2 = SXY1; // getCopReg(2, 0xd);
				*(uint *)&prim->x1 = uVar2;
				uVar2 = SXY2; // getCopReg(2, 0xe);
				*(uint *)&prim->x2 = uVar2;
				iVar1 = OTZ; // getCopReg(2, 7);

				setPolyF3(prim);
				addPrim(ot + (iVar1 >> 1), prim);

				prim++;
			}
			numTris = numTris + -1;
			src = src + 1;
		} while (0 < numTris);
	}

	pg->primptr = (unsigned char*)prim;
}



// decompiled code
// original method signature: 
// void /*$ra*/ plotCarPolyFT3(int numTris /*$a0*/, struct CAR_POLY *src /*$t1*/, struct SVECTOR *vlist /*$t4*/, struct plotCarGlobals *pg /*$t5*/)
 // line 976, offset 0x000238c4
	/* begin block 1 */
		// Start line: 977
		// Start offset: 0x000238C4
		// Variables:
	// 		struct POLY_FT3 *prim; // $t0
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

// [D]
void plotCarPolyFT3(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg)
{
	uint uVar1;
	uint FT3rgbb;
	uint uVar2;
	SVECTOR *v2;
	SVECTOR *v1;
	SVECTOR *v0;
	int iVar3;
	int iVar4;
	int iVar5;
	POLY_FT3 *prim;
	CAR_POLY *pCVar6;
	OTTYPE *ot;
	long FT3rgb;
	int reg;

	prim = (POLY_FT3 *)pg->primptr;
	FT3rgbb = pg->intensity | 0x24000000;
	ot = pg->ot;

	MTC2(FT3rgbb, 6);

	pCVar6 = src;
	if (0 < numTris) {
		do {
			uVar2 = pCVar6->vindices;
			v0 = vlist + (uVar2 & 0xff);
			v1 = (SVECTOR *)((int)&vlist->vx + ((int)uVar2 >> 5 & 0x7f8U));
			v2 = (SVECTOR *)((int)&vlist->vx + ((int)uVar2 >> 0xd & 0x7f8U));

			gte_ldv3(v0, v1, v2);

			docop2(0x280030);

			iVar4 = pCVar6->clut_uv0;
			iVar5 = pCVar6->tpage_uv1;
			iVar3 = pCVar6->uv3_uv2;
			uVar2 = (uint)pg->damageLevel[pCVar6->originalindex];
			*(uint *)&prim->r0 = FT3rgbb;
			src = (CAR_POLY *)(iVar3 + uVar2);
			*(uint *)&prim->u0 = iVar4 + uVar2;
			*(uint *)&prim->u1 = iVar5 + uVar2;
			*(CAR_POLY **)&prim->u2 = src;
			docop2(0x1400006);
			iVar3 = MAC0; // getCopReg(2, 0x18);
			docop2(0x158002d);

			if (-1 < iVar3) 
			{
				uVar1 = SXY0; // getCopReg(2, 0xc);
				*(uint *)&prim->x0 = uVar1;
				uVar1 = SXY1; //getCopReg(2, 0xd);
				*(uint *)&prim->x1 = uVar1;
				uVar1 = SXY2; //getCopReg(2, 0xe);
				*(uint *)&prim->x2 = uVar1;
				iVar3 = OTZ; //getCopReg(2, 7);

				setPolyFT3(prim);
				addPrim(ot + (iVar3 >> 1), prim);

				prim = prim + 1;
			}
			numTris = numTris + -1;
			pCVar6 = pCVar6 + 1;
		} while (0 < numTris);
	}

	pg->primptr = (unsigned char*)prim;
}



// decompiled code
// original method signature: 
// void /*$ra*/ plotCarPolyGT3(int numTris /*$a0*/, struct CAR_POLY *src /*$t1*/, struct SVECTOR *vlist /*$s0*/, struct SVECTOR *nlist /*$a3*/, struct plotCarGlobals *pg /*stack 16*/, int palette /*stack 20*/)
 // line 1125, offset 0x00020ea0
	/* begin block 1 */
		// Start line: 1126
		// Start offset: 0x00020EA0
		// Variables:
	// 		struct POLY_GT3 *prim; // $t0
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

// [D]
void plotCarPolyGT3(int numTris, CAR_POLY *src, SVECTOR *vlist, SVECTOR *nlist, plotCarGlobals *pg, int palette)
{
	int iVar1;
	int iVar2;
	uint uVar3;
	SVECTOR *pSVar4;
	ushort *puVar5;
	SVECTOR *pSVar6;
	uint uVar7;
	SVECTOR *pSVar8;
	uint uVar9;
	int iVar10;
	POLY_GT3 *prim;
	uint uVar11;
	uint uVar12;
	int iVar13;
	int iVar14;

	prim = (POLY_GT3 *)pg->primptr;
	puVar5 = pg->pciv_clut;

	MTC2(pg->intensity | 0x34000000, 6);

	while (true) 
	{
		uVar9 = src->vindices;
		iVar14 = src->tpage_uv1;
		iVar13 = src->uv3_uv2;
		uVar7 = (uint)pg->damageLevel[src->originalindex];
		iVar10 = (src->clut_uv0 & 0xffffU | (uint)puVar5[palette + (src->clut_uv0 >> 0x10)] << 0x10)
			+ uVar7;
		if (numTris < 1) break;
		pSVar8 = vlist + (uVar9 & 0xff);
		pSVar6 = vlist + ((int)uVar9 >> 8 & 0xff);
		pSVar4 = vlist + ((int)uVar9 >> 0x10 & 0xff);

		gte_ldv3(pSVar8, pSVar6, pSVar4);

		docop2(0x280030);
		uVar9 = src->nindices;
		uVar12 = (uint)*(ushort *)((int)&nlist->pad + ((int)uVar9 >> 5 & 0x7f8U));
		docop2(0x1400006);
		uVar11 = (uint)*(ushort *)((int)&nlist->pad + ((int)uVar9 >> 0xd & 0x7f8U));

		iVar1 = MAC0;	//  getCopReg(2, 0x18);

		docop2(0x158002d);
		src = src + 1;

		iVar2 = OTZ;	// getCopReg(2, 7);

		if (-1 < iVar1 && 0 < iVar2) 
		{
			setPolyGT3(prim);

			*(uint *)&prim->r0 =
				((uint)(ushort)nlist[uVar9 & 0xff].pad & 0xff) << 0x10 |
				(uint)(ushort)nlist[uVar9 & 0xff].pad | 0x34000000;

			*(uint *)&prim->r1 = (uVar12 & 0xff) << 0x10 | uVar12;
			*(uint *)&prim->r2 = (uVar11 & 0xff) << 0x10 | uVar11;
			*(int *)&prim->u0 = iVar10;
			*(uint *)&prim->u1 = iVar14 + uVar7;
			*(uint *)&prim->u2 = iVar13 + uVar7;

			uVar3 = SXY0;	// getCopReg(2, 0xc);
			*(uint *)&prim->x0 = uVar3;
			uVar3 = SXY1;	// getCopReg(2, 0xd);
			*(uint *)&prim->x1 = uVar3;
			uVar3 = SXY2;	// getCopReg(2, 0xe);
			*(uint *)&prim->x2 = uVar3;

			addPrim(pg->ot + (iVar2 >> 1), prim);

			prim = prim + 1;
		}

		numTris = numTris + -1;
	}

	pg->primptr = (unsigned char*)prim;
}



// decompiled code
// original method signature: 
// void /*$ra*/ plotCarPolyGT3nolight(int numTris /*$a0*/, struct CAR_POLY *src /*$t3*/, struct SVECTOR *vlist /*$t6*/, struct plotCarGlobals *pg /*$a3*/, int palette /*stack 16*/)
 // line 1349, offset 0x00023a20
	/* begin block 1 */
		// Start line: 1350
		// Start offset: 0x00023A20
		// Variables:
	// 		struct POLY_FT3 *prim; // $t0
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

// [D]
void plotCarPolyGT3nolight(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg, int palette)
{
	ushort uVar1;
	int iVar2;
	uint uVar3;
	uint uVar4;
	uint uVar5;
	SVECTOR *local_v0_116;
	ushort *puVar6;
	SVECTOR *local_v1_100;
	SVECTOR *pSVar7;
	uint uVar8;
	POLY_GT3 *prim;
	int iVar9;
	int iVar10;
	CAR_POLY *pCVar11;
	long *plVar12;
	long local_4;

	prim = (POLY_GT3 *)pg->primptr;
	uVar4 = pg->intensity | 0x24000000;
	puVar6 = pg->pciv_clut;

	MTC2(pg->intensity | 0x24000000, 6); // setCopReg(2, vlist, uVar4);

	pCVar11 = src;
	if (0 < numTris) 
	{
		do {
			uVar5 = pCVar11->vindices;
			pSVar7 = vlist + (uVar5 & 0xff);
			local_v1_100 = (SVECTOR *)((int)&vlist->vx + ((int)uVar5 >> 5 & 0x7f8U));
			local_v0_116 = (SVECTOR *)((int)&vlist->vx + ((int)uVar5 >> 0xd & 0x7f8U));

			gte_ldv3(pSVar7, local_v1_100, local_v0_116);

			docop2(0x280030);

			uVar8 = pCVar11->clut_uv0;
			iVar9 = pCVar11->tpage_uv1;
			iVar10 = pCVar11->uv3_uv2;
			src = (CAR_POLY *)(int)pCVar11->originalindex;
			uVar1 = puVar6[palette + ((int)uVar8 >> 0x10)];
			uVar5 = (uint)pg->damageLevel[(int)src];

			docop2(0x1400006);

			iVar2 = MAC0; // getCopReg(2, 0x18);
			docop2(0x158002d);

			local_4 = OTZ;// getCopReg(2, 7);

			if (-1 < iVar2 && 0 < local_4)	// [A] Ghidra flow detection probably failed, or blame Game devs...
			{
				//local_4 = (long)(plVar12 + (local_4 >> 1));

				uVar3 = SXY0; //getCopReg(2, 0xc);
				*(uint *)&prim->x0 = uVar3;
				uVar3 = SXY1; //getCopReg(2, 0xd);
				*(uint *)&prim->r1 = uVar3;
				uVar3 = SXY2; //getCopReg(2, 0xe);
				*(uint *)&prim->u1 = uVar3;

				*(uint *)&prim->u0 = (uVar8 & 0xffff | (uint)uVar1 << 0x10) + uVar5;
				*(uint *)&prim->x1 = iVar9 + uVar5;
				*(uint *)&prim->r2 = iVar10 + uVar5;
				*(uint *)&prim->r0 = uVar4;

				addPrim(pg->ot + (local_4 >> 1), prim);
				prim++;
			}

			numTris = numTris + -1;
			pCVar11 = pCVar11 + 1;
		} while (0 < numTris);
	}

	pg->primptr = (unsigned char*)prim;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCar(struct _CAR_DATA *cp /*$s3*/, int view /*$a1*/)
 // line 1442, offset 0x000210b8
	/* begin block 1 */
		// Start line: 1443
		// Start offset: 0x000210B8
		// Variables:
	// 		int WheelSpeed; // $s0
	// 		int model; // $fp
	// 		struct _PLAYER *lp; // $a2

		/* begin block 1.1 */
			// Start line: 1454
			// Start offset: 0x00021174
			// Variables:
		// 		struct CVECTOR col; // stack offset -312
		/* end block 1.1 */
		// End offset: 0x00021244
		// End Line: 1492

		/* begin block 1.2 */
			// Start line: 1496
			// Start offset: 0x00021244
			// Variables:
		// 		struct MATRIX temp_mat1; // stack offset -304
		// 		struct MATRIX temp_mat2; // stack offset -272
		// 		struct MATRIX final_mat; // stack offset -240
		// 		struct VECTOR pos; // stack offset -208
		// 		struct VECTOR pos1; // stack offset -192
		// 		struct SVECTOR temp_vec; // stack offset -176
		// 		int result; // $s4

			/* begin block 1.2.1 */
				// Start line: 1519
				// Start offset: 0x00021290
				// Variables:
			// 		struct VECTOR corners[4]; // stack offset -168
			/* end block 1.2.1 */
			// End offset: 0x00021384
			// End Line: 1538

			/* begin block 1.2.2 */
				// Start line: 1542
				// Start offset: 0x00021384
				// Variables:
			// 		struct VECTOR d; // stack offset -104
			// 		struct VECTOR dist; // stack offset -88
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
			// 		struct MATRIX workmatrix; // stack offset -104
			// 		struct CAR_MODEL *CarModelPtr; // $s1

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
				// 		struct CAR_MODEL *CarModelPtr; // $s0

					/* begin block 1.2.5.1.1 */
						// Start line: 1706
						// Start offset: 0x000217BC
						// Variables:
					// 		struct MATRIX workmatrix; // stack offset -72
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

// [D] [A]
void DrawCar(_CAR_DATA *cp, int view)
{
	unsigned char bVar1;
	unsigned char uVar2;
	short sVar3;
	short sVar4;
	char cVar5;
	int iVar6;
	int vvvar;

	short *psVar7;
	MATRIX *pMVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	MATRIX *m1;
	uint uVar12;
	CVECTOR col;
	MATRIX temp_mat1;
	MATRIX temp_mat2;
	VECTOR pos;
	VECTOR local_c0;
	SVECTOR temp_vec;
	VECTOR corners[4];
	VECTOR d;
	VECTOR dist;
	MATRIX workmatrix;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	uVar12 = cp->ap.model;

	if (player[view].cameraView == 2 && cp->id == player[view].cameraCarId) 
	{
		sVar3 = cp->ap.damage[0];

		LeftLight = player[view].cameraView;

		if (499 < sVar3)
		{
			if (sVar3 < 1000)
				LeftLight = '\x01';
			else 
				LeftLight = '\0';
		}

		// it has a bug... I know that since 2002...

		sVar3 = (cp->ap).damage[1];

		if (sVar3 < 500) 
			RightLight = 2;
		else if(sVar3 < 1000)
			RightLight = 1;
		else
			RightLight = '\0';

		if (gLightsOn == 0) 
			return;

		if (lightsOnDelay[cp->id] != 0) 
			return;

		PlacePoolForCar(cp, &col, 1);
		return;
	}

	pos.vx = (cp->hd).where.t[0];
	pos.vz = (cp->hd).where.t[2];
	pos.vy = -(cp->hd).where.t[1];
	local_c0.vx = pos.vx;
	local_c0.vz = pos.vz;

	SetFrustrumMatrix();
	iVar6 = FrustrumCheck(&pos, 800);
	if (iVar6 == -1) {
		return;
	}
	iVar11 = (int)(cp->hd).oBox.radii[0].vx;
	iVar9 = (int)(cp->hd).oBox.radii[2].vx;
	vvvar = pos.vx + iVar11;
	corners[0].vx = vvvar + iVar9;
	corners[1].vx = vvvar - iVar9;
	iVar11 = pos.vx - iVar11;
	corners[2].vx = iVar11 + iVar9;
	corners[3].vx = iVar11 - iVar9;
	iVar11 = (int)(cp->hd).oBox.radii[0].vz;
	iVar9 = (int)(cp->hd).oBox.radii[2].vz;
	vvvar = pos.vz + iVar11;
	corners[0].vz = vvvar + iVar9;
	corners[1].vz = vvvar - iVar9;
	iVar11 = pos.vz - iVar11;
	corners[2].vz = iVar11 + iVar9;
	corners[3].vz = iVar11 - iVar9;
	corners[3].vy = pos.vy;
	corners[2].vy = pos.vy;
	corners[1].vy = pos.vy;
	corners[0].vy = pos.vy;

	vvvar = FrustrumCheck(&pos, 0);

	if ((((vvvar == -1) && (vvvar = FrustrumCheck(corners, 0), vvvar == -1)) &&
		(vvvar = FrustrumCheck(corners + 1, 0), vvvar == -1)) &&
		((vvvar = FrustrumCheck(corners + 2, 0), vvvar == -1 &&
		(vvvar = FrustrumCheck(corners + 3, 0), vvvar == -1)))) 
	{
		iVar6 = -1;
	}

	d.vx = (cp->hd).oBox.location.vx - camera_position.vx;
	d.vy = -camera_position.vy - (cp->hd).oBox.location.vy;
	d.vz = (cp->hd).oBox.location.vz - camera_position.vz;
	iVar11 = (int)(cp->hd).oBox.length[0];

	vvvar = d.vx * cp->hd.oBox.radii[0].vx + d.vy * cp->hd.oBox.radii[0].vy + d.vz * cp->hd.oBox.radii[0].vz;

	if (vvvar < 0) 
		vvvar = -vvvar;

	iVar9 = d.vx * cp->hd.oBox.radii[1].vx + d.vy * cp->hd.oBox.radii[1].vy + d.vz * cp->hd.oBox.radii[1].vz;
	iVar10 = d.vx * cp->hd.oBox.radii[2].vx + d.vy * cp->hd.oBox.radii[2].vy +d.vz * cp->hd.oBox.radii[2].vz;

	if (vvvar < iVar11 * iVar11) 
	{
		vvvar = (int)(cp->hd).oBox.length[1];
		if (iVar9 < 0) 
			iVar9 = -iVar9;


		if (iVar9 < vvvar * vvvar)
		{
			vvvar = cp->hd.oBox.length[2];
			if (iVar10 < 0)
				iVar10 = -iVar10;

			if (iVar10 < vvvar * vvvar) 
				iVar6 = -1;
		}
	}
	if (iVar6 == -1)
		return;

	pos.vx = pos.vx - camera_position.vx;
	pos.vy = pos.vy - camera_position.vy;
	pos.vz = pos.vz - camera_position.vz;

	Apply_Inv_CameraMatrix(&pos);

	m1 = &cp->hd.drawCarMat;
	num_cars_drawn = num_cars_drawn + 1;

	/*if (cheats.MiniCars != 0)	// [A] DISABLED, NO REAL SENSE TO KEEP THIS HERE...
	{
		iVar6 = 8;
		pMVar8 = m1;
		do {
			iVar6 = iVar6 + -1;
			pMVar8->m[0] = pMVar8->m[0] >> 2;
			pMVar8 = (MATRIX *)(pMVar8->m + 1);
		} while (-1 < iVar6);
	}*/

	if (((pos.vz < 0x157d) && (gForceLowDetailCars == 0)) || (cp->controlType == '\x01')) 
	{
		vvvar = cp->hd.speed * 0x2000;
		iVar6 = MaxPlayerDamage[0];

		if (cp->controlType == 1)
		{
			iVar6 = MaxPlayerDamage[(int)cp->ai.padid];
		}

		if ((int)(uint)cp->totalDamage < iVar6) 
		{
			sVar3 = cp->ap.damage[0];

			if (3000 < sVar3)
				goto LAB_00021724;

			sVar4 = (cp->ap).damage[1];

			if (3000 < sVar4)
				goto LAB_00021724;

			if (((2000 < sVar3) || (2000 < sVar4)) && (vvvar + 399999U < 1199999))
			{
				AddSmokingEngine(cp, 0, vvvar);
			}
		}
		else {
			if (vvvar + 59999U < 119999) 
			{
				AddFlamingEngine(cp);
			}
		LAB_00021724:
			if (vvvar + 399999U < 1199999) 
			{
				AddSmokingEngine(cp, 1, vvvar);
			}
		}

		gTimeInWater = 0x19;
		gSinkingTimer = 100;

		SetShadowPoints(cp);
		PlaceShadowForCar((cp->hd).shadowPoints, cp->id, &pos, 0);

		ComputeCarLightingLevels(cp, 1);

		gTempCarUVPtr = gTempHDCarUVDump[cp->id];
		NewCarModel[uVar12].vlist = gTempCarVertDump[cp->id];
		NewCarModel[uVar12].nlist = gTempCarVertDump[cp->id];
		MulMatrix0(&inv_camera_matrix, m1, &workmatrix);
		FindCarLightFade(&workmatrix);

		DrawCarObject(NewCarModel + uVar12, &workmatrix, &pos, &local_c0, cp->ap.palette,cp, 1);

		DrawCarWheels(cp, &workmatrix, &pos, 0);
	}
	else 
	{
		NewLowCarModel[uVar12].nlist = gTempCarVertDump[cp->id];
		gTempCarUVPtr = gTempLDCarUVDump[cp->id];

		if (pos.vz < 8000) 
		{
			SetShadowPoints(cp);
			PlaceShadowForCar((cp->hd).shadowPoints, cp->id, &pos, 0);
		}

		ComputeCarLightingLevels(cp, '\0');
		MulMatrix0(&inv_camera_matrix, m1, (MATRIX *)&d);
		FindCarLightFade((MATRIX *)&d);

		DrawCarObject(NewLowCarModel + uVar12, (MATRIX *)&d, &pos, &local_c0, cp->ap.palette, cp, 0);
	}

	TransparentObject = 0;
	if (cp->controlType == 2)
	{
		PlayerCarFX(cp);
	}
	else
	{
		if (cp->controlType == 2)
		{
			CivCarFX(cp);
		}
	}
	if (gLightsOn != 0 && lightsOnDelay[cp->id] == 0)
	{
		if (cp->controlType == 2) 
		{
			if ((cp->ai.c.thrustState != 3) || (((bVar1 = cp->ai.c.ctrlState, bVar1 != 5 && (bVar1 != 7)) && (bVar1 != 8))))
			{
				AddNightLights(cp);
			}
		}
		else
		{
			cVar5 = SilenceThisCar(cp->id);

			if (cVar5 == 0)
				AddNightLights(cp);
		}
	}

	if (cp->controlType == 3)
	{
		if ((int)player[0].playerCarId < 0) 
			psVar7 = &pedestrianFelony;
		else 
			psVar7 = &car_data[(int)player[0].playerCarId].felonyRating;

		if (*psVar7 > 0x292 && (MissionHeader->residentModels[3] == 0))
		{
			if (cp->ai.p.dying < 0x4b)
				AddCopCarLight(cp);

			return;
		}
	}

	// WTF IS THIS?
	UNIMPLEMENTED(); // [A]
	/*
	if (((*(uint *)&cp->hndType & 0x2ff00) != 0x20200) &&
		(((gInGameCutsceneActive == 0 || (cp->controlType != '\a')) ||
		(force_siren[(int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2] == '\0'))))
	{
		if (gCurrentMissionNumber != 0x1a) 
			return;

		if ((cp->ap).model != 4) 
			return;

		if (cp->controlType != 10)
			return;
	}
	*/

	if (cp->ai.p.dying < 0x4b)
		AddCopCarLight(cp);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCarObject(struct CAR_MODEL *car /*$s0*/, struct MATRIX *matrix /*$a1*/, struct VECTOR *pos /*$a2*/, struct VECTOR *pos1 /*$a3*/, int palette /*stack 16*/, struct _CAR_DATA *cp /*stack 20*/, int detail /*stack 24*/)
 // line 1793, offset 0x000233dc
	/* begin block 1 */
		// Start line: 1794
		// Start offset: 0x000233DC

		/* begin block 1.1 */
			// Start line: 1794
			// Start offset: 0x000233DC
			// Variables:
		// 		struct SVECTOR cog; // stack offset -40
		// 		struct VECTOR modelLocation; // stack offset -32
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

// [D]
void DrawCarObject(CAR_MODEL *car, MATRIX *matrix, VECTOR *pos, VECTOR *pos1, int palette, _CAR_DATA *cp, int detail)
{
	static unsigned long savedSP;
	VECTOR modelLocation;
	SVECTOR cog;

	cog = cp->ap.carCos->cog;

	gte_SetRotMatrix(matrix);
	gte_SetTransVector(pos);

	gte_ldv0(&cog);

	docop2(0x480012);

	modelLocation.vx = MAC1;  //getCopReg(2, 0x19);
	modelLocation.vy = MAC2;  //getCopReg(2, 0x1a);
	modelLocation.vz = MAC3;  //getCopReg(2, 0x1b);

	TRX = modelLocation.vx;
	TRY = modelLocation.vy;
	TRZ = modelLocation.vz;

	savedSP = SetSp(0x1f800308);

	plotNewCarModel(car, palette);

	SetSp(savedSP);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawCarWheels(struct _CAR_DATA *cp /*$fp*/, struct MATRIX *RearMatrix /*stack 4*/, struct VECTOR *pos /*stack 8*/, int zclip /*$a3*/)
 // line 1850, offset 0x00021af8
	/* begin block 1 */
		// Start line: 1851
		// Start offset: 0x00021AF8
		// Variables:
	// 		struct CAR_COSMETICS *car_cos; // $s0
	// 		struct MATRIX FrontMatrix; // stack offset -144
	// 		struct MODEL *WheelModel; // $s0
	// 		struct MODEL *WheelModelBack; // stack offset -56
	// 		struct MODEL *WheelModelFront; // stack offset -52
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
		// 		struct SVECTOR *VertPtr; // $t6
		/* end block 1.2 */
		// End offset: 0x00021CD0
		// End Line: 1926

		/* begin block 1.3 */
			// Start line: 1926
			// Start offset: 0x00021CD0
			// Variables:
		// 		struct MATRIX SteerMatrix; // stack offset -112
		/* end block 1.3 */
		// End offset: 0x00021CD0
		// End Line: 1926

		/* begin block 1.4 */
			// Start line: 1988
			// Start offset: 0x00021FA4
			// Variables:
		// 		struct SVECTOR *verts; // $s5

			/* begin block 1.4.1 */
				// Start line: 2007
				// Start offset: 0x00021FF8
				// Variables:
			// 		struct VECTOR WheelPos; // stack offset -80
			// 		struct SVECTOR sWheelPos; // stack offset -64
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

void DrawCarWheels(_CAR_DATA *cp, MATRIX *RearMatrix, VECTOR *pos, int zclip)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	undefined4 in_zero;
	undefined4 in_at;
	short sVar3;
	int iVar4;
	uint wheelnum;
	int iVar5;
	short sVar6;
	int iVar7;
	short sVar8;
	short sVar9;
	undefined4 uVar10;
	undefined4 uVar11;
	undefined4 uVar12;
	MODEL *model;
	uint uVar13;
	SVECTOR *verts;
	undefined auStack144[32];
	short local_70;
	undefined2 local_6e;
	short local_6c;
	undefined2 local_6a;
	undefined2 local_68;
	undefined2 local_66;
	short local_64;
	undefined2 local_62;
	short local_60;
	int local_50;
	int local_4c;
	int local_48;
	short local_40;
	short local_3e;
	short local_3c;
	MODEL *local_38;
	MODEL *local_34;
	int *local_30;
	undefined4 *local_2c;

	local_2c = (undefined4 *)&local_40;
	local_30 = &local_50;
	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	iVar5 = (cp->hd).wheel_speed;
	if (iVar5 < 0) {
		iVar5 = iVar5 + 0xff;
	}
	iVar5 = iVar5 >> 8;
	sVar1 = car_cosmetics[(byte)(cp->ap).model].wheelSize;
	iVar7 = iVar5;
	if (cp->wheelspin != '\0') {
		iVar7 = -700;
	}
	if ((cp->hd).wheel[0].locked != '\0') {
		iVar5 = 0;
	}
	if ((cp->hd).wheel[3].locked != '\0') {
		iVar7 = 0;
	}
	if (pauseflag == 0) {
		iVar4 = ((int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2) * 2;
		*(ushort *)(&FrontWheelRotation_25 + iVar4) =
			*(ushort *)(&FrontWheelRotation_25 + iVar4) + (short)iVar5 & 0xfff;
		*(ushort *)(&BackWheelRotation_26 + iVar4) =
			*(ushort *)(&BackWheelRotation_26 + iVar4) + (short)iVar7 & 0xfff;
	}
	if (iVar5 + 400U < 0x321) {
		local_34 = gCleanWheelModelPtr;
	}
	else {
		local_34 = gFastWheelModelPtr;
	}
	if (iVar7 + 400U < 0x321) {
		local_38 = gCleanWheelModelPtr;
	}
	else {
		local_38 = gFastWheelModelPtr;
	}
	iVar7 = ((int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2) * 2;
	iVar5 = ((int)sVar1 * 0x373e) / 10000;
	sVar2 = rcossin_tbl[((uint)*(ushort *)(&FrontWheelRotation_25 + iVar7) & 0xfff) * 2];
	iVar4 = local_34->vertices;
	sVar8 = (short)(rcossin_tbl[((uint)*(ushort *)(&FrontWheelRotation_25 + iVar7) & 0xfff) * 2 + 1] *
		iVar5 >> 0xc);
	*(short *)(iVar4 + 0x42) = sVar8;
	*(short *)(iVar4 + 0x7a) = sVar8;
	sVar2 = (short)(sVar2 * iVar5 >> 0xc);
	sVar6 = -sVar2;
	*(short *)(iVar4 + 0x44) = sVar2;
	*(short *)(iVar4 + 0x7c) = sVar2;
	*(short *)(iVar4 + 0x4a) = sVar6;
	*(short *)(iVar4 + 0x72) = sVar6;
	*(short *)(iVar4 + 0x4c) = sVar8;
	sVar3 = -sVar8;
	*(short *)(iVar4 + 0x74) = sVar8;
	*(short *)(iVar4 + 0x52) = sVar3;
	*(short *)(iVar4 + 0x6a) = sVar3;
	*(short *)(iVar4 + 0x54) = sVar6;
	*(short *)(iVar4 + 0x6c) = sVar6;
	*(short *)(iVar4 + 0x5a) = sVar2;
	*(short *)(iVar4 + 0x62) = sVar2;
	*(short *)(iVar4 + 0x5c) = sVar3;
	*(short *)(iVar4 + 100) = sVar3;
	*(undefined2 *)(iVar4 + 0xbc) = 0;
	*(undefined2 *)(iVar4 + 0xb4) = 0;
	*(undefined2 *)(iVar4 + 0xaa) = 0;
	*(undefined2 *)(iVar4 + 0xa2) = 0;
	*(undefined2 *)(iVar4 + 0x9a) = 0;
	*(undefined2 *)(iVar4 + 0x92) = 0;
	*(undefined2 *)(iVar4 + 0x8c) = 0;
	*(undefined2 *)(iVar4 + 0x84) = 0;
	*(short *)(iVar4 + 0xba) = sVar1;
	sVar8 = -sVar1;
	*(short *)(iVar4 + 0xb2) = sVar1;
	*(short *)(iVar4 + 0xac) = sVar1;
	*(short *)(iVar4 + 0xa4) = sVar1;
	*(short *)(iVar4 + 0x9c) = sVar8;
	*(short *)(iVar4 + 0x94) = sVar8;
	*(short *)(iVar4 + 0x8a) = sVar8;
	*(short *)(iVar4 + 0x82) = sVar8;
	sVar2 = rcossin_tbl[((uint)*(ushort *)(&BackWheelRotation_26 + iVar7) & 0xfff) * 2];
	iVar4 = local_38->vertices;
	sVar9 = (short)(rcossin_tbl[((uint)*(ushort *)(&BackWheelRotation_26 + iVar7) & 0xfff) * 2 + 1] *
		iVar5 >> 0xc);
	*(short *)(iVar4 + 0x42) = sVar9;
	*(short *)(iVar4 + 0x7a) = sVar9;
	sVar2 = (short)(sVar2 * iVar5 >> 0xc);
	sVar6 = -sVar2;
	*(short *)(iVar4 + 0x44) = sVar2;
	*(short *)(iVar4 + 0x7c) = sVar2;
	*(short *)(iVar4 + 0x4a) = sVar6;
	*(short *)(iVar4 + 0x72) = sVar6;
	*(short *)(iVar4 + 0x4c) = sVar9;
	sVar3 = -sVar9;
	*(short *)(iVar4 + 0x74) = sVar9;
	*(short *)(iVar4 + 0x52) = sVar3;
	*(short *)(iVar4 + 0x6a) = sVar3;
	*(short *)(iVar4 + 0x54) = sVar6;
	*(short *)(iVar4 + 0x6c) = sVar6;
	*(short *)(iVar4 + 0x5a) = sVar2;
	*(short *)(iVar4 + 0x62) = sVar2;
	*(short *)(iVar4 + 0x5c) = sVar3;
	*(short *)(iVar4 + 100) = sVar3;
	*(undefined2 *)(iVar4 + 0xbc) = 0;
	*(undefined2 *)(iVar4 + 0xb4) = 0;
	*(undefined2 *)(iVar4 + 0xaa) = 0;
	*(undefined2 *)(iVar4 + 0xa2) = 0;
	*(undefined2 *)(iVar4 + 0x9a) = 0;
	*(undefined2 *)(iVar4 + 0x92) = 0;
	*(undefined2 *)(iVar4 + 0x8c) = 0;
	*(undefined2 *)(iVar4 + 0x84) = 0;
	*(short *)(iVar4 + 0xba) = sVar1;
	*(short *)(iVar4 + 0xb2) = sVar1;
	*(short *)(iVar4 + 0xac) = sVar1;
	*(short *)(iVar4 + 0xa4) = sVar1;
	*(short *)(iVar4 + 0x9c) = sVar8;
	*(short *)(iVar4 + 0x94) = sVar8;
	*(short *)(iVar4 + 0x8a) = sVar8;
	*(short *)(iVar4 + 0x82) = sVar8;
	wheelnum = (uint)(ushort)cp->wheel_angle & 0xfff;
	local_70 = rcossin_tbl[wheelnum * 2 + 1];
	local_6c = rcossin_tbl[wheelnum * 2];
	local_68 = 0x1000;
	local_62 = 0;
	local_66 = 0;
	local_6a = 0;
	local_6e = 0;
	local_64 = -local_6c;
	local_60 = local_70;
	MulMatrix0(RearMatrix, &local_70, auStack144);
	wheelnum = 0;
	do {
		model = local_34;
		if ((wheelnum & 1) != 0) {
			model = local_38;
		}
		verts = (SVECTOR *)model->vertices;
		if ((cp->controlType == '\x01') && (gHubcap.Present[3 - wheelnum] == 0)) {
			model = gDamWheelModelPtr;
		}
		setCopControlWord(2, 0, *(undefined4 *)RearMatrix->m);
		setCopControlWord(2, 1, *(undefined4 *)(RearMatrix->m + 2));
		setCopControlWord(2, 2, *(undefined4 *)(RearMatrix->m + 4));
		setCopControlWord(2, 3, *(undefined4 *)(RearMatrix->m + 6));
		setCopControlWord(2, 4, *(undefined4 *)(RearMatrix->m + 8));
		setCopReg(2, 0, *local_2c);
		setCopReg(2, 1, local_2c[1]);
		copFunction(2, 0x486012);
		uVar10 = getCopReg(2, 9);
		uVar11 = getCopReg(2, 10);
		uVar12 = getCopReg(2, 11);
		local_40 = (short)uVar10;
		local_3e = (short)uVar11;
		local_3c = (short)uVar12;
		local_50 = (int)local_40 + pos->vx;
		local_4c = (int)local_3e + pos->vy;
		local_48 = (int)local_3c + pos->vz;
		setCopControlWord(2, 5, *local_30);
		setCopControlWord(2, 6, local_30[1]);
		setCopControlWord(2, 7, local_30[2]);
		if ((wheelnum & 1) == 0) {
			SetRotMatrix(auStack144);
		}
		uVar13 = wheelnum + 1;
		DrawWheelObject(model, verts, (uint)(byte)TransparentObject, wheelnum);
		wheelnum = uVar13;
	} while ((int)uVar13 < 4);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawWheelObject(struct MODEL *model /*$t2*/, struct SVECTOR *verts /*$t4*/, int transparent /*$a2*/, int wheelnum /*$a3*/)
 // line 2058, offset 0x00022180
	/* begin block 1 */
		// Start line: 2059
		// Start offset: 0x00022180
		// Variables:
	// 		struct POLY_FT4 *prims; // $t0
	// 		struct POLYFT4LIT *src; // $t1
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

void DrawWheelObject(MODEL *model, SVECTOR *verts, int transparent, int wheelnum)
{
	UNIMPLEMENTED();
	/*
	undefined2 uVar1;
	ushort uVar2;
	int iVar3;
	int iVar4;
	undefined4 in_zero;
	undefined4 in_at;
	byte bVar5;
	undefined4 *puVar6;
	uint uVar7;
	undefined4 *puVar8;
	uint uVar9;
	uint uVar10;
	SVECTOR *pSVar11;
	uint *puVar12;
	int iVar13;
	uint in_t5;
	uint in_t6;

	iVar13 = model->poly_block;
	puVar12 = (uint *)current->primptr;
	uVar1 = (&texture_cluts)[(uint)*(byte *)(iVar13 + 1) * 0x20 + (uint)*(byte *)(iVar13 + 2)];
	uVar2 = (&texture_pages)[(uint)*(byte *)(iVar13 + 1)];
	if (-1 < gTimeOfDay) {
		if (gTimeOfDay < 3) {
			in_t6 = combointensity & 0xffffffU | 0x2c000000;
			in_t5 = (int)(combointensity & 0xfcfcfcU) >> 2 | 0x2c000000;
		}
		else {
			if (gTimeOfDay == 3) {
				uVar7 = (combointensity & 0xffU) / 3;
				uVar7 = uVar7 << 0x10 | uVar7 << 8 | uVar7;
				in_t6 = uVar7 | 0x2c000000;
				in_t5 = (int)(uVar7 & 0xfcfcfc) >> 2 | 0x2c000000;
			}
		}
	}
	uVar7 = (uint)model->num_polys;
	while (uVar7 = uVar7 - 1, uVar7 != 0xffffffff) {
		uVar10 = *(uint *)(iVar13 + 4);
		pSVar11 = verts + (uVar10 & 0xff);
		puVar8 = (undefined4 *)((int)&verts->vx + ((int)uVar10 >> 5 & 0x7f8U));
		puVar6 = (undefined4 *)((int)&verts->vx + ((int)uVar10 >> 0xd & 0x7f8U));
		setCopReg(2, 0, *(undefined4 *)pSVar11);
		setCopReg(2, 1, *(undefined4 *)&pSVar11->vz);
		setCopReg(2, 2, *puVar8);
		setCopReg(2, 3, puVar8[1]);
		setCopReg(2, 4, *puVar6);
		setCopReg(2, 5, puVar6[1]);
		copFunction(2, 0x280030);
		copFunction(2, 0x1400006);
		iVar3 = getCopReg(2, 24);
		uVar9 = getCopReg(2, 12);
		puVar12[2] = uVar9;
		setCopReg(2, 0, *(undefined4 *)(verts + (uVar10 >> 0x18)));
		setCopReg(2, 1, *(undefined4 *)&verts[uVar10 >> 0x18].vz);
		copFunction(2, 0x180001);
		copFunction(2, 0x168002e);
		iVar4 = getCopReg(2, 7);
		if (2 < iVar4) {
			uVar9 = (current->ot + (iVar4 >> 1))[9];
			(current->ot + (iVar4 >> 1))[9] = (uint)puVar12 & 0xffffff;
			*puVar12 = uVar9 & 0xffffff | 0x9000000;
			if (((int)uVar7 < 2) || (iVar3 < 0)) {
				puVar12[1] = 0x2c000000;
			}
			else {
				if (((uVar7 ^ wheelnum >> 1) & 1) == 0) {
					puVar12[1] = in_t5;
				}
				else {
					puVar12[1] = in_t6;
				}
			}
			if (transparent == 0) {
				bVar5 = *(byte *)((int)puVar12 + 7) & 0xfd;
			}
			else {
				bVar5 = *(byte *)((int)puVar12 + 7) | 2;
			}
			*(byte *)((int)puVar12 + 7) = bVar5;
			puVar12[3] = CONCAT22(uVar1, *(undefined2 *)(iVar13 + 8));
			uVar9 = getCopReg(2, 12);
			puVar12[4] = uVar9;
			puVar12[5] = (uint)*(ushort *)(iVar13 + 10) | ((uint)uVar2 | 0x20) << 0x10;
			uVar9 = getCopReg(2, 14);
			puVar12[6] = uVar9;
			puVar12[7] = (uint)*(ushort *)(iVar13 + 0xe);
			uVar9 = getCopReg(2, 13);
			puVar12[8] = uVar9;
			puVar12[9] = (uint)*(ushort *)(iVar13 + 0xc);
			puVar12 = puVar12 + 10;
		}
		iVar13 = iVar13 + 0x14;
	}
	*(uint **)&current->primptr = puVar12;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlayerCarFX(struct _CAR_DATA *cp /*$s0*/)
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

void PlayerCarFX(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	int iVar1;

	iVar1 = (cp->hd).wheel_speed;
	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	if ((iVar1 < 1) || (-1 < cp->thrust)) {
		if (-1 < iVar1) goto LAB_00023598;
		if (0 < cp->thrust) goto LAB_0002356c;
	}
	else {
	LAB_0002356c:
		AddBrakeLight(cp);
	}
	if ((iVar1 < 0) && (cp->thrust < 0)) {
		AddReverseLight(cp);
	}
LAB_00023598:
	if (iVar1 + 199U < 0x4b0c7) {
		if (cp->wheel_angle < 0xc9) {
			if (cp->wheel_angle < -200) {
				AddIndicatorLight(cp, 0);
			}
		}
		else {
			AddIndicatorLight(cp, 1);
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ComputeCarLightingLevels(struct _CAR_DATA *cp /*$s1*/, char detail /*$s3*/)
 // line 2198, offset 0x00022458
	/* begin block 1 */
		// Start line: 2199
		// Start offset: 0x00022458
		// Variables:
	// 		int light; // $s2
	// 		struct SVECTOR lightsourcevector; // stack offset -96
	// 		struct SVECTOR colour; // stack offset -88
	// 		struct VECTOR lightValues; // stack offset -80
	// 		struct VECTOR *orient; // $s0

		/* begin block 1.1 */
			// Start line: 2270
			// Start offset: 0x0002270C
			// Variables:
		// 		struct MODEL *model; // $v1
		// 		struct SVECTOR *norms; // $a3
		// 		struct SVECTOR *ppads; // $a2
		// 		int num_norms; // $a1
		// 		int count; // $a1
		// 		struct CVECTOR c0; // stack offset -64
		// 		struct CVECTOR c1; // stack offset -56
		// 		struct CVECTOR c2; // stack offset -48

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

int lightning = 0;

// [D]
void ComputeCarLightingLevels(_CAR_DATA *cp, char detail)
{
	MATRIX scratchPadMat; // 0x1f800344

	unsigned char bVar1;
	bool bVar2;
	//undefined4 in_zero;
	//undefined4 in_at;
	int iVar3;
	uint uVar4;
	int iVar5;
	MODEL **ppMVar6;
	uint uVar7;
	int iVar8;
	uint uVar9;
	int iVar10;
	uint uVar11;
	//undefined4 in_a2;
	SVECTOR *pSVar12;
	SVECTOR *local_a3_900;
	SVECTOR lightsourcevector;
	SVECTOR colour;
	VECTOR lightValues;
	CVECTOR c0;
	CVECTOR c1;
	CVECTOR c2;
	long GT3rgb;

	if (cp < car_data)
	{
		while (FrameCnt != 0x78654321)
			trap(0x400);
	}

	if (-1 < gTimeOfDay)
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
	docop2(0x486012);

	light_matrix.m[0][0] = IR1;
	light_matrix.m[0][1] = IR2;
	light_matrix.m[0][2] = IR3;

	bVar2 = false;

	colour_matrix.m[0][0] = colour.vx;
	colour_matrix.m[1][0] = colour.vy;
	colour_matrix.m[2][0] = colour.vz;

	if (gTimeOfDay != 3)
	{
		iVar8 = cp->ap.qy;
		iVar3 = cp->st.n.orientation[1];
		iVar5 = iVar3 - iVar8;
		if (iVar5 < 1) 
			iVar5 = iVar8 - iVar3;

		iVar10 = cp->ap.qw;
		iVar8 = cp->st.n.orientation[3];
		iVar3 = iVar8 - iVar10;

		if (iVar3 < 1) 
			iVar3 = iVar10 - iVar8;

		if ((200 < iVar5 + iVar3) || (cp->lowDetail != (detail | lightning)))
			bVar2 = true;

		if (((gTimeOfDay == 0) || (gTimeOfDay == 2)) && ((cp->id & 0xf) == (CameraCnt & 0xfU))) 
			bVar2 = true;

		setupLightingMatrices();

		//if (bVar2) 
		{
			MTC2(combointensity & 0xffffffU | 0x34000000, 6);

			cp->ap.qy = *(short *)(cp->st.n.orientation + 1);
			cp->ap.qw = *(short *)(cp->st.n.orientation + 3);
			cp->lowDetail = detail | lightning;

			if (detail == 0) 
			{
				bVar1 = cp->ap.model;
				ppMVar6 = gCarLowModelPtr;
			}
			else 
			{
				bVar1 = cp->ap.model;
				ppMVar6 = gCarCleanModelPtr;
			}

			uVar9 = (int)(uint)ppMVar6[bVar1]->num_point_normals / 3;
			local_a3_900 = (SVECTOR *)ppMVar6[bVar1]->point_normals;

			uVar7 = cp->id * 0x420;

			pSVar12 = gTempCarVertDump[cp->id];
			uVar4 = uVar9 + 1;
			uVar11 = uVar4;

			if (0 < (int)uVar4)
			{
				do
				{
					gte_ldv3(&local_a3_900[0], &local_a3_900[1], &local_a3_900[2]);

					docop2(0x118043f);

					*(uint*)&c0 = RGB0;
					*(uint*)&c1 = RGB1;
					*(uint*)&c2 = RGB2;

					//c0 = (short)uVar4;
					//uVar4 = uVar4 & 0xffff;
					//c1._0_2_ = (short)uVar7;
					//uVar7 = uVar7 & 0xffff;
					//c2._0_2_ = (short)uVar9;
					//uVar9 = uVar9 & 0xffff;
					
					pSVar12[0].pad = *(short*)&c0;
					pSVar12[1].pad = *(short*)&c1;
					pSVar12[2].pad = *(short*)&c2;

					uVar11--;
					local_a3_900 += 3;
					pSVar12 += 3;

				} while (uVar11 != 0);
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

// [D]
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
// void /*$ra*/ buildNewCarFromModel(struct CAR_MODEL *car /*$s5*/, struct MODEL *model /*$s7*/, int first /*$a2*/)
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
		// 		struct CAR_POLY *p; // $s1
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

// byte swapped int
#define SW_INT(a,b) (((a) << 16) | (b))

// [D]
void buildNewCarFromModel(CAR_MODEL *car, MODEL *model, int first)
{

	char bVar1;
	char bVar2;
	char bVar3;
	char bVar4;
	ushort uVar5;
	char cVar6;
	//undefined3 extraout_var;
	//undefined3 extraout_var_00;
	uint uVar7;
	int iVar8;
	char *pbVar9;
	CAR_POLY *pCVar10;
	int iVar11;
	int iVar12;
	short sVar13;
	int iVar14;
	int iVar15;
	int iVar16;

	if (first != 0) {
		whichCP = 0;
	}
	if ((model == NULL) || (0x800000 < ((uint)model->shape_flags & 0xfffffff))) 
	{
		car->numGT3 = 0;
		car->numFT3 = 0;
		car->numB3 = 0;
	}
	else 
	{
		car->vlist = (SVECTOR *)model->vertices;
		car->nlist = (SVECTOR *)model->point_normals;

		iVar15 = 0;

		do {
			iVar11 = whichCP;
			pbVar9 = (char *)model->poly_block;

			if (iVar15 == 1) {
				car->pFT3 = carPolyBuffer + whichCP;
			}
			else if (iVar15 == 0) {
				car->pGT3 = carPolyBuffer + whichCP;
			}
			else if (iVar15 == 2) {
				car->pB3 = carPolyBuffer + whichCP;
			}

			iVar14 = 0;
			iVar16 = iVar15 + 1;
			iVar12 = iVar11;

			if ((iVar11 < 2000) && (model->num_polys != 0)) 
			{
				do {
					bVar1 = *pbVar9;
					pCVar10 = carPolyBuffer + iVar11;
					iVar12 = iVar11;

					if (true) 
					{
						sVar13 = (short)iVar14;
						switch ((uint)bVar1 & 0x1f) 
						{
							case 0:
							case 0x12:
								if (iVar15 == 2) 
								{
									bVar2 = pbVar9[1];
									bVar3 = pbVar9[2];
									bVar4 = pbVar9[3];
									iVar12 = iVar11 + 1;
									carPolyBuffer[iVar11].originalindex = sVar13;
									pCVar10->vindices = (uint)bVar2 + ((uint)bVar3 + (uint)bVar4 * 0x100) * 0x100;
								}
								break;
							case 1:
							case 0x13:
								if (iVar15 == 2) 
								{
									bVar2 = pbVar9[4];
									bVar3 = pbVar9[5];
									bVar4 = pbVar9[6];
									iVar12 = iVar11 + 2;
									carPolyBuffer[iVar11].originalindex = sVar13;
									pCVar10->vindices = (uint)bVar2 + ((uint)bVar3 + (uint)bVar4 * 0x100) * 0x100;
									bVar2 = pbVar9[4];
									bVar3 = pbVar9[6];
									bVar4 = pbVar9[7];
									carPolyBuffer[iVar11 + 1].originalindex = sVar13;
									carPolyBuffer[iVar11 + 1].vindices = (uint)bVar2 + ((uint)bVar3 + (uint)bVar4 * 0x100) * 0x100;
								}
								break;
							case 0x14:
								if (iVar15 == 1) 
								{
									pCVar10->vindices = (uint)pbVar9[4] + ((uint)pbVar9[5] + (uint)pbVar9[6] * 0x100) * 0x100;

									carPolyBuffer[iVar11].clut_uv0 = SW_INT(((ushort*)texture_cluts)[(uint)pbVar9[1] * 0x20 + (uint)pbVar9[2]], *(ushort *)(pbVar9 + 8));
									carPolyBuffer[iVar11].tpage_uv1 = SW_INT(texture_pages[pbVar9[1]], *(ushort *)(pbVar9 + 10));

									uVar7 = (uint)*(ushort *)(pbVar9 + 0xc);
									iVar12 = iVar11 + 1;
								LAB_00022fd4:
									pCVar10->originalindex = sVar13;
								LAB_00022fd8:
									pCVar10->uv3_uv2 = uVar7;
								}
								break;
							case 0x15:
								if (iVar15 == 1) 
								{
									pCVar10->vindices = (uint)pbVar9[4] + ((uint)pbVar9[5] + (uint)pbVar9[6] * 0x100) * 0x100;

									carPolyBuffer[iVar11].clut_uv0 = SW_INT(((ushort*)texture_cluts)[(uint)pbVar9[1] * 0x20 + (uint)pbVar9[2]], *(ushort *)(pbVar9 + 8));
									carPolyBuffer[iVar11].tpage_uv1 = SW_INT(texture_pages[pbVar9[1]], *(ushort *)(pbVar9 + 10));

									uVar5 = *(ushort *)(pbVar9 + 0xc);
									carPolyBuffer[iVar11].originalindex = sVar13;
									carPolyBuffer[iVar11].uv3_uv2 = (uint)uVar5;
									pCVar10 = carPolyBuffer + iVar11 + 1;
									pCVar10->vindices = (uint)pbVar9[4] + ((uint)pbVar9[6] + (uint)pbVar9[7] * 0x100) * 0x100;

									carPolyBuffer[iVar11 + 1].clut_uv0 = SW_INT(((ushort*)texture_cluts)[(uint)pbVar9[1] * 0x20 + (uint)pbVar9[2]], *(ushort *)(pbVar9 + 8));
									carPolyBuffer[iVar11 + 1].tpage_uv1 = SW_INT(texture_pages[pbVar9[1]], *(ushort *)(pbVar9 + 0xc));

									uVar7 = (uint)*(ushort *)(pbVar9 + 0xe);
									iVar12 = iVar11 + 2;
									goto LAB_00022fd4;
								}
								break;
							case 0x16:
								if (iVar15 == 0) 
								{
									iVar12 = iVar11 + 1;
									cVar6 = GetCarPalIndex((uint)pbVar9[1]);

									((ushort*)civ_clut)[cVar6 * 0xc0 + (uint)pbVar9[2] * 6] = ((ushort*)texture_cluts)[(uint)pbVar9[1] * 0x20 + (uint)pbVar9[2]];
									pCVar10->vindices = (uint)pbVar9[4] + ((uint)pbVar9[5] + (uint)pbVar9[6] * 0x100) * 0x100;
									
									carPolyBuffer[iVar11].nindices = (uint)pbVar9[8] + ((uint)pbVar9[9] + (uint)pbVar9[10] * 0x100) * 0x100;
									carPolyBuffer[iVar11].clut_uv0 = ((int)(cVar6 * 0x180 + (uint)pbVar9[2] * 0xc + -0x180) >> 1) << 0x10 | (uint)*(ushort *)(pbVar9 + 0xc);
									carPolyBuffer[iVar11].tpage_uv1 = SW_INT(texture_pages[pbVar9[1]], *(ushort *)(pbVar9 + 0xe));
									
									uVar7 = (uint)*(ushort *)(pbVar9 + 0x10);
									carPolyBuffer[iVar11].originalindex = sVar13;
									goto LAB_00022fd8;
								}
								break;
							case 0x17:
								if (iVar15 == 0) 
								{
									iVar12 = iVar11 + 2;
									cVar6 = GetCarPalIndex((uint)pbVar9[1]);
									iVar8 = cVar6 * 0x180;

									*((ushort*)civ_clut[cVar6 * 0xc0 + (uint)pbVar9[2] * 6]) = ((ushort*)texture_cluts)[(uint)pbVar9[1] * 0x20 + (uint)pbVar9[2]];

									pCVar10->vindices = (uint)pbVar9[4] + ((uint)pbVar9[5] + (uint)pbVar9[6] * 0x100) * 0x100;

									carPolyBuffer[iVar11].nindices = (uint)pbVar9[8] + ((uint)pbVar9[9] + (uint)pbVar9[10] * 0x100) * 0x100;
									carPolyBuffer[iVar11].clut_uv0 = ((int)(iVar8 + (uint)pbVar9[2] * 0xc + -0x180) >> 1) << 0x10 | (uint)*(ushort *)(pbVar9 + 0xc);
									carPolyBuffer[iVar11].tpage_uv1 = SW_INT(texture_pages[pbVar9[1]], *(ushort *)(pbVar9 + 0xe));

									uVar5 = *(ushort *)(pbVar9 + 0x10);
									carPolyBuffer[iVar11].originalindex = sVar13;
									carPolyBuffer[iVar11].uv3_uv2 = (uint)uVar5;
									pCVar10 = carPolyBuffer + iVar11 + 1;
									pCVar10->vindices = (uint)pbVar9[4] + ((uint)pbVar9[6] + (uint)pbVar9[7] * 0x100) * 0x100;

									carPolyBuffer[iVar11 + 1].nindices = (uint)pbVar9[8] + ((uint)pbVar9[10] + (uint)pbVar9[0xb] * 0x100) * 0x100;
									carPolyBuffer[iVar11 + 1].clut_uv0 = ((int)(iVar8 + (uint)pbVar9[2] * 0xc + -0x180) >> 1) << 0x10 | (uint)*(ushort *)(pbVar9 + 0xc);
									carPolyBuffer[iVar11 + 1].tpage_uv1 = SW_INT(texture_pages[pbVar9[1]], *(ushort *)(pbVar9 + 0x10));

									uVar7 = (uint)*(ushort *)(pbVar9 + 0x12);
									goto LAB_00022fd4;
								}
						}
					}

					iVar14 = iVar14 + 1;
					pbVar9 = pbVar9 + PolySizes[(uint)bVar1 & 0x1f];

				} while ((iVar12 < 2000) && (iVar11 = iVar12, iVar14 < (int)(uint)model->num_polys));
			}

			if (iVar15 == 1) 
			{
				car->numFT3 = iVar12 - whichCP;
			}
			if (iVar15 == 0)
			{
				car->numGT3 = iVar12 - whichCP;
			}
			else if (iVar15 == 2) 
			{
				car->numB3 = iVar12 - whichCP;
			}

			iVar15 = iVar16;
			whichCP = iVar12;
		} while (iVar16 < 3);
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
	// 		struct MODEL *m; // $t0
	// 		struct POLYFT4LIT *src; // $a0

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

void MangleWheelModels(void)
{
	UNIMPLEMENTED();
	/*
	undefined2 uVar1;
	char cVar2;
	int iVar3;
	undefined4 *puVar4;
	MODEL *pMVar5;
	int iVar6;

	iVar3 = 0;
	do {
		pMVar5 = gCleanWheelModelPtr;
		if (((iVar3 != 1) && (pMVar5 = gFastWheelModelPtr, 1 < iVar3)) && (iVar3 == 2)) {
			pMVar5 = gDamWheelModelPtr;
		}
		iVar3 = iVar3 + 1;
		puVar4 = (undefined4 *)pMVar5->poly_block;
		iVar6 = 1;
		*puVar4 = puVar4[10];
		puVar4[1] = puVar4[0xb];
		puVar4[2] = puVar4[0xc];
		puVar4[3] = puVar4[0xd];
		puVar4[4] = puVar4[0xe];
		puVar4[5] = puVar4[0xf];
		puVar4[6] = puVar4[0x10];
		puVar4[7] = puVar4[0x11];
		puVar4[8] = puVar4[0x12];
		puVar4[9] = puVar4[0x13];
		puVar4[10] = puVar4[0x14];
		puVar4[0xb] = puVar4[0x15];
		puVar4[0xc] = puVar4[0x16];
		puVar4[0xd] = puVar4[0x17];
		puVar4[0xe] = puVar4[0x18];
		puVar4[0xf] = puVar4[0x1e];
		puVar4[0x10] = puVar4[0x1f];
		puVar4[0x11] = puVar4[0x20];
		puVar4[0x12] = puVar4[0x21];
		puVar4[0x13] = puVar4[0x22];
		*(undefined *)(puVar4 + 0xb) = 0x10;
		*(undefined *)((int)puVar4 + 0x2d) = 0x11;
		*(undefined *)((int)puVar4 + 0x2e) = 0x17;
		*(undefined *)((int)puVar4 + 0x2f) = 0x16;
		*(undefined *)(puVar4 + 0x10) = 0x15;
		*(undefined *)((int)puVar4 + 0x41) = 0x14;
		*(undefined *)((int)puVar4 + 0x43) = 0x12;
		*(undefined *)((int)puVar4 + 0x42) = 0x13;
		cVar2 = (*(byte *)(puVar4 + 2) >> 1) + (*(byte *)(puVar4 + 3) >> 1);
		*(char *)((int)puVar4 + 0x4a) = cVar2;
		*(char *)(puVar4 + 0x12) = cVar2;
		*(char *)((int)puVar4 + 0x46) = cVar2;
		*(char *)(puVar4 + 0x11) = cVar2;
		*(char *)((int)puVar4 + 0x36) = cVar2;
		*(char *)(puVar4 + 0xd) = cVar2;
		*(char *)((int)puVar4 + 0x32) = cVar2;
		*(char *)(puVar4 + 0xc) = cVar2;
		cVar2 = (*(byte *)((int)puVar4 + 9) >> 1) + (*(byte *)((int)puVar4 + 0xd) >> 1);
		*(char *)((int)puVar4 + 0x4b) = cVar2;
		*(char *)((int)puVar4 + 0x49) = cVar2;
		*(char *)((int)puVar4 + 0x47) = cVar2;
		*(char *)((int)puVar4 + 0x45) = cVar2;
		*(char *)((int)puVar4 + 0x37) = cVar2;
		*(char *)((int)puVar4 + 0x35) = cVar2;
		*(char *)((int)puVar4 + 0x33) = cVar2;
		*(char *)((int)puVar4 + 0x31) = cVar2;
		pMVar5->num_polys = 4;
		do {
			uVar1 = *(undefined2 *)(puVar4 + 2);
			iVar6 = iVar6 + -1;
			*(undefined2 *)(puVar4 + 2) = *(undefined2 *)((int)puVar4 + 10);
			*(undefined2 *)((int)puVar4 + 10) = *(undefined2 *)(puVar4 + 3);
			*(undefined2 *)(puVar4 + 3) = *(undefined2 *)((int)puVar4 + 0xe);
			*(undefined2 *)((int)puVar4 + 0xe) = uVar1;
			puVar4 = puVar4 + 5;
		} while (-1 < iVar6);
	} while (iVar3 < 3);

	// HACK: Show clean model only in Rio.
	if (GameLevel == 3) {
		gFastWheelModelPtr = gCleanWheelModelPtr;
	}
	return;*/
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

// [D]
void setupLightingMatrices(void)
{
	gte_ReadColorMatrix(&save_colour_matrix);
	gte_ReadLightMatrix(&save_light_matrix);

	gte_SetColorMatrix(&colour_matrix);
	gte_SetLightMatrix(&light_matrix);

	if (gTimeOfDay == 3) 
	{
		RBK = 0x400;
		GBK = 0x400;
		BBK = 0x400;
		return;
	}

	RBK = 0x8c0;
	GBK = 0x8c0;
	BBK = 0x8c0;
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

// [D]
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

// [D]
char GetCarPalIndex(int tpage)
{
	for (int i = 0; i < 8; i++) {
		if (tpage == carTpages[GameLevel][i])
			return (char)i;
	}

	return 0;
}





