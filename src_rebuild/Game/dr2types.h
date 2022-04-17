#ifndef DR2TYPES_H
#define DR2TYPES_H

// Platform types
#include <types.h>

//---------------------------------------------------------------------------------------
// simple types

typedef short	SHORTVECTOR4[4];

typedef long	LONGVECTOR3[3];
typedef long	LONGVECTOR4[4];

typedef long	LONGQUATERNION[4];

struct VECTOR2
{
	int vx;
	int vz;
};

struct USVECTOR_NOPAD
{
	u_short vx;
	u_short vy;
	u_short vz;
};

struct VECTOR_NOPAD
{
	int vx;
	int vy;
	int vz;
};

struct SVECTOR_NOPAD
{
	short vx;
	short vy;
	short vz;
};

struct S_XYZ
{
	short x;
	short y;
	short z;
};

struct BVECTOR
{
	char vx;
	char vy;
	char vz;
	char pad;
};

struct UnpaddedHackVector
{
	int vx;
	int vz;
	short vy;
};

struct UnpaddedCharVector
{
	char vx;
	char vy;
	char vz;
};

struct XYPAIR
{
	int x;
	int y;
};

struct SXYPAIR
{
	short x, y;
};

struct XZPAIR
{
	int x, z;
};

struct XYWH
{
	short x, y, w, h;
};

// might be old frustum data
struct ARC_ENTRY
{
	short offset;
	short length;
};

#include "engine/cell.h"
#include "engine/mdl.h"
#include "engine/tim.h"
#include "engine/tset.h"

//---------------------------------------------------------------------------------------
// TODO: ROADS.H

struct DRIVER2_CURVE
{
	int Midx;
	int Midz;
	short start;
	short end;
	short ConnectIdx[4];
	short gradient;
	short height;
	char NumLanes;
	char LaneDirs;
	char inside;
	char AILanes;
};

struct DRIVER2_STRAIGHT
{
	int Midx;
	int Midz;
	u_short length;
	short bing;
	short angle;
	short ConnectIdx[4];
	char NumLanes;
	char LaneDirs;
	char AILanes;
	char packing;
};

struct OLD_DRIVER2_JUNCTION
{
	int Midx;
	int Midz;
	short length;
	short width;
	short angle;
	short ExitIdx[4];
	u_short flags;
};

struct DRIVER2_JUNCTION
{
	short ExitIdx[4];
	u_int flags;
};

enum SurfaceType
{
	SURF_CONCRETE	= 0,	// concrete/paved tiles
	SURF_GRASS		= 4,
	SURF_WATER		= 6,
	SURF_ALLEY		= 8,
	SURF_DEEPWATER	= 9,
	SURF_SAND		= 11,
};

typedef struct _sdPlane
{
	short surface;		// also one of SurfaceTypes
	short a, b, c;
	int d;
} sdPlane;

struct sdNodePACKED
{
	int angle : 11;
	int dist : 12;
	int offset : 8;
	int node : 1;
};

typedef union _sdNode
{
	int value;
	sdNodePACKED n;
} sdNode;

// really it's UNUSED in Driver 2 - so it's Driver 1 Only
struct ROUTE_DATA
{
	short type;
	short height;
	short objectAngle;
};

struct AREA_LOAD_INFO
{
	int xoffset;
	int zoffset;
};

struct ROAD_MAP_LUMP_DATA
{
	int width;
	int height;
	int unitXMid;
	int unitZMid;
};

//---------------------------------------------------------------------------------------
// TODO: DR2COSMETICS.H

struct CAR_COSMETICS
{
	SVECTOR headLight;
	SVECTOR frontInd;
	SVECTOR backInd;
	SVECTOR brakeLight;
	SVECTOR revLight;
	SVECTOR policeLight;
	SVECTOR exhaust;
	SVECTOR smoke;
	SVECTOR fire;
	SVECTOR wheelDisp[4];
	short extraInfo;
	short powerRatio;
	short cbYoffset;
	short susCoeff;
	short traction;
	short wheelSize;
	SVECTOR cPoints[12];
	SVECTOR colBox;
	SVECTOR cog;
	short twistRateX;
	short twistRateY;
	short twistRateZ;
	short mass;
};

