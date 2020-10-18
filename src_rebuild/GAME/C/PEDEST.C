#include "DRIVER2.H"
#include "PEDEST.H"
#include "PLAYERS.H"
#include "MISSION.H"
#include "OBJCOLL.H"
#include "COSMETIC.H"
#include "MAIN.H"
#include "DR2ROADS.H"
#include "MOTION_C.H"
#include "CONVERT.H"
#include "SOUND.H"
#include "PAD.H"
#include "CIV_AI.H"
#include "GLAUNCH.H"
#include "CUTSCENE.H"
#include "CAMERA.H"
#include "PAUSE.H"
#include "AI.H"
#include "CARS.H"
#include "FELONY.H"
#include "JOB_FX.H"
#include "BCOLLIDE.H"
#include "MAP.H"
#include "SYSTEM.H"
#include "HANDLING.H"

#include "../ASM/ASMTEST.H"

#include "STRINGS.H"
#include "INLINE_C.H"


MODEL* pmTannerModels[17] = { 0 };
MODEL* pmJerichoModels[6] = { 0 };

void PedDoNothing(PEDESTRIAN* pPed);
void PedUserWalker(PEDESTRIAN* pPed);
void PedUserRunner(PEDESTRIAN* pPed);
void PedGetInCar(PEDESTRIAN* pPed);
void PedGetOutCar(PEDESTRIAN* pPed);
void PedCarryOutAnimation(PEDESTRIAN* pPed);
void CivPedDoNothing(PEDESTRIAN* pPed);
void CivPedWalk(PEDESTRIAN* pPed);
void CivPedSit(PEDESTRIAN* pPed);
void CivPedJump(PEDESTRIAN* pPed);
void PedPressButton(PEDESTRIAN* pPed);
void TannerSitDown(PEDESTRIAN* pPed);
void CopStand(PEDESTRIAN* pPed);
void CivGetIn(PEDESTRIAN* pPed);

pedFunc fpPedPersonalityFunctions[] = {
	PedDoNothing,
	PedUserWalker,
	PedUserRunner,
	PedGetInCar,
	PedGetOutCar,
	PedCarryOutAnimation,

	CivPedDoNothing,
	CivPedWalk,
	CivPedSit,
	CivPedJump,

	PedPressButton,
	TannerSitDown,

	CopStand,
	CivGetIn,
};

VECTOR tannerLookAngle = { 0, 0, 0, 0 };

const int tannerTurnMax = 16;
const int tannerTurnStep = 4;

int bKillTanner = 0;

SEATED_PEDESTRIANS* seated_pedestrian;	// lump
int seated_count;
int maxSeated;
static int numTannerPeds = 0;
static int numCopPeds = 0;
int pinginPedAngle = 0;

PEDESTRIAN pedestrians[MAX_PEDESTRIANS];

PEDESTRIAN* pUsedPeds = NULL;	// linked list of pedestrians
PEDESTRIAN* pFreePeds = NULL;
PEDESTRIAN* pHold = NULL;

int max_pedestrians;
int num_pedestrians;

char ping_in_pedestrians = 0;

int bKilled = 0;

PEDESTRIAN_ROADS pedestrian_roads;

unsigned long tannerPad;
extern short padd;
SVECTOR camAngle;
static int oldCamView;

// decompiled code
// original method signature: 
// void /*$ra*/ IHaveThePower()
 // line 1137, offset 0x0006dd34
	/* begin block 1 */
		// Start line: 1139
		// Start offset: 0x0006DD34
		// Variables:
	// 		struct _CAR_DATA *cp; // $t4

		/* begin block 1.1 */
			// Start line: 1152
			// Start offset: 0x0006DDB8
		/* end block 1.1 */
		// End offset: 0x0006DF20
		// End Line: 1170
	/* end block 1 */
	// End offset: 0x0006DF54
	// End Line: 1182

	/* begin block 2 */
		// Start line: 2274
	/* end block 2 */
	// End Line: 2275

	/* begin block 3 */
		// Start line: 2275
	/* end block 3 */
	// End Line: 2276

/* WARNING: Unknown calling convention yet parameter storage is locked */

int bPower = 0;
int oldWeather = 0;
int powerCounter = 0;

