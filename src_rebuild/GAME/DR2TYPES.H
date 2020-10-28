#ifndef DR2TYPES_H
#define DR2TYPES_H

// Driver 2 system types

struct VECTOR2 // hashcode: 0x7572A047 (dec: 1970446407)
{
	int vx; // size=0, offset=0
	int vz; // size=0, offset=4
};

struct USVECTOR_NOPAD // hashcode: 0xA2EACE82 (dec: -1561670014)
{
	unsigned short vx; // size=0, offset=0
	unsigned short vy; // size=0, offset=2
	unsigned short vz; // size=0, offset=4
};

struct VECTOR_NOPAD // hashcode: 0x32909951 (dec: 848337233)
{
	long vx; // size=0, offset=0
	long vy; // size=0, offset=4
	long vz; // size=0, offset=8
};

struct SVECTOR_NOPAD // hashcode: 0xBEBBA7F1 (dec: -1094998031)
{
	short vx; // size=0, offset=0
	short vy; // size=0, offset=2
	short vz; // size=0, offset=4
};

// TODO: DR2TYPES

struct BOX // hashcode: 0xC47BB3B2 (dec: -998526030)
{
	float xmin; // size=0, offset=0
	float ymin; // size=0, offset=4
	float zmin; // size=0, offset=8
	float xmax; // size=0, offset=12
	float ymax; // size=0, offset=16
	float zmax; // size=0, offset=20
};

struct BSPHERE // hashcode: 0x117AEF65 (dec: 293269349)
{
	VECTOR bounding_sphere_mid; // size=16, offset=0
	float bounding_sphere; // size=0, offset=16
};

struct RGB // hashcode: 0xDDB9C681 (dec: -575027583)
{
	unsigned char r; // size=0, offset=0
	unsigned char g; // size=0, offset=1
	unsigned char b; // size=0, offset=2
	unsigned char pad; // size=0, offset=3
};

struct UV_INFO // hashcode: 0x23373190 (dec: 590819728)
{
	unsigned char u; // size=0, offset=0
	unsigned char v; // size=0, offset=1
};

struct XYPAIR // hashcode: 0x26B42A1B (dec: 649341467)
{
	int x; // size=0, offset=0
	int y; // size=0, offset=4
};

struct SXYPAIR // hashcode: 0xC24DE5F5 (dec: -1035082251)
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
};

struct GAP_INFO // hashcode: 0x468CC560 (dec: 1183630688)
{
	DVECTOR offset; // size=4, offset=0
	char clear; // size=0, offset=4
};

struct PSXBUTTON // hashcode: 0x41BD456C (dec: 1102923116)
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short w; // size=0, offset=4
	short h; // size=0, offset=6
	unsigned char l; // size=0, offset=8
	unsigned char r; // size=0, offset=9
	unsigned char u; // size=0, offset=10
	unsigned char d; // size=0, offset=11
	int userDrawFunctionNum; // size=0, offset=12
	short s_x; // size=0, offset=16
	short s_y; // size=0, offset=18
	int action; // size=0, offset=20
	int var; // size=0, offset=24
	char Name[32]; // size=32, offset=28
};

struct PADRECORD // hashcode: 0x0D20CEBD (dec: 220253885)
{
	unsigned char pad; // size=0, offset=0
	unsigned char analogue; // size=0, offset=1
	unsigned char run; // size=0, offset=2
};

struct ARC_ENTRY // hashcode: 0x4C376F3B (dec: 1278701371)
{
	short offset; // size=0, offset=0
	short length; // size=0, offset=2
};

struct DRIVER2_CURVE // hashcode: 0xB805ADA3 (dec: -1207587421)
{
	int Midx; // size=0, offset=0
	int Midz; // size=0, offset=4
	short start; // size=0, offset=8
	short end; // size=0, offset=10
	short ConnectIdx[4]; // size=8, offset=12
	short gradient; // size=0, offset=20
	short height; // size=0, offset=22
	char NumLanes; // size=0, offset=24
	char LaneDirs; // size=0, offset=25
	char inside; // size=0, offset=26
	char AILanes; // size=0, offset=27
};

struct DRIVER2_STRAIGHT // hashcode: 0xCF738039 (dec: -814514119)
{
	int Midx; // size=0, offset=0
	int Midz; // size=0, offset=4
	unsigned short length; // size=0, offset=8
	short bing; // size=0, offset=10
	short angle; // size=0, offset=12
	short ConnectIdx[4]; // size=8, offset=14
	char NumLanes; // size=0, offset=22				// masked: 0xF - lane count, flags: 0x40 - allow non-drivable parked cars, 0x80: allow parked cars
	char LaneDirs; // size=0, offset=23				// bit field of lanes 
	char AILanes; // size=0, offset=24				// bit field of lanes which allows spawning active cars. LaneDirs >> (LANE_NUMBER / 2 & 0x1fU)
	char packing; // size=0, offset=25
};

struct OLD_DRIVER2_JUNCTION // hashcode: 0x42D65B1B (dec: 1121344283)
{
	int Midx; // size=0, offset=0
	int Midz; // size=0, offset=4
	short length; // size=0, offset=8
	short width; // size=0, offset=10
	short angle; // size=0, offset=12
	short ExitIdx[4]; // size=8, offset=14
	unsigned short flags; // size=0, offset=22
};

struct DRIVER2_JUNCTION // hashcode: 0x7C27C3D0 (dec: 2082980816)
{
	short ExitIdx[4]; // size=8, offset=0
	unsigned long flags; // size=0, offset=8
};

struct _sdPlane // hashcode: 0x873C357E (dec: -2026097282)
{
	short surface; // size=0, offset=0
	short a; // size=0, offset=2
	short b; // size=0, offset=4
	short c; // size=0, offset=6
	int d; // size=0, offset=8
};

struct sdNodePACKED
{
	int angle : 11; // offset=0 bit
	int dist : 12; // offset=11 bit
	int offset : 8; // offset=23 bit
	int node : 1; // offset=31 bit
};

union _sdNode // hashcode: 0xD508740E (dec: -720866290)
{
	int value;
	sdNodePACKED n;
};

struct WHEEL // hashcode: 0x76B6CC6D (dec: 1991691373)
{
	char susCompression; // size=0, offset=0
	char locked; // size=0, offset=1
	char onGrass; // size=0, offset=2
	unsigned char surface; // size=0, offset=3
};

struct OrientedBox // hashcode: 0x8D87CFA2 (dec: -1920479326)
{
	VECTOR_NOPAD location; // size=12, offset=0
	SVECTOR_NOPAD radii[3]; // size=18, offset=12
	short length[3]; // size=6, offset=30
};

struct _HANDLING_DATA // hashcode: 0x9DD0BFD7 (dec: -1647263785)
{
	MATRIX where; // size=32, offset=0
	MATRIX drawCarMat; // size=32, offset=32
	long acc[4]; // size=16, offset=64
	long aacc[4]; // size=16, offset=80
	int wheel_speed; // size=0, offset=96
	int speed; // size=0, offset=100
	int direction; // size=0, offset=104
	char gear; // size=0, offset=108
	char changingGear; // size=0, offset=109
	char mayBeColliding; // size=0, offset=110
	char autoBrake; // size=0, offset=111
	WHEEL wheel[4]; // size=16, offset=112
	short revs; // size=0, offset=128
	VECTOR shadowPoints[4]; // size=64, offset=132
	int front_vel; // size=0, offset=196
	int rear_vel; // size=0, offset=200
	struct OrientedBox oBox; // size=36, offset=204
};

union RigidBodyState // Hashcode: 0x60B16C22 (dec: 1622240290)
{
	long v[13]; // size=52, offset=0
	struct {
		long fposition[3]; // size=12, offset=0
		long orientation[4]; // size=16, offset=12
		long linearVelocity[3]; // size=12, offset=28
		long angularVelocity[3]; // size=12, offset=40
	} n; // size=52, offset=0, found in object files: obj\dr2roads.obj, obj\dr2roads.obj
};

struct _APPEARANCE_DATA // hashcode: 0x4A050E31 (dec: 1241845297)
{
	struct SXYPAIR light_trails[4][4]; // size=64, offset=0
	struct CAR_COSMETICS* carCos; // size=236, offset=64
	short old_clock[4]; // size=8, offset=68
	char life; // size=0, offset=76
	char coplife; // size=0, offset=77
	short qy; // size=0, offset=78
	short qw; // size=0, offset=80
	char life2; // size=0, offset=82
	char model; // size=0, offset=83
	char palette; // size=0, offset=84

	char needsDenting : 1; // size=0, offset=85
	char flags : 7;			// [A] new: appearance flags, 1,2,3,4 = wheel hubcaps lost

	short damage[6]; // size=12, offset=86
};

struct CIV_ROUTE_ENTRY // hashcode: 0x7DE1E25F (dec: 2111955551)
{
	short dir; // size=0, offset=0
	unsigned short pathType; // size=0, offset=2
	int distAlongSegment; // size=0, offset=4
	int x; // size=0, offset=8
	int z; // size=0, offset=12
};

struct CIV_STATE // hashcode: 0x1B69CC52 (dec: 459918418)
{
	int currentRoad; // size=0, offset=0
	int currentNode; // size=0, offset=4
	struct CIV_ROUTE_ENTRY* ctrlNode; // size=16, offset=8
	unsigned char ctrlState; // size=0, offset=12
	unsigned char trafficLightPhaseId; // size=0, offset=13
	unsigned char changeLane; // size=0, offset=14
	unsigned char turnDir; // size=0, offset=15
	char brakeLight; // size=0, offset=16
	unsigned char oldLane; // size=0, offset=17
	unsigned char changeLaneCount; // size=0, offset=18
	unsigned char pad3; // size=0, offset=19
	int turnNode; // size=0, offset=20
	int changeLaneIndicateCount; // size=0, offset=24
	int carPauseCnt; // size=0, offset=28
	int velRatio; // size=0, offset=32
	struct CIV_ROUTE_ENTRY targetRoute[13]; // size=208, offset=36
	struct CIV_ROUTE_ENTRY* pnode; // size=16, offset=244
	unsigned char maxSpeed; // size=0, offset=248
	unsigned char thrustState; // size=0, offset=249
	unsigned char carMustDie; // size=0, offset=250
	unsigned char currentLane; // size=0, offset=251
};

struct COP // hashcode: 0x03D1B2C7 (dec: 64074439)
{
	struct VECTOR2 targetHistory[2]; // size=16, offset=0
	char routeInMemory; // size=0, offset=16
	char justPinged; // size=0, offset=17
	char close_pursuit; // size=0, offset=18
	char dying; // size=0, offset=19
	unsigned short DistanceToPlayer; // size=0, offset=20
	short desiredSpeed; // size=0, offset=22
	short recalcTimer; // size=0, offset=24
	short stuckTimer; // size=0, offset=26
	short lastRecoverStrategy; // size=0, offset=28
	short recoveryTimer; // size=0, offset=30
	short hiddenTimer; // size=0, offset=32
	short frontLClear; // size=0, offset=34
	short frontRClear; // size=0, offset=36
};

struct LEAD_CAR // hashcode: 0x44C76F5F (dec: 1153920863)
{
	char dstate; // size=0, offset=0
	char ctt; // size=0, offset=1
	short targetDir; // size=0, offset=2
	int targetX; // size=0, offset=4
	int targetZ; // size=0, offset=8
	int currentRoad; // size=0, offset=12
	int lastRoad; // size=0, offset=16
	int nextJunction; // size=0, offset=20
	int nextTurn; // size=0, offset=24
	int nextExit; // size=0, offset=28
	int stuckCount; // size=0, offset=32
	int panicCount; // size=0, offset=36
	int recoverTime; // size=0, offset=40
	int roadPosition; // size=0, offset=44
	int roadForward; // size=0, offset=48
	int boringness; // size=0, offset=52
	int avoid; // size=0, offset=56
	int lastTarget; // size=0, offset=60
	int offRoad; // size=0, offset=64
	int width; // size=0, offset=68
	int d; // size=0, offset=72
	int base_Normal; // size=0, offset=76
	int base_Angle; // size=0, offset=80
	int base_Dir; // size=0, offset=84
	int outsideSpoolRegion; // size=0, offset=88
	int direction; // size=0, offset=92
	int lastDirection; // size=0, offset=96
	char takeDamage; // size=0, offset=100
};

