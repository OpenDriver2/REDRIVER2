#include "DRIVER2.H"
#include "HANDLING.H"
#include "COSMETIC.H"
#include "MISSION.H"
#include "DR2ROADS.H"
#include "CARS.H"
#include "MAIN.H"
#include "WHEELFORCES.H"
#include "OBJCOLL.H"
#include "DENTING.H"
#include "CAMERA.H"
#include "FELONY.H"
#include "DEBRIS.H"
#include "PAD.H"
#include "COP_AI.H"
#include "BCOLLIDE.H"
#include "BCOLL3D.H"
#include "GAMESND.H"
#include "PEDEST.H"
#include "AI.H"
#include "SOUND.H"
#include "GLAUNCH.H"
#include "SHADOW.H"
#include "PLAYERS.H"
#include "INLINE_C.H"
#include "STRINGS.H"

#include "RAND.H"

// decompiled code
// original method signature: 
// void /*$ra*/ InitCarPhysics(struct _CAR_DATA *cp /*$s0*/, long (*startpos)[4] /*$t0*/, int direction /*$a2*/)
 // line 998, offset 0x0005381c
	/* begin block 1 */
		// Start line: 999
		// Start offset: 0x0005381C
		// Variables:
	// 		int ty; // $v1
	// 		int dz; // $s1
	// 		int odz; // $a3

		/* begin block 1.1 */
			// Start line: 1004
			// Start offset: 0x00053890
			// Variables:
		// 		unsigned long *dst; // $a1
		/* end block 1.1 */
		// End offset: 0x00053890
		// End Line: 1004
	/* end block 1 */
	// End offset: 0x000539E8
	// End Line: 1040

	/* begin block 2 */
		// Start line: 1996
	/* end block 2 */
	// End Line: 1997

	/* begin block 3 */
		// Start line: 2000
	/* end block 3 */
	// End Line: 2001


