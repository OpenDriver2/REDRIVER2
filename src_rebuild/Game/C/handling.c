#include "driver2.h"
#include "handling.h"
#include "cosmetic.h"
#include "mission.h"
#include "dr2roads.h"
#include "cars.h"
#include "main.h"
#include "wheelforces.h"
#include "objcoll.h"
#include "denting.h"
#include "camera.h"
#include "felony.h"
#include "debris.h"
#include "pad.h"
#include "cop_ai.h"
#include "bcollide.h"
#include "bcoll3d.h"
#include "gamesnd.h"
#include "pedest.h"
#include "ai.h"
#include "sound.h"
#include "glaunch.h"
#include "shadow.h"
#include "players.h"

inline void UpdateCarDrawMatrix(CAR_DATA* cp)
{
	cp->hd.drawCarMat.m[0][0] = -cp->hd.where.m[0][0];
	cp->hd.drawCarMat.m[0][1] = -cp->hd.where.m[0][1];
	cp->hd.drawCarMat.m[0][2] = -cp->hd.where.m[0][2];

	cp->hd.drawCarMat.m[1][0] = cp->hd.where.m[1][0];
	cp->hd.drawCarMat.m[1][1] = cp->hd.where.m[1][1];
	cp->hd.drawCarMat.m[1][2] = cp->hd.where.m[1][2];

	cp->hd.drawCarMat.m[2][0] = -cp->hd.where.m[2][0];
	cp->hd.drawCarMat.m[2][1] = -cp->hd.where.m[2][1];
	cp->hd.drawCarMat.m[2][2] = -cp->hd.where.m[2][2];
}

// [D] [T]
void InitCarPhysics(CAR_DATA* cp, LONGVECTOR4* startpos, int direction)
{
	int ty;
	int odz;
	int dz;
	int sn, cs;

	dz = car_cosmetics[cp->ap.model].wheelDisp[0].vz + car_cosmetics[cp->ap.model].wheelDisp[1].vz;
	ty = dz / 5;
	odz = dz / 32;

	cp->hd.direction = direction;

	cp->hd.autoBrake = 0;

	sn = RSIN(direction / 2);
	cs = RCOS(direction / 2);

	cp->st.n.orientation[0] = FIXEDH(-cs * ty);
	cp->st.n.orientation[1] = sn;
	cp->st.n.orientation[2] = FIXEDH(sn * ty);
	cp->st.n.orientation[3] = cs;

	cp->st.n.fposition[0] = (*startpos)[0] << 4;
	cp->st.n.fposition[1] = (*startpos)[1] << 4;
	cp->st.n.fposition[2] = (*startpos)[2] << 4;

	cp->st.n.linearVelocity[0] = 0;
	cp->st.n.linearVelocity[1] = 0;
	cp->st.n.linearVelocity[2] = 0;
	cp->st.n.angularVelocity[0] = 0;
	cp->st.n.angularVelocity[1] = 0;
	cp->st.n.angularVelocity[2] = 0;

	cp->hd.aacc[0] = 0;
	cp->hd.aacc[1] = 0;
	cp->hd.aacc[2] = 0;
	cp->hd.acc[0] = 0;
	cp->hd.acc[1] = 0;
	cp->hd.acc[2] = 0;

	RebuildCarMatrix(&cp->st, cp);

	UpdateCarDrawMatrix(cp);

	cp->hd.wheel[0].susCompression = 14 - odz;
	cp->hd.wheel[1].susCompression = odz + 14;
	cp->hd.wheel[2].susCompression = 14 - odz;
	cp->hd.wheel[3].susCompression = odz + 14;

	cp->thrust = 0;
	cp->wheel_angle = 0;
	cp->hd.wheel_speed = 0;
}


// [D] [T]
void TempBuildHandlingMatrix(CAR_DATA* cp, int init)
{
	int dz;
	int sn, cs;

	dz = (car_cosmetics[cp->ap.model].wheelDisp[0].vz + car_cosmetics[cp->ap.model].wheelDisp[1].vz) / 5;

	if (init == 1)
	{
		cp->st.n.fposition[0] = cp->hd.where.t[0] << 4;
		cp->st.n.fposition[1] = cp->hd.where.t[1] << 4;
		cp->st.n.fposition[2] = cp->hd.where.t[2] << 4;
	}

	sn = RSIN(cp->hd.direction / 2);
	cs = RCOS(cp->hd.direction / 2);

	cp->st.n.orientation[0] = FIXEDH(-cs * dz);
	cp->st.n.orientation[1] = sn;
	cp->st.n.orientation[2] = FIXEDH(sn * dz);
	cp->st.n.orientation[3] = cs;

	RebuildCarMatrix(&cp->st, cp);
}


SVECTOR delta = { 0 };
int doWheels = 1;

// [D] [T]
void UpdateCarPoints(CAR_COSMETICS* carCos)
{
	SVECTOR* groundCollPoints;
	SVECTOR* wheelPoints;
	int i;

	groundCollPoints = carCos->cPoints;
	wheelPoints = carCos->wheelDisp;

	for (i = 0; i < 12; i++)
	{
		groundCollPoints->vx += delta.vx;
		groundCollPoints->vy -= delta.vy;
		groundCollPoints->vz += delta.vz;
		groundCollPoints++;
	}

	if (doWheels)
	{
		for (i = 0; i < 4; i++)
		{
			wheelPoints->vx += delta.vx;
			wheelPoints->vy -= delta.vy;
			wheelPoints->vz += delta.vz;
			wheelPoints++;
		}
	}

	carCos->cog.vx += delta.vx;
	carCos->cog.vy += delta.vy;
	carCos->cog.vz -= delta.vz;

	delta.vx = 0;
	delta.vy = 0;
	delta.vz = 0;
}

