#include "DRIVER2.H"
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
#include "INLINE_C.H"
#include <stdlib.h>

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

// Checks of two bodies collides (basic check) with Separating Axis Theorem
// also initializes axes
// [D] [T]
int bcollided2d(CDATA2D *body, int needOverlap)
{
	int dtheta;
	short ac;
	short as;
	int i; // $t7
	int j; // $a2
	int k; // $t5
	VECTOR delta;
 	int xover; // $t0
 	int zover; // $a0
 	int tmp2; // $a2
 	int FE; // $a3

	dtheta = body[1].theta - body[0].theta;

	// calc axes of each box
	i = 1;
	do {
		as = rcossin_tbl[(body[i].theta & 0xfff) * 2];
		ac = rcossin_tbl[(body[i].theta & 0xfff) * 2 + 1];

		body[i].axis[0].vx = as;
		body[i].axis[0].vz = ac;

		body[i].axis[1].vz = -as;
		body[i].axis[1].vx = ac;

		i--;
	} while (i != -1);

	ac = rcossin_tbl[(dtheta + 0x400 & 0x7ff) * 2];
	as = rcossin_tbl[(dtheta & 0x7ff) * 2];

	delta.vx = body[0].x.vx - body[1].x.vx;
	delta.vz = body[0].x.vz - body[1].x.vz;

	k = 0;
	i = 1;

	// do SAT tests for each axis
	do {
		j = 1;
		do {
			body[i].dist[j] = FIXEDH(body[i].axis[j].vx * delta.vx + body[i].axis[j].vz * delta.vz);
			body[i].limit[j] = body[i].length[j] + FIXEDH(body[k].length[j] * ac + body[k].length[1-j] * as);

			if (body[i].limit[j] < body[i].dist[j])
				return 0;

			if (body[i].dist[j] < -body[i].limit[j])
				return 0;

			j--;
		} while (j != -1);

		k++;
		i--;
	} while (i >= 0);

	// calc overlap if needed
	if (needOverlap)
	{
		FE = ABS(body[1].dist[0]) - ABS(body[1].limit[0]);
		FE = ABS(FE);

		tmp2 = FIXEDH(body->axis[0].vx * body[1].axis[0].vx + body->axis[0].vz * body[1].axis[0].vz);
		tmp2 = ABS(tmp2);

		if (tmp2 < 11)
			xover = -1;
		else
			xover = (FE * ONE) / tmp2;

		FE = ABS(body[1].dist[1]) - ABS(body[1].limit[1]);
		FE = ABS(FE);

		tmp2 = FIXEDH(body->axis[0].vx * body[1].axis[1].vx + body->axis[0].vz * body[1].axis[1].vz);
		tmp2 = ABS(tmp2);

		zover = xover;
		if (tmp2 > 10)
			zover = (FE * ONE) / tmp2;

		if (xover > -1)
		{
			if (zover < xover)
				boxOverlap = zover;
			else
				boxOverlap = xover;
		}
		else
			boxOverlap = zover;
	}

	return 1;
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

// [D] [T]
void bFindCollisionPoint(CDATA2D *body, CRET2D *collisionResult)
{
	bool carBarrierCollision;
	int lower;
	int upper;
	int k;
	int sign;
	int sign0;
	int sign1;
	int smallest;
	int besti;
	int bestk;
	CDATA2D* cd;
	int i;

	besti = 0;
	bestk = 0;
	sign = 0;
	carBarrierCollision = false;

	smallest = body->limit[0] + 1;

	if ((body[0].isCameraOrTanner == 0) && (body[1].isCameraOrTanner == 0) && 
		(body[1].length[0] << 3 <= body[1].length[1]) || (body[1].length[1] << 3 <= body[1].length[0]))
	{
		carBarrierCollision = true;
	}

	i = 1;
	do {
		k = 1;
		do {
			upper = body[i].limit[k] - body[i].dist[k];
			lower = body[i].dist[k] + body[i].limit[k];

			if (smallest > upper)
			{
				sign = (i == 1) ? 1 : -1;

				smallest = upper;
				besti = i;
				bestk = k;
			}

			if (smallest > lower)
			{
				sign = (i == 1) ? -1 : 1;

				smallest = lower;
				besti = i;
				bestk = k;
			}

			k--;
		} while (k >= 0);
		
		i--;
	} while (i >= 0);

	// calc push
	if (carBarrierCollision)
	{
		k = 1;
		do {
			upper = body[1].limit[k] - body[1].dist[k];
			lower = body[1].dist[k] + body[1].limit[k];

			if (upper < lower && (body[1].length[k] < body[1].length[1-k] << 2))
			{
				besti = 1;
				sign = 1;
				bestk = k;
			}

			if (lower < upper && (body[1].length[k] < body[1].length[1 - k] << 2))
			{
				besti = 1;
				sign = -1;
				bestk = k;
			}

			k--;
		} while (k >= 0);
	}

	cd = &body[(besti ^ 1)];

	sign0 = sign;

	if (cd->axis[0].vx * body[besti].axis[bestk].vx + cd->axis[0].vz * body[besti].axis[bestk].vz + 0x800 > -1)
		sign0 = -sign;

	sign1 = sign;

	if (cd->axis[1].vx * body[besti].axis[bestk].vx + cd->axis[1].vz * body[besti].axis[bestk].vz + 0x800 > -1)
		sign1 = -sign;

	collisionResult->penetration = smallest;

	collisionResult->hit.vx = cd->x.vx + FIXEDH(cd->axis[0].vx * cd->length[0] * sign0 + cd->axis[1].vx * cd->length[1] * sign1);
	collisionResult->hit.vz = cd->x.vz + FIXEDH(cd->axis[0].vz * cd->length[0] * sign0 + cd->axis[1].vz * cd->length[1] * sign1);

	if (besti != 0)
		sign = -sign;

	collisionResult->surfNormal.vy = 0;
	collisionResult->surfNormal.vx = body[besti].axis[bestk].vx * sign;
	collisionResult->surfNormal.vz = body[besti].axis[bestk].vz * sign;
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

// [D] [T]
int bFindCollisionTime(CDATA2D *cd, CRET2D *collisionResult)
{
	int hit;
	int q;
	int time;
	int step;
	int i;
	int neverfree;
	CDATA2D original[2];

	hit = 1;
	neverfree = 1;
	time = 0x1000;
	step = 0x800;
	
	i = 1;
	do {
		original[i] = cd[i];
		i--;
	} while (i >= 0);

	i = 7;
	do {
		
		q = 1;
		do {
			cd[q].vel.vx >>= 1;
			cd[q].vel.vz >>= 1;
			cd[q].avel >>= 1;

			if (hit == 0)
			{
				cd[q].x.vx += cd[q].vel.vx;
				cd[q].x.vz += cd[q].vel.vz;
				cd[q].theta += cd[q].avel;
			}
			else
			{
				cd[q].x.vx -= cd[q].vel.vx;
				cd[q].x.vz -= cd[q].vel.vz;
				cd[q].theta -= cd[q].avel;
			}

			q--;
		} while (q >= 0);

		if (hit == 0) 
		{
			neverfree = 0;
			time += step;
		}
		else
		{
			time -= step;
		}

		hit = bcollided2d(cd, 0);

		if (i != 0)
			step >>= 1;

		i--;
	} while (i >= 0);

	if (hit == 0) 
	{
		i = 1;
		do {
			cd[i].x.vx += cd[i].vel.vx;
			cd[i].x.vz += cd[i].vel.vz;
			cd[i].theta += cd[i].avel;

			i--;
		} while (i >= 0);

		bcollided2d(cd, 0);

		time += step;
	}
	else if (neverfree != 0)
	{
		i = 1;
		do {
			cd[i] = original[i];

			bcollided2d(cd, 0);
			i--;
		} while (i >= 0);

		time = 0x1000;
	}

	collisionResult->neverfree = neverfree;

	return time;
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

// [D] [T]
void ApplyDamage(_CAR_DATA *cp, char region, int value, char fakeDamage)
{
	short *pRegion;

	pRegion = (cp->ap.damage + region);

	if (cp->controlType == CONTROL_TYPE_PLAYER || cp->controlType == CONTROL_TYPE_LEAD_AI)
		value = value * FIXEDH(gPlayerDamageFactor);
	else 
		value = value << 1;

	if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
	{
		if (gCopDifficultyLevel == 1) 
		{
			value = value * 12 >> 4;
		}
		else if (gCopDifficultyLevel == 2)
		{
			value = value * 7 >> 4;
		}
	}

	if (fakeDamage == 0) 
	{
		if (cp->totalDamage < 0xffff - value)
			cp->totalDamage += value;
		else
			cp->totalDamage = 0xffff;
	}

	*pRegion += value;

	if (*pRegion > 4095)
		*pRegion = 4095;

	// adjust symmetric regions
	if (region == 1)
		region = 0;
	else if (region == 0)
		region = 1;
	else if (region == 3)
		region = 4;
	else if (region == 4)
		region = 3;
	else
		region = -1;

	if (region != -1)
	{
		pRegion = cp->ap.damage + region;
		value >>= 1;

		if (*pRegion < value)
		{
			if (fakeDamage == 0) 
			{
				if (cp->totalDamage < 0xffff - (value - *pRegion))
					cp->totalDamage += (value - *pRegion);
				else 
					cp->totalDamage = 0xffff;
			}

			*pRegion = value;
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

// [D] [T]
int DamageCar3D(_CAR_DATA *cp, long(*delta)[4], int strikeVel, _CAR_DATA *pOtherCar)
{
	char region;
	int value;
	bool fakeDamage;
	int lbody;

	int player_id;
	int kludge;
	int door, nose;

	strikeVel *= 375;

	lbody = cp->ap.carCos->colBox.vz / 2;

	strikeVel >>= 8;

	if (strikeVel < 0xa000) 
	{
		if (cp->totalDamage == 0)
			cp->totalDamage = 1;

		return 0;
	}

	nose = FIXEDH(cp->hd.where.m[0][2] * (*delta)[0] + cp->hd.where.m[1][2] * (*delta)[1] + cp->hd.where.m[2][2] * (*delta)[2]);
	door = FIXEDH(cp->hd.where.m[0][0] * (*delta)[0] + cp->hd.where.m[1][0] * (*delta)[1] + cp->hd.where.m[2][0] * (*delta)[2]);

	if (door < 1)
	{
		if(nose > lbody)
			region = 0;
		else if (-lbody < nose)
			region = 5;
		else
			region = 4;
	}
	else 
	{
		if(nose > lbody)
			region = 1;
		else if (-lbody < nose)
			region = 2;
		else
			region = 3;
	}

	if (cp->controlType == CONTROL_TYPE_PLAYER) 
	{
		value = (strikeVel / 350 + 0x200) * 3;

		value >>= 3;
		if (value > 0x477)
			value = 0x477;
		
	}
	else if (cp->controlType == CONTROL_TYPE_LEAD_AI)
	{
		if (pOtherCar->controlType == CONTROL_TYPE_PLAYER)
		{
			value = (strikeVel / 350 + 0x200) * 3;

			value >>= 3;

			if (value > 0x477)
				value = 0x477;

			cp->ai.l.takeDamage = 0x32;
		}
		else
		{
			value = strikeVel / 350 + 0x200;

			value >>= 3;
			if (value > 0x2fa)
				value = 0x2fa;

			if (cp->ai.l.takeDamage == 0)
				value = 0;
		}
	}
	else 
	{
		value = ((strikeVel / 400 + 0x400) * 7) >> 3;
	}

	fakeDamage = (cp->controlType == CONTROL_TYPE_PURSUER_AI && pOtherCar->controlType == CONTROL_TYPE_PURSUER_AI);

	ApplyDamage(cp, region, value, fakeDamage);

	player_id = GetPlayerId(cp);

	if (player_id < 0)
		player_id = GetPlayerId(pOtherCar);

	kludge = GetPlayerId(cp);

	if (kludge != 0 || (kludge = 2, pOtherCar->controlType != CONTROL_TYPE_CIV_AI))
	{
		kludge = 1;

		if (GetPlayerId(pOtherCar) == 0 && cp->controlType == CONTROL_TYPE_CIV_AI)
			kludge = 2;
	}

	CollisionSound(player_id, cp, strikeVel / 128, kludge);

	return 1;
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

// [D] [T]
void DamageCar(_CAR_DATA *cp, CDATA2D *cd, CRET2D *collisionResult, int strikeVel)
{
	int impact;
	int player_id;
	int value;
	int nose;
	int door;
	int region;
	int dz;
	int dx;
	int lbody;

	player_id = GetPlayerId(cp);

	lbody = cp->ap.carCos->colBox.vz / 2;
	impact = strikeVel / 600;

	if (strikeVel > 0x4fff && cp->hd.speed > 9) 
	{
		dx = collisionResult->hit.vx - cd->x.vx;
		dz = collisionResult->hit.vz - cd->x.vz;

		nose = FIXEDH(cd->axis[0].vx * dx + cd->axis[0].vz * dz);
		door = FIXEDH(cd->axis[1].vx * dx + cd->axis[1].vz * dz);

		if (door < 1)
		{
			if (nose > lbody)
				region = 0;
			else if (-lbody < nose)
				region = 5;
			else
				region = 4;
		}
		else
		{
			if (nose > lbody)
				region = 1;
			else if (-lbody < nose)
				region = 2;
			else
				region = 3;
		}
		
		if (0x1f4000 < strikeVel) 
			strikeVel = 0x1f4000;

		value = ((strikeVel / 300) * 1024) / 1500;
		if (0x800 < value)
			value = 0x800;
	
		value -= (value * cp->ap.damage[region] >> 0xd);

		if (cp->controlType == CONTROL_TYPE_LEAD_AI)
		{
			if (cp->ai.l.takeDamage == 0)
				value = 0;
			else 
				value = value / 2;
		}

		ApplyDamage(cp, region, value, 0);
		CollisionSound(player_id, cp, impact, 0);
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

// [D] [T]
int CarBuildingCollision(_CAR_DATA *cp, BUILDING_BOX *building, CELL_OBJECT *cop, int flags)
{
	static CDATA2D cd[2] = {0}; // offset 0x0
	static CRET2D collisionResult = { 0 }; // offset 0xd0

	int temp;
	int strikeVel;
	int boxDiffY;
	int collided;
	short scale;
	int chan;
	int player_id;
	SMASHABLE_OBJECT *match;
	SMASHABLE_OBJECT* sip;
	CAR_COSMETICS* car_cos;
	MODEL *model;
	VECTOR tempwhere;
	SVECTOR boxDisp;
	VECTOR velocity;
	long pointVel[4];
	long reaction[4];
	long lever[4];
	VECTOR LeafPosition;
	VECTOR lamp_velocity;
	int debris_colour;
	int displacement;
	int denom;

	model = modelpointers[cop->type];
	player_id = GetPlayerId(cp);

	cd[0].isCameraOrTanner = (cp->controlType == CONTROL_TYPE_CAMERACOLLIDER);

	if (cp->controlType == 6)
		cd[0].isCameraOrTanner += 2;

	cd[1].isCameraOrTanner = (flags & 0x1) == 0;

	boxDiffY = cp->hd.oBox.location.vy + building->pos.vy;
	boxDiffY = ABS(boxDiffY);

	collided = 0;

	car_cos = cp->ap.carCos;

	if (boxDiffY <= (building->height >> 1) + (cp->hd.oBox.length[1] >> 1) && (cop->pos.vx != 0xFD46FEC0) && (model->shape_flags & 0x10) == 0)
	{
		tempwhere.vx = cp->hd.where.t[0];
		tempwhere.vz = cp->hd.where.t[2];

		debris_colour = GetDebrisColour(cp);
		gte_SetRotMatrix(&cp->hd.where);
		gte_SetTransMatrix(&cp->hd.where);

		boxDisp.vx = -car_cos->cog.vx;
		boxDisp.vy = -car_cos->cog.vy;
		boxDisp.vz = -car_cos->cog.vz;

		gte_ldv0(&boxDisp);

		gte_rtv0tr();

		gte_stlvnl(&cd[0].x);

		cd[0].theta = cp->hd.direction;

		if (cp->controlType == 6)
		{
			cd[0].vel.vx = FIXEDH(cp->st.n.linearVelocity[0]);
			cd[0].vel.vz = FIXEDH(cp->st.n.linearVelocity[2]);

			cp->hd.where.t[0] += cd[0].vel.vx;
			cp->hd.where.t[2] += cd[0].vel.vz;

			cd[0].length[0] = 80;
			cd[0].length[1] = 80;
		}
		else if (cp->controlType == CONTROL_TYPE_CAMERACOLLIDER)
		{
			cd[0].vel.vx = 0;
			cd[0].vel.vz = 0;
			cd[0].length[1] = 5;
			cd[0].length[0] = gCameraDistance / 2;
		}
		else
		{
			cd[0].vel.vx = FIXEDH(cp->st.n.linearVelocity[0]);
			cd[0].vel.vz = FIXEDH(cp->st.n.linearVelocity[2]);

			cp->hd.where.t[0] += cd[0].vel.vx;
			cp->hd.where.t[2] += cd[0].vel.vz;

			cd[0].length[0] = car_cos->colBox.vz + 15;
			cd[0].length[1] = car_cos->colBox.vx + 15;

			if (handlingType[cp->hndType].fourWheelDrive == 1 || cp->hndType == 5)
				cd[0].length[1] = FixFloorSigned(cd[0].length[1] * 13, 4);
		}

		cd[0].avel = FIXEDH(cp->st.n.angularVelocity[1]) * 5 >> 5;

		cd[1].x.vx = cp->hd.where.t[0] + (((building->pos.vx - cp->hd.where.t[0]) << 0x10) >> 0x10);
		cd[1].x.vz = cp->hd.where.t[2] + (((building->pos.vz - cp->hd.where.t[2]) << 0x10) >> 0x10);

		cd[1].theta = building->theta;
		cd[1].length[0] = building->xsize;
		cd[1].length[1] = building->zsize;
		cd[1].vel.vx = 0;
		cd[1].vel.vz = 0;
		cd[1].avel = 0;

		if (cp->controlType == CONTROL_TYPE_CAMERACOLLIDER) 
		{
			collided = (bcollided2d(cd, 1) != 0);
		}
		else 
		{
			collided = (bcollided2d(cd, 0) != 0);


#if defined(COLLISION_DEBUG) && !defined(PSX)
			extern int gShowCollisionDebug;
			if (gShowCollisionDebug == 1)
			{
				extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
				extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

				CVECTOR bbcv = { 0, 0, 250 };
				CVECTOR rrcv = { 250, 0, 0 };
				CVECTOR yycv = { 250, 250, 0 };

				// show both box axes
				{
					VECTOR _zero = { 0 };
					VECTOR b1p = cd[0].x;
					VECTOR b2p = cd[1].x;
					b2p.vy = b1p.vy;

					// show position to position
					//Debug_AddLine(b1p1, b2p1, yycv);

					VECTOR b1ax[2] = { {0} , {0} };
					b1ax[0].vx = FIXEDH(cd[0].axis[0].vx * cd[0].length[0]);
					b1ax[0].vz = FIXEDH(cd[0].axis[0].vz * cd[0].length[0]);
					b1ax[1].vx = FIXEDH(cd[0].axis[1].vx * cd[0].length[1]);
					b1ax[1].vz = FIXEDH(cd[0].axis[1].vz * cd[0].length[1]);

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
					b2ax[0].vx += FIXEDH(cd[1].axis[0].vx * cd[1].length[0]);
					b2ax[0].vz += FIXEDH(cd[1].axis[0].vz * cd[1].length[0]);
					b2ax[1].vx += FIXEDH(cd[1].axis[1].vx * cd[1].length[1]);
					b2ax[1].vz += FIXEDH(cd[1].axis[1].vz * cd[1].length[1]);

					// show axis of body 2
					Debug_AddLineOfs(_zero, b2ax[0], b2p, rrcv);
					Debug_AddLineOfs(_zero, b2ax[1], b2p, yycv);

					CVECTOR& collColor = collided ? rrcv : yycv;

					// display 2D box 2
					{
						int h = b2ax[0].vy;
						VECTOR box_points[4] = {
							{b2ax[0].vx - b2ax[1].vx, h, b2ax[0].vz - b2ax[1].vz, 0},	// front left
							{b2ax[0].vx + b2ax[1].vx, h, b2ax[0].vz + b2ax[1].vz, 0},	// front right

							{-b2ax[0].vx + b2ax[1].vx, h, -b2ax[0].vz + b2ax[1].vz, 0},	// back right
							{-b2ax[0].vx - b2ax[1].vx, h, -b2ax[0].vz - b2ax[1].vz, 0}	// back left
						};

						Debug_AddLineOfs(box_points[0], box_points[1], b2p, collColor);
						Debug_AddLineOfs(box_points[1], box_points[2], b2p, collColor);
						Debug_AddLineOfs(box_points[2], box_points[3], b2p, collColor);
						Debug_AddLineOfs(box_points[3], box_points[0], b2p, collColor);
					}
				}
			}
#endif

			if (collided)
			{
				bFindCollisionTime(cd, &collisionResult);
				bFindCollisionPoint(cd, &collisionResult);

#if defined(COLLISION_DEBUG) && !defined(PSX)
				extern int gShowCollisionDebug;
				if(gShowCollisionDebug == 1)
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
				}
#endif
				collisionResult.surfNormal.vx = -collisionResult.surfNormal.vx;
				collisionResult.surfNormal.vy = 0;
				collisionResult.surfNormal.vz = -collisionResult.surfNormal.vz;

				collisionResult.hit.vy = cp->hd.where.t[1] + 41;

				// perform error correction
				cp->hd.where.t[0] += FIXEDH(collisionResult.penetration * collisionResult.surfNormal.vx);
				cp->hd.where.t[2] += FIXEDH(collisionResult.penetration * collisionResult.surfNormal.vz);

				lever[0] = collisionResult.hit.vx - cp->hd.where.t[0];
				lever[1] = collisionResult.hit.vy - cp->hd.where.t[1];
				lever[2] = collisionResult.hit.vz - cp->hd.where.t[2];
				
				pointVel[0] = FIXEDH(cp->st.n.angularVelocity[1] * lever[2] - cp->st.n.angularVelocity[2] * lever[1]) + cp->st.n.linearVelocity[0];
				pointVel[1] = FIXEDH(cp->st.n.angularVelocity[2] * lever[0] - cp->st.n.angularVelocity[0] * lever[2]) + cp->st.n.linearVelocity[1];
				pointVel[2] = FIXEDH(cp->st.n.angularVelocity[0] * lever[1] - cp->st.n.angularVelocity[1] * lever[0]) + cp->st.n.linearVelocity[2];

				if (flags & 0x2) // [A] Vegas train velocity - added here
				{
					pointVel[2] += 700000;
				}

				strikeVel = -(FixFloorSigned(pointVel[0], 8) * FixFloorSigned(collisionResult.surfNormal.vx, 4) +
								FixFloorSigned(pointVel[1], 8) * FixFloorSigned(collisionResult.surfNormal.vy, 4) +
								FixFloorSigned(pointVel[2], 8) * FixFloorSigned(collisionResult.surfNormal.vz, 4));

				if (strikeVel > 0)
				{
					if (cp->controlType == CONTROL_TYPE_PLAYER) 
					{
						if (strikeVel < 32) 
							scale = ((strikeVel << 0x17) >> 0x10);
						else 
							scale = 0x1000;

						if ((model->flags2 & 0x800) == 0) 
							NoteFelony(&felonyData, 6, scale);
						else
							NoteFelony(&felonyData, 7, scale);
					}

					collisionResult.hit.vy = -collisionResult.hit.vy;

					velocity.vx = FixFloorSigned(cp->st.n.linearVelocity[0], ONE_BITS);
					velocity.vy = -17;
					velocity.vz = FixFloorSigned(cp->st.n.linearVelocity[2], ONE_BITS);

					if ((model->flags2 & 0x800) != 0)
					{
						// that's for lamps
						damage_object(cop, &velocity);

						// smash object
						if ((model->shape_flags & 8) == 0)
						{
							sip = smashable;
							match = sip;

							while (sip->name != NULL)
							{
								if (modelpointers[sip->modelIdx] == model)
								{
									match = sip;
									break;
								}
								sip++;
							}

							chan = GetFreeChannel();

							if (NumPlayers > 1 && NoPlayerControl == 0)
								SetPlayerOwnsChannel(chan, player_id);

							Start3DSoundVolPitch(chan, 1, match->sound,
								collisionResult.hit.vx, -collisionResult.hit.vy, collisionResult.hit.vz, 
								match->volume, match->pitch + (((velocity.vx ^ velocity.vz) * (collisionResult.hit.vx ^ collisionResult.hit.vz) & 0x3ff) - 0x200));
						}

						cp->hd.where.t[0] = tempwhere.vx;
						cp->hd.where.t[2] = tempwhere.vz;

						collisionResult.hit.vy += 30;

						Setup_Sparks(&collisionResult.hit, &velocity, 10, 0);
						Setup_Debris(&collisionResult.hit, &velocity, 5, 0);
						Setup_Debris(&collisionResult.hit, &velocity, 5, debris_colour << 0x10);

						if (cp->controlType == CONTROL_TYPE_PLAYER)
							SetPadVibration(*cp->ai.padid, 3);

						return 0;
					}

					// add leaves
					if (strikeVel > 0x3600 && cp->hd.wheel_speed + 16000U > 32000)
					{
						if ((model->flags2 & 0x2000) == 0) 
						{
							if (gNight != 0 && (modelpointers[gLastModelCollisionCheck]->flags2 & 0x1000) != 0)
							{
								if (damage_lamp(cop) != 0)
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
							LeafPosition.vx = collisionResult.hit.vx;
							LeafPosition.vy = -((rand() & 0xfe) + 600) - collisionResult.hit.vy;
							LeafPosition.vz = collisionResult.hit.vz;

							AddLeaf(&LeafPosition, 3, 1);
						}

						if (strikeVel > 0x1b000)
						{
							Setup_Debris(&collisionResult.hit, &velocity, 6, debris_colour << 0x10);

							if(cp->controlType == CONTROL_TYPE_PLAYER)
								SetPadVibration(*cp->ai.padid, 1);
						}
					}

					DamageCar(cp, cd, &collisionResult, strikeVel);

					displacement = FIXEDH(lever[0] * collisionResult.surfNormal.vx + lever[1] * collisionResult.surfNormal.vy + lever[2] * collisionResult.surfNormal.vz);
					displacement = FIXEDH(((lever[0] * lever[0] + lever[2] * lever[2]) - displacement * displacement) * car_cos->twistRateY) + 4096;

					if (strikeVel < 0x7f001) 
						denom = (strikeVel * 4096) / displacement;
					else
						denom = (strikeVel / displacement) * 4096;

					denom = FixFloorSigned(denom, 6);

					reaction[0] = denom * FixFloorSigned(collisionResult.surfNormal.vx, 6);
					reaction[1] = denom * FixFloorSigned(collisionResult.surfNormal.vy, 6);
					reaction[2] = denom * FixFloorSigned(collisionResult.surfNormal.vz, 6);

					cp->hd.aacc[1] += FIXEDH(lever[2] * reaction[0]) - FIXEDH(lever[0] * reaction[2]);

					if (cp->controlType != CONTROL_TYPE_LEAD_AI)
					{
						temp = FIXEDH(lever[1] * reaction[2]);

						if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
							temp >>= 1;

						cp->hd.aacc[0] += temp;

						temp = FIXEDH(lever[2] * reaction[1]);

						if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
							temp >>= 1;
						
						cp->hd.aacc[0] -= temp;

						temp = FIXEDH(lever[0] * reaction[1]);

						if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
							temp >>= 1;

						cp->hd.aacc[2] += temp;

						temp = FIXEDH(lever[1] * reaction[0]);

						if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
							temp >>= 1;
						
						cp->hd.aacc[2] -= temp;

						cp->st.n.linearVelocity[1] += reaction[1];
					}

					cp->st.n.linearVelocity[0] += reaction[0];
					cp->st.n.linearVelocity[2] += reaction[2];
				}
			}

			cp->hd.where.t[0] -= FIXEDH(cp->st.n.linearVelocity[0]);
			cp->hd.where.t[2] -= FIXEDH(cp->st.n.linearVelocity[2]);
		}
	}

	return collided;
}





