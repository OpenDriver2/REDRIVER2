#ifndef DRIVINGGAMES_H
#define DRIVINGGAMES_H


extern void InitDrivingGames(); // 0x0004310C

extern void HandleDrivingGames(); // 0x0004326C

extern void DrawDrivingGames(); // 0x000438DC

extern int CarConeCollision(struct VECTOR *pPos, int car); // 0x000439FC

extern void SetSmashedCone(int cone, struct VECTOR *velocity, int player, int side); // 0x00043AE8

extern void MoveSmashedCones(); // 0x00043CE0

extern void DrawSmashedCones(); // 0x00044168

extern void DrawCone(struct VECTOR *position, int cone); // 0x00044034

extern void DrawSmashedCone(struct SMASHED_CONE *sc, struct VECTOR *wpos); // 0x00043DEC

extern void GetConePos(int cone, struct VECTOR *pos, int side); // 0x00043F34


#endif
