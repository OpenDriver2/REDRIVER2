#include "THISDUST.H"
#include "../C/CAMERA.H"
#include "GTEREG.H"
#include "INLINE_C.H"

// ASM functions.
// don't do this in PSX.

// [D]
void SetCameraVector(void)
{
	gte_ldfc(&camera_position)
}

// [D]
void Apply_Inv_CameraMatrix(VECTOR *v)
{
#ifndef PSX
	gte_ldlvl(v);
	docop2(0x4de012);
	gte_stlvl(v);
#endif // !PSX
}

int Apply_InvCameraMatrixSetTrans(VECTOR_NOPAD *pos)
{
#ifndef PSX
	VECTOR vfc;
	gte_stfc(&vfc);

	VECTOR local;
	local.vx = (pos->vx - vfc.vx) * 0x10000 >> 0x10;
	local.vy = (pos->vy - vfc.vy) * 0x10000 >> 0x10;
	local.vz = (pos->vz - vfc.vz) * 0x10000 >> 0x10;
	gte_ldlvl(&local);

	docop2(0x4de012);

	VECTOR vec;
	gte_stlvl(&vec);

	gte_SetTransVector(&vec);

	if (vec.vx >> 1 < 0)
		return vec.vz - vec.vx;

	return vec.vz + vec.vx;
#endif // !PSX
}

int Apply_InvCameraMatrixAndSetMatrix(VECTOR_NOPAD *pos, MATRIX2 *mtx)
{
#ifndef PSX
	VECTOR vfc;
	gte_stfc(&vfc);

	VECTOR local;
	local.vx = (pos->vx - vfc.vx) * 0x10000 >> 0x10;
	local.vy = (pos->vy - vfc.vy) * 0x10000 >> 0x10;
	local.vz = (pos->vz - vfc.vz) * 0x10000 >> 0x10;
	gte_ldlvl(&local);

	docop2(0x4de012);

	gte_SetRotMatrix(mtx);

	VECTOR vec;
	gte_stlvl(&vec);

	gte_SetTransVector(&vec);

	if (vec.vx >> 1 < 0)
		return vec.vz - vec.vx;

	return vec.vz + vec.vx;
#endif // !PSX
}

extern MATRIX frustrum_matrix;

// [D]
int FrustrumCheck16(PACKED_CELL_OBJECT *pcop, int bounding_sphere)
{
#ifndef PSX
	VECTOR local;
	local.vx = ((pcop->pos).vx - camera_position.vx) * 0x10000 >> 0x11;
	local.vy = ((pcop->pos).vy - camera_position.vy) * 0x10000 >> 0x11;
	local.vz = ((pcop->pos).vz - camera_position.vz) * 0x10000 >> 0x11;

	gte_ldlvl(&local);

	docop2(0x4be012);

	VECTOR result;
	gte_stlvnl(&result);

	int ang = frustrum_matrix.t[0] - (bounding_sphere >> 1);

	if (ang <= result.vx && ang <= result.vy && ang <= result.vz)
		return 0;

	return -1;
#endif // !PSX
}

// [D]
int FrustrumCheck(VECTOR *pos, int bounding_sphere)
{
#ifndef PSX
	VECTOR local;
	local.vx = (pos->vx - camera_position.vx) * 0x10000 >> 0x11;
	local.vy = (pos->vy - camera_position.vy) * 0x10000 >> 0x11;
	local.vz = (pos->vz - camera_position.vz) * 0x10000 >> 0x11;

	gte_ldlvl(&local);

	docop2(0x4be012);

	VECTOR result;
	gte_stlvnl(&result);

	int ang = frustrum_matrix.t[0] - (bounding_sphere >> 1);

	if (ang <= result.vx && ang <= result.vy && ang <= result.vz)
		return 0;

	return -1;
#endif // !PSX
}
