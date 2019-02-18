#include "../decomp_defs.h"

VECTOR CameraPos =
{ 4294967251, 4294967125, 4294967171, 0 };

VECTOR camera_position =
{ 0, 4294966916, 0, 0 };

MATRIX face_camera_work =
{ { { 4096, 0, 0 }, { 0, 4096, 0 }, { 0, 0, 4096 } }, { 0, 0, 0 } };



/*
 * Offset 0x1F65C
 * D:\driver2\game\C\CAMERA.C (line 422)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ InitCamera(struct _PLAYER *lp /*$s0*/)
{ // line 1, address 0x1f65c
	struct SVECTOR boxDisp; // stack address -16
	{ // line 6, address 0x1f684
	} // line 6, address 0x1f684
	{ // line 19, address 0x1f714
		struct _CAR_DATA *lcp; // $a0
	} // line 19, address 0x1f714
	{ // line 32, address 0x1f7fc
		struct _EVENT *event; // $a1
	} // line 33, address 0x1f7fc
} // line 122, address 0x1fa88
/*
 * Offset 0x1FA88
 * D:\driver2\game\C\CAMERA.C (line 553)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ModifyCamera()
{ // line 2, address 0x1fa88
	struct PAD *locPad; // $a3
	struct _PLAYER *lp; // $a2
	{ // line 15, address 0x1fb64
		char *pNextCameraview; // $a0
	} // line 25, address 0x1fbb0
	{ // line 32, address 0x1fbcc
		int cam_ang; // $a0
		int length; // $a1
	} // line 40, address 0x1fc6c
} // line 43, address 0x1fc78
/*
 * Offset 0x1FC80
 * D:\driver2\game\C\CAMERA.C (line 609)
 * Stack frame base $sp, length 184
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ CameraCollisionCheck()
{ // line 2, address 0x1fc80
	struct MODEL *model; // $v1
	struct COLLISION_PACKET *collide; // $t2
	struct CELL_OBJECT *cop; // $t3
	struct CELL_ITERATOR ci; // stack address -168
	struct VECTOR nearpoint; // stack address -144
	struct VECTOR surfacenormal; // stack address -128
	struct VECTOR surfacepoint; // stack address -112
	int cell_x; // $a0
	int cell_z; // $a1
	int xd; // $v1
	int zd; // $a0
	int num_cb; // $t5
	int box_loop; // $t4
	int sphere_sq; // $a2
	int camera_size; // $s0
	int count; // $s1
	struct VECTOR temp_cam; // stack address -96
	{ // line 50, address 0x1fe5c
		struct MATRIX *mat; // $a2
		struct VECTOR address; // stack address -80
		struct VECTOR cam_vec; // stack address -64
		struct VECTOR normal; // stack address -48
		int xmin; // $a0
		int xmax; // $a3
		int ymin; // $t0
		int ymax; // $v1
		int zmin; // $a1
		int zmax; // $a2
		int tx; // $a3
		int tz; // $a1
	} // line 85, address 0x20038
} // line 93, address 0x200a4
/*
 * Offset 0x200A4
 * D:\driver2\game\C\CAMERA.C (line 777)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ PlaceCameraFollowCar(struct _PLAYER *lp /*$s2*/)
{ // line 1, address 0x200a4
	int carheight; // $a0
	int minimum_height; // $s1
	int cammapht; // $s0
	int new_angle; // $a0
	int camPosVy; // $s1
	struct VECTOR locCameraPos; // stack address -48
	int lbody; // $a0
	int hbody; // $a3
	int camExpandSpeed; // $s6
	{ // line 23, address 0x200f0
		struct _CAR_DATA *camCar; // $v1
	} // line 33, address 0x20184
} // line 116, address 0x20574
/*
 * Offset 0x20574
 * D:\driver2\game\C\CAMERA.C (line 987)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ PlaceCameraInCar(struct _PLAYER *lp /*$s3*/, int BumperCam /*$a1*/)
{ // line 1, address 0x20574
	struct _CAR_DATA *cp; // $s2
	{ // line 57, address 0x20824
	} // line 58, address 0x20834
	{ // line 62, address 0x20848
	} // line 65, address 0x20868
} // line 90, address 0x2096c
/*
 * Offset 0x2096C
 * D:\driver2\game\C\CAMERA.C (line 904)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ PlaceCameraAtLocation(struct _PLAYER *lp /*$s1*/, int zoom /*$s2*/)
{ // line 1, address 0x2096c
	int d; // $s0
	{ // line 7, address 0x20998
		struct VECTOR temp; // stack address -32
	} // line 9, address 0x20998
} // line 46, address 0x20a60
/*
 * Offset 0x20A78
 * D:\driver2\game\C\CAMERA.C (line 716)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ TurnHead(struct _PLAYER *lp /*$a0*/)
{ // line 1, address 0x20a78
} // line 41, address 0x20b70
/*
 * Offset 0x20B70
 * D:\driver2\game\C\CAMERA.C (line 960)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ PointAtTarget(struct VECTOR *pPosition /*$a0*/, struct VECTOR *pTarget /*$a1*/, struct SVECTOR *pAngleVec /*$s0*/)
{ // line 1, address 0x20b70
	struct VECTOR delta; // stack address -32
	int d; // $s1
} // line 16, address 0x20c28
/*
 * Offset 0x20C28
 * D:\driver2\game\C\CAMERA.C (line 1083)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ OK_To_Zoom()
{ // line 2, address 0x20c28
	int old_z; // $s0
	struct VECTOR temp; // stack address -24
} // line 31, address 0x20cd8
/*
 * Offset 0x20CD8
 * D:\driver2\game\C\CAMERA.C (line 1119)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetBasePos(struct VECTOR *pVec /*$a0*/)
{
}