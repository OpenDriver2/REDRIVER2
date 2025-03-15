
#include "driver2.h"
#include "sysclock.h"

tmr_func tmrsub[8];

int timerflag = 0;
int timerhz;
int reentryflag;

int tickset;
int tickval;
int ticks;
int libticks = 0;
int g_currentthread = 1;
int timerevent;

void resettick()
{
	tickset = 0;
	tickval = 0;
	ticks = 0;
}

void initgp()
{
}

void savegp(long* st)
{
}

void restoregp(int gp)
{
}

// process timer interrupt
long tmrint(void)
{
	tmr_func* ptmr;
	int i;
	long _saved_gp;

	savegp(&_saved_gp);

	ptmr = tmrsub;

	ticks++;
	g_currentthread = 1;
	libticks++;

	for (i = 0; i < 8; i++)
	{
		if (tmrsub[i] != NULL)
			(tmrsub[i])();

		ptmr++;
	}
	
	g_currentthread = 0;
	restoregp(_saved_gp);

	return 0;
}

/*
void timedwait(int ms)
{
	int oldTick;

	oldTick = gettick();
	
	while (gettick() - (oldTick + ms) < 0)
		systemtask(0);

	return;
}*/

void addtimer(tmr_func func)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		if (tmrsub[i] == func)	// already added?
			return;

		if (tmrsub[i] == NULL)
		{
			tmrsub[i] = func;
			break;
		}
	}
}

void restoretimer()
{
	DisableEvent(timerevent);
	timerflag = 0;
}

void reinittimer()
{
	EnableEvent(timerevent);
	timerflag = 1;
}

void inittimer(int hz)
{
	if (hz == 0)
		hz = 100;
#ifdef PSX
	EnterCriticalSection();
#endif
	if (timerflag == 0)
	{
		memset((u_char*)&tmrsub, 0, sizeof(tmrsub));
	
		timerevent = OpenEvent(RCntCNT2, 2, RCntMdINTR, tmrint);
		EnableEvent(timerevent);
		timerflag = 1;
	
		//addexit(restoretimer);
	}

	initgp();

	if (hz == 0) {
		trap(0x1c00);
	}
	if ((hz == -1) && (false)) {
		trap(0x1800);
	}
	
	reentryflag = 0;
	timerhz = hz;

	SetRCnt(RCntCNT2, (4233600 / hz), EvSpTRAP);
	StartRCnt(RCntCNT2);

#ifdef PSX
	ExitCriticalSection();
#endif
	resettick();

	//addexit(restoretimer);
}

Clock_tGameClock clock_realTime;
int clock_InterruptStarted;
int generic128HzClock = 0;
int stopClock = 0;

void Clock_MasterInterruptHandler(void)
{
	long oldgp;

	savegp(&oldgp);

	if (stopClock == 0) 
	{
		clock_realTime.time128Hz++;
		generic128HzClock++;

		if ((clock_realTime.time128Hz & 1U) == 0)
		{
			clock_realTime.time64Hz++;

			if ((clock_realTime.time64Hz & 1U) == 0)
			{
				clock_realTime.time32Hz++;
				
				if ((clock_realTime.time32Hz & 1U) == 0) 
				{
					//Input_Update__Fv();
				}
				
				//Input_Store__Fv();
			}
		}
	}

	restoregp(oldgp);
}

void Clock_SystemStartUp(void)
{
	stopClock = 0;
	generic128HzClock = 0;

	if (clock_InterruptStarted == 0)
	{
		clock_InterruptStarted = 1;
	
		addtimer(Clock_MasterInterruptHandler);
		
		clock_realTime.time128Hz = 0;
		clock_realTime.time64Hz = 0;
		clock_realTime.time32Hz = 0;
	}
}