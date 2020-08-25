#include "THISDUST.H"
#include "EVENT.H"
#include "CARS.H"
#include "PLAYERS.H"
#include "MC_SND.H"
#include "CAMERA.H"
#include "CONVERT.H"
#include "DRAW.H"
#include "MODELS.H"
#include "MISSION.H"
#include "JOB_FX.H"
#include "BOMBERMAN.H"
#include "DEBRIS.H"
#include "MAIN.H"

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
	8, -182784, -175616, -168448, 
	7, -227328, -162304, -141824, -121344, -100864, -80384, -59904, 
	256, -312832, -305664, -298496, 
	1, 324096, -311808, -304640, -297472,
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
	-491431, 3568, -139048, 
	-453981, 409, -128009,
	-453975, 429, -127175
};

int VegasCameraHack[16] = {
	124092, 3988, 3494,
	-11285, 1559, 843824, 
	-38801, 2681, 273148, 
	-36925, 2048, 269647, 273935,
	-65503, 1617, 796775
};

int RioCameraHack[6] = {
	-276620, 3072, -321920,
	-40920, 3623, 382170
};

MissionTrain missionTrain[2] =
{
	{ 0, ElTrainData + 4, 100, 150, 200, 289051, 32768 },
	{ 0, ElTrainData + 7, 125, 145, 215, 4294762796, 0 }
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

EventGlobal events;

CELL_OBJECT *EventCop;
int event_models_active = 0;

static struct _EVENT(*trackingEvent[2]);
static struct _TARGET(*carEvent[8]);
static int cameraEventsActive = 0;
static CameraDelay cameraDelay;
static Detonator detonator;
static int eventHaze = 0;
static int carsOnBoat = 0;
static int doneFirstHavanaCameraHack = 0;
static SVECTOR boatOffset;
static struct FixedEvent *fixedEvent = NULL;

static MultiCar multiCar;
struct _EVENT *firstEvent;
struct _EVENT *event;

static struct EventCamera eventCamera;

// decompiled code
// original method signature: 
// int /*$ra*/ GetVisValue(int index /*$t1*/, int zDir /*$a1*/)
 // line 249, offset 0x00045ab8
	/* begin block 1 */
		// Start line: 250
		// Start offset: 0x00045AB8
		// Variables:
	// 		int value; // $v1
	// 		int radius; // $a0

		/* begin block 1.1 */
			// Start line: 256
			// Start offset: 0x00045AC8
			// Variables:
		// 		int camera; // $a0
		/* end block 1.1 */
		// End offset: 0x00045B28
		// End Line: 259

		/* begin block 1.2 */
			// Start line: 263
			// Start offset: 0x00045B30
			// Variables:
		// 		struct _EVENT *ev; // $a0
		// 		int multiple; // $a2

			/* begin block 1.2.1 */
				// Start line: 274
				// Start offset: 0x00045BBC
				// Variables:
			// 		struct VECTOR pos; // stack offset -16
			/* end block 1.2.1 */
			// End offset: 0x00045C3C
			// End Line: 281
		/* end block 1.2 */
		// End offset: 0x00045C40
		// End Line: 283
	/* end block 1 */
	// End offset: 0x00045C68
	// End Line: 294

	/* begin block 2 */
		// Start line: 498
	/* end block 2 */
	// End Line: 499

int GetVisValue(int index, int zDir)
{
	UNIMPLEMENTED();
	return 0;

	// WEIRD FUNCTION
	/*
	uint uVar1;
	int iVar2;
	_EVENT* local_a0_176;
	_EVENT* local_a0_180;
	VECTOR pos;

	if ((index & 0xc000U) != 0) 
	{
		uVar1 = ((uint)index >> 0xf ^ 1) & 1;
		if (zDir == 0)
		{
			pos.vx = player[uVar1].cameraPos.vx;
			iVar2 = 16000;
		}
		else
		{
			pos.vx = player[uVar1].cameraPos.vz;
			iVar2 = 16000;
		}
		goto LAB_00045c40;
	}

	if ((index & 0x80U) == 0) 
	{
		iVar2 = (index & 0x7fU) * 0x28;
		local_a0_176 = event;
	}
	else 
	{
		iVar2 = (index & 0x7fU) * 0x2c;
		local_a0_176 = (_EVENT*)fixedEvent;
	}

	local_a0_180 = (_EVENT*)((int)&(local_a0_176->position).vx + iVar2);

	if ((index & 0xf00U) == 0)
	{
	LAB_00045bbc:
		pos.vx = (local_a0_180->position).vx;
		pos.vz = (local_a0_180->position).vz;
		if ((local_a0_180->flags & 0xcc0U) == 0x80)
		{
			pos.vx = pos.vx - boatOffset.vx;
			pos.vz = pos.vz - boatOffset.vz;
		}

		if (zDir != 0)
		{
			pos.vx = pos.vz;
		}
	}
	else 
	{
		if ((local_a0_180->flags & 0x30U) == 0)
		{
			if (zDir != 0)
				goto LAB_00045bbc;
		}
		else 
		{
			if (zDir == 0)
				goto LAB_00045bbc;
		}

		pos.vx = *(int*)(((index & 0xf00U) >> 6) + (int)local_a0_180->node);
	}
	iVar2 = (int)local_a0_180->radius;
LAB_00045c40:
	if ((index & 0x2000U) != 0)
		pos.vx = pos.vx - iVar2;

	if ((index & 0x1000U) != 0)
		pos.vx = pos.vx + iVar2;

	return pos.vx;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ VisibilityLists(enum VisType type /*$a0*/, int i /*$s2*/)
 // line 297, offset 0x00045c68
	/* begin block 1 */
		// Start line: 298
		// Start offset: 0x00045C68
		// Variables:
	// 		static unsigned short xList[128]; // offset 0x0
	// 		static unsigned short zList[128]; // offset 0x100
	// 		static unsigned short (*firstX[2]); // offset 0x0
	// 		static unsigned short (*firstZ[2]); // offset 0x8
	// 		static int count; // offset 0x10

		/* begin block 1.1 */
			// Start line: 331
			// Start offset: 0x00045D98
			// Variables:
		// 		static unsigned short (*list[2]); // offset 0x50
		// 		int table[128]; // stack offset -552
		// 		int j; // $s0

			/* begin block 1.1.1 */
				// Start line: 339
				// Start offset: 0x00045E10
				// Variables:
			// 		int tempList; // $t7
			// 		int k; // $t0
			/* end block 1.1.1 */
			// End offset: 0x00045EB8
			// End Line: 350
		/* end block 1.1 */
		// End offset: 0x00045ECC
		// End Line: 352

		/* begin block 1.2 */
			// Start line: 355
			// Start offset: 0x00045F14
			// Variables:
		// 		int camera; // $a1
		/* end block 1.2 */
		// End offset: 0x00045F78
		// End Line: 361

		/* begin block 1.3 */
			// Start line: 365
			// Start offset: 0x00045F90
			// Variables:
		// 		struct _EVENT *ev; // $a0
		/* end block 1.3 */
		// End offset: 0x00046068
		// End Line: 384

		/* begin block 1.4 */
			// Start line: 387
			// Start offset: 0x00046068
			// Variables:
		// 		struct _EVENT *ev; // $v1
		/* end block 1.4 */
		// End offset: 0x000460BC
		// End Line: 398
	/* end block 1 */
	// End offset: 0x000460EC
	// End Line: 400

	/* begin block 2 */
		// Start line: 590
	/* end block 2 */
	// End Line: 591

	/* begin block 3 */
		// Start line: 594
	/* end block 3 */
	// End Line: 595

/* WARNING: Type propagation algorithm not settling */

void VisibilityLists(VisType type, int i)
{
	UNIMPLEMENTED();
	/*
	undefined2 uVar1;
	ushort uVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	int *piVar6;
	ushort *puVar7;
	_EVENT *p_Var8;
	int iVar9;
	undefined *puVar10;
	FixedEvent *pFVar11;
	ushort *puVar12;
	ushort uVar13;
	int iVar14;
	int iVar15;
	undefined4 *puVar16;
	int zDir;
	int iVar17;
	undefined *puVar18;
	undefined **ppuVar19;
	int iVar20;
	undefined local_22c[4];
	int local_228[128];

	debugCount = &count_10;
	if (type == VIS_SORT) {
		zDir = 0;
		do {
			if (0 < count_10) {
				ppuVar19 = &PTR_xList_6_000aa4c0 + zDir;
				puVar18 = &stack0xfffffdd0 + 8;
				iVar17 = 0;
				do {
					iVar5 = GetVisValue((uint)*(ushort *)(*ppuVar19 + iVar17 * 2), zDir);
					iVar9 = iVar17 * 4;
					iVar20 = iVar17 + 1;
					*(int *)(puVar18 + iVar17 * 4) = iVar5;
					if ((iVar17 != 0) && (iVar5 < *(int *)(puVar18 + (iVar17 + -1) * 4))) {
						uVar1 = *(undefined2 *)(*ppuVar19 + iVar17 * 2);
						if (0 < iVar17) {
							puVar16 = (undefined4 *)(puVar18 + iVar17 * 4);
							iVar14 = iVar9 + -8;
							iVar15 = iVar17;
							iVar3 = iVar17 + -1;
							do {
								iVar17 = iVar3;
								iVar9 = iVar9 + -4;
								puVar10 = (&PTR_xList_6_000aa4c0)[zDir];
								*puVar16 = *(undefined4 *)(puVar18 + iVar9);
								puVar16 = puVar16 + -1;
								*(undefined2 *)(puVar10 + iVar15 * 2) = *(undefined2 *)(puVar10 + iVar15 * 2 + -1);
								if (iVar17 < 1) break;
								piVar6 = (int *)(puVar18 + iVar14);
								iVar14 = iVar14 + -4;
								iVar15 = iVar17;
								iVar3 = iVar17 + -1;
							} while (iVar5 < *piVar6);
						}
						*(int *)(puVar18 + iVar17 * 4) = iVar5;
						*(undefined2 *)(*ppuVar19 + iVar17 * 2) = uVar1;
					}
					iVar17 = iVar20;
				} while (iVar20 < count_10);
			}
			zDir = zDir + 1;
		} while (zDir < 2);
		uVar4 = (uint)NumPlayers;
		zDir = 0;
		if (NumPlayers != 0) {
			do {
				uVar13 = 0x8000;
				if (zDir != 0) {
					uVar13 = 0x4000;
				}
				(&firstX_8)[zDir] = 0xcdc50;
				do {
					puVar7 = (ushort *)(&firstX_8)[zDir];
					uVar2 = *puVar7;
					*(ushort **)(&firstX_8 + zDir) = puVar7 + 1;
				} while ((uVar2 & uVar13) == 0);
				(&firstZ_9)[zDir] = 0xcdd50;
				do {
					puVar7 = (ushort *)(&firstZ_9)[zDir];
					uVar2 = *puVar7;
					*(ushort **)(&firstZ_9 + zDir) = puVar7 + 1;
				} while ((uVar2 & uVar13) == 0);
				zDir = zDir + 1;
			} while (zDir < (int)uVar4);
		}
	}
	else {
		if (type < VIS_ADD) {
			if (type == VIS_INIT) {
				zList_7 = 0xa000;
				xList_6 = 0xa000;
				DAT_000cdd52 = 0x9000;
				DAT_000cdc52 = 0x9000;
				count_10 = 2;
				if (NumPlayers == 2) {
					DAT_000cdd54 = 0x6000;
					DAT_000cdc54 = 0x6000;
					DAT_000cdd56 = 0x5000;
					DAT_000cdc56 = 0x5000;
					count_10 = 4;
				}
				uVar4 = (uint)NumPlayers;
				zDir = 0;
				if (NumPlayers != 0) {
					do {
						iVar17 = zDir + 1;
						(&firstX_8)[zDir] = 0xcdc50;
						(&firstZ_9)[zDir] = 0xcdd50;
						zDir = iVar17;
					} while (iVar17 < (int)uVar4);
				}
			}
		}
		else {
			if (type == VIS_ADD) {
				if ((i & 0x80U) == 0) {
					zDir = (i & 0x7fU) * 0x28;
					pFVar11 = (FixedEvent *)event;
				}
				else {
					zDir = (i & 0x7fU) * 0x2c;
					pFVar11 = fixedEvent;
				}
				uVar13 = (ushort)i;
				if (*(short *)((int)&pFVar11->radius + zDir) == 0) {
					puVar7 = &xList_6 + count_10;
					puVar12 = &zList_7 + count_10;
					count_10 = count_10 + 1;
					*puVar7 = uVar13;
					*puVar12 = uVar13;
				}
				else {
					(&xList_6)[count_10] = uVar13 | 0x2000;
					zDir = count_10 + 1;
					(&zList_7)[count_10] = uVar13 | 0x2000;
					count_10 = count_10 + 2;
					(&xList_6)[zDir] = uVar13 | 0x1000;
					(&zList_7)[zDir] = uVar13 | 0x1000;
				}
			}
			else {
				if (type == VIS_NEXT) {
					p_Var8 = firstEvent;
					if (firstEvent != (_EVENT *)0x0) {
						do {
							p_Var8->flags = p_Var8->flags & 0xfffb;
							p_Var8 = p_Var8->next;
						} while (p_Var8 != (_EVENT *)0x0);
					}
					xVis = (ushort *)(&firstX_8)[i];
					zVis = (ushort *)(&firstZ_9)[i];
				}
			}
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetElTrainRotation(struct _EVENT *ev /*$a1*/)
 // line 402, offset 0x0004be5c
	/* begin block 1 */
		// Start line: 804
	/* end block 1 */
	// End Line: 805

// [D]
void SetElTrainRotation(_EVENT *ev)
{
	if ((ev->flags & 0x8000U) == 0) 
		ev->rotation = 0;
	else 
		ev->rotation = 0x400;

	if (*ev->node < ev->node[2])
		ev->rotation += 0x800;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitTrain(struct _EVENT *ev /*$s0*/, int count /*$s3*/, int type /*$a2*/)
 // line 422, offset 0x000460ec
	/* begin block 1 */
		// Start line: 423
		// Start offset: 0x000460EC
		// Variables:
	// 		int height; // $s2
	// 		int length; // $s1
	// 		int *to; // $a0
	/* end block 1 */
	// End offset: 0x00046258
	// End Line: 469

	/* begin block 2 */
		// Start line: 918
	/* end block 2 */
	// End Line: 919

	/* begin block 3 */
		// Start line: 941
	/* end block 3 */
	// End Line: 942

// [D]
void InitTrain(_EVENT *ev, int count, int type)
{
	ushort uVar1;
	int *piVar2;
	uint uVar3;
	int *piVar4;
	int unaff_s1;
	long unaff_s2;

	uVar1 = *(ushort *)(ev->data + 2);
	ev->node = ev->data + 3;
	ev->timer = 0;
	ev->flags = uVar1 | 2;

	if (type == 0) 
	{
		unaff_s2 = -1773;
		unaff_s1 = 1600;
		SetElTrainRotation(ev);
	}
	else if (type == 1)
	{
		unaff_s2 = -734;
		unaff_s1 = 3700;
		ev->rotation = 0;
	}

	piVar2 = ev->node;
	ev->position.vy = unaff_s2;

	if (piVar2[3] == -0x80000000) 
		uVar1 = ev->flags & 0x8fff;
	else
		uVar1 = ev->flags & 0x8fffU | 0x3000;

	ev->flags = uVar1;
	piVar4 = ev->node;
	piVar2 = piVar4 + 2;

	if (piVar4[2] == -0x7ffffffe)
		piVar2 = piVar4 + 3;

	if ((ev->flags & 0x8000U) == 0) 
	{
		uVar3 = *piVar2 - *piVar4 >> 0x1f;
		ev->position.vx = *piVar4 + ((count * unaff_s1 ^ uVar3) - uVar3);
		ev->position.vz = piVar4[1];
	}
	else 
	{
		uVar3 = *piVar2 - *piVar4 >> 0x1f;
		ev->position.vz = *piVar4 + ((count * unaff_s1 ^ uVar3) - uVar3);
		ev->position.vx = piVar4[1];
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitDoor(struct FixedEvent *ev /*$a0*/, struct _EVENT ***e /*$a1*/, int *cEvents /*$a2*/)
 // line 471, offset 0x0004beb8
	/* begin block 1 */
		// Start line: 8350
	/* end block 1 */
	// End Line: 8351

	/* begin block 2 */
		// Start line: 8352
	/* end block 2 */
	// End Line: 8353

// [D]
void InitDoor(FixedEvent *ev, _EVENT ***e, int *cEvents)
{
	ev->active = 0;
	ev->rotation = ev->finalRotation;
	ev->flags = ev->flags | 0x200;

	*(FixedEvent **)*e = ev;	// [A] is that gonna work?
	*e = &(**e)->next;

	VisibilityLists(VIS_ADD, (ev - fixedEvent) * -0x45d1745d >> 2 | 0x80);
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitEvents()
 // line 483, offset 0x0004bbd4
	/* begin block 1 */
		// Start line: 5662
	/* end block 1 */
	// End Line: 5663

	/* begin block 2 */
		// Start line: 966
	/* end block 2 */
	// End Line: 967

	/* begin block 3 */
		// Start line: 5689
	/* end block 3 */
	// End Line: 5690

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitEvents(void)
{
	events.camera = 0;
	events.track = trackingEvent;
	events.cameraEvent = NULL;

	detonator.timer = 0;
	detonator.count = 0;

	trackingEvent[0] = NULL;
	carEvent[0] = NULL;

	cameraEventsActive = 0;
	event_models_active = 0;
	
	cameraDelay.delay = 0;
	eventHaze = 0;
	carsOnBoat = 0;
	doneFirstHavanaCameraHack = 0;

	boatOffset.vx = 0;
	boatOffset.vy = 0;
	boatOffset.vz = 0;

	VisibilityLists(VIS_INIT, 0);
	TriggerEvent(-1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetUpEvents(int full /*stack 0*/)
 // line 515, offset 0x00046258
	/* begin block 1 */
		// Start line: 516
		// Start offset: 0x00046258
		// Variables:
	// 		int count; // $s5
	// 		int *p; // $s2
	// 		int cEvents; // stack offset -52
	// 		struct _EVENT **e; // stack offset -56

		/* begin block 1.1 */
			// Start line: 540
			// Start offset: 0x00046310
			// Variables:
		// 		int ElTrackModel; // stack offset -48
		// 		int carModel; // stack offset -44
		// 		int direction; // $fp
		// 		int i; // $s3

			/* begin block 1.1.1 */
				// Start line: 551
				// Start offset: 0x00046334
				// Variables:
			// 		int cBridges; // $s1
			// 		int timeOffset; // $a2
			// 		int loop; // $a3
			/* end block 1.1.1 */
			// End offset: 0x00046548
			// End Line: 606

			/* begin block 1.1.2 */
				// Start line: 625
				// Start offset: 0x00046628
				// Variables:
			// 		int cCarriages; // $s0
			// 		int first; // $s1

				/* begin block 1.1.2.1 */
					// Start line: 634
					// Start offset: 0x00046630
				/* end block 1.1.2.1 */
				// End offset: 0x00046644
				// End Line: 635
			/* end block 1.1.2 */
			// End offset: 0x0004675C
			// End Line: 664
		/* end block 1.1 */
		// End offset: 0x000468C8
		// End Line: 703

		/* begin block 1.2 */
			// Start line: 758
			// Start offset: 0x00046AA4
			// Variables:
		// 		int trainModel; // $s5
		// 		int loop; // $s1
		// 		int carriages; // $s2

			/* begin block 1.2.1 */
				// Start line: 811
				// Start offset: 0x00046C34
				// Variables:
			// 		int loop; // $t1

				/* begin block 1.2.1.1 */
					// Start line: 824
					// Start offset: 0x00046DD8
					// Variables:
				// 		int detonatorModel; // $v0
				/* end block 1.2.1.1 */
				// End offset: 0x00046E30
				// End Line: 829
			/* end block 1.2.1 */
			// End offset: 0x00046E30
			// End Line: 830
		/* end block 1.2 */
		// End offset: 0x00046E38
		// End Line: 834

		/* begin block 1.3 */
			// Start line: 838
			// Start offset: 0x00046E38
			// Variables:
		// 		int detonatorModel; // $s3
		// 		int loop; // $s1

			/* begin block 1.3.1 */
				// Start line: 882
				// Start offset: 0x00046F84
				// Variables:
			// 		int loop; // $s1

				/* begin block 1.3.1.1 */
					// Start line: 888
					// Start offset: 0x00047094
					// Variables:
				// 		struct XYPAIR offset; // stack offset -64
				/* end block 1.3.1.1 */
				// End offset: 0x000471A0
				// End Line: 896
			/* end block 1.3.1 */
			// End offset: 0x00047218
			// End Line: 904

			/* begin block 1.3.2 */
				// Start line: 909
				// Start offset: 0x0004724C
			/* end block 1.3.2 */
			// End offset: 0x000474BC
			// End Line: 946
		/* end block 1.3 */
		// End offset: 0x000474BC
		// End Line: 948
	/* end block 1 */
	// End offset: 0x00047538
	// End Line: 964

	/* begin block 2 */
		// Start line: 1090
	/* end block 2 */
	// End Line: 1091

	/* begin block 3 */
		// Start line: 1137
	/* end block 3 */
	// End Line: 1138

	/* begin block 4 */
		// Start line: 1143
	/* end block 4 */
	// End Line: 1144

void SetUpEvents(int full)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	short sVar2;
	long lVar3;
	int iVar4;
	int i;
	FixedEvent *ev;
	_EVENT *ev_00;
	int iVar5;
	int *piVar6;
	_EVENT *p_Var7;
	int count;
	int *piVar8;
	int unaff_s3;
	uint uVar9;
	uint uVar10;
	int unaff_s5;
	FixedEvent **local_38;
	uint local_34;
	int local_30;
	int local_2c;

	i = LiftingBridges;
	firstEvent = (_EVENT *)0x0;
	local_38 = &firstEvent;
	if (doSpooling == 0) {
		firstEvent = (_EVENT *)0x0;
		EventCop = (CELL_OBJECT *)0x0;
		return;
	}
	if (full != 0) {
		EventCop = (CELL_OBJECT *)mallocptr;
		event = (_EVENT *)(mallocptr + 0x100);
		mallocptr = (char *)event;
	}
	ev_00 = event;
	local_34 = 0;
	if (GameLevel == 1) {
		event->radius = 0;
		i = INT_0009e888;
		cameraEventsActive = 1;
		(ev_00->position).vy = 0x6f;
		(ev_00->position).vx = i;
		i = INT_ARRAY_0009e88c[0];
		ev_00->rotation = 0xc00;
		ev_00->flags = -0x77ad;
		ev_00->timer = -1;
		ev_00->node = INT_ARRAY_0009e88c;
		ev_00->data = HavanaFerryData;
		(ev_00->position).vz = i;
		VisibilityLists(VIS_ADD, 0);
		MakeEventTrackable(event);
		*local_38 = event;
		fixedEvent = &havanaFixed;
		local_38 = &((FixedEvent *)*local_38)->next;
		InitDoor(&havanaFixed, (_EVENT ***)&local_38, (int *)&local_34);
		InitDoor(&FixedEvent_0009e9e8, (_EVENT ***)&local_38, (int *)&local_34);
		*(FixedEvent **)local_38 = &FixedEvent_0009e9bc;
		local_38 = &((FixedEvent *)*local_38)->next;
		VisibilityLists(VIS_ADD, 0x81);
		ev_00 = event;
		event[1].position.vy = 0xf9b;
		ev_00[1].flags = 0x4212;
		ev_00[1].node = INT_ARRAY_0009e8c8;
		ev_00[1].position.vx = -0x6f1ff;
		ev_00[1].position.vz = -0x1e9ff;
		ev_00[1].rotation = 0;
		ev_00[1].timer = -1;
		ev_00[1].radius = 0;
		ev_00[1].data = &HavanaMiniData;
		VisibilityLists(VIS_ADD, 1);
		*(FixedEvent **)local_38 = (FixedEvent *)(event + 1);
		local_38 = &((FixedEvent *)*local_38)->next;
		local_34 = 2;
		if (full != 0) {
			i = FindModelIdxWithName(s_FERRY_000aa4e0);
			event->model = i;
			i = FindModelIdxWithName(&DAT_000aa4e8);
			event[1].model = i;
			FixedEvent_0009e9bc.model = FindModelIdxWithName(FixedEvent_0009e9bc.modelName);
			FixedEvent_0009e9e8.model = FindModelIdxWithName(FixedEvent_0009e9e8.modelName);
			havanaFixed.model = FindModelIdxWithName(havanaFixed.modelName);
			foam.model = FindModelPtrWithName(&DAT_000aa4f0);
		}
	}
	else {
		if (GameLevel < 2) {
			if (GameLevel == 0) {
				bVar1 = false;
				piVar8 = &INT_0009ec2c;
				uVar9 = 0;
				if (0 < LiftingBridges) {
					do {
						cameraEventsActive = 1;
						if (*piVar8 == 0x8000) {
							bVar1 = true;
							piVar8 = piVar8 + 1;
						}
						else {
							if (*piVar8 == 0x100) {
								piVar8 = piVar8 + 1;
								firstMissionEvent = event + local_34;
							}
						}
						ev_00 = event + local_34;
						ev_00->data = piVar8;
						ev_00[1].data = piVar8 + 2;
						if (bVar1) {
							(ev_00->position).vz = (*piVar8 + piVar8[1]) / 2;
							ev_00[1].position.vz = (piVar8[1] + piVar8[2]) / 2;
						}
						else {
							(ev_00->position).vx = (*piVar8 + piVar8[1]) / 2;
							ev_00[1].position.vx = (piVar8[1] + piVar8[2]) / 2;
						}
						count = piVar8[3];
						piVar8 = piVar8 + 4;
						lVar3 = Random2(0);
						iVar5 = 0;
						iVar4 = (lVar3 >> (uVar9 & 0x1f) & 0xffU) * 0x20;
						uVar10 = uVar9 + 1;
						ev_00 = event + local_34;
						do {
							if (bVar1) {
								ev_00->flags = 1;
								(ev_00->position).vx = *piVar8;
							}
							else {
								ev_00->flags = 0x21;
								(ev_00->position).vz = *piVar8;
							}
							ev_00->node = piVar8;
							ev_00->radius = 0x1000;
							ev_00->timer = (short)iVar4 + (short)(iVar4 / 8000) * -8000;
							ev_00->model = uVar9 * 2 + iVar5;
							iVar5 = iVar5 + 1;
							ev_00 = ev_00 + 1;
						} while (iVar5 < 2);
						while (count = count + -1, count != -1) {
							piVar8 = piVar8 + 1;
							VisibilityLists(VIS_ADD, local_34 | count * 0x100);
							VisibilityLists(VIS_ADD, local_34 + 1 | count * 0x100);
						}
						*(FixedEvent **)local_38 = (FixedEvent *)(event + local_34);
						ev = (FixedEvent *)*local_38;
						ev->next = event + local_34 + 1;
						local_34 = local_34 + 2;
						local_38 = &ev->next->next;
						uVar9 = uVar10;
					} while ((int)uVar10 < i);
				}
				if (full != 0) {
					local_30 = FindModelIdxWithName(s_ELTRAIN_000aa4c8);
				}
				i = ElTrainData;
				piVar8 = &INT_0009e70c;
				uVar9 = 0;
				missionTrain.engine = event + local_34;
				MissionTrain_0009e8f0.engine = missionTrain.engine;
				if (0 < ElTrainData) {
					do {
						count = 5;
						if (uVar9 != 0) {
							lVar3 = Random2(0);
							count = (lVar3 >> (uVar9 & 0x1f) & 3U) + 2;
						}
						bVar1 = true;
						uVar9 = uVar9 + 1;
						while (count = count + -1, count != -1) {
							ev_00 = event + local_34;
							ev_00->radius = 0;
							ev_00->data = piVar8;
							InitTrain(ev_00, count, 0);
							if (bVar1) {
								bVar1 = false;
								event[local_34].flags = event[local_34].flags | 0x400;
							}
							if (full != 0) {
								event[local_34].model = local_30;
							}
							*(FixedEvent **)local_38 = (FixedEvent *)(event + local_34);
							local_38 = &((FixedEvent *)*local_38)->next;
							VisibilityLists(VIS_ADD, local_34);
							local_34 = local_34 + 1;
						}
						count = *piVar8;
						while (1 < count + 0x80000000U) {
							count = piVar8[1];
							piVar8 = piVar8 + 1;
						}
						piVar8 = piVar8 + 1;
					} while ((int)uVar9 < i);
				}
				fixedEvent = &chicagoDoor;
				InitDoor(&chicagoDoor, (_EVENT ***)&local_38, (int *)&local_34);
				InitDoor(&FixedEvent_0009e938, (_EVENT ***)&local_38, (int *)&local_34);
				*(FixedEvent **)local_38 = &FixedEvent_0009e964;
				local_38 = &((FixedEvent *)*local_38)->next;
				VisibilityLists(VIS_ADD, 0x82);
				if (full != 0) {
					FixedEvent_0009e964._20_4_ = FindModelIdxWithName((char *)&PTR_DAT_000aa4d0);
					FixedEvent_0009e964._24_4_ = FindModelIdxWithName((char *)&PTR_DAT_000aa4d4);
					FixedEvent_0009e964.model = FindModelIdxWithName(s_FRAME_000aa470);
					chicagoDoor.model = FindModelIdxWithName(chicagoDoor.modelName);
					FixedEvent_0009e938.model = FindModelIdxWithName(FixedEvent_0009e938.modelName);
					local_2c = FindModelIdxWithName(s_LORRY_000aa4d8);
				}
				count = 0x28;
				iVar4 = 6;
				multiCar.count = 0;
				multiCar.event = event + local_34;
				i = 0;
				do {
					*(undefined2 *)((int)&(multiCar.event)->flags + i) = 0x680;
					if (full != 0) {
						*(int *)((int)&(multiCar.event)->model + i) = local_2c;
					}
					*(undefined2 *)((int)&(multiCar.event)->radius + i) = 0;
					iVar4 = iVar4 + -1;
					iVar5 = (int)&((multiCar.event)->position).vx + count;
					count = count + 0x28;
					*(int *)((int)&(multiCar.event)->next + i) = iVar5;
					i = i + 0x28;
				} while (-1 < iVar4);
				local_34 = local_34 + 7;
			}
		}
		else {
			if (GameLevel == 2) {
				if (full != 0) {
					unaff_s5 = FindModelIdxWithName(s_TRAIN_000aa4f8);
				}
				uVar9 = 2;
				if (gCurrentMissionNumber == 0x16) {
					uVar9 = 9;
				}
				i = 0;
				if (uVar9 != 0) {
					piVar8 = INT_ARRAY_0009e874;
					count = 0;
					do {
						piVar6 = (int *)((int)&(event->position).vx + count);
						*(undefined2 *)((int)piVar6 + 0x1e) = 4000;
						if (i < 2) {
							*(undefined2 *)(piVar6 + 7) = 0x302;
							*piVar6 = VegasParkedTrains;
							iVar4 = *piVar8;
							*(undefined2 *)((int)piVar6 + 0x12) = 2;
							piVar6[2] = iVar4;
							VisibilityLists(VIS_ADD, i);
						}
						iVar4 = (int)&(event->position).vx + count;
						*(undefined4 *)(iVar4 + 4) = 0xfffffd22;
						*(undefined2 *)(iVar4 + 0x10) = 0;
						if (full != 0) {
							*(int *)(iVar4 + 0x20) = unaff_s5;
						}
						piVar8 = piVar8 + 1;
						i = i + 1;
						*(FixedEvent **)local_38 = (FixedEvent *)((int)&(event->position).vx + count);
						count = count + 0x28;
						local_38 = &((FixedEvent *)*local_38)->next;
					} while (i < (int)uVar9);
				}
				ev_00 = event;
				ev = &vegasDoor;
				i = 4;
				event[1].next = (_EVENT *)0x0;
				ev_00[uVar9 - 1].next = (_EVENT *)0x0;
				fixedEvent = &vegasDoor;
				local_34 = uVar9;
				do {
					InitDoor(ev, (_EVENT ***)&local_38, (int *)&local_34);
					i = i + -1;
					ev = ev + 1;
				} while (-1 < i);
				if (full != 0) {
					piVar8 = &vegasDoor.model;
					i = 4;
					do {
						i = i + -1;
						count = FindModelIdxWithName((char *)piVar8[2]);
						*piVar8 = count;
						piVar8 = piVar8 + 0xb;
					} while (-1 < i);
				}
				ev_00 = event;
				if (gCurrentMissionNumber != 0x1e) goto LAB_000474bc;
				event[local_34].position.vx = -0x2ffb;
				ev_00[local_34].position.vy = -0x113;
				i = 0;
				ev_00[local_34].position.vz = 0xcd61b;
				ev_00[local_34 + 1].position.vx = -0x34aa;
				ev_00[local_34 + 1].position.vy = -0xfa;
				ev_00[local_34 + 1].position.vz = 0xcd5e0;
				ev_00[local_34 + 2].position.vx = -0x382c;
				ev_00[local_34 + 2].position.vy = -0x114;
				ev_00[local_34 + 2].position.vz = 0xcd383;
				do {
					if (i == 2) {
						ev_00[local_34 + i].rotation = 0;
					}
					else {
						ev_00[local_34 + i].rotation = 0x800;
					}
					ev_00[local_34 + i].flags = 0x400;
					count = local_34 + i;
					i = i + 1;
					ev_00[count].radius = 0;
				} while (i < 3);
				if (full != 0) {
					i = FindModelIdxWithName(s_DETONATOR_00010978);
					ev_00 = event;
					event[local_34].model = i;
					ev_00[local_34 + 1].model = i;
					ev_00[local_34 + 2].model = i;
				}
			}
			else {
				if (GameLevel != 3) goto LAB_000474bc;
				event->radius = 0;
				if (full != 0) {
					i = FindModelIdxWithName(s_BOAT01_000aa500);
					event->model = i;
				}
				ev_00 = event;
				i = INT_0009e8b8;
				cameraEventsActive = 1;
				(event->position).vy = 0x100;
				(ev_00->position).vx = i;
				i = INT_ARRAY_0009e8bc[0];
				ev_00->flags = -0x77ad;
				ev_00->rotation = 0;
				ev_00->timer = -1;
				ev_00->node = INT_ARRAY_0009e8bc;
				ev_00->data = RioFerryData;
				(ev_00->position).vz = i;
				VisibilityLists(VIS_ADD, 0);
				i = 5;
				MakeEventTrackable(event);
				*local_38 = event;
				ev = &rioDoor;
				local_34 = 1;
				fixedEvent = &rioDoor;
				local_38 = &((FixedEvent *)*local_38)->next;
				do {
					InitDoor(ev, (_EVENT ***)&local_38, (int *)&local_34);
					i = i + -1;
					ev = ev + 1;
				} while (-1 < i);
				if (full != 0) {
					piVar8 = &rioDoor.model;
					i = 5;
					do {
						i = i + -1;
						count = FindModelIdxWithName((char *)piVar8[2]);
						*piVar8 = count;
						piVar8 = piVar8 + 0xb;
					} while (-1 < i);
					foam.model = FindModelPtrWithName(&DAT_000aa4f0);
					unaff_s3 = FindModelIdxWithName(s_DETONATOR_00010978);
				}
				ev_00 = event;
				if (gCurrentMissionNumber != 0x23) {
					if (gCurrentMissionNumber - 0x27U < 2) {
						bVar1 = gCurrentMissionNumber == 0x27;
						event[local_34].flags = 0xc0;
						if (bVar1) {
							ev_00[local_34].position.vx = 0xfec7;
							ev_00[local_34].position.vy = -0x306;
							ev_00[local_34].position.vz = -0x7ead2;
							ev_00[local_34].rotation = 0xa40;
							ev_00[local_34].timer = -1;
							HelicopterData.pitch = 0;
							HelicopterData.roll = 0;
						}
						else {
							ev_00[local_34].position.vy = -1000;
							ev_00[local_34].rotation = -1;
							ev_00[local_34].timer = 0;
							ev_00[local_34].flags = ev_00[local_34].flags | 0x100;
						}
						lVar3 = Random2(0);
						ev_00 = event;
						HelicopterData.rotorrot = (ushort)lVar3 & 0xff;
						HelicopterData.rotorvel = 1;
						*(_TARGET **)&event[local_34].node = MissionTargets + 4;
						ev_00[local_34].radius = 0;
						if (full != 0) {
							HelicopterData.cleanModel = FindModelIdxWithName(s_CHOPPERCLEAN_00010984);
							HelicopterData.deadModel = FindModelIdxWithName(s_CHOPPERDAM_00010994);
							GetTextureDetails(s_ROTOR_000aa508, &HelicopterData.rotorTexture);
						}
						event[local_34].model = HelicopterData.cleanModel;
						VisibilityLists(VIS_ADD, local_34);
						MakeEventTrackable(event + local_34);
						*(FixedEvent **)local_38 = (FixedEvent *)(event + local_34);
						local_34 = local_34 + 1;
						local_38 = &((FixedEvent *)*local_38)->next;
					}
					goto LAB_000474bc;
				}
				event[local_34].position.vx = 0x31330;
				ev_00[local_34].position.vy = -0xb1;
				ev_00[local_34].position.vz = 0x5e0e0;
				ev_00[local_34 + 1].position.vx = 0x312b0;
				ev_00[local_34 + 1].position.vy = -0xb1;
				ev_00[local_34 + 1].position.vz = 0x5f050;
				ev_00[local_34 + 2].position.vx = 0x30ad0;
				ev_00[local_34 + 2].position.vy = -0xb1;
				i = 0;
				ev_00[local_34 + 2].position.vz = 0x5f050;
				do {
					if (i == 2) {
						sVar2 = 0xc00;
					}
					else {
						sVar2 = 0x400;
					}
					event[local_34 + i].rotation = sVar2;
					ev_00 = event;
					event[local_34 + i].flags = 0x80;
					ev_00[local_34 + i].radius = 0;
					ev_00[local_34 + i].data = ev_00->data + 1;
					p_Var7 = ev_00 + local_34 + i;
					iVar4 = (ev_00->position).vz - (p_Var7->position).vz;
					count = (ev_00->position).vy - (p_Var7->position).vy;
					piVar8 = (int *)SquareRoot0(iVar4 * iVar4 + count * count);
					if (iVar4 < 0) {
						piVar8 = (int *)-(int)piVar8;
					}
					p_Var7->node = piVar8;
					ev_00 = event;
					i = i + 1;
				} while (i < 3);
				if (full != 0) {
					event[local_34].model = unaff_s3;
					ev_00[local_34 + 1].model = unaff_s3;
					ev_00[local_34 + 2].model = unaff_s3;
				}
			}
			firstMissionEvent = event + local_34;
			local_34 = local_34 + 3;
		}
	}
LAB_000474bc:
	*(FixedEvent **)local_38 = (FixedEvent *)0x0;
	if (full != 0) {
		mallocptr = mallocptr + local_34 * 0x28;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitEventCamera()
 // line 974, offset 0x0004bf54
	/* begin block 1 */
		// Start line: 9359
	/* end block 1 */
	// End Line: 9360

	/* begin block 2 */
		// Start line: 9360
	/* end block 2 */
	// End Line: 9361

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitEventCamera(void)
{
	eventCamera.position = camera_position;
	eventCamera.yAng = camera_angle.vy;
	eventCamera.matrix = inv_camera_matrix;
	eventCamera.rotate = 1;
	events.camera = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ResetEventCamera()
 // line 983, offset 0x0004c014
	/* begin block 1 */
		// Start line: 9387
	/* end block 1 */
	// End Line: 9388

	/* begin block 2 */
		// Start line: 9391
	/* end block 2 */
	// End Line: 9392

	/* begin block 3 */
		// Start line: 9395
	/* end block 3 */
	// End Line: 9396

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void ResetEventCamera(void)
{
	camera_position = eventCamera.position;
	camera_angle.vy = eventCamera.yAng;
	inv_camera_matrix = eventCamera.matrix;
	events.camera = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetCamera(struct _EVENT *ev /*$s5*/)
 // line 991, offset 0x00047538
	/* begin block 1 */
		// Start line: 992
		// Start offset: 0x00047538
		// Variables:
	// 		int rotation; // $s4
	// 		int axis; // $a3
	// 		struct VECTOR pivot; // stack offset -96
	// 		int iPivot; // $a2
	// 		int height; // $a1
	// 		struct SVECTOR offset; // stack offset -80

		/* begin block 1.1 */
			// Start line: 1037
			// Start offset: 0x00047688
			// Variables:
		// 		struct MATRIX matrix; // stack offset -72
		// 		struct SVECTOR temp; // stack offset -40

			/* begin block 1.1.1 */
				// Start line: 1045
				// Start offset: 0x0004770C
			/* end block 1.1.1 */
			// End offset: 0x0004775C
			// End Line: 1055
		/* end block 1.1 */
		// End offset: 0x0004775C
		// End Line: 1057
	/* end block 1 */
	// End offset: 0x000479DC
	// End Line: 1104

	/* begin block 2 */
		// Start line: 2631
	/* end block 2 */
	// End Line: 2632

	/* begin block 3 */
		// Start line: 2659
	/* end block 3 */
	// End Line: 2660

/* WARNING: Could not reconcile some variable overlaps */

void SetCamera(_EVENT *ev)
{
	UNIMPLEMENTED();
	/*
	undefined4 in_zero;
	CAR_POLY *in_at;
	ushort uVar1;
	short ang;
	undefined4 uVar2;
	long lVar3;
	ushort uVar4;
	int iVar5;
	long local_60;
	short local_5c;
	long local_58;
	undefined4 local_50;
	undefined4 local_4c;
	undefined4 local_48;
	undefined4 local_44;
	undefined4 local_40;
	undefined4 local_3c;
	undefined4 local_38;
	long local_34;
	long local_30;
	long local_2c;
	undefined4 local_28;
	undefined4 local_24;

	memset(&local_50, 0, 8);
	if (eventCamera.rotate != 0) {
		inv_camera_matrix.m[0]._0_4_ = eventCamera.matrix.m[0]._0_4_;
		inv_camera_matrix.m._4_4_ = eventCamera.matrix.m._4_4_;
		inv_camera_matrix.m[1]._2_4_ = eventCamera.matrix.m[1]._2_4_;
		inv_camera_matrix.m[2]._0_4_ = eventCamera.matrix.m[2]._0_4_;
		inv_camera_matrix._16_4_ = eventCamera.matrix._16_4_;
		inv_camera_matrix.t[0] = eventCamera.matrix.t[0];
		inv_camera_matrix.t[1] = eventCamera.matrix.t[1];
		inv_camera_matrix.t[2] = eventCamera.matrix.t[2];
	}
	uVar2 = 0;
	if ((ev->flags & 0x800U) == 0) {
		uVar4 = ev->flags & 0x30;
		iVar5 = (int)ev->rotation;
		lVar3 = *ev->data;
	}
	else {
		lVar3 = (ev->position).vz;
		iVar5 = ev->data[1];
		local_50 = boatOffset._0_4_;
		local_4c = boatOffset._4_4_;
		uVar2 = 0x100;
		if (GameLevel == 1) {
			uVar2 = 0x6f;
		}
		uVar4 = 0;
	}
	if (uVar4 == 0) {
		iVar5 = -iVar5;
		local_60 = camera_position.vx;
		local_58 = lVar3;
	}
	else {
		local_58 = camera_position.vz;
		local_60 = lVar3;
	}
	if (iVar5 == 0) {
		camera_position.vx = eventCamera.position.vx + (short)local_50;
		camera_angle.vy = eventCamera.yAng;
		camera_position.vy = eventCamera.position.vy + local_50._2_2_;
		camera_position.vz = eventCamera.position.vz + (short)local_4c;
	}
	else {
		camera_position.vx = eventCamera.position.vx;
		camera_position.vx._0_2_ = (short)eventCamera.position.vx;
		camera_position.vy = eventCamera.position.vy;
		camera_position.vy._0_2_ = (short)eventCamera.position.vy;
		camera_position.vz = eventCamera.position.vz;
		camera_position.vz._0_2_ = (short)eventCamera.position.vz;
		camera_position.pad = eventCamera.position.pad;
		local_48 = 0x1000;
		local_3c = 0;
		local_44 = 0;
		local_40 = 0x1000;
		local_38 = CONCAT22(local_38._2_2_, 0x1000);
		ang = (short)iVar5;
		if (uVar4 == 0x10) {
			camera_angle.vy = camera_angle.vy - ang;
			in_at = CAR_POLY_ARRAY_000b0000;
			_RotMatrixY((MATRIX *)&local_48, ang);
		}
		else {
			if (uVar4 < 0x11) {
				if (uVar4 == 0) {
					_RotMatrixX((MATRIX *)&local_48, ang);
				}
			}
			else {
				if (uVar4 == 0x20) {
					_RotMatrixZ((MATRIX *)&local_48, ang);
				}
			}
		}
		local_5c = (short)uVar2;
		local_28 = CONCAT22((short)camera_position.vy - local_5c,
			(short)camera_position.vx - (short)local_60);
		local_24 = CONCAT22(local_24._2_2_, (short)camera_position.vz - (short)local_58);
		setCopControlWord(2, 0, local_48);
		setCopControlWord(2, 0x800, local_44);
		setCopControlWord(2, 0x1000, local_40);
		setCopControlWord(2, 0x1800, local_3c);
		setCopControlWord(2, 0x2000, local_38);
		setCopControlWord(2, 0x2800, local_60);
		setCopControlWord(2, 0x3000, uVar2);
		setCopControlWord(2, 0x3800, local_58);
		setCopReg(2, in_zero, local_28);
		setCopReg(2, in_at, local_24);
		copFunction(2, 0x480012);
		camera_position.vx = getCopReg(2, 0x19);
		camera_position.vy = getCopReg(2, 0x1a);
		camera_position.vz = getCopReg(2, 0x1b);
		uVar1 = local_44._2_2_ ^ local_48._2_2_ ^ local_44._2_2_;
		local_48 = local_48 & 0xffff | (uint)(ushort)(local_48._2_2_ ^ local_44._2_2_ ^ uVar1) << 0x10;
		uVar4 = (ushort)local_3c ^ (ushort)local_44 ^ (ushort)local_3c;
		local_44 = CONCAT22(uVar1, (ushort)local_44 ^ (ushort)local_3c ^ uVar4);
		uVar1 = local_3c._2_2_ ^ local_40._2_2_ ^ local_3c._2_2_;
		local_3c = CONCAT22(uVar1, uVar4);
		local_40 = local_40 & 0xffff | (uint)(ushort)(local_40._2_2_ ^ local_3c._2_2_ ^ uVar1) << 0x10;
		setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
		setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
		setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
		setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
		setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
		MulRotMatrix(&local_48);
		inv_camera_matrix.m[0]._0_4_ = local_48;
		inv_camera_matrix.m._4_4_ = local_44;
		inv_camera_matrix.m[1]._2_4_ = local_40;
		inv_camera_matrix.m[2]._0_4_ = local_3c;
		inv_camera_matrix._16_4_ = local_38;
		inv_camera_matrix.t[0] = local_34;
		inv_camera_matrix.t[1] = local_30;
		inv_camera_matrix.t[2] = local_2c;
		camera_position.vx = camera_position.vx + (short)local_50;
		camera_position.vy = camera_position.vy + local_50._2_2_;
		camera_position.vz = camera_position.vz + (short)local_4c;
	}
	SetCameraVector();
	if ((iVar5 != 0) || (eventCamera.rotate != 0)) {
		Set_Inv_CameraMatrix();
		SetCameraVector();
		SetupDrawMapPSX();
	}
	eventCamera.rotate = iVar5;
	if ((ev->flags & 0x800U) == 0) {
		events.draw = ev->model;
	}
	else {
		ev->flags = ev->flags & 0xfffe;
		events.draw = 0;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ EventCollisions(struct _CAR_DATA *cp /*$a2*/, int type /*$a1*/)
 // line 1107, offset 0x0004bc50
	/* begin block 1 */
		// Start line: 1108
		// Start offset: 0x0004BC50
		// Variables:
	// 		static struct SVECTOR offset; // offset 0x18
	/* end block 1 */
	// End offset: 0x0004BD2C
	// End Line: 1125

	/* begin block 2 */
		// Start line: 6981
	/* end block 2 */
	// End Line: 6982

	/* begin block 3 */
		// Start line: 6984
	/* end block 3 */
	// End Line: 6985

// [D]
void EventCollisions(_CAR_DATA *cp, int type)
{
	if (carsOnBoat >> CAR_INDEX(cp) == 0)
		return;

	if (type != 0) 
	{
		cp->hd.where.t[0] -= boatOffset.vx;
		cp->hd.where.t[1] -= boatOffset.vy;
		cp->hd.where.t[2] -= boatOffset.vz;
		events.camera = 0;
		return;
	}

	events.draw = 0;
	events.camera = 1;

	cp->hd.where.t[0] += boatOffset.vx;
	cp->hd.where.t[1] += boatOffset.vy;
	cp->hd.where.t[2] += boatOffset.vz;
}



// decompiled code
// original method signature: 
// void /*$ra*/ NextNode(struct _EVENT *ev /*$a0*/)
 // line 1127, offset 0x0004c0a4
	/* begin block 1 */
		// Start line: 9546
	/* end block 1 */
	// End Line: 9547

	/* begin block 2 */
		// Start line: 9686
	/* end block 2 */
	// End Line: 9687

	/* begin block 3 */
		// Start line: 9687
	/* end block 3 */
	// End Line: 9688

// [D]
void NextNode(_EVENT *ev)
{
	int *piVar1;

	piVar1 = ev->node;
	if (piVar1[2] == -0x7ffffffe)
	{
		ev->node = piVar1 + 2;
	}
	else
	{
		ev->node = piVar1 + 1;
		ev->flags = ev->flags ^ 0x8000;
	}

	if (*ev->node == -0x7fffffff) 
	{
		ev->node = ev->data + 3;
	}
	else if (ev->node[3] == -0x80000000) 
	{
		ev->flags = ev->flags & 0x8fff;
		return;
	}

	ev->flags = ev->flags & 0x8fffU | 0x3000;
	SetElTrainRotation(ev);
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepFromToEvent(struct _EVENT *ev /*$a3*/)
 // line 1152, offset 0x000479dc
	/* begin block 1 */
		// Start line: 1153
		// Start offset: 0x000479DC

		/* begin block 1.1 */
			// Start line: 1160
			// Start offset: 0x00047A08
			// Variables:
		// 		int *from; // $a1
		// 		int *to; // $t4
		// 		long *current; // $t0
		// 		int d; // $a0
		// 		int d2; // $t2
		/* end block 1.1 */
		// End offset: 0x00047BC4
		// End Line: 1208
	/* end block 1 */
	// End offset: 0x00047BD4
	// End Line: 1209

	/* begin block 2 */
		// Start line: 2962
	/* end block 2 */
	// End Line: 2963

	/* begin block 3 */
		// Start line: 3011
	/* end block 3 */
	// End Line: 3012

void StepFromToEvent(_EVENT *ev)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;
	uint uVar2;
	uint uVar3;
	int iVar4;
	int iVar5;
	_EVENT *in_t0;
	_EVENT *p_Var6;
	int iVar7;
	uint uVar8;
	int *piVar9;

	if (0 < ev->timer) {
		ev->timer = ev->timer + -1;
		return;
	}
	if (ev->timer != 0) {
		return;
	}
	uVar2 = (int)ev->flags & 0xc000;
	piVar9 = ev->node + 1;
	if (uVar2 == 0x4000) {
		p_Var6 = (_EVENT *)&(ev->position).vy;
	}
	else {
		if (uVar2 < 0x4001) {
			p_Var6 = ev;
			if (uVar2 != 0) {
				p_Var6 = in_t0;
			}
		}
		else {
			p_Var6 = in_t0;
			if (uVar2 == 0x8000) {
				p_Var6 = (_EVENT *)&(ev->position).vz;
			}
		}
	}
	iVar7 = (p_Var6->position).vx;
	iVar5 = *ev->node;
	iVar4 = *piVar9;
	uVar3 = iVar7 - iVar5;
	uVar8 = iVar4 - iVar7;
	uVar2 = uVar3;
	if ((int)uVar3 < 0) {
		uVar2 = -uVar3;
	}
	uVar1 = uVar8;
	if ((int)uVar8 < 0) {
		uVar1 = -uVar8;
	}
	if ((int)uVar1 < (int)uVar2) {
		uVar3 = uVar8;
	}
	uVar2 = iVar4 - iVar5 >> 0x1f;
	if ((ev->flags & 0xc000U) == 0x4000) {
		if ((int)uVar3 < 0) {
			uVar3 = -uVar3;
		}
		if (0x400 < (int)uVar3) {
			uVar3 = *ev->data ^ uVar2;
			goto LAB_00047b78;
		}
		iVar4 = (*ev->data + -1) * (int)rcossin_tbl[(uVar3 & 0xfff) * 2];
	}
	else {
		if ((int)uVar3 < 0) {
			uVar3 = -uVar3;
		}
		if (0x800 < (int)uVar3) {
			uVar3 = *ev->data ^ uVar2;
			goto LAB_00047b78;
		}
		iVar4 = (*ev->data + -1) *
			(int)*(short *)((int)rcossin_tbl + ((uVar3 - ((int)uVar3 >> 0x1f)) * 2 & 0x3ffc));
	}
	if (iVar4 < 0) {
		iVar4 = iVar4 + 0xfff;
	}
	uVar3 = (iVar4 >> 0xc) + 1U ^ uVar2;
LAB_00047b78:
	(p_Var6->position).vx = iVar7 + (uVar3 - uVar2);
	iVar4 = *piVar9;
	if ((int)(uVar8 ^ iVar4 - (p_Var6->position).vx) < 0) {
		(p_Var6->position).vx = iVar4;
		ev->timer = -1;
		if (ev == events.cameraEvent) {
			SpecialCamera(SPECIAL_CAMERA_RESET, 0);
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepPathEvent(struct _EVENT *ev /*$s0*/)
 // line 1214, offset 0x00047bd4
	/* begin block 1 */
		// Start line: 1215
		// Start offset: 0x00047BD4
		// Variables:
	// 		int *from; // $a1
	// 		int *to; // $t1
	// 		long *current; // $t3
	// 		static int speed; // offset 0x20

		/* begin block 1.1 */
			// Start line: 1225
			// Start offset: 0x00047C08
			// Variables:
		// 		int flags; // $v0
		/* end block 1.1 */
		// End offset: 0x00047C34
		// End Line: 1233

		/* begin block 1.2 */
			// Start line: 1242
			// Start offset: 0x00047C7C
			// Variables:
		// 		enum Station station; // $t2

			/* begin block 1.2.1 */
				// Start line: 1276
				// Start offset: 0x00047D2C
				// Variables:
			// 		int direction; // $t2
			// 		int loop; // $a2
			// 		int *i; // $a0
			// 		int turn[4]; // stack offset -48
			// 		struct XZPAIR centre; // stack offset -32
			// 		struct XZPAIR offset; // stack offset -24
			/* end block 1.2.1 */
			// End offset: 0x00047F98
			// End Line: 1348

			/* begin block 1.2.2 */
				// Start line: 1355
				// Start offset: 0x00047FB0
				// Variables:
			// 		int d; // $a0
			// 		int d1; // $v1
			// 		int dir; // $t4
			/* end block 1.2.2 */
			// End offset: 0x000482F8
			// End Line: 1447
		/* end block 1.2 */
		// End offset: 0x000482F8
		// End Line: 1448
	/* end block 1 */
	// End offset: 0x0004830C
	// End Line: 1449

	/* begin block 2 */
		// Start line: 3131
	/* end block 2 */
	// End Line: 3132

	/* begin block 3 */
		// Start line: 3137
	/* end block 3 */
	// End Line: 3138

void StepPathEvent(_EVENT *ev)
{
	UNIMPLEMENTED();
	/*
	ushort *puVar1;
	ushort uVar2;
	short sVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int *piVar9;
	int *piVar10;
	uint uVar11;
	int *piVar12;
	int iVar13;
	_EVENT *p_Var14;
	int iVar15;
	int local_30[4];
	int local_20;
	int local_1c;
	int local_18;
	int local_14;

	sVar3 = ev->timer;
	if (ev->timer != 0) {
		ev->timer = sVar3 + -1;
		if (sVar3 == 1) {
			do {
				NextNode(ev);
				puVar1 = (ushort *)&ev->flags;
				ev = ev->next;
				if (ev == (_EVENT *)0x0) {
					speed_49 = 0;
					return;
				}
			} while (ev->flags == (*puVar1 & 0xfbff));
		}
		else {
			if ((ev->flags & 0x100U) != 0) {
				ev->timer = sVar3;
			}
		}
		speed_49 = 0;
		return;
	}
	uVar2 = ev->flags;
	if ((speed_49 == 0) && ((uVar2 & 0x400) == 0)) {
		return;
	}
	piVar10 = ev->node;
	piVar12 = piVar10 + 2;
	if (*piVar10 == -0x7ffffffe) {
		iVar13 = 2;
		piVar9 = piVar10 + 1;
	}
	else {
		iVar13 = 1;
		piVar9 = piVar10;
		if (piVar10[2] == -0x7ffffffe) {
			piVar12 = piVar10 + 3;
		}
		else {
			iVar13 = 0;
			if (piVar10[-1] == -0x7ffffffe) {
				piVar9 = piVar10 + -2;
			}
			else {
				if (piVar10[2] == -0x7fffffff) {
					piVar12 = ev->data + 3;
				}
				else {
					if ((piVar10[1] == -0x7fffffff) && (ev->data + 3 < piVar12)) {
						piVar12 = ev->data + 4;
					}
				}
			}
		}
	}
	if ((uVar2 & 0x7000) == 0x1000) {
		iVar13 = -1;
		if ((uVar2 & 0x8000) == 0) {
			iVar13 = 1;
			uVar11 = 0;
		}
		else {
			uVar11 = 3;
		}
		if (*piVar10 == -0x7ffffffe) {
			piVar9 = piVar10 + -2;
		}
		if (uVar11 < 4) {
			piVar10 = local_30 + uVar11;
			do {
				if (*piVar9 == -0x7fffffff) {
					piVar9 = ev->data + 3;
				}
				else {
					if (*piVar9 == -0x7ffffffe) {
						piVar9 = piVar9 + 2;
					}
				}
				uVar11 = uVar11 + iVar13;
				iVar4 = *piVar9;
				piVar9 = piVar9 + 1;
				*piVar10 = iVar4;
				piVar10 = piVar10 + iVar13;
			} while (uVar11 < 4);
		}
		local_20 = local_30[2] + -0x800;
		if (-1 < local_30[0] - local_30[2]) {
			local_20 = local_30[2] + 0x800;
		}
		local_1c = local_30[1] + -0x800;
		if (-1 < local_30[3] - local_30[1]) {
			local_1c = local_30[1] + 0x800;
		}
		if ((ev->flags & 0x400U) != 0) {
			speed_49 = *ev->data;
		}
		local_18 = ((ev->position).vz - local_1c) * speed_49;
		if (local_18 < 0) {
			local_18 = local_18 + 0x7ff;
		}
		local_18 = local_18 >> 0xb;
		local_14 = (local_20 - (ev->position).vx) * speed_49;
		if (local_14 < 0) {
			local_14 = local_14 + 0x7ff;
		}
		local_14 = local_14 >> 0xb;
		if (((local_30[2] - local_30[0]) * local_18 + (local_30[3] - local_30[1]) * local_14) * iVar13 <
			0) {
			local_18 = -local_18;
			local_14 = -local_14;
		}
		(ev->position).vx = (ev->position).vx + local_18;
		(ev->position).vz = (ev->position).vz + local_14;
		sVar3 = ratan2(local_18, local_14);
		ev->rotation = sVar3 + 0x400U & 0xfff;
		if (((int)ev->flags & 0x8000U) == 0) {
			iVar13 = (ev->position).vz - local_1c;
			if (local_30[3] - local_30[1] < 0) {
				if (-1 < iVar13) {
					return;
				}
			}
			else {
				if (iVar13 < 1) {
					return;
				}
			}
			(ev->position).vx = local_30[2];
			NextNode(ev);
			return;
		}
		iVar13 = (ev->position).vx - local_20;
		if (local_30[0] - local_30[2] < 0) {
			if (-1 < iVar13) {
				return;
			}
		}
		else {
			if (iVar13 < 1) {
				return;
			}
		}
		(ev->position).vz = local_30[1];
		NextNode(ev);
		return;
	}
	p_Var14 = ev;
	if ((uVar2 & 0x8000) != 0) {
		p_Var14 = (_EVENT *)&(ev->position).vz;
	}
	iVar5 = (p_Var14->position).vx;
	iVar15 = -1;
	iVar4 = *piVar12 - iVar5;
	if (-1 < iVar4) {
		iVar15 = 1;
	}
	iVar6 = *piVar9;
	if (iVar4 < 0) {
		iVar4 = -iVar4;
	}
	iVar8 = iVar5 - iVar6;
	if (iVar8 < 0) {
		iVar8 = -iVar8;
	}
	if (iVar4 < iVar8) {
		iVar7 = 2;
		iVar8 = iVar4;
	}
	else {
		iVar7 = 1;
	}
	iVar4 = iVar5 - iVar6;
	if (iVar13 == iVar7) {
		iVar13 = 0;
	}
	if (iVar8 < 0) {
		iVar8 = -iVar8;
	}
	if (iVar4 < 0) {
		iVar4 = iVar6 - iVar5;
	}
	if (iVar4 <= iVar8) {
		iVar4 = (p_Var14->position).vx;
		iVar8 = iVar4 - iVar6;
		if (iVar8 < 0) {
			iVar8 = iVar6 - iVar4;
		}
	}
	if ((uVar2 & 0x400) != 0) {
		if ((uVar2 & 0x80) != 0) {
			if (CameraCnt < 0x1000) {
				speed_49 = ev->data[1] * (0x1000 - CameraCnt) + ev->data[2] * CameraCnt;
				if (speed_49 < 0) {
					speed_49 = speed_49 + 0xfff;
				}
				speed_49 = speed_49 >> 0xc;
			}
			else {
				speed_49 = ev->data[2];
			}
			debugSpeed = speed_49;
		}
		speed_49 = ev->data[1];
	}
	if (((iVar8 < 6000) || ((iVar13 == 0 && (iVar8 < 0x1f70)))) && ((ev->flags & 0x400U) != 0)) {
		if (iVar13 == 0) {
			if ((ev->flags & 0x7000U) != 0x3000) goto LAB_00048238;
			iVar4 = (speed_49 - *ev->data) *
				(int)rcossin_tbl[(((iVar8 + -0x800) * 0x400) / 0x1f70 & 0xfffU) * 2];
			uVar11 = iVar8 + -0x800 >> 0x1f;
			speed_49 = (*ev->data ^ uVar11) - uVar11;
			if (iVar4 < 0) {
				iVar4 = iVar4 + 0xfff;
			}
		}
		else {
			iVar4 = (speed_49 + -5) * (int)rcossin_tbl[((iVar8 << 10) / 6000 & 0xfffU) * 2];
			speed_49 = (iVar8 >> 0x1f ^ 5U) - (iVar8 >> 0x1f);
			if (iVar4 < 0) {
				iVar4 = iVar4 + 0xfff;
			}
		}
		speed_49 = speed_49 + (iVar4 >> 0xc);
	}
LAB_00048238:
	iVar4 = (p_Var14->position).vx + speed_49 * iVar15;
	(p_Var14->position).vx = iVar4;
	if (iVar13 == 0) {
		uVar2 = ev->flags;
		if ((uVar2 & 0x7000) != 0) {
			if (0x7ff < (*piVar12 - iVar4) * iVar15) {
				return;
			}
			if ((uVar2 & 0x7000) == 0x3000) {
				ev->flags = uVar2 & 0x8fff | 0x1000;
				return;
			}
			return;
		}
	}
	if ((*piVar12 - iVar4) * iVar15 < 0) {
		if (iVar13 == 0) {
			InitTrain(ev, 0, 0);
		}
		else {
			if ((ev->flags & 0x400U) != 0) {
				ev->timer = 300;
			}
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetBridgeRotation(int timer /*$a0*/)
 // line 1452, offset 0x0004c158
	/* begin block 1 */
		// Start line: 1453
		// Start offset: 0x0004C158
		// Variables:
	// 		int angle; // $v1
	/* end block 1 */
	// End offset: 0x0004C208
	// End Line: 1476

	/* begin block 2 */
		// Start line: 10337
	/* end block 2 */
	// End Line: 10338

	/* begin block 3 */
		// Start line: 10339
	/* end block 3 */
	// End Line: 10340

// [D]
int GetBridgeRotation(int timer)
{
	static int debugRotation = -1;;

	int iVar1;

	if (debugRotation != -1)
		return debugRotation;

	if (2600 < timer) 
	{
		return 0;
	}

	if (timer < 1601)
	{
		if (1000 < timer) 
		{
			timer = 1000;
		}
	}
	else 
	{
		timer = 2600 - timer;
	}

	iVar1 = (0x1000 - rcossin_tbl[((timer << 0xb) / 1000 & 0xfffU) * 2 + 1]) * 800;

	return iVar1 >> 0xd;
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepHelicopter(struct _EVENT *ev /*$s0*/)
 // line 1478, offset 0x0004830c
	/* begin block 1 */
		// Start line: 1479
		// Start offset: 0x0004830C
		// Variables:
	// 		static int rotacc; // offset 0xa4

		/* begin block 1.1 */
			// Start line: 1485
			// Start offset: 0x00048334
			// Variables:
		// 		int b; // $a0
		// 		int c; // $t2
		// 		int d; // $v1
		// 		int t; // $a1
		// 		int t2; // $a3
		// 		int t3; // $v1
		// 		int dx1; // $a2
		// 		int dx2; // $t1
		// 		int dx3; // $t0
		// 		int dz1; // $v0
		// 		int dz2; // $a3
		// 		int dz3; // $a0

			/* begin block 1.1.1 */
				// Start line: 1522
				// Start offset: 0x000484A0
				// Variables:
			// 		struct XZPAIR vel; // stack offset -56
			// 		int direction; // $t1
			// 		int temp; // $t1
			// 		int dt; // $a0
			// 		int d2p; // $v1
			// 		int d2r; // $v1
			// 		int pitch; // $a1
			// 		int roll; // $a2
			// 		static int rotating; // offset 0x24
			/* end block 1.1.1 */
			// End offset: 0x000487F4
			// End Line: 1577

			/* begin block 1.1.2 */
				// Start line: 1590
				// Start offset: 0x00048854
				// Variables:
			// 		struct VECTOR pos; // stack offset -48
			/* end block 1.1.2 */
			// End offset: 0x00048854
			// End Line: 1591
		/* end block 1.1 */
		// End offset: 0x00048930
		// End Line: 1609

		/* begin block 1.2 */
			// Start line: 1613
			// Start offset: 0x00048948
			// Variables:
		// 		struct VECTOR pos; // stack offset -56
		// 		struct VECTOR drift; // stack offset -32
		/* end block 1.2 */
		// End offset: 0x00048948
		// End Line: 1613
	/* end block 1 */
	// End offset: 0x00048A60
	// End Line: 1633

	/* begin block 2 */
		// Start line: 3674
	/* end block 2 */
	// End Line: 3675

	/* begin block 3 */
		// Start line: 3704
	/* end block 3 */
	// End Line: 3705

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void StepHelicopter(_EVENT *ev)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	short sVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int *piVar12;
	int local_38;
	int local_34;
	int local_30;
	long local_2c;
	long local_28;
	VECTOR local_20;

	uVar1 = ev->timer;
	iVar6 = (uint)uVar1 << 0x10;
	if (iVar6 < 0) goto LAB_00048934;
	iVar6 = iVar6 >> 0x13;
	iVar8 = iVar6 * iVar6 + 0x800 >> 0xc;
	piVar12 = ev->node;
	iVar11 = *piVar12;
	iVar3 = iVar8 * iVar6 + 0x800 >> 0xc;
	iVar5 = (iVar3 * 3 + iVar8 * -5) / 2 + 0x1000;
	iVar10 = iVar8 * 2 + (iVar6 + iVar3 * -3) / 2;
	iVar3 = (iVar3 - iVar8) / 2;
	iVar6 = piVar12[3];
	iVar7 = piVar12[1];
	iVar9 = piVar12[5];
	iVar8 = piVar12[7];
	(ev->position).vx =
		iVar11 + ((piVar12[2] - iVar11) * iVar5 + (piVar12[4] - iVar11) * iVar10 +
		(piVar12[6] - iVar11) * iVar3 + 0x800 >> 0xc);
	(ev->position).vz =
		piVar12[1] +
		((iVar6 - iVar7) * iVar5 + (iVar9 - iVar7) * iVar10 + (iVar8 - iVar7) * iVar3 + 0x800 >> 0xc)
		;
	uVar1 = uVar1 + (short)HelicopterData.speed;
	ev->timer = uVar1;
	if ((int)((uint)uVar1 << 0x10) < 0) {
		if ((uint)(piVar12[8] == 0) == piVar12[9]) {
			ev->timer = -1;
		}
		else {
			ev->timer = 0;
			ev->node = piVar12 + 2;
		}
	}
	if (ev->rotation == -1) {
		piVar12 = ev->node;
		local_38 = (piVar12[4] - *piVar12) / 2;
		local_34 = (piVar12[5] - piVar12[1]) / 2;
		sVar2 = ratan2(local_38, local_34);
		ev->rotation = sVar2;
		rotating_57 = 0;
		HelicopterData.pitch = 0;
		HelicopterData.roll = 0;
		HelicopterData.dp = 0;
		HelicopterData.dr = 0;
	}
	else {
		local_38 = (ev->position).vx - HelicopterData.lastX;
		local_34 = (ev->position).vz - HelicopterData.lastZ;
	}
	iVar3 = ratan2(local_38, local_34);
	uVar4 = (uint)(ushort)ev->rotation & 0xfff;
	iVar6 = local_34 * rcossin_tbl[uVar4 * 2];
	local_34 = local_34 * rcossin_tbl[uVar4 * 2 + 1] + local_38 * rcossin_tbl[uVar4 * 2];
	local_38 = local_38 * rcossin_tbl[uVar4 * 2 + 1] - iVar6;
	iVar6 = local_34;
	if (local_34 < 0) {
		iVar6 = -local_34;
	}
	iVar5 = (int)HelicopterData.pitch;
	if (iVar6 < 0xdbba1) {
		iVar5 = -iVar5 - ((int)((uint)(ushort)rcossin_tbl[((local_34 * 0x400) / 900000 & 0xfffU) * 2] <<
			0x10) >> 0x13);
	}
	else {
		if (local_34 < 1) {
			iVar5 = 0x200 - iVar5;
		}
		else {
			iVar5 = -0x200 - iVar5;
		}
	}
	iVar8 = (int)HelicopterData.roll;
	iVar6 = local_38;
	if (local_38 < 0) {
		iVar6 = -local_38;
	}
	if (iVar6 < 0x249f1) {
		iVar8 = ((int)((uint)(ushort)rcossin_tbl[((local_38 * 0x400) / 150000 & 0xfffU) * 2] << 0x10) >>
			0x13) - iVar8;
	}
	else {
		if (local_38 < 1) {
			iVar8 = -0x200 - iVar8;
		}
		else {
			iVar8 = 0x200 - iVar8;
		}
	}
	iVar7 = iVar5 - HelicopterData.dp;
	iVar6 = iVar7;
	if (iVar7 < 0) {
		iVar6 = -iVar7;
	}
	if (iVar6 < 5) {
		HelicopterData.dp = (short)iVar5;
	}
	else {
		uVar1 = (ushort)(iVar7 >> 0x1f);
		HelicopterData.dp = HelicopterData.dp + ((uVar1 ^ 5) - uVar1);
	}
	iVar5 = iVar8 - HelicopterData.dr;
	iVar6 = iVar5;
	if (iVar5 < 0) {
		iVar6 = -iVar5;
	}
	if (iVar6 < 5) {
		HelicopterData.dr = (short)iVar8;
	}
	else {
		uVar1 = (ushort)(iVar5 >> 0x1f);
		HelicopterData.dr = HelicopterData.dr + ((uVar1 ^ 5) - uVar1);
	}
	HelicopterData.pitch = (HelicopterData.pitch + HelicopterData.dp + 0x800U & 0xfff) - 0x800;
	HelicopterData.roll = (HelicopterData.roll + HelicopterData.dr + 0x800U & 0xfff) - 0x800;
	iVar3 = ((iVar3 - ev->rotation) + 0x800U & 0xfff) - 0x800;
	iVar6 = iVar3;
	if (iVar3 < 0) {
		iVar6 = -iVar3;
	}
	if (iVar6 < 0x201) {
		iVar6 = (int)((uint)*(ushort *)((int)rcossin_tbl + (iVar3 * 8 & 0x3ff8U)) << 0x10) >> 0x12;
	}
	else {
		iVar6 = -0x400;
		if (0 < iVar3) {
			iVar6 = 0x400;
		}
	}
	ev->rotation = ev->rotation + (short)((iVar6 * iVar6 + 0x800 >> 0xc) * iVar6 + 0x800 >> 0xc) &
		0xfff;
	iVar6 = GetSurfaceIndex((VECTOR *)ev);
	if (iVar6 == -0x17) {
		iVar3 = (ev->position).vy;
		iVar6 = iVar3 + 10;
		if (iVar3 < -0x32) {
		LAB_000488b0:
			(ev->position).vy = iVar6;
		}
		else {
			local_2c = 0;
			local_30 = (ev->position).vx;
			local_28 = (ev->position).vz;
			Setup_Smoke((VECTOR *)(&local_38 + 8), 100, 500, 2, 0, &dummy, 0);
		}
	}
	else {
		iVar6 = (ev->position).vy;
		if (-1000 < iVar6) {
			iVar6 = iVar6 + -10;
			goto LAB_000488b0;
		}
	}
	HelicopterData.lastX = (ev->position).vx;
	HelicopterData.lastZ = (ev->position).vz;
	SetMSoundVar((int)ev, (VECTOR *)0x0);
	if (((ev->flags & 0x100U) != 0) && (uVar4 = Random2(0), (uVar4 & 3) == (CameraCnt & 3U))) {
		Setup_Smoke((VECTOR *)ev, 100, 500, 1, 0, &dummy, 0);
	}
LAB_00048934:
	if (ev->model == HelicopterData.deadModel) {
		local_20.vx = DAT_000109a0;
		local_20.vy = DAT_000109a4;
		local_20.vz = DAT_000109a8;
		local_20.pad = DAT_000109ac;
		uVar4 = rand();
		local_34 = -200;
		local_38 = (ev->position).vx + (uVar4 & 0xff) + -0x80;
		uVar4 = rand();
		local_30 = (ev->position).vz + (uVar4 & 0xff) + -0x80;
		Setup_Smoke((VECTOR *)&local_38, 0x32, 100, 4, 0, &dummy, 0);
		Setup_Smoke((VECTOR *)&local_38, 100, 500, 1, 0, &local_20, 0);
		SetMSoundVar(0, (VECTOR *)0x0);
	}
	else {
		HelicopterData.rotorrot = HelicopterData.rotorrot + HelicopterData.rotorvel;
		HelicopterData.rotorvel = HelicopterData.rotorvel + DAT_000aa514;
		iVar6 = (int)HelicopterData.rotorvel;
		if (iVar6 < 0) {
			iVar6 = -iVar6;
		}
		if (0x100 < iVar6) {
			_DAT_000aa514 = -_DAT_000aa514;
		}
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepEvents()
 // line 1642, offset 0x00048a60
	/* begin block 1 */
		// Start line: 1645
		// Start offset: 0x00048A60
		// Variables:
	// 		struct _EVENT *ev; // $s0

		/* begin block 1.1 */
			// Start line: 1671
			// Start offset: 0x00048AC4
			// Variables:
		// 		struct VECTOR old; // stack offset -72
		// 		int onBoatLastFrame; // $s7

			/* begin block 1.1.1 */
				// Start line: 1676
				// Start offset: 0x00048ACC
				// Variables:
			// 		int dist; // stack offset -48
			// 		int loop; // $s2
			// 		struct _CAR_DATA *cp; // $s1
			/* end block 1.1.1 */
			// End offset: 0x00048B98
			// End Line: 1699

			/* begin block 1.1.2 */
				// Start line: 1714
				// Start offset: 0x00048C40
				// Variables:
			// 		int d2; // $a2
			/* end block 1.1.2 */
			// End offset: 0x00048CB4
			// End Line: 1717

			/* begin block 1.1.3 */
				// Start line: 1724
				// Start offset: 0x00048CD8
			/* end block 1.1.3 */
			// End offset: 0x00048CFC
			// End Line: 1725

			/* begin block 1.1.4 */
				// Start line: 1729
				// Start offset: 0x00048D10
				// Variables:
			// 		struct XZPAIR speed; // stack offset -56

				/* begin block 1.1.4.1 */
					// Start line: 1733
					// Start offset: 0x00048D28
					// Variables:
				// 		int loop; // $s2
				// 		int mask; // $s1

					/* begin block 1.1.4.1.1 */
						// Start line: 1740
						// Start offset: 0x00048D60
						// Variables:
					// 		struct VECTOR *pos; // $a0
					// 		struct VECTOR *vel; // $a1
					/* end block 1.1.4.1.1 */
					// End offset: 0x00048E4C
					// End Line: 1775
				/* end block 1.1.4.1 */
				// End offset: 0x00048E64
				// End Line: 1776
			/* end block 1.1.4 */
			// End offset: 0x00048E64
			// End Line: 1777
		/* end block 1.1 */
		// End offset: 0x00048E64
		// End Line: 1778

		/* begin block 1.2 */
			// Start line: 1797
			// Start offset: 0x00048F44

			/* begin block 1.2.1 */
				// Start line: 1802
				// Start offset: 0x00048F54
				// Variables:
			// 		int sign; // $t0
			// 		unsigned short *target; // $a3
			/* end block 1.2.1 */
			// End offset: 0x00049070
			// End Line: 1820
		/* end block 1.2 */
		// End offset: 0x00049080
		// End Line: 1825

		/* begin block 1.3 */
			// Start line: 1862
			// Start offset: 0x0004914C
			// Variables:
		// 		int thisCamera; // $s1
		// 		int otherCamera; // $s2
		// 		int loop; // $s0
		// 		unsigned short *x; // $t0
		// 		unsigned short *z; // $a3

			/* begin block 1.3.1 */
				// Start line: 1889
				// Start offset: 0x00049240
				// Variables:
			// 		struct CELL_OBJECT *cop; // $a2
			/* end block 1.3.1 */
			// End offset: 0x000492C4
			// End Line: 1936
		/* end block 1.3 */
		// End offset: 0x0004930C
		// End Line: 1941
	/* end block 1 */
	// End offset: 0x00049364
	// End Line: 1951

	/* begin block 2 */
		// Start line: 4129
	/* end block 2 */
	// End Line: 4130

	/* begin block 3 */
		// Start line: 4139
	/* end block 3 */
	// End Line: 4140

	/* begin block 4 */
		// Start line: 4141
	/* end block 4 */
	// End Line: 4142

	/* begin block 5 */
		// Start line: 4143
	/* end block 5 */
	// End Line: 4144

/* WARNING: Unknown calling convention yet parameter storage is locked */

void StepEvents(void)
{
	UNIMPLEMENTED();

	if (detonator.timer != 0) 
	{
		DetonatorTimer();
	}

	/*
	bool bVar1;
	ushort uVar2;
	_EVENT *ev;
	uint uVar3;
	int i;
	int iVar4;
	ushort uVar5;
	int iVar6;
	int iVar7;
	uint uVar8;
	_PLAYER *pVec;
	FixedEvent *pFVar9;
	int *piVar10;
	CELL_OBJECT *pCVar11;
	int **ppiVar12;
	ushort *puVar13;
	ushort *puVar14;
	long *plVar15;
	_CAR_DATA *p_Var16;
	uint uVar17;
	int iVar18;
	int iVar19;
	uint unaff_s7;
	int local_48;
	int local_40;
	int aiStack48[2];

	uVar8 = carsOnBoat;
	ev = firstEvent;
	if (detonator.timer != 0) {
		DetonatorTimer();
		uVar8 = carsOnBoat;
		ev = firstEvent;
	}
	do {
		carsOnBoat = uVar8;
		if (ev == (_EVENT *)0x0) {
			VisibilityLists(VIS_SORT, 0);
			if (EventCop != (CELL_OBJECT *)0x0) {
				event_models_active = 0;
				i = 0;
				if (NumPlayers != 0) {
					do {
						uVar8 = 0x4000;
						if (i == 0) {
							uVar8 = 0x8000;
							uVar17 = 0x4000;
						}
						else {
							uVar17 = 0x8000;
						}
						VisibilityLists(VIS_NEXT, i);
						uVar2 = *xVis;
						i = i + 1;
						puVar14 = xVis;
						while (uVar3 = (uint)uVar2, (uVar3 & uVar8) == 0) {
							if ((uVar3 & uVar17) == 0) {
								if ((uVar2 & 0x80) == 0) {
									iVar4 = (uVar3 & 0x7f) * 0x28;
									pFVar9 = (FixedEvent *)event;
								}
								else {
									iVar4 = (uVar3 & 0x7f) * 0x2c;
									pFVar9 = fixedEvent;
								}
								plVar15 = (long *)((int)&(pFVar9->position).vx + iVar4);
								if ((plVar15[7] & 0x204U) == 0x200) {
									uVar2 = *zVis;
									puVar13 = zVis;
									while (uVar3 = (uint)uVar2, (uVar3 & uVar8) == 0) {
										if (((uVar3 & uVar17) == 0) && (((uint)*puVar14 & 0xfff) == (uVar3 & 0xfff))) {
											pCVar11 = EventCop + event_models_active;
											(pCVar11->pos).vx = *plVar15;
											(pCVar11->pos).vy = plVar15[1];
											(pCVar11->pos).vz = plVar15[2];
											pCVar11->yang = (uchar)(*(ushort *)(plVar15 + 4) >> 6);
											pCVar11->type = *(ushort *)(plVar15 + 8);
											if ((plVar15[7] & 0x12U) == 2) {
												pCVar11->pad = '\x01';
											}
											else {
												pCVar11->pad = '\0';
											}
											event_models_active = event_models_active + 1;
											*(ushort *)(plVar15 + 7) = *(ushort *)(plVar15 + 7) | 4;
										}
										puVar13 = puVar13 + 1;
										uVar2 = *puVar13;
									}
								}
							}
							puVar14 = puVar14 + 1;
							uVar2 = *puVar14;
						}
					} while (i < (int)(uint)NumPlayers);
				}
			}
			i = cameraDelay.delay + -1;
			if ((cameraDelay.delay != 0) && (cameraDelay.delay = i, i == 0)) {
				SpecialCamera((SpecialCamera)cameraDelay.type, 1);
			}
			return;
		}
		uVar2 = ev->flags;
		if ((uVar2 & 2) == 0) {
			uVar5 = uVar2 & 0xcc0;
			if (uVar5 == 0x40) {
				if (ev->timer != 0) {
					ppiVar12 = &ev->data;
					if (ev->timer == 1) {
						ppiVar12 = (int **)((int)&ev->data + 2);
					}
					uVar2 = *(ushort *)ppiVar12;
					iVar4 = (int)ev->rotation;
					uVar8 = (uint)*(ushort *)&ev->data;
					i = iVar4 - uVar8;
					if (i < 0) {
						i = uVar8 - iVar4;
					}
					uVar17 = (uint)*(ushort *)((int)&ev->data + 2);
					iVar6 = uVar17 - uVar8;
					iVar18 = uVar8 - uVar17;
					if (iVar6 < 0) {
						iVar6 = iVar18;
						if (iVar18 == 0) {
							trap(7);
						}
					}
					else {
						if (iVar6 == 0) {
							trap(7);
						}
					}
					uVar8 = (int)((uint)uVar2 - iVar4) >> 0x1f;
					i = (uint)(ushort)ev->rotation +
						(((uint)*(ushort *)&ev->node +
						((int)((int)rcossin_tbl[((i * 0x800) / iVar6 & 0xfffU) * 2] *
							((uint)*(ushort *)((int)&ev->node + 2) - (uint)*(ushort *)&ev->node)) >> 0xc)
							^ uVar8) - uVar8);
					ev->rotation = (short)i;
					if ((int)((uint)uVar2 - iVar4 ^ (uint)*(ushort *)ppiVar12 - (i * 0x10000 >> 0x10)) < 0) {
						ev->rotation = *(ushort *)ppiVar12;
						bVar1 = gCurrentMissionNumber != 0x1e;
						ev->timer = 0;
						if (bVar1) {
							SetMSoundVar(3, (VECTOR *)0x0);
						}
						if (ev == events.cameraEvent) {
							SpecialCamera(SPECIAL_CAMERA_RESET, 0);
						}
					}
				}
			}
			else {
				if (uVar5 < 0x41) {
					if ((uVar2 & 0xcc0) == 0) {
						i = GetBridgeRotation((int)ev->timer);
						ev->rotation = (short)i;
						if ((ev->model & 1U) != 0) {
							ev->rotation = -(short)i;
						}
						if (((ev->flags & 0x100U) == 0) || (ev->timer < 0x3e9)) {
							i = (int)ev->timer + 1;
							ev->timer = (short)i + (short)(i / 8000) * -8000;
						}
					}
				}
				else {
					if (uVar5 == 0xc0) {
						StepHelicopter(ev);
					}
					else {
						if (uVar5 == 0x440) {
							if ((CameraCnt & 0x1fU) == 0) {
								i = (uint)(ushort)FixedEvent_0009e964.active - 2;
								if ((FixedEvent_0009e964.active & 1U) == 0) {
									i = (uint)(ushort)FixedEvent_0009e964.active + 2;
									FixedEvent_0009e964.active = (short)i;
									if (i * 0x10000 >> 0x10 == 0x1e) {
										FixedEvent_0009e964.active = 0x1f;
									}
								}
								else {
									FixedEvent_0009e964.active = (short)i;
									if (i * 0x10000 >> 0x10 == -1) {
										FixedEvent_0009e964.active = 0;
									}
								}
							}
							FixedEvent_0009e964.rotation =
								FixedEvent_0009e964.rotation - FixedEvent_0009e964.active & 0xfff;
						}
					}
				}
			}
		}
		else {
			if ((uVar2 & 0x40) != 0) {
				uVar17 = 0;
				p_Var16 = car_data;
				carsOnBoat = 0;
				do {
					if (p_Var16->controlType != '\0') {
						i = OnBoat((VECTOR *)(p_Var16->hd).where.t, ev, aiStack48);
						if (i != 0) {
							carsOnBoat = carsOnBoat | 1 << (uVar17 & 0x1f);
						}
					}
					uVar17 = uVar17 + 1;
					p_Var16 = p_Var16 + 1;
				} while ((int)uVar17 < 0x14);
				if ((player.playerType == '\x02') && (i = OnBoat((VECTOR *)&player, ev, aiStack48), i != 0)) {
					carsOnBoat = carsOnBoat | 0x300000;
				}
				BoatOffset(&boatOffset, ev);
				local_48 = (ev->position).vx;
				local_40 = (ev->position).vz;
				unaff_s7 = uVar8;
			}
			if ((ev->flags & 0x10U) == 0) {
				StepPathEvent(ev);
			}
			else {
				StepFromToEvent(ev);
			}
			uVar8 = foam.rotate;
			if ((ev->flags & 0x800U) != 0) {
				uVar8 = CameraCnt & 0xff;
				ev->data[1] = (int)((uint)(ushort)rcossin_tbl[(CameraCnt & 0x7fU) * 0x40] << 0x10) >> 0x19 &
					0xfff;
				ev->data[2] = (int)rcossin_tbl[uVar8 * 0x20 + 1] + 0x1000 >> 7;
				i = detonator.timer * detonator.timer;
				if (detonator.timer - 1U < 0x9f) {
					ev->data[1] = ev->data[1] - (rcossin_tbl[(detonator.timer & 0x3fU) * 0x80] * i >> 0x12);
					ev->data[2] = ev->data[2] - (rcossin_tbl[(detonator.timer & 0x3fU) * 0x80] * i >> 0x10);
				}
				uVar8 = foam.rotate + -1;
				if ((foam.rotate & 0xffff7fffU) == 0) {
					uVar8 = Random2(0);
					uVar8 = foam.rotate ^ (((int)(uVar8 & 0xf00) >> 8) + 8U | 0x8000);
				}
			}
			foam.rotate = uVar8;
			if (((ev->flags & 0x40U) != 0) && ((i = 0, carsOnBoat != 0 || (unaff_s7 != 0)))) {
				uVar8 = 1;
				iVar19 = 0xd1358;
				iVar6 = (ev->position).vx - local_48;
				iVar18 = 0;
				iVar4 = (ev->position).vz - local_40;
				do {
					pVec = (_PLAYER *)((int)car_data[0].hd.where.t + iVar18);
					if (i == 0x14) {
						pVec = &player;
						piVar10 = (int *)0x0;
					}
					else {
						piVar10 = (int *)(iVar19 + 0x1c);
					}
					if ((carsOnBoat & uVar8) == 0) {
						if ((piVar10 != (int *)0x0) && ((unaff_s7 & uVar8) != 0)) {
							*piVar10 = *piVar10 + iVar6 * 0x1000;
							iVar7 = piVar10[2] + iVar4 * 0x1000;
						LAB_00048e48:
							piVar10[2] = iVar7;
						}
					}
					else {
						pVec->pos[0] = pVec->pos[0] + iVar6;
						*(int *)pVec->pos = *(int *)pVec->pos + iVar4;
						if (i == 0x14) {
							SetTannerPosition((VECTOR *)pVec);
							carsOnBoat = carsOnBoat & 0xffefffff;
						}
						else {
							if ((unaff_s7 & uVar8) == 0) {
								*piVar10 = *piVar10 + iVar6 * -0x1000;
								iVar7 = piVar10[2] + iVar4 * -0x1000;
								goto LAB_00048e48;
							}
						}
					}
					iVar19 = iVar19 + 0x29c;
					iVar18 = iVar18 + 0x29c;
					i = i + 1;
					uVar8 = uVar8 << 1;
				} while (i < 0x15);
			}
		}
		uVar8 = carsOnBoat;
		ev = ev->next;
	} while (true);
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawFerrisWheel(struct MATRIX *matrix /*$s0*/, struct VECTOR *pos /*$s1*/)
 // line 2110, offset 0x00049364
	/* begin block 1 */
		// Start line: 2111
		// Start offset: 0x00049364

		/* begin block 1.1 */
			// Start line: 2126
			// Start offset: 0x00049460
			// Variables:
		// 		int loop; // $s3
		// 		struct MODEL *model; // $s2
		// 		struct VECTOR spoke[2]; // stack offset -104

			/* begin block 1.1.1 */
				// Start line: 2138
				// Start offset: 0x000494E4
				// Variables:
			// 		struct VECTOR offset; // stack offset -72
			// 		struct VECTOR carPos; // stack offset -56
			// 		int rotation; // $v0
			/* end block 1.1.1 */
			// End offset: 0x000494E4
			// End Line: 2142
		/* end block 1.1 */
		// End offset: 0x00049658
		// End Line: 2155
	/* end block 1 */
	// End offset: 0x00049684
	// End Line: 2157

	/* begin block 2 */
		// Start line: 5081
	/* end block 2 */
	// End Line: 5082

	/* begin block 3 */
		// Start line: 5241
	/* end block 3 */
	// End Line: 5242

void DrawFerrisWheel(MATRIX *matrix, VECTOR *pos)
{
	UNIMPLEMENTED();

	/*
	short sVar1;
	short sVar2;
	uint uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	MODEL* model;
	int iVar8;
	int iVar9;
	VECTOR spoke[2];
	VECTOR offset;
	VECTOR carPos;

	if (chicagoDoor[2].model != -1)
	{
		RenderModel(modelpointers[chicagoDoor[2].model], matrix, pos, 0, 4);

		if (chicagoDoor[2].model != -1)
		{
			RenderModel(modelpointers[chicagoDoor[2]._20_4_], (MATRIX*)0x0, (VECTOR*)0x0, 0, 0);
		}


		matrix->m[0][0] = -matrix->m[0][0];
		matrix->m[1][0] = -matrix->m[1][0];;
		matrix->m[2][0] = -matrix->m[2][0];
		RenderModel(modelpointers[chicagoDoor[2].model], matrix, pos, 0, 4);

		if (chicagoDoor[2]._24_4_ != -1) 
		{
			iVar9 = 0;

			spoke[0].vx = VECTOR_000109b0.vx;
			spoke[0].vy = VECTOR_000109b0.vy;
			spoke[0].vz = VECTOR_000109b0.vz;
			spoke[0].pad = VECTOR_000109b0.pad;
			spoke[1].vx = VECTOR_000109c0.vx;
			spoke[1].vy = VECTOR_000109c0.vy;
			spoke[1].vz = VECTOR_000109c0.vz;
			spoke[1].pad = VECTOR_000109c0.pad;
			model = modelpointers[chicagoDoor[2]._24_4_];
			iVar8 = 4;

			SetRotMatrix(&inv_camera_matrix);
			_MatrixRotate(spoke);
			_MatrixRotate(spoke + 1);

			do {
				uVar3 = chicagoDoor[2].rotation + iVar9 & 0xfff;
				iVar7 = (int)rcossin_tbl[uVar3 * 2];
				iVar4 = (int)rcossin_tbl[uVar3 * 2 + 1];
				iVar6 = spoke[0].vx * iVar7 + spoke[1].vx * iVar4 + 0x800 >> 0xc;
				iVar5 = spoke[0].vy * iVar7 + spoke[1].vy * iVar4 + 0x800 >> 0xc;
				iVar4 = spoke[0].vz * iVar7 + spoke[1].vz * iVar4 + 0x800 >> 0xc;
				setCopControlWord(2, 0x2800, pos->vx + iVar6);
				setCopControlWord(2, 0x3000, pos->vy + iVar5);
				setCopControlWord(2, 0x3800, pos->vz + iVar4);
				RenderModel(model, (MATRIX*)0x0, (VECTOR*)0x0, 0, 0);
				setCopControlWord(2, 0x2800, pos->vx - iVar6);
				setCopControlWord(2, 0x3000, pos->vy - iVar5);
				setCopControlWord(2, 0x3800, pos->vz - iVar4);
				RenderModel(model, (MATRIX*)0x0, (VECTOR*)0x0, 0, 0);
				iVar8 = iVar8 + -1;
				iVar9 = iVar9 + 0x19a;
			} while (-1 < iVar8);
		}
	}*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawRotor(struct VECTOR pos /*stack 0*/, struct MATRIX *matrix /*stack 16*/)
 // line 2159, offset 0x00049684
	/* begin block 1 */
		// Start line: 2160
		// Start offset: 0x00049684
		// Variables:
	// 		struct SVECTOR v[5]; // stack offset -120
	// 		struct MATRIX local; // stack offset -80
	// 		struct POLY_FT4 *poly; // $t0
	// 		struct TEXTURE_DETAILS *tex; // $t3
	// 		int z; // stack offset -48
	// 		char *firstPoly; // $a1
	/* end block 1 */
	// End offset: 0x00049C38
	// End Line: 2238

	/* begin block 2 */
		// Start line: 5381
	/* end block 2 */
	// End Line: 5382

	/* begin block 3 */
		// Start line: 5384
	/* end block 3 */
	// End Line: 5385

	/* begin block 4 */
		// Start line: 5385
	/* end block 4 */
	// End Line: 5386

/* WARNING: Removing unreachable block (ram,0x000496dc) */
/* WARNING: Removing unreachable block (ram,0x00049704) */
/* WARNING: Removing unreachable block (ram,0x00049750) */
/* WARNING: Could not reconcile some variable overlaps */

void DrawRotor(VECTOR pos, MATRIX *matrix)
{
	UNIMPLEMENTED();
	/*
	DB *pDVar1;
	undefined4 in_zero;
	undefined4 in_at;
	ushort uVar2;
	int iVar3;
	uint *puVar4;
	uint uVar5;
	int iVar6;
	int in_a1;
	uint uVar7;
	int iVar8;
	uint uVar9;
	int in_a2;
	uint uVar10;
	short sVar11;
	uint uVar12;
	uint *puVar13;
	uint *puVar14;
	uint *puVar15;
	uint *puVar16;
	uint *puVar17;
	uint local_78;
	uint local_74;
	undefined4 local_70;
	uint local_6c[4];
	undefined2 uStack90;
	undefined4 local_5c;
	MATRIX local_50;

	puVar14 = &local_78;
	puVar17 = &DAT_000109d0;
	do {
		puVar15 = puVar17;
		puVar13 = puVar14;
		uVar7 = puVar15[1];
		uVar5 = puVar15[2];
		uVar12 = puVar15[3];
		*puVar13 = *puVar15;
		puVar13[1] = uVar7;
		puVar13[2] = uVar5;
		puVar13[3] = uVar12;
		puVar14 = puVar13 + 4;
		puVar17 = puVar15 + 4;
	} while (puVar15 + 4 != (uint *)0x109f0);
	uVar7 = puVar15[5];
	puVar13[4] = uRam000109f0;
	puVar13[5] = uVar7;
	local_50.m[0][0] = 0x1000;
	local_50.m[1][0] = 0;
	local_50.m[2][0] = 0;
	local_50.m[0][1] = 0;
	local_50.m[1][1] = 0x1000;
	local_50.m[2][1] = 0;
	local_50.m[0][2] = 0;
	local_50.m[1][2] = 0;
	local_50.m[2][2] = 0x1000;
	matrix = (MATRIX *)((int)matrix - camera_position.vx);
	uVar7 = in_a1 - camera_position.vy;
	uVar5 = in_a2 - camera_position.vz;
	_RotMatrixY(&local_50, HelicopterData.rotorrot & 0xfff);
	ApplyMatrixSV(pos.vx, &local_78, &local_78);
	MulMatrix0(pos.vx, &local_50, &local_50);
	ApplyMatrixSV(&local_50, &local_70, &local_70);
	ApplyMatrixSV(&local_50, local_6c + 1, local_6c + 1);
	uVar12 = (local_78 & 0xffff) + ((uint)matrix & 0xffff);
	uVar10 = (local_74 & 0xffff) + (uVar5 & 0xffff);
	uVar5 = (local_6c[1] & 0xffff) + uVar12;
	iVar8 = (local_78 >> 0x10) + (uVar7 & 0xffff);
	local_70._2_2_ = local_70._2_2_ + (short)iVar8;
	iVar6 = uVar12 - uVar5;
	sVar11 = (short)uVar12;
	local_74 = local_74 & 0xffff0000 | uVar10 & 0xffff;
	uVar7 = (local_6c[2] & 0xffff) + uVar10;
	local_6c[2] = local_6c[2] & 0xffff0000 | uVar7 & 0xffff;
	local_70 = CONCAT22(local_70._2_2_, (short)local_70 + sVar11);
	uVar2 = (short)local_6c[0] + (short)uVar10;
	local_6c[0] = local_6c[0] & 0xffff0000 | (uint)uVar2;
	local_5c = CONCAT22(uStack90, (short)uVar10 * 2 - (short)uVar7);
	iVar3 = (local_6c[1] >> 0x10) + iVar8;
	local_6c[1] = uVar5 & 0xffff | iVar3 * 0x10000;
	iVar3 = iVar8 * 2 - iVar3;
	local_6c[3] = CONCAT22((short)iVar3, sVar11 + (short)iVar6);
	setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
	setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
	setCopControlWord(2, 0x2800, dummy.vx);
	setCopControlWord(2, 0x3000, dummy.vy);
	setCopControlWord(2, 0x3800, dummy.vz);
	setCopReg(2, in_zero, uVar12 & 0xffff | iVar8 * 0x10000);
	setCopReg(2, in_at, local_74);
	setCopReg(2, 0xa0000, local_70);
	setCopReg(2, 0xa187c, local_6c[0]);
	setCopReg(2, iVar6, local_6c[1]);
	setCopReg(2, iVar3, local_6c[2]);
	copFunction(2, 0x280030);
	uVar5 = (uint)HelicopterData.rotorTexture.coords._0_2_;
	uVar9 = (uint)HelicopterData.rotorTexture.coords._6_2_;
	puVar14 = (uint *)current->primptr;
	puVar14[3] = CONCAT22(HelicopterData.rotorTexture.clutid, HelicopterData.rotorTexture.coords._0_2_)
		;
	uVar12 = (uint)HelicopterData.rotorTexture.coords._2_2_;
	uVar7 = (uint)HelicopterData.rotorTexture.tpageid;
	puVar14[7] = ((uVar5 & 0xfefe) >> 1) + ((uVar9 & 0xfefe) >> 1);
	puVar14[5] = uVar12 | (uVar7 | 0x40) << 0x10;
	uVar7 = (uint)HelicopterData.rotorTexture.coords._6_2_;
	*(char *)((int)puVar14 + 3) = '\t';
	*(char *)((int)puVar14 + 7) = '.';
	*(char *)(puVar14 + 1) = '\x7f';
	*(char *)((int)puVar14 + 5) = '\x7f';
	*(char *)((int)puVar14 + 6) = '\x7f';
	puVar14[9] = uVar7;
	copFunction(2, 0x158002d);
	uVar7 = getCopReg(2, 0xc);
	puVar14[6] = uVar7;
	uVar7 = getCopReg(2, 0xd);
	puVar14[4] = uVar7;
	uVar7 = getCopReg(2, 0xe);
	puVar14[2] = uVar7;
	pDVar1 = current;
	iVar3 = getCopReg(2, 0x13);
	iVar3 = iVar3 + 1000 >> 3;
	setCopReg(2, in_zero, local_6c[3]);
	setCopReg(2, in_at, local_5c);
	copFunction(2, 0x180001);
	*puVar14 = *puVar14 & 0xff000000 | current->ot[iVar3] & 0xffffff;
	pDVar1->ot[iVar3] = pDVar1->ot[iVar3] & 0xff000000 | (uint)puVar14 & 0xffffff;
	puVar13 = (uint *)pDVar1->primptr;
	*(uint **)&pDVar1->primptr = puVar13 + 10;
	uVar7 = getCopReg(2, 0xe);
	puVar14[8] = uVar7;
	local_74._0_2_ = (short)(uVar10 & 0xffff);
	puVar15 = (uint *)current->primptr;
	local_5c = CONCAT22(uStack90, (short)local_74 * 2 - uVar2);
	local_6c[3] = CONCAT22((short)iVar8 * 2 - local_70._2_2_, sVar11 * 2 - ((short)local_70 + sVar11));
	puVar14 = puVar15;
	puVar17 = puVar13;
	do {
		puVar16 = puVar17;
		puVar4 = puVar14;
		uVar7 = puVar16[1];
		uVar5 = puVar16[2];
		uVar12 = puVar16[3];
		*puVar4 = *puVar16;
		puVar4[1] = uVar7;
		puVar4[2] = uVar5;
		puVar4[3] = uVar12;
		puVar17 = puVar16 + 4;
		puVar14 = puVar4 + 4;
	} while (puVar17 != puVar13 + 8);
	uVar7 = puVar16[5];
	puVar4[4] = *puVar17;
	puVar4[5] = uVar7;
	setCopReg(2, in_zero, local_6c[3]);
	setCopReg(2, in_at, local_5c);
	copFunction(2, 0x180001);
	*(undefined2 *)(puVar15 + 5) = HelicopterData.rotorTexture.coords._4_2_;
	pDVar1 = current;
	*puVar15 = *puVar15 & 0xff000000 | current->ot[iVar3] & 0xffffff;
	pDVar1->ot[iVar3] = pDVar1->ot[iVar3] & 0xff000000 | (uint)puVar15 & 0xffffff;
	pDVar1->primptr = pDVar1->primptr + 0x28;
	uVar7 = getCopReg(2, 0xe);
	puVar15[4] = uVar7;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawEvents(int camera /*stack 0*/)
 // line 2240, offset 0x00049c38
	/* begin block 1 */
		// Start line: 2241
		// Start offset: 0x00049C38
		// Variables:
	// 		unsigned short *x; // $a1
	// 		unsigned short *z; // $a0
	// 		int thisCamera; // stack offset -56
	// 		int otherCamera; // stack offset -52
	// 		static struct _EVENT *nearestTrain; // offset 0x28
	// 		static int distanceFromNearestTrain; // offset 0x2c

		/* begin block 1.1 */
			// Start line: 2276
			// Start offset: 0x00049D14
			// Variables:
		// 		struct _EVENT *ev; // $s1

			/* begin block 1.1.1 */
				// Start line: 2289
				// Start offset: 0x00049E0C
				// Variables:
			// 		unsigned int dist; // $v1
			/* end block 1.1.1 */
			// End offset: 0x00049E74
			// End Line: 2298

			/* begin block 1.1.2 */
				// Start line: 2314
				// Start offset: 0x00049EA4

				/* begin block 1.1.2.1 */
					// Start line: 2316
					// Start offset: 0x00049ED4
					// Variables:
				// 		struct MATRIX matrix; // stack offset -208
				// 		struct MATRIX ext; // stack offset -176
				// 		struct VECTOR pos; // stack offset -144
				// 		int reflection; // $s5
				// 		int temp; // stack offset -48

					/* begin block 1.1.2.1.1 */
						// Start line: 2329
						// Start offset: 0x00049F48
					/* end block 1.1.2.1.1 */
					// End offset: 0x00049F48
					// End Line: 2329

					/* begin block 1.1.2.1.2 */
						// Start line: 2335
						// Start offset: 0x00049FB4

						/* begin block 1.1.2.1.2.1 */
							// Start line: 2346
							// Start offset: 0x0004A038
							// Variables:
						// 		struct VECTOR shadow[4]; // stack offset -128
						// 		int loop; // $t0

							/* begin block 1.1.2.1.2.1.1 */
								// Start line: 2351
								// Start offset: 0x0004A05C
								// Variables:
							// 		struct XZPAIR offset; // stack offset -64
							// 		int rotate; // $a1
							/* end block 1.1.2.1.2.1.1 */
							// End offset: 0x0004A0E8
							// End Line: 2358
						/* end block 1.1.2.1.2.1 */
						// End offset: 0x0004A118
						// End Line: 2361

						/* begin block 1.1.2.1.2.2 */
							// Start line: 2373
							// Start offset: 0x0004A17C
						/* end block 1.1.2.1.2.2 */
						// End offset: 0x0004A1B8
						// End Line: 2382
					/* end block 1.1.2.1.2 */
					// End offset: 0x0004A1B8
					// End Line: 2383

					/* begin block 1.1.2.1.3 */
						// Start line: 2393
						// Start offset: 0x0004A218
					/* end block 1.1.2.1.3 */
					// End offset: 0x0004A218
					// End Line: 2393

					/* begin block 1.1.2.1.4 */
						// Start line: 2412
						// Start offset: 0x0004A304
						// Variables:
					// 		int i; // $a0
					/* end block 1.1.2.1.4 */
					// End offset: 0x0004A354
					// End Line: 2419

					/* begin block 1.1.2.1.5 */
						// Start line: 2424
						// Start offset: 0x0004A368
					/* end block 1.1.2.1.5 */
					// End offset: 0x0004A3E0
					// End Line: 2441
				/* end block 1.1.2.1 */
				// End offset: 0x0004A540
				// End Line: 2485
			/* end block 1.1.2 */
			// End offset: 0x0004A540
			// End Line: 2485
		/* end block 1.1 */
		// End offset: 0x0004A588
		// End Line: 2495

		/* begin block 1.2 */
			// Start line: 2510
			// Start offset: 0x0004A628
		/* end block 1.2 */
		// End offset: 0x0004A628
		// End Line: 2510
	/* end block 1 */
	// End offset: 0x0004A658
	// End Line: 2516

	/* begin block 2 */
		// Start line: 5634
	/* end block 2 */
	// End Line: 5635

	/* begin block 3 */
		// Start line: 5637
	/* end block 3 */
	// End Line: 5638

	/* begin block 4 */
		// Start line: 5644
	/* end block 4 */
	// End Line: 5645

void DrawEvents(int camera)
{
	UNIMPLEMENTED();
	/*
	bool bVar1;
	uint uVar2;
	ushort uVar3;
	uint uVar4;
	int local_d8;
	short *psVar5;
	FixedEvent *pFVar6;
	ushort *puVar7;
	int iVar8;
	int iVar9;
	ushort *puVar10;
	int *piVar11;
	VECTOR *pVVar12;
	_EVENT *ev;
	undefined4 in_stack_ffffff2c;
	short local_d0;
	short local_ce;
	short local_cc;
	short local_ca;
	short local_c8;
	short local_c6;
	short local_c4;
	short local_c2;
	short local_c0;
	VECTOR local_90;
	VECTOR local_80[4];
	int local_40;
	int local_3c;
	uint local_38;
	uint local_34;
	int local_30;

	if (CurrentPlayerView == 0) {
		nearestTrain_70 = (_EVENT *)0x0;
		local_38 = 0x8000;
		local_34 = 0x4000;
	}
	else {
		local_38 = 0x4000;
		local_34 = 0x8000;
	}
	if (camera == 0) {
		SetFrustrumMatrix();
	}
	else {
		if (cameraEventsActive == 0) {
			return;
		}
		InitEventCamera();
	}
	VisibilityLists(VIS_NEXT, CurrentPlayerView);
	uVar4 = (uint)*xVis;
	uVar2 = uVar4 & local_38;
	puVar10 = xVis;
	do {
		if (uVar2 != 0) {
			if (camera == 0) {
				if (eventHaze != 0) {
					add_haze(eventHaze, eventHaze, 7);
				}
			}
			else {
				ResetEventCamera();
			}
			if (((camera == 0) && (CurrentPlayerView == (uint)NumPlayers - 1)) &&
				(local_d8 = (int)es_mobile, local_d8 != -1)) {
				if (nearestTrain_70 == (_EVENT *)0x0) {
					SetEnvSndVol(local_d8, -10000);
				}
				else {
					SetEnvSndVol(local_d8, 2000);
					SetEnvSndPos((int)es_mobile, (nearestTrain_70->position).vx, (nearestTrain_70->position).vz)
						;
				}
			}
			return;
		}
		if ((uVar4 & local_34) == 0) {
			if ((uVar4 & 0x80) == 0) {
				local_d8 = (uVar4 & 0x7f) * 0x28;
				pFVar6 = (FixedEvent *)event;
			}
			else {
				local_d8 = (uVar4 & 0x7f) * 0x2c;
				pFVar6 = fixedEvent;
			}
			ev = (_EVENT *)((int)&(pFVar6->position).vx + local_d8);
			uVar3 = ev->flags;
			if ((uVar3 & 4) == 0) {
				if (camera == 0) {
					if ((uVar3 & 1) != 1) {
					LAB_00049d90:
						uVar4 = (uint)*zVis;
						puVar7 = zVis;
						if ((uVar4 & local_38) == 0) {
						LAB_00049db4:
							if (((uVar4 & local_34) != 0) || (((uint)*puVar10 & 0xfff) != (uVar4 & 0xfff))) break;
							ev->flags = uVar3 | 4;
							if (camera == 0) {
								if ((es_mobile != -1) && ((uVar3 & 2) != 0)) {
									local_d8 = (ev->position).vx;
									iVar9 = local_d8 - camera_position.vx;
									if (iVar9 < 0) {
										iVar9 = camera_position.vx - local_d8;
									}
									iVar8 = (ev->position).vz;
									local_d8 = iVar8 - camera_position.vz;
									if (local_d8 < 0) {
										local_d8 = camera_position.vz - iVar8;
									}
									if ((nearestTrain_70 == (_EVENT *)0x0) ||
										((uint)(iVar9 + local_d8) < distanceFromNearestTrain_71)) {
										nearestTrain_70 = ev;
										distanceFromNearestTrain_71 = iVar9 + local_d8;
									}
								}
								local_d8 = FrustrumCheck(ev, (int)modelpointers1536[ev->model]->bounding_sphere);
								if (local_d8 != -1) {
									local_90.vx = (ev->position).vx - camera_position.vx;
									local_90.vy = (ev->position).vy - camera_position.vy;
									local_d0 = 0x1000;
									local_ca = 0;
									local_c4 = 0;
									local_ce = 0;
									local_c8 = 0x1000;
									local_c2 = 0;
									local_cc = 0;
									local_c6 = 0;
									local_c0 = 0x1000;
									local_90.vz = (ev->position).vz - camera_position.vz;
									bVar1 = false;
									if ((ev->flags & 2U) == 0) {
										uVar3 = ev->flags & 0xcc0;
										if (uVar3 == 0x400) goto LAB_0004a118;
										if (uVar3 < 0x401) {
											if (uVar3 == 0x80) {
												_RotMatrixY((MATRIX *)&stack0xffffff30, ev->rotation);
												local_90.vx = local_90.vx - boatOffset.vx;
												local_90.vz = local_90.vz - boatOffset.vz;
												local_90.vy = (local_90.vy - boatOffset.vy) +
													((int)ev->node * (int)rcossin_tbl[(*ev->data & 0xfffU) * 2] +
														0x800 >> 0xc);
											}
											else {
												if (uVar3 != 0xc0) {
												LAB_0004a140:
													uVar3 = ev->flags & 0x30;
													if (uVar3 == 0x10) {
														_RotMatrixY((MATRIX *)&stack0xffffff30, ev->rotation);
													}
													else {
														if (uVar3 < 0x11) {
															if ((ev->flags & 0x30U) == 0) {
																_RotMatrixX((MATRIX *)&stack0xffffff30, ev->rotation);
															}
														}
														else {
															if (uVar3 == 0x20) {
																_RotMatrixZ((MATRIX *)&stack0xffffff30, ev->rotation);
															}
														}
													}
												}
											}
										}
										else {
											if (uVar3 == 0x440) {
												_RotMatrixX((MATRIX *)&stack0xffffff30, ev->rotation);
											}
											else {
												uVar4 = 0;
												if (uVar3 != 0x480) goto LAB_0004a140;
												local_d8 = 0;
												piVar11 = &local_80[0].vz;
												pVVar12 = local_80;
												do {
													if ((uVar4 & 1) == 0) {
														local_40 = -0xc9;
													}
													else {
														local_40 = 0xc9;
													}
													if ((uVar4 & 2) == 0) {
														local_3c = -0x4ed;
													}
													else {
														local_3c = 0x4ed;
													}
													uVar2 = (int)ev->rotation + 0x200U & 0x400;
													iVar9 = local_40;
													if (uVar2 != 0) {
														iVar9 = local_3c;
													}
													pVVar12->vx = (ev->position).vx + iVar9;
													iVar9 = local_3c;
													if (uVar2 != 0) {
														iVar9 = local_40;
													}
													*piVar11 = (ev->position).vz + iVar9;
													*(undefined4 *)((int)&local_80[0].vy + local_d8) = 0;
													piVar11 = piVar11 + 4;
													pVVar12 = pVVar12 + 1;
													uVar4 = uVar4 + 1;
													local_d8 = local_d8 + 0x10;
												} while ((int)uVar4 < 4);
												PlaceShadowForCar(local_80, 0xc, (VECTOR *)0x0, 0);
											LAB_0004a118:
												_RotMatrixY((MATRIX *)&stack0xffffff30, ev->rotation);
											}
										}
									}
									else {
										_RotMatrixY((MATRIX *)&stack0xffffff30, ev->rotation);
									}
									setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
									setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
									setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
									setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
									setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
									_MatrixRotate(&local_90);
									if ((ev->flags & 0xcc0U) == 0xc0) {
										psVar5 = (short *)&stack0xffffff30;
										if (ev->model == HelicopterData.cleanModel) {
											_RotMatrixZ((MATRIX *)&stack0xffffff30, HelicopterData.roll & 0xfff);
											_RotMatrixX((MATRIX *)&stack0xffffff30, HelicopterData.pitch & 0xfff);
											_RotMatrixY((MATRIX *)&stack0xffffff30, ev->rotation & 0xfff);
											DrawRotor((VECTOR)CONCAT214(local_ca, CONCAT212(local_cc, CONCAT210(local_ce,
												CONCAT28(local_d0, CONCAT44(in_stack_ffffff2c,
												(MATRIX *)
													&stack0xffffff30))))),
													(MATRIX *)(ev->position).vx);
											RenderModel(modelpointers1536[ev->model], (MATRIX *)&stack0xffffff30, &local_90,
												0, 0);
											local_90.vx = (ev->position).vx - camera_position.vx;
											local_90.vy = -camera_position.vy - (ev->position).vy;
											local_90.vz = (ev->position).vz - camera_position.vz;
											setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
											setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
											setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
											setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
											setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
											_MatrixRotate(&local_90);
											bVar1 = true;
										}
										else {
											local_d8 = 2;
											do {
												local_d8 = local_d8 + -1;
												*psVar5 = *psVar5 << 1;
												psVar5 = psVar5 + 4;
											} while (-1 < local_d8);
											_RotMatrixY((MATRIX *)&stack0xffffff30, 0xafd);
											RenderModel(modelpointers1536[ev->model], (MATRIX *)&stack0xffffff30, &local_90,
												0, 0);
										}
									}
									if ((ev->flags & 0x800U) != 0) {
										_RotMatrixX((MATRIX *)&stack0xffffff30, (short)ev->data[1]);
										local_d8 = gTimeOfDay;
										local_90.vy = local_90.vy - ev->data[2];
										local_30 = combointensity;
										if ((ev->flags & 0x20U) == 0) {
											ev->flags = ev->flags | 1;
											if (local_d8 != 3) {
												bVar1 = true;
											}
										}
										else {
											SetupPlaneColours(0x80a0c);
										}
									}
									if (bVar1) {
										local_c8 = -local_c8;
										local_c6 = -local_c6;
										SetupPlaneColours((ulong)&DAT_00464a40);
										RenderModel(modelpointers1536[ev->model], (MATRIX *)&stack0xffffff30, &local_90,
											400, 2);
									}
									else {
										if ((ev->flags & 0xcc0U) == 0x440) {
											DrawFerrisWheel((MATRIX *)&stack0xffffff30, &local_90);
										}
										else {
											RenderModel(modelpointers1536[ev->model], (MATRIX *)&stack0xffffff30, &local_90,
												0, 0);
										}
									}
									if ((ev->flags & 0x800U) != 0) {
										combointensity = local_30;
										local_c8 = 0x1000;
										local_c6 = 0;
										local_c4 = 0x1000;
										local_c2 = 0;
										local_c0 = 0;
										local_90.vy = local_90.vy + ev->data[2];
										if (gTimeOfDay != 1) {
											SetupPlaneColours((ulong)&DAT_00282828);
										}
										if ((foam.rotate & 0x8000U) == 0) {
											local_d8 = 1;
										}
										else {
											local_d8 = 3;
										}
										RenderModel(foam.model, (MATRIX *)&stack0xffffff30, &local_90, 200, local_d8);
										SetupPlaneColours(combointensity);
									}
								}
							}
							else {
								SetCamera(ev);
								DrawMapPSX((int *)&ObjectDrawnValue);
							}
						}
					}
				}
				else {
					if ((uVar3 & 1) != 0) goto LAB_00049d90;
				}
			}
		}
	LAB_0004a58c:
		puVar10 = puVar10 + 1;
		uVar4 = (uint)*puVar10;
		uVar2 = uVar4 & local_38;
	} while (true);
	uVar4 = (uint)puVar7[1];
	puVar7 = puVar7 + 1;
	if ((uVar4 & local_38) != 0) goto LAB_0004a58c;
	goto LAB_00049db4;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ BoatOffset(SVECTOR *offset /*$a0*/, _EVENT *ev /*$a1*/)
 // line 2520, offset 0x0004be24
	/* begin block 1 */
		// Start line: 10327
	/* end block 1 */
	// End Line: 10328

	/* begin block 2 */
		// Start line: 5040
	/* end block 2 */
	// End Line: 5041

	/* begin block 3 */
		// Start line: 10328
	/* end block 3 */
	// End Line: 10329

// [D]
void BoatOffset(SVECTOR *offset, _EVENT *ev)
{
	offset->vx = 0;
	offset->vy = -*(short *)(ev->data + 2);
	offset->vz = *(short *)(ev->data + 4) - *(short *)&(ev->position).vz;
	return;
}



// decompiled code
// original method signature: 
// int /*$ra*/ OnBoat(struct VECTOR *pos /*$t1*/, struct _EVENT *ev /*$a1*/, int *dist /*$a2*/)
 // line 2527, offset 0x0004bda0
	/* begin block 1 */
		// Start line: 2528
		// Start offset: 0x0004BDA0
		// Variables:
	// 		int halfBoatWidth; // $t0
	// 		int halfBoatLength; // $a0
	/* end block 1 */
	// End offset: 0x0004BE24
	// End Line: 2558

	/* begin block 2 */
		// Start line: 10304
	/* end block 2 */
	// End Line: 10305

	/* begin block 3 */
		// Start line: 5054
	/* end block 3 */
	// End Line: 5055

	/* begin block 4 */
		// Start line: 10308
	/* end block 4 */
	// End Line: 10309

// [D]
int OnBoat(VECTOR *pos, _EVENT *ev, int *dist)
{
	int iVar1;
	int iVar2;
	int iVar3;

	if (GameLevel == 1) {
		iVar3 = 0x355;
		iVar2 = 0x97f;
	}
	else {
		iVar3 = 0x640;
		iVar2 = 0x1500;
	}
	iVar1 = (ev->position).vx;
	if (iVar1 - iVar3 < pos->vx) {
		if (iVar1 + iVar3 <= pos->vx) {
			return 0;
		}
		iVar3 = pos->vz - (ev->position).vz;
		*dist = iVar3;
		if ((-iVar2 < iVar3) && (iVar3 < iVar2)) {
			return 1;
		}
	}
	return 0;
	
}



// decompiled code
// original method signature: 
// struct _sdPlane * /*$ra*/ EventSurface(struct VECTOR *pos /*$a0*/, struct _sdPlane *plane /*$s1*/)
 // line 2560, offset 0x0004a688
	/* begin block 1 */
		// Start line: 2561
		// Start offset: 0x0004A688
		// Variables:
	// 		struct _EVENT *ev; // $s0
	// 		int i; // $a2

		/* begin block 1.1 */
			// Start line: 2572
			// Start offset: 0x0004A700
			// Variables:
		// 		int dist; // $a3
		// 		int end; // $a1
		// 		int cos; // $a2
		/* end block 1.1 */
		// End offset: 0x0004A880
		// End Line: 2623

		/* begin block 1.2 */
			// Start line: 2628
			// Start offset: 0x0004A894
			// Variables:
		// 		int dist; // stack offset -24

			/* begin block 1.2.1 */
				// Start line: 2632
				// Start offset: 0x0004A8A4
				// Variables:
			// 		int sin; // $a3
			// 		int cos; // $a2
			// 		int height; // $t0
			// 		int offset; // $a0
			/* end block 1.2.1 */
			// End offset: 0x0004AA20
			// End Line: 2664
		/* end block 1.2 */
		// End offset: 0x0004AA20
		// End Line: 2665
	/* end block 1 */
	// End offset: 0x0004AA78
	// End Line: 2681

	/* begin block 2 */
		// Start line: 6772
	/* end block 2 */
	// End Line: 6773

extern _sdPlane sea;
int debugOffset = 0;

// [D]
_sdPlane* EventSurface(VECTOR *pos, _sdPlane *plane)
{
	short uVar1;
	int* piVar2;
	int uVar3;
	short sVar4;
	int iVar5;
	int uVar6;
	int iVar7;
	int iVar8;
	_EVENT* ev;
	int iVar9;
	int dist;

	uVar6 = ((plane->surface & 0xffef));
	ev = event + uVar6;

	if (GameLevel == 1)
	{
	LAB_0004a880:
		if ((ev->flags & 0x800U) != 0)
		{
			if (OnBoat(pos, ev, &dist) == 0)
			{
			LAB_0004aa60:
				return &sea;
			}

			iVar8 = 200;

			if (GameLevel == 3)
				iVar8 = 256;

			piVar2 = ev->data;
			uVar6 = ev->data[1] & 0xfff;
			iVar5 = rcossin_tbl[uVar6 * 2];
			iVar9 = rcossin_tbl[uVar6 * 2 + 1];

			if (GameLevel == 3) 
			{
				iVar7 = dist * -4096 - iVar9 * 3328;

				if (0 < iVar7) 
				{
					uVar3 = 0xa0U - ev->data[1] & 0xfff;
					iVar9 = (int)rcossin_tbl[uVar3 * 2 + 1];

					if (iVar9 << 0xb < iVar7) 
					{
						debugOffset = iVar7;
						return &sea;
					}

					uVar6 = (iVar8 - (FIXED(iVar5 * 3328) + ev->data[2] + ev->position.vy)) + (FIXED(iVar7) * rcossin_tbl[uVar3 * 2]) / iVar9;
					iVar5 = rcossin_tbl[uVar3 * 2];
					goto LAB_0004a9f8;
				}
			}

			uVar6 = iVar8 + (((iVar5 * dist) / iVar9 - ev->data[2]) - (ev->position).vy);

		LAB_0004a9f8:
			plane->b = (iVar9 << 2);
			plane->a = 0;
			plane->c = (iVar5 << 2);
			plane->d = uVar6 ^ 0x40000000;
			return plane;
		}

		uVar6 = -(ev->position).vy;

		if (pos->vy < (int)(uVar6 - 100)) 
		{
			uVar6 = 0xbfffee02;
			goto LAB_0004aa50;
		}
	}
	else 
	{
		if (1 < GameLevel) 
		{
			if (GameLevel != 3)
			{
				return &sea;
			}
			goto LAB_0004a880;
		}

		if (GameLevel != 0)
			return &sea;

		if ((ev->flags & 0x30U) == 0) 
			iVar8 = pos->vz;
		else 
			iVar8 = pos->vx;

		if ((uVar6 & 1) == 0)
			iVar5 = ev->data[1];
		else 
			iVar5 = ev->data[-1]; // [A] WTF?

		uVar6 = ev->rotation & 0xfff;
		iVar7 = (int)rcossin_tbl[uVar6 * 2 + 1];
		iVar9 = (iVar5 - ev->data[0]) * iVar7;
		iVar8 = iVar8 - ev->data[0];
		iVar5 = iVar8;
		if (iVar8 < 0)
			iVar5 = -iVar8;

		if (iVar9 < 0)
			iVar9 = -iVar9;

		if (iVar9 < iVar5 << 0xc)
			goto LAB_0004aa60;

		uVar6 = (iVar8 * rcossin_tbl[uVar6 * 2]) / iVar7;

		sVar4 = (short)(iVar7 << 2);

		if (iVar8 > 1024) 
		{
			if (pos->vy + 200 < (int)uVar6)
				goto LAB_0004aa60;

			sVar4 = (iVar7 << 2);
		}

		plane->b = sVar4;

		if ((ev->flags & 0x30U) == 0) 
		{
			plane->a = 0;
			uVar1 = rcossin_tbl[(ev->rotation & 0xfff) * 2];
			plane->c = uVar1 * -4;
			plane->d = (uVar1 * -0x40000) >> 0x10;
		}
		else 
		{
			sVar4 = rcossin_tbl[(ev->rotation & 0xfff) * 2];
			plane->c = 0;
			plane->a = sVar4 * -4;
		}
	}
	uVar6 = uVar6 ^ 0x40000000;
LAB_0004aa50:
	plane->d = uVar6;
	return plane;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MakeEventTrackable(struct _EVENT *ev /*$a0*/)
 // line 2684, offset 0x0004bd6c
	/* begin block 1 */
		// Start line: 2685
		// Start offset: 0x0004BD6C
		// Variables:
	// 		struct _EVENT **p; // $v1
	/* end block 1 */
	// End offset: 0x0004BDA0
	// End Line: 2694

	/* begin block 2 */
		// Start line: 5368
	/* end block 2 */
	// End Line: 5369

	/* begin block 3 */
		// Start line: 10454
	/* end block 3 */
	// End Line: 10455

// [D]
void MakeEventTrackable(_EVENT *ev)
{
	_EVENT** p;

	p = trackingEvent;
	while (*p)
		p++;

	*p = ev;
	p[1] = NULL; // [A] is there a bug huh? I cannot understand...
}



// decompiled code
// original method signature: 
// void /*$ra*/ TriggerDoor(struct FixedEvent *door /*$a3*/, int *stage /*$a1*/, int sound /*$a2*/)
 // line 2696, offset 0x0004c208
	/* begin block 1 */
		// Start line: 11604
	/* end block 1 */
	// End Line: 11605

	/* begin block 2 */
		// Start line: 12825
	/* end block 2 */
	// End Line: 12826

// [D]
void TriggerDoor(FixedEvent *door, int *stage, int sound)
{
	if (*stage == 0)
	{
		if ((door->flags & 0x30U) != 0x10) 
			door->flags &= ~0x200;

		door->active = 2;
	}
	else 
	{
		door->active = 1;
		door->flags |= 0x200;

		*stage = -1;
	}

	if (sound != 0)
		SetMSoundVar(1, &door->position);
}



// decompiled code
// original method signature: 
// struct VECTOR * /*$ra*/ TriggerEvent(int i /*$s4*/)
 // line 2718, offset 0x0004aa78
	/* begin block 1 */
		// Start line: 2719
		// Start offset: 0x0004AA78
		// Variables:
	// 		static int stage[10]; // offset 0x200
	// 		struct VECTOR *pos; // $s7

		/* begin block 1.1 */
			// Start line: 2726
			// Start offset: 0x0004AAB0
			// Variables:
		// 		int loop; // $v1
		/* end block 1.1 */
		// End offset: 0x0004AAD0
		// End Line: 2731

		/* begin block 1.2 */
			// Start line: 2739
			// Start offset: 0x0004AB20
			// Variables:
		// 		struct _EVENT *ev; // $a2
		/* end block 1.2 */
		// End offset: 0x0004AB20
		// End Line: 2740

		/* begin block 1.3 */
			// Start line: 2754
			// Start offset: 0x0004AC08

			/* begin block 1.3.1 */
				// Start line: 2757
				// Start offset: 0x0004AC08
				// Variables:
			// 		struct MissionTrain *train; // $s1

				/* begin block 1.3.1.1 */
					// Start line: 2763
					// Start offset: 0x0004AC38
				/* end block 1.3.1.1 */
				// End offset: 0x0004AC50
				// End Line: 2769

				/* begin block 1.3.1.2 */
					// Start line: 2774
					// Start offset: 0x0004AC5C
					// Variables:
				// 		struct _EVENT *ev; // $s0
				// 		int count; // $s2
				// 		int offset; // $s6

					/* begin block 1.3.1.2.1 */
						// Start line: 2785
						// Start offset: 0x0004ACAC
						// Variables:
					// 		int pos; // $a1
					/* end block 1.3.1.2.1 */
					// End offset: 0x0004ACAC
					// End Line: 2785
				/* end block 1.3.1.2 */
				// End offset: 0x0004AD88
				// End Line: 2817
			/* end block 1.3.1 */
			// End offset: 0x0004AD88
			// End Line: 2819

			/* begin block 1.3.2 */
				// Start line: 2831
				// Start offset: 0x0004ADB8
				// Variables:
			// 		struct _EVENT *ev; // $v1
			// 		int count; // $a0
			/* end block 1.3.2 */
			// End offset: 0x0004AE04
			// End Line: 2848
		/* end block 1.3 */
		// End offset: 0x0004AE28
		// End Line: 2860

		/* begin block 1.4 */
			// Start line: 2867
			// Start offset: 0x0004AE90
		/* end block 1.4 */
		// End offset: 0x0004AF60
		// End Line: 2897

		/* begin block 1.5 */
			// Start line: 2905
			// Start offset: 0x0004AFA8

			/* begin block 1.5.1 */
				// Start line: 2907
				// Start offset: 0x0004AFA8
				// Variables:
			// 		int loop; // $s0
			/* end block 1.5.1 */
			// End offset: 0x0004B044
			// End Line: 2923
		/* end block 1.5 */
		// End offset: 0x0004B0D0
		// End Line: 2941
	/* end block 1 */
	// End offset: 0x0004B29C
	// End Line: 2992

	/* begin block 2 */
		// Start line: 7076
	/* end block 2 */
	// End Line: 7077

	/* begin block 3 */
		// Start line: 7114
	/* end block 3 */
	// End Line: 7115

	/* begin block 4 */
		// Start line: 7118
	/* end block 4 */
	// End Line: 7119

VECTOR * TriggerEvent(int i)
{
	UNIMPLEMENTED();
	return (VECTOR*)player[0].pos;
	/*
	ushort uVar1;
	_EVENT *p_Var2;
	undefined4 *puVar3;
	int count;
	int *piVar4;
	int iVar5;
	int iVar6;
	_EVENT *p_Var7;
	_EVENT *ev;
	int iVar8;
	_EVENT *ev_00;

	p_Var2 = firstEvent;
	p_Var7 = firstMissionEvent;
	ev = event;
	ev_00 = (_EVENT *)0x0;
	if (i == -1) {
		count = 9;
		puVar3 = &DAT_000cde74;
		do {
			*puVar3 = 0;
			count = count + -1;
			puVar3 = puVar3 + -1;
		} while (-1 < count);
		return (VECTOR *)0x0;
	}
	if (((GameLevel - 2U < 2) && (0 < i)) && (i < 4)) {
		if (*(int *)(&stage_90 + i * 4) == 0) {
			p_Var7 = firstMissionEvent + i + -1;
			ev = (_EVENT *)((int)p_Var7 - (int)event);
			p_Var7->next = firstEvent->next;
			p_Var2->next = p_Var7;
			VisibilityLists(VIS_ADD, (int)ev * -0x33333333 >> 3);
			SetMSoundVar(i, (VECTOR *)0x0);
			detonator.count = detonator.count + 1;
		}
		goto switchD_0004afa0_caseD_1;
	}
	if (GameLevel == 1) {
		if (4 < (uint)i) goto switchD_0004afa0_caseD_1;
		count = i * 4;
		switch (i) {
		case 0:
		switchD_0004ae88_caseD_0:
			event->timer = 1;
			break;
		case 1:
			(event->position).vx = INT_0009e8a0;
			count = INT_ARRAY_0009e8a4[0];
			ev->timer = 1;
			ev->node = INT_ARRAY_0009e8a4;
			ev->data = INT_ARRAY_0009e894;
			(ev->position).vz = count;
			break;
		case 2:
			TriggerDoor(&havanaFixed, (int *)(&stage_90 + count), 1);
			break;
		case 3:
			PrepareSecretCar();
			events.cameraEvent = &FixedEvent_0009e9e8;
			TriggerDoor(&FixedEvent_0009e9e8, (int *)(&stage_90 + count), 0);
			break;
		case 4:
			if (*(int *)(&stage_90 + count) != 0) {
				SpecialCamera(SPECIAL_CAMERA_WAIT, 0);
				event[1].node = event[1].node + 1;
			}
			ev = event;
			event[1].timer = 0;
			events.cameraEvent = (FixedEvent *)(ev + 1);
		}
	}
	else {
		if (GameLevel < 2) {
			if ((GameLevel == 0) && ((uint)i < 7)) {
				count = i * 4;
				switch (i) {
				case 0:
				case 1:
					if (*(int *)(&stage_90 + count) == 0) {
						ev_00 = (&missionTrain)[i].engine;
						MakeEventTrackable(ev_00);
						ev_00->flags = ev_00->flags | 0x180;
						count = -0x640;
						if (-1 < *(&missionTrain)[i].node - (&missionTrain)[i].start) {
							count = 0x640;
						}
						iVar8 = 0;
						ev = ev_00;
						do {
							piVar4 = (&missionTrain)[i].node;
							if (*piVar4 == -0x7ffffffe) {
								iVar6 = piVar4[-1];
							}
							else {
								iVar6 = piVar4[1];
							}
							if ((&missionTrain)[i].startDir == 0x8000) {
								uVar1 = ev->flags;
								(ev->position).vx = iVar6;
								ev->flags = uVar1 | 0x8000;
								(ev->position).vz = (&missionTrain)[i].start + iVar8 * count;
							}
							else {
								ev->flags = ev->flags & 0x7fff;
								iVar5 = (&missionTrain)[i].start;
								(ev->position).vz = iVar6;
								(ev->position).vx = iVar5 + iVar8 * count;
							}
							piVar4 = (&missionTrain)[i].node;
							ev->data = &(&missionTrain)[i].cornerSpeed;
							ev->timer = 0;
							ev->node = piVar4;
							ev->flags = ev->flags & 0x8fffU | 0x3000;
							SetElTrainRotation(ev);
							iVar8 = iVar8 + 1;
						} while ((ev->next != (_EVENT *)0x0) && (ev = ev->next, (ev->flags & 0x400U) == 0));
					}
					else {
						ev_00 = (&missionTrain)[i].engine;
						if (ev_00->timer != 0) {
							ev_00->timer = 1;
						}
					}
					break;
				default:
					if (*(int *)(&stage_90 + count) == 0) {
						count = 9;
						ev = firstMissionEvent;
						do {
							p_Var7 = ev;
							p_Var7->flags = p_Var7->flags | 0x100;
							if (i == 4) {
								p_Var7->timer = 0xa28;
							}
							else {
								p_Var7->timer = 1000;
							}
							count = count + -1;
							ev = p_Var7 + 1;
						} while (-1 < count);
						if (i == 2) {
							p_Var7[-1].timer = 0xa28;
							p_Var7->timer = 0xa28;
						}
					}
					else {
						firstMissionEvent[8].timer = 0;
						p_Var7[9].timer = 0;
					}
					break;
				case 5:
					PrepareSecretCar();
					events.cameraEvent = &chicagoDoor;
				case 6:
					TriggerDoor((FixedEvent *)(INT_ARRAY_0009e724 + i * 0xb + 0x43), (int *)(&stage_90 + count)
						, 1);
				}
			}
			goto switchD_0004afa0_caseD_1;
		}
		if (GameLevel == 2) {
			switch (i) {
			case 0:
				count = 0;
				iVar8 = 0;
				do {
					ev = (_EVENT *)((int)&(event->position).vx + iVar8);
					ev->data = VegasTrainData;
					InitTrain(ev, count, 1);
					iVar6 = (int)&(event->position).vx + iVar8;
					*(ushort *)(iVar6 + 0x1c) = *(ushort *)(iVar6 + 0x1c) | 0x200;
					if (1 < count) {
						VisibilityLists(VIS_ADD, count);
					}
					ev = event;
					count = count + 1;
					iVar8 = iVar8 + 0x28;
				} while (count < 9);
				event->flags = event->flags | 0x500;
				MakeEventTrackable(ev);
				event[1].next = event + 2;
				break;
			case 4:
				TriggerDoor(&FixedEvent_0009e964 + i, (int *)(&stage_90 + i * 4), 0);
				break;
			case 8:
				events.cameraEvent = &FixedEvent_0009eac4;
				PrepareSecretCar();
			case 5:
			case 6:
			case 7:
				TriggerDoor(&FixedEvent_0009e964 + i, (int *)(&stage_90 + i * 4), 1);
				break;
			case 9:
				SetMSoundVar(5, (VECTOR *)0x0);
			}
			goto switchD_0004afa0_caseD_1;
		}
		if (GameLevel != 3) goto switchD_0004afa0_caseD_1;
		count = i * 4;
		switch (i) {
		case 0:
			goto switchD_0004ae88_caseD_0;
		case 4:
			TriggerDoor(&FixedEvent_0009eb48, (int *)(&stage_90 + count), 0);
			TriggerDoor(&FixedEvent_0009eb74, (int *)(&stage_90 + count), 0);
			events.cameraEvent = &FixedEvent_0009eb48;
			break;
		case 5:
		case 6:
			TriggerDoor(&vegasDoor + i, (int *)(&stage_90 + count), (uint)(i == 5));
			break;
		case 7:
			if (*(int *)(&stage_90 + count) == 0) {
				ev_00 = event + 1;
			}
			else {
				event[1].position.vy = -0x11;
				ev[1].position.vx = -0x3afd3;
				ev[1].position.vz = -0x33e9e;
				ev[1].timer = -2;
				ev[1].model = HelicopterData.deadModel;
			}
			break;
		case 8:
			PingOutAllSpecialCivCars();
			TriggerDoor(&FixedEvent_0009eba0, (int *)(&stage_90 + count), 0);
			TriggerDoor(&FixedEvent_0009ebcc, (int *)(&stage_90 + count), 0);
			events.cameraEvent = &FixedEvent_0009eba0;
		}
	}
switchD_0004afa0_caseD_1:
	if (i < 10) {
		*(int *)(&stage_90 + i * 4) = *(int *)(&stage_90 + i * 4) + 1;
	}
	return (VECTOR *)ev_00;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ OffsetTarget(struct VECTOR *target /*$a0*/)
 // line 2994, offset 0x0004bd2c
	/* begin block 1 */
		// Start line: 8890
	/* end block 1 */
	// End Line: 8891

	/* begin block 2 */
		// Start line: 10760
	/* end block 2 */
	// End Line: 10761

	/* begin block 3 */
		// Start line: 10761
	/* end block 3 */
	// End Line: 10762

// [D]
void OffsetTarget(VECTOR *target)
{
	target->vx -= boatOffset.vx;
	target->vy -= boatOffset.vy;
	target->vz -= boatOffset.vz;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SpecialCamera(enum SpecialCamera type /*$t2*/, int change /*$a1*/)
 // line 2999, offset 0x0004b29c
	/* begin block 1 */
		// Start line: 3000
		// Start offset: 0x0004B29C
		// Variables:
	// 		static int rememberCamera[3]; // offset 0x230
	// 		static short boatCamera[6]; // offset 0x684

		/* begin block 1.1 */
			// Start line: 3013
			// Start offset: 0x0004B2E4
			// Variables:
		// 		int *hackCamera; // $a2
		// 		short *boat; // $t3
		/* end block 1.1 */
		// End offset: 0x0004B540
		// End Line: 3114
	/* end block 1 */
	// End offset: 0x0004B5FC
	// End Line: 3142

	/* begin block 2 */
		// Start line: 7742
	/* end block 2 */
	// End Line: 7743

	/* begin block 3 */
		// Start line: 7750
	/* end block 3 */
	// End Line: 7751

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

//[D]
void SpecialCamera(enum SpecialCamera type, int change)
{
	static int rememberCamera[3]; // offset 0x230
	static short boatCamera[6] = {
		-1000, 2100, 6000,
		-5000, 3584, -5000
	};

	int* hackCamera;
	short* boat;

	if ((change == 0) && (type != SPECIAL_CAMERA_WAIT)) 
	{
		cameraDelay.delay = 1;
		cameraDelay.type = (uint)type;
		camera_change = 1;
		return;
	}

	if (type == SPECIAL_CAMERA_RESET)
	{
		events.cameraEvent = NULL;
		gStopPadReads = 0;

		camera_position.vx = rememberCamera[0];
		camera_angle.vy = (short)rememberCamera[1];
		camera_position.vz = rememberCamera[2];

		player[0].cameraPos.vx = rememberCamera[0];
		player[0].cameraPos.vy = camera_position.vy;
		player[0].cameraPos.vz = rememberCamera[2];
		player[0].cameraPos.pad = camera_position.pad;
		goto LAB_0004b5b8;
	}

	if (SPECIAL_CAMERA_RESET < type) 
	{
		if (type == SPECIAL_CAMERA_WAIT)
		{
			cameraDelay.delay = 100;
			cameraDelay.type = 1;
			gStopPadReads = 1;
		}
		goto LAB_0004b5b8;
	}

	boat = NULL;
	rememberCamera[0] = camera_position.vx;
	rememberCamera[1] = camera_angle.vy;
	rememberCamera[2] = camera_position.vz;

	if (GameLevel == 1) 
	{
		if (gCurrentMissionNumber == 15) 
		{
			boat = boatCamera;
		LAB_0004b418:
			events.cameraEvent = (_EVENT*)0x1;
		}
		else 
		{
			hackCamera = HavanaCameraHack;

			if (type == SPECIAL_CAMERA_SET2)
			{
				hackCamera = HavanaCameraHack + 6;
				camera_position.vy = -500;
			}
			else if (doneFirstHavanaCameraHack == 0)
			{
				doneFirstHavanaCameraHack = 1;
			}
			else
			{
			LAB_0004b42c:
				hackCamera = hackCamera + 3;
			}
		}
	}
	else 
	{
		if (GameLevel == 0) 
		{
			hackCamera = ChicagoCameraHack;
		}
		else if (GameLevel == 2)
		{
			hackCamera = VegasCameraHack;
			if (gCurrentMissionNumber == 0x17)
			{
				if (type != SPECIAL_CAMERA_SET2) 
				{
					hackCamera = VegasCameraHack + 6;
					goto LAB_0004b418;
				}

				hackCamera = VegasCameraHack + 9;
			}
			else if (gCurrentMissionNumber == 0x16)
			{
				hackCamera = VegasCameraHack + 0xd;
				events.cameraEvent = (_EVENT*)0x1;
				camera_position.vy = -1800;
			}
			else if (gCurrentMissionNumber == 0x1e)
			{
				hackCamera = hackCamera + 3;
			}
		}
		else if (GameLevel == 3)
		{
			if (gCurrentMissionNumber == 35)
			{
				boat = boatCamera + 3;
			}
			else
			{
				hackCamera = RioCameraHack;

				if (0 < camera_position.vz)
				{
					hackCamera = RioCameraHack + 3;
				}
			}
		}
	}

	if (boat == NULL) 
	{
		camera_position.vx = hackCamera[0];
		camera_angle.vy = hackCamera[1];
		camera_position.vz = hackCamera[2];
	}
	else 
	{
		camera_position.vx = (event->position).vx + boat[0];
		camera_angle.vy = boat[1];
		camera_position.vz = (event->position).vz + boat[2];
	}

	player[0].cameraPos = camera_position;

	if (events.cameraEvent != NULL) 
	{
		gStopPadReads = 1;
	}

LAB_0004b5b8:
	if (type != SPECIAL_CAMERA_WAIT) 
	{
		camera_change = 1;
		VisibilityLists(VIS_SORT, 0);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ScreenShake(int count /*$a0*/, struct SVECTOR *ang /*$s0*/)
 // line 3144, offset 0x0004c280
	/* begin block 1 */
		// Start line: 3145
		// Start offset: 0x0004C280
	/* end block 1 */
	// End offset: 0x0004C330
	// End Line: 3150

	/* begin block 2 */
		// Start line: 13723
	/* end block 2 */
	// End Line: 13724

	/* begin block 3 */
		// Start line: 13724
	/* end block 3 */
	// End Line: 13725

// [D]
void ScreenShake(int count, SVECTOR *ang)
{
	eventHaze = count << 2;

	camera_angle.vx = (ang->vx + (Random2(0) % (eventHaze << 1))) - eventHaze;
	camera_angle.vy = (ang->vy + (Random2(0) % (eventHaze * 2))) - eventHaze;

	eventHaze = eventHaze * 3;
}



// decompiled code
// original method signature: 
// int /*$ra*/ DetonatorTimer()
 // line 3152, offset 0x0004b5fc
	/* begin block 1 */
		// Start line: 3154
		// Start offset: 0x0004B5FC
		// Variables:
	// 		static struct SVECTOR rememberCameraAngle; // offset 0x30

		/* begin block 1.1 */
			// Start line: 3168
			// Start offset: 0x0004B698

			/* begin block 1.1.1 */
				// Start line: 3175
				// Start offset: 0x0004B6B0
				// Variables:
			// 		static int count; // offset 0x38

				/* begin block 1.1.1.1 */
					// Start line: 3179
					// Start offset: 0x0004B6CC
					// Variables:
				// 		struct VECTOR pos; // stack offset -32
				/* end block 1.1.1.1 */
				// End offset: 0x0004B700
				// End Line: 3184

				/* begin block 1.1.1.2 */
					// Start line: 3188
					// Start offset: 0x0004B720
					// Variables:
				// 		struct VECTOR pos; // stack offset -32
				/* end block 1.1.1.2 */
				// End offset: 0x0004B720
				// End Line: 3189
			/* end block 1.1.1 */
			// End offset: 0x0004B7C8
			// End Line: 3204
		/* end block 1.1 */
		// End offset: 0x0004B7DC
		// End Line: 3210

		/* begin block 1.2 */
			// Start line: 3218
			// Start offset: 0x0004B864
			// Variables:
		// 		struct _EVENT *ev; // $s0
		// 		struct VECTOR pos; // stack offset -32

			/* begin block 1.2.1 */
				// Start line: 3247
				// Start offset: 0x0004B9B0
				// Variables:
			// 		struct VECTOR *epicentre; // $v1
			/* end block 1.2.1 */
			// End offset: 0x0004BA08
			// End Line: 3260
		/* end block 1.2 */
		// End offset: 0x0004BA8C
		// End Line: 3275
	/* end block 1 */
	// End offset: 0x0004BAB0
	// End Line: 3278

	/* begin block 2 */
		// Start line: 8082
	/* end block 2 */
	// End Line: 8083

	/* begin block 3 */
		// Start line: 8093
	/* end block 3 */
	// End Line: 8094

	/* begin block 4 */
		// Start line: 8094
	/* end block 4 */
	// End Line: 8095

	/* begin block 5 */
		// Start line: 8096
	/* end block 5 */
	// End Line: 8097

/* WARNING: Unknown calling convention yet parameter storage is locked */

static struct _EVENT* firstMissionEvent;

// [D]
int DetonatorTimer(void)
{
	static struct SVECTOR rememberCameraAngle; // offset 0x30
	static int count = 0; // offset 0x38

	long* plVar1;
	_EVENT* _ev;
	int cnt;
	_EVENT* ev;
	VECTOR pos;

	_ev = firstMissionEvent;
	ev = event;
	if (gCurrentMissionNumber == 23) 
	{
		if (detonator.timer - 3U < 0x11) 
		{
			cnt = detonator.timer + -2;
		}
		else 
		{
			if (8 < detonator.timer - 0x1fU)
			{
				if (detonator.timer == 0x15)
				{
					count = count + 1;
					if ((count & 7) == 0)
					{
						AddExplosion(camera_position, BIG_BANG);
					}

					camera_position.vz += 150;

					if (VegasCameraHack[12] < camera_position.vz)
					{
						pos.vx = camera_position.vx;
						pos.vy = camera_position.vy;
						pos.vz = 271695;

						AddExplosion(pos, HEY_MOMMA);

						rememberCameraAngle = camera_angle;
						Mission.timer[0].flags = Mission.timer[0].flags & 0xef;
						SetMissionComplete();
					}
					else 
					{
						detonator.timer = detonator.timer + 1;
					}

					player[0].cameraPos.vz = camera_position.vz;
				}
				else if (detonator.timer == 0)
				{
					SpecialCamera(SPECIAL_CAMERA_SET, 0);
					detonator.timer = 0x46;
				}
				else if (detonator.timer == 0x16)
				{
					SpecialCamera(SPECIAL_CAMERA_SET2, 0);
				}
				else if (detonator.timer == 40)
				{
					BombThePlayerToHellAndBack(gCarWithABerm);
					car_data[gCarWithABerm].st.n.linearVelocity[1] += 200000;
					rememberCameraAngle = camera_angle;
				}

				goto LAB_0004ba8c;
			}

			cnt = detonator.timer - 30;
		}

		ScreenShake(cnt, &rememberCameraAngle);

		goto LAB_0004ba8c;
	}

	if (detonator.timer - 0x8dU < 0x13) 
	{
		ScreenShake(detonator.timer + -0x8c, &rememberCameraAngle);
		Setup_Smoke(&_ev->position, 100, 500, 1, 0, &dummy, 0);
		goto LAB_0004ba8c;
	}

	if (detonator.timer == 167)
	{
		ev = firstMissionEvent + 1;
	LAB_0004ba0c:
		ev = ev + 1;
	}
	else 
	{
		if (detonator.timer < 168)
		{
			if (detonator.timer == 0)
			{
				cnt = detonator.count + -1;
				ev = firstMissionEvent;
				if (detonator.count < 3)
				{
					while (detonator.count = cnt, detonator.count != -1) 
					{
						AddExplosion(ev->position, BIG_BANG);
						cnt = detonator.count + -1;
						ev = ev + 1;
					}

					return 0;
				}

				detonator.timer = 200;
				SpecialCamera(SPECIAL_CAMERA_SET, 0);
				events.cameraEvent = (_EVENT*)0x1;

				rememberCameraAngle = camera_angle;
			}
			else if (detonator.timer == 0xa0)
			{
				_ev = firstMissionEvent + 1;
				if (GameLevel == 3)
				{
					event->flags = event->flags & 0xfffeU | 0x20;
					_ev = ev;
				}

				AddExplosion(_ev->position, HEY_MOMMA);
			}

			goto LAB_0004ba8c;
		}

		ev = firstMissionEvent;
		if (detonator.timer == 180) 
			goto LAB_0004ba0c;

		if (detonator.timer != 190)
			goto LAB_0004ba8c;
	}

	pos.vx = (ev->position).vx;
	pos.vy = (ev->position).vy;
	pos.vz = (ev->position).vz;

	if (GameLevel == 3) 
	{
		pos.vx = pos.vx - boatOffset.vx;
		pos.vy = pos.vy - boatOffset.vy;
		pos.vz = pos.vz - boatOffset.vz;
	}

	AddExplosion(pos, BIG_BANG);
LAB_0004ba8c:
	detonator.timer--;
	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ MultiCarEvent(struct _TARGET *target /*$a0*/)
 // line 3288, offset 0x0004bab0
	/* begin block 1 */
		// Start line: 3289
		// Start offset: 0x0004BAB0
		// Variables:
	// 		struct MULTICAR_DATA *data; // $s0
	// 		int i; // $s1
	// 		struct _EVENT *ev; // $s2

		/* begin block 1.1 */
			// Start line: 3301
			// Start offset: 0x0004BAF8
			// Variables:
		// 		int n; // $a1
		/* end block 1.1 */
		// End offset: 0x0004BAF8
		// End Line: 3303
	/* end block 1 */
	// End offset: 0x0004BBD4
	// End Line: 3313

	/* begin block 2 */
		// Start line: 8381
	/* end block 2 */
	// End Line: 8382

	/* begin block 3 */
		// Start line: 8392
	/* end block 3 */
	// End Line: 8393

	/* begin block 4 */
		// Start line: 8398
	/* end block 4 */
	// End Line: 8399

// [D]
void MultiCarEvent(_TARGET *target)
{
	_EVENT *first;
	int n;
	_EVENT *ev;
	MULTICAR_DATA *data;
	int i;

	first = firstEvent;

	data = (MULTICAR_DATA *)(target->data + 1);
	
	firstEvent = multiCar.event + multiCar.count;
	n = target->data[1];
	
	i = 0;
	while (n != -0x80000000) 
	{
		n = (multiCar.event - event) + multiCar.count;
		ev = event + n;
		ev->position.vx = data->x;
		ev->position.vy = -0x138;
		ev->position.vz = data->z;
		ev->rotation = data->rot;

		VisibilityLists(VIS_ADD, n);

		multiCar.count++;
		data++;
		i++;

		if (i > 4) 
			break;

		n = data->x;
	}
	
	multiCar.event[multiCar.count - 1].next = first;
}





