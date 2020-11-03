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

#define STATION_NODE_0	0x80000000	// -0x80000000
#define STATION_NODE_1	0x80000001	// -0x7fffffff
#define STATION_NODE_2	0x80000002	// -0x7ffffffe

// TODO: put more meaning into those arrays

int ElTrainData[83] = {
	6, 80, 130, 32768, 336284, -220364, 283420, STATION_NODE_2,
	-204500, -158924, 247580, -123084, 188624, -158924, 73520, -138444, 17200, -124148, -39120, STATION_NODE_2,
	-109276, -82131, -80103, -17628, -203568, -124712, -39728, -265000, 129620, -386012, STATION_NODE_0,
	80, 130, 0, -158928, 189219, -123684, 246995, STATION_NODE_1,
	0, 90, 32768, 188402, -425768, 354291, STATION_NODE_0,
	0, 90, 32768, 354291, -425168, 188402, STATION_NODE_0,
	60, 110, 0, -386012, 130215, -264404, -39132, -124688, 16619, -139048, 72943, -159520, 282863, STATION_NODE_2,
	-204991, -220964, 336284, STATION_NODE_0,
	70, 120, 0, -82719, -39712, STATION_NODE_2,
	-115487, -124120, -202968,-18216, -80683, STATION_NODE_1
};

int VegasTrainData[7] = {
	0, 123, 32768, 982000, -68855, 762717, STATION_NODE_0
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
	1, 247296, -256512, -249344, -242176,
	1, 247296, -262656, -255488, -248320,
	1, 324096, 32768, 170496, 177664, 184832,
	1, -271360, -12800, -5632, 1536,
	5, -162304, -102912, -82432, -61952, -39936, -6656, 512, 7680,
	3, 4137, 27648, 128000
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

			if ((ev->flags & 0xCC0) == 0x80)
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

// [D] [T]
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
	int n, j, vis;
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
				vis = GetVisValue(list[num][j], num);

				table[j] = vis;

				// add sorted
				// code is similar to sorting code in DrawAllTheCars
				if (j > 0 && vis < table[j - 1])
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
					} while (vis < table[k]);

					table[n] = vis;
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
		ev->rotation = 1024;
	else
		ev->rotation = 0;

	if (ev->node[0] < ev->node[2])
		ev->rotation += 2048;
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
	int mv;
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

	if (ev->node[3] != STATION_NODE_0)
		ev->flags |= 0x3000;

	to = ev->node;

	// get direction sign
	if (to[2] == STATION_NODE_2)
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

#ifdef PSX
#define EVENT_RADIUS 4096
#else
#define EVENT_RADIUS 12000
#endif

