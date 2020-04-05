#include "THISDUST.H"
#include "COSMETIC.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "HANDLING.H"

#include <string.h>

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

char _cosmeticBuffer[0xc30];

// [D]
void LoadCosmetics(int level)
{
	LoadfileSeg(CosmeticFiles[level], _cosmeticBuffer, 0, 0xc30);
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

			/*
			// Again, a memcpy...
			plVar1 = local_a2_276 + 0x38;

			if (((uint)local_a2_276 & 3) == 0) {
				do {
					lVar2 = local_a2_276[1];
					local_t2_284 = local_a2_276[2];
					local_t3_288 = local_a2_276[3];
					*(long *)&pCVar3->headLight = *local_a2_276;
					*(long *)&(pCVar3->headLight).vz = lVar2;
					*(long *)&pCVar3->frontInd = local_t2_284;
					*(long *)&(pCVar3->frontInd).vz = local_t3_288;
					local_a2_276 = local_a2_276 + 4;
					pCVar3 = (CAR_COSMETICS *)&pCVar3->backInd;
				} while (local_a2_276 != plVar1);
			}
			else {
				do {
					local_t1_204 = local_a2_276[1];
					local_t2_212 = local_a2_276[2];
					local_t3_220 = local_a2_276[3];
					*(long *)&pCVar3->headLight = *local_a2_276;
					*(long *)&(pCVar3->headLight).vz = local_t1_204;
					*(long *)&pCVar3->frontInd = local_t2_212;
					*(long *)&(pCVar3->frontInd).vz = local_t3_220;
					local_a2_276 = local_a2_276 + 4;
					pCVar3 = (CAR_COSMETICS *)&pCVar3->backInd;
				} while (local_a2_276 != plVar1);
			}

			lVar2 = local_a2_276[1];
			local_t1_340 = local_a2_276[2];
			*(long *)&pCVar3->headLight = *local_a2_276;
			*(long *)&(pCVar3->headLight).vz = lVar2;
			*(long *)&pCVar3->frontInd = local_t1_340;
			*/

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

void AddReverseLight(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	uint uVar2;
	CAR_COSMETICS *pCVar3;
	undefined4 local_20;
	uint local_1c;
	CVECTOR local_18[2];

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	local_18[0].r = 'd';
	pCVar3 = (cp->ap).carCos;
	local_18[0].g = 'Z';
	local_18[0].b = 'Z';
	sVar1 = (pCVar3->cog).vx;
	uVar2 = *(uint *)&(pCVar3->revLight).vz;
	local_20._0_2_ = (short)*(undefined4 *)&pCVar3->revLight;
	local_20._2_2_ = (short)((uint)*(undefined4 *)&pCVar3->revLight >> 0x10);
	local_20._0_2_ = sVar1 + (short)local_20;
	local_20._2_2_ = local_20._2_2_ + (pCVar3->cog).vy;
	local_1c._0_2_ = (short)uVar2;
	local_1c = uVar2 & 0xffff0000 | (uint)(ushort)((short)local_1c + (pCVar3->cog).vz);
	if ((cp->ap).damage[4] < 500) {
		ShowCarlight((SVECTOR *)&local_20, cp, local_18, 0xe, &light_texture, 0);
	}
	if ((cp->ap).damage[3] < 500) {
		local_20 = CONCAT22(local_20._2_2_, sVar1 * 2 - (short)local_20);
		ShowCarlight((SVECTOR *)&local_20, cp, local_18, 0xe, &light_texture, 0);
	}
	return;*/
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

void SetupSpecCosmetics(char *loadbuffer)
{
	UNIMPLEMENTED();
	/*
	undefined4 uVar1;
	undefined4 *puVar2;
	CAR_COSMETICS *pCVar3;

	pCVar3 = car_cosmetics + 4;
	puVar2 = (undefined4 *)(loadbuffer + 0xec);
	if (loadbuffer < puVar2) {
		do {
			uVar1 = *(undefined4 *)loadbuffer;
			loadbuffer = (char *)((undefined4 *)loadbuffer + 1);
			*(undefined4 *)&pCVar3->headLight = uVar1;
			pCVar3 = (CAR_COSMETICS *)&(pCVar3->headLight).vz;
		} while (loadbuffer < puVar2);
	}
	return;*/
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

void AddIndicatorLight(_CAR_DATA *cp, int Type)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	short sVar2;
	uint uVar3;
	uint uVar4;
	uint uVar5;
	char *pcVar6;
	CAR_COSMETICS *pCVar7;
	uchar uVar8;
	char *pcVar9;
	CVECTOR local_38[2];
	uint local_30;
	uint local_2c;
	short local_28;
	short sStack38;
	uint local_24;

	pcVar6 = &(cp->ap).life;
	pcVar9 = &(cp->ap).life2;
	if ((cp->ap).life < '\0') {
		uVar3 = (0xff - (uint)(byte)(cp->ap).life) * 2;
	}
	else {
		uVar3 = (uint)(byte)(cp->ap).life << 1;
	}
	local_38[0].r = (uchar)uVar3;
	uVar3 = uVar3 & 0xff;
	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	bVar1 = cp->controlType;
	if (bVar1 == 2) {
		local_38[0].g = '\0';
		local_38[0].b = '\0';
		if (pauseflag == 0) {
			*pcVar6 = *pcVar6 + '\b';
		}
		pCVar7 = (cp->ap).carCos;
		sVar2 = (pCVar7->cog).vx;
		uVar4 = *(uint *)&(pCVar7->backInd).vz;
		uVar5 = *(uint *)&(pCVar7->frontInd).vz;
		local_28 = (short)*(undefined4 *)&pCVar7->backInd;
		sStack38 = (short)((uint)*(undefined4 *)&pCVar7->backInd >> 0x10);
		local_28 = sVar2 + local_28;
		local_24._0_2_ = (short)uVar4;
		sStack38 = sStack38 + (pCVar7->cog).vy;
		local_30._0_2_ = (short)*(undefined4 *)&pCVar7->frontInd;
		local_24 = uVar4 & 0xffff0000 | (uint)(ushort)((short)local_24 + (pCVar7->cog).vz);
		local_2c._0_2_ = (short)uVar5;
		local_30 = CONCAT22((short)((uint)*(undefined4 *)&pCVar7->frontInd >> 0x10) + (pCVar7->cog).vy,
			sVar2 + (short)local_30);
		local_2c = uVar5 & 0xffff0000 | (uint)(ushort)((short)local_2c + (pCVar7->cog).vz);
		uVar8 = (uchar)uVar3;
		if ((Type == 0) || (Type == (uint)bVar1)) {
			if ((cp->ap).damage[4] < 500) {
				*pcVar9 = *pcVar9 + (char)(uVar3 >> 3);
				ShowCarlight((SVECTOR *)&local_28, cp, local_38, 0x14, &light_texture, 0);
			}
			if ((cp->ap).damage[0] < 500) {
				local_38[0].r = uVar8;
				ShowCarlight((SVECTOR *)&local_30, cp, local_38, 0x14, &light_texture, 1);
			}
		}
		if (Type - 1U < 2) {
			if ((cp->ap).damage[3] < 500) {
				local_28 = sVar2 * 2 - local_28;
				*pcVar9 = *pcVar9 + (char)(uVar3 >> 3);
				local_38[0].r = uVar8;
				ShowCarlight((SVECTOR *)&local_28, cp, local_38, 0x14, &light_texture, 0);
			}
			if ((cp->ap).damage[1] < 500) {
				local_30 = local_30 & 0xffff0000 | (uint)(ushort)(sVar2 * 2 - (short)local_30);
				local_38[0].r = uVar8;
				ShowCarlight((SVECTOR *)&local_30, cp, local_38, 0x14, &light_texture, 1);
			}
		}
	}
	return;*/
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
	UNIMPLEMENTED();
	/*
	short sVar1;
	ushort uVar2;
	short sVar3;
	int iVar4;
	uint uVar5;
	SVECTOR *v1;
	CAR_COSMETICS *pCVar6;
	int iVar7;
	char *pcVar8;
	short *psVar9;
	int iVar10;
	short local_58;
	short sStack86;
	uint local_54;
	undefined4 local_50;
	uint local_4c;
	short local_48;
	short sStack70;
	uint local_44;
	CVECTOR local_40[2];
	int local_38;
	int local_34;
	int local_30;

	pCVar6 = (cp->ap).carCos;
	local_40[0].r = -0x38;
	local_40[0].g = '\0';
	local_40[0].b = '\0';
	uVar2 = pCVar6->extraInfo;
	sVar1 = (pCVar6->cog).vx;
	pcVar8 = &(cp->ap).life2;
	if ((uVar2 & 8) != 0) {
		uVar5 = *(uint *)&(pCVar6->brakeLight).vz;
		local_48 = (short)*(undefined4 *)&pCVar6->brakeLight;
		sStack70 = (short)((uint)*(undefined4 *)&pCVar6->brakeLight >> 0x10);
		local_48 = sVar1 + local_48;
		sStack70 = sStack70 + (pCVar6->cog).vy;
		local_44._0_2_ = (short)uVar5;
		iVar7 = (((uint)(ushort)pCVar6->extraInfo & 0x300) >> 6) + 10;
		local_38 = (int)(short)(uVar2 & 0x4000);
		local_44 = uVar5 & 0xffff0000 | (uint)(ushort)((short)local_44 + (pCVar6->cog).vz);
		local_34 = (int)(short)(uVar2 & 0x1000);
		if ((pCVar6->extraInfo & 8U) != 0) {
			iVar10 = 0;
			psVar9 = (cp->ap).damage;
			local_30 = (int)sVar1 << 1;
			do {
				iVar4 = (4 - iVar10) * 0x10000 >> 0x10;
				sVar1 = (short)iVar7;
				if (local_38 == 0) {
					local_58 = local_48;
					sStack86 = sStack70;
					local_54 = local_44;
					v1 = (SVECTOR *)&local_58;
					if (psVar9[iVar4] < 500) goto LAB_000300c8;
				}
				else {
					local_54._0_2_ = (short)local_44;
					v1 = (SVECTOR *)&local_50;
					if (local_34 == 0) {
						sVar3 = psVar9[iVar4] >> 6;
						local_54 = local_44 & 0xffff0000 | (uint)(ushort)((short)local_54 + sVar3);
						local_4c = local_44 & 0xffff0000 | (uint)(ushort)((short)local_54 + sVar3);
						local_58 = sVar1 + local_48;
						sStack86 = sStack70;
						local_50 = CONCAT22(sStack70, local_48 - sVar1);
						if (psVar9[iVar4] < 500) {
							ShowCarlight((SVECTOR *)&local_58, cp, local_40, 0x11, &light_texture, 0);
							goto LAB_000300c8;
						}
					}
					else {
						sVar3 = psVar9[iVar4] >> 6;
						local_54 = local_44 & 0xffff0000 | (uint)(ushort)((short)local_54 + sVar3);
						local_4c = local_44 & 0xffff0000 | (uint)(ushort)((short)local_54 + sVar3);
						sStack86 = sVar1 + sStack70;
						local_58 = local_48;
						local_50 = CONCAT22(sStack70 - sVar1, local_48);
						if (psVar9[iVar4] < 500) {
							ShowCarlight((SVECTOR *)&local_58, cp, local_40, 0x11, &light_texture, 0);
						LAB_000300c8:
							ShowCarlight(v1, cp, local_40, 0x11, &light_texture, 0);
							*pcVar8 = *pcVar8 + '\b';
						}
					}
				}
				iVar7 = (int)-sVar1;
				iVar10 = (iVar10 + 1) * 0x10000 >> 0x10;
				local_48 = (short)local_30 - local_48;
			} while (iVar10 < 2);
		}
	}
	return;*/
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

void AddCopCarLight(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	uint uVar2;
	CAR_COSMETICS *pCVar3;
	int iVar4;
	byte *pbVar5;
	uint uVar6;
	int iVar7;
	SVECTOR local_58;
	CVECTOR local_50[2];
	int local_48;
	int local_44;
	_CAR_DATA *local_40;
	int local_3c;
	int local_38;
	undefined **local_34;
	undefined4 local_30;
	int local_2c;

	local_3c = 1;
	pbVar5 = (byte *)&(cp->ap).coplife;
	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	if ((CameraCar == (int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2) && (cameraview == 2)) {
		return;
	}
	if (FastForward != 0) {
		return;
	}
	if ((cp->hd).where.m[4] < 100) {
		return;
	}
	pCVar3 = (cp->ap).carCos;
	sVar1 = (pCVar3->cog).vx;
	if (GameLevel == 1) {
	LAB_00030268:
		iVar7 = 1;
		local_2c = 2;
		uVar6 = 3;
		local_30 = 0x30;
	}
	else {
		if (GameLevel < 2) {
			if (GameLevel == 0) {
				iVar7 = 2;
				local_2c = 2;
				uVar6 = 3;
				local_30 = 0x10;
				goto LAB_000302c4;
			}
		}
		else {
			if (GameLevel == 3) goto LAB_00030268;
		}
		iVar7 = 2;
		local_2c = 3;
		local_30 = 0x10;
		uVar6 = main_cop_light_pos + ((int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2) & 7;
	}
LAB_000302c4:
	if (iVar7 + -1 != -1) {
		local_38 = 2;
		local_40 = cp;
		iVar7 = iVar7 + -1;
		do {
			iVar4 = local_2c + -1;
			local_44 = iVar7 + -1;
			local_48 = -local_3c;
			if (iVar4 != -1) {
				local_34 = &PTR_DAT_0009c004;
				do {
					local_58.vx = sVar1;
					if ((GameLevel != 1) && (GameLevel != 3)) {
						local_58.vx = sVar1 + ((ushort)*(byte *)(uVar6 + (int)local_34) +
							(pCVar3->policeLight).vx) * (short)local_3c;
					}
					local_50[0].g = 'Z';
					local_58.vy = (pCVar3->policeLight).vy + (pCVar3->cog).vy;
					if (gNight != 0) {
						local_50[0].g = '2';
					}
					if (((pauseflag == 0) && ((CameraCnt & 1U) != 0)) && (GameLevel == local_38)) {
						uVar6 = uVar6 + 1;
					}
					uVar6 = uVar6 & 7;
					local_58.vz = (pCVar3->policeLight).vz + (pCVar3->cog).vz;
					if ((char)*pbVar5 < '\0') {
						uVar2 = 0xff - (uint)*pbVar5;
					}
					else {
						uVar2 = (uint)*pbVar5;
					}
					if (GameLevel == 1) {
					LAB_00030434:
						local_50[0].b = -1;
						local_50[0].r = local_50[0].g;
					}
					else {
						if (1 < GameLevel) {
							if (GameLevel != 3) goto LAB_0003041c;
							goto LAB_00030434;
						}
						if (GameLevel != 0) {
						LAB_0003041c:
							if (iVar7 == 0) goto LAB_00030434;
						}
						local_50[0].r = -1;
						local_50[0].b = local_50[0].g;
					}
					if (pauseflag == 0) {
						*pbVar5 = *pbVar5 + (char)local_30;
					}
					ShowCarlight(&local_58, local_40, local_50, (short)((int)uVar2 >> 1), &light_texture, 0xff);
					if (((pauseflag == 0) && ((CameraCnt & 1U) != 0)) && (GameLevel == local_38)) {
						uVar6 = uVar6 + 1;
					}
					iVar4 = iVar4 + -1;
					uVar6 = uVar6 & 7;
				} while (iVar4 != -1);
			}
			local_3c = local_48;
			iVar7 = local_44;
		} while (local_44 != -1);
	}
	return;
	*/
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

void AddNightLights(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	short sVar3;
	char cVar4;
	uint uVar5;
	int iVar6;
	char cVar7;
	int iVar8;
	short *psVar9;
	CAR_COSMETICS *pCVar10;
	undefined4 local_68;
	uint local_64;
	uint local_60;
	uint local_5c;
	uint local_58;
	uint local_54;
	CVECTOR local_50[2];
	int local_48;
	uchar *local_44;
	uint local_40;
	int local_3c;
	int local_38;
	int local_34;
	SVECTOR *local_30;
	short *local_2c;

	local_44 = (uchar *)&(cp->ap).life2;
	local_30 = (SVECTOR *)&local_68;
	local_48 = 0;
	local_40 = 0;
	LeftLight = '\0';
	RightLight = '\0';
	pCVar10 = (cp->ap).carCos;
	psVar9 = (cp->ap).damage;
	local_3c = (int)(short)(pCVar10->extraInfo & 0x8000);
	sVar1 = (pCVar10->cog).vx;
	local_34 = (int)sVar1;
	local_38 = (int)(short)(pCVar10->extraInfo & 0x2000);
	gcar_num = (int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2;
	uVar5 = *(uint *)&(pCVar10->headLight).vz;
	local_58._0_2_ = (short)*(undefined4 *)&pCVar10->headLight;
	local_58 = CONCAT22((short)((uint)*(undefined4 *)&pCVar10->headLight >> 0x10) + (pCVar10->cog).vy,
		sVar1 + (short)local_58);
	local_54._0_2_ = (short)uVar5;
	iVar6 = (((uint)(ushort)pCVar10->extraInfo & 0xc00) >> 8) + 10;
	local_54 = uVar5 & 0xffff0000 | (uint)(ushort)((short)local_54 + (pCVar10->cog).vz);
	do {
		cVar7 = '\0';
		uVar5 = 8 << (local_40 & 0x1f);
		sVar1 = (short)iVar6;
		local_64._0_2_ = (short)local_54;
		if (local_3c == 0) {
			local_2c = (cp->ap).damage;
			local_68 = local_58;
			sVar2 = *psVar9 >> 6;
			local_64 = local_54 & 0xffff0000 | (uint)(ushort)((short)local_64 + sVar2);
			local_5c = local_5c & 0xffff0000 | (uint)(ushort)((short)local_5c + sVar2);
			if (*psVar9 < 1000) {
				cVar7 = '\x01';
				local_50[0].r = -1;
				local_50[0].b = -1;
				local_50[0].g = -1;
				local_48 = local_48 + 1;
				ShowCarlight(local_30, cp, local_50, 0x14, &light_texture, uVar5 & 0xff | 1);
			}
		}
		else {
			local_2c = (cp->ap).damage;
			local_68._2_2_ = (short)(local_58 >> 0x10);
			if (local_38 == 0) {
				local_2c = (cp->ap).damage;
				sVar2 = *psVar9 >> 6;
				local_64 = local_54 & 0xffff0000 | (uint)(ushort)((short)local_64 + sVar2);
				local_68._0_2_ = (short)local_58;
				local_5c = local_54 & 0xffff0000 | (uint)(ushort)((short)local_64 + sVar2);
				local_68 = local_58 & 0xffff0000 | (uint)(ushort)(sVar1 + (short)local_68);
				local_60 = local_58 & 0xffff0000 | (uint)(ushort)((short)local_68 - sVar1);
				if (*psVar9 < 1000) {
					local_50[0].r = -1;
					local_50[0].b = -1;
					local_50[0].g = -1;
					ShowCarlight(local_30, cp, local_50, 0x14, &light_texture, uVar5 & 0xff | 1);
					sVar2 = (cp->ap).damage[0];
					iVar6 = local_48;
					goto joined_r0x00030874;
				}
			}
			else {
				sVar2 = *psVar9 >> 6;
				local_64 = local_54 & 0xffff0000 | (uint)(ushort)((short)local_64 + sVar2);
				local_5c = local_54 & 0xffff0000 | (uint)(ushort)((short)local_64 + sVar2);
				local_68 = local_58 & 0xffff | (uint)(ushort)(sVar1 + local_68._2_2_) << 0x10;
				local_60 = local_58 & 0xffff | (uint)(ushort)(local_68._2_2_ - sVar1) << 0x10;
				if (*psVar9 < 1000) {
					local_50[0].r = -1;
					local_50[0].b = -1;
					local_50[0].g = -1;
					ShowCarlight(local_30, cp, local_50, 0x14, &light_texture, uVar5 & 0xff | 1);
					sVar2 = *psVar9;
					iVar6 = local_48;
				joined_r0x00030874:
					cVar7 = '\x01';
					local_48 = iVar6 + 1;
					if (sVar2 < 500) {
						local_48 = iVar6 + 2;
						cVar7 = '\x02';
						local_50[0].r = -1;
						local_50[0].b = -1;
						local_50[0].g = -1;
						ShowCarlight((SVECTOR *)&local_60, cp, local_50, 0x14, &light_texture, 1);
					}
				}
			}
		}
		iVar6 = (int)-sVar1;
		sVar1 = (short)local_34 * 2;
		local_58 = local_58 & 0xffff0000 | (uint)(ushort)(sVar1 - (short)local_58);
		cVar4 = cVar7;
		if (local_40 == 0) {
			cVar4 = RightLight;
			LeftLight = cVar7;
		}
		RightLight = cVar4;
		psVar9 = psVar9 + 1;
		local_40 = (int)((local_40 + 1) * 0x10000) >> 0x10;
		if (1 < (int)local_40) {
			local_50[0].r = -0x38;
			if (cp->controlType != '\x01') {
				local_50[0].r = -1;
			}
			local_50[0].b = '\0';
			local_50[0].g = '\0';
			uVar5 = *(uint *)&(pCVar10->brakeLight).vz;
			local_58._0_2_ = (short)*(undefined4 *)&pCVar10->brakeLight;
			local_3c = (int)(short)(pCVar10->extraInfo & 0x4000);
			local_38 = (int)(short)(pCVar10->extraInfo & 0x1000);
			local_58 = CONCAT22((short)((uint)*(undefined4 *)&pCVar10->brakeLight >> 0x10) +
				(pCVar10->cog).vy, (short)local_34 + (short)local_58);
			local_54._0_2_ = (short)uVar5;
			local_54 = uVar5 & 0xffff0000 | (uint)(ushort)((short)local_54 + (pCVar10->cog).vz);
			iVar6 = (((uint)(ushort)pCVar10->extraInfo & 0x300) >> 6) + 10;
			if ((pCVar10->extraInfo & 8U) != 0) {
				local_40 = 0;
				do {
					uVar5 = 2 << (local_40 & 0x1f);
					iVar8 = (int)((4 - local_40) * 0x10000) >> 0x10;
					sVar2 = (short)iVar6;
					if (local_3c == 0) {
						local_68 = local_58;
						local_64 = local_54;
						if (local_2c[iVar8] < 500) {
							ShowCarlight(local_30, cp, local_50, 0x11, &light_texture, uVar5 & 0xff);
							*local_44 = *local_44 + '\x10';
						}
					}
					else {
						local_5c._0_2_ = (short)local_54;
						local_68._2_2_ = (short)(local_58 >> 0x10);
						if (local_38 == 0) {
							sVar3 = local_2c[iVar8];
							local_64 = local_54 & 0xffff0000 | (uint)(ushort)((short)local_5c + (sVar3 >> 6));
							local_68._0_2_ = (short)local_58;
							local_5c = local_54 & 0xffff0000 | (uint)(ushort)((short)local_5c + (sVar3 >> 6));
							local_68 = local_58 & 0xffff0000 | (uint)(ushort)(sVar2 + (short)local_68);
							local_60 = local_58 & 0xffff0000 | (uint)(ushort)((short)local_68 - sVar2);
						}
						else {
							sVar3 = local_2c[iVar8];
							local_64 = local_54 & 0xffff0000 | (uint)(ushort)((short)local_5c + (sVar3 >> 6));
							local_5c = local_54 & 0xffff0000 | (uint)(ushort)((short)local_5c + (sVar3 >> 6));
							local_68 = local_58 & 0xffff | (uint)(ushort)(sVar2 + local_68._2_2_) << 0x10;
							local_60 = local_58 & 0xffff | (uint)(ushort)(local_68._2_2_ - sVar2) << 0x10;
						}
						if (sVar3 < 500) {
							ShowCarlight(local_30, cp, local_50, 0x11, &light_texture, uVar5 & 0xff);
							ShowCarlight((SVECTOR *)&local_60, cp, local_50, 0x11, &light_texture, 0);
							*local_44 = *local_44 + '\x10';
						}
					}
					iVar6 = (int)-sVar2;
					local_40 = (int)((local_40 + 1) * 0x10000) >> 0x10;
					local_58 = local_58 & 0xffff0000 | (uint)(ushort)(sVar1 - (short)local_58);
				} while ((int)local_40 < 2);
			}
			if (local_48 != 0) {
				local_50[0].r = (uchar)(local_48 << 4);
				local_50[0].g = local_50[0].r;
				local_50[0].b = local_50[0].r;
				PlacePoolForCar(cp, local_50, 1);
			}
			local_50[0].r = *local_44;
			if (local_50[0].r != '\0') {
				local_50[0].b = '\0';
				local_50[0].g = '\0';
				PlacePoolForCar(cp, local_50, 0);
				*local_44 = '\0';
			}
			if (cp->controlType == '\x01') {
				gPlayerCarLights = local_48;
			}
			return;
		}
	} while (true);
	*/
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

void AddSmokingEngine(_CAR_DATA *cp, int black_smoke, int WheelSpeed)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	uint uVar2;
	CAR_COSMETICS *pCVar3;
	VECTOR local_40;
	VECTOR VStack48;
	undefined4 local_20;
	uint local_1c;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	if ((((CameraCnt & 3U) == ((int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2 & 3U)) &&
		(gDoSmoke != 0)) && (pauseflag == 0)) {
		pCVar3 = (cp->ap).carCos;
		uVar2 = *(uint *)&(pCVar3->smoke).vz;
		local_20._0_2_ = (short)*(undefined4 *)&pCVar3->smoke;
		local_20._0_2_ = (short)local_20 + (pCVar3->cog).vx;
		local_20._2_2_ = (short)((uint)*(undefined4 *)&pCVar3->smoke >> 0x10);
		local_20._2_2_ = local_20._2_2_ + (pCVar3->cog).vy;
		local_1c._0_2_ = (short)uVar2;
		local_1c = uVar2 & 0xffff0000 | (uint)(ushort)((short)local_1c + (pCVar3->cog).vz);
		iVar1 = rand();
		local_40.vx = (cp->hd).where.t[0];
		local_20 = CONCAT22(local_20._2_2_, ((ushort)iVar1 & 0x7f) - 0x40);
		local_40.vz = (cp->hd).where.t[2];
		local_40.vy = -(cp->hd).where.t[1];
		if (black_smoke != 0) {
			local_40.vy = local_40.vy + -0x32;
		}
		setCopControlWord(2, 0, *(undefined4 *)(cp->hd).drawCarMat.m);
		setCopControlWord(2, 0x800, *(undefined4 *)((cp->hd).drawCarMat.m + 2));
		setCopControlWord(2, 0x1000, *(undefined4 *)((cp->hd).drawCarMat.m + 4));
		setCopControlWord(2, 0x1800, *(undefined4 *)((cp->hd).drawCarMat.m + 6));
		setCopControlWord(2, 0x2000, *(undefined4 *)((cp->hd).drawCarMat.m + 8));
		InitFXPos(&local_40, (SVECTOR *)&local_20, cp);
		GetSmokeDrift(&VStack48);
		if (black_smoke == 0) {
			Setup_Smoke(&local_40, 100, 400, 2, WheelSpeed, &VStack48, 0);
		}
		else {
			Setup_Smoke(&local_40, 100, 500, 1, WheelSpeed, &VStack48, 0);
		}
	}
	return;*/
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

void AddFlamingEngine(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	uint uVar2;
	CAR_COSMETICS *pCVar3;
	VECTOR local_38;
	undefined4 local_28;
	uint local_24;
	VECTOR local_20;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	if ((((CameraCnt & 1U) == ((int)(cp[-0x503].ap.old_clock + 2) * -0x24ca58e9 >> 2 & 1U)) &&
		(pCVar3 = (cp->ap).carCos, gDoSmoke != 0)) && (pauseflag == 0)) {
		uVar2 = *(uint *)&(pCVar3->fire).vz;
		local_28._0_2_ = (short)*(undefined4 *)&pCVar3->fire;
		local_28._0_2_ = (short)local_28 + (pCVar3->cog).vx;
		local_28._2_2_ = (short)((uint)*(undefined4 *)&pCVar3->fire >> 0x10);
		local_28._2_2_ = local_28._2_2_ + (pCVar3->cog).vy;
		local_24._0_2_ = (short)uVar2;
		local_24 = uVar2 & 0xffff0000 | (uint)(ushort)((short)local_24 + (pCVar3->cog).vz);
		iVar1 = rand();
		local_28 = CONCAT22(local_28._2_2_, (short)local_28 + ((ushort)iVar1 & 0x3f));
		iVar1 = rand();
		local_38.vx = (cp->hd).where.t[0];
		local_24 = local_24 & 0xffff0000 | (uint)(ushort)((short)local_24 + ((ushort)iVar1 & 0x3f));
		local_38.vz = (cp->hd).where.t[2];
		local_38.vy = -(cp->hd).where.t[1];
		SetRotMatrix(&(cp->hd).drawCarMat);
		InitFXPos(&local_38, (SVECTOR *)&local_28, cp);
		local_20.vx = 0;
		local_20.vy = 0;
		local_20.vz = 0;
		Setup_Smoke(&local_38, 0x32, 100, 4, 0, &local_20, 0);
	}
	return;
	*/
}





