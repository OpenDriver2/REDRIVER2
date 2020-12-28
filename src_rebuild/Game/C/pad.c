#include "driver2.h"
#include "pad.h"
#include "system.h"
#include "mission.h"
#include "cutscene.h"
#include "pause.h"
#include "glaunch.h"
#include "main.h"
#include "players.h"
#include "cars.h"

#include "STRINGS.H"

#ifdef PSX
typedef struct PADRAW
{
	unsigned char status; // size=0, offset=0
	unsigned char id; // size=0, offset=1
	unsigned char buttons[2]; // size=2, offset=2
	unsigned char analog[4]; // size=4, offset=4
} *LPPADRAW;
#endif

void HandlePadVibration(int pad);

u_char High_shake_data[] = { 1, 0xFF, 0xFF, 0xC8, 0x50, 0x50, 0x50, 0x50, 0x50, 0x46, 0x46, 0x46, 0x46, 0x46, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0 };
u_char Med_shake_data[] = { 1, 0xC8, 0xC8, 0x64, 0x46, 0x46, 0x46, 0x46, 0x46, 0xA, 0xA, 0xA, 0 };
u_char Low_shake_data[] = { 1, 0xA0, 0xA0, 0x46, 0x46, 0xA, 0xA, 0xA, 0xA, 0 };

unsigned char* shake_data[] = {
	High_shake_data,
	Med_shake_data,
	Low_shake_data
};

PAD Pads[2];
int numPadsConnected = 0;
int pad_connected = 0;

int gVibration = 0;
int gDualShockMax = 255;

char padbuffer[2][PADBUFFER_SIZE];	// [A] was static
DUPLICATION DuplicatePadData;		// [A]

// [D] [T]
void InitControllers(void)
{
	int i, j;
	PAD* pad;

	DuplicatePadData.buffer = NULL;
	DuplicatePadData.size = 0;

	PadInitDirect((unsigned char*)padbuffer[0], (unsigned char*)padbuffer[1]);
	PadStartCom();

	for (i = 0; i < 2; i++)
	{
		pad = &Pads[i];

		pad->active = 1;
		pad->type = 0;
		pad->dualshock = 0;
		pad->motors[0] = 0;
		pad->motors[1] = 0;
		pad->vibrate = 0;
		pad->alarmShakeCounter = 0;
		pad->shake_type = 0;
		pad->shakeptr = NULL;
		pad->port = (i << 4);
		pad->state = 0;
		pad->delay = 6;
		pad->dsactive = 0;

		for (j = 0; j < 16; j++)
		{
			pad->mappings.button_lookup[j] = 1 << (j & 0x1f);
		}

		pad->mappings.swap_analog = 0;
	}
}

// [D] [T]
void CloseControllers(void)
{
	int i;

	PadStopCom();

	i = 0;
	do {
		Pads[i].active = 0;
		Pads[i].type = 0;
		i++;
	} while (i < 2);
}


// [D] [T]
void SetPadVibration(int pad, unsigned char type)
{
	if (pad < 0)
		return;

	if(Pads[pad].dualshock != 0 && gInGameCutsceneActive == 0) 
	{
		Pads[pad].shake_type = type;
		Pads[pad].vibrate = 6;
		return;
	}

	Pads[pad].shakeptr = NULL;
	Pads[pad].shake_type = 0;
	Pads[pad].vibrate = 0;
}

// [D] [T]
void StopPadVibration(int pad)
{
	Pads[pad].motors[0] = 0;
	Pads[pad].motors[1] = 0;
	Pads[pad].shakeptr = NULL;
	Pads[pad].shake_type = 0;
	Pads[pad].vibrate = 0;
	Pads[pad].alarmShakeCounter = 0;
}

// [D] [T]
void StopDualShockMotors(void)
{
	return;
}

