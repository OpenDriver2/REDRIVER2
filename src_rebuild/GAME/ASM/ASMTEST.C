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
	gte_stfc(&vfc);

	VECTOR local;
	local.vx = (pos->vx - vfc.vx);// *0x10000 >> 0x10;
	local.vy = (pos->vy - vfc.vy);// *0x10000 >> 0x10;
	local.vz = (pos->vz - vfc.vz);// *0x10000 >> 0x10;
	gte_ldlvl(&local);

	gte_lcir();

	VECTOR vec;
	gte_stlvl(&vec);

	gte_SetTransVector(&vec);

	if (vec.vx >> 1 < 0)
		return vec.vz - vec.vx;

	return vec.vz + vec.vx;
}

// [D] [T]
int Apply_InvCameraMatrixAndSetMatrix(VECTOR_NOPAD *pos, MATRIX2 *mtx)
{
	VECTOR vfc;
	gte_stfc(&vfc);

	VECTOR local;
	local.vx = (pos->vx - vfc.vx);// *0x10000 >> 0x10;
	local.vy = (pos->vy - vfc.vy);// *0x10000 >> 0x10;
	local.vz = (pos->vz - vfc.vz);// *0x10000 >> 0x10;
	gte_ldlvl(&local);

	gte_lcir();

	gte_SetRotMatrix(mtx);

	VECTOR vec;
	gte_stlvl(&vec);

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
	local.vx = (pcop->pos.vx - camera_position.vx) * 0x10000 >> 0x11;
	local.vy = (pcop->pos.vy - camera_position.vy) * 0x10000 >> 0x11;
	local.vz = (pcop->pos.vz - camera_position.vz) * 0x10000 >> 0x11;

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
