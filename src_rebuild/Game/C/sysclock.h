#ifndef SYSCLOCK_H
#define SYSCLOCK_H

struct Clock_tGameClock
{
	int time128Hz;
	int time64Hz;
	int time32Hz;
};

extern Clock_tGameClock clock_realTime;

typedef void (*tmr_func)();

extern void inittimer(int hz);
extern void reinittimer();

extern void restoretimer();
extern void resettick();

extern void addtimer(tmr_func func);

extern void Clock_SystemStartUp(void);


#endif // SYSCLOCK_H