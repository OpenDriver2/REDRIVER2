#include "DRIVER2.H"
#include "JOB_FX.H"
#include "BOMBERMAN.H"
#include "PAUSE.H"
#include "GAMESND.H"
#include "CARS.H"

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
				if (cp == &car_data[20] || cp != gBombTargetVehicle && cp->controlType != 0)
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

		pSVar4->vx = FIXED(rcossin_tbl[(uVar9 & 0xf) * 0x200 + 1] * 0x200);
		pSVar4->vz = FIXED(rcossin_tbl[(uVar9 & 0xf) * 0x200] * 0x200);

		pSVar4[1].vx = FIXED(rcossin_tbl[uVar3 * 2 + 1] * 0x1ea);
		pSVar4[1].vz = FIXED(rcossin_tbl[uVar3 * 2] * 0x1ea);

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

		pSVar4->vx = FIXED(rcossin_tbl[uVar7 * 2 + 1] * 0x1ea);
		pSVar4->vz = FIXED(rcossin_tbl[uVar7 * 2] * 0x1ea);

		pSVar4[1].vx = FIXED(rcossin_tbl[uVar3 * 2 + 1] * 0x14a);
		pSVar4[1].vz = FIXED(rcossin_tbl[uVar3 * 2] * 0x14a);

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

		pSVar4->vx = FIXED(rcossin_tbl[uVar7 * 2 + 1] * 0x14a);
		pSVar4->vz = FIXED(rcossin_tbl[uVar7 * 2] * 0x14a);

		pSVar4[1].vx = FIXED(rcossin_tbl[uVar3 * 2 + 1] * 100);
		pSVar4[1].vz = FIXED(rcossin_tbl[uVar3 * 2] * 100);

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