//---------------------------------------------------------------------------------------
// TODO: DR2CARS.H

struct CAR_POLY
{
	int vindices;
	int nindices;
	int clut_uv0;
	int tpage_uv1;
	int uv3_uv2;
	short originalindex;
};

struct CAR_MODEL
{
	int numFT3;
	CAR_POLY* pFT3;
	int numGT3;
	CAR_POLY* pGT3;
	int numB3;
	CAR_POLY* pB3;
	SVECTOR* vlist;
	SVECTOR* nlist;
};

// UNUSED
struct TEX_INFO
{
	char name[8];
	char tset;
	char u;
	char v;
	char w;
	char h;
};

// UNUSED
struct TEXTURE_LOOKUP
{
	TEX_INFO(*Damage[6]);
};

struct DENTUVS
{
	char u3;
};

struct HUBCAP
{
	MATRIX Orientation;
	VECTOR Position;
	SVECTOR Direction;
	int Rotation;
	int Duration;
};

struct BOUND_BOX
{
	int x0;
	int y0;
	int z0;
	int x1;
	int y1;
	int z1;
};

typedef struct _HANDLING_TYPE
{
	char frictionScaleRatio;
	char aggressiveBraking;
	char fourWheelDrive;
	char autoBrakeOn;
} HANDLING_TYPE;

struct BOXINFO
{
	VECTOR vel;
	VECTOR pos;
	int sf;
	int xs;
	int zs;
	int w;
	int h;
	int zb;
	int ypos;
};

//----------------------------------------

struct WHEEL
{
	char susCompression;
	char locked;
	char onGrass;
	u_char surface;
};

struct OrientedBox
{
	VECTOR_NOPAD location;
	SVECTOR_NOPAD radii[3];
	short length[3];
};

typedef struct _HANDLING_DATA
{
	MATRIX where;
	MATRIX drawCarMat;
	LONGVECTOR4 acc;
	LONGVECTOR4 aacc;
	WHEEL wheel[4];
	int wheel_speed;
	int speed;
	int direction;
	int front_vel;
	int rear_vel;
	int mayBeColliding;		// [A] now used as a bitfield to create collision pairs
	short revs;
	char gear;
	char changingGear;
	char autoBrake;

	OrientedBox oBox;
} HANDLING_DATA;

union RigidBodyState
{
	long v[13];
	struct {
		LONGVECTOR3 fposition;
		LONGQUATERNION orientation;
		LONGVECTOR3 linearVelocity;
		LONGVECTOR3 angularVelocity;
	} n;
};

typedef struct _APPEARANCE_DATA
{
	SXYPAIR light_trails[4][4];
	CAR_COSMETICS* carCos;
	short old_clock[4];
	char life;
	char coplife;
	short qy;
	short qw;
	char life2;
	char model;
	char palette;

	char needsDenting : 1;
	char flags : 7;			// [A] new: appearance flags, 1,2,3,4 = wheel hubcaps lost

	short damage[6];
} APPEARANCE_DATA;

struct CIV_ROUTE_ENTRY
{
	short dir;
	u_short pathType;
	int distAlongSegment;
	int x;
	int z;
};

struct CIV_STATE
{
	int currentRoad;
	int currentNode;
	CIV_ROUTE_ENTRY* ctrlNode;
	u_char ctrlState;
	u_char trafficLightPhaseId;
	u_char changeLane;
	u_char turnDir;
	char brakeLight;
	u_char oldLane;
	u_char changeLaneCount;
	u_char pad3;
	int turnNode;
	int changeLaneIndicateCount;
	int carPauseCnt;
	int velRatio;
	CIV_ROUTE_ENTRY targetRoute[13];
	CIV_ROUTE_ENTRY* pnode;
	u_char maxSpeed;
	u_char thrustState;
	u_char carMustDie;
	u_char currentLane;
};

struct COP
{
	VECTOR2 targetHistory[2];
	char routeInMemory;
	char justPinged;
	char close_pursuit;
	char dying;
	u_short DistanceToPlayer;
	short desiredSpeed;
	short recalcTimer;
	short stuckTimer;
	short lastRecoverStrategy;
	short recoveryTimer;
	short hiddenTimer;
	short frontLClear;
	short frontRClear;
	short batterTimer;	// [A] new gameplay feature
};

