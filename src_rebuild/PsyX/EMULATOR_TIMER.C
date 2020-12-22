#ifdef _WIN32
#include <windows.h>
#else
#include <stddef.h>
#endif // _WIN32
#include "EMULATOR_TIMER.H"

void Emulator_InitHPCTimer(timerCtx_t* timer)
{
#ifdef _WIN32
	QueryPerformanceCounter(&timer->clockStart);
#else
	gettimeofday(&timer->timeStart, NULL);
#endif // _WIN32

}

double Emulator_GetHPCTime(timerCtx_t* timer, int reset)
{
#ifdef _WIN32
	LARGE_INTEGER curr;

	QueryPerformanceFrequency(&timer->performanceFrequency);
	QueryPerformanceCounter(&curr);

	double value = double(curr.QuadPart - timer->clockStart.QuadPart) / double(timer->performanceFrequency.QuadPart);

	if (reset)
		timer->clockStart = curr;
#else
	timeval curr;

	gettimeofday(&curr, NULL);

	double value = (float(curr.tv_sec - timer->timeStart.tv_sec) + 0.000001f * float(curr.tv_usec - timer->timeStart.tv_usec));

	if (reset)
		timer->timeStart = curr;
#endif // _WIN32

	return value;
}