// [D] [T] [A] long function, please debug more
void SetUpEvents(int full)
{

	int direction;
	int i, n;
	int* p;
	EVENT* evt;

	int detonatorModel;
	int trainModel;

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
			EventCop = (CELL_OBJECT*)D_MALLOC(sizeof(CELL_OBJECT) * 16);
			event = (EVENT*)mallocptr;
		}

	evt = event;
	cEvents = 0;	// TODO: use D_MALLOC for each event?

	if (GameLevel == 0)
	{
		int count;
		int cBridges;

		cBridges = LiftingBridges[0];

		direction = 0;
		p = &LiftingBridges[1];

		// make lifting bridges
		n = 0;
		while (n < cBridges)
		{
			int timeOffset;
			cameraEventsActive = 1;

			if (p[0] == 0x8000)
			{
				direction = true;
				p++;
			}
			else if (p[0] == 0x100)
			{
				firstMissionEvent = &event[cEvents];
				p++;
			}

			evt = &event[cEvents];

			evt[0].data = &p[0];
			evt[1].data = &p[2];

			if (direction)
			{
				evt[0].position.vz = (p[0] + p[1]) / 2;
				evt[1].position.vz = (p[1] + p[2]) / 2;
			}
			else
			{
				evt[0].position.vx = (p[0] + p[1]) / 2;
				evt[1].position.vx = (p[1] + p[2]) / 2;
			}

			count = p[3];
			p += 4;

			// randomize the timer of bridges
			timeOffset = (Random2(0) >> (n & 31) & 255) * 32;

			evt = &event[cEvents];
			for (i = 0; i < 2; i++)
			{
				if (direction)
				{
					evt[i].flags = 1;
					evt[i].position.vx = *p;
				}
				else
				{
					evt[i].flags = 0x21;
					evt[i].position.vz = *p;
				}

				evt[i].node = p;
				evt[i].radius = EVENT_RADIUS;
				evt[i].timer = timeOffset % 8000;
				evt[i].model = n * 2 + i;
			}

			while (--count >= 0)
			{
				VisibilityLists(VIS_ADD, cEvents | count * 256);
				VisibilityLists(VIS_ADD, cEvents + 1 | count * 256);
				p++;
			}

			*e = &event[cEvents];

			evt = *e;
			evt->next = &event[cEvents + 1];

			cEvents += 2;

			e = &evt->next->next;
			n++;
		}

		if (full)
			ElTrackModel = FindModelIdxWithName("ELTRAIN");

		count = ElTrainData[0];
		p = ElTrainData;

		n = 0;
		missionTrain[0].engine = &event[cEvents];
		missionTrain[1].engine = missionTrain[0].engine;

		// add trains
		while (n < count)
		{
			if (n != 0)
				i = (Random2(0) >> (n & 0x1f) & 3U) + 2;
			else
				i = 5;

			direction = 1;
			n++;
			p++;

			while (--i >= 0)
			{
				evt = &event[cEvents];
				evt->radius = 0;
				evt->data = p;

				InitTrain(evt, i, 0);

				if (direction)
				{
					direction = 0;
					evt->flags |= 0x400;
				}

				if (full)
					evt->model = ElTrackModel;

				*e = evt;
				e = &(*e)->next;

				VisibilityLists(VIS_ADD, cEvents);

				cEvents++;
			}

			i = *p;

			do
			{
				i = p[1];
				p++;
			} while (i + STATION_NODE_0 > 1);
		}

		fixedEvent = chicagoDoor;

		InitDoor(&chicagoDoor[0], &e, &cEvents);
		InitDoor(&chicagoDoor[1], &e, &cEvents);

		*e = (EVENT*)&chicagoDoor[2];
		e = &(*e)->next;

		VisibilityLists(VIS_ADD, 130);

		if (full)
		{
			// these models are for ferris wheel
			chicagoDoor[2].initialRotation = FindModelIdxWithName("HUB");
			chicagoDoor[2].minSpeed = FindModelIdxWithName("CAR");
			chicagoDoor[2].model = FindModelIdxWithName("FRAME");
			chicagoDoor[0].model = FindModelIdxWithName(chicagoDoor[0].modelName);
			chicagoDoor[1].model = FindModelIdxWithName(chicagoDoor[1].modelName);

			// Caine's compund semi model
			carModel = FindModelIdxWithName("LORRY");
		}

		// Caine's compound trucks
		multiCar.count = 0;
		multiCar.event = &event[cEvents];

		evt = multiCar.event;
		for (i = 0; i < 7; i++)
		{
			evt[i].flags = 0x680;

			if (full)
				evt[i].model = carModel;

			evt[i].radius = 0;
			evt[i].next = &evt[i + 1];
		}

		cEvents += 7;
	}
	else if (GameLevel == 1)
	{
		evt = event;

		cameraEventsActive = 1;

		evt->radius = 0;
		evt->position.vy = 111;
		evt->position.vx = HavanaFerryData[3];
		evt->position.vz = HavanaFerryData[4];;
		evt->rotation = 3072;
		evt->flags = -0x77ad;
		evt->timer = -1;
		evt->node = HavanaFerryData + 4;
		evt->data = HavanaFerryData;

		VisibilityLists(VIS_ADD, 0);
		MakeEventTrackable(evt);

		*e = evt;
		fixedEvent = havanaFixed;
		e = &(*e)->next;

		InitDoor(havanaFixed, &e, &cEvents);
		InitDoor(havanaFixed + 2, &e, &cEvents);

		*e = (EVENT*)(&havanaFixed[1]);
		e = &(*e)->next;

		VisibilityLists(VIS_ADD, 129);

		evt[1].flags = 0x4212;
		evt[1].node = HavanaMiniData + 1;
		evt[1].position.vy = 3995;
		evt[1].position.vx = -455167;
		evt[1].position.vz = -125439;
		evt[1].rotation = 0;
		evt[1].timer = -1;
		evt[1].radius = 0;
		evt[1].data = HavanaMiniData;

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
		int cCarriages;

		if (full)
			trainModel = FindModelIdxWithName("TRAIN");

		evt = event;

		// in Beat the train we spawn more train cars
		if (gCurrentMissionNumber == 22)
			cCarriages = 9;
		else
			cCarriages = 2;

		for (i = 0; i < cCarriages; i++)
		{
			evt[i].radius = EVENT_RADIUS;

			if (i < 2)
			{
				evt[i].flags = 0x302;
				evt[i].position.vx = VegasParkedTrains[0];
				evt[i].position.vz = VegasParkedTrains[i + 1];
				evt[i].timer = 2;

				VisibilityLists(VIS_ADD, i);
			}

			evt[i].position.vy = -734;
			evt[i].rotation = 0;

			if (full)
				evt[i].model = trainModel;

			*e = &evt[i];
			e = &(*e)->next;
		}

		// zero first and last train links
		evt[cCarriages - 1].next = NULL;
		evt[1].next = NULL;

		cEvents = cCarriages;

		fixedEvent = vegasDoor;
		for (i = 0; i < 5; i++)
		{
			InitDoor(&vegasDoor[i], &e, &cEvents);

			if (full)
				vegasDoor[i].model = FindModelIdxWithName(vegasDoor[i].modelName);
		}

		if (gCurrentMissionNumber == 30)
		{
			// Destroy the yard
			evt[cEvents].position.vx = -12283;
			evt[cEvents].position.vy = -275;
			evt[cEvents].position.vz = 841243;

			evt[cEvents + 1].position.vx = -13482;
			evt[cEvents + 1].position.vy = -250;
			evt[cEvents + 1].position.vz = 841184;

			evt[cEvents + 2].position.vx = -14380;
			evt[cEvents + 2].position.vy = -276;
			evt[cEvents + 2].position.vz = 840579;

			i = 0;
			for (i = 0; i < 3; i++)
			{
				if (i == 2)
					evt[cEvents + i].rotation = 0;
				else
					evt[cEvents + i].rotation = 2048;

				evt[cEvents + i].flags = 0x400;
				evt[cEvents + i].radius = 0;
			}

			if (full)
			{
				detonatorModel = FindModelIdxWithName("DETONATOR");

				evt[cEvents].model = detonatorModel;
				evt[cEvents + 1].model = detonatorModel;
				evt[cEvents + 2].model = detonatorModel;
			}

			firstMissionEvent = &event[cEvents];
			cEvents += 3;
		}
	}
	else if (GameLevel == 3)
	{
		evt = event;

		cameraEventsActive = 1;

		if (full != 0)
			evt->model = FindModelIdxWithName("BOAT01");

		evt->radius = 0;
		evt->position.vy = 256;
		evt->position.vx = RioFerryData[3];
		evt->position.vz = RioFerryData[4];
		evt->flags = -0x77ad;
		evt->rotation = 0;
		evt->timer = -1;
		evt->node = RioFerryData + 4;
		evt->data = RioFerryData;

		VisibilityLists(VIS_ADD, 0);

		MakeEventTrackable(event);
		*e = event;

		cEvents = 1;
		fixedEvent = rioDoor;
		e = &(*e)->next;

		for (i = 0; i < 6; i++)
		{
			InitDoor(&rioDoor[i], &e, &cEvents);

			if (full)
				rioDoor[i].model = FindModelIdxWithName(rioDoor[i].modelName);
		}

		if (full)
		{
			foam.model = FindModelPtrWithName("FOAM");
			detonatorModel = FindModelIdxWithName("DETONATOR");
		}

		evt = event;
		if (gCurrentMissionNumber == 35)
		{
			// setup bombs on Boat Jump
			int dz, dy;

			evt[cEvents].position.vx = 201520;
			evt[cEvents].position.vy = -177;
			evt[cEvents].position.vz = 385248;

			evt[cEvents + 1].position.vx = 201392;
			evt[cEvents + 1].position.vy = -177;
			evt[cEvents + 1].position.vz = 389200;

			evt[cEvents + 2].position.vx = 199376;
			evt[cEvents + 2].position.vy = -177;
			evt[cEvents + 2].position.vz = 389200;

			for (i = 0; i < 3; i++)
			{
				if (i == 2)
					evt[cEvents + i].rotation = 3072;
				else
					evt[cEvents + i].rotation = 1024;

				evt[cEvents + i].flags = 0x80;
				evt[cEvents + i].radius = 0;
				evt[cEvents + i].data = &evt->data[1];

				dz = evt->position.vz - evt[cEvents + i].position.vz;
				dy = evt->position.vy - evt[cEvents + i].position.vy;

				evt[cEvents + i].node = (int*)ABS(SquareRoot0(dz * dz + dy * dy));
			}

			if (full != 0)
			{
				evt[cEvents].model = detonatorModel;
				evt[cEvents + 1].model = detonatorModel;
				evt[cEvents + 2].model = detonatorModel;
			}

			firstMissionEvent = &event[cEvents];
			cEvents += 3;
		}
		else if (gCurrentMissionNumber - 39U < 2)
		{
			// setup Lenny helicopter
			evt[cEvents].flags = 0xC0;

			if (gCurrentMissionNumber == 39)
			{
				evt[cEvents].position.vx = 65223;
				evt[cEvents].position.vy = -774;
				evt[cEvents].position.vz = -518866;
				evt[cEvents].rotation = 2624;
				evt[cEvents].timer = -1;

				HelicopterData.pitch = 0;
				HelicopterData.roll = 0;
			}
			else
			{
				evt[cEvents].position.vy = -1000;
				evt[cEvents].rotation = -1;
				evt[cEvents].timer = 0;
				evt[cEvents].flags |= 0x100;
			}

			HelicopterData.rotorrot = Random2(0) & 0xff;
			HelicopterData.rotorvel = 1;

			evt[cEvents].node = (int*)&MissionTargets[4];
			evt[cEvents].radius = 0;

			if (full)
			{
				HelicopterData.cleanModel = FindModelIdxWithName("CHOPPERCLEAN");
				HelicopterData.deadModel = FindModelIdxWithName("CHOPPERDAM");
				GetTextureDetails("ROTOR", &HelicopterData.rotorTexture);
			}

			evt[cEvents].model = HelicopterData.cleanModel;
			VisibilityLists(VIS_ADD, cEvents);
			MakeEventTrackable(event + cEvents);

			*e = &evt[cEvents++];

			e = &(*e)->next;
		}
	}

	*e = NULL;

	if (full)
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

