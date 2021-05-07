#ifndef UTIL_TIMER_H
#define UTIL_TIMER_H

#ifdef _WIN32
#include <stdint.h>
#else
#include <sys/time.h>
#endif

struct timerCtx_t
{
#ifdef _WIN32
	uint64_t		clockStart;
#else
	timeval			timeStart;
#endif // _WIN32
};

extern void Util_InitHPCTimer(timerCtx_t* timer);
extern double Util_GetHPCTime(timerCtx_t* timer, int reset = 0);

#endif