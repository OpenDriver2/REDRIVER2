#include "../decomp_defs.h"

int roadblockDelayDiff[] = { 1500, 1000, 800 };

char speedLimits[3] = { 56, 97, 138 };

CIV_PING civPingTest = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char modelRandomList[] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 1, 0, 4 };

/*
 * Offset 0x23E50
 * D:\driver2\game\C\CIV_AI.C (line 717)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ InitCar(struct _CAR_DATA *cp /*$s0*/, int direction /*$s6*/, long *startPos[4] /*$s2*/, unsigned char control /*$s4*/, int model /*stack 16*/, int palette /*stack 20*/, char *extraData /*stack 24*/)
{ // line 1, address 0x23e50
	struct VECTOR tmpStart; // stack address -48
} // line 69, address 0x24090
/*
 * Offset 0x24090
 * D:\driver2\game\C\CIV_AI.C (line 981)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ GetNextRoadInfo(struct _CAR_DATA *cp /*$s7*/, int randomExit /*$a1*/, int *turnAngle /*stack 8*/, int *startDist /*stack 12*/, struct CIV_ROUTE_ENTRY *oldNode /*stack 16*/)
{ // line 1, address 0x24090
	int oldOppDir; // $s4
	int i; // $a1
	int j; // $s6
	int newRoad; // $s3
	int numExits; // stack address -88
	int currentRoadExit; // $t6
	int newNumLanes; // $a3
	int newDir; // stack address -84
	int oppDir; // $s0
	struct DRIVER2_JUNCTION *jn; // $t5
	struct DRIVER2_CURVE *cv; // $s1
	struct DRIVER2_STRAIGHT *st; // $s5
	struct DRIVER2_STRAIGHT *tmpSt; // $a2
	struct DRIVER2_CURVE *tmpCv; // $s1
	short *jnExit; // $a2
	int newLane; // $s2
	char leftLane; // stack address -80
	char rightLane; // stack address -76
	{ // line 61, address 0x2479c
		char relExitId; // $fp
		static char validExitRelIdx[4][3][2]; // address 0x0
		int addRoad; // $t9
		{ // line 1, address 0x2486c
			int currentRoadExit; // $t6
			int newRoadExit; // $fp
			{ // line 1, address 0x2486c
				int exitMod; // $a0
				int ret; // $a1
			} // line 1, address 0x248d8
		} // line 1, address 0x248d8
		{ // line 110, address 0x24c80
			int x; // $v1
			int z; // $v0
			int dir; // stack address -84
			struct DRIVER2_CURVE *cv; // $s1
			{ // line 110, address 0x24c80
			} // line 110, address 0x24c80
		} // line 110, address 0x24c80
		{ // line 131, address 0x250b0
			int exitId; // $a1
			{ // line 135, address 0x250d4
				char lane; // $v0
			} // line 151, address 0x2512c
			{ // line 1, address 0x251e8
				int currentRoadExit; // $t6
				{ // line 1, address 0x251e8
					int exitMod; // $a1
					int ret; // $a2
				} // line 1, address 0x25248
			} // line 1, address 0x25248
		} // line 166, address 0x25254
		{ // line 1, address 0x25254
			struct DRIVER2_JUNCTION *jn; // $t5
			int currentExit; // $a2
			int turnAngle; // $t1
			struct _CAR_DATA *cp; // $s7
			struct CIV_ROUTE_ENTRY *oldNode; // $t7
			{ // line 1, address 0x25254
				unsigned short jnFlags; // $a0
				int i; // $a1
				int exitId; // $a3
			} // line 1, address 0x25324
		} // line 1, address 0x25324
		{ // line 171, address 0x25324
			{ // line 192, address 0x257dc
				int x; // $v1
				int z; // $v0
				int dir; // stack address -84
				struct DRIVER2_CURVE *cv; // $s1
				{ // line 192, address 0x257dc
				} // line 192, address 0x257dc
			} // line 192, address 0x257dc
		} // line 203, address 0x25c30
	} // line 203, address 0x25c30
	{ // line 211, address 0x25c38
		int i; // $a1
		int dx; // $v1
		int dz; // $a0
		int numLanes; // $fp
		int *pNewLane; // $s3
		int laneFromLeft; // $a3
		int laneFromRight; // $v1
		{ // line 274, address 0x2604c
			int preferredNewLane; // $t1
		} // line 302, address 0x2637c
		{ // line 305, address 0x263b0
			int preferredNewLane; // $s4
			{ // line 305, address 0x263b0
				int x; // $v1
				int z; // $v0
				struct DRIVER2_CURVE *cv; // $s1
				{ // line 305, address 0x263b0
				} // line 305, address 0x263b0
			} // line 305, address 0x263b0
		} // line 332, address 0x26704
	} // line 345, address 0x2680c
} // line 369, address 0x269cc
/*
 * Offset 0x269CC
 * D:\driver2\game\C\CIV_AI.C (line 1365)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ InitNodeList(struct _CAR_DATA *cp /*$s6*/, char *extraData /*$s7*/)
{ // line 1, address 0x269cc
	int i; // $v1
	struct CIV_ROUTE_ENTRY *cr; // $s5
	int dx; // $s1
	int dz; // $s2
	int surfInd; // $s4
	{ // line 32, address 0x26a6c
		int theta; // $s0
		int laneDist; // $s1
		struct DRIVER2_STRAIGHT *str; // $s3
	} // line 41, address 0x26bc8
	{ // line 46, address 0x26c04
		struct DRIVER2_CURVE *crv; // $s0
	} // line 50, address 0x26cb4
} // line 60, address 0x26d14
/*
 * Offset 0x26D14
 * D:\driver2\game\C\CIV_AI.C (line 1441)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetNodePos(struct DRIVER2_STRAIGHT *straight /*$t1*/, struct DRIVER2_JUNCTION *junction /*$a1*/, struct DRIVER2_CURVE *curve /*$t0*/, int distAlongPath /*$a3*/, struct _CAR_DATA *cp /*stack 16*/, int *x /*stack 20*/, int *z /*stack 24*/, int laneNo /*stack 28*/)
{ // line 1, address 0x26d14
	unsigned char oldLane; // $a0
	unsigned char changeLaneCount; // $t3
} // line 63, address 0x26f88
/*
 * Offset 0x26F88
 * D:\driver2\game\C\CIV_AI.C (line 1507)
 * Stack frame base $sp, length 136
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CheckChangeLanes(struct DRIVER2_STRAIGHT *straight /*$s4*/, struct DRIVER2_CURVE *curve /*$s6*/, int distAlongSegment /*$a2*/, struct _CAR_DATA *cp /*$s3*/, int tryToPark /*stack 16*/)
{ // line 1, address 0x26f88
	unsigned char currentLane; // $s7
	unsigned char newLane; // $s2
	unsigned char trials; // $t3
	unsigned char canProceed; // stack address -88
	unsigned char travelAlongRoad; // $s5
	unsigned char turnRight; // stack address -84
	struct _CAR_DATA *cp1; // $s0
	struct CIV_ROUTE_ENTRY tmpNode; // stack address -120
	{ // line 65, address 0x272f8
		struct VECTOR pos; // stack address -104
		int theta; // $a0
		int length; // $a1
		{ // line 81, address 0x273fc
		} // line 89, address 0x274fc
	} // line 91, address 0x2750c
} // line 116, address 0x27598
/*
 * Offset 0x27598
 * D:\driver2\game\C\CIV_AI.C (line 1637)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CreateNewNode(struct _CAR_DATA *cp /*$s4*/)
{ // line 1, address 0x27598
	int oldRoad; // $s1
	int cr; // $a3
	struct CIV_ROUTE_ENTRY *newNode; // $s6
	struct CIV_ROUTE_ENTRY *oldNode; // $s3
	struct DRIVER2_CURVE *curve; // $s0
	struct DRIVER2_STRAIGHT *straight; // $s5
	int turnAngle; // stack address -56
	{ // line 1, address 0x27598
		struct _CAR_DATA *cp; // $s4
		struct CIV_ROUTE_ENTRY *currentNode; // $v1
		{ // line 1, address 0x27598
			struct CIV_ROUTE_ENTRY *retNode; // $a0
		} // line 1, address 0x275e4
	} // line 1, address 0x275e4
	{ // line 1, address 0x275f4
		struct _CAR_DATA *cp; // $s4
		{ // line 1, address 0x275f4
			struct CIV_ROUTE_ENTRY *retNode; // $a0
		} // line 1, address 0x27604
	} // line 1, address 0x27604
	{ // line 1, address 0x27610
		struct _CAR_DATA *cp; // $s4
		{ // line 1, address 0x27610
			struct CIV_ROUTE_ENTRY *retNode; // $a0
		} // line 1, address 0x27620
	} // line 1, address 0x27620
	{ // line 1, address 0x2762c
		struct _CAR_DATA *cp; // $s4
		{ // line 1, address 0x2762c
			struct CIV_ROUTE_ENTRY *retNode; // $a0
		} // line 1, address 0x2763c
	} // line 1, address 0x2763c
	{ // line 16, address 0x27658
		struct _CAR_DATA *cp; // $s4
		struct CIV_ROUTE_ENTRY *currentNode; // $s3
		{ // line 16, address 0x27658
			struct CIV_ROUTE_ENTRY *retNode; // $v1
		} // line 16, address 0x27658
	} // line 16, address 0x27658
	{ // line 18, address 0x27658
		{ // line 1, address 0x27658
			struct _CAR_DATA *cp; // $s4
			{ // line 1, address 0x27658
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 1, address 0x27668
		} // line 1, address 0x27668
	} // line 21, address 0x27678
	{ // line 22, address 0x2769c
		struct _CAR_DATA *cp; // $s4
		struct CIV_ROUTE_ENTRY *currentNode; // $s3
		{ // line 22, address 0x2769c
			struct CIV_ROUTE_ENTRY *retNode; // $s2
		} // line 22, address 0x276b4
	} // line 22, address 0x276b4
	{ // line 44, address 0x27750
		int travelDir; // $a1
		int segmentEnd; // $a0
		{ // line 51, address 0x27818
			int startDist; // stack address -52
		} // line 51, address 0x27870
	} // line 51, address 0x27880
	{ // line 55, address 0x278b4
		int travelDir; // $a2
		int segmentEnd; // $t0
		{ // line 62, address 0x279bc
			int startDist; // stack address -48
		} // line 62, address 0x279f8
	} // line 63, address 0x27a0c
	{ // line 80, address 0x27a80
		struct CIV_ROUTE_ENTRY tmpNode; // stack address -72
		{ // line 84, address 0x27ac0
			int travelDir; // $a0
		} // line 95, address 0x27b80
		{ // line 102, address 0x27bf8
			struct _CAR_DATA *playerCar; // $v0
			int dx; // $v1
			int dz; // $a0
		} // line 107, address 0x27c68
		{ // line 114, address 0x27ca0
			int tryToPark; // $s1
		} // line 136, address 0x27e08
		{ // line 142, address 0x27e6c
			int radOfCrv; // $s5
			int cornerAngle; // $a3
			int segLength; // $s0
			int tmp; // $a1
			int dx; // $s1
			int dz; // $s0
			{ // line 152, address 0x27f24
				struct _CAR_DATA *cp; // $s4
				{ // line 152, address 0x27f24
					struct CIV_ROUTE_ENTRY *retNode; // $a0
				} // line 155, address 0x27fac
			} // line 155, address 0x27fac
			{ // line 163, address 0x27fe0
				struct _CAR_DATA *cp; // $s4
				{ // line 163, address 0x27fe0
					struct CIV_ROUTE_ENTRY *retNode; // $a0
				} // line 166, address 0x28074
			} // line 166, address 0x28074
		} // line 169, address 0x28074
		{ // line 173, address 0x28074
			{ // line 1, address 0x28074
				struct _CAR_DATA *cp; // $s4
				struct CIV_ROUTE_ENTRY *currentNode; // $s6
				{ // line 1, address 0x28074
					struct CIV_ROUTE_ENTRY *retNode; // $v0
				} // line 1, address 0x28074
			} // line 1, address 0x28074
		} // line 177, address 0x28084
	} // line 177, address 0x28084
} // line 191, address 0x28140
/*
 * Offset 0x28140
 * D:\driver2\game\C\CIV_AI.C (line 1843)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ InitCivState(struct _CAR_DATA *cp /*$s1*/, char *extraData /*$s2*/)
{ // line 1, address 0x28140
	struct CIV_STATE *cs; // $s0
} // line 44, address 0x28350
/*
 * Offset 0x28350
 * D:\driver2\game\C\CIV_AI.C (line 2016)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ PingOutAllSpecialCivCars()
{ // line 2, address 0x28350
	struct _CAR_DATA *lcp; // $s0
	{ // line 1, address 0x283b0
		struct _CAR_DATA *cp; // $s0
	} // line 1, address 0x2844c
} // line 9, address 0x28474
/*
 * Offset 0x28474
 * D:\driver2\game\C\CIV_AI.C (line 2028)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ PingOutAllCivCarsAndCopCars()
{ // line 2, address 0x28474
	struct _CAR_DATA *lcp; // $s0
	{ // line 1, address 0x284b4
		struct _CAR_DATA *cp; // $s0
	} // line 1, address 0x28594
} // line 9, address 0x285bc
/*
 * Offset 0x285BC
 * D:\driver2\game\C\CIV_AI.C (line 2050)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ CheckPingOut(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x285bc
	int dx; // $a0
	int dz; // $v1
	int dist; // $s1
	{ // line 1, address 0x28620
		struct _CAR_DATA *cp; // $s0
	} // line 1, address 0x286fc
} // line 31, address 0x28748
/*
 * Offset 0x28748
 * D:\driver2\game\C\CIV_AI.C (line 2176)
 * Stack frame base $sp, length 88
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ CreateCivCarWotDrivesABitThenStops(int direction /*$s5*/, long *startPos[4] /*$s2*/, long *stopPos[4] /*$a2*/, unsigned char internalModel /*$s4*/, int palette /*stack 16*/)
{ // line 1, address 0x28748
	struct _EXTRA_CIV_DATA civDat; // stack address -56
	struct _CAR_DATA *newCar; // $s1
	struct CIV_ROUTE_ENTRY *stopNode; // $a0
	struct CIV_ROUTE_ENTRY *spareNode; // $a1
	{ // line 1, address 0x28748
		{ // line 1, address 0x28748
			char *slot; // $v1
			struct _CAR_DATA *carCnt; // $a0
		} // line 8, address 0x287dc
	} // line 8, address 0x287dc
} // line 53, address 0x289c8
/*
 * Offset 0x289C8
 * D:\driver2\game\C\CIV_AI.C (line 2248)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 ra
 */
