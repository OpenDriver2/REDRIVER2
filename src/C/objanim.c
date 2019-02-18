#include "../decomp_defs.h"

CYCLE_OBJECT Lev0[2] =
{
  { "REDRVR", 0, 0, 6, 10, 2, 11, 15, 2 },
  { "NAVPIR34", 0, 0, 0, 6, 0, 7, 13, 0 }
};

CYCLE_OBJECT Lev1[] = {
	{ "DOOR11", 0, 0, 1, 7, 2, 8, 14, 3 } ,
};

CYCLE_OBJECT Lev2[12] =
{
  { "DTSYN01", 0, 0, 0, 3, 0, 4, 14, 0 },
  { "DTSYN02", 0, 0, 0, 15, 0, 65535, 65535, 0 },
  { "F-MTSYN2", 0, 0, 0, 3, 0, 10, 14, 0 },
  { "DTSYN03", 0, 0, 0, 3, 0, 65535, 65535, 0 },
  { "SYN-CAS1", 0, 0, 0, 3, 0, 4, 14, 0 },
  { "SYNSLOT", 0, 0, 0, 3, 0, 4, 7, 0 },
  { "ENT1B", 0, 0, 0, 15, 0, 65535, 65535, 0 },
  { "FLAMINGO", 0, 0, 0, 3, 0, 9, 12, 0 },
  { "CYCLE-01", 0, 0, 0, 5, 1, 6, 11, 1 },
  { "CYCLE-02", 0, 0, 0, 3, 3, 65535, 65535, 0 },
  { "CYCLE-03", 0, 0, 0, 6, 7, 7, 13, 7 },
  { "CYCLE-04", 0, 0, 0, 6, 15, 7, 13, 15 }
};

CYCLE_OBJECT Lev3[] = {
	{ "FWING11", 0, 0, 1, 7, 2, 8, 14, 3 } 
};


CYCLE_OBJECT* Lev_CycleObjPtrs[] = {
	Lev0,
	Lev1,
	Lev2,
	Lev3
};

int Num_LevCycleObjs[] = { 2, 0, 12, 0 };

ANIMATED_OBJECT Lev0AnimObjects[9] =
{
  { 0, 0, "TLIGHT01", '\0' },
  { 1, 0, "TLIGHT02", '\0' },
  { 2, 0, "SLIGHT01", '\x01' },
  { 3, 0, "LOW_SLIGHT01", '\x01' },
  { 4, 0, "DLIGHT01", '\x01' },
  { 5, 0, "STRUT", '\0' },
  { 6, 0, "NPLIGHT", '\0' },
  { 7, 0, "TLIGHT01_LOW", '\0' },
  { 8, 0, "TLIGHT02_LOW", '\0' }
};

ANIMATED_OBJECT Lev1AnimObjects[5] =
{
  { 0, 0, "TLIGHT1", '\0' },
  { 1, 0, "TLIGHT2", '\0' },
  { 2, 0, "SLIGHT1", '\x01' },
  { 3, 0, "SLIGHT2", '\x01' },
  { 4, 0, "DLIGHT1", '\x01' }
};

ANIMATED_OBJECT Lev2AnimObjects[5] =
{
  { 0, 0, "TLIGHT01", '\0' },
  { 1, 0, "TLIGHT02", '\0' },
  { 2, 0, "SLIGHT01", '\x01' },
  { 3, 0, "DLIGHT01", '\x01' },
  { 4, 0, "SLIGHT02", '\x01' }
};

ANIMATED_OBJECT Lev3AnimObjects[4] =
{
  { 0, 0, "TLIGHT01", '\0' },
  { 1, 0, "TLIGHT02", '\0' },
  { 2, 0, "SLIGHT01", '\x01' },
  { 3, 0, "MLIGHT01", '\x01' }
};

ANIMATED_OBJECT* Level_AnimatingObjectPtrs[] = { Lev0AnimObjects, Lev1AnimObjects, Lev2AnimObjects, Lev3AnimObjects };

VECTOR gMissionDoorPosition = { 108000, 0, 4294575046, 0 };

