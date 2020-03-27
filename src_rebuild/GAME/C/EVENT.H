#ifndef EVENT_H
#define EVENT_H


extern int GetVisValue(int index, int zDir); // 0x00045AB8

extern void VisibilityLists(enum VisType type, int i); // 0x00045C68

extern void SetElTrainRotation(struct _EVENT *ev); // 0x0004BE5C

extern void InitTrain(struct _EVENT *ev, int count, int type); // 0x000460EC

extern void InitDoor(struct FixedEvent *ev, struct _EVENT ***e, int *cEvents); // 0x0004BEB8

extern void InitEvents(); // 0x0004BBD4

extern void SetUpEvents(int full); // 0x00046258

extern void InitEventCamera(); // 0x0004BF54

extern void ResetEventCamera(); // 0x0004C014

extern void SetCamera(struct _EVENT *ev); // 0x00047538

extern void EventCollisions(struct _CAR_DATA *cp, int type); // 0x0004BC50

extern void NextNode(struct _EVENT *ev); // 0x0004C0A4

extern void StepFromToEvent(struct _EVENT *ev); // 0x000479DC

extern void StepPathEvent(struct _EVENT *ev); // 0x00047BD4

extern int GetBridgeRotation(int timer); // 0x0004C158

extern void StepHelicopter(struct _EVENT *ev); // 0x0004830C

extern void StepEvents(); // 0x00048A60

extern void DrawFerrisWheel(struct MATRIX *matrix, struct VECTOR *pos); // 0x00049364

extern void DrawRotor(struct VECTOR pos, struct MATRIX *matrix); // 0x00049684

extern void DrawEvents(int camera); // 0x00049C38

extern void BoatOffset(struct SVECTOR *offset, struct _EVENT *ev); // 0x0004BE24

extern int OnBoat(struct VECTOR *pos, struct _EVENT *ev, int *dist); // 0x0004BDA0

extern struct _sdPlane * EventSurface(struct VECTOR *pos, struct _sdPlane *plane); // 0x0004A688

extern void MakeEventTrackable(struct _EVENT *ev); // 0x0004BD6C

extern void TriggerDoor(struct FixedEvent *door, int *stage, int sound); // 0x0004C208

extern struct VECTOR * TriggerEvent(int i); // 0x0004AA78

extern void OffsetTarget(struct VECTOR *target); // 0x0004BD2C

extern void SpecialCamera(enum SpecialCamera type, int change); // 0x0004B29C

extern void ScreenShake(int count, struct SVECTOR *ang); // 0x0004C280

extern int DetonatorTimer(); // 0x0004B5FC

extern void MultiCarEvent(struct _TARGET *target); // 0x0004BAB0


#endif