// [D] [T]
void FixCarCos(CAR_COSMETICS* carCos, int externalModelNumber)
{
	delta.vx = 0;
	delta.vy = 0;
	delta.vz = -(carCos->wheelDisp[0].vz + carCos->wheelDisp[1].vz - 14) / 2;

	doWheels = 1;

	UpdateCarPoints(carCos);

	if (ActiveCheats.cheat10) // [A] cheat for secret car - Fireboyd78
	{
		if (carCos == &car_cosmetics[4] && externalModelNumber == 12)
		{
			carCos->powerRatio += (carCos->powerRatio / 2);
			carCos->mass *= 3;
			carCos->traction *= 2;
			carCos->wheelSize += (carCos->wheelSize / 4);
			carCos->cog.vy -= 20;
		}
	}

	// Super mini cars
	if (ActiveCheats.cheat13)
	{
		int i;
		carCos->wheelSize >>= 1;
		carCos->headLight.vx >>= 1;
		carCos->headLight.vy >>= 1;
		carCos->headLight.vz >>= 1;

		carCos->colBox.vx >>= 1;
		carCos->colBox.vy >>= 1;
		carCos->colBox.vz >>= 1;

		carCos->cog.vx >>= 1;
		carCos->cog.vy >>= 1;
		carCos->cog.vz >>= 1;

		carCos->brakeLight.vx >>= 1;
		carCos->brakeLight.vy >>= 1;
		carCos->brakeLight.vz >>= 1;

		carCos->revLight.vx >>= 1;
		carCos->revLight.vy >>= 1;
		carCos->revLight.vz >>= 1;

		carCos->backInd.vx >>= 1;
		carCos->backInd.vy >>= 1;
		carCos->backInd.vz >>= 1;

		carCos->frontInd.vx >>= 1;
		carCos->frontInd.vy >>= 1;
		carCos->frontInd.vz >>= 1;

		carCos->policeLight.vx >>= 1;
		carCos->policeLight.vy >>= 1;
		carCos->policeLight.vz >>= 1;

		carCos->exhaust.vx >>= 1;
		carCos->exhaust.vy >>= 1;
		carCos->exhaust.vz >>= 1;

		carCos->smoke.vx >>= 1;
		carCos->smoke.vy >>= 1;
		carCos->smoke.vz >>= 1;

		carCos->fire.vx >>= 1;
		carCos->fire.vy >>= 1;
		carCos->fire.vz >>= 1;

		carCos->twistRateX <<= 1;
		carCos->twistRateY <<= 1;
		carCos->twistRateZ <<= 1;

		for (i = 0; i < 4; i++)
		{
			carCos->wheelDisp[i].vx >>= 1;
			carCos->wheelDisp[i].vy >>= 1;
			carCos->wheelDisp[i].vz >>= 1;

			//carCos->wheelDisp[i].vy -= 10;
		}

		for (i = 0; i < 12; i++)
		{
			carCos->cPoints[i].vx >>= 1;
			carCos->cPoints[i].vy >>= 1;
			carCos->cPoints[i].vz >>= 1;
		}
	}

	// Caine's compound heavy Vans
	if (carCos == &car_cosmetics[2] && gCurrentMissionNumber == 7)
	{
		car_cosmetics[2].mass *= 3;
	}
}

int ghost_mode = 0;
int playerghost = 0;
int playerhitcopsanyway = 0;