int /*$ra*/ CreateStationaryCivCar(int direction /*$t4*/, long orientX /*$s2*/, long orientZ /*$s1*/, long *startPos[4] /*$a2*/, int externalModel /*stack 16*/, int palette /*stack 20*/, int controlFlags /*stack 24*/)
{ // line 1, address 0x289c8
	struct _EXTRA_CIV_DATA civDat; // stack address -72
	struct _CAR_DATA *newCar; // $s0
	long tmpRes[4]; // stack address -48
	long tmpQ[4]; // stack address -32
	{ // line 1, address 0x28a84
		{ // line 1, address 0x28a84
			char *slot; // $v1
			struct _CAR_DATA *carCnt; // $a0
		} // line 1, address 0x28ad0
	} // line 1, address 0x28ad0
} // line 41, address 0x28e1c
/*
 * Offset 0x28E1C
 * D:\driver2\game\C\CIV_AI.C (line 2323)
 * Stack frame base $sp, length 160
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ PingInCivCar(int minPingInDist /*stack 0*/)
{ // line 1, address 0x28e1c
	struct _EXTRA_CIV_DATA civDat; // stack address -128
	int dir; // stack address -52
	int distAlongSegment; // $fp
	int lane; // $s7
	struct _CAR_DATA *newCar; // $s1
	struct DRIVER2_STRAIGHT *str; // $s6
	struct DRIVER2_CURVE *crv; // $s5
	unsigned char cookieCountStart; // $s4
	int curveLength; // stack address -48
	unsigned char model; // $s4
	unsigned char possibleLanes[12]; // stack address -104
	unsigned char carDistLanes[15]; // stack address -88
	char numPossibleLanes; // $s0
	int lbody; // $s3
	{ // line 1, address 0x28f54
		{ // line 1, address 0x28f54
			char *slot; // $a1
			struct _CAR_DATA *carCnt; // $a0
		} // line 1, address 0x28fa8
	} // line 1, address 0x28fa8
	{ // line 70, address 0x29068
		char newCarId; // $v1
		{ // line 1, address 0x290c0
			struct _CAR_DATA *cp; // $s1
		} // line 1, address 0x291a8
	} // line 79, address 0x2930c
	{ // line 139, address 0x29688
		char frog; // $a0
		char numLanes; // $a1
	} // line 139, address 0x297c8
	{ // line 148, address 0x298c8
		char frog; // $a0
		char numLanes; // $a1
	} // line 148, address 0x299cc
	{ // line 205, address 0x29cb0
		int externalModel; // $v0
		{ // line 212, address 0x29d2c
			unsigned char palette; // $v0
		} // line 216, address 0x29d88
	} // line 221, address 0x29dc4
	{ // line 227, address 0x29e20
		int theta; // $s0
		int minDistAlong; // $s2
	} // line 240, address 0x29f78
	{ // line 244, address 0x29fc0
		int minAngle; // $a1
	} // line 255, address 0x2a0f8
	{ // line 270, address 0x2a150
		long pos[4]; // stack address -72
		unsigned int distSq; // stack address -56
		{ // line 270, address 0x2a150
			int *distToCarSq; // $t2
			{ // line 270, address 0x2a150
				int dz; // $v1
				int dx; // $a0
				int distSq; // $v0
				unsigned int retDistSq; // $a2
				struct _CAR_DATA *lcp; // $a1
			} // line 278, address 0x2a290
		} // line 278, address 0x2a290
		{ // line 288, address 0x2a2a8
			int x; // $t2
			int y; // $a2
			int z; // $t1
			unsigned int distSq; // $a3
			{ // line 288, address 0x2a2a8
				int dz; // $v1
				int dx; // $a0
				int ret; // $t0
				struct _CAR_DATA *lcp; // $a1
			} // line 288, address 0x2a3a8
		} // line 288, address 0x2a3a8
	} // line 299, address 0x2a3e4
} // line 333, address 0x2a52c
/*
 * Offset 0x2A52C
 * D:\driver2\game\C\CIV_AI.C (line 2659)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ AttemptUnPark(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, address 0x2a52c
	struct DRIVER2_STRAIGHT *str; // $s2
	struct DRIVER2_CURVE *crv; // $s3
} // line 31, address 0x2a664
/*
 * Offset 0x2A664
 * D:\driver2\game\C\CIV_AI.C (line 2798)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ CivAccelTrafficRules(struct _CAR_DATA *cp /*$t3*/, int *distToNode /*$a1*/)
{ // line 1, address 0x2a664
	int lbody; // $t1
	int wbody; // $t2
	struct CIV_STATE *cs; // $a2
	{ // line 46, address 0x2a784
		int stopDist; // $t0
		{ // line 50, address 0x2a7fc
			int endSpeed; // $v0
		} // line 55, address 0x2a868
	} // line 56, address 0x2a868
	{ // line 65, address 0x2a8ac
		int ret; // $a1
		int properVel; // $v1
		int brakeDist; // $a3
		{ // line 103, address 0x2a980
			int endSpeed; // $v0
			int currentDist; // $v1
		} // line 103, address 0x2a980
	} // line 117, address 0x2aa54
	{ // line 125, address 0x2aa54
		int roadClear; // $t8
		int checkObstDist; // $t7
		int numLanes; // $v0
		{ // line 134, address 0x2aa74
			struct _CAR_DATA *cp; // $t3
			{ // line 134, address 0x2aa74
				struct _CAR_DATA *lcp; // $a3
				int normal; // $v0
				int tangent; // $a0
				int distToObstacle; // $t0
				int ccarAng; // $t1
				int scarAng; // $t2
			} // line 134, address 0x2ab94
		} // line 134, address 0x2ab94
		{ // line 1, address 0x2abac
			struct _CAR_DATA *cp; // $t3
			{ // line 1, address 0x2abac
				struct CIV_STATE *cs; // $v1
			} // line 1, address 0x2abac
		} // line 1, address 0x2abac
		{ // line 145, address 0x2abc0
			int ret; // $v1
		} // line 148, address 0x2ac10
	} // line 149, address 0x2ac10
} // line 151, address 0x2ac10
/*
 * Offset 0x2AC10
 * D:\driver2\game\C\CIV_AI.C (line 2950)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SetUpCivCollFlags()
{ // line 2, address 0x2ac10
	struct SVECTOR boxDisp; // stack address -72
	int carLength[2]; // stack address -64
	struct _CAR_DATA *cp0; // $s5
	struct _CAR_DATA *cp1; // $s2
	unsigned int dNewLBODY[2]; // stack address -56
	int dx; // $s0
	int dz; // stack address -48
	{ // line 35, address 0x2ac7c
		int extraLength; // $a2
	} // line 35, address 0x2acac
	{ // line 40, address 0x2addc
		{ // line 53, address 0x2ae2c
		} // line 53, address 0x2ae80
		{ // line 66, address 0x2afc8
			int civCD; // $s7
			int brake; // $a0
			{ // line 74, address 0x2aff8
				unsigned int *blth; // $v1
			} // line 74, address 0x2b028
			{ // line 83, address 0x2b088
				int i; // $a1
				int h; // $a3
				int rnd; // $a2
				struct _CAR_DATA *cp; // $s0
				{ // line 90, address 0x2b128
				} // line 98, address 0x2b1f8
			} // line 100, address 0x2b20c
		} // line 101, address 0x2b20c
	} // line 102, address 0x2b20c
	{ // line 106, address 0x2b230
		unsigned char i; // $s0
	} // line 115, address 0x2b2d4
} // line 116, address 0x2b2d4
/*
 * Offset 0x2B2D4
 * D:\driver2\game\C\CIV_AI.C (line 3074)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ CivAccel(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x2b2d4
	int ret; // $t1
	int distToNode; // stack address -16
	int dx; // $v1
	int dz; // $a0
	{ // line 32, address 0x2b3c4
		int tmpRet; // $a0
		int lbody; // $a0
		{ // line 37, address 0x2b3f0
			int sf; // $v1
			int c1; // $t0
			int c2; // $a3
			int c3; // $a1
			{ // line 52, address 0x2b4b4
				int tmp; // $v1
			} // line 55, address 0x2b520
		} // line 58, address 0x2b530
	} // line 72, address 0x2b590
} // line 75, address 0x2b5a4
/*
 * Offset 0x2B5A4
 * D:\driver2\game\C\CIV_AI.C (line 3166)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ CivSteerAngle(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x2b5a4
	int station; // $a3
	int step; // $s2
	int ret; // $a0
	struct VECTOR locPath; // stack address -56
	struct VECTOR pathPoint; // stack address -40
	int lbody; // $s3
	{ // line 1, address 0x2b5a4
		{ // line 1, address 0x2b5a4
			struct _CAR_DATA *cp; // $s0
			{ // line 1, address 0x2b5a4
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 9, address 0x2b5f8
		} // line 9, address 0x2b5f8
		{ // line 1, address 0x2b608
			struct _CAR_DATA *cp; // $s0
			{ // line 1, address 0x2b608
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 1, address 0x2b618
		} // line 1, address 0x2b618
		{ // line 1, address 0x2b628
			struct _CAR_DATA *cp; // $s0
			{ // line 1, address 0x2b628
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 1, address 0x2b638
		} // line 1, address 0x2b638
		{ // line 1, address 0x2b648
			struct _CAR_DATA *cp; // $s0
			{ // line 1, address 0x2b648
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 1, address 0x2b658
		} // line 1, address 0x2b658
	} // line 26, address 0x2b678
	{ // line 1, address 0x2b6e4
		struct _CAR_DATA *cp; // $s0
		{ // line 1, address 0x2b6e4
			struct CIV_ROUTE_ENTRY *retNode; // $a0
		} // line 1, address 0x2b6f8
	} // line 1, address 0x2b6f8
	{ // line 35, address 0x2b708
		struct CIV_ROUTE_ENTRY *crLoc; // $a1
		struct CIV_ROUTE_ENTRY *cr; // $a0
	} // line 46, address 0x2b768
	{ // line 1, address 0x2b7b0
		struct _CAR_DATA *cp; // $s0
		{ // line 1, address 0x2b7b0
			struct CIV_ROUTE_ENTRY *retNode; // $v1
		} // line 1, address 0x2b7c0
	} // line 1, address 0x2b7c0
	{ // line 70, address 0x2b8d8
		struct CIV_ROUTE_ENTRY *cr; // $a0
		{ // line 1, address 0x2b908
			struct _CAR_DATA *cp; // $s0
			{ // line 1, address 0x2b908
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 1, address 0x2b918
		} // line 1, address 0x2b918
	} // line 77, address 0x2b928
} // line 80, address 0x2b94c
/*
 * Offset 0x2B94C
 * D:\driver2\game\C\CIV_AI.C (line 3265)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CivFindStation(struct _CAR_DATA *cp /*$s6*/)
{ // line 1, address 0x2b94c
	struct CIV_ROUTE_ENTRY *rep; // $s3
	int cx; // stack address -48
	int cz; // $fp
	{ // line 1, address 0x2b94c
		int loop; // $a0
		{ // line 1, address 0x2b9a4
			struct _CAR_DATA *cp; // $s6
			{ // line 1, address 0x2b9a4
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 1, address 0x2b9b8
		} // line 1, address 0x2b9b8
	} // line 12, address 0x2b9c4
	{ // line 15, address 0x2b9cc
		struct _CAR_DATA *cp; // $s6
		struct CIV_ROUTE_ENTRY *currentNode; // $s3
		{ // line 15, address 0x2b9cc
			struct CIV_ROUTE_ENTRY *retNode; // $s0
		} // line 15, address 0x2b9cc
	} // line 15, address 0x2b9cc
	{ // line 17, address 0x2b9cc
		int sx; // $s5
		int sz; // $s4
		int dx; // $s2
		int dz; // $s1
		int stepsize; // $a1
		int square; // $a0
		{ // line 44, address 0x2ba90
			struct _CAR_DATA *cp; // $s6
			struct CIV_ROUTE_ENTRY *currentNode; // $s3
			{ // line 44, address 0x2ba90
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 44, address 0x2baa0
		} // line 44, address 0x2baa0
		{ // line 1, address 0x2bab0
			struct _CAR_DATA *cp; // $s6
			struct CIV_ROUTE_ENTRY *currentNode; // $s3
			{ // line 1, address 0x2bab0
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 1, address 0x2bac0
		} // line 1, address 0x2bac0
		{ // line 1, address 0x2bad0
			struct _CAR_DATA *cp; // $s6
			struct CIV_ROUTE_ENTRY *currentNode; // $s3
			{ // line 1, address 0x2bad0
				struct CIV_ROUTE_ENTRY *retNode; // $v1
			} // line 1, address 0x2bae0
		} // line 1, address 0x2bae0
	} // line 52, address 0x2baf8
} // line 55, address 0x2bb54
/*
 * Offset 0x2BB54
 * D:\driver2\game\C\CIV_AI.C (line 3337)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CivFindPointOnPath(struct _CAR_DATA *cp /*$s7*/, int station /*$s2*/, struct VECTOR *ppoint /*$fp*/)
{ // line 1, address 0x2bb54
	struct CIV_ROUTE_ENTRY *cprep; // $a0
	struct CIV_ROUTE_ENTRY *start; // stack address -48
	{ // line 9, address 0x2bbb8
		struct _CAR_DATA *cp; // $s7
		struct CIV_ROUTE_ENTRY *currentNode; // $a0
		{ // line 9, address 0x2bbb8
			struct CIV_ROUTE_ENTRY *retNode; // $s0
		} // line 9, address 0x2bbb8
	} // line 9, address 0x2bbb8
	{ // line 11, address 0x2bbb8
		int sx; // $s4
		int sz; // $s5
		int dx; // $s1
		int dz; // $s3
		int stepsize; // $a2
	} // line 44, address 0x2bcf8
} // line 48, address 0x2bd5c
/*
 * Offset 0x2BD5C
 * D:\driver2\game\C\CIV_AI.C (line 3398)
 * Stack frame base $sp, length 120
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CreateRoadblock()
{ // line 2, address 0x2bd5c
	struct _CAR_DATA *cp; // $v1
	struct _CAR_DATA *lcp; // $s0
	struct _CAR_DATA *newCar; // $s0
	struct DRIVER2_STRAIGHT *str; // stack address -72
	struct DRIVER2_CURVE *crv; // $s7
	int distAlongSegment; // $s2
	int lbody; // $s4
	int dir; // $s6
	int numLanes; // stack address -68
	unsigned char externalCopModel; // stack address -64
	int delta; // $s4
	int noMoreCars; // stack address -60
	int newCarId; // $v1
	{ // line 2, address 0x2bd5c
		int dir; // $s0
	} // line 39, address 0x2c0e0
	{ // line 44, address 0x2c104
		int theta; // $s0
	} // line 53, address 0x2c200
	{ // line 57, address 0x2c248
		int minAngle; // $a3
		int curveLength; // $v1
	} // line 93, address 0x2c39c
	{ // line 80, address 0x2c460
		{ // line 85, address 0x2c530
		} // line 87, address 0x2c54c
		{ // line 1, address 0x2c5f8
			struct _CAR_DATA *cp; // $s0
		} // line 1, address 0x2c6dc
		{ // line 1, address 0x2c770
			struct _CAR_DATA *cp; // $s0
		} // line 1, address 0x2c84c
	} // line 112, address 0x2c85c
	{ // line 117, address 0x2c898
		struct VECTOR startPos2; // stack address -88
		int deltaAngle; // $a0
		int dir2NextRow; // $a1
		int faceDir; // $s1
		int numSpareCars; // $a0
		int count; // $s2
		int numSpots; // $fp
		{ // line 129, address 0x2c9b0
			int numCarsToAdd; // $s5
			{ // line 133, address 0x2c9e4
				{ // line 1, address 0x2cb2c
					struct _CAR_DATA *cp; // $s0
				} // line 1, address 0x2cc10
				{ // line 1, address 0x2cca4
					struct _CAR_DATA *cp; // $s0
				} // line 1, address 0x2cd80
			} // line 157, address 0x2cd90
		} // line 158, address 0x2cd9c
	} // line 159, address 0x2cd9c
} // line 166, address 0x2cddc
/*
 * Offset 0x2CE0C
 * D:\driver2\game\C\CIV_AI.C (line 2144)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitCivCars()
{ // line 2, address 0x2ce0c
} // line 13, address 0x2ce78
/*
 * Offset 0x2CE78
 * D:\driver2\game\C\CIV_AI.C (line 2699)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ CivControl(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x2ce78
	{ // line 1, address 0x2ce78
	} // line 1, address 0x2ce78
	{ // line 30, address 0x2cef4
	} // line 32, address 0x2cf28
} // line 41, address 0x2cf80
/*
 * Offset 0x2CF80
 * D:\driver2\game\C\CIV_AI.C (line 2116)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ TrafficLightCycle(int exit /*$a0*/)
{ // line 1, address 0x2cf80
	int timeCnt; // $v1
} // line 25, address 0x2cfe8
/*
 * Offset 0x2CFE8
 * D:\driver2\game\C\CIV_AI.C (line 1977)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ PingOutCar(struct _CAR_DATA *cp /*$s0*/)
{
}
/*
 * Offset 0x2D0EC
 * D:\driver2\game\C\CIV_AI.C (line 930)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ CivCarFX(struct _CAR_DATA *cp /*$s0*/)
{
}
/*
 * Offset 0x2D184
 * D:\driver2\game\C\CIV_AI.C (line 891)
 * Stack frame base $sp, length 0
 */
struct _CAR_DATA * /*$ra*/ FindClosestCar(int x /*$t4*/, int y /*$a1*/, int z /*$a2*/, int *distToCarSq /*$a3*/)
{ // line 1, address 0x2d184
	struct _CAR_DATA *retCar; // $t2
	struct _CAR_DATA *lcp; // $t0
	unsigned int retDistSq; // $t1
	int distSq; // $v0
	int dx; // $a0
	int dz; // $v1
} // line 24, address 0x2d288
/*
 * Offset 0x2D288
 * D:\driver2\game\C\CIV_AI.C (line 2084)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SetUpTrafficLightPhase()
{
}
/*
 * Offset 0x2D2B4
 * D:\driver2\game\C\CIV_AI.C (line 918)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
int /*$ra*/ NotTravellingAlongCurve(int x /*$a0*/, int z /*$a1*/, int dir /*$s0*/, struct DRIVER2_CURVE *cv /*$a3*/)
{ // line 1, address 0x2d2b4
} // line 9, address 0x2d300