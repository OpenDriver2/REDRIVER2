#include "THISDUST.H"
#include "OBJCOLL.H"
#include "CARS.H"
#include "CAMERA.H"
#include "BCOLLIDE.H"
#include "BCOLL3D.H"
#include "EVENT.H"
#include "MAP.H"
#include "DRAW.H"
#include "HANDLING.H"
#include "MODELS.H"
#include "MISSION.H"
#include "PEDEST.H"
#include "SPOOL.H"
#include "CELL.H"
#include "PLAYERS.H"

#include "MAIN.H"


// decompiled code
// original method signature: 
// char /*$ra*/ CellEmpty(struct VECTOR *pPosition /*$s1*/, int radius /*$s2*/)
 // line 63, offset 0x00069ba4
	/* begin block 1 */
		// Start line: 64
		// Start offset: 0x00069BA4
		// Variables:
	// 		struct CELL_ITERATOR ci; // stack offset -48
	// 		int cell_x; // $a0
	// 		struct CELL_OBJECT *pCellObject; // $a2
	// 		struct MODEL *pModel; // $a3

		/* begin block 1.1 */
			// Start line: 100
			// Start offset: 0x00069C60
			// Variables:
		// 		int sphere_sq; // $v0
		// 		int xd; // $t5
		// 		int zd; // $t4

			/* begin block 1.1.1 */
				// Start line: 114
				// Start offset: 0x00069CC4
				// Variables:
			// 		int box_loop; // $t3
			// 		int num_cb; // $t6
			// 		struct COLLISION_PACKET *collide; // $t0

				/* begin block 1.1.1.1 */
					// Start line: 119
					// Start offset: 0x00069CE8
					// Variables:
				// 		unsigned int zs; // $t2
				// 		unsigned int xs; // $t1
				// 		int cs; // $a2
				// 		int sn; // $a0
				/* end block 1.1.1.1 */
				// End offset: 0x00069DC8
				// End Line: 138
			/* end block 1.1.1 */
			// End offset: 0x00069DD8
			// End Line: 139
		/* end block 1.1 */
		// End offset: 0x00069DD8
		// End Line: 141
	/* end block 1 */
	// End offset: 0x00069E1C
	// End Line: 153

	/* begin block 2 */
		// Start line: 126
	/* end block 2 */
	// End Line: 127

char CellEmpty(VECTOR *pPosition, int radius)
{
	UNIMPLEMENTED();
	return 0;
	/*
	PACKED_CELL_OBJECT *ppco;
	CELL_OBJECT *pCVar1;
	int iVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	int *piVar6;
	int iVar7;
	int iVar8;
	int *piVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	CELL_ITERATOR CStack48;

	iVar3 = pPosition->vx + units_across_halved;
	if (iVar3 < 0) {
		iVar3 = iVar3 + 0x7ff;
	}
	iVar2 = pPosition->vz + units_down_halved;
	if (iVar2 < 0) {
		iVar2 = iVar2 + 0x7ff;
	}
	ppco = GetFirstPackedCop(iVar3 >> 0xb, iVar2 >> 0xb, &CStack48, 0);
	pCVar1 = UnpackCellObject(ppco, &CStack48.nearCell);
	do {
		if (pCVar1 == (CELL_OBJECT *)0x0) {
			return '\x01';
		}
		piVar6 = (int *)modelpointers1536[pCVar1->type]->collision_block;
		if (piVar6 != (int *)0x0) {
			iVar12 = (int)(((uint)*(ushort *)&(pCVar1->pos).vx - (uint)*(ushort *)&pPosition->vx) *
				0x10000) >> 0x10;
			iVar2 = (int)(((uint)*(ushort *)&(pCVar1->pos).vz - (uint)*(ushort *)&pPosition->vz) * 0x10000
				) >> 0x10;
			iVar3 = (int)modelpointers1536[pCVar1->type]->bounding_sphere + 0x244;
			piVar9 = piVar6 + 1;
			if (iVar12 * iVar12 + iVar2 * iVar2 < iVar3 * iVar3) {
				iVar3 = 0;
				if (0 < *piVar6) {
					do {
						iVar11 = (int)*(short *)((int)piVar9 + 0x12) * 0x800 + radius * 0x1000;
						iVar10 = (int)*(short *)((int)piVar9 + 0xe) * 0x800 + radius * 0x1000;
						uVar4 = ((uint)pCVar1->yang + (int)*(short *)((int)piVar9 + 10)) * 0x100 & 0x3f00;
						iVar7 = pPosition->vy +
							((int)(((uint)*(ushort *)&(pCVar1->pos).vy + (uint)*(ushort *)(piVar9 + 1)) *
								0x10000) >> 0x10) + 0x50;
						if (iVar7 < 0) {
							iVar7 = -iVar7;
						}
						iVar8 = (int)*(short *)((int)rcossin_tbl + uVar4 + 2);
						iVar5 = (int)*(short *)((int)rcossin_tbl + uVar4);
						if (((iVar7 < (((int)((uint)*(ushort *)(piVar9 + 4) << 0x10) >> 0x10) -
							((int)((uint)*(ushort *)(piVar9 + 4) << 0x10) >> 0x1f) >> 1) + 0x3c) &&
							((uint)((iVar12 * iVar8 - iVar2 * iVar5) + iVar10) < (uint)(iVar10 * 2))) &&
							((uint)(iVar2 * iVar8 + iVar12 * iVar5 + iVar11) < (uint)(iVar11 * 2))) {
							return '\0';
						}
						iVar3 = iVar3 + 1;
						piVar9 = piVar9 + 5;
					} while (iVar3 < *piVar6);
				}
			}
		}
		ppco = GetNextPackedCop(&CStack48);
		pCVar1 = UnpackCellObject(ppco, &CStack48.nearCell);
	} while (true);*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ GlobalPositionToCellNumber(struct VECTOR *pPosition /*$a0*/)
 // line 155, offset 0x0006b2ec
	/* begin block 1 */
		// Start line: 156
		// Start offset: 0x0006B2EC
		// Variables:
	// 		int cellX; // $a3
	// 		int cellZ; // $a1
	// 		int cbrX; // $t1
	// 		int cbrZ; // $t0
	// 		int cbr; // $t2
	// 		int xOff; // $a3
	// 		int yOff; // $a0
	/* end block 1 */
	// End offset: 0x0006B3E4
	// End Line: 175

	/* begin block 2 */
		// Start line: 1770
	/* end block 2 */
	// End Line: 1771

	/* begin block 3 */
		// Start line: 310
	/* end block 3 */
	// End Line: 311

	/* begin block 4 */
		// Start line: 1773
	/* end block 4 */
	// End Line: 1774