void DrawExplosion(int time, VECTOR position, int hscale, int rscale)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;
	undefined4 uVar2;
	ulong *puVar3;
	undefined4 in_zero;
	undefined4 in_at;
	int iVar4;
	uint uVar5;
	char *pcVar6;
	MATRIX *pMVar7;
	DB *pDVar8;
	DB *pDVar9;
	DB *pDVar10;
	MATRIX *pMVar11;
	uint *puVar12;
	int in_a3;
	SVECTOR *pSVar13;
	uint uVar14;
	uint uVar15;
	uint uVar16;
	int iVar17;
	uint uVar18;
	uint uVar19;
	int iVar20;
	int iVar21;
	int local_88;
	int local_84;
	int local_80;
	undefined4 local_78;
	undefined4 local_74;
	undefined4 local_70;
	undefined4 local_6c;
	undefined4 local_68;
	ulong auStack88[8];
	char *local_38;
	ulong *local_34;
	DB *local_30;

	uVar14 = 0xff - (time >> 4);
	uVar16 = (uint)smoke_texture.coords._0_2_ + 0x200 | (uint)smoke_texture.clutid << 0x10;
	uVar15 = (uint)smoke_texture.coords._2_2_ + 0x200 | ((uint)smoke_texture.tpageid | 0x20) << 0x10;
	local_88 = hscale - camera_position.vx;
	local_84 = rscale - camera_position.vy;
	local_80 = in_a3 - camera_position.vz;
	uVar14 = (((int)(uVar14 * uVar14) >> 10) << 8 |
		(int)((0xff - uVar14) * ((int)uVar14 >> 2) + uVar14 * ((int)uVar14 >> 1)) >> 8) << 8 |
		uVar14 | 0x2e000000;
	uVar19 = (uint)smoke_texture.coords._4_2_ - 0x800;
	uVar18 = (uint)smoke_texture.coords._6_2_ - 0x800;
	Apply_Inv_CameraMatrix(&local_88);
	setCopControlWord(2, 0x2800, local_88);
	setCopControlWord(2, 0x3000, local_84);
	setCopControlWord(2, 0x3800, local_80);
	local_30 = (DB *)&local_38;
	local_34 = auStack88;
	iVar20 = 0;
	iVar17 = 1;
	do {
		iVar4 = (time * (0x37a0 - time) + 0x800 >> 0xc) + 0xc;
		iVar21 = iVar4 * position.vy;
		if (iVar21 < 0) {
			iVar21 = iVar21 + 0xfff;
		}
		iVar4 = iVar4 * position.vz;
		if (iVar4 < 0) {
			iVar4 = iVar4 + 0xfff;
		}
		uVar5 = CameraCnt * (0x40 - iVar20) & 0xfff;
		SS.m[1][1] = (short)(iVar21 >> 0xc);
		SS.m[0][0] = (short)((iVar4 >> 0xc) * (int)rcossin_tbl[uVar5 * 2 + 1] + 0x800 >> 0xc);
		SS.m[2][0] = (short)((iVar4 >> 0xc) * (int)rcossin_tbl[uVar5 * 2] + 0x800 >> 0xc);
		SS.m[0][2] = -SS.m[2][0];
		pDVar9 = (DB *)&SS;
		SS.m[2][2] = SS.m[0][0];
		MulMatrix0(&inv_camera_matrix, &SS, &local_78);
		setCopControlWord(2, 0, local_78);
		setCopControlWord(2, 0x800, local_74);
		setCopControlWord(2, 0x1000, local_70);
		setCopControlWord(2, 0x1800, local_6c);
		setCopControlWord(2, 0x2000, local_68);
		pcVar6 = CHAR_ARRAY_000d0000;
		pSVar13 = globemesh;
		uVar5 = 0;
		pDVar8 = (DB *)time;
		do {
			pDVar10 = local_30;
			puVar12 = (uint *)current->primptr;
			setCopReg(2, in_zero, *(undefined4 *)pSVar13);
			setCopReg(2, in_at, *(undefined4 *)&pSVar13->vz);
			setCopReg(2, current, *(undefined4 *)(pSVar13 + 1));
			setCopReg(2, pcVar6, *(undefined4 *)&pSVar13[1].vz);
			setCopReg(2, pDVar8, *(undefined4 *)(pSVar13 + 2));
			setCopReg(2, pDVar9, *(undefined4 *)&pSVar13[2].vz);
			copFunction(2, 0x280030);
			pDVar8 = (DB *)(puVar12 + 4);
			puVar12[0xb] = uVar14;
			puVar12[1] = uVar14;
			uVar1 = getCopReg(2, 0xc);
			puVar12[2] = uVar1;
			pcVar6 = (char *)getCopReg(2, 0xd);
			pDVar8->primptr = pcVar6;
			uVar1 = getCopReg(2, 0xe);
			puVar12[6] = uVar1;
			uVar1 = getCopReg(2, 0xe);
			puVar12[0xc] = uVar1;
			pcVar6 = (char *)getCopReg(2, 0x13);
			local_30->primptr = pcVar6;
			puVar3 = local_34;
			setCopReg(2, in_zero, *(undefined4 *)(pSVar13 + 3));
			setCopReg(2, in_at, *(undefined4 *)&pSVar13[3].vz);
			setCopReg(2, puVar12 + 6, *(undefined4 *)(pSVar13 + 4));
			setCopReg(2, puVar12 + 0xc, *(undefined4 *)&pSVar13[4].vz);
			setCopReg(2, pDVar8, *(undefined4 *)(pSVar13 + 5));
			setCopReg(2, pDVar10, *(undefined4 *)&pSVar13[5].vz);
			iVar4 = 0x20;
			copFunction(2, 0x280030);
			pcVar6 = (char *)(uVar5 & 3);
			if ((uint *)pcVar6 == (uint *)0x3) {
				iVar4 = 0x30;
			}
			pSVar13 = (SVECTOR *)((int)&pSVar13->vx + iVar4);
			if (0x20 < (int)local_38) {
				puVar12[3] = uVar16;
				puVar12[5] = uVar15;
				puVar12[7] = uVar19;
				puVar12[9] = uVar18;
				puVar12[0xd] = uVar16;
				puVar12[0xf] = uVar15;
				puVar12[0x11] = uVar19;
				puVar12[0x13] = uVar18;
				*(char *)((int)puVar12 + 3) = '\t';
				pDVar8 = current;
				iVar4 = (int)local_38 >> 3;
				*puVar12 = *puVar12 & 0xff000000 | current->ot[iVar4] & 0xffffff;
				pDVar8->ot[iVar4] = pDVar8->ot[iVar4] & 0xff000000 | (uint)puVar12 & 0xffffff;
				*(char *)((int)puVar12 + 0x2b) = '\t';
				pDVar8 = current;
				puVar12[10] = puVar12[10] & 0xff000000 | current->ot[iVar4] & 0xffffff;
				pDVar10 = (DB *)(puVar12 + 0xe);
				pDVar8->ot[iVar4] = pDVar8->ot[iVar4] & 0xff000000 | (uint)(puVar12 + 10) & 0xffffff;
				pcVar6 = (char *)getCopReg(2, 0xc);
				pDVar10->primptr = pcVar6;
				uVar1 = getCopReg(2, 0xd);
				puVar12[0x10] = uVar1;
				uVar1 = getCopReg(2, 0xe);
				puVar12[0x12] = uVar1;
				pcVar6 = (char *)(puVar12 + 8);
				uVar1 = getCopReg(2, 0xc);
				*(uint *)pcVar6 = uVar1;
				pDVar8 = current;
				current->primptr = current->primptr + 0x50;
			}
			uVar5 = uVar5 + 1;
			pDVar9 = pDVar10;
		} while ((int)uVar5 < 0xc);
		iVar17 = iVar17 + -1;
		iVar20 = iVar20 + 0x5a;
	} while (-1 < iVar17);
	iVar17 = 0xff - (time >> 4);
	uVar14 = iVar17 >> 1;
	iVar20 = 0;
	uVar14 = (((int)(uVar14 + (iVar17 * iVar17 >> 10)) >> 1) << 8 |
		(int)(uVar14 + ((int)((0xff - iVar17) * (iVar17 >> 2) + iVar17 * uVar14) >> 8)) >> 1) <<
		8 | uVar14 | 0x2e000000;
	do {
		iVar17 = (time * (0x3930 - time) + 0x800 >> 0xc) + 0xc;
		iVar4 = iVar17 * position.vy;
		if (iVar4 < 0) {
			iVar4 = iVar4 + 0xfff;
		}
		iVar17 = iVar17 * position.vz;
		if (iVar17 < 0) {
			iVar17 = iVar17 + 0xfff;
		}
		uVar5 = CameraCnt * (iVar20 * -0x5a + 0x40) & 0xfff;
		SS.m[1][1] = (short)(iVar4 >> 0xc);
		pMVar7 = &inv_camera_matrix;
		SS.m[0][0] = (short)((iVar17 >> 0xc) * (int)rcossin_tbl[uVar5 * 2 + 1] + 0x800 >> 0xc);
		SS.m[2][0] = (short)((iVar17 >> 0xc) * (int)rcossin_tbl[uVar5 * 2] + 0x800 >> 0xc);
		SS.m[0][2] = -SS.m[2][0];
		pMVar11 = &SS;
		SS.m[2][2] = SS.m[0][0];
		MulMatrix0(&inv_camera_matrix, &SS, puVar3);
		setCopControlWord(2, 0, *puVar3);
		setCopControlWord(2, 0x800, puVar3[1]);
		setCopControlWord(2, 0x1000, puVar3[2]);
		setCopControlWord(2, 0x1800, puVar3[3]);
		setCopControlWord(2, 0x2000, puVar3[4]);
		pcVar6 = CHAR_ARRAY_000d0000;
		pSVar13 = globemesh;
		uVar5 = 0;
		iVar20 = iVar20 + 1;
		do {
			pDVar8 = local_30;
			puVar12 = (uint *)current->primptr;
			setCopReg(2, in_zero, *(undefined4 *)pSVar13);
			setCopReg(2, in_at, *(undefined4 *)&pSVar13->vz);
			setCopReg(2, current, *(undefined4 *)(pSVar13 + 1));
			setCopReg(2, pcVar6, *(undefined4 *)&pSVar13[1].vz);
			setCopReg(2, pMVar7, *(undefined4 *)(pSVar13 + 2));
			setCopReg(2, pMVar11, *(undefined4 *)&pSVar13[2].vz);
			copFunction(2, 0x280030);
			pMVar11 = (MATRIX *)(puVar12 + 2);
			puVar12[0xb] = uVar14;
			puVar12[1] = uVar14;
			uVar2 = getCopReg(2, 0xc);
			*(undefined4 *)pMVar11->m = uVar2;
			uVar1 = getCopReg(2, 0xd);
			puVar12[4] = uVar1;
			uVar1 = getCopReg(2, 0xe);
			puVar12[6] = uVar1;
			uVar1 = getCopReg(2, 0xe);
			puVar12[0xc] = uVar1;
			pcVar6 = (char *)getCopReg(2, 0x13);
			local_30->primptr = pcVar6;
			setCopReg(2, in_zero, *(undefined4 *)(pSVar13 + 3));
			setCopReg(2, in_at, *(undefined4 *)&pSVar13[3].vz);
			setCopReg(2, puVar12 + 6, *(undefined4 *)(pSVar13 + 4));
			setCopReg(2, puVar12 + 0xc, *(undefined4 *)&pSVar13[4].vz);
			setCopReg(2, pDVar8, *(undefined4 *)(pSVar13 + 5));
			setCopReg(2, pMVar11, *(undefined4 *)&pSVar13[5].vz);
			iVar17 = 0x20;
			copFunction(2, 0x280030);
			pcVar6 = (char *)(uVar5 & 3);
			if ((uint *)pcVar6 == (uint *)0x3) {
				iVar17 = 0x30;
			}
			pSVar13 = (SVECTOR *)((int)&pSVar13->vx + iVar17);
			if (0x20 < (int)local_38) {
				puVar12[3] = uVar16;
				puVar12[5] = uVar15;
				puVar12[7] = uVar19;
				puVar12[9] = uVar18;
				puVar12[0xd] = uVar16;
				puVar12[0xf] = uVar15;
				puVar12[0x11] = uVar19;
				puVar12[0x13] = uVar18;
				*(char *)((int)puVar12 + 3) = '\t';
				pDVar8 = current;
				iVar17 = (int)local_38 >> 3;
				*puVar12 = *puVar12 & 0xff000000 | current->ot[iVar17] & 0xffffff;
				pDVar8->ot[iVar17] = pDVar8->ot[iVar17] & 0xff000000 | (uint)puVar12 & 0xffffff;
				*(char *)((int)puVar12 + 0x2b) = '\t';
				pDVar8 = current;
				puVar12[10] = puVar12[10] & 0xff000000 | current->ot[iVar17] & 0xffffff;
				pMVar11 = (MATRIX *)(puVar12 + 0xe);
				pDVar8->ot[iVar17] = pDVar8->ot[iVar17] & 0xff000000 | (uint)(puVar12 + 10) & 0xffffff;
				uVar2 = getCopReg(2, 0xc);
				*(undefined4 *)pMVar11->m = uVar2;
				uVar1 = getCopReg(2, 0xd);
				puVar12[0x10] = uVar1;
				uVar1 = getCopReg(2, 0xe);
				puVar12[0x12] = uVar1;
				pcVar6 = (char *)(puVar12 + 8);
				uVar1 = getCopReg(2, 0xc);
				*(uint *)pcVar6 = uVar1;
				pDVar8 = current;
				current->primptr = current->primptr + 0x50;
			}
			uVar5 = uVar5 + 1;
			pMVar7 = (MATRIX *)pDVar8;
		} while ((int)uVar5 < 8);
	} while (iVar20 < 2);
	return;
	*/
}