// [D] [T]
void GlobalTimeStep(void)
{
	static RigidBodyState _tp[MAX_CARS]; // offset 0x0
	static RigidBodyState _d0[MAX_CARS]; // offset 0x410
	static RigidBodyState _d1[MAX_CARS]; // offset 0x820

	int mayBeCollidingBits;
	int howHard;
	int tmp;
	RigidBodyState* thisState_i;
	RigidBodyState* thisState_j;
	RigidBodyState* thisDelta;
	CAR_DATA* cp;
	CAR_DATA* c1;
	RigidBodyState* st;
	RigidBodyState* tp;
	RigidBodyState* d0;
	RigidBodyState* d1;
	LONGVECTOR4 AV;
	LONGQUATERNION delta_orientation;
	LONGVECTOR4 normal;
	LONGVECTOR4 collisionpoint;
	LONGVECTOR4 lever0;
	LONGVECTOR4 lever1;
	LONGVECTOR4 torque;
	LONGVECTOR4 pointVel0;
	VECTOR velocity;
	int depth;
	int RKstep;
	int subframe;
	int j;
	int strikeVel;
	int i;
	int do1;
	int do2;
	int m1;
	int m2;
	int strength;
	int carsDentedThisFrame;
	short *felony;

	if (player[0].playerCarId < 0)
		felony = &pedestrianFelony;
	else
		felony = &car_data[player[0].playerCarId].felonyRating;

	StepCars();
	CheckCarToCarCollisions();

	// step car forces (when no collisions with them)
	for (i = 0; i < num_active_cars; i++)
	{
		cp = active_car_list[i];

		st = &cp->st;

		st->n.linearVelocity[0] += cp->hd.acc[0];
		st->n.linearVelocity[1] += cp->hd.acc[1];
		st->n.linearVelocity[2] += cp->hd.acc[2];

		st->n.angularVelocity[0] += cp->hd.aacc[0];
		st->n.angularVelocity[1] += cp->hd.aacc[1];
		st->n.angularVelocity[2] += cp->hd.aacc[2];

		cp->hd.aacc[0] = 0;
		cp->hd.aacc[1] = 0;
		cp->hd.aacc[2] = 0;

		if (st->n.linearVelocity[1] > 200000) // reduce vertical velocity
			st->n.linearVelocity[1] = (st->n.linearVelocity[1] * 3) / 4;

		if (cp->hd.speed == 0)
		{
			if (ABS(st->n.linearVelocity[0]) + ABS(st->n.linearVelocity[1]) + ABS(st->n.linearVelocity[2]) < 1000)
			{
				st->n.linearVelocity[0] = 0;
				st->n.linearVelocity[1] = 0;
				st->n.linearVelocity[2] = 0;
				st->n.angularVelocity[0] = 0;
				st->n.angularVelocity[1] = 0;
				st->n.angularVelocity[2] = 0;
			}
			else
			{
				cp->hd.speed = 1;
			}
		}

		// limit angular velocity
		tmp = 0x800000;
		if ((tmp < st->n.angularVelocity[0]) || (tmp = -tmp, st->n.angularVelocity[0] < tmp))
			st->n.angularVelocity[0] = tmp;

		tmp = 0x800000;
		if ((tmp < st->n.angularVelocity[1]) || (tmp = -tmp, st->n.angularVelocity[1] < tmp))
			st->n.angularVelocity[1] = tmp;

		tmp = 0x800000;
		if ((tmp < st->n.angularVelocity[2]) || (tmp = -tmp, st->n.angularVelocity[2] < tmp))
			st->n.angularVelocity[2] = tmp;

		// without precision
		if (!cp->hd.mayBeColliding)
		{
			long* orient = st->n.orientation;	// LONGQUATERNION

			st->n.fposition[0] += st->n.linearVelocity[0] >> 8;
			st->n.fposition[1] += st->n.linearVelocity[1] >> 8;
			st->n.fposition[2] += st->n.linearVelocity[2] >> 8;

			AV[0] = FixHalfRound(st->n.angularVelocity[0], 13);
			AV[1] = FixHalfRound(st->n.angularVelocity[1], 13);
			AV[2] = FixHalfRound(st->n.angularVelocity[2], 13);

			delta_orientation[0] = -orient[1] * AV[2] + orient[2] * AV[1] + orient[3] * AV[0];
			delta_orientation[1] = orient[0] * AV[2] - orient[2] * AV[0] + orient[3] * AV[1];
			delta_orientation[2] = -orient[0] * AV[1] + orient[1] * AV[0] + orient[3] * AV[2];
			delta_orientation[3] = -orient[0] * AV[0] - orient[1] * AV[1] - orient[2] * AV[2];

			orient[0] += FIXEDH(delta_orientation[0]);
			orient[1] += FIXEDH(delta_orientation[1]);
			orient[2] += FIXEDH(delta_orientation[2]);
			orient[3] += FIXEDH(delta_orientation[3]);

			RebuildCarMatrix(st, cp);
		}
	}

	// do collision interactions
	for(subframe = 0; subframe < 4; subframe++) 
	{
		RKstep = 0;

		for (RKstep = 0; RKstep < 2; RKstep++)
		{
			for (i = 0; i < num_active_cars; i++)
			{
				cp = active_car_list[i];

				// check collisions with buildings
				if (RKstep != 0 && (subframe & 1) != 0 && cp->controlType == CONTROL_TYPE_PLAYER)
				{
					CheckScenaryCollisions(cp);
				}

				mayBeCollidingBits = cp->hd.mayBeColliding;

				// if has any collision, process with double precision
				if (mayBeCollidingBits)
				{
					if (RKstep == 0)
					{
						thisState_i = &cp->st;
						thisDelta = _d0;
					}
					else
					{
						thisState_i = &_tp[i];
						thisDelta = _d1;
					}

					long* orient = thisState_i->n.orientation;	// LONGQUATERNION

					thisDelta[i].n.fposition[0] = thisState_i->n.linearVelocity[0] >> 8;
					thisDelta[i].n.fposition[1] = thisState_i->n.linearVelocity[1] >> 8;
					thisDelta[i].n.fposition[2] = thisState_i->n.linearVelocity[2] >> 8;

					AV[0] = FixHalfRound(thisState_i->n.angularVelocity[0], 13);
					AV[1] = FixHalfRound(thisState_i->n.angularVelocity[1], 13);
					AV[2] = FixHalfRound(thisState_i->n.angularVelocity[2], 13);

					thisDelta[i].n.orientation[0] = FIXEDH(-orient[1] * AV[2] + orient[2] * AV[1] + orient[3] * AV[0]);
					thisDelta[i].n.orientation[1] = FIXEDH(orient[0] * AV[2] - orient[2] * AV[0] + orient[3] * AV[1]);
					thisDelta[i].n.orientation[2] = FIXEDH(-orient[0] * AV[1] + orient[1] * AV[0] + orient[3] * AV[2]);
					thisDelta[i].n.orientation[3] = FIXEDH(-orient[0] * AV[0] - orient[1] * AV[1] - orient[2] * AV[2]);

					thisDelta[i].n.linearVelocity[0] = 0;
					thisDelta[i].n.linearVelocity[1] = 0;
					thisDelta[i].n.linearVelocity[2] = 0;
					thisDelta[i].n.angularVelocity[0] = 0;
					thisDelta[i].n.angularVelocity[1] = 0;
					thisDelta[i].n.angularVelocity[2] = 0;

					for (j = 0; j < i; j++)
					{
						c1 = active_car_list[j];

						// [A] optimized run to not use the box checking
						// as it has already composed bitfield / pairs
						if((mayBeCollidingBits & (1 << CAR_INDEX(c1))) != 0 && (c1->hd.speed != 0 || cp->hd.speed != 0))
						{
							if(CarCarCollision3(cp, c1, &depth, (VECTOR*)collisionpoint, (VECTOR*)normal))
							{
								if (RKstep > 0)
									thisState_j = &_tp[j];
								else
									thisState_j = &c1->st;
								
								int c1InfiniteMass;
								int c2InfiniteMass;

								collisionpoint[1] -= 0;

								lever0[0] = collisionpoint[0] - cp->hd.where.t[0];
								lever0[1] = collisionpoint[1] - cp->hd.where.t[1];
								lever0[2] = collisionpoint[2] - cp->hd.where.t[2];

								lever1[0] = collisionpoint[0] - c1->hd.where.t[0];
								lever1[1] = collisionpoint[1] - c1->hd.where.t[1];
								lever1[2] = collisionpoint[2] - c1->hd.where.t[2];

								strength = 47 - (lever0[1] + lever1[1]) / 2;

								lever0[1] += strength;
								lever1[1] += strength;

								strikeVel = depth * 0xc000;

								pointVel0[0] = (FIXEDH(thisState_i->n.angularVelocity[1] * lever0[2] - thisState_i->n.angularVelocity[2] * lever0[1]) + thisState_i->n.linearVelocity[0]) -
									(FIXEDH(thisState_j->n.angularVelocity[1] * lever1[2] - thisState_j->n.angularVelocity[2] * lever1[1]) + thisState_j->n.linearVelocity[0]);

								pointVel0[1] = (FIXEDH(thisState_i->n.angularVelocity[2] * lever0[0] - thisState_i->n.angularVelocity[0] * lever0[2]) + thisState_i->n.linearVelocity[1]) -
									(FIXEDH(thisState_j->n.angularVelocity[2] * lever1[0] - thisState_j->n.angularVelocity[0] * lever1[2]) + thisState_j->n.linearVelocity[1]);

								pointVel0[2] = (FIXEDH(thisState_i->n.angularVelocity[0] * lever0[1] - thisState_i->n.angularVelocity[1] * lever0[0]) + thisState_i->n.linearVelocity[2]) -
									(FIXEDH(thisState_j->n.angularVelocity[0] * lever1[1] - thisState_j->n.angularVelocity[1] * lever1[0]) + thisState_j->n.linearVelocity[2]);

								howHard =	(pointVel0[0] / 256) * (normal[0] / 32) +
											(pointVel0[1] / 256) * (normal[1] / 32) +
											(pointVel0[2] / 256) * (normal[2] / 32);

								if (howHard > 0 && RKstep > -1)
								{
									if (DamageCar3D(c1, &lever1, howHard >> 1, cp))
										c1->ap.needsDenting = 1;

									if (DamageCar3D(cp, &lever0, howHard >> 1, c1))
										cp->ap.needsDenting = 1;

									if (howHard > 0x32000)
									{
										if (cp->controlType == CONTROL_TYPE_CIV_AI)
											cp->ai.c.carMustDie = 1;

										if (c1->controlType == CONTROL_TYPE_CIV_AI)
											c1->ai.c.carMustDie = 1;
									}

									// wake up cops if they've ben touched
									// [A] check player felony.
									// If player touch them without felony player will be charged with felony (hit cop car)
									if (numCopCars < 4 && numActiveCops < maxCopCars && GameType != GAME_GETAWAY && *felony >= FELONY_PURSUIT_MIN_VALUE)
									{
										if (cp->controlType == CONTROL_TYPE_PLAYER && IS_ROADBLOCK_CAR(c1))
										{
											InitCopState(c1, NULL);
											c1->ai.p.justPinged = 0;
										}

										if (c1->controlType == CONTROL_TYPE_PLAYER && IS_ROADBLOCK_CAR(cp))
										{
											InitCopState(cp, NULL);
											cp->ai.p.justPinged = 0;
										}
									}

									if (howHard > 0x1b00)
									{
										velocity.vy = -17;
										velocity.vx = FIXED(cp->st.n.linearVelocity[0]);
										velocity.vz = FIXED(cp->st.n.linearVelocity[2]);

										collisionpoint[1] = -collisionpoint[1];

										if (cp->controlType == CONTROL_TYPE_PLAYER || c1->controlType == CONTROL_TYPE_PLAYER)
										{
											Setup_Sparks((VECTOR*)collisionpoint, &velocity, 6, 0);

											if (cp->controlType == CONTROL_TYPE_PLAYER)
												SetPadVibration(*cp->ai.padid, 1);

											if (c1->controlType == CONTROL_TYPE_PLAYER)
												SetPadVibration(*c1->ai.padid, 1);
										}

										if (howHard > 0x2400)
										{
											int debris1;
											int debris2;

											debris1 = GetDebrisColour(cp);
											debris2 = GetDebrisColour(c1);

											Setup_Debris((VECTOR*)collisionpoint, &velocity, 3, 0);
											Setup_Debris((VECTOR*)collisionpoint, &velocity, 6, debris1 << 0x10);
											Setup_Debris((VECTOR*)collisionpoint, &velocity, 2, debris2 << 0x10);
										}
									}
								}

								strikeVel += (howHard * 9) / 4;

								if (strikeVel > 0x69000)
									strikeVel = 0x69000;

								m1 = cp->ap.carCos->mass;
								m2 = c1->ap.carCos->mass;

								if (m2 < m1)
								{
									do1 = (m2 * 4096) / m1;
									do2 = 4096;
								}
								else
								{
									do2 = (m1 * 4096) / m2;
									do1 = 4096;
								}

								c1InfiniteMass = cp->controlType == CONTROL_TYPE_CUTSCENE || m1 == 0x7fff;
								c2InfiniteMass = c1->controlType == CONTROL_TYPE_CUTSCENE || m2 == 0x7fff;

								// [A] if any checked cars has infinite mass, reduce bouncing
								// TODO: very easy difficulty
								if (c1InfiniteMass || c2InfiniteMass)
									strikeVel = strikeVel * 10 >> 2;

								// apply force to car 0
								if (!c1InfiniteMass)
								{
									int twistY, strength1;

									if (cp->controlType == CONTROL_TYPE_PURSUER_AI && c1->controlType != CONTROL_TYPE_LEAD_AI && c1->hndType != 0)
										strength1 = (strikeVel * (7 - gCopDifficultyLevel)) / 8;
									else if (cp->controlType == CONTROL_TYPE_LEAD_AI && c1->hndType != 0)
										strength1 = (strikeVel * 5) / 8;
									else
										strength1 = strikeVel;

									strength1 = FIXEDH(strength1) * do1 >> 3;

									velocity.vx = (normal[0] >> 3) * strength1 >> 6;
									velocity.vz = (normal[2] >> 3) * strength1 >> 6;
									velocity.vy = (normal[1] >> 3) * strength1 >> 6;

									thisDelta[i].n.linearVelocity[0] -= velocity.vx;
									thisDelta[i].n.linearVelocity[1] -= velocity.vy;
									thisDelta[i].n.linearVelocity[2] -= velocity.vz;

									twistY = car_cosmetics[cp->ap.model].twistRateY / 2;

									torque[0] = FIXEDH(velocity.vy * lever0[2] - velocity.vz * lever0[1]) * twistY;
									torque[1] = FIXEDH(velocity.vz * lever0[0] - velocity.vx * lever0[2]) * twistY;
									torque[2] = FIXEDH(velocity.vx * lever0[1] - velocity.vy * lever0[0]) * twistY;

									if (c1->controlType == CONTROL_TYPE_LEAD_AI)
									{
										torque[0] = 0;
										torque[2] = 0;
									}

									thisDelta[i].n.angularVelocity[0] += torque[0];
									thisDelta[i].n.angularVelocity[1] += torque[1];
									thisDelta[i].n.angularVelocity[2] += torque[2];
								}

								// apply force to car 1
								if (!c2InfiniteMass)
								{
									int twistY, strength2;

									if (cp->controlType == CONTROL_TYPE_PURSUER_AI && c1->controlType != CONTROL_TYPE_LEAD_AI && c1->hndType != 0)
										strength2 = (strikeVel * (7 - gCopDifficultyLevel)) / 8;
									else if (c1->controlType == CONTROL_TYPE_LEAD_AI && cp->hndType != 0)
										strength2 = (strikeVel * 5) / 8;
									else
										strength2 = strikeVel;

									strength2 = FIXEDH(strength2) * do2 >> 3;

									velocity.vx = (normal[0] >> 3) * strength2 >> 6;
									velocity.vy = (normal[1] >> 3) * strength2 >> 6;
									velocity.vz = (normal[2] >> 3) * strength2 >> 6;

									thisDelta[j].n.linearVelocity[0] += velocity.vx;
									thisDelta[j].n.linearVelocity[1] += velocity.vy;
									thisDelta[j].n.linearVelocity[2] += velocity.vz;

									twistY = car_cosmetics[c1->ap.model].twistRateY / 2;

									torque[0] = FIXEDH(lever1[1] * velocity.vz - lever1[2] * velocity.vy) * twistY;
									torque[1] = FIXEDH(lever1[2] * velocity.vx - lever1[0] * velocity.vz) * twistY;
									torque[2] = FIXEDH(lever1[0] * velocity.vy - lever1[1] * velocity.vx) * twistY;

									if (c1->controlType == CONTROL_TYPE_LEAD_AI)
									{
										torque[0] = 0;
										torque[2] = 0;
									}

									thisDelta[j].n.angularVelocity[0] += torque[0];
									thisDelta[j].n.angularVelocity[1] += torque[1];
									thisDelta[j].n.angularVelocity[2] += torque[2];
								}

								if (cp->id == player[0].playerCarId || c1->id == player[0].playerCarId)
									RegisterChaseHit(cp->id, c1->id);

								if (cp->id == player[0].playerCarId)
									CarHitByPlayer(c1, howHard);

								if (c1->id == player[0].playerCarId)
									CarHitByPlayer(cp, howHard);
							}
						} // maybe colliding
					} // j loop
				}
			}

			// update forces and rebuild matrix of the cars
			for (i = 0; i < num_active_cars; i++)
			{
				cp = active_car_list[i];

				// if has any collision, process with double precision
				if (cp->hd.mayBeColliding)
				{
					st = &cp->st;
					tp = &_tp[i];
					d0 = &_d0[i];
					d1 = &_d1[i];

					if (RKstep == 0)
					{
						for (j = 0; j < 13; j++)
						{
							tp->v[j] = st->v[j] + (d0->v[j] >> 2);
						}

						RebuildCarMatrix(tp, cp);
					}
					else if (RKstep == 1)
					{
						for (j = 0; j < 13; j++)
						{
							st->v[j] += d0->v[j] + d1->v[j] >> 3;
						}

						RebuildCarMatrix(st, cp);
					}
				}
			}
		}
	}



	// second sub frame passed, update matrices and physics direction
	// dent cars - no more than 5 cars in per frame
	carsDentedThisFrame = 0;

	for (i = 0; i < num_active_cars; i++)
	{
		cp = active_car_list[i];

		UpdateCarDrawMatrix(cp);

		if (cp->ap.needsDenting != 0 && ((CameraCnt + i & 3U) == 0 || carsDentedThisFrame < 5))
		{
			DentCar(cp);

			cp->ap.needsDenting = 0;
			carsDentedThisFrame++;
		}

		cp->hd.direction = ratan2(cp->hd.where.m[0][2], cp->hd.where.m[2][2]);
	}
}

