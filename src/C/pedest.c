
#include "../decomp_defs.h"

MODEL* pmTannerModels[17] = {0};

typedef void (*pedFunc)(struct PEDESTRIAN *pPed);

void PedDoNothing(struct PEDESTRIAN *pPed);
void PedUserWalker(struct PEDESTRIAN *pPed);
void PedUserRunner(struct PEDESTRIAN *pPed);
void PedGetInCar(struct PEDESTRIAN *pPed);
void PedGetOutCar(struct PEDESTRIAN *pPed);
void PedCarryOutAnimation(struct PEDESTRIAN *pPed);
void CivPedDoNothing(struct PEDESTRIAN *pPed);
void CivPedWalk(struct PEDESTRIAN *pPed);
void CivPedSit(struct PEDESTRIAN *pPed);
void CivPedJump(struct PEDESTRIAN *pPed);
void PedPressButton(struct PEDESTRIAN *pPed);
void TannerSitDown(struct PEDESTRIAN *pPed);
void CopStand(struct PEDESTRIAN *pPed);
void CivGetIn(struct PEDESTRIAN *pPed);

pedFunc fpPedPersonalityFunctions[] = {
	PedDoNothing, PedUserWalker, PedUserRunner,
	PedGetInCar, PedGetOutCar,
	PedCarryOutAnimation,
	CivPedDoNothing, CivPedWalk, CivPedSit, CivPedJump,
	PedPressButton, TannerSitDown, CopStand, CivGetIn };

VECTOR tannerLookAngle = { 0, 0, 0, 0 };

long force[4] = { 0x9000, 0, 0, 0 };
long point[4] = { 0, 0, 0x5A, 0 };