struct LEAD_CAR
{
	char dstate;
	char ctt;
	short targetDir;
	int targetX;
	int targetZ;
	int currentRoad;
	int lastRoad;
	int nextJunction;
	int nextTurn;
	int nextExit;
	int stuckCount;
	int panicCount;
	int recoverTime;
	int roadPosition;
	int roadForward;
	int boringness;
	int avoid;
	int lastTarget;
	int offRoad;
	int width;
	int d;
	int base_Normal;
	int base_Angle;
	int base_Dir;
	int outsideSpoolRegion;
	int direction;
	int lastDirection;
	char takeDamage;
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
	CONTROL_FLAG_COP = (1 << 0),				// civ car is a cop car
	CONTROL_FLAG_COP_SLEEPING = (1 << 1),		// passive cop flag (roadblocks). Hitting car with that flag results it's activation
	CONTROL_FLAG_WAS_PARKED = (1 << 2),			// car pinged in as parked. Really nothing to do with it
	CONTROL_FLAG_PLAYER_START_CAR = (1 << 3),	// car owned by player
};

typedef struct _CAR_DATA
{
	HANDLING_DATA hd;
	RigidBodyState st;
	APPEARANCE_DATA ap;
	u_char hndType;
	u_char controlType;
	u_char controlFlags;
	char id;
	union {
		char* padid;
		CIV_STATE c;
		COP p;
		LEAD_CAR l;
	} ai;
	int* inform;
	short thrust;
	short felonyRating;
	char handbrake;
	char wheelspin;
	char wasOnGround;
	char lowDetail;
	short wheel_angle;
	u_short totalDamage;
	int lastPad;
} CAR_DATA;

typedef struct _COP_DATA
{
	int speed;
	int power;
	int min;
	int max;
} MS_COP_DATA;

struct LEAD_PARAMETERS
{
	int tEnd;
	int tAvelLimit;
	int tDist;
	int tDistMul;
	int tWidth;
	int tWidthMul;
	int tWidth80;
	int tWidth80Mul;
	int hEnd;
	int dEnd;
	int hDist;
	int hDistMul;
	int hWidth;
	int hWidthMul;
	int hWidth80;
	int hWidth80Mul;
};

//---------------------------------------------------------------------------------------
// TODO: MISSION.H

struct SAVED_PLAYER_POS
{
	u_short type;
	short direction;
	int vx;
	int vy;
	int vz;
	u_int felony;
	u_short totaldamage;
	short damage[6];
};

struct SAVED_CAR_POS
{
	char active;
	u_char model;
	u_char palette;
	u_short totaldamage;
	u_short damage[6];
	short direction;
	int vx;
	int vy;
	int vz;
};

struct MISSION_DATA
{
	SAVED_PLAYER_POS PlayerPos;
	SAVED_CAR_POS CarPos[6];
};

typedef struct _MISSION
{
	int id;
	int size;
	int city;
	int time;
	int weather;
	XYPAIR playerStartPosition;
	int playerStartRotation;
	int type;
	short timer;
	short timerFlags;
	int strings;
	MS_COP_DATA cops;
	int msgCarWrecked;
	int msgOutOfTime;
	int msgComplete;
	int region;
	int route;
	int msgDrowned;
	int playerCarModel;
	int playerCarColour;
	int maxDamage;
	int residentModels[5];
	int nCutscenes;
	int title;
	int msgPoliceCar;
	int msgDoorsLocked;
} MS_MISSION;

typedef struct _ROUTE_INFO
{
	int nJunctions;
	char data[1000][4];
	LEAD_PARAMETERS parameters;
} ROUTE_INFO;

enum TARGET_TYPE
{
	Target_Point = 1,
	Target_Car = 2,				// any mission target car. Also, a multiplayer player 2 car in Cops'n'Robbers
	Target_Event = 3,
	Target_Player2Start = 4,		// player 2 start
	Target_MultiCar = 5
};

struct MULTICAR_DATA
{
	int x;
	int z;
	u_char palette;
	u_char model;
	short rot;
};

