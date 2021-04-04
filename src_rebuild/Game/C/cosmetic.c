#include "driver2.h"
#include "cosmetic.h"
#include "system.h"
#include "mission.h"
#include "handling.h"
#include "cars.h"
#include "debris.h"
#include "pause.h"
#include "camera.h"
#include "director.h"
#include "main.h"

#include "INLINE_C.H"

#include "RAND.H"
#include "STRINGS.H"

char* CosmeticFiles[] = {
	"LEVELS\\CHICAGO.LCF",
	"LEVELS\\HAVANA.LCF",
	"LEVELS\\VEGAS.LCF",
	"LEVELS\\RIO.LCF",
};

CAR_COSMETICS car_cosmetics[MAX_CAR_MODELS];

// [D] [T]
void ProcessCosmeticsLump(char *lump_ptr, int lump_size)
{
	int model;
	char* ptr;
	int i;
	int offset;

	i = 0;

	do {
		model = MissionHeader->residentModels[i];

		if (model == 13)
		{
			model = 10 - (MissionHeader->residentModels[0] + MissionHeader->residentModels[1] + MissionHeader->residentModels[2]);

			if (model < 1) 
				model = 1;
			else if (model > 4) 
				model = 4;
		}

		if (model != -1) 
		{
			offset = *(int*)(lump_ptr + model * sizeof(int));

			ptr = (lump_ptr + offset);

			memcpy((char*)&car_cosmetics[i], ptr, sizeof(CAR_COSMETICS));

			FixCarCos(&car_cosmetics[i], model);
		}

		i++;
	} while (i < MAX_CAR_MODELS);
}

// [D] [T]
void LoadCosmetics(int level)
{
	LoadfileSeg(CosmeticFiles[level], (char*)_other_buffer, 0, 3120);
	ProcessCosmeticsLump((char*)_other_buffer, 0);
}

#define REVERSELIGHT_SIZE		14
#define INDICATORLIGHT_SIZE		20
#define BRAKELIGHT_SIZE			17
#define HEADLIGHT_SIZE			18
#define BACKLIGHT_SIZE			17

// [D] [T]
void AddReverseLight(CAR_DATA *cp)
{
	CAR_COSMETICS *car_cos;
	SVECTOR v1;
	CVECTOR col;

	car_cos = cp->ap.carCos;

	col.r = 100;
	col.g = 90;
	col.b = 90;

	v1 = car_cos->revLight;

	v1.vx += car_cos->cog.vx;
	v1.vy += car_cos->cog.vy;
	v1.vz += car_cos->cog.vz;

	if (cp->ap.damage[4] < 500)
	{
		ShowCarlight(&v1, cp, &col, REVERSELIGHT_SIZE, REVERSELIGHT_SIZE * 3, &light_texture, 0);
	}

	if (cp->ap.damage[3] < 500) 
	{
		v1.vx = car_cos->cog.vx * 2 - v1.vx;
		ShowCarlight(&v1, cp, &col, REVERSELIGHT_SIZE, REVERSELIGHT_SIZE * 3, &light_texture, 0);
	}
}

// [D] [T]
void SetupSpecCosmetics(char *loadbuffer)
{
	int model;
	model = MissionHeader->residentModels[4];

#ifndef PSX
	int offset;

	// [A] always load cosmetics from file
	// fixes limo cosmetics as well
	LoadfileSeg(CosmeticFiles[GameLevel], (char*)_other_buffer, 0, 3120);
	offset = *(int*)(_other_buffer + model * sizeof(int));

	memcpy((char*)&car_cosmetics[4], (char*)_other_buffer + offset, sizeof(CAR_COSMETICS));
#else
	memcpy((char*)&car_cosmetics[4], loadbuffer, sizeof(CAR_COSMETICS));
#endif

	// [A] don't forget
	FixCarCos(&car_cosmetics[4], model);
}



