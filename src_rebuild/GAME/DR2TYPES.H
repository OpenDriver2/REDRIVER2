#ifndef DR2TYPES_H
#define DR2TYPES_H

// Driver 2 system types

typedef short SHORTVECTOR[4];

typedef long LONGVECTOR[4];
typedef long LONGQUATERNION[4];

struct VECTOR2
{
	int vx;
	int vz;
};

struct USVECTOR_NOPAD
{
	unsigned short vx;
	unsigned short vy;
	unsigned short vz;
};

struct VECTOR_NOPAD
{
	long vx;
	long vy;
	long vz;
};

struct SVECTOR_NOPAD
{
	short vx;
	short vy;
	short vz;
};

// TODO: DR2TYPES

struct BOX
{
	float xmin;
	float ymin;
	float zmin;
	float xmax;
	float ymax;
	float zmax;
};

struct BSPHERE
{
	VECTOR bounding_sphere_mid;
	float bounding_sphere;
};

struct RGB
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char pad;
};

struct UV_INFO
{
	unsigned char u;
	unsigned char v;
};

struct XYPAIR
{
	int x;
	int y;
};

struct SXYPAIR
{
	short x;
	short y;
};

struct GAP_INFO
{
	DVECTOR offset;
	char clear;
};



struct PADRECORD
{
	unsigned char pad;
	unsigned char analogue;
	unsigned char run;
};

struct ARC_ENTRY
{
	short offset;
	short length;
};

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
	unsigned short length;
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
	unsigned short flags;
};

struct DRIVER2_JUNCTION
{
	short ExitIdx[4];
	unsigned long flags;
};

typedef struct _sdPlane
{
	short surface;
	short a;
	short b;
	short c;
	int d;
} sdPlane;

struct sdNodePACKED
{
	int angle : 11;
	int dist : 12;
	int offset : 8;
	int node : 1;
};

union _sdNode
{
	int value;
	sdNodePACKED n;
};

struct WHEEL
{
	char susCompression;
	char locked;
	char onGrass;
	unsigned char surface;
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
	long acc[4];
	long aacc[4];
	int wheel_speed;
	int speed;
	int direction;
	char gear;
	char changingGear;
	char mayBeColliding;
	char autoBrake;
	WHEEL wheel[4];
	short revs;
	VECTOR shadowPoints[4];
	int front_vel;
	int rear_vel;
	OrientedBox oBox;
} HANDLING_DATA;

union RigidBodyState
{
	long v[13];
	struct {
		long fposition[3];
		LONGQUATERNION orientation;
		long linearVelocity[3];
		long angularVelocity[3];
	} n;
};

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
	unsigned short pathType;
	int distAlongSegment;
	int x;
	int z;
};

struct CIV_STATE
{
	int currentRoad;
	int currentNode;
	CIV_ROUTE_ENTRY* ctrlNode;
	unsigned char ctrlState;
	unsigned char trafficLightPhaseId;
	unsigned char changeLane;
	unsigned char turnDir;
	char brakeLight;
	unsigned char oldLane;
	unsigned char changeLaneCount;
	unsigned char pad3;
	int turnNode;
	int changeLaneIndicateCount;
	int carPauseCnt;
	int velRatio;
	CIV_ROUTE_ENTRY targetRoute[13];
	CIV_ROUTE_ENTRY* pnode;
	unsigned char maxSpeed;
	unsigned char thrustState;
	unsigned char carMustDie;
	unsigned char currentLane;
};

struct COP
{
	VECTOR2 targetHistory[2];
	char routeInMemory;
	char justPinged;
	char close_pursuit;
	char dying;
	unsigned short DistanceToPlayer;
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
	CONTROL_FLAG_COP = (1 << 0),		// civ car is a cop car
	CONTROL_FLAG_COP_SLEEPING = (1 << 1),		// passive cop flag (roadblocks). Hitting car with that flag results it's activation
	CONTROL_FLAG_WAS_PARKED = (1 << 2)		// car pinged in as parked. Really nothing to do with it
};

