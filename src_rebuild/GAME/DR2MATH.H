#ifndef DR2MATH_H
#define DR2MATH_H

// Driver 2 math definitions

#define ONE				4096
#define ONE_BITS		12

#define PH_ONE			256
#define PH_ONE_BITS		8

// math constants
#if 0

// DO NOT USE IT unless you don't care about replays and chases
#define	FIXED(a)		(int(a) / ONE)
#define	HFIXED(a)		(int(a) / (ONE*2))
#define	PH_FIXED(a)		(int(a) / (PH_ONE))

#else

#define FixHalfRound(x, bits)		(int(x) + (1 << (bits-1)) >> bits)
#define FixFloorSigned(x, bits)		((int(x) < 0 ? int(x) + (1 << bits)-1 : int(x)) >> bits)

#define	FIXEDH(a)		FixHalfRound(a, ONE_BITS)		// Fixed Half Round number
#define	FIXED(a)		(int(a) >> ONE_BITS)			// Fixed number

#endif

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


#endif // DR2MATH_H