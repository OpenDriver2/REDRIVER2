#include "driver2.h"
#include "pedest.h"
#include "players.h"
#include "mission.h"
#include "objcoll.h"
#include "cosmetic.h"
#include "models.h"
#include "dr2roads.h"
#include "motion_c.h"
#include "convert.h"
#include "sound.h"
#include "pad.h"
#include "civ_ai.h"
#include "glaunch.h"
#include "cutscene.h"
#include "camera.h"
#include "pause.h"
#include "ai.h"
#include "cars.h"
#include "felony.h"
#include "job_fx.h"
#include "bcollide.h"
#include "gamesnd.h"
#include "map.h"
#include "system.h"
#include "handling.h"

#include "ASM/rndrasm.h"

struct CAR_COLLISION_BOX
{
	int min_x, max_x;
	int min_z, max_z;
};

typedef struct SEATED_PEDESTRIANS
{
	int x;
	int z;
	short rotation;
	char index;
	char pad;
} *SEATEDPTR;

MODEL* pmTannerModels[17] = { 0 };
MODEL* pmJerichoModels[6] = { 0 };

void PedDoNothing(LPPEDESTRIAN pPed);
void PedUserWalker(LPPEDESTRIAN pPed);
void PedUserRunner(LPPEDESTRIAN pPed);
void PedGetInCar(LPPEDESTRIAN pPed);
void PedGetOutCar(LPPEDESTRIAN pPed);
void PedCarryOutAnimation(LPPEDESTRIAN pPed);
void CivPedDoNothing(LPPEDESTRIAN pPed);
void CivPedWalk(LPPEDESTRIAN pPed);
void CivPedSit(LPPEDESTRIAN pPed);
void CivPedJump(LPPEDESTRIAN pPed);
void PedPressButton(LPPEDESTRIAN pPed);
void TannerSitDown(LPPEDESTRIAN pPed);
void CopStand(LPPEDESTRIAN pPed);
void CivGetIn(LPPEDESTRIAN pPed);

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

SVECTOR tannerLookAngle = { 0, 0, 0, 0 };

const int tannerTurnMax = 16;
const int tannerTurnStep = 4;

int bKillTanner = 0;

SEATEDPTR seated_pedestrian;	// lump
int seated_count;
int maxSeated;
static int numTannerPeds = 0;
static int numCopPeds = 0;
int pinginPedAngle = 0;

PEDESTRIAN pedestrians[MAX_PEDESTRIANS];

LPPEDESTRIAN pUsedPeds = NULL;	// linked list of pedestrians
LPPEDESTRIAN pFreePeds = NULL;
LPPEDESTRIAN pHold = NULL;

int max_pedestrians = 28;
int num_pedestrians;

int max_sitter_peds,max_placed_peds;

#ifndef PSX
#define MAX_TANNER_PEDS 8
#define NO_MORE_PEDS() (num_pedestrians >= max_placed_peds)
#else
#define NO_MORE_PEDS() (num_pedestrians >= MAX_PLACED_PEDS)
#endif

char ping_in_pedestrians = 0;

int bKilled = 0;

PEDESTRIAN_ROADS pedestrian_roads;

u_int tannerPad;
extern short padd;
SVECTOR camAngle;
static int oldCamView;

int bPower = 0;
int oldWeather = 0;
int powerCounter = 0;

extern int CheckForPlayerCar(LPPEDESTRIAN pedestrian, CAR_COLLISION_BOX* collision_box); // 0x000732C0
extern SEATEDPTR FindSeated(); // 0x00072644
extern SEATEDPTR FindTannerASeat(LPPEDESTRIAN pPed); // 0x000717AC
extern void add_seated(SEATEDPTR seatedptr, int seat_index); // 0x000718C8

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

