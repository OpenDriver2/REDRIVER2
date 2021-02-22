#include "LIBPAD.H"
#include "LIBETC.H"

#include "../PSYX_SETUP.H"
#include "PSYX_PUBLIC.H"

SDL_GameController* padHandle[MAX_CONTROLLERS];
unsigned char* padData[MAX_CONTROLLERS];

const unsigned char* keyboardState = NULL;
int g_padCommStarted = 0;

void PadInitDirect(unsigned char* pad1, unsigned char* pad2)
{
	// do not init second time!
	if (keyboardState != NULL)
		return;

	// init keyboard state
	keyboardState = SDL_GetKeyboardState(NULL);
	
	if (pad1 != NULL)
	{
		padData[0] = pad1;

		PADRAW* pad = (PADRAW*)pad1;
		pad->id = 0x41;	// always init first controller
		pad->analog[0] = 128;
		pad->analog[1] = 128;
		pad->analog[2] = 128;
		pad->analog[3] = 128;
	}
	else
		padData[0] = NULL;

	if (pad2 != NULL)
	{
		padData[1] = pad2;

		PADRAW* pad = (PADRAW*)pad2;
		pad->status = 0xFF;
		pad->id = 0;
		pad->analog[0] = 128;
		pad->analog[1] = 128;
		pad->analog[2] = 128;
		pad->analog[3] = 128;
	}
	else
		padData[0] = NULL;

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		eprinterr("Failed to initialise SDL GameController subsystem!\n");
		return;
	}

	// Add more controllers from custom file
	SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");

	// immediately open controllers
	int numJoysticks = SDL_NumJoysticks();
	
	for (int i = 0; i < numJoysticks && i < MAX_CONTROLLERS; i++)
	{
		if (SDL_IsGameController(i))
		{
			padHandle[i] = SDL_GameControllerOpen(i);	//@TODO close joysticks
		}
	}
}

void PadInitMtap(unsigned char* unk00, unsigned char* unk01)
{
	PSYX_UNIMPLEMENTED();
}

void PadInitGun(unsigned char* unk00, int unk01)
{
	PSYX_UNIMPLEMENTED();
}

int PadChkVsync()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void PadStartCom()
{
	g_padCommStarted = 1;
}

void PadStopCom()
{
	g_padCommStarted = 0;
}

unsigned int PadEnableCom(unsigned int unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void PadEnableGun(unsigned char unk00)
{
	PSYX_UNIMPLEMENTED();
}

void PadRemoveGun()
{
	PSYX_UNIMPLEMENTED();
}

int PadGetState(int port)
{
#if _DEBUG || 1
	return PadStateStable;//FIXME should check if keyboard is connected
#endif
	if (!(SDL_GameControllerGetAttached(padHandle[port])))
	{
		return PadStateDiscon;
	}
	else
	{
		return PadStateStable;
	}

	return 0;
}

int PadInfoMode(int unk00, int unk01, int unk02)
{
	return 7;//?
}

int PadInfoAct(int unk00, int unk01, int unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int PadInfoComb(int unk00, int unk01, int unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int PadSetActAlign(int unk00, unsigned char* unk01)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int PadSetMainMode(int socket, int offs, int lock)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void PadSetAct(int unk00, unsigned char* unk01, int unk02)
{
	PSYX_UNIMPLEMENTED();
}

int GetControllerButtonState(SDL_GameController* cont, int buttonOrAxis)
{
	if(buttonOrAxis & CONTROLLER_MAP_FLAG_AXIS)
	{
		int value = SDL_GameControllerGetAxis(cont, (SDL_GameControllerAxis)(buttonOrAxis & ~(CONTROLLER_MAP_FLAG_AXIS | CONTROLLER_MAP_FLAG_INVERSE)));
		
		if (abs(value) > 500 && (buttonOrAxis & CONTROLLER_MAP_FLAG_INVERSE))
			value *= -1;

		return value;
	}

	return SDL_GameControllerGetButton(cont, (SDL_GameControllerButton)buttonOrAxis) * 32767;
}

void UpdateGameControllerInput(SDL_GameController* cont, PADRAW* pad)
{
	unsigned short ret = 0xFFFF;

	extern PsyXControllerMapping g_controller_mapping;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_square) > 16384)//Square
		ret &= ~0x8000;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_circle) > 16384)//Circle
		ret &= ~0x2000;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_triangle) > 16384)//Triangle
		ret &= ~0x1000;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_cross) > 16384)//Cross
		ret &= ~0x4000;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_l1) > 16384)//L1
		ret &= ~0x400;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_r1) > 16384)//R1
		ret &= ~0x800;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_l2) > 16384)//L2
		ret &= ~0x100;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_r2) > 16384)//R2
		ret &= ~0x200;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_dpad_up) > 16384)//UP
		ret &= ~0x10;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_dpad_down) > 16384)//DOWN
		ret &= ~0x40;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_dpad_left) > 16384)//LEFT
		ret &= ~0x80;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_dpad_right) > 16384)//RIGHT
		ret &= ~0x20;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_l3) > 16384)//L3
		ret &= ~0x2;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_r3) > 16384)//R3
		ret &= ~0x4;
	
	if (GetControllerButtonState(cont, g_controller_mapping.gc_select) > 16384)//SELECT
		ret &= ~0x1;

	if (GetControllerButtonState(cont, g_controller_mapping.gc_start) > 16384)//START
		ret &= ~0x8;

	short leftX = GetControllerButtonState(cont, g_controller_mapping.gc_axis_left_x);
	short leftY = GetControllerButtonState(cont, g_controller_mapping.gc_axis_left_y);

	short rightX = GetControllerButtonState(cont, g_controller_mapping.gc_axis_right_x);
	short rightY = GetControllerButtonState(cont, g_controller_mapping.gc_axis_right_y);
	
	*(unsigned short*)pad->buttons = ret;

	// map to range
	pad->analog[0] = (rightX / 256) + 128;
	pad->analog[1] = (rightY / 256) + 128;
	pad->analog[2] = (leftX / 256) + 128;
	pad->analog[3] = (leftY / 256) + 128;
}

