#include "THISDUST.H"
#include "BCOLLIDE.H"


// decompiled code
// original method signature: 
// int /*$ra*/ bcollided2d(struct CDATA2D *body /*$t4*/, int needOverlap /*$fp*/)
 // line 120, offset 0x0001c51c
	/* begin block 1 */
		// Start line: 121
		// Start offset: 0x0001C51C
		// Variables:
	// 		struct VECTOR delta; // stack offset -56
	// 		int dtheta; // $v1
	// 		int ac; // $s6
	// 		int as; // $s5
	// 		int i; // $t7
	// 		int j; // $a2
	// 		int k; // $t5

		/* begin block 1.1 */
			// Start line: 160
			// Start offset: 0x0001C738
			// Variables:
		// 		int xover; // $t0
		// 		int zover; // $a0
		// 		int tmp2; // $a2
		// 		int FE; // $a3
		/* end block 1.1 */
		// End offset: 0x0001C890
		// End Line: 183
	/* end block 1 */
	// End offset: 0x0001C8C0
	// End Line: 185

	/* begin block 2 */
		// Start line: 240
	/* end block 2 */
	// End Line: 241

int bcollided2d(CDATA2D *body, int needOverlap)
{
	UNIMPLEMENTED();
	return 0;
	/*
	short sVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	uint uVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int *piVar10;
	CDATA2D *pCVar11;
	VECTOR *pVVar12;
	int *piVar13;
	int *piVar14;
	int *piVar15;
	int *piVar16;
	int *piVar17;
	int iVar18;
	int iVar19;
	uint uVar20;
	VECTOR *pVVar21;
	long *plVar22;
	int *piVar23;
	int iVar24;
	int *piVar25;

	iVar19 = 1;
	pCVar11 = body + 1;
	uVar5 = body[1].theta - body->theta;
	sVar1 = rcossin_tbl[(uVar5 + 0x400 & 0x7ff) * 2];
	sVar2 = rcossin_tbl[(uVar5 & 0x7ff) * 2];
	do {
		iVar19 = iVar19 + -1;
		uVar5 = pCVar11->theta & 0xfff;
		sVar3 = rcossin_tbl[uVar5 * 2];
		pCVar11->axis[0].vx = (int)sVar3;
		sVar4 = rcossin_tbl[uVar5 * 2 + 1];
		pCVar11->axis[1].vz = -(int)sVar3;
		pCVar11->axis[0].vz = (int)sVar4;
		pCVar11->axis[1].vx = (int)sVar4;
		pCVar11 = pCVar11 + -1;
	} while (iVar19 != -1);
	uVar5 = 0;
	uVar20 = 1;
	piVar23 = body[1].limit;
	plVar22 = &body[1].axis[0].vz;
	pVVar21 = body[1].axis;
	piVar25 = body[1].dist;
	iVar24 = 100;
	iVar19 = (body->x).vx;
	iVar8 = body[1].x.vx;
	iVar6 = (body->x).vz;
	iVar9 = body[1].x.vz;
	do {
		iVar18 = 1;
		piVar17 = (int *)((int)body->length + iVar24 + 4);
		piVar16 = body->length + uVar5 * 0x19 + 1;
		piVar15 = piVar23 + 1;
		piVar14 = body[uVar5].length;
		piVar13 = plVar22 + 4;
		pVVar12 = pVVar21 + 1;
		piVar10 = piVar25 + 1;
		do {
			*piVar10 = pVVar12->vx * (iVar19 - iVar8) + *piVar13 * (iVar6 - iVar9) + 0x800 >> 0xc;
			iVar7 = *piVar17 + (*piVar16 * (int)sVar1 + *piVar14 * (int)sVar2 + 0x800 >> 0xc);
			*piVar15 = iVar7;
			if (iVar7 < *piVar10) {
				return 0;
			}
			if (*piVar10 < -iVar7) {
				return 0;
			}
			piVar17 = piVar17 + -1;
			piVar16 = piVar16 + -1;
			piVar15 = piVar15 + -1;
			piVar14 = piVar14 + 1;
			piVar13 = piVar13 + -4;
			pVVar12 = pVVar12 + -1;
			iVar18 = iVar18 + -1;
			piVar10 = piVar10 + -1;
		} while (iVar18 != -1);
		uVar5 = uVar20 & 1;
		piVar23 = piVar23 + -0x19;
		plVar22 = plVar22 + -0x19;
		pVVar21 = (VECTOR *)&pVVar21[-7].pad;
		piVar25 = piVar25 + -0x19;
		uVar20 = uVar20 - 1;
		iVar24 = iVar24 + -100;
		if (uVar20 == 0xffffffff) {
			if (needOverlap != 0) {
				iVar19 = body[1].dist[0];
				iVar6 = body[1].limit[0];
				if (iVar19 < 0) {
					iVar19 = -iVar19;
				}
				if (iVar6 < 0) {
					iVar6 = -iVar6;
				}
				iVar8 = iVar19 - iVar6;
				if (iVar8 < 0) {
					iVar8 = iVar6 - iVar19;
				}
				iVar9 = body->axis[0].vx;
				iVar6 = body->axis[0].vz;
				iVar19 = iVar9 * body[1].axis[0].vx + iVar6 * body[1].axis[0].vz + 0x800 >> 0xc;
				if (iVar19 < 0) {
					iVar19 = -iVar19;
				}
				if (iVar19 < 0xb) {
					iVar8 = -1;
				}
				else {
					iVar8 = (iVar8 << 0xc) / iVar19;
					if (iVar19 == 0) {
						trap(7);
					}
				}
				iVar19 = body[1].dist[1];
				iVar24 = body[1].limit[1];
				if (iVar19 < 0) {
					iVar19 = -iVar19;
				}
				if (iVar24 < 0) {
					iVar24 = -iVar24;
				}
				iVar18 = iVar19 - iVar24;
				if (iVar18 < 0) {
					iVar18 = iVar24 - iVar19;
				}
				iVar19 = iVar9 * body[1].axis[1].vx + iVar6 * body[1].axis[1].vz + 0x800 >> 0xc;
				if (iVar19 < 0) {
					iVar19 = -iVar19;
				}
				iVar6 = iVar8;
				if ((10 < iVar19) && (iVar6 = (iVar18 << 0xc) / iVar19, iVar19 == 0)) {
					trap(7);
				}
				boxOverlap = iVar6;
				if ((-1 < iVar8) && (boxOverlap = iVar8, iVar6 < iVar8)) {
					boxOverlap = iVar6;
				}
			}
			return 1;
		}
	} while (true);*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ bFindCollisionPoint(struct CDATA2D *body /*$t6*/, struct CRET2D *collisionResult /*$s0*/)
 // line 195, offset 0x0001c8c0
	/* begin block 1 */
		// Start line: 196
		// Start offset: 0x0001C8C0
		// Variables:
	// 		int carBarrierCollision; // $s1
	// 		int i; // $a3
	// 		int j; // $v1
	// 		int k; // $t0
	// 		int smallest; // $t4
	// 		int besti; // $t5
	// 		int bestk; // $t7
	// 		int sign; // $t3
	// 		int sign0; // $t0
	// 		int sign1; // $a3

		/* begin block 1.1 */
			// Start line: 212
			// Start offset: 0x0001C964
			// Variables:
		// 		int upper; // $a1
		// 		int lower; // $v1
		/* end block 1.1 */
		// End offset: 0x0001C9BC
		// End Line: 228

		/* begin block 1.2 */
			// Start line: 235
			// Start offset: 0x0001C9F0
			// Variables:
		// 		int upper; // $a1
		// 		int lower; // $a0
		/* end block 1.2 */
		// End offset: 0x0001CA60
		// End Line: 249
	/* end block 1 */
	// End offset: 0x0001CC30
	// End Line: 273

	/* begin block 2 */
		// Start line: 416
	/* end block 2 */
	// End Line: 417

	/* begin block 3 */
		// Start line: 427
	/* end block 3 */
	// End Line: 428

	/* begin block 4 */
		// Start line: 431
	/* end block 4 */
	// End Line: 432