enum TargetFlags
{
	// common target properties
	TARGET_FLAG_ACTIVE_P1					= 0x1,
	TARGET_FLAG_ACTIVE_P2					= 0x800,
	TARGET_FLAG_ACTIVE_ALLP					= (TARGET_FLAG_ACTIVE_P1 | TARGET_FLAG_ACTIVE_P2),

	TARGET_FLAG_COMPLETED_P1				= 0x2,
	TARGET_FLAG_COMPLETED_P2				= 0x100,
	TARGET_FLAG_COMPLETED_ALLP				= (TARGET_FLAG_COMPLETED_P1 | TARGET_FLAG_COMPLETED_P2),

	TARGET_FLAG_VISIBLE_P1					= 0x200,
	TARGET_FLAG_VISIBLE_P2					= 0x400,
	TARGET_FLAG_VISIBLE_ALLP				= (TARGET_FLAG_VISIBLE_P1 | TARGET_FLAG_VISIBLE_P2),

	// point target properties
	TARGET_FLAG_POINT_CTF_BASE_P1			= 0x10000,
	TARGET_FLAG_POINT_CTF_BASE_P2			= 0x20000,
	TARGET_FLAG_POINT_CTF_FLAG				= 0x30000,

	TARGET_FLAG_POINT_SECRET_POINT1			= 0x1000000,
	TARGET_FLAG_POINT_SECRET_POINT2			= 0x2000000,
	TARGET_FLAG_POINT_SECRET_STARTFINISH	= 0x3000000,

	TARGET_FLAG_POINT_ON_BOAT				= 0x100000,
	TARGET_FLAG_POINT_STOP_COPS_TRIGGER		= 0x200000,
	//0x400000,
	TARGET_FLAG_POINT_PLAYER_MUSTHAVE_CAR	= 0x800000,

	// car target properties
	TARGET_FLAG_CAR_SAVED					= 0x10,
	TARGET_FLAG_CAR_PLAYERCONTROLLED		= 0x20,
	TARGET_FLAG_CAR_SWAPPED					= 0x40,
	TARGET_FLAG_CAR_PINGED_IN				= 0x40000000,

	// event target properties
	TARGET_FLAG_EVENT_TRIGGERED = 0x1000,
};

enum CarTargetFlags
{
	CARTARGET_FLAG_RANDOMCHASE			= 0x1,
	CARTARGET_FLAG_THROWS_BOMBS			= 0x4,
	CARTARGET_FLAG_ISCOP				= 0x8,			// makes CATARGET_FLAG_ISCOP

	// FIXME: those target names can be specified poorly
	CATTARGET_FLAG_PROXIMITY_TARGET		= 0x10,
	CARTARGET_FLAG_STEAL_TARGET			= 0x30,
	CARTARGET_FLAG_ESCAPE_TARGET		= 0x40,
	CARTARGET_FLAG_CnR_TARGET			= 0x50,

	CARTARGET_FLAG_TO_BE_STOLEN			= 0x10000,
	CARTARGET_FLAG_FLIPPED				= 0x40000,
	CARTARGET_FLAG_DAMAGED				= 0x80000,
	CARTARGET_FLAG_PED_ESCAPES			= 0x100000,
	CARTARGET_FLAG_DETONATOR			= 0x200000,		// has a detonator timer

	CARTARGET_FLAG_BACK_TO_PLAYERCAR	= 0x400000,		// to retrieve the car to return back to
	CARTARGET_FLAG_SET_PLAYERCAR		= 0x800000,		// sets the car to return back to
};

typedef struct _TARGET
{
	int type;			// data 0

	union
	{
		MULTICAR_DATA multiCar[5];

		struct
		{
			int target_flags;	// data 1
			int display_flags;	// data 2

			union
			{
				struct
				{
					int posX;				// data 3
					int posZ;				// data 4
					int radius;				// data 5
					int posY;				// data 6
					int height;				// data 7
					int loseTailMessage;	// data 8
					int actionFlag;			// data 9
					int boatOffsetX;		// data 10
					int boatOffsetZ;		// data 11
				} point;

				struct
				{
					int posX;			// data 3
					int posZ;			// data 4
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
						struct
						{
							int closeMessages;		// data 13
							int farMessages;		// data 14
						} tail;
						struct
						{
							int maxDamage;			// data 13
							int tooFarMessage;		// data 14
							int gettingFarMessage;	// data 15
						} chasing;
					};
				} car;
				
				struct
				{
					int eventId;			// data 3
					union
					{
						VECTOR* eventPos;	// data 4
						int unused[10];
					};
					int loseMessage;		// data 14
				} event;
			};
		} s;
	};
} MS_TARGET;

