#include "driver2.h"
#include "bcoll3d.h"

// [D] [T]
void PointFaceCheck(CAR_DATA *cp0, CAR_DATA *cp1, int i, TestResult *least, int nSign)
{
	int partialDepth;
	int depth;
	SVECTOR_NOPAD *radii;
	int k;

	VECTOR normal;
	VECTOR diff;
	VECTOR point;

	point.vx = cp1->hd.oBox.location.vx;
	point.vy = cp1->hd.oBox.location.vy;
	point.vz = cp1->hd.oBox.location.vz;

	normal.vx = cp0->hd.where.m[0][i];
	normal.vy = cp0->hd.where.m[1][i];
	normal.vz = cp0->hd.where.m[2][i];

	diff.vx = point.vx - cp0->hd.oBox.location.vx;
	diff.vy = point.vy - cp0->hd.oBox.location.vy;
	diff.vz = point.vz - cp0->hd.oBox.location.vz;

	depth = FIXEDH(diff.vx * normal.vx + diff.vy * normal.vy + diff.vz * normal.vz);

	if (depth < 0) 
	{
		normal.vx = -normal.vx;
		normal.vy = -normal.vy;
		normal.vz = -normal.vz;
	}
	else 
	{
		depth = -depth;
	}

	radii = cp1->hd.oBox.radii;
	depth += cp0->hd.oBox.length[i];

	k = 2;

	do {
		diff.vx = radii->vx;
		diff.vy = radii->vy;
		diff.vz = radii->vz;

		partialDepth = FIXEDH(diff.vx * normal.vx + diff.vy * normal.vy + diff.vz * normal.vz);

		if (partialDepth < 0) 
		{
			partialDepth = -partialDepth;
		}
		else 
		{
			diff.vx = -diff.vx;
			diff.vy = -diff.vy;
			diff.vz = -diff.vz;
		}

		point.vx += diff.vx;
		point.vy += diff.vy;
		point.vz += diff.vz;

		depth += partialDepth;

		radii++;
		k--;
	} while (k >= 0);

	if (depth < least->depth && (least->depth = depth, -1 < depth))
	{
		least->location.vx = point.vx;
		least->location.vy = point.vy;
		least->location.vz = point.vz;

		if (nSign < 0) 
		{
			normal.vx = -normal.vx;
			normal.vy = -normal.vy;
			normal.vz = -normal.vz;
		}

		least->normal.vx = normal.vx;
		least->normal.vy = normal.vy;
		least->normal.vz = normal.vz;
	}
}

// [D] [T]
int collided3d(CAR_DATA *cp0, CAR_DATA *cp1, TestResult *least)
{
	int i;

	least->depth = 0x40000000;
	PointFaceCheck(cp0, cp1, 1, least, 1);

	if (least->depth > -1 && (PointFaceCheck(cp1, cp0, 1, least, -1), least->depth > -1))
	{
		least->depth = 0x40000000;
		i = 0;

		while (PointFaceCheck(cp0, cp1, i, least, 1), least->depth > -1) 
		{
			PointFaceCheck(cp1, cp0, i, least, -1);

			i += 2;

			if (least->depth < 0)
				return 0;
			
			if (i > 2)
				return 1;
		
		}
	}

	return 0;
}

// [D] [T]
int CarCarCollision3(CAR_DATA *c0, CAR_DATA *c1, int *depth, VECTOR *where, VECTOR *normal)
{
	int res;
	TestResult tr;

	res = collided3d(c0, c1, &tr);

	if (res != 0)
	{
		*depth = tr.depth;
		where->vx = tr.location.vx;
		where->vy = tr.location.vy;
		where->vz = tr.location.vz;
		normal->vx = tr.normal.vx;
		normal->vy = tr.normal.vy;
		normal->vz = tr.normal.vz;
	}

	return res;
}





