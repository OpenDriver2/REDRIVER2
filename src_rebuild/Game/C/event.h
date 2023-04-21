#ifndef EVENT_H
#define EVENT_H

enum SpecialCamera
{
	SPECIAL_CAMERA_SET = 0,
	SPECIAL_CAMERA_SET2 = 1,
	SPECIAL_CAMERA_RESET = 2,
	SPECIAL_CAMERA_WAIT = 3,
};

typedef struct _EVENT EVENT;

struct _EVENT
{
	VECTOR position;
	short rotation;
	short timer;
	int* data;
	int* node;
	short flags;
	short radius;
	int model;
	EVENT* next;
};

struct EventGlobal
{
	int camera;
	int draw;
	EVENT** track;
	EVENT* cameraEvent;
};

#define HARDCODED_CAMERA_EVENT (EVENT*)0x1

extern EventGlobal events;

extern CELL_OBJECT *EventCop;
extern int event_models_active;

#ifndef PSX
struct BOAT_CARS
{
	int count;
	char cars[MAX_CARS+2];
};

extern BOAT_CARS carsOnBoat;
#else
extern int carsOnBoat;
#endif

extern void InitEvents(); // 0x0004BBD4
extern void SetUpEvents(int full); // 0x00046258
extern VECTOR* TriggerEvent(int i);

extern void EventCollisions(CAR_DATA *cp, int type); // 0x0004BC50

extern void StepEvents(); // 0x00048A60

extern void DrawEvents(int camera); // 0x00049C38

extern void EventCameraOffset(SVECTOR* offset);

extern sdPlane* EventSurface(VECTOR *pos, sdPlane *plane); // 0x0004A688

extern void OffsetTarget(VECTOR *target); // 0x0004BD2C

extern void SetSpecialCamera(SpecialCamera type, int change); // 0x0004B29C

extern int DetonatorTimer(); // 0x0004B5FC

extern void MultiCarEvent(MS_TARGET *target); // 0x0004BAB0

extern int InitUserMissionEvents(MR_THREAD *thread);


#endif