void bFindCollisionPoint(CDATA2D *body, CRET2D *collisionResult)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int *piVar6;
	CDATA2D *pCVar7;
	uint uVar8;
	int *piVar9;
	int iVar10;
	int iVar11;
	uint uVar12;
	int *piVar13;
	int *piVar14;
	int iVar15;
	int iVar16;
	uint uVar17;
	VECTOR *pVVar18;
	int iVar19;

	uVar17 = 0;
	iVar19 = 0;
	iVar15 = 0;
	bVar1 = false;
	iVar16 = body->limit[0] + 1;
	if ((body->isCameraOrTanner == 0) && (body[1].isCameraOrTanner == 0)) {
		if ((body[1].length[0] << 2 <= body[1].length[1]) ||
			(body[1].length[1] << 2 <= body[1].length[0])) {
			bVar1 = true;
		}
	}
	uVar8 = 1;
	do {
		iVar11 = 1;
		uVar12 = uVar8 - 1;
		piVar6 = body[uVar8].dist + 1;
		do {
			iVar5 = piVar6[2] - *piVar6;
			iVar2 = *piVar6 + piVar6[2];
			if ((iVar5 < iVar16) &&
				(iVar15 = -1, iVar16 = iVar5, uVar17 = uVar8, iVar19 = iVar11, uVar8 == 1)) {
				iVar15 = 1;
			}
			if ((iVar2 < iVar16) &&
				(iVar15 = 1, iVar16 = iVar2, uVar17 = uVar8, iVar19 = iVar11, uVar8 == 1)) {
				iVar15 = -1;
			}
			iVar11 = iVar11 + -1;
			piVar6 = piVar6 + -1;
		} while (iVar11 != -1);
		iVar11 = 1;
		uVar8 = uVar12;
	} while (uVar12 != 0xffffffff);
	if (bVar1) {
		piVar9 = body[1].length + 1;
		piVar6 = body[1].length;
		piVar14 = body[1].dist + 1;
		piVar13 = body[1].limit + 1;
		do {
			iVar5 = *piVar13 - *piVar14;
			iVar2 = *piVar14 + *piVar13;
			if ((iVar5 < iVar2) && (*piVar9 < *piVar6 << 2)) {
				uVar17 = 1;
				iVar15 = 1;
				iVar19 = iVar11;
			}
			if ((iVar2 < iVar5) && (*piVar9 < *piVar6 << 2)) {
				uVar17 = 1;
				iVar15 = -1;
				iVar19 = iVar11;
			}
			piVar9 = piVar9 + -1;
			piVar6 = piVar6 + 1;
			piVar14 = piVar14 + -1;
			iVar11 = iVar11 + -1;
			piVar13 = piVar13 + -1;
		} while (iVar11 != -1);
	}
	pCVar7 = body + (uVar17 ^ 1);
	pVVar18 = body[uVar17].axis + iVar19;
	iVar5 = pCVar7->axis[0].vx;
	iVar2 = pVVar18->vx;
	piVar6 = &body[uVar17].axis[iVar19].vz;
	iVar11 = *piVar6;
	iVar19 = iVar15;
	if (-1 < iVar5 * iVar2 + pCVar7->axis[0].vz * iVar11 + 0x800) {
		iVar19 = -iVar15;
	}
	iVar3 = pCVar7->axis[1].vx;
	iVar10 = iVar15;
	if (-1 < iVar3 * iVar2 + pCVar7->axis[1].vz * iVar11 + 0x800) {
		iVar10 = -iVar15;
	}
	(collisionResult->hit).vx =
		(pCVar7->x).vx +
		(iVar5 * pCVar7->length[0] * iVar19 + iVar3 * pCVar7->length[1] * iVar10 + 0x800 >> 0xc);
	iVar11 = pCVar7->axis[0].vz;
	iVar2 = pCVar7->length[0];
	iVar4 = pCVar7->axis[1].vz;
	iVar5 = pCVar7->length[1];
	iVar3 = (pCVar7->x).vz;
	collisionResult->penetration = iVar16;
	(collisionResult->hit).vz =
		iVar3 + (iVar11 * iVar2 * iVar19 + iVar4 * iVar5 * iVar10 + 0x800 >> 0xc);
	if (uVar17 != 0) {
		iVar15 = -iVar15;
	}
	iVar16 = pVVar18->vx;
	(collisionResult->surfNormal).vy = 0;
	(collisionResult->surfNormal).vx = iVar16 * iVar15;
	(collisionResult->surfNormal).vz = *piVar6 * iVar15;
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ bFindCollisionTime(struct CDATA2D *cd /*$s5*/, struct CRET2D *collisionResult /*stack 4*/)
 // line 275, offset 0x0001cc30
	/* begin block 1 */
		// Start line: 276
		// Start offset: 0x0001CC30
		// Variables:
	// 		int i; // $s4
	// 		int q; // $s0
	// 		int hit; // $t2
	// 		int neverfree; // $fp
	// 		int time; // $s1
	// 		int step; // $s3
	// 		struct CDATA2D original[2]; // stack offset -248
	/* end block 1 */
	// End offset: 0x0001CEEC
	// End Line: 357

	/* begin block 2 */
		// Start line: 635
	/* end block 2 */
	// End Line: 636

	/* begin block 3 */
		// Start line: 638
	/* end block 3 */
	// End Line: 639