int GlobalPositionToCellNumber(VECTOR *pPosition)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	int iVar3;
	uint uVar4;
	uint uVar5;
	int iVar6;

	iVar1 = pPosition->vx + units_across_halved;
	iVar3 = iVar1 + -0x400;
	if (iVar3 < 0) {
		iVar3 = iVar1 + 0x3ff;
	}
	iVar1 = pPosition->vz + units_down_halved;
	iVar2 = iVar1 + -0x400;
	iVar3 = iVar3 >> 0xb;
	if (iVar2 < 0) {
		iVar2 = iVar1 + 0x3ff;
	}
	iVar2 = iVar2 >> 0xb;
	iVar1 = iVar3;
	if (iVar3 < 0) {
		iVar1 = iVar3 + 0x1f;
	}
	uVar5 = iVar1 >> 5;
	iVar1 = iVar2;
	if (iVar2 < 0) {
		iVar1 = iVar2 + 0x1f;
	}
	uVar4 = iVar1 >> 5;
	iVar6 = (uVar5 & 1) + (uVar4 & 1) * 2;
	iVar1 = cells_across;
	if (cells_across < 0) {
		iVar1 = cells_across + 0x1f;
	}
	if (RoadMapRegions[iVar6] != uVar5 + uVar4 * (iVar1 >> 5)) {
		return -1;
	}
	return (uint)cell_ptrs[(iVar2 + uVar4 * -0x20) * 0x20 + iVar6 * 0x400 + iVar3 + uVar5 * -0x20];*/
}



// decompiled code
// original method signature: 
// char /*$ra*/ CellAtPositionEmpty(struct VECTOR *pPosition /*$s0*/, int radius /*$s1*/)
 // line 183, offset 0x0006b3e4
	/* begin block 1 */
		// Start line: 184
		// Start offset: 0x0006B3E4
	/* end block 1 */
	// End offset: 0x0006B430
	// End Line: 205

	/* begin block 2 */
		// Start line: 1826
	/* end block 2 */
	// End Line: 1827

	/* begin block 3 */
		// Start line: 1835
	/* end block 3 */
	// End Line: 1836

// [D]
char CellAtPositionEmpty(VECTOR *pPosition, int radius)
{
	char cVar1;
	int iVar2;

	iVar2 = GlobalPositionToCellNumber(pPosition);
	if (iVar2 == -1)
		cVar1 = 1;
	else
		cVar1 = CellEmpty(pPosition, radius);

	return cVar1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ RaySlabsIntersection(struct tRay *ray /*$t5*/, struct tAABB *bbox /*$t4*/)
 // line 217, offset 0x00069e1c
	/* begin block 1 */
		// Start line: 218
		// Start offset: 0x00069E1C
		// Variables:
	// 		int i; // $t1
	// 		struct tRange inside; // stack offset -24

		/* begin block 1.1 */
			// Start line: 226
			// Start offset: 0x00069E40
			// Variables:
		// 		struct tRange cabbage; // stack offset -16
		// 		struct tRange scaledCabbage; // stack offset -8
		// 		int dir; // $a2
		/* end block 1.1 */
		// End offset: 0x00069F94
		// End Line: 253
	/* end block 1 */
	// End offset: 0x00069FB4
	// End Line: 255

	/* begin block 2 */
		// Start line: 435
	/* end block 2 */
	// End Line: 436

	/* begin block 3 */
		// Start line: 500
	/* end block 3 */
	// End Line: 501

	/* begin block 4 */
		// Start line: 506
	/* end block 4 */
	// End Line: 507

// [D]
int RaySlabsIntersection(tRay *ray, tAABB *bbox)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	tAABB *ptVar6;
	tRay *ptVar7;
	int local_18;
	int local_14;
	int local_8;
	int local_4;

	iVar5 = 0;
	local_18 = 0;
	local_14 = 0x1000;
	ptVar6 = bbox;
	ptVar7 = ray;
	do {
		uVar4 = 0xffffffff;
		iVar3 = ptVar6->slab[0].lower - ptVar7->org[0];
		iVar2 = ray->dir[iVar5];
		iVar1 = bbox->slab[iVar5].upper - ptVar7->org[0];
		if (-1 < iVar2) {
			uVar4 = (uint)(iVar2 != 0);
		}
		if (uVar4 == 0) {
			if (0 < iVar3) {
				return 0;
			}
			if (iVar1 < 0) {
				return 0;
			}
			local_4 = 0x3000;
			local_8 = -0x3000;
		}
		else {
			if ((int)uVar4 < 1) {
				if (uVar4 == 0xffffffff) {
					local_4 = (iVar3 * 0x1000) / iVar2;
					if (iVar2 == 0) {
						trap(7);
					}
					local_8 = (iVar1 * 0x1000) / iVar2;
					if (iVar2 == 0) {
						trap(7);
					}
				}
			}
			else {
				if (uVar4 == 1) {
					local_8 = (iVar3 * 0x1000) / iVar2;
					if (iVar2 == 0) {
						trap(7);
					}
					local_4 = (iVar1 * 0x1000) / iVar2;
					if (iVar2 == 0) {
						trap(7);
					}
				}
			}
		}
		if (local_18 < local_8) {
			local_18 = local_8;
		}
		if (local_4 < local_14) {
			local_14 = local_4;
		}
		if (local_14 < local_18) {
			return 0;
		}
		ptVar7 = (tRay *)(ptVar7->org + 1);
		iVar5 = iVar5 + 1;
		ptVar6 = (tAABB *)(ptVar6->slab + 1);
		if (2 < iVar5) {
			return 1;
		}
	} while (true);
}



