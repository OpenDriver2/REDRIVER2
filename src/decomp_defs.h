#include <stddef.h>

// 16 enums
enum PAUSEMODE {
	PAUSEMODE_PAUSE = 0,
	PAUSEMODE_PAUSEP1 = 1,
	PAUSEMODE_PAUSEP2 = 2,
	PAUSEMODE_GAMEOVER = 3,
	PAUSEMODE_COMPLETE = 4,
	PAUSEMODE_PADERROR = 5,
};

enum PED_ACTION_TYPE {
	PED_ACTION_WALK = 0,
	PED_ACTION_RUN = 1,
	PED_ACTION_BACK = 2,
	PED_ACTION_GETINCAR = 3,
	PED_ACTION_GETOUTCAR = 4,
	PED_ACTION_TIME = 5,
	PED_ACTION_PRESSBUTTON = 6,
	PED_ACTION_SIT = 7,
	PED_ACTION_CIVWALK = 8,
	PED_ACTION_CIVRUN = 9,
	PED_ACTION_JUMP = 10,
	PED_ACTION_CIVSIT = 11,
	PED_ACTION_COPSTAND = 12,
	PED_ACTION_COPCROUCH = 13,
	PED_ACTION_TALK = 14,
	PED_ACTION_STOPPING = 15,
};

enum PED_MODEL_TYPES {
	TANNER_MODEL = 0,
	OTHER_MODEL = 1,
	OTHER_SPRITE = 2,
	CIVILIAN = 3,
};

enum ExplosionType {
	BIG_BANG = 0,
	LITTLE_BANG = 1,
	HEY_MOMMA = 666,
	BANG_USED = 999,
};

enum AIZon {
	zoneFrnt = 0,
	zoneBack = 1,
	zoneLeft = 2,
	zoneRght = 3,
};

enum SpecialCamera {
	SPECIAL_CAMERA_SET = 0,
	SPECIAL_CAMERA_SET2 = 1,
	SPECIAL_CAMERA_RESET = 2,
	SPECIAL_CAMERA_WAIT = 3,
};

enum VisType {
	VIS_INIT = 0,
	VIS_SORT = 1,
	VIS_ADD = 2,
	VIS_NEXT = 3,
};

enum Station {
	EVENT_NO_STATION = 0,
	EVENT_APPROACHING = 1,
	EVENT_LEAVING = 2,
};

enum GAMEMODE {
	GAMEMODE_NORMAL = 0,
	GAMEMODE_QUIT = 1,
	GAMEMODE_RESTART = 2,
	GAMEMODE_REPLAY = 3,
	GAMEMODE_DIRECTOR = 4,
	GAMEMODE_NEXTMISSION = 5,
	GAMEMODE_DEMO = 6,
};

enum GAMETYPE {
	GAME_MISSION = 0,
	GAME_TAKEADRIVE = 1,
	GAME_IDLEDEMO = 2,
	GAME_PURSUIT = 3,
	GAME_GETAWAY = 4,
	GAME_GATERACE = 5,
	GAME_CHECKPOINT = 6,
	GAME_TRAILBLAZER = 7,
	GAME_SURVIVAL = 8,
	GAME_INVALIDGAME1 = 9,
	GAME_REPLAYMISSION = 10,
	GAME_COPSANDROBBERS = 11,
	GAME_CAPTURETHEFLAG = 12,
	GAME_SECRET = 13,
	GAME_CONTINUEMISSION = 14,
	GAME_LOADEDREPLAY = 15,
};

enum EXIT_VALUE {
	MENU_QUIT_NONE = 0,
	MENU_QUIT_CONTINUE = 1,
	MENU_QUIT_QUIT = 2,
	MENU_QUIT_RESTART = 3,
	MENU_QUIT_DIRECTOR = 4,
	MENU_QUIT_QUICKREPLAY = 5,
	MENU_QUIT_BACKMENU = 6,
	MENU_QUIT_NEXTMISSION = 7,
};

enum FAIL_REASON {
	FAILED_OUTOFTIME = 0,
	FAILED_CnR_LOSTHIM = 1,
	FAILED_MESSAGESET = 2,
};

enum LIMBS {
	ROOT = 0,
	LOWERBACK = 1,
	JOINT_1 = 2,
	NECK = 3,
	HEAD = 4,
	LSHOULDER = 5,
	LELBOW = 6,
	LHAND = 7,
	LFINGERS = 8,
	RSHOULDER = 9,
	RELBOW = 10,
	RHAND = 11,
	RFINGERS = 12,
	HIPS = 13,
	LHIP = 14,
	LKNEE = 15,
	LFOOT = 16,
	LTOE = 17,
	RHIP = 18,
	RKNEE = 19,
	RFOOT = 20,
	RTOE = 21,
	JOINT = 22,
};

enum TEXTURE_PALS {
	NO_PAL = 0,
	JEANS_PAL = 1,
	ARM_PAL = 2,
	CHEST_PAL = 3,
};

enum CDTYPE {
	CDTYPE_NODISC = 0,
	CDTYPE_SHELLOPEN = 1,
	CDTYPE_DISCERROR = 2,
	CDTYPE_WRONGDISC = 3,
	CDTYPE_CORRECTDISC = 4,
};

enum CITYTYPE {
	CITYTYPE_DAY = 0,
	CITYTYPE_NIGHT = 1,
	CITYTYPE_MULTI_DAY = 2,
	CITYTYPE_MULTI_NIGHT = 3,
};

struct bodyst {
	long fposition[3]; // length=12, address=0
	long orientation[4]; // length=16, address=12
	long linearVelocity[3]; // length=12, address=28
	long angularVelocity[3]; // length=12, address=40
};

// 22 unions
union RigidBodyState {
	long v[13]; // length=52, address=0
	struct bodyst n; // length=52, address=0
};

// 300 structs
struct TCB {
	long status; // length=0, address=0
	long mode; // length=0, address=4
	unsigned long reg[40]; // length=160, address=8
	long system[6]; // length=24, address=168
};


struct EXEC {
	unsigned long pc0; // length=0, address=0
	unsigned long gp0; // length=0, address=4
	unsigned long t_addr; // length=0, address=8
	unsigned long t_size; // length=0, address=12
	unsigned long d_addr; // length=0, address=16
	unsigned long d_size; // length=0, address=20
	unsigned long b_addr; // length=0, address=24
	unsigned long b_size; // length=0, address=28
	unsigned long s_addr; // length=0, address=32
	unsigned long s_size; // length=0, address=36
	unsigned long sp; // length=0, address=40
	unsigned long fp; // length=0, address=44
	unsigned long gp; // length=0, address=48
	unsigned long ret; // length=0, address=52
	unsigned long base; // length=0, address=56
};

struct DIRENTRY {
	char name[20]; // length=20, address=0
	long attr; // length=0, address=20
	long length; // length=0, address=24
	struct DIRENTRY *next; // length=40, address=28
	long head; // length=0, address=32
	char system[4]; // length=4, address=36
};

struct MATRIX {
	short m[3][3]; // length=18, address=0
	long t[3]; // length=12, address=20
};

struct VECTOR2 {
	int vx; // length=0, address=0
	int vz; // length=0, address=4
};

struct VECTOR {
	long vx; // length=0, address=0
	long vy; // length=0, address=4
	long vz; // length=0, address=8
	long pad; // length=0, address=12
};

struct SVECTOR {
	short vx; // length=0, address=0
	short vy; // length=0, address=2
	short vz; // length=0, address=4
	short pad; // length=0, address=6
};

struct CVECTOR {
	unsigned char r; // length=0, address=0
	unsigned char g; // length=0, address=1
	unsigned char b; // length=0, address=2
	unsigned char cd; // length=0, address=3
};

struct DVECTOR {
	short vx; // length=0, address=0
	short vy; // length=0, address=2
};

struct RVECTOR {
	struct SVECTOR v; // length=8, address=0
	unsigned char uv[2]; // length=2, address=8
	unsigned short pad; // length=0, address=10
	struct CVECTOR c; // length=4, address=12
	struct DVECTOR sxy; // length=4, address=16
	unsigned long sz; // length=0, address=20
};

struct CRVECTOR3 {
	struct RVECTOR r01; // length=24, address=0
	struct RVECTOR r12; // length=24, address=24
	struct RVECTOR r20; // length=24, address=48
	struct RVECTOR *r0; // length=24, address=72
	struct RVECTOR *r1; // length=24, address=76
	struct RVECTOR *r2; // length=24, address=80
	unsigned long *rtn; // length=0, address=84
};

struct CRVECTOR4 {
	struct RVECTOR r01; // length=24, address=0
	struct RVECTOR r02; // length=24, address=24
	struct RVECTOR r31; // length=24, address=48
	struct RVECTOR r32; // length=24, address=72
	struct RVECTOR rc; // length=24, address=96
	struct RVECTOR *r0; // length=24, address=120
	struct RVECTOR *r1; // length=24, address=124
	struct RVECTOR *r2; // length=24, address=128
	struct RVECTOR *r3; // length=24, address=132
	unsigned long *rtn; // length=0, address=136
};

struct RECT {
	short x; // length=0, address=0
	short y; // length=0, address=2
	short w; // length=0, address=4
	short h; // length=0, address=6
};

struct DR_ENV {
	unsigned long tag; // length=0, address=0
	unsigned long code[15]; // length=60, address=4
};

struct SndVolume2 {
	short left; // length=0, address=0
	short right; // length=0, address=2
};

struct CdlLOC {
	unsigned char minute; // length=0, address=0
	unsigned char second; // length=0, address=1
	unsigned char sector; // length=0, address=2
	unsigned char track; // length=0, address=3
};

struct VECTOR_NOPAD {
	long vx; // length=0, address=0
	long vy; // length=0, address=4
	long vz; // length=0, address=8
};

struct SVECTOR_NOPAD {
	short vx; // length=0, address=0
	short vy; // length=0, address=2
	short vz; // length=0, address=4
};

struct BOX {
	float xmin; // length=0, address=0
	float ymin; // length=0, address=4
	float zmin; // length=0, address=8
	float xmax; // length=0, address=12
	float ymax; // length=0, address=16
	float zmax; // length=0, address=20
};

struct BSPHERE {
	struct VECTOR bounding_sphere_mid; // length=16, address=0
	float bounding_sphere; // length=0, address=16
};

struct RGB {
	unsigned char r; // length=0, address=0
	unsigned char g; // length=0, address=1
	unsigned char b; // length=0, address=2
	unsigned char pad; // length=0, address=3
};

struct UV_INFO {
	unsigned char u; // length=0, address=0
	unsigned char v; // length=0, address=1
};

struct XYPAIR {
	int x; // length=0, address=0
	int y; // length=0, address=4
};

struct SXYPAIR {
	short x; // length=0, address=0
	short y; // length=0, address=2
};

struct GAP_INFO {
	struct DVECTOR address; // length=4, address=0
	char clear; // length=0, address=4
};

struct PSXBUTTON {
	short x; // length=0, address=0
	short y; // length=0, address=2
	short w; // length=0, address=4
	short h; // length=0, address=6
	unsigned char l; // length=0, address=8
	unsigned char r; // length=0, address=9
	unsigned char u; // length=0, address=10
	unsigned char d; // length=0, address=11
	int userDrawFunctionNum; // length=0, address=12
	short s_x; // length=0, address=16
	short s_y; // length=0, address=18
	int action; // length=0, address=20
	int var; // length=0, address=24
	char Name[32]; // length=32, address=28
};

struct PADRECORD {
	unsigned char pad; // length=0, address=0
	char analogue; // length=0, address=1
	unsigned char run; // length=0, address=2
};

struct ARC_ENTRY {
	short address; // length=0, address=0
	short length; // length=0, address=2
};

struct USVECTOR_NOPAD {
	unsigned short vx; // length=0, address=0
	unsigned short vy; // length=0, address=2
	unsigned short vz; // length=0, address=4
};

struct DRIVER2_STRAIGHT {
	int Midx; // length=0, address=0
	int Midz; // length=0, address=4
	unsigned short length; // length=0, address=8
	short bing; // length=0, address=10
	short angle; // length=0, address=12
	short ConnectIdx[4]; // length=8, address=14
	char NumLanes; // length=0, address=22
	char LaneDirs; // length=0, address=23
	char AILanes; // length=0, address=24
	char packing; // length=0, address=25
};

struct OLD_DRIVER2_JUNCTION {
	int Midx; // length=0, address=0
	int Midz; // length=0, address=4
	short length; // length=0, address=8
	short width; // length=0, address=10
	short angle; // length=0, address=12
	short ExitIdx[4]; // length=8, address=14
	unsigned short flags; // length=0, address=22
};

struct DRIVER2_JUNCTION {
	short ExitIdx[4]; // length=8, address=0
	unsigned long flags; // length=0, address=8
};

struct DRIVER2_CURVE {
	int Midx; // length=0, address=0
	int Midz; // length=0, address=4
	short start; // length=0, address=8
	short end; // length=0, address=10
	short ConnectIdx[4]; // length=8, address=12
	short gradient; // length=0, address=20
	short height; // length=0, address=22
	char NumLanes; // length=0, address=24
	char LaneDirs; // length=0, address=25
	char inside; // length=0, address=26
	char AILanes; // length=0, address=27
};

struct _sdPlane {
	short surface; // length=0, address=0
	short a; // length=0, address=2
	short b; // length=0, address=4
	short c; // length=0, address=6
	int d; // length=0, address=8
};

struct _sdNode {
	int angle : 11; // address=0.0
	int dist : 12; // address=1.3
	int address : 8; // address=2.7
	int node : 1; // address=3.7
};

struct OrientedBox {
	struct VECTOR_NOPAD location; // length=12, address=0
	struct SVECTOR_NOPAD radii[3]; // length=18, address=12
	short length[3]; // length=6, address=30
};

struct WHEEL {
	char susCompression; // length=0, address=0
	char locked; // length=0, address=1
	char onGrass; // length=0, address=2
	unsigned char surface; // length=0, address=3
};

struct _HANDLING_DATA {
	struct MATRIX where; // length=32, address=0
	struct MATRIX drawCarMat; // length=32, address=32
	long acc[4]; // length=16, address=64
	long aacc[4]; // length=16, address=80
	int wheel_speed; // length=0, address=96
	int speed; // length=0, address=100
	int direction; // length=0, address=104
	char gear; // length=0, address=108
	char changingGear; // length=0, address=109
	char mayBeColliding; // length=0, address=110
	char autoBrake; // length=0, address=111
	struct WHEEL wheel[4]; // length=16, address=112
	short revs; // length=0, address=128
	struct VECTOR shadowPoints[4]; // length=64, address=132
	int front_vel; // length=0, address=196
	int rear_vel; // length=0, address=200
	struct OrientedBox oBox; // length=36, address=204
};

struct _APPEARANCE_DATA {
	struct SXYPAIR light_trails[4][4]; // length=64, address=0
	struct CAR_COSMETICS *carCos; // length=236, address=64
	short old_clock[4]; // length=8, address=68
	char life; // length=0, address=76
	char coplife; // length=0, address=77
	short qy; // length=0, address=78
	short qw; // length=0, address=80
	char life2; // length=0, address=82
	char model; // length=0, address=83
	char palette; // length=0, address=84
	char needsDenting; // length=0, address=85
	short damage[6]; // length=12, address=86
};

struct CIV_ROUTE_ENTRY {
	short dir; // length=0, address=0
	unsigned short pathType; // length=0, address=2
	int distAlongSegment; // length=0, address=4
	int x; // length=0, address=8
	int z; // length=0, address=12
};

struct CIV_STATE {
	int currentRoad; // length=0, address=0
	int currentNode; // length=0, address=4
	struct CIV_ROUTE_ENTRY *ctrlNode; // length=16, address=8
	unsigned char ctrlState; // length=0, address=12
	unsigned char trafficLightPhaseId; // length=0, address=13
	unsigned char changeLane; // length=0, address=14
	unsigned char turnDir; // length=0, address=15
	char brakeLight; // length=0, address=16
	unsigned char oldLane; // length=0, address=17
	unsigned char changeLaneCount; // length=0, address=18
	unsigned char pad3; // length=0, address=19
	int turnNode; // length=0, address=20
	int changeLaneIndicateCount; // length=0, address=24
	int carPauseCnt; // length=0, address=28
	int velRatio; // length=0, address=32
	struct CIV_ROUTE_ENTRY targetRoute[13]; // length=208, address=36
	struct CIV_ROUTE_ENTRY *pnode; // length=16, address=244
	unsigned char maxSpeed; // length=0, address=248
	unsigned char thrustState; // length=0, address=249
	unsigned char carMustDie; // length=0, address=250
	unsigned char currentLane; // length=0, address=251
};

struct COP {
	struct VECTOR2 targetHistory[2]; // length=16, address=0
	char routeInMemory; // length=0, address=16
	char justPinged; // length=0, address=17
	char close_pursuit; // length=0, address=18
	char dying; // length=0, address=19
	unsigned short DistanceToPlayer; // length=0, address=20
	short desiredSpeed; // length=0, address=22
	short recalcTimer; // length=0, address=24
	short stuckTimer; // length=0, address=26
	short lastRecoverStrategy; // length=0, address=28
	short recoveryTimer; // length=0, address=30
	short hiddenTimer; // length=0, address=32
	short frontLClear; // length=0, address=34
	short frontRClear; // length=0, address=36
};

struct LEAD_CAR {
	char dstate; // length=0, address=0
	char ctt; // length=0, address=1
	short targetDir; // length=0, address=2
	int targetX; // length=0, address=4
	int targetZ; // length=0, address=8
	int currentRoad; // length=0, address=12
	int lastRoad; // length=0, address=16
	int nextJunction; // length=0, address=20
	int nextTurn; // length=0, address=24
	int nextExit; // length=0, address=28
	int stuckCount; // length=0, address=32
	int panicCount; // length=0, address=36
	int recoverTime; // length=0, address=40
	int roadPosition; // length=0, address=44
	int roadForward; // length=0, address=48
	int boringness; // length=0, address=52
	int avoid; // length=0, address=56
	int lastTarget; // length=0, address=60
	int offRoad; // length=0, address=64
	int width; // length=0, address=68
	int d; // length=0, address=72
	int base_Normal; // length=0, address=76
	int base_Angle; // length=0, address=80
	int base_Dir; // length=0, address=84
	int outsideSpoolRegion; // length=0, address=88
	int direction; // length=0, address=92
	int lastDirection; // length=0, address=96
	char takeDamage; // length=0, address=100
};

struct _CAR_DATA {
	struct _HANDLING_DATA hd; // length=240, address=0
	union RigidBodyState st; // length=52, address=240
	struct _APPEARANCE_DATA ap; // length=100, address=292
	unsigned char hndType; // length=0, address=392
	unsigned char controlType; // length=0, address=393
	unsigned char controlFlags; // length=0, address=394
	char id; // length=0, address=395
	union ai {
		char *padid; // length=0, address=0
		struct CIV_STATE c; // length=252, address=0
		struct COP p; // length=40, address=0
		struct LEAD_CAR l; // length=104, address=0
	};
 // length=252, address=396
	int *inform; // length=0, address=648
	short thrust; // length=0, address=652
	short felonyRating; // length=0, address=654
	char handbrake; // length=0, address=656
	char wheelspin; // length=0, address=657
	char wasOnGround; // length=0, address=658
	char lowDetail; // length=0, address=659
	short wheel_angle; // length=0, address=660
	unsigned short totalDamage; // length=0, address=662
	long lastPad; // length=0, address=664
};

struct CAR_COSMETICS {
	struct SVECTOR headLight; // length=8, address=0
	struct SVECTOR frontInd; // length=8, address=8
	struct SVECTOR backInd; // length=8, address=16
	struct SVECTOR brakeLight; // length=8, address=24
	struct SVECTOR revLight; // length=8, address=32
	struct SVECTOR policeLight; // length=8, address=40
	struct SVECTOR exhaust; // length=8, address=48
	struct SVECTOR smoke; // length=8, address=56
	struct SVECTOR fire; // length=8, address=64
	struct SVECTOR wheelDisp[4]; // length=32, address=72
	short extraInfo; // length=0, address=104
	short powerRatio; // length=0, address=106
	short cbYoffset; // length=0, address=108
	short susCoeff; // length=0, address=110
	short traction; // length=0, address=112
	short wheelSize; // length=0, address=114
	struct SVECTOR cPoints[12]; // length=96, address=116
	struct SVECTOR colBox; // length=8, address=212
	struct SVECTOR cog; // length=8, address=220
	short twistRateX; // length=0, address=228
	short twistRateY; // length=0, address=230
	short twistRateZ; // length=0, address=232
	short mass; // length=0, address=234
};

struct _COP_DATA {
	int speed; // length=0, address=0
	int power; // length=0, address=4
	int min; // length=0, address=8
	int max; // length=0, address=12
};

struct LEAD_PARAMETERS {
	int tEnd; // length=0, address=0
	int tAvelLimit; // length=0, address=4
	int tDist; // length=0, address=8
	int tDistMul; // length=0, address=12
	int tWidth; // length=0, address=16
	int tWidthMul; // length=0, address=20
	int tWidth80; // length=0, address=24
	int tWidth80Mul; // length=0, address=28
	int hEnd; // length=0, address=32
	int dEnd; // length=0, address=36
	int hDist; // length=0, address=40
	int hDistMul; // length=0, address=44
	int hWidth; // length=0, address=48
	int hWidthMul; // length=0, address=52
	int hWidth80; // length=0, address=56
	int hWidth80Mul; // length=0, address=60
};

struct _EVENT {
	struct VECTOR position; // length=16, address=0
	short rotation; // length=0, address=16
	short timer; // length=0, address=18
	int *data; // length=0, address=20
	int *node; // length=0, address=24
	short flags; // length=0, address=28
	short radius; // length=0, address=30
	int model; // length=0, address=32
	struct _EVENT *next; // length=40, address=36
};

struct MAPPING {
	unsigned short button_lookup[16]; // length=32, address=0
	unsigned short swap_analog; // length=0, address=32
	unsigned short reserved1; // length=0, address=34
};

struct SAVED_PLAYER_POS {
	unsigned short type; // length=0, address=0
	short direction; // length=0, address=2
	long vx; // length=0, address=4
	long vy; // length=0, address=8
	long vz; // length=0, address=12
	unsigned long felony; // length=0, address=16
	unsigned short totaldamage; // length=0, address=20
	short damage[6]; // length=12, address=22
};

struct SAVED_CAR_POS {
	char active; // length=0, address=0
	unsigned char model; // length=0, address=1
	unsigned char palette; // length=0, address=2
	unsigned short totaldamage; // length=0, address=4
	unsigned short damage[6]; // length=12, address=6
	short direction; // length=0, address=18
	long vx; // length=0, address=20
	long vy; // length=0, address=24
	long vz; // length=0, address=28
};

struct MISSION_DATA {
	struct SAVED_PLAYER_POS PlayerPos; // length=36, address=0
	struct SAVED_CAR_POS CarPos[6]; // length=192, address=36
};

struct SCORE_ENTRY {
	int time; // length=0, address=0
	short items; // length=0, address=4
	char name[6]; // length=6, address=6
};

struct SCORE_TABLES {
	struct SCORE_ENTRY GetawayTable[4][2][5]; // length=480, address=0
	struct SCORE_ENTRY GateRaceTable[4][2][5]; // length=480, address=480
	struct SCORE_ENTRY CheckpointTable[4][2][5]; // length=480, address=960
	struct SCORE_ENTRY TrailblazerTable[4][2][5]; // length=480, address=1440
	struct SCORE_ENTRY SurvivalTable[4][1][5]; // length=240, address=1920
};

struct ACTIVE_CHEATS {
	unsigned char cheat1 : 1; // address=0.0
	unsigned char cheat2 : 1; // address=0.1
	unsigned char cheat3 : 1; // address=0.2
	unsigned char cheat4 : 1; // address=0.3
	unsigned char cheat5 : 1; // address=0.4
	unsigned char cheat6 : 1; // address=0.5
	unsigned char cheat7 : 1; // address=0.6
	unsigned char cheat8 : 1; // address=0.7
	unsigned char cheat9 : 1; // address=1.0
	unsigned char cheat10 : 1; // address=1.1
	unsigned char cheat11 : 1; // address=1.2
	unsigned char reserved1 : 5; // address=1.3
	unsigned char reserved2; // length=0, address=2
	unsigned char reserved3; // length=0, address=3
};

struct STREAM_SOURCE {
	unsigned char type; // length=0, address=0
	unsigned char model; // length=0, address=1
	unsigned char palette; // length=0, address=2
	char controlType; // length=0, address=3
	unsigned short flags; // length=0, address=4
	unsigned short rotation; // length=0, address=6
	struct VECTOR_NOPAD position; // length=12, address=8
	int totaldamage; // length=0, address=20
	int damage[6]; // length=24, address=24
};

struct DRAWENV {
	struct RECT clip; // length=8, address=0
	short ofs[2]; // length=4, address=8
	struct RECT tw; // length=8, address=12
	unsigned short tpage; // length=0, address=20
	unsigned char dtd; // length=0, address=22
	unsigned char dfe; // length=0, address=23
	unsigned char isbg; // length=0, address=24
	unsigned char r0; // length=0, address=25
	unsigned char g0; // length=0, address=26
	unsigned char b0; // length=0, address=27
	struct DR_ENV dr_env; // length=64, address=28
};

struct DISPENV {
	struct RECT disp; // length=8, address=0
	struct RECT screen; // length=8, address=8
	unsigned char isinter; // length=0, address=16
	unsigned char isrgb24; // length=0, address=17
	unsigned char pad0; // length=0, address=18
	unsigned char pad1; // length=0, address=19
};

struct DR_LOAD {
	unsigned long tag; // length=0, address=0
	unsigned long code[3]; // length=12, address=4
	unsigned long p[13]; // length=52, address=16
};

struct MODEL {
	unsigned short shape_flags; // length=0, address=0
	unsigned short flags2; // length=0, address=2
	short instance_number; // length=0, address=4
	unsigned char tri_verts; // length=0, address=6
	unsigned char zBias; // length=0, address=7
	short bounding_sphere; // length=0, address=8
	unsigned short num_point_normals; // length=0, address=10
	unsigned short num_vertices; // length=0, address=12
	unsigned short num_polys; // length=0, address=14
	int vertices; // length=0, address=16
	int poly_block; // length=0, address=20
	int normals; // length=0, address=24
	int point_normals; // length=0, address=28
	int collision_block; // length=0, address=32
};

struct UV {
	unsigned char u0; // length=0, address=0
	unsigned char v0; // length=0, address=1
	unsigned char u1; // length=0, address=2
	unsigned char v1; // length=0, address=3
	unsigned char u2; // length=0, address=4
	unsigned char v2; // length=0, address=5
	unsigned char u3; // length=0, address=6
	unsigned char v3; // length=0, address=7
};

struct TEXTURE_DETAILS {
	struct UV coords; // length=8, address=0
	unsigned short tpageid; // length=0, address=8
	unsigned short clutid; // length=0, address=10
	char texture_number; // length=0, address=12
	char texture_page; // length=0, address=13
};

struct CELL_OBJECT {
	struct VECTOR_NOPAD pos; // length=12, address=0
	unsigned char pad; // length=0, address=12
	unsigned char yang; // length=0, address=13
	unsigned short type; // length=0, address=14
};

struct ANIMATED_OBJECT {
	int internal_id; // length=0, address=0
	int model_num; // length=0, address=4
	char *name; // length=0, address=8
	char LitPoly; // length=0, address=12
};

struct SMASHABLE_OBJECT {
	int modelIdx; // length=0, address=0
	char *name; // length=0, address=4
	int sound; // length=0, address=8
	int volume; // length=0, address=12
	int pitch; // length=0, address=16
};

struct GARAGE_DOOR {
	struct CELL_OBJECT *cop; // length=16, address=0
	struct VECTOR_NOPAD old_pos; // length=12, address=4
	struct VECTOR_NOPAD pos; // length=12, address=16
	short rotation; // length=0, address=28
	char yang; // length=0, address=30
};

struct RGB16 {
	short r; // length=0, address=0
	short g; // length=0, address=2
	short b; // length=0, address=4
	short pad; // length=0, address=6
};

struct UnpaddedHackVector {
	int vx; // length=0, address=0
	int vz; // length=0, address=4
	short vy; // length=0, address=8
};

struct UnpaddedCharVector {
	char vx; // length=0, address=0
	char vy; // length=0, address=1
	char vz; // length=0, address=2
};

struct BVECTOR {
	char vx; // length=0, address=0
	char vy; // length=0, address=1
	char vz; // length=0, address=2
	char pad; // length=0, address=3
};

struct ADJACENT_ROAD_INFO {
	struct DVECTOR address; // length=4, address=0
	struct GAP_INFO gap; // length=6, address=4
};

struct SpuVolume {
	short left; // length=0, address=0
	short right; // length=0, address=2
};

struct SpuVoiceAttr {
	unsigned long voice; // length=0, address=0
	unsigned long mask; // length=0, address=4
	struct SpuVolume volume; // length=4, address=8
	struct SpuVolume volmode; // length=4, address=12
	struct SpuVolume volumex; // length=4, address=16
	unsigned short pitch; // length=0, address=20
	unsigned short note; // length=0, address=22
	unsigned short sample_note; // length=0, address=24
	short envx; // length=0, address=26
	unsigned long addr; // length=0, address=28
	unsigned long loop_addr; // length=0, address=32
	long a_mode; // length=0, address=36
	long s_mode; // length=0, address=40
	long r_mode; // length=0, address=44
	unsigned short ar; // length=0, address=48
	unsigned short dr; // length=0, address=50
	unsigned short sr; // length=0, address=52
	unsigned short rr; // length=0, address=54
	unsigned short sl; // length=0, address=56
	unsigned short adsr1; // length=0, address=58
	unsigned short adsr2; // length=0, address=60
};

struct SpuExtAttr {
	struct SpuVolume volume; // length=4, address=0
	long reverb; // length=0, address=4
	long mix; // length=0, address=8
};

struct SpuStVoiceAttr {
	char status; // length=0, address=0
	char pad1; // length=0, address=1
	char pad2; // length=0, address=2
	char pad3; // length=0, address=3
	long last_size; // length=0, address=4
	unsigned long buf_addr; // length=0, address=8
	unsigned long data_addr; // length=0, address=12
};


struct FELONY_DELAY {
	short current; // length=0, address=0
	short maximum; // length=0, address=2
};

struct FELONY_VALUE {
	short placid; // length=0, address=0
	short angry; // length=0, address=2
};

struct DB {
	char *primptr; // length=0, address=0
	unsigned long *ot; // length=0, address=4
	char *primtab; // length=0, address=8
	int id; // length=0, address=12
	struct DRAWENV draw; // length=92, address=16
	struct DISPENV disp; // length=20, address=108
};

struct _TARGET {
	int data[16]; // length=64, address=0
};

struct MR_TIMER {
	short x; // length=0, address=0
	short y; // length=0, address=2
	unsigned char flags; // length=0, address=4
	unsigned char min; // length=0, address=5
	unsigned char sec; // length=0, address=6
	unsigned char frac; // length=0, address=7
	long count; // length=0, address=8
};

struct PEDESTRIAN {
	struct PEDESTRIAN *pNext; // length=92, address=0
	struct PEDESTRIAN *pPrev; // length=92, address=4
	void(*fpRestState)(); // length=0, address=8
	void(*fpAgitatedState)(); // length=0, address=12
	char padId; // length=0, address=16
	enum PED_MODEL_TYPES pedType; // length=1, address=17
	struct VECTOR_NOPAD position; // length=12, address=20
	struct SVECTOR dir; // length=8, address=32
	struct SVECTOR velocity; // length=8, address=40
	struct VECTOR target; // length=16, address=48
	int flags; // length=0, address=64
	short head_pos; // length=0, address=68
	short head_rot; // length=0, address=70
	short index; // length=0, address=72
	short last_dir; // length=0, address=74
	short interest; // length=0, address=76
	char frame1; // length=0, address=78
	char *motion; // length=0, address=80
	char speed; // length=0, address=84
	char doing_turn; // length=0, address=85
	char finished_turn; // length=0, address=86
	char seat_index; // length=0, address=87
	unsigned char pallet; // length=0, address=88
	enum PED_ACTION_TYPE type; // length=1, address=89
};

struct __skidinfo {
	char chan; // length=0, address=0
	char sound; // length=0, address=1
};

struct __horninfo {
	char on; // length=0, address=0
	char time; // length=0, address=1
	char request; // length=0, address=2
};

struct CYCLE_OBJECT {
	char *name; // length=0, address=0
	short vx; // length=0, address=4
	short vy; // length=0, address=6
	short start1; // length=0, address=8
	short stop1; // length=0, address=10
	short speed1; // length=0, address=12
	short start2; // length=0, address=14
	short stop2; // length=0, address=16
	short speed2; // length=0, address=18
};

struct POLY_G4 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	unsigned char r1; // length=0, address=12
	unsigned char g1; // length=0, address=13
	unsigned char b1; // length=0, address=14
	unsigned char pad1; // length=0, address=15
	short x1; // length=0, address=16
	short y1; // length=0, address=18
	unsigned char r2; // length=0, address=20
	unsigned char g2; // length=0, address=21
	unsigned char b2; // length=0, address=22
	unsigned char pad2; // length=0, address=23
	short x2; // length=0, address=24
	short y2; // length=0, address=26
	unsigned char r3; // length=0, address=28
	unsigned char g3; // length=0, address=29
	unsigned char b3; // length=0, address=30
	unsigned char pad3; // length=0, address=31
	short x3; // length=0, address=32
	short y3; // length=0, address=34
};

struct TILE {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	short w; // length=0, address=12
	short h; // length=0, address=14
};

struct DR_TPAGE {
	unsigned long tag; // length=0, address=0
	unsigned long code[1]; // length=4, address=4
};


struct CAR_POLY {
	int vindices; // length=0, address=0
	int nindices; // length=0, address=4
	int clut_uv0; // length=0, address=8
	int tpage_uv1; // length=0, address=12
	int uv3_uv2; // length=0, address=16
	short originalindex; // length=0, address=20
};

struct COLOUR_BAND {
	struct CVECTOR colour; // length=4, address=0
	int value; // length=0, address=4
	int flags; // length=0, address=8
};

struct _PERCENTAGE_BAR {
	char *tag; // length=0, address=0
	short xpos; // length=0, address=4
	short ypos; // length=0, address=6
	short width; // length=0, address=8
	short height; // length=0, address=10
	unsigned short position; // length=0, address=12
	unsigned short max; // length=0, address=14
	struct COLOUR_BAND *pColourBand; // length=12, address=16
	int flags; // length=0, address=20
	int active; // length=0, address=24
};

struct POLY_F3 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	short x1; // length=0, address=12
	short y1; // length=0, address=14
	short x2; // length=0, address=16
	short y2; // length=0, address=18
};

struct POLY_F4 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	short x1; // length=0, address=12
	short y1; // length=0, address=14
	short x2; // length=0, address=16
	short y2; // length=0, address=18
	short x3; // length=0, address=20
	short y3; // length=0, address=22
};

struct POLY_FT3 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	unsigned char u0; // length=0, address=12
	unsigned char v0; // length=0, address=13
	unsigned short clut; // length=0, address=14
	short x1; // length=0, address=16
	short y1; // length=0, address=18
	unsigned char u1; // length=0, address=20
	unsigned char v1; // length=0, address=21
	unsigned short tpage; // length=0, address=22
	short x2; // length=0, address=24
	short y2; // length=0, address=26
	unsigned char u2; // length=0, address=28
	unsigned char v2; // length=0, address=29
	unsigned short pad1; // length=0, address=30
};

struct POLY_FT4 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	unsigned char u0; // length=0, address=12
	unsigned char v0; // length=0, address=13
	unsigned short clut; // length=0, address=14
	short x1; // length=0, address=16
	short y1; // length=0, address=18
	unsigned char u1; // length=0, address=20
	unsigned char v1; // length=0, address=21
	unsigned short tpage; // length=0, address=22
	short x2; // length=0, address=24
	short y2; // length=0, address=26
	unsigned char u2; // length=0, address=28
	unsigned char v2; // length=0, address=29
	unsigned short pad1; // length=0, address=30
	short x3; // length=0, address=32
	short y3; // length=0, address=34
	unsigned char u3; // length=0, address=36
	unsigned char v3; // length=0, address=37
	unsigned short pad2; // length=0, address=38
};

struct POLY_G3 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	unsigned char r1; // length=0, address=12
	unsigned char g1; // length=0, address=13
	unsigned char b1; // length=0, address=14
	unsigned char pad1; // length=0, address=15
	short x1; // length=0, address=16
	short y1; // length=0, address=18
	unsigned char r2; // length=0, address=20
	unsigned char g2; // length=0, address=21
	unsigned char b2; // length=0, address=22
	unsigned char pad2; // length=0, address=23
	short x2; // length=0, address=24
	short y2; // length=0, address=26
};

struct LINE_F2 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	short x1; // length=0, address=12
	short y1; // length=0, address=14
};

struct LINE_G2 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	unsigned char r1; // length=0, address=12
	unsigned char g1; // length=0, address=13
	unsigned char b1; // length=0, address=14
	unsigned char p1; // length=0, address=15
	short x1; // length=0, address=16
	short y1; // length=0, address=18
};

struct LINE_F4 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	short x1; // length=0, address=12
	short y1; // length=0, address=14
	short x2; // length=0, address=16
	short y2; // length=0, address=18
	short x3; // length=0, address=20
	short y3; // length=0, address=22
	unsigned long pad; // length=0, address=24
};

struct TILE_1 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
};

struct DR_AREA {
	unsigned long tag; // length=0, address=0
	unsigned long code[2]; // length=8, address=4
};

struct COP_SIGHT_DATA {
	short surroundViewDistance; // length=0, address=0
	short frontViewDistance; // length=0, address=2
	short frontViewAngle; // length=0, address=4
};

struct MAPTEX {
	short u; // length=0, address=0
	short w; // length=0, address=2
	short v; // length=0, address=4
	short h; // length=0, address=6
};

struct OVERMAP {
	int x_offset; // length=0, address=0
	int y_offset; // length=0, address=4
	int width; // length=0, address=8
	int height; // length=0, address=12
	char toptile; // length=0, address=16
	char dummy; // length=0, address=17
	int scale; // length=0, address=20
};

struct REPLAY_PARAMETER_BLOCK {
	int RecordingEnd; // length=0, address=0
	struct VECTOR_NOPAD lead_car_start; // length=12, address=4
	short Lead_car_dir; // length=0, address=16
	unsigned char timeofday; // length=0, address=18
	unsigned char weather; // length=0, address=19
};


struct REPLAY_SAVE_HEADER {
	unsigned long magic; // length=0, address=0
	unsigned char GameLevel; // length=0, address=4
	unsigned char GameType; // length=0, address=5
	unsigned char reserved1; // length=0, address=6
	unsigned char NumReplayStreams; // length=0, address=7
	unsigned char NumPlayers; // length=0, address=8
	unsigned char RandomChase; // length=0, address=9
	unsigned char CutsceneEvent; // length=0, address=10
	unsigned char gCopDifficultyLevel; // length=0, address=11
	struct MISSION_DATA SavedData; // length=228, address=12
	struct ACTIVE_CHEATS ActiveCheats; // length=4, address=240
	int wantedCar[2]; // length=8, address=244
	int MissionNumber; // length=0, address=252
	int HaveStoredData; // length=0, address=256
	int reserved2[6]; // length=24, address=260
};

struct REPLAY_STREAM_HEADER {
	struct STREAM_SOURCE SourceType; // length=48, address=0
	int Size; // length=0, address=48
	int Length; // length=0, address=52
};

struct REPLAY_STREAM {
	struct STREAM_SOURCE SourceType; // length=48, address=0
	struct PADRECORD *InitialPadRecordBuffer; // length=3, address=48
	struct PADRECORD *PadRecordBuffer; // length=3, address=52
	struct PADRECORD *PadRecordBufferEnd; // length=3, address=56
	unsigned char playbackrun; // length=0, address=60
	int length; // length=0, address=64
};

struct _PING_PACKET {
	unsigned short frame; // length=0, address=0
	char carId; // length=0, address=2
	char cookieCount; // length=0, address=3
};


struct ROADBLOCK {
	struct VECTOR position; // length=16, address=0
	struct ADJACENT_ROAD_INFO adjacentRoadInfo; // length=10, address=16
	short RoadToBlock; // length=0, address=26
	short AdjacentRoad; // length=0, address=28
	short RoadblockTimer; // length=0, address=30
	int copRespawnTime; // length=0, address=32
	char NumCarsNeededForRoad; // length=0, address=36
	char NumCarsNeededForAdjacentRoad; // length=0, address=37
	char NumCarsSavedForBlock; // length=0, address=38
	char DirectionToRoadblock; // length=0, address=39
	char status; // length=0, address=40
	char AI_Slot[13]; // length=13, address=41
};

struct TestResult {
	int depth; // length=0, address=0
	struct VECTOR location; // length=16, address=4
	struct VECTOR normal; // length=16, address=20
};


struct BUILDING_BOX {
	struct VECTOR pos; // length=16, address=0
	int xsize; // length=0, address=16
	int zsize; // length=0, address=20
	int theta; // length=0, address=24
	int height; // length=0, address=28
};

struct CDATA2D {
	struct VECTOR x; // length=16, address=0
	struct VECTOR axis[2]; // length=32, address=16
	struct VECTOR vel; // length=16, address=48
	int theta; // length=0, address=64
	int length[2]; // length=8, address=68
	int dist[2]; // length=8, address=76
	int limit[2]; // length=8, address=84
	int avel; // length=0, address=92
	int isCameraOrTanner; // length=0, address=96
};

struct CRET2D {
	struct VECTOR hit; // length=16, address=0
	struct VECTOR surfNormal; // length=16, address=16
	int penetration; // length=0, address=32
	int neverfree; // length=0, address=36
};

struct __tunnelcoords {
	struct VECTOR p1; // length=16, address=0
	struct VECTOR p2; // length=16, address=16
};

struct _ExOBJECT {
	int time; // length=0, address=0
	int speed; // length=0, address=4
	int hscale; // length=0, address=8
	int rscale; // length=0, address=12
	enum ExplosionType type; // length=2, address=16
	struct VECTOR pos; // length=16, address=20
};

struct BOMB {
	unsigned char flags; // length=0, address=0
	unsigned char active; // length=0, address=1
	short rot_speed; // length=0, address=2
	struct VECTOR position; // length=16, address=4
	struct VECTOR velocity; // length=16, address=20
};

struct COLLISION_PACKET {
	short type; // length=0, address=0
	short xpos; // length=0, address=2
	short ypos; // length=0, address=4
	short zpos; // length=0, address=6
	short flags; // length=0, address=8
	short yang; // length=0, address=10
	short empty; // length=0, address=12
	short xsize; // length=0, address=14
	short ysize; // length=0, address=16
	short zsize; // length=0, address=18
};

struct _PLAYER {
	long pos[4]; // length=16, address=0
	int dir; // length=0, address=16
	struct VECTOR *spoolXZ; // length=16, address=20
	struct VECTOR cameraPos; // length=16, address=24
	int cameraDist; // length=0, address=40
	int maxCameraDist; // length=0, address=44
	int cameraAngle; // length=0, address=48
	int headPos; // length=0, address=52
	int headTarget; // length=0, address=56
	int viewChange; // length=0, address=60
	char dying; // length=0, address=64
	char upsideDown; // length=0, address=65
	char onGrass; // length=0, address=66
	char targetCarId; // length=0, address=67
	char cameraView; // length=0, address=68
	char headTimer; // length=0, address=69
	char playerType; // length=0, address=70
	char worldCentreCarId; // length=0, address=71
	char playerCarId; // length=0, address=72
	char cameraCarId; // length=0, address=73
	char padid; // length=0, address=74
	char car_is_sounding; // length=0, address=75
	long camera_vel[3]; // length=12, address=76
	int snd_cam_ang; // length=0, address=88
	struct __skidinfo skidding; // length=2, address=92
	struct __skidinfo wheelnoise; // length=2, address=94
	struct __horninfo horn; // length=3, address=96
	int car_sound_timer; // length=0, address=100
	short revsvol; // length=0, address=104
	short idlevol; // length=0, address=106
	struct PEDESTRIAN *pPed; // length=92, address=108
	int crash_timer; // length=0, address=112
};

struct XZPAIR {
	int x; // length=0, address=0
	int z; // length=0, address=4
};

struct CELL_DATA {
	unsigned short num; // length=0, address=0
};

struct PACKED_CELL_OBJECT {
	struct USVECTOR_NOPAD pos; // length=6, address=0
	unsigned short value; // length=0, address=6
};

struct PAD {
	unsigned char active; // length=0, address=0
	unsigned char type; // length=0, address=1
	unsigned char dualshock; // length=0, address=2
	unsigned char reserved1; // length=0, address=3
	unsigned short direct; // length=0, address=4
	unsigned short dirnew; // length=0, address=6
	char diranalog[4]; // length=4, address=8
	unsigned short mapped; // length=0, address=12
	unsigned short mapnew; // length=0, address=14
	char mapanalog[4]; // length=4, address=16
	struct MAPPING mappings; // length=36, address=20
	unsigned char alarmShakeCounter; // length=0, address=56
	unsigned char asd; // length=0, address=57
	unsigned char sdf; // length=0, address=58
	unsigned char dfg; // length=0, address=59
	unsigned char delay; // length=0, address=60
	unsigned char port; // length=0, address=61
	unsigned char state; // length=0, address=62
	unsigned char dsactive; // length=0, address=63
	unsigned char *shakeptr; // length=0, address=64
	unsigned char motors[2]; // length=2, address=68
	unsigned char shake_type; // length=0, address=70
	unsigned char vibrate; // length=0, address=71
};

struct CELL_ITERATOR {
	struct CELL_DATA *pcd; // length=2, address=0
	struct PACKED_CELL_OBJECT *ppco; // length=8, address=4
	struct XZPAIR near; // length=8, address=8
	int use_computed; // length=0, address=16
};

struct POLY_GT3 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	unsigned char u0; // length=0, address=12
	unsigned char v0; // length=0, address=13
	unsigned short clut; // length=0, address=14
	unsigned char r1; // length=0, address=16
	unsigned char g1; // length=0, address=17
	unsigned char b1; // length=0, address=18
	unsigned char p1; // length=0, address=19
	short x1; // length=0, address=20
	short y1; // length=0, address=22
	unsigned char u1; // length=0, address=24
	unsigned char v1; // length=0, address=25
	unsigned short tpage; // length=0, address=26
	unsigned char r2; // length=0, address=28
	unsigned char g2; // length=0, address=29
	unsigned char b2; // length=0, address=30
	unsigned char p2; // length=0, address=31
	short x2; // length=0, address=32
	short y2; // length=0, address=34
	unsigned char u2; // length=0, address=36
	unsigned char v2; // length=0, address=37
	unsigned short pad2; // length=0, address=38
};

struct POLYFT4LIT {
	unsigned char id; // length=0, address=0
	unsigned char texture_set; // length=0, address=1
	unsigned char texture_id; // length=0, address=2
	unsigned char spare; // length=0, address=3
	unsigned char v0; // length=0, address=4
	unsigned char v1; // length=0, address=5
	unsigned char v2; // length=0, address=6
	unsigned char v3; // length=0, address=7
	struct UV_INFO uv0; // length=2, address=8
	struct UV_INFO uv1; // length=2, address=10
	struct UV_INFO uv2; // length=2, address=12
	struct UV_INFO uv3; // length=2, address=14
	struct RGB color; // length=4, address=16
};

struct TEX_INFO {
	char name[8]; // length=8, address=0
	char tset; // length=0, address=8
	char u; // length=0, address=9
	char v; // length=0, address=10
	char w; // length=0, address=11
	char h; // length=0, address=12
};


struct TEXTURE_LOOKUP {
	struct TEX_INFO *Damage[6]; // length=24, address=0
};

struct CAR_MODEL {
	int numFT3; // length=0, address=0
	struct CAR_POLY *pFT3; // length=24, address=4
	int numGT3; // length=0, address=8
	struct CAR_POLY *pGT3; // length=24, address=12
	int numB3; // length=0, address=16
	struct CAR_POLY *pB3; // length=24, address=20
	struct SVECTOR *vlist; // length=8, address=24
	struct SVECTOR *nlist; // length=8, address=28
};

struct plotCarGlobals {
	unsigned char *primptr; // length=0, address=0
	long *ot; // length=0, address=4
	unsigned long intensity; // length=0, address=8
	unsigned short *pciv_clut; // length=0, address=12
	unsigned long ShineyTPageASL16; // length=0, address=16
	unsigned long ShineyClutASL16; // length=0, address=20
	unsigned char *damageLevel; // length=0, address=24
	unsigned char *shineyTable; // length=0, address=28
	int ghost; // length=0, address=32
};

struct _EXTRA_CIV_DATA {
	int surfInd; // length=0, address=0
	int distAlongSegment; // length=0, address=4
	short angle; // length=0, address=8
	unsigned short ctrlState; // length=0, address=10
	int thrustState; // length=0, address=12
	unsigned char palette; // length=0, address=16
	unsigned char controlFlags; // length=0, address=17
};

struct CIV_PING {
	int NumPingedIn; // length=0, address=0
	int OffRoad; // length=0, address=4
	int NotDrivable; // length=0, address=8
	int TooShortStr; // length=0, address=12
	int NearEndStr; // length=0, address=16
	int TooShortCrv; // length=0, address=20
	int NearEndCrv; // length=0, address=24
	int TooCloseNuddaCar; // length=0, address=28
	int TooClosePlayer; // length=0, address=32
	int InvalidRegion; // length=0, address=36
};


struct COP_DATA {
	int autoMaxPowerScaleLimit; // length=0, address=0
	int autoDesiredSpeedScaleLimit; // length=0, address=4
	int autoRespawnScaleLimit; // length=0, address=8
	int autoBatterPlayerTrigger; // length=0, address=12
	int immortal; // length=0, address=16
	int roadblockTrigger; // length=0, address=20
	int cutOffPowerScale; // length=0, address=24
	int cutOffDistance; // length=0, address=28
	short trigger[5]; // length=10, address=32
};

struct FELONY_DATA {
	struct FELONY_DELAY occurrenceDelay[12]; // length=48, address=0
	struct FELONY_DELAY reoccurrenceDelay[12]; // length=48, address=48
	struct FELONY_VALUE value[12]; // length=48, address=96
	int pursuitFelonyScale; // length=0, address=144
};

struct iVectNT {
	int n; // length=0, address=0
	int t; // length=0, address=4
};


struct PLAYBACKCAMERA {
	struct VECTOR_NOPAD position; // length=12, address=0
	struct SVECTOR angle; // length=8, address=12
	int FrameCnt; // length=0, address=20
	short CameraPosvy; // length=0, address=24
	short gCameraDistance; // length=0, address=26
	short gCameraMaxDistance; // length=0, address=28
	short gCameraAngle; // length=0, address=30
	char cameraview; // length=0, address=32
	char next; // length=0, address=33
	char prev; // length=0, address=34
	char idx; // length=0, address=35
};

struct CUTSCENE_BUFFER {
	int numResident; // length=0, address=0
	unsigned char residentCutscenes[4]; // length=4, address=4
	char *residentPointers[4]; // length=16, address=8
	char *currentPointer; // length=0, address=24
	int bytesFree; // length=0, address=28
	char buffer[8192]; // length=8192, address=32
};

struct CUTSCENE_INFO {
	unsigned short address; // length=0, address=0
	unsigned short length; // length=0, address=2
};

struct CUTSCENE_HEADER {
	int maxsize; // length=0, address=0
	struct CUTSCENE_INFO data[15]; // length=60, address=4
};

struct POLY_GT4 {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	unsigned char u0; // length=0, address=12
	unsigned char v0; // length=0, address=13
	unsigned short clut; // length=0, address=14
	unsigned char r1; // length=0, address=16
	unsigned char g1; // length=0, address=17
	unsigned char b1; // length=0, address=18
	unsigned char p1; // length=0, address=19
	short x1; // length=0, address=20
	short y1; // length=0, address=22
	unsigned char u1; // length=0, address=24
	unsigned char v1; // length=0, address=25
	unsigned short tpage; // length=0, address=26
	unsigned char r2; // length=0, address=28
	unsigned char g2; // length=0, address=29
	unsigned char b2; // length=0, address=30
	unsigned char p2; // length=0, address=31
	short x2; // length=0, address=32
	short y2; // length=0, address=34
	unsigned char u2; // length=0, address=36
	unsigned char v2; // length=0, address=37
	unsigned short pad2; // length=0, address=38
	unsigned char r3; // length=0, address=40
	unsigned char g3; // length=0, address=41
	unsigned char b3; // length=0, address=42
	unsigned char p3; // length=0, address=43
	short x3; // length=0, address=44
	short y3; // length=0, address=46
	unsigned char u3; // length=0, address=48
	unsigned char v3; // length=0, address=49
	unsigned short pad3; // length=0, address=50
};

struct POLYFT4 {
	unsigned char id; // length=0, address=0
	unsigned char texture_set; // length=0, address=1
	unsigned char texture_id; // length=0, address=2
	unsigned char spare; // length=0, address=3
	unsigned char v0; // length=0, address=4
	unsigned char v1; // length=0, address=5
	unsigned char v2; // length=0, address=6
	unsigned char v3; // length=0, address=7
	struct UV_INFO uv0; // length=2, address=8
	struct UV_INFO uv1; // length=2, address=10
	struct UV_INFO uv2; // length=2, address=12
	struct UV_INFO uv3; // length=2, address=14
	struct RGB color; // length=4, address=16
};

struct TPAN {
	unsigned char texture_page; // length=0, address=0
	unsigned char texture_number; // length=0, address=1
};


struct SMOKE {
	struct UnpaddedHackVector position; // length=12, address=0
	struct UnpaddedCharVector drift; // length=3, address=12
	struct UnpaddedCharVector drift_change; // length=3, address=15
	struct UnpaddedHackVector final_tail_pos; // length=12, address=20
	unsigned char step; // length=0, address=32
	unsigned char pos; // length=0, address=33
	short start_w; // length=0, address=34
	short final_w; // length=0, address=36
	char life; // length=0, address=38
	char halflife; // length=0, address=39
	unsigned short flags; // length=0, address=40
	unsigned char num; // length=0, address=42
	unsigned char t_step; // length=0, address=43
	short transparency; // length=0, address=44
};

struct DEBRIS {
	struct VECTOR position; // length=16, address=0
	struct SVECTOR direction; // length=8, address=16
	unsigned short life; // length=0, address=24
	unsigned short flags; // length=0, address=26
	unsigned short num; // length=0, address=28
	unsigned short pos; // length=0, address=30
	struct RGB rgb; // length=4, address=32
	char step; // length=0, address=36
	char type; // length=0, address=37
};

struct LEAF {
	struct VECTOR position; // length=16, address=0
	struct SVECTOR direction; // length=8, address=16
	unsigned short life; // length=0, address=24
	unsigned short flags; // length=0, address=26
	unsigned short num; // length=0, address=28
	unsigned short pos; // length=0, address=30
	struct RGB rgb; // length=4, address=32
	char step; // length=0, address=36
	char type; // length=0, address=37
	short sin_index1; // length=0, address=38
	short sin_index2; // length=0, address=40
	char sin_addition1; // length=0, address=42
	char sin_addition2; // length=0, address=43
};

struct DAMAGED_LAMP {
	struct CELL_OBJECT *cop; // length=16, address=0
	char damage; // length=0, address=4
};

struct DAMAGED_OBJECT {
	struct CELL_OBJECT cop; // length=16, address=0
	char active; // length=0, address=16
	char damage; // length=0, address=17
	int rot_speed; // length=0, address=20
	struct SVECTOR velocity; // length=8, address=24
	int vx; // length=0, address=32
};

struct TRI_POINT {
	struct BVECTOR v0; // length=4, address=0
	struct BVECTOR v1; // length=4, address=4
	struct BVECTOR v2; // length=4, address=8
};

struct TRI_POINT_LONG {
	struct VECTOR_NOPAD v0; // length=12, address=0
	struct VECTOR_NOPAD v1; // length=12, address=12
	struct VECTOR_NOPAD v2; // length=12, address=24
};

struct RAIN_TYPE {
	struct VECTOR_NOPAD position; // length=12, address=0
	struct SVECTOR oldposition; // length=8, address=12
};

struct LAMP_STREAK {
	struct SXYPAIR light_trails[4]; // length=16, address=0
	int id; // length=0, address=16
	short clock; // length=0, address=20
	char set; // length=0, address=22
};

struct ROUTE_DATA {
	short type; // length=0, address=0
	short height; // length=0, address=2
	short objectAngle; // length=0, address=4
};

struct DENTUVS {
	char u3; // length=0, address=0
};

struct HUBCAP {
	int Present[4]; // length=16, address=0
	struct VECTOR Offset[4]; // length=64, address=16
	struct MATRIX Orientation; // length=32, address=80
	struct MATRIX LocalOrientation; // length=32, address=112
	struct VECTOR Position; // length=16, address=144
	struct VECTOR Direction; // length=16, address=160
	float Height; // length=0, address=176
	int Duration; // length=0, address=180
};

struct SPRT {
	unsigned long tag; // length=0, address=0
	unsigned char r0; // length=0, address=4
	unsigned char g0; // length=0, address=5
	unsigned char b0; // length=0, address=6
	unsigned char code; // length=0, address=7
	short x0; // length=0, address=8
	short y0; // length=0, address=10
	unsigned char u0; // length=0, address=12
	unsigned char v0; // length=0, address=13
	unsigned short clut; // length=0, address=14
	short w; // length=0, address=16
	short h; // length=0, address=18
};

struct REPLAY_ICON {
	short x; // length=0, address=0
	short y; // length=0, address=2
	struct TEXTURE_DETAILS *texture; // length=14, address=4
	char *TextPtr; // length=0, address=8
	short tx; // length=0, address=12
	short ty; // length=0, address=14
};

struct _pct {
	struct DB *current; // length=128, address=0
	unsigned short *ptexture_pages[128]; // length=4, address=4
	unsigned short *ptexture_cluts[128][32]; // length=4, address=8
	long f4colourTable[32]; // length=128, address=12
	int *polySizes; // length=0, address=140
	char *primptr; // length=0, address=144
	unsigned long *ot; // length=0, address=148
	unsigned long clut; // length=0, address=152
	unsigned long tpage; // length=0, address=156
	unsigned long colour; // length=0, address=160
	int flags; // length=0, address=164
	struct SVECTOR *verts; // length=8, address=168
	unsigned long lastTexInfo; // length=0, address=172
	int scribble[8]; // length=32, address=176
	int model; // length=0, address=208
};

struct MATRIX2 {
	short m[3][3]; // length=18, address=0
	short computed; // length=0, address=18
	char null[12]; // length=12, address=20
};

struct Spool {
	unsigned short address; // length=0, address=0
	unsigned char connected_areas[2]; // length=2, address=2
	unsigned char pvs_size; // length=0, address=4
	unsigned char cell_data_size[3]; // length=3, address=5
	unsigned char super_region; // length=0, address=8
	unsigned char num_connected_areas; // length=0, address=9
	unsigned char roadm_size; // length=0, address=10
	unsigned char roadh_size; // length=0, address=11
};

struct PL_POLYFT4 {
	unsigned char id; // length=0, address=0
	unsigned char texture_set; // length=0, address=1
	unsigned char texture_id; // length=0, address=2
	unsigned char th; // length=0, address=3
	unsigned char v0; // length=0, address=4
	unsigned char v1; // length=0, address=5
	unsigned char v2; // length=0, address=6
	unsigned char v3; // length=0, address=7
	struct UV_INFO uv0; // length=2, address=8
	struct UV_INFO uv1; // length=2, address=10
	struct UV_INFO uv2; // length=2, address=12
	struct UV_INFO uv3; // length=2, address=14
};

struct MVERTEX {
	short vx; // length=0, address=0
	short vy; // length=0, address=2
	short vz; // length=0, address=4
	unsigned short uv; // length=0, address=6
};

struct VERTEX {
	struct DVECTOR coord; // length=4, address=0
	struct UV_INFO uv_coord; // length=2, address=4
	unsigned char pad[2]; // length=2, address=6
};

struct TRAILBLAZER_DATA {
	int x; // length=0, address=0
	int z; // length=0, address=4
	short y; // length=0, address=8
	short rot; // length=0, address=10
};

struct SMASHED_CONE {
	char cone; // length=0, address=0
	unsigned char active : 7; // address=1.0
	unsigned char side : 1; // address=1.7
	short rot_speed; // length=0, address=2
	struct VECTOR velocity; // length=16, address=4
};

struct POLYCOORD {
	short x; // length=0, address=0
	short y; // length=0, address=2
	short u; // length=0, address=4
	short v; // length=0, address=6
	short w; // length=0, address=8
	short h; // length=0, address=10
};

struct FixedEvent {
	struct VECTOR position; // length=16, address=0
	short rotation; // length=0, address=16
	short active; // length=0, address=18
	unsigned short initialRotation; // length=0, address=20
	unsigned short finalRotation; // length=0, address=22
	unsigned short minSpeed; // length=0, address=24
	unsigned short maxSpeed; // length=0, address=26
	short flags; // length=0, address=28
	short radius; // length=0, address=30
	int model; // length=0, address=32
	struct _EVENT *next; // length=40, address=36
	char *modelName; // length=0, address=40
};

struct EventGlobal {
	int camera; // length=0, address=0
	int draw; // length=0, address=4
	struct _EVENT **track; // length=40, address=8
	struct _EVENT *cameraEvent; // length=40, address=12
};


struct MissionTrain {
	struct _EVENT *engine; // length=40, address=0
	int *node; // length=0, address=4
	int cornerSpeed; // length=0, address=8
	int initialStraightSpeed; // length=0, address=12
	int finalStraightSpeed; // length=0, address=16
	int start; // length=0, address=20
	int startDir; // length=0, address=24
};

struct Foam {
	struct MODEL *model; // length=36, address=0
	int rotate; // length=0, address=4
};

struct EventCarriage {
	short rotation; // length=0, address=0
	short vel; // length=0, address=2
};

struct MultiCar {
	struct _EVENT *event; // length=40, address=0
	int count; // length=0, address=4
};

struct Helicopter {
	int speed; // length=0, address=0
	short pitch; // length=0, address=4
	short dp; // length=0, address=6
	short roll; // length=0, address=8
	short dr; // length=0, address=10
	int lastX; // length=0, address=12
	int lastZ; // length=0, address=16
	struct TEXTURE_DETAILS rotorTexture; // length=14, address=20
	short rotorrot; // length=0, address=34
	short rotorvel; // length=0, address=36
	int cleanModel; // length=0, address=40
	int deadModel; // length=0, address=44
};

struct Detonator {
	int timer; // length=0, address=0
	int count; // length=0, address=4
};

struct CameraDelay {
	int delay; // length=0, address=0
	int type; // length=0, address=4
};

struct EventCamera {
	struct VECTOR position; // length=16, address=0
	short yAng; // length=0, address=16
	struct MATRIX matrix; // length=32, address=20
	int rotate; // length=0, address=52
};

struct MULTICAR_DATA {
	int x; // length=0, address=0
	int z; // length=0, address=4
	unsigned char palette; // length=0, address=8
	unsigned char model; // length=0, address=9
	short rot; // length=0, address=10
};

struct RENDER_ARG {
	unsigned char render; // length=0, address=0
	unsigned char credits; // length=0, address=1
	unsigned short recap; // length=0, address=2
};

struct RENDER_ARGS {
	unsigned char nRenders; // length=0, address=0
	unsigned char subtitle; // length=0, address=1
	char screenx; // length=0, address=2
	char screeny; // length=0, address=3
	struct RENDER_ARG Args[4]; // length=16, address=4
};

struct __envsound {
	unsigned char type; // length=0, address=0
	unsigned char flags; // length=0, address=1
	struct VECTOR pos; // length=16, address=4
	struct VECTOR pos2; // length=16, address=20
	int bank; // length=0, address=36
	int sample; // length=0, address=40
	int vol; // length=0, address=44
};

struct __envsoundtags {
	int frame_cnt; // length=0, address=0
	int func_cnt; // length=0, address=4
	int num_envsnds; // length=0, address=8
	int envsnd_cnt; // length=0, address=12
};

struct __envsoundinfo {
	struct VECTOR eff_pos[4]; // length=64, address=0
	struct VECTOR cam_pos; // length=16, address=64
	float g[4]; // length=16, address=80
	int this[4]; // length=16, address=96
	int playing_sound[4]; // length=16, address=112
	int chan[4]; // length=16, address=128
	unsigned long flags; // length=0, address=144
};

struct SPEECH_QUEUE {
	char allowed; // length=0, address=0
	char chan; // length=0, address=1
	char is_playing; // length=0, address=2
	int count; // length=0, address=4
	char reverb; // length=0, address=8
	int slot[7]; // length=28, address=12
};

struct __othercarsound {
	int car; // length=0, address=0
	int chan; // length=0, address=4
	char in_use; // length=0, address=8
	char stopped; // length=0, address=9
	char idle; // length=0, address=10
};

struct __tunnelinfo {
	char num_tunnels; // length=0, address=0
	char tunnel_cnt; // length=0, address=1
	struct __tunnelcoords coords[29]; // length=928, address=4
};

struct __bitfield64 {
	long h; // length=0, address=0
	long l; // length=0, address=4
};

struct XMCHANNEL {
	unsigned short Octave; // length=0, address=0
	short LVol; // length=0, address=2
	short RVol; // length=0, address=4
	short OldLVol; // length=0, address=6
	short OldRVol; // length=0, address=8
	unsigned short OldPeriod; // length=0, address=10
	unsigned char OldSample; // length=0, address=12
	unsigned long OldSOff; // length=0, address=16
	unsigned long SOffset; // length=0, address=20
	unsigned char nothing; // length=0, address=24
	unsigned char ChDead; // length=0, address=25
	unsigned char panenvflg; // length=0, address=26
	unsigned char panenvpts; // length=0, address=27
	unsigned char panenvsus; // length=0, address=28
	unsigned char panenvbeg; // length=0, address=29
	unsigned char panenvend; // length=0, address=30
	short panenvp; // length=0, address=32
	unsigned short panenva; // length=0, address=34
	unsigned short panenvb; // length=0, address=36
	unsigned short keyoffspd; // length=0, address=38
	unsigned char envflg; // length=0, address=40
	unsigned char envpts; // length=0, address=41
	unsigned char envsus; // length=0, address=42
	unsigned char envbeg; // length=0, address=43
	unsigned char envend; // length=0, address=44
	short envp; // length=0, address=46
	unsigned short enva; // length=0, address=48
	unsigned short envb; // length=0, address=50
	unsigned char ins; // length=0, address=52
	unsigned char vol; // length=0, address=53
	unsigned char dat; // length=0, address=54
	unsigned char datold; // length=0, address=55
	unsigned char eff; // length=0, address=56
	unsigned char not; // length=0, address=57
	unsigned char oldvslide; // length=0, address=58
	unsigned char oldfvslide; // length=0, address=59
	unsigned char oldfslide; // length=0, address=60
	short fadevol; // length=0, address=62
	unsigned char keyon; // length=0, address=64
	unsigned char kick; // length=0, address=65
	unsigned char sample; // length=0, address=66
	short handle; // length=0, address=68
	unsigned long start; // length=0, address=72
	unsigned char panning; // length=0, address=76
	unsigned char pansspd; // length=0, address=77
	char volume; // length=0, address=78
	unsigned short period; // length=0, address=80
	unsigned short SPUPitch; // length=0, address=82
	char transpose; // length=0, address=84
	unsigned char note; // length=0, address=85
	short ownper; // length=0, address=86
	short ownvol; // length=0, address=88
	short UserVol; // length=0, address=90
	char retrig; // length=0, address=92
	unsigned short c2spd; // length=0, address=94
	char tmpvolume; // length=0, address=96
	unsigned short tmpperiod; // length=0, address=98
	unsigned short wantedperiod; // length=0, address=100
	unsigned short slidespeed; // length=0, address=102
	unsigned short portspeed; // length=0, address=104
	unsigned char s3mtremor; // length=0, address=106
	unsigned char s3mvolslide; // length=0, address=107
	unsigned char s3mrtgspeed; // length=0, address=108
	unsigned char s3mrtgslide; // length=0, address=109
	unsigned char glissando; // length=0, address=110
	unsigned char wavecontrol; // length=0, address=111
	char vibpos; // length=0, address=112
	unsigned char vibspd; // length=0, address=113
	unsigned char vibdepth; // length=0, address=114
	char trmpos; // length=0, address=115
	unsigned char trmspd; // length=0, address=116
	unsigned char trmdepth; // length=0, address=117
	unsigned char SPUChannel; // length=0, address=118
	unsigned char Dolby; // length=0, address=119
};

struct GEAR_DESC {
	int lowidl_ws; // length=0, address=0
	int low_ws; // length=0, address=4
	int hi_ws; // length=0, address=8
	int ratio_ac; // length=0, address=12
	int ratio_id; // length=0, address=16
};

struct PSXSCREEN {
	char index; // length=0, address=0
	unsigned char numButtons; // length=0, address=1
	char userFunctionNum; // length=0, address=2
	struct PSXBUTTON buttons[8]; // length=480, address=4
};

struct MISSION_STEP {
	unsigned char flags : 3; // address=0.0
	unsigned char recap : 5; // address=0.3
	unsigned char data : 7; // address=1.0
	unsigned char disc : 1; // address=1.7
};

struct BOUND_BOX {
	int x0; // length=0, address=0
	int y0; // length=0, address=4
	int z0; // length=0, address=8
	int x1; // length=0, address=12
	int y1; // length=0, address=16
	int z1; // length=0, address=20
};

struct _HANDLING_TYPE {
	char frictionScaleRatio; // length=0, address=0
	char aggressiveBraking; // length=0, address=1
	char fourWheelDrive; // length=0, address=2
	char autoBrakeOn; // length=0, address=3
};

struct CHEATS {
	int RearWheelSteer; // length=0, address=0
	int MiniCars; // length=0, address=4
	int Stilts; // length=0, address=8
	int LowGravity; // length=0, address=12
	int Australia; // length=0, address=16
	int MagicMirror; // length=0, address=20
};


struct BOXINFO {
	struct VECTOR vel; // length=16, address=0
	struct VECTOR pos; // length=16, address=16
	int sf; // length=0, address=32
	int xs; // length=0, address=36
	int zs; // length=0, address=40
	int w; // length=0, address=44
	int h; // length=0, address=48
	int zb; // length=0, address=52
	int ypos; // length=0, address=56
};

struct MAP_DATA {
	struct _CAR_DATA *cp; // length=0, address=0
	struct VECTOR *base; // length=16, address=4
	struct VECTOR *pos; // length=16, address=8
	struct VECTOR *vel; // length=16, address=12
	struct VECTOR *length; // length=16, address=16
	int intention; // length=0, address=20
	int *map; // length=0, address=24
	int *local; // length=0, address=28
};

struct GAME_SAVE_HEADER {
	unsigned long magic; // length=0, address=0
	unsigned char gMissionLadderPos; // length=0, address=4
	unsigned char pad1; // length=0, address=5
	unsigned char pad2; // length=0, address=6
	unsigned char pad3; // length=0, address=7
	struct MISSION_DATA SavedData; // length=228, address=8
	int reserved[8]; // length=32, address=236
};

struct CONFIG_SAVE_HEADER {
	unsigned long magic; // length=0, address=0
	int gMasterVolume; // length=0, address=4
	int gMusicVolume; // length=0, address=8
	int gSoundMode; // length=0, address=12
	int gVibration; // length=0, address=16
	int gCopDifficultyLevel; // length=0, address=20
	int gFurthestMission; // length=0, address=24
	struct MAPPING PadMapping[2]; // length=72, address=28
	struct SCORE_TABLES ScoreTables; // length=2160, address=100
	int PALAdjustX; // length=0, address=2260
	int PALAdjustY; // length=0, address=2264
	int NTSCAdjustX; // length=0, address=2268
	int NTSCAdjustY; // length=0, address=2272
	int gSubtitles; // length=0, address=2276
	struct ACTIVE_CHEATS AvailableCheats; // length=4, address=2280
	int reserved[6]; // length=24, address=2284
};

struct OUT_CELL_FILE_HEADER {
	int cells_across; // length=0, address=0
	int cells_down; // length=0, address=4
	int cell_size; // length=0, address=8
	int num_regions; // length=0, address=12
	int region_size; // length=0, address=16
	int num_cell_objects; // length=0, address=20
	int num_cell_data; // length=0, address=24
	int ambient_light_level; // length=0, address=28
	struct VECTOR_NOPAD light_source; // length=12, address=32
};


struct XYWH {
	short x; // length=0, address=0
	short y; // length=0, address=2
	short w; // length=0, address=4
	short h; // length=0, address=6
};


struct MENU_HEADER {
	char *Title; // length=0, address=0
	struct XYWH Bound; // length=8, address=4
	unsigned char NumItems; // length=0, address=12
	struct MENU_ITEM *MenuItems; // length=20, address=16
};

struct MENU_ITEM {
	char *Text; // length=0, address=0
	unsigned char Type; // length=0, address=4
	unsigned char Justify; // length=0, address=5
	void(*func)(); // length=0, address=8
	enum EXIT_VALUE ExitValue; // length=1, address=12
	struct MENU_HEADER *SubMenu; // length=0, address=16
};


struct AREA_LOAD_INFO {
	int xoffset; // length=0, address=0
	int zoffset; // length=0, address=4
};


struct ROAD_MAP_LUMP_DATA {
	int width; // length=0, address=0
	int height; // length=0, address=4
	int unitXMid; // length=0, address=8
	int unitZMid; // length=0, address=12
};

struct __io {
	char in; // length=0, address=0
	char out; // length=0, address=1
};

struct __xa_request {
	short delay; // length=0, address=0
	char bank; // length=0, address=2
	char track; // length=0, address=3
	char mission; // length=0, address=4
	char cutscene; // length=0, address=5
};

struct _MISSION {
	int id; // length=0, address=0
	int length; // length=0, address=4
	int city; // length=0, address=8
	int time; // length=0, address=12
	int weather; // length=0, address=16
	struct XYPAIR playerStartPosition; // length=8, address=20
	int playerStartRotation; // length=0, address=28
	int type; // length=0, address=32
	short timer; // length=0, address=36
	short timerFlags; // length=0, address=38
	int strings; // length=0, address=40
	struct _COP_DATA cops; // length=16, address=44
	int msgCarWrecked; // length=0, address=60
	int msgOutOfTime; // length=0, address=64
	int msgComplete; // length=0, address=68
	int region; // length=0, address=72
	int route; // length=0, address=76
	int msgDrowned; // length=0, address=80
	int playerCarModel; // length=0, address=84
	int playerCarColour; // length=0, address=88
	int maxDamage; // length=0, address=92
	int residentModels[5]; // length=20, address=96
	int nCutscenes; // length=0, address=116
	int title; // length=0, address=120
	int msgPoliceCar; // length=0, address=124
	int msgDoorsLocked; // length=0, address=128
};

struct _ROUTE_INFO {
	int nJunctions; // length=0, address=0
	char data[1000][4]; // length=4000, address=4
	struct LEAD_PARAMETERS parameters; // length=64, address=4004
};

struct MR_MISSION {
	int active; // length=0, address=0
	int gameover_delay; // length=0, address=4
	enum PAUSEMODE gameover_mode; // length=1, address=8
	short message_timer[2]; // length=4, address=10
	short message_priority[2]; // length=4, address=14
	char *message_string[2]; // length=8, address=20
	struct MR_TIMER timer[2]; // length=24, address=28
	struct _TARGET *CarTarget; // length=64, address=52
	struct _TARGET *ChaseTarget; // length=64, address=56
	int PhantomCarId; // length=0, address=60
	int ChaseHitDelay; // length=0, address=64
	char *StealMessage; // length=0, address=68
};

struct STOPCOPS {
	struct VECTOR_NOPAD pos; // length=12, address=0
	int radius; // length=0, address=12
};

struct MR_THREAD {
	unsigned char active; // length=0, address=0
	unsigned char player; // length=0, address=1
	unsigned long *initial_sp; // length=0, address=4
	unsigned long *pc; // length=0, address=8
	unsigned long *sp; // length=0, address=12
};

struct POLYFT3 {
	unsigned char id; // length=0, address=0
	unsigned char texture_set; // length=0, address=1
	unsigned char texture_id; // length=0, address=2
	unsigned char spare; // length=0, address=3
	unsigned char v0; // length=0, address=4
	unsigned char v1; // length=0, address=5
	unsigned char v2; // length=0, address=6
	unsigned char pad; // length=0, address=7
	struct UV_INFO uv0; // length=2, address=8
	struct UV_INFO uv1; // length=2, address=10
	struct UV_INFO uv2; // length=2, address=12
	struct UV_INFO pad2; // length=2, address=14
	struct RGB color; // length=4, address=16
};

struct BONE {
	enum LIMBS id; // length=1, address=0
	struct BONE *pParent; // length=68, address=4
	char numChildren; // length=0, address=8
	struct BONE *pChildren[3]; // length=12, address=12
	struct SVECTOR_NOPAD *pvOrigPos; // length=6, address=24
	struct SVECTOR *pvRotation; // length=8, address=28
	struct VECTOR vOffset; // length=16, address=32
	struct VECTOR vCurrPos; // length=16, address=48
	struct MODEL **pModel; // length=36, address=64
};

struct PED_DATA {
	char cWidth; // length=0, address=0
	unsigned char cAdj; // length=0, address=1
	struct TEXTURE_DETAILS *ptd; // length=14, address=4
	enum TEXTURE_PALS texPal; // length=1, address=8
};

struct tRay {
	long org[4]; // length=16, address=0
	long dir[4]; // length=16, address=16
};

struct tRange {
	int lower; // length=0, address=0
	int upper; // length=0, address=4
};

struct tAABB {
	struct tRange slab[3]; // length=24, address=0
};

struct PADRAW {
	unsigned char status; // length=0, address=0
	unsigned char id; // length=0, address=1
	unsigned char buttons[2]; // length=2, address=2
	unsigned char analog[4]; // length=4, address=4
};

struct DUPLICATION {
	char *buffer; // length=0, address=0
	int length; // length=0, address=4
};

struct tNode {
	int vx; // length=0, address=0
	int vy; // length=0, address=4
	int vz; // length=0, address=8
	unsigned short dist; // length=0, address=12
	unsigned short ptoey; // length=0, address=14
};

struct tNodeDir {
	short dx; // length=0, address=0
	short dz; // length=0, address=2
};


struct PLAYER_SCORE {
	int time; // length=0, address=0
	int P2time; // length=0, address=4
	short items; // length=0, address=8
	short P2items; // length=0, address=10
	char name[6]; // length=6, address=12
};

struct SEATED_PEDESTRIANS {
	int x; // length=0, address=0
	int z; // length=0, address=4
	short rotation; // length=0, address=8
	char index; // length=0, address=10
	char pad; // length=0, address=11
};

struct CAR_COLLISION_BOX {
	int min_x; // length=0, address=0
	int max_x; // length=0, address=4
	int min_z; // length=0, address=8
	int max_z; // length=0, address=12
};

struct PEDESTRIAN_ROADS {
	short pos; // length=0, address=0
	short north; // length=0, address=2
	short south; // length=0, address=4
	short east; // length=0, address=6
	short west; // length=0, address=8
};

struct OUT_FONTINFO {
	unsigned char x; // length=0, address=0
	unsigned char y; // length=0, address=1
	char offx; // length=0, address=2
	char offy; // length=0, address=3
	unsigned char width; // length=0, address=4
	unsigned char height; // length=0, address=5
	unsigned short pad; // length=0, address=6
};

struct FONT_DIGIT {
	char xOffset; // length=0, address=0
	char width; // length=0, address=1
};

struct TEXINF {
	unsigned short id; // length=0, address=0
	unsigned short nameoffset; // length=0, address=2
	unsigned char x; // length=0, address=4
	unsigned char y; // length=0, address=5
	unsigned char width; // length=0, address=6
	unsigned char height; // length=0, address=7
};

struct SHADOWHDR {
	unsigned long num_common_verts; // length=0, address=0
	unsigned short num_verts_total; // length=0, address=4
	unsigned short num_polys_total; // length=0, address=6
	unsigned short vert_offsets[4]; // length=8, address=8
	unsigned short nverts[4]; // length=8, address=16
	unsigned short npolys[4]; // length=8, address=24
	unsigned long *poly_block[4]; // length=16, address=32
	struct SVECTOR *vertices; // length=8, address=48
};

struct TYRE_TRACK {
	char type; // length=0, address=0
	char shade; // length=0, address=1
	char shade_type; // length=0, address=2
	char surface; // length=0, address=3
	struct SVECTOR_NOPAD p1; // length=6, address=4
	struct SVECTOR_NOPAD p2; // length=6, address=10
	struct SVECTOR_NOPAD p3; // length=6, address=16
	struct SVECTOR_NOPAD p4; // length=6, address=22
};

struct S_XYZ {
	short x; // length=0, address=0
	short y; // length=0, address=2
	short z; // length=0, address=4
};

struct DR_MOVE {
	unsigned long tag; // length=0, address=0
	unsigned long code[5]; // length=20, address=4
};

struct FLAREREC {
	struct RGB16 transparency; // length=8, address=0
	char length; // length=0, address=8
	short gapmod; // length=0, address=10
};

struct SpuReverbAttr {
	unsigned long mask; // length=0, address=0
	long mode; // length=0, address=4
	struct SpuVolume depth; // length=4, address=8
	long delay; // length=0, address=12
	long feedback; // length=0, address=16
};

struct SpuCommonAttr {
	unsigned long mask; // length=0, address=0
	struct SpuVolume mvol; // length=4, address=4
	struct SpuVolume mvolmode; // length=4, address=8
	struct SpuVolume mvolx; // length=4, address=12
	struct SpuExtAttr cd; // length=12, address=16
	struct SpuExtAttr ext; // length=12, address=28
};

struct __LSBDinfo {
	int addr; // length=0, address=0
	int memtop; // length=0, address=4
	int count[7]; // length=28, address=8
	int bnktop[7]; // length=28, address=36
	int append; // length=0, address=64
};

struct CHANNEL_DATA {
	struct SpuVoiceAttr attr; // length=64, address=0
	unsigned char loop; // length=0, address=64
	unsigned char locked; // length=0, address=65
	unsigned short time; // length=0, address=66
	long samplerate; // length=0, address=68
	char player; // length=0, address=72
	long srcvolume; // length=0, address=76
	long volumeScale; // length=0, address=80
	unsigned short srcpitch; // length=0, address=84
	unsigned short dopplerScale; // length=0, address=86
	long cameradist; // length=0, address=88
	long lastcameradist; // length=0, address=92
	struct VECTOR *srcposition; // length=16, address=96
	struct VECTOR position; // length=16, address=100
	long *srcvelocity; // length=0, address=116
};

struct SAMPLE_DATA {
	unsigned long address; // length=0, address=0
	unsigned long length; // length=0, address=4
	unsigned long loop; // length=0, address=8
	unsigned long samplerate; // length=0, address=12
};


struct __pauseinfo {
	unsigned short pitch[16]; // length=32, address=0
	unsigned short voll[16]; // length=32, address=32
	unsigned short volr[16]; // length=32, address=64
	unsigned short max; // length=0, address=96
	unsigned short lev; // length=0, address=98
};

struct SPOOLQ {
	unsigned char type; // length=0, address=0
	unsigned char data; // length=0, address=1
	unsigned short nsectors; // length=0, address=2
	unsigned long sector; // length=0, address=4
	char *addr; // length=0, address=8
	void(*func)(); // length=0, address=12
};

struct SPL_REGIONINFO {
	unsigned short region_to_unpack; // length=0, address=0
	unsigned short target_barrel_region; // length=0, address=2
	int nsectors; // length=0, address=4
	char *cell_addr; // length=0, address=8
	char *roadm_addr; // length=0, address=12
};

struct AreaDataStr {
	unsigned short gfx_offset; // length=0, address=0
	unsigned short model_offset; // length=0, address=2
	unsigned short music_offset; // length=0, address=4
	unsigned short ambient_offset; // length=0, address=6
	unsigned char model_size; // length=0, address=8
	unsigned char pad; // length=0, address=9
	unsigned char num_tpages; // length=0, address=10
	unsigned char ambient_size; // length=0, address=11
	unsigned char music_size; // length=0, address=12
	unsigned char music_samples_size; // length=0, address=13
	unsigned char music_id; // length=0, address=14
	unsigned char ambient_id; // length=0, address=15
};


struct CdlFILE {
	struct CdlLOC pos; // length=4, address=0
	unsigned long length; // length=0, address=4
	char name[16]; // length=16, address=8
};

struct DRAW_MODE {
	short x1; // length=0, address=0
	short y1; // length=0, address=2
	short x2; // length=0, address=4
	short y2; // length=0, address=6
	short width; // length=0, address=8
	short height; // length=0, address=10
	short framex; // length=0, address=12
	short framey; // length=0, address=14
};

struct TARGET_ARROW_MODEL {
	struct SVECTOR *pVerts; // length=8, address=0
	char *pTris; // length=0, address=4
	char numTris; // length=0, address=8
};

struct TP {
	unsigned long flags; // length=0, address=0
	unsigned long address; // length=0, address=4
};

struct CAR_LOCALS {
	long vel[4]; // length=16, address=0
	long avel[4]; // length=16, address=16
	int extraangulardamping; // length=0, address=32
	int aggressive; // length=0, address=36
};

struct CdlFILTER {
	unsigned char file; // length=0, address=0
	unsigned char chan; // length=0, address=1
	unsigned short pad; // length=0, address=2
};

struct XA_TRACK {
	int start; // length=0, address=0
	int end; // length=0, address=4
};

struct XM_HeaderInfo {
	unsigned short BPM; // length=0, address=0
	unsigned short Speed; // length=0, address=2
};

struct XM_VABInfo {
	unsigned char *Address; // length=0, address=0
	unsigned long Size; // length=0, address=4
};

struct XM_Feedback {
	unsigned char Volume; // length=0, address=0
	short Panning; // length=0, address=2
	int CurrentStart; // length=0, address=4
	short PlayNext; // length=0, address=8
	unsigned short SongLength; // length=0, address=10
	unsigned char Status; // length=0, address=12
	unsigned short PatternPos; // length=0, address=14
	short SongPos; // length=0, address=16
	unsigned short CurrentPattern; // length=0, address=18
	unsigned short SongSpeed; // length=0, address=20
	unsigned short SongBPM; // length=0, address=22
	int SongLoop; // length=0, address=24
	int ActiveVoices; // length=0, address=28
};

struct XMHEADER {
	unsigned short version; // length=0, address=0
	unsigned short songlength; // length=0, address=2
	unsigned short restart; // length=0, address=4
	unsigned short numchn; // length=0, address=6
	unsigned short numpat; // length=0, address=8
	unsigned short numins; // length=0, address=10
	unsigned short flags; // length=0, address=12
	unsigned short tempo; // length=0, address=14
	unsigned short bpm; // length=0, address=16
	unsigned short XMChannels; // length=0, address=18
	unsigned short XMPSXChannels; // length=0, address=20
	unsigned long *JAP_PAT_ADDR[256]; // length=1024, address=24
	unsigned long *JAP_PAT_ADDR2[256]; // length=1024, address=1048
	unsigned long *JAP_InstrumentOffset[128]; // length=512, address=2072
	unsigned long *JAP_SampAddr[128]; // length=512, address=2584
	unsigned long *JAP_SampHdrAddr[128]; // length=512, address=3096
	unsigned char jorders[256]; // length=256, address=3608
	int S3MPanning; // length=0, address=3864
};

struct XMSONG {
	unsigned char Status; // length=0, address=0
	int HeaderNum; // length=0, address=4
	int CurPos; // length=0, address=8
	unsigned short reppos; // length=0, address=12
	unsigned short repcnt; // length=0, address=14
	unsigned short vbtick; // length=0, address=16
	unsigned short patbrk; // length=0, address=18
	unsigned char patdly; // length=0, address=20
	unsigned char patdly2; // length=0, address=21
	unsigned short numrow; // length=0, address=22
	short posjmp; // length=0, address=24
	unsigned short PatternPos; // length=0, address=26
	short SongPos; // length=0, address=28
	unsigned short CurrentPattern; // length=0, address=30
	unsigned short SongSpeed; // length=0, address=32
	unsigned short SongBPM; // length=0, address=34
	int SongLoop; // length=0, address=36
	unsigned char SongVolume; // length=0, address=40
	unsigned char MasterVolume; // length=0, address=41
	int XMActiveVoices; // length=0, address=44
	int NotAmiga; // length=0, address=48
	unsigned char XMPlay; // length=0, address=52
	int FirstCh; // length=0, address=56
	int JBPM; // length=0, address=60
	int PCounter; // length=0, address=64
	unsigned short PatSize; // length=0, address=68
	unsigned long *PatAdr; // length=0, address=72
	unsigned long *PatAdr2; // length=0, address=76
	int PlayMask; // length=0, address=80
	int SFXNum; // length=0, address=84
	struct XMCHANNEL XM_Chnl[24]; // length=2880, address=88
	int JUp; // length=0, address=2968
	short PlayNext; // length=0, address=2972
	short BPlayNext; // length=0, address=2974
	short BPlayFlag; // length=0, address=2976
	int CurrentStart; // length=0, address=2980
	unsigned char VabID; // length=0, address=2984
	short UserPan; // length=0, address=2986
	unsigned char MaxChans; // length=0, address=2988
};


struct FE_CHARDATA {
	unsigned char u; // length=0, address=0
	unsigned char v; // length=0, address=1
	unsigned char w; // length=0, address=2
	unsigned char h; // length=0, address=3
};

struct FE_FONT {
	int NumFonts; // length=0, address=0
	struct FE_CHARDATA CharInfo[256]; // length=1024, address=4
};

struct SCREEN_LIMITS {
	short minx; // length=0, address=0
	short miny; // length=0, address=2
	short maxx; // length=0, address=4
	short maxy; // length=0, address=6
};

struct BOTCH {
	int missNum; // length=0, address=0
	char **name; // length=0, address=4
};

struct FILEFORMAT {
	char blockSize; // length=0, address=0
	char asciiTitle[32]; // length=32, address=1
	short kanjiTitle[32]; // length=64, address=34
	char sonyProductCode[13]; // length=13, address=98
	char blockType; // length=0, address=111
	short blockIconClut[16]; // length=32, address=112
	int blockIconData[32]; // length=128, address=144
	int sliceByteSize; // length=0, address=272
	long *sliceIconTimPtrs[16]; // length=64, address=276
};

struct SLICE {
	char title[20]; // length=20, address=0
	char sliceIconRefs[3]; // length=3, address=20
	char *sliceData; // length=0, address=24
};

struct MouseData {
	unsigned short buttons; // length=0, address=0
	char xOffset; // length=0, address=2
	char yOffset; // length=0, address=3
};

struct NegconData {
	unsigned short digitalButtons; // length=0, address=0
	char centralTwist; // length=0, address=2
	char buttonI; // length=0, address=3
	char buttonII; // length=0, address=4
	char topLeft; // length=0, address=5
};

struct AnalogjoyData {
	unsigned short digitalButtons; // length=0, address=0
	unsigned char right_x; // length=0, address=2
	unsigned char right_y; // length=0, address=3
	unsigned char left_x; // length=0, address=4
	unsigned char left_y; // length=0, address=5
};

struct TapCtrllerData {
	unsigned char transStatus; // length=0, address=0
	unsigned char dataFormat; // length=0, address=1
	union tapdata {
		unsigned short pad; // length=0, address=0
		struct NegconData negcon; // length=6, address=0
		struct MouseData mouse; // length=4, address=0
	};
 // length=6, address=2
};

struct MultiTapData {
	struct TapCtrllerData ctrllers[4]; // length=32, address=0
};

struct _CARD {
	char Magic[2]; // length=2, address=0
	char Type; // length=0, address=2
	char BlockEntry; // length=0, address=3
	char Title[64]; // length=64, address=4
	char reserve[28]; // length=28, address=68
	char Clut[32]; // length=32, address=96
	char Icon[3][128]; // length=384, address=128
};

struct TIMSTRUCT {
	unsigned short clut; // length=0, address=0
	unsigned short tpage; // length=0, address=2
	unsigned short x; // length=0, address=4
	unsigned short y; // length=0, address=6
	unsigned short w; // length=0, address=8
	unsigned short h; // length=0, address=10
};

struct FONTTABSTRUCT {
	struct TIMSTRUCT timStruct; // length=12, address=0
	short width; // length=0, address=12
	short height; // length=0, address=14
};

struct KANJILOOKUP {
	short sjisCode; // length=0, address=0
	unsigned int used; // length=0, address=4
	struct TIMSTRUCT timStruct; // length=12, address=8
};

struct SLICEHEADER {
	int length; // length=0, address=0
	char title[20]; // length=20, address=4
	char iconRef[3]; // length=3, address=24
	char used; // length=0, address=27
	short checksum; // length=0, address=28
	short pad; // length=0, address=30
};

struct BLOCKINFO {
	unsigned int infoOK; // length=0, address=0
	int id; // length=0, address=4
	int length; // length=0, address=8
	int freeBytes; // length=0, address=12
	struct DIRENTRY dirEntry; // length=40, address=16
	struct _CARD header; // length=512, address=56
	struct TIMSTRUCT iconTim; // length=12, address=568
	unsigned int gremBlock; // length=0, address=580
	int sliceCount; // length=0, address=584
	int usedSlices; // length=0, address=588
	struct SLICEHEADER sliceHeader[16]; // length=512, address=592
};

struct CARDINFO {
	int usedBlocks; // length=0, address=0
	struct BLOCKINFO blockInfo[15]; // length=16560, address=4
	unsigned int dirOK; // length=0, address=16564
	unsigned int infoOK; // length=0, address=16568
};

struct MCSLOT {
	struct CARDINFO m_cardInfo; // length=16572, address=0
	int m_port; // length=0, address=16572
	int m_card; // length=0, address=16576
	int m_chan; // length=0, address=16580
	char m_device[6]; // length=6, address=16584
	int m_blocksRead; // length=0, address=16592
	int m_readFilePtr; // length=0, address=16596
	int m_readBytes; // length=0, address=16600
	int m_fromReadBytes; // length=0, address=16604
	int m_toReadBytes; // length=0, address=16608
	int m_writeFilePtr; // length=0, address=16612
	int m_writeBytes; // length=0, address=16616
	int m_fromWriteBytes; // length=0, address=16620
	int m_toWriteBytes; // length=0, address=16624
	int m_iconX; // length=0, address=16628
	int m_iconY; // length=0, address=16632
	int m_clutX; // length=0, address=16636
	int m_clutY; // length=0, address=16640
	unsigned int m_doCheckSum; // length=0, address=16644
	short m_checkSumWork; // length=0, address=16648
	short m_checkSum; // length=0, address=16650
};

struct MCPAD {
	struct MCSLOT m_mcSlot0; // length=16652, address=0
	struct MCSLOT m_mcSlot1; // length=16652, address=16652
	int m_mouseX; // length=0, address=33304
	int m_mouseY; // length=0, address=33308
	int m_scanPort; // length=0, address=33312
	unsigned int m_cardChanged[2]; // length=8, address=33316
	unsigned int m_bControllerChanged; // length=0, address=33324
	unsigned int m_bMouseTested; // length=0, address=33328
	unsigned int m_bUsingMouse; // length=0, address=33332
	unsigned int m_bUsingNegCon; // length=0, address=33336
	unsigned int m_bControllerInserted; // length=0, address=33340
	int m_nLastControllerType; // length=0, address=33344
	char slotString[3]; // length=3, address=33348
	struct MCSLOT *m_slotObjPtrs[2]; // length=8, address=33352
	int m_slotObjPorts[2]; // length=8, address=33360
	int m_currSlotObj; // length=0, address=33368
	int m_portStatus[8]; // length=32, address=33372
};

struct POINT {
	int x; // length=0, address=0
	int y; // length=0, address=4
};

struct DISPMAN {
	unsigned int m_displayingMessage; // length=0, address=0
	int m_language; // length=0, address=4
	char m_textBuffer[256]; // length=256, address=8
	struct DR_AREA m_sliceClipArea; // length=12, address=264
	struct DR_AREA m_screenClipArea; // length=12, address=276
	struct RECT m_backRect[7]; // length=56, address=288
	struct RECT m_srcRect[7]; // length=56, address=344
	int s_screenMode; // length=0, address=400
	int dispWidth; // length=0, address=404
	int dispHeight; // length=0, address=408
	int dispXOffset; // length=0, address=412
	int dispYOffset; // length=0, address=416
	struct DRAWENV m_drawEnv; // length=92, address=420
	struct DISPENV m_dispEnv; // length=20, address=512
	struct DRAWENV m_oldDrawEnv; // length=92, address=532
	struct DISPENV m_oldDispEnv; // length=20, address=624
	int spriteCount; // length=0, address=644
	int polyCountFT4; // length=0, address=648
	int polyCountG3; // length=0, address=652
	int polyCountF4; // length=0, address=656
	int moveCount; // length=0, address=660
	int m_dirtyMouseX; // length=0, address=664
	int m_dirtyMouseY; // length=0, address=668
	unsigned short m_dirtyMouseBuffer[256]; // length=512, address=672
	char m_kanjiTimBuffer[350]; // length=350, address=1184
	struct SPRT sprites[200]; // length=4000, address=1536
	struct DR_TPAGE tpages[200]; // length=1600, address=5536
	struct POLY_FT4 polysFT4[25]; // length=1000, address=7136
	//struct POLY_F4 polysF4[0]; // length=0, address=8136
	struct POLY_G3 polysG3[20]; // length=560, address=8136
	struct DR_MOVE moves[2]; // length=48, address=8696
	int m_dispX; // length=0, address=8744
	int m_dispY; // length=0, address=8748
	int m_flashCount; // length=0, address=8752
	int m_flash; // length=0, address=8756
	unsigned int m_flashOn; // length=0, address=8760
	unsigned int m_invalidArea[7]; // length=28, address=8764
	int m_addingBlock; // length=0, address=8792
	int m_deletingBlock; // length=0, address=8796
	struct FONTTABSTRUCT m_fontTable[3][76]; // length=3648, address=8800
	struct KANJILOOKUP m_kanjiFontTable[256]; // length=5120, address=12448
	struct TIMSTRUCT m_darkTimStruct; // length=12, address=17568
	struct TIMSTRUCT m_pointerTimStruct; // length=12, address=17580
	struct TIMSTRUCT m_lightTimStruct; // length=12, address=17592
	struct TIMSTRUCT m_cardTimStruct; // length=12, address=17604
	struct TIMSTRUCT m_buttonTimStructs[4]; // length=48, address=17616
	struct TIMSTRUCT m_arrowTimStruct[2]; // length=24, address=17664
	struct TIMSTRUCT m_sliceIconTimStructs[16]; // length=192, address=17688
	struct TIMSTRUCT m_createBlockTimStruct; // length=12, address=17880
	struct PAD *m_padPtr; // length=33404, address=17892
	long *m_backImagePtr; // length=0, address=17896
	int m_updateQueue[7]; // length=28, address=17900
	int m_kanjiChars; // length=0, address=17928
	int m_activeArea; // length=0, address=17932
	int m_menuSelect; // length=0, address=17936
	int m_blockSelect; // length=0, address=17940
	int m_sliceSelect; // length=0, address=17944
	int m_sliceMenuOffset; // length=0, address=17948
	int m_sliceMenuRem; // length=0, address=17952
	int m_sliceMenuInc; // length=0, address=17956
	int m_activeFunction; // length=0, address=17960
	int m_mainFunction; // length=0, address=17964
	int m_maxKanji; // length=0, address=17968
	unsigned int m_menuActive[4]; // length=16, address=17972
	char *m_menuText[4]; // length=16, address=17988
	char *m_infoText[3]; // length=12, address=18004
	char *m_titleText; // length=0, address=18016
	char *m_blockNameText; // length=0, address=18020
	char m_saveFilename[32]; // length=32, address=18024
	struct FILEFORMAT *m_fileFormatPtr; // length=340, address=18056
};

struct ControllerPacket {
	unsigned char transStatus; // length=0, address=0
	unsigned char dataFormat; // length=0, address=1
	union data {
		unsigned short pad; // length=0, address=0
		struct MouseData mouse; // length=4, address=0
		struct NegconData negcon; // length=6, address=0
		struct AnalogjoyData joystick; // length=6, address=0
		struct MultiTapData tap; // length=32, address=0
	};
 // length=32, address=2
};

// 319 typedefs
typedef struct MATRIX MATRIX;
typedef struct VECTOR VECTOR;
typedef struct SVECTOR SVECTOR;
typedef struct CVECTOR CVECTOR;
typedef struct DVECTOR DVECTOR;
typedef struct RVECTOR RVECTOR;
typedef struct CRVECTOR3 CRVECTOR3;
typedef struct CRVECTOR4 CRVECTOR4;
typedef struct RECT RECT;
typedef struct DR_ENV DR_ENV;
typedef struct SndVolume2 SndVolume2;
typedef struct CdlLOC CdlLOC;
typedef struct VECTOR_NOPAD VECTOR_NOPAD;
typedef struct SVECTOR_NOPAD SVECTOR_NOPAD;
typedef struct BOX BOX;
typedef struct BSPHERE BSPHERE;
typedef struct RGB RGB;
typedef struct UV_INFO UV_INFO;
typedef struct XYPAIR XYPAIR;
typedef struct SXYPAIR SXYPAIR;
typedef struct GAP_INFO GAP_INFO;
typedef struct PSXBUTTON PSXBUTTON;
typedef struct PADRECORD PADRECORD;
typedef struct ARC_ENTRY ARC_ENTRY;
typedef struct USVECTOR_NOPAD USVECTOR_NOPAD;
typedef struct DRIVER2_STRAIGHT DRIVER2_STRAIGHT;
typedef struct OLD_DRIVER2_JUNCTION OLD_DRIVER2_JUNCTION;
typedef struct DRIVER2_JUNCTION DRIVER2_JUNCTION;
typedef struct DRIVER2_CURVE DRIVER2_CURVE;
typedef struct _sdPlane sdPlane;
typedef struct _sdNode sdNode;
typedef struct _CAR_DATA CAR_DATA;
typedef struct CIV_ROUTE_ENTRY CIV_ROUTE_ENTRY;
typedef struct CIV_STATE CIV_STATE;
typedef struct CAR_COSMETICS CAR_COSMETICS;
typedef struct VECTOR2 VECTOR2;
typedef struct COP COP;
typedef struct LEAD_CAR LEAD_CAR;
typedef union RigidBodyState RigidBodyState;
typedef struct WHEEL WHEEL;
typedef struct OrientedBox OrientedBox;
typedef struct _HANDLING_DATA HANDLING_DATA;
typedef struct _APPEARANCE_DATA APPEARANCE_DATA;
typedef struct _COP_DATA MS_COP_DATA;
typedef struct LEAD_PARAMETERS LEAD_PARAMETERS;
typedef struct _EVENT EVENT;
typedef struct MAPPING MAPPING;
typedef struct SAVED_PLAYER_POS SAVED_PLAYER_POS;
typedef struct SAVED_CAR_POS SAVED_CAR_POS;
typedef struct MISSION_DATA MISSION_DATA;
typedef struct MISSION_STEP MISSION_STEP;
typedef struct SCORE_ENTRY SCORE_ENTRY;
typedef struct SCORE_TABLES SCORE_TABLES;
typedef struct ACTIVE_CHEATS ACTIVE_CHEATS;
typedef struct STREAM_SOURCE STREAM_SOURCE;
typedef struct CIV_PING CIV_PING;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned short ushort;
typedef struct _physadr *physadr;
typedef long daddr_t;
typedef char *caddr_t;
typedef long *qaddr_t;
typedef unsigned long ino_t;
typedef long swblk_t;
typedef unsigned int size_t;
//typedef long time_t;
typedef short dev_t;
typedef long off_t;
typedef unsigned short uid_t;
typedef unsigned short gid_t;
typedef void(*SsMarkCallbackProc)();
typedef void(*CdlCB)();
typedef long LONGVECTOR[4];
typedef short SHORTVECTOR[4];
typedef long LONGQUATERNION[4];
typedef unsigned long ulong;
//typedef unsigned long wchar_t;
typedef struct PADRAW *LPPADRAW;
typedef struct MAPPING *LPMAPPING;
typedef struct PAD *LPPAD;
typedef struct DRAWENV DRAWENV;
typedef struct DISPENV DISPENV;
typedef struct DR_LOAD DR_LOAD;
typedef struct MODEL MODEL;
typedef enum PAUSEMODE PAUSEMODE;
typedef struct UV UV;
typedef struct TEXTURE_DETAILS TEXTURE_DETAILS;
typedef struct CELL_OBJECT CELL_OBJECT;
typedef struct ANIMATED_OBJECT ANIMATED_OBJECT;
typedef struct SMASHABLE_OBJECT SMASHABLE_OBJECT;
typedef struct GARAGE_DOOR GARAGE_DOOR;
typedef struct RGB16 RGB16;
typedef struct BVECTOR BVECTOR;
typedef struct ADJACENT_ROAD_INFO ADJACENT_ROAD_INFO;
typedef struct SpuVolume SpuVolume;
typedef struct SpuVoiceAttr SpuVoiceAttr;
typedef struct SpuExtAttr SpuExtAttr;
typedef struct SpuStVoiceAttr SpuStVoiceAttr;
typedef struct FELONY_DELAY FELONY_DELAY;
typedef struct FELONY_VALUE FELONY_VALUE;
typedef struct DB DB;
typedef struct _TARGET MS_TARGET;
typedef struct MR_TIMER MR_TIMER;
typedef struct PEDESTRIAN PEDESTRIAN;
typedef enum PED_ACTION_TYPE PED_ACTION_TYPE;
typedef enum PED_MODEL_TYPES PED_MODEL_TYPES;
typedef struct __skidinfo skidinfo;
typedef struct __horninfo horninfo;
typedef struct CYCLE_OBJECT CYCLE_OBJECT;
typedef void(*SpuIRQCallbackProc)();
typedef void(*SpuTransferCallbackProc)();
typedef void(*SpuStCallbackProc)();
typedef unsigned char uchar;
typedef char schar;
typedef unsigned int uint;
typedef void (*envsoundfunc)(struct __envsound *ep /*$s1*/, struct __envsoundinfo *E /*$a1*/, int pl /*$a2*/);
typedef struct MVERTEX SV5x5[5][5];
typedef struct PEDESTRIAN *LPPEDESTRIAN;
typedef struct SEATED_PEDESTRIANS *SEATEDPTR;
typedef struct PEDESTRIAN_ROADS *LPPEDESTRIAN_ROADS;
typedef struct POLY_G4 POLY_G4;
typedef struct TILE TILE;
typedef struct DR_TPAGE DR_TPAGE;
typedef struct CAR_POLY CAR_POLY;
typedef struct COLOUR_BAND COLOUR_BAND;
typedef struct _PERCENTAGE_BAR PERCENTAGE_BAR;
typedef struct _PERCENTAGE_BAR *LPPERCENTAGE_BAR;
typedef struct POLY_F3 POLY_F3;
typedef struct POLY_F4 POLY_F4;
typedef struct POLY_FT3 POLY_FT3;
typedef struct POLY_FT4 POLY_FT4;
typedef struct POLY_G3 POLY_G3;
typedef struct LINE_F2 LINE_F2;
typedef struct LINE_G2 LINE_G2;
typedef struct LINE_F4 LINE_F4;
typedef struct TILE_1 TILE_1;
typedef struct DR_AREA DR_AREA;
typedef struct COP_SIGHT_DATA COP_SIGHT_DATA;
typedef struct MAPTEX MAPTEX;
typedef struct OVERMAP OVERMAP;
typedef struct REPLAY_PARAMETER_BLOCK REPLAY_PARAMETER_BLOCK;
typedef struct REPLAY_SAVE_HEADER REPLAY_SAVE_HEADER;
typedef struct REPLAY_STREAM_HEADER REPLAY_STREAM_HEADER;
typedef struct REPLAY_STREAM REPLAY_STREAM;
typedef struct _PING_PACKET PING_PACKET;
typedef struct ROADBLOCK ROADBLOCK;
typedef struct TestResult TestResult;
typedef struct BUILDING_BOX BUILDING_BOX;
typedef struct CDATA2D CDATA2D;
typedef struct CRET2D CRET2D;
typedef struct __tunnelcoords tunnelcoords;
typedef struct _ExOBJECT EXOBJECT;
typedef struct BOMB BOMB;
typedef struct COLLISION_PACKET COLLISION_PACKET;
typedef struct _PLAYER PLAYER;
typedef struct XZPAIR XZPAIR;
typedef struct CELL_DATA CELL_DATA;
typedef struct PACKED_CELL_OBJECT PACKED_CELL_OBJECT;
typedef struct PAD PAD;
typedef struct CELL_ITERATOR CELL_ITERATOR;
typedef struct POLY_GT3 POLY_GT3;
typedef struct POLYFT4LIT POLYFT4LIT;
typedef struct TEX_INFO TEX_INFO;
typedef struct TEXTURE_LOOKUP TEXTURE_LOOKUP;
typedef struct CAR_MODEL CAR_MODEL;
typedef struct plotCarGlobals plotCarGlobals;
typedef unsigned char DAMAGEZONEVERTS[5][6][50];
typedef unsigned char HDDAMAGEZONEPOLYS[5][6][70];
typedef char HDDAMAGELEVELS[5][255];
typedef struct _EXTRA_CIV_DATA EXTRA_CIV_DATA;
typedef struct COP_DATA COP_DATA;
typedef struct FELONY_DATA FELONY_DATA;
typedef enum AIZone AIZone;
typedef struct iVectNT iVectNT;
typedef struct PLAYBACKCAMERA PLAYBACKCAMERA;
typedef struct CUTSCENE_BUFFER CUTSCENE_BUFFER;
typedef struct CUTSCENE_INFO CUTSCENE_INFO;
typedef struct CUTSCENE_HEADER CUTSCENE_HEADER;
typedef struct POLY_GT4 POLY_GT4;
typedef struct POLYFT4 POLYFT4;
typedef struct TPAN TPAN;
typedef struct SMOKE SMOKE;
typedef struct DEBRIS DEBRIS;
typedef struct LEAF LEAF;
typedef struct DAMAGED_LAMP DAMAGED_LAMP;
typedef struct DAMAGED_OBJECT DAMAGED_OBJECT;
typedef struct TRI_POINT TRI_POINT;
typedef struct TRI_POINT_LONG TRI_POINT_LONG;
typedef struct RAIN_TYPE RAIN_TYPE;
typedef struct LAMP_STREAK LAMP_STREAK;
typedef struct ROUTE_DATA ROUTE_DATA;
typedef struct DENTUVS DENTUVS;
typedef struct HUBCAP HUBCAP;
typedef struct SPRT SPRT;
typedef struct REPLAY_ICON REPLAY_ICON;
typedef struct _pct plotContext;
typedef struct MATRIX2 MATRIX2;
typedef struct Spool Spool;
typedef struct PL_POLYFT4 PL_POLYFT4;
typedef unsigned int u32;
typedef struct MVERTEX MVERTEX;
typedef struct VERTEX VERTEX;
typedef struct TRAILBLAZER_DATA TRAILBLAZER_DATA;
typedef struct SMASHED_CONE SMASHED_CONE;
typedef struct POLYCOORD POLYCOORD;
typedef struct MULTICAR_DATA MULTICAR_DATA;
typedef struct RENDER_ARG RENDER_ARG;
typedef struct RENDER_ARGS RENDER_ARGS;
typedef struct __envsound envsound;
typedef struct __envsoundtags envsoundtags;
typedef struct __envsoundinfo envsoundinfo;
typedef struct SPEECH_QUEUE SPEECH_QUEUE;
typedef struct __othercarsound othercarsound;
typedef struct __tunnelinfo tunnelinfo;
typedef struct __bitfield64 bitfield64;
typedef struct XMCHANNEL XMCHANNEL;
typedef struct GEAR_DESC GEAR_DESC;
//typedef void *va_list;
typedef struct PSXSCREEN PSXSCREEN;
typedef enum GAMEMODE GAMEMODE;
typedef struct MISSION_STEP MISSION_STEP;
typedef struct BOUND_BOX BOUND_BOX;
typedef struct _HANDLING_TYPE HANDLING_TYPE;
typedef struct CHEATS CHEATS;
typedef struct BOXINFO BOXINFO;
typedef struct MAP_DATA MAP_DATA;
typedef struct GAME_SAVE_HEADER GAME_SAVE_HEADER;
typedef struct CONFIG_SAVE_HEADER CONFIG_SAVE_HEADER;
typedef enum GAMETYPE GAMETYPE;
typedef struct OUT_CELL_FILE_HEADER OUT_CELL_FILE_HEADER;
typedef enum EXIT_VALUE EXIT_VALUE;
typedef struct MENU_HEADER MENU_HEADER;
typedef struct MENU_ITEM MENU_ITEM;
typedef struct XYWH XYWH;
typedef struct AREA_LOAD_INFO AREA_LOAD_INFO;
typedef struct ROAD_MAP_LUMP_DATA ROAD_MAP_LUMP_DATA;
typedef struct __io io;
typedef struct __xa_request xa_request;
typedef struct _MISSION MS_MISSION;
typedef struct MissionTrain MissionTrain;
typedef struct FixedEvent FixedEvent;
typedef struct Helicopter Helicopter;
typedef struct _ROUTE_INFO MS_ROUTE_INFO;
typedef struct MR_MISSION MR_MISSION;
typedef struct STOPCOPS STOPCOPS;
typedef enum FAIL_REASON FAIL_REASON;
typedef struct MR_THREAD MR_THREAD;
typedef struct POLYFT3 POLYFT3;
typedef struct BONE BONE;
typedef enum LIMBS LIMBS;
typedef enum TEXTURE_PALS TEXTURE_PALS;
typedef struct PED_DATA PED_DATA;
typedef struct tRay tRay;
typedef struct tRange tRange;
typedef struct tAABB tAABB;
typedef struct PADRAW PADRAW;
typedef struct DUPLICATION DUPLICATION;
typedef struct tNode tNode;
typedef short int16;
typedef long int32;
typedef struct PLAYER_SCORE PLAYER_SCORE;
typedef struct SEATED_PEDESTRIANS SEATED_PEDESTRIANS;
typedef struct CAR_COLLISION_BOX CAR_COLLISION_BOX;
typedef struct PEDESTRIAN_ROADS PEDESTRIAN_ROADS;
typedef struct OUT_FONTINFO OUT_FONTINFO;
typedef struct FONT_DIGIT FONT_DIGIT;
typedef struct TEXINF TEXINF;
typedef struct SHADOWHDR SHADOWHDR;
typedef struct TYRE_TRACK TYRE_TRACK;
typedef struct S_XYZ S_XYZ;
typedef struct DR_MOVE DR_MOVE;
typedef struct FLAREREC FLAREREC;
typedef struct SpuReverbAttr SpuReverbAttr;
typedef struct SpuCommonAttr SpuCommonAttr;
typedef struct __LSBDinfo LSBDinfo;
typedef struct CHANNEL_DATA CHANNEL_DATA;
typedef struct SAMPLE_DATA SAMPLE_DATA;
typedef struct __pauseinfo pauseinfo;
typedef struct SPOOLQ SPOOLQ;
typedef struct SPL_REGIONINFO SPL_REGIONINFO;
typedef struct AreaDataStr AreaDataStr;
typedef struct CdlFILE CdlFILE;
typedef struct DRAW_MODE DRAW_MODE;
typedef enum CDTYPE CDTYPE;
typedef enum CITYTYPE CITYTYPE;
typedef struct TARGET_ARROW_MODEL TARGET_ARROW_MODEL;
typedef struct TP TP;
typedef struct CAR_LOCALS CAR_LOCALS;
typedef struct CdlFILTER CdlFILTER;
typedef struct XA_TRACK XA_TRACK;
typedef struct XM_HeaderInfo XM_HeaderInfo;
typedef struct XM_VABInfo XM_VABInfo;
typedef struct XM_Feedback XM_Feedback;
typedef struct XMHEADER XMHEADER;
typedef struct XMSONG XMSONG;
typedef struct FE_CHARDATA FE_CHARDATA;
typedef struct FE_FONT FE_FONT;
typedef struct SCREEN_LIMITS SCREEN_LIMITS;
typedef struct BOTCH BOTCH;
typedef struct FILEFORMAT FILEFORMAT;
typedef struct SLICE SLICE;
typedef struct TCB TCB;
typedef struct EXEC EXEC;
typedef struct DIRENTRY DIRENTRY;
typedef struct MouseData MouseData;
typedef struct NegconData NegconData;
typedef struct AnalogjoyData AnalogjoyData;
typedef struct TapCtrllerData TapCtrllerData;
typedef struct MultiTapData MultiTapData;
typedef struct _CARD _CARD;
typedef struct TIMSTRUCT TIMSTRUCT;
typedef struct FONTTABSTRUCT FONTTABSTRUCT;
typedef struct KANJILOOKUP KANJILOOKUP;
typedef struct SLICEHEADER SLICEHEADER;
typedef struct BLOCKINFO BLOCKINFO;
typedef struct CARDINFO CARDINFO;
typedef struct MCSLOT MCSLOT;
typedef unsigned short PadData;
typedef struct POINT POINT;
typedef struct DISPMAN DISPMAN;
typedef struct ControllerPacket ControllerPacket;

/* 3219 labels
0xA9FF0 __SN_GP_BASE
0xA9FF0 __data_objend
0xA9FF0 __data_orgend
0xA9FF0 __sdata_obj
0xA9FF0 __sdata_org
0x10000 _text_obj
0x10000 _text_org
0x10000 __rdata_obj
0x10000 __rdata_org
0xAAA88 _text_objend
0xAAA88 _text_orgend
0xAAA88 _bss_obj
0xAAA88 _bss_org
0xAAA88 __sdata_objend
0xAAA88 __sdata_orgend
0xAAA88 __ctors_obj
0xAAA88 __ctors_objend
0xAAA88 __ctors_org
0xAAA88 __ctors_orgend
0xAAA88 __dtors_obj
0xAAA88 __dtors_objend
0xAAA88 __dtors_org
0xAAA88 __dtors_orgend
0xAAA88 __sbss_obj
0xAAA88 __sbss_org
0xAAA88 NumDriver2Curves
0x9AA88 _text_size
0x9AA88 __subsf3
0xE6380 _bss_objend
0xE6380 _bss_orgend
0xE6380 __bss_objend
0xE6380 __bss_orgend
0x3B8F8 _bss_size
0x1C0000 _frnt_obj
0x1C0000 _frnt_org
0x1C0000 _frnt_rdata_obj
0x1C0000 _frnt_rdata_org
0x1CC5D8 _frnt_objend
0x1CC5D8 _frnt_orgend
0x1CC5D8 _frnt_bss_objend
0x1CC5D8 _frnt_bss_orgend
0x1CC5D8 _frnt_ctors_obj
0x1CC5D8 _frnt_ctors_objend
0x1CC5D8 _frnt_ctors_org
0x1CC5D8 _frnt_ctors_orgend
0x1CC5D8 _frnt_dtors_obj
0x1CC5D8 _frnt_dtors_objend
0x1CC5D8 _frnt_dtors_org
0x1CC5D8 _frnt_dtors_orgend
0xC5D8 _frnt_size
0xE7000 _lead_obj
0xE7000 _lead_org
0xE7000 _path_obj
0xE7000 _path_org
0xE7000 _lead_rdata_obj
0xE7000 _lead_rdata_org
0xE7000 _path_rdata_obj
0xE7000 _path_rdata_objend
0xE7000 _path_rdata_org
0xE7000 _path_rdata_orgend
0xE7000 _path_text_obj
0xE7000 _path_text_org
0xE7000 popNode
0xECED0 _lead_objend
0xECED0 _lead_orgend
0xECED0 _lead_bss_objend
0xECED0 _lead_bss_orgend
0xECED0 _lead_ctors_obj
0xECED0 _lead_ctors_objend
0xECED0 _lead_ctors_org
0xECED0 _lead_ctors_orgend
0xECED0 _lead_dtors_obj
0xECED0 _lead_dtors_objend
0xECED0 _lead_dtors_org
0xECED0 _lead_dtors_orgend
0x5ED0 _lead_size
0xF27C8 _path_objend
0xF27C8 _path_orgend
0xF27C8 _path_bss_objend
0xF27C8 _path_bss_orgend
0xF27C8 _path_ctors_obj
0xF27C8 _path_ctors_objend
0xF27C8 _path_ctors_org
0xF27C8 _path_ctors_orgend
0xF27C8 _path_dtors_obj
0xF27C8 _path_dtors_objend
0xF27C8 _path_dtors_org
0xF27C8 _path_dtors_orgend
0xB7C8 _path_size
0xF3000 _mcard_obj
0xF3000 _mcard_org
0xF3000 _mcard_rdata_obj
0xF3000 _mcard_rdata_org
0x10F288 _mcard_objend
0x10F288 _mcard_orgend
0x10F288 _mcard_bss_objend
0x10F288 _mcard_bss_orgend
0x10F288 _mcard_ctors_obj
0x10F288 _mcard_ctors_objend
0x10F288 _mcard_ctors_org
0x10F288 _mcard_ctors_orgend
0x10F288 _mcard_dtors_obj
0x10F288 _mcard_dtors_objend
0x10F288 _mcard_dtors_org
0x10F288 _mcard_dtors_orgend
0x1C288 _mcard_size
0x12D80 __rdata_objend
0x12D80 __rdata_orgend
0x12D80 __text_obj
0x12D80 __text_org
0x12D80 sdSelfModifyingCode
0x2D80 __rdata_size
0x9B388 __text_objend
0x9B388 __text_orgend
0x9B388 __data_obj
0x9B388 __data_org
0x9B388 sea							+
0x88608 __text_size
0xEC68 __data_size
0xA98 __sdata_size
0x0 __ctors_size
0x0 __dtors_size
0x0 _lead_sdata_size
0x0 _lead_sbss_size
0x0 _lead_ctors_size
0x0 _lead_dtors_size
0x0 _path_rdata_size
0x0 _path_sdata_size
0x0 _path_sbss_size
0x0 _path_ctors_size
0x0 _path_dtors_size
0x0 _frnt_sdata_size
0x0 _frnt_sbss_size
0x0 _frnt_ctors_size
0x0 _frnt_dtors_size
0x0 _mcard_sdata_size
0x0 _mcard_sbss_size
0x0 _mcard_ctors_size
0x0 _mcard_dtors_size
0xAB418 __sbss_objend
0xAB418 __sbss_orgend
0xAB418 __bss_obj
0xAB418 __bss_org
0xAB418 cyclecluts
0x990 __sbss_size
0x3AF68 __bss_size
0xE70A0 _lead_rdata_objend
0xE70A0 _lead_rdata_orgend
0xE70A0 _lead_text_obj
0xE70A0 _lead_text_org
0xE70A0 leadRand
0xA0 _lead_rdata_size
0xECBE8 _lead_text_objend
0xECBE8 _lead_text_orgend
0xECBE8 _lead_data_obj
0xECBE8 _lead_data_org
0xECBE8 pathParams
0x5B48 _lead_text_size
0xECC0C _lead_data_objend
0xECC0C _lead_data_orgend
0xECC0C _lead_sdata_obj
0xECC0C _lead_sdata_objend
0xECC0C _lead_sdata_org
0xECC0C _lead_sdata_orgend
0xECC0C _lead_sbss_obj
0xECC0C _lead_sbss_objend
0xECC0C _lead_sbss_org
0xECC0C _lead_sbss_orgend
0x24 _lead_data_size
0xECC10 _lead_bss_obj
0xECC10 _lead_bss_org
0xECC10 d.21
0x2C0 _lead_bss_size
0xE9108 _path_text_objend
0xE9108 _path_text_orgend
0xE9108 _path_data_obj
0xE9108 _path_data_org
0xE9108 ends
0x2108 _path_text_size
0xE91A4 _path_data_objend
0xE91A4 _path_data_orgend
0xE91A4 _path_sdata_obj
0xE91A4 _path_sdata_objend
0xE91A4 _path_sdata_org
0xE91A4 _path_sdata_orgend
0xE91A4 _path_sbss_obj
0xE91A4 _path_sbss_objend
0xE91A4 _path_sbss_org
0xE91A4 _path_sbss_orgend
0x9C _path_data_size
0xE91A8 _path_bss_obj
0xE91A8 _path_bss_org
0xE91A8 omap
0x9620 _path_bss_size
0x1C096C _frnt_rdata_objend
0x1C096C _frnt_rdata_orgend
0x1C096C _frnt_text_obj
0x1C096C _frnt_text_org
0x1C096C SetVariable
0x96C _frnt_rdata_size
0x1C6764 _frnt_text_objend
0x1C6764 _frnt_text_orgend
0x1C6764 _frnt_data_obj
0x1C6764 _frnt_data_org
0x1C6764 carSelectPlayerText
0x5DF8 _frnt_text_size
0x1C6D04 _frnt_data_objend
0x1C6D04 _frnt_data_orgend
0x1C6D04 _frnt_sdata_obj
0x1C6D04 _frnt_sdata_objend
0x1C6D04 _frnt_sdata_org
0x1C6D04 _frnt_sdata_orgend
0x1C6D04 _frnt_sbss_obj
0x1C6D04 _frnt_sbss_objend
0x1C6D04 _frnt_sbss_org
0x1C6D04 _frnt_sbss_orgend
0x5A0 _frnt_data_size
0x1C6D08 _frnt_bss_obj
0x1C6D08 _frnt_bss_org
0x1C6D08 result.42
0x58D0 _frnt_bss_size
0xF3644 _mcard_rdata_objend
0xF3644 _mcard_rdata_orgend
0xF3644 _mcard_text_obj
0xF3644 _mcard_text_org
0xF3644 card_start__6MCSLOT
0x644 _mcard_rdata_size
0x10EB40 _mcard_text_objend
0x10EB40 _mcard_text_orgend
0x10EB40 _mcard_data_obj
0x10EB40 _mcard_data_org
0x10EB40 _6MCSLOT.s_init
0x1B4FC _mcard_text_size
0x10EE34 _mcard_data_objend
0x10EE34 _mcard_data_orgend
0x10EE34 _mcard_sdata_obj
0x10EE34 _mcard_sdata_objend
0x10EE34 _mcard_sdata_org
0x10EE34 _mcard_sdata_orgend
0x10EE34 _mcard_sbss_obj
0x10EE34 _mcard_sbss_objend
0x10EE34 _mcard_sbss_org
0x10EE34 _mcard_sbss_orgend
0x2F4 _mcard_data_size
0x10EE38 _mcard_bss_obj
0x10EE38 _mcard_bss_org
0x10EE38 _6MCSLOT.s_copyBlockInfo
0x450 _mcard_bss_size
0x12F5C FindSurfaceD2
0x1313C sdHeightOnPlane
0x13294 RoadInCell
0x134D4 sdGetCell
0x13728 ProcessStraightsDriver2Lump
0x1375C ProcessCurvesDriver2Lump
0x13790 ProcessJunctionsDriver2Lump
0x13834 MapHeight
0x13874 GetSurfaceIndex
0x138B0 sdGetBSP
0x13958 FindRoadInBSP
0x139E8 ColourCycle
0x13D14 InitAnimatingObjects
0x13E60 animate_object
0x1470C animate_garage_door
0x14890 InitSpooledAnimObj
0x14908 DrawAnimatingObject
0x149B8 FindSmashableObjects
0x14A10 int_garage_door
0x14A1C InitCyclingPals
0x14AC0 InitOverlays
0x14CA4 DisplayOverlays
0x14E10 DrawPercentageBar
0x1533C DrawProximityBar
0x1585C DrawDrivingGameOverlays
0x15ED8 SetFullscreenDrawing
0x15F88 InitPercentageBar
0x15FC0 EnablePercentageBar
0x15FD4 SetColourByValue
0x16100 TransparencyOn
0x1617C UpdateFlashValue
0x161EC PrintScoreTableTime
0x162E8 DrawTargetBlip
0x165E0 DrawTargetArrow
0x1687C DrawPlayerDot
0x16B50 ProcessOverlayLump
0x16C74 Long2DDistance
0x16D7C DrawOverheadMap
0x17C98 DrawFullscreenMap
0x18450 DrawCopIndicators
0x18608 DrawMultiplayerMap
0x189E8 FlashOverheadMap
0x18B08 LoadMapTile
0x18C5C draw_box
0x18DBC DrawN
0x18F80 DrawCompass
0x191FC DrawBigCompass
0x1941C CopIndicator
0x195FC DrawSightCone
0x19824 InitOverheadMap
0x19948 InitMultiplayerMap
0x199FC WorldToMultiplayerMap
0x19AC8 SetMapPos
0x19B58 WorldToOverheadMapPositions
0x19D74 SetFullscreenMapMatrix
0x19E50 WorldToFullscreenMap
0x19EE4 WorldToFullscreenMap2
0x19FAC ProcessPalletLump
0x1A0FC load_civ_palettes
0x1A104 InitPadRecording
0x1A29C SaveReplayToBuffer
0x1A800 LoadReplayFromBuffer
0x1ADB8 cjpRecord
0x1AF9C valid_region
0x1B064 cjpPlay
0x1B0F8 GetPingInfo
0x1B180 LoadAttractReplay
0x1B1E4 AllocateReplayStream
0x1B258 Get
0x1B2E8 Put
0x1B3CC RecordWaypoint
0x1B49C UnpackRNC
0x1B4F0 Unpack
0x1BAF0 InitTextureNames
0x1BAF8 TannerStuckInCar
0x1BC20 StoreGameFlags
0x1BC50 TannerCanEnterCar
0x1BD3C SetCameraVector
0x1BD64 Apply_Inv_CameraMatrix
0x1BD98 FrustrumCheck16
0x1BE54 FrustrumCheck
0x1BF4C Asm_PlotSprite
0x1C1C8 PointFaceCheck
0x1C3E8 CarCarCollision3
0x1C470 collided3d
0x1C584 bcollided2d
0x1C928 bFindCollisionPoint
0x1CC98 bFindCollisionTime
0x1CF54 ApplyDamage
0x1D118 DamageCar3D
0x1D4BC DamageCar
0x1D6F4 CarBuildingCollision
0x1E450 HandleThrownBombs
0x1E878 DrawThrownBombs
0x1EA68 BombThePlayerToHellAndBack
0x1ECC0 BombCollisionCheck
0x1ED80 ExplosionCollisionCheck
0x1F55C AddFlash
0x1F5D8 InitThrownBombs
0x1F65C InitCamera
0x1FA88 ModifyCamera
0x1FC80 CameraCollisionCheck
0x200A4 PlaceCameraFollowCar
0x20574 PlaceCameraInCar
0x2096C PlaceCameraAtLocation
0x20A78 TurnHead
0x20B70 PointAtTarget
0x20C28 OK_To_Zoom
0x20CD8 SetBasePos
0x20CFC plotNewCarModel
0x20F08 plotCarPolyGT3
0x21120 DrawCar
0x21B60 DrawCarWheels
0x221E8 DrawWheelObject
0x224C0 ComputeCarLightingLevels
0x228C8 buildNewCars
0x229C8 buildNewCarFromModel
0x23130 MangleWheelModels
0x233F8 GetCarPalIndex
0x23444 DrawCarObject
0x23544 PlayerCarFX
0x23660 setupLightingMatrices
0x237B8 restoreLightingMatrices
0x23820 plotCarPolyB3
0x2392C plotCarPolyFT3
0x23A88 plotCarPolyGT3nolight
0x23C14 GetFirstPackedCop
0x23E28 ClearCopUsage
0x23E50 InitCar
0x24090 GetNextRoadInfo
0x269CC InitNodeList
0x26D14 GetNodePos
0x26F88 CheckChangeLanes
0x27598 CreateNewNode
0x28140 InitCivState
0x28350 PingOutAllSpecialCivCars
0x28474 PingOutAllCivCarsAndCopCars
0x285BC CheckPingOut
0x28748 CreateCivCarWotDrivesABitThenStops
0x289C8 CreateStationaryCivCar
0x28E1C PingInCivCar
0x2A52C AttemptUnPark
0x2A664 CivAccelTrafficRules
0x2AC10 SetUpCivCollFlags
0x2B2D4 CivAccel
0x2B5A4 CivSteerAngle
0x2B94C CivFindStation
0x2BB54 CivFindPointOnPath
0x2BD5C CreateRoadblock
0x2CE0C InitCivCars
0x2CE78 CivControl
0x2CF80 TrafficLightCycle
0x2CFE8 PingOutCar
0x2D0EC CivCarFX
0x2D184 FindClosestCar
0x2D288 SetUpTrafficLightPhase
0x2D2B4 NotTravellingAlongCurve
0x2D300 decomp_asm
0x2D36C BuildWorldMatrix
0x2D460 Calc_Object_MatrixYZX
0x2D4D8 _RotMatrixX
0x2D504 _RotMatrixY
0x2D530 _RotMatrixZ
0x2D55C RotMatrixXYZ
0x2D584 _MatrixRotate
0x2D5C4 InvertMatrix
0x2D630 ScaleCamera
0x2D6E0 Getlong
0x2D710 RandomInit
0x2D78C Random2
0x2D7F4 WibbleDownTheRoad
0x2DA04 InitCops
0x2DB40 ControlCops
0x2DF64 CopControl1
0x2ED40 ControlCopDetection
0x2F434 ControlNumberOfCops
0x2F674 CopControl
0x2F6E8 InitCopState
0x2F764 PassiveCopTasks
0x2F860 InitCopData
0x2F8AC UpdateCopSightData
0x2F944 FindCost
0x2F9FC AddReverseLight
0x2FB54 AddIndicatorLight
0x2FE4C AddBrakeLight
0x301B0 AddCopCarLight
0x305AC AddNightLights
0x30E04 AddSmokingEngine
0x31014 AddFlamingEngine
0x311C8 LoadCosmetics
0x31218 ProcessCosmeticsLump
0x313C8 SetupSpecCosmetics
0x31400 DrawInGameCutscene
0x31550 TriggerChase
0x31754 ReleaseInGameCutscene
0x31A88 TriggerInGameCutsceneSystem
0x31F44 SetNullPlayer
0x31FC8 SetNullPlayerDontKill
0x32048 DestroyPlayer
0x32180 LoadCutsceneToReplayBuffer
0x324A4 LoadCutsceneToBuffer
0x32628 InitInGameCutsceneVariables
0x32694 HandleInGameCutscene
0x327A8 TriggerInGameCutscene
0x328A4 CalcInGameCutsceneSize
0x32930 PreLoadInGameCutscene
0x32950 CutsceneCameraChange
0x32A1C LoadInGameCutscene
0x32A9C FindNextCutChange
0x32B00 LoadCutsceneInformation
0x32BBC FreeCutsceneBuffer
0x32C28 IsCutsceneResident
0x32C70 ShowCutsceneError
0x32C78 PlacePoolForCar
0x335DC AddLeaf
0x33814 InitDebrisNames
0x33C04 InitDebris
0x34010 AddGroundDebris
0x341A0 DrawSmashable_sprites
0x3448C AddSmallStreetLight
0x348C0 AddLightEffect
0x34CD4 PreLampStreak
0x34D84 damage_lamp
0x34E14 damage_object
0x34FCC AddTrafficLight
0x35334 ShowCarlight
0x355C4 ShowLight1
0x357B8 ShowLight
0x36494 ShowGroundLight
0x366F0 RoundShadow
0x36940 ShowFlare
0x36BD4 DisplayWater
0x36E80 DisplaySpark
0x371C0 GetSmokeDrift
0x372B8 Setup_Debris
0x374DC Setup_Smoke
0x379B8 Setup_Sparks
0x37B7C DisplayDebris
0x38070 HandleDebris
0x387E4 DisplaySmoke
0x38D1C add_haze
0x38E70 DrawRainDrops
0x39204 AddRainDrops
0x394D0 DisplaySplashes
0x39828 DisplayLightReflections
0x39ABC AllocateDebris
0x39AF8 AllocateLeaf
0x39B34 AllocateSmoke
0x39B70 find_lamp_streak
0x39BE0 DoLightning
0x39CD0 FindCarLightFade
0x39CF8 InitFXPos
0x39DD0 ReleaseDebris
0x39DF4 ReleaseLeaf
0x39E18 ReleaseRainDrop
0x39E3C ReleaseSmoke
0x39E60 SetupRain
0x39EBC SwirlLeaves
0x3A010 GetDebrisColour
0x3A068 DoWeather
0x3A124 InitThunder
0x3A188 RequestThunder
0x3A1AC DoThunder
0x3A29C MoveSmashable_object
0x3A33C AllocateRainDrop
0x3A378 DentCar
0x3A74C CreateDentableCar
0x3A8DC InitHubcap
0x3A960 LoseHubcap
0x3ABB4 MoveHubcap
0x3AEC8 ProcessDentLump
0x3B228 InitialiseDenting
0x3B258 LoadDenting
0x3B2A8 SetupSpecDenting
0x3B34C EditCamera
0x3B5B0 RecordCamera
0x3B7FC CheckCameraChange
0x3B930 IsMovingCamera
0x3BC10 CameraBar
0x3C218 ShowIcons
0x3C624 ShowReplayMenu
0x3C810 ControlReplay
0x3DEC8 DoAutoDirect
0x3E390 SelectCameraCar
0x3E5A4 InvalidCamera
0x3E804 InitDirectorVariables
0x3E870 DeleteCurrentCamera
0x3E904 setCamera
0x3E9B4 FindNextChange
0x3EA20 FindFreeCamera
0x3EA60 deleteCamera
0x3EAA8 DeleteAllCameras
0x3EB0C ShowReplayOptions
0x3EB58 NoMoreCamerasErrorMessage
0x3EBD4 FirstCamera
0x3EC04 dist
0x3EC74 SetPlaybackCamera
0x3ED2C SetCameraReturnedFromCutscene
0x3EDE4 addSubdivSpriteShadow
0x3EFCC DrawSprites
0x3F658 GetNextPackedCop
0x3F718 DrawMapPSX
0x40280 SetupPlaneColours
0x40470 SetupDrawMapPSX
0x4059C InitFrustrumMatrix
0x40670 ProcessMapLump
0x40840 DrawAllTheCars
0x40AF8 PlotBuildingModelSubdivNxN
0x4125C DrawAllBuildings
0x414A4 RenderModel
0x4164C normalIndex
0x4180C SetFrustrumMatrix
0x41844 Set_Inv_CameraMatrix
0x4187C CalcObjectRotationMatrices
0x41924 PlotMDL_less_than_128
0x41950 UnpackCellObject
0x41A10 Apply_InvCameraMatrixAndSetMatrix
0x41AB8 Apply_InvCameraMatrixSetTrans
0x41B78 Tile1x1
0x41DE4 DrawTILES
0x42118 makeMesh
0x426B8 drawMesh
0x42B54 SubdivNxM
0x42F9C ProcessSubDivisionLump
0x42FA8 TileNxN
0x430F8 ProcessLowDetailTable
0x43174 InitDrivingGames
0x432D4 HandleDrivingGames
0x43944 DrawDrivingGames
0x43A64 CarConeCollision
0x43B50 SetSmashedCone
0x43D48 MoveSmashedCones
0x43E54 DrawSmashedCone
0x43F9C GetConePos
0x4409C DrawCone
0x441D0 DrawSmashedCones
0x442AC FadeInHiresScreen
0x4465C FadeOutHiresScreen
0x44934 SetPleaseWait
0x44AA8 CheckForCorrectDisc
0x44D48 ShowHiresScreens
0x44E08 SetupDefDispEnv
0x44EA8 SetupDefDrawEnv
0x44EF0 Env_MakeColourAddTable
0x44F70 Init_Reflection_Mapping
0x44FC8 AddEnvSounds
0x45B20 GetVisValue
0x45CD0 VisibilityLists
0x46154 InitTrain
0x462C0 SetUpEvents
0x475A0 SetCamera
0x47A44 StepFromToEvent
0x47C3C StepPathEvent
0x48374 StepHelicopter
0x48AC8 StepEvents
0x493CC DrawFerrisWheel
0x496EC DrawRotor
0x49CA0 DrawEvents
0x4A6F0 EventSurface
0x4AAE0 TriggerEvent
0x4B304 SpecialCamera
0x4B664 DetonatorTimer
0x4BB18 MultiCarEvent
0x4BC3C InitEvents
0x4BCB8 EventCollisions
0x4BD94 OffsetTarget
0x4BDD4 MakeEventTrackable
0x4BE08 OnBoat
0x4BE8C BoatOffset
0x4BEC4 SetElTrainRotation
0x4BF20 InitDoor
0x4BFBC InitEventCamera
0x4C07C ResetEventCamera
0x4C10C NextNode
0x4C1C0 GetBridgeRotation
0x4C270 TriggerDoor
0x4C2E8 ScreenShake
0x4C398 NoteFelony
0x4C91C AdjustFelony
0x4CC90 CheckPlayerMiscFelonies
0x4D2E8 InitFelonySystem
0x4D320 CarHitByPlayer
0x4D3CC InitFelonyDelayArray
0x4D408 InitFelonyData
0x4D488 GetCarHeading
0x4D498 GetCarDirectionOfTravel
0x4D4E0 ReInitSystem
0x4D580 PlayFMV
0x4D638 PlayRender
0x4D6F8 ResidentModelsBodge
0x4D7EC LoadLevelSFX
0x4DE98 StartGameSounds
0x4E1F0 GetEngineRevs
0x4E350 ControlCarRevs
0x4E5C8 ControlSpeech
0x4E778 InitDopplerSFX
0x4E7F8 DoDopplerSFX
0x4F508 DoPoliceLoudhailer
0x4F6D0 CollisionSound
0x4F9EC ExplosionSound
0x4FBFC JerichoSpeak
0x4FCF8 SoundTasks
0x5014C InitMusic
0x502E4 Tunnels
0x50468 AddTunnels
0x50C70 AddEnvSnd
0x50E70 IdentifyZone
0x51524 CalcEffPos
0x51838 CalcEffPos2
0x51F74 UpdateEnvSnd
0x521D0 SetEnvSndVol
0x521F8 CopSay
0x522F4 PlaySpeech
0x52354 CarHasSiren
0x523F0 InitEnvSnd
0x524A4 InitTunnels
0x524C8 LoadBankFromLump
0x52578 SpecialVehicleKludge
0x525A8 MapCarIndexToBank
0x52660 DoSpeech
0x526BC InitSpeechQueue
0x526FC BodSay
0x52738 MissionSay
0x52774 jsqrt
0x52828 FunkUpDaBGMTunez
0x528B0 AddTunnel
0x5296C SetEnvSndPos
0x529B0 InitLeadHorn
0x529BC LeadHorn
0x52A90 GameStart
0x52F00 ReInitFrontend
0x53050 RunMissionLadder
0x53320 LaunchGame
0x53640 GetRandomChase
0x53718 StartRender
0x53740 FindPrevMissionFromLadderPos
0x537A8 FindMissionLadderPos
0x53884 InitCarPhysics
0x53A50 TempBuildHandlingMatrix
0x53B70 UpdateCarPoints
0x53C68 GlobalTimeStep
0x55254 SetShadowPoints
0x55434 LongQuaternion2Matrix
0x55558 initOBox
0x55748 CheckCarToCarCollisions
0x55B04 ProcessCarPad
0x56314 TerminateSkidding
0x563B8 CheckCarEffects
0x56940 jump_debris
0x56A74 StepCarPhysics
0x56AD4 InitialiseCarHandling
0x56ADC nose_down
0x56B4C RebuildCarMatrix
0x56C8C FixCarCos
0x56D20 InitSkidding
0x56D54 GetPlayerId
0x56DBC AddExplosion
0x56EAC HandleExplosion
0x57028 initExplosion
0x57310 DrawExplosion
0x57B74 InitExObjects
0x57BB8 DrawAllExplosions
0x57C58 SaveConfigData
0x57E58 LoadConfigData
0x5803C CalcReplayDataSize
0x5805C SaveReplayData
0x5807C LoadReplayData
0x5809C CalcGameDataSize
0x580A4 SaveGameData
0x58134 LoadGameData
0x581CC CalcConfigDataSize
0x581D4 ShowLoading
0x58314 FadeGameScreen
0x5845C ShowLoadingScreen
0x587FC SetupFadePolys
0x5888C DrawFadePoly
0x58A18 SetupScreenFade
0x58A38 CloseShutters
0x58B70 DisplayMissionTitle
0x58C70 ProcessLumps
0x590B8 LoadGameLevel
0x592A0 InitModelNames
0x59398 GameInit
0x59AAC StepSim
0x5A944 GameLoop
0x5AB90 StepGame
0x5B3EC main
0x5B5B4 UpdatePlayerInformation
0x5B8F0 RenderGame2
0x5BD4C InitGameVariables
0x5BFDC DealWithHorn
0x5C1D4 Havana3DOcclusion
0x5C4C0 DrawGame
0x5C5DC EndGame
0x5C5F8 EnablePause
0x5C638 CheckForPause
0x5C6D0 FadeScreen
0x5C748 RenderGame
0x5C884 ReplayLog_Fnarr_He_Said_Log
0x5C88C CheckUnpackNewRegions
0x5CC68 ControlMap
0x5CDE8 InitMap
0x5D010 PVSDecode
0x5D28C GetPVSRegionCell2
0x5D3D4 InitCellData
0x5D474 FindModelPtrWithName
0x5D52C FindModelIdxWithName
0x5D5C8 PositionVisible
0x5D684 newPositionVisible
0x5D72C ProcessRoadsLump
0x5D734 ProcessJunctionsLump
0x5D73C ProcessRoadBoundsLump
0x5D744 ProcessJuncBoundsLump
0x5D74C GetVisSetAtPosition
0x5D824 NewProcessRoadMapLump
0x5D87C GetMissionSound
0x5D9B8 DoCutsceneSound
0x5DD78 InitializeMissionSound
0x5E088 DoMissionSound
0x5EE68 SilenceThisCar
0x5F194 RequestXA
0x5F21C HandleRequestedXA
0x5F28C InitializeCutsceneSound
0x5F2C4 SetMSoundVar
0x5F2FC AdjustPlayerCarVolume
0x5F364 DrawMission
0x5F5D4 DrawWorldTarget
0x5F8CC DrawMultiplayerTarget
0x5FAF0 DrawTimer
0x5FBE4 DisplayPlayerPosition
0x5FC2C DrawMessage
0x5FCA4 DrawWorldTargets
0x5FCF4 DrawOverheadTargets
0x5FD44 DrawFullscreenTargets
0x5FD94 DrawMultiplayerTargets
0x5FDE4 DrawOverheadTarget
0x5FEFC DrawFullscreenTarget
0x60014 StorePlayerPosition
0x602B0 RestorePlayerPosition
0x60418 StoreCarPosition
0x6054C RestoreCarPosition
0x607A8 StoreEndData
0x6084C RestoreStartData
0x608B4 InitialiseMissionDefaults
0x60ADC LoadMission
0x612DC HandleMission
0x6150C HandleTimer
0x616EC RegisterChaseHit
0x617EC Swap2Cars
0x61CC4 HandleMissionThreads
0x61EA4 MRCommand
0x624D8 MRProcessTarget
0x63790 MRCreateCar
0x63A08 PreProcessTargets
0x63BE0 HandleGameOver
0x63FEC SetMissionComplete
0x64210 ActivateNextFlag
0x642D0 PauseMissionTimer
0x64310 SetMissionMessage
0x643B0 SetPlayerMessage
0x6442C TargetComplete
0x64470 TargetActive
0x644B4 SetConfusedCar
0x64500 MROperator
0x64614 MRFunction
0x6467C MRInitialiseThread
0x64698 MRStartThread
0x646F8 MRStopThread
0x64704 MRCommitThreadGenocide
0x64748 MRJump
0x64794 MRPush
0x647AC MRPop
0x647C8 MRGetParam
0x64834 MRGetVariable
0x64918 MRSetVariable
0x64A4C MRRequestCar
0x64A8C MRHandleCarRequests
0x64AB8 MRCancelCarRequest
0x64ADC Handle321Go
0x64B38 CompleteAllActiveTargets
0x64BA0 SetMissionFailed
0x64C40 SetMissionOver
0x64C8C CalcLapTime
0x64CC8 SetCarToBeStolen
0x64D38 MakePhantomCarEqualPlayerCar
0x64D64 ProcessMDSLump
0x64ED4 ProcessCarModelLump
0x6519C GetCarModel
0x65274 DrawBodySprite
0x659B4 StoreVertexLists
0x65B40 SetupTannerSkeleton
0x65D40 newShowTanner
0x666B0 newRotateBones
0x67020 GetModelVertPtr
0x67134 DrawCiv
0x67938 DrawTanner
0x67DAC DrawCharacter
0x68254 InitTannerShadow
0x683C0 TannerShadow
0x68B94 DoCivHead
0x694A0 DrawObject
0x698DC wjmDraw3
0x69AA0 ProcessMotionLump
0x69B20 SetupPedMotionData
0x69B40 SetSkelModelPointers
0x69BD4 SetupPedestrian
0x69C0C CellEmpty
0x69E84 RaySlabsIntersection
0x6A01C lineClear
0x6A500 CollisionCopList
0x6A6B4 CheckScenaryCollisions
0x6AE24 QuickBuildingCollisionCheck
0x6B288 DoScenaryCollisions
0x6B354 GlobalPositionToCellNumber
0x6B44C CellAtPositionEmpty
0x6B498 SetCopListCell
0x6B4C4 BuildCollisionCopList
0x6B4E8 InitControllers
0x6B610 ReadControllers
0x6B758 MapPad
0x6B948 HandleDualShock
0x6BC2C HandlePadVibration
0x6BE60 CloseControllers
0x6BEA0 SetPadVibration
0x6BF1C StopPadVibration
0x6BF54 StopDualShockMotors
0x6BF5C SetDuplicatePadData
0x6BF8C ClearPad
0x6BFB8 ShowPauseMenu
0x6C314 InitaliseMenu
0x6C720 SetupMenu
0x6C85C DrawVisibleMenus
0x6CC50 ControlMenu
0x6D0AC EnterScoreName
0x6D38C CreateScoreNames
0x6D6FC DrawHighScoreMenu
0x6DA18 SaveReplay
0x6DA3C SaveGame
0x6DA60 EnterName
0x6DA80 MaxMenuStringLength
0x6DB38 PauseMap
0x6DB9C SfxVolume
0x6DC6C MusicVolume
0x6DD3C DrawPauseMenus
0x6DD9C IHaveThePower
0x6DFBC ProcessTannerPad
0x6E470 InitTanner
0x6E62C InitPedestrians
0x6E72C ActivatePlayerPedestrian
0x6ECF0 PlaceRoadBlockCops
0x6F074 CreatePedAtLocation
0x6F1D4 ControlPedestrians
0x6F344 PedDoNothing
0x6F614 PedUserRunner
0x6F874 SetupGetOutCar
0x6FAA4 SetupGetInCar
0x6FD70 TannerCameraHandler
0x6FFB0 TannerSitDown
0x70138 AnimatePed
0x704E4 PingInPedestrians
0x708E0 FindPointOfCollision
0x70B04 TannerCarCollisionCheck
0x710BC SetupCivJump
0x7138C CivPedWalk
0x71664 CorrectPathPosition
0x71670 CalcPedestrianDirection
0x71814 FindTannerASeat
0x71930 add_seated
0x71AC4 set_coll_box
0x71BE4 BuildCarCollisionBox
0x71E74 CalculatePedestrianInterest
0x71FBC DestroyPedestrians
0x7201C DestroyPedestrian
0x72114 CreatePedestrian
0x72184 HandlePedestrians
0x721D4 DeActivatePlayerPedestrian
0x722F8 DrawAllPedestrians
0x72498 TannerActionHappening
0x724E0 SetTannerPosition
0x72568 SetPedestrianTurn
0x725EC PedSurfaceType
0x72620 IsPavement
0x726AC FindSeated
0x727A0 CheckForCar
0x728A4 PedestrianActionInit_WalkToTarget
0x72930 SetupTannerSitDown
0x7296C SetupPressButton
0x729AC PedUserWalker
0x72A78 PedCarryOutAnimation
0x72BC4 PedGetInCar
0x72C54 PedGetOutCar
0x72CF8 PedPressButton
0x72D48 CivPedDoNothing
0x72D50 CivPedSit
0x72D58 CivPedJump
0x72E08 CopStand
0x72E64 CivGetIn
0x72F4C TannerCollision
0x73038 DestroyCivPedestrians
0x730A0 SetupDoNowt
0x730E4 SetupWalker
0x73120 SetupRunner
0x73164 SetupBack
0x731A4 SetupCivPedRouteData
0x73260 PingOutPed
0x732D8 SetupCivPedWalk
0x73328 CheckForPlayerCar
0x73390 ProcessChairLump
0x7339C ChangeCarPlayerToPed
0x73574 ChangePedPlayerToCar
0x73900 UpdatePlayers
0x73A40 InitPlayer
0x73C74 RequestSlightPauseBeforeCarSoundStarts
0x73CBC HaveCarSoundStraightAway
0x73CF4 MakeTheCarShutUp
0x73D30 LoadFont
0x73F08 PrintString
0x741A8 PrintDigit
0x743CC PrintStringBoxed
0x74644 PrintScaledString
0x748C0 DrawButton
0x74A78 SetTextColour
0x74A8C StringWidth
0x74B18 OutputString
0x74BF4 PrintStringRightAligned
0x74C40 PrintStringCentred
0x74C90 StoreClut2
0x74CCC SetCLUT16Flags
0x74D9C PrintStringFeature
0x74DBC GetNextWord
0x74DFC SetFontTPage
0x74EBC InitButtonTextures
0x74F1C ROADS_GetRouteData
0x74F28 InitialiseScoreTables
0x750A4 OnScoreTable
0x75260 AddScoreToTable
0x752D4 CheckGetawayPlacing
0x75324 CheckTrailblazerPlacing
0x753A0 CheckCheckpointPlacing
0x753F0 CheckSurvivalPlacing
0x75440 ResetTable
0x75470 GetTyreTrackPositions
0x755A8 AddTyreTrack
0x75A48 DrawTyreTracks
0x75F9C InitShadow
0x76170 SubdivShadow
0x76734 PlaceShadowForCar
0x76AA8 clipAgainstZ
0x76D3C clippedPoly
0x771A0 sQuad
0x7758C InitTyreTracks
0x775C0 SetTyreTrackOldPositions
0x77630 LoadSky
0x779C4 DrawSkyDome
0x77AF4 DrawLensFlare
0x78124 DisplaySun
0x785AC DisplayMoon
0x78818 TunnelSkyFade
0x789CC calc_sky_brightness
0x78B80 PlotSkyPoly
0x78F2C PlotHorizonMDL
0x7914C InitSound
0x7923C ClearChannelFields
0x792B8 ResetSound
0x79398 CompleteSoundSetup
0x7956C SetChannelPitch
0x7962C ComputeDoppler
0x7979C PauseXM
0x797FC PauseSFX
0x799C0 UnPauseXM
0x79A18 UnPauseSFX
0x79BA0 SoundHandler
0x79C34 LoadSoundBankDynamic
0x79E6C GetFreeChannel
0x79FA0 UpdateVolumeAttributesS
0x7A3C8 CalculateVolume
0x7A59C FESound
0x7A728 SetReverbState
0x7A76C SetReverbInGameState
0x7A7C4 SetReverbChannelState
0x7A818 SetMasterVolume
0x7A860 StartSound
0x7A8FC Start3DSoundVolPitch
0x7A9FC Start3DTrackingSound
0x7AAE0 SetChannelVolume
0x7ABA4 AllocateReverb
0x7AC10 SetPlayerOwnsChannel
0x7AC34 SetChannelPosition3
0x7AD40 PauseSound
0x7AD78 UnPauseSound
0x7ADA8 StopChannel
0x7AE5C StopAllChannels
0x7AE9C LockChannel
0x7AECC UnlockChannel
0x7AEF8 LoadSoundBank
0x7AFEC FreeXM
0x7B038 StartXM
0x7B0B8 StopXM
0x7B0DC SetXMVolume
0x7B12C UpdateVolumeAttributesM
0x7B1E0 VsyncProc
0x7B22C UpdateXMSamples
0x7B290 test_changemode
0x7B42C check_regions_present
0x7B72C UpdateSpool
0x7B8F4 SendTPage
0x7BB7C LoadInAreaTSets
0x7BDEC SendSBK
0x7BF24 init_spooled_models
0x7C0F4 CheckLoadAreaData
0x7C2F4 LoadRegionData
0x7C4CC ProcessSpoolInfoLump
0x7C628 unpack_cellpointers
0x7C7B4 SpecClutsSpooled
0x7CA20 CleanModelSpooled
0x7CB64 DamagedModelSpooled
0x7CC8C LowModelSpooled
0x7CDCC CleanSpooled
0x7CF74 Tada
0x7D1AC SpecialStartNextBlock
0x7D548 CheckSpecialSpool
0x7D740 InitSpecSpool
0x7D9E0 Unpack_CellPtrs
0x7DA34 GotRegion
0x7DAC8 data_cb_misc
0x7DBA0 ready_cb_misc
0x7DC34 data_cb_soundbank
0x7DD0C ready_cb_soundbank
0x7DE10 data_cb_regions
0x7DEF8 ready_cb_regions
0x7DFCC data_cb_textures
0x7E0E0 ready_cb_textures
0x7E210 changemode
0x7E2B4 DrawCDicon
0x7E334 CheckValidSpoolData
0x7E3D4 RequestSpool
0x7E44C ClearRegion
0x7E4FC InitSpooling
0x7E590 SpoolSYNC
0x7E5A8 SetupModels
0x7E5E8 LoadInAreaModels
0x7E644 UnpackRegion
0x7E6D4 WaitCloseLid
0x7E740 FoundError
0x7E78C StartSpooling
0x7E828 LowSpooled
0x7E8B4 QuickSpoolSpecial
0x7E944 PrepareSecretCar
0x7E9C0 stopgame
0x7EA08 startgame
0x7EA38 LoadfileSeg
0x7ED58 SwapDrawBuffers2
0x7EE44 SetupDrawBuffers
0x7EF74 SetupDrawBufferData
0x7F180 SetCityType
0x7F3BC Loadfile
0x7F450 ClearMem
0x7F4E4 setMem8
0x7F58C setMem16
0x7F61C ResetCityType
0x7F630 FileExists
0x7F6A8 DiscSwapped
0x7F764 SwapDrawBuffers
0x7F828 InitaliseDrawEnv
0x7F8B0 Init_FileSystem
0x7F8D8 DoCDRetry
0x7F920 ReportMode
0x7F96C loadsectors
0x7F9EC EnableDisplay
0x7FA58 DisableDisplay
0x7FA78 UpdatePadData
0x7FAAC data_ready
0x7FADC sector_ready
0x7FBAC Draw3DTarget
0x7FDB0 DrawTargetArrowModel
0x80160 DrawStopZone
0x804E4 WorldToCameraPositions
0x80590 IncrementTPageNum
0x80654 Find_TexID
0x806F0 LoadPermanentTPages
0x80C18 GetTextureDetails
0x80E08 GetTextureInfoName
0x80E44 IncrementClutNum
0x80E7C LoadTPageAndCluts
0x80FA4 GetTEXINFName
0x810A0 update_slotinfo
0x810E8 ProcessTextureInfo
0x81180 ReloadIcons
0x811A8 GetTimeStamp
0x811E0 StepOneCar
0x819F4 GetFrictionScalesDriver1
0x81E88 ConvertTorqueToAngularAcceleration
0x81FB8 AddWheelForcesDriver1
0x82C38 StepCars
0x82CCC PlayXA
0x82DC8 GetXAData
0x82E14 PrepareXA
0x82ED0 UnprepareXA
0x82F28 GetMissionXAData
0x82F80 SetXAVolume
0x82FE0 StopXA
0x8302C ResumeXA
0x830E0 PauseXA
0x83158 XAPrepared
0x83164 cbready
0x83218 InitXMData
0x834B4 XM_Init
0x83994 JPlayNote
0x83BCC JPlayEffects
0x83E0C SPE
0x84218 DoEEffects
0x8458C SetPer
0x84740 DoS3MRetrig
0x84958 DoVibrato
0x84A58 DoTremolo
0x84BA4 UpdatePatternData
0x8509C ApplyEffs
0x853DC DoDolbySS
0x854B0 UpdateHardware
0x8580C ProcessEnvelope
0x859DC ProcessPanEnvelope
0x85BAC XM_Restart
0x85CA0 XM_Pause
0x85D80 XM_Exit
0x85DE0 XM_Update
0x85E30 XM_PlayStop
0x85EA0 XM_PlayStart
0x85EF4 XM_SetSongPos
0x85FE4 XM_OnceOffInit
0x8601C XM_CloseVAB
0x86070 XM_SetMasterVol
0x860C4 XM_FreeVAG
0x860E4 UpdateWithTimer
0x861E0 XM_DoFullUpdate
0x8629C XM_Quit
0x862E0 XM_GetFreeVAB
0x86320 XM_SetVAGAddress
0x86358 XM_CloseVAB2
0x863C0 XM_SetSongAddress
0x86404 XM_GetSongSize
0x8640C XM_FreeAllSongIDs
0x86418 XM_SetFileHeaderAddress
0x8644C XM_GetFileHeaderSize
0x86454 GetLogPeriod
0x864EC UpdateXMData
0x865A0 DoVol
0x865C8 DoPan
0x8661C DoVolSlide
0x866AC DoToneSlide
0x86714 DoXMPanSlide
0x867A0 Arpeggio
0x8684C SetInstr
0x86948 SetNote
0x86A28 GetLong
0x86A54 Interpolate
0x86AD4 JPGetPeriod
0x86B08 GetPeriod
0x86B58 GetFreq2
0x86BB0 CurrentKeyStat
0x86C5C StpCh
0x86C80 SetFrq
0x86CA0 SetVol
0x86CCC PlaySFX
0x86D60 ClearSPU
0x86DDC InitSPUChannel
0x86E44 SilenceXM
0x86F24 UpdateEffs
0x86FD8 IntVols
0x87008 GetFreeSongID
0x87058 JPClearSPUFlags
0x8708C CalcPlayPos
0x87144 JCalcPat
0x871B4 PACKEDCalcPlayPos
0x87290 GetEmpty
0x87358 CallMemoryCard
0x8793C libcman_SelectSound
0x87970 libcman_ConfirmSound
0x879A4 libcman_CancelSound
0x879D8 libcman_ErrorSound
0x87A0C libcman_InitControllerLibrary
0x87A5C libcman_DeInitControllerLibrary
0x87A9C libcman_ReadControllers
0x87ACC DoMemoryCard
0x87D4C LoadMemCardOverlay
0x87DD0 StorePermanentTPage
0x87E44 RestorePermanentTPage
0x87EB8 PutCorrectIcon
0x87FB8 __main
0x87FC0 __SN_ENTRY_POINT
0x87FC0 stup2
0x87FE4 stup1
0x88060 stup0
0x8807C CdInit
0x881CC CdPosToInt
0x8824C CdSearchFile
0x89120 CD_sync
0x893A0 CD_ready
0x89668 CD_cw
0x89A74 CD_flush
0x89B48 CD_initvol
0x89C38 CD_init
0x89E18 CD_datasync
0x89F80 CD_set_test_parmnum
0x8A068 CdIntToPos
0x8A178 CdReadyCallback
0x8A198 CdControl
0x8A2D4 CdControlF
0x8A408 CdControlB
0x8A558 CdGetSector
0x8A578 CD_getsector
0x8A678 CdDataCallback
0x8AC08 CdRead
0x8ADA4 CdReadSync
0x8AEA8 CdStatus
0x8AEB8 CdMode
0x8AEC8 CdLastPos
0x8AED8 CdFlush
0x8AEF8 CdReady
0x8AF18 CdSyncCallback
0x8AF38 CdGetSector2
0x8AF58 CD_getsector2
0x8B048 CdDataSync
0x8B068 CdDiskReady
0x8B1A8 CdGetDiskType
0x8B318 CdReadFile
0x8B498 rsin
0x8B4D4 sin_1
0x8B568 rcos
0x8B610 InitGeom
0x8B698 SquareRoot0
0x8B728 MulMatrix0
0x8B838 MulRotMatrix
0x8B928 ApplyRotMatrixLV
0x8BA68 ApplyMatrixSV
0x8BAC8 TransMatrix
0x8BAF8 SetRotMatrix
0x8BB28 SetTransMatrix
0x8BB48 SetGeomOffset
0x8BB68 SetGeomScreen
0x8BB78 RotTransPers
0x8BBA8 RotTrans
0x8BBD8 RotMatrix
0x8BE68 RotMatrixYXZ
0x8C0F8 RotMatrixX
0x8C298 RotMatrixY
0x8C438 RotMatrixZ
0x8C5D8 RotMatrixZYX_gte
0x8C7D8 ratan2
0x8C958 _patch_gte
0x8CA38 ResetGraph
0x8CBAC SetGraphDebug
0x8CC08 DrawSyncCallback
0x8CC68 SetDispMask
0x8CD00 DrawSync
0x8CE84 ClearImage
0x8CF14 ClearImage2
0x8CFAC LoadImage
0x8D00C StoreImage
0x8D06C MoveImage
0x8D124 ClearOTag
0x8D1EC ClearOTagR
0x8D298 DrawPrim
0x8D2F4 DrawOTag
0x8D364 PutDrawEnv
0x8D424 GetDrawEnv
0x8D458 PutDispEnv
0x8D950 GetDispEnv
0x8D984 SetDrawArea
0x8DA04 SetDrawEnv
0x8F2D4 LoadImage2
0x8F3C0 StoreImage2
0x8F4AC _GPU_ResetCallback
0x8F4FC LoadClut
0x8F56C LoadClut2
0x8F5DC SetDefDrawEnv
0x8F69C SetDefDispEnv
0x8F6DC GetTPage
0x8F71C GetClut
0x8F73C SetSemiTrans
0x8F76C SetPolyG3
0x8F78C SetPolyFT4
0x8F7AC SetPolyG4
0x8F7CC SetTile
0x8F7EC SetLineF2
0x8F80C SetLineF4
0x8F82C SetDrawTPage
0x8F85C SetDrawMove
0x8F8BC SetDrawLoad
0x8F92C Krom2Tim
0x8FE2C kanjitrans
0x9035C hankanjitrans
0x9049C InitHeap
0x904AC Exec
0x904BC FlushCache
0x904CC GPU_cw
0x904DC _bu_init
0x904EC DeliverEvent
0x904FC OpenEvent
0x9050C CloseEvent
0x9051C TestEvent
0x9052C EnableEvent
0x9053C DisableEvent
0x9054C EnterCriticalSection
0x9055C ExitCriticalSection
0x9056C SetSp
0x9057C open
0x9058C lseek
0x9059C read
0x905AC write
0x905BC close
0x905CC format
0x905DC nextfile
0x905EC erase
0x905FC Krom2RawAdd
0x9060C GetSp
0x9061C firstfile
0x908BC firstfile2
0x908CC VSync
0x90ADC ChangeClearPAD
0x90AEC ChangeClearRCnt
0x90AFC ResetCallback
0x90B2C InterruptCallback
0x90B5C DMACallback
0x90B8C VSyncCallback
0x90BC0 StopCallback
0x90BF0 CheckCallback
0x90C00 SetIntrMask
0x9114C _96_remove
0x91164 ReturnFromException
0x91174 ResetEntryInt
0x91184 HookEntryInt
0x91194 startIntrVSync
0x912B4 startIntrDMA
0x91554 SetVideoMode
0x91568 GetVideoMode
0x91584 bcopy
0x915C4 bzero
0x915F4 memcmp
0x91634 memcpy
0x91674 memmove
0x916E4 memset
0x91714 rand
0x91744 srand
0x91754 strcat
0x91804 strcmp
0x91874 strcpy
0x918C4 strlen
0x91904 strncmp
0x91984 printf
0x919C4 prnt
0x92064 memchr
0x920B4 _putchar
0x921B0 _putchar_flash
0x921EC sprintf
0x92A6C puts
0x92ACC setjmp
0x92B08 exit
0x92B18 __fixunssfsi
0x92B74 __builtin_delete
0x92B98 free
0x92BA4 SsSetSerialVol
0x92CB4 SpuInit
0x92CD4 _SpuInit
0x92DBC SpuStart
0x92E34 _spu_init
0x93274 _spu_FiDMA
0x93330 _spu_t
0x935B0 _spu_Fw
0x93634 _spu_FsetRXX
0x93678 _spu_FsetRXXa
0x9371C _spu_FsetPCR
0x937C4 _spu_Fw1ts
0x9382C _SpuDataCallback
0x9385C SpuQuit
0x938DC SpuSetMute
0x9393C SpuInitMalloc
0x9399C SpuMalloc
0x93C6C _spu_gcSPU
0x93F6C SpuFree
0x93FEC SpuFlush
0x941EC SpuSetReverb
0x942DC _SpuIsInAllocateArea_
0x9436C SpuSetReverbModeParam
0x9484C _spu_setReverbAttr
0x94D1C SpuReserveReverbWorkArea
0x94D6C SpuSetReverbDepth
0x94DEC SpuSetReverbVoice
0x94E1C _SpuSetAnyVoice
0x950DC SpuGetReverbVoice
0x9510C _SpuGetAnyVoice
0x9513C SpuClearReverbWorkArea
0x952DC WaitEvent
0x952EC SpuSetKey
0x954AC SpuGetKeyStatus
0x9553C SpuWrite
0x9559C SpuSetTransferStartAddr
0x955FC SpuSetTransferMode
0x9562C SpuIsTransferCompleted
0x956DC SpuGetAllKeysStatus
0x95768 SpuSetVoiceVolume
0x957E8 SpuSetVoicePitch
0x95858 SpuSetVoiceAR
0x958D8 SpuSetVoiceRR
0x95958 SpuSetVoiceAttr
0x95F58 _spu_note2pitch
0x96028 SpuGetVoiceVolume
0x96088 SpuGetVoicePitch
0x960A8 SpuSetCommonAttr
0x96428 PadSetAct
0x96468 PadSetActAlign
0x965D8 PadGetState
0x966A8 PadInfoMode
0x967A8 PadStartCom
0x96874 PadStopCom
0x968B8 SysEnqIntRP
0x968C8 SysDeqIntRP
0x968D8 PadInitDirect
0x96988 _padInitDirPort
0x972B8 _dirFailAuto
0x973C8 _padIsVsync
0x97430 _padIntPad
0x975C0 _padInitSioMode
0x979E4 _padSioRW
0x97C08 _padSioRW2
0x97E84 _padClrIntSio0
0x97F14 _padWaitRXready
0x97F3C _padSetCmd
0x97F4C _padSendAtLoadInfo
0x97FD0 _padRecvAtLoadInfo
0x98240 _padGetActSize
0x98278 _padLoadActInfo
0x987EC _padCmdParaMode
0x98894 _padSetRC2wait
0x988B4 _padChkRC2wait
0x99238 _card_info
0x99248 _card_load
0x99258 _card_read
0x99268 _new_card
0x99278 _card_wait
0x99288 _card_clear
0x992C8 _card_write
0x992D8 InitCARD
0x99368 StartCARD
0x993B0 StopCARD
0x993D8 ReadInitPadFlag
0x993E8 InitCARD2
0x993F8 StartCARD2
0x99408 StopCARD2
0x99418 _patch_card_info
0x994F4 _patch_card
0x99588 _patch_card2
0x995F8 _copy_memcard_patch
0x99638 _ExitCard
0x996B8 MemCardInit
0x996E8 __adddf3
0x99A68 _add_mant_d
0x99B18 __addsf3
0x99CC8 _dbl_shift
0x99D88 __divdf3
0x9A068 _comp_mant
0x9A0B8 _dbl_shift_us
0x9A178 __divsf3
0x9A2C8 __extendsfdf2
0x9A428 __fixsfsi
0x9A4D8 __floatsidf
0x9A5F8 __floatsisf
0x9A6C8 __gesf2
0x9A768 __gtsf2
0x9A808 __ltsf2
0x9A8B8 _mainasu
0x9A928 __mulsf3
0x9AA68 __negsf2
0x9AAE8 __truncdfsf2
0x9AC18 _err_math
0x9AC88 sqrt
0x9ADC8 __gtdf2
0x9AEA8 __ltdf2
0x9AF88 __muldf3
0x9B29C _mul_mant_d
0x9B394 Lev0
0x9B3BC Lev1
0x9B3D0 Lev2
0x9B4C0 Lev3
0x9B4D4 Lev_CycleObjPtrs
0x9B4E4 Num_LevCycleObjs
0x9B4F4 Lev0AnimObjects
0x9B584 Lev1AnimObjects
0x9B5D4 Lev2AnimObjects
0x9B624 Lev3AnimObjects
0x9B664 Level_AnimatingObjectPtrs
0x9B674 Level_NumAnimatedObjects
0x9B694 gMissionDoorPosition
0x9B6A4 smashable
0x9B99C felonyColour
0x9B9C0 playerDamageColour
0x9B9E4 damageColour
0x9B9FC overlaidmaps
0x9BA5C MapSegmentPos
0x9BA9C NVertex
0x9BABC north
0x9BADC big_north
0x9BAE4 player_position
0x9BAF4 palletedir
0x9BBC4 AnalogueUnpack
0x9BBD4 date_date
0x9BBD8 date_time
0x9BBDC cd_icon
0x9BE1C CameraPos
0x9BE2C camera_position
0x9BE3C face_camera_work
0x9BE5C specTpages
0x9BE8C carTpages
0x9BEAC day_vectors
0x9BECC night_vectors
0x9BEEC day_colours
0x9BF0C night_colours
0x9BF2C light_matrix
0x9BF4C colour_matrix
0x9BF6C roadblockDelayDiff
0x9BF78 speedLimits
0x9BF7C civPingTest
0x9BFA4 modelRandomList
0x9BFB4 aspect
0x9BFD4 gCopData
0x9C000 speed1
0x9C00C speed2
0x9C018 sqtbl
0x9C05C CosmeticFiles
0x9C074 PoolPrimData
0x9C084 debris_rot_table
0x9C098 debris_colour
0x9C288 debris1_vert
0x9C2AC debris2_vert
0x9C2D0 leaf_vert
0x9C2F4 litter_vert
0x9C318 debris3_vert
0x9C33C debris_data
0x9C350 grassColour
0x9C35C DentingFiles
0x9C36C replay_icons
0x9C4DC menu0
0x9C4E0 menu1
0x9C4EC menu2
0x9C4F4 menu3
0x9C4F8 menu4
0x9C4FC menu5
0x9C504 menu6
0x9C50C tunnel_dim
0x9C5DC texture_pages
0x9C6DC texture_cluts
0x9E6DC polycoords
0x9E724 gPlayerCar0ShinyFaces
0x9E770 ElTrainData
0x9E8BC VegasTrainData
0x9E8D8 VegasParkedTrains
0x9E8E4 HavanaFerryData
0x9E914 RioFerryData
0x9E92C HavanaMiniData
0x9E93C missionTrain
0x9E974 chicagoDoor
0x9E9F8 havanaFixed
0x9EA7C vegasDoor
0x9EB58 rioDoor
0x9EC60 HelicopterData
0x9EC90 LiftingBridges
0x9ED6C ChicagoCameraHack
0x9ED78 HavanaCameraHack
0x9ED9C VegasCameraHack
0x9EDDC RioCameraHack
0x9EE00 initialOccurrenceDelay
0x9EE18 initialReccurrenceDelay
0x9EE30 initialFelonyValue
0x9EE60 UpdateEnvSounds
0x9EFC4 geard
0x9F064 coptrackpos
0x9F084 MissionLadder
0x9F10C RecapFrameLength
0x9F134 feVariableSave
0x9F144 handlingType
0x9F160 src_cosmetics
0xA03D0 theBox
0xA040C Drift
0xA041C SS
0xA043C LevelFiles
0xA044C LevelPalettes
0xA046C LoadingScreenNames
0xA047C missionstarts
0xA04A8 id_map
0xA050C xa_data
0xA05A8 gameNames
0xA06A8 cheatText
0xA06BC CutSceneNames
0xA072C MissionName
0xA07C0 lRoutes
0xA07E8 motion_files
0xA0808 MotionSpeed
0xA0810 MainPed
0xA0924 Skel
0xA0F40 boneIdvals
0xA0F7C High_shake_data
0xA0F94 Med_shake_data
0xA0FA4 Low_shake_data
0xA0FB0 shake_data
0xA0FBC MainPauseItems
0xA1070 MultiplayerPauseItems
0xA10FC CutscenePauseItems
0xA1174 MissionCompleteItems
0xA1214 MissionFailedItems
0xA128C TakeARideFinishedItems
0xA1304 DrivingGameFinishedItems
0xA1390 MultiplayerFinishedItems
0xA13F4 ChaseGameFinishedItems
0xA146C YesNoRestartItems
0xA14A8 YesNoQuitItems
0xA14E4 NoPadItems
0xA14F8 NoMultiPadItems
0xA1520 InvalidPadItems
0xA1534 InvalidMultiPadItems
0xA155C PauseMenuHeader
0xA1570 MultiplayerPauseHeader
0xA1584 CutscenePauseMenuHeader
0xA1598 MissionCompleteHeader
0xA15AC MissionFailedHeader
0xA15C0 TakeARideFinishedHeader
0xA15D4 DrivingGameFinishedHeader
0xA15E8 MultiplayerFinishedHeader
0xA15FC ChaseGameFinishedHeader
0xA1610 NoPadHeader
0xA1624 NoMultiPadHeader
0xA1638 InvalidPadHeader
0xA164C InvalidMultiPadHeader
0xA1660 playerwithcontrol
0xA166C YesNoRestartHeader
0xA1680 YesNoQuitHeader
0xA1694 validchars
0xA16D8 fpPedPersonalityFunctions
0xA1710 tannerLookAngle
0xA1720 force
0xA1730 point
0xA1740 levelstartpos
0xA17C0 PolySizes
0xA18A0 fontDigit
0xA18B8 button_names
0xA18E4 dummy
0xA18F4 frustpos
0xA1904 tempmatrix
0xA1944 sky_y_offset
0xA1954 HorizonLookup
0xA1964 HorizonTextures
0xA198C sun_position
0xA19AC moon_position
0xA19CC moon_shadow_position
0xA19EC flare_info
0xA1A4C tunnelDir
0xA1A64 tunnelPos
0xA1AC4 dummylong
0xA1AD0 pvsSize
0xA1AE0 SpecialByRegion
0xA1C20 draw_mode_pal
0xA1C30 draw_mode_ntsc
0xA1C40 currentfilename
0xA1CC0 targetArrowVerts
0xA1E18 normalTargetArrowTris
0xA1E24 loseTailTargetArrowTris
0xA1E3C windowTargetArrowTris
0xA1E5C maxSpeedTargetArrowTris
0xA1E70 targetArrowModel
0xA1EA0 tpagepos
0xA1EF0 LevelTab
0xA1F88 XANames
0xA1F98 iVABID
0xA1FA8 XMSongIDs
0xA1FD8 XMSPU_SFX
0xA2008 lintab
0xA2608 logtab
0xA26D8 VibratoTable
0xA26F8 fileFormat
0xA284C slice
0xA2868 icon_0
0xA2928 icon_1
0xA29E8 icon_2
0xA2AA8 CD_cbread
0xA2AAC CD_read_dma_mode
0xA2AD0 CD_cbsync
0xA2AD4 CD_cbready
0xA2AD8 CD_debug
0xA2ADC CD_status
0xA2AE0 CD_status1
0xA2AE4 CD_nopen
0xA2AE8 CD_pos
0xA2AEC CD_mode
0xA2AED CD_com
0xA2AF0 DS_active
0xA2AF4 CD_comstr
0xA2B74 CD_intstr
0xA2ED8 rsin_tbl
0xA36F8 SQRT
0xA3878 rcossin_tbl
0xA7878 ratan_tbl
0xA80D4 GPU_printf
0xA80D8 GEnv
0xA8200 _qin
0xA8204 _qout
0xA83A8 Hcount
0xA94D8 Vcount
0xA9558 _ctype_
0xA95E8 _stacksize
0xA95EC _ramsize
0xA95F8 _spu_EVdma
0xA95FC _spu_keystat
0xA9600 _spu_trans_mode
0xA9604 _spu_rev_flag
0xA9608 _spu_rev_reserve_wa
0xA960C _spu_rev_offsetaddr
0xA9610 _spu_rev_attr
0xA9624 _spu_RQvoice
0xA9628 _spu_RQmask
0xA962C _spu_voice_centerNote
0xA965C _spu_env
0xA9660 _spu_isCalled
0xA9670 _spu_RXX
0xA9688 _spu_tsa
0xA968C _spu_transMode
0xA9690 _spu_addrMode
0xA9694 _spu_mem_mode
0xA9698 _spu_mem_mode_plus
0xA969C _spu_mem_mode_unit
0xA96A0 _spu_mem_mode_unitM
0xA96A4 _spu_inTransfer
0xA96A8 _spu_transferCallback
0xA96AC _spu_IRQCallback
0xA96D0 _spu_AllocBlockNum
0xA96D4 _spu_AllocLastNum
0xA96D8 _spu_memList
0xA96E0 _spu_zerobuf
0xA9C00 _spu_rev_startaddr
0xA9C30 _spu_rev_param
0xA9F08 _padFuncNextPort
0xA9F0C _padFuncClrInfo
0xA9F10 _padFuncGetTxd
0xA9F14 _padFuncCurrLimit
0xA9F18 _padFuncPtr2Port
0xA9F1C _padFuncPort2Info
0xA9F20 _padFuncSendAuto
0xA9F24 _padFuncChkEng
0xA9F28 _padFuncRecvAuto
0xA9F2C _padFuncClrCmdNo
0xA9F30 _padFuncIntGun
0xA9F34 _padFuncSetGunPort
0xA9F38 _padFuncGetGunPos
0xA9F3C _padInfoDir
0xA9F40 _padIntExec
0xA9F44 _padGunExec
0xA9F48 _padSioChan
0xA9F4C _padSioState
0xA9F50 _padTotalCurr
0xA9F54 _padModeMtap
0xA9F58 _padChanStart
0xA9F5C _padChanStop
0xA9F60 _padFixResult
0xA9F68 _padVsyncParam
0xA9F78 _padCalledIntPad
0xA9FE8 math_errno
0xA9FEC math_err_point
0xAA068 GuitarType
0xAA0BC gUseRotatedMap
0xAA0C0 map_x_offset
0xAA0C4 map_z_offset
0xAA0C8 x_map
0xAA0CC y_map
0xAA0D0 old_x_mod
0xAA0D4 old_y_mod
0xAA0D8 tilehnum
0xAA0DC tile_size
0xAA0E0 flashtimer
0xAA100 map_x_shift
0xAA104 map_z_shift
0xAA108 ReplaySize
0xAA10C NumReplayStreams
0xAA110 RecordingPads
0xAA114 pad_recorded
0xAA118 gOutOfTape
0xAA124 bodySelect
0xAA128 mScale
0xAA12C ThrownBombDelay
0xAA130 CurrentBomb
0xAA134 fullStrike
0xAA138 halfStrike
0xAA13C gWantFlash
0xAA140 flashval
0xAA144 gBombModel
0xAA148 gBombTargetVehicle
0xAA14C littleBoxRange
0xAA150 minBoxSize
0xAA158 camera_angle
0xAA160 current_camera_angle
0xAA164 gCameraDistance
0xAA168 gCameraMaxDistance
0xAA16C gCameraAngle
0xAA170 inGameCamera
0xAA174 jtest53
0xAA178 headtarget
0xAA17C headposition
0xAA180 trayoffset
0xAA184 gDoBonnets
0xAA188 civ_smoke_enabled
0xAA18C gCurrentResidentSlot
0xAA190 switch_detail_distance
0xAA194 myPalette
0xAA1A0 carDisplayOffset
0xAA1A8 cell_object_index
0xAA1AC useStoredPings
0xAA1B0 testNumPingedOut
0xAA1B4 checkFrames
0xAA1B8 maxSteer
0xAA1BC newAccel
0xAA1C0 roadblockDelay
0xAA1C4 cookieCount
0xAA1C8 hornchanflag
0xAA1CC horncarflag
0xAA1D4 testCrv
0xAA1D8 test23
0xAA1DC PingOutCivsOnly
0xAA1E0 CAR_PAUSE_START
0xAA1E4 testCar
0xAA1E8 makeNextNodeCtrlNode
0xAA1EC closeEncounter
0xAA1F0 sideMul
0xAA1F4 corner
0xAA1F8 sideShift
0xAA1FC carAngle
0xAA200 EVENT_CAR_SPEED
0xAA204 horizonadd
0xAA208 l1
0xAA20C l2
0xAA210 gMinimumCops
0xAA214 gPuppyDogCop
0xAA218 gBatterPlayer
0xAA21C gCopDesiredSpeedScale
0xAA220 gCopMaxPowerScale
0xAA224 pedestrianFelony
0xAA228 gCopRespawnTime
0xAA22C toggleCam
0xAA230 CutsceneReplayStart
0xAA234 CutsceneStreamIndex
0xAA238 NumCutsceneStreams
0xAA23C CutsceneCameraOffset
0xAA240 CutNextChange
0xAA244 CutLastChange
0xAA248 PreLoadedCutscene
0xAA24C gHaveInGameCutscene
0xAA250 gCSDestroyPlayer
0xAA254 CutsceneLength
0xAA258 BlackBorderHeight
0xAA25C CutsceneInReplayBuffer
0xAA260 CutsceneCamera
0xAA264 gInGameChaseActive
0xAA268 gInGameCutsceneActive
0xAA26C CutsceneFrameCnt
0xAA270 CutsceneEventTrigger
0xAA274 gThePlayerCar
0xAA278 gInGameCutsceneDelay
0xAA27C gInGameCutsceneID
0xAA280 JustReturnedFromCutscene
0xAA284 gCutsceneAtEnd
0xAA288 gPlayerCarLights
0xAA28C LightningTimer
0xAA290 variable_weather
0xAA294 gFlareScale
0xAA298 SmokeCnt
0xAA29C gDoSmoke
0xAA2A0 gDoLeaves
0xAA3FC gDoShinyCars
0xAA43C MIN_TRIPOD_CAMERA_HEIGHT
0xAA440 EditMode
0xAA444 SetFastForward
0xAA448 NextChange
0xAA44C ThisChange
0xAA450 LastChange
0xAA454 editing_existing_camera
0xAA458 FastForward
0xAA45C ClearCameras
0xAA460 attract_number
0xAA464 FastForwardCameraCnt
0xAA474 farClip2Player
0xAA478 sprite_shadow
0xAA47C TransparentObject
0xAA480 groundDebrisIndex
0xAA484 lightning
0xAA488 alleycount
0xAA48C treecount
0xAA490 setupYet
0xAA494 visiblelist
0xAA498 tcRoof
0xAA49C tcWall
0xAA4A0 tcRoad
0xAA4A4 goFaster
0xAA4A8 current_smashed_cone
0xAA4AC gTrailblazerPrevConeDelay
0xAA4B0 gTrailblazerData
0xAA4B4 gTrailblazerConeCount
0xAA4B8 gTrailblazerConeIndex
0xAA4C4 gUseCopModel
0xAA4C8 lastrequesteddisc
0xAA518 DistanceTriggerCarMoves
0xAA51C eventHaze
0xAA570 debugRotation
0xAA578 maxrevdrop
0xAA57C maxrevrise
0xAA580 copmusic
0xAA594 gLastChase
0xAA598 gChaseNumber
0xAA59C gRandomChase
0xAA5A0 gSubGameNumber
0xAA5A4 bReturnToMain
0xAA5A8 CurrentGameMode
0xAA5A9 WantedGameMode
0xAA5AC fakeOtherPlayer
0xAA5B0 gMissionLadderPos
0xAA5B4 gFurthestMission
0xAA5B8 gWantNight
0xAA5BC gIdleReplay
0xAA5C0 autobrakeon
0xAA5C4 gPlayerCarDamage
0xAA5C8 DebrisTimer
0xAA5CC last_track_state
0xAA5D0 doWheels
0xAA5D4 playerghost
0xAA5D8 playerhitcopsanyway
0xAA5DC savemapinfo
0xAA5E0 crateoffset
0xAA5E4 littleBangTime
0xAA5E8 screen_fade_value
0xAA5EC screen_fade_start
0xAA5F0 screen_fade_end
0xAA5F4 screen_fade_speed
0xAA5F8 FadingScreen
0xAA5FC bMissionTitleFade
0xAA600 bWantFade
0xAA604 fadeVal
0xAA608 WantPause
0xAA60C gDieWithFade
0xAA610 tannerDeathTimer
0xAA614 LoadedLevel
0xAA615 NewLevel
0xAA616 IconsLoaded
0xAA617 gLeadCarModel
0xAA618 gNoSaveAllowed
0xAA619 gDoneQuickReplay
0xAA61A gRightWayUp
0xAA61B ghost_mode
0xAA61C paused
0xAA61D CamerasSaved
0xAA61E final_replays
0xAA61F cameraview
0xAA620 ReplayMode
0xAA621 NoPlayerControl
0xAA622 CurrentRoad
0xAA624 CurrentJunction
0xAA628 gNumCitiesOpen
0xAA62C GameType
0xAA62D StoredGameType
0xAA630 gCurrentMissionNumber
0xAA634 gCurrentChaseNumber
0xAA638 CurrentPlayerView
0xAA63C persuit_mode
0xAA640 GameLevel
0xAA644 PlayerCarModel
0xAA648 AttractMode
0xAA64C gCopDifficultyLevel
0xAA650 pauseflag
0xAA654 lead_car
0xAA658 PlayerCar
0xAA65C CameraCar
0xAA660 TargetCar
0xAA664 defaultPlayerModel
0xAA666 defaultPlayerPalette
0xAA668 gameinit
0xAA66C gInFrontend
0xAA670 gLoadedReplay
0xAA674 gShowMap
0xAA678 gVibration
0xAA67C gInvincibleCar
0xAA680 gPlayerImmune
0xAA684 gNight
0xAA688 gStopPadReads
0xAA68C leadAIRequired
0xAA690 leadAILoaded
0xAA694 pathAILoaded
0xAA698 wantedCar
0xAA6A0 gSubtitles
0xAA6A4 ObjectDrawnCounter
0xAA6D4 cells_across
0xAA6D8 cells_down
0xAA6DC es_mobile
0xAA6E0 gDisplayPosition
0xAA6F8 gHaveStoredData
0xAA6FC carSelectPlayerText
0xAA738 MissionLoadAddress
0xAA73C cop_adjust
0xAA740 NewLeadDelay
0xAA744 prevCopsInPursuit
0xAA748 last_flag
0xAA74C lastsay
0xAA750 gStartOnFoot
0xAA754 gTimeOfDay
0xAA758 gWeather
0xAA75C gTannerActionNeeded
0xAA760 gPlayerWithTheFlag
0xAA764 gCarWithABerm
0xAA768 gCantDrive
0xAA76C MaxPlayerDamage
0xAA774 TAIL_TOOCLOSE
0xAA778 TAIL_GETTINGCLOSE
0xAA77C TAIL_GETTINGFAR
0xAA780 TAIL_TOOFAR
0xAA784 gNumRaceTrackLaps
0xAA788 gMissionTitle
0xAA78C gMissionCompletionState
0xAA790 gDontPingInCops
0xAA794 g321GoDelay
0xAA798 gGotInStolenCar
0xAA79C gCopCarTheftAttempted
0xAA7A0 gLockPickingAttempted
0xAA7A4 gDontResetCarDamage
0xAA7B0 specModelValid
0xAA7B4 bAllreadyRotated
0xAA7B8 bDoingShadow
0xAA7BC vStored
0xAA7C0 zVal
0xAA800 motion_dir
0xAA804 bLoadedAllMC
0xAA808 bDisplayBones
0xAA80C myVal
0xAA810 bodyShiftValue
0xAA814 palnumber
0xAA818 testRadius
0xAA81C test777
0xAA820 align
0xAA828 dummymotors
0xAA82C DuplicatePadData
0xAA834 pad_connected
0xAA838 gDualShockMax
0xAA83C gEnteringScore
0xAA840 gScorePosition
0xAA844 gScoreEntered
0xAA860 allownameentry
0xAA864 gDrawPauseMenus
0xAA868 gNoReplaySaveAllowed
0xAA8B4 num_pedestrians
0xAA8B8 numTannerPeds
0xAA8BC bTannerSitting
0xAA8C0 pinginPedAngle
0xAA8C4 iAllowWatch
0xAA8C8 iFreezeTimer
0xAA8CC bFreezeAnimation
0xAA8D0 bReverseAnimation
0xAA8D4 max_pedestrians
0xAA8D8 bKillTanner
0xAA8DC bReverseYRotation
0xAA8E0 bAvoidTanner
0xAA8E4 bAvoidBomb
0xAA8E8 iIdleTimer
0xAA8EC bKilled
0xAA8F0 bStopTanner
0xAA8F4 numCopPeds
0xAA8F8 tannerTurnStep
0xAA8FC tannerTurnMax
0xAA900 tannerTurn
0xAA904 bPower
0xAA908 powerCounter
0xAA930 pCivCarToGetIn
0xAA938 allreadydone
0xAA93C lastCarCameraView
0xAA940 numPlayersToCreate
0xAA97C idx
0xAA980 rotated
0xAA984 distance
0xAA988 pos
0xAA98C outvertices
0xAA990 outcoords
0xAA994 skyred
0xAA998 skygreen
0xAA99C skyblue
0xAA9A0 gDrawLowerSky
0xAA9AC gTunnelNum
0xAA9B0 gSoundMode
0xAA9B4 gSurround
0xAA9B8 banksize
0xAA9C0 sound_paused
0xAA9C4 music_paused
0xAA9C8 master_volume
0xAA9CC stop_sound_handler
0xAA9D0 Song_ID
0xAA9D4 VABID
0xAA9D8 gMusicVolume
0xAA9DC gMasterVolume
0xAA9E0 gAllowMusic
0xAA9E4 gAllowSfx
0xAA9E8 LoadingArea
0xAA9EC spoolpos_reading
0xAA9F0 spoolpos_writing
0xAA9F4 type
0xAA9F8 music_is_loading
0xAA9FC doSpooling
0xAAA00 error_bounds
0xAAA04 times
0xAAA08 specialState
0xAAA0C specBlocksToLoad
0xAAA18 lasttype
0xAAA19 lastcity
0xAAA1A NumPlayers
0xAAA1C DoNotSwap
0xAAA20 gMultiplayerLevels
0xAAA28 cak
0xAAA2C gDraw3DArrowBlue
0xAAA30 texture_is_icon
0xAAA34 specspooldata
0xAAA48 dbSurfacePtr
0xAAA4C finished_count
0xAAA50 gPlaying
0xAAA54 gChannel
0xAAA58 xa_prepared
0xAAA5C XM_SCAN
0xAAA60 JPError
0xAAA64 MonoMode
0xAAA68 XM_NSA
0xAAA6C XM_HA
0xAAA70 tt
0xAAA74 aa
0xAAA78 dd
0xAAA7C de
0xAAA80 JPPer
0xAAA8C Driver2CurvesPtr
0xAAA90 sdLevel
0xAAA94 region_buffer_xor
0xAAA98 NumDriver2Straights
0xAAA9C NumDriver2Junctions
0xAAAA0 Driver2StraightsPtr
0xAAAA4 Driver2JunctionsPtr
0xAAAA8 cycle_phase
0xAAAAC cycle_timer
0xAAAB0 num_anim_objects
0xAAAB4 num_cycle_obj
0xAAAB8 OverlayFlashValue
0xAAAC0 MapBitMaps
0xAAAC8 MapRect
0xAAAD0 MapTPage
0xAAAD2 MapClut
0xAAAD4 first_paletised_page
0xAAAD8 TestCnt
0xAAADC ReplayStart
0xAAAE0 way_distance
0xAAAE4 PingBufferPos
0xAAAE8 PlayerWayRecordPtr
0xAAAEC ReplayParameterPtr
0xAAAF0 TimeToWay
0xAAAF4 replayptr
0xAAAF8 PingBuffer
0xAAB00 boxOverlap
0xAAB04 wibblewibblewoo
0xAAB08 mTheta
0xAAB10 baseDir
0xAAB14 maxCameraDist
0xAAB18 jcam
0xAAB1C paddCamera
0xAAB20 savedSP.21
0xAAB24 gUnderIntensity
0xAAB28 whichCP
0xAAB2C gForceLowDetailCars
0xAAB30 baseSpecCP
0xAAB34 num_cars_drawn
0xAAB38 sizeof_cell_object_computed_values
0xAAB40 tmpNewLane
0xAAB48 numCopCars
0xAAB4C numCivCars
0xAAB50 tmpNewRoad
0xAAB58 angle
0xAAB5C distFurthestCivCarSq
0xAAB60 numInactiveCars
0xAAB64 frameStart
0xAAB68 test42
0xAAB6C test123
0xAAB70 limoId
0xAAB74 test555
0xAAB78 makeLimoPullOver
0xAAB7C numRoadblockCars
0xAAB80 tmpCrv
0xAAB88 carnum
0xAAB8C radius
0xAAB90 tmpStr
0xAAB98 requestRoadblock
0xAAB9C collDat
0xAABA0 laneFit
0xAABA8 roadSeg
0xAABB0 validExitIdx
0xAABB8 dx
0xAABBC dy
0xAABC0 dz
0xAABC4 newExit
0xAABC8 distObstacle
0xAABCC currentAngle
0xAABD0 testNum
0xAABD4 tstNode1
0xAABD8 tstNode2
0xAABDC furthestCivID
0xAABE0 maxParkedCars
0xAABE4 numParkedCars
0xAABE8 currentRoadId
0xAABEC maxPlayerCars
0xAABF0 numPlayerCars
0xAABF4 requestStationaryCivCar
0xAABF8 distFromCentre
0xAABFC startNode
0xAAC00 playerNum
0xAAC04 roadblockCount
0xAAC08 junctionLightsPhase
0xAAC0C maxCopCars
0xAAC10 maxCivCars
0xAAC18 randomcounter
0xAAC1C randomindex
0xAAC20 mcgn
0xAAC24 srgn
0xAAC28 said_picked_up
0xAAC2C OutOfSightCount
0xAAC30 CopsCanSeePlayer
0xAAC34 LastHeading
0xAAC38 CopsAllowed
0xAAC3C copsAreInPursuit
0xAAC40 copSightData
0xAAC48 pathStraight
0xAAC4C player_position_known
0xAAC50 cop_respawn_timer
0xAAC54 numActiveCops
0xAAC58 requestCopCar
0xAAC5C targetVehicle
0xAAC60 padid.33
0xAAC68 SavedCameraCarId
0xAAC6C SavedCameraView
0xAAC70 SavedCameraAngle
0xAAC74 SavedWorldCentreCarId
0xAAC78 SavedSpoolXZ
0xAAC80 SinX.103
0xAAC84 CosX.104
0xAAC88 rand.142
0xAAC8C ThunderTimer
0xAAC90 ThunderDistance
0xAAC94 plotted
0xAAC98 RightLight
0xAAC99 gRainCount
0xAAC9C next_smoke
0xAACA0 LightSortCorrect
0xAACA4 smoke_table
0xAACA8 leaf_rotvec
0xAACB0 CarLightFadeFront
0xAACB4 next_debris
0xAACB8 StreakCount1
0xAACBC NextDamagedPmeter
0xAACC0 wetness
0xAACC4 gNextRainDrop
0xAACC8 NoRainIndoors
0xAACCC gEffectsTimer
0xAACD0 SmashablesHit
0xAACD4 gcar_num
0xAACD8 debris_rotvec
0xAACE0 main_cop_light_pos
0xAACE4 LeftLight
0xAACE6 light_col
0xAACE8 next_leaf
0xAACEC NextDamagedLamp
0xAACF0 gCarPoolsToDraw
0xAACF4 LightIndex
0xAACF8 CarLightFadeBack
0xAAD00 gHubcapTime
0xAAD08 FlashCnt.42
0xAAD0C cammapht2
0xAAD10 mapstuff
0xAAD14 MenuOffset
0xAAD18 time_taken
0xAAD1C menuactive
0xAAD20 PlayerWaypoints
0xAAD24 CursorX
0xAAD28 CursorY
0xAAD2C tracking_car
0xAAD2D CameraChanged
0xAAD30 quick_replay
0xAAD34 PlayMode
0xAAD38 PlaybackCamera
0xAAD3C ReplayContinue
0xAAD40 frame_advance_count
0xAAD44 AutoDirect
0xAAD48 temp.61
0xAAD4C current_matrix
0xAAD50 numSpritesFound
0xAAD54 transparent_buffer
0xAAD58 current_inv_matrix
0xAAD5C buildingsFound
0xAAD60 FrAng
0xAAD64 current_offset
0xAAD68 tile_overflow_buffer
0xAAD6C vcount
0xAAD70 SubDivisionArrays
0xAAD74 fasterToggle
0xAAD78 ot_slot
0xAAD7C Low2HighDetailTable
0xAAD80 Low2LowerDetailTable
0xAAD88 gTrailblazerConeModel
0xAAD90 ShinyTextureNum
0xAAD94 ShinyTexturePage
0xAAD98 firstX.8
0xAADA0 firstZ.9
0xAADA8 count.10
0xAADB0 address.39
0xAADB8 speed.49
0xAADBC rotating.57
0xAADC0 nearestTrain.70
0xAADC4 distanceFromNearestTrain.71
0xAADC8 rememberCameraAngle.105
0xAADD0 count.106
0xAADD8 foam
0xAADE0 event
0xAADE4 cameraEventsActive
0xAADE8 trackingEvent
0xAADF0 carsOnBoat
0xAADF8 boatOffset
0xAAE00 multiCar
0xAAE08 fixedEvent
0xAAE0C firstMissionEvent
0xAAE10 detonator
0xAAE18 doneFirstHavanaCameraHack
0xAAE20 cameraDelay
0xAAE28 xVis
0xAAE2C zVis
0xAAE30 debugSpeed
0xAAE34 debugCount
0xAAE38 firstEvent
0xAAE3C debugOffset
0xAAE40 EventCop
0xAAE48 debugNode
0xAAE50 event_models_active
0xAAE58 last_cop_phrase
0xAAE5C FelonyDecreaseTime
0xAAE60 FelonyIncreaseTime
0xAAE64 FelonyDecreaseTimer
0xAAE68 FelonyIncreaseTimer
0xAAE6C playerLastRoad
0xAAE70 test3
0xAAE74 test4
0xAAE78 test5
0xAAE7C test6
0xAAE80 test7
0xAAE84 test8
0xAAE88 oldsp.12
0xAAE90 j_said.78
0xAAE94 xm_samples.90
0xAAE95 xm_samples.96
0xAAE98 rnd.139
0xAAE9C loudhail_time
0xAAEA0 cop_model
0xAAEA1 cop_bank
0xAAEA4 horn_time
0xAAEA8 phrase_top
0xAAEA9 first_offence
0xAAEAC TimeSinceLastSpeech
0xAAEB0 ScreenDepth
0xAAEB8 hSubShad
0xAAEC0 delta
0xAAEC8 num_active_cars
0xAAECC gTimeInWater
0xAAED0 continuous_track
0xAAED1 rear_only
0xAAED8 ExBoxDamage
0xAAEDC ExBombTimer
0xAAEE0 TriggerBomb
0xAAEE4 ExLastCarXVel
0xAAEE8 ExLastCarZVel
0xAAEEC ExLastCarX
0xAAEF0 ExLastCarZ
0xAAEF8 ActiveCheats
0xAAEFC AvailableCheats
0xAAF00 loading_bar_pos
0xAAF04 load_steps
0xAAF08 t0.18
0xAAF0C t1.19
0xAAF0D t2.20
0xAAF10 oldsp.21
0xAAF14 null.27
0xAAF18 PauseMode
0xAAF1C gLoadedMotionCapture
0xAAF20 cells
0xAAF24 scr_z
0xAAF28 current_object_computed_value
0xAAF2C car_models_lump
0xAAF30 xa_timeout
0xAAF34 gPed1HeadModelPtr
0xAAF38 gPed2HeadModelPtr
0xAAF3C gPed3HeadModelPtr
0xAAF40 gPed4HeadModelPtr
0xAAF44 ObjectDrawnValue
0xAAF48 controller_bits
0xAAF4C handle
0xAAF50 cell_header
0xAAF54 playerDying
0xAAF58 gDamWheelModelPtr
0xAAF5C InWater
0xAAF60 gBoxModelPtr
0xAAF64 gShowPlayerDamage
0xAAF68 NightAmbient
0xAAF6C cell_objects
0xAAF70 saved_leadcar_pos
0xAAF74 palette_lump
0xAAF78 gFastWheelModelPtr
0xAAF7C lead_pad
0xAAF80 gSinkingTimer
0xAAF84 lead_analogue
0xAAF88 leadCarId
0xAAF8C map_lump
0xAAF90 CameraCnt
0xAAF94 gCleanWheelModelPtr
0xAAF98 gBobIndex
0xAAF9C saved_counter
0xAAFA0 gDoCrates
0xAAFA4 gLightsOn
0xAAFA8 DawnCount
0xAAFAC gLoadedOverlay
0xAAFB0 HitLeadCar
0xAAFB4 gRotorPtr
0xAAFB8 game_over
0xAAFBC cell_ptrs
0xAAFC0 mallocptr
0xAAFC4 gHubcapModelPtr
0xAAFC8 lockAllTheDoors
0xAAFD0 PVSEncodeTable
0xAAFD4 units_across_halved
0xAAFD8 old_region
0xAAFDC pvs_square
0xAAFE0 pvs_objects_rejected
0xAAFE4 num_regions
0xAAFE8 regions_down
0xAAFEC units_down_halved
0xAAFF0 camera_cell_x
0xAAFF4 camera_cell_z
0xAAFF8 current_barrel_region_xcell
0xAAFFC current_barrel_region_zcell
0xAB000 initarea
0xAB004 region_x
0xAB008 region_z
0xAB00C num_models_in_pack
0xAB010 pvs_cells_rejected
0xAB014 pvs_square_sq
0xAB018 view_dist
0xAB01C current_cell_x
0xAB020 current_cell_z
0xAB024 regions_across
0xAB028 current_region
0xAB02C num_straddlers
0xAB030 cutscene_timer
0xAB034 holdall
0xAB038 bodgevar
0xAB03C rio_alarm
0xAB040 xa
0xAB048 force_idle
0xAB050 jericho_in_back
0xAB058 force_siren
0xAB060 playercollected
0xAB064 gMusicType
0xAB068 NumTempJunctions
0xAB06C MissionHeader
0xAB070 Driver2TempJunctionsPtr
0xAB074 MissionScript
0xAB078 gPlayerDamageFactor
0xAB07C MissionTargets
0xAB080 MissionStrings
0xAB088 modelname_buffer
0xAB08C specmallocptr
0xAB090 specLoadBuffer
0xAB098 ThisMotion
0xAB09C pDrawingPed
0xAB0A0 Tangle
0xAB0A4 frames
0xAB0A8 svTemp
0xAB0AC joints
0xAB0B0 rectTannerWindow
0xAB0B8 iCurrBone
0xAB0BC gCurrentZ
0xAB0C0 initial.24
0xAB0C8 coplist
0xAB0CC pcoplist
0xAB0D0 gLastModelCollisionCheck
0xAB0D8 VisibleMenu
0xAB0DC ActiveMenu
0xAB0E0 ActiveMenuItem
0xAB0E4 PauseReturnValue
0xAB0E8 SfxVolumeText
0xAB0F0 MusicVolumeText
0xAB0F8 storedCam
0xAB0FC oldCamView
0xAB100 camAngle
0xAB108 oldDir
0xAB10C pPlayerPed
0xAB110 collision_boxes_set
0xAB114 num_extra_boxes_set
0xAB118 oldWeather
0xAB11C seated_count
0xAB120 seated_pedestrian
0xAB124 basic_car_interest
0xAB128 pFreePeds
0xAB12C pUsedPeds
0xAB130 maxSeated
0xAB134 tannerPad
0xAB138 pcdTanner
0xAB13C carToGetIn
0xAB140 ping_in_pedestrians
0xAB144 pHold
0xAB148 my_sly_var
0xAB150 combointensity
0xAB154 gTempCarUVPtr
0xAB158 gFontColour
0xAB15C fontclutid
0xAB160 fontclutpos
0xAB168 fonttpage
0xAB170 JunctionLightsWE
0xAB171 JunctionLightsNS
0xAB178 numcv
0xAB17C lastcv
0xAB180 spolys
0xAB184 gShadowTextureNum
0xAB188 gShadowTexturePage
0xAB18C shadow_header
0xAB190 shadowuv
0xAB198 edgecount
0xAB19A nextindex
0xAB1A0 last_attempt_failed.9
0xAB1A4 skycolour
0xAB1A8 skyFade
0xAB1B0 old_camera_change
0xAB1B4 song_address
0xAB1B8 camera_change
0xAB1C0 bankaddr
0xAB1C8 music_address
0xAB1D0 param
0xAB1D8 result
0xAB1E0 target_address
0xAB1E4 current_sector
0xAB1E8 sectors_to_read
0xAB1EC sectors_this_chunk
0xAB1F0 switch_spooltype
0xAB1F4 nTPchunks
0xAB1F8 nTPchunks_reading
0xAB1FC nTPchunks_writing
0xAB200 tpage
0xAB208 ntpages
0xAB20C endchunk
0xAB210 RegionSpoolInfo
0xAB214 SpoolLumpOffset
0xAB218 spool_regioncounter
0xAB21C quickSpool
0xAB220 spuaddress
0xAB224 n_sample_chunks
0xAB228 packed_cell_pointers
0xAB22C spoolerror
0xAB230 spool_regionpos
0xAB234 buffer
0xAB238 modelMemory
0xAB23C num_samples
0xAB240 spoolactive
0xAB244 current_music_id
0xAB248 tsetcounter
0xAB24C AreaData
0xAB250 specSpoolComplete
0xAB254 models_ready
0xAB258 sample_chunk
0xAB25C allowSpecSpooling
0xAB260 new_area_location
0xAB264 tsetpos
0xAB268 NumAreas
0xAB26C firstDamBlock
0xAB270 spoolcounter
0xAB274 spoolinfo_offsets
0xAB278 loadbank_read
0xAB27C firstLowBlock
0xAB280 unpack_roadmap_tbl
0xAB288 nsectors
0xAB28C Music_And_AmbientOffsets
0xAB290 spoolpos
0xAB294 model_spool_buffer
0xAB298 lengthDamBlock
0xAB29C lastCleanBlock
0xAB2A0 damOffset
0xAB2A4 done
0xAB2A8 lengthLowBlock
0xAB2AC send_bank
0xAB2B0 lowOffset
0xAB2B4 AreaTPages
0xAB2B8 LoadedArea
0xAB2C0 loading_region
0xAB2C8 unpack_roadmap_flag
0xAB2CC loadbank_write
0xAB2D0 startSpecSpool
0xAB2D4 last_size
0xAB2D8 newmodels
0xAB2DC spoolseek
0xAB2E0 chunk_complete
0xAB2E4 unpack_cellptr_flag
0xAB2E8 param.25
0xAB2F0 load_complete
0xAB2F1 endread
0xAB2F4 current_sector
0xAB2F8 sectors_left
0xAB2FC sectors_read
0xAB300 current_address
0xAB304 paddp
0xAB308 vblcounter
0xAB310 MPlast
0xAB318 current
0xAB31C primptr
0xAB320 FrameCnt
0xAB324 padd
0xAB328 MPcurrent
0xAB330 last
0xAB338 tpage
0xAB340 nspecpages
0xAB344 NoTextureMemory
0xAB348 mapclutpos
0xAB350 specialSlot
0xAB354 nperms
0xAB358 MaxSpecCluts
0xAB35C environmenttpage
0xAB360 tpage_amount
0xAB368 clutpos
0xAB370 speclist
0xAB374 permlist
0xAB378 texturename_buffer
0xAB37C texture_lump_start
0xAB380 texamount
0xAB384 slotsused
0xAB388 tpage_position
0xAB390 impulse
0xAB398 CurrentChannel
0xAB39A ID
0xAB39C StartPos
0xAB3A0 pause_loc
0xAB3A4 olddatacallback
0xAB3A8 oldreadycallback
0xAB3B0 XMTime1
0xAB3B4 XMTime2
0xAB3B8 XMTime3
0xAB3BC PALType
0xAB3C0 mh
0xAB3C4 ms
0xAB3C8 mu
0xAB3CC BPMLimit
0xAB3D0 DVL
0xAB3D4 XMC
0xAB3D8 XM_FrameSpeed
0xAB3DC DVR
0xAB3E0 JP_Do_Nothing
0xAB3E4 XMCU
0xAB3E8 mhu
0xAB3EC CurrentCh
0xAB3F0 ret.30
0xAB3F4 MCbuffer128K
0xAB3F8 MClanguageBuffer
0xAB3FC MCsaveBuffer
0xAB400 MCfilename
0xAB404 MCoptions
0xAB408 MCsp
0xAB40C gMemCardMode
0xAB748 CurrentGarage
0xAB768 GuitarPos
0xAB778 cycle_tex
0xAB820 Player2DamageBar
0xAB840 ProxyBar
0xAB860 DamageBar
0xAB880 FelonyBar
0xAB8A0 PlayerDamageBar
0xAB8C0 MapBuffer
0xABAD0 maptile
0xABAE0 map_matrix
0xABB00 civ_clut
0xAC700 ReplayStreams
0xAC920 Roadblock
0xAC958 cd.24
0xACA28 collisionResult.25
0xACA50 ThrownBombs
0xACB08 basePos
0xACB18 face_camera
0xACB38 viewer_position
0xACB48 inv_camera_matrix
0xACB68 camera_matrix
0xACB88 FrontWheelRotation.25
0xACBB8 BackWheelRotation.26
0xACBE0 NewCarModel
0xACC80 save_light_matrix
0xACCA0 pbf
0xB8838 NewLowCarModel
0xB88D8 save_colour_matrix
0xB88F8 cell_object_computed_values
0xB90F8 cell_object_buffer
0xBD0F8 cd
0xBD1C8 civrseed
0xBD210 currentCar
0xBD4B0 currentPos
0xBD4C0 endPos
0xBD4D0 brakeLength
0xBD520 baseLoc
0xBD530 roadblockLoc
0xBD540 testVec
0xBD550 startPos
0xBD560 reservedSlots
0xBD578 randomLoc
0xBD588 rseed
0xBD5D0 felonyData
0xBD668 targetPoint
0xBD678 CarTail
0xBD688 lastKnownPosition
0xBD698 CopWorkMem
0xBD858 work_matrix.25
0xBD878 PlayerStartInfo
0xBD898 CutsceneBuffer
0xBF8B8 joypad_texture
0xBF8C8 collon_texture
0xBF8D8 leaf_alloc
0xBF940 clock
0xBF950 incar
0xBF960 litter_texture
0xBF970 pause
0xBF980 smoke
0xC0880 debris_mat
0xC08A0 norot
0xC08C0 movecampos
0xC08D0 litter_rot
0xC0A50 addcam
0xC0A60 debris_rot1
0xC0BE0 debris_rot2
0xC0D60 debris_rot3
0xC0EE0 delcam
0xC0EF0 tannerShadow_texture
0xC0F00 Known_Lamps
0xC10F8 debris
0xC1A58 smoke_alloc
0xC1AF8 forearm1_texture
0xC1B08 pad_texture
0xC1B18 sea_texture
0xC1B28 NewLamp
0xC1B80 cop_texture
0xC1B90 sun_texture
0xC1BA0 lightref_texture
0xC1BB0 damaged_lamp
0xC1BD8 ok
0xC1BE8 editcam
0xC1BF8 arm1_texture
0xC1C08 playcam
0xC1C18 movecam
0xC1C28 debris_alloc
0xC1CA0 autocam
0xC1CB0 lookcar
0xC1CC0 gTyreTexture
0xC1CD0 restart
0xC1CE0 line_texture
0xC1CF0 drop_texture
0xC1D00 moon_texture
0xC1D10 pool_texture
0xC1D20 lensflare_texture
0xC1D30 head1_texture
0xC1D40 leaf_mat
0xC1D60 chasecar
0xC1D70 fixedcam
0xC1D80 frameadv
0xC1D90 bird_texture1
0xC1DA0 bird_texture2
0xC1DB0 lenschan
0xC1DC0 leaf_rot
0xC1F40 save2card
0xC1F50 flare_texture
0xC1F60 digit_texture
0xC1F70 jeans_texture
0xC1F80 watch_texture
0xC1F90 light_texture
0xC1FA0 paper_texture
0xC1FB0 trail_texture
0xC1FC0 leaf
0xC2858 smoke_texture
0xC2868 spark_texture
0xC2878 cross_texture
0xC2888 damaged_object
0xC29D0 texturePedHead
0xC29E0 gPoolPoly
0xC29F8 light_pool_texture
0xC2A08 choosecar
0xC2A18 chest1_texture
0xC2A28 playpause
0xC2A38 gRainAlloc
0xC2BA0 gRain
0xC39B0 debris_texture
0xC39C0 gHDCarDamageZonePolys
0xC41F8 gTempCarVertDump
0xC9478 gHubcap
0xC9530 gHDCarDamageLevels
0xC9A30 gCarDamageZoneVerts
0xCA010 ShadowPos
0xCA020 gTempHDCarUVDump
0xCB410 gTempLDCarUVDump
0xCBE88 GreyIcons
0xCBEA0 car_distance.60
0xCBEF0 anim_obj_buffer
0xCBF40 spriteList
0xCC070 frustrum_matrix
0xCC090 matrixtable
0xCC890 planeColours
0xCC8B0 shadowMatrix
0xCC8D0 model_object_ptrs
0xCD0D0 ground_debris
0xCD1D0 current_camera_position
0xCD1E0 CompoundMatrix
0xCD9E0 vtab
0xCDA20 wrongside
0xCDA50 smashed_cones
0xCDAC8 VeryShinyTable
0xCDBC8 Car0_ShinyTable
0xCDCC8 xList.6
0xCDDC8 zList.7
0xCDEC8 stage.90
0xCDEF8 rememberCamera.97
0xCDF08 carEvent
0xCDF28 eventCamera
0xCDF60 events
0xCDF70 carriageData
0xCDF98 envsnd
0xCE598 ESdata
0xCE6C8 EStags
0xCE6D8 car_noise
0xCE708 siren_noise
0xCE728 header_pt
0xCF648 song_pt
0xD01F8 gSpeechQueue
0xD0220 tunnels
0xD05C8 ScreenNames
0xD05F8 pScreenStack
0xD0620 pButtonStack
0xD0648 _tp.18
0xD0A58 _d0.19
0xD0E68 _d1.20
0xD1278 active_car_list
0xD12C8 cheats
0xD12E0 car_data
0xD4C48 car_cosmetics
0xD50E8 bbox
0xD52C8 SmokePos
0xD52D8 bangPos
0xD52E8 globemesh
0xD5498 explosion
0xD5550 poly.9
0xD5570 p.10
0xD55A0 fade_gt4
0xD5610 fade_g4
0xD5658 load_draw
0xD56B8 load_disp
0xD56D0 stupid_logic.22
0xD56E0 buffer.26
0xD5720 leadcar_pos
0xD5730 gCarCleanModelPtr
0xD5748 lightsOnDelay
0xD5760 modelpointers
0xD6F60 gCarDamModelPtr
0xD6F78 gCarLowModelPtr
0xD6F90 PVS_Buffers
0xD6FA0 cell_objects_add
0xD6FB8 gRamSlotPosition
0xD71B8 nybblearray
0xD73B8 regions_unpacked
0xD73C8 cell_slots_add
0xD73E0 CurrentPVS
0xD75A0 pos
0xD75B0 MissionStartData
0xD7698 MissionEndData
0xD7780 MissionStack
0xD7B80 MissionThreads
0xD7C80 Mission
0xD7CC8 gLapTimes
0xD7CF0 gStopCops
0xD7D00 tileTannerClear
0xD7D20 cTannerVNumbers
0xD7D80 cJerichoVNumbers
0xD7DA0 vTannerList
0xD8430 pedestrians
0xD8E40 MotionCaptureData
0xD8EA0 vJerichoList
0xD91D0 ft4TannerShadow
0xD9220 cd
0xD92E8 padbuffer
0xD9330 Pads
0xD93C0 VisibleMenus
0xD93D0 ActiveItem
0xD93E0 EnterNameText
0xD9400 ScoreName
0xD9430 ScoreItems
0xD9480 ScoreTime
0xD94D0 DrivingDebugHeader
0xD94E8 EnterScoreText
0xD9508 collisionResult.124
0xD9538 collisionResult.128
0xD9568 cd
0xD9630 pmJerichoModels
0xD9648 tanner_collision_box
0xD9658 pedestrian_roads
0xD9668 extra_collision_boxes
0xD96B8 collision_car_ptr
0xD96D8 collision_box
0xD9758 pmTannerModels
0xD97A0 player
0xD9B40 button_textures
0xD9BE0 fontinfo
0xD9FE0 AsciiTable
0xDA0E0 RoadMapDataRegions
0xDA0F0 RoadMapRegions
0xDA100 roadMapLumpData
0xDA110 ScoreTables
0xDA980 gPlayerScore
0xDA998 Cont.12
0xDA9A8 cv
0xDAA08 tyre_save_positions
0xDAA48 num_tyre_tracks
0xDAA58 shadowPolys
0xDB098 smoke_count
0xDB0A8 track_buffer
0xDCCA8 tyre_track_offset
0xDCCB8 edgelist
0xDCCD8 ShadowPolygon
0xDCCF0 camverts
0xDD0F0 tyre_new_positions
0xDD130 direction
0xDD140 buffer.10
0xDD280 skytpage
0xDD2C0 skyclut
0xDD300 skytexuv
0xDD3E0 tabs.93
0xDD430 banks
0xDD450 channel_lookup
0xDD490 sound_attr
0xDD4C0 pause
0xDD530 musps
0xDD598 samples
0xDE4E8 lis_pos
0xDE4F8 channels
0xDEC78 cd_sprite
0xDECA8 dummyModel
0xDECD0 cd_palette
0xDED10 spool_regioninfo
0xDED90 tsetinfo
0xDEE10 unpack_cellptr_tbl
0xDEE20 multiplayerregions
0xDEE30 spooldata
0xDF130 pLodModels
0xE0930 MPBuff
0xE0B30 currentfileinfo
0xE0B48 citystart
0xE0B68 citylumps
0xE0C68 tpageslots
0xE0C80 tpageloaded
0xE0D00 tsdname
0xE0D80 slot_clutpos
0xE0DD0 tpage_texamts
0xE0FD0 slot_tpagepos
0xE1020 tpage_ids
0xE1220 buffer
0xE1240 XAMissionMessages
0xE1260 XM_HeaderAddress
0xE1280 xm_g_s_attr
0xE12C0 XM_SngAddress
0xE1320 xm_l_vag_spu_addr
0xE2320 uxm_g_s_attr
0xE2360 xm_r_attr
0xE47A8 StMode
0xE4830 _que
0xE6090 _spu_RQ
0xE6328 _padRestPeriod
0xE6330 _apiPadPatch
0x1C0C14 LoadFrontendScreens
0x1C0F1C LoadBackgroundFile
0x1C10EC SetupBackgroundPolys
0x1C1324 SetupScreenSprts
0x1C1474 DrawScreen
0x1C18DC DisplayOnScreenText
0x1C1AC8 SetupExtraPoly
0x1C1CEC ReInitScreens
0x1C1E10 NewSelection
0x1C22A0 HandleKeyPress
0x1C2660 PadChecks
0x1C2964 DoFrontEnd
0x1C2C24 SetFEDrawMode
0x1C2D88 FEPrintString
0x1C2FD0 FEPrintStringSized
0x1C31F4 CentreScreen
0x1C3428 CarSelectScreen
0x1C3A58 VibroOnOffScreen
0x1C3B14 MissionSelectScreen
0x1C4330 MissionCityScreen
0x1C45F8 CutSceneSelectScreen
0x1C4B28 CutSceneCitySelectScreen
0x1C50A8 SetVolumeScreen
0x1C55F0 DisplayScoreTable
0x1C5998 ScoreScreen
0x1C5B44 CheatScreen
0x1C6098 GameNameScreen
0x1C61A4 FEInitCdIcon
0x1C62F0 FEDrawCDicon
0x1C6370 EndFrame
0x1C63FC CopDiffLevelScreen
0x1C64A8 SubtitlesOnOffScreen
0x1C64F4 CityCutOffScreen
0x1C6540 ControllerScreen
0x1C660C MainScreen
0x1C664C ImmunityOnOffScreen
0x1C6698 InvincibleOnOffScreen
0x1C66E4 GamePlayScreen
0x1C671C CheatNumlayerSelect
0x1C676C gameNames
0x1C686C cheatText
0x1C6880 CutSceneNames
0x1C68F0 MissionName
0x1C6984 screen_limits
0x1C6994 bDoingScores
0x1C6998 cutSelection
0x1C699C bDoingCutSelect
0x1C69A0 cutGfxNames
0x1C69B0 CutAmounts
0x1C69C4 CutAmountsTotal
0x1C69D8 cutUnlock
0x1C6A04 carSelection
0x1C6A08 gfxNames
0x1C6A18 fpUserFunctions
0x1C6A68 currCity
0x1C6A6C missionSetup
0x1C6A70 loaded
0x1C6A73 lastCity
0x1C6A74 lastCutCity
0x1C6A78 bInCutSelect
0x1C6A7C currPlayer
0x1C6A80 bDoingCarSelect
0x1C6A84 currSelIndex
0x1C6A88 bDrawExtra
0x1C6A8C bScreenSetup
0x1C6A90 storeRect
0x1C6A98 bRedrawFrontend
0x1C6A9C bWantCDReset
0x1C6AA0 bRequestedKey
0x1C6AA4 bDoneAllready
0x1C6AA8 bMissionSelect
0x1C6AAC allowVibration
0x1C6AB0 numPadsConnected
0x1C6AB4 padsConnected
0x1C6ABC mainScreenLoaded
0x1C6AC0 bCdIconSetup
0x1C6AC4 carNumLookup
0x1C6AEC CarAvailability
0x1C6B8C oldActionSet
0x1C6B90 minmaxSelections
0x1C6BB0 botch
0x1C6CE0 GameNum
0x1C6CE4 CityNames
0x1C6CF4 scoreCol
0x1C6CF8 otherCol
0x1C6CFC contNames
0x1C6D18 cd_sprite
0x1C6D40 pNewScreen
0x1C6D48 PsxScreens
0x1CBCB0 pNewButton
0x1CBCB8 BackgroundPolys
0x1CBDA8 idle_timer
0x1CBDB0 extraDummy
0x1CBDD0 feFont
0x1CC1D8 ScreenTitle
0x1CC258 oldSfxLevel
0x1CC25C pCurrScreen
0x1CC260 ScreenDummy
0x1CC360 ScreenPolys
0x1CC4A0 ScreenSprts
0x1CC540 pCurrButton
0x1CC544 currMission
0x1CC548 In
0x1CC560 oldActionVal
0x1CC568 Out
0x1CC580 oldMusicLevel
0x1CC588 HighlightSprt
0x1CC5A0 HighlightDummy
0x1CC5C0 extraSprt
0x1CC5D4 fePad
0xE7128 InitLead
0xE73E8 LeadUpdateState
0xE7994 LeadPadResponse
0xE7DE8 FakeMotion
0xE834C PosToIndex
0xE86BC BlockToMap
0xE98A4 IsOnMap
0xE9BB8 UpdateRoadPosition
0xEB1FC CheckCurrentRoad
0xEC1C4 SetTarget
0xEC5E4 SelectExit
0xEC99C FreeRoamer
0xECB28 hypot
0xECC14 toGo.22
0xECC18 angle.23
0xECC1C s.24
0xECC20 c.25
0xECC24 carLength.35
0xECC28 carWidth.36
0xECC2C left.39
0xECC30 right.40
0xECC34 ldist.41
0xECC38 rdist.42
0xECC40 newdata.43
0xECC60 nextJunction.55
0xECC70 basePosition.56
0xECC80 d.57
0xECC84 toGo.58
0xECC88 angle.59
0xECC8C s.60
0xECC90 c.61
0xECC94 angle.62
0xECC98 radius.63
0xECC9C dx.64
0xECCA0 dz.65
0xECCA4 fixedThresh.66
0xECCA8 diff.67
0xECCAC dx.68
0xECCB0 dz.69
0xECCB4 dx.70
0xECCB8 dz.71
0xECCBC dist.72
0xECCC0 offx.73
0xECCC4 offz.74
0xECCC8 angle.75
0xECCCC dx.76
0xECCD0 dz.77
0xECCD4 basex.78
0xECCD8 basez.79
0xECCDC dist.80
0xECCE0 offx.81
0xECCE4 offz.82
0xECCE8 dx.86
0xECCEC dz.87
0xECCF0 randState
0xECD34 randIndex
0xECD38 road_c
0xECD3C road_s
0xECD40 localMap
0xECDE8 roadAhead
0xECE90 LeadValues
0xE7194 WunCell
0xE735C InvalidateMap
0xE74B0 BloodyHell
0xE76C4 blocked
0xE7814 iterate
0xE7BD0 InitPathFinding
0xE7CA8 getInterpolatedDistance
0xE822C addCivs
0xE836C UpdateCopMap
0xE8F00 getHeadingToPlayer
0xE90A4 setDistance
0xE9138 cellsPerFrame
0xE913C slowWallTests
0xE9140 dirs
0xE9158 asf
0xE915C na
0xE91A0 OverlayOccupancyGrid
0xE99A8 pathFrames
0xE99AC DoExtraWorkForNFrames
0xE99B0 dunyet
0xE9AB0 distLogIndex
0xE9AB8 searchTarget
0xE9AC8 lastDistanceFound
0xE9ACC playerTargetDistanceSq
0xE9AD0 dbb
0xE9B00 distanceCache
0xF1B00 pathFrame
0xF1B08 heap
0xF2798 cellsThisFrame
0xF279C numHeapEntries
0xF27A0 distanceReturnedLog
0xF27C0 pathIterations
0xF3828 CardRemoved__6MCSLOT
0xF3994 CardInserted__6MCSLOT
0xF3B04 FormatCard__6MCSLOT
0xF3C74 ReadCardDir__6MCSLOT
0xF3DB8 ReadCardInfo__6MCSLOTPc
0xF41A0 ReadSlice__6MCSLOTiiP5SLICEP10FILEFORMAT
0xF43A0 read_block__6MCSLOTiPcR9BLOCKINFO
0xF46B4 write_block__6MCSLOTR9BLOCKINFOPc
0xF49E8 CreateBlock__6MCSLOTP10FILEFORMATP5SLICE
0xF502C DeleteBlock__6MCSLOTi
0xF512C Ascii2ShiftJis__FPsPc
0xF523C __6MCSLOTiiiiiiPc
0xF52F0 _._6MCSLOT
0xF534C card_stop__6MCSLOT
0xF5474 CheckCard__6MCSLOT
0xF555C card_event__6MCSLOTi
0xF5610 clear_event__6MCSLOT
0xF5668 invalidate_info__6MCSLOT
0xF56FC download_icon__6MCSLOTR9BLOCKINFOiiiii
0xF5860 CopyBlock__6MCSLOTi
0xF5918 PasteBlock__6MCSLOT
0xF5968 ReadHeader__6MCSLOTii
0xF5A60 RenameCopyBlock__6MCSLOTP10FILEFORMAT
0xF5B38 WriteSlice__6MCSLOTiiP5SLICEP10FILEFORMATPc
0xF5C70 SetPort__6MCSLOTii
0xF5D30 BlocksShared__6MCSLOTii
0xF5DC8 GetBlockSize__6MCSLOTi
0xF5DFC CardInfoRead__6MCSLOT
0xF5E08 GetBlockIconPtr__6MCSLOTi
0xF5E84 GetNoUsedBlocks__6MCSLOT
0xF5EA0 GetBlockTitlePtr__6MCSLOTi
0xF5EE4 GetBlockFilenamePtr__6MCSLOTi
0xF5F1C FilenameUsed__6MCSLOTPc
0xF5FBC GetNumGremBlocks__6MCSLOTPc
0xF6088 InsertSliceIntoCopyBuffer__6MCSLOTiPccccT2
0xF61F0 ExtractSliceFromCopyBuffer__6MCSLOTiPc
0xF628C GetSliceFilenamePtr__6MCSLOTii
0xF633C SliceUsed__6MCSLOTii
0xF63EC GetNoUsedSlices__6MCSLOTi
0xF6448 GetSliceIconRef__6MCSLOTiii
0xF64F4 GetNoSlices__6MCSLOTi
0xF6550 GremlinBlock__6MCSLOTi
0xF6588 delete_file
0xF65A8 __7DISPMANPlPPlP3PADP10FILEFORMATib
0xF72B8 DrawTitleBar__7DISPMAN
0xF7508 DrawCards__7DISPMAN
0xF7688 DrawMenu__7DISPMAN
0xF79C8 DrawKeyInfo__7DISPMAN
0xF7C4C DrawBlocks__7DISPMAN
0xF819C DrawSlices__7DISPMAN
0xF8B28 write_mess_in_box__7DISPMANG4RECTPciiii
0xF8D24 DrawBlockName__7DISPMAN
0xF8EE4 ActiveAreaLeft__7DISPMAN
0xF902C ActiveAreaRight__7DISPMAN
0xF9270 ActiveAreaUp__7DISPMAN
0xF941C ActiveAreaDown__7DISPMAN
0xF96F0 ActiveAreaSelect__7DISPMANii
0xF9BAC ActiveAreaConfirm__7DISPMAN
0xF9FAC intersect__7DISPMANG4RECTT1
0xFA174 Update__7DISPMAN
0xFA684 PrintKanji__7DISPMANPsiiiiii
0xFA97C darken__7DISPMANG4RECT
0xFACD4 DrawSprite__7DISPMANP9TIMSTRUCTiiiiii
0xFAED0 AddCircleG16__7DISPMANiiiiiiii
0xFB304 MessageBox__7DISPMANiPcbT3
0xFC950 ProgressBox__7DISPMANPci
0xFCC54 message_width__7DISPMANPcii
0xFCE00 justify_mess__7DISPMANPcii
0xFD000 write_mess__7DISPMANPciiiiiiii
0xFD410 font_ref__7DISPMANcb
0xFD658 Tim2VRAM__7DISPMANPlP9TIMSTRUCTibiiii
0xFD86C wipe_screen__7DISPMANii
0xFDAD8 _._7DISPMAN
0xFDBEC DrawEnterName__7DISPMANPc
0xFDC6C SetMenuOption__7DISPMANi
0xFDCBC SetActiveFunction__7DISPMANi
0xFDCC4 MoveActiveAreaTo__7DISPMANi
0xFDD0C SelectNewBlock__7DISPMANi
0xFDDD0 GetArea__7DISPMANii
0xFDE50 ActiveAreaCancel__7DISPMAN
0xFDF58 AddingBlock__7DISPMANi
0xFDF60 DeletingCurrBlock__7DISPMANi
0xFDF68 InvalidateArea__7DISPMANG4RECT
0xFE040 InvalidateArea__7DISPMANi
0xFE098 DrawArea__7DISPMANi
0xFE144 FlashOn__7DISPMAN
0xFE150 FlashOff__7DISPMAN
0xFE160 FindKanji__7DISPMANs
0xFE1B0 CentrePrintKanji__7DISPMANPsiiiiii
0xFE258 KanjiStrLen__FPsi
0xFE2F4 GetCurrBlock__7DISPMAN
0xFE300 GetCurrSlice__7DISPMAN
0xFE30C draw_card__7DISPMANiiPcb
0xFE434 AddIcon__7DISPMANP9TIMSTRUCTiiiiiib
0xFE598 AddMoveImage__7DISPMANP4RECTT1
0xFE61C AddSprite__7DISPMANP9TIMSTRUCTiiiiii
0xFE72C DrawBox__7DISPMANiiiiiii
0xFE834 write_mess_c__7DISPMANPciiiiiiii
0xFE908 download_block_icon__7DISPMANiiii
0xFEA44 move_screen__7DISPMANiii
0xFEB24 GetCyclesPerSecond__7DISPMAN
0xFEB70 __3PADPc
0xFECC0 GetPadData__3PADi
0xFF2CC port_name__3PADi
0xFF3C0 WaitUntilCardRemoved__3PADi
0xFF6E4 WaitUntilAnyCardInserted__3PAD
0xFFA1C check_ports__3PAD
0xFFC98 search_ports__3PADib
0xFFE44 _._3PAD
0xFFEA0 UpdateSlots__3PAD
0xFFEE0 NegConInserted__3PAD
0xFFF10 ControllerInserted__3PAD
0xFFF48 ControllerChanged__3PAD
0xFFF5C SetControllerType__3PAD
0x1000D0 MouseInserted__3PAD
0x100158 GetMouseX__3PAD
0x10016C GetMouseY__3PAD
0x100180 ResetPadData__3PAD
0x1001AC GetPortName__3PADi
0x100214 GetControllerPortName__3PAD
0x100244 CardSelected__3PADi
0x100260 CurrCardInfoRead__3PAD
0x10029C next_port__3PADi
0x1002A4 GetCurrNoUsedBlocks__3PAD
0x1002E0 CurrSlotBlocksShared__3PADii
0x10031C GetCurrSlotPtr__3PAD
0x100340 GetCurrSlot__3PAD
0x100354 GetDestSlotPtr__3PAD
0x10037C CardChanged__3PADi
0x1003B0 CardInserted__3PADi
0x1003E4 CycleSelectedSlot__3PAD
0x10042C CardFormatted__3PADi
0x100460 FormatCard__3PADi
0x1004C8 ParseLanguageFile__FPci
0x1005E0 cardman__FiiPcP10FILEFORMATP5SLICET2T2
0x102364 EnterName__FP3PADP7DISPMANPc
0x102710 card_manager
0x102744 LoadBackground__FPcT0
0x1027E8 g_black
0x1027E8 g_tim_buffer
0x1028F0 g_pointer
0x1029B8 g_memcard
0x102D68 g_arrows
0x103370 g_buttons
0x103FF0 g_abcd
0x1043F8 g_font0
0x1074CC g_font1
0x1095F0 g_font2
0x10EB20 add_prim
0x10EB44 _6MCSLOT.s_ev0
0x10EB48 _6MCSLOT.s_ev1
0x10EB4C _6MCSLOT.s_ev2
0x10EB50 _6MCSLOT.s_ev3
0x10EB54 _6MCSLOT.s_ev10
0x10EB58 _6MCSLOT.s_ev11
0x10EB5C _6MCSLOT.s_ev12
0x10EB60 _6MCSLOT.s_ev13
0x10EB64 _6MCSLOT.s_nullKanjiString
0x10EB68 _6MCSLOT.s_copyBufferSize
0x10EB6C _6MCSLOT.s_copyBufferPtr
0x10EB70 DM_CIRCLE
0x10EC70 _7DISPMAN.dispManPtr
0x10EC74 oTablePtr
0x10EC78 g_strActiveMouseArea
0x10EC80 g_PAD_FRB
0x10EC82 g_PAD_FLB
0x10EC84 g_PAD_FRT
0x10EC86 g_PAD_FLT
0x10EC88 g_PAD_RU
0x10EC8A g_PAD_RD
0x10EC8C g_PAD_RL
0x10EC8E g_PAD_RR
0x10EC90 g_PAD_LU
0x10EC92 g_PAD_LD
0x10EC94 g_PAD_LL
0x10EC96 g_PAD_LR
0x10EC98 g_PAD_SEL
0x10EC9A g_PAD_START
0x10EC9C g_controllerData
0x10ECE0 g_msg
0x10EE04 g_textBuffer
0x10EE08 g_nCManOptions
0x10EE0C validchars
*/
// 1474 external declarations
extern char *buffer; // address 0xAB234
extern char *car_models_lump; // address 0xAAF2C
extern char *CityNames[4]; // address 0x1C6CE4
extern char *contNames[2]; // address 0x1C6CFC
extern char *CosmeticFiles[4]; // address 0x9C05C
extern char *cutGfxNames[4]; // address 0x1C69A0
extern char *DentingFiles[4]; // address 0x9C35C
extern char *g_msg[73]; // address 0x10ECE0
extern char *g_textBuffer; // address 0x10EE04
extern char *gfxNames[4]; // address 0x1C6A08
extern char *gMissionTitle; // address 0xAA788
extern char *gRamSlotPosition[128]; // address 0xD6FB8
extern char *LevelFiles[4]; // address 0xA043C
extern char *LevelPalettes[8]; // address 0xA044C
extern char *LoadingScreenNames[4]; // address 0xA046C
extern char *mallocptr; // address 0xAAFC0
extern char *map_lump; // address 0xAAF8C
extern char *MissionStrings; // address 0xAB080
extern char *model_spool_buffer; // address 0xAB294
extern char *modelname_buffer; // address 0xAB088
extern char *motion_dir; // address 0xAA800
extern char *motion_files[8]; // address 0xA07E8
extern char *music_address; // address 0xAB1C8
extern char *packed_cell_pointers; // address 0xAB228
extern char *palette_lump; // address 0xAAF74
extern char *primptr; // address 0xAB31C
extern char *PVS_Buffers[4]; // address 0xD6F90
extern char *RegionSpoolInfo; // address 0xAB210
extern char *replayptr; // address 0xAAAF4
extern char *ReplayStart; // address 0xAAADC
extern char *ScreenNames[12]; // address 0xD05C8
extern char *song_address; // address 0xAB1B4
extern char *specLoadBuffer; // address 0xAB090
extern char *specmallocptr; // address 0xAB08C
extern char *SubDivisionArrays; // address 0xAAD70
extern char *texturename_buffer; // address 0xAB378
extern char *visiblelist; // address 0xAA494
extern char *XANames[4]; // address 0xA1F88
extern char AsciiTable[256]; // address 0xD9FE0
extern char camera_change; // address 0xAB1B8
extern char CameraChanged; // address 0xAAD2D
extern char CamerasSaved; // address 0xAA61D
extern char cameraview; // address 0xAA61F
extern char Car0_ShinyTable[256]; // address 0xCDBC8
extern char carNumLookup[4][10]; // address 0x1C6AC4
extern char carTpages[4][8]; // address 0x9BE8C
extern char continuous_track; // address 0xAAED0
extern char cookieCount; // address 0xAA1C4
extern char CopWorkMem[444]; // address 0xBD698
extern char currentfilename[128]; // address 0xA1C40
extern char CurrentPVS[444]; // address 0xD73E0
extern char cutUnlock[41]; // address 0x1C69D8
extern char DebrisTimer; // address 0xAA5C8
extern char EnterScoreText[32]; // address 0xD94E8
extern char es_mobile[1]; // address 0xAA6DC
extern char final_replays; // address 0xAA61E
extern char first_offence; // address 0xAAEA9
extern char force_idle[8]; // address 0xAB048
extern char force_siren[8]; // address 0xAB058
extern char furthestCivID; // address 0xAABDC
extern char gDoneQuickReplay; // address 0xAA619
extern char ghost_mode; // address 0xAA61B
extern char gLeadCarModel; // address 0xAA617
extern char gNoReplaySaveAllowed; // address 0xAA868
extern char gNoSaveAllowed; // address 0xAA618
extern char gRainCount; // address 0xAAC99
extern char gRightWayUp; // address 0xAA61A
extern char IconsLoaded; // address 0xAA616
extern char inGameCamera[4]; // address 0xAA170
extern char InWater; // address 0xAAF5C
extern char JunctionLightsNS; // address 0xAB171
extern char junctionLightsPhase[2]; // address 0xAAC08
extern char JunctionLightsWE; // address 0xAB170
extern char last_cop_phrase; // address 0xAAE58
extern char lastCity; // address 0x1C6A73
extern char lastCutCity; // address 0x1C6A74
extern char LeftLight; // address 0xAACE4
extern char limoId; // address 0xAAB70
extern char loaded[3]; // address 0x1C6A70
extern char lockAllTheDoors; // address 0xAAFC8
extern char makeLimoPullOver; // address 0xAAB78
extern char modelRandomList[16]; // address 0x9BFA4
extern char MonoMode; // address 0xAAA64
extern char MotionSpeed[7]; // address 0xA0808
extern char NewLevel; // address 0xAA615
extern char NoPlayerControl; // address 0xAA621
extern char NumPlayers; // address 0xAAA1A
extern char nybblearray[512]; // address 0xD71B8
extern char old_camera_change; // address 0xAB1B0
extern char OverlayFlashValue; // address 0xAAAB8
extern char paused; // address 0xAA61C
extern char phrase_top; // address 0xAAEA8
extern char ping_in_pedestrians; // address 0xAB140
extern char PingOutCivsOnly; // address 0xAA1DC
extern char playerNum; // address 0xAAC00
extern char PoolPrimData[16]; // address 0x9C074
extern char rear_only; // address 0xAAED1
extern char RecordingPads; // address 0xAA110
extern char ReplayMode; // address 0xAA620
extern char RightLight; // address 0xAAC98
extern char ScreenTitle[128]; // address 0x1CC1D8
extern char specModelValid; // address 0xAA7B0
extern char specTpages[4][12]; // address 0x9BE5C
extern char speedLimits[3]; // address 0x9BF78
extern char tracking_car; // address 0xAAD2C
extern char TransparentObject; // address 0xAA47C
extern char tsdname[128]; // address 0xE0D00
extern char VeryShinyTable[256]; // address 0xCDAC8
extern enum GAMEMODE CurrentGameMode; // address 0xAA5A8
extern enum GAMEMODE WantedGameMode; // address 0xAA5A9
extern enum GAMETYPE GameType; // address 0xAA62C
extern enum GAMETYPE StoredGameType; // address 0xAA62D
extern enum LIMBS lRoutes[5][8]; // address 0xA07C0
extern enum PAUSEMODE gMissionCompletionState; // address 0xAA78C
extern int *debugCount; // address 0xAAE34
extern int *idx; // address 0xAA97C
extern int *modelMemory; // address 0xAB238
extern int aa; // address 0xAAA74
extern int allowSpecSpooling; // address 0xAB25C
extern int allowVibration; // address 0x1C6AAC
extern int allreadydone; // address 0xAA938
extern int angle; // address 0xAAB58
extern int asf; // address 0xE9158
extern int attract_number; // address 0xAA460
extern int AttractMode; // address 0xAA648
extern int autobrakeon; // address 0xAA5C0
extern int AutoDirect; // address 0xAAD44
extern int bAllreadyRotated; // address 0xAA7B4
extern int baseSpecCP; // address 0xAAB30
extern int basic_car_interest; // address 0xAB124
extern int bAvoidBomb; // address 0xAA8E4
extern int bAvoidTanner; // address 0xAA8E0
extern int bCdIconSetup; // address 0x1C6AC0
extern int bDisplayBones; // address 0xAA808
extern int bDoingCarSelect; // address 0x1C6A80
extern int bDoingCutSelect; // address 0x1C699C
extern int bDoingScores; // address 0x1C6994
extern int bDoingShadow; // address 0xAA7B8
extern int bDoneAllready; // address 0x1C6AA4
extern int bDrawExtra; // address 0x1C6A88
extern int bFreezeAnimation; // address 0xAA8CC
extern int bInCutSelect; // address 0x1C6A78
extern int bKilled; // address 0xAA8EC
extern int bKillTanner; // address 0xAA8D8
extern int bLoadedAllMC; // address 0xAA804
extern int bMissionSelect; // address 0x1C6AA8
extern int bMissionTitleFade; // address 0xAA5FC
extern int bodySelect; // address 0xAA124
extern int bodyShiftValue; // address 0xAA810
extern int boneIdvals[15]; // address 0xA0F40
extern int boxOverlap; // address 0xAAB00
extern int BPMLimit; // address 0xAB3CC
extern int bPower; // address 0xAA904
extern int bRedrawFrontend; // address 0x1C6A98
extern int bRequestedKey; // address 0x1C6AA0
extern int bReturnToMain; // address 0xAA5A4
extern int bReverseAnimation; // address 0xAA8D0
extern int bReverseYRotation; // address 0xAA8DC
extern int bScreenSetup; // address 0x1C6A8C
extern int bStopTanner; // address 0xAA8F0
extern int bTannerSitting; // address 0xAA8BC
extern int buildingsFound; // address 0xAAD5C
extern int bWantCDReset; // address 0x1C6A9C
extern int cak; // address 0xAAA28
extern int camera_cell_x; // address 0xAAFF0
extern int camera_cell_z; // address 0xAAFF4
extern int CameraCar; // address 0xAA65C
extern int CameraCnt; // address 0xAAF90
extern int CAR_PAUSE_START; // address 0xAA1E0
extern int carAngle; // address 0xAA1FC
extern int CarAvailability[4][10]; // address 0x1C6AEC
extern int CarLightFadeBack; // address 0xAACF8
extern int CarLightFadeFront; // address 0xAACB0
extern int carnum; // address 0xAAB88
extern int carSelection; // address 0x1C6A04
extern int cell_object_index; // address 0xAA1A8
extern int cell_objects_add[5]; // address 0xD6FA0
extern int cell_slots_add[5]; // address 0xD73C8
extern int cells_across; // address 0xAA6D4
extern int cells_down; // address 0xAA6D8
extern int checkFrames; // address 0xAA1B4
extern int chunk_complete; // address 0xAB2E0
extern int citystart[8]; // address 0xE0B48
extern int civ_smoke_enabled; // address 0xAA188
extern int cJerichoVNumbers[7]; // address 0xD7D80
extern int ClearCameras; // address 0xAA45C
extern int closeEncounter; // address 0xAA1EC
extern int collision_boxes_set; // address 0xAB110
extern int combointensity; // address 0xAB150
extern int cop_respawn_timer; // address 0xAAC50
extern int CopsAllowed; // address 0xAAC38
extern int copsAreInPursuit; // address 0xAAC3C
extern int CopsCanSeePlayer; // address 0xAAC30
extern int coptrackpos[8]; // address 0x9F064
extern int corner; // address 0xAA1F4
extern int crateoffset; // address 0xAA5E0
extern int cTannerVNumbers[24]; // address 0xD7D20
extern int currCity; // address 0x1C6A68
extern int current_barrel_region_xcell; // address 0xAAFF8
extern int current_barrel_region_zcell; // address 0xAAFFC
extern int current_camera_angle; // address 0xAA160
extern int current_cell_x; // address 0xAB01C
extern int current_cell_z; // address 0xAB020
extern int current_music_id; // address 0xAB244
extern int current_object_computed_value; // address 0xAAF28
extern int current_region; // address 0xAB028
extern int currentAngle; // address 0xAABCC
extern int CurrentCh; // address 0xAB3EC
extern int CurrentPlayerView; // address 0xAA638
extern int currentRoadId; // address 0xAABE8
extern int currMission; // address 0x1CC544
extern int currPlayer; // address 0x1C6A7C
extern int currSelIndex; // address 0x1C6A84
extern int CursorX; // address 0xAAD24
extern int CursorY; // address 0xAAD28
extern int CutAmounts[5]; // address 0x1C69B0
extern int CutAmountsTotal[5]; // address 0x1C69C4
extern int CutsceneEventTrigger; // address 0xAA270
extern int CutsceneFrameCnt; // address 0xAA26C
extern int cutSelection; // address 0x1C6998
extern int cycle_phase; // address 0xAAAA8
extern int damOffset; // address 0xAB2A0
extern int DawnCount; // address 0xAAFA8
extern int dd; // address 0xAAA78
extern int de; // address 0xAAA7C
extern int debugNode[2]; // address 0xAAE48
extern int debugOffset; // address 0xAAE3C
extern int debugRotation; // address 0xAA570
extern int debugSpeed; // address 0xAAE30
extern int distanceReturnedLog[8]; // address 0xF27A0
extern int DistanceTriggerCarMoves; // address 0xAA518
extern int distFromCentre; // address 0xAABF8
extern int distFurthestCivCarSq; // address 0xAAB5C
extern int distLogIndex; // address 0xE9AB0
extern int distObstacle; // address 0xAABC8
extern int DM_CIRCLE[16][2][2]; // address 0x10EB70
extern int DoExtraWorkForNFrames; // address 0xE99AC
extern int done; // address 0xAB2A4
extern int DoNotSwap; // address 0xAAA1C
extern int doSpooling; // address 0xAA9FC
extern int doWheels; // address 0xAA5D0
extern int DVL; // address 0xAB3D0
extern int DVR; // address 0xAB3DC
extern int dx; // address 0xAABB8
extern int dy; // address 0xAABBC
extern int dz; // address 0xAABC0
extern int editing_existing_camera; // address 0xAA454
extern int EditMode; // address 0xAA440
extern int ElTrainData[83]; // address 0x9E770
extern int environmenttpage; // address 0xAB35C
extern int error_bounds; // address 0xAAA00
extern int EVENT_CAR_SPEED; // address 0xAA200
extern int event_models_active; // address 0xAAE50
extern int ExBombTimer; // address 0xAAEDC
extern int ExBoxDamage; // address 0xAAED8
extern int ExLastCarX; // address 0xAAEEC
extern int ExLastCarXVel; // address 0xAAEE4
extern int ExLastCarZ; // address 0xAAEF0
extern int ExLastCarZVel; // address 0xAAEE8
extern int FadingScreen; // address 0xAA5F8
extern int fakeOtherPlayer; // address 0xAA5AC
extern int fasterToggle; // address 0xAAD74
extern int FastForward; // address 0xAA458
extern int FastForwardCameraCnt; // address 0xAA464
extern int FelonyDecreaseTime; // address 0xAAE5C
extern int FelonyDecreaseTimer; // address 0xAAE64
extern int FelonyIncreaseTime; // address 0xAAE60
extern int FelonyIncreaseTimer; // address 0xAAE68
extern int feVariableSave[4]; // address 0x9F134
extern int first_paletised_page; // address 0xAAAD4
extern int firstDamBlock; // address 0xAB26C
extern int firstLowBlock; // address 0xAB27C
extern int frame_advance_count; // address 0xAAD40
extern int FrameCnt; // address 0xAB320
extern int frames; // address 0xAB0A4
extern int frameStart; // address 0xAAB64
extern int FrAng; // address 0xAAD60
extern int g321GoDelay; // address 0xAA794
extern int gAllowMusic; // address 0xAA9E0
extern int gAllowSfx; // address 0xAA9E4
extern int game_over; // address 0xAAFB8
extern int gameinit; // address 0xAA668
extern int GameLevel; // address 0xAA640
extern int GameNum; // address 0x1C6CE0
extern int gBatterPlayer; // address 0xAA218
extern int gBobIndex; // address 0xAAF98
extern int gCameraAngle; // address 0xAA16C
extern int gCameraDistance; // address 0xAA164
extern int gCameraMaxDistance; // address 0xAA168
extern int gCantDrive; // address 0xAA768
extern int gcar_num; // address 0xAACD4
extern int gCarPoolsToDraw; // address 0xAACF0
extern int gCarWithABerm; // address 0xAA764
extern int gChaseNumber; // address 0xAA598
extern int gCopCarTheftAttempted; // address 0xAA79C
extern int gCopDesiredSpeedScale; // address 0xAA21C
extern int gCopDifficultyLevel; // address 0xAA64C
extern int gCopMaxPowerScale; // address 0xAA220
extern int gCopRespawnTime; // address 0xAA228
extern int gCurrentChaseNumber; // address 0xAA634
extern int gCurrentMissionNumber; // address 0xAA630
extern int gCurrentResidentSlot; // address 0xAA18C
extern int gCurrentZ; // address 0xAB0BC
extern int gCutsceneAtEnd; // address 0xAA284
extern int gDisplayPosition; // address 0xAA6E0
extern int gDoBonnets; // address 0xAA184
extern int gDoCrates; // address 0xAAFA0
extern int gDoLeaves; // address 0xAA2A0
extern int gDontPingInCops; // address 0xAA790
extern int gDontResetCarDamage; // address 0xAA7A4
extern int gDoShinyCars; // address 0xAA3FC
extern int gDoSmoke; // address 0xAA29C
extern int gDraw3DArrowBlue; // address 0xAAA2C
extern int gDrawLowerSky; // address 0xAA9A0
extern int gDrawPauseMenus; // address 0xAA864
extern int gDualShockMax; // address 0xAA838
extern int gEffectsTimer; // address 0xAACCC
extern int gFlareScale; // address 0xAA294
extern int gForceLowDetailCars; // address 0xAAB2C
extern int gFurthestMission; // address 0xAA5B4
extern int gGotInStolenCar; // address 0xAA798
extern int gHaveStoredData; // address 0xAA6F8
extern int gIdleReplay; // address 0xAA5BC
extern int gInFrontend; // address 0xAA66C
extern int gInGameChaseActive; // address 0xAA264
extern int gInGameCutsceneActive; // address 0xAA268
extern int gInGameCutsceneDelay; // address 0xAA278
extern int gInGameCutsceneID; // address 0xAA27C
extern int gInvincibleCar; // address 0xAA67C
extern int gLapTimes[2][5]; // address 0xD7CC8
extern int gLightsOn; // address 0xAAFA4
extern int gLoadedMotionCapture; // address 0xAAF1C
extern int gLoadedOverlay; // address 0xAAFAC
extern int gLoadedReplay; // address 0xAA670
extern int gLockPickingAttempted; // address 0xAA7A0
extern int gMasterVolume; // address 0xAA9DC
extern int gMinimumCops; // address 0xAA210
extern int gMissionLadderPos; // address 0xAA5B0
extern int gMultiplayerLevels; // address 0xAAA20
extern int gMusicType; // address 0xAB064
extern int gMusicVolume; // address 0xAA9D8
extern int gNextRainDrop; // address 0xAACC4
extern int gNight; // address 0xAA684
extern int gNumCitiesOpen; // address 0xAA628
extern int gNumRaceTrackLaps; // address 0xAA784
extern int goFaster; // address 0xAA4A4
extern int gOutOfTape; // address 0xAA118
extern int gPlayerCarDamage; // address 0xAA5C4
extern int gPlayerCarLights; // address 0xAA288
extern int gPlayerDamageFactor; // address 0xAB078
extern int gPlayerImmune; // address 0xAA680
extern int gPlayerWithTheFlag; // address 0xAA760
extern int gPuppyDogCop; // address 0xAA214
extern int gRandomChase; // address 0xAA59C
extern int groundDebrisIndex; // address 0xAA480
extern int gShadowTextureNum; // address 0xAB184
extern int gShadowTexturePage; // address 0xAB188
extern int gShowMap; // address 0xAA674
extern int gShowPlayerDamage; // address 0xAAF64
extern int gSinkingTimer; // address 0xAAF80
extern int gSoundMode; // address 0xAA9B0
extern int gStartOnFoot; // address 0xAA750
extern int gStopPadReads; // address 0xAA688
extern int gSubGameNumber; // address 0xAA5A0
extern int gSubtitles; // address 0xAA6A0
extern int gSurround; // address 0xAA9B4
extern int gTannerActionNeeded; // address 0xAA75C
extern int gThePlayerCar; // address 0xAA274
extern int gTimeInWater; // address 0xAAECC
extern int gTimeOfDay; // address 0xAA754
extern int gTrailblazerConeCount; // address 0xAA4B4
extern int gTrailblazerConeIndex; // address 0xAA4B8
extern int gTunnelNum; // address 0xAA9AC
extern int GuitarType; // address 0xAA068
extern int gUseCopModel; // address 0xAA4C4
extern int gVibration; // address 0xAA678
extern int gWantNight; // address 0xAA5B8
extern int gWeather; // address 0xAA758
extern int handle; // address 0xAAF4C
extern int HavanaFerryData[12]; // address 0x9E8E4
extern int HavanaMiniData[4]; // address 0x9E92C
extern int headposition; // address 0xAA17C
extern int headtarget; // address 0xAA178
extern int HitLeadCar; // address 0xAAFB0
extern int horizonadd; // address 0xAA204
extern int iAllowWatch; // address 0xAA8C4
extern int iCurrBone; // address 0xAB0B8
extern int idle_timer; // address 0x1CBDA8
extern int iFreezeTimer; // address 0xAA8C8
extern int iIdleTimer; // address 0xAA8E8
extern int impulse; // address 0xAB390
extern int initarea; // address 0xAB000
extern int jericho_in_back; // address 0xAB050
extern int joints; // address 0xAB0AC
extern int JP_Do_Nothing; // address 0xAB3E0
extern int JPError; // address 0xAAA60
extern int JPPer; // address 0xAAA80
extern int jtest53; // address 0xAA174
extern int JustReturnedFromCutscene; // address 0xAA280
extern int l1; // address 0xAA208
extern int l2; // address 0xAA20C
extern int laneFit[2]; // address 0xAABA0
extern int last_size; // address 0xAB2D4
extern int last_track_state; // address 0xAA5CC
extern int lastCarCameraView; // address 0xAA93C
extern int lastCleanBlock; // address 0xAB29C
extern int lastDistanceFound; // address 0xE9AC8
extern int LastHeading; // address 0xAAC34
extern int lead_car; // address 0xAA654
extern int leadAILoaded; // address 0xAA690
extern int leadAIRequired; // address 0xAA68C
extern int leadCarId; // address 0xAAF88
extern int lengthDamBlock; // address 0xAB298
extern int lengthLowBlock; // address 0xAB2A8
extern int Level_NumAnimatedObjects[8]; // address 0x9B674
extern int LevelTab[32]; // address 0xA1EF0
extern int LiftingBridges[55]; // address 0x9EC90
extern int LightIndex; // address 0xAACF4
extern int lightning; // address 0xAA484
extern int LightningTimer; // address 0xAA28C
extern int LightSortCorrect; // address 0xAACA0
extern int littleBangTime; // address 0xAA5E4
extern int littleBoxRange; // address 0xAA14C
extern int loadbank_read; // address 0xAB278
extern int loadbank_write; // address 0xAB2CC
extern int LoadedArea; // address 0xAB2B8
extern int LoadingArea; // address 0xAA9E8
extern int localMap[41]; // address 0xECD40
extern int lowOffset; // address 0xAB2B0
extern int main_cop_light_pos; // address 0xAACE0
extern int mainScreenLoaded; // address 0x1C6ABC
extern int makeNextNodeCtrlNode; // address 0xAA1E8
extern int map_x_shift; // address 0xAA100
extern int map_z_shift; // address 0xAA104
extern int max_pedestrians; // address 0xAA8D4
extern int maxCameraDist; // address 0xAAB14
extern int maxCivCars; // address 0xAAC10
extern int maxCopCars; // address 0xAAC0C
extern int maxParkedCars; // address 0xAABE0
extern int maxPlayerCars; // address 0xAABEC
extern int MaxPlayerDamage[2]; // address 0xAA76C
extern int maxrevdrop; // address 0xAA578
extern int maxrevrise; // address 0xAA57C
extern int maxSeated; // address 0xAB130
extern int MaxSpecCluts; // address 0xAB358
extern int maxSteer; // address 0xAA1B8
extern int menuactive; // address 0xAAD1C
extern int MenuOffset; // address 0xAAD14
extern int MIN_TRIPOD_CAMERA_HEIGHT; // address 0xAA43C
extern int minBoxSize; // address 0xAA150
extern int minmaxSelections[4][2]; // address 0x1C6B90
extern int missionSetup; // address 0x1C6A6C
extern int models_ready; // address 0xAB254
extern int MotionCaptureData[24]; // address 0xD8E40
extern int mScale; // address 0xAA128
extern int mTheta; // address 0xAAB08
extern int multiplayerregions[4]; // address 0xDEE20
extern int music_is_loading; // address 0xAA9F8
extern int music_paused; // address 0xAA9C4
extern int my_sly_var; // address 0xAB148
extern int myPalette; // address 0xAA194
extern int myVal; // address 0xAA80C
extern int n_sample_chunks; // address 0xAB224
extern int na; // address 0xE915C
extern int new_area_location; // address 0xAB260
extern int newAccel; // address 0xAA1BC
extern int newExit; // address 0xAABC4
extern int NewLamp[21]; // address 0xC1B28
extern int next_debris; // address 0xAACB4
extern int next_leaf; // address 0xAACE8
extern int next_smoke; // address 0xAAC9C
extern int NextDamagedLamp; // address 0xAACEC
extern int NextDamagedPmeter; // address 0xAACBC
extern int NightAmbient; // address 0xAAF68
extern int NoRainIndoors; // address 0xAACC8
extern int NoTextureMemory; // address 0xAB344
extern int nperms; // address 0xAB354
extern int nsectors; // address 0xAB288
extern int nspecpages; // address 0xAB340
extern int num_active_cars; // address 0xAAEC8
extern int num_anim_objects; // address 0xAAAB0
extern int num_cars_drawn; // address 0xAAB34
extern int num_cycle_obj; // address 0xAAAB4
extern int num_extra_boxes_set; // address 0xAB114
extern int Num_LevCycleObjs[4]; // address 0x9B4E4
extern int num_models_in_pack; // address 0xAB00C
extern int num_regions; // address 0xAAFE4
extern int num_samples; // address 0xAB23C
extern int num_straddlers; // address 0xAB02C
extern int num_tyre_tracks[4]; // address 0xDAA48
extern int numActiveCops; // address 0xAAC54
extern int NumAreas; // address 0xAB268
extern int numCivCars; // address 0xAAB4C
extern int numCopCars; // address 0xAAB48
extern int NumDriver2Curves; // address 0xAAA88
extern int NumDriver2Junctions; // address 0xAAA9C
extern int NumDriver2Straights; // address 0xAAA98
extern int numInactiveCars; // address 0xAAB60
extern int numPadsConnected; // address 0x1C6AB0
extern int numParkedCars; // address 0xAABE4
extern int numPlayerCars; // address 0xAABF0
extern int numPlayersToCreate; // address 0xAA940
extern int NumReplayStreams; // address 0xAA10C
extern int numRoadblockCars; // address 0xAAB7C
extern int numSpritesFound; // address 0xAAD50
extern int NumTempJunctions; // address 0xAB068
extern int ObjectDrawnCounter; // address 0xAA6A4
extern int old_region; // address 0xAAFD8
extern int oldActionSet; // address 0x1C6B8C
extern int oldActionVal; // address 0x1CC560
extern int oldMusicLevel; // address 0x1CC580
extern int oldSfxLevel; // address 0x1CC258
extern int oldWeather; // address 0xAB118
extern int OutOfSightCount; // address 0xAAC2C
extern int OverlayOccupancyGrid; // address 0xE91A0
extern int pad_connected; // address 0xAA834
extern int pad_recorded; // address 0xAA114
extern int padsConnected[2]; // address 0x1C6AB4
extern int palnumber; // address 0xAA814
extern int PALType; // address 0xAB3BC
extern int pathAILoaded; // address 0xAA694
extern int pathFrame; // address 0xF1B00
extern int pathFrames; // address 0xE99A8
extern int pathIterations; // address 0xF27C0
extern int pathStraight; // address 0xAAC48
extern int pauseflag; // address 0xAA650
extern int persuit_mode; // address 0xAA63C
extern int pinginPedAngle; // address 0xAA8C0
extern int player_position_known; // address 0xAAC4C
extern int PlayerCar; // address 0xAA658
extern int PlayerCarModel; // address 0xAA644
extern int playerDying; // address 0xAAF54
extern int playerghost; // address 0xAA5D4
extern int playerhitcopsanyway; // address 0xAA5D8
extern int playerTargetDistanceSq; // address 0xE9ACC
extern int PlayMode; // address 0xAAD34
extern int PolySizes[56]; // address 0xA17C0
extern int powerCounter; // address 0xAA908
extern int pvs_cells_rejected; // address 0xAB010
extern int pvs_objects_rejected; // address 0xAAFE0
extern int pvs_square; // address 0xAAFDC
extern int pvs_square_sq; // address 0xAB014
extern int quick_replay; // address 0xAAD30
extern int quickSpool; // address 0xAB21C
extern int radius; // address 0xAAB8C
extern int region_buffer_xor; // address 0xAAA94
extern int region_x; // address 0xAB004
extern int region_z; // address 0xAB008
extern int regions_across; // address 0xAB024
extern int regions_down; // address 0xAAFE8
extern int regions_unpacked[4]; // address 0xD73B8
extern int ReplayContinue; // address 0xAAD3C
extern int ReplaySize; // address 0xAA108
extern int requestCopCar; // address 0xAAC58
extern int requestRoadblock; // address 0xAAB98
extern int requestStationaryCivCar; // address 0xAABF4
extern int RioFerryData[6]; // address 0x9E914
extern int road_c; // address 0xECD38
extern int road_s; // address 0xECD3C
extern int roadAhead[41]; // address 0xECDE8
extern int roadblockCount; // address 0xAAC04
extern int roadblockDelay; // address 0xAA1C0
extern int roadblockDelayDiff[3]; // address 0x9BF6C
extern int RoadMapRegions[4]; // address 0xDA0F0
extern int roadSeg; // address 0xAABA8
extern int sample_chunk; // address 0xAB258
extern int saved_counter; // address 0xAAF9C
extern int saved_leadcar_pos; // address 0xAAF70
extern int scr_z; // address 0xAAF24
extern int screen_fade_end; // address 0xAA5F0
extern int screen_fade_speed; // address 0xAA5F4
extern int screen_fade_start; // address 0xAA5EC
extern int screen_fade_value; // address 0xAA5E8
extern int ScreenDepth; // address 0xAAEB0
extern int sdLevel; // address 0xAAA90
extern int seated_count; // address 0xAB11C
extern int send_bank; // address 0xAB2AC
extern int SetFastForward; // address 0xAA444
extern int setupYet; // address 0xAA490
extern int ShinyTextureNum; // address 0xAAD90
extern int ShinyTexturePage; // address 0xAAD94
extern int sideMul; // address 0xAA1F0
extern int sideShift; // address 0xAA1F8
extern int sizeof_cell_object_computed_values; // address 0xAAB38
extern int skyFade; // address 0xAB1A8
extern int slotsused; // address 0xAB384
extern int slowWallTests; // address 0xE913C
extern int SmashablesHit; // address 0xAACD0
extern int smoke_count[4]; // address 0xDB098
extern int SmokeCnt; // address 0xAA298
extern int Song_ID; // address 0xAA9D0
extern int specBlocksToLoad; // address 0xAAA0C
extern int SpecialByRegion[4][20]; // address 0xA1AE0
extern int specialState; // address 0xAAA08
extern int specSpoolComplete; // address 0xAB250
extern int speed1[3]; // address 0x9C000
extern int speed2[3]; // address 0x9C00C
extern int spool_regioncounter; // address 0xAB218
extern int spool_regionpos; // address 0xAB230
extern int spoolactive; // address 0xAB240
extern int spoolcounter; // address 0xAB270
extern int spoolerror; // address 0xAB22C
extern int SpoolLumpOffset; // address 0xAB214
extern int spoolpos; // address 0xAB290
extern int spoolpos_reading; // address 0xAA9EC
extern int spoolpos_writing; // address 0xAA9F0
extern int spoolseek; // address 0xAB2DC
extern int sprite_shadow; // address 0xAA478
extern int spuaddress; // address 0xAB220
extern int startSpecSpool; // address 0xAB2D0
extern int StreakCount1; // address 0xAACB8
extern int switch_detail_distance; // address 0xAA190
extern int TAIL_GETTINGCLOSE; // address 0xAA778
extern int TAIL_GETTINGFAR; // address 0xAA77C
extern int TAIL_TOOCLOSE; // address 0xAA774
extern int TAIL_TOOFAR; // address 0xAA780
extern int Tangle; // address 0xAB0A0
extern int tannerDeathTimer; // address 0xAA610
extern int tannerTurn; // address 0xAA900
extern int tannerTurnMax; // address 0xAA8FC
extern int tannerTurnStep; // address 0xAA8F8
extern int TargetCar; // address 0xAA660
extern int tcRoad; // address 0xAA4A0
extern int tcRoof; // address 0xAA498
extern int tcWall; // address 0xAA49C
extern int test123; // address 0xAAB6C
extern int test23; // address 0xAA1D8
extern int test3; // address 0xAAE70
extern int test4; // address 0xAAE74
extern int test42; // address 0xAAB68
extern int test5; // address 0xAAE78
extern int test555; // address 0xAAB74
extern int test6; // address 0xAAE7C
extern int test7; // address 0xAAE80
extern int test777; // address 0xAA81C
extern int test8; // address 0xAAE84
extern int testCar; // address 0xAA1E4
extern int testNum; // address 0xAABD0
extern int testNumPingedOut; // address 0xAA1B0
extern int testRadius; // address 0xAA818
extern int texamount; // address 0xAB380
extern int texture_is_icon; // address 0xAAA30
extern int texture_lump_start; // address 0xAB37C
extern int ThisMotion; // address 0xAB098
extern int time_taken; // address 0xAAD18
extern int times; // address 0xAAA04
extern int TimeSinceLastSpeech; // address 0xAAEAC
extern int TimeToWay; // address 0xAAAF0
extern int tmpNewLane[2]; // address 0xAAB40
extern int tmpNewRoad[2]; // address 0xAAB50
extern int toggleCam; // address 0xAA22C
extern int tpage_amount; // address 0xAB360
extern int tpage_texamts[128]; // address 0xE0DD0
extern int trayoffset; // address 0xAA180
extern int TriggerBomb; // address 0xAAEE0
extern int tsetcounter; // address 0xAB248
extern int tsetinfo[32]; // address 0xDED90
extern int tsetpos; // address 0xAB264
extern int tt; // address 0xAAA70
extern int tunnelDir[3][2]; // address 0xA1A4C
extern int type; // address 0xAA9F4
extern int tyre_track_offset[4]; // address 0xDCCA8
extern int units_across_halved; // address 0xAAFD4
extern int units_down_halved; // address 0xAAFEC
extern int unpack_cellptr_flag; // address 0xAB2E4
extern int unpack_roadmap_flag; // address 0xAB2C8
extern int useStoredPings; // address 0xAA1AC
extern int VABID; // address 0xAA9D4
extern int variable_weather; // address 0xAA290
extern int vblcounter; // address 0xAB308
extern int vcount; // address 0xAAD6C
extern int VegasParkedTrains[3]; // address 0x9E8D8
extern int VegasTrainData[7]; // address 0x9E8BC
extern int view_dist; // address 0xAB018
extern int vStored; // address 0xAA7BC
extern int wantedCar[2]; // address 0xAA698
extern int way_distance; // address 0xAAAE0
extern int wetness; // address 0xAACC0
extern int whichCP; // address 0xAAB28
extern int wibblewibblewoo; // address 0xAAB04
extern int xa_timeout; // address 0xAAF30
extern int XM_FrameSpeed; // address 0xAB3D8
extern int XM_HA; // address 0xAAA6C
extern int XM_NSA; // address 0xAAA68
extern int XM_SCAN; // address 0xAAA5C
extern int XMTime1; // address 0xAB3B0
extern int XMTime2; // address 0xAB3B4
extern int XMTime3; // address 0xAB3B8
extern int zVal; // address 0xAA7C0
extern long *savemapinfo; // address 0xAA5DC
extern long bankaddr[2]; // address 0xAB1C0
extern long dummylong[3]; // address 0xA1AC4
extern long dunyet[32][2]; // address 0xE99B0
extern long force[4]; // address 0xA1720
extern long gHubcapTime; // address 0xAAD00
extern long levelstartpos[8][4]; // address 0xA1740
extern long point[4]; // address 0xA1730
extern short *RoadMapDataRegions[4]; // address 0xDA0E0
extern short CurrentJunction; // address 0xAA624
extern short CurrentRoad; // address 0xAA622
extern short cycle_timer; // address 0xAAAAC
extern short debris_alloc[60]; // address 0xC1C28
extern short fePad; // address 0x1CC5D4
extern short fontclutid; // address 0xAB15C
extern short fonttpage; // address 0xAB168
extern short gPlayerCar0ShinyFaces[38]; // address 0x9E724
extern short gRainAlloc[180]; // address 0xC2A38
extern short initialOccurrenceDelay[12]; // address 0x9EE00
extern short initialReccurrenceDelay[12]; // address 0x9EE18
extern short iVABID[8]; // address 0xA1F98
extern short leaf_alloc[50]; // address 0xBF8D8
extern short light_col; // address 0xAACE6
extern short loading_region[4]; // address 0xAB2C0
extern short padd; // address 0xAB324
extern short paddp; // address 0xAB304
extern short pedestrianFelony; // address 0xAA224
extern short playerLastRoad; // address 0xAAE6C
extern short PlayerWaypoints; // address 0xAAD20
extern short smoke_alloc[80]; // address 0xC1A58
extern short specialSlot; // address 0xAB350
extern short specspooldata[3]; // address 0xAAA34
extern short validExitIdx[4]; // address 0xAABB0
extern short XMSongIDs[24]; // address 0xA1FA8
extern short XMSPU_SFX[24]; // address 0xA1FD8
extern struct CIV_PING civPingTest; // address 0x9BF7C
extern struct tNodeDir ends[6][2]; // address 0xE9108
extern struct tNodeDir dirs[6]; // address 0xE9140
extern struct __tunnelinfo tunnels; // address 0xD0220
extern struct _CAR_DATA *active_car_list[20]; // address 0xD1278
extern struct _CAR_DATA *carToGetIn; // address 0xAB13C
extern struct _CAR_DATA *collision_car_ptr[8]; // address 0xD96B8
extern struct _CAR_DATA *gBombTargetVehicle; // address 0xAA148
extern struct _CAR_DATA *jcam; // address 0xAAB18
extern struct _CAR_DATA *pcdTanner; // address 0xAB138
extern struct _CAR_DATA *pCivCarToGetIn; // address 0xAA930
extern struct _CAR_DATA *targetVehicle; // address 0xAAC5C
extern struct _CAR_DATA car_data[22]; // address 0xD12E0
extern struct _CAR_DATA currentCar; // address 0xBD210
extern struct _EVENT *firstEvent; // address 0xAAE38
extern struct _ExOBJECT explosion[5]; // address 0xD5498
extern struct _HANDLING_TYPE handlingType[7]; // address 0x9F144
extern struct _MISSION *MissionHeader; // address 0xAB06C
extern struct _PERCENTAGE_BAR DamageBar; // address 0xAB860
extern struct _PERCENTAGE_BAR FelonyBar; // address 0xAB880
extern struct _PERCENTAGE_BAR Player2DamageBar; // address 0xAB820
extern struct _PERCENTAGE_BAR PlayerDamageBar; // address 0xAB8A0
extern struct _PERCENTAGE_BAR ProxyBar; // address 0xAB840
extern struct _PING_PACKET *PingBuffer; // address 0xAAAF8
extern struct _PLAYER player[8]; // address 0xD97A0
extern struct _sdPlane *dbSurfacePtr; // address 0xAAA48
extern struct _sdPlane sea; // address 0x9B388
extern struct _TARGET *MissionTargets; // address 0xAB07C
extern struct ACTIVE_CHEATS ActiveCheats; // address 0xAAEF8
extern struct ACTIVE_CHEATS AvailableCheats; // address 0xAAEFC
extern struct ANIMATED_OBJECT *Level_AnimatingObjectPtrs[4]; // address 0x9B664
extern struct ANIMATED_OBJECT Lev0AnimObjects[9]; // address 0x9B4F4
extern struct ANIMATED_OBJECT Lev1AnimObjects[5]; // address 0x9B584
extern struct ANIMATED_OBJECT Lev2AnimObjects[5]; // address 0x9B5D4
extern struct ANIMATED_OBJECT Lev3AnimObjects[4]; // address 0x9B624
extern struct AreaDataStr *AreaData; // address 0xAB24C
extern struct BLOCKINFO s_copyBlockInfo; // address 0x10EE38
extern struct BONE Skel[23]; // address 0xA0924
extern struct BOTCH botch[38]; // address 0x1C6BB0
extern struct BOUND_BOX bbox[20]; // address 0xD50E8
extern struct BOXINFO theBox; // address 0xA03D0
extern struct CAR_COLLISION_BOX collision_box[8]; // address 0xD96D8
extern struct CAR_COLLISION_BOX extra_collision_boxes[5]; // address 0xD9668
extern struct CAR_COLLISION_BOX tanner_collision_box; // address 0xD9648
extern struct CAR_COSMETICS car_cosmetics[5]; // address 0xD4C48
extern struct CAR_COSMETICS src_cosmetics[20]; // address 0x9F160
extern struct CAR_MODEL NewCarModel[5]; // address 0xACBE0
extern struct CAR_MODEL NewLowCarModel[5]; // address 0xB8838
extern struct CAR_POLY pbf[2001]; // address 0xACCA0
extern struct CdlFILE currentfileinfo; // address 0xE0B30
extern struct CELL_DATA *cells; // address 0xAAF20
extern struct CELL_OBJECT **coplist; // address 0xAB0C8
extern struct CELL_OBJECT *EventCop; // address 0xAAE40
extern struct CELL_OBJECT cell_object_buffer[1024]; // address 0xB90F8
extern struct CELL_OBJECT ground_debris[16]; // address 0xCD0D0
extern struct CHANNEL_DATA channels[16]; // address 0xDE4F8
extern struct CHEATS cheats; // address 0xD12C8
extern struct CIV_ROUTE_ENTRY *startNode; // address 0xAABFC
extern struct CIV_ROUTE_ENTRY *tstNode1; // address 0xAABD4
extern struct CIV_ROUTE_ENTRY *tstNode2; // address 0xAABD8
extern struct ControllerPacket g_controllerData[2]; // address 0x10EC9C
extern struct COP_DATA gCopData; // address 0x9BFD4
extern struct COP_SIGHT_DATA copSightData; // address 0xAAC40
extern struct CUTSCENE_BUFFER CutsceneBuffer; // address 0xBD898
//extern struct CVECTOR debris_colour[4][31]; // address 0x9C098
extern struct CVECTOR otherCol; // address 0x1C6CF8
extern struct CVECTOR scoreCol; // address 0x1C6CF4
extern struct CYCLE_OBJECT *Lev_CycleObjPtrs[4]; // address 0x9B4D4
extern struct CYCLE_OBJECT Lev0[2]; // address 0x9B394
extern struct CYCLE_OBJECT Lev1[1]; // address 0x9B3BC
extern struct CYCLE_OBJECT Lev2[12]; // address 0x9B3D0
extern struct CYCLE_OBJECT Lev3[1]; // address 0x9B4C0
extern struct DAMAGED_LAMP damaged_lamp[5]; // address 0xC1BB0
extern struct DAMAGED_OBJECT damaged_object[9]; // address 0xC2888
extern struct DB *current; // address 0xAB318
extern struct DB *last; // address 0xAB330
extern struct DB *MPcurrent[2]; // address 0xAB328
extern struct DB *MPlast[2]; // address 0xAB310
extern struct DB MPBuff[2][2]; // address 0xE0930
extern struct DEBRIS debris[60]; // address 0xC10F8
extern struct DENTUVS *gTempCarUVPtr; // address 0xAB154
extern struct DENTUVS gTempHDCarUVDump[20][255]; // address 0xCA020
extern struct DENTUVS gTempLDCarUVDump[20][134]; // address 0xCB410
extern struct DISPENV load_disp; // address 0xD56B8
extern struct DR_LOAD cyclecluts[12]; // address 0xAB418
extern struct DR_MOVE In; // address 0x1CC548
extern struct DR_MOVE Out; // address 0x1CC568
extern struct DRAW_MODE draw_mode_ntsc; // address 0xA1C30
extern struct DRAW_MODE draw_mode_pal; // address 0xA1C20
extern struct DRAWENV load_draw; // address 0xD5658
extern struct DRIVER2_CURVE *Driver2CurvesPtr; // address 0xAAA8C
extern struct DRIVER2_CURVE *testCrv; // address 0xAA1D4
extern struct DRIVER2_CURVE *tmpCrv[2]; // address 0xAAB80
extern struct DRIVER2_JUNCTION *Driver2JunctionsPtr; // address 0xAAAA4
extern struct DRIVER2_STRAIGHT *Driver2StraightsPtr; // address 0xAAAA0
extern struct DRIVER2_STRAIGHT *tmpStr[2]; // address 0xAAB90
extern struct DVECTOR *outvertices; // address 0xAA98C
extern struct DVECTOR slot_clutpos[19]; // address 0xE0D80
extern struct DVECTOR slot_tpagepos[19]; // address 0xE0FD0
extern struct EventCarriage carriageData[10]; // address 0xCDF70
extern struct EventGlobal events; // address 0xCDF60
extern struct FE_FONT feFont; // address 0x1CBDD0
extern struct FELONY_DATA felonyData; // address 0xBD5D0
extern struct FELONY_VALUE initialFelonyValue[12]; // address 0x9EE30
extern struct GARAGE_DOOR CurrentGarage; // address 0xAB748
extern struct GEAR_DESC geard[2][4]; // address 0x9EFC4
extern struct HUBCAP gHubcap; // address 0xC9478
extern struct LAMP_STREAK Known_Lamps[21]; // address 0xC0F00
extern struct LEAD_PARAMETERS LeadValues; // address 0xECE90
extern struct LEAF leaf[50]; // address 0xC1FC0
extern struct MATRIX *current_inv_matrix; // address 0xAAD58
extern struct MATRIX *current_matrix; // address 0xAAD4C
extern struct MATRIX aspect; // address 0x9BFB4
extern struct MATRIX camera_matrix; // address 0xACB68
extern struct MATRIX colour_matrix; // address 0x9BF4C
extern struct MATRIX debris_mat; // address 0xC0880
extern struct MATRIX face_camera; // address 0xACB18
extern struct MATRIX face_camera_work; // address 0x9BE3C
extern struct MATRIX frustrum_matrix; // address 0xCC070
extern struct MATRIX inv_camera_matrix; // address 0xACB48
extern struct MATRIX leaf_mat; // address 0xC1D40
extern struct MATRIX light_matrix; // address 0x9BF2C
extern struct MATRIX norot; // address 0xC08A0
extern struct MATRIX save_colour_matrix; // address 0xB88D8
extern struct MATRIX save_light_matrix; // address 0xACC80
extern struct MATRIX shadowMatrix; // address 0xCC8B0
extern struct MATRIX tempmatrix; // address 0xA1904
extern struct MATRIX2 CompoundMatrix[64]; // address 0xCD1E0
extern struct MATRIX2 matrixtable[64]; // address 0xCC090
extern struct MENU_HEADER YesNoQuitHeader; // address 0xA1680
extern struct MENU_HEADER YesNoRestartHeader; // address 0xA166C
extern struct MISSION_DATA MissionEndData; // address 0xD7698
extern struct MISSION_DATA MissionStartData; // address 0xD75B0
extern struct MODEL *gBombModel; // address 0xAA144
extern struct MODEL *gBoxModelPtr; // address 0xAAF60
extern struct MODEL *gCarCleanModelPtr[5]; // address 0xD5730
extern struct MODEL *gCarDamModelPtr[5]; // address 0xD6F60
extern struct MODEL *gCarLowModelPtr[5]; // address 0xD6F78
extern struct MODEL *gCleanWheelModelPtr; // address 0xAAF94
extern struct MODEL *gDamWheelModelPtr; // address 0xAAF58
extern struct MODEL *gFastWheelModelPtr; // address 0xAAF78
extern struct MODEL *gHubcapModelPtr; // address 0xAAFC4
extern struct MODEL *gPed1HeadModelPtr; // address 0xAAF34
extern struct MODEL *gPed2HeadModelPtr; // address 0xAAF38
extern struct MODEL *gPed3HeadModelPtr; // address 0xAAF3C
extern struct MODEL *gPed4HeadModelPtr; // address 0xAAF40
extern struct MODEL *gRotorPtr; // address 0xAAFB4
extern struct MODEL *gTrailblazerConeModel; // address 0xAAD88
extern struct MODEL *modelpointers[1536]; // address 0xD5760
extern struct MODEL *pLodModels[1536]; // address 0xDF130
extern struct MODEL *pmJerichoModels[6]; // address 0xD9630
extern struct MODEL *pmTannerModels[17]; // address 0xD9758
extern struct MR_MISSION Mission; // address 0xD7C80
extern struct OUT_CELL_FILE_HEADER *cell_header; // address 0xAAF50
extern struct OUT_FONTINFO fontinfo[128]; // address 0xD9BE0
extern struct PACKED_CELL_OBJECT **pcoplist; // address 0xAB0CC
extern struct PACKED_CELL_OBJECT *cell_objects; // address 0xAAF6C
extern struct PACKED_CELL_OBJECT *spriteList[75]; // address 0xCBF40
extern struct PAD Pads[2]; // address 0xD9330
extern struct PED_DATA MainPed[23]; // address 0xA0810
extern struct PEDESTRIAN *pDrawingPed; // address 0xAB09C
extern struct PEDESTRIAN *pFreePeds; // address 0xAB128
extern struct PEDESTRIAN *pHold; // address 0xAB144
extern struct PEDESTRIAN *pPlayerPed; // address 0xAB10C
extern struct PEDESTRIAN *pUsedPeds; // address 0xAB12C
extern struct PEDESTRIAN pedestrians[28]; // address 0xD8430
extern struct PEDESTRIAN_ROADS pedestrian_roads; // address 0xD9658
extern struct PLAYBACKCAMERA *CutsceneCamera; // address 0xAA260
extern struct PLAYBACKCAMERA *LastChange; // address 0xAA450
extern struct PLAYBACKCAMERA *NextChange; // address 0xAA448
extern struct PLAYBACKCAMERA *PlaybackCamera; // address 0xAAD38
extern struct PLAYBACKCAMERA *ThisChange; // address 0xAA44C
extern struct PLAYER_SCORE gPlayerScore; // address 0xDA980
extern struct POLY_F3 *spolys; // address 0xAB180
extern struct POLY_FT3 extraDummy; // address 0x1CBDB0
extern struct POLY_FT3 HighlightDummy; // address 0x1CC5A0
extern struct POLY_FT3 ScreenDummy[8]; // address 0x1CC260
extern struct POLY_FT4 BackgroundPolys[6]; // address 0x1CBCB8
extern struct POLY_FT4 ft4TannerShadow[2]; // address 0xD91D0
extern struct POLY_FT4 ScreenPolys[8]; // address 0x1CC360
extern struct POLY_FT4 shadowPolys[2][20]; // address 0xDAA58
extern struct POLYFT4 gPoolPoly; // address 0xC29E0
extern struct POLYFT4 ShadowPolygon; // address 0xDCCD8
extern struct PSXBUTTON *pButtonStack[10]; // address 0xD0620
extern struct PSXBUTTON *pCurrButton; // address 0x1CC540
extern struct PSXBUTTON *pNewButton; // address 0x1CBCB0
extern struct PSXSCREEN *pCurrScreen; // address 0x1CC25C
extern struct PSXSCREEN *pNewScreen; // address 0x1C6D40
extern struct PSXSCREEN *pScreenStack[10]; // address 0xD05F8
extern struct PSXSCREEN PsxScreens[42]; // address 0x1C6D48
extern struct RAIN_TYPE gRain[180]; // address 0xC2BA0
extern struct RECT clutpos; // address 0xAB368
extern struct RECT fontclutpos; // address 0xAB160
extern struct RECT g_strActiveMouseArea; // address 0x10EC78
extern struct RECT mapclutpos; // address 0xAB348
extern struct RECT rectTannerWindow; // address 0xAB0B0
extern struct RECT storeRect; // address 0x1C6A90
extern struct RECT tpage; // address 0xAB338
extern struct REPLAY_PARAMETER_BLOCK *ReplayParameterPtr; // address 0xAAAEC
extern struct REPLAY_STREAM ReplayStreams[8]; // address 0xAC700
extern struct ROAD_MAP_LUMP_DATA roadMapLumpData; // address 0xDA100
extern struct ROADBLOCK Roadblock; // address 0xAC920
extern struct S_XYZ *distance; // address 0xAA984
extern struct SAMPLE_DATA samples[7][35]; // address 0xDD598
extern struct SCORE_TABLES ScoreTables; // address 0xDA110
extern struct SCREEN_LIMITS screen_limits[2]; // address 0x1C6984
extern struct SEATED_PEDESTRIANS *seated_pedestrian; // address 0xAB120
extern struct SHADOWHDR *shadow_header; // address 0xAB18C
extern struct SMASHABLE_OBJECT smashable[38]; // address 0x9B6A4
extern struct SMOKE *smoke_table; // address 0xAACA4
extern struct SMOKE smoke[80]; // address 0xBF980
extern struct SPEECH_QUEUE gSpeechQueue; // address 0xD01F8
extern struct SPL_REGIONINFO spool_regioninfo[8]; // address 0xDED10
extern struct SPOOLQ spooldata[48]; // address 0xDEE30
extern struct SPRT extraSprt; // address 0x1CC5C0
extern struct SPRT HighlightSprt; // address 0x1CC588
extern struct SPRT ScreenSprts[8]; // address 0x1CC4A0
extern struct SpuReverbAttr xm_r_attr; // address 0xE2360
extern struct SpuVoiceAttr uxm_g_s_attr; // address 0xE2320
extern struct SpuVoiceAttr xm_g_s_attr; // address 0xE1280
extern struct STOPCOPS gStopCops; // address 0xD7CF0
extern struct STREAM_SOURCE *PlayerStartInfo[8]; // address 0xBD878
extern struct SVECTOR *rotated; // address 0xAA980
extern struct SVECTOR camera_angle; // address 0xAA158
extern struct SVECTOR camverts[128]; // address 0xDCCF0
extern struct SVECTOR carDisplayOffset; // address 0xAA1A0
extern struct SVECTOR day_colours[4]; // address 0x9BEEC
extern struct SVECTOR day_vectors[4]; // address 0x9BEAC
extern struct SVECTOR debris_rotvec; // address 0xAACD8
extern struct SVECTOR delta; // address 0xAAEC0
extern struct SVECTOR globemesh[54]; // address 0xD52E8
extern struct SVECTOR gTempCarVertDump[20][132]; // address 0xC41F8
extern struct SVECTOR leaf_rotvec; // address 0xAACA8
extern struct SVECTOR moon_position[4]; // address 0xA19AC
extern struct SVECTOR night_colours[4]; // address 0x9BF0C
extern struct SVECTOR night_vectors[4]; // address 0x9BECC
extern struct SVECTOR sun_position[4]; // address 0xA198C
extern struct SVECTOR vJerichoList[102]; // address 0xD8EA0
extern struct SVECTOR vTannerList[210]; // address 0xD7DA0
extern struct SVECTOR_NOPAD *svTemp; // address 0xAB0A8
extern struct SXYPAIR *Music_And_AmbientOffsets; // address 0xAB28C
extern struct SXYPAIR *PlayerWayRecordPtr; // address 0xAAAE8
extern struct SXYPAIR tpagepos[20]; // address 0xA1EA0
extern struct TEXINF *tpage_ids[128]; // address 0xE1020
extern struct TEXTURE_DETAILS addcam; // address 0xC0A50
extern struct TEXTURE_DETAILS arm1_texture; // address 0xC1BF8
extern struct TEXTURE_DETAILS autocam; // address 0xC1CA0
extern struct TEXTURE_DETAILS bird_texture1; // address 0xC1D90
extern struct TEXTURE_DETAILS bird_texture2; // address 0xC1DA0
extern struct TEXTURE_DETAILS chasecar; // address 0xC1D60
extern struct TEXTURE_DETAILS chest1_texture; // address 0xC2A18
extern struct TEXTURE_DETAILS choosecar; // address 0xC2A08
extern struct TEXTURE_DETAILS clock; // address 0xBF940
extern struct TEXTURE_DETAILS collon_texture; // address 0xBF8C8
extern struct TEXTURE_DETAILS cop_texture; // address 0xC1B80
extern struct TEXTURE_DETAILS cross_texture; // address 0xC2878
extern struct TEXTURE_DETAILS cycle_tex[12]; // address 0xAB778
extern struct TEXTURE_DETAILS debris_texture; // address 0xC39B0
extern struct TEXTURE_DETAILS delcam; // address 0xC0EE0
extern struct TEXTURE_DETAILS digit_texture; // address 0xC1F60
extern struct TEXTURE_DETAILS drop_texture; // address 0xC1CF0
extern struct TEXTURE_DETAILS editcam; // address 0xC1BE8
extern struct TEXTURE_DETAILS fixedcam; // address 0xC1D70
extern struct TEXTURE_DETAILS flare_texture; // address 0xC1F50
extern struct TEXTURE_DETAILS forearm1_texture; // address 0xC1AF8
extern struct TEXTURE_DETAILS frameadv; // address 0xC1D80
extern struct TEXTURE_DETAILS gTyreTexture; // address 0xC1CC0
extern struct TEXTURE_DETAILS head1_texture; // address 0xC1D30
extern struct TEXTURE_DETAILS incar; // address 0xBF950
extern struct TEXTURE_DETAILS jeans_texture; // address 0xC1F70
extern struct TEXTURE_DETAILS joypad_texture; // address 0xBF8B8
extern struct TEXTURE_DETAILS lenschan; // address 0xC1DB0
extern struct TEXTURE_DETAILS lensflare_texture; // address 0xC1D20
extern struct TEXTURE_DETAILS light_pool_texture; // address 0xC29F8
extern struct TEXTURE_DETAILS light_texture; // address 0xC1F90
extern struct TEXTURE_DETAILS lightref_texture; // address 0xC1BA0
extern struct TEXTURE_DETAILS line_texture; // address 0xC1CE0
extern struct TEXTURE_DETAILS litter_texture; // address 0xBF960
extern struct TEXTURE_DETAILS lookcar; // address 0xC1CB0
extern struct TEXTURE_DETAILS moon_texture; // address 0xC1D00
extern struct TEXTURE_DETAILS movecam; // address 0xC1C18
extern struct TEXTURE_DETAILS movecampos; // address 0xC08C0
extern struct TEXTURE_DETAILS ok; // address 0xC1BD8
extern struct TEXTURE_DETAILS pad_texture; // address 0xC1B08
extern struct TEXTURE_DETAILS paper_texture; // address 0xC1FA0
extern struct TEXTURE_DETAILS dir_pause; // address 0xBF970
extern struct TEXTURE_DETAILS playcam; // address 0xC1C08
extern struct TEXTURE_DETAILS playpause; // address 0xC2A28
extern struct TEXTURE_DETAILS pool_texture; // address 0xC1D10
extern struct TEXTURE_DETAILS restart; // address 0xC1CD0
extern struct TEXTURE_DETAILS save2card; // address 0xC1F40
extern struct TEXTURE_DETAILS sea_texture; // address 0xC1B18
extern struct TEXTURE_DETAILS smoke_texture; // address 0xC2858
extern struct TEXTURE_DETAILS spark_texture; // address 0xC2868
extern struct TEXTURE_DETAILS sun_texture; // address 0xC1B90
extern struct TEXTURE_DETAILS tannerShadow_texture; // address 0xC0EF0
extern struct TEXTURE_DETAILS texturePedHead; // address 0xC29D0
extern struct TEXTURE_DETAILS trail_texture; // address 0xC1FB0
extern struct TEXTURE_DETAILS watch_texture; // address 0xC1F80
extern struct TILE tileTannerClear[2]; // address 0xD7D00
extern struct tNode dbb[3]; // address 0xE9AD0
extern struct tNode heap[201]; // address 0xF1B08
extern struct TP *tpage_position; // address 0xAB388
extern struct TRAILBLAZER_DATA *gTrailblazerData; // address 0xAA4B0
extern struct TRI_POINT *debris_rot_table[5]; // address 0x9C084
extern struct TRI_POINT debris_rot1[32]; // address 0xC0A60
extern struct TRI_POINT debris_rot2[32]; // address 0xC0BE0
extern struct TRI_POINT debris_rot3[32]; // address 0xC0D60
extern struct TRI_POINT leaf_rot[32]; // address 0xC1DC0
extern struct TRI_POINT litter_rot[32]; // address 0xC08D0
extern struct TRI_POINT_LONG *debris_data[5]; // address 0x9C33C
extern struct TRI_POINT_LONG debris1_vert; // address 0x9C288
extern struct TRI_POINT_LONG debris2_vert; // address 0x9C2AC
extern struct TRI_POINT_LONG debris3_vert; // address 0x9C318
extern struct TRI_POINT_LONG leaf_vert; // address 0x9C2D0
extern struct TRI_POINT_LONG litter_vert; // address 0x9C2F4
extern struct TYRE_TRACK track_buffer[4][64]; // address 0xDB0A8
extern struct UV shadowuv; // address 0xAB190
extern struct VECTOR *current_offset; // address 0xAAD64
extern struct VECTOR *pos; // address 0xAA988
extern struct VECTOR bangPos; // address 0xD52D8
extern struct VECTOR baseLoc; // address 0xBD520
extern struct VECTOR camera_position; // address 0x9BE2C
extern struct VECTOR CameraPos; // address 0x9BE1C
extern struct VECTOR CarTail; // address 0xBD678
extern struct VECTOR current_camera_position; // address 0xCD1D0
extern struct VECTOR currentPos; // address 0xBD4B0
extern struct VECTOR direction; // address 0xDD130
extern struct VECTOR dummy; // address 0xA18E4
extern struct VECTOR endPos; // address 0xBD4C0
extern struct VECTOR frustpos; // address 0xA18F4
extern struct VECTOR gMissionDoorPosition; // address 0x9B694
extern struct VECTOR GuitarPos; // address 0xAB768
extern struct VECTOR lastKnownPosition; // address 0xBD688
extern struct VECTOR leadcar_pos; // address 0xD5720
extern struct VECTOR lis_pos; // address 0xDE4E8
extern struct VECTOR randomLoc; // address 0xBD578
extern struct VECTOR roadblockLoc; // address 0xBD530
extern struct VECTOR searchTarget; // address 0xE9AB8
extern struct VECTOR ShadowPos; // address 0xCA010
extern struct VECTOR startPos; // address 0xBD550
extern struct VECTOR tannerLookAngle; // address 0xA1710
extern struct VECTOR targetPoint; // address 0xBD668
extern struct VECTOR testVec; // address 0xBD540
extern struct VECTOR tunnel_dim[12]; // address 0x9C50C
extern struct VECTOR tunnelPos[3][2]; // address 0xA1A64
extern struct VECTOR tyre_new_positions[4]; // address 0xDD0F0
extern struct VECTOR tyre_save_positions[4]; // address 0xDAA08
extern struct VECTOR viewer_position; // address 0xACB38
extern struct VERTEX vtab[8]; // address 0xCD9E0
extern struct XA_TRACK XAMissionMessages[4]; // address 0xE1240
extern struct XMCHANNEL *XMC; // address 0xAB3D4
extern struct XMCHANNEL *XMCU; // address 0xAB3E4
extern struct XMHEADER *mh; // address 0xAB3C0
extern struct XMHEADER *mhu; // address 0xAB3E8
extern struct XMSONG *ms; // address 0xAB3C4
extern struct XMSONG *mu; // address 0xAB3C8
extern struct XYPAIR *permlist; // address 0xAB374
extern struct XYPAIR *speclist; // address 0xAB370
extern struct XYPAIR citylumps[8][4]; // address 0xE0B68
extern unsigned char *AreaTPages; // address 0xAB2B4
extern unsigned char *XM_HeaderAddress[8]; // address 0xE1260
extern unsigned char *XM_SngAddress[24]; // address 0xE12C0
extern unsigned char cell_object_computed_values[2048]; // address 0xB88F8
extern unsigned char defaultPlayerModel[2]; // address 0xAA664
extern unsigned char defaultPlayerPalette; // address 0xAA666
extern unsigned char gCarDamageZoneVerts[5][6][50]; // address 0xC9A30
extern unsigned char gHDCarDamageLevels[5][255]; // address 0xC9530
extern unsigned char gHDCarDamageZonePolys[5][6][70]; // address 0xC39C0
extern unsigned char grassColour[4][3]; // address 0x9C350
extern unsigned char lead_analogue; // address 0xAAF84
extern unsigned char lightsOnDelay[20]; // address 0xD5748
extern unsigned char LoadedLevel; // address 0xAA614
extern unsigned char reservedSlots[20]; // address 0xBD560
extern unsigned char tpageloaded[128]; // address 0xE0C80
extern unsigned char tpageslots[19]; // address 0xE0C68
extern unsigned int brakeLength[20]; // address 0xBD4D0
extern unsigned int cellsPerFrame; // address 0xE9138
extern unsigned int cellsThisFrame; // address 0xF2798
extern unsigned int collDat; // address 0xAAB9C
extern unsigned int farClip2Player; // address 0xAA474
extern unsigned int g_nCManOptions; // address 0x10EE08
extern unsigned int numHeapEntries; // address 0xF279C
extern unsigned int ObjectDrawnValue; // address 0xAAF44
extern unsigned long *Driver2TempJunctionsPtr; // address 0xAB070
extern unsigned long *MissionScript; // address 0xAB074
extern unsigned long *ot_slot; // address 0xAAD78
extern unsigned long *oTablePtr; // address 0x10EC74
extern unsigned long *outcoords; // address 0xAA990
extern unsigned long *tile_overflow_buffer; // address 0xAAD68
extern unsigned long *transparent_buffer; // address 0xAAD54
extern unsigned long anim_obj_buffer[20]; // address 0xCBEF0
extern unsigned long gUnderIntensity; // address 0xAAB24
extern unsigned long lead_pad; // address 0xAAF7C
extern unsigned long mcgn; // address 0xAAC20
extern unsigned long model_object_ptrs[512]; // address 0xCC8D0
extern unsigned long PingBufferPos; // address 0xAAAE4
extern unsigned long planeColours[8]; // address 0xCC890
extern unsigned long srgn; // address 0xAAC24
extern unsigned long tannerPad; // address 0xAB134
extern unsigned long unpack_cellptr_tbl[3]; // address 0xDEE10
extern unsigned long unpack_roadmap_tbl[2]; // address 0xAB280
extern unsigned long xm_l_vag_spu_addr[8][128]; // address 0xE1320
extern unsigned short *cell_ptrs; // address 0xAAFBC
extern unsigned short *Low2HighDetailTable; // address 0xAAD7C
extern unsigned short *Low2LowerDetailTable; // address 0xAAD80
extern unsigned short *newmodels; // address 0xAB2D8
extern unsigned short *spoolinfo_offsets; // address 0xAB274
extern unsigned short cd_palette[32]; // address 0xDECD0
extern unsigned short civ_clut[8][32][6]; // address 0xABB00
extern unsigned short controller_bits; // address 0xAAF48
extern unsigned short distanceCache[16384]; // address 0xE9B00
extern unsigned short edgecount; // address 0xAB198
extern unsigned short edgelist[16]; // address 0xDCCB8
extern unsigned short g_PAD_FLB; // address 0x10EC82
extern unsigned short g_PAD_FLT; // address 0x10EC86
extern unsigned short g_PAD_FRB; // address 0x10EC80
extern unsigned short g_PAD_FRT; // address 0x10EC84
extern unsigned short g_PAD_LD; // address 0x10EC92
extern unsigned short g_PAD_LL; // address 0x10EC94
extern unsigned short g_PAD_LR; // address 0x10EC96
extern unsigned short g_PAD_LU; // address 0x10EC90
extern unsigned short g_PAD_RD; // address 0x10EC8A
extern unsigned short g_PAD_RL; // address 0x10EC8C
extern unsigned short g_PAD_RR; // address 0x10EC8E
extern unsigned short g_PAD_RU; // address 0x10EC88
extern unsigned short g_PAD_SEL; // address 0x10EC98
extern unsigned short g_PAD_START; // address 0x10EC9A
extern unsigned short gChannel; // address 0xAAA54
extern unsigned short gLastModelCollisionCheck; // address 0xAB0D0
extern unsigned short gMemCardMode; // address 0xAB40C
extern unsigned short lintab[768]; // address 0xA2008
extern unsigned short logtab[104]; // address 0xA2608
extern unsigned short nextindex; // address 0xAB19A
extern unsigned short paddCamera; // address 0xAAB1C

static char *button_names[11]; // address 0xA18B8
static char *carSelectPlayerText[2]; // address 0x1C6764
static char *carSelectPlayerText[2]; // address 0xAA6FC
static char *cheatText[5]; // address 0x1C686C
static char *cheatText[5]; // address 0xA06A8
static char *current_address; // address 0xAB300
static char *CutSceneNames[28]; // address 0x1C6880
static char *CutSceneNames[28]; // address 0xA06BC
static char *CutsceneReplayStart; // address 0xAA230
static char *gameNames[64]; // address 0x1C676C
static char *gameNames[64]; // address 0xA05A8
static char *MapBitMaps; // address 0xAAAC0
static char *MCbuffer128K; // address 0xAB3F4
static char *MCfilename; // address 0xAB400
static char *MClanguageBuffer; // address 0xAB3F8
static char *MCsaveBuffer; // address 0xAB3FC
static char *MissionLoadAddress; // address 0xAA738
static char *MissionName[37]; // address 0x1C68F0
static char *MissionName[37]; // address 0xA072C
static char *palletedir[8]; // address 0x9BAF4
static char *target_address; // address 0xAB1E0
static char AnalogueUnpack[16]; // address 0x9BBC4
static char banks[24]; // address 0xDD430
static char cop_bank; // address 0xAAEA1
static char cop_model; // address 0xAAEA0
static char EnterNameText[32]; // address 0xD93E0
static char GreyIcons[24]; // address 0xCBE88
static char header_pt[3868]; // address 0xCE728
static char loseTailTargetArrowTris[24]; // address 0xA1E24
static char MapBuffer[520]; // address 0xAB8C0
static char maptile[4][4]; // address 0xABAD0
static char maxSpeedTargetArrowTris[18]; // address 0xA1E5C
static char menu0[2]; // address 0x9C4DC
static char menu1[10]; // address 0x9C4E0
static char menu2[5]; // address 0x9C4EC
static char menu3[2]; // address 0x9C4F4
static char menu4[2]; // address 0x9C4F8
static char menu5[5]; // address 0x9C4FC
static char menu6[7]; // address 0x9C504
static char missionstarts[42]; // address 0xA047C
static char MusicVolumeText[8]; // address 0xAB0F0
static char NewLeadDelay; // address 0xAA740
static char normalTargetArrowTris[9]; // address 0xA1E18
static char omap[128][16]; // address 0xE91A8
static char padbuffer[2][34]; // address 0xD92E8
static char ScoreItems[5][16]; // address 0xD9430
static char ScoreName[5][7]; // address 0xD9400
static char ScoreTime[5][16]; // address 0xD9480
static char SfxVolumeText[8]; // address 0xAB0E8
static char song_pt[2992]; // address 0xCF648
static char sqtbl[65]; // address 0x9C018
static char tile_size; // address 0xAA0DC
static char fevalidchars[39]; // address 0x10EE0C
static char validchars[68]; // address 0xA1694
static char windowTargetArrowTris[30]; // address 0xA1E3C
static enum CITYTYPE lastcity; // address 0xAAA19
static enum CITYTYPE lasttype; // address 0xAAA18
static enum PAUSEMODE PauseMode; // address 0xAAF18
static int ActiveMenuItem; // address 0xAB0E0
static int alleycount; // address 0xAA488
static int allownameentry; // address 0xAA860
static int BlackBorderHeight; // address 0xAA258
static int bodgevar; // address 0xAB038
static int bWantFade; // address 0xAA600
static int cameraEventsActive; // address 0xAADE4
static int cammapht2; // address 0xAAD0C
static int carsOnBoat; // address 0xAADF0
static int ChicagoCameraHack[3]; // address 0x9ED6C
static int cop_adjust; // address 0xAA73C
static int copmusic; // address 0xAA580
static int current_sector; // address 0xAB1E4
static int current_sector; // address 0xAB2F4
static int current_smashed_cone; // address 0xAA4A8
static int CurrentBomb; // address 0xAA130
static int cutscene_timer; // address 0xAB030
static int CutsceneCameraOffset; // address 0xAA23C
static int CutsceneInReplayBuffer; // address 0xAA25C
static int CutsceneLength; // address 0xAA254
static int CutsceneStreamIndex; // address 0xAA234
static int doneFirstHavanaCameraHack; // address 0xAAE18
static int endchunk; // address 0xAB20C
static int eventHaze; // address 0xAA51C
static int fadeVal; // address 0xAA604
static int flashtimer; // address 0xAA0E0
static int flashval; // address 0xAA140
static int fullStrike; // address 0xAA134
static int gCSDestroyPlayer; // address 0xAA250
static int gDieWithFade; // address 0xAA60C
static int gEnteringScore; // address 0xAA83C
static int gHaveInGameCutscene; // address 0xAA24C
static int gLastChase; // address 0xAA594
static int gPlaying; // address 0xAAA50
static int gScoreEntered; // address 0xAA844
static int gScorePosition; // address 0xAA840
static int gTrailblazerPrevConeDelay; // address 0xAA4AC
static int gUseRotatedMap; // address 0xAA0BC
static int gWantFlash; // address 0xAA13C
static int halfStrike; // address 0xAA138
static int HavanaCameraHack[9]; // address 0x9ED78
static int holdall; // address 0xAB034
static int hSubShad; // address 0xAAEB8
static int last_flag; // address 0xAA748
static int lastcv; // address 0xAB17C
static int lastrequesteddisc; // address 0xAA4C8
static int lastsay; // address 0xAA74C
static int load_steps; // address 0xAAF04
static int loading_bar_pos; // address 0xAAF00
static int loudhail_time; // address 0xAAE9C
static int map_x_offset; // address 0xAA0C0
static int map_z_offset; // address 0xAA0C4
static int mapstuff; // address 0xAAD10
static int master_volume; // address 0xAA9C8
static int MCoptions; // address 0xAB404
static int ntpages; // address 0xAB208
static int nTPchunks; // address 0xAB1F4
static int nTPchunks_reading; // address 0xAB1F8
static int nTPchunks_writing; // address 0xAB1FC
static int num_pedestrians; // address 0xAA8B4
static int numCopPeds; // address 0xAA8F4
static int NumCutsceneStreams; // address 0xAA238
static int numcv; // address 0xAB178
static int numTannerPeds; // address 0xAA8B8
static int old_x_mod; // address 0xAA0D0
static int old_y_mod; // address 0xAA0D4
static int oldCamView; // address 0xAB0FC
static int oldDir; // address 0xAB108
static int pathParams[5]; // address 0xECBE8
static int PauseReturnValue; // address 0xAB0E4
static int playerwithcontrol[3]; // address 0xA1660
static int plotted; // address 0xAAC94
static int PreLoadedCutscene; // address 0xAA248
static int prevCopsInPursuit; // address 0xAA744
static int pvsSize[4]; // address 0xA1AD0
static int randIndex; // address 0xECD34
static int randomcounter; // address 0xAAC18
static int randomindex; // address 0xAAC1C
static int randState[17]; // address 0xECCF0
static int rio_alarm; // address 0xAB03C
static int RioCameraHack[6]; // address 0x9EDDC
static int said_picked_up; // address 0xAAC28
static int SavedCameraAngle; // address 0xAAC70
static int SavedCameraCarId; // address 0xAAC68
static int SavedCameraView; // address 0xAAC6C
static int SavedWorldCentreCarId; // address 0xAAC74
static int sectors_left; // address 0xAB2F8
static int sectors_read; // address 0xAB2FC
static int sectors_this_chunk; // address 0xAB1EC
static int sectors_to_read; // address 0xAB1E8
static int sky_y_offset[4]; // address 0xA1944
static int skycolour; // address 0xAB1A4
static int sound_paused; // address 0xAA9C0
static int StartPos; // address 0xAB39C
static int stop_sound_handler; // address 0xAA9CC
static int storedCam; // address 0xAB0F8
static int switch_spooltype; // address 0xAB1F0
static int TestCnt; // address 0xAAAD8
static int ThrownBombDelay; // address 0xAA12C
static int ThunderDistance; // address 0xAAC90
static int ThunderTimer; // address 0xAAC8C
static int tilehnum; // address 0xAA0D8
static int treecount; // address 0xAA48C
static int VegasCameraHack[16]; // address 0x9ED9C
static int VisibleMenu; // address 0xAB0D8
static int WantPause; // address 0xAA608
static int wrongside[2][6]; // address 0xCDA20
static int x_map; // address 0xAA0C8
static int xa_prepared; // address 0xAAA58
static int y_map; // address 0xAA0CC
static long banksize[2]; // address 0xAA9B8
static long baseDir; // address 0xAAB10
static long basePos[3]; // address 0xACB08
static long civrseed[17]; // address 0xBD1C8
static long missndpos[4]; // address 0xD75A0
static long rseed[17]; // address 0xBD588
static long skyblue; // address 0xAA99C
static long skygreen; // address 0xAA998
static long skyred; // address 0xAA994
static short big_north[4]; // address 0x9BADC
static short skyclut[28]; // address 0xDD2C0
static short skytpage[28]; // address 0xDD280
static struct __envsound envsnd[32]; // address 0xCDF98
static struct __envsoundinfo ESdata[2]; // address 0xCE598
static struct __envsoundtags EStags; // address 0xCE6C8
static struct __io id_map[49]; // address 0xA04A8
static struct __othercarsound car_noise[4]; // address 0xCE6D8
static struct __othercarsound siren_noise[2]; // address 0xCE708
static struct __pauseinfo musps; // address 0xDD530
static struct __pauseinfo pause; // address 0xDD4C0
static struct __xa_request xa; // address 0xAB040
static struct __xa_request xa_data[26]; // address 0xA050C
static struct _CAR_DATA *horncarflag[2]; // address 0xAA1CC
static struct _EVENT *event; // address 0xAADE0
static struct _EVENT *firstMissionEvent; // address 0xAAE0C
static struct _EVENT *trackingEvent[2]; // address 0xAADE8
static struct _TARGET *carEvent[8]; // address 0xCDF08
static struct BOMB ThrownBombs[5]; // address 0xACA50
static struct CameraDelay cameraDelay; // address 0xAAE20
static struct CDATA2D cd[2]; // address 0xBD0F8
static struct CDATA2D cd[2]; // address 0xD9220
static struct CDATA2D cd[2]; // address 0xD9568
static struct CdlLOC pause_loc; // address 0xAB3A0
static struct COLOUR_BAND damageColour[2]; // address 0x9B9E4
static struct COLOUR_BAND felonyColour[3]; // address 0x9B99C
static struct COLOUR_BAND playerDamageColour[3]; // address 0x9B9C0
static struct CVECTOR gFontColour; // address 0xAB158
static struct Detonator detonator; // address 0xAAE10
static struct DUPLICATION DuplicatePadData; // address 0xAA82C
static struct EventCamera eventCamera; // address 0xCDF28
static struct FILEFORMAT fileFormat; // address 0xA26F8
static struct FixedEvent *fixedEvent; // address 0xAAE08
static struct FixedEvent chicagoDoor[3]; // address 0x9E974
static struct FixedEvent havanaFixed[3]; // address 0x9E9F8
static struct FixedEvent rioDoor[6]; // address 0x9EB58
static struct FixedEvent vegasDoor[5]; // address 0x9EA7C
static struct FLAREREC flare_info[8]; // address 0xA19EC
static struct Foam foam; // address 0xAADD8
static struct FONT_DIGIT fontDigit[12]; // address 0xA18A0
static struct Helicopter HelicopterData; // address 0x9EC60
static struct MATRIX map_matrix; // address 0xABAE0
static struct MATRIX SS; // address 0xA041C
static struct MENU_HEADER *ActiveMenu; // address 0xAB0DC
static struct MENU_HEADER *VisibleMenus[3]; // address 0xD93C0
static struct MENU_HEADER ChaseGameFinishedHeader; // address 0xA15FC
static struct MENU_HEADER CutscenePauseMenuHeader; // address 0xA1584
static struct MENU_HEADER DrivingDebugHeader; // address 0xD94D0
static struct MENU_HEADER DrivingGameFinishedHeader; // address 0xA15D4
static struct MENU_HEADER InvalidMultiPadHeader; // address 0xA164C
static struct MENU_HEADER InvalidPadHeader; // address 0xA1638
static struct MENU_HEADER MissionCompleteHeader; // address 0xA1598
static struct MENU_HEADER MissionFailedHeader; // address 0xA15AC
static struct MENU_HEADER MultiplayerFinishedHeader; // address 0xA15E8
static struct MENU_HEADER MultiplayerPauseHeader; // address 0xA1570
static struct MENU_HEADER NoMultiPadHeader; // address 0xA1624
static struct MENU_HEADER NoPadHeader; // address 0xA1610
static struct MENU_HEADER PauseMenuHeader; // address 0xA155C
static struct MENU_HEADER TakeARideFinishedHeader; // address 0xA15C0
static struct MENU_ITEM *ActiveItem[3]; // address 0xD93D0
static struct MENU_ITEM ChaseGameFinishedItems[6]; // address 0xA13F4
static struct MENU_ITEM CutscenePauseItems[6]; // address 0xA10FC
static struct MENU_ITEM DrivingGameFinishedItems[7]; // address 0xA1304
static struct MENU_ITEM InvalidMultiPadItems[2]; // address 0xA1534
static struct MENU_ITEM InvalidPadItems[1]; // address 0xA1520
static struct MENU_ITEM MainPauseItems[9]; // address 0xA0FBC
static struct MENU_ITEM MissionCompleteItems[8]; // address 0xA1174
static struct MENU_ITEM MissionFailedItems[6]; // address 0xA1214
static struct MENU_ITEM MultiplayerFinishedItems[5]; // address 0xA1390
static struct MENU_ITEM MultiplayerPauseItems[7]; // address 0xA1070
static struct MENU_ITEM NoMultiPadItems[2]; // address 0xA14F8
static struct MENU_ITEM NoPadItems[1]; // address 0xA14E4
static struct MENU_ITEM TakeARideFinishedItems[6]; // address 0xA128C
static struct MENU_ITEM YesNoQuitItems[3]; // address 0xA14A8
static struct MENU_ITEM YesNoRestartItems[3]; // address 0xA146C
static struct MISSION_STEP MissionLadder[68]; // address 0x9F084
static struct MissionTrain missionTrain[2]; // address 0x9E93C
static struct MODEL dummyModel; // address 0xDECA8
static struct MR_THREAD MissionThreads[16]; // address 0xD7B80
static struct MultiCar multiCar; // address 0xAAE00
static struct OVERMAP overlaidmaps[4]; // address 0x9B9FC
static struct PLAYBACKCAMERA *CutLastChange; // address 0xAA244
static struct PLAYBACKCAMERA *CutNextChange; // address 0xAA240
static struct POLY_FT4 cd_sprite; // address 0x1C6D18
static struct POLY_FT4 cd_sprite; // address 0xDEC78
static struct POLY_G4 fade_g4[2]; // address 0xD5610
static struct POLY_GT4 fade_gt4[2]; // address 0xD55A0
static struct POLYCOORD polycoords[6]; // address 0x9E6DC
static struct RECT MapRect; // address 0xAAAC8
static struct RECT tpage; // address 0xAB200
static struct REPLAY_ICON replay_icons[23]; // address 0x9C36C
static struct SLICE slice; // address 0xA284C
static struct SMASHED_CONE smashed_cones[6]; // address 0xCDA50
static struct SpuCommonAttr sound_attr; // address 0xDD490
static struct SVECTOR boatOffset; // address 0xAADF8
static struct SVECTOR camAngle; // address 0xAB100
static struct SVECTOR cv[12]; // address 0xDA9A8
static struct SVECTOR moon_shadow_position[4]; // address 0xA19CC
static struct SVECTOR targetArrowVerts[43]; // address 0xA1CC0
static struct SXYPAIR MapSegmentPos[16]; // address 0x9BA5C
static struct TARGET_ARROW_MODEL targetArrowModel[4]; // address 0xA1E70
static struct TEXTURE_DETAILS button_textures[11]; // address 0xD9B40
static struct UV skytexuv[28]; // address 0xDD300
static struct VECTOR *SavedSpoolXZ; // address 0xAAC78
static struct VECTOR Drift; // address 0xA040C
static struct VECTOR player_position; // address 0x9BAE4
static struct VECTOR SmokePos; // address 0xD52C8
static struct XYPAIR north[4]; // address 0x9BABC
static struct XYPAIR NVertex[4]; // address 0x9BA9C
static unsigned char *PVSEncodeTable; // address 0xAAFD0
static unsigned char *shake_data[3]; // address 0xA0FB0
static unsigned char align[6]; // address 0xAA820
static unsigned char dummymotors[2]; // address 0xAA828
static unsigned char endread; // address 0xAB2F1
static unsigned char High_shake_data[21]; // address 0xA0F7C
static unsigned char HorizonLookup[4][4]; // address 0xA1954
static unsigned char HorizonTextures[40]; // address 0xA1964
static unsigned char hornchanflag[2]; // address 0xAA1C8
static unsigned char load_complete; // address 0xAB2F0
static unsigned char Low_shake_data[10]; // address 0xA0FA4
static unsigned char Med_shake_data[13]; // address 0xA0F94
static unsigned char param[8]; // address 0xAB1D0
static unsigned char playercollected[2]; // address 0xAB060
static unsigned char result[8]; // address 0xAB1D8
static unsigned char VibratoTable[32]; // address 0xA26D8
static unsigned int horn_time; // address 0xAAEA4
static unsigned long buffer_0[8]; // address 0xE1220
static unsigned long channel_lookup[16]; // address 0xDD450
static unsigned long finished_count; // address 0xAAA4C
static unsigned long MCsp; // address 0xAB408
static unsigned long MissionStack[16][16]; // address 0xD7780
static unsigned short *xVis; // address 0xAAE28
static unsigned short *zVis; // address 0xAAE2C
static unsigned short CurrentChannel; // address 0xAB398
static unsigned short ID; // address 0xAB39A
static unsigned short MapClut; // address 0xAAAD2
static unsigned short MapTPage; // address 0xAAAD0
static unsigned short RecapFrameLength[19]; // address 0x9F10C

// 1182 functions

