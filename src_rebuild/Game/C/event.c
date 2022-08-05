#include "driver2.h"
#include "event.h"
#include "cars.h"
#include "players.h"
#include "mc_snd.h"
#include "camera.h"
#include "convert.h"
#include "draw.h"
#include "models.h"
#include "mission.h"
#include "job_fx.h"
#include "bomberman.h"
#include "debris.h"
#include "main.h"
#include "system.h"
#include "spool.h"
#include "texture.h"
#include "civ_ai.h"
#include "pedest.h"
#include "shadow.h"
#include "gamesnd.h"
#include "dr2roads.h"
#include "ASM/rndrasm.h"
#include "cutrecorder.h"
#include "overmap.h"
#include "mission.h"

struct FixedEvent // same as EVENT but different fields
{
	VECTOR position;
	short rotation;
	short active;
	u_short initialRotation;
	u_short finalRotation;
	u_short minSpeed;
	u_short maxSpeed;
	short flags;
	short radius;
	int model;
	EVENT* next;
	char* modelName;
};

struct MissionTrain
{
	EVENT* engine;
	int* node;
	int cornerSpeed;
	int initialStraightSpeed;
	int finalStraightSpeed;
	int start;
	int startDir;
};

struct Foam
{
	MODEL* model;
	int rotate;
};

struct EventCarriage
{
	short rotation;
	short vel;
};

struct MultiCar
{
	EVENT* event;
	int count;
};

struct Helicopter
{
	int speed;
	short pitch;
	short dp;
	short roll;
	short dr;
	int lastX;
	int lastZ;
	TEXTURE_DETAILS rotorTexture;
	short rotorrot;
	short rotorvel;
	int cleanModel;
	int deadModel;
};

struct Detonator
{
	int timer;
	int count;
};

struct CameraDelay
{
	int delay;
	int type;
};

enum VisType
{
	VIS_INIT = 0,
	VIS_SORT = 1,
	VIS_ADD = 2,
	VIS_NEXT = 3,
};

struct EventCamera
{
	VECTOR position;
	short yAng;
	MATRIX matrix;
	int rotate;
};

enum Station
{
	EVENT_NO_STATION = 0,
	EVENT_APPROACHING = 1,
	EVENT_LEAVING = 2,
};

#define PATH_NODE_WRAP		0x80000000	// go back to first node without interpolation
#define PATH_NODE_CYCLE		0x80000001	// cycle nodes with interpolation
#define PATH_NODE_STATION	0x80000002	// stop point

#define PATH_NODE_REVERSE	0x80000003

// TODO: put more meaning into those arrays

int ElTrainData[83] = {
	6, // train count

	// train 1 (n 1)
	80, 130, 0x8000,	// speed 1, 2, start direction
	336284, -220364, 283420, PATH_NODE_STATION,
	-204500, -158924, 247580, -123084, 188624, -158924, 73520, -138444, 17200, -124148, -39120, PATH_NODE_STATION,
	-109276, -82131, -80103, -17628, -203568, -124712, -39728, -265000, 129620, -386012, PATH_NODE_WRAP,

	// train 2 (n 31)
	80, 130, 0,
	-158928, 189219, -123684, 246995, PATH_NODE_CYCLE,

	// train 3 (n 39)
	0, 90, 0x8000,
	188402, -425768, 354291, PATH_NODE_WRAP,

	// train 4 (n 46)
	0, 90, 0x8000,
	354291, -425168, 188402, PATH_NODE_WRAP,

	// train 5 (n 53)
	60, 110, 0,
	-386012, 130215, -264404, -39132, -124688, 16619, -139048, 72943, -159520, 282863, PATH_NODE_STATION,
	-204991, -220964, 336284, PATH_NODE_WRAP,

	// train 6 (n 71)
	70, 120, 0,
	-82719, -39712, PATH_NODE_STATION,
	-115487, -124120, -202968,-18216, -80683, PATH_NODE_CYCLE
};

int VegasTrainData[7] = {
	0, 123, 0x8000,
	982000, -68855, 762717, PATH_NODE_WRAP
};

int VegasParkedTrains[3] = {
	-68855, 975520, 792317
};

// [A] monorail
int VegasMonorailData[] = {
	20, 70, 0x18000, // cycle flag. Cannot be used for event itself
	-70500, -67510, -111000, PATH_NODE_REVERSE, -70500, PATH_NODE_WRAP,
};

int HavanaFerryData[] = {
	40, 0, 64, 425555, -452, 20000,		// Ferry 1
	25, 0, 64, 315750, 130740, 135960	// Ferry 2
};

int RioFerryData[6] = {
	6, 0, 0, 200384, 387424, 410000
};

int HavanaMiniData[4] = {
	50, 3995, 4605, 0
};