enum ECarControlType
{
	CONTROL_TYPE_NONE = 0,				// car is not in the world
	CONTROL_TYPE_PLAYER = 1,			// controlled by player pads
	CONTROL_TYPE_CIV_AI = 2,			// Civilian car. May be a passive cop car with CONTROL_FLAG_COP flag.
	CONTROL_TYPE_PURSUER_AI = 3,		// Police pursuer car. Always chases player
	CONTROL_TYPE_LEAD_AI = 4,			// FreeRoamer AI

	CONTROL_TYPE_CAMERACOLLIDER = 5,	// Used as a camera collider
	CONTROL_TYPE_TANNERCOLLIDER = 6,	// Used as collision box for tanner
	CONTROL_TYPE_CUTSCENE = 7,			// Pretty same as player car but controllled by cutscene. Can be a chase car.
};

enum ECarControlFlags
{
	CONTROL_FLAG_COP = (1 << 0),		// civ car is a cop car
	CONTROL_FLAG_COP_SLEEPING = (1 << 1),		// passive cop flag (roadblocks). Hitting car with that flag results it's activation
	CONTROL_FLAG_WAS_PARKED = (1 << 2)		// car pinged in as parked. Really nothing to do with it
};

typedef struct _CAR_DATA // hashcode: 0x8D78CB99 (dec: -1921463399)
{
	struct _HANDLING_DATA hd; // size=240, offset=0
	union RigidBodyState st; // size=52, offset=240
	struct _APPEARANCE_DATA ap; // size=100, offset=292
	unsigned char hndType; // size=0, offset=392
	unsigned char controlType; // size=0, offset=393
	unsigned char controlFlags; // size=0, offset=394
	char id; // size=0, offset=395
	union {
		char* padid; // size=0, offset=0
		struct CIV_STATE c; // size=252, offset=0
		struct COP p; // size=40, offset=0
		struct LEAD_CAR l; // size=104, offset=0
	} ai; // size=252, offset=396, found in object files: obj\dr2roads.obj, obj\dr2roads.obj
	int* inform; // size=0, offset=648
	short thrust; // size=0, offset=652
	short felonyRating; // size=0, offset=654
	char handbrake; // size=0, offset=656
	char wheelspin; // size=0, offset=657
	char wasOnGround; // size=0, offset=658
	char lowDetail; // size=0, offset=659
	short wheel_angle; // size=0, offset=660
	unsigned short totalDamage; // size=0, offset=662
	long lastPad; // size=0, offset=664
} _CAR_DATA;

struct CAR_COSMETICS // hashcode: 0x48DDA5C0 (dec: 1222485440)
{
	struct SVECTOR headLight; // size=8, offset=0
	struct SVECTOR frontInd; // size=8, offset=8
	struct SVECTOR backInd; // size=8, offset=16
	struct SVECTOR brakeLight; // size=8, offset=24
	struct SVECTOR revLight; // size=8, offset=32
	struct SVECTOR policeLight; // size=8, offset=40
	struct SVECTOR exhaust; // size=8, offset=48
	struct SVECTOR smoke; // size=8, offset=56
	struct SVECTOR fire; // size=8, offset=64
	struct SVECTOR wheelDisp[4]; // size=32, offset=72
	short extraInfo; // size=0, offset=104
	short powerRatio; // size=0, offset=106
	short cbYoffset; // size=0, offset=108
	short susCoeff; // size=0, offset=110
	short traction; // size=0, offset=112
	short wheelSize; // size=0, offset=114
	struct SVECTOR cPoints[12]; // size=96, offset=116
	struct SVECTOR colBox; // size=8, offset=212
	struct SVECTOR cog; // size=8, offset=220
	short twistRateX; // size=0, offset=228
	short twistRateY; // size=0, offset=230
	short twistRateZ; // size=0, offset=232
	short mass; // size=0, offset=234
};

struct _COP_DATA // hashcode: 0xDE3D2698 (dec: -566417768)
{
	int speed; // size=0, offset=0
	int power; // size=0, offset=4
	int min; // size=0, offset=8
	int max; // size=0, offset=12
};

struct LEAD_PARAMETERS // hashcode: 0x5849B382 (dec: 1481225090)
{
	int tEnd; // size=0, offset=0
	int tAvelLimit; // size=0, offset=4
	int tDist; // size=0, offset=8
	int tDistMul; // size=0, offset=12
	int tWidth; // size=0, offset=16
	int tWidthMul; // size=0, offset=20
	int tWidth80; // size=0, offset=24
	int tWidth80Mul; // size=0, offset=28
	int hEnd; // size=0, offset=32
	int dEnd; // size=0, offset=36
	int hDist; // size=0, offset=40
	int hDistMul; // size=0, offset=44
	int hWidth; // size=0, offset=48
	int hWidthMul; // size=0, offset=52
	int hWidth80; // size=0, offset=56
	int hWidth80Mul; // size=0, offset=60
};

struct _EVENT // hashcode: 0xDD197EB3 (dec: -585531725)
{
	VECTOR position; // size=16, offset=0
	short rotation; // size=0, offset=16
	short timer; // size=0, offset=18
	int* data; // size=0, offset=20
	int* node; // size=0, offset=24
	short flags; // size=0, offset=28
	short radius; // size=0, offset=30
	int model; // size=0, offset=32
	struct _EVENT* next; // size=40, offset=36
};

struct FixedEvent // hashcode: 0xF758406C (dec: -145211284)
{
	VECTOR position; // size=16, offset=0
	short rotation; // size=0, offset=16
	short active; // size=0, offset=18
	unsigned short initialRotation; // size=0, offset=20
	unsigned short finalRotation; // size=0, offset=22
	unsigned short minSpeed; // size=0, offset=24
	unsigned short maxSpeed; // size=0, offset=26
	short flags; // size=0, offset=28
	short radius; // size=0, offset=30
	int model; // size=0, offset=32
	_EVENT* next; // size=40, offset=36
	char* modelName; // size=0, offset=40
};

struct MAPPING // hashcode: 0x46E5EAED (dec: 1189473005)
{
	unsigned short button_lookup[16]; // size=32, offset=0
	unsigned short swap_analog; // size=0, offset=32
	unsigned short reserved1; // size=0, offset=34
};

struct SAVED_PLAYER_POS // hashcode: 0x3269504F (dec: 845762639)
{
	unsigned short type; // size=0, offset=0
	short direction; // size=0, offset=2
	long vx; // size=0, offset=4
	long vy; // size=0, offset=8
	long vz; // size=0, offset=12
	unsigned long felony; // size=0, offset=16
	unsigned short totaldamage; // size=0, offset=20
	short damage[6]; // size=12, offset=22
};

struct SAVED_CAR_POS // hashcode: 0x02E940CC (dec: 48840908)
{
	char active; // size=0, offset=0
	unsigned char model; // size=0, offset=1
	unsigned char palette; // size=0, offset=2
	unsigned short totaldamage; // size=0, offset=4
	unsigned short damage[6]; // size=12, offset=6
	short direction; // size=0, offset=18
	long vx; // size=0, offset=20
	long vy; // size=0, offset=24
	long vz; // size=0, offset=28
};

struct MISSION_DATA // hashcode: 0x2CE3A08C (dec: 753115276)
{
	struct SAVED_PLAYER_POS PlayerPos; // size=36, offset=0
	struct SAVED_CAR_POS CarPos[6]; // size=192, offset=36
};

struct SCORE_ENTRY // hashcode: 0xD0B3A6C6 (dec: -793532730)
{
	int time; // size=0, offset=0
	short items; // size=0, offset=4
	char name[6]; // size=6, offset=6
};

struct SCORE_TABLES // hashcode: 0xDB95702F (dec: -610963409)
{
	struct SCORE_ENTRY GetawayTable[4][2][5]; // size=480, offset=0
	struct SCORE_ENTRY GateRaceTable[4][2][5]; // size=480, offset=480
	struct SCORE_ENTRY CheckpointTable[4][2][5]; // size=480, offset=960
	struct SCORE_ENTRY TrailblazerTable[4][2][5]; // size=480, offset=1440
	struct SCORE_ENTRY SurvivalTable[4][1][5]; // size=240, offset=1920
};

struct ACTIVE_CHEATS // hashcode: 0x2127EFE8 (dec: 556265448)
{
	unsigned char cheat1 : 1; // size=1, offset=0
	unsigned char cheat2 : 1; // size=1, offset=1
	unsigned char cheat3 : 1; // size=1, offset=2
	unsigned char cheat4 : 1; // size=1, offset=3
	unsigned char cheat5 : 1; // size=1, offset=4
	unsigned char cheat6 : 1; // size=1, offset=5
	unsigned char cheat7 : 1; // size=1, offset=6
	unsigned char cheat8 : 1; // size=1, offset=7
	unsigned char cheat9 : 1; // size=1, offset=8
	unsigned char cheat10 : 1; // size=1, offset=9
	unsigned char cheat11 : 1; // size=1, offset=10
	unsigned char cheat12 : 1; // size=1, offset=11
	unsigned char cheat13 : 1; // size=1, offset=12
	unsigned char cheat14 : 1; // size=1, offset=13
	unsigned char cheat15 : 1; // size=1, offset=14
	unsigned char cheat16 : 1; // size=1, offset=15
	unsigned char reserved1; // size=0, offset=2
	unsigned char reserved2; // size=0, offset=3
};

struct STREAM_SOURCE // hashcode: 0x81E93B6E (dec: -2115421330)
{
	unsigned char type; // size=0, offset=0
	unsigned char model; // size=0, offset=1
	unsigned char palette; // size=0, offset=2
	char controlType; // size=0, offset=3
	unsigned short flags; // size=0, offset=4
	unsigned short rotation; // size=0, offset=6
	struct VECTOR_NOPAD position; // size=12, offset=8
	int totaldamage; // size=0, offset=20
	int damage[6]; // size=24, offset=24
};

typedef struct RVECTOR RVECTOR;

typedef struct CRVECTOR3 CRVECTOR3;

typedef struct CRVECTOR4 CRVECTOR4;

typedef struct SndVolume2 SndVolume2;

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

typedef struct SCORE_ENTRY SCORE_ENTRY;

typedef struct SCORE_TABLES SCORE_TABLES;

typedef struct ACTIVE_CHEATS ACTIVE_CHEATS;

typedef struct STREAM_SOURCE STREAM_SOURCE;

typedef unsigned char u_char;

typedef unsigned short u_short;

typedef unsigned int u_int;

typedef unsigned long u_long;

typedef unsigned short ushort;

typedef struct _physadr* physadr;

// typedef long daddr_t;

typedef char* caddr_t;

typedef long* qaddr_t;

typedef long swblk_t;

// typedef unsigned int size_t;

typedef long off_t;

#ifndef __GNUC__
typedef unsigned short uid_t;

typedef unsigned short gid_t;
#endif

typedef void (*SsMarkCallbackProc)();

typedef long LONGVECTOR[4];

typedef short SHORTVECTOR[4];

typedef long LONGQUATERNION[4];

typedef unsigned long ulong;


typedef struct PADRAW* LPPADRAW;

typedef struct MAPPING* LPMAPPING;

typedef struct PAD* LPPAD;

struct MODEL // hashcode: 0x3A42A4FE (dec: 977446142)
{
	unsigned short shape_flags; // size=0, offset=0
	unsigned short flags2; // size=0, offset=2
	short instance_number; // size=0, offset=4
	unsigned char tri_verts; // size=0, offset=6
	unsigned char zBias; // size=0, offset=7
	short bounding_sphere; // size=0, offset=8
	unsigned short num_point_normals; // size=0, offset=10
	unsigned short num_vertices; // size=0, offset=12
	unsigned short num_polys; // size=0, offset=14
	int vertices; // size=0, offset=16				SVECTOR list
	int poly_block; // size=0, offset=20			POLY* list
	int normals; // size=0, offset=24				SVECTOR list
	int point_normals; // size=0, offset=28			SVECTOR list
	int collision_block; // size=0, offset=32		COLLISION_PACKET list
};

typedef enum PAUSEMODE // Hashcode: 0x086AB147 (dec: 141209927)
{
	PAUSEMODE_PAUSE = 0,
	PAUSEMODE_PAUSEP1 = 1,
	PAUSEMODE_PAUSEP2 = 2,
	PAUSEMODE_GAMEOVER = 3,
	PAUSEMODE_COMPLETE = 4,
	PAUSEMODE_PADERROR = 5,
} PAUSEMODE;

struct UV // hashcode: 0xB11A813B (dec: -1323663045)
{
	unsigned char u0; // size=0, offset=0
	unsigned char v0; // size=0, offset=1
	unsigned char u1; // size=0, offset=2
	unsigned char v1; // size=0, offset=3
	unsigned char u2; // size=0, offset=4
	unsigned char v2; // size=0, offset=5
	unsigned char u3; // size=0, offset=6
	unsigned char v3; // size=0, offset=7
};

struct TEXTURE_DETAILS // hashcode: 0xBFBD097F (dec: -1078130305)
{
	struct UV coords; // size=8, offset=0
	unsigned short tpageid; // size=0, offset=8
	unsigned short clutid; // size=0, offset=10
	char texture_number; // size=0, offset=12
	char texture_page; // size=0, offset=13
};

struct CELL_OBJECT // hashcode: 0xD26720D4 (dec: -764993324)
{
	struct VECTOR_NOPAD pos; // size=12, offset=0
	unsigned char pad; // size=0, offset=12
	unsigned char yang; // size=0, offset=13
	unsigned short type; // size=0, offset=14
};

struct ANIMATED_OBJECT // hashcode: 0xBC1CAB6E (dec: -1138971794)
{
	int internal_id; // size=0, offset=0
	int model_num; // size=0, offset=4
	char* name; // size=0, offset=8
	char LitPoly; // size=0, offset=12
};

struct SMASHABLE_OBJECT // hashcode: 0x15B5F719 (dec: 364246809)
{
	int modelIdx; // size=0, offset=0
	char* name; // size=0, offset=4
	int sound; // size=0, offset=8
	int volume; // size=0, offset=12
	int pitch; // size=0, offset=16
};

struct GARAGE_DOOR // hashcode: 0x830EFAED (dec: -2096170259)
{
	struct CELL_OBJECT* cop; // size=16, offset=0
	struct VECTOR_NOPAD old_pos; // size=12, offset=4
	struct VECTOR_NOPAD pos; // size=12, offset=16
	short rotation; // size=0, offset=28
	char yang; // size=0, offset=30
};

struct RGB16 // hashcode: 0xDC722146 (dec: -596500154)
{
	short r; // size=0, offset=0
	short g; // size=0, offset=2
	short b; // size=0, offset=4
	short pad; // size=0, offset=6
};

struct UnpaddedHackVector // hashcode: 0x83568E05 (dec: -2091479547)
{
	int vx; // size=0, offset=0
	int vz; // size=0, offset=4
	short vy; // size=0, offset=8
};

struct UnpaddedCharVector // hashcode: 0xCF0188EA (dec: -821982998)
{
	char vx; // size=0, offset=0
	char vy; // size=0, offset=1
	char vz; // size=0, offset=2
};

struct BVECTOR // hashcode: 0xD3E280B3 (dec: -740130637)
{
	char vx; // size=0, offset=0
	char vy; // size=0, offset=1
	char vz; // size=0, offset=2
	char pad; // size=0, offset=3
};

struct ADJACENT_ROAD_INFO // hashcode: 0xB24A0A42 (dec: -1303770558)
{
	DVECTOR offset; // size=4, offset=0
	GAP_INFO gap; // size=6, offset=4
};

struct FELONY_DELAY // hashcode: 0x62906D28 (dec: 1653632296)
{
	short current; // size=0, offset=0
	short maximum; // size=0, offset=2
};

struct FELONY_VALUE // hashcode: 0x8F078047 (dec: -1895333817)
{
	short placid; // size=0, offset=0
	short angry; // size=0, offset=2
};

enum TARGET_TYPE
{
	Target_Point = 1,
	Target_Car = 2,
	Target_Event = 3
};

struct MS_TARGET_BASE
{
	int type;			// data 0
	int target_flags;	// data 1
	int display_flags;	// data 2
	int posX;			// data 3
	int posZ;			// data 4
};

struct MS_TARGET_CAR_TAILING
{
	int closeMessages;		// data 13
	int farMessages;		// data 14
};

struct MS_TARGET_CAR_CHASING
{
	int maxDamage;			// data 13
	int tooFarMessage;		// data 14
	int gettingFarMessage;	// data 15
};

struct MS_TARGET_CAR
{
	MS_TARGET_BASE base;
	int rotation;		// data 5
	int slot;			// data 6
	int model;			// data 7
	int palette;		// data 8
	int type;			// data 9
	int flags;			// data 10
	int cutscene;		// data 11
	int maxDistance;	// data 12
	union
	{
		MS_TARGET_CAR_TAILING tail;
		MS_TARGET_CAR_CHASING chasing;
	};
};

struct MS_TARGET_POINT
{
	MS_TARGET_BASE base;
	int radius;			// data 5
	int posY;			// data 6
	int height;			// data 7
	int _unused;
	int actionFlag;		// data 9
	int boatX;			// data 10
	int boatZ;			// data 11
};

struct MS_TARGET_EVENT
{
	int type;			// data 0
	int target_flags;	// data 1
	int display_flags;	// data 2
	int _unused;
	VECTOR* eventPos;	// data 4
	int _unused2[10];
	int loseMessage;	// data 14
};

struct _TARGET// hashcode: 0xB3C67F7D (dec: -1278836867)
{
	union
	{
		int data[16]; // size=64, offset=0
		MS_TARGET_BASE base;
		MS_TARGET_POINT point;
		MS_TARGET_CAR car;
		MS_TARGET_EVENT event;
	};
};

struct MR_TIMER // hashcode: 0xEA39F36E (dec: -365300882)
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	unsigned char flags; // size=0, offset=4
	unsigned char min; // size=0, offset=5
	unsigned char sec; // size=0, offset=6
	unsigned char frac; // size=0, offset=7
	long count; // size=0, offset=8
};

