#ifndef DRLIMITS_H
#define DRLIMITS_H

// DRIVER 2 game engine limits
// please populate this file only with engine limits during refactoring

#define MAX_CARS				20

#define MAX_CAR_MODELS			5
#define MAX_PEDESTRIANS			28
#define MAX_SEATED_PEDS			20
#define MAX_PLACED_PEDS			15
#define MAX_TRAFFIC_CARS		19
#define MAX_EXPLOSION_OBJECTS	5
#define MAX_THROWN_BOMBS		5

// replay definitions.
// DO NOT EDIT, breaks compatibility!
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

#endif // DRLIMITS_H