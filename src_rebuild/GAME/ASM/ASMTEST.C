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
	int local_t1_96;
	int iVar1;
	int iVar2;
	int iVar3;

	iVar1 = RFC;
	iVar2 = GFC;
	iVar3 = BFC;

	IR1 = (pos->vx - iVar1);
	IR2 = (pos->vy - iVar2);
	IR3 = (pos->vz - iVar3);

	docop2(0x4de012);

	iVar2 = IR1;
	local_t1_96 = IR2;
	iVar1 = IR3;

	TRX = iVar2;
	TRY = local_t1_96;
	TRZ = iVar1;

	iVar2 = iVar2 >> 1;

	if (iVar2 < 0) 
		return iVar1 - iVar2;

	return iVar1 + iVar2;
#endif // !PSX
}

int Apply_InvCameraMatrixAndSetMatrix(VECTOR_NOPAD *pos, MATRIX2 *mtx)
{
#ifndef PSX
	int local_t1_120;
	int iVar1;
	int iVar2;
	int iVar3;

	IR1 = (pos->vx - RFC);
	IR2 = (pos->vy - GFC);
	IR3 = (pos->vz - BFC);

	docop2(0x4de012);

	gte_SetRotMatrix(mtx);

	iVar2 = IR1;
	local_t1_120 = IR2;
	iVar1 = IR3;

	TRX = iVar2;
	TRY = local_t1_120;
	TRZ = iVar1;

	iVar2 = iVar2 >> 1;

	if (iVar2 < 0) 
		return iVar1 - iVar2;

	return iVar1 + iVar2;
#endif // !PSX
}

extern MATRIX frustrum_matrix;

// [D]
int FrustrumCheck16(PACKED_CELL_OBJECT *pcop, int bounding_sphere)
{
#ifndef PSX
	int iVar1;
	int iVar2;
	int iVar3;

	IR1 = ((pcop->pos).vx - camera_position.vx);
	IR2 = ((pcop->pos).vy - camera_position.vy);
	IR3 = ((pcop->pos).vz - camera_position.vz);

	docop2(0x4be012);

	iVar1 = MAC1;
	iVar3 = MAC2;

	iVar2 = frustrum_matrix.t[0] - (bounding_sphere >> 1);

	if (iVar2 <= iVar1)
	{
		iVar1 = MAC3;

		if (iVar2 <= iVar3 && (iVar2 <= iVar1))
			return 0;
	}

	return -1;
#endif // !PSX
}