enum PED_ACTION_TYPE : char // Hashcode: 0x3531DCAF (dec: 892460207)
{
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

enum PED_MODEL_TYPES : char // Hashcode: 0x2858A7E3 (dec: 676898787)
{
	TANNER_MODEL = 0,
	OTHER_MODEL = 1,
	OTHER_SPRITE = 2,
	CIVILIAN = 3,
};

struct PEDESTRIAN;
typedef void(*pedFunc)(PEDESTRIAN* pPed);

struct PEDESTRIAN // hashcode: 0xF569ED7C (dec: -177607300)
{
	PEDESTRIAN* pNext; // size=92, offset=0
	PEDESTRIAN* pPrev; // size=92, offset=4
	pedFunc fpRestState; // size=0, offset=8
	pedFunc fpAgitatedState; // size=0, offset=12
	char padId; // size=0, offset=16
	enum PED_MODEL_TYPES pedType; // size=1, offset=17
	VECTOR_NOPAD position; // size=12, offset=20
	SVECTOR dir; // size=8, offset=32
	SVECTOR velocity; // size=8, offset=40
	VECTOR target; // size=16, offset=48
	int flags; // size=0, offset=64
	short head_pos; // size=0, offset=68
	short head_rot; // size=0, offset=70
	short index; // size=0, offset=72
	short last_dir; // size=0, offset=74
	short interest; // size=0, offset=76
	char frame1; // size=0, offset=78
	char* motion; // size=0, offset=80
	char speed; // size=0, offset=84
	char doing_turn; // size=0, offset=85
	char finished_turn; // size=0, offset=86
	char seat_index; // size=0, offset=87
	unsigned char pallet; // size=0, offset=88
	enum PED_ACTION_TYPE type; // size=1, offset=89
};

struct __skidinfo // hashcode: 0x807ED49D (dec: -2139171683)
{
	char chan; // size=0, offset=0
	char sound; // size=0, offset=1
};

struct __horninfo // hashcode: 0x09E3B159 (dec: 165917017)
{
	char on; // size=0, offset=0
	char time; // size=0, offset=1
	char request; // size=0, offset=2
};

struct CYCLE_OBJECT // hashcode: 0x61BB6061 (dec: 1639669857)
{
	char* name; // size=0, offset=0
	short vx; // size=0, offset=4
	short vy; // size=0, offset=6
	short start1; // size=0, offset=8
	short stop1; // size=0, offset=10
	short speed1; // size=0, offset=12
	short start2; // size=0, offset=14
	short stop2; // size=0, offset=16
	short speed2; // size=0, offset=18
};
/*
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
*/

/*
typedef struct _TARGET MS_TARGET;

typedef struct MR_TIMER MR_TIMER;

typedef struct PEDESTRIAN PEDESTRIAN;

typedef enum PED_ACTION_TYPE PED_ACTION_TYPE;

typedef enum PED_MODEL_TYPES PED_MODEL_TYPES;

typedef struct __skidinfo skidinfo;

typedef struct __horninfo horninfo;

typedef struct CYCLE_OBJECT CYCLE_OBJECT;

typedef void (*SpuIRQCallbackProc)();

typedef void (*SpuTransferCallbackProc)();

typedef void (*SpuStCallbackProc)();

typedef unsigned char uchar;

typedef char schar;

typedef unsigned int uint;

typedef void envsoundfunc();

typedef struct MVERTEX SV5x5[5][5];

typedef struct PEDESTRIAN *LPPEDESTRIAN;

typedef struct SEATED_PEDESTRIANS *SEATEDPTR;

typedef struct PEDESTRIAN_ROADS *LPPEDESTRIAN_ROADS;
*/

struct CAR_POLY // hashcode: 0x6DD9D398 (dec: 1842992024)
{
	int vindices; // size=0, offset=0
	int nindices; // size=0, offset=4
	int clut_uv0; // size=0, offset=8
	int tpage_uv1; // size=0, offset=12
	int uv3_uv2; // size=0, offset=16
	short originalindex; // size=0, offset=20
};

struct COLOUR_BAND // hashcode: 0x1D8D5AB8 (dec: 495803064)
{
	struct CVECTOR colour; // size=4, offset=0
	int value; // size=0, offset=4
	int flags; // size=0, offset=8
};

struct _PERCENTAGE_BAR // hashcode: 0x56E8855E (dec: 1458079070)
{
	char* tag; // size=0, offset=0
	short xpos; // size=0, offset=4
	short ypos; // size=0, offset=6
	short width; // size=0, offset=8
	short height; // size=0, offset=10
	unsigned short position; // size=0, offset=12
	unsigned short max; // size=0, offset=14
	struct COLOUR_BAND* pColourBand; // size=12, offset=16
	int flags; // size=0, offset=20
	int active; // size=0, offset=24
};
/*
typedef struct POLY_G4 POLY_G4;

typedef struct TILE TILE;

typedef struct DR_TPAGE DR_TPAGE;

typedef struct CAR_POLY CAR_POLY;

typedef struct COLOUR_BAND COLOUR_BAND;

typedef struct _PERCENTAGE_BAR PERCENTAGE_BAR;

typedef struct _PERCENTAGE_BAR *LPPERCENTAGE_BAR;
*/

struct COP_SIGHT_DATA // hashcode: 0x4400B303 (dec: 1140896515)
{
	short surroundViewDistance; // size=0, offset=0
	short frontViewDistance; // size=0, offset=2
	short frontViewAngle; // size=0, offset=4
};

struct MAPTEX // hashcode: 0x0693A802 (dec: 110340098)
{
	short u; // size=0, offset=0
	short w; // size=0, offset=2
	short v; // size=0, offset=4
	short h; // size=0, offset=6
};

struct OVERMAP // hashcode: 0x34D52BCC (dec: 886385612)
{
	int x_offset; // size=0, offset=0
	int y_offset; // size=0, offset=4
	int width; // size=0, offset=8
	int height; // size=0, offset=12
	unsigned char toptile; // size=0, offset=16
	unsigned char dummy; // size=0, offset=17
	int scale; // size=0, offset=20
};
/*
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
*/
struct REPLAY_PARAMETER_BLOCK // hashcode: 0xA8ABCA42 (dec: -1465136574)
{
	int RecordingEnd; // size=0, offset=0
	struct VECTOR_NOPAD lead_car_start; // size=12, offset=4
	short Lead_car_dir; // size=0, offset=16
	unsigned char timeofday; // size=0, offset=18
	unsigned char weather; // size=0, offset=19
};

struct REPLAY_SAVE_HEADER // hashcode: 0x7B872BEC (dec: 2072456172)
{
	unsigned long magic; // size=0, offset=0
	unsigned char GameLevel; // size=0, offset=4
	unsigned char GameType; // size=0, offset=5
	unsigned char reserved1; // size=0, offset=6
	unsigned char NumReplayStreams; // size=0, offset=7
	unsigned char NumPlayers; // size=0, offset=8
	unsigned char RandomChase; // size=0, offset=9
	unsigned char CutsceneEvent; // size=0, offset=10
	unsigned char gCopDifficultyLevel; // size=0, offset=11
	struct MISSION_DATA SavedData; // size=228, offset=12
	struct ACTIVE_CHEATS ActiveCheats; // size=4, offset=240
	int wantedCar[2]; // size=8, offset=244
	int MissionNumber; // size=0, offset=252
	int HaveStoredData; // size=0, offset=256
	int reserved2[6]; // size=24, offset=260
};

struct REPLAY_STREAM_HEADER // hashcode: 0x7D77518E (dec: 2104971662)
{
	struct STREAM_SOURCE SourceType; // size=48, offset=0
	int Size; // size=0, offset=48
	int Length; // size=0, offset=52
};

struct REPLAY_STREAM // hashcode: 0xC894D541 (dec: -929770175)
{
	struct STREAM_SOURCE SourceType; // size=48, offset=0
	struct PADRECORD* InitialPadRecordBuffer; // size=3, offset=48
	struct PADRECORD* PadRecordBuffer; // size=3, offset=52
	struct PADRECORD* PadRecordBufferEnd; // size=3, offset=56
	unsigned char playbackrun; // size=0, offset=60
	int length; // size=0, offset=64
	int padCount;
};

struct _PING_PACKET // hashcode: 0x9E8E7C27 (dec: -1634829273)
{
	unsigned short frame; // size=0, offset=0
	char carId; // size=0, offset=2
	char cookieCount; // size=0, offset=3
};
/*
typedef struct REPLAY_PARAMETER_BLOCK REPLAY_PARAMETER_BLOCK;

typedef struct REPLAY_SAVE_HEADER REPLAY_SAVE_HEADER;

typedef struct REPLAY_STREAM_HEADER REPLAY_STREAM_HEADER;

typedef struct REPLAY_STREAM REPLAY_STREAM;

typedef struct _PING_PACKET PING_PACKET;
*/
struct ROADBLOCK // hashcode: 0x006C3CDD (dec: 7093469)
{
	VECTOR position; // size=16, offset=0
	ADJACENT_ROAD_INFO adjacentRoadInfo; // size=10, offset=16
	short RoadToBlock; // size=0, offset=26
	short AdjacentRoad; // size=0, offset=28
	short RoadblockTimer; // size=0, offset=30
	int copRespawnTime; // size=0, offset=32
	char NumCarsNeededForRoad; // size=0, offset=36
	char NumCarsNeededForAdjacentRoad; // size=0, offset=37
	char NumCarsSavedForBlock; // size=0, offset=38
	char DirectionToRoadblock; // size=0, offset=39
	char status; // size=0, offset=40
	char AI_Slot[13]; // size=13, offset=41
};

//typedef struct ROADBLOCK ROADBLOCK;

struct TestResult // hashcode: 0x105A4D3D (dec: 274353469)
{
	int depth; // size=0, offset=0
	VECTOR location; // size=16, offset=4
	VECTOR normal; // size=16, offset=20
};

//typedef struct TestResult TestResult;

struct BUILDING_BOX // hashcode: 0x6B53A728 (dec: 1800644392)
{
	VECTOR pos; // size=16, offset=0
	int xsize; // size=0, offset=16
	int zsize; // size=0, offset=20
	int theta; // size=0, offset=24
	int height; // size=0, offset=28
};

struct CDATA2D // hashcode: 0x077C224E (dec: 125575758)
{
	VECTOR x; // size=16, offset=0
	VECTOR axis[2]; // size=32, offset=16
	VECTOR vel; // size=16, offset=48
	int theta; // size=0, offset=64
	int length[2]; // size=8, offset=68
	int dist[2]; // size=8, offset=76
	int limit[2]; // size=8, offset=84
	int avel; // size=0, offset=92
	int isCameraOrTanner; // size=0, offset=96
};

struct CRET2D // hashcode: 0x0DF86D8D (dec: 234384781)
{
	VECTOR hit; // size=16, offset=0
	VECTOR surfNormal; // size=16, offset=16
	int penetration; // size=0, offset=32
	int neverfree; // size=0, offset=36
};

struct __tunnelcoords // hashcode: 0x7711175C (dec: 1997608796)
{
	VECTOR p1; // size=16, offset=0
	VECTOR p2; // size=16, offset=16
};
/*
typedef struct BUILDING_BOX BUILDING_BOX;

typedef struct CDATA2D CDATA2D;

typedef struct CRET2D CRET2D;

typedef struct __tunnelcoords tunnelcoords;
*/
enum ExplosionType // Hashcode: 0xD0FDC1E0 (dec: -788676128)
{
	BIG_BANG = 0,
	LITTLE_BANG = 1,
	HEY_MOMMA = 666,
	BANG_USED = 999,
};

struct _ExOBJECT // hashcode: 0x1D4ED61D (dec: 491705885)
{
	int time; // size=0, offset=0
	int speed; // size=0, offset=4
	int hscale; // size=0, offset=8
	int rscale; // size=0, offset=12
	ExplosionType type; // size=2, offset=16
	VECTOR pos; // size=16, offset=20
};

struct BOMB // hashcode: 0x9EA608A2 (dec: -1633285982)
{
	unsigned char flags; // size=0, offset=0
	unsigned char active; // size=0, offset=1
	short rot_speed; // size=0, offset=2
	VECTOR position; // size=16, offset=4
	VECTOR velocity; // size=16, offset=20
};
/*
typedef struct _ExOBJECT EXOBJECT;

typedef struct BOMB BOMB;
*/
struct COLLISION_PACKET // hashcode: 0x404603E7 (dec: 1078330343)
{
	short type; // size=0, offset=0
	short xpos; // size=0, offset=2
	short ypos; // size=0, offset=4
	short zpos; // size=0, offset=6
	short flags; // size=0, offset=8
	short yang; // size=0, offset=10
	short empty; // size=0, offset=12
	short xsize; // size=0, offset=14
	short ysize; // size=0, offset=16
	short zsize; // size=0, offset=18
};

struct _PLAYER // hashcode: 0x8C0D3284 (dec: -1945292156)
{
	long pos[4]; // size=16, offset=0
	int dir; // size=0, offset=16
	VECTOR* spoolXZ; // size=16, offset=20
	VECTOR cameraPos; // size=16, offset=24
	int cameraDist; // size=0, offset=40
	int maxCameraDist; // size=0, offset=44
	int cameraAngle; // size=0, offset=48
	int headPos; // size=0, offset=52
	int headTarget; // size=0, offset=56
	int viewChange; // size=0, offset=60
	unsigned char dying; // size=0, offset=64
	unsigned char upsideDown; // size=0, offset=65
	char onGrass; // size=0, offset=66
	char targetCarId; // size=0, offset=67
	char cameraView; // size=0, offset=68
	unsigned char headTimer; // size=0, offset=69
	char playerType; // size=0, offset=70
	char worldCentreCarId; // size=0, offset=71
	char playerCarId; // size=0, offset=72
	char cameraCarId; // size=0, offset=73
	char padid; // size=0, offset=74
	char car_is_sounding; // size=0, offset=75
	long camera_vel[3]; // size=12, offset=76
	int snd_cam_ang; // size=0, offset=88
	__skidinfo skidding; // size=2, offset=92
	__skidinfo wheelnoise; // size=2, offset=94
	__horninfo horn; // size=3, offset=96
	int car_sound_timer; // size=0, offset=100
	short revsvol; // size=0, offset=104
	short idlevol; // size=0, offset=106
	PEDESTRIAN* pPed; // size=92, offset=108
	int crash_timer; // size=0, offset=112
};

struct XZPAIR // hashcode: 0x0F1AD091 (dec: 253415569)
{
	int x; // size=0, offset=0
	int z; // size=0, offset=4
};

struct CELL_DATA // hashcode: 0x016E4A08 (dec: 24005128)
{
	unsigned short num; // size=0, offset=0
};

struct PACKED_CELL_OBJECT // hashcode: 0x4109E18D (dec: 1091166605)
{
	struct USVECTOR_NOPAD pos; // size=6, offset=0
	unsigned short value; // size=0, offset=6
};

struct PAD // hashcode: 0x3E7349EB (dec: 1047742955)
{
	unsigned char active; // size=0, offset=0
	unsigned char type; // size=0, offset=1
	unsigned char dualshock; // size=0, offset=2
	unsigned char reserved1; // size=0, offset=3
	unsigned short direct; // size=0, offset=4
	unsigned short dirnew; // size=0, offset=6
	char diranalog[4]; // size=4, offset=8
	unsigned short mapped; // size=0, offset=12
	unsigned short mapnew; // size=0, offset=14
	char mapanalog[4]; // size=4, offset=16
	struct MAPPING mappings; // size=36, offset=20
	unsigned char alarmShakeCounter; // size=0, offset=56
	unsigned char asd; // size=0, offset=57
	unsigned char sdf; // size=0, offset=58
	unsigned char dfg; // size=0, offset=59
	unsigned char delay; // size=0, offset=60
	unsigned char port; // size=0, offset=61
	unsigned char state; // size=0, offset=62
	unsigned char dsactive; // size=0, offset=63
	unsigned char* shakeptr; // size=0, offset=64
	unsigned char motors[2]; // size=2, offset=68
	unsigned char shake_type; // size=0, offset=70
	unsigned char vibrate; // size=0, offset=71
};

struct CELL_ITERATOR // hashcode: 0x4C2A91BE (dec: 1277858238)
{
	struct CELL_DATA* pcd; // size=2, offset=0
	struct PACKED_CELL_OBJECT* ppco; // size=8, offset=4
	struct XZPAIR nearCell; // size=8, offset=8
	int use_computed; // size=0, offset=16
};

struct TEX_INFO // hashcode: 0x7C1A76C5 (dec: 2082109125)
{
	char name[8]; // size=8, offset=0
	char tset; // size=0, offset=8
	char u; // size=0, offset=9
	char v; // size=0, offset=10
	char w; // size=0, offset=11
	char h; // size=0, offset=12
};

struct TEXTURE_LOOKUP // hashcode: 0x531E7A41 (dec: 1394506305)
{
	struct TEX_INFO(*Damage[6]); // size=24, offset=0
};

struct CAR_MODEL // hashcode: 0xE3A253F1 (dec: -475900943)
{
	int numFT3; // size=0, offset=0
	struct CAR_POLY* pFT3; // size=24, offset=4
	int numGT3; // size=0, offset=8
	struct CAR_POLY* pGT3; // size=24, offset=12
	int numB3; // size=0, offset=16
	struct CAR_POLY* pB3; // size=24, offset=20
	struct SVECTOR* vlist; // size=8, offset=24
	struct SVECTOR* nlist; // size=8, offset=28
};

struct plotCarGlobals // hashcode: 0xED466FF8 (dec: -314150920)
{
	unsigned char* primptr; // size=0, offset=0
	OTTYPE* ot; // size=0, offset=4
	unsigned long intensity; // size=0, offset=8
	unsigned short* pciv_clut; // size=0, offset=12
	unsigned long ShineyTPageASL16; // size=0, offset=16
	unsigned long ShineyClutASL16; // size=0, offset=20
	unsigned char* damageLevel; // size=0, offset=24
	unsigned char* shineyTable; // size=0, offset=28
	int ghost; // size=0, offset=32
};

struct _EXTRA_CIV_DATA // hashcode: 0x98F5BF74 (dec: -1728725132)
{
	int surfInd; // size=0, offset=0
	int distAlongSegment; // size=0, offset=4
	short angle; // size=0, offset=8
	unsigned short ctrlState; // size=0, offset=10
	int thrustState; // size=0, offset=12
	unsigned char palette; // size=0, offset=16
	unsigned char controlFlags; // size=0, offset=17
};

struct CIV_AI_234fake // hashcode: 0xF56A6FC4 (dec: -177573948)
{
	int NumPingedIn; // size=0, offset=0
	int OffRoad; // size=0, offset=4
	int NotDrivable; // size=0, offset=8
	int TooShortStr; // size=0, offset=12
	int NearEndStr; // size=0, offset=16
	int TooShortCrv; // size=0, offset=20
	int NearEndCrv; // size=0, offset=24
	int TooCloseNuddaCar; // size=0, offset=28
	int TooClosePlayer; // size=0, offset=32
	int InvalidRegion; // size=0, offset=36
};

typedef struct _EXTRA_CIV_DATA EXTRA_CIV_DATA;

struct COP_DATA // hashcode: 0x2EAA754B (dec: 782923083)
{
	int autoMaxPowerScaleLimit; // size=0, offset=0
	int autoDesiredSpeedScaleLimit; // size=0, offset=4
	int autoRespawnScaleLimit; // size=0, offset=8
	int autoBatterPlayerTrigger; // size=0, offset=12
	int immortal; // size=0, offset=16
	int roadblockTrigger; // size=0, offset=20
	int cutOffPowerScale; // size=0, offset=24
	int cutOffDistance; // size=0, offset=28
	short trigger[5]; // size=10, offset=32
};

struct FELONY_DATA // hashcode: 0x2264AF24 (dec: 577023780)
{
	struct FELONY_DELAY occurrenceDelay[12]; // size=48, offset=0
	struct FELONY_DELAY reoccurrenceDelay[12]; // size=48, offset=48
	struct FELONY_VALUE value[12]; // size=48, offset=96
	int pursuitFelonyScale; // size=0, offset=144
};

enum AIZone // Hashcode: 0x51DDC1C4 (dec: 1373487556)
{
	zoneFrnt = 0,
	zoneBack = 1,
	zoneLeft = 2,
	zoneRght = 3,
};

struct iVectNT // hashcode: 0x3D8D0417 (dec: 1032651799)
{
	int n; // size=0, offset=0
	int t; // size=0, offset=4
};

struct PLAYBACKCAMERA // hashcode: 0xF83C80A8 (dec: -130252632)
{
	struct VECTOR_NOPAD position; // size=12, offset=0
	struct SVECTOR angle; // size=8, offset=12
	int FrameCnt; // size=0, offset=20
	short CameraPosvy; // size=0, offset=24
	short scr_z; // size=0, offset=26
	short gCameraMaxDistance; // size=0, offset=28
	short gCameraAngle; // size=0, offset=30
	unsigned char cameraview; // size=0, offset=32
	unsigned char next; // size=0, offset=33
	unsigned char prev; // size=0, offset=34
	unsigned char idx; // size=0, offset=35
};

struct CUTSCENE_BUFFER // hashcode: 0x4B940558 (dec: 1267991896)
{
	int numResident; // size=0, offset=0
	unsigned char residentCutscenes[4]; // size=4, offset=4
	char(*residentPointers[4]); // size=16, offset=8
	char* currentPointer; // size=0, offset=24
	int bytesFree; // size=0, offset=28
	char buffer[8192]; // size=8192, offset=32
};

struct CUTSCENE_INFO // hashcode: 0x57BD570A (dec: 1472026378)
{
	unsigned short offset; // size=0, offset=0
	unsigned short size; // size=0, offset=2
};

struct CUTSCENE_HEADER // hashcode: 0xAC6560B4 (dec: -1402642252)
{
	int maxsize; // size=0, offset=0
	struct CUTSCENE_INFO data[15]; // size=60, offset=4
};

struct TPAN // hashcode: 0x984DCD6C (dec: -1739731604)
{
	unsigned char texture_page; // size=0, offset=0
	unsigned char texture_number; // size=0, offset=1
};

struct POLYFT4 // hashcode: 0x0B933067 (dec: 194195559)
{
	unsigned char id; // size=0, offset=0
	unsigned char texture_set; // size=0, offset=1
	unsigned char texture_id; // size=0, offset=2
	unsigned char spare; // size=0, offset=3
	unsigned char v0; // size=0, offset=4
	unsigned char v1; // size=0, offset=5
	unsigned char v2; // size=0, offset=6
	unsigned char v3; // size=0, offset=7
	struct UV_INFO uv0; // size=2, offset=8
	struct UV_INFO uv1; // size=2, offset=10
	struct UV_INFO uv2; // size=2, offset=12
	struct UV_INFO uv3; // size=2, offset=14
	struct RGB color; // size=4, offset=16
};

struct POLYGT4 // hashcode: 0x9BF00654 (dec: -1678768556)
{
	unsigned char id; // size=0, offset=0
	unsigned char texture_set; // size=0, offset=1
	unsigned char texture_id; // size=0, offset=2
	unsigned char spare; // size=0, offset=3
	unsigned char v0; // size=0, offset=4
	unsigned char v1; // size=0, offset=5
	unsigned char v2; // size=0, offset=6
	unsigned char v3; // size=0, offset=7
	unsigned char n0; // size=0, offset=8
	unsigned char n1; // size=0, offset=9
	unsigned char n2; // size=0, offset=10
	unsigned char n3; // size=0, offset=11
	struct UV_INFO uv0; // size=2, offset=12
	struct UV_INFO uv1; // size=2, offset=14
	struct UV_INFO uv2; // size=2, offset=16
	struct UV_INFO uv3; // size=2, offset=18
	struct RGB color; // size=4, offset=20
};


struct SMOKE // hashcode: 0x9F745C35 (dec: -1619764171)
{
	UnpaddedHackVector position; // size=12, offset=0
	UnpaddedCharVector drift; // size=3, offset=12
	UnpaddedCharVector drift_change; // size=3, offset=15
	UnpaddedHackVector final_tail_pos; // size=12, offset=20
	unsigned char step; // size=0, offset=32
	unsigned char pos; // size=0, offset=33
	short start_w; // size=0, offset=34
	short final_w; // size=0, offset=36
	char life; // size=0, offset=38
	char halflife; // size=0, offset=39
	unsigned short flags; // size=0, offset=40
	unsigned char num; // size=0, offset=42
	unsigned char t_step; // size=0, offset=43
	short transparency; // size=0, offset=44
};

struct DEBRIS // hashcode: 0x7F875F65 (dec: 2139578213)
{
	VECTOR position; // size=16, offset=0
	SVECTOR direction; // size=8, offset=16
	unsigned short life; // size=0, offset=24
	unsigned short flags; // size=0, offset=26
	unsigned short num; // size=0, offset=28
	unsigned short pos; // size=0, offset=30
	struct RGB rgb; // size=4, offset=32
	char step; // size=0, offset=36
	char type; // size=0, offset=37
};

struct LEAF // hashcode: 0x8E232930 (dec: -1910298320)
{
	VECTOR position; // size=16, offset=0
	SVECTOR direction; // size=8, offset=16
	unsigned short life; // size=0, offset=24
	unsigned short flags; // size=0, offset=26
	unsigned short num; // size=0, offset=28
	unsigned short pos; // size=0, offset=30
	struct RGB rgb; // size=4, offset=32
	char step; // size=0, offset=36
	char type; // size=0, offset=37
	short sin_index1; // size=0, offset=38
	short sin_index2; // size=0, offset=40
	char sin_addition1; // size=0, offset=42
	char sin_addition2; // size=0, offset=43
};

struct DAMAGED_LAMP // hashcode: 0x1240B5B5 (dec: 306230709)
{
	struct CELL_OBJECT* cop; // size=16, offset=0
	char damage; // size=0, offset=4
};

struct DAMAGED_OBJECT // hashcode: 0xC8C77ECE (dec: -926449970)
{
	struct CELL_OBJECT cop; // size=16, offset=0
	char active; // size=0, offset=16
	char damage; // size=0, offset=17
	int rot_speed; // size=0, offset=20
	struct SVECTOR velocity; // size=8, offset=24
	int vx; // size=0, offset=32
};

struct TRI_POINT // hashcode: 0x50D0CFA0 (dec: 1355861920)
{
	struct BVECTOR v0; // size=4, offset=0
	struct BVECTOR v1; // size=4, offset=4
	struct BVECTOR v2; // size=4, offset=8
};

struct TRI_POINT_LONG // hashcode: 0xAFB61D06 (dec: -1347019514)
{
	struct VECTOR_NOPAD v0; // size=12, offset=0
	struct VECTOR_NOPAD v1; // size=12, offset=12
	struct VECTOR_NOPAD v2; // size=12, offset=24
};

struct RAIN_TYPE // hashcode: 0x4B9D35B0 (dec: 1268594096)
{
	struct VECTOR_NOPAD position; // size=12, offset=0
	struct SVECTOR oldposition; // size=8, offset=12
};

struct LAMP_STREAK // hashcode: 0xB0E3FA15 (dec: -1327236587)
{
	struct SXYPAIR light_trails[4]; // size=16, offset=0
	int id; // size=0, offset=16
	short clock; // size=0, offset=20
	char set; // size=0, offset=22
};

struct ROUTE_DATA // hashcode: 0xBBEEB7AD (dec: -1141983315)
{
	short type; // size=0, offset=0
	short height; // size=0, offset=2
	short objectAngle; // size=0, offset=4
};

struct DENTUVS // hashcode: 0x7F7AFC21 (dec: 2138766369)
{
	char u3; // size=0, offset=0
};

struct HUBCAP // hashcode: 0x8B4D12CD (dec: -1957883187)
{
	int Present[4]; // size=16, offset=0
	VECTOR Offset[4]; // size=64, offset=16
	MATRIX Orientation; // size=32, offset=80
	MATRIX LocalOrientation; // size=32, offset=112
	VECTOR Position; // size=16, offset=144
	VECTOR Direction; // size=16, offset=160
	float Height; // size=0, offset=176
	int Duration; // size=0, offset=180
};

typedef struct DENTUVS DENTUVS;

typedef struct HUBCAP HUBCAP;

struct REPLAY_ICON // hashcode: 0x6B6009DA (dec: 1801456090)
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	struct TEXTURE_DETAILS* texture; // size=14, offset=4
	char* TextPtr; // size=0, offset=8
	short tx; // size=0, offset=12
	short ty; // size=0, offset=14
};

