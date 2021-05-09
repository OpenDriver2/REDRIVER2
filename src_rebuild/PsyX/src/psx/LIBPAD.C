#include "libpad.h"
#include "libetc.h"

#include "../PsyX_setup.h"
#include "PsyX/PsyX_public.h"

#include <string.h>


struct PsyXController
{
	Sint32				deviceId;	// linked device Id
	SDL_GameController* gc;
	SDL_Haptic*			haptic;

	u_char*				padData;
};

PsyXController			g_controllers[MAX_CONTROLLERS];
int						g_controllerToSlotMapping[MAX_CONTROLLERS] = { -1, -1 };

const u_char*			g_sdlKeyboardState = NULL;

int g_padCommEnable = 0;

void PsyX_Pad_Debug_ListControllers()
{
	int numJoysticks = SDL_NumJoysticks();
	int numHaptics = SDL_NumHaptics();

	if(numJoysticks)
	{
		eprintf("SDL GameController list:\n");

		for (int i = 0; i < numJoysticks; i++)
		{
			if (SDL_IsGameController(i))
			{
				eprintinfo("  %d '%s'\n", i, SDL_GameControllerNameForIndex(i));
			}
		}
	}
	else
		eprintwarn("No SDL GameControllers found!\n");

	if(numHaptics)
	{
		eprintf("SDL haptic list:\n");

		for (int i = 0; i < numHaptics; i++)
		{
			eprintinfo("  %d '%s'\n", i, SDL_HapticName(i));
		}
	}
	else
		eprintwarn("No SDL haptics found!\n");
}

void PsyX_Pad_OpenController(Sint32 deviceId, int slot)
{
	PsyXController& controller = g_controllers[slot];

	if(controller.gc)
	{
		return;
	}
	
	controller.gc = SDL_GameControllerOpen(deviceId);

	if(controller.gc)
	{
		// assign device id automatically
		if (controller.deviceId == -1)
			controller.deviceId = deviceId;
		
		SDL_Joystick* joy = SDL_GameControllerGetJoystick(controller.gc);

		// try open haptics
		if(SDL_JoystickIsHaptic(joy))
			controller.haptic = SDL_HapticOpenFromJoystick(joy);
		else // try open using device ID
			controller.haptic = SDL_HapticOpen(controller.deviceId);

		if(!controller.haptic)
		{
			eprintwarn("No haptic for '%s'\n", SDL_GameControllerNameForIndex(deviceId));
		}
	}
}

void PsyX_Pad_CloseController(int slot)
{
	PsyXController& controller = g_controllers[slot];

	SDL_HapticClose(controller.haptic);
	SDL_GameControllerClose(controller.gc);
	
	//controller.deviceId = -1;
	controller.gc = NULL;
	controller.haptic = NULL;
}

void PsyX_Pad_InitPad(int slot, u_char* padData)
{
	PsyXController& controller = g_controllers[slot];

	controller.padData = padData;
	controller.deviceId = g_controllerToSlotMapping[slot];

	if(padData)
	{
		PADRAW* pad = (PADRAW*)padData;
		pad->id = slot == 0 ? 0x41 : 0xFF;	// since keyboard is a main controller - it's always on
		pad->buttons[0] = 0xFF;
		pad->buttons[1] = 0xFF;
		pad->analog[0] = 128;
		pad->analog[1] = 128;
		pad->analog[2] = 128;
		pad->analog[3] = 128;
	}
}

// called from Psy-X SDL events
void PsyX_Pad_Event_ControllerAdded(Sint32 deviceId)
{
	// reinitialize haptics (why we still here?)
	SDL_QuitSubSystem(SDL_INIT_HAPTIC);			// FIXME: this will crash if you already have haptics
	SDL_InitSubSystem(SDL_INIT_HAPTIC);
	
	PsyX_Pad_Debug_ListControllers();

	// find mapping and open
	for(int i = 0; i < MAX_CONTROLLERS; i++)
	{
		PsyXController& controller = g_controllers[i];

		if(controller.deviceId == -1 || controller.deviceId == deviceId)
		{
			PsyX_Pad_OpenController(deviceId, i);
			break;
		}
	}
}

// called from Psy-X SDL events
void PsyX_Pad_Event_ControllerRemoved(Sint32 deviceId)
{
	PsyX_Pad_Debug_ListControllers();

	// find mapping and close
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		PsyXController& controller = g_controllers[i];

		if (controller.deviceId == deviceId)
		{
			PsyX_Pad_CloseController(i);
		}
	}
}

void PadInitDirect(unsigned char* pad1, unsigned char* pad2)
{
	// do not init second time!
	if (g_sdlKeyboardState != NULL)
		return;

	memset(g_controllers, 0, sizeof(g_controllers));

	// init keyboard state
	g_sdlKeyboardState = SDL_GetKeyboardState(NULL);

	PsyX_Pad_InitPad(0, pad1);
	PsyX_Pad_InitPad(1, pad2);
	
	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) < 0)
	{
		eprinterr("Failed to initialise SDL GameController subsystem!\n");
		return;
	}
	
	// Add more controllers from custom file
	SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
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
	g_padCommEnable = 1;
}

void PadStopCom()
{
	g_padCommEnable = 0;
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
	int mtap = port & 3;
	int slot = (mtap * 2) + (port >> 4) & 1;

	if(slot == 0)
		return PadStateStable;	// keyboard always here

	PsyXController& controller = g_controllers[slot];
	
	if(controller.gc && SDL_GameControllerGetAttached(controller.gc))
		return PadStateStable;

	return PadStateDiscon;
}