/*
 * Offset 0x6DD9C
 * D:\driver2\game\C\PEDEST.C (line 1137)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ IHaveThePower()
{ // line 2, address 0x6dd9c
	struct _CAR_DATA *cp; // $t4
	{ // line 15, address 0x6de20
	} // line 33, address 0x6df88
} // line 45, address 0x6dfbc
/*
 * Offset 0x6DFBC
 * D:\driver2\game\C\PEDEST.C (line 1191)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ ProcessTannerPad(struct PEDESTRIAN *pPed /*$s1*/, unsigned long pad /*$a1*/, char PadSteer /*$a2*/, char use_analogue /*$a3*/)
{ // line 1, address 0x6dfbc
	struct VECTOR vec; // stack address -88
	int mapheight; // $s2
	struct VECTOR normal; // stack address -72
	struct VECTOR out; // stack address -56
	struct _sdPlane *SurfacePtr; // stack address -24
	{ // line 33, address 0x6e030
		struct VECTOR tVec; // stack address -40
		struct _sdPlane *plane; // $v0
		int mH; // $v1
		int sI; // $a0
	} // line 86, address 0x6e16c
	{ // line 168, address 0x6e3f8
	} // line 174, address 0x6e458
} // line 176, address 0x6e458
/*
 * Offset 0x6E470
 * D:\driver2\game\C\PEDEST.C (line 1375)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ InitTanner()
{ // line 2, address 0x6e470
} // line 58, address 0x6e62c
/*
 * Offset 0x6E62C
 * D:\driver2\game\C\PEDEST.C (line 1466)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ InitPedestrians()
{ // line 2, address 0x6e62c
	int loop; // $a1
	struct SEATED_PEDESTRIANS *seatedptr; // $s2
} // line 47, address 0x6e72c
/*
 * Offset 0x6E72C
 * D:\driver2\game\C\PEDEST.C (line 1623)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ ActivatePlayerPedestrian(struct _CAR_DATA *pCar /*$s6*/, char *padId /*stack 4*/, int direction /*$a1*/, long *position[4] /*$a3*/, int playerType /*stack 16*/)
{ // line 1, address 0x6e72c
	struct PEDESTRIAN *pPed; // $s1
	struct PEDESTRIAN *pSPed; // $a0
	struct VECTOR v; // stack address -72
	int nx; // $s4
	int nz; // $s2
	long w; // $s0
	long x; // $s5
	long y; // stack address -52
	long z; // $s1
	long d; // stack address -48
	int side; // $fp
	int id; // $s3
	{ // line 65, address 0x6e83c
		{ // line 140, address 0x6eab0
		} // line 140, address 0x6eab0
		{ // line 184, address 0x6ebb0
		} // line 184, address 0x6ebb0
	} // line 184, address 0x6ebb0
} // line 212, address 0x6ecf0
/*
 * Offset 0x6ECF0
 * D:\driver2\game\C\PEDEST.C (line 1877)
 * Stack frame base $sp, length 168
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ PlaceRoadBlockCops()
{ // line 2, address 0x6ecf0
	struct _CAR_DATA *pCar; // $a0
	struct _CAR_DATA *pCopCars[16]; // stack address -152
	int numCops; // $fp
	{ // line 19, address 0x6ed84
		int x; // $s2
		int z; // $s0
		int w; // $s0
		int i; // $s7
		int s1; // $s1
		int s2; // $a3
		struct VECTOR vert; // stack address -88
		long disp[4]; // stack address -72
		long dir[4]; // stack address -56
		int alpha; // $s1
	} // line 89, address 0x6f044
} // line 91, address 0x6f044
/*
 * Offset 0x6F074
 * D:\driver2\game\C\PEDEST.C (line 1975)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ CreatePedAtLocation(long *pPos[4] /*$s2*/, int pedType /*$s1*/)
{ // line 1, address 0x6f074
	struct PEDESTRIAN *pPed; // $s0
} // line 70, address 0x6f1d4
/*
 * Offset 0x6F1D4
 * D:\driver2\game\C\PEDEST.C (line 2168)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ ControlPedestrians()
{ // line 2, address 0x6f1d4
	struct PEDESTRIAN *pPed; // $s0
	struct PEDESTRIAN *pPedNext; // $s2
	struct _CAR_DATA *pCar; // $v0
	{ // line 57, address 0x6f2d4
	} // line 65, address 0x6f318
} // line 73, address 0x6f344
/*
 * Offset 0x6F344
 * D:\driver2\game\C\PEDEST.C (line 2385)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ PedDoNothing(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x6F614
 * D:\driver2\game\C\PEDEST.C (line 2523)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ PedUserRunner(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x6f614
} // line 109, address 0x6f874
/*
 * Offset 0x6F874
 * D:\driver2\game\C\PEDEST.C (line 2827)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ SetupGetOutCar(struct PEDESTRIAN *pPed /*$s5*/, struct _CAR_DATA *pCar /*$s3*/, int side /*$s7*/)
{ // line 1, address 0x6f874
	int alpha; // $s2
	long disp[4]; // stack address -80
	long dir[4]; // stack address -64
	struct SVECTOR vert; // stack address -48
	int x; // $s4
	int z; // $s0
	int a; // $s6
	int nx; // $a3
	int nz; // $a1
} // line 64, address 0x6faa4
/*
 * Offset 0x6FAA4
 * D:\driver2\game\C\PEDEST.C (line 2898)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ SetupGetInCar(struct PEDESTRIAN *pPed /*$s2*/)
{ // line 1, address 0x6faa4
	int alpha; // $s1
	long disp[4]; // stack address -72
	long dir[4]; // stack address -56
	struct SVECTOR vert; // stack address -40
	{ // line 36, address 0x6fb94
		int x; // $t1
		int z; // $t2
		int a; // $a0
		int nx; // $a3
		int nz; // $a1
	} // line 59, address 0x6fc8c
	{ // line 70, address 0x6fcd8
		long pos[4]; // stack address -32
	} // line 71, address 0x6fcd8
} // line 90, address 0x6fd70
/*
 * Offset 0x6FD70
 * D:\driver2\game\C\PEDEST.C (line 3074)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ TannerCameraHandler(struct PEDESTRIAN *pPed /*$a0*/)
{ // line 2, address 0x6fd70
	int padsteer; // $a3
	int maxY; // $t1
	int maxX; // $t5
	int range; // $t0
	int minX; // $t4
	int extra; // $a3
} // line 76, address 0x6ffb0
/*
 * Offset 0x6FFB0
 * D:\driver2\game\C\PEDEST.C (line 3157)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: ra
 */