// [D] [T]
void SetDuplicatePadData(char *buffer, int size)
{
	if (size - 1U < PADBUFFER_SIZE) 
	{
		DuplicatePadData.buffer = buffer;
		DuplicatePadData.size = size;
		return;
	}

	DuplicatePadData.buffer = NULL;
	DuplicatePadData.size = 0;
}

// [D] [T]
void MapPad(int pad, PADRAW *pData)
{
	unsigned char uVar1;

	ushort i;
	ushort buttons;
	ushort mapped;

	if (pData->status != 0)
	{
		Pads[pad].type = 0;
		return;
	}

	if (pData->id >> 4 == 4)
	{
		Pads[pad].type = 2;
	}
	else if(pData->id >> 4 == 7)
	{
		Pads[pad].type = 4;
	}
	else
	{
		Pads[pad].type = 1;
		return;
	}

	mapped = Pads[pad].direct;
	buttons = ~((pData->buttons[0] << 8) | (pData->buttons[1])) & 0xffff;

	Pads[pad].direct = buttons;
	Pads[pad].dirnew = buttons & ~mapped;

	Pads[pad].diranalog[0] = pData->analog[0] - 128;
	Pads[pad].diranalog[1] = pData->analog[1] - 128;
	Pads[pad].diranalog[2] = pData->analog[2] - 128;
	Pads[pad].diranalog[3] = pData->analog[3] - 128;

	if (Pads[pad].active != 0) 
	{
		mapped = 0;
		i = 0;

		do {
			if (((buttons >> i) & 1) != 0)
			{
				mapped |= Pads[pad].mappings.button_lookup[i];
			}

			i++;
		} while (i < 16);


		Pads[pad].mapnew = mapped & ~Pads[pad].mapped;
		Pads[pad].mapped = mapped;
		

		if (Pads[pad].mappings.swap_analog == 0)
		{
			Pads[pad].mapanalog[1] = Pads[pad].diranalog[1];
			Pads[pad].mapanalog[2] = Pads[pad].diranalog[2];
			Pads[pad].mapanalog[3] = Pads[pad].diranalog[3];
			Pads[pad].mapanalog[0] = Pads[pad].diranalog[0];
		}
		else 
		{
			Pads[pad].mapanalog[1] = Pads[pad].diranalog[3];
			Pads[pad].mapanalog[2] = Pads[pad].diranalog[0];
			Pads[pad].mapanalog[3] = Pads[pad].diranalog[1];
			Pads[pad].mapanalog[0] = Pads[pad].diranalog[2];
		}
	}
}

// [D] [T]
void ClearPad(int pad)
{
	Pads[pad].direct = 0;
	Pads[pad].dirnew = 0;
	Pads[pad].mapped = 0;
	Pads[pad].mapnew = 0;
}