typedef struct _CAR_DATA
{
	HANDLING_DATA hd;
	RigidBodyState st;
	APPEARANCE_DATA ap;
	unsigned char hndType;
	unsigned char controlType;
	unsigned char controlFlags;
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
	unsigned short totalDamage;
	long lastPad;
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

typedef struct _EVENT EVENT;

struct _EVENT
{
	VECTOR position;
	short rotation;
	short timer;
	int* data;
	int* node;
	short flags;
	short radius;
	int model;
	EVENT* next;
};

struct FixedEvent
{
	VECTOR position;
	short rotation;
	short active;
	unsigned short initialRotation;
	unsigned short finalRotation;
	unsigned short minSpeed;
	unsigned short maxSpeed;
	short flags;
	short radius;
	int model;
	EVENT* next;
	char* modelName;
};

typedef struct MAPPING
{
	unsigned short button_lookup[16];
	unsigned short swap_analog;
	unsigned short reserved1;
} *LPMAPPING;

struct SAVED_PLAYER_POS
{
	unsigned short type;
	short direction;
	long vx;
	long vy;
	long vz;
	unsigned long felony;
	unsigned short totaldamage;
	short damage[6];
};

struct SAVED_CAR_POS
{
	char active;
	unsigned char model;
	unsigned char palette;
	unsigned short totaldamage;
	unsigned short damage[6];
	short direction;
	long vx;
	long vy;
	long vz;
};

struct MISSION_DATA
{
	SAVED_PLAYER_POS PlayerPos;
	SAVED_CAR_POS CarPos[6];
};

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

struct ACTIVE_CHEATS
{
	unsigned char cheat1 : 1;
	unsigned char cheat2 : 1;
	unsigned char cheat3 : 1;
	unsigned char cheat4 : 1;
	unsigned char cheat5 : 1;
	unsigned char cheat6 : 1;
	unsigned char cheat7 : 1;
	unsigned char cheat8 : 1;
	unsigned char cheat9 : 1;
	unsigned char cheat10 : 1;
	unsigned char cheat11 : 1;
	unsigned char cheat12 : 1;
	unsigned char cheat13 : 1;
	unsigned char cheat14 : 1;
	unsigned char cheat15 : 1;
	unsigned char cheat16 : 1;
	unsigned char reserved1;
	unsigned char reserved2;
};

struct STREAM_SOURCE
{
	unsigned char type;
	unsigned char model;
	unsigned char palette;
	char controlType;
	unsigned short flags;
	unsigned short rotation;
	VECTOR_NOPAD position;
	int totaldamage;
	int damage[6];
};

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

typedef char schar;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#ifndef __GNUC__
typedef unsigned short uid_t;

typedef unsigned short gid_t;
#endif

typedef void (*SsMarkCallbackProc)();

struct MODEL
{
	unsigned short shape_flags;
	unsigned short flags2;
	short instance_number;
	unsigned char tri_verts;
	unsigned char zBias;
	short bounding_sphere;
	unsigned short num_point_normals;
	unsigned short num_vertices;
	unsigned short num_polys;
	int vertices;
	int poly_block;
	int normals;
	int point_normals;
	int collision_block;
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

struct UV
{
	unsigned char u0;
	unsigned char v0;
	unsigned char u1;
	unsigned char v1;
	unsigned char u2;
	unsigned char v2;
	unsigned char u3;
	unsigned char v3;
};

struct TEXTURE_DETAILS
{
	UV coords;
	unsigned short tpageid;
	unsigned short clutid;
	char texture_number;
	char texture_page;
};

struct CELL_OBJECT
{
	VECTOR_NOPAD pos;
	unsigned char pad;
	unsigned char yang;
	unsigned short type;
};

struct ANIMATED_OBJECT
{
	int internal_id;
	int model_num;
	char* name;
	char LitPoly;
};

struct SMASHABLE_OBJECT
{
	int modelIdx;
	char* name;
	int sound;
	int volume;
	int pitch;
};

struct GARAGE_DOOR
{
	CELL_OBJECT* cop;
	VECTOR_NOPAD old_pos;
	VECTOR_NOPAD pos;
	short rotation;
	char yang;
};

struct RGB16
{
	short r;
	short g;
	short b;
	short pad;
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

struct BVECTOR
{
	char vx;
	char vy;
	char vz;
	char pad;
};

struct ADJACENT_ROAD_INFO
{
	DVECTOR offset;
	GAP_INFO gap;
};

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

typedef struct _TARGET
{
	union
	{
		int data[16];
		MS_TARGET_BASE base;
		MS_TARGET_POINT point;
		MS_TARGET_CAR car;
		MS_TARGET_EVENT event;
	};
} MS_TARGET;

struct MR_TIMER
{
	short x;
	short y;
	unsigned char flags;
	unsigned char min;
	unsigned char sec;
	unsigned char frac;
	long count;
};

enum PED_ACTION_TYPE : char
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

enum PED_MODEL_TYPES : char
{
	TANNER_MODEL = 0,
	OTHER_MODEL = 1,
	OTHER_SPRITE = 2,
	CIVILIAN = 3,
};

typedef void(*pedFunc)(struct PEDESTRIAN* pPed);

typedef struct PEDESTRIAN
{
	PEDESTRIAN* pNext;
	PEDESTRIAN* pPrev;
	pedFunc fpRestState;
	pedFunc fpAgitatedState;
	char padId;
	PED_MODEL_TYPES pedType;
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
	unsigned char pallet;
	PED_ACTION_TYPE type;
} *LPPEDESTRIAN;

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

struct CYCLE_OBJECT
{
	char* name;
	short vx;
	short vy;
	short start1;
	short stop1;
	short speed1;
	short start2;
	short stop2;
	short speed2;
};

struct COLOUR_BAND
{
	CVECTOR colour;
	int value;
	int flags;
};

typedef struct _PERCENTAGE_BAR
{
	char* tag;
	short xpos;
	short ypos;
	short width;
	short height;
	unsigned short position;
	unsigned short max;
	COLOUR_BAND* pColourBand;
	int flags;
	int active;
} PERCENTAGE_BAR, *LPPERCENTAGE_BAR;

struct COP_SIGHT_DATA
{
	short surroundViewDistance;
	short frontViewDistance;
	short frontViewAngle;
};

struct MAPTEX
{
	short u;
	short w;
	short v;
	short h;
};

struct OVERMAP
{
	int x_offset;
	int y_offset;
	int width;
	int height;
	unsigned char toptile;
	unsigned char dummy;
	int scale;
};

struct REPLAY_PARAMETER_BLOCK
{
	int RecordingEnd;
	VECTOR_NOPAD lead_car_start;
	short Lead_car_dir;
	unsigned char timeofday;
	unsigned char weather;
};

struct REPLAY_SAVE_HEADER
{
	unsigned long magic;
	unsigned char GameLevel;
	unsigned char GameType;
	unsigned char reserved1;
	unsigned char NumReplayStreams;
	unsigned char NumPlayers;
	unsigned char RandomChase;
	unsigned char CutsceneEvent;
	unsigned char gCopDifficultyLevel;
	MISSION_DATA SavedData;
	ACTIVE_CHEATS ActiveCheats;
	int wantedCar[2];
	int MissionNumber;
	int HaveStoredData;
	int reserved2[6];
};

struct REPLAY_STREAM_HEADER
{
	STREAM_SOURCE SourceType;
	int Size;
	int Length;
};

struct REPLAY_STREAM
{
	STREAM_SOURCE SourceType;
	PADRECORD* InitialPadRecordBuffer;
	PADRECORD* PadRecordBuffer;
	PADRECORD* PadRecordBufferEnd;
	unsigned char playbackrun;
	int length;
	int padCount;
};

typedef struct _PING_PACKET
{
	unsigned short frame;
	char carId;
	char cookieCount;
} PING_PACKET;

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
	unsigned char flags;
	unsigned char active;
	short rot_speed;
	VECTOR position;
	VECTOR velocity;
};

struct COLLISION_PACKET
{
	short type;
	short xpos;
	short ypos;
	short zpos;
	short flags;
	short yang;
	short empty;
	short xsize;
	short ysize;
	short zsize;
};

typedef struct _PLAYER
{
	long pos[4];
	int dir;
	VECTOR* spoolXZ;
	VECTOR cameraPos;
	int cameraDist;
	int maxCameraDist;
	int cameraAngle;
	int headPos;
	int headTarget;
	int viewChange;
	unsigned char dying;
	unsigned char upsideDown;
	char onGrass;
	char targetCarId;
	char cameraView;
	unsigned char headTimer;
	char playerType;
	char worldCentreCarId;
	char playerCarId;
	char cameraCarId;
	char padid;
	char car_is_sounding;
	long camera_vel[3];
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

struct XZPAIR
{
	int x;
	int z;
};

struct CELL_DATA
{
	unsigned short num;
};

struct PACKED_CELL_OBJECT
{
	USVECTOR_NOPAD pos;
	unsigned short value;
};

typedef struct PAD
{
	unsigned char active;
	unsigned char type;
	unsigned char dualshock;
	unsigned char reserved1;
	unsigned short direct;
	unsigned short dirnew;
	char diranalog[4];
	unsigned short mapped;
	unsigned short mapnew;
	char mapanalog[4];
	MAPPING mappings;
	unsigned char alarmShakeCounter;
	unsigned char asd;
	unsigned char sdf;
	unsigned char dfg;
	unsigned char delay;
	unsigned char port;
	unsigned char state;
	unsigned char dsactive;
	unsigned char* shakeptr;
	unsigned char motors[2];
	unsigned char shake_type;
	unsigned char vibrate;
} *LPPAD;

struct CELL_ITERATOR
{
	CELL_DATA* pcd;
	PACKED_CELL_OBJECT* ppco;
	XZPAIR nearCell;
	int use_computed;
};

struct TEX_INFO
{
	char name[8];
	char tset;
	char u;
	char v;
	char w;
	char h;
};

struct TEXTURE_LOOKUP
{
	TEX_INFO(*Damage[6]);
};

struct plotCarGlobals
{
	unsigned char* primptr;
	OTTYPE* ot;
	unsigned long intensity;
	unsigned short* pciv_clut;
	unsigned long ShineyTPageASL16;
	unsigned long ShineyClutASL16;
	unsigned char* damageLevel;
	unsigned char* shineyTable;
	int ghost;
};

typedef struct _EXTRA_CIV_DATA
{
	int surfInd;
	int distAlongSegment;
	short angle;
	unsigned short ctrlState;
	int thrustState;
	unsigned char palette;
	unsigned char controlFlags;
} EXTRA_CIV_DATA;

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

struct FELONY_DATA
{
	FELONY_DELAY occurrenceDelay[12];
	FELONY_DELAY reoccurrenceDelay[12];
	FELONY_VALUE value[12];
	int pursuitFelonyScale;
};

enum AIZone
{
	zoneFrnt = 0,
	zoneBack = 1,
	zoneLeft = 2,
	zoneRght = 3,
};

struct iVectNT
{
	int n;
	int t;
};

struct PLAYBACKCAMERA
{
	VECTOR_NOPAD position;
	SVECTOR angle;
	int FrameCnt;
	short CameraPosvy;
	short scr_z;
	short gCameraMaxDistance;
	short gCameraAngle;
	unsigned char cameraview;
	unsigned char next;
	unsigned char prev;
	unsigned char idx;
};

struct CUTSCENE_BUFFER
{
	int numResident;
	unsigned char residentCutscenes[4];
	char(*residentPointers[4]);
	char* currentPointer;
	int bytesFree;
	char buffer[8192];
};

struct CUTSCENE_INFO
{
	unsigned short offset;
	unsigned short size;
};

struct CUTSCENE_HEADER
{
	int maxsize;
	CUTSCENE_INFO data[15];
};

struct TPAN
{
	unsigned char texture_page;
	unsigned char texture_number;
};

struct POLYFT4
{
	unsigned char id;
	unsigned char texture_set;
	unsigned char texture_id;
	unsigned char spare;
	unsigned char v0;
	unsigned char v1;
	unsigned char v2;
	unsigned char v3;
	UV_INFO uv0;
	UV_INFO uv1;
	UV_INFO uv2;
	UV_INFO uv3;
	RGB color;
};

struct POLYGT4
{
	unsigned char id;
	unsigned char texture_set;
	unsigned char texture_id;
	unsigned char spare;
	unsigned char v0;
	unsigned char v1;
	unsigned char v2;
	unsigned char v3;
	unsigned char n0;
	unsigned char n1;
	unsigned char n2;
	unsigned char n3;
	UV_INFO uv0;
	UV_INFO uv1;
	UV_INFO uv2;
	UV_INFO uv3;
	RGB color;
};

struct SMOKE
{
	UnpaddedHackVector position;
	UnpaddedCharVector drift;
	UnpaddedCharVector drift_change;
	UnpaddedHackVector final_tail_pos;
	unsigned char step;
	unsigned char pos;
	short start_w;
	short final_w;
	char life;
	char halflife;
	unsigned short flags;
	unsigned char num;
	unsigned char t_step;
	short transparency;
};

struct DEBRIS
{
	VECTOR position;
	SVECTOR direction;
	unsigned short life;
	unsigned short flags;
	unsigned short num;
	unsigned short pos;
	RGB rgb;
	char step;
	char type;
};

struct LEAF
{
	VECTOR position;
	SVECTOR direction;
	unsigned short life;
	unsigned short flags;
	unsigned short num;
	unsigned short pos;
	RGB rgb;
	char step;
	char type;
	short sin_index1;
	short sin_index2;
	char sin_addition1;
	char sin_addition2;
};

struct DAMAGED_LAMP
{
	int index;
	char damage;
};

struct DAMAGED_OBJECT
{
	CELL_OBJECT cop;
	char active;
	char damage;
	int rot_speed;
	SVECTOR velocity;
	int vx;
};

struct TRI_POINT
{
	BVECTOR v0;
	BVECTOR v1;
	BVECTOR v2;
};

struct TRI_POINT_LONG
{
	VECTOR_NOPAD v0;
	VECTOR_NOPAD v1;
	VECTOR_NOPAD v2;
};

struct RAIN_TYPE
{
	VECTOR_NOPAD position;
	SVECTOR oldposition;
};

struct LAMP_STREAK
{
	SXYPAIR light_trails[4];
	int id;
	short clock;
	char set;
};

struct ROUTE_DATA
{
	short type;
	short height;
	short objectAngle;
};

struct DENTUVS
{
	char u3;
};

struct HUBCAP
{
	int Present[4];
	VECTOR Offset[4];
	MATRIX Orientation;
	MATRIX LocalOrientation;
	VECTOR Position;
	VECTOR Direction;
	float Height;
	int Duration;
};

struct REPLAY_ICON
{
	short x;
	short y;
	TEXTURE_DETAILS* texture;
	char* TextPtr;
	short tx;
	short ty;
};

struct _pct
{
	struct DB* current;
	unsigned short(*ptexture_pages)[128];
	unsigned short(*ptexture_cluts)[128][32];
	long f4colourTable[32];
	int* polySizes;
	char* primptr;
	OTTYPE* ot;
	unsigned long clut;
	unsigned long tpage;
	unsigned long colour;
	int flags;
	SVECTOR* verts;
	unsigned long lastTexInfo;
	int scribble[8];
	int model;
};

struct MATRIX2
{
	short m[3][3];
	short computed;
	char null[12];
};

struct Spool
{
	unsigned short offset;
	unsigned char connected_areas[2];
	unsigned char pvs_size;
	unsigned char cell_data_size[3];
	unsigned char super_region;
	unsigned char num_connected_areas;
	unsigned char roadm_size;
	unsigned char roadh_size;
};

union VERT_INDEX
{
	struct {
		unsigned char v0;
		unsigned char v1;
		unsigned char v2;
		unsigned char v3;
	};
	uint value;
};

struct PL_POLYFT4
{
	unsigned char id;
	unsigned char texture_set;
	unsigned char texture_id;
	unsigned char th;
	unsigned char v0;
	unsigned char v1;
	unsigned char v2;
	unsigned char v3;
	UV_INFO uv0;
	UV_INFO uv1;
	UV_INFO uv2;
	UV_INFO uv3;
};

struct MVERTEX
{
	short vx;
	short vy;
	short vz;
	union {
		short val;
		struct {
			unsigned char u0;
			unsigned char v0;
		};
	}uv;
};

struct VERTEX
{
	DVECTOR coord;
	UV_INFO uv_coord;
	unsigned char pad[2];
};

struct TRAILBLAZER_DATA
{
	int x;
	int z;
	short y;
	short rot;
};

struct SMASHED_CONE
{
	char cone;
	unsigned char active : 7;
	unsigned char side : 1;
	short rot_speed;
	VECTOR velocity;
};

struct POLYCOORD
{
	short x;
	short y;
	short u;
	short v;
	short w;
	short h;
};

struct EventGlobal
{
	int camera;
	int draw;
	EVENT** track;
	EVENT* cameraEvent;
};

enum SpecialCamera
{
	SPECIAL_CAMERA_SET = 0,
	SPECIAL_CAMERA_SET2 = 1,
	SPECIAL_CAMERA_RESET = 2,
	SPECIAL_CAMERA_WAIT = 3,
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

struct MULTICAR_DATA
{
	int x;
	int z;
	unsigned char palette;
	unsigned char model;
	short rot;
};

struct RENDER_ARG
{
	unsigned char render;
	unsigned char credits;
	unsigned short recap;
};

struct RENDER_ARGS
{
	unsigned char nRenders;
	unsigned char subtitle;
	char screenx;
	char screeny;
	RENDER_ARG Args[4];
};

typedef struct __envsound
{
	unsigned char type;
	unsigned char flags;
	VECTOR pos;
	VECTOR pos2;
	int bank;
	int sample;
	int vol;
} envsound;

typedef struct __envsoundtags
{
	int frame_cnt;
	int func_cnt;
	int num_envsnds;
	int envsnd_cnt;
} envsoundtags;

typedef struct __envsoundinfo
{
	VECTOR eff_pos[4];
	VECTOR cam_pos;
	float g[4];
	int thisS[4];
	int playing_sound[4];
	int chan[4];
	unsigned long flags;
} envsoundinfo;

struct SPEECH_QUEUE
{
	char allowed;
	char chan;
	char is_playing;
	int count;
	char reverb;
	int slot[7];
};

typedef struct __othercarsound
{
	int car;
	int chan;
	char in_use;
	char stopped;
	char idle;
} othercarsound;

typedef struct __bitfield64
{
	long h;
	long l;
} bitfield64;

struct GEAR_DESC
{
	int lowidl_ws;
	int low_ws;
	int hi_ws;
	int ratio_ac;
	int ratio_id;
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

struct MISSION_STEP
{
	unsigned char flags : 3;
	unsigned char recap : 5;
	unsigned char data : 7;
	unsigned char disc : 1;
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

struct _HANDLING_TYPE
{
	char frictionScaleRatio;
	char aggressiveBraking;
	char fourWheelDrive;
	char autoBrakeOn;
};

struct CHEATS
{
	int RearWheelSteer;
	int MiniCars;
	int Stilts;
	int LowGravity;
	int Australia;
	int MagicMirror;
};

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

struct MAP_DATA
{
	CAR_DATA* cp;
	VECTOR* base;
	VECTOR* pos;
	VECTOR* vel;
	VECTOR* size;
	int intention;
	int* map;
	int* local;
};

struct GAME_SAVE_HEADER
{
	unsigned long magic;
	unsigned char gMissionLadderPos;
	unsigned char pad1;
	unsigned char pad2;
	unsigned char pad3;
	MISSION_DATA SavedData;
	int reserved[8];
};

struct CONFIG_SAVE_HEADER
{
	unsigned long magic;
	int gMasterVolume;
	int gMusicVolume;
	int gSoundMode;
	int gVibration;
	int gCopDifficultyLevel;
	int gFurthestMission;
	MAPPING PadMapping[2];
	SCORE_TABLES ScoreTables;
	int PALAdjustX;
	int PALAdjustY;
	int NTSCAdjustX;
	int NTSCAdjustY;
	int gSubtitles;
	ACTIVE_CHEATS AvailableCheats;
	int reserved[6];
};

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

struct OUT_CELL_FILE_HEADER
{
	int cells_across;
	int cells_down;
	int cell_size;
	int num_regions;
	int region_size;
	int num_cell_objects;
	int num_cell_data;
	int ambient_light_level;
	VECTOR_NOPAD light_source;
};

enum EXIT_VALUE
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

struct XYWH
{
	short x;
	short y;
	short w;
	short h;
};

typedef void(*pauseFunc)(int dir);

struct MENU_ITEM;
struct MENU_HEADER;

struct MENU_ITEM
{
	char* Text;
	unsigned char Type;
	unsigned char Justify;
	pauseFunc func;
	EXIT_VALUE ExitValue;
	MENU_HEADER* SubMenu;
};

struct MENU_HEADER
{
	char* Title;
	XYWH Bound;
	unsigned char NumItems;
	MENU_ITEM* MenuItems;
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

struct __io
{
	char in;
	char out;
};

struct __xa_request
{
	short delay;
	char bank;
	char track;
	char mission;
	char cutscene;
};

struct _MISSION
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
};

struct _ROUTE_INFO
{
	int nJunctions;
	char data[1000][4];
	LEAD_PARAMETERS parameters;
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

struct STOPCOPS
{
	VECTOR_NOPAD pos;
	int radius;
};

enum FAIL_REASON
{
	FAILED_OUTOFTIME = 0,
	FAILED_CnR_LOSTHIM = 1,
	FAILED_MESSAGESET = 2,
};

struct MR_THREAD
{
	unsigned char active;
	unsigned char player;
	unsigned long* initial_sp;
	unsigned long* pc;
	unsigned long* sp;
};

struct POLYFT3
{
	unsigned char id;
	unsigned char texture_set;
	unsigned char texture_id;
	unsigned char spare;
	unsigned char v0;
	unsigned char v1;
	unsigned char v2;
	unsigned char pad;
	UV_INFO uv0;
	UV_INFO uv1;
	UV_INFO uv2;
	UV_INFO pad2;
	RGB color;
};

struct POLYGT3
{
	unsigned char id;
	unsigned char texture_set;
	unsigned char texture_id;
	unsigned char spare;
	unsigned char v0;
	unsigned char v1;
	unsigned char v2;
	unsigned char pad;
	unsigned char n0;
	unsigned char n1;
	unsigned char n2;
	unsigned char pad2;
	UV_INFO uv0;
	UV_INFO uv1;
	UV_INFO uv2;
	UV_INFO pad3;
	RGB color;
};

enum LIMBS
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

struct BONE
{
	LIMBS id;
	BONE* pParent;
	char numChildren;
	BONE(*pChildren[3]);
	SVECTOR_NOPAD* pvOrigPos;
	SVECTOR* pvRotation;
	VECTOR vOffset;
	VECTOR vCurrPos;
	MODEL** pModel;
};

enum TEXTURE_PALS
{
	NO_PAL = 0,
	JEANS_PAL = 1,
	ARM_PAL = 2,
	CHEST_PAL = 3,
};

struct PED_DATA
{
	char cWidth;
	unsigned char cAdj;
	TEXTURE_DETAILS* ptd;
	TEXTURE_PALS texPal;
};

struct tRay
{
	long org[4];
	long dir[4];
};

struct tRange
{
	int lower;
	int upper;
};

struct tAABB
{
	tRange slab[3];
};

struct DUPLICATION
{
	char* buffer;
	int size;
};

struct tNode
{
	int vx;
	int vy;
	int vz;
	unsigned short dist;
	unsigned short ptoey;
};

struct PATHFIND_237fake
{
	short dx;
	short dz;
};

struct PATHFIND_238fake
{
	short dx;
	short dz;
};

struct PLAYER_SCORE
{
	int time;
	int P2time;
	short items;
	short P2items;
	char name[6];
};

typedef struct SEATED_PEDESTRIANS
{
	int x;
	int z;
	short rotation;
	char index;
	char pad;
} *SEATEDPTR;

struct CAR_COLLISION_BOX
{
	int min_x;
	int max_x;
	int min_z;
	int max_z;
};

typedef struct PEDESTRIAN_ROADS
{
	short pos;
	short north;
	short south;
	short east;
	short west;
} *LPPEDESTRIAN_ROADS;

struct OUT_FONTINFO
{
	unsigned char x;
	unsigned char y;
	char offx;
	char offy;
	unsigned char width;
	unsigned char height;
	unsigned short pad;
};

struct FONT_DIGIT
{
	char xOffset;
	char width;
};

struct TEXINF
{
	unsigned short id;
	unsigned short nameoffset;
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct SHADOWHDR
{
	unsigned long num_common_verts;
	unsigned short num_verts_total;
	unsigned short num_polys_total;
	unsigned short vert_offsets[4];
	unsigned short nverts[4];
	unsigned short npolys[4];
	unsigned long(*poly_block[4]);
	SVECTOR* vertices;
};

struct TYRE_TRACK
{
	u_char type;
	u_char shade;
	u_char shade_type;
	u_char surface;
	SVECTOR_NOPAD p1;
	SVECTOR_NOPAD p2;
	SVECTOR_NOPAD p3;
	SVECTOR_NOPAD p4;
};

struct S_XYZ
{
	short x;
	short y;
	short z;
};

struct FLAREREC
{
	RGB16 transparency;
	char size;
	short gapmod;
};

struct __LSBDinfo
{
	int addr;
	int memtop;
	int count[7];
	int bnktop[7];
	int append;
};

struct CHANNEL_DATA
{
	SpuVoiceAttr attr;
	unsigned char loop;
	unsigned char locked;
	unsigned short time;
	long samplerate;
	char player;
	long srcvolume;
	long volumeScale;
	unsigned short srcpitch;
	unsigned short dopplerScale;
	long cameradist;
	long lastcameradist;
	VECTOR* srcposition;
	VECTOR position;
	long* srcvelocity;
};

struct SAMPLE_DATA
{
	unsigned long address;
	unsigned long length;
	unsigned long loop;
	unsigned long samplerate;
};

struct __pauseinfo
{
	unsigned short pitch[16];
	unsigned short voll[16];
	unsigned short volr[16];
	unsigned short max;
	unsigned short lev;
};

struct SPOOLQ
{
	unsigned char type;
	unsigned char data;
	unsigned short nsectors;
	unsigned long sector;
	char* addr;
	void (*func)();
#ifdef _DEBUG
	const char* requestby;
	int requestbyline;
#endif
};

struct SPL_REGIONINFO
{
	unsigned short region_to_unpack;
	unsigned short target_barrel_region;
	int nsectors;
	char* cell_addr;
	char* roadm_addr;
};

struct AreaDataStr
{
	unsigned short gfx_offset;
	unsigned short model_offset;
	unsigned short music_offset;
	unsigned short ambient_offset;
	unsigned char model_size;
	unsigned char pad;
	unsigned char num_tpages;
	unsigned char ambient_size;
	unsigned char music_size;
	unsigned char music_samples_size;
	unsigned char music_id;
	unsigned char ambient_id;
};

struct DRAW_MODE
{
	short x1;
	short y1;
	short x2;
	short y2;
	short width;
	short height;
	short framex;
	short framey;
};

enum CDTYPE
{
	CDTYPE_NODISC = 0,
	CDTYPE_SHELLOPEN = 1,
	CDTYPE_DISCERROR = 2,
	CDTYPE_WRONGDISC = 3,
	CDTYPE_CORRECTDISC = 4,
};

enum CITYTYPE
{
	CITYTYPE_DAY = 0,
	CITYTYPE_NIGHT = 1,
	CITYTYPE_MULTI_DAY = 2,
	CITYTYPE_MULTI_NIGHT = 3,
};

struct TARGET_ARROW_MODEL
{
	SVECTOR* pVerts;
	char* pTris;
	char numTris;
};

struct TP
{
	unsigned long flags;
	unsigned long offset;
};

struct CAR_LOCALS
{
	long vel[4];
	long avel[4];
	int extraangulardamping;
	int aggressive;
};

struct XA_TRACK
{
	int start;
	int end;
};

struct FE_CHARDATA
{
	unsigned char u;
	unsigned char v;
	unsigned char w;
	unsigned char h;
};

struct FE_FONT
{
	int NumFonts;
	FE_CHARDATA CharInfo[256];
};

struct SCREEN_LIMITS
{
	short minx;
	short miny;
	short maxx;
	short maxy;
};

struct BOTCH
{
	int missNum;
	char** name;
};

#endif // DR2TYPES_H