struct _pct // hashcode: 0x3CC33EEE (dec: 1019428590)
{
	struct DB* current; // size=128, offset=0
	unsigned short(*ptexture_pages)[128]; // size=4, offset=4
	unsigned short(*ptexture_cluts)[128][32]; // size=4, offset=8
	long f4colourTable[32]; // size=128, offset=12
	int* polySizes; // size=0, offset=140
	char* primptr; // size=0, offset=144
	OTTYPE* ot; // size=0, offset=148
	unsigned long clut; // size=0, offset=152
	unsigned long tpage; // size=0, offset=156
	unsigned long colour; // size=0, offset=160
	int flags; // size=0, offset=164
	struct SVECTOR* verts; // size=8, offset=168
	unsigned long lastTexInfo; // size=0, offset=172
	int scribble[8]; // size=32, offset=176
	int model; // size=0, offset=208
};

struct MATRIX2 // hashcode: 0x7326ABFE (dec: 1931914238)
{
	short m[3][3]; // size=18, offset=0
	short computed; // size=0, offset=18
	char null[12]; // size=12, offset=20
};

struct Spool // hashcode: 0x25ACC86C (dec: 632080492)
{
	unsigned short offset; // size=0, offset=0
	unsigned char connected_areas[2]; // size=2, offset=2
	unsigned char pvs_size; // size=0, offset=4
	unsigned char cell_data_size[3]; // size=3, offset=5
	unsigned char super_region; // size=0, offset=8
	unsigned char num_connected_areas; // size=0, offset=9
	unsigned char roadm_size; // size=0, offset=10
	unsigned char roadh_size; // size=0, offset=11
};

