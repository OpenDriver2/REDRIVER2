#ifndef SHADOW_H
#define SHADOW_H

extern int gShadowTexturePage;
extern int gShadowTextureNum;
extern UV shadowuv;

extern void InitTyreTracks(); // 0x00077524
extern void InitShadow(); // 0x00075F34

extern void ResetTyreTracks(CAR_DATA* cp, int player_id);

extern void GetTyreTrackPositions(CAR_DATA *cp, int player_id); // 0x00075408
extern void SetTyreTrackOldPositions(int player_id); // 0x00077558
extern void AddTyreTrack(int wheel, int tracksAndSmoke, int player_id, int continuous_track); // 0x00075540
extern void DrawTyreTracks(); // 0x000759E0


extern void SubdivShadow(int z0, int z1, int z2, int z3, POLY_FT4 *sps); // 0x00076108
extern void PlaceShadowForCar(VECTOR *shadowPoints, int subdiv, int zOfs, int flag); // 0x000766CC

extern void sQuad(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3, CVECTOR* light_col, int LightSortCorrect); // 0x00077138


#endif
