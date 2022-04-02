#include "driver2.h"
#include "bcollide.h"
#include "pad.h"
#include "debris.h"
#include "models.h"
#include "sound.h"
#include "gamesnd.h"
#include "glaunch.h"
#include "mission.h"
#include "felony.h"
#include "wheelforces.h"
#include "handling.h"
#include "camera.h"
#include "objanim.h"
#include "system.h"

extern int gCameraBoxOverlap;

// Checks of two bodies collides (basic check) with Separating Axis Theorem
// also initializes axes
// [D] [T]
int bcollided2d(CDATA2D *body, int* boxOverlap)
{
	int dtheta;
	int ac,as;
	int i, j, k;
 	int xover, zover;
 	int tmp;
 	int FE;
	VECTOR delta;

	dtheta = body[1].theta - body[0].theta;

	// calc axes of each box
	for (i = 0; i < 2; i++)
	{
		as = RSIN(body[i].theta);
		ac = RCOS(body[i].theta);

		body[i].axis[0].vx = as;
		body[i].axis[0].vz = ac;

		body[i].axis[1].vz = -as;
		body[i].axis[1].vx = ac;
	}

	// hmmm, why?
	as = RSIN(dtheta & 0x7ff);			// rcossin_tbl[(dtheta & 0x7ff) * 2];
	ac = RSIN(dtheta + 1024 & 0x7ff);	// rcossin_tbl[(dtheta + 1024 & 0x7ff) * 2];

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

			if (body[i].dist[j] < -body[i].limit[j] ||
				body[i].dist[j] > body[i].limit[j])
				return 0;

			j--;
		} while (j >= 0);

		k++;
		i--;
	} while (i >= 0);

	// calc overlap if needed
	if (boxOverlap)
	{
		FE = ABS(body[1].dist[0]) - ABS(body[1].limit[0]);
		FE = ABS(FE);

		tmp = FIXEDH(body->axis[0].vx * body[1].axis[0].vx + body->axis[0].vz * body[1].axis[0].vz);
		tmp = ABS(tmp);

		if (tmp > 10)
			xover = (FE * ONE) / tmp;
		else
			xover = -1;

		FE = ABS(body[1].dist[1]) - ABS(body[1].limit[1]);
		FE = ABS(FE);

		tmp = FIXEDH(body->axis[0].vx * body[1].axis[1].vx + body->axis[0].vz * body[1].axis[1].vz);
		tmp = ABS(tmp);

		if (tmp > 10)
			zover = (FE * ONE) / tmp;
		else
			zover = xover;

		if (xover <= -1)
			*boxOverlap = zover;
		else if (zover < xover)
			*boxOverlap = zover;
		else
			*boxOverlap = xover;
	}

	return 1;
}

// [D] [T]
void bFindCollisionPoint(CDATA2D *body, CRET2D *collisionResult)
{
	int carBarrierCollision;
	int lower, upper;
	int i, k, besti, bestk;
	int sign, sign0, sign1, smallest;

	CDATA2D* cd;

	besti = 0;
	bestk = 0;
	sign = 0;
	carBarrierCollision = 0;

	smallest = body[0].limit[0] + 1;
	
	if (!body[0].isCameraOrTanner && !body[1].isCameraOrTanner &&
		(body[1].length[1] >= body[1].length[0] * 4 || body[1].length[0] >= body[1].length[1] * 4))
	{
		carBarrierCollision = 1;
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

			if (upper < lower && (body[1].length[k] < body[1].length[1-k] * 4))
			{
				besti = 1;
				sign = 1;
				bestk = k;
			}

			if (lower < upper && (body[1].length[k] < body[1].length[1 - k] * 4))
			{
				besti = 1;
				sign = -1;
				bestk = k;
			}

			k--;
		} while (k >= 0);
	}

	cd = &body[(besti ^ 1)];

	if (cd->axis[0].vx * body[besti].axis[bestk].vx + cd->axis[0].vz * body[besti].axis[bestk].vz + 2048 > -1)
		sign0 = -sign;
	else
		sign0 = sign;

	if (cd->axis[1].vx * body[besti].axis[bestk].vx + cd->axis[1].vz * body[besti].axis[bestk].vz + 2048 > -1)
		sign1 = -sign;
	else
		sign1 = sign;

	collisionResult->penetration = smallest;

	collisionResult->hit.vx = cd->x.vx + FIXEDH(cd->axis[0].vx * cd->length[0] * sign0 + cd->axis[1].vx * cd->length[1] * sign1);
	collisionResult->hit.vz = cd->x.vz + FIXEDH(cd->axis[0].vz * cd->length[0] * sign0 + cd->axis[1].vz * cd->length[1] * sign1);

	if (besti != 0)
		sign = -sign;

	collisionResult->surfNormal.vy = 0;
	collisionResult->surfNormal.vx = body[besti].axis[bestk].vx * sign;
	collisionResult->surfNormal.vz = body[besti].axis[bestk].vz * sign;
}