// [D] [T]
void SetShadowPoints(CAR_DATA* c0, VECTOR* outpoints)
{
	int i;
	SVECTOR disp;
	VECTOR pointPos;
	VECTOR surfaceNormal;
	CAR_COSMETICS* car_cos;

	sdPlane* surfacePtr;
	surfacePtr = NULL;

	gte_SetRotMatrix(&c0->hd.where);
	gte_SetTransMatrix(&c0->hd.where);

	car_cos = &car_cosmetics[c0->ap.model];

	for (i = 0; i < 4; i++)
	{
		disp = car_cos->cPoints[i];

		gte_ldv0(&disp);

		gte_rtv0tr();

		gte_stlvnl(&pointPos);

		FindSurfaceD2(&pointPos, &surfaceNormal, &outpoints[i], &surfacePtr);
	}
}

// [D] [T]
void LongQuaternion2Matrix(LONGQUATERNION *qua, MATRIX* m)
{
	int qx = (*qua)[0];
	int qy = (*qua)[1];
	int qz = (*qua)[2];
	int qw = (*qua)[3];

	int yy = FixHalfRound(qy * qy, 11);
	int zz = FixHalfRound(qz * qz, 11);
	int xx = FixHalfRound(qx * qx, 11);
	int zw = FixHalfRound(qz * qw, 11);
	int xy = FixHalfRound(qx * qy, 11);
	int xz = FixHalfRound(qx * qz, 11);
	int yw = FixHalfRound(qy * qw, 11);
	int xw = FixHalfRound(qx * qw, 11);
	int yz = FixHalfRound(qy * qz, 11);

	m->m[0][0] = ONE - (yy + zz);
	m->m[1][1] = ONE - (xx + zz);
	m->m[2][2] = ONE - (xx + yy);
	m->m[0][1] = xy - zw;
	m->m[0][2] = xz + yw;
	m->m[1][0] = xy + zw;
	m->m[2][0] = xz - yw;
	m->m[1][2] = yz - xw;
	m->m[2][1] = yz + xw;
}

