#ifndef UTIL_TIMER_H
#define UTIL_TIMER_H

#ifdef _WIN32
#include <stdint.h>
#else
#include <sys/time.h>
#endif

typedef struct 
{
#ifdef _WIN32
	uint64_t		clockStart;
#else
	struct timeval	timeStart;
#endif // _WIN32
} timerCtx_t;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void Util_InitHPCTimer(timerCtx_t* timer);
extern double Util_GetHPCTime(timerCtx_t* timer, int reset /*= 0*/);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif