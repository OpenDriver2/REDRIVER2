#ifndef PEDEST_H
#define PEDEST_H

extern int bKillTanner;

extern void IHaveThePower(); // 0x0006DD34

extern void ProcessTannerPad(PEDESTRIAN *pPed, unsigned long pad, char PadSteer, char use_analogue); // 0x0006DF54

extern void InitTanner(); // 0x0006E408

extern void SetTannerPosition(VECTOR *pVec); // 0x00072478

extern void InitPedestrians(); // 0x0006E5C4

extern void DestroyPedestrians(); // 0x00071F54

extern void DestroyCivPedestrians(); // 0x00072FD0

extern void DestroyPedestrian(PEDESTRIAN *pPed); // 0x00071FB4

extern int ActivatePlayerPedestrian(_CAR_DATA *pCar, char *padId, int direction, long (*position)[4], int playerType); // 0x0006E6C4

extern struct PEDESTRIAN * CreatePedestrian(); // 0x000720AC

extern void PlaceRoadBlockCops(); // 0x0006EC88

extern int CreatePedAtLocation(long (*pPos)[4], int pedType); // 0x0006F00C

extern void DrawAllPedestrians(); // 0x00072290

extern int TannerActionHappening(); // 0x00072430

extern void ControlPedestrians(); // 0x0006F16C

extern void SetupDoNowt(PEDESTRIAN *pPed); // 0x00073038

extern void SetupWalker(PEDESTRIAN *pPed); // 0x0007307C

extern void SetupRunner(PEDESTRIAN *pPed); // 0x000730B8

extern void SetupBack(PEDESTRIAN *pPed); // 0x000730FC

extern void CivGetIn(PEDESTRIAN *pPed); // 0x00072DFC

extern void CopStand(PEDESTRIAN *pPed); // 0x00072DA0

extern void PedDoNothing(PEDESTRIAN *pPed); // 0x0006F2DC

extern void PedUserRunner(PEDESTRIAN *pPed); // 0x0006F5AC

extern void PedUserWalker(PEDESTRIAN *pPed); // 0x00072944

extern void PedCarryOutAnimation(PEDESTRIAN *pPed); // 0x00072A10

extern void PedGetOutCar(PEDESTRIAN *pPed); // 0x00072BEC

extern void SetupGetOutCar(PEDESTRIAN *pPed, struct _CAR_DATA *pCar, int side); // 0x0006F80C

extern void SetupGetInCar(PEDESTRIAN *pPed); // 0x0006FA3C

extern void PedGetInCar(PEDESTRIAN *pPed); // 0x00072B5C

extern void SetupPressButton(PEDESTRIAN *pPed); // 0x00072904

extern void PedPressButton(PEDESTRIAN *pPed); // 0x00072C90

extern void SetupTannerSitDown(PEDESTRIAN *pPed); // 0x000728C8

extern void TannerCameraHandler(PEDESTRIAN *pPed); // 0x0006FD08

extern void TannerSitDown(PEDESTRIAN *pPed); // 0x0006FF48

extern void AnimatePed(PEDESTRIAN *pPed); // 0x000700D0

extern void DeActivatePlayerPedestrian(PEDESTRIAN *pPed); // 0x0007216C

extern void CivPedDoNothing(PEDESTRIAN *pPed); // 0x00072CE0

extern void SetupCivPedRouteData(VECTOR *pPos); // 0x0007313C

extern void PingInPedestrians(); // 0x0007047C

extern void TannerCollision(PEDESTRIAN *pPed); // 0x00072EE4

extern int FindPointOfCollision(_CAR_DATA *pCar, VECTOR *pPos); // 0x00070878

extern int TannerCarCollisionCheck(VECTOR *pPos, int dir, int bQuick); // 0x00070A9C

extern int PingOutPed(PEDESTRIAN *pPed); // 0x000731F8

extern void SetupCivJump(PEDESTRIAN *pPed, struct _CAR_DATA *cp); // 0x00071054

extern void CivPedJump(PEDESTRIAN *pPed); // 0x00072CF0

extern void SetupCivPedWalk(PEDESTRIAN *pPed); // 0x00073270

extern void CivPedWalk(PEDESTRIAN *pPed); // 0x00071324

extern void CivPedSit(PEDESTRIAN *pPed); // 0x00072CE8

extern void HandlePedestrians(); // 0x0007211C

extern void PedestrianActionInit_WalkToTarget(PEDESTRIAN *pPed); // 0x0007283C

extern void CorrectPathPosition(PEDESTRIAN *pedestrian, VECTOR *position); // 0x000715FC

extern int CalcPedestrianDirection(int last_dir, int wx, int wz, VECTOR *target); // 0x00071608

extern int IsPavement(int x, int y, int z, struct PEDESTRIAN *pPed); // 0x000725B8

extern void SetPedestrianTurn(PEDESTRIAN *pedestrian, int turn); // 0x00072500

extern struct SEATED_PEDESTRIANS * FindSeated(); // 0x00072644

extern struct SEATED_PEDESTRIANS * FindTannerASeat(PEDESTRIAN *pPed); // 0x000717AC

extern void add_seated(SEATED_PEDESTRIANS *seatedptr, int seat_index); // 0x000718C8

extern void set_coll_box(int index, _CAR_DATA *cp, int offset); // 0x00071A5C

extern void BuildCarCollisionBox(); // 0x00071B7C

extern struct _CAR_DATA * CheckForCar(PEDESTRIAN *pedestrian); // 0x00072738

extern int CheckForPlayerCar(PEDESTRIAN *pedestrian, CAR_COLLISION_BOX *collision_box); // 0x000732C0

extern void CalculatePedestrianInterest(PEDESTRIAN *pPed); // 0x00071E0C

extern int PedSurfaceType(VECTOR *ped_pos); // 0x00072584

extern void ProcessChairLump(char *lump_file, int lump_size); // 0x00073328


#endif