// decompiled code
// original method signature: 
// char /*$ra*/ lineClear(struct VECTOR *v1 /*stack 0*/, struct VECTOR *v2 /*stack 4*/)
 // line 259, offset 0x00069fb4
	/* begin block 1 */
		// Start line: 260
		// Start offset: 0x00069FB4
		// Variables:
	// 		int we; // stack offset -56
	// 		int ocx; // $t2
	// 		int ocz; // $t3
	// 		struct VECTOR pos; // stack offset -184
	// 		struct VECTOR va; // stack offset -168
	// 		struct VECTOR vb; // stack offset -152

		/* begin block 1.1 */
			// Start line: 279
			// Start offset: 0x0006A074
			// Variables:
		// 		int cell_x; // $fp
		// 		int cell_z; // $s7
		// 		struct CELL_ITERATOR ci; // stack offset -136
		// 		struct CELL_OBJECT *pCellObject; // $s4

			/* begin block 1.1.1 */
				// Start line: 299
				// Start offset: 0x0006A134
				// Variables:
			// 		struct MODEL *pModel; // $a1

				/* begin block 1.1.1.1 */
					// Start line: 307
					// Start offset: 0x0006A170
					// Variables:
				// 		int sphere_sq; // $v0
				// 		int xd; // $a0
				// 		int zd; // $v1

					/* begin block 1.1.1.1.1 */
						// Start line: 318
						// Start offset: 0x0006A1D4
						// Variables:
					// 		int box_loop; // $s5
					// 		int num_cb; // $s6
					// 		struct COLLISION_PACKET *collide; // $s3

						/* begin block 1.1.1.1.1.1 */
							// Start line: 323
							// Start offset: 0x0006A1F0
							// Variables:
						// 		struct MATRIX *mat; // $a0
						// 		int cx; // $v1
						// 		int cy; // $a2
						// 		int cz; // $v0
						// 		int cs; // $t1
						// 		int sn; // $t5

							/* begin block 1.1.1.1.1.1.1 */
								// Start line: 323
								// Start offset: 0x0006A1F0
								// Variables:
							// 		struct tRay ray; // stack offset -112
							// 		struct tAABB box; // stack offset -80
							/* end block 1.1.1.1.1.1.1 */
							// End offset: 0x0006A414
							// End Line: 347
						/* end block 1.1.1.1.1.1 */
						// End offset: 0x0006A414
						// End Line: 348
					/* end block 1.1.1.1.1 */
					// End offset: 0x0006A424
					// End Line: 349
				/* end block 1.1.1.1 */
				// End offset: 0x0006A424
				// End Line: 351
			/* end block 1.1.1 */
			// End offset: 0x0006A424
			// End Line: 352
		/* end block 1.1 */
		// End offset: 0x0006A444
		// End Line: 355
	/* end block 1 */
	// End offset: 0x0006A498
	// End Line: 360

	/* begin block 2 */
		// Start line: 633
	/* end block 2 */
	// End Line: 634

	/* begin block 3 */
		// Start line: 638
	/* end block 3 */
	// End Line: 639

	/* begin block 4 */
		// Start line: 654
	/* end block 4 */
	// End Line: 655


