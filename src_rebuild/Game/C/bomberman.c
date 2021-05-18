#include "driver2.h"
#include "bomberman.h"
#include "convert.h"
#include "overmap.h"
#include "players.h"
#include "cars.h"
#include "glaunch.h"
#include "job_fx.h"
#include "dr2roads.h"
#include "pad.h"
#include "camera.h"
#include "draw.h"
#include "debris.h"
#include "mission.h"
#include "denting.h"
#include "cosmetic.h"
#include "bcollide.h"
#include "pedest.h"

#include "ASM/rndrasm.h"

MODEL* gBombModel;

static BOMB ThrownBombs[MAX_THROWN_BOMBS];

static int ThrownBombDelay = 0;
static int CurrentBomb = 0;
static int gWantFlash = 0;
CAR_DATA *gBombTargetVehicle = NULL;
static int flashval;

// [D] [T]
void InitThrownBombs(void)
{
	int i;

	for (i = 0; i < MAX_THROWN_BOMBS; i++)
		ThrownBombs[i].flags = 0;

	ThrownBombDelay = Random2(0) % 45 + 8;
	CurrentBomb = 0;
	gWantFlash = 0;
	gBombTargetVehicle = NULL;
}

// [D] [T]
void DrawThrownBombs(void)
{
	BOMB *bomb;
	int i;
	MATRIX object_matrix;
	VECTOR pos;

	if (gBombModel == NULL)
		return;

	bomb = ThrownBombs;
	i = 0;
	while (i < MAX_THROWN_BOMBS)
	{
		if ((bomb->flags & 1) != 0) 
		{
			InitMatrix(object_matrix);

			RotMatrixY(bomb->rot_speed * bomb->active * 3 & 0xfff, &object_matrix);
			RotMatrixZ(bomb->rot_speed * bomb->active & 0xfff, &object_matrix);

			pos.vx = bomb->position.vx - camera_position.vx;
			pos.vy = bomb->position.vy - camera_position.vy;
			pos.vz = bomb->position.vz - camera_position.vz;

			Apply_Inv_CameraMatrix(&pos);

			gte_SetRotMatrix(&object_matrix);
			gte_SetTransVector(&pos);

			pos.vx = bomb->position.vx;
			pos.vy = bomb->position.vy;
			pos.vz = bomb->position.vz;

			SetFrustrumMatrix();

			if (FrustrumCheck(&pos, gBombModel->bounding_sphere) != -1) 
			{
				PlotMDL_less_than_128(gBombModel);
			}
		}

		i++;
		bomb++;
	}

	if (gWantFlash != 0) 
	{
		add_haze(flashval, flashval, 7);

		flashval -= 10;

		if (flashval < 1)
			gWantFlash = 0;
	}
}

// [D] [T]
void BombThePlayerToHellAndBack(int car)
{
	BOMB *bomb;

	if (car == -1)
		return;

	car_data[car].ap.damage[0] = 0xfff;
	car_data[car].ap.damage[1] = 0xfff;
	car_data[car].ap.damage[2] = 0xfff;
	car_data[car].ap.damage[3] = 0xfff;
	car_data[car].ap.damage[4] = 0xfff;
	car_data[car].ap.damage[5] = 0xfff;

	car_data[car].ap.needsDenting = 1;
	car_data[car].totalDamage = MaxPlayerDamage[0];

	DentCar(&car_data[car]);

	if (maxCivCars == 0) 
	{
		trap(7);
	}

	gBombTargetVehicle = &car_data[(car + 1) % maxCivCars];

	bomb = &ThrownBombs[CurrentBomb++];
	CurrentBomb = CurrentBomb % MAX_THROWN_BOMBS;

	bomb->flags = 1;
	bomb->active = 1;

	bomb->position.vx = car_data[car].hd.where.t[0];
	bomb->position.vy = car_data[car].hd.where.t[1];
	bomb->position.vz = car_data[car].hd.where.t[2];

	bomb->velocity.vx = 0;
	bomb->velocity.vy = 0;
	bomb->velocity.vz = 0;
		
	bomb = &ThrownBombs[CurrentBomb++];
	CurrentBomb = CurrentBomb % MAX_THROWN_BOMBS;

	bomb->flags = 1;
	bomb->active = 1;

	bomb->position.vx = car_data[car].hd.where.t[0] + 170;
	bomb->position.vy = car_data[car].hd.where.t[1];
	bomb->position.vz = car_data[car].hd.where.t[2] + 73;

	bomb->velocity.vx = 0;
	bomb->velocity.vy = 0;
	bomb->velocity.vz = 0;
		
	bomb = &ThrownBombs[CurrentBomb++];
	CurrentBomb = CurrentBomb % MAX_THROWN_BOMBS;

	bomb->flags = 1;
	bomb->active = 1;
	bomb->position.vx = car_data[car].hd.where.t[0] - 109;
	bomb->position.vy = car_data[car].hd.where.t[1];
	bomb->position.vz = car_data[car].hd.where.t[2] - 147;

	bomb->velocity.vx = 0;
	bomb->velocity.vy = 0;
	bomb->velocity.vz = 0;
}