int bFindCollisionTime(CDATA2D *cd, CRET2D *collisionResult)
{
	UNIMPLEMENTED();
	return 0;
	/*
	undefined4 *puVar1;
	int iVar2;
	long lVar3;
	undefined4 uVar4;
	long lVar5;
	CDATA2D *pCVar6;
	undefined4 *puVar7;
	int iVar8;
	undefined4 *puVar9;
	undefined4 *puVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	int iVar15;
	long *plVar16;
	long *plVar17;
	int iVar18;
	int *piVar19;
	int iVar20;
	int iVar21;
	long alStack248[16];
	int aiStack184[4];
	undefined4 auStack168[21];
	int local_54[9];
	long *local_30;
	long *local_2c;

	iVar13 = 1;
	iVar21 = 1;
	iVar15 = 0x1000;
	iVar18 = 0x800;
	iVar20 = 1;
	pCVar6 = cd + 1;
	iVar12 = 100;
	local_30 = alStack248;
	local_2c = alStack248 + 2;
	do {
		iVar14 = 1;
		puVar10 = (undefined4 *)((int)auStack168 + iVar12);
		puVar7 = (undefined4 *)((int)cd->dist + iVar12 + 4);
		puVar9 = (undefined4 *)((int)auStack168 + iVar12 + 8);
		*(long *)((int)local_30 + iVar12) = (pCVar6->x).vx;
		*(long *)((int)local_2c + iVar12) = (pCVar6->x).vz;
		*(int *)((int)aiStack184 + iVar12) = pCVar6->theta;
		do {
			puVar1 = puVar7 + 2;
			uVar4 = *puVar7;
			puVar7 = puVar7 + -1;
			iVar14 = iVar14 + -1;
			*puVar9 = *puVar1;
			*puVar10 = uVar4;
			puVar10 = puVar10 + -1;
			puVar9 = puVar9 + -1;
		} while (iVar14 != -1);
		pCVar6 = pCVar6 + -1;
		iVar20 = iVar20 + -1;
		iVar12 = iVar12 + -100;
	} while (iVar20 != -1);
	iVar12 = 7;
	do {
		iVar14 = 1;
		iVar20 = iVar12 + -1;
		pCVar6 = cd + 1;
		do {
			iVar8 = (pCVar6->vel).vx >> 1;
			iVar2 = (pCVar6->vel).vz;
			iVar11 = pCVar6->avel >> 1;
			(pCVar6->vel).vx = iVar8;
			pCVar6->avel = iVar11;
			iVar2 = iVar2 >> 1;
			(pCVar6->vel).vz = iVar2;
			if (iVar13 == 0) {
				(pCVar6->x).vx = (pCVar6->x).vx + iVar8;
				iVar8 = pCVar6->theta;
				(pCVar6->x).vz = (pCVar6->x).vz + iVar2;
				iVar8 = iVar8 + iVar11;
			}
			else {
				(pCVar6->x).vx = (pCVar6->x).vx - iVar8;
				iVar8 = pCVar6->theta;
				(pCVar6->x).vz = (pCVar6->x).vz - iVar2;
				iVar8 = iVar8 - iVar11;
			}
			pCVar6->theta = iVar8;
			iVar14 = iVar14 + -1;
			pCVar6 = pCVar6 + -1;
		} while (iVar14 != -1);
		if (iVar13 == 0) {
			iVar21 = 0;
			iVar13 = iVar18;
		}
		else {
			iVar13 = -iVar18;
		}
		iVar15 = iVar15 + iVar13;
		iVar13 = bcollided2d(cd, 0);
		if (iVar12 != 0) {
			iVar18 = iVar18 >> 1;
		}
		iVar14 = 1;
		iVar12 = iVar20;
	} while (iVar20 != -1);
	if (iVar13 == 0) {
		pCVar6 = cd + 1;
		do {
			iVar12 = (pCVar6->vel).vz;
			iVar20 = pCVar6->avel;
			iVar14 = iVar14 + -1;
			(pCVar6->x).vx = (pCVar6->x).vx + (pCVar6->vel).vx;
			iVar13 = pCVar6->theta;
			(pCVar6->x).vz = (pCVar6->x).vz + iVar12;
			pCVar6->theta = iVar13 + iVar20;
			pCVar6 = pCVar6 + -1;
		} while (iVar14 != -1);
		bcollided2d(cd, 0);
		iVar15 = iVar15 + iVar18;
	}
	else {
		iVar13 = 1;
		if (iVar21 != 0) {
			piVar19 = local_54;
			plVar17 = local_2c + 0x19;
			pCVar6 = cd + 1;
			plVar16 = local_30 + 0x19;
			do {
				iVar15 = *piVar19;
				piVar19 = piVar19 + -0x19;
				lVar5 = *plVar17;
				plVar17 = plVar17 + -0x19;
				lVar3 = *plVar16;
				plVar16 = plVar16 + -0x19;
				iVar13 = iVar13 + -1;
				(pCVar6->x).vx = lVar3;
				(pCVar6->x).vz = lVar5;
				pCVar6->theta = iVar15;
				bcollided2d(cd, 0);
				pCVar6 = pCVar6 + -1;
			} while (iVar13 != -1);
			iVar15 = 0x1000;
		}
	}
	collisionResult->neverfree = iVar21;
	return iVar15;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ApplyDamage(struct _CAR_DATA *cp /*$a0*/, char region /*$a1*/, int value /*$a2*/, char fakeDamage /*$a3*/)
 // line 384, offset 0x0001ceec
	/* begin block 1 */
		// Start line: 385
		// Start offset: 0x0001CEEC
		// Variables:
	// 		short *pRegion; // $t0
	/* end block 1 */
	// End offset: 0x0001D0B0
	// End Line: 465

	/* begin block 2 */
		// Start line: 965
	/* end block 2 */
	// End Line: 966

	/* begin block 3 */
		// Start line: 993
	/* end block 3 */
	// End Line: 994

