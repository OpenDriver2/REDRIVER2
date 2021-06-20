#include "driver2.h"
#include "objcoll.h"
#include "cars.h"
#include "camera.h"
#include "bcollide.h"
#include "event.h"
#include "map.h"
#include "draw.h"
#include "handling.h"
#include "models.h"
#include "pedest.h"
#include "spool.h"
#include "cell.h"
#include "players.h"
#include "main.h"

// [D] [T]
char CellEmpty(VECTOR *pPosition, int radius)
{
	PACKED_CELL_OBJECT* ppco;
	CELL_OBJECT tempCO;
	MODEL* pModel;
	int num_cb;
	int box_loop;
	int sphere_sq;
	int xd, zd;
	int sn, cs;
	int xs, zs;
	int ypos;
	COLLISION_PACKET* collide;
	
	int cell_x, cell_z;
	int type;

#if 0
	CELL_ITERATOR& ci = *(CELL_ITERATOR*)((u_char*)getScratchAddr(0) + 1024 - sizeof(CELL_ITERATOR));
#else
	CELL_ITERATOR ci;
#endif

	cell_x = (pPosition->vx + units_across_halved) / MAP_CELL_SIZE;
	cell_z = (pPosition->vz + units_down_halved) / MAP_CELL_SIZE;

	ppco = GetFirstPackedCop(cell_x, cell_z, &ci, 0);

	while(ppco)
	{
		type = (ppco->value >> 6) | ((ppco->pos.vy & 1) << 10);
		pModel = modelpointers[type];

		if ((uint)pModel->collision_block > 0 && 
			(pModel->flags2 & (MODEL_FLAG_CHAIR | MODEL_FLAG_SMASHABLE)) == 0)
		{
			QuickUnpackCellObject(ppco, &ci.nearCell, &tempCO);

			num_cb = *(int*)pModel->collision_block;

			xd = (tempCO.pos.vx - pPosition->vx);
			zd = (tempCO.pos.vz - pPosition->vz);

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

					theta = (tempCO.yang + collide->yang) * 64;
					ypos = pPosition->vy + (tempCO.pos.vy + collide->ypos) + 80;

					cs = RCOS(theta);
					sn = RSIN(theta);
					*/

					// [A] NEW
					int xxd, zzd;
					int yang;
					int theta;
					MATRIX2* mat;

					yang = -tempCO.yang & 0x3f;
					theta = (tempCO.yang + collide->yang) * 64;

					mat = &matrixtable[yang];

					cs = RCOS(theta);
					sn = RSIN(theta);

					xxd = FIXEDH(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]);
					zzd = FIXEDH(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]);

					xd = (tempCO.pos.vx - pPosition->vx) + xxd;
					zd = (tempCO.pos.vz - pPosition->vz) + zzd;

					zs = ((collide->zsize + 10) * 2048 + radius * 4096);
					xs = ((collide->xsize + 10) * 2048 + radius * 4096);

					ypos = pPosition->vy + (tempCO.pos.vy + collide->ypos);	// [A] removed excessive height
					
#if defined(COLLISION_DEBUG) && !defined(PSX)
					int result = 0;

					if (collide->ysize / 2 > ABS(ypos) &&
						xs * 2 > ABS(xd * cs - zd * sn) + xs &&
						zs * 2 > ABS(zd * cs + xd * sn) + zs)
					{
						result = 1;
					}

					extern int gShowCollisionDebug;
					if (gShowCollisionDebug == 3)
					{
						CDATA2D cd[1];

						cd[0].x.vx = (tempCO.pos.vx + xxd);//FIXEDH(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]));
						cd[0].x.vz = (tempCO.pos.vz + zzd);//FIXEDH(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]));
						cd[0].x.vy = pPosition->vy;

						cd[0].theta = theta; // (tempCO.yang + collide->yang) * 64 & 0xfff;
						cd[0].length[0] = collide->zsize / 2;
						cd[0].length[1] = collide->xsize / 2;

						// calc axes of box
						int dtheta = cd[0].theta & 0xfff;

						cd[0].axis[0].vx = RSIN(dtheta);
						cd[0].axis[0].vz = RCOS(dtheta);

						cd[0].axis[1].vz = -RSIN(dtheta);
						cd[0].axis[1].vx = RCOS(dtheta);

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
					if (collide->ysize / 2 > ABS(ypos) &&
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
	}

	return 1;
}


// [D] [T]
int GlobalPositionToCellNumber(VECTOR *pPosition)
{
	int cellX, cellZ;
	int cbrX, cbrZ;
	int cbr;

	cellX = (pPosition->vx + units_across_halved - (MAP_REGION_SIZE*MAP_REGION_SIZE)) / MAP_CELL_SIZE;
	cellZ = (pPosition->vz + units_down_halved - (MAP_REGION_SIZE*MAP_REGION_SIZE)) / MAP_CELL_SIZE;
	
	cbrX = cellX / MAP_REGION_SIZE;
	cbrZ = cellZ / MAP_REGION_SIZE;

	cbr = (cbrX & 1) + (cbrZ & 1) * 2;

	if (RoadMapRegions[cbr] != cbrX + cbrZ * regions_across)
		return -1;

	return cell_ptrs[(cellZ - cbrZ * MAP_REGION_SIZE) * MAP_REGION_SIZE + cbr * (MAP_REGION_SIZE*MAP_REGION_SIZE) + cellX - cbrX * MAP_REGION_SIZE];
}


// [D] [T]
char CellAtPositionEmpty(VECTOR *pPosition, int radius)
{
	if (GlobalPositionToCellNumber(pPosition) == -1)
		return 1;

	return CellEmpty(pPosition, radius);
}


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

int testRadius = 222;

// [D] [T]
char lineClear(VECTOR *v1, VECTOR *v2)
{
	PACKED_CELL_OBJECT* ppco;
	CELL_OBJECT tempCO;
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

#ifdef PSX
	CELL_ITERATOR& ci = *(CELL_ITERATOR*)((u_char*)getScratchAddr(0) + 1024 - sizeof(CELL_ITERATOR));
#else
	CELL_ITERATOR ci;
#endif

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

			while (ppco)
			{
				QuickUnpackCellObject(ppco, &ci.nearCell, &tempCO);
				pModel = modelpointers[tempCO.type];

				xd = ((tempCO.pos.vx - ((va.vx + vb.vx) / 2 & 0xffffU)) * 0x10000) >> 0x10;
				zd = ((tempCO.pos.vz - ((va.vz + vb.vz) / 2 & 0xffffU)) * 0x10000) >> 0x10;

				sphere_sq = pModel->bounding_sphere + 800;

				if ((uint)pModel->collision_block > 0 &&
					(pModel->flags2 & (MODEL_FLAG_CHAIR | MODEL_FLAG_SMASHABLE)) == 0 && 
					(xd*xd + zd*zd < sphere_sq*sphere_sq))
				{
					num_cb = *(int*)pModel->collision_block;
					box_loop = 0;

					collide = (COLLISION_PACKET*)(pModel->collision_block + sizeof(int));

					while (box_loop < num_cb)
					{
						yang = -tempCO.yang & 0x3f;
						theta = (tempCO.yang + collide->yang) * 64;

						mat = &matrixtable[yang];

						cs = RCOS(theta);
						sn = RSIN(theta);

						dx = va.vx - (tempCO.pos.vx + FIXEDH(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]));
						dz = va.vz - (tempCO.pos.vz + FIXEDH(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]));
						
						box.slab[0].upper = collide->xsize / 2 +testRadius;
						box.slab[0].lower = -box.slab[0].upper;
					
						box.slab[1].upper = collide->ysize / 2 +testRadius;
						box.slab[1].lower = -box.slab[1].upper;
						
						box.slab[2].upper = collide->zsize / 2 +testRadius;
						box.slab[2].lower = -box.slab[2].upper;

						ray.org[0] = FIXEDH(cs * dx - sn * dz);
						ray.org[2] = FIXEDH(cs * dz + sn * dx);
						ray.org[1] = (va.vy - (((-collide->ypos - tempCO.pos.vy) * 0x10000) >> 0x10)) + 80;

						ray.dir[0] = FIXEDH(cs * pos.vx - sn * pos.vz);
						ray.dir[2] = FIXEDH(cs * pos.vz + sn * pos.vx);
						ray.dir[1] = vb.vy - va.vy;

#if defined(COLLISION_DEBUG) && !defined(PSX)
						int rayResult = RaySlabsIntersection(&ray, &box);

						extern int gShowCollisionDebug;
						if (gShowCollisionDebug == 3)
						{
							CDATA2D cd[1];

							cd[0].x.vx = (tempCO.pos.vx + FIXEDH(collide->xpos * mat->m[0][0] + collide->zpos * mat->m[2][0]));
							cd[0].x.vz = (tempCO.pos.vz + FIXEDH(collide->xpos * mat->m[0][2] + collide->zpos * mat->m[2][2]));
							cd[0].x.vy = va.vy;

							cd[0].theta = (tempCO.yang + collide->yang) * 64 & 0xfff;
							cd[0].length[0] = collide->zsize / 2;
							cd[0].length[1] = collide->xsize / 2;

							// calc axes of box
							int dtheta = cd[0].theta & 0xfff;

							cd[0].axis[0].vx = RSIN(dtheta);
							cd[0].axis[0].vz = RCOS(dtheta);

							cd[0].axis[1].vz = -RSIN(dtheta); 
							cd[0].axis[1].vx = RCOS(dtheta);

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

// [D] [T]
void CollisionCopList(XZPAIR* pos, int* count)
{
	static XZPAIR initial;

	PACKED_CELL_OBJECT* ppco;
	CELL_OBJECT* cop;
	int i, j, cnt;
	XZPAIR cell;
	XZPAIR cbr;
	MODEL* model;
	int cellLevel;
	int type;

#if 0
	CELL_ITERATOR& ci = *(CELL_ITERATOR*)((u_char*)getScratchAddr(0) + 1024 - sizeof(CELL_ITERATOR));
#else
	CELL_ITERATOR ci;
#endif
	
	cellLevel = events.camera ? events.draw : -1;

	if (pos == NULL)
	{
		cnt = *count;
		
		cell.x = initial.x;
		for (i = 0; i < 2; i++)
		{
			cbr.x = cell.x / MAP_REGION_SIZE;
			
			cell.z = initial.z;
			for (j = 0; j < 2; j++) 
			{
				cbr.z = cell.z / MAP_REGION_SIZE;

				// check if we have valid region
				if (cbr.x + cbr.z * regions_across == RoadMapRegions[(cbr.x & 1) + (cbr.z & 1) * 2])
				{
					ppco = GetFirstPackedCop(cell.x, cell.z, &ci, 1, cellLevel);
					
					while (ppco)
					{
						type = (ppco->value >> 6) | ((ppco->pos.vy & 1) << 10);

						model = modelpointers[type];

						if ((uint)model->collision_block > 0 &&
							/*model->num_vertices - 3 < 300 &&
							model->num_point_normals < 300 &&
							model->num_polys < 300 &&*/
							*(int*)model->collision_block > 0)
						{
							cop = UnpackCellObject(ppco, &ci.nearCell);
							cop->pad = cnt;

							coplist[cnt] = cop;
							pcoplist[cnt] = ppco;
							cnt++;
						}

						ppco = GetNextPackedCop(&ci);
					}
				}

				cell.z++;
			}

			cell.x++;
		}

		*count = cnt;
	}
	else
	{
		initial.x = pos->x;
		initial.z = pos->z;

		ClearCopUsage();
	}
}


// [D] [T]
void SetCopListCell(int x, int z)
{
	XZPAIR cell;

	cell.x = x;
	cell.z = z;
	CollisionCopList(&cell, NULL);
}

// [D] [T]
void BuildCollisionCopList(int *count)
{
	CollisionCopList(NULL, count);
}

int gCameraBoxOverlap;
int ExBoxDamage = 0;

// [D] [T]
void CheckScenaryCollisions(CAR_DATA *cp)
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

	D_CHECK_ERROR(cp < car_data, "Invalid car");

	if (ghost_mode || cp->controlType == CONTROL_TYPE_PLAYER && playerghost)
		return;

	EventCollisions(cp, 0);

	player_pos.vx = cp->hd.where.t[0];
	player_pos.vz = cp->hd.where.t[2];

	gCameraBoxOverlap = -1;

	if (cp->controlType == CONTROL_TYPE_TANNERCOLLIDER)
		extraDist = 100;
	else
		extraDist = 580;

	// [A] FIXME: replace with 'cell_header.cell_size'
	cell.x = (player_pos.vx + units_across_halved - (MAP_REGION_SIZE*MAP_REGION_SIZE)) / MAP_CELL_SIZE;
	cell.z = (player_pos.vz + units_down_halved - (MAP_REGION_SIZE*MAP_REGION_SIZE)) / MAP_CELL_SIZE;

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
		num_cb = *(int*)model->collision_block;	// box count

		if ((uint)model->collision_block > 0 /*&&
			model->num_vertices - 3 < 300 &&
			model->num_point_normals < 300 &&
			model->num_polys < 300*/ &&
			num_cb > 0)
		{
			dx = cop->pos.vx - player_pos.vx;
			dz = cop->pos.vz - player_pos.vz;
					
			sphereSq = model->bounding_sphere + extraDist + cp->hd.speed;

			if (dx * dx + dz * dz < sphereSq * sphereSq)
			{
				collide = (COLLISION_PACKET*)(model->collision_block + sizeof(int));

				while(num_cb--)
				{
					yang = -cop->yang & 63;

					// box 'rotated' by matrix
					// [A] FIXME: replace add+shift by division
					bbox.pos.vx = cop->pos.vx + FIXEDH(collide->xpos * matrixtable[yang].m[0][0] + collide->zpos * matrixtable[yang].m[2][0]);
					bbox.pos.vy = cop->pos.vy + collide->ypos;
					bbox.pos.vz = cop->pos.vz + FIXEDH(collide->xpos * matrixtable[yang].m[0][2] + collide->zpos * matrixtable[yang].m[2][2]);

					//bbox.pos.pad = (model->flags2 & MODEL_FLAG_BARRIER) > 0;

					bbox.xsize = collide->zsize / 2;
					bbox.zsize = collide->xsize / 2;

					bbox.height = collide->ysize;
					bbox.theta = (cop->yang + collide->yang) * 64 & 0xfff;
					bbox.model = cop->type; // [A]

					if (CAR_INDEX(cp) == TANNER_COLLIDER_CARID)
					{
						if (count >= mdcount && cop->pad != 0) // kill by Vegas train
						{
							if (CarBuildingCollision(cp, &bbox, cop, 0))
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
						if ((model->flags2 & (MODEL_FLAG_CHAIR | MODEL_FLAG_SMASHABLE)) == 0 && 
							(bbox.xsize > 100 || (bbox.zsize > 100)))
						{
							coll_test_count = 5;
							
							bbox.xsize += 100;
							bbox.zsize += 100;

							gCameraBoxOverlap = -1;

							minDist = lbody / 2;
							
							while (coll_test_count > 0 && minDist <= gCameraDistance && CarBuildingCollision(cp, &bbox, cop, 0))
							{
								gCameraDistance -= gCameraBoxOverlap;
										
								if (gCameraDistance < minDist)
									gCameraDistance = minDist;

								cp->hd.where.t[0] = car_data[0].hd.where.t[0] + FIXEDH((gCameraDistance * RSIN(cp->hd.direction)) / 2);
								cp->hd.where.t[2] = car_data[0].hd.where.t[2] + FIXEDH((gCameraDistance * RCOS(cp->hd.direction)) / 2);
								
								coll_test_count--;
							}
						}
					}
					else
					{
						if (count >= mdcount && cop->pad != 0)
						{
							cp->st.n.linearVelocity[2] = ExBoxDamage + cp->st.n.linearVelocity[2];
									
							if (CarBuildingCollision(cp, &bbox, cop, (cop->pad == 1) ? CollisionCheckFlag_IsVegasMovingTrain : 0))
							{
								cp->ap.needsDenting = 1;
							}

							//cp->st.n.linearVelocity[2] -= 700000; // [A] Vegas train velocity - disabled here
						}
						else
						{
							if (CarBuildingCollision(cp, &bbox, cop, (model->flags2 & MODEL_FLAG_BARRIER) ? CollisionCheckFlag_MightBeABarrier : 0))
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


// [D] [T]
int QuickBuildingCollisionCheck(VECTOR *pPos, int dir, int l, int w, int extra)
{
	int count;
	int num_cb;
	MODEL *model;
	u_int yang;
	int sphereSq;
	COLLISION_PACKET *collide;
	CELL_OBJECT *cop;
	XZPAIR cell;
	VECTOR player_pos;
	BUILDING_BOX bbox;
	VECTOR offset;
	int mdcount;
	int dx, dz;

#if 0
	CDATA2D* cd = (CDATA2D*)((u_char*)getScratchAddr(0) + 1024 - sizeof(CDATA2D) * 2);
#else
	CDATA2D cd[2] = { 0 };
#endif

	gCameraBoxOverlap = -1;

	player_pos.vx = pPos->vx;
	player_pos.vz = pPos->vz;

	cell.x = (player_pos.vx + units_across_halved - (MAP_REGION_SIZE*MAP_REGION_SIZE)) / MAP_CELL_SIZE;
	cell.z = (player_pos.vz + units_down_halved - (MAP_REGION_SIZE*MAP_REGION_SIZE)) / MAP_CELL_SIZE;
	
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

		count++;

		model = modelpointers[cop->type];

		if ((uint)model->collision_block > 0 /*&&
			model->num_vertices - 3 < 300 && 
			model->num_point_normals < 300 && 
			model->num_polys < 300*/)
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

						int res = bcollided2d(cd);
							
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

// [D] [T]
void DoScenaryCollisions(void)
{
	CAR_DATA *cp;

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





