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
#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"

EXOBJECT explosion[MAX_EXPLOSION_OBJECTS];

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

// [D] [T]
void InitExObjects(void)
{
	int i;

	for (i = 0; i < MAX_EXPLOSION_OBJECTS; i++)
		explosion[i].time = -1;

	initExplosion();
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddExplosion(VECTOR pos /*stack 0*/, int type /*stack 16*/)
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

// [D] [T]
void AddExplosion(VECTOR pos, int type)
{
	EXOBJECT *newExplosion;
	int i;

	i = 0;
	newExplosion = explosion;

	while (newExplosion->time != -1 && i < MAX_EXPLOSION_OBJECTS) 
	{
		newExplosion++;
		i++;
	}

	newExplosion->time = 0;
	newExplosion->pos = pos;
	newExplosion->type = (ExplosionType)type;

	if (type == LITTLE_BANG) 
	{
		newExplosion->speed = 192;
		newExplosion->hscale = 1024;
		newExplosion->rscale = 1024;
	}
	else if (type == BIG_BANG)
	{
		newExplosion->speed = 128;
		newExplosion->hscale = 4096;
		newExplosion->rscale = 4096;
	}
	else if (type == HEY_MOMMA)
	{
		newExplosion->speed = 64;
		newExplosion->hscale = 16384;
		newExplosion->rscale = 16384;
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
	// 		CAR_DATA *cp; // $s0

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

// [D] [T]
void HandleExplosion(void)
{
	CAR_DATA *cp;
	EXOBJECT *exp;
	int i;

	if (pauseflag != 0)
		return;

	i = 0;
	exp = explosion;

	while (i < MAX_EXPLOSION_OBJECTS)
	{
		if (exp->time != -1 && exp->type != BANG_USED) 
		{
			cp = car_data;

			do {
				if (cp == &car_data[CAMERA_COLLIDER_CARID] || cp != gBombTargetVehicle && cp->controlType != CONTROL_TYPE_NONE)
					ExplosionCollisionCheck(cp, &explosion[i]);

				cp++;
			} while (cp < &car_data[MAX_CARS]);
		}

		i++;
		exp++;
	};

	
	i = 0;
	exp = explosion;
	while (i < MAX_EXPLOSION_OBJECTS)
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
	}
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

// [D] [T]
void DrawAllExplosions(void)
{
	int i;
	i = 0;
	while (i < MAX_EXPLOSION_OBJECTS)
	{
		if (explosion[i].time != -1)
			DrawExplosion(explosion[i].time, explosion[i].pos, explosion[i].hscale, explosion[i].rscale);

		i++;
	}
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
	int uVar3;
	SVECTOR *vert;
	int uVar5;
	int iVar6;
	int uVar7;
	int puVar8;
	int uVar9;

	uVar7 = 128;
	vert = globemesh;
	uVar9 = 0;
	do {
		uVar3 = uVar7 & 0xfff;
		uVar7 = uVar7 + 0x200;
		uVar5 = uVar9 + 2;

		vert[0].vy = 5;
		vert[1].vy = -265;

		vert[0].vx = FIXEDH(rcossin_tbl[(uVar9 & 0xf) * 512 + 1] * 512);
		vert[0].vz = FIXEDH(rcossin_tbl[(uVar9 & 0xf) * 512] * 512);

		vert[1].vx = FIXEDH(rcossin_tbl[uVar3 * 2 + 1] * 490);
		vert[1].vz = FIXEDH(rcossin_tbl[uVar3 * 2] * 490);

		vert += 2;
		uVar9 = uVar5;
	} while (uVar5 < 18);

	vert = globemesh + 18;
	
	uVar9 = 0x1300;
	puVar8 = 0x1280;
	iVar6 = 0x10;
	do {
		uVar3 = uVar9 & 0xfff;
		uVar9 = uVar9 + 512;
		uVar7 = puVar8 & 0xfff;
		puVar8 = puVar8 + 512;
		iVar6 = iVar6 - 2;

		vert[0].vy = -265;
		vert[1].vy = -505;

		vert[0].vx = FIXEDH(rcossin_tbl[uVar7 * 2 + 1] * 490);
		vert[0].vz = FIXEDH(rcossin_tbl[uVar7 * 2] * 490);

		vert[1].vx = FIXEDH(rcossin_tbl[uVar3 * 2 + 1] * 330);
		vert[1].vz = FIXEDH(rcossin_tbl[uVar3 * 2] * 330);

		vert += 2;
	} while (iVar6 > -1);

	puVar8 = 9600;
	vert = globemesh + 36;
	uVar9 = 0x2500;
	iVar6 = 0x10;
	do {
		uVar3 = (uint)puVar8 & 0xfff;
		puVar8 = puVar8 + 512;
		uVar7 = uVar9 & 0xfff;
		uVar9 = uVar9 + 512;
		iVar6 = iVar6 - 2;

		vert[0].vy = -505;
		vert[1].vy = -617;

		vert[0].vx = FIXEDH(rcossin_tbl[uVar7 * 2 + 1] * 330);
		vert[0].vz = FIXEDH(rcossin_tbl[uVar7 * 2] * 330);

		vert[1].vx = FIXEDH(rcossin_tbl[uVar3 * 2 + 1] * 100);
		vert[1].vz = FIXEDH(rcossin_tbl[uVar3 * 2] * 100);

		vert += 2;
	} while (-1 < iVar6);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawExplosion(int time /*stack 0*/, VECTOR position /*stack 4*/, int hscale /*stack 20*/, int rscale /*stack 24*/)
 // line 588, offset 0x000572a8
	/* begin block 1 */
		// Start line: 589
		// Start offset: 0x000572A8
		// Variables:
	// 		int i; // $t1
	// 		int j; // $s3
	// 		POLY_FT4 *poly; // $a2
	// 		SVECTOR *src; // $t0
	// 		VECTOR v; // stack offset -136
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
		// 		MATRIX workmatrix; // stack offset -120
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
		// 		MATRIX workmatrix; // stack offset -88
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
		iVar3 = FIXEDH(time * (0x37a0 - time)) + 12;

		i = CameraCnt * (64 - iVar12) & 0xfff;
		SS.m[1][1] = FIXED(iVar3 * hscale);
		SS.m[0][0] = FIXEDH(FIXED(iVar3 * rscale) * rcossin_tbl[i * 2 + 1]);
		SS.m[2][0] = FIXEDH(FIXED(iVar3 * rscale) * rcossin_tbl[i * 2]);
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

			setPolyFT4(&poly[0]);
			setSemiTrans(&poly[0], 1);

			setPolyFT4(&poly[1]);
			setSemiTrans(&poly[1], 1);

			gte_stsxy3(&poly[0].x0, &poly[0].x1, &poly[0].x2);

			gte_stsxy2(&poly[1].x0);

			gte_stsz(&z);

			

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
			else
				iVar3 = 32; // 4 verts step?

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
		iVar3 = FIXEDH(time * (14640 - time)) + 12;
		i = CameraCnt * (iVar12 * -90 + 64) & 0xfff;
		SS.m[1][1] = FIXED(iVar3 * hscale);
		SS.m[0][0] = FIXEDH(FIXED(iVar3 * rscale) * rcossin_tbl[i * 2 + 1]);
		SS.m[2][0] = FIXEDH(FIXED(iVar3 * rscale) * rcossin_tbl[i * 2]);
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
			*(uint *)&poly[0].r0 = uVar6;

			gte_stsxy3(&poly[0].x0, &poly[0].x1, &poly[0].x2);

			gte_stsxy2(&poly[1].x0);

			gte_stsz(&z);

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

			if (i & 3 == 3)
				iVar9 = 0x30;
			else
				iVar9 = 0x20;

			src = (SVECTOR *)((int)&src->vx + iVar9);

			i++;
		} while (i < 8);
	} while (iVar12 < 2);
}