assert_sizeof(MS_TARGET, 64);

//---------------------------------------------------------------------------------------

enum FAIL_REASON
{
	FAILED_OUTOFTIME = 0,
	FAILED_CnR_LOSTHIM = 1,
	FAILED_MESSAGESET = 2,
};

typedef enum PAUSEMODE
{
	PAUSEMODE_PAUSE = 0,
	PAUSEMODE_PAUSEP1 = 1,
	PAUSEMODE_PAUSEP2 = 2,
	PAUSEMODE_GAMEOVER = 3,
	PAUSEMODE_COMPLETE = 4,
	PAUSEMODE_PADERROR = 5,
} PAUSEMODE;

enum TimerFlags
{
	TIMER_FLAG_ACTIVE				= 0x1,
	TIMER_FLAG_COUNTER				= 0x2,
	TIMER_FLAG_PAUSED				= 0x4,
	
	TIMER_FLAG_COMPLETE_ON_OUT		= 0x8,
	TIMER_FLAG_BOMB_COUNTDOWN		= 0x10,
	TIMER_FLAG_BOMB_TRIGGERED		= 0x20,
};

enum MissionTimerFlags
{
	MISSIONTIMER_FLAG_BOMB_TIMER		= 0x1000,
	MISSIONTIMER_FLAG_BOMB_COUNTDOWN	= 0x2000,
	MISSIONTIMER_FLAG_COMPLETE_ON_OUT	= 0x4000,
	MISSIONTIMER_FLAG_COUNTER			= 0x8000,
};

struct MR_TIMER
{
	short x, y;
	u_char flags;
	u_char min, sec, frac;
	int count;
};

struct MR_MISSION
{
	int active;
	int gameover_delay;
	PAUSEMODE gameover_mode;
	short message_timer[2];
	short message_priority[2];
	char(*message_string[2]);
	MR_TIMER timer[2];
	MS_TARGET* CarTarget;
	MS_TARGET* ChaseTarget;
	int PhantomCarId;
	int ChaseHitDelay;
	char* StealMessage;
};

struct MR_THREAD
{
	u_char active;
	u_char player;
	u_int* initial_sp;
	u_int* pc;
	u_int* sp;
};

//---------------------------------------------------------------------------------------
// TODO: SCORES.H

struct SCORE_ENTRY
{
	int time;
	short items;
	char name[6];
};

struct SCORE_TABLES
{
	SCORE_ENTRY GetawayTable[4][2][5];
	SCORE_ENTRY GateRaceTable[4][2][5];
	SCORE_ENTRY CheckpointTable[4][2][5];
	SCORE_ENTRY TrailblazerTable[4][2][5];
	SCORE_ENTRY SurvivalTable[4][1][5];
};

struct PLAYER_SCORE
{
	int time;
	int P2time;
	short items;
	short P2items;
	char name[6];
};

//---------------------------------------------------------------------------------------
// TODO: FELONY.H

struct FELONY_DELAY
{
	short current;
	short maximum;
};

struct FELONY_VALUE
{
	short placid;
	short angry;
};

struct FELONY_DATA
{
	FELONY_DELAY occurrenceDelay[12];
	FELONY_DELAY reoccurrenceDelay[12];
	FELONY_VALUE value[12];
	int pursuitFelonyScale;
};

//---------------------------------------------------------------------------------------
// TODO: PEDEST.H

enum PED_ACTION_TYPE //: char
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

enum PED_MODEL_TYPES //: char
{
	TANNER_MODEL = 0,
	OTHER_MODEL = 1,
	OTHER_SPRITE = 2,
	CIVILIAN = 3,
};

typedef struct PEDESTRIAN *LPPEDESTRIAN;

typedef void(*pedFunc)(LPPEDESTRIAN pPed);

