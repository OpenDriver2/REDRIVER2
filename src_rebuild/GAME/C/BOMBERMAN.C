#include "DRIVER2.H"
#include "BOMBERMAN.H"
#include "CONVERT.H"
#include "OVERMAP.H"
#include "PLAYERS.H"
#include "CARS.H"
#include "GLAUNCH.H"
#include "JOB_FX.H"
#include "DR2ROADS.H"
#include "PAD.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "DEBRIS.H"
#include "MISSION.H"
#include "DENTING.H"
#include "COSMETIC.H"
#include "BCOLLIDE.H"
#include "PEDEST.H"

#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"
#include "RAND.H"

MODEL* gBombModel;

static BOMB ThrownBombs[MAX_THROWN_BOMBS];

static int ThrownBombDelay = 0;
static int CurrentBomb = 0;
static int gWantFlash = 0;
_CAR_DATA *gBombTargetVehicle = NULL;
static int flashval;

// decompiled code
// original method signature: 
// void /*$ra*/ InitThrownBombs()
 // line 222, offset 0x0001f570
	/* begin block 1 */
		// Start line: 224
		// Start offset: 0x0001F570
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x0001F5F4
	// End Line: 235

	/* begin block 2 */
		// Start line: 1445
	/* end block 2 */
	// End Line: 1446

	/* begin block 3 */
		// Start line: 444
	/* end block 3 */
	// End Line: 445

	/* begin block 4 */
		// Start line: 1446
	/* end block 4 */
	// End Line: 1447

	/* begin block 5 */
		// Start line: 1448
	/* end block 5 */
	// End Line: 1449

/* WARNING: Unknown calling convention yet parameter storage is locked */

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



// decompiled code
// original method signature: 
// void /*$ra*/ HandleThrownBombs()
 // line 245, offset 0x0001e3e8
	/* begin block 1 */
		// Start line: 247
		// Start offset: 0x0001E3E8
		// Variables:
	// 		struct BOMB *bomb; // $s1
	// 		struct VECTOR velocity; // stack offset -48
	// 		struct _CAR_DATA *cp; // $s0
	// 		int i; // $s5
	// 		int y; // $a0

		/* begin block 1.1 */
			// Start line: 258
			// Start offset: 0x0001E42C
		/* end block 1.1 */
		// End offset: 0x0001E5C8
		// End Line: 301

		/* begin block 1.2 */
			// Start line: 319
			// Start offset: 0x0001E670
			// Variables:
		// 		int len; // $v1
		/* end block 1.2 */
		// End offset: 0x0001E6E8
		// End Line: 330
	/* end block 1 */
	// End offset: 0x0001E7E8
	// End Line: 357

	/* begin block 2 */
		// Start line: 490
	/* end block 2 */
	// End Line: 491

	/* begin block 3 */
		// Start line: 491
	/* end block 3 */
	// End Line: 492

	/* begin block 4 */
		// Start line: 497
	/* end block 4 */
	// End Line: 498

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void HandleThrownBombs(void)
{
	_CAR_DATA *cp;
	BOMB *bomb;
	int i;
	int y;

	int dx, dz;
	VECTOR velocity;

	if (gBombTargetVehicle == NULL)
		return;

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
		velocity.vy = 0;
		velocity.vz = FIXEDH(gBombTargetVehicle->st.n.linearVelocity[2]);

		bomb->velocity.vx = velocity.vx >> 10;
		bomb->velocity.vz = velocity.vz >> 10;
		bomb->velocity.vy = -(Long2DDistance(&bomb->position, (VECTOR *)player[0].pos) >> 7);

		if ((rand() & 1) == 0)
			bomb->rot_speed = -bomb->velocity.vy;
		else
			bomb->rot_speed = bomb->velocity.vy;

		if (bomb->velocity.vy < -100)
			bomb->velocity.vy = -100;
	}

	bomb = ThrownBombs;

	i = 0;
	while (i < MAX_THROWN_BOMBS)
	{
		if ((bomb->flags & 1) != 0) 
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
			while (cp < car_data + MAX_CARS)
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
	};
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawThrownBombs()
 // line 381, offset 0x0001e810
	/* begin block 1 */
		// Start line: 383
		// Start offset: 0x0001E810
		// Variables:
	// 		struct MATRIX object_matrix; // stack offset -80
	// 		struct MATRIX *finalmatrix; // $s2
	// 		struct BOMB *bomb; // $s0
	// 		struct VECTOR pos; // stack offset -48
	// 		int i; // $s3

		/* begin block 1.1 */
			// Start line: 397
			// Start offset: 0x0001E86C
		/* end block 1.1 */
		// End offset: 0x0001E998
		// End Line: 414

		/* begin block 1.2 */
			// Start line: 420
			// Start offset: 0x0001E9B4
		/* end block 1.2 */
		// End offset: 0x0001E9DC
		// End Line: 424
	/* end block 1 */
	// End offset: 0x0001E9DC
	// End Line: 425

	/* begin block 2 */
		// Start line: 864
	/* end block 2 */
	// End Line: 865

	/* begin block 3 */
		// Start line: 865
	/* end block 3 */
	// End Line: 866

	/* begin block 4 */
		// Start line: 871
	/* end block 4 */
	// End Line: 872

