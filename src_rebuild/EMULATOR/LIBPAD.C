#include "LIBPAD.H"

#include "EMULATOR.H"

#include <SDL.h>

SDL_GameController* padHandle[MAX_CONTROLLERS];
unsigned char* padData[MAX_CONTROLLERS];

const unsigned char* keyboardState;

void PadInitDirect(unsigned char* pad1, unsigned char* pad2)
{
	if (pad1 != NULL)
	{
		padData[0] = pad1;

		PADRAW* pad = (PADRAW*)pad1;
		pad->status = 0xFF;
		pad->id = 0;
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
		eprinterr("Failed to initialise subsystem GAMECONTROLLER\n");
	}

	if (SDL_NumJoysticks() < 1)
	{
		eprinterr("Failed to locate a connected gamepad!\n");
	}
	else
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (SDL_IsGameController(i) && i < MAX_CONTROLLERS)
			{
				padHandle[i] = SDL_GameControllerOpen(i);///@TODO close joysticks
			}
		}
	}

	keyboardState = SDL_GetKeyboardState(NULL);
}

void PadInitMtap(unsigned char* unk00, unsigned char* unk01)
{
	UNIMPLEMENTED();
}

void PadInitGun(unsigned char* unk00, int unk01)
{
	UNIMPLEMENTED();
}

int PadChkVsync()
{
	UNIMPLEMENTED();
	return 0;
}

void PadStartCom()
{
	UNIMPLEMENTED();
}

void PadStopCom()
{
	UNIMPLEMENTED();
}

unsigned int PadEnableCom(unsigned int unk00)
{
	UNIMPLEMENTED();
	return 0;
}

void PadEnableGun(unsigned char unk00)
{
	UNIMPLEMENTED();
}

void PadRemoveGun()
{
	UNIMPLEMENTED();
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
	UNIMPLEMENTED();
	return 0;
}

int PadInfoComb(int unk00, int unk01, int unk02)
{
	UNIMPLEMENTED();
	return 0;
}

int PadSetActAlign(int unk00, unsigned char* unk01)
{
	UNIMPLEMENTED();
	return 0;
}

int PadSetMainMode(int socket, int offs, int lock)
{
	UNIMPLEMENTED();
	return 0;
}

void PadSetAct(int unk00, unsigned char* unk01, int unk02)
{
	UNIMPLEMENTED();
}

unsigned short UpdateGameControllerInput(SDL_GameController* pad)
{
	unsigned short ret = 0xFFFF;

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_X))//Square
	{
		ret &= ~0x8000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_B))//Circle
	{
		ret &= ~0x2000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_Y))//Triangle
	{
		ret &= ~0x1000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_A))//Cross
	{
		ret &= ~0x4000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_LEFTSHOULDER))//L1
	{
		ret &= ~0x400;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))//R1
	{
		ret &= ~0x800;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_UP))//UP
	{
		ret &= ~0x10;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN))//DOWN
	{
		ret &= ~0x40;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_LEFT))//LEFT
	{
		ret &= ~0x80;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))//RIGHT
	{
		ret &= ~0x20;
	}

	if (SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERLEFT))//L2
	{
		ret &= ~0x100;
	}

	if (SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT))//R2
	{
		ret &= ~0x200;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_LEFTSTICK))//L3
	{
		ret &= ~0x2;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_RIGHTSTICK))//R3
	{
		ret &= ~0x4;
	}
	
	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_BACK))//SELECT
	{
		ret &= ~0x1;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_START))//START
	{
		ret &= ~0x8;
	}
	
	return ret;
}

unsigned short UpdateKeyboardInput()
{
	unsigned short ret = 0xFFFF;

	//Not initialised yet
	if (keyboardState == NULL)
	{
		return ret;
	}

	SDL_PumpEvents();

	if (keyboardState[SDL_SCANCODE_X])//Square
	{
		ret &= ~0x8000;
	}

	if (keyboardState[SDL_SCANCODE_V])//Circle
	{
		ret &= ~0x2000;
	}

	if (keyboardState[SDL_SCANCODE_Z])//Triangle
	{
		ret &= ~0x1000;
	}

	if (keyboardState[SDL_SCANCODE_C])//Cross
	{
		ret &= ~0x4000;
	}

	if (keyboardState[SDL_SCANCODE_LSHIFT])//L1
	{
		ret &= ~0x400;
	}

	if (keyboardState[SDL_SCANCODE_RSHIFT])//R1
	{
		ret &= ~0x800;
	}

	if (keyboardState[SDL_SCANCODE_UP])//UP
	{
		ret &= ~0x10;
	}

	if (keyboardState[SDL_SCANCODE_DOWN])//DOWN
	{
		ret &= ~0x40;
	}

	if (keyboardState[SDL_SCANCODE_LEFT])//LEFT
	{
		ret &= ~0x80;
	}

	if (keyboardState[SDL_SCANCODE_RIGHT])//RIGHT
	{
		ret &= ~0x20;
	}

	if (keyboardState[SDL_SCANCODE_LCTRL])//L2
	{
		ret &= ~0x100;
	}

	if (keyboardState[SDL_SCANCODE_RCTRL])//R2
	{
		ret &= ~0x200;
	}

	if (keyboardState[SDL_SCANCODE_SPACE])//SELECT
	{
		ret &= ~0x1;
	}

	if (keyboardState[SDL_SCANCODE_RETURN])//START
	{
		ret &= ~0x8;
	}

	return ret;
}

extern int activeControllers;

void InternalPadUpdates()
{
	unsigned short kbInputs = UpdateKeyboardInput();

	//Update pad
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			if (padHandle[i] != NULL)
			{
				unsigned short controllerInputs = UpdateGameControllerInput(padHandle[i]);

				PADRAW* pad = (PADRAW*)padData[i];
				pad->status = 0;	// PadStateStable?
				pad->id = 0x41;
				*(unsigned short*)pad->buttons = controllerInputs;
				pad->analog[0] = 128;
				pad->analog[1] = 128;
				pad->analog[2] = 128;
				pad->analog[3] = 128;

				if (activeControllers & 0x1)
				{
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
			pad->analog[0] = 128;
			pad->analog[1] = 128;
			pad->analog[2] = 128;
			pad->analog[3] = 128;
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