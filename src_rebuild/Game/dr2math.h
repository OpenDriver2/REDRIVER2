#ifndef DR2MATH_H
#define DR2MATH_H

#include <abs.h>

struct MATRIX2
{
	short m[3][3];
	short computed;
	char null[12];
};

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

// Driver 2 math definitions
extern short rcossin_tbl[8192];

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#define ONE				4096
#define ONE_BITS		12

#define PH_ONE			256
#define PH_ONE_BITS		8

// math constants
#define FixHalfRound(x, bits)		(((x) + (1 << (bits-1))) >> bits)

#define	FIXEDH(a)		FixHalfRound(a, ONE_BITS)		// Fixed Half Round number
#define	FIXED(a)		((a) >> ONE_BITS)				// Fixed number (unsigned)

#define RSIN(a)			(rcossin_tbl[((a) & 4095) * 2])
#define RCOS(a)			(rcossin_tbl[((a) & 4095) * 2 + 1])

#define isin(a)			(rcossin_tbl[( ( a ) & 4095) * 2])
#define icos(a)			(rcossin_tbl[((( a )+1024) & 4095) * 2])

#define DIFF_ANGLES( A, B ) \
	(((((B) - (A)) + 2048) & 4095) - 2048)

// Remap a value in the range [A,B] to [C,D].
#define RemapVal( val, A, B, C, D) \
	(C + (D - C) * (val - A) / (B - A))

#define VecCopy(_v, _xyz) \
{ \
	(_v)->vx = (_xyz)->vx; \
	(_v)->vy = (_xyz)->vy; \
	(_v)->vz = (_xyz)->vz; \
}

#define VecNegate(_v) \
{ \
	(_v)->vx = -(_v)->vx; \
	(_v)->vy = -(_v)->vy; \
	(_v)->vz = -(_v)->vz; \
}

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

#define	InitMatrix(_m) \
{ \
	(_m).m[0][0] = ONE; \
	(_m).m[1][0] = 0;   \
	(_m).m[2][0] = 0;   \
	(_m).m[0][1] = 0;   \
	(_m).m[1][1] = ONE; \
	(_m).m[2][1] = 0;   \
	(_m).m[0][2] = 0;   \
	(_m).m[1][2] = 0;   \
	(_m).m[2][2] = ONE; \
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