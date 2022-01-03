#ifndef PAD_H
#define PAD_H

#define PADBUFFER_SIZE 34

// mapped pad identifiers
#define MPAD_L2			0x1
#define MPAD_R2			0x2
#define MPAD_L1			0x4
#define MPAD_R1			0x8

#define MPAD_TRIANGLE	0x10
#define MPAD_CIRCLE		0x20
#define MPAD_CROSS		0x40
#define MPAD_SQUARE		0x80

#define MPAD_SELECT		0x100
#define MPAD_L3			0x200
#define MPAD_R3			0x400
#define MPAD_START		0x800

#define MPAD_D_UP		0x1000
#define MPAD_D_RIGHT	0x2000
#define MPAD_D_DOWN		0x4000
#define MPAD_D_LEFT		0x8000

enum ECameraPad
{
	CAMERA_PAD_LOOK_LEFT		= MPAD_L2,
	CAMERA_PAD_LOOK_RIGHT		= MPAD_R2,

	CAMERA_PAD_LOOK_BACK		= MPAD_L2 | MPAD_R2,
	CAMERA_PAD_LOOK_BACK_DED	= MPAD_L3
};

enum ETannerPad
{
	TANNER_PAD_ACTION		= MPAD_TRIANGLE,
	TANNER_PAD_POWER		= MPAD_CIRCLE,
	TANNER_PAD_GOFORWARD	= MPAD_CROSS | MPAD_D_UP,
	TANNER_PAD_GOBACK		= MPAD_SQUARE | MPAD_D_DOWN,
	TANNER_PAD_TURNLEFT		= MPAD_D_LEFT,
	TANNER_PAD_TURNRIGHT	= MPAD_D_RIGHT,

	TANNER_PAD_ACTION_DED	= MPAD_R3,		// R3 mapped for car entrance
};

enum ECarPads
{
	CAR_PAD_FASTSTEER		= MPAD_L1,
	CAR_PAD_HANDBRAKE		= MPAD_TRIANGLE,
	CAR_PAD_WHEELSPIN		= MPAD_CIRCLE,
	CAR_PAD_ACCEL			= MPAD_CROSS,
	CAR_PAD_BRAKE			= MPAD_SQUARE,
	CAR_PAD_UP				= MPAD_D_UP,
	CAR_PAD_LEFT			= MPAD_D_LEFT,
	CAR_PAD_RIGHT			= MPAD_D_RIGHT,

	CAR_PAD_LEAVECAR_DED	= MPAD_R3,		// R3 mapped

	CAR_PAD_LEAVECAR		= (MPAD_D_UP | MPAD_TRIANGLE),
};

extern int pad_connected;
extern int numPadsConnected;
extern int gVibration;

extern PAD Pads[2];

extern char padbuffer[2][PADBUFFER_SIZE];
extern DUPLICATION DuplicatePadData;

extern void InitControllers(); // 0x0006B480
extern void CloseControllers(); // 0x0006BDF8

extern void ReadControllers(); // 0x0006B5A8

extern void SetPadVibration(int pad, unsigned char type); // 0x0006BE38
extern void StopPadVibration(int pad); // 0x0006BEB4

extern void HandleDualShock(); // 0x0006B8E0
extern void StopDualShockMotors(); // 0x0006BEEC

extern void SetDuplicatePadData(char *buffer, int size); // 0x0006BEF4

#endif