// [D] [T]
int BombCollisionCheck(CAR_DATA *cp, VECTOR *pPos)
{
	CDATA2D cd[2] = {0};

	cd[1].theta = cp->hd.direction;
	cd[1].length[0] = car_cosmetics[cp->ap.model].colBox.vz;
	cd[1].length[1] = car_cosmetics[cp->ap.model].colBox.vx;
	cd[1].x.vx = cp->hd.where.t[0];
	cd[1].x.vz = cp->hd.where.t[2];

	cd[0].x.vx = pPos->vx;
	cd[0].x.vz = pPos->vz;
	cd[0].length[0] = 40;
	cd[0].length[1] = 40;
	cd[0].theta = 0;
	cd[0].avel = 0;
	cd[0].vel.vx = 0;
	cd[0].vel.vy = 0;
	cd[0].vel.vz = 0;

	return bcollided2d(cd);
}

const int minBoxSize = 90;
const int littleBoxRange = 400;
const int halfStrike = 0x32000;
const int fullStrike = 0x32000;

// [D] [T]
void ExplosionCollisionCheck(CAR_DATA *cp, EXOBJECT *pE)
{
	static int setUsed = 0;

	int temp;
	int strikeVel;
	bool isCar;
	VECTOR *pos;
	int displacement;
	int denom;
	int debrisColour;
	CDATA2D cd[2];
	int carLength[2];
	CRET2D collisionResult;
	VECTOR velocity;
	LONGVECTOR4 pointVel;
	LONGVECTOR4 reaction;
	LONGVECTOR4 lever;

	isCar = (cp != &car_data[TANNER_COLLIDER_CARID]);

	if (player[0].playerType == 2 || isCar)
	{
		cd[1].x.vx = cp->hd.where.t[0];
		cd[1].length[0] = car_cosmetics[cp->ap.model].colBox.vz;
		cd[1].length[1] = car_cosmetics[cp->ap.model].colBox.vx;
		cd[1].theta = cp->hd.direction;
		cd[1].x.vz = cp->hd.where.t[2];

		if (pE->type <= LITTLE_BANG)
		{
			cd[0].length[1] = minBoxSize + ((pE->time / pE->speed) * littleBoxRange) / (4096 / pE->speed);
		}
		else if (pE->type == HEY_MOMMA) // biggest bang that might kill Tanner
		{
			pos = (VECTOR*)cp->hd.where.t;

			if (!isCar)
				pos = (VECTOR*)player->pos;

			if (cd[0].length[1] < 0)
				cd[0].length[1] = pos->vx - pE->pos.vx;
			else
				cd[0].length[1] = pE->pos.vx - pos->vx;

			temp = pE->pos.vz - pos->vz;

			if (temp < 0)
				temp = pos->vz - pE->pos.vz;

			if (cd[0].length[1] < temp)
				cd[0].length[1] = temp;

			if (cd[0].length[1] < 3000)
			{
				if (isCar)
				{
					if (CAR_INDEX(cp) == player[0].playerCarId)
					{
						cp->totalDamage = MaxPlayerDamage[0];
						player[0].dying = 1;
						lockAllTheDoors = 1;
					}
				}
				else
				{
					bKillTanner = 1;
					player[0].dying = 1;
				}
			}
			else
			{
				cd[0].length[1] = 10;
			}
		}
		else
		{
			cd[0].length[1] = 0;
		}

		cd[0].x.vx = (pE->pos).vx;
		cd[0].x.vz = (pE->pos).vz;
		cd[0].theta = 0;
		cd[0].avel = 0;
		cd[0].vel.vx = 0;
		cd[0].vel.vy = 0;
		cd[0].vel.vz = 0;
		cd[0].length[0] = cd[0].length[1];

		if (bcollided2d(cd))
		{
			bFindCollisionPoint(cd, &collisionResult);

			cp->hd.where.t[2] += FIXEDH(collisionResult.penetration * collisionResult.surfNormal.vz);
			cp->hd.where.t[0] += FIXEDH(collisionResult.penetration * collisionResult.surfNormal.vx);

			lever[0] = collisionResult.hit.vx - cp->hd.where.t[0];
			lever[1] = 60;
			lever[2] = collisionResult.hit.vz - cp->hd.where.t[2];

			collisionResult.surfNormal.vy = 0;

			if (pE->type == LITTLE_BANG)
				strikeVel = halfStrike - ((pE->time / pE->speed) * halfStrike) / (0x1000 / pE->speed);
			else if (pE->type == BIG_BANG)
				strikeVel = fullStrike;
			else if (pE->type == HEY_MOMMA)
				strikeVel = fullStrike << 1;
			else
				strikeVel = 0;

			setUsed = 1;

			if (strikeVel > 0)
			{
				collisionResult.hit.vy = -(cp->hd.where.t[1] + 60);

				velocity.vx = cp->st.n.linearVelocity[0] >> 0xc;
				velocity.vy = -17;
				velocity.vz = cp->st.n.linearVelocity[2] >> 0xc;

				if (strikeVel > 0x3600)
				{
					collisionResult.hit.vy += 30;
					velocity.vy = -37;
					Setup_Sparks(&collisionResult.hit, &velocity, 4, 0);
					collisionResult.hit.vy -= 30;
					velocity.vy += 20;

					if (strikeVel > 0x1b000)
					{
						debrisColour = GetDebrisColour(cp);
						Setup_Debris(&collisionResult.hit, &velocity, 6, debrisColour << 0x10);

						if (cp->controlType == CONTROL_TYPE_PLAYER)
							SetPadVibration(*cp->ai.padid, 1);
					}
				}

				if(isCar)
					DamageCar(cp, cd, &collisionResult, strikeVel);

				displacement = FIXEDH(lever[0] * collisionResult.surfNormal.vx + lever[1] * collisionResult.surfNormal.vy + lever[2] * collisionResult.surfNormal.vz);
				displacement = FIXEDH(((lever[0] * lever[0] + lever[2] * lever[2]) - displacement * displacement) * car_cosmetics[cp->ap.model].twistRateY) + 4096;

				if (strikeVel < 0x7f001)
					denom = (strikeVel * 4096) / displacement;
				else
					denom = (strikeVel / displacement) * 4096;

				denom >>= 6;

				pointVel[0] = denom * (collisionResult.surfNormal.vx >> 6);
				pointVel[1] = denom * (collisionResult.surfNormal.vy >> 6);
				pointVel[2] = denom * (collisionResult.surfNormal.vz >> 6);

				cp->st.n.linearVelocity[0] += pointVel[0];
				cp->st.n.linearVelocity[1] += pointVel[1];
				cp->st.n.linearVelocity[2] += pointVel[2];

				cp->hd.aacc[0] += FIXEDH(lever[1] * pointVel[2]) - FIXEDH(lever[2] * pointVel[1]);
				cp->hd.aacc[1] += FIXEDH(lever[2] * pointVel[0]) - FIXEDH(lever[0] * pointVel[2]);
				cp->hd.aacc[2] += FIXEDH(lever[0] * pointVel[1]) - FIXEDH(lever[1] * pointVel[0]);
			}
		}

		if (isCar)
			return;
	}

	if (setUsed != 0) 
	{
		pE->type = BANG_USED;
		setUsed = 0;
	}
}