void /*$ra*/ TannerSitDown(struct PEDESTRIAN *pPed /*$a2*/)
{ // line 1, address 0x6ffb0
	struct VECTOR angle; // stack address -24
} // line 62, address 0x70138
/*
 * Offset 0x70138
 * D:\driver2\game\C\PEDEST.C (line 3227)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ AnimatePed(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x70138
	{ // line 11, address 0x70158
		int mapheight; // $a3
		int reverse; // $s1
		{ // line 14, address 0x70158
			struct VECTOR vec; // stack address -32
		} // line 39, address 0x701c4
		{ // line 103, address 0x70374
			int sfc; // $v1
		} // line 108, address 0x70424
	} // line 121, address 0x704d0
} // line 123, address 0x704d0
/*
 * Offset 0x704E4
 * D:\driver2\game\C\PEDEST.C (line 3447)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ PingInPedestrians()
{ // line 2, address 0x704e4
	int bFound; // $s1
	struct VECTOR randomLoc; // stack address -88
	struct VECTOR baseLoc; // stack address -72
	int i; // $s2
	int pingInDist; // $a2
	struct VECTOR position; // stack address -56
	struct VECTOR target; // stack address -40
	struct PEDESTRIAN *pedestrian; // $s1
	{ // line 37, address 0x70580
		{ // line 55, address 0x70660
			struct PEDESTRIAN *pPed; // $a2
			{ // line 73, address 0x70690
				int x; // $v1
				int z; // $v0
				int radius; // $v1
			} // line 75, address 0x70690
		} // line 77, address 0x706dc
	} // line 79, address 0x706dc
	{ // line 87, address 0x70714
		{ // line 136, address 0x7085c
			int rval; // $v1
		} // line 175, address 0x708c0
	} // line 180, address 0x708c0
} // line 185, address 0x708c0
/*
 * Offset 0x708E0
 * D:\driver2\game\C\PEDEST.C (line 3685)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ FindPointOfCollision(struct _CAR_DATA *pCar /*$s3*/, struct VECTOR *pPos /*$a1*/)
{ // line 1, address 0x708e0
	int tb1; // $v1
	int tb2; // $v0
	int minX; // $a3
	int maxX; // $t0
	int minZ; // $v0
	int maxZ; // $a0
	int x; // $t1
	int z; // $a1
	int s1; // $a2
	int s2; // $v1
	int carLength[2]; // stack address -40
	static struct CRET2D collisionResult; // address 0x0
} // line 68, address 0x70b04
/*
 * Offset 0x70B04
 * D:\driver2\game\C\PEDEST.C (line 3762)
 * Stack frame base $sp, length 136
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ TannerCarCollisionCheck(struct VECTOR *pPos /*$s5*/, int dir /*$a1*/, int bQuick /*stack 8*/)
{ // line 1, address 0x70b04
	int carLength[2]; // stack address -120
	struct _CAR_DATA *cp0; // $s0
	struct _CAR_DATA *cp1; // $s1
	static struct CRET2D collisionResult; // address 0x30
	unsigned int dNewLBODY[2]; // stack address -112
	int speed; // $v0
	{ // line 36, address 0x70b94
		{ // line 36, address 0x70b94
		} // line 36, address 0x70b94
		{ // line 53, address 0x70c6c
			struct VECTOR velocity; // stack address -104
			long pointVel[4]; // stack address -88
			long reaction[4]; // stack address -72
			long lever[4]; // stack address -56
			int strikeVel; // $t1
			{ // line 84, address 0x70dec
			} // line 95, address 0x70dec
			{ // line 99, address 0x70e18
				int twistY; // $a2
				int lever_dot_n; // $a0
				int displacementsquared; // $a1
				int denom; // $a0
			} // line 112, address 0x70ef4
		} // line 133, address 0x71040
	} // line 142, address 0x71070
} // line 145, address 0x710bc
/*
 * Offset 0x710BC
 * D:\driver2\game\C\PEDEST.C (line 3946)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ SetupCivJump(struct PEDESTRIAN *pPed /*$s1*/, struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x710bc
	long disp[4]; // stack address -48
	long dir[4]; // stack address -32
	int angle; // $s0
	{ // line 14, address 0x71128
		short scale; // $a2
	} // line 21, address 0x7114c
	{ // line 62, address 0x71250
	} // line 81, address 0x71314
} // line 94, address 0x7138c
/*
 * Offset 0x7138C
 * D:\driver2\game\C\PEDEST.C (line 4101)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ CivPedWalk(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x7138c
	int turn; // $a1
	int offset1; // $t0
	int offset2; // $v1
	int lookahead; // $s3
	int speed; // $s1
} // line 81, address 0x71664
/*
 * Offset 0x71664
 * D:\driver2\game\C\PEDEST.C (line 4508)
 * Stack frame base $sp, length 32
 */