int LiftingBridges[55] = {
	8,	// bridge count

	// 1
	-182784, -175616, -168448,
	7, -227328, -162304, -141824, -121344, -100864, -80384, -59904,

	0x100, // goose island start

	// 2
	-312832, -305664, -298496, 
	1, 324096,

	// 3
	-311808, -304640, -297472,
	1, 247296,

	// 4
	-256512, -249344, -242176,
	1, 247296,

	// 5
	-262656, -255488, -248320,
	1, 324096,

	0x8000,	// goose island end

	// 6
	170496, 177664, 184832,
	1, -271360,

	// 7
	-12800, -5632, 1536,
	5, -162304, -102912, -82432, -61952, -39936,

	// 8
	-6656, 512, 7680,
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
	800,
	0,
	25,
	50,
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
	2496,
	4096,
	25,
	50,
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
	0,
	0,
	0,
	0,
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
	0,
	0,
	0,
	0,
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
	1152,
	0,
	10,
	20,
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
	3200,
	4096,
	25,
	50,
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
	1600,
	0,
	25,
	50,
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
	1748,
	3072,
	25,
	50,
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
	2348,
	1024,
	25,
	50,
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
	700,
	2048,
	25,
	50,
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
	900,
	0,
	25,
	50,
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
static int doneFirstHavanaCameraHack = 0;
SVECTOR boatOffset;
static FixedEvent* fixedEvent = NULL;

#ifndef PSX
BOAT_CARS carsOnBoat;
#else
int carsOnBoat = 0;
#endif

MultiCar multiCar;

EVENT* firstEvent;
EVENT* firstMissionEvent;
EVENT* event;

static EventCamera eventCamera;

void MakeEventTrackable(EVENT* ev);

#ifdef PSX
#define EVENT_DRAW_DISTANCE VIEW_DRAW_DISTANCE
#else
#define EVENT_DRAW_DISTANCE 15000 // [A] world becomes repetetive if further :(
#endif // PSX

// [D] [T]
int GetVisValue(int index, int zDir)
{
	int camera;
	int radius;
	EVENT* ev;
	VECTOR pos;

	if (index & 0xC000)
	{
		camera = (index >> 15 ^ 1) & 1;
		radius = EVENT_DRAW_DISTANCE;

		if (zDir == 0)
		{
			pos.vx = player[camera].cameraPos.vx;
		}
		else
		{
			pos.vx = player[camera].cameraPos.vz;
		}
	}
	else
	{
		int multiple;

		if (index & 0x80)
			ev = (EVENT*)&fixedEvent[index & 127];
		else
			ev = &event[index & 127];

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
		do
		{
			for (j = 0; j < count; j++)
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
			}
		} while (++num < 2);

		for (num = 0; num < NumPlayers; num++)
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

		for (num = 0; num < NumPlayers; num++)
		{
			firstX[num] = xList;
			firstZ[num] = zList;
		}
	}
	else if (type == VIS_ADD)
	{
		if (i & 0x80)
			ev = (EVENT*)&fixedEvent[i & 127];
		else
			ev = &event[i & 127];

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
		if(ev->data == VegasMonorailData) // [A]
		{
			length = 1850;
			height = -1100;
		}
		else
		{
			length = 3700;
			height = -734;
		}

		ev->rotation = 0;
	}

	ev->position.vy = height;

	ev->flags &= ~0x7000;

	if (ev->node[3] != PATH_NODE_WRAP && ev->node[3] != PATH_NODE_REVERSE)
		ev->flags |= 0x3000;

	to = ev->node;

	// get direction sign
	if (to[2] == PATH_NODE_STATION)
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

// [A]
void AddEvent(EVENT *ev, EVENT*** e)
{
	**e = ev;
	*e = &ev->next;
}

// [A]
void NewEvent(EVENT *ev, EVENT*** e)
{
	**e = ev;
	ev->next = &ev[1];
	
	*e = &(ev->next)->next;
}

// [D] [T]
void InitDoor(FixedEvent* ev, EVENT*** e, int* cEvents)
{
	ev->active = 0;
	ev->rotation = ev->finalRotation;
	ev->flags |= 0x200;

	AddEvent((EVENT*)ev, e);

	VisibilityLists(VIS_ADD, (ev - fixedEvent) | 0x80);
}

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
#ifndef PSX
	ClearMem((char*)&carsOnBoat, sizeof(BOAT_CARS)); // clear count + array
#else
	carsOnBoat = 0;
#endif
	doneFirstHavanaCameraHack = 0;

	boatOffset.vx = 0;
	boatOffset.vy = 0;
	boatOffset.vz = 0;

	VisibilityLists(VIS_INIT, 0);
	TriggerEvent(-1);
}

