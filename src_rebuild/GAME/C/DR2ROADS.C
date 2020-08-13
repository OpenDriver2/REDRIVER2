#include "THISDUST.H"
#include "DR2ROADS.H"

#include "SYSTEM.H"
#include "MAP.H"
#include "EVENT.H"
#include "CONVERT.H"
#include "CUTSCENE.H"
#include "MISSION.H"

#if defined(_DEBUG) || defined(DEBUG_OPTIONS)
sdPlane sea = { 0, 0, 0, 0, 2048 };
#else
sdPlane sea = { 9, 0, 16384, 0, 2048 }; // a default surface if FindSurfaceD2 fails
#endif

ROAD_MAP_LUMP_DATA roadMapLumpData;
short* RoadMapDataRegions[4];

int NumTempJunctions = 0;
DRIVER2_JUNCTION *Driver2JunctionsPtr = NULL;
ulong *Driver2TempJunctionsPtr = NULL;

DRIVER2_CURVE *Driver2CurvesPtr = NULL;
int NumDriver2Curves = 0;

int NumDriver2Straights = 0;
DRIVER2_STRAIGHT *Driver2StraightsPtr = NULL;

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
	Getlong((char *)&NumDriver2Straights, lump_file);
	Driver2StraightsPtr = (DRIVER2_STRAIGHT *)(lump_file + 4);
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

int NumDriver2Junctions = 0;

