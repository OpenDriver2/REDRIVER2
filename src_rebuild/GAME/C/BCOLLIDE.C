#include "THISDUST.H"
#include "BCOLLIDE.H"
#include "COSMETIC.H"
#include "PAD.H"
#include "DEBRIS.H"
#include "EVENT.H"
#include "OBJCOLL.H"
#include "MODELS.H"
#include "SOUND.H"
#include "GAMESND.H"
#include "GLAUNCH.H"
#include "MAIN.H"
#include "MISSION.H"
#include "FELONY.H"
#include "WHEELFORCES.H"
#include "HANDLING.H"
#include "CAMERA.H"
#include "OBJANIM.H"

#include "STRINGS.H"
#include "GTEREG.H"
#include "INLINE_C.H"
#include <stdlib.h>

#define COLLISION_DEBUG

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

int boxOverlap = 0;

// Checks of two bodies collides (basic check)
// also initializes axes
// [D] [A]
int bcollided2d(CDATA2D *body, int needOverlap)
{
	short sVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	int uVar5;
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
	int uVar20;
	VECTOR *pVVar21;
	int *plVar22;
	int *piVar23;
	int iVar24;
	int *piVar25;
	VECTOR delta;

	iVar19 = 1;
	pCVar11 = body + 1;
	uVar5 = body[1].theta - body[0].theta;

	sVar1 = rcossin_tbl[(uVar5 + 0x400 & 0x7ff) * 2];
	sVar2 = rcossin_tbl[(uVar5 & 0x7ff) * 2];

	// calc axes of each box
	do {
		uVar5 = body[iVar19].theta & 0xfff;
		sVar3 = rcossin_tbl[uVar5 * 2];
		sVar4 = rcossin_tbl[uVar5 * 2 + 1];

		body[iVar19].axis[0].vx = sVar3;
		body[iVar19].axis[0].vz = sVar4;

		body[iVar19].axis[1].vz = -sVar3;
		body[iVar19].axis[1].vx = sVar4;

		iVar19--;
	} while (iVar19 != -1);

	uVar5 = 0;
	uVar20 = 1;

	piVar23 = body[1].limit;
	pVVar21 = body[1].axis;
	piVar25 = body[1].dist;

	plVar22 = (int*)&body[1].axis[0].vz;

	iVar24 = 100;

	iVar19 = body[0].x.vx;
	iVar6 = body[0].x.vz;

	iVar9 = body[1].x.vz;
	iVar8 = body[1].x.vx;

	do {
		
		piVar15 = piVar23 + 1;

		piVar17 = body[uVar20].length + 1;

		piVar16 = body[uVar5].length + 1;
		piVar14 = body[uVar5].length;

		piVar13 = plVar22 + 4;
		pVVar12 = body[uVar20].axis + 1;
		piVar10 = piVar25 + 1;

		iVar18 = 1;
		do {
			*piVar10 = (pVVar12->vx * (iVar19 - iVar8) + *piVar13 * (iVar6 - iVar9)) / 4096;
			iVar7 = *piVar17 + (*piVar16 * sVar1 + *piVar14 * sVar2) / 4096;
			*piVar15 = iVar7;

			if (iVar7 < *piVar10)
				return 0;
		
			if (*piVar10 < -iVar7)
				return 0;
		
			piVar17--;
			piVar16--;
			piVar15--;
			pVVar12--;
			iVar18--;
			piVar10--;
			piVar13 -= 4;
			piVar14++;
		} while (iVar18 != -1);

		uVar5 = uVar20 & 1;
		piVar23 -= 25;
		plVar22 -= 25;
		//pVVar21 = (VECTOR *)&pVVar21[-7].pad;
		piVar25 = piVar25-25;
		iVar24-= 100;

		uVar20--;

		if (uVar20 == -1) 
		{
			if (needOverlap != 0) 
			{
				iVar19 = body[1].dist[0];
				iVar6 = body[1].limit[0];

				if (iVar19 < 0)
					iVar19 = -iVar19;
			
				if (iVar6 < 0)
					iVar6 = -iVar6;
			
				iVar8 = iVar19 - iVar6;
				if (iVar8 < 0)
					iVar8 = iVar6 - iVar19;
			
				iVar9 = body[0].axis[0].vx;
				iVar6 = body[0].axis[0].vz;
				iVar19 = (iVar9 * body[1].axis[0].vx + iVar6 * body[1].axis[0].vz) / 4096;

				if (iVar19 < 0) 
					iVar19 = -iVar19;

				if (iVar19 < 0xb) 
				{
					iVar8 = -1;
				}
				else 
				{
					iVar8 = (iVar8 << 0xc) / iVar19;
					if (iVar19 == 0) 
					{
						trap(7);
					}
				}
				iVar19 = body[1].dist[1];
				iVar24 = body[1].limit[1];

				if (iVar19 < 0)
					iVar19 = -iVar19;
			
				if (iVar24 < 0)
					iVar24 = -iVar24;
			
				iVar18 = iVar19 - iVar24;
				if (iVar18 < 0)
					iVar18 = iVar24 - iVar19;
			
				iVar19 = (iVar9 * body[1].axis[1].vx + iVar6 * body[1].axis[1].vz) / 4096;
				if (iVar19 < 0)
					iVar19 = -iVar19;
			
				iVar6 = iVar8;
				if ((10 < iVar19) && (iVar6 = (iVar18 << 0xc) / iVar19, iVar19 == 0)) 
				{
					trap(7);
				}

				boxOverlap = iVar6;

				if (-1 < iVar8)
				{
					boxOverlap = iVar8;

					if(iVar6 < iVar8)
						boxOverlap = iVar6;
				}
			}
			return 1;
		}

	} while (true);

	return 0;
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

// [D]
void bFindCollisionPoint(CDATA2D *body, CRET2D *collisionResult)
{
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
	int local_t1_132;
	int *piVar12;
	int *piVar13;
	int iVar14;
	int iVar15;
	int local_t5_4;
	VECTOR *pVVar16;
	int iVar17;

	local_t5_4 = 0;
	iVar17 = 0;
	iVar14 = 0;
	bVar1 = false;
	iVar15 = body->limit[0] + 1;

	if ((body->isCameraOrTanner == 0) && (body[1].isCameraOrTanner == 0))
	{
		if ((body[1].length[0] << 2 <= body[1].length[1]) ||
			(body[1].length[1] << 2 <= body[1].length[0]))
		{
			bVar1 = true;
		}
	}

	uVar8 = 1;
	do {
		iVar11 = 1;
		local_t1_132 = uVar8 - 1;
		piVar6 = body[uVar8].dist + 1;

		do {
			iVar5 = piVar6[2] - *piVar6;
			iVar2 = *piVar6 + piVar6[2];

			if ((iVar5 < iVar15) &&
				(iVar14 = -1, iVar15 = iVar5, local_t5_4 = uVar8, iVar17 = iVar11, uVar8 == 1)) {
				iVar14 = 1;
			}

			if ((iVar2 < iVar15) &&
				(iVar14 = 1, iVar15 = iVar2, local_t5_4 = uVar8, iVar17 = iVar11, uVar8 == 1)) {
				iVar14 = -1;
			}

			iVar11--;
			piVar6--;
		} while (iVar11 != -1);

		iVar11 = 1;
		uVar8 = local_t1_132;
	} while (local_t1_132 != -1);

	if (bVar1) 
	{
		piVar9 = body[1].length + 1;
		piVar6 = body[1].length;
		piVar13 = body[1].dist + 1;
		piVar12 = body[1].limit + 1;

		do {
			iVar5 = *piVar12 - *piVar13;
			iVar2 = *piVar13 + *piVar12;

			if ((iVar5 < iVar2) && (*piVar9 < *piVar6 << 2)) 
			{
				local_t5_4 = 1;
				iVar14 = 1;
				iVar17 = iVar11;
			}

			if ((iVar2 < iVar5) && (*piVar9 < *piVar6 << 2)) 
			{
				local_t5_4 = 1;
				iVar14 = -1;
				iVar17 = iVar11;
			}

			piVar9--;
			piVar6++;
			piVar13--;
			iVar11--;
			piVar12--;
		} while (iVar11 != -1);
	}

	pCVar7 = body + (local_t5_4 ^ 1);
	pVVar16 = body[local_t5_4].axis + iVar17;
	iVar5 = pCVar7->axis[0].vx;
	iVar2 = pVVar16->vx;
	piVar6 = (int*)&body[local_t5_4].axis[iVar17].vz;
	iVar11 = body[local_t5_4].axis[iVar17].vz;
	iVar17 = iVar14;

	if (-1 < iVar5 * iVar2 + pCVar7->axis[0].vz * iVar11)
		iVar17 = -iVar14;

	iVar3 = pCVar7->axis[1].vx;
	iVar10 = iVar14;

	if (-1 < iVar3 * iVar2 + pCVar7->axis[1].vz * iVar11) 
		iVar10 = -iVar14;

	collisionResult->hit.vx = pCVar7->x.vx + (iVar5 * pCVar7->length[0] * iVar17 + iVar3 * pCVar7->length[1] * iVar10) / 4096;

	iVar11 = pCVar7->axis[0].vz;
	iVar2 = pCVar7->length[0];
	iVar4 = pCVar7->axis[1].vz;
	iVar5 = pCVar7->length[1];
	iVar3 = pCVar7->x.vz;

	collisionResult->penetration = iVar15;
	collisionResult->hit.vz = pCVar7->x.vz + (iVar11 * iVar2 * iVar17 + iVar4 * iVar5 * iVar10) / 4096;

	if (local_t5_4 != 0)
		iVar14 = -iVar14;

	iVar15 = pVVar16->vx;

	collisionResult->surfNormal.vy = 0;
	collisionResult->surfNormal.vx = iVar15 * iVar14;
	collisionResult->surfNormal.vz = *piVar6 * iVar14;
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

// [D]
int bFindCollisionTime(CDATA2D *cd, CRET2D *collisionResult)
{
	int *piVar1;
	VECTOR *pVVar2;
	int iVar3;
	long lVar4;
	CDATA2D *pCVar5;
	int *local_a1_184;
	int iVar6;
	int *piVar7;
	int *piVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	CDATA2D *pCVar14;
	long *plVar15;
	int iVar16;
	int iVar17;
	int iVar18;
	CDATA2D original[2];

	iVar11 = 1;
	iVar18 = 1;
	iVar13 = 0x1000;
	iVar16 = 0x800;
	iVar17 = 1;
	pCVar5 = cd + 1;
	iVar10 = 100;

	do {
		original[iVar17].x.vx = cd[iVar17].x.vx;
		original[iVar17].x.vz = cd[iVar17].x.vz;
		original[iVar17].theta = cd[iVar17].theta;

		original[iVar17].dist[0] = cd[iVar17].dist[0];
		original[iVar17].limit[0] = cd[iVar17].limit[0];
		original[iVar17].dist[1] = cd[iVar17].dist[1];
		original[iVar17].limit[1] = cd[iVar17].limit[1];
		iVar17--;

	} while (iVar17 != -1);

	iVar10 = 7;
	do {
		iVar12 = 1;
		iVar17 = iVar10 + -1;
		pCVar5 = cd + 1;
		do 
		{
			iVar6 = pCVar5->vel.vx / 2;
			iVar3 = pCVar5->vel.vz;

			iVar9 = pCVar5->avel / 2;

			pCVar5->vel.vx = iVar6;
			pCVar5->avel = iVar9;

			iVar3 = iVar3 >> 1;
			pCVar5->vel.vz = iVar3;

			if (iVar11 == 0) 
			{
				pCVar5->x.vx += iVar6;
				pCVar5->x.vz += iVar3;

				iVar6 = pCVar5->theta + iVar9;
			}
			else 
			{
				pCVar5->x.vx -= iVar6;
				pCVar5->x.vz -= iVar3;
				iVar6 = pCVar5->theta - iVar9;
			}

			pCVar5->theta = iVar6;
			iVar12--;
			pCVar5--;
		} while (iVar12 != -1);

		if (iVar11 == 0)
		{
			iVar18 = 0;
			iVar11 = iVar16;
		}
		else 
		{
			iVar11 = -iVar16;
		}

		iVar13 = iVar13 + iVar11;

		iVar11 = bcollided2d(cd, 0);

		if (iVar10 != 0)
			iVar16 = iVar16 >> 1;

		iVar12 = 1;
		iVar10 = iVar17;
	} while (iVar17 != -1);

	if (iVar11 == 0)
	{
		pCVar5 = cd + 1;

		do {	
			pCVar5->x.vx += pCVar5->vel.vx;
			pCVar5->x.vz += pCVar5->vel.vz;
			pCVar5->theta += pCVar5->avel;

			iVar12--;
			pCVar5--;
		} while (iVar12 != -1);

		bcollided2d(cd, 0);
		iVar13 = iVar13 + iVar16;
	}
	else 
	{
		iVar11 = 1;
		if (iVar18 != 0)
		{
			pCVar5 = cd + 1;
			pCVar14 = original + 1;

			do {
				pCVar5->x.vx = pCVar14->x.vx;
				pCVar5->x.vz = pCVar14->x.vz;
				pCVar5->theta = pCVar14->theta;

				bcollided2d(cd, 0);

				pCVar14--;
				pCVar5--;
				iVar11--;
			} while (iVar11 != -1);

			iVar13 = 0x1000;
		}
	}

	collisionResult->neverfree = iVar18;
	return iVar13;
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

int wibblewibblewoo = 0;

// [D]
void ApplyDamage(_CAR_DATA *cp, char region, int value, char fakeDamage)
{
	ushort uVar1;
	int iVar2;
	int iVar3;
	ushort *puVar4;
	short *psVar5;

	iVar3 = region;
	puVar4 = (ushort *)(cp->ap.damage + region);

	if (cp->controlType == 1 || cp->controlType == 4)
		value = value * gPlayerDamageFactor / 4096;
	else 
		value = value << 1;

	if (cp->controlType == 3)
	{
		if (gCopDifficultyLevel == 1) 
		{
			iVar2 = value * 0xc;
		}
		else 
		{
			if (gCopDifficultyLevel != 2) 
				goto LAB_0001cf9c;

			iVar2 = value * 7;
		}
		value = iVar2 >> 4;
	}
LAB_0001cf9c:
	wibblewibblewoo = region;
	if (fakeDamage == 0) {
		if (cp->totalDamage < 0xffff - value)
		{
			cp->totalDamage = cp->totalDamage + value;
		}
		else {
			cp->totalDamage = 0xffff;
		}
	}
	uVar1 = *puVar4;
	*puVar4 = (uVar1 + value);

	if (0xfff < ((uVar1 + value) * 0x10000) >> 0x10) 
		*puVar4 = 0xfff;

	if (iVar3 == 1) 
		iVar3 = 0;
	else if (iVar3 == 0)
		iVar3 = 1;
	else if (iVar3 == 3)
		iVar3 = 4;
	else if (iVar3 == 4)
		iVar3 = 3;
	else
		iVar3 = -1;


	if (iVar3 != -1)
	{
		psVar5 = cp->ap.damage + iVar3;
		value = value >> 1;

		if (*psVar5 < value) 
		{
			if (fakeDamage == 0) 
			{
				if (cp->totalDamage < 0xffff - (value - *psVar5)) 
					cp->totalDamage = cp->totalDamage + (value - *psVar5);
				else 
					cp->totalDamage = 0xffff;
			}

			*psVar5 = value;
		}
	}
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

// [D]
void DamageCar(_CAR_DATA *cp, CDATA2D *cd, CRET2D *collisionResult, int strikeVel)
{
	int impact;
	int iVar1;
	int value;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar1 = GetPlayerId(cp);
	value = cp->ap.carCos->colBox.vz << 0x10;
	impact = strikeVel / 600;

	value = (value >> 0x10) - (value >> 0x1f) >> 1;

	if (0x4fff < strikeVel && 9 < cp->hd.speed) 
	{
		iVar4 = collisionResult->hit.vx - cd->x.vx;
		iVar3 = collisionResult->hit.vz - cd->x.vz;

		iVar2 = (cd->axis[0].vx * iVar4 + cd->axis[0].vz * iVar3) / 4096;

		if ((cd->axis[1].vx * iVar4 + cd->axis[1].vz * iVar3) / 4096 < 1) 
		{
			iVar3 = 0;
			if ((iVar2 <= value) && (iVar3 = 4, -value < iVar2))
				iVar3 = 5;
		}
		else {
			iVar3 = 1;

			if ((iVar2 <= value) && (iVar3 = 3, -value < iVar2))
				iVar3 = 2;
		}
		if (0x1f4000 < strikeVel) 
			strikeVel = 0x1f4000;

		value = ((strikeVel / 300) * 0x400) / 0x5dc;
		if (0x800 < value)
			value = 0x800;
	
		value -= (value * cp->ap.damage[iVar3] >> 0xd);

		if (cp->controlType == 4)
		{
			if (cp->ai.l.takeDamage == 0)
				value = 0;
			else 
				value = value / 2;
		}

		ApplyDamage(cp, iVar3, value, 0);
		CollisionSound(iVar1, cp, impact, 0);
	}
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

// [D]
int CarBuildingCollision(_CAR_DATA *cp, BUILDING_BOX *building, CELL_OBJECT *cop, int mightBeABarrier)
{
	static CDATA2D cd[2]; // offset 0x0
	static CRET2D collisionResult; // offset 0xd0

	unsigned char uVar1;
	int iVar2;
	int uVar3;
	long lVar4;
	long lVar5;
	long lVar6;
	long lVar7;
	int strikeVel;
	long lVar8;
	int iVar9;
	int iVar10;
	int uVar11;
	CAR_COSMETICS *pCVar12;
	int iVar13;
	int iVar14;
	SMASHABLE_OBJECT *pSVar15;
	short scale;
	int iVar16;
	int iVar17;
	int iVar18;
	SMASHABLE_OBJECT *pSVar19;
	MODEL *pMVar20;
	VECTOR tempwhere;
	SVECTOR boxDisp;
	VECTOR velocity;
	long pointVel[4];
	long reaction[4];
	long lever[4];
	VECTOR LeafPosition;
	VECTOR lamp_velocity;
	int debris_colour;
	int player_id;

	pMVar20 = modelpointers[cop->type];
	iVar2 = GetPlayerId(cp);

	cd[0].isCameraOrTanner = (cp->controlType == 5);

	if (cp->controlType == 6)
		cd[0].isCameraOrTanner = cd[0].isCameraOrTanner + 2;

	cd[1].isCameraOrTanner = (mightBeABarrier == 0);
	iVar14 = cp->hd.oBox.location.vy + building->pos.vy;

	if (iVar14 < 0)
		iVar14 = -iVar14;

	strikeVel = cp->hd.oBox.length[1] << 0x10;
	uVar3 = 0;

	if (((iVar14 <= building->height / 2 + ((strikeVel >> 0x10) - (strikeVel >> 0x1f) >> 1)) &&
		(uVar3 = 0, (cop->pos).vx != 0xFD46FEC0)) && (uVar3 = 0, (pMVar20->shape_flags & 0x10) == 0))
	{
		lVar4 = cp->hd.where.t[0];
		lVar8 = cp->hd.where.t[2];

		iVar14 = GetDebrisColour(cp);
		gte_SetRotMatrix(&cp->hd.where);
		gte_SetTransMatrix(&cp->hd.where);

		pCVar12 = cp->ap.carCos;

		boxDisp.vx = -pCVar12->cog.vx;
		boxDisp.vy = -pCVar12->cog.vy;
		boxDisp.vz = -pCVar12->cog.vz;

		gte_ldv0(&boxDisp);

		docop2(0x480012);

		cd[0].x.vx = MAC1;
		cd[0].x.vy = MAC2;
		cd[0].x.vz = MAC3; 

		cd[0].theta = cp->hd.direction;

		if (cp->controlType == 6)
		{
			cd[0].vel.vx = cp->st.n.linearVelocity[0] / 4096;
			cd[0].vel.vz = cp->st.n.linearVelocity[2] / 4096;

			cp->hd.where.t[0] += cd[0].vel.vx;
			cp->hd.where.t[2] += cd[0].vel.vz;

			cd[0].length[0] = 90;
			cd[0].length[1] = 90;
		}
		else 
		{
			if (cp->controlType == 5) 
			{
				cd[0].vel.vx = 0;
				cd[0].vel.vz = 0;
				cd[0].length[1] = 5;
				cd[0].length[0] = gCameraDistance / 2;
			}
			else 
			{
				scale = cp->ap.carCos->colBox.vx;
				cd[0].vel.vx = cp->st.n.linearVelocity[0] / 4096;
				cd[0].vel.vz = cp->st.n.linearVelocity[2] / 4096;

				cp->hd.where.t[0] += cd[0].vel.vx;
				cp->hd.where.t[2] += cd[0].vel.vz;

				pCVar12 = cp->ap.carCos;
				cd[0].length[0] = pCVar12->colBox.vz + 15;
				cd[0].length[1] = pCVar12->colBox.vx + 15;

				if ((handlingType[cp->hndType].fourWheelDrive == 1) || (cp->hndType == 5))
				{
					cd[0].length[1] *= 13;
					cd[0].length[1] /= 16;
				}
			}
		}
		cd[0].avel = (cp->st.n.angularVelocity[1] / 4096) * 5 >> 5;
		cd[1].x.vx = building->pos.vx;
		cd[1].x.vz = building->pos.vz; 

		cd[1].theta = building->theta;

		cd[1].length[0] = building->xsize;
		cd[1].length[1] = building->zsize;

		cd[1].vel.vx = 0;
		cd[1].vel.vz = 0;
		cd[1].avel = 0;

		if (cp->controlType == 5) 
		{
			iVar2 = bcollided2d(cd, 1);
			uVar3 = (iVar2 != 0);
		}
		else 
		{
			strikeVel = bcollided2d(cd, 0);
			if (strikeVel == 0) 
			{
				uVar3 = 0;
			}
			else 
			{
				bFindCollisionTime(cd, &collisionResult);
				bFindCollisionPoint(cd, &collisionResult);

#if defined(COLLISION_DEBUG) && !defined(PSX)
				extern int gShowCollisionDebug;
				if(gShowCollisionDebug)
				{
					extern void Debug_AddLine(VECTOR& pointA, VECTOR& pointB, CVECTOR& color);
					extern void Debug_AddLineOfs(VECTOR& pointA, VECTOR& pointB, VECTOR& ofs, CVECTOR& color);
					

					CVECTOR bbcv = { 0, 0, 250 };
					CVECTOR rrcv = { 250, 0, 0 };
					CVECTOR yycv = { 250, 250, 0 };

					// show collision point and normal
					{

						VECTOR pb = collisionResult.hit;
						pb.vy += 16;

						// display collision point
						Debug_AddLine(collisionResult.hit, pb, rrcv);

						VECTOR nb = collisionResult.hit;
						nb.vx += collisionResult.surfNormal.vx / 16;
						nb.vy += collisionResult.surfNormal.vy / 16;
						nb.vz += collisionResult.surfNormal.vz / 16;

						// show collision normal
						Debug_AddLine(collisionResult.hit, nb, bbcv);
					}

					// show both box axes
					{
						VECTOR _zero = { 0 };
						VECTOR b1p = *(VECTOR*)cp->hd.where.t;
						VECTOR b2p = building->pos;
						b2p.vy = b1p.vy;

						// show position to position
						//Debug_AddLine(b1p1, b2p1, yycv);

						VECTOR b1ax[2] = { {0} , {0} };
						b1ax[0].vx = (cd[0].axis[0].vx * cd[0].length[0]) / 4096;
						b1ax[0].vz = (cd[0].axis[0].vz * cd[0].length[0]) / 4096;
						b1ax[1].vx = (cd[0].axis[1].vx * cd[0].length[1]) / 4096;
						b1ax[1].vz = (cd[0].axis[1].vz * cd[0].length[1]) / 4096;

						// show axis of body 1
						Debug_AddLineOfs(_zero, b1ax[0], b1p, rrcv);
						Debug_AddLineOfs(_zero, b1ax[1], b1p, yycv);
						
						// display 2D box 1
						{
							int h = b1ax[0].vy;
							VECTOR box_points[4] = {
								{b1ax[0].vx - b1ax[1].vx, h, b1ax[0].vz - b1ax[1].vz, 0},	// front left
								{b1ax[0].vx + b1ax[1].vx, h, b1ax[0].vz + b1ax[1].vz, 0},	// front right

								{-b1ax[0].vx + b1ax[1].vx, h, -b1ax[0].vz + b1ax[1].vz, 0},	// back right
								{-b1ax[0].vx - b1ax[1].vx, h, -b1ax[0].vz - b1ax[1].vz, 0}	// back left
							};

							Debug_AddLineOfs(box_points[0], box_points[1], b1p, bbcv);
							Debug_AddLineOfs(box_points[1], box_points[2], b1p, bbcv);
							Debug_AddLineOfs(box_points[2], box_points[3], b1p, bbcv);
							Debug_AddLineOfs(box_points[3], box_points[0], b1p, bbcv);
						}

						VECTOR b2ax[2] = { {0} , {0} };
						b2ax[0].vx += (cd[1].axis[0].vx * cd[1].length[0]) / 4096;
						b2ax[0].vz += (cd[1].axis[0].vz * cd[1].length[0]) / 4096;
						b2ax[1].vx += (cd[1].axis[1].vx * cd[1].length[1]) / 4096;
						b2ax[1].vz += (cd[1].axis[1].vz * cd[1].length[1]) / 4096;

						// show axis of body 2
						Debug_AddLineOfs(_zero, b2ax[0], b2p, rrcv);
						Debug_AddLineOfs(_zero, b2ax[1], b2p, yycv);

						// display 2D box 2
						{
							int h = b2ax[0].vy;
							VECTOR box_points[4] = {
								{b2ax[0].vx - b2ax[1].vx, h, b2ax[0].vz - b2ax[1].vz, 0},	// front left
								{b2ax[0].vx + b2ax[1].vx, h, b2ax[0].vz + b2ax[1].vz, 0},	// front right

								{-b2ax[0].vx + b2ax[1].vx, h, -b2ax[0].vz + b2ax[1].vz, 0},	// back right
								{-b2ax[0].vx - b2ax[1].vx, h, -b2ax[0].vz - b2ax[1].vz, 0}	// back left
							};

							Debug_AddLineOfs(box_points[0], box_points[1], b2p, yycv);
							Debug_AddLineOfs(box_points[1], box_points[2], b2p, yycv);
							Debug_AddLineOfs(box_points[2], box_points[3], b2p, yycv);
							Debug_AddLineOfs(box_points[3], box_points[0], b2p, yycv);
						}
					}
				}
#endif
				collisionResult.surfNormal.vx = -collisionResult.surfNormal.vx;
				collisionResult.surfNormal.vy = 0;
				collisionResult.surfNormal.vz = -collisionResult.surfNormal.vz;

				collisionResult.hit.vy = cp->hd.where.t[1] + 41;

				cp->hd.where.t[0] += (collisionResult.penetration * collisionResult.surfNormal.vx) / 4096;
				cp->hd.where.t[2] += (collisionResult.penetration * collisionResult.surfNormal.vz) / 4096;

				iVar13 = cp->st.n.angularVelocity[0];
				iVar18 = cp->st.n.angularVelocity[1];
				iVar10 = cp->st.n.angularVelocity[2];

				iVar17 = collisionResult.hit.vx - cp->hd.where.t[0];
				iVar16 = collisionResult.hit.vy - cp->hd.where.t[1];
				iVar9 = collisionResult.hit.vz - cp->hd.where.t[2];
				
				strikeVel = ((iVar18 * iVar9 - iVar10 * iVar16) / 4096) + cp->st.n.linearVelocity[0];
				iVar10 = ((iVar10 * iVar17 - iVar13 * iVar9) / 4096) + cp->st.n.linearVelocity[1];
				iVar13 = ((iVar13 * iVar16 - iVar18 * iVar17) / 4096) + cp->st.n.linearVelocity[2];

				lVar5 = collisionResult.surfNormal.vx;
				lVar6 = collisionResult.surfNormal.vy;
				lVar7 = collisionResult.surfNormal.vz;

				iVar10 = (strikeVel >> 8) * (lVar5 >> 4) + (iVar10 >> 8) * (lVar6 >> 4) + (iVar13 >> 8) * (lVar7 >> 4);
				strikeVel = -iVar10;

				if (iVar10 < 0) 
				{
					if (cp->controlType == 1) 
					{
						if (strikeVel < 0x20) 
							scale = ((iVar10 << 0x17) >> 0x10);
						else 
							scale = 0x1000;

						if ((pMVar20->flags2 & 0x800) == 0) 
							NoteFelony(&felonyData, 6, scale);
						else
							NoteFelony(&felonyData, 7, scale);
					}

					collisionResult.hit.vy = -collisionResult.hit.vy;

					velocity.vx = cp->st.n.linearVelocity[0] / 4096;
					velocity.vy = -17;
					velocity.vz = cp->st.n.linearVelocity[2] / 4096;

					if ((pMVar20->flags2 & 0x800) != 0)
					{
						damage_object(cop, &velocity);

						if ((pMVar20->shape_flags & 8) == 0)
						{
							pSVar15 = smashable;
							strikeVel = pSVar15->modelIdx;
							pSVar19 = NULL;

							if (pSVar15->name != NULL)
							{
								while ((pSVar19 = pSVar15, modelpointers[strikeVel] != pMVar20 && (pSVar19 = NULL, pSVar15[1].name != NULL)))
								{
									strikeVel = pSVar15[1].modelIdx;
									pSVar15 = pSVar15 + 1;
								}
							}

							if (pSVar19 == NULL)
								pSVar19 = smashable;

							uVar3 = velocity.vx ^ velocity.vz;
							uVar11 = collisionResult.hit.vx ^ collisionResult.hit.vz;
							strikeVel = GetFreeChannel();

							if ((1 < NumPlayers) && (NoPlayerControl == 0))
								SetPlayerOwnsChannel(strikeVel, iVar2);

							Start3DSoundVolPitch(strikeVel, 1, pSVar19->sound, 
								collisionResult.hit.vx, -collisionResult.hit.vy, collisionResult.hit.vz, 
								pSVar19->volume, pSVar19->pitch + ((uVar3 * uVar11 & 0x3ff) - 0x200));
						}

						cp->hd.where.t[0] = lVar4;
						cp->hd.where.t[2] = lVar8;

						collisionResult.hit.vy += 30;

						Setup_Sparks(&collisionResult.hit, &velocity, 10, 0);
						Setup_Debris(&collisionResult.hit, &velocity, 5, 0);
						Setup_Debris(&collisionResult.hit, &velocity, 5, iVar14 << 0x10);

						if (cp->controlType == 1)
							SetPadVibration((int)cp->ai.padid, 3);

						return 0;
					}



					if ((0x3600 < strikeVel) && (32000 < cp->hd.wheel_speed + 16000U))
					{
						if ((pMVar20->flags2 & 0x2000) == 0) 
						{
							if (gNight != 0 && (modelpointers[gLastModelCollisionCheck]->flags2 & 0x1000) != 0)
							{
								iVar2 = damage_lamp(cop);
								if (iVar2 != 0)
								{
									memset(&lamp_velocity, 0, sizeof(lamp_velocity));

									collisionResult.hit.vy = -730;
									Setup_Sparks(&collisionResult.hit, &lamp_velocity, 0x14, 0);
									collisionResult.hit.vy = 730;
								}
							}

							velocity.vy -= 20;
							collisionResult.hit.vy += 30;

							Setup_Sparks(&collisionResult.hit, &velocity, 4, 0);

							collisionResult.hit.vy -= 30;
							velocity.vy += 20;
						}
						else 
						{
							uVar3 = rand();
							LeafPosition.vx = collisionResult.hit.vx;
							LeafPosition.vy = -((uVar3 & 0xfe) + 600) - collisionResult.hit.vy;
							LeafPosition.vz = collisionResult.hit.vz;

							AddLeaf(&LeafPosition, 3, 1);
						}

						if ((0x1b000 < strikeVel) && (Setup_Debris(&collisionResult.hit, &velocity, 6, iVar14 << 0x10), cp->controlType == 1)) 
						{
							SetPadVibration((int)cp->ai.padid, 1);
						}
					}

					DamageCar(cp, cd, &collisionResult, strikeVel);

					iVar2 = (iVar17 * collisionResult.surfNormal.vx + iVar16 * collisionResult.surfNormal.vy + iVar9 * collisionResult.surfNormal.vz) / 4096;
					iVar2 = (((iVar17 * iVar17 + iVar9 * iVar9) - iVar2 * iVar2) * car_cosmetics[cp->ap.model].twistRateY) / 4096 + 0x1000;

					if (strikeVel < 0x7f001) 
					{
						iVar14 = (iVar10 * -0x1000) / iVar2;
						if (iVar2 == 0)
							trap(7);
					}
					else
					{
						if (iVar2 == 0) 
							trap(7);

						iVar14 = (strikeVel / iVar2) * 4096;
					}

					// [A] temporary hack
					cp->st.n.fposition[0] += (collisionResult.penetration * collisionResult.surfNormal.vx) / 512;
					cp->st.n.fposition[2] += (collisionResult.penetration * collisionResult.surfNormal.vz) / 512;

					iVar14 = iVar14 / 64;
					lVar4 = collisionResult.surfNormal.vx;

					iVar2 = iVar14 * (lVar4 / 64);
					lVar4 = collisionResult.surfNormal.vy;

					strikeVel = iVar14 * (lVar4 / 64);
					lVar4 = collisionResult.surfNormal.vz;

					iVar14 = iVar14 * (lVar4 / 64);

					if (cp->controlType != 4)
					{
						iVar13 = iVar16 * iVar14;
						iVar10 = iVar13 / 4096;
						if (cp->controlType == 3)
							iVar10 = iVar13 / 8192;
						
						iVar10 = cp->hd.aacc[0] + iVar10;
						cp->hd.aacc[0] = iVar10;
						iVar18 = iVar9 * strikeVel;
						iVar13 = iVar18 / 4096;

						if (cp->controlType == 3) 
							iVar13 = iVar18 / 8192;
						
						cp->hd.aacc[0] = iVar10 - iVar13;
					}

					cp->hd.aacc[1] += (iVar9 * iVar2) / 4096 - (iVar17 * iVar14) / 4096;

					if (cp->controlType != 4)
					{
						iVar10 = iVar17 * strikeVel;
						iVar9 = iVar10 / 4096;

						if (cp->controlType == 3)
							iVar9 = iVar10 / 8192;

						iVar9 = cp->hd.aacc[2] + iVar9;
						cp->hd.aacc[2] = iVar9;
						iVar13 = iVar16 * iVar2;
						iVar10 = iVar13 / 4096;

						if (cp->controlType == 3) 
							iVar10 = iVar13 / 8192;
						
						cp->hd.aacc[2] = iVar9 - iVar10;
					}

					cp->st.n.linearVelocity[0] += iVar2;

					if (cp->controlType != 4)
						cp->st.n.linearVelocity[1] += strikeVel;

					cp->st.n.linearVelocity[2] += iVar14;
				}
				uVar3 = 1;
			}

			cp->hd.where.t[0] -= cp->st.n.linearVelocity[0] / 4096;
			cp->hd.where.t[2] -= cp->st.n.linearVelocity[2] / 4096;
		}
	}

	return uVar3;
}





