#include "THISDUST.H"
#include "DR2ROADS.H"

#include "SYSTEM.H"
#include "MAP.H"
#include "EVENT.H"
#include "CONVERT.H"

sdPlane sea = { 9, 0, 16384, 0, 2048 }; // a default surface if FindSurfaceD2 fails

ROAD_MAP_LUMP_DATA roadMapLumpData;

int NumTempJunctions = 0;
DRIVER2_JUNCTION *Driver2JunctionsPtr = NULL;
ulong *Driver2TempJunctionsPtr = NULL;

DRIVER2_CURVE *Driver2CurvesPtr = NULL;
int NumDriver2Curves = 0;

short* RoadMapDataRegions[4];

// decompiled code
// original method signature: 
// void /*$ra*/ ProcessStraightsDriver2Lump(char *lump_file /*$s0*/, int lump_size /*$a1*/)
 // line 64, offset 0x000136c0
	/* begin block 1 */
		// Start line: 65
		// Start offset: 0x000136C0
	/* end block 1 */
	// End offset: 0x000136F4
	// End Line: 69

	/* begin block 2 */
		// Start line: 659
	/* end block 2 */
	// End Line: 660

	/* begin block 3 */
		// Start line: 128
	/* end block 3 */
	// End Line: 129

void ProcessStraightsDriver2Lump(char *lump_file, int lump_size)
{
	UNIMPLEMENTED();
	/*
	Getlong((char *)&NumDriver2Straights, lump_file);
	Driver2StraightsPtr = (DRIVER2_STRAIGHT *)(lump_file + 4);
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessCurvesDriver2Lump(char *lump_file /*$s0*/, int lump_size /*$a1*/)
 // line 80, offset 0x000136f4
	/* begin block 1 */
		// Start line: 81
		// Start offset: 0x000136F4
	/* end block 1 */
	// End offset: 0x00013728
	// End Line: 85

	/* begin block 2 */
		// Start line: 681
	/* end block 2 */
	// End Line: 682

	/* begin block 3 */
		// Start line: 693
	/* end block 3 */
	// End Line: 694

