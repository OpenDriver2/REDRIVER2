#ifndef PEDEST_H
#define PEDEST_H

#define TANNER_COLLIDER_CARID (MAX_CARS)

typedef struct SEATED_PEDESTRIANS* SEATEDPTR;

extern SVECTOR tannerLookAngle;

extern MODEL* pmTannerModels[17];
extern MODEL* pmJerichoModels[6];

extern SEATEDPTR seated_pedestrian;
extern int bKillTanner;
extern int bReverseYRotation;

extern LPPEDESTRIAN pUsedPeds;

// [A] for PC version adjustable density
extern int max_pedestrians;

extern void ProcessChairLump(char *lump_file, int lump_size); // 0x00073328

extern void InitTanner(); // 0x0006E408
extern void SetTannerPosition(VECTOR *pVec); // 0x00072478

extern void ProcessTannerPad(LPPEDESTRIAN pPed, u_int pad, char PadSteer, char use_analogue); // 0x0006DF54

extern void InitPedestrians(); // 0x0006E5C4
extern void DestroyPedestrians(); // 0x00071F54

extern void DestroyCivPedestrians(); // 0x00072FD0

extern void DestroyPedestrian(LPPEDESTRIAN pPed); // 0x00071FB4

extern int ActivatePlayerPedestrian(CAR_DATA *pCar, char *padId, int direction, LONGVECTOR4* position, PED_MODEL_TYPES playerType); // 0x0006E6C4
extern LPPEDESTRIAN  CreatePedestrian(); // 0x000720AC

extern void PlaceRoadBlockCops(); // 0x0006EC88
extern int CreatePedAtLocation(LONGVECTOR4* pPos, int pedType); // 0x0006F00C

extern void DrawAllPedestrians(); // 0x00072290
extern int TannerActionHappening(); // 0x00072430

extern void ControlPedestrians(); // 0x0006F16C

extern void DeActivatePlayerPedestrian(LPPEDESTRIAN pPed); // 0x0007216C

extern void SetupCivPedRouteData(VECTOR *pPos); // 0x0007313C

extern void PingInPedestrians(); // 0x0007047C

extern void TannerCollision(LPPEDESTRIAN pPed); // 0x00072EE4

extern int FindPointOfCollision(CAR_DATA *pCar, LPPEDESTRIAN pPed); // 0x00070878

extern int TannerCarCollisionCheck(VECTOR *pPos, int dir, int bQuick); // 0x00070A9C

extern int PingOutPed(LPPEDESTRIAN pPed); // 0x000731F8

extern void SetupCivJump(LPPEDESTRIAN pPed, CAR_DATA *cp); // 0x00071054

extern void SetupCivPedWalk(LPPEDESTRIAN pPed); // 0x00073270

extern void HandlePedestrians(); // 0x0007211C

extern void PedestrianActionInit_WalkToTarget(LPPEDESTRIAN pPed); // 0x0007283C

extern void CorrectPathPosition(LPPEDESTRIAN pedestrian, VECTOR *position); // 0x000715FC

extern int CalcPedestrianDirection(int last_dir, int wx, int wz, VECTOR *target); // 0x00071608

extern int IsPavement(int x, int y, int z, LPPEDESTRIAN pPed); // 0x000725B8

extern void SetPedestrianTurn(LPPEDESTRIAN pedestrian, int turn); // 0x00072500

extern void set_coll_box(int index, CAR_DATA *cp, int offset); // 0x00071A5C

extern void BuildCarCollisionBox(); // 0x00071B7C

extern CAR_DATA* CheckForCar(LPPEDESTRIAN pedestrian); // 0x00072738

extern void CalculatePedestrianInterest(LPPEDESTRIAN pPed); // 0x00071E0C

#endif