union VERT_INDEX
{
	struct {
		unsigned char v0; // size=0, offset=4
		unsigned char v1; // size=0, offset=5
		unsigned char v2; // size=0, offset=6
		unsigned char v3; // size=0, offset=7
	};
	uint value;
};

struct PL_POLYFT4 // hashcode: 0x851A459F (dec: -2061875809)
{
	unsigned char id; // size=0, offset=0
	unsigned char texture_set; // size=0, offset=1
	unsigned char texture_id; // size=0, offset=2
	unsigned char th; // size=0, offset=3
	unsigned char v0; // size=0, offset=4
	unsigned char v1; // size=0, offset=5
	unsigned char v2; // size=0, offset=6
	unsigned char v3; // size=0, offset=7
	struct UV_INFO uv0; // size=2, offset=8
	struct UV_INFO uv1; // size=2, offset=10
	struct UV_INFO uv2; // size=2, offset=12
	struct UV_INFO uv3; // size=2, offset=14
};

struct MVERTEX // hashcode: 0xCC5E5250 (dec: -866233776)
{
	short vx; // size=0, offset=0
	short vy; // size=0, offset=2
	short vz; // size=0, offset=4
	union {
		short val;
		struct {
			unsigned char u0; // size=0, offset=0
			unsigned char v0; // size=0, offset=1
		};
	}uv; // size=0, offset=6
};

struct VERTEX // hashcode: 0x01A9F7DD (dec: 27916253)
{
	DVECTOR coord; // size=4, offset=0
	UV_INFO uv_coord; // size=2, offset=4
	unsigned char pad[2]; // size=2, offset=6
};

struct TRAILBLAZER_DATA // hashcode: 0x99CBFE9E (dec: -1714684258)
{
	int x; // size=0, offset=0
	int z; // size=0, offset=4
	short y; // size=0, offset=8
	short rot; // size=0, offset=10
};

struct SMASHED_CONE // hashcode: 0xC79161AF (dec: -946773585)
{
	char cone; // size=0, offset=0
	unsigned char active : 7; // size=7, offset=8
	unsigned char side : 1; // size=1, offset=15
	short rot_speed; // size=0, offset=2
	VECTOR velocity; // size=16, offset=4
};

struct POLYCOORD // hashcode: 0x567DCFE0 (dec: 1451085792)
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short u; // size=0, offset=4
	short v; // size=0, offset=6
	short w; // size=0, offset=8
	short h; // size=0, offset=10
};

struct EventGlobal // hashcode: 0xF4852999 (dec: -192599655)
{
	int camera; // size=0, offset=0
	int draw; // size=0, offset=4
	struct _EVENT** track; // size=40, offset=8
	struct _EVENT* cameraEvent; // size=40, offset=12
};

enum SpecialCamera // Hashcode: 0xB5557F2F (dec: -1252688081)
{
	SPECIAL_CAMERA_SET = 0,
	SPECIAL_CAMERA_SET2 = 1,
	SPECIAL_CAMERA_RESET = 2,
	SPECIAL_CAMERA_WAIT = 3,
};

struct MissionTrain // hashcode: 0x1C680836 (dec: 476579894)
{
	struct _EVENT* engine; // size=40, offset=0
	int* node; // size=0, offset=4
	int cornerSpeed; // size=0, offset=8
	int initialStraightSpeed; // size=0, offset=12
	int finalStraightSpeed; // size=0, offset=16
	int start; // size=0, offset=20
	int startDir; // size=0, offset=24
};

struct Foam // hashcode: 0xFD0C756C (dec: -49515156)
{
	struct MODEL* model; // size=36, offset=0
	int rotate; // size=0, offset=4
};

struct EventCarriage // hashcode: 0xA136BEAC (dec: -1590247764)
{
	short rotation; // size=0, offset=0
	short vel; // size=0, offset=2
};

struct MultiCar // hashcode: 0x862F8E20 (dec: -2043703776)
{
	struct _EVENT* event; // size=40, offset=0
	int count; // size=0, offset=4
};

struct Helicopter // hashcode: 0xE626A675 (dec: -433674635)
{
	int speed; // size=0, offset=0
	short pitch; // size=0, offset=4
	short dp; // size=0, offset=6
	short roll; // size=0, offset=8
	short dr; // size=0, offset=10
	int lastX; // size=0, offset=12
	int lastZ; // size=0, offset=16
	struct TEXTURE_DETAILS rotorTexture; // size=14, offset=20
	short rotorrot; // size=0, offset=34
	short rotorvel; // size=0, offset=36
	int cleanModel; // size=0, offset=40
	int deadModel; // size=0, offset=44
};

struct Detonator // hashcode: 0xB22424C8 (dec: -1306254136)
{
	int timer; // size=0, offset=0
	int count; // size=0, offset=4
};

struct CameraDelay // hashcode: 0xE75FD106 (dec: -413150970)
{
	int delay; // size=0, offset=0
	int type; // size=0, offset=4
};

enum VisType // Hashcode: 0x2316487E (dec: 588662910)
{
	VIS_INIT = 0,
	VIS_SORT = 1,
	VIS_ADD = 2,
	VIS_NEXT = 3,
};

struct EventCamera // hashcode: 0x13E042AF (dec: 333464239)
{
	VECTOR position; // size=16, offset=0
	short yAng; // size=0, offset=16
	MATRIX matrix; // size=32, offset=20
	int rotate; // size=0, offset=52
};

enum Station // Hashcode: 0xABF98660 (dec: -1409710496)
{
	EVENT_NO_STATION = 0,
	EVENT_APPROACHING = 1,
	EVENT_LEAVING = 2,
};

struct MULTICAR_DATA // hashcode: 0xFB584F7B (dec: -78098565)
{
	int x; // size=0, offset=0
	int z; // size=0, offset=4
	unsigned char palette; // size=0, offset=8
	unsigned char model; // size=0, offset=9
	short rot; // size=0, offset=10
};

struct RENDER_ARG // hashcode: 0x5BAC7E8D (dec: 1538031245)
{
	unsigned char render; // size=0, offset=0
	unsigned char credits; // size=0, offset=1
	unsigned short recap; // size=0, offset=2
};

struct RENDER_ARGS // hashcode: 0x9CEEC3A3 (dec: -1662073949)
{
	unsigned char nRenders; // size=0, offset=0
	unsigned char subtitle; // size=0, offset=1
	char screenx; // size=0, offset=2
	char screeny; // size=0, offset=3
	struct RENDER_ARG Args[4]; // size=16, offset=4
};

typedef struct __envsound // hashcode: 0x7218E697 (dec: 1914234519)
{
	unsigned char type; // size=0, offset=0
	unsigned char flags; // size=0, offset=1
	VECTOR pos; // size=16, offset=4
	VECTOR pos2; // size=16, offset=20
	int bank; // size=0, offset=36
	int sample; // size=0, offset=40
	int vol; // size=0, offset=44
} __envsound;

struct __envsoundtags // hashcode: 0x8645A61D (dec: -2042255843)
{
	int frame_cnt; // size=0, offset=0
	int func_cnt; // size=0, offset=4
	int num_envsnds; // size=0, offset=8
	int envsnd_cnt; // size=0, offset=12
};

typedef struct __envsoundinfo // hashcode: 0x45AC9536 (dec: 1168938294)
{
	VECTOR eff_pos[4]; // size=64, offset=0
	VECTOR cam_pos; // size=16, offset=64
	float g[4]; // size=16, offset=80
	int thisS[4]; // size=16, offset=96
	int playing_sound[4]; // size=16, offset=112
	int chan[4]; // size=16, offset=128
	unsigned long flags; // size=0, offset=144
} __envsoundinfo;

struct SPEECH_QUEUE // hashcode: 0xF7AB07B1 (dec: -139786319)
{
	char allowed; // size=0, offset=0
	char chan; // size=0, offset=1
	char is_playing; // size=0, offset=2
	int count; // size=0, offset=4
	char reverb; // size=0, offset=8
	int slot[7]; // size=28, offset=12
};

struct __othercarsound // hashcode: 0x88F0C520 (dec: -1997486816)
{
	int car; // size=0, offset=0
	int chan; // size=0, offset=4
	char in_use; // size=0, offset=8
	char stopped; // size=0, offset=9
	char idle; // size=0, offset=10
};

typedef struct __tunnelinfo // hashcode: 0xC172C5A2 (dec: -1049442910)
{
	char num_tunnels; // size=0, offset=0
	char tunnel_cnt; // size=0, offset=1
	struct __tunnelcoords coords[29]; // size=928, offset=4
} __tunnelinfo;

struct __bitfield64 // hashcode: 0x2A3F54F0 (dec: 708793584)
{
	long h; // size=0, offset=0
	long l; // size=0, offset=4
};

struct GEAR_DESC // hashcode: 0xE4380123 (dec: -466091741)
{
	int lowidl_ws; // size=0, offset=0
	int low_ws; // size=0, offset=4
	int hi_ws; // size=0, offset=8
	int ratio_ac; // size=0, offset=12
	int ratio_id; // size=0, offset=16
};

struct PSXSCREEN // hashcode: 0x9E392939 (dec: -1640421063)
{
	unsigned char index; // size=0, offset=0
	unsigned char numButtons; // size=0, offset=1
	unsigned char userFunctionNum; // size=0, offset=2
	struct PSXBUTTON buttons[8]; // size=480, offset=4
};

enum GAMEMODE // Hashcode: 0xA71425E4 (dec: -1491851804)
{
	GAMEMODE_NORMAL = 0,
	GAMEMODE_QUIT = 1,
	GAMEMODE_RESTART = 2,
	GAMEMODE_REPLAY = 3,
	GAMEMODE_DIRECTOR = 4,
	GAMEMODE_NEXTMISSION = 5,
	GAMEMODE_DEMO = 6,
};