// [D] [T]
int bFindCollisionTime(CDATA2D *cd, CRET2D *collisionResult)
{
	int hit;
	int i, q;
	int time, step;
	int neverfree;
	CDATA2D original[2];

	hit = 1;
	neverfree = 1;
	time = 4096;
	step = 2048;
	
	for (i = 0; i < 2; i++)
		original[i] = cd[i];

	i = 7;
	do {
		for (q = 0; q < 2; q++)
		{
			cd[q].vel.vx >>= 1;
			cd[q].vel.vz >>= 1;
			cd[q].avel >>= 1;

			if (hit)
			{
				cd[q].x.vx -= cd[q].vel.vx;
				cd[q].x.vz -= cd[q].vel.vz;
				cd[q].theta -= cd[q].avel;
			}
			else
			{
				cd[q].x.vx += cd[q].vel.vx;
				cd[q].x.vz += cd[q].vel.vz;
				cd[q].theta += cd[q].avel;
			}
		}

		if (hit) 
		{
			time -= step;
		}
		else
		{
			neverfree = 0;
			time += step;
		}

		hit = bcollided2d(cd);

		if (i != 0)
			step >>= 1;

		i--;
	} while (i >= 0);

	if (hit == 0) 
	{
		for (i = 0; i < 2; i++)
		{
			cd[i].x.vx += cd[i].vel.vx;
			cd[i].x.vz += cd[i].vel.vz;
			cd[i].theta += cd[i].avel;
		}

		bcollided2d(cd);

		time += step;
	}
	else if (neverfree)
	{
		for (i = 0; i < 2; i++)
		{
			cd[i] = original[i];
			bcollided2d(cd);
		}

		time = ONE;
	}

	collisionResult->neverfree = neverfree;

	return time;
}

// [D] [T]
void ApplyDamage(CAR_DATA *cp, char region, int value, char fakeDamage)
{
	short *pRegion;

	if (cp->controlType == CONTROL_TYPE_PLAYER || cp->controlType == CONTROL_TYPE_LEAD_AI)
		value *= FIXEDH(gPlayerDamageFactor);
	else 
		value *= 2;

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

	if (!fakeDamage) 
	{
		if (cp->totalDamage < USHRT_MAX - value)
			cp->totalDamage += value;
		else
			cp->totalDamage = USHRT_MAX;
	}

	pRegion = &cp->ap.damage[region];
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
		pRegion = &cp->ap.damage[region];
		value >>= 1;

		if (*pRegion < value)
		{
			if (!fakeDamage) 
			{
				if (cp->totalDamage < USHRT_MAX - (value - *pRegion))
					cp->totalDamage += (value - *pRegion);
				else 
					cp->totalDamage = USHRT_MAX;
			}

			*pRegion = value;
		}
	}
}

