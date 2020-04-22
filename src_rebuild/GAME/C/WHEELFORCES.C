#include "THISDUST.H"
#include "WHEELFORCES.H"
#include "CARS.H"
#include "MAIN.H"
#include "GAMESND.H"
#include "DEBRIS.H"
#include "HANDLING.H"
#include "COSMETIC.H"
#include "DR2ROADS.H"

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
	int iStack140;
	long surfaceNormal[4];
	long lever[4];
	VECTOR direction;
	VECTOR partdir;
	_sdPlane *SurfacePtr;

	iVar12 = 2;
	plVar15 = (cp->hd).where.t;
	puVar7 = (long *)(_cl.vel + 2);
	puVar5 = (long *)(cp->st.v + 2);

	SurfacePtr = NULL;
	_cl.aggressive = handlingType[cp->hndType].aggressiveBraking;
	_cl.extraangulardamping = 0;

	// apply damping
	
	do {
		uVar3 = puVar5[10];
		iVar12 = iVar12 + -1;
		*puVar7 = puVar5[7];
		puVar7[4] = uVar3;
		puVar7 = puVar7 + -1;
		*puVar5 = (*puVar5 & 0xf) + puVar5[-0x37] * 0x10;
		puVar5 = puVar5 + -1;
	} while (-1 < iVar12);

	(cp->hd).acc[0] = 0;
	(cp->hd).acc[1] = -7456; // apply gravity
	(cp->hd).acc[2] = 0;

	iVar12 = _cl.vel[0] + 0x800 >> 0xc;
	iVar4 = _cl.vel[2] + 0x800 >> 0xc;

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

	iVar4 = 0xc;

	if ((0x800 < cp->hd.where.m[1][1]) && (iVar4 = 4, cp->controlType == 2)) 
	{
		iVar4 = (uint)(cp->totalDamage != 0) << 2;
	}

	iVar13 = iVar4 + -1;
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

			lever[0] = pointPos[0] - (cp->hd).where.t[0];
			lever[1] = pointPos[1] - (cp->hd).where.t[1];
			lever[2] = pointPos[2] - (cp->hd).where.t[2];

			FindSurfaceD2((VECTOR *)pointPos, (VECTOR *)surfaceNormal, (VECTOR *)&surfacePoint, &SurfacePtr);

			if (((surfacePoint[1] - pointPos[1]) - 1 < 799) && (iVar4 = (surfacePoint[1] - pointPos[1]) * surfaceNormal[1] + 0x800 >> 0xc, iVar12 < iVar4))
			{
				unaff_s6 = 0;
				deepestNormal[1] = surfaceNormal[1];
				deepestNormal[0] = surfaceNormal[0];
				deepestNormal[2] = surfaceNormal[2];
				deepestLever[0] = lever[0];
				deepestLever[1] = lever[1];
				deepestLever[2] = lever[2];

				//deepestPoint = surfacePoint; // [A]

				iVar12 = iVar4;
				if (3 < iVar13)
				{
					unaff_s6 = 3;
				}
			}
			iVar13 = iVar13 + -1;
			pSVar14 = pSVar14 + -1;
		} while (iVar13 != -1);
	}

	if (iVar12 != 0)
	{
		lever[0] = ((_cl.avel[1] * deepestLever[2] - _cl.avel[2] * deepestLever[1]) + 0x800 >> 0xc)
			+ _cl.vel[0];

		lever[1] = ((_cl.avel[2] * deepestLever[0] - _cl.avel[0] * deepestLever[2]) + 0x800 >> 0xc)
			+ _cl.vel[1];

		iVar4 = deepestLever[0] * deepestNormal[0] + deepestLever[1] * deepestNormal[1] +
			deepestLever[2] * deepestNormal[2] + 0x800 >> 0xc;

		lever[2] = ((_cl.avel[0] * deepestLever[1] - _cl.avel[1] * deepestLever[0]) + 0x800 >> 0xc)
			+ _cl.vel[2];

		iVar4 = (((deepestLever[0] * deepestLever[0] + deepestLever[1] * deepestLever[1] + deepestLever[2] * deepestLever[2]) - iVar4 * iVar4) *
			(int)car_cosmetics[cp->ap.model].twistRateY + 0x800 >> 0xc) + 0x1000;

		if (iVar4 == 0) 
		{
			trap(7);
		}

		iVar13 = 2;
		impulse = (((lever[0] >> 6) * (deepestNormal[0] >> 6) + (lever[1] >> 6) * (deepestNormal[1] >> 6) + (lever[2] >> 6) * (deepestNormal[2] >> 6)) / iVar4) * -0x800;

		piVar11 = (long*)&direction.vz;
		piVar10 = deepestNormal + 2;
		piVar9 = lever + 2;
		piVar8 = (long*)frictionLimit + unaff_s6;

		
		do {
			iVar6 = *piVar8;
			iVar4 = *piVar9 * 0x43;
			iVar1 = -iVar6;
			if ((iVar4 <= iVar6) && (iVar6 = iVar4, iVar4 < iVar1)) 
				iVar6 = iVar1;

			iVar4 = *piVar10;
			piVar10 = piVar10 + -1;
			piVar9 = piVar9 + -1;
			piVar8 = piVar8 + -1;
			iVar13 = iVar13 + -1;
			*piVar11 = (impulse * iVar4 - iVar6) + 0x800 >> 0xc;
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

		cp->hd.acc[0] = cp->hd.acc[0] + direction.vx;
		cp->hd.acc[1] = cp->hd.acc[1] + direction.vy;
		cp->hd.acc[2] = cp->hd.acc[2] + direction.vz;

		//p->hd.aacc[0] = cp->hd.aacc[0] + ((deepestLever[1] * direction.vz - deepestLever[2] * direction.vy) + 0x800 >> 0xc);
		//cp->hd.aacc[1] = cp->hd.aacc[1] + ((deepestLever[2] * direction.vx - deepestLever[0] * direction.vz) + 0x800 >> 0xc);
		//cp->hd.aacc[2] = cp->hd.aacc[2] + ((deepestLever[0] * direction.vy - deepestLever[1] * direction.vx) + 0x800 >> 0xc);

		if (iVar12 != 0) 
		{
			lever[0] = iVar12 * deepestNormal[0] + 0x800 >> 0xc;
			lever[1] = iVar12 * deepestNormal[1] + 0x800 >> 0xc;
			lever[2] = iVar12 * deepestNormal[2] + 0x800 >> 0xc;

			iVar4 = (cp->hd).where.t[1];
			(cp->hd).where.t[0] = (cp->hd).where.t[0] + lever[0];

			iVar13 = (cp->hd).where.t[2];
			(cp->hd).where.t[1] = iVar4 + lever[1];

			iVar4 = (cp->st).n.fposition[0];
			(cp->hd).where.t[2] = iVar13 + lever[2];

			iVar13 = (cp->st).n.fposition[1];
			(cp->st).n.fposition[0] = iVar4 + lever[0] * 0x10;

			iVar4 = (cp->st).n.fposition[2];

			(cp->st).n.fposition[1] = iVar13 + lever[1] * 0x10;
			(cp->st).n.fposition[2] = iVar4 + lever[2] * 0x10;

			gte_SetTransMatrix(&cp->hd.where);

			_cl.extraangulardamping = 1;

			if (0x78 < iVar12) 
			{
				(cp->st).n.linearVelocity[1] = 0;
			}
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

void GetFrictionScalesDriver1(_CAR_DATA *cp, CAR_LOCALS *cl, int *frontFS, int *rearFS)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	int iVar2;
	int iVar3;

	bVar1 = cp->hndType;
	if (cp->thrust < 0) {
		iVar2 = 0x5ad;
	}
	else {
		iVar2 = 0x334;
		if (cp->thrust < 1) {
			iVar2 = 0x3a9;
		}
	}
	*frontFS = iVar2;
	if ((((cp->wheelspin == '\0') && (handlingType[cp->hndType].autoBrakeOn != '\0')) &&
		(iVar2 = (int)(cp->hd).autoBrake, 0 < iVar2)) && (0 < (cp->hd).wheel_speed)) {
		iVar3 = iVar2 << 1;
		if (0xd < iVar2) {
			iVar2 = 0xd;
			iVar3 = 0x1a;
		}
		*frontFS = *frontFS + (iVar3 + iVar2) * 0xf;
		if (handlingType[cp->hndType].autoBrakeOn == '\x02') {
			while (FrameCnt != 0x78654321) {
				trap(0x400);
			}
		}
	}
	if ((((cp->thrust < 0) && (0xa3d7 < (cp->hd).wheel_speed)) && (cp->hndType == '\0')) ||
		(((cp->controlType == '\x02' && (cp->ai[0xf9] == 3)) && (cp->ai[0xc] != 9)))) {
		(cp->hd).wheel[3].locked = '\x01';
		(cp->hd).wheel[2].locked = '\x01';
		(cp->hd).wheel[1].locked = '\x01';
		(cp->hd).wheel[0].locked = '\x01';
	}
	else {
		(cp->hd).wheel[3].locked = '\0';
		(cp->hd).wheel[2].locked = '\0';
		(cp->hd).wheel[1].locked = '\0';
		(cp->hd).wheel[0].locked = '\0';
	}
	if (cp->handbrake == '\0') {
		if (cp->wheelspin != '\0') {
			*frontFS = *frontFS + 600;
		}
	}
	else {
		if (-1 < cp->thrust) {
			cp->thrust = 0;
		}
		if ((cp->hd).wheel_speed < 1) {
			iVar2 = *frontFS + -0x177;
		}
		else {
			iVar2 = *frontFS + 0x290;
		}
		*frontFS = iVar2;
		(cp->hd).wheel[1].locked = '\x01';
		(cp->hd).wheel[3].locked = '\x01';
		cp->wheelspin = '\0';
	}
	if ((((cp->hd).wheel_speed < 0) && (-1 < cp->thrust)) && (cp->handbrake == '\0')) {
		*frontFS = *frontFS + -400;
	}
	*rearFS = 0x780 - *frontFS;
	if (cp->wheelspin != '\0') {
		cp->thrust = (short)((int)((cp->ap).carCos)->powerRatio * 5000 + 0x800 >> 0xc);
	}
	if (((cp->thrust < 0) && (0xa3d7 < (cp->hd).wheel_speed)) && (cl->aggressive != 0)) {
		iVar2 = *frontFS * 10;
		if (iVar2 < 0) {
			iVar2 = iVar2 + 7;
		}
		*frontFS = iVar2 >> 3;
		iVar2 = *rearFS * 10;
		if (iVar2 < 0) {
			iVar2 = iVar2 + 7;
		}
		*rearFS = iVar2 >> 3;
	}
	else {
		if ((cp->hd).wheel[0].onGrass == '\0') {
			iVar3 = *frontFS;
			iVar2 = iVar3 * 0x24;
		}
		else {
			iVar3 = *frontFS;
			iVar2 = iVar3 * 0x28;
		}
		iVar2 = iVar2 - iVar3;
		if (iVar2 < 0) {
			iVar2 = iVar2 + 0x1f;
		}
		*frontFS = iVar2 >> 5;
	}
	iVar2 = *frontFS * (uint)(byte)handlingType[bVar1].frictionScaleRatio;
	if (iVar2 < 0) {
		iVar2 = iVar2 + 0x1f;
	}
	*frontFS = iVar2 >> 5;
	iVar2 = *rearFS * (uint)(byte)handlingType[bVar1].frictionScaleRatio;
	if (iVar2 < 0) {
		iVar2 = iVar2 + 0x1f;
	}
	*rearFS = iVar2 >> 5;
	if ((cp->hndType == '\x05') && (cp->ai[0] == 5)) {
		*frontFS = (*frontFS * 3) / 2;
		*rearFS = (*rearFS * 3) / 2;
	}
	iVar2 = (int)((cp->ap).carCos)->traction;
	if (iVar2 != 0x1000) {
		*frontFS = *frontFS * iVar2 + 0x800 >> 0xc;
		*rearFS = *rearFS * iVar2 + 0x800 >> 0xc;
	}
	return;*/
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

void ConvertTorqueToAngularAcceleration(_CAR_DATA *cp, CAR_LOCALS *cl)
{
	UNIMPLEMENTED();
	/*
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
	int *piVar12;
	int *piVar13;
	short *psVar14;
	int iVar15;

	sVar1 = (cp->hd).where.m[2];
	iVar6 = (cp->hd).aacc[0];
	sVar2 = (cp->hd).where.m[5];
	iVar7 = (cp->hd).aacc[1];
	psVar14 = (cp->hd).where.m + 8;
	piVar12 = (cp->hd).aacc + 2;
	sVar3 = (cp->hd).where.m[8];
	iVar8 = (cp->hd).aacc[2];
	uVar10 = (uint)(byte)(cp->ap).model;
	sVar4 = car_cosmetics[uVar10].twistRateY;
	sVar5 = car_cosmetics[uVar10].twistRateZ;
	iVar15 = 2;
	piVar13 = cl->avel + 2;
	do {
		iVar11 = *piVar12 * (int)sVar4 +
			((int)*psVar14 *
			((int)sVar5 - (int)sVar4) *
				(sVar1 * iVar6 + sVar2 * iVar7 + sVar3 * iVar8 + 0x800 >> 0xc) + *piVar13 * -0x80 +
				0x800 >> 0xc);
		*piVar12 = iVar11;
		if (cl->extraangulardamping == 1) {
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
	return;*/
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
			// 		int chan; // $s1
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

void AddWheelForcesDriver1(_CAR_DATA *cp, CAR_LOCALS *cl)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	short sVar2;
	long lVar3;
	VECTOR *pVVar4;
	undefined4 in_zero;
	undefined4 in_at;
	uint uVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	bool bVar9;
	int iVar10;
	int iVar11;
	uint uVar12;
	int iVar13;
	int iVar14;
	int iVar15;
	int chan;
	int iVar16;
	WHEEL *pWVar17;
	VECTOR local_b0;
	VECTOR VStack160;
	VECTOR local_90;
	int local_80;
	int local_7c;
	int local_78;
	int local_70;
	int local_6c;
	int local_68;
	int local_60;
	int local_5c;
	_sdPlane *local_58;
	uint local_54;
	int local_50;
	int local_4c;
	int local_48;
	int local_44;
	CAR_COSMETICS *local_40;
	int local_3c;
	VECTOR *local_38;
	VECTOR *local_34;
	VECTOR *local_30;
	_sdPlane **local_2c;

	iVar10 = (cp->hd).speed * 3 >> 1;
	if (iVar10 < 0x20) {
		iVar10 = iVar10 * -0x48 + 0xe70;
	}
	else {
		iVar10 = 0x590 - iVar10;
	}
	uVar5 = (cp->hd).direction;
	local_58 = (_sdPlane *)0x0;
	uVar12 = uVar5 & 0xfff;
	uVar5 = uVar5 + (int)cp->wheel_angle & 0xfff;
	local_50 = (int)rcossin_tbl[uVar12 * 2];
	local_4c = (int)rcossin_tbl[uVar12 * 2 + 1];
	local_48 = (int)rcossin_tbl[uVar5 * 2];
	local_44 = (int)rcossin_tbl[uVar5 * 2 + 1];
	local_3c = GetPlayerId(cp);
	local_40 = car_cosmetics + (byte)(cp->ap).model;
	GetFrictionScalesDriver1(cp, cl, &local_60, &local_5c);
	(cp->hd).front_vel = 0;
	(cp->hd).rear_vel = 0;
	if (0xce4 < iVar10) {
		iVar10 = 0xce4;
	}
	local_38 = &local_b0;
	local_30 = &local_90;
	local_54 = 3;
	local_34 = &VStack160;
	local_2c = &local_58;
	pWVar17 = (cp->hd).wheel + 3;
	do {
		pVVar4 = local_38;
		setCopReg(2, in_zero, *(undefined4 *)(local_40->wheelDisp + local_54));
		setCopReg(2, in_at, *(undefined4 *)&local_40->wheelDisp[local_54].vz);
		copFunction(2, 0x480012);
		lVar3 = getCopReg(2, 0x19);
		local_38->vx = lVar3;
		lVar3 = getCopReg(2, 0x1a);
		pVVar4->vy = lVar3;
		lVar3 = getCopReg(2, 0x1b);
		pVVar4->vz = lVar3;
		iVar6 = FindSurfaceD2(local_38, local_30, local_34, local_2c);
		bVar9 = false;
		iVar6 = (iVar6 * (0x7e90 - wetness) >> 0xf) + 500;
		if (local_58 != (_sdPlane *)0x0) {
			bVar9 = local_58->surface == 4;
		}
		*(bool *)&pWVar17->onGrass = bVar9;
		if (local_58 == (_sdPlane *)0x0) {
			pWVar17->surface = '\0';
		}
		else {
			sVar2 = local_58->surface;
			if ((((sVar2 == 4) || (sVar2 == 6)) || (sVar2 == 0xb)) || (sVar2 == 9)) {
				pWVar17->surface = -0x80;
			}
			else {
				pWVar17->surface = '\0';
			}
			if (sVar2 == 8) {
				pWVar17->surface = pWVar17->surface | 2;
			}
			else {
				if (sVar2 < 9) {
					if (sVar2 == 6) {
					LAB_000821c4:
						pWVar17->surface = pWVar17->surface | 1;
					}
				}
				else {
					if (sVar2 == 9) goto LAB_000821c4;
					if (sVar2 == 0xb) {
						pWVar17->surface = pWVar17->surface | 3;
					}
				}
			}
		}
		bVar1 = pWVar17->susCompression;
		uVar5 = (uint)bVar1;
		chan = ((VStack160.vy - local_b0.vy) * local_90.vy + 0x800 >> 0xc) + 0xe;
		iVar16 = chan;
		if (chan < 0) {
			iVar16 = 0;
		}
		if (800 < chan) {
			iVar16 = 0xc;
		}
		if (cp->controlType == '\x01') {
			chan = iVar16 - uVar5;
			if (chan < 0) {
				chan = uVar5 - iVar16;
			}
			if ((0xc < chan) && ((local_54 & 1) != 0)) {
				chan = GetFreeChannel();
				if ((1 < NumPlayers) && (NoPlayerControl == 0)) {
					SetPlayerOwnsChannel(chan, (char)local_3c);
				}
				Start3DSoundVolPitch
				(chan, 1, 5, (cp->hd).where.t[0], (cp->hd).where.t[1], (cp->hd).where.t[2], -0x9c4, 400);
				SetChannelPosition3(chan, (VECTOR *)(cp->hd).where.t, (long *)0x0, -0x9c4, 400, 0);
			}
			if (iVar16 < 0x55) {
				if (0x30 < iVar16) {
					SetPadVibration((int)**(char **)cp->ai, '\x03');
				}
			}
			else {
				SetPadVibration((int)**(char **)cp->ai, '\x02');
			}
		}
		if (0x2a < iVar16) {
			iVar16 = 0x2a;
		}
		if ((iVar16 == 0) && (bVar1 == 0)) {
			pWVar17->susCompression = '\0';
		}
		else {
			local_b0.vz = local_b0.vz - (cp->hd).where.t[2];
			local_b0.vy = local_b0.vy - (cp->hd).where.t[1];
			local_b0.vx = local_b0.vx - (cp->hd).where.t[0];
			local_78 = 0;
			local_80 = 0;
			local_70 = ((cl->avel[1] * local_b0.vz - cl->avel[2] * local_b0.vy) + 0x800 >> 0xc) +
				cl->vel[0];
			local_6c = ((cl->avel[2] * local_b0.vx - cl->avel[0] * local_b0.vz) + 0x800 >> 0xc) +
				cl->vel[1];
			local_68 = ((cl->avel[0] * local_b0.vy - cl->avel[1] * local_b0.vx) + 0x800 >> 0xc) +
				cl->vel[2];
			chan = iVar16 * 0xe6 + uVar5 * -100;
			if (pWVar17->locked == '\0') {
				uVar5 = local_54 & 1;
				if (uVar5 == 0) {
					iVar15 = -local_48;
					iVar14 = local_44;
				}
				else {
					iVar15 = -local_50;
					iVar14 = local_4c;
				}
			}
			else {
				uVar12 = ratan2(local_70 >> 6, local_68 >> 6);
				uVar5 = local_54 & 1;
				iVar15 = (int)rcossin_tbl[(uVar12 & 0xfff) * 2 + 1];
				iVar11 = local_70;
				if (local_70 < 0) {
					iVar11 = -local_70;
				}
				iVar7 = local_68;
				if (local_68 < 0) {
					iVar7 = -local_68;
				}
				iVar14 = (int)rcossin_tbl[(uVar12 & 0xfff) * 2];
				if (iVar11 + iVar7 < 8000) {
					local_90.vx = 0;
					local_90.vy = 0x1000;
					local_90.vz = 0;
				}
			}
			iVar11 = local_70;
			if (local_70 < 0) {
				iVar11 = local_70 + 0x3f;
			}
			iVar7 = iVar14;
			if (iVar14 < 0) {
				iVar7 = iVar14 + 0x3f;
			}
			iVar13 = local_68;
			if (local_68 < 0) {
				iVar13 = local_68 + 0x3f;
			}
			iVar8 = iVar15;
			if (iVar15 < 0) {
				iVar8 = iVar15 + 0x3f;
			}
			iVar7 = (iVar11 >> 6) * (iVar7 >> 6) + (iVar13 >> 6) * (iVar8 >> 6);
			iVar11 = iVar10;
			if (iVar10 < 0) {
				iVar11 = iVar10 + 0x3f;
			}
			iVar13 = iVar7;
			if (iVar7 < 0) {
				iVar13 = iVar7 + 0x3f;
			}
			iVar11 = (iVar11 >> 6) * (iVar13 >> 6);
			if (iVar11 < 0) {
				iVar11 = -iVar11;
			}
			if (iVar7 < 0xc351) {
				if (iVar7 < -50000) {
				LAB_00082604:
					iVar7 = -0x30d4;
				}
				else {
					iVar7 = iVar10 * iVar7 + 0x800 >> 0xc;
					if (0x30d4 < iVar7) goto LAB_000825f4;
					if (iVar7 < -0x30d4) goto LAB_00082604;
				}
			}
			else {
			LAB_000825f4:
				iVar7 = 0x30d4;
			}
			if (uVar5 == 0) {
				iVar13 = local_60 * iVar7 + 0x800;
				iVar7 = iVar13 >> 0xc;
				if (pWVar17->locked == '\0') {
					if (cp->controlType == '\x03') {
						local_80 = local_80 + local_48 * cp->thrust;
						local_78 = local_78 + local_44 * cp->thrust;
					}
				}
				else {
					iVar7 = (iVar13 >> 0xd) + iVar7 >> 1;
					iVar13 = ((-iVar7 * iVar14 + 0x800 >> 0xc) * local_44 -
						(-iVar7 * iVar15 + 0x800 >> 0xc) * local_48) + 0x400 >> 0xb;
					local_80 = local_80 + iVar13 * local_44;
					local_78 = local_78 + -iVar13 * local_48;
				}
				if ((cp->hd).front_vel < iVar11) {
					(cp->hd).front_vel = iVar11;
				}
			}
			else {
				if (pWVar17->locked == '\0') {
					iVar7 = local_5c * iVar7 + 0x800 >> 0xc;
					if ((handlingType[cp->hndType].autoBrakeOn != '\0') && (0 < iVar7 * cp->wheel_angle)) {
						(cp->hd).autoBrake = -1;
					}
					local_80 = local_80 + -iVar15 * (int)cp->thrust;
					local_78 = local_78 + iVar14 * (int)cp->thrust;
				}
				else {
					iVar7 = local_60 * iVar7 + 0x2000 >> 0xe;
				}
				if ((cp->hd).rear_vel < iVar11) {
					(cp->hd).rear_vel = iVar11;
				}
			}
			local_80 = local_80 + (chan * local_90.vx - iVar7 * iVar14) + cl->vel[0] * -0xc;
			local_78 = local_78 + (chan * local_90.vz - iVar7 * iVar15) + cl->vel[2] * -0xc;
			if ((pWVar17->surface & 7) == 1) {
				local_80 = local_80 + cl->vel[0] * -0x4b;
				local_78 = local_78 + cl->vel[2] * -0x4b;
			}
			iVar15 = (int)(cp->hd).where.m[4];
			if (iVar15 < 0x800) {
				iVar15 = 0x1000 - iVar15;
				if (iVar15 < 0x1001) {
					iVar15 = 0x1000 - (iVar15 * iVar15 + 0x800 >> 0xc);
				}
				else {
					iVar15 = 0;
				}
				iVar6 = iVar6 * iVar15 + 0x800 >> 0xc;
			}
			if (local_90.vy < 0xccc) {
				iVar6 = iVar6 * local_90.vy * 5 >> 0xe;
			}
			local_7c = chan * local_90.vy + cl->vel[1] * -0xc + 0x800 >> 0xc;
			local_80 = (local_80 + 0x800 >> 0xc) * iVar6 >> 0xc;
			local_78 = (local_78 + 0x800 >> 0xc) * iVar6 >> 0xc;
			if (cp->controlType == '\x03') {
				if (gCopDifficultyLevel == 2) {
					local_b0.vy = local_b0.vy * 0xc;
				}
				else {
					local_b0.vy = local_b0.vy * 0x13;
				}
				if (local_b0.vy < 0) {
					local_b0.vy = local_b0.vy + 0x1f;
				}
				local_b0.vy = local_b0.vy >> 5;
			}
			chan = (cp->hd).acc[1];
			(cp->hd).acc[0] = (cp->hd).acc[0] + local_80;
			iVar6 = (cp->hd).acc[2];
			(cp->hd).acc[1] = chan + local_7c;
			(cp->hd).acc[2] = iVar6 + local_78;
			(cp->hd).aacc[0] =
				(cp->hd).aacc[0] + ((local_b0.vy * local_78 - local_b0.vz * local_7c) + 0x800 >> 0xc);
			(cp->hd).aacc[1] =
				(cp->hd).aacc[1] + ((local_b0.vz * local_80 - local_b0.vx * local_78) + 0x800 >> 0xc);
			(cp->hd).aacc[2] =
				(cp->hd).aacc[2] + ((local_b0.vx * local_7c - local_b0.vy * local_80) + 0x800 >> 0xc);
			pWVar17->susCompression = (char)iVar16;
		}
		pWVar17 = pWVar17 + -1;
		local_54 = local_54 - 1;
	} while (-1 < (int)local_54);
	if (((cp->hd).wheel[1].susCompression == '\0') && ((cp->hd).wheel[3].susCompression == '\0')) {
		uVar5 = 0x1a0000;
		if (cp->thrust < 1) {
			uVar5 = 0;
			if (-1 < cp->thrust) goto LAB_00082b9c;
			uVar5 = 0xffed0000;
		}
		uVar5 = uVar5 | 0x4000;
	}
	else {
		iVar10 = cl->vel[0];
		if (iVar10 < 0) {
			iVar10 = iVar10 + 0x3f;
		}
		if (local_50 < 0) {
			local_50 = local_50 + 0x3f;
		}
		iVar6 = cl->vel[2];
		if (iVar6 < 0) {
			iVar6 = iVar6 + 0x3f;
		}
		if (local_4c < 0) {
			local_4c = local_4c + 0x3f;
		}
		uVar5 = (iVar10 >> 6) * (local_50 >> 6) + (iVar6 >> 6) * (local_4c >> 6);
	}
LAB_00082b9c:
	(cp->hd).wheel_speed = uVar5;
	return;
	*/
}