// [D] [T]
void initOBox(CAR_DATA* cp)
{
	SVECTOR boxDisp;
	CAR_COSMETICS* car_cos;

	short length;

	gte_SetRotMatrix(&cp->hd.where);
	gte_SetTransMatrix(&cp->hd.where);

	car_cos = &car_cosmetics[cp->ap.model];

	boxDisp.vx = -car_cos->cog.vx;
	boxDisp.vy = -car_cos->cog.vy;
	boxDisp.vz = -car_cos->cog.vz;

	gte_ldv0(&boxDisp);
	gte_rtv0tr();

	if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
	{
		length = (car_cos->colBox.vx * 14) / 16;
		cp->hd.oBox.length[0] = length;
	}
	else
	{
		length = car_cos->colBox.vx;
		cp->hd.oBox.length[0] = length;
	}

	gte_stlvnl(&cp->hd.oBox.location);

	VECTOR svx = { length, 0 ,0 };
	VECTOR svy = { 0, car_cos->colBox.vy ,0 };
	VECTOR svz = { 0, 0 ,car_cos->colBox.vz };

	gte_ldlvl(&svx);

	gte_rtir();
	cp->hd.oBox.length[1] = car_cos->colBox.vy;
	gte_stsv(&cp->hd.oBox.radii[0]);

	gte_ldlvl(&svy);
	gte_rtir();
	cp->hd.oBox.length[2] = car_cos->colBox.vz;
	gte_stsv(&cp->hd.oBox.radii[1]);

	gte_ldlvl(&svz);
	gte_rtir();
	gte_stsv(&cp->hd.oBox.radii[2]);
}


// [D] [T]
void RebuildCarMatrix(RigidBodyState* st, CAR_DATA* cp)
{
	int sm;
	int osm;
	int qw;
	int qz;
	int qy;
	int qx;

	cp->hd.where.t[0] = st->n.fposition[0] >> 4;
	cp->hd.where.t[1] = st->n.fposition[1] >> 4;
	cp->hd.where.t[2] = st->n.fposition[2] >> 4;

	qx = st->n.orientation[0];
	qy = st->n.orientation[1];
	qz = st->n.orientation[2];
	qw = st->n.orientation[3];

	osm = qx * qx + qy * qy + qz * qz + qw * qw;
	sm = 4096;

	if (osm < 1024)
	{
		st->n.orientation[2] = 0;
		st->n.orientation[1] = 0;
		st->n.orientation[0] = 0;
	}
	else
	{
		sm = 0x1800 - (osm >> 13);

		st->n.orientation[0] = FIXEDH(sm * qx);
		st->n.orientation[1] = FIXEDH(sm * qy);
		st->n.orientation[2] = FIXEDH(sm * qz);

		sm = FIXEDH(sm * qw);
	}
	st->n.orientation[3] = sm;

	LongQuaternion2Matrix(&st->n.orientation, &cp->hd.where);

	initOBox(cp);
}


// [D] [T]
void StepCarPhysics(CAR_DATA* cp)
{
	HANDLING_TYPE* hp;
	int car_id;

	int frontWheelSpeed;
	int backWheelSpeed;

	if (cp->controlType == CONTROL_TYPE_NONE)
		return;

	hp = &handlingType[cp->hndType];

	if (cp->hndType == 1)
		hp->aggressiveBraking = 0;
	else
		hp->aggressiveBraking = 1;

#ifdef _DEBUG
	extern int gStopCivCars;
	if (!(gStopCivCars && cp->controlType == CONTROL_TYPE_CIV_AI))
	{
		active_car_list[num_active_cars] = cp;
		num_active_cars++;
	}
#else
	active_car_list[num_active_cars] = cp;
	num_active_cars++;
#endif

	// [A] update wheel rotation - fix for multiplayer outside cameras
	car_id = CAR_INDEX(cp);

	frontWheelSpeed = cp->hd.wheel_speed / 256;

	if (cp->hd.wheel[0].locked == 0)
	{
		FrontWheelRotation[car_id] += frontWheelSpeed;
		FrontWheelRotation[car_id] &= 0xfff;
	}

	if (cp->hd.wheel[3].locked == 0)
	{
		backWheelSpeed = frontWheelSpeed;

		if (cp->wheelspin != 0)
			backWheelSpeed = 700;

		BackWheelRotation[car_id] += backWheelSpeed;
		BackWheelRotation[car_id] &= 0xfff;
	}
}


// [D] [T]
void InitialiseCarHandling(void)
{
	return;
}

