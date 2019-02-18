
#include "../decomp_defs.h"

COP_DATA gCopData =
{ 0, 0, 0, 2048, 0, 4096, 2048, 3000000, { 0, 0, 0, 0, 0 } };

int speed1[] = { 0xCB, 0xD2, 0xD9 };
int speed2[] = { 0xEE, 0x10A, 0x126 };

char sqtbl[] = { 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x81, 0x81, 0x81, 0x82, 0x82, 0x83, 0x83, 0x83, 0x84,
	0x84, 0x85, 0x86, 0x86, 0x87, 0x88, 0x88, 0x89, 0x8A,
	0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x90, 0x91,
	0x92, 0x93, 0x94, 0x95, 0x96, 0x98, 0x99, 0x9A, 0x9B,
	0x9C, 0x9D, 0x9E, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA6,
	0xA7, 0xA8, 0xAA, 0xAB, 0xAC, 0xAE, 0xAF, 0xB0, 0xB2,
	0xB3, 0xB5};


/*
 * Offset 0x2D7F4
 * D:\driver2\game\C\COP_AI.C (line 593)
 * Stack frame base $sp, length 152
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ WibbleDownTheRoad(struct VECTOR *from /*$a0*/, int distance /*$s1*/, struct VECTOR *to /*$s5*/)
{ // line 1, address 0x2d7f4
	int th; // $s0
	int j; // $s3
	int thl[4]; // stack address -136
	struct VECTOR pos; // stack address -120
	struct VECTOR dir; // stack address -104
	{ // line 11, address 0x2d878
		struct VECTOR p2; // stack address -88
		struct VECTOR d2; // stack address -72
		int colour[3]; // stack address -56
	} // line 21, address 0x2d904
} // line 46, address 0x2da04
/*
 * Offset 0x2DA04
 * D:\driver2\game\C\COP_AI.C (line 643)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitCops()
{
}
/*
 * Offset 0x2DB40
 * D:\driver2\game\C\COP_AI.C (line 708)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ ControlCops()
{ // line 2, address 0x2db40
	{ // line 18, address 0x2db9c
		int playerID; // $v1
	} // line 21, address 0x2dbdc
	{ // line 41, address 0x2dcd4
		int heading; // $s1
		int rnd; // $s0
	} // line 66, address 0x2de04
	{ // line 76, address 0x2de64
		int copsWereInPursuit; // $a1
	} // line 90, address 0x2df04
	{ // line 93, address 0x2df14
	} // line 99, address 0x2df48
} // line 101, address 0x2df48
/*
 * Offset 0x2DF64
 * D:\driver2\game\C\COP_AI.C (line 845)
 * Stack frame base $sp, length 104
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ CopControl1(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, address 0x2df64
	int currentSpeed; // $s7
	int desiredSteerAngle; // $s4
	{ // line 48, address 0x2e02c
		int dx; // $a1
		int dz; // $a0
		{ // line 52, address 0x2e080
		} // line 60, address 0x2e0c0
	} // line 61, address 0x2e0c0
	{ // line 67, address 0x2e0d8
		struct VECTOR pos; // stack address -88
	} // line 77, address 0x2e2a4
	{ // line 90, address 0x2e2a4
		enum AIZone targetZone; // $a0
		struct VECTOR doordir; // stack address -72
		int targetFound; // $a1
		int cx; // $s5
		int cz; // $s6
		int dvx; // $s0
		int dvz; // $s3
		int dist; // $s2
		int framesToImpact; // $a1
		{ // line 139, address 0x2e3c8
			int dz; // $a1
			int idvx; // $v1
			int idvz; // $v0
		} // line 139, address 0x2e3c8
		{ // line 204, address 0x2e64c
			struct iVectNT path[2]; // stack address -56
			int slidevel; // $a3
			{ // line 260, address 0x2e950
				int plcrspd; // $a1
			} // line 263, address 0x2e9bc
		} // line 279, address 0x2ea90
		{ // line 295, address 0x2eae0
			int b; // $a0
		} // line 300, address 0x2eb28
		{ // line 304, address 0x2eb28
			int steerdif; // $v1
			int speeddif; // $a2
			int maxPower; // $a1
			{ // line 330, address 0x2ec20
				int sf; // $v1
			} // line 332, address 0x2ec38
		} // line 343, address 0x2eccc
	} // line 343, address 0x2eccc
	{ // line 352, address 0x2ecec
	} // line 356, address 0x2ed14
} // line 358, address 0x2ed14
/*
 * Offset 0x2ED40
 * D:\driver2\game\C\COP_AI.C (line 1368)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ ControlCopDetection()
{ // line 14, address 0x2ed40
	int dx; // $v1
	int dz; // $a0
	struct VECTOR vec; // stack address -64
	int ccx; // stack address -32
	int ccz; // stack address -28
	char *scratch; // $s4
	struct _CAR_DATA *lcp; // $s1
	{ // line 17, address 0x2ed40
		{ // line 17, address 0x2ed40
			int angry; // $v1
		} // line 23, address 0x2ee10
	} // line 23, address 0x2ee10
	{ // line 48, address 0x2ee64
		int dx; // $v1
		int dz; // $v0
	} // line 58, address 0x2eee4
	{ // line 66, address 0x2ef38
		int distanceToPlayer; // $s0
		int active; // $s2
		{ // line 1, address 0x2efd8
			struct _CAR_DATA *cp; // $s1
			int distanceToPlayer; // $s0
			{ // line 1, address 0x2efd8
				int farDist; // $v1
				int nearDist; // $v0
				char result; // $s2
				{ // line 1, address 0x2eff8
					int theta; // $v1
					struct VECTOR delta; // stack address -48
					{ // line 1, address 0x2f098
					} // line 1, address 0x2f09c
				} // line 1, address 0x2f09c
			} // line 1, address 0x2f09c
		} // line 1, address 0x2f09c
	} // line 84, address 0x2f0b8
	{ // line 110, address 0x2f1cc
	} // line 110, address 0x2f1cc
	{ // line 123, address 0x2f1f8
		{ // line 130, address 0x2f220
		} // line 150, address 0x2f290
	} // line 152, address 0x2f2a0
	{ // line 157, address 0x2f2c4
		int rnd; // $s0
		int dir; // $s1
	} // line 161, address 0x2f330
	{ // line 166, address 0x2f364
		int rnd; // $s0
		int dir; // $s1
	} // line 168, address 0x2f3fc
} // line 174, address 0x2f434
/*
 * Offset 0x2F434
 * D:\driver2\game\C\COP_AI.C (line 1583)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ControlNumberOfCops()
{ // line 2, address 0x2f434
	int numWantedCops; // $t2
	{ // line 5, address 0x2f434
		short *pTrigger; // $a2
	} // line 13, address 0x2f4bc
	{ // line 26, address 0x2f508
		int temp; // $a1
	} // line 41, address 0x2f5b4
	{ // line 50, address 0x2f5d8
		int num_closer; // $a2
		int cutOffDistance; // $a1
		{ // line 55, address 0x2f5e8
			struct _CAR_DATA *lcp; // $a0
			int tempDist; // $a3
			{ // line 64, address 0x2f614
				int copDist; // $v1
			} // line 75, address 0x2f634
		} // line 78, address 0x2f644
	} // line 81, address 0x2f650
} // line 88, address 0x2f674
/*
 * Offset 0x2F674
 * D:\driver2\game\C\COP_AI.C (line 824)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ CopControl(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, address 0x2f674
} // line 18, address 0x2f6e8
/*
 * Offset 0x2F6E8
 * D:\driver2\game\C\COP_AI.C (line 577)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ InitCopState(struct _CAR_DATA *cp /*$s0*/, char *extraData /*$a1*/)
{
}
/*
 * Offset 0x2F764
 * D:\driver2\game\C\COP_AI.C (line 1562)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ PassiveCopTasks(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, address 0x2f764
	{ // line 1, address 0x2f7d4
		struct _CAR_DATA *cp; // $s0
	} // line 1, address 0x2f82c
} // line 14, address 0x2f860
/*
 * Offset 0x2F860
 * D:\driver2\game\C\COP_AI.C (line 1267)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitCopData(struct COP_DATA *pCopData /*$a0*/)
{ // line 1, address 0x2f860
	short *pTrigger; // $v1
	short trigger; // $a2
} // line 14, address 0x2f8ac
/*
 * Offset 0x2F8AC
 * D:\driver2\game\C\COP_AI.C (line 1308)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ UpdateCopSightData()
{ // line 2, address 0x2f8ac
	int angry; // $v1
} // line 6, address 0x2f944

/*
 * Offset 0x2F944
 * D:\driver2\game\C\COP_AI.C (line 1231)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ FindCost(int x /*$a0*/, int z /*$a1*/, int dvx /*$a2*/, int dvz /*$a3*/)
{ // line 1, address 0x2f944
	int tx; // $v0
	int tz; // $v0
	int dx; // $a2
	int dz; // $v1
	int d; // $v0
} // line 13, address 0x2f9fc