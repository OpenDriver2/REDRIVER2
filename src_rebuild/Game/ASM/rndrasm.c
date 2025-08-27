#include "driver2.h"
#include "C/camera.h"
#include "C/draw.h"

#define FRUSTUM_THRESHOLD (-80)

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
	MATRIX& lc = inv_camera_matrix;
	//gte_ReadColorMatrix(&lc);	// in general this is a inv_camera_matrix

	// lcir is limited to short vector values so we do this instead
	v->vx = FIXED(lc.m[0][0] * local.vx + lc.m[0][1] * local.vy + lc.m[0][2] * local.vz);
	v->vy = FIXED(lc.m[1][0] * local.vx + lc.m[1][1] * local.vy + lc.m[1][2] * local.vz);
	v->vz = FIXED(lc.m[2][0] * local.vx + lc.m[2][1] * local.vy + lc.m[2][2] * local.vz);
#endif
}

// [D] [T]
int Apply_InvCameraMatrixSetTrans(VECTOR_NOPAD* pos)
{
	VECTOR vfc, vec;
	SVECTOR local;
	gte_stfc(&vfc);

	VecSubtract(&local, pos, &vfc);

#ifdef PSX
	gte_ldsv(&local);
	gte_lcir();
	gte_stlvl(&vec);
#else
	MATRIX& lc = inv_camera_matrix;
	//gte_ReadColorMatrix(&lc);	// in general this is a inv_camera_matrix

	// lcir is limited to short vector values so we do this instead
	vec.vx = FIXED(lc.m[0][0] * local.vx + lc.m[0][1] * local.vy + lc.m[0][2] * local.vz);
	vec.vy = FIXED(lc.m[1][0] * local.vx + lc.m[1][1] * local.vy + lc.m[1][2] * local.vz);
	vec.vz = FIXED(lc.m[2][0] * local.vx + lc.m[2][1] * local.vy + lc.m[2][2] * local.vz);
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
	SVECTOR local;
	gte_stfc(&vfc);

	VecSubtract(&local, pos, &vfc);

#ifdef PSX
	gte_ldsv(&local);
	gte_lcir();
	gte_stlvl(&vec);
#else

	MATRIX& lc = inv_camera_matrix;
	//gte_ReadColorMatrix(&lc);	// in general this is a inv_camera_matrix

	// lcir is limited to short vector values so we do this instead
	vec.vx = FIXED(lc.m[0][0] * local.vx + lc.m[0][1] * local.vy + lc.m[0][2] * local.vz);
	vec.vy = FIXED(lc.m[1][0] * local.vx + lc.m[1][1] * local.vy + lc.m[1][2] * local.vz);
	vec.vz = FIXED(lc.m[2][0] * local.vx + lc.m[2][1] * local.vy + lc.m[2][2] * local.vz);
#endif

	gte_SetRotMatrix(mtx);
	gte_SetTransVector(&vec);

	if (vec.vx >> 1 < 0)
		return vec.vz - vec.vx;

	return vec.vz + vec.vx;
}

// [D] [T]
int FrustrumCheck16(PACKED_CELL_OBJECT* pcop, int bounding_sphere)
{
	VECTOR_NOPAD result;
	SVECTOR local;
	int ang;
	VecSubtract(&local, &pcop->pos, &camera_position);

	gte_ldsv(&local);
	gte_llir();

	gte_stlvnl(&result);

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
	SVECTOR local;
	int ang;
	VecSubtract(&local, pos, &camera_position);

	gte_ldsv(&local);
	gte_llir();

	gte_stlvnl(&result);

	ang = FRUSTUM_THRESHOLD - bounding_sphere;

	if (ang <= result.vx && ang <= result.vy && ang <= result.vz) 
	{
		return 0;
	}

	return -1;
}
