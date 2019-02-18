#include "../decomp_defs.h"

int ElTrainData[83] = {
	6, 80, 130, 32768, 336284, -220364, 283420, -2147483646,
	-204500, -158924, 247580, -123084, 188624, -158924,
	73520, -138444, 17200, -124148, -39120, -2147483646,
	-109276, -82131, -80103, -17628, -203568, -124712,
	-39728, -265000, 129620, -386012, 2147483648, 80,
	130, 0, -158928, 189219, -123684, 246995, -2147483647,
	0, 90, 32768, 188402, -425768, 354291, 2147483648,
	0, 90, 32768, 354291, -425168, 188402, 2147483648,
	60, 110, 0, -386012, 130215, -264404, -39132, -124688,
	16619, -139048, 72943, -159520, 282863, -2147483646,
	-204991, -220964, 336284, 2147483648, 70, 120, 0,
	-82719, -39712, -2147483646, -115487, -124120, -202968,
	-18216, -80683, -2147483647
};

int VegasTrainData[7] = {
	123, 32768, 982000, -68855, 762717, 2147483648
};

int VegasParkedTrains[3] = {
	-68855, 975520, 792317
};

int HavanaFerryData[12] = {
	40, 0, 0, 425555, -452, 20000, 25, 0, 0, 315750, 130740, 135960
};

int RioFerryData[6] = {
	6, 0, 0, 200384, 387424, 410000
};

int HavanaMiniData[4] = {
	50, 3995, 4605, 0
};

int LiftingBridges[55] = {
	8, -182784, -175616, -168448, 7, -227328, -162304,
	-141824, -121344, -100864, -80384, -59904, 256, -312832,
	-305664, -298496, 1, 324096, -311808, -304640, -297472,
	1, 247296, -256512, -249344, -242176, 1, 247296,
	-262656, -255488, -248320, 1, 324096, 32768, 170496,
	177664, 184832, 1, -271360, -12800, -5632, 1536,
	5, -162304, -102912, -82432, -61952, -39936, -6656,
	512, 7680, 3, 4137, 27648, 128000
};


int ChicagoCameraHack[3] = {
	-208006, 198, 657039
};

int HavanaCameraHack[9] = {
	-491431, 3568, -139048, -453981, 409, -128009, -453975, 429, -127175
};

int VegasCameraHack[16] = {
	124092, 3988, 3494, -11285, 1559, 843824, -38801,
	2681, 273148, -36925, 2048, 269647, 273935, -65503, 1617, 796775
};

int RioCameraHack[6] = {
	-276620, 3072, -321920, -40920, 3623, 382170
};

MissionTrain missionTrain[2] =
{
	{ 0, ElTrainData+4, 100, 150, 200, 289051, 32768 },
	{ 0, ElTrainData+7, 125, 145, 215, 4294762796, 0 }
};

FixedEvent chicagoDoor[3] =
{
  {
	{ 4294759680, 0, 659706, 0 },
	0,
	0,
	800u,
	0u,
	25u,
	50u,
	80,
	0,
	0,
	0,
	"WRGFLDDOOR"
  },
  {
	{ 4294758144, 4294966784, 668928, 0 },
	0,
	0,
	2496u,
	4096u,
	25u,
	50u,
	64,
	0,
	0,
	0,
	"DOOR01"
  },
  {
	{ 195264, 4294963568, 74752, 0 },
	0,
	0,
	0u,
	0u,
	0u,
	0u,
	1088,
	0,
	0,
	0,
	"FRAME"
  }
};

FixedEvent havanaFixed[3] =
{
  {
	{ 4294784000, 4294967023, 4294925576, 0 },
	0,
	0,
	800u,
	0u,
	25u,
	50u,
	64,
	0,
	0,
	0,
	"DOOR"
  },
  {
	{ 4294512128, 1529, 4294841856, 0 },
	0,
	0,
	0u,
	0u,
	0u,
	0u,
	1536,
	0,
	0,
	0,
	"LIFT_SHAFT"
  },
  {
	{ 4294479360, 0, 4294830607, 0 },
	0,
	0,
	1152u,
	0u,
	10u,
	20u,
	80,
	0,
	0,
	0,
	"BASEDOOR"
  }
};

