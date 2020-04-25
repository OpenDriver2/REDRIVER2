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
#include "GTEREG.H"

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

	iVar12 = _cl.vel[0] + 0x800 / 4096;
	iVar4 = _cl.vel[2] + 0x800 / 4096;

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

			pointPos[0] = MAC1; // getCopReg(2, 0x19);
			pointPos[1] = MAC2; // getCopReg(2, 0x1a);
			pointPos[2] = MAC3; // getCopReg(2, 0x1b);

			lever[0] = pointPos[0] - cp->hd.where.t[0];
			lever[1] = pointPos[1] - cp->hd.where.t[1];
			lever[2] = pointPos[2] - cp->hd.where.t[2];

			FindSurfaceD2((VECTOR *)pointPos, (VECTOR *)surfaceNormal, (VECTOR *)&surfacePoint, &SurfacePtr);

			if((surfacePoint[1] - pointPos[1]) - 1 < 799)
			{
				iVar4 = ((surfacePoint[1] - pointPos[1]) * surfaceNormal[1] + 2048) / 4096;

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
		reaction[0] = ((_cl.avel[1] * deepestLever[2] - _cl.avel[2] * deepestLever[1]) + 2048) / 4096 + _cl.vel[0];
		reaction[1] = ((_cl.avel[2] * deepestLever[0] - _cl.avel[0] * deepestLever[2]) + 2048) / 4096 + _cl.vel[1];
		reaction[2] = ((_cl.avel[0] * deepestLever[1] - _cl.avel[1] * deepestLever[0]) + 2048) / 4096 + _cl.vel[2];

		iVar4 = (deepestLever[0] * deepestNormal[0] + deepestLever[1] * deepestNormal[1] + deepestLever[2] * deepestNormal[2] + 2048) / 4096;
		iVar4 = (((deepestLever[0] * deepestLever[0] + deepestLever[1] * deepestLever[1] + deepestLever[2] * deepestLever[2]) - iVar4 * iVar4) 
			* car_cosmetics[cp->ap.model].twistRateY + 2048) / 4096 + 4069;

		if (iVar4 == 0) 
		{
			trap(7);
		}

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
			*piVar11 = ((impulse * iVar4 - iVar6) + 0x800) / 4096;
			piVar11 = piVar11-1;
		} while (-1 < iVar13);
		
		if (20000 < impulse) 
		{
			if (gNight == 1)
			{
				partdir.vx = 0;
				partdir.vy = 0x32;
				partdir.vz = 0;

				Setup_Sparks((VECTOR *)&deepestPoint, &partdir, 0xf, 1);
			}
			else
			{
				partdir.vx = 0;
				partdir.vy = 0x28;
				partdir.vz = 0;

				Setup_Debris((VECTOR *)&deepestPoint, &partdir, 10, 0);
			}

			if ((SurfacePtr->surface != 9) && (SurfacePtr->surface != 6)) 
			{
				iVar4 = GetPlayerId(cp);
				CollisionSound((char)iVar4, cp, (impulse / 6 + (impulse >> 0x1f) >> 3) - (impulse >> 0x1f), 0);
			}
		}

		cp->hd.acc[0] += direction.vx;
		cp->hd.acc[1] += direction.vy;
		cp->hd.acc[2] += direction.vz;

		cp->hd.aacc[0] += ((deepestLever[1] * direction.vz - deepestLever[2] * direction.vy) + 2048) / 4096;
		cp->hd.aacc[1] += ((deepestLever[2] * direction.vx - deepestLever[0] * direction.vz) + 2048) / 4096;
		cp->hd.aacc[2] += ((deepestLever[0] * direction.vy - deepestLever[1] * direction.vx) + 2048) / 4096;

		if (iVar12 != 0) 
		{
			reaction[0] = (iVar12 * deepestNormal[0] + 2048) / 4096;
			reaction[1] = (iVar12 * deepestNormal[1] + 2048) / 4096;
			reaction[2] = (iVar12 * deepestNormal[2] + 2048) / 4096;

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

	if ((cp->hd.wheel_speed < 0) && (-1 < cp->thrust) && (cp->handbrake == '\0'))
	{
		*frontFS = *frontFS + -400;
	}

	*rearFS = 0x780 - *frontFS;

	if (cp->wheelspin !=  0)
	{
		cp->thrust = cp->ap.carCos->powerRatio * 5000 + 0x800 >> 0xc;
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
		*frontFS = *frontFS * iVar2 + 0x800 >> 0xc;
		*rearFS = *rearFS * iVar2 + 0x800 >> 0xc;
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
	piVar13 = cl->avel + 2;

	psVar14 = (short*)cp->hd.where.m + 8;
	piVar12 = cp->hd.aacc + 2;

	do {
		iVar11 = *piVar12 * (int)sVar4 +
			((int)*psVar14 *
			((int)sVar5 - (int)sVar4) * (sVar1 * iVar6 + sVar2 * iVar7 + sVar3 * iVar8 + 0x800 >> 0xc) + *piVar13 * -0x80 + 0x800) / 4096;
		*piVar12 = iVar11;

		if (cl->extraangulardamping == 1)
		{
			iVar9 = *piVar13;
			if (iVar9 < 0) {
				iVar9 = iVar9 + 7;
			}
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

void AddWheelForcesDriver1RE(_CAR_DATA *cp, CAR_LOCALS *cl)
{
#if 1
	int var_C0;// = -0xC0
	int var_BC;// = -0xBC
	int var_B8;// = -0xB8
	int var_B4;// = -0xB4
	int wheelPos[4];// = -0xB0
	int surfacePoint[4]; //= -0xA0
	int surfaceNormal[4]; //= -0x90
	VECTOR force;// = -0x80;
	int pointVel[4];// = -0x70;
	int frontFS;// = -0x60;
	int rearFS;// = -0x5C;
	_sdPlane* SurfacePtr;// = -0x58;
	int i;// = -0x54;
	int cdx;// = -0x50;
	int	cdz;// = -0x4C;
	int sdx;// = -0x48;
	int sdz;// = -0x44;
	CAR_COSMETICS* car_cos;// = -0x40;
	int var_3C;// = -0x3C;
	//int(*wheelPosPtr)[4];// = -0x38
	//int(*surfacePointPtr)[4];// = -0x34
	//int(*surfaceNormalPtr)[4];// = -0x30
	//_sdPlane** sdPlanePtr;// = -0x2C
	int var_28;// = -0x28;
	int var_24;// = -0x24;
	int var_20;// = -0x20;
	int var_1C;//= -0x1C;
	int var_18;// = -0x18;
	int var_14;// = -0x14;
	int var_10;// = -0x10;
	int var_C;// = -0xC;
	int var_8;// = -8;
	int var_4;// = -4;



	int v0, v1, v2, v3, t0, t1, t2, t3, t4, a0, a1, a2, a3, fp, s0, s1, s2, newCompression, oldCompression, s6;
	WHEEL* s4;

	//s2 = cp; // a0
	//s7 = cl; // a1

	v0 = cp->hd.speed;					// lw      $v0, CAR_DATA.hd.speed($s2)
	v1 = v0 << 1;						// sll     $v1, $v0, 1
	v1 += v0;							// addu    $v1, $v0
	v1 = v1 >> 1;						// sra     $v1, 1
	v0 = v1 < 0x20;						// slti    $v0, $v1, 0x20

	if (v0)	 // beqz    $v0, loc_82020
	{
		v0 = v1 << 3;					// sll     $v0, $v1, 3
		v0 += v1;						// addu    $v0, $v1
		v0 = v0 << 3;					// sll     $v0, 3
		v1 = 0x370;						// li      $v1, 0xE70
		fp = v1 - v0;					// subu    $fp, $v1, $v0
	}
	else
	{
		// loc_82020
		v0 = 0x590;						// li      $v0, 0x590
		fp = v0 - v1;					// subu    $fp, $v0, $v1
	}

loc_82028:
	v1 = (int)rcossin_tbl;				// la      $v1, rcossin_tbl
	v0 = cp->hd.direction;				// lw      $v0, _CAR_DATA.hd.direction($s2)
	a3 = (int)((char*)rcossin_tbl + 2);			//addiu   $a3, $v1, (rcossin_tbl + 2 - 0xA3878)
	SurfacePtr = NULL;					// sw      $zero, 0xD0 + SurfacePtr($sp)
	a2 = cp->wheel_angle;				// lh      $a2, _CAR_DATA.wheel_angle($s2)
	a1 = (v0 & 0xFFF) << 2;				// andi    $a1, $v0, 0xFFF
										// sll     $a1, 2
	t0 = a1 + v1;						// addu    $t0, $a1, $v1
	a1 += a3;							// addu    $a1, $a3
	v0 += a2;							// addu    $v0, $a2
	v0 = v0 & 0xFFF;					// andi    $v0, 0xFFF
	t0 = *(short*)t0; // lh      $t0, 0($t0)

	v0 = v0 << 2;						// sll     $v0, 2
	cdx = t0;							// sw      $t0, 0xD0 + cdx($sp)
	a1 = *(short*)a1; // lh      $a1, 0($a1)
	v1 += v0;							// addu    $v1, $v0, $v1
	cdz = a1;							// sw      $a1, 0xD0 + cdz($sp)
	v1 = *(short*)v1; // lh      $v1, 0($v1)
	v0 += a3;							// addu    $v0, $a3
	sdx = v1;							// sw      $v1, 0xD0 + sdx($sp)
	v0 = *(short*)v0; // lh      $v0, 0($v0)
		//move    $a0, $s2
		//jal     GetPlayerId
		//sw      $v0, 0xD0 + sdz($sp)
	sdz = v0;

	v0 = GetPlayerId(cp);
	//move    $a0, $s2
	//move    $a1, $s7
// addiu   $a2, $sp, 0xD0 + frontFS
	v1 = cp->ap.model;					// lbu     $v1, _CAR_DATA.ap.model($s2)
								// addiu   $a3, $sp, 0xD0 + rearFS
	var_3C = v0;						// sw      $v0, 0xD0 + var_3C($sp)
	v0 = v1 << 4;						// sll     $v0, $v1, 4
	v0 -= v1;							// subu    $v0, $v1
	v0 = v0 << 2;						// sll     $v0, 2
	v0 -= v1;							// subu    $v0, $v1
	v0 = v0 << 2;						// sll     $v0, 2
	v1 = (int)car_cosmetics;			// la      $v1, car_cosmetics

	v0 += v1;						// addu    $v0, $v1
	GetFrictionScalesDriver1(cp, cl, &frontFS, &rearFS); // jal     GetFrictionScalesDriver1
	car_cos = &car_cosmetics[cp->ap.model];		// sw      $v0, car_cos($sp)
	v0 = fp < 0xCE5;							// slti    $v0, $fp, 0xCE5
	cp->hd.front_vel = 0;						// sw      $zero, CAR_DATA.hd.front_vel($s2)
	cp->hd.rear_vel = 0;						// sw      $zero, CAR_DATA.hd.rear_vel($s2)

	if (v0 == 0)	//bnez    $v0, loc_820E0
	{
		fp = 0xCE4;								// li      $fp, 0xCE4
	}

	// loc_820E0:
		//v0 = 3;									// li      $v0, 3
		//v1 = (int)(wheelPos);					// addiu   $v1, $sp, 0xD0 + wheelPos
		//a0 = (int)surfaceNormal;				// addiu   $a0, $sp, 0xD0 + surfaceNormal
		//i = v0;									// sw      $v0, 0xD0 + i($sp)
		//v0 = (int)surfacePoint;					// addiu   $v0, $sp, 0xD0 + surfacePoint
		//wheelPosPtr = &wheelPos;							// sw      $v1, 0xD0 + var_38($sp)
		//v1 = (int)SurfacePtr;					// addiu   $v1, $sp, 0xD0 + SurfacePtr
		//s4 = cp->hd.wheel->susCompression;	// addiu   $s4, $s2, _CAR_DATA.hd.wheel.susCompression + 0xC
		//surfaceNormalPtr = &surfaceNormal;							// sw      $a0, 0xD0 + var_30($sp)
		//surfacePointPtr = &surfacePoint;							// sw      $v0, 0xD0 + var_34($sp)
		//sdPlanePtr = &SurfacePtr;				// sw      $v1, 0xD0 + var_2C($sp)

	i = 3;
	s4 = &cp->hd.wheel[i];
	while (i >= 0)
	{
		//loc_8210C:
				// lw      $a0, 0xD0 + i($sp)
				// lw      $v1, CAR_COSMETICS.cPoints.vz + 0x18($sp)
				// sll     $v0, $a0, 3
				// addiu   $v0, 0x48
				//addu    $v0, $v1, $v0
				//lwc2    $0, 0($v0)       # gte_ldv0
				//lwc2    $1, 4($v0)
		gte_ldv0(&car_cos->wheelDisp[i]);
		docop2(0x480012);
		//lw      $a0, 0xD0 + var_38($sp)
		//nop
		wheelPos[0] = MAC1;		// swc2    $25, 0($a0)      # MAC1
		wheelPos[1] = MAC2;		// swc2    $26, 4($a0)
		wheelPos[2] = MAC3;		// swc2    $27, 8($a0)

		//lw      $a0, 0xD0 + wheelPosPtr($sp)
		//lw      $a1, 0xD0 + surfaceNormalPtr($sp)
		//lw      $a2, 0xD0 + surfacePointPtr($sp)
		//lw      $a3, 0xD0 + sdPlanePtr($sp)
		//jal     FindSurfaceD2
		v0 = FindSurfaceD2((VECTOR*)wheelPos, (VECTOR*)surfaceNormal, (VECTOR*)surfacePoint, &SurfacePtr);

		//a0 = wetness;		// lw      $a0, wetness
		v1 = 32400;			// li      $v1, 0x7E90
		v1 -= wetness;		// subu    $v1, $a0
		v0 = v0 * v1;		//----------------mult    $v0, $v1
		v1 = 0;				// move    $v1, $zero
		//lw      $a0, 0xD0 + SurfacePtr($sp)
							//mflo    $v0
		v0 = v0 >> 15;		// sra     $v0, 15
		s6 = v0 + 500;		// addiu   $s6, $v0, 0x1F4

		if (SurfacePtr)		// beqz    $a0, loc_821A0
		{
			v0 = SurfacePtr->surface;		// lh      $v0, 0($a0)
			v0 = v0 ^ 4;		// xori    $v0, 4
			v0 = v0 < 1;		// sltiu   $v0, 1
			v1 = v0;			// move    $v1, $v0
		}
		// loc_821A0:
		s4->onGrass = v1;		//sb      $v1, WHEEL.onGrass($s4)

		if (SurfacePtr)			// beqz    $a0, loc_82254
		{
			v1 = SurfacePtr->surface;			// lh      $v1, 0($a0)

			if (v1 == 4 || v1 == 6 || v1 == 0xb || v1 == 9)
				s4->surface = 0x80;
			else
				s4->surface = 0;

			if (v1 == 8)
			{
				s4->surface = s4->surface | 2;
			}
			else
			{
				if (v1 < 9)
				{
					if (v1 == 6)
					{
					LAB_000821c4:
						s4->surface = s4->surface | 1;
					}
				}
				else
				{
					if (v1 == 9)
						goto LAB_000821c4;
					if (v1 == 0xb)
					{
						s4->surface = s4->surface | 3;
					}
				}
			}
		}
		else
		{
			s4->surface = 0; // loc_82254
		}

		// loc_82258
		v0 = surfacePoint[1];									// lw      $v0, 0xD0 + surfacePoint + 4($sp)
		v1 = wheelPos[1];										// lw      $v1, 0xD0 + wheelPos + 4($sp)
		a0 = surfaceNormal[1];									// lw      $a0, 0xD0 + surfaceNormal + 4($sp)
		v0 -= v1;												// subu    $v0, $v1

		oldCompression = s4->susCompression;					// lbu     $s5, 0($s4)
									// mflo    $v0
		v0 = v0 * a0;				// mult    $v0, $a0
		v0 += 0x800;											// addiu   $v0, 0x800
		v0 = v0 >> 12;											// sra     $v0, 12
		newCompression = v0 + 14;								// addiu   $s3, $v0, 0xE

		v0 = newCompression < 801;								// slti    $v0, $s3, 0x321

		if (!(newCompression >= 0))								// bgez    $s3, loc_82290
		{
			newCompression = 0;									// move    $s3, $zero
			v0 = newCompression < 801;							// slti    $v0, $s3, 0x321
		}

		if (v0 == 0)	//bnez    $v0, loc_8229C
		{
			//loc_82290:
			newCompression = 0xC;								// li      $s3, 0xC
		}

	loc_8229C:
		v1 = cp->controlType;						// lbu     $v1, _CAR_DATA.controlType($s2)
		//v0 = 1;										// li      $v0, 1
		//v0 = s3 < 0x2B;		//slti    $v0, $s3, 0x2B
		if (v1 == 1)	//bne     $v1, $v0, loc_823CC
		{
			// [A] wheel sounds and PAD vibration TODO
			UNIMPLEMENTED();
		}

		//loc_823CC:
		if (0x2B < newCompression)
			newCompression = 0x2a;

		//loc_823D8

		if (newCompression == 0 && oldCompression == 0) // bnez    $s3, loc_823E8 + beqz    $s5, loc_82B40
		{
			// loc_82B40:
			s4->susCompression = 0;		// sb      $zero, 0($s4)
		}
		else
		{
			// loc_823E8:
			t0 = wheelPos[2];				// lw      $t0, 0xD0 + wheelPos + 8($sp)
			v0 = cp->hd.where.t[2];			// lw      $v0, _CAR_DATA.hd.where.t + 8($s2)
			t1 = cl->avel[1];				// lw      $t1, CAR_LOCALS.avel + 4($s7)
			t0 -= v0;						// subu    $t0, $v0
			//---------------------mult    $t1, $t0
			a3 = wheelPos[1];				//lw      $a3, 0xD0 + wheelPos + 4($sp)
			v0 = cp->hd.where.t[1];			// lw      $v0, _CAR_DATA.hd.where.t + 4($s2)
			a1 = t1 * t0;		// mflo    $a1
			v1 = cl->avel[2];				// lw      $v1, CAR_LOCALS.avel + 8($s7)
			a3 -= v0;						// subu    $a3, $v0
			//----------------------mult    $v1, $a3
			a2 = wheelPos[0];				// lw      $a2, 0xD0 + wheelPos($sp)
			v0 = cp->hd.where.t[0];			// lw      $v0, _CAR_DATA.hd.where.t($s2)
			t2 = v1 * a3;		// mflo    $t2
			a2 -= v0;						// subu    $a2, $v0

			v1 = v1 * a2;		//mult    $v1, $a2
								//mflo    $v1
			a0 = cl->avel[0];				// lw      $a0, CAR_LOCALS.avel($s7)

			t3 = a0 * t0;		// mult    $a0, $t0
								//mflo    $t3

		
			a0 = a0 * a3;		// mult    $a0, $a3
			force.vz = 0;					// sw      $zero, 0xD0 + force.vz($sp)
			force.vx = 0;					// sw      $zero, 0xD0 + force($sp)
			wheelPos[1] = a3;				// sw      $a3, 0xD0 + wheelPos + 4($sp)
			wheelPos[2] = t0;				// sw      $t0, 0xD0 + wheelPos + 8($sp)
			wheelPos[0] = a2;				// sw      $a2, 0xD0 + wheelPos($sp)
			v0 = cl->vel[0];				// lw      $v0, CAR_LOCALS($s7)
			a1 -= t2;						// subu    $a1, $t2
			a1 += 0x800;					// addiu   $a1, 0x800
			a1 = a1 >> 12;					// sra     $a1, 12
								//-----mflo    $a0 
			v1 -= t3;						// subu    $v1, $t3
			v1 += 0x800;					// addiu   $v1, 0x800
			//-----------------------------mult    $t1, $a2
			t1 = t1 * a2;
			a2 = a1 + v0;					// addu    $a2, $a1, $v0
			pointVel[0] = a2;				// sw      $a2, 0xD0 + pointVel($sp)
			v0 = cl->vel[1];				// lw      $v0, CAR_LOCALS.vel + 4($s7)
			v1 = v1 >> 12;					// sra     $v1, 12
			v1 += v0;						// addu    $v1, $v0
			pointVel[1] = v1;				// sw      $v1, 0xD0 + pointVel + 4($sp)
			v1 = newCompression << 3;		// sll     $v1, $s3, 3
			v1 -= newCompression;			// subu    $v1, $s3
			v1 = v1 << 2;					// sll     $v1, 2
			v1 += newCompression;			// addu    $v1, $s3
			v1 = v1 << 2;					// sll     $v1, 2
			v1 -= newCompression;			// subu    $v1, $s3
			v1 = v1 << 1;					// sll     $v1, 1
			v0 = cl->vel[2];				// lw      $v0, CAR_LOCALS.vel + 8($s7)
			//mflo    $t1
			a0 -= t1;						// subu    $a0, $t1
			a0 += 0x800;					// addiu   $a0, 0x800
			a0 = a0 >> 12;					// sra     $a0, 12
			a1 = a0 + v0;					// addu    $a1, $a0, $v0
			v0 = oldCompression << 1;		// sll     $v0, $s5, 1
			v0 += oldCompression;			// addu    $v0, $s5
			v0 = v0 << 3;					// sll     $v0, 3
			v0 += oldCompression;			// addu    $v0, $s5
			v0 = v0 << 2;					// sll     $v0, 2
			pointVel[2] = a1;				// sw      $a1, 0xD0 + pointVel + 8($sp)
			//a0 = s4->locked;				// lbu     $a0, 1($s4)

			s0 = v1 - v0;					//subu    $s0, $v1, $v0

			if (s4->locked) // beqz    $a0, loc_82568
			{
				// sra     $a0, $a2, 6
				v0 = ratan2(a0 >> 6, a1 >> 6);	//jal     ratan2; sra    $a1, 6

				v0 = v0 & 0xFFF;				// andi    $v0, 0xFFF

				a0 = (int)(char*)rcossin_tbl + 2;			// la      $a0, (rcossin_tbl + 2)
				//v1 = i;						// lw      $v1, 0xD0 + i($sp)
				v0 = v0 << 2;					// sll     $v0, 2
				a3 = i & 1;						// andi    $a3, $v1, 1
				v1 = v0 + a0;					// addu    $v1, $v0, $a0
				a0 += v0;						// addu    $a0, $v0
				t2 = *(short*)v1;	// rcossin_tbl + v0 << 2 + 2					// lh      $t2, 0($v1)
				a2 = *(short*)(a0 - 2);			// lh      $a2, -2($a0)
				v0 = pointVel[0];				// lw      $v0, 0xD0 + pointVel($sp)
				v1 = pointVel[2];				// lw      $v1, 0xD0 + pointVel + 8($sp)

				if (!(v0 >= 0))		// bgez    $v0, loc_8253C
					v0 = -v0;

				if (!(v1 >= 0))		//bgez    $v1, loc_82548
					v1 = -v1;					// negu    $v1, $v1

				// addu    $v0, $v1
				// slti    $v0, 0x1F40
				// li      $v0, 0x1000
				if (v0 + v1 < 0x1F40)	//	beqz    $v0, loc_82598
				{
					//v0 = 0x1000;
					surfaceNormal[0] = 0;		//sw      $zero, 0xD0 + surfaceNormal($sp)
					surfaceNormal[1] = 0x1000;	//sw      $v0, 0xD0 + surfaceNormal + 4($sp)
					surfaceNormal[2] = 0;		//sw      $zero, 0xD0 + surfaceNormal + 8($sp)					
				}
			}
			else
			{
				// loc_82568
				a0 = i;							// lw      $a0, 0xD0 + i($sp)
				a3 = a0 & 1;					// andi    $a3, $a0, 1
				if (a3)	// bnez    $a3, loc_8258C
				{
					v0 = sdx;					// lw      $v0, 0xD0 + sdx($sp)
					a2 = sdz;					// lw      $a2, 0xD0 + sdz($sp)
					t2 = -v0;					// negu    $t2, $v0
				}
				else
				{
					// loc_8258C
					v1 = cdx;					// lw      $v1, 0xD0 + cdx($sp)
					a2 = cdz;					// lw      $a2, 0xD0 + cdz($sp)
					t2 = -v1;					// negu    $t2, $v1
				}
			}
			// loc_82598

			v1 = pointVel[0];				// lw      $v1, 0xD0 + pointVel($sp)

			v0 = a2;						//move    $v0, $a2
			if (!(v1 >= 0))	// bgez    $v1, loc_825AC
				a1 += 0x3F;					// addiu   $a1, 0x3F

			v1 = v1 >> 6;					// sra     $v1, 6
			if (!(a2 >= 0))	// bgez    $a2, loc_825B8
				v0 = a2 + 0x3f;				// addiu   $v0, $a2, 0x3F

			v0 = v0 >> 6;					// sra     $v0, 6
			v1 = v1 * v0;		// mult    $v1, $v0
								//mflo    $v1
			a1 = pointVel[2];				// lw      $a1, 0xD0 + pointVel + 8($sp)

			v0 = t2;						// move    $v0, $t2
			if (!(a1 >= 0))	// bgez    $a1, loc_825D4
				a1 += 0x3F;

			//loc_825D4:
			a1 = a1 >> 6;	// sra     $a1, 6
			if (!(t2 >= 0))	// bgez    $t2, loc_825E0
				v0 = t2 + 0x3F;				// addiu   $v0, $t2, 0x3F

			//loc_825E0:

			v0 = v0 >> 6;					// sra     $v0, 6
			v0 = a1 * v0;		// mult    $a1, $v0
								//mflo    $v0
			a1 = fp;						// move    $a1, $fp

			t0 = v1 + v0;		// addu    $t0, $v1, $v0
			if (!(fp >= 0))		// bgez    $fp, loc_825FC
				a1 = fp + 0x3F;				//addiu   $a1, $fp, 0xD0 + surfacePoint + 0xF	// WTF? broken SPANISH exe?

			//loc_825FC:
			v0 = t0;						// move    $v0, $t0
			v1 = a1 >> 6;					// sra     $v1, $a1, 6
			if (!(t0 >= 0))	//bgez    $t0, loc_8260C
				v0 = t0 + 0x3F;				// addiu   $v0, $t0, 0x3F

			// loc_8260C
			v0 = v0 >> 6;					// sra     $v0, 6

			int tmp = v1 * v0; //------------------- mult    $v1, $v0
			v1 = 50000;					// li      $v1, 0xC350
			v1 = v1 < t0;					// slt     $v1, $t0
			v0 = tmp; //mflo    $v0

			t1 = v0;			// move    $t1, $v0
			if (!(v0 >= 0))		// bgez    $v0, loc_8262C
					t1 = -t1;					// negu    $t1, $t1			

			//loc_8262C
			v0 = 0xFFFF;	// lui     $v0, 0xFFFF
			if (v1 == 0) // !(v1 < t0) //bnez    $v1, loc_8265C
			{
				v0 = -50000;					//li      $v0, -0xC350
				v0 = t0 < v0;					// slt     $v0, $t0, $v0
				//-----------------mult    $fp, $t0
				if (v0 == 0) // !(t0 < v0)		//bnez    $v0, loc_8266C
				{
					v0 = fp * t0;				// mflo    $v0
					v0 += 0x800;				// addiu   $v0, 0x800
					t0 = v0 >> 12;				// sra     $t0, $v0, 12

					v1 = t0 < 12501;			// slti    $v1, $t0, 0x30D5
					v0 = t0 < -12500;			// slti    $v0, $t0, -0x30D4

					if (v1 != 0 && v0 != 0) // bnez    $v1, loc_82664  + beqz    $v0, loc_82670
						goto loc_8266C;
				}
				else
				{
				loc_8266C:
					t0 = -12500;						// li      $t0, -0x30D4
				}
			}
			else
			{
				// loc_8265C:
				t0 = 12500;	//li      $t0, 0x30D4
			}

				

			// loc_82670
			// front wheels / back wheels
			if (a3 == 0) // bnez    $a3, loc_82794
			{
				// loc_82794:
				//v0 = s4->locked;						// lbu     $v0, 1($s4)
				v1 = 0xA;								// lui     $v1, 0xA
				if (s4->locked == 0) //bnez    $v0, loc_8282C
				{
					a0 = rearFS;						// lw      $a0, 0xD0 + rearFS($sp)

					a0 = a0 * t0;	// mult    $a0, $t0
						// lbu     $v0, _CAR_DATA.hndType($s2)
						// la      $v1, handlingType
						// sll     $v0, 2
						// addu    $v1, $v0
					a1 = handlingType[cp->hndType].autoBrakeOn;	// lbu     $a1, 3($v1)
					//-----mflo    $a0
					a0 += 0x800;						// addiu   $a0, 0x800
					t0 = a0 >> 12;						// sra     $t0, $a0, 12

					if (a1 != 0) //beqz    $a1, loc_827F0
					{
						v0 = cp->wheel_angle;			// lh      $v0, _CAR_DATA.wheel_angle($s2)

						v0 = t0 * v0;	// mult    $t0, $v0
										//mflo    $v0

						if (!(v0 <= 0));	// blez    $v0, loc_827F0; li      $v0, -1
							cp->hd.autoBrake = -1;			//sb      $v0, _CAR_DATA.hd.autoBrake($s2)
					}

					// loc_827F0
					a1 = cp->thrust;						// lh      $a1, _CAR_DATA.thrust($s2)
					a0 = -t2;								// negu    $a0, $t2
					a0 = a0 * a1;		// mult    $a0, $a1
										//mflo    $a0

					a1 = a2 * a1;		// mult    $a2, $a1
					v0 = force.vx;							// lw      $v0, 0xD0 + force($sp)
					v1 = force.vz;							// lw      $v1, 0xD0 + force.vz($sp)
					v0 += a0;								// addu    $v0, $a0
					force.vx = v0;							// sw      $v0, 0xD0 + force($sp)
					//--------mflo    $a1
					v1 += a1;								// addu    $v1, $a1
					//j       loc_82844
					force.vz = v1;							// sw      $v1, 0xD0 + force.vz($sp)
				}
				else
				{
					// loc_8282C:
					v0 = frontFS;							// lw      $v0, 0xD0 + frontFS($sp)

					v0 = v0 * t0;		// mult    $v0, $t0
										// mflo    $v0
					v0 += 0x2000;							// addiu   $v0, 0x2000
					t0 = v0 >> 14;							// sra     $t0, $v0, 14
				}

				v0 = cp->hd.rear_vel;						// lw      $v0, _CAR_DATA.hd.rear_vel($s2)
				v0 = v0 < t1;								// slt     $v0, $t1

				if (v0 != 0)	//beqz    $v0, loc_8285C
					cp->hd.rear_vel = t1;					 // sw      $t1, _CAR_DATA.hd.rear_vel($s2)
			}
			else
			{
				v0 = frontFS;								// lw      $v0, 0xD0 + frontFS($sp)

				v0 = v0 * t0;			// mult    $v0, $t0
				//v1 = s4->locked;							// lbu     $v1, 1($s4)
				//---------mflo    $v0
				v0 += 0x800;								// addiu   $v0, 0x800
				t0 = v0 >> 12;								// sra     $t0, $v0, 12

				if (s4->locked != 0)	// beqz    $v1, loc_8272C
				{
					v0 = v0 >> 13;							// sra     $v0, 13
					v0 += t0;								// addu    $v0, $t0
					t0 = v0 >> 1;							// sra     $t0, $v0, 1
					v1 = -t0;								// negu    $v1, $t0
					v0 = v1 * a2;	// mult    $v1, $a2
									// mflo    $v0

					v1 = v1 * t2;	// mult    $v1, $t2
					a0 = sdz;								// lw      $a0, 0xD0 + sdz($sp)
					//--------------mflo    $v1
					v0 += 0x800;							// addiu   $v0, 0x800
					v0 = v0 >> 12;							// sra     $v0, 12
					v0 = v0 * a0;	// mult    $v0, $a0
					v1 += 0x800;							// addiu   $v1, 0x800
					//--------------mflo    $v0
					a0 = sdx;								// lw      $a0, 0xD0 + sdx($sp)
					v1 = v1 >> 12;							// sra     $v1, 12
					v1 = v1 * a0;	// mult    $v1, $a0
					//--------------mflo    $v1
					v0 -= v1;								// subu    $v0, $v1
					v0 += 0x400;							// addiu   $v0, 0x400
					v1 = sdz;								// lw      $v1, 0xD0 + sdz($sp)
					v0 = v0 >> 11;							// sra     $v0, 11
					a1 = v0 * v1;	// mult    $v0, $v1
									// mflo    $a1
					v0 = -v0;								// negu    $v0, $v0

					v0 = v0 * a0;	// mult    $v0, $a0
					v1 = force.vx;							// lw      $v1, 0xD0 + force($sp)
					a0 = force.vz;							// lw      $a0, 0xD0 + force.vz($sp)
					v1 += a1;								// addu    $v1, $a1
					force.vx = v1;							// sw      $v1, 0xD0 + force($sp)
					//--------------mflo    $v0
					a0 += v0;								// addu    $a0, $v0
					//j       loc_82778
					force.vz = a0;							// sw      $a0, 0xD0 + force.vz($sp)
				}
				else
				{
					// loc_8272C:
					v1 = cp->controlType;					// lbu     $v1, _CAR_DATA.controlType($s2)
					v0 = 3;									// li      $v0, 3
					if (v1 == v0)	// bne     $v1, $v0, loc_82778
					{
						a0 = cp->thrust;					// lh      $a0, _CAR_DATA.thrust($s2)
						v0 = sdx;							// lw      $v0, 0xD0 + sdx($sp)

						a1 = v0 * a0;	// mult    $v0, $a0
										// mflo    $a1
						v0 = sdz;							// lw      $v0, 0xD0 + sdz($sp)

						a0 = v0 * a0;	// mult    $v0, $a0
						v0 = force.vx;						// lw      $v0, 0xD0 + force($sp)
						v1 = force.vz;						// lw      $v1, 0xD0 + force.vz($sp)
						v0 += a1;							// addu    $v0, $a1
						force.vx = v0;						// sw      $v0, 0xD0 + force($sp)
						//--------------mflo    $a0
						v1 += a0;							// addu    $v1, $a0
						force.vz = v1;						// sw      $v1, 0xD0 + force.vz($sp)
					}
				}

				// loc_82778:
				v0 = cp->hd.front_vel;						// lw      $v0, CAR_DATA.hd.front_vel($s2)

				//slt     $v0, $t1
				if (!(v0 < t1))//beqz    $v0, loc_8285C
				{
					//j       loc_8285C
					cp->hd.front_vel = t1;					// sw      $t1, _CAR_DATA.hd.front_vel($s2)
				}
			}

			//loc_8285C
			v1 = surfaceNormal[0];							// lw      $v1, 0xD0 + surfaceNormal($sp)

			v1 = s0 * v1;			// mult    $s0, $v1
									// mflo    $v1

			a0 = t0 * a2;			// mult    $t0, $a2
									// mflo    $a0
			a3 = surfaceNormal[1];							// lw      $a3, 0xD0 + surfaceNormal + 4($sp)

			a3 = s0 * a3;			// mult    $s0, $a3
									// mflo    $a3
			a2 = surfaceNormal[2];							// lw      $a2, 0xD0 + surfaceNormal + 8($sp)

			a2 = s0 * a2;			// mult    $s0, $a2
			t1 = cl->vel[0];								// lw      $t1, CAR_LOCALS($s7)
			a1 = cl->vel[1];								// lw      $a1, CAR_LOCALS.vel + 4($s7)
			v0 = t1 << 1;									// sll     $v0, $t1, 1
			v0 += t1;										// addu    $v0, $t1
			v0 = v0 << 2;									// sll     $v0, 2
			v1 -= a0;										// subu    $v1, $a0
			v1 -= v0;										// subu    $v1, $v0
			v0 = a1 << 1;									// sll     $v0, $a1, 1
			v0 += a1;										// addu    $v0, $a1
			//-----------------------mflo    $a2
			v0 = v0 << 2;									// sll     $v0, 2
			a0 = force.vx;									// lw      $a0, 0xD0 + force($sp)
			t0 = t0 * t2;			// mult    $t0, $t2
			a3 -= v0;										// subu    $a3, $v0
			force.vy = a3;									// sw      $a3, 0xD0 + force.vy($sp)
			t2 = a0 + v1;									// addu    $t2, $a0, $v1
			force.vx = t2;									// sw      $t2, 0xD0 + force($sp)
			a1 = cl->vel[2];								// lw      $a1, CAR_LOCALS.vel + 8($s7)
			a0 = force.vz;									// lw      $a0, 0xD0 + force.vz($sp)
			v1 = s4->surface;								// lbu     $v1, 3($s4)
			v0 = a1 << 1;									// sll     $v0, $a1, 1
			v0 += a1;										// addu    $v0, $a1
			v0 = v0 << 2;									// sll     $v0, 2
			v1 = v1 & 7;									// andi    $v1, 7
			//-----------------------mflo    $t0
			a2 -= t0;										// subu    $a2, $t0
			a2 -= v0;										// subu    $a2, $v0
			a0 += a2;										// addu    $a0, $a2
			v0 = 1;											// li      $v0, 1

			force.vz = a0;									// sw      $a0, 0xD0 + force.vz($sp)
			if (v1 == 1) // bne     $v1, $v0, loc_82944
			{
				v0 = t1 << 2;								// sll     $v0, $t1, 2
				v0 += t1;									// addu    $v0, $t1
				v1 = v0 << 4;								// sll     $v1, $v0, 4
				v0 -= v1;									// subu    $v0, $v1
				v0 += t2;									// addu    $v0, $t2, $v0
				v1 = a1 << 2;								// sll     $v1, $a1, 2
				v1 += a1;									// addu    $v1, $a1
				force.vx = v0;								// sw      $v0, 0xD0 + force($sp)
				v0 = v1 << 4;								// sll     $v0, $v1, 4
				v1 -= v0;									// subu    $v1, $v0
				v1 += a0;									// addu    $v1, $a0, $v1
				force.vz = v1;								// sw      $v1, 0xD0 + force.vz($sp)
			}

			// loc_82944:
			v1 = cp->hd.where.m[1][1];						//lh      $v1, _CAR_DATA.hd.where.m + 8($s2)

			v0 = v1 < 0x800;								// slti    $v0, $v1, 0x800
			a0 = 0x1000;									// li      $a0, 0x1000
			if (v0 != 0) // beqz    $v0, loc_82990
			{
				v1 = a0 - v1;								// subu    $v1, $a0, $v1
				v0 = v1 < 0x1001;							// slti    $v0, $v1, 0x1001

				if (v0 != 0)	//beqz    $v0, loc_8297C
				{
					v0 = v1 * v1;	// mult    $v1, $v1
									//mflo    $v0
					v0 += 0x800;							// addiu   $v0, 0x800
					v0 = v0 >> 12;							// sra     $v0, 12
					//j       loc_82980
					v0 = a0 - v0;							// subu    $v0, $a0, $v0
				}
				else
				{
					// loc_8297C
					v0 = 0;									// move    $v0, $zero
				}

				// loc_82980
				v0 = s6 * v0;		// mult    $s6, $v0
									// mflo    $v0
				v0 += 0x800;								// addiu   $v0, 0x800
				s6 = v0 >> 12;								// sra     $s6, $v0, 12
			}
			// loc_82990
			v1 = surfaceNormal[1];							//lw      $v1, 0xD0 + surfaceNormal + 4($sp)

			v0 = v1 < 0xCCC;								// slti    $v0, $v1, 0xCCC
			if (v0 != 0) // beqz    $v0, loc_829B4 
			{
				v1 = s6 * v1;		// mult    $s6, $v1
									// mflo    $v1
				v0 = v1 << 2;								// sll     $v0, $v1, 2
				v0 += v1;									// addu    $v0, $v1
				s6 = v0 >> 14;								// sra     $s6, $v0, 14
			}

			//loc_829B4
			a0 = force.vx;									// lw      $a0, 0xD0 + force($sp)

			a0 += 0x800;									// addiu   $a0, 0x800
			a0 = a0 >> 12;									// sra     $a0, 12
			a0 = a0 * s6;	// mult    $a0, $s6
			v1 = force.vz;									// lw      $v1, 0xD0 + force.vz($sp)
							// mflo    $a0
			v1 += 0x800;									// addiu   $v1, 0x800
			v1 = v1 >> 12;									// sra     $v1, 12
			v1 = v1 * s6;	// mult    $v1, $s6
			v0 = force.vy;									// lw      $v0, 0xD0 + force.vy($sp)

			v0 += 0x800;									// addiu   $v0, 0x800
			v0 = v0 >> 12;									// sra     $v0, 12
			force.vy = v0;									// sw      $v0, 0xD0 + force.vy($sp)
			a0 = a0 >> 12;									// sra     $a0, 12
			force.vx = a0;									// sw      $a0, 0xD0 + force($sp)
			//----------------mflo    $v1
			v1 = v1 >> 12;									// sra     $v1, 12
			force.vz = v1;									// sw      $v1, 0xD0 + force.vz($sp)
			//a0 = cp->controlType;							// lbu     $a0, _CAR_DATA.controlType($s2)
			//v0 = 3;											//li      $v0, 3
			if (cp->controlType == 3) // bne     $a0, $v0, loc_82A6C
			{
				// li      $v0, 2
				// lw      $v1, gCopDifficultyLevel
				if (gCopDifficultyLevel == 2)	// bne     $v1, $v0, loc_82A40
				{
					v1 = wheelPos[1];						// lw      $v1, 0xD0 + wheelPos + 4($sp)

					v0 = v1 << 1;							// sll     $v0, $v1, 1
					v0 += v1;								// addu    $v0, $v1
					v0 += v1;								// addu    $v0, $v1
					//j       loc_82A58
					v0 = v0 << 2;							// sll     $v0, 2
				}
				else
				{
					// loc_82A40
					v1 = wheelPos[1];						// lw      $v1, 0xD0 + wheelPos + 4($sp)

					v0 = v1 << 2;							// sll     $v0, $v1, 2
					v0 += v1;								// addu    $v0, $v1
					v0 = v0 << 2;							// sll     $v0, 2
					v0 -= v1;								// subu    $v0, $v1
				}
				// loc_82A58
				if (!(v0 >= 0))	//bgez    $v0, loc_82A64
					v0 += 0x1F;								//  addiu   $v0, 0x1F

				v0 = v0 >> 5;								// sra     $v0, 5
				wheelPos[1] = v0;							// sw      $v0, 0xD0 + wheelPos + 4($sp)
			}
			// loc_82A6C
			t2 = wheelPos[1];								// lw      $t2, 0xD0 + wheelPos + 4($sp)
			t1 = force.vz;									// lw      $t1, 0xD0 + force.vz($sp)

			a2 = t2 * t1;	// mult    $t2, $t1
			a0 = wheelPos[2];								// lw      $a0, 0xD0 + wheelPos + 8($sp)
							//mflo    $a2
			a3 = force.vy;									// lw      $a3, 0xD0 + force.vy($sp)

			t3 = a0 * a3;	// mult    $a0, $a3
							//mflo    $t3
			t0 = force.vx;									// lw      $t0, 0xD0 + force($sp)

			a0 = a0 * t0;	// mult    $a0, $t0
							// mflo    $a0
			a1 = wheelPos[0];								// lw      $a1, 0xD0 + wheelPos($sp)

			t4 = a1 * t1;	//mult    $a1, $t1
							//mflo    $t4

			a1 = a1 * a3;	// mult    $a1, $a3
			v0 = cp->hd.acc[0];								// lw      $v0, _CAR_DATA.hd.acc($s2)
			v1 = cp->hd.acc[1];								// lw      $v1, _CAR_DATA.hd.acc + 4($s2)
			v0 += t0;										// addu    $v0, $t0
			cp->hd.acc[0] = v0;								// sw      $v0, _CAR_DATA.hd.acc($s2)
			v0 = cp->hd.acc[2];								// lw      $v0, _CAR_DATA.hd.acc + 8($s2)
			v1 += a3;										// addu    $v1, $a3
			cp->hd.acc[1] = v1;								// sw      $v1, _CAR_DATA.hd.acc + 4($s2)
			v0 += t1;										// addu    $v0, $t1
			cp->hd.acc[2] = v0;								// sw      $v0, _CAR_DATA.hd.acc + 8($s2)
			//------------------------mflo    $a1
			v0 = cp->hd.aacc[0];							// lw      $v0, _CAR_DATA.hd.aacc($s2)
			a2 -= t3;										// subu    $a2, $t3
			t2 = t2 * t0;	// mult    $t2, $t0
			a2 += 0x800;									// addiu   $a2, 0x800
			a2 = a2 >> 12;									// sra     $a2, 12
			v0 += a2;										// addu    $v0, $a2
			cp->hd.aacc[0] = v0;							// sw      $v0, _CAR_DATA.hd.aacc($s2)
			v0 = cp->hd.aacc[1];							// lw      $v0, _CAR_DATA.hd.aacc + 4($s2)
			a0 -= t4;										// subu    $a0, $t4
			a0 += 0x800;									// addiu   $a0, 0x800
			a0 = a0 >> 12;									// sra     $a0, 12
			v0 += a0;										// addu    $v0, $a0
			cp->hd.aacc[1] = v0;							// sw      $v0, _CAR_DATA.hd.aacc + 4($s2)
			v0 = cp->hd.aacc[2];							// lw      $v0, _CAR_DATA.hd.aacc + 8($s2)
			//--------------mflo    $t2
			a1 -= t2;										// subu    $a1, $t2
			a1 += 0x800;									// addiu   $a1, 0x800
			a1 = a1 >> 12;									// sra     $a1, 12
			v0 += a1;										// addu    $v0, $a1
			cp->hd.aacc[2] = v0;							// sw      $v0, _CAR_DATA.hd.aacc + 8($s2)
			//j       loc_82B44
			s4->susCompression = newCompression;						// sb      $s3, 0($s4)

		}
		// loc_82B44
		// lw      $v0, 0xD0 + i($sp)
		//addiu   $s4, -4
		//addiu   $v0, -1
		//bgez    $v0, loc_8210C
		//sw      $v0, 0xD0 + i($sp)
		s4--;
		i--;
	}

	//loc_8210C
	v0 = cp->hd.wheel[1].susCompression; //lbu     $v0, _CAR_DATA.hd.wheel.susCompression + 4($s2)
	if (cp->hd.wheel[1].susCompression == 0 && cp->hd.wheel[3].susCompression == 0) // bnez    $v0, loc_82B78 + 	beqz    $v0, loc_82BE4
	{
		// loc_82BE4
		//v1 = cp->thrust;									// lh      $v1, _CAR_DATA.thrust($s2)
		v0 = 0x1A;											// lui     $v0, 0x1A
		if (!(cp->thrust > 0))	// bgtz    $v1, loc_82C00
		{
			v0 = 0;											//move    $v0, $zero
			if (!(cp->thrust > 0)) //bgez    $v1, loc_82C04
			{
				v0 = -0x13;		//lui     $v0, -0x13
		// loc_82C00
				v0 = v0 | 0x4000;							// ori     $v0, 0x4000
			}
		}
		else
		{
			// loc_82C00
			v0 = v0 | 0x4000;								// ori     $v0, 0x4000
		}
	}
	else
	{
		// loc_82B78
		v1 = cl->vel[0];									//lw      $v1, CAR_LOCALS($s7)

		if (!(v1 >= 0))	//bgez    $v1, loc_82B8C
			v1 += 0x3F;

		v0 = cdx;											// lw      $v0, 0xD0 + cdx($sp)

		v1 = v1 >> 6;										// sra     $v1, 6
		if (!(v0 >= 0)) // bgez    $v0, loc_82BA0
			v0 += 0x3F;										// addiu   $v0, 0x3F;

		v0 = v0 >> 6;										// sra     $v0, 6
		v1 = v1 * v0;			// mult    $v1, $v0
		a1 = cl->vel[2];									// lw      $a1, CAR_LOCALS.vel + 8($s7)
								// mflo    $v1
		if (!(a1 >= 0))	// bgez    $a1, loc_82BBC
			a1 += 0x3F;										// addiu   $a1, 0x3F

		v0 = cdz;											// lw      $v0, 0xD0 + cdz($sp)

		a1 = a1 >> 6;										// sra     $a1, 6
		if (v0 >= 0) //bgez    $v0, loc_82BD0
			v0 += 0x3F;										// addiu   $v0, 0x3F

		v0 = v0 >> 6;										// sra     $v0, 6
		v0 = a1 * v0;		// mult    $a1, $v0
							// mflo    $v0
		//j       loc_82C04
		v0 = v1 + v0;										// addu    $v0, $v1, $v0
	}

	// loc_82C04
	cp->hd.wheel_speed = v0;		// sw      $v0, _CAR_DATA.hd.wheel_speed($s2)
#endif
}

int useREDRIVER = 0;

// [D]
void AddWheelForcesDriver1(_CAR_DATA *cp, CAR_LOCALS *cl)
{
	if (useREDRIVER)
	{
		AddWheelForcesDriver1RE(cp, cl);
		return;
	}

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
	uVar3 = uVar3 + (int)cp->wheel_angle & 0xfff;
	cdx = (int)rcossin_tbl[uVar9 * 2];
	cdz = (int)rcossin_tbl[uVar9 * 2 + 1];
	sdx = (int)rcossin_tbl[uVar3 * 2];
	sdz = (int)rcossin_tbl[uVar3 * 2 + 1];
	player_id = GetPlayerId(cp);
	car_cos = car_cosmetics + cp->ap.model;
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
		wheelPosPtr->vx = MAC1;
		wheelPosPtr2->vy = MAC2;
		wheelPosPtr2->vz = MAC3;
		iVar4 = FindSurfaceD2(wheelPosPtr, surfaceNormalPtr, surfacePointPtr, surfacePtrPtr);
		bVar7 = false;
		iVar4 = (iVar4 * (0x7e90 - wetness) >> 0xf) + 500;
		if (SurfacePtr != NULL) {
			bVar7 = SurfacePtr->surface == 4;
		}
		*(bool *)&pWVar14->onGrass = bVar7;
		if (SurfacePtr == NULL) {
			pWVar14->surface = '\0';
		}
		else {
			sVar1 = SurfacePtr->surface;
			if ((((sVar1 == 4) || (sVar1 == 6)) || (sVar1 == 0xb)) || (sVar1 == 9)) {
				pWVar14->surface = -0x80;
			}
			else {
				pWVar14->surface = '\0';
			}
			if (sVar1 == 8) {
				pWVar14->surface = pWVar14->surface | 2;
			}
			else {
				if (sVar1 < 9) {
					if (sVar1 == 6) {
					LAB_000821c4:
						pWVar14->surface = pWVar14->surface | 1;
					}
				}
				else {
					if (sVar1 == 9) goto LAB_000821c4;
					if (sVar1 == 0xb) {
						pWVar14->surface = pWVar14->surface | 3;
					}
				}
			}
		}
		oldCompression = pWVar14->susCompression;
		uVar3 = (uint)oldCompression;
		chan = ((surfacePoint[1] - wheelPos[1]) * surfaceNormal[1] + 0x800 >> 0xc) + 0xe;
		newCompression = chan;
		if (chan < 0) {
			newCompression = 0;
		}
		if (800 < chan) {
			newCompression = 0xc;
		}
		if (cp->controlType == '\x01') {
			chan = newCompression - uVar3;
			if (chan < 0) {
				chan = uVar3 - newCompression;
			}
			if ((0xc < chan) && ((i & 1U) != 0)) {
				chan = GetFreeChannel();
				if ((1 < NumPlayers) && (NoPlayerControl == 0)) {
					SetPlayerOwnsChannel(chan, (char)player_id);
				}
				Start3DSoundVolPitch
				(chan, 1, 5, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2],
					-0x9c4, 400);
				SetChannelPosition3(chan, (VECTOR *)cp->hd.where.t, NULL, -0x9c4, 400, 0);
			}
			if (newCompression < 0x55) {
				if (0x30 < newCompression) {
					SetPadVibration((int)**(char **)cp->ai.padid, '\x03');
				}
			}
			else {
				SetPadVibration((int)cp->ai.padid, '\x02');
			}
		}
		if (0x2a < newCompression) {
			newCompression = 0x2a;
		}
		if ((newCompression == 0) && (oldCompression == 0)) {
			pWVar14->susCompression = '\0';
		}
		else {
			wheelPos[2] = wheelPos[2] - cp->hd.where.t[2];
			wheelPos[1] = wheelPos[1] - cp->hd.where.t[1];
			wheelPos[0] = wheelPos[0] - cp->hd.where.t[0];
			force.vz = 0;
			force.vx = 0;

			// // [A] valid decompile - Seems like OK
			pointVel[0] = ((cl->avel[1] * wheelPos[2] - cl->avel[2] * wheelPos[1]) + 0x800) >> 12 + cl->vel[0];
			pointVel[1] = ((cl->avel[2] * wheelPos[0] - cl->avel[0] * wheelPos[2]) + 0x800) >> 12 + cl->vel[1];
			pointVel[2] = ((cl->avel[0] * wheelPos[1] - cl->avel[1] * wheelPos[0]) + 0x800) >> 12 + cl->vel[2];

			chan = ((cl->avel[1] * wheelPos[2] - cl->avel[2] * wheelPos[1]) + 0x800 >> 0xc) +
				cl->vel[0];
			iVar10 = ((cl->avel[0] * wheelPos[1] - cl->avel[1] * wheelPos[0]) + 0x800 >> 0xc) +
				cl->vel[2];
			iVar13 = newCompression * 0xe6 + uVar3 * -100;
			if (pWVar14->locked == '\0') {
				if ((i & 1U) == 0) {
					iVar12 = -sdx;
					iVar11 = sdz;
				}
				else {
					iVar12 = -cdx;
					iVar11 = cdz;
				}
			}
			else {
				uVar3 = ratan2(chan >> 6, iVar10 >> 6);
				iVar12 = (int)rcossin_tbl[(uVar3 & 0xfff) * 2 + 1];
				iVar5 = chan;
				if (chan < 0) {
					iVar5 = -chan;
				}
				iVar6 = iVar10;
				if (iVar10 < 0) {
					iVar6 = -iVar10;
				}
				iVar11 = (int)rcossin_tbl[(uVar3 & 0xfff) * 2];
				if (iVar5 + iVar6 < 8000) {
					surfaceNormal[0] = 0;
					surfaceNormal[1] = 0x1000;
					surfaceNormal[2] = 0;
				}
			}
			if (chan < 0) {
				chan = chan + 0x3f;
			}
			iVar5 = iVar11;
			if (iVar11 < 0) {
				iVar5 = iVar11 + 0x3f;
			}
			if (iVar10 < 0) {
				iVar10 = iVar10 + 0x3f;
			}
			iVar6 = iVar12;
			if (iVar12 < 0) {
				iVar6 = iVar12 + 0x3f;
			}
			iVar10 = (chan >> 6) * (iVar5 >> 6) + (iVar10 >> 6) * (iVar6 >> 6);
			chan = iVar8;
			if (iVar8 < 0) {
				chan = iVar8 + 0x3f;
			}
			iVar5 = iVar10;
			if (iVar10 < 0) {
				iVar5 = iVar10 + 0x3f;
			}
			chan = (chan >> 6) * (iVar5 >> 6);
			if (chan < 0) {
				chan = -chan;
			}
			if (iVar10 < 0xc351) {
				if (iVar10 < -50000) {
				LAB_00082604:
					iVar10 = -0x30d4;
				}
				else {
					iVar10 = iVar8 * iVar10 + 0x800 >> 0xc;
					if (0x30d4 < iVar10) goto LAB_000825f4;
					if (iVar10 < -0x30d4) goto LAB_00082604;
				}
			}
			else {
			LAB_000825f4:
				iVar10 = 0x30d4;
			}
			if ((i & 1U) == 0) {
				iVar5 = frontFS * iVar10 + 0x800;
				iVar10 = iVar5 >> 0xc;
				if (pWVar14->locked == '\0') {
					if (cp->controlType == '\x03') {
						force.vx = sdx * cp->thrust;
						force.vz = sdz * cp->thrust;
					}
				}
				else {
					iVar10 = (iVar5 >> 0xd) + iVar10 >> 1;
					iVar5 = ((-iVar10 * iVar11 + 0x800 >> 0xc) * sdz -
						(-iVar10 * iVar12 + 0x800 >> 0xc) * sdx) + 0x400 >> 0xb;
					force.vx = iVar5 * sdz;
					force.vz = -iVar5 * sdx;
				}
				if (cp->hd.front_vel < chan) {
					cp->hd.front_vel = chan;
				}
			}
			else {
				if (pWVar14->locked == '\0') {
					iVar10 = rearFS * iVar10 + 0x800 >> 0xc;
					if ((handlingType[cp->hndType].autoBrakeOn != '\0') &&
						(0 < iVar10 * cp->wheel_angle)) {
						cp->hd.autoBrake = -1;
					}
					force.vx = -iVar12 * (int)cp->thrust;
					force.vz = iVar11 * (int)cp->thrust;
				}
				else {
					iVar10 = frontFS * iVar10 + 0x2000 >> 0xe;
				}
				if (cp->hd.rear_vel < chan) {
					cp->hd.rear_vel = chan;
				}
			}
			force.vx = force.vx + (iVar13 * surfaceNormal[0] - iVar10 * iVar11) + cl->vel[0] * -0xc;
			force.vz = force.vz + (iVar13 * surfaceNormal[2] - iVar10 * iVar12) + cl->vel[2] * -0xc;
			if ((pWVar14->surface & 7) == 1) {
				force.vx = force.vx + cl->vel[0] * -0x4b;
				force.vz = force.vz + cl->vel[2] * -0x4b;
			}
			chan = (int)cp->hd.where.m[4];
			if (chan < 0x800) {
				chan = 0x1000 - chan;
				if (chan < 0x1001) {
					chan = 0x1000 - (chan * chan + 0x800 >> 0xc);
				}
				else {
					chan = 0;
				}
				iVar4 = iVar4 * chan + 0x800 >> 0xc;
			}
			if (surfaceNormal[1] < 0xccc) {
				iVar4 = iVar4 * surfaceNormal[1] * 5 >> 0xe;
			}
			chan = iVar13 * surfaceNormal[1] + cl->vel[1] * -0xc + 0x800 >> 0xc;
			iVar10 = (force.vx + 0x800 >> 0xc) * iVar4 >> 0xc;
			iVar4 = (force.vz + 0x800 >> 0xc) * iVar4 >> 0xc;
			if (cp->controlType == '\x03') {
				if (gCopDifficultyLevel == 2) {
					iVar13 = wheelPos[1] * 0xc;
				}
				else {
					iVar13 = wheelPos[1] * 0x13;
				}
				if (iVar13 < 0) {
					iVar13 = iVar13 + 0x1f;
				}
				wheelPos[1] = iVar13 >> 5;
			}

			// [A] valid decompile - Seems like OK
			/*
			cp->hd.acc[0] += force.vx;
			cp->hd.acc[1] += force.vy;
			cp->hd.acc[2] += force.vz;

			cp->hd.aacc[0] += ((wheelPos[1] * force.vz - wheelPos[2] * force.vy) + 0x800) >> 12;
			cp->hd.aacc[1] += ((wheelPos[2] * force.vx - wheelPos[0] * force.vz) + 0x800) >> 12;
			cp->hd.aacc[2] += ((wheelPos[0] * force.vy - wheelPos[1] * force.vx) + 0x800) >> 12;
			*/

			iVar12 = cp->hd.acc[1];
			cp->hd.acc[0] = cp->hd.acc[0] + iVar10;
			iVar13 = cp->hd.acc[2];
			cp->hd.acc[1] = iVar12 + chan;
			cp->hd.acc[2] = iVar13 + iVar4;
			cp->hd.aacc[0] = cp->hd.aacc[0] + ((wheelPos[1] * iVar4 - wheelPos[2] * chan) + 0x800 >> 0xc);
			cp->hd.aacc[1] = cp->hd.aacc[1] + ((wheelPos[2] * iVar10 - wheelPos[0] * iVar4) + 0x800 >> 0xc);
			cp->hd.aacc[2] = cp->hd.aacc[2] + ((wheelPos[0] * chan - wheelPos[1] * iVar10) + 0x800 >> 0xc);


			pWVar14->susCompression = (char)newCompression;
		}
		pWVar14 = pWVar14 + -1;
		i = i + -1;
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
		if (iVar8 < 0) {
			iVar8 = iVar8 + 0x3f;
		}
		if (cdx < 0) {
			cdx = cdx + 0x3f;
		}
		iVar4 = cl->vel[2];
		if (iVar4 < 0) {
			iVar4 = iVar4 + 0x3f;
		}
		if (cdz < 0) {
			cdz = cdz + 0x3f;
		}
		uVar3 = (iVar8 >> 6) * (cdx >> 6) + (iVar4 >> 6) * (cdz >> 6);
	}
LAB_00082b9c:
	cp->hd.wheel_speed = uVar3;
	return;
}