void /*$ra*/ CorrectPathPosition(struct PEDESTRIAN *pedestrian /*$a0*/, struct VECTOR *position /*$a1*/)
{ // line 2, address 0x71664
	struct VECTOR vec; // stack address -16
} // line 102, address 0x71664
/*
 * Offset 0x71670
 * D:\driver2\game\C\PEDEST.C (line 4619)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ CalcPedestrianDirection(int last_dir /*$a0*/, int wx /*$s5*/, int wz /*$s6*/, struct VECTOR *target /*$s3*/)
{ // line 1, address 0x71670
	int dir; // $s2
	int num; // $s1
	int rx; // $v1
	int rz; // $a0
	int mask; // $s0
	{ // line 50, address 0x71728
	} // line 62, address 0x71774
} // line 115, address 0x71814
/*
 * Offset 0x71814
 * D:\driver2\game\C\PEDEST.C (line 4984)
 * Stack frame base $sp, length 0
 */
struct SEATED_PEDESTRIANS * /*$ra*/ FindTannerASeat(struct PEDESTRIAN *pPed /*$t4*/)
{ // line 1, address 0x71814
	struct SEATED_PEDESTRIANS *seatedptr; // $a2
	struct SEATED_PEDESTRIANS *theOne; // $t1
	int dx; // $a0
	int dz; // $v1
	int distsqr; // $v0
	int bestSqr; // $t2
} // line 39, address 0x71930
/*
 * Offset 0x71930
 * D:\driver2\game\C\PEDEST.C (line 5031)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ add_seated(struct SEATED_PEDESTRIANS *seatedptr /*$s0*/, int seat_index /*$s2*/)
{ // line 1, address 0x71930
	struct PEDESTRIAN *pedestrian; // $s1
	int index; // $v0
} // line 45, address 0x71aac
/*
 * Offset 0x71AC4
 * D:\driver2\game\C\PEDEST.C (line 5084)
 * Stack frame base $sp, length 16
 */
void /*$ra*/ set_coll_box(int index /*$t2*/, struct _CAR_DATA *cp /*$t0*/, int address /*$t3*/)
{ // line 1, address 0x71ac4
	struct VECTOR BoxCentre; // stack address -16
	int boxsize; // $t1
} // line 26, address 0x71bdc
/*
 * Offset 0x71BE4
 * D:\driver2\game\C\PEDEST.C (line 5118)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ BuildCarCollisionBox()
{ // line 2, address 0x71be4
	struct _CAR_DATA *cp; // $s3
	int count1; // $s4
	int i; // $t1
	{ // line 28, address 0x71d24
		int x; // $a0
		int z; // $a2
	} // line 37, address 0x71dc0
} // line 53, address 0x71e74
/*
 * Offset 0x71E74
 * D:\driver2\game\C\PEDEST.C (line 5249)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ CalculatePedestrianInterest(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x71e74
	int interest; // $a2
	int dist; // $v1
	struct _CAR_DATA *pCar; // $a2
	struct VECTOR v1; // stack address -40
	struct VECTOR v2; // stack address -24
} // line 69, address 0x71fac
/*
 * Offset 0x71FBC
 * D:\driver2\game\C\PEDEST.C (line 1521)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DestroyPedestrians()
{ // line 2, address 0x71fbc
} // line 13, address 0x7201c
/*
 * Offset 0x7201C
 * D:\driver2\game\C\PEDEST.C (line 1567)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ DestroyPedestrian(struct PEDESTRIAN *pPed /*$a1*/)
{ // line 1, address 0x7201c
	{ // line 38, address 0x720cc
		struct SEATED_PEDESTRIANS *seatedptr; // $a0
	} // line 41, address 0x720f8
} // line 49, address 0x72114
/*
 * Offset 0x72114
 * D:\driver2\game\C\PEDEST.C (line 1842)
 * Stack frame base $sp, length 0
 */