// [D] [T]
void CheckCarToCarCollisions(void)
{
	int fz;
	int fx;
	int sz;
	int sx;

	int loop1, loop2;
	int lbod;
	int wbod;
	int hbod;
	int xx, zz;

	BOUND_BOX* bb;
	BOUND_BOX* bb2;
	BOUND_BOX* bb1;
	CAR_DATA* cp;
	SVECTOR* colBox;


	if (ghost_mode == 1)
		return;

	bb = bbox;
	cp = car_data;
	loop1 = 0;

	// build boxes
	do {
		if (cp->controlType == CONTROL_TYPE_NONE ||
			cp->controlType == CONTROL_TYPE_PLAYER && playerghost && !playerhitcopsanyway) // [A] required as game crashing
		{
			bb->y1 = INT_MAX;
			
			cp++;
			bb++;
			loop1++;
			continue;
		}

		colBox = &cp->ap.carCos->colBox;

		hbod = colBox->vy;
		lbod = colBox->vz * 9;
		wbod = colBox->vx * 9;

		sx = cp->hd.where.m[0][0] * wbod / 8;
		sz = cp->hd.where.m[0][2] * lbod / 8;

		fx = cp->hd.where.m[2][0] * wbod / 8;
		fz = cp->hd.where.m[2][2] * lbod / 8;

		xx = FIXEDH(ABS(sz) + ABS(sx)) + hbod;
		zz = FIXEDH(ABS(fz) + ABS(fx)) + hbod;

		bb->x0 = (cp->hd.where.t[0] - xx) / 16;
		bb->z0 = (cp->hd.where.t[2] - zz) / 16;
		bb->x1 = (cp->hd.where.t[0] + xx) / 16;
		bb->z1 = (cp->hd.where.t[2] + zz) / 16;

		if (cp->st.n.linearVelocity[0] < 0)
			bb->x0 = (cp->hd.where.t[0] - xx) / 16 + FIXEDH(cp->st.n.linearVelocity[0]) / 8;
		else
			bb->x1 = (cp->hd.where.t[0] + xx) / 16 + FIXEDH(cp->st.n.linearVelocity[0]) / 8;

		if (cp->st.n.linearVelocity[2] < 0)
			bb->z0 = bb->z0 + (FIXEDH(cp->st.n.linearVelocity[2]) / 8);
		else
			bb->z1 = bb->z1 + (FIXEDH(cp->st.n.linearVelocity[2]) / 8);

		// [A] 2400 for box size - bye bye collision check performance under bridges
		bb->y0 = (cp->hd.where.t[1] - colBox->vy * 2) / 16;
		bb->y1 = (cp->hd.where.t[1] + colBox->vy * 4) / 16;

		// make player handled cars always processed with precision
		if (cp->hndType == 0)
		{
			cp->hd.mayBeColliding = (1 << 31);
		}

		loop1++;
		bb++;
		cp++;
	} while (loop1 < MAX_CARS);

	bb1 = bbox;
	loop1 = 0;

	// check boxes intersection with each other
	do
	{
		bb2 = bb1 + 1;
		loop2 = loop1 + 1;

		while (loop2 < MAX_CARS)
		{
			if (bb1->y1 != INT_MAX && bb2->y1 != INT_MAX &&
				bb2->x0 < bb1->x1 && bb2->z0 < bb1->z1 && bb1->x0 < bb2->x1 &&
				bb1->z0 < bb2->z1 && bb2->y0 < bb1->y1 && bb1->y0 < bb2->y1)
			{
				car_data[loop1].hd.mayBeColliding |= (1 << loop2);
				car_data[loop2].hd.mayBeColliding |= (1 << loop1);
			}

			loop2++;
			bb2++;
		}

#if defined(COLLISION_DEBUG) && !defined(PSX)
		extern int gShowCollisionDebug;
		if (gShowCollisionDebug == 2 && car_data[loop1].controlType != CONTROL_TYPE_NONE)
		{
			extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);

			CVECTOR bbcv = { 0, 0, 250 };
			CVECTOR rrcv = { 250, 0, 0 };
			CVECTOR yycv = { 250, 250, 0 };

			CVECTOR bbcol = car_data[loop1].hd.mayBeColliding ? rrcv : yycv;

			VECTOR box_pointsy0[4] = {
				{bb1->x0 * 16, bb1->y0 * 16, bb1->z0 * 16, 0},	// front left
				{bb1->x1 * 16, bb1->y0 * 16, bb1->z0 * 16, 0},	// front right
				{bb1->x1 * 16, bb1->y0 * 16, bb1->z1 * 16, 0},	// back right
				{bb1->x0 * 16, bb1->y0 * 16, bb1->z1 * 16, 0},	// back left
			};

			Debug_AddLine(box_pointsy0[0], box_pointsy0[1], bbcol);
			Debug_AddLine(box_pointsy0[1], box_pointsy0[2], bbcol);
			Debug_AddLine(box_pointsy0[2], box_pointsy0[3], bbcol);
			Debug_AddLine(box_pointsy0[3], box_pointsy0[0], bbcol);

			VECTOR box_pointsy1[4] = {
				{bb1->x0 * 16, bb1->y1 * 16, bb1->z0 * 16, 0},	// front left
				{bb1->x1 * 16, bb1->y1 * 16, bb1->z0 * 16, 0},	// front right
				{bb1->x1 * 16, bb1->y1 * 16, bb1->z1 * 16, 0},	// back right
				{bb1->x0 * 16, bb1->y1 * 16, bb1->z1 * 16, 0},	// back left
			};

			Debug_AddLine(box_pointsy1[0], box_pointsy1[1], bbcol);
			Debug_AddLine(box_pointsy1[1], box_pointsy1[2], bbcol);
			Debug_AddLine(box_pointsy1[2], box_pointsy1[3], bbcol);
			Debug_AddLine(box_pointsy1[3], box_pointsy1[0], bbcol);

			Debug_AddLine(box_pointsy0[0], box_pointsy1[0], bbcol);
			Debug_AddLine(box_pointsy0[1], box_pointsy1[1], bbcol);
			Debug_AddLine(box_pointsy0[2], box_pointsy1[2], bbcol);
			Debug_AddLine(box_pointsy0[3], box_pointsy1[3], bbcol);
		}
#endif

		bb1++;
		loop1++;

	} while (loop1 < MAX_CARS);
}