// [D] [T]
int DamageCar3D(CAR_DATA *cp, LONGVECTOR4* delta, int strikeVel, CAR_DATA *pOtherCar)
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

	if (strikeVel < 40960) 
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
		value = (strikeVel / 350 + 512) * 3;

		value >>= 3;
		
		if (value > 1143)
			value = 1143;
	}
	else if (cp->controlType == CONTROL_TYPE_LEAD_AI)
	{
		if (pOtherCar->controlType == CONTROL_TYPE_PLAYER)
		{
			value = (strikeVel / 350 + 512) * 3;

			value >>= 3;

			if (value > 1143)
				value = 1143;

			cp->ai.l.takeDamage = 50;
		}
		else
		{
			value = strikeVel / 350 + 512;

			value >>= 3;
			
			if (value > 762)
				value = 762;

			if (cp->ai.l.takeDamage == 0)
				value = 0;
		}
	}
	else 
	{
		value = ((strikeVel / 400 + 1024) * 7) >> 3;
	}

	// if cop cars colliding with themselves, only apply fake damage
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


// [D] [T]
void DamageCar(CAR_DATA *cp, CDATA2D *cd, CRET2D *collisionResult, int strikeVel)
{
	int impact;
	int player_id;
	int nose, door, region, value;
	int dx, dz;
	int lbody;

	player_id = GetPlayerId(cp);

	lbody = cp->ap.carCos->colBox.vz / 2;
	impact = strikeVel / 600;

	if (strikeVel >= 20480 && cp->hd.speed > 9) 
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

		if (strikeVel > 2048000) 
			strikeVel = 2048000;

		value = ((strikeVel / 300) * 1024) / 1500;
		if (value > 2048)
			value = 2048;
	
		value -= (value * cp->ap.damage[region] >> 0xd);

		if (cp->controlType == CONTROL_TYPE_LEAD_AI)
		{
			if (cp->ai.l.takeDamage == 0)
				value = 0;
			else 
				value >>= 1;
		}

		ApplyDamage(cp, region, value, 0);
		CollisionSound(player_id, cp, impact, 0);
	}
}

