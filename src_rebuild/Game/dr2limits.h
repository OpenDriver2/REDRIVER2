#ifndef DRLIMITS_H
#define DRLIMITS_H

// DRIVER 2 game engine limits
// please populate this file only with engine limits during refactoring

#define MAX_PLAYERS				8			// used for replay streams mostly

#define MAX_MODEL_SLOTS			1536		// DO NOT CHANGE. No effect in upping it - limited by cell types
#define MAX_CARS				20

#define MAX_CAR_MODELS			5
#define MAX_PEDESTRIANS			28
#define MAX_SEATED_PEDS			20
#define MAX_PLACED_PEDS			15
#define MAX_EXPLOSION_OBJECTS	5
#define MAX_THROWN_BOMBS		5
#define MAX_MOTION_CAPTURE		24

// denting
#define MAX_DAMAGE_ZONE_VERTS	50
#define MAX_DAMAGE_ZONE_POLYS	70
#define MAX_DAMAGE_LEVELS		256

#ifndef PSX
#define MAX_DENTING_VERTS		256
#define MAX_DENTING_UVS			256
#define MAX_DENTING_LOD_UVS		256
#else
#define MAX_DENTING_VERTS		132
#define MAX_DENTING_UVS			255
#define MAX_DENTING_LOD_UVS		134
#endif

// Mission limits
// DO NOT EDIT, breaks compatibility!
#define MAX_MISSION_THREADS		16
#define MAX_MISSION_TARGETS		16

// replay definitions.
// DO NOT EDIT, breaks compatibility!
#define MAX_REPLAY_STREAMS		MAX_PLAYERS
#define MAX_REPLAY_CAMERAS		60
#define MAX_REPLAY_WAYPOINTS	150
#define MAX_REPLAY_PINGS		400

// debris limits
#define MAX_SMOKE				80
#define MAX_LEAVES				50
#define MAX_DEBRIS				60
#define MAX_GROUND_DEBRIS		16
#define MAX_DAMAGED_LAMPS		5
#define MAX_SMASHED_OBJECTS		8
#define MAX_LAMP_STREAKS		21
#define MAX_RAIN_DROPS			180

// driving games limit
#define MAX_SMASHED_CONES		6

// sound limits
#define MAX_SFX_CHANNELS		16		// DON'T CHANGE unless you have more than 24 channels (no PSX code)
#define MAX_LEVEL_ENVSOUNDS		32
#define MAX_SIREN_NOISES		2
#define MAX_CAR_NOISES			4


#endif // DRLIMITS_H