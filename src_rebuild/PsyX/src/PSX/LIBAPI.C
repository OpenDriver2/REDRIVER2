#include "libapi.h"

#include <stdio.h>
#include "../PSYX_SETUP.H"

int sp = 0;

int dword_300[] = { 0x20, 0xD,  0x0,  0x0 };
int dword_308[] = { 0x10, 0x20, 0x40, 0x1 };

#define CTR_RUNNING (0)
#define CTR_STOPPED (1)

#define CTR_MODE_TO_FFFF (0)
#define CTR_MODE_TO_TARG (1)

#define CTR_CLOCK_SYS (0)
#define CTR_CLOCK_PIXEL (1)
#define CTR_HORIZ_RETRACE (1)

#define CTR_CLOCK_SYS_ONE (0)
#define CTR_CLOCK_SYS_ONE_EIGHTH (1)

typedef struct
{
	unsigned int i_cycle;

	union
	{
		unsigned short cycle;
		unsigned short unk00;
	};

	unsigned int i_value;

	union
	{
		unsigned short value;
		unsigned short unk01;
	};

	unsigned int i_target;

	union
	{
		unsigned short target;
		unsigned short unk02;
	};


	unsigned int padding00;
	unsigned int padding01;
} SysCounter;

extern SysCounter counters[3];

SysCounter counters[3] = { 0 };

long SetRCnt(long spec, unsigned short target, long mode)//(F)
{
	int value = 0x48;

	spec &= 0xFFFF;
	if (spec > 2)
	{
		return 0;
	}

	counters[spec].value = 0;
	counters[spec].target = target;

	if (spec < 2)
	{
		if ((mode & 0x10))
		{
			value = 0x49;
		}
		else if ((mode & 0x1))//loc_148
		{
			value |= 0x100;
		}
	}
	else
	{
		//loc_158
		if (spec == 2 && !(mode & 1))
		{
			value = 0x248;
		}//loc_174
	}
	//loc_174
	if ((mode & 0x1000))
	{
		value |= 0x10;
	}//loc_180

	counters[spec].value = value;

	return 1;
}

long GetRCnt(long spec)//(F)
{
	spec &= 0xFFFF;

	if (spec > 2)
	{
		return 0;
	}

	return counters[spec].cycle;
}

long ResetRCnt(long spec)//(F)
{
	spec &= 0xFFFF;

	if (spec > 2)
	{
		return 0;
	}

	counters[spec].cycle = 0;

	return 1;
}

long StartRCnt(long spec)//(F)
{
	spec &= 0xFFFF;
	dword_300[1] |= dword_308[spec];
	return spec < 3 ? 1 : 0;
}

long StopRCnt(long spec)//TODO
{
	return 0;
}
#undef OpenEvent
long OpenEvent(unsigned long unk00, long unk01, long unk02, long(*func)())
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long CloseEvent(long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long EnableEvent(unsigned long event)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long DisableEvent(unsigned long event)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long WaitEvent(long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long TestEvent(long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long EnableEvent(long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long DisableEvent(long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void DeliverEvent(unsigned long unk00, unsigned long unk01)
{
	PSYX_UNIMPLEMENTED();
}

void UnDeliverEvent(unsigned long unk00, unsigned long unk01)
{
	PSYX_UNIMPLEMENTED();
}

long OpenTh(long(*func)(), unsigned long unk01, unsigned long unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int CloseTh(long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int ChangeTh(long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long open(char* unk00, unsigned long unk01)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long close(long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long lseek(long unk00, long unk01, long unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long read(long unk00, void* unk01, long unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long write(long unk00, void* unk01, long unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long ioctl(long unk00, long unk01, long unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

struct DIRENTRY* firstfile(char* unk00, struct DIRENTRY* unk01)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

struct DIRENTRY* nextfile(struct DIRENTRY* unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long erase(char* unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long undelete(char* unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long format(char* unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}
long rename(char* unk00, char* unk01)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long cd(char* unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long LoadTest(char*  unk00, struct EXEC* unk01)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long Load(char * unk00, struct EXEC* unk01)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long Exec(struct EXEC * unk00, long unk01, char** unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long LoadExec(char * unk00, unsigned long unk01, unsigned long unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long InitPAD(char * unk00, long unk01, char* unk02, long unk03)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long StartPAD()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void StopPAD()
{
	PSYX_UNIMPLEMENTED();
}

void EnablePAD()
{
	PSYX_UNIMPLEMENTED();
}

void DisablePAD()
{
	PSYX_UNIMPLEMENTED();
}

void FlushCache()
{
	PSYX_UNIMPLEMENTED();
}

void ReturnFromException()
{
	PSYX_UNIMPLEMENTED();
}

int EnterCriticalSection()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void ExitCriticalSection()
{
	PSYX_UNIMPLEMENTED();
}

void Exception()
{
	PSYX_UNIMPLEMENTED();
}

void SwEnterCriticalSection()
{
	PSYX_UNIMPLEMENTED();
}
void SwExitCriticalSection()
{
	PSYX_UNIMPLEMENTED();
}

unsigned long SetSp(unsigned long newsp)//(F)
{
	unsigned long old_sp = sp;
	sp = newsp;
	return old_sp;
}

unsigned long GetSp()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

unsigned long GetGp()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

unsigned long GetCr()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

unsigned long GetSr()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

unsigned long GetSysSp()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long SetConf(unsigned long unk00, unsigned long unk01, unsigned long unk02)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void GetConf(unsigned long* unk00, unsigned long* unk01, unsigned long* unk02)
{
	PSYX_UNIMPLEMENTED();
}

long _get_errno(void)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long _get_error(long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void SystemError(char unk00, long unk01)
{
	PSYX_UNIMPLEMENTED();
}

void SetMem(long unk00)
{
	PSYX_UNIMPLEMENTED();
}

long Krom2RawAdd(unsigned long unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long Krom2RawAdd2(unsigned short unk00)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void _96_init(void)
{
	PSYX_UNIMPLEMENTED();
}

void _96_remove(void)
{
	PSYX_UNIMPLEMENTED();
}

void _boot(void)
{
	PSYX_UNIMPLEMENTED();
}

void ChangeClearPAD(long unk00)
{
	PSYX_UNIMPLEMENTED();
}

void InitCARD(long val)
{
	PSYX_UNIMPLEMENTED();
}

long StartCARD()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long StopCARD()
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void _bu_init()
{
	PSYX_UNIMPLEMENTED();
}

long _card_info(long chan)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long _card_clear(long chan)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long _card_load(long chan)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long _card_auto(long val)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void _new_card()
{
	PSYX_UNIMPLEMENTED();
}

long _card_status(long drv)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long _card_wait(long drv)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

unsigned long _card_chan(void)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long _card_write(long chan, long block, unsigned char *buf)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long _card_read(long chan, long block, unsigned char *buf)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

long _card_format(long chan)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}