char lineClear(VECTOR *v1, VECTOR *v2)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	VECTOR *pVVar2;
	PACKED_CELL_OBJECT *ppco;
	int iVar3;
	CELL_OBJECT *pCVar4;
	int iVar5;
	int cellz;
	int iVar6;
	int iVar7;
	int cellx;
	int iVar8;
	uint uVar9;
	int iVar10;
	MODEL *pMVar11;
	int iVar12;
	int *piVar13;
	int iVar14;
	uint uVar15;
	int iVar16;
	int iVar17;
	int iVar18;
	int iVar19;
	int iVar20;
	int iVar21;
	int *piVar22;
	CELL_ITERATOR CStack136;
	tRay local_70;
	tAABB local_50;
	int local_38;
	int local_30;

	iVar7 = v1->vx;
	iVar10 = v1->vy;
	iVar12 = v1->vz;
	iVar16 = v2->vx;
	local_38 = 0;
	iVar1 = iVar16 - iVar7;
	iVar14 = v2->vy;
	iVar18 = v2->vz;
	iVar5 = iVar18 - iVar12;
	iVar3 = -1;
	iVar6 = -1;
	do {
		if (local_38 == 0) {
			cellx = v2->vx + units_across_halved;
			pVVar2 = v2;
			if (cellx < 0) {
				cellx = cellx + 0x7ff;
			}
		}
		else {
			cellx = v1->vx + units_across_halved;
			pVVar2 = v1;
			if (cellx < 0) {
				cellx = cellx + 0x7ff;
			}
		}
		cellz = pVVar2->vz + units_down_halved;
		cellx = cellx >> 0xb;
		if (cellz < 0) {
			cellz = cellz + 0x7ff;
		}
		cellz = cellz >> 0xb;
		if ((iVar3 != cellx) || (iVar6 != cellz)) {
			ppco = GetFirstPackedCop(cellx, cellz, &CStack136, 0);
			while (pCVar4 = UnpackCellObject(ppco, &CStack136.nearCell), pCVar4 != (CELL_OBJECT *)0x0) {
				pMVar11 = modelpointers1536[pCVar4->type];
				piVar13 = (int *)pMVar11->collision_block;
				if (((piVar13 != (int *)0x0) && ((pMVar11->flags2 & 0xa00) == 0)) &&
					(iVar8 = (int)(((uint)*(ushort *)&(pCVar4->pos).vx - ((iVar7 + iVar16) / 2 & 0xffffU)) *
						0x10000) >> 0x10,
						iVar6 = (int)(((uint)*(ushort *)&(pCVar4->pos).vz - ((iVar12 + iVar18) / 2 & 0xffffU)) *
							0x10000) >> 0x10, iVar3 = (int)pMVar11->bounding_sphere + 800,
						iVar8 * iVar8 + iVar6 * iVar6 < iVar3 * iVar3)) {
					piVar22 = piVar13 + 1;
					iVar6 = *piVar13;
					iVar3 = 0;
					if (0 < iVar6) {
						local_30 = 0xa3812;
						do {
							uVar9 = -(uint)pCVar4->yang & 0x3f;
							uVar15 = ((uint)pCVar4->yang + (int)*(short *)((int)piVar22 + 10)) * 0x100 & 0x3f00;
							iVar19 = (int)*(short *)(uVar15 + local_30);
							iVar21 = iVar7 - ((pCVar4->pos).vx +
								((int)*(short *)((int)piVar22 + 2) * (int)(&matrixtable)[uVar9].m[0]
									+ (int)*(short *)((int)piVar22 + 6) *
									(int)(&matrixtable)[uVar9].m[6] + 0x800 >> 0xc));
							iVar20 = (int)*(short *)((int)rcossin_tbl + uVar15);
							iVar17 = iVar12 - ((pCVar4->pos).vz +
								((int)*(short *)((int)piVar22 + 2) * (int)(&matrixtable)[uVar9].m[2]
									+ (int)*(short *)((int)piVar22 + 6) *
									(int)(&matrixtable)[uVar9].m[8] + 0x800 >> 0xc));
							iVar8 = (uint)*(ushort *)((int)piVar22 + 0xe) << 0x10;
							local_50.slab[0].upper = ((iVar8 >> 0x10) - (iVar8 >> 0x1f) >> 1) + testRadius;
							local_50.slab[0].lower = -local_50.slab[0].upper;
							local_50.slab[1].upper =
								(((int)((uint)*(ushort *)(piVar22 + 4) << 0x10) >> 0x10) -
								((int)((uint)*(ushort *)(piVar22 + 4) << 0x10) >> 0x1f) >> 1) + testRadius;
							local_50.slab[1].lower = -local_50.slab[1].upper;
							local_70.org[1] =
								(iVar10 - ((int)((-(uint)*(ushort *)(piVar22 + 1) -
								(uint)*(ushort *)&(pCVar4->pos).vy) * 0x10000) >> 0x10)) + 0x50;
							iVar8 = (uint)*(ushort *)((int)piVar22 + 0x12) << 0x10;
							local_50.slab[2].upper = ((iVar8 >> 0x10) - (iVar8 >> 0x1f) >> 1) + testRadius;
							local_50.slab[2].lower = -local_50.slab[2].upper;
							local_70.org[0] = (iVar19 * iVar21 - iVar20 * iVar17) + 0x800 >> 0xc;
							local_70.org[2] = iVar19 * iVar17 + iVar20 * iVar21 + 0x800 >> 0xc;
							local_70.dir[0] = (iVar19 * iVar1 - iVar20 * iVar5) + 0x800 >> 0xc;
							local_70.dir[2] = iVar19 * iVar5 + iVar20 * iVar1 + 0x800 >> 0xc;
							local_70.dir[1] = iVar14 - iVar10;
							iVar8 = RaySlabsIntersection(&local_70, &local_50);
							if (iVar8 != 0) {
								return '\0';
							}
							iVar3 = iVar3 + 1;
							piVar22 = piVar22 + 5;
						} while (iVar3 < iVar6);
					}
				}
				ppco = GetNextPackedCop(&CStack136);
			}
		}
		local_38 = local_38 + 1;
		iVar3 = cellx;
		iVar6 = cellz;
	} while (local_38 < 2);
	return '\x01';*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetCopListCell(int x /*$a0*/, int z /*$a1*/)
 // line 377, offset 0x0006b430
	/* begin block 1 */
		// Start line: 379
		// Start offset: 0x0006B430
		// Variables:
	// 		struct XZPAIR cell; // stack offset -16
	/* end block 1 */
	// End offset: 0x0006B45C
	// End Line: 384

	/* begin block 2 */
		// Start line: 2054
	/* end block 2 */
	// End Line: 2055

	/* begin block 3 */
		// Start line: 2227
	/* end block 3 */
	// End Line: 2228

	/* begin block 4 */
		// Start line: 2228
	/* end block 4 */
	// End Line: 2229

	/* begin block 5 */
		// Start line: 2229
	/* end block 5 */
	// End Line: 2230

