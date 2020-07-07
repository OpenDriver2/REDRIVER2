#include "THISDUST.H"
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

#include <string.h>
#include <stdlib.h>

char* CosmeticFiles[] = {
	"LEVELS\\CHICAGO.LCF",
	"LEVELS\\HAVANA.LCF",
	"LEVELS\\VEGAS.LCF",
	"LEVELS\\RIO.LCF",
};


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

// [D]
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

CAR_COSMETICS car_cosmetics[5];
CAR_COSMETICS dummyCosmetics = { 0 };

void ProcessCosmeticsLump(char *lump_ptr, int lump_size)
{
	long *plVar1;
	long lVar2;
	int externalModelNumber;
	char* ptr;
	CAR_COSMETICS *pCVar3;
	int i = 0;

	do {
		externalModelNumber = MissionHeader->residentModels[i];

		if (externalModelNumber == 0xd) 
		{
			externalModelNumber = 10 - (MissionHeader->residentModels[0] + MissionHeader->residentModels[1] + MissionHeader->residentModels[2]);

			if (externalModelNumber < 1) 
			{
				externalModelNumber = 1;
			}
			else if (4 < externalModelNumber) 
			{
				externalModelNumber = 4;
			}
		}

		if (externalModelNumber != -1) 
		{
			pCVar3 = &car_cosmetics[i];
			ptr = (lump_ptr + *(int *)(lump_ptr + externalModelNumber * 4));

			memcpy(&car_cosmetics[i], ptr, sizeof(CAR_COSMETICS));

			FixCarCos(&car_cosmetics[i], externalModelNumber);
		}
		i++;
	} while (i < 5);
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

// [D]
void AddReverseLight(_CAR_DATA *cp)
{
	CAR_COSMETICS *car_cos;
	SVECTOR v1;
	CVECTOR col;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

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

// [D]
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

// [D]
void AddIndicatorLight(_CAR_DATA *cp, int Type)
{
	uint uVar3;
	char *life;
	CAR_COSMETICS *car_cos;
	unsigned char uVar8;
	char *life2;
	CVECTOR col;
	SVECTOR vfrnt;
	SVECTOR vback;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	//if (cp->controlType != 2)		// [A] weird way to disable it here
	//	return;

	life = &cp->ap.life;
	life2 = &cp->ap.life2;

	if (cp->ap.life < 0)
		uVar3 = (0xff - (uint)cp->ap.life) * 2;
	else
		uVar3 = cp->ap.life << 1;

	col.r = uVar3 & 0xFF;

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
			*life2 += uVar3 >> 3;
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
			*life2 += uVar3 >> 3;

			ShowCarlight(&vback, cp, &col, 0x14, &light_texture, 0);
		}

		if (cp->ap.damage[1] < 500) 
		{
			vfrnt.vx = car_cos->cog.vx * 2 - vfrnt.vx;
			ShowCarlight(&vfrnt, cp, &col, 0x14, &light_texture, 1);
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

void AddBrakeLight(_CAR_DATA *cp)
{
	short sVar1;
	ushort uVar2;
	short sVar3;
	short sVar4;
	int iVar5;
	ushort uVar6;
	uint uVar7;
	CAR_COSMETICS *car_cos;
	int iVar9;
	char *life2;
	short *psVar11;
	int iVar12;
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

	uVar2 = car_cos->extraInfo;
	sVar1 = car_cos->cog.vx;

	life2 = &cp->ap.life2;

	if ((uVar2 & 8) != 0)
	{
		vec = car_cos->brakeLight;

		vec.vx += car_cos->cog.vx;
		vec.vy += car_cos->cog.vy;
		vec.vz += car_cos->cog.vz;

		uVar7 = *(uint *)&(car_cos->brakeLight).vz;

		iVar9 = ((car_cos->extraInfo & 0x300) >> 6) + 10;
		uVar6 = vec.vz + car_cos->cog.vz;
		uVar7 = uVar7 & 0xffff0000;

		if ((car_cos->extraInfo & 8U) != 0) 
		{
			iVar12 = 0;
			psVar11 = cp->ap.damage;

			do {
				iVar5 = (4 - iVar12);// *0x10000 >> 0x10;
				sVar4 = iVar9;

				if ((uVar2 & 0x4000) == 0)
				{
					v1 = vec;

					if (psVar11[iVar5] < 500)
					{
						ShowCarlight(&v1, cp, &col, 0x11, &light_texture, 0);
						*life2 += 8;
					}

				}
				else if ((uVar2 & 0x1000) == 0)
				{
					v1 = vec;
					v2 = vec;

					sVar3 = psVar11[iVar5] >> 6;
					v1.vz = uVar6 + sVar3;
					v2.vz = uVar6 + sVar3;

					v1.vx = sVar4 + vec.vx;
					v2.vx = vec.vx - sVar4;

					if (psVar11[iVar5] < 500)
					{
						ShowCarlight(&v1, cp, &col, 0x11, &light_texture, 0);
						ShowCarlight(&v2, cp, &col, 0x11, &light_texture, 0);
						*life2 += 8;
					}
				}
				else
				{
					v1 = vec;
					v2 = vec;

					sVar3 = psVar11[iVar5] >> 6;

					v1.vz = uVar6 + sVar3;
					v2.vz = uVar6 + sVar3;

					v1.vx = vec.vx;
					v1.vy = sVar4 + vec.vy;
					v2.vy = vec.vy - sVar4;

					if (psVar11[iVar5] < 500)
					{
						ShowCarlight(&v1, cp, &col, 0x11, &light_texture, 0);
						ShowCarlight(&v2, cp, &col, 0x11, &light_texture, 0);
						*life2 += 8;
					}
				}

				iVar9 = -sVar4;
				iVar12++;// = (iVar12 + 1) * 0x10000 >> 0x10;
				vec.vx = car_cos->cog.vx * 2 - vec.vx;

			} while (iVar12 < 2);
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

// [D]
void AddCopCarLight(_CAR_DATA *cp)
{
	static char xpos1[8] = {
		0x30, 0x20, 0x10,  0x0,
		0x0, 0x10, 0x20, 0x30
	};

	short sVar1;
	short sVar2;
	int iVar3;
	int uVar4;
	short sVar5;
	char cVar6;
	int iVar7;
	CAR_COSMETICS *car_cos;
	char *coplife;
	uint uVar10;
	int iVar11;
	SVECTOR v1;
	CVECTOR col;

	sVar5 = 1;
	coplife = &cp->ap.coplife;

	if (cp < car_data) 
	{
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	if (CameraCar == CAR_INDEX(cp) && cameraview == 2)
		return;

	if (FastForward != 0) 
		return;

	if (cp->hd.where.m[1][1] < 100)
		return;

	car_cos = cp->ap.carCos;
	sVar1 = (car_cos->cog).vx;

	if (GameLevel == 1 || GameLevel == 3)
	{
		iVar11 = 1;
		iVar7 = 2;
		uVar10 = 3;
		cVar6 = 48;
	}
	else if (GameLevel == 0)
	{
		iVar11 = 2;
		iVar7 = 2;
		uVar10 = 3;
		cVar6 = 16;
	}
	else 
	{
		iVar11 = 2;
		iVar7 = 3;
		cVar6 = 16;
		uVar10 = main_cop_light_pos + CAR_INDEX(cp) & 7;
	}

	do {
		sVar2 = sVar5;
		iVar11--;

		if (iVar11 == -1)
			return;

		iVar3 = iVar7;

		while (iVar3--, sVar5 = -sVar2, iVar3 != -1) 
		{
			v1.vx = sVar1;

			if (GameLevel != 1 && GameLevel != 3) 
				v1.vx = sVar1 + (xpos1[uVar10] + (car_cos->policeLight).vx) * sVar2;

			col.g = 90;
			v1.vy = car_cos->policeLight.vy + car_cos->cog.vy;

			if (gNight != 0)
				col.g = 50;

			if (pauseflag == 0 && (CameraCnt & 1U) != 0 && GameLevel == 2) 
				uVar10++;

			uVar10 = uVar10 & 7;
			v1.vz = (car_cos->policeLight).vz + (car_cos->cog).vz;

			uVar4 = *coplife;

			// [A] too entangled...
			if (GameLevel == 1)
			{
			LAB_00030434:
				col.b = 255;
				col.r = col.g;
			}
			else 
			{
				if (1 < GameLevel) 
				{
					if (GameLevel != 3) 
						goto LAB_0003041c;
					goto LAB_00030434;
				}

				if (GameLevel != 0)
				{
				LAB_0003041c:
					if (iVar11 == 0) 
						goto LAB_00030434;
				}

				col.r = 255;
				col.b = col.g;
			}

			if (pauseflag == 0) 
				cp->ap.coplife += cVar6;

			ShowCarlight(&v1, cp, &col, uVar4 >> 1, &light_texture, 0xff);

			if (pauseflag == 0 && (CameraCnt & 1U) != 0 && GameLevel == 2) 
				uVar10++;

			uVar10 = uVar10 & 7;
		}

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

// [D]
void AddNightLights(_CAR_DATA *cp)
{
	short sVar1;
	short sVar2;
	ushort uVar3;
	short sVar4;
	char cVar5;
	ushort uVar6;
	uint uVar8;
	uint uVar9;
	int iVar10;
	char cVar11;
	int iVar12;
	short *psVar13;
	CAR_COSMETICS *pCVar14;
	SVECTOR Position1;
	SVECTOR Position2;
	SVECTOR vec;
	CVECTOR col;
	int lit;
	char *life2;
	short loop;
	short doubleFlag;
	short verticalFlag;
	short cogOffset;
	short *local_2c;

	life2 = &cp->ap.life2;

	lit = 0;
	loop = 0;
	LeftLight = 0;
	RightLight = 0;

	pCVar14 = cp->ap.carCos;
	uVar3 = pCVar14->extraInfo;
	psVar13 = cp->ap.damage;

	sVar1 = pCVar14->cog.vx;
	gcar_num = CAR_INDEX(cp);

	vec.vx = pCVar14->headLight.vx + pCVar14->cog.vx;
	vec.vy = pCVar14->headLight.vy + pCVar14->cog.vy;
	vec.vz = pCVar14->headLight.vz + pCVar14->cog.vz;
	iVar10 = (((uint)(ushort)pCVar14->extraInfo & 0xc00) >> 8) + 10;
	//vec.vz = vec.vz + pCVar14->cog.vz;

	do {
		cVar11 = 0;
		uVar8 = 8 << (loop & 0x1f);
		sVar4 = (short)iVar10;
		iVar10 = lit;

		if ((uVar3 & 0x8000) == 0) 
		{
			Position1.vx = vec.vx;
			Position1.vy = vec.vy;
			sVar2 = *psVar13 >> 6;
			Position1.vz = (vec.vz + sVar2);
			Position2.vz = (vec.vz + sVar2);

			if (*psVar13 < 1000) 
			{
				cVar11 = 1;

				col.r = -1;
				col.b = -1;
				col.g = -1;

				ShowCarlight(&Position1, cp, &col, 20, &light_texture, uVar8 & 0xff | 1);
				iVar10 = lit + 1;
			}
		}
		else if ((uVar3 & 0x2000) == 0)
		{
			sVar2 = *psVar13 >> 6;
			Position1.vz = vec.vz + sVar2;
			Position2.vz = vec.vz + sVar2;

			Position1.vx = sVar4 + vec.vx;
			Position1.vy = vec.vy;

			Position2.vx = vec.vx - sVar4;
			Position2.vy = vec.vy;

			if (*psVar13 < 1000) 
			{
				col.r = -1;
				col.b = -1;
				col.g = -1;
				ShowCarlight(&Position1, cp, &col, 0x14, &light_texture, uVar8 & 0xff | 1);
				sVar2 = cp->ap.damage[0];
				goto joined_r0x00030874;
			}
		}
		else 
		{
			sVar2 = *psVar13 >> 6;
			Position1.vz = vec.vz + sVar2;
			Position2.vz = vec.vz + sVar2;
			Position1.vy = sVar4 + vec.vy;
			Position2.vy = vec.vy - sVar4;

			if (*psVar13 < 1000)
			{
				col.r = -1;
				col.b = -1;
				col.g = -1;
				ShowCarlight(&Position1, cp, &col, 20, &light_texture, uVar8 & 0xff | 1);
				sVar2 = *psVar13;
			joined_r0x00030874:
				cVar11 = 1;
				iVar10 = lit + 1;

				if (sVar2 < 500) 
				{
					lit = lit + 2;
					cVar11 = 2;
					col.r = -1;
					col.b = -1;
					col.g = -1;
					ShowCarlight(&Position2, cp, &col, 20, &light_texture, 1);
					iVar10 = lit;
				}
			}
		}

		lit = iVar10;
		local_2c = cp->ap.damage;
		iVar10 = -sVar4;
		vec.vx = sVar1 * 2 - vec.vx;
		cVar5 = cVar11;

		if (loop == 0) 
		{
			cVar5 = RightLight;
			LeftLight = cVar11;
		}

		RightLight = cVar5;
		psVar13 = psVar13 + 1;
		loop = ((loop + 1) * 0x10000) >> 0x10;

		if (1 < loop)
		{
			col.r = 56;

			if (cp->controlType != 1)
				col.r = 255;

			col.b = 0;
			col.g = 0;

			uVar3 = pCVar14->extraInfo;

			vec.vx = pCVar14->brakeLight.vx + pCVar14->cog.vx;
			vec.vy = pCVar14->brakeLight.vy + pCVar14->cog.vy;
			vec.vz = pCVar14->brakeLight.vz + pCVar14->cog.vz;

			iVar10 = ((pCVar14->extraInfo & 0x300) >> 6) + 10;

			if ((pCVar14->extraInfo & 8U) != 0) 
			{
				loop = 0;

				do {
					uVar8 = 2 << (loop & 0x1f);
					iVar12 = ((4 - loop) * 0x10000) >> 0x10;
					sVar4 = iVar10;

					if ((uVar3 & 0x4000) == 0)
					{
						Position1 = vec;

						if (local_2c[iVar12] < 500)
						{
							ShowCarlight(&Position1, cp, &col, 17, &light_texture, uVar8 & 0xff);

							*life2 = *life2 + 16;
						}
					}
					else 
					{
						if ((uVar3 & 0x1000) == 0) 
						{
							sVar2 = local_2c[iVar12];
							Position1.vx = sVar4 + vec.vx;
							Position2.vx = vec.vx - sVar4;

							Position1.vy = vec.vy;
							Position2.vy = vec.vy;
						}
						else
						{
							sVar2 = local_2c[iVar12];
							Position1.vy = sVar4 + vec.vy;
							Position2.vy = vec.vy - sVar4;

							Position1.vx = vec.vx;
							Position2.vx = vec.vx;
						}

						Position2.vz = vec.vz + (sVar2 >> 6);
						Position1.vz = vec.vz + (sVar2 >> 6);

						if (sVar2 < 500)
						{
							ShowCarlight(&Position1, cp, &col, 17, &light_texture, uVar8 & 0xff);
							ShowCarlight(&Position2, cp, &col, 17, &light_texture, 0);

							*life2 = *life2 + 16;
						}
					}

					iVar10 = -sVar4;
					loop = ((loop + 1) * 0x10000) >> 0x10;
					vec.vx = sVar1 * 2 - vec.vx;
				} while (loop < 2);
			}
			if (lit != 0) 
			{
				col.r = (lit << 4);
				col.g = col.r;
				col.b = col.r;
				PlacePoolForCar(cp, &col, 1, 0);
			}

			col.r = *life2;
			if (col.r != 0) 
			{
				col.b = 0;
				col.g = 0;
				
				PlacePoolForCar(cp, &col, 0, 0);
				*life2 = 0;
			}

			if (cp->controlType == 1)
				gPlayerCarLights = lit;

			return;
		}
	} while (true);
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

// [D]
void AddSmokingEngine(_CAR_DATA *cp, int black_smoke, int WheelSpeed)
{
	CAR_COSMETICS *car_cos;
	VECTOR SmokePos;
	VECTOR Drift;
	SVECTOR svec;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

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

	if (cp->controlType == 2 && cp->ai.c.thrustState == 3 && (cp->ai.c.ctrlState == 5 || cp->ai.c.ctrlState == 7))
		return;

	// if (((newCar->controlType != 2 && newCar->controlType != 7) || newCar->ai.c.thrustState != 3) || (newCar->ai.c.ctrlState != 7 && newCar->ai.c.ctrlState != 5))

	if (WheelSpeed > 4096 * 64)
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

		Drift.vx -= FIXED(smokedir.vx) / 2;
		Drift.vz -= FIXED(smokedir.vz) / 2;

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

// [D]
void AddFlamingEngine(_CAR_DATA *cp)
{
	CAR_COSMETICS *car_cos;
	VECTOR SmokePos;
	SVECTOR svec;
	VECTOR Drift;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

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