// [D] [T]
void SetTannerPosition(VECTOR* pVec)
{
	LPPEDESTRIAN pPed;

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

#ifndef PSX
static int PED_PING_RADIUS = (250000 << 6);

int pedestrianDensityMap[] = { 28, 38, 48, 64 };
#else
const int PED_PING_RADIUS = (250000 << 6);
#endif

// [D] [T]
void InitPedestrians(void)
{
	int loop;
	SEATEDPTR seatedptr;

	memset((u_char*)pedestrians, 0, sizeof(pedestrians));
	DestroyPedestrians();

	max_pedestrians = 28;

#ifndef PSX
	if (gExtraConfig.gPedestrianDensity != 0)
		max_pedestrians = pedestrianDensityMap[gExtraConfig.gPedestrianDensity - 1];
#endif

	LPPEDESTRIAN lastPed = &pedestrians[0];

	lastPed->pPrev = NULL;

	for (loop = 1; loop < MAX_PEDESTRIANS; loop++)
	{
		LPPEDESTRIAN currPed = &pedestrians[loop];

		lastPed->pNext = currPed;
		currPed->pPrev = lastPed++;
	}

#ifndef PSX
	// terminate linked-list earlier if needed
	if (max_pedestrians < MAX_PEDESTRIANS)
	{
		lastPed = &pedestrians[max_pedestrians - 1];

		// break the chain
		lastPed->pNext->pPrev = NULL;
	}
#endif

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
	seated_count = 0;
	ping_in_pedestrians = 1;
	numCopPeds = 0;

#ifndef PSX
	int peds_available = (max_pedestrians-MAX_TANNER_PEDS);

	if (peds_available > 20)
	{
		// smoothly ramp up clustering factor when not using defaults
		PED_PING_RADIUS = ((250000 >> (peds_available / 20)) << 6);
	}
	else
	{
		PED_PING_RADIUS = (250000 << 6);
	}

	max_sitter_peds = peds_available / 4;
	max_placed_peds = peds_available - max_sitter_peds;
#endif
}

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

// [D] [T]
void DestroyCivPedestrians(void)
{
	LPPEDESTRIAN pPed;
	LPPEDESTRIAN pHPed;

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


// [D] [T]
void DestroyPedestrian(LPPEDESTRIAN pPed)
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

// [D] [T]
int PedSurfaceType(VECTOR* ped_pos)
{
	sdPlane* sfc_ptr;
	sfc_ptr = sdGetCell(ped_pos);

	if (!sfc_ptr)
		return 0;

	return sfc_ptr->surface;
}

// [D] [T]
LPPEDESTRIAN CreatePedestrian(void)
{
	LPPEDESTRIAN pNewPed;
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


// [D] [T]
void PlaceRoadBlockCops(void)
{
	int wbody;
	int lbody;
	int cs, sn;
	u_int dir;
	CAR_DATA* cp;
	CAR_DATA* pCar;
	int i;
	int numCops;
	CAR_DATA* pCopCars[16];
	LONGVECTOR4 disp;

	if (numCopPeds >= 8)
		return;

	numCops = 0;

	cp = car_data;
	do {
		if (cp->controlFlags & CONTROL_FLAG_COP_SLEEPING)
			pCopCars[numCops++] = cp;

		cp++;
	} while (cp < &car_data[MAX_CARS]);

	for (i = 0; i < numCops; i++)
	{
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

		dir = pCar->hd.direction + 2048;
		cs = RCOS(dir);
		sn = RSIN(dir);

		disp[0] = pCar->hd.where.t[0] - (FIXED(wbody * cs) - FIXED(lbody * sn));
		disp[1] = -pCar->hd.where.t[1];
		disp[2] = pCar->hd.where.t[2] + FIXED(wbody * sn) + FIXED(lbody * cs);

		if (CreatePedAtLocation(&disp, 12) != 0)
			numCopPeds++;

		disp[0] = pCar->hd.where.t[0] - (FIXED(wbody * cs) - FIXED(-lbody * sn));
		disp[1] = -pCar->hd.where.t[1];
		disp[2] = pCar->hd.where.t[2] + FIXED(wbody * sn) + FIXED(-lbody * cs);

		if (CreatePedAtLocation(&disp, 13) != 0)
			numCopPeds++;
	}
}

// [D] [T]
int CreatePedAtLocation(LONGVECTOR4* pPos, int pedType)
{
	LPPEDESTRIAN pPed;

	if ( NO_MORE_PEDS() )
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


// [D] [T]
void DrawAllPedestrians(void)
{
	LPPEDESTRIAN pPed;

	pPed = pUsedPeds;
	while (pPed != NULL)
	{
		if (PositionVisible((VECTOR*)&pPed->position) &&
			FrustrumCheck((VECTOR*)&pPed->position, 60) != -1)
		{
			if (pPed->pedType == TANNER_MODEL)
			{
				if (!bKillTanner)
					DrawTanner(pPed);
			}
			else if (pPed->pedType == OTHER_MODEL)
			{
				if (!bKillTanner)
					DrawCharacter(pPed);
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

// [D] [T]
int TannerActionHappening(void)
{
	LPPEDESTRIAN pPed = player[0].pPed;

	if (pPed && pPed->type == PED_ACTION_PRESSBUTTON)
		return pPed->frame1 == 14;

	return 0;
}

int bAvoidTanner = 0;
int bAvoidBomb = -1;

// [D] [T]
void ControlPedestrians(void)
{
	CAR_DATA* pCar;
	LPPEDESTRIAN pPed;
	LPPEDESTRIAN pPedNext;

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


// [D] [T]
void AnimatePed(LPPEDESTRIAN pPed)
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
		pPed->position.vx -= FIXED(pPed->speed * RSIN(dir));
		pPed->position.vz -= FIXED(pPed->speed * RCOS(-dir));
	}
	else
	{
		dir = pPed->dir.vy - 2048;
		pPed->position.vx += FIXED(pPed->speed * RSIN(dir));
		pPed->position.vz += FIXED(pPed->speed * RCOS(dir));
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
		int g_cdNumFrames;
		pPed->frame1++;

		if (pPed->type - 8U < 3)	// [A] TODO: figure out what type it is to have extended frames
			g_cdNumFrames = 31;
		else
			g_cdNumFrames = 16;

		if (pPed->frame1 >= g_cdNumFrames)
			pPed->frame1 = 0;
	}

	if ((pPed->pedType == TANNER_MODEL || (ActiveCheats.cheat12 && pPed->pedType == OTHER_MODEL)) && pPed->type < PED_ACTION_BACK)
	{
		int surfId;
		surfId = PedSurfaceType(&vec);

		// play footstep sounds
		if (surfId != SURF_GRASS && 
			surfId != SURF_WATER && 
			surfId != SURF_SAND && 
			surfId != SURF_DEEPWATER)
		{
			if (pPed->frame1 == 3)
				Start3DSoundVolPitch(-1, SOUND_BANK_TANNER, 0, pPed->position.vx, -pPed->position.vy, pPed->position.vz, -5000, 0x1000);

			if (pPed->frame1 == 11)
				Start3DSoundVolPitch(-1, SOUND_BANK_TANNER, 1, pPed->position.vx, -pPed->position.vy, pPed->position.vz, -5000, 0x1000);
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


// [D] [T]
void SetupDoNowt(LPPEDESTRIAN pPed)
{
	pPed->speed = 0;
	pPed->dir.vz = 0;
	pPed->type = PED_ACTION_BACK;

	SetupPedMotionData(pPed);

	pPed->flags |= 0x10;
}

// [D] [T]
void SetupWalker(LPPEDESTRIAN pPed)
{
	pPed->type = PED_ACTION_WALK;
	pPed->speed = 14;
	SetupPedMotionData(pPed);

	pPed->flags |= 0x10;
}

// [D] [T]
void SetupRunner(LPPEDESTRIAN pPed)
{
	pPed->type = PED_ACTION_RUN;
	pPed->frame1 = 0;
	pPed->speed = 40;
	SetupPedMotionData(pPed);

	pPed->flags |= 0x10;
}

// [D] [T]
void SetupBack(LPPEDESTRIAN pPed)
{
	pPed->type = PED_ACTION_WALK;
	pPed->frame1 = 0;
	pPed->speed = -10;
	SetupPedMotionData(pPed);

	pPed->flags |= 0x10;
}

CAR_DATA* pCivCarToGetIn = NULL;

// [D] [T]
void CivGetIn(LPPEDESTRIAN pPed)		// [A] UNUSED
{
	u_int padid;
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

// [D] [T]
void CopStand(LPPEDESTRIAN pPed)
{
	VECTOR v;
	v.vx = pPed->position.vx - player[0].pos[0];
	v.vz = pPed->position.vz - player[0].pos[2];

	pPed->frame1 = 0;
	pPed->dir.vy = 1024 - ratan2(v.vz, v.vx);
}

int iAllowWatch = 0;

// [D] [T]
void PedDoNothing(LPPEDESTRIAN pPed)
{
	pPed->speed = 0;

	if ((pPed->flags & 0x10) == 0)
	{
		SetupDoNowt(pPed);
		pPed->flags |= 0x10;
	}

	if (tannerPad & TANNER_PAD_GOFORWARD)
	{
		// run forward
		pPed->interest = 0;
		pPed->flags &= ~0x10;
		pPed->fpAgitatedState = fpPedPersonalityFunctions[2];

		SetupRunner(pPed);
	}
	else if (tannerPad & TANNER_PAD_GOBACK)
	{
		// walk back
		pPed->interest = 0;
		pPed->flags &= ~0x10;
		pPed->fpAgitatedState = fpPedPersonalityFunctions[1];

		SetupBack(pPed);
	}
	else if (tannerPad & TANNER_PAD_TURNRIGHT)
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
	else if (tannerPad & TANNER_PAD_TURNLEFT)
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

// [D] [T]
void PedUserRunner(LPPEDESTRIAN pPed)
{
	if ((pPed->flags & 0x10U) == 0)
	{
		SetupRunner(pPed);
	}

	if (tannerPad & TANNER_PAD_GOFORWARD)
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

	if (tannerPad & TANNER_PAD_TURNRIGHT)
	{
		if (pPed->dir.vz > -80)
			pPed->dir.vz -= 20;

		pPed->doing_turn -= 2;

		if (pPed->doing_turn < -tannerTurnMax)
			pPed->doing_turn = -tannerTurnMax;

		pPed->head_rot = 0;
		pPed->dir.vy = pPed->dir.vy + 64 - (pPed->doing_turn + tannerTurnMax) * tannerTurnStep;
	}
	else if (tannerPad & TANNER_PAD_TURNLEFT)
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

// [D] [T]
void PedUserWalker(LPPEDESTRIAN pPed)
{
	if ((pPed->flags & 0x10) == 0)
	{
		SetupWalker(pPed);
	}

	if (tannerPad & TANNER_PAD_GOBACK)
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

	if (tannerPad & TANNER_PAD_TURNRIGHT)
	{
		pPed->head_rot = 0;
		pPed->dir.vy += 20;
	}

	if (tannerPad & TANNER_PAD_TURNLEFT)
	{
		pPed->head_rot = 0;
		pPed->dir.vy -= 20;
	}

	AnimatePed(pPed);
}

int iFreezeTimer = 0;
int bFreezeAnimation = 0;
int allreadydone = 0;

// [D] [T]
void PedCarryOutAnimation(LPPEDESTRIAN pPed)
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

CAR_DATA* carToGetIn;
int bReverseYRotation = 0;

// [D] [T]
void PedGetOutCar(LPPEDESTRIAN pPed)
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


int lastCarCameraView = 0;

// [D] [T]
void SetupGetOutCar(LPPEDESTRIAN pPed, CAR_DATA* pCar, int side)
{
	bool entrySide;
	int sn, cs;
	u_int carDir;
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

	carDir = pCar->hd.direction + 2048;

	if (NoPlayerControl == 0)
	{
		player[playerId].cameraView = 5;

		player[playerId].cameraPos.vx = pCar->hd.where.t[0] - (FIXED(xOfs * RCOS(carDir)) - FIXED(RSIN(carDir) * 800));
		player[playerId].cameraPos.vy = -200 - pCar->hd.where.t[1];
		player[playerId].cameraPos.vz = pCar->hd.where.t[2] + (FIXED(xOfs * RSIN(carDir)) + FIXED(RCOS(carDir) * 800));
	}

	pPed->frame1 = 0;
	carToGetIn = pCar;
}


// [D] [T]
void SetupGetInCar(LPPEDESTRIAN pPed)
{
	int sn, cs;
	int carDir;
	int xOfs;
	int playerId;
	int entrySide;

	LONGVECTOR4 pos;

	pPed->flags &= ~4;
	pPed->speed = 0;
	pPed->frame1 = 0;

	playerId = pPed->padId;

	sn = rsin(carToGetIn->hd.direction);
	cs = rcos(carToGetIn->hd.direction);

	entrySide = cs * (carToGetIn->hd.where.t[0] - pPed->position.vx) - FIXED(sn * ONE) * (carToGetIn->hd.where.t[2] - pPed->position.vz) + 2048 < 0;

	if (entrySide)
		pPed->dir.vy = carToGetIn->hd.direction + 1024;
	else
		pPed->dir.vy = carToGetIn->hd.direction - 1024;

	if (pPed->dir.vy > carToGetIn->hd.direction)
		xOfs = -400;
	else
		xOfs = 400;

	carDir = carToGetIn->hd.direction + 2048;

	if (NoPlayerControl == 0 && gInGameCutsceneActive == 0)
	{
		player[playerId].cameraView = 5;
		player[playerId].cameraPos.vx = carToGetIn->hd.where.t[0] - (FIXED(xOfs * RCOS(carDir)) - FIXED(RSIN(carDir) * 800));
		player[playerId].cameraPos.vy = -200 - carToGetIn->hd.where.t[1];
		player[playerId].cameraPos.vz = carToGetIn->hd.where.t[2] + (FIXED(xOfs * RSIN(carDir)) + FIXED(RCOS(carDir) * 800));
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
			Start3DSoundVolPitch(-1, SOUND_BANK_TANNER, 5, pos[0], pos[1], pos[2], 0, 0x1000);

			carToGetIn->controlFlags |= CONTROL_FLAG_WAS_PARKED;
		}
	}
}

// [D] [T]
void PedGetInCar(LPPEDESTRIAN pPed)
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

		numTannerPeds--;
	}
}

// [D] [T]
void SetupPressButton(LPPEDESTRIAN pPed)
{
	pPed->type = PED_ACTION_PRESSBUTTON;
	SetupPedMotionData(pPed);

	pPed->dir.vz = 0;
	pPed->speed = 0;
	pPed->frame1 = 0;
	pPed->fpAgitatedState = PedPressButton;
}

// [D] [T]
void PedPressButton(LPPEDESTRIAN pPed)
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


// [D] [T]
void SetupTannerSitDown(LPPEDESTRIAN pPed)
{
	pPed->type = PED_ACTION_SIT;
	SetupPedMotionData(pPed);

	pPed->dir.vz = 0;
	pPed->speed = 0;
	pPed->frame1 = 0;
	pPed->fpAgitatedState = TannerSitDown;
}

// [D] [T]
void TannerCameraHandler(LPPEDESTRIAN pPed)
{
	int value;
	int padSteer;
	int padid;

	padid = pPed->padId;

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
				tannerLookAngle.vy = (value - 32) * -11;
			else
				tannerLookAngle.vy = (value - 32) * 11;
		}
		else
		{
			tannerLookAngle.vy = 0;
		}

		tannerLookAngle.vx = -Pads[padid].mapanalog[1] * 2;

		if (tannerLookAngle.vx < -60)
			tannerLookAngle.vx -= 128;
		else if (tannerLookAngle.vx < 60)
			tannerLookAngle.vx = 0;
	}
	else
	{
		tannerLookAngle.vx = 0;
		tannerLookAngle.vy = 0;
		tannerLookAngle.vz = 0;
	}

	// [A] old non-functioning code bloat removed
}



// [D] [T]
void TannerSitDown(LPPEDESTRIAN pPed)
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

			if (tannerPad & TANNER_PAD_ACTION)
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

// [D] [T]
void CivPedDoNothing(LPPEDESTRIAN pPed)
{
}

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

// [D] [T]
void PingInPedestrians(void)
{
	int bFound;
	LPPEDESTRIAN pPed;
	int rnd;
	int pingInDist;
	int i;
	int dx, dz;
	VECTOR randomLoc;
	VECTOR baseLoc;

	if (NO_MORE_PEDS() || pFreePeds == NULL || pFreePeds->pNext == NULL)
		return;

	baseLoc.vx = player[0].pos[0];
	baseLoc.vy = player[0].pos[1];
	baseLoc.vz = player[0].pos[2];

	if (gWeather == WEATHER_NONE && FindSeated() != NULL)
		return;

	for (i = 0; i < 50; i++)
	{
		pinginPedAngle += 81;

		pingInDist = Random2(0) % 128 + 1536;

		randomLoc.vy = baseLoc.vy;
		randomLoc.vx = baseLoc.vx + pingInDist * FIXEDH(RSIN(pinginPedAngle) * 8);
		randomLoc.vz = baseLoc.vz + pingInDist * FIXEDH(RCOS(pinginPedAngle) * 8);

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

				while (dx * dx + dz * dz >= PED_PING_RADIUS)
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

// [D] [T]
void TannerCollision(LPPEDESTRIAN pPed)
{
	CAR_DATA* pcdTanner;

	if (pPed->type == PED_ACTION_SIT)
		return;

	pcdTanner = &car_data[TANNER_COLLIDER_CARID];

	ClearMem((char*)pcdTanner, sizeof(CAR_DATA));

	pcdTanner->id = TANNER_COLLIDER_CARID;
	pcdTanner->controlType = 6;

	pcdTanner->hd.direction = pPed->dir.vy - 2048 & 4095;

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

// [D] [T]
int FindPointOfCollision(CAR_DATA* pCar, LPPEDESTRIAN pPed)
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

	if (!bcollided2d(cd))
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


	dx = FIXED((collisionResult.hit.vx - cd[1].x.vx) * RCOS(cd[1].theta)) -
		 FIXED((collisionResult.hit.vz - cd[1].x.vz) * RSIN(cd[1].theta));

	dz = FIXED((collisionResult.hit.vx - cd[1].x.vx) * RSIN(cd[1].theta)) +
		 FIXED((collisionResult.hit.vz - cd[1].x.vz) * RCOS(cd[1].theta));

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

// [D] [T]
int TannerCarCollisionCheck(VECTOR* pPos, int dir, int bQuick)
{
	CAR_DATA* cp1;
	LONGVECTOR4 pointVel;
	LONGVECTOR4 reaction;
	LONGVECTOR4 lever;
	int strikeVel;
	SVECTOR boxDisp;
	CAR_COSMETICS* car_cos;
	CAR_DATA* pcdTanner;

	CRET2D collisionResult; // offset 0x30
	CDATA2D cd[2];

	pcdTanner = &car_data[TANNER_COLLIDER_CARID];

	cd[0].length[0] = 60;
	cd[0].length[1] = 60;

	cd[0].x.vx = pPos->vx;
	cd[0].x.vz = pPos->vz;
	cd[0].theta = dir;

	cp1 = &car_data[MAX_CARS - 1];

	do {
		// [A] skip sooner
		if (cp1->controlType == CONTROL_TYPE_NONE)
		{
			cp1--;
			continue;
		}

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

		int dist = ABS(cp1->hd.where.t[1] + pPos->vy);

		if (dist < 500 && bcollided2d(cd))
		{
			if (bQuick != 0)
				return 1;

			if (FIXEDH(cp1->hd.wheel_speed) > 50)
			{
				// [A] testing revealed the dist was usually 99 or 100 here
				if (!gExtraConfig.Flags.FixTannerPhasingThruCars || dist > 100)
					return 1;
			}

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

			strikeVel = (pointVel[0] / 256) * (-collisionResult.surfNormal.vx / 16) + 
				        (pointVel[2] / 256) * (-collisionResult.surfNormal.vz / 16);

			if (strikeVel < 0)
			{
				int lever_dot_n; // $a0
				int displacementsquared; // $a1
				int denom; // $a0
				int twistRateY;

				twistRateY = car_cos->twistRateY;
				
				lever_dot_n = FIXEDH(lever[0] * -collisionResult.surfNormal.vx + lever[2] * -collisionResult.surfNormal.vz);
				displacementsquared = FIXEDH(((lever[0] * lever[0] + lever[2] * lever[2]) - lever_dot_n * lever_dot_n) * twistRateY) + ONE;

				if (-strikeVel < 520193)
					denom = (strikeVel * -ONE) / displacementsquared;
				else
					denom = -strikeVel / displacementsquared * ONE;

				denom /= 64;
				
				reaction[0] = denom * (-collisionResult.surfNormal.vx / 64);
				reaction[2] = denom * (-collisionResult.surfNormal.vz / 64);
				
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

// [D] [T]
int PingOutPed(LPPEDESTRIAN pPed)
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

// [D] [T]
void SetupCivJump(LPPEDESTRIAN pPed, CAR_DATA* cp)
{
	int dz;
	short scale;
	int dx;
	short angle;
	LONGVECTOR4 dir;

	if (pPed->type != PED_ACTION_JUMP)
	{
		pPed->frame1 = 0;
		pPed->speed = 30;

		// if player horns make scare box bigger and give player felony
		if (cp == &car_data[player[0].playerCarId])
		{
			if (player[0].horn.on != 0)
				scale = 2048;
			else
				scale = 4096;

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
			int d;
			
			dx = player[0].pPed->position.vx - pPed->position.vx;
			dz = player[0].pPed->position.vz - pPed->position.vz;

			d = player[0].pPed->dir.vy - 2048;

			dir[0] = player[0].pPed->speed * RCOS(d);
			dir[2] = player[0].pPed->speed * RSIN(d);
			
			// [A] fuck....
			if (FIXED(-dir[0]) * dx + FIXED(dir[2]) * dz + 2048 < 0)
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

// [D] [T]
void CivPedJump(LPPEDESTRIAN pPed)
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

// [D] [T]
void SetupCivPedWalk(LPPEDESTRIAN pPed)
{
	pPed->flags |= 0x10;

	if (pPed->type == PED_ACTION_CIVRUN)
		pPed->speed = 30;
	else
		pPed->speed = 10;

	SetupPedMotionData(pPed);

	pPed->frame1 = 0;
}

// [D] [T]
void CivPedWalk(LPPEDESTRIAN pPed)
{
	int dir;
	int turn;

	if ((pPed->flags & 0x10) == 0)
		SetupCivPedWalk(pPed);

	if (pPed->finished_turn == 9)
		dir = pPed->dir.vy + 2048;
	else
		dir = pPed->dir.vy + 1850;

	if ((pPed->flags & 2U) != 0)
	{
		pPed->speed = 0;
		pPed->dir.vy += pPed->head_rot;
	}
	else
	{
		if (IsPavement(
			pPed->position.vx + (RSIN(dir) >> 5),
			pPed->position.vy,
			pPed->position.vz + (RCOS(dir) >> 5), pPed) == 0)
		{
			if (pPed->finished_turn == 9)
			{
				dir = pPed->dir.vy + 2560;

				if (IsPavement(
					pPed->position.vx + FIXED(RSIN(dir) * 128),
					pPed->position.vy,
					pPed->position.vz + FIXED(RCOS(dir) * 128), NULL) == 0)

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
				dir = pPed->dir.vy + 2048;

				pPed->velocity.vx = FIXED(pPed->speed * RSIN(dir));
				pPed->velocity.vz = FIXED(pPed->speed * RCOS(dir));
			}
			pPed->finished_turn = 0;
		}
		else
		{
			pPed->doing_turn = 0;

			if (pPed->finished_turn++ > 8)
			{
				pPed->dir.vy = pPed->dir.vy + 512 & 0xfc00;

				dir = pPed->dir.vy + 2048 & 0xfff;

				pPed->velocity.vx = FIXED(pPed->speed * RSIN(dir));
				pPed->velocity.vz = FIXED(pPed->speed * RCOS(dir));

				pPed->finished_turn = 9;
			}
		}
	}

	AnimatePed(pPed);
}

// [D] [T]
void CivPedSit(LPPEDESTRIAN pPed)
{
	pPed->frame1 = 0;
}

// [D] [T]
void HandlePedestrians(void)
{
	if (gInGameCutsceneActive != 0 || NumPlayers != 1)
		return;

	BuildCarCollisionBox();
	ControlPedestrians();
	PingInPedestrians();
}

// [D] [T]
void PedestrianActionInit_WalkToTarget(LPPEDESTRIAN pPed)
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

// [D] [T]
void CorrectPathPosition(LPPEDESTRIAN pedestrian, VECTOR* position)
{
}


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

	rx = wx & ~1023;
	rz = wz & ~1023;

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

// [D] [T]
int IsPavement(int x, int y, int z, LPPEDESTRIAN pPed)
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

// [D] [T]
void SetPedestrianTurn(LPPEDESTRIAN pedestrian, int turn)
{
	int speed;
	int dir;

	dir = pedestrian->dir.vy + turn & 0xfff;

	pedestrian->dir.vy = dir;

	dir += 2048;

	pedestrian->position.vz -= pedestrian->velocity.vz;
	pedestrian->position.vx -= pedestrian->velocity.vx;

	speed = pedestrian->speed;
	
	pedestrian->velocity.vx = FIXEDH(speed * RSIN(dir));
	pedestrian->velocity.vz = FIXEDH(speed * RCOS(dir));
}

// [D] [T]
SEATEDPTR FindSeated(void)
{
	int dz;
	int dx;
	int count1;
	SEATEDPTR seatedptr;

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

// [D] [T]
SEATEDPTR FindTannerASeat(LPPEDESTRIAN pPed)
{
	int dx, dz;
	int distSqr;
	int bestSqr;
	SEATEDPTR seatedptr;
	SEATEDPTR theOne;
	
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

#ifndef PSX
int PedsAvailable()
{
	int peds_available = max_pedestrians - num_pedestrians;

	if (peds_available <= MAX_TANNER_PEDS)
		return 0;

	peds_available -= MAX_TANNER_PEDS;

	return peds_available;
}
#endif

// [D] [T]
void add_seated(SEATEDPTR seatedptr, int seat_index)
{
	LPPEDESTRIAN pedptr;
	int rnd;

#ifndef PSX
	if (PedsAvailable() > 0)
#else
	if (num_pedestrians < MAX_SEATED_PEDS)
#endif
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

CAR_COLLISION_BOX collision_box[8];
CAR_DATA* collision_car_ptr[8];

// [D] [T]
void set_coll_box(int index, CAR_DATA* cp, int offset)
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
	EXOBJECT* expl;
	CAR_DATA* cp;

	if (player[0].playerCarId != -1) // [A] ASan bug fix
	{
		set_coll_box(0, &car_data[player[0].playerCarId], 8);
		set_coll_box(1, &car_data[player[0].playerCarId], 9);
	}

	cp = &car_data[(CameraCnt & 3)];

	collision_boxes_set = 2;

	while (cp < &car_data[MAX_CARS])
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
		dir = player[0].pPed->dir.vy - 2048;

		vx = FIXED(player[0].pPed->speed * RSIN(dir) * 4);
		vz = FIXED(player[0].pPed->speed * RCOS(dir) * 4);
		
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

// [D] [T]
CAR_DATA* CheckForCar(LPPEDESTRIAN pedestrian)
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

// [D] [T]
int CheckForPlayerCar(LPPEDESTRIAN pedestrian, CAR_COLLISION_BOX* collision_box)
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

int basic_car_interest;

// [D] [T]
void CalculatePedestrianInterest(LPPEDESTRIAN pPed)
{
	CAR_DATA* pCar;
	int carId;
	int interest;
	VECTOR v1;
	VECTOR v2;

	carId = player[0].playerCarId;

	if (carId == -1) // [A] ASan bug fix
	{
		pPed->head_rot = 0;
		return;
	}

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

// [D] [T]
void ProcessChairLump(char* lump_file, int lump_size)
{
	seated_pedestrian = (SEATEDPTR)lump_file;
}

// [D] [T]
// Havana easter egg.
void IHaveThePower(void)
{
	CAR_DATA* cp;
	LONGVECTOR4 force = { 0x9000, 0, 0, 0 };
	LONGVECTOR4 point = { 0, 0, 90, 0 };

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

	if (tannerPad & TANNER_PAD_POWER)
	{
		if (bPower == 0)
		{
			oldWeather = gWeather;
			bPower = 1;
			gWeather = WEATHER_RAIN;
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

// [D] [T]
void ProcessTannerPad(LPPEDESTRIAN pPed, u_int pad, char PadSteer, char use_analogue)
{
	int mapheight[2];

	sdPlane* SurfacePtr;
	int direction, diff;
	VECTOR vec, normal, out, tVec;
	sdPlane* plane;
	PLAYER* lcp;

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
			tannerPad |= (PadSteer < 0) ? TANNER_PAD_TURNLEFT : TANNER_PAD_TURNRIGHT;
	}

	IHaveThePower();	// process Havana easter egg near the entrance cemetery

	vec.vx = pPed->position.vx;
	vec.vy = -pPed->position.vy;
	vec.vz = pPed->position.vz;

	direction = pPed->dir.vy - 2048;

	tVec.vx = vec.vx + (RSIN(direction) * 5 >> 9);
	tVec.vy = vec.vy;
	tVec.vz = vec.vz + (RCOS(direction) * 5 >> 9);

	bStopTanner = 0;

	mapheight[0] = -130 - MapHeight(&vec);
	mapheight[1] = -130 - MapHeight(&tVec);

	diff = ABS(mapheight[1] - mapheight[0]);

	// check slope
	if (diff <= 1010)
	{
		SurfacePtr = sdGetCell(&tVec);

		if (SurfacePtr != NULL)
		{
			diff = ABS(DIFF_ANGLES((SurfacePtr->b >> 2), 0)); //ABS(((SurfacePtr->b >> 2) - 2048 & 0xfff) - 2048);

			if (diff <= 1100)
			{
				switch (SurfacePtr->surface)
				{
				case -32:
					break;
					//case 6:	// water. We allow to walk on water in Rio a little bit. Then he drowns
				case 9:		// water with fade out
				default:
					diff = -1;
					break;
				}
			}
		}
	}

	// can't walk in water
	if (diff != -1)
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
	if (tannerPad & TANNER_PAD_ACTION)
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

		if (plane && plane->surface != -1 && plane->surface < 32 && (plane->surface & 16))
		{
			pPed->position.vx += (normal.vx >> 6);
			pPed->position.vz += (normal.vz >> 6);
			pPed->position.vy = mapheight[0];
		}
	}
}


// [D] [T]
int ActivatePlayerPedestrian(CAR_DATA* pCar, char* padId, int direction, LONGVECTOR4* position, PED_MODEL_TYPES playerType)
{
	int wbody;
	int side;
	int dir;
	LPPEDESTRIAN pedptr;
	int playerId;
	VECTOR* pos;
	VECTOR v;
	int d, y;
	PLAYER* lp;
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

	dir = d - 2048;

	v.vy = y;
	v.vx = x - FIXED(wbody * RCOS(d));
	v.vz = z + FIXED(wbody * RSIN(d));

	side = 0;

	if (pCar != NULL)
	{
		if (QuickBuildingCollisionCheck(&v, dir, 10, 10, 10) || 
			TannerCarCollisionCheck(&v, d, 1))
		{
			side = 1;

			v.vy = y;

			v.vx = x - FIXED(-wbody * RCOS(d));
			v.vz = z + FIXED(-wbody * RSIN(d));

			if (QuickBuildingCollisionCheck(&v, dir, 10, 10, 10))
				return 0;
			
			if (TannerCarCollisionCheck(&v, d, 1))
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
		pedptr->position.vy = pCar->hd.where.t[1];

	pedptr->position.vy = -130 - MapHeight(pos);
	pedptr->dir.vz = 0;
	pedptr->dir.vx = 0;
	pedptr->dir.vy = dir;
	pedptr->head_rot = 0;
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
				int rnd1 = Random2(0);
				int rnd2 = Random2(0);
				
				pedptr->pallet = rnd1 - rnd1 / 3 * 3 + (rnd2 - rnd2 / 3 * 3) * 16;
			}
		}
	}
	else
	{
		MakeTheCarShutUp(playerId);
		Start3DSoundVolPitch(-1, SOUND_BANK_TANNER, 2, lp->pos[0], lp->pos[1], lp->pos[2], 0, 0x1000);
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

// [D] [T]
void DeActivatePlayerPedestrian(LPPEDESTRIAN pPed)
{
	CAR_DATA* cp;
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

		Start3DSoundVolPitch(-1, SOUND_BANK_TANNER, 2, player[0].pos[0], player[0].pos[1], player[0].pos[2], 0, 0x1000);
		SetupPedestrian(pPed);
		SetupGetInCar(pPed);
	}
}