void ApplyDamage(_CAR_DATA *cp, char region, int value, char fakeDamage)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	int iVar2;
	int iVar3;
	ushort *puVar4;
	short *psVar5;

	iVar3 = (int)region;
	puVar4 = (ushort *)((cp->ap).damage + iVar3);
	if ((cp->controlType == '\x01') || (cp->controlType == '\x04')) {
		value = value * gPlayerDamageFactor + 0x800 >> 0xc;
	}
	else {
		value = value << 1;
	}
	if (cp->controlType == '\x03') {
		if (gCopDifficultyLevel == 1) {
			iVar2 = value * 0xc;
		}
		else {
			if (gCopDifficultyLevel != 2) goto LAB_0001cf9c;
			iVar2 = value * 7;
		}
		value = iVar2 >> 4;
		if (iVar2 < 0) {
			value = iVar2 + 0xf >> 4;
		}
	}
LAB_0001cf9c:
	wibblewibblewoo = iVar3;
	if (fakeDamage == '\0') {
		if ((int)(uint)cp->totalDamage < 0xffff - value) {
			cp->totalDamage = cp->totalDamage + (short)value;
		}
		else {
			cp->totalDamage = 0xffff;
		}
	}
	uVar1 = *puVar4;
	*puVar4 = (ushort)((uint)uVar1 + value);
	if (0xfff < (int)(((uint)uVar1 + value) * 0x10000) >> 0x10) {
		*puVar4 = 0xfff;
	}
	if (iVar3 == 1) {
		iVar3 = 0;
	}
	else {
		if (iVar3 < 2) {
			iVar3 = -1;
			if (iVar3 == 0) {
				iVar3 = 1;
			}
		}
		else {
			if (iVar3 == 3) {
				iVar3 = 4;
			}
			else {
				iVar3 = -1;
				if (iVar3 == 4) {
					iVar3 = 3;
				}
			}
		}
	}
	if (iVar3 != -1) {
		psVar5 = (cp->ap).damage + iVar3;
		value = value >> 1;
		if (*psVar5 < value) {
			if (fakeDamage == '\0') {
				if ((int)(uint)cp->totalDamage < 0xffff - (value - *psVar5)) {
					cp->totalDamage = cp->totalDamage + ((short)value - *psVar5);
				}
				else {
					cp->totalDamage = 0xffff;
				}
			}
			*psVar5 = (short)value;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ DamageCar3D(struct _CAR_DATA *cp /*$s1*/, long (*delta)[4] /*$t4*/, int strikeVel /*$t6*/, struct _CAR_DATA *pOtherCar /*$s2*/)
 // line 470, offset 0x0001d0b0
	/* begin block 1 */
		// Start line: 471
		// Start offset: 0x0001D0B0
		// Variables:
	// 		int l; // $v1
	// 		int w; // $v0
	// 		int region; // $a1
	// 		long nose[4]; // stack offset -56
	// 		long door[4]; // stack offset -40
	// 		int impact; // $s3
	// 		int QQQ; // $t7

		/* begin block 1.1 */
			// Start line: 549
			// Start offset: 0x0001D388
			// Variables:
		// 		char fakeDamage; // $a3
		// 		char player_id; // $s0
		// 		char kludge; // $a3
		/* end block 1.1 */
		// End offset: 0x0001D424
		// End Line: 568
	/* end block 1 */
	// End offset: 0x0001D454
	// End Line: 572

	/* begin block 2 */
		// Start line: 1162
	/* end block 2 */
	// End Line: 1163

	/* begin block 3 */
		// Start line: 1168
	/* end block 3 */
	// End Line: 1169

int DamageCar3D(_CAR_DATA *cp, long(*delta)[4], int strikeVel, _CAR_DATA *pOtherCar)
{
	UNIMPLEMENTED();
	return 0;
	/*
	char region;
	int value;
	int iVar1;
	bool fakeDamage;
	int iVar2;

	iVar2 = strikeVel;
	if (strikeVel < 0) {
		iVar2 = strikeVel + 0x7f;
	}
	strikeVel = strikeVel * 0x177;
	value = (uint)(ushort)(((cp->ap).carCos)->colBox).vz << 0x10;
	value = (value >> 0x10) - (value >> 0x1f) >> 1;
	if (strikeVel < 0) {
		strikeVel = strikeVel + 0xff;
	}
	strikeVel = strikeVel >> 8;
	if (strikeVel < 0xa000) {
		if (cp->totalDamage == 0) {
			cp->totalDamage = 1;
		}
		iVar2 = 0;
	}
	else {
		iVar1 = (int)(cp->hd).where.m[2] * (*delta)[0] + (int)(cp->hd).where.m[5] * (*delta)[1] +
			(int)(cp->hd).where.m[8] * (*delta)[2] + 0x800 >> 0xc;
		if ((int)(cp->hd).where.m[0] * (*delta)[0] + (int)(cp->hd).where.m[3] * (*delta)[1] +
			(int)(cp->hd).where.m[6] * (*delta)[2] + 0x800 >> 0xc < 1) {
			region = '\0';
			if ((iVar1 <= value) && (region = '\x04', -value < iVar1)) {
				region = '\x05';
			}
		}
		else {
			region = '\x01';
			if ((iVar1 <= value) && (region = '\x03', -value < iVar1)) {
				region = '\x02';
			}
		}
		if (cp->controlType == '\x01') {
			value = (strikeVel / 0x15e + 0x200) * 3;
			if (value < 0) {
				value = value + 7;
			}
			value = value >> 3;
			if (0x477 < value) {
				value = 0x477;
			}
		}
		else {
			if (cp->controlType == '\x04') {
				if (pOtherCar->controlType == '\x01') {
					value = (strikeVel / 0x15e + 0x200) * 3;
					if (value < 0) {
						value = value + 7;
					}
					value = value >> 3;
					if (0x477 < value) {
						value = 0x477;
					}
					cp->ai[100] = 0x32;
				}
				else {
					value = strikeVel / 0x15e + 0x200;
					if (value < 0) {
						value = strikeVel / 0x15e + 0x203;
					}
					value = value >> 2;
					if (0x2fa < value) {
						value = 0x2fa;
					}
					if (cp->ai[100] == 0) {
						value = 0;
					}
				}
			}
			else {
				iVar1 = (strikeVel / 400 + 0x400) * 7;
				value = iVar1 >> 3;
				if (iVar1 < 0) {
					value = iVar1 + 7 >> 3;
				}
			}
		}
		fakeDamage = false;
		if (cp->controlType == '\x03') {
			fakeDamage = pOtherCar->controlType == '\x03';
		}
		ApplyDamage(cp, region, value, fakeDamage);
		value = GetPlayerId(cp);
		region = (char)value;
		if (region < '\0') {
			value = GetPlayerId(pOtherCar);
			region = (char)value;
		}
		value = GetPlayerId(cp);
		if ((value != 0) || (value = 2, pOtherCar->controlType != '\x02')) {
			iVar1 = GetPlayerId(pOtherCar);
			value = 1;
			if ((iVar1 == 0) && (cp->controlType == '\x02')) {
				value = 2;
			}
		}
		CollisionSound(region, cp, iVar2 >> 7, value);
		iVar2 = 1;
	}
	return iVar2;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DamageCar(struct _CAR_DATA *cp /*$s2*/, struct CDATA2D *cd /*$s1*/, struct CRET2D *collisionResult /*$s3*/, int strikeVel /*$s0*/)
 // line 587, offset 0x0001d454
	/* begin block 1 */
		// Start line: 588
		// Start offset: 0x0001D454
		// Variables:
	// 		struct VECTOR delta; // stack offset -48
	// 		int l; // $v1
	// 		int w; // $v0
	// 		int region; // $a1
	// 		int damage; // $a2
	// 		char player_id; // $s5
	// 		int impact; // $s4
	// 		int QQQ; // $t0
	/* end block 1 */
	// End offset: 0x0001D668
	// End Line: 633

	/* begin block 2 */
		// Start line: 1425
	/* end block 2 */
	// End Line: 1426

	/* begin block 3 */
		// Start line: 1441
	/* end block 3 */
	// End Line: 1442

void DamageCar(_CAR_DATA *cp, CDATA2D *cd, CRET2D *collisionResult, int strikeVel)
{
	UNIMPLEMENTED();
	/*
	int impact;
	int iVar1;
	int value;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar1 = GetPlayerId(cp);
	value = (uint)(ushort)(((cp->ap).carCos)->colBox).vz << 0x10;
	impact = strikeVel / 600;
	value = (value >> 0x10) - (value >> 0x1f) >> 1;
	if ((0x4fff < strikeVel) && (9 < (cp->hd).speed)) {
		iVar4 = (collisionResult->hit).vx - (cd->x).vx;
		iVar3 = (collisionResult->hit).vz - (cd->x).vz;
		iVar2 = cd->axis[0].vx * iVar4 + cd->axis[0].vz * iVar3 + 0x800 >> 0xc;
		if (cd->axis[1].vx * iVar4 + cd->axis[1].vz * iVar3 + 0x800 >> 0xc < 1) {
			iVar3 = 0;
			if ((iVar2 <= value) && (iVar3 = 4, -value < iVar2)) {
				iVar3 = 5;
			}
		}
		else {
			iVar3 = 1;
			if ((iVar2 <= value) && (iVar3 = 3, -value < iVar2)) {
				iVar3 = 2;
			}
		}
		if (0x1f4000 < strikeVel) {
			strikeVel = 0x1f4000;
		}
		value = ((strikeVel / 300) * 0x400) / 0x5dc;
		if (0x800 < value) {
			value = 0x800;
		}
		value = value - (value * (cp->ap).damage[iVar3] >> 0xd);
		if (cp->controlType == '\x04') {
			if (cp->ai[100] == 0) {
				value = 0;
			}
			else {
				value = value / 2;
			}
		}
		ApplyDamage(cp, (char)iVar3, value, '\0');
		CollisionSound((char)iVar1, cp, impact, 0);
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ CarBuildingCollision(struct _CAR_DATA *cp /*$s3*/, struct BUILDING_BOX *building /*$s2*/, struct CELL_OBJECT *cop /*$s6*/, int mightBeABarrier /*$s1*/)
 // line 839, offset 0x0001d68c
	/* begin block 1 */
		// Start line: 840
		// Start offset: 0x0001D68C
		// Variables:
	// 		static struct CDATA2D cd[2]; // offset 0x0
	// 		static struct CRET2D collisionResult; // offset 0xd0
	// 		int debris_colour; // stack offset -48
	// 		struct VECTOR tempwhere; // stack offset -168
	// 		struct MODEL *pModel; // $s5
	// 		int player_id; // stack offset -44

		/* begin block 1.1 */
			// Start line: 866
			// Start offset: 0x0001D794
			// Variables:
		// 		struct SVECTOR boxDisp; // stack offset -152

			/* begin block 1.1.1 */
				// Start line: 908
				// Start offset: 0x0001D8F4
				// Variables:
			// 		int wbod; // $a1
			/* end block 1.1.1 */
			// End offset: 0x0001D9A4
			// End Line: 918
		/* end block 1.1 */
		// End offset: 0x0001D9A4
		// End Line: 920

		/* begin block 1.2 */
			// Start line: 977
			// Start offset: 0x0001DA64

			/* begin block 1.2.1 */
				// Start line: 977
				// Start offset: 0x0001DA64
				// Variables:
			// 		struct VECTOR velocity; // stack offset -144
			// 		long pointVel[4]; // stack offset -128
			// 		long reaction[4]; // stack offset -112
			// 		long lever[4]; // stack offset -96
			// 		int strikeVel; // $s1

				/* begin block 1.2.1.1 */
					// Start line: 1014
					// Start offset: 0x0001DC58
					// Variables:
				// 		short scale; // $a2
				/* end block 1.2.1.1 */
				// End offset: 0x0001DCA4
				// End Line: 1034

				/* begin block 1.2.1.2 */
					// Start line: 1050
					// Start offset: 0x0001DD04

					/* begin block 1.2.1.2.1 */
						// Start line: 1058
						// Start offset: 0x0001DD28
						// Variables:
					// 		struct SMASHABLE_OBJECT *sip; // $a1
					// 		struct SMASHABLE_OBJECT *match; // $s0
					// 		int chan; // $s1
					// 		int adjust; // $s2
					/* end block 1.2.1.2.1 */
					// End offset: 0x0001DE3C
					// End Line: 1079
				/* end block 1.2.1.2 */
				// End offset: 0x0001DEC4
				// End Line: 1093

				/* begin block 1.2.1.3 */
					// Start line: 1098
					// Start offset: 0x0001DEF4
					// Variables:
				// 		struct VECTOR LeafPosition; // stack offset -80
				/* end block 1.2.1.3 */
				// End offset: 0x0001DEF4
				// End Line: 1098

				/* begin block 1.2.1.4 */
					// Start line: 1116
					// Start offset: 0x0001DF50

					/* begin block 1.2.1.4.1 */
						// Start line: 1119
						// Start offset: 0x0001DF90
						// Variables:
					// 		struct VECTOR lamp_velocity; // stack offset -64
					/* end block 1.2.1.4.1 */
					// End offset: 0x0001DFC4
					// End Line: 1123
				/* end block 1.2.1.4 */
				// End offset: 0x0001DFC4
				// End Line: 1124

				/* begin block 1.2.1.5 */
					// Start line: 1143
					// Start offset: 0x0001E058
					// Variables:
				// 		int twistY; // $a1
				// 		int lever_dot_n; // $a0
				// 		int displacementsquared; // $v1
				// 		int denom; // $v1
				/* end block 1.2.1.5 */
				// End offset: 0x0001E170
				// End Line: 1155
			/* end block 1.2.1 */
			// End offset: 0x0001E37C
			// End Line: 1184
		/* end block 1.2 */
		// End offset: 0x0001E384
		// End Line: 1188
	/* end block 1 */
	// End offset: 0x0001E3E8
	// End Line: 1195

	/* begin block 2 */
		// Start line: 1966
	/* end block 2 */
	// End Line: 1967

int CarBuildingCollision(_CAR_DATA *cp, BUILDING_BOX *building, CELL_OBJECT *cop, int mightBeABarrier)
{
	UNIMPLEMENTED();
	return 0;
	/*
	uchar uVar1;
	undefined4 in_zero;
	undefined4 in_at;
	uint uVar2;
	long lVar3;
	int iVar4;
	int iVar5;
	int chan;
	long lVar6;
	int iVar7;
	uint uVar8;
	CAR_COSMETICS *pCVar9;
	int iVar10;
	int strikeVel;
	SMASHABLE_OBJECT *pSVar11;
	short scale;
	SMASHABLE_OBJECT *pSVar12;
	MODEL *pMVar13;
	undefined4 local_98;
	uint local_94;
	VECTOR local_90;
	int local_80;
	int local_7c;
	int local_78;
	int local_60;
	int local_5c;
	int local_58;
	VECTOR local_50;
	VECTOR VStack64;
	int local_30;
	int local_2c;

	pMVar13 = modelpointers1536[cop->type];
	local_2c = GetPlayerId(cp);
	DAT_000ac940 = (uint)(cp->controlType == '\x05');
	if (cp->controlType == '\x06') {
		DAT_000ac940 = DAT_000ac940 + 2;
	}
	DAT_000ac9a4 = (uint)(mightBeABarrier == 0);
	strikeVel = (cp->hd).oBox.location.vy + (int)*(short *)&(building->pos).vy;
	if (strikeVel < 0) {
		strikeVel = -strikeVel;
	}
	chan = (uint)(ushort)(cp->hd).oBox.length[1] << 0x10;
	uVar2 = 0;
	if (((strikeVel <= building->height / 2 + ((chan >> 0x10) - (chan >> 0x1f) >> 1)) &&
		(uVar2 = 0, (cop->pos).vx != -0x2b90140)) && (uVar2 = 0, (pMVar13->shape_flags & 0x10) == 0))
	{
		lVar3 = (cp->hd).where.t[0];
		lVar6 = (cp->hd).where.t[2];
		local_30 = GetDebrisColour(cp);
		setCopControlWord(2, 0, *(undefined4 *)(cp->hd).where.m);
		setCopControlWord(2, 0x800, *(undefined4 *)((cp->hd).where.m + 2));
		setCopControlWord(2, 0x1000, *(undefined4 *)((cp->hd).where.m + 4));
		setCopControlWord(2, 0x1800, *(undefined4 *)((cp->hd).where.m + 6));
		setCopControlWord(2, 0x2000, *(undefined4 *)((cp->hd).where.m + 8));
		setCopControlWord(2, 0x2800, (cp->hd).where.t[0]);
		setCopControlWord(2, 0x3000, (cp->hd).where.t[1]);
		setCopControlWord(2, 0x3800, (cp->hd).where.t[2]);
		pCVar9 = (cp->ap).carCos;
		local_98 = CONCAT22(-(pCVar9->cog).vy, -(pCVar9->cog).vx);
		local_94 = local_94 & 0xffff0000 | (uint)(ushort)-(pCVar9->cog).vz;
		setCopReg(2, in_zero, local_98);
		setCopReg(2, in_at, local_94);
		copFunction(2, 0x480012);
		cd_24 = getCopReg(2, 0x19);
		DAT_000ac8e4 = getCopReg(2, 0x1a);
		DAT_000ac8e8 = getCopReg(2, 0x1b);
		DAT_000ac920 = (cp->hd).direction;
		if (cp->controlType == '\x06') {
			DAT_000ac910 = *(int *)(cp->st + 0x1c) + 0x800 >> 0xc;
			DAT_000ac918 = *(int *)(cp->st + 0x24) + 0x800 >> 0xc;
			strikeVel = (cp->hd).where.t[2];
			(cp->hd).where.t[0] = (cp->hd).where.t[0] + DAT_000ac910;
			(cp->hd).where.t[2] = strikeVel + DAT_000ac918;
			DAT_000ac924 = 0x5a;
			DAT_000ac928 = 0x5a;
		}
		else {
			if (cp->controlType == '\x05') {
				DAT_000ac910 = 0;
				DAT_000ac918 = 0;
				DAT_000ac928 = 5;
				DAT_000ac924 = gCameraDistance / 2;
			}
			else {
				scale = (((cp->ap).carCos)->colBox).vx;
				DAT_000ac910 = *(int *)(cp->st + 0x1c) + 0x800 >> 0xc;
				DAT_000ac918 = *(int *)(cp->st + 0x24) + 0x800 >> 0xc;
				strikeVel = (cp->hd).where.t[2];
				(cp->hd).where.t[0] = (cp->hd).where.t[0] + DAT_000ac910;
				pCVar9 = (cp->ap).carCos;
				(cp->hd).where.t[2] = strikeVel + DAT_000ac918;
				DAT_000ac924 = (int)(pCVar9->colBox).vz + 0xf;
				DAT_000ac928 = (int)scale + 0xf;
				if ((handlingType[cp->hndType].fourWheelDrive == '\x01') || (cp->hndType == 5)) {
					DAT_000ac928 = DAT_000ac928 * 0xd;
					if (DAT_000ac928 < 0) {
						DAT_000ac928 = DAT_000ac928 + 0xf;
					}
					DAT_000ac928 = DAT_000ac928 >> 4;
				}
			}
		}
		DAT_000ac93c = (*(int *)(cp->st + 0x2c) + 0x800 >> 0xc) * 5 >> 5;
		DAT_000ac944 = (cp->hd).where.t[0] +
			((int)(((uint)*(ushort *)&(building->pos).vx - (uint)*(ushort *)(cp->hd).where.t)
				* 0x10000) >> 0x10);
		DAT_000ac94c = (cp->hd).where.t[2] +
			((int)(((uint)*(ushort *)&(building->pos).vz -
			(uint)*(ushort *)((cp->hd).where.t + 2)) * 0x10000) >> 0x10);
		DAT_000ac984 = building->theta;
		DAT_000ac988 = building->xsize;
		DAT_000ac98c = building->zsize;
		DAT_000ac974 = 0;
		DAT_000ac97c = 0;
		DAT_000ac9a0 = 0;
		if (cp->controlType == '\x05') {
			strikeVel = bcollided2d((CDATA2D *)&cd_24, 1);
			uVar2 = (uint)(strikeVel != 0);
		}
		else {
			strikeVel = bcollided2d((CDATA2D *)&cd_24, 0);
			if (strikeVel == 0) {
				uVar2 = 0;
			}
			else {
				bFindCollisionTime((CDATA2D *)&cd_24, (CRET2D *)&collisionResult_25);
				bFindCollisionPoint((CDATA2D *)&cd_24, (CRET2D *)&collisionResult_25);
				DAT_000ac9c0 = -DAT_000ac9c0;
				DAT_000ac9c4 = 0;
				DAT_000ac9b4 = (cp->hd).where.t[1] + 0x29;
				DAT_000ac9c8 = -DAT_000ac9c8;
				local_60 = (cp->hd).where.t[0] + (DAT_000ac9d0 * DAT_000ac9c0 + 0x800 >> 0xc);
				(cp->hd).where.t[0] = local_60;
				local_58 = (cp->hd).where.t[2] + (DAT_000ac9d0 * DAT_000ac9c8 + 0x800 >> 0xc);
				(cp->hd).where.t[2] = local_58;
				local_58 = DAT_000ac9b8 - local_58;
				local_5c = DAT_000ac9b4 - (cp->hd).where.t[1];
				local_60 = collisionResult_25 - local_60;
				local_80 = ((*(int *)(cp->st + 0x2c) * local_58 - *(int *)(cp->st + 0x30) * local_5c) +
					0x800 >> 0xc) + *(int *)(cp->st + 0x1c);
				local_7c = ((*(int *)(cp->st + 0x30) * local_60 - *(int *)(cp->st + 0x28) * local_58) +
					0x800 >> 0xc) + *(int *)(cp->st + 0x20);
				local_78 = ((*(int *)(cp->st + 0x28) * local_5c - *(int *)(cp->st + 0x2c) * local_60) +
					0x800 >> 0xc) + *(int *)(cp->st + 0x24);
				strikeVel = local_80;
				if (local_80 < 0) {
					strikeVel = local_80 + 0xff;
				}
				chan = DAT_000ac9c0;
				if (DAT_000ac9c0 < 0) {
					chan = DAT_000ac9c0 + 0xf;
				}
				iVar7 = local_7c;
				if (local_7c < 0) {
					iVar7 = local_7c + 0xff;
				}
				iVar4 = DAT_000ac9c4;
				if (DAT_000ac9c4 < 0) {
					iVar4 = DAT_000ac9c4 + 0xf;
				}
				iVar10 = local_78;
				if (local_78 < 0) {
					iVar10 = local_78 + 0xff;
				}
				iVar5 = DAT_000ac9c8;
				if (DAT_000ac9c8 < 0) {
					iVar5 = DAT_000ac9c8 + 0xf;
				}
				chan = (strikeVel >> 8) * (chan >> 4) + (iVar7 >> 8) * (iVar4 >> 4) +
					(iVar10 >> 8) * (iVar5 >> 4);
				strikeVel = -chan;
				if (chan < 0) {
					if (cp->controlType == '\x01') {
						if (strikeVel < 0x20) {
							scale = (short)((uint)(chan * -0x800000) >> 0x10);
						}
						else {
							scale = 0x1000;
						}
						if ((pMVar13->flags2 & 0x800) == 0) {
							NoteFelony(&felonyData, '\x06', scale);
						}
						else {
							NoteFelony(&felonyData, '\a', scale);
						}
					}
					DAT_000ac9b4 = -DAT_000ac9b4;
					iVar7 = *(int *)(cp->st + 0x1c);
					if (iVar7 < 0) {
						iVar7 = iVar7 + 0xfff;
					}
					local_90.vx = iVar7 >> 0xc;
					iVar7 = *(int *)(cp->st + 0x24);
					local_90.vy = -0x11;
					if (iVar7 < 0) {
						iVar7 = iVar7 + 0xfff;
					}
					local_90.vz = iVar7 >> 0xc;
					if ((pMVar13->flags2 & 0x800) != 0) {
						damage_object(cop, &local_90);
						strikeVel = local_30 << 0x10;
						if ((pMVar13->shape_flags & 8) == 0) {
							pSVar11 = &smashable;
							chan = smashable.modelIdx;
							pSVar12 = (SMASHABLE_OBJECT *)0x0;
							if (smashable.name != (char *)0x0) {
								while ((pSVar12 = pSVar11, modelpointers1536[chan] != pMVar13 &&
									(pSVar12 = (SMASHABLE_OBJECT *)0x0, pSVar11[1].name != (char *)0x0))) {
									chan = pSVar11[1].modelIdx;
									pSVar11 = pSVar11 + 1;
								}
							}
							if (pSVar12 == (SMASHABLE_OBJECT *)0x0) {
								pSVar12 = &smashable;
							}
							uVar2 = local_90.vx ^ local_90.vz;
							uVar8 = collisionResult_25 ^ DAT_000ac9b8;
							chan = GetFreeChannel();
							if ((1 < NumPlayers) && (NoPlayerControl == 0)) {
								SetPlayerOwnsChannel(chan, (char)local_2c);
							}
							Start3DSoundVolPitch
							(chan, 1, pSVar12->sound, collisionResult_25, -DAT_000ac9b4, DAT_000ac9b8,
								pSVar12->volume, pSVar12->pitch + ((uVar2 * uVar8 & 0x3ff) - 0x200));
						}
						(cp->hd).where.t[0] = lVar3;
						(cp->hd).where.t[2] = lVar6;
						DAT_000ac9b4 = DAT_000ac9b4 + 0x1e;
						Setup_Sparks((VECTOR *)&collisionResult_25, &local_90, 10, '\0');
						Setup_Debris((VECTOR *)&collisionResult_25, &local_90, 5, 0);
						Setup_Debris((VECTOR *)&collisionResult_25, &local_90, 5, strikeVel);
						if (cp->controlType == '\x01') {
							SetPadVibration((int)**(char **)cp->ai, '\x03');
						}
						return 0;
					}
					if ((0x3600 < strikeVel) && (32000 < (cp->hd).wheel_speed + 16000U)) {
						if ((pMVar13->flags2 & 0x2000) == 0) {
							if ((gNight != 0) &&
								((modelpointers1536[gLastModelCollisionCheck]->flags2 & 0x1000) != 0)) {
								iVar7 = damage_lamp(cop);
								if (iVar7 != 0) {
									memset(&VStack64, 0, 0x10);
									DAT_000ac9b4 = 0xfffffd26;
									Setup_Sparks((VECTOR *)&collisionResult_25, &VStack64, 0x14, '\0');
									DAT_000ac9b4 = 0x2da;
								}
							}
							local_90.vy = local_90.vy + -0x14;
							DAT_000ac9b4 = DAT_000ac9b4 + 0x1e;
							Setup_Sparks((VECTOR *)&collisionResult_25, &local_90, 4, '\0');
							DAT_000ac9b4 = DAT_000ac9b4 + -0x1e;
							local_90.vy = local_90.vy + 0x14;
						}
						else {
							uVar2 = rand();
							local_50.vx = collisionResult_25;
							local_50.vy = -((uVar2 & 0xfe) + 600) - DAT_000ac9b4;
							local_50.vz = DAT_000ac9b8;
							AddLeaf(&local_50, 3, 1);
						}
						if ((0x1b000 < strikeVel) &&
							(Setup_Debris((VECTOR *)&collisionResult_25, &local_90, 6, local_30 << 0x10),
								cp->controlType == '\x01')) {
							SetPadVibration((int)**(char **)cp->ai, '\x01');
						}
					}
					DamageCar(cp, (CDATA2D *)&cd_24, (CRET2D *)&collisionResult_25, strikeVel);
					iVar7 = local_60 * DAT_000ac9c0 + local_5c * DAT_000ac9c4 + local_58 * DAT_000ac9c8 +
						0x800 >> 0xc;
					iVar7 = (((local_60 * local_60 + local_58 * local_58) - iVar7 * iVar7) *
						(int)car_cosmetics[(byte)(cp->ap).model].twistRateY + 0x800 >> 0xc) + 0x1000;
					if (strikeVel < 0x7f001) {
						strikeVel = (chan * -0x1000) / iVar7;
						if (iVar7 == 0) {
							trap(7);
						}
					}
					else {
						if (iVar7 == 0) {
							trap(7);
						}
						strikeVel = strikeVel / iVar7 << 0xc;
					}
					if (strikeVel < 0) {
						strikeVel = strikeVel + 0x3f;
					}
					strikeVel = strikeVel >> 6;
					chan = DAT_000ac9c0;
					if (DAT_000ac9c0 < 0) {
						chan = DAT_000ac9c0 + 0x3f;
					}
					iVar7 = strikeVel * (chan >> 6);
					chan = DAT_000ac9c4;
					if (DAT_000ac9c4 < 0) {
						chan = DAT_000ac9c4 + 0x3f;
					}
					iVar4 = strikeVel * (chan >> 6);
					chan = DAT_000ac9c8;
					if (DAT_000ac9c8 < 0) {
						chan = DAT_000ac9c8 + 0x3f;
					}
					strikeVel = strikeVel * (chan >> 6);
					if (cp->controlType != '\x04') {
						iVar10 = local_5c * strikeVel + 0x800;
						chan = iVar10 >> 0xc;
						if (cp->controlType == '\x03') {
							chan = iVar10 >> 0xd;
						}
						chan = (cp->hd).aacc[0] + chan;
						(cp->hd).aacc[0] = chan;
						iVar5 = local_58 * iVar4 + 0x800;
						iVar10 = iVar5 >> 0xc;
						if (cp->controlType == '\x03') {
							iVar10 = iVar5 >> 0xd;
						}
						(cp->hd).aacc[0] = chan - iVar10;
					}
					uVar1 = cp->controlType;
					(cp->hd).aacc[1] =
						((cp->hd).aacc[1] + (local_58 * iVar7 + 0x800 >> 0xc)) -
						(local_60 * strikeVel + 0x800 >> 0xc);
					if (uVar1 != '\x04') {
						iVar10 = local_60 * iVar4 + 0x800;
						chan = iVar10 >> 0xc;
						if (uVar1 == '\x03') {
							chan = iVar10 >> 0xd;
						}
						chan = (cp->hd).aacc[2] + chan;
						(cp->hd).aacc[2] = chan;
						iVar5 = local_5c * iVar7 + 0x800;
						iVar10 = iVar5 >> 0xc;
						if (cp->controlType == '\x03') {
							iVar10 = iVar5 >> 0xd;
						}
						(cp->hd).aacc[2] = chan - iVar10;
					}
					uVar1 = cp->controlType;
					*(int *)(cp->st + 0x1c) = *(int *)(cp->st + 0x1c) + iVar7;
					if (uVar1 != '\x04') {
						*(int *)(cp->st + 0x20) = *(int *)(cp->st + 0x20) + iVar4;
					}
					*(int *)(cp->st + 0x24) = *(int *)(cp->st + 0x24) + strikeVel;
				}
				uVar2 = 1;
			}
			strikeVel = *(int *)(cp->st + 0x24);
			(cp->hd).where.t[0] = (cp->hd).where.t[0] - (*(int *)(cp->st + 0x1c) + 0x800 >> 0xc);
			(cp->hd).where.t[2] = (cp->hd).where.t[2] - (strikeVel + 0x800 >> 0xc);
		}
	}
	return uVar2;*/
}