// [D] [T]
void AddIndicatorLight(CAR_DATA *cp, int Type)
{
	u_int brightness;
	char *life;
	CAR_COSMETICS *car_cos;
	char *life2;
	CVECTOR col;
	SVECTOR vfrnt;
	SVECTOR vback;

	//if (cp->controlType != CONTROL_TYPE_CIV_AI)		// [A] weird way to disable it here
	//	return;

	life = &cp->ap.life;
	life2 = &cp->ap.life2;

	if (cp->ap.life < 0)
		brightness = (0xff - (u_int)cp->ap.life) * 2;
	else
		brightness = cp->ap.life << 1;

	col.r = brightness & 0xFF;

	col.g = 0;
	col.b = 0;

	if (pauseflag == 0)
		*life += 8;

	car_cos = cp->ap.carCos;

	vback = car_cos->backInd;

	vback.vx += car_cos->cog.vx;
	vback.vy += car_cos->cog.vy;
	vback.vz += car_cos->cog.vz;

	vfrnt = car_cos->frontInd;

	vfrnt.vx += car_cos->cog.vx;
	vfrnt.vy += car_cos->cog.vy;
	vfrnt.vz += car_cos->cog.vz;

	if (Type == 0 || Type == 2)
	{
		if (cp->ap.damage[4] < 500)
		{
			*life2 += brightness >> 3;
			ShowCarlight(&vback, cp, &col, INDICATORLIGHT_SIZE, INDICATORLIGHT_SIZE * 4, &light_texture, 0);
		}

		if (cp->ap.damage[0] < 500) 
		{
			ShowCarlight(&vfrnt, cp, &col, INDICATORLIGHT_SIZE, INDICATORLIGHT_SIZE * 4, &light_texture, 1);
		}
	}

	if (Type - 1U < 2)
	{
		if (cp->ap.damage[3] < 500) 
		{
			vback.vx = car_cos->cog.vx * 2 - vback.vx;
			*life2 += brightness >> 3;

			ShowCarlight(&vback, cp, &col, INDICATORLIGHT_SIZE, INDICATORLIGHT_SIZE * 4, &light_texture, 0);
		}

		if (cp->ap.damage[1] < 500) 
		{
			vfrnt.vx = car_cos->cog.vx * 2 - vfrnt.vx;
			ShowCarlight(&vfrnt, cp, &col, INDICATORLIGHT_SIZE, INDICATORLIGHT_SIZE * 4, &light_texture, 1);
		}
	}
}

// [D] [T]
void AddBrakeLight(CAR_DATA *cp)
{
	short damageFac;
	int damIndex;
	short cogOffset;
	CAR_COSMETICS *car_cos;
	int offset;
	char *life2;
	int loop;
	SVECTOR v1;
	SVECTOR v2;
	SVECTOR vec;
	CVECTOR col;
	short doubleFlag;
	short verticalFlag;

	car_cos = cp->ap.carCos;
	col.r = 200;
	col.g = 0;
	col.b = 0;

	life2 = &cp->ap.life2;

	if (!(car_cos->extraInfo & 8))
		return;

	vec = car_cos->brakeLight;

	vec.vx += car_cos->cog.vx;
	vec.vy += car_cos->cog.vy;
	vec.vz += car_cos->cog.vz;

	offset = ((car_cos->extraInfo & 0x300) >> 6) + 10;
	cogOffset = vec.vz + car_cos->cog.vz;

	loop = 0;

	doubleFlag = (car_cos->extraInfo & 0x4000) != 0;
	verticalFlag = (car_cos->extraInfo & 0x1000) != 0;

	do {
		damIndex = (4 - loop);

		if (doubleFlag)
		{
			if (verticalFlag)
			{
				v1 = vec;
				v2 = vec;

				damageFac = cp->ap.damage[damIndex] >> 6;

				v1.vz = cogOffset + damageFac;
				v2.vz = cogOffset + damageFac;

				v1.vx = vec.vx;
				v1.vy = offset + vec.vy;
				v2.vy = vec.vy - offset;

				if (cp->ap.damage[damIndex] < 500)
				{
					ShowCarlight(&v1, cp, &col, BRAKELIGHT_SIZE, BRAKELIGHT_SIZE * 4, &light_texture, 0);
					ShowCarlight(&v2, cp, &col, BRAKELIGHT_SIZE, BRAKELIGHT_SIZE * 4, &light_texture, 0);
					*life2 += 8;
				}
			}
			else
			{
				v1 = vec;
				v2 = vec;

				damageFac = cp->ap.damage[damIndex] >> 6;
				v1.vz = cogOffset + damageFac;
				v2.vz = cogOffset + damageFac;

				v1.vx = offset + vec.vx;
				v2.vx = vec.vx - offset;

				if (cp->ap.damage[damIndex] < 500)
				{
					ShowCarlight(&v1, cp, &col, BRAKELIGHT_SIZE, BRAKELIGHT_SIZE * 4, &light_texture, 0);
					ShowCarlight(&v2, cp, &col, BRAKELIGHT_SIZE, BRAKELIGHT_SIZE * 4, &light_texture, 0);
					*life2 += 8;
				}
			}
		}
		else
		{
			v1 = vec;

			if (cp->ap.damage[damIndex] < 500)
			{
				ShowCarlight(&v1, cp, &col, BRAKELIGHT_SIZE, BRAKELIGHT_SIZE * 4, &light_texture, 0);
				*life2 += 8;
			}
		}

		offset = -offset;
				
		vec.vx = car_cos->cog.vx * 2 - vec.vx;

		loop++;
	} while (loop < 2);
}