// [D] [T]
void ProcessCarPad(CAR_DATA* cp, u_int pad, char PadSteer, char use_analogue)
{
	int player_id;
	int int_steer;
	int analog_angle;
	PED_MODEL_TYPES whoExit;

	whoExit = TANNER_MODEL;

	int_steer = PadSteer;
	player_id = GetPlayerId(cp);

	// Handle player car controls...
	if (cp->controlType == CONTROL_TYPE_PLAYER)
	{
		// handle car leaving
		if ((pad & CAR_PAD_LEAVECAR) == CAR_PAD_LEAVECAR && player_id > -1)
		{
			if (!TannerStuckInCar(1, player_id))
			{
				if (player[player_id].dying == 0)
				{
					if (ActiveCheats.cheat12 && (GameLevel == 1 || GameLevel == 2))		// [A] play as Jericho cheat
						whoExit = OTHER_MODEL;

					ActivatePlayerPedestrian(cp, NULL, 0, NULL, whoExit);
				}
			}
			else if (lockAllTheDoors != 0)
			{
				// this is to show message
				gLockPickingAttempted = 1;
			}
		}

		// Lock car if it has mission lock or fully damaged
		if (gStopPadReads != 0 || MaxPlayerDamage[*cp->ai.padid] <= cp->totalDamage || gCantDrive != 0)
		{
			pad = CAR_PAD_HANDBRAKE;

			// apply brakes
			if (cp->hd.wheel_speed > 36864)
				pad = CAR_PAD_BRAKE;

			int_steer = 0;
			use_analogue = 1;
		}

		// turn of horning
		if (player_id > -1)
		{
			if (CarHasSiren(cp->ap.model) == 0)
				player[player_id].horn.on = (pad >> 3) & 1;
			else if ((cp->lastPad & 8U) == 0 && (pad & 8) != 0)
				player[player_id].horn.on ^= 8;
		}
	}

	if (cp->hd.autoBrake > 90)
		cp->hd.autoBrake = 90;

	// handle burnouts or handbrake
	if (pad & CAR_PAD_HANDBRAKE)
	{
		cp->handbrake = 1;
	}
	else
	{
		cp->handbrake = 0;

		if (pad & CAR_PAD_WHEELSPIN)
			cp->wheelspin = 1;
		else
			cp->wheelspin = 0;

		// continue without burnout
		if (cp->wheelspin != 0 && cp->hd.wheel_speed > 452952)
		{
			cp->wheelspin = 0;
			pad |= CAR_PAD_ACCEL;
		}
	}

	// handle steering
	if (use_analogue == 0)
	{
		if (pad & CAR_PAD_FASTSTEER)
		{
			// fast steer
			if (pad & CAR_PAD_RIGHT)
			{
				cp->wheel_angle += 64;

				if (cp->wheel_angle > 511)
					cp->wheel_angle = 511;
			}

			if (pad & CAR_PAD_LEFT)
			{
				cp->wheel_angle -= 64;

				if (cp->wheel_angle < -511)
					cp->wheel_angle = -511;
			}
		}
		else
		{
			// regular steer
			if (pad & CAR_PAD_RIGHT)
			{
				cp->wheel_angle += 32;

				if (cp->wheel_angle > 352)
					cp->wheel_angle = 352;
			}

			if (pad & CAR_PAD_LEFT)
			{
				cp->wheel_angle -= 32;

				if (cp->wheel_angle < -352)
					cp->wheel_angle = -352;
			}
		}

		if (pad & (CAR_PAD_LEFT | CAR_PAD_RIGHT))
			cp->hd.autoBrake++;
		else
			cp->hd.autoBrake = 0;
	}
	else
	{
		if (pad & CAR_PAD_FASTSTEER)
		{
			int_steer *= (int_steer * int_steer) / 60;
			analog_angle = ((long long)int_steer * 0x88888889) >> 32;		// int_steer * 0.6
		}
		else
		{
			int_steer *= (int_steer * int_steer) / 80;
			analog_angle = ((long long)int_steer * 0x66666667) >> 32;		// int_steer * 0.4
		}

		analog_angle = (analog_angle >> 5) - (int_steer >> 0x1f);

		cp->wheel_angle = analog_angle & 0xfffc;

		if (analog_angle + 270U < 541)
			cp->hd.autoBrake = 0;
		else
			cp->hd.autoBrake++;
	}

	// center steering
	if ((pad & (CAR_PAD_LEFT | CAR_PAD_RIGHT)) == 0)
	{
		if (cp->wheel_angle < -64)
			cp->wheel_angle += 64;
		else if (cp->wheel_angle < 65)
			cp->wheel_angle = 0;
		else
			cp->wheel_angle -= 64;
	}

	cp->thrust = 0;

	//if (gTimeInWater != 0)
	{
		if (pad & CAR_PAD_BRAKE)
		{
			int rws;

			// brakes
			rws = FIXEDH(cp->hd.wheel_speed * 1500 / 1024);

			if (-rws < 23)
				rws = -5000;
			else
				rws = ((rws + 278) * -4778) >> 8;

			cp->thrust = FIXEDH(cp->ap.carCos->powerRatio * rws);
		}
		else if (pad & CAR_PAD_ACCEL)
		{
			if (cp->hndType == 5)
			{
				// rubber band freeroamer.
				// accelerate faster if closer to player
				int dx, dz, dist;

				dx = car_data[player[0].playerCarId].hd.where.t[0] - cp->hd.where.t[0] >> 10;
				dz = car_data[player[0].playerCarId].hd.where.t[2] - cp->hd.where.t[2] >> 10;

				dist = dx * dx + dz * dz;

				if (dist > 40)
					cp->thrust = 3000;
				else if (dist > 20)
					cp->thrust = 4000;
				else if (dist > 9)
					cp->thrust = 4900;
				else
					cp->thrust = 6000;
			}
			else
			{
				cp->thrust = FIXEDH(cp->ap.carCos->powerRatio * 4915);
			}

			if (cp->controlType == CONTROL_TYPE_PLAYER)
			{
				CAR_DATA* tp;
				int targetCarId, cx, cz, chase_square_dist;

				if (player[0].playerCarId == cp->id)
					targetCarId = player[0].targetCarId;
				else if (player[1].playerCarId == cp->id)
					targetCarId = player[1].targetCarId;
				else
					targetCarId = -1;

				// apply rubber banding to player car depending on distance from target car
				if (targetCarId != -1)
				{
					tp = &car_data[targetCarId];

					if (3050 < cp->ap.carCos->powerRatio)
						cp->thrust = FIXEDH(tp->ap.carCos->powerRatio * 4915);

					cx = cp->hd.where.t[0] - tp->hd.where.t[0] >> 10;
					cz = cp->hd.where.t[2] - tp->hd.where.t[2] >> 10;

					chase_square_dist = cx * cx + cz * cz;

					if (chase_square_dist > 20)
						cp->thrust = (cp->thrust * 8000) / 7000;
					else if (chase_square_dist > 6)
						cp->thrust = (cp->thrust * 7400) / 7000;
					else
						cp->thrust = (cp->thrust * 6700) / 7000;
				}
			}

			if (cp->hndType == 0 && cp->hd.changingGear != 0)
				cp->thrust = 1;
		}
	}

	cp->lastPad = pad;
}


// [D] [T]
void InitSkidding(void)
{
	int i;

	for(i = 0; i < 2; i++)
	{
		player[i].wheelnoise.sound = -1;
		player[i].wheelnoise.chan = -1;
		player[i].skidding.sound = -1;
		player[i].skidding.chan = -1;
	}
}


// [D] [T]
void TerminateSkidding(int player_id)
{
	int channel;

	if (player_id < 2)
	{
		channel = player[player_id].skidding.chan;

		if (channel > -1)
		{
			StopChannel(channel);
			UnlockChannel(player[player_id].skidding.chan);

			player[player_id].skidding.sound = -1;
			player[player_id].skidding.chan = -1;
		}

		channel = player[player_id].wheelnoise.chan;

		if (channel > -1)
		{
			StopChannel(channel);
			UnlockChannel(player[player_id].wheelnoise.chan);

			player[player_id].wheelnoise.sound = -1;
			player[player_id].wheelnoise.chan = -1;
		}
	}
}


char rear_only = 0;
char continuous_track = 0;
int last_track_state = -1;
char DebrisTimer = 0;

// [D] [T]
void nose_down(CAR_DATA* cp)
{
	cp->st.n.angularVelocity[0] += cp->hd.where.m[0][0] * 50;
	cp->st.n.angularVelocity[1] += cp->hd.where.m[1][0] * 50;
	cp->st.n.angularVelocity[2] += cp->hd.where.m[2][0] * 50;
}

