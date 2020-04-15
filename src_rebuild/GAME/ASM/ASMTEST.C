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

	iVar1 = CFC2_S(21);
	iVar2 = CFC2_S(22);
	iVar3 = CFC2_S(23);

	MTC2_S((pos->vx - iVar1) * 0x10000 >> 0x10, 9);
	MTC2_S((pos->vy - iVar2) * 0x10000 >> 0x10, 10);
	MTC2_S((pos->vz - iVar3) * 0x10000 >> 0x10, 11);

	docop2(0x4de012);

	iVar2 = MFC2_S(9);
	local_t1_96 = MFC2_S(10);
	iVar1 = MFC2_S(11);

	CTC2_S(iVar2, 5);
	CTC2_S(local_t1_96, 6);
	CTC2_S(iVar1, 7);

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

	iVar1 = CFC2_S(21);
	iVar2 = CFC2_S(22);
	iVar3 = CFC2_S(23);

	MTC2_S((pos->vx - iVar1) * 0x10000 >> 0x10, 9);
	MTC2_S((pos->vy - iVar2) * 0x10000 >> 0x10, 10);
	MTC2_S((pos->vz - iVar3) * 0x10000 >> 0x10, 11);

	copFunction(2, 0x4de012);

	CTC2_S(*(uint*)((char *)mtx->m), 0);
	CTC2_S(*(uint*)((char *)mtx->m + 2), 1);
	CTC2_S(*(uint*)((char *)mtx->m + 4), 2);
	CTC2_S(*(uint*)((char *)mtx->m + 6), 3);
	CTC2_S(*(uint*)((char *)mtx->m + 8), 4);

	iVar2 = MFC2_S(9);
	local_t1_120 = MFC2_S(10);
	iVar1 = MFC2_S(11);

	CTC2_S(iVar2, 5);
	CTC2_S(local_t1_120, 6);
	CTC2_S(iVar1, 7);

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

	MTC2_S(((pcop->pos).vx - camera_position.vx) * 0x10000 >> 0x11, 9);
	MTC2_S(((pcop->pos).vy - camera_position.vy) * 0x10000 >> 0x11, 10);
	MTC2_S(((pcop->pos).vz - camera_position.vz) * 0x10000 >> 0x11, 11);

	docop2(0x4be012);

	iVar1 = MFC2_S(25);
	iVar3 = MFC2_S(26);

	iVar2 = frustrum_matrix.t[0] - (bounding_sphere >> 1);

	if (iVar2 <= iVar1)
	{
		// [A]
		iVar1 = MFC2_S(27);

		if (iVar2 <= iVar3 && (iVar2 <= iVar1))
			return 0;
	}

	return -1;
#endif // !PSX
}