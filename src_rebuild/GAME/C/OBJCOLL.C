#include "DRIVER2.H"
#include "OBJCOLL.H"
#include "CARS.H"
#include "CAMERA.H"
#include "BCOLLIDE.H"
#include "EVENT.H"
#include "MAP.H"
#include "DRAW.H"
#include "HANDLING.H"
#include "MODELS.H"
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

// [D] [T]
char CellEmpty(VECTOR *pPosition, int radius)
{
	PACKED_CELL_OBJECT* ppco;
	CELL_OBJECT* pCellObject;
	MODEL* pModel;
	int num_cb;
	int box_loop;
	int sphere_sq;
	int zd;
	int sn;
	int ypos;
	int cs;
	COLLISION_PACKET* collide;
	int xs;
	int zs;
	int xd;
	int cell_x, cell_z;
	CELL_ITERATOR ci;

	cell_x = (pPosition->vx + units_across_halved) / MAP_CELL_SIZE;
	cell_z = (pPosition->vz + units_down_halved) / MAP_CELL_SIZE;

	ppco = GetFirstPackedCop(cell_x, cell_z, &ci, 0);
	pCellObject = UnpackCellObject(ppco, &ci.nearCell);

	while(pCellObject)
	{
		pModel = modelpointers[pCellObject->type];

		if (pModel->collision_block > 0 && (pModel->flags2 & 0xA00) == 0)
		{
			num_cb = *(int*)pModel->collision_block;

			xd = (pCellObject->pos.vx - pPosition->vx);
			zd = (pCellObject->pos.vz - pPosition->vz);

			sphere_sq = pModel->bounding_sphere + 580;
			sphere_sq = (sphere_sq * sphere_sq);

			collide = (COLLISION_PACKET*)(pModel->collision_block + sizeof(int));

			if (xd * xd + zd * zd < sphere_sq)
			{
				box_loop = 0;

				while (box_loop < num_cb)
				{
					// [A] ORIGINAL
					/*
					zs = collide->zsize * 0x800 + radius * 0x1000;
					xs = collide->xsize * 0x800 + radius * 0x1000;

					theta = (pCellObject->yang + collide->yang) * 64 & 0xfff;
					ypos = pPosition->vy + (pCellObject->pos.vy + collide->ypos) + 80;

					cs = rcossin_tbl[theta * 2 + 1];
					sn = rcossin_tbl[theta * 2];
					*/

					// [A] NEW
					int xxd, zzd;
					int yang;
					int theta;
					MATRIX2* mat;

					yang = -pCellObject->yang & 0x3f;
					theta = (pCellObject->yang + collide->yang) * 64 & 0xfff;

					mat = &matrixtable[yang];

					cs = rcossin_tbl[theta * 2 + 1];
					sn = rcossin_tbl[theta * 2];

					xxd = FIXEDH(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]);
					zzd = FIXEDH(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]);

					xd = (pCellObject->pos.vx - pPosition->vx) + xxd;
					zd = (pCellObject->pos.vz - pPosition->vz) + zzd;

					zs = ((collide->zsize + 10) * 2048 + radius * 4096);
					xs = ((collide->xsize + 10) * 2048 + radius * 4096);

					ypos = pPosition->vy + (pCellObject->pos.vy + collide->ypos) + 80;
					
#ifdef COLLISION_DEBUG
					int result = 0;

					if (collide->ysize / 2 + 60 > ABS(ypos) &&
						xs * 2 > ABS(xd * cs - zd * sn) + xs &&
						zs * 2 > ABS(zd * cs + xd * sn) + zs)
					{
						result = 1;
					}

					extern int gShowCollisionDebug;
					if (gShowCollisionDebug == 3)
					{
						CDATA2D cd[1];

						cd[0].x.vx = (pCellObject->pos.vx + xxd);//FIXEDH(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]));
						cd[0].x.vz = (pCellObject->pos.vz + zzd);//FIXEDH(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]));
						cd[0].x.vy = pPosition->vy;

						cd[0].theta = theta; // (pCellObject->yang + collide->yang) * 64 & 0xfff;
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
							b1ax[0].vx = FIXEDH(cd[0].axis[0].vx * cd[0].length[0]);
							b1ax[0].vz = FIXEDH(cd[0].axis[0].vz * cd[0].length[0]);
							b1ax[1].vx = FIXEDH(cd[0].axis[1].vx * cd[0].length[1]);
							b1ax[1].vz = FIXEDH(cd[0].axis[1].vz * cd[0].length[1]);

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

								Debug_AddLineOfs(box_points[0], box_points[1], b1p, result ? rrcv : ggcv);
								Debug_AddLineOfs(box_points[1], box_points[2], b1p, result ? rrcv : ggcv);
								Debug_AddLineOfs(box_points[2], box_points[3], b1p, result ? rrcv : ggcv);
								Debug_AddLineOfs(box_points[3], box_points[0], b1p, result ? rrcv : ggcv);
							}
						}
					}

					if (result)
						return 0;
#else
					if (collide->ysize / 2 + 60 > ABS(ypos) &&
						xs * 2 > ABS(xd * cs - zd * sn) + xs &&
						zs * 2 > ABS(zd * cs + xd * sn) + zs)
					{
						return 0;
					}
#endif

					box_loop++;
					collide++;
				}
			}
		}

		ppco = GetNextPackedCop(&ci);
		pCellObject = UnpackCellObject(ppco, &ci.nearCell);
	}

	return 1;
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

