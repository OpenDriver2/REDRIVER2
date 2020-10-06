#include "DRIVER2.H"
#include "COSMETIC.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "HANDLING.H"
#include "CARS.H"
#include "DEBRIS.H"
#include "PAUSE.H"
#include "CAMERA.H"
#include "DIRECTOR.H"
#include "MAIN.H"

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
CAR_COSMETICS dummyCosmetics = { 0 };

// decompiled code
// original method signature: 
// void /*$ra*/ LoadCosmetics(int level /*$a0*/)
 // line 188, offset 0x00031160
	/* begin block 1 */
		// Start line: 190
		// Start offset: 0x00031160
	/* end block 1 */
	// End offset: 0x000311B0
	// End Line: 203

	/* begin block 2 */
		// Start line: 376
	/* end block 2 */
	// End Line: 377

	/* begin block 3 */
		// Start line: 2374
	/* end block 3 */
	// End Line: 2375

	/* begin block 4 */
		// Start line: 2381
	/* end block 4 */
	// End Line: 2382

char _cosmeticBuffer[3120];

// [D] [T]
void LoadCosmetics(int level)
{
	LoadfileSeg(CosmeticFiles[level], _cosmeticBuffer, 0, sizeof(_cosmeticBuffer));
	ProcessCosmeticsLump(_cosmeticBuffer, 0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessCosmeticsLump(char *lump_ptr /*$s2*/, int lump_size /*$a1*/)
 // line 213, offset 0x000311b0
	/* begin block 1 */
		// Start line: 214
		// Start offset: 0x000311B0
		// Variables:
	// 		int i; // $t0
	// 		int model; // $a1
	// 		int offset; // $a0

		/* begin block 1.1 */
			// Start line: 236
			// Start offset: 0x00031238
		/* end block 1.1 */
		// End offset: 0x00031338
		// End Line: 240
	/* end block 1 */
	// End offset: 0x00031360
	// End Line: 243

	/* begin block 2 */
		// Start line: 2415
	/* end block 2 */
	// End Line: 2416

	/* begin block 3 */
		// Start line: 2426
	/* end block 3 */
	// End Line: 2427

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
			offset = *(int*)(lump_ptr + model * 4);

			ptr = (lump_ptr + offset);

			memcpy(&car_cosmetics[i], ptr, sizeof(CAR_COSMETICS));

			FixCarCos(&car_cosmetics[i], model);
		}

		i++;
	} while (i < MAX_CAR_MODELS);
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddReverseLight(struct _CAR_DATA *cp /*$s1*/)
 // line 252, offset 0x0002f994
	/* begin block 1 */
		// Start line: 253
		// Start offset: 0x0002F994
		// Variables:
	// 		struct CAR_COSMETICS *car_cos; // $a1
	// 		struct SVECTOR v1; // stack offset -32
	// 		struct CVECTOR col; // stack offset -24
	// 		short cogOffset; // $s2
	/* end block 1 */
	// End offset: 0x0002FAEC
	// End Line: 283

	/* begin block 2 */
		// Start line: 504
	/* end block 2 */
	// End Line: 505

	/* begin block 3 */
		// Start line: 510
	/* end block 3 */
	// End Line: 511

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void AddReverseLight(_CAR_DATA *cp)
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
		ShowCarlight(&v1, cp, &col, 0xe, &light_texture, 0);
	}

	if (cp->ap.damage[3] < 500) 
	{
		v1.vx = car_cos->cog.vx * 2 - v1.vx;
		ShowCarlight(&v1, cp, &col, 0xe, &light_texture, 0);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupSpecCosmetics(char *loadbuffer /*$a0*/)
 // line 293, offset 0x00031360
	/* begin block 1 */
		// Start line: 298
		// Start offset: 0x00031360
		// Variables:
	// 		int *to; // $a1
	// 		int *from; // $a0
	// 		int *end; // $v1
	/* end block 1 */
	// End offset: 0x00031398
	// End Line: 311

	/* begin block 2 */
		// Start line: 2564
	/* end block 2 */
	// End Line: 2565

	/* begin block 3 */
		// Start line: 2615
	/* end block 3 */
	// End Line: 2616

	/* begin block 4 */
		// Start line: 2619
	/* end block 4 */
	// End Line: 2620

// [D] [T]
void SetupSpecCosmetics(char *loadbuffer)
{
	// [A] this is better
	memcpy(&car_cosmetics[4], loadbuffer, sizeof(CAR_COSMETICS));
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddIndicatorLight(struct _CAR_DATA *cp /*$s0*/, int Type /*$s6*/)
 // line 325, offset 0x0002faec
	/* begin block 1 */
		// Start line: 326
		// Start offset: 0x0002FAEC
		// Variables:
	// 		struct CAR_COSMETICS *car_cos; // $a1
	// 		struct CVECTOR col; // stack offset -56
	// 		struct SVECTOR vfrnt; // stack offset -48
	// 		struct SVECTOR vback; // stack offset -40
	// 		char tempcol; // $s1
	// 		char *life; // $a0
	// 		char *life2; // $s3
	// 		short cogOffset; // $s2
	/* end block 1 */
	// End offset: 0x0002FDBC
	// End Line: 397

	/* begin block 2 */
		// Start line: 623
	/* end block 2 */
	// End Line: 624

	/* begin block 3 */
		// Start line: 666
	/* end block 3 */
	// End Line: 667

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void AddIndicatorLight(_CAR_DATA *cp, int Type)
{
	uint brightness;
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
		brightness = (0xff - (uint)cp->ap.life) * 2;
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
			ShowCarlight(&vback, cp, &col, 0x14, &light_texture, 0);
		}

		if (cp->ap.damage[0] < 500) 
		{
			ShowCarlight(&vfrnt, cp, &col, 0x14, &light_texture, 1);
		}
	}

	if (Type - 1U < 2)
	{
		if (cp->ap.damage[3] < 500) 
		{
			vback.vx = car_cos->cog.vx * 2 - vback.vx;
			*life2 += brightness >> 3;

			ShowCarlight(&vback, cp, &col, 20, &light_texture, 0);
		}

		if (cp->ap.damage[1] < 500) 
		{
			vfrnt.vx = car_cos->cog.vx * 2 - vfrnt.vx;
			ShowCarlight(&vfrnt, cp, &col, 20, &light_texture, 1);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddBrakeLight(struct _CAR_DATA *cp /*$s5*/)
 // line 407, offset 0x0002fde4
	/* begin block 1 */
		// Start line: 408
		// Start offset: 0x0002FDE4
		// Variables:
	// 		struct CAR_COSMETICS *car_cos; // $a1
	// 		struct SVECTOR v1; // stack offset -88
	// 		struct SVECTOR v2; // stack offset -80
	// 		struct SVECTOR vec; // stack offset -72
	// 		struct CVECTOR col; // stack offset -64
	// 		char *life2; // $s2
	// 		short doubleFlag; // stack offset -56
	// 		short verticalFlag; // stack offset -52
	// 		short offset; // $s1
	// 		short loop; // $fp
	// 		short damIndex; // $v0
	// 		short cogOffset; // $a3
	/* end block 1 */
	// End offset: 0x00030118
	// End Line: 504

	/* begin block 2 */
		// Start line: 867
	/* end block 2 */
	// End Line: 868

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void AddBrakeLight(_CAR_DATA *cp)
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

	if (car_cos->extraInfo & 8)
	{
		vec = car_cos->brakeLight;

		vec.vx += car_cos->cog.vx;
		vec.vy += car_cos->cog.vy;
		vec.vz += car_cos->cog.vz;

		offset = ((car_cos->extraInfo & 0x300) >> 6) + 10;
		cogOffset = vec.vz + car_cos->cog.vz;

		if (car_cos->extraInfo & 8) 
		{
			loop = 0;

			do {
				damIndex = (4 - loop);

				if ((car_cos->extraInfo & 0x4000) == 0)
				{
					v1 = vec;

					if (cp->ap.damage[damIndex] < 500)
					{
						ShowCarlight(&v1, cp, &col, 0x11, &light_texture, 0);
						*life2 += 8;
					}
				}
				else if ((car_cos->extraInfo & 0x1000) == 0)
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
						ShowCarlight(&v1, cp, &col, 17, &light_texture, 0);
						ShowCarlight(&v2, cp, &col, 17, &light_texture, 0);
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

					v1.vx = vec.vx;
					v1.vy = offset + vec.vy;
					v2.vy = vec.vy - offset;

					if (cp->ap.damage[damIndex] < 500)
					{
						ShowCarlight(&v1, cp, &col, 0x11, &light_texture, 0);
						ShowCarlight(&v2, cp, &col, 0x11, &light_texture, 0);
						*life2 += 8;
					}
				}

				offset = -offset;
				
				vec.vx = car_cos->cog.vx * 2 - vec.vx;

				loop++;
			} while (loop < 2);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddCopCarLight(struct _CAR_DATA *cp /*$t0*/)
 // line 514, offset 0x00030148
	/* begin block 1 */
		// Start line: 515
		// Start offset: 0x00030148
		// Variables:
	// 		int size; // $a3
	// 		int light; // $s1
	// 		int pos; // $s3
	// 		int side; // $s4
	// 		int num_lights; // $t5
	// 		int count_speed; // $t4
	// 		char col1; // $a2
	// 		char col2; // $a1
	// 		static char xpos1[8]; // offset 0x10
	// 		int sign; // $t1
	// 		char *coplife; // $s2
	// 		struct SVECTOR v1; // stack offset -88
	// 		struct CVECTOR col; // stack offset -80
	// 		struct CAR_COSMETICS *car_cos; // $s0
	// 		short cogOffset; // $fp
	/* end block 1 */
	// End offset: 0x00030514
	// End Line: 644

	/* begin block 2 */
		// Start line: 1341
	/* end block 2 */
	// End Line: 1342

	/* begin block 3 */
		// Start line: 1347
	/* end block 3 */
	// End Line: 1348

// [D] [T]
void AddCopCarLight(_CAR_DATA *cp)
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
	uint pos;
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

			ShowCarlight(&v1, cp, &col, size, &light_texture, 0xff);

			if (pauseflag == 0 && (CameraCnt & 1U) != 0 && GameLevel == 2) 
				pos++;

			pos = pos & 7;
		}

		sign = -sign;

	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddNightLights(struct _CAR_DATA *cp /*$s6*/)
 // line 653, offset 0x00030544
	/* begin block 1 */
		// Start line: 654
		// Start offset: 0x00030544
		// Variables:
	// 		static struct MATRIX work_matrix; // offset 0x0
	// 		struct CAR_COSMETICS *car_cos; // $fp
	// 		struct SVECTOR Position1; // stack offset -104
	// 		struct SVECTOR Position2; // stack offset -96
	// 		struct SVECTOR vec; // stack offset -88
	// 		struct CVECTOR col; // stack offset -80
	// 		int lit; // stack offset -72
	// 		int lightFlag; // $t0
	// 		char *life2; // stack offset -68
	// 		short damIndex; // $s5
	// 		short loop; // stack offset -64
	// 		short offset; // $s2
	// 		short doubleFlag; // stack offset -60
	// 		short verticalFlag; // stack offset -56
	// 		short cogOffset; // stack offset -52
	/* end block 1 */
	// End offset: 0x00030D9C
	// End Line: 919

	/* begin block 2 */
		// Start line: 1653
	/* end block 2 */
	// End Line: 1654

	/* begin block 3 */
		// Start line: 1663
	/* end block 3 */
	// End Line: 1664

/* WARNING: Could not reconcile some variable overlaps */

int gPlayerCarLights = 0;
int gcar_num = 0;

// [D] [T]
void AddNightLights(_CAR_DATA *cp)
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

		col.r = 255;
		col.b = 255;
		col.g = 255;
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

				ShowCarlight(&Position1, cp, &col, 20, &light_texture, lightFlag & 0xff | 1);

				lights = 1;
				lit++;

				if (cp->ap.damage[loop] < 500)
				{
					lights = 2;

					ShowCarlight(&Position2, cp, &col2, 20, &light_texture, 1);
					lit++;
				}
			}
			else
			{
				Position1.vx = vec.vx;
				Position1.vy = vec.vy;

				Position1.vz = vec.vz + (cp->ap.damage[loop] >> 6);
				Position2.vz = vec.vz + (cp->ap.damage[loop] >> 6);

				lights = 1;

				ShowCarlight(&Position1, cp, &col, 20, &light_texture, lightFlag & 0xff | 1);
				lit++;
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

			if (cp->controlType == CONTROL_TYPE_PLAYER)
				col.r = 56;
			else
				col.r = 255;

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

					ShowCarlight(&Position1, cp, &col, 17, &light_texture, lightFlag & 0xff);
					ShowCarlight(&Position2, cp, &col2, 17, &light_texture, 0);
				}
				else
				{
					Position1 = vec;

					ShowCarlight(&Position1, cp, &col, 17, &light_texture, lightFlag & 0xff);
				}

				*life2 += 16;
			}

			vec.vx = cogOffset * 2 - vec.vx;
			offset = -offset;

			loop++;
		} while (loop < 2);
	}

	// front lights pool
	if (lit != 0)
	{
		col.r = (lit << 4);
		col.g = col.r;
		col.b = col.r;
		PlacePoolForCar(cp, &col, 1, 0);
	}

	// back lights pool
	col.r = *life2;
	if (col.r != 0)
	{
		col.b = 0;
		col.g = 0;

		PlacePoolForCar(cp, &col, 0, 0);
		*life2 = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddSmokingEngine(struct _CAR_DATA *cp /*$s0*/, int black_smoke /*$s2*/, int WheelSpeed /*$s3*/)
 // line 989, offset 0x00030d9c
	/* begin block 1 */
		// Start line: 990
		// Start offset: 0x00030D9C
		// Variables:
	// 		struct VECTOR SmokePos; // stack offset -64
	// 		struct CAR_COSMETICS *car_cos; // $a0
	// 		struct VECTOR Drift; // stack offset -48
	// 		struct SVECTOR svec; // stack offset -32
	/* end block 1 */
	// End offset: 0x00030F90
	// End Line: 1038

	/* begin block 2 */
		// Start line: 3039
	/* end block 2 */
	// End Line: 3040

/* WARNING: Could not reconcile some variable overlaps */

int gDoSmoke = 1;

// [D] [T]
void AddSmokingEngine(_CAR_DATA *cp, int black_smoke, int WheelSpeed)
{
	CAR_COSMETICS *car_cos;
	VECTOR SmokePos;
	VECTOR Drift;
	SVECTOR svec;

	if((CameraCnt & 3U) == (CAR_INDEX(cp) & 3U) && gDoSmoke != 0 && pauseflag == 0)
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

		if (black_smoke == 0)
			Setup_Smoke(&SmokePos, 100, 400, 2, WheelSpeed, &Drift, 0);
		else
			Setup_Smoke(&SmokePos, 100, 500, 1, WheelSpeed, &Drift, 0);
	}
}

