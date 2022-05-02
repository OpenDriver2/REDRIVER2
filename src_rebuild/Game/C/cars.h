#ifndef CARS_H
#define CARS_H


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

extern void DrawCar(CAR_DATA *cp, int view); // 0x000210B8

extern void buildNewCars(); // 0x00022860
extern void buildNewCarFromModel(CAR_MODEL *car, MODEL *model, int first); // 0x00022960

extern void MangleWheelModels(); // 0x000230C8

extern char GetCarPalIndex(int tpage); // 0x00023390

extern int gCarLODDistance;


#endif
