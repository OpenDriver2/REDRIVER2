#include "DRIVER2.H"
#include "PAD.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "CUTSCENE.H"
#include "PAUSE.H"
#include "GLAUNCH.H"
#include "MAIN.H"
#include "PLAYERS.H"
#include "CARS.H"

#include <string.h>



unsigned char High_shake_data[] = { 1, 0xFF, 0xFF, 0xC8, 0x50, 0x50, 0x50, 0x50, 0x50, 0x46, 0x46, 0x46, 0x46, 0x46, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0 };

unsigned char Med_shake_data[] = { 1, 0xC8, 0xC8, 0x64, 0x46, 0x46, 0x46, 0x46, 0x46, 0xA, 0xA, 0xA, 0 };

unsigned char Low_shake_data[] = { 1, 0xA0, 0xA0, 0x46, 0x46, 0xA, 0xA, 0xA, 0xA, 0 };

unsigned char* shake_data[] = { High_shake_data, Med_shake_data, Low_shake_data };

PAD Pads[2];
int numPadsConnected = 0;
int pad_connected = 0;
int gVibration = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ InitControllers()
 // line 75, offset 0x0006b480
	/* begin block 1 */
		// Start line: 77
		// Start offset: 0x0006B480
		// Variables:
	// 		int i; // $s3
	// 		int j; // $a1
	/* end block 1 */
	// End offset: 0x0006B5A8
	// End Line: 111

	/* begin block 2 */
		// Start line: 150
	/* end block 2 */
	// End Line: 151

	/* begin block 3 */
		// Start line: 151
	/* end block 3 */
	// End Line: 152

	/* begin block 4 */
		// Start line: 156
	/* end block 4 */
	// End Line: 157

/* WARNING: Unknown calling convention yet parameter storage is locked */

char padbuffer[2][PADBUFFER_SIZE];	// [A] was static
DUPLICATION DuplicatePadData;		// [A]