// [D] [T]
int CarBuildingCollision(CAR_DATA *cp, BUILDING_BOX *building, CELL_OBJECT *cop, int flags)
{
	int strikeVel;
	int boxDiffY, buildingHeightY;
	int collided;
	int player_id;
	SMASHABLE_OBJECT* match;
	SMASHABLE_OBJECT* sip;
	CAR_COSMETICS* car_cos;
	MODEL *model;
	VECTOR tempwhere, velocity;
	SVECTOR boxDisp;
	LONGVECTOR4 pointVel, reaction, lever;
	int debris_colour;
	int displacement, denom;

#if 0 //def PSX
	CDATA2D* cd = (CDATA2D*)(u_char*)getScratchAddr(0);
	CRET2D& collisionResult = *(CRET2D*)((u_char*)getScratchAddr(0) + sizeof(CDATA2D) * 2);

	memset((u_char*)cd, 0, sizeof(CDATA2D));
	memset((u_char*)&collisionResult, 0, sizeof(CRET2D));
#else
	static CDATA2D cd[2] = { 0 }; // offset 0x0
	static CRET2D collisionResult = { 0 }; // offset 0xd0
#endif

	model = modelpointers[cop->type];

	boxDiffY = cp->hd.oBox.location.vy + building->pos.vy;
	boxDiffY = ABS(boxDiffY);

	// [A] Boat Jump: make player's life easier getting out
	if (cop->type == 1246 && gCurrentMissionNumber == 35)
		buildingHeightY = building->height / 5;
	else
		buildingHeightY = building->height >> 1;

	if (boxDiffY > buildingHeightY + (cp->hd.oBox.length[1] >> 1) || 
		(cop->pos.vx == OBJECT_SMASHED_MARK) || 
		(model->shape_flags & SHAPE_FLAG_NOCOLLIDE))
	{
		return 0;
	}

	collided = 0;
	car_cos = cp->ap.carCos;

	player_id = GetPlayerId(cp);

	cd[0].isCameraOrTanner = (cp->controlType == CONTROL_TYPE_TANNERCOLLIDER || cp->controlType == CONTROL_TYPE_CAMERACOLLIDER);

	if (cp->controlType == CONTROL_TYPE_TANNERCOLLIDER)
		cd[0].isCameraOrTanner += 2;

	cd[1].isCameraOrTanner = (flags & CollisionCheckFlag_MightBeABarrier) == 0;

	if (cp->controlType == CONTROL_TYPE_TANNERCOLLIDER)
	{
		cd[0].x.vx = cp->hd.where.t[0];
		cd[0].x.vy = cp->hd.where.t[1];
		cd[0].x.vz = cp->hd.where.t[2];
			
		cd[0].vel.vx = FIXEDH(cp->st.n.linearVelocity[0]);
		cd[0].vel.vz = FIXEDH(cp->st.n.linearVelocity[2]);

		cd[0].length[0] = 90;
		cd[0].length[1] = 90;
	}
	else if (cp->controlType == CONTROL_TYPE_CAMERACOLLIDER)
	{
		cd[0].x.vx = cp->hd.where.t[0];
		cd[0].x.vy = cp->hd.where.t[1];
		cd[0].x.vz = cp->hd.where.t[2];
			
		cd[0].vel.vx = 0;
		cd[0].vel.vz = 0;
		cd[0].length[1] = 5;
		cd[0].length[0] = gCameraDistance / 2;
	}
	else
	{
		gte_SetRotMatrix(&cp->hd.where);
		gte_SetTransMatrix(&cp->hd.where);

		boxDisp.vx = -car_cos->cog.vx;
		boxDisp.vy = -car_cos->cog.vy;
		boxDisp.vz = -car_cos->cog.vz;

		gte_ldv0(&boxDisp);
		gte_rtv0tr();
		gte_stlvnl(&cd[0].x);
			
		cd[0].vel.vx = FIXEDH(cp->st.n.linearVelocity[0]);
		cd[0].vel.vz = FIXEDH(cp->st.n.linearVelocity[2]);

		cd[0].length[0] = car_cos->colBox.vz + 15;
		cd[0].length[1] = car_cos->colBox.vx + 15;

		if (handlingType[cp->hndType].fourWheelDrive == 1 || cp->hndType == 5)
			cd[0].length[1] = (cd[0].length[1] * 13) / 16;
	}

	cd[0].theta = cp->hd.direction;
	cd[0].avel = FIXEDH(cp->st.n.angularVelocity[1]) * 5 >> 5;

	tempwhere.vx = cp->hd.where.t[0];
	tempwhere.vz = cp->hd.where.t[2];

	cp->hd.where.t[0] += cd[0].vel.vx;
	cp->hd.where.t[2] += cd[0].vel.vz;

	cd[1].x.vx = cp->hd.where.t[0] + (short)(building->pos.vx - cp->hd.where.t[0]);
	cd[1].x.vz = cp->hd.where.t[2] + (short)(building->pos.vz - cp->hd.where.t[2]);

	cd[1].theta = building->theta;
	cd[1].length[0] = building->xsize;
	cd[1].length[1] = building->zsize;
	cd[1].vel.vx = 0;
	cd[1].vel.vz = 0;
	cd[1].avel = 0;

	if (cp->controlType == CONTROL_TYPE_CAMERACOLLIDER) 
	{
		collided = bcollided2d(cd, &gCameraBoxOverlap);
	}
	else 
	{
		collided = bcollided2d(cd);

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
			if ((model->flags2 & MODEL_FLAG_SMASHABLE) == 0)
			{
				cp->hd.where.t[0] += FIXEDH(collisionResult.penetration * collisionResult.surfNormal.vx);
				cp->hd.where.t[2] += FIXEDH(collisionResult.penetration * collisionResult.surfNormal.vz);
			}

			lever[0] = collisionResult.hit.vx - cp->hd.where.t[0];
			lever[1] = collisionResult.hit.vy - cp->hd.where.t[1];
			lever[2] = collisionResult.hit.vz - cp->hd.where.t[2];

			pointVel[0] = FIXEDH(cp->st.n.angularVelocity[1] * lever[2] - cp->st.n.angularVelocity[2] * lever[1]) + cp->st.n.linearVelocity[0];
			pointVel[1] = FIXEDH(cp->st.n.angularVelocity[2] * lever[0] - cp->st.n.angularVelocity[0] * lever[2]) + cp->st.n.linearVelocity[1];
			pointVel[2] = FIXEDH(cp->st.n.angularVelocity[0] * lever[1] - cp->st.n.angularVelocity[1] * lever[0]) + cp->st.n.linearVelocity[2];

			if (flags & CollisionCheckFlag_IsVegasMovingTrain) // [A] Vegas train velocity - added here
			{
				pointVel[2] += 700000;
			}

			strikeVel = -((pointVel[0] / 256) * (collisionResult.surfNormal.vx / 16) +
						  (pointVel[1] / 256) * (collisionResult.surfNormal.vy / 16) +
						  (pointVel[2] / 256) * (collisionResult.surfNormal.vz / 16));

			if (strikeVel > 0)
			{
				if (cp->controlType == CONTROL_TYPE_PLAYER) 
				{
					short scale;

					if (strikeVel < 32) 
						scale = ((strikeVel << 23) >> 16);
					else 
						scale = 4096;

					if (model->flags2 & MODEL_FLAG_SMASHABLE)
						NoteFelony(&felonyData, 7, scale);
					else
						NoteFelony(&felonyData, 6, scale);
				}

				collisionResult.hit.vy = -collisionResult.hit.vy;

				velocity.vx = cp->st.n.linearVelocity[0] / ONE;
				velocity.vy = -17;
				velocity.vz = cp->st.n.linearVelocity[2] / ONE;

				debris_colour = GetDebrisColour(cp);

				if (model->flags2 & MODEL_FLAG_SMASHABLE)
				{
					// smash object
					damage_object(cop, &velocity);

					// smash object
					if ((model->shape_flags & SHAPE_FLAG_TRANS) == 0)
					{
						int chan;

						sip = smashable;
						match = sip;

						while (sip->name != NULL)
						{
							if (sip->modelIdx == cop->type)
							{
								match = sip;
								break;
							}
							sip++;
						}

						chan = GetFreeChannel();

						if (NumPlayers > 1 && NoPlayerControl == 0)
							SetPlayerOwnsChannel(chan, player_id);

						Start3DSoundVolPitch(chan, SOUND_BANK_SFX, match->sound,
							collisionResult.hit.vx, -collisionResult.hit.vy, collisionResult.hit.vz, 
							match->volume, match->pitch + (((velocity.vx ^ velocity.vz) * (collisionResult.hit.vx ^ collisionResult.hit.vz) & 1023) - 512));
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
					if (model->flags2 & MODEL_FLAG_TREE)
					{
						VECTOR LeafPosition;
						LeafPosition.vx = collisionResult.hit.vx;
						LeafPosition.vy = -((rand() & 0xfe) + 600) - collisionResult.hit.vy;
						LeafPosition.vz = collisionResult.hit.vz;

						AddLeaf(&LeafPosition, 3, 1);
					}
					else 
					{
						if (gNight && (model->flags2 & MODEL_FLAG_LAMP))
						{
							if (damage_lamp(cop))
							{
								VECTOR lamp_velocity;
								lamp_velocity.vx = 0;
								lamp_velocity.vy = 16;
								lamp_velocity.vz = 0;

								collisionResult.hit.vy -= 730;
								Setup_Sparks(&collisionResult.hit, &lamp_velocity, 20, 0);
								collisionResult.hit.vy += 730;
							}
						}

						velocity.vy -= 20;
						collisionResult.hit.vy += 30;

						Setup_Sparks(&collisionResult.hit, &velocity, 4, 0);

						collisionResult.hit.vy -= 30;
						velocity.vy += 20;
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

				denom /= 64;

				reaction[0] = denom * (collisionResult.surfNormal.vx / 64);
				reaction[1] = denom * (collisionResult.surfNormal.vy / 64);
				reaction[2] = denom * (collisionResult.surfNormal.vz / 64);

				cp->hd.aacc[1] += FIXEDH(lever[2] * reaction[0]) - FIXEDH(lever[0] * reaction[2]);

				// angular impulse calculation and modifiers
				if (cp->controlType != CONTROL_TYPE_LEAD_AI)
				{
					int temp;
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

	return collided;
}