// [D] [T]
void AddCopCarLight(CAR_DATA *cp)
{
	static char xpos1[8] = {
		48, 32, 16,  0,
		0, 16, 32, 48
	};

	int light;
	int size;
	short sign;
	char count_speed;
	int num_lights;
	CAR_COSMETICS *car_cos;
	char *coplife;
	u_int pos;
	int side;
	SVECTOR v1;
	CVECTOR col;

	coplife = &cp->ap.coplife;

	if (CameraCar == CAR_INDEX(cp) && cameraview == 2)
		return;

	if (FastForward != 0) 
		return;

	// don't display on flipped cars
	if (cp->hd.where.m[1][1] < 100)
		return;

	car_cos = cp->ap.carCos;

	// configure
	if (GameLevel == 1 || GameLevel == 3)
	{
		side = 1;
		num_lights = 2;
		pos = 3;
		count_speed = 48;
	}
	else if (GameLevel == 0)
	{
		side = 2;
		num_lights = 2;
		pos = 3;
		count_speed = 16;
	}
	else 
	{
		side = 2;
		num_lights = 3;
		count_speed = 16;
		pos = main_cop_light_pos + CAR_INDEX(cp) & 7;
	}

	sign = 1;

	do {
		side--;

		if (side == -1)
			return;

		light = num_lights;

		while (light-- >= 0) 
		{
			v1.vx = car_cos->cog.vx;

			if (GameLevel != 1 && GameLevel != 3) 
				v1.vx += (xpos1[pos] + car_cos->policeLight.vx) * sign;

			col.g = 90;
			v1.vy = car_cos->policeLight.vy + car_cos->cog.vy;

			if (gNight != 0)
				col.g = 50;

			if (pauseflag == 0 && (CameraCnt & 1U) != 0 && GameLevel == 2) 
				pos++;

			v1.vz = car_cos->policeLight.vz + car_cos->cog.vz;

			size = *coplife >> 1;

			// switch colours if needed
			if (GameLevel == 1 || GameLevel == 3 || GameLevel == 2 && side == 0)
			{
				col.b = 255;
				col.r = col.g;
			}
			else 
			{
				col.r = 255;
				col.b = col.g;
			}

			if (pauseflag == 0) 
				cp->ap.coplife += count_speed;

			ShowCarlight(&v1, cp, &col, size, size*3, &light_texture, 0xff);

			if (pauseflag == 0 && (CameraCnt & 1U) != 0 && GameLevel == 2) 
				pos++;

			pos = pos & 7;
		}

		sign = -sign;

	} while (true);
}

int gPlayerCarLights = 0;
int gcar_num = 0;

