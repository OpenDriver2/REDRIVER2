#include "THISDUST.H"
#include "PAD.H"
#include "SYSTEM.H"
#include <string.h>


char High_shake_data[] = { 1, 0xFF, 0xFF, 0xC8, 0x50, 0x50, 0x50, 0x50, 0x50, 0x46, 0x46, 0x46, 0x46, 0x46, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0 };

char Med_shake_data[] = { 1, 0xC8, 0xC8, 0x64, 0x46, 0x46, 0x46, 0x46, 0x46, 0xA, 0xA, 0xA, 0 };

char Low_shake_data[] = { 1, 0xA0, 0xA0, 0x46, 0x46, 0xA, 0xA, 0xA, 0xA, 0 };

char* shake_data[] = { High_shake_data, Med_shake_data, Low_shake_data };

struct PAD Pads[2];
int numPadsConnected = 0;
int pad_connected = 0;

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

const int PADBUFFER_SIZE = 34;

static char padbuffer[2][PADBUFFER_SIZE];
static DUPLICATION DuplicatePadData;

// [D]
void InitControllers(void)
{
	struct PAD* pad;

	DuplicatePadData.buffer = NULL;
	DuplicatePadData.size = 0;

	PadInitDirect((unsigned char*)padbuffer[0], (unsigned char*)padbuffer[1]);
	PadStartCom();

	for (int i = 0; i < 2; i++)
	{
		pad = &Pads[i];

		pad->active = 0;
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

		for (int j = 0; j < 16; j++)
			pad->mappings.button_lookup[j] = 0;

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

void CloseControllers(void)
{
	UNIMPLEMENTED();

	/*
	PAD *pPVar1;
	int iVar2;

	PadStopCom();
	pPVar1 = Pads;
	iVar2 = 1;
	do {
		pPVar1->active = '\0';
		pPVar1->type = '\0';
		iVar2 = iVar2 + -1;
		pPVar1 = pPVar1 + 1;
	} while (-1 < iVar2);
	return;
	*/
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

// [D]
void ReadControllers(void)
{
#ifndef PSX
	Emulator_UpdateInput();
#endif

	char *pData;
	int pad;
	int iVar2;

	pad = 0;

	if (DuplicatePadData.buffer)
		memcpy(DuplicatePadData.buffer, &padbuffer, DuplicatePadData.size);

	pData = padbuffer[0];
	iVar2 = 1;
	do {
		PADRAW* padRaw = (PADRAW*)pData;

		if (padRaw->status == '\0')
		{
			if ((padRaw->id == 65) || (padRaw->id == 115))
			{
				MapPad(pad, padRaw);
			}
			else 
			{
				Pads[pad].type = 1;
				ClearPad(pad);
			}
		}
		else {
			Pads[pad].type = 0;
			ClearPad(pad);
		}

		pad = pad + 1;
		iVar2 = iVar2 + -1;
		pData += PADBUFFER_SIZE;
	} while (-1 < iVar2);

	HandleDualShock();
	pad_connected = (Pads[0].type != 0);

	if (Pads[0].type == 1)
		pad_connected = -1;

	if (1 < NumPlayers) 
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

void SetPadVibration(int pad, unsigned char type)
{
	UNIMPLEMENTED();

	/*
	if (-1 < pad) {
		if ((Pads[pad].dualshock != '\0') && (gInGameCutsceneActive == 0)) {
			Pads[pad].shake_type = type;
			Pads[pad].vibrate = '\x06';
			return;
		}
		Pads[pad].shakeptr = (uchar *)0x0;
		Pads[pad].shake_type = '\0';
		Pads[pad].vibrate = '\0';
	}
	return;
	*/
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

void StopPadVibration(int pad)
{
	UNIMPLEMENTED();

	/*
	Pads[pad].motors[0] = '\0';
	Pads[pad].motors[1] = '\0';
	Pads[pad].shakeptr = (uchar *)0x0;
	Pads[pad].shake_type = '\0';
	Pads[pad].vibrate = '\0';
	Pads[pad].alarmShakeCounter = '\0';
	return;
	*/
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

void SetDuplicatePadData(char *buffer, int size)
{
	if (size - 1U < 0x22) {
		DuplicatePadData.buffer = buffer;
		DuplicatePadData.size = size;
		return;
	}
	DuplicatePadData.buffer = (char *)0x0;
	DuplicatePadData.size = 0;
	return;
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

void MapPad(int pad, PADRAW *pData)
{
	UNIMPLEMENTED();

	/*
	uchar uVar1;
	ushort uVar2;
	ushort uVar3;
	byte bVar4;
	uint uVar5;
	char cVar6;
	char cVar7;
	char cVar8;
	uint uVar9;
	uint uVar10;
	ushort uVar11;

	if (pData->status != '\0') {
		Pads[pad].type = '\0';
		return;
	}
	bVar4 = pData->id >> 4;
	if (bVar4 == 4) {
		Pads[pad].type = '\x02';
	}
	else {
		if (bVar4 != 7) {
			Pads[pad].type = '\x01';
			return;
		}
		Pads[pad].type = '\x04';
	}
	uVar11 = Pads[pad].direct;
	uVar10 = ~(uint)CONCAT11(pData->buttons[0], pData->buttons[1]) & 0xffff;
	Pads[pad].direct = (ushort)uVar10;
	Pads[pad].dirnew = (ushort)uVar10 & ~uVar11;
	Pads[pad].diranalog[0] = pData->analog[0] + -0x80;
	Pads[pad].diranalog[1] = pData->analog[1] + -0x80;
	Pads[pad].diranalog[2] = pData->analog[2] + -0x80;
	uVar1 = Pads[pad].active;
	Pads[pad].diranalog[3] = pData->analog[3] + -0x80;
	if (uVar1 != '\0') {
		uVar11 = 0;
		uVar9 = 0;
		uVar5 = uVar10;
		do {
			if ((uVar5 & 1) != 0) {
				uVar11 = Pads[pad].mappings.button_lookup[uVar9] | uVar11;
			}
			uVar5 = uVar9 + 1;
			uVar9 = uVar5 & 0xffff;
			uVar5 = (int)uVar10 >> (uVar5 & 0x1f);
		} while (uVar9 < 0x10);
		uVar2 = Pads[pad].mapped;
		uVar3 = Pads[pad].mappings.swap_analog;
		Pads[pad].mapped = uVar11;
		Pads[pad].mapnew = uVar11 & ~uVar2;
		if (uVar3 == 0) {
			cVar6 = Pads[pad].diranalog[1];
			cVar7 = Pads[pad].diranalog[2];
			cVar8 = Pads[pad].diranalog[3];
			Pads[pad].mapanalog[0] = Pads[pad].diranalog[0];
		}
		else {
			cVar6 = Pads[pad].diranalog[3];
			cVar7 = Pads[pad].diranalog[0];
			cVar8 = Pads[pad].diranalog[1];
			Pads[pad].mapanalog[0] = Pads[pad].diranalog[2];
		}
		Pads[pad].mapanalog[1] = cVar6;
		Pads[pad].mapanalog[2] = cVar7;
		Pads[pad].mapanalog[3] = cVar8;
	}
	return;
	*/
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

// [D]
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

void HandleDualShock(void)
{
	UNIMPLEMENTED();

	/*
	uchar uVar1;
	undefined4 uVar2;
	int iVar3;
	uint uVar4;
	int pad;
	int iVar5;

	iVar5 = 0;
	pad = 0;
	do {
		uVar4 = (uint)Pads[pad].port;
		HandlePadVibration(pad);
		if (Pads[pad].active == '\0') {
			Pads[pad].motors[0] = '\0';
			Pads[pad].motors[1] = '\0';
			Pads[pad].vibrate = '\0';
		}
		uVar2 = PadGetState(uVar4);
		switch (uVar2) {
		case 0:
		case 4:
			break;
		case 1:
			uVar1 = Pads[pad].dsactive;
			Pads[pad].state = '\x01';
			if (uVar1 != '\0') {
				Pads[pad].dualshock = '\0';
				Pads[pad].dsactive = '\0';
				Pads[pad].state = '\0';
				Pads[pad].delay = '\x06';
			LAB_0006ba78:
				Pads[pad].motors[0] = '\0';
				Pads[pad].motors[1] = '\0';
				Pads[pad].vibrate = '\0';
			}
			break;
		case 2:
			if (Pads[pad].state == '\x06') goto LAB_0006ba8c;
			Pads[pad].state = '\x06';
			break;
		default:
		LAB_0006ba8c:
			if ((Pads[pad].dsactive == '\0') ||
				(((Pads[pad].vibrate == '\0' && (Pads[pad].alarmShakeCounter == '\0')) || (0x32 < iVar5))))
			{
				Pads[pad].motors[0] = '\0';
				Pads[pad].motors[1] = '\0';
			}
			else {
				if ((Pads[pad].vibrate == '\x06') || (Pads[pad].alarmShakeCounter != '\0')) {
					if (gVibration == 0) {
						PadSetAct(uVar4, dummymotors, 2);
					}
					else {
						if (Pads[pad].motors[0] != '\0') {
							iVar5 = iVar5 + 10;
						}
						if (Pads[pad].motors[1] != '\0') {
							iVar5 = iVar5 + 0x14;
						}
						PadSetAct(uVar4, pad * 0x48 + 0xd92fc, 2);
					}
				}
				if (Pads[pad].vibrate != '\0') {
					Pads[pad].vibrate = Pads[pad].vibrate + -1;
				}
			}
			break;
		case 6:
			if (Pads[pad].state == '\x06') goto LAB_0006ba8c;
			iVar3 = PadInfoMode(uVar4, 4, 1);
			if (iVar3 != 7) {
				Pads[pad].dualshock = '\0';
			LAB_0006ba60:
				Pads[pad].state = '\x06';
				goto LAB_0006ba78;
			}
			uVar1 = Pads[pad].delay;
			Pads[pad].dualshock = '\x01';
			if (uVar1 == '\x06') {
				iVar3 = PadSetActAlign(uVar4, align);
				if (iVar3 != 0) {
					Pads[pad].dsactive = '\x01';
					goto LAB_0006ba60;
				}
				Pads[pad].delay = '\0';
			}
			else {
				Pads[pad].delay = uVar1 + '\x01';
			}
		}
		pad = pad + 1;
		if (1 < pad) {
			return;
		}
	} while (true);
	*/
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

void HandlePadVibration(int pad)
{
	UNIMPLEMENTED();

	/*
	byte bVar1;
	uchar uVar2;
	byte *pbVar3;
	int iVar4;
	byte **ppbVar5;
	int iVar6;

	iVar6 = 0;
	if ((((NoPlayerControl != 0) || (gDualShockMax == 0)) || (gDrawPauseMenus != 0)) ||
		((game_over != 0 || (gInGameCutsceneActive != 0)))) {
		StopPadVibration(pad);
		return;
	}
	if ((&player)[pad].onGrass != '\0') {
		iVar6 = *(int *)(car_data[(&player)[pad].playerCarId].st + 0x2c) >> 0xf;
		if (iVar6 < 0) {
			iVar6 = -iVar6;
		}
		iVar6 = iVar6 + car_data[(&player)[pad].playerCarId].hd.speed;
		if (0x3c < iVar6) {
			iVar6 = 0x3c;
		}
		Pads[pad].vibrate = '\x06';
	}
	if (Pads[pad].shake_type == '\0') {
	LAB_0006bd30:
		if (Pads[pad].shakeptr == (uchar *)0x0) goto LAB_0006bd84;
	}
	else {
		if (Pads[pad].shakeptr == (uchar *)0x0) {
			Pads[pad].shakeptr = shake_data3[(uint)Pads[pad].shake_type - 1];
			goto LAB_0006bd30;
		}
	}
	ppbVar5 = &Pads[pad].shakeptr;
	bVar1 = **ppbVar5;
	pbVar3 = *ppbVar5 + 1;
	*ppbVar5 = pbVar3;
	iVar6 = iVar6 + (uint)bVar1;
	if (*pbVar3 == 0) {
		*ppbVar5 = (byte *)0x0;
	}
LAB_0006bd84:
	if (0xff < iVar6) {
		iVar6 = 0xff;
	}
	iVar4 = gDualShockMax + 0x100;
	uVar2 = Pads[pad].alarmShakeCounter;
	Pads[pad].shake_type = '\0';
	Pads[pad].motors[1] = (uchar)(iVar6 * iVar4 >> 9);
	if (uVar2 != '\0') {
		Pads[pad].alarmShakeCounter = uVar2 + -1;
		if (uVar2 == '\x01') {
			Pads[pad].motors[0] = '\0';
		}
		else {
			Pads[pad].motors[0] = '\x01';
		}
	}
	return;
	*/
}





