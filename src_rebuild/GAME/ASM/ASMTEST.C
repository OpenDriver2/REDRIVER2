#include "THISDUST.H"
#include "../C/CAMERA.H"

void SetCameraVector(void)
{
	setCopControlWord(2, 0xa800, camera_position.vx);
	setCopControlWord(2, 0xb000, camera_position.vy);
	setCopControlWord(2, 0xb800, camera_position.vz);
}