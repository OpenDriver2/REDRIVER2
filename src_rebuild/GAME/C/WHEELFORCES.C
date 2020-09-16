#include "DRIVER2.H"
#include "WHEELFORCES.H"
#include "CARS.H"
#include "MAIN.H"
#include "GAMESND.H"
#include "DEBRIS.H"
#include "HANDLING.H"
#include "COSMETIC.H"
#include "DR2ROADS.H"
#include "MISSION.H"
#include "PAD.H"
#include "SOUND.H"
#include "GLAUNCH.H"
#include "SYSTEM.H"

#include "INLINE_C.H"
#include "LIBMATH.H"

_HANDLING_TYPE handlingType[7] =
{
	// frictionScaleRatio, aggressiveBraking, fourWheelDrive, autoBrakeOn
	{ 32, 1, 0, 1 },
	{ 29, 0, 0, 0 },
	{ 45, 1, 1, 0 },
	{ 55, 1, 1, 0 },
	{ 68, 1, 1, 0 },
	{ 32, 1, 0, 1 },
	{ 29, 0, 0, 0 }
};


// decompiled code
// original method signature: 
// void /*$ra*/ StepCars()
 // line 66, offset 0x00082bd0
	/* begin block 1 */
		// Start line: 68
		// Start offset: 0x00082BD0
		// Variables:
	// 		struct _CAR_DATA **ppCar; // $s0
	// 		struct _CAR_DATA **end; // $s1

		/* begin block 1.1 */
			// Start line: 73
			// Start offset: 0x00082C0C
		/* end block 1.1 */
		// End offset: 0x00082C0C
		// End Line: 76

		/* begin block 1.2 */
			// Start line: 80
			// Start offset: 0x00082C34
		/* end block 1.2 */
		// End offset: 0x00082C34
		// End Line: 81
	/* end block 1 */
	// End offset: 0x00082C64
	// End Line: 83

	/* begin block 2 */
		// Start line: 1357
	/* end block 2 */
	// End Line: 1358

	/* begin block 3 */
		// Start line: 132
	/* end block 3 */
	// End Line: 133

	/* begin block 4 */
		// Start line: 1358
	/* end block 4 */
	// End Line: 1359

	/* begin block 5 */
		// Start line: 1359
	/* end block 5 */
	// End Line: 1360

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void StepCars(void)
{
	_CAR_DATA **ppCar;
	_CAR_DATA **end;

	ppCar = active_car_list;
	end = active_car_list + num_active_cars;

	// step active cars
	while (ppCar < end)
	{
		StepOneCar(*ppCar);
		ControlCarRevs(*ppCar++);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepOneCar(struct _CAR_DATA *cp /*$s1*/)
 // line 98, offset 0x00081178
	/* begin block 1 */
		// Start line: 99
		// Start offset: 0x00081178
		// Variables:
	// 		struct CAR_LOCALS _cl; // stack offset -248
	// 		struct CAR_LOCALS *cl; // $s3
	// 		int i; // $s0
	// 		int speed; // $v1
	// 		struct _sdPlane *SurfacePtr; // stack offset -48

		/* begin block 1.1 */
			// Start line: 122
			// Start offset: 0x00081214
			// Variables:
		// 		int a; // $v1
		// 		int b; // $a0
		/* end block 1.1 */
		// End offset: 0x0008127C
		// End Line: 131

		/* begin block 1.2 */
			// Start line: 133
			// Start offset: 0x0008127C
			// Variables:
		// 		long deepestNormal[4]; // stack offset -208
		// 		long deepestLever[4]; // stack offset -192
		// 		long deepestPoint[4]; // stack offset -176
		// 		int lift; // $s5
		// 		int count; // $a0
		// 		int friToUse; // $s6
		// 		struct SVECTOR *carDisp; // $a1

			/* begin block 1.2.1 */
				// Start line: 156
				// Start offset: 0x00081314
				// Variables:
			// 		long pointPos[4]; // stack offset -160
			// 		long surfacePoint[4]; // stack offset -144
			// 		long surfaceNormal[4]; // stack offset -128
			// 		long lever[4]; // stack offset -112
			// 		int newLift; // $a0
			/* end block 1.2.1 */
			// End offset: 0x00081410
			// End Line: 196

			/* begin block 1.2.2 */
				// Start line: 201
				// Start offset: 0x00081428
				// Variables:
			// 		long pointVel[4]; // stack offset -112
			// 		long reaction[4]; // stack offset -96
			// 		int strikeVel; // $a2
			// 		int componant; // $t3
			// 		static int frictionLimit[6]; // offset 0x0

				/* begin block 1.2.2.1 */
					// Start line: 209
					// Start offset: 0x00081428
					// Variables:
				// 		int lever_dot_n; // $v1
				// 		int twistY; // $v0
				// 		int displacementsquared; // $a0
				// 		int denom; // $a0
				/* end block 1.2.2.1 */
				// End offset: 0x00081428
				// End Line: 209

				/* begin block 1.2.2.2 */
					// Start line: 226
					// Start offset: 0x00081630
					// Variables:
				// 		int loss; // $v1
				// 		int limit; // $a1
				/* end block 1.2.2.2 */
				// End offset: 0x0008166C
				// End Line: 230

				/* begin block 1.2.2.3 */
					// Start line: 235
					// Start offset: 0x000816B8

					/* begin block 1.2.2.3.1 */
						// Start line: 237
						// Start offset: 0x000816CC
						// Variables:
					// 		struct VECTOR direction; // stack offset -80
					/* end block 1.2.2.3.1 */
					// End offset: 0x000816CC
					// End Line: 237

					/* begin block 1.2.2.3.2 */
						// Start line: 242
						// Start offset: 0x0008170C
						// Variables:
					// 		struct VECTOR direction; // stack offset -64
					/* end block 1.2.2.3.2 */
					// End offset: 0x00081744
					// End Line: 244
				/* end block 1.2.2.3 */
				// End offset: 0x0008179C
				// End Line: 249
			/* end block 1.2.2 */
			// End offset: 0x0008179C
			// End Line: 250

			/* begin block 1.2.3 */
				// Start line: 256
				// Start offset: 0x0008186C
				// Variables:
			// 		struct VECTOR offset; // stack offset -112
			/* end block 1.2.3 */
			// End offset: 0x00081944
			// End Line: 269
		/* end block 1.2 */
		// End offset: 0x00081944
		// End Line: 270
	/* end block 1 */
	// End offset: 0x0008198C
	// End Line: 282

	/* begin block 2 */
		// Start line: 196
	/* end block 2 */
	// End Line: 197

	/* begin block 3 */
		// Start line: 211
	/* end block 3 */
	// End Line: 212

int impulse;

// [D]
void StepOneCar(_CAR_DATA *cp)
{
	static int frictionLimit[6] = {
		0x3ED000, 0x13A1000,
		0x75C6000, 0x13A1000, 
		0x11F30, 0x11F14
	};

	int iVar1;
	CAR_COSMETICS *car_cos;
	uint uVar3;
	int iVar4;
	long *puVar5;
	int iVar6;
	long *puVar7;
	long *piVar8;
	long *piVar9;
	long *piVar10;
	long *piVar11;
	int iVar12;
	int iVar13;
	SVECTOR *pSVar14;
	int friToUse;
	CAR_LOCALS _cl;
	long deepestNormal[4];
	long deepestLever[4];
	long deepestPoint[4];
	long pointPos[4];
	long surfacePoint[4];
	long surfaceNormal[4];
	long lever[4];
	long reaction[4];
	VECTOR direction;
	VECTOR partdir;
	_sdPlane *SurfacePtr;

	if (cp->controlType == 0)
		return;

	

	SurfacePtr = NULL;
	_cl.aggressive = handlingType[cp->hndType].aggressiveBraking;
	_cl.extraangulardamping = 0;

	iVar12 = 0;
	do {
		_cl.vel[iVar12] = cp->st.n.linearVelocity[iVar12];
		_cl.avel[iVar12] = cp->st.n.angularVelocity[iVar12];
		cp->st.n.fposition[iVar12] = (cp->st.n.fposition[iVar12] & 0xF) + cp->hd.where.t[iVar12] * 16;

		iVar12++;
	} while (iVar12 < 3);

	cp->hd.acc[0] = 0;
	cp->hd.acc[1] = -7456; // apply gravity
	cp->hd.acc[2] = 0;

	iVar12 = FIXEDH(_cl.vel[0]);
	iVar4 = FIXEDH(_cl.vel[2]);

	if (iVar12 < 0)
		iVar12 = -iVar12;

	if (iVar4 < 0)
		iVar4 = -iVar4;

	if (iVar12 < iVar4)
		iVar4 = iVar4 + iVar12 / 2;
	else
		iVar4 = iVar12 + iVar4 / 2;

	car_cos = cp->ap.carCos;
	iVar12 = 0;

	cp->hd.speed = iVar4;

	gte_SetRotMatrix(&cp->hd.where);
	gte_SetTransMatrix(&cp->hd.where);

	iVar4 = 12;

	if (cp->hd.where.m[1][1] > 0x800 && (iVar4 = 4, cp->controlType == 2))
	{
		iVar4 = (cp->totalDamage != 0) << 2;
	}

	iVar13 = iVar4 - 1;
	pSVar14 = car_cos->cPoints + iVar13;
	while (iVar13 >= 0)
	{
		gte_ldv0(pSVar14);

		gte_rtv0tr();

		gte_stlvnl(pointPos);

		lever[0] = pointPos[0] - cp->hd.where.t[0];
		lever[1] = pointPos[1] - cp->hd.where.t[1];
		lever[2] = pointPos[2] - cp->hd.where.t[2];

		FindSurfaceD2((VECTOR *)pointPos, (VECTOR *)surfaceNormal, (VECTOR *)&surfacePoint, &SurfacePtr);

		if((surfacePoint[1] - pointPos[1]) - 1 < 799)
		{
			iVar4 = FIXEDH((surfacePoint[1] - pointPos[1]) * surfaceNormal[1]);

			if (iVar12 < iVar4)
			{
				friToUse = 0;

				deepestNormal[0] = surfaceNormal[0];
				deepestNormal[1] = surfaceNormal[1];
				deepestNormal[2] = surfaceNormal[2];

				deepestLever[0] = lever[0];
				deepestLever[1] = lever[1];
				deepestLever[2] = lever[2];

				deepestPoint[0] = surfacePoint[0];
				deepestPoint[1] = surfacePoint[1];
				deepestPoint[2] = surfacePoint[2];

				iVar12 = iVar4;

				if (iVar13 > 3)
					friToUse = 3;
			}
		}

		iVar13--;
		pSVar14--;
	}

	if (iVar12 != 0)
	{
		reaction[0] = FIXEDH(_cl.avel[1] * deepestLever[2] - _cl.avel[2] * deepestLever[1]) + _cl.vel[0];
		reaction[1] = FIXEDH(_cl.avel[2] * deepestLever[0] - _cl.avel[0] * deepestLever[2]) + _cl.vel[1];
		reaction[2] = FIXEDH(_cl.avel[0] * deepestLever[1] - _cl.avel[1] * deepestLever[0]) + _cl.vel[2];

		iVar4 = FIXEDH(deepestLever[0] * deepestNormal[0] + deepestLever[1] * deepestNormal[1] + deepestLever[2] * deepestNormal[2]);
		iVar4 = FIXEDH(((deepestLever[0] * deepestLever[0] + deepestLever[1] * deepestLever[1] + deepestLever[2] * deepestLever[2]) - iVar4 * iVar4) * car_cosmetics[cp->ap.model].twistRateY) + 4096;

		iVar13 = 2;
		impulse = (((reaction[0] >> 6) * (deepestNormal[0] >> 6) + (reaction[1] >> 6) * (deepestNormal[1] >> 6) + (reaction[2] >> 6) * (deepestNormal[2] >> 6)) / iVar4) * -2048;

		piVar11 = (long*)&direction.vz;
		piVar10 = deepestNormal + 2;
		piVar9 = reaction + 2;

		piVar8 = (long*)frictionLimit + friToUse;

		do {
			iVar6 = *piVar8;
			iVar4 = *piVar9 * 67;
			iVar1 = -*piVar8;

			if (iVar4 <= iVar6)
			{
				iVar6 = iVar4;

				if(iVar4 < iVar1)
					iVar6 = iVar1;
			}

			*piVar11-- = FIXEDH(impulse * *piVar10 - iVar6);
			piVar10--;
			piVar9--;
			piVar8++;	// [A] ASan bug fix
			iVar13--;
		} while (-1 < iVar13);
		
		if (20000 < impulse) 
		{
			if (gNight == 1)
			{
				partdir.vx = 0;
				partdir.vy = 0x32;
				partdir.vz = 0;

				Setup_Sparks((VECTOR *)&deepestPoint, &partdir, 15, 1);
			}
			else
			{
				partdir.vx = 0;
				partdir.vy = 0x28;
				partdir.vz = 0;

				Setup_Debris((VECTOR *)&deepestPoint, &partdir, 10, 0);
			}

			if (SurfacePtr && (SurfacePtr->surface != 9) && (SurfacePtr->surface != 6))
			{
				iVar4 = GetPlayerId(cp);
				CollisionSound((char)iVar4, cp, (impulse / 6 + (impulse >> 0x1f) >> 3) - (impulse >> 0x1f), 0);
			}
		}

		cp->hd.acc[0] += direction.vx;
		cp->hd.acc[1] += direction.vy;
		cp->hd.acc[2] += direction.vz;

		cp->hd.aacc[0] += FIXEDH(deepestLever[1] * direction.vz - deepestLever[2] * direction.vy);
		cp->hd.aacc[1] += FIXEDH(deepestLever[2] * direction.vx - deepestLever[0] * direction.vz);
		cp->hd.aacc[2] += FIXEDH(deepestLever[0] * direction.vy - deepestLever[1] * direction.vx);

		if (iVar12 != 0) 
		{
			reaction[0] = FIXEDH(iVar12 * deepestNormal[0]);
			reaction[1] = FIXEDH(iVar12 * deepestNormal[1]);
			reaction[2] = FIXEDH(iVar12 * deepestNormal[2]);

			cp->hd.where.t[0] += reaction[0];
			cp->hd.where.t[1] += reaction[1];
			cp->hd.where.t[2] += reaction[2];

			cp->st.n.fposition[0] += reaction[0] * 16;
			cp->st.n.fposition[1] += reaction[1] * 16;
			cp->st.n.fposition[2] += reaction[2] * 16;

			gte_SetTransMatrix(&cp->hd.where);

			_cl.extraangulardamping = 1;

			if (120 < iVar12) 
				cp->st.n.linearVelocity[1] = 0;
		}
	}

	AddWheelForcesDriver1(cp, &_cl);
	ConvertTorqueToAngularAcceleration(cp, &_cl);

	cp->hd.mayBeColliding = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ GetFrictionScalesDriver1(struct _CAR_DATA *cp /*$t0*/, struct CAR_LOCALS *cl /*$a1*/, int *frontFS /*$a2*/, int *rearFS /*$a3*/)
 // line 288, offset 0x0008198c
	/* begin block 1 */
		// Start line: 289
		// Start offset: 0x0008198C
		// Variables:
	// 		struct _HANDLING_TYPE *hp; // $t2

		/* begin block 1.1 */
			// Start line: 306
			// Start offset: 0x00081A1C
			// Variables:
		// 		int q; // $v1
		/* end block 1.1 */
		// End offset: 0x00081A98
		// End Line: 314

		/* begin block 1.2 */
			// Start line: 387
			// Start offset: 0x00081DC8
			// Variables:
		// 		int traction; // $a0
		/* end block 1.2 */
		// End offset: 0x00081E20
		// End Line: 393
	/* end block 1 */
	// End offset: 0x00081E20
	// End Line: 394

	/* begin block 2 */
		// Start line: 800
	/* end block 2 */
	// End Line: 801

	/* begin block 3 */
		// Start line: 807
	/* end block 3 */
	// End Line: 808

// [D]
void GetFrictionScalesDriver1(_CAR_DATA *cp, CAR_LOCALS *cl, int *frontFS, int *rearFS)
{
	unsigned char bVar1;
	int iVar2;
	int iVar3;
	_HANDLING_TYPE* hp;

	hp = &handlingType[cp->hndType];

	if (cp->thrust < 0)
		*frontFS = 1453;
	else if (cp->thrust < 1)
		*frontFS = 937;
	else
		*frontFS = 820;

	iVar2 = cp->hd.autoBrake;

	if (cp->wheelspin == 0 && hp->autoBrakeOn != 0 && 0 < iVar2 && (0 < cp->hd.wheel_speed))
	{
		iVar3 = iVar2 << 1;

		if (iVar2 > 13) 
		{
			iVar2 = 13;
			iVar3 = 26;
		}

		*frontFS = *frontFS + (iVar3 + iVar2) * 15;

		if (hp->autoBrakeOn == 2)
		{
			while (FrameCnt != 0x78654321) 
			{
				trap(0x400);
			}
		}
	}

	if ((((cp->thrust < 0) && (0xa3d7 < cp->hd.wheel_speed)) && (cp->hndType == 0)) ||
		(((cp->controlType == 2 && (cp->ai.c.thrustState == 3)) && (cp->ai.c.ctrlState != 9))))
	{
		cp->hd.wheel[3].locked = 1;
		cp->hd.wheel[2].locked = 1;
		cp->hd.wheel[1].locked = 1;
		cp->hd.wheel[0].locked = 1;
	}
	else 
	{
		cp->hd.wheel[3].locked = 0;
		cp->hd.wheel[2].locked = 0;
		cp->hd.wheel[1].locked = 0;
		cp->hd.wheel[0].locked = 0;
	}

	if (cp->handbrake == 0) 
	{
		if (cp->wheelspin != 0)
			*frontFS = *frontFS + 600;
	}
	else 
	{
		if (-1 < cp->thrust) 
			cp->thrust = 0;

		if (cp->hd.wheel_speed < 1)
			*frontFS = *frontFS - 375;
		else 
			*frontFS = *frontFS + 656;

		cp->hd.wheel[1].locked = 1;
		cp->hd.wheel[3].locked = 1;
		cp->wheelspin = 0;
	}

	if ((cp->hd.wheel_speed < 0) && (-1 < cp->thrust) && (cp->handbrake == 0))
	{
		*frontFS = *frontFS - 400;
	}

	*rearFS = 0x780 - *frontFS;

	if (cp->wheelspin !=  0)
	{
		cp->thrust = FIXED(cp->ap.carCos->powerRatio * 5000);
	}

	if ((cp->thrust < 0) && (0xa3d7 < cp->hd.wheel_speed) && (cl->aggressive != 0))
	{
		*frontFS = FixFloorSigned(*frontFS * 10, 3);
		*rearFS = FixFloorSigned(*rearFS * 10, 3);
	}
	else 
	{
		if (cp->hd.wheel[0].onGrass == 0) 
			*frontFS = FixFloorSigned(*frontFS * 36 - *frontFS, 5);
		else
			*frontFS = FixFloorSigned(*frontFS * 40 - *frontFS, 5);
	}

	*frontFS = FixFloorSigned(*frontFS * hp->frictionScaleRatio, 5);
	*rearFS = FixFloorSigned(*rearFS * hp->frictionScaleRatio, 5);

	if ((cp->hndType == 5) && (cp->ai.l.dstate == 5))
	{
		*frontFS = (*frontFS * 3) / 2;
		*rearFS = (*rearFS * 3) / 2;
	}

	int traction = cp->ap.carCos->traction;

	if (traction != 0x1000)
	{
		*frontFS = FIXEDH(*frontFS * traction);
		*rearFS = FIXEDH(*rearFS * traction);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ConvertTorqueToAngularAcceleration(struct _CAR_DATA *cp /*$a0*/, struct CAR_LOCALS *cl /*$t5*/)
 // line 412, offset 0x00081e20
	/* begin block 1 */
		// Start line: 413
		// Start offset: 0x00081E20
		// Variables:
	// 		long nose[4]; // stack offset -16
	// 		int zd; // $a3
	// 		int i; // $t4
	// 		int twistY; // $t0
	// 		int twistZ; // $v1
	/* end block 1 */
	// End offset: 0x00081F50
	// End Line: 439

	/* begin block 2 */
		// Start line: 1035
	/* end block 2 */
	// End Line: 1036

	/* begin block 3 */
		// Start line: 1036
	/* end block 3 */
	// End Line: 1037

	/* begin block 4 */
		// Start line: 1055
	/* end block 4 */
	// End Line: 1056

	/* begin block 5 */
		// Start line: 1065
	/* end block 5 */
	// End Line: 1066

// [D]
void ConvertTorqueToAngularAcceleration(_CAR_DATA *cp, CAR_LOCALS *cl)
{
	int twistY;
	int twistZ;
	int zd;
	int i;

	twistY = car_cosmetics[cp->ap.model].twistRateY;
	twistZ = car_cosmetics[cp->ap.model].twistRateZ;

	i = 0;

	zd = FIXEDH(cp->hd.where.m[0][2] * cp->hd.aacc[0] + cp->hd.where.m[1][2] * cp->hd.aacc[1] + cp->hd.where.m[2][2] * cp->hd.aacc[2]);

	do {

		cp->hd.aacc[i] = cp->hd.aacc[i] * twistY + FIXEDH(cp->hd.where.m[i][2] * (twistZ - twistY) * zd - cl->avel[i] * 128);

		if (cl->extraangulardamping == 1)
			cp->hd.aacc[i] -= FixFloorSigned(cl->avel[i], 3);

		i++;
	} while (i < 3);
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddWheelForcesDriver1(struct _CAR_DATA *cp /*$s2*/, struct CAR_LOCALS *cl /*$s7*/)
 // line 442, offset 0x00081f50
	/* begin block 1 */
		// Start line: 443
		// Start offset: 0x00081F50
		// Variables:
	// 		int oldSpeed; // $v1
	// 		int frictionScale; // $fp
	// 		int frontFS; // stack offset -96
	// 		int rearFS; // stack offset -92
	// 		int i; // stack offset -84
	// 		int cdx; // stack offset -80
	// 		int cdz; // stack offset -76
	// 		int sdx; // stack offset -72
	// 		int sdz; // stack offset -68
	// 		int friction_coef; // $s6
	// 		struct CAR_COSMETICS *car_cos; // stack offset -64
	// 		struct _sdPlane *SurfacePtr; // stack offset -88
	// 		int player_id; // stack offset -60

		/* begin block 1.1 */
			// Start line: 469
			// Start offset: 0x000820A4
			// Variables:
		// 		int oldCompression; // $s5
		// 		int newCompression; // $s3
		// 		int susForce; // $s0
		// 		long wheelPos[4]; // stack offset -176
		// 		long surfacePoint[4]; // stack offset -160
		// 		long surfaceNormal[4]; // stack offset -144

			/* begin block 1.1.1 */
				// Start line: 488
				// Start offset: 0x00082140
				// Variables:
			// 		short typ; // $v1
			/* end block 1.1.1 */
			// End offset: 0x000821D8
			// End Line: 497

			/* begin block 1.1.2 */
				// Start line: 513
				// Start offset: 0x00082284
				// Variables:
			// 		int iVar17; // $s1
			/* end block 1.1.2 */
			// End offset: 0x0008231C
			// End Line: 525

			/* begin block 1.1.3 */
				// Start line: 537
				// Start offset: 0x00082380
				// Variables:
			// 		struct VECTOR force; // stack offset -128
			// 		long pointVel[4]; // stack offset -112
			// 		int lfx; // $a2
			// 		int lfz; // $t2
			// 		int sidevel; // $t0
			// 		int slidevel; // $t1

				/* begin block 1.1.3.1 */
					// Start line: 554
					// Start offset: 0x0008248C
				/* end block 1.1.3.1 */
				// End offset: 0x000824F0
				// End Line: 559

				/* begin block 1.1.3.2 */
					// Start line: 592
					// Start offset: 0x00082630
					// Variables:
				// 		int hack; // $v0
				// 		int hx; // $v0
				// 		int hz; // $v1
				/* end block 1.1.3.2 */
				// End offset: 0x00082630
				// End Line: 592

				/* begin block 1.1.3.3 */
					// Start line: 645
					// Start offset: 0x000828F0
					// Variables:
				// 		int a; // $v1
				/* end block 1.1.3.3 */
				// End offset: 0x00082928
				// End Line: 648
			/* end block 1.1.3 */
			// End offset: 0x00082A04
			// End Line: 671
		/* end block 1.1 */
		// End offset: 0x00082ADC
		// End Line: 679
	/* end block 1 */
	// End offset: 0x00082BD0
	// End Line: 694

	/* begin block 2 */
		// Start line: 1168
	/* end block 2 */
	// End Line: 1169

	/* begin block 3 */
		// Start line: 1172
	/* end block 3 */
	// End Line: 1173

// [D]
void AddWheelForcesDriver1(_CAR_DATA *cp, CAR_LOCALS *cl)
{
	int oldCompression;
	short sVar1;
	long lVar2;
	int uVar3;
	int newCompression;
	int iVar4;
	int iVar5;
	int local_v0_1748;
	int local_v0_1852;
	int _angle;
	bool bVar6;
	int angle;
	int iVar7;
	int uVar8;
	int iVar9;
	int lfx;
	int local_t0_1700;
	int sidevel;
	int slidevel;
	int lfz;
	int susForce;
	int chan;
	WHEEL* wheel;
	int friction_coef;
	int oldSpeed;
	long wheelPos[4];
	long surfacePoint[4];
	long surfaceNormal[4];
	VECTOR force;
	long pointVel[4];
	int frontFS;
	int rearFS;
	_sdPlane* SurfacePtr;
	int i;
	int cdx;
	int cdz;
	int sdx;
	int sdz;
	CAR_COSMETICS* car_cos;
	int player_id;

	oldSpeed = cp->hd.speed * 3 >> 1;

	if (oldSpeed < 0x20)
		oldSpeed = oldSpeed * -72 + 3696;
	else
		oldSpeed = 1424 - oldSpeed;

	uVar3 = cp->hd.direction;
	SurfacePtr = NULL;
	uVar8 = uVar3 & 0xfff;
	uVar3 = uVar3 + (int)cp->wheel_angle & 0xfff;

	cdx = (int)rcossin_tbl[uVar8 * 2];
	cdz = (int)rcossin_tbl[uVar8 * 2 + 1];
	sdx = (int)rcossin_tbl[uVar3 * 2];
	sdz = (int)rcossin_tbl[uVar3 * 2 + 1];

	player_id = GetPlayerId(cp);
	car_cos = &car_cosmetics[cp->ap.model];

	GetFrictionScalesDriver1(cp, cl, &frontFS, &rearFS);
	cp->hd.front_vel = 0;
	cp->hd.rear_vel = 0;

	if (oldSpeed > 3300)
		oldSpeed = 3300;

	i = 3;
	wheel = cp->hd.wheel + 3;
	do {
		gte_ldv0(&car_cos->wheelDisp[i]);

		gte_rtv0tr();
		gte_stlvnl(wheelPos);

		newCompression = FindSurfaceD2((VECTOR*)&wheelPos, (VECTOR*)&surfaceNormal, (VECTOR*)&surfacePoint, &SurfacePtr);

		friction_coef = (newCompression * (32400 - wetness) >> 15) + 500;

		if (SurfacePtr != NULL)
			wheel->onGrass = SurfacePtr->surface == 4;
		else
			wheel->onGrass = false;

		if (SurfacePtr)
		{
			switch (SurfacePtr->surface)
			{
				case 4:
				case 6:
				case 9:
				case 11:
					wheel->surface = 0x80;
					break;
				default:
					wheel->surface = 0;
			}

			switch (SurfacePtr->surface)
			{
				case 8:
					wheel->surface |= 2;
					break;
				case 6:
				case 9:
					wheel->surface |= 1;
					break;
				case 11:
					wheel->surface |= 3;
					break;
			}
		}
		else
		{
			wheel->surface = 0;
		}

		oldCompression = wheel->susCompression;
		newCompression = FIXEDH((surfacePoint[1] - wheelPos[1]) * surfaceNormal[1]) + 14;

		if (newCompression < 0)
			newCompression = 0;
	
		if (newCompression > 800)
			newCompression = 12;

		if (cp->controlType == 1) 
		{
			chan = newCompression - oldCompression;

			if (chan < 0)
				chan = oldCompression - newCompression;

			if (chan > 12 && (i & 1U) != 0)
			{
				chan = GetFreeChannel();
				if (NumPlayers > 1 && NoPlayerControl == 0) 
					SetPlayerOwnsChannel(chan, player_id);

				Start3DSoundVolPitch(chan, 1, 5, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -2500, 400);
				SetChannelPosition3(chan, (VECTOR*)cp->hd.where.t, NULL, -2500, 400, 0);
			}

			if (newCompression < 85)
			{
				if (newCompression > 48) 
					SetPadVibration(*cp->ai.padid, 3);
			}
			else 
			{
				SetPadVibration(*cp->ai.padid, 2);
			}
		}

		if (newCompression > 42)
			newCompression = 42;

		if (newCompression == 0 && oldCompression == 0) 
		{
			wheel->susCompression = 0;
		}
		else
		{
			wheelPos[2] = wheelPos[2] - cp->hd.where.t[2];
			wheelPos[1] = wheelPos[1] - cp->hd.where.t[1];
			wheelPos[0] = wheelPos[0] - cp->hd.where.t[0];

			force.vz = 0;
			force.vx = 0;

			pointVel[0] = FIXEDH(cl->avel[1] * wheelPos[2] - cl->avel[2] * wheelPos[1]) + cl->vel[0];
			pointVel[2] = FIXEDH(cl->avel[0] * wheelPos[1] - cl->avel[1] * wheelPos[0]) + cl->vel[2];

			susForce = newCompression * 230 - oldCompression * 100;

			if (wheel->locked == 0) 
			{
				if ((i & 1U) == 0) 
				{
					lfz = -sdx;
					lfx = sdz;
				}
				else 
				{
					lfz = -cdx;
					lfx = cdz;
				}
			}
			else 
			{
				uVar3 = ratan2(pointVel[0] >> 6, pointVel[2] >> 6);

				lfz = (int)rcossin_tbl[(uVar3 & 0xfff) * 2 + 1];

				iVar4 = pointVel[0];
				if (pointVel[0] < 0)
					iVar4 = -pointVel[0];

				iVar5 = pointVel[2];
				if (pointVel[2] < 0)
					iVar5 = -pointVel[2];

				lfx = (int)rcossin_tbl[(uVar3 & 0xfff) * 2];

				if (iVar4 + iVar5 < 8000) 
				{
					surfaceNormal[0] = 0;
					surfaceNormal[1] = 0x1000;
					surfaceNormal[2] = 0;
				}
			}

			iVar9 = FixFloorSigned(pointVel[0], 6) * FixFloorSigned(lfx, 6) + FixFloorSigned(pointVel[2], 6) * FixFloorSigned(lfz, 6);

			slidevel = FixFloorSigned(oldSpeed, 6) * FixFloorSigned(iVar9, 6);

			if (slidevel < 0)
				slidevel = -slidevel;

			if (iVar9 < 0xc351) 
			{
				if (iVar9 < -50000)
				{
				LAB_00082604:
					local_t0_1700 = -12500;
				}
				else 
				{
					local_t0_1700 = FIXEDH(oldSpeed * iVar9);
					if (12500 < local_t0_1700)
						goto LAB_000825f4;

					if (local_t0_1700 < -12500)
						goto LAB_00082604;
				}
			}
			else 
			{
			LAB_000825f4:
				local_t0_1700 = 0x30d4;
			}

			if ((i & 1U) == 0)
			{
				local_v0_1748 = frontFS * local_t0_1700 + 0x800;
				sidevel = local_v0_1748 >> 0xc;
				if (wheel->locked == 0)
				{
					if (cp->controlType == 3)
					{
						force.vx = sdx * cp->thrust;
						force.vz = sdz * cp->thrust;
					}
				}
				else 
				{
					sidevel = (local_v0_1748 >> 0xd) + sidevel >> 1;
					local_v0_1852 = FixFloorSigned(FIXEDH(-sidevel * lfx) * sdz - FIXEDH(-sidevel * lfz) * sdx, 11);
					force.vx = local_v0_1852 * sdz;
					force.vz = -local_v0_1852 * sdx;
				}

				if (cp->hd.front_vel < slidevel)
					cp->hd.front_vel = slidevel;

			}
			else
			{
				if (wheel->locked == 0)
				{
					sidevel = FIXEDH(rearFS * local_t0_1700);

					if (handlingType[cp->hndType].autoBrakeOn != 0 && 0 < sidevel * cp->wheel_angle) 
						cp->hd.autoBrake = -1;

					force.vx = -lfz * cp->thrust;
					force.vz = lfx * cp->thrust;
				}
				else 
				{
					sidevel = FixHalfRound(frontFS * local_t0_1700, 14);
				}

				if (cp->hd.rear_vel < slidevel)
					cp->hd.rear_vel = slidevel;
			}

			force.vx = force.vx + (susForce * surfaceNormal[0] - sidevel * lfx) - cl->vel[0] * 12;
			force.vz = force.vz + (susForce * surfaceNormal[2] - sidevel * lfz) - cl->vel[2] * 12;

			if ((wheel->surface & 7) == 1) 
			{
				force.vx = force.vx - cl->vel[0] * 75;
				force.vz = force.vz - cl->vel[2] * 75;
			}

			angle = (int)cp->hd.where.m[1][1];

			if (angle < 0x800)
			{
				angle = 0x1000 - angle;

				if (angle < 0x1001)
					_angle = 0x1000 - FIXEDH(angle * angle);
				else
					_angle = 0;

				friction_coef = FIXEDH(friction_coef * _angle);
			}

			if (surfaceNormal[1] < 0xccc)
				friction_coef = friction_coef * surfaceNormal[1] * 5 >> 0xe;

			force.vy = FIXEDH(susForce * surfaceNormal[1] - cl->vel[1] * 12);
			force.vx = FIXEDH(force.vx) * friction_coef >> 0xc;
			force.vz = FIXEDH(force.vz) * friction_coef >> 0xc;

			if (cp->controlType == 3) 
			{
				if (gCopDifficultyLevel == 2)
					wheelPos[1] = FixFloorSigned(wheelPos[1] * 12, 5);
				else
					wheelPos[1] = FixFloorSigned(wheelPos[1] * 19, 5);
			}

			cp->hd.acc[0] += force.vx;
			cp->hd.acc[1] += force.vy;
			cp->hd.acc[2] += force.vz;
			cp->hd.aacc[0] += FIXEDH(wheelPos[1] * force.vz - wheelPos[2] * force.vy);
			cp->hd.aacc[1] += FIXEDH(wheelPos[2] * force.vx - wheelPos[0] * force.vz);
			cp->hd.aacc[2] += FIXEDH(wheelPos[0] * force.vy - wheelPos[1] * force.vx);

			wheel->susCompression = newCompression;
		}
		wheel--;
		i--;
	} while (-1 < i);

	if (cp->hd.wheel[1].susCompression == 0 && cp->hd.wheel[3].susCompression == 0)
	{
		uVar3 = 0x1a0000;
		if (cp->thrust < 1) 
		{
			uVar3 = 0;
			if (-1 < cp->thrust)
				goto LAB_00082b9c;

			uVar3 = 0xffed0000;
		}
		uVar3 = uVar3 | 0x4000;
	}
	else 
	{
		uVar3 = FixFloorSigned(cl->vel[0], 6) * FixFloorSigned(cdx,  6) + FixFloorSigned(cl->vel[2], 6) * FixFloorSigned(cdz, 6);
	}

LAB_00082b9c:
	cp->hd.wheel_speed = uVar3;
}





