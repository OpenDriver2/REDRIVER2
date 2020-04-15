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
#endif // PSX
}

extern MATRIX frustrum_matrix;

// [D]
int FrustrumCheck16(PACKED_CELL_OBJECT *pcop, int bounding_sphere)
{
#ifndef PSX
	int iVar1;
	int iVar2;
	int iVar3;

	MTC2(((short)(pcop->pos).vx - camera_position.vx) * 0x10000 >> 0x11, 9);
	MTC2(((short)(pcop->pos).vy - camera_position.vy) * 0x10000 >> 0x11, 10);
	MTC2(((short)(pcop->pos).vz - camera_position.vz) * 0x10000 >> 0x11, 11);

	docop2(0x4be012);

	iVar1 = MFC2(25);
	iVar3 = MFC2(26);

	iVar2 = frustrum_matrix.t[0] - (bounding_sphere >> 1);

	if (iVar2 <= iVar1)
	{
		// [A]
		iVar1 = MFC2(27);
		if (iVar2 <= iVar3 && (iVar2 <= iVar1))
		{
			return 0;
		}
	}

	return -1;
#endif // PSX
}