// [D] [T]
void InitCarPhysics(_CAR_DATA *cp, long(*startpos)[4], int direction)
{
	int ty;
	int odz;
	int dz;

	dz = car_cosmetics[cp->ap.model].wheelDisp[0].vz + car_cosmetics[cp->ap.model].wheelDisp[1].vz;
	ty = dz / 5;
	odz = FixFloorSigned(dz, 5);

	cp->hd.direction = direction;

	cp->hd.autoBrake = 0;

	cp->st.n.orientation[0] = FIXEDH(-rcossin_tbl[(direction & 0xffeU) + 1] * ty);
	cp->st.n.orientation[1] = rcossin_tbl[direction & 0xffeU];
	cp->st.n.orientation[2] = FIXEDH(rcossin_tbl[direction & 0xffeU] * ty);
	cp->st.n.orientation[3] = rcossin_tbl[(direction & 0xffeU) + 1];

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

	cp->hd.drawCarMat.m[0][0] = ~cp->hd.where.m[0][0];
	cp->hd.drawCarMat.m[0][1] = ~cp->hd.where.m[0][1];
	cp->hd.drawCarMat.m[0][2] = ~cp->hd.where.m[0][2];
	cp->hd.drawCarMat.m[1][0] = cp->hd.where.m[1][0];
	cp->hd.drawCarMat.m[1][1] = cp->hd.where.m[1][1];
	cp->hd.drawCarMat.m[1][2] = cp->hd.where.m[1][2];
	cp->hd.drawCarMat.m[2][0] = ~cp->hd.where.m[2][0];
	cp->hd.drawCarMat.m[2][1] = ~cp->hd.where.m[2][1];
	cp->hd.drawCarMat.m[2][2] = ~cp->hd.where.m[2][2];

	cp->hd.wheel[0].susCompression = 14 - odz;
	cp->hd.wheel[1].susCompression = odz + 14;
	cp->hd.wheel[2].susCompression = 14 - odz;
	cp->hd.wheel[3].susCompression = odz + 14;
	
	cp->thrust = 0;
	cp->wheel_angle = 0;
	cp->hd.wheel_speed = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ TempBuildHandlingMatrix(struct _CAR_DATA *cp /*$s0*/, int init /*$a1*/)
 // line 1055, offset 0x000539e8
	/* begin block 1 */
		// Start line: 1056
		// Start offset: 0x000539E8
		// Variables:
	// 		int ty; // $v1
	// 		int dz; // $a3
	/* end block 1 */
	// End offset: 0x00053B08
	// End Line: 1075

	/* begin block 2 */
		// Start line: 2158
	/* end block 2 */
	// End Line: 2159

	/* begin block 3 */
		// Start line: 2174
	/* end block 3 */
	// End Line: 2175

	/* begin block 4 */
		// Start line: 2178
	/* end block 4 */
	// End Line: 2179

// [D] [T]
void TempBuildHandlingMatrix(_CAR_DATA *cp, int init)
{
	int dz;
	int ang;

	dz = (car_cosmetics[cp->ap.model].wheelDisp[0].vz + car_cosmetics[cp->ap.model].wheelDisp[1].vz) / 5;

	if (init == 1) 
	{
		cp->st.n.fposition[0] = cp->hd.where.t[0] << 4;
		cp->st.n.fposition[1] = cp->hd.where.t[1] << 4;
		cp->st.n.fposition[2] = cp->hd.where.t[2] << 4;
	}

	ang = cp->hd.direction & 0xffe;

	cp->st.n.orientation[0] = FIXEDH(-rcossin_tbl[ang + 1] * dz);
	cp->st.n.orientation[1] = rcossin_tbl[ang];
	cp->st.n.orientation[2] = FIXEDH(rcossin_tbl[ang] * dz);
	cp->st.n.orientation[3] = rcossin_tbl[ang + 1];

	RebuildCarMatrix(&cp->st, cp);
	SetShadowPoints(cp);
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateCarPoints(struct CAR_COSMETICS *carCos /*$a0*/)
 // line 1079, offset 0x00053b08
	/* begin block 1 */
		// Start line: 1080
		// Start offset: 0x00053B08
		// Variables:
	// 		struct SVECTOR *groundCollPoints; // $a1
	// 		struct SVECTOR *wheelPoints; // $a3
	// 		int i; // $a2
	/* end block 1 */
	// End offset: 0x00053C00
	// End Line: 1103

	/* begin block 2 */
		// Start line: 2233
	/* end block 2 */
	// End Line: 2234

	/* begin block 3 */
		// Start line: 2238
	/* end block 3 */
	// End Line: 2239

	/* begin block 4 */
		// Start line: 2239
	/* end block 4 */
	// End Line: 2240

SVECTOR delta = { 0 };
int doWheels = 1;

// [D] [T]
void UpdateCarPoints(CAR_COSMETICS *carCos)
{
	SVECTOR *groundCollPoints;
	SVECTOR *wheelPoints;
	int i;

	groundCollPoints = carCos->cPoints;
	wheelPoints = carCos->wheelDisp;

	i = 0;

	do {
		groundCollPoints->vx += delta.vx;
		groundCollPoints->vy -= delta.vy;
		groundCollPoints->vz += delta.vz;
		groundCollPoints++;
		i++;
	} while (i < 12);

	if (doWheels) 
	{
		i = 0;

		do {
			wheelPoints->vx += delta.vx;
			wheelPoints->vy -= delta.vy;
			wheelPoints->vz += delta.vz;
			wheelPoints++;
			i++;
		} while (i < 4);
	}

	carCos->cog.vx += delta.vx;
	carCos->cog.vy += delta.vy;
	carCos->cog.vz -= delta.vz;

	delta.vx = 0;
	delta.vy = 0;
	delta.vz = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ FixCarCos(struct CAR_COSMETICS *carCos /*$s0*/, int externalModelNumber /*$a1*/)
 // line 1106, offset 0x00056c24
	/* begin block 1 */
		// Start line: 1107
		// Start offset: 0x00056C24
		// Variables:
	// 		int current; // $v0
	/* end block 1 */
	// End offset: 0x00056CB8
	// End Line: 1130

	/* begin block 2 */
		// Start line: 5974
	/* end block 2 */
	// End Line: 5975

	/* begin block 3 */
		// Start line: 2212
	/* end block 3 */
	// End Line: 2213

	/* begin block 4 */
		// Start line: 5977
	/* end block 4 */
	// End Line: 5978

// [D] [T]
void FixCarCos(CAR_COSMETICS *carCos, int externalModelNumber)
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

			carCos->wheelDisp[i].vy -= 10;
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



// decompiled code
// original method signature: 
// void /*$ra*/ GlobalTimeStep()
 // line 1192, offset 0x00053c00
	/* begin block 1 */
		// Start line: 1194
		// Start offset: 0x00053C00
		// Variables:
	// 		int i; // $fp
	// 		int RKstep; // stack offset -84
	// 		int subframe; // stack offset -80
	// 		struct _CAR_DATA *c0; // $s0
	// 		static union RigidBodyState _tp[20]; // offset 0x0
	// 		static union RigidBodyState _d0[20]; // offset 0x410
	// 		static union RigidBodyState _d1[20]; // offset 0x820

		/* begin block 1.1 */
			// Start line: 1268
			// Start offset: 0x00053C6C
			// Variables:
		// 		struct _CAR_DATA *c0; // $t2
		// 		union RigidBodyState *st; // $t1

			/* begin block 1.1.1 */
				// Start line: 1283
				// Start offset: 0x00053D2C
				// Variables:
			// 		int s; // $v0
			/* end block 1.1.1 */
			// End offset: 0x00053D90
			// End Line: 1293

			/* begin block 1.1.2 */
				// Start line: 1301
				// Start offset: 0x00053E18
				// Variables:
			// 		long AV[4]; // stack offset -248
			// 		long delta_orientation[4]; // stack offset -232
			/* end block 1.1.2 */
			// End offset: 0x00053FF8
			// End Line: 1321
		/* end block 1.1 */
		// End offset: 0x00053FF8
		// End Line: 1322

		/* begin block 1.2 */
			// Start line: 1334
			// Start offset: 0x00054024
			// Variables:
		// 		union RigidBodyState *thisDelta; // stack offset -76

			/* begin block 1.2.1 */
				// Start line: 1340
				// Start offset: 0x00054038
				// Variables:
			// 		struct _CAR_DATA *c0; // $s4

				/* begin block 1.2.1.1 */
					// Start line: 1348
					// Start offset: 0x00054094
					// Variables:
				// 		union RigidBodyState *thisState_i; // $s6
				// 		int j; // stack offset -72

					/* begin block 1.2.1.1.1 */
						// Start line: 1193
						// Start offset: 0x000540EC
						// Variables:
					// 		union RigidBodyState *state; // $s6
					// 		union RigidBodyState *delta; // $a3
					// 		struct _CAR_DATA *cp; // $s4

						/* begin block 1.2.1.1.1.1 */
							// Start line: 1193
							// Start offset: 0x000540EC
							// Variables:
						// 		long AV[4]; // stack offset -248
						/* end block 1.2.1.1.1.1 */
						// End offset: 0x000540EC
						// End Line: 1193
					/* end block 1.2.1.1.1 */
					// End offset: 0x000540EC
					// End Line: 1193

					/* begin block 1.2.1.1.2 */
						// Start line: 1367
						// Start offset: 0x000542D8
						// Variables:
					// 		struct _CAR_DATA *c1; // $s3
					// 		union RigidBodyState *thisState_j; // $s0

						/* begin block 1.2.1.1.2.1 */
							// Start line: 1375
							// Start offset: 0x00054340
							// Variables:
						// 		int strength; // $s5
						// 		long centre0[4]; // stack offset -248
						// 		long centre1[4]; // stack offset -232
						// 		long normal[4]; // stack offset -216
						// 		long collisionpoint[4]; // stack offset -200

							/* begin block 1.2.1.1.2.1.1 */
								// Start line: 1378
								// Start offset: 0x00054340
								// Variables:
							// 		struct BOUND_BOX *bb1; // $a2
							// 		struct BOUND_BOX *bb2; // $a0
							/* end block 1.2.1.1.2.1.1 */
							// End offset: 0x00054440
							// End Line: 1409

							/* begin block 1.2.1.1.2.1.2 */
								// Start line: 1414
								// Start offset: 0x00054440
								// Variables:
							// 		int depth; // stack offset -88
							/* end block 1.2.1.1.2.1.2 */
							// End offset: 0x00054460
							// End Line: 1419

							/* begin block 1.2.1.1.2.1.3 */
								// Start line: 1419
								// Start offset: 0x00054460
								// Variables:
							// 		long lever0[4]; // stack offset -184
							// 		long lever1[4]; // stack offset -168
							// 		long torque[4]; // stack offset -152
							// 		long pointVel0[4]; // stack offset -136
							// 		long pointVel1[4]; // stack offset -120
							// 		int strikeVel; // stack offset -68

								/* begin block 1.2.1.1.2.1.3.1 */
									// Start line: 1419
									// Start offset: 0x00054460
									// Variables:
								// 		int is; // $v0
								// 		int wanted; // $v1
								/* end block 1.2.1.1.2.1.3.1 */
								// End offset: 0x00054460
								// End Line: 1419

								/* begin block 1.2.1.1.2.1.3.2 */
									// Start line: 1487
									// Start offset: 0x00054870
									// Variables:
								// 		struct VECTOR velocity; // stack offset -104

									/* begin block 1.2.1.1.2.1.3.2.1 */
										// Start line: 1506
										// Start offset: 0x00054924
										// Variables:
									// 		int debris1; // $s0
									// 		int debris2; // $s2
									/* end block 1.2.1.1.2.1.3.2.1 */
									// End offset: 0x0005497C
									// End Line: 1518
								/* end block 1.2.1.1.2.1.3.2 */
								// End offset: 0x0005497C
								// End Line: 1519

								/* begin block 1.2.1.1.2.1.3.3 */
									// Start line: 1526
									// Start offset: 0x000549BC
									// Variables:
								// 		int do1; // $a0
								// 		int do2; // $t5
								// 		int m1; // $t3
								// 		int m2; // $a1

									/* begin block 1.2.1.1.2.1.3.3.1 */
										// Start line: 1548
										// Start offset: 0x00054A50
										// Variables:
									// 		long force[4]; // stack offset -104
									// 		int strength1; // $a0
									// 		int twistY; // $t4
									/* end block 1.2.1.1.2.1.3.3.1 */
									// End offset: 0x00054CA0
									// End Line: 1577

									/* begin block 1.2.1.1.2.1.3.3.2 */
										// Start line: 1581
										// Start offset: 0x00054CA8
										// Variables:
									// 		long force[4]; // stack offset -104
									// 		int strength2; // $a1
									// 		int twistY; // $t2
									/* end block 1.2.1.1.2.1.3.3.2 */
									// End offset: 0x00054EDC
									// End Line: 1610
								/* end block 1.2.1.1.2.1.3.3 */
								// End offset: 0x00054EDC
								// End Line: 1611
							/* end block 1.2.1.1.2.1.3 */
							// End offset: 0x00054F58
							// End Line: 1618
						/* end block 1.2.1.1.2.1 */
						// End offset: 0x00054F58
						// End Line: 1619
					/* end block 1.2.1.1.2 */
					// End offset: 0x00054F58
					// End Line: 1620
				/* end block 1.2.1.1 */
				// End offset: 0x00054F7C
				// End Line: 1621
			/* end block 1.2.1 */
			// End offset: 0x00054F7C
			// End Line: 1622

			/* begin block 1.2.2 */
				// Start line: 1626
				// Start offset: 0x00054FA4
				// Variables:
			// 		struct _CAR_DATA *c0; // $a1

				/* begin block 1.2.2.1 */
					// Start line: 1630
					// Start offset: 0x00054FC4
					// Variables:
				// 		union RigidBodyState *st; // $t2
				// 		union RigidBodyState *tp; // $a0
				// 		union RigidBodyState *d0; // $a2
				// 		union RigidBodyState *d1; // $v1
				// 		int j; // $t1
				/* end block 1.2.2.1 */
				// End offset: 0x000550B0
				// End Line: 1646
			/* end block 1.2.2 */
			// End offset: 0x000550B0
			// End Line: 1647
		/* end block 1.2 */
		// End offset: 0x000550C8
		// End Line: 1648

		/* begin block 1.3 */
			// Start line: 1652
			// Start offset: 0x000550F4
			// Variables:
		// 		int carsDentedThisFrame; // $s2

			/* begin block 1.3.1 */
				// Start line: 1655
				// Start offset: 0x00055104

				/* begin block 1.3.1.1 */
					// Start line: 1656
					// Start offset: 0x00055104
					// Variables:
				// 		unsigned long *dst; // $a1
				/* end block 1.3.1.1 */
				// End offset: 0x00055104
				// End Line: 1656

				/* begin block 1.3.1.2 */
					// Start line: 1670
					// Start offset: 0x00055188
				/* end block 1.3.1.2 */
				// End offset: 0x00055198
				// End Line: 1673
			/* end block 1.3.1 */
			// End offset: 0x00055198
			// End Line: 1675
		/* end block 1.3 */
		// End offset: 0x000551EC
		// End Line: 1679
	/* end block 1 */
	// End offset: 0x000551EC
	// End Line: 1699

	/* begin block 2 */
		// Start line: 2396
	/* end block 2 */
	// End Line: 2397

	/* begin block 3 */
		// Start line: 2486
	/* end block 3 */
	// End Line: 2487

	/* begin block 4 */
		// Start line: 2487
	/* end block 4 */
	// End Line: 2488

	/* begin block 5 */
		// Start line: 2530
	/* end block 5 */
	// End Line: 2531

/* WARNING: Unknown calling convention yet parameter storage is locked */

int ghost_mode = 0;
int playerghost = 0;
int playerhitcopsanyway = 0;

// [D] [T]
void GlobalTimeStep(void)
{
	static union RigidBodyState _tp[MAX_CARS]; // offset 0x0
	static union RigidBodyState _d0[MAX_CARS]; // offset 0x410
	static union RigidBodyState _d1[MAX_CARS]; // offset 0x820

	int howHard;
	long tmp;
	RigidBodyState* thisState_i;
	RigidBodyState* thisState_j;
	RigidBodyState* thisDelta;
	BOUND_BOX *bb1;
	BOUND_BOX *bb2;
	_CAR_DATA* cp;
	_CAR_DATA* c1;
	RigidBodyState* st;
	RigidBodyState* tp;
	RigidBodyState* d0;
	RigidBodyState* d1;
	long AV[4];
	long delta_orientation[4];
	long normal[4];
	long collisionpoint[4];
	long lever0[4];
	long lever1[4];
	long torque[4];
	long pointVel0[4];
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

	StepCars();
	CheckCarToCarCollisions();

	i = 0;

	// step car forces (when no collisions with them)
	while (i < num_active_cars)
	{
		cp = active_car_list[i];

		st = &cp->st;

		if (cp->controlType == CONTROL_TYPE_PLAYER && playerghost != 0 && playerhitcopsanyway == 0) // [A]
			cp->hd.mayBeColliding = 0;

		// too many reads and writes, you know how to optimize it

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
			st->n.linearVelocity[1] = FixFloorSigned(st->n.linearVelocity[1] * 3, 2);

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

		if (cp->hd.mayBeColliding == 0) 
		{
			long* orient = st->n.orientation;

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

		i++;
	}

	subframe = 0;

	// do collision interactions
	do {
		RKstep = 0;

		do {
			i = 0;

			while (i < num_active_cars)
			{
				cp = active_car_list[i];

				// check collisions with buildings
				if (RKstep != 0 && (subframe & 1U) != 0 && cp->controlType == CONTROL_TYPE_PLAYER)
				{
					CheckScenaryCollisions(cp);
				}


				// check collisions with vehicles
				if (cp->hd.mayBeColliding != 0) 
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

					long* orient = thisState_i->n.orientation;

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

					if (cp->hd.mayBeColliding & 0x2) // [A] a litle skip for bbox checking
						j = 0;
					else
						j = 512;

					while (j < i)
					{
						c1 = active_car_list[j];

						if (RKstep > 0)
							thisState_j = &_tp[j];
						else
							thisState_j = &c1->st;

						if ((c1->hd.mayBeColliding & 0x2) && (c1->hd.speed != 0 || cp->hd.speed != 0))
						{
							bb1 = &bbox[cp->id];
							bb2 = &bbox[c1->id];

							if (bb2->x0 < bb1->x1 && bb2->z0 < bb1->z1 && bb1->x0 < bb2->x1 &&
								bb1->z0 < bb2->z1 && bb2->y0 < bb1->y1 && bb1->y0 < bb2->y1 &&
								CarCarCollision3(cp, c1, &depth, (VECTOR*)collisionpoint, (VECTOR*)normal))
							{
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

								howHard = FixFloorSigned(pointVel0[0], 8) * FixFloorSigned(normal[0], 5) +
									FixFloorSigned(pointVel0[1], 8) * FixFloorSigned(normal[1], 5) +
									FixFloorSigned(pointVel0[2], 8) * FixFloorSigned(normal[2], 5);

								if (howHard > 0 && RKstep > -1)
								{
									if (DamageCar3D(c1, (long(*)[4])lever1, howHard >> 1, cp))
										c1->ap.needsDenting = 1;

									if (DamageCar3D(cp, (long(*)[4])lever0, howHard >> 1, c1))
										cp->ap.needsDenting = 1;

									if (howHard > 0x32000)
									{
										if (cp->controlType == CONTROL_TYPE_CIV_AI)
											cp->ai.c.carMustDie = 1;

										if (c1->controlType == CONTROL_TYPE_CIV_AI)
											c1->ai.c.carMustDie = 1;
									}

									// wake up cops if they've ben touched
									if (numCopCars < 4 && numActiveCops < maxCopCars && GameType != GAME_GETAWAY)
									{
										if (cp->controlType == CONTROL_TYPE_PLAYER && IS_ROADBLOCK_CAR(c1))
										{
											InitCopState(c1, NULL);
											c1->ai.p.justPinged = 0;
										}

										if (c1->controlType == CONTROL_TYPE_PLAYER && IS_ROADBLOCK_CAR(cp))
										{
											InitCopState(cp, NULL);
											c1->ai.p.justPinged = 0;
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

								strikeVel += FixFloorSigned(howHard * 9, 2);

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
								if (c1InfiniteMass ||c2InfiniteMass)
									strikeVel = strikeVel * 10 >> 2;

								// apply force to car 0
								if (!c1InfiniteMass)
								{
									int twistY, strength1;

									if (cp->controlType == CONTROL_TYPE_PURSUER_AI && c1->controlType != CONTROL_TYPE_LEAD_AI && c1->hndType != 0)
										strength1 = FixFloorSigned(strikeVel * (7 - gCopDifficultyLevel), 3);
									else if (cp->controlType == CONTROL_TYPE_LEAD_AI && c1->hndType != 0)
										strength1 = FixFloorSigned(strikeVel * 5, 3);
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
										strength2 = FixFloorSigned(strikeVel * (7 - gCopDifficultyLevel), 3);
									else if (c1->controlType == CONTROL_TYPE_LEAD_AI && cp->hndType != 0)
										strength2 = FixFloorSigned(strikeVel * 5, 3);
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
						}

						j++;
					}
				}

				i++;
			}

			// update forces and rebuild matrix of the cars
			i = 0;

			while (i < num_active_cars)
			{
				cp = active_car_list[i];

				if (cp->hd.mayBeColliding != 0)
				{
					st = &cp->st;
					tp = &_tp[i];
					d0 = &_d0[i];
					d1 = &_d1[i];

					if (RKstep == 0)
					{
						j = 0;
						do {
							tp->v[j] = st->v[j] + (d0->v[j] >> 2);
							j++;
						} while (j < 13);

						RebuildCarMatrix(tp, cp);
					}
					else if (RKstep == 1)
					{
						j = 0;
						do {
							st->v[j] += d0->v[j] + d1->v[j] >> 3;
							j++;
						} while (j < 13);

						RebuildCarMatrix(st, cp);
					}
				}

				i++;
			}

			RKstep++;

		} while (RKstep < 2);

		subframe++;
	} while (subframe < 4);



	// second sub frame passed, update matrices and physics direction
	// dent cars - no more than 5 cars in per frame
	i = 0;
	carsDentedThisFrame = 0;

	while (i < num_active_cars)
	{
		cp = active_car_list[i];

		cp->hd.drawCarMat.m[0][0] = ~cp->hd.where.m[0][0];
		cp->hd.drawCarMat.m[0][1] = ~cp->hd.where.m[0][1];
		cp->hd.drawCarMat.m[0][2] = ~cp->hd.where.m[0][2];
		cp->hd.drawCarMat.m[1][0] = cp->hd.where.m[1][0];
		cp->hd.drawCarMat.m[1][1] = cp->hd.where.m[1][1];
		cp->hd.drawCarMat.m[1][2] = cp->hd.where.m[1][2];
		cp->hd.drawCarMat.m[2][0] = ~cp->hd.where.m[2][0];
		cp->hd.drawCarMat.m[2][1] = ~cp->hd.where.m[2][1];
		cp->hd.drawCarMat.m[2][2] = ~cp->hd.where.m[2][2];

		if (cp->ap.needsDenting != 0 && ((CameraCnt + i & 3U) == 0 || carsDentedThisFrame < 5))
		{
			DentCar(cp);

			cp->ap.needsDenting = 0;
			carsDentedThisFrame++;
		}

		i++;
		cp->hd.direction = ratan2(cp->hd.where.m[0][2], cp->hd.where.m[2][2]);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetShadowPoints(struct _CAR_DATA *c0 /*$s4*/)
 // line 1704, offset 0x000551ec
	/* begin block 1 */
		// Start line: 1705
		// Start offset: 0x000551EC
		// Variables:
	// 		int j; // $s2
	// 		struct CAR_COSMETICS *car_cos; // $v1
	// 		struct _sdPlane *surfacePtr; // stack offset -48

		/* begin block 1.1 */
			// Start line: 1718
			// Start offset: 0x000552A8
			// Variables:
		// 		struct SVECTOR disp; // stack offset -104
		// 		struct VECTOR pointPos; // stack offset -96
		// 		struct VECTOR surfaceNormal; // stack offset -80
		// 		struct VECTOR surfacePoint; // stack offset -64
		/* end block 1.1 */
		// End offset: 0x00055388
		// End Line: 1739
	/* end block 1 */
	// End offset: 0x000553CC
	// End Line: 1741

	/* begin block 2 */
		// Start line: 4674
	/* end block 2 */
	// End Line: 4675

	/* begin block 3 */
		// Start line: 4694
	/* end block 3 */
	// End Line: 4695

	/* begin block 4 */
		// Start line: 4700
	/* end block 4 */
	// End Line: 4701

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void SetShadowPoints(_CAR_DATA *c0)
{
	int i;
	SVECTOR disp;
	VECTOR pointPos;
	VECTOR surfaceNormal;
	VECTOR surfacePoint;
	CAR_COSMETICS* car_cos;

	_sdPlane *surfacePtr;
	surfacePtr = NULL;

	gte_SetRotMatrix(&c0->hd.where);
	gte_SetTransMatrix(&c0->hd.where);

	i = 0;
	car_cos = &car_cosmetics[c0->ap.model];

	do {
		disp = car_cos->cPoints[i];

		/* // [A] No point to keep this cheat
		if (cheats.MiniCars != 0) 
		{
			disp._0_4_ = CONCAT22((short)((int)disp._0_4_ >> 0x12), disp.vx >> 2);
			disp._4_4_ = disp._4_4_ & 0xffff0000 | (uint)(ushort)(disp.vz >> 2);
		}*/

		gte_ldv0(&disp);

		gte_rtv0tr();

		gte_stlvnl(&pointPos);

		//static int hSubShad = 0;
		//hSubShad = 0;

		FindSurfaceD2(&pointPos, &surfaceNormal, &surfacePoint, &surfacePtr);

		c0->hd.shadowPoints[i].vx = surfacePoint.vx;
		c0->hd.shadowPoints[i].vy = surfacePoint.vy;
		c0->hd.shadowPoints[i].vz = surfacePoint.vz;

		//if (hSubShad != 0)
		//	c0->hd.shadowPoints[i].vy += 1;

		i++;
	} while (i < 4);
}



// decompiled code
// original method signature: 
// void /*$ra*/ LongQuaternion2Matrix(long (*qua)[4] /*$a0*/, struct MATRIX *m /*$a1*/)
 // line 1753, offset 0x000553cc
	/* begin block 1 */
		// Start line: 1754
		// Start offset: 0x000553CC
		// Variables:
	// 		int xx; // $t3
	// 		int xy; // $a3
	// 		int xz; // $t2
	// 		int xw; // $t0
	// 		int yy; // $t7
	// 		int yz; // $a2
	// 		int yw; // $t5
	// 		int zz; // $v1
	// 		int zw; // $a0
	/* end block 1 */
	// End offset: 0x000554F0
	// End Line: 1778

	/* begin block 2 */
		// Start line: 4819
	/* end block 2 */
	// End Line: 4820

	/* begin block 3 */
		// Start line: 4832
	/* end block 3 */
	// End Line: 4833

	/* begin block 4 */
		// Start line: 4833
	/* end block 4 */
	// End Line: 4834

// [D] [T]
void LongQuaternion2Matrix(long(*qua)[4], MATRIX *m)
{
	int xx;
	int xy;
	int xz;
	int xw;
	int yy;
	int yz;
	int yw;
	int zz;
	int zw;

	int qy;
	int qx;
	int qw;
	int qz;

	qx = (*qua)[0];
	qy = (*qua)[1];
	qz = (*qua)[2];
	qw = (*qua)[3];

	yy = FixHalfRound(qy * qy, 11);
	zz = FixHalfRound(qz * qz, 11);
	xx = FixHalfRound(qx * qx, 11);
	zw = FixHalfRound(qz * qw, 11);
	xy = FixHalfRound(qx * qy, 11);
	xz = FixHalfRound(qx * qz, 11);
	yw = FixHalfRound(qy * qw, 11);
	xw = FixHalfRound(qx * qw, 11);
	yz = FixHalfRound(qy * qz, 11);

	m->m[0][0] = 4096 - (yy + zz);
	m->m[1][1] = 4096 - (xx + zz);
	m->m[2][2] = 4096 - (xx + yy);
	m->m[0][1] = xy - zw;
	m->m[0][2] = xz + yw;
	m->m[1][0] = xy + zw;
	m->m[2][0] = xz - yw;
	m->m[1][2] = yz - xw;
	m->m[2][1] = yz + xw;
}



// decompiled code
// original method signature: 
// void /*$ra*/ initOBox(struct _CAR_DATA *cp /*$a2*/)
 // line 1802, offset 0x000554f0
	/* begin block 1 */
		// Start line: 1803
		// Start offset: 0x000554F0
		// Variables:
	// 		struct SVECTOR *boxDisp; // $a0

		/* begin block 1.1 */
			// Start line: 1803
			// Start offset: 0x000554F0
			// Variables:
		// 		int length; // $a1
		/* end block 1.1 */
		// End offset: 0x000556E0
		// End Line: 1842
	/* end block 1 */
	// End offset: 0x000556E0
	// End Line: 1844

	/* begin block 2 */
		// Start line: 4994
	/* end block 2 */
	// End Line: 4995

	/* begin block 3 */
		// Start line: 5019
	/* end block 3 */
	// End Line: 5020

// [D] [T]
void initOBox(_CAR_DATA *cp)
{
	SVECTOR boxDisp;

	short length;

	gte_SetRotMatrix(&cp->hd.where);
	gte_SetTransMatrix(&cp->hd.where);

	boxDisp.vx = -cp->ap.carCos->cog.vx;
	boxDisp.vy = -cp->ap.carCos->cog.vy;
	boxDisp.vz = -cp->ap.carCos->cog.vz;

	gte_ldv0(&boxDisp);
	gte_rtv0tr();

	if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
	{
		length = FixFloorSigned(cp->ap.carCos->colBox.vx * 14, 4);
		cp->hd.oBox.length[0] = length;
	}
	else 
	{
		length = cp->ap.carCos->colBox.vx;
		cp->hd.oBox.length[0] = length;
	}

	gte_stlvnl(&cp->hd.oBox.location);

	VECTOR svx = { length, 0 ,0 };
	VECTOR svy = { 0, cp->ap.carCos->colBox.vy ,0 };
	VECTOR svz = { 0, 0 ,cp->ap.carCos->colBox.vz };

	gte_ldlvl(&svx);

	gte_rtir();
	cp->hd.oBox.length[1] = cp->ap.carCos->colBox.vy;
	gte_stsv(&cp->hd.oBox.radii[0]);

	gte_ldlvl(&svy);
	gte_rtir();
	cp->hd.oBox.length[2] = cp->ap.carCos->colBox.vz;
	gte_stsv(&cp->hd.oBox.radii[1]);

	gte_ldlvl(&svz);
	gte_rtir();
	gte_stsv(&cp->hd.oBox.radii[2]);
}



// decompiled code
// original method signature: 
// void /*$ra*/ RebuildCarMatrix(union RigidBodyState *st /*$a2*/, struct _CAR_DATA *cp /*$s0*/)
 // line 1854, offset 0x00056ae4
	/* begin block 1 */
		// Start line: 1855
		// Start offset: 0x00056AE4

		/* begin block 1.1 */
			// Start line: 1855
			// Start offset: 0x00056AE4
			// Variables:
		// 		int sm; // $v1

			/* begin block 1.1.1 */
				// Start line: 1859
				// Start offset: 0x00056B8C
				// Variables:
			// 		int osm; // $v0
			/* end block 1.1.1 */
			// End offset: 0x00056C00
			// End Line: 1859
		/* end block 1.1 */
		// End offset: 0x00056C00
		// End Line: 1859
	/* end block 1 */
	// End offset: 0x00056C24
	// End Line: 1862

	/* begin block 2 */
		// Start line: 3708
	/* end block 2 */
	// End Line: 3709

// [D] [T]
void RebuildCarMatrix(RigidBodyState *st, _CAR_DATA *cp)
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
	
	LongQuaternion2Matrix((long(*)[4])st->n.orientation, &cp->hd.where);

	initOBox(cp);
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepCarPhysics(struct _CAR_DATA *cp /*$a2*/)
 // line 1875, offset 0x00056a0c
	/* begin block 1 */
		// Start line: 1876
		// Start offset: 0x00056A0C
		// Variables:
	// 		struct _HANDLING_TYPE *hp; // $v0
	/* end block 1 */
	// End offset: 0x00056A64
	// End Line: 1899

	/* begin block 2 */
		// Start line: 3750
	/* end block 2 */
	// End Line: 3751

// [D] [T]
void StepCarPhysics(_CAR_DATA *cp)
{
	_HANDLING_TYPE *hp;
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

	frontWheelSpeed = FixFloorSigned(cp->hd.wheel_speed, 8);

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



// decompiled code
// original method signature: 
// void /*$ra*/ InitialiseCarHandling()
 // line 1911, offset 0x00056a6c
	/* begin block 1 */
		// Start line: 6067
	/* end block 1 */
	// End Line: 6068

	/* begin block 2 */
		// Start line: 6072
	/* end block 2 */
	// End Line: 6073

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitialiseCarHandling(void)
{
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckCarToCarCollisions()
 // line 1930, offset 0x000556e0
	/* begin block 1 */
		// Start line: 1932
		// Start offset: 0x000556E0
		// Variables:
	// 		struct _CAR_DATA *cp; // $t2
	// 		struct BOUND_BOX *bp; // $t1
	// 		struct BOUND_BOX *bb1; // $t0
	// 		struct BOUND_BOX *bb2; // $a1
	// 		int lbod; // $v1
	// 		int wbod; // $a0
	// 		int hbod; // $t0
	// 		struct SVECTOR *colBox; // $a1
	// 		int loop1; // $t4
	// 		int loop2; // $a3

		/* begin block 1.1 */
			// Start line: 1947
			// Start offset: 0x0005570C
			// Variables:
		// 		int wx; // $v1
		// 		int wz; // $a2
		/* end block 1.1 */
		// End offset: 0x0005592C
		// End Line: 1982
	/* end block 1 */
	// End offset: 0x00055A94
	// End Line: 2014

	/* begin block 2 */
		// Start line: 5188
	/* end block 2 */
	// End Line: 5189

	/* begin block 3 */
		// Start line: 5190
	/* end block 3 */
	// End Line: 5191

	/* begin block 4 */
		// Start line: 5277
	/* end block 4 */
	// End Line: 5278

	/* begin block 5 */
		// Start line: 5278
	/* end block 5 */
	// End Line: 5279

/* WARNING: Unknown calling convention yet parameter storage is locked */


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
	BOUND_BOX *bb2;
	BOUND_BOX *bb1;
	_CAR_DATA *cp;
	SVECTOR *colBox;

	cp = car_data;

	if (ghost_mode == 1)
		return;

	bb = bbox;
	loop1 = 0;

	// build boxes
	do {
		if (cp->controlType == CONTROL_TYPE_NONE) // [A] required as game crashing
		{
			cp++;
			bb++;
			loop1++;
			continue;
		}

		colBox = &cp->ap.carCos->colBox;

		hbod = colBox->vy;
		lbod = colBox->vz * 9;
		wbod = colBox->vx * 9;

		sx = cp->hd.where.m[0][0] * FixFloorSigned(wbod, 3);
		sz = cp->hd.where.m[0][2] * FixFloorSigned(lbod, 3);

		fx = cp->hd.where.m[2][0] * FixFloorSigned(wbod, 3);
		fz = cp->hd.where.m[2][2] * FixFloorSigned(lbod, 3);

		xx = FIXEDH(ABS(sz) + ABS(sx)) + hbod;
		zz = FIXEDH(ABS(fz) + ABS(fx)) + hbod;

		bb->x0 = FixFloorSigned(cp->hd.where.t[0] - xx, 4);
		bb->z0 = FixFloorSigned(cp->hd.where.t[2] - zz, 4);
		bb->x1 = FixFloorSigned(cp->hd.where.t[0] + xx, 4);
		bb->z1 = FixFloorSigned(cp->hd.where.t[2] + zz, 4);

		if (cp->st.n.linearVelocity[0] < 0)
			bb->x0 = FixFloorSigned(cp->hd.where.t[0] - xx, 4) + FixFloorSigned(FIXEDH(cp->st.n.linearVelocity[0]), 3);
		else
			bb->x1 = FixFloorSigned(cp->hd.where.t[0] + xx, 4) + FixFloorSigned(FIXEDH(cp->st.n.linearVelocity[0]), 3);

		if (cp->st.n.linearVelocity[2] < 0)
			bb->z0 = bb->z0 + FixFloorSigned(FIXEDH(cp->st.n.linearVelocity[2]), 3);
		else
			bb->z1 = bb->z1 + FixFloorSigned(FIXEDH(cp->st.n.linearVelocity[2]), 3);

		// [A] 2400 for box size - bye bye collision check performance under bridges
		bb->y0 = FixFloorSigned(cp->hd.where.t[1] - colBox->vy * 2 /* - 2400*/, 4);
		bb->y1 = FixFloorSigned(cp->hd.where.t[1] + colBox->vy * 4 /* + 2400*/, 4);

		if (cp->hndType == 0)
			cp->hd.mayBeColliding = 0x1;

		loop1++;
		bb++;
		cp++;
	} while (loop1 < MAX_CARS);

	bb1 = bbox;
	loop1 = 0;

	// check boxes intersection with each other
	do {
		bb2 = bb1 + 1;
		loop2 = loop1 + 1;

		while (loop2 < MAX_CARS)
		{
			if (bb2->x0 < bb1->x1 && bb2->z0 < bb1->z1 && bb1->x0 < bb2->x1 &&
				bb1->z0 < bb2->z1 && bb2->y0 < bb1->y1 && bb1->y0 < bb2->y1 &&
				(loop1 == 0 || car_data[loop1].controlType != CONTROL_TYPE_NONE) && car_data[loop2].controlType != CONTROL_TYPE_NONE)
			{
				car_data[loop1].hd.mayBeColliding = car_data[loop2].hd.mayBeColliding = 0x2;
			}

			loop2++;
			bb2++;
		};

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



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessCarPad(struct _CAR_DATA *cp /*$s0*/, unsigned long pad /*$s3*/, char PadSteer /*$s4*/, char use_analogue /*$s5*/)
 // line 2027, offset 0x00055a9c
	/* begin block 1 */
		// Start line: 2028
		// Start offset: 0x00055A9C
		// Variables:
	// 		int player_id; // $s1

		/* begin block 1.1 */
			// Start line: 2158
			// Start offset: 0x00055CD8
			// Variables:
		// 		int int_steer; // $v0
		// 		int analog_angle; // $v1
		/* end block 1.1 */
		// End offset: 0x00055D90
		// End Line: 2180

		/* begin block 1.2 */
			// Start line: 2260
			// Start offset: 0x00055EF0
			// Variables:
		// 		int rws; // $v0
		/* end block 1.2 */
		// End offset: 0x00055F80
		// End Line: 2270

		/* begin block 1.3 */
			// Start line: 2282
			// Start offset: 0x00055FE4
			// Variables:
		// 		int playerCar; // $v0
		// 		int dist; // $a0
		// 		int dx; // $a0
		// 		int dz; // $v0
		/* end block 1.3 */
		// End offset: 0x00056080
		// End Line: 2299

		/* begin block 1.4 */
			// Start line: 2303
			// Start offset: 0x00056090
			// Variables:
		// 		int targetCarId; // $v1

			/* begin block 1.4.1 */
				// Start line: 2320
				// Start offset: 0x000560D4
				// Variables:
			// 		struct _CAR_DATA *tp; // $a1
			// 		int cx; // $v1
			// 		int cz; // $v0
			// 		int chase_square_dist; // $v0

				/* begin block 1.4.1.1 */
					// Start line: 2327
					// Start offset: 0x0005610C
					// Variables:
				// 		int averagePower; // $a0
				/* end block 1.4.1.1 */
				// End offset: 0x00056148
				// End Line: 2329
			/* end block 1.4.1 */
			// End offset: 0x00056258
			// End Line: 2340
		/* end block 1.4 */
		// End offset: 0x00056258
		// End Line: 2342
	/* end block 1 */
	// End offset: 0x000562AC
	// End Line: 2375

	/* begin block 2 */
		// Start line: 5531
	/* end block 2 */
	// End Line: 5532

// [D] [T]
void ProcessCarPad(_CAR_DATA *cp, ulong pad, char PadSteer, char use_analogue)
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
		if ((pad & 0x1010) == 0x1010 && player_id > -1)
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
			pad = 0x10;

			// apply brakes
			if (cp->hd.wheel_speed > 0x9000)
				pad = 0x80;

			int_steer = 0;
			use_analogue = 1;
		}

		// turn of horning
		if (player_id > -1)
		{
			if (CarHasSiren(cp->ap.model) == 0)
				player[player_id].horn.on = (pad >> 3) & 1;
			else if((cp->lastPad & 8U) == 0 && (pad & 8) != 0)
				player[player_id].horn.on ^= 8;
		}
	}

	if (cp->hd.autoBrake > 90)
		cp->hd.autoBrake = 90;

	// handle burnouts or handbrake
	if ((pad & 0x10) == 0)
	{
		cp->handbrake = 0;

		if ((pad & 0x20) == 0)
			cp->wheelspin = 0;
		else 
			cp->wheelspin = 1;

		// continue without burnout
		if (cp->wheelspin != 0 && cp->hd.wheel_speed > 0x6e958)
		{
			cp->wheelspin = 0;
			pad |= 0x40;
		}
	}
	else 
	{
		cp->handbrake = 1;
	}

	// handle steering
	if (use_analogue == 0)
	{
		if ((pad & 4) == 0)
		{
			// regular steer
			if((pad & 0x2000) != 0)
			{
				cp->wheel_angle += 32;

				if (cp->wheel_angle > 352)
					cp->wheel_angle = 352;
			}
			
			if ((pad & 0x8000) != 0)
			{
				cp->wheel_angle -= 32;

				if (cp->wheel_angle < -352)
					cp->wheel_angle = -352;
			}
		}
		else
		{
			// fast steer
			if ((pad & 0x2000) != 0)
			{
				cp->wheel_angle += 64;

				if (cp->wheel_angle > 511)
					cp->wheel_angle = 511;
			}

			if ((pad & 0x8000) != 0)
			{
				cp->wheel_angle -= 64;

				if (cp->wheel_angle < -511)
					cp->wheel_angle = -511;
			}
		}

		if ((pad & 0xa000) != 0) 
			cp->hd.autoBrake++;
		else
			cp->hd.autoBrake = 0;
	}
	else 
	{
		if ((pad & 4) == 0) 
		{
			int_steer *= (int_steer * int_steer) / 80;
			analog_angle = ((long long)int_steer * 0x66666667) >> 32;		// int_steer * 0.4
		}
		else 
		{
			int_steer *= (int_steer * int_steer) / 60;
			analog_angle =  ((long long)int_steer * 0x88888889) >> 32;		// int_steer * 0.6
		}

		analog_angle = (analog_angle >> 5) - (int_steer >> 0x1f);

		cp->wheel_angle = analog_angle & 0xfffc;

		if (analog_angle + 270U < 541)
			cp->hd.autoBrake = 0;
		else
			cp->hd.autoBrake++;
	}

	// center steering
	if ((pad & 0xa000) == 0)
	{
		if (cp->wheel_angle < -64) 
			cp->wheel_angle += 64;
		else if (cp->wheel_angle < 65)
			cp->wheel_angle = 0;
		else
			cp->wheel_angle -= 64;
	}

	cp->thrust = 0;

	if (gTimeInWater != 0)
	{
		if ((pad & 0x80) != 0) 
		{
			int rws;

			// brakes
			rws = FIXEDH(FixFloorSigned(cp->hd.wheel_speed * 1500, 10));

			if (-rws < 23)
				rws = -5000;
			else
				rws = ((rws + 278) * -4778) >> 8;

			cp->thrust = FIXEDH(cp->ap.carCos->powerRatio * rws);
		}
		else if ((pad & 0x40) != 0)
		{
			if (cp->hndType == 5)
			{
				// rubber band freeroamer.
				// accelerate faster if closer to player
				int dx, dz, dist;

				dx = car_data[player[0].playerCarId].hd.where.t[0] - cp->hd.where.t[0] >> 10;
				dz = car_data[player[0].playerCarId].hd.where.t[2] - cp->hd.where.t[2] >> 10;

				dist = dx * dx + dz * dz;

				if (dist < 41)
				{
					if (dist < 21)
					{
						if (dist > 9)
							cp->thrust = 4900;
						else
							cp->thrust = 6000;
					}
					else
						cp->thrust = 4000;
				}
				else
					cp->thrust = 3000;
			}
			else
			{
				cp->thrust = FIXEDH(cp->ap.carCos->powerRatio * 4915);
			}

			if (cp->controlType == CONTROL_TYPE_PLAYER)
			{
				_CAR_DATA* tp;
				int targetCarId, cx, cz, chase_square_dist;

				targetCarId = -1;

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

					if (chase_square_dist < 21)
					{
						if (chase_square_dist < 7)
							cp->thrust = (cp->thrust * 6700) / 7000;
						else 
							cp->thrust = (cp->thrust * 7400) / 7000;
					}
					else
						cp->thrust = (cp->thrust * 8000) / 7000;
				}
			}

			if (cp->hndType == 0 && cp->hd.changingGear != 0)
				cp->thrust = 1;
		}
	}

	cp->lastPad = pad;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitSkidding()
 // line 2389, offset 0x00056cb8
	/* begin block 1 */
		// Start line: 2390
		// Start offset: 0x00056CB8
		// Variables:
	// 		int i; // $a0
	/* end block 1 */
	// End offset: 0x00056CEC
	// End Line: 2395

	/* begin block 2 */
		// Start line: 8794
	/* end block 2 */
	// End Line: 8795

	/* begin block 3 */
		// Start line: 4778
	/* end block 3 */
	// End Line: 4779

	/* begin block 4 */
		// Start line: 8796
	/* end block 4 */
	// End Line: 8797

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitSkidding(void)
{
	int i;

	i = 2;
	do {
		player[i].wheelnoise.sound = -1;
		player[i].wheelnoise.chan = -1;
		player[i].skidding.sound = -1;
		player[i].skidding.chan = -1;
		i--;
	} while (i >= 0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ TerminateSkidding(int player_id /*$a0*/)
 // line 2397, offset 0x000562ac
	/* begin block 1 */
		// Start line: 6265
	/* end block 1 */
	// End Line: 6266

	/* begin block 2 */
		// Start line: 6288
	/* end block 2 */
	// End Line: 6289

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



// decompiled code
// original method signature: 
// void /*$ra*/ CheckCarEffects(struct _CAR_DATA *cp /*$s2*/, int player_id /*$s3*/)
 // line 2414, offset 0x00056350
	/* begin block 1 */
		// Start line: 2415
		// Start offset: 0x00056350
		// Variables:
	// 		int skidsound; // $s1
	// 		int cnt; // $a0
	// 		int wheels_on_ground; // $s5
	// 		char lay_down_tracks; // $s7
	// 		char desired_skid; // $a1
	// 		char desired_wheel; // $a1

		/* begin block 1.1 */
			// Start line: 2500
			// Start offset: 0x000565E8
			// Variables:
		// 		int pitch; // $v0
		/* end block 1.1 */
		// End offset: 0x00056644
		// End Line: 2504

		/* begin block 1.2 */
			// Start line: 2507
			// Start offset: 0x00056660
			// Variables:
		// 		int wnse; // $a0
		/* end block 1.2 */
		// End offset: 0x000566A8
		// End Line: 2510

		/* begin block 1.3 */
			// Start line: 2533
			// Start offset: 0x000567A8
			// Variables:
		// 		int pitch; // $t0
		/* end block 1.3 */
		// End offset: 0x00056810
		// End Line: 2537

		/* begin block 1.4 */
			// Start line: 2546
			// Start offset: 0x00056840
		/* end block 1.4 */
		// End offset: 0x00056868
		// End Line: 2550
	/* end block 1 */
	// End offset: 0x000568AC
	// End Line: 2560

	/* begin block 2 */
		// Start line: 6322
	/* end block 2 */
	// End Line: 6323

	/* begin block 3 */
		// Start line: 6325
	/* end block 3 */
	// End Line: 6326

char rear_only = 0;
char continuous_track = 0;
int last_track_state = -1;

// [D] [T]
void CheckCarEffects(_CAR_DATA *cp, int player_id)
{
	int channel;
	int sample;

	int skidsound;
	int cnt;
	int wheels_on_ground;
	char lay_down_tracks;
	char desired_skid;
	char desired_wheel;

	wheels_on_ground = 0;
	lay_down_tracks = 0;

	if (cp->controlType != CONTROL_TYPE_PLAYER && cp->controlType != CONTROL_TYPE_LEAD_AI && cp->controlType != CONTROL_TYPE_CUTSCENE)
	{
		TerminateSkidding(player_id);
		return;
	}

	// PHYSICS! jumping effects, also make car nose down
	jump_debris(cp);

	// [A] do hubcaps here
	HandlePlayerHubcaps(player_id);

	cnt = 0;
	do {
		if (cp->hd.wheel[cnt].susCompression != 0)
			wheels_on_ground = 1;

		cnt++;
	} while (cnt < 4);

	skidsound = 0;

	// make tyre tracks and skid sound if needed
	if (wheels_on_ground) 
	{
		if (ABS(cp->hd.rear_vel) > 11100 || cp->wheelspin)
		{
			rear_only = 1;
			lay_down_tracks = true;

			if (cp->wheelspin == 0)
				skidsound = (ABS(cp->hd.rear_vel) - 11100) / 2 + 1;
			else
				skidsound = 13000;

			if (skidsound > 13000)
				skidsound = 13000;
		}
		else if (ABS(cp->hd.front_vel) > 11100)
		{
			rear_only = 0;
			lay_down_tracks = true;
		}
	}

	desired_skid = -1;

	// should be on asphalt
	if (skidsound != 0 && ((cp->hd.wheel[1].surface & 0x80) == 0 || (cp->hd.wheel[3].surface & 0x80) == 0))
	{
		if (gWeather - 1U < 2)
			desired_skid = -1;
		else
			desired_skid = 11;
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
			channel = StartSound(-1, 1, player[player_id].skidding.sound, skidsound - 10000, 0x1000);

			player[player_id].skidding.chan = channel;
			LockChannel(channel);

			if (NumPlayers > 1 && NoPlayerControl == 0) 
				SetPlayerOwnsChannel(player[player_id].skidding.chan, player_id);
		}
	}

	// update skidding sound
	if (player[player_id].skidding.sound > -1 && player[player_id].skidding.chan > -1)
	{
		SetChannelPosition3(player[player_id].skidding.chan,
			(VECTOR*)cp->hd.where.t,
			cp->st.n.linearVelocity,
			(((skidsound - 10000) * 3) / 4) - 5000,
			(skidsound * 1024) / 13000 + 3072 + player_id * 8, 0);
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
				desired_wheel = wnse + 12;
			else
				desired_wheel = -1;
		}
		else
			desired_wheel = 13;
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
			channel = StartSound(-1, 1, player[player_id].wheelnoise.sound, -200, 4096);

			player[player_id].wheelnoise.chan = channel;
			LockChannel(channel);

			if (NumPlayers > 1 && NoPlayerControl == 0)
				SetPlayerOwnsChannel(player[player_id].wheelnoise.chan, player_id);
		}
	}

	// update wheel noise
	if (player[player_id].wheelnoise.sound > -1 && player[player_id].wheelnoise.chan > -1)
	{
		int pitch, spd;

		spd = cp->hd.speed;
		if (spd > 100)
			spd = 100;

		pitch = spd * 27;

		if (pitch > 3584)
			pitch = 3584;

		SetChannelPosition3(player[player_id].wheelnoise.chan, 
							(VECTOR *)cp->hd.where.t, cp->st.n.linearVelocity, 
							spd * 50-10000,
							pitch + player_id * 8, 0);
	}

	player[player_id].onGrass = 0;

	GetTyreTrackPositions(cp, player_id);

	// make tyre tracks
	if (lay_down_tracks) 
	{
		continuous_track = last_track_state == rear_only;

		AddTyreTrack(player_id * 2, (player_id < 2), player_id);
		AddTyreTrack(player_id * 2 + 1, (player_id < 2), player_id);

		last_track_state = rear_only;
	}
	else
	{
		last_track_state = -1;
	}

	SetTyreTrackOldPositions(player_id);
}



// decompiled code
// original method signature: 
// void /*$ra*/ jump_debris(struct _CAR_DATA *cp /*$s1*/)
 // line 2575, offset 0x000568d8
	/* begin block 1 */
		// Start line: 2576
		// Start offset: 0x000568D8
		// Variables:
	// 		int count; // $a1

		/* begin block 1.1 */
			// Start line: 2599
			// Start offset: 0x00056964
			// Variables:
		// 		struct VECTOR position; // stack offset -48
		// 		struct VECTOR velocity; // stack offset -32
		/* end block 1.1 */
		// End offset: 0x000569F8
		// End Line: 2603
	/* end block 1 */
	// End offset: 0x000569F8
	// End Line: 2604

	/* begin block 2 */
		// Start line: 6655
	/* end block 2 */
	// End Line: 6656

	/* begin block 3 */
		// Start line: 6657
	/* end block 3 */
	// End Line: 6658

char DebrisTimer = 0;

// [D] [T]
void jump_debris(_CAR_DATA *cp)
{
	WHEEL *wheel;
	int count;
	VECTOR position;
	VECTOR velocity;

	count = 0;
	wheel = cp->hd.wheel;

	do {
		
		if (wheel->susCompression != 0) 
		{
			DebrisTimer = 0;
			cp->wasOnGround = 1;
			return;
		}

		wheel++;
		count++;
	} while (count < 4);

	if (cp->wasOnGround == 1) 
	{
		cp->wasOnGround = 0;
		DebrisTimer = 80;

		nose_down(cp);
	}

	if (DebrisTimer != 0 && --DebrisTimer < 75)
	{
		memset(&velocity, 0, sizeof(velocity));

		velocity.vx = cp->hd.where.t[0] + ((rand() & 0x1ff) - 0x100);
		velocity.vy = 200 - cp->hd.where.t[1];

		position.vz = cp->hd.where.t[2] + ((rand() & 0x1ff) - 0x100);
		position.vx = velocity.vx;
		position.vy = velocity.vy;
		position.pad = velocity.pad;

		velocity.vz = position.vz;

		memset(&velocity, 0, sizeof(velocity));
		Setup_Debris(&position, &velocity, 5, 0xb);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ nose_down(struct _CAR_DATA *cp /*$a0*/)
 // line 2607, offset 0x00056a74
	/* begin block 1 */
		// Start line: 7459
	/* end block 1 */
	// End Line: 7460

	/* begin block 2 */
		// Start line: 7461
	/* end block 2 */
	// End Line: 7462

// [D] [T]
void nose_down(_CAR_DATA *cp)
{
	cp->st.n.angularVelocity[0] += cp->hd.where.m[0][0] * 50;
	cp->st.n.angularVelocity[1] += cp->hd.where.m[1][0] * 50;
	cp->st.n.angularVelocity[2] += cp->hd.where.m[2][0] * 50;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetPlayerId(struct _CAR_DATA *cp /*$a0*/)
 // line 2664, offset 0x00056cec
	/* begin block 1 */
		// Start line: 2665
		// Start offset: 0x00056CEC
		// Variables:
	// 		int i; // $a1
	// 		int p_id; // $a3
	/* end block 1 */
	// End offset: 0x00056D54
	// End Line: 2669

	/* begin block 2 */
		// Start line: 9334
	/* end block 2 */
	// End Line: 9335

	/* begin block 3 */
		// Start line: 9345
	/* end block 3 */
	// End Line: 9346

// [D] [T]
int GetPlayerId(_CAR_DATA *cp)
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





