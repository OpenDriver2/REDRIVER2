#ifndef JOB_FX_H
#define JOB_FX_H


extern void InitExObjects(); // 0x00057B0C

extern void AddExplosion(VECTOR pos, int type); // 0x00056D54

extern void HandleExplosion(); // 0x00056E44

extern void DrawAllExplosions(); // 0x00057B50

extern void initExplosion(); // 0x00056FC0

extern void DrawExplosion(int time, VECTOR position, int hscale, int rscale); // 0x000572A8


#endif
