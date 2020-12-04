#ifndef CARS_H
#define CARS_H

#ifndef PSX
#define MAX_DENTING_VERTS		256
#define MAX_DENTING_UVS			256
#define MAX_DENTING_LOD_UVS		256
#else
#define MAX_DENTING_VERTS		132
#define MAX_DENTING_UVS			255
#define MAX_DENTING_LOD_UVS		134
#endif


#define CAR_INDEX(cp)  (int)(cp-car_data)

#define IS_ROADBLOCK_CAR(cp) (cp->controlType == CONTROL_TYPE_CIV_AI && (cp->controlFlags & CONTROL_FLAG_COP_SLEEPING))

// PHYSICS
extern CAR_DATA car_data[MAX_CARS + 2];	// all cars + Tanner cbox + Camera cbox

// active cars
extern CAR_DATA* active_car_list[MAX_CARS];
extern BOUND_BOX bbox[MAX_CARS];
extern unsigned char lightsOnDelay[MAX_CARS];

extern CAR_MODEL NewCarModel[MAX_CAR_MODELS];
extern CAR_MODEL NewLowCarModel[MAX_CAR_MODELS];

extern MODEL* gCarLowModelPtr[MAX_CAR_MODELS];
extern MODEL* gCarDamModelPtr[MAX_CAR_MODELS];
extern MODEL* gCarCleanModelPtr[MAX_CAR_MODELS];

extern int whichCP;		// car poly counter
extern int baseSpecCP;	// special car poly counter

extern SVECTOR gTempCarVertDump[MAX_CARS][MAX_DENTING_VERTS];
extern DENTUVS gTempHDCarUVDump[MAX_CARS][MAX_DENTING_UVS];
extern DENTUVS gTempLDCarUVDump[MAX_CARS][MAX_DENTING_LOD_UVS];

extern MODEL *gHubcapModelPtr;
extern MODEL *gCleanWheelModelPtr;
extern MODEL *gFastWheelModelPtr;
extern MODEL *gDamWheelModelPtr;

extern short FrontWheelRotation[MAX_CARS];
extern short BackWheelRotation[MAX_CARS];

extern char LeftLight;
extern char RightLight;

extern u_short civ_clut[8][32][6];

extern void plotNewCarModel(CAR_MODEL *car, int palette); // 0x00020C94

extern void plotCarPolyB3(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg); // 0x000237B8

extern void plotCarPolyFT3(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg); // 0x000238C4

extern void plotCarPolyGT3(int numTris, CAR_POLY *src, SVECTOR *vlist, SVECTOR *nlist, plotCarGlobals *pg, int palette); // 0x00020EA0

extern void plotCarPolyGT3nolight(int numTris, CAR_POLY *src, SVECTOR *vlist, plotCarGlobals *pg, int palette); // 0x00023A20

extern void DrawCar(CAR_DATA *cp, int view); // 0x000210B8

extern void DrawCarObject(CAR_MODEL *car, MATRIX *matrix, VECTOR *pos, int palette, CAR_DATA *cp, int detail); // 0x000233DC

extern void DrawCarWheels(CAR_DATA *cp, MATRIX *RearMatrix, VECTOR *pos, int zclip); // 0x00021AF8

extern void DrawWheelObject(MODEL *model, SVECTOR *verts, int transparent, int wheelnum); // 0x00022180

extern void PlayerCarFX(CAR_DATA *cp); // 0x000234DC

extern void ComputeCarLightingLevels(CAR_DATA *cp, char detail); // 0x00022458

extern void buildNewCars(); // 0x00022860

extern void buildNewCarFromModel(CAR_MODEL *car, MODEL *model, int first); // 0x00022960

extern void MangleWheelModels(); // 0x000230C8

extern void setupLightingMatrices(); // 0x000235F8

extern void restoreLightingMatrices(); // 0x00023750

extern char GetCarPalIndex(int tpage); // 0x00023390


#endif