// [D]
void ProcessJunctionsDriver2Lump(char *lump_file, int lump_size, int fix)
{
	int loop;
	DRIVER2_JUNCTION *p;
	OLD_DRIVER2_JUNCTION *old;
	int i;

	Getlong((char *)&NumDriver2Junctions, lump_file);

	p = (DRIVER2_JUNCTION *)(lump_file + 4);
	Driver2JunctionsPtr = p;

	if (fix)
	{
		loop = 0;
		old = (OLD_DRIVER2_JUNCTION *)(lump_file + 4);

		for (loop = 0; loop < NumDriver2Junctions; loop++)
		{
			p->flags = old->flags;
			for (i = 0; i < 4; i++)
				p->ExitIdx[i] = old->ExitIdx[i];

			p++;
			old++;
		}
	}
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

// [D]
int FindSurfaceD2(VECTOR *pos, VECTOR *normal, VECTOR *out, _sdPlane **plane)
{
	_sdPlane *p_Var1;
	int iVar2;

	p_Var1 = sdGetCell(pos);
	*plane = p_Var1;
	out->vx = pos->vx;
	out->vz = pos->vz;
	iVar2 = sdHeightOnPlane(pos, *plane);
	out->vy = iVar2;
	p_Var1 = *plane;

	if ((p_Var1 == NULL) || (p_Var1->b == 0))
	{
		normal->vx = 0;
		normal->vy = 0x1000;
		normal->vz = 0;
	}
	else 
	{
		normal->vx = (int)((uint)(ushort)p_Var1->a << 0x10) >> 0x12;
		normal->vy = (int)((uint)(ushort)(*plane)->b << 0x10) >> 0x12;
		normal->vz = (int)((uint)(ushort)(*plane)->c << 0x10) >> 0x12;
	}

	if (*plane == NULL)
	{
		iVar2 = 0x1000;
	}
	else 
	{
		iVar2 = 0x1000;

		if ((*plane)->surface == 4) 
		{
			if (((gInGameCutsceneActive == 0) || (gCurrentMissionNumber != 0x17)) || (gInGameCutsceneID != 0)) 
			{
				iVar2 = out->vy + ((((int)((uint)*(ushort *)
					((int)rcossin_tbl +
					((pos->vx + pos->vz) * 8 & 0x3ff8U)) << 0x10) >>
					0x18) / 3) * 0x10000 >> 0x10);
			}
			else
			{
				iVar2 = out->vy + ((int)((uint)*(ushort *)
					((int)rcossin_tbl +
					((pos->vx + pos->vz) * 8 & 0x3ff8U)) << 0x10) >>
					0x19);
			}

			out->vy = iVar2;
			iVar2 = 0x800;
		}
	}

	return iVar2;
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
	int uVar2;
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

			return FIXED(iVar4) - pDVar3->height;
		}

		iVar4 = (int)plane->b;

		if (iVar4 != 0)
		{
			if (iVar4 == 0x4000) 
				return -uVar2;

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
	_sdPlane *plane = sdGetCell(pos);

	if (plane == NULL)
		return -32;
 
	return plane->surface - 32;
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
#if 0
	_sdPlane *plane;

	while (true) 
	{
		if (node->value > -1) 
		{
			base += node->value;
			return (base->surface < 32) ? NULL : base;
		}

		plane = FindRoadInBSP(node+1, base);

		if (plane != NULL) 
			break;

		node += ((node->value << 1) >> 0x18);	// offset
	}

	return plane;
#else
	_sdPlane *plane;

	while (true)
	{
		if (node->value > -1)
		{
			base += node->value;
			return (base->surface < 32) ? NULL : base;
		}

		plane = FindRoadInBSP(node+1, base);

		if (plane != NULL)
			break;

		node += node->n.offset;	// offset
	}

	return plane;
#endif
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

// [D]
int RoadInCell(VECTOR *pos)
{
	bool bVar1;
	short sVar2;
	ushort uVar3;
	_sdPlane *plane;
	int iVar4;
	int iVar5;
	int local_a2_200;
	ushort *puVar6;
	short *psVar7;

	iVar4 = pos->vx - 0x200;
	iVar5 = pos->vz - 0x200;
	psVar7 = RoadMapDataRegions[iVar4 >> 0x10 & 1U ^ (cells_across >> 6 & 1U) + (iVar5 >> 0xf & 2U) ^ cells_down >> 5 & 2U];

	if (*psVar7 == 2) 
	{
		puVar6 = (ushort *)(psVar7 + (iVar4 >> 10 & 0x3fU) + (iVar5 >> 10 & 0x3fU) * 0x40 + 4);

		local_a2_200 = (int)(short)*puVar6;
		uVar3 = *puVar6;

		if (local_a2_200 == -1)
			return -1;

		if ((uVar3 & 0xe000) == 0) 
		{
			plane = (_sdPlane *)((int)psVar7 + local_a2_200 * sizeof(_sdPlane) + (int)psVar7[1]);
		}
		else
		{
			if ((local_a2_200 & 0x8000U) != 0)
			{
				sVar2 = psVar7[1];
				bVar1 = ((uint)uVar3 & 0x6000) == 0x2000;
				if (bVar1) 
				{
					puVar6 = (ushort *)((int)psVar7 + ((uint)uVar3 & 0x1fff) * 2 + (int)psVar7[2] + 2);
					goto LAB_0001335c;
				}

			LAB_00013370:
				uVar3 = *puVar6;
				if ((uVar3 & 0x4000) == 0) 
				{
					plane = (_sdPlane *)((int)psVar7 + (int)sVar2) + (short)uVar3;
					if (0x1f < plane->surface) goto LAB_0001340c;
				}
				else 
				{
					plane = FindRoadInBSP((_sdNode *) ((int)psVar7 + ((uint)uVar3 & 0x3fff) * sizeof(_sdNode) + (int)psVar7[3]), (_sdPlane *)((int)psVar7 + (int)sVar2));

					if (plane != NULL) 
						goto LAB_00013414;
				}

				puVar6 = puVar6 + 2;
				if (!bVar1)
					goto LAB_0001340c;

			LAB_0001335c:
				if (puVar6[-1] == 0x8000)
				{
					bVar1 = false;
				}
				goto LAB_00013370;
			}
			plane = NULL;
		}
	LAB_0001340c:
		if (plane == NULL)
			return -1;

	LAB_00013414:
		if (0x1f < plane->surface) 
		{
			iVar4 = sdHeightOnPlane(pos, plane);
			pos->vy = iVar4 + 0x100;
			return plane->surface - 32;
		}
	}

	return -1;
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

int sdLevel = 0; // debug value?

// [D]
_sdPlane * sdGetCell(VECTOR *pos)
{
	bool bVar1;
	_sdPlane *plane;
	short *psVar2;
	short *surface;
	short *surface1;
	short *buffer;
	XYPAIR cell;
	XYPAIR cellPos;

	sdLevel = 0;

	cellPos.x = pos->vx - 512;
	cellPos.y = pos->vz - 512;

	buffer = RoadMapDataRegions[cellPos.x >> 0x10 & 1U ^ (cells_across >> 6 & 1U) + (cellPos.y >> 0xf & 2U) ^ cells_down >> 5 & 2U];

	plane = NULL;

	if (*buffer == 2) 
	{
		surface = buffer + (cellPos.x >> 10 & 0x3fU) + (cellPos.y >> 10 & 0x3fU) * 0x40 + 4;

		if (*surface == -1) 
		{
			plane = &sea;
		}
		else 
		{
			if (((uint)(ushort)*surface & 0x6000) == 0x2000) 
			{
				psVar2 = (short *)((int)buffer +((uint)(ushort)*surface & 0x1fff) * 2 + (int)buffer[2]);

				do 
				{
					if (-256 - pos->vy <= (int)*psVar2)
						break;

					psVar2 = psVar2 + 2;
					sdLevel = sdLevel + 1;
				} while (*psVar2 != -0x8000);

				surface = psVar2 + 1;
			}

			do 
			{
				bVar1 = false;
				surface1 = surface;

				if ((*surface & 0x4000U) != 0) 
				{
					cellPos.x = cellPos.x & 0x3ff;
					cellPos.y = cellPos.y & 0x3ff;

					surface1 = sdGetBSP((_sdNode *)((int)buffer + ((uint)(ushort)*surface & 0x3fff) * 4 + (int)buffer[3]), &cellPos);

					if (*surface1 == 0x7fff) 
					{
						sdLevel = sdLevel + 1;
						bVar1 = true;
						surface1 = surface + 2;
					}
				}
				surface = surface1;
			} while (bVar1);

			plane = (_sdPlane *)((int)buffer + (int)*surface1 * 0xc + (int)buffer[1]);

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
short* sdGetBSP(_sdNode *node, XYPAIR *pos)
{
#if 0
	int local_v1_48;
	int local_a2_4;

	local_a2_4 = node->value;
	if (local_a2_4 < 0) {
		do {
			local_v1_48 = (local_a2_4 << 0x15) >> 0x13 & 0x3ffc;
			if (pos->y * (int)*(short *)((int)rcossin_tbl + local_v1_48 + 2) -
				pos->x * (int)*(short *)((int)rcossin_tbl + local_v1_48) <
				((local_a2_4 << 9) >> 0x14) << 0xc) {
				node = node + 1;
			}
			else {
				node = node + ((local_a2_4 << 1) >> 0x18);
			}
			local_a2_4 = node->value;
		} while ((local_a2_4 & 0x80000000U) != 0);
	}
	return (short *)node;
#else
	// new
	if (node->value < 0)
	{
		do
		{
			int ang = ((node->n.angle * 4) & 0x3ffc) / 2;
			int dot = pos->y * rcossin_tbl[ang + 1] - pos->x * rcossin_tbl[ang];

			if (dot < node->n.dist * 4096)
				node++;
			else
				node += node->n.offset;
		} while ((node->value & 0x80000000U) != 0);
	}

	return (short *)node;
#endif
}