typedef struct PEDESTRIAN
{
	LPPEDESTRIAN pNext;
	LPPEDESTRIAN pPrev;
	pedFunc fpRestState;
	pedFunc fpAgitatedState;
	char padId;
	char pedType;
	VECTOR_NOPAD position;
	SVECTOR dir;
	SVECTOR velocity;
	VECTOR target;
	int flags;
	short head_pos;
	short head_rot;
	short index;
	short last_dir;
	short interest;
	char frame1;
	char* motion;
	char speed;
	char doing_turn;
	char finished_turn;
	char seat_index;
	u_char pallet;
	char type;
} *LPPEDESTRIAN;

typedef struct PEDESTRIAN_ROADS
{
	short pos;
	short north;
	short south;
	short east;
	short west;
} *LPPEDESTRIAN_ROADS;

//---------------------------------------------------------------------------------------
// TODO: GAMESND.H

typedef struct __skidinfo
{
	char chan;
	char sound;
} skidinfo;

typedef struct __horninfo
{
	char on;
	char time;
	char request;
} horninfo;

//---------------------------------------------------------------------------------------
// TODO: CHEATS.H

struct ACTIVE_CHEATS
{
	u_char cheat1 : 1;
	u_char cheat2 : 1;
	u_char cheat3 : 1;
	u_char cheat4 : 1;
	u_char cheat5 : 1;
	u_char cheat6 : 1;
	u_char cheat7 : 1;
	u_char cheat8 : 1;
	u_char cheat9 : 1;
	u_char cheat10 : 1;
	u_char cheat11 : 1;
	u_char cheat12 : 1;
	u_char cheat13 : 1;
	u_char cheat14 : 1;
	u_char cheat15 : 1;
	u_char cheat16 : 1;
	u_char reserved1;
	u_char reserved2;
};

// UNUSED - Driver 1 cheats
struct CHEATS
{
	int RearWheelSteer;
	int MiniCars;
	int Stilts;
	int LowGravity;
	int Australia;
	int MagicMirror;
};

//---------------------------------------------------------------------------------------
// TODO: REPLAYS.H

#define DRIVER2_REPLAY_MAGIC		0x14793209
#define REDRIVER2_CHASE_MAGIC		(('D' << 24) | ('2' << 16) | ('C' << 8) | 'R' )

struct REPLAY_PARAMETER_BLOCK
{
	int RecordingEnd;
	VECTOR_NOPAD lead_car_start;
	short Lead_car_dir;
	u_char timeofday;
	u_char weather;
};

struct REPLAY_SAVE_HEADER
{
	u_int magic;
	u_char GameLevel;
	u_char GameType;
	u_char reserved1;
	u_char NumReplayStreams;
	u_char NumPlayers;
	u_char RandomChase;
	u_char CutsceneEvent;
	u_char gCopDifficultyLevel;
	MISSION_DATA SavedData;
	ACTIVE_CHEATS ActiveCheats;
	int wantedCar[2];
	int MissionNumber;
	int HaveStoredData;
	int reserved2[6];
};

struct STREAM_SOURCE
{
	u_char type;
	u_char model;
	u_char palette;
	char controlType;
	u_short flags;
	u_short rotation;
	VECTOR_NOPAD position;
	int totaldamage;
	int damage[6];
};

struct REPLAY_STREAM_HEADER
{
	STREAM_SOURCE SourceType;
	int Size;
	int Length;
};

struct PADRECORD
{
	u_char pad;
	u_char analogue;
	u_char run;
};

struct REPLAY_STREAM
{
	STREAM_SOURCE SourceType;
	PADRECORD* InitialPadRecordBuffer;
	PADRECORD* PadRecordBuffer;
	PADRECORD* PadRecordBufferEnd;
	u_char playbackrun;
	int length;
	int padCount;
};

typedef struct _PING_PACKET
{
	u_short frame;
	char carId;
	char cookieCount;
} PING_PACKET;

struct PLAYBACKCAMERA
{
	VECTOR_NOPAD position;
	SVECTOR angle;
	int FrameCnt;
	short CameraPosvy;
	short scr_z;
	short gCameraMaxDistance;
	short gCameraAngle;
	u_char cameraview;
	u_char next;
	u_char prev;
	u_char idx;
};

//---------------------------------------------------------------------------------------
// TODO: COP_AI.H

