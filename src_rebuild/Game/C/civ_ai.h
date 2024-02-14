#ifndef CIV_AI_H
#define CIV_AI_H

typedef struct _EXTRA_CIV_DATA
{
	int surfInd;
	int distAlongSegment;
	short angle;
	u_short ctrlState;
	int thrustState;
	u_char palette;
	u_char controlFlags;
} EXTRA_CIV_DATA;

extern const u_char speedLimits[3];
extern unsigned char reservedSlots[MAX_CARS];
extern int frameStart;

extern int distFurthestCivCarSq;
extern char furthestCivID;

extern char makeLimoPullOver;

extern char junctionLightsPhase[2];

extern void InitCivCars(); // 0x0002CDA4

extern int InitCar(CAR_DATA *cp, int direction, LONGVECTOR4* startPos, unsigned char control, int model, int palette, char *extraData); // 0x00023DE8
extern int InitCivState(CAR_DATA* cp, EXTRA_CIV_DATA* extraData); // 0x000280D8

extern CAR_DATA* FindClosestCar(int x, int y, int z, int *distToCarSq); // 0x0002D11C

extern void CivCarFX(CAR_DATA *cp); // 0x0002D084

extern void SetUpCivCollFlags(); // 0x0002ABA8

extern int PingInCivCar(int minPingInDist); // 0x00028DB4
extern void CreateRoadblock(); // 0x0002BCF4

extern int PingOutCar(CAR_DATA *cp); // 0x0002CF80
extern int PingOutAllSpecialCivCars(); // 0x000282E8
extern int PingOutAllCivCarsAndCopCars(); // 0x0002840C
extern int CheckPingOut(CAR_DATA *cp); // 0x00028554

extern void SetUpTrafficLightPhase(); // 0x0002D220
extern int TrafficLightCycle(int exit); // 0x0002CF18

extern int CreateCivCarWotDrivesABitThenStops(int direction, LONGVECTOR4* startPos, LONGVECTOR4* stopPos, unsigned char internalModel, int palette); // 0x000286E0
extern int CreateStationaryCivCar(int direction, int orientX, int orientZ, LONGVECTOR4* startPos, int externalModel, int palette, int controlFlags); // 0x00028960

extern int CheckChangeLanes(DRIVER2_STRAIGHT* straight, DRIVER2_CURVE* curve, int distAlongSegment, CAR_DATA* cp, int tryToPark); // 0x00026F20
extern int NotTravellingAlongCurve(int x, int z, int dir, DRIVER2_CURVE* cv);

extern int CivControl(CAR_DATA* cp); // 0x0002CE10



#endif
