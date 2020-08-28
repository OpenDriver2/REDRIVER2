//Version = 1, targetUnit = 0

// 16 enums
enum PAUSEMODE : char {
  PAUSEMODE_PAUSE = 0,
  PAUSEMODE_PAUSEP1 = 1,
  PAUSEMODE_PAUSEP2 = 2,
  PAUSEMODE_GAMEOVER = 3,
  PAUSEMODE_COMPLETE = 4,
  PAUSEMODE_PADERROR = 5,
};
enum PED_ACTION_TYPE : char {
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
enum PED_MODEL_TYPES : char {
  TANNER_MODEL = 0,
  OTHER_MODEL = 1,
  OTHER_SPRITE = 2,
  CIVILIAN = 3,
};
enum ExplosionType : short {
  BIG_BANG = 0,
  LITTLE_BANG = 1,
  HEY_MOMMA = 666,
  BANG_USED = 999,
};
enum AIZone : char {
  zoneFrnt = 0,
  zoneBack = 1,
  zoneLeft = 2,
  zoneRght = 3,
};
enum SpecialCamera : char {
  SPECIAL_CAMERA_SET = 0,
  SPECIAL_CAMERA_SET2 = 1,
  SPECIAL_CAMERA_RESET = 2,
  SPECIAL_CAMERA_WAIT = 3,
};
enum VisType : char {
  VIS_INIT = 0,
  VIS_SORT = 1,
  VIS_ADD = 2,
  VIS_NEXT = 3,
};
enum Station : char {
  EVENT_NO_STATION = 0,
  EVENT_APPROACHING = 1,
  EVENT_LEAVING = 2,
};
enum GAMEMODE : char {
  GAMEMODE_NORMAL = 0,
  GAMEMODE_QUIT = 1,
  GAMEMODE_RESTART = 2,
  GAMEMODE_REPLAY = 3,
  GAMEMODE_DIRECTOR = 4,
  GAMEMODE_NEXTMISSION = 5,
  GAMEMODE_DEMO = 6,
};
enum GAMETYPE : char {
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
enum EXIT_VALUE : char {
  MENU_QUIT_NONE = 0,
  MENU_QUIT_CONTINUE = 1,
  MENU_QUIT_QUIT = 2,
  MENU_QUIT_RESTART = 3,
  MENU_QUIT_DIRECTOR = 4,
  MENU_QUIT_QUICKREPLAY = 5,
  MENU_QUIT_BACKMENU = 6,
  MENU_QUIT_NEXTMISSION = 7,
};
enum FAIL_REASON : char {
  FAILED_OUTOFTIME = 0,
  FAILED_CnR_LOSTHIM = 1,
  FAILED_MESSAGESET = 2,
};
enum LIMBS : char {
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
enum TEXTURE_PALS : char {
  NO_PAL = 0,
  JEANS_PAL = 1,
  ARM_PAL = 2,
  CHEST_PAL = 3,
};
enum CDTYPE : char {
  CDTYPE_NODISC = 0,
  CDTYPE_SHELLOPEN = 1,
  CDTYPE_DISCERROR = 2,
  CDTYPE_WRONGDISC = 3,
  CDTYPE_CORRECTDISC = 4,
};
enum CITYTYPE : char {
  CITYTYPE_DAY = 0,
  CITYTYPE_NIGHT = 1,
  CITYTYPE_MULTI_DAY = 2,
  CITYTYPE_MULTI_NIGHT = 3,
};

struct bodyst {
  	long fposition[3]; // size=12, offset=0
  	long orientation[4]; // size=16, offset=12
  	long linearVelocity[3]; // size=12, offset=28
  	long angularVelocity[3]; // size=12, offset=40
};

// 22 unions
union RigidBodyState {
  long v[13]; // size=52, offset=0
  struct bodyst n; // size=52, offset=0
};

// 300 structs
struct TCB {
  long status; // size=0, offset=0
  long mode; // size=0, offset=4
  unsigned long reg[40]; // size=160, offset=8
  long system[6]; // size=24, offset=168
};
struct EXEC {
  unsigned long pc0; // size=0, offset=0
  unsigned long gp0; // size=0, offset=4
  unsigned long t_addr; // size=0, offset=8
  unsigned long t_size; // size=0, offset=12
  unsigned long d_addr; // size=0, offset=16
  unsigned long d_size; // size=0, offset=20
  unsigned long b_addr; // size=0, offset=24
  unsigned long b_size; // size=0, offset=28
  unsigned long s_addr; // size=0, offset=32
  unsigned long s_size; // size=0, offset=36
  unsigned long sp; // size=0, offset=40
  unsigned long fp; // size=0, offset=44
  unsigned long gp; // size=0, offset=48
  unsigned long ret; // size=0, offset=52
  unsigned long base; // size=0, offset=56
};
struct DIRENTRY {
  char name[20]; // size=20, offset=0
  long attr; // size=0, offset=20
  long size; // size=0, offset=24
  struct DIRENTRY *next; // size=40, offset=28
  long head; // size=0, offset=32
  char system[4]; // size=4, offset=36
};
struct MATRIX {
  short m[3][3]; // size=18, offset=0
  long t[3]; // size=12, offset=20
};
struct VECTOR {
  long vx; // size=0, offset=0
  long vy; // size=0, offset=4
  long vz; // size=0, offset=8
  long pad; // size=0, offset=12
};
struct SVECTOR {
  short vx; // size=0, offset=0
  short vy; // size=0, offset=2
  short vz; // size=0, offset=4
  short pad; // size=0, offset=6
};
struct CVECTOR {
  unsigned char r; // size=0, offset=0
  unsigned char g; // size=0, offset=1
  unsigned char b; // size=0, offset=2
  unsigned char cd; // size=0, offset=3
};
struct DVECTOR {
  short vx; // size=0, offset=0
  short vy; // size=0, offset=2
};
struct RVECTOR {
  struct SVECTOR v; // size=8, offset=0
  unsigned char uv[2]; // size=2, offset=8
  unsigned short pad; // size=0, offset=10
  struct CVECTOR c; // size=4, offset=12
  struct DVECTOR sxy; // size=4, offset=16
  unsigned long sz; // size=0, offset=20
};
struct CRVECTOR3 {
  struct RVECTOR r01; // size=24, offset=0
  struct RVECTOR r12; // size=24, offset=24
  struct RVECTOR r20; // size=24, offset=48
  struct RVECTOR *r0; // size=24, offset=72
  struct RVECTOR *r1; // size=24, offset=76
  struct RVECTOR *r2; // size=24, offset=80
  unsigned long *rtn; // size=0, offset=84
};
struct CRVECTOR4 {
  struct RVECTOR r01; // size=24, offset=0
  struct RVECTOR r02; // size=24, offset=24
  struct RVECTOR r31; // size=24, offset=48
  struct RVECTOR r32; // size=24, offset=72
  struct RVECTOR rc; // size=24, offset=96
  struct RVECTOR *r0; // size=24, offset=120
  struct RVECTOR *r1; // size=24, offset=124
  struct RVECTOR *r2; // size=24, offset=128
  struct RVECTOR *r3; // size=24, offset=132
  unsigned long *rtn; // size=0, offset=136
};
struct RECT {
  short x; // size=0, offset=0
  short y; // size=0, offset=2
  short w; // size=0, offset=4
  short h; // size=0, offset=6
};
struct DR_ENV {
  unsigned long tag; // size=0, offset=0
  unsigned long code[15]; // size=60, offset=4
};
struct SndVolume2 {
  short left; // size=0, offset=0
  short right; // size=0, offset=2
};
struct CdlLOC {
  unsigned char minute; // size=0, offset=0
  unsigned char second; // size=0, offset=1
  unsigned char sector; // size=0, offset=2
  unsigned char track; // size=0, offset=3
};
struct VECTOR_NOPAD {
  long vx; // size=0, offset=0
  long vy; // size=0, offset=4
  long vz; // size=0, offset=8
};
struct SVECTOR_NOPAD {
  short vx; // size=0, offset=0
  short vy; // size=0, offset=2
  short vz; // size=0, offset=4
};
struct BOX {
  float xmin; // size=0, offset=0
  float ymin; // size=0, offset=4
  float zmin; // size=0, offset=8
  float xmax; // size=0, offset=12
  float ymax; // size=0, offset=16
  float zmax; // size=0, offset=20
};
struct BSPHERE {
  struct VECTOR bounding_sphere_mid; // size=16, offset=0
  float bounding_sphere; // size=0, offset=16
};
struct RGB {
  unsigned char r; // size=0, offset=0
  unsigned char g; // size=0, offset=1
  unsigned char b; // size=0, offset=2
  unsigned char pad; // size=0, offset=3
};
struct UV_INFO {
  unsigned char u; // size=0, offset=0
  unsigned char v; // size=0, offset=1
};
struct XYPAIR {
  int x; // size=0, offset=0
  int y; // size=0, offset=4
};
struct SXYPAIR {
  short x; // size=0, offset=0
  short y; // size=0, offset=2
};
struct GAP_INFO {
  struct DVECTOR offset; // size=4, offset=0
  char clear; // size=0, offset=4
};
struct PSXBUTTON {
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
struct PADRECORD {
  unsigned char pad; // size=0, offset=0
  char analogue; // size=0, offset=1
  unsigned char run; // size=0, offset=2
};
struct ARC_ENTRY {
  short offset; // size=0, offset=0
  short length; // size=0, offset=2
};
struct USVECTOR_NOPAD {
  unsigned short vx; // size=0, offset=0
  unsigned short vy; // size=0, offset=2
  unsigned short vz; // size=0, offset=4
};
struct DRIVER2_STRAIGHT {
  int Midx; // size=0, offset=0
  int Midz; // size=0, offset=4
  unsigned short length; // size=0, offset=8
  short bing; // size=0, offset=10
  short angle; // size=0, offset=12
  short ConnectIdx[4]; // size=8, offset=14
  char NumLanes; // size=0, offset=22
  char LaneDirs; // size=0, offset=23
  char AILanes; // size=0, offset=24
  char packing; // size=0, offset=25
};
struct OLD_DRIVER2_JUNCTION {
  int Midx; // size=0, offset=0
  int Midz; // size=0, offset=4
  short length; // size=0, offset=8
  short width; // size=0, offset=10
  short angle; // size=0, offset=12
  short ExitIdx[4]; // size=8, offset=14
  unsigned short flags; // size=0, offset=22
};
struct DRIVER2_JUNCTION {
  short ExitIdx[4]; // size=8, offset=0
  unsigned long flags; // size=0, offset=8
};
struct DRIVER2_CURVE {
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
struct _sdPlane {
  short surface; // size=0, offset=0
  short a; // size=0, offset=2
  short b; // size=0, offset=4
  short c; // size=0, offset=6
  int d; // size=0, offset=8
};
struct _sdNode {
  int angle : 11; // offset=0.0
  int dist : 12; // offset=1.3
  int offset : 8; // offset=2.7
  int node : 1; // offset=3.7
};
struct _CAR_DATA {
  struct _HANDLING_DATA hd; // size=240, offset=0
  union RigidBodyState st; // size=52, offset=240
  struct _APPEARANCE_DATA ap; // size=100, offset=292
  unsigned char hndType; // size=0, offset=392
  unsigned char controlType; // size=0, offset=393
  unsigned char controlFlags; // size=0, offset=394
  char id; // size=0, offset=395
  union ai {
    char *padid; // size=0, offset=0
    struct CIV_STATE c; // size=252, offset=0
    struct COP p; // size=40, offset=0
    struct LEAD_CAR l; // size=104, offset=0
  }; // size=252, offset=396
  int *inform; // size=0, offset=648
  short thrust; // size=0, offset=652
  short felonyRating; // size=0, offset=654
  char handbrake; // size=0, offset=656
  char wheelspin; // size=0, offset=657
  char wasOnGround; // size=0, offset=658
  char lowDetail; // size=0, offset=659
  short wheel_angle; // size=0, offset=660
  unsigned short totalDamage; // size=0, offset=662
  long lastPad; // size=0, offset=664
};
struct CIV_ROUTE_ENTRY {
  short dir; // size=0, offset=0
  unsigned short pathType; // size=0, offset=2
  int distAlongSegment; // size=0, offset=4
  int x; // size=0, offset=8
  int z; // size=0, offset=12
};
struct CIV_STATE {
  int currentRoad; // size=0, offset=0
  int currentNode; // size=0, offset=4
  struct CIV_ROUTE_ENTRY *ctrlNode; // size=16, offset=8
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
  struct CIV_ROUTE_ENTRY *pnode; // size=16, offset=244
  unsigned char maxSpeed; // size=0, offset=248
  unsigned char thrustState; // size=0, offset=249
  unsigned char carMustDie; // size=0, offset=250
  unsigned char currentLane; // size=0, offset=251
};
struct CAR_COSMETICS {
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
struct VECTOR2 {
  int vx; // size=0, offset=0
  int vz; // size=0, offset=4
};
struct COP {
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
struct LEAD_CAR {
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

struct WHEEL {
  char susCompression; // size=0, offset=0
  char locked; // size=0, offset=1
  char onGrass; // size=0, offset=2
  unsigned char surface; // size=0, offset=3
};
struct OrientedBox {
  struct VECTOR_NOPAD location; // size=12, offset=0
  struct SVECTOR_NOPAD radii[3]; // size=18, offset=12
  short length[3]; // size=6, offset=30
};
struct _HANDLING_DATA {
  struct MATRIX where; // size=32, offset=0
  struct MATRIX drawCarMat; // size=32, offset=32
  long acc[4]; // size=16, offset=64
  long aacc[4]; // size=16, offset=80
  int wheel_speed; // size=0, offset=96
  int speed; // size=0, offset=100
  int direction; // size=0, offset=104
  char gear; // size=0, offset=108
  char changingGear; // size=0, offset=109
  char mayBeColliding; // size=0, offset=110
  char autoBrake; // size=0, offset=111
  struct WHEEL wheel[4]; // size=16, offset=112
  short revs; // size=0, offset=128
  struct VECTOR shadowPoints[4]; // size=64, offset=132
  int front_vel; // size=0, offset=196
  int rear_vel; // size=0, offset=200
  struct OrientedBox oBox; // size=36, offset=204
};
struct _APPEARANCE_DATA {
  struct SXYPAIR light_trails[4][4]; // size=64, offset=0
  struct CAR_COSMETICS *carCos; // size=236, offset=64
  short old_clock[4]; // size=8, offset=68
  char life; // size=0, offset=76
  char coplife; // size=0, offset=77
  short qy; // size=0, offset=78
  short qw; // size=0, offset=80
  char life2; // size=0, offset=82
  char model; // size=0, offset=83
  char palette; // size=0, offset=84
  char needsDenting; // size=0, offset=85
  short damage[6]; // size=12, offset=86
};
struct _COP_DATA {
  int speed; // size=0, offset=0
  int power; // size=0, offset=4
  int min; // size=0, offset=8
  int max; // size=0, offset=12
};
struct LEAD_PARAMETERS {
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
struct _EVENT {
  struct VECTOR position; // size=16, offset=0
  short rotation; // size=0, offset=16
  short timer; // size=0, offset=18
  int *data; // size=0, offset=20
  int *node; // size=0, offset=24
  short flags; // size=0, offset=28
  short radius; // size=0, offset=30
  int model; // size=0, offset=32
  struct _EVENT *next; // size=40, offset=36
};
struct MAPPING {
  unsigned short button_lookup[16]; // size=32, offset=0
  unsigned short swap_analog; // size=0, offset=32
  unsigned short reserved1; // size=0, offset=34
};
struct SAVED_PLAYER_POS {
  unsigned short type; // size=0, offset=0
  short direction; // size=0, offset=2
  long vx; // size=0, offset=4
  long vy; // size=0, offset=8
  long vz; // size=0, offset=12
  unsigned long felony; // size=0, offset=16
  unsigned short totaldamage; // size=0, offset=20
  short damage[6]; // size=12, offset=22
};
struct SAVED_CAR_POS {
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
struct MISSION_DATA {
  struct SAVED_PLAYER_POS PlayerPos; // size=36, offset=0
  struct SAVED_CAR_POS CarPos[6]; // size=192, offset=36
};
struct SCORE_ENTRY {
  int time; // size=0, offset=0
  short items; // size=0, offset=4
  char name[6]; // size=6, offset=6
};
struct SCORE_TABLES {
  struct SCORE_ENTRY GetawayTable[4][2][5]; // size=480, offset=0
  struct SCORE_ENTRY GateRaceTable[4][2][5]; // size=480, offset=480
  struct SCORE_ENTRY CheckpointTable[4][2][5]; // size=480, offset=960
  struct SCORE_ENTRY TrailblazerTable[4][2][5]; // size=480, offset=1440
  struct SCORE_ENTRY SurvivalTable[4][1][5]; // size=240, offset=1920
};
struct ACTIVE_CHEATS {
  unsigned char cheat1 : 1; // offset=0.0
  unsigned char cheat2 : 1; // offset=0.1
  unsigned char cheat3 : 1; // offset=0.2
  unsigned char cheat4 : 1; // offset=0.3
  unsigned char cheat5 : 1; // offset=0.4
  unsigned char cheat6 : 1; // offset=0.5
  unsigned char cheat7 : 1; // offset=0.6
  unsigned char cheat8 : 1; // offset=0.7
  unsigned char cheat9 : 1; // offset=1.0
  unsigned char cheat10 : 1; // offset=1.1
  unsigned char cheat11 : 1; // offset=1.2
  unsigned char reserved1 : 5; // offset=1.3
  unsigned char reserved2; // size=0, offset=2
  unsigned char reserved3; // size=0, offset=3
};
struct STREAM_SOURCE {
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
struct DRAWENV {
  struct RECT clip; // size=8, offset=0
  short ofs[2]; // size=4, offset=8
  struct RECT tw; // size=8, offset=12
  unsigned short tpage; // size=0, offset=20
  unsigned char dtd; // size=0, offset=22
  unsigned char dfe; // size=0, offset=23
  unsigned char isbg; // size=0, offset=24
  unsigned char r0; // size=0, offset=25
  unsigned char g0; // size=0, offset=26
  unsigned char b0; // size=0, offset=27
  struct DR_ENV dr_env; // size=64, offset=28
};
struct DISPENV {
  struct RECT disp; // size=8, offset=0
  struct RECT screen; // size=8, offset=8
  unsigned char isinter; // size=0, offset=16
  unsigned char isrgb24; // size=0, offset=17
  unsigned char pad0; // size=0, offset=18
  unsigned char pad1; // size=0, offset=19
};
struct DR_LOAD {
  unsigned long tag; // size=0, offset=0
  unsigned long code[3]; // size=12, offset=4
  unsigned long p[13]; // size=52, offset=16
};
struct MODEL {
  unsigned short shape_flags; // size=0, offset=0
  unsigned short flags2; // size=0, offset=2
  short instance_number; // size=0, offset=4
  unsigned char tri_verts; // size=0, offset=6
  unsigned char zBias; // size=0, offset=7
  short bounding_sphere; // size=0, offset=8
  unsigned short num_point_normals; // size=0, offset=10
  unsigned short num_vertices; // size=0, offset=12
  unsigned short num_polys; // size=0, offset=14
  int vertices; // size=0, offset=16
  int poly_block; // size=0, offset=20
  int normals; // size=0, offset=24
  int point_normals; // size=0, offset=28
  int collision_block; // size=0, offset=32
};
struct UV {
  unsigned char u0; // size=0, offset=0
  unsigned char v0; // size=0, offset=1
  unsigned char u1; // size=0, offset=2
  unsigned char v1; // size=0, offset=3
  unsigned char u2; // size=0, offset=4
  unsigned char v2; // size=0, offset=5
  unsigned char u3; // size=0, offset=6
  unsigned char v3; // size=0, offset=7
};
struct TEXTURE_DETAILS {
  struct UV coords; // size=8, offset=0
  unsigned short tpageid; // size=0, offset=8
  unsigned short clutid; // size=0, offset=10
  char texture_number; // size=0, offset=12
  char texture_page; // size=0, offset=13
};
struct CELL_OBJECT {
  struct VECTOR_NOPAD pos; // size=12, offset=0
  unsigned char pad; // size=0, offset=12
  unsigned char yang; // size=0, offset=13
  unsigned short type; // size=0, offset=14
};
struct ANIMATED_OBJECT {
  int internal_id; // size=0, offset=0
  int model_num; // size=0, offset=4
  char *name; // size=0, offset=8
  char LitPoly; // size=0, offset=12
};
struct SMASHABLE_OBJECT {
  int modelIdx; // size=0, offset=0
  char *name; // size=0, offset=4
  int sound; // size=0, offset=8
  int volume; // size=0, offset=12
  int pitch; // size=0, offset=16
};
struct GARAGE_DOOR {
  struct CELL_OBJECT *cop; // size=16, offset=0
  struct VECTOR_NOPAD old_pos; // size=12, offset=4
  struct VECTOR_NOPAD pos; // size=12, offset=16
  short rotation; // size=0, offset=28
  char yang; // size=0, offset=30
};
struct RGB16 {
  short r; // size=0, offset=0
  short g; // size=0, offset=2
  short b; // size=0, offset=4
  short pad; // size=0, offset=6
};
struct UnpaddedHackVector {
  int vx; // size=0, offset=0
  int vz; // size=0, offset=4
  short vy; // size=0, offset=8
};
struct UnpaddedCharVector {
  char vx; // size=0, offset=0
  char vy; // size=0, offset=1
  char vz; // size=0, offset=2
};
struct BVECTOR {
  char vx; // size=0, offset=0
  char vy; // size=0, offset=1
  char vz; // size=0, offset=2
  char pad; // size=0, offset=3
};
struct ADJACENT_ROAD_INFO {
  struct DVECTOR offset; // size=4, offset=0
  struct GAP_INFO gap; // size=6, offset=4
};
struct SpuVolume {
  short left; // size=0, offset=0
  short right; // size=0, offset=2
};
struct SpuVoiceAttr {
  unsigned long voice; // size=0, offset=0
  unsigned long mask; // size=0, offset=4
  struct SpuVolume volume; // size=4, offset=8
  struct SpuVolume volmode; // size=4, offset=12
  struct SpuVolume volumex; // size=4, offset=16
  unsigned short pitch; // size=0, offset=20
  unsigned short note; // size=0, offset=22
  unsigned short sample_note; // size=0, offset=24
  short envx; // size=0, offset=26
  unsigned long addr; // size=0, offset=28
  unsigned long loop_addr; // size=0, offset=32
  long a_mode; // size=0, offset=36
  long s_mode; // size=0, offset=40
  long r_mode; // size=0, offset=44
  unsigned short ar; // size=0, offset=48
  unsigned short dr; // size=0, offset=50
  unsigned short sr; // size=0, offset=52
  unsigned short rr; // size=0, offset=54
  unsigned short sl; // size=0, offset=56
  unsigned short adsr1; // size=0, offset=58
  unsigned short adsr2; // size=0, offset=60
};
struct SpuExtAttr {
  struct SpuVolume volume; // size=4, offset=0
  long reverb; // size=0, offset=4
  long mix; // size=0, offset=8
};
struct SpuStVoiceAttr {
  char status; // size=0, offset=0
  char pad1; // size=0, offset=1
  char pad2; // size=0, offset=2
  char pad3; // size=0, offset=3
  long last_size; // size=0, offset=4
  unsigned long buf_addr; // size=0, offset=8
  unsigned long data_addr; // size=0, offset=12
};

struct FELONY_DELAY {
  short current; // size=0, offset=0
  short maximum; // size=0, offset=2
};
struct FELONY_VALUE {
  short placid; // size=0, offset=0
  short angry; // size=0, offset=2
};
struct DB {
  char *primptr; // size=0, offset=0
  unsigned long *ot; // size=0, offset=4
  char *primtab; // size=0, offset=8
  int id; // size=0, offset=12
  struct DRAWENV draw; // size=92, offset=16
  struct DISPENV disp; // size=20, offset=108
};
struct _TARGET {
  int data[16]; // size=64, offset=0
};
struct MR_TIMER {
  short x; // size=0, offset=0
  short y; // size=0, offset=2
  unsigned char flags; // size=0, offset=4
  unsigned char min; // size=0, offset=5
  unsigned char sec; // size=0, offset=6
  unsigned char frac; // size=0, offset=7
  long count; // size=0, offset=8
};
struct PEDESTRIAN {
  struct PEDESTRIAN *pNext; // size=92, offset=0
  struct PEDESTRIAN *pPrev; // size=92, offset=4
  void (*fpRestState)(); // size=0, offset=8
  void (*fpAgitatedState)(); // size=0, offset=12
  char padId; // size=0, offset=16
  enum PED_MODEL_TYPES pedType; // size=1, offset=17
  struct VECTOR_NOPAD position; // size=12, offset=20
  struct SVECTOR dir; // size=8, offset=32
  struct SVECTOR velocity; // size=8, offset=40
  struct VECTOR target; // size=16, offset=48
  int flags; // size=0, offset=64
  short head_pos; // size=0, offset=68
  short head_rot; // size=0, offset=70
  short index; // size=0, offset=72
  short last_dir; // size=0, offset=74
  short interest; // size=0, offset=76
  char frame1; // size=0, offset=78
  char *motion; // size=0, offset=80
  char speed; // size=0, offset=84
  char doing_turn; // size=0, offset=85
  char finished_turn; // size=0, offset=86
  char seat_index; // size=0, offset=87
  unsigned char pallet; // size=0, offset=88
  enum PED_ACTION_TYPE type; // size=1, offset=89
};
struct __skidinfo {
  char chan; // size=0, offset=0
  char sound; // size=0, offset=1
};
struct __horninfo {
  char on; // size=0, offset=0
  char time; // size=0, offset=1
  char request; // size=0, offset=2
};
struct CYCLE_OBJECT {
  char *name; // size=0, offset=0
  short vx; // size=0, offset=4
  short vy; // size=0, offset=6
  short start1; // size=0, offset=8
  short stop1; // size=0, offset=10
  short speed1; // size=0, offset=12
  short start2; // size=0, offset=14
  short stop2; // size=0, offset=16
  short speed2; // size=0, offset=18
};
struct POLY_G4 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  unsigned char r1; // size=0, offset=12
  unsigned char g1; // size=0, offset=13
  unsigned char b1; // size=0, offset=14
  unsigned char pad1; // size=0, offset=15
  short x1; // size=0, offset=16
  short y1; // size=0, offset=18
  unsigned char r2; // size=0, offset=20
  unsigned char g2; // size=0, offset=21
  unsigned char b2; // size=0, offset=22
  unsigned char pad2; // size=0, offset=23
  short x2; // size=0, offset=24
  short y2; // size=0, offset=26
  unsigned char r3; // size=0, offset=28
  unsigned char g3; // size=0, offset=29
  unsigned char b3; // size=0, offset=30
  unsigned char pad3; // size=0, offset=31
  short x3; // size=0, offset=32
  short y3; // size=0, offset=34
};
struct TILE {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  short w; // size=0, offset=12
  short h; // size=0, offset=14
};
struct DR_TPAGE {
  unsigned long tag; // size=0, offset=0
  unsigned long code[1]; // size=4, offset=4
};

struct CAR_POLY {
  int vindices; // size=0, offset=0
  int nindices; // size=0, offset=4
  int clut_uv0; // size=0, offset=8
  int tpage_uv1; // size=0, offset=12
  int uv3_uv2; // size=0, offset=16
  short originalindex; // size=0, offset=20
};
struct COLOUR_BAND {
  struct CVECTOR colour; // size=4, offset=0
  int value; // size=0, offset=4
  int flags; // size=0, offset=8
};
struct _PERCENTAGE_BAR {
  char *tag; // size=0, offset=0
  short xpos; // size=0, offset=4
  short ypos; // size=0, offset=6
  short width; // size=0, offset=8
  short height; // size=0, offset=10
  unsigned short position; // size=0, offset=12
  unsigned short max; // size=0, offset=14
  struct COLOUR_BAND *pColourBand; // size=12, offset=16
  int flags; // size=0, offset=20
  int active; // size=0, offset=24
};
struct POLY_F3 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  short x1; // size=0, offset=12
  short y1; // size=0, offset=14
  short x2; // size=0, offset=16
  short y2; // size=0, offset=18
};
struct POLY_F4 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  short x1; // size=0, offset=12
  short y1; // size=0, offset=14
  short x2; // size=0, offset=16
  short y2; // size=0, offset=18
  short x3; // size=0, offset=20
  short y3; // size=0, offset=22
};
struct POLY_FT3 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  unsigned char u0; // size=0, offset=12
  unsigned char v0; // size=0, offset=13
  unsigned short clut; // size=0, offset=14
  short x1; // size=0, offset=16
  short y1; // size=0, offset=18
  unsigned char u1; // size=0, offset=20
  unsigned char v1; // size=0, offset=21
  unsigned short tpage; // size=0, offset=22
  short x2; // size=0, offset=24
  short y2; // size=0, offset=26
  unsigned char u2; // size=0, offset=28
  unsigned char v2; // size=0, offset=29
  unsigned short pad1; // size=0, offset=30
};
struct POLY_FT4 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  unsigned char u0; // size=0, offset=12
  unsigned char v0; // size=0, offset=13
  unsigned short clut; // size=0, offset=14
  short x1; // size=0, offset=16
  short y1; // size=0, offset=18
  unsigned char u1; // size=0, offset=20
  unsigned char v1; // size=0, offset=21
  unsigned short tpage; // size=0, offset=22
  short x2; // size=0, offset=24
  short y2; // size=0, offset=26
  unsigned char u2; // size=0, offset=28
  unsigned char v2; // size=0, offset=29
  unsigned short pad1; // size=0, offset=30
  short x3; // size=0, offset=32
  short y3; // size=0, offset=34
  unsigned char u3; // size=0, offset=36
  unsigned char v3; // size=0, offset=37
  unsigned short pad2; // size=0, offset=38
};
struct POLY_G3 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  unsigned char r1; // size=0, offset=12
  unsigned char g1; // size=0, offset=13
  unsigned char b1; // size=0, offset=14
  unsigned char pad1; // size=0, offset=15
  short x1; // size=0, offset=16
  short y1; // size=0, offset=18
  unsigned char r2; // size=0, offset=20
  unsigned char g2; // size=0, offset=21
  unsigned char b2; // size=0, offset=22
  unsigned char pad2; // size=0, offset=23
  short x2; // size=0, offset=24
  short y2; // size=0, offset=26
};
struct LINE_F2 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  short x1; // size=0, offset=12
  short y1; // size=0, offset=14
};
struct LINE_G2 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  unsigned char r1; // size=0, offset=12
  unsigned char g1; // size=0, offset=13
  unsigned char b1; // size=0, offset=14
  unsigned char p1; // size=0, offset=15
  short x1; // size=0, offset=16
  short y1; // size=0, offset=18
};
struct LINE_F4 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  short x1; // size=0, offset=12
  short y1; // size=0, offset=14
  short x2; // size=0, offset=16
  short y2; // size=0, offset=18
  short x3; // size=0, offset=20
  short y3; // size=0, offset=22
  unsigned long pad; // size=0, offset=24
};
struct TILE_1 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
};
struct DR_AREA {
  unsigned long tag; // size=0, offset=0
  unsigned long code[2]; // size=8, offset=4
};
struct COP_SIGHT_DATA {
  short surroundViewDistance; // size=0, offset=0
  short frontViewDistance; // size=0, offset=2
  short frontViewAngle; // size=0, offset=4
};
struct MAPTEX {
  short u; // size=0, offset=0
  short w; // size=0, offset=2
  short v; // size=0, offset=4
  short h; // size=0, offset=6
};
struct OVERMAP {
  int x_offset; // size=0, offset=0
  int y_offset; // size=0, offset=4
  int width; // size=0, offset=8
  int height; // size=0, offset=12
  char toptile; // size=0, offset=16
  char dummy; // size=0, offset=17
  int scale; // size=0, offset=20
};
struct REPLAY_PARAMETER_BLOCK {
  int RecordingEnd; // size=0, offset=0
  struct VECTOR_NOPAD lead_car_start; // size=12, offset=4
  short Lead_car_dir; // size=0, offset=16
  unsigned char timeofday; // size=0, offset=18
  unsigned char weather; // size=0, offset=19
};

struct REPLAY_SAVE_HEADER {
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
struct REPLAY_STREAM_HEADER {
  struct STREAM_SOURCE SourceType; // size=48, offset=0
  int Size; // size=0, offset=48
  int Length; // size=0, offset=52
};
struct REPLAY_STREAM {
  struct STREAM_SOURCE SourceType; // size=48, offset=0
  struct PADRECORD *InitialPadRecordBuffer; // size=3, offset=48
  struct PADRECORD *PadRecordBuffer; // size=3, offset=52
  struct PADRECORD *PadRecordBufferEnd; // size=3, offset=56
  unsigned char playbackrun; // size=0, offset=60
  int length; // size=0, offset=64
};
struct _PING_PACKET {
  unsigned short frame; // size=0, offset=0
  char carId; // size=0, offset=2
  char cookieCount; // size=0, offset=3
};

struct ROADBLOCK {
  struct VECTOR position; // size=16, offset=0
  struct ADJACENT_ROAD_INFO adjacentRoadInfo; // size=10, offset=16
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
struct TestResult {
  int depth; // size=0, offset=0
  struct VECTOR location; // size=16, offset=4
  struct VECTOR normal; // size=16, offset=20
};

struct BUILDING_BOX {
  struct VECTOR pos; // size=16, offset=0
  int xsize; // size=0, offset=16
  int zsize; // size=0, offset=20
  int theta; // size=0, offset=24
  int height; // size=0, offset=28
};
struct CDATA2D {
  struct VECTOR x; // size=16, offset=0
  struct VECTOR axis[2]; // size=32, offset=16
  struct VECTOR vel; // size=16, offset=48
  int theta; // size=0, offset=64
  int length[2]; // size=8, offset=68
  int dist[2]; // size=8, offset=76
  int limit[2]; // size=8, offset=84
  int avel; // size=0, offset=92
  int isCameraOrTanner; // size=0, offset=96
};
struct CRET2D {
  struct VECTOR hit; // size=16, offset=0
  struct VECTOR surfNormal; // size=16, offset=16
  int penetration; // size=0, offset=32
  int neverfree; // size=0, offset=36
};
struct __tunnelcoords {
  struct VECTOR p1; // size=16, offset=0
  struct VECTOR p2; // size=16, offset=16
};
struct _ExOBJECT {
  int time; // size=0, offset=0
  int speed; // size=0, offset=4
  int hscale; // size=0, offset=8
  int rscale; // size=0, offset=12
  enum ExplosionType type; // size=2, offset=16
  struct VECTOR pos; // size=16, offset=20
};
struct BOMB {
  unsigned char flags; // size=0, offset=0
  unsigned char active; // size=0, offset=1
  short rot_speed; // size=0, offset=2
  struct VECTOR position; // size=16, offset=4
  struct VECTOR velocity; // size=16, offset=20
};
struct COLLISION_PACKET {
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
struct _PLAYER {
  long pos[4]; // size=16, offset=0
  int dir; // size=0, offset=16
  struct VECTOR *spoolXZ; // size=16, offset=20
  struct VECTOR cameraPos; // size=16, offset=24
  int cameraDist; // size=0, offset=40
  int maxCameraDist; // size=0, offset=44
  int cameraAngle; // size=0, offset=48
  int headPos; // size=0, offset=52
  int headTarget; // size=0, offset=56
  int viewChange; // size=0, offset=60
  char dying; // size=0, offset=64
  char upsideDown; // size=0, offset=65
  char onGrass; // size=0, offset=66
  char targetCarId; // size=0, offset=67
  char cameraView; // size=0, offset=68
  char headTimer; // size=0, offset=69
  char playerType; // size=0, offset=70
  char worldCentreCarId; // size=0, offset=71
  char playerCarId; // size=0, offset=72
  char cameraCarId; // size=0, offset=73
  char padid; // size=0, offset=74
  char car_is_sounding; // size=0, offset=75
  long camera_vel[3]; // size=12, offset=76
  int snd_cam_ang; // size=0, offset=88
  struct __skidinfo skidding; // size=2, offset=92
  struct __skidinfo wheelnoise; // size=2, offset=94
  struct __horninfo horn; // size=3, offset=96
  int car_sound_timer; // size=0, offset=100
  short revsvol; // size=0, offset=104
  short idlevol; // size=0, offset=106
  struct PEDESTRIAN *pPed; // size=92, offset=108
  int crash_timer; // size=0, offset=112
};
struct XZPAIR {
  int x; // size=0, offset=0
  int z; // size=0, offset=4
};
struct CELL_DATA {
  unsigned short num; // size=0, offset=0
};
struct PACKED_CELL_OBJECT {
  struct USVECTOR_NOPAD pos; // size=6, offset=0
  unsigned short value; // size=0, offset=6
};
struct PAD {
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
  unsigned char *shakeptr; // size=0, offset=64
  unsigned char motors[2]; // size=2, offset=68
  unsigned char shake_type; // size=0, offset=70
  unsigned char vibrate; // size=0, offset=71
};
struct CELL_ITERATOR {
  struct CELL_DATA *pcd; // size=2, offset=0
  struct PACKED_CELL_OBJECT *ppco; // size=8, offset=4
  struct XZPAIR near; // size=8, offset=8
  int use_computed; // size=0, offset=16
};
struct POLY_GT3 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  unsigned char u0; // size=0, offset=12
  unsigned char v0; // size=0, offset=13
  unsigned short clut; // size=0, offset=14
  unsigned char r1; // size=0, offset=16
  unsigned char g1; // size=0, offset=17
  unsigned char b1; // size=0, offset=18
  unsigned char p1; // size=0, offset=19
  short x1; // size=0, offset=20
  short y1; // size=0, offset=22
  unsigned char u1; // size=0, offset=24
  unsigned char v1; // size=0, offset=25
  unsigned short tpage; // size=0, offset=26
  unsigned char r2; // size=0, offset=28
  unsigned char g2; // size=0, offset=29
  unsigned char b2; // size=0, offset=30
  unsigned char p2; // size=0, offset=31
  short x2; // size=0, offset=32
  short y2; // size=0, offset=34
  unsigned char u2; // size=0, offset=36
  unsigned char v2; // size=0, offset=37
  unsigned short pad2; // size=0, offset=38
};
struct POLYFT4LIT {
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
struct TEX_INFO {
  char name[8]; // size=8, offset=0
  char tset; // size=0, offset=8
  char u; // size=0, offset=9
  char v; // size=0, offset=10
  char w; // size=0, offset=11
  char h; // size=0, offset=12
};

struct TEXTURE_LOOKUP {
  struct TEX_INFO *Damage[6]; // size=24, offset=0
};
struct CAR_MODEL {
  int numFT3; // size=0, offset=0
  struct CAR_POLY *pFT3; // size=24, offset=4
  int numGT3; // size=0, offset=8
  struct CAR_POLY *pGT3; // size=24, offset=12
  int numB3; // size=0, offset=16
  struct CAR_POLY *pB3; // size=24, offset=20
  struct SVECTOR *vlist; // size=8, offset=24
  struct SVECTOR *nlist; // size=8, offset=28
};
struct plotCarGlobals {
  unsigned char *primptr; // size=0, offset=0
  long *ot; // size=0, offset=4
  unsigned long intensity; // size=0, offset=8
  unsigned short *pciv_clut; // size=0, offset=12
  unsigned long ShineyTPageASL16; // size=0, offset=16
  unsigned long ShineyClutASL16; // size=0, offset=20
  unsigned char *damageLevel; // size=0, offset=24
  unsigned char *shineyTable; // size=0, offset=28
  int ghost; // size=0, offset=32
};
struct _EXTRA_CIV_DATA {
  int surfInd; // size=0, offset=0
  int distAlongSegment; // size=0, offset=4
  short angle; // size=0, offset=8
  unsigned short ctrlState; // size=0, offset=10
  int thrustState; // size=0, offset=12
  unsigned char palette; // size=0, offset=16
  unsigned char controlFlags; // size=0, offset=17
};
struct CIV_PING {
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

struct COP_DATA {
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
struct FELONY_DATA {
  struct FELONY_DELAY occurrenceDelay[12]; // size=48, offset=0
  struct FELONY_DELAY reoccurrenceDelay[12]; // size=48, offset=48
  struct FELONY_VALUE value[12]; // size=48, offset=96
  int pursuitFelonyScale; // size=0, offset=144
};
struct iVectNT {
  int n; // size=0, offset=0
  int t; // size=0, offset=4
};

struct PLAYBACKCAMERA {
  struct VECTOR_NOPAD position; // size=12, offset=0
  struct SVECTOR angle; // size=8, offset=12
  int FrameCnt; // size=0, offset=20
  short CameraPosvy; // size=0, offset=24
  short gCameraDistance; // size=0, offset=26
  short gCameraMaxDistance; // size=0, offset=28
  short gCameraAngle; // size=0, offset=30
  char cameraview; // size=0, offset=32
  char next; // size=0, offset=33
  char prev; // size=0, offset=34
  char idx; // size=0, offset=35
};
struct CUTSCENE_BUFFER {
  int numResident; // size=0, offset=0
  unsigned char residentCutscenes[4]; // size=4, offset=4
  char *residentPointers[4]; // size=16, offset=8
  char *currentPointer; // size=0, offset=24
  int bytesFree; // size=0, offset=28
  char buffer[8192]; // size=8192, offset=32
};
struct CUTSCENE_INFO {
  unsigned short offset; // size=0, offset=0
  unsigned short size; // size=0, offset=2
};
struct CUTSCENE_HEADER {
  int maxsize; // size=0, offset=0
  struct CUTSCENE_INFO data[15]; // size=60, offset=4
};
struct POLY_GT4 {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  unsigned char u0; // size=0, offset=12
  unsigned char v0; // size=0, offset=13
  unsigned short clut; // size=0, offset=14
  unsigned char r1; // size=0, offset=16
  unsigned char g1; // size=0, offset=17
  unsigned char b1; // size=0, offset=18
  unsigned char p1; // size=0, offset=19
  short x1; // size=0, offset=20
  short y1; // size=0, offset=22
  unsigned char u1; // size=0, offset=24
  unsigned char v1; // size=0, offset=25
  unsigned short tpage; // size=0, offset=26
  unsigned char r2; // size=0, offset=28
  unsigned char g2; // size=0, offset=29
  unsigned char b2; // size=0, offset=30
  unsigned char p2; // size=0, offset=31
  short x2; // size=0, offset=32
  short y2; // size=0, offset=34
  unsigned char u2; // size=0, offset=36
  unsigned char v2; // size=0, offset=37
  unsigned short pad2; // size=0, offset=38
  unsigned char r3; // size=0, offset=40
  unsigned char g3; // size=0, offset=41
  unsigned char b3; // size=0, offset=42
  unsigned char p3; // size=0, offset=43
  short x3; // size=0, offset=44
  short y3; // size=0, offset=46
  unsigned char u3; // size=0, offset=48
  unsigned char v3; // size=0, offset=49
  unsigned short pad3; // size=0, offset=50
};
struct POLYFT4 {
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
struct TPAN {
  unsigned char texture_page; // size=0, offset=0
  unsigned char texture_number; // size=0, offset=1
};

struct SMOKE {
  struct UnpaddedHackVector position; // size=12, offset=0
  struct UnpaddedCharVector drift; // size=3, offset=12
  struct UnpaddedCharVector drift_change; // size=3, offset=15
  struct UnpaddedHackVector final_tail_pos; // size=12, offset=20
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
struct DEBRIS {
  struct VECTOR position; // size=16, offset=0
  struct SVECTOR direction; // size=8, offset=16
  unsigned short life; // size=0, offset=24
  unsigned short flags; // size=0, offset=26
  unsigned short num; // size=0, offset=28
  unsigned short pos; // size=0, offset=30
  struct RGB rgb; // size=4, offset=32
  char step; // size=0, offset=36
  char type; // size=0, offset=37
};
struct LEAF {
  struct VECTOR position; // size=16, offset=0
  struct SVECTOR direction; // size=8, offset=16
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
struct DAMAGED_LAMP {
  struct CELL_OBJECT *cop; // size=16, offset=0
  char damage; // size=0, offset=4
};
struct DAMAGED_OBJECT {
  struct CELL_OBJECT cop; // size=16, offset=0
  char active; // size=0, offset=16
  char damage; // size=0, offset=17
  int rot_speed; // size=0, offset=20
  struct SVECTOR velocity; // size=8, offset=24
  int vx; // size=0, offset=32
};
struct TRI_POINT {
  struct BVECTOR v0; // size=4, offset=0
  struct BVECTOR v1; // size=4, offset=4
  struct BVECTOR v2; // size=4, offset=8
};
struct TRI_POINT_LONG {
  struct VECTOR_NOPAD v0; // size=12, offset=0
  struct VECTOR_NOPAD v1; // size=12, offset=12
  struct VECTOR_NOPAD v2; // size=12, offset=24
};
struct RAIN_TYPE {
  struct VECTOR_NOPAD position; // size=12, offset=0
  struct SVECTOR oldposition; // size=8, offset=12
};
struct LAMP_STREAK {
  struct SXYPAIR light_trails[4]; // size=16, offset=0
  int id; // size=0, offset=16
  short clock; // size=0, offset=20
  char set; // size=0, offset=22
};
struct ROUTE_DATA {
  short type; // size=0, offset=0
  short height; // size=0, offset=2
  short objectAngle; // size=0, offset=4
};
struct DENTUVS {
  char u3; // size=0, offset=0
};
struct HUBCAP {
  int Present[4]; // size=16, offset=0
  struct VECTOR Offset[4]; // size=64, offset=16
  struct MATRIX Orientation; // size=32, offset=80
  struct MATRIX LocalOrientation; // size=32, offset=112
  struct VECTOR Position; // size=16, offset=144
  struct VECTOR Direction; // size=16, offset=160
  float Height; // size=0, offset=176
  int Duration; // size=0, offset=180
};
struct SPRT {
  unsigned long tag; // size=0, offset=0
  unsigned char r0; // size=0, offset=4
  unsigned char g0; // size=0, offset=5
  unsigned char b0; // size=0, offset=6
  unsigned char code; // size=0, offset=7
  short x0; // size=0, offset=8
  short y0; // size=0, offset=10
  unsigned char u0; // size=0, offset=12
  unsigned char v0; // size=0, offset=13
  unsigned short clut; // size=0, offset=14
  short w; // size=0, offset=16
  short h; // size=0, offset=18
};
struct REPLAY_ICON {
  short x; // size=0, offset=0
  short y; // size=0, offset=2
  struct TEXTURE_DETAILS *texture; // size=14, offset=4
  char *TextPtr; // size=0, offset=8
  short tx; // size=0, offset=12
  short ty; // size=0, offset=14
};
struct _pct {
  struct DB *current; // size=128, offset=0
  unsigned short *ptexture_pages[128]; // size=4, offset=4
  unsigned short *ptexture_cluts[128][32]; // size=4, offset=8
  long f4colourTable[32]; // size=128, offset=12
  int *polySizes; // size=0, offset=140
  char *primptr; // size=0, offset=144
  unsigned long *ot; // size=0, offset=148
  unsigned long clut; // size=0, offset=152
  unsigned long tpage; // size=0, offset=156
  unsigned long colour; // size=0, offset=160
  int flags; // size=0, offset=164
  struct SVECTOR *verts; // size=8, offset=168
  unsigned long lastTexInfo; // size=0, offset=172
  int scribble[8]; // size=32, offset=176
  int model; // size=0, offset=208
};
struct MATRIX2 {
  short m[3][3]; // size=18, offset=0
  short computed; // size=0, offset=18
  char null[12]; // size=12, offset=20
};
struct Spool {
  unsigned short offset; // size=0, offset=0
  unsigned char connected_areas[2]; // size=2, offset=2
  unsigned char pvs_size; // size=0, offset=4
  unsigned char cell_data_size[3]; // size=3, offset=5
  unsigned char super_region; // size=0, offset=8
  unsigned char num_connected_areas; // size=0, offset=9
  unsigned char roadm_size; // size=0, offset=10
  unsigned char roadh_size; // size=0, offset=11
};
struct PL_POLYFT4 {
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
struct _pct {
  struct DB *current; // size=0, offset=0
  unsigned short *ptexture_pages[128]; // size=4, offset=4
  unsigned short *ptexture_cluts[128][32]; // size=4, offset=8
  long f4colourTable[32]; // size=128, offset=12
  int *polySizes; // size=0, offset=140
  char *primptr; // size=0, offset=144
  unsigned long *ot; // size=0, offset=148
  unsigned long clut; // size=0, offset=152
  unsigned long tpage; // size=0, offset=156
  unsigned long colour; // size=0, offset=160
  int flags; // size=0, offset=164
  struct SVECTOR *verts; // size=8, offset=168
  unsigned long lastTexInfo; // size=0, offset=172
  int scribble[8]; // size=32, offset=176
  int model; // size=0, offset=208
};
struct _pct {
  struct DB *current; // size=0, offset=0
  unsigned short *ptexture_pages[128]; // size=4, offset=4
  unsigned short *ptexture_cluts[128][32]; // size=4, offset=8
  long f4colourTable[32]; // size=128, offset=12
  int *polySizes; // size=0, offset=140
  char *primptr; // size=0, offset=144
  unsigned long *ot; // size=0, offset=148
  unsigned long clut; // size=0, offset=152
  unsigned long tpage; // size=0, offset=156
  unsigned long colour; // size=0, offset=160
  int flags; // size=0, offset=164
  struct SVECTOR *verts; // size=8, offset=168
  unsigned long lastTexInfo; // size=0, offset=172
  int scribble[8]; // size=32, offset=176
  int model; // size=0, offset=208
};
struct MVERTEX {
  short vx; // size=0, offset=0
  short vy; // size=0, offset=2
  short vz; // size=0, offset=4
  unsigned short uv; // size=0, offset=6
};

struct VERTEX {
  struct DVECTOR coord; // size=4, offset=0
  struct UV_INFO uv_coord; // size=2, offset=4
  unsigned char pad[2]; // size=2, offset=6
};
struct TRAILBLAZER_DATA {
  int x; // size=0, offset=0
  int z; // size=0, offset=4
  short y; // size=0, offset=8
  short rot; // size=0, offset=10
};
struct SMASHED_CONE {
  char cone; // size=0, offset=0
  unsigned char active : 7; // offset=1.0
  unsigned char side : 1; // offset=1.7
  short rot_speed; // size=0, offset=2
  struct VECTOR velocity; // size=16, offset=4
};
struct POLYCOORD {
  short x; // size=0, offset=0
  short y; // size=0, offset=2
  short u; // size=0, offset=4
  short v; // size=0, offset=6
  short w; // size=0, offset=8
  short h; // size=0, offset=10
};
struct FixedEvent {
  struct VECTOR position; // size=16, offset=0
  short rotation; // size=0, offset=16
  short active; // size=0, offset=18
  unsigned short initialRotation; // size=0, offset=20
  unsigned short finalRotation; // size=0, offset=22
  unsigned short minSpeed; // size=0, offset=24
  unsigned short maxSpeed; // size=0, offset=26
  short flags; // size=0, offset=28
  short radius; // size=0, offset=30
  int model; // size=0, offset=32
  struct _EVENT *next; // size=40, offset=36
  char *modelName; // size=0, offset=40
};
struct EventGlobal {
  int camera; // size=0, offset=0
  int draw; // size=0, offset=4
  struct _EVENT **track; // size=40, offset=8
  struct _EVENT *cameraEvent; // size=40, offset=12
};

struct MissionTrain {
  struct _EVENT *engine; // size=40, offset=0
  int *node; // size=0, offset=4
  int cornerSpeed; // size=0, offset=8
  int initialStraightSpeed; // size=0, offset=12
  int finalStraightSpeed; // size=0, offset=16
  int start; // size=0, offset=20
  int startDir; // size=0, offset=24
};
struct Foam {
  struct MODEL *model; // size=36, offset=0
  int rotate; // size=0, offset=4
};
struct EventCarriage {
  short rotation; // size=0, offset=0
  short vel; // size=0, offset=2
};
struct MultiCar {
  struct _EVENT *event; // size=40, offset=0
  int count; // size=0, offset=4
};
struct Helicopter {
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
struct Detonator {
  int timer; // size=0, offset=0
  int count; // size=0, offset=4
};
struct CameraDelay {
  int delay; // size=0, offset=0
  int type; // size=0, offset=4
};
struct EventCamera {
  struct VECTOR position; // size=16, offset=0
  short yAng; // size=0, offset=16
  struct MATRIX matrix; // size=32, offset=20
  int rotate; // size=0, offset=52
};
struct MULTICAR_DATA {
  int x; // size=0, offset=0
  int z; // size=0, offset=4
  unsigned char palette; // size=0, offset=8
  unsigned char model; // size=0, offset=9
  short rot; // size=0, offset=10
};
struct RENDER_ARG {
  unsigned char render; // size=0, offset=0
  unsigned char credits; // size=0, offset=1
  unsigned short recap; // size=0, offset=2
};
struct RENDER_ARGS {
  unsigned char nRenders; // size=0, offset=0
  unsigned char subtitle; // size=0, offset=1
  char screenx; // size=0, offset=2
  char screeny; // size=0, offset=3
  struct RENDER_ARG Args[4]; // size=16, offset=4
};
struct __envsound {
  unsigned char type; // size=0, offset=0
  unsigned char flags; // size=0, offset=1
  struct VECTOR pos; // size=16, offset=4
  struct VECTOR pos2; // size=16, offset=20
  int bank; // size=0, offset=36
  int sample; // size=0, offset=40
  int vol; // size=0, offset=44
};
struct __envsoundtags {
  int frame_cnt; // size=0, offset=0
  int func_cnt; // size=0, offset=4
  int num_envsnds; // size=0, offset=8
  int envsnd_cnt; // size=0, offset=12
};
struct __envsoundinfo {
  struct VECTOR eff_pos[4]; // size=64, offset=0
  struct VECTOR cam_pos; // size=16, offset=64
  float g[4]; // size=16, offset=80
  int this[4]; // size=16, offset=96
  int playing_sound[4]; // size=16, offset=112
  int chan[4]; // size=16, offset=128
  unsigned long flags; // size=0, offset=144
};
struct SPEECH_QUEUE {
  char allowed; // size=0, offset=0
  char chan; // size=0, offset=1
  char is_playing; // size=0, offset=2
  int count; // size=0, offset=4
  char reverb; // size=0, offset=8
  int slot[7]; // size=28, offset=12
};
struct __othercarsound {
  int car; // size=0, offset=0
  int chan; // size=0, offset=4
  char in_use; // size=0, offset=8
  char stopped; // size=0, offset=9
  char idle; // size=0, offset=10
};
struct __tunnelinfo {
  char num_tunnels; // size=0, offset=0
  char tunnel_cnt; // size=0, offset=1
  struct __tunnelcoords coords[29]; // size=928, offset=4
};
struct __bitfield64 {
  long h; // size=0, offset=0
  long l; // size=0, offset=4
};
struct XMCHANNEL {
  unsigned short Octave; // size=0, offset=0
  short LVol; // size=0, offset=2
  short RVol; // size=0, offset=4
  short OldLVol; // size=0, offset=6
  short OldRVol; // size=0, offset=8
  unsigned short OldPeriod; // size=0, offset=10
  unsigned char OldSample; // size=0, offset=12
  unsigned long OldSOff; // size=0, offset=16
  unsigned long SOffset; // size=0, offset=20
  unsigned char nothing; // size=0, offset=24
  unsigned char ChDead; // size=0, offset=25
  unsigned char panenvflg; // size=0, offset=26
  unsigned char panenvpts; // size=0, offset=27
  unsigned char panenvsus; // size=0, offset=28
  unsigned char panenvbeg; // size=0, offset=29
  unsigned char panenvend; // size=0, offset=30
  short panenvp; // size=0, offset=32
  unsigned short panenva; // size=0, offset=34
  unsigned short panenvb; // size=0, offset=36
  unsigned short keyoffspd; // size=0, offset=38
  unsigned char envflg; // size=0, offset=40
  unsigned char envpts; // size=0, offset=41
  unsigned char envsus; // size=0, offset=42
  unsigned char envbeg; // size=0, offset=43
  unsigned char envend; // size=0, offset=44
  short envp; // size=0, offset=46
  unsigned short enva; // size=0, offset=48
  unsigned short envb; // size=0, offset=50
  unsigned char ins; // size=0, offset=52
  unsigned char vol; // size=0, offset=53
  unsigned char dat; // size=0, offset=54
  unsigned char datold; // size=0, offset=55
  unsigned char eff; // size=0, offset=56
  unsigned char not; // size=0, offset=57
  unsigned char oldvslide; // size=0, offset=58
  unsigned char oldfvslide; // size=0, offset=59
  unsigned char oldfslide; // size=0, offset=60
  short fadevol; // size=0, offset=62
  unsigned char keyon; // size=0, offset=64
  unsigned char kick; // size=0, offset=65
  unsigned char sample; // size=0, offset=66
  short handle; // size=0, offset=68
  unsigned long start; // size=0, offset=72
  unsigned char panning; // size=0, offset=76
  unsigned char pansspd; // size=0, offset=77
  char volume; // size=0, offset=78
  unsigned short period; // size=0, offset=80
  unsigned short SPUPitch; // size=0, offset=82
  char transpose; // size=0, offset=84
  unsigned char note; // size=0, offset=85
  short ownper; // size=0, offset=86
  short ownvol; // size=0, offset=88
  short UserVol; // size=0, offset=90
  char retrig; // size=0, offset=92
  unsigned short c2spd; // size=0, offset=94
  char tmpvolume; // size=0, offset=96
  unsigned short tmpperiod; // size=0, offset=98
  unsigned short wantedperiod; // size=0, offset=100
  unsigned short slidespeed; // size=0, offset=102
  unsigned short portspeed; // size=0, offset=104
  unsigned char s3mtremor; // size=0, offset=106
  unsigned char s3mvolslide; // size=0, offset=107
  unsigned char s3mrtgspeed; // size=0, offset=108
  unsigned char s3mrtgslide; // size=0, offset=109
  unsigned char glissando; // size=0, offset=110
  unsigned char wavecontrol; // size=0, offset=111
  char vibpos; // size=0, offset=112
  unsigned char vibspd; // size=0, offset=113
  unsigned char vibdepth; // size=0, offset=114
  char trmpos; // size=0, offset=115
  unsigned char trmspd; // size=0, offset=116
  unsigned char trmdepth; // size=0, offset=117
  unsigned char SPUChannel; // size=0, offset=118
  unsigned char Dolby; // size=0, offset=119
};
struct GEAR_DESC {
  int lowidl_ws; // size=0, offset=0
  int low_ws; // size=0, offset=4
  int hi_ws; // size=0, offset=8
  int ratio_ac; // size=0, offset=12
  int ratio_id; // size=0, offset=16
};
struct PSXSCREEN {
  char index; // size=0, offset=0
  unsigned char numButtons; // size=0, offset=1
  char userFunctionNum; // size=0, offset=2
  struct PSXBUTTON buttons[8]; // size=480, offset=4
};
struct MISSION_STEP {
  unsigned char flags : 3; // offset=0.0
  unsigned char recap : 5; // offset=0.3
  unsigned char data : 7; // offset=1.0
  unsigned char disc : 1; // offset=1.7
};
struct BOUND_BOX {
  int x0; // size=0, offset=0
  int y0; // size=0, offset=4
  int z0; // size=0, offset=8
  int x1; // size=0, offset=12
  int y1; // size=0, offset=16
  int z1; // size=0, offset=20
};
struct _HANDLING_TYPE {
  char frictionScaleRatio; // size=0, offset=0
  char aggressiveBraking; // size=0, offset=1
  char fourWheelDrive; // size=0, offset=2
  char autoBrakeOn; // size=0, offset=3
};
struct CHEATS {
  int RearWheelSteer; // size=0, offset=0
  int MiniCars; // size=0, offset=4
  int Stilts; // size=0, offset=8
  int LowGravity; // size=0, offset=12
  int Australia; // size=0, offset=16
  int MagicMirror; // size=0, offset=20
};

struct BOXINFO {
  struct VECTOR vel; // size=16, offset=0
  struct VECTOR pos; // size=16, offset=16
  int sf; // size=0, offset=32
  int xs; // size=0, offset=36
  int zs; // size=0, offset=40
  int w; // size=0, offset=44
  int h; // size=0, offset=48
  int zb; // size=0, offset=52
  int ypos; // size=0, offset=56
};
struct MAP_DATA {
  struct _CAR_DATA *cp; // size=0, offset=0
  struct VECTOR *base; // size=16, offset=4
  struct VECTOR *pos; // size=16, offset=8
  struct VECTOR *vel; // size=16, offset=12
  struct VECTOR *size; // size=16, offset=16
  int intention; // size=0, offset=20
  int *map; // size=0, offset=24
  int *local; // size=0, offset=28
};
struct GAME_SAVE_HEADER {
  unsigned long magic; // size=0, offset=0
  unsigned char gMissionLadderPos; // size=0, offset=4
  unsigned char pad1; // size=0, offset=5
  unsigned char pad2; // size=0, offset=6
  unsigned char pad3; // size=0, offset=7
  struct MISSION_DATA SavedData; // size=228, offset=8
  int reserved[8]; // size=32, offset=236
};
struct CONFIG_SAVE_HEADER {
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
struct OUT_CELL_FILE_HEADER {
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

struct XYWH {
  short x; // size=0, offset=0
  short y; // size=0, offset=2
  short w; // size=0, offset=4
  short h; // size=0, offset=6
};

struct MENU_HEADER {
  char *Title; // size=0, offset=0
  struct XYWH Bound; // size=8, offset=4
  unsigned char NumItems; // size=0, offset=12
  struct MENU_ITEM *MenuItems; // size=20, offset=16
};
struct MENU_ITEM {
  char *Text; // size=0, offset=0
  unsigned char Type; // size=0, offset=4
  unsigned char Justify; // size=0, offset=5
  void (*func)(); // size=0, offset=8
  enum EXIT_VALUE ExitValue; // size=1, offset=12
  struct MENU_HEADER *SubMenu; // size=0, offset=16
};

struct AREA_LOAD_INFO {
  int xoffset; // size=0, offset=0
  int zoffset; // size=0, offset=4
};

struct ROAD_MAP_LUMP_DATA {
  int width; // size=0, offset=0
  int height; // size=0, offset=4
  int unitXMid; // size=0, offset=8
  int unitZMid; // size=0, offset=12
};
struct __io {
  char in; // size=0, offset=0
  char out; // size=0, offset=1
};
struct __xa_request {
  short delay; // size=0, offset=0
  char bank; // size=0, offset=2
  char track; // size=0, offset=3
  char mission; // size=0, offset=4
  char cutscene; // size=0, offset=5
};
struct _MISSION {
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
struct _ROUTE_INFO {
  int nJunctions; // size=0, offset=0
  char data[1000][4]; // size=4000, offset=4
  struct LEAD_PARAMETERS parameters; // size=64, offset=4004
};
struct MR_MISSION {
  int active; // size=0, offset=0
  int gameover_delay; // size=0, offset=4
  enum PAUSEMODE gameover_mode; // size=1, offset=8
  short message_timer[2]; // size=4, offset=10
  short message_priority[2]; // size=4, offset=14
  char *message_string[2]; // size=8, offset=20
  struct MR_TIMER timer[2]; // size=24, offset=28
  struct _TARGET *CarTarget; // size=64, offset=52
  struct _TARGET *ChaseTarget; // size=64, offset=56
  int PhantomCarId; // size=0, offset=60
  int ChaseHitDelay; // size=0, offset=64
  char *StealMessage; // size=0, offset=68
};
struct STOPCOPS {
  struct VECTOR_NOPAD pos; // size=12, offset=0
  int radius; // size=0, offset=12
};
struct MR_THREAD {
  unsigned char active; // size=0, offset=0
  unsigned char player; // size=0, offset=1
  unsigned long *initial_sp; // size=0, offset=4
  unsigned long *pc; // size=0, offset=8
  unsigned long *sp; // size=0, offset=12
};
struct POLYFT3 {
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
struct BONE {
  enum LIMBS id; // size=1, offset=0
  struct BONE *pParent; // size=68, offset=4
  char numChildren; // size=0, offset=8
  struct BONE *pChildren[3]; // size=12, offset=12
  struct SVECTOR_NOPAD *pvOrigPos; // size=6, offset=24
  struct SVECTOR *pvRotation; // size=8, offset=28
  struct VECTOR vOffset; // size=16, offset=32
  struct VECTOR vCurrPos; // size=16, offset=48
  struct MODEL **pModel; // size=36, offset=64
};
struct PED_DATA {
  char cWidth; // size=0, offset=0
  unsigned char cAdj; // size=0, offset=1
  struct TEXTURE_DETAILS *ptd; // size=14, offset=4
  enum TEXTURE_PALS texPal; // size=1, offset=8
};
struct tRay {
  long org[4]; // size=16, offset=0
  long dir[4]; // size=16, offset=16
};
struct tRange {
  int lower; // size=0, offset=0
  int upper; // size=0, offset=4
};
struct tAABB {
  struct tRange slab[3]; // size=24, offset=0
};
struct PADRAW {
  unsigned char status; // size=0, offset=0
  unsigned char id; // size=0, offset=1
  unsigned char buttons[2]; // size=2, offset=2
  unsigned char analog[4]; // size=4, offset=4
};
struct DUPLICATION {
  char *buffer; // size=0, offset=0
  int size; // size=0, offset=4
};
struct tNode {
  int vx; // size=0, offset=0
  int vy; // size=0, offset=4
  int vz; // size=0, offset=8
  unsigned short dist; // size=0, offset=12
  unsigned short ptoey; // size=0, offset=14
};
struct tNodeDir {
  short dx; // size=0, offset=0
  short dz; // size=0, offset=2
};

struct PLAYER_SCORE {
  int time; // size=0, offset=0
  int P2time; // size=0, offset=4
  short items; // size=0, offset=8
  short P2items; // size=0, offset=10
  char name[6]; // size=6, offset=12
};
struct SEATED_PEDESTRIANS {
  int x; // size=0, offset=0
  int z; // size=0, offset=4
  short rotation; // size=0, offset=8
  char index; // size=0, offset=10
  char pad; // size=0, offset=11
};
struct CAR_COLLISION_BOX {
  int min_x; // size=0, offset=0
  int max_x; // size=0, offset=4
  int min_z; // size=0, offset=8
  int max_z; // size=0, offset=12
};
struct PEDESTRIAN_ROADS {
  short pos; // size=0, offset=0
  short north; // size=0, offset=2
  short south; // size=0, offset=4
  short east; // size=0, offset=6
  short west; // size=0, offset=8
};
struct OUT_FONTINFO {
  unsigned char x; // size=0, offset=0
  unsigned char y; // size=0, offset=1
  char offx; // size=0, offset=2
  char offy; // size=0, offset=3
  unsigned char width; // size=0, offset=4
  unsigned char height; // size=0, offset=5
  unsigned short pad; // size=0, offset=6
};
struct FONT_DIGIT {
  char xOffset; // size=0, offset=0
  char width; // size=0, offset=1
};
struct TEXINF {
  unsigned short id; // size=0, offset=0
  unsigned short nameoffset; // size=0, offset=2
  unsigned char x; // size=0, offset=4
  unsigned char y; // size=0, offset=5
  unsigned char width; // size=0, offset=6
  unsigned char height; // size=0, offset=7
};
struct SHADOWHDR {
  unsigned long num_common_verts; // size=0, offset=0
  unsigned short num_verts_total; // size=0, offset=4
  unsigned short num_polys_total; // size=0, offset=6
  unsigned short vert_offsets[4]; // size=8, offset=8
  unsigned short nverts[4]; // size=8, offset=16
  unsigned short npolys[4]; // size=8, offset=24
  unsigned long *poly_block[4]; // size=16, offset=32
  struct SVECTOR *vertices; // size=8, offset=48
};
struct TYRE_TRACK {
  char type; // size=0, offset=0
  char shade; // size=0, offset=1
  char shade_type; // size=0, offset=2
  char surface; // size=0, offset=3
  struct SVECTOR_NOPAD p1; // size=6, offset=4
  struct SVECTOR_NOPAD p2; // size=6, offset=10
  struct SVECTOR_NOPAD p3; // size=6, offset=16
  struct SVECTOR_NOPAD p4; // size=6, offset=22
};
struct S_XYZ {
  short x; // size=0, offset=0
  short y; // size=0, offset=2
  short z; // size=0, offset=4
};
struct DR_MOVE {
  unsigned long tag; // size=0, offset=0
  unsigned long code[5]; // size=20, offset=4
};
struct FLAREREC {
  struct RGB16 transparency; // size=8, offset=0
  char size; // size=0, offset=8
  short gapmod; // size=0, offset=10
};
struct SpuReverbAttr {
  unsigned long mask; // size=0, offset=0
  long mode; // size=0, offset=4
  struct SpuVolume depth; // size=4, offset=8
  long delay; // size=0, offset=12
  long feedback; // size=0, offset=16
};
struct SpuCommonAttr {
  unsigned long mask; // size=0, offset=0
  struct SpuVolume mvol; // size=4, offset=4
  struct SpuVolume mvolmode; // size=4, offset=8
  struct SpuVolume mvolx; // size=4, offset=12
  struct SpuExtAttr cd; // size=12, offset=16
  struct SpuExtAttr ext; // size=12, offset=28
};
struct __LSBDinfo {
  int addr; // size=0, offset=0
  int memtop; // size=0, offset=4
  int count[7]; // size=28, offset=8
  int bnktop[7]; // size=28, offset=36
  int append; // size=0, offset=64
};
struct CHANNEL_DATA {
  struct SpuVoiceAttr attr; // size=64, offset=0
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
  struct VECTOR *srcposition; // size=16, offset=96
  struct VECTOR position; // size=16, offset=100
  long *srcvelocity; // size=0, offset=116
};
struct SAMPLE_DATA {
  unsigned long address; // size=0, offset=0
  unsigned long length; // size=0, offset=4
  unsigned long loop; // size=0, offset=8
  unsigned long samplerate; // size=0, offset=12
};

struct __pauseinfo {
  unsigned short pitch[16]; // size=32, offset=0
  unsigned short voll[16]; // size=32, offset=32
  unsigned short volr[16]; // size=32, offset=64
  unsigned short max; // size=0, offset=96
  unsigned short lev; // size=0, offset=98
};
struct SPOOLQ {
  unsigned char type; // size=0, offset=0
  unsigned char data; // size=0, offset=1
  unsigned short nsectors; // size=0, offset=2
  unsigned long sector; // size=0, offset=4
  char *addr; // size=0, offset=8
  void (*func)(); // size=0, offset=12
};
struct SPL_REGIONINFO {
  unsigned short region_to_unpack; // size=0, offset=0
  unsigned short target_barrel_region; // size=0, offset=2
  int nsectors; // size=0, offset=4
  char *cell_addr; // size=0, offset=8
  char *roadm_addr; // size=0, offset=12
};
struct AreaDataStr {
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

struct CdlFILE {
  struct CdlLOC pos; // size=4, offset=0
  unsigned long size; // size=0, offset=4
  char name[16]; // size=16, offset=8
};
struct DRAW_MODE {
  short x1; // size=0, offset=0
  short y1; // size=0, offset=2
  short x2; // size=0, offset=4
  short y2; // size=0, offset=6
  short width; // size=0, offset=8
  short height; // size=0, offset=10
  short framex; // size=0, offset=12
  short framey; // size=0, offset=14
};
struct TARGET_ARROW_MODEL {
  struct SVECTOR *pVerts; // size=8, offset=0
  char *pTris; // size=0, offset=4
  char numTris; // size=0, offset=8
};
struct TP {
  unsigned long flags; // size=0, offset=0
  unsigned long offset; // size=0, offset=4
};
struct CAR_LOCALS {
  long vel[4]; // size=16, offset=0
  long avel[4]; // size=16, offset=16
  int extraangulardamping; // size=0, offset=32
  int aggressive; // size=0, offset=36
};
struct CdlFILTER {
  unsigned char file; // size=0, offset=0
  unsigned char chan; // size=0, offset=1
  unsigned short pad; // size=0, offset=2
};
struct XA_TRACK {
  int start; // size=0, offset=0
  int end; // size=0, offset=4
};
struct XM_HeaderInfo {
  unsigned short BPM; // size=0, offset=0
  unsigned short Speed; // size=0, offset=2
};
struct XM_VABInfo {
  unsigned char *Address; // size=0, offset=0
  unsigned long Size; // size=0, offset=4
};
struct XM_Feedback {
  unsigned char Volume; // size=0, offset=0
  short Panning; // size=0, offset=2
  int CurrentStart; // size=0, offset=4
  short PlayNext; // size=0, offset=8
  unsigned short SongLength; // size=0, offset=10
  unsigned char Status; // size=0, offset=12
  unsigned short PatternPos; // size=0, offset=14
  short SongPos; // size=0, offset=16
  unsigned short CurrentPattern; // size=0, offset=18
  unsigned short SongSpeed; // size=0, offset=20
  unsigned short SongBPM; // size=0, offset=22
  int SongLoop; // size=0, offset=24
  int ActiveVoices; // size=0, offset=28
};
struct XMHEADER {
  unsigned short version; // size=0, offset=0
  unsigned short songlength; // size=0, offset=2
  unsigned short restart; // size=0, offset=4
  unsigned short numchn; // size=0, offset=6
  unsigned short numpat; // size=0, offset=8
  unsigned short numins; // size=0, offset=10
  unsigned short flags; // size=0, offset=12
  unsigned short tempo; // size=0, offset=14
  unsigned short bpm; // size=0, offset=16
  unsigned short XMChannels; // size=0, offset=18
  unsigned short XMPSXChannels; // size=0, offset=20
  unsigned long *JAP_PAT_ADDR[256]; // size=1024, offset=24
  unsigned long *JAP_PAT_ADDR2[256]; // size=1024, offset=1048
  unsigned long *JAP_InstrumentOffset[128]; // size=512, offset=2072
  unsigned long *JAP_SampAddr[128]; // size=512, offset=2584
  unsigned long *JAP_SampHdrAddr[128]; // size=512, offset=3096
  unsigned char jorders[256]; // size=256, offset=3608
  int S3MPanning; // size=0, offset=3864
};
struct XMSONG {
  unsigned char Status; // size=0, offset=0
  int HeaderNum; // size=0, offset=4
  int CurPos; // size=0, offset=8
  unsigned short reppos; // size=0, offset=12
  unsigned short repcnt; // size=0, offset=14
  unsigned short vbtick; // size=0, offset=16
  unsigned short patbrk; // size=0, offset=18
  unsigned char patdly; // size=0, offset=20
  unsigned char patdly2; // size=0, offset=21
  unsigned short numrow; // size=0, offset=22
  short posjmp; // size=0, offset=24
  unsigned short PatternPos; // size=0, offset=26
  short SongPos; // size=0, offset=28
  unsigned short CurrentPattern; // size=0, offset=30
  unsigned short SongSpeed; // size=0, offset=32
  unsigned short SongBPM; // size=0, offset=34
  int SongLoop; // size=0, offset=36
  unsigned char SongVolume; // size=0, offset=40
  unsigned char MasterVolume; // size=0, offset=41
  int XMActiveVoices; // size=0, offset=44
  int NotAmiga; // size=0, offset=48
  unsigned char XMPlay; // size=0, offset=52
  int FirstCh; // size=0, offset=56
  int JBPM; // size=0, offset=60
  int PCounter; // size=0, offset=64
  unsigned short PatSize; // size=0, offset=68
  unsigned long *PatAdr; // size=0, offset=72
  unsigned long *PatAdr2; // size=0, offset=76
  int PlayMask; // size=0, offset=80
  int SFXNum; // size=0, offset=84
  struct XMCHANNEL XM_Chnl[24]; // size=2880, offset=88
  int JUp; // size=0, offset=2968
  short PlayNext; // size=0, offset=2972
  short BPlayNext; // size=0, offset=2974
  short BPlayFlag; // size=0, offset=2976
  int CurrentStart; // size=0, offset=2980
  unsigned char VabID; // size=0, offset=2984
  short UserPan; // size=0, offset=2986
  unsigned char MaxChans; // size=0, offset=2988
};

struct FE_CHARDATA {
  unsigned char u; // size=0, offset=0
  unsigned char v; // size=0, offset=1
  unsigned char w; // size=0, offset=2
  unsigned char h; // size=0, offset=3
};
struct FE_FONT {
  int NumFonts; // size=0, offset=0
  struct FE_CHARDATA CharInfo[256]; // size=1024, offset=4
};
struct SCREEN_LIMITS {
  short minx; // size=0, offset=0
  short miny; // size=0, offset=2
  short maxx; // size=0, offset=4
  short maxy; // size=0, offset=6
};
struct BOTCH {
  int missNum; // size=0, offset=0
  char **name; // size=0, offset=4
};
struct FILEFORMAT {
  char blockSize; // size=0, offset=0
  char asciiTitle[32]; // size=32, offset=1
  short kanjiTitle[32]; // size=64, offset=34
  char sonyProductCode[13]; // size=13, offset=98
  char blockType; // size=0, offset=111
  short blockIconClut[16]; // size=32, offset=112
  int blockIconData[32]; // size=128, offset=144
  int sliceByteSize; // size=0, offset=272
  long *sliceIconTimPtrs[16]; // size=64, offset=276
};
struct SLICE {
  char title[20]; // size=20, offset=0
  char sliceIconRefs[3]; // size=3, offset=20
  char *sliceData; // size=0, offset=24
};
struct MouseData {
  unsigned short buttons; // size=0, offset=0
  char xOffset; // size=0, offset=2
  char yOffset; // size=0, offset=3
};
struct NegconData {
  unsigned short digitalButtons; // size=0, offset=0
  char centralTwist; // size=0, offset=2
  char buttonI; // size=0, offset=3
  char buttonII; // size=0, offset=4
  char topLeft; // size=0, offset=5
};
struct AnalogjoyData {
  unsigned short digitalButtons; // size=0, offset=0
  unsigned char right_x; // size=0, offset=2
  unsigned char right_y; // size=0, offset=3
  unsigned char left_x; // size=0, offset=4
  unsigned char left_y; // size=0, offset=5
};
struct TapCtrllerData {
  unsigned char transStatus; // size=0, offset=0
  unsigned char dataFormat; // size=0, offset=1
  union data{
    unsigned short pad; // size=0, offset=0
    struct NegconData negcon; // size=6, offset=0
    struct MouseData mouse; // size=4, offset=0
  }; // size=6, offset=2
};
struct MultiTapData {
  struct TapCtrllerData ctrllers[4]; // size=32, offset=0
};
struct _CARD {
  char Magic[2]; // size=2, offset=0
  char Type; // size=0, offset=2
  char BlockEntry; // size=0, offset=3
  char Title[64]; // size=64, offset=4
  char reserve[28]; // size=28, offset=68
  char Clut[32]; // size=32, offset=96
  char Icon[3][128]; // size=384, offset=128
};
struct TIMSTRUCT {
  unsigned short clut; // size=0, offset=0
  unsigned short tpage; // size=0, offset=2
  unsigned short x; // size=0, offset=4
  unsigned short y; // size=0, offset=6
  unsigned short w; // size=0, offset=8
  unsigned short h; // size=0, offset=10
};
struct FONTTABSTRUCT {
  struct TIMSTRUCT timStruct; // size=12, offset=0
  short width; // size=0, offset=12
  short height; // size=0, offset=14
};
struct KANJILOOKUP {
  short sjisCode; // size=0, offset=0
  unsigned int used; // size=0, offset=4
  struct TIMSTRUCT timStruct; // size=12, offset=8
};
struct SLICEHEADER {
  int size; // size=0, offset=0
  char title[20]; // size=20, offset=4
  char iconRef[3]; // size=3, offset=24
  char used; // size=0, offset=27
  short checksum; // size=0, offset=28
  short pad; // size=0, offset=30
};
struct BLOCKINFO {
  unsigned int infoOK; // size=0, offset=0
  int id; // size=0, offset=4
  int size; // size=0, offset=8
  int freeBytes; // size=0, offset=12
  struct DIRENTRY dirEntry; // size=40, offset=16
  struct _CARD header; // size=512, offset=56
  struct TIMSTRUCT iconTim; // size=12, offset=568
  unsigned int gremBlock; // size=0, offset=580
  int sliceCount; // size=0, offset=584
  int usedSlices; // size=0, offset=588
  struct SLICEHEADER sliceHeader[16]; // size=512, offset=592
};
struct CARDINFO {
  int usedBlocks; // size=0, offset=0
  struct BLOCKINFO blockInfo[15]; // size=16560, offset=4
  unsigned int dirOK; // size=0, offset=16564
  unsigned int infoOK; // size=0, offset=16568
};
struct MCSLOT {
  struct CARDINFO m_cardInfo; // size=16572, offset=0
  int m_port; // size=0, offset=16572
  int m_card; // size=0, offset=16576
  int m_chan; // size=0, offset=16580
  char m_device[6]; // size=6, offset=16584
  int m_blocksRead; // size=0, offset=16592
  int m_readFilePtr; // size=0, offset=16596
  int m_readBytes; // size=0, offset=16600
  int m_fromReadBytes; // size=0, offset=16604
  int m_toReadBytes; // size=0, offset=16608
  int m_writeFilePtr; // size=0, offset=16612
  int m_writeBytes; // size=0, offset=16616
  int m_fromWriteBytes; // size=0, offset=16620
  int m_toWriteBytes; // size=0, offset=16624
  int m_iconX; // size=0, offset=16628
  int m_iconY; // size=0, offset=16632
  int m_clutX; // size=0, offset=16636
  int m_clutY; // size=0, offset=16640
  unsigned int m_doCheckSum; // size=0, offset=16644
  short m_checkSumWork; // size=0, offset=16648
  short m_checkSum; // size=0, offset=16650
};
struct PAD {
  struct MCSLOT m_mcSlot0; // size=16652, offset=0
  struct MCSLOT m_mcSlot1; // size=16652, offset=16652
  int m_mouseX; // size=0, offset=33304
  int m_mouseY; // size=0, offset=33308
  int m_scanPort; // size=0, offset=33312
  unsigned int m_cardChanged[2]; // size=8, offset=33316
  unsigned int m_bControllerChanged; // size=0, offset=33324
  unsigned int m_bMouseTested; // size=0, offset=33328
  unsigned int m_bUsingMouse; // size=0, offset=33332
  unsigned int m_bUsingNegCon; // size=0, offset=33336
  unsigned int m_bControllerInserted; // size=0, offset=33340
  int m_nLastControllerType; // size=0, offset=33344
  char slotString[3]; // size=3, offset=33348
  struct MCSLOT *m_slotObjPtrs[2]; // size=8, offset=33352
  int m_slotObjPorts[2]; // size=8, offset=33360
  int m_currSlotObj; // size=0, offset=33368
  int m_portStatus[8]; // size=32, offset=33372
};
struct POINT {
  int x; // size=0, offset=0
  int y; // size=0, offset=4
};
struct PAD {
  struct MCSLOT m_mcSlot0; // size=16652, offset=0
  struct MCSLOT m_mcSlot1; // size=16652, offset=16652
  int m_mouseX; // size=0, offset=33304
  int m_mouseY; // size=0, offset=33308
  int m_scanPort; // size=0, offset=33312
  unsigned int m_cardChanged[2]; // size=8, offset=33316
  unsigned int m_bControllerChanged; // size=0, offset=33324
  unsigned int m_bMouseTested; // size=0, offset=33328
  unsigned int m_bUsingMouse; // size=0, offset=33332
  unsigned int m_bUsingNegCon; // size=0, offset=33336
  unsigned int m_bControllerInserted; // size=0, offset=33340
  int m_nLastControllerType; // size=0, offset=33344
  char slotString[3]; // size=3, offset=33348
  struct MCSLOT *m_slotObjPtrs[2]; // size=8, offset=33352
  int m_slotObjPorts[2]; // size=8, offset=33360
  int m_currSlotObj; // size=0, offset=33368
  int m_portStatus[8]; // size=32, offset=33372
};
struct DISPMAN {
  unsigned int m_displayingMessage; // size=0, offset=0
  int m_language; // size=0, offset=4
  char m_textBuffer[256]; // size=256, offset=8
  struct DR_AREA m_sliceClipArea; // size=12, offset=264
  struct DR_AREA m_screenClipArea; // size=12, offset=276
  struct RECT m_backRect[7]; // size=56, offset=288
  struct RECT m_srcRect[7]; // size=56, offset=344
  int s_screenMode; // size=0, offset=400
  int dispWidth; // size=0, offset=404
  int dispHeight; // size=0, offset=408
  int dispXOffset; // size=0, offset=412
  int dispYOffset; // size=0, offset=416
  struct DRAWENV m_drawEnv; // size=92, offset=420
  struct DISPENV m_dispEnv; // size=20, offset=512
  struct DRAWENV m_oldDrawEnv; // size=92, offset=532
  struct DISPENV m_oldDispEnv; // size=20, offset=624
  int spriteCount; // size=0, offset=644
  int polyCountFT4; // size=0, offset=648
  int polyCountG3; // size=0, offset=652
  int polyCountF4; // size=0, offset=656
  int moveCount; // size=0, offset=660
  int m_dirtyMouseX; // size=0, offset=664
  int m_dirtyMouseY; // size=0, offset=668
  unsigned short m_dirtyMouseBuffer[256]; // size=512, offset=672
  char m_kanjiTimBuffer[350]; // size=350, offset=1184
  struct SPRT sprites[200]; // size=4000, offset=1536
  struct DR_TPAGE tpages[200]; // size=1600, offset=5536
  struct POLY_FT4 polysFT4[25]; // size=1000, offset=7136
  struct POLY_F4 polysF4[0]; // size=0, offset=8136
  struct POLY_G3 polysG3[20]; // size=560, offset=8136
  struct DR_MOVE moves[2]; // size=48, offset=8696
  int m_dispX; // size=0, offset=8744
  int m_dispY; // size=0, offset=8748
  int m_flashCount; // size=0, offset=8752
  int m_flash; // size=0, offset=8756
  unsigned int m_flashOn; // size=0, offset=8760
  unsigned int m_invalidArea[7]; // size=28, offset=8764
  int m_addingBlock; // size=0, offset=8792
  int m_deletingBlock; // size=0, offset=8796
  struct FONTTABSTRUCT m_fontTable[3][76]; // size=3648, offset=8800
  struct KANJILOOKUP m_kanjiFontTable[256]; // size=5120, offset=12448
  struct TIMSTRUCT m_darkTimStruct; // size=12, offset=17568
  struct TIMSTRUCT m_pointerTimStruct; // size=12, offset=17580
  struct TIMSTRUCT m_lightTimStruct; // size=12, offset=17592
  struct TIMSTRUCT m_cardTimStruct; // size=12, offset=17604
  struct TIMSTRUCT m_buttonTimStructs[4]; // size=48, offset=17616
  struct TIMSTRUCT m_arrowTimStruct[2]; // size=24, offset=17664
  struct TIMSTRUCT m_sliceIconTimStructs[16]; // size=192, offset=17688
  struct TIMSTRUCT m_createBlockTimStruct; // size=12, offset=17880
  struct PAD *m_padPtr; // size=33404, offset=17892
  long *m_backImagePtr; // size=0, offset=17896
  int m_updateQueue[7]; // size=28, offset=17900
  int m_kanjiChars; // size=0, offset=17928
  int m_activeArea; // size=0, offset=17932
  int m_menuSelect; // size=0, offset=17936
  int m_blockSelect; // size=0, offset=17940
  int m_sliceSelect; // size=0, offset=17944
  int m_sliceMenuOffset; // size=0, offset=17948
  int m_sliceMenuRem; // size=0, offset=17952
  int m_sliceMenuInc; // size=0, offset=17956
  int m_activeFunction; // size=0, offset=17960
  int m_mainFunction; // size=0, offset=17964
  int m_maxKanji; // size=0, offset=17968
  unsigned int m_menuActive[4]; // size=16, offset=17972
  char *m_menuText[4]; // size=16, offset=17988
  char *m_infoText[3]; // size=12, offset=18004
  char *m_titleText; // size=0, offset=18016
  char *m_blockNameText; // size=0, offset=18020
  char m_saveFilename[32]; // size=32, offset=18024
  struct FILEFORMAT *m_fileFormatPtr; // size=340, offset=18056
};
struct ControllerPacket {
  unsigned char transStatus; // size=0, offset=0
  unsigned char dataFormat; // size=0, offset=1
  union data{
    unsigned short pad; // size=0, offset=0
    struct MouseData mouse; // size=4, offset=0
    struct NegconData negcon; // size=6, offset=0
    struct AnalogjoyData joystick; // size=6, offset=0
    struct MultiTapData tap; // size=32, offset=0
  }; // size=32, offset=2
};
struct PAD {
  struct MCSLOT m_mcSlot0; // size=16652, offset=0
  struct MCSLOT m_mcSlot1; // size=16652, offset=16652
  int m_mouseX; // size=0, offset=33304
  int m_mouseY; // size=0, offset=33308
  int m_scanPort; // size=0, offset=33312
  unsigned int m_cardChanged[2]; // size=8, offset=33316
  unsigned int m_bControllerChanged; // size=0, offset=33324
  unsigned int m_bMouseTested; // size=0, offset=33328
  unsigned int m_bUsingMouse; // size=0, offset=33332
  unsigned int m_bUsingNegCon; // size=0, offset=33336
  unsigned int m_bControllerInserted; // size=0, offset=33340
  int m_nLastControllerType; // size=0, offset=33344
  char slotString[3]; // size=3, offset=33348
  struct MCSLOT *m_slotObjPtrs[2]; // size=8, offset=33352
  int m_slotObjPorts[2]; // size=8, offset=33360
  int m_currSlotObj; // size=0, offset=33368
  int m_portStatus[8]; // size=32, offset=33372
};
struct PAD {
  struct MCSLOT m_mcSlot0; // size=16652, offset=0
  struct MCSLOT m_mcSlot1; // size=16652, offset=16652
  int m_mouseX; // size=0, offset=33304
  int m_mouseY; // size=0, offset=33308
  int m_scanPort; // size=0, offset=33312
  unsigned int m_cardChanged[2]; // size=8, offset=33316
  unsigned int m_bControllerChanged; // size=0, offset=33324
  unsigned int m_bMouseTested; // size=0, offset=33328
  unsigned int m_bUsingMouse; // size=0, offset=33332
  unsigned int m_bUsingNegCon; // size=0, offset=33336
  unsigned int m_bControllerInserted; // size=0, offset=33340
  int m_nLastControllerType; // size=0, offset=33344
  char slotString[3]; // size=3, offset=33348
  struct MCSLOT *m_slotObjPtrs[2]; // size=8, offset=33352
  int m_slotObjPorts[2]; // size=8, offset=33360
  int m_currSlotObj; // size=0, offset=33368
  int m_portStatus[8]; // size=32, offset=33372
};
struct PAD {
  struct MCSLOT m_mcSlot0; // size=16652, offset=0
  struct MCSLOT m_mcSlot1; // size=16652, offset=16652
  int m_mouseX; // size=0, offset=33304
  int m_mouseY; // size=0, offset=33308
  int m_scanPort; // size=0, offset=33312
  unsigned int m_cardChanged[2]; // size=8, offset=33316
  unsigned int m_bControllerChanged; // size=0, offset=33324
  unsigned int m_bMouseTested; // size=0, offset=33328
  unsigned int m_bUsingMouse; // size=0, offset=33332
  unsigned int m_bUsingNegCon; // size=0, offset=33336
  unsigned int m_bControllerInserted; // size=0, offset=33340
  int m_nLastControllerType; // size=0, offset=33344
  char slotString[3]; // size=3, offset=33348
  struct MCSLOT *m_slotObjPtrs[2]; // size=8, offset=33352
  int m_slotObjPorts[2]; // size=8, offset=33360
  int m_currSlotObj; // size=0, offset=33368
  int m_portStatus[8]; // size=32, offset=33372
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
typedef struct SCORE_ENTRY SCORE_ENTRY;
typedef struct SCORE_TABLES SCORE_TABLES;
typedef struct ACTIVE_CHEATS ACTIVE_CHEATS;
typedef struct STREAM_SOURCE STREAM_SOURCE;
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
typedef long time_t;
typedef short dev_t;
typedef long off_t;
typedef unsigned short uid_t;
typedef unsigned short gid_t;
typedef void (*SsMarkCallbackProc)();
typedef void (*CdlCB)();
typedef long LONGVECTOR[4];
typedef short SHORTVECTOR[4];
typedef long LONGQUATERNION[4];
typedef unsigned long ulong;
typedef unsigned long wchar_t;
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
typedef void *va_list;
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
0x9B388 sea
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
0xAADB0 offset.39
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
extern char *buffer; // offset 0xAB234
extern char *car_models_lump; // offset 0xAAF2C
extern char *CityNames[4]; // offset 0x1C6CE4
extern char *contNames[2]; // offset 0x1C6CFC
extern char *CosmeticFiles[4]; // offset 0x9C05C
extern char *cutGfxNames[4]; // offset 0x1C69A0
extern char *DentingFiles[4]; // offset 0x9C35C
extern char *g_msg[73]; // offset 0x10ECE0
extern char *g_textBuffer; // offset 0x10EE04
extern char *gfxNames[4]; // offset 0x1C6A08
extern char *gMissionTitle; // offset 0xAA788
extern char *gRamSlotPosition[128]; // offset 0xD6FB8
extern char *LevelFiles[4]; // offset 0xA043C
extern char *LevelPalettes[8]; // offset 0xA044C
extern char *LoadingScreenNames[4]; // offset 0xA046C
extern char *mallocptr; // offset 0xAAFC0
extern char *map_lump; // offset 0xAAF8C
extern char *MissionStrings; // offset 0xAB080
extern char *model_spool_buffer; // offset 0xAB294
extern char *modelname_buffer; // offset 0xAB088
extern char *motion_dir; // offset 0xAA800
extern char *motion_files[8]; // offset 0xA07E8
extern char *music_address; // offset 0xAB1C8
extern char *packed_cell_pointers; // offset 0xAB228
extern char *palette_lump; // offset 0xAAF74
extern char *primptr; // offset 0xAB31C
extern char *PVS_Buffers[4]; // offset 0xD6F90
extern char *RegionSpoolInfo; // offset 0xAB210
extern char *replayptr; // offset 0xAAAF4
extern char *ReplayStart; // offset 0xAAADC
extern char *ScreenNames[12]; // offset 0xD05C8
extern char *song_address; // offset 0xAB1B4
extern char *specLoadBuffer; // offset 0xAB090
extern char *specmallocptr; // offset 0xAB08C
extern char *SubDivisionArrays; // offset 0xAAD70
extern char *texturename_buffer; // offset 0xAB378
extern char *visiblelist; // offset 0xAA494
extern char *XANames[4]; // offset 0xA1F88
extern char AsciiTable[256]; // offset 0xD9FE0
extern char camera_change; // offset 0xAB1B8
extern char CameraChanged; // offset 0xAAD2D
extern char CamerasSaved; // offset 0xAA61D
extern char cameraview; // offset 0xAA61F
extern char Car0_ShinyTable[256]; // offset 0xCDBC8
extern char carNumLookup[4][10]; // offset 0x1C6AC4
extern char carTpages[4][8]; // offset 0x9BE8C
extern char continuous_track; // offset 0xAAED0
extern char cookieCount; // offset 0xAA1C4
extern char CopWorkMem[444]; // offset 0xBD698
extern char currentfilename[128]; // offset 0xA1C40
extern char CurrentPVS[444]; // offset 0xD73E0
extern char cutUnlock[41]; // offset 0x1C69D8
extern char DebrisTimer; // offset 0xAA5C8
extern char EnterScoreText[32]; // offset 0xD94E8
extern char es_mobile[1]; // offset 0xAA6DC
extern char final_replays; // offset 0xAA61E
extern char first_offence; // offset 0xAAEA9
extern char force_idle[8]; // offset 0xAB048
extern char force_siren[8]; // offset 0xAB058
extern char furthestCivID; // offset 0xAABDC
extern char gDoneQuickReplay; // offset 0xAA619
extern char ghost_mode; // offset 0xAA61B
extern char gLeadCarModel; // offset 0xAA617
extern char gNoReplaySaveAllowed; // offset 0xAA868
extern char gNoSaveAllowed; // offset 0xAA618
extern char gRainCount; // offset 0xAAC99
extern char gRightWayUp; // offset 0xAA61A
extern char IconsLoaded; // offset 0xAA616
extern char inGameCamera[4]; // offset 0xAA170
extern char InWater; // offset 0xAAF5C
extern char JunctionLightsNS; // offset 0xAB171
extern char junctionLightsPhase[2]; // offset 0xAAC08
extern char JunctionLightsWE; // offset 0xAB170
extern char last_cop_phrase; // offset 0xAAE58
extern char lastCity; // offset 0x1C6A73
extern char lastCutCity; // offset 0x1C6A74
extern char LeftLight; // offset 0xAACE4
extern char limoId; // offset 0xAAB70
extern char loaded[3]; // offset 0x1C6A70
extern char lockAllTheDoors; // offset 0xAAFC8
extern char makeLimoPullOver; // offset 0xAAB78
extern char modelRandomList[16]; // offset 0x9BFA4
extern char MonoMode; // offset 0xAAA64
extern char MotionSpeed[7]; // offset 0xA0808
extern char NewLevel; // offset 0xAA615
extern char NoPlayerControl; // offset 0xAA621
extern char NumPlayers; // offset 0xAAA1A
extern char nybblearray[512]; // offset 0xD71B8
extern char old_camera_change; // offset 0xAB1B0
extern char OverlayFlashValue; // offset 0xAAAB8
extern char paused; // offset 0xAA61C
extern char phrase_top; // offset 0xAAEA8
extern char ping_in_pedestrians; // offset 0xAB140
extern char PingOutCivsOnly; // offset 0xAA1DC
extern char playerNum; // offset 0xAAC00
extern char PoolPrimData[16]; // offset 0x9C074
extern char rear_only; // offset 0xAAED1
extern char RecordingPads; // offset 0xAA110
extern char ReplayMode; // offset 0xAA620
extern char RightLight; // offset 0xAAC98
extern char ScreenTitle[128]; // offset 0x1CC1D8
extern char specModelValid; // offset 0xAA7B0
extern char specTpages[4][12]; // offset 0x9BE5C
extern char speedLimits[3]; // offset 0x9BF78
extern char tracking_car; // offset 0xAAD2C
extern char TransparentObject; // offset 0xAA47C
extern char tsdname[128]; // offset 0xE0D00
extern char VeryShinyTable[256]; // offset 0xCDAC8
extern enum GAMEMODE CurrentGameMode; // offset 0xAA5A8
extern enum GAMEMODE WantedGameMode; // offset 0xAA5A9
extern enum GAMETYPE GameType; // offset 0xAA62C
extern enum GAMETYPE StoredGameType; // offset 0xAA62D
extern enum LIMBS lRoutes[5][8]; // offset 0xA07C0
extern enum PAUSEMODE gMissionCompletionState; // offset 0xAA78C
extern int *debugCount; // offset 0xAAE34
extern int *idx; // offset 0xAA97C
extern int *modelMemory; // offset 0xAB238
extern int aa; // offset 0xAAA74
extern int allowSpecSpooling; // offset 0xAB25C
extern int allowVibration; // offset 0x1C6AAC
extern int allreadydone; // offset 0xAA938
extern int angle; // offset 0xAAB58
extern int asf; // offset 0xE9158
extern int attract_number; // offset 0xAA460
extern int AttractMode; // offset 0xAA648
extern int autobrakeon; // offset 0xAA5C0
extern int AutoDirect; // offset 0xAAD44
extern int bAllreadyRotated; // offset 0xAA7B4
extern int baseSpecCP; // offset 0xAAB30
extern int basic_car_interest; // offset 0xAB124
extern int bAvoidBomb; // offset 0xAA8E4
extern int bAvoidTanner; // offset 0xAA8E0
extern int bCdIconSetup; // offset 0x1C6AC0
extern int bDisplayBones; // offset 0xAA808
extern int bDoingCarSelect; // offset 0x1C6A80
extern int bDoingCutSelect; // offset 0x1C699C
extern int bDoingScores; // offset 0x1C6994
extern int bDoingShadow; // offset 0xAA7B8
extern int bDoneAllready; // offset 0x1C6AA4
extern int bDrawExtra; // offset 0x1C6A88
extern int bFreezeAnimation; // offset 0xAA8CC
extern int bInCutSelect; // offset 0x1C6A78
extern int bKilled; // offset 0xAA8EC
extern int bKillTanner; // offset 0xAA8D8
extern int bLoadedAllMC; // offset 0xAA804
extern int bMissionSelect; // offset 0x1C6AA8
extern int bMissionTitleFade; // offset 0xAA5FC
extern int bodySelect; // offset 0xAA124
extern int bodyShiftValue; // offset 0xAA810
extern int boneIdvals[15]; // offset 0xA0F40
extern int boxOverlap; // offset 0xAAB00
extern int BPMLimit; // offset 0xAB3CC
extern int bPower; // offset 0xAA904
extern int bRedrawFrontend; // offset 0x1C6A98
extern int bRequestedKey; // offset 0x1C6AA0
extern int bReturnToMain; // offset 0xAA5A4
extern int bReverseAnimation; // offset 0xAA8D0
extern int bReverseYRotation; // offset 0xAA8DC
extern int bScreenSetup; // offset 0x1C6A8C
extern int bStopTanner; // offset 0xAA8F0
extern int bTannerSitting; // offset 0xAA8BC
extern int buildingsFound; // offset 0xAAD5C
extern int bWantCDReset; // offset 0x1C6A9C
extern int cak; // offset 0xAAA28
extern int camera_cell_x; // offset 0xAAFF0
extern int camera_cell_z; // offset 0xAAFF4
extern int CameraCar; // offset 0xAA65C
extern int CameraCnt; // offset 0xAAF90
extern int CAR_PAUSE_START; // offset 0xAA1E0
extern int carAngle; // offset 0xAA1FC
extern int CarAvailability[4][10]; // offset 0x1C6AEC
extern int CarLightFadeBack; // offset 0xAACF8
extern int CarLightFadeFront; // offset 0xAACB0
extern int carnum; // offset 0xAAB88
extern int carSelection; // offset 0x1C6A04
extern int cell_object_index; // offset 0xAA1A8
extern int cell_objects_add[5]; // offset 0xD6FA0
extern int cell_slots_add[5]; // offset 0xD73C8
extern int cells_across; // offset 0xAA6D4
extern int cells_down; // offset 0xAA6D8
extern int checkFrames; // offset 0xAA1B4
extern int chunk_complete; // offset 0xAB2E0
extern int citystart[8]; // offset 0xE0B48
extern int civ_smoke_enabled; // offset 0xAA188
extern int cJerichoVNumbers[7]; // offset 0xD7D80
extern int ClearCameras; // offset 0xAA45C
extern int closeEncounter; // offset 0xAA1EC
extern int collision_boxes_set; // offset 0xAB110
extern int combointensity; // offset 0xAB150
extern int cop_respawn_timer; // offset 0xAAC50
extern int CopsAllowed; // offset 0xAAC38
extern int copsAreInPursuit; // offset 0xAAC3C
extern int CopsCanSeePlayer; // offset 0xAAC30
extern int coptrackpos[8]; // offset 0x9F064
extern int corner; // offset 0xAA1F4
extern int crateoffset; // offset 0xAA5E0
extern int cTannerVNumbers[24]; // offset 0xD7D20
extern int currCity; // offset 0x1C6A68
extern int current_barrel_region_xcell; // offset 0xAAFF8
extern int current_barrel_region_zcell; // offset 0xAAFFC
extern int current_camera_angle; // offset 0xAA160
extern int current_cell_x; // offset 0xAB01C
extern int current_cell_z; // offset 0xAB020
extern int current_music_id; // offset 0xAB244
extern int current_object_computed_value; // offset 0xAAF28
extern int current_region; // offset 0xAB028
extern int currentAngle; // offset 0xAABCC
extern int CurrentCh; // offset 0xAB3EC
extern int CurrentPlayerView; // offset 0xAA638
extern int currentRoadId; // offset 0xAABE8
extern int currMission; // offset 0x1CC544
extern int currPlayer; // offset 0x1C6A7C
extern int currSelIndex; // offset 0x1C6A84
extern int CursorX; // offset 0xAAD24
extern int CursorY; // offset 0xAAD28
extern int CutAmounts[5]; // offset 0x1C69B0
extern int CutAmountsTotal[5]; // offset 0x1C69C4
extern int CutsceneEventTrigger; // offset 0xAA270
extern int CutsceneFrameCnt; // offset 0xAA26C
extern int cutSelection; // offset 0x1C6998
extern int cycle_phase; // offset 0xAAAA8
extern int damOffset; // offset 0xAB2A0
extern int DawnCount; // offset 0xAAFA8
extern int dd; // offset 0xAAA78
extern int de; // offset 0xAAA7C
extern int debugNode[2]; // offset 0xAAE48
extern int debugOffset; // offset 0xAAE3C
extern int debugRotation; // offset 0xAA570
extern int debugSpeed; // offset 0xAAE30
extern int distanceReturnedLog[8]; // offset 0xF27A0
extern int DistanceTriggerCarMoves; // offset 0xAA518
extern int distFromCentre; // offset 0xAABF8
extern int distFurthestCivCarSq; // offset 0xAAB5C
extern int distLogIndex; // offset 0xE9AB0
extern int distObstacle; // offset 0xAABC8
extern int DM_CIRCLE[16][2][2]; // offset 0x10EB70
extern int DoExtraWorkForNFrames; // offset 0xE99AC
extern int done; // offset 0xAB2A4
extern int DoNotSwap; // offset 0xAAA1C
extern int doSpooling; // offset 0xAA9FC
extern int doWheels; // offset 0xAA5D0
extern int DVL; // offset 0xAB3D0
extern int DVR; // offset 0xAB3DC
extern int dx; // offset 0xAABB8
extern int dy; // offset 0xAABBC
extern int dz; // offset 0xAABC0
extern int editing_existing_camera; // offset 0xAA454
extern int EditMode; // offset 0xAA440
extern int ElTrainData[83]; // offset 0x9E770
extern int environmenttpage; // offset 0xAB35C
extern int error_bounds; // offset 0xAAA00
extern int EVENT_CAR_SPEED; // offset 0xAA200
extern int event_models_active; // offset 0xAAE50
extern int ExBombTimer; // offset 0xAAEDC
extern int ExBoxDamage; // offset 0xAAED8
extern int ExLastCarX; // offset 0xAAEEC
extern int ExLastCarXVel; // offset 0xAAEE4
extern int ExLastCarZ; // offset 0xAAEF0
extern int ExLastCarZVel; // offset 0xAAEE8
extern int FadingScreen; // offset 0xAA5F8
extern int fakeOtherPlayer; // offset 0xAA5AC
extern int fasterToggle; // offset 0xAAD74
extern int FastForward; // offset 0xAA458
extern int FastForwardCameraCnt; // offset 0xAA464
extern int FelonyDecreaseTime; // offset 0xAAE5C
extern int FelonyDecreaseTimer; // offset 0xAAE64
extern int FelonyIncreaseTime; // offset 0xAAE60
extern int FelonyIncreaseTimer; // offset 0xAAE68
extern int feVariableSave[4]; // offset 0x9F134
extern int first_paletised_page; // offset 0xAAAD4
extern int firstDamBlock; // offset 0xAB26C
extern int firstLowBlock; // offset 0xAB27C
extern int frame_advance_count; // offset 0xAAD40
extern int FrameCnt; // offset 0xAB320
extern int frames; // offset 0xAB0A4
extern int frameStart; // offset 0xAAB64
extern int FrAng; // offset 0xAAD60
extern int g321GoDelay; // offset 0xAA794
extern int gAllowMusic; // offset 0xAA9E0
extern int gAllowSfx; // offset 0xAA9E4
extern int game_over; // offset 0xAAFB8
extern int gameinit; // offset 0xAA668
extern int GameLevel; // offset 0xAA640
extern int GameNum; // offset 0x1C6CE0
extern int gBatterPlayer; // offset 0xAA218
extern int gBobIndex; // offset 0xAAF98
extern int gCameraAngle; // offset 0xAA16C
extern int gCameraDistance; // offset 0xAA164
extern int gCameraMaxDistance; // offset 0xAA168
extern int gCantDrive; // offset 0xAA768
extern int gcar_num; // offset 0xAACD4
extern int gCarPoolsToDraw; // offset 0xAACF0
extern int gCarWithABerm; // offset 0xAA764
extern int gChaseNumber; // offset 0xAA598
extern int gCopCarTheftAttempted; // offset 0xAA79C
extern int gCopDesiredSpeedScale; // offset 0xAA21C
extern int gCopDifficultyLevel; // offset 0xAA64C
extern int gCopMaxPowerScale; // offset 0xAA220
extern int gCopRespawnTime; // offset 0xAA228
extern int gCurrentChaseNumber; // offset 0xAA634
extern int gCurrentMissionNumber; // offset 0xAA630
extern int gCurrentResidentSlot; // offset 0xAA18C
extern int gCurrentZ; // offset 0xAB0BC
extern int gCutsceneAtEnd; // offset 0xAA284
extern int gDisplayPosition; // offset 0xAA6E0
extern int gDoBonnets; // offset 0xAA184
extern int gDoCrates; // offset 0xAAFA0
extern int gDoLeaves; // offset 0xAA2A0
extern int gDontPingInCops; // offset 0xAA790
extern int gDontResetCarDamage; // offset 0xAA7A4
extern int gDoShinyCars; // offset 0xAA3FC
extern int gDoSmoke; // offset 0xAA29C
extern int gDraw3DArrowBlue; // offset 0xAAA2C
extern int gDrawLowerSky; // offset 0xAA9A0
extern int gDrawPauseMenus; // offset 0xAA864
extern int gDualShockMax; // offset 0xAA838
extern int gEffectsTimer; // offset 0xAACCC
extern int gFlareScale; // offset 0xAA294
extern int gForceLowDetailCars; // offset 0xAAB2C
extern int gFurthestMission; // offset 0xAA5B4
extern int gGotInStolenCar; // offset 0xAA798
extern int gHaveStoredData; // offset 0xAA6F8
extern int gIdleReplay; // offset 0xAA5BC
extern int gInFrontend; // offset 0xAA66C
extern int gInGameChaseActive; // offset 0xAA264
extern int gInGameCutsceneActive; // offset 0xAA268
extern int gInGameCutsceneDelay; // offset 0xAA278
extern int gInGameCutsceneID; // offset 0xAA27C
extern int gInvincibleCar; // offset 0xAA67C
extern int gLapTimes[2][5]; // offset 0xD7CC8
extern int gLightsOn; // offset 0xAAFA4
extern int gLoadedMotionCapture; // offset 0xAAF1C
extern int gLoadedOverlay; // offset 0xAAFAC
extern int gLoadedReplay; // offset 0xAA670
extern int gLockPickingAttempted; // offset 0xAA7A0
extern int gMasterVolume; // offset 0xAA9DC
extern int gMinimumCops; // offset 0xAA210
extern int gMissionLadderPos; // offset 0xAA5B0
extern int gMultiplayerLevels; // offset 0xAAA20
extern int gMusicType; // offset 0xAB064
extern int gMusicVolume; // offset 0xAA9D8
extern int gNextRainDrop; // offset 0xAACC4
extern int gNight; // offset 0xAA684
extern int gNumCitiesOpen; // offset 0xAA628
extern int gNumRaceTrackLaps; // offset 0xAA784
extern int goFaster; // offset 0xAA4A4
extern int gOutOfTape; // offset 0xAA118
extern int gPlayerCarDamage; // offset 0xAA5C4
extern int gPlayerCarLights; // offset 0xAA288
extern int gPlayerDamageFactor; // offset 0xAB078
extern int gPlayerImmune; // offset 0xAA680
extern int gPlayerWithTheFlag; // offset 0xAA760
extern int gPuppyDogCop; // offset 0xAA214
extern int gRandomChase; // offset 0xAA59C
extern int groundDebrisIndex; // offset 0xAA480
extern int gShadowTextureNum; // offset 0xAB184
extern int gShadowTexturePage; // offset 0xAB188
extern int gShowMap; // offset 0xAA674
extern int gShowPlayerDamage; // offset 0xAAF64
extern int gSinkingTimer; // offset 0xAAF80
extern int gSoundMode; // offset 0xAA9B0
extern int gStartOnFoot; // offset 0xAA750
extern int gStopPadReads; // offset 0xAA688
extern int gSubGameNumber; // offset 0xAA5A0
extern int gSubtitles; // offset 0xAA6A0
extern int gSurround; // offset 0xAA9B4
extern int gTannerActionNeeded; // offset 0xAA75C
extern int gThePlayerCar; // offset 0xAA274
extern int gTimeInWater; // offset 0xAAECC
extern int gTimeOfDay; // offset 0xAA754
extern int gTrailblazerConeCount; // offset 0xAA4B4
extern int gTrailblazerConeIndex; // offset 0xAA4B8
extern int gTunnelNum; // offset 0xAA9AC
extern int GuitarType; // offset 0xAA068
extern int gUseCopModel; // offset 0xAA4C4
extern int gVibration; // offset 0xAA678
extern int gWantNight; // offset 0xAA5B8
extern int gWeather; // offset 0xAA758
extern int handle; // offset 0xAAF4C
extern int HavanaFerryData[12]; // offset 0x9E8E4
extern int HavanaMiniData[4]; // offset 0x9E92C
extern int headposition; // offset 0xAA17C
extern int headtarget; // offset 0xAA178
extern int HitLeadCar; // offset 0xAAFB0
extern int horizonadd; // offset 0xAA204
extern int iAllowWatch; // offset 0xAA8C4
extern int iCurrBone; // offset 0xAB0B8
extern int idle_timer; // offset 0x1CBDA8
extern int iFreezeTimer; // offset 0xAA8C8
extern int iIdleTimer; // offset 0xAA8E8
extern int impulse; // offset 0xAB390
extern int initarea; // offset 0xAB000
extern int jericho_in_back; // offset 0xAB050
extern int joints; // offset 0xAB0AC
extern int JP_Do_Nothing; // offset 0xAB3E0
extern int JPError; // offset 0xAAA60
extern int JPPer; // offset 0xAAA80
extern int jtest53; // offset 0xAA174
extern int JustReturnedFromCutscene; // offset 0xAA280
extern int l1; // offset 0xAA208
extern int l2; // offset 0xAA20C
extern int laneFit[2]; // offset 0xAABA0
extern int last_size; // offset 0xAB2D4
extern int last_track_state; // offset 0xAA5CC
extern int lastCarCameraView; // offset 0xAA93C
extern int lastCleanBlock; // offset 0xAB29C
extern int lastDistanceFound; // offset 0xE9AC8
extern int LastHeading; // offset 0xAAC34
extern int lead_car; // offset 0xAA654
extern int leadAILoaded; // offset 0xAA690
extern int leadAIRequired; // offset 0xAA68C
extern int leadCarId; // offset 0xAAF88
extern int lengthDamBlock; // offset 0xAB298
extern int lengthLowBlock; // offset 0xAB2A8
extern int Level_NumAnimatedObjects[8]; // offset 0x9B674
extern int LevelTab[32]; // offset 0xA1EF0
extern int LiftingBridges[55]; // offset 0x9EC90
extern int LightIndex; // offset 0xAACF4
extern int lightning; // offset 0xAA484
extern int LightningTimer; // offset 0xAA28C
extern int LightSortCorrect; // offset 0xAACA0
extern int littleBangTime; // offset 0xAA5E4
extern int littleBoxRange; // offset 0xAA14C
extern int loadbank_read; // offset 0xAB278
extern int loadbank_write; // offset 0xAB2CC
extern int LoadedArea; // offset 0xAB2B8
extern int LoadingArea; // offset 0xAA9E8
extern int localMap[41]; // offset 0xECD40
extern int lowOffset; // offset 0xAB2B0
extern int main_cop_light_pos; // offset 0xAACE0
extern int mainScreenLoaded; // offset 0x1C6ABC
extern int makeNextNodeCtrlNode; // offset 0xAA1E8
extern int map_x_shift; // offset 0xAA100
extern int map_z_shift; // offset 0xAA104
extern int max_pedestrians; // offset 0xAA8D4
extern int maxCameraDist; // offset 0xAAB14
extern int maxCivCars; // offset 0xAAC10
extern int maxCopCars; // offset 0xAAC0C
extern int maxParkedCars; // offset 0xAABE0
extern int maxPlayerCars; // offset 0xAABEC
extern int MaxPlayerDamage[2]; // offset 0xAA76C
extern int maxrevdrop; // offset 0xAA578
extern int maxrevrise; // offset 0xAA57C
extern int maxSeated; // offset 0xAB130
extern int MaxSpecCluts; // offset 0xAB358
extern int maxSteer; // offset 0xAA1B8
extern int menuactive; // offset 0xAAD1C
extern int MenuOffset; // offset 0xAAD14
extern int MIN_TRIPOD_CAMERA_HEIGHT; // offset 0xAA43C
extern int minBoxSize; // offset 0xAA150
extern int minmaxSelections[4][2]; // offset 0x1C6B90
extern int missionSetup; // offset 0x1C6A6C
extern int models_ready; // offset 0xAB254
extern int MotionCaptureData[24]; // offset 0xD8E40
extern int mScale; // offset 0xAA128
extern int mTheta; // offset 0xAAB08
extern int multiplayerregions[4]; // offset 0xDEE20
extern int music_is_loading; // offset 0xAA9F8
extern int music_paused; // offset 0xAA9C4
extern int my_sly_var; // offset 0xAB148
extern int myPalette; // offset 0xAA194
extern int myVal; // offset 0xAA80C
extern int n_sample_chunks; // offset 0xAB224
extern int na; // offset 0xE915C
extern int new_area_location; // offset 0xAB260
extern int newAccel; // offset 0xAA1BC
extern int newExit; // offset 0xAABC4
extern int NewLamp[21]; // offset 0xC1B28
extern int next_debris; // offset 0xAACB4
extern int next_leaf; // offset 0xAACE8
extern int next_smoke; // offset 0xAAC9C
extern int NextDamagedLamp; // offset 0xAACEC
extern int NextDamagedPmeter; // offset 0xAACBC
extern int NightAmbient; // offset 0xAAF68
extern int NoRainIndoors; // offset 0xAACC8
extern int NoTextureMemory; // offset 0xAB344
extern int nperms; // offset 0xAB354
extern int nsectors; // offset 0xAB288
extern int nspecpages; // offset 0xAB340
extern int num_active_cars; // offset 0xAAEC8
extern int num_anim_objects; // offset 0xAAAB0
extern int num_cars_drawn; // offset 0xAAB34
extern int num_cycle_obj; // offset 0xAAAB4
extern int num_extra_boxes_set; // offset 0xAB114
extern int Num_LevCycleObjs[4]; // offset 0x9B4E4
extern int num_models_in_pack; // offset 0xAB00C
extern int num_regions; // offset 0xAAFE4
extern int num_samples; // offset 0xAB23C
extern int num_straddlers; // offset 0xAB02C
extern int num_tyre_tracks[4]; // offset 0xDAA48
extern int numActiveCops; // offset 0xAAC54
extern int NumAreas; // offset 0xAB268
extern int numCivCars; // offset 0xAAB4C
extern int numCopCars; // offset 0xAAB48
extern int NumDriver2Curves; // offset 0xAAA88
extern int NumDriver2Junctions; // offset 0xAAA9C
extern int NumDriver2Straights; // offset 0xAAA98
extern int numInactiveCars; // offset 0xAAB60
extern int numPadsConnected; // offset 0x1C6AB0
extern int numParkedCars; // offset 0xAABE4
extern int numPlayerCars; // offset 0xAABF0
extern int numPlayersToCreate; // offset 0xAA940
extern int NumReplayStreams; // offset 0xAA10C
extern int numRoadblockCars; // offset 0xAAB7C
extern int numSpritesFound; // offset 0xAAD50
extern int NumTempJunctions; // offset 0xAB068
extern int ObjectDrawnCounter; // offset 0xAA6A4
extern int old_region; // offset 0xAAFD8
extern int oldActionSet; // offset 0x1C6B8C
extern int oldActionVal; // offset 0x1CC560
extern int oldMusicLevel; // offset 0x1CC580
extern int oldSfxLevel; // offset 0x1CC258
extern int oldWeather; // offset 0xAB118
extern int OutOfSightCount; // offset 0xAAC2C
extern int OverlayOccupancyGrid; // offset 0xE91A0
extern int pad_connected; // offset 0xAA834
extern int pad_recorded; // offset 0xAA114
extern int padsConnected[2]; // offset 0x1C6AB4
extern int palnumber; // offset 0xAA814
extern int PALType; // offset 0xAB3BC
extern int pathAILoaded; // offset 0xAA694
extern int pathFrame; // offset 0xF1B00
extern int pathFrames; // offset 0xE99A8
extern int pathIterations; // offset 0xF27C0
extern int pathStraight; // offset 0xAAC48
extern int pauseflag; // offset 0xAA650
extern int persuit_mode; // offset 0xAA63C
extern int pinginPedAngle; // offset 0xAA8C0
extern int player_position_known; // offset 0xAAC4C
extern int PlayerCar; // offset 0xAA658
extern int PlayerCarModel; // offset 0xAA644
extern int playerDying; // offset 0xAAF54
extern int playerghost; // offset 0xAA5D4
extern int playerhitcopsanyway; // offset 0xAA5D8
extern int playerTargetDistanceSq; // offset 0xE9ACC
extern int PlayMode; // offset 0xAAD34
extern int PolySizes[56]; // offset 0xA17C0
extern int powerCounter; // offset 0xAA908
extern int pvs_cells_rejected; // offset 0xAB010
extern int pvs_objects_rejected; // offset 0xAAFE0
extern int pvs_square; // offset 0xAAFDC
extern int pvs_square_sq; // offset 0xAB014
extern int quick_replay; // offset 0xAAD30
extern int quickSpool; // offset 0xAB21C
extern int radius; // offset 0xAAB8C
extern int region_buffer_xor; // offset 0xAAA94
extern int region_x; // offset 0xAB004
extern int region_z; // offset 0xAB008
extern int regions_across; // offset 0xAB024
extern int regions_down; // offset 0xAAFE8
extern int regions_unpacked[4]; // offset 0xD73B8
extern int ReplayContinue; // offset 0xAAD3C
extern int ReplaySize; // offset 0xAA108
extern int requestCopCar; // offset 0xAAC58
extern int requestRoadblock; // offset 0xAAB98
extern int requestStationaryCivCar; // offset 0xAABF4
extern int RioFerryData[6]; // offset 0x9E914
extern int road_c; // offset 0xECD38
extern int road_s; // offset 0xECD3C
extern int roadAhead[41]; // offset 0xECDE8
extern int roadblockCount; // offset 0xAAC04
extern int roadblockDelay; // offset 0xAA1C0
extern int roadblockDelayDiff[3]; // offset 0x9BF6C
extern int RoadMapRegions[4]; // offset 0xDA0F0
extern int roadSeg; // offset 0xAABA8
extern int sample_chunk; // offset 0xAB258
extern int saved_counter; // offset 0xAAF9C
extern int saved_leadcar_pos; // offset 0xAAF70
extern int scr_z; // offset 0xAAF24
extern int screen_fade_end; // offset 0xAA5F0
extern int screen_fade_speed; // offset 0xAA5F4
extern int screen_fade_start; // offset 0xAA5EC
extern int screen_fade_value; // offset 0xAA5E8
extern int ScreenDepth; // offset 0xAAEB0
extern int sdLevel; // offset 0xAAA90
extern int seated_count; // offset 0xAB11C
extern int send_bank; // offset 0xAB2AC
extern int SetFastForward; // offset 0xAA444
extern int setupYet; // offset 0xAA490
extern int ShinyTextureNum; // offset 0xAAD90
extern int ShinyTexturePage; // offset 0xAAD94
extern int sideMul; // offset 0xAA1F0
extern int sideShift; // offset 0xAA1F8
extern int sizeof_cell_object_computed_values; // offset 0xAAB38
extern int skyFade; // offset 0xAB1A8
extern int slotsused; // offset 0xAB384
extern int slowWallTests; // offset 0xE913C
extern int SmashablesHit; // offset 0xAACD0
extern int smoke_count[4]; // offset 0xDB098
extern int SmokeCnt; // offset 0xAA298
extern int Song_ID; // offset 0xAA9D0
extern int specBlocksToLoad; // offset 0xAAA0C
extern int SpecialByRegion[4][20]; // offset 0xA1AE0
extern int specialState; // offset 0xAAA08
extern int specSpoolComplete; // offset 0xAB250
extern int speed1[3]; // offset 0x9C000
extern int speed2[3]; // offset 0x9C00C
extern int spool_regioncounter; // offset 0xAB218
extern int spool_regionpos; // offset 0xAB230
extern int spoolactive; // offset 0xAB240
extern int spoolcounter; // offset 0xAB270
extern int spoolerror; // offset 0xAB22C
extern int SpoolLumpOffset; // offset 0xAB214
extern int spoolpos; // offset 0xAB290
extern int spoolpos_reading; // offset 0xAA9EC
extern int spoolpos_writing; // offset 0xAA9F0
extern int spoolseek; // offset 0xAB2DC
extern int sprite_shadow; // offset 0xAA478
extern int spuaddress; // offset 0xAB220
extern int startSpecSpool; // offset 0xAB2D0
extern int StreakCount1; // offset 0xAACB8
extern int switch_detail_distance; // offset 0xAA190
extern int TAIL_GETTINGCLOSE; // offset 0xAA778
extern int TAIL_GETTINGFAR; // offset 0xAA77C
extern int TAIL_TOOCLOSE; // offset 0xAA774
extern int TAIL_TOOFAR; // offset 0xAA780
extern int Tangle; // offset 0xAB0A0
extern int tannerDeathTimer; // offset 0xAA610
extern int tannerTurn; // offset 0xAA900
extern int tannerTurnMax; // offset 0xAA8FC
extern int tannerTurnStep; // offset 0xAA8F8
extern int TargetCar; // offset 0xAA660
extern int tcRoad; // offset 0xAA4A0
extern int tcRoof; // offset 0xAA498
extern int tcWall; // offset 0xAA49C
extern int test123; // offset 0xAAB6C
extern int test23; // offset 0xAA1D8
extern int test3; // offset 0xAAE70
extern int test4; // offset 0xAAE74
extern int test42; // offset 0xAAB68
extern int test5; // offset 0xAAE78
extern int test555; // offset 0xAAB74
extern int test6; // offset 0xAAE7C
extern int test7; // offset 0xAAE80
extern int test777; // offset 0xAA81C
extern int test8; // offset 0xAAE84
extern int testCar; // offset 0xAA1E4
extern int testNum; // offset 0xAABD0
extern int testNumPingedOut; // offset 0xAA1B0
extern int testRadius; // offset 0xAA818
extern int texamount; // offset 0xAB380
extern int texture_is_icon; // offset 0xAAA30
extern int texture_lump_start; // offset 0xAB37C
extern int ThisMotion; // offset 0xAB098
extern int time_taken; // offset 0xAAD18
extern int times; // offset 0xAAA04
extern int TimeSinceLastSpeech; // offset 0xAAEAC
extern int TimeToWay; // offset 0xAAAF0
extern int tmpNewLane[2]; // offset 0xAAB40
extern int tmpNewRoad[2]; // offset 0xAAB50
extern int toggleCam; // offset 0xAA22C
extern int tpage_amount; // offset 0xAB360
extern int tpage_texamts[128]; // offset 0xE0DD0
extern int trayoffset; // offset 0xAA180
extern int TriggerBomb; // offset 0xAAEE0
extern int tsetcounter; // offset 0xAB248
extern int tsetinfo[32]; // offset 0xDED90
extern int tsetpos; // offset 0xAB264
extern int tt; // offset 0xAAA70
extern int tunnelDir[3][2]; // offset 0xA1A4C
extern int type; // offset 0xAA9F4
extern int tyre_track_offset[4]; // offset 0xDCCA8
extern int units_across_halved; // offset 0xAAFD4
extern int units_down_halved; // offset 0xAAFEC
extern int unpack_cellptr_flag; // offset 0xAB2E4
extern int unpack_roadmap_flag; // offset 0xAB2C8
extern int useStoredPings; // offset 0xAA1AC
extern int VABID; // offset 0xAA9D4
extern int variable_weather; // offset 0xAA290
extern int vblcounter; // offset 0xAB308
extern int vcount; // offset 0xAAD6C
extern int VegasParkedTrains[3]; // offset 0x9E8D8
extern int VegasTrainData[7]; // offset 0x9E8BC
extern int view_dist; // offset 0xAB018
extern int vStored; // offset 0xAA7BC
extern int wantedCar[2]; // offset 0xAA698
extern int way_distance; // offset 0xAAAE0
extern int wetness; // offset 0xAACC0
extern int whichCP; // offset 0xAAB28
extern int wibblewibblewoo; // offset 0xAAB04
extern int xa_timeout; // offset 0xAAF30
extern int XM_FrameSpeed; // offset 0xAB3D8
extern int XM_HA; // offset 0xAAA6C
extern int XM_NSA; // offset 0xAAA68
extern int XM_SCAN; // offset 0xAAA5C
extern int XMTime1; // offset 0xAB3B0
extern int XMTime2; // offset 0xAB3B4
extern int XMTime3; // offset 0xAB3B8
extern int zVal; // offset 0xAA7C0
extern long *savemapinfo; // offset 0xAA5DC
extern long bankaddr[2]; // offset 0xAB1C0
extern long dummylong[3]; // offset 0xA1AC4
extern long dunyet[32][2]; // offset 0xE99B0
extern long force[4]; // offset 0xA1720
extern long gHubcapTime; // offset 0xAAD00
extern long levelstartpos[8][4]; // offset 0xA1740
extern long point[4]; // offset 0xA1730
extern short *RoadMapDataRegions[4]; // offset 0xDA0E0
extern short CurrentJunction; // offset 0xAA624
extern short CurrentRoad; // offset 0xAA622
extern short cycle_timer; // offset 0xAAAAC
extern short debris_alloc[60]; // offset 0xC1C28
extern short fePad; // offset 0x1CC5D4
extern short fontclutid; // offset 0xAB15C
extern short fonttpage; // offset 0xAB168
extern short gPlayerCar0ShinyFaces[38]; // offset 0x9E724
extern short gRainAlloc[180]; // offset 0xC2A38
extern short initialOccurrenceDelay[12]; // offset 0x9EE00
extern short initialReccurrenceDelay[12]; // offset 0x9EE18
extern short iVABID[8]; // offset 0xA1F98
extern short leaf_alloc[50]; // offset 0xBF8D8
extern short light_col; // offset 0xAACE6
extern short loading_region[4]; // offset 0xAB2C0
extern short padd; // offset 0xAB324
extern short paddp; // offset 0xAB304
extern short pedestrianFelony; // offset 0xAA224
extern short playerLastRoad; // offset 0xAAE6C
extern short PlayerWaypoints; // offset 0xAAD20
extern short smoke_alloc[80]; // offset 0xC1A58
extern short specialSlot; // offset 0xAB350
extern short specspooldata[3]; // offset 0xAAA34
extern short validExitIdx[4]; // offset 0xAABB0
extern short XMSongIDs[24]; // offset 0xA1FA8
extern short XMSPU_SFX[24]; // offset 0xA1FD8
extern struct CIV_PING civPingTest; // offset 0x9BF7C
extern struct tNodeDir ends[6][2]; // offset 0xE9108
extern struct tNodeDir dirs[6]; // offset 0xE9140
extern struct __tunnelinfo tunnels; // offset 0xD0220
extern struct _CAR_DATA *active_car_list[20]; // offset 0xD1278
extern struct _CAR_DATA *carToGetIn; // offset 0xAB13C
extern struct _CAR_DATA *collision_car_ptr[8]; // offset 0xD96B8
extern struct _CAR_DATA *gBombTargetVehicle; // offset 0xAA148
extern struct _CAR_DATA *jcam; // offset 0xAAB18
extern struct _CAR_DATA *pcdTanner; // offset 0xAB138
extern struct _CAR_DATA *pCivCarToGetIn; // offset 0xAA930
extern struct _CAR_DATA *targetVehicle; // offset 0xAAC5C
extern struct _CAR_DATA car_data[22]; // offset 0xD12E0
extern struct _CAR_DATA currentCar; // offset 0xBD210
extern struct _EVENT *firstEvent; // offset 0xAAE38
extern struct _ExOBJECT explosion[5]; // offset 0xD5498
extern struct _HANDLING_TYPE handlingType[7]; // offset 0x9F144
extern struct _MISSION *MissionHeader; // offset 0xAB06C
extern struct _PERCENTAGE_BAR DamageBar; // offset 0xAB860
extern struct _PERCENTAGE_BAR FelonyBar; // offset 0xAB880
extern struct _PERCENTAGE_BAR Player2DamageBar; // offset 0xAB820
extern struct _PERCENTAGE_BAR PlayerDamageBar; // offset 0xAB8A0
extern struct _PERCENTAGE_BAR ProxyBar; // offset 0xAB840
extern struct _PING_PACKET *PingBuffer; // offset 0xAAAF8
extern struct _PLAYER player[8]; // offset 0xD97A0
extern struct _sdPlane *dbSurfacePtr; // offset 0xAAA48
extern struct _sdPlane sea; // offset 0x9B388
extern struct _TARGET *MissionTargets; // offset 0xAB07C
extern struct ACTIVE_CHEATS ActiveCheats; // offset 0xAAEF8
extern struct ACTIVE_CHEATS AvailableCheats; // offset 0xAAEFC
extern struct ANIMATED_OBJECT *Level_AnimatingObjectPtrs[4]; // offset 0x9B664
extern struct ANIMATED_OBJECT Lev0AnimObjects[9]; // offset 0x9B4F4
extern struct ANIMATED_OBJECT Lev1AnimObjects[5]; // offset 0x9B584
extern struct ANIMATED_OBJECT Lev2AnimObjects[5]; // offset 0x9B5D4
extern struct ANIMATED_OBJECT Lev3AnimObjects[4]; // offset 0x9B624
extern struct AreaDataStr *AreaData; // offset 0xAB24C
extern struct BLOCKINFO s_copyBlockInfo; // offset 0x10EE38
extern struct BONE Skel[23]; // offset 0xA0924
extern struct BOTCH botch[38]; // offset 0x1C6BB0
extern struct BOUND_BOX bbox[20]; // offset 0xD50E8
extern struct BOXINFO theBox; // offset 0xA03D0
extern struct CAR_COLLISION_BOX collision_box[8]; // offset 0xD96D8
extern struct CAR_COLLISION_BOX extra_collision_boxes[5]; // offset 0xD9668
extern struct CAR_COLLISION_BOX tanner_collision_box; // offset 0xD9648
extern struct CAR_COSMETICS car_cosmetics[5]; // offset 0xD4C48
extern struct CAR_COSMETICS src_cosmetics[20]; // offset 0x9F160
extern struct CAR_MODEL NewCarModel[5]; // offset 0xACBE0
extern struct CAR_MODEL NewLowCarModel[5]; // offset 0xB8838
extern struct CAR_POLY pbf[2001]; // offset 0xACCA0
extern struct CdlFILE currentfileinfo; // offset 0xE0B30
extern struct CELL_DATA *cells; // offset 0xAAF20
extern struct CELL_OBJECT **coplist; // offset 0xAB0C8
extern struct CELL_OBJECT *EventCop; // offset 0xAAE40
extern struct CELL_OBJECT cell_object_buffer[1024]; // offset 0xB90F8
extern struct CELL_OBJECT ground_debris[16]; // offset 0xCD0D0
extern struct CHANNEL_DATA channels[16]; // offset 0xDE4F8
extern struct CHEATS cheats; // offset 0xD12C8
extern struct CIV_ROUTE_ENTRY *startNode; // offset 0xAABFC
extern struct CIV_ROUTE_ENTRY *tstNode1; // offset 0xAABD4
extern struct CIV_ROUTE_ENTRY *tstNode2; // offset 0xAABD8
extern struct ControllerPacket g_controllerData[2]; // offset 0x10EC9C
extern struct COP_DATA gCopData; // offset 0x9BFD4
extern struct COP_SIGHT_DATA copSightData; // offset 0xAAC40
extern struct CUTSCENE_BUFFER CutsceneBuffer; // offset 0xBD898
extern struct CVECTOR debris_colour[4][31]; // offset 0x9C098
extern struct CVECTOR otherCol; // offset 0x1C6CF8
extern struct CVECTOR scoreCol; // offset 0x1C6CF4
extern struct CYCLE_OBJECT *Lev_CycleObjPtrs[4]; // offset 0x9B4D4
extern struct CYCLE_OBJECT Lev0[2]; // offset 0x9B394
extern struct CYCLE_OBJECT Lev1[1]; // offset 0x9B3BC
extern struct CYCLE_OBJECT Lev2[12]; // offset 0x9B3D0
extern struct CYCLE_OBJECT Lev3[1]; // offset 0x9B4C0
extern struct DAMAGED_LAMP damaged_lamp[5]; // offset 0xC1BB0
extern struct DAMAGED_OBJECT damaged_object[9]; // offset 0xC2888
extern struct DB *current; // offset 0xAB318
extern struct DB *last; // offset 0xAB330
extern struct DB *MPcurrent[2]; // offset 0xAB328
extern struct DB *MPlast[2]; // offset 0xAB310
extern struct DB MPBuff[2][2]; // offset 0xE0930
extern struct DEBRIS debris[60]; // offset 0xC10F8
extern struct DENTUVS *gTempCarUVPtr; // offset 0xAB154
extern struct DENTUVS gTempHDCarUVDump[20][255]; // offset 0xCA020
extern struct DENTUVS gTempLDCarUVDump[20][134]; // offset 0xCB410
extern struct DISPENV load_disp; // offset 0xD56B8
extern struct DR_LOAD cyclecluts[12]; // offset 0xAB418
extern struct DR_MOVE In; // offset 0x1CC548
extern struct DR_MOVE Out; // offset 0x1CC568
extern struct DRAW_MODE draw_mode_ntsc; // offset 0xA1C30
extern struct DRAW_MODE draw_mode_pal; // offset 0xA1C20
extern struct DRAWENV load_draw; // offset 0xD5658
extern struct DRIVER2_CURVE *Driver2CurvesPtr; // offset 0xAAA8C
extern struct DRIVER2_CURVE *testCrv; // offset 0xAA1D4
extern struct DRIVER2_CURVE *tmpCrv[2]; // offset 0xAAB80
extern struct DRIVER2_JUNCTION *Driver2JunctionsPtr; // offset 0xAAAA4
extern struct DRIVER2_STRAIGHT *Driver2StraightsPtr; // offset 0xAAAA0
extern struct DRIVER2_STRAIGHT *tmpStr[2]; // offset 0xAAB90
extern struct DVECTOR *outvertices; // offset 0xAA98C
extern struct DVECTOR slot_clutpos[19]; // offset 0xE0D80
extern struct DVECTOR slot_tpagepos[19]; // offset 0xE0FD0
extern struct EventCarriage carriageData[10]; // offset 0xCDF70
extern struct EventGlobal events; // offset 0xCDF60
extern struct FE_FONT feFont; // offset 0x1CBDD0
extern struct FELONY_DATA felonyData; // offset 0xBD5D0
extern struct FELONY_VALUE initialFelonyValue[12]; // offset 0x9EE30
extern struct GARAGE_DOOR CurrentGarage; // offset 0xAB748
extern struct GEAR_DESC geard[2][4]; // offset 0x9EFC4
extern struct HUBCAP gHubcap; // offset 0xC9478
extern struct LAMP_STREAK Known_Lamps[21]; // offset 0xC0F00
extern struct LEAD_PARAMETERS LeadValues; // offset 0xECE90
extern struct LEAF leaf[50]; // offset 0xC1FC0
extern struct MATRIX *current_inv_matrix; // offset 0xAAD58
extern struct MATRIX *current_matrix; // offset 0xAAD4C
extern struct MATRIX aspect; // offset 0x9BFB4
extern struct MATRIX camera_matrix; // offset 0xACB68
extern struct MATRIX colour_matrix; // offset 0x9BF4C
extern struct MATRIX debris_mat; // offset 0xC0880
extern struct MATRIX face_camera; // offset 0xACB18
extern struct MATRIX face_camera_work; // offset 0x9BE3C
extern struct MATRIX frustrum_matrix; // offset 0xCC070
extern struct MATRIX inv_camera_matrix; // offset 0xACB48
extern struct MATRIX leaf_mat; // offset 0xC1D40
extern struct MATRIX light_matrix; // offset 0x9BF2C
extern struct MATRIX norot; // offset 0xC08A0
extern struct MATRIX save_colour_matrix; // offset 0xB88D8
extern struct MATRIX save_light_matrix; // offset 0xACC80
extern struct MATRIX shadowMatrix; // offset 0xCC8B0
extern struct MATRIX tempmatrix; // offset 0xA1904
extern struct MATRIX2 CompoundMatrix[64]; // offset 0xCD1E0
extern struct MATRIX2 matrixtable[64]; // offset 0xCC090
extern struct MENU_HEADER YesNoQuitHeader; // offset 0xA1680
extern struct MENU_HEADER YesNoRestartHeader; // offset 0xA166C
extern struct MISSION_DATA MissionEndData; // offset 0xD7698
extern struct MISSION_DATA MissionStartData; // offset 0xD75B0
extern struct MODEL *gBombModel; // offset 0xAA144
extern struct MODEL *gBoxModelPtr; // offset 0xAAF60
extern struct MODEL *gCarCleanModelPtr[5]; // offset 0xD5730
extern struct MODEL *gCarDamModelPtr[5]; // offset 0xD6F60
extern struct MODEL *gCarLowModelPtr[5]; // offset 0xD6F78
extern struct MODEL *gCleanWheelModelPtr; // offset 0xAAF94
extern struct MODEL *gDamWheelModelPtr; // offset 0xAAF58
extern struct MODEL *gFastWheelModelPtr; // offset 0xAAF78
extern struct MODEL *gHubcapModelPtr; // offset 0xAAFC4
extern struct MODEL *gPed1HeadModelPtr; // offset 0xAAF34
extern struct MODEL *gPed2HeadModelPtr; // offset 0xAAF38
extern struct MODEL *gPed3HeadModelPtr; // offset 0xAAF3C
extern struct MODEL *gPed4HeadModelPtr; // offset 0xAAF40
extern struct MODEL *gRotorPtr; // offset 0xAAFB4
extern struct MODEL *gTrailblazerConeModel; // offset 0xAAD88
extern struct MODEL *modelpointers[1536]; // offset 0xD5760
extern struct MODEL *pLodModels[1536]; // offset 0xDF130
extern struct MODEL *pmJerichoModels[6]; // offset 0xD9630
extern struct MODEL *pmTannerModels[17]; // offset 0xD9758
extern struct MR_MISSION Mission; // offset 0xD7C80
extern struct OUT_CELL_FILE_HEADER *cell_header; // offset 0xAAF50
extern struct OUT_FONTINFO fontinfo[128]; // offset 0xD9BE0
extern struct PACKED_CELL_OBJECT **pcoplist; // offset 0xAB0CC
extern struct PACKED_CELL_OBJECT *cell_objects; // offset 0xAAF6C
extern struct PACKED_CELL_OBJECT *spriteList[75]; // offset 0xCBF40
extern struct PAD Pads[2]; // offset 0xD9330
extern struct PED_DATA MainPed[23]; // offset 0xA0810
extern struct PEDESTRIAN *pDrawingPed; // offset 0xAB09C
extern struct PEDESTRIAN *pFreePeds; // offset 0xAB128
extern struct PEDESTRIAN *pHold; // offset 0xAB144
extern struct PEDESTRIAN *pPlayerPed; // offset 0xAB10C
extern struct PEDESTRIAN *pUsedPeds; // offset 0xAB12C
extern struct PEDESTRIAN pedestrians[28]; // offset 0xD8430
extern struct PEDESTRIAN_ROADS pedestrian_roads; // offset 0xD9658
extern struct PLAYBACKCAMERA *CutsceneCamera; // offset 0xAA260
extern struct PLAYBACKCAMERA *LastChange; // offset 0xAA450
extern struct PLAYBACKCAMERA *NextChange; // offset 0xAA448
extern struct PLAYBACKCAMERA *PlaybackCamera; // offset 0xAAD38
extern struct PLAYBACKCAMERA *ThisChange; // offset 0xAA44C
extern struct PLAYER_SCORE gPlayerScore; // offset 0xDA980
extern struct POLY_F3 *spolys; // offset 0xAB180
extern struct POLY_FT3 extraDummy; // offset 0x1CBDB0
extern struct POLY_FT3 HighlightDummy; // offset 0x1CC5A0
extern struct POLY_FT3 ScreenDummy[8]; // offset 0x1CC260
extern struct POLY_FT4 BackgroundPolys[6]; // offset 0x1CBCB8
extern struct POLY_FT4 ft4TannerShadow[2]; // offset 0xD91D0
extern struct POLY_FT4 ScreenPolys[8]; // offset 0x1CC360
extern struct POLY_FT4 shadowPolys[2][20]; // offset 0xDAA58
extern struct POLYFT4 gPoolPoly; // offset 0xC29E0
extern struct POLYFT4 ShadowPolygon; // offset 0xDCCD8
extern struct PSXBUTTON *pButtonStack[10]; // offset 0xD0620
extern struct PSXBUTTON *pCurrButton; // offset 0x1CC540
extern struct PSXBUTTON *pNewButton; // offset 0x1CBCB0
extern struct PSXSCREEN *pCurrScreen; // offset 0x1CC25C
extern struct PSXSCREEN *pNewScreen; // offset 0x1C6D40
extern struct PSXSCREEN *pScreenStack[10]; // offset 0xD05F8
extern struct PSXSCREEN PsxScreens[42]; // offset 0x1C6D48
extern struct RAIN_TYPE gRain[180]; // offset 0xC2BA0
extern struct RECT clutpos; // offset 0xAB368
extern struct RECT fontclutpos; // offset 0xAB160
extern struct RECT g_strActiveMouseArea; // offset 0x10EC78
extern struct RECT mapclutpos; // offset 0xAB348
extern struct RECT rectTannerWindow; // offset 0xAB0B0
extern struct RECT storeRect; // offset 0x1C6A90
extern struct RECT tpage; // offset 0xAB338
extern struct REPLAY_PARAMETER_BLOCK *ReplayParameterPtr; // offset 0xAAAEC
extern struct REPLAY_STREAM ReplayStreams[8]; // offset 0xAC700
extern struct ROAD_MAP_LUMP_DATA roadMapLumpData; // offset 0xDA100
extern struct ROADBLOCK Roadblock; // offset 0xAC920
extern struct S_XYZ *distance; // offset 0xAA984
extern struct SAMPLE_DATA samples[7][35]; // offset 0xDD598
extern struct SCORE_TABLES ScoreTables; // offset 0xDA110
extern struct SCREEN_LIMITS screen_limits[2]; // offset 0x1C6984
extern struct SEATED_PEDESTRIANS *seated_pedestrian; // offset 0xAB120
extern struct SHADOWHDR *shadow_header; // offset 0xAB18C
extern struct SMASHABLE_OBJECT smashable[38]; // offset 0x9B6A4
extern struct SMOKE *smoke_table; // offset 0xAACA4
extern struct SMOKE smoke[80]; // offset 0xBF980
extern struct SPEECH_QUEUE gSpeechQueue; // offset 0xD01F8
extern struct SPL_REGIONINFO spool_regioninfo[8]; // offset 0xDED10
extern struct SPOOLQ spooldata[48]; // offset 0xDEE30
extern struct SPRT extraSprt; // offset 0x1CC5C0
extern struct SPRT HighlightSprt; // offset 0x1CC588
extern struct SPRT ScreenSprts[8]; // offset 0x1CC4A0
extern struct SpuReverbAttr xm_r_attr; // offset 0xE2360
extern struct SpuVoiceAttr uxm_g_s_attr; // offset 0xE2320
extern struct SpuVoiceAttr xm_g_s_attr; // offset 0xE1280
extern struct STOPCOPS gStopCops; // offset 0xD7CF0
extern struct STREAM_SOURCE *PlayerStartInfo[8]; // offset 0xBD878
extern struct SVECTOR *rotated; // offset 0xAA980
extern struct SVECTOR camera_angle; // offset 0xAA158
extern struct SVECTOR camverts[128]; // offset 0xDCCF0
extern struct SVECTOR carDisplayOffset; // offset 0xAA1A0
extern struct SVECTOR day_colours[4]; // offset 0x9BEEC
extern struct SVECTOR day_vectors[4]; // offset 0x9BEAC
extern struct SVECTOR debris_rotvec; // offset 0xAACD8
extern struct SVECTOR delta; // offset 0xAAEC0
extern struct SVECTOR globemesh[54]; // offset 0xD52E8
extern struct SVECTOR gTempCarVertDump[20][132]; // offset 0xC41F8
extern struct SVECTOR leaf_rotvec; // offset 0xAACA8
extern struct SVECTOR moon_position[4]; // offset 0xA19AC
extern struct SVECTOR night_colours[4]; // offset 0x9BF0C
extern struct SVECTOR night_vectors[4]; // offset 0x9BECC
extern struct SVECTOR sun_position[4]; // offset 0xA198C
extern struct SVECTOR vJerichoList[102]; // offset 0xD8EA0
extern struct SVECTOR vTannerList[210]; // offset 0xD7DA0
extern struct SVECTOR_NOPAD *svTemp; // offset 0xAB0A8
extern struct SXYPAIR *Music_And_AmbientOffsets; // offset 0xAB28C
extern struct SXYPAIR *PlayerWayRecordPtr; // offset 0xAAAE8
extern struct SXYPAIR tpagepos[20]; // offset 0xA1EA0
extern struct TEXINF *tpage_ids[128]; // offset 0xE1020
extern struct TEXTURE_DETAILS addcam; // offset 0xC0A50
extern struct TEXTURE_DETAILS arm1_texture; // offset 0xC1BF8
extern struct TEXTURE_DETAILS autocam; // offset 0xC1CA0
extern struct TEXTURE_DETAILS bird_texture1; // offset 0xC1D90
extern struct TEXTURE_DETAILS bird_texture2; // offset 0xC1DA0
extern struct TEXTURE_DETAILS chasecar; // offset 0xC1D60
extern struct TEXTURE_DETAILS chest1_texture; // offset 0xC2A18
extern struct TEXTURE_DETAILS choosecar; // offset 0xC2A08
extern struct TEXTURE_DETAILS clock; // offset 0xBF940
extern struct TEXTURE_DETAILS collon_texture; // offset 0xBF8C8
extern struct TEXTURE_DETAILS cop_texture; // offset 0xC1B80
extern struct TEXTURE_DETAILS cross_texture; // offset 0xC2878
extern struct TEXTURE_DETAILS cycle_tex[12]; // offset 0xAB778
extern struct TEXTURE_DETAILS debris_texture; // offset 0xC39B0
extern struct TEXTURE_DETAILS delcam; // offset 0xC0EE0
extern struct TEXTURE_DETAILS digit_texture; // offset 0xC1F60
extern struct TEXTURE_DETAILS drop_texture; // offset 0xC1CF0
extern struct TEXTURE_DETAILS editcam; // offset 0xC1BE8
extern struct TEXTURE_DETAILS fixedcam; // offset 0xC1D70
extern struct TEXTURE_DETAILS flare_texture; // offset 0xC1F50
extern struct TEXTURE_DETAILS forearm1_texture; // offset 0xC1AF8
extern struct TEXTURE_DETAILS frameadv; // offset 0xC1D80
extern struct TEXTURE_DETAILS gTyreTexture; // offset 0xC1CC0
extern struct TEXTURE_DETAILS head1_texture; // offset 0xC1D30
extern struct TEXTURE_DETAILS incar; // offset 0xBF950
extern struct TEXTURE_DETAILS jeans_texture; // offset 0xC1F70
extern struct TEXTURE_DETAILS joypad_texture; // offset 0xBF8B8
extern struct TEXTURE_DETAILS lenschan; // offset 0xC1DB0
extern struct TEXTURE_DETAILS lensflare_texture; // offset 0xC1D20
extern struct TEXTURE_DETAILS light_pool_texture; // offset 0xC29F8
extern struct TEXTURE_DETAILS light_texture; // offset 0xC1F90
extern struct TEXTURE_DETAILS lightref_texture; // offset 0xC1BA0
extern struct TEXTURE_DETAILS line_texture; // offset 0xC1CE0
extern struct TEXTURE_DETAILS litter_texture; // offset 0xBF960
extern struct TEXTURE_DETAILS lookcar; // offset 0xC1CB0
extern struct TEXTURE_DETAILS moon_texture; // offset 0xC1D00
extern struct TEXTURE_DETAILS movecam; // offset 0xC1C18
extern struct TEXTURE_DETAILS movecampos; // offset 0xC08C0
extern struct TEXTURE_DETAILS ok; // offset 0xC1BD8
extern struct TEXTURE_DETAILS pad_texture; // offset 0xC1B08
extern struct TEXTURE_DETAILS paper_texture; // offset 0xC1FA0
extern struct TEXTURE_DETAILS pause; // offset 0xBF970
extern struct TEXTURE_DETAILS playcam; // offset 0xC1C08
extern struct TEXTURE_DETAILS playpause; // offset 0xC2A28
extern struct TEXTURE_DETAILS pool_texture; // offset 0xC1D10
extern struct TEXTURE_DETAILS restart; // offset 0xC1CD0
extern struct TEXTURE_DETAILS save2card; // offset 0xC1F40
extern struct TEXTURE_DETAILS sea_texture; // offset 0xC1B18
extern struct TEXTURE_DETAILS smoke_texture; // offset 0xC2858
extern struct TEXTURE_DETAILS spark_texture; // offset 0xC2868
extern struct TEXTURE_DETAILS sun_texture; // offset 0xC1B90
extern struct TEXTURE_DETAILS tannerShadow_texture; // offset 0xC0EF0
extern struct TEXTURE_DETAILS texturePedHead; // offset 0xC29D0
extern struct TEXTURE_DETAILS trail_texture; // offset 0xC1FB0
extern struct TEXTURE_DETAILS watch_texture; // offset 0xC1F80
extern struct TILE tileTannerClear[2]; // offset 0xD7D00
extern struct tNode dbb[3]; // offset 0xE9AD0
extern struct tNode heap[201]; // offset 0xF1B08
extern struct TP *tpage_position; // offset 0xAB388
extern struct TRAILBLAZER_DATA *gTrailblazerData; // offset 0xAA4B0
extern struct TRI_POINT *debris_rot_table[5]; // offset 0x9C084
extern struct TRI_POINT debris_rot1[32]; // offset 0xC0A60
extern struct TRI_POINT debris_rot2[32]; // offset 0xC0BE0
extern struct TRI_POINT debris_rot3[32]; // offset 0xC0D60
extern struct TRI_POINT leaf_rot[32]; // offset 0xC1DC0
extern struct TRI_POINT litter_rot[32]; // offset 0xC08D0
extern struct TRI_POINT_LONG *debris_data[5]; // offset 0x9C33C
extern struct TRI_POINT_LONG debris1_vert; // offset 0x9C288
extern struct TRI_POINT_LONG debris2_vert; // offset 0x9C2AC
extern struct TRI_POINT_LONG debris3_vert; // offset 0x9C318
extern struct TRI_POINT_LONG leaf_vert; // offset 0x9C2D0
extern struct TRI_POINT_LONG litter_vert; // offset 0x9C2F4
extern struct TYRE_TRACK track_buffer[4][64]; // offset 0xDB0A8
extern struct UV shadowuv; // offset 0xAB190
extern struct VECTOR *current_offset; // offset 0xAAD64
extern struct VECTOR *pos; // offset 0xAA988
extern struct VECTOR bangPos; // offset 0xD52D8
extern struct VECTOR baseLoc; // offset 0xBD520
extern struct VECTOR camera_position; // offset 0x9BE2C
extern struct VECTOR CameraPos; // offset 0x9BE1C
extern struct VECTOR CarTail; // offset 0xBD678
extern struct VECTOR current_camera_position; // offset 0xCD1D0
extern struct VECTOR currentPos; // offset 0xBD4B0
extern struct VECTOR direction; // offset 0xDD130
extern struct VECTOR dummy; // offset 0xA18E4
extern struct VECTOR endPos; // offset 0xBD4C0
extern struct VECTOR frustpos; // offset 0xA18F4
extern struct VECTOR gMissionDoorPosition; // offset 0x9B694
extern struct VECTOR GuitarPos; // offset 0xAB768
extern struct VECTOR lastKnownPosition; // offset 0xBD688
extern struct VECTOR leadcar_pos; // offset 0xD5720
extern struct VECTOR lis_pos; // offset 0xDE4E8
extern struct VECTOR randomLoc; // offset 0xBD578
extern struct VECTOR roadblockLoc; // offset 0xBD530
extern struct VECTOR searchTarget; // offset 0xE9AB8
extern struct VECTOR ShadowPos; // offset 0xCA010
extern struct VECTOR startPos; // offset 0xBD550
extern struct VECTOR tannerLookAngle; // offset 0xA1710
extern struct VECTOR targetPoint; // offset 0xBD668
extern struct VECTOR testVec; // offset 0xBD540
extern struct VECTOR tunnel_dim[12]; // offset 0x9C50C
extern struct VECTOR tunnelPos[3][2]; // offset 0xA1A64
extern struct VECTOR tyre_new_positions[4]; // offset 0xDD0F0
extern struct VECTOR tyre_save_positions[4]; // offset 0xDAA08
extern struct VECTOR viewer_position; // offset 0xACB38
extern struct VERTEX vtab[8]; // offset 0xCD9E0
extern struct XA_TRACK XAMissionMessages[4]; // offset 0xE1240
extern struct XMCHANNEL *XMC; // offset 0xAB3D4
extern struct XMCHANNEL *XMCU; // offset 0xAB3E4
extern struct XMHEADER *mh; // offset 0xAB3C0
extern struct XMHEADER *mhu; // offset 0xAB3E8
extern struct XMSONG *ms; // offset 0xAB3C4
extern struct XMSONG *mu; // offset 0xAB3C8
extern struct XYPAIR *permlist; // offset 0xAB374
extern struct XYPAIR *speclist; // offset 0xAB370
extern struct XYPAIR citylumps[8][4]; // offset 0xE0B68
extern unsigned char *AreaTPages; // offset 0xAB2B4
extern unsigned char *XM_HeaderAddress[8]; // offset 0xE1260
extern unsigned char *XM_SngAddress[24]; // offset 0xE12C0
extern unsigned char cell_object_computed_values[2048]; // offset 0xB88F8
extern unsigned char defaultPlayerModel[2]; // offset 0xAA664
extern unsigned char defaultPlayerPalette; // offset 0xAA666
extern unsigned char gCarDamageZoneVerts[5][6][50]; // offset 0xC9A30
extern unsigned char gHDCarDamageLevels[5][255]; // offset 0xC9530
extern unsigned char gHDCarDamageZonePolys[5][6][70]; // offset 0xC39C0
extern unsigned char grassColour[4][3]; // offset 0x9C350
extern unsigned char lead_analogue; // offset 0xAAF84
extern unsigned char lightsOnDelay[20]; // offset 0xD5748
extern unsigned char LoadedLevel; // offset 0xAA614
extern unsigned char reservedSlots[20]; // offset 0xBD560
extern unsigned char tpageloaded[128]; // offset 0xE0C80
extern unsigned char tpageslots[19]; // offset 0xE0C68
extern unsigned int brakeLength[20]; // offset 0xBD4D0
extern unsigned int cellsPerFrame; // offset 0xE9138
extern unsigned int cellsThisFrame; // offset 0xF2798
extern unsigned int collDat; // offset 0xAAB9C
extern unsigned int farClip2Player; // offset 0xAA474
extern unsigned int g_nCManOptions; // offset 0x10EE08
extern unsigned int numHeapEntries; // offset 0xF279C
extern unsigned int ObjectDrawnValue; // offset 0xAAF44
extern unsigned long *Driver2TempJunctionsPtr; // offset 0xAB070
extern unsigned long *MissionScript; // offset 0xAB074
extern unsigned long *ot_slot; // offset 0xAAD78
extern unsigned long *oTablePtr; // offset 0x10EC74
extern unsigned long *outcoords; // offset 0xAA990
extern unsigned long *tile_overflow_buffer; // offset 0xAAD68
extern unsigned long *transparent_buffer; // offset 0xAAD54
extern unsigned long anim_obj_buffer[20]; // offset 0xCBEF0
extern unsigned long gUnderIntensity; // offset 0xAAB24
extern unsigned long lead_pad; // offset 0xAAF7C
extern unsigned long mcgn; // offset 0xAAC20
extern unsigned long model_object_ptrs[512]; // offset 0xCC8D0
extern unsigned long PingBufferPos; // offset 0xAAAE4
extern unsigned long planeColours[8]; // offset 0xCC890
extern unsigned long srgn; // offset 0xAAC24
extern unsigned long tannerPad; // offset 0xAB134
extern unsigned long unpack_cellptr_tbl[3]; // offset 0xDEE10
extern unsigned long unpack_roadmap_tbl[2]; // offset 0xAB280
extern unsigned long xm_l_vag_spu_addr[8][128]; // offset 0xE1320
extern unsigned short *cell_ptrs; // offset 0xAAFBC
extern unsigned short *Low2HighDetailTable; // offset 0xAAD7C
extern unsigned short *Low2LowerDetailTable; // offset 0xAAD80
extern unsigned short *newmodels; // offset 0xAB2D8
extern unsigned short *spoolinfo_offsets; // offset 0xAB274
extern unsigned short cd_palette[32]; // offset 0xDECD0
extern unsigned short civ_clut[8][32][6]; // offset 0xABB00
extern unsigned short controller_bits; // offset 0xAAF48
extern unsigned short distanceCache[16384]; // offset 0xE9B00
extern unsigned short edgecount; // offset 0xAB198
extern unsigned short edgelist[16]; // offset 0xDCCB8
extern unsigned short g_PAD_FLB; // offset 0x10EC82
extern unsigned short g_PAD_FLT; // offset 0x10EC86
extern unsigned short g_PAD_FRB; // offset 0x10EC80
extern unsigned short g_PAD_FRT; // offset 0x10EC84
extern unsigned short g_PAD_LD; // offset 0x10EC92
extern unsigned short g_PAD_LL; // offset 0x10EC94
extern unsigned short g_PAD_LR; // offset 0x10EC96
extern unsigned short g_PAD_LU; // offset 0x10EC90
extern unsigned short g_PAD_RD; // offset 0x10EC8A
extern unsigned short g_PAD_RL; // offset 0x10EC8C
extern unsigned short g_PAD_RR; // offset 0x10EC8E
extern unsigned short g_PAD_RU; // offset 0x10EC88
extern unsigned short g_PAD_SEL; // offset 0x10EC98
extern unsigned short g_PAD_START; // offset 0x10EC9A
extern unsigned short gChannel; // offset 0xAAA54
extern unsigned short gLastModelCollisionCheck; // offset 0xAB0D0
extern unsigned short gMemCardMode; // offset 0xAB40C
extern unsigned short lintab[768]; // offset 0xA2008
extern unsigned short logtab[104]; // offset 0xA2608
extern unsigned short nextindex; // offset 0xAB19A
extern unsigned short paddCamera; // offset 0xAAB1C
static char *button_names[11]; // offset 0xA18B8
static char *carSelectPlayerText[2]; // offset 0x1C6764
static char *carSelectPlayerText[2]; // offset 0xAA6FC
static char *cheatText[5]; // offset 0x1C686C
static char *cheatText[5]; // offset 0xA06A8
static char *current_address; // offset 0xAB300
static char *CutSceneNames[28]; // offset 0x1C6880
static char *CutSceneNames[28]; // offset 0xA06BC
static char *CutsceneReplayStart; // offset 0xAA230
static char *gameNames[64]; // offset 0x1C676C
static char *gameNames[64]; // offset 0xA05A8
static char *MapBitMaps; // offset 0xAAAC0
static char *MCbuffer128K; // offset 0xAB3F4
static char *MCfilename; // offset 0xAB400
static char *MClanguageBuffer; // offset 0xAB3F8
static char *MCsaveBuffer; // offset 0xAB3FC
static char *MissionLoadAddress; // offset 0xAA738
static char *MissionName[37]; // offset 0x1C68F0
static char *MissionName[37]; // offset 0xA072C
static char *palletedir[8]; // offset 0x9BAF4
static char *target_address; // offset 0xAB1E0
static char AnalogueUnpack[16]; // offset 0x9BBC4
static char banks[24]; // offset 0xDD430
static char cop_bank; // offset 0xAAEA1
static char cop_model; // offset 0xAAEA0
static char EnterNameText[32]; // offset 0xD93E0
static char GreyIcons[24]; // offset 0xCBE88
static char header_pt[3868]; // offset 0xCE728
static char loseTailTargetArrowTris[24]; // offset 0xA1E24
static char MapBuffer[520]; // offset 0xAB8C0
static char maptile[4][4]; // offset 0xABAD0
static char maxSpeedTargetArrowTris[18]; // offset 0xA1E5C
static char menu0[2]; // offset 0x9C4DC
static char menu1[10]; // offset 0x9C4E0
static char menu2[5]; // offset 0x9C4EC
static char menu3[2]; // offset 0x9C4F4
static char menu4[2]; // offset 0x9C4F8
static char menu5[5]; // offset 0x9C4FC
static char menu6[7]; // offset 0x9C504
static char missionstarts[42]; // offset 0xA047C
static char MusicVolumeText[8]; // offset 0xAB0F0
static char NewLeadDelay; // offset 0xAA740
static char normalTargetArrowTris[9]; // offset 0xA1E18
static char omap[128][16]; // offset 0xE91A8
static char padbuffer[2][34]; // offset 0xD92E8
static char ScoreItems[5][16]; // offset 0xD9430
static char ScoreName[5][7]; // offset 0xD9400
static char ScoreTime[5][16]; // offset 0xD9480
static char SfxVolumeText[8]; // offset 0xAB0E8
static char song_pt[2992]; // offset 0xCF648
static char sqtbl[65]; // offset 0x9C018
static char tile_size; // offset 0xAA0DC
static char validchars[39]; // offset 0x10EE0C
static char validchars[68]; // offset 0xA1694
static char windowTargetArrowTris[30]; // offset 0xA1E3C
static enum CITYTYPE lastcity; // offset 0xAAA19
static enum CITYTYPE lasttype; // offset 0xAAA18
static enum PAUSEMODE PauseMode; // offset 0xAAF18
static int ActiveMenuItem; // offset 0xAB0E0
static int alleycount; // offset 0xAA488
static int allownameentry; // offset 0xAA860
static int BlackBorderHeight; // offset 0xAA258
static int bodgevar; // offset 0xAB038
static int bWantFade; // offset 0xAA600
static int cameraEventsActive; // offset 0xAADE4
static int cammapht2; // offset 0xAAD0C
static int carsOnBoat; // offset 0xAADF0
static int ChicagoCameraHack[3]; // offset 0x9ED6C
static int cop_adjust; // offset 0xAA73C
static int copmusic; // offset 0xAA580
static int current_sector; // offset 0xAB1E4
static int current_sector; // offset 0xAB2F4
static int current_smashed_cone; // offset 0xAA4A8
static int CurrentBomb; // offset 0xAA130
static int cutscene_timer; // offset 0xAB030
static int CutsceneCameraOffset; // offset 0xAA23C
static int CutsceneInReplayBuffer; // offset 0xAA25C
static int CutsceneLength; // offset 0xAA254
static int CutsceneStreamIndex; // offset 0xAA234
static int doneFirstHavanaCameraHack; // offset 0xAAE18
static int endchunk; // offset 0xAB20C
static int eventHaze; // offset 0xAA51C
static int fadeVal; // offset 0xAA604
static int flashtimer; // offset 0xAA0E0
static int flashval; // offset 0xAA140
static int fullStrike; // offset 0xAA134
static int gCSDestroyPlayer; // offset 0xAA250
static int gDieWithFade; // offset 0xAA60C
static int gEnteringScore; // offset 0xAA83C
static int gHaveInGameCutscene; // offset 0xAA24C
static int gLastChase; // offset 0xAA594
static int gPlaying; // offset 0xAAA50
static int gScoreEntered; // offset 0xAA844
static int gScorePosition; // offset 0xAA840
static int gTrailblazerPrevConeDelay; // offset 0xAA4AC
static int gUseRotatedMap; // offset 0xAA0BC
static int gWantFlash; // offset 0xAA13C
static int halfStrike; // offset 0xAA138
static int HavanaCameraHack[9]; // offset 0x9ED78
static int holdall; // offset 0xAB034
static int hSubShad; // offset 0xAAEB8
static int last_flag; // offset 0xAA748
static int lastcv; // offset 0xAB17C
static int lastrequesteddisc; // offset 0xAA4C8
static int lastsay; // offset 0xAA74C
static int load_steps; // offset 0xAAF04
static int loading_bar_pos; // offset 0xAAF00
static int loudhail_time; // offset 0xAAE9C
static int map_x_offset; // offset 0xAA0C0
static int map_z_offset; // offset 0xAA0C4
static int mapstuff; // offset 0xAAD10
static int master_volume; // offset 0xAA9C8
static int MCoptions; // offset 0xAB404
static int ntpages; // offset 0xAB208
static int nTPchunks; // offset 0xAB1F4
static int nTPchunks_reading; // offset 0xAB1F8
static int nTPchunks_writing; // offset 0xAB1FC
static int num_pedestrians; // offset 0xAA8B4
static int numCopPeds; // offset 0xAA8F4
static int NumCutsceneStreams; // offset 0xAA238
static int numcv; // offset 0xAB178
static int numTannerPeds; // offset 0xAA8B8
static int old_x_mod; // offset 0xAA0D0
static int old_y_mod; // offset 0xAA0D4
static int oldCamView; // offset 0xAB0FC
static int oldDir; // offset 0xAB108
static int pathParams[5]; // offset 0xECBE8
static int PauseReturnValue; // offset 0xAB0E4
static int playerwithcontrol[3]; // offset 0xA1660
static int plotted; // offset 0xAAC94
static int PreLoadedCutscene; // offset 0xAA248
static int prevCopsInPursuit; // offset 0xAA744
static int pvsSize[4]; // offset 0xA1AD0
static int randIndex; // offset 0xECD34
static int randomcounter; // offset 0xAAC18
static int randomindex; // offset 0xAAC1C
static int randState[17]; // offset 0xECCF0
static int rio_alarm; // offset 0xAB03C
static int RioCameraHack[6]; // offset 0x9EDDC
static int said_picked_up; // offset 0xAAC28
static int SavedCameraAngle; // offset 0xAAC70
static int SavedCameraCarId; // offset 0xAAC68
static int SavedCameraView; // offset 0xAAC6C
static int SavedWorldCentreCarId; // offset 0xAAC74
static int sectors_left; // offset 0xAB2F8
static int sectors_read; // offset 0xAB2FC
static int sectors_this_chunk; // offset 0xAB1EC
static int sectors_to_read; // offset 0xAB1E8
static int sky_y_offset[4]; // offset 0xA1944
static int skycolour; // offset 0xAB1A4
static int sound_paused; // offset 0xAA9C0
static int StartPos; // offset 0xAB39C
static int stop_sound_handler; // offset 0xAA9CC
static int storedCam; // offset 0xAB0F8
static int switch_spooltype; // offset 0xAB1F0
static int TestCnt; // offset 0xAAAD8
static int ThrownBombDelay; // offset 0xAA12C
static int ThunderDistance; // offset 0xAAC90
static int ThunderTimer; // offset 0xAAC8C
static int tilehnum; // offset 0xAA0D8
static int treecount; // offset 0xAA48C
static int VegasCameraHack[16]; // offset 0x9ED9C
static int VisibleMenu; // offset 0xAB0D8
static int WantPause; // offset 0xAA608
static int wrongside[2][6]; // offset 0xCDA20
static int x_map; // offset 0xAA0C8
static int xa_prepared; // offset 0xAAA58
static int y_map; // offset 0xAA0CC
static long banksize[2]; // offset 0xAA9B8
static long baseDir; // offset 0xAAB10
static long basePos[3]; // offset 0xACB08
static long civrseed[17]; // offset 0xBD1C8
static long pos[4]; // offset 0xD75A0
static long rseed[17]; // offset 0xBD588
static long skyblue; // offset 0xAA99C
static long skygreen; // offset 0xAA998
static long skyred; // offset 0xAA994
static short big_north[4]; // offset 0x9BADC
static short skyclut[28]; // offset 0xDD2C0
static short skytpage[28]; // offset 0xDD280
static struct __envsound envsnd[32]; // offset 0xCDF98
static struct __envsoundinfo ESdata[2]; // offset 0xCE598
static struct __envsoundtags EStags; // offset 0xCE6C8
static struct __io id_map[49]; // offset 0xA04A8
static struct __othercarsound car_noise[4]; // offset 0xCE6D8
static struct __othercarsound siren_noise[2]; // offset 0xCE708
static struct __pauseinfo musps; // offset 0xDD530
static struct __pauseinfo pause; // offset 0xDD4C0
static struct __xa_request xa; // offset 0xAB040
static struct __xa_request xa_data[26]; // offset 0xA050C
static struct _CAR_DATA *horncarflag[2]; // offset 0xAA1CC
static struct _EVENT *event; // offset 0xAADE0
static struct _EVENT *firstMissionEvent; // offset 0xAAE0C
static struct _EVENT *trackingEvent[2]; // offset 0xAADE8
static struct _TARGET *carEvent[8]; // offset 0xCDF08
static struct BOMB ThrownBombs[5]; // offset 0xACA50
static struct CameraDelay cameraDelay; // offset 0xAAE20
static struct CDATA2D cd[2]; // offset 0xBD0F8
static struct CDATA2D cd[2]; // offset 0xD9220
static struct CDATA2D cd[2]; // offset 0xD9568
static struct CdlLOC pause_loc; // offset 0xAB3A0
static struct COLOUR_BAND damageColour[2]; // offset 0x9B9E4
static struct COLOUR_BAND felonyColour[3]; // offset 0x9B99C
static struct COLOUR_BAND playerDamageColour[3]; // offset 0x9B9C0
static struct CVECTOR gFontColour; // offset 0xAB158
static struct Detonator detonator; // offset 0xAAE10
static struct DUPLICATION DuplicatePadData; // offset 0xAA82C
static struct EventCamera eventCamera; // offset 0xCDF28
static struct FILEFORMAT fileFormat; // offset 0xA26F8
static struct FixedEvent *fixedEvent; // offset 0xAAE08
static struct FixedEvent chicagoDoor[3]; // offset 0x9E974
static struct FixedEvent havanaFixed[3]; // offset 0x9E9F8
static struct FixedEvent rioDoor[6]; // offset 0x9EB58
static struct FixedEvent vegasDoor[5]; // offset 0x9EA7C
static struct FLAREREC flare_info[8]; // offset 0xA19EC
static struct Foam foam; // offset 0xAADD8
static struct FONT_DIGIT fontDigit[12]; // offset 0xA18A0
static struct Helicopter HelicopterData; // offset 0x9EC60
static struct MATRIX map_matrix; // offset 0xABAE0
static struct MATRIX SS; // offset 0xA041C
static struct MENU_HEADER *ActiveMenu; // offset 0xAB0DC
static struct MENU_HEADER *VisibleMenus[3]; // offset 0xD93C0
static struct MENU_HEADER ChaseGameFinishedHeader; // offset 0xA15FC
static struct MENU_HEADER CutscenePauseMenuHeader; // offset 0xA1584
static struct MENU_HEADER DrivingDebugHeader; // offset 0xD94D0
static struct MENU_HEADER DrivingGameFinishedHeader; // offset 0xA15D4
static struct MENU_HEADER InvalidMultiPadHeader; // offset 0xA164C
static struct MENU_HEADER InvalidPadHeader; // offset 0xA1638
static struct MENU_HEADER MissionCompleteHeader; // offset 0xA1598
static struct MENU_HEADER MissionFailedHeader; // offset 0xA15AC
static struct MENU_HEADER MultiplayerFinishedHeader; // offset 0xA15E8
static struct MENU_HEADER MultiplayerPauseHeader; // offset 0xA1570
static struct MENU_HEADER NoMultiPadHeader; // offset 0xA1624
static struct MENU_HEADER NoPadHeader; // offset 0xA1610
static struct MENU_HEADER PauseMenuHeader; // offset 0xA155C
static struct MENU_HEADER TakeARideFinishedHeader; // offset 0xA15C0
static struct MENU_ITEM *ActiveItem[3]; // offset 0xD93D0
static struct MENU_ITEM ChaseGameFinishedItems[6]; // offset 0xA13F4
static struct MENU_ITEM CutscenePauseItems[6]; // offset 0xA10FC
static struct MENU_ITEM DrivingGameFinishedItems[7]; // offset 0xA1304
static struct MENU_ITEM InvalidMultiPadItems[2]; // offset 0xA1534
static struct MENU_ITEM InvalidPadItems[1]; // offset 0xA1520
static struct MENU_ITEM MainPauseItems[9]; // offset 0xA0FBC
static struct MENU_ITEM MissionCompleteItems[8]; // offset 0xA1174
static struct MENU_ITEM MissionFailedItems[6]; // offset 0xA1214
static struct MENU_ITEM MultiplayerFinishedItems[5]; // offset 0xA1390
static struct MENU_ITEM MultiplayerPauseItems[7]; // offset 0xA1070
static struct MENU_ITEM NoMultiPadItems[2]; // offset 0xA14F8
static struct MENU_ITEM NoPadItems[1]; // offset 0xA14E4
static struct MENU_ITEM TakeARideFinishedItems[6]; // offset 0xA128C
static struct MENU_ITEM YesNoQuitItems[3]; // offset 0xA14A8
static struct MENU_ITEM YesNoRestartItems[3]; // offset 0xA146C
static struct MISSION_STEP MissionLadder[68]; // offset 0x9F084
static struct MissionTrain missionTrain[2]; // offset 0x9E93C
static struct MODEL dummyModel; // offset 0xDECA8
static struct MR_THREAD MissionThreads[16]; // offset 0xD7B80
static struct MultiCar multiCar; // offset 0xAAE00
static struct OVERMAP overlaidmaps[4]; // offset 0x9B9FC
static struct PLAYBACKCAMERA *CutLastChange; // offset 0xAA244
static struct PLAYBACKCAMERA *CutNextChange; // offset 0xAA240
static struct POLY_FT4 cd_sprite; // offset 0x1C6D18
static struct POLY_FT4 cd_sprite; // offset 0xDEC78
static struct POLY_G4 fade_g4[2]; // offset 0xD5610
static struct POLY_GT4 fade_gt4[2]; // offset 0xD55A0
static struct POLYCOORD polycoords[6]; // offset 0x9E6DC
static struct RECT MapRect; // offset 0xAAAC8
static struct RECT tpage; // offset 0xAB200
static struct REPLAY_ICON replay_icons[23]; // offset 0x9C36C
static struct SLICE slice; // offset 0xA284C
static struct SMASHED_CONE smashed_cones[6]; // offset 0xCDA50
static struct SpuCommonAttr sound_attr; // offset 0xDD490
static struct SVECTOR boatOffset; // offset 0xAADF8
static struct SVECTOR camAngle; // offset 0xAB100
static struct SVECTOR cv[12]; // offset 0xDA9A8
static struct SVECTOR moon_shadow_position[4]; // offset 0xA19CC
static struct SVECTOR targetArrowVerts[43]; // offset 0xA1CC0
static struct SXYPAIR MapSegmentPos[16]; // offset 0x9BA5C
static struct TARGET_ARROW_MODEL targetArrowModel[4]; // offset 0xA1E70
static struct TEXTURE_DETAILS button_textures[11]; // offset 0xD9B40
static struct UV skytexuv[28]; // offset 0xDD300
static struct VECTOR *SavedSpoolXZ; // offset 0xAAC78
static struct VECTOR Drift; // offset 0xA040C
static struct VECTOR player_position; // offset 0x9BAE4
static struct VECTOR SmokePos; // offset 0xD52C8
static struct XYPAIR north[4]; // offset 0x9BABC
static struct XYPAIR NVertex[4]; // offset 0x9BA9C
static unsigned char *PVSEncodeTable; // offset 0xAAFD0
static unsigned char *shake_data[3]; // offset 0xA0FB0
static unsigned char align[6]; // offset 0xAA820
static unsigned char dummymotors[2]; // offset 0xAA828
static unsigned char endread; // offset 0xAB2F1
static unsigned char High_shake_data[21]; // offset 0xA0F7C
static unsigned char HorizonLookup[4][4]; // offset 0xA1954
static unsigned char HorizonTextures[40]; // offset 0xA1964
static unsigned char hornchanflag[2]; // offset 0xAA1C8
static unsigned char load_complete; // offset 0xAB2F0
static unsigned char Low_shake_data[10]; // offset 0xA0FA4
static unsigned char Med_shake_data[13]; // offset 0xA0F94
static unsigned char param[8]; // offset 0xAB1D0
static unsigned char playercollected[2]; // offset 0xAB060
static unsigned char result[8]; // offset 0xAB1D8
static unsigned char VibratoTable[32]; // offset 0xA26D8
static unsigned int horn_time; // offset 0xAAEA4
static unsigned long buffer[8]; // offset 0xE1220
static unsigned long channel_lookup[16]; // offset 0xDD450
static unsigned long finished_count; // offset 0xAAA4C
static unsigned long MCsp; // offset 0xAB408
static unsigned long MissionStack[16][16]; // offset 0xD7780
static unsigned short *xVis; // offset 0xAAE28
static unsigned short *zVis; // offset 0xAAE2C
static unsigned short CurrentChannel; // offset 0xAB398
static unsigned short ID; // offset 0xAB39A
static unsigned short MapClut; // offset 0xAAAD2
static unsigned short MapTPage; // offset 0xAAAD0
static unsigned short RecapFrameLength[19]; // offset 0x9F10C

// 1182 functions
/*
 * Offset 0x12F5C
 * D:\driver2\game\C\DR2ROADS.C (line 164)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ FindSurfaceD2(struct VECTOR *pos /*$s0*/, struct VECTOR *normal /*$s1*/, struct VECTOR *out /*$s3*/, struct _sdPlane **plane /*$s2*/)
{
}
/*
 * Offset 0x1313C
 * D:\driver2\game\C\DR2ROADS.C (line 205)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ sdHeightOnPlane(struct VECTOR *pos /*$t0*/, struct _sdPlane *plane /*$a1*/)
{ // line 1, offset 0x1313c
  { // line 11, offset 0x1319c
    int angle; // $v0
    int i; // $v0
    struct DRIVER2_CURVE *curve; // $s0
  } // line 23, offset 0x13204
  { // line 26, offset 0x13204
    int val; // $a3
    { // line 35, offset 0x13224
      int lx; // $v0
      int ly; // $v1
    } // line 39, offset 0x13280
  } // line 42, offset 0x13294
} // line 43, offset 0x13294
/*
 * Offset 0x13294
 * D:\driver2\game\C\DR2ROADS.C (line 295)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ RoadInCell(struct VECTOR *pos /*$s5*/)
{ // line 1, offset 0x13294
  char *buffer; // $s2
  struct XYPAIR cellPos; // stack offset -48
  struct XYPAIR cell; // stack offset -40
  short *surface; // $a0
  struct _sdPlane *plane; // $s0
  { // line 36, offset 0x13380
    int moreLevels; // $s3
    short *check; // $s1
    struct _sdPlane *base; // $s4
  } // line 77, offset 0x1344c
} // line 94, offset 0x134d4
/*
 * Offset 0x134D4
 * D:\driver2\game\C\DR2ROADS.C (line 400)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
struct _sdPlane * /*$ra*/ sdGetCell(struct VECTOR *pos /*$s3*/)
{ // line 1, offset 0x134d4
  char *buffer; // $s1
  short *surface; // $s0
  int nextLevel; // $s2
  struct _sdPlane *plane; // $a1
  struct XYPAIR cell; // stack offset -40
  struct XYPAIR cellPos; // stack offset -32
  { // line 41, offset 0x135c4
    int y; // $a0
  } // line 56, offset 0x13620
  { // line 63, offset 0x13634
    short *BSPsurface; // $a0
  } // line 81, offset 0x1369c
} // line 102, offset 0x13728
/*
 * Offset 0x13728
 * D:\driver2\game\C\DR2ROADS.C (line 64)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ProcessStraightsDriver2Lump(char *lump_file /*$s0*/, int lump_size /*$a1*/)
{ // line 1, offset 0x13728
} // line 5, offset 0x1375c
/*
 * Offset 0x1375C
 * D:\driver2\game\C\DR2ROADS.C (line 80)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ProcessCurvesDriver2Lump(char *lump_file /*$s0*/, int lump_size /*$a1*/)
{ // line 1, offset 0x1375c
} // line 5, offset 0x13790
/*
 * Offset 0x13790
 * D:\driver2\game\C\DR2ROADS.C (line 94)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ProcessJunctionsDriver2Lump(char *lump_file /*$s1*/, int lump_size /*$a1*/, int fix /*$s0*/)
{ // line 1, offset 0x13790
  { // line 8, offset 0x137c4
    int loop; // $v1
    struct OLD_DRIVER2_JUNCTION *old; // $a1
    struct DRIVER2_JUNCTION *p; // $a0
    { // line 13, offset 0x137e0
      int i; // $a1
    } // line 19, offset 0x1380c
  } // line 20, offset 0x13820
} // line 21, offset 0x13834
/*
 * Offset 0x13834
 * D:\driver2\game\C\DR2ROADS.C (line 146)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ MapHeight(struct VECTOR *pos /*$s0*/)
{ // line 1, offset 0x13834
  int height; // $v0
  struct _sdPlane *plane; // $v0
} // line 16, offset 0x13874
/*
 * Offset 0x13874
 * D:\driver2\game\C\DR2ROADS.C (line 250)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ GetSurfaceIndex(struct VECTOR *pos /*$a0*/)
{ // line 2, offset 0x13874
  struct _sdPlane *plane; // $v0
} // line 10, offset 0x138b0
/*
 * Offset 0x138B0
 * D:\driver2\game\C\DR2ROADS.C (line 505)
 * Stack frame base $sp, size 0
 */
short * /*$ra*/ sdGetBSP(struct _sdNode *node /*$a3*/, struct XYPAIR *pos /*$a1*/)
{ // line 1, offset 0x138b0
  { // line 4, offset 0x138d8
    int dot; // $a0
  } // line 17, offset 0x1393c
} // line 19, offset 0x13958
/*
 * Offset 0x13958
 * D:\driver2\game\C\DR2ROADS.C (line 266)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
struct _sdPlane * /*$ra*/ FindRoadInBSP(struct _sdNode *node /*$s0*/, struct _sdPlane *base /*$s1*/)
{ // line 2, offset 0x13970
  struct _sdPlane *plane; // $v0
} // line 27, offset 0x139e8
/*
 * Offset 0x139E8
 * D:\driver2\game\C\OBJANIM.C (line 362)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ ColourCycle()
{ // line 3, offset 0x139e8
  int i; // $s5
  struct CYCLE_OBJECT *cyc; // $s2
  struct RECT vram; // stack offset -56
  unsigned short *bufaddr; // $s0
  unsigned short length; // $v0
  unsigned short temp; // $s1
  { // line 26, offset 0x13ab4
    int tnum; // $a1
    { // line 39, offset 0x13b0c
    } // line 48, offset 0x13b54
    { // line 53, offset 0x13b80
    } // line 62, offset 0x13bc8
  } // line 81, offset 0x13c88
} // line 88, offset 0x13ce4
/*
 * Offset 0x13D14
 * D:\driver2\game\C\OBJANIM.C (line 481)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ InitAnimatingObjects()
{ // line 2, offset 0x13d14
  struct ANIMATED_OBJECT *aop; // $s1
  int loop; // $s0
  int count1; // $a0
  int count; // $a2
  struct MODEL *modelPtr; // $a0
} // line 47, offset 0x13e60
/*
 * Offset 0x13E60
 * D:\driver2\game\C\OBJANIM.C (line 613)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ animate_object(struct CELL_OBJECT *cop /*$s2*/, int type /*$a1*/)
{ // line 1, offset 0x13e60
  short yang; // $s1
  char phase; // $a0
} // line 283, offset 0x1470c
/*
 * Offset 0x1470C
 * D:\driver2\game\C\OBJANIM.C (line 931)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ animate_garage_door()
{ // line 2, offset 0x1470c
  int dx; // $a0
  int dz; // $v1
  int dist; // $a0
} // line 34, offset 0x14888
/*
 * Offset 0x14890
 * D:\driver2\game\C\OBJANIM.C (line 536)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitSpooledAnimObj(int model_number /*$a0*/)
{ // line 1, offset 0x14890
  struct ANIMATED_OBJECT *aop; // $a1
  int i; // $a2
} // line 15, offset 0x14900
/*
 * Offset 0x14908
 * D:\driver2\game\C\OBJANIM.C (line 578)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ DrawAnimatingObject(struct MODEL *model /*$a0*/, struct CELL_OBJECT *cop /*$s3*/, struct VECTOR *pos /*$a2*/)
{ // line 1, offset 0x14908
  struct ANIMATED_OBJECT *aop; // $s1
  int loop; // $s2
  int type; // $s0
} // line 27, offset 0x149b8
/*
 * Offset 0x149B8
 * D:\driver2\game\C\OBJANIM.C (line 460)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ FindSmashableObjects()
{ // line 2, offset 0x149b8
  struct SMASHABLE_OBJECT *sip; // $s0
} // line 8, offset 0x14a10
/*
 * Offset 0x14A10
 * D:\driver2\game\C\OBJANIM.C (line 565)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ int_garage_door()
{
}
/*
 * Offset 0x14A1C
 * D:\driver2\game\C\OBJANIM.C (line 260)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ InitCyclingPals()
{ // line 2, offset 0x14a1c
  int i; // $s0
  struct CYCLE_OBJECT *cyc; // $s1
  struct RECT vram; // stack offset -24
} // line 18, offset 0x14ac0
/*
 * Offset 0x14AC0
 * D:\driver2\game\C\OVERLAY.C (line 270)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ InitOverlays()
{
}
/*
 * Offset 0x14CA4
 * D:\driver2\game\C\OVERLAY.C (line 329)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DisplayOverlays()
{
}
/*
 * Offset 0x14E10
 * D:\driver2\game\C\OVERLAY.C (line 426)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawPercentageBar(struct _PERCENTAGE_BAR *bar /*$fp*/)
{ // line 1, offset 0x14e10
  struct POLY_G4 *poly; // $s0
  struct CVECTOR temp; // stack offset -56
  int min_x; // $s1
  int max_x; // $s7
  int min_y; // $s2
  int max_y; // stack offset -48
  char *tag; // $s0
  { // line 94, offset 0x152b0
    short tagX; // $s1
    short tagY; // $s2
  } // line 102, offset 0x1530c
} // line 104, offset 0x1533c
/*
 * Offset 0x1533C
 * D:\driver2\game\C\OVERLAY.C (line 532)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawProximityBar(struct _PERCENTAGE_BAR *bar /*$t3*/)
{ // line 1, offset 0x1533c
  struct TILE *tile; // $a1
  int min_x; // $s1
  int max_x; // $s7
  int min_y; // $s2
  int max_y; // $fp
  short total; // $v1
  char *tag; // $s0
  { // line 87, offset 0x157c8
    short tagX; // $s1
    short tagY; // $s2
  } // line 95, offset 0x1582c
} // line 97, offset 0x1585c
/*
 * Offset 0x1585C
 * D:\driver2\game\C\OVERLAY.C (line 707)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DrawDrivingGameOverlays()
{ // line 2, offset 0x1585c
  struct SCORE_ENTRY *table; // $s1
  char string[32]; // stack offset -64
  int i; // $s1
  int x; // $s3
  int y; // $s2
  { // line 11, offset 0x158c4
    { // line 25, offset 0x1593c
    } // line 25, offset 0x1593c
    { // line 50, offset 0x15a4c
    } // line 63, offset 0x15b10
  } // line 136, offset 0x15eb4
} // line 137, offset 0x15ed8
/*
 * Offset 0x15ED8
 * D:\driver2\game\C\OVERLAY.C (line 378)
 * Stack frame base $sp, size 128
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetFullscreenDrawing()
{ // line 2, offset 0x15ed8
  struct DRAWENV drawenv; // stack offset -104
  struct DR_ENV *dr_env; // $s0
} // line 10, offset 0x15f88
/*
 * Offset 0x15F88
 * D:\driver2\game\C\OVERLAY.C (line 395)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitPercentageBar(struct _PERCENTAGE_BAR *bar /*$a0*/, int size /*$a1*/, struct COLOUR_BAND *pColourBand /*$a2*/, char *tag /*$a3*/)
{
}
/*
 * Offset 0x15FC0
 * D:\driver2\game\C\OVERLAY.C (line 414)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ EnablePercentageBar(struct _PERCENTAGE_BAR *bar /*$a0*/, int max /*$a1*/)
{
}
/*
 * Offset 0x15FD4
 * D:\driver2\game\C\OVERLAY.C (line 631)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetColourByValue(struct COLOUR_BAND *pColourBand /*$a3*/, int value /*$a1*/, struct CVECTOR *pOut /*$t0*/)
{ // line 1, offset 0x15fd4
  struct COLOUR_BAND *pPrevColourBand; // $a2
  int scale; // $a0
  int temp; // $a1
} // line 30, offset 0x16100
/*
 * Offset 0x16100
 * D:\driver2\game\C\OVERLAY.C (line 669)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ TransparencyOn(void *potz /*$a0*/, unsigned short tpage /*$a1*/)
{ // line 1, offset 0x16100
  struct DR_TPAGE *null; // $a2
} // line 7, offset 0x1617c
/*
 * Offset 0x1617C
 * D:\driver2\game\C\OVERLAY.C (line 687)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ UpdateFlashValue()
{ // line 2, offset 0x1617c
  char size; // $v1
} // line 13, offset 0x161ec
/*
 * Offset 0x161EC
 * D:\driver2\game\C\OVERLAY.C (line 846)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ PrintScoreTableTime(int x /*$s0*/, int y /*$s1*/, int time /*$a0*/)
{ // line 1, offset 0x161ec
  char string[32]; // stack offset -48
  int min; // $t0
  int frac; // $v1
} // line 15, offset 0x162e8
/*
 * Offset 0x162E8
 * D:\driver2\game\C\OVERMAP.C (line 685)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawTargetBlip(struct VECTOR *pos /*$t0*/, unsigned char r /*$s2*/, unsigned char g /*$s3*/, unsigned char b /*$s4*/, unsigned long flags /*stack 16*/)
{ // line 1, offset 0x162e8
  struct POLY_FT4 *poly; // $t0
  struct VECTOR vec; // stack offset -40
  int ysize; // $a2
} // line 74, offset 0x165c0
/*
 * Offset 0x165E0
 * D:\driver2\game\C\OVERMAP.C (line 815)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawTargetArrow(struct VECTOR *pos /*$a2*/, unsigned long flags /*$s3*/)
{ // line 1, offset 0x165e0
  struct VECTOR vec; // stack offset -56
  struct VECTOR vec2; // stack offset -40
  struct POLY_FT3 *null; // $t1
  struct POLY_G3 *poly; // $s2
  int dx; // $s1
  int dy; // $s0
} // line 60, offset 0x1687c
/*
 * Offset 0x1687C
 * D:\driver2\game\C\OVERMAP.C (line 883)
 * Stack frame base $sp, size 192
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DrawPlayerDot(struct VECTOR *pos /*$a1*/, short rot /*$s2*/, unsigned char r /*$s5*/, unsigned char g /*$s4*/, int b /*stack 16*/, unsigned long flags /*stack 20*/)
{ // line 1, offset 0x1687c
  struct MATRIX matrix; // stack offset -168
  struct VECTOR direction; // stack offset -136
  struct SVECTOR apos[3]; // stack offset -120
  struct VECTOR opos[3]; // stack offset -96
  struct POLY_F3 *poly; // $t0
  struct VECTOR vec; // stack offset -48
} // line 63, offset 0x16b2c
/*
 * Offset 0x16B50
 * D:\driver2\game\C\OVERMAP.C (line 954)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ProcessOverlayLump(char *lump_ptr /*$s1*/, int lump_size /*$s0*/)
{ // line 1, offset 0x16b50
  struct TEXTURE_DETAILS info; // stack offset -32
  int i; // $a1
  int x; // $v0
  int y; // $a0
} // line 32, offset 0x16c74
/*
 * Offset 0x16C74
 * D:\driver2\game\C\OVERMAP.C (line 994)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: ra
 */
unsigned long /*$ra*/ Long2DDistance(struct VECTOR *pPoint1 /*$a0*/, struct VECTOR *pPoint2 /*$a2*/)
{ // line 1, offset 0x16c74
  struct VECTOR delta; // stack offset -24
  unsigned int result; // $v0
  { // line 7, offset 0x16cb8
    int Theta; // $v1
    int tempTheta; // $v0
    { // line 15, offset 0x16cd8
      int cos; // $v1
    } // line 23, offset 0x16d04
    { // line 28, offset 0x16d0c
      int sin; // $v1
    } // line 38, offset 0x16d6c
  } // line 39, offset 0x16d6c
} // line 42, offset 0x16d7c
/*
 * Offset 0x16D7C
 * D:\driver2\game\C\OVERMAP.C (line 1077)
 * Stack frame base $sp, size 808
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawOverheadMap()
{ // line 2, offset 0x16d7c
  int width; // $t5
  int height; // $t4
  int count; // $s2
  int count1; // $s3
  int tpage; // $t1
  int x_mod; // $s5
  int y_mod; // $fp
  int MeshWidth; // $s6
  int MeshHeight; // $s7
  long flag; // stack offset -104
  struct SVECTOR MapMesh[5][5]; // stack offset -784
  struct VECTOR MapMeshO[5][5]; // stack offset -584
  struct MAPTEX MapTex[4]; // stack offset -184
  struct SVECTOR direction; // stack offset -152
  struct POLY_FT4 *spt; // $a3
  struct POLY_F4 *sptb; // $a0
  struct DR_AREA *draw_area; // $s2
  struct RECT clipped_size; // stack offset -144
  struct VECTOR translate; // stack offset -136
  { // line 35, offset 0x16e8c
    static int ptab[16]; // offset 0x118
  } // line 36, offset 0x16e8c
  { // line 48, offset 0x16f60
    static int ptab[12]; // offset 0x158
    int intens; // $a1
  } // line 58, offset 0x17010
  { // line 62, offset 0x17010
    { // line 62, offset 0x17010
      struct VECTOR vec; // stack offset -120
      struct TILE_1 *tile1; // $a0
    } // line 65, offset 0x1715c
  } // line 65, offset 0x1715c
  { // line 69, offset 0x1715c
    struct _CAR_DATA *cp; // $s0
  } // line 84, offset 0x17280
  { // line 91, offset 0x172a8
  } // line 93, offset 0x172a8
  { // line 108, offset 0x17328
  } // line 110, offset 0x17328
  { // line 125, offset 0x173b4
  } // line 127, offset 0x173b4
  { // line 142, offset 0x17448
  } // line 144, offset 0x17448
} // line 290, offset 0x17c68
/*
 * Offset 0x17C98
 * D:\driver2\game\C\OVERMAP.C (line 1374)
 * Stack frame base $sp, size 216
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawFullscreenMap()
{ // line 2, offset 0x17c98
  struct TILE *polys; // $v0
  struct POLY_FT4 *back; // $a1
  struct POLY_FT3 *null; // $a2
  struct SVECTOR Mesh[4]; // stack offset -192
  struct VECTOR MeshO[4]; // stack offset -160
  struct VECTOR target; // stack offset -96
  long flag; // stack offset -64
  long count; // $s4
  int width; // stack offset -60
  int height; // stack offset -56
  int x; // $s7
  int y; // $s3
  int min_x; // $a0
  int max_x; // $v0
  int min_y; // $v1
  int max_y; // $v1
  { // line 65, offset 0x17e98
    int px; // $a2
    int pz; // $a1
  } // line 126, offset 0x17ff0
  { // line 180, offset 0x1805c
    int clipped; // $s5
  } // line 232, offset 0x18278
  { // line 246, offset 0x18318
    { // line 246, offset 0x18318
      struct VECTOR vec; // stack offset -80
      struct TILE_1 *tile1; // $v1
    } // line 246, offset 0x18318
  } // line 246, offset 0x18318
} // line 263, offset 0x18450
/*
 * Offset 0x18450
 * D:\driver2\game\C\OVERMAP.C (line 1645)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ DrawCopIndicators()
{ // line 2, offset 0x18450
  static int ft[16]; // offset 0x188
  struct _CAR_DATA *cp; // $s0
  int fade; // $s1
  int cc; // $s3
  int cs; // $s2
  { // line 17, offset 0x184e8
    int dx; // $a3
    int dz; // $a1
    int p; // $a1
    int q; // $a0
    int ap; // $v1
    { // line 25, offset 0x18578
    } // line 28, offset 0x185d0
  } // line 29, offset 0x185d0
} // line 31, offset 0x18608
/*
 * Offset 0x18608
 * D:\driver2\game\C\OVERMAP.C (line 1697)
 * Stack frame base $sp, size 88
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawMultiplayerMap()
{ // line 2, offset 0x18608
  struct POLY_FT4 *poly; // $a2
  struct LINE_F2 *line2; // $s1
  struct VECTOR target; // stack offset -64
  int i; // $s3
  int y; // $s7
} // line 79, offset 0x189e8
/*
 * Offset 0x189E8
 * D:\driver2\game\C\OVERMAP.C (line 2319)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ FlashOverheadMap(int r /*$a0*/, int g /*$a1*/, int b /*$a2*/)
{ // line 2, offset 0x189e8
  struct TILE *tile; // $a3
} // line 22, offset 0x18b08
/*
 * Offset 0x18B08
 * D:\driver2\game\C\OVERMAP.C (line 2350)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ LoadMapTile(int tpage /*$a0*/, int x /*$a1*/, int y /*$a2*/)
{ // line 1, offset 0x18b08
  struct RECT MapSegment; // stack offset -16
  int temp; // $a0
  int count; // $a2
  int idx; // $a3
} // line 33, offset 0x18c5c
/*
 * Offset 0x18C5C
 * D:\driver2\game\C\OVERMAP.C (line 2405)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ draw_box()
{ // line 2, offset 0x18c5c
  struct LINE_F4 *line4; // $s0
  struct LINE_F2 *line2; // $s1
} // line 22, offset 0x18dbc
/*
 * Offset 0x18DBC
 * D:\driver2\game\C\OVERMAP.C (line 2435)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ DrawN(struct VECTOR *pScreenPosition /*$s2*/, int direct /*$s7*/)
{ // line 1, offset 0x18dbc
  struct XYPAIR lastPoint; // stack offset -48
  struct XYPAIR *pPoint; // $s0
  char loop; // $s4
  { // line 11, offset 0x18e2c
    struct LINE_F2 *pLine; // $a2
  } // line 34, offset 0x18f2c
} // line 36, offset 0x18f80
/*
 * Offset 0x18F80
 * D:\driver2\game\C\OVERMAP.C (line 2479)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawCompass()
{ // line 2, offset 0x18f80
  struct VECTOR position[5]; // stack offset -88
  struct XYPAIR *pNorth; // $a1
  int scale; // $a0
  { // line 3, offset 0x18f80
    char loop; // $t2
    struct VECTOR *pPosition; // $a3
    void *pot; // $s0
    { // line 32, offset 0x19120
      struct LINE_G2 *pLine; // $a0
    } // line 32, offset 0x19120
  } // line 46, offset 0x191fc
} // line 47, offset 0x191fc
/*
 * Offset 0x191FC
 * D:\driver2\game\C\OVERMAP.C (line 2534)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ DrawBigCompass(struct VECTOR *root /*$a0*/, int angle /*$a1*/)
{ // line 1, offset 0x191fc
  struct VECTOR position[5]; // stack offset -96
  struct VECTOR *pPosition; // $s0
  char loop; // $s1
  { // line 23, offset 0x19368
    struct LINE_G2 *pLine; // $a1
  } // line 23, offset 0x19368
} // line 35, offset 0x1941c
/*
 * Offset 0x1941C
 * D:\driver2\game\C\OVERMAP.C (line 2577)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CopIndicator(int xpos /*$a3*/, int strength /*$a1*/)
{ // line 1, offset 0x1941c
  struct POLY_F3 *tri; // $a2
  int str2; // $fp
  void *pot; // stack offset -56
} // line 30, offset 0x195fc
/*
 * Offset 0x195FC
 * D:\driver2\game\C\OVERMAP.C (line 2609)
 * Stack frame base $sp, size 184
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ DrawSightCone(struct COP_SIGHT_DATA *pCopSightData /*$a0*/, struct VECTOR *pPosition /*$a1*/, int direction /*$t6*/)
{ // line 1, offset 0x195fc
  struct VECTOR vertex[9]; // stack offset -160
  struct VECTOR *pVertex; // $t0
  int angle; // $a3
  int frontViewAngle; // $t1
  int negFrontViewAngle; // $a2
  int frontViewDistance; // $t4
  int surroundViewDistance; // $t3
  { // line 15, offset 0x19650
    int len; // $a1
    { // line 27, offset 0x19668
      int temp; // $v0
    } // line 27, offset 0x19668
  } // line 27, offset 0x19668
  { // line 34, offset 0x196d4
    struct VECTOR *pVertex; // $a2
    void *pot; // $a3
    { // line 42, offset 0x19720
      struct POLY_G3 *poly; // $a1
      struct VECTOR *pNextVertex; // $a0
    } // line 50, offset 0x19744
  } // line 61, offset 0x19824
} // line 62, offset 0x19824
/*
 * Offset 0x19824
 * D:\driver2\game\C\OVERMAP.C (line 1043)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ InitOverheadMap()
{ // line 2, offset 0x19824
  int tpage; // $s3
  int c; // $s2
  int d; // $s1
} // line 27, offset 0x19924
/*
 * Offset 0x19948
 * D:\driver2\game\C\OVERMAP.C (line 1678)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ InitMultiplayerMap()
{ // line 2, offset 0x19948
  struct RECT rect; // stack offset -48
  char filename[32]; // stack offset -40
} // line 17, offset 0x199fc
/*
 * Offset 0x199FC
 * D:\driver2\game\C\OVERMAP.C (line 1778)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ WorldToMultiplayerMap(struct VECTOR *in /*$a3*/, struct VECTOR *out /*$a2*/)
{ // line 1, offset 0x199fc
  int x; // $v1
  int z; // $a0
} // line 17, offset 0x19ac8
/*
 * Offset 0x19AC8
 * D:\driver2\game\C\OVERMAP.C (line 2392)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetMapPos()
{
}
/*
 * Offset 0x19B58
 * D:\driver2\game\C\OVERMAP.C (line 2703)
 * Stack frame base $sp, size 96
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ WorldToOverheadMapPositions(struct VECTOR *pGlobalPosition /*$s1*/, struct VECTOR *pOverheadMapPosition /*$s3*/, int count /*$s2*/, char inputRelative /*$s5*/, int outputRelative /*stack 16*/)
{ // line 1, offset 0x19b58
  struct MATRIX TempMatrix; // stack offset -80
  int sin; // $a1
  int cos; // $a2
  int angle; // $v1
  int scale; // $s0
  { // line 42, offset 0x19c88
    struct SVECTOR tempVector; // stack offset -48
    long flag; // stack offset -40
  } // line 57, offset 0x19d28
} // line 61, offset 0x19d74
/*
 * Offset 0x19D74
 * D:\driver2\game\C\OVERMAP.C (line 2771)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetFullscreenMapMatrix()
{ // line 2, offset 0x19d74
  struct VECTOR translate; // stack offset -32
  struct SVECTOR direction; // stack offset -16
} // line 16, offset 0x19e50
/*
 * Offset 0x19E50
 * D:\driver2\game\C\OVERMAP.C (line 2794)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ WorldToFullscreenMap(struct VECTOR *in /*$a0*/, struct VECTOR *out /*$a1*/)
{
}
/*
 * Offset 0x19EE4
 * D:\driver2\game\C\OVERMAP.C (line 2806)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: ra
 */
void /*$ra*/ WorldToFullscreenMap2(struct VECTOR *in /*$a0*/, struct VECTOR *out /*$a1*/)
{ // line 1, offset 0x19ee4
  struct SVECTOR pos; // stack offset -24
  long flag; // stack offset -16
} // line 13, offset 0x19fac
/*
 * Offset 0x19FAC
 * D:\driver2\game\C\OVERMAP.C (line 1970)
 * Stack frame base $sp, size 696
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ ProcessPalletLump(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
{ // line 1, offset 0x19fac
  int total_cluts; // $v0
  int clutValue; // $s1
  int tpageindex; // $s2
  int texnum; // $s3
  int palette; // $s4
  int clut_number; // $v1
  unsigned short clutTable[320]; // stack offset -680
  char *buffPtr; // $s0
  { // line 43, offset 0x1a038
  } // line 43, offset 0x1a038
} // line 64, offset 0x1a0fc
/*
 * Offset 0x1A0FC
 * D:\driver2\game\C\OVERMAP.C (line 2043)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ load_civ_palettes(struct RECT *cluts /*$a0*/)
{
}
/*
 * Offset 0x1A104
 * D:\driver2\game\C\REPLAYS.C (line 498)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ InitPadRecording()
{ // line 2, offset 0x1a104
  int i; // $s0
  int remain; // $s0
} // line 152, offset 0x1a29c
/*
 * Offset 0x1A29C
 * D:\driver2\game\C\REPLAYS.C (line 657)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ SaveReplayToBuffer(char *buffer /*$s0*/)
{ // line 1, offset 0x1a29c
  struct REPLAY_SAVE_HEADER *header; // $s2
  int i; // $a2
  int size; // $s1
  int numstreams; // $s6
} // line 76, offset 0x1a800
/*
 * Offset 0x1A800
 * D:\driver2\game\C\REPLAYS.C (line 740)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ LoadReplayFromBuffer(char *buffer /*$s1*/)
{ // line 2, offset 0x1a800
  struct REPLAY_SAVE_HEADER *header; // $s3
  struct REPLAY_STREAM_HEADER *sheader; // $t0
  int i; // $a1
  int size; // $s0
} // line 73, offset 0x1adb8
/*
 * Offset 0x1ADB8
 * D:\driver2\game\C\REPLAYS.C (line 1310)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ cjpRecord(int stream /*$s1*/, unsigned long *ppad /*$s4*/, char *psteer /*$s2*/, char *ptype /*$s3*/)
{ // line 1, offset 0x1adb8
  unsigned long t0; // stack offset -32
  int t1; // $s0
} // line 60, offset 0x1af7c
/*
 * Offset 0x1AF9C
 * D:\driver2\game\C\REPLAYS.C (line 1222)
 * Stack frame base $sp, size 8
 */
int /*$ra*/ valid_region(int x /*$a0*/, int z /*$a1*/)
{ // line 2, offset 0x1af9c
  struct XYPAIR region_coords; // stack offset -8
  int region; // $a0
} // line 47, offset 0x1b064
/*
 * Offset 0x1B064
 * D:\driver2\game\C\REPLAYS.C (line 1271)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ cjpPlay(int stream /*$a0*/, unsigned long *ppad /*$s2*/, char *psteer /*$s0*/, char *ptype /*$s1*/)
{ // line 1, offset 0x1b064
  int ret; // $a0
  unsigned long t0; // stack offset -24
  int t1; // $v1
} // line 20, offset 0x1b0f8
/*
 * Offset 0x1B0F8
 * D:\driver2\game\C\REPLAYS.C (line 1182)
 * Stack frame base $sp, size 0
 */
char /*$ra*/ GetPingInfo(char *cookieCount /*$a2*/)
{ // line 1, offset 0x1b0f8
  struct _PING_PACKET *pp; // $a1
  char retCarId; // $v0
} // line 24, offset 0x1b180
/*
 * Offset 0x1B180
 * D:\driver2\game\C\REPLAYS.C (line 1059)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: ra
 */
int /*$ra*/ LoadAttractReplay(int mission /*$a2*/)
{ // line 1, offset 0x1b180
  char filename[32]; // stack offset -40
} // line 12, offset 0x1b1e4
/*
 * Offset 0x1B1E4
 * D:\driver2\game\C\REPLAYS.C (line 1383)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ AllocateReplayStream(struct REPLAY_STREAM *stream /*$a0*/, int maxpad /*$a1*/)
{
}
/*
 * Offset 0x1B258
 * D:\driver2\game\C\REPLAYS.C (line 1402)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ Get(int stream /*$a0*/, unsigned long *pt0 /*$a1*/)
{ // line 1, offset 0x1b258
  struct REPLAY_STREAM *rstream; // $a2
  unsigned long t0; // $a0
} // line 36, offset 0x1b2e8
/*
 * Offset 0x1B2E8
 * D:\driver2\game\C\REPLAYS.C (line 1440)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ Put(int stream /*$a0*/, unsigned long *pt0 /*$a1*/)
{ // line 2, offset 0x1b2e8
  struct REPLAY_STREAM *rstream; // $a0
  unsigned char **pstream; // $a3
  unsigned long t0; // $a1
} // line 37, offset 0x1b3cc
/*
 * Offset 0x1B3CC
 * D:\driver2\game\C\REPLAYS.C (line 1479)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ RecordWaypoint()
{
}
/*
 * Offset 0x1BAF0
 * D:\driver2\game\C\SEARCH.C (line 12)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitTextureNames()
{
}
/*
 * Offset 0x1BAF8
 * D:\driver2\game\C\AI.C (line 324)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ TannerStuckInCar(int doSpeedCheck /*$a0*/)
{ // line 1, offset 0x1baf8
  struct _CAR_DATA *cp; // $a2
} // line 17, offset 0x1bc20
/*
 * Offset 0x1BC20
 * D:\driver2\game\C\AI.C (line 275)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ StoreGameFlags()
{
}
/*
 * Offset 0x1BC50
 * D:\driver2\game\C\AI.C (line 297)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ TannerCanEnterCar(struct _CAR_DATA *cp /*$a0*/, int distToCarSq /*$a1*/)
{ // line 1, offset 0x1bc50
  { // line 13, offset 0x1bce4
    struct SVECTOR *carCollBox; // $v0
    int carRange; // $a0
  } // line 20, offset 0x1bd34
} // line 23, offset 0x1bd3c
/*
 * Offset 0x1C1C8
 * D:\driver2\game\C\BCOLL3D.C (line 83)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0
 */
void /*$ra*/ PointFaceCheck(struct _CAR_DATA *cp0 /*$t7*/, struct _CAR_DATA *cp1 /*$t8*/, int i /*$t9*/, struct TestResult *least /*$a3*/, int nSign /*stack 16*/)
{ // line 1, offset 0x1c1c8
  int k; // $t5
  struct VECTOR normal; // stack offset -56
  struct VECTOR diff; // stack offset -40
  struct VECTOR point; // stack offset -24
  int depth; // $t0
  { // line 23, offset 0x1c2b8
    int partialDepth; // $v1
  } // line 36, offset 0x1c354
} // line 47, offset 0x1c3e8
/*
 * Offset 0x1C3E8
 * D:\driver2\game\C\BCOLL3D.C (line 153)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ CarCarCollision3(struct _CAR_DATA *c0 /*$a0*/, struct _CAR_DATA *c1 /*$a1*/, int *depth /*$s2*/, struct VECTOR *where /*$s0*/, struct VECTOR *normal /*stack 16*/)
{ // line 1, offset 0x1c3e8
  struct TestResult tr; // stack offset -56
  int res; // $t1
} // line 12, offset 0x1c470
/*
 * Offset 0x1C470
 * D:\driver2\game\C\BCOLL3D.C (line 133)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ collided3d(struct _CAR_DATA *cp0 /*$s3*/, struct _CAR_DATA *cp1 /*$s2*/, struct TestResult *least /*$s1*/)
{ // line 1, offset 0x1c470
  int i; // $s0
} // line 18, offset 0x1c584
/*
 * Offset 0x1C584
 * D:\driver2\game\C\BCOLLIDE.C (line 120)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 fp
 */
int /*$ra*/ bcollided2d(struct CDATA2D *body /*$t4*/, int needOverlap /*$fp*/)
{ // line 1, offset 0x1c584
  struct VECTOR delta; // stack offset -56
  int dtheta; // $v1
  int ac; // $s6
  int as; // $s5
  int i; // $t7
  int j; // $a2
  int k; // $t5
  { // line 40, offset 0x1c7a0
    int xover; // $t0
    int zover; // $a0
    int tmp2; // $a2
    int FE; // $a3
  } // line 63, offset 0x1c8f8
} // line 65, offset 0x1c928
/*
 * Offset 0x1C928
 * D:\driver2\game\C\BCOLLIDE.C (line 195)
 * Stack frame base $sp, size 8
 * Saved registers at offset -4: s0 s1
 */
void /*$ra*/ bFindCollisionPoint(struct CDATA2D *body /*$t6*/, struct CRET2D *collisionResult /*$s0*/)
{ // line 1, offset 0x1c928
  int carBarrierCollision; // $s1
  int i; // $a3
  int j; // $v1
  int k; // $t0
  int smallest; // $t4
  int besti; // $t5
  int bestk; // $t7
  int sign; // $t3
  int sign0; // $t0
  int sign1; // $a3
  { // line 17, offset 0x1c9cc
    int upper; // $a1
    int lower; // $v1
  } // line 33, offset 0x1ca24
  { // line 40, offset 0x1ca58
    int upper; // $a1
    int lower; // $a0
  } // line 54, offset 0x1cac8
} // line 78, offset 0x1cc98
/*
 * Offset 0x1CC98
 * D:\driver2\game\C\BCOLLIDE.C (line 275)
 * Stack frame base $sp, size 264
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ bFindCollisionTime(struct CDATA2D *cd /*$s5*/, struct CRET2D *collisionResult /*stack 4*/)
{ // line 1, offset 0x1cc98
  int i; // $s4
  int q; // $s0
  int hit; // $t2
  int neverfree; // $fp
  int time; // $s1
  int step; // $s3
  struct CDATA2D original[2]; // stack offset -248
} // line 82, offset 0x1cf54
/*
 * Offset 0x1CF54
 * D:\driver2\game\C\BCOLLIDE.C (line 384)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ApplyDamage(struct _CAR_DATA *cp /*$a0*/, char region /*$a1*/, int value /*$a2*/, char fakeDamage /*$a3*/)
{ // line 1, offset 0x1cf54
  short *pRegion; // $t0
} // line 81, offset 0x1d118
/*
 * Offset 0x1D118
 * D:\driver2\game\C\BCOLLIDE.C (line 470)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ DamageCar3D(struct _CAR_DATA *cp /*$s1*/, long *delta[4] /*$t4*/, int strikeVel /*$t6*/, struct _CAR_DATA *pOtherCar /*$s2*/)
{ // line 1, offset 0x1d118
  int l; // $v1
  int w; // $v0
  int region; // $a1
  long nose[4]; // stack offset -56
  long door[4]; // stack offset -40
  int impact; // $s3
  int QQQ; // $t7
  { // line 79, offset 0x1d3f0
    char fakeDamage; // $a3
    char player_id; // $s0
    char kludge; // $a3
  } // line 98, offset 0x1d48c
} // line 102, offset 0x1d4bc
/*
 * Offset 0x1D4BC
 * D:\driver2\game\C\BCOLLIDE.C (line 587)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DamageCar(struct _CAR_DATA *cp /*$s2*/, struct CDATA2D *cd /*$s1*/, struct CRET2D *collisionResult /*$s3*/, int strikeVel /*$s0*/)
{ // line 1, offset 0x1d4bc
  struct VECTOR delta; // stack offset -48
  int l; // $v1
  int w; // $v0
  int region; // $a1
  int damage; // $a2
  char player_id; // $s5
  int impact; // $s4
  int QQQ; // $t0
} // line 46, offset 0x1d6d0
/*
 * Offset 0x1D6F4
 * D:\driver2\game\C\BCOLLIDE.C (line 839)
 * Stack frame base $sp, size 200
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CarBuildingCollision(struct _CAR_DATA *cp /*$s3*/, struct BUILDING_BOX *building /*$s2*/, struct CELL_OBJECT *cop /*$s6*/, int mightBeABarrier /*$s1*/)
{ // line 1, offset 0x1d6f4
  static struct CDATA2D cd[2]; // offset 0x0
  static struct CRET2D collisionResult; // offset 0xd0
  int debris_colour; // stack offset -48
  struct VECTOR tempwhere; // stack offset -168
  struct MODEL *pModel; // $s5
  int player_id; // stack offset -44
  { // line 27, offset 0x1d7fc
    struct SVECTOR boxDisp; // stack offset -152
    { // line 69, offset 0x1d95c
      int wbod; // $a1
    } // line 79, offset 0x1da0c
  } // line 81, offset 0x1da0c
  { // line 138, offset 0x1dacc
    { // line 138, offset 0x1dacc
      struct VECTOR velocity; // stack offset -144
      long pointVel[4]; // stack offset -128
      long reaction[4]; // stack offset -112
      long lever[4]; // stack offset -96
      int strikeVel; // $s1
      { // line 175, offset 0x1dcc0
        short scale; // $a2
      } // line 195, offset 0x1dd0c
      { // line 211, offset 0x1dd6c
        { // line 219, offset 0x1dd90
          struct SMASHABLE_OBJECT *sip; // $a1
          struct SMASHABLE_OBJECT *match; // $s0
          int chan; // $s1
          int adjust; // $s2
        } // line 240, offset 0x1dea4
      } // line 254, offset 0x1df2c
      { // line 259, offset 0x1df5c
        struct VECTOR LeafPosition; // stack offset -80
      } // line 259, offset 0x1df5c
      { // line 277, offset 0x1dfb8
        { // line 280, offset 0x1dff8
          struct VECTOR lamp_velocity; // stack offset -64
        } // line 284, offset 0x1e02c
      } // line 285, offset 0x1e02c
      { // line 304, offset 0x1e0c0
        int twistY; // $a1
        int lever_dot_n; // $a0
        int displacementsquared; // $v1
        int denom; // $v1
      } // line 316, offset 0x1e1d8
    } // line 345, offset 0x1e3e4
  } // line 349, offset 0x1e3ec
} // line 356, offset 0x1e450
/*
 * Offset 0x1E450
 * D:\driver2\game\C\BOMBERMAN.C (line 245)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ HandleThrownBombs()
{ // line 2, offset 0x1e450
  struct BOMB *bomb; // $s1
  struct VECTOR velocity; // stack offset -48
  struct _CAR_DATA *cp; // $s0
  int i; // $s5
  int y; // $a0
  { // line 13, offset 0x1e494
  } // line 56, offset 0x1e630
  { // line 74, offset 0x1e6d8
    int len; // $v1
  } // line 85, offset 0x1e750
} // line 112, offset 0x1e850
/*
 * Offset 0x1E878
 * D:\driver2\game\C\BOMBERMAN.C (line 381)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DrawThrownBombs()
{ // line 2, offset 0x1e878
  struct MATRIX object_matrix; // stack offset -80
  struct MATRIX *finalmatrix; // $s2
  struct BOMB *bomb; // $s0
  struct VECTOR pos; // stack offset -48
  int i; // $s3
  { // line 16, offset 0x1e8d4
  } // line 33, offset 0x1ea00
  { // line 39, offset 0x1ea1c
  } // line 43, offset 0x1ea44
} // line 44, offset 0x1ea44
/*
 * Offset 0x1EA68
 * D:\driver2\game\C\BOMBERMAN.C (line 432)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ BombThePlayerToHellAndBack(int car /*$s3*/)
{ // line 1, offset 0x1ea68
  struct BOMB *bomb; // $t3
} // line 54, offset 0x1eca4
/*
 * Offset 0x1ECC0
 * D:\driver2\game\C\BOMBERMAN.C (line 496)
 * Stack frame base $sp, size 232
 * Saved registers at offset -8: ra
 */
int /*$ra*/ BombCollisionCheck(struct _CAR_DATA *cp /*$a0*/, struct VECTOR *pPos /*$a1*/)
{ // line 1, offset 0x1ecc0
  struct CDATA2D cd[2]; // stack offset -216
  int carLength[2]; // stack offset -16
  { // line 1, offset 0x1ecc0
  } // line 1, offset 0x1ecc0
} // line 27, offset 0x1ed80
/*
 * Offset 0x1ED80
 * D:\driver2\game\C\BOMBERMAN.C (line 534)
 * Stack frame base $sp, size 368
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ ExplosionCollisionCheck(struct _CAR_DATA *cp /*$s1*/, struct _ExOBJECT *pE /*$s3*/)
{ // line 1, offset 0x1ed80
  struct CDATA2D cd[2]; // stack offset -352
  int carLength[2]; // stack offset -152
  static int setUsed; // offset 0x28
  int tanner; // $s6
  { // line 12, offset 0x1eddc
    { // line 12, offset 0x1eddc
    } // line 12, offset 0x1eddc
    { // line 19, offset 0x1ee74
    } // line 24, offset 0x1eee8
    { // line 27, offset 0x1eee8
      int x; // $a1
      int z; // $v1
      struct VECTOR *pos; // $v0
    } // line 66, offset 0x1efbc
    { // line 89, offset 0x1effc
      struct CRET2D collisionResult; // stack offset -144
      { // line 92, offset 0x1effc
        struct VECTOR velocity; // stack offset -104
        long pointVel[4]; // stack offset -88
        long reaction[4]; // stack offset -72
        long lever[4]; // stack offset -56
        int strikeVel; // $s0
        { // line 154, offset 0x1f278
        } // line 161, offset 0x1f2b8
        { // line 164, offset 0x1f2b8
          int twistY; // $a1
          int lever_dot_n; // $a0
          int displacementsquared; // $v1
          int denom; // $v1
        } // line 176, offset 0x1f3c8
      } // line 198, offset 0x1f510
    } // line 199, offset 0x1f510
  } // line 200, offset 0x1f510
} // line 206, offset 0x1f55c
/*
 * Offset 0x1F55C
 * D:\driver2\game\C\BOMBERMAN.C (line 747)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ AddFlash(struct VECTOR *pos /*$a0*/)
{ // line 1, offset 0x1f55c
  int dist; // $a0
} // line 14, offset 0x1f5d8
/*
 * Offset 0x1F5D8
 * D:\driver2\game\C\BOMBERMAN.C (line 222)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitThrownBombs()
{ // line 2, offset 0x1f5d8
  int i; // $v1
} // line 13, offset 0x1f65c
/*
 * Offset 0x1F65C
 * D:\driver2\game\C\CAMERA.C (line 422)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ InitCamera(struct _PLAYER *lp /*$s0*/)
{ // line 1, offset 0x1f65c
  struct SVECTOR boxDisp; // stack offset -16
  { // line 6, offset 0x1f684
  } // line 6, offset 0x1f684
  { // line 19, offset 0x1f714
    struct _CAR_DATA *lcp; // $a0
  } // line 19, offset 0x1f714
  { // line 32, offset 0x1f7fc
    struct _EVENT *event; // $a1
  } // line 33, offset 0x1f7fc
} // line 122, offset 0x1fa88
/*
 * Offset 0x1FA88
 * D:\driver2\game\C\CAMERA.C (line 553)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ModifyCamera()
{ // line 2, offset 0x1fa88
  struct PAD *locPad; // $a3
  struct _PLAYER *lp; // $a2
  { // line 15, offset 0x1fb64
    char *pNextCameraview; // $a0
  } // line 25, offset 0x1fbb0
  { // line 32, offset 0x1fbcc
    int cam_ang; // $a0
    int length; // $a1
  } // line 40, offset 0x1fc6c
} // line 43, offset 0x1fc78
/*
 * Offset 0x1FC80
 * D:\driver2\game\C\CAMERA.C (line 609)
 * Stack frame base $sp, size 184
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ CameraCollisionCheck()
{ // line 2, offset 0x1fc80
  struct MODEL *model; // $v1
  struct COLLISION_PACKET *collide; // $t2
  struct CELL_OBJECT *cop; // $t3
  struct CELL_ITERATOR ci; // stack offset -168
  struct VECTOR nearpoint; // stack offset -144
  struct VECTOR surfacenormal; // stack offset -128
  struct VECTOR surfacepoint; // stack offset -112
  int cell_x; // $a0
  int cell_z; // $a1
  int xd; // $v1
  int zd; // $a0
  int num_cb; // $t5
  int box_loop; // $t4
  int sphere_sq; // $a2
  int camera_size; // $s0
  int count; // $s1
  struct VECTOR temp_cam; // stack offset -96
  { // line 50, offset 0x1fe5c
    struct MATRIX *mat; // $a2
    struct VECTOR offset; // stack offset -80
    struct VECTOR cam_vec; // stack offset -64
    struct VECTOR normal; // stack offset -48
    int xmin; // $a0
    int xmax; // $a3
    int ymin; // $t0
    int ymax; // $v1
    int zmin; // $a1
    int zmax; // $a2
    int tx; // $a3
    int tz; // $a1
  } // line 85, offset 0x20038
} // line 93, offset 0x200a4
/*
 * Offset 0x200A4
 * D:\driver2\game\C\CAMERA.C (line 777)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ PlaceCameraFollowCar(struct _PLAYER *lp /*$s2*/)
{ // line 1, offset 0x200a4
  int carheight; // $a0
  int minimum_height; // $s1
  int cammapht; // $s0
  int new_angle; // $a0
  int camPosVy; // $s1
  struct VECTOR locCameraPos; // stack offset -48
  int lbody; // $a0
  int hbody; // $a3
  int camExpandSpeed; // $s6
  { // line 23, offset 0x200f0
    struct _CAR_DATA *camCar; // $v1
  } // line 33, offset 0x20184
} // line 116, offset 0x20574
/*
 * Offset 0x20574
 * D:\driver2\game\C\CAMERA.C (line 987)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ PlaceCameraInCar(struct _PLAYER *lp /*$s3*/, int BumperCam /*$a1*/)
{ // line 1, offset 0x20574
  struct _CAR_DATA *cp; // $s2
  { // line 57, offset 0x20824
  } // line 58, offset 0x20834
  { // line 62, offset 0x20848
  } // line 65, offset 0x20868
} // line 90, offset 0x2096c
/*
 * Offset 0x2096C
 * D:\driver2\game\C\CAMERA.C (line 904)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ PlaceCameraAtLocation(struct _PLAYER *lp /*$s1*/, int zoom /*$s2*/)
{ // line 1, offset 0x2096c
  int d; // $s0
  { // line 7, offset 0x20998
    struct VECTOR temp; // stack offset -32
  } // line 9, offset 0x20998
} // line 46, offset 0x20a60
/*
 * Offset 0x20A78
 * D:\driver2\game\C\CAMERA.C (line 716)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ TurnHead(struct _PLAYER *lp /*$a0*/)
{ // line 1, offset 0x20a78
} // line 41, offset 0x20b70
/*
 * Offset 0x20B70
 * D:\driver2\game\C\CAMERA.C (line 960)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ PointAtTarget(struct VECTOR *pPosition /*$a0*/, struct VECTOR *pTarget /*$a1*/, struct SVECTOR *pAngleVec /*$s0*/)
{ // line 1, offset 0x20b70
  struct VECTOR delta; // stack offset -32
  int d; // $s1
} // line 16, offset 0x20c28
/*
 * Offset 0x20C28
 * D:\driver2\game\C\CAMERA.C (line 1083)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ OK_To_Zoom()
{ // line 2, offset 0x20c28
  int old_z; // $s0
  struct VECTOR temp; // stack offset -24
} // line 31, offset 0x20cd8
/*
 * Offset 0x20CD8
 * D:\driver2\game\C\CAMERA.C (line 1119)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetBasePos(struct VECTOR *pVec /*$a0*/)
{
}
/*
 * Offset 0x20CFC
 * D:\driver2\game\C\CARS.C (line 834)
 * Stack frame base $sp, size 96
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ plotNewCarModel(struct CAR_MODEL *car /*$s0*/, int palette /*$s2*/)
{ // line 1, offset 0x20cfc
  struct plotCarGlobals _pg; // stack offset -72
  struct SVECTOR v0; // stack offset -32
  unsigned long lightlevel; // stack offset -24
} // line 74, offset 0x20ef0
/*
 * Offset 0x20F08
 * D:\driver2\game\C\CARS.C (line 1125)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 s1
 */
void /*$ra*/ plotCarPolyGT3(int numTris /*$a0*/, struct CAR_POLY *src /*$t1*/, struct SVECTOR *vlist /*$s0*/, struct SVECTOR *nlist /*$a3*/, struct plotCarGlobals *pg /*stack 16*/, int palette /*stack 20*/)
{ // line 1, offset 0x20f08
  struct POLY_GT3 *prim; // $t0
  long *ot; // $s1
  long GT3rgb; // stack offset -24
  int i; // $t7
  int v0; // $t3
  int v1; // $t4
  int v2; // $t2
  int n0; // $t3
  int n1; // $a2
  int n2; // $a0
  int r0; // stack offset -20
  int r1; // stack offset -16
  int r2; // $v0
  int reg; // $a0
  int clut_uv0; // $a1
  int tpage_uv1; // $t6
  int uv3_uv2; // $t5
  unsigned short *clut_base; // $t9
  { // line 1, offset 0x20f08
    int ofse; // $v1
  } // line 1, offset 0x20f08
  { // line 106, offset 0x210a8
    int ofse; // $v1
  } // line 106, offset 0x210a8
} // line 126, offset 0x21120
/*
 * Offset 0x21120
 * D:\driver2\game\C\CARS.C (line 1442)
 * Stack frame base $sp, size 344
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawCar(struct _CAR_DATA *cp /*$s3*/, int view /*$a1*/)
{ // line 1, offset 0x21120
  int WheelSpeed; // $s0
  int model; // $fp
  struct _PLAYER *lp; // $a2
  { // line 12, offset 0x211dc
    struct CVECTOR col; // stack offset -312
  } // line 50, offset 0x212ac
  { // line 54, offset 0x212ac
    struct MATRIX temp_mat1; // stack offset -304
    struct MATRIX temp_mat2; // stack offset -272
    struct MATRIX final_mat; // stack offset -240
    struct VECTOR pos; // stack offset -208
    struct VECTOR pos1; // stack offset -192
    struct SVECTOR temp_vec; // stack offset -176
    int result; // $s4
    { // line 77, offset 0x212f8
      struct VECTOR corners[4]; // stack offset -168
    } // line 96, offset 0x213ec
    { // line 100, offset 0x213ec
      struct VECTOR d; // stack offset -104
      struct VECTOR dist; // stack offset -88
    } // line 117, offset 0x21540
    { // line 168, offset 0x215b4
      int i; // $a0
    } // line 173, offset 0x215d8
    { // line 185, offset 0x2160c
      struct MATRIX workmatrix; // stack offset -104
      struct CAR_MODEL *CarModelPtr; // $s1
      { // line 193, offset 0x2166c
      } // line 195, offset 0x21688
    } // line 197, offset 0x21688
    { // line 208, offset 0x216dc
      int damage; // $v1
      { // line 264, offset 0x21824
        struct CAR_MODEL *CarModelPtr; // $s0
        { // line 264, offset 0x21824
          struct MATRIX workmatrix; // stack offset -72
        } // line 293, offset 0x21924
      } // line 294, offset 0x21924
    } // line 295, offset 0x21924
    { // line 314, offset 0x21984
    } // line 322, offset 0x219ec
  } // line 346, offset 0x21b30
} // line 347, offset 0x21b30
/*
 * Offset 0x21B60
 * D:\driver2\game\C\CARS.C (line 1850)
 * Stack frame base $sp, size 160
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawCarWheels(struct _CAR_DATA *cp /*$fp*/, struct MATRIX *RearMatrix /*stack 4*/, struct VECTOR *pos /*stack 8*/, int zclip /*$a3*/)
{ // line 1, offset 0x21b60
  struct CAR_COSMETICS *car_cos; // $s0
  struct MATRIX FrontMatrix; // stack offset -144
  struct MODEL *WheelModel; // $s0
  struct MODEL *WheelModelBack; // stack offset -56
  struct MODEL *WheelModelFront; // stack offset -52
  int i; // $s4
  static short FrontWheelRotation[20]; // offset 0x0
  static short BackWheelRotation[20]; // offset 0x30
  short model; // $a0
  short wheelSize; // $s2
  { // line 16, offset 0x21c10
    int FrontWheelIncrement; // $a3
    int BackWheelIncrement; // $t0
  } // line 69, offset 0x21d38
  { // line 72, offset 0x21d38
    int c; // $t2
    int s; // $t3
    int FW1z; // $v0
    int FW2z; // $a0
    int BW1z; // $v0
    int BW2z; // $a3
    struct SVECTOR *VertPtr; // $t6
  } // line 76, offset 0x21d38
  { // line 76, offset 0x21d38
    struct MATRIX SteerMatrix; // stack offset -112
  } // line 76, offset 0x21d38
  { // line 138, offset 0x2200c
    struct SVECTOR *verts; // $s5
    { // line 157, offset 0x22060
      struct VECTOR WheelPos; // stack offset -80
      struct SVECTOR sWheelPos; // stack offset -64
    } // line 162, offset 0x22090
  } // line 194, offset 0x22180
} // line 196, offset 0x221e8
/*
 * Offset 0x221E8
 * D:\driver2\game\C\CARS.C (line 2058)
 * Stack frame base $sp, size 8
 */
void /*$ra*/ DrawWheelObject(struct MODEL *model /*$t2*/, struct SVECTOR *verts /*$t4*/, int transparent /*$a2*/, int wheelnum /*$a3*/)
{ // line 1, offset 0x221e8
  struct POLY_FT4 *prims; // $t0
  struct POLYFT4LIT *src; // $t1
  int i; // $t2
  int Z; // stack offset -4
  int clut; // $t8
  int tpage; // $t7
  unsigned long bright; // $t6
  unsigned long dim; // $t5
  { // line 35, offset 0x22300
    int flag1; // stack offset -8
    long vl; // $a0
    { // line 53, offset 0x223b0
      int r2; // $v1
    } // line 53, offset 0x223b0
  } // line 83, offset 0x22498
} // line 85, offset 0x224c0
/*
 * Offset 0x224C0
 * D:\driver2\game\C\CARS.C (line 2198)
 * Stack frame base $sp, size 112
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ComputeCarLightingLevels(struct _CAR_DATA *cp /*$s1*/, char detail /*$s3*/)
{ // line 1, offset 0x224c0
  int light; // $s2
  struct SVECTOR lightsourcevector; // stack offset -96
  struct SVECTOR colour; // stack offset -88
  struct VECTOR lightValues; // stack offset -80
  struct VECTOR *orient; // $s0
  { // line 72, offset 0x22774
    struct MODEL *model; // $v1
    struct SVECTOR *norms; // $a3
    struct SVECTOR *ppads; // $a2
    int num_norms; // $a1
    int count; // $a1
    struct CVECTOR c0; // stack offset -64
    struct CVECTOR c1; // stack offset -56
    struct CVECTOR c2; // stack offset -48
    { // line 78, offset 0x22774
      long GT3rgb; // stack offset -40
    } // line 78, offset 0x22774
  } // line 114, offset 0x2289c
} // line 118, offset 0x228c8
/*
 * Offset 0x228C8
 * D:\driver2\game\C\CARS.C (line 2321)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ buildNewCars()
{
}
/*
 * Offset 0x229C8
 * D:\driver2\game\C\CARS.C (line 2357)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ buildNewCarFromModel(struct CAR_MODEL *car /*$s5*/, struct MODEL *model /*$s7*/, int first /*$a2*/)
{ // line 1, offset 0x229c8
  char *polylist; // $s0
  int i; // $s2
  int j; // $s3
  int pass; // $s4
  { // line 37, offset 0x22b04
    struct CAR_POLY *p; // $s1
    char ptype; // $s6
    { // line 46, offset 0x22b4c
    } // line 48, offset 0x22b4c
    { // line 51, offset 0x22b4c
    } // line 53, offset 0x22b4c
    { // line 57, offset 0x22b4c
    } // line 59, offset 0x22b4c
    { // line 62, offset 0x22b4c
    } // line 64, offset 0x22b4c
    { // line 69, offset 0x22b4c
    } // line 77, offset 0x22b4c
    { // line 80, offset 0x22b4c
    } // line 92, offset 0x22b4c
    { // line 96, offset 0x22b4c
    } // line 104, offset 0x22b84
    { // line 107, offset 0x22b84
    } // line 119, offset 0x22be4
    { // line 123, offset 0x22be4
    } // line 125, offset 0x22be4
    { // line 129, offset 0x22be4
    } // line 131, offset 0x22be4
    { // line 135, offset 0x22be4
    } // line 147, offset 0x22c78
    { // line 150, offset 0x22c78
    } // line 169, offset 0x22d8c
    { // line 173, offset 0x22d8c
    } // line 191, offset 0x22e94
    { // line 194, offset 0x22e94
    } // line 222, offset 0x23044
  } // line 225, offset 0x23044
} // line 236, offset 0x23100
/*
 * Offset 0x23130
 * D:\driver2\game\C\CARS.C (line 2595)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MangleWheelModels()
{ // line 2, offset 0x23130
  int i; // $v1
  struct MODEL *m; // $t0
  struct POLYFT4LIT *src; // $a0
  { // line 15, offset 0x23178
    int j; // $t1
  } // line 46, offset 0x233bc
} // line 54, offset 0x233f8
/*
 * Offset 0x233F8
 * D:\driver2\game\C\CARS.C (line 2697)
 * Stack frame base $sp, size 0
 */
char /*$ra*/ GetCarPalIndex(int tpage /*$a0*/)
{ // line 1, offset 0x233f8
  int i; // $a1
} // line 16, offset 0x2343c
/*
 * Offset 0x23444
 * D:\driver2\game\C\CARS.C (line 1793)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ DrawCarObject(struct CAR_MODEL *car /*$s0*/, struct MATRIX *matrix /*$a1*/, struct VECTOR *pos /*$a2*/, struct VECTOR *pos1 /*$a3*/, int palette /*stack 16*/, struct _CAR_DATA *cp /*stack 20*/, int detail /*stack 24*/)
{ // line 1, offset 0x23444
  { // line 1, offset 0x23444
    struct SVECTOR cog; // stack offset -40
    struct VECTOR modelLocation; // stack offset -32
  } // line 1, offset 0x23444
  { // line 1, offset 0x23444
    static unsigned long savedSP; // offset 0x0
  } // line 40, offset 0x23544
} // line 43, offset 0x23544
/*
 * Offset 0x23544
 * D:\driver2\game\C\CARS.C (line 2152)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ PlayerCarFX(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x23544
  int WheelSpeed; // $s1
} // line 39, offset 0x23660
/*
 * Offset 0x23660
 * D:\driver2\game\C\CARS.C (line 2656)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ setupLightingMatrices()
{
}
/*
 * Offset 0x237B8
 * D:\driver2\game\C\CARS.C (line 2685)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ restoreLightingMatrices()
{
}
/*
 * Offset 0x23820
 * D:\driver2\game\C\CARS.C (line 917)
 * Stack frame base $sp, size 8
 */
void /*$ra*/ plotCarPolyB3(int numTris /*$a0*/, struct CAR_POLY *src /*$a1*/, struct SVECTOR *vlist /*$a2*/, struct plotCarGlobals *pg /*$a3*/)
{ // line 1, offset 0x23820
  struct POLY_F3 *prim; // $t0
  int i; // $t1
  long *ot; // $t3
  long F3rgb; // $t4
  { // line 10, offset 0x23848
    int reg; // stack offset -8
  } // line 50, offset 0x23914
} // line 53, offset 0x2392c
/*
 * Offset 0x2392C
 * D:\driver2\game\C\CARS.C (line 976)
 * Stack frame base $sp, size 8
 */
void /*$ra*/ plotCarPolyFT3(int numTris /*$a0*/, struct CAR_POLY *src /*$t1*/, struct SVECTOR *vlist /*$t4*/, struct plotCarGlobals *pg /*$t5*/)
{ // line 1, offset 0x2392c
  struct POLY_FT3 *prim; // $t0
  long *ot; // $t6
  long FT3rgb; // stack offset -8
  int i; // $t2
  { // line 16, offset 0x2396c
    int reg; // stack offset -4
    int clut_uv0; // $a2
    int tpage_uv1; // $a3
    int uv3_uv2; // $a1
    { // line 22, offset 0x2396c
      int ofse; // $v1
    } // line 22, offset 0x2396c
  } // line 76, offset 0x23a70
} // line 79, offset 0x23a88
/*
 * Offset 0x23A88
 * D:\driver2\game\C\CARS.C (line 1349)
 * Stack frame base $sp, size 8
 */
void /*$ra*/ plotCarPolyGT3nolight(int numTris /*$a0*/, struct CAR_POLY *src /*$t3*/, struct SVECTOR *vlist /*$t6*/, struct plotCarGlobals *pg /*$a3*/, int palette /*stack 16*/)
{ // line 1, offset 0x23a88
  struct POLY_FT3 *prim; // $t0
  long *ot; // $t7
  long GT3rgb; // stack offset -8
  int i; // $t4
  unsigned short *clut_base; // $t8
  { // line 17, offset 0x23ad0
    int reg; // stack offset -4
    int clut_uv0; // $a0
    int tpage_uv1; // $t1
    int uv3_uv2; // $t2
    { // line 22, offset 0x23ad0
      int ofse; // $v1
    } // line 22, offset 0x23ad0
  } // line 76, offset 0x23bfc
} // line 79, offset 0x23c14
/*
 * Offset 0x23C14
 * D:\driver2\game\C\CELL.C (line 67)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
struct PACKED_CELL_OBJECT * /*$ra*/ GetFirstPackedCop(int cellx /*$t3*/, int cellz /*$a1*/, struct CELL_ITERATOR *pci /*$a2*/, int use_computed /*$a3*/)
{ // line 1, offset 0x23c14
  struct PACKED_CELL_OBJECT *ppco; // $a1
  unsigned short index; // $a0
  unsigned short num; // $t0
  int cbrx; // $t0
  int cbrz; // $t1
  int xoff; // $a0
  int yoff; // $v0
  int cbr; // $t2
  { // line 34, offset 0x23cec
    int event; // $t0
  } // line 43, offset 0x23d30
} // line 75, offset 0x23e28
/*
 * Offset 0x23E28
 * D:\driver2\game\C\CELL.C (line 57)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ ClearCopUsage()
{
}
/*
 * Offset 0x23E50
 * D:\driver2\game\C\CIV_AI.C (line 717)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ InitCar(struct _CAR_DATA *cp /*$s0*/, int direction /*$s6*/, long *startPos[4] /*$s2*/, unsigned char control /*$s4*/, int model /*stack 16*/, int palette /*stack 20*/, char *extraData /*stack 24*/)
{ // line 1, offset 0x23e50
  struct VECTOR tmpStart; // stack offset -48
} // line 69, offset 0x24090
/*
 * Offset 0x24090
 * D:\driver2\game\C\CIV_AI.C (line 981)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ GetNextRoadInfo(struct _CAR_DATA *cp /*$s7*/, int randomExit /*$a1*/, int *turnAngle /*stack 8*/, int *startDist /*stack 12*/, struct CIV_ROUTE_ENTRY *oldNode /*stack 16*/)
{ // line 1, offset 0x24090
  int oldOppDir; // $s4
  int i; // $a1
  int j; // $s6
  int newRoad; // $s3
  int numExits; // stack offset -88
  int currentRoadExit; // $t6
  int newNumLanes; // $a3
  int newDir; // stack offset -84
  int oppDir; // $s0
  struct DRIVER2_JUNCTION *jn; // $t5
  struct DRIVER2_CURVE *cv; // $s1
  struct DRIVER2_STRAIGHT *st; // $s5
  struct DRIVER2_STRAIGHT *tmpSt; // $a2
  struct DRIVER2_CURVE *tmpCv; // $s1
  short *jnExit; // $a2
  int newLane; // $s2
  char leftLane; // stack offset -80
  char rightLane; // stack offset -76
  { // line 61, offset 0x2479c
    char relExitId; // $fp
    static char validExitRelIdx[4][3][2]; // offset 0x0
    int addRoad; // $t9
    { // line 1, offset 0x2486c
      int currentRoadExit; // $t6
      int newRoadExit; // $fp
      { // line 1, offset 0x2486c
        int exitMod; // $a0
        int ret; // $a1
      } // line 1, offset 0x248d8
    } // line 1, offset 0x248d8
    { // line 110, offset 0x24c80
      int x; // $v1
      int z; // $v0
      int dir; // stack offset -84
      struct DRIVER2_CURVE *cv; // $s1
      { // line 110, offset 0x24c80
      } // line 110, offset 0x24c80
    } // line 110, offset 0x24c80
    { // line 131, offset 0x250b0
      int exitId; // $a1
      { // line 135, offset 0x250d4
        char lane; // $v0
      } // line 151, offset 0x2512c
      { // line 1, offset 0x251e8
        int currentRoadExit; // $t6
        { // line 1, offset 0x251e8
          int exitMod; // $a1
          int ret; // $a2
        } // line 1, offset 0x25248
      } // line 1, offset 0x25248
    } // line 166, offset 0x25254
    { // line 1, offset 0x25254
      struct DRIVER2_JUNCTION *jn; // $t5
      int currentExit; // $a2
      int turnAngle; // $t1
      struct _CAR_DATA *cp; // $s7
      struct CIV_ROUTE_ENTRY *oldNode; // $t7
      { // line 1, offset 0x25254
        unsigned short jnFlags; // $a0
        int i; // $a1
        int exitId; // $a3
      } // line 1, offset 0x25324
    } // line 1, offset 0x25324
    { // line 171, offset 0x25324
      { // line 192, offset 0x257dc
        int x; // $v1
        int z; // $v0
        int dir; // stack offset -84
        struct DRIVER2_CURVE *cv; // $s1
        { // line 192, offset 0x257dc
        } // line 192, offset 0x257dc
      } // line 192, offset 0x257dc
    } // line 203, offset 0x25c30
  } // line 203, offset 0x25c30
  { // line 211, offset 0x25c38
    int i; // $a1
    int dx; // $v1
    int dz; // $a0
    int numLanes; // $fp
    int *pNewLane; // $s3
    int laneFromLeft; // $a3
    int laneFromRight; // $v1
    { // line 274, offset 0x2604c
      int preferredNewLane; // $t1
    } // line 302, offset 0x2637c
    { // line 305, offset 0x263b0
      int preferredNewLane; // $s4
      { // line 305, offset 0x263b0
        int x; // $v1
        int z; // $v0
        struct DRIVER2_CURVE *cv; // $s1
        { // line 305, offset 0x263b0
        } // line 305, offset 0x263b0
      } // line 305, offset 0x263b0
    } // line 332, offset 0x26704
  } // line 345, offset 0x2680c
} // line 369, offset 0x269cc
/*
 * Offset 0x269CC
 * D:\driver2\game\C\CIV_AI.C (line 1365)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ InitNodeList(struct _CAR_DATA *cp /*$s6*/, char *extraData /*$s7*/)
{ // line 1, offset 0x269cc
  int i; // $v1
  struct CIV_ROUTE_ENTRY *cr; // $s5
  int dx; // $s1
  int dz; // $s2
  int surfInd; // $s4
  { // line 32, offset 0x26a6c
    int theta; // $s0
    int laneDist; // $s1
    struct DRIVER2_STRAIGHT *str; // $s3
  } // line 41, offset 0x26bc8
  { // line 46, offset 0x26c04
    struct DRIVER2_CURVE *crv; // $s0
  } // line 50, offset 0x26cb4
} // line 60, offset 0x26d14
/*
 * Offset 0x26D14
 * D:\driver2\game\C\CIV_AI.C (line 1441)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetNodePos(struct DRIVER2_STRAIGHT *straight /*$t1*/, struct DRIVER2_JUNCTION *junction /*$a1*/, struct DRIVER2_CURVE *curve /*$t0*/, int distAlongPath /*$a3*/, struct _CAR_DATA *cp /*stack 16*/, int *x /*stack 20*/, int *z /*stack 24*/, int laneNo /*stack 28*/)
{ // line 1, offset 0x26d14
  unsigned char oldLane; // $a0
  unsigned char changeLaneCount; // $t3
} // line 63, offset 0x26f88
/*
 * Offset 0x26F88
 * D:\driver2\game\C\CIV_AI.C (line 1507)
 * Stack frame base $sp, size 136
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CheckChangeLanes(struct DRIVER2_STRAIGHT *straight /*$s4*/, struct DRIVER2_CURVE *curve /*$s6*/, int distAlongSegment /*$a2*/, struct _CAR_DATA *cp /*$s3*/, int tryToPark /*stack 16*/)
{ // line 1, offset 0x26f88
  unsigned char currentLane; // $s7
  unsigned char newLane; // $s2
  unsigned char trials; // $t3
  unsigned char canProceed; // stack offset -88
  unsigned char travelAlongRoad; // $s5
  unsigned char turnRight; // stack offset -84
  struct _CAR_DATA *cp1; // $s0
  struct CIV_ROUTE_ENTRY tmpNode; // stack offset -120
  { // line 65, offset 0x272f8
    struct VECTOR pos; // stack offset -104
    int theta; // $a0
    int length; // $a1
    { // line 81, offset 0x273fc
    } // line 89, offset 0x274fc
  } // line 91, offset 0x2750c
} // line 116, offset 0x27598
/*
 * Offset 0x27598
 * D:\driver2\game\C\CIV_AI.C (line 1637)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CreateNewNode(struct _CAR_DATA *cp /*$s4*/)
{ // line 1, offset 0x27598
  int oldRoad; // $s1
  int cr; // $a3
  struct CIV_ROUTE_ENTRY *newNode; // $s6
  struct CIV_ROUTE_ENTRY *oldNode; // $s3
  struct DRIVER2_CURVE *curve; // $s0
  struct DRIVER2_STRAIGHT *straight; // $s5
  int turnAngle; // stack offset -56
  { // line 1, offset 0x27598
    struct _CAR_DATA *cp; // $s4
    struct CIV_ROUTE_ENTRY *currentNode; // $v1
    { // line 1, offset 0x27598
      struct CIV_ROUTE_ENTRY *retNode; // $a0
    } // line 1, offset 0x275e4
  } // line 1, offset 0x275e4
  { // line 1, offset 0x275f4
    struct _CAR_DATA *cp; // $s4
    { // line 1, offset 0x275f4
      struct CIV_ROUTE_ENTRY *retNode; // $a0
    } // line 1, offset 0x27604
  } // line 1, offset 0x27604
  { // line 1, offset 0x27610
    struct _CAR_DATA *cp; // $s4
    { // line 1, offset 0x27610
      struct CIV_ROUTE_ENTRY *retNode; // $a0
    } // line 1, offset 0x27620
  } // line 1, offset 0x27620
  { // line 1, offset 0x2762c
    struct _CAR_DATA *cp; // $s4
    { // line 1, offset 0x2762c
      struct CIV_ROUTE_ENTRY *retNode; // $a0
    } // line 1, offset 0x2763c
  } // line 1, offset 0x2763c
  { // line 16, offset 0x27658
    struct _CAR_DATA *cp; // $s4
    struct CIV_ROUTE_ENTRY *currentNode; // $s3
    { // line 16, offset 0x27658
      struct CIV_ROUTE_ENTRY *retNode; // $v1
    } // line 16, offset 0x27658
  } // line 16, offset 0x27658
  { // line 18, offset 0x27658
    { // line 1, offset 0x27658
      struct _CAR_DATA *cp; // $s4
      { // line 1, offset 0x27658
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 1, offset 0x27668
    } // line 1, offset 0x27668
  } // line 21, offset 0x27678
  { // line 22, offset 0x2769c
    struct _CAR_DATA *cp; // $s4
    struct CIV_ROUTE_ENTRY *currentNode; // $s3
    { // line 22, offset 0x2769c
      struct CIV_ROUTE_ENTRY *retNode; // $s2
    } // line 22, offset 0x276b4
  } // line 22, offset 0x276b4
  { // line 44, offset 0x27750
    int travelDir; // $a1
    int segmentEnd; // $a0
    { // line 51, offset 0x27818
      int startDist; // stack offset -52
    } // line 51, offset 0x27870
  } // line 51, offset 0x27880
  { // line 55, offset 0x278b4
    int travelDir; // $a2
    int segmentEnd; // $t0
    { // line 62, offset 0x279bc
      int startDist; // stack offset -48
    } // line 62, offset 0x279f8
  } // line 63, offset 0x27a0c
  { // line 80, offset 0x27a80
    struct CIV_ROUTE_ENTRY tmpNode; // stack offset -72
    { // line 84, offset 0x27ac0
      int travelDir; // $a0
    } // line 95, offset 0x27b80
    { // line 102, offset 0x27bf8
      struct _CAR_DATA *playerCar; // $v0
      int dx; // $v1
      int dz; // $a0
    } // line 107, offset 0x27c68
    { // line 114, offset 0x27ca0
      int tryToPark; // $s1
    } // line 136, offset 0x27e08
    { // line 142, offset 0x27e6c
      int radOfCrv; // $s5
      int cornerAngle; // $a3
      int segLength; // $s0
      int tmp; // $a1
      int dx; // $s1
      int dz; // $s0
      { // line 152, offset 0x27f24
        struct _CAR_DATA *cp; // $s4
        { // line 152, offset 0x27f24
          struct CIV_ROUTE_ENTRY *retNode; // $a0
        } // line 155, offset 0x27fac
      } // line 155, offset 0x27fac
      { // line 163, offset 0x27fe0
        struct _CAR_DATA *cp; // $s4
        { // line 163, offset 0x27fe0
          struct CIV_ROUTE_ENTRY *retNode; // $a0
        } // line 166, offset 0x28074
      } // line 166, offset 0x28074
    } // line 169, offset 0x28074
    { // line 173, offset 0x28074
      { // line 1, offset 0x28074
        struct _CAR_DATA *cp; // $s4
        struct CIV_ROUTE_ENTRY *currentNode; // $s6
        { // line 1, offset 0x28074
          struct CIV_ROUTE_ENTRY *retNode; // $v0
        } // line 1, offset 0x28074
      } // line 1, offset 0x28074
    } // line 177, offset 0x28084
  } // line 177, offset 0x28084
} // line 191, offset 0x28140
/*
 * Offset 0x28140
 * D:\driver2\game\C\CIV_AI.C (line 1843)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ InitCivState(struct _CAR_DATA *cp /*$s1*/, char *extraData /*$s2*/)
{ // line 1, offset 0x28140
  struct CIV_STATE *cs; // $s0
} // line 44, offset 0x28350
/*
 * Offset 0x28350
 * D:\driver2\game\C\CIV_AI.C (line 2016)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ PingOutAllSpecialCivCars()
{ // line 2, offset 0x28350
  struct _CAR_DATA *lcp; // $s0
  { // line 1, offset 0x283b0
    struct _CAR_DATA *cp; // $s0
  } // line 1, offset 0x2844c
} // line 9, offset 0x28474
/*
 * Offset 0x28474
 * D:\driver2\game\C\CIV_AI.C (line 2028)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ PingOutAllCivCarsAndCopCars()
{ // line 2, offset 0x28474
  struct _CAR_DATA *lcp; // $s0
  { // line 1, offset 0x284b4
    struct _CAR_DATA *cp; // $s0
  } // line 1, offset 0x28594
} // line 9, offset 0x285bc
/*
 * Offset 0x285BC
 * D:\driver2\game\C\CIV_AI.C (line 2050)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ CheckPingOut(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x285bc
  int dx; // $a0
  int dz; // $v1
  int dist; // $s1
  { // line 1, offset 0x28620
    struct _CAR_DATA *cp; // $s0
  } // line 1, offset 0x286fc
} // line 31, offset 0x28748
/*
 * Offset 0x28748
 * D:\driver2\game\C\CIV_AI.C (line 2176)
 * Stack frame base $sp, size 88
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ CreateCivCarWotDrivesABitThenStops(int direction /*$s5*/, long *startPos[4] /*$s2*/, long *stopPos[4] /*$a2*/, unsigned char internalModel /*$s4*/, int palette /*stack 16*/)
{ // line 1, offset 0x28748
  struct _EXTRA_CIV_DATA civDat; // stack offset -56
  struct _CAR_DATA *newCar; // $s1
  struct CIV_ROUTE_ENTRY *stopNode; // $a0
  struct CIV_ROUTE_ENTRY *spareNode; // $a1
  { // line 1, offset 0x28748
    { // line 1, offset 0x28748
      char *slot; // $v1
      struct _CAR_DATA *carCnt; // $a0
    } // line 8, offset 0x287dc
  } // line 8, offset 0x287dc
} // line 53, offset 0x289c8
/*
 * Offset 0x289C8
 * D:\driver2\game\C\CIV_AI.C (line 2248)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ CreateStationaryCivCar(int direction /*$t4*/, long orientX /*$s2*/, long orientZ /*$s1*/, long *startPos[4] /*$a2*/, int externalModel /*stack 16*/, int palette /*stack 20*/, int controlFlags /*stack 24*/)
{ // line 1, offset 0x289c8
  struct _EXTRA_CIV_DATA civDat; // stack offset -72
  struct _CAR_DATA *newCar; // $s0
  long tmpRes[4]; // stack offset -48
  long tmpQ[4]; // stack offset -32
  { // line 1, offset 0x28a84
    { // line 1, offset 0x28a84
      char *slot; // $v1
      struct _CAR_DATA *carCnt; // $a0
    } // line 1, offset 0x28ad0
  } // line 1, offset 0x28ad0
} // line 41, offset 0x28e1c
/*
 * Offset 0x28E1C
 * D:\driver2\game\C\CIV_AI.C (line 2323)
 * Stack frame base $sp, size 160
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ PingInCivCar(int minPingInDist /*stack 0*/)
{ // line 1, offset 0x28e1c
  struct _EXTRA_CIV_DATA civDat; // stack offset -128
  int dir; // stack offset -52
  int distAlongSegment; // $fp
  int lane; // $s7
  struct _CAR_DATA *newCar; // $s1
  struct DRIVER2_STRAIGHT *str; // $s6
  struct DRIVER2_CURVE *crv; // $s5
  unsigned char cookieCountStart; // $s4
  int curveLength; // stack offset -48
  unsigned char model; // $s4
  unsigned char possibleLanes[12]; // stack offset -104
  unsigned char carDistLanes[15]; // stack offset -88
  char numPossibleLanes; // $s0
  int lbody; // $s3
  { // line 1, offset 0x28f54
    { // line 1, offset 0x28f54
      char *slot; // $a1
      struct _CAR_DATA *carCnt; // $a0
    } // line 1, offset 0x28fa8
  } // line 1, offset 0x28fa8
  { // line 70, offset 0x29068
    char newCarId; // $v1
    { // line 1, offset 0x290c0
      struct _CAR_DATA *cp; // $s1
    } // line 1, offset 0x291a8
  } // line 79, offset 0x2930c
  { // line 139, offset 0x29688
    char frog; // $a0
    char numLanes; // $a1
  } // line 139, offset 0x297c8
  { // line 148, offset 0x298c8
    char frog; // $a0
    char numLanes; // $a1
  } // line 148, offset 0x299cc
  { // line 205, offset 0x29cb0
    int externalModel; // $v0
    { // line 212, offset 0x29d2c
      unsigned char palette; // $v0
    } // line 216, offset 0x29d88
  } // line 221, offset 0x29dc4
  { // line 227, offset 0x29e20
    int theta; // $s0
    int minDistAlong; // $s2
  } // line 240, offset 0x29f78
  { // line 244, offset 0x29fc0
    int minAngle; // $a1
  } // line 255, offset 0x2a0f8
  { // line 270, offset 0x2a150
    long pos[4]; // stack offset -72
    unsigned int distSq; // stack offset -56
    { // line 270, offset 0x2a150
      int *distToCarSq; // $t2
      { // line 270, offset 0x2a150
        int dz; // $v1
        int dx; // $a0
        int distSq; // $v0
        unsigned int retDistSq; // $a2
        struct _CAR_DATA *lcp; // $a1
      } // line 278, offset 0x2a290
    } // line 278, offset 0x2a290
    { // line 288, offset 0x2a2a8
      int x; // $t2
      int y; // $a2
      int z; // $t1
      unsigned int distSq; // $a3
      { // line 288, offset 0x2a2a8
        int dz; // $v1
        int dx; // $a0
        int ret; // $t0
        struct _CAR_DATA *lcp; // $a1
      } // line 288, offset 0x2a3a8
    } // line 288, offset 0x2a3a8
  } // line 299, offset 0x2a3e4
} // line 333, offset 0x2a52c
/*
 * Offset 0x2A52C
 * D:\driver2\game\C\CIV_AI.C (line 2659)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ AttemptUnPark(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, offset 0x2a52c
  struct DRIVER2_STRAIGHT *str; // $s2
  struct DRIVER2_CURVE *crv; // $s3
} // line 31, offset 0x2a664
/*
 * Offset 0x2A664
 * D:\driver2\game\C\CIV_AI.C (line 2798)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CivAccelTrafficRules(struct _CAR_DATA *cp /*$t3*/, int *distToNode /*$a1*/)
{ // line 1, offset 0x2a664
  int lbody; // $t1
  int wbody; // $t2
  struct CIV_STATE *cs; // $a2
  { // line 46, offset 0x2a784
    int stopDist; // $t0
    { // line 50, offset 0x2a7fc
      int endSpeed; // $v0
    } // line 55, offset 0x2a868
  } // line 56, offset 0x2a868
  { // line 65, offset 0x2a8ac
    int ret; // $a1
    int properVel; // $v1
    int brakeDist; // $a3
    { // line 103, offset 0x2a980
      int endSpeed; // $v0
      int currentDist; // $v1
    } // line 103, offset 0x2a980
  } // line 117, offset 0x2aa54
  { // line 125, offset 0x2aa54
    int roadClear; // $t8
    int checkObstDist; // $t7
    int numLanes; // $v0
    { // line 134, offset 0x2aa74
      struct _CAR_DATA *cp; // $t3
      { // line 134, offset 0x2aa74
        struct _CAR_DATA *lcp; // $a3
        int normal; // $v0
        int tangent; // $a0
        int distToObstacle; // $t0
        int ccarAng; // $t1
        int scarAng; // $t2
      } // line 134, offset 0x2ab94
    } // line 134, offset 0x2ab94
    { // line 1, offset 0x2abac
      struct _CAR_DATA *cp; // $t3
      { // line 1, offset 0x2abac
        struct CIV_STATE *cs; // $v1
      } // line 1, offset 0x2abac
    } // line 1, offset 0x2abac
    { // line 145, offset 0x2abc0
      int ret; // $v1
    } // line 148, offset 0x2ac10
  } // line 149, offset 0x2ac10
} // line 151, offset 0x2ac10
/*
 * Offset 0x2AC10
 * D:\driver2\game\C\CIV_AI.C (line 2950)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SetUpCivCollFlags()
{ // line 2, offset 0x2ac10
  struct SVECTOR boxDisp; // stack offset -72
  int carLength[2]; // stack offset -64
  struct _CAR_DATA *cp0; // $s5
  struct _CAR_DATA *cp1; // $s2
  unsigned int dNewLBODY[2]; // stack offset -56
  int dx; // $s0
  int dz; // stack offset -48
  { // line 35, offset 0x2ac7c
    int extraLength; // $a2
  } // line 35, offset 0x2acac
  { // line 40, offset 0x2addc
    { // line 53, offset 0x2ae2c
    } // line 53, offset 0x2ae80
    { // line 66, offset 0x2afc8
      int civCD; // $s7
      int brake; // $a0
      { // line 74, offset 0x2aff8
        unsigned int *blth; // $v1
      } // line 74, offset 0x2b028
      { // line 83, offset 0x2b088
        int i; // $a1
        int h; // $a3
        int rnd; // $a2
        struct _CAR_DATA *cp; // $s0
        { // line 90, offset 0x2b128
        } // line 98, offset 0x2b1f8
      } // line 100, offset 0x2b20c
    } // line 101, offset 0x2b20c
  } // line 102, offset 0x2b20c
  { // line 106, offset 0x2b230
    unsigned char i; // $s0
  } // line 115, offset 0x2b2d4
} // line 116, offset 0x2b2d4
/*
 * Offset 0x2B2D4
 * D:\driver2\game\C\CIV_AI.C (line 3074)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ CivAccel(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x2b2d4
  int ret; // $t1
  int distToNode; // stack offset -16
  int dx; // $v1
  int dz; // $a0
  { // line 32, offset 0x2b3c4
    int tmpRet; // $a0
    int lbody; // $a0
    { // line 37, offset 0x2b3f0
      int sf; // $v1
      int c1; // $t0
      int c2; // $a3
      int c3; // $a1
      { // line 52, offset 0x2b4b4
        int tmp; // $v1
      } // line 55, offset 0x2b520
    } // line 58, offset 0x2b530
  } // line 72, offset 0x2b590
} // line 75, offset 0x2b5a4
/*
 * Offset 0x2B5A4
 * D:\driver2\game\C\CIV_AI.C (line 3166)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ CivSteerAngle(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x2b5a4
  int station; // $a3
  int step; // $s2
  int ret; // $a0
  struct VECTOR locPath; // stack offset -56
  struct VECTOR pathPoint; // stack offset -40
  int lbody; // $s3
  { // line 1, offset 0x2b5a4
    { // line 1, offset 0x2b5a4
      struct _CAR_DATA *cp; // $s0
      { // line 1, offset 0x2b5a4
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 9, offset 0x2b5f8
    } // line 9, offset 0x2b5f8
    { // line 1, offset 0x2b608
      struct _CAR_DATA *cp; // $s0
      { // line 1, offset 0x2b608
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 1, offset 0x2b618
    } // line 1, offset 0x2b618
    { // line 1, offset 0x2b628
      struct _CAR_DATA *cp; // $s0
      { // line 1, offset 0x2b628
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 1, offset 0x2b638
    } // line 1, offset 0x2b638
    { // line 1, offset 0x2b648
      struct _CAR_DATA *cp; // $s0
      { // line 1, offset 0x2b648
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 1, offset 0x2b658
    } // line 1, offset 0x2b658
  } // line 26, offset 0x2b678
  { // line 1, offset 0x2b6e4
    struct _CAR_DATA *cp; // $s0
    { // line 1, offset 0x2b6e4
      struct CIV_ROUTE_ENTRY *retNode; // $a0
    } // line 1, offset 0x2b6f8
  } // line 1, offset 0x2b6f8
  { // line 35, offset 0x2b708
    struct CIV_ROUTE_ENTRY *crLoc; // $a1
    struct CIV_ROUTE_ENTRY *cr; // $a0
  } // line 46, offset 0x2b768
  { // line 1, offset 0x2b7b0
    struct _CAR_DATA *cp; // $s0
    { // line 1, offset 0x2b7b0
      struct CIV_ROUTE_ENTRY *retNode; // $v1
    } // line 1, offset 0x2b7c0
  } // line 1, offset 0x2b7c0
  { // line 70, offset 0x2b8d8
    struct CIV_ROUTE_ENTRY *cr; // $a0
    { // line 1, offset 0x2b908
      struct _CAR_DATA *cp; // $s0
      { // line 1, offset 0x2b908
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 1, offset 0x2b918
    } // line 1, offset 0x2b918
  } // line 77, offset 0x2b928
} // line 80, offset 0x2b94c
/*
 * Offset 0x2B94C
 * D:\driver2\game\C\CIV_AI.C (line 3265)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CivFindStation(struct _CAR_DATA *cp /*$s6*/)
{ // line 1, offset 0x2b94c
  struct CIV_ROUTE_ENTRY *rep; // $s3
  int cx; // stack offset -48
  int cz; // $fp
  { // line 1, offset 0x2b94c
    int loop; // $a0
    { // line 1, offset 0x2b9a4
      struct _CAR_DATA *cp; // $s6
      { // line 1, offset 0x2b9a4
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 1, offset 0x2b9b8
    } // line 1, offset 0x2b9b8
  } // line 12, offset 0x2b9c4
  { // line 15, offset 0x2b9cc
    struct _CAR_DATA *cp; // $s6
    struct CIV_ROUTE_ENTRY *currentNode; // $s3
    { // line 15, offset 0x2b9cc
      struct CIV_ROUTE_ENTRY *retNode; // $s0
    } // line 15, offset 0x2b9cc
  } // line 15, offset 0x2b9cc
  { // line 17, offset 0x2b9cc
    int sx; // $s5
    int sz; // $s4
    int dx; // $s2
    int dz; // $s1
    int stepsize; // $a1
    int square; // $a0
    { // line 44, offset 0x2ba90
      struct _CAR_DATA *cp; // $s6
      struct CIV_ROUTE_ENTRY *currentNode; // $s3
      { // line 44, offset 0x2ba90
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 44, offset 0x2baa0
    } // line 44, offset 0x2baa0
    { // line 1, offset 0x2bab0
      struct _CAR_DATA *cp; // $s6
      struct CIV_ROUTE_ENTRY *currentNode; // $s3
      { // line 1, offset 0x2bab0
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 1, offset 0x2bac0
    } // line 1, offset 0x2bac0
    { // line 1, offset 0x2bad0
      struct _CAR_DATA *cp; // $s6
      struct CIV_ROUTE_ENTRY *currentNode; // $s3
      { // line 1, offset 0x2bad0
        struct CIV_ROUTE_ENTRY *retNode; // $v1
      } // line 1, offset 0x2bae0
    } // line 1, offset 0x2bae0
  } // line 52, offset 0x2baf8
} // line 55, offset 0x2bb54
/*
 * Offset 0x2BB54
 * D:\driver2\game\C\CIV_AI.C (line 3337)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CivFindPointOnPath(struct _CAR_DATA *cp /*$s7*/, int station /*$s2*/, struct VECTOR *ppoint /*$fp*/)
{ // line 1, offset 0x2bb54
  struct CIV_ROUTE_ENTRY *cprep; // $a0
  struct CIV_ROUTE_ENTRY *start; // stack offset -48
  { // line 9, offset 0x2bbb8
    struct _CAR_DATA *cp; // $s7
    struct CIV_ROUTE_ENTRY *currentNode; // $a0
    { // line 9, offset 0x2bbb8
      struct CIV_ROUTE_ENTRY *retNode; // $s0
    } // line 9, offset 0x2bbb8
  } // line 9, offset 0x2bbb8
  { // line 11, offset 0x2bbb8
    int sx; // $s4
    int sz; // $s5
    int dx; // $s1
    int dz; // $s3
    int stepsize; // $a2
  } // line 44, offset 0x2bcf8
} // line 48, offset 0x2bd5c
/*
 * Offset 0x2BD5C
 * D:\driver2\game\C\CIV_AI.C (line 3398)
 * Stack frame base $sp, size 120
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CreateRoadblock()
{ // line 2, offset 0x2bd5c
  struct _CAR_DATA *cp; // $v1
  struct _CAR_DATA *lcp; // $s0
  struct _CAR_DATA *newCar; // $s0
  struct DRIVER2_STRAIGHT *str; // stack offset -72
  struct DRIVER2_CURVE *crv; // $s7
  int distAlongSegment; // $s2
  int lbody; // $s4
  int dir; // $s6
  int numLanes; // stack offset -68
  unsigned char externalCopModel; // stack offset -64
  int delta; // $s4
  int noMoreCars; // stack offset -60
  int newCarId; // $v1
  { // line 2, offset 0x2bd5c
    int dir; // $s0
  } // line 39, offset 0x2c0e0
  { // line 44, offset 0x2c104
    int theta; // $s0
  } // line 53, offset 0x2c200
  { // line 57, offset 0x2c248
    int minAngle; // $a3
    int curveLength; // $v1
  } // line 93, offset 0x2c39c
  { // line 80, offset 0x2c460
    { // line 85, offset 0x2c530
    } // line 87, offset 0x2c54c
    { // line 1, offset 0x2c5f8
      struct _CAR_DATA *cp; // $s0
    } // line 1, offset 0x2c6dc
    { // line 1, offset 0x2c770
      struct _CAR_DATA *cp; // $s0
    } // line 1, offset 0x2c84c
  } // line 112, offset 0x2c85c
  { // line 117, offset 0x2c898
    struct VECTOR startPos2; // stack offset -88
    int deltaAngle; // $a0
    int dir2NextRow; // $a1
    int faceDir; // $s1
    int numSpareCars; // $a0
    int count; // $s2
    int numSpots; // $fp
    { // line 129, offset 0x2c9b0
      int numCarsToAdd; // $s5
      { // line 133, offset 0x2c9e4
        { // line 1, offset 0x2cb2c
          struct _CAR_DATA *cp; // $s0
        } // line 1, offset 0x2cc10
        { // line 1, offset 0x2cca4
          struct _CAR_DATA *cp; // $s0
        } // line 1, offset 0x2cd80
      } // line 157, offset 0x2cd90
    } // line 158, offset 0x2cd9c
  } // line 159, offset 0x2cd9c
} // line 166, offset 0x2cddc
/*
 * Offset 0x2CE0C
 * D:\driver2\game\C\CIV_AI.C (line 2144)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitCivCars()
{ // line 2, offset 0x2ce0c
} // line 13, offset 0x2ce78
/*
 * Offset 0x2CE78
 * D:\driver2\game\C\CIV_AI.C (line 2699)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ CivControl(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x2ce78
  { // line 1, offset 0x2ce78
  } // line 1, offset 0x2ce78
  { // line 30, offset 0x2cef4
  } // line 32, offset 0x2cf28
} // line 41, offset 0x2cf80
/*
 * Offset 0x2CF80
 * D:\driver2\game\C\CIV_AI.C (line 2116)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ TrafficLightCycle(int exit /*$a0*/)
{ // line 1, offset 0x2cf80
  int timeCnt; // $v1
} // line 25, offset 0x2cfe8
/*
 * Offset 0x2CFE8
 * D:\driver2\game\C\CIV_AI.C (line 1977)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ PingOutCar(struct _CAR_DATA *cp /*$s0*/)
{
}
/*
 * Offset 0x2D0EC
 * D:\driver2\game\C\CIV_AI.C (line 930)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ CivCarFX(struct _CAR_DATA *cp /*$s0*/)
{
}
/*
 * Offset 0x2D184
 * D:\driver2\game\C\CIV_AI.C (line 891)
 * Stack frame base $sp, size 0
 */
struct _CAR_DATA * /*$ra*/ FindClosestCar(int x /*$t4*/, int y /*$a1*/, int z /*$a2*/, int *distToCarSq /*$a3*/)
{ // line 1, offset 0x2d184
  struct _CAR_DATA *retCar; // $t2
  struct _CAR_DATA *lcp; // $t0
  unsigned int retDistSq; // $t1
  int distSq; // $v0
  int dx; // $a0
  int dz; // $v1
} // line 24, offset 0x2d288
/*
 * Offset 0x2D288
 * D:\driver2\game\C\CIV_AI.C (line 2084)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetUpTrafficLightPhase()
{
}
/*
 * Offset 0x2D2B4
 * D:\driver2\game\C\CIV_AI.C (line 918)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ NotTravellingAlongCurve(int x /*$a0*/, int z /*$a1*/, int dir /*$s0*/, struct DRIVER2_CURVE *cv /*$a3*/)
{ // line 1, offset 0x2d2b4
} // line 9, offset 0x2d300
/*
 * Offset 0x2D36C
 * D:\driver2\game\C\CONVERT.C (line 272)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ BuildWorldMatrix()
{ // line 2, offset 0x2d36c
  struct MATRIX newmatrix; // stack offset -48
} // line 17, offset 0x2d460
/*
 * Offset 0x2D460
 * D:\driver2\game\C\CONVERT.C (line 149)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ Calc_Object_MatrixYZX(struct MATRIX *mat /*$s0*/, struct SVECTOR *angles /*$s1*/)
{
}
/*
 * Offset 0x2D4D8
 * D:\driver2\game\C\CONVERT.C (line 182)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ _RotMatrixX(struct MATRIX *m /*$v0*/, short ang /*$a1*/)
{
}
/*
 * Offset 0x2D504
 * D:\driver2\game\C\CONVERT.C (line 187)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ _RotMatrixY(struct MATRIX *m /*$v0*/, short ang /*$a1*/)
{
}
/*
 * Offset 0x2D530
 * D:\driver2\game\C\CONVERT.C (line 192)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ _RotMatrixZ(struct MATRIX *m /*$v0*/, short ang /*$a1*/)
{
}
/*
 * Offset 0x2D55C
 * D:\driver2\game\C\CONVERT.C (line 199)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ RotMatrixXYZ(struct MATRIX *m /*$v0*/, struct SVECTOR *r /*$a1*/)
{
}
/*
 * Offset 0x2D584
 * D:\driver2\game\C\CONVERT.C (line 205)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ _MatrixRotate(struct VECTOR *pos /*$s0*/)
{ // line 1, offset 0x2d584
  struct VECTOR temp; // stack offset -24
} // line 9, offset 0x2d5c4
/*
 * Offset 0x2D5C4
 * D:\driver2\game\C\CONVERT.C (line 240)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InvertMatrix(struct MATRIX *a /*$a0*/, struct MATRIX *b /*$a1*/)
{
}
/*
 * Offset 0x2D630
 * D:\driver2\game\C\CONVERT.C (line 334)
 * Stack frame base $sp, size 176
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ScaleCamera()
{ // line 2, offset 0x2d630
  struct MATRIX temp; // stack offset -160
  struct MATRIX temp2; // stack offset -128
  struct MATRIX scale; // stack offset -96
  struct MATRIX scaledcammat; // stack offset -64
  struct VECTOR pos; // stack offset -32
  struct SVECTOR tempang; // stack offset -16
} // line 27, offset 0x2d6e0
/*
 * Offset 0x2D6E0
 * D:\driver2\game\C\CONVERT.C (line 365)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ Getlong(char *dest /*$a0*/, char *source /*$a1*/)
{
}
/*
 * Offset 0x2D710
 * D:\driver2\game\C\CONVERT.C (line 387)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ RandomInit(long i1 /*$a0*/, long i2 /*$a1*/)
{ // line 2, offset 0x2d710
  int count; // $s0
} // line 15, offset 0x2d78c
/*
 * Offset 0x2D78C
 * D:\driver2\game\C\CONVERT.C (line 414)
 * Stack frame base $sp, size 0
 */
long /*$ra*/ Random2(int step /*$a0*/)
{ // line 2, offset 0x2d78c
  unsigned int seed; // $a0
} // line 6, offset 0x2d7f4
/*
 * Offset 0x2D7F4
 * D:\driver2\game\C\COP_AI.C (line 593)
 * Stack frame base $sp, size 152
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ WibbleDownTheRoad(struct VECTOR *from /*$a0*/, int distance /*$s1*/, struct VECTOR *to /*$s5*/)
{ // line 1, offset 0x2d7f4
  int th; // $s0
  int j; // $s3
  int thl[4]; // stack offset -136
  struct VECTOR pos; // stack offset -120
  struct VECTOR dir; // stack offset -104
  { // line 11, offset 0x2d878
    struct VECTOR p2; // stack offset -88
    struct VECTOR d2; // stack offset -72
    int colour[3]; // stack offset -56
  } // line 21, offset 0x2d904
} // line 46, offset 0x2da04
/*
 * Offset 0x2DA04
 * D:\driver2\game\C\COP_AI.C (line 643)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitCops()
{
}
/*
 * Offset 0x2DB40
 * D:\driver2\game\C\COP_AI.C (line 708)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ ControlCops()
{ // line 2, offset 0x2db40
  { // line 18, offset 0x2db9c
    int playerID; // $v1
  } // line 21, offset 0x2dbdc
  { // line 41, offset 0x2dcd4
    int heading; // $s1
    int rnd; // $s0
  } // line 66, offset 0x2de04
  { // line 76, offset 0x2de64
    int copsWereInPursuit; // $a1
  } // line 90, offset 0x2df04
  { // line 93, offset 0x2df14
  } // line 99, offset 0x2df48
} // line 101, offset 0x2df48
/*
 * Offset 0x2DF64
 * D:\driver2\game\C\COP_AI.C (line 845)
 * Stack frame base $sp, size 104
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ CopControl1(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, offset 0x2df64
  int currentSpeed; // $s7
  int desiredSteerAngle; // $s4
  { // line 48, offset 0x2e02c
    int dx; // $a1
    int dz; // $a0
    { // line 52, offset 0x2e080
    } // line 60, offset 0x2e0c0
  } // line 61, offset 0x2e0c0
  { // line 67, offset 0x2e0d8
    struct VECTOR pos; // stack offset -88
  } // line 77, offset 0x2e2a4
  { // line 90, offset 0x2e2a4
    enum AIZone targetZone; // $a0
    struct VECTOR doordir; // stack offset -72
    int targetFound; // $a1
    int cx; // $s5
    int cz; // $s6
    int dvx; // $s0
    int dvz; // $s3
    int dist; // $s2
    int framesToImpact; // $a1
    { // line 139, offset 0x2e3c8
      int dz; // $a1
      int idvx; // $v1
      int idvz; // $v0
    } // line 139, offset 0x2e3c8
    { // line 204, offset 0x2e64c
      struct iVectNT path[2]; // stack offset -56
      int slidevel; // $a3
      { // line 260, offset 0x2e950
        int plcrspd; // $a1
      } // line 263, offset 0x2e9bc
    } // line 279, offset 0x2ea90
    { // line 295, offset 0x2eae0
      int b; // $a0
    } // line 300, offset 0x2eb28
    { // line 304, offset 0x2eb28
      int steerdif; // $v1
      int speeddif; // $a2
      int maxPower; // $a1
      { // line 330, offset 0x2ec20
        int sf; // $v1
      } // line 332, offset 0x2ec38
    } // line 343, offset 0x2eccc
  } // line 343, offset 0x2eccc
  { // line 352, offset 0x2ecec
  } // line 356, offset 0x2ed14
} // line 358, offset 0x2ed14
/*
 * Offset 0x2ED40
 * D:\driver2\game\C\COP_AI.C (line 1368)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ ControlCopDetection()
{ // line 14, offset 0x2ed40
  int dx; // $v1
  int dz; // $a0
  struct VECTOR vec; // stack offset -64
  int ccx; // stack offset -32
  int ccz; // stack offset -28
  char *scratch; // $s4
  struct _CAR_DATA *lcp; // $s1
  { // line 17, offset 0x2ed40
    { // line 17, offset 0x2ed40
      int angry; // $v1
    } // line 23, offset 0x2ee10
  } // line 23, offset 0x2ee10
  { // line 48, offset 0x2ee64
    int dx; // $v1
    int dz; // $v0
  } // line 58, offset 0x2eee4
  { // line 66, offset 0x2ef38
    int distanceToPlayer; // $s0
    int active; // $s2
    { // line 1, offset 0x2efd8
      struct _CAR_DATA *cp; // $s1
      int distanceToPlayer; // $s0
      { // line 1, offset 0x2efd8
        int farDist; // $v1
        int nearDist; // $v0
        char result; // $s2
        { // line 1, offset 0x2eff8
          int theta; // $v1
          struct VECTOR delta; // stack offset -48
          { // line 1, offset 0x2f098
          } // line 1, offset 0x2f09c
        } // line 1, offset 0x2f09c
      } // line 1, offset 0x2f09c
    } // line 1, offset 0x2f09c
  } // line 84, offset 0x2f0b8
  { // line 110, offset 0x2f1cc
  } // line 110, offset 0x2f1cc
  { // line 123, offset 0x2f1f8
    { // line 130, offset 0x2f220
    } // line 150, offset 0x2f290
  } // line 152, offset 0x2f2a0
  { // line 157, offset 0x2f2c4
    int rnd; // $s0
    int dir; // $s1
  } // line 161, offset 0x2f330
  { // line 166, offset 0x2f364
    int rnd; // $s0
    int dir; // $s1
  } // line 168, offset 0x2f3fc
} // line 174, offset 0x2f434
/*
 * Offset 0x2F434
 * D:\driver2\game\C\COP_AI.C (line 1583)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ControlNumberOfCops()
{ // line 2, offset 0x2f434
  int numWantedCops; // $t2
  { // line 5, offset 0x2f434
    short *pTrigger; // $a2
  } // line 13, offset 0x2f4bc
  { // line 26, offset 0x2f508
    int temp; // $a1
  } // line 41, offset 0x2f5b4
  { // line 50, offset 0x2f5d8
    int num_closer; // $a2
    int cutOffDistance; // $a1
    { // line 55, offset 0x2f5e8
      struct _CAR_DATA *lcp; // $a0
      int tempDist; // $a3
      { // line 64, offset 0x2f614
        int copDist; // $v1
      } // line 75, offset 0x2f634
    } // line 78, offset 0x2f644
  } // line 81, offset 0x2f650
} // line 88, offset 0x2f674
/*
 * Offset 0x2F674
 * D:\driver2\game\C\COP_AI.C (line 824)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ CopControl(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, offset 0x2f674
} // line 18, offset 0x2f6e8
/*
 * Offset 0x2F6E8
 * D:\driver2\game\C\COP_AI.C (line 577)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ InitCopState(struct _CAR_DATA *cp /*$s0*/, char *extraData /*$a1*/)
{
}
/*
 * Offset 0x2F764
 * D:\driver2\game\C\COP_AI.C (line 1562)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ PassiveCopTasks(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x2f764
  { // line 1, offset 0x2f7d4
    struct _CAR_DATA *cp; // $s0
  } // line 1, offset 0x2f82c
} // line 14, offset 0x2f860
/*
 * Offset 0x2F860
 * D:\driver2\game\C\COP_AI.C (line 1267)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitCopData(struct COP_DATA *pCopData /*$a0*/)
{ // line 1, offset 0x2f860
  short *pTrigger; // $v1
  short trigger; // $a2
} // line 14, offset 0x2f8ac
/*
 * Offset 0x2F8AC
 * D:\driver2\game\C\COP_AI.C (line 1308)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ UpdateCopSightData()
{ // line 2, offset 0x2f8ac
  int angry; // $v1
} // line 6, offset 0x2f944
/*
 * Offset 0x2F944
 * D:\driver2\game\C\COP_AI.C (line 1231)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ FindCost(int x /*$a0*/, int z /*$a1*/, int dvx /*$a2*/, int dvz /*$a3*/)
{ // line 1, offset 0x2f944
  int tx; // $v0
  int tz; // $v0
  int dx; // $a2
  int dz; // $v1
  int d; // $v0
} // line 13, offset 0x2f9fc
/*
 * Offset 0x2F9FC
 * D:\driver2\game\C\COSMETIC.C (line 252)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ AddReverseLight(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, offset 0x2f9fc
  struct CAR_COSMETICS *car_cos; // $a1
  struct SVECTOR v1; // stack offset -32
  struct CVECTOR col; // stack offset -24
  short cogOffset; // $s2
} // line 31, offset 0x2fb54
/*
 * Offset 0x2FB54
 * D:\driver2\game\C\COSMETIC.C (line 325)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ AddIndicatorLight(struct _CAR_DATA *cp /*$s0*/, int Type /*$s6*/)
{ // line 1, offset 0x2fb54
  struct CAR_COSMETICS *car_cos; // $a1
  struct CVECTOR col; // stack offset -56
  struct SVECTOR vfrnt; // stack offset -48
  struct SVECTOR vback; // stack offset -40
  char tempcol; // $s1
  char *life; // $a0
  char *life2; // $s3
  short cogOffset; // $s2
} // line 72, offset 0x2fe24
/*
 * Offset 0x2FE4C
 * D:\driver2\game\C\COSMETIC.C (line 407)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddBrakeLight(struct _CAR_DATA *cp /*$s5*/)
{ // line 1, offset 0x2fe4c
  struct CAR_COSMETICS *car_cos; // $a1
  struct SVECTOR v1; // stack offset -88
  struct SVECTOR v2; // stack offset -80
  struct SVECTOR vec; // stack offset -72
  struct CVECTOR col; // stack offset -64
  char *life2; // $s2
  short doubleFlag; // stack offset -56
  short verticalFlag; // stack offset -52
  short offset; // $s1
  short loop; // $fp
  short damIndex; // $v0
  short cogOffset; // $a3
} // line 97, offset 0x30180
/*
 * Offset 0x301B0
 * D:\driver2\game\C\COSMETIC.C (line 514)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddCopCarLight(struct _CAR_DATA *cp /*$t0*/)
{ // line 1, offset 0x301b0
  int size; // $a3
  int light; // $s1
  int pos; // $s3
  int side; // $s4
  int num_lights; // $t5
  int count_speed; // $t4
  char col1; // $a2
  char col2; // $a1
  static char xpos1[8]; // offset 0x10
  int sign; // $t1
  char *coplife; // $s2
  struct SVECTOR v1; // stack offset -88
  struct CVECTOR col; // stack offset -80
  struct CAR_COSMETICS *car_cos; // $s0
  short cogOffset; // $fp
} // line 130, offset 0x3057c
/*
 * Offset 0x305AC
 * D:\driver2\game\C\COSMETIC.C (line 653)
 * Stack frame base $sp, size 128
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddNightLights(struct _CAR_DATA *cp /*$s6*/)
{ // line 1, offset 0x305ac
  static struct MATRIX work_matrix; // offset 0x0
  struct CAR_COSMETICS *car_cos; // $fp
  struct SVECTOR Position1; // stack offset -104
  struct SVECTOR Position2; // stack offset -96
  struct SVECTOR vec; // stack offset -88
  struct CVECTOR col; // stack offset -80
  int lit; // stack offset -72
  int lightFlag; // $t0
  char *life2; // stack offset -68
  short damIndex; // $s5
  short loop; // stack offset -64
  short offset; // $s2
  short doubleFlag; // stack offset -60
  short verticalFlag; // stack offset -56
  short cogOffset; // stack offset -52
} // line 266, offset 0x30e04
/*
 * Offset 0x30E04
 * D:\driver2\game\C\COSMETIC.C (line 989)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ AddSmokingEngine(struct _CAR_DATA *cp /*$s0*/, int black_smoke /*$s2*/, int WheelSpeed /*$s3*/)
{ // line 1, offset 0x30e04
  struct VECTOR SmokePos; // stack offset -64
  struct CAR_COSMETICS *car_cos; // $a0
  struct VECTOR Drift; // stack offset -48
  struct SVECTOR svec; // stack offset -32
} // line 49, offset 0x30ff8
/*
 * Offset 0x31014
 * D:\driver2\game\C\COSMETIC.C (line 1048)
 * Stack frame base $sp, size 88
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ AddFlamingEngine(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, offset 0x31014
  struct VECTOR SmokePos; // stack offset -56
  struct SVECTOR svec; // stack offset -40
  struct CAR_COSMETICS *car_cos; // $a0
  struct VECTOR Drift; // stack offset -32
} // line 36, offset 0x311b4
/*
 * Offset 0x311C8
 * D:\driver2\game\C\COSMETIC.C (line 188)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ LoadCosmetics(int level /*$a0*/)
{ // line 2, offset 0x311c8
} // line 15, offset 0x31218
/*
 * Offset 0x31218
 * D:\driver2\game\C\COSMETIC.C (line 213)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ ProcessCosmeticsLump(char *lump_ptr /*$s2*/, int lump_size /*$a1*/)
{ // line 1, offset 0x31218
  int i; // $t0
  int model; // $a1
  int offset; // $a0
  { // line 23, offset 0x312a0
  } // line 27, offset 0x313a0
} // line 30, offset 0x313c8
/*
 * Offset 0x313C8
 * D:\driver2\game\C\COSMETIC.C (line 293)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupSpecCosmetics(char *loadbuffer /*$a0*/)
{ // line 5, offset 0x313c8
  int *to; // $a1
  int *from; // $a0
  int *end; // $v1
} // line 18, offset 0x31400
/*
 * Offset 0x31400
 * D:\driver2\game\C\CUTSCENE.C (line 646)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawInGameCutscene()
{ // line 2, offset 0x31400
  struct TILE *tile; // $s0
} // line 30, offset 0x31550
/*
 * Offset 0x31550
 * D:\driver2\game\C\CUTSCENE.C (line 683)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ TriggerChase(int *car /*$s2*/, int cutscene /*$a1*/)
{ // line 1, offset 0x31550
  void *inform; // $s3
  int i; // $a0
  int length; // $s1
  { // line 12, offset 0x315c0
  } // line 38, offset 0x3170c
} // line 42, offset 0x31754
/*
 * Offset 0x31754
 * D:\driver2\game\C\CUTSCENE.C (line 838)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ ReleaseInGameCutscene()
{ // line 2, offset 0x31754
  { // line 7, offset 0x317b0
    struct STREAM_SOURCE *pinfo; // $a0
    int i; // $s0
  } // line 79, offset 0x319e0
} // line 105, offset 0x31a88
/*
 * Offset 0x31A88
 * D:\driver2\game\C\CUTSCENE.C (line 1040)
 * Stack frame base $sp, size 96
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ TriggerInGameCutsceneSystem(int cutscene /*$a0*/)
{ // line 1, offset 0x31a88
  static char padid[8]; // offset 0x0
  int bDamageOverride; // stack offset -64
  int i; // $s2
  int id; // $v1
  { // line 18, offset 0x31acc
    { // line 54, offset 0x31c2c
      int car; // $v1
      int model; // $v1
      int palette; // $a1
    } // line 65, offset 0x31c84
    { // line 85, offset 0x31d14
      { // line 90, offset 0x31d74
        int car; // $v1
      } // line 104, offset 0x31df8
    } // line 112, offset 0x31df8
  } // line 146, offset 0x31f08
} // line 151, offset 0x31f44
/*
 * Offset 0x31F44
 * D:\driver2\game\C\CUTSCENE.C (line 1199)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetNullPlayer(int plr /*$a0*/)
{ // line 1, offset 0x31f44
} // line 14, offset 0x31fc8
/*
 * Offset 0x31FC8
 * D:\driver2\game\C\CUTSCENE.C (line 1221)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetNullPlayerDontKill(int plr /*$a0*/)
{ // line 1, offset 0x31fc8
} // line 14, offset 0x32048
/*
 * Offset 0x32048
 * D:\driver2\game\C\CUTSCENE.C (line 1244)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ DestroyPlayer(int plr /*$s0*/, int fully /*$a1*/)
{
}
/*
 * Offset 0x32180
 * D:\driver2\game\C\CUTSCENE.C (line 1299)
 * Stack frame base $sp, size 104
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ LoadCutsceneToReplayBuffer(int residentCutscene /*$a0*/)
{ // line 2, offset 0x32180
  struct REPLAY_SAVE_HEADER *rheader; // $a1
  struct REPLAY_STREAM_HEADER *sheader; // $t1
  char filename[64]; // stack offset -88
  char *pt; // $s1
  int i; // $a0
  int size; // $s0
} // line 56, offset 0x324a4
/*
 * Offset 0x324A4
 * D:\driver2\game\C\CUTSCENE.C (line 1362)
 * Stack frame base $sp, size 456
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ LoadCutsceneToBuffer(int subindex /*$s3*/)
{ // line 1, offset 0x324a4
  struct CUTSCENE_HEADER header; // stack offset -440
  struct REPLAY_SAVE_HEADER rheader; // stack offset -376
  char filename[64]; // stack offset -88
  int offset; // $a2
  int size; // $s0
} // line 78, offset 0x32628
/*
 * Offset 0x32628
 * D:\driver2\game\C\CUTSCENE.C (line 566)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitInGameCutsceneVariables()
{
}
/*
 * Offset 0x32694
 * D:\driver2\game\C\CUTSCENE.C (line 594)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ HandleInGameCutscene()
{ // line 2, offset 0x32694
  { // line 37, offset 0x32774
  } // line 48, offset 0x32798
} // line 50, offset 0x327a8
/*
 * Offset 0x327A8
 * D:\driver2\game\C\CUTSCENE.C (line 732)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ TriggerInGameCutscene(int cutscene /*$s0*/)
{ // line 1, offset 0x327a8
  { // line 30, offset 0x32858
  } // line 37, offset 0x32894
} // line 38, offset 0x32894
/*
 * Offset 0x328A4
 * D:\driver2\game\C\CUTSCENE.C (line 778)
 * Stack frame base $sp, size 152
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ CalcInGameCutsceneSize()
{ // line 39, offset 0x328a4
  struct CUTSCENE_HEADER header; // stack offset -136
  char filename[64]; // stack offset -72
} // line 52, offset 0x32930
/*
 * Offset 0x32930
 * D:\driver2\game\C\CUTSCENE.C (line 951)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ PreLoadInGameCutscene(int chase /*$a0*/)
{
}
/*
 * Offset 0x32950
 * D:\driver2\game\C\CUTSCENE.C (line 965)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ CutsceneCameraChange(int cameracnt /*$s0*/)
{
}
/*
 * Offset 0x32A1C
 * D:\driver2\game\C\CUTSCENE.C (line 1010)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ LoadInGameCutscene(int subindex /*$s1*/)
{ // line 1, offset 0x32a1c
  int ret; // $s0
} // line 23, offset 0x32a9c
/*
 * Offset 0x32A9C
 * D:\driver2\game\C\CUTSCENE.C (line 1274)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ FindNextCutChange(int cameracnt /*$a0*/)
{ // line 1, offset 0x32a9c
  int found; // $t0
  int count; // $a3
  int nextframe; // $a2
} // line 17, offset 0x32b00
/*
 * Offset 0x32B00
 * D:\driver2\game\C\CUTSCENE.C (line 1471)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ LoadCutsceneInformation(int cutscene /*$s2*/)
{ // line 1, offset 0x32b00
  int i; // $s1
} // line 27, offset 0x32bbc
/*
 * Offset 0x32BBC
 * D:\driver2\game\C\CUTSCENE.C (line 1505)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ FreeCutsceneBuffer()
{ // line 2, offset 0x32bbc
  int i; // $v1
} // line 13, offset 0x32c28
/*
 * Offset 0x32C28
 * D:\driver2\game\C\CUTSCENE.C (line 1520)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ IsCutsceneResident(int cutscene /*$a0*/)
{ // line 1, offset 0x32c28
  int i; // $a1
} // line 13, offset 0x32c70
/*
 * Offset 0x32C70
 * D:\driver2\game\C\CUTSCENE.C (line 1442)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ShowCutsceneError()
{
}
/*
 * Offset 0x32C78
 * D:\driver2\game\C\DEBRIS.C (line 790)
 * Stack frame base $sp, size 848
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ PlacePoolForCar(struct _CAR_DATA *cp /*$s4*/, struct CVECTOR *col /*stack 4*/, int front /*$a2*/)
{ // line 1, offset 0x32c78
  int car_road_height; // $s2
  struct SVECTOR s[27]; // stack offset -832
  struct SVECTOR *ptr; // $s1
  struct SVECTOR sout[27]; // stack offset -616
  struct VECTOR s1[12]; // stack offset -400
  struct VECTOR *ptr1; // $s0
  struct POLY_FT4 *poly; // $t0
  struct MATRIX final_matrix; // stack offset -208
  struct VECTOR averagepos; // stack offset -176
  int in_car; // $t0
  int z; // stack offset -48
  int sub_level; // $fp
  int count; // $s3
  struct VECTOR mid_position; // stack offset -160
  { // line 23, offset 0x32d54
    short farz; // $a2
    short nearz; // $a0
  } // line 108, offset 0x32f28
  { // line 114, offset 0x32f38
  } // line 130, offset 0x32fa0
  { // line 147, offset 0x3301c
    struct VECTOR toss; // stack offset -144
    int temp_y; // $a1
  } // line 161, offset 0x330d4
  { // line 164, offset 0x3310c
    long n[4]; // stack offset -128
  } // line 170, offset 0x331d4
  { // line 177, offset 0x33258
    int count; // $s2
    { // line 206, offset 0x3342c
      long z[15]; // stack offset -112
      { // line 216, offset 0x33484
        char *VertIdx; // $s0
        { // line 228, offset 0x33504
        } // line 233, offset 0x33594
      } // line 234, offset 0x33594
    } // line 235, offset 0x335a4
  } // line 237, offset 0x335a4
} // line 239, offset 0x335ac
/*
 * Offset 0x335DC
 * D:\driver2\game\C\DEBRIS.C (line 1327)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ AddLeaf(struct VECTOR *Position /*$s1*/, int num_leaves /*$s5*/, int Type /*$s3*/)
{ // line 1, offset 0x335dc
  struct LEAF *myleaf; // $a1
  int num; // $v1
  int loop; // $s2
  int temprand; // $s0
  { // line 16, offset 0x33640
    { // line 74, offset 0x3374c
    } // line 79, offset 0x33760
    { // line 83, offset 0x33774
      int temp; // $v0
    } // line 83, offset 0x33774
    { // line 89, offset 0x337a0
      int temp; // $v0
    } // line 92, offset 0x337b4
  } // line 93, offset 0x337b4
} // line 101, offset 0x337ec
/*
 * Offset 0x33814
 * D:\driver2\game\C\DEBRIS.C (line 1493)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ InitDebrisNames()
{ // line 2, offset 0x33814
} // line 62, offset 0x33c04
/*
 * Offset 0x33C04
 * D:\driver2\game\C\DEBRIS.C (line 1564)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ InitDebris()
{ // line 2, offset 0x33c04
  int loop; // $v1
  int count; // $s0
  struct TPAN texnum; // stack offset -88
  struct TRI_POINT_LONG temptri; // stack offset -80
  struct BVECTOR *debrisPTR; // $a0
  { // line 37, offset 0x33d5c
    { // line 41, offset 0x33d78
    } // line 46, offset 0x33de8
  } // line 63, offset 0x33e94
} // line 110, offset 0x34010
/*
 * Offset 0x34010
 * D:\driver2\game\C\DEBRIS.C (line 1753)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ AddGroundDebris()
{ // line 2, offset 0x34010
  struct VECTOR Position; // stack offset -48
  int seed; // $s0
  int number; // $v0
  int count; // $s3
  int xbound; // $a1
  int zbound; // $a0
  int type; // $a2
  struct CELL_OBJECT *cop; // $s1
  struct MODEL *model; // $s2
  { // line 30, offset 0x340e4
  } // line 51, offset 0x34168
} // line 54, offset 0x34178
/*
 * Offset 0x341A0
 * D:\driver2\game\C\DEBRIS.C (line 1815)
 * Stack frame base $sp, size 144
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawSmashable_sprites()
{ // line 2, offset 0x341a0
  int count; // $s6
  struct VECTOR pos; // stack offset -128
  struct DAMAGED_OBJECT *dam; // $s2
  { // line 11, offset 0x3420c
    struct MATRIX object_matrix; // stack offset -112
    struct MATRIX spritematrix; // stack offset -80
    struct MATRIX *finalmatrix; // $s0
    struct MODEL *model; // $s3
    { // line 46, offset 0x343c4
      unsigned long colours; // $a0
    } // line 55, offset 0x3441c
  } // line 60, offset 0x34450
} // line 62, offset 0x3448c
/*
 * Offset 0x3448C
 * D:\driver2\game\C\DEBRIS.C (line 1925)
 * Stack frame base $sp, size 128
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddSmallStreetLight(struct CELL_OBJECT *cop /*$s1*/, int x /*$s3*/, int y /*$s6*/, int z /*$s4*/, int type /*stack 16*/)
{ // line 1, offset 0x3448c
  struct VECTOR v1; // stack offset -112
  struct VECTOR v2; // stack offset -96
  struct VECTOR v3; // stack offset -80
  struct SVECTOR pos; // stack offset -64
  struct CVECTOR col; // stack offset -56
  struct CVECTOR col1; // stack offset -48
  int count; // $v1
  short angle; // $s2
  int halo_size; // $fp
  int size; // $s5
  int LampId; // $s7
  struct DAMAGED_LAMP *dam; // $s0
  { // line 36, offset 0x34554
  } // line 42, offset 0x345a8
} // line 114, offset 0x34890
/*
 * Offset 0x348C0
 * D:\driver2\game\C\DEBRIS.C (line 2049)
 * Stack frame base $sp, size 104
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ AddLightEffect(struct CELL_OBJECT *cop /*$t0*/, int x /*$t2*/, int y /*$a2*/, int z /*$a3*/, int type /*stack 16*/, int colour /*stack 20*/)
{ // line 1, offset 0x348c0
  struct VECTOR v1; // stack offset -88
  struct VECTOR v2; // stack offset -72
  struct VECTOR v3; // stack offset -56
  struct SVECTOR pos; // stack offset -40
  struct CVECTOR col; // stack offset -32
  struct CVECTOR col1; // stack offset -24
  short angle; // $v1
  int size; // $s1
} // line 126, offset 0x34cd4
/*
 * Offset 0x34CD4
 * D:\driver2\game\C\DEBRIS.C (line 2178)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ PreLampStreak()
{ // line 2, offset 0x34cd4
  int count; // $a3
} // line 20, offset 0x34d84
/*
 * Offset 0x34D84
 * D:\driver2\game\C\DEBRIS.C (line 2230)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ damage_lamp(struct CELL_OBJECT *cop /*$a2*/)
{ // line 1, offset 0x34d84
  int count; // $v1
  int old_damage; // $v0
} // line 15, offset 0x34e14
/*
 * Offset 0x34E14
 * D:\driver2\game\C\DEBRIS.C (line 2255)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ damage_object(struct CELL_OBJECT *cop /*$s1*/, struct VECTOR *velocity /*$a1*/)
{ // line 1, offset 0x34e14
  struct DAMAGED_OBJECT *dam; // $s0
  { // line 1, offset 0x34e14
    struct PACKED_CELL_OBJECT *pcop; // $a0
  } // line 1, offset 0x34e14
} // line 63, offset 0x34fcc
/*
 * Offset 0x34FCC
 * D:\driver2\game\C\DEBRIS.C (line 2326)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ AddTrafficLight(struct CELL_OBJECT *cop /*$t4*/, int x /*$t6*/, int y /*$t7*/, int z /*$a3*/, int flag /*stack 16*/, int yang /*stack 20*/)
{ // line 1, offset 0x34fcc
  struct CVECTOR a; // stack offset -80
  struct CVECTOR b; // stack offset -72
  struct CVECTOR c; // stack offset -64
  struct VECTOR v1; // stack offset -56
  struct VECTOR v2; // stack offset -40
  int lDiffAnglesX; // $s2
  int lDiffAnglesY; // $s1
  int AbsX; // $a2
  int AbsY; // $a1
  int tempfade; // $v0
  { // line 1, offset 0x34fcc
    int c; // $t1
    int s; // $t2
  } // line 1, offset 0x34fcc
} // line 90, offset 0x35318
/*
 * Offset 0x35334
 * D:\driver2\game\C\DEBRIS.C (line 2462)
 * Stack frame base $sp, size 88
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ ShowCarlight(struct SVECTOR *v1 /*$s6*/, struct _CAR_DATA *cp /*$s3*/, struct CVECTOR *col /*$s1*/, short size /*$s5*/, struct TEXTURE_DETAILS *texture /*stack 16*/, int flag /*stack 20*/)
{ // line 1, offset 0x35334
  int CarLightFade; // $a1
  struct VECTOR v1t; // stack offset -72
  struct VECTOR v1l; // stack offset -56
  struct CVECTOR flareCol; // stack offset -40
  int front; // $a0
} // line 52, offset 0x3559c
/*
 * Offset 0x355C4
 * D:\driver2\game\C\DEBRIS.C (line 2523)
 * Stack frame base $sp, size 40
 */
void /*$ra*/ ShowLight1(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$a1*/, short size /*$a2*/, struct TEXTURE_DETAILS *texture /*$a3*/)
{ // line 1, offset 0x355c4
  struct SVECTOR vert[4]; // stack offset -40
  struct POLY_FT4 *poly; // $t0
  int z; // stack offset -8
} // line 52, offset 0x357b0
/*
 * Offset 0x357B8
 * D:\driver2\game\C\DEBRIS.C (line 2579)
 * Stack frame base $sp, size 104
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ShowLight(struct VECTOR *v1 /*$s0*/, struct CVECTOR *col /*$s3*/, short size /*$s4*/, struct TEXTURE_DETAILS *texture /*$s2*/)
{ // line 1, offset 0x357b8
  struct SVECTOR vert[4]; // stack offset -88
  struct POLY_FT4 *poly; // $s1
  int z; // stack offset -40
  int index; // $a1
  int tail_width; // $s5
  { // line 65, offset 0x35abc
    int loop; // $a1
  } // line 71, offset 0x35b14
  { // line 75, offset 0x35b3c
    struct POLY_G4 *poly1; // $s0
    int dx; // $a0
    int dy; // $v0
    int angle; // $v0
    int width; // $s2
    int c; // $a0
    int s; // $a2
    int length; // $v0
    struct SVECTOR tail; // stack offset -56
    struct SVECTOR head; // stack offset -48
  } // line 130, offset 0x35f20
  { // line 148, offset 0x35fd0
    int loop; // $a3
  } // line 154, offset 0x36050
  { // line 158, offset 0x3608c
    struct POLY_G4 *poly1; // $s0
    int dx; // $a2
    int dy; // $a1
    int angle; // $v0
    int width; // $s1
    int c; // $a2
    int s; // $a1
    int length; // $v0
    struct SVECTOR tail; // stack offset -56
    struct SVECTOR head; // stack offset -48
  } // line 213, offset 0x36470
} // line 215, offset 0x36470
/*
 * Offset 0x36494
 * D:\driver2\game\C\DEBRIS.C (line 2804)
 * Stack frame base $sp, size 40
 */
void /*$ra*/ ShowGroundLight(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$a1*/, short size /*$a2*/)
{ // line 1, offset 0x36494
  struct SVECTOR vert[4]; // stack offset -40
  struct POLY_FT4 *poly; // $t0
  int z; // stack offset -8
} // line 54, offset 0x366e8
/*
 * Offset 0x366F0
 * D:\driver2\game\C\DEBRIS.C (line 2869)
 * Stack frame base $sp, size 40
 */
void /*$ra*/ RoundShadow(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$a1*/, short size /*$a2*/)
{ // line 1, offset 0x366f0
  struct SVECTOR vert[4]; // stack offset -40
  struct POLY_FT4 *poly; // $t0
  int z; // stack offset -8
} // line 64, offset 0x36938
/*
 * Offset 0x36940
 * D:\driver2\game\C\DEBRIS.C (line 2945)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ ShowFlare(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$s2*/, short size /*$a2*/, int rotation /*$a3*/)
{ // line 1, offset 0x36940
  struct SVECTOR vert[4]; // stack offset -96
  struct POLY_FT4 *poly; // $t0
  struct SVECTOR direction; // stack offset -64
  struct MATRIX temp_matrix; // stack offset -56
  int z; // stack offset -24
} // line 71, offset 0x36bbc
/*
 * Offset 0x36BD4
 * D:\driver2\game\C\DEBRIS.C (line 3029)
 * Stack frame base $sp, size 64
 */
void /*$ra*/ DisplayWater(struct SMOKE *smoke /*$a0*/)
{ // line 1, offset 0x36bd4
  struct POLY_FT4 *poly; // $t1
  struct VECTOR v; // stack offset -64
  struct SVECTOR vert[4]; // stack offset -48
  int size; // $t1
  int z; // $v0
  int z1; // stack offset -16
  int z2; // stack offset -12
  int z3; // stack offset -8
  int z4; // stack offset -4
} // line 58, offset 0x36e80
/*
 * Offset 0x36E80
 * D:\driver2\game\C\DEBRIS.C (line 3102)
 * Stack frame base $sp, size 40
 */
void /*$ra*/ DisplaySpark(struct SMOKE *spark /*$t1*/)
{ // line 1, offset 0x36e80
  int z; // stack offset -8
  struct SVECTOR v[3]; // stack offset -40
  struct SVECTOR TrailPos; // stack offset -16
  struct POLY_G3 *poly; // $t0
  { // line 33, offset 0x36f98
    unsigned char *col; // $a0
  } // line 48, offset 0x37048
} // line 68, offset 0x371b8
/*
 * Offset 0x371C0
 * D:\driver2\game\C\DEBRIS.C (line 3182)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ GetSmokeDrift(struct VECTOR *Wind /*$t2*/)
{ // line 1, offset 0x371c0
  static int SinTabIndex1; // offset 0x158
  static int SinTabIndex2; // offset 0x15c
  static int SinTabIndex3; // offset 0x160
  static int WindMagnitude; // offset 0x164
  static int SinX; // offset 0x0
  static int CosX; // offset 0x4
} // line 33, offset 0x372b8
/*
 * Offset 0x372B8
 * D:\driver2\game\C\DEBRIS.C (line 3227)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ Setup_Debris(struct VECTOR *ipos /*$fp*/, struct VECTOR *ispeed /*$s6*/, int num_debris /*$s7*/, int type /*$s5*/)
{ // line 1, offset 0x372b8
  struct DEBRIS *mydebris; // $s1
  int num; // $v1
  int loop; // $s4
  int vx; // $s2
  int vy; // $s3
  int vz; // $a2
  int seed; // $s0
  int col; // $a3
  { // line 18, offset 0x3735c
  } // line 32, offset 0x3741c
} // line 58, offset 0x374ac
/*
 * Offset 0x374DC
 * D:\driver2\game\C\DEBRIS.C (line 3296)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ Setup_Smoke(struct VECTOR *ipos /*$s1*/, int start_w /*$s3*/, int end_w /*$s4*/, int SmokeType /*$s7*/, int WheelSpeed /*stack 16*/, struct VECTOR *Drift /*stack 20*/, int Exhaust /*stack 24*/)
{ // line 1, offset 0x374dc
  struct SMOKE *mysmoke; // $s0
  int num; // $v1
  { // line 39, offset 0x375fc
  } // line 39, offset 0x375fc
  { // line 76, offset 0x37708
  } // line 76, offset 0x37708
  { // line 86, offset 0x37754
  } // line 91, offset 0x37790
  { // line 127, offset 0x37874
  } // line 138, offset 0x378ec
} // line 167, offset 0x37988
/*
 * Offset 0x379B8
 * D:\driver2\game\C\DEBRIS.C (line 3475)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ Setup_Sparks(struct VECTOR *ipos /*$fp*/, struct VECTOR *ispeed /*$s7*/, int num_sparks /*stack 8*/, char SparkType /*$s5*/)
{ // line 1, offset 0x379b8
  struct SMOKE *mysmoke; // $s2
  int num; // $s0
  int loop; // $s4
  int vx; // $s1
  int vy; // $s0
  int vz; // $v1
  int randtemp; // $v0
  { // line 12, offset 0x37a08
  } // line 74, offset 0x37b38
} // line 75, offset 0x37b4c
/*
 * Offset 0x37B7C
 * D:\driver2\game\C\DEBRIS.C (line 3564)
 * Stack frame base $sp, size 56
 */
void /*$ra*/ DisplayDebris(struct DEBRIS *debris /*$t2*/, char type /*$t3*/)
{ // line 1, offset 0x37b7c
  int pos; // $a1
  int z; // stack offset -8
  struct SVECTOR v[4]; // stack offset -56
  struct TRI_POINT *tv; // $t1
  struct VECTOR debrisvec; // stack offset -24
  struct POLY_FT3 *poly; // $t0
  struct POLY_GT4 *poly1; // $t0
  { // line 43, offset 0x37dfc
    unsigned long cbgr; // $v1
  } // line 54, offset 0x37e78
} // line 84, offset 0x38068
/*
 * Offset 0x38070
 * D:\driver2\game\C\DEBRIS.C (line 3659)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ HandleDebris()
{ // line 2, offset 0x38070
  int count; // $s0
  int i; // $s3
  struct DEBRIS *lpDebris; // $s1
  struct SMOKE *smokeptr; // $s0
  struct VECTOR dummy; // stack offset -80
  struct LEAF *lpLeaf; // $s1
  int Height; // $v0
  int SinX; // $s2
  int CosX; // $v1
  struct VECTOR Drift; // stack offset -64
  { // line 193, offset 0x38484
    int offshore; // $s1
    struct ROUTE_DATA routeData; // stack offset -48
  } // line 205, offset 0x3851c
  { // line 294, offset 0x38758
    static int weather_level; // offset 0x168
  } // line 307, offset 0x387b8
} // line 308, offset 0x387e4
/*
 * Offset 0x387E4
 * D:\driver2\game\C\DEBRIS.C (line 3983)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DisplaySmoke(struct SMOKE *smoke /*$s0*/)
{ // line 1, offset 0x387e4
  struct POLY_FT4 *poly; // $t0
  struct VECTOR v; // stack offset -80
  struct SVECTOR smokemesh[4]; // stack offset -64
  int x; // $s2
  int negx; // $s1
  int z; // stack offset -32
  int smoke_z_offset; // $s3
  int tmode; // $a3
  int size; // $v0
  int centrex; // $a1
  int centrey; // $v1
  { // line 58, offset 0x389d8
    char red; // $a0
    char green; // $a1
    char blue; // $v1
  } // line 63, offset 0x38a04
} // line 132, offset 0x38d00
/*
 * Offset 0x38D1C
 * D:\driver2\game\C\DEBRIS.C (line 4118)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ add_haze(int top_col /*$a0*/, int bot_col /*$a1*/, short ot_pos /*$a2*/)
{ // line 1, offset 0x38d1c
  struct TILE *polys; // $a1
} // line 23, offset 0x38e68
/*
 * Offset 0x38E70
 * D:\driver2\game\C\DEBRIS.C (line 4208)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawRainDrops()
{ // line 2, offset 0x38e70
  struct RAIN_TYPE *RainPtr; // $s0
  struct POLY_GT3 *poly; // $a3
  int Count; // $s2
  int z; // stack offset -48
  struct SVECTOR v[3]; // stack offset -88
  struct VECTOR drift; // stack offset -64
  int tpage; // $fp
  int clut; // $s7
  int col; // $s1
  { // line 51, offset 0x3900c
    int notfirst; // $a1
  } // line 88, offset 0x391c0
} // line 92, offset 0x39204
/*
 * Offset 0x39204
 * D:\driver2\game\C\DEBRIS.C (line 4413)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ AddRainDrops()
{ // line 2, offset 0x39204
  struct SVECTOR v; // stack offset -48
  struct RAIN_TYPE *RainPtr; // $a2
  int RainIndex; // $s0
  int RainNo; // $s1
  int first; // $s3
  static unsigned long rand; // offset 0x8
  { // line 40, offset 0x393f0
    int depth; // $v0
  } // line 43, offset 0x39418
  { // line 53, offset 0x3944c
    struct ROUTE_DATA routeData; // stack offset -40
  } // line 61, offset 0x3949c
} // line 64, offset 0x394ac
/*
 * Offset 0x394D0
 * D:\driver2\game\C\DEBRIS.C (line 4489)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DisplaySplashes()
{ // line 2, offset 0x394d0
  int SplashNo; // $s4
  int SplashFrac; // $v0
  struct VECTOR CamGnd; // stack offset -96
  struct VECTOR Gnd1; // stack offset -80
  struct VECTOR Gnd2; // stack offset -64
  struct VECTOR Position; // stack offset -48
  struct CVECTOR col; // stack offset -32
  static unsigned long rand; // offset 0x170
  int d1; // $a0
  int d2; // $a2
} // line 58, offset 0x39808
/*
 * Offset 0x39828
 * D:\driver2\game\C\DEBRIS.C (line 4550)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DisplayLightReflections(struct VECTOR *v1 /*$s1*/, struct CVECTOR *col /*$s3*/, short size /*$a2*/, struct TEXTURE_DETAILS *texture /*$s2*/)
{ // line 1, offset 0x39828
  struct SVECTOR vert[4]; // stack offset -80
  struct POLY_FT4 *poly; // $a1
  struct CVECTOR thiscol; // stack offset -48
  int z; // stack offset -40
  int tpage; // $s5
  int clut; // $s4
} // line 52, offset 0x39a98
/*
 * Offset 0x39ABC
 * D:\driver2\game\C\DEBRIS.C (line 1686)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ AllocateDebris()
{
}
/*
 * Offset 0x39AF8
 * D:\driver2\game\C\DEBRIS.C (line 1297)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ AllocateLeaf()
{
}
/*
 * Offset 0x39B34
 * D:\driver2\game\C\DEBRIS.C (line 1719)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ AllocateSmoke()
{
}
/*
 * Offset 0x39B70
 * D:\driver2\game\C\DEBRIS.C (line 2200)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ find_lamp_streak(int LampId /*$a0*/)
{ // line 1, offset 0x39b70
  int count; // $a1
} // line 17, offset 0x39be0
/*
 * Offset 0x39BE0
 * D:\driver2\game\C\DEBRIS.C (line 4607)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DoLightning()
{ // line 2, offset 0x39be0
} // line 24, offset 0x39cc0
/*
 * Offset 0x39CD0
 * D:\driver2\game\C\DEBRIS.C (line 2447)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ FindCarLightFade(struct MATRIX *carToCamera /*$a0*/)
{ // line 2, offset 0x39cd0
  int zz; // $v0
} // line 5, offset 0x39cf8
/*
 * Offset 0x39CF8
 * D:\driver2\game\C\DEBRIS.C (line 2428)
 * Stack frame base $sp, size 8
 */
void /*$ra*/ InitFXPos(struct VECTOR *vec /*$a0*/, struct SVECTOR *svec /*$a1*/, struct _CAR_DATA *cp /*$a2*/)
{ // line 1, offset 0x39cf8
  struct SVECTOR svectmp; // stack offset -8
} // line 9, offset 0x39dd0
/*
 * Offset 0x39DD0
 * D:\driver2\game\C\DEBRIS.C (line 1704)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ReleaseDebris(short num /*$a0*/)
{
}
/*
 * Offset 0x39DF4
 * D:\driver2\game\C\DEBRIS.C (line 1313)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ReleaseLeaf(short num /*$a0*/)
{
}
/*
 * Offset 0x39E18
 * D:\driver2\game\C\DEBRIS.C (line 4190)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ReleaseRainDrop(int RainIndex /*$a0*/)
{
}
/*
 * Offset 0x39E3C
 * D:\driver2\game\C\DEBRIS.C (line 1737)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ReleaseSmoke(short num /*$a0*/)
{
}
/*
 * Offset 0x39E60
 * D:\driver2\game\C\DEBRIS.C (line 4152)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupRain()
{ // line 2, offset 0x39e60
} // line 11, offset 0x39ebc
/*
 * Offset 0x39EBC
 * D:\driver2\game\C\DEBRIS.C (line 1437)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ SwirlLeaves(struct _CAR_DATA *cp /*$a0*/)
{ // line 1, offset 0x39ebc
  int count; // $s2
  struct LEAF *lpLeaf; // $s0
  int XDiff; // $v0
  int ZDiff; // $a1
  struct VECTOR *CarPos; // $s1
  int WheelSpeed; // $a1
  { // line 38, offset 0x39fc8
  } // line 40, offset 0x39fec
} // line 44, offset 0x39ff8
/*
 * Offset 0x3A010
 * D:\driver2\game\C\DEBRIS.C (line 4725)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetDebrisColour(struct _CAR_DATA *cp /*$a0*/)
{ // line 1, offset 0x3a010
  int car_model; // $v1
  int palette; // $a0
} // line 17, offset 0x3a068
/*
 * Offset 0x3A068
 * D:\driver2\game\C\DEBRIS.C (line 4651)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DoWeather(int weather /*$a0*/)
{
}
/*
 * Offset 0x3A124
 * D:\driver2\game\C\DEBRIS.C (line 4635)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitThunder()
{ // line 1, offset 0x3a124
} // line 1, offset 0x3a188
/*
 * Offset 0x3A188
 * D:\driver2\game\C\DEBRIS.C (line 4636)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ RequestThunder()
{
}
/*
 * Offset 0x3A1AC
 * D:\driver2\game\C\DEBRIS.C (line 4638)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DoThunder()
{ // line 2, offset 0x3a1ac
} // line 9, offset 0x3a28c
/*
 * Offset 0x3A29C
 * D:\driver2\game\C\DEBRIS.C (line 1886)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ MoveSmashable_object()
{ // line 2, offset 0x3a29c
  int count; // $a3
  struct DAMAGED_OBJECT *dam; // $a1
  { // line 10, offset 0x3a2c0
    int groundlevel; // $v0
  } // line 25, offset 0x3a328
} // line 28, offset 0x3a33c
/*
 * Offset 0x3A33C
 * D:\driver2\game\C\DEBRIS.C (line 4173)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ AllocateRainDrop()
{
}
/*
 * Offset 0x3A378
 * D:\driver2\game\C\DENTING.C (line 288)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: s0 s1 s2 s3 s4
 */
void /*$ra*/ DentCar(struct _CAR_DATA *cp /*$t7*/)
{ // line 1, offset 0x3a378
  struct SVECTOR *VertPtr; // $t0
  int MaxDamage; // $s0
  unsigned char VertIndex; // $v0
  unsigned char PolyIndex; // $v0
  struct DENTUVS *dentptr; // $t1
  unsigned char *DamPtr; // $a2
  int model; // $t5
  int Poly; // $a1
  int Damage; // $v1
  int Zone; // $a3
  int VertNo; // $a2
  short *tempDamage; // $t1
  struct SVECTOR *DamVertPtr; // $a3
  struct SVECTOR *CleanVertPtr; // $a1
  struct MODEL *pCleanModel; // $t3
  { // line 133, offset 0x3a6f8
  } // line 135, offset 0x3a6f8
} // line 140, offset 0x3a74c
/*
 * Offset 0x3A74C
 * D:\driver2\game\C\DENTING.C (line 458)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ CreateDentableCar(struct _CAR_DATA *cp /*$t2*/)
{ // line 1, offset 0x3a74c
  struct DENTUVS *dentptr; // $a3
  int Zone; // $v1
  int count; // $a2
  int model; // $t3
  { // line 20, offset 0x3a778
    struct SVECTOR *dst; // $a2
    struct SVECTOR *src; // $a3
    int count; // $t0
    { // line 26, offset 0x3a7b0
      int x; // $v0
      int y; // $v1
      int z; // $a0
    } // line 26, offset 0x3a7b0
  } // line 35, offset 0x3a7d8
} // line 76, offset 0x3a8dc
/*
 * Offset 0x3A8DC
 * D:\driver2\game\C\DENTING.C (line 549)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitHubcap()
{ // line 3, offset 0x3a8dc
} // line 24, offset 0x3a960
/*
 * Offset 0x3A960
 * D:\driver2\game\C\DENTING.C (line 600)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ LoseHubcap(int Hubcap /*$s3*/, int Velocity /*$a1*/)
{ // line 1, offset 0x3a960
  struct _CAR_DATA *car_data_pt; // $s1
  struct SVECTOR InitialLocalAngle; // stack offset -64
  { // line 71, offset 0x3aaec
    struct VECTOR R; // stack offset -56
    struct VECTOR VW; // stack offset -40
    long AY; // $t0
  } // line 81, offset 0x3ab48
} // line 94, offset 0x3ab94
/*
 * Offset 0x3ABB4
 * D:\driver2\game\C\DENTING.C (line 706)
 * Stack frame base $sp, size 104
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ MoveHubcap()
{ // line 2, offset 0x3abb4
  struct _CAR_DATA *car_data_pt; // $a1
  struct VECTOR Position; // stack offset -80
  struct MATRIX Orientation; // stack offset -64
  struct CVECTOR col; // stack offset -32
  int VelocityMagnitude; // $s0
  int CurrentMapHeight; // $a0
  int savecombo; // $s0
  { // line 25, offset 0x3ac60
  } // line 28, offset 0x3ac80
  { // line 32, offset 0x3ac90
  } // line 35, offset 0x3acc0
  { // line 56, offset 0x3ad0c
  } // line 74, offset 0x3ad8c
} // line 99, offset 0x3aeac
/*
 * Offset 0x3AEC8
 * D:\driver2\game\C\DENTING.C (line 838)
 * Stack frame base $sp, size 16
 * Saved registers at offset -4: s0 s1 s2 s3
 */
void /*$ra*/ ProcessDentLump(char *lump_ptr /*$t2*/, int lump_size /*$a1*/)
{ // line 1, offset 0x3aec8
  int i; // $a3
  int model; // $a0
  int offset; // $a0
} // line 30, offset 0x3b228
/*
 * Offset 0x3B228
 * D:\driver2\game\C\DENTING.C (line 267)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitialiseDenting()
{
}
/*
 * Offset 0x3B258
 * D:\driver2\game\C\DENTING.C (line 815)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ LoadDenting(int level /*$a0*/)
{ // line 2, offset 0x3b258
} // line 15, offset 0x3b2a8
/*
 * Offset 0x3B2A8
 * D:\driver2\game\C\DENTING.C (line 877)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupSpecDenting(char *loadbuffer /*$a0*/)
{ // line 1, offset 0x3b2a8
  char *from; // $a0
  char *to; // $v1
  char *limit; // $a1
} // line 34, offset 0x3b34c
/*
 * Offset 0x3B34C
 * D:\driver2\game\C\DIRECTOR.C (line 513)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ EditCamera(int CameraCnt /*$a0*/)
{ // line 2, offset 0x3b34c
  int count; // $t0
  { // line 30, offset 0x3b47c
    int prev; // $a2
    int next; // $v1
  } // line 57, offset 0x3b584
} // line 59, offset 0x3b5b0
/*
 * Offset 0x3B5B0
 * D:\driver2\game\C\DIRECTOR.C (line 574)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ RecordCamera(int CameraCnt /*$s0*/)
{ // line 1, offset 0x3b5b0
  struct PLAYBACKCAMERA *TempChange; // $a1
} // line 58, offset 0x3b7fc
/*
 * Offset 0x3B7FC
 * D:\driver2\game\C\DIRECTOR.C (line 658)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ CheckCameraChange(int CameraCnt /*$s0*/)
{
}
/*
 * Offset 0x3B930
 * D:\driver2\game\C\DIRECTOR.C (line 731)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ IsMovingCamera(struct PLAYBACKCAMERA *lastcam /*$t3*/, struct PLAYBACKCAMERA *nextcam /*$t0*/, int cameracnt /*$a2*/)
{ // line 1, offset 0x3b930
  struct PLAYBACKCAMERA cam; // stack offset -56
  long xdist; // $t5
  long ydist; // $t6
  long zdist; // $t4
  long xangle; // $a3
  long yangle; // $t1
  long zangle; // $t2
  int s; // $a0
  int e; // $v1
  int f; // $t8
  int t; // $a2
  int nextcview; // $a0
} // line 61, offset 0x3bc10
/*
 * Offset 0x3BC10
 * D:\driver2\game\C\DIRECTOR.C (line 794)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 fp
 */
void /*$ra*/ CameraBar(int CameraCnt /*stack 0*/)
{ // line 1, offset 0x3bc10
  struct POLY_G4 *camera; // $a2
  struct LINE_F2 *bar; // $t2
  int x; // $a2
  int min_x; // $t1
  int max_x; // $t0
  int min_y; // $s3
  char red; // $s0
  char green; // $s4
  char blue; // $fp
  int bar_x; // $s1
  int first; // stack offset -48
  int last; // $s7
  unsigned long idx; // $t9
} // line 133, offset 0x3c1ec
/*
 * Offset 0x3C218
 * D:\driver2\game\C\DIRECTOR.C (line 966)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ ShowIcons(char *menu /*$s3*/, int selected /*stack 4*/, int x_offset /*$s7*/)
{ // line 1, offset 0x3c218
  static int FlashCnt; // offset 0x0
  struct REPLAY_ICON *IconPtr; // $s0
  struct SPRT *icon; // $a2
  int count; // $s6
  { // line 61, offset 0x3c3a8
    struct TEXTURE_DETAILS *Icon_texture; // $s1
    int min_x; // $v1
    int min_y; // $a0
    { // line 69, offset 0x3c3cc
    } // line 71, offset 0x3c3ec
    { // line 82, offset 0x3c44c
      int ramp; // $a0
    } // line 93, offset 0x3c4b0
  } // line 100, offset 0x3c4d8
} // line 130, offset 0x3c624
/*
 * Offset 0x3C624
 * D:\driver2\game\C\DIRECTOR.C (line 1135)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ ShowReplayMenu()
{ // line 2, offset 0x3c624
  { // line 4, offset 0x3c64c
  } // line 8, offset 0x3c670
  { // line 12, offset 0x3c688
  } // line 16, offset 0x3c6a4
  { // line 43, offset 0x3c7b8
    int strobe; // $v0
  } // line 47, offset 0x3c800
} // line 49, offset 0x3c810
/*
 * Offset 0x3C810
 * D:\driver2\game\C\DIRECTOR.C (line 1186)
 * Stack frame base $sp, size 120
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ ControlReplay()
{ // line 2, offset 0x3c810
  static int debounce; // offset 0x60
  static int first_time; // offset 0x64
  int move; // $s0
  { // line 85, offset 0x3ca68
    int speed; // $s2
    { // line 95, offset 0x3cad0
    } // line 99, offset 0x3caf4
    { // line 102, offset 0x3cb0c
      int prev; // $v1
    } // line 105, offset 0x3cb44
    { // line 141, offset 0x3cc9c
      struct ROUTE_DATA routeData; // stack offset -96
      int road_height; // $s1
    } // line 152, offset 0x3cd18
    { // line 161, offset 0x3cd24
      struct VECTOR old_camera; // stack offset -88
      int x; // $s5
      int z; // $s4
      int d; // $s3
      int angle; // $s1
      char cameraCar; // $a0
      int dx; // $s1
      int dz; // $s0
      struct VECTOR basePos; // stack offset -72
      struct VECTOR tmpPos; // stack offset -56
      { // line 186, offset 0x3cda0
        struct _EVENT *event; // $a1
      } // line 190, offset 0x3cdd0
      { // line 224, offset 0x3cecc
        int temp; // $v0
      } // line 228, offset 0x3ced8
      { // line 245, offset 0x3cf90
      } // line 264, offset 0x3cfdc
      { // line 268, offset 0x3cfdc
        struct ROUTE_DATA routeData; // stack offset -40
        int road_height; // $s1
      } // line 289, offset 0x3d0cc
    } // line 291, offset 0x3d0f0
  } // line 320, offset 0x3d230
  { // line 374, offset 0x3d574
    { // line 496, offset 0x3d870
    } // line 496, offset 0x3d870
    { // line 605, offset 0x3dad4
      int prev1; // $a1
    } // line 615, offset 0x3db14
  } // line 789, offset 0x3de74
} // line 802, offset 0x3dea0
/*
 * Offset 0x3DEC8
 * D:\driver2\game\C\DIRECTOR.C (line 1990)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DoAutoDirect()
{ // line 2, offset 0x3dec8
  struct VECTOR pos; // stack offset -40
  { // line 8, offset 0x3df64
    int new_view; // $v1
    { // line 25, offset 0x3dffc
    } // line 35, offset 0x3e004
    { // line 58, offset 0x3e0c0
      int tmp; // $v0
    } // line 67, offset 0x3e138
    { // line 69, offset 0x3e138
      int tmp; // $v0
    } // line 75, offset 0x3e15c
  } // line 105, offset 0x3e32c
} // line 116, offset 0x3e390
/*
 * Offset 0x3E390
 * D:\driver2\game\C\DIRECTOR.C (line 2108)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ SelectCameraCar(int current /*$t1*/)
{ // line 1, offset 0x3e390
  int count; // $a2
  { // line 15, offset 0x3e408
    struct _EVENT *event; // $a0
    struct _CAR_DATA *car; // $a3
    struct XZPAIR pos; // stack offset -16
    { // line 60, offset 0x3e4ec
      int dist; // $v0
      int dx; // $a1
      int dz; // $a0
    } // line 72, offset 0x3e574
  } // line 73, offset 0x3e574
} // line 76, offset 0x3e5a4
/*
 * Offset 0x3E5A4
 * D:\driver2\game\C\DIRECTOR.C (line 2186)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ InvalidCamera(int car_num /*$a2*/)
{ // line 1, offset 0x3e5a4
  { // line 7, offset 0x3e5d0
    char invalidCamera; // $a3
    { // line 14, offset 0x3e638
      char numEventModels; // $a0
      struct _EVENT *event; // $v1
      struct XZPAIR pos; // stack offset -24
      { // line 22, offset 0x3e690
        int dist; // $v0
        int dx; // $v1
        int dz; // $a0
      } // line 38, offset 0x3e728
    } // line 39, offset 0x3e728
  } // line 50, offset 0x3e760
} // line 74, offset 0x3e804
/*
 * Offset 0x3E804
 * D:\driver2\game\C\DIRECTOR.C (line 445)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitDirectorVariables()
{ // line 2, offset 0x3e804
  int count; // $a0
} // line 22, offset 0x3e870
/*
 * Offset 0x3E870
 * D:\driver2\game\C\DIRECTOR.C (line 476)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DeleteCurrentCamera(int CameraCnt /*$a0*/)
{ // line 2, offset 0x3e870
  int prev; // $a1
  int next; // $a0
} // line 15, offset 0x3e8f4
/*
 * Offset 0x3E904
 * D:\driver2\game\C\DIRECTOR.C (line 493)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ setCamera(struct PLAYBACKCAMERA *Change /*$a0*/)
{
}
/*
 * Offset 0x3E9B4
 * D:\driver2\game\C\DIRECTOR.C (line 634)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ FindNextChange(int CameraCnt /*$a0*/)
{ // line 1, offset 0x3e9b4
  int count; // $a3
  int nextframe; // $a2
  int found; // $t0
  struct PLAYBACKCAMERA *RestoreChange; // $t1
} // line 21, offset 0x3ea20
/*
 * Offset 0x3EA20
 * D:\driver2\game\C\DIRECTOR.C (line 929)
 * Stack frame base $sp, size 0
 */
struct PLAYBACKCAMERA * /*$ra*/ FindFreeCamera()
{ // line 2, offset 0x3ea20
  int count; // $a1
} // line 12, offset 0x3ea60
/*
 * Offset 0x3EA60
 * D:\driver2\game\C\DIRECTOR.C (line 943)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ deleteCamera(int count /*$a0*/)
{
}
/*
 * Offset 0x3EAA8
 * D:\driver2\game\C\DIRECTOR.C (line 951)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DeleteAllCameras()
{ // line 2, offset 0x3eaa8
  struct PLAYBACKCAMERA nextcamera; // stack offset -48
  int count; // $s0
} // line 13, offset 0x3eb0c
/*
 * Offset 0x3EB0C
 * D:\driver2\game\C\DIRECTOR.C (line 1098)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ ShowReplayOptions()
{ // line 2, offset 0x3eb0c
  static int toggle_icons; // offset 0x5c
} // line 35, offset 0x3eb48
/*
 * Offset 0x3EB58
 * D:\driver2\game\C\DIRECTOR.C (line 2263)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ NoMoreCamerasErrorMessage()
{ // line 2, offset 0x3eb58
  { // line 4, offset 0x3eb70
    int strobe; // $v0
  } // line 9, offset 0x3ebc4
} // line 12, offset 0x3ebd4
/*
 * Offset 0x3EBD4
 * D:\driver2\game\C\DIRECTOR.C (line 2279)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ FirstCamera()
{ // line 2, offset 0x3ebd4
} // line 8, offset 0x3ec04
/*
 * Offset 0x3EC04
 * D:\driver2\game\C\DIRECTOR.C (line 2289)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ dist(struct VECTOR *pos1 /*$a0*/, struct VECTOR *pos2 /*$a1*/)
{ // line 1, offset 0x3ec04
  int dx; // $v0
  int dz; // $a0
} // line 7, offset 0x3ec74
/*
 * Offset 0x3EC74
 * D:\driver2\game\C\DIRECTOR.C (line 710)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetPlaybackCamera(struct PLAYBACKCAMERA *camera /*$a0*/)
{
}
/*
 * Offset 0x3ED2C
 * D:\driver2\game\C\DIRECTOR.C (line 2303)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetCameraReturnedFromCutscene(int CameraCnt /*$s0*/)
{ // line 1, offset 0x3ed2c
  struct PLAYBACKCAMERA *next; // $a1
  int count; // $a2
} // line 28, offset 0x3ede4
/*
 * Offset 0x3EDE4
 * D:\driver2\game\C\DRAW.C (line 651)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ addSubdivSpriteShadow(struct POLYFT4LIT *src /*$t3*/, struct SVECTOR *verts /*$t2*/, int z /*$a2*/)
{ // line 1, offset 0x3ede4
  unsigned long word0; // $a0
  unsigned long vidx; // $t1
  struct _pct *pc; // $t0
  int w; // $s0
} // line 19, offset 0x3efcc
/*
 * Offset 0x3EFCC
 * D:\driver2\game\C\DRAW.C (line 675)
 * Stack frame base $sp, size 96
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawSprites(int numFound /*$a2*/)
{ // line 1, offset 0x3efcc
  struct XZPAIR near; // stack offset -80
  struct PACKED_CELL_OBJECT **list; // stack offset -64
  unsigned long spriteColour; // stack offset -60
  int numShadows; // stack offset -56
  { // line 1, offset 0x3efcc
    struct SVECTOR result; // stack offset -72
    unsigned char lightLevel; // $a1
  } // line 41, offset 0x3f164
  { // line 41, offset 0x3f164
    int i; // $t0
  } // line 54, offset 0x3f1dc
  { // line 68, offset 0x3f258
    struct PACKED_CELL_OBJECT *ppco; // $fp
    struct MODEL *model; // $s4
    int z; // stack offset -52
    int yang; // $a0
    { // line 95, offset 0x3f310
    } // line 95, offset 0x3f310
    { // line 101, offset 0x3f358
      struct POLYFT4LIT *src; // $s0
      struct SVECTOR *verts; // $s3
      int i; // $s1
      { // line 106, offset 0x3f3a0
        unsigned long vidx; // $a3
      } // line 107, offset 0x3f3a0
    } // line 119, offset 0x3f504
  } // line 132, offset 0x3f604
} // line 134, offset 0x3f658
/*
 * Offset 0x3F658
 * D:\driver2\game\C\DRAW.C (line 813)
 * Stack frame base $sp, size 0
 */
struct PACKED_CELL_OBJECT * /*$ra*/ GetNextPackedCop(struct CELL_ITERATOR *pci /*$a0*/)
{ // line 1, offset 0x3f658
  struct PACKED_CELL_OBJECT *ppco; // $a3
  unsigned short num; // $a1
} // line 40, offset 0x3f718
/*
 * Offset 0x3F718
 * D:\driver2\game\C\DRAW.C (line 883)
 * Stack frame base $sp, size 200
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawMapPSX(int *comp_val /*$t1*/)
{ // line 1, offset 0x3f718
  struct CELL_ITERATOR ci; // stack offset -184
  struct PACKED_CELL_OBJECT *ppco; // $s0
  int i; // $s1
  int dir; // $s7
  int cellxpos; // $a0
  int cellzpos; // $a1
  int hloop; // $s4
  int vloop; // $s5
  int camx; // stack offset -112
  int camz; // stack offset -108
  char *PVS_ptr; // stack offset -104
  int tiles_found; // stack offset -100
  int other_models_found; // stack offset -96
  int anim_objs; // $s6
  struct MATRIX mRotStore; // stack offset -160
  int rightcos; // stack offset -92
  int rightsin; // stack offset -88
  int leftcos; // stack offset -84
  int leftsin; // stack offset -80
  int backcos; // stack offset -76
  int backsin; // stack offset -72
  int rightPlane; // stack offset -68
  int leftPlane; // stack offset -64
  int backPlane; // $fp
  unsigned int farClipLimit; // stack offset -60
  { // line 84, offset 0x3f9cc
    struct MODEL *model; // $s2
    { // line 92, offset 0x3fa1c
      int model_shape_flags; // $s1
      { // line 103, offset 0x3fa78
        struct CELL_OBJECT *cop; // $a2
        { // line 1, offset 0x3fa78
          struct PACKED_CELL_OBJECT *ppco; // $s0
          { // line 1, offset 0x3fa78
            struct CELL_OBJECT *pco; // $a1
          } // line 1, offset 0x3fb20
        } // line 1, offset 0x3fb20
      } // line 105, offset 0x3fb2c
      { // line 110, offset 0x3fb5c
        struct CELL_OBJECT *cop; // $a2
        { // line 1, offset 0x3fb5c
          struct PACKED_CELL_OBJECT *ppco; // $s0
          { // line 1, offset 0x3fb5c
            struct CELL_OBJECT *pco; // $a1
          } // line 1, offset 0x3fc04
        } // line 1, offset 0x3fc04
      } // line 111, offset 0x3fc04
      { // line 119, offset 0x3fc50
        int yang; // $a1
      } // line 127, offset 0x3fd38
      { // line 135, offset 0x3fd74
        struct CELL_OBJECT *cop; // $a2
        { // line 1, offset 0x3fd74
          struct PACKED_CELL_OBJECT *ppco; // $s0
          { // line 1, offset 0x3fd74
            struct CELL_OBJECT *pco; // $a1
          } // line 1, offset 0x3fe1c
        } // line 1, offset 0x3fe1c
      } // line 138, offset 0x3fe68
      { // line 149, offset 0x3fe9c
        struct CELL_OBJECT *cop; // $a2
        { // line 1, offset 0x3fe9c
          struct PACKED_CELL_OBJECT *ppco; // $s0
          { // line 1, offset 0x3fe9c
            struct CELL_OBJECT *pco; // $a1
          } // line 1, offset 0x3ff44
        } // line 1, offset 0x3ff44
      } // line 159, offset 0x3ff9c
    } // line 162, offset 0x3ff9c
  } // line 163, offset 0x3ff9c
  { // line 188, offset 0x40134
  } // line 189, offset 0x4013c
  { // line 198, offset 0x4014c
  } // line 200, offset 0x40174
  { // line 206, offset 0x401a0
    struct VECTOR newpos; // stack offset -128
    struct CELL_OBJECT *cop; // $s0
  } // line 207, offset 0x401a0
} // line 240, offset 0x40280
/*
 * Offset 0x40280
 * D:\driver2\game\C\DRAW.C (line 1125)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupPlaneColours(unsigned long ambient /*$a3*/)
{ // line 1, offset 0x40280
  { // line 15, offset 0x4031c
    unsigned long r; // $t4
    unsigned long g; // $t2
    unsigned long b; // $a0
  } // line 15, offset 0x4031c
} // line 34, offset 0x40470
/*
 * Offset 0x40470
 * D:\driver2\game\C\DRAW.C (line 1162)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SetupDrawMapPSX()
{ // line 3, offset 0x40470
  { // line 4, offset 0x404d0
    int region_x1; // $t0
    int region_z1; // $a0
    int current_barrel_region_x1; // $v0
    int current_barrel_region_z1; // $a0
  } // line 16, offset 0x404f4
  { // line 16, offset 0x404f4
    int theta; // $s2
  } // line 34, offset 0x40568
} // line 38, offset 0x4059c
/*
 * Offset 0x4059C
 * D:\driver2\game\C\DRAW.C (line 1209)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ InitFrustrumMatrix()
{
}
/*
 * Offset 0x40670
 * D:\driver2\game\C\DRAW.C (line 1425)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ProcessMapLump(char *lump_ptr /*$v0*/, int lump_size /*$a1*/)
{ // line 1, offset 0x40670
  char *cellptr; // $s0
  int cell_size; // $a3
  int region_size; // $t0
} // line 53, offset 0x40840
/*
 * Offset 0x40840
 * D:\driver2\game\C\DRAW.C (line 1711)
 * Stack frame base $sp, size 128
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ DrawAllTheCars(int view /*$s6*/)
{ // line 1, offset 0x40840
  int loop; // $s0
  int x; // $s2
  int z; // $s1
  int xd; // $a0
  int zd; // $v1
  struct _CAR_DATA *cars_to_draw[20]; // stack offset -112
  int num_cars_to_draw; // $s4
  static int car_distance[20]; // offset 0x0
  static int temp; // offset 0x0
  { // line 1, offset 0x40840
    struct _CAR_DATA *lcp; // $s0
    { // line 27, offset 0x408c8
      int dist; // $v0
    } // line 37, offset 0x40948
  } // line 40, offset 0x40958
  { // line 46, offset 0x40960
    int i; // $a0
    { // line 51, offset 0x40988
      struct _CAR_DATA *car; // $t4
      int dist; // $t0
      int j; // $a3
    } // line 60, offset 0x40a08
  } // line 63, offset 0x40a28
  { // line 79, offset 0x40a4c
    int spacefree; // $a1
  } // line 87, offset 0x40a94
} // line 113, offset 0x40ad0
/*
 * Offset 0x40AF8
 * D:\driver2\game\C\DRAW.C (line 1857)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ PlotBuildingModelSubdivNxN(struct MODEL *model /*$t0*/, int rot /*stack 4*/, struct _pct *pc /*$s2*/, int n /*stack 12*/)
{ // line 1, offset 0x40af8
  struct SVECTOR *verts; // $s4
  struct PL_POLYFT4 *polys; // $s1
  int i; // $s7
  int asdf; // $fp
  { // line 19, offset 0x40ba8
    unsigned long word0; // $s0
    { // line 29, offset 0x40c04
      int Z; // stack offset -48
      unsigned int vidx; // $s3
      { // line 39, offset 0x40c38
        unsigned long th; // $v1
      } // line 45, offset 0x40c78
      { // line 83, offset 0x40e98
        int diff; // $a1
        int min; // $a2
        { // line 88, offset 0x40e98
          int max; // $v1
        } // line 92, offset 0x40f0c
        { // line 113, offset 0x40f78
          int w; // $s0
        } // line 116, offset 0x40fa4
        { // line 126, offset 0x410c8
          struct POLY_FT4 *prims; // $t2
          int uv0; // $v1
          int uv1; // $a2
          int uv2; // $t3
          int uv3; // $t1
          { // line 137, offset 0x41110
            unsigned int r; // $a2
          } // line 137, offset 0x41110
          { // line 137, offset 0x41110
            int r2; // $v1
          } // line 137, offset 0x41110
        } // line 162, offset 0x411a8
      } // line 164, offset 0x411a8
    } // line 169, offset 0x411c0
  } // line 176, offset 0x411e0
} // line 183, offset 0x4125c
/*
 * Offset 0x4125C
 * D:\driver2\game\C\DRAW.C (line 2053)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ DrawAllBuildings(unsigned long *objects /*$t3*/, int num_buildings /*$s5*/, struct DB *disp /*$a2*/)
{ // line 1, offset 0x4125c
  int i; // $s3
  int model_number; // $v0
  int prev_mat; // $s4
  struct MODEL *model; // $a0
  struct CELL_OBJECT *building; // $s0
  { // line 38, offset 0x41394
    int spacefree; // $a0
    { // line 81, offset 0x413c4
    } // line 82, offset 0x413cc
    { // line 85, offset 0x413cc
      int zBias; // $v0
      unsigned long *savedOT; // $s1
    } // line 97, offset 0x41400
  } // line 97, offset 0x41400
} // line 126, offset 0x414a4
/*
 * Offset 0x414A4
 * D:\driver2\game\C\DRAW.C (line 2181)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ RenderModel(struct MODEL *model /*$s2*/, struct MATRIX *matrix /*$a1*/, struct VECTOR *pos /*$a2*/, int zBias /*$s0*/, int flags /*stack 16*/)
{ // line 1, offset 0x414a4
  int i; // $t0
  unsigned long *savedOT; // $s1
  { // line 10, offset 0x414d0
    struct MATRIX comb; // stack offset -48
  } // line 15, offset 0x41500
  { // line 29, offset 0x415a0
    int spacefree; // $a0
  } // line 41, offset 0x41628
} // line 43, offset 0x4164c
/*
 * Offset 0x4164C
 * D:\driver2\game\C\DRAW.C (line 2267)
 * Stack frame base $sp, size 16
 */
unsigned long /*$ra*/ normalIndex(struct SVECTOR *verts /*$a0*/, unsigned int vidx /*$a1*/)
{ // line 1, offset 0x4164c
  int th23; // $a0
  int nx; // $t4
  int ny; // $v1
  int nz; // $a2
  struct SVECTOR p; // stack offset -16
  struct SVECTOR q; // stack offset -8
  { // line 1, offset 0x4164c
    int x; // $a1
    int y; // $a0
  } // line 8, offset 0x4178c
} // line 19, offset 0x4180c
/*
 * Offset 0x4180C
 * D:\driver2\game\C\DRAW.C (line 1219)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetFrustrumMatrix()
{
}
/*
 * Offset 0x41844
 * D:\driver2\game\C\DRAW.C (line 1224)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ Set_Inv_CameraMatrix()
{
}
/*
 * Offset 0x4187C
 * D:\driver2\game\C\DRAW.C (line 1324)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ CalcObjectRotationMatrices()
{ // line 2, offset 0x4187c
  int i; // $s1
  int j; // $a0
  struct SVECTOR ang; // stack offset -56
  struct MATRIX mat; // stack offset -48
} // line 17, offset 0x41924
/*
 * Offset 0x41924
 * D:\driver2\game\C\DRAW.C (line 1344)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ PlotMDL_less_than_128(struct MODEL *model /*$a0*/)
{
}
/*
 * Offset 0x41950
 * D:\driver2\game\C\DRAW.C (line 854)
 * Stack frame base $sp, size 0
 */
struct CELL_OBJECT * /*$ra*/ UnpackCellObject(struct PACKED_CELL_OBJECT *ppco /*$a3*/, struct XZPAIR *near /*$t0*/)
{ // line 1, offset 0x41950
  struct CELL_OBJECT *pco; // $a2
} // line 16, offset 0x41a10
/*
 * Offset 0x41B78
 * D:\driver2\game\C\TILE.C (line 79)
 * Stack frame base $sp, size 16
 * Saved registers at offset -8: s0
 */
void /*$ra*/ Tile1x1(struct MODEL *model /*$a0*/)
{ // line 1, offset 0x41b78
  int i; // $t3
  unsigned char *polys; // $t0
  struct SVECTOR *verts; // $t1
  struct POLY_FT4 *prims; // $a2
  unsigned long clut; // $t6
  unsigned long tpage; // $a1
  { // line 14, offset 0x41bb4
    unsigned long indices; // $a3
    unsigned long texInfo; // $t2
    { // line 14, offset 0x41bb4
      long *ot; // $t8
      { // line 14, offset 0x41bb4
        int Z; // stack offset -16
        unsigned long uv_01; // $t4
        unsigned long uv_23; // $t5
        0x1B4 otherhalf
        { // line 65, offset 0x41d2c
          int r2; // $a0
        } // line 65, offset 0x41d2c
      } // line 82, offset 0x41db0
    } // line 83, offset 0x41db0
  } // line 84, offset 0x41db0
} // line 87, offset 0x41de4
/*
 * Offset 0x41DE4
 * D:\driver2\game\C\TILE.C (line 180)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ DrawTILES(int tile_amount /*$s2*/)
{ // line 1, offset 0x41de4
  { // line 21, offset 0x41eec
  } // line 24, offset 0x41f24
  { // line 28, offset 0x41f24
    struct PACKED_CELL_OBJECT **tilePointers; // $s3
    int previous_matrix; // $s4
    { // line 40, offset 0x41f9c
      int model_number; // $s0
      int z; // $a1
      { // line 43, offset 0x41f9c
        int yang; // $a1
        struct PACKED_CELL_OBJECT *ppco; // $a0
      } // line 61, offset 0x42020
      { // line 90, offset 0x42094
        struct MODEL *model; // $a0
      } // line 99, offset 0x420c8
    } // line 102, offset 0x420c8
  } // line 105, offset 0x42118
} // line 107, offset 0x42118
/*
 * Offset 0x42118
 * D:\driver2\game\C\TILE.C (line 292)
 * Stack frame base $sp, size 8
 * Saved registers at offset -8: s0
 */
void /*$ra*/ makeMesh(struct MVERTEX *VSP[5][5] /*$t4*/, int m /*$t2*/, int n /*$a2*/)
{ // line 1, offset 0x42118
  { // line 21, offset 0x42130
    int a; // $t0
    int b; // $t1
  } // line 21, offset 0x42130
  { // line 21, offset 0x42130
    int a; // $a3
  } // line 21, offset 0x42130
  { // line 21, offset 0x42130
    int a; // $a0
    int b; // $a1
  } // line 21, offset 0x42130
  { // line 28, offset 0x4221c
    int a; // $t0
    int b; // $t1
  } // line 28, offset 0x4221c
  { // line 28, offset 0x4221c
    int a; // $a3
  } // line 28, offset 0x4221c
  { // line 28, offset 0x4221c
    int a; // $a0
    int b; // $a1
  } // line 28, offset 0x4221c
  { // line 34, offset 0x422f4
    int k; // $s0
    { // line 35, offset 0x422f4
      int a; // $t0
      int b; // $t1
    } // line 35, offset 0x422f4
    { // line 35, offset 0x422f4
      int a; // $a3
    } // line 35, offset 0x422f4
    { // line 35, offset 0x422f4
      int a; // $a0
      int b; // $a1
    } // line 35, offset 0x422f4
    { // line 40, offset 0x423e0
      int a; // $t0
      int b; // $t1
    } // line 40, offset 0x423e0
    { // line 40, offset 0x423e0
      int a; // $a3
    } // line 40, offset 0x423e0
    { // line 40, offset 0x423e0
      int a; // $a0
      int b; // $a1
    } // line 40, offset 0x423e0
  } // line 44, offset 0x424c0
  { // line 48, offset 0x424c8
    int a; // $t1
    int b; // $t5
  } // line 48, offset 0x424c8
  { // line 51, offset 0x42538
    int a; // $v0
    int b; // $a1
  } // line 51, offset 0x42538
  { // line 55, offset 0x42594
    int a; // $t0
    int b; // $t2
  } // line 55, offset 0x42594
  { // line 55, offset 0x42594
    int a; // $t3
    int b; // $v0
  } // line 55, offset 0x42594
  { // line 55, offset 0x42594
    int a; // $a2
  } // line 55, offset 0x42594
  { // line 55, offset 0x42594
    int a; // $t8
    int b; // $a1
  } // line 58, offset 0x426ac
} // line 61, offset 0x426b8
/*
 * Offset 0x426B8
 * D:\driver2\game\C\TILE.C (line 359)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 s1 s2 s3
 */
void /*$ra*/ drawMesh(struct MVERTEX *VSP[5][5] /*$s2*/, int m /*$s3*/, int n /*$s1*/, struct _pct *pc /*$a3*/)
{ // line 1, offset 0x426b8
  int j; // $t6
  int k; // $t9
  struct POLY_FT4 *prims; // $t1
  { // line 11, offset 0x42720
    int Z1; // stack offset -24
    int Z2; // stack offset -20
    struct MVERTEX *VST[5][5]; // $t2
    long *ot; // $t7
    { // line 23, offset 0x4277c
      int r2; // $v0
    } // line 23, offset 0x4277c
    { // line 103, offset 0x42a98
      int r2; // $v0
    } // line 121, offset 0x42b1c
  } // line 124, offset 0x42b1c
} // line 127, offset 0x42b54
/*
 * Offset 0x42B54
 * D:\driver2\game\C\TILE.C (line 489)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ SubdivNxM(char *polys /*$t4*/, unsigned long n /*$s1*/, unsigned long m /*$s0*/, int ofse /*$s2*/)
{ // line 1, offset 0x42b54
  struct MVERTEX *VSP[5][5]; // $t3
  struct _pct *pc; // $t2
  { // line 1, offset 0x42b54
    unsigned long indices; // $a0
    struct SVECTOR *v0; // $t1
    struct SVECTOR *v1; // $a1
    struct SVECTOR *v2; // $t0
  } // line 1, offset 0x42b54
  { // line 1, offset 0x42b54
    unsigned long uv_01; // $v1
    unsigned long uv_23; // $a2
  } // line 1, offset 0x42b54
  { // line 58, offset 0x42e54
    int Z; // stack offset -24
    { // line 73, offset 0x42ec8
      unsigned long texInfo; // $a0
    } // line 80, offset 0x42f3c
  } // line 86, offset 0x42f6c
} // line 88, offset 0x42f9c
/*
 * Offset 0x42F9C
 * D:\driver2\game\C\TILE.C (line 641)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessSubDivisionLump(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x42FA8
 * D:\driver2\game\C\TILE.C (line 581)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ TileNxN(struct MODEL *model /*$s4*/, int levels /*$s2*/, int Dofse /*$s6*/)
{ // line 1, offset 0x42fa8
  int i; // $s3
  char *polys; // $s0
  char ttype; // $a3
  unsigned long tiletypes; // $s1
  int baseOffset; // $s5
} // line 50, offset 0x430f8
/*
 * Offset 0x430F8
 * D:\driver2\game\C\TILE.C (line 651)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessLowDetailTable(char *lump_ptr /*$a0*/, int lump_size /*$a1*/)
{ // line 1, offset 0x430f8
  int i; // $a1
} // line 23, offset 0x43174
/*
 * Offset 0x43174
 * D:\driver2\game\C\DRIVINGGAMES.C (line 231)
 * Stack frame base $sp, size 88
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitDrivingGames()
{ // line 2, offset 0x43174
  char filename[64]; // stack offset -72
  int i; // $a0
  int j; // $v1
} // line 57, offset 0x432d4
/*
 * Offset 0x432D4
 * D:\driver2\game\C\DRIVINGGAMES.C (line 290)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ HandleDrivingGames()
{ // line 2, offset 0x432d4
  struct _CAR_DATA *cp; // $a2
  struct VECTOR vel; // stack offset -96
  int i; // $s3
  int j; // $v1
  int k; // $a0
  int id; // $s2
  int dist; // $a1
  { // line 61, offset 0x433bc
    struct VECTOR pos1; // stack offset -80
    struct VECTOR pos2; // stack offset -64
    int x; // $t0
    int z; // $a1
    int r; // $v0
    int side; // $s1
    int radius; // $a0
  } // line 123, offset 0x436c0
  { // line 145, offset 0x43768
    struct VECTOR pos; // stack offset -80
  } // line 166, offset 0x43868
} // line 185, offset 0x43944
/*
 * Offset 0x43944
 * D:\driver2\game\C\DRIVINGGAMES.C (line 477)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawDrivingGames()
{ // line 2, offset 0x43944
  struct VECTOR wpos; // stack offset -24
  int i; // $s0
} // line 49, offset 0x43a64
/*
 * Offset 0x43A64
 * D:\driver2\game\C\DRIVINGGAMES.C (line 545)
 * Stack frame base $sp, size 232
 * Saved registers at offset -8: ra
 */
int /*$ra*/ CarConeCollision(struct VECTOR *pPos /*$a0*/, int car /*$a1*/)
{ // line 1, offset 0x43a64
  struct CDATA2D cd[2]; // stack offset -216
  struct _CAR_DATA *cp1; // $t0
  int carLength[2]; // stack offset -16
  { // line 20, offset 0x43b3c
  } // line 20, offset 0x43b3c
} // line 21, offset 0x43b50
/*
 * Offset 0x43B50
 * D:\driver2\game\C\DRIVINGGAMES.C (line 578)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ SetSmashedCone(int cone /*$s1*/, struct VECTOR *velocity /*$a1*/, int player /*$s2*/, int side /*$a3*/)
{ // line 1, offset 0x43b50
  struct SMASHED_CONE *sc; // $s0
  int chan; // $s0
} // line 43, offset 0x43d48
/*
 * Offset 0x43D48
 * D:\driver2\game\C\DRIVINGGAMES.C (line 628)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MoveSmashedCones()
{ // line 2, offset 0x43d48
  int i; // $t0
} // line 27, offset 0x43e4c
/*
 * Offset 0x43E54
 * D:\driver2\game\C\DRIVINGGAMES.C (line 730)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ DrawSmashedCone(struct SMASHED_CONE *sc /*$s0*/, struct VECTOR *wpos /*$s1*/)
{ // line 1, offset 0x43e54
  struct MATRIX object_matrix; // stack offset -64
  struct MATRIX *finalmatrix; // $s2
  struct VECTOR pos; // stack offset -32
} // line 20, offset 0x43f9c
/*
 * Offset 0x43F9C
 * D:\driver2\game\C\DRIVINGGAMES.C (line 757)
 * Stack frame base $sp, size 16
 */
void /*$ra*/ GetConePos(int cone /*$a0*/, struct VECTOR *pos /*$t2*/, int side /*$a2*/)
{ // line 1, offset 0x43f9c
  struct VECTOR offset; // stack offset -16
  int x; // $t3
  int z; // $t4
  int r; // $v1
  int radius; // $a1
} // line 35, offset 0x4409c
/*
 * Offset 0x4409C
 * D:\driver2\game\C\DRIVINGGAMES.C (line 703)
 * Stack frame base $sp, size 88
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ DrawCone(struct VECTOR *position /*$s0*/, int cone /*$s1*/)
{ // line 1, offset 0x4409c
  struct MATRIX matrix; // stack offset -64
  struct VECTOR pos; // stack offset -32
  { // line 10, offset 0x440cc
    { // line 12, offset 0x440ec
    } // line 18, offset 0x441bc
  } // line 19, offset 0x441bc
} // line 20, offset 0x441bc
/*
 * Offset 0x441D0
 * D:\driver2\game\C\DRIVINGGAMES.C (line 662)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawSmashedCones()
{ // line 2, offset 0x441d0
  struct SMASHED_CONE *sc; // $s0
  struct VECTOR wpos; // stack offset -40
  int i; // $s1
} // line 34, offset 0x44290
/*
 * Offset 0x442AC
 * D:\driver2\game\C\E3STUFF.C (line 171)
 * Stack frame base $sp, size 512
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ FadeInHiresScreen(char *filename /*stack 0*/)
{ // line 1, offset 0x442ac
  struct DISPENV disp; // stack offset -488
  struct DRAWENV draw; // stack offset -464
  struct SPRT prims[6]; // stack offset -368
  struct POLY_FT3 nulls[6]; // stack offset -248
  struct RECT rect; // stack offset -56
  unsigned long ot; // stack offset -48
  int i; // $t5
  int col; // $s1
} // line 80, offset 0x4465c
/*
 * Offset 0x4465C
 * D:\driver2\game\C\E3STUFF.C (line 258)
 * Stack frame base $sp, size 520
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ FadeOutHiresScreen()
{ // line 2, offset 0x4465c
  struct DISPENV disp; // stack offset -496
  struct DRAWENV draw; // stack offset -472
  struct SPRT prims[6]; // stack offset -376
  struct POLY_FT3 nulls[6]; // stack offset -256
  struct RECT rect; // stack offset -64
  unsigned long ot; // stack offset -56
  int i; // $t5
  int col; // $s1
} // line 60, offset 0x44934
/*
 * Offset 0x44934
 * D:\driver2\game\C\E3STUFF.C (line 391)
 * Stack frame base $sp, size 168
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ SetPleaseWait(char *buffer /*$s2*/)
{ // line 1, offset 0x44934
  struct DISPENV disp; // stack offset -144
  struct DRAWENV draw; // stack offset -120
  struct RECT rect; // stack offset -24
  char *exe; // $a0
} // line 44, offset 0x44aa8
/*
 * Offset 0x44AA8
 * D:\driver2\game\C\E3STUFF.C (line 443)
 * Stack frame base $sp, size 184
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ CheckForCorrectDisc(int disc /*$s0*/)
{ // line 1, offset 0x44aa8
  struct DISPENV disp; // stack offset -160
  struct DRAWENV draw; // stack offset -136
  struct RECT rect; // stack offset -40
  char *mess1; // $s6
  char *mess2; // $s3
  char *exe; // $s4
  int ret; // $s0
  int discerror; // $s5
  { // line 49, offset 0x44bd8
  } // line 79, offset 0x44c5c
} // line 95, offset 0x44d20
/*
 * Offset 0x44D48
 * D:\driver2\game\C\E3STUFF.C (line 139)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ ShowHiresScreens(char **names /*$s1*/, int delay /*$s4*/, int wait /*$s3*/)
{ // line 1, offset 0x44d48
  char *filename; // $a0
  int timedelay; // $s0
} // line 25, offset 0x44e08
/*
 * Offset 0x44E08
 * D:\driver2\game\C\E3STUFF.C (line 350)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupDefDispEnv(struct DISPENV *env /*$s0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/)
{
}
/*
 * Offset 0x44EA8
 * D:\driver2\game\C\E3STUFF.C (line 325)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetupDefDrawEnv(struct DRAWENV *env /*$a0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/)
{
}
/*
 * Offset 0x44EF0
 * D:\driver2\game\C\ENVIRO.C (line 46)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ Env_MakeColourAddTable(short *shinysrc /*$s0*/, char *polytable /*$s1*/, int length /*$a2*/)
{ // line 1, offset 0x44ef0
  short addval; // $a0
  short polynum; // $v1
} // line 21, offset 0x44f70
/*
 * Offset 0x44F70
 * D:\driver2\game\C\ENVIRO.C (line 72)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ Init_Reflection_Mapping()
{ // line 2, offset 0x44f70
  struct TPAN pos; // stack offset -16
  int count; // $v1
} // line 17, offset 0x44fc8
/*
 * Offset 0x44FC8
 * D:\driver2\game\C\ENVSOUND.C (line 41)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ AddEnvSounds(int level /*$a0*/, int time /*$a1*/)
{
}
/*
 * Offset 0x45B20
 * D:\driver2\game\C\EVENT.C (line 249)
 * Stack frame base $sp, size 16
 */
int /*$ra*/ GetVisValue(int index /*$t1*/, int zDir /*$a1*/)
{ // line 1, offset 0x45b20
  int value; // $v1
  int radius; // $a0
  { // line 7, offset 0x45b30
    int camera; // $a0
  } // line 10, offset 0x45b90
  { // line 14, offset 0x45b98
    struct _EVENT *ev; // $a0
    int multiple; // $a2
    { // line 25, offset 0x45c24
      struct VECTOR pos; // stack offset -16
    } // line 32, offset 0x45ca4
  } // line 34, offset 0x45ca8
} // line 45, offset 0x45cd0
/*
 * Offset 0x45CD0
 * D:\driver2\game\C\EVENT.C (line 297)
 * Stack frame base $sp, size 568
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ VisibilityLists(enum VisType type /*$a0*/, int i /*$s2*/)
{ // line 1, offset 0x45cd0
  static unsigned short xList[128]; // offset 0x0
  static unsigned short zList[128]; // offset 0x100
  static unsigned short *firstX[2]; // offset 0x0
  static unsigned short *firstZ[2]; // offset 0x8
  static int count; // offset 0x10
  { // line 34, offset 0x45e00
    static unsigned short *list[2]; // offset 0x50
    int table[128]; // stack offset -552
    int j; // $s0
    { // line 42, offset 0x45e78
      int tempList; // $t7
      int k; // $t0
    } // line 53, offset 0x45f20
  } // line 55, offset 0x45f34
  { // line 58, offset 0x45f7c
    int camera; // $a1
  } // line 64, offset 0x45fe0
  { // line 68, offset 0x45ff8
    struct _EVENT *ev; // $a0
  } // line 87, offset 0x460d0
  { // line 90, offset 0x460d0
    struct _EVENT *ev; // $v1
  } // line 101, offset 0x46124
} // line 103, offset 0x46154
/*
 * Offset 0x46154
 * D:\driver2\game\C\EVENT.C (line 422)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ InitTrain(struct _EVENT *ev /*$s0*/, int count /*$s3*/, int type /*$a2*/)
{ // line 1, offset 0x46154
  int height; // $s2
  int length; // $s1
  int *to; // $a0
} // line 47, offset 0x462c0
/*
 * Offset 0x462C0
 * D:\driver2\game\C\EVENT.C (line 515)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SetUpEvents(int full /*stack 0*/)
{ // line 1, offset 0x462c0
  int count; // $s5
  int *p; // $s2
  int cEvents; // stack offset -52
  struct _EVENT **e; // stack offset -56
  { // line 25, offset 0x46378
    int ElTrackModel; // stack offset -48
    int carModel; // stack offset -44
    int direction; // $fp
    int i; // $s3
    { // line 36, offset 0x4639c
      int cBridges; // $s1
      int timeOffset; // $a2
      int loop; // $a3
    } // line 91, offset 0x465b0
    { // line 110, offset 0x46690
      int cCarriages; // $s0
      int first; // $s1
      { // line 119, offset 0x46698
      } // line 120, offset 0x466ac
    } // line 149, offset 0x467c4
  } // line 188, offset 0x46930
  { // line 243, offset 0x46b0c
    int trainModel; // $s5
    int loop; // $s1
    int carriages; // $s2
    { // line 296, offset 0x46c9c
      int loop; // $t1
      { // line 309, offset 0x46e40
        int detonatorModel; // $v0
      } // line 314, offset 0x46e98
    } // line 315, offset 0x46e98
  } // line 319, offset 0x46ea0
  { // line 323, offset 0x46ea0
    int detonatorModel; // $s3
    int loop; // $s1
    { // line 367, offset 0x46fec
      int loop; // $s1
      { // line 373, offset 0x470fc
        struct XYPAIR offset; // stack offset -64
      } // line 381, offset 0x47208
    } // line 389, offset 0x47280
    { // line 394, offset 0x472b4
    } // line 431, offset 0x47524
  } // line 433, offset 0x47524
} // line 449, offset 0x475a0
/*
 * Offset 0x475A0
 * D:\driver2\game\C\EVENT.C (line 991)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ SetCamera(struct _EVENT *ev /*$s5*/)
{ // line 1, offset 0x475a0
  int rotation; // $s4
  int axis; // $a3
  struct VECTOR pivot; // stack offset -96
  int iPivot; // $a2
  int height; // $a1
  struct SVECTOR offset; // stack offset -80
  { // line 46, offset 0x476f0
    struct MATRIX matrix; // stack offset -72
    struct SVECTOR temp; // stack offset -40
    { // line 54, offset 0x47774
    } // line 64, offset 0x477c4
  } // line 66, offset 0x477c4
} // line 113, offset 0x47a44
/*
 * Offset 0x47A44
 * D:\driver2\game\C\EVENT.C (line 1152)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ StepFromToEvent(struct _EVENT *ev /*$a3*/)
{ // line 1, offset 0x47a44
  { // line 8, offset 0x47a70
    int *from; // $a1
    int *to; // $t4
    long *current; // $t0
    int d; // $a0
    int d2; // $t2
  } // line 56, offset 0x47c2c
} // line 57, offset 0x47c3c
/*
 * Offset 0x47C3C
 * D:\driver2\game\C\EVENT.C (line 1214)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ StepPathEvent(struct _EVENT *ev /*$s0*/)
{ // line 1, offset 0x47c3c
  int *from; // $a1
  int *to; // $t1
  long *current; // $t3
  static int speed; // offset 0x20
  { // line 11, offset 0x47c70
    int flags; // $v0
  } // line 19, offset 0x47c9c
  { // line 28, offset 0x47ce4
    enum Station station; // $t2
    { // line 62, offset 0x47d94
      int direction; // $t2
      int loop; // $a2
      int *i; // $a0
      int turn[4]; // stack offset -48
      struct XZPAIR centre; // stack offset -32
      struct XZPAIR offset; // stack offset -24
    } // line 134, offset 0x48000
    { // line 141, offset 0x48018
      int d; // $a0
      int d1; // $v1
      int dir; // $t4
    } // line 233, offset 0x48360
  } // line 234, offset 0x48360
} // line 235, offset 0x48374
/*
 * Offset 0x48374
 * D:\driver2\game\C\EVENT.C (line 1478)
 * Stack frame base $sp, size 88
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ StepHelicopter(struct _EVENT *ev /*$s0*/)
{ // line 1, offset 0x48374
  static int rotacc; // offset 0xa4
  { // line 7, offset 0x4839c
    int b; // $a0
    int c; // $t2
    int d; // $v1
    int t; // $a1
    int t2; // $a3
    int t3; // $v1
    int dx1; // $a2
    int dx2; // $t1
    int dx3; // $t0
    int dz1; // $v0
    int dz2; // $a3
    int dz3; // $a0
    { // line 44, offset 0x48508
      struct XZPAIR vel; // stack offset -56
      int direction; // $t1
      int temp; // $t1
      int dt; // $a0
      int d2p; // $v1
      int d2r; // $v1
      int pitch; // $a1
      int roll; // $a2
      static int rotating; // offset 0x24
    } // line 99, offset 0x4885c
    { // line 112, offset 0x488bc
      struct VECTOR pos; // stack offset -48
    } // line 113, offset 0x488bc
  } // line 131, offset 0x48998
  { // line 135, offset 0x489b0
    struct VECTOR pos; // stack offset -56
    struct VECTOR drift; // stack offset -32
  } // line 135, offset 0x489b0
} // line 155, offset 0x48ac8
/*
 * Offset 0x48AC8
 * D:\driver2\game\C\EVENT.C (line 1642)
 * Stack frame base $sp, size 88
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ StepEvents()
{ // line 3, offset 0x48ac8
  struct _EVENT *ev; // $s0
  { // line 29, offset 0x48b2c
    struct VECTOR old; // stack offset -72
    int onBoatLastFrame; // $s7
    { // line 34, offset 0x48b34
      int dist; // stack offset -48
      int loop; // $s2
      struct _CAR_DATA *cp; // $s1
    } // line 57, offset 0x48c00
    { // line 72, offset 0x48ca8
      int d2; // $a2
    } // line 75, offset 0x48d1c
    { // line 82, offset 0x48d40
    } // line 83, offset 0x48d64
    { // line 87, offset 0x48d78
      struct XZPAIR speed; // stack offset -56
      { // line 91, offset 0x48d90
        int loop; // $s2
        int mask; // $s1
        { // line 98, offset 0x48dc8
          struct VECTOR *pos; // $a0
          struct VECTOR *vel; // $a1
        } // line 133, offset 0x48eb4
      } // line 134, offset 0x48ecc
    } // line 135, offset 0x48ecc
  } // line 136, offset 0x48ecc
  { // line 155, offset 0x48fac
    { // line 160, offset 0x48fbc
      int sign; // $t0
      unsigned short *target; // $a3
    } // line 178, offset 0x490d8
  } // line 183, offset 0x490e8
  { // line 220, offset 0x491b4
    int thisCamera; // $s1
    int otherCamera; // $s2
    int loop; // $s0
    unsigned short *x; // $t0
    unsigned short *z; // $a3
    { // line 247, offset 0x492a8
      struct CELL_OBJECT *cop; // $a2
    } // line 294, offset 0x4932c
  } // line 299, offset 0x49374
} // line 309, offset 0x493cc
/*
 * Offset 0x493CC
 * D:\driver2\game\C\EVENT.C (line 2110)
 * Stack frame base $sp, size 128
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ DrawFerrisWheel(struct MATRIX *matrix /*$s0*/, struct VECTOR *pos /*$s1*/)
{ // line 1, offset 0x493cc
  { // line 16, offset 0x494c8
    int loop; // $s3
    struct MODEL *model; // $s2
    struct VECTOR spoke[2]; // stack offset -104
    { // line 28, offset 0x4954c
      struct VECTOR offset; // stack offset -72
      struct VECTOR carPos; // stack offset -56
      int rotation; // $v0
    } // line 32, offset 0x4954c
  } // line 45, offset 0x496c0
} // line 47, offset 0x496ec
/*
 * Offset 0x496EC
 * D:\driver2\game\C\EVENT.C (line 2159)
 * Stack frame base $sp, size 136
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawRotor(struct VECTOR pos /*stack 0*/, struct MATRIX *matrix /*stack 16*/)
{ // line 1, offset 0x496ec
  struct SVECTOR v[5]; // stack offset -120
  struct MATRIX local; // stack offset -80
  struct POLY_FT4 *poly; // $t0
  struct TEXTURE_DETAILS *tex; // $t3
  int z; // stack offset -48
  char *firstPoly; // $a1
} // line 79, offset 0x49ca0
/*
 * Offset 0x49CA0
 * D:\driver2\game\C\EVENT.C (line 2240)
 * Stack frame base $sp, size 232
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawEvents(int camera /*stack 0*/)
{ // line 1, offset 0x49ca0
  unsigned short *x; // $a1
  unsigned short *z; // $a0
  int thisCamera; // stack offset -56
  int otherCamera; // stack offset -52
  static struct _EVENT *nearestTrain; // offset 0x28
  static int distanceFromNearestTrain; // offset 0x2c
  { // line 36, offset 0x49d7c
    struct _EVENT *ev; // $s1
    { // line 49, offset 0x49e74
      unsigned int dist; // $v1
    } // line 58, offset 0x49edc
    { // line 74, offset 0x49f0c
      { // line 76, offset 0x49f3c
        struct MATRIX matrix; // stack offset -208
        struct MATRIX ext; // stack offset -176
        struct VECTOR pos; // stack offset -144
        int reflection; // $s5
        int temp; // stack offset -48
        { // line 89, offset 0x49fb0
        } // line 89, offset 0x49fb0
        { // line 95, offset 0x4a01c
          { // line 106, offset 0x4a0a0
            struct VECTOR shadow[4]; // stack offset -128
            int loop; // $t0
            { // line 111, offset 0x4a0c4
              struct XZPAIR offset; // stack offset -64
              int rotate; // $a1
            } // line 118, offset 0x4a150
          } // line 121, offset 0x4a180
          { // line 133, offset 0x4a1e4
          } // line 142, offset 0x4a220
        } // line 143, offset 0x4a220
        { // line 153, offset 0x4a280
        } // line 153, offset 0x4a280
        { // line 172, offset 0x4a36c
          int i; // $a0
        } // line 179, offset 0x4a3bc
        { // line 184, offset 0x4a3d0
        } // line 201, offset 0x4a448
      } // line 245, offset 0x4a5a8
    } // line 245, offset 0x4a5a8
  } // line 255, offset 0x4a5f0
  { // line 270, offset 0x4a690
  } // line 270, offset 0x4a690
} // line 276, offset 0x4a6c0
/*
 * Offset 0x4A6F0
 * D:\driver2\game\C\EVENT.C (line 2560)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 ra
 */
struct _sdPlane * /*$ra*/ EventSurface(struct VECTOR *pos /*$a0*/, struct _sdPlane *plane /*$s1*/)
{ // line 1, offset 0x4a6f0
  struct _EVENT *ev; // $s0
  int i; // $a2
  { // line 12, offset 0x4a768
    int dist; // $a3
    int end; // $a1
    int cos; // $a2
  } // line 63, offset 0x4a8e8
  { // line 68, offset 0x4a8fc
    int dist; // stack offset -24
    { // line 72, offset 0x4a90c
      int sin; // $a3
      int cos; // $a2
      int height; // $t0
      int offset; // $a0
    } // line 104, offset 0x4aa88
  } // line 105, offset 0x4aa88
} // line 121, offset 0x4aae0
/*
 * Offset 0x4AAE0
 * D:\driver2\game\C\EVENT.C (line 2718)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
struct VECTOR * /*$ra*/ TriggerEvent(int i /*$s4*/)
{ // line 1, offset 0x4aae0
  static int stage[10]; // offset 0x200
  struct VECTOR *pos; // $s7
  { // line 8, offset 0x4ab18
    int loop; // $v1
  } // line 13, offset 0x4ab38
  { // line 21, offset 0x4ab88
    struct _EVENT *ev; // $a2
  } // line 22, offset 0x4ab88
  { // line 36, offset 0x4ac70
    { // line 39, offset 0x4ac70
      struct MissionTrain *train; // $s1
      { // line 45, offset 0x4aca0
      } // line 51, offset 0x4acb8
      { // line 56, offset 0x4acc4
        struct _EVENT *ev; // $s0
        int count; // $s2
        int offset; // $s6
        { // line 67, offset 0x4ad14
          int pos; // $a1
        } // line 67, offset 0x4ad14
      } // line 99, offset 0x4adf0
    } // line 101, offset 0x4adf0
    { // line 113, offset 0x4ae20
      struct _EVENT *ev; // $v1
      int count; // $a0
    } // line 130, offset 0x4ae6c
  } // line 142, offset 0x4ae90
  { // line 149, offset 0x4aef8
  } // line 179, offset 0x4afc8
  { // line 187, offset 0x4b010
    { // line 189, offset 0x4b010
      int loop; // $s0
    } // line 205, offset 0x4b0ac
  } // line 223, offset 0x4b138
} // line 274, offset 0x4b304
/*
 * Offset 0x4B304
 * D:\driver2\game\C\EVENT.C (line 2999)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SpecialCamera(enum SpecialCamera type /*$t2*/, int change /*$a1*/)
{ // line 1, offset 0x4b304
  static int rememberCamera[3]; // offset 0x230
  static short boatCamera[6]; // offset 0x684
  { // line 14, offset 0x4b34c
    int *hackCamera; // $a2
    short *boat; // $t3
  } // line 115, offset 0x4b5a8
} // line 143, offset 0x4b664
/*
 * Offset 0x4B664
 * D:\driver2\game\C\EVENT.C (line 3152)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ DetonatorTimer()
{ // line 2, offset 0x4b664
  static struct SVECTOR rememberCameraAngle; // offset 0x30
  { // line 16, offset 0x4b700
    { // line 23, offset 0x4b718
      static int count; // offset 0x38
      { // line 27, offset 0x4b734
        struct VECTOR pos; // stack offset -32
      } // line 32, offset 0x4b768
      { // line 36, offset 0x4b788
        struct VECTOR pos; // stack offset -32
      } // line 37, offset 0x4b788
    } // line 52, offset 0x4b830
  } // line 58, offset 0x4b844
  { // line 66, offset 0x4b8cc
    struct _EVENT *ev; // $s0
    struct VECTOR pos; // stack offset -32
    { // line 95, offset 0x4ba18
      struct VECTOR *epicentre; // $v1
    } // line 108, offset 0x4ba70
  } // line 123, offset 0x4baf4
} // line 126, offset 0x4bb18
/*
 * Offset 0x4BB18
 * D:\driver2\game\C\EVENT.C (line 3288)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ MultiCarEvent(struct _TARGET *target /*$a0*/)
{ // line 1, offset 0x4bb18
  struct MULTICAR_DATA *data; // $s0
  int i; // $s1
  struct _EVENT *ev; // $s2
  { // line 13, offset 0x4bb60
    int n; // $a1
  } // line 15, offset 0x4bb60
} // line 25, offset 0x4bc3c
/*
 * Offset 0x4BC3C
 * D:\driver2\game\C\EVENT.C (line 483)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitEvents()
{
}
/*
 * Offset 0x4BCB8
 * D:\driver2\game\C\EVENT.C (line 1107)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ EventCollisions(struct _CAR_DATA *cp /*$a2*/, int type /*$a1*/)
{ // line 1, offset 0x4bcb8
  static struct SVECTOR offset; // offset 0x18
} // line 18, offset 0x4bd94
/*
 * Offset 0x4BD94
 * D:\driver2\game\C\EVENT.C (line 2994)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ OffsetTarget(struct VECTOR *target /*$a0*/)
{
}
/*
 * Offset 0x4BDD4
 * D:\driver2\game\C\EVENT.C (line 2684)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MakeEventTrackable(struct _EVENT *ev /*$a0*/)
{ // line 1, offset 0x4bdd4
  struct _EVENT **p; // $v1
} // line 10, offset 0x4be08
/*
 * Offset 0x4BE08
 * D:\driver2\game\C\EVENT.C (line 2527)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ OnBoat(struct VECTOR *pos /*$t1*/, struct _EVENT *ev /*$a1*/, int *dist /*$a2*/)
{ // line 1, offset 0x4be08
  int halfBoatWidth; // $t0
  int halfBoatLength; // $a0
} // line 31, offset 0x4be8c
/*
 * Offset 0x4BE8C
 * D:\driver2\game\C\EVENT.C (line 2520)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ BoatOffset(struct SVECTOR *offset /*$a0*/, struct _EVENT *ev /*$a1*/)
{
}
/*
 * Offset 0x4BEC4
 * D:\driver2\game\C\EVENT.C (line 402)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetElTrainRotation(struct _EVENT *ev /*$a1*/)
{
}
/*
 * Offset 0x4BF20
 * D:\driver2\game\C\EVENT.C (line 471)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitDoor(struct FixedEvent *ev /*$a0*/, struct _EVENT ***e /*$a1*/, int *cEvents /*$a2*/)
{
}
/*
 * Offset 0x4BFBC
 * D:\driver2\game\C\EVENT.C (line 974)
 * Stack frame base $sp, size 16
 * Saved registers at offset -4: s0 s1 s2 s3
 */
void /*$ra*/ InitEventCamera()
{
}
/*
 * Offset 0x4C07C
 * D:\driver2\game\C\EVENT.C (line 983)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ResetEventCamera()
{
}
/*
 * Offset 0x4C10C
 * D:\driver2\game\C\EVENT.C (line 1127)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ NextNode(struct _EVENT *ev /*$a0*/)
{
}
/*
 * Offset 0x4C1C0
 * D:\driver2\game\C\EVENT.C (line 1452)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetBridgeRotation(int timer /*$a0*/)
{ // line 1, offset 0x4c1c0
  int angle; // $v1
} // line 24, offset 0x4c270
/*
 * Offset 0x4C270
 * D:\driver2\game\C\EVENT.C (line 2696)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ TriggerDoor(struct FixedEvent *door /*$a3*/, int *stage /*$a1*/, int sound /*$a2*/)
{
}
/*
 * Offset 0x4C2E8
 * D:\driver2\game\C\EVENT.C (line 3144)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ScreenShake(int count /*$a0*/, struct SVECTOR *ang /*$s0*/)
{ // line 1, offset 0x4c2e8
} // line 6, offset 0x4c398
/*
 * Offset 0x4C398
 * D:\driver2\game\C\FELONY.C (line 476)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ NoteFelony(struct FELONY_DATA *pFelonyData /*$a3*/, char type /*$s3*/, short scale /*$t0*/)
{ // line 1, offset 0x4c398
  int felonyTooLowForRoadblocks; // $s4
  { // line 2, offset 0x4c410
    struct FELONY_DELAY *pFelonyDelay; // $v1
  } // line 19, offset 0x4c434
  { // line 36, offset 0x4c468
    int additionalFelonyPoints; // $a0
  } // line 52, offset 0x4c57c
  { // line 77, offset 0x4c698
    char rnd; // $s1
    int dir; // $a3
  } // line 107, offset 0x4c86c
} // line 112, offset 0x4c8fc
/*
 * Offset 0x4C91C
 * D:\driver2\game\C\FELONY.C (line 597)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ AdjustFelony(struct FELONY_DATA *pFelonyData /*$a0*/)
{ // line 1, offset 0x4c91c
  { // line 52, offset 0x4cc50
    struct FELONY_DELAY *pFelonyDelay; // $v1
  } // line 61, offset 0x4cc90
} // line 62, offset 0x4cc90
/*
 * Offset 0x4CC90
 * D:\driver2\game\C\FELONY.C (line 668)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CheckPlayerMiscFelonies()
{ // line 2, offset 0x4cc90
  struct FELONY_DATA *pFelonyData; // $s4
  struct DRIVER2_CURVE *cv; // $s5
  struct DRIVER2_STRAIGHT *st; // $s6
  struct _CAR_DATA *cp; // $s3
  struct VECTOR *carPos; // $s2
  int surfInd; // $s0
  { // line 22, offset 0x4cd28
    char i; // $a1
    { // line 31, offset 0x4cdcc
      struct DRIVER2_JUNCTION *jn; // $a2
      short exitId; // $s1
    } // line 47, offset 0x4ce74
  } // line 48, offset 0x4ce74
  { // line 48, offset 0x4ce74
    char goingWrongWay; // $s7
    int lane; // $s0
    int dx; // $v1
    int dz; // $a0
    { // line 70, offset 0x4d014
    } // line 80, offset 0x4d140
  } // line 90, offset 0x4d160
  { // line 111, offset 0x4d200
    int maxSpeed; // $a0
    int limit; // $v1
  } // line 137, offset 0x4d2b8
} // line 138, offset 0x4d2b8
/*
 * Offset 0x4D2E8
 * D:\driver2\game\C\FELONY.C (line 810)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitFelonySystem()
{
}
/*
 * Offset 0x4D320
 * D:\driver2\game\C\FELONY.C (line 824)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ CarHitByPlayer(struct _CAR_DATA *victim /*$a0*/, int howHard /*$a2*/)
{
}
/*
 * Offset 0x4D3CC
 * D:\driver2\game\C\FELONY.C (line 413)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitFelonyDelayArray(struct FELONY_DELAY *pFelonyDelay /*$a0*/, short *pMaximum /*$a1*/, int count /*$a2*/)
{ // line 1, offset 0x4d3cc
  struct FELONY_DELAY *pCurrent; // $a0
} // line 9, offset 0x4d408
/*
 * Offset 0x4D408
 * D:\driver2\game\C\FELONY.C (line 431)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ InitFelonyData(struct FELONY_DATA *pFelonyData /*$s0*/)
{ // line 1, offset 0x4d408
  { // line 1, offset 0x4d408
    struct FELONY_VALUE *pSrc; // $v1
    struct FELONY_VALUE *pDest; // $s0
    struct FELONY_VALUE *pEnd; // $a0
  } // line 14, offset 0x4d488
} // line 15, offset 0x4d488
/*
 * Offset 0x4D488
 * D:\driver2\game\C\FELONY.C (line 450)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetCarHeading(int direction /*$a0*/)
{
}
/*
 * Offset 0x4D498
 * D:\driver2\game\C\FELONY.C (line 454)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
char /*$ra*/ GetCarDirectionOfTravel(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x4d498
  int direction; // $v0
} // line 12, offset 0x4d4e0
/*
 * Offset 0x4D4E0
 * D:\driver2\game\C\FMVPLAY.C (line 23)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ ReInitSystem()
{ // line 2, offset 0x4d4e0
} // line 25, offset 0x4d580
/*
 * Offset 0x4D580
 * D:\driver2\game\C\FMVPLAY.C (line 68)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ PlayFMV(unsigned char render /*$s0*/)
{ // line 1, offset 0x4d580
  struct RENDER_ARGS args; // stack offset -40
  { // line 7, offset 0x4d5ac
  } // line 7, offset 0x4d5ac
  { // line 12, offset 0x4d5d8
  } // line 13, offset 0x4d5e0
} // line 28, offset 0x4d638
/*
 * Offset 0x4D638
 * D:\driver2\game\C\FMVPLAY.C (line 107)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ PlayRender(struct RENDER_ARGS *args /*$s0*/)
{ // line 1, offset 0x4d638
  static unsigned long oldsp; // offset 0x0
  { // line 22, offset 0x4d69c
  } // line 31, offset 0x4d6e0
} // line 34, offset 0x4d6f8
/*
 * Offset 0x4D6F8
 * D:\driver2\game\C\GAMESND.C (line 171)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ ResidentModelsBodge()
{ // line 1, offset 0x4d6f8
  int i; // $a1
  int j; // $a2
} // line 12, offset 0x4d7ec
/*
 * Offset 0x4D7EC
 * D:\driver2\game\C\GAMESND.C (line 228)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ LoadLevelSFX(int missionNum /*$s1*/)
{ // line 1, offset 0x4d7ec
  char city_night_fx; // $s2
  int i; // $s0
  { // line 38, offset 0x4db40
    int mission; // $a1
  } // line 41, offset 0x4dcd8
} // line 67, offset 0x4de98
/*
 * Offset 0x4DE98
 * D:\driver2\game\C\GAMESND.C (line 305)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ StartGameSounds()
{ // line 2, offset 0x4de98
  struct VECTOR *cp; // $s2
  int i; // $s1
  { // line 10, offset 0x4defc
    int siren; // $a2
    int car_model; // $s0
  } // line 28, offset 0x4e0e4
} // line 59, offset 0x4e1f0
/*
 * Offset 0x4E1F0
 * D:\driver2\game\C\GAMESND.C (line 404)
 * Stack frame base $sp, size 0
 */
unsigned short /*$ra*/ GetEngineRevs(struct _CAR_DATA *cp /*$t2*/)
{ // line 1, offset 0x4e1f0
  int gear; // $a1
  int lastgear; // $a0
  int ws; // $a2
  int acc; // $t1
  int type; // $t0
} // line 35, offset 0x4e350
/*
 * Offset 0x4E350
 * D:\driver2\game\C\GAMESND.C (line 458)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ ControlCarRevs(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x4e350
  unsigned short oldRevs; // $s2
  unsigned short desiredRevs; // $v1
  unsigned short newRevs; // $a0
  int acc; // $s3
  char spin; // $s4
  char player_id; // $s1
  { // line 40, offset 0x4e47c
    int revsmax; // $a3
  } // line 46, offset 0x4e53c
} // line 55, offset 0x4e5c8
/*
 * Offset 0x4E5C8
 * D:\driver2\game\C\GAMESND.C (line 595)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ControlSpeech(struct SPEECH_QUEUE *pSpeechQueue /*$s0*/)
{ // line 1, offset 0x4e5c8
} // line 40, offset 0x4e768
/*
 * Offset 0x4E778
 * D:\driver2\game\C\GAMESND.C (line 721)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitDopplerSFX()
{ // line 1, offset 0x4e778
  int i; // $v1
} // line 5, offset 0x4e7f8
/*
 * Offset 0x4E7F8
 * D:\driver2\game\C\GAMESND.C (line 734)
 * Stack frame base $sp, size 200
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DoDopplerSFX()
{ // line 1, offset 0x4e7f8
  int i; // $s1
  int j; // $s0
  int num_noisy_cars; // $s5
  unsigned long car_dist[20]; // stack offset -176
  unsigned short indexlist[20]; // stack offset -96
  struct _CAR_DATA *car_ptr; // $s2
  struct VECTOR *pp; // $a1
  unsigned long car_flags; // $s4
  char sirens; // stack offset -56
  { // line 91, offset 0x4ed20
    int siren; // $v0
  } // line 108, offset 0x4ee30
  { // line 156, offset 0x4f104
    int model; // $v1
  } // line 158, offset 0x4f19c
  { // line 175, offset 0x4f224
    char old_idle; // $a1
    { // line 180, offset 0x4f2a8
      int model; // $v1
    } // line 190, offset 0x4f37c
  } // line 195, offset 0x4f3d0
} // line 210, offset 0x4f508
/*
 * Offset 0x4F508
 * D:\driver2\game\C\GAMESND.C (line 946)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DoPoliceLoudhailer(int cars /*$s1*/, unsigned short *indexlist /*$s2*/, unsigned long *dist /*$s3*/)
{ // line 1, offset 0x4f508
  int i; // $t1
  int rnd; // $t0
  int time; // $s0
  { // line 5, offset 0x4f5c8
    struct _CAR_DATA *car_ptr; // $a3
  } // line 13, offset 0x4f68c
} // line 16, offset 0x4f6b4
/*
 * Offset 0x4F6D0
 * D:\driver2\game\C\GAMESND.C (line 975)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CollisionSound(char player_id /*$s0*/, struct _CAR_DATA *cp /*$s5*/, int impact /*$s2*/, int car_car /*$s7*/)
{ // line 1, offset 0x4f6d0
  long *here; // $s3
  char chan; // $s1
  char crash; // $s6
  char size; // $s4
  { // line 8, offset 0x4f758
    unsigned long p0dst; // $a1
    unsigned long p1dst; // $a0
  } // line 9, offset 0x4f758
  { // line 18, offset 0x4f7ec
    { // line 25, offset 0x4f900
    } // line 32, offset 0x4f998
  } // line 36, offset 0x4f9bc
} // line 37, offset 0x4f9bc
/*
 * Offset 0x4F9EC
 * D:\driver2\game\C\GAMESND.C (line 1019)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ExplosionSound(struct VECTOR *pos /*$s4*/, int type /*$s0*/)
{ // line 1, offset 0x4f9ec
  int bang; // $s5
  int pitch; // $t0
  int rnd; // $s3
  struct VECTOR P; // stack offset -48
  int sc1; // $s2
  int sc2; // $s1
} // line 29, offset 0x4fbd8
/*
 * Offset 0x4FBFC
 * D:\driver2\game\C\GAMESND.C (line 1052)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ JerichoSpeak()
{ // line 1, offset 0x4fbfc
  static unsigned int j_said; // offset 0x0
  int rnd; // $a1
} // line 8, offset 0x4fcf8
/*
 * Offset 0x4FCF8
 * D:\driver2\game\C\GAMESND.C (line 1103)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ SoundTasks()
{ // line 1, offset 0x4fcf8
  int i; // $s2
  struct _CAR_DATA *cp; // $s1
} // line 80, offset 0x5014c
/*
 * Offset 0x5014C
 * D:\driver2\game\C\GAMESND.C (line 1195)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ InitMusic(int musicnum /*$s0*/)
{ // line 1, offset 0x5014c
  static char *music_pt; // offset 0xc
  static char *sample_pt; // offset 0x10
  static char xm_samples; // offset 0x4
  int musicpos[3]; // stack offset -32
  char *name; // $s1
  int sample_len; // $s0
  int music_len; // $t0
  { // line 45, offset 0x5020c
  } // line 52, offset 0x50270
} // line 61, offset 0x502e4
/*
 * Offset 0x502E4
 * D:\driver2\game\C\GAMESND.C (line 1350)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ Tunnels(struct __tunnelinfo *T /*$a0*/)
{ // line 1, offset 0x502e4
  int i; // $t2
  int verb; // $t4
} // line 14, offset 0x50468
/*
 * Offset 0x50468
 * D:\driver2\game\C\GAMESND.C (line 1366)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ AddTunnels(int level /*$a0*/)
{
}
/*
 * Offset 0x50C70
 * D:\driver2\game\C\GAMESND.C (line 1577)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ AddEnvSnd(int type /*$t4*/, char flags /*$a1*/, int bank /*$a2*/, int sample /*$a3*/, int vol /*stack 16*/, long px /*stack 20*/, long pz /*stack 24*/)
{ // line 1, offset 0x50c70
  void *data; // $a1
  struct __envsound *ep; // $t1
  struct __envsoundtags *T; // $t0
  long s; // $a1
} // line 58, offset 0x50e70
/*
 * Offset 0x50E70
 * D:\driver2\game\C\GAMESND.C (line 1646)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ IdentifyZone(struct __envsound *ep /*$a3*/, struct __envsoundinfo *E /*stack 4*/, int pl /*$a2*/)
{ // line 1, offset 0x50e70
  int i; // $s7
  int j; // $fp
  int tmp[4]; // stack offset -96
  float d; // $s0
  float _g[4]; // stack offset -80
  struct __bitfield64 zones; // stack offset -64
} // line 58, offset 0x51524
/*
 * Offset 0x51524
 * D:\driver2\game\C\GAMESND.C (line 1706)
 * Stack frame base $sp, size 8
 * Saved registers at offset -4: s0 s1
 */
void /*$ra*/ CalcEffPos(struct __envsound *ep /*$s1*/, struct __envsoundinfo *E /*$a1*/, int pl /*$a2*/)
{ // line 1, offset 0x51524
  int j; // $t5
  int me; // $t2
} // line 36, offset 0x51838
/*
 * Offset 0x51838
 * D:\driver2\game\C\GAMESND.C (line 1744)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CalcEffPos2(struct __envsound *ep /*stack 0*/, struct __envsoundinfo *E /*$s7*/, int pl /*$a2*/)
{ // line 1, offset 0x51838
  int j; // stack offset -56
  int me; // $s5
  { // line 12, offset 0x51940
  } // line 12, offset 0x51940
} // line 66, offset 0x51f74
/*
 * Offset 0x51F74
 * D:\driver2\game\C\GAMESND.C (line 1812)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ UpdateEnvSnd(struct __envsound *ep /*stack 0*/, struct __envsoundinfo *E /*$s4*/, int pl /*stack 8*/)
{ // line 1, offset 0x51f74
  int i; // stack offset -48
} // line 29, offset 0x521d0
/*
 * Offset 0x521D0
 * D:\driver2\game\C\GAMESND.C (line 1545)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ SetEnvSndVol(int snd /*$a0*/, int vol /*$a1*/)
{ // line 1, offset 0x521d0
  int was; // $v0
} // line 5, offset 0x521f8
/*
 * Offset 0x521F8
 * D:\driver2\game\C\GAMESND.C (line 665)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ CopSay(int phrase /*$s1*/, int direction /*$s2*/)
{
}
/*
 * Offset 0x522F4
 * D:\driver2\game\C\GAMESND.C (line 562)
 * Stack frame base $sp, size 0
 */
char /*$ra*/ PlaySpeech(struct SPEECH_QUEUE *pSpeechQueue /*$a0*/, int sound /*$a1*/)
{ // line 1, offset 0x522f4
  char result; // $v0
  int i; // $a2
} // line 21, offset 0x52354
/*
 * Offset 0x52354
 * D:\driver2\game\C\GAMESND.C (line 127)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CarHasSiren(int index /*$a0*/)
{
}
/*
 * Offset 0x523F0
 * D:\driver2\game\C\GAMESND.C (line 1510)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitEnvSnd(int num_envsnds /*$a0*/)
{ // line 1, offset 0x523f0
  int i; // $v1
  int p; // $a1
  struct __envsoundtags *T; // $t1
} // line 28, offset 0x524a4
/*
 * Offset 0x524A4
 * D:\driver2\game\C\GAMESND.C (line 1317)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitTunnels(char n /*$a0*/)
{ // line 1, offset 0x524a4
  struct __tunnelinfo *T; // $a1
} // line 8, offset 0x524c8
/*
 * Offset 0x524C8
 * D:\driver2\game\C\GAMESND.C (line 98)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ LoadBankFromLump(int bank /*$s3*/, int lump /*$s2*/)
{ // line 1, offset 0x524c8
  static unsigned int blockLimit[73]; // offset 0x10
  int size; // $s0
  char *name; // $s1
} // line 21, offset 0x52578
/*
 * Offset 0x52578
 * D:\driver2\game\C\GAMESND.C (line 161)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ SpecialVehicleKludge(char vehicle2 /*$a0*/)
{ // line 1, offset 0x52578
  static char kludge_bank[4][3]; // offset 0x134
} // line 8, offset 0x525a8
/*
 * Offset 0x525A8
 * D:\driver2\game\C\GAMESND.C (line 197)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ MapCarIndexToBank(int index /*$a1*/)
{ // line 1, offset 0x525a8
  int *RM; // $a2
  static char car_banks[4][9]; // offset 0x140
} // line 22, offset 0x52660
/*
 * Offset 0x52660
 * D:\driver2\game\C\GAMESND.C (line 515)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DoSpeech(int chan /*$a0*/, int sound /*$a2*/)
{
}
/*
 * Offset 0x526BC
 * D:\driver2\game\C\GAMESND.C (line 587)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ InitSpeechQueue(struct SPEECH_QUEUE *pSpeechQueue /*$s0*/)
{
}
/*
 * Offset 0x526FC
 * D:\driver2\game\C\GAMESND.C (line 677)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ BodSay(int phrase /*$a1*/)
{
}
/*
 * Offset 0x52738
 * D:\driver2\game\C\GAMESND.C (line 686)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ MissionSay(int phrase /*$a0*/)
{ // line 1, offset 0x52738
} // line 5, offset 0x52764
/*
 * Offset 0x52774
 * D:\driver2\game\C\GAMESND.C (line 700)
 * Stack frame base $sp, size 16
 */
long /*$ra*/ jsqrt(unsigned long a /*$a0*/)
{ // line 1, offset 0x52774
  long b1; // $a1
  long b0; // $v1
} // line 13, offset 0x52828
/*
 * Offset 0x52828
 * D:\driver2\game\C\GAMESND.C (line 1085)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ FunkUpDaBGMTunez(int funk /*$a0*/)
{
}
/*
 * Offset 0x528B0
 * D:\driver2\game\C\GAMESND.C (line 1331)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ AddTunnel(long x1 /*$t1*/, long y1 /*$a1*/, long z1 /*$a2*/, long x2 /*$a3*/, long y2 /*stack 16*/, long z2 /*stack 20*/)
{ // line 1, offset 0x528b0
  struct __tunnelinfo *T; // $t0
} // line 13, offset 0x52964
/*
 * Offset 0x5296C
 * D:\driver2\game\C\GAMESND.C (line 1555)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetEnvSndPos(int snd /*$a0*/, long px /*$a1*/, long pz /*$a2*/)
{
}
/*
 * Offset 0x529B0
 * D:\driver2\game\C\GAMESND.C (line 1852)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitLeadHorn()
{
}
/*
 * Offset 0x529BC
 * D:\driver2\game\C\GAMESND.C (line 1855)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ LeadHorn(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x529bc
  static unsigned int rnd; // offset 0x8
} // line 12, offset 0x52a90
/*
 * Offset 0x52A90
 * D:\driver2\game\C\GLAUNCH.C (line 834)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ GameStart()
{ // line 2, offset 0x52a90
  struct RECT rect; // stack offset -16
  int oldVMode; // $s0
  int SurvivalCopSettingsBackup; // $s0
} // line 177, offset 0x52f00
/*
 * Offset 0x52F00
 * D:\driver2\game\C\GLAUNCH.C (line 1030)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ReInitFrontend()
{ // line 2, offset 0x52f00
  struct RECT rect; // stack offset -24
} // line 73, offset 0x53050
/*
 * Offset 0x53050
 * D:\driver2\game\C\GLAUNCH.C (line 1105)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ RunMissionLadder(int newgame /*$a1*/)
{ // line 1, offset 0x53050
  struct MISSION_STEP *CurrentStep; // $s0
  struct RENDER_ARGS RenderArgs; // stack offset -48
  int quit; // $s3
  { // line 38, offset 0x5310c
  } // line 38, offset 0x5310c
  { // line 43, offset 0x5311c
  } // line 44, offset 0x53124
  { // line 48, offset 0x53134
  } // line 52, offset 0x53150
  { // line 58, offset 0x5319c
    { // line 67, offset 0x53200
    } // line 70, offset 0x53214
  } // line 107, offset 0x532f4
} // line 110, offset 0x53320
/*
 * Offset 0x53320
 * D:\driver2\game\C\GLAUNCH.C (line 1279)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ LaunchGame()
{ // line 2, offset 0x53320
  struct RECT rect; // stack offset -16
  int quit; // $s0
} // line 136, offset 0x53640
/*
 * Offset 0x53640
 * D:\driver2\game\C\GLAUNCH.C (line 1222)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ GetRandomChase()
{ // line 2, offset 0x53640
  int bump; // $s1
} // line 28, offset 0x53704
/*
 * Offset 0x53718
 * D:\driver2\game\C\GLAUNCH.C (line 1018)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ StartRender(int renderNum /*$a0*/)
{
}
/*
 * Offset 0x53740
 * D:\driver2\game\C\GLAUNCH.C (line 1252)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ FindPrevMissionFromLadderPos(int pos /*$a0*/)
{ // line 2, offset 0x53740
} // line 16, offset 0x537a8
/*
 * Offset 0x537A8
 * D:\driver2\game\C\GLAUNCH.C (line 1417)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ FindMissionLadderPos(int mission /*$a0*/)
{ // line 1, offset 0x537a8
  struct MISSION_STEP *step; // $a1
  int pos; // $a2
} // line 40, offset 0x5387c
/*
 * Offset 0x53884
 * D:\driver2\game\C\HANDLING.C (line 998)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ InitCarPhysics(struct _CAR_DATA *cp /*$s0*/, long *startpos[4] /*$t0*/, int direction /*$a2*/)
{ // line 1, offset 0x53884
  int ty; // $v1
  int dz; // $s1
  int odz; // $a3
  { // line 6, offset 0x538f8
    unsigned long *dst; // $a1
  } // line 6, offset 0x538f8
} // line 42, offset 0x53a50
/*
 * Offset 0x53A50
 * D:\driver2\game\C\HANDLING.C (line 1055)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ TempBuildHandlingMatrix(struct _CAR_DATA *cp /*$s0*/, int init /*$a1*/)
{ // line 1, offset 0x53a50
  int ty; // $v1
  int dz; // $a3
} // line 20, offset 0x53b70
/*
 * Offset 0x53B70
 * D:\driver2\game\C\HANDLING.C (line 1079)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ UpdateCarPoints(struct CAR_COSMETICS *carCos /*$a0*/)
{ // line 1, offset 0x53b70
  struct SVECTOR *groundCollPoints; // $a1
  struct SVECTOR *wheelPoints; // $a3
  int i; // $a2
} // line 24, offset 0x53c68
/*
 * Offset 0x53C68
 * D:\driver2\game\C\HANDLING.C (line 1192)
 * Stack frame base $sp, size 272
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ GlobalTimeStep()
{ // line 2, offset 0x53c68
  int i; // $fp
  int RKstep; // stack offset -84
  int subframe; // stack offset -80
  struct _CAR_DATA *c0; // $s0
  static union RigidBodyState _tp[20]; // offset 0x0
  static union RigidBodyState _d0[20]; // offset 0x410
  static union RigidBodyState _d1[20]; // offset 0x820
  { // line 76, offset 0x53cd4
    struct _CAR_DATA *c0; // $t2
    union RigidBodyState *st; // $t1
    { // line 91, offset 0x53d94
      int s; // $v0
    } // line 101, offset 0x53df8
    { // line 109, offset 0x53e80
      long AV[4]; // stack offset -248
      long delta_orientation[4]; // stack offset -232
    } // line 129, offset 0x54060
  } // line 130, offset 0x54060
  { // line 142, offset 0x5408c
    union RigidBodyState *thisDelta; // stack offset -76
    { // line 148, offset 0x540a0
      struct _CAR_DATA *c0; // $s4
      { // line 156, offset 0x540fc
        union RigidBodyState *thisState_i; // $s6
        int j; // stack offset -72
        { // line 1, offset 0x54154
          union RigidBodyState *state; // $s6
          union RigidBodyState *delta; // $a3
          struct _CAR_DATA *cp; // $s4
          { // line 1, offset 0x54154
            long AV[4]; // stack offset -248
          } // line 1, offset 0x54154
        } // line 1, offset 0x54154
        { // line 175, offset 0x54340
          struct _CAR_DATA *c1; // $s3
          union RigidBodyState *thisState_j; // $s0
          { // line 183, offset 0x543a8
            int strength; // $s5
            long centre0[4]; // stack offset -248
            long centre1[4]; // stack offset -232
            long normal[4]; // stack offset -216
            long collisionpoint[4]; // stack offset -200
            { // line 186, offset 0x543a8
              struct BOUND_BOX *bb1; // $a2
              struct BOUND_BOX *bb2; // $a0
            } // line 217, offset 0x544a8
            { // line 222, offset 0x544a8
              int depth; // stack offset -88
            } // line 227, offset 0x544c8
            { // line 227, offset 0x544c8
              long lever0[4]; // stack offset -184
              long lever1[4]; // stack offset -168
              long torque[4]; // stack offset -152
              long pointVel0[4]; // stack offset -136
              long pointVel1[4]; // stack offset -120
              int strikeVel; // stack offset -68
              { // line 227, offset 0x544c8
                int is; // $v0
                int wanted; // $v1
              } // line 227, offset 0x544c8
              { // line 295, offset 0x548d8
                struct VECTOR velocity; // stack offset -104
                { // line 314, offset 0x5498c
                  int debris1; // $s0
                  int debris2; // $s2
                } // line 326, offset 0x549e4
              } // line 327, offset 0x549e4
              { // line 334, offset 0x54a24
                int do1; // $a0
                int do2; // $t5
                int m1; // $t3
                int m2; // $a1
                { // line 356, offset 0x54ab8
                  long force[4]; // stack offset -104
                  int strength1; // $a0
                  int twistY; // $t4
                } // line 385, offset 0x54d08
                { // line 389, offset 0x54d10
                  long force[4]; // stack offset -104
                  int strength2; // $a1
                  int twistY; // $t2
                } // line 418, offset 0x54f44
              } // line 419, offset 0x54f44
            } // line 426, offset 0x54fc0
          } // line 427, offset 0x54fc0
        } // line 428, offset 0x54fc0
      } // line 429, offset 0x54fe4
    } // line 430, offset 0x54fe4
    { // line 434, offset 0x5500c
      struct _CAR_DATA *c0; // $a1
      { // line 438, offset 0x5502c
        union RigidBodyState *st; // $t2
        union RigidBodyState *tp; // $a0
        union RigidBodyState *d0; // $a2
        union RigidBodyState *d1; // $v1
        int j; // $t1
      } // line 454, offset 0x55118
    } // line 455, offset 0x55118
  } // line 456, offset 0x55130
  { // line 460, offset 0x5515c
    int carsDentedThisFrame; // $s2
    { // line 463, offset 0x5516c
      { // line 464, offset 0x5516c
        unsigned long *dst; // $a1
      } // line 464, offset 0x5516c
      { // line 478, offset 0x551f0
      } // line 481, offset 0x55200
    } // line 483, offset 0x55200
  } // line 487, offset 0x55254
} // line 507, offset 0x55254
/*
 * Offset 0x55254
 * D:\driver2\game\C\HANDLING.C (line 1704)
 * Stack frame base $sp, size 120
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SetShadowPoints(struct _CAR_DATA *c0 /*$s4*/)
{ // line 1, offset 0x55254
  int j; // $s2
  struct CAR_COSMETICS *car_cos; // $v1
  struct _sdPlane *surfacePtr; // stack offset -48
  { // line 14, offset 0x55310
    struct SVECTOR disp; // stack offset -104
    struct VECTOR pointPos; // stack offset -96
    struct VECTOR surfaceNormal; // stack offset -80
    struct VECTOR surfacePoint; // stack offset -64
  } // line 35, offset 0x553f0
} // line 37, offset 0x55434
/*
 * Offset 0x55434
 * D:\driver2\game\C\HANDLING.C (line 1753)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ LongQuaternion2Matrix(long *qua[4] /*$a0*/, struct MATRIX *m /*$a1*/)
{ // line 1, offset 0x55434
  int xx; // $t3
  int xy; // $a3
  int xz; // $t2
  int xw; // $t0
  int yy; // $t7
  int yz; // $a2
  int yw; // $t5
  int zz; // $v1
  int zw; // $a0
} // line 25, offset 0x55558
/*
 * Offset 0x55558
 * D:\driver2\game\C\HANDLING.C (line 1802)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ initOBox(struct _CAR_DATA *cp /*$a2*/)
{ // line 1, offset 0x55558
  struct SVECTOR *boxDisp; // $a0
  { // line 1, offset 0x55558
    int length; // $a1
  } // line 40, offset 0x55748
} // line 42, offset 0x55748
/*
 * Offset 0x55748
 * D:\driver2\game\C\HANDLING.C (line 1930)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ CheckCarToCarCollisions()
{ // line 2, offset 0x55748
  struct _CAR_DATA *cp; // $t2
  struct BOUND_BOX *bp; // $t1
  struct BOUND_BOX *bb1; // $t0
  struct BOUND_BOX *bb2; // $a1
  int lbod; // $v1
  int wbod; // $a0
  int hbod; // $t0
  struct SVECTOR *colBox; // $a1
  int loop1; // $t4
  int loop2; // $a3
  { // line 17, offset 0x55774
    int wx; // $v1
    int wz; // $a2
  } // line 52, offset 0x55994
} // line 84, offset 0x55afc
/*
 * Offset 0x55B04
 * D:\driver2\game\C\HANDLING.C (line 2027)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ProcessCarPad(struct _CAR_DATA *cp /*$s0*/, unsigned long pad /*$s3*/, char PadSteer /*$s4*/, char use_analogue /*$s5*/)
{ // line 1, offset 0x55b04
  int player_id; // $s1
  { // line 131, offset 0x55d40
    int int_steer; // $v0
    int analog_angle; // $v1
  } // line 153, offset 0x55df8
  { // line 233, offset 0x55f58
    int rws; // $v0
  } // line 243, offset 0x55fe8
  { // line 255, offset 0x5604c
    int playerCar; // $v0
    int dist; // $a0
    int dx; // $a0
    int dz; // $v0
  } // line 272, offset 0x560e8
  { // line 276, offset 0x560f8
    int targetCarId; // $v1
    { // line 293, offset 0x5613c
      struct _CAR_DATA *tp; // $a1
      int cx; // $v1
      int cz; // $v0
      int chase_square_dist; // $v0
      { // line 300, offset 0x56174
        int averagePower; // $a0
      } // line 302, offset 0x561b0
    } // line 313, offset 0x562c0
  } // line 315, offset 0x562c0
} // line 348, offset 0x56314
/*
 * Offset 0x56314
 * D:\driver2\game\C\HANDLING.C (line 2397)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ TerminateSkidding(int player_id /*$a0*/)
{
}
/*
 * Offset 0x563B8
 * D:\driver2\game\C\HANDLING.C (line 2414)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ CheckCarEffects(struct _CAR_DATA *cp /*$s2*/, int player_id /*$s3*/)
{ // line 1, offset 0x563b8
  int skidsound; // $s1
  int cnt; // $a0
  int wheels_on_ground; // $s5
  char lay_down_tracks; // $s7
  char desired_skid; // $a1
  char desired_wheel; // $a1
  { // line 86, offset 0x56650
    int pitch; // $v0
  } // line 90, offset 0x566ac
  { // line 93, offset 0x566c8
    int wnse; // $a0
  } // line 96, offset 0x56710
  { // line 119, offset 0x56810
    int pitch; // $t0
  } // line 123, offset 0x56878
  { // line 132, offset 0x568a8
  } // line 136, offset 0x568d0
} // line 146, offset 0x56914
/*
 * Offset 0x56940
 * D:\driver2\game\C\HANDLING.C (line 2575)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ jump_debris(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, offset 0x56940
  int count; // $a1
  { // line 24, offset 0x569cc
    struct VECTOR position; // stack offset -48
    struct VECTOR velocity; // stack offset -32
  } // line 28, offset 0x56a60
} // line 29, offset 0x56a60
/*
 * Offset 0x56A74
 * D:\driver2\game\C\HANDLING.C (line 1875)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ StepCarPhysics(struct _CAR_DATA *cp /*$a2*/)
{ // line 1, offset 0x56a74
  struct _HANDLING_TYPE *hp; // $v0
} // line 24, offset 0x56acc
/*
 * Offset 0x56AD4
 * D:\driver2\game\C\HANDLING.C (line 1911)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitialiseCarHandling()
{
}
/*
 * Offset 0x56ADC
 * D:\driver2\game\C\HANDLING.C (line 2607)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ nose_down(struct _CAR_DATA *cp /*$a0*/)
{
}
/*
 * Offset 0x56B4C
 * D:\driver2\game\C\HANDLING.C (line 1854)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ RebuildCarMatrix(union RigidBodyState *st /*$a2*/, struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x56b4c
  { // line 1, offset 0x56b4c
    int sm; // $v1
    { // line 5, offset 0x56bf4
      int osm; // $v0
    } // line 5, offset 0x56c68
  } // line 5, offset 0x56c68
} // line 8, offset 0x56c8c
/*
 * Offset 0x56C8C
 * D:\driver2\game\C\HANDLING.C (line 1106)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ FixCarCos(struct CAR_COSMETICS *carCos /*$s0*/, int externalModelNumber /*$a1*/)
{ // line 1, offset 0x56c8c
  int current; // $v0
} // line 24, offset 0x56d20
/*
 * Offset 0x56D20
 * D:\driver2\game\C\HANDLING.C (line 2389)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitSkidding()
{ // line 1, offset 0x56d20
  int i; // $a0
} // line 6, offset 0x56d54
/*
 * Offset 0x56D54
 * D:\driver2\game\C\HANDLING.C (line 2664)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetPlayerId(struct _CAR_DATA *cp /*$a0*/)
{ // line 1, offset 0x56d54
  int i; // $a1
  int p_id; // $a3
} // line 5, offset 0x56dbc
/*
 * Offset 0x56DBC
 * D:\driver2\game\C\JOB_FX.C (line 129)
 * Stack frame base $sp, size 8
 * Saved registers at offset -8: s0
 */
void /*$ra*/ AddExplosion(struct VECTOR pos /*stack 0*/, int type /*stack 16*/)
{ // line 1, offset 0x56dbc
  int i; // $t1
} // line 40, offset 0x56eac
/*
 * Offset 0x56EAC
 * D:\driver2\game\C\JOB_FX.C (line 178)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ HandleExplosion()
{ // line 2, offset 0x56eac
  int i; // $s5
  struct _CAR_DATA *cp; // $s0
  { // line 34, offset 0x56fb4
  } // line 42, offset 0x56fec
} // line 45, offset 0x56ffc
/*
 * Offset 0x57028
 * D:\driver2\game\C\JOB_FX.C (line 557)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ initExplosion()
{ // line 2, offset 0x57028
  int i; // $t0
} // line 25, offset 0x57310
/*
 * Offset 0x57310
 * D:\driver2\game\C\JOB_FX.C (line 588)
 * Stack frame base $sp, size 152
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawExplosion(int time /*stack 0*/, struct VECTOR position /*stack 4*/, int hscale /*stack 20*/, int rscale /*stack 24*/)
{ // line 1, offset 0x57310
  int i; // $t1
  int j; // $s3
  struct POLY_FT4 *poly; // $a2
  struct SVECTOR *src; // $t0
  struct VECTOR v; // stack offset -136
  int rgb; // $s0
  int z; // stack offset -56
  int sf1; // $t0
  int sf2; // $a0
  unsigned long u0; // $s2
  unsigned long u1; // $s1
  unsigned long u2; // $s5
  unsigned long u3; // $s4
  { // line 1, offset 0x57310
    int transparency; // $t2
    int green; // $t1
    int blue; // $v1
  } // line 1, offset 0x57310
  { // line 43, offset 0x57458
    struct MATRIX workmatrix; // stack offset -120
    int sf; // $v0
    int s; // $v1
    int c; // $a3
  } // line 50, offset 0x574ac
  { // line 97, offset 0x57788
    int transparency; // $a0
    int red; // $a1
    int green; // $a2
    int blue; // $v1
  } // line 97, offset 0x57788
  { // line 110, offset 0x5780c
    struct MATRIX workmatrix; // stack offset -88
    int sf; // $v0
    int s; // $v1
    int c; // $a3
  } // line 119, offset 0x57860
} // line 167, offset 0x57b74
/*
 * Offset 0x57B74
 * D:\driver2\game\C\JOB_FX.C (line 110)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitExObjects()
{ // line 2, offset 0x57b74
  int i; // $v1
} // line 11, offset 0x57bb8
/*
 * Offset 0x57BB8
 * D:\driver2\game\C\JOB_FX.C (line 232)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawAllExplosions()
{ // line 2, offset 0x57bb8
  int i; // $s1
  { // line 8, offset 0x57bfc
    int hscale; // $v1
    int rscale; // $a0
  } // line 12, offset 0x57c28
} // line 14, offset 0x57c58
/*
 * Offset 0xE70A0
 * D:\driver2\game\C\LEADAI.C (line 205)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ leadRand()
{
}
/*
 * Offset 0xE7128
 * D:\driver2\game\C\LEADAI.C (line 278)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ InitLead(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0xe7128
  { // line 41, offset 0xe71a0
    struct DRIVER2_STRAIGHT *straight; // $a3
    struct DRIVER2_CURVE *curve; // $t0
    int i; // $a2
    int dx; // $a0
    int dz; // $a1
    int sqrdist; // $v1
    int min; // $t1
  } // line 74, offset 0xe7310
} // line 100, offset 0xe73e8
/*
 * Offset 0xE73E8
 * D:\driver2\game\C\LEADAI.C (line 382)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ LeadUpdateState(struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0xe73e8
  int dif; // $t0
  int avel; // $s1
  { // line 17, offset 0xe7498
    struct VECTOR tmpStart; // stack offset -48
  } // line 30, offset 0xe74ec
  { // line 124, offset 0xe7768
    int dist; // $t1
  } // line 153, offset 0xe792c
  { // line 160, offset 0xe7938
    struct VECTOR pos; // stack offset -32
  } // line 175, offset 0xe7980
} // line 182, offset 0xe7980
/*
 * Offset 0xE7994
 * D:\driver2\game\C\LEADAI.C (line 566)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
unsigned long /*$ra*/ LeadPadResponse(struct _CAR_DATA *cp /*$t0*/)
{ // line 1, offset 0xe7994
  int dif; // $t2
  int avel; // $t1
  unsigned long t0; // $s0
  { // line 34, offset 0xe7a4c
  } // line 60, offset 0xe7b18
  { // line 95, offset 0xe7bc8
    int deltaVel; // $a1
    int deltaAVel; // $a3
    int deltaPos; // $a0
    int deltaTh; // $t2
    int steerDelta; // $a0
  } // line 122, offset 0xe7d50
  { // line 128, offset 0xe7d58
    int diff; // $a0
  } // line 141, offset 0xe7dd4
} // line 149, offset 0xe7de8
/*
 * Offset 0xE7DE8
 * D:\driver2\game\C\LEADAI.C (line 718)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ FakeMotion(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, offset 0xe7de8
  { // line 6, offset 0xe7e40
    struct DRIVER2_STRAIGHT *straight; // $t1
    static int d; // offset 0x0
    static int toGo; // offset 0x4
    static int angle; // offset 0x8
    static int s; // offset 0xc
    static int c; // offset 0x10
    int dx; // $a2
    int dz; // $t3
    int nextJunction; // $t0
    { // line 39, offset 0xe7fa4
      struct DRIVER2_JUNCTION *junction; // $s0
    } // line 39, offset 0xe7fa4
  } // line 60, offset 0xe8010
  { // line 63, offset 0xe8010
    struct DRIVER2_CURVE *curve; // $s0
    int angle; // $a3
    int toGo; // $v0
    int radius; // $a2
    int dx; // $a0
    int dz; // $a1
    int nextJunction; // $a2
    { // line 95, offset 0xe8104
      struct DRIVER2_JUNCTION *junction; // $s0
    } // line 95, offset 0xe8104
    { // line 130, offset 0xe81f0
      struct DRIVER2_JUNCTION *junction; // $s0
    } // line 130, offset 0xe81f0
  } // line 156, offset 0xe82e0
  { // line 159, offset 0xe82e0
    struct DRIVER2_JUNCTION *junction; // $s0
  } // line 167, offset 0xe8338
} // line 170, offset 0xe8338
/*
 * Offset 0xE834C
 * D:\driver2\game\C\LEADAI.C (line 932)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ PosToIndex(int *normal /*$t1*/, int *tangent /*$t4*/, int intention /*$a2*/, struct _CAR_DATA *cp /*$a3*/)
{ // line 1, offset 0xe834c
  { // line 18, offset 0xe8398
    int dist; // $a1
  } // line 26, offset 0xe8420
  { // line 38, offset 0xe84b0
    int w; // $t2
    int w80; // $t0
    int t; // $a1
    int t80; // $a3
    { // line 47, offset 0xe85f0
      int temp; // $v1
    } // line 47, offset 0xe85f0
    { // line 54, offset 0xe8614
      int temp; // $a0
    } // line 56, offset 0xe8614
    { // line 66, offset 0xe865c
    } // line 70, offset 0xe8690
  } // line 113, offset 0xe86b4
} // line 116, offset 0xe86b4
/*
 * Offset 0xE86BC
 * D:\driver2\game\C\LEADAI.C (line 1053)
 * Stack frame base $sp, size 128
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ BlockToMap(struct MAP_DATA *data /*$s3*/)
{ // line 1, offset 0xe86bc
  static int carLength; // offset 0x14
  static int carWidth; // offset 0x18
  static int length; // offset 0x14
  static int width; // offset 0x18
  static int left; // offset 0x1c
  static int right; // offset 0x20
  static int ldist; // offset 0x24
  static int rdist; // offset 0x28
  static struct MAP_DATA newdata; // offset 0x30
  { // line 21, offset 0xe873c
    int dx; // $t4
    int dz; // $t3
    int v; // $v1
    int tangent; // $s0
    int normal; // $s1
  } // line 108, offset 0xe8ab0
  { // line 113, offset 0xe8ab0
    struct DRIVER2_CURVE *curve; // $s1
    int dx; // $s6
    int dz; // $s5
    int v; // $a0
    int angle; // $a2
    int s; // $s4
    int c; // $s2
    int tangent; // $s0
    int normal; // $s1
  } // line 211, offset 0xe8e48
  { // line 218, offset 0xe8e48
    int dx; // $s0
    int dz; // $s2
    int angle; // $s5
    int s; // $t3
    int c; // $t2
    int tangent; // $s1
    int normal; // $s0
    int i; // $s2
    { // line 248, offset 0xe8f7c
      int corners[4][3]; // stack offset -112
      int diff; // $v0
      int overlap; // $s1
      int quad1; // $a1
      int quad2; // $v1
      { // line 297, offset 0xe9184
        int temp; // $v1
      } // line 301, offset 0xe91b0
      { // line 310, offset 0xe921c
        int vx; // $a1
        int vz; // $t0
        int theta; // $v0
      } // line 328, offset 0xe9324
    } // line 329, offset 0xe9324
    { // line 334, offset 0xe9350
      int temp; // $a0
    } // line 354, offset 0xe93f0
  } // line 358, offset 0xe93f0
  { // line 372, offset 0xe9424
    int *nearest; // $s2
    int *furthest; // $s4
    int *ndist; // $s1
    int *fdist; // $s0
    { // line 390, offset 0xe94a4
      int temp; // stack offset -64
      int tdist; // stack offset -60
    } // line 414, offset 0xe9560
  } // line 415, offset 0xe9560
  { // line 429, offset 0xe95a0
    int locall; // stack offset -56
    int localr; // stack offset -48
    int localld; // stack offset -52
    int localrd; // stack offset -44
    { // line 439, offset 0xe9614
      int i; // $a2
    } // line 446, offset 0xe9664
    { // line 446, offset 0xe9664
      int i; // $a0
    } // line 459, offset 0xe96ec
  } // line 460, offset 0xe96ec
  { // line 469, offset 0xe9734
    int tangent; // $a2
    int i; // $a1
  } // line 480, offset 0xe97b0
  { // line 493, offset 0xe97b0
    int dtan; // $a3
    int tangent; // $a2
    int i; // $a1
  } // line 505, offset 0xe9874
} // line 507, offset 0xe9874
/*
 * Offset 0xE98A4
 * D:\driver2\game\C\LEADAI.C (line 1563)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ IsOnMap(int x /*$t0*/, int z /*$a1*/, struct VECTOR *basePos /*$a2*/, int intention /*$s4*/, struct _CAR_DATA *cp /*stack 16*/)
{ // line 1, offset 0xe98a4
  int dx; // $s1
  int dz; // $s2
  { // line 14, offset 0xe9938
    int tangent; // stack offset -44
    int normal; // stack offset -48
  } // line 28, offset 0xe99f4
  { // line 33, offset 0xe99f4
    struct DRIVER2_CURVE *curve; // $s0
    int tangent; // stack offset -36
    int normal; // stack offset -40
  } // line 59, offset 0xe9b20
  { // line 65, offset 0xe9b20
    int tangent; // stack offset -28
    int normal; // stack offset -32
  } // line 79, offset 0xe9b94
} // line 87, offset 0xe9bb8
/*
 * Offset 0xE9BB8
 * D:\driver2\game\C\LEADAI.C (line 1657)
 * Stack frame base $sp, size 368
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ UpdateRoadPosition(struct _CAR_DATA *cp /*$s3*/, struct VECTOR *basePos /*stack 4*/, int intention /*stack 8*/)
{ // line 1, offset 0xe9bb8
  int sindex; // $t0
  int i; // $s0
  int di; // $a2
  struct _CAR_DATA *lcp; // $s0
  int laneAvoid; // stack offset -56
  { // line 23, offset 0xe9c4c
    int cell_x; // $s4
    int x1; // $a0
    { // line 36, offset 0xe9cb0
      int cell_z; // $s0
      int z1; // $s1
      { // line 43, offset 0xe9cfc
        int cbrx; // $a3
        int cbrz; // $a2
        int cbr; // $a0
        { // line 57, offset 0xe9d94
          struct CELL_OBJECT *cop; // $s1
          struct CELL_ITERATOR ci; // stack offset -344
          { // line 64, offset 0xe9db0
            struct COLLISION_PACKET *collide; // $s0
            struct MODEL *model; // $a0
            int num_cb; // $a0
            int box_loop; // $s2
            { // line 82, offset 0xe9e4c
              struct MATRIX *mat; // $a1
              struct VECTOR offset; // stack offset -320
              struct VECTOR vel; // stack offset -304
              struct VECTOR size; // stack offset -288
              struct MAP_DATA data; // stack offset -272
              { // line 96, offset 0xe9ef8
                int sb; // $t0
                int cb; // $a1
                int theta; // $v1
                int xsize; // $a0
                int zsize; // $a3
              } // line 110, offset 0xe9fd8
            } // line 118, offset 0xe9fd8
          } // line 138, offset 0xea068
        } // line 140, offset 0xea088
      } // line 141, offset 0xea088
    } // line 142, offset 0xea098
  } // line 143, offset 0xea0ac
  { // line 157, offset 0xea0cc
    struct SVECTOR *colBox; // $a3
    struct VECTOR pos; // stack offset -344
    struct VECTOR vel; // stack offset -328
    struct VECTOR size; // stack offset -312
    struct MAP_DATA data; // stack offset -296
  } // line 188, offset 0xea260
  { // line 203, offset 0xea2f4
    int left; // $a3
    int right; // $a2
  } // line 232, offset 0xea3d8
  { // line 247, offset 0xea410
    int smallest; // $s1
  } // line 266, offset 0xea4e0
  { // line 274, offset 0xea4ec
    int tmpMap[41]; // stack offset -240
    { // line 280, offset 0xea528
      int count; // $t0
      int j; // $a1
    } // line 287, offset 0xea594
  } // line 289, offset 0xea5c4
  { // line 349, offset 0xea8ac
    int i; // stack offset -68
    int penalty; // $a2
    int left; // stack offset -72
    int right; // stack offset -64
    int centre; // stack offset -60
  } // line 389, offset 0xeaaa0
  { // line 412, offset 0xead80
    int biggest; // $a3
    { // line 433, offset 0xeaeac
    } // line 433, offset 0xeaeac
  } // line 442, offset 0xeaee0
  { // line 446, offset 0xeaee0
    int biggest; // $a1
  } // line 456, offset 0xeaf4c
  { // line 477, offset 0xeaffc
    int smallForward; // $a1
    int smallBack; // $v0
  } // line 494, offset 0xeb060
  { // line 569, offset 0xeb0c4
    struct _CAR_DATA *cp; // $s3
    int sindex; // $a0
    int intention; // stack offset 8
  } // line 569, offset 0xeb1cc
} // line 582, offset 0xeb1cc
/*
 * Offset 0xEB1FC
 * D:\driver2\game\C\LEADAI.C (line 2242)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CheckCurrentRoad(struct _CAR_DATA *cp /*$s3*/)
{ // line 1, offset 0xeb1fc
  static int heading; // offset 0x1c
  int cr; // $s5
  static int jdist; // offset 0x20
  static int nextJunction; // offset 0x50
  static struct VECTOR basePosition; // offset 0x60
  int checkNext; // $s6
  { // line 36, offset 0xeb300
    struct DRIVER2_STRAIGHT *straight; // $t3
    static int d; // offset 0x70
    static int toGo; // offset 0x74
    static int angle; // offset 0x78
    static int s; // offset 0x7c
    static int c; // offset 0x80
    int dx; // $t5
    int dz; // $t6
  } // line 77, offset 0xeb578
  { // line 86, offset 0xeb5c4
    struct DRIVER2_CURVE *curve; // $s2
    static int angle; // offset 0x84
    static int radius; // offset 0x88
    static int dx; // offset 0x8c
    static int dz; // offset 0x90
    static int fixedThresh; // offset 0x94
  } // line 144, offset 0xeb8f8
  { // line 173, offset 0xeb974
    static int diff; // offset 0x98
    { // line 178, offset 0xeb98c
      struct DRIVER2_JUNCTION *junction; // $s0
    } // line 186, offset 0xeb9d4
    { // line 198, offset 0xeba14
      struct DRIVER2_STRAIGHT *straight; // $v1
    } // line 204, offset 0xeba5c
    { // line 207, offset 0xeba5c
      struct DRIVER2_CURVE *curve; // $v1
      static int dx; // offset 0x9c
      static int dz; // offset 0xa0
    } // line 218, offset 0xebae8
    { // line 233, offset 0xebb2c
      struct DRIVER2_STRAIGHT *straight; // $t1
      static int dx; // offset 0xa4
      static int dz; // offset 0xa8
      static int dist; // offset 0xac
      static int offx; // offset 0xb0
      static int offz; // offset 0xb4
    } // line 233, offset 0xebb2c
    { // line 262, offset 0xebc5c
      struct DRIVER2_CURVE *curve; // $s4
      static int angle; // offset 0xb8
      int radius; // $s2
      static int dx; // offset 0xbc
      static int dz; // offset 0xc0
      static int basex; // offset 0xc4
      static int basez; // offset 0xc8
      static int dist; // offset 0xcc
      static int offx; // offset 0xd0
      static int offz; // offset 0xd4
    } // line 302, offset 0xebe44
  } // line 352, offset 0xebfd0
  { // line 387, offset 0xec158
  } // line 388, offset 0xec158
} // line 399, offset 0xec194
/*
 * Offset 0xEC1C4
 * D:\driver2\game\C\LEADAI.C (line 2644)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ SetTarget(struct _CAR_DATA *cp /*$s1*/, int cr /*$a0*/, int heading /*$s4*/, int *nextJunction /*$s3*/)
{ // line 1, offset 0xec1c4
  { // line 13, offset 0xec1fc
    static int dx; // offset 0xd8
    static int dz; // offset 0xdc
  } // line 24, offset 0xec278
  { // line 31, offset 0xec298
    struct DRIVER2_STRAIGHT *straight; // $t5
    int dx; // $a1
    int dz; // $a0
    int rx; // $v1
    int rz; // $a2
    int ux; // $t0
    int uz; // $t4
    int d; // $v1
    int angle; // $v0
    int mul; // $v1
  } // line 51, offset 0xec33c
  { // line 76, offset 0xec444
    struct DRIVER2_CURVE *curve; // $s0
    int angle; // $a1
    int radius; // $a2
  } // line 110, offset 0xec5c4
} // line 116, offset 0xec5c4
/*
 * Offset 0xEC5E4
 * D:\driver2\game\C\LEADAI.C (line 2763)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SelectExit(struct _CAR_DATA *cp /*$s3*/, struct DRIVER2_JUNCTION *junction /*$a3*/)
{ // line 1, offset 0xec5e4
  int onward; // $s1
  int numExits; // $s2
  int el[4][2]; // stack offset -56
  int tmp; // $a1
  int i; // $a2
  int total; // $s0
  { // line 18, offset 0xec6f4
  } // line 25, offset 0xec71c
  { // line 29, offset 0xec79c
  } // line 36, offset 0xec7c8
  { // line 40, offset 0xec844
  } // line 47, offset 0xec870
} // line 80, offset 0xec99c
/*
 * Offset 0xEC99C
 * D:\driver2\game\C\LEADAI.C (line 2848)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
unsigned long /*$ra*/ FreeRoamer(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, offset 0xec99c
  { // line 117, offset 0xeca4c
    struct _CAR_DATA *pCar; // $v0
    { // line 117, offset 0xeca4c
      int seed; // $a0
      { // line 117, offset 0xeca4c
        int i; // $s0
      } // line 118, offset 0xecb04
    } // line 118, offset 0xecb04
  } // line 119, offset 0xecb04
} // line 123, offset 0xecb28
/*
 * Offset 0xECB28
 * D:\driver2\game\C\LEADAI.C (line 2993)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
unsigned long /*$ra*/ hypot(long x /*$s1*/, long y /*$a1*/)
{ // line 1, offset 0xecb28
  { // line 4, offset 0xecb5c
    long t; // $v0
  } // line 4, offset 0xecb64
  { // line 8, offset 0xecbb4
  } // line 13, offset 0xecbe8
} // line 14, offset 0xecbe8
/*
 * Offset 0x57C58
 * D:\driver2\game\C\LOADSAVE.C (line 109)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ SaveConfigData(char *buffer /*$a0*/)
{ // line 1, offset 0x57c58
  struct CONFIG_SAVE_HEADER *header; // $s0
  int i; // $t0
} // line 29, offset 0x57e58
/*
 * Offset 0x57E58
 * D:\driver2\game\C\LOADSAVE.C (line 140)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ LoadConfigData(char *buffer /*$a0*/)
{ // line 1, offset 0x57e58
  struct CONFIG_SAVE_HEADER *header; // $t3
  int i; // $t4
} // line 28, offset 0x5803c
/*
 * Offset 0x5803C
 * D:\driver2\game\C\LOADSAVE.C (line 37)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ CalcReplayDataSize()
{ // line 2, offset 0x5803c
} // line 9, offset 0x5805c
/*
 * Offset 0x5805C
 * D:\driver2\game\C\LOADSAVE.C (line 48)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ SaveReplayData(char *buffer /*$a0*/)
{ // line 2, offset 0x5805c
} // line 6, offset 0x5807c
/*
 * Offset 0x5807C
 * D:\driver2\game\C\LOADSAVE.C (line 56)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ LoadReplayData(char *buffer /*$a0*/)
{
}
/*
 * Offset 0x5809C
 * D:\driver2\game\C\LOADSAVE.C (line 62)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CalcGameDataSize()
{
}
/*
 * Offset 0x580A4
 * D:\driver2\game\C\LOADSAVE.C (line 69)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ SaveGameData(char *buffer /*$s0*/)
{ // line 1, offset 0x580a4
} // line 14, offset 0x58134
/*
 * Offset 0x58134
 * D:\driver2\game\C\LOADSAVE.C (line 85)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ LoadGameData(char *buffer /*$a0*/)
{ // line 1, offset 0x58134
  struct GAME_SAVE_HEADER *header; // $a0
} // line 14, offset 0x581cc
/*
 * Offset 0x581CC
 * D:\driver2\game\C\LOADSAVE.C (line 102)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CalcConfigDataSize()
{
}
/*
 * Offset 0x581D4
 * D:\driver2\game\C\LOADVIEW.C (line 200)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ShowLoading()
{ // line 2, offset 0x581d4
  struct POLY_G4 poly; // stack offset -56
  int col; // $s0
} // line 36, offset 0x58300
/*
 * Offset 0x58314
 * D:\driver2\game\C\LOADVIEW.C (line 268)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ FadeGameScreen(int flag /*$t0*/, int speed /*$t1*/)
{ // line 1, offset 0x58314
  static struct POLY_F4 poly; // offset 0x0
  static struct POLY_FT4 p; // offset 0x20
  int do_fade; // $v0
  { // line 23, offset 0x58354
    int val; // $a3
  } // line 42, offset 0x58430
} // line 47, offset 0x5845c
/*
 * Offset 0x5845C
 * D:\driver2\game\C\LOADVIEW.C (line 327)
 * Stack frame base $sp, size 288
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ ShowLoadingScreen(char *screen_name /*$fp*/, int effect /*$s7*/, int loading_steps /*$a2*/)
{ // line 1, offset 0x5845c
  int fcount; // $s0
  int j; // $s2
  int done; // $fp
  struct RECT dest; // stack offset -264
  struct SPRT prims[4]; // stack offset -256
  struct POLY_FT3 nulls[4]; // stack offset -176
  int fade; // $s5
  int fade_step; // stack offset -48
} // line 142, offset 0x587fc
/*
 * Offset 0x587FC
 * D:\driver2\game\C\LOADVIEW.C (line 527)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupFadePolys()
{ // line 3, offset 0x587fc
  int i; // $a1
} // line 22, offset 0x5888c
/*
 * Offset 0x5888C
 * D:\driver2\game\C\LOADVIEW.C (line 556)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DrawFadePoly()
{ // line 2, offset 0x5888c
  struct POLY_G4 *fl_g4; // $a2
} // line 21, offset 0x58a18
/*
 * Offset 0x58A18
 * D:\driver2\game\C\LOADVIEW.C (line 248)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupScreenFade(int start /*$a0*/, int end /*$a1*/, int speed /*$a2*/)
{
}
/*
 * Offset 0x58A38
 * D:\driver2\game\C\LOADVIEW.C (line 482)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ CloseShutters(int speed /*$s5*/, int width /*$s1*/, int height /*$s4*/)
{ // line 1, offset 0x58a38
  struct POLY_F4 poly[2]; // stack offset -80
  int h; // $s0
  int done; // $s2
} // line 31, offset 0x58b70
/*
 * Offset 0x58B70
 * D:\driver2\game\C\LOADVIEW.C (line 585)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DisplayMissionTitle()
{ // line 2, offset 0x58b70
  { // line 17, offset 0x58bf0
  } // line 21, offset 0x58c20
} // line 37, offset 0x58c70
/*
 * Offset 0x58C70
 * D:\driver2\game\C\MAIN.C (line 2672)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ ProcessLumps(char *lump_ptr /*$s1*/, int lump_size /*$a1*/)
{ // line 1, offset 0x58c70
  int quit; // $s3
  int lump_type; // $v1
  int seg_size; // $s0
  { // line 14, offset 0x58dfc
    { // line 173, offset 0x58fe4
      struct DRIVER2_JUNCTION *dst; // $a0
      unsigned long *src; // $a2
      int i; // $v1
    } // line 186, offset 0x5902c
    { // line 193, offset 0x59034
      struct DRIVER2_JUNCTION *dst; // $a0
      unsigned long *src; // $a2
      int i; // $v1
    } // line 206, offset 0x59080
  } // line 218, offset 0x5908c
} // line 222, offset 0x590b8
/*
 * Offset 0x590B8
 * D:\driver2\game\C\MAIN.C (line 2896)
 * Stack frame base $sp, size 112
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ LoadGameLevel()
{ // line 2, offset 0x590b8
  int sector; // stack offset -32
  int nsectors; // $s1
  char name[64]; // stack offset -96
  char *malloc_lump; // $s2
} // line 71, offset 0x592a0
/*
 * Offset 0x592A0
 * D:\driver2\game\C\MAIN.C (line 3003)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ InitModelNames()
{ // line 2, offset 0x592a0
} // line 64, offset 0x59398
/*
 * Offset 0x59398
 * D:\driver2\game\C\MAIN.C (line 3114)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ GameInit()
{ // line 8, offset 0x59398
  { // line 112, offset 0x59528
  } // line 114, offset 0x5953c
  { // line 149, offset 0x5961c
  } // line 149, offset 0x5961c
  { // line 157, offset 0x59644
  } // line 163, offset 0x5966c
  { // line 191, offset 0x59718
    struct STREAM_SOURCE *pinfo; // $s0
    char padid; // stack offset -48
    int i; // $s2
  } // line 245, offset 0x59874
  { // line 328, offset 0x599ac
    int loop; // $s0
    { // line 331, offset 0x599b4
    } // line 331, offset 0x599b4
  } // line 333, offset 0x599d4
  { // line 341, offset 0x599f4
    int i; // $v1
  } // line 346, offset 0x59a20
  { // line 350, offset 0x59a20
  } // line 361, offset 0x59a20
  { // line 390, offset 0x59a74
  } // line 392, offset 0x59a7c
} // line 395, offset 0x59aac
/*
 * Offset 0x59AAC
 * D:\driver2\game\C\MAIN.C (line 3555)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ StepSim()
{ // line 2, offset 0x59aac
  static unsigned long t0; // offset 0x0
  static char t1; // offset 0x4
  static char t2; // offset 0x5
  static int oldsp; // offset 0x8
  struct _CAR_DATA *lcp; // $s0
  int i; // $s2
  { // line 78, offset 0x59cd8
    int eekTimer; // $s0
    { // line 84, offset 0x59d2c
    } // line 86, offset 0x59d2c
  } // line 90, offset 0x59d88
  { // line 94, offset 0x59dd4
  } // line 98, offset 0x59dd4
  { // line 1, offset 0x5a040
  } // line 1, offset 0x5a040
  { // line 283, offset 0x5a288
    int padsteer; // $a1
    { // line 313, offset 0x5a388
    } // line 317, offset 0x5a3a4
    { // line 324, offset 0x5a3dc
    } // line 324, offset 0x5a3dc
  } // line 324, offset 0x5a3dc
  { // line 331, offset 0x5a3fc
  } // line 333, offset 0x5a430
  { // line 428, offset 0x5a6b8
    int i; // $s1
    int j; // $s0
    static int stupid_logic[4]; // offset 0x0
    { // line 448, offset 0x5a7ac
    } // line 450, offset 0x5a7fc
  } // line 451, offset 0x5a818
  { // line 478, offset 0x5a8fc
  } // line 481, offset 0x5a914
} // line 484, offset 0x5a944
/*
 * Offset 0x5A944
 * D:\driver2\game\C\MAIN.C (line 4046)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ GameLoop()
{ // line 2, offset 0x5a944
  int i; // $s0
  struct RECT dest; // stack offset -24
  { // line 79, offset 0x5aa94
    static struct POLY_FT3 buffer[2]; // offset 0x10
    static struct POLY_FT3 *null; // offset 0xc
  } // line 94, offset 0x5ab00
} // line 142, offset 0x5ab90
/*
 * Offset 0x5AB90
 * D:\driver2\game\C\MAIN.C (line 4196)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ StepGame()
{ // line 2, offset 0x5ab90
  { // line 42, offset 0x5abc8
  } // line 44, offset 0x5abd8
  { // line 56, offset 0x5ac40
    int i; // $a1
  } // line 66, offset 0x5aca4
  { // line 140, offset 0x5ae88
  } // line 149, offset 0x5aeb8
  { // line 165, offset 0x5af28
  } // line 172, offset 0x5af38
  { // line 199, offset 0x5afd4
    int strobe; // $v0
  } // line 202, offset 0x5b020
  { // line 340, offset 0x5b34c
  } // line 342, offset 0x5b384
} // line 351, offset 0x5b3ec
/*
 * Offset 0x5B3EC
 * D:\driver2\game\C\MAIN.C (line 4767)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: ra
 */
int /*$ra*/ main()
{ // line 1, offset 0x5b3ec
  { // line 1, offset 0x5b3ec
    { // line 1, offset 0x5b3ec
      char *PALScreenNames[4]; // stack offset -24
      char *NTSCScreenNames[4]; // stack offset -40
      char *OPMScreenNames[4]; // stack offset -56
    } // line 1, offset 0x5b3ec
  } // line 1, offset 0x5b3ec
} // line 101, offset 0x5b5b4
/*
 * Offset 0x5B5B4
 * D:\driver2\game\C\MAIN.C (line 4893)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ UpdatePlayerInformation()
{ // line 2, offset 0x5b5b4
  struct _CAR_DATA *cp; // $s1
  int count; // $s0
  int scale; // $v1
  int wheel; // $t1
  int wheelsonwater; // $t2
} // line 79, offset 0x5b8f0
/*
 * Offset 0x5B8F0
 * D:\driver2\game\C\MAIN.C (line 5021)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ RenderGame2(int view /*$s3*/)
{ // line 1, offset 0x5b8f0
  int spaceFree; // $a1
  int notInDreaAndStevesEvilLair; // $s0
  { // line 46, offset 0x5ba0c
    int strobe; // $v0
  } // line 49, offset 0x5ba54
  { // line 52, offset 0x5ba54
    int i; // $s1
  } // line 56, offset 0x5baec
  { // line 69, offset 0x5bb4c
    struct POLY_F4 *poly; // $v1
    int col; // $a1
  } // line 92, offset 0x5bc88
  { // line 100, offset 0x5bca8
  } // line 104, offset 0x5bcf0
} // line 111, offset 0x5bd4c
/*
 * Offset 0x5BD4C
 * D:\driver2\game\C\MAIN.C (line 5272)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ InitGameVariables()
{ // line 2, offset 0x5bd4c
} // line 69, offset 0x5bfdc
/*
 * Offset 0x5BFDC
 * D:\driver2\game\C\MAIN.C (line 5345)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ DealWithHorn(char *hr /*$s2*/, int i /*$s1*/)
{ // line 1, offset 0x5bfdc
  struct _CAR_DATA *car; // $s0
  { // line 3, offset 0x5c07c
  } // line 18, offset 0x5c18c
} // line 20, offset 0x5c1bc
/*
 * Offset 0x5C1D4
 * D:\driver2\game\C\MAIN.C (line 5367)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ Havana3DOcclusion(void (*func)() /*$a3*/, int *param /*$fp*/)
{ // line 1, offset 0x5c1d4
  int outside; // $s6
  int otAltered; // $s5
  { // line 12, offset 0x5c270
    int draw; // $s2
    int loop; // $s0
  } // line 106, offset 0x5c47c
} // line 113, offset 0x5c4c0
/*
 * Offset 0x5C4C0
 * D:\driver2\game\C\MAIN.C (line 4549)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DrawGame()
{ // line 2, offset 0x5c4c0
  static unsigned long frame; // offset 0xc8
  { // line 6, offset 0x5c4e8
  } // line 12, offset 0x5c538
  { // line 18, offset 0x5c554
  } // line 28, offset 0x5c5bc
} // line 34, offset 0x5c5dc
/*
 * Offset 0x5C5DC
 * D:\driver2\game\C\MAIN.C (line 4586)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ EndGame(enum GAMEMODE mode /*$a0*/)
{
}
/*
 * Offset 0x5C5F8
 * D:\driver2\game\C\MAIN.C (line 4593)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ EnablePause(enum PAUSEMODE mode /*$a0*/)
{
}
/*
 * Offset 0x5C638
 * D:\driver2\game\C\MAIN.C (line 4602)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ CheckForPause()
{ // line 2, offset 0x5c638
  { // line 1, offset 0x5c64c
  } // line 1, offset 0x5c67c
} // line 16, offset 0x5c6d0
/*
 * Offset 0x5C6D0
 * D:\driver2\game\C\MAIN.C (line 4870)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ FadeScreen(int end_value /*$a1*/)
{ // line 1, offset 0x5c6d0
  int tmp2; // $s1
} // line 18, offset 0x5c748
/*
 * Offset 0x5C748
 * D:\driver2\game\C\MAIN.C (line 5260)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ RenderGame()
{ // line 2, offset 0x5c748
  { // line 2, offset 0x5c748
    { // line 2, offset 0x5c748
      static unsigned long frame; // offset 0xc8
      { // line 1, offset 0x5c77c
      } // line 1, offset 0x5c7cc
      { // line 1, offset 0x5c7e8
      } // line 1, offset 0x5c850
    } // line 1, offset 0x5c850
  } // line 1, offset 0x5c850
} // line 9, offset 0x5c884
/*
 * Offset 0x5C884
 * D:\driver2\game\C\MAIN.C (line 2973)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ ReplayLog_Fnarr_He_Said_Log(int val /*$a0*/)
{
}
/*
 * Offset 0x5C88C
 * D:\driver2\game\C\MAP.C (line 438)
 * Stack frame base $sp, size 120
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CheckUnpackNewRegions()
{ // line 2, offset 0x5c88c
  struct AREA_LOAD_INFO regions_to_unpack[3]; // stack offset -104
  int leftright_unpack; // $a1
  int topbottom_unpack; // $a2
  int num_regions_to_unpack; // $s5
  int x; // $a2
  int z; // $v1
  int loop; // $s6
  int barrel_region; // $s1
  int sortcount; // $s4
  int i; // $v1
  int j; // $a2
  struct SVECTOR sortregions[4]; // stack offset -80
  unsigned short sortorder[4]; // stack offset -48
  int force_load_boundary; // $a0
  { // line 101, offset 0x5ca5c
    int region_to_unpack; // $s0
    struct Spool *spoolptr; // $a1
    { // line 121, offset 0x5cadc
    } // line 141, offset 0x5cb68
  } // line 142, offset 0x5cb68
  { // line 146, offset 0x5cb90
  } // line 156, offset 0x5cbfc
} // line 160, offset 0x5cc68
/*
 * Offset 0x5CC68
 * D:\driver2\game\C\MAP.C (line 612)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ControlMap()
{ // line 2, offset 0x5cc68
  int x; // $a2
  int z; // $a1
  { // line 27, offset 0x5cd4c
  } // line 28, offset 0x5cd54
  { // line 36, offset 0x5cd78
  } // line 37, offset 0x5cd88
} // line 42, offset 0x5cde8
/*
 * Offset 0x5CDE8
 * D:\driver2\game\C\MAP.C (line 677)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ InitMap()
{ // line 2, offset 0x5cde8
  int i; // $s0
  int tpage; // $v0
  char result[8]; // stack offset -24
  { // line 30, offset 0x5ce98
    { // line 39, offset 0x5cef0
      int region; // $a3
      int barrel_region; // $a1
      struct Spool *spoolptr; // $v1
      { // line 49, offset 0x5cf5c
      } // line 55, offset 0x5cf88
    } // line 56, offset 0x5cf88
  } // line 65, offset 0x5cff8
  { // line 1, offset 0x5cff8
  } // line 1, offset 0x5d010
} // line 67, offset 0x5d010
/*
 * Offset 0x5D010
 * D:\driver2\game\C\MAP.C (line 824)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ PVSDecode(char *output /*$s2*/, char *celldata /*$s3*/, unsigned short sz /*$s0*/, int havanaCorruptCellBodge /*$s4*/)
{ // line 1, offset 0x5d010
  char *decodeBuf; // $s1
  { // line 1, offset 0x5d010
    int pixelIndex; // $t0
    int i; // $a0
    int ni; // $a3
    0x8EC spod
    { // line 11, offset 0x5d05c
    } // line 11, offset 0x5d05c
    { // line 18, offset 0x5d0a4
      int symIndex; // $a2
      int sym; // $a0
      { // line 1, offset 0x5d110
        unsigned char *pt; // $v0
      } // line 1, offset 0x5d110
      { // line 1, offset 0x5d124
        unsigned char *pt; // $v0
      } // line 1, offset 0x5d124
    } // line 45, offset 0x5d16c
  } // line 48, offset 0x5d178
  { // line 49, offset 0x5d178
    int i; // $a2
    int j; // $v1
    int sz; // $a3
    char *op; // $a1
  } // line 80, offset 0x5d24c
  { // line 82, offset 0x5d24c
    int i; // $v1
  } // line 87, offset 0x5d28c
} // line 89, offset 0x5d28c
/*
 * Offset 0x5D28C
 * D:\driver2\game\C\MAP.C (line 928)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ GetPVSRegionCell2(int source_region /*$a0*/, int region /*$a1*/, int cell /*$t2*/, char *output /*$a3*/)
{ // line 1, offset 0x5d28c
  char *bp; // $a2
  char *tbp; // $a1
  int j; // $v1
  unsigned short length; // $t0
  { // line 17, offset 0x5d304
    unsigned char *pt; // $a0
  } // line 17, offset 0x5d304
  { // line 17, offset 0x5d304
  } // line 17, offset 0x5d304
  { // line 1, offset 0x5d394
    char *output; // $a0
    { // line 1, offset 0x5d394
      int k; // $v1
    } // line 1, offset 0x5d3c4
  } // line 1, offset 0x5d3c4
} // line 35, offset 0x5d3c4
/*
 * Offset 0x5D3D4
 * D:\driver2\game\C\MAP.C (line 311)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitCellData()
{ // line 2, offset 0x5d3d4
  char *alloclist; // $a2
  int loop; // $v1
} // line 49, offset 0x5d474
/*
 * Offset 0x5D474
 * D:\driver2\game\C\MAP.C (line 289)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
struct MODEL * /*$ra*/ FindModelPtrWithName(char *name /*$s4*/)
{ // line 1, offset 0x5d474
  int dummy; // stack offset -32
  { // line 1, offset 0x5d474
    char *name; // $s4
    int *num; // $s2
    { // line 1, offset 0x5d474
      int count; // $s1
      char *temp; // $s0
    } // line 1, offset 0x5d50c
  } // line 1, offset 0x5d50c
} // line 4, offset 0x5d52c
/*
 * Offset 0x5D52C
 * D:\driver2\game\C\MAP.C (line 295)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ FindModelIdxWithName(char *name /*$s3*/)
{ // line 1, offset 0x5d52c
  int i; // stack offset -32
  { // line 1, offset 0x5d52c
    char *name; // $s3
    int *num; // $s2
    { // line 1, offset 0x5d52c
      int count; // $s1
      char *temp; // $s0
    } // line 1, offset 0x5d5a8
  } // line 1, offset 0x5d5a8
} // line 5, offset 0x5d5c8
/*
 * Offset 0x5D5C8
 * D:\driver2\game\C\MAP.C (line 400)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ PositionVisible(struct VECTOR *pos /*$a0*/)
{ // line 1, offset 0x5d5c8
  int dx; // $a1
  int dz; // $a0
  int cellx; // $v1
  int cellz; // $v0
} // line 20, offset 0x5d684
/*
 * Offset 0x5D684
 * D:\driver2\game\C\MAP.C (line 378)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ newPositionVisible(struct VECTOR *pos /*$a0*/, char *pvs /*$a1*/, int ccx /*$a2*/, int ccz /*$a3*/)
{ // line 1, offset 0x5d684
  int dx; // $a2
  int dz; // $a0
  int cellx; // $v1
  int cellz; // $v0
} // line 20, offset 0x5d72c
/*
 * Offset 0x5D72C
 * D:\driver2\game\C\MAP.C (line 252)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessRoadsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x5D734
 * D:\driver2\game\C\MAP.C (line 247)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessJunctionsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x5D73C
 * D:\driver2\game\C\MAP.C (line 253)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessRoadBoundsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x5D744
 * D:\driver2\game\C\MAP.C (line 254)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessJuncBoundsLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x5D74C
 * D:\driver2\game\C\MAP.C (line 756)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ GetVisSetAtPosition(struct VECTOR *pos /*$a0*/, char *tgt /*$t3*/, int *ccx /*$a1*/, int *ccz /*$a3*/)
{ // line 1, offset 0x5d74c
  int x; // $t2
  int z; // $t1
  int cx; // $t0
  int cz; // $a2
  int rx; // $a3
  int rz; // $a0
  { // line 11, offset 0x5d7d4
    int barrel_region_x; // $v0
    int barrel_region_z; // $a0
  } // line 22, offset 0x5d824
} // line 23, offset 0x5d824
/*
 * Offset 0x5D824
 * D:\driver2\game\C\MAP.C (line 237)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ NewProcessRoadMapLump(struct ROAD_MAP_LUMP_DATA *pRoadMapLumpData /*$s0*/, char *pLumpFile /*$s1*/)
{ // line 1, offset 0x5d824
} // line 6, offset 0x5d87c
/*
 * Offset 0x5D87C
 * D:\driver2\game\C\MC_SND.C (line 88)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
char /*$ra*/ GetMissionSound(char id /*$s1*/)
{ // line 1, offset 0x5d87c
  char c; // $s0
  char start; // $s2
  char end; // $a0
  char rnd; // $t1
} // line 18, offset 0x5d9b8
/*
 * Offset 0x5D9B8
 * D:\driver2\game\C\MC_SND.C (line 187)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DoCutsceneSound()
{ // line 1, offset 0x5d9b8
  { // line 4, offset 0x5da04
    { // line 37, offset 0x5daf0
      { // line 39, offset 0x5db18
        long *here; // $t0
      } // line 41, offset 0x5db54
    } // line 42, offset 0x5db54
    { // line 57, offset 0x5dc04
      { // line 58, offset 0x5dc14
        struct _CAR_DATA *you; // $s0
      } // line 61, offset 0x5dc58
    } // line 63, offset 0x5dc84
  } // line 82, offset 0x5dd68
} // line 84, offset 0x5dd78
/*
 * Offset 0x5DD78
 * D:\driver2\game\C\MC_SND.C (line 279)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ InitializeMissionSound()
{ // line 1, offset 0x5dd78
  int i; // $a1
} // line 29, offset 0x5e088
/*
 * Offset 0x5E088
 * D:\driver2\game\C\MC_SND.C (line 321)
 * Stack frame base $sp, size 128
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DoMissionSound()
{ // line 1, offset 0x5e088
  int i; // $a2
  { // line 79, offset 0x5e24c
    long *pos; // $s5
    long *vel; // $s4
    { // line 83, offset 0x5e2c4
      int chan; // $s1
    } // line 83, offset 0x5e2c4
  } // line 83, offset 0x5e2c4
  { // line 154, offset 0x5e3b0
    struct VECTOR Q[3]; // stack offset -96
    struct VECTOR P; // stack offset -48
  } // line 157, offset 0x5e478
  { // line 159, offset 0x5e48c
    int i; // $s0
  } // line 163, offset 0x5e620
  { // line 202, offset 0x5e758
    struct VECTOR Q[3]; // stack offset -96
    struct VECTOR P; // stack offset -48
  } // line 205, offset 0x5e820
  { // line 207, offset 0x5e834
    int i; // $s0
  } // line 211, offset 0x5e9d0
  { // line 236, offset 0x5eadc
    long V[3]; // stack offset -96
    long *C; // $a1
  } // line 245, offset 0x5ec00
} // line 307, offset 0x5ee68
/*
 * Offset 0x5EE68
 * D:\driver2\game\C\MC_SND.C (line 652)
 * Stack frame base $sp, size 0
 */
char /*$ra*/ SilenceThisCar(int car /*$a1*/)
{
}
/*
 * Offset 0x5F194
 * D:\driver2\game\C\MC_SND.C (line 145)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ RequestXA()
{ // line 1, offset 0x5f194
} // line 12, offset 0x5f21c
/*
 * Offset 0x5F21C
 * D:\driver2\game\C\MC_SND.C (line 164)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ HandleRequestedXA()
{ // line 2, offset 0x5f21c
} // line 6, offset 0x5f28c
/*
 * Offset 0x5F28C
 * D:\driver2\game\C\MC_SND.C (line 176)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitializeCutsceneSound(int cutscene /*$a0*/)
{ // line 1, offset 0x5f28c
  int i; // $a0
} // line 5, offset 0x5f2c4
/*
 * Offset 0x5F2C4
 * D:\driver2\game\C\MC_SND.C (line 636)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetMSoundVar(int var /*$a0*/, struct VECTOR *V /*$a1*/)
{
}
/*
 * Offset 0x5F2FC
 * D:\driver2\game\C\MC_SND.C (line 749)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ AdjustPlayerCarVolume()
{
}
/*
 * Offset 0x5F364
 * D:\driver2\game\C\MDRAW.C (line 58)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ DrawMission()
{ // line 2, offset 0x5f364
  { // line 10, offset 0x5f3f8
    char *string; // $s1
  } // line 27, offset 0x5f480
} // line 66, offset 0x5f5bc
/*
 * Offset 0x5F5D4
 * D:\driver2\game\C\MDRAW.C (line 312)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ DrawWorldTarget(struct _TARGET *target /*$s0*/)
{ // line 1, offset 0x5f5d4
  struct VECTOR tv; // stack offset -32
  int slot; // $v1
  int flags; // $s1
} // line 105, offset 0x5f8b8
/*
 * Offset 0x5F8CC
 * D:\driver2\game\C\MDRAW.C (line 419)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawMultiplayerTarget(struct _TARGET *target /*$s0*/)
{ // line 1, offset 0x5f8cc
  struct VECTOR tv; // stack offset -40
  unsigned char r; // $s3
  unsigned char g; // $s2
  unsigned char b; // $s1
} // line 98, offset 0x5fad4
/*
 * Offset 0x5FAF0
 * D:\driver2\game\C\MDRAW.C (line 126)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ DrawTimer(struct MR_TIMER *timer /*$s1*/)
{ // line 1, offset 0x5faf0
  char string[16]; // stack offset -32
} // line 27, offset 0x5fbd0
/*
 * Offset 0x5FBE4
 * D:\driver2\game\C\MDRAW.C (line 155)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DisplayPlayerPosition()
{ // line 2, offset 0x5fbe4
  char string[32]; // stack offset -40
} // line 6, offset 0x5fc2c
/*
 * Offset 0x5FC2C
 * D:\driver2\game\C\MDRAW.C (line 163)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ DrawMessage(int y /*$s1*/, char *string /*$s0*/)
{ // line 1, offset 0x5fc2c
  { // line 4, offset 0x5fc48
  } // line 13, offset 0x5fc90
} // line 14, offset 0x5fca4
/*
 * Offset 0x5FCA4
 * D:\driver2\game\C\MDRAW.C (line 179)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawWorldTargets()
{ // line 2, offset 0x5fca4
  int i; // $s0
} // line 9, offset 0x5fce4
/*
 * Offset 0x5FCF4
 * D:\driver2\game\C\MDRAW.C (line 190)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawOverheadTargets()
{ // line 2, offset 0x5fcf4
  int i; // $s0
} // line 9, offset 0x5fd34
/*
 * Offset 0x5FD44
 * D:\driver2\game\C\MDRAW.C (line 201)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawFullscreenTargets()
{ // line 2, offset 0x5fd44
  int i; // $s0
} // line 9, offset 0x5fd84
/*
 * Offset 0x5FD94
 * D:\driver2\game\C\MDRAW.C (line 212)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawMultiplayerTargets()
{ // line 2, offset 0x5fd94
  int i; // $s0
} // line 9, offset 0x5fdd4
/*
 * Offset 0x5FDE4
 * D:\driver2\game\C\MDRAW.C (line 230)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawOverheadTarget(struct _TARGET *target /*$s0*/)
{ // line 1, offset 0x5fde4
  struct VECTOR tv; // stack offset -24
} // line 39, offset 0x5feec
/*
 * Offset 0x5FEFC
 * D:\driver2\game\C\MDRAW.C (line 271)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawFullscreenTarget(struct _TARGET *target /*$s0*/)
{ // line 1, offset 0x5fefc
  struct VECTOR tv; // stack offset -24
} // line 39, offset 0x60004
/*
 * Offset 0x60014
 * D:\driver2\game\C\MGENERIC.C (line 109)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ StorePlayerPosition(struct SAVED_PLAYER_POS *data /*$a2*/)
{ // line 1, offset 0x60014
  unsigned short type; // $a0
} // line 39, offset 0x602b0
/*
 * Offset 0x602B0
 * D:\driver2\game\C\MGENERIC.C (line 150)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ RestorePlayerPosition(struct SAVED_PLAYER_POS *data /*$a2*/)
{ // line 1, offset 0x602b0
} // line 28, offset 0x60418
/*
 * Offset 0x60418
 * D:\driver2\game\C\MGENERIC.C (line 180)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ StoreCarPosition(struct _TARGET *target /*$t1*/, struct SAVED_CAR_POS *data /*$t0*/)
{ // line 1, offset 0x60418
  int slot; // $v1
} // line 32, offset 0x60544
/*
 * Offset 0x6054C
 * D:\driver2\game\C\MGENERIC.C (line 214)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ RestoreCarPosition(struct SAVED_CAR_POS *data /*$a3*/)
{
}
/*
 * Offset 0x607A8
 * D:\driver2\game\C\MGENERIC.C (line 62)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ StoreEndData()
{ // line 2, offset 0x607a8
  struct _TARGET *target; // $s0
  struct SAVED_CAR_POS *carpos; // $s2
  int i; // $s1
} // line 22, offset 0x6084c
/*
 * Offset 0x6084C
 * D:\driver2\game\C\MGENERIC.C (line 86)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ RestoreStartData()
{ // line 2, offset 0x6084c
  struct SAVED_CAR_POS *carpos; // $s0
  int i; // $s1
} // line 18, offset 0x608a0
/*
 * Offset 0x608B4
 * D:\driver2\game\C\MISSION.C (line 1347)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ InitialiseMissionDefaults()
{ // line 2, offset 0x608b4
  int i; // $a0
} // line 88, offset 0x60adc
/*
 * Offset 0x60ADC
 * D:\driver2\game\C\MISSION.C (line 1437)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ LoadMission(int missionnum /*$s0*/)
{ // line 1, offset 0x60adc
  char filename[32]; // stack offset -64
  unsigned long header; // stack offset -32
  unsigned long offset; // $s0
  unsigned long length; // $s1
  int size; // $t1
  int i; // $v0
  { // line 240, offset 0x60df0
    int flags; // $a1
    int time; // $a2
  } // line 261, offset 0x60e6c
  { // line 330, offset 0x60fec
    struct _ROUTE_INFO *rinfo; // $s0
  } // line 356, offset 0x6108c
  { // line 393, offset 0x61164
    int num; // $v1
  } // line 404, offset 0x61190
} // line 442, offset 0x612c0
/*
 * Offset 0x612DC
 * D:\driver2\game\C\MISSION.C (line 1881)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ HandleMission()
{
}
/*
 * Offset 0x6150C
 * D:\driver2\game\C\MISSION.C (line 1962)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ HandleTimer(struct MR_TIMER *timer /*$s0*/)
{
}
/*
 * Offset 0x616EC
 * D:\driver2\game\C\MISSION.C (line 2015)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ RegisterChaseHit(int car1 /*$a0*/, int car2 /*$a1*/)
{
}
/*
 * Offset 0x617EC
 * D:\driver2\game\C\MISSION.C (line 2140)
 * Stack frame base $sp, size 720
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ Swap2Cars(int curslot /*$a3*/, int newslot /*$s1*/)
{ // line 1, offset 0x617ec
  struct _CAR_DATA cd; // stack offset -704
  struct _CAR_DATA *cp; // $s0
  int ctrlNodeCurId; // $s4
  int pnodeCurId; // $s5
  int ctrlNodeNewId; // $t2
  int pnodeNewId; // $t3
} // line 81, offset 0x61cc4
/*
 * Offset 0x61CC4
 * D:\driver2\game\C\MISSION.C (line 2234)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ HandleMissionThreads()
{ // line 2, offset 0x61cc4
  struct MR_THREAD *thread; // $s0
  int running; // $s1
  unsigned long value; // $a1
  int i; // $a0
} // line 43, offset 0x61ea4
/*
 * Offset 0x61EA4
 * D:\driver2\game\C\MISSION.C (line 2279)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ MRCommand(struct MR_THREAD *thread /*$s1*/, unsigned long cmd /*$a1*/)
{ // line 1, offset 0x61ea4
  unsigned long val1; // $s0
  unsigned long val2; // $s0
} // line 160, offset 0x624d8
/*
 * Offset 0x624D8
 * D:\driver2\game\C\MISSION.C (line 2701)
 * Stack frame base $sp, size 120
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ MRProcessTarget(struct MR_THREAD *thread /*$s7*/, struct _TARGET *target /*$s5*/)
{ // line 1, offset 0x624d8
  struct VECTOR tv; // stack offset -96
  struct VECTOR pv; // stack offset -80
  int ret; // $fp
  unsigned long dist; // $s6
  int slot; // stack offset -48
  int message; // $v0
  int sample; // $a0
  { // line 158, offset 0x62a24
    unsigned long message; // $s1
    unsigned long timer; // $s0
    unsigned long delay; // $s2
  } // line 173, offset 0x62a94
  { // line 233, offset 0x62c64
    int direction; // $s0
    long pos[4]; // stack offset -64
    int *inform; // $s4
    struct _CAR_DATA *cp; // $v0
  } // line 239, offset 0x62c64
  { // line 368, offset 0x63090
    long pos[4]; // stack offset -64
  } // line 375, offset 0x630f8
  { // line 403, offset 0x63204
  } // line 403, offset 0x63204
  { // line 434, offset 0x632bc
  } // line 434, offset 0x632bc
  { // line 457, offset 0x63380
  } // line 457, offset 0x63380
} // line 593, offset 0x63790
/*
 * Offset 0x63790
 * D:\driver2\game\C\MISSION.C (line 3311)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ MRCreateCar(struct _TARGET *target /*$s1*/)
{ // line 1, offset 0x63790
  long pos[4]; // stack offset -64
  int actAsCop; // $s2
  int damaged; // $s7
  int model; // $s4
  int palette; // $s5
  int dir; // $s3
  int rot; // $a2
  int id; // $s0
  char playerid; // stack offset -48
} // line 79, offset 0x63a08
/*
 * Offset 0x63A08
 * D:\driver2\game\C\MISSION.C (line 3398)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ PreProcessTargets()
{ // line 2, offset 0x63a08
  struct _TARGET *target; // $s0
  int i; // $s1
} // line 52, offset 0x63be0
/*
 * Offset 0x63BE0
 * D:\driver2\game\C\MISSION.C (line 3469)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ HandleGameOver()
{ // line 3, offset 0x63be0
  { // line 5, offset 0x63c20
    struct _PLAYER *lp; // $s0
    struct _CAR_DATA *cp; // $a2
    int i; // $s2
    int playersdead; // $s3
    { // line 41, offset 0x63d4c
      int surfInd; // $v1
    } // line 53, offset 0x63de4
  } // line 96, offset 0x63f4c
} // line 120, offset 0x63fec
/*
 * Offset 0x63FEC
 * D:\driver2\game\C\MISSION.C (line 3623)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetMissionComplete()
{
}
/*
 * Offset 0x64210
 * D:\driver2\game\C\MISSION.C (line 3716)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ActivateNextFlag()
{ // line 2, offset 0x64210
  int i; // $a3
  int j; // $a1
} // line 23, offset 0x642d0
/*
 * Offset 0x642D0
 * D:\driver2\game\C\MISSION.C (line 2046)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ PauseMissionTimer(int pause /*$a0*/)
{
}
/*
 * Offset 0x64310
 * D:\driver2\game\C\MISSION.C (line 2060)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetMissionMessage(char *message /*$a0*/, int priority /*$a1*/, int seconds /*$a2*/)
{ // line 1, offset 0x64310
  int i; // $a3
} // line 19, offset 0x643a8
/*
 * Offset 0x643B0
 * D:\driver2\game\C\MISSION.C (line 2081)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetPlayerMessage(int player /*$a0*/, char *message /*$a1*/, int priority /*$a2*/, int seconds /*$a3*/)
{
}
/*
 * Offset 0x6442C
 * D:\driver2\game\C\MISSION.C (line 2094)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ TargetComplete(struct _TARGET *target /*$a0*/, int player /*$a1*/)
{ // line 1, offset 0x6442c
  unsigned long complete; // $a0
} // line 21, offset 0x64470
/*
 * Offset 0x64470
 * D:\driver2\game\C\MISSION.C (line 2117)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ TargetActive(struct _TARGET *target /*$a0*/, int player /*$a1*/)
{ // line 1, offset 0x64470
  unsigned long active; // $a0
} // line 21, offset 0x644b4
/*
 * Offset 0x644B4
 * D:\driver2\game\C\MISSION.C (line 2223)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetConfusedCar(int slot /*$a0*/)
{
}
/*
 * Offset 0x64500
 * D:\driver2\game\C\MISSION.C (line 2441)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ MROperator(struct MR_THREAD *thread /*$s3*/, unsigned long op /*$s0*/)
{ // line 1, offset 0x64500
  int result; // $s2
  long val1; // $s1
  long val2; // $a1
} // line 51, offset 0x64614
/*
 * Offset 0x64614
 * D:\driver2\game\C\MISSION.C (line 2494)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ MRFunction(struct MR_THREAD *thread /*$s0*/, unsigned long fnc /*$a1*/)
{ // line 1, offset 0x64614
} // line 17, offset 0x6467c
/*
 * Offset 0x6467C
 * D:\driver2\game\C\MISSION.C (line 2514)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MRInitialiseThread(struct MR_THREAD *thread /*$a0*/, unsigned long *pc /*$a1*/, unsigned char player /*$a2*/)
{
}
/*
 * Offset 0x64698
 * D:\driver2\game\C\MISSION.C (line 2526)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ MRStartThread(struct MR_THREAD *callingthread /*$t0*/, unsigned long addr /*$a1*/, unsigned char player /*$a2*/)
{ // line 1, offset 0x64698
  int i; // $v1
} // line 17, offset 0x646e8
/*
 * Offset 0x646F8
 * D:\driver2\game\C\MISSION.C (line 2545)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ MRStopThread(struct MR_THREAD *thread /*$a0*/)
{
}
/*
 * Offset 0x64704
 * D:\driver2\game\C\MISSION.C (line 2551)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ MRCommitThreadGenocide()
{ // line 2, offset 0x64704
  int i; // $s0
} // line 6, offset 0x64748
/*
 * Offset 0x64748
 * D:\driver2\game\C\MISSION.C (line 2560)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ MRJump(struct MR_THREAD *thread /*$a2*/, long jump /*$a1*/)
{
}
/*
 * Offset 0x64794
 * D:\driver2\game\C\MISSION.C (line 2575)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MRPush(struct MR_THREAD *thread /*$a0*/, long value /*$a1*/)
{
}
/*
 * Offset 0x647AC
 * D:\driver2\game\C\MISSION.C (line 2585)
 * Stack frame base $sp, size 0
 */
long /*$ra*/ MRPop(struct MR_THREAD *thread /*$a0*/)
{ // line 1, offset 0x647ac
} // line 12, offset 0x647c8
/*
 * Offset 0x647C8
 * D:\driver2\game\C\MISSION.C (line 2600)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
long /*$ra*/ MRGetParam(struct MR_THREAD *thread /*$s0*/)
{ // line 1, offset 0x647c8
  long value; // $a1
} // line 20, offset 0x64834
/*
 * Offset 0x64834
 * D:\driver2\game\C\MISSION.C (line 2622)
 * Stack frame base $sp, size 0
 */
long /*$ra*/ MRGetVariable(struct MR_THREAD *thread /*$a2*/, unsigned long var /*$a1*/)
{
}
/*
 * Offset 0x64918
 * D:\driver2\game\C\MISSION.C (line 2648)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MRSetVariable(struct MR_THREAD *thread /*$v1*/, unsigned long var /*$a1*/, long value /*$a2*/)
{
}
/*
 * Offset 0x64A4C
 * D:\driver2\game\C\MISSION.C (line 3296)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ MRRequestCar(struct _TARGET *target /*$a0*/)
{
}
/*
 * Offset 0x64A8C
 * D:\driver2\game\C\MISSION.C (line 3305)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ MRHandleCarRequests()
{
}
/*
 * Offset 0x64AB8
 * D:\driver2\game\C\MISSION.C (line 3392)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MRCancelCarRequest(struct _TARGET *target /*$a0*/)
{
}
/*
 * Offset 0x64ADC
 * D:\driver2\game\C\MISSION.C (line 3452)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ Handle321Go()
{ // line 2, offset 0x64adc
} // line 15, offset 0x64b38
/*
 * Offset 0x64B38
 * D:\driver2\game\C\MISSION.C (line 3591)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ CompleteAllActiveTargets(int player /*$a0*/)
{ // line 2, offset 0x64b38
  int i; // $a1
  int flag1; // $a3
  int flag2; // $a2
} // line 30, offset 0x64ba0
/*
 * Offset 0x64BA0
 * D:\driver2\game\C\MISSION.C (line 3684)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetMissionFailed(enum FAIL_REASON reason /*$a0*/)
{
}
/*
 * Offset 0x64C40
 * D:\driver2\game\C\MISSION.C (line 3704)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetMissionOver(enum PAUSEMODE mode /*$a0*/)
{
}
/*
 * Offset 0x64C8C
 * D:\driver2\game\C\MISSION.C (line 3760)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CalcLapTime(int player /*$a0*/, int time /*$a1*/, int lap /*$a2*/)
{ // line 1, offset 0x64c8c
  int i; // $a2
  int ptime; // $a3
} // line 8, offset 0x64cc8
/*
 * Offset 0x64CC8
 * D:\driver2\game\C\MISSION.C (line 3770)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ SetCarToBeStolen(struct _TARGET *target /*$s0*/, int player /*$s1*/)
{
}
/*
 * Offset 0x64D38
 * D:\driver2\game\C\MISSION.C (line 3781)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MakePhantomCarEqualPlayerCar()
{
}
/*
 * Offset 0x64D64
 * D:\driver2\game\C\MODELS.C (line 33)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessMDSLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{ // line 1, offset 0x64d64
  int i; // $a2
  int size; // $v0
  int modelamt; // $a3
  char *mdsfile; // $a0
  struct MODEL *model; // $a0
  struct MODEL *parentmodel; // $a1
} // line 61, offset 0x64ed4
/*
 * Offset 0x64ED4
 * D:\driver2\game\C\MODELS.C (line 212)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ ProcessCarModelLump(char *lump_ptr /*$s2*/, int lump_size /*$a1*/)
{ // line 2, offset 0x64ed4
  int offset; // $a0
  int i; // $s3
  int car_model; // $a0
  int specMemReq; // $s4
  { // line 19, offset 0x64f18
    struct MODEL *model; // $v0
    int mem; // $a1
  } // line 74, offset 0x64ff0
} // line 136, offset 0x6519c
/*
 * Offset 0x6519C
 * D:\driver2\game\C\MODELS.C (line 391)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
struct MODEL * /*$ra*/ GetCarModel(char *src /*$s2*/, char **dest /*$s1*/, int KeepNormals /*$s3*/)
{ // line 1, offset 0x6519c
  struct MODEL *model; // $s0
  int size; // $a2
  char *mem; // $v1
  { // line 28, offset 0x65204
  } // line 38, offset 0x65254
} // line 41, offset 0x65274
/*
 * Offset 0x65274
 * D:\driver2\game\C\MOTION_C.C (line 978)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawBodySprite(int boneId /*$s1*/, long v1 /*$a1*/, long v2 /*$a2*/, int sz /*$s7*/, int sy /*stack 16*/)
{ // line 1, offset 0x65274
  struct TEXTURE_DETAILS *body_texture; // $s2
  int x0; // $s5
  int x1; // $s6
  int y0; // $fp
  int y1; // stack offset -48
  int dx1; // $s4
  int dy1; // $s3
  int z; // $a3
  int z2; // $a3
  int dx2; // $t5
  int dy2; // $t3
  int width; // $t0
  int sort_fix; // $a3
  int angle; // $t3
  int c; // $t0
  int s; // $a2
  int clut; // $a2
  int tpage; // $t0
  struct POLY_FT4 *prims; // $t2
  int z1; // stack offset -44
  int pal; // $v1
  { // line 125, offset 0x65618
    int tp; // $v1
  } // line 155, offset 0x656b4
} // line 231, offset 0x659b4
/*
 * Offset 0x659B4
 * D:\driver2\game\C\MOTION_C.C (line 1289)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ StoreVertexLists()
{ // line 2, offset 0x659b4
  int i; // $t1
  int j; // $a3
  int numVerts; // $t3
  struct MODEL *pModel; // $t0
  struct SVECTOR *pVerts; // $a2
  int counter; // $t4
  struct BONE *pBone; // $a0
} // line 57, offset 0x65b40
/*
 * Offset 0x65B40
 * D:\driver2\game\C\MOTION_C.C (line 1355)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupTannerSkeleton()
{ // line 2, offset 0x65b40
  int i; // $t1
  struct BONE *pBone; // $a3
  char *pC; // $v0
  struct SVECTOR *store; // $t4
  struct SVECTOR_NOPAD *pSVNP; // $v1
} // line 58, offset 0x65d40
/*
 * Offset 0x65D40
 * D:\driver2\game\C\MOTION_C.C (line 1421)
 * Stack frame base $sp, size 152
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ newShowTanner()
{ // line 2, offset 0x65d40
  struct VECTOR *playerPos; // $a2
  struct VECTOR *camPos; // $a1
  struct VECTOR *vJPos; // $s1
  struct VECTOR v; // stack offset -128
  struct MODEL *pModel; // $t0
  struct SVECTOR *mVerts; // $a1
  int i; // $s2
  int j; // $a3
  int c; // $a3
  int id; // $a2
  int limbs; // $a0
  struct BONE *pBone; // $s0
  int lval; // $t1
  { // line 109, offset 0x66108
    struct BONE *pBone; // $s0
    struct VECTOR *v1; // $a2
    struct VECTOR *v2; // $a1
    { // line 109, offset 0x66108
      struct SVECTOR *data; // $t1
      long t1; // stack offset -92
      long t0; // stack offset -96
      int z2; // stack offset -80
      int z1; // stack offset -84
      int z; // stack offset -88
    } // line 109, offset 0x6622c
  } // line 109, offset 0x6622c
  { // line 115, offset 0x66260
    struct BONE *pBone; // $s0
    struct VECTOR *v1; // $a0
    struct VECTOR *v2; // $a2
    { // line 115, offset 0x66260
      struct SVECTOR *data; // $t0
      long t1; // stack offset -72
      long t0; // stack offset -76
      int z2; // stack offset -60
      int z1; // stack offset -64
      int z; // stack offset -68
    } // line 115, offset 0x66260
  } // line 115, offset 0x66260
  { // line 121, offset 0x66398
    struct SVECTOR v1; // stack offset -112
    struct SVECTOR v2; // stack offset -104
  } // line 123, offset 0x66398
  { // line 148, offset 0x664f4
    struct BONE *pBone; // $s0
    struct VECTOR *v1; // $a2
    struct VECTOR *v2; // $a1
    { // line 148, offset 0x664f4
      struct SVECTOR *data; // $t1
      long t1; // stack offset -52
      long t0; // stack offset -56
      int z2; // stack offset -40
      int z1; // stack offset -44
      int z; // stack offset -48
    } // line 148, offset 0x664f4
  } // line 148, offset 0x664f4
  { // line 154, offset 0x66630
    int bias; // $a3
  } // line 167, offset 0x6665c
} // line 178, offset 0x666b0
/*
 * Offset 0x666B0
 * D:\driver2\game\C\MOTION_C.C (line 1606)
 * Stack frame base $sp, size 1104
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ newRotateBones(struct BONE *poBone /*$a0*/)
{ // line 2, offset 0x666b0
  struct MATRIX mStore[32]; // stack offset -1088
  struct MATRIX *pMatrix; // $s2
  struct MATRIX *oMatrix; // $s5
  struct SVECTOR *svBone; // $s6
  struct VECTOR *vBoneRotated; // $s3
  struct BONE *pBone; // $s1
  int id; // $s0
  struct SVECTOR *pVerts; // $a3
  struct SVECTOR *pmVerts; // $s0
  int numVerts; // $t0
  struct MODEL *pModel; // $v0
  int i; // $a2
  struct SVECTOR *pD; // $a0
  int c; // $s4
  int j; // $a1
  struct VECTOR sv; // stack offset -64
  { // line 3, offset 0x666b0
    int cx; // $t2
    int sx; // $a3
    int cy; // $a0
    int sy; // $t0
    int cz; // $t3
    int sz; // $t6
    int stmp; // $v0
  } // line 3, offset 0x666b0
} // line 160, offset 0x67020
/*
 * Offset 0x67020
 * D:\driver2\game\C\MOTION_C.C (line 1774)
 * Stack frame base $sp, size 0
 */
struct SVECTOR * /*$ra*/ GetModelVertPtr(int boneId /*$a1*/, int modelType /*$a1*/)
{
}
/*
 * Offset 0x67134
 * D:\driver2\game\C\MOTION_C.C (line 1834)
 * Stack frame base $sp, size 184
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawCiv(struct PEDESTRIAN *pPed /*$fp*/)
{ // line 1, offset 0x67134
  int i; // $s5
  struct DVECTOR *outpoints; // $t9
  long *outlongs; // $s5
  struct SVECTOR *psrLerpData; // $t8
  long *zbuff; // $s4
  struct SVECTOR *pLerpData; // $s0
  struct SVECTOR pos; // stack offset -160
  struct VECTOR pos1; // stack offset -152
  struct SVECTOR *vert1; // $a1
  struct SVECTOR *vert2; // $a0
  struct SVECTOR temp1; // stack offset -136
  struct SVECTOR temp2; // stack offset -128
  int cnt3; // $a2
  int bHeadModel; // stack offset -56
  int shift; // $t0
  int frame; // $a2
  struct MATRIX workmatrix; // stack offset -120
  int j; // $s7
  { // line 74, offset 0x67320
    int cx; // $v1
    int sx; // $a0
    int cy; // $a1
    int sy; // $t0
    int cz; // $t3
    int sz; // $t6
    int stmp; // $t7
  } // line 74, offset 0x67320
  { // line 130, offset 0x67828
    struct SVECTOR sV; // stack offset -88
    struct SVECTOR sV2; // stack offset -80
    struct VECTOR v; // stack offset -72
  } // line 142, offset 0x67864
  { // line 151, offset 0x67864
    struct CVECTOR cv; // stack offset -88
    struct VECTOR pos; // stack offset -80
    int phase; // $s0
  } // line 164, offset 0x67908
} // line 167, offset 0x67908
/*
 * Offset 0x67938
 * D:\driver2\game\C\MOTION_C.C (line 2041)
 * Stack frame base $sp, size 128
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawTanner(struct PEDESTRIAN *pPed /*$s2*/)
{ // line 1, offset 0x67938
  struct VECTOR v; // stack offset -112
  struct CVECTOR cV; // stack offset -96
  struct MATRIX mRotStore; // stack offset -88
  struct MATRIX iMatrix; // stack offset -56
  { // line 1, offset 0x67938
  } // line 20, offset 0x67a48
  { // line 26, offset 0x67a48
    int cx; // $a2
    int sx; // $t0
    int cy; // $a0
    int sy; // $t2
    int cz; // $t5
    int sz; // $s0
    int stmp; // $v1
  } // line 26, offset 0x67a48
} // line 72, offset 0x67dac
/*
 * Offset 0x67DAC
 * D:\driver2\game\C\MOTION_C.C (line 2120)
 * Stack frame base $sp, size 144
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ DrawCharacter(struct PEDESTRIAN *pPed /*$s1*/)
{ // line 1, offset 0x67dac
  struct MATRIX mRotStore; // stack offset -128
  struct MATRIX iMatrix; // stack offset -96
  struct CVECTOR cV; // stack offset -64
  struct VECTOR v; // stack offset -56
  { // line 1, offset 0x67dac
    int cx; // $t0
    int sx; // $a3
    int cy; // $a0
    int sy; // $t2
    int cz; // $a2
    int sz; // $t7
    int stmp; // $v1
  } // line 1, offset 0x67dac
  { // line 55, offset 0x6819c
    struct CVECTOR cv; // stack offset -40
    struct VECTOR pos; // stack offset -32
    int phase; // $s0
  } // line 69, offset 0x68238
} // line 73, offset 0x68254
/*
 * Offset 0x68254
 * D:\driver2\game\C\MOTION_C.C (line 2201)
 * Stack frame base $sp, size 8
 */
void /*$ra*/ InitTannerShadow()
{ // line 2, offset 0x68254
  struct CVECTOR cV; // stack offset -8
  int i; // $a3
} // line 46, offset 0x683c0
/*
 * Offset 0x683C0
 * D:\driver2\game\C\MOTION_C.C (line 2258)
 * Stack frame base $sp, size 296
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ TannerShadow(struct VECTOR *pPedPos /*$s6*/, struct SVECTOR *pLightPos /*$s7*/, struct CVECTOR *col /*$a2*/, short angle /*$a3*/)
{ // line 1, offset 0x683c0
  int z; // $a1
  int z0; // stack offset -72
  int z1; // stack offset -68
  int z2; // stack offset -64
  int z3; // stack offset -60
  struct SVECTOR vert[4]; // stack offset -272
  struct VECTOR d; // stack offset -240
  struct DR_ENV *pDE; // $s3
  struct DRAWENV drEnv; // stack offset -224
  struct VECTOR cp; // stack offset -128
  struct SVECTOR ca; // stack offset -112
  struct VECTOR v1; // stack offset -104
  int i; // $s4
  struct VECTOR myVector; // stack offset -88
  int avalue2; // $v0
  int w; // $v1
  { // line 117, offset 0x68880
  } // line 117, offset 0x68880
} // line 176, offset 0x68b94
/*
 * Offset 0x68B94
 * D:\driver2\game\C\MOTION_C.C (line 2442)
 * Stack frame base $sp, size 200
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ DoCivHead(struct SVECTOR *vert1 /*$s1*/, struct SVECTOR *vert2 /*$s3*/)
{ // line 1, offset 0x68b94
  struct VECTOR headpos; // stack offset -184
  struct SVECTOR final_rotation; // stack offset -168
  struct SVECTOR spos1; // stack offset -160
  struct MODEL *model; // $s5
  struct MATRIX work2matrix; // stack offset -152
  struct MATRIX mRotStore; // stack offset -120
  struct VECTOR pos1; // stack offset -88
  int pal; // $v1
  int ci; // $s6
  { // line 53, offset 0x68da0
    int cx; // $v1
    int sx; // $a0
    int cy; // $a1
    int sy; // $t0
    int cz; // $t3
    int sz; // $t6
    int stmp; // $a3
  } // line 53, offset 0x68da0
  { // line 65, offset 0x69000
    int cx; // $v1
    int sx; // $t3
    int cy; // $t1
    int sy; // $a3
    int stmp; // $v0
  } // line 65, offset 0x69000
  { // line 93, offset 0x692dc
    struct MATRIX comb; // stack offset -72
  } // line 95, offset 0x692dc
} // line 112, offset 0x69474
/*
 * Offset 0x694A0
 * D:\driver2\game\C\MOTION_C.C (line 2562)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawObject(struct MODEL *model /*$t8*/, struct MATRIX *matrix /*$a1*/, struct VECTOR *pos /*$a2*/, int z_correct /*$a3*/)
{ // line 1, offset 0x694a0
  struct DVECTOR *outpoints; // $t7
  short *zbuff; // $t5
  struct SVECTOR *verts; // $t6
  char *polys; // $s0
  int cnt3; // $t1
  int i; // $s1
  int z0; // stack offset -40
  int z1; // stack offset -36
  int z2; // stack offset -32
  long *outlongs; // $s2
  int z; // stack offset -28
  { // line 92, offset 0x6983c
  } // line 101, offset 0x698a8
} // line 121, offset 0x698dc
/*
 * Offset 0x698DC
 * D:\driver2\game\C\MOTION_C.C (line 2690)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ wjmDraw3()
{ // line 2, offset 0x698dc
  struct POLYFT3 *src; // $a3
  short *zbuff; // $t2
  long *outlongs; // $a2
  struct POLY_FT3 *prims; // $t1
  unsigned long clut; // $t0
  unsigned long tpage; // $a1
  int z; // $a2
} // line 34, offset 0x69aa0
/*
 * Offset 0x69AA0
 * D:\driver2\game\C\MOTION_C.C (line 853)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ProcessMotionLump(char *lump_ptr /*$a0*/, int lump_size /*$s0*/)
{
}
/*
 * Offset 0x69B20
 * D:\driver2\game\C\MOTION_C.C (line 944)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupPedMotionData(struct PEDESTRIAN *pPed /*$a0*/)
{
}
/*
 * Offset 0x69B40
 * D:\driver2\game\C\MOTION_C.C (line 2011)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetSkelModelPointers(int type /*$a0*/)
{
}
/*
 * Offset 0x69BD4
 * D:\driver2\game\C\MOTION_C.C (line 955)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupPedestrian(struct PEDESTRIAN *pedptr /*$a0*/)
{
}
/*
 * Offset 0x69C0C
 * D:\driver2\game\C\OBJCOLL.C (line 63)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
char /*$ra*/ CellEmpty(struct VECTOR *pPosition /*$s1*/, int radius /*$s2*/)
{ // line 1, offset 0x69c0c
  struct CELL_ITERATOR ci; // stack offset -48
  int cell_x; // $a0
  struct CELL_OBJECT *pCellObject; // $a2
  struct MODEL *pModel; // $a3
  { // line 37, offset 0x69cc8
    int sphere_sq; // $v0
    int xd; // $t5
    int zd; // $t4
    { // line 51, offset 0x69d2c
      int box_loop; // $t3
      int num_cb; // $t6
      struct COLLISION_PACKET *collide; // $t0
      { // line 56, offset 0x69d50
        unsigned int zs; // $t2
        unsigned int xs; // $t1
        int cs; // $a2
        int sn; // $a0
      } // line 75, offset 0x69e30
    } // line 76, offset 0x69e40
  } // line 78, offset 0x69e40
} // line 90, offset 0x69e84
/*
 * Offset 0x69E84
 * D:\driver2\game\C\OBJCOLL.C (line 217)
 * Stack frame base $sp, size 24
 */
int /*$ra*/ RaySlabsIntersection(struct tRay *ray /*$t5*/, struct tAABB *bbox /*$t4*/)
{ // line 1, offset 0x69e84
  int i; // $t1
  struct tRange inside; // stack offset -24
  { // line 9, offset 0x69ea8
    struct tRange cabbage; // stack offset -16
    struct tRange scaledCabbage; // stack offset -8
    int dir; // $a2
  } // line 36, offset 0x69ffc
} // line 38, offset 0x6a01c
/*
 * Offset 0x6A01C
 * D:\driver2\game\C\OBJCOLL.C (line 259)
 * Stack frame base $sp, size 200
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
char /*$ra*/ lineClear(struct VECTOR *v1 /*stack 0*/, struct VECTOR *v2 /*stack 4*/)
{ // line 1, offset 0x6a01c
  int we; // stack offset -56
  int ocx; // $t2
  int ocz; // $t3
  struct VECTOR pos; // stack offset -184
  struct VECTOR va; // stack offset -168
  struct VECTOR vb; // stack offset -152
  { // line 20, offset 0x6a0dc
    int cell_x; // $fp
    int cell_z; // $s7
    struct CELL_ITERATOR ci; // stack offset -136
    struct CELL_OBJECT *pCellObject; // $s4
    { // line 40, offset 0x6a19c
      struct MODEL *pModel; // $a1
      { // line 48, offset 0x6a1d8
        int sphere_sq; // $v0
        int xd; // $a0
        int zd; // $v1
        { // line 59, offset 0x6a23c
          int box_loop; // $s5
          int num_cb; // $s6
          struct COLLISION_PACKET *collide; // $s3
          { // line 64, offset 0x6a258
            struct MATRIX *mat; // $a0
            int cx; // $v1
            int cy; // $a2
            int cz; // $v0
            int cs; // $t1
            int sn; // $t5
            { // line 64, offset 0x6a258
              struct tRay ray; // stack offset -112
              struct tAABB box; // stack offset -80
            } // line 88, offset 0x6a47c
          } // line 89, offset 0x6a47c
        } // line 90, offset 0x6a48c
      } // line 92, offset 0x6a48c
    } // line 93, offset 0x6a48c
  } // line 96, offset 0x6a4ac
} // line 101, offset 0x6a500
/*
 * Offset 0x6A500
 * D:\driver2\game\C\OBJCOLL.C (line 391)
 * Stack frame base $sp, size 88
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ CollisionCopList(struct XZPAIR *pos /*$a0*/, int *count /*$s0*/)
{ // line 1, offset 0x6a500
  static struct XZPAIR initial; // offset 0x0
  { // line 11, offset 0x6a550
    struct XZPAIR cell; // stack offset -72
    int i; // $a0
    int j; // $t1
    { // line 20, offset 0x6a570
      struct CELL_ITERATOR ci; // stack offset -64
      struct XZPAIR cbr; // stack offset -40
      int barrelRegion; // $v0
      struct CELL_OBJECT *cop; // $a0
    } // line 38, offset 0x6a660
  } // line 40, offset 0x6a690
} // line 41, offset 0x6a6b4
/*
 * Offset 0x6A6B4
 * D:\driver2\game\C\OBJCOLL.C (line 439)
 * Stack frame base $sp, size 168
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CheckScenaryCollisions(struct _CAR_DATA *cp /*$s7*/)
{ // line 1, offset 0x6a6b4
  struct MODEL *model; // stack offset -76
  struct CELL_OBJECT *cop; // $s5
  struct VECTOR player_pos; // stack offset -152
  struct COLLISION_PACKET *collide; // $s1
  int cell_x; // $a0
  int xd; // $v1
  int zd; // $a0
  int num_cb; // stack offset -72
  int box_loop; // $s6
  int sphere_sq; // $v0
  int x1; // stack offset -68
  struct BUILDING_BOX bbox; // stack offset -136
  int mdcount; // stack offset -80
  int coll_test_count; // $t0
  struct XZPAIR box; // stack offset -104
  int lbody; // stack offset -64
  int extraDist; // stack offset -60
  { // line 80, offset 0x6a99c
    struct BUILDING_BOX *pbox; // $s4
    struct MATRIX *mat; // $a1
    struct VECTOR offset; // stack offset -96
  } // line 152, offset 0x6adb0
} // line 158, offset 0x6adf4
/*
 * Offset 0x6AE24
 * D:\driver2\game\C\OBJCOLL.C (line 609)
 * Stack frame base $sp, size 128
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ QuickBuildingCollisionCheck(struct VECTOR *pPos /*$s5*/, int dir /*stack 4*/, int l /*stack 8*/, int w /*$fp*/, int extra /*stack 16*/)
{ // line 1, offset 0x6ae24
  struct MODEL *model; // $a1
  struct CELL_OBJECT *cop; // $s3
  struct VECTOR player_pos; // stack offset -112
  struct COLLISION_PACKET *collide; // $s0
  int cell_x; // $a0
  int xd; // $v1
  int zd; // $a0
  int num_cb; // $s7
  int box_loop; // $s4
  int sphere_sq; // $v0
  int x1; // $s6
  struct BUILDING_BOX bbox; // stack offset -96
  int mdcount; // stack offset -48
  { // line 60, offset 0x6b00c
    struct BUILDING_BOX *pbox; // $s1
    struct MATRIX *mat; // $a1
    struct VECTOR offset; // stack offset -64
    { // line 76, offset 0x6b158
    } // line 103, offset 0x6b224
  } // line 105, offset 0x6b224
} // line 112, offset 0x6b288
/*
 * Offset 0x6B288
 * D:\driver2\game\C\OBJCOLL.C (line 735)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ DoScenaryCollisions()
{ // line 2, offset 0x6b288
  struct _CAR_DATA *lcp; // $s0
} // line 18, offset 0x6b354
/*
 * Offset 0x6B354
 * D:\driver2\game\C\OBJCOLL.C (line 155)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GlobalPositionToCellNumber(struct VECTOR *pPosition /*$a0*/)
{ // line 1, offset 0x6b354
  int cellX; // $a3
  int cellZ; // $a1
  int cbrX; // $t1
  int cbrZ; // $t0
  int cbr; // $t2
  int xOff; // $a3
  int yOff; // $a0
} // line 20, offset 0x6b44c
/*
 * Offset 0x6B44C
 * D:\driver2\game\C\OBJCOLL.C (line 183)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
char /*$ra*/ CellAtPositionEmpty(struct VECTOR *pPosition /*$s0*/, int radius /*$s1*/)
{ // line 1, offset 0x6b44c
} // line 22, offset 0x6b498
/*
 * Offset 0x6B498
 * D:\driver2\game\C\OBJCOLL.C (line 377)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetCopListCell(int x /*$a0*/, int z /*$a1*/)
{ // line 2, offset 0x6b498
  struct XZPAIR cell; // stack offset -16
} // line 7, offset 0x6b4c4
/*
 * Offset 0x6B4C4
 * D:\driver2\game\C\OBJCOLL.C (line 386)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ BuildCollisionCopList(int *count /*$a1*/)
{
}
/*
 * Offset 0x6B4E8
 * D:\driver2\game\C\PAD.C (line 75)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ InitControllers()
{ // line 2, offset 0x6b4e8
  int i; // $s3
  int j; // $a1
} // line 36, offset 0x6b610
/*
 * Offset 0x6B610
 * D:\driver2\game\C\PAD.C (line 132)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ ReadControllers()
{ // line 2, offset 0x6b610
  int i; // $s3
  int pad; // $s2
} // line 57, offset 0x6b758
/*
 * Offset 0x6B758
 * D:\driver2\game\C\PAD.C (line 257)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MapPad(int pad /*$t2*/, struct PADRAW *pData /*$a3*/)
{ // line 1, offset 0x6b758
  unsigned short i; // $a3
  unsigned short buttons; // $t0
  unsigned short mapped; // $t1
} // line 64, offset 0x6b940
/*
 * Offset 0x6B948
 * D:\driver2\game\C\PAD.C (line 336)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ HandleDualShock()
{ // line 2, offset 0x6b948
  int state; // $v1
  int port; // $s3
  int pad; // $s5
  int dsload; // $s7
} // line 114, offset 0x6bc2c
/*
 * Offset 0x6BC2C
 * D:\driver2\game\C\PAD.C (line 452)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ HandlePadVibration(int pad /*$t1*/)
{ // line 1, offset 0x6bc2c
  int speed; // $a3
} // line 44, offset 0x6be50
/*
 * Offset 0x6BE60
 * D:\driver2\game\C\PAD.C (line 113)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ CloseControllers()
{ // line 2, offset 0x6be60
  int i; // $v1
} // line 11, offset 0x6bea0
/*
 * Offset 0x6BEA0
 * D:\driver2\game\C\PAD.C (line 191)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetPadVibration(int pad /*$a3*/, unsigned char type /*$a1*/)
{
}
/*
 * Offset 0x6BF1C
 * D:\driver2\game\C\PAD.C (line 209)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ StopPadVibration(int pad /*$a0*/)
{
}
/*
 * Offset 0x6BF54
 * D:\driver2\game\C\PAD.C (line 228)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ StopDualShockMotors()
{
}
/*
 * Offset 0x6BF5C
 * D:\driver2\game\C\PAD.C (line 232)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetDuplicatePadData(char *buffer /*$a0*/, int size /*$a1*/)
{
}
/*
 * Offset 0x6BF8C
 * D:\driver2\game\C\PAD.C (line 323)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ClearPad(int pad /*$a0*/)
{
}
/*
 * Offset 0xE7000
 * D:\driver2\game\C\PATHFIND.C (line 314)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 s1
 */
struct tNode /*$ra*/ popNode()
{ // line 1, offset 0xe7000
  unsigned int lNumHeapEntries; // $s0
  struct tNode res; // stack offset -24
  unsigned short f; // $t8
  unsigned int child; // $a1
  unsigned int here; // $t5
  { // line 11, offset 0xe7058
    unsigned int lastEntry; // $t4
    { // line 15, offset 0xe7070
      int d; // $t3
      int d2; // $t2
      int d3; // $a3
      int d4; // $t1
    } // line 32, offset 0xe70b8
  } // line 33, offset 0xe7110
  { // line 35, offset 0xe7110
    int d; // $a2
    int d2; // $a3
    int d3; // $t1
    int d4; // $t2
  } // line 44, offset 0xe715c
} // line 47, offset 0xe715c
/*
 * Offset 0xE7194
 * D:\driver2\game\C\PATHFIND.C (line 426)
 * Stack frame base $sp, size 104
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ WunCell(struct VECTOR *pbase /*$s0*/)
{ // line 1, offset 0xe7194
  int i; // $s2
  int j; // $s4
  struct VECTOR v[2]; // stack offset -88
  struct VECTOR pos; // stack offset -56
  { // line 14, offset 0xe723c
    { // line 14, offset 0xe723c
      int z; // $a1
      int x; // $a2
    } // line 20, offset 0xe72c8
  } // line 20, offset 0xe72c8
} // line 24, offset 0xe735c
/*
 * Offset 0xE735C
 * D:\driver2\game\C\PATHFIND.C (line 453)
 * Stack frame base $sp, size 16
 */
void /*$ra*/ InvalidateMap()
{ // line 2, offset 0xe735c
  struct VECTOR bPos; // stack offset -16
  int count; // $t4
  int dir; // $t1
  int p; // $t2
  int q; // $t3
  { // line 12, offset 0xe73a8
    int tile; // $a0
    int mask; // $a1
    int diff; // $a1
    int i; // $v0
  } // line 15, offset 0xe73a8
} // line 34, offset 0xe74b0
/*
 * Offset 0xE74B0
 * D:\driver2\game\C\PATHFIND.C (line 495)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ BloodyHell()
{ // line 2, offset 0xe74b0
  struct VECTOR bPos; // stack offset -48
  int count; // $s4
  int dir; // $s0
  int p; // $s1
  int q; // $s2
  unsigned int howMany; // $s3
  0x69C raa
  { // line 22, offset 0xe755c
    int tile; // $a0
    int mask; // $a1
    int diff; // $v0
    int i; // $v0
  } // line 42, offset 0xe75e4
} // line 70, offset 0xe76c4
/*
 * Offset 0xE76C4
 * D:\driver2\game\C\PATHFIND.C (line 567)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: ra
 */
int /*$ra*/ blocked(struct tNode *v1 /*$a3*/, struct tNode *v2 /*$a2*/)
{ // line 1, offset 0xe76c4
  struct VECTOR pos; // stack offset -24
  int res; // $a0
  { // line 8, offset 0xe76e0
    { // line 8, offset 0xe76e0
      int z; // $a2
      int x; // $v1
    } // line 11, offset 0xe774c
  } // line 11, offset 0xe774c
  { // line 18, offset 0xe7790
    { // line 18, offset 0xe7790
      int z; // $v1
      int x; // $a0
    } // line 18, offset 0xe7790
  } // line 18, offset 0xe7790
} // line 23, offset 0xe7814
/*
 * Offset 0xE7814
 * D:\driver2\game\C\PATHFIND.C (line 712)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ iterate()
{ // line 2, offset 0xe7814
  int dir; // $s2
  struct tNode itHere; // stack offset -48
  struct tNode *nbr; // $s4
  { // line 12, offset 0xe7870
    int nearBy; // $v1
    int computed; // $s1
    { // line 14, offset 0xe7870
      int dx; // $v0
      int dz; // $a0
    } // line 15, offset 0xe7870
    { // line 15, offset 0xe7870
      { // line 15, offset 0xe7870
        int res; // $a0
      } // line 15, offset 0xe7870
    } // line 15, offset 0xe7870
  } // line 51, offset 0xe797c
  { // line 56, offset 0xe79b4
    int nr; // $a0
    int nl; // $v1
    { // line 58, offset 0xe7a08
      unsigned int a; // $v1
      { // line 58, offset 0xe7a08
        { // line 1, offset 0xe7a44
          unsigned int r; // $v0
        } // line 1, offset 0xe7a68
      } // line 1, offset 0xe7a68
    } // line 1, offset 0xe7a68
    { // line 61, offset 0xe7aac
      struct tNode *pnode; // $s0
      { // line 61, offset 0xe7aac
        unsigned int parent; // $a2
        unsigned int i; // $a3
      } // line 61, offset 0xe7b98
    } // line 61, offset 0xe7b98
  } // line 62, offset 0xe7b98
} // line 64, offset 0xe7ba8
/*
 * Offset 0xE7BD0
 * D:\driver2\game\C\PATHFIND.C (line 801)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitPathFinding()
{ // line 2, offset 0xe7bd0
  int i; // $a0
  { // line 1, offset 0xe7bd0
  } // line 1, offset 0xe7bd0
  { // line 1, offset 0xe7bd0
  } // line 1, offset 0xe7bd0
} // line 18, offset 0xe7ca8
/*
 * Offset 0xE7CA8
 * D:\driver2\game\C\PATHFIND.C (line 821)
 * Stack frame base $sp, size 88
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ getInterpolatedDistance(struct VECTOR *pos /*$s2*/)
{ // line 1, offset 0xe7ca8
  struct tNode n; // stack offset -72
  int fx; // $s4
  int fz; // $s5
  int a; // $s3
  int b; // $s2
  int c; // $v1
  int min; // $s0
  int flag; // $fp
  { // line 1, offset 0xe7ca8
    struct VECTOR *where; // $s2
    struct tNode *node; // $s0
    { // line 1, offset 0xe7ca8
      int x; // $v1
      { // line 1, offset 0xe7ca8
        struct tNode *pos; // $s0
        { // line 1, offset 0xe7ca8
          struct VECTOR sp; // stack offset -56
          { // line 1, offset 0xe7ca8
            { // line 1, offset 0xe7ca8
              int z; // $v0
              int x; // $a0
            } // line 1, offset 0xe7ca8
          } // line 1, offset 0xe7ca8
          { // line 1, offset 0xe7d78
            int res; // $v0
          } // line 1, offset 0xe7d9c
        } // line 1, offset 0xe7da0
      } // line 1, offset 0xe7da0
    } // line 1, offset 0xe7da0
  } // line 1, offset 0xe7da0
  { // line 1, offset 0xe7da0
    { // line 1, offset 0xe7da0
      int res; // $v0
    } // line 1, offset 0xe7da0
  } // line 1, offset 0xe7da0
  { // line 1, offset 0xe7da0
    { // line 1, offset 0xe7da0
      struct VECTOR sp; // stack offset -56
      { // line 1, offset 0xe7da0
        { // line 1, offset 0xe7da0
          int x; // $a3
          int z; // $v0
        } // line 1, offset 0xe7da0
      } // line 1, offset 0xe7da0
      { // line 1, offset 0xe7e84
        int res; // $v0
      } // line 1, offset 0xe7ea8
    } // line 1, offset 0xe7eac
  } // line 1, offset 0xe7eac
  { // line 18, offset 0xe7eac
    { // line 18, offset 0xe7eac
      int res; // $a0
    } // line 18, offset 0xe7eac
  } // line 18, offset 0xe7eac
  { // line 27, offset 0xe7f28
    { // line 27, offset 0xe7f28
      struct VECTOR sp; // stack offset -56
      { // line 27, offset 0xe7f28
        { // line 27, offset 0xe7f28
          int x; // $v1
          int z; // $v0
        } // line 27, offset 0xe7f28
      } // line 27, offset 0xe7f28
      { // line 1, offset 0xe7f8c
        int res; // $v0
      } // line 1, offset 0xe7fb0
    } // line 1, offset 0xe7fb4
  } // line 1, offset 0xe7fb4
  { // line 29, offset 0xe7fb4
    { // line 29, offset 0xe7fb4
      int res; // $a0
    } // line 29, offset 0xe7fb4
  } // line 29, offset 0xe7fb4
  { // line 43, offset 0xe807c
    { // line 43, offset 0xe807c
      struct VECTOR sp; // stack offset -56
      { // line 43, offset 0xe807c
        { // line 43, offset 0xe807c
          int x; // $v1
          int z; // $v0
        } // line 43, offset 0xe807c
      } // line 43, offset 0xe807c
      { // line 1, offset 0xe80d8
        int res; // $v0
      } // line 1, offset 0xe80fc
    } // line 1, offset 0xe8100
  } // line 1, offset 0xe8100
  { // line 44, offset 0xe8100
    { // line 44, offset 0xe8100
      int res; // $a0
    } // line 44, offset 0xe8100
  } // line 44, offset 0xe8100
} // line 59, offset 0xe822c
/*
 * Offset 0xE822C
 * D:\driver2\game\C\PATHFIND.C (line 891)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ addCivs()
{ // line 2, offset 0xe822c
  struct _CAR_DATA *cp; // $t5
  { // line 7, offset 0xe8260
    int where; // $a3
    { // line 9, offset 0xe8260
      int vx; // $a3
      int vz; // $a1
      int x; // $a3
      int z; // $t0
    } // line 9, offset 0xe8260
    { // line 9, offset 0xe8260
      int vx; // $t1
      int vz; // $t2
      int x; // $t1
      int z; // $a1
    } // line 31, offset 0xe8354
  } // line 32, offset 0xe8354
} // line 34, offset 0xe836c
/*
 * Offset 0xE836C
 * D:\driver2\game\C\PATHFIND.C (line 933)
 * Stack frame base $sp, size 88
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ UpdateCopMap()
{ // line 2, offset 0xe836c
  { // line 6, offset 0xe83c0
  } // line 6, offset 0xe83c0
  { // line 13, offset 0xe83fc
    struct tNode startNode; // stack offset -72
    { // line 19, offset 0xe843c
      struct _CAR_DATA *cp; // $a0
    } // line 19, offset 0xe843c
    { // line 1, offset 0xe8500
      { // line 1, offset 0xe8500
        { // line 1, offset 0xe8500
          { // line 1, offset 0xe8500
            int i; // $a1
            { // line 1, offset 0xe8524
              int d; // $v0
            } // line 1, offset 0xe8554
          } // line 1, offset 0xe8564
        } // line 1, offset 0xe8564
      } // line 1, offset 0xe8564
    } // line 1, offset 0xe8564
    { // line 1, offset 0xe8564
      { // line 1, offset 0xe8564
        int x; // $v0
        { // line 1, offset 0xe8564
          { // line 1, offset 0xe8564
            struct VECTOR sp; // stack offset -56
            { // line 1, offset 0xe8564
              { // line 1, offset 0xe8564
                int z; // $v0
                int x; // $v1
              } // line 1, offset 0xe8564
            } // line 1, offset 0xe8564
            { // line 1, offset 0xe8604
              int res; // $v0
            } // line 1, offset 0xe8628
          } // line 1, offset 0xe862c
        } // line 1, offset 0xe862c
      } // line 1, offset 0xe862c
    } // line 1, offset 0xe862c
    { // line 1, offset 0xe862c
      struct tNode n; // stack offset -56
      int fx; // $v1
      int fz; // $v0
      { // line 1, offset 0xe8660
        { // line 1, offset 0xe8660
          int dz; // $a0
          int dx; // $v0
        } // line 1, offset 0xe8660
      } // line 1, offset 0xe8660
      { // line 1, offset 0xe8660
        { // line 1, offset 0xe8660
          unsigned int parent; // $a2
          unsigned int i; // $a3
        } // line 1, offset 0xe8774
      } // line 1, offset 0xe8774
      { // line 53, offset 0xe8774
        { // line 53, offset 0xe8774
          int dz; // $a0
          int dx; // $v0
        } // line 53, offset 0xe8774
      } // line 53, offset 0xe8774
      { // line 53, offset 0xe8774
        { // line 53, offset 0xe8774
          unsigned int parent; // $a2
          unsigned int i; // $a3
        } // line 54, offset 0xe88b4
      } // line 54, offset 0xe88b4
      { // line 56, offset 0xe88b4
        { // line 56, offset 0xe88b4
          int dz; // $a0
          int dx; // $v0
        } // line 56, offset 0xe88b4
      } // line 56, offset 0xe88b4
      { // line 56, offset 0xe88b4
        { // line 56, offset 0xe88b4
          unsigned int parent; // $a2
          unsigned int i; // $a3
        } // line 57, offset 0xe89bc
      } // line 57, offset 0xe89bc
      { // line 1, offset 0xe89c4
        { // line 1, offset 0xe89c4
          int dz; // $a0
          int dx; // $v0
        } // line 1, offset 0xe89c4
      } // line 1, offset 0xe89c4
      { // line 1, offset 0xe89c4
        { // line 1, offset 0xe89c4
          unsigned int parent; // $a2
          unsigned int i; // $a3
        } // line 1, offset 0xe8ad8
      } // line 1, offset 0xe8ad8
      { // line 63, offset 0xe8ad8
        { // line 63, offset 0xe8ad8
          int dz; // $a0
          int dx; // $v0
        } // line 63, offset 0xe8ad8
      } // line 63, offset 0xe8ad8
      { // line 63, offset 0xe8ad8
        { // line 63, offset 0xe8ad8
          unsigned int parent; // $a2
          unsigned int i; // $a3
        } // line 64, offset 0xe8c18
      } // line 64, offset 0xe8c18
      { // line 66, offset 0xe8c18
        { // line 66, offset 0xe8c18
          int dz; // $a0
          int dx; // $v0
        } // line 66, offset 0xe8c18
      } // line 66, offset 0xe8c18
      { // line 66, offset 0xe8c18
        { // line 66, offset 0xe8c18
          unsigned int parent; // $a2
          unsigned int i; // $a3
        } // line 66, offset 0xe8d18
      } // line 66, offset 0xe8d18
    } // line 66, offset 0xe8d18
  } // line 66, offset 0xe8d18
  { // line 77, offset 0xe8d54
    int i; // $s0
    { // line 1, offset 0xe8df4
    } // line 1, offset 0xe8dfc
  } // line 91, offset 0xe8dfc
  { // line 94, offset 0xe8dfc
    int i; // $a1
    int maxRet; // $a0
  } // line 105, offset 0xe8e70
  { // line 108, offset 0xe8e70
    int dx; // $a0
    int dy; // $v1
    int dz; // $v0
  } // line 112, offset 0xe8f00
} // line 113, offset 0xe8f00
/*
 * Offset 0xE8F00
 * D:\driver2\game\C\PATHFIND.C (line 1050)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ getHeadingToPlayer(int vx /*$s4*/, int vy /*$a1*/, int vz /*$s3*/)
{ // line 1, offset 0xe8f00
  int d1; // $s2
  int d2; // $s1
  int d3; // $s0
  struct VECTOR pos; // stack offset -48
  { // line 1, offset 0xe8f00
    int dx; // $a3
    int dy; // $v1
    int dz; // $v0
    int playerHereDistSq; // $a3
    { // line 21, offset 0xe8f98
    } // line 23, offset 0xe8f98
  } // line 24, offset 0xe8f98
  { // line 48, offset 0xe8ff8
  } // line 50, offset 0xe9024
  { // line 52, offset 0xe9030
  } // line 60, offset 0xe9058
  { // line 56, offset 0xe9058
  } // line 61, offset 0xe90a4
} // line 62, offset 0xe90a4
/*
 * Offset 0xE90A4
 * D:\driver2\game\C\PATHFIND.C (line 659)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ setDistance(struct tNode *n /*$a0*/, unsigned short dist /*$a1*/)
{
}
/*
 * Offset 0x6BFB8
 * D:\driver2\game\C\PAUSE.C (line 1004)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ ShowPauseMenu(enum PAUSEMODE mode /*$s0*/)
{ // line 1, offset 0x6bfb8
  enum PAUSEMODE passed_mode; // $s2
  { // line 58, offset 0x6c128
  } // line 81, offset 0x6c1a8
  { // line 88, offset 0x6c1e0
    struct RECT rect; // stack offset -32
  } // line 97, offset 0x6c264
} // line 133, offset 0x6c314
/*
 * Offset 0x6C314
 * D:\driver2\game\C\PAUSE.C (line 1216)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitaliseMenu(enum PAUSEMODE mode /*$a2*/)
{ // line 1, offset 0x6c314
  struct MENU_ITEM *pItem; // $a0
  int i; // $a1
} // line 172, offset 0x6c720
/*
 * Offset 0x6C720
 * D:\driver2\game\C\PAUSE.C (line 1401)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupMenu(struct MENU_HEADER *menu /*$a0*/, int back /*$a1*/)
{ // line 1, offset 0x6c720
  struct MENU_ITEM *pItem; // $a2
  int count; // $a3
} // line 30, offset 0x6c85c
/*
 * Offset 0x6C85C
 * D:\driver2\game\C\PAUSE.C (line 1443)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawVisibleMenus()
{ // line 2, offset 0x6c85c
  struct MENU_HEADER *pActive; // $s5
  struct MENU_ITEM *pItem; // $s1
  struct POLY_FT3 *null; // $a0
  int i; // stack offset -48
  int ypos; // $s3
  int xpos; // $fp
  int width; // $s4
  { // line 30, offset 0x6c928
    unsigned char r; // $s6
    unsigned char b; // $s7
    int x1; // $s0
    int x2; // $s2
  } // line 66, offset 0x6caa8
} // line 85, offset 0x6cc50
/*
 * Offset 0x6CC50
 * D:\driver2\game\C\PAUSE.C (line 1543)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ControlMenu()
{ // line 2, offset 0x6cc50
  static int debounce; // offset 0x38
  unsigned short paddata; // $a2
  unsigned short paddirect; // $a3
  { // line 53, offset 0x6cd3c
    int doit; // $v1
  } // line 78, offset 0x6cde0
  { // line 132, offset 0x6cfbc
    int i; // $a0
  } // line 139, offset 0x6d020
  { // line 149, offset 0x6d040
    int i; // $a0
  } // line 160, offset 0x6d09c
} // line 162, offset 0x6d09c
/*
 * Offset 0x6D0AC
 * D:\driver2\game\C\PAUSE.C (line 1787)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ EnterScoreName()
{ // line 2, offset 0x6d0ac
  struct SCORE_ENTRY *table; // stack offset -40
  char *username; // $s3
  unsigned short npad; // $a1
  int so; // $s0
  int co; // $s1
  int delay; // $s2
  char c; // $a0
  char toggle; // $s6
} // line 154, offset 0x6d38c
/*
 * Offset 0x6D38C
 * D:\driver2\game\C\PAUSE.C (line 1943)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ CreateScoreNames(struct SCORE_ENTRY *table /*$s0*/, struct PLAYER_SCORE *score /*stack 4*/, int position /*stack 8*/)
{ // line 1, offset 0x6d38c
  char *text; // $s1
  int min; // $t1
  int frac; // $v0
  int i; // $s5
} // line 69, offset 0x6d6cc
/*
 * Offset 0x6D6FC
 * D:\driver2\game\C\PAUSE.C (line 2020)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawHighScoreMenu(int selection /*stack 0*/)
{ // line 1, offset 0x6d6fc
  struct POLY_FT3 *null; // $a0
  char text[4]; // stack offset -48
  unsigned char r; // $s3
  unsigned char g; // $s5
  unsigned char b; // $s2
  int i; // $s0
  int ypos; // $s4
} // line 55, offset 0x6da18
/*
 * Offset 0x6DA18
 * D:\driver2\game\C\PAUSE.C (line 1153)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SaveReplay(int direction /*$a0*/)
{
}
/*
 * Offset 0x6DA3C
 * D:\driver2\game\C\PAUSE.C (line 1158)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SaveGame(int direction /*$a0*/)
{
}
/*
 * Offset 0x6DA60
 * D:\driver2\game\C\PAUSE.C (line 1163)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ EnterName()
{
}
/*
 * Offset 0x6DA80
 * D:\driver2\game\C\PAUSE.C (line 1185)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ MaxMenuStringLength(struct MENU_HEADER *pMenu /*$v0*/)
{ // line 1, offset 0x6da80
  struct MENU_ITEM *pItems; // $s1
  int max; // $s2
  int temp; // $s0
} // line 21, offset 0x6db38
/*
 * Offset 0x6DB38
 * D:\driver2\game\C\PAUSE.C (line 1710)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ PauseMap(int direction /*$a0*/)
{
}
/*
 * Offset 0x6DB9C
 * D:\driver2\game\C\PAUSE.C (line 1725)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SfxVolume(int direction /*$a0*/)
{ // line 1, offset 0x6db9c
} // line 19, offset 0x6dc6c
/*
 * Offset 0x6DC6C
 * D:\driver2\game\C\PAUSE.C (line 1746)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ MusicVolume(int direction /*$a0*/)
{ // line 1, offset 0x6dc6c
} // line 19, offset 0x6dd3c
/*
 * Offset 0x6DD3C
 * D:\driver2\game\C\PAUSE.C (line 1139)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DrawPauseMenus()
{
}
/*
 * Offset 0x6DD9C
 * D:\driver2\game\C\PEDEST.C (line 1137)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ IHaveThePower()
{ // line 2, offset 0x6dd9c
  struct _CAR_DATA *cp; // $t4
  { // line 15, offset 0x6de20
  } // line 33, offset 0x6df88
} // line 45, offset 0x6dfbc
/*
 * Offset 0x6DFBC
 * D:\driver2\game\C\PEDEST.C (line 1191)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ ProcessTannerPad(struct PEDESTRIAN *pPed /*$s1*/, unsigned long pad /*$a1*/, char PadSteer /*$a2*/, char use_analogue /*$a3*/)
{ // line 1, offset 0x6dfbc
  struct VECTOR vec; // stack offset -88
  int mapheight; // $s2
  struct VECTOR normal; // stack offset -72
  struct VECTOR out; // stack offset -56
  struct _sdPlane *SurfacePtr; // stack offset -24
  { // line 33, offset 0x6e030
    struct VECTOR tVec; // stack offset -40
    struct _sdPlane *plane; // $v0
    int mH; // $v1
    int sI; // $a0
  } // line 86, offset 0x6e16c
  { // line 168, offset 0x6e3f8
  } // line 174, offset 0x6e458
} // line 176, offset 0x6e458
/*
 * Offset 0x6E470
 * D:\driver2\game\C\PEDEST.C (line 1375)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ InitTanner()
{ // line 2, offset 0x6e470
} // line 58, offset 0x6e62c
/*
 * Offset 0x6E62C
 * D:\driver2\game\C\PEDEST.C (line 1466)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ InitPedestrians()
{ // line 2, offset 0x6e62c
  int loop; // $a1
  struct SEATED_PEDESTRIANS *seatedptr; // $s2
} // line 47, offset 0x6e72c
/*
 * Offset 0x6E72C
 * D:\driver2\game\C\PEDEST.C (line 1623)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ ActivatePlayerPedestrian(struct _CAR_DATA *pCar /*$s6*/, char *padId /*stack 4*/, int direction /*$a1*/, long *position[4] /*$a3*/, int playerType /*stack 16*/)
{ // line 1, offset 0x6e72c
  struct PEDESTRIAN *pPed; // $s1
  struct PEDESTRIAN *pSPed; // $a0
  struct VECTOR v; // stack offset -72
  int nx; // $s4
  int nz; // $s2
  long w; // $s0
  long x; // $s5
  long y; // stack offset -52
  long z; // $s1
  long d; // stack offset -48
  int side; // $fp
  int id; // $s3
  { // line 65, offset 0x6e83c
    { // line 140, offset 0x6eab0
    } // line 140, offset 0x6eab0
    { // line 184, offset 0x6ebb0
    } // line 184, offset 0x6ebb0
  } // line 184, offset 0x6ebb0
} // line 212, offset 0x6ecf0
/*
 * Offset 0x6ECF0
 * D:\driver2\game\C\PEDEST.C (line 1877)
 * Stack frame base $sp, size 168
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ PlaceRoadBlockCops()
{ // line 2, offset 0x6ecf0
  struct _CAR_DATA *pCar; // $a0
  struct _CAR_DATA *pCopCars[16]; // stack offset -152
  int numCops; // $fp
  { // line 19, offset 0x6ed84
    int x; // $s2
    int z; // $s0
    int w; // $s0
    int i; // $s7
    int s1; // $s1
    int s2; // $a3
    struct VECTOR vert; // stack offset -88
    long disp[4]; // stack offset -72
    long dir[4]; // stack offset -56
    int alpha; // $s1
  } // line 89, offset 0x6f044
} // line 91, offset 0x6f044
/*
 * Offset 0x6F074
 * D:\driver2\game\C\PEDEST.C (line 1975)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ CreatePedAtLocation(long *pPos[4] /*$s2*/, int pedType /*$s1*/)
{ // line 1, offset 0x6f074
  struct PEDESTRIAN *pPed; // $s0
} // line 70, offset 0x6f1d4
/*
 * Offset 0x6F1D4
 * D:\driver2\game\C\PEDEST.C (line 2168)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ ControlPedestrians()
{ // line 2, offset 0x6f1d4
  struct PEDESTRIAN *pPed; // $s0
  struct PEDESTRIAN *pPedNext; // $s2
  struct _CAR_DATA *pCar; // $v0
  { // line 57, offset 0x6f2d4
  } // line 65, offset 0x6f318
} // line 73, offset 0x6f344
/*
 * Offset 0x6F344
 * D:\driver2\game\C\PEDEST.C (line 2385)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ PedDoNothing(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x6F614
 * D:\driver2\game\C\PEDEST.C (line 2523)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ PedUserRunner(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x6f614
} // line 109, offset 0x6f874
/*
 * Offset 0x6F874
 * D:\driver2\game\C\PEDEST.C (line 2827)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ SetupGetOutCar(struct PEDESTRIAN *pPed /*$s5*/, struct _CAR_DATA *pCar /*$s3*/, int side /*$s7*/)
{ // line 1, offset 0x6f874
  int alpha; // $s2
  long disp[4]; // stack offset -80
  long dir[4]; // stack offset -64
  struct SVECTOR vert; // stack offset -48
  int x; // $s4
  int z; // $s0
  int a; // $s6
  int nx; // $a3
  int nz; // $a1
} // line 64, offset 0x6faa4
/*
 * Offset 0x6FAA4
 * D:\driver2\game\C\PEDEST.C (line 2898)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ SetupGetInCar(struct PEDESTRIAN *pPed /*$s2*/)
{ // line 1, offset 0x6faa4
  int alpha; // $s1
  long disp[4]; // stack offset -72
  long dir[4]; // stack offset -56
  struct SVECTOR vert; // stack offset -40
  { // line 36, offset 0x6fb94
    int x; // $t1
    int z; // $t2
    int a; // $a0
    int nx; // $a3
    int nz; // $a1
  } // line 59, offset 0x6fc8c
  { // line 70, offset 0x6fcd8
    long pos[4]; // stack offset -32
  } // line 71, offset 0x6fcd8
} // line 90, offset 0x6fd70
/*
 * Offset 0x6FD70
 * D:\driver2\game\C\PEDEST.C (line 3074)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ TannerCameraHandler(struct PEDESTRIAN *pPed /*$a0*/)
{ // line 2, offset 0x6fd70
  int padsteer; // $a3
  int maxY; // $t1
  int maxX; // $t5
  int range; // $t0
  int minX; // $t4
  int extra; // $a3
} // line 76, offset 0x6ffb0
/*
 * Offset 0x6FFB0
 * D:\driver2\game\C\PEDEST.C (line 3157)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: ra
 */
void /*$ra*/ TannerSitDown(struct PEDESTRIAN *pPed /*$a2*/)
{ // line 1, offset 0x6ffb0
  struct VECTOR angle; // stack offset -24
} // line 62, offset 0x70138
/*
 * Offset 0x70138
 * D:\driver2\game\C\PEDEST.C (line 3227)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ AnimatePed(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x70138
  { // line 11, offset 0x70158
    int mapheight; // $a3
    int reverse; // $s1
    { // line 14, offset 0x70158
      struct VECTOR vec; // stack offset -32
    } // line 39, offset 0x701c4
    { // line 103, offset 0x70374
      int sfc; // $v1
    } // line 108, offset 0x70424
  } // line 121, offset 0x704d0
} // line 123, offset 0x704d0
/*
 * Offset 0x704E4
 * D:\driver2\game\C\PEDEST.C (line 3447)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ PingInPedestrians()
{ // line 2, offset 0x704e4
  int bFound; // $s1
  struct VECTOR randomLoc; // stack offset -88
  struct VECTOR baseLoc; // stack offset -72
  int i; // $s2
  int pingInDist; // $a2
  struct VECTOR position; // stack offset -56
  struct VECTOR target; // stack offset -40
  struct PEDESTRIAN *pedestrian; // $s1
  { // line 37, offset 0x70580
    { // line 55, offset 0x70660
      struct PEDESTRIAN *pPed; // $a2
      { // line 73, offset 0x70690
        int x; // $v1
        int z; // $v0
        int radius; // $v1
      } // line 75, offset 0x70690
    } // line 77, offset 0x706dc
  } // line 79, offset 0x706dc
  { // line 87, offset 0x70714
    { // line 136, offset 0x7085c
      int rval; // $v1
    } // line 175, offset 0x708c0
  } // line 180, offset 0x708c0
} // line 185, offset 0x708c0
/*
 * Offset 0x708E0
 * D:\driver2\game\C\PEDEST.C (line 3685)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ FindPointOfCollision(struct _CAR_DATA *pCar /*$s3*/, struct VECTOR *pPos /*$a1*/)
{ // line 1, offset 0x708e0
  int tb1; // $v1
  int tb2; // $v0
  int minX; // $a3
  int maxX; // $t0
  int minZ; // $v0
  int maxZ; // $a0
  int x; // $t1
  int z; // $a1
  int s1; // $a2
  int s2; // $v1
  int carLength[2]; // stack offset -40
  static struct CRET2D collisionResult; // offset 0x0
} // line 68, offset 0x70b04
/*
 * Offset 0x70B04
 * D:\driver2\game\C\PEDEST.C (line 3762)
 * Stack frame base $sp, size 136
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ TannerCarCollisionCheck(struct VECTOR *pPos /*$s5*/, int dir /*$a1*/, int bQuick /*stack 8*/)
{ // line 1, offset 0x70b04
  int carLength[2]; // stack offset -120
  struct _CAR_DATA *cp0; // $s0
  struct _CAR_DATA *cp1; // $s1
  static struct CRET2D collisionResult; // offset 0x30
  unsigned int dNewLBODY[2]; // stack offset -112
  int speed; // $v0
  { // line 36, offset 0x70b94
    { // line 36, offset 0x70b94
    } // line 36, offset 0x70b94
    { // line 53, offset 0x70c6c
      struct VECTOR velocity; // stack offset -104
      long pointVel[4]; // stack offset -88
      long reaction[4]; // stack offset -72
      long lever[4]; // stack offset -56
      int strikeVel; // $t1
      { // line 84, offset 0x70dec
      } // line 95, offset 0x70dec
      { // line 99, offset 0x70e18
        int twistY; // $a2
        int lever_dot_n; // $a0
        int displacementsquared; // $a1
        int denom; // $a0
      } // line 112, offset 0x70ef4
    } // line 133, offset 0x71040
  } // line 142, offset 0x71070
} // line 145, offset 0x710bc
/*
 * Offset 0x710BC
 * D:\driver2\game\C\PEDEST.C (line 3946)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ SetupCivJump(struct PEDESTRIAN *pPed /*$s1*/, struct _CAR_DATA *cp /*$s0*/)
{ // line 1, offset 0x710bc
  long disp[4]; // stack offset -48
  long dir[4]; // stack offset -32
  int angle; // $s0
  { // line 14, offset 0x71128
    short scale; // $a2
  } // line 21, offset 0x7114c
  { // line 62, offset 0x71250
  } // line 81, offset 0x71314
} // line 94, offset 0x7138c
/*
 * Offset 0x7138C
 * D:\driver2\game\C\PEDEST.C (line 4101)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ CivPedWalk(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x7138c
  int turn; // $a1
  int offset1; // $t0
  int offset2; // $v1
  int lookahead; // $s3
  int speed; // $s1
} // line 81, offset 0x71664
/*
 * Offset 0x71664
 * D:\driver2\game\C\PEDEST.C (line 4508)
 * Stack frame base $sp, size 32
 */
void /*$ra*/ CorrectPathPosition(struct PEDESTRIAN *pedestrian /*$a0*/, struct VECTOR *position /*$a1*/)
{ // line 2, offset 0x71664
  struct VECTOR vec; // stack offset -16
} // line 102, offset 0x71664
/*
 * Offset 0x71670
 * D:\driver2\game\C\PEDEST.C (line 4619)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ CalcPedestrianDirection(int last_dir /*$a0*/, int wx /*$s5*/, int wz /*$s6*/, struct VECTOR *target /*$s3*/)
{ // line 1, offset 0x71670
  int dir; // $s2
  int num; // $s1
  int rx; // $v1
  int rz; // $a0
  int mask; // $s0
  { // line 50, offset 0x71728
  } // line 62, offset 0x71774
} // line 115, offset 0x71814
/*
 * Offset 0x71814
 * D:\driver2\game\C\PEDEST.C (line 4984)
 * Stack frame base $sp, size 0
 */
struct SEATED_PEDESTRIANS * /*$ra*/ FindTannerASeat(struct PEDESTRIAN *pPed /*$t4*/)
{ // line 1, offset 0x71814
  struct SEATED_PEDESTRIANS *seatedptr; // $a2
  struct SEATED_PEDESTRIANS *theOne; // $t1
  int dx; // $a0
  int dz; // $v1
  int distsqr; // $v0
  int bestSqr; // $t2
} // line 39, offset 0x71930
/*
 * Offset 0x71930
 * D:\driver2\game\C\PEDEST.C (line 5031)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ add_seated(struct SEATED_PEDESTRIANS *seatedptr /*$s0*/, int seat_index /*$s2*/)
{ // line 1, offset 0x71930
  struct PEDESTRIAN *pedestrian; // $s1
  int index; // $v0
} // line 45, offset 0x71aac
/*
 * Offset 0x71AC4
 * D:\driver2\game\C\PEDEST.C (line 5084)
 * Stack frame base $sp, size 16
 */
void /*$ra*/ set_coll_box(int index /*$t2*/, struct _CAR_DATA *cp /*$t0*/, int offset /*$t3*/)
{ // line 1, offset 0x71ac4
  struct VECTOR BoxCentre; // stack offset -16
  int boxsize; // $t1
} // line 26, offset 0x71bdc
/*
 * Offset 0x71BE4
 * D:\driver2\game\C\PEDEST.C (line 5118)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ BuildCarCollisionBox()
{ // line 2, offset 0x71be4
  struct _CAR_DATA *cp; // $s3
  int count1; // $s4
  int i; // $t1
  { // line 28, offset 0x71d24
    int x; // $a0
    int z; // $a2
  } // line 37, offset 0x71dc0
} // line 53, offset 0x71e74
/*
 * Offset 0x71E74
 * D:\driver2\game\C\PEDEST.C (line 5249)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ CalculatePedestrianInterest(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x71e74
  int interest; // $a2
  int dist; // $v1
  struct _CAR_DATA *pCar; // $a2
  struct VECTOR v1; // stack offset -40
  struct VECTOR v2; // stack offset -24
} // line 69, offset 0x71fac
/*
 * Offset 0x71FBC
 * D:\driver2\game\C\PEDEST.C (line 1521)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DestroyPedestrians()
{ // line 2, offset 0x71fbc
} // line 13, offset 0x7201c
/*
 * Offset 0x7201C
 * D:\driver2\game\C\PEDEST.C (line 1567)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DestroyPedestrian(struct PEDESTRIAN *pPed /*$a1*/)
{ // line 1, offset 0x7201c
  { // line 38, offset 0x720cc
    struct SEATED_PEDESTRIANS *seatedptr; // $a0
  } // line 41, offset 0x720f8
} // line 49, offset 0x72114
/*
 * Offset 0x72114
 * D:\driver2\game\C\PEDEST.C (line 1842)
 * Stack frame base $sp, size 0
 */
struct PEDESTRIAN * /*$ra*/ CreatePedestrian()
{ // line 2, offset 0x72114
} // line 27, offset 0x7217c
/*
 * Offset 0x72184
 * D:\driver2\game\C\PEDEST.C (line 4221)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ HandlePedestrians()
{ // line 2, offset 0x72184
} // line 236, offset 0x721c4
/*
 * Offset 0x721D4
 * D:\driver2\game\C\PEDEST.C (line 3357)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DeActivatePlayerPedestrian(struct PEDESTRIAN *pPed /*$s3*/)
{ // line 1, offset 0x721d4
  int distToCarSq; // stack offset -32
  struct _CAR_DATA *closestCar; // $s1
  struct _PLAYER *pPlayer; // $v0
  struct VECTOR point; // stack offset -48
  int getIn; // $s2
  { // line 27, offset 0x72284
  } // line 38, offset 0x722dc
} // line 39, offset 0x722f8
/*
 * Offset 0x722F8
 * D:\driver2\game\C\PEDEST.C (line 2052)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawAllPedestrians()
{ // line 2, offset 0x722f8
  struct PEDESTRIAN *pPed; // $s0
  int pedType; // $s2
  struct MATRIX mStore; // stack offset -56
  { // line 19, offset 0x72384
    { // line 26, offset 0x723b4
    } // line 26, offset 0x723b4
  } // line 33, offset 0x723cc
  { // line 49, offset 0x7243c
  } // line 54, offset 0x72468
} // line 85, offset 0x72498
/*
 * Offset 0x72498
 * D:\driver2\game\C\PEDEST.C (line 2145)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ TannerActionHappening()
{ // line 2, offset 0x72498
  struct PEDESTRIAN *pPed; // $a0
} // line 13, offset 0x724e0
/*
 * Offset 0x724E0
 * D:\driver2\game\C\PEDEST.C (line 1440)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetTannerPosition(struct VECTOR *pVec /*$a0*/)
{ // line 1, offset 0x724e0
  struct PEDESTRIAN *pPed; // $a1
} // line 19, offset 0x72568
/*
 * Offset 0x72568
 * D:\driver2\game\C\PEDEST.C (line 4924)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetPedestrianTurn(struct PEDESTRIAN *pedestrian /*$a0*/, int turn /*$a1*/)
{ // line 1, offset 0x72568
  int dir; // $a2
  int speed; // $v1
} // line 11, offset 0x725ec
/*
 * Offset 0x725EC
 * D:\driver2\game\C\PEDEST.C (line 5325)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ PedSurfaceType(struct VECTOR *ped_pos /*$a0*/)
{ // line 5, offset 0x725ec
  struct _sdPlane *sfc_ptr; // $v0
} // line 10, offset 0x72620
/*
 * Offset 0x72620
 * D:\driver2\game\C\PEDEST.C (line 4845)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ IsPavement(int x /*$a0*/, int y /*$a1*/, int z /*$a2*/, struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x72620
  struct VECTOR vec; // stack offset -24
  int r; // $v1
} // line 72, offset 0x726ac
/*
 * Offset 0x726AC
 * D:\driver2\game\C\PEDEST.C (line 4943)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
struct SEATED_PEDESTRIANS * /*$ra*/ FindSeated()
{ // line 2, offset 0x726ac
  struct SEATED_PEDESTRIANS *seatedptr; // $s0
  { // line 7, offset 0x726d4
    int dx; // $v1
    int dz; // $v0
    int distsqr; // $v1
    int count1; // $a2
  } // line 32, offset 0x7278c
} // line 34, offset 0x727a0
/*
 * Offset 0x727A0
 * D:\driver2\game\C\PEDEST.C (line 5178)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
struct _CAR_DATA * /*$ra*/ CheckForCar(struct PEDESTRIAN *pedestrian /*$s3*/)
{ // line 1, offset 0x727a0
  int count; // $s0
  { // line 5, offset 0x727d8
  } // line 26, offset 0x727f8
  { // line 28, offset 0x7281c
  } // line 35, offset 0x7281c
  { // line 39, offset 0x72868
  } // line 43, offset 0x72884
} // line 45, offset 0x728a4
/*
 * Offset 0x728A4
 * D:\driver2\game\C\PEDEST.C (line 4465)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ PedestrianActionInit_WalkToTarget(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x728a4
  int dir; // $v1
} // line 31, offset 0x72920
/*
 * Offset 0x72930
 * D:\driver2\game\C\PEDEST.C (line 3060)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupTannerSitDown(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x7296C
 * D:\driver2\game\C\PEDEST.C (line 3026)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupPressButton(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x729AC
 * D:\driver2\game\C\PEDEST.C (line 2639)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ PedUserWalker(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x729ac
  static int speed; // offset 0x80
} // line 55, offset 0x72a78
/*
 * Offset 0x72A78
 * D:\driver2\game\C\PEDEST.C (line 2702)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ PedCarryOutAnimation(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x72BC4
 * D:\driver2\game\C\PEDEST.C (line 2994)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ PedGetInCar(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x72bc4
  long disp[4]; // stack offset -48
  long dir[4]; // stack offset -32
  struct SVECTOR vert; // stack offset -16
} // line 24, offset 0x72c54
/*
 * Offset 0x72C54
 * D:\driver2\game\C\PEDEST.C (line 2796)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ PedGetOutCar(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x72CF8
 * D:\driver2\game\C\PEDEST.C (line 3040)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ PedPressButton(struct PEDESTRIAN *pPed /*$v1*/)
{
}
/*
 * Offset 0x72D48
 * D:\driver2\game\C\PEDEST.C (line 3402)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ CivPedDoNothing(struct PEDESTRIAN *pPed /*$a0*/)
{
}
/*
 * Offset 0x72D50
 * D:\driver2\game\C\PEDEST.C (line 4190)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ CivPedSit(struct PEDESTRIAN *pPed /*$a0*/)
{ // line 2, offset 0x72d50
} // line 18, offset 0x72d58
/*
 * Offset 0x72D58
 * D:\driver2\game\C\PEDEST.C (line 4047)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ CivPedJump(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x72d58
} // line 26, offset 0x72e08
/*
 * Offset 0x72E08
 * D:\driver2\game\C\PEDEST.C (line 2353)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ CopStand(struct PEDESTRIAN *pPed /*$s0*/)
{ // line 1, offset 0x72e08
  struct VECTOR v; // stack offset -24
} // line 24, offset 0x72e64
/*
 * Offset 0x72E64
 * D:\driver2\game\C\PEDEST.C (line 2325)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ CivGetIn(struct PEDESTRIAN *pPed /*$s2*/)
{ // line 1, offset 0x72e64
  struct DRIVER2_STRAIGHT *str; // $s1
  struct DRIVER2_CURVE *crv; // $s0
  { // line 1, offset 0x72e64
  } // line 20, offset 0x72f4c
} // line 21, offset 0x72f4c
/*
 * Offset 0x72F4C
 * D:\driver2\game\C\PEDEST.C (line 3640)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ TannerCollision(struct PEDESTRIAN *pPed /*$s1*/)
{ // line 1, offset 0x72f4c
} // line 35, offset 0x73024
/*
 * Offset 0x73038
 * D:\driver2\game\C\PEDEST.C (line 1541)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ DestroyCivPedestrians()
{ // line 2, offset 0x73038
  struct PEDESTRIAN *pPed; // $v1
  struct PEDESTRIAN *pHPed; // $s0
} // line 18, offset 0x730a0
/*
 * Offset 0x730A0
 * D:\driver2\game\C\PEDEST.C (line 2256)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupDoNowt(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x730E4
 * D:\driver2\game\C\PEDEST.C (line 2275)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupWalker(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x73120
 * D:\driver2\game\C\PEDEST.C (line 2291)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupRunner(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x73164
 * D:\driver2\game\C\PEDEST.C (line 2302)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupBack(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x731A4
 * D:\driver2\game\C\PEDEST.C (line 3411)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ SetupCivPedRouteData(struct VECTOR *pPos /*$s1*/)
{ // line 1, offset 0x731a4
  struct VECTOR baseLoc; // stack offset -32
} // line 24, offset 0x73260
/*
 * Offset 0x73260
 * D:\driver2\game\C\PEDEST.C (line 3915)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ PingOutPed(struct PEDESTRIAN *pPed /*$a2*/)
{ // line 1, offset 0x73260
  int px; // $a0
  int pz; // $v1
  int ps; // $a0
} // line 23, offset 0x732d8
/*
 * Offset 0x732D8
 * D:\driver2\game\C\PEDEST.C (line 4080)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupCivPedWalk(struct PEDESTRIAN *pPed /*$s0*/)
{
}
/*
 * Offset 0x73328
 * D:\driver2\game\C\PEDEST.C (line 5231)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CheckForPlayerCar(struct PEDESTRIAN *pedestrian /*$a0*/, struct CAR_COLLISION_BOX *collision_box /*$a1*/)
{
}
/*
 * Offset 0x73390
 * D:\driver2\game\C\PEDEST.C (line 5344)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessChairLump(char *lump_file /*$a0*/, int lump_size /*$a1*/)
{
}
/*
 * Offset 0x7339C
 * D:\driver2\game\C\PLAYERS.C (line 130)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ ChangeCarPlayerToPed(int playerID /*$s0*/)
{ // line 1, offset 0x7339c
  struct _CAR_DATA *lcp; // $s2
} // line 51, offset 0x73574
/*
 * Offset 0x73574
 * D:\driver2\game\C\PLAYERS.C (line 184)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ ChangePedPlayerToCar(int playerID /*$s4*/, struct _CAR_DATA *newCar /*$s2*/)
{ // line 1, offset 0x73574
  struct _PLAYER *lPlayer; // $s1
  int siren; // $s5
  long *pos; // $s3
  int carParked; // $s6
} // line 60, offset 0x73900
/*
 * Offset 0x73900
 * D:\driver2\game\C\PLAYERS.C (line 247)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ UpdatePlayers()
{ // line 2, offset 0x73900
  struct _PLAYER *locPlayer; // $t0
  struct _CAR_DATA *cp; // $v1
} // line 39, offset 0x73a40
/*
 * Offset 0x73A40
 * D:\driver2\game\C\PLAYERS.C (line 75)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ InitPlayer(struct _PLAYER *locPlayer /*$s1*/, struct _CAR_DATA *cp /*$s2*/, char carCtrlType /*$s3*/, int direction /*$s6*/, long *startPos[4] /*stack 16*/, int externModel /*stack 20*/, int palette /*stack 24*/, char *padid /*stack 28*/)
{ // line 1, offset 0x73a40
} // line 52, offset 0x73c74
/*
 * Offset 0x73C74
 * D:\driver2\game\C\PLAYERS.C (line 298)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ RequestSlightPauseBeforeCarSoundStarts(char player_id /*$a0*/)
{
}
/*
 * Offset 0x73CBC
 * D:\driver2\game\C\PLAYERS.C (line 305)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ HaveCarSoundStraightAway(char player_id /*$a0*/)
{
}
/*
 * Offset 0x73CF4
 * D:\driver2\game\C\PLAYERS.C (line 310)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ MakeTheCarShutUp(char player_id /*$a0*/)
{
}
/*
 * Offset 0x73D30
 * D:\driver2\game\C\PRES.C (line 360)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ LoadFont(char *buffer /*$a0*/)
{ // line 1, offset 0x73d30
  struct RECT dest; // stack offset -24
  char *file; // $s1
  int i; // $v1
  int nchars; // $s0
} // line 48, offset 0x73f08
/*
 * Offset 0x73F08
 * D:\driver2\game\C\PRES.C (line 457)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ PrintString(char *string /*$s3*/, int x /*$s2*/, int y /*$s6*/)
{ // line 1, offset 0x73f08
  struct OUT_FONTINFO *pFontInfo; // $a1
  struct SPRT *font; // $s0
  unsigned char width; // $s1
  unsigned char c; // $s1
  int index; // $v1
} // line 79, offset 0x741a8
/*
 * Offset 0x741A8
 * D:\driver2\game\C\PRES.C (line 539)
 * Stack frame base $sp, size 8
 * Saved registers at offset -4: s0 s1
 */
short /*$ra*/ PrintDigit(int x /*$t3*/, int y /*$s1*/, char *string /*$a2*/)
{ // line 1, offset 0x741a8
  struct FONT_DIGIT *pDigit; // $a1
  struct SPRT *font; // $t0
  char width; // $a3
  char fixedWidth; // $t1
  char vOff; // $t2
  char h; // $a0
  { // line 13, offset 0x741f8
    char let; // $v1
    char convLet; // $a0
  } // line 44, offset 0x7425c
} // line 67, offset 0x743cc
/*
 * Offset 0x743CC
 * D:\driver2\game\C\PRES.C (line 643)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ PrintStringBoxed(char *string /*$s2*/, int ix /*$s5*/, int iy /*$a2*/)
{ // line 1, offset 0x743cc
  struct OUT_FONTINFO *pFontInfo; // $a1
  struct SPRT *font; // $s0
  char word[32]; // stack offset -64
  char *wpt; // $t0
  char c; // $a0
  int x; // $s1
  int y; // $s3
  int index; // $a1
  int wordcount; // $s4
} // line 68, offset 0x74644
/*
 * Offset 0x74644
 * D:\driver2\game\C\PRES.C (line 726)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ PrintScaledString(int y /*$s4*/, char *string /*$s1*/, int scale /*$s2*/)
{ // line 1, offset 0x74644
  struct FONT_DIGIT *pDigit; // $a2
  struct POLY_FT4 *font; // $t0
  int x; // $s0
  int width; // $t3
  int height; // $t6
  int y0; // $t1
  int x1; // $t5
  int y1; // $v0
  unsigned char vOff; // $t8
  char c; // $a0
} // line 68, offset 0x748c0
/*
 * Offset 0x748C0
 * D:\driver2\game\C\PRES.C (line 819)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void * /*$ra*/ DrawButton(unsigned char button /*$a0*/, void *prim /*$s1*/, int x /*$a2*/, int y /*$a3*/)
{ // line 1, offset 0x748c0
  struct TEXTURE_DETAILS *btn; // $a1
  struct POLY_FT3 *null; // $s0
} // line 34, offset 0x74a78
/*
 * Offset 0x74A78
 * D:\driver2\game\C\PRES.C (line 228)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetTextColour(unsigned char Red /*$a0*/, unsigned char Green /*$a1*/, unsigned char Blue /*$a2*/)
{
}
/*
 * Offset 0x74A8C
 * D:\driver2\game\C\PRES.C (line 245)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ StringWidth(char *pString /*$a0*/)
{ // line 1, offset 0x74a8c
  int w; // $a2
  char let; // $a1
  { // line 11, offset 0x74ac8
    char convLet; // $v1
  } // line 21, offset 0x74b00
} // line 24, offset 0x74b18
/*
 * Offset 0x74B18
 * D:\driver2\game\C\PRES.C (line 285)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ OutputString(char *pString /*$s2*/, int formatting /*$s0*/, int x /*$a2*/, int y /*$s3*/, int xw /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, offset 0x74b18
  int xpos; // $s1
  { // line 17, offset 0x74b7c
  } // line 17, offset 0x74b7c
} // line 38, offset 0x74bf4
/*
 * Offset 0x74BF4
 * D:\driver2\game\C\PRES.C (line 333)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ PrintStringRightAligned(char *pString /*$s1*/, int x /*$s0*/, int y /*$s2*/)
{
}
/*
 * Offset 0x74C40
 * D:\driver2\game\C\PRES.C (line 347)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ PrintStringCentred(char *pString /*$s1*/, short y /*$a1*/)
{ // line 1, offset 0x74c40
} // line 5, offset 0x74c90
/*
 * Offset 0x74C90
 * D:\driver2\game\C\PRES.C (line 416)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ StoreClut2(unsigned long *pDest /*$a1*/, int x /*$a1*/, int y /*$a2*/)
{ // line 1, offset 0x74c90
  struct RECT rect; // stack offset -16
} // line 10, offset 0x74ccc
/*
 * Offset 0x74CCC
 * D:\driver2\game\C\PRES.C (line 434)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SetCLUT16Flags(unsigned short clutID /*$a0*/, unsigned short mask /*$s2*/, char transparent /*$s0*/)
{ // line 1, offset 0x74ccc
  unsigned short buffer[16]; // stack offset -56
  unsigned short *pCurrent; // $a0
  char ctr; // $a1
  int x; // $s3
  int y; // $s1
} // line 21, offset 0x74d9c
/*
 * Offset 0x74D9C
 * D:\driver2\game\C\PRES.C (line 612)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ PrintStringFeature(char *string /*$a0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/, int transparent /*stack 20*/)
{
}
/*
 * Offset 0x74DBC
 * D:\driver2\game\C\PRES.C (line 800)
 * Stack frame base $sp, size 0
 */
char * /*$ra*/ GetNextWord(char *string /*$a0*/, char *word /*$a1*/)
{ // line 1, offset 0x74dbc
  char c; // $v1
} // line 17, offset 0x74dfc
/*
 * Offset 0x74DFC
 * D:\driver2\game\C\PRES.C (line 855)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void * /*$ra*/ SetFontTPage(void *prim /*$a0*/)
{ // line 1, offset 0x74dfc
  struct POLY_FT3 *null; // $s0
} // line 16, offset 0x74ebc
/*
 * Offset 0x74EBC
 * D:\driver2\game\C\PRES.C (line 713)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ InitButtonTextures()
{ // line 2, offset 0x74ebc
  int i; // $s0
} // line 6, offset 0x74f1c
/*
 * Offset 0x74F1C
 * D:\driver2\game\C\ROADBITS.C (line 147)
 * Stack frame base $sp, size 0
 */
char /*$ra*/ ROADS_GetRouteData(int x /*$a0*/, int z /*$a1*/, struct ROUTE_DATA *pRouteData /*$a2*/)
{
}
/*
 * Offset 0x74F28
 * D:\driver2\game\C\SCORES.C (line 58)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ InitialiseScoreTables()
{ // line 2, offset 0x74f28
  int i; // $s3
  int j; // $s1
} // line 26, offset 0x750a4
/*
 * Offset 0x750A4
 * D:\driver2\game\C\SCORES.C (line 86)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ OnScoreTable(struct SCORE_ENTRY **tablept /*$s1*/)
{ // line 1, offset 0x750a4
  struct SCORE_ENTRY *table; // $s0
  int position; // $v0
} // line 40, offset 0x75260
/*
 * Offset 0x75260
 * D:\driver2\game\C\SCORES.C (line 133)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ AddScoreToTable(struct SCORE_ENTRY *table /*$a2*/, int entry /*$a1*/)
{ // line 1, offset 0x75260
  int i; // $a3
} // line 16, offset 0x752d4
/*
 * Offset 0x752D4
 * D:\driver2\game\C\SCORES.C (line 162)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CheckGetawayPlacing(struct SCORE_ENTRY *table /*$a0*/)
{ // line 1, offset 0x752d4
  int i; // $v1
} // line 16, offset 0x75324
/*
 * Offset 0x75324
 * D:\driver2\game\C\SCORES.C (line 188)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CheckTrailblazerPlacing(struct SCORE_ENTRY *table /*$a0*/)
{ // line 1, offset 0x75324
  int i; // $a2
} // line 21, offset 0x753a0
/*
 * Offset 0x753A0
 * D:\driver2\game\C\SCORES.C (line 218)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CheckCheckpointPlacing(struct SCORE_ENTRY *table /*$a0*/)
{ // line 1, offset 0x753a0
  int i; // $v1
} // line 16, offset 0x753f0
/*
 * Offset 0x753F0
 * D:\driver2\game\C\SCORES.C (line 243)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CheckSurvivalPlacing(struct SCORE_ENTRY *table /*$a0*/)
{ // line 1, offset 0x753f0
  int i; // $v1
} // line 16, offset 0x75440
/*
 * Offset 0x75440
 * D:\driver2\game\C\SCORES.C (line 261)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ResetTable(struct SCORE_ENTRY *table /*$a0*/)
{ // line 1, offset 0x75440
  int i; // $v1
} // line 11, offset 0x75470
/*
 * Offset 0x75470
 * D:\driver2\game\C\SHADOW.C (line 272)
 * Stack frame base $sp, size 104
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ GetTyreTrackPositions(struct _CAR_DATA *cp /*$s3*/, int player_id /*$s7*/)
{ // line 1, offset 0x75470
  struct CAR_COSMETICS *car_cos; // $s4
  struct VECTOR WheelPos; // stack offset -88
  struct VECTOR target_pos; // stack offset -72
  struct VECTOR normal; // stack offset -56
  int loop; // $s2
  { // line 11, offset 0x754c0
  } // line 16, offset 0x754e8
} // line 26, offset 0x755a8
/*
 * Offset 0x755A8
 * D:\driver2\game\C\SHADOW.C (line 330)
 * Stack frame base $sp, size 200
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ AddTyreTrack(int wheel /*$s2*/, int tracksAndSmoke /*$s6*/, int padid /*$s0*/)
{ // line 1, offset 0x755a8
  struct VECTOR New1; // stack offset -168
  struct VECTOR New2; // stack offset -152
  struct VECTOR New3; // stack offset -136
  struct VECTOR New4; // stack offset -120
  struct VECTOR *old; // $s5
  struct VECTOR *newt; // $s3
  struct TYRE_TRACK *tt_p; // $s1
  int x; // $v1
  int z; // $a1
  int c; // $t1
  int s; // $t0
  unsigned int index; // $a2
  static int Cont[4]; // offset 0x0
  struct VECTOR psxoffset; // stack offset -104
  struct VECTOR SmokeDrift; // stack offset -88
  struct VECTOR SmokePosition; // stack offset -72
  char trackSurface; // $s0
  { // line 34, offset 0x75678
    struct ROUTE_DATA routeData; // stack offset -56
    struct _sdPlane *SurfaceDataPtr; // $v0
  } // line 69, offset 0x75704
  { // line 74, offset 0x75710
  } // line 81, offset 0x75738
  { // line 91, offset 0x75794
    struct VECTOR grass_vector; // stack offset -48
  } // line 91, offset 0x75794
} // line 176, offset 0x75a20
/*
 * Offset 0x75A48
 * D:\driver2\game\C\SHADOW.C (line 517)
 * Stack frame base $sp, size 136
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6
 */
void /*$ra*/ DrawTyreTracks()
{ // line 2, offset 0x75a48
  struct VECTOR p[4]; // stack offset -136
  struct SVECTOR ps[4]; // stack offset -72
  struct TYRE_TRACK *tt_p; // $t0
  int z; // stack offset -40
  int temp; // $a2
  int loop; // $t7
  int wheel_loop; // $s0
  int index; // $t2
  char last_duff; // $s1
  struct POLY_FT4 *poly; // $a3
  struct POLY_FT4 *lasttyre; // $t8
} // line 128, offset 0x75f9c
/*
 * Offset 0x75F9C
 * D:\driver2\game\C\SHADOW.C (line 659)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ InitShadow()
{ // line 2, offset 0x75f9c
  struct TPAN pos; // stack offset -16
  struct TEXINF *texinf; // $v0
  int i; // $a2
  int j; // $a3
  { // line 23, offset 0x760f8
  } // line 25, offset 0x760f8
} // line 38, offset 0x76170
/*
 * Offset 0x76170
 * D:\driver2\game\C\SHADOW.C (line 717)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SubdivShadow(long z0 /*$t7*/, long z1 /*$t9*/, long z2 /*$t8*/, long z3 /*$t6*/, struct POLY_FT4 *sps /*stack 16*/)
{ // line 1, offset 0x76170
  struct POLY_FT4 *spd; // $t3
  int i; // $t4
  { // line 18, offset 0x76220
    unsigned long A0; // $v1
    unsigned long A1; // $a1
    unsigned long E0; // $a3
    unsigned long E1; // $t0
    unsigned long C0; // $a0
    unsigned long C1; // $a2
    unsigned long B0; // $v1
    unsigned long B1; // $a1
    unsigned long D0; // $a0
    unsigned long D1; // $a2
  } // line 18, offset 0x76220
  { // line 18, offset 0x76220
    unsigned long A0; // $a1
    unsigned long A1; // $a2
    unsigned long E0; // $a3
    unsigned long E1; // $t0
    unsigned long C0; // $a0
    unsigned long C1; // $v1
    unsigned long B0; // $a1
    unsigned long B1; // $a2
    unsigned long D0; // $a0
    unsigned long D1; // $v1
  } // line 18, offset 0x76220
} // line 144, offset 0x76734
/*
 * Offset 0x76734
 * D:\driver2\game\C\SHADOW.C (line 864)
 * Stack frame base $sp, size 88
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ PlaceShadowForCar(struct VECTOR *shadowPoints /*$t0*/, int slot /*$s0*/, struct VECTOR *CarPos /*$a2*/, int zclip /*$a3*/)
{ // line 1, offset 0x76734
  struct SVECTOR points[4]; // stack offset -64
  long z; // $a0
  long z0; // stack offset -32
  long z1; // stack offset -28
  long z2; // stack offset -24
  long z3; // stack offset -20
  struct POLY_FT4 *spt; // $a3
} // line 69, offset 0x76aa8
/*
 * Offset 0x76AA8
 * D:\driver2\game\C\SHADOW.C (line 1038)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ clipAgainstZ()
{ // line 2, offset 0x76aa8
  int srccount; // $t4
  int dstcount; // $t5
  struct SVECTOR *current; // $t2
  struct SVECTOR *previous; // $t1
  struct SVECTOR *dst; // $a3
  int flags; // $t3
  { // line 19, offset 0x76b28
    int q; // $a2
  } // line 19, offset 0x76b28
  { // line 25, offset 0x76c20
    int q; // $a2
  } // line 25, offset 0x76c20
} // line 41, offset 0x76d3c
/*
 * Offset 0x76D3C
 * D:\driver2\game\C\SHADOW.C (line 1081)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ clippedPoly()
{ // line 2, offset 0x76d3c
  int i; // $a3
  int j; // $t0
  int z1; // $v1
  struct POLY_G3 *pg3; // $s0
  int z[3]; // stack offset -24
} // line 75, offset 0x77190
/*
 * Offset 0x771A0
 * D:\driver2\game\C\SHADOW.C (line 1160)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ sQuad(struct SVECTOR *v0 /*$a0*/, struct SVECTOR *v1 /*$s5*/, struct SVECTOR *v2 /*$s6*/, struct SVECTOR *v3 /*$s4*/)
{ // line 1, offset 0x771a0
  int z1; // $v0
  int z[4]; // stack offset -48
  { // line 8, offset 0x7721c
    struct POLY_G4 *pf4; // $t2
  } // line 30, offset 0x7731c
} // line 62, offset 0x7758c
/*
 * Offset 0x7758C
 * D:\driver2\game\C\SHADOW.C (line 253)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitTyreTracks()
{ // line 2, offset 0x7758c
  int loop; // $a0
} // line 9, offset 0x775c0
/*
 * Offset 0x775C0
 * D:\driver2\game\C\SHADOW.C (line 306)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetTyreTrackOldPositions(int player_id /*$a0*/)
{
}
/*
 * Offset 0x77630
 * D:\driver2\game\C\SKY.C (line 145)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ LoadSky()
{ // line 2, offset 0x77630
  struct RECT rect; // stack offset -96
  char name[16]; // stack offset -88
  int x; // $s6
  int y; // $a1
  int i; // $t1
  int u; // $v1
  int v; // $s2
  int skynum; // $a2
  int offset; // stack offset -72
  { // line 11, offset 0x77670
    int flipped; // $t0
    int single; // $s5
    int ry; // $a2
  } // line 113, offset 0x77838
} // line 174, offset 0x779c4
/*
 * Offset 0x779C4
 * D:\driver2\game\C\SKY.C (line 327)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DrawSkyDome()
{
}
/*
 * Offset 0x77AF4
 * D:\driver2\game\C\SKY.C (line 351)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DrawLensFlare()
{ // line 2, offset 0x77af4
  static char last_attempt_failed; // offset 0x0
  static short buffer[160]; // offset 0x0
  struct DVECTOR sun_pers_conv_position; // stack offset -64
  struct RECT source; // stack offset -56
  struct DR_MOVE *sample_sun; // $s0
  int distance_to_sun; // $s0
  int xpos; // $t1
  int ypos; // $v0
  int xgap; // $s4
  int ygap; // $s2
  int flarez; // stack offset -40
  int shade; // $t4
  int sun_intensity; // $s3
  struct POLY_FT4 *polys; // $a1
  struct CVECTOR col; // stack offset -48
  int r; // $a2
  int g; // $a3
  int b; // $a0
  { // line 36, offset 0x77bc0
    int bufferX; // $a0
    int bufferY; // $v1
    unsigned short *pwBuffer; // $s0
  } // line 54, offset 0x77c28
  { // line 95, offset 0x77d9c
    int temp; // $v0
    { // line 107, offset 0x77e38
      struct FLAREREC *pFlareInfo; // $t3
      int flaresize; // $t0
    } // line 144, offset 0x78014
  } // line 145, offset 0x78014
} // line 167, offset 0x78100
/*
 * Offset 0x78124
 * D:\driver2\game\C\SKY.C (line 527)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 s3
 */
void /*$ra*/ DisplaySun(struct DVECTOR *pos /*$a0*/, struct CVECTOR *col /*$a1*/, int flare_col /*$a2*/)
{ // line 1, offset 0x78124
  struct POLY_FT4 *polys; // $a1
  struct POLY_FT3 *null; // $a3
  struct VECTOR output; // stack offset -32
  int width; // $t5
  int height; // $t4
} // line 73, offset 0x785ac
/*
 * Offset 0x785AC
 * D:\driver2\game\C\SKY.C (line 609)
 * Stack frame base $sp, size 16
 */
void /*$ra*/ DisplayMoon(struct DVECTOR *pos /*$t4*/, struct CVECTOR *col /*$t6*/, int flip /*$a2*/)
{ // line 1, offset 0x785ac
  struct POLY_FT3 *null; // $a0
  struct VECTOR output; // stack offset -16
  int width; // $t5
  int height; // $t3
} // line 40, offset 0x78818
/*
 * Offset 0x78818
 * D:\driver2\game\C\SKY.C (line 679)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ TunnelSkyFade()
{ // line 2, offset 0x78818
  int tun; // $a3
  { // line 16, offset 0x78840
    int diffX; // $v1
    int diffZ; // $v0
    int dX; // $v1
    int dZ; // $v0
    int len; // $a1
    struct VECTOR *v1; // $t1
    struct VECTOR *v2; // $t0
    { // line 46, offset 0x788dc
      int l2; // $v1
    } // line 66, offset 0x78950
  } // line 97, offset 0x789c4
} // line 98, offset 0x789c4
/*
 * Offset 0x789CC
 * D:\driver2\game\C\SKY.C (line 785)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ calc_sky_brightness()
{
}
/*
 * Offset 0x78B80
 * D:\driver2\game\C\SKY.C (line 855)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ PlotSkyPoly(int skytexnum /*$t5*/, unsigned char r /*$a1*/, unsigned char g /*$a2*/, unsigned char b /*$a3*/, int offset /*stack 16*/)
{ // line 1, offset 0x78b80
  struct POLYFT4 *src; // $t1
  struct DVECTOR *outpoints; // $t0
  struct POLY_FT4 *prims; // $t2
} // line 39, offset 0x78f24
/*
 * Offset 0x78F2C
 * D:\driver2\game\C\SKY.C (line 896)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ PlotHorizonMDL(struct MODEL *model /*$s6*/, int horizontaboffset /*$a1*/)
{ // line 1, offset 0x78f2c
  struct SVECTOR *verts; // $v1
  char *polys; // $s1
  int i; // $s0
  int p; // stack offset -56
  int flag; // stack offset -52
  short *zbuff; // $t5
  int z; // stack offset -48
  unsigned char r; // $s5
  unsigned char g; // $s4
  unsigned char b; // $s3
} // line 49, offset 0x7911c
/*
 * Offset 0x7914C
 * D:\driver2\game\C\SOUND.C (line 114)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ InitSound()
{ // line 2, offset 0x7914c
  int ct; // $s0
} // line 47, offset 0x7923c
/*
 * Offset 0x7923C
 * D:\driver2\game\C\SOUND.C (line 163)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ClearChannelFields(int channel /*$a0*/)
{
}
/*
 * Offset 0x792B8
 * D:\driver2\game\C\SOUND.C (line 187)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ ResetSound()
{ // line 2, offset 0x792b8
  int ct; // $s0
} // line 35, offset 0x79398
/*
 * Offset 0x79398
 * D:\driver2\game\C\SOUND.C (line 399)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ CompleteSoundSetup(int channel /*$s2*/, int bank /*$s0*/, int sample /*$s5*/, int pitch /*$s1*/, int proximity /*stack 16*/)
{ // line 1, offset 0x79398
  long bpf; // $a1
  long rate; // $a1
} // line 44, offset 0x7956c
/*
 * Offset 0x7956C
 * D:\driver2\game\C\SOUND.C (line 450)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetChannelPitch(int channel /*$a0*/, int pitch /*$a1*/)
{ // line 1, offset 0x7956c
  long rate; // $a0
} // line 20, offset 0x7961c
/*
 * Offset 0x7962C
 * D:\driver2\game\C\SOUND.C (line 501)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ComputeDoppler(struct CHANNEL_DATA *ch /*$s1*/)
{ // line 1, offset 0x7962c
  int dist; // $s0
  int seperationrate; // $v0
  struct _PLAYER *pl; // $s0
} // line 26, offset 0x79788
/*
 * Offset 0x7979C
 * D:\driver2\game\C\SOUND.C (line 635)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ PauseXM()
{ // line 1, offset 0x7979c
  int fade; // $v1
} // line 20, offset 0x797fc
/*
 * Offset 0x797FC
 * D:\driver2\game\C\SOUND.C (line 657)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ PauseSFX()
{ // line 1, offset 0x797fc
  int i; // $s1
  int fade; // $s3
} // line 24, offset 0x799c0
/*
 * Offset 0x799C0
 * D:\driver2\game\C\SOUND.C (line 698)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ UnPauseXM()
{ // line 1, offset 0x799c0
  int fade; // $a1
} // line 19, offset 0x79a18
/*
 * Offset 0x79A18
 * D:\driver2\game\C\SOUND.C (line 720)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ UnPauseSFX()
{ // line 1, offset 0x79a18
  int i; // $s1
  int fade; // $s2
} // line 22, offset 0x79ba0
/*
 * Offset 0x79BA0
 * D:\driver2\game\C\SOUND.C (line 822)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SoundHandler()
{ // line 2, offset 0x79ba0
  int ct; // $a0
  long off; // $a1
} // line 16, offset 0x79c24
/*
 * Offset 0x79C34
 * D:\driver2\game\C\SOUND.C (line 904)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ LoadSoundBankDynamic(char *address /*$s2*/, int length /*$s6*/, int dbank /*$a2*/)
{ // line 1, offset 0x79c34
  static struct __LSBDinfo tabs; // offset 0x0
  int i; // $a3
  int num_samples; // $s1
  int slength; // $s0
} // line 73, offset 0x79e6c
/*
 * Offset 0x79E6C
 * D:\driver2\game\C\SOUND.C (line 1124)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ GetFreeChannel()
{ // line 1, offset 0x79e6c
  int ct; // $a0
  int least; // $s1
  int il; // $s0
  char status[24]; // stack offset -40
} // line 32, offset 0x79fa0
/*
 * Offset 0x79FA0
 * D:\driver2\game\C\SOUND.C (line 1163)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ UpdateVolumeAttributesS(int channel /*$s2*/, int proximity /*$s5*/)
{ // line 1, offset 0x79fa0
  int volume; // $s1
  int vol; // $a2
  long ang; // $s0
  long dist; // $s6
  int player_id; // $a3
  struct VECTOR *pos; // $s3
  struct VECTOR *cam_pos; // $s4
  int cam_ang; // $fp
  long damp; // $v1
  { // line 52, offset 0x7a21c
  } // line 54, offset 0x7a268
} // line 67, offset 0x7a398
/*
 * Offset 0x7A3C8
 * D:\driver2\game\C\SOUND.C (line 1257)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ CalculateVolume(int channel /*$a2*/)
{ // line 1, offset 0x7a3c8
  int volume; // $s0
  struct VECTOR *pp; // $a3
  { // line 9, offset 0x7a45c
    int distance; // $v1
    { // line 14, offset 0x7a45c
      struct VECTOR ofse; // stack offset -24
    } // line 17, offset 0x7a45c
    { // line 29, offset 0x7a514
      int fade; // $a0
    } // line 34, offset 0x7a56c
  } // line 36, offset 0x7a588
} // line 38, offset 0x7a59c
/*
 * Offset 0x7A59C
 * D:\driver2\game\C\SOUND.C (line 1326)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ FESound(int sample /*$s0*/)
{ // line 1, offset 0x7a59c
  long bpf; // $a1
  long rate; // $a1
  long pitch; // $s5
  int channel; // $s6
} // line 32, offset 0x7a728
/*
 * Offset 0x7A728
 * D:\driver2\game\C\SOUND.C (line 233)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetReverbState(int on /*$a0*/)
{
}
/*
 * Offset 0x7A76C
 * D:\driver2\game\C\SOUND.C (line 253)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetReverbInGameState(int on /*$a0*/)
{ // line 1, offset 0x7a76c
  long cl; // $a1
} // line 11, offset 0x7a7c4
/*
 * Offset 0x7A7C4
 * D:\driver2\game\C\SOUND.C (line 274)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ SetReverbChannelState(int ch /*$a0*/, int on /*$s0*/)
{ // line 1, offset 0x7a7c4
  long cl; // $s1
  int prev; // $s2
} // line 7, offset 0x7a818
/*
 * Offset 0x7A818
 * D:\driver2\game\C\SOUND.C (line 288)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetMasterVolume(int vol /*$a0*/)
{
}
/*
 * Offset 0x7A860
 * D:\driver2\game\C\SOUND.C (line 323)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ StartSound(int channel /*$a0*/, int bank /*$s1*/, int sample /*$s2*/, int volume /*$s0*/, int pitch /*stack 16*/)
{
}
/*
 * Offset 0x7A8FC
 * D:\driver2\game\C\SOUND.C (line 357)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ Start3DSoundVolPitch(int channel /*$s1*/, int bank /*$s0*/, int sample /*$s4*/, int x /*$s3*/, int y /*stack 16*/, int z /*stack 20*/, int volume /*stack 24*/, int pitch /*stack 28*/)
{
}
/*
 * Offset 0x7A9FC
 * D:\driver2\game\C\SOUND.C (line 342)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ Start3DTrackingSound(int channel /*$s1*/, int bank /*$s0*/, int sample /*$s3*/, struct VECTOR *position /*$s2*/, long *velocity /*stack 16*/)
{
}
/*
 * Offset 0x7AAE0
 * D:\driver2\game\C\SOUND.C (line 477)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ SetChannelVolume(int channel /*$s0*/, int volume /*$t1*/, int proximity /*$a2*/)
{ // line 1, offset 0x7aae0
} // line 18, offset 0x7ab8c
/*
 * Offset 0x7ABA4
 * D:\driver2\game\C\SOUND.C (line 1303)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ AllocateReverb(long mode /*$s1*/, long depth /*$s0*/)
{ // line 1, offset 0x7aba4
  struct SpuReverbAttr r_attr; // stack offset -40
} // line 16, offset 0x7abfc
/*
 * Offset 0x7AC10
 * D:\driver2\game\C\SOUND.C (line 307)
 * Stack frame base $sp, size 0
 */
char /*$ra*/ SetPlayerOwnsChannel(int chan /*$a0*/, char player /*$a1*/)
{ // line 1, offset 0x7ac10
} // line 5, offset 0x7ac34
/*
 * Offset 0x7AC34
 * D:\driver2\game\C\SOUND.C (line 588)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ SetChannelPosition3(int channel /*$s1*/, struct VECTOR *position /*$a0*/, long *velocity /*$t0*/, int volume /*$t2*/, int pitch /*stack 16*/, int proximity /*stack 20*/)
{ // line 1, offset 0x7ac34
} // line 24, offset 0x7ad28
/*
 * Offset 0x7AD40
 * D:\driver2\game\C\SOUND.C (line 683)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ PauseSound()
{
}
/*
 * Offset 0x7AD78
 * D:\driver2\game\C\SOUND.C (line 744)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ UnPauseSound()
{ // line 1, offset 0x7ad78
} // line 9, offset 0x7ada8
/*
 * Offset 0x7ADA8
 * D:\driver2\game\C\SOUND.C (line 760)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ StopChannel(int channel /*$s2*/)
{ // line 1, offset 0x7ada8
  { // line 3, offset 0x7adcc
    unsigned char l; // $s3
    int vsync; // $s0
  } // line 11, offset 0x7ae40
} // line 13, offset 0x7ae5c
/*
 * Offset 0x7AE5C
 * D:\driver2\game\C\SOUND.C (line 780)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ StopAllChannels()
{ // line 2, offset 0x7ae5c
  int ct; // $s0
} // line 10, offset 0x7ae9c
/*
 * Offset 0x7AE9C
 * D:\driver2\game\C\SOUND.C (line 797)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ LockChannel(int channel /*$a0*/)
{
}
/*
 * Offset 0x7AECC
 * D:\driver2\game\C\SOUND.C (line 811)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ UnlockChannel(int c /*$a0*/)
{
}
/*
 * Offset 0x7AEF8
 * D:\driver2\game\C\SOUND.C (line 845)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ LoadSoundBank(char *address /*$s3*/, int length /*$s2*/, int bank /*$s1*/)
{ // line 1, offset 0x7aef8
  int num_samples; // $s4
  int slength; // $s2
  int spuaddress; // $s1
  int ct; // $v1
} // line 31, offset 0x7afec
/*
 * Offset 0x7AFEC
 * D:\driver2\game\C\SOUND.C (line 993)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ FreeXM()
{
}
/*
 * Offset 0x7B038
 * D:\driver2\game\C\SOUND.C (line 1012)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ StartXM(int reverb /*$s2*/)
{ // line 1, offset 0x7b038
  int ct; // $s0
} // line 16, offset 0x7b0b8
/*
 * Offset 0x7B0B8
 * D:\driver2\game\C\SOUND.C (line 1035)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ StopXM()
{
}
/*
 * Offset 0x7B0DC
 * D:\driver2\game\C\SOUND.C (line 1073)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetXMVolume(int volume /*$a0*/)
{ // line 1, offset 0x7b0dc
  int vol; // $a1
} // line 12, offset 0x7b12c
/*
 * Offset 0x7B12C
 * D:\driver2\game\C\SOUND.C (line 1232)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ UpdateVolumeAttributesM(int channel /*$s0*/)
{ // line 1, offset 0x7b12c
  int volume; // $a1
  int vol; // $a0
} // line 17, offset 0x7b1e0
/*
 * Offset 0x7B1E0
 * D:\driver2\game\C\SOUND.C (line 1371)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ VsyncProc()
{
}
/*
 * Offset 0x7B22C
 * D:\driver2\game\C\SOUND.C (line 882)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ UpdateXMSamples(int num_samps /*$s2*/)
{ // line 1, offset 0x7b22c
  int i; // $s0
} // line 6, offset 0x7b290
/*
 * Offset 0x7B290
 * D:\driver2\game\C\SPOOL.C (line 532)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ test_changemode()
{ // line 2, offset 0x7b290
  struct SPOOLQ *current; // $a3
} // line 56, offset 0x7b41c
/*
 * Offset 0x7B42C
 * D:\driver2\game\C\SPOOL.C (line 625)
 * Stack frame base $sp, size 160
 * Saved registers at offset -8: s0
 */
int /*$ra*/ check_regions_present()
{ // line 2, offset 0x7b42c
  struct AREA_LOAD_INFO regions_to_unpack[3]; // stack offset -160
  int leftright_unpack; // $a2
  int topbottom_unpack; // $a3
  int num_regions_to_unpack; // $a1
  int x; // $v1
  int z; // $v0
  int loop; // $t1
  int retval; // $a3
  int region_to_unpack; // $a0
  int barrel_region; // $v1
  char textbuf[128]; // stack offset -136
} // line 146, offset 0x7b72c
/*
 * Offset 0x7B72C
 * D:\driver2\game\C\SPOOL.C (line 925)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ UpdateSpool()
{ // line 2, offset 0x7b72c
  struct SPOOLQ *current; // $s0
  struct CdlLOC pos; // stack offset -16
} // line 52, offset 0x7b8e4
/*
 * Offset 0x7B8F4
 * D:\driver2\game\C\SPOOL.C (line 1161)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SendTPage()
{ // line 2, offset 0x7b8f4
  int tpage2send; // $s2
  int slot; // $s0
  int old; // $v1
  char *tpageaddress; // $t0
  { // line 15, offset 0x7b968
    struct RECT cluts; // stack offset -32
    int npalettes; // $s1
    int i; // $a3
    unsigned long *clutptr; // $a1
  } // line 47, offset 0x7ba8c
} // line 74, offset 0x7bb7c
/*
 * Offset 0x7BB7C
 * D:\driver2\game\C\SPOOL.C (line 1262)
 * Stack frame base $sp, size 128
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ LoadInAreaTSets(int area /*$t4*/)
{ // line 1, offset 0x7bb7c
  unsigned char *tpages; // $s1
  int ntpages_to_load; // $s3
  int i; // $s0
  int slot; // $a0
  int j; // $a1
  int offset; // $s4
  int availableslots[16]; // stack offset -104
  int navailable; // $s2
  char *loadaddr; // $fp
} // line 71, offset 0x7bdec
/*
 * Offset 0x7BDEC
 * D:\driver2\game\C\SPOOL.C (line 1337)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ SendSBK()
{ // line 2, offset 0x7bdec
  char *address; // $s0
  int slength; // $s1
  int i; // $a1
  unsigned long *source; // $v0
  unsigned long *dest; // $a0
} // line 43, offset 0x7bf24
/*
 * Offset 0x7BF24
 * D:\driver2\game\C\SPOOL.C (line 1484)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ init_spooled_models()
{ // line 2, offset 0x7bf24
  int i; // $s1
  int nmodels; // $s4
  int size; // $s2
  int model_number; // $a1
  char *addr; // $s0
  struct MODEL *parentmodel; // $a1
  { // line 35, offset 0x7c024
  } // line 37, offset 0x7c038
  { // line 44, offset 0x7c06c
  } // line 52, offset 0x7c0b0
} // line 59, offset 0x7c0f4
/*
 * Offset 0x7C0F4
 * D:\driver2\game\C\SPOOL.C (line 1574)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ CheckLoadAreaData(int cellx /*$t9*/, int cellz /*$a1*/)
{ // line 1, offset 0x7c0f4
  int i; // $a2
  int nAreas; // $t0
  struct Spool *spoolptr; // $t1
  int load; // $a3
  int force_load_boundary; // $a0
} // line 92, offset 0x7c2e4
/*
 * Offset 0x7C2F4
 * D:\driver2\game\C\SPOOL.C (line 1713)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ LoadRegionData(int region /*$s4*/, int target_region /*$s5*/)
{ // line 1, offset 0x7c2f4
  int offset; // $s0
  char *target_unpacked_data; // $t1
  struct Spool *spoolptr; // $s1
  char *roadmap_buffer; // $s6
  char *cell_buffer; // $s3
} // line 63, offset 0x7c4cc
/*
 * Offset 0x7C4CC
 * D:\driver2\game\C\SPOOL.C (line 1815)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessSpoolInfoLump(char *lump_ptr /*$a2*/, int lump_size /*$a1*/)
{ // line 1, offset 0x7c4cc
  int i; // $t2
  int size; // $v1
  int slots_count; // $t0
  int objects_count; // $t1
  int num_of_regions; // $v0
  char *alloclist; // $a3
} // line 103, offset 0x7c628
/*
 * Offset 0x7C628
 * D:\driver2\game\C\SPOOL.C (line 2351)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ unpack_cellpointers()
{ // line 2, offset 0x7c628
  int target_barrel_region; // $t0
  char *source_packed_data; // $v0
  int bitpos; // $a3
  int loop; // $a2
  int packtype; // $a0
  unsigned short cell; // $a0
  unsigned short *short_ptr; // $a1
  unsigned short pcode; // $t1
} // line 86, offset 0x7c7b4
/*
 * Offset 0x7C7B4
 * D:\driver2\game\C\SPOOL.C (line 2509)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SpecClutsSpooled()
{ // line 2, offset 0x7c7b4
  char *loadaddr; // $s4
  int i; // $s1
  int j; // $s2
  int tpage; // $s0
  struct RECT specCluts; // stack offset -48
  { // line 13, offset 0x7c85c
    int index; // $a3
    { // line 28, offset 0x7c984
    } // line 28, offset 0x7c984
  } // line 33, offset 0x7c9c4
} // line 37, offset 0x7ca20
/*
 * Offset 0x7CA20
 * D:\driver2\game\C\SPOOL.C (line 2549)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ CleanModelSpooled()
{ // line 3, offset 0x7ca20
  int *loadaddr; // $a1
  int *mem; // $a3
  { // line 27, offset 0x7cae8
  } // line 38, offset 0x7cb38
} // line 42, offset 0x7cb64
/*
 * Offset 0x7CB64
 * D:\driver2\game\C\SPOOL.C (line 2594)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DamagedModelSpooled()
{ // line 2, offset 0x7cb64
  int *loadaddr; // $a1
  int *mem; // $a3
  { // line 26, offset 0x7cc28
  } // line 35, offset 0x7cc60
} // line 39, offset 0x7cc8c
/*
 * Offset 0x7CC8C
 * D:\driver2\game\C\SPOOL.C (line 2635)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ LowModelSpooled()
{ // line 2, offset 0x7cc8c
  int *loadaddr; // $a1
  int *mem; // $a3
  { // line 26, offset 0x7cd50
  } // line 37, offset 0x7cda0
} // line 41, offset 0x7cdcc
/*
 * Offset 0x7CDCC
 * D:\driver2\game\C\SPOOL.C (line 2680)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ CleanSpooled()
{ // line 3, offset 0x7cdcc
  char *loadaddr; // $a1
  { // line 22, offset 0x7cef4
    struct MODEL *tempModel; // $a1
  } // line 33, offset 0x7cf48
} // line 37, offset 0x7cf74
/*
 * Offset 0x7CF74
 * D:\driver2\game\C\SPOOL.C (line 2744)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ Tada()
{ // line 2, offset 0x7cf74
  char *loadaddr; // $s1
  { // line 7, offset 0x7cfc8
    struct RECT tpage; // stack offset -32
    int spec_tpage; // $a0
  } // line 20, offset 0x7d080
  { // line 23, offset 0x7d080
    struct RECT tpage; // stack offset -24
    int spec_tpage; // $a0
  } // line 36, offset 0x7d154
  { // line 39, offset 0x7d154
  } // line 45, offset 0x7d198
} // line 49, offset 0x7d1ac
/*
 * Offset 0x7D1AC
 * D:\driver2\game\C\SPOOL.C (line 2799)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SpecialStartNextBlock()
{ // line 2, offset 0x7d1ac
  char *loadaddr; // $s0
  int fileSector; // $t0
} // line 126, offset 0x7d538
/*
 * Offset 0x7D548
 * D:\driver2\game\C\SPOOL.C (line 2956)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ CheckSpecialSpool()
{ // line 2, offset 0x7d548
  struct _CAR_DATA *lcp; // $a0
  int ret; // $a3
  { // line 9, offset 0x7d584
  } // line 13, offset 0x7d5a4
} // line 66, offset 0x7d730
/*
 * Offset 0x7D740
 * D:\driver2\game\C\SPOOL.C (line 3063)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InitSpecSpool()
{
}
/*
 * Offset 0x7D9E0
 * D:\driver2\game\C\SPOOL.C (line 2442)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ Unpack_CellPtrs()
{ // line 2, offset 0x7d9e0
  int region_to_unpack; // $a1
  int target_barrel_region; // $a1
  char *source_packed_data; // $v1
} // line 27, offset 0x7da34
/*
 * Offset 0x7DA34
 * D:\driver2\game\C\SPOOL.C (line 1970)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ GotRegion()
{ // line 2, offset 0x7da34
  int cbr; // $a1
} // line 20, offset 0x7dac8
/*
 * Offset 0x7DAC8
 * D:\driver2\game\C\SPOOL.C (line 2246)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ data_cb_misc()
{ // line 2, offset 0x7dac8
  { // line 4, offset 0x7dadc
    struct SPOOLQ *current; // $v0
  } // line 29, offset 0x7db90
} // line 30, offset 0x7dba0
/*
 * Offset 0x7DBA0
 * D:\driver2\game\C\SPOOL.C (line 2278)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ready_cb_misc(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
{
}
/*
 * Offset 0x7DC34
 * D:\driver2\game\C\SPOOL.C (line 2171)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ data_cb_soundbank()
{ // line 2, offset 0x7dc34
  { // line 4, offset 0x7dc48
  } // line 29, offset 0x7dcfc
} // line 30, offset 0x7dd0c
/*
 * Offset 0x7DD0C
 * D:\driver2\game\C\SPOOL.C (line 2203)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ready_cb_soundbank(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
{ // line 1, offset 0x7dd0c
  { // line 14, offset 0x7dd6c
    struct SPOOLQ *current; // $a0
  } // line 34, offset 0x7ddd8
} // line 41, offset 0x7de00
/*
 * Offset 0x7DE10
 * D:\driver2\game\C\SPOOL.C (line 2132)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ data_cb_regions()
{ // line 2, offset 0x7de10
  { // line 4, offset 0x7de24
    struct SPOOLQ *current; // $v0
  } // line 35, offset 0x7dee8
} // line 36, offset 0x7def8
/*
 * Offset 0x7DEF8
 * D:\driver2\game\C\SPOOL.C (line 2090)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ready_cb_regions(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
{ // line 1, offset 0x7def8
  { // line 20, offset 0x7df70
    struct SPOOLQ *current; // $v1
  } // line 20, offset 0x7df70
} // line 39, offset 0x7dfcc
/*
 * Offset 0x7DFCC
 * D:\driver2\game\C\SPOOL.C (line 1993)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ data_cb_textures()
{ // line 2, offset 0x7dfcc
  { // line 4, offset 0x7dfe0
  } // line 40, offset 0x7e0d0
} // line 41, offset 0x7e0e0
/*
 * Offset 0x7E0E0
 * D:\driver2\game\C\SPOOL.C (line 2036)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ready_cb_textures(unsigned char intr /*$s0*/, unsigned char *result /*$a2*/)
{ // line 1, offset 0x7e0e0
  { // line 14, offset 0x7e140
    struct SPOOLQ *current; // $a2
  } // line 44, offset 0x7e1f0
} // line 50, offset 0x7e200
/*
 * Offset 0x7E210
 * D:\driver2\game\C\SPOOL.C (line 591)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ changemode(struct SPOOLQ *current /*$a0*/)
{
}
/*
 * Offset 0x7E2B4
 * D:\driver2\game\C\SPOOL.C (line 836)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DrawCDicon()
{ // line 2, offset 0x7e2b4
  unsigned short *palette; // $a1
  int temp; // $a2
  int i; // $a0
  struct RECT dest; // stack offset -16
} // line 20, offset 0x7e334
/*
 * Offset 0x7E334
 * D:\driver2\game\C\SPOOL.C (line 859)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ CheckValidSpoolData()
{ // line 2, offset 0x7e334
  struct RECT dest; // stack offset -16
} // line 59, offset 0x7e3c4
/*
 * Offset 0x7E3D4
 * D:\driver2\game\C\SPOOL.C (line 1104)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ RequestSpool(int type /*$a0*/, int data /*$a1*/, int offset /*$a2*/, int loadsize /*$a3*/, char *address /*stack 16*/, void (*func)() /*stack 20*/)
{ // line 1, offset 0x7e3d4
  struct SPOOLQ *next; // $t0
  int sector; // $v0
} // line 22, offset 0x7e44c
/*
 * Offset 0x7E44C
 * D:\driver2\game\C\SPOOL.C (line 1670)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ClearRegion(int target_region /*$a0*/)
{ // line 1, offset 0x7e44c
  int loop; // $a1
  unsigned short *cell_ptrs_s; // $v1
  unsigned long *pvsptr; // $v0
} // line 41, offset 0x7e4fc
/*
 * Offset 0x7E4FC
 * D:\driver2\game\C\SPOOL.C (line 1129)
 * Stack frame base $sp, size 168
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ InitSpooling()
{ // line 2, offset 0x7e4fc
  int i; // $s0
  char namebuffer[128]; // stack offset -152
  struct CdlLOC pos; // stack offset -24
} // line 29, offset 0x7e590
/*
 * Offset 0x7E590
 * D:\driver2\game\C\SPOOL.C (line 1239)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SpoolSYNC()
{
}
/*
 * Offset 0x7E5A8
 * D:\driver2\game\C\SPOOL.C (line 1545)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetupModels()
{
}
/*
 * Offset 0x7E5E8
 * D:\driver2\game\C\SPOOL.C (line 1559)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ LoadInAreaModels(int area /*$a0*/)
{ // line 2, offset 0x7e5e8
  int offset; // $a2
  int length; // $a3
} // line 12, offset 0x7e644
/*
 * Offset 0x7E644
 * D:\driver2\game\C\SPOOL.C (line 1779)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ UnpackRegion(int region_to_unpack /*$s1*/, int target_barrel_region /*$s0*/)
{ // line 1, offset 0x7e644
} // line 33, offset 0x7e6c0
/*
 * Offset 0x7E6D4
 * D:\driver2\game\C\SPOOL.C (line 1928)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ WaitCloseLid()
{ // line 2, offset 0x7e6d4
  void (*old)(); // $s1
} // line 14, offset 0x7e740
/*
 * Offset 0x7E740
 * D:\driver2\game\C\SPOOL.C (line 1945)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ FoundError(char *name /*$a0*/, unsigned char intr /*$a1*/, unsigned char *result /*$a2*/)
{ // line 2, offset 0x7e740
  struct CdlLOC p; // stack offset -16
} // line 18, offset 0x7e78c
/*
 * Offset 0x7E78C
 * D:\driver2\game\C\SPOOL.C (line 2302)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ StartSpooling()
{ // line 2, offset 0x7e78c
} // line 19, offset 0x7e818
/*
 * Offset 0x7E828
 * D:\driver2\game\C\SPOOL.C (line 2720)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ LowSpooled()
{ // line 3, offset 0x7e828
  char *loadaddr; // $v1
  { // line 8, offset 0x7e840
    struct MODEL *tempModel; // $a1
  } // line 17, offset 0x7e888
} // line 21, offset 0x7e8b4
/*
 * Offset 0x7E8B4
 * D:\driver2\game\C\SPOOL.C (line 3025)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ QuickSpoolSpecial()
{
}
/*
 * Offset 0x7E944
 * D:\driver2\game\C\SPOOL.C (line 3046)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ PrepareSecretCar()
{
}
/*
 * Offset 0x7E9C0
 * D:\driver2\game\C\SPOOL.C (line 818)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ stopgame()
{ // line 4, offset 0x7e9c0
} // line 9, offset 0x7ea08
/*
 * Offset 0x7EA08
 * D:\driver2\game\C\SPOOL.C (line 829)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ startgame()
{ // line 2, offset 0x7ea08
} // line 4, offset 0x7ea38
/*
 * Offset 0x7EA38
 * D:\driver2\game\C\SYSTEM.C (line 759)
 * Stack frame base $sp, size 2208
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ LoadfileSeg(char *name /*$v0*/, char *addr /*$s1*/, int offset /*$s5*/, int loadsize /*$fp*/)
{ // line 1, offset 0x7ea38
  char namebuffer[64]; // stack offset -2192
  unsigned char result[8]; // stack offset -2128
  int sector; // $s2
  int nsectors; // $s5
  char sectorbuffer[2048]; // stack offset -2120
  struct CdlFILE info; // stack offset -72
  struct CdlLOC pos; // stack offset -48
  int i; // $a2
  int toload; // $s4
  int first; // $a0
} // line 120, offset 0x7ed58
/*
 * Offset 0x7ED58
 * D:\driver2\game\C\SYSTEM.C (line 1310)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SwapDrawBuffers2(int player /*$s0*/)
{ // line 1, offset 0x7ed58
  int toggle; // $v1
} // line 30, offset 0x7ee44
/*
 * Offset 0x7EE44
 * D:\driver2\game\C\SYSTEM.C (line 1364)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ SetupDrawBuffers()
{ // line 2, offset 0x7ee44
  struct RECT rect; // stack offset -24
  int i; // $v1
} // line 47, offset 0x7ef74
/*
 * Offset 0x7EF74
 * D:\driver2\game\C\SYSTEM.C (line 1429)
 * Stack frame base $sp, size 96
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ SetupDrawBufferData(int num_players /*stack 0*/)
{ // line 1, offset 0x7ef74
  unsigned long *otpt; // $s2
  unsigned char *primpt; // $s1
  unsigned char *PRIMpt; // $fp
  int x[2]; // stack offset -72
  int y[2]; // stack offset -64
  int i; // $s3
  int j; // $s6
  int toggle; // $s7
  int height; // stack offset -56
} // line 94, offset 0x7f180
/*
 * Offset 0x7F180
 * D:\driver2\game\C\SYSTEM.C (line 1577)
 * Stack frame base $sp, size 136
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SetCityType(enum CITYTYPE type /*$a0*/)
{ // line 1, offset 0x7f180
  struct CdlFILE cdfile; // stack offset -120
  struct XYPAIR *info; // $s2
  char namebuffer[64]; // stack offset -96
  unsigned char result[8]; // stack offset -32
  int i; // $a2
  int sector; // $s0
} // line 78, offset 0x7f3a0
/*
 * Offset 0x7F3BC
 * D:\driver2\game\C\SYSTEM.C (line 646)
 * Stack frame base $sp, size 104
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ Loadfile(char *name /*$a2*/, char *addr /*$s2*/)
{ // line 1, offset 0x7f3bc
  char namebuffer[64]; // stack offset -88
  unsigned char result[8]; // stack offset -24
  int nread; // $s0
} // line 24, offset 0x7f450
/*
 * Offset 0x7F450
 * D:\driver2\game\C\SYSTEM.C (line 389)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ClearMem(char *mem /*$a0*/, int size /*$a1*/)
{ // line 1, offset 0x7f450
  char *end; // $v1
} // line 27, offset 0x7f4e4
/*
 * Offset 0x7F4E4
 * D:\driver2\game\C\SYSTEM.C (line 427)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ setMem8(unsigned char *mem /*$a0*/, unsigned char val /*$a1*/, int size /*$a2*/)
{ // line 1, offset 0x7f4e4
  unsigned char *end; // $v1
  unsigned long lval; // $a3
} // line 32, offset 0x7f58c
/*
 * Offset 0x7F58C
 * D:\driver2\game\C\SYSTEM.C (line 469)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ setMem16(unsigned short *mem /*$a0*/, unsigned short val /*$a1*/, int size /*$a2*/)
{ // line 1, offset 0x7f58c
  unsigned short *end; // $a3
  unsigned long lval; // $a2
} // line 26, offset 0x7f61c
/*
 * Offset 0x7F61C
 * D:\driver2\game\C\SYSTEM.C (line 1566)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ResetCityType()
{
}
/*
 * Offset 0x7F630
 * D:\driver2\game\C\SYSTEM.C (line 1682)
 * Stack frame base $sp, size 192
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ FileExists(char *filename /*$a2*/)
{ // line 1, offset 0x7f630
  struct CdlFILE cdfile; // stack offset -176
  char namebuffer[128]; // stack offset -152
  unsigned char result[8]; // stack offset -24
  int retries; // $s1
} // line 26, offset 0x7f6a8
/*
 * Offset 0x7F6A8
 * D:\driver2\game\C\SYSTEM.C (line 1723)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 ra
 */
enum CDTYPE /*$ra*/ DiscSwapped(char *filename /*$s1*/)
{ // line 1, offset 0x7f6a8
  struct CdlFILE cdfile; // stack offset -40
  int ret; // $v1
} // line 39, offset 0x7f764
/*
 * Offset 0x7F764
 * D:\driver2\game\C\SYSTEM.C (line 1253)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SwapDrawBuffers()
{ // line 2, offset 0x7f764
} // line 50, offset 0x7f828
/*
 * Offset 0x7F828
 * D:\driver2\game\C\SYSTEM.C (line 1535)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ InitaliseDrawEnv(struct DB *pBuff /*$s0*/, int x /*$s4*/, int y /*$s3*/, int w /*$s1*/, int h /*stack 16*/)
{
}
/*
 * Offset 0x7F8B0
 * D:\driver2\game\C\SYSTEM.C (line 580)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ Init_FileSystem()
{
}
/*
 * Offset 0x7F8D8
 * D:\driver2\game\C\SYSTEM.C (line 622)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DoCDRetry()
{ // line 2, offset 0x7f8d8
  static int retries; // offset 0xc
  unsigned char result[8]; // stack offset -16
} // line 11, offset 0x7f920
/*
 * Offset 0x7F920
 * D:\driver2\game\C\SYSTEM.C (line 952)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ReportMode(int on /*$s0*/)
{ // line 1, offset 0x7f920
  static unsigned char param[8]; // offset 0x0
} // line 15, offset 0x7f95c
/*
 * Offset 0x7F96C
 * D:\driver2\game\C\SYSTEM.C (line 1017)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ loadsectors(char *addr /*$a0*/, int sector /*$v0*/, int nsectors /*$a2*/)
{ // line 1, offset 0x7f96c
  struct CdlLOC pos; // stack offset -16
} // line 18, offset 0x7f9ec
/*
 * Offset 0x7F9EC
 * D:\driver2\game\C\SYSTEM.C (line 1221)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ EnableDisplay()
{ // line 2, offset 0x7f9ec
  int i; // $s1
} // line 9, offset 0x7fa58
/*
 * Offset 0x7FA58
 * D:\driver2\game\C\SYSTEM.C (line 1239)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DisableDisplay()
{
}
/*
 * Offset 0x7FA78
 * D:\driver2\game\C\SYSTEM.C (line 1349)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ UpdatePadData()
{
}
/*
 * Offset 0x7FAAC
 * D:\driver2\game\C\SYSTEM.C (line 978)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ data_ready()
{
}
/*
 * Offset 0x7FADC
 * D:\driver2\game\C\SYSTEM.C (line 987)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ sector_ready(unsigned char intr /*$a0*/, unsigned char *result /*$a1*/)
{ // line 1, offset 0x7fadc
  { // line 17, offset 0x7fb4c
    struct CdlLOC p; // stack offset -16
  } // line 27, offset 0x7fb9c
} // line 28, offset 0x7fbac
/*
 * Offset 0x7FBAC
 * D:\driver2\game\C\TARGETS.C (line 213)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ Draw3DTarget(struct VECTOR *position /*$s0*/, int flags /*$s2*/)
{ // line 1, offset 0x7fbac
  struct VECTOR pos; // stack offset -32
  int shadow; // $s1
} // line 49, offset 0x7fdb0
/*
 * Offset 0x7FDB0
 * D:\driver2\game\C\TARGETS.C (line 267)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DrawTargetArrowModel(struct TARGET_ARROW_MODEL *pTargetArrowModel /*$s1*/, struct VECTOR *pPosition /*$s2*/, int shadow /*$s4*/, int invert /*$s3*/)
{ // line 1, offset 0x7fdb0
  { // line 4, offset 0x7fe04
    struct VECTOR tempVec; // stack offset -56
    struct SVECTOR *pVerts; // $s0
    struct SVECTOR temp; // stack offset -40
    char *pVertIndex; // $a3
    { // line 16, offset 0x7fe94
      struct POLY_F3 *poly; // $t0
      int z; // stack offset -32
    } // line 56, offset 0x800ac
  } // line 62, offset 0x80140
} // line 63, offset 0x80160
/*
 * Offset 0x80160
 * D:\driver2\game\C\TARGETS.C (line 412)
 * Stack frame base $sp, size 144
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawStopZone(struct VECTOR *pPosition /*$s5*/)
{ // line 1, offset 0x80160
  struct VECTOR *pVector; // $s0
  struct VECTOR pStopZonePt[4]; // stack offset -128
  struct POLY_FT4 *pPoly; // $s1
  long *pOut; // $s2
  long sz; // stack offset -48
  { // line 18, offset 0x80264
    struct SVECTOR temp; // stack offset -64
    long p; // stack offset -56
    long flag; // stack offset -52
  } // line 53, offset 0x80374
} // line 77, offset 0x804e4
/*
 * Offset 0x804E4
 * D:\driver2\game\C\TARGETS.C (line 496)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ WorldToCameraPositions(struct VECTOR *pGlobalPositionIn /*$s1*/, struct VECTOR *pCameraPositionOut /*$s0*/, int count /*$s2*/)
{ // line 1, offset 0x804e4
  { // line 4, offset 0x80520
    struct VECTOR temp; // stack offset -48
  } // line 6, offset 0x80520
} // line 15, offset 0x80590
/*
 * Offset 0x80590
 * D:\driver2\game\C\TEXTURE.C (line 126)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ IncrementTPageNum(struct RECT *tpage /*$t0*/)
{ // line 1, offset 0x80590
  int i; // $a3
} // line 27, offset 0x80654
/*
 * Offset 0x80654
 * D:\driver2\game\C\TEXTURE.C (line 191)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ Find_TexID(struct MODEL *model /*$t0*/, int t_id /*$a1*/)
{ // line 1, offset 0x80654
  char *polylist; // $a2
  int i; // $a3
  { // line 12, offset 0x806a0
  } // line 15, offset 0x806b8
  { // line 18, offset 0x806b8
  } // line 21, offset 0x806b8
  { // line 24, offset 0x806b8
  } // line 27, offset 0x806b8
  { // line 31, offset 0x806b8
  } // line 34, offset 0x806b8
  { // line 38, offset 0x806b8
  } // line 41, offset 0x806b8
  { // line 44, offset 0x806b8
  } // line 47, offset 0x806b8
  { // line 50, offset 0x806b8
  } // line 53, offset 0x806b8
  { // line 56, offset 0x806b8
  } // line 59, offset 0x806b8
} // line 67, offset 0x806f0
/*
 * Offset 0x806F0
 * D:\driver2\game\C\TEXTURE.C (line 378)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ LoadPermanentTPages(int *sector /*$fp*/)
{ // line 1, offset 0x806f0
  int tloop; // $s1
  int i; // $s1
  int tset; // $s0
  int nsectors; // $s3
  char *tpagebuffer; // $s2
  { // line 67, offset 0x80944
    int specmodel; // $a1
    int page1; // $s6
    int page2; // $s5
    { // line 87, offset 0x809ec
      int temp; // $s4
      int clutsLoaded; // $s7
    } // line 126, offset 0x80b40
  } // line 127, offset 0x80b40
} // line 197, offset 0x80c18
/*
 * Offset 0x80C18
 * D:\driver2\game\C\TEXTURE.C (line 602)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ GetTextureDetails(char *name /*stack 0*/, struct TEXTURE_DETAILS *info /*$s3*/)
{ // line 1, offset 0x80c18
  int i; // $s2
  int j; // $s1
  int texamt; // $s4
  struct TEXINF *texinf; // $v1
  char *nametable; // stack offset -56
} // line 45, offset 0x80dd8
/*
 * Offset 0x80E08
 * D:\driver2\game\C\TEXTURE.C (line 290)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
struct TEXINF * /*$ra*/ GetTextureInfoName(char *name /*$a0*/, struct TPAN *result /*$s0*/)
{ // line 1, offset 0x80e08
  int tpagenum; // stack offset -16
  int texturenum; // stack offset -12
} // line 10, offset 0x80e44
/*
 * Offset 0x80E44
 * D:\driver2\game\C\TEXTURE.C (line 116)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ IncrementClutNum(struct RECT *clut /*$a0*/)
{
}
/*
 * Offset 0x80E7C
 * D:\driver2\game\C\TEXTURE.C (line 155)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ LoadTPageAndCluts(struct RECT *tpage /*$s5*/, struct RECT *cluts /*$s2*/, int tpage2send /*$s6*/, char *tpageaddress /*$s0*/)
{ // line 1, offset 0x80e7c
  int i; // $s3
  int npalettes; // $s4
  struct RECT temptpage; // stack offset -40
} // line 30, offset 0x80fa4
/*
 * Offset 0x80FA4
 * D:\driver2\game\C\TEXTURE.C (line 261)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
struct TEXINF * /*$ra*/ GetTEXINFName(char *name /*$fp*/, int *tpagenum /*stack 4*/, int *texturenum /*stack 8*/)
{ // line 1, offset 0x80fa4
  int i; // $s4
  int j; // $s1
  int texamt; // $s2
  struct TEXINF *texinf; // $s3
  char *nametable; // $s6
} // line 26, offset 0x810a0
/*
 * Offset 0x810A0
 * D:\driver2\game\C\TEXTURE.C (line 334)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ update_slotinfo(int tpage /*$a0*/, int slot /*$a1*/, struct RECT *pos /*$a2*/)
{
}
/*
 * Offset 0x810E8
 * D:\driver2\game\C\TEXTURE.C (line 347)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ ProcessTextureInfo(char *lump_ptr /*$a1*/)
{ // line 1, offset 0x810e8
  int i; // $a0
} // line 28, offset 0x81180
/*
 * Offset 0x81180
 * D:\driver2\game\C\TEXTURE.C (line 578)
 * Stack frame base $sp, size 104
 * Saved registers at offset -8: ra
 */
void /*$ra*/ ReloadIcons()
{ // line 2, offset 0x81180
  struct RECT tpage; // stack offset -88
  struct RECT clutpos; // stack offset -80
  char name[64]; // stack offset -72
} // line 21, offset 0x811a8
/*
 * Offset 0x811A8
 * D:\driver2\game\C\TIME.C (line 5)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ GetTimeStamp(char *buffer /*$a0*/)
{
}
/*
 * Offset 0x811E0
 * D:\driver2\game\C\WHEELFORCES.C (line 98)
 * Stack frame base $sp, size 264
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ StepOneCar(struct _CAR_DATA *cp /*$s1*/)
{ // line 1, offset 0x811e0
  struct CAR_LOCALS _cl; // stack offset -248
  struct CAR_LOCALS *cl; // $s3
  int i; // $s0
  int speed; // $v1
  struct _sdPlane *SurfacePtr; // stack offset -48
  { // line 24, offset 0x8127c
    int a; // $v1
    int b; // $a0
  } // line 33, offset 0x812e4
  { // line 35, offset 0x812e4
    long deepestNormal[4]; // stack offset -208
    long deepestLever[4]; // stack offset -192
    long deepestPoint[4]; // stack offset -176
    int lift; // $s5
    int count; // $a0
    int friToUse; // $s6
    struct SVECTOR *carDisp; // $a1
    { // line 58, offset 0x8137c
      long pointPos[4]; // stack offset -160
      long surfacePoint[4]; // stack offset -144
      long surfaceNormal[4]; // stack offset -128
      long lever[4]; // stack offset -112
      int newLift; // $a0
    } // line 98, offset 0x81478
    { // line 103, offset 0x81490
      long pointVel[4]; // stack offset -112
      long reaction[4]; // stack offset -96
      int strikeVel; // $a2
      int componant; // $t3
      static int frictionLimit[6]; // offset 0x0
      { // line 111, offset 0x81490
        int lever_dot_n; // $v1
        int twistY; // $v0
        int displacementsquared; // $a0
        int denom; // $a0
      } // line 111, offset 0x81490
      { // line 128, offset 0x81698
        int loss; // $v1
        int limit; // $a1
      } // line 132, offset 0x816d4
      { // line 137, offset 0x81720
        { // line 139, offset 0x81734
          struct VECTOR direction; // stack offset -80
        } // line 139, offset 0x81734
        { // line 144, offset 0x81774
          struct VECTOR direction; // stack offset -64
        } // line 146, offset 0x817ac
      } // line 151, offset 0x81804
    } // line 152, offset 0x81804
    { // line 158, offset 0x818d4
      struct VECTOR offset; // stack offset -112
    } // line 171, offset 0x819ac
  } // line 172, offset 0x819ac
} // line 184, offset 0x819f4
/*
 * Offset 0x819F4
 * D:\driver2\game\C\WHEELFORCES.C (line 288)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ GetFrictionScalesDriver1(struct _CAR_DATA *cp /*$t0*/, struct CAR_LOCALS *cl /*$a1*/, int *frontFS /*$a2*/, int *rearFS /*$a3*/)
{ // line 1, offset 0x819f4
  struct _HANDLING_TYPE *hp; // $t2
  { // line 18, offset 0x81a84
    int q; // $v1
  } // line 26, offset 0x81b00
  { // line 99, offset 0x81e30
    int traction; // $a0
  } // line 105, offset 0x81e88
} // line 106, offset 0x81e88
/*
 * Offset 0x81E88
 * D:\driver2\game\C\WHEELFORCES.C (line 412)
 * Stack frame base $sp, size 16
 */
void /*$ra*/ ConvertTorqueToAngularAcceleration(struct _CAR_DATA *cp /*$a0*/, struct CAR_LOCALS *cl /*$t5*/)
{ // line 1, offset 0x81e88
  long nose[4]; // stack offset -16
  int zd; // $a3
  int i; // $t4
  int twistY; // $t0
  int twistZ; // $v1
} // line 27, offset 0x81fb8
/*
 * Offset 0x81FB8
 * D:\driver2\game\C\WHEELFORCES.C (line 442)
 * Stack frame base $sp, size 208
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddWheelForcesDriver1(struct _CAR_DATA *cp /*$s2*/, struct CAR_LOCALS *cl /*$s7*/)
{ // line 1, offset 0x81fb8
  int oldSpeed; // $v1
  int frictionScale; // $fp
  int frontFS; // stack offset -96
  int rearFS; // stack offset -92
  int i; // stack offset -84
  int cdx; // stack offset -80
  int cdz; // stack offset -76
  int sdx; // stack offset -72
  int sdz; // stack offset -68
  int friction_coef; // $s6
  struct CAR_COSMETICS *car_cos; // stack offset -64
  struct _sdPlane *SurfacePtr; // stack offset -88
  int player_id; // stack offset -60
  { // line 27, offset 0x8210c
    int oldCompression; // $s5
    int newCompression; // $s3
    int susForce; // $s0
    long wheelPos[4]; // stack offset -176
    long surfacePoint[4]; // stack offset -160
    long surfaceNormal[4]; // stack offset -144
    { // line 46, offset 0x821a8
      short typ; // $v1
    } // line 55, offset 0x82240
    { // line 71, offset 0x822ec
      int chan; // $s1
    } // line 83, offset 0x82384
    { // line 95, offset 0x823e8
      struct VECTOR force; // stack offset -128
      long pointVel[4]; // stack offset -112
      int lfx; // $a2
      int lfz; // $t2
      int sidevel; // $t0
      int slidevel; // $t1
      { // line 112, offset 0x824f4
      } // line 117, offset 0x82558
      { // line 150, offset 0x82698
        int hack; // $v0
        int hx; // $v0
        int hz; // $v1
      } // line 150, offset 0x82698
      { // line 203, offset 0x82958
        int a; // $v1
      } // line 206, offset 0x82990
    } // line 229, offset 0x82a6c
  } // line 237, offset 0x82b44
} // line 252, offset 0x82c38
/*
 * Offset 0x82C38
 * D:\driver2\game\C\WHEELFORCES.C (line 66)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ StepCars()
{ // line 2, offset 0x82c38
  struct _CAR_DATA **ppCar; // $s0
  struct _CAR_DATA **end; // $s1
  { // line 7, offset 0x82c74
  } // line 10, offset 0x82c74
  { // line 14, offset 0x82c9c
  } // line 15, offset 0x82c9c
} // line 17, offset 0x82ccc
/*
 * Offset 0x82CCC
 * D:\driver2\game\C\XAPLAY.C (line 265)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ PlayXA(int num /*$a3*/, int index /*$t0*/)
{ // line 1, offset 0x82ccc
  struct CdlFILTER filt; // stack offset -40
  struct CdlLOC loc; // stack offset -32
  unsigned char res[8]; // stack offset -24
} // line 25, offset 0x82db0
/*
 * Offset 0x82DC8
 * D:\driver2\game\C\XAPLAY.C (line 155)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ GetXAData(int number /*$a0*/)
{ // line 1, offset 0x82dc8
  int i; // $s0
  struct CdlFILE fp; // stack offset -32
} // line 12, offset 0x82e14
/*
 * Offset 0x82E14
 * D:\driver2\game\C\XAPLAY.C (line 226)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ PrepareXA()
{ // line 2, offset 0x82e14
  unsigned char param[4]; // stack offset -16
} // line 23, offset 0x82ec0
/*
 * Offset 0x82ED0
 * D:\driver2\game\C\XAPLAY.C (line 320)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ UnprepareXA()
{ // line 2, offset 0x82ed0
  unsigned char param[4]; // stack offset -16
} // line 17, offset 0x82f18
/*
 * Offset 0x82F28
 * D:\driver2\game\C\XAPLAY.C (line 128)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ GetMissionXAData(int number /*$s0*/)
{ // line 1, offset 0x82f28
  struct CdlFILE fp; // stack offset -32
} // line 16, offset 0x82f80
/*
 * Offset 0x82F80
 * D:\driver2\game\C\XAPLAY.C (line 185)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetXAVolume(int volume /*$a0*/)
{ // line 1, offset 0x82f80
} // line 12, offset 0x82fe0
/*
 * Offset 0x82FE0
 * D:\driver2\game\C\XAPLAY.C (line 343)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ StopXA()
{
}
/*
 * Offset 0x8302C
 * D:\driver2\game\C\XAPLAY.C (line 386)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ResumeXA()
{ // line 2, offset 0x8302c
  struct CdlFILTER filt; // stack offset -32
  unsigned char res[8]; // stack offset -24
} // line 22, offset 0x830cc
/*
 * Offset 0x830E0
 * D:\driver2\game\C\XAPLAY.C (line 418)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ PauseXA()
{ // line 1, offset 0x830e0
  unsigned char res[8]; // stack offset -16
} // line 15, offset 0x83148
/*
 * Offset 0x83158
 * D:\driver2\game\C\XAPLAY.C (line 310)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ XAPrepared()
{
}
/*
 * Offset 0x83164
 * D:\driver2\game\C\XAPLAY.C (line 355)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ cbready(int intr /*$s1*/, unsigned char *result /*$a1*/)
{
}
/*
 * Offset 0x83218
 * D:\driver2\game\C\XMPLAY.C (line 454)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ InitXMData(unsigned char *mpp /*$s5*/, int XM_ID /*$a1*/, int S3MPan /*$a2*/)
{ // line 1, offset 0x83218
  int t; // $s2
  int a; // $s4
  int c; // $s3
  unsigned long b; // $a2
  unsigned short b2; // $v1
} // line 67, offset 0x834b4
/*
 * Offset 0x834B4
 * D:\driver2\game\C\XMPLAY.C (line 627)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ XM_Init(int VabID /*$s5*/, int XM_ID /*$s4*/, int SongID /*$s0*/, int FirstCh /*$s2*/, int Loop /*stack 16*/, int PlayMask /*stack 20*/, int PlayType /*stack 24*/, int SFXNum /*stack 28*/)
{ // line 1, offset 0x834b4
  int i; // $s1
  int pmsk; // $v1
  int Chn; // $s0
  int t; // $a2
  int SngID; // $s3
  int fr; // $a3
} // line 151, offset 0x83994
/*
 * Offset 0x83994
 * D:\driver2\game\C\XMPLAY.C (line 788)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ JPlayNote(unsigned char *j /*$s0*/, int pmsk /*$s3*/)
{ // line 1, offset 0x83994
  unsigned char b; // $s1
  int ret; // $s2
  unsigned char note; // $s4
} // line 88, offset 0x83bcc
/*
 * Offset 0x83BCC
 * D:\driver2\game\C\XMPLAY.C (line 885)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ JPlayEffects()
{ // line 2, offset 0x83bcc
  unsigned char vol; // $a1
  unsigned char eff; // $s1
  unsigned char dat; // $s0
} // line 119, offset 0x83e0c
/*
 * Offset 0x83E0C
 * D:\driver2\game\C\XMPLAY.C (line 1012)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SPE(unsigned char eff /*$a0*/, unsigned char dat /*$s0*/)
{ // line 1, offset 0x83e0c
  int hi; // $v1
  int lo; // $a0
} // line 162, offset 0x84218
/*
 * Offset 0x84218
 * D:\driver2\game\C\XMPLAY.C (line 1182)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DoEEffects(unsigned char dat /*$a0*/)
{ // line 1, offset 0x84218
  unsigned char nib; // $a1
} // line 138, offset 0x8458c
/*
 * Offset 0x8458C
 * D:\driver2\game\C\XMPLAY.C (line 1448)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetPer()
{ // line 2, offset 0x8458c
  unsigned long *j; // $a1
} // line 61, offset 0x84730
/*
 * Offset 0x84740
 * D:\driver2\game\C\XMPLAY.C (line 1596)
 * Stack frame base $sp, size 8
 */
void /*$ra*/ DoS3MRetrig(unsigned char inf /*$a0*/)
{ // line 1, offset 0x84740
  unsigned char hi; // $a1
} // line 76, offset 0x84958
/*
 * Offset 0x84958
 * D:\driver2\game\C\XMPLAY.C (line 1710)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DoVibrato()
{ // line 2, offset 0x84958
  unsigned char q; // $a1
  unsigned short temp; // $a2
} // line 36, offset 0x84a58
/*
 * Offset 0x84A58
 * D:\driver2\game\C\XMPLAY.C (line 1754)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DoTremolo()
{ // line 2, offset 0x84a58
  unsigned char q; // $a2
  unsigned short temp; // $a3
} // line 40, offset 0x84ba4
/*
 * Offset 0x84BA4
 * D:\driver2\game\C\XMPLAY.C (line 1921)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ UpdatePatternData(int SC /*$a0*/)
{ // line 1, offset 0x84ba4
  int SP; // $s1
  int t; // $s0
  int pmsk; // $a2
  int FindOffset; // $t0
  unsigned char *pataddr; // $a0
  unsigned char patdat; // $a1
} // line 174, offset 0x85080
/*
 * Offset 0x8509C
 * D:\driver2\game\C\XMPLAY.C (line 2195)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ApplyEffs()
{ // line 2, offset 0x8509c
  short envpan; // $s2
  short envvol; // $s1
  int t; // $s3
  int pmsk; // $v1
  short vlm; // $s0
  short Pn; // $a1
  unsigned char MaxChans; // $s4
} // line 86, offset 0x853b8
/*
 * Offset 0x853DC
 * D:\driver2\game\C\XMPLAY.C (line 2322)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DoDolbySS()
{
}
/*
 * Offset 0x854B0
 * D:\driver2\game\C\XMPLAY.C (line 2398)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ UpdateHardware()
{ // line 2, offset 0x854b0
  int t; // $s2
  int prd; // $s0
  int SPUKeyOn; // $s6
  int pmsk; // $v1
  int Chnl; // $s1
  unsigned char MaxChans; // $s3
  int i; // $v1
} // line 105, offset 0x857e4
/*
 * Offset 0x8580C
 * D:\driver2\game\C\XMPLAY.C (line 2564)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
short /*$ra*/ ProcessEnvelope(short v /*$a2*/, unsigned char keyon /*$a1*/, int JSmp /*$a2*/)
{ // line 1, offset 0x8580c
  unsigned char a2; // $s2
  unsigned char b; // $s0
  unsigned short p; // $s1
  unsigned long *j; // $s5
  short bpos; // $s3
} // line 63, offset 0x859dc
/*
 * Offset 0x859DC
 * D:\driver2\game\C\XMPLAY.C (line 2635)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
short /*$ra*/ ProcessPanEnvelope(short v /*$a2*/, unsigned char keyon /*$a1*/, int JSmp /*$a2*/)
{ // line 1, offset 0x859dc
  unsigned char a2; // $s2
  unsigned char b; // $s0
  unsigned short p; // $s1
  unsigned long *j; // $s5
  short bpos; // $s3
} // line 64, offset 0x85bac
/*
 * Offset 0x85BAC
 * D:\driver2\game\C\XMPLAY.C (line 3206)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ XM_Restart(int Song_ID /*$a1*/)
{ // line 1, offset 0x85bac
  int t; // $s0
} // line 20, offset 0x85c8c
/*
 * Offset 0x85CA0
 * D:\driver2\game\C\XMPLAY.C (line 3160)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ XM_Pause(int Song_ID /*$a1*/)
{ // line 1, offset 0x85ca0
  int t; // $s0
} // line 19, offset 0x85d6c
/*
 * Offset 0x85D80
 * D:\driver2\game\C\XMPLAY.C (line 331)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ XM_Exit()
{ // line 2, offset 0x85d80
  int i; // $s0
} // line 11, offset 0x85de0
/*
 * Offset 0x85DE0
 * D:\driver2\game\C\XMPLAY.C (line 374)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ XM_Update()
{ // line 2, offset 0x85de0
} // line 11, offset 0x85e20
/*
 * Offset 0x85E30
 * D:\driver2\game\C\XMPLAY.C (line 429)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ XM_PlayStop(int Song_ID /*$a1*/)
{
}
/*
 * Offset 0x85EA0
 * D:\driver2\game\C\XMPLAY.C (line 409)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ XM_PlayStart(int Song_ID /*$a2*/, int PlayMask /*$a1*/)
{
}
/*
 * Offset 0x85EF4
 * D:\driver2\game\C\XMPLAY.C (line 2707)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ XM_SetSongPos(int Song_ID /*$a2*/, unsigned short pos /*$a1*/)
{ // line 1, offset 0x85ef4
  int t; // $a2
} // line 29, offset 0x85fdc
/*
 * Offset 0x85FE4
 * D:\driver2\game\C\XMPLAY.C (line 592)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ XM_OnceOffInit(int PAL /*$a0*/)
{
}
/*
 * Offset 0x8601C
 * D:\driver2\game\C\XMPLAY.C (line 345)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ XM_CloseVAB(int VabID /*$a1*/)
{
}
/*
 * Offset 0x86070
 * D:\driver2\game\C\XMPLAY.C (line 3273)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ XM_SetMasterVol(int Song_ID /*$a2*/, unsigned char Vol /*$a1*/)
{
}
/*
 * Offset 0x860C4
 * D:\driver2\game\C\XMPLAY.C (line 3331)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ XM_FreeVAG(int addr /*$a0*/)
{
}
/*
 * Offset 0x860E4
 * D:\driver2\game\C\XMPLAY.C (line 1855)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ UpdateWithTimer(int SC /*$a3*/)
{
}
/*
 * Offset 0x861E0
 * D:\driver2\game\C\XMPLAY.C (line 1887)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ XM_DoFullUpdate(int SC /*$s1*/)
{
}
/*
 * Offset 0x8629C
 * D:\driver2\game\C\XMPLAY.C (line 3351)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ XM_Quit(int SongID /*$s0*/)
{
}
/*
 * Offset 0x862E0
 * D:\driver2\game\C\XMPLAY.C (line 3449)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ XM_GetFreeVAB()
{ // line 2, offset 0x862e0
  int i; // $v1
} // line 10, offset 0x86318
/*
 * Offset 0x86320
 * D:\driver2\game\C\XMPLAY.C (line 3461)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ XM_SetVAGAddress(int VabID /*$a0*/, int slot /*$a1*/, int addr /*$a2*/)
{
}
/*
 * Offset 0x86358
 * D:\driver2\game\C\XMPLAY.C (line 354)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ XM_CloseVAB2(int VabID /*$a3*/)
{ // line 1, offset 0x86358
  int i; // $v0
} // line 13, offset 0x863c0
/*
 * Offset 0x863C0
 * D:\driver2\game\C\XMPLAY.C (line 3511)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ XM_SetSongAddress(unsigned char *Address /*$a0*/)
{
}
/*
 * Offset 0x86404
 * D:\driver2\game\C\XMPLAY.C (line 3506)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ XM_GetSongSize()
{
}
/*
 * Offset 0x8640C
 * D:\driver2\game\C\XMPLAY.C (line 3527)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ XM_FreeAllSongIDs()
{
}
/*
 * Offset 0x86418
 * D:\driver2\game\C\XMPLAY.C (line 3537)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ XM_SetFileHeaderAddress(unsigned char *Address /*$a0*/)
{
}
/*
 * Offset 0x8644C
 * D:\driver2\game\C\XMPLAY.C (line 3532)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ XM_GetFileHeaderSize()
{
}
/*
 * Offset 0x86454
 * D:\driver2\game\C\XMPLAY.C (line 256)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 ra
 */
unsigned short /*$ra*/ GetLogPeriod(unsigned char note /*$a0*/, unsigned short fine /*$a1*/)
{ // line 1, offset 0x86454
} // line 25, offset 0x864ec
/*
 * Offset 0x864EC
 * D:\driver2\game\C\XMPLAY.C (line 1831)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ UpdateXMData()
{ // line 2, offset 0x864ec
  int SC; // $s0
} // line 20, offset 0x86588
/*
 * Offset 0x865A0
 * D:\driver2\game\C\XMPLAY.C (line 1817)
 * Stack frame base $sp, size 0
 */
short /*$ra*/ DoVol(unsigned long a /*$v0*/, short b /*$a1*/, short c /*$a2*/)
{
}
/*
 * Offset 0x865C8
 * D:\driver2\game\C\XMPLAY.C (line 1802)
 * Stack frame base $sp, size 0
 */
short /*$ra*/ DoPan(short envpan /*$a0*/, short pan /*$a1*/)
{
}
/*
 * Offset 0x8661C
 * D:\driver2\game\C\XMPLAY.C (line 1545)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DoVolSlide(unsigned char dat /*$a1*/)
{
}
/*
 * Offset 0x866AC
 * D:\driver2\game\C\XMPLAY.C (line 1680)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DoToneSlide()
{ // line 2, offset 0x866ac
  int dist; // $v1
} // line 22, offset 0x86714
/*
 * Offset 0x86714
 * D:\driver2\game\C\XMPLAY.C (line 1561)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DoXMPanSlide(unsigned char inf /*$a0*/)
{ // line 1, offset 0x86714
  unsigned char lo; // $v0
  unsigned char hi; // $a0
  short pan; // $v1
} // line 27, offset 0x86798
/*
 * Offset 0x867A0
 * D:\driver2\game\C\XMPLAY.C (line 1517)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ Arpeggio(unsigned char dat /*$a1*/)
{ // line 1, offset 0x867a0
  unsigned char note; // $a2
} // line 20, offset 0x8684c
/*
 * Offset 0x8684C
 * D:\driver2\game\C\XMPLAY.C (line 1372)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetInstr(unsigned char inst /*$a0*/)
{ // line 1, offset 0x8684c
  unsigned long *j; // $a2
} // line 61, offset 0x86940
/*
 * Offset 0x86948
 * D:\driver2\game\C\XMPLAY.C (line 1328)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetNote(unsigned char note /*$a0*/)
{ // line 1, offset 0x86948
  unsigned char *j; // $a0
} // line 35, offset 0x86a20
/*
 * Offset 0x86A28
 * D:\driver2\game\C\XMPLAY.C (line 568)
 * Stack frame base $sp, size 0
 */
unsigned long /*$ra*/ GetLong(unsigned char *mpp /*$a0*/)
{ // line 1, offset 0x86a28
} // line 16, offset 0x86a54
/*
 * Offset 0x86A54
 * D:\driver2\game\C\XMPLAY.C (line 237)
 * Stack frame base $sp, size 0
 */
short /*$ra*/ Interpolate(short p /*$a0*/, short p1 /*$a1*/, short p2 /*$a2*/, short v1 /*$a3*/, int v2 /*stack 16*/)
{ // line 1, offset 0x86a54
} // line 11, offset 0x86ad4
/*
 * Offset 0x86AD4
 * D:\driver2\game\C\XMPLAY.C (line 288)
 * Stack frame base $sp, size 0
 */
unsigned short /*$ra*/ JPGetPeriod(unsigned char note /*$a0*/, short fine /*$a1*/)
{
}
/*
 * Offset 0x86B08
 * D:\driver2\game\C\XMPLAY.C (line 299)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
unsigned short /*$ra*/ GetPeriod(unsigned char note /*$a2*/, unsigned short c2spd /*$a1*/)
{ // line 1, offset 0x86b08
} // line 8, offset 0x86b58
/*
 * Offset 0x86B58
 * D:\driver2\game\C\XMPLAY.C (line 2540)
 * Stack frame base $sp, size 0
 */
long /*$ra*/ GetFreq2(long period /*$v1*/)
{ // line 2, offset 0x86b58
  int okt; // $a1
  long frequency; // $a0
} // line 16, offset 0x86bb0
/*
 * Offset 0x86BB0
 * D:\driver2\game\C\XMPLAY.C (line 3068)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: ra
 */
void /*$ra*/ CurrentKeyStat()
{ // line 2, offset 0x86bb0
  int t; // $a1
  char KeyStat[24]; // stack offset -32
} // line 15, offset 0x86c5c
/*
 * Offset 0x86C5C
 * D:\driver2\game\C\XMPLAY.C (line 3091)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ StpCh(int Channel /*$a0*/)
{
}
/*
 * Offset 0x86C80
 * D:\driver2\game\C\XMPLAY.C (line 3115)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetFrq(int Channel /*$a0*/, int Pitch /*$a1*/)
{
}
/*
 * Offset 0x86CA0
 * D:\driver2\game\C\XMPLAY.C (line 3104)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetVol(int Channel /*$a0*/, int LVol /*$a1*/, int RVol /*$a2*/)
{
}
/*
 * Offset 0x86CCC
 * D:\driver2\game\C\XMPLAY.C (line 3003)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ PlaySFX(int VBID /*$a0*/, int Channel /*$a1*/, int Inst /*$a2*/, int Pitch /*$a3*/, int LV /*stack 16*/, int RV /*stack 20*/)
{ // line 1, offset 0x86ccc
} // line 23, offset 0x86d60
/*
 * Offset 0x86D60
 * D:\driver2\game\C\XMPLAY.C (line 3308)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ClearSPU(int VBID /*$a0*/)
{ // line 1, offset 0x86d60
  int i; // $s1
  int Amount; // $a1
} // line 15, offset 0x86ddc
/*
 * Offset 0x86DDC
 * D:\driver2\game\C\XMPLAY.C (line 3035)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ InitSPUChannel(int Channel /*$a0*/)
{
}
/*
 * Offset 0x86E44
 * D:\driver2\game\C\XMPLAY.C (line 3126)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SilenceXM(int Song_ID /*$a0*/)
{ // line 2, offset 0x86e44
  int t; // $s0
  int i; // $s1
  int c; // $a0
  int pmsk; // $v0
} // line 25, offset 0x86f24
/*
 * Offset 0x86F24
 * D:\driver2\game\C\XMPLAY.C (line 2289)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ UpdateEffs()
{ // line 2, offset 0x86f24
  int t; // $s0
  int pmsk; // $v1
  unsigned char MaxChans; // $s1
} // line 24, offset 0x86fbc
/*
 * Offset 0x86FD8
 * D:\driver2\game\C\XMPLAY.C (line 2516)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ IntVols(int Vol1 /*$a0*/, int Vol2 /*$a1*/)
{ // line 1, offset 0x86fd8
  int a; // $v1
} // line 11, offset 0x87008
/*
 * Offset 0x87008
 * D:\driver2\game\C\XMPLAY.C (line 3337)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetFreeSongID()
{ // line 2, offset 0x87008
  int i; // $v1
} // line 12, offset 0x87058
/*
 * Offset 0x87058
 * D:\driver2\game\C\XMPLAY.C (line 3359)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ JPClearSPUFlags(int SongID /*$a0*/)
{ // line 1, offset 0x87058
  int i; // $a1
} // line 9, offset 0x8708c
/*
 * Offset 0x8708C
 * D:\driver2\game\C\XMPLAY.C (line 2099)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ CalcPlayPos(int StartPos /*$s4*/)
{ // line 1, offset 0x8708c
  int SP; // $s1
  int t; // $s0
  int i; // $a1
} // line 15, offset 0x87144
/*
 * Offset 0x87144
 * D:\driver2\game\C\XMPLAY.C (line 2143)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ JCalcPat(unsigned char *j /*$a0*/)
{ // line 2, offset 0x87144
  unsigned char b; // $v1
  int ret; // $a1
} // line 44, offset 0x871b4
/*
 * Offset 0x871B4
 * D:\driver2\game\C\XMPLAY.C (line 2116)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ PACKEDCalcPlayPos(int StartPos /*$s3*/)
{ // line 1, offset 0x871b4
  int SP; // $s0
  int i; // $a1
  unsigned char *pataddr; // $a0
  unsigned char patdat; // $v1
} // line 23, offset 0x87290
/*
 * Offset 0x87290
 * D:\driver2\game\C\XMPLAY.C (line 2368)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetEmpty(int old /*$t1*/)
{ // line 1, offset 0x87290
  int i; // $a3
  struct XMCHANNEL *j; // $a0
} // line 28, offset 0x87358
/*
 * Offset 0x1C096C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1205)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ SetVariable(int var /*$a0*/)
{ // line 1, offset 0x1c096c
  int code; // $v1
  int value; // $a2
} // line 157, offset 0x1c0c14
/*
 * Offset 0x1C0C14
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1371)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ LoadFrontendScreens()
{ // line 2, offset 0x1c0c14
  int iTpage; // $s0
  int iNumScreens; // $t6
  int i; // $t0
  int j; // $a3
  struct RECT rect; // stack offset -40
  char *ptr; // $a2
} // line 83, offset 0x1c0f1c
/*
 * Offset 0x1C0F1C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1461)
 * Stack frame base $sp, size 88
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ LoadBackgroundFile(char *name /*$s4*/)
{ // line 1, offset 0x1c0f1c
  int iTpage; // $s2
  struct RECT rect; // stack offset -72
  int p; // $s0
  int pages[7]; // stack offset -64
} // line 48, offset 0x1c10ec
/*
 * Offset 0x1C10EC
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1516)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetupBackgroundPolys()
{ // line 2, offset 0x1c10ec
  int i; // $v1
  int tpage; // $t3
} // line 64, offset 0x1c1324
/*
 * Offset 0x1C1324
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1588)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SetupScreenSprts(struct PSXSCREEN *pScr /*$a0*/)
{ // line 1, offset 0x1c1324
  int tpage; // $a1
  struct POLY_FT3 *null; // $v0
} // line 62, offset 0x1c1474
/*
 * Offset 0x1C1474
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1658)
 * Stack frame base $sp, size 120
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawScreen(struct PSXSCREEN *pScr /*stack 0*/)
{ // line 1, offset 0x1c1474
  int i; // $s1
  char version_info[32]; // stack offset -88
  int numBtnsToDraw; // stack offset -56
} // line 102, offset 0x1c18ac
/*
 * Offset 0x1C18DC
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1769)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DisplayOnScreenText()
{ // line 2, offset 0x1c18dc
  int i; // $s0
  char text[32]; // stack offset -64
  { // line 26, offset 0x1c19d4
    { // line 28, offset 0x1c19dc
    } // line 29, offset 0x1c19e4
  } // line 30, offset 0x1c19e4
  { // line 38, offset 0x1c1a44
    int extraVal; // $t1
  } // line 41, offset 0x1c1aa4
} // line 78, offset 0x1c1ac8
/*
 * Offset 0x1C1AC8
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1855)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ SetupExtraPoly(char *fileName /*$s5*/, int offset /*$s1*/, int offset2 /*$s0*/)
{ // line 1, offset 0x1c1ac8
  int i; // $s0
  int tpage; // $v1
  struct RECT rect; // stack offset -40
} // line 61, offset 0x1c1cec
/*
 * Offset 0x1C1CEC
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1941)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ReInitScreens()
{
}
/*
 * Offset 0x1C1E10
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 1991)
 * Stack frame base $sp, size 80
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ NewSelection(short dir /*$s3*/)
{ // line 1, offset 0x1c1e10
  struct RECT rect; // stack offset -48
  struct PSXBUTTON *pNewB; // $s2
} // line 94, offset 0x1c2274
/*
 * Offset 0x1C22A0
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2093)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ HandleKeyPress()
{ // line 2, offset 0x1c22a0
  { // line 19, offset 0x1c2338
    int action; // $s0
    { // line 48, offset 0x1c2444
    } // line 73, offset 0x1c2508
  } // line 93, offset 0x1c255c
} // line 139, offset 0x1c2660
/*
 * Offset 0x1C2660
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2300)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ PadChecks()
{ // line 2, offset 0x1c2660
  int i; // $a2
  int oldnum; // $s2
} // line 117, offset 0x1c2964
/*
 * Offset 0x1C2964
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2423)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DoFrontEnd()
{ // line 2, offset 0x1c2964
  static unsigned char result[8]; // offset 0x0
} // line 165, offset 0x1c2c24
/*
 * Offset 0x1C2C24
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2630)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ SetFEDrawMode()
{ // line 2, offset 0x1c2c24
  struct DRAW_MODE *dm; // $s3
} // line 57, offset 0x1c2d88
/*
 * Offset 0x1C2D88
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2745)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: s0 s1 s2 s3 s4
 */
int /*$ra*/ FEPrintString(char *string /*$t1*/, int x /*$t2*/, int y /*$s4*/, int justification /*$a3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/)
{ // line 1, offset 0x1c2d88
  struct FE_CHARDATA *pFontInfo; // $a0
  struct SPRT *font; // $t0
  unsigned char let; // $a0
  int counter; // $t4
  { // line 1, offset 0x1c2de4
    char *pString; // $a1
    { // line 1, offset 0x1c2de4
      char let; // $v1
      int w; // $a2
    } // line 1, offset 0x1c2e30
  } // line 1, offset 0x1c2e30
  { // line 47, offset 0x1c2f20
    int tpage; // $v1
  } // line 47, offset 0x1c2f20
} // line 64, offset 0x1c2fd0
/*
 * Offset 0x1C2FD0
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2817)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: s0 s1 s2 s3 s4
 */
int /*$ra*/ FEPrintStringSized(char *string /*$t2*/, int x /*$t1*/, int y /*$t7*/, int scale /*$a3*/, int transparent /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, offset 0x1c2fd0
  struct POLY_FT4 *font; // $t0
  struct FE_CHARDATA *pFontInfo; // $a2
  char let; // $v1
  int tpage; // $v0
  int w; // $t3
  int h; // $t4
} // line 63, offset 0x1c31f4
/*
 * Offset 0x1C31F4
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2894)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ CentreScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C3428
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3029)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ CarSelectScreen(int bSetup /*$a0*/)
{ // line 2, offset 0x1c3428
  int i; // $a0
  struct RECT rect; // stack offset -32
  { // line 116, offset 0x1c3734
    int lastVal; // $a3
    { // line 1, offset 0x1c37b4
      { // line 1, offset 0x1c37b4
        struct RECT rect; // stack offset -24
      } // line 1, offset 0x1c37b4
    } // line 1, offset 0x1c37b4
  } // line 1, offset 0x1c37b4
  { // line 135, offset 0x1c37c8
    int lastVal; // $a3
    { // line 1, offset 0x1c3850
      { // line 1, offset 0x1c3850
        struct RECT rect; // stack offset -24
      } // line 1, offset 0x1c3850
    } // line 1, offset 0x1c3850
  } // line 1, offset 0x1c3850
} // line 183, offset 0x1c3a58
/*
 * Offset 0x1C3A58
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3256)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ VibroOnOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C3B14
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3394)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ MissionSelectScreen(int bSetup /*$a0*/)
{ // line 2, offset 0x1c3b14
  int i; // $a1
  { // line 29, offset 0x1c3bd4
    int usedB; // $s2
    int done; // $t0
    int bP; // $a3
    int bN; // $s5
    int shift; // $a3
  } // line 158, offset 0x1c40d0
} // line 231, offset 0x1c4330
/*
 * Offset 0x1C4330
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3632)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
int /*$ra*/ MissionCityScreen(int bSetup /*$a0*/)
{ // line 6, offset 0x1c4330
  { // line 71, offset 0x1c4494
    { // line 71, offset 0x1c4494
      struct RECT rect; // stack offset -16
    } // line 71, offset 0x1c4494
  } // line 71, offset 0x1c4494
  { // line 77, offset 0x1c44bc
    { // line 77, offset 0x1c44bc
      struct RECT rect; // stack offset -16
    } // line 77, offset 0x1c44bc
  } // line 77, offset 0x1c44bc
} // line 88, offset 0x1c45f8
/*
 * Offset 0x1C45F8
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3728)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: ra
 */
int /*$ra*/ CutSceneSelectScreen(int bSetup /*$a0*/)
{ // line 2, offset 0x1c45f8
  struct RENDER_ARGS renderArgs; // stack offset -48
  int extraVal; // $a0
  struct RECT rect; // stack offset -24
  { // line 61, offset 0x1c4790
    { // line 61, offset 0x1c4790
      struct RECT rect; // stack offset -16
    } // line 61, offset 0x1c4790
  } // line 61, offset 0x1c4790
  { // line 1, offset 0x1c483c
    int offset; // $a1
    { // line 1, offset 0x1c483c
      struct RECT rect; // stack offset -16
    } // line 1, offset 0x1c483c
  } // line 1, offset 0x1c483c
  { // line 80, offset 0x1c48f8
    { // line 80, offset 0x1c48f8
      struct RECT rect; // stack offset -16
    } // line 80, offset 0x1c48f8
  } // line 80, offset 0x1c48f8
  { // line 85, offset 0x1c4938
    { // line 85, offset 0x1c4938
      struct RECT rect; // stack offset -16
    } // line 85, offset 0x1c4938
  } // line 85, offset 0x1c4938
} // line 119, offset 0x1c4b28
/*
 * Offset 0x1C4B28
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3855)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: ra
 */
int /*$ra*/ CutSceneCitySelectScreen(int bSetup /*$a0*/)
{ // line 2, offset 0x1c4b28
  struct RECT rect; // stack offset -24
  { // line 1, offset 0x1c4e64
    { // line 1, offset 0x1c4e64
      struct RECT rect; // stack offset -16
    } // line 1, offset 0x1c4e64
  } // line 1, offset 0x1c4e64
  { // line 1, offset 0x1c4e64
    { // line 1, offset 0x1c4e64
      struct RECT rect; // stack offset -16
    } // line 1, offset 0x1c4e64
  } // line 1, offset 0x1c4e64
  { // line 1, offset 0x1c4eac
    { // line 1, offset 0x1c4eac
      struct RECT rect; // stack offset -16
    } // line 1, offset 0x1c4eac
  } // line 1, offset 0x1c4eac
  { // line 1, offset 0x1c4fa4
    { // line 1, offset 0x1c4fa4
      struct RECT rect; // stack offset -16
    } // line 1, offset 0x1c5098
  } // line 1, offset 0x1c5098
} // line 140, offset 0x1c50a8
/*
 * Offset 0x1C50A8
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4005)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ SetVolumeScreen(int bSetup /*$a0*/)
{ // line 2, offset 0x1c50a8
  int last; // $s2
  char text[4]; // stack offset -48
  int ypos[2]; // stack offset -40
  struct RECT rect; // stack offset -32
  { // line 43, offset 0x1c524c
    { // line 43, offset 0x1c524c
      struct DB *db_hold; // $a1
    } // line 43, offset 0x1c524c
  } // line 43, offset 0x1c524c
  { // line 65, offset 0x1c527c
    { // line 65, offset 0x1c527c
      struct DB *db_hold; // $a1
    } // line 65, offset 0x1c527c
  } // line 65, offset 0x1c527c
  { // line 92, offset 0x1c52c4
    { // line 92, offset 0x1c52c4
      struct DB *db_hold; // $a1
    } // line 92, offset 0x1c52c4
  } // line 92, offset 0x1c52c4
  { // line 114, offset 0x1c5418
    { // line 114, offset 0x1c5418
      struct DB *db_hold; // $a1
    } // line 117, offset 0x1c5528
  } // line 117, offset 0x1c5528
} // line 143, offset 0x1c55f0
/*
 * Offset 0x1C55F0
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4165)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DisplayScoreTable()
{ // line 2, offset 0x1c55f0
  int offset; // $a2
  int i; // $s4
  char text[32]; // stack offset -80
  struct SCORE_ENTRY *pSE; // stack offset -48
  int min; // $v1
  int frac; // $t0
} // line 56, offset 0x1c5998
/*
 * Offset 0x1C5998
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4227)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ ScoreScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C5B44
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4434)
 * Stack frame base $sp, size 120
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CheatScreen(int bSetup /*$a0*/)
{ // line 2, offset 0x1c5b44
  int numOpen; // $s5
  int i; // $s1
  int k; // $s6
  int *uc; // $s2
  unsigned char cheatOn[12]; // stack offset -104
  int hackLookup1[4]; // stack offset -88
  int hackLookup2[4]; // stack offset -72
  { // line 39, offset 0x1c5c64
    int evilRuss[4]; // stack offset -56
  } // line 126, offset 0x1c6064
} // line 134, offset 0x1c6098
/*
 * Offset 0x1C6098
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4642)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ GameNameScreen(int bSetup /*$a0*/)
{ // line 2, offset 0x1c6098
  int offset; // $s3
} // line 14, offset 0x1c61a4
/*
 * Offset 0x1C61A4
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4671)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ FEInitCdIcon()
{ // line 2, offset 0x1c61a4
  int i; // $a0
  struct RECT dest; // stack offset -24
  unsigned short *palette; // $a2
} // line 38, offset 0x1c62f0
/*
 * Offset 0x1C62F0
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4716)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: ra
 */
void /*$ra*/ FEDrawCDicon()
{ // line 2, offset 0x1c62f0
  unsigned short *palette; // $a1
  int temp; // $a2
  int i; // $a0
  struct RECT dest; // stack offset -16
} // line 19, offset 0x1c6370
/*
 * Offset 0x1C6370
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 2695)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ EndFrame()
{ // line 2, offset 0x1c6370
  struct DB *db_hold; // $a1
} // line 21, offset 0x1c63fc
/*
 * Offset 0x1C63FC
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 3220)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CopDiffLevelScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C64A8
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4322)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ SubtitlesOnOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C64F4
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4345)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CityCutOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C6540
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4378)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ ControllerScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C660C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4412)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ MainScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C664C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4575)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ ImmunityOnOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C6698
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4597)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ InvincibleOnOffScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C66E4
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4619)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GamePlayScreen(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x1C671C
 * D:\driver2\game\FRONTEND\FEMAIN.C (line 4742)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ CheatNumlayerSelect(int bSetup /*$a0*/)
{
}
/*
 * Offset 0x87358
 * D:\driver2\game\MEMCARD\MAIN.C (line 120)
 * Stack frame base $fp, size 56
 * Saved registers at offset -8: s0 fp ra
 */
int /*$ra*/ CallMemoryCard(int flags /*stack 0*/, int ingame /*stack 4*/)
{ // line 3, offset 0x87374
  struct REPLAY_SAVE_HEADER *rheader; // stack offset -40
  struct GAME_SAVE_HEADER *gheader; // stack offset -36
  struct CONFIG_SAVE_HEADER *cheader; // stack offset -32
  char *pt; // stack offset -28
  int ret; // stack offset -24
  int size; // stack offset -20
  { // line 21, offset 0x873d0
  } // line 23, offset 0x873e4
  { // line 129, offset 0x878a4
  } // line 135, offset 0x878d0
} // line 148, offset 0x87920
/*
 * Offset 0x8793C
 * D:\driver2\game\MEMCARD\MAIN.C (line 270)
 * Stack frame base $fp, size 24
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ libcman_SelectSound()
{
}
/*
 * Offset 0x87970
 * D:\driver2\game\MEMCARD\MAIN.C (line 275)
 * Stack frame base $fp, size 24
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ libcman_ConfirmSound()
{
}
/*
 * Offset 0x879A4
 * D:\driver2\game\MEMCARD\MAIN.C (line 280)
 * Stack frame base $fp, size 24
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ libcman_CancelSound()
{
}
/*
 * Offset 0x879D8
 * D:\driver2\game\MEMCARD\MAIN.C (line 285)
 * Stack frame base $fp, size 24
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ libcman_ErrorSound()
{
}
/*
 * Offset 0x87A0C
 * D:\driver2\game\MEMCARD\MAIN.C (line 290)
 * Stack frame base $fp, size 24
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ libcman_InitControllerLibrary(char *a /*stack 0*/, int b /*stack 4*/, char *c /*stack 8*/, int d /*stack 12*/)
{
}
/*
 * Offset 0x87A5C
 * D:\driver2\game\MEMCARD\MAIN.C (line 296)
 * Stack frame base $fp, size 24
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ libcman_DeInitControllerLibrary()
{
}
/*
 * Offset 0x87A9C
 * D:\driver2\game\MEMCARD\MAIN.C (line 302)
 * Stack frame base $fp, size 24
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ libcman_ReadControllers()
{
}
/*
 * Offset 0x87ACC
 * D:\driver2\game\MEMCARD\MAIN.C (line 371)
 * Stack frame base $fp, size 88
 * Saved registers at offset -4: fp ra
 */
int /*$ra*/ DoMemoryCard()
{ // line 2, offset 0x87adc
  struct RECT rect; // stack offset -56
  char filename[32]; // stack offset -48
  char l; // stack offset -16
  int options; // stack offset -12
  static int ret; // offset 0x0
} // line 71, offset 0x87d34
/*
 * Offset 0x87D4C
 * D:\driver2\game\MEMCARD\MAIN.C (line 444)
 * Stack frame base $fp, size 32
 * Saved registers at offset -4: fp ra
 */
char * /*$ra*/ LoadMemCardOverlay()
{ // line 2, offset 0x87d5c
  char *pt; // stack offset -16
  int ovsize; // stack offset -12
} // line 16, offset 0x87db8
/*
 * Offset 0x87DD0
 * D:\driver2\game\MEMCARD\MAIN.C (line 462)
 * Stack frame base $fp, size 40
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ StorePermanentTPage()
{ // line 2, offset 0x87de0
  struct RECT rect; // stack offset -24
  unsigned long *buffer; // stack offset -16
} // line 8, offset 0x87e2c
/*
 * Offset 0x87E44
 * D:\driver2\game\MEMCARD\MAIN.C (line 472)
 * Stack frame base $fp, size 40
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ RestorePermanentTPage()
{ // line 2, offset 0x87e54
  struct RECT rect; // stack offset -24
  unsigned long *buffer; // stack offset -16
} // line 8, offset 0x87ea0
/*
 * Offset 0x87EB8
 * D:\driver2\game\MEMCARD\MAIN.C (line 482)
 * Stack frame base $fp, size 32
 * Saved registers at offset -4: fp ra
 */
void /*$ra*/ PutCorrectIcon(int which /*stack 0*/)
{ // line 2, offset 0x87ecc
  unsigned char *clut; // stack offset -16
  unsigned char *icon; // stack offset -12
} // line 24, offset 0x87fa0
/*
 * Offset 0xF3644
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 99)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ card_start__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, offset 0xf3644
} // line 39, offset 0xf3828
/*
 * Offset 0xF3828
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 383)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
unsigned int /*$ra*/ CardRemoved__6MCSLOT(struct MCSLOT *this /*$s6*/)
{ // line 1, offset 0xf3828
  int card_status; // $v0
  { // line 1, offset 0xf3828
    struct MCSLOT *this; // $s6
    int timeout; // $s0
    { // line 1, offset 0xf3828
      { // line 1, offset 0xf387c
        { // line 1, offset 0xf387c
        } // line 1, offset 0xf3890
        { // line 1, offset 0xf3890
        } // line 1, offset 0xf38a4
        { // line 1, offset 0xf38a4
        } // line 1, offset 0xf38b8
        { // line 1, offset 0xf38b8
        } // line 1, offset 0xf38cc
      } // line 1, offset 0xf38cc
    } // line 1, offset 0xf38d4
  } // line 1, offset 0xf38d4
  { // line 11, offset 0xf38d4
    { // line 11, offset 0xf38e4
      { // line 11, offset 0xf38e4
        struct MCSLOT *this; // $s6
        { // line 11, offset 0xf38e4
        } // line 11, offset 0xf38e4
      } // line 11, offset 0xf38e4
    } // line 24, offset 0xf3924
  } // line 24, offset 0xf3924
  { // line 24, offset 0xf3924
    struct MCSLOT *this; // $s6
    { // line 24, offset 0xf3924
    } // line 24, offset 0xf3924
  } // line 24, offset 0xf3924
} // line 24, offset 0xf3994
/*
 * Offset 0xF3994
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 418)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
unsigned int /*$ra*/ CardInserted__6MCSLOT(struct MCSLOT *this /*$s6*/)
{ // line 1, offset 0xf3994
  int card_status; // $v1
  { // line 1, offset 0xf3994
    struct MCSLOT *this; // $s6
    int timeout; // $s0
    { // line 1, offset 0xf3994
      { // line 1, offset 0xf39e8
        { // line 1, offset 0xf39e8
        } // line 1, offset 0xf39fc
        { // line 1, offset 0xf39fc
        } // line 1, offset 0xf3a10
        { // line 1, offset 0xf3a10
        } // line 1, offset 0xf3a24
        { // line 1, offset 0xf3a24
        } // line 1, offset 0xf3a38
      } // line 1, offset 0xf3a38
    } // line 1, offset 0xf3a40
  } // line 1, offset 0xf3a40
  { // line 11, offset 0xf3a40
    { // line 12, offset 0xf3a54
      { // line 1, offset 0xf3a54
        struct MCSLOT *this; // $s6
        { // line 1, offset 0xf3a54
        } // line 1, offset 0xf3a54
      } // line 1, offset 0xf3a54
    } // line 19, offset 0xf3aa8
  } // line 19, offset 0xf3aa8
  { // line 1, offset 0xf3aa8
    struct MCSLOT *this; // $s6
    { // line 1, offset 0xf3aa8
    } // line 1, offset 0xf3aa8
  } // line 1, offset 0xf3aa8
} // line 24, offset 0xf3b04
/*
 * Offset 0xF3B04
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 489)
 * Stack frame base $sp, size 176
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ FormatCard__6MCSLOT(struct MCSLOT *this /*$s2*/)
{ // line 1, offset 0xf3b04
  char buffer[128]; // stack offset -160
  { // line 1, offset 0xf3b04
    struct MCSLOT *this; // $s2
    { // line 1, offset 0xf3b04
    } // line 1, offset 0xf3b04
  } // line 1, offset 0xf3b04
  { // line 1, offset 0xf3b04
    { // line 1, offset 0xf3b04
      struct MCSLOT *this; // $s2
      int timeout; // $s3
      { // line 1, offset 0xf3b04
        { // line 1, offset 0xf3bb4
          { // line 1, offset 0xf3bb4
          } // line 1, offset 0xf3bc8
          { // line 1, offset 0xf3bc8
          } // line 1, offset 0xf3bdc
          { // line 1, offset 0xf3bdc
          } // line 1, offset 0xf3bf0
          { // line 1, offset 0xf3bf0
          } // line 1, offset 0xf3c04
        } // line 1, offset 0xf3c04
      } // line 1, offset 0xf3c0c
    } // line 1, offset 0xf3c0c
  } // line 15, offset 0xf3c28
} // line 20, offset 0xf3c74
/*
 * Offset 0xF3C74
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 520)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ ReadCardDir__6MCSLOT(struct MCSLOT *this /*$s3*/)
{ // line 1, offset 0xf3c74
  long size; // $a1
  char path[7]; // stack offset -48
  struct DIRENTRY *entryPtr; // $s0
  { // line 17, offset 0xf3cf4
  } // line 40, offset 0xf3d6c
} // line 49, offset 0xf3d8c
/*
 * Offset 0xF3DB8
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 618)
 * Stack frame base $sp, size 96
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ ReadCardInfo__6MCSLOTPc(struct MCSLOT *this /*$s1*/, char *managerFilename /*$s0*/)
{ // line 1, offset 0xf3db8
  int i; // $a2
  int n; // $s0
  char filename[32]; // stack offset -64
  int filePtr; // $s2
  { // line 11, offset 0xf3df4
    { // line 12, offset 0xf3e0c
      { // line 13, offset 0xf3e0c
        { // line 14, offset 0xf3e38
          { // line 16, offset 0xf3e38
            { // line 21, offset 0xf3e70
            } // line 24, offset 0xf3eb0
          } // line 26, offset 0xf3eb0
          { // line 30, offset 0xf3eb0
            { // line 31, offset 0xf3ed4
              { // line 32, offset 0xf3ed4
                { // line 35, offset 0xf3f4c
                  { // line 37, offset 0xf3f4c
                  } // line 37, offset 0xf3f88
                } // line 54, offset 0xf4060
              } // line 55, offset 0xf4094
            } // line 57, offset 0xf4094
          } // line 61, offset 0xf40e4
        } // line 68, offset 0xf4130
      } // line 68, offset 0xf4130
    } // line 73, offset 0xf4130
  } // line 79, offset 0xf4168
} // line 82, offset 0xf41a0
/*
 * Offset 0xF41A0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 912)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ ReadSlice__6MCSLOTiiP5SLICEP10FILEFORMAT(struct MCSLOT *this /*$t0*/, int block /*$a1*/, int slice /*$a2*/, struct SLICE *slicePtr /*$a3*/, struct FILEFORMAT *fileFormatPtr /*stack 16*/)
{ // line 1, offset 0xf41a0
} // line 28, offset 0xf43a0
/*
 * Offset 0xF43A0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 950)
 * Stack frame base $sp, size 216
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ read_block__6MCSLOTiPcR9BLOCKINFO(struct MCSLOT *this /*$s1*/, int block /*$a1*/, char *bufferPtr /*$fp*/, struct BLOCKINFO *blockInfo /*$s7*/)
{ // line 1, offset 0xf43a0
  int n; // $s5
  char verifyBuffer[128]; // stack offset -200
  char filename[32]; // stack offset -72
  long bytesRead; // $v0
  unsigned int verifyFailed; // $v0
  int retry; // $s0
  { // line 1, offset 0xf43a0
    { // line 12, offset 0xf43e4
    } // line 39, offset 0xf44a0
  } // line 39, offset 0xf44a0
  { // line 44, offset 0xf44a0
    { // line 45, offset 0xf44b8
      { // line 48, offset 0xf44b8
        { // line 48, offset 0xf44c0
          { // line 50, offset 0xf44c0
            { // line 55, offset 0xf44ec
              { // line 58, offset 0xf44f4
                { // line 61, offset 0xf44f4
                  { // line 62, offset 0xf44f4
                    { // line 67, offset 0xf4524
                    } // line 67, offset 0xf4524
                  } // line 67, offset 0xf4524
                } // line 67, offset 0xf4524
                { // line 85, offset 0xf4530
                  { // line 86, offset 0xf4530
                    { // line 91, offset 0xf455c
                    } // line 91, offset 0xf455c
                  } // line 91, offset 0xf455c
                } // line 91, offset 0xf455c
                { // line 106, offset 0xf4564
                  { // line 109, offset 0xf4584
                  } // line 109, offset 0xf4584
                } // line 109, offset 0xf4584
              } // line 109, offset 0xf4584
            } // line 121, offset 0xf458c
          } // line 121, offset 0xf458c
        } // line 126, offset 0xf458c
      } // line 127, offset 0xf45b4
    } // line 130, offset 0xf45dc
    { // line 132, offset 0xf45dc
      { // line 134, offset 0xf45dc
        { // line 142, offset 0xf4608
          { // line 143, offset 0xf4608
            int check; // $a1
          } // line 146, offset 0xf4640
        } // line 158, offset 0xf4678
      } // line 158, offset 0xf4678
    } // line 167, offset 0xf46b4
  } // line 167, offset 0xf46b4
} // line 167, offset 0xf46b4
/*
 * Offset 0xF46B4
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1261)
 * Stack frame base $sp, size 216
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ write_block__6MCSLOTR9BLOCKINFOPc(struct MCSLOT *this /*$s1*/, struct BLOCKINFO *blockInfo /*$s7*/, char *bufferPtr /*$fp*/)
{ // line 1, offset 0xf46b4
  int n; // $s5
  char verifyBuffer[128]; // stack offset -200
  char filename[32]; // stack offset -72
  int filePtr; // $v0
  long bytes; // $v0
  unsigned int verifyFailed; // $v0
  int retry; // $s0
  { // line 1, offset 0xf46b4
    { // line 12, offset 0xf46f8
    } // line 47, offset 0xf478c
  } // line 47, offset 0xf478c
  { // line 51, offset 0xf478c
    { // line 54, offset 0xf47c0
      { // line 56, offset 0xf47c0
        { // line 56, offset 0xf47cc
          { // line 58, offset 0xf47cc
            { // line 64, offset 0xf4814
              { // line 66, offset 0xf481c
                { // line 69, offset 0xf481c
                  { // line 71, offset 0xf481c
                    { // line 76, offset 0xf484c
                    } // line 76, offset 0xf484c
                  } // line 76, offset 0xf484c
                } // line 76, offset 0xf484c
                { // line 94, offset 0xf4858
                  { // line 95, offset 0xf4858
                    { // line 100, offset 0xf4884
                    } // line 100, offset 0xf4884
                  } // line 100, offset 0xf4884
                } // line 100, offset 0xf4884
                { // line 117, offset 0xf488c
                  { // line 120, offset 0xf48ac
                  } // line 120, offset 0xf48ac
                } // line 120, offset 0xf48ac
              } // line 120, offset 0xf48ac
            } // line 134, offset 0xf48b4
          } // line 134, offset 0xf48b4
        } // line 139, offset 0xf48b4
      } // line 140, offset 0xf48dc
    } // line 143, offset 0xf4924
    { // line 145, offset 0xf4924
      { // line 148, offset 0xf4924
        struct MCSLOT *this; // $s1
        { // line 148, offset 0xf4924
          { // line 148, offset 0xf4924
            int n; // $a1
          } // line 150, offset 0xf496c
          { // line 1, offset 0xf496c
            { // line 1, offset 0xf497c
            } // line 1, offset 0xf498c
          } // line 1, offset 0xf498c
          { // line 1, offset 0xf498c
            { // line 1, offset 0xf499c
            } // line 1, offset 0xf49ac
          } // line 1, offset 0xf49ac
        } // line 1, offset 0xf49ac
      } // line 1, offset 0xf49ac
    } // line 204, offset 0xf49e8
  } // line 204, offset 0xf49e8
} // line 204, offset 0xf49e8
/*
 * Offset 0xF49E8
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1473)
 * Stack frame base $sp, size 704
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ CreateBlock__6MCSLOTP10FILEFORMATP5SLICE(struct MCSLOT *this /*$s5*/, struct FILEFORMAT *fileFormatPtr /*$s4*/, struct SLICE *slicePtr /*stack 8*/)
{ // line 1, offset 0xf49e8
  int i; // $a1
  int n; // $s0
  struct _CARD header; // stack offset -680
  char filename[32]; // stack offset -168
  int filePtr; // $s1
  int bytes; // $s3
  int blockNum; // $fp
  char charBuffer[64]; // stack offset -136
  struct SLICEHEADER emptySlice; // stack offset -72
  char *charPtr; // $a2
  { // line 94, offset 0xf4d98
    { // line 97, offset 0xf4db0
    } // line 104, offset 0xf4ddc
  } // line 107, offset 0xf4ddc
  { // line 111, offset 0xf4ddc
    { // line 112, offset 0xf4df0
      { // line 113, offset 0xf4df0
        { // line 121, offset 0xf4e28
        } // line 141, offset 0xf4f28
      } // line 142, offset 0xf4f4c
    } // line 147, offset 0xf4f74
  } // line 147, offset 0xf4f74
  { // line 152, offset 0xf4f74
    struct MCSLOT *this; // $s5
    { // line 152, offset 0xf4f74
      { // line 152, offset 0xf4f74
        int n; // $a1
      } // line 152, offset 0xf4fb8
      { // line 1, offset 0xf4fb8
        { // line 1, offset 0xf4fc8
        } // line 1, offset 0xf4fd8
      } // line 1, offset 0xf4fd8
      { // line 1, offset 0xf4fd8
        { // line 1, offset 0xf4fe8
        } // line 1, offset 0xf4ff8
      } // line 1, offset 0xf4ff8
    } // line 1, offset 0xf4ff8
  } // line 1, offset 0xf4ff8
} // line 157, offset 0xf502c
/*
 * Offset 0xF502C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1640)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ DeleteBlock__6MCSLOTi(struct MCSLOT *this /*$s1*/, int block /*$a1*/)
{ // line 1, offset 0xf502c
  char filename[32]; // stack offset -48
  { // line 1, offset 0xf502c
    { // line 7, offset 0xf506c
      { // line 9, offset 0xf506c
        struct MCSLOT *this; // $s1
        { // line 9, offset 0xf506c
          { // line 9, offset 0xf506c
            int n; // $a1
          } // line 11, offset 0xf50cc
          { // line 1, offset 0xf50cc
            { // line 1, offset 0xf50dc
            } // line 1, offset 0xf50ec
          } // line 1, offset 0xf50ec
          { // line 1, offset 0xf50ec
            { // line 1, offset 0xf50fc
            } // line 1, offset 0xf510c
          } // line 1, offset 0xf510c
        } // line 1, offset 0xf510c
      } // line 1, offset 0xf510c
    } // line 26, offset 0xf5114
  } // line 28, offset 0xf512c
} // line 28, offset 0xf512c
/*
 * Offset 0xF512C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2067)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ Ascii2ShiftJis__FPsPc(short *dest /*$a0*/, char *source /*$a1*/)
{ // line 1, offset 0xf512c
  char a; // $a2
  short scode; // $v1
} // line 49, offset 0xf523c
/*
 * Offset 0xF523C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 58)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
struct MCSLOT * /*$ra*/ __6MCSLOTiiiiiiPc(struct MCSLOT *this /*$s0*/, int port /*$a1*/, int card /*$a2*/, int iconX /*$a3*/, int iconY /*stack 16*/, int clutX /*stack 20*/, int clutY /*stack 24*/, char *bufferPtr /*stack 28*/)
{ // line 1, offset 0xf523c
} // line 29, offset 0xf52d8
/*
 * Offset 0xF52F0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 159)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ MCSLOT_ctor(struct MCSLOT *this /*$s0*/, int __in_chrg /*$s1*/)
{ // line 1, offset 0xf52f0
} // line 11, offset 0xf5324
/*
 * Offset 0xF534C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 193)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ card_stop__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, offset 0xf534c
} // line 25, offset 0xf5474
/*
 * Offset 0xF5474
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 235)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ CheckCard__6MCSLOT(struct MCSLOT *this /*$s0*/)
{ // line 1, offset 0xf5474
  int card_status; // $v1
  { // line 1, offset 0xf5474
    { // line 13, offset 0xf54c0
    } // line 64, offset 0xf555c
  } // line 64, offset 0xf555c
} // line 64, offset 0xf555c
/*
 * Offset 0xF555C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 311)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ card_event__6MCSLOTi(struct MCSLOT *this /*$a0*/, int timeout /*$s0*/)
{ // line 1, offset 0xf555c
  { // line 5, offset 0xf5584
    { // line 7, offset 0xf5584
    } // line 7, offset 0xf55a4
    { // line 9, offset 0xf55a4
    } // line 9, offset 0xf55c0
    { // line 11, offset 0xf55c0
    } // line 11, offset 0xf55d4
    { // line 13, offset 0xf55d4
    } // line 13, offset 0xf55f0
  } // line 13, offset 0xf55f0
} // line 16, offset 0xf5610
/*
 * Offset 0xF5610
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 332)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ clear_event__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, offset 0xf5610
} // line 5, offset 0xf5668
/*
 * Offset 0xF5668
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 579)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ invalidate_info__6MCSLOT(struct MCSLOT *this /*$s0*/)
{ // line 1, offset 0xf5668
  { // line 1, offset 0xf5668
    int n; // $v1
  } // line 11, offset 0xf56a8
  { // line 14, offset 0xf56a8
    { // line 15, offset 0xf56b8
    } // line 17, offset 0xf56c8
  } // line 17, offset 0xf56c8
  { // line 20, offset 0xf56c8
    { // line 21, offset 0xf56d8
    } // line 23, offset 0xf56e8
  } // line 23, offset 0xf56e8
} // line 23, offset 0xf56e8
/*
 * Offset 0xF56FC
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 712)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ download_icon__6MCSLOTR9BLOCKINFOiiiii(struct MCSLOT *this /*$a0*/, struct BLOCKINFO *blockInfo /*$s2*/, int iconX /*$s3*/, int iconY /*$s4*/, int clutX /*stack 16*/, int clutY /*stack 20*/, int icon /*stack 24*/)
{ // line 1, offset 0xf56fc
  struct RECT rect; // stack offset -32
  struct TIMSTRUCT *timPtr; // $s0
  { // line 1, offset 0xf56fc
    int n; // $a0
  } // line 22, offset 0xf5790
} // line 42, offset 0xf5860
/*
 * Offset 0xF5860
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 764)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ CopyBlock__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, offset 0xf5860
} // line 15, offset 0xf5918
/*
 * Offset 0xF5918
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1130)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ PasteBlock__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, offset 0xf5918
} // line 7, offset 0xf5968
/*
 * Offset 0xF5968
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1146)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ ReadHeader__6MCSLOTii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/)
{ // line 1, offset 0xf5968
} // line 18, offset 0xf5a60
/*
 * Offset 0xF5A60
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1173)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ RenameCopyBlock__6MCSLOTP10FILEFORMAT(struct MCSLOT *this /*$a0*/, struct FILEFORMAT *fileFormatPtr /*$s1*/)
{ // line 1, offset 0xf5a60
  struct _CARD *headerptr; // $s0
} // line 6, offset 0xf5b24
/*
 * Offset 0xF5B38
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1187)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ WriteSlice__6MCSLOTiiP5SLICEP10FILEFORMATPc(struct MCSLOT *this /*$s0*/, int block /*$s4*/, int slice /*$s1*/, struct SLICE *slicePtr /*$a2*/, struct FILEFORMAT *fileFormatPtr /*stack 16*/, char *bufferPtr /*stack 20*/)
{ // line 1, offset 0xf5b38
} // line 62, offset 0xf5c70
/*
 * Offset 0xF5C70
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1675)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ SetPort__6MCSLOTii(struct MCSLOT *this /*$s0*/, int port /*$a1*/, int card /*$a2*/)
{ // line 1, offset 0xf5c70
  { // line 1, offset 0xf5c70
    struct MCSLOT *this; // $s0
    { // line 1, offset 0xf5c70
      { // line 1, offset 0xf5c70
        int n; // $v1
      } // line 7, offset 0xf5cdc
      { // line 1, offset 0xf5cdc
        { // line 1, offset 0xf5cec
        } // line 1, offset 0xf5cfc
      } // line 1, offset 0xf5cfc
      { // line 1, offset 0xf5cfc
        { // line 1, offset 0xf5d0c
        } // line 1, offset 0xf5d1c
      } // line 1, offset 0xf5d1c
    } // line 1, offset 0xf5d1c
  } // line 1, offset 0xf5d30
} // line 9, offset 0xf5d30
/*
 * Offset 0xF5D30
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1710)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ BlocksShared__6MCSLOTii(struct MCSLOT *this /*$t0*/, int block1 /*$a1*/, int block2 /*$a2*/)
{ // line 1, offset 0xf5d30
} // line 9, offset 0xf5dc0
/*
 * Offset 0xF5DC8
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1723)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetBlockSize__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, offset 0xf5dc8
} // line 4, offset 0xf5dfc
/*
 * Offset 0xF5DFC
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1731)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ CardInfoRead__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, offset 0xf5dfc
} // line 2, offset 0xf5e08
/*
 * Offset 0xF5E08
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1755)
 * Stack frame base $sp, size 0
 */
struct TIMSTRUCT * /*$ra*/ GetBlockIconPtr__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, offset 0xf5e08
} // line 8, offset 0xf5e84
/*
 * Offset 0xF5E84
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1788)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetNoUsedBlocks__6MCSLOT(struct MCSLOT *this /*$a0*/)
{ // line 1, offset 0xf5e84
} // line 6, offset 0xf5ea0
/*
 * Offset 0xF5EA0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1806)
 * Stack frame base $sp, size 0
 */
short * /*$ra*/ GetBlockTitlePtr__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, offset 0xf5ea0
} // line 7, offset 0xf5ee4
/*
 * Offset 0xF5EE4
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1822)
 * Stack frame base $sp, size 0
 */
char * /*$ra*/ GetBlockFilenamePtr__6MCSLOTi(struct MCSLOT *this /*$a0*/, int block /*$a1*/)
{ // line 1, offset 0xf5ee4
} // line 8, offset 0xf5f1c
/*
 * Offset 0xF5F1C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1836)
 * Stack frame base $sp, size 40
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
int /*$ra*/ FilenameUsed__6MCSLOTPc(struct MCSLOT *this /*$s3*/, char *filename /*$s4*/)
{ // line 1, offset 0xf5f1c
  int n; // $s0
} // line 15, offset 0xf5fbc
/*
 * Offset 0xF5FBC
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1872)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ GetNumGremBlocks__6MCSLOTPc(struct MCSLOT *this /*$s3*/, char *filename /*$s5*/)
{ // line 1, offset 0xf5fbc
  int n; // $s2
  int files; // $s4
  { // line 7, offset 0xf5ffc
    { // line 7, offset 0xf6014
      { // line 9, offset 0xf6014
      } // line 12, offset 0xf6048
    } // line 12, offset 0xf6048
  } // line 14, offset 0xf6060
} // line 16, offset 0xf6088
/*
 * Offset 0xF6088
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1896)
 * Stack frame base $sp, size 88
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ InsertSliceIntoCopyBuffer__6MCSLOTiPccccT2(struct MCSLOT *this /*$a0*/, int slice /*$s4*/, char *sliceName /*$a2*/, char icon0 /*$s7*/, int icon1 /*stack 16*/, int icon2 /*stack 20*/, char *dataPtr /*stack 24*/)
{ // line 1, offset 0xf6088
  struct SLICEHEADER *sliceHeaderPtr; // $s1
  char *sliceDataPtr; // $a3
  int sliceSize; // $a2
  struct SLICEHEADER dummySlice; // stack offset -72
  int check; // $a1
} // line 55, offset 0xf61f0
/*
 * Offset 0xF61F0
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1955)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ ExtractSliceFromCopyBuffer__6MCSLOTiPc(struct MCSLOT *this /*$a0*/, int slice /*$a1*/, char *bufferPtr /*$a0*/)
{ // line 1, offset 0xf61f0
  struct SLICEHEADER *sliceHeaderPtr; // $a2
  char *sliceDataPtr; // $a1
} // line 23, offset 0xf628c
/*
 * Offset 0xF628C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 1982)
 * Stack frame base $sp, size 0
 */
char * /*$ra*/ GetSliceFilenamePtr__6MCSLOTii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/)
{ // line 1, offset 0xf628c
} // line 15, offset 0xf633c
/*
 * Offset 0xF633C
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2001)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ SliceUsed__6MCSLOTii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/)
{ // line 1, offset 0xf633c
} // line 15, offset 0xf63e4
/*
 * Offset 0xF63EC
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2019)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetNoUsedSlices__6MCSLOTi(struct MCSLOT *this /*$a2*/, int block /*$a1*/)
{ // line 1, offset 0xf63ec
} // line 8, offset 0xf6448
/*
 * Offset 0xF6448
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2030)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetSliceIconRef__6MCSLOTiii(struct MCSLOT *this /*$a0*/, int block /*$a1*/, int slice /*$a2*/, int ref /*$a3*/)
{ // line 1, offset 0xf6448
} // line 11, offset 0xf64f4
/*
 * Offset 0xF64F4
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2044)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetNoSlices__6MCSLOTi(struct MCSLOT *this /*$a2*/, int block /*$a1*/)
{ // line 1, offset 0xf64f4
} // line 8, offset 0xf6550
/*
 * Offset 0xF6550
 * D:\driver2\game\MEMCARD\SLOT.CPP (line 2055)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ GremlinBlock__6MCSLOTi(struct MCSLOT *this /*$a2*/, int block /*$a1*/)
{ // line 1, offset 0xf6550
} // line 4, offset 0xf6588
/*
 * Offset 0xF6588
 * D:\driver2\game\MEMCARD\DELETE.C (line 10)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
long /*$ra*/ delete_file(char *filename /*$a0*/)
{ // line 5, offset 0xf6588
} // line 7, offset 0xf65a8
/*
 * Offset 0xF65A8
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 49)
 * Stack frame base $sp, size 152
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
struct DISPMAN * /*$ra*/ __7DISPMANPlPPlP3PADP10FILEFORMATib(struct DISPMAN *this /*$s2*/, long *imagePtr /*$a1*/, long **sliceIconPtrs /*stack 8*/, struct PAD *pad /*$a3*/, struct FILEFORMAT *fileFormatPtr /*stack 16*/, int language /*stack 20*/, unsigned int save /*stack 24*/)
{ // line 1, offset 0xf65a8
  int n; // $s1
  struct RECT rect; // stack offset -112
} // line 340, offset 0xf727c
/*
 * Offset 0xF72B8
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 472)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawTitleBar__7DISPMAN(struct DISPMAN *this /*$s3*/)
{ // line 1, offset 0xf72b8
  char *titleText; // $s2
  { // line 1, offset 0xf72b8
    { // line 6, offset 0xf72e4
      { // line 56, offset 0xf740c
        { // line 58, offset 0xf742c
          char *titleText2; // $s0
          int i; // $t0
        } // line 72, offset 0xf7454
      } // line 76, offset 0xf74e8
    } // line 79, offset 0xf74ec
  } // line 79, offset 0xf74ec
} // line 79, offset 0xf74ec
/*
 * Offset 0xF7508
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 555)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ DrawCards__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, offset 0xf7508
} // line 35, offset 0xf7670
/*
 * Offset 0xF7688
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 602)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawMenu__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, offset 0xf7688
} // line 92, offset 0xf79ac
/*
 * Offset 0xF79C8
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 701)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DrawKeyInfo__7DISPMAN(struct DISPMAN *this /*$s3*/)
{ // line 1, offset 0xf79c8
} // line 41, offset 0xf7c30
/*
 * Offset 0xF7C4C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 747)
 * Stack frame base $sp, size 96
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawBlocks__7DISPMAN(struct DISPMAN *this /*$s1*/)
{ // line 1, offset 0xf7c4c
  int x; // $s6
  int y; // $s2
} // line 87, offset 0xf816c
/*
 * Offset 0xF819C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 839)
 * Stack frame base $sp, size 144
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawSlices__7DISPMAN(struct DISPMAN *this /*$s2*/)
{ // line 1, offset 0xf819c
  int n; // $s3
  char textBuffer[50]; // stack offset -104
  int iconRef; // $v1
  int maxIcons; // $s1
  { // line 29, offset 0xf82bc
    { // line 30, offset 0xf82cc
      { // line 31, offset 0xf82cc
        { // line 35, offset 0xf8304
          { // line 38, offset 0xf8304
            { // line 48, offset 0xf83bc
              { // line 48, offset 0xf83bc
                { // line 57, offset 0xf8404
                  { // line 57, offset 0xf8404
                    { // line 57, offset 0xf841c
                      { // line 59, offset 0xf841c
                        { // line 59, offset 0xf8460
                          { // line 61, offset 0xf8460
                            { // line 63, offset 0xf847c
                              { // line 64, offset 0xf847c
                                { // line 65, offset 0xf8484
                                  { // line 66, offset 0xf8484
                                    { // line 67, offset 0xf84a8
                                    } // line 68, offset 0xf84a8
                                  } // line 80, offset 0xf8574
                                } // line 80, offset 0xf8574
                              } // line 116, offset 0xf8770
                            } // line 116, offset 0xf8770
                          } // line 116, offset 0xf8770
                        } // line 116, offset 0xf8770
                      } // line 122, offset 0xf8784
                    } // line 122, offset 0xf8784
                  } // line 122, offset 0xf8784
                } // line 122, offset 0xf8784
              } // line 122, offset 0xf8784
            } // line 122, offset 0xf8784
          } // line 122, offset 0xf8784
        } // line 122, offset 0xf8784
      } // line 122, offset 0xf8784
    } // line 136, offset 0xf87d4
  } // line 183, offset 0xf8ae8
} // line 189, offset 0xf8b28
/*
 * Offset 0xF8B28
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1031)
 * Stack frame base $sp, size 88
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ write_mess_in_box__7DISPMANG4RECTPciiii(struct DISPMAN *this /*$s5*/, struct RECT box /*stack 4*/, char *text /*$fp*/, int font /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, offset 0xf8b28
  int n; // $s1
  int textY; // $s2
  int messCount; // $s6
  int lineCount; // $s0
} // line 25, offset 0xf8d24
/*
 * Offset 0xF8D24
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1060)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawBlockName__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, offset 0xf8d24
} // line 40, offset 0xf8ed4
/*
 * Offset 0xF8EE4
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1327)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ActiveAreaLeft__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, offset 0xf8ee4
  int start; // $s1
} // line 43, offset 0xf9018
/*
 * Offset 0xF902C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1375)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ ActiveAreaRight__7DISPMAN(struct DISPMAN *this /*$s1*/)
{ // line 1, offset 0xf902c
  int start; // $s2
} // line 57, offset 0xf9258
/*
 * Offset 0xF9270
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1437)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ ActiveAreaUp__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, offset 0xf9270
} // line 51, offset 0xf940c
/*
 * Offset 0xF941C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1493)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ ActiveAreaDown__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, offset 0xf941c
  int start; // $s1
} // line 71, offset 0xf96dc
/*
 * Offset 0xF96F0
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1568)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ ActiveAreaSelect__7DISPMANii(struct DISPMAN *this /*$s1*/, int x /*$s2*/, int y /*$s0*/)
{ // line 1, offset 0xf96f0
  int selected; // $s0
  int newArea; // $a0
} // line 138, offset 0xf9bac
/*
 * Offset 0xF9BAC
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1728)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
int /*$ra*/ ActiveAreaConfirm__7DISPMAN(struct DISPMAN *this /*$s1*/)
{ // line 1, offset 0xf9bac
} // line 230, offset 0xf9fac
/*
 * Offset 0xF9FAC
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2044)
 * Stack frame base $sp, size 40
 */
unsigned int /*$ra*/ intersect__7DISPMANG4RECTT1(struct DISPMAN *this /*$a0*/, struct RECT rect1 /*stack 4*/, struct RECT rect2 /*stack 12*/)
{ // line 1, offset 0xf9fac
  int n; // $t0
  struct POINT p[4]; // stack offset -40
  char bitPattern[2]; // stack offset -8
} // line 34, offset 0xfa174
/*
 * Offset 0xFA174
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2139)
 * Stack frame base $sp, size 64
 * Saved registers at offset -4: s0 s1 s2 s3 s4 ra
 */
unsigned int /*$ra*/ Update__7DISPMAN(struct DISPMAN *this /*$s1*/)
{ // line 1, offset 0xfa174
  int n; // $s0
  struct RECT rect; // stack offset -32
  { // line 28, offset 0xfa238
    { // line 29, offset 0xfa260
      { // line 1, offset 0xfa260
        struct DISPMAN *this; // $s1
        { // line 1, offset 0xfa260
          int i; // $a0
        } // line 1, offset 0xfa2a4
      } // line 1, offset 0xfa2a4
      { // line 1, offset 0xfa2a4
        struct DISPMAN *this; // $s1
        { // line 1, offset 0xfa2a4
          int i; // $a0
        } // line 1, offset 0xfa2ec
      } // line 1, offset 0xfa2ec
      { // line 1, offset 0xfa2ec
        struct DISPMAN *this; // $s1
        { // line 1, offset 0xfa2ec
          int i; // $a0
        } // line 1, offset 0xfa334
      } // line 1, offset 0xfa334
      { // line 1, offset 0xfa334
        struct DISPMAN *this; // $s1
        { // line 1, offset 0xfa334
          int i; // $a0
        } // line 1, offset 0xfa37c
      } // line 1, offset 0xfa37c
      { // line 1, offset 0xfa37c
        struct DISPMAN *this; // $s1
        { // line 1, offset 0xfa37c
        } // line 1, offset 0xfa39c
      } // line 1, offset 0xfa39c
    } // line 38, offset 0xfa39c
  } // line 38, offset 0xfa39c
  { // line 49, offset 0xfa3d8
    { // line 52, offset 0xfa3e8
      { // line 53, offset 0xfa3e8
        { // line 53, offset 0xfa3ec
          { // line 1, offset 0xfa3ec
            struct DISPMAN *this; // $s1
            int n; // $s0
            { // line 1, offset 0xfa3ec
            } // line 1, offset 0xfa47c
          } // line 1, offset 0xfa47c
        } // line 53, offset 0xfa47c
      } // line 53, offset 0xfa488
    } // line 53, offset 0xfa488
  } // line 53, offset 0xfa488
} // line 127, offset 0xfa684
/*
 * Offset 0xFA684
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2271)
 * Stack frame base $sp, size 352
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ PrintKanji__7DISPMANPsiiiiii(struct DISPMAN *this /*$s1*/, short *string /*$s0*/, int x /*$s4*/, int y /*$fp*/, int maxChars /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, offset 0xfa684
  char textBuffer[256]; // stack offset -312
  int lookup; // $a1
  int n; // stack offset -48
  short *sjisPtr; // $s0
  short sjisCode[3]; // stack offset -56
  int chars; // $v1
} // line 79, offset 0xfa97c
/*
 * Offset 0xFA97C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2402)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ darken__7DISPMANG4RECT(struct DISPMAN *this /*$s0*/, struct RECT rect /*stack 4*/)
{ // line 1, offset 0xfa97c
} // line 31, offset 0xfacc4
/*
 * Offset 0xFACD4
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2670)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ DrawSprite__7DISPMANP9TIMSTRUCTiiiiii(struct DISPMAN *this /*$s0*/, struct TIMSTRUCT *tim /*$s1*/, int x /*$s2*/, int y /*$s3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/, int trans /*stack 28*/)
{ // line 1, offset 0xfacd4
} // line 25, offset 0xfaed0
/*
 * Offset 0xFAED0
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2743)
 * Stack frame base $sp, size 56
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ AddCircleG16__7DISPMANiiiiiiii(struct DISPMAN *this /*$s0*/, int x /*stack 4*/, int y /*stack 8*/, int diameter /*$a3*/, int complete /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/, int divisor /*stack 32*/)
{ // line 1, offset 0xfaed0
  int modX; // $s6
  int modY; // $s5
  { // line 10, offset 0xfaf54
    int n; // $s3
  } // line 31, offset 0xfb304
} // line 31, offset 0xfb304
/*
 * Offset 0xFB304
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2786)
 * Stack frame base $sp, size 344
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
short /*$ra*/ MessageBox__7DISPMANiPcbT3(struct DISPMAN *this /*$s5*/, int type /*stack 4*/, char *text /*stack 8*/, unsigned int bIgnoreEvents /*stack 12*/, unsigned int bSwapKeys /*stack 16*/)
{ // line 1, offset 0xfb304
  int boxHeight; // $s6
  int boxTop; // stack offset -72
  int maxTextLen; // stack offset -68
  int textLen; // $s0
  int textY; // $s3
  int lineCount; // $s1
  struct RECT darkRect; // stack offset -304
  struct RECT rect; // stack offset -296
  char textBuffer[128]; // stack offset -288
  int sel; // $fp
  unsigned int cardState; // stack offset -64
  unsigned int bInBox; // $s4
  int n; // $s2
  int messCount; // $s7
  short padData; // $s4
  { // line 102, offset 0xfb79c
    struct DISPMAN *this; // $s5
    struct RECT rect; // stack offset -148
    { // line 102, offset 0xfb79c
      int n; // $s2
    } // line 113, offset 0xfb8d0
  } // line 113, offset 0xfb8d0
  { // line 117, offset 0xfb8d0
    { // line 120, offset 0xfb8fc
      { // line 124, offset 0xfb954
        { // line 127, offset 0xfb984
          { // line 129, offset 0xfb9a8
            struct DISPMAN *this; // $s5
            int y; // $s3
            { // line 129, offset 0xfb9a8
              struct LINE_F2 strF2; // stack offset -88
              struct LINE_F4 strF4; // stack offset -120
            } // line 129, offset 0xfb9a8
          } // line 129, offset 0xfb9a8
          { // line 130, offset 0xfba68
            struct DISPMAN *this; // $s5
            int y; // $s3
            { // line 130, offset 0xfba68
              struct LINE_F2 strF2; // stack offset -128
              struct LINE_F4 strF4; // stack offset -160
            } // line 130, offset 0xfba68
          } // line 130, offset 0xfba68
          { // line 133, offset 0xfbb2c
            struct DISPMAN *this; // $s5
            int y; // $s3
            { // line 133, offset 0xfbb2c
              struct LINE_F2 strF2; // stack offset -128
              struct LINE_F4 strF4; // stack offset -160
            } // line 133, offset 0xfbbc8
          } // line 133, offset 0xfbbc8
        } // line 136, offset 0xfbbc8
      } // line 136, offset 0xfbbc8
      { // line 141, offset 0xfbc34
        { // line 176, offset 0xfbd50
          { // line 179, offset 0xfbd80
            { // line 1, offset 0xfbdd4
              struct DISPMAN *this; // $s5
              int y; // $s3
              int r; // $s2
              int g; // $s1
              int b; // $s0
              { // line 1, offset 0xfbdd4
                struct LINE_F2 strF2; // stack offset -128
                struct LINE_F4 strF4; // stack offset -160
              } // line 1, offset 0xfbdd4
            } // line 1, offset 0xfbdd4
            { // line 1, offset 0xfbefc
              struct DISPMAN *this; // $s5
              int y; // $s3
              int r; // $s2
              int g; // $s1
              int b; // $s0
              { // line 1, offset 0xfbefc
                struct LINE_F2 strF2; // stack offset -128
                struct LINE_F4 strF4; // stack offset -160
              } // line 1, offset 0xfbefc
            } // line 1, offset 0xfbefc
            { // line 188, offset 0xfc01c
              struct DISPMAN *this; // $s5
              int y; // $s3
              int r; // $s1
              { // line 188, offset 0xfc01c
                struct LINE_F2 strF2; // stack offset -128
                struct LINE_F4 strF4; // stack offset -160
              } // line 188, offset 0xfc0cc
            } // line 188, offset 0xfc0cc
          } // line 191, offset 0xfc0cc
        } // line 191, offset 0xfc0cc
      } // line 207, offset 0xfc138
    } // line 233, offset 0xfc278
    { // line 236, offset 0xfc280
      { // line 240, offset 0xfc2b0
        { // line 241, offset 0xfc2f0
          { // line 244, offset 0xfc2fc
            { // line 1, offset 0xfc390
              struct DISPMAN *this; // $s5
              int y; // $s3
              { // line 1, offset 0xfc390
                struct LINE_F2 strF2; // stack offset -128
                struct LINE_F4 strF4; // stack offset -160
              } // line 1, offset 0xfc390
            } // line 1, offset 0xfc390
            { // line 1, offset 0xfc474
              struct DISPMAN *this; // $s5
              int y; // $s3
              { // line 1, offset 0xfc474
                struct LINE_F2 strF2; // stack offset -128
                struct LINE_F4 strF4; // stack offset -160
              } // line 1, offset 0xfc474
            } // line 1, offset 0xfc474
          } // line 266, offset 0xfc540
          { // line 283, offset 0xfc650
            struct DISPMAN *this; // $s5
            int y; // $s3
            int w; // $v0
            { // line 283, offset 0xfc650
              struct LINE_F2 strF2; // stack offset -128
              struct LINE_F4 strF4; // stack offset -160
            } // line 283, offset 0xfc650
          } // line 283, offset 0xfc650
          { // line 308, offset 0xfc848
            struct DISPMAN *this; // $s5
            int y; // $s3
            int w; // $v0
            { // line 308, offset 0xfc848
              struct LINE_F2 strF2; // stack offset -128
              struct LINE_F4 strF4; // stack offset -160
            } // line 308, offset 0xfc8e8
          } // line 308, offset 0xfc8e8
        } // line 313, offset 0xfc8f0
      } // line 313, offset 0xfc8f0
    } // line 313, offset 0xfc8f0
  } // line 313, offset 0xfc8f0
} // line 321, offset 0xfc950
/*
 * Offset 0xFC950
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3112)
 * Stack frame base $sp, size 232
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
struct RECT /*$ra*/ ProgressBox__7DISPMANPci(struct DISPMAN *this /*$s3*/, char *text /*$fp*/, int progress /*stack 12*/)
{ // line 1, offset 0xfc950
  int boxHeight; // $s4
  int boxTop; // stack offset -48
  int maxTextLen; // $s7
  int textLen; // $v1
  int textY; // $s1
  int lineCount; // $s0
  struct RECT darkRect; // stack offset -192
  char textBuffer[128]; // stack offset -184
  int n; // $s2
  int messCount; // $s6
} // line 39, offset 0xfcb08
/*
 * Offset 0xFCC54
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3182)
 * Stack frame base $sp, size 312
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ message_width__7DISPMANPcii(struct DISPMAN *this /*$s3*/, char *mesPtr /*$s1*/, int font /*$a2*/, int maxChars /*$s6*/)
{ // line 1, offset 0xfcc54
  char c; // $a1
  int fRef; // $s0
  int w; // $s2
  int n; // $s5
  { // line 1, offset 0xfcc54
    { // line 7, offset 0xfcc98
      { // line 1, offset 0xfcc98
        short *kanjiStringPtr; // $s1
        int maxChars; // $s6
        { // line 1, offset 0xfcc98
          int totalLen; // $a1
          short textBuffer[128]; // stack offset -296
        } // line 1, offset 0xfcd04
      } // line 1, offset 0xfcd04
    } // line 8, offset 0xfcd0c
  } // line 27, offset 0xfce00
} // line 27, offset 0xfce00
/*
 * Offset 0xFCE00
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3214)
 * Stack frame base $sp, size 184
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ justify_mess__7DISPMANPcii(struct DISPMAN *this /*$fp*/, char *messPtr /*$s3*/, int font /*stack 8*/, int maxLineLength /*$s7*/)
{ // line 1, offset 0xfce00
  char c; // $s0
  short kanji; // $s0
  char word[128]; // stack offset -168
  int wordCount; // $s1
  int lineLength; // $s6
  int lineCount; // $s4
} // line 117, offset 0xfd000
/*
 * Offset 0xFD000
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3337)
 * Stack frame base $sp, size 88
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ write_mess__7DISPMANPciiiiiiii(struct DISPMAN *this /*$s2*/, char *mesPtr /*$s6*/, int x /*$s3*/, int y /*stack 12*/, int font /*stack 16*/, int maxChars /*stack 20*/, int r /*stack 24*/, int g /*stack 28*/, int b /*stack 32*/, int trans /*stack 36*/)
{ // line 1, offset 0xfd000
  int fRef; // $s1
  int n; // stack offset -56
  char c; // $s0
  { // line 1, offset 0xfd000
    { // line 9, offset 0xfd080
      { // line 11, offset 0xfd0f4
        { // line 20, offset 0xfd124
          { // line 21, offset 0xfd134
            { // line 22, offset 0xfd134
              struct DISPMAN *this; // $s2
              struct TIMSTRUCT *tim; // $a3
              int y; // stack offset 12
              int r; // $t1
              int g; // $t0
              int b; // $a3
              int trans; // $v0
              { // line 22, offset 0xfd134
                struct DR_TPAGE *tpagePtr; // $a2
                struct SPRT *spritePtr; // $a1
              } // line 29, offset 0xfd27c
            } // line 29, offset 0xfd27c
          } // line 29, offset 0xfd27c
        } // line 29, offset 0xfd27c
        { // line 39, offset 0xfd2a4
          { // line 40, offset 0xfd2b0
            { // line 1, offset 0xfd2b0
              struct DISPMAN *this; // $s2
              struct TIMSTRUCT *tim; // $a3
              int x; // $s3
              int y; // stack offset 12
              int r; // $t1
              int g; // $t0
              int b; // $a3
              int trans; // $v0
              { // line 1, offset 0xfd2b0
                struct DR_TPAGE *tpagePtr; // $a2
                struct SPRT *spritePtr; // $a1
              } // line 1, offset 0xfd2b0
            } // line 1, offset 0xfd2b0
          } // line 44, offset 0xfd3a4
        } // line 44, offset 0xfd3a4
      } // line 44, offset 0xfd3a4
    } // line 49, offset 0xfd410
  } // line 49, offset 0xfd410
} // line 49, offset 0xfd410
/*
 * Offset 0xFD410
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3392)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ font_ref__7DISPMANcb(struct DISPMAN *this /*$a0*/, char c /*$a1*/, unsigned int accent /*$a2*/)
{ // line 1, offset 0xfd410
} // line 127, offset 0xfd650
/*
 * Offset 0xFD658
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3524)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ Tim2VRAM__7DISPMANPlP9TIMSTRUCTibiiii(struct DISPMAN *this /*$a0*/, long *timDataPtr /*$s0*/, struct TIMSTRUCT *destTimPtr /*$s2*/, int abr /*$s1*/, unsigned int setCoords /*stack 16*/, int clutX /*stack 20*/, int clutY /*stack 24*/, int iconX /*stack 28*/, int iconY /*stack 32*/)
{ // line 1, offset 0xfd658
  long flag; // $a0
  struct RECT *timRect; // $a2
  { // line 19, offset 0xfd6a4
    { // line 25, offset 0xfd6b8
      { // line 34, offset 0xfd6d8
        { // line 39, offset 0xfd6f0
          { // line 40, offset 0xfd6f0
            int n; // $a0
          } // line 45, offset 0xfd718
        } // line 45, offset 0xfd718
      } // line 45, offset 0xfd718
    } // line 52, offset 0xfd740
  } // line 52, offset 0xfd740
} // line 87, offset 0xfd86c
/*
 * Offset 0xFD86C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3749)
 * Stack frame base $sp, size 264
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ wipe_screen__7DISPMANii(struct DISPMAN *this /*$s1*/, int wt /*$s3*/, int step /*$s5*/)
{ // line 1, offset 0xfd86c
  int i; // $s2
  struct DRAWENV drawenv; // stack offset -248
  struct DISPENV de; // stack offset -152
  unsigned long fadeOt[3]; // stack offset -128
  struct POLY_GT3 FadeSetTp; // stack offset -112
  struct POLY_G4 FadePol; // stack offset -72
} // line 57, offset 0xfdad8
/*
 * Offset 0xFDAD8
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 392)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DISPMAN_ctor(struct DISPMAN *this /*$s2*/, int __in_chrg /*$s3*/)
{ // line 1, offset 0xfdad8
  struct RECT rect; // stack offset -32
} // line 14, offset 0xfdb38
/*
 * Offset 0xFDBEC
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1105)
 * Stack frame base $sp, size 112
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ DrawEnterName__7DISPMANPc(struct DISPMAN *this /*$s0*/, char *ascii /*$a3*/)
{ // line 1, offset 0xfdbec
  char message[64]; // stack offset -72
} // line 6, offset 0xfdc6c
/*
 * Offset 0xFDC6C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1114)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ SetMenuOption__7DISPMANi(struct DISPMAN *this /*$s0*/, int menuOption /*$s1*/)
{ // line 1, offset 0xfdc6c
} // line 7, offset 0xfdca8
/*
 * Offset 0xFDCBC
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1125)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ SetActiveFunction__7DISPMANi(struct DISPMAN *this /*$a0*/, int menuOption /*$a1*/)
{ // line 1, offset 0xfdcbc
} // line 2, offset 0xfdcc4
/*
 * Offset 0xFDCC4
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1131)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ MoveActiveAreaTo__7DISPMANi(struct DISPMAN *this /*$s0*/, int area /*$s1*/)
{ // line 1, offset 0xfdcc4
} // line 5, offset 0xfdd0c
/*
 * Offset 0xFDD0C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1249)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
void /*$ra*/ SelectNewBlock__7DISPMANi(struct DISPMAN *this /*$s0*/, int newBlock /*$a1*/)
{ // line 1, offset 0xfdd0c
} // line 16, offset 0xfddc0
/*
 * Offset 0xFDDD0
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1710)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetArea__7DISPMANii(struct DISPMAN *this /*$a0*/, int x /*$a1*/, int y /*$a2*/)
{ // line 1, offset 0xfddd0
  int n; // $a3
} // line 15, offset 0xfde48
/*
 * Offset 0xFDE50
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 1962)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ ActiveAreaCancel__7DISPMAN(struct DISPMAN *this /*$s0*/)
{ // line 1, offset 0xfde50
} // line 53, offset 0xfdf58
/*
 * Offset 0xFDF58
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2028)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ AddingBlock__7DISPMANi(struct DISPMAN *this /*$a0*/, int n /*$a1*/)
{ // line 1, offset 0xfdf58
} // line 1, offset 0xfdf60
/*
 * Offset 0xFDF60
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2030)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ DeletingCurrBlock__7DISPMANi(struct DISPMAN *this /*$a0*/, int n /*$a1*/)
{ // line 1, offset 0xfdf60
} // line 1, offset 0xfdf68
/*
 * Offset 0xFDF68
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2033)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ InvalidateArea__7DISPMANG4RECT(struct DISPMAN *this /*$s3*/, struct RECT rect /*stack 4*/)
{ // line 1, offset 0xfdf68
  int n; // $s2
} // line 7, offset 0xfe040
/*
 * Offset 0xFE040
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2081)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ InvalidateArea__7DISPMANi(struct DISPMAN *this /*$a0*/, int n /*$a1*/)
{ // line 1, offset 0xfe040
  int i; // $a2
} // line 14, offset 0xfe090
/*
 * Offset 0xFE098
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2100)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ DrawArea__7DISPMANi(struct DISPMAN *this /*$a2*/, int n /*$a1*/)
{ // line 1, offset 0xfe098
} // line 26, offset 0xfe134
/*
 * Offset 0xFE144
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2129)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ FlashOn__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, offset 0xfe144
} // line 1, offset 0xfe150
/*
 * Offset 0xFE150
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2132)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ FlashOff__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, offset 0xfe150
} // line 3, offset 0xfe160
/*
 * Offset 0xFE160
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2355)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ FindKanji__7DISPMANs(struct DISPMAN *this /*$a0*/, short sjisCode /*$a1*/)
{ // line 1, offset 0xfe160
  int n; // $v1
} // line 12, offset 0xfe1a8
/*
 * Offset 0xFE1B0
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2371)
 * Stack frame base $sp, size 72
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ CentrePrintKanji__7DISPMANPsiiiiii(struct DISPMAN *this /*$s5*/, short *string /*$s3*/, int x /*$s6*/, int y /*$s7*/, int maxChars /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, offset 0xfe1b0
} // line 4, offset 0xfe258
/*
 * Offset 0xFE258
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2379)
 * Stack frame base $sp, size 288
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ KanjiStrLen__FPsi(short *kanjiStringPtr /*$s1*/, int maxChars /*$s0*/)
{ // line 1, offset 0xfe258
  short textBuffer[128]; // stack offset -272
  int totalLen; // $a1
} // line 17, offset 0xfe2f4
/*
 * Offset 0xFE2F4
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2474)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetCurrBlock__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, offset 0xfe2f4
} // line 1, offset 0xfe300
/*
 * Offset 0xFE300
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2476)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetCurrSlice__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, offset 0xfe300
} // line 1, offset 0xfe30c
/*
 * Offset 0xFE30C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2480)
 * Stack frame base $sp, size 64
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ draw_card__7DISPMANiiPcb(struct DISPMAN *this /*$s1*/, int x /*$s2*/, int y /*$s3*/, char *text /*$a1*/, unsigned int selected /*stack 16*/)
{ // line 1, offset 0xfe30c
} // line 15, offset 0xfe418
/*
 * Offset 0xFE434
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2515)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ AddIcon__7DISPMANP9TIMSTRUCTiiiiiib(struct DISPMAN *this /*$a0*/, struct TIMSTRUCT *tim /*$t2*/, int x /*$a2*/, int y /*$a1*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/, int trans /*stack 28*/, unsigned int scale /*stack 32*/)
{ // line 1, offset 0xfe434
  int XPlusW; // $t1
  int YPlusH; // $a0
  struct POLY_FT4 *polyFT4Ptr; // $t0
} // line 45, offset 0xfe590
/*
 * Offset 0xFE598
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2616)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ AddMoveImage__7DISPMANP4RECTT1(struct DISPMAN *this /*$s0*/, struct RECT *srect /*$a1*/, struct RECT *drect /*$t0*/)
{ // line 1, offset 0xfe598
  struct DR_MOVE *movePtr; // $s0
} // line 9, offset 0xfe61c
/*
 * Offset 0xFE61C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2630)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ AddSprite__7DISPMANP9TIMSTRUCTiiiiii(struct DISPMAN *this /*$a0*/, struct TIMSTRUCT *tim /*$a1*/, int x /*$a2*/, int y /*$a3*/, int r /*stack 16*/, int g /*stack 20*/, int b /*stack 24*/, int trans /*stack 28*/)
{ // line 1, offset 0xfe61c
  struct SPRT *spritePtr; // $t0
  struct DR_TPAGE *tpagePtr; // $a0
} // line 36, offset 0xfe72c
/*
 * Offset 0xFE72C
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 2699)
 * Stack frame base $sp, size 104
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ DrawBox__7DISPMANiiiiiii(struct DISPMAN *this /*$a0*/, int x /*$s2*/, int y /*$s3*/, int w /*$s1*/, int h /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, offset 0xfe72c
  struct LINE_F4 strF4; // stack offset -88
  struct LINE_F2 strF2; // stack offset -56
} // line 32, offset 0xfe834
/*
 * Offset 0xFE834
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3172)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ write_mess_c__7DISPMANPciiiiiiii(struct DISPMAN *this /*$s0*/, char *mesPtr /*$s1*/, int x /*stack 8*/, int y /*$s4*/, int font /*stack 16*/, int maxChars /*stack 20*/, int r /*stack 24*/, int g /*stack 28*/, int b /*stack 32*/, int trans /*stack 36*/)
{ // line 1, offset 0xfe834
  int w; // $s0
} // line 6, offset 0xfe908
/*
 * Offset 0xFE908
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3615)
 * Stack frame base $sp, size 48
 * Saved registers at offset -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ download_block_icon__7DISPMANiiii(struct DISPMAN *this /*$s2*/, int iconX /*$s3*/, int iconY /*$s1*/, int clutX /*$a3*/, int clutY /*stack 16*/)
{ // line 1, offset 0xfe908
  struct RECT rect; // stack offset -32
  struct TIMSTRUCT *timPtr; // $s0
  unsigned short *clutWordPtr; // $v1
  { // line 1, offset 0xfe908
    int n; // $a0
  } // line 22, offset 0xfe998
} // line 42, offset 0xfea44
/*
 * Offset 0xFEA44
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3809)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ move_screen__7DISPMANiii(struct DISPMAN *this /*$s0*/, int startY /*$a1*/, int finishY /*$s3*/, int steps /*$a3*/)
{ // line 1, offset 0xfea44
  int screenY; // $s1
} // line 26, offset 0xfeb00
/*
 * Offset 0xFEB24
 * D:\driver2\game\MEMCARD\DISPLAY.CPP (line 3840)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetCyclesPerSecond__7DISPMAN(struct DISPMAN *this /*$a0*/)
{ // line 1, offset 0xfeb24
} // line 14, offset 0xfeb70
/*
 * Offset 0xFEB70
 * D:\driver2\game\MEMCARD\PAD.CPP (line 32)
 * Stack frame base $sp, size 48
 * Saved registers at offset -4: s0 s1 s2 ra
 */
struct PAD * /*$ra*/ __3PADPc(struct PAD *this /*$s1*/, char *bufferPtr /*$a1*/)
{ // line 1, offset 0xfeb70
} // line 28, offset 0xfec44
/*
 * Offset 0xFECC0
 * D:\driver2\game\MEMCARD\PAD.CPP (line 137)
 * Stack frame base $sp, size 72
 * Saved registers at offset -4: s0 s1 s2 ra
 */
unsigned short /*$ra*/ GetPadData__3PADi(struct PAD *this /*$s1*/, int pad /*$s0*/)
{ // line 1, offset 0xfecc0
  struct ControllerPacket cData; // stack offset -56
  unsigned short retVal; // $s2
} // line 296, offset 0xff2cc
/*
 * Offset 0xFF2CC
 * D:\driver2\game\MEMCARD\PAD.CPP (line 527)
 * Stack frame base $sp, size 0
 */
char * /*$ra*/ port_name__3PADi(struct PAD *this /*$a2*/, int port /*$a1*/)
{ // line 1, offset 0xff2cc
} // line 36, offset 0xff3b8
/*
 * Offset 0xFF3C0
 * D:\driver2\game\MEMCARD\PAD.CPP (line 569)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
unsigned int /*$ra*/ WaitUntilCardRemoved__3PADi(struct PAD *this /*$s3*/, int slot /*$a1*/)
{ // line 1, offset 0xff3c0
  struct RECT rect; // stack offset -48
  short padData; // $a0
  unsigned int bInBox; // $s2
  { // line 8, offset 0xff410
    { // line 14, offset 0xff448
      { // line 1, offset 0xff448
        struct PAD *this; // $s3
        { // line 1, offset 0xff448
        } // line 1, offset 0xff4bc
      } // line 1, offset 0xff4bc
      { // line 15, offset 0xff4c4
        { // line 16, offset 0xff4c4
          struct PAD *this; // $s3
          { // line 16, offset 0xff4c4
          } // line 16, offset 0xff4c4
        } // line 16, offset 0xff4c4
        { // line 16, offset 0xff4c4
          struct PAD *this; // $s3
          { // line 16, offset 0xff4c4
          } // line 16, offset 0xff4c4
        } // line 16, offset 0xff4c4
        { // line 16, offset 0xff4c4
          struct PAD *this; // $s3
          { // line 16, offset 0xff4c4
          } // line 16, offset 0xff4c4
        } // line 16, offset 0xff4c4
        { // line 1, offset 0xff564
          struct PAD *this; // $s3
          { // line 1, offset 0xff564
          } // line 1, offset 0xff564
        } // line 1, offset 0xff564
        { // line 1, offset 0xff57c
          struct PAD *this; // $s3
          { // line 1, offset 0xff57c
          } // line 1, offset 0xff57c
        } // line 1, offset 0xff57c
        { // line 1, offset 0xff594
          struct PAD *this; // $s3
          { // line 1, offset 0xff594
          } // line 1, offset 0xff594
        } // line 1, offset 0xff594
        { // line 45, offset 0xff5a4
          struct PAD *this; // $s3
          { // line 45, offset 0xff5a4
          } // line 45, offset 0xff5a4
        } // line 45, offset 0xff5a4
        { // line 45, offset 0xff5a4
          struct PAD *this; // $s3
          { // line 45, offset 0xff5a4
          } // line 45, offset 0xff5a4
        } // line 45, offset 0xff5a4
      } // line 56, offset 0xff664
    } // line 64, offset 0xff6b4
  } // line 64, offset 0xff6b4
} // line 64, offset 0xff6e4
/*
 * Offset 0xFF6E4
 * D:\driver2\game\MEMCARD\PAD.CPP (line 655)
 * Stack frame base $sp, size 80
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
unsigned int /*$ra*/ WaitUntilAnyCardInserted__3PAD(struct PAD *this /*$s3*/)
{ // line 1, offset 0xff6e4
  struct RECT rect; // stack offset -48
  unsigned int bInBox; // $s2
  { // line 8, offset 0xff730
    { // line 20, offset 0xff7a0
      { // line 1, offset 0xff7a0
        struct PAD *this; // $s3
        { // line 1, offset 0xff7a0
        } // line 1, offset 0xff814
      } // line 1, offset 0xff814
      { // line 21, offset 0xff81c
        { // line 22, offset 0xff81c
          struct PAD *this; // $s3
          { // line 22, offset 0xff81c
          } // line 22, offset 0xff81c
        } // line 22, offset 0xff81c
        { // line 22, offset 0xff81c
          struct PAD *this; // $s3
          { // line 22, offset 0xff81c
          } // line 22, offset 0xff81c
        } // line 22, offset 0xff81c
        { // line 22, offset 0xff81c
          struct PAD *this; // $s3
          { // line 22, offset 0xff81c
          } // line 22, offset 0xff81c
        } // line 22, offset 0xff81c
        { // line 1, offset 0xff8c0
          struct PAD *this; // $s3
          { // line 1, offset 0xff8c0
          } // line 1, offset 0xff8c0
        } // line 1, offset 0xff8c0
        { // line 1, offset 0xff8d8
          struct PAD *this; // $s3
          { // line 1, offset 0xff8d8
          } // line 1, offset 0xff8d8
        } // line 1, offset 0xff8d8
        { // line 1, offset 0xff8f0
          struct PAD *this; // $s3
          { // line 1, offset 0xff8f0
          } // line 1, offset 0xff8f0
        } // line 1, offset 0xff8f0
        { // line 53, offset 0xff900
          struct PAD *this; // $s3
          { // line 53, offset 0xff900
          } // line 53, offset 0xff900
        } // line 53, offset 0xff900
        { // line 53, offset 0xff900
          struct PAD *this; // $s3
          { // line 53, offset 0xff900
          } // line 53, offset 0xff900
        } // line 53, offset 0xff900
      } // line 63, offset 0xff9b0
    } // line 71, offset 0xff9ec
  } // line 71, offset 0xff9ec
} // line 71, offset 0xffa1c
/*
 * Offset 0xFFA1C
 * D:\driver2\game\MEMCARD\PAD.CPP (line 794)
 * Stack frame base $sp, size 32
 * Saved registers at offset -4: s0 s1 s2 ra
 */
void /*$ra*/ check_ports__3PAD(struct PAD *this /*$s1*/)
{ // line 1, offset 0xffa1c
} // line 102, offset 0xffc80
/*
 * Offset 0xFFC98
 * D:\driver2\game\MEMCARD\PAD.CPP (line 905)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ search_ports__3PADib(struct PAD *this /*$s4*/, int slot /*$s0*/, unsigned int cycle /*$a2*/)
{ // line 1, offset 0xffc98
} // line 46, offset 0xffe18
/*
 * Offset 0xFFE44
 * D:\driver2\game\MEMCARD\PAD.CPP (line 89)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
void /*$ra*/ PAD_ctor(struct PAD *this /*$s1*/, int __in_chrg /*$s0*/)
{ // line 1, offset 0xffe44
} // line 1, offset 0xffe44
/*
 * Offset 0xFFEA0
 * D:\driver2\game\MEMCARD\PAD.CPP (line 103)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
int /*$ra*/ UpdateSlots__3PAD(struct PAD *this /*$s0*/)
{ // line 1, offset 0xffea0
} // line 31, offset 0xffee0
/*
 * Offset 0xFFEE0
 * D:\driver2\game\MEMCARD\PAD.CPP (line 437)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ NegConInserted__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0xffee0
} // line 8, offset 0xfff10
/*
 * Offset 0xFFF10
 * D:\driver2\game\MEMCARD\PAD.CPP (line 448)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ ControllerInserted__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0xfff10
} // line 12, offset 0xfff48
/*
 * Offset 0xFFF48
 * D:\driver2\game\MEMCARD\PAD.CPP (line 463)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ ControllerChanged__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0xfff48
} // line 2, offset 0xfff5c
/*
 * Offset 0xFFF5C
 * D:\driver2\game\MEMCARD\PAD.CPP (line 468)
 * Stack frame base $sp, size 56
 */
unsigned int /*$ra*/ SetControllerType__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0xfff5c
  struct ControllerPacket cData; // stack offset -40
} // line 19, offset 0x1000d0
/*
 * Offset 0x1000D0
 * D:\driver2\game\MEMCARD\PAD.CPP (line 490)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ MouseInserted__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x1000d0
} // line 22, offset 0x100158
/*
 * Offset 0x100158
 * D:\driver2\game\MEMCARD\PAD.CPP (line 514)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetMouseX__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x100158
} // line 1, offset 0x10016c
/*
 * Offset 0x10016C
 * D:\driver2\game\MEMCARD\PAD.CPP (line 515)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetMouseY__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x10016c
} // line 1, offset 0x100180
/*
 * Offset 0x100180
 * D:\driver2\game\MEMCARD\PAD.CPP (line 519)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
void /*$ra*/ ResetPadData__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x100180
} // line 2, offset 0x1001ac
/*
 * Offset 0x1001AC
 * D:\driver2\game\MEMCARD\PAD.CPP (line 733)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
char * /*$ra*/ GetPortName__3PADi(struct PAD *this /*$s1*/, int slot /*$s0*/)
{ // line 1, offset 0x1001ac
} // line 6, offset 0x100214
/*
 * Offset 0x100214
 * D:\driver2\game\MEMCARD\PAD.CPP (line 757)
 * Stack frame base $sp, size 24
 * Saved registers at offset -4: s0 ra
 */
char * /*$ra*/ GetControllerPortName__3PAD(struct PAD *this /*$s0*/)
{ // line 1, offset 0x100214
} // line 4, offset 0x100244
/*
 * Offset 0x100244
 * D:\driver2\game\MEMCARD\PAD.CPP (line 778)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ CardSelected__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
{ // line 1, offset 0x100244
} // line 2, offset 0x100260
/*
 * Offset 0x100260
 * D:\driver2\game\MEMCARD\PAD.CPP (line 783)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
unsigned int /*$ra*/ CurrCardInfoRead__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x100260
} // line 2, offset 0x10029c
/*
 * Offset 0x10029C
 * D:\driver2\game\MEMCARD\PAD.CPP (line 956)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ next_port__3PADi(struct PAD *this /*$a0*/, int port /*$a1*/)
{ // line 1, offset 0x10029c
} // line 17, offset 0x1002a4
/*
 * Offset 0x1002A4
 * D:\driver2\game\MEMCARD\PAD.CPP (line 978)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
int /*$ra*/ GetCurrNoUsedBlocks__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x1002a4
} // line 2, offset 0x1002e0
/*
 * Offset 0x1002E0
 * D:\driver2\game\MEMCARD\PAD.CPP (line 984)
 * Stack frame base $sp, size 24
 * Saved registers at offset -8: ra
 */
unsigned int /*$ra*/ CurrSlotBlocksShared__3PADii(struct PAD *this /*$a0*/, int block1 /*$a1*/, int block2 /*$a2*/)
{ // line 1, offset 0x1002e0
} // line 2, offset 0x10031c
/*
 * Offset 0x10031C
 * D:\driver2\game\MEMCARD\PAD.CPP (line 1001)
 * Stack frame base $sp, size 0
 */
struct MCSLOT * /*$ra*/ GetCurrSlotPtr__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x10031c
} // line 2, offset 0x100340
/*
 * Offset 0x100340
 * D:\driver2\game\MEMCARD\PAD.CPP (line 1006)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ GetCurrSlot__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x100340
} // line 2, offset 0x100354
/*
 * Offset 0x100354
 * D:\driver2\game\MEMCARD\PAD.CPP (line 1011)
 * Stack frame base $sp, size 0
 */
struct MCSLOT * /*$ra*/ GetDestSlotPtr__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x100354
} // line 2, offset 0x10037c
/*
 * Offset 0x10037C
 * D:\driver2\game\MEMCARD\PAD.CPP (line 1017)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ CardChanged__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
{ // line 1, offset 0x10037c
} // line 5, offset 0x1003a8
/*
 * Offset 0x1003B0
 * D:\driver2\game\MEMCARD\PAD.CPP (line 1029)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ CardInserted__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
{ // line 1, offset 0x1003b0
} // line 2, offset 0x1003e4
/*
 * Offset 0x1003E4
 * D:\driver2\game\MEMCARD\PAD.CPP (line 1035)
 * Stack frame base $sp, size 0
 */
void /*$ra*/ CycleSelectedSlot__3PAD(struct PAD *this /*$a0*/)
{ // line 1, offset 0x1003e4
} // line 4, offset 0x10042c
/*
 * Offset 0x10042C
 * D:\driver2\game\MEMCARD\PAD.CPP (line 1049)
 * Stack frame base $sp, size 0
 */
unsigned int /*$ra*/ CardFormatted__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
{ // line 1, offset 0x10042c
} // line 2, offset 0x100460
/*
 * Offset 0x100460
 * D:\driver2\game\MEMCARD\PAD.CPP (line 1054)
 * Stack frame base $sp, size 32
 * Saved registers at offset -8: s0 s1 ra
 */
int /*$ra*/ FormatCard__3PADi(struct PAD *this /*$a0*/, int slot /*$a1*/)
{ // line 1, offset 0x100460
} // line 5, offset 0x1004c8
/*
 * Offset 0x1004C8
 * D:\driver2\game\MEMCARD\TEXT.CPP (line 16)
 * Stack frame base $sp, size 0
 */
int /*$ra*/ ParseLanguageFile__FPci(char *textBuffer /*$a0*/, int language /*$a1*/)
{ // line 1, offset 0x1004c8
  int m; // $t0
  char *textPtr; // $a0
} // line 156, offset 0x1005d8
/*
 * Offset 0x1005E0
 * D:\driver2\game\MEMCARD\CMAN.CPP (line 33)
 * Stack frame base $sp, size 51872
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ cardman__FiiPcP10FILEFORMATP5SLICET2T2(int operation /*stack 0*/, int options /*$a1*/, char *textBuffer /*$s4*/, struct FILEFORMAT *fileFormatPtr /*stack 12*/, struct SLICE *slicePtr /*stack 16*/, char *backImageName /*stack 20*/, char *bufferPtr96K /*stack 24*/)
{ // line 1, offset 0x1005e0
  struct TIMSTRUCT tempTimStruct; // stack offset -51840
  struct RECT rect; // stack offset -51824
  int n; // $s0
  char charBuffer[250]; // stack offset -51816
  char kanjiFree[6]; // stack offset -51560
  char kanjiSize[6]; // stack offset -51552
  char kanjiDel[6]; // stack offset -51544
  int card_process; // $s3
  int padWait; // stack offset -56
  int dirCount; // $s0
  int delCount; // stack offset -52
  int copyStatus; // $s0
  int pasteStatus; // $a3
  int destFree; // $s6
  int sourceSize; // $s5
  int newBlock; // $s2
  int nMessage; // $s2
  int language; // stack offset -48
  short padData; // $s1
  struct PAD pad; // stack offset -51536
  struct DISPMAN dispMan; // stack offset -18128
  { // line 36, offset 0x10067c
    { // line 44, offset 0x1006c4
    } // line 47, offset 0x100708
  } // line 47, offset 0x100708
  { // line 51, offset 0x100708
    { // line 52, offset 0x100720
      struct _CARD *header; // $a1
    } // line 74, offset 0x100970
  } // line 74, offset 0x100970
  { // line 124, offset 0x100a14
    { // line 142, offset 0x100a14
      { // line 148, offset 0x100a58
        { // line 149, offset 0x100a58
          { // line 150, offset 0x100a68
          } // line 167, offset 0x100b40
        } // line 167, offset 0x100b40
      } // line 170, offset 0x100b48
    } // line 170, offset 0x100b48
    { // line 174, offset 0x100b48
      { // line 183, offset 0x100b64
        { // line 184, offset 0x100b64
          { // line 185, offset 0x100b74
            { // line 186, offset 0x100b74
              { // line 190, offset 0x100b94
              } // line 273, offset 0x100d8c
              { // line 278, offset 0x100d9c
              } // line 293, offset 0x100e08
            } // line 293, offset 0x100e08
          } // line 293, offset 0x100e08
        } // line 293, offset 0x100e08
      } // line 293, offset 0x100e08
    } // line 293, offset 0x100e08
    { // line 301, offset 0x100e08
      { // line 302, offset 0x100e30
      } // line 317, offset 0x100e94
    } // line 317, offset 0x100e94
    { // line 321, offset 0x100e94
      { // line 322, offset 0x100ebc
        { // line 325, offset 0x100ebc
          { // line 326, offset 0x100ecc
            { // line 327, offset 0x100ecc
            } // line 327, offset 0x100ecc
          } // line 333, offset 0x100ef4
        } // line 333, offset 0x100ef4
        { // line 391, offset 0x10108c
        } // line 391, offset 0x10108c
        { // line 437, offset 0x1011a8
        } // line 437, offset 0x1011a8
        { // line 445, offset 0x1011b0
          { // line 446, offset 0x1011d8
            { // line 466, offset 0x10126c
            } // line 466, offset 0x10126c
            { // line 489, offset 0x101354
            } // line 489, offset 0x101354
            { // line 499, offset 0x101364
            } // line 499, offset 0x101364
          } // line 499, offset 0x101364
        } // line 499, offset 0x101364
        { // line 499, offset 0x101364
        } // line 499, offset 0x101364
        { // line 532, offset 0x101448
        } // line 532, offset 0x101448
        { // line 540, offset 0x101460
          { // line 541, offset 0x1014a4
            { // line 542, offset 0x1014a4
            } // line 542, offset 0x1014a4
          } // line 544, offset 0x1014b8
        } // line 544, offset 0x1014b8
        { // line 547, offset 0x1014b8
          { // line 551, offset 0x101500
            { // line 552, offset 0x101500
            } // line 552, offset 0x101500
          } // line 556, offset 0x101548
        } // line 556, offset 0x101548
        { // line 560, offset 0x101548
          { // line 563, offset 0x101580
            { // line 564, offset 0x101580
            } // line 564, offset 0x101580
          } // line 566, offset 0x101590
        } // line 566, offset 0x101590
        { // line 579, offset 0x101650
          { // line 580, offset 0x101658
            { // line 581, offset 0x101658
            } // line 581, offset 0x101658
          } // line 583, offset 0x101670
        } // line 583, offset 0x101670
        { // line 594, offset 0x101714
          { // line 595, offset 0x10171c
            { // line 596, offset 0x10171c
            } // line 596, offset 0x10171c
          } // line 598, offset 0x101734
        } // line 598, offset 0x101734
        { // line 601, offset 0x101734
        } // line 601, offset 0x101734
        { // line 611, offset 0x10177c
          { // line 615, offset 0x1017b0
            { // line 675, offset 0x1019c8
            } // line 675, offset 0x1019c8
          } // line 678, offset 0x1019f4
        } // line 678, offset 0x1019f4
        { // line 681, offset 0x1019f4
          { // line 682, offset 0x101a14
            { // line 707, offset 0x101afc
              { // line 711, offset 0x101b1c
                { // line 712, offset 0x101b1c
                } // line 712, offset 0x101b1c
              } // line 714, offset 0x101b30
            } // line 714, offset 0x101b30
          } // line 717, offset 0x101b30
        } // line 732, offset 0x101b4c
        { // line 732, offset 0x101b4c
        } // line 732, offset 0x101b4c
        { // line 738, offset 0x101b4c
          { // line 742, offset 0x101b8c
            { // line 743, offset 0x101b8c
              { // line 749, offset 0x101bc0
                { // line 753, offset 0x101c04
                } // line 753, offset 0x101c04
              } // line 754, offset 0x101c0c
              { // line 758, offset 0x101c0c
                { // line 764, offset 0x101c50
                  { // line 768, offset 0x101cb4
                    { // line 770, offset 0x101cec
                    } // line 770, offset 0x101cec
                  } // line 771, offset 0x101cf4
                } // line 771, offset 0x101cf4
              } // line 771, offset 0x101cf4
            } // line 771, offset 0x101cf4
          } // line 771, offset 0x101cf4
        } // line 771, offset 0x101cf4
        { // line 804, offset 0x101d38
          { // line 805, offset 0x101d40
            { // line 808, offset 0x101d40
            } // line 808, offset 0x101d40
          } // line 810, offset 0x101d58
        } // line 810, offset 0x101d58
        { // line 839, offset 0x101e94
          { // line 840, offset 0x101e9c
            { // line 841, offset 0x101e9c
            } // line 841, offset 0x101e9c
          } // line 843, offset 0x101eb4
        } // line 843, offset 0x101eb4
        { // line 867, offset 0x101f98
        } // line 867, offset 0x101f98
        { // line 874, offset 0x101fb0
        } // line 874, offset 0x101fb0
        { // line 898, offset 0x102104
          { // line 899, offset 0x10210c
            { // line 904, offset 0x10210c
            } // line 904, offset 0x10210c
          } // line 907, offset 0x102124
          { // line 910, offset 0x102124
            { // line 910, offset 0x102124
              { // line 911, offset 0x10212c
                { // line 913, offset 0x10212c
                } // line 913, offset 0x10212c
              } // line 916, offset 0x102150
            } // line 922, offset 0x102150
          } // line 922, offset 0x102150
        } // line 922, offset 0x102150
        { // line 922, offset 0x102150
        } // line 922, offset 0x102150
        { // line 937, offset 0x1021b0
          { // line 938, offset 0x1021b0
            { // line 940, offset 0x1021b0
              { // line 941, offset 0x1021d8
                { // line 943, offset 0x1021d8
                } // line 943, offset 0x1021d8
                { // line 948, offset 0x10220c
                } // line 948, offset 0x10220c
              } // line 948, offset 0x10220c
            } // line 948, offset 0x10220c
          } // line 964, offset 0x1022a8
        } // line 964, offset 0x1022a8
        { // line 967, offset 0x1022a8
        } // line 967, offset 0x1022a8
      } // line 967, offset 0x1022a8
    } // line 967, offset 0x1022a8
  } // line 980, offset 0x1022ec
  { // line 997, offset 0x102304
  } // line 997, offset 0x102304
} // line 997, offset 0x102364
/*
 * Offset 0x102364
 * D:\driver2\game\MEMCARD\CMAN.CPP (line 1065)
 * Stack frame base $sp, size 88
 * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
int /*$ra*/ EnterName__FP3PADP7DISPMANPc(struct PAD *pad /*$fp*/, struct DISPMAN *disp /*stack 4*/, char *username /*stack 8*/)
{ // line 1, offset 0x102364
  char asciiname[20]; // stack offset -72
  int ret; // stack offset -48
  short padData; // $s5
  short prevData; // $s7
  int so; // $s2
  int co; // $s6
  int delay; // $s3
  char c; // $s1
  char toggle; // stack offset -44
} // line 157, offset 0x102710
/*
 * Offset 0x102710
 * D:\driver2\game\MEMCARD\CMAN.CPP (line 24)
 * Stack frame base $sp, size 40
 * Saved registers at offset -8: ra
 */
int /*$ra*/ card_manager(int operation /*$a0*/, int options /*$a1*/, char *textBuffer /*$a2*/, struct FILEFORMAT *fileFormatPtr /*$a3*/, struct SLICE *slicePtr /*stack 16*/, char *backImageName /*stack 20*/, char *bufferPtr96K /*stack 24*/)
{ // line 1, offset 0x102710
} // line 6, offset 0x102744
/*
 * Offset 0x102744
 * D:\driver2\game\MEMCARD\CMAN.CPP (line 1034)
 * Stack frame base $sp, size 56
 * Saved registers at offset -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ LoadBackground__FPcT0(char *filename /*$s5*/, char *buffer /*$s2*/)
{ // line 1, offset 0x102744
  struct RECT rect; // stack offset -40
  int i; // $s0
  { // line 1, offset 0x102744
    { // line 5, offset 0x10277c
    } // line 8, offset 0x10277c
  } // line 12, offset 0x1027e8
} // line 12, offset 0x1027e8
