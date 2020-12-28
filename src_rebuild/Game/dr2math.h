#ifndef DR2MATH_H
#define DR2MATH_H

#include "ABS.H"

// Driver 2 math definitions
extern short rcossin_tbl[8192];

#define ONE				4096
#define ONE_BITS		12

#define PH_ONE			256
#define PH_ONE_BITS		8

// math constants
#define FixHalfRound(x, bits)		(((x) + (1 << (bits-1))) >> bits)
#define FixFloorSigned(x, bits)		((x) / (1 << bits)) // in disassembly: ((int(x) < 0 ? int(x) + (1 << bits)-1 : int(x)) >> bits)

#define	FIXEDH(a)		FixHalfRound(a, ONE_BITS)		// Fixed Half Round number
#define	FIXED(a)		((a) >> ONE_BITS)				// Fixed number (unsigned)

#define RSIN(a)			rcossin_tbl[(a & 0xFFFU) * 2]
#define RCOS(a)			rcossin_tbl[(a & 0xFFFU) * 2 + 1]

// Remap a value in the range [A,B] to [C,D].
#define RemapVal( val, A, B, C, D) \
	(C + (D - C) * (val - A) / (B - A))

#define SetVec(_v, _x, _y, _z) \
{ \
	(_v)->vx = _x; \
	(_v)->vy = _y; \
	(_v)->vz = _z; \
}

#define VecAdd(vecOut, vecLeft, vecRight) \
{ \
	(vecOut)->vx = (vecLeft)->vx + (vecRight)->vx; \
	(vecOut)->vy = (vecLeft)->vy + (vecRight)->vy; \
	(vecOut)->vz = (vecLeft)->vz + (vecRight)->vz; \
}

#define VecSubtract(vecOut, vecLeft, vecRight) \
{ \
	(vecOut)->vx = (vecLeft)->vx - (vecRight)->vx; \
	(vecOut)->vy = (vecLeft)->vy - (vecRight)->vy; \
	(vecOut)->vz = (vecLeft)->vz - (vecRight)->vz; \
}

#define VecAddEq(vecLeft, vecRight) \
{ \
	(vecLeft)->vx += (vecRight)->vz; \
	(vecLeft)->vy += (vecRight)->vy; \
	(vecLeft)->vz += (vecRight)->vz; \
}

#define VecSubtractEq(vecLeft, vecRight) \
{ \
	(vecLeft)->vx -= (vecRight)->vx; \
	(vecLeft)->vy -= (vecRight)->vy; \
	(vecLeft)->vz -= (vecRight)->vz; \
}

#define VecDivEq(vecLeft, vecRight) \
{ \
	(vecLeft)->vx /= (vecRight)->vz; \
	(vecLeft)->vy /= (vecRight)->vy; \
	(vecLeft)->vz /= (vecRight)->vz; \
}

#define VecMulEq(vecLeft, vecRight) \
{ \
	(vecLeft)->vx *= (vecRight)->vx; \
	(vecLeft)->vy *= (vecRight)->vy; \
	(vecLeft)->vz *= (vecRight)->vz; \
}

#define numberOf(sexToys)					(sizeof(sexToys) / sizeof(sexToys[0]))

#ifndef MIN
#define MIN(a,b)	fst_min(a,b)
#endif

#ifndef MAX
#define MAX(a,b)	fst_max(a,b)
#endif

inline int fst_min(int a, int b)
{
	int diff = a - b;
	int dsgn = diff >> 31;
	return b + (diff & dsgn);
}

inline int fst_max(int a, int b)
{
	int diff = a - b;
	int dsgn = diff >> 31;
	return a - (diff & dsgn);
}

#endif // DR2MATH_H