struct MISSION_STEP // hashcode: 0x6445CD70 (dec: 1682296176)
{
	unsigned char flags : 3; // size=3, offset=0
	unsigned char recap : 5; // size=5, offset=3
	unsigned char data : 7; // size=7, offset=8
	unsigned char disc : 1; // size=1, offset=15
};

struct BOUND_BOX // hashcode: 0xF08E6742 (dec: -259102910)
{
	int x0; // size=0, offset=0
	int y0; // size=0, offset=4
	int z0; // size=0, offset=8
	int x1; // size=0, offset=12
	int y1; // size=0, offset=16
	int z1; // size=0, offset=20
};

struct _HANDLING_TYPE // hashcode: 0x61CB7B87 (dec: 1640725383)
{
	char frictionScaleRatio; // size=0, offset=0
	char aggressiveBraking; // size=0, offset=1
	char fourWheelDrive; // size=0, offset=2
	char autoBrakeOn; // size=0, offset=3
};

struct CHEATS // hashcode: 0x77AC236B (dec: 2007769963)
{
	int RearWheelSteer; // size=0, offset=0
	int MiniCars; // size=0, offset=4
	int Stilts; // size=0, offset=8
	int LowGravity; // size=0, offset=12
	int Australia; // size=0, offset=16
	int MagicMirror; // size=0, offset=20
};

struct BOXINFO // hashcode: 0x0A20DC94 (dec: 169925780)
{
	VECTOR vel; // size=16, offset=0
	VECTOR pos; // size=16, offset=16
	int sf; // size=0, offset=32
	int xs; // size=0, offset=36
	int zs; // size=0, offset=40
	int w; // size=0, offset=44
	int h; // size=0, offset=48
	int zb; // size=0, offset=52
	int ypos; // size=0, offset=56
};

struct MAP_DATA // hashcode: 0x83C30077 (dec: -2084372361)
{
	_CAR_DATA* cp; // size=0, offset=0
	VECTOR* base; // size=16, offset=4
	VECTOR* pos; // size=16, offset=8
	VECTOR* vel; // size=16, offset=12
	VECTOR* size; // size=16, offset=16
	int intention; // size=0, offset=20
	int* map; // size=0, offset=24
	int* local; // size=0, offset=28
};

struct GAME_SAVE_HEADER // hashcode: 0xB1E0BE5E (dec: -1310671266)
{
	unsigned long magic; // size=0, offset=0
	unsigned char gMissionLadderPos; // size=0, offset=4
	unsigned char pad1; // size=0, offset=5
	unsigned char pad2; // size=0, offset=6
	unsigned char pad3; // size=0, offset=7
	struct MISSION_DATA SavedData; // size=228, offset=8
	int reserved[8]; // size=32, offset=236
};

struct CONFIG_SAVE_HEADER // hashcode: 0x6370AFC2 (dec: 1668329410)
{
	unsigned long magic; // size=0, offset=0
	int gMasterVolume; // size=0, offset=4
	int gMusicVolume; // size=0, offset=8
	int gSoundMode; // size=0, offset=12
	int gVibration; // size=0, offset=16
	int gCopDifficultyLevel; // size=0, offset=20
	int gFurthestMission; // size=0, offset=24
	struct MAPPING PadMapping[2]; // size=72, offset=28
	struct SCORE_TABLES ScoreTables; // size=2160, offset=100
	int PALAdjustX; // size=0, offset=2260
	int PALAdjustY; // size=0, offset=2264
	int NTSCAdjustX; // size=0, offset=2268
	int NTSCAdjustY; // size=0, offset=2272
	int gSubtitles; // size=0, offset=2276
	struct ACTIVE_CHEATS AvailableCheats; // size=4, offset=2280
	int reserved[6]; // size=24, offset=2284
};

enum GAMETYPE // Hashcode: 0xD623FEBE (dec: -702284098)
{
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

struct OUT_CELL_FILE_HEADER // hashcode: 0x5665F7D5 (dec: 1449523157)
{
	int cells_across; // size=0, offset=0
	int cells_down; // size=0, offset=4
	int cell_size; // size=0, offset=8
	int num_regions; // size=0, offset=12
	int region_size; // size=0, offset=16
	int num_cell_objects; // size=0, offset=20
	int num_cell_data; // size=0, offset=24
	int ambient_light_level; // size=0, offset=28
	struct VECTOR_NOPAD light_source; // size=12, offset=32
};

enum EXIT_VALUE // Hashcode: 0x3F23BCE8 (dec: 1059306728)
{
	MENU_QUIT_NONE = 0,
	MENU_QUIT_CONTINUE = 1,
	MENU_QUIT_QUIT = 2,
	MENU_QUIT_RESTART = 3,
	MENU_QUIT_DIRECTOR = 4,
	MENU_QUIT_QUICKREPLAY = 5,
	MENU_QUIT_BACKMENU = 6,
	MENU_QUIT_NEXTMISSION = 7,
};

struct XYWH // hashcode: 0x1C1E57F6 (dec: 471750646)
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short w; // size=0, offset=4
	short h; // size=0, offset=6
};

struct MENU_HEADER // hashcode: 0x0BDA3805 (dec: 198850565)
{
	char* Title; // size=0, offset=0
	struct XYWH Bound; // size=8, offset=4
	unsigned char NumItems; // size=0, offset=12
	struct MENU_ITEM* MenuItems; // size=20, offset=16
};

typedef void(*pauseFunc)(int dir);

struct MENU_ITEM // hashcode: 0x9519D4FB (dec: -1793469189)
{
	char* Text; // size=0, offset=0
	unsigned char Type; // size=0, offset=4
	unsigned char Justify; // size=0, offset=5
	pauseFunc func; // size=0, offset=8
	enum EXIT_VALUE ExitValue; // size=1, offset=12
	struct MENU_HEADER* SubMenu; // size=0, offset=16
};

struct AREA_LOAD_INFO // hashcode: 0xC55B5A7D (dec: -983868803)
{
	int xoffset; // size=0, offset=0
	int zoffset; // size=0, offset=4
};

struct ROAD_MAP_LUMP_DATA // hashcode: 0xE3B836E2 (dec: -474466590)
{
	int width; // size=0, offset=0
	int height; // size=0, offset=4
	int unitXMid; // size=0, offset=8
	int unitZMid; // size=0, offset=12
};

struct __io // hashcode: 0x3FBD636F (dec: 1069376367)
{
	char in; // size=0, offset=0
	char out; // size=0, offset=1
};

struct __xa_request // hashcode: 0xD6B93389 (dec: -692505719)
{
	short delay; // size=0, offset=0
	char bank; // size=0, offset=2
	char track; // size=0, offset=3
	char mission; // size=0, offset=4
	char cutscene; // size=0, offset=5
};

struct _MISSION // hashcode: 0x85F0EB6C (dec: -2047808660)
{
	int id; // size=0, offset=0
	int size; // size=0, offset=4
	int city; // size=0, offset=8
	int time; // size=0, offset=12
	int weather; // size=0, offset=16
	struct XYPAIR playerStartPosition; // size=8, offset=20
	int playerStartRotation; // size=0, offset=28
	int type; // size=0, offset=32
	short timer; // size=0, offset=36
	short timerFlags; // size=0, offset=38
	int strings; // size=0, offset=40
	struct _COP_DATA cops; // size=16, offset=44
	int msgCarWrecked; // size=0, offset=60
	int msgOutOfTime; // size=0, offset=64
	int msgComplete; // size=0, offset=68
	int region; // size=0, offset=72
	int route; // size=0, offset=76
	int msgDrowned; // size=0, offset=80
	int playerCarModel; // size=0, offset=84
	int playerCarColour; // size=0, offset=88
	int maxDamage; // size=0, offset=92
	int residentModels[5]; // size=20, offset=96
	int nCutscenes; // size=0, offset=116
	int title; // size=0, offset=120
	int msgPoliceCar; // size=0, offset=124
	int msgDoorsLocked; // size=0, offset=128
};

struct _ROUTE_INFO // hashcode: 0x5A21DB68 (dec: 1512168296)
{
	int nJunctions; // size=0, offset=0
	char data[1000][4]; // size=4000, offset=4
	struct LEAD_PARAMETERS parameters; // size=64, offset=4004
};

struct MR_MISSION // hashcode: 0xF240F754 (dec: -230623404)
{
	int active; // size=0, offset=0
	int gameover_delay; // size=0, offset=4
	enum PAUSEMODE gameover_mode; // size=1, offset=8
	short message_timer[2]; // size=4, offset=10
	short message_priority[2]; // size=4, offset=14
	char(*message_string[2]); // size=8, offset=20
	struct MR_TIMER timer[2]; // size=24, offset=28
	_TARGET* CarTarget; // size=64, offset=52
	_TARGET* ChaseTarget; // size=64, offset=56
	int PhantomCarId; // size=0, offset=60
	int ChaseHitDelay; // size=0, offset=64
	char* StealMessage; // size=0, offset=68
};

struct STOPCOPS // hashcode: 0x145E8976 (dec: 341739894)
{
	struct VECTOR_NOPAD pos; // size=12, offset=0
	int radius; // size=0, offset=12
};

enum FAIL_REASON // Hashcode: 0x6CB87873 (dec: 1824028787)
{
	FAILED_OUTOFTIME = 0,
	FAILED_CnR_LOSTHIM = 1,
	FAILED_MESSAGESET = 2,
};

struct MR_THREAD // hashcode: 0xEFF00E62 (dec: -269480350)
{
	unsigned char active; // size=0, offset=0
	unsigned char player; // size=0, offset=1
	unsigned long* initial_sp; // size=0, offset=4
	unsigned long* pc; // size=0, offset=8
	unsigned long* sp; // size=0, offset=12
};

struct POLYFT3 // hashcode: 0xF42A702D (dec: -198545363)
{
	unsigned char id; // size=0, offset=0
	unsigned char texture_set; // size=0, offset=1
	unsigned char texture_id; // size=0, offset=2
	unsigned char spare; // size=0, offset=3
	unsigned char v0; // size=0, offset=4
	unsigned char v1; // size=0, offset=5
	unsigned char v2; // size=0, offset=6
	unsigned char pad; // size=0, offset=7
	struct UV_INFO uv0; // size=2, offset=8
	struct UV_INFO uv1; // size=2, offset=10
	struct UV_INFO uv2; // size=2, offset=12
	struct UV_INFO pad2; // size=2, offset=14
	struct RGB color; // size=4, offset=16
};

struct POLYGT3
{
	unsigned char id; // size=0, offset=0
	unsigned char texture_set; // size=0, offset=1
	unsigned char texture_id; // size=0, offset=2
	unsigned char spare; // size=0, offset=3
	unsigned char v0; // size=0, offset=4
	unsigned char v1; // size=0, offset=5
	unsigned char v2; // size=0, offset=6
	unsigned char pad; // size=0, offset=7
	unsigned char n0; // size=0, offset=8
	unsigned char n1; // size=0, offset=9
	unsigned char n2; // size=0, offset=10
	unsigned char pad2; // size=0, offset=11
	struct UV_INFO uv0; // size=2, offset=12
	struct UV_INFO uv1; // size=2, offset=14
	struct UV_INFO uv2; // size=2, offset=16
	struct UV_INFO pad3; // size=2, offset=18
	struct RGB color; // size=4, offset=20
};

