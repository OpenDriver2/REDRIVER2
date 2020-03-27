#ifndef AI_H
#define AI_H


extern void StoreGameFlags(); // 0x0001BBB8

extern int TannerCanEnterCar(struct _CAR_DATA *cp, int distToCarSq); // 0x0001BBE8

extern int TannerStuckInCar(int doSpeedCheck); // 0x0001BA90


#endif
