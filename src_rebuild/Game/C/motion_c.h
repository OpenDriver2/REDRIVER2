#ifndef MOTION_C_H
#define MOTION_C_H

extern TEXTURE_DETAILS jeans_texture;
extern TEXTURE_DETAILS arm1_texture;
extern TEXTURE_DETAILS forearm1_texture;
extern TEXTURE_DETAILS chest1_texture;
extern TEXTURE_DETAILS head1_texture;

extern MODEL* gPed1HeadModelPtr;
extern MODEL* gPed2HeadModelPtr;
extern MODEL* gPed3HeadModelPtr;
extern MODEL* gPed4HeadModelPtr;

extern int ThisMotion;

extern void ProcessMotionLump(char *lump_ptr, int lump_size); // 0x00069A38

extern void SetupPedMotionData(LPPEDESTRIAN pPed); // 0x00069AB8
extern void SetupPedestrian(LPPEDESTRIAN pedptr); // 0x00069B6C

extern void StoreVertexLists(); // 0x0006594C

extern void DrawCiv(LPPEDESTRIAN pPed); // 0x000670CC
extern void SetSkelModelPointers(int type); // 0x00069AD8

extern void DrawTanner(LPPEDESTRIAN pPed); // 0x000678D0
extern int DrawCharacter(LPPEDESTRIAN pPed); // 0x00067D44

extern void InitTannerShadow(); // 0x000681EC
extern void TannerShadow(LPPEDESTRIAN pDrawingPed, VECTOR *pPedPos, SVECTOR *pLightPos, CVECTOR *col, short angle); // 0x00068358

#ifndef PSX
// [A] extra parameter for proper sprite shadow support
extern void DoCivHead(LPPEDESTRIAN pPed, SVECTOR *vert1, SVECTOR *vert2, SVECTOR *vJPos); // 0x00068B2C
#else
extern void DoCivHead(LPPEDESTRIAN pPed, SVECTOR *vert1, SVECTOR *vert2); // 0x00068B2C
#endif

#endif
