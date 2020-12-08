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
	// 		CAR_DATA **ppCar; // $s0
	// 		CAR_DATA **end; // $s1

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

// [D] [T]
void StepCars(void)
{
	CAR_DATA** ppCar;
	CAR_DATA** end;

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
// void /*$ra*/ StepOneCar(CAR_DATA *cp /*$s1*/)
 // line 98, offset 0x00081178
	/* begin block 1 */
		// Start line: 99
		// Start offset: 0x00081178
		// Variables:
	// 		CAR_LOCALS _cl; // stack offset -248
	// 		CAR_LOCALS *cl; // $s3
	// 		int i; // $s0
	// 		int speed; // $v1
	// 		sdPlane *SurfacePtr; // stack offset -48

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
		// 		LONGVECTOR deepestNormal; // stack offset -208
		// 		LONGVECTOR deepestLever; // stack offset -192
		// 		LONGVECTOR deepestPoint; // stack offset -176
		// 		int lift; // $s5
		// 		int count; // $a0
		// 		int friToUse; // $s6
		// 		SVECTOR *carDisp; // $a1

			/* begin block 1.2.1 */
				// Start line: 156
				// Start offset: 0x00081314
				// Variables:
			// 		LONGVECTOR pointPos; // stack offset -160
			// 		LONGVECTOR surfacePoint; // stack offset -144
			// 		LONGVECTOR surfaceNormal; // stack offset -128
			// 		LONGVECTOR lever; // stack offset -112
			// 		int newLift; // $a0
			/* end block 1.2.1 */
			// End offset: 0x00081410
			// End Line: 196

			/* begin block 1.2.2 */
				// Start line: 201
				// Start offset: 0x00081428
				// Variables:
			// 		LONGVECTOR pointVel; // stack offset -112
			// 		LONGVECTOR reaction; // stack offset -96
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
					// 		VECTOR direction; // stack offset -80
					/* end block 1.2.2.3.1 */
					// End offset: 0x000816CC
					// End Line: 237

					/* begin block 1.2.2.3.2 */
						// Start line: 242
						// Start offset: 0x0008170C
						// Variables:
					// 		VECTOR direction; // stack offset -64
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
			// 		VECTOR offset; // stack offset -112
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

// [D] [T]
void StepOneCar(CAR_DATA* cp)
{
	static int frictionLimit[6] = {
		0x3ED000, 0x178E000,
		0x3ED000, 0x13A1000,
		0x75C6000,0x13A1000
	};

	CAR_COSMETICS* car_cos;
	int friToUse;
	int lift;
	int a, b, speed;
	int count, i;
	CAR_LOCALS _cl;
	LONGVECTOR4 deepestNormal;
	LONGVECTOR4 deepestLever;
	LONGVECTOR4 deepestPoint;
	LONGVECTOR4 pointPos;
	LONGVECTOR4 surfacePoint;
	LONGVECTOR4 surfaceNormal;
	LONGVECTOR4 lever;
	LONGVECTOR4 reaction;
	VECTOR direction;
	sdPlane* SurfacePtr;

	if (cp->controlType == CONTROL_TYPE_NONE)
		return;

	SurfacePtr = NULL;
	_cl.aggressive = handlingType[cp->hndType].aggressiveBraking;
	_cl.extraangulardamping = 0;

	i = 0;
	do {
		_cl.vel[i] = cp->st.n.linearVelocity[i];
		_cl.avel[i] = cp->st.n.angularVelocity[i];
		cp->st.n.fposition[i] = (cp->st.n.fposition[i] & 0xF) + cp->hd.where.t[i] * 16;

		i++;
	} while (i < 3);

	cp->hd.acc[0] = 0;
	cp->hd.acc[1] = -7456; // apply gravity
	cp->hd.acc[2] = 0;

	// calculate car speed
	a = ABS(FIXEDH(_cl.vel[0]));
	b = ABS(FIXEDH(_cl.vel[2]));

	if (a < b)
		speed = b + a / 2;
	else
		speed = a + b / 2;

	car_cos = cp->ap.carCos;
	lift = 0;

	cp->hd.speed = speed;

	gte_SetRotMatrix(&cp->hd.where);
	gte_SetTransMatrix(&cp->hd.where);

	count = 12;

	if (cp->hd.where.m[1][1] > 0x800 && (count = 4, cp->controlType == CONTROL_TYPE_CIV_AI))
	{
		count = (cp->totalDamage != 0) << 2;
	}

	count--;

	// calculate lifting factor
	while (count >= 0)
	{
		gte_ldv0(&car_cos->cPoints[count]);

		gte_rtv0tr();

		gte_stlvnl(pointPos);

		lever[0] = pointPos[0] - cp->hd.where.t[0];
		lever[1] = pointPos[1] - cp->hd.where.t[1];
		lever[2] = pointPos[2] - cp->hd.where.t[2];

		FindSurfaceD2((VECTOR*)pointPos, (VECTOR*)surfaceNormal, (VECTOR*)&surfacePoint, &SurfacePtr);

		if ((surfacePoint[1] - pointPos[1]) - 1U < 799)
		{
			int newLift;

			newLift = FIXEDH((surfacePoint[1] - pointPos[1]) * surfaceNormal[1]);

			if (lift < newLift)
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

				lift = newLift;

				if (count > 3)
					friToUse = 3;
			}
		}

		count--;
	}

	// do lifting
	if (lift != 0)
	{
		int strikeVel; // $a2
		int componant; // $t3

		int lever_dot_n; // $v1
		int twistY; // $v0
		int displacementsquared; // $a0
		int denom; // $a0

		lever[0] = FIXEDH(_cl.avel[1] * deepestLever[2] - _cl.avel[2] * deepestLever[1]) + _cl.vel[0];
		lever[1] = FIXEDH(_cl.avel[2] * deepestLever[0] - _cl.avel[0] * deepestLever[2]) + _cl.vel[1];
		lever[2] = FIXEDH(_cl.avel[0] * deepestLever[1] - _cl.avel[1] * deepestLever[0]) + _cl.vel[2];

		twistY = car_cos->twistRateY;

		lever_dot_n = FIXEDH(deepestLever[0] * deepestNormal[0] + deepestLever[1] * deepestNormal[1] + deepestLever[2] * deepestNormal[2]);
		displacementsquared = FIXEDH(((deepestLever[0] * deepestLever[0] + deepestLever[1] * deepestLever[1] + deepestLever[2] * deepestLever[2]) - lever_dot_n * lever_dot_n) * twistY) + 4096;

		strikeVel = (lever[0] >> 6) * (deepestNormal[0] >> 6) + (lever[1] >> 6) * (deepestNormal[1] >> 6) + (lever[2] >> 6) * (deepestNormal[2] >> 6);
		impulse = (strikeVel / displacementsquared) * -2048;

		// apply friction
		componant = 2;
		do {
			int loss;
			int limit;

			limit = frictionLimit[friToUse + 2 - componant];
			loss = lever[componant] * 67;

			if (loss <= limit)
			{
				if (loss < -limit)
					limit = -limit;
				else
					limit = loss;
			}

			reaction[componant] = FIXEDH(impulse * deepestNormal[componant] - limit);
			componant--;
		} while (componant >= 0);

		if (impulse > 20000)
		{
			if (gNight == 1)
			{
				direction.vx = 0;
				direction.vy = 50;
				direction.vz = 0;

				Setup_Sparks((VECTOR*)&deepestPoint, &direction, 15, 1);
			}
			else
			{
				direction.vx = 0;
				direction.vy = 40;
				direction.vz = 0;

				Setup_Debris((VECTOR*)&deepestPoint, &direction, 10, 0);
			}

			if (SurfacePtr && (SurfacePtr->surface != 9) && (SurfacePtr->surface != 6))
			{
				CollisionSound(GetPlayerId(cp), cp, (impulse / 6 + (impulse >> 0x1f) >> 3) - (impulse >> 0x1f), 0);
			}
		}

		cp->hd.acc[0] += reaction[0];
		cp->hd.acc[1] += reaction[1];
		cp->hd.acc[2] += reaction[2];

		cp->hd.aacc[0] += FIXEDH(deepestLever[1] * reaction[2] - deepestLever[2] * reaction[1]);
		cp->hd.aacc[1] += FIXEDH(deepestLever[2] * reaction[0] - deepestLever[0] * reaction[2]);
		cp->hd.aacc[2] += FIXEDH(deepestLever[0] * reaction[1] - deepestLever[1] * reaction[0]);

		if (lift != 0)
		{
			lever[0] = FIXEDH(lift * deepestNormal[0]);
			lever[1] = FIXEDH(lift * deepestNormal[1]);
			lever[2] = FIXEDH(lift * deepestNormal[2]);

			cp->hd.where.t[0] += lever[0];
			cp->hd.where.t[1] += lever[1];
			cp->hd.where.t[2] += lever[2];

			cp->st.n.fposition[0] += lever[0] * 16;
			cp->st.n.fposition[1] += lever[1] * 16;
			cp->st.n.fposition[2] += lever[2] * 16;

			gte_SetTransMatrix(&cp->hd.where);

			_cl.extraangulardamping = 1;

			if (lift > 120)
				cp->st.n.linearVelocity[1] = 0;
		}
	}

	AddWheelForcesDriver1(cp, &_cl);
	ConvertTorqueToAngularAcceleration(cp, &_cl);

	cp->hd.mayBeColliding = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ GetFrictionScalesDriver1(CAR_DATA *cp /*$t0*/, CAR_LOCALS *cl /*$a1*/, int *frontFS /*$a2*/, int *rearFS /*$a3*/)
 // line 288, offset 0x0008198c
	/* begin block 1 */
		// Start line: 289
		// Start offset: 0x0008198C
		// Variables:
	// 		_HANDLING_TYPE *hp; // $t2

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

// [D] [T]
void GetFrictionScalesDriver1(CAR_DATA* cp, CAR_LOCALS* cl, int* frontFS, int* rearFS)
{
	unsigned char bVar1;
	int autoBrake;
	int q;
	_HANDLING_TYPE* hp;

	hp = &handlingType[cp->hndType];

	if (cp->thrust < 0)
		*frontFS = 1453;
	else if (cp->thrust < 1)
		*frontFS = 937;
	else
		*frontFS = 820;

	autoBrake = cp->hd.autoBrake;

	if (cp->wheelspin == 0 && hp->autoBrakeOn != 0 && autoBrake > 0 && cp->hd.wheel_speed > 0)
	{
		q = autoBrake << 1;

		if (autoBrake > 13)
		{
			autoBrake = 13;
			q = 26;
		}

		*frontFS += (q + autoBrake) * 15;

		if (hp->autoBrakeOn == 2)
		{
			while (FrameCnt != 0x78654321)
			{
				trap(0x400);
			}
		}
	}

	if ((cp->thrust < 0 && cp->hd.wheel_speed > 41943 && cp->hndType == 0) ||
		(cp->controlType == CONTROL_TYPE_CIV_AI && cp->ai.c.thrustState == 3 && cp->ai.c.ctrlState != 9))
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
			*frontFS += 600;
	}
	else
	{
		if (cp->thrust > -1)
			cp->thrust = 0;

		if (cp->hd.wheel_speed < 1)
			*frontFS -= 375;
		else
			*frontFS += 656;

		cp->hd.wheel[1].locked = 1;
		cp->hd.wheel[3].locked = 1;
		cp->wheelspin = 0;
	}

	if (cp->hd.wheel_speed < 0 && cp->thrust > -1 && cp->handbrake == 0)
	{
		*frontFS -= 400;
	}

	*rearFS = 0x780 - *frontFS;

	if (cp->wheelspin != 0)
	{
		cp->thrust = FIXEDH(cp->ap.carCos->powerRatio * 5000);
	}

	if (cp->thrust < 0 && cp->hd.wheel_speed > 41943 && cl->aggressive != 0)
	{
		*frontFS = (*frontFS * 10) / 8;
		*rearFS = (*rearFS * 10) / 8;
	}
	else
	{
		if (cp->hd.wheel[0].onGrass == 0)
			*frontFS = (*frontFS * 36 - *frontFS) / 32;
		else
			*frontFS = (*frontFS * 40 - *frontFS) / 32;
	}

	*frontFS = (*frontFS * hp->frictionScaleRatio) / 32;
	*rearFS = (*rearFS * hp->frictionScaleRatio) / 32;

	if ((cp->hndType == 5) && (cp->ai.l.dstate == 5))
	{
		*frontFS = (*frontFS * 3) / 2;
		*rearFS = (*rearFS * 3) / 2;
	}

	int traction = cp->ap.carCos->traction;

	if (traction != 4096)
	{
		*frontFS = FIXEDH(*frontFS * traction);
		*rearFS = FIXEDH(*rearFS * traction);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ConvertTorqueToAngularAcceleration(CAR_DATA *cp /*$a0*/, CAR_LOCALS *cl /*$t5*/)
 // line 412, offset 0x00081e20
	/* begin block 1 */
		// Start line: 413
		// Start offset: 0x00081E20
		// Variables:
	// 		LONGVECTOR nose; // stack offset -16
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

// [D] [T]
void ConvertTorqueToAngularAcceleration(CAR_DATA* cp, CAR_LOCALS* cl)
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
			cp->hd.aacc[i] -= cl->avel[i] / 8;

		i++;
	} while (i < 3);
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddWheelForcesDriver1(CAR_DATA *cp /*$s2*/, CAR_LOCALS *cl /*$s7*/)
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
	// 		CAR_COSMETICS *car_cos; // stack offset -64
	// 		sdPlane *SurfacePtr; // stack offset -88
	// 		int player_id; // stack offset -60

		/* begin block 1.1 */
			// Start line: 469
			// Start offset: 0x000820A4
			// Variables:
		// 		int oldCompression; // $s5
		// 		int newCompression; // $s3
		// 		int susForce; // $s0
		// 		LONGVECTOR wheelPos; // stack offset -176
		// 		LONGVECTOR surfacePoint; // stack offset -160
		// 		LONGVECTOR surfaceNormal; // stack offset -144

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
			// 		VECTOR force; // stack offset -128
			// 		LONGVECTOR pointVel; // stack offset -112
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

// [D] [T]
void AddWheelForcesDriver1(CAR_DATA* cp, CAR_LOCALS* cl)
{
	int oldCompression;
	int dir;
	int newCompression;
	int forcefac;
	int angle;
	int lfx, lfz;
	int sidevel;
	int slidevel;
	int susForce;
	int chan;
	WHEEL* wheel;
	int friction_coef;
	int oldSpeed;
	int wheelspd;
	LONGVECTOR4 wheelPos;
	LONGVECTOR4 surfacePoint;
	LONGVECTOR4 surfaceNormal;
	VECTOR force;
	LONGVECTOR4 pointVel;
	int frontFS;
	int rearFS;
	sdPlane* SurfacePtr;
	int i;
	int cdx;
	int cdz;
	int sdx;
	int sdz;
	CAR_COSMETICS* car_cos;
	int player_id;

	oldSpeed = cp->hd.speed * 3 >> 1;

	if (oldSpeed < 32)
		oldSpeed = oldSpeed * -72 + 3696;
	else
		oldSpeed = 1424 - oldSpeed;

	dir = cp->hd.direction;
	cdx = rcossin_tbl[(dir & 0xfff) * 2];
	cdz = rcossin_tbl[(dir & 0xfff) * 2 + 1];

	dir += cp->wheel_angle;
	sdx = rcossin_tbl[(dir & 0xfff) * 2];
	sdz = rcossin_tbl[(dir & 0xfff) * 2 + 1];

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
			wheel->onGrass = 0;

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

			// [A] indication of Event surface which means we can't add tyre tracks for that wheel
			if (SurfacePtr->surface - 16U < 16)
				wheel->surface |= 0x8;

			switch (SurfacePtr->surface)
			{
				case 8:
					wheel->surface |= 0x2;
					break;
				case 6:
				case 9:
					wheel->surface |= 0x1;
					break;
				case 11:
					wheel->surface |= 0x3;
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

		// play wheel collision sound
		// and apply vibration to player controller
		if (cp->controlType == CONTROL_TYPE_PLAYER)
		{
			if (ABS(newCompression - oldCompression) > 12 && (i & 1U) != 0)
			{
				chan = GetFreeChannel(0);
				if(chan > -1)
				{
					if (NumPlayers > 1 && NoPlayerControl == 0)
						SetPlayerOwnsChannel(chan, player_id);

					Start3DSoundVolPitch(chan, SOUND_BANK_SFX, 5, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -2500, 400);
					SetChannelPosition3(chan, (VECTOR*)cp->hd.where.t, NULL, -2500, 400, 0);
				}
			}

			if (newCompression >= 85)
				SetPadVibration(*cp->ai.padid, 2);
			else if (newCompression > 48)
				SetPadVibration(*cp->ai.padid, 3);
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

			// that's our spring
			susForce = newCompression * 230 - oldCompression * 100;

			if (wheel->locked)
			{
				dir = ratan2(pointVel[0] >> 6, pointVel[2] >> 6);

				lfx = rcossin_tbl[(dir & 0xfff) * 2];
				lfz = rcossin_tbl[(dir & 0xfff) * 2 + 1];

				if (ABS(pointVel[0]) + ABS(pointVel[2]) < 8000)
				{
					surfaceNormal[0] = 0;
					surfaceNormal[1] = 0x1000;
					surfaceNormal[2] = 0;
				}
			}
			else
			{
				if ((i & 1U) != 0)
				{
					lfz = -cdx;
					lfx = cdz;
				}
				else
				{
					lfz = -sdx;
					lfx = sdz;
				}
			}

			slidevel = (pointVel[0] / 64) * (lfx / 64) + (pointVel[2] / 64) * (lfz / 64);
			wheelspd = ABS((oldSpeed / 64) * (slidevel / 64));

			if (slidevel > 50000)
			{
				slidevel = 12500;
			}
			else if (slidevel < -50000)
			{
				slidevel = -12500;
			}
			else
			{
				slidevel = FIXEDH(oldSpeed * slidevel);

				if (slidevel > 12500)
					slidevel = 12500;

				if (slidevel < -12500)
					slidevel = -12500;
			}
			
			if ((i & 1U) != 0)
			{
				// rear wheels
				if (wheel->locked == 0)
				{
					sidevel = FIXEDH(rearFS * slidevel);

					if (handlingType[cp->hndType].autoBrakeOn != 0 && 0 < sidevel * cp->wheel_angle)
						cp->hd.autoBrake = -1;

					force.vx = -lfz * cp->thrust;
					force.vz = lfx * cp->thrust;
				}
				else
				{
					sidevel = FixHalfRound(frontFS * slidevel, 14);
				}

				if (cp->hd.rear_vel < wheelspd)
					cp->hd.rear_vel = wheelspd;
			}
			else
			{
				// front wheels
				sidevel = frontFS * slidevel + 0x800 >> 0xc;
				
				if (wheel->locked)
				{
					sidevel = (frontFS * slidevel + 0x800 >> 0xd) + sidevel >> 1;
					
					forcefac = FixHalfRound(FIXEDH(-sidevel * lfx) * sdz - FIXEDH(-sidevel * lfz) * sdx, 11);
					
					force.vx = forcefac * sdz;
					force.vz = -forcefac * sdx;
				}
				else
				{
					if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
					{
						force.vx = sdx * cp->thrust;
						force.vz = sdz * cp->thrust;
					}
				}

				if (cp->hd.front_vel < wheelspd)
					cp->hd.front_vel = wheelspd;

			}

			force.vx += (susForce * surfaceNormal[0] - sidevel * lfx) - cl->vel[0] * 12;
			force.vz += (susForce * surfaceNormal[2] - sidevel * lfz) - cl->vel[2] * 12;

			// apply speed reduction by water
			if ((wheel->surface & 7) == 1)
			{
				force.vx -= cl->vel[0] * 75;
				force.vz -= cl->vel[2] * 75;
			}

			angle = cp->hd.where.m[1][1];

			if (angle < 2048)
			{
				angle = 4096 - angle;

				if (angle <= 4096)
					angle = 4096 - FIXEDH(angle * angle);
				else
					angle = 0;

				friction_coef = FIXEDH(friction_coef * angle);
			}

			if (surfaceNormal[1] < 3276)
				friction_coef = friction_coef * surfaceNormal[1] * 5 >> 0xe;

			force.vy = FIXEDH(susForce * surfaceNormal[1] - cl->vel[1] * 12);
			force.vx = FIXEDH(force.vx) * friction_coef >> 0xc;
			force.vz = FIXEDH(force.vz) * friction_coef >> 0xc;

			// pursuer cars have more stability
			if (cp->controlType == CONTROL_TYPE_PURSUER_AI)
			{
				if (gCopDifficultyLevel == 2)
					wheelPos[1] = (wheelPos[1] * 12) / 32;
				else
					wheelPos[1] = (wheelPos[1] * 19) / 32;
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
	} while (i >= 0);

	if (cp->hd.wheel[1].susCompression == 0 && cp->hd.wheel[3].susCompression == 0)
	{
		if (cp->thrust >= 1)
			cp->hd.wheel_speed = 1703936 + 0x4000;
		else if (cp->thrust <= -1)
			cp->hd.wheel_speed = -1245184 + 0x4000;
		else
			cp->hd.wheel_speed = 0;
	}
	else
	{
		cp->hd.wheel_speed = cdz / 64 * (cl->vel[2] / 64) + cdx / 64 * (cl->vel[0] / 64);
	}
}