int PadInfoMode(int port, int term, int offs)
{
	return 7;//?
}

int PadInfoAct(int port, int acno, int term)
{
	return 0;
}

int PadInfoComb(int unk00, int unk01, int unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int PadSetActAlign(int port, unsigned char* table)
{
	return 1;
}

int PadSetMainMode(int socket, int offs, int lock)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

u_short hapticData[MAX_CONTROLLERS][64];
int hapticEffects[MAX_CONTROLLERS] = { -1, -1 };

void PadSetAct(int port, unsigned char* table, int len)
{
	int mtap = port & 3;
	int slot = (mtap * 2) + (port >> 4) & 1;

	PsyXController& controller = g_controllers[slot];
	
	if (!controller.haptic)
		return;

	if (len == 0)
		return;

	SDL_HapticEffect eff;
	eff.type = SDL_HAPTIC_LEFTRIGHT;
	
	eff.leftright.small_magnitude = table[0] * 255;
	
	if(len > 1)
		eff.leftright.large_magnitude = table[1] * 255;
	else
		eff.leftright.large_magnitude = 0;

	eff.leftright.length = 400;
	
	if (SDL_HapticEffectSupported(controller.haptic, &eff) != SDL_TRUE)
		return;
	
	if(hapticEffects[slot] == -1)
	{
		hapticEffects[slot] = SDL_HapticNewEffect(controller.haptic, &eff);
		if(hapticEffects[slot] == -1)
		{
			eprintwarn("Warning: Unable to create haptic effect! %s\n", SDL_GetError());
		}
	}
	else
		SDL_HapticUpdateEffect(controller.haptic, hapticEffects[slot], &eff);
	
	if (SDL_HapticRunEffect(controller.haptic, hapticEffects[slot], 1) != 0)
	{
		eprintwarn("Warning: Unable to run haptic effect! %s\n", SDL_GetError());
	}
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

void PsyX_Pad_UpdateGameControllerInput(SDL_GameController* cont, PADRAW* pad)
{
	unsigned short ret = 0xFFFF;

	if (!cont)
	{
		pad->analog[0] = 127;
		pad->analog[1] = 127;
		pad->analog[2] = 127;
		pad->analog[3] = 127;

		*(u_short*)pad->buttons = ret;
		return;
	}
	
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
	
	*(u_short*)pad->buttons = ret;

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
	if (g_sdlKeyboardState == NULL)
		return ret;

	SDL_PumpEvents();

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_square])//Square
		ret &= ~0x8000;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_circle])//Circle
		ret &= ~0x2000;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_triangle])//Triangle
		ret &= ~0x1000;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_cross])//Cross
		ret &= ~0x4000;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_l1])//L1
		ret &= ~0x400;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_l2])//L2
		ret &= ~0x100;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_l3])//L3
		ret &= ~0x2;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_r1])//R1
		ret &= ~0x800;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_r2])//R2
		ret &= ~0x200;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_r3])//R3
		ret &= ~0x4;
	
	if (g_sdlKeyboardState[g_keyboard_mapping.kc_dpad_up])//UP
		ret &= ~0x10;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_dpad_down])//DOWN
		ret &= ~0x40;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_dpad_left])//LEFT
		ret &= ~0x80;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_dpad_right])//RIGHT
		ret &= ~0x20;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_select])//SELECT
		ret &= ~0x1;

	if (g_sdlKeyboardState[g_keyboard_mapping.kc_start])//START
		ret &= ~0x8;

	return ret;
}

extern int g_activeKeyboardControllers;

void PsyX_Pad_InternalPadUpdates()
{
	if (g_padCommEnable == 0)
		return;
	
	unsigned short kbInputs = UpdateKeyboardInput();

	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		PsyXController& controller = g_controllers[i];

		if (controller.padData)
		{
			PADRAW* pad = (PADRAW*)controller.padData;

			PsyX_Pad_UpdateGameControllerInput(controller.gc, pad);

			if (i == 0)	// Update keyboard for PAD 1
			{
				pad->status = 0;	// PadStateStable?

				// switch to analog state
				if ((pad->analog[0] == 255 ||
					pad->analog[1] == 255 ||
					pad->analog[2] == 255 ||
					pad->analog[3] == 255) &&
					pad->id == 0x41)
				{
					eprintf("Switched controller type to ANALOG\n");
					pad->id = 0x73;
				}
				
				if(g_activeKeyboardControllers & 0x1)
				{
					// switch state
					if (kbInputs != 0xFFFF && pad->id == 0x73)
					{
						eprintf("Switched controller type to SIMPLE\n");
						pad->id = 0x41;
						pad->analog[0] = 127;	// TODO: mouse?
						pad->analog[1] = 127;
						pad->analog[2] = 127;
						pad->analog[3] = 127;
					}

					*(u_short*)pad->buttons &= kbInputs;
				}
			}
			else if (i == 1)	// Update keyboard for PAD 2
			{
				if (g_activeKeyboardControllers & 0x2)
				{
					pad->status = 0;	// PadStateStable?
					pad->id = 0x41;
					pad->analog[0] = 127;
					pad->analog[1] = 127;
					pad->analog[2] = 127;
					pad->analog[3] = 127;

					*(u_short*)pad->buttons &= kbInputs;
				}
			}
		}
	}

#if defined(__ANDROID__)
	///@TODO SDL_NumJoysticks always reports > 0 for some reason on Android.
#endif
}