#include "driver2.h"
#include "C/camera.h"
#include "C/draw.h"
#include "C/cell.h"

#define FRUSTUM_THRESHOLD (-80)

#ifndef PSX
static int FixedDot(const MATRIX& matrix, int row, int vx, int vy, int vz)
{
	return (int)(((long long)matrix.m[row][0] * vx +
		(long long)matrix.m[row][1] * vy +
		(long long)matrix.m[row][2] * vz) >> ONE_BITS);
}

static void ApplyMatrixFull(const MATRIX& matrix, VECTOR* out, int vx, int vy, int vz)
{
	out->vx = FixedDot(matrix, 0, vx, vy, vz);
	out->vy = FixedDot(matrix, 1, vx, vy, vz);
	out->vz = FixedDot(matrix, 2, vx, vy, vz);
	out->pad = 0;
}

static void ApplyMatrixFullNoPad(const MATRIX& matrix, VECTOR_NOPAD* out, int vx, int vy, int vz)
{
	out->vx = FixedDot(matrix, 0, vx, vy, vz);
	out->vy = FixedDot(matrix, 1, vx, vy, vz);
	out->vz = FixedDot(matrix, 2, vx, vy, vz);
}
#endif

// [D] [T]
void SetCameraVector(void)
{
	gte_ldfc(&camera_position);
}

// [D] [T]
void Apply_Inv_CameraMatrix(VECTOR* v)
{
#ifdef PSX
	gte_ldlvl(v);
	gte_lcir();
	gte_stlvl(v);
#else
	VECTOR local = *v;
	ApplyMatrixFull(inv_camera_matrix, v, local.vx, local.vy, local.vz);
#endif
}

// [D] [T]
int Apply_InvCameraMatrixSetTrans(VECTOR_NOPAD* pos)
{
	VECTOR vfc, vec;
	gte_stfc(&vfc);

#ifdef PSX
	SVECTOR local;
	VecSubtract(&local, pos, &vfc);

	gte_ldsv(&local);
	gte_lcir();
	gte_stlvl(&vec);
#else
	ApplyMatrixFull(inv_camera_matrix, &vec, pos->vx - vfc.vx, pos->vy - vfc.vy, pos->vz - vfc.vz);
#endif
	gte_SetTransVector(&vec);

	if (vec.vx >> 1 < 0)
		return vec.vz - vec.vx;

	return vec.vz + vec.vx;
}

// [D] [T]
int Apply_InvCameraMatrixAndSetMatrix(VECTOR_NOPAD* pos, MATRIX2* mtx)
{
	VECTOR vfc, vec;
	gte_stfc(&vfc);

#ifdef PSX
	SVECTOR local;
	VecSubtract(&local, pos, &vfc);

	gte_ldsv(&local);
	gte_lcir();
	gte_stlvl(&vec);
#else
	ApplyMatrixFull(inv_camera_matrix, &vec, pos->vx - vfc.vx, pos->vy - vfc.vy, pos->vz - vfc.vz);
#endif

	gte_SetRotMatrix(mtx);
	gte_SetTransVector(&vec);

	if (vec.vx >> 1 < 0)
		return vec.vz - vec.vx;

	return vec.vz + vec.vx;
}

// [D] [T]
int FrustrumCheck16(PACKED_CELL_OBJECT* pcop, XZPAIR* near, int bounding_sphere)
{
	VECTOR_NOPAD result;
	SVECTOR local;
	int ang;

#ifdef PSX
	VecSubtract(&local, &pcop->pos, &camera_position);

	gte_ldsv(&local);
	gte_llir();

	gte_stlvnl(&result);
#else
	CELL_OBJECT cellObject;
	QuickUnpackCellObject(pcop, near, &cellObject);
	ApplyMatrixFullNoPad(frustrum_matrix, &result,
		cellObject.pos.vx - camera_position.vx,
		cellObject.pos.vy - camera_position.vy,
		cellObject.pos.vz - camera_position.vz);
#endif

	ang = FRUSTUM_THRESHOLD - bounding_sphere;

	if (ang <= result.vx && ang <= result.vy && ang <= result.vz) 
	{
		return 0;
	}

	return -1;
}

// [D] [T]
int FrustrumCheck(VECTOR* pos, int bounding_sphere)
{
	VECTOR_NOPAD result;
	int ang;

#ifdef PSX
	SVECTOR local;
	VecSubtract(&local, pos, &camera_position);

	gte_ldsv(&local);
	gte_llir();

	gte_stlvnl(&result);
#else
	ApplyMatrixFullNoPad(frustrum_matrix, &result,
		pos->vx - camera_position.vx,
		pos->vy - camera_position.vy,
		pos->vz - camera_position.vz);
#endif

	ang = FRUSTUM_THRESHOLD - bounding_sphere;

	if (ang <= result.vx && ang <= result.vy && ang <= result.vz) 
	{
		return 0;
	}

	return -1;
}
