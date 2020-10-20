#ifndef DRLIMITS_H
#define DRLIMITS_H

// DRIVER 2 game engine limits
// please populate this file only with engine limits during refactoring

#define MAX_CAR_MODELS			5
#define MAX_PEDESTRIANS			28
#define MAX_PLACED_PEDS			15
#define MAX_EXPLOSION_OBJECTS	5
#define MAX_THROWN_BOMBS		5

#ifdef PSX
#define MAX_CARS				20
#define MAX_TRAFFIC_CARS		14
#define MAX_TRAFFIC_CARS_SECRET	10
#define MAX_PARKED_CARS			7
#define MAX_PARKED_CARS_SECRET	5
#else
#define MAX_CARS				26
#define MAX_TRAFFIC_CARS		MAX_CARS-6 // - MAX_COPS - 2?
#define MAX_TRAFFIC_CARS_SECRET	MAX_TRAFFIC_CARS-4
#define MAX_PARKED_CARS			MAX_CARS/2
#define MAX_PARKED_CARS_SECRET	MAX_PARKED_CARS-2
#endif

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