#include "THISDUST.H"
#include "HANDLING.H"
#include "COSMETIC.H"
#include "MISSION.H"
#include "DR2ROADS.H"
#include "TEXTURE.H"
#include "CARS.H"
#include "MAIN.H"
#include "WHEELFORCES.H"
#include "OBJCOLL.H"
#include "DENTING.H"
#include "CAMERA.H"
#include "FELONY.H"
#include "MISSION.H"
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

#include "GTEREG.H"
#include "INLINE_C.H"
#include "STRINGS.H"

#include <stdlib.h>

#define COLLISION_DEBUG

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

#include "CONVERT.H"

// [D]
void InitCarPhysics(_CAR_DATA *cp, long(*startpos)[4], int direction)
{
	char cVar1;
	int iVar2;
	char cVar3;
	uint uVar4;
	int iVar5;

	uVar4 = cp->ap.model;
	iVar5 = (int)car_cosmetics[uVar4].wheelDisp[0].vz + (int)car_cosmetics[uVar4].wheelDisp[1].vz;
	iVar2 = iVar5 / 5;
	if (iVar5 < 0) {
		iVar5 = iVar5 + 0x1f;
	}
	cp->hd.direction = direction;

	cp->hd.autoBrake = 0;

	cp->st.n.orientation[0] = -rcossin_tbl[(direction & 0xffeU) + 1] * iVar2 / 4096;
	cp->st.n.orientation[1] = rcossin_tbl[direction & 0xffeU];
	cp->st.n.orientation[2] = rcossin_tbl[direction & 0xffeU] * iVar2 / 4096;
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
	cp->hd.drawCarMat.m[0][2] = cp->hd.where.m[0][2] ^ 0xFFFF;
	cp->hd.drawCarMat.m[1][0] = cp->hd.where.m[1][0];
	cp->hd.drawCarMat.m[1][1] = cp->hd.where.m[1][1];
	cp->hd.drawCarMat.m[1][2] = cp->hd.where.m[1][2];
	cp->hd.drawCarMat.m[2][0] = ~cp->hd.where.m[2][0];
	cp->hd.drawCarMat.m[2][1] = ~cp->hd.where.m[2][1];
	cp->hd.drawCarMat.m[2][2] = cp->hd.where.m[2][2] ^ 0xFFFF;
	
	cVar3 = (iVar5 >> 5);
	cVar1 = 14 - cVar3;
	
	cVar3 = cVar3 + 14;

	cp->hd.wheel[0].susCompression = cVar1;
	cp->hd.wheel[1].susCompression = cVar3;
	cp->hd.wheel[2].susCompression = cVar1;
	cp->hd.wheel[3].susCompression = cVar3;
	
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

// [D]
void TempBuildHandlingMatrix(_CAR_DATA *cp, int init)
{
	int iVar1;
	int iVar2;
	uint uVar3;
	int iVar4;

	uVar3 = cp->ap.model;
	iVar1 = (car_cosmetics[uVar3].wheelDisp[0].vz + car_cosmetics[uVar3].wheelDisp[1].vz) / 5;

	if (init == 1) 
	{
		cp->st.n.fposition[0] = cp->hd.where.t[0] << 4;
		cp->st.n.fposition[1] = cp->hd.where.t[1] << 4;
		cp->st.n.fposition[2] = cp->hd.where.t[2] << 4;
	}

	uVar3 = cp->hd.direction & 0xffe;
	cp->st.n.orientation[0] = (-rcossin_tbl[uVar3 + 1] * iVar1) / 4096;
	cp->st.n.orientation[1] = rcossin_tbl[uVar3];
	cp->st.n.orientation[2] = (rcossin_tbl[uVar3] * iVar1) / 4096;
	cp->st.n.orientation[3] = rcossin_tbl[uVar3 + 1];

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

// [D]
void UpdateCarPoints(CAR_COSMETICS *carCos)
{
	SVECTOR *groundCollPoints;
	SVECTOR *wheelPoints;
	int i;

	groundCollPoints = carCos->cPoints;
	wheelPoints = carCos->wheelDisp;

	i = 11;

	do {
		groundCollPoints->vx = groundCollPoints->vx + delta.vx;
		groundCollPoints->vy = groundCollPoints->vy - delta.vy;
		groundCollPoints->vz = groundCollPoints->vz + delta.vz;
		groundCollPoints++;
		i--;
	} while (-1 < i);

	if (doWheels != 0) 
	{
		i = 3;

		do {
			wheelPoints->vx = wheelPoints->vx + delta.vx;
			wheelPoints->vy = wheelPoints->vy - delta.vy;
			wheelPoints->vz = wheelPoints->vz + delta.vz;
			wheelPoints++;
			i--;
		} while (-1 < i);
	}

	carCos->cog.vx = carCos->cog.vx + delta.vx;
	carCos->cog.vy = carCos->cog.vy + delta.vy;
	carCos->cog.vz = carCos->cog.vz - delta.vz;

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

// [D]
void FixCarCos(CAR_COSMETICS *carCos, int externalModelNumber)
{
	delta.vx = 0;
	delta.vy = 0;

	doWheels = 1;
	delta.vz = -(short)(((int)carCos->wheelDisp[0].vz + (int)carCos->wheelDisp[1].vz-14) / 2);

	UpdateCarPoints(carCos);

	if ((carCos == car_cosmetics + 2) && (gCurrentMissionNumber == 7)) {
		car_cosmetics[2].mass = car_cosmetics[2].mass * 3;
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

// [D]
void GlobalTimeStep(void)
{
	static union RigidBodyState _tp[20]; // offset 0x0
	static union RigidBodyState _d0[20]; // offset 0x410
	static union RigidBodyState _d1[20]; // offset 0x820

	unsigned char uVar1;
	unsigned char uVar2;
	short sVar3;
	bool bVar4;
	int iVar5;
	uint uVar6;
	long lVar7;
	long lVar8;
	int howHard;
	int iVar9;
	long lVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	uint uVar14;
	int iVar15;
	int iVar16;
	long *plVar17;
	long *piVar18;
	int iVar19;
	int iVar20;
	int iVar21;
	int iVar22;
	long *plVar23;
	int iVar24;
	_CAR_DATA *cp;
	RigidBodyState *p_Var25;
	_CAR_DATA **pp_Var26;
	_CAR_DATA *c1;
	RigidBodyState *st;
	RigidBodyState *p_Var27;
	int iVar28;
	long AV[4];
	long delta_orientation[4];
	long normal[4];
	long collisionpoint[4];
	long lever0[4];
	long lever1[4];
	long torque[4];
	long pointVel0[4];
	long pointVel1[4];
	VECTOR velocity;
	int local_58;
	int RKstep;
	int subframe;
	RigidBodyState *local_4c;
	int local_48;
	int local_40;
	int local_34;
	int local_30;

	StepCars();
	CheckCarToCarCollisions();

	if (playerghost != 0 && playerhitcopsanyway == 0) 
		car_data[0].hd.mayBeColliding = 0;

	iVar28 = 0;

	if (0 < num_active_cars) 
	{
		do {
			cp = active_car_list[iVar28];

			iVar19 = cp->hd.aacc[0];
			iVar21 = cp->hd.aacc[1];
			iVar24 = cp->hd.aacc[2];

			iVar5 = cp->st.n.linearVelocity[0];
			howHard = cp->hd.acc[0];
			iVar15 = cp->st.n.linearVelocity[1];
			iVar9 = cp->hd.acc[1];

			cp->hd.aacc[0] = 0;
			cp->hd.aacc[1] = 0;
			cp->hd.aacc[2] = 0;

			st = &cp->st;

			iVar15 = iVar15 + iVar9;
			cp->st.n.linearVelocity[0] = iVar5 + howHard;
			iVar5 = cp->st.n.linearVelocity[2];
			iVar9 = cp->hd.acc[2];
			howHard = cp->st.n.angularVelocity[0];
			cp->st.n.linearVelocity[1] = iVar15;
			cp->st.n.linearVelocity[2] = iVar5 + iVar9;
			iVar5 = (cp->st).n.angularVelocity[1];
			cp->st.n.angularVelocity[0] = howHard + iVar19;
			howHard = (cp->st).n.angularVelocity[2];
			
			cp->st.n.angularVelocity[1] = iVar5 + iVar21;
			cp->st.n.angularVelocity[2] = howHard + iVar24;

			if (200000 < iVar15) 
			{
				iVar15 = iVar15 * 3;
				cp->st.n.linearVelocity[1] = iVar15 / 4;
			}
			if (cp->hd.speed == 0)
			{
				iVar15 = cp->st.n.linearVelocity[0];
				iVar5 = cp->st.n.linearVelocity[1];
				howHard = cp->st.n.linearVelocity[2];

				if (iVar15 < 0) 
					iVar15 = -iVar15;

				if (iVar5 < 0) 
					iVar5 = -iVar5;

				if (howHard < 0) 
					howHard = -howHard;

				if (iVar15 + iVar5 + howHard < 1000) 
				{
					cp->st.n.linearVelocity[0] = 0;
					cp->st.n.linearVelocity[1] = 0;
					cp->st.n.linearVelocity[2] = 0;
					cp->st.n.angularVelocity[0] = 0;
					cp->st.n.angularVelocity[1] = 0;
					cp->st.n.angularVelocity[2] = 0;
				}
				else
				{
					cp->hd.speed = 1;
				}
			}
			iVar15 = cp->st.n.angularVelocity[0];
			lVar10 = 0x800000;

			if ((0x800000 < iVar15) || (lVar10 = -0x800000, iVar15 < -0x800000)) 
				cp->st.n.angularVelocity[0] = lVar10;

			iVar15 = cp->st.n.angularVelocity[1];
			lVar10 = 0x800000;

			if ((0x800000 < iVar15) || (lVar10 = -0x800000, iVar15 < -0x800000)) 
				cp->st.n.angularVelocity[1] = lVar10;

			iVar15 = cp->st.n.angularVelocity[2];
			lVar10 = 0x800000;

			if ((0x800000 < iVar15) || (lVar10 = -0x800000, iVar15 < -0x800000))
				cp->st.n.angularVelocity[2] = lVar10;

			if (cp->hd.mayBeColliding == 0)
			{
				// there might be bug, please decompile correctly
				long* orient = cp->st.n.orientation;

				st->n.fposition[0] += cp->st.n.linearVelocity[0] / 256;
				st->n.fposition[1] += cp->st.n.linearVelocity[1] / 256;
				st->n.fposition[2] += cp->st.n.linearVelocity[2] / 256;

				AV[0] = cp->st.n.angularVelocity[0] / 8192;
				AV[1] = cp->st.n.angularVelocity[1] / 8192;
				AV[2] = cp->st.n.angularVelocity[2] / 8192;

				delta_orientation[0] = (-orient[1] * AV[2] + orient[2] * AV[1] + orient[3] * AV[0]);
				delta_orientation[1] = (orient[0] * AV[2] - orient[2] * AV[0]) + orient[3] * AV[1];
				delta_orientation[2] = (-orient[0] * AV[1] + orient[1] * AV[0] + orient[3] * AV[2]);
				delta_orientation[3] = (-orient[0] * AV[0] - orient[1] * AV[1]) - orient[2] * AV[2];

				orient[0] += delta_orientation[0] / 4096;
				orient[1] += delta_orientation[1] / 4096;
				orient[2] += delta_orientation[2] / 4096;
				orient[3] += delta_orientation[3] / 4096;

				RebuildCarMatrix(st, cp);
			}

			iVar28 = iVar28 + 1;
		} while (iVar28 < num_active_cars);
	}
	subframe = 0;
	iVar28 = num_active_cars;

	do {

		RKstep = 0;
		iVar15 = subframe + 1;

		do {
			local_40 = 0;
			iVar5 = RKstep + 1;

			if (0 < iVar28)
			{
				// Update each car
				howHard = 0;
				do {
					cp = active_car_list[local_40];// *(_CAR_DATA **)((int)active_car_list + howHard);

					if (RKstep != 0 && (subframe & 1U) != 0 && cp->controlType == 1) 
					{
						CheckScenaryCollisions(cp);
					}

					if (cp->hd.mayBeColliding != 0)
					{
						local_34 = local_40 * 2;

						if (RKstep == 0) 
						{
							st = &cp->st;
							local_4c = _d0;

							local_34 = local_40 << 1;
						}
						else 
						{
							st = &_tp[local_40];
							local_4c = _d1;
						}

						long* orient = st->n.orientation;

						local_4c[local_40].n.fposition[0] = st->n.linearVelocity[0] / 256;
						local_4c[local_40].n.fposition[1] = st->n.linearVelocity[1] / 256;
						local_4c[local_40].n.fposition[2] = st->n.linearVelocity[2] / 256;

						AV[0] = st->n.angularVelocity[0] / 8192;
						AV[1] = st->n.angularVelocity[1] / 8192;
						AV[2] = st->n.angularVelocity[2] / 8192;

						local_4c[local_40].n.orientation[0] = (-orient[1] * AV[2] + orient[2] * AV[1] + orient[3] * AV[0]) / 4096;
						local_4c[local_40].n.orientation[1] = ((orient[0] * AV[2] - orient[2] * AV[0]) + orient[3] * AV[1]) / 4096;
						local_4c[local_40].n.orientation[2] = (-orient[0] * AV[1] + orient[1] * AV[0] + orient[3] * AV[2]) / 4096;
						local_4c[local_40].n.orientation[3] = ((-orient[0] * AV[0] - orient[1] * AV[1]) - orient[2] * AV[2]) / 4096;

						local_4c[local_40].n.linearVelocity[0] = 0;
						local_4c[local_40].n.linearVelocity[1] = 0;
						local_4c[local_40].n.linearVelocity[2] = 0;
						local_4c[local_40].n.angularVelocity[0] = 0;
						local_4c[local_40].n.angularVelocity[1] = 0;
						local_4c[local_40].n.angularVelocity[2] = 0;

						local_48 = 0;

						if (0 < local_40) 
						{
							local_30 = 0;
							p_Var27 = local_4c;

							do {
								c1 = active_car_list[local_48];
								p_Var25 = &c1->st;

								if (0 < RKstep)
									p_Var25 = &_tp[local_30]; //(RigidBodyState *)((int)_tp[0].v + local_30);

								if (c1->hd.mayBeColliding != 0 && (c1->hd.speed != 0 || cp->hd.speed != 0))
								{
									iVar28 = cp->hd.where.t[0];
									iVar19 = cp->hd.where.t[1];
									howHard = cp->hd.where.t[2];

									iVar21 = c1->hd.where.t[0];
									iVar9 = c1->hd.where.t[1];
									iVar24 = c1->hd.where.t[2];

									uVar6 = cp->id;
									uVar14 = c1->id;

									BOUND_BOX* bb1 = &bbox[cp->id];
									BOUND_BOX* bb2 = &bbox[c1->id];

									if (bb2->x0 < bb1->x1 && bb2->z0 < bb1->z1 &&
										bb1->x0 < bb2->x1 && bb1->z0 < bb2->z1 &&
										bb2->y0 < bb1->y1 && bb1->y0 < bb2->y1 &&
										CarCarCollision3(cp, c1, &local_58, (VECTOR *)collisionpoint, (VECTOR *)normal) != 0) 
									{
										collisionpoint[1] -= 60;

										lever0[0] = collisionpoint[0] - cp->hd.where.t[0];
										lever0[2] = collisionpoint[2] - cp->hd.where.t[2];

										lever1[0] = collisionpoint[0] - c1->hd.where.t[0];
										lever1[2] = collisionpoint[2] - c1->hd.where.t[2];

										iVar19 = collisionpoint[1] - cp->hd.where.t[1];
										iVar9 = collisionpoint[1] - c1->hd.where.t[1];

										iVar28 = 0x2f - (iVar19 + iVar9) / 2;

										lever0[1] = iVar19 + iVar28;
										lever1[1] = iVar9 + iVar28;

										iVar28 = local_58 * 0xc000;

										howHard = (((st->n.angularVelocity[1] * lever0[2] - st->n.angularVelocity[2] * lever0[1]) / 4096) + st->n.linearVelocity[0]) -
											(((p_Var25->n.angularVelocity[1] * lever1[2] - p_Var25->n.angularVelocity[2] * lever1[1]) / 4096) + p_Var25->n.linearVelocity[0]);

										iVar19 = (((st->n.angularVelocity[2] * lever0[0] - st->n.angularVelocity[0] * lever0[2]) / 4096) + st->n.linearVelocity[1]) -
											(((p_Var25->n.angularVelocity[2] * lever1[0] - p_Var25->n.angularVelocity[0] * lever1[2]) / 4096) + p_Var25->n.linearVelocity[1]);

										iVar9 = (((st->n.angularVelocity[0] * lever0[1] - st->n.angularVelocity[1] * lever0[0]) / 4096) + st->n.linearVelocity[2]) -
											(((p_Var25->n.angularVelocity[0] * lever1[1] - p_Var25->n.angularVelocity[1] * lever1[0]) / 4096) + p_Var25->n.linearVelocity[2]);

										lVar10 = normal[0];
										lVar7 = normal[1];
										lVar8 = normal[2];

										howHard = (howHard >> 8) * (lVar10 >> 5) + (iVar19 >> 8) * (lVar7 >> 5) + (iVar9 >> 8) * (lVar8 >> 5);

										if ((0 < howHard) && (-1 < RKstep))
										{
											if (DamageCar3D(c1, (long(*)[4])lever1, howHard / 2, cp))
												c1->ap.needsDenting = 1;

											if (DamageCar3D(cp, (long(*)[4])lever0, howHard / 2, c1))
												cp->ap.needsDenting = 1;

											if (0x32000 < howHard) 
											{
												if (cp->controlType == 2) 
													cp->ai.c.carMustDie = 1;

												if (c1->controlType == 2) 
													c1->ai.c.carMustDie = 1;
											}

											if (((numCopCars < 4) && (numActiveCops < maxCopCars)) && (GameType != GAME_GETAWAY))
											{
												if ((cp->controlType == 1) && ((*(uint *)&c1->hndType & 0x2ff00) == 0x20200))
												{
													InitCopState(c1, NULL);
													c1->ai.p.justPinged = 0;
												}
												if ((c1->controlType == 1) && ((*(uint *)&cp->hndType & 0x2ff00) == 0x20200))
												{
													InitCopState(cp, NULL);
													cp->ai.p.justPinged = 0;
												}
											}

											if (0x1b00 < howHard) 
											{
												velocity.vy = -17;
												velocity.vx = cp->st.n.linearVelocity[0] / 4096;
												velocity.vz = cp->st.n.linearVelocity[2] / 4096;

												collisionpoint[1] = -collisionpoint[1];

												if ((cp->controlType == 1) || (c1->controlType == 1))
												{
													Setup_Sparks((VECTOR *)collisionpoint, &velocity, 6, 0);

													if (cp->controlType == 1) 
														SetPadVibration(*cp->ai.padid, 1);

													if (c1->controlType == 1)
														SetPadVibration(*c1->ai.padid, 1);
												}

												if (0x2400 < howHard) 
												{
													iVar9 = GetDebrisColour(cp);
													iVar19 = GetDebrisColour(c1);

													Setup_Debris((VECTOR *)collisionpoint, &velocity, 3, 0);
													Setup_Debris((VECTOR *)collisionpoint, &velocity, 6, iVar9 << 0x10);
													Setup_Debris((VECTOR *)collisionpoint, &velocity, 2, iVar19 << 0x10);
												}
											}
										}

										iVar9 = howHard * 9;
										//if (iVar9 < 0) {
										//	iVar9 = iVar9 + 3;
										//}
										iVar28 = iVar28 + (iVar9 >> 2);

										if (0x69000 < iVar28) 
											iVar28 = 0x69000;

										iVar19 = cp->ap.carCos->mass;
										iVar9 = c1->ap.carCos->mass;
										uVar1 = cp->controlType;
										uVar2 = c1->controlType;

										if (iVar9 < iVar19)
										{
											iVar24 = (iVar9 << 0xc) / iVar19;
											iVar21 = 0x1000;
										}
										else 
										{
											iVar21 = (iVar19 << 0xc) / iVar9;
											iVar24 = 0x1000;
										}

										if (uVar1 != 7 && iVar19 != 0x7fff)
										{
											sVar3 = car_cosmetics[cp->ap.model].twistRateY;

											if (((uVar1 == 3) && (uVar2 != 3)) && (c1->hndType != '\0'))
											{
												iVar11 = iVar28 * (7 - gCopDifficultyLevel);
											LAB_00054ae0:
												iVar19 = iVar11 >> 3;
												//if (iVar11 < 0)
												//{
												//	iVar19 = iVar11 + 7 >> 3;
												//}
											}
											else 
											{
												iVar19 = iVar28;
												if ((uVar1 == 4) && (c1->hndType != 0))
												{
													iVar11 = iVar28 * 5;
													goto LAB_00054ae0;
												}
											}

											iVar19 = iVar19 / 4096 * iVar24 >> 3;
											velocity.vx = (normal[0] >> 3) * iVar19 >> 6;
											velocity.vz = (normal[2] >> 3) * iVar19 >> 6;
											velocity.vy = (normal[1] >> 3) * iVar19 >> 6;

											local_4c[local_40].n.linearVelocity[0] -= velocity.vx;
											local_4c[local_40].n.linearVelocity[1] -= velocity.vy;
											local_4c[local_40].n.linearVelocity[2] -= velocity.vz;

											iVar19 = sVar3 >> 1;
											torque[0] = ((velocity.vy * lever0[2] - velocity.vz * lever0[1]) / 4096) * iVar19;
											torque[1] = ((velocity.vz * lever0[0] - velocity.vx * lever0[2]) / 4096) * iVar19;
											torque[2] = ((velocity.vx * lever0[1] - velocity.vy * lever0[0]) / 4096) * iVar19;

											if (c1->controlType == 4) // infinite mass
											{
												torque[0] = 0;
												torque[2] = 0;
											}

											local_4c[local_40].n.angularVelocity[0] += torque[0];
											local_4c[local_40].n.angularVelocity[1] += torque[1];
											local_4c[local_40].n.angularVelocity[2] += torque[2];
										}

										if (uVar2 != 7 && iVar9 != 0x7fff)
										{
											sVar3 = car_cosmetics[c1->ap.model].twistRateY;

											if (((cp->controlType == 3) ||
												(c1->controlType != 3)) ||
												(c1->hndType == 0)) 
											{
												if ((c1->controlType == 4) && (cp->hndType != 0))
												{
													iVar9 = iVar28 * 5;
													goto LAB_00054d38;
												}
											}
											else 
											{
												iVar9 = iVar28 * (7 - gCopDifficultyLevel);
											LAB_00054d38:
												iVar28 = iVar9 >> 3;
												//if (iVar9 < 0)
												//{
												//	iVar28 = iVar9 + 7 >> 3;
												//}
											}

											iVar28 = (iVar28 / 4096) * iVar21 >> 3;
											velocity.vx = (normal[0] >> 3) * iVar28 >> 6;
											velocity.vy = (normal[1] >> 3) * iVar28 >> 6;
											velocity.vz = (normal[2] >> 3) * iVar28 >> 6;

											iVar28 = p_Var27->n.linearVelocity[1];
											p_Var27->n.linearVelocity[0] = p_Var27->n.linearVelocity[0] + velocity.vx;
											p_Var27->n.linearVelocity[1] = iVar28 + velocity.vy;
											p_Var27->n.linearVelocity[2] = p_Var27->n.linearVelocity[2] + velocity.vz;
											iVar28 = (int)sVar3 >> 1;

											torque[0] = ((lever1[1] * velocity.vz - lever1[2] * velocity.vy) / 4096) * iVar28;
											torque[2] = ((lever1[0] * velocity.vy - lever1[1] * velocity.vx) / 4096) * iVar28;

											if (c1->controlType == 4) 
											{
												torque[0] = 0;
												torque[2] = 0;
											}

											iVar9 = p_Var27->n.angularVelocity[1];
											p_Var27->n.angularVelocity[0] = p_Var27->n.angularVelocity[0] + torque[0];
											p_Var27->n.angularVelocity[1] = iVar9 + ((lever1[2] * velocity.vx - lever1[0] * velocity.vz) / 4096) * iVar28;
											p_Var27->n.angularVelocity[2] = p_Var27->n.angularVelocity[2] + torque[2];
										}

										if ((cp->id == player[0].playerCarId) ||
											(c1->id == player[0].playerCarId)) 
										{
											RegisterChaseHit(cp->id, c1->id);
										}

										if (cp->id == player[0].playerCarId)
										{
											CarHitByPlayer(c1, howHard);
										}

										if (c1->id == player[0].playerCarId) 
										{
											CarHitByPlayer(cp, howHard);
										}
									}
								}

								p_Var27++;
								local_30++;
								local_48++;
							} while (local_48 < local_40);
						}
					}
					local_40 = local_40 + 1;
					howHard = local_40 * 4;
					iVar28 = num_active_cars;
				} while (local_40 < num_active_cars);
			}

			if (0 < iVar28) 
			{
				howHard = 0;
				iVar19 = 0;
				do {
					cp = active_car_list[iVar19];
					iVar19 = howHard + 1;

					if (cp->hd.mayBeColliding != 0)
					{
						if (RKstep == 0) 
						{
							iVar28 = 12;

							piVar18 = cp->st.v;
							plVar23 = _tp[howHard].v;
							plVar17 = _d0[howHard].v;

							do {
								*plVar23 = *piVar18 + (*plVar17 >> 2);

								piVar18++;
								plVar17++;
								plVar23++;

								iVar28--;
							} while (-1 < iVar28);

							RebuildCarMatrix(&_tp[howHard], cp);
						}
						else if (RKstep == 1)
						{
							iVar28 = 12;

							plVar23 = _d1[howHard].v;
							plVar17 = _d0[howHard].v;
							piVar18 = cp->st.v;

							do {
								*piVar18 = *piVar18 + (*plVar17 + *plVar23 >> 3);

								plVar23++;
								plVar17++;
								piVar18++;

								iVar28--;
							} while (-1 < iVar28);

							RebuildCarMatrix(&cp->st, cp);
						}
					}

					iVar28 = num_active_cars;
					howHard = iVar19;
				} while (iVar19 < num_active_cars);
			}

			RKstep = iVar5;
		} while (iVar5 < 2);

		iVar5 = 0;
		subframe = iVar15;

		if (3 < iVar15) 
		{
			iVar15 = 0;
			if (0 < iVar28) 
			{
				pp_Var26 = active_car_list;

				do {
					cp = *pp_Var26;
					
					cp->hd.drawCarMat.m[0][0] = ~cp->hd.where.m[0][0];
					cp->hd.drawCarMat.m[0][1] = ~cp->hd.where.m[0][1];
					cp->hd.drawCarMat.m[0][2] = cp->hd.where.m[0][2] ^ 0xFFFF;
					cp->hd.drawCarMat.m[1][0] = cp->hd.where.m[1][0];
					cp->hd.drawCarMat.m[1][1] = cp->hd.where.m[1][1];
					cp->hd.drawCarMat.m[1][2] = cp->hd.where.m[1][2];
					cp->hd.drawCarMat.m[2][0] = ~cp->hd.where.m[2][0];
					cp->hd.drawCarMat.m[2][1] = ~cp->hd.where.m[2][1];
					cp->hd.drawCarMat.m[2][2] = cp->hd.where.m[2][2] ^ 0xFFFF;

					if ((cp->ap.needsDenting != 0) && (((CameraCnt + iVar15 & 3U) == 0 || (iVar5 < 5)))) 
					{
						DentCar(cp);
						cp->ap.needsDenting = 0;
						iVar5 = iVar5 + 1;
					}

					cp->hd.direction = ratan2(cp->hd.where.m[0][2], cp->hd.where.m[2][2]);

					pp_Var26++;
					iVar15++;
				} while (iVar15 < num_active_cars);
			}
			return;
		}
	} while (true);
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

// [D]
void SetShadowPoints(_CAR_DATA *c0)
{
	bool bVar1;
	uint uVar2;
	uint puVar3;
	SVECTOR *pSVar5;
	int iVar6;
	SVECTOR disp;
	VECTOR pointPos;
	VECTOR surfaceNormal;
	VECTOR surfacePoint;

	_sdPlane *surfacePtr;
	surfacePtr = NULL;

	gte_SetRotMatrix(&c0->hd.where);
	gte_SetTransMatrix(&c0->hd.where);

	iVar6 = 0;
	pSVar5 = car_cosmetics[c0->ap.model].cPoints;

	do {
		disp = *pSVar5;

		/* // [A] No point to keep this cheat
		if (cheats.MiniCars != 0) 
		{
			disp._0_4_ = CONCAT22((short)((int)disp._0_4_ >> 0x12), disp.vx >> 2);
			disp._4_4_ = disp._4_4_ & 0xffff0000 | (uint)(ushort)(disp.vz >> 2);
		}*/

		gte_ldv0(&disp);

		docop2(0x480012);

		pointPos.vx = MAC1; // getCopReg(2, 0x19);
		pointPos.vy = MAC2; // getCopReg(2, 0x1a);
		pointPos.vz = MAC3; // getCopReg(2, 0x1b);

		static int hSubShad = 0;

		hSubShad = 0;

		FindSurfaceD2(&pointPos, &surfaceNormal, &surfacePoint, &surfacePtr);

		c0->hd.shadowPoints[iVar6].vx = surfacePoint.vx;
		c0->hd.shadowPoints[iVar6].vy = surfacePoint.vy;
		c0->hd.shadowPoints[iVar6].vz = surfacePoint.vz;

		puVar3 = c0->hd.shadowPoints[iVar6].vy;
		uVar2 = puVar3;

		bVar1 = hSubShad != 0;

		c0->hd.shadowPoints[iVar6].vy = uVar2 & 0xfffffffe;

		if (bVar1)
			c0->hd.shadowPoints[iVar6].vy = uVar2 & 0xfffffffe | 1;

		iVar6 = iVar6 + 1;
		pSVar5 = pSVar5 + 1;

	} while (iVar6 < 4);
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

// [D]
void LongQuaternion2Matrix(long(*qua)[4], MATRIX *m)
{
	short sVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	iVar6 = (*qua)[0];
	iVar5 = (*qua)[1];
	iVar8 = (*qua)[2];
	iVar7 = (*qua)[3];

	sVar1 = (iVar5 * iVar5) / 2048;
	sVar2 = (iVar8 * iVar8) / 2048;
	sVar3 = (iVar6 * iVar6) / 2048;

	m->m[0][0] = 4096 - (sVar1 + sVar2);
	m->m[1][1] = 4096 - (sVar3 + sVar2);
	m->m[2][2] = 4096 - (sVar3 + sVar1);

	sVar2 = (iVar8 * iVar7) / 2048;
	sVar1 = (iVar6 * iVar5) / 2048;

	m->m[0][1] = sVar1 - sVar2;

	sVar3 = (iVar6 * iVar8) / 2048;
	sVar4 = (iVar5 * iVar7) / 2048;

	m->m[0][2] = sVar3 + sVar4;
	m->m[1][0] = sVar1 + sVar2;
	m->m[2][0] = sVar3 - sVar4;

	sVar2 = (iVar6 * iVar7) / 2048;
	sVar1 = (iVar5 * iVar8) / 2048;

	m->m[1][2] = sVar1 - sVar2;
	m->m[2][1] = sVar1 + sVar2;
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

// [D]
void initOBox(_CAR_DATA *cp)
{
	SVECTOR boxDisp;

	short sVar2;
	int iVar3;


	gte_SetRotMatrix(&cp->hd.where);
	gte_SetTransMatrix(&cp->hd.where);

	boxDisp.vx = -cp->ap.carCos->cog.vx;
	boxDisp.vy = -cp->ap.carCos->cog.vy;
	boxDisp.vz = -cp->ap.carCos->cog.vz;

	gte_ldv0(&boxDisp);
	docop2(0x480012);

	if (cp->controlType == 3) 
	{
		iVar3 = cp->ap.carCos->colBox.vx * 14;

		sVar2 = (iVar3 >> 4);
		cp->hd.oBox.length[0] = sVar2;
	}
	else 
	{
		sVar2 = cp->ap.carCos->colBox.vx;
		cp->hd.oBox.length[0] = sVar2;
	}

	cp->hd.oBox.location.vx = MAC1;
	cp->hd.oBox.location.vy = MAC2;
	cp->hd.oBox.location.vz = MAC3;

	IR1 = sVar2;
	IR2 = 0;
	IR3 = 0;

	docop2(0x49e012);

	sVar2 = cp->ap.carCos->colBox.vy;
	cp->hd.oBox.length[1] = sVar2;

	cp->hd.oBox.radii[0].vx = IR1;
	cp->hd.oBox.radii[0].vy = IR2;
	cp->hd.oBox.radii[0].vz = IR3;

	IR1 = 0;
	IR2 = sVar2;
	IR3 = 0;

	docop2(0x49e012);

	sVar2 = cp->ap.carCos->colBox.vz;
	cp->hd.oBox.length[2] = sVar2;

	cp->hd.oBox.radii[1].vx = IR1;
	cp->hd.oBox.radii[1].vy = IR2;
	cp->hd.oBox.radii[1].vz = IR3;

	IR1 = 0;
	IR2 = 0;
	IR3 = sVar2;

	docop2(0x49e012);

	cp->hd.oBox.radii[2].vx = IR1;
	cp->hd.oBox.radii[2].vy = IR2;
	cp->hd.oBox.radii[2].vz = IR3;
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

// [D]
void RebuildCarMatrix(RigidBodyState *st, _CAR_DATA *cp)
{
	int iVar1;
	int osm;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	cp->hd.where.t[0] = st->n.fposition[0] / 16;
	cp->hd.where.t[1] = st->n.fposition[1] / 16;
	cp->hd.where.t[2] = st->n.fposition[2] / 16;
	
	iVar6 = st->n.orientation[0];
	iVar5 = st->n.orientation[1];
	iVar4 = st->n.orientation[2];
	iVar3 = st->n.orientation[3];

	osm = iVar6 * iVar6 + iVar5 * iVar5 + iVar4 * iVar4 + iVar3 * iVar3;
	iVar1 = 4096;

	if (osm < 1024)
	{
		st->n.orientation[2] = 0;
		st->n.orientation[1] = 0;
		st->n.orientation[0] = 0;
	}
	else 
	{
		iVar1 = 6144 - (osm / 8192);

		st->n.orientation[0] = (iVar1 * iVar6) / 4096;
		st->n.orientation[1] = (iVar1 * iVar5) / 4096;
		st->n.orientation[2] = (iVar1 * iVar4) / 4096;

		iVar1 = (iVar1 * iVar3) / 4096;
	}
	st->n.orientation[3] = iVar1;
	
	LongQuaternion2Matrix((long(*)[4])st->n.orientation, (MATRIX *)cp);

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



// [D]
void StepCarPhysics(_CAR_DATA *cp)
{
	unsigned char bVar1;

	bVar1 = cp->hndType;
	if (cp->controlType != '\0')
	{
		if (bVar1 == 1)
			handlingType[bVar1].aggressiveBraking = 0;
		else 
			handlingType[bVar1].aggressiveBraking = 1;

		active_car_list[num_active_cars] = cp;
		num_active_cars++;
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

// [D]
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


// [D]
void CheckCarToCarCollisions(void)
{
	int iVar2;
	int iVar4;
	int iVar5;
	int iVar6;
	char *pcVar7;
	int iVar8;
	int iVar9;
	int iVar10;

	int loop1, loop2;

	BOUND_BOX *bb1;
	BOUND_BOX *bb2;
	_CAR_DATA *cp;
	SVECTOR *colBox;

	cp = car_data;

	if (ghost_mode == 1)
		return;

	bb2 = bbox;
	iVar8 = 19;

	do {
		if (cp->controlType == 0) // [A] required as game crashing
		{
			cp++;
			bb2++;
			iVar8--;
			continue;
		}

		colBox = &cp->ap.carCos->colBox;

		iVar6 = colBox->vy;
		iVar2 = colBox->vz * 9;

		iVar9 = cp->hd.where.m[0][2] * (iVar2 >> 3);
		iVar4 = colBox->vx * 9;

		if (iVar9 < 0)
			iVar9 = -iVar9;
	
		iVar10 = cp->hd.where.m[0][0] * (iVar4 >> 3);

		if (iVar10 < 0)
			iVar10 = -iVar10;
	
		iVar9 = (iVar9 + iVar10) / 4096 + iVar6;
		iVar2 = cp->hd.where.m[2][2] * (iVar2 >> 3);

		if (iVar2 < 0)
			iVar2 = -iVar2;
	
		iVar4 = cp->hd.where.m[2][0] * (iVar4 >> 3);
		iVar10 = cp->hd.where.t[0];
		iVar5 = iVar10 - iVar9;

		if (iVar4 < 0)
			iVar4 = -iVar4;
	
		iVar6 = (iVar2 + iVar4) / 4096 + iVar6;

		iVar4 = cp->hd.where.t[2];
		iVar2 = iVar4 - iVar6;
		bb2->x0 = iVar5 >> 4;

		bb2->z0 = iVar2 >> 4;
		iVar10 = iVar10 + iVar9;

		iVar4 = iVar4 + iVar6;
		bb2->x1 = iVar10 >> 4;

		iVar2 = cp->st.n.linearVelocity[0];
		bb2->z1 = iVar4 >> 4;

		if (iVar2 < 0) 
		{
			iVar2 = iVar2 / 4096;
			bb2->x0 = (iVar5 >> 4) + (iVar2 >> 3);
		}
		else
		{
			iVar2 = iVar2 / 4096;
			bb2->x1 = (iVar10 >> 4) + (iVar2 >> 3);
		}

		iVar2 = cp->st.n.linearVelocity[2];

		if (iVar2 < 0)
		{
			iVar2 = iVar2 / 4096;
			bb2->z0 = bb2->z0 + (iVar2 >> 3);
		}
		else
		{
			iVar2 = iVar2 / 4096;
			bb2->z1 = bb2->z1 + (iVar2 >> 3);
		}

		iVar6 = cp->hd.where.t[1];

		// [A] 2400 for box size - bye bye collision check performance under bridges
		iVar2 = iVar6 - colBox->vy * 2;// -2400;
		bb2->y0 = iVar2 >> 4;

		iVar2 = iVar6 + colBox->vy * 4;// +2400;
		bb2->y1 = iVar2 >> 4;

		if (cp->hndType == 0)
			cp->hd.mayBeColliding = 1;

		iVar8--;
		bb2++;
		cp++;
	} while (-1 < iVar8);

	bb2 = bbox;
	iVar8 = 0;

	do {

		iVar2 = iVar8 + 1;
		bool mayBeColliding = false;

		if (iVar2 < 20) 
		{
			bb1 = bb2 + 1;
			iVar6 = iVar2;

			do {

				if (bb1->x0 < bb2->x1 && bb1->z0 < bb2->z1 && bb2->x0 < bb1->x1 &&
					bb2->z0 < bb1->z1 && bb1->y0 < bb2->y1 && bb2->y0 < bb1->y1 &&
					(iVar8 == 0 || car_data[iVar8].controlType != 0) && car_data[iVar6].controlType != 0)
				{
					car_data[iVar8].hd.mayBeColliding = car_data[iVar6].hd.mayBeColliding = 1;
					mayBeColliding = true;
				}

				iVar6++;
				bb1++;
			} while (iVar6 < 20);
		}

#if defined(COLLISION_DEBUG) && !defined(PSX)
		extern int gShowCollisionDebug;
		if (gShowCollisionDebug && car_data[iVar8].controlType != 0)
		{
			extern void Debug_AddLine(VECTOR& pointA, VECTOR& pointB, CVECTOR& color);

			CVECTOR bbcv = { 0, 0, 250 };
			CVECTOR rrcv = { 250, 0, 0 };
			CVECTOR yycv = { 250, 250, 0 };

			CVECTOR bbcol = mayBeColliding ? rrcv : yycv;

			VECTOR box_pointsy0[4] = {
				{bb2->x0 * 16, bb2->y0 * 16, bb2->z0 * 16, 0},	// front left
				{bb2->x1 * 16, bb2->y0 * 16, bb2->z0 * 16, 0},	// front right
				{bb2->x1 * 16, bb2->y0 * 16, bb2->z1 * 16, 0},	// back right
				{bb2->x0 * 16, bb2->y0 * 16, bb2->z1 * 16, 0},	// back left
			};

			Debug_AddLine(box_pointsy0[0], box_pointsy0[1], bbcol);
			Debug_AddLine(box_pointsy0[1], box_pointsy0[2], bbcol);
			Debug_AddLine(box_pointsy0[2], box_pointsy0[3], bbcol);
			Debug_AddLine(box_pointsy0[3], box_pointsy0[0], bbcol);

			VECTOR box_pointsy1[4] = {
				{bb2->x0 * 16, bb2->y1 * 16, bb2->z0 * 16, 0},	// front left
				{bb2->x1 * 16, bb2->y1 * 16, bb2->z0 * 16, 0},	// front right
				{bb2->x1 * 16, bb2->y1 * 16, bb2->z1 * 16, 0},	// back right
				{bb2->x0 * 16, bb2->y1 * 16, bb2->z1 * 16, 0},	// back left
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

		bb2 = bb2 + 1;
		iVar8 = iVar2;

	} while (iVar2 < 20);
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

#include "DR2ROADS.H"

void ProcessCarPad(_CAR_DATA *cp, ulong pad, char PadSteer, char use_analogue)
{
#if 1
	extern int gInGameCutsceneActive;
	if (gInGameCutsceneActive == 0 && cp->controlType == 1)
	{
		extern MATRIX camera_matrix;

		// [A]
		if ((pad & 4) == 0) {

			if ((pad & 0x2000) != 0)
			{
				//RotMatrixY(3200, &cp->hd.where);
				//cp->hd.direction -= 30;
				//cp->st.n.angularVelocity[1] += 5000;
			}

			if ((pad & 0x8000) != 0)
			{
				//cp->hd.direction += 30;
				//RotMatrixY(-3200, &cp->hd.where);
				//cp->st.n.angularVelocity[1] -= 5000;
			}

			if ((pad & 0x40) != 0)
			{
				//cp->st.n.angularVelocity
				//cp->st.n.linearVelocity[1] += 12150;
			}

			if ((pad & 0x80) != 0)
			{
				//cp->st.n.linearVelocity[1] -= 12150;
			}

			if ((pad & 0x1000) != 0)
			{
				cp->st.n.linearVelocity[1] += 10000;

				//cp->st.n.linearVelocity[0] += camera_matrix.m[0][2];
				//cp->st.n.linearVelocity[2] += camera_matrix.m[2][2];
				//cp->hd.where.t[0] += camera_matrix.m[0][2] / 30;
				//cp->hd.where.t[2] += camera_matrix.m[2][2] / 30;
			}

			if ((pad & 0x4000) != 0)
			{
				//cp->hd.where.t[0] -= camera_matrix.m[0][2] / 30;
				//cp->hd.where.t[2] -= camera_matrix.m[2][2] / 30;
			}
		}

	}
#endif
	char cVar1;
	short sVar2;
	int iVar3;
	int iVar4;
	unsigned char bVar5;
	CAR_COSMETICS *pCVar6;
	int iVar7;

	int player_id;
	int int_steer;
	int analog_angle;

	iVar7 = PadSteer;

	int_steer = PadSteer;
	player_id = GetPlayerId(cp);
	bVar5 = cp->controlType;

	// control player
	if (cp->controlType == 1) 
	{
		if ((pad & 0x1010) == 0x1010 && (player_id > -1))
		{
			if (TannerStuckInCar(1) == 0)
			{
				if (player[0].dying == 0)
					ActivatePlayerPedestrian(cp, NULL, 0, NULL, 0);
			}
			else if (lockAllTheDoors != 1)
				gLockPickingAttempted = 1;
		}

		if ((gStopPadReads != 0 || MaxPlayerDamage[*cp->ai.padid] <= cp->totalDamage) || gCantDrive != 0) 
		{
			pad = 0x10;

			if (0x9000 < cp->hd.wheel_speed)
				pad = 0x80;

			analog_angle = 0;
			use_analogue = 1;
		}

		if (player_id > -1)
		{
			if (CarHasSiren(cp->ap.model) == 0)
			{
				player[player_id].horn.on = (pad >> 3) & 1;
			}
			else if((cp->lastPad & 8U) == 0 && (pad & 8) != 0)
			{
				player[player_id].horn.on ^= 8;
			}
		}
	}

	if (cp->hd.autoBrake > 90)
		cp->hd.autoBrake = 90;

	if ((pad & 0x10) == 0)
	{
		cp->handbrake = 0;

		if ((pad & 0x20) == 0)
			cp->wheelspin = 0;
		else 
			cp->wheelspin = 1;

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
			int_steer *= ((int_steer * int_steer) / 80);
			analog_angle = int_steer / 2;
			//analog_angle = (int)((uint)int_steer * 0x66666667) >> 0x20;
		}
		else 
		{
			int_steer *= ((int_steer * int_steer) / 60);
			analog_angle = int_steer / 2;
			//analog_angle =  (int)((uint)int_steer * 0x88888889) >> 0x20;
		}

		analog_angle = (analog_angle >> 5) - (int_steer >> 0x1f);

		cp->wheel_angle = analog_angle & 0xfffc;

		if (analog_angle + 270 < 541)
			cp->hd.autoBrake = 0;
		else
			cp->hd.autoBrake++;
	}

	if ((pad & 0xa000) == 0)
	{
		if (cp->wheel_angle < -64) 
			cp->wheel_angle += 64;
		else if (cp->wheel_angle < 65)
			cp->wheel_angle = 0;
		else
			cp->wheel_angle -= 64;
	}

	if (gTimeInWater != 0)
	{
		if ((pad & 0x80) != 0) 
		{
			iVar3 = cp->hd.wheel_speed * 1500;
			iVar3 = (iVar3 >> 10) / 4096;

			if (-iVar3 < 0x17) 
			{
				sVar2 = -5000;
			}
			else
			{
				sVar2 = (short)((uint)((iVar3 + 0x116) * -0x12aa) >> 8);
			}

			cp->thrust = sVar2;
			cp->thrust = cp->thrust * cp->ap.carCos->powerRatio / 4096;
			goto LAB_00056284;
		}

		if ((pad & 0x40) != 0)
		{
			pCVar6 = cp->ap.carCos;
			cp->thrust = 0x1333;
			cp->thrust = (pCVar6->powerRatio * 0x1333) / 4096;

			if (cp->hndType == 5)
			{
				iVar7 = car_data[player[0].playerCarId].hd.where.t[0] - cp->hd.where.t[0] >> 10;
				iVar3 = car_data[player[0].playerCarId].hd.where.t[2] - cp->hd.where.t[2] >> 10;

				iVar3 = iVar7 * iVar7 + iVar3 * iVar3;
				if (iVar3 < 0x29)
				{
					if (iVar3 < 0x15) 
					{
						sVar2 = 6000;
						if (9 < iVar3) 
						{
							sVar2 = 0x1324;
						}
					}
					else
					{
						sVar2 = 4000;
					}
				}
				else
				{
					sVar2 = 3000;
				}
				cp->thrust = sVar2;
			}

			if (cp->controlType == 1) 
			{
				if (player[0].playerCarId == cp->id) 
				{
					iVar3 = player[0].targetCarId;
				}
				else
				{
					iVar3 = -1;

					if (player[1].playerCarId == cp->id) 
						iVar3 = player[1].targetCarId;
				}

				if (iVar3 != -1) 
				{
					if (3050 < cp->ap.carCos->powerRatio) 
						cp->thrust = (car_data[iVar3].ap.carCos->powerRatio * 0x1333) / 4096;

					iVar7 = cp->hd.where.t[0] - car_data[iVar3].hd.where.t[0] >> 10;
					iVar3 = cp->hd.where.t[2] - car_data[iVar3].hd.where.t[2] >> 10;

					iVar3 = iVar7 * iVar7 + iVar3 * iVar3;

					if (iVar3 < 0x15) 
					{
						if (iVar3 < 7) 
						{
							cp->thrust = ((cp->thrust * 0x1a2c) / 7000);
						}
						else 
						{
							cp->thrust = ((cp->thrust * 0x1ce8) / 7000);
						}
					}
					else
					{
						cp->thrust = ((cp->thrust * 8000) / 7000);
					}
				}
			}

			if (cp->hndType == 0 && cp->hd.changingGear != 0)
				cp->thrust = 1;

			goto LAB_00056284;
		}
	}

	cp->thrust = 0;

LAB_00056284:
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

// [D]
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

// [D]
void TerminateSkidding(int player_id)
{
	int channel;

	if (player_id < 2) 
	{
		channel = player[player_id].skidding.chan;
		if (-1 < channel) 
		{
			StopChannel(channel);
			UnlockChannel(player[player_id].skidding.chan);

			player[player_id].skidding.sound = -1;
			player[player_id].skidding.chan = -1;
		}

		channel = player[player_id].wheelnoise.chan;

		if (-1 < channel) 
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

// [D]
void CheckCarEffects(_CAR_DATA *cp, int player_id)
{
	unsigned char uVar1;
	bool bVar2;
	bool bVar3;
	int channel;
	int uVar4;
	WHEEL *pWVar5;
	int iVar6;
	int uVar7;
	int sample;
	char cVar8;

	bVar2 = false;
	bVar3 = false;
	uVar1 = cp->controlType;

	if (uVar1 != 1 && uVar1 != 4 && uVar1 != 7) 
	{
		TerminateSkidding(player_id);
		return;
	}

	jump_debris(cp);
	pWVar5 = cp->hd.wheel;
	sample = 3;
	do {
		if (pWVar5->susCompression != 0)
			bVar2 = true;

		sample = sample + -1;
		pWVar5 = pWVar5 + 1;
	} while (-1 < sample);

	sample = 0;
	if (bVar2) 
	{
		if (cp->wheelspin == 0) 
		{
			channel = cp->hd.rear_vel;
			if (channel < 0)
				channel = -channel;

			if (channel < 11101) 
				goto LAB_00056474;
		}

		rear_only = 1;

		bVar3 = true;
		if (cp->wheelspin == 0) 
		{
			sample = cp->hd.rear_vel;
			if (sample < 0)
				sample = -sample;

			sample = (sample-11100) / 2 + 1;

			if (sample < 13001) 
				goto LAB_00056474;
		}

		sample = 13000;
	}

LAB_00056474:
	channel = cp->hd.front_vel;

	if (channel < 0)
		channel = -channel;

	if (11100 < channel)
	{
		rear_only = 0;
		bVar3 = true;
	}

	cVar8 = -1;

	if (((sample != 0) && (((cp->hd.wheel[1].surface & 0x80) == 0 || ((cp->hd.wheel[3].surface & 0x80) == 0)))) && (cVar8 = 11, gWeather - 1U < 2))
	{
		cVar8 = -1;
	}

	if (cVar8 == player[player_id].skidding.sound) 
	{
	LAB_000565b4:
		if ((-1 < player[player_id].skidding.sound) && (channel = (int)player[player_id].skidding.chan, -1 < channel)) 
		{
			iVar6 = (sample + -10000) * 3;
			//if (iVar6 < 0)
			//	iVar6 = iVar6 + 3;

			SetChannelPosition3(channel, (VECTOR *)cp->hd.where.t, cp->st.n.linearVelocity, (iVar6 / 4) - 5000, (sample * 1024) / 13000 + 3072 + player_id * 8, 0);
		}
	}
	else 
	{
		channel = (int)player[player_id].skidding.chan;
		player[player_id].skidding.sound = cVar8;

		if (-1 < channel) 
		{
			StopChannel(channel);
			UnlockChannel(player[player_id].skidding.chan);
			player[player_id].skidding.chan = -1;
		}

		channel = player[player_id].skidding.sound;
		if (-1 < channel) 
		{
			channel = StartSound(-1, 1, channel, sample-10000, 0x1000);
			player[player_id].skidding.chan = channel;
			LockChannel(channel);

			if ((1 < NumPlayers) && (NoPlayerControl == 0)) 
				SetPlayerOwnsChannel((int)player[player_id].skidding.chan, (char)player_id);
			goto LAB_000565b4;
		}
	}
	sample = -1;
	if (bVar2 && (10 < cp->hd.speed))
	{
		uVar4 = cp->hd.wheel[3].surface & 7;
		uVar7 = cp->hd.wheel[1].surface & 7;

		if (uVar4 < uVar7)
			uVar4 = uVar7;

		sample = 0xd;

		if ((1 < gWeather - 1U) && (sample = -1, uVar4 != 0))
			sample = uVar4 + 12;
	}

	if (sample != player[player_id].wheelnoise.sound)
	{
		channel = player[player_id].wheelnoise.chan;
		player[player_id].wheelnoise.sound = sample;

		if (-1 < channel)
		{
			StopChannel(channel);
			UnlockChannel(player[player_id].wheelnoise.chan);

			player[player_id].wheelnoise.chan = -1;
		}

		sample = player[player_id].wheelnoise.sound;

		if (sample < 0)
			goto LAB_00056814;

		sample = StartSound(-1, 1, sample, -200, 4096);

		player[player_id].wheelnoise.chan = sample;
		LockChannel(sample);

		if ((1 < NumPlayers) && (NoPlayerControl == 0)) 
			SetPlayerOwnsChannel(player[player_id].wheelnoise.chan, player_id);
	}
	if ((-1 < player[player_id].wheelnoise.sound) && (sample = player[player_id].wheelnoise.chan, -1 < sample))
	{
		iVar6 = cp->hd.speed;

		channel = iVar6 * 27;

		if (3584 < channel)
			channel = 3584;

		if (100 < iVar6)
			iVar6 = 100;

		SetChannelPosition3(sample, (VECTOR *)cp->hd.where.t, cp->st.n.linearVelocity, iVar6 * 50-10000, channel + player_id * 8, 0);
	}

LAB_00056814:
	player[player_id].onGrass = 0;

	GetTyreTrackPositions(cp, player_id);

	if (bVar3) 
	{
		continuous_track = last_track_state == rear_only;

		AddTyreTrack(player_id << 1, (uint)(player_id < 2), player_id);
		AddTyreTrack(player_id << 1 | 1, (uint)(player_id < 2), player_id);

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

// [D]
void jump_debris(_CAR_DATA *cp)
{
	char cVar1;
	unsigned char bVar2;

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

	cVar1 = DebrisTimer-1;

	if ((DebrisTimer != 0) && (bVar2 = DebrisTimer - 1, DebrisTimer = cVar1, bVar2 < 0x4b))
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

// [D]
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

// [D]
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