unsigned short UpdateKeyboardInput()
{
	extern PsyXKeyboardMapping g_keyboard_mapping;
	unsigned short ret = 0xFFFF;

	//Not initialised yet
	if (keyboardState == NULL)
		return ret;

	SDL_PumpEvents();

	if (keyboardState[g_keyboard_mapping.kc_square])//Square
		ret &= ~0x8000;

	if (keyboardState[g_keyboard_mapping.kc_circle])//Circle
		ret &= ~0x2000;

	if (keyboardState[g_keyboard_mapping.kc_triangle])//Triangle
		ret &= ~0x1000;

	if (keyboardState[g_keyboard_mapping.kc_cross])//Cross
		ret &= ~0x4000;

	if (keyboardState[g_keyboard_mapping.kc_l1])//L1
		ret &= ~0x400;

	if (keyboardState[g_keyboard_mapping.kc_l2])//L2
		ret &= ~0x100;

	if (keyboardState[g_keyboard_mapping.kc_l3])//L3
		ret &= ~0x2;

	if (keyboardState[g_keyboard_mapping.kc_r1])//R1
		ret &= ~0x800;

	if (keyboardState[g_keyboard_mapping.kc_r2])//R2
		ret &= ~0x200;

	if (keyboardState[g_keyboard_mapping.kc_r3])//R3
		ret &= ~0x4;
	
	if (keyboardState[g_keyboard_mapping.kc_dpad_up])//UP
		ret &= ~0x10;

	if (keyboardState[g_keyboard_mapping.kc_dpad_down])//DOWN
		ret &= ~0x40;

	if (keyboardState[g_keyboard_mapping.kc_dpad_left])//LEFT
		ret &= ~0x80;

	if (keyboardState[g_keyboard_mapping.kc_dpad_right])//RIGHT
		ret &= ~0x20;

	if (keyboardState[g_keyboard_mapping.kc_select])//SELECT
		ret &= ~0x1;

	if (keyboardState[g_keyboard_mapping.kc_start])//START
		ret &= ~0x8;

	return ret;
}

extern int activeControllers;

void PsyX_InternalPadUpdates()
{
	if (g_padCommStarted == 0)
		return;
	
	unsigned short kbInputs = UpdateKeyboardInput();

	//Update pad
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			if (padHandle[i] != NULL)
			{
				PADRAW* pad = (PADRAW*)padData[i];
				
				UpdateGameControllerInput(padHandle[i], pad);

				pad->status = 0;	// PadStateStable?

				// switch to analog state
				if((pad->analog[0] == 255 || 
					pad->analog[1] == 255 || 
					pad->analog[2] == 255 || 
					pad->analog[3] == 255) && 
					pad->id == 0x41)
				{
					eprintf("Switched controller type to ANALOG\n");
					pad->id = 0x73;
				}

				if (activeControllers & 0x1)
				{
					// switch state
					if(kbInputs != 0xFFFF && pad->id == 0x73)
					{
						eprintf("Switched controller type to SIMPLE\n");
						pad->id = 0x41;
					}
					
					*(unsigned short*)pad->buttons &= kbInputs;
				}
			}
		}
	}
	else
	{
		//Update keyboard
		if (padData[0] != NULL && activeControllers & 0x1)
		{
			PADRAW* pad = (PADRAW*)padData[0];

			pad->status = 0;	// PadStateStable?
			pad->id = 0x41;
			*(unsigned short*)pad->buttons = kbInputs;
			pad->analog[0] = 127;	// TODO: mouse?
			pad->analog[1] = 127;
			pad->analog[2] = 127;
			pad->analog[3] = 127;
		}
	}

	//Update keyboard
	if (padData[1] != NULL && activeControllers & 0x2)
	{
		PADRAW* pad = (PADRAW*)padData[1];

		pad->status = 0;	// PadStateStable?
		pad->id = 0x41;
		*(unsigned short*)pad->buttons = kbInputs;
		pad->analog[0] = 128;
		pad->analog[1] = 128;
		pad->analog[2] = 128;
		pad->analog[3] = 128;
	}

#if defined(__ANDROID__)
	///@TODO SDL_NumJoysticks always reports > 0 for some reason on Android.
	((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
#endif
}