// [D] [T]
void InitControllers(void)
{
	int i, j;
	struct PAD* pad;

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

// decompiled code
// original method signature: 
// void /*$ra*/ CloseControllers()
 // line 113, offset 0x0006bdf8
	/* begin block 1 */
		// Start line: 115
		// Start offset: 0x0006BDF8
		// Variables:
	// 		int i; // $v1
	/* end block 1 */
	// End offset: 0x0006BE38
	// End Line: 124

	/* begin block 2 */
		// Start line: 226
	/* end block 2 */
	// End Line: 227

	/* begin block 3 */
		// Start line: 837
	/* end block 3 */
	// End Line: 838

	/* begin block 4 */
		// Start line: 839
	/* end block 4 */
	// End Line: 840

/* WARNING: Unknown calling convention yet parameter storage is locked */

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



// decompiled code
// original method signature: 
// void /*$ra*/ ReadControllers()
 // line 132, offset 0x0006b5a8
	/* begin block 1 */
		// Start line: 134
		// Start offset: 0x0006B5A8
		// Variables:
	// 		int i; // $s3
	// 		int pad; // $s2
	/* end block 1 */
	// End offset: 0x0006B6F0
	// End Line: 189

	/* begin block 2 */
		// Start line: 299
	/* end block 2 */
	// End Line: 300

	/* begin block 3 */
		// Start line: 321
	/* end block 3 */
	// End Line: 322

	/* begin block 4 */
		// Start line: 322
	/* end block 4 */
	// End Line: 323

	/* begin block 5 */
		// Start line: 325
	/* end block 5 */
	// End Line: 326

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void ReadControllers(void)
{
#ifndef PSX
	Emulator_UpdateInput();
#endif

	int pad;

	if (DuplicatePadData.buffer)
		memcpy(DuplicatePadData.buffer, &padbuffer, DuplicatePadData.size);

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



// decompiled code
// original method signature: 
// void /*$ra*/ SetPadVibration(int pad /*$a3*/, unsigned char type /*$a1*/)
 // line 191, offset 0x0006be38
	/* begin block 1 */
		// Start line: 927
	/* end block 1 */
	// End Line: 928

	/* begin block 2 */
		// Start line: 995
	/* end block 2 */
	// End Line: 996

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



// decompiled code
// original method signature: 
// void /*$ra*/ StopPadVibration(int pad /*$a0*/)
 // line 209, offset 0x0006beb4
	/* begin block 1 */
		// Start line: 1033
	/* end block 1 */
	// End Line: 1034

	/* begin block 2 */
		// Start line: 1034
	/* end block 2 */
	// End Line: 1035

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



// decompiled code
// original method signature: 
// void /*$ra*/ StopDualShockMotors()
 // line 228, offset 0x0006beec
	/* begin block 1 */
		// Start line: 1073
	/* end block 1 */
	// End Line: 1074

	/* begin block 2 */
		// Start line: 1074
	/* end block 2 */
	// End Line: 1075

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void StopDualShockMotors(void)
{
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetDuplicatePadData(char *buffer /*$a0*/, int size /*$a1*/)
 // line 232, offset 0x0006bef4
	/* begin block 1 */
		// Start line: 1081
	/* end block 1 */
	// End Line: 1082

	/* begin block 2 */
		// Start line: 1082
	/* end block 2 */
	// End Line: 1083

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



// decompiled code
// original method signature: 
// void /*$ra*/ MapPad(int pad /*$t2*/, struct PADRAW *pData /*$a3*/)
 // line 257, offset 0x0006b6f0
	/* begin block 1 */
		// Start line: 258
		// Start offset: 0x0006B6F0
		// Variables:
	// 		unsigned short i; // $a3
	// 		unsigned short buttons; // $t0
	// 		unsigned short mapped; // $t1
	/* end block 1 */
	// End offset: 0x0006B8D8
	// End Line: 321

	/* begin block 2 */
		// Start line: 532
	/* end block 2 */
	// End Line: 533

	/* begin block 3 */
		// Start line: 601
	/* end block 3 */
	// End Line: 602

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



// decompiled code
// original method signature: 
// void /*$ra*/ ClearPad(int pad /*$a0*/)
 // line 323, offset 0x0006bf24
	/* begin block 1 */
		// Start line: 1263
	/* end block 1 */
	// End Line: 1264

	/* begin block 2 */
		// Start line: 1264
	/* end block 2 */
	// End Line: 1265

// [D] [T]
void ClearPad(int pad)
{
	Pads[pad].direct = 0;
	Pads[pad].dirnew = 0;
	Pads[pad].mapped = 0;
	Pads[pad].mapnew = 0;
}


// decompiled code
// original method signature: 
// void /*$ra*/ HandleDualShock()
 // line 336, offset 0x0006b8e0
	/* begin block 1 */
		// Start line: 338
		// Start offset: 0x0006B8E0
		// Variables:
	// 		int state; // $v1
	// 		int port; // $s3
	// 		int pad; // $s5
	// 		int dsload; // $s7
	/* end block 1 */
	// End offset: 0x0006BBC4
	// End Line: 450

	/* begin block 2 */
		// Start line: 776
	/* end block 2 */
	// End Line: 777

	/* begin block 3 */
		// Start line: 777
	/* end block 3 */
	// End Line: 778

	/* begin block 4 */
		// Start line: 778
	/* end block 4 */
	// End Line: 779

/* WARNING: Unknown calling convention yet parameter storage is locked */

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



// decompiled code
// original method signature: 
// void /*$ra*/ HandlePadVibration(int pad /*$t1*/)
 // line 452, offset 0x0006bbc4
	/* begin block 1 */
		// Start line: 453
		// Start offset: 0x0006BBC4
		// Variables:
	// 		int speed; // $a3
	/* end block 1 */
	// End offset: 0x0006BDE8
	// End Line: 496

	/* begin block 2 */
		// Start line: 1119
	/* end block 2 */
	// End Line: 1120

	/* begin block 3 */
		// Start line: 1122
	/* end block 3 */
	// End Line: 1123

	/* begin block 4 */
		// Start line: 1123
	/* end block 4 */
	// End Line: 1124

int gDualShockMax = 255;

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





