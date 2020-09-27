#include "DRIVER2.H"
#include "JOB_FX.H"
#include "BOMBERMAN.H"
#include "PAUSE.H"
#include "GAMESND.H"
#include "CARS.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "DEBRIS.H"
#include "SYSTEM.H"
#include "..\ASM\ASMTEST.H"

#include "INLINE_C.H"

MATRIX SS = { 0 };

// decompiled code
// original method signature: 
// void /*$ra*/ InitExObjects()
 // line 110, offset 0x00057b0c
	/* begin block 1 */
		// Start line: 112
		// Start offset: 0x00057B0C
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x00057B50
	// End Line: 121

	/* begin block 2 */
		// Start line: 1292
	/* end block 2 */
	// End Line: 1293

	/* begin block 3 */
		// Start line: 220
	/* end block 3 */
	// End Line: 221

	/* begin block 4 */
		// Start line: 1293
	/* end block 4 */
	// End Line: 1294

	/* begin block 5 */
		// Start line: 1295
	/* end block 5 */
	// End Line: 1296

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitExObjects(void)
{
	int i;

	for (i = 0; i < 5; i++)
		explosion[i].time = -1;

	initExplosion();
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddExplosion(struct VECTOR pos /*stack 0*/, int type /*stack 16*/)
 // line 129, offset 0x00056d54
	/* begin block 1 */
		// Start line: 130
		// Start offset: 0x00056D54
		// Variables:
	// 		int i; // $t1
	/* end block 1 */
	// End offset: 0x00056E44
	// End Line: 169

	/* begin block 2 */
		// Start line: 258
	/* end block 2 */
	// End Line: 259

	/* begin block 3 */
		// Start line: 263
	/* end block 3 */
	// End Line: 264

// [D]
void AddExplosion(VECTOR pos, int type)
{
	_ExOBJECT *newExplosion;
	int i;

	i = 0;
	newExplosion = explosion;

	while (newExplosion->time != -1) 
	{
		i++;
		newExplosion++;

		if (i > 4) 
			return;
	}

	newExplosion->time = 0;
	newExplosion->pos = pos;
	newExplosion->type = (ExplosionType)type;

	if (type == LITTLE_BANG) 
	{
		newExplosion->speed = 0xc0;
		newExplosion->hscale = 0x400;
		newExplosion->rscale = 0x400;
	}
	else if (type == BIG_BANG)
	{
		newExplosion->speed = 0x80;
		newExplosion->hscale = 0x1000;
		newExplosion->rscale = 0x1000;
	}
	else if (type == HEY_MOMMA)
	{
		newExplosion->speed = 0x40;
		newExplosion->hscale = 0x4000;
		newExplosion->rscale = 0x4000;
	}

}



// decompiled code
// original method signature: 
// void /*$ra*/ HandleExplosion()
 // line 178, offset 0x00056e44
	/* begin block 1 */
		// Start line: 180
		// Start offset: 0x00056E44
		// Variables:
	// 		int i; // $s5
	// 		struct _CAR_DATA *cp; // $s0

		/* begin block 1.1 */
			// Start line: 212
			// Start offset: 0x00056F4C
		/* end block 1.1 */
		// End offset: 0x00056F84
		// End Line: 220
	/* end block 1 */
	// End offset: 0x00056F94
	// End Line: 223

	/* begin block 2 */
		// Start line: 387
	/* end block 2 */
	// End Line: 388

	/* begin block 3 */
		// Start line: 397
	/* end block 3 */
	// End Line: 398

	/* begin block 4 */
		// Start line: 398
	/* end block 4 */
	// End Line: 399

	/* begin block 5 */
		// Start line: 402
	/* end block 5 */
	// End Line: 403

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void HandleExplosion(void)
{
	_CAR_DATA *cp;
	_ExOBJECT *exp;
	int i;

	if (pauseflag != 0)
		return;

	i = 0;
	exp = explosion;

	while (i < 5)
	{
		if (exp->time != -1 && exp->type != BANG_USED) 
		{
			cp = car_data;

			do {
				if (cp == &car_data[20] || cp != gBombTargetVehicle && cp->controlType != CONTROL_TYPE_NONE)
					ExplosionCollisionCheck(cp, &explosion[i]);

				cp++;
			} while (cp < &car_data[20]);
		}

		i++;
		exp++;
	};

	
	i = 0;
	exp = explosion;
	while (i < 5)
	{
		if (exp->time != -1)
		{
			if (exp->time == 0)
				ExplosionSound(&exp->pos, exp->type);

			exp->time += exp->speed;

			if (exp->time > 0xfff)
				exp->time = -1;
		}

		exp++;
		i++;
	};
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawAllExplosions()
 // line 232, offset 0x00057b50
	/* begin block 1 */
		// Start line: 234
		// Start offset: 0x00057B50
		// Variables:
	// 		int i; // $s1

		/* begin block 1.1 */
			// Start line: 240
			// Start offset: 0x00057B94
			// Variables:
		// 		int hscale; // $v1
		// 		int rscale; // $a0
		/* end block 1.1 */
		// End offset: 0x00057BC0
		// End Line: 244
	/* end block 1 */
	// End offset: 0x00057BF0
	// End Line: 246

	/* begin block 2 */
		// Start line: 1426
	/* end block 2 */
	// End Line: 1427

	/* begin block 3 */
		// Start line: 1538
	/* end block 3 */
	// End Line: 1539

	/* begin block 4 */
		// Start line: 1539
	/* end block 4 */
	// End Line: 1540

	/* begin block 5 */
		// Start line: 1541
	/* end block 5 */
	// End Line: 1542

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DrawAllExplosions(void)
{
	int i;
	i = 0;
	while (i < 5)
	{
		if (explosion[i].time != -1)
			DrawExplosion(explosion[i].time, explosion[i].pos, explosion[i].hscale, explosion[i].rscale);

		i++;
	};
}



// decompiled code
// original method signature: 
// void /*$ra*/ initExplosion()
 // line 557, offset 0x00056fc0
	/* begin block 1 */
		// Start line: 559
		// Start offset: 0x00056FC0
		// Variables:
	// 		int i; // $t0
	/* end block 1 */
	// End offset: 0x000572A8
	// End Line: 582

	/* begin block 2 */
		// Start line: 1167
	/* end block 2 */
	// End Line: 1168

	/* begin block 3 */
		// Start line: 1180
	/* end block 3 */
	// End Line: 1181

	/* begin block 4 */
		// Start line: 1181
	/* end block 4 */
	// End Line: 1182

	/* begin block 5 */
		// Start line: 1189
	/* end block 5 */
	// End Line: 1190

/* WARNING: Unknown calling convention yet parameter storage is locked */

SVECTOR globemesh[54];

// [D]
void initExplosion(void)
{
	short sVar1;
	short sVar2;
	uint uVar3;
	SVECTOR *pSVar4;
	uint uVar5;
	int iVar6;
	uint uVar7;
	int puVar8;
	uint uVar9;

	uVar7 = 128;
	pSVar4 = globemesh;
	uVar9 = 0;
	do {
		uVar3 = uVar7 & 0xfff;
		uVar7 = uVar7 + 0x200;
		uVar5 = uVar9 + 2;

		pSVar4->vy = 5;
		pSVar4[1].vy = -0x109;

		pSVar4->vx = FIXEDH(rcossin_tbl[(uVar9 & 0xf) * 0x200 + 1] * 0x200);
		pSVar4->vz = FIXEDH(rcossin_tbl[(uVar9 & 0xf) * 0x200] * 0x200);

		pSVar4[1].vx = FIXEDH(rcossin_tbl[uVar3 * 2 + 1] * 0x1ea);
		pSVar4[1].vz = FIXEDH(rcossin_tbl[uVar3 * 2] * 0x1ea);

		pSVar4 = pSVar4 + 2;
		uVar9 = uVar5;
	} while (uVar5 < 0x12);

	uVar9 = 0x1300;
	pSVar4 = globemesh + 18;
	puVar8 = 0x1280;
	iVar6 = 0x10;
	do {
		uVar3 = uVar9 & 0xfff;
		uVar9 = uVar9 + 0x200;
		uVar7 = (uint)puVar8 & 0xfff;
		puVar8 = puVar8 + 0x200;
		iVar6 = iVar6 + -2;

		pSVar4->vy = -0x109;
		pSVar4[1].vy = -0x1f9;

		pSVar4->vx = FIXEDH(rcossin_tbl[uVar7 * 2 + 1] * 0x1ea);
		pSVar4->vz = FIXEDH(rcossin_tbl[uVar7 * 2] * 0x1ea);

		pSVar4[1].vx = FIXEDH(rcossin_tbl[uVar3 * 2 + 1] * 0x14a);
		pSVar4[1].vz = FIXEDH(rcossin_tbl[uVar3 * 2] * 0x14a);

		pSVar4 = pSVar4 + 2;
	} while (-1 < iVar6);

	puVar8 = 9600;
	pSVar4 = globemesh + 36;
	uVar9 = 0x2500;
	iVar6 = 0x10;
	do {
		uVar3 = (uint)puVar8 & 0xfff;
		puVar8 = puVar8 + 0x200;
		uVar7 = uVar9 & 0xfff;
		uVar9 = uVar9 + 0x200;
		iVar6 = iVar6 + -2;

		pSVar4->vy = -0x1f9;
		pSVar4[1].vy = -0x269;

		pSVar4->vx = FIXEDH(rcossin_tbl[uVar7 * 2 + 1] * 0x14a);
		pSVar4->vz = FIXEDH(rcossin_tbl[uVar7 * 2] * 0x14a);

		pSVar4[1].vx = FIXEDH(rcossin_tbl[uVar3 * 2 + 1] * 100);
		pSVar4[1].vz = FIXEDH(rcossin_tbl[uVar3 * 2] * 100);

		pSVar4 = pSVar4 + 2;
	} while (-1 < iVar6);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawExplosion(int time /*stack 0*/, struct VECTOR position /*stack 4*/, int hscale /*stack 20*/, int rscale /*stack 24*/)
 // line 588, offset 0x000572a8
	/* begin block 1 */
		// Start line: 589
		// Start offset: 0x000572A8
		// Variables:
	// 		int i; // $t1
	// 		int j; // $s3
	// 		struct POLY_FT4 *poly; // $a2
	// 		struct SVECTOR *src; // $t0
	// 		struct VECTOR v; // stack offset -136
	// 		int rgb; // $s0
	// 		int z; // stack offset -56
	// 		int sf1; // $t0
	// 		int sf2; // $a0
	// 		unsigned long u0; // $s2
	// 		unsigned long u1; // $s1
	// 		unsigned long u2; // $s5
	// 		unsigned long u3; // $s4

		/* begin block 1.1 */
			// Start line: 589
			// Start offset: 0x000572A8
			// Variables:
		// 		int transparency; // $t2
		// 		int green; // $t1
		// 		int blue; // $v1
		/* end block 1.1 */
		// End offset: 0x000572A8
		// End Line: 589

		/* begin block 1.2 */
			// Start line: 631
			// Start offset: 0x000573F0
			// Variables:
		// 		struct MATRIX workmatrix; // stack offset -120
		// 		int sf; // $v0
		// 		int s; // $v1
		// 		int c; // $a3
		/* end block 1.2 */
		// End offset: 0x00057444
		// End Line: 638

		/* begin block 1.3 */
			// Start line: 685
			// Start offset: 0x00057720
			// Variables:
		// 		int transparency; // $a0
		// 		int red; // $a1
		// 		int green; // $a2
		// 		int blue; // $v1
		/* end block 1.3 */
		// End offset: 0x00057720
		// End Line: 685

		/* begin block 1.4 */
			// Start line: 698
			// Start offset: 0x000577A4
			// Variables:
		// 		struct MATRIX workmatrix; // stack offset -88
		// 		int sf; // $v0
		// 		int s; // $v1
		// 		int c; // $a3
		/* end block 1.4 */
		// End offset: 0x000577F8
		// End Line: 707
	/* end block 1 */
	// End offset: 0x00057B0C
	// End Line: 755

	/* begin block 2 */
		// Start line: 1271
	/* end block 2 */
	// End Line: 1272

	/* begin block 3 */
		// Start line: 1278
	/* end block 3 */
	// End Line: 1279

// [D]
void DrawExplosion(int time, VECTOR position, int hscale, int rscale)
{
	int iVar3;
	int i;
	POLY_FT4 *poly;
	SVECTOR *src;
	int uVar6;
	uint uVar7;
	uint uVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	VECTOR v;
	MATRIX workmatrix;
	int z;

	uVar8 = *(ushort*)&smoke_texture.coords.u0 + 0x200 | *(ushort*)&smoke_texture.clutid << 0x10;
	uVar7 = *(ushort*)&smoke_texture.coords.u1 + 0x200 | (*(ushort*)&smoke_texture.tpageid | 0x20) << 0x10;
	iVar11 = *(ushort*)&smoke_texture.coords.u2 - 0x800;
	iVar10 = *(ushort*)&smoke_texture.coords.u3 - 0x800;

	v.vx = position.vx - camera_position.vx;
	v.vy = position.vy - camera_position.vy;
	v.vz = position.vz - camera_position.vz;

	uVar6 = 255 - (time >> 4);
	uVar6 = (((uVar6 * uVar6) >> 10) << 8 | ((255 - uVar6) * (uVar6 >> 2) + uVar6 * (uVar6 >> 1)) >> 8) << 8 | uVar6 | 0x2e000000;


	Apply_Inv_CameraMatrix(&v);
	gte_SetTransVector(&v);

	iVar12 = 0;
	iVar9 = 1;

	do {
		iVar3 = (time * (0x37a0 - time) + 0x800 >> 0xc) + 0xc;

		i = CameraCnt * (0x40 - iVar12) & 0xfff;
		SS.m[1][1] = (short)(iVar3 * hscale >> 0xc);
		SS.m[0][0] = (short)((iVar3 * rscale >> 0xc) * (int)rcossin_tbl[i * 2 + 1] + 0x800 >> 0xc);
		SS.m[2][0] = (short)((iVar3 * rscale >> 0xc) * (int)rcossin_tbl[i * 2] + 0x800 >> 0xc);
		SS.m[0][2] = -SS.m[2][0];
		SS.m[2][2] = SS.m[0][0];

		MulMatrix0(&inv_camera_matrix, &SS, &workmatrix);

		gte_SetRotMatrix(&workmatrix);

		src = globemesh;
		i = 0;

		do {
			poly = (POLY_FT4 *)current->primptr;

			gte_ldv3(&src[0], &src[1], &src[2]);
			gte_rtpt();

			*(uint *)&poly[0].r0 = uVar6;
			*(uint *)&poly[1].r0 = uVar6;

			gte_stsxy3(&poly[0].x0, &poly[0].x1, &poly[0].x2);

			gte_stsxy2(&poly[1].x0);

			gte_stsz(&z);

			iVar3 = 32; // 4 verts step?

			if (z > 32)
			{
				gte_ldv3(&src[3], &src[4], &src[5]);
				gte_rtpt();

				*(uint *)&poly[0].u0 = uVar8;
				*(uint *)&poly[0].u1 = uVar7;
				*(uint *)&poly[0].u2 = iVar11;
				*(uint *)&poly[0].u3 = iVar10;
				*(uint *)&poly[1].u0 = uVar8;
				*(uint *)&poly[1].u1 = uVar7;
				*(uint *)&poly[1].u2 = iVar11;
				*(uint *)&poly[1].u3 = iVar10;

				setPolyFT4(poly);
				setSemiTrans(poly, 1);

				setPolyFT4(&poly[1]);
				setSemiTrans(&poly[1], 1);

				gte_stsxy3(&poly[1].x1, &poly[1].x2, &poly[1].x3);

				gte_stsxy0(&poly[0].x3);

				addPrim(current->ot + (z >> 3), &poly[0]);
				addPrim(current->ot + (z >> 3), &poly[1]);

				current->primptr += sizeof(POLY_FT4) * 2;
			}

			if ((i & 3) == 3)
				iVar3 = 48;  // 6 verts step?

			src = (SVECTOR *)((int)&src->vx + iVar3);

			i++;
		} while (i < 12);

		iVar9--;
		iVar12 += 90;
	} while (-1 < iVar9);

	iVar9 = 255 - (time >> 4);
	uVar6 = iVar9 >> 1;
	iVar12 = 0;
	uVar6 = (((uVar6 + (iVar9 * iVar9 >> 10)) >> 1) << 8 | (uVar6 + (((255 - iVar9) * (iVar9 >> 2) + iVar9 * uVar6) >> 8)) >> 1) << 8 | uVar6 | 0x2e000000;

	do {
		iVar3 = (time * (0x3930 - time) + 0x800 >> 0xc) + 0xc;
		i = CameraCnt * (iVar12 * -0x5a + 0x40) & 0xfff;
		SS.m[1][1] = (short)(iVar3 * hscale >> 0xc);
		SS.m[0][0] = (short)((iVar3 * rscale >> 0xc) * (int)rcossin_tbl[i * 2 + 1] + 0x800 >> 0xc);
		SS.m[2][0] = (short)((iVar3 * rscale >> 0xc) * (int)rcossin_tbl[i * 2] + 0x800 >> 0xc);
		SS.m[0][2] = -SS.m[2][0];
		SS.m[2][2] = SS.m[0][0];

		MulMatrix0(&inv_camera_matrix, &SS, &workmatrix);
		gte_SetRotMatrix(&workmatrix);

		src = globemesh;
		i = 0;
		iVar12 = iVar12 + 1;

		do {
			poly = (POLY_FT4 *)current->primptr;

			gte_ldv3(&src[0], &src[1], &src[2]);

			gte_rtpt();

			*(uint *)&poly[1].r0 = uVar6;
			*(uint *)&poly->r0 = uVar6;

			gte_stsxy3(&poly[0].x0, &poly[0].x1, &poly[0].x2);

			gte_stsxy2(&poly[1].x0);

			gte_stsz(&z);

			if (z > 32)
			{
				gte_ldv3(&src[3], &src[4], &src[5]);
				gte_rtpt();

				*(uint *)&poly->u0 = uVar8;
				*(uint *)&poly->u1 = uVar7;
				*(uint *)&poly->u2 = iVar11;
				*(uint *)&poly->u3 = iVar10;
				*(uint *)&poly[1].u0 = uVar8;
				*(uint *)&poly[1].u1 = uVar7;
				*(uint *)&poly[1].u2 = iVar11;
				*(uint *)&poly[1].u3 = iVar10;

				setPolyFT4(poly);
				setSemiTrans(poly, 1);

				setPolyFT4(&poly[1]);
				setSemiTrans(&poly[1], 1);

				gte_stsxy3(&poly[1].x1, &poly[1].x2, &poly[1].x3);

				gte_stsxy0(&poly[0].x3);

				addPrim(current->ot + (z >> 3), &poly[0]);
				addPrim(current->ot + (z >> 3), &poly[1]);

				current->primptr += sizeof(POLY_FT4) * 2;
			}

			iVar9 = 0x20;

			if (i & 3 == 3)
				iVar9 = 0x30;

			src = (SVECTOR *)((int)&src->vx + iVar9);

			i++;
		} while (i < 8);
	} while (iVar12 < 2);
}





