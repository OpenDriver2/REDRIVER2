#include "DRIVER2.H"
#include "../C/CAMERA.H"
#include "GTEREG.H"
#include "INLINE_C.H"

// ASM functions.
// don't do this in PSX.

// [D] [T]
void SetCameraVector(void)
{
	gte_ldfc(&camera_position)
}

// [D] [T]
void Apply_Inv_CameraMatrix(VECTOR *v)
{
	gte_ldlvl(v);
	gte_lcir();
	gte_stlvl(v);
}

// [D] [T]
int Apply_InvCameraMatrixSetTrans(VECTOR_NOPAD *pos)
{
	VECTOR vfc;
	VECTOR vec;
	VECTOR local;
	gte_stfc(&vfc);

	local.vx = (pos->vx - vfc.vx) << 0x10 >> 0x10;
	local.vy = (pos->vy - vfc.vy) << 0x10 >> 0x10;
	local.vz = (pos->vz - vfc.vz) << 0x10 >> 0x10;

#if 0
	gte_ldlvl(&local);
	gte_lcir();
	gte_stlvl(&vec);
#else
	MATRIX lc;
	gte_ReadColorMatrix(&lc);

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
int Apply_InvCameraMatrixAndSetMatrix(VECTOR_NOPAD *pos, MATRIX2 *mtx)
{
	VECTOR vfc;
	VECTOR vec;
	VECTOR local;
	gte_stfc(&vfc);

	local.vx = (pos->vx - vfc.vx) << 0x10 >> 0x10;
	local.vy = (pos->vy - vfc.vy) << 0x10 >> 0x10;
	local.vz = (pos->vz - vfc.vz) << 0x10 >> 0x10;

#if 0
	gte_ldlvl(&local);
	gte_lcir();
	gte_stlvl(&vec);
#else
	MATRIX lc;
	gte_ReadColorMatrix(&lc);

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

extern MATRIX frustrum_matrix;

// [D] [T]
int FrustrumCheck16(PACKED_CELL_OBJECT *pcop, int bounding_sphere)
{
	VECTOR local;
	local.vx = (pcop->pos.vx - camera_position.vx) << 0x10 >> 0x11;
	local.vy = (pcop->pos.vy - camera_position.vy) << 0x10 >> 0x11;
	local.vz = (pcop->pos.vz - camera_position.vz) << 0x10 >> 0x11;

	gte_ldlvl(&local);

	gte_llir();

	VECTOR result;
	gte_stlvnl(&result);

	int ang = frustrum_matrix.t[0] - (bounding_sphere >> 1);

	if (ang <= result.vx && ang <= result.vy && ang <= result.vz)
		return 0;

	return -1;
}

// [D] [T]
int FrustrumCheck(VECTOR *pos, int bounding_sphere)
{
	VECTOR local;
	local.vx = (pos->vx - camera_position.vx) * 0x10000 >> 0x11;
	local.vy = (pos->vy - camera_position.vy) * 0x10000 >> 0x11;
	local.vz = (pos->vz - camera_position.vz) * 0x10000 >> 0x11;

	gte_ldlvl(&local);

	gte_llir();

	VECTOR result;
	gte_stlvnl(&result);

	int ang = frustrum_matrix.t[0] - (bounding_sphere >> 1);

	if (ang <= result.vx && ang <= result.vy && ang <= result.vz)
		return 0;

	return -1;
}
