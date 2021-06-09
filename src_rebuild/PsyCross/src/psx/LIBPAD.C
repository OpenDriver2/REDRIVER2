#include "psx/libpad.h"
#include "psx/libetc.h"

#include "../PsyX_main.h"
#include "../pad/PsyX_pad.h"

#include "PsyX/PsyX_public.h"

#include <string.h>

int g_padCommEnable = 0;

void PadInitDirect(unsigned char* pad1, unsigned char* pad2)
{
	PsyX_Pad_InitPad(0, pad1);
	PsyX_Pad_InitPad(1, pad2);
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
	int mtap, slot;

	mtap = port & 3;
	slot = (mtap * 2) + (port >> 4) & 1;

	return PsyX_Pad_GetStatus(mtap, slot) ? PadStateStable : PadStateDiscon;
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

void PadSetAct(int port, unsigned char* table, int len)
{
	int mtap, slot;

	mtap = port & 3;
	slot = (mtap * 2) + (port >> 4) & 1;

	PsyX_Pad_Vibrate(mtap, slot, table, len);
}