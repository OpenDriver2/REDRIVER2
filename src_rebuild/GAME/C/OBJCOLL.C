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

// [D] [A] might be bugged
char CellEmpty(VECTOR *pPosition, int radius)
{
	PACKED_CELL_OBJECT* ppco;
	CELL_OBJECT* pCellObject;
	MODEL* pModel;
	int num_cb;
	int box_loop;
	int sphere_sq;
	int iVar1;
	int iVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	int* piVar6;
	int iVar7;
	int iVar8;
	COLLISION_PACKET* collide;
	int iVar9;
	int iVar10;
	int iVar11;
	CELL_ITERATOR ci;

	iVar3 = pPosition->vx + units_across_halved;
	iVar1 = pPosition->vz + units_down_halved;

	ppco = GetFirstPackedCop(iVar3 >> 0xb, iVar1 >> 0xb, &ci, 0);
	pCellObject = UnpackCellObject(ppco, &ci.nearCell);

	do {
		if (!pCellObject) 
			return 1;
	
		pModel = modelpointers[pCellObject->type];

		piVar6 = (int*)pModel->collision_block;

		if (piVar6 != NULL)
		{
			num_cb = *piVar6;

			iVar11 = ((pCellObject->pos.vx - pPosition->vx) * 0x10000) >> 0x10;
			iVar1 = ((pCellObject->pos.vz - pPosition->vz) * 0x10000) >> 0x10;

			sphere_sq = pModel->bounding_sphere + 580;
			sphere_sq = (sphere_sq * sphere_sq);

			collide = (COLLISION_PACKET*)(piVar6 + 1);

			if (iVar11 * iVar11 + iVar1 * iVar1 < sphere_sq)
			{
				box_loop = 0;

				while (box_loop < num_cb)
				{
					iVar10 = collide->zsize * 0x800 + radius * 0x1000;
					iVar9 = collide->xsize * 0x800 + radius * 0x1000;
					uVar4 = (pCellObject->yang + collide->yang) * 0x100 & 0x3f00;
					iVar7 = pPosition->vy + ((int)(((uint) * (ushort*)&(pCellObject->pos).vy + (uint)(ushort)collide->ypos) * 0x10000) >> 0x10) + 0x50;

					if (iVar7 < 0)
						iVar7 = -iVar7;

					iVar8 = (int)*(short*)((int)rcossin_tbl + uVar4 + 2);
					iVar5 = (int)*(short*)((int)rcossin_tbl + uVar4);
					iVar2 = (uint)(ushort)collide->ysize << 0x10;

					if (((iVar7 < ((iVar2 >> 0x10) - (iVar2 >> 0x1f) >> 1) + 0x3c) &&
						((uint)((iVar11 * iVar8 - iVar1 * iVar5) + iVar9) < (uint)(iVar9 * 2))) &&
						((uint)(iVar1 * iVar8 + iVar11 * iVar5 + iVar10) < (uint)(iVar10 * 2))) 
					{
						return 0;
					}

					box_loop++;
					collide++;
				}
			}
		}

		ppco = GetNextPackedCop(&ci);
		pCellObject = UnpackCellObject(ppco, &ci.nearCell);

	} while (true);

	return 0;
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

// [D]
int GlobalPositionToCellNumber(VECTOR *pPosition)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint uVar4;
	uint uVar5;
	int iVar6;

	iVar1 = pPosition->vx + units_across_halved;
	iVar3 = iVar1 - 1024;

	iVar1 = pPosition->vz + units_down_halved;
	iVar2 = iVar1 - 1024;
	iVar3 = iVar3 >> 0xb;

	iVar2 = iVar2 >> 0xb;
	iVar1 = iVar3;

	uVar5 = iVar1 >> 5;
	iVar1 = iVar2;

	uVar4 = iVar1 >> 5;
	iVar6 = (uVar5 & 1) + (uVar4 & 1) * 2;

	if (RoadMapRegions[iVar6] != uVar5 + uVar4 * (cells_across >> 5))
		return -1;

	return cell_ptrs[(iVar2 - uVar4 * 32) * 32 + iVar6 * 1024 + iVar3 - uVar5 * 32];
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
	int dir;
	int iVar3;
	int local_t0_36;
	int i;

	tRange inside;
	tRange cabbage;
	tRange scaledCabbage;

	inside.lower = 0;
	inside.upper = 4096;

	i = 0;
	do {
		local_t0_36 = -1;

		cabbage.lower = bbox->slab[i].lower - ray->org[i];
		cabbage.upper = bbox->slab[i].upper - ray->org[i];

		dir = ray->dir[i];

		if (dir > -1) 
			local_t0_36 = (dir != 0);

		if (local_t0_36 == 0) 
		{
			if (cabbage.lower > 0)
				return 0;

			if (cabbage.upper < 0)
				return 0;

			scaledCabbage.upper = 0x3000;
			scaledCabbage.lower = -0x3000;
		}
		else if (local_t0_36 == -1)
		{
			scaledCabbage.upper = (cabbage.lower * 4096) / dir;
			scaledCabbage.lower = (cabbage.upper * 4096) / dir;
		}
		else if (local_t0_36 == 1)
		{
			scaledCabbage.lower = (cabbage.lower * 4096) / dir;
			scaledCabbage.upper = (cabbage.upper * 4096) / dir;
		}

		if (inside.lower < scaledCabbage.lower)
			inside.lower = scaledCabbage.lower;

		if (scaledCabbage.upper < inside.upper)
			inside.upper = scaledCabbage.upper;

		if (inside.upper < inside.lower)
			return 0;

		i++;

	} while(i < 3);

	return 1;
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

int testRadius = 222;

// [D]
char lineClear(VECTOR *v1, VECTOR *v2)
{
	PACKED_CELL_OBJECT* ppco;
	CELL_OBJECT* pCellObject;
	MATRIX2* mat;
	int pos_z;
	int cell_z;
	int cell_x;
	int local_a0_592;
	MODEL* pModel;
	int* piVar2;
	int local_a3_704;
	int iVar3;
	int cs;
	int sn;
	int iVar4;
	COLLISION_PACKET* collide;
	VECTOR pos;
	VECTOR va;
	VECTOR vb;
	CELL_ITERATOR ci;
	tRay ray;
	tAABB box;
	int we;
	int ocz;
	int ocx;
	int box_loop; // $s5
	int num_cb; // $s6
 	int sphere_sq; // $v0
 	int xd; // $a0
 	int zd; // $v1

	va.vx = v1->vx;
	va.vy = v1->vy;
	va.vz = v1->vz;

	vb.vx = v2->vx;
	vb.vy = v2->vy;
	vb.vz = v2->vz;

	pos.vx = vb.vx - va.vx;
	pos.vz = vb.vz - va.vz;

	ocx = -1;
	ocz = -1;

	we = 0;

	do {
		if (we == 0) 
		{
			cell_x = (v2->vx + units_across_halved) / 2048;
			cell_z = (v2->vz + units_down_halved) / 2048;
		}
		else 
		{
			cell_x = (v1->vx + units_across_halved) / 2048;
			cell_z = (v1->vz + units_down_halved) / 2048;
		}

		if ((ocx != cell_x) || (ocz != cell_z))
		{
			ppco = GetFirstPackedCop(cell_x, cell_z, &ci, 0);

			while (pCellObject = UnpackCellObject(ppco, &ci.nearCell), pCellObject != NULL)
			{
				pModel = modelpointers[pCellObject->type];
				piVar2 = (int*)pModel->collision_block;

				xd = ((pCellObject->pos.vx - ((va.vx + vb.vx) / 2 & 0xffffU)) * 0x10000) >> 0x10;
				zd = ((pCellObject->pos.vz - ((va.vz + vb.vz) / 2 & 0xffffU)) * 0x10000) >> 0x10;

				sphere_sq = pModel->bounding_sphere + 800;

				if (piVar2 != NULL && (pModel->flags2 & 0xA00) == 0 && (xd*xd + zd*zd < sphere_sq*sphere_sq))
				{
					collide = (COLLISION_PACKET*)(piVar2 + 1);

					num_cb = *piVar2;
					box_loop = 0;

					while (box_loop < num_cb)
					{
						local_a0_592 = -pCellObject->yang & 0x3f;
						local_a3_704 = (pCellObject->yang + collide->yang) * 64 & 0xfff;

						mat = &matrixtable[local_a0_592];

						cs = rcossin_tbl[local_a3_704 * 2 + 1];
						sn = rcossin_tbl[local_a3_704 * 2];

						iVar4 = va.vx - (pCellObject->pos.vx + FIXED(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]));
						iVar3 = va.vz - (pCellObject->pos.vz + FIXED(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]));
						
						box.slab[0].upper = collide->xsize / 2 +testRadius;
						box.slab[0].lower = -box.slab[0].upper;
					
						box.slab[1].upper = collide->ysize / 2 +testRadius;
						box.slab[1].lower = -box.slab[1].upper;
						
						box.slab[2].upper = collide->zsize / 2 +testRadius;
						box.slab[2].lower = -box.slab[2].upper;

						ray.org[0] = FIXED(cs * iVar4 - sn * iVar3);
						ray.org[2] = FIXED(cs * iVar3 + sn * iVar4);
						ray.org[1] = (va.vy - (((-collide->ypos - pCellObject->pos.vy) * 0x10000) >> 0x10)) + 80;

						ray.dir[0] = FIXED(cs * pos.vx - sn * pos.vz);
						ray.dir[2] = FIXED(cs * pos.vz + sn * pos.vx);
						ray.dir[1] = vb.vy - va.vy;

#if defined(COLLISION_DEBUG)
						int rayResult = RaySlabsIntersection(&ray, &box);

						extern int gShowCollisionDebug;
						if (gShowCollisionDebug == 3)
						{
							CDATA2D cd[1];

							cd[0].x.vx = (pCellObject->pos.vx + FIXED(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]));
							cd[0].x.vz = (pCellObject->pos.vz + FIXED(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]));
							cd[0].x.vy = va.vy;

							cd[0].theta = (pCellObject->yang + collide->yang) * 64 & 0xfff;
							cd[0].length[0] = collide->zsize / 2;
							cd[0].length[1] = collide->xsize / 2;

							// calc axes of box
							int dtheta = cd[0].theta & 0xfff;

							cd[0].axis[0].vx = rcossin_tbl[dtheta * 2];
							cd[0].axis[0].vz = rcossin_tbl[dtheta * 2 + 1];

							cd[0].axis[1].vz = -rcossin_tbl[dtheta * 2];
							cd[0].axis[1].vx = rcossin_tbl[dtheta * 2 + 1];

							extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
							extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

							CVECTOR ggcv = { 0, 250, 0 };
							CVECTOR rrcv = { 250, 0, 0 };
							CVECTOR yycv = { 250, 250, 0 };

							// show both box axes
							{
								VECTOR _zero = { 0 };
								VECTOR b1p = cd[0].x;

								// show position to position
								//Debug_AddLine(b1p1, b2p1, yycv);

								VECTOR b1ax[2] = { {0} , {0} };
								b1ax[0].vx = FIXED(cd[0].axis[0].vx * cd[0].length[0]);
								b1ax[0].vz = FIXED(cd[0].axis[0].vz * cd[0].length[0]);
								b1ax[1].vx = FIXED(cd[0].axis[1].vx * cd[0].length[1]);
								b1ax[1].vz = FIXED(cd[0].axis[1].vz * cd[0].length[1]);

								// show axis of body 1
								Debug_AddLineOfs(_zero, b1ax[0], b1p, rrcv);
								Debug_AddLineOfs(_zero, b1ax[1], b1p, yycv);

								// display 2D box 1
								{
									int h = b1ax[0].vy;
									VECTOR box_points[4] = {
										{b1ax[0].vx - b1ax[1].vx, h, b1ax[0].vz - b1ax[1].vz, 0},	// front left
										{b1ax[0].vx + b1ax[1].vx, h, b1ax[0].vz + b1ax[1].vz, 0},	// front right

										{-b1ax[0].vx + b1ax[1].vx, h, -b1ax[0].vz + b1ax[1].vz, 0},	// back right
										{-b1ax[0].vx - b1ax[1].vx, h, -b1ax[0].vz - b1ax[1].vz, 0}	// back left
									};

									Debug_AddLineOfs(box_points[0], box_points[1], b1p, rayResult ? rrcv : ggcv);
									Debug_AddLineOfs(box_points[1], box_points[2], b1p, rayResult ? rrcv : ggcv);
									Debug_AddLineOfs(box_points[2], box_points[3], b1p, rayResult ? rrcv : ggcv);
									Debug_AddLineOfs(box_points[3], box_points[0], b1p, rayResult ? rrcv : ggcv);
								}
							}
						}

						if (rayResult != 0)
							return 0;

#else
						if (RaySlabsIntersection(&ray, &box) != 0)
							return 0;
#endif
						box_loop++;
						collide++;
					}
				}
				ppco = GetNextPackedCop(&ci);
			}
		}

		we++;

		ocx = cell_x;
		ocz = cell_z;
	} while (we < 2);

	return 1;
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
					cop = UnpackCellObject(ppco, &ci.nearCell);

					while (cop != NULL)
					{
						coplist[*count] = cop;
						cop->pad = *(unsigned char *)count;
						pcoplist[*count] = ci.ppco;

						ppco = GetNextPackedCop(&ci);
						cop = UnpackCellObject(ppco, &ci.nearCell);

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
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int uVar9;
	int iVar10;
	int *piVar11;
	int iVar12;
	int iVar13;
	COLLISION_PACKET *collide;
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

				model = modelpointers[cop->type];
				iVar3 = x1 + 1;

				if (model->collision_block > 0 &&
					model->num_vertices-3 < 300 && 
					model->num_point_normals < 300 &&
					model->num_polys < 300)
				{
					iVar8 = cop->pos.vx - iVar10;
					iVar7 = cop->pos.vz - iVar12;
					iVar6 = model->bounding_sphere + extraDist + cp->hd.speed;

					if (iVar8 * iVar8 + iVar7 * iVar7 < iVar6 * iVar6)
					{
						iVar6 = *(int *)model->collision_block;	// box count
						collide = (COLLISION_PACKET*)(model->collision_block + 4);

						for (int i = 0; i < iVar6; i++)
						{
							uVar9 = -cop->yang & 0x3f;

							// box 'rotated' by matrix
							// [A] FIXME: replace add+shift by division
							bbox.pos.vx = cop->pos.vx + FIXED(collide->xpos * matrixtable[uVar9].m[0][0] + collide->zpos * matrixtable[uVar9].m[2][0]);
							bbox.pos.vy = cop->pos.vy + collide->ypos;
							bbox.pos.vz = cop->pos.vz + FIXED(collide->xpos * matrixtable[uVar9].m[0][2] + collide->zpos * matrixtable[uVar9].m[2][2]);

							bbox.pos.pad = (model->flags2 >> 10) & 1;

							//iVar7 = collide->zsize << 0x10;
							bbox.xsize = collide->zsize / 2; // (iVar7 >> 0x10) - (iVar7 >> 0x1f) >> 1;

							//iVar7 = collide->xsize << 0x10;
							bbox.zsize = collide->xsize / 2;// //;(iVar7 >> 0x10) - (iVar7 >> 0x1f) >> 1;

							bbox.height = collide->ysize;
							bbox.theta = (cop->yang + collide->yang) * 64 & 0xfff;

							gLastModelCollisionCheck = cop->type;

							if (CAR_INDEX(cp) == 21)
							{
								if (x1 < mdcount || (cop->pad == 0))
								{
									CarBuildingCollision(cp, &bbox, cop, 0);
								}
								else
								{
									if (CarBuildingCollision(cp, &bbox, cop, 0) != 0)
									{
										if (!bKillTanner)
											player[0].dying = 1;

										bKillTanner = 1;
									}
								}
							}
							else if (cp->controlType == 5)
							{
								if ((model->flags2 & 0xa00) == 0 && (100 < bbox.xsize || (100 < bbox.zsize)))
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
									if (CarBuildingCollision(cp, &bbox, cop, (model->flags2 >> 10) & 1) != 0)
										cp->ap.needsDenting = 1;
								}
								else
								{
									cp->st.n.linearVelocity[2] = ExBoxDamage + cp->st.n.linearVelocity[2];
									
									if (CarBuildingCollision(cp, &bbox, cop, (cop->pad == 1) ? 0x2 : 0) != 0)
									{
										cp->ap.needsDenting = 1;
									}

									//cp->st.n.linearVelocity[2] -= 700000; // [A] Vegas train velocity - disabled here
								}
							}

							collide++;
						};
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

// [D]
int QuickBuildingCollisionCheck(VECTOR *pPos, int dir, int l, int w, int extra)
{
	CDATA2D cd[2] = { 0 };
	bool bVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	MODEL *model;
	uint uVar9;
	int iVar10;
	int *piVar11;
	int iVar12;
	int iVar13;
	COLLISION_PACKET *collide;
	CELL_OBJECT *cop;
	VECTOR player_pos;
	BUILDING_BOX bbox;
	VECTOR offset;
	int mdcount;

	iVar5 = pPos->vx;
	boxOverlap = -1;
	iVar12 = pPos->vz;
	iVar13 = iVar5 + units_across_halved;
	iVar4 = iVar13 - 0x400;
	iVar13 = iVar12 + units_down_halved;
	iVar7 = iVar13 - 0x400;

	SetCopListCell(iVar4 / 2048, iVar7 / 2048);
	mdcount = 0;

	Havana3DOcclusion(BuildCollisionCopList, &mdcount);
	iVar4 = 0;

	if (0 < mdcount + event_models_active)
	{
		bVar1 = 0 < mdcount;
		do {
			if (bVar1)
				cop = coplist[iVar4];
			else
				cop = EventCop + (iVar4 - mdcount);

			model = modelpointers[cop->type];

			if (model->collision_block > 0 &&
				model->num_vertices - 3 < 300 && 
				model->num_point_normals < 300 && 
				model->num_polys < 300)
			{
				piVar11 = (int *)model->collision_block;

				iVar13 = model->bounding_sphere + extra;
				iVar7 = cop->pos.vx - iVar5;
				iVar6 = cop->pos.vz - iVar12;

				if (iVar7 * iVar7 + iVar6 * iVar6 < iVar13 * iVar13)
				{
					iVar7 = *(int *)model->collision_block;
					collide = (COLLISION_PACKET*)(model->collision_block + 4);

					for (int i = 0; i < iVar7; i++)
					{
						uVar9 = -cop->yang & 0x3f;
						bbox.pos.vy = cop->pos.vy + collide->ypos;
						iVar2 = collide->zsize;
						iVar3 = collide->xsize;
						iVar10 = collide->ysize;
						iVar6 = pPos->vy + bbox.pos.vy;

						if (iVar6 < 0)
							iVar6 = -iVar6;

						if (iVar6 < (iVar10) / 2)
						{
							gLastModelCollisionCheck = cop->type;

							cd[0].theta = dir;
							cd[0].length[0] = l;
							cd[0].length[1] = w;

							cd[0].x.vx = pPos->vx;
							cd[0].x.vz = pPos->vz;

							cd[0].vel.vx = 0;
							cd[0].vel.vz = 0;

							offset.vx = cop->pos.vx + FIXED(collide->xpos * matrixtable[uVar9].m[0][0] + collide->zpos * matrixtable[uVar9].m[2][0]);
							offset.vz = cop->pos.vz + FIXED(collide->xpos * matrixtable[uVar9].m[0][2] + collide->zpos * matrixtable[uVar9].m[2][2]);

							cd[1].theta = (cop->yang + collide->yang) * 64 & 0xfff;

							cd[1].length[0] = collide->zsize / 2 + 100;
							cd[1].length[1] = collide->xsize / 2 + 100;

							cd[1].x.vx = pPos->vx + (((offset.vx - pPos->vx) << 0x10) >> 0x10);
							cd[1].x.vz = pPos->vz + (((offset.vz - pPos->vz) << 0x10) >> 0x10);

							cd[1].vel.vx = 0;
							cd[1].vel.vz = 0;
							cd[1].avel = 0;

							int res = bcollided2d(cd, 1);
							
#if defined(COLLISION_DEBUG) && !defined(PSX)
							extern int gShowCollisionDebug;
							if (gShowCollisionDebug == 1)
							{
								extern void Debug_AddLine(VECTOR& pointA, VECTOR& pointB, CVECTOR& color);
								extern void Debug_AddLineOfs(VECTOR& pointA, VECTOR& pointB, VECTOR& ofs, CVECTOR& color);

								CVECTOR bbcv = { 0, 0, 250 };
								CVECTOR rrcv = { 250, 0, 0 };
								CVECTOR yycv = { 250, 250, 0 };

								// show both box axes
								{
									VECTOR _zero = { 0 };
									VECTOR b1p = cd[0].x;
									VECTOR b2p = cd[1].x;
									b2p.vy = b1p.vy;

									// show position to position
									//Debug_AddLine(b1p1, b2p1, yycv);

									VECTOR b1ax[2] = { {0} , {0} };
									b1ax[0].vx = FIXED(cd[0].axis[0].vx * cd[0].length[0]);
									b1ax[0].vz = FIXED(cd[0].axis[0].vz * cd[0].length[0]);
									b1ax[1].vx = FIXED(cd[0].axis[1].vx * cd[0].length[1]);
									b1ax[1].vz = FIXED(cd[0].axis[1].vz * cd[0].length[1]);

									// show axis of body 1
									Debug_AddLineOfs(_zero, b1ax[0], b1p, rrcv);
									Debug_AddLineOfs(_zero, b1ax[1], b1p, yycv);

									// display 2D box 1
									{
										int h = b1ax[0].vy;
										VECTOR box_points[4] = {
											{b1ax[0].vx - b1ax[1].vx, h, b1ax[0].vz - b1ax[1].vz, 0},	// front left
											{b1ax[0].vx + b1ax[1].vx, h, b1ax[0].vz + b1ax[1].vz, 0},	// front right

											{-b1ax[0].vx + b1ax[1].vx, h, -b1ax[0].vz + b1ax[1].vz, 0},	// back right
											{-b1ax[0].vx - b1ax[1].vx, h, -b1ax[0].vz - b1ax[1].vz, 0}	// back left
										};

										Debug_AddLineOfs(box_points[0], box_points[1], b1p, bbcv);
										Debug_AddLineOfs(box_points[1], box_points[2], b1p, bbcv);
										Debug_AddLineOfs(box_points[2], box_points[3], b1p, bbcv);
										Debug_AddLineOfs(box_points[3], box_points[0], b1p, bbcv);
									}

									VECTOR b2ax[2] = { {0} , {0} };
									b2ax[0].vx += FIXED(cd[1].axis[0].vx * cd[1].length[0]);
									b2ax[0].vz += FIXED(cd[1].axis[0].vz * cd[1].length[0]);
									b2ax[1].vx += FIXED(cd[1].axis[1].vx * cd[1].length[1]);
									b2ax[1].vz += FIXED(cd[1].axis[1].vz * cd[1].length[1]);

									// show axis of body 2
									Debug_AddLineOfs(_zero, b2ax[0], b2p, rrcv);
									Debug_AddLineOfs(_zero, b2ax[1], b2p, yycv);

									CVECTOR& collColor = res ? rrcv : yycv;

									// display 2D box 2
									{
										int h = b2ax[0].vy;
										VECTOR box_points[4] = {
											{b2ax[0].vx - b2ax[1].vx, h, b2ax[0].vz - b2ax[1].vz, 0},	// front left
											{b2ax[0].vx + b2ax[1].vx, h, b2ax[0].vz + b2ax[1].vz, 0},	// front right

											{-b2ax[0].vx + b2ax[1].vx, h, -b2ax[0].vz + b2ax[1].vz, 0},	// back right
											{-b2ax[0].vx - b2ax[1].vx, h, -b2ax[0].vz - b2ax[1].vz, 0}	// back left
										};

										Debug_AddLineOfs(box_points[0], box_points[1], b2p, collColor);
										Debug_AddLineOfs(box_points[1], box_points[2], b2p, collColor);
										Debug_AddLineOfs(box_points[2], box_points[3], b2p, collColor);
										Debug_AddLineOfs(box_points[3], box_points[0], b2p, collColor);
									}
								}
							}
#endif
							if(res)
								return 1;
						}

						collide++;

					}
				}
			}

			iVar4++;
			bVar1 = iVar4 < mdcount;
		} while (iVar4 < mdcount + event_models_active);
	}
	return 0;
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





