#include "THISDUST.H"
#include "../C/CAMERA.H"
#include "GTEREG.H"

void SetCameraVector(void)
{
	setCopControlWord(2, 0xa800, camera_position.vx);
	setCopControlWord(2, 0xb000, camera_position.vy);
	setCopControlWord(2, 0xb800, camera_position.vz);
}

void Apply_Inv_CameraMatrix(VECTOR *v)
{
	UNIMPLEMENTED();
	/*
	int local_t1_;
	int local_t2_;
	int local_t3_;
	int temp_13f6df32dea;
	int temp_13fa5c10845;
	int temp_13f23483f68;

	setCopReg(2, local_t1_, *(int *)m0->m);
	setCopReg(2, local_t2_, *(int *)(m0->m + 2));
	setCopReg(2, local_t3_, *(int *)(m0->m + 4));
	copFunction(2, 0x4de012);
	temp_13f6df32dea = getCopReg(2, 9);
	*(int *)m0->m = temp_13f6df32dea;
	temp_13fa5c10845 = getCopReg(2, 10);
	*(int *)(m0->m + 2) = temp_13fa5c10845;
	temp_13f23483f68 = getCopReg(2, 0xb);
	*(int *)(m0->m + 4) = temp_13f23483f68;
	*/
}

int FrustrumCheck16(PACKED_CELL_OBJECT *pcop, int bounding_sphere)
{
	UNIMPLEMENTED();
	return 0;
	/*
	int iVar1;
	int iVar2;
	int iVar3;

	setCopReg(2, 0x4800, ((short)(pcop->pos).vx - camera_position.vx) * 0x10000 >> 0x11);
	setCopReg(2, 0x5000, ((short)(pcop->pos).vy - camera_position.vy) * 0x10000 >> 0x11);
	setCopReg(2, 0x5800, ((short)(pcop->pos).vz - camera_position.vz) * 0x10000 >> 0x11);
	copFunction(2, 0x4be012);
	iVar1 = getCopReg(2, 0xc800);
	iVar3 = getCopReg(2, 0xd000);
	iVar2 = frustrum_matrix.t[0] - (bounding_sphere >> 1);
	if (((iVar2 <= iVar1) && (iVar1 = getCopReg(2, 0xd800), iVar2 <= iVar3)) && (iVar2 <= iVar1)) {
		return 0;
	}
	return -1;
	*/
}