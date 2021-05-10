#ifndef DEBRIS_H
#define DEBRIS_H

struct SMASHABLE_OBJECT
{
	int modelIdx;
	char* name;
	int sound;
	int volume;
	int pitch;
};

#define SMOKE_BLACK		1
#define SMOKE_WHITE		2
#define SMOKE_BROWN		3
#define SMOKE_FIRE		4

extern TEXTURE_DETAILS smoke_texture;
extern TEXTURE_DETAILS debris_texture;
extern TEXTURE_DETAILS litter_texture;
extern TEXTURE_DETAILS cop_texture;
extern TEXTURE_DETAILS light_texture;
extern TEXTURE_DETAILS gTyreTexture;
extern TEXTURE_DETAILS flare_texture;
extern TEXTURE_DETAILS sea_texture;
extern TEXTURE_DETAILS bird_texture1;
extern TEXTURE_DETAILS bird_texture2;
extern TEXTURE_DETAILS lensflare_texture;
extern TEXTURE_DETAILS sun_texture;
extern TEXTURE_DETAILS moon_texture;
extern TEXTURE_DETAILS drop_texture;
extern TEXTURE_DETAILS collon_texture;

extern TEXTURE_DETAILS texturePedHead;
extern TEXTURE_DETAILS tannerShadow_texture;

extern TEXTURE_DETAILS lightref_texture;

extern VECTOR dummy;

extern int gNight;
extern u_char gRainCount;
extern int gEffectsTimer;
extern int lightning;
extern int variable_weather;
extern int NoRainIndoors;

extern int main_cop_light_pos;
extern int groundDebrisIndex;
extern CELL_OBJECT ground_debris[16];

extern SMASHABLE_OBJECT smashable[];

extern void InitDebrisNames(); // 0x000337AC
extern void InitDebris(); // 0x00033B9C
extern void InitThunder(); // 0x0003A0BC

extern void PlacePoolForCar(CAR_DATA *cp, CVECTOR *col, int front, int in_car); // 0x00032C10
extern void FindCarLightFade(MATRIX* carToCamera); // 0x00039C68

extern void PreLampStreak(); // 0x00034C6C
extern void AddGroundDebris(); // 0x00033FA8
extern void DrawSmashable_sprites(); // 0x00034138
extern int MoveSmashable_object(); // 0x0003A234

extern void AddSmallStreetLight(CELL_OBJECT *cop, int x, int y, int z, int type); // 0x00034424
extern void AddLightEffect(CELL_OBJECT *cop, int x, int y, int z, int type, int colour); // 0x00034858
extern void AddTrafficLight(CELL_OBJECT* cop, int x, int y, int z, int flag, int yang); // 0x00034F64

extern int damage_lamp(CELL_OBJECT *cop); // 0x00034D1C
extern int damage_object(CELL_OBJECT *cop, VECTOR *velocity); // 0x00034DAC

extern void InitFXPos(VECTOR* vec, SVECTOR* svec, CAR_DATA* cp); // 0x00039C90

extern void SwirlLeaves(CAR_DATA* cp); // 0x00039E54
extern void AddLeaf(VECTOR* Position, int num_leaves, int Type); // 0x00033574

extern void ShowCarlight(SVECTOR *v1, CAR_DATA *cp, CVECTOR *col, short size, short flare_size, TEXTURE_DETAILS *texture, int flag); // 0x000352CC
extern void ShowLight1(VECTOR *v1, CVECTOR *col, short size, TEXTURE_DETAILS *texture); // 0x0003555C
extern void ShowLight(VECTOR *v1, CVECTOR *col, short size, TEXTURE_DETAILS *texture); // 0x00035750
extern void ShowGroundLight(VECTOR *v1, CVECTOR *col, short size); // 0x0003642C
extern void RoundShadow(VECTOR *v1, CVECTOR *col, short size); // 0x00036688

extern void GetSmokeDrift(VECTOR *Wind); // 0x00037158

extern int GetDebrisColour(CAR_DATA* cp); // 0x00039FA8

extern void Setup_Debris(VECTOR *ipos, VECTOR *ispeed, int num_debris, int type); // 0x00037250
extern void Setup_Smoke(VECTOR *ipos, int start_w, int end_w, int SmokeType, int WheelSpeed, VECTOR *Drift, int Exhaust); // 0x00037474
extern void Setup_Sparks(VECTOR *ipos, VECTOR *ispeed, int num_sparks, char SparkType); // 0x00037950

extern void HandleDebris(); // 0x00038008

extern void add_haze(int top_col, int bot_col, short ot_pos); // 0x00038CB4


extern void SetupRain(); // 0x00039DF8
extern void DrawRainDrops(); // 0x00038E08
extern void DoLightning(); // 0x00039B78
extern void RequestThunder(); // 0x0003A120

extern void DoThunder(); // 0x0003A144
extern void DoWeather(int weather); // 0x0003A000



extern void add_haze(int top_col, int bot_col, short ot_pos); // 0x00038CB4


#endif