struct PEDESTRIAN * /*$ra*/ CreatePedestrian()
{ // line 2, address 0x72114
} // line 27, address 0x7217c
/*
 * Offset 0x72184
 * D:\driver2\game\C\PEDEST.C (line 4221)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ HandlePedestrians()
{ // line 2, address 0x72184
} // line 236, address 0x721c4
/*
 * Offset 0x721D4
 * D:\driver2\game\C\PEDEST.C (line 3357)
 * Stack frame base $sp, length 80
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DeActivatePlayerPedestrian(struct PEDESTRIAN *pPed /*$s3*/)
{ // line 1, address 0x721d4
	int distToCarSq; // stack address -32
	struct _CAR_DATA *closestCar; // $s1
	struct _PLAYER *pPlayer; // $v0
	struct VECTOR point; // stack address -48
	int getIn; // $s2
	{ // line 27, address 0x72284
	} // line 38, address 0x722dc
} // line 39, address 0x722f8
/*
 * Offset 0x722F8
 * D:\driver2\game\C\PEDEST.C (line 2052)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawAllPedestrians()
{ // line 2, address 0x722f8
	struct PEDESTRIAN *pPed; // $s0
	int pedType; // $s2
	struct MATRIX mStore; // stack address -56
	{ // line 19, address 0x72384
		{ // line 26, address 0x723b4
		} // line 26, address 0x723b4
	} // line 33, address 0x723cc
	{ // line 49, address 0x7243c
	} // line 54, address 0x72468
} // line 85, address 0x72498
/*
 * Offset 0x72498
 * D:\driver2\game\C\PEDEST.C (line 2145)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ TannerActionHappening()
{ // line 2, address 0x72498
	struct PEDESTRIAN *pPed; // $a0
} // line 13, address 0x724e0
/*
 * Offset 0x724E0
 * D:\driver2\game\C\PEDEST.C (line 1440)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetTannerPosition(struct VECTOR *pVec /*$a0*/)
{ // line 1, address 0x724e0
	struct PEDESTRIAN *pPed; // $a1
} // line 19, address 0x72568
/*
 * Offset 0x72568
 * D:\driver2\game\C\PEDEST.C (line 4924)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetPedestrianTurn(struct PEDESTRIAN *pedestrian /*$a0*/, int turn /*$a1*/)
{ // line 1, address 0x72568
	int dir; // $a2
	int speed; // $v1
} // line 11, address 0x725ec
/*
 * Offset 0x725EC
 * D:\driver2\game\C\PEDEST.C (line 5325)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ PedSurfaceType(struct VECTOR *ped_pos /*$a0*/)
{ // line 5, address 0x725ec
	struct _sdPlane *sfc_ptr; // $v0
} // line 10, address 0x72620
/*
 * Offset 0x72620
 * D:\driver2\game\C\PEDEST.C (line 4845)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ IsPavement(int x /*$a0*/, int y /*$a1*/, int z /*$a2*/, struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x72620
	struct VECTOR vec; // stack address -24
	int r; // $v1
} // line 72, address 0x726ac
/*
 * Offset 0x726AC
 * D:\driver2\game\C\PEDEST.C (line 4943)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
struct SEATED_PEDESTRIANS * /*$ra*/ FindSeated()
{ // line 2, address 0x726ac
	struct SEATED_PEDESTRIANS *seatedptr; // $s0
	{ // line 7, address 0x726d4
		int dx; // $v1
		int dz; // $v0
		int distsqr; // $v1
		int count1; // $a2
	} // line 32, address 0x7278c
} // line 34, address 0x727a0
/*
 * Offset 0x727A0
 * D:\driver2\game\C\PEDEST.C (line 5178)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
struct _CAR_DATA * /*$ra*/ CheckForCar(struct PEDESTRIAN *pedestrian /*$s3*/)
{ // line 1, address 0x727a0
	int count; // $s0
	{ // line 5, address 0x727d8
	} // line 26, address 0x727f8
	{ // line 28, address 0x7281c
	} // line 35, address 0x7281c
	{ // line 39, address 0x72868
	} // line 43, address 0x72884
} // line 45, address 0x728a4
/*
 * Offset 0x728A4
 * D:\driver2\game\C\PEDEST.C (line 4465)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ PedestrianActionInit_WalkToTarget(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x728a4
	int dir; // $v1
} // line 31, address 0x72920
/*
 * Offset 0x72930
 * D:\driver2\game\C\PEDEST.C (line 3060)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupTannerSitDown(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x7296C
 * D:\driver2\game\C\PEDEST.C (line 3026)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupPressButton(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x729AC
 * D:\driver2\game\C\PEDEST.C (line 2639)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ PedUserWalker(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x729ac
	static int speed; // address 0x80
} // line 55, address 0x72a78
/*
 * Offset 0x72A78
 * D:\driver2\game\C\PEDEST.C (line 2702)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ PedCarryOutAnimation(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x72BC4
 * D:\driver2\game\C\PEDEST.C (line 2994)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ PedGetInCar(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x72bc4
	long disp[4]; // stack address -48
	long dir[4]; // stack address -32
	struct SVECTOR vert; // stack address -16
} // line 24, address 0x72c54
/*
 * Offset 0x72C54
 * D:\driver2\game\C\PEDEST.C (line 2796)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ PedGetOutCar(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x72CF8
 * D:\driver2\game\C\PEDEST.C (line 3040)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ PedPressButton(struct PEDESTRIAN *pPed /*$v1*/)
{
}
/*
 * Offset 0x72D48
 * D:\driver2\game\C\PEDEST.C (line 3402)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ CivPedDoNothing(struct PEDESTRIAN *pPed /*$a0*/)
{
}
/*
 * Offset 0x72D50
 * D:\driver2\game\C\PEDEST.C (line 4190)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ CivPedSit(struct PEDESTRIAN *pPed /*$a0*/)
{ // line 2, address 0x72d50
} // line 18, address 0x72d58
/*
 * Offset 0x72D58
 * D:\driver2\game\C\PEDEST.C (line 4047)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ CivPedJump(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x72d58
} // line 26, address 0x72e08
/*
 * Offset 0x72E08
 * D:\driver2\game\C\PEDEST.C (line 2353)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ CopStand(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, address 0x72e08
	struct VECTOR v; // stack address -24
} // line 24, address 0x72e64
/*
 * Offset 0x72E64
 * D:\driver2\game\C\PEDEST.C (line 2325)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ CivGetIn(struct PEDESTRIAN *pPed /*$s2*/)
{ // line 1, address 0x72e64
	struct DRIVER2_STRAIGHT *str; // $s1
	struct DRIVER2_CURVE *crv; // $s0
	{ // line 1, address 0x72e64
	} // line 20, address 0x72f4c
} // line 21, address 0x72f4c
/*
 * Offset 0x72F4C
 * D:\driver2\game\C\PEDEST.C (line 3640)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ TannerCollision(struct PEDESTRIAN *pPed /*$s1*/)
{ // line 1, address 0x72f4c
} // line 35, address 0x73024
/*
 * Offset 0x73038
 * D:\driver2\game\C\PEDEST.C (line 1541)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ DestroyCivPedestrians()
{ // line 2, address 0x73038
	struct PEDESTRIAN *pPed; // $v1
	struct PEDESTRIAN *pHPed; // $s0
} // line 18, address 0x730a0
/*
 * Offset 0x730A0
 * D:\driver2\game\C\PEDEST.C (line 2256)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupDoNowt(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x730E4
 * D:\driver2\game\C\PEDEST.C (line 2275)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupWalker(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x73120
 * D:\driver2\game\C\PEDEST.C (line 2291)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupRunner(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x73164
 * D:\driver2\game\C\PEDEST.C (line 2302)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupBack(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x731A4
 * D:\driver2\game\C\PEDEST.C (line 3411)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ SetupCivPedRouteData(struct VECTOR *pPos /*$s1*/)
{ // line 1, address 0x731a4
	struct VECTOR baseLoc; // stack address -32
} // line 24, address 0x73260
/*
 * Offset 0x73260
 * D:\driver2\game\C\PEDEST.C (line 3915)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ PingOutPed(struct PEDESTRIAN *pPed /*$a2*/)
{ // line 1, address 0x73260
	int px; // $a0
	int pz; // $v1
	int ps; // $a0
} // line 23, address 0x732d8
/*
 * Offset 0x732D8
 * D:\driver2\game\C\PEDEST.C (line 4080)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ SetupCivPedWalk(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x73328
 * D:\driver2\game\C\PEDEST.C (line 5231)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ CheckForPlayerCar(struct PEDESTRIAN *pedestrian /*$a0*/, struct CAR_COLLISION_BOX *collision_box /*$a1*/)
{
}
/*
 * Offset 0x73390
 * D:\driver2\game\C\PEDEST.C (line 5344)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessChairLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}