SMASHABLE_OBJECT smashable[] =
{
  { 0, "CONE_TASTIC", 5, 0, 800 },
  { 0, "BOX_TASTIC", 4, 4294961296, 4096 },
  { 0, "BOX2_TASTIC", 4, 4294961296, 4096 },
  { 0, "BOX3_TASTIC", 4, 4294961296, 4096 },
  { 0, "CONE1_TASTIC", 5, 0, 800 },
  { 0, "CONE2_TASTIC", 5, 0, 800 },
  { 0, "BIN_TASTIC", 7, 4294960796, 3200 },
  { 0, "BARRIER_TASTIC", 7, 4294960796, 3200 },
  { 0, "BARREL_TASTIC", 6, 4294963996, 2400 },
  { 0, "BARREL1_TASTIC", 6, 4294963996, 2400 },
  { 0, "BARREL2_TASTIC", 6, 4294963996, 2400 },
  { 0, "TABLE_TASTIC", 7, 4294960796, 3200 },
  { 0, "BENCH_TASTIC", 7, 4294960796, 3200 },
  { 0, "CHAIR_TASTIC", 7, 4294960796, 3200 },
  { 0, "CHAIR1_TASTIC", 7, 4294960796, 3200 },
  { 0, "CHAIR2_TASTIC", 7, 4294960796, 3200 },
  { 0, "UMBRELLA_TASTIC", 7, 4294960796, 3200 },
  { 0, "UMBRELLA1_TASTIC", 7, 4294960796, 3200 },
  { 0, "PHONE_TASTIC", 6, 4294963996, 3600 },
  { 0, "PHONE1_TASTIC", 6, 4294963996, 3600 },
  { 0, "SIGN00_TASTIC", 7, 4294960796, 3200 },
  { 0, "NEWS_TASTIC", 7, 4294960796, 3200 },
  { 0, "PARKING_TASTIC", 6, 4294959796, 4096 },
  { 0, "DRINKS_TASTIC", 6, 4294963996, 3600 },
  { 0, "FENCE_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE00_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE01_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE02_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE03_TASTIC", 7, 4294960796, 3200 },
  { 0, "FENCE04_TASTIC", 7, 4294960796, 3200 },
  { 0, "CONE_TASTIC1", 5, 0, 800 },
  { 0, "CONE_TASTIC2", 5, 0, 800 },
  { 0, "CONE_TASTIC3", 5, 0, 800 },
  { 0, "CONE_TASTIC4", 5, 0, 800 },
  { 0, "TRAININGCONES1", 5, 0, 800 },
  { 0, "TRAININGCONES2", 5, 0, 800 },
  { 0, "TRAININGCONES3", 5, 0, 800 },
  { 0, 0, 0, 0, 0 }
};


int Level_NumAnimatedObjects[] = { 9, 5, 5, 4, 0, 6, 0, 0 };

char* texture_pages = 0;	// some big empty array
char* texture_cluts = 0;	// some big empty array



/*
 * Offset 0x139E8
 * D:\driver2\game\C\OBJANIM.C (line 362)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ ColourCycle()
{ // line 3, address 0x139e8
	int i; // $s5
	struct CYCLE_OBJECT *cyc; // $s2
	struct RECT vram; // stack address -56
	unsigned short *bufaddr; // $s0
	unsigned short length; // $v0
	unsigned short temp; // $s1
	{ // line 26, address 0x13ab4
		int tnum; // $a1
		{ // line 39, address 0x13b0c
		} // line 48, address 0x13b54
		{ // line 53, address 0x13b80
		} // line 62, address 0x13bc8
	} // line 81, address 0x13c88
} // line 88, address 0x13ce4
/*
 * Offset 0x13D14
 * D:\driver2\game\C\OBJANIM.C (line 481)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ InitAnimatingObjects()
{ // line 2, address 0x13d14
	struct ANIMATED_OBJECT *aop; // $s1
	int loop; // $s0
	int count1; // $a0
	int count; // $a2
	struct MODEL *modelPtr; // $a0
} // line 47, address 0x13e60
/*
 * Offset 0x13E60
 * D:\driver2\game\C\OBJANIM.C (line 613)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ animate_object(struct CELL_OBJECT *cop /*$s2*/, int type /*$a1*/)
{ // line 1, address 0x13e60
	short yang; // $s1
	char phase; // $a0
} // line 283, address 0x1470c
/*
 * Offset 0x1470C
 * D:\driver2\game\C\OBJANIM.C (line 931)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ animate_garage_door()
{ // line 2, address 0x1470c
	int dx; // $a0
	int dz; // $v1
	int dist; // $a0
} // line 34, address 0x14888
/*
 * Offset 0x14890
 * D:\driver2\game\C\OBJANIM.C (line 536)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ InitSpooledAnimObj(int model_number /*$a0*/)
{ // line 1, address 0x14890
	struct ANIMATED_OBJECT *aop; // $a1
	int i; // $a2
} // line 15, address 0x14900
/*
 * Offset 0x14908
 * D:\driver2\game\C\OBJANIM.C (line 578)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ DrawAnimatingObject(struct MODEL *model /*$a0*/, struct CELL_OBJECT *cop /*$s3*/, struct VECTOR *pos /*$a2*/)
{ // line 1, address 0x14908
	struct ANIMATED_OBJECT *aop; // $s1
	int loop; // $s2
	int type; // $s0
} // line 27, address 0x149b8
/*
 * Offset 0x149B8
 * D:\driver2\game\C\OBJANIM.C (line 460)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void /*$ra*/ FindSmashableObjects()
{ // line 2, address 0x149b8
	struct SMASHABLE_OBJECT *sip; // $s0
} // line 8, address 0x14a10
/*
 * Offset 0x14A10
 * D:\driver2\game\C\OBJANIM.C (line 565)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ int_garage_door()
{
}
/*
 * Offset 0x14A1C
 * D:\driver2\game\C\OBJANIM.C (line 260)
 * Stack frame base $sp, length 40
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ InitCyclingPals()
{ // line 2, address 0x14a1c
	int i; // $s0
	struct CYCLE_OBJECT *cyc; // $s1
	struct RECT vram; // stack address -24
} // line 18, address 0x14ac0