// [D]
void HandleDualShock(void)
{
#ifdef PSX
	PAD* pPad;

	static unsigned char align[6] = {
		0, 1, 255, 255, 255, 255
	};

	static unsigned char dummymotors[2] = {
		0, 0
	};

	int state;
	int port;
	int pad;
	int dsload;

	dsload = 0;

	for (pad = 0; pad < 2; pad++)
	{
		pPad = &Pads[pad];
		
		port = pPad->port;
		HandlePadVibration(pad);

		if (pPad->active == 0) 
		{
			pPad->motors[0] = 0;
			pPad->motors[1] = 0;
			pPad->vibrate = 0;
		}

		state = PadGetState(port);

		switch (state) 
		{
			case 0:
			case 4:
				break;
			case 1:
				pPad->state = 1;

				if (pPad->dsactive != 0)
				{
					pPad->dualshock = 0;
					pPad->dsactive = 0;
					pPad->state = 0;
					pPad->delay = 6;
					pPad->motors[0] = 0;
					pPad->motors[1] = 0;
					pPad->vibrate = 0;
				}
				break;
			case 2:
				if (pPad->state != 6)
					pPad->state = 6;

				break;
			case 6:
				if (pPad->state != 6)
				{
					if (PadInfoMode(port, 4, 1) != 7)
					{
						pPad->dualshock = 0;
						pPad->state = 6;
						pPad->motors[0] = 0;
						pPad->motors[1] = 0;
						pPad->vibrate = 0;
						break;
					}

					pPad->dualshock = 1;

					if (pPad->delay == 6)
					{
						if (PadSetActAlign(port, align) != 0)
						{
							pPad->dsactive = 1;
							pPad->state = 6;
							pPad->motors[0] = 0;
							pPad->motors[1] = 0;
							pPad->vibrate = 0;
							break;
						}

						pPad->delay = 0;
					}
					else 
					{
						pPad->delay++;
					}
				}
				break;
		}

		if (pPad->state == 6)
		{
			if (pPad->dsactive == 0 || (pPad->vibrate == 0 && pPad->alarmShakeCounter == 0 || 50 < dsload))
			{
				pPad->motors[0] = 0;
				pPad->motors[1] = 0;
			}
			else 
			{
				if (pPad->vibrate == 6 || pPad->alarmShakeCounter != 0)
				{
					if (gVibration == 0) 
					{
						PadSetAct(port, dummymotors, 2);
					}
					else
					{
						if (pPad->motors[0] != 0) 
							dsload += 10;

						if (pPad->motors[1] != 0)
							dsload += 20;

						PadSetAct(port, pPad->motors, 2);
					}
				}

				if (pPad->vibrate != 0) 
					pPad->vibrate--;
			}
		}


	}
#endif
}

// [D]
void HandlePadVibration(int pad)
{
	int speed;
	PAD* pPad;
	
	pPad = &Pads[pad];
	speed = 0;

	if (NoPlayerControl != 0 || gDualShockMax == 0 || gDrawPauseMenus != 0 || (game_over != 0 || gInGameCutsceneActive != 0))
	{
		StopPadVibration(pad);
		return;
	}

	if (player[pad].onGrass != 0) 
	{
		speed = ABS(car_data[player[pad].playerCarId].st.n.angularVelocity[1] >> 0xf);
		speed += car_data[player[pad].playerCarId].hd.speed;

		if (speed > 60)
			speed = 60;
	
		pPad->vibrate = 6;
	}

	if (pPad->shake_type != 0)
	{
		if (pPad->shakeptr == NULL) 
			pPad->shakeptr = shake_data[pPad->shake_type - 1];
	}

	if (pPad->shakeptr)
	{
		speed += *pPad->shakeptr;

		if (++pPad->shakeptr == 0) 
			pPad->shakeptr = NULL;
	}

	if (speed > 255)
		speed = 255;

	pPad->shake_type = 0;
	pPad->motors[1] = (speed * (gDualShockMax + 256) >> 9);

	if (pPad->alarmShakeCounter != 0) 
	{
		if (pPad->alarmShakeCounter-- == 1)
			pPad->motors[0] = 0;
		else
			pPad->motors[0] = 1;
	}
}


// [D] [T]
void ReadControllers(void)
{
#ifndef PSX
	PsyX_UpdateInput();
#endif

	int pad;

	if (DuplicatePadData.buffer)
		memcpy((u_char*)DuplicatePadData.buffer, (u_char*)&padbuffer, DuplicatePadData.size);

	pad = 0;
	do {
		PADRAW* padRaw = (PADRAW*)padbuffer[pad];

		if (padRaw->status == 0)
		{
			if (padRaw->id == 65 || padRaw->id == 115)
			{
				MapPad(pad, padRaw);
			}
			else
			{
				Pads[pad].type = 1;
				ClearPad(pad);
			}
		}
		else
		{
			Pads[pad].type = 0;
			ClearPad(pad);
		}

		pad++;
	} while (pad < 2);

	HandleDualShock();
	pad_connected = (Pads[0].type != 0);

	if (Pads[0].type == 1)
		pad_connected = -1;

	if (NumPlayers > 1)
	{
		if (Pads[1].type == 0)
			pad_connected = 0;

		if (Pads[1].type == 1)
			pad_connected = -1;
	}
}