// [D] [T]
void BoatOffset(SVECTOR* offset, EVENT* ev)
{
	offset->vx = 0;
	offset->vy = -ev->data[2];
	offset->vz = ev->data[4] - ev->position.vz;
}

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

	// Multiplayer level loaded?
	if (!doSpooling)
	{
		firstEvent = NULL;
		EventCop = NULL;
		return;
	}

	D_MALLOC_BEGIN()

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
		for (n = 0; n < cBridges; n++)
		{
			int timeOffset;
			cameraEventsActive = 1;

			// goose island bridges start/end?
			if (p[0] == 0x100)
			{
				firstMissionEvent = &event[cEvents];
				p++;
			}
			else if (p[0] == 0x8000)
			{
				direction = true;
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
					evt[i].flags = 0x1;
					evt[i].position.vx = p[0];
				}
				else
				{
					evt[i].flags = 0x21;
					evt[i].position.vz = p[0];
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

			NewEvent(evt, &e);
			
			cEvents += 2;
		}

		if (full)
			ElTrackModel = FindModelIdxWithName("ELTRAIN");

		p = ElTrainData;
		
		count = p[0];

		missionTrain[0].engine = &event[cEvents];
		missionTrain[1].engine = &event[cEvents];

		// add trains
		for (n = 0; n < count - 1; n++)
		{
			// randomize carriage count
			if (n != 0)
				i = (Random2(0) >> (n & 0x1f) & 3) + 2;
			else
				i = 5;

			direction = 1;
			p++;

			while (--i >= 0)
			{
				evt = &event[cEvents];
				evt->radius = 0;
				evt->data = p;
				evt->position.pad = p - ElTrainData;

				InitTrain(evt, i, 0);

				if (direction)
				{
					direction = 0;
					evt->flags |= 0x400;
				}

				if (full)
					evt->model = ElTrackModel;

				AddEvent(evt, &e);
				
				VisibilityLists(VIS_ADD, cEvents);

				cEvents++;
			}

			// skip PATH_NODE_STATION, PATH_NODE_REVERSE
			while (p[1] + PATH_NODE_WRAP > 1)
				p++;
		}

		fixedEvent = chicagoDoor;

		InitDoor(&chicagoDoor[0], &e, &cEvents);
		InitDoor(&chicagoDoor[1], &e, &cEvents);

		AddEvent((EVENT*)&chicagoDoor[2], &e);
		
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
		cameraEventsActive = 1;

		event[0].radius = 0;
		event[0].position.vy = 111;
		event[0].position.vx = HavanaFerryData[3];
		event[0].position.vz = HavanaFerryData[4];
		event[0].rotation = 3072;
		event[0].flags = -0x77ad;
		event[0].timer = -1;
		event[0].node = HavanaFerryData + 4;
		event[0].data = HavanaFerryData;

		// [A] reset Ferry angles
		event[0].data[1] = RSIN(CameraCnt * 32) >> 9;
		event[0].data[2] = RCOS(CameraCnt * 16) + 4096 >> 7;

		VisibilityLists(VIS_ADD, 0);
		MakeEventTrackable(event);

		AddEvent(event, &e);

		fixedEvent = havanaFixed;
		
		InitDoor(&havanaFixed[0], &e, &cEvents);
		InitDoor(&havanaFixed[2], &e, &cEvents);

		AddEvent((EVENT*)&havanaFixed[1], &e);
		
		VisibilityLists(VIS_ADD, 129);

		event[1].flags = 0x4212;
		event[1].node = HavanaMiniData + 1;
		event[1].position.vy = 3995;
		event[1].position.vx = -455167;
		event[1].position.vz = -125439;
		event[1].rotation = 0;
		event[1].timer = -1;
		event[1].radius = 0;
		event[1].data = HavanaMiniData;

		VisibilityLists(VIS_ADD, 1);

		AddEvent(&event[1], &e);
		
		cEvents = 2;

		if (full)
		{
			event[0].model = FindModelIdxWithName("FERRY");
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

			AddEvent(&evt[i], &e);			
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

		// [A] Init cut Vegas monorail
		if (full)
			trainModel = FindModelIdxWithName("MONORAIL");

		evt = &event[cEvents];
		
		// [A] add monorail. More than two for some unknown reason are not visible
		cCarriages = 2;

		for (i = 0; i < cCarriages; i++)
		{
			evt[i].radius = EVENT_RADIUS;
			evt[i].position.vx = VegasMonorailData[4];
			evt[i].position.vz = VegasMonorailData[3];
			evt[i].data = VegasMonorailData;

			InitTrain(&evt[i], i, 1);

			VisibilityLists(VIS_ADD, cEvents+i);

			if (full)
				evt[i].model = trainModel;

			AddEvent(&evt[i], &e);
		}

		evt->flags |= 0x500;

		// zero first and last train links
		evt[cCarriages - 1].next = NULL;
		evt[1].next = NULL;

		cEvents += cCarriages;
		evt = &event[cEvents];

		if (gCurrentMissionNumber == 30)
		{
			// Destroy the yard
			evt[0].position.vx = -12283;
			evt[0].position.vy = -275;
			evt[0].position.vz = 841243;

			evt[1].position.vx = -13482;
			evt[1].position.vy = -250;
			evt[1].position.vz = 841184;

			evt[2].position.vx = -14380;
			evt[2].position.vy = -276;
			evt[2].position.vz = 840579;

			i = 0;
			for (i = 0; i < 3; i++)
			{
				if (i == 2)
					evt[i].rotation = 0;
				else
					evt[i].rotation = 2048;

				evt[i].flags = 0x400;
				evt[i].radius = 0;
			}

			if (full)
			{
				detonatorModel = FindModelIdxWithName("DETONATOR");

				evt[0].model = detonatorModel;
				evt[1].model = detonatorModel;
				evt[2].model = detonatorModel;
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

		AddEvent(event, &e);

		cEvents = 1;
		fixedEvent = rioDoor;

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

			AddEvent(&event[cEvents++], &e);
		}
	}

	*e = NULL;

	if (full)
		mallocptr += cEvents * sizeof(EVENT);

	D_MALLOC_END();
}

// [D] [T]
void InitEventCamera(void)
{
	eventCamera.position = camera_position;
	eventCamera.yAng = camera_angle.vy;
	eventCamera.matrix = inv_camera_matrix;
	eventCamera.rotate = 1;
	events.camera = 1;
}

// [D] [T]
void ResetEventCamera(void)
{
	camera_position = eventCamera.position;
	camera_angle.vy = eventCamera.yAng;
	inv_camera_matrix = eventCamera.matrix;
	events.camera = 0;
}

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

		InitMatrix(matrix);

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

// [D] [T]
void EventCollisions(CAR_DATA* cp, int type)
{
#ifndef PSX
	if (carsOnBoat.count == 0 || carsOnBoat.cars[CAR_INDEX(cp)] == 0)
		return;
#else
	if (carsOnBoat >> CAR_INDEX(cp) == 0)
		return;
#endif

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

// [D] [T]
void NextNode(EVENT* ev)
{
	if (ev->node[2] == PATH_NODE_STATION || ev->node[2] == PATH_NODE_REVERSE)
	{
		ev->node = &ev->node[2];
	}
	else
	{
		ev->node = &ev->node[1];
		ev->flags ^= 0x8000;
	}

	if (*ev->node == PATH_NODE_CYCLE)
	{
		ev->node = &ev->data[3];
	}
	else if (ev->node[3] == PATH_NODE_WRAP || ev->node[3] == PATH_NODE_REVERSE)
	{
		ev->flags &= ~0x7000;
		return;
	}

	ev->flags &= ~0x7000;
	ev->flags |= 0x3000;

	SetElTrainRotation(ev);
}

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
			curr = &ev->position.vx;
		else
			curr = &ev->position.vz;
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
			md = ((ev->data[0] - 1) * RSIN(md)) / 4096 + 1 ^ df;
	}
	else
	{
		if (md > 2048)
			md = ev->data[0] ^ df;
		else
			md = ((ev->data[0] - 1) * RSIN(md >> 1)) / 4096 + 1U ^ df;
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
				if(!(ev->data[2] & 0x10000))
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

	//
	// [A] completely custom code for Luxor Monorail because OG code for handling trains SUCKS!!!
	if(ev->data[2] & 0x10000)
	{
		from = ev->node;
		to = &from[2];
		
		if (flags & 0x8000)
			curr = &ev->position.vz;
		else
			curr = &ev->position.vx;

		i = &from[0];
		d = *to - *curr;

		if (d < 0)
			dir = -1;
		else
			dir = 1;

		d = ABS(d);
		d1 = ABS(*curr - *i);

		if (d1 > d)
			d1 = d;

		d = ABS(*curr - *i);

		if (d <= d1)
			d1 = d;

		if (ev->flags & 0x400)
			speed = ev->data[1];

		if ((d1 < 6000 && d1 < 8048) && (ev->flags & 0x400))
		{
			speed = ev->data[0] + (speed - ev->data[0]) * RSIN(((d1 - 2048) * 1024) / 8048) / 4096;
		}

		*curr += speed * dir;

		int dist = (*to - *curr) * dir;

		if(dist < (-dir)*2048 && ev->flags & 0x400)
		{
			EVENT* _evit = ev;

			do
			{
				_evit->flags &= ~0x100;
				_evit->timer = 300;

				// manually advance node
				do
				{
					_evit->node += 1;

					if (_evit->node[2] == PATH_NODE_WRAP)
					{
						// reinitialize if we reached WRAP
						_evit->node = &ev->data[3];
						break;
					}
				} while (_evit->node[2] == PATH_NODE_WRAP || _evit->node[2] == PATH_NODE_REVERSE);

				_evit = _evit->next;
			} while (_evit);
		
		}

		return;
	}
	
	from = ev->node;
	to = &from[2];
	
	if (*from == PATH_NODE_STATION)
	{
		station = EVENT_LEAVING;
		i = &from[1];
	}
	else
	{
		station = EVENT_APPROACHING;

		i = &from[0];

		if (from[2] == PATH_NODE_STATION)
		{
			to = &from[3];
		}
		else
		{
			station = EVENT_NO_STATION;

			if (from[-1] == PATH_NODE_STATION)
				i = &from[-2];
			else if (from[2] == PATH_NODE_CYCLE)
				to = &ev->data[3];
			else if (from[1] == PATH_NODE_CYCLE && &ev->data[3] < to)
				to = &ev->data[4];
		}
	}

	// move train
	if ((flags & 0x7000) == 0x1000)
	{
		u_int loop; // unsigned on purspose

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

		if (from[0] == PATH_NODE_STATION)
			i = &from[-2];

		while (loop < 4)
		{
			if (*i == PATH_NODE_CYCLE)
				i = &ev->data[3];
			else if (*i == PATH_NODE_STATION)
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
			speed = ev->data[0];

		offset.x = (ev->position.vz - centre.z) * speed / 2048;
		offset.z = (centre.x - ev->position.vx) * speed / 2048;

		if (((turn[2] - turn[0]) * offset.x + (turn[3] - turn[1]) * offset.z) * direction < 0)
		{
			offset.x = -offset.x;
			offset.z = -offset.z;
		}

		ev->position.vx += offset.x;
		ev->position.vz += offset.z;

		ev->rotation = ratan2(offset.x, offset.z) + 1024U & 4095;

		if (ev->flags & 0x8000)
		{
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
		}
		else
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
		}

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
				speed = ev->data[0] + (speed - ev->data[0]) * RSIN(((d1 - 2048) * 1024) / 8048) / 4096;
			}
		}
		else
		{
			// acceleration or slowdown
			speed = 5 + (speed - 5) * RSIN((d1 << 10) / 6000) / 4096;
		}
	}

	*curr += speed * dir;

	int dist = (*to - *curr) * dir;
	
	if (station == EVENT_NO_STATION && (ev->flags & 0x7000))
	{
		if (dist < 2048)
		{
			if ((ev->flags & 0x7000) == 0x3000)
			{
				ev->flags &= ~0x7000;
				ev->flags |= 0x1000;
			}
		}
		
		return;
	}

	if (dist < 0)
	{
		if (station == EVENT_NO_STATION)
		{
			// [A] preserve direction flag or train will get stuck
			// i might have been decompiled it wrong but now it works
			dir = ev->flags & 0x400;
			
			InitTrain(ev, 0, GameLevel == 0 ? 0 : 1);

			if (dir)
				ev->flags |= 0x400;
		}
		else if (ev->flags & 0x400)
		{
			ev->timer = 300;
		}
	}
}


