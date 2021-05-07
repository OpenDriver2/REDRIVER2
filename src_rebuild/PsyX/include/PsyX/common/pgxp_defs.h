#ifndef PGXP_DEFS_H
#define PGXP_DEFS_H

#ifdef USE_PGXP
#include "PsyX/common/half_float.h"

typedef half VERTTYPE;
#define PGXP_LOOKUP_VALUE(x, y) (x.sh | (y.sh << 16))

struct PGXPVector3D
{
	float px, py, pz;	// 32 bit values
	VERTTYPE x, y, z;	// 16 bit values (for lookup and backwards compat if not found in cache)
};

extern PGXPVector3D g_FP_SXYZ0; // direct access PGXP without table lookup
extern PGXPVector3D g_FP_SXYZ1;
extern PGXPVector3D g_FP_SXYZ2;

struct PGXPVData
{
	uint lookup;
	float px;
	float py;
	float pz;

	float scr_h;
	float ofx;
	float ofy;
};

extern int g_pgxpVertexIndex;

void	PGXP_ClearCache();

ushort	PGXP_EmitCacheData(PGXPVData& newData);
void	PGXP_SetZOffsetScale(float offset, float scale);

bool	PGXP_GetCacheData(PGXPVData& out, uint lookup, ushort indexhint);
ushort	PGXP_GetIndex();

// special PGXP type
typedef struct {		/* 2D short vector */
	half vx, vy;
	ushort pgxp_index;
} DVECTORF;

#else
typedef short VERTTYPE;
#endif

#endif // PGXP_DEFS