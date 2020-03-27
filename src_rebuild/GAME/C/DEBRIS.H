#ifndef DEBRIS_H
#define DEBRIS_H


extern void PlacePoolForCar(struct _CAR_DATA *cp, struct CVECTOR *col, int front); // 0x00032C10

extern int AllocateLeaf(); // 0x00039A90

extern void ReleaseLeaf(short num); // 0x00039D8C

extern void AddLeaf(struct VECTOR *Position, int num_leaves, int Type); // 0x00033574

extern void SwirlLeaves(struct _CAR_DATA *cp); // 0x00039E54

extern void InitDebrisNames(); // 0x000337AC

extern void InitDebris(); // 0x00033B9C

extern int AllocateDebris(); // 0x00039A54

extern void ReleaseDebris(short num); // 0x00039D68

extern int AllocateSmoke(); // 0x00039ACC

extern void ReleaseSmoke(short num); // 0x00039DD4

extern void AddGroundDebris(); // 0x00033FA8

extern void DrawSmashable_sprites(); // 0x00034138

extern int MoveSmashable_object(); // 0x0003A234

extern void AddSmallStreetLight(struct CELL_OBJECT *cop, int x, int y, int z, int type); // 0x00034424

extern void AddLightEffect(struct CELL_OBJECT *cop, int x, int y, int z, int type, int colour); // 0x00034858

extern void PreLampStreak(); // 0x00034C6C

extern int find_lamp_streak(int LampId); // 0x00039B08

extern int damage_lamp(struct CELL_OBJECT *cop); // 0x00034D1C

extern int damage_object(struct CELL_OBJECT *cop, struct VECTOR *velocity); // 0x00034DAC

extern void AddTrafficLight(struct CELL_OBJECT *cop, int x, int y, int z, int flag, int yang); // 0x00034F64

extern void InitFXPos(struct VECTOR *vec, struct SVECTOR *svec, struct _CAR_DATA *cp); // 0x00039C90

extern void FindCarLightFade(struct MATRIX *carToCamera); // 0x00039C68

extern void ShowCarlight(struct SVECTOR *v1, struct _CAR_DATA *cp, struct CVECTOR *col, short size, struct TEXTURE_DETAILS *texture, int flag); // 0x000352CC

extern void ShowLight1(struct VECTOR *v1, struct CVECTOR *col, short size, struct TEXTURE_DETAILS *texture); // 0x0003555C

extern void ShowLight(struct VECTOR *v1, struct CVECTOR *col, short size, struct TEXTURE_DETAILS *texture); // 0x00035750

extern void ShowGroundLight(struct VECTOR *v1, struct CVECTOR *col, short size); // 0x0003642C

extern void RoundShadow(struct VECTOR *v1, struct CVECTOR *col, short size); // 0x00036688

extern void ShowFlare(struct VECTOR *v1, struct CVECTOR *col, short size, int rotation); // 0x000368D8

extern void DisplayWater(struct SMOKE *smoke); // 0x00036B6C

extern void DisplaySpark(struct SMOKE *spark); // 0x00036E18

extern void GetSmokeDrift(struct VECTOR *Wind); // 0x00037158

extern void Setup_Debris(struct VECTOR *ipos, struct VECTOR *ispeed, int num_debris, int type); // 0x00037250

extern void Setup_Smoke(struct VECTOR *ipos, int start_w, int end_w, int SmokeType, int WheelSpeed, struct VECTOR *Drift, int Exhaust); // 0x00037474

extern void Setup_Sparks(struct VECTOR *ipos, struct VECTOR *ispeed, int num_sparks, char SparkType); // 0x00037950

extern void DisplayDebris(struct DEBRIS *debris, char type); // 0x00037B14

extern void HandleDebris(); // 0x00038008

extern void DisplaySmoke(struct SMOKE *smoke); // 0x0003877C

extern void add_haze(int top_col, int bot_col, short ot_pos); // 0x00038CB4

extern void SetupRain(); // 0x00039DF8

extern int AllocateRainDrop(); // 0x0003A2D4

extern void ReleaseRainDrop(int RainIndex); // 0x00039DB0

extern void DrawRainDrops(); // 0x00038E08

extern void AddRainDrops(); // 0x0003919C

extern void DisplaySplashes(); // 0x00039468

extern void DisplayLightReflections(struct VECTOR *v1, struct CVECTOR *col, short size, struct TEXTURE_DETAILS *texture); // 0x000397C0

extern void DoLightning(); // 0x00039B78

extern void InitThunder(); // 0x0003A0BC

extern void RequestThunder(); // 0x0003A120

extern void DoThunder(); // 0x0003A144

extern void DoWeather(int weather); // 0x0003A000

extern int GetDebrisColour(struct _CAR_DATA *cp); // 0x00039FA8


#endif