// [D] [T]
// Havana easter egg.
void IHaveThePower(void)
{
	_CAR_DATA* cp;
	long force[4] = { 0x9000, 0, 0, 0 };
	long point[4] = { 0, 0, 90, 0 };

	if (GameLevel != 1)
		return;

	if (player[0].pos[0] > -231749 || player[0].pos[0] < -232147 ||
		player[0].pos[2] < -236229 || player[0].pos[2] > -235831)
	{
		// if player gets out the zone, restore weather back
		if (bPower != 0)
		{
			bPower = 0;
			gWeather = oldWeather;
		}

		return;
	}

	if (tannerPad & 0x20)
	{
		if (bPower == 0)
		{
			oldWeather = gWeather;
			bPower = 1;
			gWeather = 1;
		}

		powerCounter++;

		// make cars go crazy
		if (powerCounter < 20)
		{
			cp = car_data;

			do {
				if (cp->controlType != CONTROL_TYPE_NONE)
				{
					cp->hd.acc[0] += force[0];
					cp->hd.acc[1] += force[1];
					cp->hd.acc[2] += force[2];

					cp->hd.aacc[0] += FIXEDH(point[1] * force[2] - point[2] * force[1]);
					cp->hd.aacc[1] += FIXEDH(point[2] * force[0] - point[0] * force[2]);
					cp->hd.aacc[2] += FIXEDH(point[0] * force[1] - point[1] * force[0]);
				}

				cp++;
			} while (cp < &car_data[MAX_CARS]);
		}

		if (powerCounter > 48)
			powerCounter = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessTannerPad(struct PEDESTRIAN *pPed /*$s1*/, unsigned long pad /*$a1*/, char PadSteer /*$a2*/, char use_analogue /*$a3*/)
 // line 1191, offset 0x0006df54
	/* begin block 1 */
		// Start line: 1192
		// Start offset: 0x0006DF54
		// Variables:
	// 		struct VECTOR vec; // stack offset -88
	// 		int mapheight; // $s2
	// 		struct VECTOR normal; // stack offset -72
	// 		struct VECTOR out; // stack offset -56
	// 		struct _sdPlane *SurfacePtr; // stack offset -24

		/* begin block 1.1 */
			// Start line: 1224
			// Start offset: 0x0006DFC8
			// Variables:
		// 		struct VECTOR tVec; // stack offset -40
		// 		struct _sdPlane *plane; // $v0
		// 		int mH; // $v1
		// 		int sI; // $a0
		/* end block 1.1 */
		// End offset: 0x0006E104
		// End Line: 1277

		/* begin block 1.2 */
			// Start line: 1359
			// Start offset: 0x0006E390
		/* end block 1.2 */
		// End offset: 0x0006E3F0
		// End Line: 1365
	/* end block 1 */
	// End offset: 0x0006E3F0
	// End Line: 1367

	/* begin block 2 */
		// Start line: 2378
	/* end block 2 */
	// End Line: 2379

	/* begin block 3 */
		// Start line: 2388
	/* end block 3 */
	// End Line: 2389

	/* begin block 4 */
		// Start line: 2397
	/* end block 4 */
	// End Line: 2398

// [D] [T]
void ProcessTannerPad(PEDESTRIAN* pPed, ulong pad, char PadSteer, char use_analogue)
{
	_sdPlane* SurfacePtr;
	int direction;
	VECTOR vec;
	VECTOR normal;
	VECTOR out;
	VECTOR tVec;
	_sdPlane* plane;
	_PLAYER* lcp;

	int padId;

	padId = ABS(pPed->padId);
	plane = NULL;

	lcp = &player[padId];

	// don't move dead Tanner
	if (lcp->dying != 0)
		tannerPad = 0;
	else
		tannerPad = pad;

	if (use_analogue)
	{
		tannerPad = pad;

		if (PadSteer != 0)
			tannerPad |= (PadSteer < 0) ? 0x8000 : 0x2000;
	}

	IHaveThePower();	// process Havana easter egg near the entrance cemetery

	vec.vx = pPed->position.vx;
	vec.vy = -pPed->position.vy;
	vec.vz = pPed->position.vz;

	direction = pPed->dir.vy - 0x800U & 0xfff;

	tVec.vx = vec.vx + (rcossin_tbl[direction * 2] * 5 >> 9);
	tVec.vy = vec.vy;
	tVec.vz = vec.vz + (rcossin_tbl[direction * 2 + 1] * 5 >> 9);

	bStopTanner = 0;

	int mapheight[2];

	mapheight[0] = -130 - MapHeight(&vec);
	mapheight[1] = -130 - MapHeight(&tVec);

	int dist = ABS(mapheight[1] - mapheight[0]);

	// check slope
	if (dist <= 1010)
	{
		SurfacePtr = sdGetCell(&tVec);

		if (SurfacePtr != NULL)
		{
			dist = ABS(((SurfacePtr->b >> 2) - 2048 & 0xfff) - 2048);

			if (dist <= 1100)
			{
				switch (SurfacePtr->surface)
				{
					case -32:
						break;
						//case 6:	// water. We allow to walk on water in Rio a little bit. Then he drowns
					case 9:		// water with fade out
					default:
						dist = -1;
						break;
				}
			}
		}
	}

	// can't walk in water
	if (dist != -1)
		bStopTanner = 1;

	if (pPed->type != PED_ACTION_SIT && !bStopTanner)
		pPed->position.vy = mapheight[0];

	// "Car Bomb" cutscene
	if (gInGameCutsceneActive && gCurrentMissionNumber == 23 &&
		gInGameCutsceneID == 0 && CameraCnt == 459 && pPed->pedType != TANNER_MODEL &&
		(!ActiveCheats.cheat12 || pPed->pedType != OTHER_MODEL))
	{
		lcp->pPed = NULL;
		lcp->playerType = 0;

		DestroyPedestrian(pPed);
		return;
	}

	// do actions
	if (tannerPad & 0x10)
	{
		if (gTannerActionNeeded)
		{
			// attempt to push a button
			switch (pPed->type)
			{
				case PED_ACTION_GETINCAR:
				case PED_ACTION_GETOUTCAR:
					// do not attempt
					break;
				default:
					// hey, wait -- TANNER!
					SetupPressButton(pPed);
					break;
			}
		}
		else
		{
			// priority. Try to get into car first
			// attempt to get into a car
			switch (pPed->type)
			{
				case PED_ACTION_GETINCAR:
				case PED_ACTION_GETOUTCAR:
					// do not attempt
					break;
				default:
					// enter the nearest car if possible
					if (!gCantDrive)
					{
						DeActivatePlayerPedestrian(pPed);
						break;
					}

					break;
			}

			// attempt to sit down
			switch (pPed->type)
			{
				case PED_ACTION_GETINCAR:
				case PED_ACTION_GETOUTCAR:
				case PED_ACTION_SIT:
					// do not attempt
					break;
				default:
					// sit his ass down
					if (FindTannerASeat(pPed) != NULL)
					{
						SetupTannerSitDown(pPed);
						break;
					}
			}
		}
	}

	if (pPed->fpAgitatedState != NULL)
		(*pPed->fpAgitatedState)(pPed);
	else
		(*pPed->fpRestState)(pPed);

	if (lcp->cameraView == 2 && pPed->type != PED_ACTION_GETINCAR)
	{
		if (oldCamView != lcp->cameraView)
		{
			camAngle.vx = camera_angle.vx;
			camAngle.vz = camera_angle.vz;
		}

		camAngle.vy = lcp->headPos - player[0].dir & 0xfff;
		TannerCameraHandler(pPed);
	}

	oldCamView = lcp->cameraView;
	TannerCollision(pPed);

	// chicago bridge slope
	if (GameLevel == 0)
	{
		FindSurfaceD2((VECTOR*)lcp->pos, &normal, &out, &plane);

		if (plane->surface != -1 && plane->surface < 32 && (plane->surface & 0x10))
		{
			pPed->position.vx += (normal.vx >> 6);
			pPed->position.vz += (normal.vz >> 6);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitTanner()
 // line 1375, offset 0x0006e408
	/* begin block 1 */
		// Start line: 1377
		// Start offset: 0x0006E408
	/* end block 1 */
	// End offset: 0x0006E5C4
	// End Line: 1433

	/* begin block 2 */
		// Start line: 2819
	/* end block 2 */
	// End Line: 2820

	/* begin block 3 */
		// Start line: 2820
	/* end block 3 */
	// End Line: 2821

	/* begin block 4 */
		// Start line: 2823
	/* end block 4 */
	// End Line: 2824

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitTanner(void)
{
	pmTannerModels[0] = FindModelPtrWithName("TORSO");
	pmTannerModels[1] = FindModelPtrWithName("HEAD");
	pmTannerModels[2] = FindModelPtrWithName("U_ARM_RIGHT");
	pmTannerModels[3] = FindModelPtrWithName("L_ARM_RIGHT");
	pmTannerModels[4] = FindModelPtrWithName("HAND_RIGHT");
	pmTannerModels[5] = FindModelPtrWithName("THIGH_RIGHT");
	pmTannerModels[6] = FindModelPtrWithName("CALF_RIGHT");
	pmTannerModels[7] = FindModelPtrWithName("FOOT_LEFT");
	pmTannerModels[8] = FindModelPtrWithName("U_ARM_LEFT");
	pmTannerModels[9] = FindModelPtrWithName("L_ARM_LEFT");
	pmTannerModels[10] = FindModelPtrWithName("HAND_LEFT");
	pmTannerModels[11] = FindModelPtrWithName("THIGH_LEFT");
	pmTannerModels[12] = FindModelPtrWithName("CALF_LEFT");
	pmTannerModels[13] = FindModelPtrWithName("FOOT_RIGHT");
	pmTannerModels[14] = FindModelPtrWithName("NECK");
	pmTannerModels[15] = FindModelPtrWithName("HIPS");
	pmTannerModels[16] = FindModelPtrWithName("BAG");

	pmJerichoModels[0] = FindModelPtrWithName("JERI_TORSO");
	pmJerichoModels[1] = FindModelPtrWithName("JERI_HEAD");
	pmJerichoModels[2] = FindModelPtrWithName("JERI_U_ARM_LEFT");
	pmJerichoModels[3] = FindModelPtrWithName("JERI_L_ARM_LEFT");
	pmJerichoModels[4] = FindModelPtrWithName("JERI_U_ARM_RIGHT");
	pmJerichoModels[5] = FindModelPtrWithName("JERI_L_ARM_RIGHT");

	SetSkelModelPointers(TANNER_MODEL);
	StoreVertexLists();

	numTannerPeds = 0;
	bKillTanner = 0;
	bKilled = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetTannerPosition(struct VECTOR *pVec /*$a0*/)
 // line 1440, offset 0x00072478
	/* begin block 1 */
		// Start line: 1441
		// Start offset: 0x00072478
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $a1
	/* end block 1 */
	// End offset: 0x00072500
	// End Line: 1459

	/* begin block 2 */
		// Start line: 11519
	/* end block 2 */
	// End Line: 11520

	/* begin block 3 */
		// Start line: 2880
	/* end block 3 */
	// End Line: 2881

	/* begin block 4 */
		// Start line: 11522
	/* end block 4 */
	// End Line: 11523

// [D] [T]
void SetTannerPosition(VECTOR* pVec)
{
	PEDESTRIAN* pPed;

	pPed = pUsedPeds;
	while (pPed)
	{
		if (pPed->pedType == TANNER_MODEL || ActiveCheats.cheat12 && pPed->pedType == OTHER_MODEL)
		{
			pPed->position.vx = pVec->vx;
			pPed->position.vy = -pVec->vy;
			pPed->position.vz = pVec->vz;

			player[0].pos[0] = pVec->vx;
			player[0].pos[1] = pVec->vy;
			player[0].pos[2] = pVec->vz;
		}

		pPed = pPed->pNext;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitPedestrians()
 // line 1466, offset 0x0006e5c4
	/* begin block 1 */
		// Start line: 1468
		// Start offset: 0x0006E5C4
		// Variables:
	// 		int loop; // $a1
	// 		struct SEATED_PEDESTRIANS *seatedptr; // $s2
	/* end block 1 */
	// End offset: 0x0006E6C4
	// End Line: 1513

	/* begin block 2 */
		// Start line: 2973
	/* end block 2 */
	// End Line: 2974

	/* begin block 3 */
		// Start line: 3007
	/* end block 3 */
	// End Line: 3008

	/* begin block 4 */
		// Start line: 3008
	/* end block 4 */
	// End Line: 3009

	/* begin block 5 */
		// Start line: 3009
	/* end block 5 */
	// End Line: 3010

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void InitPedestrians(void)
{
	int loop;
	SEATED_PEDESTRIANS* seatedptr;

	memset(pedestrians, 0, sizeof(pedestrians));
	DestroyPedestrians();

	PEDESTRIAN* lastPed = &pedestrians[0];

	lastPed->pPrev = NULL;

	for (loop = 1; loop < MAX_PEDESTRIANS; loop++)
	{
		PEDESTRIAN* currPed = &pedestrians[loop];

		lastPed->pNext = currPed;
		currPed->pPrev = lastPed++;
	}

	lastPed->pNext = NULL;

	pUsedPeds = NULL;
	pFreePeds = pedestrians;

	seated_count = 0;

	seatedptr = seated_pedestrian;
	if (seatedptr != NULL)
	{
		while (seatedptr->rotation != 9999)
		{
			seatedptr->index = 0;

			seated_count++;
			seatedptr++;
		}
	}

	maxSeated = seated_count;
	numTannerPeds = 0;
	pinginPedAngle = 0;
	pPlayerPed = NULL;
	seated_count = 0;
	ping_in_pedestrians = 1;
	numCopPeds = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DestroyPedestrians()
 // line 1521, offset 0x00071f54
	/* begin block 1 */
		// Start line: 1523
		// Start offset: 0x00071F54
	/* end block 1 */
	// End offset: 0x00071FB4
	// End Line: 1534

	/* begin block 2 */
		// Start line: 3042
	/* end block 2 */
	// End Line: 3043

	/* begin block 3 */
		// Start line: 8489
	/* end block 3 */
	// End Line: 8490

	/* begin block 4 */
		// Start line: 8491
	/* end block 4 */
	// End Line: 8492

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DestroyPedestrians(void)
{
	while (pUsedPeds)
	{
		if (pUsedPeds->pedType == TANNER_MODEL || ActiveCheats.cheat12 && pUsedPeds->pedType == OTHER_MODEL)
			numTannerPeds--;

		DestroyPedestrian(pUsedPeds);
	}

	num_pedestrians = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DestroyCivPedestrians()
 // line 1541, offset 0x00072fd0
	/* begin block 1 */
		// Start line: 1543
		// Start offset: 0x00072FD0
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $v1
	// 		struct PEDESTRIAN *pHPed; // $s0
	/* end block 1 */
	// End offset: 0x00073038
	// End Line: 1559

	/* begin block 2 */
		// Start line: 3082
	/* end block 2 */
	// End Line: 3083

	/* begin block 3 */
		// Start line: 19292
	/* end block 3 */
	// End Line: 19293

	/* begin block 4 */
		// Start line: 19296
	/* end block 4 */
	// End Line: 19297

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DestroyCivPedestrians(void)
{
	PEDESTRIAN* pPed;
	PEDESTRIAN* pHPed;

	pPed = pUsedPeds;
	while (pPed != NULL)
	{
		pHPed = pPed->pNext;

		if (pPed->pedType == CIVILIAN)
		{
			DestroyPedestrian(pUsedPeds);
			num_pedestrians--;
		}

		pPed = pHPed;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DestroyPedestrian(struct PEDESTRIAN *pPed /*$a1*/)
 // line 1567, offset 0x00071fb4
	/* begin block 1 */
		// Start line: 1568
		// Start offset: 0x00071FB4

		/* begin block 1.1 */
			// Start line: 1605
			// Start offset: 0x00072064
			// Variables:
		// 		struct SEATED_PEDESTRIANS *seatedptr; // $a0
		/* end block 1.1 */
		// End offset: 0x00072090
		// End Line: 1608
	/* end block 1 */
	// End offset: 0x000720AC
	// End Line: 1616

	/* begin block 2 */
		// Start line: 8546
	/* end block 2 */
	// End Line: 8547

	/* begin block 3 */
		// Start line: 8580
	/* end block 3 */
	// End Line: 8581

// [D] [T]
void DestroyPedestrian(PEDESTRIAN* pPed)
{
	if (pPed->flags & 8)
		numCopPeds--; // or road block pedestrians

	pPed->flags = 0;
	pPed->dir.vz = 0;
	pPed->dir.vy = 0;
	pPed->dir.vx = 0;

	if (pPed == pUsedPeds)
	{
		pUsedPeds = pPed->pNext;

		if (pUsedPeds)	// [A] is this valid? Or it was by Reflections?
			pUsedPeds->pPrev = NULL;

		pPed->pNext = pFreePeds;

		if (pFreePeds)
			pFreePeds->pPrev = pPed;
	}
	else
	{
		if (pPed->pPrev)
			pPed->pPrev->pNext = pPed->pNext;

		if (pPed->pNext)
			pPed->pNext->pPrev = pPed->pPrev;

		pPed->pNext = pFreePeds;
		if (pFreePeds)
			pFreePeds->pPrev = pPed;
		pPed->pPrev = NULL;
	}

	pFreePeds = pPed;

	if (pPed->type == PED_ACTION_CIVSIT)
		seated_pedestrian[pPed->seat_index].index = 0;		// [A] removed check

	pPed->doing_turn = 0;

	num_pedestrians--;
}



// decompiled code
// original method signature: 
// int /*$ra*/ ActivatePlayerPedestrian(struct _CAR_DATA *pCar /*$s6*/, char *padId /*stack 4*/, int direction /*$a1*/, long (*position)[4] /*$a3*/, int playerType /*stack 16*/)
 // line 1623, offset 0x0006e6c4
	/* begin block 1 */
		// Start line: 1624
		// Start offset: 0x0006E6C4
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $s1
	// 		struct PEDESTRIAN *pSPed; // $a0
	// 		struct VECTOR v; // stack offset -72
	// 		int nx; // $s4
	// 		int nz; // $s2
	// 		long w; // $s0
	// 		long x; // $s5
	// 		long y; // stack offset -52
	// 		long z; // $s1
	// 		long d; // stack offset -48
	// 		int side; // $fp
	// 		int id; // $s3

		/* begin block 1.1 */
			// Start line: 1688
			// Start offset: 0x0006E7D4

			/* begin block 1.1.1 */
				// Start line: 1763
				// Start offset: 0x0006EA48
			/* end block 1.1.1 */
			// End offset: 0x0006EA48
			// End Line: 1763

			/* begin block 1.1.2 */
				// Start line: 1807
				// Start offset: 0x0006EB48
			/* end block 1.1.2 */
			// End offset: 0x0006EB48
			// End Line: 1807
		/* end block 1.1 */
		// End offset: 0x0006EB48
		// End Line: 1807
	/* end block 1 */
	// End offset: 0x0006EC88
	// End Line: 1835

	/* begin block 2 */
		// Start line: 3244
	/* end block 2 */
	// End Line: 3245

	/* begin block 3 */
		// Start line: 3355
	/* end block 3 */
	// End Line: 3356

	/* begin block 4 */
		// Start line: 3365
	/* end block 4 */
	// End Line: 3366

/* WARNING: Type propagation algorithm not settling */

// [D] [T]
int ActivatePlayerPedestrian(_CAR_DATA* pCar, char* padId, int direction, long(*position)[4], PED_MODEL_TYPES playerType)
{
	int wbody;
	int side;
	int dir;
	PEDESTRIAN* pedptr;
	int playerId;
	VECTOR* pos;
	VECTOR v;
	long y;
	long d;
	_PLAYER* lp;
	int x, z;

	if (numTannerPeds > 7)
		return 0;

	if (padId == NULL)
	{
		playerId = GetPlayerId(pCar);
		lp = &player[playerId];
	}
	else
	{
		playerId = ABS(*padId);

		pedptr = pUsedPeds;

		while (pedptr != NULL)
		{
			if (ABS(pedptr->padId) == playerId)
			{
				player[playerId].pPed = pedptr;
				return 0;
			}

			pedptr = pedptr->pNext;
		}

		lp = &player[playerId];
	}

	if (pCar == NULL)
	{
		x = (*position)[0];
		z = (*position)[2];

		wbody = 1;

		d = direction;
		y = 0;
	}
	else
	{
		x = pCar->hd.where.t[0];
		z = pCar->hd.where.t[2];

		y = pCar->hd.where.t[1];
		d = pCar->hd.direction;

		wbody = car_cosmetics[pCar->ap.model].colBox.vx;
	}

	wbody += 90;

	dir = d - 0x800;
	v.vy = y;
	v.vx = x - FIXED(wbody * rcossin_tbl[(d & 0xfffU) * 2 + 1]);
	v.vz = z + FIXED(wbody * rcossin_tbl[(d & 0xfffU) * 2]);

	side = 0;

	if (pCar != NULL)
	{
		if (QuickBuildingCollisionCheck(&v, dir, 10, 10, 10) != 0 || TannerCarCollisionCheck(&v, d, 1) != 0)
		{
			side = 1;

			v.vy = y;

			v.vx = x - FIXED(-wbody * rcossin_tbl[(d & 0xfffU) * 2 + 1]);
			v.vz = z + FIXED(-wbody * rcossin_tbl[(d & 0xfffU) * 2]);

			if (QuickBuildingCollisionCheck(&v, dir, 10, 10, 10) != 0)
				return 0;
			if (TannerCarCollisionCheck(&v, d, 1) != 0)
				return 0;
		}
	}

	pedptr = CreatePedestrian();
	numTannerPeds++;

	pedptr->interest = 0;		// idle timer
	pedptr->flags &= ~4;		// reverse animation

	if (padId == NULL)
		pedptr->padId = playerId;
	else
		pedptr->padId = *padId;

	if (pedptr)
		pos = (VECTOR*)&pedptr->position;
	else
		pos = NULL;

	if (pCar == NULL)
	{
		pedptr->type = PED_ACTION_BACK;
		pedptr->fpAgitatedState = NULL;
		pedptr->fpRestState = fpPedPersonalityFunctions[0];
	}
	else
	{
		pedptr->type = PED_ACTION_GETOUTCAR;
		pedptr->fpRestState = fpPedPersonalityFunctions[0];
		pedptr->fpAgitatedState = PedGetOutCar;
	}

	pedptr->position.vx = v.vx;
	pedptr->position.vz = v.vz;

	if (pCar != NULL)
		pedptr->position.vy = (pCar->hd).where.t[1];

	pedptr->position.vy = -130 - MapHeight(pos);
	pedptr->dir.vz = 0;
	pedptr->dir.vx = 0;
	pedptr->dir.vy = dir;
	pedptr->head_rot = 0;

	pPlayerPed = pedptr;
	lp->headTimer = 0;
	pedptr->pedType = playerType;
	SetupPedestrian(pedptr);

	if (pCar == NULL)
	{
		lp->cameraView = 0;
		lp->headPos = 0;
		lp->headTarget = 0;
		lp->headTimer = 0;
		lp->playerType = 2;
		lp->cameraAngle = dir;
		lp->cameraCarId = -1;
		lp->worldCentreCarId = -1;

		lp->pos[0] = pedptr->position.vx;
		lp->pos[1] = pedptr->position.vy;
		lp->pos[2] = pedptr->position.vz;

		lp->spoolXZ = pos;
		lp->pPed = pedptr;
		lp->onGrass = 0;
		lp->dir = d;

		pedptr->frame1 = 0;
		pedptr->speed = 0;

		if (playerType == OTHER_SPRITE)
		{
			if (gCurrentMissionNumber == 9)
			{
				pedptr->pallet = 68;
			}
			else
			{
				pedptr->pallet = ((Random2(0) % 3) + (Random2(0) % 3)) * 16;

				//rnd1 = Random2(0);
				//rnd2 = Random2(0);
				//pedptr->pallet = rnd1 - (rnd1 / 3) * 3 + (rnd2 - (rnd2 / 3) * 3) * 16;
			}
		}
	}
	else
	{
		MakeTheCarShutUp(playerId);
		Start3DSoundVolPitch(-1, 6, 2, lp->pos[0], lp->pos[1], lp->pos[2], 0, 0x1000);
		SetupGetOutCar(pedptr, pCar, side);

		//pedptr->padId = 0;
		lp->pPed = pedptr;

		SetConfusedCar(lp->playerCarId);
		StopPadVibration(0);
		StopPadVibration(1);

		lp->onGrass = 0;
	}

	pedptr->doing_turn = 0;

	gGotInStolenCar = 0;
	bKillTanner = 0;
	bKilled = 0;

	if (gCurrentMissionNumber == 23 && playerType != TANNER_MODEL)
	{
		pedptr->doing_turn = 16;
		pedptr->dir.vy = (pedptr->dir.vy - (tannerTurnMax + 16) * tannerTurnStep) + 294;
	}

	return 1;
}



// decompiled code
// original method signature: 
// struct PEDESTRIAN * /*$ra*/ CreatePedestrian()
 // line 1842, offset 0x000720ac
	/* begin block 1 */
		// Start line: 1844
		// Start offset: 0x000720AC
	/* end block 1 */
	// End offset: 0x00072114
	// End Line: 1869

	/* begin block 2 */
		// Start line: 8911
	/* end block 2 */
	// End Line: 8912

	/* begin block 3 */
		// Start line: 9138
	/* end block 3 */
	// End Line: 9139

	/* begin block 4 */
		// Start line: 9139
	/* end block 4 */
	// End Line: 9140

	/* begin block 5 */
		// Start line: 9141
	/* end block 5 */
	// End Line: 9142

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
PEDESTRIAN* CreatePedestrian(void)
{
	PEDESTRIAN* pNewPed;
	pNewPed = pFreePeds;

	if (pFreePeds != NULL)
	{
		if (pFreePeds->pNext != NULL)
			pFreePeds->pNext->pPrev = NULL;

		pFreePeds = pFreePeds->pNext;
		if (pUsedPeds != NULL)
			pUsedPeds->pPrev = pNewPed;

		pNewPed->pPrev = NULL;
		pNewPed->pNext = pUsedPeds;

		num_pedestrians++;
		pUsedPeds = pNewPed;

		return pNewPed;
	}

	return NULL;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PlaceRoadBlockCops()
 // line 1877, offset 0x0006ec88
	/* begin block 1 */
		// Start line: 1879
		// Start offset: 0x0006EC88
		// Variables:
	// 		struct _CAR_DATA *pCar; // $a0
	// 		struct _CAR_DATA (*pCopCars[16]); // stack offset -152
	// 		int numCops; // $fp

		/* begin block 1.1 */
			// Start line: 1896
			// Start offset: 0x0006ED1C
			// Variables:
		// 		int x; // $s2
		// 		int z; // $s0
		// 		int w; // $s0
		// 		int i; // $s7
		// 		int s1; // $s1
		// 		int s2; // $a3
		// 		struct VECTOR vert; // stack offset -88
		// 		long disp[4]; // stack offset -72
		// 		long dir[4]; // stack offset -56
		// 		int alpha; // $s1
		/* end block 1.1 */
		// End offset: 0x0006EFDC
		// End Line: 1966
	/* end block 1 */
	// End offset: 0x0006EFDC
	// End Line: 1968

	/* begin block 2 */
		// Start line: 4102
	/* end block 2 */
	// End Line: 4103

	/* begin block 3 */
		// Start line: 4145
	/* end block 3 */
	// End Line: 4146

	/* begin block 4 */
		// Start line: 4146
	/* end block 4 */
	// End Line: 4147

	/* begin block 5 */
		// Start line: 4150
	/* end block 5 */
	// End Line: 4151

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void PlaceRoadBlockCops(void)
{
	int wbody;
	int lbody;
	int cs, sn;
	uint dir;
	_CAR_DATA* cp;
	_CAR_DATA* pCar;
	int i;
	int numCops;
	_CAR_DATA* pCopCars[16];
	long disp[4];

	if (numCopPeds >= 8)
		return;

	numCops = 0;

	cp = car_data;
	do {
		if (cp->controlFlags & CONTROL_FLAG_COP_SLEEPING)
			pCopCars[numCops++] = cp;

		cp++;
	} while (cp < &car_data[MAX_CARS]);

	if (!numCops)
		return;

	i = 0;

	do {
		pCar = pCopCars[i];

		sn = rsin(pCar->hd.direction);
		cs = rcos(pCar->hd.direction);

		disp[0] = pCar->hd.where.t[0] - player[0].pos[0];
		disp[1] = player[0].pos[1] - pCar->hd.where.t[1];
		disp[2] = pCar->hd.where.t[2] - player[0].pos[2];

		lbody = car_cosmetics[pCar->ap.model].colBox.vz - 120;
		wbody = car_cosmetics[pCar->ap.model].colBox.vx + 400;

		if (FIXED(cs * 0x1000) * disp[0] - FIXED(sn * 0x1000) * disp[2] + 0x800 < 0)
			wbody = -wbody;

		dir = pCar->hd.direction + 0x800U & 0xfff;
		cs = rcossin_tbl[dir * 2 + 1];
		sn = rcossin_tbl[dir * 2];

		disp[0] = pCar->hd.where.t[0] - (FIXED(wbody * cs) - FIXED(lbody * sn));
		disp[1] = -pCar->hd.where.t[1];
		disp[2] = pCar->hd.where.t[2] + FIXED(wbody * sn) + FIXED(lbody * cs);

		if (CreatePedAtLocation((long(*)[4])disp, 12) != 0)
			numCopPeds++;

		disp[0] = pCar->hd.where.t[0] - (FIXED(wbody * cs) - FIXED(-lbody * sn));
		disp[1] = -pCar->hd.where.t[1];
		disp[2] = pCar->hd.where.t[2] + FIXED(wbody * sn) + FIXED(-lbody * cs);

		if (CreatePedAtLocation((long(*)[4])disp, 13) != 0)
			numCopPeds++;

		i++;
	} while (i < numCops);
}



// decompiled code
// original method signature: 
// int /*$ra*/ CreatePedAtLocation(long (*pPos)[4] /*$s2*/, int pedType /*$s1*/)
 // line 1975, offset 0x0006f00c
	/* begin block 1 */
		// Start line: 1976
		// Start offset: 0x0006F00C
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $s0
	/* end block 1 */
	// End offset: 0x0006F16C
	// End Line: 2045

	/* begin block 2 */
		// Start line: 4495
	/* end block 2 */
	// End Line: 4496

// [D] [T]
int CreatePedAtLocation(long(*pPos)[4], int pedType)
{
	PEDESTRIAN* pPed;

	if (num_pedestrians >= MAX_PLACED_PEDS)
		return 0;

	pPed = CreatePedestrian();

	if (pPed == NULL)
		return 0;

	pPed->position.vx = (*pPos)[0];
	pPed->position.vy = (*pPos)[1];
	pPed->position.vz = (*pPos)[2];

	pPed->pedType = CIVILIAN;

	pPed->dir.vz = 0;
	pPed->dir.vx = 0;
	pPed->dir.vy = 0;
	pPed->type = (PED_ACTION_TYPE)pedType;
	pPed->flags = 0;

	pPed->fpRestState = fpPedPersonalityFunctions[12];

	if (pedType == 8)
	{
		pPed->flags = 0;
		pPed->fpRestState = fpPedPersonalityFunctions[7];
	}
	else if (pedType >= 8 && pedType <= 13)
	{
		pPed->flags = 8;
		pPed->pallet = 85;
	}

	pPed->fpAgitatedState = NULL;
	SetupPedMotionData(pPed);

	if (pPed->type == PED_ACTION_COPSTAND)
	{
		pPed->position.vy = -(*pPos)[1];
		pPed->position.vy = -98 - MapHeight((VECTOR*)&pPed->position);
	}
	else  if (pPed->type == PED_ACTION_COPCROUCH)
	{
		pPed->position.vy = -(*pPos)[1];
		pPed->position.vy = -62 - MapHeight((VECTOR*)&pPed->position);
	}

	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawAllPedestrians()
 // line 2052, offset 0x00072290
	/* begin block 1 */
		// Start line: 2054
		// Start offset: 0x00072290
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $s0
	// 		int pedType; // $s2
	// 		struct MATRIX mStore; // stack offset -56

		/* begin block 1.1 */
			// Start line: 2071
			// Start offset: 0x0007231C

			/* begin block 1.1.1 */
				// Start line: 2078
				// Start offset: 0x0007234C
			/* end block 1.1.1 */
			// End offset: 0x0007234C
			// End Line: 2078
		/* end block 1.1 */
		// End offset: 0x00072364
		// End Line: 2085

		/* begin block 1.2 */
			// Start line: 2101
			// Start offset: 0x000723D4
		/* end block 1.2 */
		// End offset: 0x00072400
		// End Line: 2106
	/* end block 1 */
	// End offset: 0x00072430
	// End Line: 2137

	/* begin block 2 */
		// Start line: 12025
	/* end block 2 */
	// End Line: 12026

	/* begin block 3 */
		// Start line: 4104
	/* end block 3 */
	// End Line: 4105

	/* begin block 4 */
		// Start line: 12026
	/* end block 4 */
	// End Line: 12027

	/* begin block 5 */
		// Start line: 12031
	/* end block 5 */
	// End Line: 12032

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void DrawAllPedestrians(void)
{
	PEDESTRIAN* pPed;

	//MATRIX mStore;
	//gte_ReadRotMatrix(&mStore);

	pPed = pUsedPeds;
	while (pPed != NULL)
	{
		if (PositionVisible((VECTOR*)&pPed->position) &&
			FrustrumCheck((VECTOR*)&pPed->position, 60) != -1)
		{
			if (pPed->pedType <= OTHER_MODEL)
			{
				if (!bKillTanner)
					DrawTanner(pPed);
			}
			else if (pPed->pedType == OTHER_SPRITE)
			{
				DrawCharacter(pPed);
			}
			else
			{
				DrawCiv(pPed);
			}
		}

		pPed = pPed->pNext;
	}

	/*
	// THIS IS OLD AND PROBABLY NOT NEEDED
	gte_SetRotMatrix(&mStore);

	pPed = pUsedPeds;
	while (pPed != NULL)
	{
		if (pPed->pedType < OTHER_SPRITE && PedVisible(pPed, 60))
		{
			if (!bKillTanner)
				DrawTanner(pPed);
		}

		pPed = pPed->pNext;
	}*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ TannerActionHappening()
 // line 2145, offset 0x00072430
	/* begin block 1 */
		// Start line: 2147
		// Start offset: 0x00072430
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $a0
	/* end block 1 */
	// End offset: 0x00072478
	// End Line: 2158

	/* begin block 2 */
		// Start line: 12203
	/* end block 2 */
	// End Line: 12204

	/* begin block 3 */
		// Start line: 12212
	/* end block 3 */
	// End Line: 12213

	/* begin block 4 */
		// Start line: 12213
	/* end block 4 */
	// End Line: 12214

	/* begin block 5 */
		// Start line: 12215
	/* end block 5 */
	// End Line: 12216

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
int TannerActionHappening(void)
{
	PEDESTRIAN* pPed = player[0].pPed;

	if (pPed && pPed->type == PED_ACTION_PRESSBUTTON)
		return pPed->frame1 == 14;

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ControlPedestrians()
 // line 2168, offset 0x0006f16c
	/* begin block 1 */
		// Start line: 2170
		// Start offset: 0x0006F16C
		// Variables:
	// 		struct PEDESTRIAN *pPed; // $s0
	// 		struct PEDESTRIAN *pPedNext; // $s2
	// 		struct _CAR_DATA *pCar; // $v0

		/* begin block 1.1 */
			// Start line: 2225
			// Start offset: 0x0006F26C
		/* end block 1.1 */
		// End offset: 0x0006F2B0
		// End Line: 2233
	/* end block 1 */
	// End offset: 0x0006F2DC
	// End Line: 2241

	/* begin block 2 */
		// Start line: 4773
	/* end block 2 */
	// End Line: 4774

	/* begin block 3 */
		// Start line: 4897
	/* end block 3 */
	// End Line: 4898

	/* begin block 4 */
		// Start line: 4898
	/* end block 4 */
	// End Line: 4899

	/* begin block 5 */
		// Start line: 4902
	/* end block 5 */
	// End Line: 4903

/* WARNING: Unknown calling convention yet parameter storage is locked */

int bAvoidTanner = 0;
int bAvoidBomb = -1;

// [D] [T]
void ControlPedestrians(void)
{
	_CAR_DATA* pCar;
	PEDESTRIAN* pPed;
	PEDESTRIAN* pPedNext;

	pPed = pUsedPeds;

	while (pPed)
	{
		pPedNext = pPed->pNext;	// in case if ped gets removed

		if (pPed->pedType == CIVILIAN)
		{
			CalculatePedestrianInterest(pPed);

			if (pPed->fpAgitatedState == NULL)
				(*pPed->fpRestState)(pPed);
			else
				(*pPed->fpAgitatedState)(pPed);

			if (pPed->type != PED_ACTION_GETINCAR)
			{
				pCar = CheckForCar(pPed);

				if (pCar)
					SetupCivJump(pPed, pCar);
			}

			if (bAvoidTanner == 0)
			{
				if (bAvoidBomb != -1)
				{
					SetupCivJump(pPed, NULL);
					bAvoidBomb = -1;
				}
			}
			else
			{
				SetupCivJump(pPed, NULL);
				bAvoidTanner = 0;
			}
		}

		pPed = pPedNext;
	}

	pPed = pUsedPeds;

	// remove peds with PingOut
	while (pPed)
	{
		if (pPed->pedType == CIVILIAN && (PingOutPed(pPed) != 0 || (pPed->flags & 1U) != 0))
		{
			pHold = pPed->pNext;
			DestroyPedestrian(pPed);
			pPed = pHold;
		}
		else
		{
			pPed = pPed->pNext;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDoNowt(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2256, offset 0x00073038
	/* begin block 1 */
		// Start line: 20024
	/* end block 1 */
	// End Line: 20025

	/* begin block 2 */
		// Start line: 20722
	/* end block 2 */
	// End Line: 20723

// [D] [T]
void SetupDoNowt(PEDESTRIAN* pPed)
{
	pPed->speed = 0;
	pPed->dir.vz = 0;
	pPed->type = PED_ACTION_BACK;

	SetupPedMotionData(pPed);

	pPed->flags |= 0x10;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupWalker(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2275, offset 0x0007307c
	/* begin block 1 */
		// Start line: 20767
	/* end block 1 */
	// End Line: 20768

// [D] [T]
void SetupWalker(PEDESTRIAN* pPed)
{
	pPed->type = PED_ACTION_WALK;
	pPed->speed = 14;
	SetupPedMotionData(pPed);

	pPed->flags |= 0x10;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupRunner(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2291, offset 0x000730b8
	/* begin block 1 */
		// Start line: 20802
	/* end block 1 */
	// End Line: 20803

// [D] [T]
void SetupRunner(PEDESTRIAN* pPed)
{
	pPed->type = PED_ACTION_RUN;
	pPed->frame1 = 0;
	pPed->speed = 40;
	SetupPedMotionData(pPed);

	pPed->flags |= 0x10;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupBack(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2302, offset 0x000730fc
	/* begin block 1 */
		// Start line: 20826
	/* end block 1 */
	// End Line: 20827

// [D] [T]
void SetupBack(PEDESTRIAN* pPed)
{
	pPed->type = PED_ACTION_WALK;
	pPed->frame1 = 0;
	pPed->speed = -10;
	SetupPedMotionData(pPed);

	pPed->flags |= 0x10;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivGetIn(struct PEDESTRIAN *pPed /*$s2*/)
 // line 2325, offset 0x00072dfc
	/* begin block 1 */
		// Start line: 2326
		// Start offset: 0x00072DFC
		// Variables:
	// 		struct DRIVER2_STRAIGHT *str; // $s1
	// 		struct DRIVER2_CURVE *crv; // $s0

		/* begin block 1.1 */
			// Start line: 2326
			// Start offset: 0x00072DFC
		/* end block 1.1 */
		// End offset: 0x00072EE4
		// End Line: 2345
	/* end block 1 */
	// End offset: 0x00072EE4
	// End Line: 2346

	/* begin block 2 */
		// Start line: 18692
	/* end block 2 */
	// End Line: 18693

	/* begin block 3 */
		// Start line: 4650
	/* end block 3 */
	// End Line: 4651

	/* begin block 4 */
		// Start line: 18693
	/* end block 4 */
	// End Line: 18694

_CAR_DATA* pCivCarToGetIn = NULL;

// [D] [T]
void CivGetIn(PEDESTRIAN* pPed)		// [A] UNUSED
{
	uint padid;
	DRIVER2_CURVE* curve;
	DRIVER2_STRAIGHT* straight;

	straight = NULL;
	curve = NULL;

	InitCivState(pCivCarToGetIn, NULL);

	if (IS_STRAIGHT_SURFACE(pCivCarToGetIn->ai.c.currentRoad))
		straight = GET_STRAIGHT(pCivCarToGetIn->ai.c.currentRoad);
	else
		curve = GET_CURVE(pCivCarToGetIn->ai.c.currentRoad);

	pCivCarToGetIn->ai.c.currentLane = CheckChangeLanes(straight, curve, pCivCarToGetIn->ai.c.targetRoute[0].distAlongSegment, pCivCarToGetIn, 0);

	DestroyPedestrian(pPed);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CopStand(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2353, offset 0x00072da0
	/* begin block 1 */
		// Start line: 2354
		// Start offset: 0x00072DA0
		// Variables:
	// 		struct VECTOR v; // stack offset -24
	/* end block 1 */
	// End offset: 0x00072DFC
	// End Line: 2377

	/* begin block 2 */
		// Start line: 18683
	/* end block 2 */
	// End Line: 18684

	/* begin block 3 */
		// Start line: 4706
	/* end block 3 */
	// End Line: 4707

// [D] [T]
void CopStand(PEDESTRIAN* pPed)
{
	VECTOR v;
	v.vx = pPed->position.vx - player[0].pos[0];
	v.vz = pPed->position.vz - player[0].pos[2];

	pPed->frame1 = 0;
	pPed->dir.vy = 1024 - ratan2(v.vz, v.vx);
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedDoNothing(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2385, offset 0x0006f2dc
	/* begin block 1 */
		// Start line: 5187
	/* end block 1 */
	// End Line: 5188

	/* begin block 2 */
		// Start line: 5332
	/* end block 2 */
	// End Line: 5333

int iAllowWatch = 0;

// [D] [T]
void PedDoNothing(PEDESTRIAN* pPed)
{
	pPed->speed = 0;

	if ((pPed->flags & 0x10) == 0)
	{
		SetupDoNowt(pPed);
		pPed->flags |= 0x10;
	}

	if (tannerPad & 0x1040)
	{
		// run forward
		pPed->interest = 0;
		pPed->flags &= ~0x10;
		pPed->fpAgitatedState = fpPedPersonalityFunctions[2];

		SetupRunner(pPed);
	}
	else if (tannerPad & 0x4080)
	{
		// walk back
		pPed->interest = 0;
		pPed->flags &= ~0x10;
		pPed->fpAgitatedState = fpPedPersonalityFunctions[1];

		SetupBack(pPed);
	}
	else if (tannerPad & 0x2000)
	{
		pPed->interest = 0;

		pPed->doing_turn -= 2;

		if (pPed->doing_turn < -tannerTurnMax)
			pPed->doing_turn = -tannerTurnMax;

		pPed->dir.vy = pPed->dir.vy + 64 - (pPed->doing_turn + tannerTurnMax) * tannerTurnStep;

		if (pPed->frame1 == 0)
			pPed->frame1 = 15;
		else
			pPed->frame1--;

		pPed->head_rot = 0;
	}
	else if (tannerPad & 0x8000)
	{
		pPed->interest = 0;

		pPed->doing_turn += 2;

		if (pPed->doing_turn > tannerTurnMax)
			pPed->doing_turn = tannerTurnMax;

		pPed->dir.vy = pPed->dir.vy - 64 + (tannerTurnMax - pPed->doing_turn) * tannerTurnStep;

		if (pPed->frame1 > 14)
			pPed->frame1 = 0;
		else
			pPed->frame1++;

		pPed->head_rot = 0;
	}
	else
	{
		pPed->frame1 = 0;
		pPed->interest += 1;

		if (pPed->doing_turn < 0)
		{
			pPed->doing_turn += 2;

			if (pPed->doing_turn > 0)
				pPed->doing_turn = 0;
		}

		if (pPed->doing_turn > 0)
		{
			pPed->doing_turn -= 2;

			if (pPed->doing_turn < 0)
				pPed->doing_turn = 0;
		}

		if (pPed->doing_turn != 0)
		{
			if (pPed->doing_turn < 0)
				pPed->dir.vy = pPed->dir.vy + 64 - (pPed->doing_turn + tannerTurnMax) * tannerTurnStep;
			else
				pPed->dir.vy = pPed->dir.vy - 64 + (tannerTurnMax - pPed->doing_turn) * tannerTurnStep;
		}
	}

	if (pPed->interest > 119)
	{
		pPed->frame1 = 0;
		pPed->type = PED_ACTION_TIME;

		SetupPedMotionData(pPed);

		pPed->flags |= 0x10;
		pPed->fpAgitatedState = fpPedPersonalityFunctions[5];
		pPed->interest = -2;

		if (pPed->type == PED_ACTION_TIME)
			iAllowWatch = 3;

		if (iAllowWatch != 0)
			iAllowWatch--;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedUserRunner(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2523, offset 0x0006f5ac
	/* begin block 1 */
		// Start line: 2524
		// Start offset: 0x0006F5AC
	/* end block 1 */
	// End offset: 0x0006F80C
	// End Line: 2632

	/* begin block 2 */
		// Start line: 5640
	/* end block 2 */
	// End Line: 5641

// [D] [T]
void PedUserRunner(PEDESTRIAN* pPed)
{
	if ((pPed->flags & 0x10U) == 0)
	{
		SetupRunner(pPed);
	}

	if (tannerPad & 0x1040)
	{
		if (bStopTanner == 0)
			pPed->speed = 40 - (tannerDeathTimer >> 1);
		else
			pPed->speed = 0;
	}
	else
	{
		pPed->dir.vz = 0;
		pPed->speed = 0;
		pPed->fpAgitatedState = NULL;
		pPed->flags &= ~0x10;
	}

	if (tannerPad & 0x2000)
	{
		if (pPed->dir.vz > -80)
			pPed->dir.vz -= 20;

		pPed->doing_turn -= 2;

		if (pPed->doing_turn < -tannerTurnMax)
			pPed->doing_turn = -tannerTurnMax;

		pPed->head_rot = 0;
		pPed->dir.vy = pPed->dir.vy + 64 - (pPed->doing_turn + tannerTurnMax) * tannerTurnStep;
	}
	else if (tannerPad & 0x8000)
	{
		if (pPed->dir.vz < 80)
			pPed->dir.vz += 20;

		pPed->doing_turn += 2;

		if (pPed->doing_turn > tannerTurnMax)
			pPed->doing_turn = tannerTurnMax;

		pPed->head_rot = 0;
		pPed->dir.vy = pPed->dir.vy - 64 + (tannerTurnMax - pPed->doing_turn) * tannerTurnStep;
	}
	else
	{
		if (pPed->dir.vz < 0)
			pPed->dir.vz += 40;

		if (pPed->dir.vz > 0)
			pPed->dir.vz -= 40;

		if (pPed->doing_turn < 0)
		{
			pPed->doing_turn += 2;
			if (pPed->doing_turn > 0)
				pPed->doing_turn = 0;
		}

		if (pPed->doing_turn > 0)
		{
			pPed->doing_turn -= 2;

			if (pPed->doing_turn < 0)
				pPed->doing_turn = 0;
		}

		pPed->dir.vy = pPed->dir.vy - 64 + (tannerTurnMax - pPed->doing_turn) * tannerTurnStep;
	}

	AnimatePed(pPed);
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedUserWalker(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2639, offset 0x00072944
	/* begin block 1 */
		// Start line: 2640
		// Start offset: 0x00072944
		// Variables:
	// 		static int speed; // offset 0x80
	/* end block 1 */
	// End offset: 0x00072A10
	// End Line: 2694

	/* begin block 2 */
		// Start line: 17115
	/* end block 2 */
	// End Line: 17116

	/* begin block 3 */
		// Start line: 5278
	/* end block 3 */
	// End Line: 5279

// [D] [T]
void PedUserWalker(PEDESTRIAN* pPed)
{
	if ((pPed->flags & 0x10) == 0)
	{
		SetupWalker(pPed);
	}

	if (tannerPad & 0x4080)
	{
		pPed->speed = -10;
	}
	else
	{
		pPed->type = PED_ACTION_STOPPING;
		pPed->frame1 = 0;
		pPed->speed = 0;
		pPed->fpAgitatedState = NULL;
		pPed->flags &= ~0x10;
	}

	if (tannerPad & 0x2000)
	{
		pPed->head_rot = 0;
		pPed->dir.vy += 20;
	}

	if (tannerPad & 0x8000)
	{
		pPed->head_rot = 0;
		pPed->dir.vy -= 20;
	}

	AnimatePed(pPed);
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedCarryOutAnimation(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2702, offset 0x00072a10
	/* begin block 1 */
		// Start line: 17238
	/* end block 1 */
	// End Line: 17239

	/* begin block 2 */
		// Start line: 17247
	/* end block 2 */
	// End Line: 17248

int iFreezeTimer = 0;
int bFreezeAnimation = 0;
int allreadydone = 0;

// [D] [T]
void PedCarryOutAnimation(PEDESTRIAN* pPed)
{
	pPed->speed = 0;
	if (tannerPad != 0)
	{
		pPed->frame1 = 0;
		pPed->fpAgitatedState = NULL;
		pPed->flags &= ~0x10;

		bFreezeAnimation = 0;
		pPed->flags &= ~4;
		allreadydone = 0;
	}

	if (bFreezeAnimation == 0)
	{
		AnimatePed(pPed);
	}
	else
	{
		if (iFreezeTimer == 0)
		{
			bFreezeAnimation = 0;
			pPed->flags |= 4;
			iFreezeTimer = 0;
		}

		iFreezeTimer--;
	}

	if ((pPed->flags & 4) == 0)
	{
		if (pPed->frame1 > 14 && bFreezeAnimation == 0)
		{
			if (pPed->type == PED_ACTION_TIME)
			{
				bFreezeAnimation = 1;
				iFreezeTimer = 12;
			}
			else
			{
				pPed->frame1 = 0;
				pPed->fpAgitatedState = NULL;
				pPed->flags &= ~0x10;
			}
		}
	}
	else if (pPed->frame1 == 0)
	{
		pPed->frame1 = 0;
		pPed->fpAgitatedState = NULL;
		pPed->flags &= ~0x10;

		bFreezeAnimation = 0;
		pPed->flags &= ~4;
		allreadydone = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedGetOutCar(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2796, offset 0x00072bec
	/* begin block 1 */
		// Start line: 17673
	/* end block 1 */
	// End Line: 17674

	/* begin block 2 */
		// Start line: 5592
	/* end block 2 */
	// End Line: 5593

_CAR_DATA* carToGetIn;
int bReverseYRotation = 0;

// [D] [T]
void PedGetOutCar(PEDESTRIAN* pPed)
{
	int playerId;

	playerId = pPed->padId;

	pPed->speed = 0;
	pPed->frame1++;

	player[playerId].pos[0] = pPed->position.vx;
	player[playerId].pos[1] = -pPed->position.vy;
	player[playerId].pos[2] = pPed->position.vz;

	if (pPed->frame1 > 14)
	{
		ChangeCarPlayerToPed(playerId);

		pPed->speed = 0;
		pPed->fpAgitatedState = NULL;
		pPed->flags &= ~0x10;
		pPed->dir.vy = carToGetIn->hd.direction - 2048;

		bReverseYRotation = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupGetOutCar(struct PEDESTRIAN *pPed /*$s5*/, struct _CAR_DATA *pCar /*$s3*/, int side /*$s7*/)
 // line 2827, offset 0x0006f80c
	/* begin block 1 */
		// Start line: 2828
		// Start offset: 0x0006F80C
		// Variables:
	// 		int alpha; // $s2
	// 		long disp[4]; // stack offset -80
	// 		long dir[4]; // stack offset -64
	// 		struct SVECTOR vert; // stack offset -48
	// 		int x; // $s4
	// 		int z; // $s0
	// 		int a; // $s6
	// 		int nx; // $a3
	// 		int nz; // $a1
	/* end block 1 */
	// End offset: 0x0006FA3C
	// End Line: 2891

	/* begin block 2 */
		// Start line: 6072
	/* end block 2 */
	// End Line: 6073

	/* begin block 3 */
		// Start line: 6268
	/* end block 3 */
	// End Line: 6269

int lastCarCameraView = 0;

// [D] [T]
void SetupGetOutCar(PEDESTRIAN* pPed, _CAR_DATA* pCar, int side)
{
	bool entrySide;
	int sn, cs;
	uint carDir;
	int xOfs;
	int playerId;

	playerId = pPed->padId;

	lastCarCameraView = player[playerId].cameraView;
	pPed->speed = 0;

	sn = rsin(pCar->hd.direction);
	cs = rcos(pCar->hd.direction);

	entrySide = cs * (pCar->hd.where.t[0] - pPed->position.vx) - FIXED(sn * 0x1000) * (pCar->hd.where.t[2] - pPed->position.vz) + 0x800 > -1;

	if (entrySide)
		pPed->dir.vy = pCar->hd.direction - 1024;
	else
		pPed->dir.vy = pCar->hd.direction + 1024;

	bReverseYRotation = !entrySide;

	if (side == 1)
		xOfs = -400;
	else
		xOfs = 400;

	carDir = pCar->hd.direction + 0x800U & 0xfff;

	if (NoPlayerControl == 0)
	{
		player[playerId].cameraView = 5;

		player[playerId].cameraPos.vx = pCar->hd.where.t[0] - (FIXED(xOfs * rcossin_tbl[carDir * 2 + 1]) - FIXED(rcossin_tbl[carDir * 2] * 800));
		player[playerId].cameraPos.vy = -200 - pCar->hd.where.t[1];
		player[playerId].cameraPos.vz = pCar->hd.where.t[2] + (FIXED(xOfs * rcossin_tbl[carDir * 2]) + FIXED(rcossin_tbl[carDir * 2 + 1] * 800));
	}

	pPed->frame1 = 0;
	carToGetIn = pCar;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupGetInCar(struct PEDESTRIAN *pPed /*$s2*/)
 // line 2898, offset 0x0006fa3c
	/* begin block 1 */
		// Start line: 2899
		// Start offset: 0x0006FA3C
		// Variables:
	// 		int alpha; // $s1
	// 		long disp[4]; // stack offset -72
	// 		long dir[4]; // stack offset -56
	// 		struct SVECTOR vert; // stack offset -40

		/* begin block 1.1 */
			// Start line: 2934
			// Start offset: 0x0006FB2C
			// Variables:
		// 		int x; // $t1
		// 		int z; // $t2
		// 		int a; // $a0
		// 		int nx; // $a3
		// 		int nz; // $a1
		/* end block 1.1 */
		// End offset: 0x0006FC24
		// End Line: 2957

		/* begin block 1.2 */
			// Start line: 2968
			// Start offset: 0x0006FC70
			// Variables:
		// 		long pos[4]; // stack offset -32
		/* end block 1.2 */
		// End offset: 0x0006FC70
		// End Line: 2969
	/* end block 1 */
	// End offset: 0x0006FD08
	// End Line: 2988

	/* begin block 2 */
		// Start line: 6510
	/* end block 2 */
	// End Line: 6511

	/* begin block 3 */
		// Start line: 6518
	/* end block 3 */
	// End Line: 6519

	/* begin block 4 */
		// Start line: 6525
	/* end block 4 */
	// End Line: 6526

// [D] [T]
void SetupGetInCar(PEDESTRIAN* pPed)
{
	int sn, cs;
	int carDir;
	int xOfs;
	int playerId;
	int entrySide;

	long pos[4];

	pPed->flags &= ~4;
	pPed->speed = 0;
	pPed->frame1 = 0;

	playerId = pPed->padId;

	sn = rsin(carToGetIn->hd.direction);
	cs = rcos(carToGetIn->hd.direction);

	entrySide = cs * (carToGetIn->hd.where.t[0] - pPed->position.vx) - FIXED(sn * 0x1000) * (carToGetIn->hd.where.t[2] - pPed->position.vz) + 0x800 < 0;

	if (entrySide)
		pPed->dir.vy = carToGetIn->hd.direction + 0x400;
	else
		pPed->dir.vy = carToGetIn->hd.direction - 0x400;

	if (pPed->dir.vy > carToGetIn->hd.direction)
		xOfs = -400;
	else
		xOfs = 400;

	carDir = carToGetIn->hd.direction + 0x800U & 0xfff;

	if (NoPlayerControl == 0 && gInGameCutsceneActive == 0)
	{
		player[playerId].cameraView = 5;
		player[playerId].cameraPos.vx = carToGetIn->hd.where.t[0] - (FIXED(xOfs * rcossin_tbl[carDir * 2 + 1]) - FIXED(rcossin_tbl[carDir * 2] * 800));
		player[playerId].cameraPos.vy = -200 - carToGetIn->hd.where.t[1];
		player[playerId].cameraPos.vz = carToGetIn->hd.where.t[2] + (FIXED(xOfs * rcossin_tbl[carDir * 2]) + FIXED(rcossin_tbl[carDir * 2 + 1] * 800));
	}

	if ((carToGetIn->controlFlags & CONTROL_FLAG_WAS_PARKED) == 0)
	{
		if (carToGetIn->controlType == CONTROL_TYPE_CIV_AI && carToGetIn->ai.c.thrustState == 3 && carToGetIn->ai.c.ctrlState == 5)
		{
			carToGetIn->controlFlags |= CONTROL_FLAG_WAS_PARKED;
		}
		else
		{
			pos[0] = player[playerId].pos[0];
			pos[1] = -player[playerId].pos[1];
			pos[2] = player[playerId].pos[2];

			// HEY!
			CreatePedAtLocation(&pos, 8);
			Start3DSoundVolPitch(-1, 6, 5, pos[0], pos[1], pos[2], 0, 0x1000);

			carToGetIn->controlFlags |= CONTROL_FLAG_WAS_PARKED;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedGetInCar(struct PEDESTRIAN *pPed /*$s0*/)
 // line 2994, offset 0x00072b5c
	/* begin block 1 */
		// Start line: 2995
		// Start offset: 0x00072B5C
		// Variables:
	// 		long disp[4]; // stack offset -48
	// 		long dir[4]; // stack offset -32
	// 		struct SVECTOR vert; // stack offset -16
	/* end block 1 */
	// End offset: 0x00072BEC
	// End Line: 3018

	/* begin block 2 */
		// Start line: 17840
	/* end block 2 */
	// End Line: 17841

// [D] [T]
void PedGetInCar(PEDESTRIAN* pPed)
{
	int playerID;

	pPed->speed = 0;

	if (pPed->frame1 < 0xf)
	{
		AnimatePed(pPed);
	}
	else
	{
		playerID = ABS(pPed->padId);

		pPed->speed = 0;
		pPed->fpAgitatedState = NULL;

		pPed->flags &= ~0x10;

		ChangePedPlayerToCar(playerID, carToGetIn);
		DestroyPedestrian(pPed);

		pPlayerPed = NULL;
		numTannerPeds--;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupPressButton(struct PEDESTRIAN *pPed /*$s0*/)
 // line 3026, offset 0x00072904
	/* begin block 1 */
		// Start line: 17494
	/* end block 1 */
	// End Line: 17495

	/* begin block 2 */
		// Start line: 6052
	/* end block 2 */
	// End Line: 6053

// [D] [T]
void SetupPressButton(PEDESTRIAN* pPed)
{
	pPed->type = PED_ACTION_PRESSBUTTON;
	SetupPedMotionData(pPed);

	pPed->speed = 0;
	pPed->frame1 = 0;
	pPed->fpAgitatedState = PedPressButton;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedPressButton(struct PEDESTRIAN *pPed /*$v1*/)
 // line 3040, offset 0x00072c90
	/* begin block 1 */
		// Start line: 18175
	/* end block 1 */
	// End Line: 18176

// [D] [T]
void PedPressButton(PEDESTRIAN* pPed)
{
	if (pPed->frame1 < 15)
	{
		AnimatePed(pPed);
	}
	else
	{
		pPed->type = PED_ACTION_BACK;
		pPed->fpAgitatedState = NULL;
		pPed->frame1 = 0;

		SetupPedMotionData(pPed);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupTannerSitDown(struct PEDESTRIAN *pPed /*$s0*/)
 // line 3060, offset 0x000728c8
	/* begin block 1 */
		// Start line: 6120
	/* end block 1 */
	// End Line: 6121

// [D] [T]
void SetupTannerSitDown(PEDESTRIAN* pPed)
{
	pPed->type = PED_ACTION_SIT;
	SetupPedMotionData(pPed);

	pPed->speed = 0;
	pPed->frame1 = 0;
	pPed->fpAgitatedState = TannerSitDown;
}

// decompiled code
// original method signature: 
// void /*$ra*/ TannerCameraHandler(struct PEDESTRIAN *pPed /*$a0*/)
 // line 3074, offset 0x0006fd08
	/* begin block 1 */
		// Start line: 3076
		// Start offset: 0x0006FD08
		// Variables:
	// 		int padsteer; // $a3
	// 		int maxY; // $t1
	// 		int maxX; // $t5
	// 		int range; // $t0
	// 		int minX; // $t4
	// 		int extra; // $a3
	/* end block 1 */
	// End offset: 0x0006FF48
	// End Line: 3150

	/* begin block 2 */
		// Start line: 6830
	/* end block 2 */
	// End Line: 6831

	/* begin block 3 */
		// Start line: 6917
	/* end block 3 */
	// End Line: 6918

	/* begin block 4 */
		// Start line: 6918
	/* end block 4 */
	// End Line: 6919

	/* begin block 5 */
		// Start line: 6927
	/* end block 5 */
	// End Line: 6928

/* WARNING: Removing unreachable block (ram,0x0006fe58) */
/* WARNING: Removing unreachable block (ram,0x0006fde0) */
/* WARNING: Removing unreachable block (ram,0x0006fe8c) */

// [D] [T]
void TannerCameraHandler(PEDESTRIAN* pPed)
{
	int value;
	short extra;
	int padSteer;
	_PLAYER* lcp;

	int padid;

	padid = pPed->padId;

	lcp = &player[padid];

	camera_position.vy = pPed->head_pos - 28 - lcp->pos[1];

	if (Pads[padid].type == 4)
	{
		padSteer = Pads[padid].mapanalog[0];

		if (padSteer < -32 || padSteer > 32)
		{
			if (padSteer < 0)
				value = -padSteer;
			else
				value = padSteer;

			if (padSteer < 0)
				tannerLookAngle.vy = (value - 32) * -9;
			else
				tannerLookAngle.vy = (value - 32) * 9;
		}
		else
		{
			tannerLookAngle.vy = 0;
		}

		tannerLookAngle.vx = -Pads[padid].mapanalog[1];

		if (tannerLookAngle.vx < -32)
			tannerLookAngle.vx = tannerLookAngle.vx - 128;
		else if (tannerLookAngle.vx < 33)
			tannerLookAngle.vx = 0;
	}
	else
	{
		tannerLookAngle.vx = 0;
		tannerLookAngle.vy = 0;
		tannerLookAngle.vz = 0;
	}

	if (padd & 1)
	{
		if (padd & 2)
			extra = 2048;
		else
			extra = 1024;
	}
	else
	{
		if (padd & 2)
			extra = -1024;
		else
			extra = 0;
	}

	camera_position.vx = lcp->pos[0];
	camera_position.vz = lcp->pos[2];

	camera_angle.vx = camAngle.vx + tannerLookAngle.vx;
	camera_angle.vy = (camAngle.vy - tannerLookAngle.vy) + extra & 0xfff;
	camera_angle.vz = camAngle.vz + tannerLookAngle.vz;

	tracking_car = 0;

	lcp->cameraPos.vx = lcp->pos[0];
	lcp->cameraPos.vy = camera_position.vy;
	lcp->cameraPos.vz = lcp->pos[2];
}



// decompiled code
// original method signature: 
// void /*$ra*/ TannerSitDown(struct PEDESTRIAN *pPed /*$a2*/)
 // line 3157, offset 0x0006ff48
	/* begin block 1 */
		// Start line: 3158
		// Start offset: 0x0006FF48
		// Variables:
	// 		struct VECTOR angle; // stack offset -24
	/* end block 1 */
	// End offset: 0x000700D0
	// End Line: 3219

	/* begin block 2 */
		// Start line: 7110
	/* end block 2 */
	// End Line: 7111

	/* begin block 3 */
		// Start line: 7118
	/* end block 3 */
	// End Line: 7119

// [D] [T]
void TannerSitDown(PEDESTRIAN* pPed)
{
	if (oldCamView != 2 && player[pPed->padId].cameraView == 2)
	{
		camAngle.vx = camera_angle.vx;
		camAngle.vy = camera_angle.vy;
		camAngle.vz = camera_angle.vz;
	}

	// if sit down/standup animation playing
	if (pPed->flags & 4)
	{
		if (pPed->frame1 == 0)
		{
			pPed->frame1 = 0;
			pPed->fpAgitatedState = NULL;
			pPed->flags &= ~0x10;

			tannerLookAngle.vx = 0;
			tannerLookAngle.vy = 0;
			tannerLookAngle.vz = 0;

			bFreezeAnimation = 0;
			pPed->flags &= ~4;
			return;
		}

		pPed->position.vy -= 3;
	}
	else
	{
		if (pPed->frame1 == 15)
		{
			oldCamView = player[pPed->padId].cameraView;
			bFreezeAnimation = 1;

			if (tannerPad & 0x10)
			{
				tracking_car = 1;
				pPed->flags |= 4; // new reverse animation flag
				bFreezeAnimation = 0;

				oldCamView = -1;
			}
			return;
		}

		pPed->position.vy += 3;
	}

	AnimatePed(pPed);
}



// decompiled code
// original method signature: 
// void /*$ra*/ AnimatePed(struct PEDESTRIAN *pPed /*$s0*/)
 // line 3227, offset 0x000700d0
	/* begin block 1 */
		// Start line: 3228
		// Start offset: 0x000700D0

		/* begin block 1.1 */
			// Start line: 3238
			// Start offset: 0x000700F0
			// Variables:
		// 		int mapheight; // $a3
		// 		int reverse; // $s1

			/* begin block 1.1.1 */
				// Start line: 3241
				// Start offset: 0x000700F0
				// Variables:
			// 		struct VECTOR vec; // stack offset -32
			/* end block 1.1.1 */
			// End offset: 0x0007015C
			// End Line: 3266

			/* begin block 1.1.2 */
				// Start line: 3330
				// Start offset: 0x0007030C
				// Variables:
			// 		int sfc; // $v1
			/* end block 1.1.2 */
			// End offset: 0x000703BC
			// End Line: 3335
		/* end block 1.1 */
		// End offset: 0x00070468
		// End Line: 3348
	/* end block 1 */
	// End offset: 0x00070468
	// End Line: 3350

	/* begin block 2 */
		// Start line: 7270
	/* end block 2 */
	// End Line: 7271

	/* begin block 3 */
		// Start line: 7279
	/* end block 3 */
	// End Line: 7280

	/* begin block 4 */
		// Start line: 7285
	/* end block 4 */
	// End Line: 7286

// [D] [T]
void AnimatePed(PEDESTRIAN* pPed)
{
	int dir;
	VECTOR vec;

	if (pauseflag)
		return;

	vec.vx = pPed->position.vx;
	vec.vz = pPed->position.vz;
	vec.vy = -pPed->position.vy;

	if (pPed->type != PED_ACTION_SIT)
	{
		if (pPed->pedType == CIVILIAN && (pPed->flags & 0x8000U) != 0)
			pPed->position.vy = -60 - MapHeight(&vec);
		else
			pPed->position.vy = -130 - MapHeight(&vec);
	}

	if (pPed->speed < 0)
	{
		dir = pPed->dir.vy;
		pPed->position.vx -= FIXED(pPed->speed * rcossin_tbl[(dir & 0xfff) * 2]);
		pPed->position.vz -= FIXED(pPed->speed * rcossin_tbl[(-dir & 0xfffU) * 2 + 1]);
	}
	else
	{
		dir = pPed->dir.vy - 0x800U & 0xfff;
		pPed->position.vx += FIXED(pPed->speed * rcossin_tbl[dir * 2]);
		pPed->position.vz += FIXED(pPed->speed * rcossin_tbl[dir * 2 + 1]);
	}

	if (pPed->type != PED_ACTION_SIT &&
		pPed->type != PED_ACTION_COPCROUCH &&
		pPed->type != PED_ACTION_COPSTAND)
	{
		pPed->velocity.vy = 10;
	}

	if ((pPed->flags & 4) /*&& pPed->pedType == TANNER_MODEL*/)
	{
		if (pPed->frame1 == 0)
			pPed->frame1 = 15;

		pPed->frame1--;
	}
	else
	{
		int numFrames;
		pPed->frame1++;

		if (pPed->type - 8U < 3)	// [A] TODO: figure out what type it is to have extended frames
			numFrames = 31;
		else
			numFrames = 16;

		if (pPed->frame1 >= numFrames)
			pPed->frame1 = 0;
	}

	if ((pPed->pedType == TANNER_MODEL || (ActiveCheats.cheat12 && pPed->pedType == OTHER_MODEL)) && pPed->type < PED_ACTION_BACK)
	{
		int surfId;
		surfId = PedSurfaceType((VECTOR*)&pPed->position);

		if (surfId != 4 && surfId != 6 && surfId != 11 && surfId != 9)
		{
			if (pPed->frame1 == 3)
				Start3DSoundVolPitch(-1, 6, 0, pPed->position.vx, pPed->position.vy, pPed->position.vz, -5000, 0x1000);

			if (pPed->frame1 == 11)
				Start3DSoundVolPitch(-1, 6, 1, pPed->position.vx, pPed->position.vy, pPed->position.vz, -5000, 0x1000);
		}
	}

	if (pPed->pedType != CIVILIAN)
	{
		int padId;
		padId = ABS(pPed->padId);

		player[padId].pos[0] = pPed->position.vx;
		player[padId].pos[1] = -pPed->position.vy;
		player[padId].pos[2] = pPed->position.vz;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DeActivatePlayerPedestrian(struct PEDESTRIAN *pPed /*$s3*/)
 // line 3357, offset 0x0007216c
	/* begin block 1 */
		// Start line: 3358
		// Start offset: 0x0007216C
		// Variables:
	// 		int distToCarSq; // stack offset -32
	// 		struct _CAR_DATA *closestCar; // $s1
	// 		struct _PLAYER *pPlayer; // $v0
	// 		struct VECTOR point; // stack offset -48
	// 		int getIn; // $s2

		/* begin block 1.1 */
			// Start line: 3384
			// Start offset: 0x0007221C
		/* end block 1.1 */
		// End offset: 0x00072274
		// End Line: 3395
	/* end block 1 */
	// End offset: 0x00072290
	// End Line: 3396

	/* begin block 2 */
		// Start line: 6714
	/* end block 2 */
	// End Line: 6715

// [D] [T]
void DeActivatePlayerPedestrian(PEDESTRIAN* pPed)
{
	_CAR_DATA* cp;
	int playerId;
	int getIn;
	int distToCarSq;

	getIn = 0;
	playerId = pPed->padId;

	if (playerId < 0)
		playerId = -playerId;

	cp = FindClosestCar(player[playerId].pos[0], player[playerId].pos[1], player[playerId].pos[2], &distToCarSq);

	if (!cp)
		return;

	if (cp->ap.model == 4)
		getIn = FindPointOfCollision(cp, pPed);
	else if (cp && TannerCanEnterCar(cp, distToCarSq))
		getIn = 1;

	if (getIn != 0)
	{
		carToGetIn = cp;
		pPed->type = PED_ACTION_GETINCAR;
		pPed->fpAgitatedState = PedGetInCar;

		Start3DSoundVolPitch(-1, 6, 2, player[0].pos[0], player[0].pos[1], player[0].pos[2], 0, 0x1000);
		SetupPedestrian(pPed);
		SetupGetInCar(pPed);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivPedDoNothing(struct PEDESTRIAN *pPed /*$a0*/)
 // line 3402, offset 0x00072ce0
	/* begin block 1 */
		// Start line: 18899
	/* end block 1 */
	// End Line: 18900

	/* begin block 2 */
		// Start line: 18900
	/* end block 2 */
	// End Line: 18901

// [D] [T]
void CivPedDoNothing(PEDESTRIAN* pPed)
{
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupCivPedRouteData(struct VECTOR *pPos /*$s1*/)
 // line 3411, offset 0x0007313c
	/* begin block 1 */
		// Start line: 3412
		// Start offset: 0x0007313C
		// Variables:
	// 		struct VECTOR baseLoc; // stack offset -32
	/* end block 1 */
	// End offset: 0x000731F8
	// End Line: 3435

	/* begin block 2 */
		// Start line: 23047
	/* end block 2 */
	// End Line: 23048

// [D] [T]
void SetupCivPedRouteData(VECTOR* pPos)
{
	VECTOR baseLoc;

	baseLoc.vx = pPos->vx;
	baseLoc.vy = pPos->vy;
	baseLoc.vz = pPos->vz;

	pedestrian_roads.pos = GetSurfaceIndex(&baseLoc);

	baseLoc.vz = pPos->vz - 128;
	pedestrian_roads.north = GetSurfaceIndex(&baseLoc);

	baseLoc.vz = pPos->vz + 128;
	pedestrian_roads.south = GetSurfaceIndex(&baseLoc);

	baseLoc.vz = pPos->vz;
	baseLoc.vx = pPos->vx - 128;
	pedestrian_roads.east = GetSurfaceIndex(&baseLoc);

	baseLoc.vx = pPos->vx + 128;
	pedestrian_roads.west = GetSurfaceIndex(&baseLoc);
}



// decompiled code
// original method signature: 
// void /*$ra*/ PingInPedestrians()
 // line 3447, offset 0x0007047c
	/* begin block 1 */
		// Start line: 3449
		// Start offset: 0x0007047C
		// Variables:
	// 		int bFound; // $s1
	// 		struct VECTOR randomLoc; // stack offset -88
	// 		struct VECTOR baseLoc; // stack offset -72
	// 		int i; // $s2
	// 		int pingInDist; // $a2
	// 		struct VECTOR position; // stack offset -56
	// 		struct VECTOR target; // stack offset -40
	// 		struct PEDESTRIAN *pedestrian; // $s1

		/* begin block 1.1 */
			// Start line: 3484
			// Start offset: 0x00070518

			/* begin block 1.1.1 */
				// Start line: 3502
				// Start offset: 0x000705F8
				// Variables:
			// 		struct PEDESTRIAN *pPed; // $a2

				/* begin block 1.1.1.1 */
					// Start line: 3520
					// Start offset: 0x00070628
					// Variables:
				// 		int x; // $v1
				// 		int z; // $v0
				// 		int radius; // $v1
				/* end block 1.1.1.1 */
				// End offset: 0x00070628
				// End Line: 3522
			/* end block 1.1.1 */
			// End offset: 0x00070674
			// End Line: 3524
		/* end block 1.1 */
		// End offset: 0x00070674
		// End Line: 3526

		/* begin block 1.2 */
			// Start line: 3534
			// Start offset: 0x000706AC

			/* begin block 1.2.1 */
				// Start line: 3583
				// Start offset: 0x000707F4
				// Variables:
			// 		int rval; // $v1
			/* end block 1.2.1 */
			// End offset: 0x00070858
			// End Line: 3622
		/* end block 1.2 */
		// End offset: 0x00070858
		// End Line: 3627
	/* end block 1 */
	// End offset: 0x00070858
	// End Line: 3632

	/* begin block 2 */
		// Start line: 7739
	/* end block 2 */
	// End Line: 7740

	/* begin block 3 */
		// Start line: 7740
	/* end block 3 */
	// End Line: 7741

	/* begin block 4 */
		// Start line: 7753
	/* end block 4 */
	// End Line: 7754

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void PingInPedestrians(void)
{
	int bFound;
	PEDESTRIAN* pPed;
	long rnd;
	int pingInDist;
	int i;
	int dx, dz;
	VECTOR randomLoc;
	VECTOR baseLoc;

	if (num_pedestrians >= MAX_PLACED_PEDS || pFreePeds == NULL || pFreePeds->pNext == NULL)
		return;

	baseLoc.vx = player[0].pos[0];
	baseLoc.vy = player[0].pos[1];
	baseLoc.vz = player[0].pos[2];

	if (gWeather == 0 && FindSeated() != NULL)
		return;

	for (i = 0; i < 50; i++)
	{
		pinginPedAngle += 81;

		pingInDist = Random2(0) % 128 + 1536;

		randomLoc.vy = baseLoc.vy;
		randomLoc.vx = baseLoc.vx + pingInDist * FIXEDH(rcossin_tbl[(pinginPedAngle & 0xfffU) * 2] * 8);
		randomLoc.vz = baseLoc.vz + pingInDist * FIXEDH(rcossin_tbl[(pinginPedAngle & 0xfffU) * 2 + 1] * 8);

		randomLoc.vy = -MapHeight(&randomLoc);

		if (baseLoc.vy - 512 <= -randomLoc.vy &&
			baseLoc.vy + 512 >= -randomLoc.vy &&
			IsPavement(randomLoc.vx, randomLoc.vy, randomLoc.vz, NULL))
		{
			if (pUsedPeds != NULL)
			{
				pPed = pUsedPeds;

				dx = pPed->position.vx - randomLoc.vx;
				dz = pPed->position.vz - randomLoc.vz;

				bFound = 0;

				while (dx * dx + dz * dz > 15999999)
				{
					pPed = pPed->pNext;

					if (pPed == NULL)
					{
						bFound = 1;
						break;
					}

					dx = pPed->position.vx - randomLoc.vx;
					dz = pPed->position.vz - randomLoc.vz;
				}
			}
			else
			{
				bFound = 1;
			}

			if (!bFound)
				return;

			if (pFreePeds->pNext == NULL)
				return;

			pPed = CreatePedestrian();

			pPed->flags = 0;
			pPed->position.vx = randomLoc.vx;
			pPed->position.vy = randomLoc.vy;
			pPed->pedType = CIVILIAN;
			pPed->dir.vz = 0;
			pPed->dir.vx = 0;
			pPed->dir.vy = 0;
			pPed->position.vz = randomLoc.vz;

			baseLoc.vx = randomLoc.vx;
			baseLoc.vy = pPed->position.vy;
			baseLoc.vz = pPed->position.vz;

			baseLoc.vy = -MapHeight(&baseLoc);

			SetupCivPedRouteData(&baseLoc);
			PedestrianActionInit_WalkToTarget(pPed);

			pPed->type = PED_ACTION_CIVRUN;

			if (pedestrian_roads.north != -28 &&
				(pPed->type = PED_ACTION_CIVRUN, pedestrian_roads.south != -28) &&
				(pPed->type = PED_ACTION_CIVRUN, pedestrian_roads.east != -28) &&
				(pPed->type = PED_ACTION_CIVWALK, pedestrian_roads.west == -28))
			{
				pPed->type = PED_ACTION_CIVRUN;
			}

			// it might not be correct
			pPed->pallet = (Random2(-28) % 5) + (Random2(-28) % 5) * 16;

			SetupPedMotionData(pPed);

			pPed->fpAgitatedState = NULL;
			pPed->dir.vy = 0;
			pPed->fpRestState = fpPedPersonalityFunctions[7];
			pPed->speed = 0;

			rnd = Random2(0);

			if ((rnd / 6) * 6 != rnd - 3)
				return;

			pPed->flags |= 0x4000;
			return;
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ TannerCollision(struct PEDESTRIAN *pPed /*$s1*/)
 // line 3640, offset 0x00072ee4
	/* begin block 1 */
		// Start line: 3641
		// Start offset: 0x00072EE4
	/* end block 1 */
	// End offset: 0x00072FBC
	// End Line: 3675

	/* begin block 2 */
		// Start line: 20049
	/* end block 2 */
	// End Line: 20050

	/* begin block 3 */
		// Start line: 20050
	/* end block 3 */
	// End Line: 20051

	/* begin block 4 */
		// Start line: 21345
	/* end block 4 */
	// End Line: 21346



// [D] [T]
void TannerCollision(PEDESTRIAN* pPed)
{
	_CAR_DATA* pcdTanner;

	if (pPed->type == PED_ACTION_SIT)
		return;

	pcdTanner = &car_data[21];

	ClearMem((char*)pcdTanner, sizeof(_CAR_DATA));

	pcdTanner->id = 21;
	pcdTanner->controlType = 6;

	pcdTanner->hd.direction = pPed->dir.vy - 0x800U & 0xfff;

	pcdTanner->hd.oBox.location.vx = pPed->position.vx;
	pcdTanner->hd.where.t[0] = pPed->position.vx;

	pcdTanner->hd.oBox.location.vy = -pPed->position.vy;
	pcdTanner->hd.where.t[1] = -pPed->position.vy;

	pcdTanner->hd.oBox.location.vz = pPed->position.vz;
	pcdTanner->hd.where.t[2] = pPed->position.vz;

	pcdTanner->st.n.linearVelocity[0] = 0;
	pcdTanner->st.n.linearVelocity[1] = 0;
	pcdTanner->st.n.linearVelocity[2] = 0;

	CheckScenaryCollisions(pcdTanner);
	TannerCarCollisionCheck((VECTOR*)&pPed->position, pPed->dir.vy, 0);

	pPed->position.vx = pcdTanner->hd.where.t[0];
	pPed->position.vz = pcdTanner->hd.where.t[2];
}



// decompiled code
// original method signature: 
// int /*$ra*/ FindPointOfCollision(struct _CAR_DATA *pCar /*$s3*/, struct VECTOR *pPos /*$a1*/)
 // line 3685, offset 0x00070878
	/* begin block 1 */
		// Start line: 3686
		// Start offset: 0x00070878
		// Variables:
	// 		int tb1; // $v1
	// 		int tb2; // $v0
	// 		int minX; // $a3
	// 		int maxX; // $t0
	// 		int minZ; // $v0
	// 		int maxZ; // $a0
	// 		int x; // $t1
	// 		int z; // $a1
	// 		int s1; // $a2
	// 		int s2; // $v1
	// 		int carLength[2]; // stack offset -40
	// 		static struct CRET2D collisionResult; // offset 0x0
	/* end block 1 */
	// End offset: 0x00070A9C
	// End Line: 3753

	/* begin block 2 */
		// Start line: 8376
	/* end block 2 */
	// End Line: 8377

	/* begin block 3 */
		// Start line: 8377
	/* end block 3 */
	// End Line: 8378

// [D] [T]
int FindPointOfCollision(_CAR_DATA* pCar, PEDESTRIAN* pPed)
{
	int dx, dz;
	int minZ;
	int maxZ;
	int minX;
	int maxX;

	CDATA2D cd[2];
	static CRET2D collisionResult;
	CAR_COSMETICS* car_cos;

	car_cos = &car_cosmetics[pCar->ap.model];

	cd[0].length[0] = 120;
	cd[0].length[1] = 12;

	cd[0].x.vx = pPed->position.vx;
	cd[0].x.vz = pPed->position.vz;
	cd[0].theta = pPed->dir.vy - 0x800U & 0xfff;

	cd[1].length[0] = car_cos->colBox.vz;
	cd[1].length[1] = car_cos->colBox.vx;

	cd[1].x.vx = pCar->hd.where.t[0];
	cd[1].x.vz = pCar->hd.where.t[2];
	cd[1].theta = pCar->hd.direction;

	if (!bcollided2d(cd, 1))
		return 0;

	bFindCollisionPoint(cd, &collisionResult);

#if defined(COLLISION_DEBUG) && !defined(PSX)
	extern int gShowCollisionDebug;
	if (gShowCollisionDebug)
	{
		extern void Debug_AddLine(VECTOR & pointA, VECTOR & pointB, CVECTOR & color);
		extern void Debug_AddLineOfs(VECTOR & pointA, VECTOR & pointB, VECTOR & ofs, CVECTOR & color);

		CVECTOR bbcv = { 0, 0, 250 };
		CVECTOR rrcv = { 250, 0, 0 };
		CVECTOR yycv = { 250, 250, 0 };

		VECTOR _zero = { 0, 100, 0 };
		VECTOR up = { 0, 200, 0 };

		Debug_AddLineOfs(_zero, up, cd[0].x, rrcv);

		Debug_AddLineOfs(_zero, up, cd[1].x, yycv);

		Debug_AddLineOfs(_zero, up, collisionResult.hit, bbcv);
	}
#endif


	dx = FIXED((collisionResult.hit.vx - cd[1].x.vx) * rcossin_tbl[(cd[1].theta & 0xfffU) * 2 + 1]) -
		FIXED((collisionResult.hit.vz - cd[1].x.vz) * rcossin_tbl[(cd[1].theta & 0xfffU) * 2]);

	dz = FIXED((collisionResult.hit.vx - cd[1].x.vx) * rcossin_tbl[(cd[1].theta & 0xfffU) * 2]) +
		FIXED((collisionResult.hit.vz - cd[1].x.vz) * rcossin_tbl[(cd[1].theta & 0xfffU) * 2 + 1]);

	minX = car_cos->colBox.vx + 96;
	maxX = car_cos->colBox.vx - 96;

	minZ = car_cos->colBox.vz - 480;
	maxZ = car_cos->colBox.vz - 200;

	if (dz > minZ && dz < maxZ &&
		(dx > maxX && dx < minX || dx < -maxX && dx > -minX))
	{
		return 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ TannerCarCollisionCheck(struct VECTOR *pPos /*$s5*/, int dir /*$a1*/, int bQuick /*stack 8*/)
 // line 3762, offset 0x00070a9c
	/* begin block 1 */
		// Start line: 3763
		// Start offset: 0x00070A9C
		// Variables:
	// 		int carLength[2]; // stack offset -120
	// 		struct _CAR_DATA *cp0; // $s0
	// 		struct _CAR_DATA *cp1; // $s1
	// 		static struct CRET2D collisionResult; // offset 0x30
	// 		unsigned int dNewLBODY[2]; // stack offset -112
	// 		int speed; // $v0

		/* begin block 1.1 */
			// Start line: 3798
			// Start offset: 0x00070B2C

			/* begin block 1.1.1 */
				// Start line: 3798
				// Start offset: 0x00070B2C
			/* end block 1.1.1 */
			// End offset: 0x00070B2C
			// End Line: 3798

			/* begin block 1.1.2 */
				// Start line: 3815
				// Start offset: 0x00070C04
				// Variables:
			// 		struct VECTOR velocity; // stack offset -104
			// 		long pointVel[4]; // stack offset -88
			// 		long reaction[4]; // stack offset -72
			// 		long lever[4]; // stack offset -56
			// 		int strikeVel; // $t1

				/* begin block 1.1.2.1 */
					// Start line: 3846
					// Start offset: 0x00070D84
				/* end block 1.1.2.1 */
				// End offset: 0x00070D84
				// End Line: 3857

				/* begin block 1.1.2.2 */
					// Start line: 3861
					// Start offset: 0x00070DB0
					// Variables:
				// 		int twistY; // $a2
				// 		int lever_dot_n; // $a0
				// 		int displacementsquared; // $a1
				// 		int denom; // $a0
				/* end block 1.1.2.2 */
				// End offset: 0x00070E8C
				// End Line: 3874
			/* end block 1.1.2 */
			// End offset: 0x00070FD8
			// End Line: 3895
		/* end block 1.1 */
		// End offset: 0x00071008
		// End Line: 3904
	/* end block 1 */
	// End offset: 0x00071054
	// End Line: 3907

	/* begin block 2 */
		// Start line: 8611
	/* end block 2 */
	// End Line: 8612

	/* begin block 3 */
		// Start line: 8621
	/* end block 3 */
	// End Line: 8622

	/* begin block 4 */
		// Start line: 8646
	/* end block 4 */
	// End Line: 8647

/* WARNING: Removing unreachable block (ram,0x00070ec8) */
/* WARNING: Type propagation algorithm not settling */

// [D] [T]
int TannerCarCollisionCheck(VECTOR* pPos, int dir, int bQuick)
{
	_CAR_DATA* cp1;
	long pointVel[4];
	long reaction[4];
	long lever[4];
	int strikeVel;
	SVECTOR boxDisp;
	CAR_COSMETICS* car_cos;
	_CAR_DATA* pcdTanner;

	CRET2D collisionResult; // offset 0x30
	CDATA2D cd[2];

	pcdTanner = &car_data[21];

	cd[0].length[0] = 0x3c;
	cd[0].length[1] = 0x3c;
	cd[0].x.vx = pPos->vx;
	cd[0].x.vz = pPos->vz;
	cd[0].theta = dir;

	cp1 = car_data + MAX_CARS - 1;

	do {
		car_cos = &car_cosmetics[cp1->ap.model];

		cd[1].length[0] = car_cos->colBox.vz;
		cd[1].length[1] = car_cos->colBox.vx;
		cd[1].theta = cp1->hd.direction;

		// [A] fix bug with offset box collision
		gte_SetRotMatrix(&cp1->hd.where);
		gte_SetTransMatrix(&cp1->hd.where);

		boxDisp.vx = -car_cos->cog.vx;
		boxDisp.vy = -car_cos->cog.vy;
		boxDisp.vz = -car_cos->cog.vz;

		gte_ldv0(&boxDisp);

		gte_rtv0tr();

		gte_stlvnl(&cd[1].x);

		if (cp1->controlType != CONTROL_TYPE_NONE &&
			ABS(cp1->hd.where.t[1] + pPos->vy) < 500 &&
			bcollided2d(cd, 1))
		{
			if (bQuick != 0)
				return 1;

			if (FIXEDH(cp1->hd.wheel_speed) > 50)
				return 1;

			bFindCollisionPoint(cd, &collisionResult);

			collisionResult.surfNormal.vy = 0;
			collisionResult.hit.vy = pcdTanner->hd.where.t[1] + 60;

			pcdTanner->hd.where.t[0] += FIXEDH(collisionResult.penetration * -collisionResult.surfNormal.vx);
			pcdTanner->hd.where.t[2] += FIXEDH(collisionResult.penetration * -collisionResult.surfNormal.vz);

			lever[0] = collisionResult.hit.vx - pcdTanner->hd.where.t[0];
			lever[1] = collisionResult.hit.vy - pcdTanner->hd.where.t[1];
			lever[2] = collisionResult.hit.vz - pcdTanner->hd.where.t[2];

			pointVel[0] = FIXEDH(pcdTanner->st.n.angularVelocity[1] * lever[2] - pcdTanner->st.n.angularVelocity[2] * lever[1]) + pcdTanner->st.n.linearVelocity[0];
			pointVel[2] = FIXEDH(pcdTanner->st.n.angularVelocity[0] * lever[1] - pcdTanner->st.n.angularVelocity[1] * lever[0]) + pcdTanner->st.n.linearVelocity[2];

			strikeVel = FixFloorSigned(pointVel[0], 8) * FixFloorSigned(-collisionResult.surfNormal.vx, 4) + FixFloorSigned(pointVel[2], 8) * FixFloorSigned(-collisionResult.surfNormal.vz, 4);

			if (strikeVel < 0)
			{
				int lever_dot_n; // $a0
				int displacementsquared; // $a1
				int denom; // $a0
				int twistRateY;

				twistRateY = car_cos->twistRateY;
				
				lever_dot_n = FIXEDH(lever[0] * -collisionResult.surfNormal.vx + lever[2] * -collisionResult.surfNormal.vz);
				displacementsquared = FIXEDH(((lever[0] * lever[0] + lever[2] * lever[2]) - lever_dot_n * lever_dot_n) * twistRateY) + 0x1000;

				if (-strikeVel < 0x7f001)
					denom = (strikeVel * -0x1000) / displacementsquared;
				else
					denom = -strikeVel / displacementsquared << 0xc;

				denom = FixFloorSigned(denom, 6);
				
				reaction[0] = denom * FixFloorSigned(-collisionResult.surfNormal.vx, 6);
				reaction[2] = denom * FixFloorSigned(-collisionResult.surfNormal.vz, 6);
				
				pcdTanner->st.n.linearVelocity[0] += pcdTanner->st.n.linearVelocity[0] + reaction[0];
				pcdTanner->st.n.linearVelocity[2] += pcdTanner->st.n.linearVelocity[2] + reaction[2];

				pcdTanner->hd.aacc[2] -= FIXEDH(lever[1] * reaction[0]);
				pcdTanner->hd.aacc[0] += FIXEDH(lever[1] * reaction[2]);
				pcdTanner->hd.aacc[1] += FIXEDH(lever[2] * reaction[0]) - FIXEDH(lever[0] * reaction[2]);
			}

			pcdTanner->hd.where.t[0] -= FIXEDH(pcdTanner->st.n.linearVelocity[0]);
			pcdTanner->hd.where.t[2] -= FIXEDH(pcdTanner->st.n.linearVelocity[2]);
		}
		cp1--;
	} while (cp1 >= car_data);

	return 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ PingOutPed(struct PEDESTRIAN *pPed /*$a2*/)
// line 3915, offset 0x000731f8
/* begin block 1 */
// Start line: 3916
// Start offset: 0x000731F8
// Variables:
// 		int px; // $a0
// 		int pz; // $v1
// 		int ps; // $a0
/* end block 1 */
// End offset: 0x00073270
// End Line: 3938

/* begin block 2 */
// Start line: 23590
/* end block 2 */
// End Line: 23591

/* begin block 3 */
// Start line: 24071
/* end block 3 */
// End Line: 24072

// [D] [T]
int PingOutPed(PEDESTRIAN* pPed)
{
	int pz;
	int px;
	int ps;

	px = pPed->position.vx - player[0].pos[0];
	pz = pPed->position.vz - player[0].pos[2];

	ps = px * px + pz * pz;

	if (ps <= 20496 * 20496)
		return (-player[0].pos[1] - pPed->position.vy < 513) ^ 1;

	return 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupCivJump(struct PEDESTRIAN *pPed /*$s1*/, struct _CAR_DATA *cp /*$s0*/)
// line 3946, offset 0x00071054
/* begin block 1 */
// Start line: 3947
// Start offset: 0x00071054
// Variables:
// 		long disp[4]; // stack offset -48
// 		long dir[4]; // stack offset -32
// 		int angle; // $s0

/* begin block 1.1 */
// Start line: 3960
// Start offset: 0x000710C0
// Variables:
// 		short scale; // $a2
/* end block 1.1 */
// End offset: 0x000710E4
// End Line: 3967

/* begin block 1.2 */
// Start line: 4008
// Start offset: 0x000711E8
/* end block 1.2 */
// End offset: 0x000712AC
// End Line: 4027
/* end block 1 */
// End offset: 0x00071324
// End Line: 4040

/* begin block 2 */
// Start line: 9290
/* end block 2 */
// End Line: 9291

/* begin block 3 */
// Start line: 9330
/* end block 3 */
// End Line: 9331

// [D] [T]
void SetupCivJump(PEDESTRIAN* pPed, _CAR_DATA* cp)
{
	int dz;
	short scale;
	int dx;
	short angle;
	long dir[4];

	if (pPed->type != PED_ACTION_JUMP)
	{
		pPed->frame1 = 0;
		pPed->speed = 30;

		if (cp == &car_data[player[0].playerCarId])
		{
			if (player[0].horn.on != 0)
				scale = 0x800;
			else
				scale = 0x1000;

			NoteFelony(&felonyData, 1, scale);
		}
	}

	pPed->type = PED_ACTION_JUMP;
	pPed->flags |= 0x10;
	pPed->fpAgitatedState = CivPedJump;

	SetupPedMotionData(pPed);

	if (cp == NULL)
	{
		if (bAvoidTanner == 0)
		{
			angle = ratan2(pPed->position.vx - explosion[bAvoidBomb].pos.vx, pPed->position.vz - explosion[bAvoidBomb].pos.vz) - 2048;
		}
		else
		{
			dx = player[0].pPed->position.vx - pPed->position.vx;
			dz = player[0].pPed->position.vz - pPed->position.vz;

			dir[0] = player[0].pPed->speed * rcossin_tbl[(player[0].pPed->dir.vy - 0x800U & 0xfff) * 2 + 1];
			dir[2] = player[0].pPed->speed * rcossin_tbl[(player[0].pPed->dir.vy - 0x800U & 0xfff) * 2];
			
			// [A] fuck....
			if (FIXED(-dir[0]) * dx + FIXED(dir[2]) * dz + 0x800 < 0)
				angle = -1024;
			else
				angle = 1024;

			angle += player[0].pPed->dir.vy;
		}
	}
	else
	{
		dx = cp->hd.where.t[0] - pPed->position.vx;
		dz = cp->hd.where.t[2] - pPed->position.vz;

		if (cp->st.n.linearVelocity[2] != 0 || cp->st.n.linearVelocity[0] != 0)
		{
			int carVelDisp;
			carVelDisp = (cp->st.n.linearVelocity[2] * dx - cp->st.n.linearVelocity[0] * dz + 2048);
			
			angle = ((short)~(ushort)(carVelDisp >> 0x1c) >> 0xf & 0x800U) - ratan2(cp->st.n.linearVelocity[2], cp->st.n.linearVelocity[0]);
		}
		else
		{
			angle = ratan2(dz, dx);;
		}
	}

	pPed->dir.vy = angle & 0xfff;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivPedJump(struct PEDESTRIAN *pPed /*$s0*/)
// line 4047, offset 0x00072cf0
/* begin block 1 */
// Start line: 4048
// Start offset: 0x00072CF0
/* end block 1 */
// End offset: 0x00072DA0
// End Line: 4073

/* begin block 2 */
// Start line: 20349
/* end block 2 */
// End Line: 20350

/* begin block 3 */
// Start line: 8094
/* end block 3 */
// End Line: 8095

// [D] [T]
void CivPedJump(PEDESTRIAN* pPed)
{
	if (pPed->frame1 == 2)
		pPed->speed *= 2;
	else if (pPed->frame1 == 14)
		pPed->speed /= 2;

	AnimatePed(pPed);

	if (pPed->frame1 > 29)
	{
		pPed->frame1 = 0;
		pPed->type = PED_ACTION_CIVWALK;
		pPed->fpRestState = CivPedWalk;

		SetupPedMotionData(pPed);

		pPed->fpAgitatedState = NULL;
		pPed->flags &= ~0x10;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupCivPedWalk(struct PEDESTRIAN *pPed /*$s0*/)
// line 4080, offset 0x00073270
/* begin block 1 */
// Start line: 24276
/* end block 1 */
// End Line: 24277

/* begin block 2 */
// Start line: 24419
/* end block 2 */
// End Line: 24420

// [D] [T]
void SetupCivPedWalk(PEDESTRIAN* pPed)
{
	pPed->flags |= 0x10;

	if (pPed->type == PED_ACTION_CIVRUN)
		pPed->speed = 30;
	else
		pPed->speed = 10;

	SetupPedMotionData(pPed);

	pPed->frame1 = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivPedWalk(struct PEDESTRIAN *pPed /*$s0*/)
// line 4101, offset 0x00071324
/* begin block 1 */
// Start line: 4102
// Start offset: 0x00071324
// Variables:
// 		int turn; // $a1
// 		int offset1; // $t0
// 		int offset2; // $v1
// 		int lookahead; // $s3
// 		int speed; // $s1
/* end block 1 */
// End offset: 0x000715FC
// End Line: 4182

/* begin block 2 */
// Start line: 9615
/* end block 2 */
// End Line: 9616

/* begin block 3 */
// Start line: 9677
/* end block 3 */
// End Line: 9678

// [D] [T]
void CivPedWalk(PEDESTRIAN* pPed)
{
	int dir;
	int turn;

	if ((pPed->flags & 0x10U) == 0)
		SetupCivPedWalk(pPed);

	if (pPed->finished_turn == 9)
		dir = pPed->dir.vy + 2048;
	else
		dir = pPed->dir.vy + 1850;

	if ((pPed->flags & 2U) == 0)
	{
		if (IsPavement(pPed->position.vx + (rcossin_tbl[(dir & 0xfff) * 2] >> 5),
			pPed->position.vy,
			pPed->position.vz + (rcossin_tbl[(dir & 0xfff) * 2 + 1] >> 5), pPed) == 0)
		{
			if (pPed->finished_turn == 9)
			{
				dir = pPed->dir.vy + 0xa00U & 0xfff;

				if (IsPavement(
					pPed->position.vx + FIXED(rcossin_tbl[dir * 2] * 0x80),
					pPed->position.vy,
					pPed->position.vz + FIXED(rcossin_tbl[dir * 2 + 1] * 0x80), NULL) == 0)

					pPed->flags &= ~0x2000;
				else
					pPed->flags |= 0x2000;
			}

			if (pPed->flags & 0x2000)
				turn = 128;
			else
				turn = -128;

			if (pPed->doing_turn < 32)
			{
				SetPedestrianTurn(pPed, turn);
				pPed->doing_turn++;
			}
			else
			{
				dir = pPed->dir.vy + 0x800U & 0xfff;

				pPed->velocity.vx = FIXED(pPed->speed * rcossin_tbl[dir * 2]);
				pPed->velocity.vz = FIXED(pPed->speed * rcossin_tbl[dir * 2 + 1]);
			}
			pPed->finished_turn = 0;
		}
		else
		{
			pPed->doing_turn = 0;

			if (pPed->finished_turn++ > 8)
			{
				pPed->dir.vy += 0x200U & 0xfc00;

				dir = pPed->dir.vy + 0x800U & 0xfff;

				pPed->velocity.vx = FIXED(pPed->speed * rcossin_tbl[dir * 2]);
				pPed->velocity.vz = FIXED(pPed->speed * rcossin_tbl[dir * 2 + 1]);

				pPed->finished_turn = 9;
			}
		}
	}
	else
	{
		pPed->speed = 0;
		pPed->dir.vy += pPed->head_rot;
	}

	AnimatePed(pPed);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CivPedSit(struct PEDESTRIAN *pPed /*$a0*/)
// line 4190, offset 0x00072ce8
/* begin block 1 */
// Start line: 4192
// Start offset: 0x00072CE8
/* end block 1 */
// End offset: 0x00072CF0
// End Line: 4208

/* begin block 2 */
// Start line: 20475
/* end block 2 */
// End Line: 20476

/* begin block 3 */
// Start line: 20476
/* end block 3 */
// End Line: 20477

/* begin block 4 */
// Start line: 20480
/* end block 4 */
// End Line: 20481

// [D] [T]
void CivPedSit(PEDESTRIAN* pPed)
{
	pPed->frame1 = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandlePedestrians()
// line 4221, offset 0x0007211c
/* begin block 1 */
// Start line: 4223
// Start offset: 0x0007211C
/* end block 1 */
// End offset: 0x0007215C
// End Line: 4457

/* begin block 2 */
// Start line: 13906
/* end block 2 */
// End Line: 13907

/* begin block 3 */
// Start line: 13907
/* end block 3 */
// End Line: 13908

/* begin block 4 */
// Start line: 13925
/* end block 4 */
// End Line: 13926

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void HandlePedestrians(void)
{
	if (gInGameCutsceneActive != 0 || NumPlayers != 1)
		return;

	BuildCarCollisionBox();
	ControlPedestrians();
	PingInPedestrians();
}



// decompiled code
// original method signature: 
// void /*$ra*/ PedestrianActionInit_WalkToTarget(struct PEDESTRIAN *pPed /*$s0*/)
// line 4465, offset 0x0007283c
/* begin block 1 */
// Start line: 4466
// Start offset: 0x0007283C
// Variables:
// 		int dir; // $v1
/* end block 1 */
// End offset: 0x000728B8
// End Line: 4496

/* begin block 2 */
// Start line: 18892
/* end block 2 */
// End Line: 18893

/* begin block 3 */
// Start line: 8930
/* end block 3 */
// End Line: 8931

// [D] [T]
void PedestrianActionInit_WalkToTarget(PEDESTRIAN* pPed)
{
	int dir;
	dir = CalcPedestrianDirection(0, (pPed->position).vx, (pPed->position).vz, &pPed->target);

	if (dir == 0)
		return;

	pPed->last_dir = dir;

	if (dir == 1)
		pPed->dir.vy = 1024;
	else if (dir == 2)
		pPed->dir.vy = 3072;
	else if (dir == 4)
		pPed->dir.vy = 0;
	else if (dir == 8)
		pPed->dir.vy = 2048;

	CorrectPathPosition(pPed, (VECTOR*)&pPed->position);
}



// decompiled code
// original method signature: 
// void /*$ra*/ CorrectPathPosition(struct PEDESTRIAN *pedestrian /*$a0*/, struct VECTOR *position /*$a1*/)
// line 4508, offset 0x000715fc
/* begin block 1 */
// Start line: 4510
// Start offset: 0x000715FC
// Variables:
// 		struct VECTOR vec; // stack offset -16
/* end block 1 */
// End offset: 0x000715FC
// End Line: 4610

/* begin block 2 */
// Start line: 10180
/* end block 2 */
// End Line: 10181

/* begin block 3 */
// Start line: 10507
/* end block 3 */
// End Line: 10508

/* begin block 4 */
// Start line: 10508
/* end block 4 */
// End Line: 10509

/* begin block 5 */
// Start line: 10608
/* end block 5 */
// End Line: 10609

// [D] [T]
void CorrectPathPosition(PEDESTRIAN* pedestrian, VECTOR* position)
{
}



// decompiled code
// original method signature: 
// int /*$ra*/ CalcPedestrianDirection(int last_dir /*$a0*/, int wx /*$s5*/, int wz /*$s6*/, struct VECTOR *target /*$s3*/)
// line 4619, offset 0x00071608
/* begin block 1 */
// Start line: 4620
// Start offset: 0x00071608
// Variables:
// 		int dir; // $s2
// 		int num; // $s1
// 		int rx; // $v1
// 		int rz; // $a0
// 		int mask; // $s0

/* begin block 1.1 */
// Start line: 4669
// Start offset: 0x000716C0
/* end block 1.1 */
// End offset: 0x0007170C
// End Line: 4681
/* end block 1 */
// End offset: 0x000717AC
// End Line: 4734

/* begin block 2 */
// Start line: 10729
/* end block 2 */
// End Line: 10730

/* begin block 3 */
// Start line: 10737
/* end block 3 */
// End Line: 10738

// [D] [T]
int CalcPedestrianDirection(int last_dir, int wx, int wz, VECTOR* target)
{
	int num;
	int rx;
	int rz;
	int dir;
	int mask;
	int cnt;
	
	mask = pedestrian_roads.west == -20;
	dir = mask;

	if (pedestrian_roads.east == -20)
	{
		mask |= 2;
		dir++;
	}

	if (pedestrian_roads.north == -20)
	{
		mask |= 4;
		dir++;
	}

	if (pedestrian_roads.south == -20)
	{
		mask |= 8;
		dir++;
	}

	num = mask & last_dir;

	if (num == 0)
	{
		if(dir > 1)
		{
			num = 16;

			cnt = Random2(0) % dir + 1;

			while (cnt != 0)
			{
				num >>= 1;

				if (mask & num)
					cnt--;
			}

			num = mask & num;
		}
		else
		{
			num = mask;
		}
	}

	rx = wx & 0xfffffc00;
	rz = wz & 0xfffffc00;

	if (num == 1)
	{
		target->vx = rx - 512;
		target->vz = rz + 512;
	}
	else if (num == 2)
	{
		target->vx = rx + 1536;
		target->vz = rz + 512;
	}
	else if (num == 4)
	{
		target->vx = rx + 512;
		target->vz = rz + 1536;
	}
	else if (num == 8)
	{
		target->vx = rx + 512;
		target->vz = rz - 512;
	}

	target->vy = 0;

	return num;
}



// decompiled code
// original method signature: 
// int /*$ra*/ IsPavement(int x /*$a0*/, int y /*$a1*/, int z /*$a2*/, struct PEDESTRIAN *pPed /*$s0*/)
// line 4845, offset 0x000725b8
/* begin block 1 */
// Start line: 4846
// Start offset: 0x000725B8
// Variables:
// 		struct VECTOR vec; // stack offset -24
// 		int r; // $v1
/* end block 1 */
// End offset: 0x00072644
// End Line: 4917

/* begin block 2 */
// Start line: 18844
/* end block 2 */
// End Line: 18845

/* begin block 3 */
// Start line: 9690
/* end block 3 */
// End Line: 9691

/* begin block 4 */
// Start line: 18854
/* end block 4 */
// End Line: 18855

// [D] [T]
int IsPavement(int x, int y, int z, PEDESTRIAN* pPed)
{
	int r;
	VECTOR v;

	v.vy = -y;
	v.vx = x;
	v.vz = z;
	r = GetSurfaceIndex(&v);

	if (r == -20)
		return (RoadInCell(&v) != 0);

	if (pPed)
	{
		if (r != -26 && r != -23 && r != -32)
			return 0;

		pPed->flags |= 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetPedestrianTurn(struct PEDESTRIAN *pedestrian /*$a0*/, int turn /*$a1*/)
// line 4924, offset 0x00072500
/* begin block 1 */
// Start line: 4925
// Start offset: 0x00072500
// Variables:
// 		int dir; // $a2
// 		int speed; // $v1
/* end block 1 */
// End offset: 0x00072584
// End Line: 4935

/* begin block 2 */
// Start line: 15021
/* end block 2 */
// End Line: 15022

/* begin block 3 */
// Start line: 18487
/* end block 3 */
// End Line: 18488

/* begin block 4 */
// Start line: 18488
/* end block 4 */
// End Line: 18489

// [D] [T]
void SetPedestrianTurn(PEDESTRIAN* pedestrian, int turn)
{
	int speed;
	int dir;

	dir = pedestrian->dir.vy + turn & 0xfff;

	pedestrian->dir.vy = dir;

	dir = dir + 0x800 & 0xfff;

	pedestrian->position.vz -= pedestrian->velocity.vz;
	pedestrian->position.vx -= pedestrian->velocity.vx;

	speed = pedestrian->speed;
	
	pedestrian->velocity.vx = FIXEDH(speed * rcossin_tbl[dir * 2]);
	pedestrian->velocity.vz = FIXEDH(speed * rcossin_tbl[dir * 2 + 1]);
}



// decompiled code
// original method signature: 
// struct SEATED_PEDESTRIANS * /*$ra*/ FindSeated()
// line 4943, offset 0x00072644
/* begin block 1 */
// Start line: 4945
// Start offset: 0x00072644
// Variables:
// 		struct SEATED_PEDESTRIANS *seatedptr; // $s0

/* begin block 1.1 */
// Start line: 4950
// Start offset: 0x0007266C
// Variables:
// 		int dx; // $v1
// 		int dz; // $v0
// 		int distsqr; // $v1
// 		int count1; // $a2
/* end block 1.1 */
// End offset: 0x00072724
// End Line: 4975
/* end block 1 */
// End offset: 0x00072738
// End Line: 4977

/* begin block 2 */
// Start line: 19027
/* end block 2 */
// End Line: 19028

/* begin block 3 */
// Start line: 19054
/* end block 3 */
// End Line: 19055

/* begin block 4 */
// Start line: 19055
/* end block 4 */
// End Line: 19056

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
SEATED_PEDESTRIANS* FindSeated(void)
{
	int dz;
	int dx;
	int count1;
	SEATED_PEDESTRIANS* seatedptr;

	if (!seated_pedestrian)
		return NULL;

	if (seated_pedestrian->rotation == 9999)
		return NULL;

	count1 = 3;

	do
	{
		seatedptr = seated_pedestrian + seated_count;
		seated_count++;

		if (seatedptr->rotation == 9999)
		{
			seated_count = 0;
			seatedptr = seated_pedestrian;
		}

		dx = FIXED(seatedptr->x - player[0].pos[0]);
		dz = FIXED(seatedptr->z - player[0].pos[2]);

		if (seatedptr->index == 0)
		{
			count1--;
		
			if((dx * dx + dz * dz) - 11U < 29)
			{
				add_seated(seatedptr, seated_count);
				return seatedptr;
			}
		}

	} while (count1 != 0);

	return NULL;
}



// decompiled code
// original method signature: 
// struct SEATED_PEDESTRIANS * /*$ra*/ FindTannerASeat(struct PEDESTRIAN *pPed /*$t4*/)
// line 4984, offset 0x000717ac
/* begin block 1 */
// Start line: 4985
// Start offset: 0x000717AC
// Variables:
// 		struct SEATED_PEDESTRIANS *seatedptr; // $a2
// 		struct SEATED_PEDESTRIANS *theOne; // $t1
// 		int dx; // $a0
// 		int dz; // $v1
// 		int distsqr; // $v0
// 		int bestSqr; // $t2
/* end block 1 */
// End offset: 0x000718C8
// End Line: 5023

/* begin block 2 */
// Start line: 11491
/* end block 2 */
// End Line: 11492

/* begin block 3 */
// Start line: 11493
/* end block 3 */
// End Line: 11494

// [D] [T]
SEATED_PEDESTRIANS* FindTannerASeat(PEDESTRIAN* pPed)
{
	int dx, dz;
	int distSqr;
	int bestSqr;
	SEATED_PEDESTRIANS* seatedptr;
	SEATED_PEDESTRIANS* theOne;
	
	theOne = NULL;
	bestSqr = 4096;
	seated_count = 0;

	if (seated_pedestrian->rotation != 9999)
	{
		seatedptr = seated_pedestrian;
		seated_count = 0;

		do
		{
			dx = ABS(seatedptr->x - pPed->position.vx);
			dz = ABS(seatedptr->z - pPed->position.vz);
			
			seated_count++;

			if (dx < 900 && dz < 900)
			{
				distSqr = FIXED(dx * dx + dz * dz);
	
				if(distSqr < bestSqr)
				{
					theOne = seatedptr;
					bestSqr = distSqr;
				}
			}

			seatedptr++;
		} while (seatedptr->rotation != 9999);
	}

	if (bestSqr < 6 && theOne)
	{
		pPed->dir.vy = theOne->rotation;
		pPed->position.vx = theOne->x;
		pPed->position.vz = theOne->z;

		return theOne;
	}

	return NULL;
}



// decompiled code
// original method signature: 
// void /*$ra*/ add_seated(struct SEATED_PEDESTRIANS *seatedptr /*$s0*/, int seat_index /*$s2*/)
// line 5031, offset 0x000718c8
/* begin block 1 */
// Start line: 5032
// Start offset: 0x000718C8
// Variables:
// 		struct PEDESTRIAN *pedestrian; // $s1
// 		int index; // $v0
/* end block 1 */
// End offset: 0x00071A44
// End Line: 5076

/* begin block 2 */
// Start line: 11581
/* end block 2 */
// End Line: 11582

/* begin block 3 */
// Start line: 11590
/* end block 3 */
// End Line: 11591

/* begin block 4 */
// Start line: 11596
/* end block 4 */
// End Line: 11597

// [D] [T]
void add_seated(SEATED_PEDESTRIANS* seatedptr, int seat_index)
{
	PEDESTRIAN* pedptr;
	long rnd;

	if (num_pedestrians < 20)
	{
		pedptr = CreatePedestrian();

		if (!pedptr)
			return;

		seatedptr->index = 2;
	
		pedptr->type = PED_ACTION_CIVSIT;
		pedptr->speed = 0;
		pedptr->velocity.vx = 0;
		pedptr->velocity.vy = 0;
		pedptr->velocity.vz = 0;
		pedptr->dir.vy = seatedptr->rotation;
		pedptr->position.vx = seatedptr->x;
		pedptr->position.vz = seatedptr->z;
		pedptr->position.vy = player[0].pos[1];
		
		pedptr->position.vy = -75 - MapHeight((VECTOR*)&pedptr->position);

		pedptr->index = 1;
		pedptr->seat_index = seat_index;
		pedptr->pedType = CIVILIAN;
	
		SetupPedestrian(pedptr);

		pedptr->fpAgitatedState = NULL;
		pedptr->fpRestState = CivPedSit;

		pedptr->pallet = (Random2(0) % 5) + (Random2(0) % 5) * 16;
		rnd = Random2(0);

		if ((rnd / 6) * 6 == rnd - 3)
			pedptr->flags |= 0x4000;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ set_coll_box(int index /*$t2*/, struct _CAR_DATA *cp /*$t0*/, int offset /*$t3*/)
// line 5084, offset 0x00071a5c
/* begin block 1 */
// Start line: 5085
// Start offset: 0x00071A5C
// Variables:
// 		struct VECTOR BoxCentre; // stack offset -16
// 		int boxsize; // $t1
/* end block 1 */
// End offset: 0x00071B74
// End Line: 5110

/* begin block 2 */
// Start line: 11714
/* end block 2 */
// End Line: 11715

CAR_COLLISION_BOX collision_box[8];
_CAR_DATA* collision_car_ptr[8];

// [D]
void set_coll_box(int index, _CAR_DATA* cp, int offset)
{
	int isPlayerCar;
	int boxSize;

	VECTOR BoxCentre;

	if (index >= 8)
		return;

	boxSize = 400;

	isPlayerCar = (cp == &car_data[player[0].playerCarId]);
	
	if (player[0].horn.on)
	{
		if (isPlayerCar)
			boxSize = 1200;
		else
			boxSize = 260;
	}

	if (!isPlayerCar)
		boxSize -= 140;

	collision_car_ptr[index] = cp;

	BoxCentre.vx = cp->hd.where.t[0] + (cp->st.n.linearVelocity[0] >> (offset & 0x1fU));
	BoxCentre.vz = cp->hd.where.t[2] + (cp->st.n.linearVelocity[2] >> (offset & 0x1fU));

	collision_box[index].min_x = BoxCentre.vx - boxSize;
	collision_box[index].min_z = BoxCentre.vz - boxSize;
	collision_box[index].max_x = BoxCentre.vx + boxSize;
	collision_box[index].max_z = BoxCentre.vz + boxSize;
}



// decompiled code
// original method signature: 
// void /*$ra*/ BuildCarCollisionBox()
// line 5118, offset 0x00071b7c
/* begin block 1 */
// Start line: 5120
// Start offset: 0x00071B7C
// Variables:
// 		struct _CAR_DATA *cp; // $s3
// 		int count1; // $s4
// 		int i; // $t1

/* begin block 1.1 */
// Start line: 5146
// Start offset: 0x00071CBC
// Variables:
// 		int x; // $a0
// 		int z; // $a2
/* end block 1.1 */
// End offset: 0x00071D58
// End Line: 5155
/* end block 1 */
// End offset: 0x00071E0C
// End Line: 5171

/* begin block 2 */
// Start line: 11805
/* end block 2 */
// End Line: 11806

/* begin block 3 */
// Start line: 11806
/* end block 3 */
// End Line: 11807

/* begin block 4 */
// Start line: 11808
/* end block 4 */
// End Line: 11809

/* WARNING: Unknown calling convention yet parameter storage is locked */

CAR_COLLISION_BOX extra_collision_boxes[5];
CAR_COLLISION_BOX tanner_collision_box;
int num_extra_boxes_set;
int collision_boxes_set;

// [D] [T]
void BuildCarCollisionBox(void)
{
	CAR_COLLISION_BOX* cbox;
	int dir;
	int vx, vz;
	int index;
	_ExOBJECT* expl;
	_CAR_DATA* cp;

	if (player[0].playerCarId != -1) // [A] ASan bug fix
	{
		set_coll_box(0, &car_data[player[0].playerCarId], 8);
		set_coll_box(1, &car_data[player[0].playerCarId], 9);
	}

	cp = car_data + (CameraCnt & 3);

	collision_boxes_set = 2;

	while (cp < car_data + MAX_CARS)
	{
		if (cp != &car_data[player[0].playerCarId] && cp->controlType != CONTROL_TYPE_NONE)
		{
			set_coll_box(collision_boxes_set, cp, 8);
			collision_boxes_set++;
		}

		cp += 4; // [A] WTF?
	}

	if (player[0].playerType == 2)
	{
		dir = player[0].pPed->dir.vy - 0x800U & 0xfff;

		vx = FIXED(player[0].pPed->speed * rcossin_tbl[dir * 2] * 4);
		vz = FIXED(player[0].pPed->speed * rcossin_tbl[dir * 2 + 1] * 4);
		
		tanner_collision_box.min_x = player[0].pPed->position.vx + vx - 148;
		tanner_collision_box.max_x = player[0].pPed->position.vx + vx + 148;
		tanner_collision_box.min_z = player[0].pPed->position.vz + vz - 148;
		tanner_collision_box.max_z = player[0].pPed->position.vz + vz + 148;
	}

	num_extra_boxes_set = 0;
	expl = explosion;
	
	index = 4;
	do
	{
		if (expl->time >= 2048)
		{
			cbox = extra_collision_boxes + num_extra_boxes_set;
			
			cbox->min_x = expl->pos.vx - 1952;
			cbox->max_x = expl->pos.vx + 1952;

			cbox->min_z = expl->pos.vz - 1952;
			cbox->max_z = expl->pos.vz + 1952;

			num_extra_boxes_set++;
		}

		index--;
		expl++;
	} while (index > -1);
}



// decompiled code
// original method signature: 
// struct _CAR_DATA * /*$ra*/ CheckForCar(struct PEDESTRIAN *pedestrian /*$s3*/)
// line 5178, offset 0x00072738
/* begin block 1 */
// Start line: 5179
// Start offset: 0x00072738
// Variables:
// 		int count; // $s0

/* begin block 1.1 */
// Start line: 5183
// Start offset: 0x00072770
/* end block 1.1 */
// End offset: 0x00072790
// End Line: 5204

/* begin block 1.2 */
// Start line: 5206
// Start offset: 0x000727B4
/* end block 1.2 */
// End offset: 0x000727B4
// End Line: 5213

/* begin block 1.3 */
// Start line: 5217
// Start offset: 0x00072800
/* end block 1.3 */
// End offset: 0x0007281C
// End Line: 5221
/* end block 1 */
// End offset: 0x0007283C
// End Line: 5223

/* begin block 2 */
// Start line: 19327
/* end block 2 */
// End Line: 19328

/* begin block 3 */
// Start line: 19529
/* end block 3 */
// End Line: 19530

/* begin block 4 */
// Start line: 19531
/* end block 4 */
// End Line: 19532

// [D] [T]
_CAR_DATA* CheckForCar(PEDESTRIAN* pedestrian)
{
	int count;

	count = 0;

	while (count < collision_boxes_set)
	{
		if (CheckForPlayerCar(pedestrian, &collision_box[count]) != 0)
			return collision_car_ptr[count];

		count++;
	}

	count = 0;
	while (count < num_extra_boxes_set)
	{
		if (CheckForPlayerCar(pedestrian, &extra_collision_boxes[count]))
		{
			bAvoidBomb = count;
			break;
		}

		count++;
	}


	if (player[0].playerType == 2 && CheckForPlayerCar(pedestrian, &tanner_collision_box) != 0)
		bAvoidTanner = 1;

	return NULL;
}



// decompiled code
// original method signature: 
// int /*$ra*/ CheckForPlayerCar(struct PEDESTRIAN *pedestrian /*$a0*/, struct CAR_COLLISION_BOX *collision_box /*$a1*/)
// line 5231, offset 0x000732c0
/* begin block 1 */
// Start line: 26722
/* end block 1 */
// End Line: 26723

/* begin block 2 */
// Start line: 26723
/* end block 2 */
// End Line: 26724

// [D] [T]
int CheckForPlayerCar(PEDESTRIAN* pedestrian, CAR_COLLISION_BOX* collision_box)
{
	if (pedestrian->position.vx >= collision_box->min_x && 
		pedestrian->position.vx <= collision_box->max_x &&
		pedestrian->position.vz >= collision_box->min_z && 
		pedestrian->position.vz <= collision_box->max_z)
	{
		return 1;
	}

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ CalculatePedestrianInterest(struct PEDESTRIAN *pPed /*$s0*/)
// line 5249, offset 0x00071e0c
/* begin block 1 */
// Start line: 5250
// Start offset: 0x00071E0C
// Variables:
// 		int interest; // $a2
// 		int dist; // $v1
// 		struct _CAR_DATA *pCar; // $a2
// 		struct VECTOR v1; // stack offset -40
// 		struct VECTOR v2; // stack offset -24
/* end block 1 */
// End offset: 0x00071F44
// End Line: 5318

/* begin block 2 */
// Start line: 12043
/* end block 2 */
// End Line: 12044

/* begin block 3 */
// Start line: 12122
/* end block 3 */
// End Line: 12123

/* begin block 4 */
// Start line: 12128
/* end block 4 */
// End Line: 12129

int basic_car_interest;

// [D] [T]
void CalculatePedestrianInterest(PEDESTRIAN* pPed)
{
	_CAR_DATA* pCar;
	int carId;
	int interest;
	VECTOR v1;
	VECTOR v2;

	carId = player[0].playerCarId;

	if (carId == -1) // [A] ASan bug fix
		return;

	pCar = &car_data[carId];

	basic_car_interest = (pCar->hd.wheel_speed >> 10) + pCar->totalDamage;

	v1.vx = pPed->position.vx - pCar->hd.where.t[0];
	v1.vz = pPed->position.vz - pCar->hd.where.t[2];

	v2.vx = (v1.vx < 0) ? -v1.vx : v1.vx;
	v2.vz = (v1.vz < 0) ? -v1.vz : v1.vz;

	int dist = (v2.vx + v2.vz);

	if (dist < 6001)
		interest = 6000 - dist;
	else
		interest = 0;

	if (pPed->type == PED_ACTION_JUMP)
	{
		pPed->head_rot = pPed->dir.vy + ratan2(v1.vz, v1.vx) + 3072 & 0xfff;
		return;
	}

	if (interest + basic_car_interest > 2999)
	{
		pPed->interest = interest + basic_car_interest;
		pPed->head_rot = pPed->dir.vy + ratan2(v1.vz, v1.vx) + 3072 & 0xfff;

		if (pPed->head_rot - 897U > 2302)
			return;
	}

	pPed->head_rot = 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ PedSurfaceType(struct VECTOR *ped_pos /*$a0*/)
// line 5325, offset 0x00072584
/* begin block 1 */
// Start line: 5330
// Start offset: 0x00072584
// Variables:
// 		struct _sdPlane *sfc_ptr; // $v0
/* end block 1 */
// End offset: 0x000725B8
// End Line: 5335

/* begin block 2 */
// Start line: 18922
/* end block 2 */
// End Line: 18923

/* begin block 3 */
// Start line: 19313
/* end block 3 */
// End Line: 19314

/* begin block 4 */
// Start line: 19317
/* end block 4 */
// End Line: 19318

// [D] [T]
int PedSurfaceType(VECTOR* ped_pos)
{
	_sdPlane* sfc_ptr;
	sfc_ptr = sdGetCell(ped_pos);

	if (!sfc_ptr)
		return 0;

	return sfc_ptr->surface;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessChairLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
// line 5344, offset 0x00073328
/* begin block 1 */
// Start line: 26847
/* end block 1 */
// End Line: 26848

/* begin block 2 */
// Start line: 26951
/* end block 2 */
// End Line: 26952

/* begin block 3 */
// Start line: 26952
/* end block 3 */
// End Line: 26953

// [D] [T]
void ProcessChairLump(char* lump_file, int lump_size)
{
	seated_pedestrian = (SEATED_PEDESTRIANS*)lump_file;
}





