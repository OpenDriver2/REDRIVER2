#ifndef CIV_AI_H
#define CIV_AI_H

extern unsigned char reservedSlots[20];
extern unsigned long PingBufferPos;
extern _PING_PACKET *PingBuffer;
extern int frameStart;

extern int distFurthestCivCarSq;
extern char furthestCivID;

extern char makeLimoPullOver;

extern int InitCar(_CAR_DATA *cp, int direction, long (*startPos)[4], unsigned char control, int model, int palette, char *extraData); // 0x00023DE8

extern _CAR_DATA * FindClosestCar(int x, int y, int z, int *distToCarSq); // 0x0002D11C

extern int NotTravellingAlongCurve(int x, int z, int dir, DRIVER2_CURVE *cv); // 0x0002D24C

extern void CivCarFX(_CAR_DATA *cp); // 0x0002D084

extern int GetNextRoadInfo(_CAR_DATA *cp, int randomExit, int *turnAngle, int *startDist, CIV_ROUTE_ENTRY *oldNode); // 0x00024028

extern void InitNodeList(_CAR_DATA *cp, char *extraData); // 0x00026964

extern int GetNodePos(DRIVER2_STRAIGHT *straight, DRIVER2_JUNCTION *junction, DRIVER2_CURVE *curve, int distAlongPath, _CAR_DATA *cp, int *x, int *z, int laneNo); // 0x00026CAC

extern int CheckChangeLanes(DRIVER2_STRAIGHT *straight, DRIVER2_CURVE *curve, int distAlongSegment, _CAR_DATA *cp, int tryToPark); // 0x00026F20

extern int CreateNewNode(_CAR_DATA *cp); // 0x00027530

extern int InitCivState(_CAR_DATA *cp, char *extraData); // 0x000280D8

extern int PingOutCar(_CAR_DATA *cp); // 0x0002CF80

extern int PingOutAllSpecialCivCars(); // 0x000282E8

extern int PingOutAllCivCarsAndCopCars(); // 0x0002840C

extern int CheckPingOut(_CAR_DATA *cp); // 0x00028554

extern void SetUpTrafficLightPhase(); // 0x0002D220

extern int TrafficLightCycle(int exit); // 0x0002CF18

extern void InitCivCars(); // 0x0002CDA4

extern int CreateCivCarWotDrivesABitThenStops(int direction, long (*startPos)[4], long (*stopPos)[4], unsigned char internalModel, int palette); // 0x000286E0

extern int CreateStationaryCivCar(int direction, long orientX, long orientZ, long (*startPos)[4], int externalModel, int palette, int controlFlags); // 0x00028960

extern int PingInCivCar(int minPingInDist); // 0x00028DB4

extern void AttemptUnPark(_CAR_DATA *cp); // 0x0002A4C4

extern int CivControl(_CAR_DATA *cp); // 0x0002CE10

extern int CivAccelTrafficRules(_CAR_DATA *cp, int *distToNode); // 0x0002A5FC

extern void SetUpCivCollFlags(); // 0x0002ABA8

extern int CivAccel(_CAR_DATA *cp); // 0x0002B26C

extern int CivSteerAngle(_CAR_DATA *cp); // 0x0002B53C

extern int CivFindStation(_CAR_DATA *cp); // 0x0002B8E4

extern int CivFindPointOnPath(_CAR_DATA *cp, int station, VECTOR *ppoint); // 0x0002BAEC

extern void CreateRoadblock(); // 0x0002BCF4


#endif