// [D] [T]
void AddFlash(VECTOR *pos)
{
	int dist;

	dist = Long2DDistance(pos, NoPlayerControl ? &player[0].cameraPos : (VECTOR*)player[0].pos);

	if (dist < 2500)
	{
		gWantFlash = 1;
		flashval = 150 - dist / 20;
	}
}

// [D] [T]
void HandleThrownBombs(void)
{
	CAR_DATA* cp;
	BOMB* bomb;
	int i;
	int y;

	int dx, dz;
	VECTOR velocity;

	// throw bombs if we have vehicle
	if (gBombTargetVehicle)
	{
		ThrownBombDelay--;

		if (ThrownBombDelay == -1)
		{
			ThrownBombDelay = Random2(0) % 45 + 8;

			bomb = &ThrownBombs[CurrentBomb++];
			CurrentBomb = CurrentBomb % MAX_THROWN_BOMBS;

			bomb->flags = 1;
			bomb->active = 1;

			bomb->position.vx = gBombTargetVehicle->hd.where.t[0];
			bomb->position.vy = gBombTargetVehicle->hd.where.t[1] - 200;
			bomb->position.vz = gBombTargetVehicle->hd.where.t[2];

			velocity.vx = FIXEDH(gBombTargetVehicle->st.n.linearVelocity[0]);
			velocity.vz = FIXEDH(gBombTargetVehicle->st.n.linearVelocity[2]);

			bomb->velocity.vx = velocity.vx >> 10;
			bomb->velocity.vz = velocity.vz >> 10;
			bomb->velocity.vy = -(Long2DDistance(&bomb->position, (VECTOR*)player[0].pos) >> 7);

			if ((rand() & 1) == 0)
				bomb->rot_speed = -bomb->velocity.vy;
			else
				bomb->rot_speed = bomb->velocity.vy;

			if (bomb->velocity.vy < -100)
				bomb->velocity.vy = -100;
		}
	}

	bomb = ThrownBombs;

	i = 0;
	while (i < MAX_THROWN_BOMBS)
	{
		if (bomb->flags & 1)
		{
			bomb->position.vx += bomb->velocity.vx;
			bomb->position.vy += bomb->velocity.vy;
			bomb->position.vz += bomb->velocity.vz;

			bomb->velocity.vy += 10;

			bomb->active++;

			y = -MapHeight(&bomb->position);

			if (y < bomb->position.vy)
			{
				if ((bomb->flags & 2) == 0)
				{
					bomb->flags |= 2;
					bomb->position.vy = y;
					bomb->velocity.vy = -bomb->velocity.vy / 2; // bounce
				}
				else
				{
					bomb->flags = 0;
					bomb->position.vy = y;

					AddExplosion(bomb->position, LITTLE_BANG);
					AddFlash(&bomb->position);

					dx = (bomb->position.vx - player[0].pos[0]);
					dz = (bomb->position.vz - player[0].pos[2]);

					if (FIXEDH(dx * dx + dz * dz) < 1024)
						SetPadVibration(player[0].padid, 3);		// [A] bug fix
				}
			}

			cp = car_data;

			while (cp < &car_data[MAX_CARS])
			{
				if (cp != gBombTargetVehicle && cp->controlType != CONTROL_TYPE_NONE && BombCollisionCheck(cp, &bomb->position) != 0)
				{
					bomb->flags = 0;

					AddExplosion(bomb->position, BIG_BANG);
					AddFlash(&bomb->position);
				}
				cp++;
			}
		}
		bomb++;
		i++;
	}
}