// [A] custom function for bringing back exhaust
void AddExhaustSmoke(_CAR_DATA *cp, int black_smoke, int WheelSpeed)
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

	if ((CameraCnt & 3U) == (CAR_INDEX(cp) & 3U) && gDoSmoke != 0 && pauseflag == 0)
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

		if (black_smoke == 0)
			Setup_Smoke(&SmokePos, 10, 40, 2, WheelSpeed, &Drift, 1);
		else
			Setup_Smoke(&SmokePos, 10, 40, 1, WheelSpeed, &Drift, 1);
	}
}

// decompiled code
// original method signature: 
// void /*$ra*/ AddFlamingEngine(struct _CAR_DATA *cp /*$s1*/)
 // line 1048, offset 0x00030fac
	/* begin block 1 */
		// Start line: 1049
		// Start offset: 0x00030FAC
		// Variables:
	// 		struct VECTOR SmokePos; // stack offset -56
	// 		struct SVECTOR svec; // stack offset -40
	// 		struct CAR_COSMETICS *car_cos; // $a0
	// 		struct VECTOR Drift; // stack offset -32
	/* end block 1 */
	// End offset: 0x0003114C
	// End Line: 1084

	/* begin block 2 */
		// Start line: 3174
	/* end block 2 */
	// End Line: 3175

/* WARNING: Could not reconcile some variable overlaps */

// [D] [T]
void AddFlamingEngine(_CAR_DATA *cp)
{
	CAR_COSMETICS *car_cos;
	VECTOR SmokePos;
	SVECTOR svec;
	VECTOR Drift;

	if ((CameraCnt & 1U) == (CAR_INDEX(cp) & 1U) && gDoSmoke != 0 && pauseflag == 0)
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

		Setup_Smoke(&SmokePos, 0x32, 100, 4, 0, &Drift, 0);
	}
}





