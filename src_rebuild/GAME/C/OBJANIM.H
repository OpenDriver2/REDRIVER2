#ifndef OBJANIM_H
#define OBJANIM_H


extern void InitCyclingPals(); // 0x000149B4

extern void ColourCycle(); // 0x00013980

extern void FindSmashableObjects(); // 0x00014950

extern void InitAnimatingObjects(); // 0x00013CAC

extern void InitSpooledAnimObj(int model_number); // 0x00014828

extern void int_garage_door(); // 0x000149A8

extern int DrawAnimatingObject(MODEL *model, CELL_OBJECT *cop, VECTOR *pos); // 0x000148A0

extern void animate_object(CELL_OBJECT *cop, int type); // 0x00013DF8

extern void animate_garage_door(); // 0x000146A4


#endif