/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawThrownBombs(void)
{
	int iVar1;
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
			object_matrix.m[0][0] = 0x1000;
			object_matrix.m[0][1] = 0;
			object_matrix.m[0][2] = 0;

			object_matrix.m[1][0] = 0;
			object_matrix.m[1][1] = 0x1000;
			object_matrix.m[1][2] = 0;

			object_matrix.m[2][0] = 0;
			object_matrix.m[2][1] = 0;
			object_matrix.m[2][2] = 0x1000;

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



// decompiled code
// original method signature: 
// void /*$ra*/ BombThePlayerToHellAndBack(int car /*$s3*/)
 // line 432, offset 0x0001ea00
	/* begin block 1 */
		// Start line: 433
		// Start offset: 0x0001EA00
		// Variables:
	// 		struct BOMB *bomb; // $t3
	/* end block 1 */
	// End offset: 0x0001EC3C
	// End Line: 486

	/* begin block 2 */
		// Start line: 1001
	/* end block 2 */
	// End Line: 1002

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



// decompiled code
// original method signature: 
// int /*$ra*/ BombCollisionCheck(struct _CAR_DATA *cp /*$a0*/, struct VECTOR *pPos /*$a1*/)
 // line 496, offset 0x0001ec58
	/* begin block 1 */
		// Start line: 497
		// Start offset: 0x0001EC58
		// Variables:
	// 		struct CDATA2D cd[2]; // stack offset -216
	// 		int carLength[2]; // stack offset -16

		/* begin block 1.1 */
			// Start line: 497
			// Start offset: 0x0001EC58
		/* end block 1.1 */
		// End offset: 0x0001EC58
		// End Line: 497
	/* end block 1 */
	// End offset: 0x0001ED18
	// End Line: 523

	/* begin block 2 */
		// Start line: 1230
	/* end block 2 */
	// End Line: 1231

	/* begin block 3 */
		// Start line: 1235
	/* end block 3 */
	// End Line: 1236

// [D] [T]
int BombCollisionCheck(_CAR_DATA *cp, VECTOR *pPos)
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

	return bcollided2d(cd, 1) != 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ExplosionCollisionCheck(struct _CAR_DATA *cp /*$s1*/, struct _ExOBJECT *pE /*$s3*/)
 // line 534, offset 0x0001ed18
	/* begin block 1 */
		// Start line: 535
		// Start offset: 0x0001ED18
		// Variables:
	// 		struct CDATA2D cd[2]; // stack offset -352
	// 		int carLength[2]; // stack offset -152
	// 		static int setUsed; // offset 0x28
	// 		int tanner; // $s6

		/* begin block 1.1 */
			// Start line: 546
			// Start offset: 0x0001ED74

			/* begin block 1.1.1 */
				// Start line: 546
				// Start offset: 0x0001ED74
			/* end block 1.1.1 */
			// End offset: 0x0001ED74
			// End Line: 546

			/* begin block 1.1.2 */
				// Start line: 553
				// Start offset: 0x0001EE0C
			/* end block 1.1.2 */
			// End offset: 0x0001EE80
			// End Line: 558

			/* begin block 1.1.3 */
				// Start line: 561
				// Start offset: 0x0001EE80
				// Variables:
			// 		int x; // $a1
			// 		int z; // $v1
			// 		struct VECTOR *pos; // $v0
			/* end block 1.1.3 */
			// End offset: 0x0001EF54
			// End Line: 600

			/* begin block 1.1.4 */
				// Start line: 623
				// Start offset: 0x0001EF94
				// Variables:
			// 		struct CRET2D collisionResult; // stack offset -144

				/* begin block 1.1.4.1 */
					// Start line: 626
					// Start offset: 0x0001EF94
					// Variables:
				// 		struct VECTOR velocity; // stack offset -104
				// 		long pointVel[4]; // stack offset -88
				// 		long reaction[4]; // stack offset -72
				// 		long lever[4]; // stack offset -56
				// 		int strikeVel; // $s0

					/* begin block 1.1.4.1.1 */
						// Start line: 688
						// Start offset: 0x0001F210
					/* end block 1.1.4.1.1 */
					// End offset: 0x0001F250
					// End Line: 695

					/* begin block 1.1.4.1.2 */
						// Start line: 698
						// Start offset: 0x0001F250
						// Variables:
					// 		int twistY; // $a1
					// 		int lever_dot_n; // $a0
					// 		int displacementsquared; // $v1
					// 		int denom; // $v1
					/* end block 1.1.4.1.2 */
					// End offset: 0x0001F360
					// End Line: 710
				/* end block 1.1.4.1 */
				// End offset: 0x0001F4A8
				// End Line: 732
			/* end block 1.1.4 */
			// End offset: 0x0001F4A8
			// End Line: 733
		/* end block 1.1 */
		// End offset: 0x0001F4A8
		// End Line: 734
	/* end block 1 */
	// End offset: 0x0001F4F4
	// End Line: 740

	/* begin block 2 */
		// Start line: 1339
	/* end block 2 */
	// End Line: 1340

	/* begin block 3 */
		// Start line: 1351
	/* end block 3 */
	// End Line: 1352

/* WARNING: Removing unreachable block (ram,0x0001ef54) */

const int minBoxSize = 90;
const int littleBoxRange = 400;
const int halfStrike = 0x32000;
const int fullStrike = 0x32000;

// [D] [T]
void ExplosionCollisionCheck(_CAR_DATA *cp, _ExOBJECT *pE)
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
	long pointVel[4];
	long reaction[4];
	long lever[4];

	isCar = (cp != car_data + MAX_CARS);

	if (player[0].playerType == 2 || isCar)
	{

		cd[1].x.vx = cp->hd.where.t[0];
		cd[1].length[0] = car_cosmetics[cp->ap.model].colBox.vz;
		cd[1].length[1] = car_cosmetics[cp->ap.model].colBox.vx;
		cd[1].theta = cp->hd.direction;
		cd[1].x.vz = cp->hd.where.t[2];

		if (pE->type <= LITTLE_BANG)
		{
			cd[0].length[1] = minBoxSize + ((pE->time / pE->speed) * littleBoxRange) / (0x1000 / pE->speed);
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

		if (bcollided2d(cd, 1) != 0)
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

				DamageCar(cp, cd, &collisionResult, strikeVel);

				displacement = FIXEDH(lever[0] * collisionResult.surfNormal.vx + lever[1] * collisionResult.surfNormal.vy + lever[2] * collisionResult.surfNormal.vz);
				displacement = FIXEDH(((lever[0] * lever[0] + lever[2] * lever[2]) - displacement * displacement) * car_cosmetics[cp->ap.model].twistRateY) + 0x1000;

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



// decompiled code
// original method signature: 
// void /*$ra*/ AddFlash(struct VECTOR *pos /*$a0*/)
 // line 747, offset 0x0001f4f4
	/* begin block 1 */
		// Start line: 748
		// Start offset: 0x0001F4F4
		// Variables:
	// 		int dist; // $a0
	/* end block 1 */
	// End offset: 0x0001F570
	// End Line: 761

	/* begin block 2 */
		// Start line: 1947
	/* end block 2 */
	// End Line: 1948

	/* begin block 3 */
		// Start line: 1955
	/* end block 3 */
	// End Line: 1956

	/* begin block 4 */
		// Start line: 1958
	/* end block 4 */
	// End Line: 1959

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