// [D] [T]
void jump_debris(CAR_DATA* cp)
{
	WHEEL* wheel;
	int count;
	VECTOR position;
	VECTOR velocity;

	wheel = cp->hd.wheel;

	for(count = 0; count < 4; count++)
	{
		if (wheel->susCompression != 0)
		{
			DebrisTimer = 0;
			cp->wasOnGround = 1;
			return;
		}

		wheel++;
	}

	if (cp->wasOnGround == 1)
	{
		cp->wasOnGround = 0;
		DebrisTimer = 80;

		nose_down(cp);
	}

	if (DebrisTimer != 0 && --DebrisTimer < 75)
	{
		memset((u_char*)&velocity, 0, sizeof(velocity));

		velocity.vx = cp->hd.where.t[0] + ((rand() & 0x1ff) - 256);
		velocity.vy = 200 - cp->hd.where.t[1];

		position.vz = cp->hd.where.t[2] + ((rand() & 0x1ff) - 256);
		position.vx = velocity.vx;
		position.vy = velocity.vy;
		position.pad = velocity.pad;

		velocity.vz = position.vz;

		memset((u_char*)&velocity, 0, sizeof(velocity));
		Setup_Debris(&position, &velocity, 5, 0xb);
	}
}

// [D] [T]
void CheckCarEffects(CAR_DATA* cp, int player_id)
{
	int channel;

	int skidsound;
	int cnt;
	int wheels_on_ground;
	char lay_down_tracks;
	char tracks_and_smoke;
	char desired_skid;
	char desired_wheel;

	wheels_on_ground = 0;
	lay_down_tracks = 0;
	tracks_and_smoke = 0;

	if (cp->controlType != CONTROL_TYPE_PLAYER && 
		cp->controlType != CONTROL_TYPE_LEAD_AI && 
		cp->controlType != CONTROL_TYPE_CUTSCENE)
	{
		TerminateSkidding(player_id);
		return;
	}

	// PHYSICS! jumping effects, also make car nose down
	jump_debris(cp);

	// [A] do hubcaps here
	HandlePlayerHubcaps(player_id);

	for (cnt = 0; cnt < 4; cnt++)
	{
		if (cp->hd.wheel[cnt].susCompression != 0)
			wheels_on_ground = 1;
	}

	skidsound = 0;

	// make tyre tracks and skid sound if needed
	if (wheels_on_ground)
	{
		int rear_vel, front_vel;
		rear_vel = ABS(cp->hd.rear_vel);
		front_vel = ABS(cp->hd.front_vel);

		if (rear_vel > 22000 || cp->wheelspin)
		{
			rear_only = 1;
			lay_down_tracks = true;

			if (cp->wheelspin == 0)
				skidsound = (rear_vel - 11100) / 2 + 1;
			else
				skidsound = 13000;

			if (skidsound > 13000)
				skidsound = 13000;
		}
		else if (front_vel > 50000)
		{
			rear_only = 0;
			lay_down_tracks = true;
		}

		tracks_and_smoke = (player_id < 2) && !(cp->hd.wheel[1].surface & 0x8) && !(cp->hd.wheel[3].surface & 0x8);
	}

	desired_skid = -1;

	// should be on asphalt
	if (skidsound != 0 && ((cp->hd.wheel[1].surface & 0x80) == 0 || (cp->hd.wheel[3].surface & 0x80) == 0))
	{
		if (gWeather - 1U < 2)
			desired_skid = -1;
		else
			desired_skid = 7;
	}

	// play skid sound
	if (desired_skid != player[player_id].skidding.sound)
	{
		player[player_id].skidding.sound = desired_skid;

		if (player[player_id].skidding.chan > -1)
		{
			StopChannel(player[player_id].skidding.chan);
			UnlockChannel(player[player_id].skidding.chan);

			player[player_id].skidding.chan = -1;
		}

		if (player[player_id].skidding.sound > -1)
		{
			channel = StartSound(-1, SOUND_BANK_SFX, player[player_id].skidding.sound, skidsound - 10000, 4096);

			player[player_id].skidding.chan = channel;
			LockChannel(channel);

			if (NumPlayers > 1 && NoPlayerControl == 0)
				SetPlayerOwnsChannel(player[player_id].skidding.chan, player_id);
		}
	}

	// update skidding sound
	if (player[player_id].skidding.sound > -1 && 
		player[player_id].skidding.chan > -1)
	{
		SetChannelPosition3(player[player_id].skidding.chan,
			(VECTOR*)cp->hd.where.t,
			(LONGVECTOR3*)cp->st.n.linearVelocity,
			(skidsound - 10000) * 3 / 4 - 5000,
			skidsound * 1024 / 13000 + 3072 + player_id * 8, 0);
	}

	// pick best wheel
	desired_wheel = -1;

	if (wheels_on_ground && cp->hd.speed > 10)
	{
		int wnse, wheel2;

		wnse = cp->hd.wheel[3].surface & 7;
		wheel2 = cp->hd.wheel[1].surface & 7;

		if (wheel2 > wnse)
			wnse = wheel2;

		if (gWeather - 1U > 1)
		{
			if (wnse != 0)
				desired_wheel = wnse + 8;
			else
				desired_wheel = -1;
		}
		else
			desired_wheel = 13 - 4;
	}

	// play noise sound
	if (desired_wheel != player[player_id].wheelnoise.sound)
	{
		player[player_id].wheelnoise.sound = desired_wheel;

		if (player[player_id].wheelnoise.chan > -1)
		{
			StopChannel(player[player_id].wheelnoise.chan);
			UnlockChannel(player[player_id].wheelnoise.chan);

			player[player_id].wheelnoise.chan = -1;
		}

		if (player[player_id].wheelnoise.sound > -1)
		{
			channel = StartSound(-1, SOUND_BANK_SFX, player[player_id].wheelnoise.sound, -200, 4096);

			player[player_id].wheelnoise.chan = channel;
			LockChannel(channel);

			if (NumPlayers > 1 && NoPlayerControl == 0)
				SetPlayerOwnsChannel(player[player_id].wheelnoise.chan, player_id);
		}
	}

	// update wheel noise
	if (player[player_id].wheelnoise.sound > -1 && 
		player[player_id].wheelnoise.chan > -1)
	{
		int pitch, spd;

		spd = cp->hd.speed;
		if (spd > 100)
			spd = 100;

		pitch = spd * 27;

		if (pitch > 3584)
			pitch = 3584;

		SetChannelPosition3(player[player_id].wheelnoise.chan,
			(VECTOR*)cp->hd.where.t, 
			(LONGVECTOR3*)cp->st.n.linearVelocity,
			spd * 50 - 10000,
			pitch + player_id * 8, 0);
	}

	player[player_id].onGrass = 0;

	GetTyreTrackPositions(cp, player_id);

	// make tyre tracks
	if (lay_down_tracks)
	{
		continuous_track = (last_track_state == rear_only);

		AddTyreTrack(player_id * 2, tracks_and_smoke, player_id);
		AddTyreTrack(player_id * 2 + 1, tracks_and_smoke, player_id);

		last_track_state = rear_only;
	}
	else
	{
		last_track_state = -1;
	}

	SetTyreTrackOldPositions(player_id);
}

// [D] [T]
int GetPlayerId(CAR_DATA* cp)
{
	int i;
	int p_id;

	for (i = 0; i < 3; i++)
	{
		p_id = player[i].playerCarId;

		if (&car_data[p_id] == cp)
			return i;
	}

	return -1;
}





