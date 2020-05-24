#ifndef SHADOW_H
#define SHADOW_H

extern int gShadowTexturePage;
extern int gShadowTextureNum;
extern UV shadowuv;

extern void InitTyreTracks(); // 0x00077524

extern void GetTyreTrackPositions(_CAR_DATA *cp, int player_id); // 0x00075408

extern void SetTyreTrackOldPositions(int player_id); // 0x00077558

extern void AddTyreTrack(int wheel, int tracksAndSmoke, int padid); // 0x00075540

extern void DrawTyreTracks(); // 0x000759E0

extern void InitShadow(); // 0x00075F34

extern void SubdivShadow(long z0, long z1, long z2, long z3, POLY_FT4 *sps); // 0x00076108

extern void PlaceShadowForCar(VECTOR *shadowPoints, int slot, VECTOR *CarPos, int zclip); // 0x000766CC

extern int clipAgainstZ(); // 0x00076A40

extern void clippedPoly(); // 0x00076CD4

extern void sQuad(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3); // 0x00077138


#endif
