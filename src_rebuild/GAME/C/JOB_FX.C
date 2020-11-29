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
#include "RAND.H"

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
	VECTOR drift;
	VECTOR smokePos;
	CAR_DATA *cp;
	EXOBJECT *exp;
	int i;

	GetSmokeDrift(&drift);	// [A]

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
			} while (cp < &car_data[MAX_CARS + 1]); // + TANNER_COLLIDER_CARID
		}

		i++;
		exp++;
	}

	
	i = 0;
	exp = explosion;
	while (i < MAX_EXPLOSION_OBJECTS)
	{
		if (exp->time != -1)
		{
			if (exp->time == 0)
			{
				ExplosionSound(&exp->pos, exp->type);
			}

			// [A] add smoke to explosions
			if(exp->time > 1500 && (CameraCnt & 0x3) == 0)
			{
				smokePos = exp->pos;
				smokePos.vy -= 120;
				Setup_Smoke(&smokePos, 100 + (rand() & 15) * 20, 900, SMOKE_BLACK, 0, &drift, 0);
			}

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

// [D] [T]
void initExplosion(void)
{
	SVECTOR *vert;
	int i;
	int d1, d2;

	// generate half-globe mesh

	vert = globemesh;
	
	d1 = 0;
	d2 = 128;

	i = 0;
	do {
		vert[0].vy = 5;
		vert[1].vy = -265;

		vert[0].vx = FIXEDH(rcossin_tbl[(d1 & 0xf) * 512 + 1] * 512);
		vert[0].vz = FIXEDH(rcossin_tbl[(d1 & 0xf) * 512] * 512);

		vert[1].vx = FIXEDH(rcossin_tbl[(d2 & 0xfff) * 2 + 1] * 490);
		vert[1].vz = FIXEDH(rcossin_tbl[(d2 & 0xfff) * 2] * 490);

		vert += 2;
	
		d1 += 2;
		d2 += 512;
		
		i++;
	} while (i < 18);

	vert = globemesh + 18;
	
	d1 = 0x1280;
	d2 = 0x1300;

	i = 0;
	do {
		vert[0].vy = -265;
		vert[1].vy = -505;

		vert[0].vx = FIXEDH(rcossin_tbl[(d1 & 0xfff) * 2 + 1] * 490);
		vert[0].vz = FIXEDH(rcossin_tbl[(d1 & 0xfff) * 2] * 490);

		vert[1].vx = FIXEDH(rcossin_tbl[(d2 & 0xfff) * 2 + 1] * 330);
		vert[1].vz = FIXEDH(rcossin_tbl[(d2 & 0xfff) * 2] * 330);

		vert += 2;

		d1 += 512;
		d2 += 512;
		
		i += 2;
	} while (i < 18);

	vert = globemesh + 36;

	d1 = 0x2500;
	d2 = 9600;

	i = 0;
	do {
		vert[0].vy = -505;
		vert[1].vy = -617;

		vert[0].vx = FIXEDH(rcossin_tbl[(d1 & 0xfff) * 2 + 1] * 330);
		vert[0].vz = FIXEDH(rcossin_tbl[(d1 & 0xfff) * 2] * 330);

		vert[1].vx = FIXEDH(rcossin_tbl[(d2 & 0xfff) * 2 + 1] * 100);
		vert[1].vz = FIXEDH(rcossin_tbl[(d2 & 0xfff) * 2] * 100);

		vert += 2;
		
		d1 += 512;
		d2 += 512;

		i += 2;
	} while (i < 18);
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

// [D] [T]
void DrawExplosion(int time, VECTOR position, int hscale, int rscale)
{
	int j;
	POLY_FT4 *poly;
	SVECTOR *src;
	
	int rgb, transparency;
	int red, green, blue;
	int sf, sf1, sf2;
	
	uint u0, u1,u2,u3;
	int i;
	VECTOR v;
	MATRIX workmatrix;
	int z;

	u0 = *(ushort*)&smoke_texture.coords.u0 + 0x200 | *(ushort*)&smoke_texture.clutid << 0x10;
	u1 = *(ushort*)&smoke_texture.coords.u1 + 0x200 | (*(ushort*)&smoke_texture.tpageid | 0x20) << 0x10;
	u2 = *(ushort*)&smoke_texture.coords.u2 - 0x800;
	u3 = *(ushort*)&smoke_texture.coords.u3 - 0x800;

	v.vx = position.vx - camera_position.vx;
	v.vy = position.vy - camera_position.vy;
	v.vz = position.vz - camera_position.vz;

	transparency = 255 - (time >> 4);
	rgb = (transparency * transparency >> 10 << 8 |
		(255 - transparency) * (transparency >> 2) + transparency * (transparency >> 1) >> 8) << 8 | 
		transparency | 
		0x2e000000;

	Apply_Inv_CameraMatrix(&v);
	gte_SetTransVector(&v);

	// [A] modify scale factor to make explosions prettier
	sf1 = FIXEDH(time * (5000 - time) * 4) + 12;
	sf2 = FIXEDH(time * (10000 - time) * 2) + 12;

	i = 0;
	do {
		sf = CameraCnt * (64 - i*90) & 0xfff;
		
		SS.m[1][1] = FIXED(sf1 * hscale);
		SS.m[0][0] = FIXEDH(FIXED(sf1 * rscale) * rcossin_tbl[sf * 2 + 1]);
		SS.m[2][0] = FIXEDH(FIXED(sf1 * rscale) * rcossin_tbl[sf * 2]);
		SS.m[0][2] = -SS.m[2][0];
		SS.m[2][2] = SS.m[0][0];

		MulMatrix0(&inv_camera_matrix, &SS, &workmatrix);

		gte_SetRotMatrix(&workmatrix);

		src = globemesh;
		j = 0;

		do {
			poly = (POLY_FT4 *)current->primptr;

			gte_ldv3(&src[0], &src[1], &src[2]);
			gte_rtpt();

			*(uint *)&poly[0].r0 = rgb;
			*(uint *)&poly[1].r0 = rgb;

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

				*(uint *)&poly[0].u0 = u0;
				*(uint *)&poly[0].u1 = u1;
				*(uint *)&poly[0].u2 = u2;
				*(uint *)&poly[0].u3 = u3;
				
				*(uint *)&poly[1].u0 = u0;
				*(uint *)&poly[1].u1 = u1;
				*(uint *)&poly[1].u2 = u2;
				*(uint *)&poly[1].u3 = u3;

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

			if ((j & 3) == 3)
				src += 6;
			else
				src += 4;

			j++;
		} while (j < 12);

		i++;
	} while (i < 2);

	transparency = 255 - (time >> 4);

	rgb = transparency >> 1;
	rgb = (rgb + (transparency * transparency >> 10) >> 1 << 8 | 
			rgb + ((255 - transparency) * (transparency >> 2) + transparency * rgb >> 8) >> 1) << 8 | 
			rgb | 0x2e000000;

	i = 0;
	do {
		sf = CameraCnt * (i * -90 + 64) & 0xfff;
		SS.m[1][1] = FIXED(sf2 * hscale);
		SS.m[0][0] = FIXEDH(FIXED(sf2 * rscale) * rcossin_tbl[sf * 2 + 1]);
		SS.m[2][0] = FIXEDH(FIXED(sf2 * rscale) * rcossin_tbl[sf * 2]);
		SS.m[0][2] = -SS.m[2][0];
		SS.m[2][2] = SS.m[0][0];

		MulMatrix0(&inv_camera_matrix, &SS, &workmatrix);
		gte_SetRotMatrix(&workmatrix);

		src = globemesh;
		j = 0;
		do {
			poly = (POLY_FT4 *)current->primptr;

			gte_ldv3(&src[0], &src[1], &src[2]);

			gte_rtpt();

			*(uint *)&poly[1].r0 = rgb;
			*(uint *)&poly[0].r0 = rgb;

			gte_stsxy3(&poly[0].x0, &poly[0].x1, &poly[0].x2);

			gte_stsxy2(&poly[1].x0);

			gte_stsz(&z);

			if (z > 32)
			{
				gte_ldv3(&src[3], &src[4], &src[5]);
				gte_rtpt();

				*(uint *)&poly[0].u0 = u0;
				*(uint *)&poly[0].u1 = u1;
				*(uint *)&poly[0].u2 = u2;
				*(uint *)&poly[0].u3 = u3;
				*(uint *)&poly[1].u0 = u0;
				*(uint *)&poly[1].u1 = u1;
				*(uint *)&poly[1].u2 = u2;
				*(uint *)&poly[1].u3 = u3;

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

			if (j & 3 == 3)
				src += 6;
			else
				src += 4;
			
			j++;
		} while (j < 8);

		i++;
	} while (i < 2);
}





