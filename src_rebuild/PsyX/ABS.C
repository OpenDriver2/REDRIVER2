#include "ABS.H"

// this is definitely NOT in psx runtime libs
int fst_abs(int x)
{
	const int mask = x >> 31;
	return (x ^ mask) - mask;
}

int fst_min(int a, int b)
{
	int diff = a - b;
	int dsgn = diff >> 31;
	return b + (diff & dsgn);
}

int fst_max(int a, int b)
{
	int diff = a - b;
	int dsgn = diff >> 31;
	return a - (diff & dsgn);
}