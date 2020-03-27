#ifndef CARS_H
#define CARS_H


extern void plotNewCarModel(struct CAR_MODEL *car, int palette); // 0x00020C94

extern void plotCarPolyB3(int numTris, struct CAR_POLY *src, struct SVECTOR *vlist, struct plotCarGlobals *pg); // 0x000237B8

extern void plotCarPolyFT3(int numTris, struct CAR_POLY *src, struct SVECTOR *vlist, struct plotCarGlobals *pg); // 0x000238C4

extern void plotCarPolyGT3(int numTris, struct CAR_POLY *src, struct SVECTOR *vlist, struct SVECTOR *nlist, struct plotCarGlobals *pg, int palette); // 0x00020EA0

extern void plotCarPolyGT3nolight(int numTris, struct CAR_POLY *src, struct SVECTOR *vlist, struct plotCarGlobals *pg, int palette); // 0x00023A20

extern void DrawCar(struct _CAR_DATA *cp, int view); // 0x000210B8

extern void DrawCarObject(struct CAR_MODEL *car, struct MATRIX *matrix, struct VECTOR *pos, struct VECTOR *pos1, int palette, struct _CAR_DATA *cp, int detail); // 0x000233DC

extern void DrawCarWheels(struct _CAR_DATA *cp, struct MATRIX *RearMatrix, struct VECTOR *pos, int zclip); // 0x00021AF8

extern void DrawWheelObject(struct MODEL *model, struct SVECTOR *verts, int transparent, int wheelnum); // 0x00022180

extern void PlayerCarFX(struct _CAR_DATA *cp); // 0x000234DC

extern void ComputeCarLightingLevels(struct _CAR_DATA *cp, char detail); // 0x00022458

extern void buildNewCars(); // 0x00022860

extern void buildNewCarFromModel(struct CAR_MODEL *car, struct MODEL *model, int first); // 0x00022960

extern void MangleWheelModels(); // 0x000230C8

extern void setupLightingMatrices(); // 0x000235F8

extern void restoreLightingMatrices(); // 0x00023750

extern char GetCarPalIndex(int tpage); // 0x00023390


#endif
