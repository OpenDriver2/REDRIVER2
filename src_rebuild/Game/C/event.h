#ifndef EVENT_H
#define EVENT_H

extern EventGlobal events;

extern CELL_OBJECT *EventCop;
extern int event_models_active;

extern int carsOnBoat;

extern void InitEvents(); // 0x0004BBD4
extern void SetUpEvents(int full); // 0x00046258
extern VECTOR* TriggerEvent(int i);

extern void InitEventCamera(); // 0x0004BF54
extern void ResetEventCamera(); // 0x0004C014

extern void SetCamera(EVENT *ev); // 0x00047538

extern void EventCollisions(CAR_DATA *cp, int type); // 0x0004BC50

extern void StepEvents(); // 0x00048A60

extern void DrawEvents(int camera); // 0x00049C38

extern void EventCameraOffset(SVECTOR* offset);

extern sdPlane* EventSurface(VECTOR *pos, sdPlane *plane); // 0x0004A688

extern void MakeEventTrackable(EVENT *ev); // 0x0004BD6C

extern void OffsetTarget(VECTOR *target); // 0x0004BD2C

extern void SetSpecialCamera(SpecialCamera type, int change); // 0x0004B29C

extern void ScreenShake(int count, SVECTOR *ang); // 0x0004C280

extern int DetonatorTimer(); // 0x0004B5FC

extern void MultiCarEvent(MS_TARGET *target); // 0x0004BAB0


#endif
