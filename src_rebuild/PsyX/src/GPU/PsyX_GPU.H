#ifndef PSYX_GPU_H
#define PSYX_GPU_H

#include "LIBGTE.H"
#include "LIBGPU.H"
#include "TYPES.H"
#include "COMMON/PGXP_DEFS.H"

#if defined(USE_EXTENDED_PRIM_POINTERS)
extern u_long prim_terminator[2]; // P_TAG with zero length
#else
extern u_long prim_terminator;
#endif

extern int g_splitIndex;
extern DISPENV activeDispEnv;
extern DRAWENV activeDrawEnv;
extern int g_GPUDisabledState;

void ClearSplits();
void ParsePrimitivesToSplits(u_long* p, bool singlePrimitive);
void DrawAllSplits();

#endif