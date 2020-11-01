#include "DRIVER2.H"
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
#include "SYSTEM.H"
#include "SPOOL.H"
#include "MAP.H"
#include "TEXTURE.H"
#include "CIV_AI.H"
#include "PEDEST.H"
#include "SHADOW.H"
#include "GAMESND.H"
#include "DR2ROADS.H"
#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"
#include "RAND.H"

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
	0, 123, 32768, 982000, -68855, 762717, 0x80000000
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
	{ 0, ElTrainData + 7, 125, 145, 215, -204500, 0 }
};

FixedEvent chicagoDoor[3] =
{
  {
	{ -207616, 0, 659706, 0 },
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
	{ -209152, -512, 668928, 0 },
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
	{ 195264, -3728, 74752, 0 },
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
	{ -183296, -273, -41720, 0 },
	0,
	0,
	800,
	0,
	25,
	50,
	64,
	0,
	0,
	0,
	"DOOR"
  },
  {
	{ -455168, 1529, -125440, 0 },
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
	{ -487936, 0, -136689, 0 },
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
	{ -11851, 0, 844163, 0 },
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
	{ -106242, -239, -216960, 0 },
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
	{ 63058, -231, 501184, 0 },
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
	{ -159356, -176, 647024, 0 },
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
	{ 123936, -170, 4928, 0 },
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
	{ -123328, -177, -254720, 0 },
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
	{ -125248, -17, -256208, 0 },
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
	{ -274000, -17, -321408, 0 },
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
	{ -274000, -17, -322432, 0 },
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
	{ -40432, -17, 383328, 0 },
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
	{ -39424, -17, 383328, 0 },
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
  { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u }, 0u, 0u, 0, 0 },
  0,
  0,
  0,
  0
};

static Foam foam;

EventGlobal events;

CELL_OBJECT* EventCop;
int event_models_active = 0;

static EVENT(*trackingEvent[2]);
static MS_TARGET(*carEvent[8]);
static int cameraEventsActive = 0;
static CameraDelay cameraDelay;
static Detonator detonator;
static int eventHaze = 0;
static int carsOnBoat = 0;
static int doneFirstHavanaCameraHack = 0;
static SVECTOR boatOffset;
static FixedEvent* fixedEvent = NULL;

MultiCar multiCar;

EVENT* firstEvent;
EVENT* firstMissionEvent;
EVENT* event;

static EventCamera eventCamera;

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
		// 		int num; // $a0
		/* end block 1.1 */
		// End offset: 0x00045B28
		// End Line: 259

		/* begin block 1.2 */
			// Start line: 263
			// Start offset: 0x00045B30
			// Variables:
		// 		EVENT *ev; // $a0
		// 		int multiple; // $a2

			/* begin block 1.2.1 */
				// Start line: 274
				// Start offset: 0x00045BBC
				// Variables:
			// 		VECTOR pos; // stack offset -16
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

// [D] [T]
int GetVisValue(int index, int zDir)
{
	int camera;
	int radius;
	EVENT* ev;
	VECTOR pos;

	if (index & 0xC000)
	{
		camera = (index >> 0xf ^ 1) & 1;

		if (zDir == 0)
		{
			pos.vx = player[camera].cameraPos.vx;
			radius = 16000;
		}
		else
		{
			pos.vx = player[camera].cameraPos.vz;
			radius = 16000;
		}
	}
	else
	{
		int multiple;

		if (index & 0x80)
			ev = (EVENT*)&fixedEvent[index & 0x7f];
		else
			ev = &event[index & 0x7f];

		if (index & 0xf00)
		{
			if ((ev->flags & 0x30) && zDir == 0 || !(ev->flags & 0x30) && zDir != 0)
				multiple = 1;
			else
				multiple = 0;
		}
		else
		{
			multiple = 1;
		}

		if (multiple)
		{
			pos.vx = ev->position.vx;
			pos.vz = ev->position.vz;

			if ((ev->flags & 0xCC0U) == 0x80)
			{
				pos.vx -= boatOffset.vx;
				pos.vz -= boatOffset.vz;
			}

			if (zDir != 0)
				pos.vx = pos.vz;
		}
		else
		{
			pos.vx = ev->node[(index & 0xf00U) >> 8];
		}

		radius = ev->radius;
	}

	if (index & 0x2000)
		pos.vx -= radius;

	if (index & 0x1000)
		pos.vx += radius;

	return pos.vx;
}



// decompiled code
// original method signature: 
// void /*$ra*/ VisibilityLists(VisType type /*$a0*/, int i /*$s2*/)
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
		// 		int num; // $a1
		/* end block 1.2 */
		// End offset: 0x00045F78
		// End Line: 361

		/* begin block 1.3 */
			// Start line: 365
			// Start offset: 0x00045F90
			// Variables:
		// 		EVENT *ev; // $a0
		/* end block 1.3 */
		// End offset: 0x00046068
		// End Line: 384

		/* begin block 1.4 */
			// Start line: 387
			// Start offset: 0x00046068
			// Variables:
		// 		EVENT *ev; // $v1
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

static unsigned short* xVis;
static unsigned short* zVis;