// [D] [T]
int GlobalPositionToCellNumber(VECTOR *pPosition)
{
	int cellZ;
	int cellX;
	int cbrZ;
	int cbrX;
	int cbr;

	cellX = (pPosition->vx + units_across_halved - (MAP_CELL_SIZE / 2)) / MAP_CELL_SIZE;
	cellZ = (pPosition->vz + units_down_halved - (MAP_CELL_SIZE / 2)) / MAP_CELL_SIZE;
	
	cbrX = cellX / MAP_REGION_SIZE;
	cbrZ = cellZ / MAP_REGION_SIZE;

	cbr = (cbrX & 1) + (cbrZ & 1) * 2;

	if (RoadMapRegions[cbr] != cbrX + cbrZ * (cells_across / MAP_REGION_SIZE))
		return -1;

	return cell_ptrs[(cellZ - cbrZ * MAP_REGION_SIZE) * MAP_REGION_SIZE + cbr * (MAP_CELL_SIZE / 2) + cellX - cbrX * MAP_REGION_SIZE];
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

// [D] [T]
char CellAtPositionEmpty(VECTOR *pPosition, int radius)
{
	if (GlobalPositionToCellNumber(pPosition) == -1)
		return 1;

	return CellEmpty(pPosition, radius);
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

// [D] [T]
int RaySlabsIntersection(tRay *ray, tAABB *bbox)
{
	int dir;
	int d;
	int i;

	tRange inside;
	tRange cabbage;
	tRange scaledCabbage;

	inside.lower = 0;
	inside.upper = 4096;

	i = 0;
	do {
		d = -1;

		cabbage.lower = bbox->slab[i].lower - ray->org[i];
		cabbage.upper = bbox->slab[i].upper - ray->org[i];

		dir = ray->dir[i];

		if (dir > -1) 
			d = (dir != 0);

		if (d == 0) 
		{
			if (cabbage.lower > 0)
				return 0;

			if (cabbage.upper < 0)
				return 0;

			scaledCabbage.upper = 0x3000;
			scaledCabbage.lower = -0x3000;
		}
		else if (d == -1)
		{
			scaledCabbage.upper = (cabbage.lower * 4096) / dir;
			scaledCabbage.lower = (cabbage.upper * 4096) / dir;
		}
		else if (d == 1)
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

// [D] [T]
char lineClear(VECTOR *v1, VECTOR *v2)
{
	PACKED_CELL_OBJECT* ppco;
	CELL_OBJECT* pCellObject;
	MATRIX2* mat;
	int cell_z;
	int cell_x;
	int yang;
	MODEL* pModel;
	int theta;
	
	int dx,dz;

	int cs;
	int sn;

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
			cell_x = (v2->vx + units_across_halved) / MAP_CELL_SIZE;
			cell_z = (v2->vz + units_down_halved) / MAP_CELL_SIZE;
		}
		else 
		{
			cell_x = (v1->vx + units_across_halved) / MAP_CELL_SIZE;
			cell_z = (v1->vz + units_down_halved) / MAP_CELL_SIZE;
		}

		if ((ocx != cell_x) || (ocz != cell_z))
		{
			ppco = GetFirstPackedCop(cell_x, cell_z, &ci, 0);

			while (pCellObject = UnpackCellObject(ppco, &ci.nearCell), pCellObject != NULL)
			{
				pModel = modelpointers[pCellObject->type];

				xd = ((pCellObject->pos.vx - ((va.vx + vb.vx) / 2 & 0xffffU)) * 0x10000) >> 0x10;
				zd = ((pCellObject->pos.vz - ((va.vz + vb.vz) / 2 & 0xffffU)) * 0x10000) >> 0x10;

				sphere_sq = pModel->bounding_sphere + 800;

				if (pModel->collision_block > 0 && (pModel->flags2 & 0xA00) == 0 && (xd*xd + zd*zd < sphere_sq*sphere_sq))
				{
					num_cb = *(int*)pModel->collision_block;
					box_loop = 0;

					collide = (COLLISION_PACKET*)(pModel->collision_block + sizeof(int));

					while (box_loop < num_cb)
					{
						yang = -pCellObject->yang & 0x3f;
						theta = (pCellObject->yang + collide->yang) * 64 & 0xfff;

						mat = &matrixtable[yang];

						cs = rcossin_tbl[theta * 2 + 1];
						sn = rcossin_tbl[theta * 2];

						dx = va.vx - (pCellObject->pos.vx + FIXEDH(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]));
						dz = va.vz - (pCellObject->pos.vz + FIXEDH(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]));
						
						box.slab[0].upper = collide->xsize / 2 +testRadius;
						box.slab[0].lower = -box.slab[0].upper;
					
						box.slab[1].upper = collide->ysize / 2 +testRadius;
						box.slab[1].lower = -box.slab[1].upper;
						
						box.slab[2].upper = collide->zsize / 2 +testRadius;
						box.slab[2].lower = -box.slab[2].upper;

						ray.org[0] = FIXEDH(cs * dx - sn * dz);
						ray.org[2] = FIXEDH(cs * dz + sn * dx);
						ray.org[1] = (va.vy - (((-collide->ypos - pCellObject->pos.vy) * 0x10000) >> 0x10)) + 80;

						ray.dir[0] = FIXEDH(cs * pos.vx - sn * pos.vz);
						ray.dir[2] = FIXEDH(cs * pos.vz + sn * pos.vx);
						ray.dir[1] = vb.vy - va.vy;

#if defined(COLLISION_DEBUG)
						int rayResult = RaySlabsIntersection(&ray, &box);

						extern int gShowCollisionDebug;
						if (gShowCollisionDebug == 3)
						{
							CDATA2D cd[1];

							cd[0].x.vx = (pCellObject->pos.vx + FIXEDH(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]));
							cd[0].x.vz = (pCellObject->pos.vz + FIXEDH(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]));
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
								b1ax[0].vx = FIXEDH(cd[0].axis[0].vx * cd[0].length[0]);
								b1ax[0].vz = FIXEDH(cd[0].axis[0].vz * cd[0].length[0]);
								b1ax[1].vx = FIXEDH(cd[0].axis[1].vx * cd[0].length[1]);
								b1ax[1].vz = FIXEDH(cd[0].axis[1].vz * cd[0].length[1]);

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

// [D] [T]
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

// [D] [T]
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

// [D] [T]
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
	MODEL* model;

	if (pos == NULL)
	{
		i = 0;
		cell.x = initial.x;

		do {
			j = 0;

			cell.z = initial.z;

			do {
				cbr.x = cell.x / MAP_REGION_SIZE;
				cbr.z = cell.z / MAP_REGION_SIZE;
				
				// [A] FIXME: replace with 'cell_header.region_size'
				if (cbr.x + cbr.z * (cells_across / MAP_REGION_SIZE) == RoadMapRegions[(cbr.x & 1) + (cbr.z & 1) * 2])
				{
					ppco = GetFirstPackedCop(cell.x, cell.z, &ci, 1);
					cop = UnpackCellObject(ppco, &ci.nearCell);

					while (cop != NULL)
					{
						cop->pad = *count;

						model = modelpointers[cop->type];
						
						if (model->collision_block > 0 &&
							model->num_vertices-3 < 300 && 
							model->num_point_normals < 300 &&
							model->num_polys < 300 &&
							*(int *)model->collision_block > 0)
						{
							coplist[*count] = cop;
							pcoplist[*count] = ci.ppco;
							(*count)++;
						}

						ppco = GetNextPackedCop(&ci);
						cop = UnpackCellObject(ppco, &ci.nearCell);
					}
				}

				cell.z++;
				j++;
			} while (j < 2);

			cell.x++;
			i++;
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

// [D] [T]
void CheckScenaryCollisions(_CAR_DATA *cp)
{
	int count;
	int num_cb;
	int coll_test_count;
	int yang;
	int minDist;
	COLLISION_PACKET *collide;
	CELL_OBJECT *cop;
	VECTOR player_pos;
	BUILDING_BOX bbox;
	XZPAIR cell;
	int mdcount;
	MODEL *model;
	int lbody;
	int extraDist;
	int sphereSq;
	int dx, dz;
	
	if (cp->controlType == CONTROL_TYPE_CAMERACOLLIDER || cp->ap.carCos == NULL)
		lbody = 360;
	else
		lbody = cp->ap.carCos->colBox.vz;

	if (cp < car_data)
	{
		while (FrameCnt != 0x78654321)
			trap(0x400);
	}

	if (ghost_mode != 0 || cp->controlType == CONTROL_TYPE_PLAYER && playerghost != 0)
		return;

	EventCollisions(cp, 0);

	player_pos.vx = cp->hd.where.t[0];
	player_pos.vz = cp->hd.where.t[2];

	boxOverlap = -1;

	if (cp->controlType == CONTROL_TYPE_TANNERCOLLIDER)
		extraDist = 100;
	else
		extraDist = 580;

	// [A] FIXME: replace with 'cell_header.cell_size'
	cell.x = (player_pos.vx + units_across_halved - (MAP_CELL_SIZE / 2)) / MAP_CELL_SIZE;
	cell.z = (player_pos.vz + units_down_halved - (MAP_CELL_SIZE / 2)) / MAP_CELL_SIZE;

	SetCopListCell(cell.x, cell.z);

	mdcount = 0;
	Havana3DOcclusion(BuildCollisionCopList, &mdcount);
		
	count = 0;
	while (count < mdcount + event_models_active)
	{
		if (count < mdcount)
			cop = coplist[count];
		else
			cop = &EventCop[count - mdcount];

		model = modelpointers[cop->type];

		if (model->collision_block > 0 &&
			model->num_vertices-3 < 300 && 
			model->num_point_normals < 300 &&
			model->num_polys < 300)
		{

			dx = cop->pos.vx - player_pos.vx;
			dz = cop->pos.vz - player_pos.vz;
					
			sphereSq = model->bounding_sphere + extraDist + cp->hd.speed;

			if (dx * dx + dz * dz < sphereSq * sphereSq)
			{
				num_cb = *(int *)model->collision_block;	// box count
				collide = (COLLISION_PACKET*)(model->collision_block + sizeof(int));

				while(num_cb--)
				{
					yang = -cop->yang & 0x3f;

					// box 'rotated' by matrix
					// [A] FIXME: replace add+shift by division
					bbox.pos.vx = cop->pos.vx + FIXEDH(collide->xpos * matrixtable[yang].m[0][0] + collide->zpos * matrixtable[yang].m[2][0]);
					bbox.pos.vy = cop->pos.vy + collide->ypos;
					bbox.pos.vz = cop->pos.vz + FIXEDH(collide->xpos * matrixtable[yang].m[0][2] + collide->zpos * matrixtable[yang].m[2][2]);

					bbox.pos.pad = (model->flags2 >> 10) & 1;

					bbox.xsize = (collide->zsize >> 1);
					bbox.zsize = (collide->xsize >> 1);

					bbox.height = collide->ysize;
					bbox.theta = (cop->yang + collide->yang) * 64 & 0xfff;

					gLastModelCollisionCheck = cop->type;

					if (CAR_INDEX(cp) == TANNER_COLLIDER_CARID)
					{
						if (count >= mdcount && cop->pad != 0)
						{
							if (CarBuildingCollision(cp, &bbox, cop, 0) != 0)
							{
								if (!bKillTanner)
									player[0].dying = 1;

								bKillTanner = 1;
							}
						}
						else
						{
							CarBuildingCollision(cp, &bbox, cop, 0);
						}
					}
					else if (cp->controlType == CONTROL_TYPE_CAMERACOLLIDER)
					{
						if ((model->flags2 & 0xa00) == 0 && (bbox.xsize > 100 || (bbox.zsize > 100)))
						{
							coll_test_count = 5;
							
							bbox.xsize += 100;
							bbox.zsize += 100;

							boxOverlap = -1;

							minDist = lbody / 2;
							
							while (coll_test_count > 0 && minDist <= gCameraDistance && CarBuildingCollision(cp, &bbox, cop, 0))
							{
								gCameraDistance -= boxOverlap;
										
								if (gCameraDistance < minDist)
									gCameraDistance = minDist;

								yang = cp->hd.direction & 0xfff;

								cp->hd.where.t[0] = car_data[0].hd.where.t[0] + FIXEDH((gCameraDistance * rcossin_tbl[yang * 2]) / 2);
								cp->hd.where.t[2] = car_data[0].hd.where.t[2] + FIXEDH((gCameraDistance * rcossin_tbl[yang * 2 + 1]) / 2);
								
								coll_test_count--;
							}
						}
					}
					else
					{
						if (count >= mdcount && cop->pad != 0)
						{
							cp->st.n.linearVelocity[2] = ExBoxDamage + cp->st.n.linearVelocity[2];
									
							if (CarBuildingCollision(cp, &bbox, cop, (cop->pad == 1) ? 0x2 : 0) != 0)
							{
								cp->ap.needsDenting = 1;
							}

							//cp->st.n.linearVelocity[2] -= 700000; // [A] Vegas train velocity - disabled here
						}
						else
						{
							if (CarBuildingCollision(cp, &bbox, cop, (model->flags2 >> 10) & 1) != 0)
								cp->ap.needsDenting = 1;
						}
					}

					collide++;
				}
			}
		}
		count++;
	}

	EventCollisions(cp, 1);
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

// [D] [T]
int QuickBuildingCollisionCheck(VECTOR *pPos, int dir, int l, int w, int extra)
{
	CDATA2D cd[2] = { 0 };
	int count;
	int num_cb;
	MODEL *model;
	uint yang;
	int sphereSq;
	COLLISION_PACKET *collide;
	CELL_OBJECT *cop;
	XZPAIR cell;
	VECTOR player_pos;
	BUILDING_BOX bbox;
	VECTOR offset;
	int mdcount;
	int dx, dz;

	boxOverlap = -1;

	player_pos.vx = pPos->vx;
	player_pos.vz = pPos->vz;

	cell.x = (player_pos.vx + units_across_halved - (MAP_CELL_SIZE / 2)) / MAP_CELL_SIZE;
	cell.z = (player_pos.vz + units_down_halved - (MAP_CELL_SIZE / 2)) / MAP_CELL_SIZE;
	
	SetCopListCell(cell.x, cell.z);
	mdcount = 0;

	Havana3DOcclusion(BuildCollisionCopList, &mdcount);

	count = 0;

	while (count < mdcount + event_models_active)
	{
		if (count < mdcount)
			cop = coplist[count];
		else
			cop = EventCop + (count - mdcount);

		count++;

		model = modelpointers[cop->type];

		if (model->collision_block > 0 &&
			model->num_vertices - 3 < 300 && 
			model->num_point_normals < 300 && 
			model->num_polys < 300)
		{
			sphereSq = model->bounding_sphere + extra;
			
			dx = cop->pos.vx - player_pos.vx;
			dz = cop->pos.vz - player_pos.vz;

			if (dx * dx + dz * dz < sphereSq * sphereSq)
			{
				num_cb = *(int *)model->collision_block;
				collide = (COLLISION_PACKET*)(model->collision_block + sizeof(int));

				while(num_cb--)
				{
					yang = -cop->yang & 0x3f;
					
					bbox.pos.vy = cop->pos.vy + collide->ypos;

					if (ABS(pPos->vy + bbox.pos.vy) < collide->ysize / 2)
					{
						gLastModelCollisionCheck = cop->type;

						cd[0].theta = dir;
						cd[0].length[0] = l;
						cd[0].length[1] = w;

						cd[0].x.vx = pPos->vx;
						cd[0].x.vz = pPos->vz;

						cd[0].vel.vx = 0;
						cd[0].vel.vz = 0;

						offset.vx = cop->pos.vx + FIXEDH(collide->xpos * matrixtable[yang].m[0][0] + collide->zpos * matrixtable[yang].m[2][0]);
						offset.vz = cop->pos.vz + FIXEDH(collide->xpos * matrixtable[yang].m[0][2] + collide->zpos * matrixtable[yang].m[2][2]);

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
								b1ax[0].vx = FIXEDH(cd[0].axis[0].vx * cd[0].length[0]);
								b1ax[0].vz = FIXEDH(cd[0].axis[0].vz * cd[0].length[0]);
								b1ax[1].vx = FIXEDH(cd[0].axis[1].vx * cd[0].length[1]);
								b1ax[1].vz = FIXEDH(cd[0].axis[1].vz * cd[0].length[1]);

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
								b2ax[0].vx += FIXEDH(cd[1].axis[0].vx * cd[1].length[0]);
								b2ax[0].vz += FIXEDH(cd[1].axis[0].vz * cd[1].length[0]);
								b2ax[1].vx += FIXEDH(cd[1].axis[1].vx * cd[1].length[1]);
								b2ax[1].vz += FIXEDH(cd[1].axis[1].vz * cd[1].length[1]);

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

// [D] [T]
void DoScenaryCollisions(void)
{
	_CAR_DATA *cp;

	cp = &car_data[MAX_CARS - 1];

	do {
		if (cp->controlType != CONTROL_TYPE_NONE)
		{
			// civ AI and dead cop cars perform less collision detection frames
			if (cp->controlType == CONTROL_TYPE_CIV_AI || 
				cp->controlType == CONTROL_TYPE_PURSUER_AI && cp->ai.p.dying > 85)
			{
				if (cp->totalDamage != 0 && (cp->hd.speed > 10 || (cp->id + CameraCnt & 3) == 0))
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