// [D]
void SetCopListCell(int x, int z)
{
	XZPAIR cell;

	cell.x = x;
	cell.z = z;
	CollisionCopList(&cell, NULL);
}



// decompiled code
// original method signature: 
// void /*$ra*/ BuildCollisionCopList(int *count /*$a1*/)
 // line 386, offset 0x0006b45c
	/* begin block 1 */
		// Start line: 2245
	/* end block 1 */
	// End Line: 2246

	/* begin block 2 */
		// Start line: 2248
	/* end block 2 */
	// End Line: 2249

// [D]
void BuildCollisionCopList(int *count)
{
	CollisionCopList(NULL, count);
}

// decompiled code
// original method signature: 
// void /*$ra*/ CollisionCopList(struct XZPAIR *pos /*$a0*/, int *count /*$s0*/)
 // line 391, offset 0x0006a498
	/* begin block 1 */
		// Start line: 392
		// Start offset: 0x0006A498
		// Variables:
	// 		static struct XZPAIR initial; // offset 0x0

		/* begin block 1.1 */
			// Start line: 402
			// Start offset: 0x0006A4E8
			// Variables:
		// 		struct XZPAIR cell; // stack offset -72
		// 		int i; // $a0
		// 		int j; // $t1

			/* begin block 1.1.1 */
				// Start line: 411
				// Start offset: 0x0006A508
				// Variables:
			// 		struct CELL_ITERATOR ci; // stack offset -64
			// 		struct XZPAIR cbr; // stack offset -40
			// 		int barrelRegion; // $v0
			// 		struct CELL_OBJECT *cop; // $a0
			/* end block 1.1.1 */
			// End offset: 0x0006A5F8
			// End Line: 429
		/* end block 1.1 */
		// End offset: 0x0006A628
		// End Line: 431
	/* end block 1 */
	// End offset: 0x0006A64C
	// End Line: 432

	/* begin block 2 */
		// Start line: 1207
	/* end block 2 */
	// End Line: 1208

	/* begin block 3 */
		// Start line: 1239
	/* end block 3 */
	// End Line: 1240