// [D]
void ProcessCurvesDriver2Lump(char *lump_file, int lump_size)
{
	Getlong((char *)&NumDriver2Curves, lump_file);
	Driver2CurvesPtr = (DRIVER2_CURVE *)(lump_file + 4);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessJunctionsDriver2Lump(char *lump_file /*$s1*/, int lump_size /*$a1*/, int fix /*$s0*/)
 // line 94, offset 0x00013728
	/* begin block 1 */
		// Start line: 95
		// Start offset: 0x00013728

		/* begin block 1.1 */
			// Start line: 102
			// Start offset: 0x0001375C
			// Variables:
		// 		int loop; // $v1
		// 		struct OLD_DRIVER2_JUNCTION *old; // $a1
		// 		struct DRIVER2_JUNCTION *p; // $a0

			/* begin block 1.1.1 */
				// Start line: 107
				// Start offset: 0x00013778
				// Variables:
			// 		int i; // $a1
			/* end block 1.1.1 */
			// End offset: 0x000137A4
			// End Line: 113
		/* end block 1.1 */
		// End offset: 0x000137B8
		// End Line: 114
	/* end block 1 */
	// End offset: 0x000137CC
	// End Line: 115

	/* begin block 2 */
		// Start line: 713
	/* end block 2 */
	// End Line: 714

	/* begin block 3 */
		// Start line: 723
	/* end block 3 */
	// End Line: 724

void ProcessJunctionsDriver2Lump(char *lump_file, int lump_size, int fix)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	short *psVar3;
	DRIVER2_JUNCTION *pDVar4;
	DRIVER2_JUNCTION *pDVar5;
	int iVar6;
	DRIVER2_JUNCTION *pDVar7;

	Getlong((char *)&NumDriver2Junctions, lump_file);
	iVar1 = NumDriver2Junctions;
	pDVar4 = (DRIVER2_JUNCTION *)(lump_file + 4);
	Driver2JunctionsPtr = pDVar4;
	if ((fix != 0) && (iVar2 = 0, pDVar5 = pDVar4, 0 < NumDriver2Junctions)) {
		do {
			iVar2 = iVar2 + 1;
			pDVar7 = pDVar4 + 1;
			psVar3 = pDVar5[1].ExitIdx;
			iVar6 = 3;
			do {
				psVar3 = psVar3 + 1;
				iVar6 = iVar6 + -1;
				pDVar4->ExitIdx[0] = *psVar3;
				pDVar4 = (DRIVER2_JUNCTION *)(pDVar4->ExitIdx + 1);
			} while (-1 < iVar6);
			pDVar4 = pDVar7;
			pDVar5 = pDVar5 + 2;
		} while (iVar2 < iVar1);
	}
	return;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ MapHeight(struct VECTOR *pos /*$s0*/)
 // line 146, offset 0x000137cc
	/* begin block 1 */
		// Start line: 147
		// Start offset: 0x000137CC
		// Variables:
	// 		int height; // $v0
	// 		struct _sdPlane *plane; // $v0
	/* end block 1 */
	// End offset: 0x0001380C
	// End Line: 162

	/* begin block 2 */
		// Start line: 808
	/* end block 2 */
	// End Line: 809

	/* begin block 3 */
		// Start line: 840
	/* end block 3 */
	// End Line: 841

// [D]
int MapHeight(VECTOR *pos)
{
	_sdPlane *plane;

	plane = sdGetCell(pos);

	if (plane)
		return sdHeightOnPlane(pos, plane);

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ FindSurfaceD2(struct VECTOR *pos /*$s0*/, struct VECTOR *normal /*$s1*/, struct VECTOR *out /*$s3*/, struct _sdPlane **plane /*$s2*/)
 // line 164, offset 0x00012ef4
	/* begin block 1 */
		// Start line: 328
	/* end block 1 */
	// End Line: 329

int FindSurfaceD2(VECTOR *pos, VECTOR *normal, VECTOR *out, _sdPlane **plane)
{
	UNIMPLEMENTED();
	return 0;
	/*
	_sdPlane *p_Var1;
	int iVar2;

	p_Var1 = sdGetCell(pos);
	*plane = p_Var1;
	out->vx = pos->vx;
	out->vz = pos->vz;
	iVar2 = sdHeightOnPlane(pos, *plane);
	out->vy = iVar2;
	p_Var1 = *plane;
	if ((p_Var1 == (_sdPlane *)0x0) || (p_Var1->b == 0)) {
		normal->vx = 0;
		normal->vy = 0x1000;
		normal->vz = 0;
	}
	else {
		normal->vx = (int)((uint)(ushort)p_Var1->a << 0x10) >> 0x12;
		normal->vy = (int)((uint)(ushort)(*plane)->b << 0x10) >> 0x12;
		normal->vz = (int)((uint)(ushort)(*plane)->c << 0x10) >> 0x12;
	}
	if (*plane == (_sdPlane *)0x0) {
		iVar2 = 0x1000;
	}
	else {
		iVar2 = 0x1000;
		if ((*plane)->surface == 4) {
			if (((gInGameCutsceneActive == 0) || (gCurrentMissionNumber != 0x17)) ||
				(gInGameCutsceneID != 0)) {
				iVar2 = out->vy + ((((int)((uint)*(ushort *)
					((int)rcossin_tbl + ((pos->vx + pos->vz) * 8 & 0x3ff8U))
					<< 0x10) >> 0x18) / 3) * 0x10000 >> 0x10);
			}
			else {
				iVar2 = out->vy + ((int)((uint)*(ushort *)
					((int)rcossin_tbl + ((pos->vx + pos->vz) * 8 & 0x3ff8U)) <<
					0x10) >> 0x19);
			}
			out->vy = iVar2;
			iVar2 = 0x800;
		}
	}
	return iVar2;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ sdHeightOnPlane(struct VECTOR *pos /*$t0*/, struct _sdPlane *plane /*$a1*/)
 // line 205, offset 0x000130d4
	/* begin block 1 */
		// Start line: 206
		// Start offset: 0x000130D4

		/* begin block 1.1 */
			// Start line: 216
			// Start offset: 0x00013134
			// Variables:
		// 		int angle; // $v0
		// 		int i; // $v0
		// 		struct DRIVER2_CURVE *curve; // $s0
		/* end block 1.1 */
		// End offset: 0x0001319C
		// End Line: 228

		/* begin block 1.2 */
			// Start line: 231
			// Start offset: 0x0001319C
			// Variables:
		// 		int val; // $a3

			/* begin block 1.2.1 */
				// Start line: 240
				// Start offset: 0x000131BC
				// Variables:
			// 		int lx; // $v0
			// 		int ly; // $v1
			/* end block 1.2.1 */
			// End offset: 0x00013218
			// End Line: 244
		/* end block 1.2 */
		// End offset: 0x0001322C
		// End Line: 247
	/* end block 1 */
	// End offset: 0x0001322C
	// End Line: 248

	/* begin block 2 */
		// Start line: 410
	/* end block 2 */
	// End Line: 411

// [D]
int sdHeightOnPlane(VECTOR *pos, _sdPlane *plane)
{
	long lVar1;
	uint uVar2;
	DRIVER2_CURVE *pDVar3;
	int iVar4;

	if (plane != NULL) 
	{
		uVar2 = plane->d;

		if ((((int)uVar2 >> 1 ^ uVar2) & 0x40000000) != 0) {
			return uVar2 ^ 0x40000000;
		}

		if (((plane->surface & 0xe000U) == 0x4000) && (plane->b == 0)) 
		{
			pDVar3 = Driver2CurvesPtr + (((uint)(ushort)plane->surface & 0x1fff) - 0x20);
			lVar1 = ratan2(pDVar3->Midz - pos->vz, pDVar3->Midx - pos->vx);
			iVar4 = (int)pDVar3->gradient * (lVar1 + 0x800U & 0xfff);
			if (iVar4 < 0) {
				iVar4 = iVar4 + 0xfff;
			}
			return (iVar4 >> 0xc) - (int)pDVar3->height;
		}

		iVar4 = (int)plane->b;

		if (iVar4 != 0)
		{
			if (iVar4 == 0x4000) 
			{
				return -uVar2;
			}

			if (iVar4 == 0) 
			{
				trap(7);
			}

			return -uVar2 - (int)((int)plane->a * ((pos->vx - 0x200U & 0xffff) + 0x200) +
				(int)plane->c * ((pos->vz - 0x200U & 0xffff) + 0x200)) / iVar4;
		}
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetSurfaceIndex(struct VECTOR *pos /*$a0*/)
 // line 250, offset 0x0001380c
	/* begin block 1 */
		// Start line: 252
		// Start offset: 0x0001380C
		// Variables:
	// 		struct _sdPlane *plane; // $v0
	/* end block 1 */
	// End offset: 0x00013848
	// End Line: 260

	/* begin block 2 */
		// Start line: 959
	/* end block 2 */
	// End Line: 960

	/* begin block 3 */
		// Start line: 1048
	/* end block 3 */
	// End Line: 1049

	/* begin block 4 */
		// Start line: 1049
	/* end block 4 */
	// End Line: 1050

	/* begin block 5 */
		// Start line: 1051
	/* end block 5 */
	// End Line: 1052

// [D]
int GetSurfaceIndex(VECTOR *pos)
{
	_sdPlane *p_Var1;
	int iVar2;

	p_Var1 = sdGetCell(pos);
	if (p_Var1 == (_sdPlane *)0x0) {
		iVar2 = -0x20;
	}
	else {
		iVar2 = (int)p_Var1->surface + -0x20;
	}
	return iVar2;
}



// decompiled code
// original method signature: 
// struct _sdPlane * /*$ra*/ FindRoadInBSP(struct _sdNode *node /*$s0*/, struct _sdPlane *base /*$s1*/)
 // line 266, offset 0x000138f0
	/* begin block 1 */
		// Start line: 268
		// Start offset: 0x00013908
		// Variables:
	// 		struct _sdPlane *plane; // $v0
	/* end block 1 */
	// End offset: 0x00013980
	// End Line: 293

	/* begin block 2 */
		// Start line: 409
	/* end block 2 */
	// End Line: 410

	/* begin block 3 */
		// Start line: 1463
	/* end block 3 */
	// End Line: 1464

// [D]
_sdPlane * FindRoadInBSP(_sdNode *node, _sdPlane *base)
{
	_sdPlane *p_Var1;

	while (true) {
		if (-1 < node->angle) {
			base = base + node->angle;
			if (base->surface < 0x20) {
				base = (_sdPlane *)0x0;
			}
			return base;
		}
		p_Var1 = FindRoadInBSP((_sdNode *)&node->dist, base);
		if (p_Var1 != (_sdPlane *)0x0) break;
		node = (_sdNode *)(&node->angle + ((node->angle << 1) >> 0x18));
	}
	return p_Var1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ RoadInCell(struct VECTOR *pos /*$s5*/)
 // line 295, offset 0x0001322c
	/* begin block 1 */
		// Start line: 296
		// Start offset: 0x0001322C
		// Variables:
	// 		char *buffer; // $s2
	// 		struct XYPAIR cellPos; // stack offset -48
	// 		struct XYPAIR cell; // stack offset -40
	// 		short *surface; // $a0
	// 		struct _sdPlane *plane; // $s0

		/* begin block 1.1 */
			// Start line: 331
			// Start offset: 0x00013318
			// Variables:
		// 		int moreLevels; // $s3
		// 		short *check; // $s1
		// 		struct _sdPlane *base; // $s4
		/* end block 1.1 */
		// End offset: 0x000133E4
		// End Line: 372
	/* end block 1 */
	// End offset: 0x0001346C
	// End Line: 389

	/* begin block 2 */
		// Start line: 549
	/* end block 2 */
	// End Line: 550

	/* begin block 3 */
		// Start line: 550
	/* end block 3 */
	// End Line: 551

	/* begin block 4 */
		// Start line: 598
	/* end block 4 */
	// End Line: 599

int RoadInCell(VECTOR *pos)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	short sVar2;
	ushort uVar3;
	_sdPlane *plane;
	int iVar4;
	int iVar5;
	uint uVar6;
	ushort *puVar7;
	short *psVar8;

	iVar4 = pos->vx + -0x200;
	iVar5 = pos->vz + -0x200;
	psVar8 = RoadMapDataRegions4
		[iVar4 >> 0x10 & 1U ^ (cells_across >> 6 & 1U) + (iVar5 >> 0xf & 2U) ^
		cells_down >> 5 & 2U];
	if (*psVar8 == 2) {
		puVar7 = (ushort *)(psVar8 + (iVar4 >> 10 & 0x3fU) + (iVar5 >> 10 & 0x3fU) * 0x40 + 4);
		uVar6 = SEXT24((short)*puVar7);
		uVar3 = *puVar7;
		if (uVar6 == 0xffffffff) {
			return -1;
		}
		if ((uVar3 & 0xe000) == 0) {
			plane = (_sdPlane *)((int)psVar8 + uVar6 * 0xc + (int)psVar8[1]);
		}
		else {
			if ((uVar6 & 0x8000) != 0) {
				sVar2 = psVar8[1];
				bVar1 = ((uint)uVar3 & 0x6000) == 0x2000;
				if (bVar1) {
					puVar7 = (ushort *)((int)psVar8 + ((uint)uVar3 & 0x1fff) * 2 + (int)psVar8[2] + 2);
					goto LAB_0001335c;
				}
			LAB_00013370:
				uVar3 = *puVar7;
				if ((uVar3 & 0x4000) == 0) {
					plane = (_sdPlane *)((int)psVar8 + (int)sVar2) + (short)uVar3;
					if (0x1f < plane->surface) goto LAB_0001340c;
				}
				else {
					plane = FindRoadInBSP((_sdNode *)
						((int)psVar8 + ((uint)uVar3 & 0x3fff) * 4 + (int)psVar8[3]),
						(_sdPlane *)((int)psVar8 + (int)sVar2));
					if (plane != (_sdPlane *)0x0) goto LAB_00013414;
				}
				puVar7 = puVar7 + 2;
				if (!bVar1) goto LAB_0001340c;
			LAB_0001335c:
				if (puVar7[-1] == 0x8000) {
					bVar1 = false;
				}
				goto LAB_00013370;
			}
			plane = (_sdPlane *)0x0;
		}
	LAB_0001340c:
		if (plane == (_sdPlane *)0x0) {
			return -1;
		}
	LAB_00013414:
		if (0x1f < plane->surface) {
			iVar4 = sdHeightOnPlane(pos, plane);
			pos->vy = iVar4 + 0x100;
			return (int)plane->surface + -0x20;
		}
	}
	return -1;*/
}



// decompiled code
// original method signature: 
// struct _sdPlane * /*$ra*/ sdGetCell(struct VECTOR *pos /*$s3*/)
 // line 400, offset 0x0001346c
	/* begin block 1 */
		// Start line: 401
		// Start offset: 0x0001346C
		// Variables:
	// 		char *buffer; // $s1
	// 		short *surface; // $s0
	// 		int nextLevel; // $s2
	// 		struct _sdPlane *plane; // $a1
	// 		struct XYPAIR cell; // stack offset -40
	// 		struct XYPAIR cellPos; // stack offset -32

		/* begin block 1.1 */
			// Start line: 441
			// Start offset: 0x0001355C
			// Variables:
		// 		int y; // $a0
		/* end block 1.1 */
		// End offset: 0x000135B8
		// End Line: 456

		/* begin block 1.2 */
			// Start line: 463
			// Start offset: 0x000135CC
			// Variables:
		// 		short *BSPsurface; // $a0
		/* end block 1.2 */
		// End offset: 0x00013634
		// End Line: 481
	/* end block 1 */
	// End offset: 0x000136C0
	// End Line: 502

	/* begin block 2 */
		// Start line: 828
	/* end block 2 */
	// End Line: 829

	/* begin block 3 */
		// Start line: 840
	/* end block 3 */
	// End Line: 841

	/* begin block 4 */
		// Start line: 852
	/* end block 4 */
	// End Line: 853

int sdLevel = 0;

// [D]
_sdPlane * sdGetCell(VECTOR *pos)
{
	bool bVar1;
	_sdPlane *plane;
	short *psVar2;
	ushort *puVar3;
	ushort *puVar4;
	short *psVar5;
	XYPAIR local_20;

	sdLevel = 0;
	local_20.x = pos->vx - 0x200;
	local_20.y = pos->vz - 0x200;

	psVar5 = RoadMapDataRegions[(int)local_20.x >> 0x10 & 1U ^ (cells_across >> 6 & 1U) + ((int)local_20.y >> 0xf & 2U) ^ cells_down >> 5 & 2U];
	plane = NULL;

	if (*psVar5 == 2) 
	{
		puVar3 = (ushort *)(psVar5 + ((int)local_20.x >> 10 & 0x3fU) + ((int)local_20.y >> 10 & 0x3fU) * 0x40 + 4);
		if (*puVar3 == 0xffff) 
		{
			plane = &sea;
		}
		else 
		{
			if (((uint)*puVar3 & 0x6000) == 0x2000) 
			{
				psVar2 = (short *)((int)psVar5 + ((uint)*puVar3 & 0x1fff) * 2 + (int)psVar5[2]);

				do {
					if (-0x100 - pos->vy <= (int)*psVar2) break;
					psVar2 = psVar2 + 2;
					sdLevel = sdLevel + 1;
				} while (*psVar2 != -0x8000);

				puVar3 = (ushort *)(psVar2 + 1);
			}
			do {
				bVar1 = false;
				puVar4 = puVar3;

				if ((*puVar3 & 0x4000) != 0) 
				{
					local_20.x = local_20.x & 0x3ff;
					local_20.y = local_20.y & 0x3ff;
					puVar4 = (ushort *)sdGetBSP((_sdNode *)((int)psVar5 + ((uint)*puVar3 & 0x3fff) * 4 + (int)psVar5[3]), &local_20);
					if (*puVar4 == 0x7fff) {
						sdLevel = sdLevel + 1;
						bVar1 = true;
						puVar4 = puVar3 + 2;
					}
				}

				puVar3 = puVar4;
			} while (bVar1);

			plane = (_sdPlane *)((int)psVar5 + (int)(short)*puVar4 * 0xc + (int)psVar5[1]);

			if ((((uint)plane & 3) == 0) && (*(int *)plane != -1)) 
			{
				if ((uint)(ushort)plane->surface - 0x10 < 0x10)
				{
					plane = EventSurface(pos, plane);
				}
			}
			else 
			{
				plane = &sea;
			}
		}
	}
	return plane;
}



// decompiled code
// original method signature: 
// short * /*$ra*/ sdGetBSP(struct _sdNode *node /*$a3*/, struct XYPAIR *pos /*$a1*/)
 // line 505, offset 0x00013848
	/* begin block 1 */
		// Start line: 506
		// Start offset: 0x00013848

		/* begin block 1.1 */
			// Start line: 509
			// Start offset: 0x00013870
			// Variables:
		// 		int dot; // $a0
		/* end block 1.1 */
		// End offset: 0x000138D4
		// End Line: 522
	/* end block 1 */
	// End offset: 0x000138F0
	// End Line: 524

	/* begin block 2 */
		// Start line: 1560
	/* end block 2 */
	// End Line: 1561

// [D]
short * sdGetBSP(_sdNode *node, XYPAIR *pos)
{
	uint uVar1;
	uint uVar2;

	uVar2 = node->angle;
	if ((int)uVar2 < 0) {
		do {
			uVar1 = (int)(uVar2 << 0x15) >> 0x13 & 0x3ffc;
			if (pos->y * (int)*(short *)((int)rcossin_tbl + uVar1 + 2) -
				pos->x * (int)*(short *)((int)rcossin_tbl + uVar1) < ((int)(uVar2 << 9) >> 0x14) << 0xc) {
				node = (_sdNode *)&node->dist;
			}
			else {
				node = (_sdNode *)(&node->angle + ((int)(uVar2 << 1) >> 0x18));
			}
			uVar2 = node->angle;
		} while ((uVar2 & 0x80000000) != 0);
	}
	return (short *)node;
}