// [D] [T]
int GetBridgeRotation(int timer)
{
	if (_CutRec_IsOn())
		return 0;

	if (gDisableChicagoBridges)
		return 0;

	if (timer > 2600)
		return 0;

	if (timer > 1600)
		timer = 2600 - timer;
	else if (timer > 1000)
		timer = 1000;

	return (4096 - RCOS((timer * 2048) / 1000)) * 800 / 8192;
}

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

		rot = ev->rotation;

		vz = vel.z * RCOS(rot) + vel.x * RSIN(rot);
		vx = vel.x * RCOS(rot) - vel.z * RSIN(rot);

		pitch = HelicopterData.pitch;

		if (ABS(vz) <= 900000)
			pitch = -HelicopterData.pitch - (RSIN((vz * 1024) / 900000) >> 3);
		else if (vz < 1)
			pitch = 512 - pitch;
		else
			pitch = -512 - pitch;

		roll = HelicopterData.roll;

		if (ABS(vx) <= 150000)
			roll = (RSIN((vx * 1024) / 150000) >> 3) - roll;
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

		HelicopterData.pitch = DIFF_ANGLES(-HelicopterData.dp, HelicopterData.pitch);// (HelicopterData.pitch + HelicopterData.dp + 2048U & 0xfff) - 2048;
		HelicopterData.roll = DIFF_ANGLES(-HelicopterData.dr, HelicopterData.roll); //(HelicopterData.roll + HelicopterData.dr + 2048U & 0xfff) - 2048;

		rot = DIFF_ANGLES(ev->rotation, ratan2(vel.x, vel.z)); //(ratan2(vel.x, vel.z) - ev->rotation + 2048U & 0xfff) - 2048;

		if (ABS(rot) > 512)
		{
			if (rot > 0)
				direction = 1024;
			else
				direction = -1024;
		}
		else
		{
			direction = RSIN(rot * 2) >> 2;
		}

		ev->rotation += FIXEDH(FIXEDH(direction * direction) * direction);
		ev->rotation &= 4095;

		if (GetSurfaceIndex(&ev->position) == -23)
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

				Setup_Smoke(&pos, 100, 500, SMOKE_WHITE, 0, &dummy, 0);
			}
		}
		else
		{
			if (ev->position.vy > -1000)
				ev->position.vy -= 10;
		}

		HelicopterData.lastX = ev->position.vx;
		HelicopterData.lastZ = ev->position.vz;

		SetMSoundVar((intptr_t)&ev->position, NULL);

		if ((ev->flags & 0x100) && (Random2(0) & 3) == (CameraCnt & 3U))
		{
			Setup_Smoke(&ev->position, 100, 500, SMOKE_BLACK, 0, &dummy, 0);
		}
	}

	if (ev->model == HelicopterData.deadModel)
	{
		pos.vy = -200;
		pos.vx = ev->position.vx + (rand() & 0xff) - 128;
		pos.vz = ev->position.vz + (rand() & 0xff) - 128;

		Setup_Smoke(&pos, 50, 100, SMOKE_FIRE, 0, &dummy, 0);
		Setup_Smoke(&pos, 100, 500, SMOKE_BLACK, 0, &drift, 0);

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
#ifndef PSX
	static BOAT_CARS onBoatLastFrame;
#else
	int onBoatLastFrame;
#endif
	int dist;
	int thisCamera, otherCamera;

	onBoatLastFrame = carsOnBoat;

	ev = firstEvent;

	if (detonator.timer)
		DetonatorTimer();

	while (ev)
	{
		//carsOnBoat = onBoatLastFrame;

		if (ev->flags & 2)
		{
			if (ev->flags & 0x40)
			{
				i = 0;
				cp = car_data;

#ifndef PSX
				ClearMem((char*)&carsOnBoat, sizeof(BOAT_CARS)); // clear count + array
#else
				carsOnBoat = 0;
#endif
				do {

					if (cp->controlType != CONTROL_TYPE_NONE &&
						OnBoat((VECTOR*)cp->hd.where.t, ev, &dist))
					{
#ifndef PSX
						carsOnBoat.cars[i] = 1;
						carsOnBoat.count++;
#else
						carsOnBoat |= 1 << i;
#endif
					}

					i++;
					cp++;
#ifndef PSX
				} while (i < MAX_CARS);
#else
				} while (i < MAX_CARS && i < 32);
#endif

				// make Tanner on boat also
				if (player[0].playerType == 2 && OnBoat((VECTOR*)player[0].pos, ev, &dist))
				{
#ifndef PSX
					carsOnBoat.cars[TANNER_COLLIDER_CARID] = 1;
					carsOnBoat.cars[CAMERA_COLLIDER_CARID] = 1;
					carsOnBoat.count += 2;
#else
					carsOnBoat |= (1 << TANNER_COLLIDER_CARID) | 0x200000;// 0x300000;
#endif
				}

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
				ev->data[1] = RSIN(CameraCnt * 32) >> 9;
				ev->data[2] = RCOS(CameraCnt * 16) + 4096 >> 7;

				if (detonator.timer - 1U < 159) // HMM?
				{
					int tmSqr;
					tmSqr = detonator.timer * detonator.timer;

					ev->data[1] -= RSIN(detonator.timer * 64) * tmSqr >> 18; //rcossin_tbl[(detonator.timer & 0x3fU) * 128] * tmSqr >> 0x12;
					ev->data[2] -= RSIN(detonator.timer * 64) * tmSqr >> 16; //rcossin_tbl[(detonator.timer & 0x3fU) * 128] * tmSqr >> 0x10;
				}

				if (foam.rotate & 0xffff7fffU) // HMMMMMM?
					foam.rotate--;
				else
					foam.rotate ^= ((Random2(0) & 0xf00) >> 8) + 8U | 0x8000;
			}

			// move cars on boats
#ifndef PSX
			if ((ev->flags & 0x40) && (carsOnBoat.count != 0 || onBoatLastFrame.count != 0))
			{
#else	
			if ((ev->flags & 0x40) && (carsOnBoat != 0 || onBoatLastFrame != 0))
			{
				int bit;
#endif

				speed.x = ev->position.vx - old.vx;
				speed.z = ev->position.vz - old.vz;

				// go thru cars
#ifndef PSX
				for (i = 0; i < MAX_CARS + 1; i++)
				{
#else
				for (i = 0; i < MAX_CARS + 1 && i < 32; i++)
				{
					bit = (1 << i);
#endif
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
#ifndef PSX
					if (carsOnBoat.cars[i])
#else
					if (carsOnBoat & bit)
#endif
					{
						pos->vx += speed.x;
						pos->vz += speed.z;

						if (i == TANNER_COLLIDER_CARID)
						{
							SetTannerPosition(pos);
#ifndef PSX
							carsOnBoat.cars[TANNER_COLLIDER_CARID] = 0;
							carsOnBoat.count--;
#else
							carsOnBoat &= ~(1 << TANNER_COLLIDER_CARID);
#endif
						}
#ifndef PSX
						else if (onBoatLastFrame.cars[i] == 0)
#else
						else if ((onBoatLastFrame & bit) == 0)
#endif
						{
							vel->vx -= speed.x * 4096;
							vel->vz -= speed.z * 4096;
						}

						// [A] this causes drifting, StepOneCar already does better job at updating this
						// car_data[i].st.n.fposition[0] = pos->vx << 4;
						// car_data[i].st.n.fposition[2] = pos->vz << 4;
					}
#ifndef PSX
					else if (vel && onBoatLastFrame.cars[i])
#else
					else if (vel && (onBoatLastFrame & bit))
#endif
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
					door->rotation += (door->minSpeed + (RSIN(rotAngle) * (door->maxSpeed - door->minSpeed) >> 0xc) ^ sign) - sign;

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
				chicagoDoor[2].rotation &= 4095;
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
						evt = &event[*x & 127];
					else
						evt = (EVENT*)&fixedEvent[*x & 127];

					// events that enable drawing
					if ((evt->flags & 0x204) == 0x200)
					{
						z = zVis;

						while ((*z & thisCamera) == 0)
						{
							if ((*z & otherCamera) == 0 && (*x & 4095) == (*z & 4095))
							{
								cop = &EventCop[event_models_active++];

								cop->pos.vx = evt->position.vx;
								cop->pos.vy = evt->position.vy;
								cop->pos.vz = evt->position.vz;
								cop->yang = (evt->rotation >> 6);
								cop->type = evt->model;

								// [A] train should be only dangerous in "Beat the train"
								if ((evt->flags & 0x12) == 2 && evt->data == VegasTrainData)
									cop->pad = 1;
								else
									cop->pad = 0;

								evt->flags |= 0x4;
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

// [D] [T]
void DrawFerrisWheel(MATRIX* matrix, VECTOR* pos)
{
	MODEL* model;
	int loop;
	int sn, cs, angle;
	int rotation;
	VECTOR offset;
	VECTOR carPos;

	if (chicagoDoor[2].model == -1)
		return;

	RenderModel(modelpointers[chicagoDoor[2].model], matrix, pos, 0, PLOT_NO_CULL, 1, 0);

	if (chicagoDoor[2].model != -1)
		RenderModel(modelpointers[chicagoDoor[2].initialRotation], NULL, NULL, 0, 0, 1, 0);

	matrix->m[0][0] = -matrix->m[0][0];
	matrix->m[1][0] = -matrix->m[1][0];
	matrix->m[2][0] = -matrix->m[2][0];

	RenderModel(modelpointers[chicagoDoor[2].model], matrix, pos, 0, PLOT_NO_CULL, 1, 0);

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
		angle = chicagoDoor[2].rotation + rotation;

		sn = RSIN(angle);
		cs = RCOS(angle);

		offset.vx = FIXEDH(spoke[0].vx * sn + spoke[1].vx * cs);
		offset.vy = FIXEDH(spoke[0].vy * sn + spoke[1].vy * cs);
		offset.vz = FIXEDH(spoke[0].vz * sn + spoke[1].vz * cs);

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

	InitMatrix(localMat);

	pos.vx -= camera_position.vx;
	pos.vy -= camera_position.vy;
	pos.vz -= camera_position.vz;

	_RotMatrixY(&localMat, HelicopterData.rotorrot & 4095);
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

#ifndef PSX
	if (gDemoLevel)
	{
		firstEvent = NULL;
		EventCop = NULL;
		return;
	}
#endif

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
				ev = &event[*x & 127];
			else
				ev = (EVENT*)&fixedEvent[*x & 127];

			z = zVis;

			while ((*z & thisCamera) == 0)
			{
				if ((*z & otherCamera) == 0 && (*x & 4095) == (*z & 4095))
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

							if (FrustrumCheck(&ev->position, modelpointers[ev->model]->bounding_sphere) != -1)
							{
								pos.vx = ev->position.vx - camera_position.vx;
								pos.vy = ev->position.vy - camera_position.vy;
								pos.vz = ev->position.vz - camera_position.vz;

								InitMatrix(matrix);
								
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
										pos.vy = (pos.vy - boatOffset.vy) + FIXEDH((int)ev->node * RSIN(*ev->data));
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
										_RotMatrixZ(&matrix, HelicopterData.roll & 4095);
										_RotMatrixX(&matrix, HelicopterData.pitch & 4095);
										_RotMatrixY(&matrix, ev->rotation & 4095);

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

									RenderModel(modelpointers[ev->model], &matrix, &pos, 400, PLOT_INV_CULL, 1, ev->rotation >> 6);
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

									if (gTimeOfDay != TIME_DAY)
										SetupPlaneColours(0x00282828);

									int flags = PLOT_TRANSPARENT;

									if (foam.rotate & 0x8000)
										flags |= PLOT_INV_CULL;

									RenderModel(foam.model, &matrix, &pos, 200, flags, 1, 0);
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

		d = ev->rotation;
		sin = RSIN(d);
		cos = RCOS(d);

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
		// make secret base solid due to we use surface Ids
		// Havana 3D occlusion was made simpler in Rev 1.1
		// this change was very sneaky
		if (i > 8)
			return plane;
		
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


			d = ev->data[1];

			sin = RSIN(d);
			cos = RCOS(d);

			offset = dist * -4096 + cos * -3328;

			if (GameLevel == 3 && offset > 0)
			{
				int sin2;
				d = 160 - ev->data[1];

				cos = RCOS(d);
				sin2 = RSIN(d);

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

// [D] [T]
void MakeEventTrackable(EVENT* ev)
{
	EVENT** p;

	p = trackingEvent;

	while (*p)
		p++;

	*p++ = ev;
	*p = NULL; // mark next free trackable event
}

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

	if ((GameLevel == 2 || GameLevel == 3) &&
		(i >= 1 && i <= 3)) // Vegas and Rio detonators
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
	else if (GameLevel == 0) // Chicago events
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

					if (missionTrain[i].node[0] - missionTrain[i].start > -1)
						offset = 1600;
					else
						offset = -1600;

					loop = 0;

					do {
						if (missionTrain[i].node[0] == PATH_NODE_STATION)
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
				TriggerDoor(&chicagoDoor[0], &stage[i], 1);
				break;
			case 6:
				TriggerDoor(&chicagoDoor[1], &stage[i], 1);
				break;
		}
	}
	else if (GameLevel == 1) // Havana events
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

				// [A] reset Ferry angles
				event->data[1] = RSIN(CameraCnt * 32) >> 9;
				event->data[2] = RCOS(CameraCnt * 16) + 4096 >> 7;

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
				break;
		}
	}
	else if (GameLevel == 2) // Vegas events
	{
		switch (i)
		{
			case 0:
				// start train
				for (loop = 0; loop < 9; loop++)
				{
					ev = &event[loop];

					ev->data = VegasTrainData;

					InitTrain(ev, loop, 1);

					ev->flags |= 0x200;

					if (loop > 1)
						VisibilityLists(VIS_ADD, loop);
				}

				event->flags |= 0x500;

				MakeEventTrackable(ev);

				event[1].next = &event[2];
				break;
			case 4:
				TriggerDoor(&vegasDoor[0], &stage[i], 0);
				break;
			case 5:
			case 6:
			case 7:
				// trigger doors 1-3
				TriggerDoor(&vegasDoor[i - 4], &stage[i], 1);
				break;
			case 8:
				events.cameraEvent = (EVENT*)&vegasDoor[4];
				PrepareSecretCar();
				TriggerDoor(&vegasDoor[4], &stage[i], 1);
				break;
			case 9:
				SetMSoundVar(5, NULL);
				break;
		}
	}
	else if (GameLevel == 3) // Rio events
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
				// police station garage
				TriggerDoor(&rioDoor[0], &stage[i], 1);
				break;
			case 6:
				// police station door
				TriggerDoor(&rioDoor[1], &stage[i], 0);
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
				break;
		}
	}

	if (i < 10)
		stage[i]++;

	return pos;
}

// [D] [T]
void OffsetTarget(VECTOR* target)
{
	target->vx -= boatOffset.vx;
	target->vy -= boatOffset.vy;
	target->vz -= boatOffset.vz;
}

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
				events.cameraEvent = HARDCODED_CAMERA_EVENT;
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
					events.cameraEvent = HARDCODED_CAMERA_EVENT;
				}
				else
				{
					hackCamera = &VegasCameraHack[9];
				}
			}
			else if (gCurrentMissionNumber == 22)
			{
				hackCamera = &VegasCameraHack[13];

				events.cameraEvent = HARDCODED_CAMERA_EVENT;
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
			camera_position.vx = event->position.vx + boat[0];
			camera_angle.vy = boat[1];
			camera_position.vz = event->position.vz + boat[2];
		}

		player[0].cameraPos = camera_position;

		if (events.cameraEvent != NULL)
		{
			gStopPadReads = 1;
		}
	}

	if (type != SPECIAL_CAMERA_WAIT)
	{
		Havana3DLevelDraw = -1;
		camera_change = 1;
		
		VisibilityLists(VIS_SORT, 0);
	}
}

// [D] [T]
void ScreenShake(int count, SVECTOR* ang)
{
	eventHaze = count * 4;

	camera_angle.vx = (ang->vx + (Random2(0) % (eventHaze / 2))) - eventHaze;
	camera_angle.vy = (ang->vy + (Random2(0) % (eventHaze * 2))) - eventHaze;

	eventHaze *= 3;
}

// [D] [T]
int DetonatorTimer(void)
{
	static SVECTOR rememberCameraAngle; // offset 0x30
	static int count = 0; // offset 0x38

	EVENT* ev;
	VECTOR pos;

	if (gCurrentMissionNumber == 23)
	{
		if (detonator.timer > 2 && detonator.timer < 18)
		{
			ScreenShake(detonator.timer - 2, &rememberCameraAngle);
		}
		else if (detonator.timer <= 30 || detonator.timer >= 40)
		{
			if (detonator.timer == 0)
			{
				SetSpecialCamera(SPECIAL_CAMERA_SET, 0);
				detonator.timer = 70;
			}
			else if (detonator.timer == 21)
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
					
					Mission.timer[0].flags &= ~TIMER_FLAG_BOMB_COUNTDOWN;
					
					SetMissionComplete();
				}
				else
				{
					detonator.timer++;
				}

				player[0].cameraPos.vz = camera_position.vz;
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
		if (detonator.timer > 140 && detonator.timer < 160)
		{
			ScreenShake(detonator.timer - 140, &rememberCameraAngle);
			Setup_Smoke(&firstMissionEvent[0].position, 100, 500, SMOKE_BLACK, 0, &dummy, 0);
		}
		else
		{
			if (detonator.timer == 167)
			{
				ev = &firstMissionEvent[1];
				ev++;
			}
			else if (detonator.timer < 168)
			{
				if (detonator.timer == 0)
				{
					ev = &firstMissionEvent[0];

					if (detonator.count < 3)
					{
						while (--detonator.count != -1)
						{
							AddExplosion(ev->position, BIG_BANG);
							ev++;
						}

						return 0;
					}

					detonator.timer = 200;
					SetSpecialCamera(SPECIAL_CAMERA_SET, 0);
					events.cameraEvent = HARDCODED_CAMERA_EVENT;

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
			else
			{
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

// [D] [T]
void MultiCarEvent(MS_TARGET* target)
{
	EVENT* first;
	int n;
	EVENT* ev;
	MULTICAR_DATA* mcd;
	int i;

	first = firstEvent;

	// [A] validate
	if (target->type != Target_MultiCar)
		return;
	
	firstEvent = multiCar.event + multiCar.count;

	for (i = 0; i < 5; i++)
	{
		mcd = &target->multiCar[i];

		if (mcd->x == 0x80000000)
			break;
		
		n = (multiCar.event - event) + multiCar.count;

		ev = event + n;

		ev->position.vx = mcd->x;
		ev->position.vz = mcd->z;
		
		ev->position.vy = -312;
	
		ev->rotation = mcd->rot;

		VisibilityLists(VIS_ADD, n);

		multiCar.count++;
	}

	//firstEvent->next = first; // [A] bug fix
	multiCar.event[multiCar.count - 1].next = first;
}

extern int MRProcessTarget(MR_THREAD * thread, MS_TARGET * target);

int user_events_allowed = 0;

int FindFreeTargets(MS_TARGET **targets, int count, int index)
{
	if (targets == NULL || count == 0 || index >= MAX_MISSION_TARGETS)
		return -1;

	int found = 0;

	for (int i = index; i < MAX_MISSION_TARGETS && found < count; i++)
	{
		MS_TARGET *target = &MissionTargets[i];

		if (target->type == 0)
			targets[found++] = target;
	}

	return found;
}

int EmptyMissionEvents(MR_THREAD *thread, int init)
{
	return 0;
}

int ChicagoTAREvents(MR_THREAD *thread, int init)
{
	if (init)
	{
		printInfo("**** CHICAGO TAR EVENT SETUP\n");

		if (gCurrentMissionNumber == 50 || gCurrentMissionNumber == 51)
			return 1;
	}

	return 0;
}

int HavanaTAREvents(MR_THREAD *thread, int init)
{
	static MS_TARGET *safehouse_targets[4];
	static int targets;
	static int cars_to_spawn;
	static int door_state;

	if (init)
	{
		printInfo("**** HAVANA TAR EVENT SETUP\n");

		safehouse_targets[0] = NULL;
		safehouse_targets[1] = NULL;
		targets = 0;
		cars_to_spawn = 0;
		door_state = 0;
		
		if (gCurrentMissionNumber == 52 || gCurrentMissionNumber == 53)
		{
			targets = FindFreeTargets(safehouse_targets, 4, 0);

			// need at least 2 free targets
			if (targets < 2)
				return 0;

			MS_TARGET *target = safehouse_targets[0];

			// outside switch
			target->type = Target_Point;
			target->s.target_flags = 0x400000;
			target->s.display_flags = 0;
			target->s.point.posX = -182450;
			target->s.point.posZ = -41235;
			target->s.point.radius = 150;
			target->s.point.actionFlag = 0x310003;

			// inside switch
			target++;
			target->type = Target_Point;
			target->s.target_flags = 0x400000;
			target->s.display_flags = 0;
			target->s.point.posX = -182705;
			target->s.point.posZ = -41723;
			target->s.point.radius = 150;
			target->s.point.actionFlag = 0x310003;

			printInfo("**** Doors are ready!\n");

			if (targets == 4)
			{
				// random car 1
				target++;
				target->type = Target_Car;
				target->s.target_flags = 0;
				target->s.display_flags = 0;
				target->s.car.posX = -184200;
				target->s.car.posZ = -43680;
				target->s.car.rotation = 0;
				target->s.car.slot = -1;
				target->s.car.type = 1;
				target->s.car.flags = 32;

				// random car 2
				target++;
				target->type = Target_Car;
				target->s.target_flags = 0;
				target->s.display_flags = 0;
				target->s.car.posX = -181920;
				target->s.car.posZ = -43400;
				target->s.car.rotation = -1536;
				target->s.car.slot = -1;
				target->s.car.type = 1;
				target->s.car.flags = 32;

				cars_to_spawn = 2;

				printInfo("**** Cars are ready!\n");
			}

			return 1;
		}

		// setup failed!
		return 0;
	}

	// doors
	for (int i = 0; i < 2; i++)
	{
		if (MRProcessTarget(thread, safehouse_targets[i]))
		{
			TriggerEvent(2);
			
			if (i == 0)
				door_state = (door_state == 0) ? 1 : 0;
			else if (i == 1)
				door_state = (door_state == 1) ? 0 : 1;

			printWarning("**** DOOR IS NOW %s\n", (door_state == 1) ? "OPEN" : "CLOSED");
		}
	}

	if (door_state == 1 && cars_to_spawn > 0)
	{
		VECTOR tv;

		for (int j = 0; j < cars_to_spawn; j++)
		{
			MS_TARGET *target = safehouse_targets[j + 2];

			if (!(target->s.target_flags & TARGET_FLAG_CAR_PINGED_IN))
			{
				printWarning("**** REQUESTING RANDOM SPAWN OF CAR %d\n", j);

				int model = 0;
				int pal = Random2(0) % 6;
				int rm = Random2(0) % 3;

				// only request available civ cars (no cops or specials)
				if (rm > 2)
					rm = 2;

				model = MissionHeader->residentModels[rm];

				target->s.car.model = model;
				target->s.car.palette = pal;

				MRProcessTarget(thread, target);
				return 0;
			}
		}

		// door is opened and all cars are spawned
		cars_to_spawn = -cars_to_spawn;
	}
	else if (door_state == 0 && cars_to_spawn < 0)
	{
		// door is closed - check if all cars are spawned next time it opens
		cars_to_spawn = -cars_to_spawn;
	}

	return 0;
}

int VegasTAREvents(MR_THREAD *thread, int init)
{
	if (init)
	{
		printInfo("**** VEGAS TAR EVENT SETUP\n");

		if (gCurrentMissionNumber == 54 || gCurrentMissionNumber == 55)
			return 1;
	}

	return 0;
}

int RioTAREvents(MR_THREAD *thread, int init)
{
	if (init)
	{
		printInfo("**** RIO TAR EVENT SETUP\n");

		if (gCurrentMissionNumber == 56 || gCurrentMissionNumber == 57)
			return 1;
	}

	return 0;
}

typedef int userEventFunc(MR_THREAD *thread, int init);
typedef userEventFunc * (userEventFuncList)[4];

userEventFuncList fnTAREventHandlers[] = {
	ChicagoTAREvents,
	HavanaTAREvents,
	VegasTAREvents,
	RioTAREvents,
};

userEventFuncList fnNullMissionEventHandlers[] = {
	EmptyMissionEvents,
	EmptyMissionEvents,
	EmptyMissionEvents,
	EmptyMissionEvents,
};

userEventFuncList * fnMissionEventHandlers;

int StopUserMissionEvents(MR_THREAD *thread)
{
	return 1;
}

int RunUserMissionEvents(MR_THREAD *thread)
{
	if (gCurrentMissionNumber >= 50 && gCurrentMissionNumber <= 65)
		maxCopCars = 32;

	return (*fnMissionEventHandlers)[GameLevel](thread, 0);
}

int InitUserMissionEvents(MR_THREAD *thread)
{
	thread->stepFunc = RunUserMissionEvents;
	thread->stopFunc = StopUserMissionEvents;

	if (gCurrentMissionNumber >= 50 && gCurrentMissionNumber <= 57)
		fnMissionEventHandlers = fnTAREventHandlers;
	else
		fnMissionEventHandlers = fnNullMissionEventHandlers;

	user_events_allowed = (*fnMissionEventHandlers)[GameLevel](thread, 1);

	return 1;
}