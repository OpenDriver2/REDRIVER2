#ifndef PGXP_DEFS_H
#define PGXP_DEFS_H

#ifdef USE_PGXP
#include "PsyX/common/half_float.h"

// Helpful macro
#define PGXP_LOOKUP_VALUE(x, y) (*(u_short*)&(x) | (*(u_short*)&(y) << 16))

//-------------------------------------

// in C++, VERTTYPE can be declared as half
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
typedef half VERTTYPE;
#else
typedef short VERTTYPE;
#endif

typedef struct
{
	float px, py, pz;	// 32 bit values
	VERTTYPE x, y, z;	// 16 bit values (for lookup and backwards compat if not found in cache)
} PGXPVector3D;

typedef struct
{
	uint lookup;
	float px;
	float py;
	float pz;

	float scr_h;
	float ofx;
	float ofy;
} PGXPVData;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern PGXPVector3D g_FP_SXYZ0; // direct access PGXP without table lookup
extern PGXPVector3D g_FP_SXYZ1;
extern PGXPVector3D g_FP_SXYZ2;

extern int g_pgxpVertexIndex;

/* clears PGXP vertex buffer */
void	PGXP_ClearCache();

/* emits new PGXP vertex */
ushort	PGXP_EmitCacheData(PGXPVData* newData);

/* sets Z offset (works like Z bias) */
void	PGXP_SetZOffsetScale(float offset, float scale);

/* searches for vertex with given lookup value */
int		PGXP_GetCacheData(PGXPVData* out, uint lookup, ushort indexhint /* = 0xFFFF */);

/* used by primitive setup */
ushort	PGXP_GetIndex();

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

// special PGXP type
typedef struct {		/* 2D short vector */
	half vx, vy;
	ushort pgxp_index;
} DVECTORF;

#else
typedef short VERTTYPE;
#endif


#endif // PGXP_DEFS