// [D] [T]
void AddNightLights(CAR_DATA *cp)
{
	short offset;
	int lightFlag;
	char lights;
	int damIndex;
	CAR_COSMETICS *car_cos;
	SVECTOR Position1;
	SVECTOR Position2;
	SVECTOR vec;
	CVECTOR col;
	CVECTOR col2;
	int lit;
	char *life2;
	short loop;
	short doubleFlag;
	short verticalFlag;
	short cogOffset;

	life2 = &cp->ap.life2;

	LeftLight = 0;
	RightLight = 0;

	car_cos = cp->ap.carCos;

	cogOffset = car_cos->cog.vx;
	gcar_num = CAR_INDEX(cp);

	vec.vx = car_cos->headLight.vx + car_cos->cog.vx;
	vec.vy = car_cos->headLight.vy + car_cos->cog.vy;
	vec.vz = car_cos->headLight.vz + car_cos->cog.vz;

	offset = ((car_cos->extraInfo & 0xC00) >> 8) + 10;
	doubleFlag = (car_cos->extraInfo & 0x8000);
	verticalFlag = (car_cos->extraInfo & 0x2000);

	// draw front lights
	lit = 0;
	loop = 0;
	do {
		lights = 0;
		lightFlag = 8 << (loop & 0x1f);

		col.r = 128;
		col.g = 124;
		col.b = 112;
		col2 = col;

		if (cp->ap.damage[loop] < 1000)
		{
			if (doubleFlag)
			{
				if (verticalFlag)
				{
					Position1.vy = offset + vec.vy;
					Position2.vy = vec.vy - offset;

					Position1.vx = vec.vx;
					Position2.vx = vec.vx;
				}
				else
				{
					Position1.vx = offset + vec.vx;
					Position2.vx = vec.vx - offset;

					Position1.vy = vec.vy;
					Position2.vy = vec.vy;
				}

				Position1.vz = vec.vz + (cp->ap.damage[loop] >> 6);
				Position2.vz = vec.vz + (cp->ap.damage[loop] >> 6);

				ShowCarlight(&Position1, cp, &col, HEADLIGHT_SIZE, HEADLIGHT_SIZE*4, &light_texture, lightFlag & 0xff | 1);

				lights = 1;
				lit++;

				if (cp->ap.damage[loop] < 500)
				{
					lights++;

					ShowCarlight(&Position2, cp, &col2, HEADLIGHT_SIZE, HEADLIGHT_SIZE * 4, &light_texture, 1);
					lit++;
				}
			}
			else
			{
				Position1.vx = vec.vx;
				Position1.vy = vec.vy;

				Position1.vz = vec.vz + (cp->ap.damage[loop] >> 6);
				Position2.vz = vec.vz + (cp->ap.damage[loop] >> 6);

				ShowCarlight(&Position1, cp, &col, HEADLIGHT_SIZE, HEADLIGHT_SIZE * 4, &light_texture, lightFlag & 0xff | 1);

				lights = 1;
				lit++;

				if (cp->ap.damage[loop] < 500)
					lights++;
			}
		}

		if (loop == 0)
			LeftLight = lights;
		else
			RightLight = lights;

		vec.vx = cogOffset * 2 - vec.vx;
		offset = -offset;

		loop++;
	} while (loop < 2);


	// check if back lights are supported
	// and draw
	if (car_cos->extraInfo & 8)
	{
		offset = ((car_cos->extraInfo & 0x300) >> 6) + 10;
		doubleFlag = car_cos->extraInfo & 0x4000;
		verticalFlag = car_cos->extraInfo & 0x1000;

		vec.vx = car_cos->brakeLight.vx + car_cos->cog.vx;
		vec.vy = car_cos->brakeLight.vy + car_cos->cog.vy;
		vec.vz = car_cos->brakeLight.vz + car_cos->cog.vz;

		loop = 0;

		do {
			lightFlag = 2 << (loop & 0x1f);
			damIndex = (4 - loop);

			col.r = 110;
			col.b = 0;
			col.g = 0;

			col2 = col;

			if (cp->ap.damage[damIndex] < 500)
			{
				if (doubleFlag)
				{
					// double flag
					if (verticalFlag)
					{
						Position1.vy = offset + vec.vy;
						Position2.vy = vec.vy - offset;

						Position1.vx = vec.vx;
						Position2.vx = vec.vx;
					}
					else
					{
						Position1.vx = offset + vec.vx;
						Position2.vx = vec.vx - offset;

						Position1.vy = vec.vy;
						Position2.vy = vec.vy;
					}

					Position2.vz = vec.vz - (cp->ap.damage[damIndex] >> 6);
					Position1.vz = vec.vz - (cp->ap.damage[damIndex] >> 6);

					ShowCarlight(&Position1, cp, &col, BACKLIGHT_SIZE, BACKLIGHT_SIZE * 3, &light_texture, lightFlag & 0xff);
					ShowCarlight(&Position2, cp, &col2, BACKLIGHT_SIZE, BACKLIGHT_SIZE * 3, &light_texture, 0);
				}
				else
				{
					Position1 = vec;

					ShowCarlight(&Position1, cp, &col, BACKLIGHT_SIZE, BACKLIGHT_SIZE * 3, &light_texture, lightFlag & 0xff);
				}

				*life2 += 16;
			}

			vec.vx = cogOffset * 2 - vec.vx;
			offset = -offset;

			loop++;
		} while (loop < 2);
	}

	// front lights pool
	if (lit)
	{
		col.r = 128;
		col.g = 120;
		col.b = 110;

		PlacePoolForCar(cp, &col, 1, 0);
	}

	// back lights pool
	col.r = *life2;
	if (col.r)
	{
		col.b = 0;
		col.g = 0;

		PlacePoolForCar(cp, &col, 0, 0);
		*life2 = 0;
	}
}

// [D] [T]
void AddSmokingEngine(CAR_DATA *cp, int black_smoke, int WheelSpeed)
{
	CAR_COSMETICS *car_cos;
	VECTOR SmokePos;
	VECTOR Drift;
	SVECTOR svec;

	if((CameraCnt & 3U) == (CAR_INDEX(cp) & 3U) && pauseflag == 0)
	{
		car_cos = cp->ap.carCos;

		svec.vx = (rand() & 0x7f) - 0x40; //car_cos->smoke.vx + car_cos->cog.vx;
		svec.vy = car_cos->smoke.vy + car_cos->cog.vy;
		svec.vz = car_cos->smoke.vz + car_cos->cog.vz;

		SmokePos.vx = cp->hd.where.t[0];
		SmokePos.vy = -cp->hd.where.t[1];
		SmokePos.vz = cp->hd.where.t[2];
		
		if (black_smoke != 0)
			SmokePos.vy -= 50;
	
		gte_SetRotMatrix(cp->hd.drawCarMat.m);

		InitFXPos(&SmokePos, &svec, cp);
		GetSmokeDrift(&Drift);

		if (black_smoke)
			Setup_Smoke(&SmokePos, 100, 500, SMOKE_BLACK, WheelSpeed, &Drift, 0);
		else
			Setup_Smoke(&SmokePos, 100, 400, SMOKE_WHITE, WheelSpeed, &Drift, 0);
	}
}

// [A] custom function for bringing back exhaust
void AddExhaustSmoke(CAR_DATA *cp, int black_smoke, int WheelSpeed)
{
	CAR_COSMETICS *car_cos;
	VECTOR SmokePos;
	VECTOR Drift;
	SVECTOR svec;
	SVECTOR smokedir;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	if (cp->controlType == CONTROL_TYPE_CIV_AI && cp->ai.c.thrustState == 3 && (cp->ai.c.ctrlState == 5 || cp->ai.c.ctrlState == 7))
		return;

	if (WheelSpeed > 512 * 64)
		return;

	if ((CameraCnt & 3U) == (CAR_INDEX(cp) & 3U) && pauseflag == 0)
	{
		car_cos = cp->ap.carCos;

		svec.vx = car_cos->exhaust.vx + car_cos->cog.vx;
		svec.vy = car_cos->exhaust.vy + car_cos->cog.vy;
		svec.vz = car_cos->exhaust.vz + car_cos->cog.vz;

		SmokePos.vx = cp->hd.where.t[0];
		SmokePos.vy = -cp->hd.where.t[1];
		SmokePos.vz = cp->hd.where.t[2];

		gte_SetRotMatrix(cp->hd.drawCarMat.m);

		InitFXPos(&SmokePos, &svec, cp);
		GetSmokeDrift(&Drift);

		gte_ldv0(&svec);
		gte_rtir();
		gte_stsv(&smokedir);

		Drift.vx /= 2;
		Drift.vz /= 2;

		Drift.vx -= FIXEDH(smokedir.vx) / 2;
		Drift.vz -= FIXEDH(smokedir.vz) / 2;

		if (black_smoke)
			Setup_Smoke(&SmokePos, 10, 40, SMOKE_BLACK, WheelSpeed, &Drift, 1);
		else
			Setup_Smoke(&SmokePos, 10, 40, SMOKE_WHITE, WheelSpeed, &Drift, 1);
	}
}

// [D] [T]
void AddFlamingEngine(CAR_DATA *cp)
{
	CAR_COSMETICS *car_cos;
	VECTOR SmokePos;
	SVECTOR svec;
	VECTOR Drift;

	if ((CameraCnt & 1U) == (CAR_INDEX(cp) & 1U) && pauseflag == 0)
	{
		car_cos = cp->ap.carCos;

		svec.vx = (rand() & 0x3f); //car_cos->smoke.vx + car_cos->cog.vx;
		svec.vy = car_cos->fire.vy + car_cos->cog.vy;
		svec.vz = car_cos->fire.vz + car_cos->cog.vz + (rand() & 0x3f);

		SmokePos.vx = (cp->hd).where.t[0];

		SmokePos.vz = (cp->hd).where.t[2];
		SmokePos.vy = -(cp->hd).where.t[1];

		SetRotMatrix(&(cp->hd).drawCarMat);
		InitFXPos(&SmokePos, &svec, cp);
		Drift.vx = 0;
		Drift.vy = 0;
		Drift.vz = 0;

		Setup_Smoke(&SmokePos, 50, 100, SMOKE_FIRE, 0, &Drift, 0);
	}
}





