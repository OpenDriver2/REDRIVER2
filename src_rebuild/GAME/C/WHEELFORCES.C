#include "THISDUST.H"
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
	_CAR_DATA *cp;
	_CAR_DATA **pp_Var1;
	_CAR_DATA **pp_Var2;

	pp_Var2 = active_car_list + num_active_cars;
	pp_Var1 = active_car_list;

	while (pp_Var1 < pp_Var2) 
	{
		cp = *pp_Var1;
		pp_Var1 = pp_Var1 + 1;

		StepOneCar(cp);
	}

	pp_Var1 = active_car_list;

	while (pp_Var1 < pp_Var2)
	{
		cp = *pp_Var1;
		pp_Var1 = pp_Var1 + 1;
		ControlCarRevs(cp);
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
		0x3ED000, 0x13A1000, 0x75C6000, 0x13A1000, 0x11F30, 0x11F14
	};

	int iVar1;
	CAR_COSMETICS *pCVar2;
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
	int unaff_s6;
	long *plVar15;
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

	iVar12 = 2;
	plVar15 = cp->hd.where.t;
	puVar7 = (long *)(_cl.vel + 2);
	puVar5 = (long *)(cp->st.v + 2);

	SurfacePtr = NULL;
	_cl.aggressive = handlingType[cp->hndType].aggressiveBraking;
	_cl.extraangulardamping = 0;

	_cl.vel[0] = cp->st.n.linearVelocity[0];
	_cl.vel[1] = cp->st.n.linearVelocity[1];
	_cl.vel[2] = cp->st.n.linearVelocity[2];
	_cl.vel[3] = cp->st.n.linearVelocity[3];
	_cl.avel[0] = cp->st.n.angularVelocity[0];
	_cl.avel[1] = cp->st.n.angularVelocity[1];
	_cl.avel[2] = cp->st.n.angularVelocity[2];
	_cl.avel[3] = cp->st.n.angularVelocity[3];

	cp->hd.acc[0] = 0;
	cp->hd.acc[1] = -7456; // apply gravity
	cp->hd.acc[2] = 0;

	iVar12 = FIXED(_cl.vel[0]);
	iVar4 = FIXED(_cl.vel[2]);

	if (iVar12 < 0) {
		iVar12 = -iVar12;
	}
	if (iVar4 < 0) {
		iVar4 = -iVar4;
	}
	if (iVar12 < iVar4) {
		iVar4 = iVar4 + iVar12 / 2;
	}
	else {
		iVar4 = iVar12 + iVar4 / 2;
	}

	pCVar2 = cp->ap.carCos;
	iVar12 = 0;

	cp->hd.speed = iVar4;

	gte_SetRotMatrix(&cp->hd.where);
	gte_SetTransMatrix(&cp->hd.where);

	iVar4 = 12;

	if ((0x800 < cp->hd.where.m[1][1]) && (iVar4 = 4, cp->controlType == 2)) 
	{
		iVar4 = (cp->totalDamage != 0) << 2;
	}

	iVar13 = iVar4-1;
	if (iVar4 != 0) 
	{
		pSVar14 = pCVar2->cPoints + iVar13;

		do {
			gte_ldv0(pSVar14);
			//setCopReg(2, in_zero, *(undefined4 *)pSVar14);
			//setCopReg(2, in_at, *(undefined4 *)&pSVar14->vz);

			docop2(0x480012);

			gte_stlvnl(pointPos);

			lever[0] = pointPos[0] - cp->hd.where.t[0];
			lever[1] = pointPos[1] - cp->hd.where.t[1];
			lever[2] = pointPos[2] - cp->hd.where.t[2];

			FindSurfaceD2((VECTOR *)pointPos, (VECTOR *)surfaceNormal, (VECTOR *)&surfacePoint, &SurfacePtr);

			if((surfacePoint[1] - pointPos[1]) - 1 < 799)
			{
				iVar4 = FIXED((surfacePoint[1] - pointPos[1]) * surfaceNormal[1]);

				if (iVar12 < iVar4)
				{
					unaff_s6 = 0;
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
					if (3 < iVar13)
					{
						unaff_s6 = 3;
					}
				}
			}

			iVar13 = iVar13 + -1;
			pSVar14 = pSVar14 + -1;
		} while (iVar13 != -1);
	}

	if (iVar12 != 0)
	{
		reaction[0] = FIXED(_cl.avel[1] * deepestLever[2] - _cl.avel[2] * deepestLever[1]) + _cl.vel[0];
		reaction[1] = FIXED(_cl.avel[2] * deepestLever[0] - _cl.avel[0] * deepestLever[2]) + _cl.vel[1];
		reaction[2] = FIXED(_cl.avel[0] * deepestLever[1] - _cl.avel[1] * deepestLever[0]) + _cl.vel[2];

		iVar4 = FIXED(deepestLever[0] * deepestNormal[0] + deepestLever[1] * deepestNormal[1] + deepestLever[2] * deepestNormal[2]);
		iVar4 = FIXED(((deepestLever[0] * deepestLever[0] + deepestLever[1] * deepestLever[1] + deepestLever[2] * deepestLever[2]) - iVar4 * iVar4) * car_cosmetics[cp->ap.model].twistRateY) + 4096;

		iVar13 = 2;
		impulse = (((reaction[0] / 64) * (deepestNormal[0] / 64) + (reaction[1] / 64) * (deepestNormal[1] / 64) + (reaction[2] / 64) * (deepestNormal[2] / 64)) / iVar4) * -2048;

		piVar11 = (long*)&direction.vz;
		piVar10 = deepestNormal + 2;
		piVar9 = reaction + 2;
		piVar8 = (long*)frictionLimit + unaff_s6;

		do {
			iVar6 = *piVar8;
			iVar4 = *piVar9 * 67;
			iVar1 = -iVar6;

			if ((iVar4 <= iVar6) && (iVar6 = iVar4, iVar4 < iVar1)) 
				iVar6 = iVar1;

			iVar4 = *piVar10;
			piVar10 = piVar10 + -1;
			piVar9 = piVar9 + -1;
			piVar8 = piVar8 + -1;
			iVar13 = iVar13 + -1;
			*piVar11 = FIXED(impulse * iVar4 - iVar6);
			piVar11 = piVar11-1;
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

		cp->hd.aacc[0] += FIXED(deepestLever[1] * direction.vz - deepestLever[2] * direction.vy);
		cp->hd.aacc[1] += FIXED(deepestLever[2] * direction.vx - deepestLever[0] * direction.vz);
		cp->hd.aacc[2] += FIXED(deepestLever[0] * direction.vy - deepestLever[1] * direction.vx);

		if (iVar12 != 0) 
		{
			reaction[0] = FIXED(iVar12 * deepestNormal[0]);
			reaction[1] = FIXED(iVar12 * deepestNormal[1]);
			reaction[2] = FIXED(iVar12 * deepestNormal[2]);

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

	bVar1 = cp->hndType;
	if (cp->thrust < 0)
	{
		iVar2 = 0x5ad;
	}
	else 
	{
		iVar2 = 0x334;
		if (cp->thrust < 1) 
			iVar2 = 0x3a9;
	}

	*frontFS = iVar2;

	if ((((cp->wheelspin == 0) && (handlingType[cp->hndType].autoBrakeOn != 0)) && (iVar2 = cp->hd.autoBrake, 0 < iVar2)) && (0 < cp->hd.wheel_speed)) 
	{
		iVar3 = iVar2 << 1;
		if (0xd < iVar2) 
		{
			iVar2 = 0xd;
			iVar3 = 0x1a;
		}
		*frontFS = *frontFS + (iVar3 + iVar2) * 0xf;
		if (handlingType[cp->hndType].autoBrakeOn == 2) 
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
		{
			*frontFS = *frontFS + 600;
		}
	}
	else 
	{
		if (-1 < cp->thrust) 
			cp->thrust = 0;

		if (cp->hd.wheel_speed < 1)
		{
			iVar2 = *frontFS + -0x177;
		}
		else 
		{
			iVar2 = *frontFS + 0x290;
		}

		*frontFS = iVar2;
		cp->hd.wheel[1].locked = 1;
		cp->hd.wheel[3].locked = 1;
		cp->wheelspin = 0;
	}

	if ((cp->hd.wheel_speed < 0) && (-1 < cp->thrust) && (cp->handbrake == 0))
	{
		*frontFS = *frontFS + -400;
	}

	*rearFS = 0x780 - *frontFS;

	if (cp->wheelspin !=  0)
	{
		cp->thrust = FIXED(cp->ap.carCos->powerRatio * 5000);
	}

	if ((cp->thrust < 0) && (0xa3d7 < cp->hd.wheel_speed) && (cl->aggressive != 0))
	{
		iVar2 = *frontFS * 10;

		if (iVar2 < 0) 
			iVar2 = iVar2 + 7;

		*frontFS = iVar2 >> 3;

		iVar2 = *rearFS * 10;
		if (iVar2 < 0)
			iVar2 = iVar2 + 7;

		*rearFS = iVar2 >> 3;
	}
	else 
	{
		if (cp->hd.wheel[0].onGrass == 0) 
		{
			iVar3 = *frontFS;
			iVar2 = iVar3 * 0x24;
		}
		else
		{
			iVar3 = *frontFS;
			iVar2 = iVar3 * 0x28;
		}

		iVar2 = iVar2 - iVar3;
		if (iVar2 < 0) 
			iVar2 = iVar2 + 0x1f;

		*frontFS = iVar2 >> 5;
	}

	iVar2 = *frontFS * handlingType[bVar1].frictionScaleRatio;
	if (iVar2 < 0)
		iVar2 = iVar2 + 0x1f;

	*frontFS = iVar2 >> 5;
	iVar2 = *rearFS * handlingType[bVar1].frictionScaleRatio;

	if (iVar2 < 0)
		iVar2 = iVar2 + 0x1f;

	*rearFS = iVar2 >> 5;

	if ((cp->hndType == 5) && (cp->ai.l.dstate == 5))
	{
		*frontFS = (*frontFS * 3) / 2;
		*rearFS = (*rearFS * 3) / 2;
	}

	iVar2 = cp->ap.carCos->traction;

	if (iVar2 != 0x1000) 
	{
		*frontFS = FIXED(*frontFS * iVar2);
		*rearFS = FIXED(*rearFS * iVar2);
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
	short sVar1;
	short sVar2;
	short sVar3;
	short sVar4;
	short sVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	uint uVar10;
	int iVar11;
	long *piVar12;
	long *piVar13;
	short *psVar14;
	int iVar15;

	sVar1 = cp->hd.where.m[0][2];
	sVar2 = cp->hd.where.m[1][2];
	sVar3 = cp->hd.where.m[2][2];
	iVar6 = cp->hd.aacc[0];
	iVar7 = cp->hd.aacc[1];
	iVar8 = cp->hd.aacc[2];

	uVar10 = cp->ap.model;

	sVar4 = car_cosmetics[uVar10].twistRateY;
	sVar5 = car_cosmetics[uVar10].twistRateZ;

	iVar15 = 2;
	piVar13 = &cl->avel[2];

	psVar14 = &cp->hd.where.m[2][2];
	piVar12 = cp->hd.aacc + 2;

	do {
		iVar11 = *piVar12 * sVar4 + FIXED(*psVar14 * (sVar5 - sVar4) * FIXED(sVar1 * iVar6 + sVar2 * iVar7 + sVar3 * iVar8) - *piVar13 * 0x80);
		*piVar12 = iVar11;

		if (cl->extraangulardamping == 1)
		{
			iVar9 = *piVar13;
			*piVar12 = iVar11 - (iVar9 >> 3);
		}

		piVar13 = piVar13 + -1;
		psVar14 = psVar14 + -3;
		iVar15 = iVar15 + -1;
		piVar12 = piVar12 + -1;

	} while (-1 < iVar15);
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
#if 0
	// THIS IS ALMOST CORRECT

	// Has problems:
	//					some unimplemented code
	int oldCompression;
	short sVar1;
	long lVar2;
	VECTOR *wheelPosPtr2;
	uint uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	bool bVar7;
	int iVar8;
	uint uVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int chan;
	int newCompression;
	WHEEL *wh;
	long wheelPos[4];
	long surfacePoint[4];
	long surfaceNormal[4];
	VECTOR force;
	long pointVel[4];
	int frontFS;
	int rearFS;
	_sdPlane *SurfacePtr;
	int i;
	int cdx;
	int cdz;
	int sdx;
	int sdz;
	CAR_COSMETICS *car_cos;
	int player_id;

	int frictionScale;	// fp
	int oldSpeed;

	oldSpeed = cp->hd.speed * 3 >> 1;

	if (oldSpeed < 32)
		frictionScale = oldSpeed * -72 + 3696;
	else 
		frictionScale = 0x590 - oldSpeed;

	uVar3 = cp->hd.direction;

	SurfacePtr = NULL;

	uVar9 = uVar3 & 0xfff;
	uVar3 = uVar3 + cp->wheel_angle & 0xfff;

	cdx = rcossin_tbl[uVar9 * 2];
	cdz = rcossin_tbl[uVar9 * 2 + 1];
	sdx = rcossin_tbl[uVar3 * 2];
	sdz = rcossin_tbl[uVar3 * 2 + 1];

	player_id = GetPlayerId(cp);
	car_cos = &car_cosmetics[cp->ap.model];

	GetFrictionScalesDriver1(cp, cl, &frontFS, &rearFS);

	cp->hd.front_vel = 0;
	cp->hd.rear_vel = 0;

	if (frictionScale > 3300)
		frictionScale = 3300;

	i = 3;
	wh = &cp->hd.wheel[3];

	do {
		gte_ldv0(&car_cos->wheelDisp[i]);

		docop2(0x480012);

		gte_stlvnl(wheelPos);

		int friction_coef = FindSurfaceD2((VECTOR*)wheelPos, (VECTOR*)surfaceNormal, (VECTOR*)surfacePoint, &SurfacePtr);

		friction_coef = ((friction_coef * (32400 - wetness)) >> 15) + 500;	// s6, iVar4

		wh->onGrass = SurfacePtr && SurfacePtr->surface == 4;

		if(SurfacePtr)
		{
			switch (SurfacePtr->surface)
			{
				case 4:
				case 6:
				case 9:
				case 11:
					wh->surface = 0x80;
					break;
				default:
					wh->surface = 0;
			}

			switch (SurfacePtr->surface)
			{
				case 8:
					wh->surface |= 2;
					break;
				case 6:
				case 9:
					wh->surface |= 1;
					break;
				case 11:
					wh->surface |= 3;
					break;
			}
		}
		else
		{
			wh->surface = 0;
		}

		oldCompression = wh->susCompression;
		newCompression = FIXED((surfacePoint[1] - wheelPos[1]) * surfaceNormal[1]) + 14;

		if (newCompression < 0)
			newCompression = 0;

		if (newCompression > 800)
			newCompression = 12;

		// play curb hit sound on player
		if (cp->controlType == 1)
		{
			int diff = newCompression - oldCompression;

			if (diff < 0)
				diff = oldCompression - newCompression;

			if (diff > 12 && ((i & 1U) != 0))
			{
				chan = GetFreeChannel();

				if ((1 < NumPlayers) && (NoPlayerControl == 0)) 
					SetPlayerOwnsChannel(chan, (char)player_id);

				Start3DSoundVolPitch(chan, 1, 5, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -0x9c4, 400);
				SetChannelPosition3(chan, (VECTOR *)cp->hd.where.t, NULL, -0x9c4, 400, 0);
			}

			if (newCompression < 0x55)
			{
				if (newCompression > 48) 
					SetPadVibration(*cp->ai.padid, 3);
			}
			else 
				SetPadVibration(*cp->ai.padid, 2);
		}

		// clamp to not make it too jumpy
		if (newCompression > 42)
			newCompression = 42;

		if ((newCompression == 0) && (oldCompression == 0))
		{
			wh->susCompression = 0; // not on ground
		}
		else 
		{
			wheelPos[2] = wheelPos[2] - cp->hd.where.t[2];
			wheelPos[1] = wheelPos[1] - cp->hd.where.t[1];
			wheelPos[0] = wheelPos[0] - cp->hd.where.t[0];

			force.vz = 0;
			force.vx = 0;

			// seems like OK
			pointVel[0] = FIXED(cl->avel[1] * wheelPos[2] - cl->avel[2] * wheelPos[1]) + cl->vel[0]; //((cl->avel[1] * wheelPos[2] - cl->avel[2] * wheelPos[1]) + 2048) / 4096 + cl->vel[0];
			pointVel[1] = FIXED(cl->avel[2] * wheelPos[0] - cl->avel[0] * wheelPos[2]) + cl->vel[1]; //((cl->avel[2] * wheelPos[0] - cl->avel[0] * wheelPos[2]) + 2048) / 4096 + cl->vel[1];
			pointVel[2] = FIXED(cl->avel[0] * wheelPos[1] - cl->avel[1] * wheelPos[0]) + cl->vel[2]; //((cl->avel[0] * wheelPos[1] - cl->avel[1] * wheelPos[0]) + 2048) / 4096 + cl->vel[2];

			// equivalents?
			//int susForce = (((((((newCompression << 3) - newCompression) << 2) + newCompression) << 2) - newCompression) << 1) - 
			//	((((oldCompression << 1) + oldCompression) << 3) + oldCompression << 2);
			int susForce = newCompression * 230 - oldCompression * 100;

			int lfx = 0;	// iVar12, a2
			int lfz = 0;	// iVar11, t2

			if (wh->locked) 
			{
				int a = ratan2(pointVel[0] / 64, pointVel[2] / 64);
				lfx = rcossin_tbl[(a & 0xfff) * 2 + 1];
				lfz = rcossin_tbl[(uVar3 & 0xfff) * 2];

				if (abs(pointVel[0]) + abs(pointVel[2]) < 8000)
				{
					surfaceNormal[0] = 0;
					surfaceNormal[1] = 0x1000;
					surfaceNormal[2] = 0;
				}
			}
			else 
			{
				if ((i & 1U) == 0)
				{
					lfx = -sdx;
					lfz = sdz;
				}
				else 
				{
					lfx = -cdx;
					lfz = cdz;
				}
			}

			int sidevel;

			{
				int _lfx = lfx;
				int _lfz = lfz;

				int _pvx = pointVel[0];
				int _pvz = pointVel[2];

				/*
				if (_pvx < 0)
					_pvx += 0x3F;

				if (_pvz < 0)
					_pvz += 0x3F;

				if (_lfx < 0)
					_lfx += 0x3F;

				if (_lfx < 0)
					_lfx += 0x3F;*/

				sidevel = (_pvx / 64) * (_lfz / 64) + (_pvz / 64) * (_lfx / 64);
			}

			int slidevel;
			{
				int _fs = frictionScale;
				int _sv = sidevel;
				/*
				if (_fs < 0)
					_fs += 0x3F;

			
				if (_sv < 0)
					_sv += 0x3F;*/

				slidevel = (_fs / 64) * (_sv / 64);

				if (slidevel < 0)
					slidevel = -slidevel;
			}

			if (sidevel < 50000)
			{
				if(sidevel > -50000)
				{
					sidevel = FIXED(frictionScale * sidevel);
	
					if (sidevel > 12500)
						sidevel = 12500;
					if (sidevel < -12500)
						sidevel = -12500;
				}
				else
					sidevel = -12500;
			}
			else
				sidevel = 12500;

			//lfx = frontFS * lfx + 0x2000 >> 0xE;
			//lfz = frontFS * lfz + 0x2000 >> 0xE;

			//lfx			= iVar12
			//lfz			= iVar11
			//pointVel[0]	= chan;
			//pointVel[2]	= iVar10

			if ((i & 1U) == 0) 
			{
				sidevel = FIXED(frontFS * sidevel);

				if (wh->locked == 0) 
				{
					if (cp->controlType == 3) 
					{
						force.vx = sdx * cp->thrust;
						force.vz = sdz * cp->thrust;
					}
				}
				else 
				{
					//sidevel = (sidevel >> 0xd) + iVar10 >> 1;
					//iVar5 = (((-sidevel * lfz + 0x800 >> 0xc) * sdz - (-sidevel * lfx + 0x800 >> 0xc) * sdx) + 1024) / 2048;

					//force.vx = iVar5 * sdz;
					//force.vz = -iVar5 * sdx;
				}

				if (cp->hd.front_vel < slidevel)
					cp->hd.front_vel = slidevel;
			}
			else
			{
				if (wh->locked == 0) 
				{
					sidevel = FIXED(rearFS * sidevel);

					if ((handlingType[cp->hndType].autoBrakeOn != 0) && (0 < sidevel * cp->wheel_angle))
						cp->hd.autoBrake = -1;

					force.vx = -lfx * cp->thrust;
					force.vz = lfz * cp->thrust;
				}
				else 
				{
					sidevel = (frontFS * sidevel + 8192) / 16384;
				}

				if (cp->hd.rear_vel < slidevel)
					cp->hd.rear_vel = slidevel;
			}

			// add the driving forces
			force.vx += (susForce * surfaceNormal[0] - sidevel * lfz) - cl->vel[0] * 12;
			force.vy = susForce * surfaceNormal[1] - cl->vel[1] * 12;
			force.vz += (susForce * surfaceNormal[2] - sidevel * lfx) - cl->vel[2] * 12;

			//force.vx += (susForce * surfaceNormal[0] - sidevel * lfz) - (((cl->vel[0] << 1) + cl->vel[0]) << 2);
			//force.vy = susForce * surfaceNormal[1] - (((cl->vel[1] << 1) + cl->vel[1]) << 2);
			//force.vz += (susForce * surfaceNormal[2] - sidevel * lfx) - (((cl->vel[2] << 1) + cl->vel[2]) << 2);

			if((wh->surface & 7) == 1)
			{
				force.vx -= cl->vel[0] * 75;
				force.vz -= cl->vel[2] * 75;
			}

			int a = cp->hd.where.m[1][1];

			if (a < 2048)
			{
				a = 4096 - a;
				if (a < 0x1001)
					a = 4096 - FIXED(a * a);
				else
					a = 0;

				friction_coef = FIXED(friction_coef * a);
			}

			if (surfaceNormal[1] < 3276)
				friction_coef = friction_coef * surfaceNormal[1] * 5 >> 14;

			// last force addition
			force.vy = FIXED(force.vy);
			force.vx = FIXED(force.vx) * FIXED(friction_coef);
			force.vz = FIXED(force.vz) * FIXED(friction_coef);

			// make cops not flip to over
			if (cp->controlType == 3)
			{
				if (gCopDifficultyLevel == 2) 
					wheelPos[1] *= 12;
				else
					wheelPos[1] *= 19;

				if (wheelPos[1] < 0)
					wheelPos[1] +=  31;

				wheelPos[1] = wheelPos[1] >> 5;
			}
			
			// apply
			cp->hd.acc[0] += force.vx;
			cp->hd.acc[1] += force.vy;
			cp->hd.acc[2] += force.vz;

			cp->hd.aacc[0] += FIXED(wheelPos[1] * force.vz - wheelPos[2] * force.vy);
			cp->hd.aacc[1] += FIXED(wheelPos[2] * force.vx - wheelPos[0] * force.vz);
			cp->hd.aacc[2] += FIXED(wheelPos[0] * force.vy - wheelPos[1] * force.vx);

			wh->susCompression = newCompression;
		}

		wh = wh--;
		i--;
	} while (-1 < i);
	if ((cp->hd.wheel[1].susCompression == '\0') && (cp->hd.wheel[3].susCompression == '\0')) {
		uVar3 = 0x1a0000;
		if (cp->thrust < 1) {
			uVar3 = 0;
			if (-1 < cp->thrust) goto LAB_00082b9c;
			uVar3 = 0xffed0000;
		}
		uVar3 = uVar3 | 0x4000;
	}
	else {
		iVar8 = cl->vel[0];
		iVar4 = cl->vel[2];
		uVar3 = (iVar8 >> 6) * (cdx >> 6) + (iVar4 >> 6) * (cdz >> 6);
	}
LAB_00082b9c:
	cp->hd.wheel_speed = uVar3;
	return;
#else
	int oldCompression;
	short sVar1;
	long lVar2;
	VECTOR *wheelPosPtr2;
	int uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	bool bVar7;
	int iVar8;
	int uVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int chan;
	int newCompression;
	WHEEL *pWVar14;
	long wheelPos[4];
	long surfacePoint[4];
	long surfaceNormal[4];
	VECTOR force;
	long pointVel[4];
	int frontFS;
	int rearFS;
	_sdPlane *SurfacePtr;
	int i;
	int cdx;
	int cdz;
	int sdx;
	int sdz;
	CAR_COSMETICS *car_cos;
	int player_id;
	VECTOR *wheelPosPtr;
	VECTOR *surfacePointPtr;
	VECTOR *surfaceNormalPtr;
	_sdPlane **surfacePtrPtr;

	iVar8 = cp->hd.speed * 3 >> 1;
	if (iVar8 < 0x20) {
		iVar8 = iVar8 * -0x48 + 0xe70;
	}
	else {
		iVar8 = 0x590 - iVar8;
	}
	uVar3 = cp->hd.direction;
	SurfacePtr = NULL;
	uVar9 = uVar3 & 0xfff;
	uVar3 = uVar3 + cp->wheel_angle & 0xfff;
	cdx = rcossin_tbl[uVar9 * 2];
	cdz = rcossin_tbl[uVar9 * 2 + 1];
	sdx = rcossin_tbl[uVar3 * 2];
	sdz = rcossin_tbl[uVar3 * 2 + 1];
	player_id = GetPlayerId(cp);
	car_cos = car_cosmetics + (cp->ap).model;
	GetFrictionScalesDriver1(cp, cl, &frontFS, &rearFS);
	cp->hd.front_vel = 0;
	cp->hd.rear_vel = 0;
	if (0xce4 < iVar8) {
		iVar8 = 0xce4;
	}
	wheelPosPtr = (VECTOR *)wheelPos;
	surfaceNormalPtr = (VECTOR *)surfaceNormal;
	i = 3;
	surfacePointPtr = (VECTOR *)surfacePoint;
	surfacePtrPtr = &SurfacePtr;
	pWVar14 = cp->hd.wheel + 3;

	do {
		wheelPosPtr2 = wheelPosPtr;
		gte_ldv0(&car_cos->wheelDisp[i]);

		docop2(0x480012);
		gte_stlvnl(wheelPos);


		iVar4 = FindSurfaceD2(wheelPosPtr, surfaceNormalPtr, surfacePointPtr, surfacePtrPtr);
		bVar7 = false;
		iVar4 = (iVar4 * (0x7e90 - wetness) >> 0xf) + 500;
		if (SurfacePtr != NULL) 
		{
			bVar7 = SurfacePtr->surface == 4;
		}

		*(bool *)&pWVar14->onGrass = bVar7;
		if (SurfacePtr == NULL) 
		{
			pWVar14->surface = 0;
		}
		else 
		{
			sVar1 = SurfacePtr->surface;
			if ((((sVar1 == 4) || (sVar1 == 6)) || (sVar1 == 0xb)) || (sVar1 == 9))
			{
				pWVar14->surface = -0x80;
			}
			else {
				pWVar14->surface = 0;
			}
			if (sVar1 == 8) 
			{
				pWVar14->surface = pWVar14->surface | 2;
			}
			else 
			{
				if (sVar1 < 9)
				{
					if (sVar1 == 6) 
					{
					LAB_000821c4:
						pWVar14->surface = pWVar14->surface | 1;
					}
				}
				else 
				{
					if (sVar1 == 9) 
						goto LAB_000821c4;

					if (sVar1 == 0xb) 
					{
						pWVar14->surface = pWVar14->surface | 3;
					}
				}
			}
		}

		oldCompression = pWVar14->susCompression;
		uVar3 = oldCompression;
		chan = FIXED((surfacePoint[1] - wheelPos[1]) * surfaceNormal[1]) + 14;
		newCompression = chan;

		if (chan < 0)
			newCompression = 0;

		if (chan > 800)
			newCompression = 12;

		if (cp->controlType == 1) 
		{
			chan = newCompression - uVar3;
			if (chan < 0)
				chan = uVar3 - newCompression;

			if (chan > 12 && ((i & 1U) != 0)) 
			{
				chan = GetFreeChannel();

				if (NumPlayers > 1 && NoPlayerControl == 0)
					SetPlayerOwnsChannel(chan, player_id);
	
				Start3DSoundVolPitch(chan, 1, 5, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -2500, 400);
				SetChannelPosition3(chan, (VECTOR *)cp->hd.where.t, NULL, -0x9c4, 400, 0);
			}

			if (newCompression < 85) 
			{
				if (newCompression > 48)
				{
					SetPadVibration(*cp->ai.padid, 3);
				}
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
			pWVar14->susCompression = 0;
		}
		else 
		{
			wheelPos[2] = wheelPos[2] - cp->hd.where.t[2];
			wheelPos[1] = wheelPos[1] - cp->hd.where.t[1];
			wheelPos[0] = wheelPos[0] - cp->hd.where.t[0];

			force.vz = 0;
			force.vx = 0;

			chan = FIXED(cl->avel[1] * wheelPos[2] - cl->avel[2] * wheelPos[1]) + cl->vel[0];
			iVar10 = FIXED(cl->avel[0] * wheelPos[1] - cl->avel[1] * wheelPos[0]) + cl->vel[2];

			iVar13 = newCompression * 230 - uVar3 * 100;

			if (pWVar14->locked == 0) 
			{
				if ((i & 1U) == 0) 
				{
					iVar12 = -sdx;
					iVar11 = sdz;
				}
				else 
				{
					iVar12 = -cdx;
					iVar11 = cdz;
				}
			}
			else
			{
				uVar3 = ratan2(chan / 64, iVar10 / 64);
				iVar12 = rcossin_tbl[(uVar3 & 0xfff) * 2 + 1];
				iVar5 = chan;
				if (chan < 0)
					iVar5 = -chan;

				iVar6 = iVar10;
				if (iVar10 < 0)
					iVar6 = -iVar10;

				iVar11 = rcossin_tbl[(uVar3 & 0xfff) * 2];

				if (iVar5 + iVar6 < 8000) 
				{
					surfaceNormal[0] = 0;
					surfaceNormal[1] = 4096;
					surfaceNormal[2] = 0;
				}
			}

			iVar5 = iVar11;

			iVar6 = iVar12;

			iVar10 = (chan / 64) * (iVar5 / 64) + (iVar10 / 64) * (iVar6 / 64);
			chan = iVar8;

			iVar5 = iVar10;

			chan = (chan / 64) * (iVar5 / 64);
			if (chan < 0)
				chan = -chan;

			if (iVar10 < 50001) 
			{
				if (iVar10 < -50000)
				{
				LAB_00082604:
					iVar10 = -12500;
				}
				else 
				{
					iVar10 = FIXED(iVar8 * iVar10);
					if (iVar10 > 12500)
						goto LAB_000825f4;
					if (iVar10 < -12500) 
						goto LAB_00082604;
				}
			}
			else 
			{
			LAB_000825f4:
				iVar10 = 0x30d4;
			}

			if ((i & 1U) == 0) 
			{
				iVar5 = frontFS * iVar10;
				iVar10 = FIXED(iVar5);
				if (pWVar14->locked == 0)
				{
					if (cp->controlType == 3) 
					{
						force.vx = sdx * cp->thrust;
						force.vz = sdz * cp->thrust;
					}
				}
				else 
				{
					iVar10 = FIXED(iVar5) + iVar10 >> 1;
					iVar5 = FIXED(FIXED(-iVar10 * iVar11) * sdz - FIXED(-iVar10 * iVar12) * sdx);
					force.vx = iVar5 * sdz;
					force.vz = -iVar5 * sdx;
				}

				if (cp->hd.front_vel < chan)
					cp->hd.front_vel = chan;
			}
			else
			{
				if (pWVar14->locked == 0) 
				{
					iVar10 = FIXED(rearFS * iVar10);

					if (handlingType[cp->hndType].autoBrakeOn != 0 && (0 < iVar10 * cp->wheel_angle))
						cp->hd.autoBrake = -1;

					force.vx = -iVar12 * cp->thrust;
					force.vz = iVar11 * cp->thrust;
				}
				else 
				{
					iVar10 = (frontFS * iVar10) / 16384;
				}

				if (cp->hd.rear_vel < chan)
					cp->hd.rear_vel = chan;
			}

			force.vx = force.vx + (iVar13 * surfaceNormal[0] - iVar10 * iVar11) - cl->vel[0] * 12;
			force.vz = force.vz + (iVar13 * surfaceNormal[2] - iVar10 * iVar12) - cl->vel[2] * 12;

			if ((pWVar14->surface & 7) == 1) 
			{
				force.vx = force.vx - cl->vel[0] * 75;
				force.vz = force.vz - cl->vel[2] * 75;
			}

			chan = cp->hd.where.m[1][1];
			if (chan < 0x800) 
			{
				chan = 0x1000 - chan;
				if (chan < 0x1001) 
					chan = 0x1000 - FIXED(chan * chan);
				else
					chan = 0;

				iVar4 = FIXED(iVar4 * chan);
			}

			if (surfaceNormal[1] < 0xccc) 
				iVar4 = (iVar4 * surfaceNormal[1] * 5) >> 14;

			chan = FIXED(iVar13 * surfaceNormal[1] - cl->vel[1] * 12);
			iVar10 = FIXED(FIXED(force.vx) * iVar4);
			iVar4 = FIXED(FIXED(force.vz) * iVar4);

			if (cp->controlType == 3) 
			{
				if (gCopDifficultyLevel == 2) 
					iVar13 = wheelPos[1] * 12;
				else 
					iVar13 = wheelPos[1] * 19;

				wheelPos[1] = iVar13 / 32;
			}
			
			cp->hd.acc[0] += iVar10;
			cp->hd.acc[1] += chan;
			cp->hd.acc[2] += iVar4;

			cp->hd.aacc[0] += FIXED(wheelPos[1] * iVar4 - wheelPos[2] * chan);
			cp->hd.aacc[1] += FIXED(wheelPos[2] * iVar10 - wheelPos[0] * iVar4);
			cp->hd.aacc[2] += FIXED(wheelPos[0] * chan - wheelPos[1] * iVar10);

			pWVar14->susCompression = newCompression;
		}

		pWVar14--;
		i = i + -1;
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
		iVar8 = cl->vel[0];
		iVar4 = cl->vel[2];
		uVar3 = (iVar8 / 64) * (cdx / 64) + (iVar4 / 64) * (cdz / 64);
	}

	LAB_00082b9c:
	cp->hd.wheel_speed = uVar3;
#endif
}