FixedEvent vegasDoor[5] =
{
  {
	{ 4294955445, 0, 844163, 0 },
	0,
	0,
	1700u,
	3072u,
	25u,
	50u,
	80,
	0,
	0,
	0,
	"DOOR"
  },
  {
	{ 4294861054, 4294967057, 4294750336, 0 },
	0,
	0,
	800u,
	0u,
	25u,
	50u,
	96,
	0,
	0,
	0,
	"DOOR01"
  },
  {
	{ 63058, 4294967065, 501184, 0 },
	0,
	0,
	3200u,
	4096u,
	25u,
	50u,
	96,
	0,
	0,
	0,
	"DOOR02"
  },
  {
	{ 4294807940, 4294967120, 647024, 0 },
	0,
	0,
	3200u,
	4096u,
	25u,
	50u,
	64,
	0,
	0,
	0,
	"DOOR03"
  },
  {
	{ 123936, 4294967126, 4928, 0 },
	0,
	0,
	3200u,
	4096u,
	25u,
	50u,
	80,
	0,
	0,
	0,
	"GATE01"
  }
};

FixedEvent rioDoor[6] =
{
  {
	{ 4294843968, 4294967119, 4294712576, 0 },
	0,
	0,
	3200u,
	4096u,
	25u,
	50u,
	96,
	0,
	0,
	0,
	"DOOR1"
  },
  {
	{ 4294842048, 4294967279, 4294711088, 0 },
	0,
	0,
	1600u,
	0u,
	25u,
	50u,
	80,
	0,
	0,
	0,
	"DOOR2"
  },
  {
	{ 4294693296, 4294967279, 4294645888, 0 },
	0,
	0,
	1748u,
	3072u,
	25u,
	50u,
	80,
	0,
	0,
	0,
	"GATE01"
  },
  {
	{ 4294693296, 4294967279, 4294644864, 0 },
	0,
	0,
	2348u,
	1024u,
	25u,
	50u,
	80,
	0,
	0,
	0,
	"GATE01"
  },
  {
	{ 4294926864, 4294967279, 383328, 0 },
	0,
	0,
	700u,
	2048u,
	25u,
	50u,
	80,
	0,
	0,
	0,
	"GATE03"
  },
  {
	{ 4294927872, 4294967279, 383328, 0 },
	0,
	0,
	900u,
	0u,
	25u,
	50u,
	80,
	0,
	0,
	0,
	"GATE03"
  }
};

Helicopter HelicopterData =
{
  400,
  0,
  0,
  0,
  0,
  0,
  0,
  { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u }, 0u, 0u, '\0', '\0' },
  0,
  0,
  0,
  0
};



/*
 * Offset 0x45B20
 * D:\driver2\game\C\EVENT.C (line 249)
 * Stack frame base $sp, length 16
 */
