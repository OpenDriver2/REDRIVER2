#ifndef PSYX_GPU_H
#define PSYX_GPU_H

#include "libgte.h"
#include "libgpu.h"
#include "types.h"
#include "PsyX/common/pgxp_defs.h"

extern OT_TAG prim_terminator; // P_TAG with zero length

extern int g_splitIndex;
extern DISPENV activeDispEnv;
extern DRAWENV activeDrawEnv;
extern int g_GPUDisabledState;

void ClearSplits();
void ParsePrimitivesToSplits(u_long* p, bool singlePrimitive);
void DrawAllSplits();

#endif