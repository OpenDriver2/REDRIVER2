#ifndef CIV_AI_H
#define CIV_AI_H

extern const u_char speedLimits[3];
extern unsigned char reservedSlots[MAX_CARS];
extern int frameStart;

extern int distFurthestCivCarSq;
extern char furthestCivID;

extern char makeLimoPullOver;

extern char junctionLightsPhase[2];

extern int InitCar(CAR_DATA *cp, int direction, LONGVECTOR4* startPos, unsigned char control, int model, int palette, char *extraData); // 0x00023DE8

extern CAR_DATA * FindClosestCar(int x, int y, int z, int *distToCarSq); // 0x0002D11C

extern int NotTravellingAlongCurve(int x, int z, int dir, DRIVER2_CURVE *cv); // 0x0002D24C

extern void CivCarFX(CAR_DATA *cp); // 0x0002D084

extern int GetNextRoadInfo(CAR_DATA *cp, int randomExit, int *turnAngle, int *startDist, CIV_ROUTE_ENTRY *oldNode); // 0x00024028

extern void InitNodeList(CAR_DATA *cp, EXTRA_CIV_DATA *extraData); // 0x00026964

extern int GetNodePos(DRIVER2_STRAIGHT *straight, DRIVER2_JUNCTION *junction, DRIVER2_CURVE *curve, int distAlongPath, CAR_DATA *cp, int *x, int *z, int laneNo); // 0x00026CAC

extern int CheckChangeLanes(DRIVER2_STRAIGHT *straight, DRIVER2_CURVE *curve, int distAlongSegment, CAR_DATA *cp, int tryToPark); // 0x00026F20

extern int CreateNewNode(CAR_DATA *cp); // 0x00027530

extern int InitCivState(CAR_DATA *cp, EXTRA_CIV_DATA *extraData); // 0x000280D8

extern int PingOutCar(CAR_DATA *cp); // 0x0002CF80

extern int PingOutAllSpecialCivCars(); // 0x000282E8

extern int PingOutAllCivCarsAndCopCars(); // 0x0002840C

extern int CheckPingOut(CAR_DATA *cp); // 0x00028554

extern void SetUpTrafficLightPhase(); // 0x0002D220

extern int TrafficLightCycle(int exit); // 0x0002CF18

extern void InitCivCars(); // 0x0002CDA4

extern int CreateCivCarWotDrivesABitThenStops(int direction, LONGVECTOR4* startPos, LONGVECTOR4* stopPos, unsigned char internalModel, int palette); // 0x000286E0

extern int CreateStationaryCivCar(int direction, long orientX, long orientZ, LONGVECTOR4* startPos, int externalModel, int palette, int controlFlags); // 0x00028960

extern int PingInCivCar(int minPingInDist); // 0x00028DB4

extern void AttemptUnPark(CAR_DATA *cp); // 0x0002A4C4

extern int CivControl(CAR_DATA *cp); // 0x0002CE10

extern int CivAccelTrafficRules(CAR_DATA *cp, int *distToNode); // 0x0002A5FC

extern void SetUpCivCollFlags(); // 0x0002ABA8

extern int CivAccel(CAR_DATA *cp); // 0x0002B26C

extern int CivSteerAngle(CAR_DATA *cp); // 0x0002B53C

extern int CivFindStation(CAR_DATA *cp); // 0x0002B8E4

extern int CivFindPointOnPath(CAR_DATA *cp, int station, VECTOR *ppoint); // 0x0002BAEC

extern void CreateRoadblock(); // 0x0002BCF4


#endif
