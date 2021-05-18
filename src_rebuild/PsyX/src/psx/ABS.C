#include "psx/abs.h"

// this is definitely NOT in psx runtime libs
int fst_abs(int x)
{
	const int mask = x >> 31;
	return (x ^ mask) - mask;
}