// [D]
void VisibilityLists(VisType type, int i)
{
	static unsigned short xList[128]; // offset 0x0
	static unsigned short zList[128]; // offset 0x100
	static unsigned short(*firstX[2]); // offset 0x0
	static unsigned short(*firstZ[2]); // offset 0x8
	static int count; // offset 0x10

	static unsigned short(*list[2]) = {
		xList, zList
	};

	int k;
	EVENT* ev;
	int tempList;
	int num;
	int n;
	int j;
	int camera;
	int table[128];

	//debugCount = &count.10;
	if (type == VIS_SORT)
	{
		num = 0;
		do {
			j = 0;

			while (j < count)
			{
				table[j] = GetVisValue(list[num][j], num);

				// add sorted
				// code is similar to sorting code in DrawAllTheCars
				if (j != 0 && (table[j] < table[j - 1]))
				{
					tempList = list[num][j];

					k = j - 1;
					do {
						n = k;

						table[k + 1] = table[k];
						list[num][k + 1] = list[num][k];

						if (k == 0)
							break;

						k--;
					} while (table[j] < table[k]);

					table[n] = table[j];
					list[num][n] = tempList;
				}

				j++;
			}
			num++;
		} while (num < 2);

		num = 0;
		while (num < NumPlayers)
		{
			if (num != 0)
				camera = 0x4000;
			else
				camera = 0x8000;

			firstX[num] = xList;
			firstZ[num] = zList;

			do {
			} while ((*(firstX[num]++) & camera) == 0);

			do {
			} while ((*(firstZ[num]++) & camera) == 0);

			num++;
		}
	}
	else if (type == VIS_INIT)
	{
		zList[0] = -0x6000;
		xList[0] = -0x6000;
		zList[1] = -0x7000;
		xList[1] = -0x7000;

		count = 2;

		if (NumPlayers == 2)
		{
			zList[2] = 0x6000;
			xList[2] = 0x6000;
			zList[3] = 0x5000;
			xList[3] = 0x5000;

			count = 4;
		}

		num = 0;
		while (num < NumPlayers)
		{
			firstX[num] = xList;
			firstZ[num] = zList;
			num++;
		}
	}
	else if (type == VIS_ADD)
	{
		if (i & 0x80)
			ev = (EVENT*)&fixedEvent[i & 0x7f];
		else
			ev = &event[i & 0x7f];

		if (ev->radius == 0)
		{
			xList[count] = i;
			zList[count] = i;

			count++;
		}
		else
		{
			xList[count] = i | 0x2000;
			zList[count] = i | 0x2000;

			xList[count + 1] = i | 0x1000;
			zList[count + 1] = i | 0x1000;

			count += 2;
		}
	}
	else if (type == VIS_NEXT)
	{
		ev = firstEvent;

		while (ev != NULL)
		{
			ev->flags &= ~4;
			ev = ev->next;
		}

		xVis = firstX[i];
		zVis = firstZ[i];
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetElTrainRotation(EVENT *ev /*$a1*/)
 // line 402, offset 0x0004be5c
	/* begin block 1 */
		// Start line: 804
	/* end block 1 */
	// End Line: 805

// [D] [T]
void SetElTrainRotation(EVENT* ev)
{
	if (ev->flags & 0x8000)
		ev->rotation = 0x400;
	else
		ev->rotation = 0;

	if (ev->node[0] < ev->node[2])
		ev->rotation += 0x800;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitTrain(EVENT *ev /*$s0*/, int count /*$s3*/, int type /*$a2*/)
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

// [D] [T]
void InitTrain(EVENT* ev, int count, int type)
{
	ushort uVar1;
	uint mv;
	int* to;
	int length;
	int height;

	ev->node = &ev->data[3];

	ev->timer = 0;
	ev->flags = ev->data[2] | 0x2;

	if (type == 0)
	{
		height = -1773;
		length = 1600;

		SetElTrainRotation(ev);
	}
	else if (type == 1)
	{
		height = -734;
		length = 3700;

		ev->rotation = 0;
	}

	ev->position.vy = height;

	ev->flags &= ~0x7000;

	if (ev->node[3] != -0x80000000)
		ev->flags |= 0x3000;

	to = ev->node;

	if (to[2] == -0x7ffffffe)
		mv = to[3] - to[0] >> 0x1f;
	else
		mv = to[2] - to[0] >> 0x1f;

	if (ev->flags & 0x8000)
	{
		ev->position.vz = to[0] + ((count * length ^ mv) - mv);
		ev->position.vx = to[1];
	}
	else
	{
		ev->position.vx = to[0] + ((count * length ^ mv) - mv);
		ev->position.vz = to[1];
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitDoor(FixedEvent *ev /*$a0*/, EVENT ***e /*$a1*/, int *cEvents /*$a2*/)
 // line 471, offset 0x0004beb8
	/* begin block 1 */
		// Start line: 8350
	/* end block 1 */
	// End Line: 8351

	/* begin block 2 */
		// Start line: 8352
	/* end block 2 */
	// End Line: 8353

// [D] [T]
void InitDoor(FixedEvent* ev, EVENT*** e, int* cEvents)
{
	ev->active = 0;
	ev->rotation = ev->finalRotation;
	ev->flags |= 0x200;

	*(FixedEvent**)*e = ev;	// [A] is that gonna work?
	*e = &(**e)->next;

	VisibilityLists(VIS_ADD, (ev - fixedEvent) | 0x80);
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

// [D] [T]
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
	// 		EVENT **e; // stack offset -56

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
				// 		XYPAIR offset; // stack offset -64
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

// [D] [A] long function, please debug
void SetUpEvents(int full)
{
	bool bVar1;
	short sVar2;
	long lVar3;
	int iVar4;
	int iVar5;
	FixedEvent* ev;
	int* piVar6;
	EVENT* ev_00;
	int iVar7;
	int loop;
	int* piVar8;
	EVENT* p_Var9;
	int i;
	int detonatorModel;
	uint __i;
	uint _i;
	uint uVar10;
	int trainModel;
	XYPAIR offset;
	EVENT** e;
	int cEvents;
	int ElTrackModel;
	int carModel;

	firstEvent = NULL;
	e = &firstEvent;

	if (doSpooling == 0)
	{
		firstEvent = NULL;
		EventCop = NULL;
		return;
	}

	MALLOC_BEGIN()

		if (full)
		{
			EventCop = (CELL_OBJECT*)mallocptr;
			event = (EVENT*)(mallocptr + 256);
			mallocptr = (char*)event;
		}

	ev_00 = event;
	cEvents = 0;

	if (GameLevel == 0)
	{
		bVar1 = false;
		piVar6 = LiftingBridges + 1;
		__i = 0;

		while (__i < LiftingBridges[0])
		{
			cameraEventsActive = 1;

			if (*piVar6 == 0x8000)
			{
				bVar1 = true;
				piVar6 = piVar6 + 1;
			}
			else if (*piVar6 == 0x100)
			{
				piVar6 = piVar6 + 1;
				firstMissionEvent = event + cEvents;
			}

			ev_00 = event + cEvents;
			ev_00->data = piVar6;
			ev_00[1].data = piVar6 + 2;

			if (bVar1)
			{
				ev_00->position.vz = (*piVar6 + piVar6[1]) / 2;
				ev_00[1].position.vz = (piVar6[1] + piVar6[2]) / 2;
			}
			else
			{
				ev_00->position.vx = (*piVar6 + piVar6[1]) / 2;
				ev_00[1].position.vx = (piVar6[1] + piVar6[2]) / 2;
			}

			i = piVar6[3];
			piVar6 = piVar6 + 4;
			lVar3 = Random2(0);
			loop = 0;
			iVar4 = (lVar3 >> (__i & 0x1f) & 0xffU) * 0x20;
			uVar10 = __i + 1;
			ev_00 = event + cEvents;

			do {
				if (bVar1)
				{
					ev_00->flags = 1;
					ev_00->position.vx = *piVar6;
				}
				else
				{
					ev_00->flags = 0x21;
					ev_00->position.vz = *piVar6;
				}

				ev_00->node = piVar6;
				ev_00->radius = 0x1000;
				ev_00->timer = (short)iVar4 + (short)(iVar4 / 8000) * -8000;
				ev_00->model = __i * 2 + loop;
				loop = loop + 1;
				ev_00 = ev_00 + 1;
			} while (loop < 2);

			while (i--, i != -1)
			{
				piVar6++;
				VisibilityLists(VIS_ADD, cEvents | i * 0x100);
				VisibilityLists(VIS_ADD, cEvents + 1 | i * 0x100);
			}

			*e = event + cEvents;
			ev_00 = *e;
			ev_00->next = event + cEvents + 1;
			cEvents = cEvents + 2;
			e = &ev_00->next->next;
			__i = uVar10;
		}

		if (full != 0)
			ElTrackModel = FindModelIdxWithName("ELTRAIN");

		iVar5 = ElTrainData[0];
		piVar6 = ElTrainData;

		_i = 0;
		missionTrain[0].engine = event + cEvents;
		missionTrain[1].engine = missionTrain[0].engine;

		while (_i < ElTrainData[0])
		{
			piVar6 = piVar6 + 1;
			i = 5;
			if (_i != 0)
			{
				lVar3 = Random2(0);
				i = (lVar3 >> (_i & 0x1f) & 3U) + 2;
			}

			bVar1 = true;
			_i++;

			while (i = i + -1, i != -1)
			{
				ev_00 = event + cEvents;
				ev_00->radius = 0;
				ev_00->data = piVar6;

				InitTrain(ev_00, i, 0);

				if (bVar1)
				{
					bVar1 = false;
					event[cEvents].flags |= 0x400;
				}

				if (full != 0)
					event[cEvents].model = ElTrackModel;

				*e = event + cEvents;
				e = &(*e)->next;

				VisibilityLists(VIS_ADD, cEvents);

				cEvents = cEvents + 1;
			}

			i = *piVar6;

			while (1 < i + 0x80000000U)
			{
				i = piVar6[1];
				piVar6 = piVar6 + 1;
			}
		}

		fixedEvent = chicagoDoor;

		InitDoor(chicagoDoor, &e, &cEvents);
		InitDoor(chicagoDoor + 1, &e, &cEvents);

		*(FixedEvent**)e = chicagoDoor + 2;
		e = &(*e)->next;
		VisibilityLists(VIS_ADD, 130);

		if (full)
		{
			chicagoDoor[2].initialRotation = FindModelIdxWithName("HUB");
			chicagoDoor[2].minSpeed = FindModelIdxWithName("CAR");
			chicagoDoor[2].model = FindModelIdxWithName("FRAME");
			chicagoDoor[0].model = FindModelIdxWithName(chicagoDoor[0].modelName);
			chicagoDoor[1].model = FindModelIdxWithName(chicagoDoor[1].modelName);
			carModel = FindModelIdxWithName("LORRY");
		}

		multiCar.count = 0;
		multiCar.event = event + cEvents;
		iVar5 = 0;

		ev_00 = multiCar.event;
		iVar4 = 0;
		do {
			ev_00->flags = 0x680;

			if (full)
				ev_00->model = carModel;

			ev_00->radius = 0;
			ev_00->next = ev_00 + 1;

			ev_00++;
			iVar4++;
		} while (iVar4 < 7);

		cEvents = cEvents + 7;
	}
	else if (GameLevel == 1)
	{
		cameraEventsActive = 1;

		event->radius = 0;
		event->position.vy = 0x6f;
		event->position.vx = HavanaFerryData[3];
		event->position.vz = HavanaFerryData[4];;
		event->rotation = 0xc00;
		event->flags = -0x77ad;
		event->timer = -1;
		event->node = HavanaFerryData + 4;
		event->data = HavanaFerryData;

		VisibilityLists(VIS_ADD, 0);
		MakeEventTrackable(event);

		*e = event;
		fixedEvent = havanaFixed;
		e = &(*e)->next;

		InitDoor(havanaFixed, &e, &cEvents);
		InitDoor(havanaFixed + 2, &e, &cEvents);

		*(FixedEvent**)e = havanaFixed + 1;
		e = &(*e)->next;
		VisibilityLists(VIS_ADD, 129);

		event[1].flags = 0x4212;
		event[1].node = HavanaMiniData + 1;
		event[1].position.vy = 0xf9b;
		event[1].position.vx = -0x6f1ff;
		event[1].position.vz = -0x1e9ff;
		event[1].rotation = 0;
		event[1].timer = -1;
		event[1].radius = 0;
		event[1].data = HavanaMiniData;

		VisibilityLists(VIS_ADD, 1);
		*e = event + 1;
		e = &(*e)->next;
		cEvents = 2;

		if (full != 0)
		{
			event->model = FindModelIdxWithName("FERRY");
			event[1].model = FindModelIdxWithName("LIFT");

			havanaFixed[1].model = FindModelIdxWithName(havanaFixed[1].modelName);
			havanaFixed[2].model = FindModelIdxWithName(havanaFixed[2].modelName);
			havanaFixed[0].model = FindModelIdxWithName(havanaFixed[0].modelName);

			foam.model = FindModelPtrWithName("FOAM");
		}
	}
	else if (GameLevel == 2)
	{
		if (full != 0)
			trainModel = FindModelIdxWithName("TRAIN");

		iVar5 = 2;

		if (gCurrentMissionNumber == 22)
			iVar5 = 9;

		i = 0;
		piVar6 = VegasParkedTrains;

		while (i < iVar5)
		{
			piVar6++;
			ev_00 = &event[i];
			ev_00->radius = 4000;

			if (i < 2)
			{
				ev_00->flags = 0x302;
				ev_00->position.vx = VegasParkedTrains[0];
				ev_00->timer = 2;
				ev_00->position.vz = *piVar6;

				VisibilityLists(VIS_ADD, i);
			}

			ev_00->position.vy = -734;
			ev_00->rotation = 0;

			if (full != 0)
				ev_00->model = trainModel;

			*e = &event[i];
			e = &(*e)->next;

			i++;
		}
		event[iVar5 - 1].next = NULL;
		event[1].next = NULL;

		ev_00 = event;
		ev = vegasDoor;
		i = 4;

		fixedEvent = vegasDoor;
		cEvents = iVar5;

		do {
			InitDoor(ev, &e, &cEvents);
			i--;
			ev++;
		} while (-1 < i);

		if (full)
		{
			iVar5 = 0;
			do {
				vegasDoor[iVar5].model = FindModelIdxWithName(vegasDoor[iVar5].modelName);
				iVar5++;
			} while (iVar5 < 5);
		}

		ev_00 = event;

		if (gCurrentMissionNumber == 30)
		{
			event[cEvents].position.vx = -0x2ffb;
			ev_00[cEvents].position.vy = -0x113;
			ev_00[cEvents].position.vz = 0xcd61b;
			ev_00[cEvents + 1].position.vx = -0x34aa;
			ev_00[cEvents + 1].position.vy = -0xfa;
			ev_00[cEvents + 1].position.vz = 0xcd5e0;
			ev_00[cEvents + 2].position.vx = -0x382c;
			ev_00[cEvents + 2].position.vy = -0x114;
			ev_00[cEvents + 2].position.vz = 0xcd383;

			iVar5 = 0;
			do {
				if (iVar5 == 2)
					ev_00[cEvents + iVar5].rotation = 0;
				else
					ev_00[cEvents + iVar5].rotation = 0x800;

				ev_00[cEvents + iVar5].flags = 0x400;
				i = cEvents + iVar5;
				iVar5 = iVar5 + 1;
				ev_00[i].radius = 0;
			} while (iVar5 < 3);

			if (full != 0)
			{
				iVar5 = FindModelIdxWithName("DETONATOR");
				ev_00 = event;
				event[cEvents].model = iVar5;
				ev_00[cEvents + 1].model = iVar5;
				ev_00[cEvents + 2].model = iVar5;
			}

			firstMissionEvent = event + cEvents;
			cEvents = cEvents + 3;
		}
	}
	else if (GameLevel == 3)
	{
		event->radius = 0;

		if (full != 0)
		{
			iVar5 = FindModelIdxWithName("BOAT01");
			event->model = iVar5;
		}

		ev_00 = event;
		iVar5 = RioFerryData[3];
		cameraEventsActive = 1;
		(event->position).vy = 0x100;
		ev_00->position.vx = iVar5;
		iVar5 = RioFerryData[4];
		ev_00->flags = -0x77ad;
		ev_00->rotation = 0;
		ev_00->timer = -1;
		ev_00->node = RioFerryData + 4;
		ev_00->data = RioFerryData;
		ev_00->position.vz = iVar5;
		VisibilityLists(VIS_ADD, 0);
		iVar5 = 5;
		MakeEventTrackable(event);
		*e = event;
		ev = rioDoor;
		cEvents = 1;
		fixedEvent = rioDoor;
		e = &(*e)->next;

		do {
			InitDoor(ev, &e, &cEvents);
			iVar5 = iVar5 + -1;
			ev = ev + 1;
		} while (-1 < iVar5);

		if (full != 0)
		{
			iVar5 = 5;
			do {
				rioDoor[iVar5].model = FindModelIdxWithName(rioDoor[iVar5].modelName);
				iVar5--;
			} while (-1 < iVar5);

			foam.model = FindModelPtrWithName("FOAM");
			detonatorModel = FindModelIdxWithName("DETONATOR");
		}

		ev_00 = event;
		if (gCurrentMissionNumber != 0x23)
		{
			if (gCurrentMissionNumber - 0x27U < 2)
			{
				event[cEvents].flags = 0xc0;

				if (gCurrentMissionNumber == 0x27)
				{
					ev_00[cEvents].position.vx = 0xfec7;
					ev_00[cEvents].position.vy = -0x306;
					ev_00[cEvents].position.vz = -0x7ead2;
					ev_00[cEvents].rotation = 0xa40;
					ev_00[cEvents].timer = -1;
					HelicopterData.pitch = 0;
					HelicopterData.roll = 0;
				}
				else
				{
					ev_00[cEvents].position.vy = -1000;
					ev_00[cEvents].rotation = -1;
					ev_00[cEvents].timer = 0;
					ev_00[cEvents].flags = ev_00[cEvents].flags | 0x100;
				}

				lVar3 = Random2(0);
				ev_00 = event;
				HelicopterData.rotorrot = (ushort)lVar3 & 0xff;
				HelicopterData.rotorvel = 1;
				*(MS_TARGET**)&event[cEvents].node = MissionTargets + 4;
				ev_00[cEvents].radius = 0;

				if (full != 0)
				{
					HelicopterData.cleanModel = FindModelIdxWithName("CHOPPERCLEAN");
					HelicopterData.deadModel = FindModelIdxWithName("CHOPPERDAM");
					GetTextureDetails("ROTOR", &HelicopterData.rotorTexture);
				}

				event[cEvents].model = HelicopterData.cleanModel;
				VisibilityLists(VIS_ADD, cEvents);
				MakeEventTrackable(event + cEvents);
				*e = event + cEvents;
				cEvents = cEvents + 1;
				e = &(*e)->next;
			}
			goto LAB_000474bc;
		}

		event[cEvents].position.vx = 0x31330;
		ev_00[cEvents].position.vy = -0xb1;
		ev_00[cEvents].position.vz = 0x5e0e0;
		ev_00[cEvents + 1].position.vx = 0x312b0;
		ev_00[cEvents + 1].position.vy = -0xb1;
		ev_00[cEvents + 1].position.vz = 0x5f050;
		ev_00[cEvents + 2].position.vx = 0x30ad0;
		ev_00[cEvents + 2].position.vy = -0xb1;
		ev_00[cEvents + 2].position.vz = 0x5f050;

		iVar5 = 0;

		do {
			if (iVar5 == 2)
				sVar2 = 0xc00;
			else
				sVar2 = 0x400;

			event[cEvents + iVar5].rotation = sVar2;
			ev_00 = event;
			event[cEvents + iVar5].flags = 0x80;
			ev_00[cEvents + iVar5].radius = 0;
			ev_00[cEvents + iVar5].data = ev_00->data + 1;
			p_Var9 = ev_00 + cEvents + iVar5;
			iVar4 = ev_00->position.vz - (p_Var9->position).vz;
			i = ev_00->position.vy - (p_Var9->position).vy;

			piVar6 = (int*)SquareRoot0(iVar4 * iVar4 + i * i);
			if (iVar4 < 0)
			{
				piVar6 = (int*)-(int)piVar6;
			}

			p_Var9->node = piVar6;
			ev_00 = event;
			iVar5 = iVar5 + 1;
		} while (iVar5 < 3);

		if (full != 0)
		{
			event[cEvents].model = detonatorModel;
			ev_00[cEvents + 1].model = detonatorModel;
			ev_00[cEvents + 2].model = detonatorModel;
		}

		firstMissionEvent = event + cEvents;
		cEvents = cEvents + 3;
	}

LAB_000474bc:

	*e = NULL;

	if (full != 0)
		mallocptr += cEvents * sizeof(EVENT);

	MALLOC_END();
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

// [D] [T]
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

// [D] [T]
void ResetEventCamera(void)
{
	camera_position = eventCamera.position;
	camera_angle.vy = eventCamera.yAng;
	inv_camera_matrix = eventCamera.matrix;
	events.camera = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetCamera(EVENT *ev /*$s5*/)
 // line 991, offset 0x00047538
	/* begin block 1 */
		// Start line: 992
		// Start offset: 0x00047538
		// Variables:
	// 		int rotation; // $s4
	// 		int axis; // $a3
	// 		VECTOR pivot; // stack offset -96
	// 		int iPivot; // $a2
	// 		int height; // $a1
	// 		SVECTOR offset; // stack offset -80

		/* begin block 1.1 */
			// Start line: 1037
			// Start offset: 0x00047688
			// Variables:
		// 		MATRIX matrix; // stack offset -72
		// 		SVECTOR temp; // stack offset -40

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

// [D]
void SetCamera(EVENT* ev)
{
	ushort uVar1;
	short ang;
	int uVar2;
	long lVar3;
	ushort uVar4;
	int iVar5;
	VECTOR pivot;
	SVECTOR offset;
	MATRIX matrix;
	SVECTOR temp;

	offset.vx = 0;
	offset.vy = 0;
	offset.vz = 0;

	if (eventCamera.rotate != 0)
		inv_camera_matrix = eventCamera.matrix;

	pivot.vy = 0;

	if ((ev->flags & 0x800U) == 0)
	{
		uVar4 = ev->flags & 0x30;
		iVar5 = (int)ev->rotation;
		lVar3 = *ev->data;
	}
	else
	{
		lVar3 = (ev->position).vz;
		iVar5 = ev->data[1];
		offset = boatOffset;
		pivot.vy = 0x100;

		if (GameLevel == 1)
			pivot.vy = 0x6f;

		uVar4 = 0;
	}

	if (uVar4 == 0)
	{
		iVar5 = -iVar5;
		pivot.vx = camera_position.vx;
		pivot.vz = lVar3;
	}
	else
	{
		pivot.vz = camera_position.vz;
		pivot.vx = lVar3;
	}

	if (iVar5 == 0)
	{
		camera_position.vx = eventCamera.position.vx + offset.vx;
		camera_position.vy = eventCamera.position.vy + offset.vy;
		camera_position.vz = eventCamera.position.vz + offset.vz;
		camera_angle.vy = eventCamera.yAng;
	}
	else
	{
		camera_position = eventCamera.position;

		matrix.m[0][0] = 0x1000;
		matrix.m[1][0] = 0;
		matrix.m[2][0] = 0;

		matrix.m[0][1] = 0;
		matrix.m[1][1] = 0x1000;
		matrix.m[2][1] = 0;

		matrix.m[0][2] = 0;
		matrix.m[1][2] = 0;
		matrix.m[2][2] = 0x1000;

		ang = (short)iVar5;

		if (uVar4 == 0x10)
		{
			camera_angle.vy = camera_angle.vy - ang;
			_RotMatrixY(&matrix, ang);
		}
		else if (uVar4 == 0)
		{
			_RotMatrixX(&matrix, ang);
		}
		else if (uVar4 == 0x20)
		{
			_RotMatrixZ(&matrix, ang);
		}

		temp.vx = camera_position.vx - pivot.vx;
		temp.vy = camera_position.vy - pivot.vy;
		temp.vz = camera_position.vz - pivot.vz;

		gte_SetRotMatrix(&matrix);
		gte_SetTransVector(&pivot);

		gte_ldv0(&temp);

		gte_rtv0tr();

		gte_stlvnl(&camera_position);

		short v1, v0, a1, a2;

		v1 = matrix.m[0][1];
		v0 = matrix.m[1][0];
		a1 = matrix.m[0][2];
		a2 = matrix.m[2][0];
		v1 = v1 ^ v0;
		v0 = v0 ^ v1;
		v1 = v1 ^ v0;
		a1 = a1 ^ a2;
		matrix.m[0][1] = v1;
		v1 = matrix.m[1][2];
		a2 = a2 ^ a1;
		matrix.m[1][0] = v0;
		v0 = matrix.m[2][1];
		a1 = a1 ^ a2;
		matrix.m[2][0] = a2;
		matrix.m[0][2] = a1;
		v1 = v1 ^ v0;
		v0 = v0 ^ v1;
		v1 = v1 ^ v0;
		matrix.m[2][1] = v0;
		matrix.m[1][2] = v1;

		// OLD
		//gte_SetRotMatrix(&inv_camera_matrix);
		//MulRotMatrix(&matrix);
		//inv_camera_matrix = matrix;

		// NEW
		gte_MulMatrix0(&inv_camera_matrix, &matrix, &inv_camera_matrix);


		camera_position.vx += offset.vx;
		camera_position.vy += offset.vy;
		camera_position.vz += offset.vz;
	}

	SetCameraVector();

	if ((iVar5 != 0) || (eventCamera.rotate != 0))
	{
		Set_Inv_CameraMatrix();
		SetCameraVector();
		SetupDrawMapPSX();
	}

	eventCamera.rotate = iVar5;

	if ((ev->flags & 0x800U) == 0)
	{
		events.draw = ev->model;
	}
	else
	{
		ev->flags = ev->flags & 0xfffe;
		events.draw = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ EventCollisions(CAR_DATA *cp /*$a2*/, int type /*$a1*/)
 // line 1107, offset 0x0004bc50
	/* begin block 1 */
		// Start line: 1108
		// Start offset: 0x0004BC50
		// Variables:
	// 		static SVECTOR offset; // offset 0x18
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

// [D] [T]
void EventCollisions(CAR_DATA* cp, int type)
{
	if (carsOnBoat >> CAR_INDEX(cp) == 0)
		return;

	if (type == 0)
	{
		events.draw = 0;
		events.camera = 1;

		cp->hd.where.t[0] += boatOffset.vx;
		cp->hd.where.t[1] += boatOffset.vy;
		cp->hd.where.t[2] += boatOffset.vz;

		return;
	}

	cp->hd.where.t[0] -= boatOffset.vx;
	cp->hd.where.t[1] -= boatOffset.vy;
	cp->hd.where.t[2] -= boatOffset.vz;

	events.camera = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ NextNode(EVENT *ev /*$a0*/)
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

// [D] [T]
void NextNode(EVENT* ev)
{
	if (ev->node[2] == -0x7ffffffe)
	{
		ev->node = &ev->node[2];
	}
	else
	{
		ev->node = &ev->node[1];
		ev->flags ^= 0x8000;
	}

	if (*ev->node == -0x7fffffff)
	{
		ev->node = &ev->data[3];
	}
	else if (ev->node[3] == -0x80000000)
	{
		ev->flags &= ~0x7000;
		return;
	}

	ev->flags &= ~0x7000;
	ev->flags |= 0x3000;

	SetElTrainRotation(ev);
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepFromToEvent(EVENT *ev /*$a3*/)
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

// [D]
void StepFromToEvent(EVENT* ev)
{
	int uVar1;
	int uVar2;
	int uVar3;
	int iVar4;
	int iVar5;
	long* local_t0_132;
	int iVar6;
	int uVar7;
	int* piVar8;

	if (ev->timer > 0)
	{
		ev->timer--;
		return;
	}

	if (ev->timer != 0)
		return;

	uVar2 = ev->flags & 0xc000;
	piVar8 = ev->node + 1;

	if (uVar2 == 0x4000)
	{
		local_t0_132 = &(ev->position).vy;
	}
	else if (uVar2 < 0x4001)
	{
		local_t0_132 = (long*)&ev->position;

		if (uVar2 != 0)
			local_t0_132 = (long*)&ev->position;
	}
	else
	{
		if (uVar2 == 0x8000)
			local_t0_132 = &(ev->position).vz;
	}

	iVar6 = *local_t0_132;
	iVar5 = *ev->node;
	iVar4 = *piVar8;
	uVar3 = iVar6 - iVar5;
	uVar7 = iVar4 - iVar6;
	uVar2 = uVar3;

	if (uVar3 < 0)
		uVar2 = -uVar3;

	uVar1 = uVar7;

	if (uVar7 < 0)
		uVar1 = -uVar7;

	if (uVar1 < uVar2)
		uVar3 = uVar7;

	uVar2 = iVar4 - iVar5 >> 0x1f;

	if ((ev->flags & 0xc000U) == 0x4000)
	{
		if (uVar3 < 0)
			uVar3 = -uVar3;

		if (0x400 < (int)uVar3)
		{
			uVar3 = *ev->data ^ uVar2;
			goto LAB_00047b78;
		}
		iVar4 = (*ev->data + -1) * rcossin_tbl[(uVar3 & 0xfff) * 2];
	}
	else
	{
		if (uVar3 < 0)
			uVar3 = -uVar3;

		if (0x800 < uVar3)
		{
			uVar3 = *ev->data ^ uVar2;
			goto LAB_00047b78;
		}

		iVar4 = (*ev->data + -1) * (int)*(short*)((int)rcossin_tbl + ((uVar3 - (uVar3 >> 0x1f)) * 2 & 0x3ffc));
	}

	uVar3 = FIXEDH(iVar4) + 1U ^ uVar2;
LAB_00047b78:

	*local_t0_132 = iVar6 + (uVar3 - uVar2);
	iVar4 = *piVar8;

	if ((uVar7 ^ iVar4 - *local_t0_132) < 0)
	{
		*local_t0_132 = iVar4;

		ev->timer = -1;

		if (ev == events.cameraEvent)
			SpecialCamera(SPECIAL_CAMERA_RESET, 0);

	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepPathEvent(EVENT *ev /*$s0*/)
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
		// 		Station station; // $t2

			/* begin block 1.2.1 */
				// Start line: 1276
				// Start offset: 0x00047D2C
				// Variables:
			// 		int direction; // $t2
			// 		int loop; // $a2
			// 		int *i; // $a0
			// 		int turn[4]; // stack offset -48
			// 		XZPAIR centre; // stack offset -32
			// 		XZPAIR offset; // stack offset -24
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

// [D]
void StepPathEvent(EVENT* ev)
{
	static int speed;

	short* puVar1;
	short sVar2;
	ushort uVar3;
	int iVar4;
	long lVar5;
	int iVar6;
	int iVar7;
	int* piVar8;
	int iVar9;
	int* i;
	int* from;
	int iVar10;
	uint uVar11;
	int* to;
	int iVar12;
	long* curr;
	int iVar13;
	int turn[4];
	XZPAIR centre;
	XZPAIR offset;

	sVar2 = ev->timer;

	if (ev->timer != 0)
	{
		ev->timer = sVar2 + -1;

		if (sVar2 == 1)
		{
			do {
				NextNode(ev);
				puVar1 = &ev->flags;
				ev = ev->next;
				if (ev == NULL) {
					speed = 0;
					return;
				}
			} while (ev->flags == (*puVar1 & 0xfbff));
		}
		else if ((ev->flags & 0x100U) != 0)
		{
			ev->timer = sVar2;
		}

		speed = 0;
		return;
	}

	uVar3 = ev->flags;

	if ((speed == 0) && ((uVar3 & 0x400) == 0))
		return;

	from = ev->node;
	to = from + 2;

	if (*from == -0x7ffffffe)
	{
		iVar12 = 2;
		i = from + 1;
	}
	else
	{
		iVar12 = 1;
		i = from;

		if (from[2] == -0x7ffffffe)
		{
			to = from + 3;
		}
		else
		{
			iVar12 = 0;

			if (from[-1] == -0x7ffffffe)
				i = from + -2;
			else if (from[2] == -0x7fffffff)
				to = ev->data + 3;
			else if ((from[1] == -0x7fffffff) && (ev->data + 3 < to))
				to = ev->data + 4;
		}
	}

	if ((uVar3 & 0x7000) == 0x1000)
	{
		iVar12 = -1;

		if ((uVar3 & 0x8000) == 0)
		{
			iVar12 = 1;
			uVar11 = 0;
		}
		else
		{
			uVar11 = 3;
		}
		if (*from == -0x7ffffffe)
			i = from + -2;


		if (uVar11 < 4)
		{
			piVar8 = turn + uVar11;
			do {

				if (*i == -0x7fffffff)
					i = ev->data + 3;
				else if (*i == -0x7ffffffe)
					i = i + 2;

				uVar11 = uVar11 + iVar12;
				iVar4 = *i;
				i = i + 1;
				*piVar8 = iVar4;
				piVar8 = piVar8 + iVar12;
			} while (uVar11 < 4);
		}

		iVar4 = turn[2] + -0x800;

		if (-1 < turn[0] - turn[2])
			iVar4 = turn[2] + 0x800;

		iVar10 = turn[1] - 0x800;

		if (-1 < turn[3] - turn[1])
			iVar10 = turn[1] + 0x800;

		if ((ev->flags & 0x400U) != 0)
			speed = *ev->data;

		offset.x = ((ev->position).vz - iVar10) * speed;

		offset.x = offset.x >> 0xb;
		offset.z = (iVar4 - (ev->position).vx) * speed;
		offset.z = offset.z >> 0xb;

		if (((turn[2] - turn[0]) * offset.x + (turn[3] - turn[1]) * offset.z) * iVar12 < 0)
		{
			offset.x = -offset.x;
			offset.z = -offset.z;
		}

		(ev->position).vx = (ev->position).vx + offset.x;
		(ev->position).vz = (ev->position).vz + offset.z;
		lVar5 = ratan2(offset.x, offset.z);
		ev->rotation = (short)lVar5 + 0x400U & 0xfff;

		if (((int)ev->flags & 0x8000U) == 0)
		{
			iVar10 = (ev->position).vz - iVar10;

			if (turn[3] - turn[1] < 0)
			{
				if (-1 < iVar10)
					return;

			}
			else if (iVar10 < 1)
				return;

			(ev->position).vx = turn[2];
			NextNode(ev);
			return;
		}
		iVar4 = (ev->position).vx - iVar4;

		if (turn[0] - turn[2] < 0) {
			if (-1 < iVar4)
				return;

		}
		else if (iVar4 < 1)
			return;

		(ev->position).vz = turn[1];
		NextNode(ev);
		return;
	}

	curr = (long*)ev;

	if ((uVar3 & 0x8000) != 0)
		curr = &(ev->position).vz;

	iVar10 = *curr;
	iVar13 = -1;
	iVar4 = *to - iVar10;

	if (-1 < iVar4)
		iVar13 = 1;

	iVar6 = *i;
	if (iVar4 < 0)
		iVar4 = -iVar4;

	iVar9 = iVar10 - iVar6;
	if (iVar9 < 0)
		iVar9 = -iVar9;

	if (iVar4 < iVar9)
	{
		iVar7 = 2;
		iVar9 = iVar4;
	}
	else
		iVar7 = 1;

	iVar4 = iVar10 - iVar6;
	if (iVar12 == iVar7)
		iVar12 = 0;

	if (iVar9 < 0)
		iVar9 = -iVar9;

	if (iVar4 < 0)
		iVar4 = iVar6 - iVar10;

	if (iVar4 <= iVar9)
	{
		iVar9 = *curr - iVar6;
		if (iVar9 < 0)
			iVar9 = iVar6 - *curr;

	}

	if ((uVar3 & 0x400) != 0)
	{
		if ((uVar3 & 0x80) != 0)
		{
			if (CameraCnt < 0x1000)
			{
				speed = ev->data[1] * (0x1000 - CameraCnt) + ev->data[2] * CameraCnt;

				speed = FIXEDH(speed);
			}
			else
			{
				speed = ev->data[2];
			}
			//debugSpeed = speed;
		}
		speed = ev->data[1];
	}

	if (((iVar9 < 6000) || ((iVar12 == 0 && (iVar9 < 0x1f70)))) && ((ev->flags & 0x400U) != 0))
	{
		if (iVar12 == 0)
		{
			if ((ev->flags & 0x7000U) != 0x3000)
				goto LAB_00048238;
			iVar4 = (speed - *ev->data) * (int)rcossin_tbl[(((iVar9 + -0x800) * 0x400) / 0x1f70 & 0xfffU) * 2];
			uVar11 = iVar9 + -0x800 >> 0x1f;
			speed = (*ev->data ^ uVar11) - uVar11;
		}
		else
		{
			iVar4 = (speed + -5) * (int)rcossin_tbl[((iVar9 << 10) / 6000 & 0xfffU) * 2];
			speed = (iVar9 >> 0x1f ^ 5U) - (iVar9 >> 0x1f);
		}

		speed = speed + FIXEDH(iVar4);
	}
LAB_00048238:
	iVar4 = *curr + speed * iVar13;
	*curr = iVar4;

	if (iVar12 == 0)
	{
		uVar3 = ev->flags;
		if ((uVar3 & 0x7000) != 0)
		{
			if (0x7ff < (*to - iVar4) * iVar13)
				return;

			if ((uVar3 & 0x7000) == 0x3000)
			{
				ev->flags = uVar3 & 0x8fff | 0x1000;
				return;
			}

			return;
		}
	}

	if ((*to - iVar4) * iVar13 < 0)
	{
		if (iVar12 == 0)
			InitTrain(ev, 0, 0);
		else if ((ev->flags & 0x400U) != 0)
			ev->timer = 300;

	}
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

// [D] [T]
int GetBridgeRotation(int timer)
{
#ifdef CUTSCENE_RECORDER
	extern int gCutsceneAsReplay;
	if (gCutsceneAsReplay != 0)
		return 0;
#endif

	if (timer > 2600)
		return 0;

	if (timer > 1600)
		timer = 2600 - timer;
	else if (timer > 1000)
		timer = 1000;

	return (4096 - rcossin_tbl[((timer << 0xb) / 1000 & 0xfffU) * 2 + 1]) * 800 >> 0xd;
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepHelicopter(EVENT *ev /*$s0*/)
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
			// 		XZPAIR vel; // stack offset -56
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
			// 		VECTOR pos; // stack offset -48
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
		// 		VECTOR pos; // stack offset -56
		// 		VECTOR drift; // stack offset -32
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

// [D]
void StepHelicopter(EVENT* ev)
{
	static int rotating = 1;

	short uVar1;
	long lVar2;
	int iVar3;
	int uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int* piVar12;
	XZPAIR vel;
	VECTOR pos;
	VECTOR drift = { 2,3,2 };

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
	(ev->position).vx = iVar11 + ((piVar12[2] - iVar11) * iVar5 + (piVar12[4] - iVar11) * iVar10 + (piVar12[6] - iVar11) * iVar3 + 0x800 >> 0xc);
	(ev->position).vz = piVar12[1] + ((iVar6 - iVar7) * iVar5 + (iVar9 - iVar7) * iVar10 + (iVar8 - iVar7) * iVar3 + 0x800 >> 0xc);
	uVar1 = uVar1 + HelicopterData.speed;
	ev->timer = uVar1;

	if ((uVar1 << 0x10) < 0)
	{
		if ((uint)(piVar12[8] == 0) == piVar12[9])
		{
			ev->timer = -1;
		}
		else
		{
			ev->timer = 0;
			ev->node = piVar12 + 2;
		}
	}

	if (ev->rotation == -1)
	{
		piVar12 = ev->node;
		vel.x = (piVar12[4] - *piVar12) / 2;
		vel.z = (piVar12[5] - piVar12[1]) / 2;
		lVar2 = ratan2(vel.x, vel.z);
		ev->rotation = (short)lVar2;
		HelicopterData.pitch = 0;
		HelicopterData.roll = 0;
		HelicopterData.dp = 0;
		HelicopterData.dr = 0;
	}
	else
	{
		vel.x = (ev->position).vx - HelicopterData.lastX;
		vel.z = (ev->position).vz - HelicopterData.lastZ;
	}

	lVar2 = ratan2(vel.x, vel.z);
	uVar4 = ev->rotation & 0xfff;
	iVar6 = vel.z * rcossin_tbl[uVar4 * 2];
	vel.z = vel.z * rcossin_tbl[uVar4 * 2 + 1] + vel.x * rcossin_tbl[uVar4 * 2];
	vel.x = vel.x * rcossin_tbl[uVar4 * 2 + 1] - iVar6;
	iVar6 = vel.z;

	if (vel.z < 0)
		iVar6 = -vel.z;

	iVar3 = (int)HelicopterData.pitch;

	if (iVar6 < 0xdbba1)
		iVar3 = -iVar3 - ((rcossin_tbl[((vel.z * 0x400) / 900000 & 0xfffU) * 2] << 0x10) >> 0x13);
	else if (vel.z < 1)
		iVar3 = 0x200 - iVar3;
	else
		iVar3 = -0x200 - iVar3;

	iVar5 = (int)HelicopterData.roll;
	iVar6 = vel.x;

	if (vel.x < 0)
		iVar6 = -vel.x;

	if (iVar6 < 0x249f1)
		iVar5 = ((rcossin_tbl[((vel.x * 0x400) / 150000 & 0xfffU) * 2] << 0x10) >> 0x13) - iVar5;
	else if (vel.x < 1)
		iVar5 = -0x200 - iVar5;
	else
		iVar5 = 0x200 - iVar5;


	iVar8 = iVar3 - HelicopterData.dp;
	iVar6 = iVar8;
	if (iVar8 < 0)
		iVar6 = -iVar8;

	if (iVar6 < 5)
	{
		HelicopterData.dp = (short)iVar3;
	}
	else
	{
		uVar1 = (iVar8 >> 0x1f);
		HelicopterData.dp = HelicopterData.dp + ((uVar1 ^ 5) - uVar1);
	}

	iVar3 = iVar5 - HelicopterData.dr;
	iVar6 = iVar3;

	if (iVar3 < 0)
		iVar6 = -iVar3;

	if (iVar6 < 5)
	{
		HelicopterData.dr = iVar5;
	}
	else
	{
		uVar1 = (iVar3 >> 0x1f);
		HelicopterData.dr = HelicopterData.dr + ((uVar1 ^ 5) - uVar1);
	}

	HelicopterData.pitch = (HelicopterData.pitch + HelicopterData.dp + 0x800U & 0xfff) - 0x800;
	HelicopterData.roll = (HelicopterData.roll + HelicopterData.dr + 0x800U & 0xfff) - 0x800;
	iVar3 = ((lVar2 - ev->rotation) + 0x800U & 0xfff) - 0x800;
	iVar6 = iVar3;

	if (iVar3 < 0)
		iVar6 = -iVar3;

	if (iVar6 < 0x201)
	{
		iVar6 = (int)((uint) * (ushort*)((int)rcossin_tbl + (iVar3 * 8 & 0x3ff8U)) << 0x10) >> 0x12;
	}
	else
	{
		iVar6 = -0x400;
		if (0 < iVar3)
			iVar6 = 0x400;

	}

	ev->rotation = ev->rotation + (short)((iVar6 * iVar6 + 0x800 >> 0xc) * iVar6 + 0x800 >> 0xc) & 0xfff;

	if (GetSurfaceIndex((VECTOR*)ev) == -23)
	{
		iVar3 = (ev->position).vy;
		iVar6 = iVar3 + 10;

		if (iVar3 < -0x32)
		{
		LAB_000488b0:
			(ev->position).vy = iVar6;
		}
		else
		{
			pos.vy = 0;
			pos.vx = (ev->position).vx;
			pos.vz = (ev->position).vz;

			Setup_Smoke(&pos, 100, 500, 2, 0, &dummy, 0);
		}
	}
	else
	{
		iVar6 = (ev->position).vy;

		if (-1000 < iVar6)
		{
			iVar6 = iVar6 + -10;
			goto LAB_000488b0;
		}
	}

	HelicopterData.lastX = (ev->position).vx;
	HelicopterData.lastZ = (ev->position).vz;

	SetMSoundVar((int)ev, NULL);

	if (((ev->flags & 0x100U) != 0) && (uVar4 = Random2(0), (uVar4 & 3) == (CameraCnt & 3U)))
	{
		Setup_Smoke((VECTOR*)ev, 100, 500, 1, 0, &dummy, 0);
	}

LAB_00048934:
	if (ev->model == HelicopterData.deadModel)
	{
		pos.vy = -200;
		pos.vx = (ev->position).vx + (rand() & 0xff) + -0x80;
		pos.vz = (ev->position).vz + (rand() & 0xff) + -0x80;

		Setup_Smoke(&pos, 0x32, 100, 4, 0, &dummy, 0);
		Setup_Smoke(&pos, 100, 500, 1, 0, &drift, 0);
		SetMSoundVar(0, NULL);
	}
	else
	{
		HelicopterData.rotorrot = HelicopterData.rotorrot + HelicopterData.rotorvel;
		HelicopterData.rotorvel = HelicopterData.rotorvel + rotating;

		iVar6 = HelicopterData.rotorvel;
		if (iVar6 < 0)
			iVar6 = -iVar6;

		if (0x100 < iVar6)
			rotating = -rotating;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ StepEvents()
 // line 1642, offset 0x00048a60
	/* begin block 1 */
		// Start line: 1645
		// Start offset: 0x00048A60
		// Variables:
	// 		EVENT *ev; // $s0

		/* begin block 1.1 */
			// Start line: 1671
			// Start offset: 0x00048AC4
			// Variables:
		// 		VECTOR old; // stack offset -72
		// 		int onBoatLastFrame; // $s7

			/* begin block 1.1.1 */
				// Start line: 1676
				// Start offset: 0x00048ACC
				// Variables:
			// 		int dist; // stack offset -48
			// 		int loop; // $s2
			// 		CAR_DATA *cp; // $s1
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
			// 		XZPAIR speed; // stack offset -56

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
					// 		VECTOR *pos; // $a0
					// 		VECTOR *vel; // $a1
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
			// 		CELL_OBJECT *cop; // $a2
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

// [D]
void StepEvents(void)
{
	bool bVar1;
	ushort uVar2;
	EVENT* ev;
	uint uVar3;
	int i;
	int iVar4;
	ushort uVar5;
	int iVar6;
	int iVar7;
	uint uVar8;
	VECTOR* pos;
	EVENT* evt;
	VECTOR* vel;
	CELL_OBJECT* cop;
	int** ppiVar9;
	ushort* puVar10;
	ushort* puVar11;
	EVENT* _ev;
	CAR_DATA* cp;
	uint uVar12;
	int iVar13;
	long* local_s4_736;
	int onBoatLastFrame;
	VECTOR old;
	XZPAIR speed;
	int dist;

	uVar8 = carsOnBoat;
	ev = firstEvent;
	onBoatLastFrame = 0;

	if (detonator.timer != 0)
	{
		DetonatorTimer();
		uVar8 = carsOnBoat;
		ev = firstEvent;
	}

	do {
		carsOnBoat = uVar8;
		if (ev == NULL)
		{
			VisibilityLists(VIS_SORT, 0);

			if (EventCop != NULL)
			{
				event_models_active = 0;
				i = 0;

				while (i < NumPlayers)
				{
					uVar8 = 0x4000;

					if (i == 0)
					{
						uVar8 = 0x8000;
						uVar12 = 0x4000;
					}
					else
					{
						uVar12 = 0x8000;
					}

					VisibilityLists(VIS_NEXT, i);

					uVar2 = *xVis;
					puVar11 = xVis;

					i++;

					while (uVar3 = uVar2, (uVar3& uVar8) == 0)
					{
						if ((uVar3 & uVar12) == 0)
						{
							if ((uVar2 & 0x80) == 0)
								evt = &event[uVar3 & 0x7f];
							else
								evt = (EVENT*)&fixedEvent[uVar3 & 0x7f];

							if ((*(uint*)&evt->flags & 0x204) == 0x200)
							{
								uVar2 = *zVis;
								puVar10 = zVis;

								while (uVar3 = uVar2, (uVar3& uVar8) == 0)
								{
									if (((uVar3 & uVar12) == 0) && ((*puVar11 & 0xfff) == (uVar3 & 0xfff)))
									{
										cop = EventCop + event_models_active;

										cop->pos.vx = evt->position.vx;
										cop->pos.vy = evt->position.vy;
										cop->pos.vz = evt->position.vz;
										cop->yang = (evt->rotation >> 6);
										cop->type = evt->model;

										if ((*(uint*)&evt->flags & 0x12) == 2 && gCurrentMissionNumber == 22)
											cop->pad = 1;
										else
											cop->pad = 0;

										event_models_active++;
										evt->flags |= 4;
									}
									puVar10++;
									uVar2 = *puVar10;
								}
							}
						}
						puVar11++;
						uVar2 = *puVar11;
					}
				}
			}

			i = cameraDelay.delay - 1;

			if ((cameraDelay.delay != 0) && (cameraDelay.delay = i, i == 0))
			{
				SpecialCamera((enum SpecialCamera)cameraDelay.type, 1);
			}

			return;
		}

		uVar2 = ev->flags;

		if ((uVar2 & 2) == 0)
		{
			uVar5 = uVar2 & 0xcc0;

			if (uVar5 == 0x40)
			{
				if (ev->timer != 0)
				{
					ppiVar9 = &ev->data;
					if (ev->timer == 1)
						ppiVar9 = (int**)((int)&ev->data + 2);

					uVar2 = *(ushort*)ppiVar9;
					iVar4 = (int)ev->rotation;
					uVar8 = (uint) * (ushort*)&ev->data;
					i = iVar4 - uVar8;

					if (i < 0)
						i = uVar8 - iVar4;

					uVar12 = (uint) * (ushort*)((int)&ev->data + 2);
					iVar6 = uVar12 - uVar8;
					iVar13 = uVar8 - uVar12;

					if (iVar6 < 0)
						iVar6 = iVar13;

					uVar8 = (int)((uint)uVar2 - iVar4) >> 0x1f;
					i = ev->rotation +
						(((uint) * (ushort*)&ev->node +
							((int)((int)rcossin_tbl[((i * 0x800) / iVar6 & 0xfffU) * 2] *
								((uint) * (ushort*)((int)&ev->node + 2) - (uint) * (ushort*)&ev->node)) >> 0xc) ^ uVar8) - uVar8);

					ev->rotation = i;

					if ((int)((uint)uVar2 - iVar4 ^ (uint) * (ushort*)ppiVar9 - (i * 0x10000 >> 0x10)) < 0)
					{
						ev->rotation = *(ushort*)ppiVar9;
						ev->timer = 0;

						if (gCurrentMissionNumber != 30)
							SetMSoundVar(3, NULL);

						if (ev == events.cameraEvent)
							SpecialCamera(SPECIAL_CAMERA_RESET, 0);
					}
				}
			}
			else if (uVar5 < 0x41)
			{
				if ((uVar2 & 0xcc0) == 0)
				{
					i = GetBridgeRotation((int)ev->timer);

					ev->rotation = (short)i;

					if ((ev->model & 1U) != 0)
						ev->rotation = -(short)i;

					if (((ev->flags & 0x100U) == 0) || (ev->timer < 0x3e9))
					{
						i = (int)ev->timer + 1;
						ev->timer = (short)i + (short)(i / 8000) * -8000;
					}
				}
			}
			else if (uVar5 == 0xc0)
			{
				StepHelicopter(ev);
			}
			else if (uVar5 == 0x440)
			{
				if ((CameraCnt & 0x1fU) == 0)
				{
					if ((chicagoDoor[2].active & 1U) == 0)
					{
						chicagoDoor[2].active += 2;

						if (chicagoDoor[2].active == 30)
							chicagoDoor[2].active = 31;

					}
					else
					{
						chicagoDoor[2].active -= 2;

						if (chicagoDoor[2].active == -1)
							chicagoDoor[2].active = 0;
					}
				}

				chicagoDoor[2].rotation = chicagoDoor[2].rotation - chicagoDoor[2].active & 0xfff;
			}
		}
		else
		{
			if ((uVar2 & 0x40) != 0)
			{
				i = 0;
				cp = car_data;

				carsOnBoat = 0;
				do {

					if (cp->controlType != CONTROL_TYPE_NONE && OnBoat((VECTOR*)cp->hd.where.t, ev, &dist) != 0)
					{
						carsOnBoat |= 1 << i;
					}

					i++;
					cp++;
				} while (i < MAX_CARS && i < 32);

				// make Tanner on boat also
				if (player[0].playerType == 2 && OnBoat((VECTOR*)player, ev, &dist) != 0)
					carsOnBoat |= 0x300000;

				BoatOffset(&boatOffset, ev);

				old.vx = ev->position.vx;
				old.vz = ev->position.vz;

				onBoatLastFrame = uVar8;
			}

			if ((ev->flags & 0x10U) == 0)
				StepPathEvent(ev);
			else
				StepFromToEvent(ev);

			uVar8 = foam.rotate;

			if ((ev->flags & 0x800U) != 0)
			{
				uVar8 = CameraCnt & 0xff;
				ev->data[1] = (int)((uint)(ushort)rcossin_tbl[(CameraCnt & 0x7fU) * 0x40] << 0x10) >> 0x19 & 0xfff;
				ev->data[2] = (int)rcossin_tbl[uVar8 * 0x20 + 1] + 0x1000 >> 7;

				i = detonator.timer * detonator.timer;

				if (detonator.timer - 1U < 0x9f)
				{
					ev->data[1] = ev->data[1] - (rcossin_tbl[(detonator.timer & 0x3fU) * 0x80] * i >> 0x12);
					ev->data[2] = ev->data[2] - (rcossin_tbl[(detonator.timer & 0x3fU) * 0x80] * i >> 0x10);
				}

				uVar8 = foam.rotate + -1;
				if ((foam.rotate & 0xffff7fffU) == 0)
				{
					uVar8 = Random2(0);
					uVar8 = foam.rotate ^ (((int)(uVar8 & 0xf00) >> 8) + 8U | 0x8000);
				}
			}

			foam.rotate = uVar8;
			if ((ev->flags & 0x40U) != 0 && (carsOnBoat != 0 || onBoatLastFrame != 0))
			{
				iVar13 = 0;

				iVar6 = (ev->position).vx - old.vx;
				iVar4 = (ev->position).vz - old.vz;

				uVar8 = 1;
				i = 0;
				do {
					pos = (VECTOR*)car_data[i].hd.where.t;

					if (i == TANNER_COLLIDER_CARID)
					{
						pos = (VECTOR*)player[0].pos;
						vel = NULL;
					}
					else
					{
						vel = (VECTOR*)car_data[i].st.n.linearVelocity;
					}

					if ((carsOnBoat & uVar8) == 0)
					{
						if ((vel != NULL) && ((onBoatLastFrame & uVar8) != 0))
						{
							vel->vx += iVar6 * 0x1000;
							vel->vz += iVar4 * 0x1000;
						}
					}
					else
					{
						pos->vx += iVar6;
						pos->vz += iVar4;

						if (i == TANNER_COLLIDER_CARID)
						{
							SetTannerPosition((VECTOR*)pos);
							carsOnBoat = carsOnBoat & 0xffefffff;
						}
						else if ((onBoatLastFrame & uVar8) == 0)
						{
							vel->vx += iVar6 * -0x1000;
							vel->vz += iVar4 * -0x1000;
						}

						car_data[i].st.n.fposition[0] = car_data[i].hd.where.t[0] << 4;
						car_data[i].st.n.fposition[2] = car_data[i].hd.where.t[2] << 4;
					}

					uVar8 = uVar8 << 1;

					i++;
				} while (i < 21);
			}
		}
		uVar8 = carsOnBoat;
		ev = ev->next;
	} while (true);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawFerrisWheel(MATRIX *matrix /*$s0*/, VECTOR *pos /*$s1*/)
 // line 2110, offset 0x00049364
	/* begin block 1 */
		// Start line: 2111
		// Start offset: 0x00049364

		/* begin block 1.1 */
			// Start line: 2126
			// Start offset: 0x00049460
			// Variables:
		// 		int loop; // $s3
		// 		MODEL *model; // $s2
		// 		VECTOR spoke[2]; // stack offset -104

			/* begin block 1.1.1 */
				// Start line: 2138
				// Start offset: 0x000494E4
				// Variables:
			// 		VECTOR offset; // stack offset -72
			// 		VECTOR carPos; // stack offset -56
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

// [D] [T]
void DrawFerrisWheel(MATRIX* matrix, VECTOR* pos)
{
	MODEL* model;
	int loop;
	int cx, sx, angle;
	int rotation;
	VECTOR offset;
	VECTOR carPos;

	if (chicagoDoor[2].model != -1)
	{
		RenderModel(modelpointers[chicagoDoor[2].model], matrix, pos, 0, 4, 1, 0);

		if (chicagoDoor[2].model != -1)
		{
			RenderModel(modelpointers[chicagoDoor[2].initialRotation], NULL, NULL, 0, 0, 1, 0);
		}

		matrix->m[0][0] = -matrix->m[0][0];
		matrix->m[1][0] = -matrix->m[1][0];
		matrix->m[2][0] = -matrix->m[2][0];

		RenderModel(modelpointers[chicagoDoor[2].model], matrix, pos, 0, 4, 1, 0);

		if (chicagoDoor[2].minSpeed != -1)
		{
			VECTOR spoke[2] = {
				{0, 0, 2677},
				{0, 2677, 0}
			};

			rotation = 0;

			model = modelpointers[chicagoDoor[2].minSpeed];
			loop = 4;

			SetRotMatrix(&inv_camera_matrix);
			_MatrixRotate(&spoke[0]);
			_MatrixRotate(&spoke[1]);

			do {
				angle = chicagoDoor[2].rotation + rotation & 0xfff;

				cx = rcossin_tbl[angle * 2];
				sx = rcossin_tbl[angle * 2 + 1];

				offset.vx = FIXEDH(spoke[0].vx * cx + spoke[1].vx * sx);
				offset.vy = FIXEDH(spoke[0].vy * cx + spoke[1].vy * sx);
				offset.vz = FIXEDH(spoke[0].vz * cx + spoke[1].vz * sx);

				carPos.vx = pos->vx + offset.vx;
				carPos.vy = pos->vy + offset.vy;
				carPos.vz = pos->vz + offset.vz;
				gte_SetTransVector(&carPos);

				RenderModel(model, NULL, NULL, 0, 0, 1, 0);

				carPos.vx = pos->vx - offset.vx;
				carPos.vy = pos->vy - offset.vy;
				carPos.vz = pos->vz - offset.vz;

				gte_SetTransVector(&carPos);

				RenderModel(model, NULL, NULL, 0, 0, 1, 0);
				loop--;
				rotation += 410;
			} while (-1 < loop);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawRotor(VECTOR pos /*stack 0*/, MATRIX *matrix /*stack 16*/)
 // line 2159, offset 0x00049684
	/* begin block 1 */
		// Start line: 2160
		// Start offset: 0x00049684
		// Variables:
	// 		SVECTOR v[5]; // stack offset -120
	// 		MATRIX local; // stack offset -80
	// 		POLY_FT4 *poly; // $t0
	// 		TEXTURE_DETAILS *tex; // $t3
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

// [D] [T]
void DrawRotor(VECTOR pos, MATRIX* matrix)
{
	POLY_FT4* poly;
	MATRIX localMat;

	int z;
	SVECTOR v[5] = {
		{0,-470,-120},
		{1024,0,0 },
		{0,0,1024 },
		{0,0,0},
		{0,0,0},
	};

	localMat.m[0][0] = 0x1000;
	localMat.m[1][0] = 0;
	localMat.m[2][0] = 0;
	localMat.m[0][1] = 0;
	localMat.m[1][1] = 0x1000;
	localMat.m[2][1] = 0;
	localMat.m[0][2] = 0;
	localMat.m[1][2] = 0;
	localMat.m[2][2] = 0x1000;

	pos.vx -= camera_position.vx;
	pos.vy -= camera_position.vy;
	pos.vz -= camera_position.vz;

	_RotMatrixY(&localMat, HelicopterData.rotorrot & 0xfff);
	ApplyMatrixSV(matrix, v, v);
	MulMatrix0(matrix, &localMat, &localMat);
	ApplyMatrixSV(&localMat, v + 1, v + 1);
	ApplyMatrixSV(&localMat, v + 2, v + 2);

	v[0].vx += pos.vx;
	v[0].vy += pos.vy;
	v[0].vz += pos.vz;

	v[1].vx += v[0].vx;
	v[1].vy += v[0].vy;
	v[1].vz += v[0].vz;

	v[2].vx += v[0].vx;
	v[2].vy += v[0].vy;
	v[2].vz += v[0].vz;

	v[4].vx = v[0].vx - v[2].vx;
	v[4].vy = v[0].vy - v[2].vy;
	v[4].vz = v[0].vz - v[2].vz;

	v[3].vx = v[0].vx + v[4].vx;
	v[3].vy = v[0].vy + v[4].vy;
	v[3].vz = v[0].vz + v[4].vz;


	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&dummy);

	gte_ldv3(&v[0], &v[1], &v[2]);

	gte_rtpt();

	poly = (POLY_FT4*)current->primptr;

	*(ushort*)&poly->u0 = *(ushort*)&HelicopterData.rotorTexture.coords.u0;
	*(ushort*)&poly->u1 = *(ushort*)&HelicopterData.rotorTexture.coords.u1;
	*(ushort*)&poly->u2 = ((*(ushort*)&HelicopterData.rotorTexture.coords.u0 & 0xfefe) >> 1) + ((*(ushort*)&HelicopterData.rotorTexture.coords.u3 & 0xfefe) >> 1);
	*(ushort*)&poly->u3 = *(ushort*)&HelicopterData.rotorTexture.coords.u3; // [A] FIXME: might be incorrect

	poly->tpage = HelicopterData.rotorTexture.tpageid | 0x40;
	poly->clut = HelicopterData.rotorTexture.clutid;

	setPolyFT4(poly);
	setSemiTrans(poly, 1);

	poly->r0 = 127;
	poly->g0 = 127;
	poly->b0 = 127;

	gte_avsz3();

	gte_stsxy3(&poly->x2, &poly->x1, &poly->x0);

	gte_stsz(&z);
	z = z + 1000 >> 3;

	gte_ldv0(&v[3]);

	gte_rtps();

	gte_stsxy(&poly->x3);

	addPrim(current->ot + z, poly);

	current->primptr += sizeof(POLY_FT4);

	*(poly + 1) = *poly;
	poly++;

	v[3].vz = v[0].vz * 2 - v[1].vz;
	v[3].vy = v[0].vy * 2 - v[1].vy;
	v[3].vx = v[0].vx * 2 - v[1].vx;

	gte_ldv0(&v[3]);

	gte_rtps();

	gte_stsxy(&poly->x1);
	addPrim(current->ot + z, poly);

	*(ushort*)&poly->u1 = *(ushort*)&HelicopterData.rotorTexture.coords.u2;

	current->primptr += sizeof(POLY_FT4);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawEvents(int num /*stack 0*/)
 // line 2240, offset 0x00049c38
	/* begin block 1 */
		// Start line: 2241
		// Start offset: 0x00049C38
		// Variables:
	// 		unsigned short *x; // $a1
	// 		unsigned short *z; // $a0
	// 		int thisCamera; // stack offset -56
	// 		int otherCamera; // stack offset -52
	// 		static EVENT *nearestTrain; // offset 0x28
	// 		static int distanceFromNearestTrain; // offset 0x2c

		/* begin block 1.1 */
			// Start line: 2276
			// Start offset: 0x00049D14
			// Variables:
		// 		EVENT *ev; // $s1

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
				// 		MATRIX matrix; // stack offset -208
				// 		MATRIX ext; // stack offset -176
				// 		VECTOR pos; // stack offset -144
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
						// 		VECTOR shadow[4]; // stack offset -128
						// 		int loop; // $t0

							/* begin block 1.1.2.1.2.1.1 */
								// Start line: 2351
								// Start offset: 0x0004A05C
								// Variables:
							// 		XZPAIR offset; // stack offset -64
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

// [D]
void DrawEvents(int camera)
{
	static EVENT* nearestTrain; // offset 0x28
	static int distanceFromNearestTrain; // offset 0x2c

	bool bVar1;
	uint uVar2;
	ushort uVar3;
	uint uVar4;
	int local_d8;
	MATRIX* pMVar5;
	ushort* puVar7;
	int iVar8;
	int iVar9;
	ushort* _xv;
	int* piVar11;
	VECTOR* pVVar12;
	EVENT* ev;
	MATRIX matrix;
	MATRIX ext;
	VECTOR pos;
	VECTOR shadow[4];
	XZPAIR offset;
	int thisCamera;
	int otherCamera;
	int temp;

	if (CurrentPlayerView == 0)
	{
		nearestTrain = NULL;
		thisCamera = 0x8000;
		otherCamera = 0x4000;
	}
	else
	{
		thisCamera = 0x4000;
		otherCamera = 0x8000;
	}

	if (camera == 0)
	{
		SetFrustrumMatrix();
	}
	else
	{
		if (cameraEventsActive == 0)
			return;

		InitEventCamera();
	}

	VisibilityLists(VIS_NEXT, CurrentPlayerView);

	_xv = xVis;

	do {
		if ((*_xv & thisCamera) != 0)
		{
			if (camera == 0)
			{
				if (eventHaze != 0)
				{
					add_haze(eventHaze, eventHaze, 7);
				}
			}
			else
			{
				ResetEventCamera();
			}

			if (camera == 0 && (CurrentPlayerView == NumPlayers - 1) && es_mobile[0] != -1)
			{
				if (nearestTrain == NULL)
				{
					SetEnvSndVol(es_mobile[0], -10000);
				}
				else
				{
					SetEnvSndVol(es_mobile[0], 2000);
					SetEnvSndPos(es_mobile[0], nearestTrain->position.vx, nearestTrain->position.vz);
				}
			}

			return;
		}

		if ((*_xv & otherCamera) == 0)
		{
			if ((*_xv & 0x80) == 0)
				ev = &event[(*_xv & 0x7f)];
			else
				ev = (EVENT*)&fixedEvent[(*_xv & 0x7f)];

			uVar3 = ev->flags;

			if ((uVar3 & 4) == 0)
			{
				if (camera == 0)
				{
					if ((uVar3 & 1) != 1)
					{
					LAB_00049d90:
						uVar4 = *zVis;
						puVar7 = zVis;
						if ((uVar4 & thisCamera) == 0)
						{
						LAB_00049db4:
							if (((uVar4 & otherCamera) != 0) || ((*_xv & 0xfff) != (uVar4 & 0xfff)))
								break;
							ev->flags = uVar3 | 4;

							if (camera == 0)
							{
								if ((es_mobile[0] != -1) && ((uVar3 & 2) != 0))
								{
									local_d8 = (ev->position).vx;
									iVar9 = local_d8 - camera_position.vx;
									if (iVar9 < 0)
										iVar9 = camera_position.vx - local_d8;

									iVar8 = (ev->position).vz;
									local_d8 = iVar8 - camera_position.vz;

									if (local_d8 < 0)
										local_d8 = camera_position.vz - iVar8;

									if ((nearestTrain == NULL) ||
										((uint)(iVar9 + local_d8) < distanceFromNearestTrain))
									{
										nearestTrain = ev;
										distanceFromNearestTrain = iVar9 + local_d8;
									}
								}

								local_d8 = FrustrumCheck((VECTOR*)ev, (int)modelpointers[ev->model]->bounding_sphere);

								if (local_d8 != -1)
								{
									pos.vx = (ev->position).vx - camera_position.vx;
									pos.vy = (ev->position).vy - camera_position.vy;
									matrix.m[0][0] = 0x1000;
									matrix.m[1][0] = 0;
									matrix.m[2][0] = 0;
									matrix.m[0][1] = 0;
									matrix.m[1][1] = 0x1000;
									matrix.m[2][1] = 0;
									matrix.m[0][2] = 0;
									matrix.m[1][2] = 0;
									matrix.m[2][2] = 0x1000;
									pos.vz = (ev->position).vz - camera_position.vz;
									bVar1 = false;

									if ((ev->flags & 2U) == 0)
									{
										uVar3 = ev->flags & 0xcc0;

										if (uVar3 == 0x400)
											goto LAB_0004a118;

										if (uVar3 < 0x401)
										{
											if (uVar3 == 0x80)
											{
												_RotMatrixY(&matrix, ev->rotation);
												pos.vx = pos.vx - boatOffset.vx;
												pos.vz = pos.vz - boatOffset.vz;
												pos.vy = (pos.vy - boatOffset.vy) + FIXEDH((int)ev->node * (int)rcossin_tbl[(*ev->data & 0xfffU) * 2]);
											}
											else if (uVar3 != 0xc0)
											{
											LAB_0004a140:
												uVar3 = ev->flags & 0x30;
												if (uVar3 == 0x10) {
													_RotMatrixY(&matrix, ev->rotation);
												}
												else if (uVar3 < 0x11)
												{
													if ((ev->flags & 0x30U) == 0)
													{
														_RotMatrixX(&matrix, ev->rotation);
													}
												}
												else if (uVar3 == 0x20)
												{
													_RotMatrixZ(&matrix, ev->rotation);
												}
											}
										}
										else if (uVar3 == 0x440)
										{
											_RotMatrixX(&matrix, ev->rotation);
										}
										else
										{
											uVar4 = 0;

											if (uVar3 != 0x480)
												goto LAB_0004a140;

											do {
												if ((uVar4 & 1) == 0)
													offset.x = -201;
												else
													offset.x = 201;

												if ((uVar4 & 2) == 0)
													offset.z = -1261;
												else
													offset.z = 1261;

												uVar2 = ev->rotation + 0x200U & 0x400;

												iVar9 = offset.x;
												if (uVar2 != 0)
													iVar9 = offset.z;

												if (uVar2 != 0)
													offset.z = offset.x;

												shadow[uVar4].vx = (ev->position).vx + iVar9;
												shadow[uVar4].vy = 0;
												shadow[uVar4].vz = (ev->position).vz + offset.z;

												uVar4++;
											} while (uVar4 < 4);

											PlaceShadowForCar(shadow, 0, 35, 4);

										LAB_0004a118:
											_RotMatrixY(&matrix, ev->rotation);
										}
									}
									else
									{
										_RotMatrixY(&matrix, ev->rotation);
									}

									gte_SetRotMatrix(&inv_camera_matrix);

									_MatrixRotate(&pos);

									if ((ev->flags & 0xcc0U) == 0xc0)
									{
										pMVar5 = &matrix;

										if (ev->model == HelicopterData.cleanModel)
										{
											_RotMatrixZ(&matrix, HelicopterData.roll & 0xfff);
											_RotMatrixX(&matrix, HelicopterData.pitch & 0xfff);
											_RotMatrixY(&matrix, ev->rotation & 0xfff);

											DrawRotor(ev->position, &matrix);

											RenderModel(modelpointers[ev->model], &matrix, &pos, 0, 0, 1, 0);
											pos.vx = (ev->position).vx - camera_position.vx;
											pos.vy = -camera_position.vy - (ev->position).vy;
											pos.vz = (ev->position).vz - camera_position.vz;

											gte_SetRotMatrix(&inv_camera_matrix);

											_MatrixRotate(&pos);
											bVar1 = true;
										}
										else
										{
											local_d8 = 2;

											do {
												local_d8--;
												pMVar5->m[0][0] = pMVar5->m[0][0] << 1;
												pMVar5 = (MATRIX*)(pMVar5->m + 4);
											} while (-1 < local_d8); // rotation???

											_RotMatrixY(&matrix, 0xafd);
											RenderModel(modelpointers[ev->model], &matrix, &pos, 0, 0, 1, 0);
										}
									}

									if ((ev->flags & 0x800U) != 0)
									{
										_RotMatrixX(&matrix, (short)ev->data[1]);

										local_d8 = gTimeOfDay;
										pos.vy = pos.vy - ev->data[2];
										temp = combointensity;

										if ((ev->flags & 0x20U) == 0)
										{
											ev->flags = ev->flags | 1;
											if (local_d8 != 3)
											{
												bVar1 = true;
											}
										}
										else
										{
											SetupPlaneColours(0x80a0c);
										}
									}

									if (bVar1)
									{
										matrix.m[1][0] = -matrix.m[1][0];
										matrix.m[1][1] = -matrix.m[1][1];
										matrix.m[1][2] = -matrix.m[1][2];

										SetupPlaneColours(0x00464a40);

										RenderModel(modelpointers[ev->model], &matrix, &pos, 400, 2, 1, ev->rotation >> 6);
									}
									else
									{
										if ((ev->flags & 0xcc0U) == 0x440)
											DrawFerrisWheel(&matrix, &pos);
										else
											RenderModel(modelpointers[ev->model], &matrix, &pos, 0, 0, 1, ev->rotation >> 6);
									}

									if ((ev->flags & 0x800U) != 0) {
										combointensity = temp;
										matrix.m[0][0] = 0;
										matrix.m[0][1] = 0;
										matrix.m[1][0] = 0;
										matrix.m[1][1] = 0x1000;
										matrix.m[1][2] = 0;
										matrix.m[2][0] = 0x1000;
										matrix.m[2][1] = 0;
										matrix.m[2][2] = 0;

										pos.vy = pos.vy + ev->data[2];

										if ((foam.rotate & 0x8000U) == 0)
										{
											matrix.m[0][2] = -0x1000;
										}
										else
										{
											matrix.m[0][2] = 0x1000;
										}

										if (gTimeOfDay != 1)
										{
											SetupPlaneColours(0x00282828);
										}

										if ((foam.rotate & 0x8000U) == 0)
											local_d8 = 1;
										else
											local_d8 = 3;

										RenderModel(foam.model, &matrix, &pos, 200, local_d8, 1, 0);
										SetupPlaneColours(combointensity);
									}
								}
							}
							else
							{
								SetCamera(ev);
								DrawMapPSX(&ObjectDrawnValue);
							}
						}
					}
				}
				else
				{
					if ((uVar3 & 1) != 0)
						goto LAB_00049d90;
				}
			}
		}
	LAB_0004a58c:
		_xv++;
	} while (true);

	uVar4 = (uint)puVar7[1];
	puVar7 = puVar7 + 1;

	if ((uVar4 & thisCamera) != 0)
		goto LAB_0004a58c;

	goto LAB_00049db4;
}



// decompiled code
// original method signature: 
// void /*$ra*/ BoatOffset(SVECTOR *offset /*$a0*/, EVENT *ev /*$a1*/)
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

// [D] [T]
void BoatOffset(SVECTOR* offset, EVENT* ev)
{
	offset->vx = 0;
	offset->vy = -ev->data[2];
	offset->vz = ev->data[4] - ev->position.vz;
}



// decompiled code
// original method signature: 
// int /*$ra*/ OnBoat(VECTOR *pos /*$t1*/, EVENT *ev /*$a1*/, int *dist /*$a2*/)
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

// [D] [T]
int OnBoat(VECTOR* pos, EVENT* ev, int* dist)
{
	int halfBoatLength;
	int halfBoatWidth;

	if (GameLevel == 1)
	{
		halfBoatWidth = 853;
		halfBoatLength = 2431;
	}
	else
	{
		halfBoatWidth = 1600;
		halfBoatLength = 5376;
	}


	if (ev->position.vx - halfBoatWidth < pos->vx && 
		ev->position.vx + halfBoatWidth > pos->vx)
	{
		*dist = pos->vz - ev->position.vz;
			
		if (*dist > -halfBoatLength && *dist < halfBoatLength)
		{
			return 1;
		}
	}

	return 0;

}



// decompiled code
// original method signature: 
// sdPlane * /*$ra*/ EventSurface(VECTOR *pos /*$a0*/, sdPlane *plane /*$s1*/)
 // line 2560, offset 0x0004a688
	/* begin block 1 */
		// Start line: 2561
		// Start offset: 0x0004A688
		// Variables:
	// 		EVENT *ev; // $s0
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

int debugOffset = 0;

// [D]
sdPlane* EventSurface(VECTOR* pos, sdPlane* plane)
{
	short uVar1;
	int* piVar2;
	int uVar3;
	short sVar4;
	int iVar5;
	int uVar6;
	int iVar7;
	int iVar8;
	EVENT* ev;
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
				return GetSeaPlane();
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
						return GetSeaPlane();
					}

					uVar6 = (iVar8 - (FIXEDH(iVar5 * 3328) + ev->data[2] + ev->position.vy)) + (FIXEDH(iVar7) * rcossin_tbl[uVar3 * 2]) / iVar9;
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
				return GetSeaPlane();
			}
			goto LAB_0004a880;
		}

		if (GameLevel != 0)
			return GetSeaPlane();

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
// void /*$ra*/ MakeEventTrackable(EVENT *ev /*$a0*/)
 // line 2684, offset 0x0004bd6c
	/* begin block 1 */
		// Start line: 2685
		// Start offset: 0x0004BD6C
		// Variables:
	// 		EVENT **p; // $v1
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

// [D] [T]
void MakeEventTrackable(EVENT* ev)
{
	EVENT** p;

	p = trackingEvent;
	while (*p)
		p++;

	*p = ev;
	p[1] = NULL;	// WTF?
}



// decompiled code
// original method signature: 
// void /*$ra*/ TriggerDoor(FixedEvent *door /*$a3*/, int *stage /*$a1*/, int sound /*$a2*/)
 // line 2696, offset 0x0004c208
	/* begin block 1 */
		// Start line: 11604
	/* end block 1 */
	// End Line: 11605

	/* begin block 2 */
		// Start line: 12825
	/* end block 2 */
	// End Line: 12826

// [D] [T]
void TriggerDoor(FixedEvent* door, int* stage, int sound)
{
	if (*stage == 0)
	{
		if ((door->flags & 0x30) != 0x10)
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
// VECTOR * /*$ra*/ TriggerEvent(int i /*$s4*/)
 // line 2718, offset 0x0004aa78
	/* begin block 1 */
		// Start line: 2719
		// Start offset: 0x0004AA78
		// Variables:
	// 		static int stage[10]; // offset 0x200
	// 		VECTOR *pos; // $s7

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
		// 		EVENT *ev; // $a2
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
			// 		MissionTrain *train; // $s1

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
				// 		EVENT *ev; // $s0
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
			// 		EVENT *ev; // $v1
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

// [D]
VECTOR* TriggerEvent(int i)
{
	static int stage[10];

	short uVar1;
	EVENT* p_Var2;
	int count;
	int* piVar3;
	int iVar4;
	EVENT* _ev;
	int iVar5;
	EVENT* p_Var6;
	EVENT* ev;
	int iVar7;
	EVENT* ev_00;

	p_Var2 = firstEvent;
	p_Var6 = firstMissionEvent;
	ev = event;
	ev_00 = NULL;

	if (i == -1) // initialize
	{
		count = 9;
		piVar3 = stage + 9;

		do {
			*piVar3 = 0;
			count--;
			piVar3--;
		} while (-1 < count);

		return NULL;
	}

	if (GameLevel > 1 && i > 0 && i < 4) // Vegas and Rio detonators
	{
		if (stage[i] == 0)
		{
			p_Var6 = firstMissionEvent + i - 1;

			p_Var6->next = firstEvent->next;
			p_Var2->next = p_Var6;

			VisibilityLists(VIS_ADD, p_Var6 - event);
			SetMSoundVar(i, NULL);

			detonator.count++;
		}

		goto switchD_0004afa0_caseD_1;
	}

	if (GameLevel == 0)
	{
		switch (i)
		{
			case 0:
			case 1:
				if (stage[i] == 0)
				{
					ev_00 = missionTrain[i].engine;
					MakeEventTrackable(ev_00);
					ev_00->flags = ev_00->flags | 0x180;
					count = -0x640;

					if (-1 < *missionTrain[i].node - missionTrain[i].start)
						count = 0x640;

					iVar7 = 0;
					ev = ev_00;
					do {
						piVar3 = missionTrain[i].node;

						if (*piVar3 == -0x7ffffffe)
							iVar5 = piVar3[-1];
						else
							iVar5 = piVar3[1];

						if (missionTrain[i].startDir == 0x8000)
						{
							uVar1 = ev->flags;
							(ev->position).vx = iVar5;
							ev->flags = uVar1 | 0x8000;
							(ev->position).vz = missionTrain[i].start + iVar7 * count;
						}
						else
						{
							ev->flags = ev->flags & 0x7fff;
							iVar4 = missionTrain[i].start;
							(ev->position).vz = iVar5;
							(ev->position).vx = iVar4 + iVar7 * count;
						}

						piVar3 = missionTrain[i].node;
						ev->data = &missionTrain[i].cornerSpeed;
						ev->timer = 0;
						ev->node = piVar3;
						ev->flags = ev->flags & 0x8fffU | 0x3000;

						SetElTrainRotation(ev);

						iVar7 = iVar7 + 1;
					} while ((ev->next != NULL) && (ev = ev->next, (ev->flags & 0x400U) == 0));
				}
				else
				{
					ev_00 = missionTrain[i].engine;

					if (ev_00->timer != 0)
						ev_00->timer = 1;

				}
				break;
			case 2:
			case 3:
			case 4:
				if (stage[i] == 0)
				{
					count = 9;
					ev = firstMissionEvent;
					do {
						p_Var6 = ev;
						p_Var6->flags = p_Var6->flags | 0x100;

						if (i == 4)
							p_Var6->timer = 0xa28;
						else
							p_Var6->timer = 1000;

						count--;
						ev = p_Var6 + 1;
					} while (-1 < count);

					if (i == 2)
					{
						p_Var6[-1].timer = 0xa28;
						p_Var6->timer = 0xa28;
					}
				}
				else
				{
					firstMissionEvent[8].timer = 0;
					p_Var6[9].timer = 0;
				}

				break;
			case 5:
				PrepareSecretCar();
				events.cameraEvent = (EVENT*)chicagoDoor;
			case 6:
				TriggerDoor(chicagoDoor + i - 5, stage + i, 1); // might be incorrect
		}
	}
	else if (GameLevel == 1)
	{
		switch (i)
		{
			case 0:
				event->timer = 1;
				break;
			case 1:
				(event->position).vx = HavanaFerryData[9];
				count = HavanaFerryData[10];
				ev->timer = 1;
				ev->node = HavanaFerryData + 10;
				ev->data = HavanaFerryData + 6;
				(ev->position).vz = count;
				break;
			case 2:
				TriggerDoor(havanaFixed, stage + i, 1);
				break;
			case 3:
				PrepareSecretCar();
				events.cameraEvent = (EVENT*)(havanaFixed + 2);
				TriggerDoor(havanaFixed + 2, stage + i, 0);
				break;
			case 4:
				if (stage[i] != 0)
				{
					SpecialCamera(SPECIAL_CAMERA_WAIT, 0);
					event[1].node = event[1].node + 1;
				}

				ev = event;
				event[1].timer = 0;
				events.cameraEvent = ev + 1;
		}
	}
	else if (GameLevel == 2)
	{
		switch (i)
		{
			case 0:
				count = 0;

				do {
					ev = &event[count];

					ev->data = VegasTrainData;
					InitTrain(ev, count, 1);
					ev->flags |= 0x200;

					if (count > 1)
						VisibilityLists(VIS_ADD, count);

					count++;
				} while (count < 9);

				event->flags |= 0x500;

				MakeEventTrackable(ev);

				event[1].next = event + 2;
				break;
			case 4:
				TriggerDoor(vegasDoor + i - 4, stage + i, 0);
				break;
			case 8:
				events.cameraEvent = (EVENT*)(vegasDoor + 4);
				PrepareSecretCar();
			case 5:
			case 6:
			case 7:
				TriggerDoor(vegasDoor + i - 4, stage + i, 1);
				break;
			case 9:
				SetMSoundVar(5, NULL);
		}
	}
	else if (GameLevel == 3)
	{
		switch (i)
		{
			case 0:
				event->timer = 1;
				break;
			case 4:
				TriggerDoor(rioDoor + 2, stage + i, 0);
				TriggerDoor(rioDoor + 3, stage + i, 0);

				events.cameraEvent = (EVENT*)(rioDoor + 2);
				break;
			case 5:
			case 6:
				TriggerDoor(rioDoor + i - 5, stage + i, (i == 5));
				break;
			case 7:
				if (stage[i] == 0)
				{
					ev_00 = event + 1;
				}
				else
				{
					event[1].position.vy = -0x11;
					ev[1].position.vx = -0x3afd3;
					ev[1].position.vz = -0x33e9e;
					ev[1].timer = -2;
					ev[1].model = HelicopterData.deadModel;
				}

				break;
			case 8:
				PingOutAllSpecialCivCars();
				TriggerDoor(rioDoor + 4, stage + i, 0);
				TriggerDoor(rioDoor + 5, stage + i, 0);
				events.cameraEvent = (EVENT*)(rioDoor + 4);
		}
	}

switchD_0004afa0_caseD_1:

	if (i < 10)
		stage[i]++;

	return (VECTOR*)&ev_00->position;
}



// decompiled code
// original method signature: 
// void /*$ra*/ OffsetTarget(VECTOR *target /*$a0*/)
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

// [D] [T]
void OffsetTarget(VECTOR* target)
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
			events.cameraEvent = (EVENT*)0x1;
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
				events.cameraEvent = (EVENT*)0x1;
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
// void /*$ra*/ ScreenShake(int count /*$a0*/, SVECTOR *ang /*$s0*/)
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

// [D] [T]
void ScreenShake(int count, SVECTOR* ang)
{
	eventHaze = count * 4;

	camera_angle.vx = (ang->vx + (Random2(0) % (eventHaze / 2))) - eventHaze;
	camera_angle.vy = (ang->vy + (Random2(0) % (eventHaze * 2))) - eventHaze;

	eventHaze *= 3;
}



// decompiled code
// original method signature: 
// int /*$ra*/ DetonatorTimer()
 // line 3152, offset 0x0004b5fc
	/* begin block 1 */
		// Start line: 3154
		// Start offset: 0x0004B5FC
		// Variables:
	// 		static SVECTOR rememberCameraAngle; // offset 0x30

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
				// 		VECTOR pos; // stack offset -32
				/* end block 1.1.1.1 */
				// End offset: 0x0004B700
				// End Line: 3184

				/* begin block 1.1.1.2 */
					// Start line: 3188
					// Start offset: 0x0004B720
					// Variables:
				// 		VECTOR pos; // stack offset -32
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
		// 		EVENT *ev; // $s0
		// 		VECTOR pos; // stack offset -32

			/* begin block 1.2.1 */
				// Start line: 3247
				// Start offset: 0x0004B9B0
				// Variables:
			// 		VECTOR *epicentre; // $v1
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

// [D]
int DetonatorTimer(void)
{
	static SVECTOR rememberCameraAngle; // offset 0x30
	static int count = 0; // offset 0x38

	long* plVar1;
	EVENT* _ev;
	int cnt;
	EVENT* ev;
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
			if (detonator.timer - 0x1fU > 8)
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
				events.cameraEvent = (EVENT*)0x1;

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
// void /*$ra*/ MultiCarEvent(MS_TARGET *target /*$a0*/)
 // line 3288, offset 0x0004bab0
	/* begin block 1 */
		// Start line: 3289
		// Start offset: 0x0004BAB0
		// Variables:
	// 		MULTICAR_DATA *data; // $s0
	// 		int i; // $s1
	// 		EVENT *ev; // $s2

		/* begin block 1.1 */
			// Start line: 3301
			// Start offset: 0x0004BAF8
			// Variables:
		// 		int num; // $a1
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

// [D] [T]
void MultiCarEvent(MS_TARGET* target)
{
	EVENT* first;
	int n;
	EVENT* ev;
	MULTICAR_DATA* data;
	int i;

	first = firstEvent;

	data = (MULTICAR_DATA*)(target->data + 1);

	firstEvent = multiCar.event + multiCar.count;
	n = target->data[1];

	i = 0;
	while (n != -0x80000000)
	{
		n = (multiCar.event - event) + multiCar.count;

		ev = event + n;

		ev->position.vx = data->x;
		ev->position.vy = -312;
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

	//firstEvent->next = first; // [A] bug fix
	multiCar.event[multiCar.count - 1].next = first;
}