enum LIMBS // Hashcode: 0x200BA5A5 (dec: 537634213)
{
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

struct BONE // hashcode: 0xC453A1B7 (dec: -1001152073)
{
	enum LIMBS id; // size=1, offset=0
	struct BONE* pParent; // size=68, offset=4
	char numChildren; // size=0, offset=8
	BONE(*pChildren[3]); // size=12, offset=12
	SVECTOR_NOPAD* pvOrigPos; // size=6, offset=24
	SVECTOR* pvRotation; // size=8, offset=28
	VECTOR vOffset; // size=16, offset=32
	VECTOR vCurrPos; // size=16, offset=48
	MODEL** pModel; // size=36, offset=64
};

enum TEXTURE_PALS // Hashcode: 0x7EFDB21D (dec: 2130555421)
{
	NO_PAL = 0,
	JEANS_PAL = 1,
	ARM_PAL = 2,
	CHEST_PAL = 3,
};

struct PED_DATA // hashcode: 0xF0838D4B (dec: -259814069)
{
	char cWidth; // size=0, offset=0
	unsigned char cAdj; // size=0, offset=1
	struct TEXTURE_DETAILS* ptd; // size=14, offset=4
	enum TEXTURE_PALS texPal; // size=1, offset=8
};

struct tRay // hashcode: 0x9D13B2B7 (dec: -1659653449)
{
	long org[4]; // size=16, offset=0
	long dir[4]; // size=16, offset=16
};

struct tRange // hashcode: 0x2599E03D (dec: 630841405)
{
	int lower; // size=0, offset=0
	int upper; // size=0, offset=4
};

struct tAABB // hashcode: 0x67B18B0E (dec: 1739688718)
{
	struct tRange slab[3]; // size=24, offset=0
};

struct DUPLICATION // hashcode: 0x6B8217F0 (dec: 1803687920)
{
	char* buffer; // size=0, offset=0
	int size; // size=0, offset=4
};

struct tNode // hashcode: 0xA7EA5E4B (dec: -1477812661)
{
	int vx; // size=0, offset=0
	int vy; // size=0, offset=4
	int vz; // size=0, offset=8
	unsigned short dist; // size=0, offset=12
	unsigned short ptoey; // size=0, offset=14
};

struct PATHFIND_237fake // hashcode: 0xA878A4A1 (dec: -1468488543)
{
	short dx; // size=0, offset=0
	short dz; // size=0, offset=2
};

struct PATHFIND_238fake // hashcode: 0x9B0AB30F (dec: -1693797617)
{
	short dx; // size=0, offset=0
	short dz; // size=0, offset=2
};

struct PLAYER_SCORE // hashcode: 0x4C80DCD4 (dec: 1283513556)
{
	int time; // size=0, offset=0
	int P2time; // size=0, offset=4
	short items; // size=0, offset=8
	short P2items; // size=0, offset=10
	char name[6]; // size=6, offset=12
};

struct SEATED_PEDESTRIANS // hashcode: 0x75CFA44E (dec: 1976542286)
{
	int x; // size=0, offset=0
	int z; // size=0, offset=4
	short rotation; // size=0, offset=8
	char index; // size=0, offset=10
	char pad; // size=0, offset=11
};

struct CAR_COLLISION_BOX // hashcode: 0xE148B668 (dec: -515328408)
{
	int min_x; // size=0, offset=0
	int max_x; // size=0, offset=4
	int min_z; // size=0, offset=8
	int max_z; // size=0, offset=12
};

struct PEDESTRIAN_ROADS // hashcode: 0xC3763082 (dec: -1015664510)
{
	short pos; // size=0, offset=0
	short north; // size=0, offset=2
	short south; // size=0, offset=4
	short east; // size=0, offset=6
	short west; // size=0, offset=8
};

struct OUT_FONTINFO // hashcode: 0x22390EDA (dec: 574164698)
{
	unsigned char x; // size=0, offset=0
	unsigned char y; // size=0, offset=1
	char offx; // size=0, offset=2
	char offy; // size=0, offset=3
	unsigned char width; // size=0, offset=4
	unsigned char height; // size=0, offset=5
	unsigned short pad; // size=0, offset=6
};

struct FONT_DIGIT // hashcode: 0x2500B456 (dec: 620803158)
{
	char xOffset; // size=0, offset=0
	char width; // size=0, offset=1
};

struct TEXINF // hashcode: 0xFC140D7C (dec: -65794692)
{
	unsigned short id; // size=0, offset=0
	unsigned short nameoffset; // size=0, offset=2
	unsigned char x; // size=0, offset=4
	unsigned char y; // size=0, offset=5
	unsigned char width; // size=0, offset=6
	unsigned char height; // size=0, offset=7
};

struct SHADOWHDR // hashcode: 0x4ED3B57A (dec: 1322497402)
{
	unsigned long num_common_verts; // size=0, offset=0
	unsigned short num_verts_total; // size=0, offset=4
	unsigned short num_polys_total; // size=0, offset=6
	unsigned short vert_offsets[4]; // size=8, offset=8
	unsigned short nverts[4]; // size=8, offset=16
	unsigned short npolys[4]; // size=8, offset=24
	unsigned long(*poly_block[4]); // size=16, offset=32
	struct SVECTOR* vertices; // size=8, offset=48
};

struct TYRE_TRACK // hashcode: 0xF19415A8 (dec: -241953368)
{
	char type; // size=0, offset=0
	char shade; // size=0, offset=1
	char shade_type; // size=0, offset=2
	char surface; // size=0, offset=3
	struct SVECTOR_NOPAD p1; // size=6, offset=4
	struct SVECTOR_NOPAD p2; // size=6, offset=10
	struct SVECTOR_NOPAD p3; // size=6, offset=16
	struct SVECTOR_NOPAD p4; // size=6, offset=22
};

struct S_XYZ // hashcode: 0x44EE024B (dec: 1156448843)
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short z; // size=0, offset=4
};

struct FLAREREC // hashcode: 0x61D9DD50 (dec: 1641667920)
{
	struct RGB16 transparency; // size=8, offset=0
	char size; // size=0, offset=8
	short gapmod; // size=0, offset=10
};

struct __LSBDinfo // hashcode: 0x6EB8DAAC (dec: 1857608364)
{
	int addr; // size=0, offset=0
	int memtop; // size=0, offset=4
	int count[7]; // size=28, offset=8
	int bnktop[7]; // size=28, offset=36
	int append; // size=0, offset=64
};

struct CHANNEL_DATA // hashcode: 0x1B8E1AD1 (dec: 462297809)
{
	SpuVoiceAttr attr; // size=64, offset=0
	unsigned char loop; // size=0, offset=64
	unsigned char locked; // size=0, offset=65
	unsigned short time; // size=0, offset=66
	long samplerate; // size=0, offset=68
	char player; // size=0, offset=72
	long srcvolume; // size=0, offset=76
	long volumeScale; // size=0, offset=80
	unsigned short srcpitch; // size=0, offset=84
	unsigned short dopplerScale; // size=0, offset=86
	long cameradist; // size=0, offset=88
	long lastcameradist; // size=0, offset=92
	VECTOR* srcposition; // size=16, offset=96
	VECTOR position; // size=16, offset=100
	long* srcvelocity; // size=0, offset=116
};

struct SAMPLE_DATA // hashcode: 0x2179B04F (dec: 561623119)
{
	unsigned long address; // size=0, offset=0
	unsigned long length; // size=0, offset=4
	unsigned long loop; // size=0, offset=8
	unsigned long samplerate; // size=0, offset=12
};

struct __pauseinfo // hashcode: 0x31AB86B4 (dec: 833324724)
{
	unsigned short pitch[16]; // size=32, offset=0
	unsigned short voll[16]; // size=32, offset=32
	unsigned short volr[16]; // size=32, offset=64
	unsigned short max; // size=0, offset=96
	unsigned short lev; // size=0, offset=98
};

struct SPOOLQ // hashcode: 0xF6540C3E (dec: -162264002)
{
	unsigned char type; // size=0, offset=0
	unsigned char data; // size=0, offset=1
	unsigned short nsectors; // size=0, offset=2
	unsigned long sector; // size=0, offset=4
	char* addr; // size=0, offset=8
	void (*func)(); // size=0, offset=12
#ifdef _DEBUG
	const char* requestby;
	int requestbyline;
#endif
};

struct SPL_REGIONINFO // hashcode: 0xDA8E3C77 (dec: -628212617)
{
	unsigned short region_to_unpack; // size=0, offset=0
	unsigned short target_barrel_region; // size=0, offset=2
	int nsectors; // size=0, offset=4
	char* cell_addr; // size=0, offset=8
	char* roadm_addr; // size=0, offset=12
};

struct AreaDataStr // hashcode: 0x2EA8DA37 (dec: 782817847)
{
	unsigned short gfx_offset; // size=0, offset=0
	unsigned short model_offset; // size=0, offset=2
	unsigned short music_offset; // size=0, offset=4
	unsigned short ambient_offset; // size=0, offset=6
	unsigned char model_size; // size=0, offset=8
	unsigned char pad; // size=0, offset=9
	unsigned char num_tpages; // size=0, offset=10
	unsigned char ambient_size; // size=0, offset=11
	unsigned char music_size; // size=0, offset=12
	unsigned char music_samples_size; // size=0, offset=13
	unsigned char music_id; // size=0, offset=14
	unsigned char ambient_id; // size=0, offset=15
};

struct DRAW_MODE // hashcode: 0x568DA31F (dec: 1452122911)
{
	short x1; // size=0, offset=0
	short y1; // size=0, offset=2
	short x2; // size=0, offset=4
	short y2; // size=0, offset=6
	short width; // size=0, offset=8
	short height; // size=0, offset=10
	short framex; // size=0, offset=12
	short framey; // size=0, offset=14
};

enum CDTYPE // Hashcode: 0x61FF3A77 (dec: 1644116599)
{
	CDTYPE_NODISC = 0,
	CDTYPE_SHELLOPEN = 1,
	CDTYPE_DISCERROR = 2,
	CDTYPE_WRONGDISC = 3,
	CDTYPE_CORRECTDISC = 4,
};

enum CITYTYPE // Hashcode: 0x89BC71DE (dec: -1984138786)
{
	CITYTYPE_DAY = 0,
	CITYTYPE_NIGHT = 1,
	CITYTYPE_MULTI_DAY = 2,
	CITYTYPE_MULTI_NIGHT = 3,
};

struct TARGET_ARROW_MODEL // hashcode: 0x49188CA9 (dec: 1226345641)
{
	struct SVECTOR* pVerts; // size=8, offset=0
	char* pTris; // size=0, offset=4
	char numTris; // size=0, offset=8
};

struct TP // hashcode: 0x3B17636E (dec: 991388526)
{
	unsigned long flags; // size=0, offset=0
	unsigned long offset; // size=0, offset=4
};

struct CAR_LOCALS // hashcode: 0xC11EBC40 (dec: -1054950336)
{
	long vel[4]; // size=16, offset=0
	long avel[4]; // size=16, offset=16
	int extraangulardamping; // size=0, offset=32
	int aggressive; // size=0, offset=36
};

struct XA_TRACK // hashcode: 0xB1C796C2 (dec: -1312319806)
{
	int start; // size=0, offset=0
	int end; // size=0, offset=4
};

struct FE_CHARDATA // hashcode: 0x3BD93806 (dec: 1004091398)
{
	unsigned char u; // size=0, offset=0
	unsigned char v; // size=0, offset=1
	unsigned char w; // size=0, offset=2
	unsigned char h; // size=0, offset=3
};

struct FE_FONT // hashcode: 0x602743A1 (dec: 1613185953)
{
	int NumFonts; // size=0, offset=0
	struct FE_CHARDATA CharInfo[256]; // size=1024, offset=4
};

struct SCREEN_LIMITS // hashcode: 0x445BA46E (dec: 1146856558)
{
	short minx; // size=0, offset=0
	short miny; // size=0, offset=2
	short maxx; // size=0, offset=4
	short maxy; // size=0, offset=6
};

struct BOTCH // hashcode: 0xE1A31543 (dec: -509405885)
{
	int missNum; // size=0, offset=0
	char** name; // size=0, offset=4
};

#endif // DR2TYPES_H