// [D] [T]
void SetCamera(EVENT* ev)
{
	int iPivot;
	int axis;
	int rotation;
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

	if (ev->flags & 0x800)
	{
		iPivot = ev->position.vz;
		rotation = ev->data[1];

		offset = boatOffset;

		if (GameLevel == 1)
			pivot.vy = 111;
		else
			pivot.vy = 256;

		axis = 0;
	}
	else
	{
		axis = ev->flags & 0x30;

		rotation = ev->rotation;
		iPivot = *ev->data;
	}

	if (axis == 0)
	{
		rotation = -rotation;

		pivot.vx = camera_position.vx;
		pivot.vz = iPivot;
	}
	else
	{
		pivot.vz = camera_position.vz;
		pivot.vx = iPivot;
	}

	if (rotation == 0)
	{
		camera_position.vx = eventCamera.position.vx + offset.vx;
		camera_position.vy = eventCamera.position.vy + offset.vy;
		camera_position.vz = eventCamera.position.vz + offset.vz;
		camera_angle.vy = eventCamera.yAng;
	}
	else
	{
		camera_position = eventCamera.position;

		matrix.m[0][0] = ONE;
		matrix.m[1][0] = 0;
		matrix.m[2][0] = 0;

		matrix.m[0][1] = 0;
		matrix.m[1][1] = ONE;
		matrix.m[2][1] = 0;

		matrix.m[0][2] = 0;
		matrix.m[1][2] = 0;
		matrix.m[2][2] = ONE;

		if (axis == 0x10)
		{
			camera_angle.vy = camera_angle.vy - rotation;
			_RotMatrixY(&matrix, rotation);
		}
		else if (axis == 0)
		{
			_RotMatrixX(&matrix, rotation);
		}
		else if (axis == 0x20)
		{
			_RotMatrixZ(&matrix, rotation);
		}

		temp.vx = camera_position.vx - pivot.vx;
		temp.vy = camera_position.vy - pivot.vy;
		temp.vz = camera_position.vz - pivot.vz;

		gte_SetRotMatrix(&matrix);
		gte_SetTransVector(&pivot);

		gte_ldv0(&temp);
		gte_rtv0tr();
		gte_stlvnl(&camera_position);

		// this seems to reflect matrix by Y axis
		short v1, v0, a1, a2;

		v1 = matrix.m[0][1];
		v0 = matrix.m[1][0];
		a1 = matrix.m[0][2];
		a2 = matrix.m[2][0];

		v1 = v1 ^ v0;
		v0 = v0 ^ v1;
		v1 = v1 ^ v0;
		matrix.m[1][0] = v0;
		matrix.m[0][1] = v1;

		a1 = a1 ^ a2;
		a2 = a2 ^ a1;
		a1 = a1 ^ a2;
		matrix.m[2][0] = a2;
		matrix.m[0][2] = a1;

		v0 = matrix.m[2][1];
		v1 = matrix.m[1][2];
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

	if (rotation != 0 || eventCamera.rotate != 0)
	{
		Set_Inv_CameraMatrix();
		SetCameraVector();
		SetupDrawMapPSX();
	}

	eventCamera.rotate = rotation;

	if (ev->flags & 0x800)
	{
		ev->flags &= ~0x1;
		events.draw = 0;
	}
	else
	{
		events.draw = ev->model;
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
	if (ev->node[2] == STATION_NODE_2)
	{
		ev->node = &ev->node[2];
	}
	else
	{
		ev->node = &ev->node[1];
		ev->flags ^= 0x8000;
	}

	if (*ev->node == STATION_NODE_1)
	{
		ev->node = &ev->data[3];
	}
	else if (ev->node[3] == STATION_NODE_0)
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

// [D] [T]
void StepFromToEvent(EVENT* ev)
{
	int df;
	int md;
	long* curr;
	int* to;
	int direction;
	int d, d2;

	if (ev->timer > 0)
	{
		ev->timer--;
		return;
	}

	if (ev->timer != 0)
		return;

	direction = ev->flags & 0xc000;
	to = &ev->node[1];

	if (direction == 16384)
	{
		curr = &ev->position.vy;
	}
	else if (direction <= 16384)
	{
		if (direction != 0)
			curr = (long*)&ev->position.vx;
		else
			curr = (long*)&ev->position.vz;
	}
	else if (direction == 32768)
	{
		curr = &ev->position.vz;
	}

	d = *curr - *ev->node;
	d2 = *to - *curr;

	if (ABS(d2) < ABS(d))
		md = ABS(d2);
	else
		md = ABS(d);

	df = *to - ev->node[0] >> 31;

	// movement speed
	if ((ev->flags & 0xC000) == 0x4000)
	{
		if (md > 1024)
			md = ev->data[0] ^ df;
		else
			md = ((ev->data[0] - 1) * rcossin_tbl[(md & 0xfff) * 2]) / 4096 + 1 ^ df;
	}
	else
	{
		if (md > 2048)
			md = ev->data[0] ^ df;
		else
			md = ((ev->data[0] - 1) * rcossin_tbl[(md >> 1 & 0xfff) * 2]) / 4096 + 1U ^ df;
	}

	*curr += (md - df);

	if ((d2 ^ *to - *curr) < 0)
	{
		*curr = *to;

		ev->timer = -1;

		if (ev == events.cameraEvent)
		{
			SetSpecialCamera(SPECIAL_CAMERA_RESET, 0);

			if(direction == 16384)
			{
				SetMSoundVar(3, NULL);
			}
		}
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

// [D] [T]
void StepPathEvent(EVENT* ev)
{
	static int speed;

	int d1;
	int* i;
	int d;
	int* from;
	int* to;
	Station station;
	int direction;
	long* curr;
	int dir;
	int turn[4];
	XZPAIR centre;
	XZPAIR offset;
	short flags;

	if (ev->timer != 0)
	{
		if (ev->timer == 1)
		{
			ev->timer--;

			do
			{
				NextNode(ev);
				flags = ev->flags;

				ev = ev->next;

				if (ev == NULL)
				{
					speed = 0;
					return;
				}

			} while (ev->flags == (flags & ~0x400));
		}
		else
		{
			if (!(ev->flags & 0x100))
				ev->timer--;
		}

		speed = 0;
		return;
	}

	flags = ev->flags;

	if (speed == 0 && (flags & 0x400) == 0)
		return;

	from = ev->node;
	to = &from[2];

	if (*from == STATION_NODE_2)
	{
		station = EVENT_LEAVING;
		i = &from[1];
	}
	else
	{
		station = EVENT_APPROACHING;

		i = &from[0];

		if (from[2] == STATION_NODE_2)
		{
			to = &from[3];
		}
		else
		{
			station = EVENT_NO_STATION;

			if (from[-1] == STATION_NODE_2)
				i = &from[-2];
			else if (from[2] == STATION_NODE_1)
				to = &ev->data[3];
			else if (from[1] == STATION_NODE_1 && &ev->data[3] < to)
				to = &ev->data[4];
		}
	}

	// move train
	if ((flags & 0x7000) == 0x1000)
	{
		uint loop; // unsigned on purspose

		if (flags & 0x8000)
		{
			direction = -1;
			loop = 3;
		}
		else
		{
			direction = 1;
			loop = 0;
		}

		if (from[0] == STATION_NODE_2)
			i = &from[-2];

		while (loop < 4)
		{
			if (*i == STATION_NODE_1)
				i = &ev->data[3];
			else if (*i == STATION_NODE_2)
				i += 2;

			turn[loop] = *i;
			i++;
			loop += direction;
		}

		if (turn[0] - turn[2] > -1)
			centre.x = turn[2] + 2048;
		else
			centre.x = turn[2] - 2048;

		if (turn[3] - turn[1] > -1)
			centre.z = turn[1] + 2048;
		else
			centre.z = turn[1] - 2048;

		if (ev->flags & 0x400)
			speed = *ev->data;

		offset.x = (ev->position.vz - centre.z) * speed / 2048;
		offset.z = (centre.x - ev->position.vx) * speed / 2048;

		if (((turn[2] - turn[0]) * offset.x + (turn[3] - turn[1]) * offset.z) * direction < 0)
		{
			offset.x = -offset.x;
			offset.z = -offset.z;
		}

		ev->position.vx += offset.x;
		ev->position.vz += offset.z;

		ev->rotation = ratan2(offset.x, offset.z) + 1024U & 0xfff;

		if ((ev->flags & 0x8000) == 0)
		{
			centre.z = ev->position.vz - centre.z;

			if (turn[3] - turn[1] < 0)
			{
				if (centre.z > -1)
					return;
			}
			else
			{
				if (centre.z < 1)
					return;
			}

			ev->position.vx = turn[2];
			NextNode(ev);
			return;
		}

		centre.x = ev->position.vx - centre.x;

		if (turn[0] - turn[2] < 0)
		{
			if (centre.x > -1)
				return;
		}
		else
		{
			if (centre.x < 1)
				return;
		}

		ev->position.vz = turn[1];

		NextNode(ev);
		return;
	}

	if (flags & 0x8000)
		curr = &ev->position.vz;
	else
		curr = &ev->position.vx;

	d = *to - *curr;

	if (d < 0)
		dir = -1;
	else
		dir = 1;

	d = ABS(d);
	d1 = ABS(*curr - *i);

	if (d1 > d)
	{
		if (station == EVENT_LEAVING)
			station = EVENT_NO_STATION;

		d1 = d;
	}
	else
	{
		if (station == EVENT_APPROACHING)
			station = EVENT_NO_STATION;
	}

	d = ABS(*curr - *i);

	if (d <= d1)
		d1 = d;

	if (ev->flags & 0x400)
	{
		if (ev->flags & 0x80)
		{
			if (CameraCnt < 0x1000)
				speed = (ev->data[1] * (4096 - CameraCnt) + ev->data[2] * CameraCnt) / 4096;
			else
				speed = ev->data[2];
			//debugSpeed = speed;
		}

		speed = ev->data[1];
	}

	if ((d1 < 6000 || station == EVENT_NO_STATION && d1 < 8048) && (ev->flags & 0x400))
	{
		if (station == EVENT_NO_STATION)
		{
			if ((ev->flags & 0x7000U) == 0x3000)
			{
				speed = ev->data[0] + (speed - ev->data[0]) * rcossin_tbl[(((d1 - 2048) * 1024) / 8048 & 0xfffU) * 2] / 4096;
			}
		}
		else
		{
			// acceleration or slowdown
			speed = 5 + (speed - 5) * rcossin_tbl[((d1 << 10) / 6000 & 0xfffU) * 2] / 4096;
		}
	}

	*curr += speed * dir;

	if (station == 0 && ev->flags & 0x7000)
	{
		if ((*to - *curr) * dir > 2047)
		{
			return;
		}

		if ((ev->flags & 0x7000) == 0x3000)
		{
			ev->flags &= ~0x7000;
			ev->flags |= 0x1000;
			return;
		}
		return;
	}

	if ((*to - *curr) * dir < 0)
	{
		if (station == 0)
		{
			InitTrain(ev, 0, 0);
		}
		else if (ev->flags & 0x400)
		{
			ev->timer = 300;
		}
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

	return (4096 - rcossin_tbl[((timer * 2048) / 1000 & 0xfffU) * 2 + 1]) * 800 / 8192;
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

// [D] [T]
void StepHelicopter(EVENT* ev)
{
	static int rotating = 1;

	short sign;
	int rot;
	int pitch, roll, d2p, d2r;
	int direction;
	int vx, vz;
	XZPAIR vel;
	VECTOR pos;
	VECTOR drift = { 2,3,2 };

	if (ev->timer >= 0)
	{
		int b, c, d, t, tt1, tt2;
		t = ev->timer >> 3;

		tt1 = FIXEDH(t * t);
		tt2 = FIXEDH(tt1 * t);

		b = (tt2 * 3 - tt1 * 5) / 2 + 4096;
		c = tt1 * 2 + (t - tt2 * 3) / 2;
		d = (tt2 - tt1) / 2;

		ev->position.vx = ev->node[0] + FIXEDH((ev->node[2] - ev->node[0]) * b + (ev->node[4] - ev->node[0]) * c + (ev->node[6] - ev->node[0]) * d);
		ev->position.vz = ev->node[1] + FIXEDH((ev->node[3] - ev->node[1]) * b + (ev->node[5] - ev->node[1]) * c + (ev->node[7] - ev->node[1]) * d);

		ev->timer += HelicopterData.speed;

		if (ev->timer < 0)
		{
			if (ev->node[9] == (ev->node[8] == 0))
			{
				ev->timer = -1;
			}
			else
			{
				ev->timer = 0;
				ev->node += 2;
			}
		}

		if (ev->rotation == -1)
		{
			vel.x = (ev->node[4] - ev->node[0]) / 2;
			vel.z = (ev->node[5] - ev->node[1]) / 2;

			ev->rotation = ratan2(vel.x, vel.z);

			HelicopterData.pitch = 0;
			HelicopterData.roll = 0;
			HelicopterData.dp = 0;
			HelicopterData.dr = 0;
		}
		else
		{
			vel.x = ev->position.vx - HelicopterData.lastX;
			vel.z = ev->position.vz - HelicopterData.lastZ;
		}

		rot = ev->rotation & 0xfff;

		vz = vel.z * rcossin_tbl[rot * 2 + 1] + vel.x * rcossin_tbl[rot * 2];
		vx = vel.x * rcossin_tbl[rot * 2 + 1] - vel.z * rcossin_tbl[rot * 2];

		pitch = HelicopterData.pitch;

		if (ABS(vz) <= 900000)
			pitch = -HelicopterData.pitch - (rcossin_tbl[((vz * 1024) / 900000 & 0xfffU) * 2] >> 3);
		else if (vz < 1)
			pitch = 512 - pitch;
		else
			pitch = -512 - pitch;

		roll = HelicopterData.roll;

		if (ABS(vx) <= 150000)
			roll = (rcossin_tbl[((vx * 1024) / 150000 & 0xfff) * 2] >> 3) - roll;
		else if (vx < 1)
			roll = -512 - roll;
		else
			roll = 512 - roll;

		d2p = pitch - HelicopterData.dp;

		if (ABS(d2p) < 5)
		{
			HelicopterData.dp = pitch;
		}
		else
		{
			sign = (d2p >> 0x1f);
			HelicopterData.dp += (sign ^ 5) - sign;
		}

		d2r = roll - HelicopterData.dr;

		if (ABS(d2r) < 5)
		{
			HelicopterData.dr = roll;
		}
		else
		{
			sign = (d2r >> 0x1f);
			HelicopterData.dr += (sign ^ 5) - sign;
		}

		HelicopterData.pitch = (HelicopterData.pitch + HelicopterData.dp + 2048U & 0xfff) - 2048;
		HelicopterData.roll = (HelicopterData.roll + HelicopterData.dr + 2048U & 0xfff) - 2048;

		rot = (ratan2(vel.x, vel.z) - ev->rotation + 2048U & 0xfff) - 2048;

		if (ABS(rot) > 512)
		{
			if (rot > 0)
				direction = 1024;
			else
				direction = -1024;
		}
		else
		{
			direction = rcossin_tbl[(rot & 0x7ff) * 4] >> 2;
		}

		ev->rotation += FIXEDH(FIXEDH(direction * direction) * direction);
		ev->rotation &= 0xfff;

		if (GetSurfaceIndex((VECTOR*)&ev->position) == -23)
		{
			if (ev->position.vy < -50)
			{
				ev->position.vy += 10;
			}
			else
			{
				pos.vy = 0;
				pos.vx = ev->position.vx;
				pos.vz = ev->position.vz;

				Setup_Smoke(&pos, 100, 500, 2, 0, &dummy, 0);
			}
		}
		else
		{
			if (ev->position.vy > -1000)
				ev->position.vy -= 10;
		}

		HelicopterData.lastX = ev->position.vx;
		HelicopterData.lastZ = ev->position.vz;

		SetMSoundVar((int)&ev->position, NULL);

		if ((ev->flags & 0x100) && (Random2(0) & 3) == (CameraCnt & 3U))
		{
			Setup_Smoke((VECTOR*)&ev->position, 100, 500, 1, 0, &dummy, 0);
		}
	}

	if (ev->model == HelicopterData.deadModel)
	{
		pos.vy = -200;
		pos.vx = ev->position.vx + (rand() & 0xff) - 128;
		pos.vz = ev->position.vz + (rand() & 0xff) - 128;

		Setup_Smoke(&pos, 50, 100, 4, 0, &dummy, 0);
		Setup_Smoke(&pos, 100, 500, 1, 0, &drift, 0);

		SetMSoundVar(0, NULL);
	}
	else
	{
		HelicopterData.rotorrot += HelicopterData.rotorvel;
		HelicopterData.rotorvel += rotating;

		if (ABS(HelicopterData.rotorvel) > 256)
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

// [D] [T]
void StepEvents(void)
{
	EVENT* ev;
	int i;
	VECTOR old;
	XZPAIR speed;
	VECTOR* pos;
	EVENT* evt;
	VECTOR* vel;
	CELL_OBJECT* cop;
	CAR_DATA* cp;
	int onBoatLastFrame;
	int dist;
	int thisCamera, otherCamera;

	onBoatLastFrame = carsOnBoat;
	ev = firstEvent;

	if (detonator.timer)
		DetonatorTimer();

	while (ev)
	{
		carsOnBoat = onBoatLastFrame;

		if (ev->flags & 2)
		{
			if (ev->flags & 0x40)
			{
				i = 0;
				cp = car_data;

				carsOnBoat = 0;
				do {

					if (cp->controlType != CONTROL_TYPE_NONE &&
						OnBoat((VECTOR*)cp->hd.where.t, ev, &dist))
					{
						carsOnBoat |= 1 << i;
					}

					i++;
					cp++;
				} while (i < MAX_CARS && i < 32);

				// make Tanner on boat also
				if (player[0].playerType == 2 && OnBoat((VECTOR*)player, ev, &dist))
					carsOnBoat |= 0x300000;

				BoatOffset(&boatOffset, ev);

				old.vx = ev->position.vx;
				old.vz = ev->position.vz;
			}

			if (ev->flags & 0x10)
				StepFromToEvent(ev);
			else
				StepPathEvent(ev);

			if (ev->flags & 0x800)
			{
				int tmSqr;

				ev->data[1] = rcossin_tbl[(CameraCnt & 0x7f) * 64] >> 9 & 0xfff;
				ev->data[2] = rcossin_tbl[(CameraCnt & 0xff) * 32 + 1] + 4096 >> 7;

				tmSqr = detonator.timer * detonator.timer;

				if (detonator.timer - 1U < 159) // HMM?
				{
					ev->data[1] -= rcossin_tbl[(detonator.timer & 0x3fU) * 128] * tmSqr >> 0x12;
					ev->data[2] -= rcossin_tbl[(detonator.timer & 0x3fU) * 128] * tmSqr >> 0x10;
				}

				if (foam.rotate & 0xffff7fffU) // HMMMMMM?
					foam.rotate--;
				else
					foam.rotate ^= ((Random2(0) & 0xf00) >> 8) + 8U | 0x8000;
			}

			// move cars on boats
			if ((ev->flags & 0x40) && (carsOnBoat != 0 || onBoatLastFrame != 0))
			{
				int bit;

				speed.x = ev->position.vx - old.vx;
				speed.z = ev->position.vz - old.vz;

				// go thru cars
				for (i = 0; i < MAX_CARS + 1 && i < 32; i++)
				{
					bit = (1 << i);

					if (i == TANNER_COLLIDER_CARID)
					{
						pos = (VECTOR*)player[0].pos;
						vel = NULL;
					}
					else
					{
						pos = (VECTOR*)car_data[i].hd.where.t;
						vel = (VECTOR*)car_data[i].st.n.linearVelocity;
					}

					// update position and add velocity
					if (carsOnBoat & bit)
					{
						pos->vx += speed.x;
						pos->vz += speed.z;

						if (i == TANNER_COLLIDER_CARID)
						{
							SetTannerPosition((VECTOR*)pos);
							carsOnBoat &= ~0x100000;
						}
						else if ((onBoatLastFrame & bit) == 0)
						{
							vel->vx -= speed.x * 4096;
							vel->vz -= speed.z * 4096;
						}

						car_data[i].st.n.fposition[0] = car_data[i].hd.where.t[0] << 4;
						car_data[i].st.n.fposition[2] = car_data[i].hd.where.t[2] << 4;
					}
					else if (vel && (onBoatLastFrame & bit))
					{
						vel->vx += speed.x * 4096;
						vel->vz += speed.z * 4096;
					}
				}
			}
		}
		else
		{
			ushort flags;
			flags = ev->flags & 0xcc0;

			if (flags == 0x40)
			{
				// perform rotation of doors
				if (ev->timer != 0)
				{
					FixedEvent* door;
					int sign, rotAngle;
					unsigned short* target;

					door = (FixedEvent*)ev;

					if (door->active == 1)
						target = &door->finalRotation;
					else
						target = &door->initialRotation;

					rotAngle = ABS(door->rotation - door->initialRotation) * 2048 / ABS(door->finalRotation - door->initialRotation);

					sign = (*target - door->rotation) >> 0x1f;
					door->rotation += (door->minSpeed + (rcossin_tbl[(rotAngle & 0xfffU) * 2] * (door->maxSpeed - door->minSpeed) >> 0xc) ^ sign) - sign;

					// check if complete
					if (((*target - door->rotation) ^ sign) - sign < 0)
					{
						door->rotation = *target;
						door->active = 0;

						if (gCurrentMissionNumber != 30)
							SetMSoundVar(3, NULL);

						if (door == (FixedEvent*)events.cameraEvent)
							SetSpecialCamera(SPECIAL_CAMERA_RESET, 0);
					}
				}
			}
			else if (flags < 0x41)
			{
				// perform bridge rotation
				if ((ev->flags & 0xcc0) == 0)
				{
					ev->rotation = GetBridgeRotation(ev->timer);

					if (ev->model & 1)
						ev->rotation = -ev->rotation;

					if ((ev->flags & 0x100) == 0 || ev->timer <= 1000)
					{
						ev->timer++;
						ev->timer %= 8000;
					}
				}
			}
			else if (flags == 0xc0)
			{
				StepHelicopter(ev);
			}
			else if (flags == 0x440)
			{
				// rotate ferris wheel
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

				chicagoDoor[2].rotation -= chicagoDoor[2].active;
				chicagoDoor[2].rotation &= 0xfff;
			}
		}

		onBoatLastFrame = carsOnBoat;

		ev = ev->next;
	}

	VisibilityLists(VIS_SORT, 0);

	if (EventCop != NULL)
	{
		event_models_active = 0;

		for (i = 0; i < NumPlayers; i++)
		{
			unsigned short* x;
			unsigned short* z;

			if (i == 0)
			{
				thisCamera = 0x8000;
				otherCamera = 0x4000;

			}
			else
			{
				thisCamera = 0x4000;
				otherCamera = 0x8000;
			}

			VisibilityLists(VIS_NEXT, i);

			x = xVis;
			while ((*x & thisCamera) == 0)
			{
				if ((*x & otherCamera) == 0)
				{
					if ((*x & 0x80) == 0)
						evt = &event[*x & 0x7f];
					else
						evt = (EVENT*)&fixedEvent[*x & 0x7f];

					// events that enable drawing
					if ((evt->flags & 0x204) == 0x200)
					{
						z = zVis;

						while ((*z & thisCamera) == 0)
						{
							if ((*z & otherCamera) == 0 && (*x & 0xfff) == (*z & 0xfff))
							{
								cop = &EventCop[event_models_active++];

								cop->pos.vx = evt->position.vx;
								cop->pos.vy = evt->position.vy;
								cop->pos.vz = evt->position.vz;
								cop->yang = (evt->rotation >> 6);
								cop->type = evt->model;

								// [A] train should be only dangerous in "Beat the train"
								if ((evt->flags & 0x12) == 2 && gCurrentMissionNumber == 22)
									cop->pad = 1;
								else
									cop->pad = 0;

								evt->flags |= 4;
							}
							z++;
						}
					}
				}

				x++;
			}
		}
	}

	if (cameraDelay.delay != 0 && --cameraDelay.delay == 0)
	{
		SetSpecialCamera((SpecialCamera)cameraDelay.type, 1);
	}
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

	if (chicagoDoor[2].model == -1)
		return;

	RenderModel(modelpointers[chicagoDoor[2].model], matrix, pos, 0, 4, 1, 0);

	if (chicagoDoor[2].model != -1)
		RenderModel(modelpointers[chicagoDoor[2].initialRotation], NULL, NULL, 0, 0, 1, 0);

	matrix->m[0][0] = -matrix->m[0][0];
	matrix->m[1][0] = -matrix->m[1][0];
	matrix->m[2][0] = -matrix->m[2][0];

	RenderModel(modelpointers[chicagoDoor[2].model], matrix, pos, 0, 4, 1, 0);

	if (chicagoDoor[2].minSpeed == -1)
		return;

	VECTOR spoke[2] = {
		{0, 0, 2677},
		{0, 2677, 0}
	};

	rotation = 0;

	model = modelpointers[chicagoDoor[2].minSpeed];

	SetRotMatrix(&inv_camera_matrix);
	_MatrixRotate(&spoke[0]);
	_MatrixRotate(&spoke[1]);

	for (loop = 0; loop < 5; loop++)
	{
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
		rotation += 410;
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

	localMat.m[0][0] = ONE;
	localMat.m[1][0] = 0;
	localMat.m[2][0] = 0;
	localMat.m[0][1] = 0;
	localMat.m[1][1] = ONE;
	localMat.m[2][1] = 0;
	localMat.m[0][2] = 0;
	localMat.m[1][2] = 0;
	localMat.m[2][2] = ONE;

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
	*(ushort*)&poly->u3 = *(ushort*)&HelicopterData.rotorTexture.coords.u3;

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

// [D] [T]
void DrawEvents(int camera)
{
	static EVENT* nearestTrain; // offset 0x28
	static int distanceFromNearestTrain; // offset 0x2c

	int reflection;
	int i;
	unsigned short* x;
	unsigned short* z;
	EVENT* ev;
	MATRIX matrix;
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

	x = xVis;
	while ((*x & thisCamera) == 0)
	{
		if ((*x & otherCamera) == 0)
		{
			if ((*x & 0x80) == 0)
				ev = &event[*x & 0x7f];
			else
				ev = (EVENT*)&fixedEvent[*x & 0x7f];

			z = zVis;

			while ((*z & thisCamera) == 0)
			{
				if ((*z & otherCamera) == 0 && (*x & 0xfff) == (*z & 0xfff))
				{
					if ((ev->flags & 4) == 0 && (ev->flags & 1) == camera)
					{
						ev->flags |= 4;

						if (camera == 0)
						{
							if (es_mobile[0] != -1 && (ev->flags & 2))
							{
								int dist;

								dist = ABS(ev->position.vx - camera_position.vx) + ABS(ev->position.vz - camera_position.vz);

								if (nearestTrain == NULL || dist < distanceFromNearestTrain)
								{
									nearestTrain = ev;
									distanceFromNearestTrain = dist;
								}
							}

							if (FrustrumCheck((VECTOR*)&ev->position, modelpointers[ev->model]->bounding_sphere) != -1)
							{
								pos.vx = ev->position.vx - camera_position.vx;
								pos.vy = ev->position.vy - camera_position.vy;
								pos.vz = ev->position.vz - camera_position.vz;

								matrix.m[0][0] = ONE;
								matrix.m[1][0] = 0;
								matrix.m[2][0] = 0;
								matrix.m[0][1] = 0;
								matrix.m[1][1] = ONE;
								matrix.m[2][1] = 0;
								matrix.m[0][2] = 0;
								matrix.m[1][2] = 0;
								matrix.m[2][2] = ONE;

								reflection = 0;

								if ((ev->flags & 2U) == 0)
								{
									int type;

									type = ev->flags & 0xcc0;

									if (type == 0x80)
									{
										_RotMatrixY(&matrix, ev->rotation);

										pos.vx = pos.vx - boatOffset.vx;
										pos.vz = pos.vz - boatOffset.vz;
										pos.vy = (pos.vy - boatOffset.vy) + FIXEDH((int)ev->node * rcossin_tbl[(*ev->data & 0xfffU) * 2]);
									}
									else if (type == 0x400)
									{
										_RotMatrixY(&matrix, ev->rotation);
									}
									else if (type == 0x440)
									{
										_RotMatrixX(&matrix, ev->rotation);
									}
									else if (type == 0x480)
									{
										int rot;

										for (i = 0; i < 4; i++)
										{
											if ((i & 1) == 0)
												offset.x = -201;
											else
												offset.x = 201;

											if ((i & 2) == 0)
												offset.z = -1261;
											else
												offset.z = 1261;

											rot = ev->rotation + 0x200U & 0x400;

											shadow[i].vx = ev->position.vx + (rot ? offset.z : offset.x);
											shadow[i].vy = 0;
											shadow[i].vz = ev->position.vz + (rot ? offset.x : offset.z);
										}

										PlaceShadowForCar(shadow, 0, 35, 4);
										_RotMatrixY(&matrix, ev->rotation);
									}
									else if (type != 0xc0)
									{
										type = ev->flags & 0x30;

										if (type == 0x20)
										{
											_RotMatrixZ(&matrix, ev->rotation);
										}
										else if (type == 0x10)
										{
											_RotMatrixY(&matrix, ev->rotation);
										}
										else if (type == 0)
										{
											_RotMatrixX(&matrix, ev->rotation);
										}
									}
								}
								else
								{
									_RotMatrixY(&matrix, ev->rotation);
								}

								gte_SetRotMatrix(&inv_camera_matrix);

								_MatrixRotate(&pos);

								if ((ev->flags & 0xcc0) == 0xc0)
								{
									if (ev->model == HelicopterData.cleanModel)
									{
										_RotMatrixZ(&matrix, HelicopterData.roll & 0xfff);
										_RotMatrixX(&matrix, HelicopterData.pitch & 0xfff);
										_RotMatrixY(&matrix, ev->rotation & 0xfff);

										DrawRotor(ev->position, &matrix);

										RenderModel(modelpointers[ev->model], &matrix, &pos, 0, 0, 1, 0);

										pos.vx = ev->position.vx - camera_position.vx;
										pos.vy = -camera_position.vy - ev->position.vy;
										pos.vz = ev->position.vz - camera_position.vz;

										gte_SetRotMatrix(&inv_camera_matrix);

										_MatrixRotate(&pos);
										reflection = 1;
									}
									else
									{
										// scale matrix lil bit
										matrix.m[0][0] = matrix.m[0][0] * 5 >> 2;
										matrix.m[1][1] = matrix.m[1][1] * 5 >> 2;
										matrix.m[2][2] = matrix.m[2][2] * 5 >> 2;

										_RotMatrixY(&matrix, 2813);
										RenderModel(modelpointers[ev->model], &matrix, &pos, 0, 0, 1, 0);
									}
								}

								if (ev->flags & 0x800)
								{
									_RotMatrixX(&matrix, ev->data[1]);

									pos.vy -= ev->data[2];
									temp = combointensity;

									if (ev->flags & 0x20)
									{
										SetupPlaneColours(0x80a0c);
									}
									else
									{
										ev->flags |= 1;
										reflection = 1;	// [A] fix bug with ferry reflection at night
									}
								}

								if (reflection)
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

								if (ev->flags & 0x800)
								{
									combointensity = temp;

									matrix.m[0][0] = 0;
									matrix.m[0][1] = 0;
									matrix.m[0][2] = (foam.rotate & 0x8000) ? ONE : -ONE;
									matrix.m[1][0] = 0;
									matrix.m[1][1] = ONE;
									matrix.m[1][2] = 0;
									matrix.m[2][0] = ONE;
									matrix.m[2][1] = 0;
									matrix.m[2][2] = 0;

									pos.vy += ev->data[2];

									if (gTimeOfDay != 1)
										SetupPlaneColours(0x00282828);

									RenderModel(foam.model, &matrix, &pos, 200, (foam.rotate & 0x8000) ? 0x3 : 0x1, 1, 0);
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
				z++;
			}
		}

		x++;
	}

	if (camera)
	{
		ResetEventCamera();
	}
	else if (eventHaze != 0)
	{
		add_haze(eventHaze, eventHaze, 7);
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

// [A] camera offset for events
void EventCameraOffset(SVECTOR* offset)
{
	offset->vx = 0;
	offset->vy = 0;
	offset->vz = 0;

	if (gCurrentMissionNumber == 22)
	{
		offset->vy = 650;
		offset->vz = -850;
	}
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

// [D] [T]
sdPlane* EventSurface(VECTOR* pos, sdPlane* plane)
{
	int d;
	EVENT* ev;
	int d1, d2;
	int dist;
	int sin;
	int cos;

	int i;

	i = plane->surface & 0xffef;

	ev = &event[i];

	// chicago bridge plane
	if (GameLevel == 0)
	{
		int dist;
		int end;

		if ((ev->flags & 0x30U) == 0)
			dist = pos->vz;
		else
			dist = pos->vx;

		if ((i & 1) == 0)
			end = ev->data[1];
		else
			end = ev->data[-1];

		d = ev->rotation & 0xfff;
		sin = rcossin_tbl[d * 2];
		cos = rcossin_tbl[d * 2 + 1];

		d1 = (end - ev->data[0]) * cos;
		d2 = dist - ev->data[0];

		if (ABS(d1) < ABS(d2) * 4096)
			return GetSeaPlane();

		plane->d = d2 * sin / cos;

		if (d2 > 1024)
		{
			if (pos->vy + 200 < plane->d)
			{
				return GetSeaPlane();
			}

			plane->b = cos * 4;
		}
		else
		{
			plane->b = cos * 4;
		}

		if ((ev->flags & 0x30U) == 0)
		{
			plane->a = 0;
			plane->c = sin * -4;
			//plane->d = (sin * -0x40000) >> 0x10;	// [A] this is unused and incorrect!
		}
		else
		{
			plane->c = 0;
			plane->a = sin * -4;
		}

		plane->d ^= 0x40000000;
	}
	else if (GameLevel == 1 || GameLevel == 3)
	{
		// Havana and Rio boats floating

		if (ev->flags & 0x800)
		{
			int height;
			int offset;

			if (OnBoat(pos, ev, &dist) == 0)
				return GetSeaPlane();

			if (GameLevel == 3)
				height = 256;
			else
				height = 200;


			d = ev->data[1] & 0xfff;

			sin = rcossin_tbl[d * 2];
			cos = rcossin_tbl[d * 2 + 1];

			offset = dist * -4096 + cos * -3328;

			if (GameLevel == 3 && offset > 0)
			{
				int sin2;
				d = 160 - ev->data[1] & 0xfff;

				cos = rcossin_tbl[d * 2 + 1];
				sin2 = rcossin_tbl[d * 2];

				if (offset > cos * 2048)
				{
					debugOffset = offset;
					return GetSeaPlane();
				}

				plane->d = height - (FIXEDH(sin * 3328) + ev->data[2] + ev->position.vy) + (FIXEDH(offset) * sin2 / cos) ^ 0x40000000;

				plane->b = cos * 4;
				plane->a = 0;
				plane->c = sin2 * 4;
			}
			else
			{
				plane->b = cos * 4;
				plane->a = 0;
				plane->c = sin * 4;
				plane->d = (height + (sin * dist / cos - ev->data[2] - ev->position.vy)) ^ 0x40000000;
			}
		}
		else
		{
			if (pos->vy < -ev->position.vy - 100)
			{
				plane->d = 0xbfffee02;
			}
			else
			{
				plane->d = ev->position.vy;
			}
		}
	}
	else
	{
		return GetSeaPlane();
	}

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

// [D] [T]
VECTOR* TriggerEvent(int i)
{
	static int stage[10];

	EVENT* ev;
	int loop;
	VECTOR* pos;

	pos = NULL;

	if (i == -1) // initialize
	{
		for (loop = 0; loop < 10; loop++)
			stage[loop] = 0;

		return NULL;
	}

	if (GameLevel >= 2 && i > 0 && i < 4) // Vegas and Rio detonators
	{
		if (stage[i] == 0)
		{
			ev = &firstMissionEvent[i - 1];

			ev->next = firstEvent->next;
			firstEvent->next = ev;

			VisibilityLists(VIS_ADD, ev - event);
			SetMSoundVar(i, NULL);

			detonator.count++;
		}
	}
	else
	{
		if (GameLevel == 0)
		{
			switch (i)
			{
				case 0:
				case 1:
					if (stage[i] == 0)
					{
						int offset, nodePos;
						
						ev = missionTrain[i].engine;
						
						MakeEventTrackable(ev);
						ev->flags |= 0x180;

						if (*missionTrain[i].node - missionTrain[i].start > -1)
							offset = 1600;
						else
							offset = -1600;

						loop = 0;

						do {
							if (missionTrain[i].node[0] == STATION_NODE_2)
								nodePos = missionTrain[i].node[-1];
							else
								nodePos = missionTrain[i].node[1];

							if (missionTrain[i].startDir == 0x8000)
							{
								ev->flags |= 0x8000;
								ev->position.vx = nodePos;
								ev->position.vz = missionTrain[i].start + loop * offset;
							}
							else
							{
								ev->flags &= ~0x8000;
								ev->position.vz = nodePos;
								ev->position.vx = missionTrain[i].start + loop * offset;
							}

							ev->node = missionTrain[i].node;
							ev->data = &missionTrain[i].cornerSpeed;
							ev->timer = 0;
							
							ev->flags &= ~0x7000;
							ev->flags |= 0x3000;

							SetElTrainRotation(ev);

							loop++;
							ev = ev->next;
						} while (ev && (ev->flags & 0x400U) == 0);
					}
					else
					{
						ev = missionTrain[i].engine;
						
						pos = &ev->position;
						
						if (ev->timer != 0)
							ev->timer = 1;

					}
					break;
				case 2:
				case 3:
				case 4:
					if (stage[i] == 0)
					{
						// start bridges raised
						ev = firstMissionEvent;
						for (loop = 0; loop < 10; loop++)
						{
							ev->flags |= 0x100;

							if (i == 4)
								ev->timer = 2600;
							else
								ev->timer = 1000;
							
							ev++;
						}

						if (i == 2)
						{
							firstMissionEvent[9].timer = 2600;
							firstMissionEvent[8].timer = 2600;
						}
					}
					else
					{
						// raise bridges
						firstMissionEvent[8].timer = 0;
						firstMissionEvent[9].timer = 0;
					}
					break;
				case 5:
					PrepareSecretCar();
					events.cameraEvent = (EVENT*)&chicagoDoor[0];
				case 6:
					TriggerDoor(&chicagoDoor[i - 5], &stage[i], 1);
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
					event->position.vx = HavanaFerryData[9];
					event->position.vz = HavanaFerryData[10];
				
					event->timer = 1;
				
					event->node = &HavanaFerryData[10];
					event->data = &HavanaFerryData[6];
					break;
				case 2:
					TriggerDoor(&havanaFixed[0], &stage[i], 1);
					break;
				case 3:
					PrepareSecretCar();
					events.cameraEvent = (EVENT*)&havanaFixed[2];
					TriggerDoor(&havanaFixed[2], &stage[i], 0);
					break;
				case 4:
					if (stage[i] != 0)
					{
						SetSpecialCamera(SPECIAL_CAMERA_WAIT, 0);
						event[1].node++;
					}

					SetMSoundVar(1, &event[1].position);

					event[1].timer = 0;
					events.cameraEvent = &event[1];
			}
		}
		else if (GameLevel == 2)
		{
			switch (i)
			{
				case 0:
					loop = 0;

					// start train
					do {
						ev = &event[loop];

						ev->data = VegasTrainData;
						
						InitTrain(ev, loop, 1);
						
						ev->flags |= 0x200;

						if (loop > 1)
							VisibilityLists(VIS_ADD, loop);

						loop++;
					} while (loop < 9);

					event->flags |= 0x500;

					MakeEventTrackable(ev);

					event[1].next = &event[2];
					break;
				case 4:
					TriggerDoor(&vegasDoor[i - 4], &stage[i], 0);
					break;
				case 8:
					events.cameraEvent = (EVENT*)&vegasDoor[4];
					PrepareSecretCar();
				case 5:
				case 6:
				case 7:
					TriggerDoor(&vegasDoor[i - 4], &stage[i], 1);
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
					// open race track gates
					TriggerDoor(&rioDoor[2], &stage[i], 0);
					TriggerDoor(&rioDoor[3], &stage[i], 0);

					events.cameraEvent = (EVENT*)&rioDoor[2];
					break;
				case 5:
				case 6:
					TriggerDoor(&rioDoor[i - 5], &stage[i], (i == 5));
					break;
				case 7:
					if (stage[i] == 0)
					{
						pos = &event[1].position;
					}
					else
					{
						event[1].position.vy = -17;
						event[1].position.vx = -241619;
						event[1].position.vz = -212638;
						event[1].timer = -2;
						event[1].model = HelicopterData.deadModel;
					}

					break;
				case 8:
					// open gate to secret car
					PingOutAllSpecialCivCars();
				
					TriggerDoor(&rioDoor[4], &stage[i], 0);
					TriggerDoor(&rioDoor[5], &stage[i], 0);
				
					events.cameraEvent = (EVENT*)&rioDoor[4];
			}
		}
	}

	if (i < 10)
		stage[i]++;

	return pos;
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

//[D] [T]
void SetSpecialCamera(SpecialCamera type, int change)
{
	static int rememberCamera[3]; // offset 0x230
	static short boatCamera[6] = {
		-1000, 2100, 6000,
		-5000, 3584, -5000
	};

	int* hackCamera;
	short* boat;

	if (change == 0 && type != SPECIAL_CAMERA_WAIT)
	{
		cameraDelay.delay = 1;
		cameraDelay.type = type;
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
	}
	else if (type == SPECIAL_CAMERA_WAIT)
	{
		cameraDelay.delay = 100;
		cameraDelay.type = 1;
		gStopPadReads = 1;
	}
	else
	{
		boat = NULL;

		rememberCamera[0] = camera_position.vx;
		rememberCamera[1] = camera_angle.vy;
		rememberCamera[2] = camera_position.vz;

		if (GameLevel == 0)
		{
			hackCamera = &ChicagoCameraHack[0];
		}
		else if (GameLevel == 1)
		{
			if (gCurrentMissionNumber == 15)
			{
				boat = boatCamera;
				events.cameraEvent = (EVENT*)0x1;
			}
			else
			{
				if (type == SPECIAL_CAMERA_SET2)
				{
					hackCamera = &HavanaCameraHack[6];
					camera_position.vy = -500;
				}
				else if (doneFirstHavanaCameraHack)
				{
					hackCamera = &HavanaCameraHack[3];
				}
				else
				{
					hackCamera = &HavanaCameraHack[0];
					doneFirstHavanaCameraHack = 1;
				}
			}
		}
		else if (GameLevel == 2)
		{
			hackCamera = &VegasCameraHack[0];

			if (gCurrentMissionNumber == 23)
			{
				if (type != SPECIAL_CAMERA_SET2)
				{
					hackCamera = &VegasCameraHack[6];
					events.cameraEvent = (EVENT*)0x1;
				}
				else
				{
					hackCamera = &VegasCameraHack[9];
				}
			}
			else if (gCurrentMissionNumber == 22)
			{
				hackCamera = &VegasCameraHack[13];

				events.cameraEvent = (EVENT*)0x1;
				camera_position.vy = -1800;
			}
			else if (gCurrentMissionNumber == 30)
			{
				hackCamera += 3;
			}
		}
		else if (GameLevel == 3)
		{
			if (gCurrentMissionNumber == 35)
			{
				boat = &boatCamera[3];
			}
			else if (camera_position.vz > 0)
			{
				hackCamera = &RioCameraHack[3];
			}
			else
			{
				hackCamera = &RioCameraHack[0];
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
	}

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

// [D] [T]
int DetonatorTimer(void)
{
	static SVECTOR rememberCameraAngle; // offset 0x30
	static int count = 0; // offset 0x38

	int cnt;
	EVENT* ev;
	VECTOR pos;

	if (gCurrentMissionNumber == 23)
	{
		if (detonator.timer - 3U < 17)
		{
			ScreenShake(detonator.timer - 2, &rememberCameraAngle);
		}
		else if (detonator.timer - 31U > 8)
		{
			if (detonator.timer == 21)
			{
				count++;

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
				SetSpecialCamera(SPECIAL_CAMERA_SET, 0);
				detonator.timer = 70;
			}
			else if (detonator.timer == 22)
			{
				SetSpecialCamera(SPECIAL_CAMERA_SET2, 0);
			}
			else if (detonator.timer == 40)
			{
				BombThePlayerToHellAndBack(gCarWithABerm);
				car_data[gCarWithABerm].st.n.linearVelocity[1] += 200000;
				rememberCameraAngle = camera_angle;
			}
		}
		else
		{
			ScreenShake(detonator.timer - 30, &rememberCameraAngle);
		}
	}
	else
	{
		if (detonator.timer - 141U < 19)
		{
			ScreenShake(detonator.timer - 140, &rememberCameraAngle);
			Setup_Smoke(&firstMissionEvent[0].position, 100, 500, 1, 0, &dummy, 0);
		}
		else
		{
			if (detonator.timer == 167)
			{
				ev = &firstMissionEvent[1];
				ev++;
			}
			else
			{
				if (detonator.timer < 168)
				{
					if (detonator.timer == 0)
					{
						cnt = detonator.count - 1;
						ev = &firstMissionEvent[0];

						if (detonator.count < 3)
						{
							while (detonator.count = cnt, detonator.count != -1)
							{
								AddExplosion(ev->position, BIG_BANG);
								cnt = detonator.count - 1;
								ev++;
							}

							return 0;
						}

						detonator.timer = 200;
						SetSpecialCamera(SPECIAL_CAMERA_SET, 0);
						events.cameraEvent = (EVENT*)0x1;

						rememberCameraAngle = camera_angle;
					}
					else if (detonator.timer == 160)
					{

						if (GameLevel == 3)
						{
							event->flags &= ~0x1;
							event->flags |= 0x20;

							AddExplosion(event[0].position, HEY_MOMMA);
						}
						else
						{
							AddExplosion(firstMissionEvent[1].position, HEY_MOMMA);
						}


					}

					detonator.timer--;
					return 1;
				}

				ev = &firstMissionEvent[0];

				if (detonator.timer == 180)
				{
					ev++;
				}
				else if (detonator.timer != 190)
				{
					detonator.timer--;
					return 1;
				}
			}

			pos.vx = ev->position.vx;
			pos.vy = ev->position.vy;
			pos.vz = ev->position.vz;

			if (GameLevel == 3)
			{
				pos.vx -= boatOffset.vx;
				pos.vy -= boatOffset.vy;
				pos.vz -= boatOffset.vz;
			}

			AddExplosion(pos, BIG_BANG);
		}
	}

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
	while (n != 0x80000000)
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