struct STOPCOPS
{
	VECTOR_NOPAD pos;
	int radius;
};

struct GAP_INFO
{
	DVECTOR offset;
	char clear;
};

struct ADJACENT_ROAD_INFO
{
	DVECTOR offset;
	GAP_INFO gap;
};

// only "status" is used
struct ROADBLOCK
{
	VECTOR position;
	ADJACENT_ROAD_INFO adjacentRoadInfo;
	short RoadToBlock;
	short AdjacentRoad;
	short RoadblockTimer;
	int copRespawnTime;
	char NumCarsNeededForRoad;
	char NumCarsNeededForAdjacentRoad;
	char NumCarsSavedForBlock;
	char DirectionToRoadblock;
	char status;
	char AI_Slot[13];
};

//---------------------------------------------------------------------------------------
// TODO: OBJCOLL.H

struct TestResult
{
	int depth;
	VECTOR location;
	VECTOR normal;
};

struct BUILDING_BOX
{
	VECTOR pos;
	int xsize;
	int zsize;
	int theta;
	int height;
	int model;
};

struct CDATA2D
{
	VECTOR x;
	VECTOR axis[2];
	VECTOR vel;
	int theta;
	int length[2];
	int dist[2];
	int limit[2];
	int avel;
	int isCameraOrTanner;
};

struct CRET2D
{
	VECTOR hit;
	VECTOR surfNormal;
	int penetration;
	int neverfree;
};

//---------------------------------------------------------------------------------------
// TODO: TUNNELS.H

typedef struct __tunnelcoords
{
	VECTOR p1;
	VECTOR p2;
} tunnelcoords;

typedef struct __tunnelinfo
{
	char num_tunnels;
	char tunnel_cnt;
	tunnelcoords coords[29];
} tunnelinfo;

//---------------------------------------------------------------------------------------
// TODO: BOMBERMAN.H or JOB_FX.H

enum ExplosionType
{
	BIG_BANG = 0,
	LITTLE_BANG = 1,
	HEY_MOMMA = 666,
	BANG_USED = 999,
};

typedef struct _ExOBJECT
{
	int time;
	int speed;
	int hscale;
	int rscale;
	ExplosionType type;
	VECTOR pos;
} EXOBJECT;

struct BOMB
{
	u_char flags;
	u_char active;
	short rot_speed;
	VECTOR position;
	VECTOR velocity;
};

//---------------------------------------------------------------------------------------
// TODO: PLAYER.H

typedef struct _PLAYER
{
	LONGVECTOR4 pos;
	int dir;
	VECTOR* spoolXZ;
	VECTOR cameraPos;
	int cameraDist;
	int maxCameraDist;
	int cameraAngle;
	int headPos;
	int headTarget;
	int viewChange;
	u_char dying;
	u_char upsideDown;
	char onGrass;
	char targetCarId;
	char cameraView;
	u_char headTimer;
	char playerType;
	char worldCentreCarId;
	char playerCarId;
	char cameraCarId;
	char padid;
	char car_is_sounding;
	LONGVECTOR3 camera_vel;
	int snd_cam_ang;
	skidinfo skidding;
	skidinfo wheelnoise;
	horninfo horn;
	int car_sound_timer;
	short revsvol;
	short idlevol;
	LPPEDESTRIAN pPed;
	int crash_timer;
} PLAYER;

//---------------------------------------------------------------------------------------
// TODO: AI.H

struct COP_DATA
{
	int autoMaxPowerScaleLimit;
	int autoDesiredSpeedScaleLimit;
	int autoRespawnScaleLimit;
	int autoBatterPlayerTrigger;
	int immortal;
	int roadblockTrigger;
	int cutOffPowerScale;
	int cutOffDistance;
	short trigger[5];
};

//---------------------------------------------------------------------------------------
// TODO: GLAUNCH.H

enum GAMETYPE
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

enum GAMEMODE
{
	GAMEMODE_NORMAL = 0,
	GAMEMODE_QUIT = 1,
	GAMEMODE_RESTART = 2,
	GAMEMODE_REPLAY = 3,
	GAMEMODE_DIRECTOR = 4,
	GAMEMODE_NEXTMISSION = 5,
	GAMEMODE_DEMO = 6,
};

#endif // DR2TYPES_H