int /*$ra*/ GetVisValue(int index /*$t1*/, int zDir /*$a1*/)
{ // line 1, address 0x45b20
	int value; // $v1
	int radius; // $a0
	{ // line 7, address 0x45b30
		int camera; // $a0
	} // line 10, address 0x45b90
	{ // line 14, address 0x45b98
		struct _EVENT *ev; // $a0
		int multiple; // $a2
		{ // line 25, address 0x45c24
			struct VECTOR pos; // stack address -16
		} // line 32, address 0x45ca4
	} // line 34, address 0x45ca8
} // line 45, address 0x45cd0
/*
 * Offset 0x45CD0
 * D:\driver2\game\C\EVENT.C (line 297)
 * Stack frame base $sp, length 568
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ VisibilityLists(enum VisType type /*$a0*/, int i /*$s2*/)
{ // line 1, address 0x45cd0
	static unsigned short xList[128]; // address 0x0
	static unsigned short zList[128]; // address 0x100
	static unsigned short *firstX[2]; // address 0x0
	static unsigned short *firstZ[2]; // address 0x8
	static int count; // address 0x10
	{ // line 34, address 0x45e00
		static unsigned short *list[2]; // address 0x50
		int table[128]; // stack address -552
		int j; // $s0
		{ // line 42, address 0x45e78
			int tempList; // $t7
			int k; // $t0
		} // line 53, address 0x45f20
	} // line 55, address 0x45f34
	{ // line 58, address 0x45f7c
		int camera; // $a1
	} // line 64, address 0x45fe0
	{ // line 68, address 0x45ff8
		struct _EVENT *ev; // $a0
	} // line 87, address 0x460d0
	{ // line 90, address 0x460d0
		struct _EVENT *ev; // $v1
	} // line 101, address 0x46124
} // line 103, address 0x46154
/*
 * Offset 0x46154
 * D:\driver2\game\C\EVENT.C (line 422)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ InitTrain(struct _EVENT *ev /*$s0*/, int count /*$s3*/, int type /*$a2*/)
{ // line 1, address 0x46154
	int height; // $s2
	int length; // $s1
	int *to; // $a0
} // line 47, address 0x462c0
/*
 * Offset 0x462C0
 * D:\driver2\game\C\EVENT.C (line 515)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SetUpEvents(int full /*stack 0*/)
{ // line 1, address 0x462c0
	int count; // $s5
	int *p; // $s2
	int cEvents; // stack address -52
	struct _EVENT **e; // stack address -56
	{ // line 25, address 0x46378
		int ElTrackModel; // stack address -48
		int carModel; // stack address -44
		int direction; // $fp
		int i; // $s3
		{ // line 36, address 0x4639c
			int cBridges; // $s1
			int timeOffset; // $a2
			int loop; // $a3
		} // line 91, address 0x465b0
		{ // line 110, address 0x46690
			int cCarriages; // $s0
			int first; // $s1
			{ // line 119, address 0x46698
			} // line 120, address 0x466ac
		} // line 149, address 0x467c4
	} // line 188, address 0x46930
	{ // line 243, address 0x46b0c
		int trainModel; // $s5
		int loop; // $s1
		int carriages; // $s2
		{ // line 296, address 0x46c9c
			int loop; // $t1
			{ // line 309, address 0x46e40
				int detonatorModel; // $v0
			} // line 314, address 0x46e98
		} // line 315, address 0x46e98
	} // line 319, address 0x46ea0
	{ // line 323, address 0x46ea0
		int detonatorModel; // $s3
		int loop; // $s1
		{ // line 367, address 0x46fec
			int loop; // $s1
			{ // line 373, address 0x470fc
				struct XYPAIR address; // stack address -64
			} // line 381, address 0x47208
		} // line 389, address 0x47280
		{ // line 394, address 0x472b4
		} // line 431, address 0x47524
	} // line 433, address 0x47524
} // line 449, address 0x475a0
/*
 * Offset 0x475A0
 * D:\driver2\game\C\EVENT.C (line 991)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ SetCamera(struct _EVENT *ev /*$s5*/)
{ // line 1, address 0x475a0
	int rotation; // $s4
	int axis; // $a3
	struct VECTOR pivot; // stack address -96
	int iPivot; // $a2
	int height; // $a1
	struct SVECTOR address; // stack address -80
	{ // line 46, address 0x476f0
		struct MATRIX matrix; // stack address -72
		struct SVECTOR temp; // stack address -40
		{ // line 54, address 0x47774
		} // line 64, address 0x477c4
	} // line 66, address 0x477c4
} // line 113, address 0x47a44
/*
 * Offset 0x47A44
 * D:\driver2\game\C\EVENT.C (line 1152)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ StepFromToEvent(struct _EVENT *ev /*$a3*/)
{ // line 1, address 0x47a44
	{ // line 8, address 0x47a70
		int *from; // $a1
		int *to; // $t4
		long *current; // $t0
		int d; // $a0
		int d2; // $t2
	} // line 56, address 0x47c2c
} // line 57, address 0x47c3c
/*
 * Offset 0x47C3C
 * D:\driver2\game\C\EVENT.C (line 1214)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ StepPathEvent(struct _EVENT *ev /*$s0*/)
{ // line 1, address 0x47c3c
	int *from; // $a1
	int *to; // $t1
	long *current; // $t3
	static int speed; // address 0x20
	{ // line 11, address 0x47c70
		int flags; // $v0
	} // line 19, address 0x47c9c
	{ // line 28, address 0x47ce4
		enum Station station; // $t2
		{ // line 62, address 0x47d94
			int direction; // $t2
			int loop; // $a2
			int *i; // $a0
			int turn[4]; // stack address -48
			struct XZPAIR centre; // stack address -32
			struct XZPAIR address; // stack address -24
		} // line 134, address 0x48000
		{ // line 141, address 0x48018
			int d; // $a0
			int d1; // $v1
			int dir; // $t4
		} // line 233, address 0x48360
	} // line 234, address 0x48360
} // line 235, address 0x48374
/*
 * Offset 0x48374
 * D:\driver2\game\C\EVENT.C (line 1478)
 * Stack frame base $sp, length 88
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ StepHelicopter(struct _EVENT *ev /*$s0*/)
{ // line 1, address 0x48374
	static int rotacc; // address 0xa4
	{ // line 7, address 0x4839c
		int b; // $a0
		int c; // $t2
		int d; // $v1
		int t; // $a1
		int t2; // $a3
		int t3; // $v1
		int dx1; // $a2
		int dx2; // $t1
		int dx3; // $t0
		int dz1; // $v0
		int dz2; // $a3
		int dz3; // $a0
		{ // line 44, address 0x48508
			struct XZPAIR vel; // stack address -56
			int direction; // $t1
			int temp; // $t1
			int dt; // $a0
			int d2p; // $v1
			int d2r; // $v1
			int pitch; // $a1
			int roll; // $a2
			static int rotating; // address 0x24
		} // line 99, address 0x4885c
		{ // line 112, address 0x488bc
			struct VECTOR pos; // stack address -48
		} // line 113, address 0x488bc
	} // line 131, address 0x48998
	{ // line 135, address 0x489b0
		struct VECTOR pos; // stack address -56
		struct VECTOR drift; // stack address -32
	} // line 135, address 0x489b0
} // line 155, address 0x48ac8
/*
 * Offset 0x48AC8
 * D:\driver2\game\C\EVENT.C (line 1642)
 * Stack frame base $sp, length 88
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ StepEvents()
{ // line 3, address 0x48ac8
	struct _EVENT *ev; // $s0
	{ // line 29, address 0x48b2c
		struct VECTOR old; // stack address -72
		int onBoatLastFrame; // $s7
		{ // line 34, address 0x48b34
			int dist; // stack address -48
			int loop; // $s2
			struct _CAR_DATA *cp; // $s1
		} // line 57, address 0x48c00
		{ // line 72, address 0x48ca8
			int d2; // $a2
		} // line 75, address 0x48d1c
		{ // line 82, address 0x48d40
		} // line 83, address 0x48d64
		{ // line 87, address 0x48d78
			struct XZPAIR speed; // stack address -56
			{ // line 91, address 0x48d90
				int loop; // $s2
				int mask; // $s1
				{ // line 98, address 0x48dc8
					struct VECTOR *pos; // $a0
					struct VECTOR *vel; // $a1
				} // line 133, address 0x48eb4
			} // line 134, address 0x48ecc
		} // line 135, address 0x48ecc
	} // line 136, address 0x48ecc
	{ // line 155, address 0x48fac
		{ // line 160, address 0x48fbc
			int sign; // $t0
			unsigned short *target; // $a3
		} // line 178, address 0x490d8
	} // line 183, address 0x490e8
	{ // line 220, address 0x491b4
		int thisCamera; // $s1
		int otherCamera; // $s2
		int loop; // $s0
		unsigned short *x; // $t0
		unsigned short *z; // $a3
		{ // line 247, address 0x492a8
			struct CELL_OBJECT *cop; // $a2
		} // line 294, address 0x4932c
	} // line 299, address 0x49374
} // line 309, address 0x493cc
/*
 * Offset 0x493CC
 * D:\driver2\game\C\EVENT.C (line 2110)
 * Stack frame base $sp, length 128
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ DrawFerrisWheel(struct MATRIX *matrix /*$s0*/, struct VECTOR *pos /*$s1*/)
{ // line 1, address 0x493cc
	{ // line 16, address 0x494c8
		int loop; // $s3
		struct MODEL *model; // $s2
		struct VECTOR spoke[2]; // stack address -104
		{ // line 28, address 0x4954c
			struct VECTOR address; // stack address -72
			struct VECTOR carPos; // stack address -56
			int rotation; // $v0
		} // line 32, address 0x4954c
	} // line 45, address 0x496c0
} // line 47, address 0x496ec
/*
 * Offset 0x496EC
 * D:\driver2\game\C\EVENT.C (line 2159)
 * Stack frame base $sp, length 136
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawRotor(struct VECTOR pos /*stack 0*/, struct MATRIX *matrix /*stack 16*/)
{ // line 1, address 0x496ec
	struct SVECTOR v[5]; // stack address -120
	struct MATRIX local; // stack address -80
	struct POLY_FT4 *poly; // $t0
	struct TEXTURE_DETAILS *tex; // $t3
	int z; // stack address -48
	char *firstPoly; // $a1
} // line 79, address 0x49ca0
/*
 * Offset 0x49CA0
 * D:\driver2\game\C\EVENT.C (line 2240)
 * Stack frame base $sp, length 232
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawEvents(int camera /*stack 0*/)
{ // line 1, address 0x49ca0
	unsigned short *x; // $a1
	unsigned short *z; // $a0
	int thisCamera; // stack address -56
	int otherCamera; // stack address -52
	static struct _EVENT *nearestTrain; // address 0x28
	static int distanceFromNearestTrain; // address 0x2c
	{ // line 36, address 0x49d7c
		struct _EVENT *ev; // $s1
		{ // line 49, address 0x49e74
			unsigned int dist; // $v1
		} // line 58, address 0x49edc
		{ // line 74, address 0x49f0c
			{ // line 76, address 0x49f3c
				struct MATRIX matrix; // stack address -208
				struct MATRIX ext; // stack address -176
				struct VECTOR pos; // stack address -144
				int reflection; // $s5
				int temp; // stack address -48
				{ // line 89, address 0x49fb0
				} // line 89, address 0x49fb0
				{ // line 95, address 0x4a01c
					{ // line 106, address 0x4a0a0
						struct VECTOR shadow[4]; // stack address -128
						int loop; // $t0
						{ // line 111, address 0x4a0c4
							struct XZPAIR address; // stack address -64
							int rotate; // $a1
						} // line 118, address 0x4a150
					} // line 121, address 0x4a180
					{ // line 133, address 0x4a1e4
					} // line 142, address 0x4a220
				} // line 143, address 0x4a220
				{ // line 153, address 0x4a280
				} // line 153, address 0x4a280
				{ // line 172, address 0x4a36c
					int i; // $a0
				} // line 179, address 0x4a3bc
				{ // line 184, address 0x4a3d0
				} // line 201, address 0x4a448
			} // line 245, address 0x4a5a8
		} // line 245, address 0x4a5a8
	} // line 255, address 0x4a5f0
	{ // line 270, address 0x4a690
	} // line 270, address 0x4a690
} // line 276, address 0x4a6c0
/*
 * Offset 0x4A6F0
 * D:\driver2\game\C\EVENT.C (line 2560)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 ra
 */
struct _sdPlane * /*$ra*/ EventSurface(struct VECTOR *pos /*$a0*/, struct _sdPlane *plane /*$s1*/)
{ // line 1, address 0x4a6f0
	struct _EVENT *ev; // $s0
	int i; // $a2
	{ // line 12, address 0x4a768
		int dist; // $a3
		int end; // $a1
		int cos; // $a2
	} // line 63, address 0x4a8e8
	{ // line 68, address 0x4a8fc
		int dist; // stack address -24
		{ // line 72, address 0x4a90c
			int sin; // $a3
			int cos; // $a2
			int height; // $t0
			int address; // $a0
		} // line 104, address 0x4aa88
	} // line 105, address 0x4aa88
} // line 121, address 0x4aae0
/*
 * Offset 0x4AAE0
 * D:\driver2\game\C\EVENT.C (line 2718)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
struct VECTOR * /*$ra*/ TriggerEvent(int i /*$s4*/)
{ // line 1, address 0x4aae0
	static int stage[10]; // address 0x200
	struct VECTOR *pos; // $s7
	{ // line 8, address 0x4ab18
		int loop; // $v1
	} // line 13, address 0x4ab38
	{ // line 21, address 0x4ab88
		struct _EVENT *ev; // $a2
	} // line 22, address 0x4ab88
	{ // line 36, address 0x4ac70
		{ // line 39, address 0x4ac70
			struct MissionTrain *train; // $s1
			{ // line 45, address 0x4aca0
			} // line 51, address 0x4acb8
			{ // line 56, address 0x4acc4
				struct _EVENT *ev; // $s0
				int count; // $s2
				int address; // $s6
				{ // line 67, address 0x4ad14
					int pos; // $a1
				} // line 67, address 0x4ad14
			} // line 99, address 0x4adf0
		} // line 101, address 0x4adf0
		{ // line 113, address 0x4ae20
			struct _EVENT *ev; // $v1
			int count; // $a0
		} // line 130, address 0x4ae6c
	} // line 142, address 0x4ae90
	{ // line 149, address 0x4aef8
	} // line 179, address 0x4afc8
	{ // line 187, address 0x4b010
		{ // line 189, address 0x4b010
			int loop; // $s0
		} // line 205, address 0x4b0ac
	} // line 223, address 0x4b138
} // line 274, address 0x4b304
/*
 * Offset 0x4B304
 * D:\driver2\game\C\EVENT.C (line 2999)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ SpecialCamera(enum SpecialCamera type /*$t2*/, int change /*$a1*/)
{ // line 1, address 0x4b304
	static int rememberCamera[3]; // address 0x230
	static short boatCamera[6] = { -1000, 2100, 6000, -5000, 3584, -5000 };
	{ // line 14, address 0x4b34c
		int *hackCamera; // $a2
		short *boat; // $t3
	} // line 115, address 0x4b5a8
} // line 143, address 0x4b664
/*
 * Offset 0x4B664
 * D:\driver2\game\C\EVENT.C (line 3152)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ DetonatorTimer()
{ // line 2, address 0x4b664
	static struct SVECTOR rememberCameraAngle; // address 0x30
	{ // line 16, address 0x4b700
		{ // line 23, address 0x4b718
			static int count; // address 0x38
			{ // line 27, address 0x4b734
				struct VECTOR pos; // stack address -32
			} // line 32, address 0x4b768
			{ // line 36, address 0x4b788
				struct VECTOR pos; // stack address -32
			} // line 37, address 0x4b788
		} // line 52, address 0x4b830
	} // line 58, address 0x4b844
	{ // line 66, address 0x4b8cc
		struct _EVENT *ev; // $s0
		struct VECTOR pos; // stack address -32
		{ // line 95, address 0x4ba18
			struct VECTOR *epicentre; // $v1
		} // line 108, address 0x4ba70
	} // line 123, address 0x4baf4
} // line 126, address 0x4bb18
/*
 * Offset 0x4BB18
 * D:\driver2\game\C\EVENT.C (line 3288)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ MultiCarEvent(struct _TARGET *target /*$a0*/)
{ // line 1, address 0x4bb18
	struct MULTICAR_DATA *data; // $s0
	int i; // $s1
	struct _EVENT *ev; // $s2
	{ // line 13, address 0x4bb60
		int n; // $a1
	} // line 15, address 0x4bb60
} // line 25, address 0x4bc3c
/*
 * Offset 0x4BC3C
 * D:\driver2\game\C\EVENT.C (line 483)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitEvents()
{
}
/*
 * Offset 0x4BCB8
 * D:\driver2\game\C\EVENT.C (line 1107)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ EventCollisions(struct _CAR_DATA *cp /*$a2*/, int type /*$a1*/)
{ // line 1, address 0x4bcb8
	static struct SVECTOR address; // address 0x18
} // line 18, address 0x4bd94
/*
 * Offset 0x4BD94
 * D:\driver2\game\C\EVENT.C (line 2994)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ OffsetTarget(struct VECTOR *target /*$a0*/)
{
}
/*
 * Offset 0x4BDD4
 * D:\driver2\game\C\EVENT.C (line 2684)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ MakeEventTrackable(struct _EVENT *ev /*$a0*/)
{ // line 1, address 0x4bdd4
	struct _EVENT **p; // $v1
} // line 10, address 0x4be08
/*
 * Offset 0x4BE08
 * D:\driver2\game\C\EVENT.C (line 2527)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ OnBoat(struct VECTOR *pos /*$t1*/, struct _EVENT *ev /*$a1*/, int *dist /*$a2*/)
{ // line 1, address 0x4be08
	int halfBoatWidth; // $t0
	int halfBoatLength; // $a0
} // line 31, address 0x4be8c
/*
 * Offset 0x4BE8C
 * D:\driver2\game\C\EVENT.C (line 2520)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ BoatOffset(struct SVECTOR *address /*$a0*/, struct _EVENT *ev /*$a1*/)
{
}
/*
 * Offset 0x4BEC4
 * D:\driver2\game\C\EVENT.C (line 402)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetElTrainRotation(struct _EVENT *ev /*$a1*/)
{
}
/*
 * Offset 0x4BF20
 * D:\driver2\game\C\EVENT.C (line 471)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitDoor(struct FixedEvent *ev /*$a0*/, struct _EVENT ***e /*$a1*/, int *cEvents /*$a2*/)
{
}
/*
 * Offset 0x4BFBC
 * D:\driver2\game\C\EVENT.C (line 974)
 * Stack frame base $sp, length 16
 * Saved registers at address -4: s0 s1 s2 s3
 */
void /*$ra*/ InitEventCamera()
{
}
/*
 * Offset 0x4C07C
 * D:\driver2\game\C\EVENT.C (line 983)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ResetEventCamera()
{
}
/*
 * Offset 0x4C10C
 * D:\driver2\game\C\EVENT.C (line 1127)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ NextNode(struct _EVENT *ev /*$a0*/)
{
}
/*
 * Offset 0x4C1C0
 * D:\driver2\game\C\EVENT.C (line 1452)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetBridgeRotation(int timer /*$a0*/)
{ // line 1, address 0x4c1c0
	int angle; // $v1
} // line 24, address 0x4c270
/*
 * Offset 0x4C270
 * D:\driver2\game\C\EVENT.C (line 2696)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ TriggerDoor(struct FixedEvent *door /*$a3*/, int *stage /*$a1*/, int sound /*$a2*/)
{
}
/*
 * Offset 0x4C2E8
 * D:\driver2\game\C\EVENT.C (line 3144)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ ScreenShake(int count /*$a0*/, struct SVECTOR *ang /*$s0*/)
{ // line 1, address 0x4c2e8
} // line 6, address 0x4c398