// [D]
void CollisionCopList(XZPAIR *pos, int *count)
{
	static XZPAIR initial;

	PACKED_CELL_OBJECT *ppco;
	CELL_OBJECT *cop;
	int i;
	int j;
	XZPAIR cell;
	CELL_ITERATOR ci;
	XZPAIR cbr;

	if (pos == NULL)
	{
		i = 0;
		cell.x = initial.x;

		do {
			j = 0;

			i++;
			cell.z = initial.z;

			do {
				j++;

				// [A] FIXME: replace with 'cell_header.region_size'
				if ((cell.x / 32) + (cell.z / 32) * (cells_across / 32) == RoadMapRegions[((cell.x / 32) & 1) + ((cell.z / 32) & 1) * 2])
				{
					ppco = GetFirstPackedCop(cell.x, cell.z, &ci, 1);
					cop = UnpackCellObject(ppco, &ci.near);

					while (cop != NULL)
					{
						coplist[*count] = cop;
						cop->pad = *(unsigned char *)count;
						pcoplist[*count] = ci.ppco;

						ppco = GetNextPackedCop(&ci);
						cop = UnpackCellObject(ppco, &ci.near);

						*count = *count + 1;
					}
				}

				cell.z++;
			} while (j < 2);

			cell.x++;
		} while (i < 2);
	}
	else
	{
		initial.x = pos->x;
		initial.z = pos->z;

		ClearCopUsage();
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckScenaryCollisions(struct _CAR_DATA *cp /*$s7*/)
 // line 439, offset 0x0006a64c
	/* begin block 1 */
		// Start line: 440
		// Start offset: 0x0006A64C
		// Variables:
	// 		struct MODEL *model; // stack offset -76
	// 		struct CELL_OBJECT *cop; // $s5
	// 		struct VECTOR player_pos; // stack offset -152
	// 		struct COLLISION_PACKET *collide; // $s1
	// 		int cell_x; // $a0
	// 		int xd; // $v1
	// 		int zd; // $a0
	// 		int num_cb; // stack offset -72
	// 		int box_loop; // $s6
	// 		int sphere_sq; // $v0
	// 		int x1; // stack offset -68
	// 		struct BUILDING_BOX bbox; // stack offset -136
	// 		int mdcount; // stack offset -80
	// 		int coll_test_count; // $t0
	// 		struct XZPAIR box; // stack offset -104
	// 		int lbody; // stack offset -64
	// 		int extraDist; // stack offset -60

		/* begin block 1.1 */
			// Start line: 519
			// Start offset: 0x0006A934
			// Variables:
		// 		struct BUILDING_BOX *pbox; // $s4
		// 		struct MATRIX *mat; // $a1
		// 		struct VECTOR offset; // stack offset -96
		/* end block 1.1 */
		// End offset: 0x0006AD48
		// End Line: 591
	/* end block 1 */
	// End offset: 0x0006AD8C
	// End Line: 597

	/* begin block 2 */
		// Start line: 1368
	/* end block 2 */
	// End Line: 1369

	/* begin block 3 */
		// Start line: 1376
	/* end block 3 */
	// End Line: 1377

extern int boxOverlap;
ushort gLastModelCollisionCheck;
int ExBoxDamage = 0;

// [D]
void CheckScenaryCollisions(_CAR_DATA *cp)
{
	long lVar1;
	long lVar2;
	int iVar3;
	MODEL *pMVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int uVar9;
	int iVar10;
	int *piVar11;
	int iVar12;
	int iVar13;
	COLLISION_PACKET *piVar14;
	CELL_OBJECT *cop;
	VECTOR player_pos;
	BUILDING_BOX bbox;
	XZPAIR box;
	VECTOR offset;
	int mdcount;
	MODEL *model;
	int num_cb;
	int x1;
	int lbody;
	int extraDist;

	if (cp->controlType == 5 && cp->ap.carCos == NULL)
		lbody = 360;
	else
		lbody = cp->ap.carCos->colBox.vz;

	if (cp < car_data)
	{
		while (FrameCnt != 0x78654321)
			trap(0x400);
	}

	if (ghost_mode == 0 && (cp->controlType != 1 || playerghost == 0))
	{
		EventCollisions(cp, 0);

		lVar2 = car_data[0].hd.where.t[2];
		lVar1 = car_data[0].hd.where.t[0];

		extraDist = 580;

		iVar10 = cp->hd.where.t[0];
		iVar12 = cp->hd.where.t[2];

		boxOverlap = -1;

		if (cp->controlType == 6)
			extraDist = 100;

		iVar3 = iVar10 + units_across_halved;
		iVar6 = iVar3 - 1024;

		//if (iVar6 < 0)
		//	iVar6 = iVar3 + 1023;

		iVar3 = iVar12 + units_down_halved;
		iVar8 = iVar3 - 1024;

		//if (iVar8 < 0)
		//	iVar8 = iVar3 + 1023;

		// [A] FIXME: replace with 'cell_header.cell_size'
		SetCopListCell(iVar6 / 2048, iVar8 / 2048);

		mdcount = 0;
		Havana3DOcclusion(BuildCollisionCopList, &mdcount);

		x1 = 0;
		if (0 < mdcount + event_models_active)
		{
			do {
				if (x1 < mdcount)
					cop = coplist[x1];
				else
					cop = &EventCop[x1 - mdcount];

				pMVar4 = modelpointers[cop->type];
				iVar3 = x1 + 1;

				if (pMVar4->collision_block > 0 &&
					pMVar4->num_vertices-3 < 300 && 
					pMVar4->num_point_normals < 300 &&
					pMVar4->num_polys < 300)
				{
					iVar8 = cop->pos.vx - iVar10;
					iVar7 = cop->pos.vz - iVar12;
					iVar6 = pMVar4->bounding_sphere + extraDist + cp->hd.speed;

					if (iVar8 * iVar8 + iVar7 * iVar7 < iVar6 * iVar6)
					{
						iVar8 = 0;

						iVar6 = *(int *)pMVar4->collision_block;	// box count
						piVar14 = (COLLISION_PACKET*)(pMVar4->collision_block + 4);

						do {
							uVar9 = -cop->yang & 0x3f;

							// box 'rotated' by matrix
							// [A] FIXME: replace add+shift by division
							bbox.pos.vx = cop->pos.vx + FIXED(piVar14->xpos * matrixtable[uVar9].m[0][0] + piVar14->zpos * matrixtable[uVar9].m[2][0]);
							bbox.pos.vy = cop->pos.vy + piVar14->ypos;
							bbox.pos.vz = cop->pos.vz + FIXED(piVar14->xpos * matrixtable[uVar9].m[0][2] + piVar14->zpos * matrixtable[uVar9].m[2][2]);

							bbox.pos.pad = (pMVar4->flags2 >> 10) & 1;

							iVar7 = piVar14->zsize << 0x10;
							bbox.xsize = (iVar7 >> 0x10) - (iVar7 >> 0x1f) >> 1;

							iVar7 = piVar14->xsize << 0x10;
							bbox.zsize = (iVar7 >> 0x10) - (iVar7 >> 0x1f) >> 1;

							bbox.height = piVar14->ysize;
							bbox.theta = (cop->yang + piVar14->yang) * 64 & 0xfff;

							gLastModelCollisionCheck = cop->type;

							if (CAR_INDEX(cp) == 21)
							{
								if (x1 < mdcount || (cop->pad == 0))
								{
									CarBuildingCollision(cp, &bbox, cop, 0);
								}
								else
								{
									iVar7 = CarBuildingCollision(cp, &bbox, cop, 0);

									if (iVar7 != 0)
									{
										bKillTanner = 1;
										player[0].dying = 1;
									}
								}
							}
							else
							{
								if (cp->controlType == 5)
								{
									if ((modelpointers[cop->type]->flags2 & 0xa00) == 0 && (100 < bbox.xsize || (100 < bbox.zsize)))
									{
										iVar7 = 5;
										bbox.xsize += 100;
										bbox.zsize += 100;

										while ((iVar13 = lbody / 2, iVar13 <= gCameraDistance &&
											CarBuildingCollision(cp, &bbox, cop, 0) && 0 < iVar7))
										{
											gCameraDistance -= boxOverlap;
											if (gCameraDistance < iVar13)
												gCameraDistance = iVar13;

											iVar13 = gCameraDistance;
											uVar9 = cp->hd.direction & 0xfff;

											cp->hd.where.t[0] = lVar1 + FIXED((gCameraDistance * rcossin_tbl[uVar9 * 2]) / 2);
											cp->hd.where.t[2] = lVar2 + FIXED((iVar13 * rcossin_tbl[uVar9 * 2 + 1]) / 2);
											iVar7--;
										}
									}
								}
								else
								{
									if (x1 < mdcount || cop->pad == 0)
									{
										iVar7 = CarBuildingCollision(cp, &bbox, cop, (pMVar4->flags2 >> 10) & 1);

										if (iVar7 != 0)
											cp->ap.needsDenting = 1;
									}
									else
									{
										cp->st.n.linearVelocity[2] = ExBoxDamage + cp->st.n.linearVelocity[2];
										iVar7 = CarBuildingCollision(cp, &bbox, cop, 0);

										if (iVar7 != 0)
											cp->ap.needsDenting = 1;

										cp->st.n.linearVelocity[2] -= 700000;
									}
								}
							}
							iVar8++;
							piVar14++;
						} while (iVar8 < iVar6);
					}
				}

				x1 = iVar3;
			} while (iVar3 < mdcount + event_models_active);
		}

		EventCollisions(cp, 1);
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ QuickBuildingCollisionCheck(struct VECTOR *pPos /*$s5*/, int dir /*stack 4*/, int l /*stack 8*/, int w /*$fp*/, int extra /*stack 16*/)
 // line 609, offset 0x0006adbc
	/* begin block 1 */
		// Start line: 610
		// Start offset: 0x0006ADBC
		// Variables:
	// 		struct MODEL *model; // $a1
	// 		struct CELL_OBJECT *cop; // $s3
	// 		struct VECTOR player_pos; // stack offset -112
	// 		struct COLLISION_PACKET *collide; // $s0
	// 		int cell_x; // $a0
	// 		int xd; // $v1
	// 		int zd; // $a0
	// 		int num_cb; // $s7
	// 		int box_loop; // $s4
	// 		int sphere_sq; // $v0
	// 		int x1; // $s6
	// 		struct BUILDING_BOX bbox; // stack offset -96
	// 		int mdcount; // stack offset -48

		/* begin block 1.1 */
			// Start line: 669
			// Start offset: 0x0006AFA4
			// Variables:
		// 		struct BUILDING_BOX *pbox; // $s1
		// 		struct MATRIX *mat; // $a1
		// 		struct VECTOR offset; // stack offset -64

			/* begin block 1.1.1 */
				// Start line: 685
				// Start offset: 0x0006B0F0
			/* end block 1.1.1 */
			// End offset: 0x0006B1BC
			// End Line: 712
		/* end block 1.1 */
		// End offset: 0x0006B1BC
		// End Line: 714
	/* end block 1 */
	// End offset: 0x0006B220
	// End Line: 721

	/* begin block 2 */
		// Start line: 1891
	/* end block 2 */
	// End Line: 1892

int QuickBuildingCollisionCheck(VECTOR *pPos, int dir, int l, int w, int extra)
{
	UNIMPLEMENTED();
	return 0;
	/*
	bool bVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	MODEL *pMVar8;
	uint uVar9;
	int *piVar10;
	int iVar11;
	int iVar12;
	int *piVar13;
	CELL_OBJECT *pCVar14;
	short local_5c;
	int local_30[2];

	iVar5 = pPos->vx;
	boxOverlap = -1;
	iVar11 = pPos->vz;
	iVar12 = iVar5 + units_across_halved;
	iVar4 = iVar12 + -0x400;
	if (iVar4 < 0) {
		iVar4 = iVar12 + 0x3ff;
	}
	iVar12 = iVar11 + units_down_halved;
	iVar7 = iVar12 + -0x400;
	if (iVar7 < 0) {
		iVar7 = iVar12 + 0x3ff;
	}
	SetCopListCell(iVar4 >> 0xb, iVar7 >> 0xb);
	local_30[0] = 0;
	Havana3DOcclusion(0x5c, local_30);
	iVar4 = 0;
	if (0 < local_30[0] + event_models_active) {
		bVar1 = 0 < local_30[0];
		do {
			if (bVar1) {
				pCVar14 = coplist[iVar4];
			}
			else {
				pCVar14 = EventCop + (iVar4 - local_30[0]);
			}
			pMVar8 = modelpointers1536[pCVar14->type];
			if (((((uint)pMVar8->num_vertices - 3 < 300) && (pMVar8->num_point_normals < 300)) &&
				(pMVar8->num_polys < 300)) &&
				((piVar10 = (int *)pMVar8->collision_block, piVar10 != (int *)0x0 &&
				(iVar7 = (pCVar14->pos).vx - iVar5, iVar6 = (pCVar14->pos).vz - iVar11,
					iVar12 = pMVar8->bounding_sphere + extra, iVar7 * iVar7 + iVar6 * iVar6 < iVar12 * iVar12)
					))) {
				piVar13 = piVar10 + 1;
				iVar7 = *piVar10;
				iVar12 = 0;
				if (0 < iVar7) {
					do {
						uVar9 = -(uint)pCVar14->yang & 0x3f;
						local_5c = (short)(pCVar14->pos).vy + *(short *)(piVar13 + 1);
						iVar2 = (uint)*(ushort *)((int)piVar13 + 0x12) << 0x10;
						iVar3 = (uint)*(ushort *)((int)piVar13 + 0xe) << 0x10;
						iVar6 = pPos->vy + (int)local_5c;
						if (iVar6 < 0) {
							iVar6 = -iVar6;
						}
						if (iVar6 < ((int)((uint)*(ushort *)(piVar13 + 4) << 0x10) >> 0x10) -
							((int)((uint)*(ushort *)(piVar13 + 4) << 0x10) >> 0x1f) >> 1) {
							CDATA2D_000d920c.theta =
								((uint)pCVar14->yang + (int)*(short *)((int)piVar13 + 10)) * 0x40 & 0xfff;
							gLastModelCollisionCheck = pCVar14->type;
							cd.x.vx = pPos->vx;
							cd.x.vz = pPos->vz;
							CDATA2D_000d920c.length[1] = ((iVar3 >> 0x10) - (iVar3 >> 0x1f) >> 1) + 100;
							cd.vel.vx = 0;
							cd.vel.vz = 0;
							CDATA2D_000d920c.x.vx =
								pPos->vx +
								((int)((((pCVar14->pos).vx +
								((int)*(short *)((int)piVar13 + 2) * (int)(&matrixtable)[uVar9].m[0] +
									(int)*(short *)((int)piVar13 + 6) * (int)(&matrixtable)[uVar9].m[6] +
									0x800 >> 0xc) & 0xffffU) - (uint)*(ushort *)&pPos->vx) * 0x10000) >>
									0x10);
							CDATA2D_000d920c.vel.vx = 0;
							CDATA2D_000d920c.vel.vz = 0;
							CDATA2D_000d920c.avel = 0;
							CDATA2D_000d920c.x.vz =
								pPos->vz +
								((int)((((pCVar14->pos).vz +
								((int)*(short *)((int)piVar13 + 2) * (int)(&matrixtable)[uVar9].m[2] +
									(int)*(short *)((int)piVar13 + 6) * (int)(&matrixtable)[uVar9].m[8] +
									0x800 >> 0xc) & 0xffffU) - (uint)*(ushort *)&pPos->vz) * 0x10000) >>
									0x10);
							cd.theta = dir;
							cd.length[0] = l;
							cd.length[1] = w;
							CDATA2D_000d920c.length[0] = ((iVar2 >> 0x10) - (iVar2 >> 0x1f) >> 1) + 100;
							iVar6 = bcollided2d(&cd, 1);
							if (iVar6 != 0) {
								return 1;
							}
						}
						iVar12 = iVar12 + 1;
						piVar13 = piVar13 + 5;
					} while (iVar12 < iVar7);
				}
			}
			iVar4 = iVar4 + 1;
			bVar1 = iVar4 < local_30[0];
		} while (iVar4 < local_30[0] + event_models_active);
	}
	return 0;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoScenaryCollisions()
 // line 735, offset 0x0006b220
	/* begin block 1 */
		// Start line: 737
		// Start offset: 0x0006B220
		// Variables:
	// 		struct _CAR_DATA *lcp; // $s0
	/* end block 1 */
	// End offset: 0x0006B2EC
	// End Line: 753

	/* begin block 2 */
		// Start line: 2307
	/* end block 2 */
	// End Line: 2308

	/* begin block 3 */
		// Start line: 2322
	/* end block 3 */
	// End Line: 2323

	/* begin block 4 */
		// Start line: 2323
	/* end block 4 */
	// End Line: 2324

	/* begin block 5 */
		// Start line: 2324
	/* end block 5 */
	// End Line: 2325

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DoScenaryCollisions(void)
{
	_CAR_DATA *cp;

	cp = car_data + 19;

	do {
		if (cp->controlType != 0)
		{
			if (cp->controlType == 2)
			{
				if (cp->totalDamage != 0 && (10 < cp->hd.speed || (cp->id + CameraCnt & 3) == 0))
				{
					CheckScenaryCollisions(cp);
				}
			}
			else
			{
				CheckScenaryCollisions(cp);
			}
		}
		cp--;
	} while (cp >= car_data);
}





