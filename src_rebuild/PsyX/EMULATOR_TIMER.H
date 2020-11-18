#ifndef EMULATOR_TIMER_H
#define EMULATOR_TIMER_H

#ifdef _WIN32
#include <profileapi.h>
#else
#include <sys/time.h>
#endif

struct timerCtx_t
{
#ifdef _WIN32
	LARGE_INTEGER	performanceFrequency;
	LARGE_INTEGER	clockStart;
#else
	timeval			timeStart;
#endif // _WIN32
};


extern void Emulator_InitHPCTimer(timerCtx_t* timer);
extern double Emulator_GetHPCTime(timerCtx_t* timer, int reset = 0);

#endif // EMULATOR_TIMER_H