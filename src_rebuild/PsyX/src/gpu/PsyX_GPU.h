#ifndef PSYX_GPU_H
#define PSYX_GPU_H

#include "psx/libgte.h"
#include "psx/libgpu.h"
#include "psx/types.h"

#include "PsyX/common/pgxp_defs.h"

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern OT_TAG prim_terminator; // P_TAG with zero length

extern int g_splitIndex;
extern DISPENV activeDispEnv;
extern DRAWENV activeDrawEnv;
extern int g_GPUDisabledState;

void ClearSplits();
void ParsePrimitivesToSplits(u_long* p, int singlePrimitive);
void DrawAllSplits();

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif