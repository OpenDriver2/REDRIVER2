#include "driver2.h"
#include "wheelforces.h"
#include "cars.h"
#include "main.h"
#include "gamesnd.h"
#include "debris.h"
#include "handling.h"
#include "cosmetic.h"
#include "dr2roads.h"
#include "mission.h"
#include "pad.h"
#include "sound.h"
#include "glaunch.h"
#include "system.h"

#define GRAVITY_FORCE		(-7456)			// D1 has -10922

struct CAR_LOCALS
{
	LONGVECTOR4 vel;
	LONGVECTOR4 avel;
	int extraangulardamping;
	int aggressive;
};

HANDLING_TYPE handlingType[7] =
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

// [D] [T]
void GetFrictionScalesDriver1(CAR_DATA* cp, CAR_LOCALS* cl, int* frontFS, int* rearFS)
{
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

		D_CHECK_ERROR(hp->autoBrakeOn == 2, "invalid autoBrakeOn");
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

// [D] [T]
void ConvertTorqueToAngularAcceleration(CAR_DATA* cp, CAR_LOCALS* cl)
{
	int twistY, twistZ;
	int zd;
	int i;

	twistY = car_cosmetics[cp->ap.model].twistRateY;
	twistZ = car_cosmetics[cp->ap.model].twistRateZ;

	zd = (twistZ - twistY) * FIXEDH(cp->hd.where.m[0][2] * cp->hd.aacc[0] + cp->hd.where.m[1][2] * cp->hd.aacc[1] + cp->hd.where.m[2][2] * cp->hd.aacc[2]);

	for (i = 0; i < 3; i++)
	{
		cp->hd.aacc[i] = cp->hd.aacc[i] * twistY + FIXEDH(cp->hd.where.m[i][2] * zd - cl->avel[i] * 128);

		if (cl->extraangulardamping == 1)
			cp->hd.aacc[i] -= cl->avel[i] / 8;
	}
}


// [D] [T]
void AddWheelForcesDriver1(CAR_DATA* cp, CAR_LOCALS* cl)
{
	int oldCompression, newCompression;
	int dir;
	int forcefac;
	int angle;
	int lfx, lfz;
	int sidevel, slidevel;
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
	int cdx, cdz;
	int sdx, sdz;
	CAR_COSMETICS* car_cos;
	int player_id;

	oldSpeed = cp->hd.speed * 3 >> 1;

	if (oldSpeed < 32)
		oldSpeed = oldSpeed * -72 + 3696;
	else
		oldSpeed = 1424 - oldSpeed;

	dir = cp->hd.direction;
	cdx = RSIN(dir);
	cdz = RCOS(dir);

	dir += cp->wheel_angle;
	sdx = RSIN(dir);
	sdz = RCOS(dir);

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

					Start3DSoundVolPitch(chan, SOUND_BANK_SFX, 1, cp->hd.where.t[0], cp->hd.where.t[1], cp->hd.where.t[2], -2500, 400);
					SetChannelPosition3(chan, (VECTOR*)cp->hd.where.t, NULL, -2500, 400, 0);
				}
			}

			if (newCompression >= 65)
				SetPadVibration(*cp->ai.padid, 1);
			else if (newCompression >= 35)
				SetPadVibration(*cp->ai.padid, 2);
			else if (newCompression > 25)
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

				lfx = RSIN(dir);
				lfz = RCOS(dir);

				if (ABS(pointVel[0]) + ABS(pointVel[2]) < 8000)
				{
					surfaceNormal[0] = 0;
					surfaceNormal[1] = ONE;
					surfaceNormal[2] = 0;
				}
			}
			else
			{
				if (i & 1)
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
				sidevel = frontFS * slidevel + 2048 >> 12;
				
				if (wheel->locked)
				{
					sidevel = (frontFS * slidevel + 2048 >> 13) + sidevel >> 1;
					
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

// [D] [T]
void StepOneCar(CAR_DATA* cp)
{
	static int frictionLimit[6] = {
		1005 * ONE, 6030 * ONE,
		1005 * ONE, 5025 * ONE,
		1884 * ONE, 5025 * ONE
	};

	volatile int impulse;
	CAR_COSMETICS* car_cos;
	int friToUse;
	int lift;
	int a, b, speed;
	int count, i;
	CAR_LOCALS _cl;
	LONGVECTOR4 deepestNormal, deepestLever, deepestPoint;
	LONGVECTOR4 pointPos, surfacePoint, surfaceNormal;
	LONGVECTOR4 lever, reaction;
	VECTOR direction;
	sdPlane* SurfacePtr;

	if (cp->controlType == CONTROL_TYPE_NONE)
		return;

	SurfacePtr = NULL;
	_cl.aggressive = handlingType[cp->hndType].aggressiveBraking;
	_cl.extraangulardamping = 0;

	for (i = 0; i < 3; i++)
	{
		_cl.vel[i] = cp->st.n.linearVelocity[i];
		_cl.avel[i] = cp->st.n.angularVelocity[i];
		
		cp->st.n.fposition[i] = (cp->st.n.fposition[i] & 0xF) + cp->hd.where.t[i] * 16;
	}

	cp->hd.acc[0] = 0;
	cp->hd.acc[1] = GRAVITY_FORCE; // apply gravity
	cp->hd.acc[2] = 0;

	// calculate car speed
	a = ABS(FIXEDH(_cl.vel[0]));
	b = ABS(FIXEDH(_cl.vel[2]));

	if (a < b)
		speed = b + a / 2;
	else
		speed = a + b / 2;

	cp->hd.speed = speed;

	car_cos = cp->ap.carCos;
	lift = 0;

	gte_SetRotMatrix(&cp->hd.where);
	gte_SetTransMatrix(&cp->hd.where);

	count = 12;

	if (cp->hd.where.m[1][1] > 2048)
	{
		if(cp->controlType == CONTROL_TYPE_CIV_AI)
			count = (cp->totalDamage != 0) * 4;
		else
			count = 4;
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
		int strikeVel;
		int componant;

		int lever_dot_n;
		int twistY;
		int displacementsquared;

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

		//if (lift != 0)
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