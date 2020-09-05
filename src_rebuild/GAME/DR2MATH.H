#ifndef DR2MATH_H
#define DR2MATH_H

// Driver 2 math definitions

#define ONE				4096
#define PH_ONE			256

#define ONE_BITS		12
#define ONE_BIT			(1 << ONE_BITS)

#define PH_ONE_BITS		8
#define PH_ONE_BIT		(1 << PH_ONE_BITS)

// math constants
#if 0

// DO NOT USE IT unless you don't care about replays and chases
#define	FIXED(a)		(int(a) / ONE)
#define	HFIXED(a)		(int(a) / (ONE*2))
#define	PH_FIXED(a)		(int(a) / (PH_ONE))

#else

#define	FIXED(a)		(int(a) + (ONE/2) >> ONE_BITS)
#define	HFIXED(a)		(int(a) + ONE >> (ONE_BITS+1))
#define	PH_FIXED(a)		(int(a) + (PH_ONE) >> PH_ONE_BITS)

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