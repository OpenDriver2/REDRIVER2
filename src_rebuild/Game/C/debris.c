#include "driver2.h"
#include "debris.h"
#include "motion_c.h"
#include "texture.h"
#include "pres.h"
#include "director.h"
#include "pause.h"
#include "sound.h"
#include "main.h"
#include "system.h"
#include "cars.h"
#include "camera.h"
#include "dr2roads.h"
#include "convert.h"
#include "map.h"
#include "mission.h"
#include "draw.h"
#include "models.h"
#include "players.h"
#include "shadow.h"
#include "cosmetic.h"
#include "denting.h"
#include "gamesnd.h"

#include "ASM/rndrasm.h"

#include "INLINE_C.H"
#include "RAND.H"

TEXTURE_DETAILS digit_texture;

TRI_POINT debris_rot1[32]; // offset 0xC0A60
TRI_POINT debris_rot2[32]; // offset 0xC0BE0
TRI_POINT debris_rot3[32]; // offset 0xC0D60
TRI_POINT leaf_rot[32]; // offset 0xC1DC0
TRI_POINT litter_rot[32]; // offset 0xC08D0

TRI_POINT* debris_rot_table[5] = {
	debris_rot1,
	leaf_rot,
	litter_rot,
	debris_rot2,
	debris_rot3,
};

CVECTOR debris_colour[4][31] =
{
	{
		{ 100, 100, 100, 0 },
		{ 214, 214, 244, 0 },
		{ 195, 79, 65, 0 },
		{ 83, 83, 101, 0 },
		{ 197, 142, 80, 0 },
		{ 222, 204, 196, 0 },
		{ 189, 168, 114, 0 },
		{ 203, 180, 121, 0 },
		{ 132, 145, 103, 0 },
		{ 168, 143, 122, 0 },
		{ 107, 107, 107, 0 },
		{ 192, 110, 110, 0 },
		{ 130, 130, 130, 0 },
		{ 101, 129, 145, 0 },
		{ 130, 130, 130, 0 },
		{ 181, 88, 88, 0 },
		{ 130, 105, 83, 0 },
		{ 164, 164, 164, 0 },
		{ 126, 143, 108, 0 },
		{ 140, 163, 181, 0 },
		{ 143, 129, 152, 0 },
		{ 156, 138, 118, 0 },
		{ 190, 190, 190, 0 },
		{ 203, 112, 112, 0 },
		{ 255, 242, 201, 0 },
		{ 167, 145, 90, 0 },
		{ 190, 190, 190, 0 },
		{ 150, 164, 184, 0 },
		{ 102, 102, 102, 0 },
		{ 140, 114, 99, 0 },
		{ 75, 63, 134, 0 },
	}, {
		{ 100, 100, 100, 0 },
		{ 83, 82, 97, 0 },
		{ 138, 179, 201, 0 },
		{ 114, 159, 183, 0 },
		{ 107, 61, 46, 0 },
		{ 162, 120, 76, 0 },
		{ 235, 227, 214, 0 },
		{ 197, 138, 121, 0 },
		{ 159, 169, 131, 0 },
		{ 146, 178, 195, 0 },
		{ 181, 151, 101, 0 },
		{ 230, 191, 139, 0 },
		{ 147, 147, 151, 0 },
		{ 182, 127, 138, 0 },
		{ 160, 165, 127, 0 },
		{ 175, 203, 225, 0 },
		{ 211, 175, 117, 0 },
		{ 209, 167, 118, 0 },
		{ 157, 147, 140, 0 },
		{ 210, 191, 145, 0 },
		{ 155, 185, 148, 0 },
		{ 158, 210, 254, 0 },
		{ 206, 176, 134, 0 },
		{ 236, 173, 117, 0 },
		{ 146, 146, 146, 0 },
		{ 88, 103, 128, 0 },
		{ 96, 96, 96, 0 },
		{ 125, 92, 92, 0 },
		{ 184, 174, 155, 0 },
		{ 42, 42, 42, 0 },
		{ 219, 37, 130, 0 },
	}, {
		{ 100, 100, 100, 0 },
		{ 112, 110, 112, 0 },
		{ 230, 212, 214, 0 },
		{ 178, 181, 175, 0 },
		{ 120, 120, 120, 0 },
		{ 102, 101, 115, 0 },
		{ 70, 83, 100, 0 },
		{ 206, 108, 88, 0 },
		{ 220, 136, 107, 0 },
		{ 97, 97, 97, 0 },
		{ 139, 116, 150, 0 },
		{ 173, 173, 173, 0 },
		{ 104, 133, 173, 0 },
		{ 224, 196, 139, 0 },
		{ 108, 146, 141, 0 },
		{ 82, 82, 82, 0 },
		{ 123, 123, 123, 0 },
		{ 140, 67, 67, 0 },
		{ 103, 92, 121, 0 },
		{ 219, 192, 148, 0 },
		{ 160, 185, 195, 0 },
		{ 158, 173, 130, 0 },
		{ 183, 183, 183, 0 },
		{ 126, 98, 84, 0 },
		{ 126, 125, 156, 0 },
		{ 36, 74, 203, 0 },
		{ 105, 105, 105, 0 },
		{ 162, 179, 183, 0 },
		{ 102, 130, 162, 0 },
		{ 149, 88, 88, 0 },
		{ 119, 145, 129, 0 },
	}, {
		{ 100, 100, 100, 0 },
		{ 153, 149, 150, 0 },
		{ 118, 110, 131, 0 },
		{ 135, 110, 89, 0 },
		{ 191, 102, 66, 0 },
		{ 95, 90, 101, 0 },
		{ 157, 171, 186, 0 },
		{ 203, 184, 132, 0 },
		{ 221, 100, 100, 0 },
		{ 149, 149, 149, 0 },
		{ 100, 118, 145, 0 },
		{ 78, 78, 78, 0 },
		{ 105, 128, 107, 0 },
		{ 203, 94, 94, 0 },
		{ 163, 178, 152, 0 },
		{ 167, 119, 117, 0 },
		{ 117, 139, 142, 0 },
		{ 160, 160, 160, 0 },
		{ 92, 92, 92, 0 },
		{ 229, 144, 136, 0 },
		{ 145, 167, 149, 0 },
		{ 198, 173, 173, 0 },
		{ 137, 163, 175, 0 },
		{ 173, 173, 173, 0 },
		{ 143, 143, 143, 0 },
		{ 218, 198, 154, 0 },
		{ 104, 134, 78, 0 },
		{ 172, 116, 86, 0 },
		{ 155, 170, 185, 0 },
		{ 122, 142, 147, 0 },
		{ 193, 193, 193, 0 }
	}
};

unsigned char grassColour[4][3] = {
	{110, 115, 67},
	{64, 55, 49},
	{91, 104, 56},
	{118, 108, 89}
};


TRI_POINT_LONG debris1_vert =
{
	{-16,0,0},
	{0,-16,0},
	{16,16,0}
};

TRI_POINT_LONG debris2_vert =
{
	{-4,4,0},
	{0,-4,0},
	{4,4,0}
};

TRI_POINT_LONG debris3_vert =
{
	{-80,0,15},
	{0, 0,15},
	{80,0,-15}
};

TRI_POINT_LONG leaf_vert =
{
	{-30,5,7},
	{0,0,10},
	{0,0,-7}
};

TRI_POINT_LONG litter_vert =
{
	{-25,0,25},
	{25,0,25},
	{-25,0,-25}
};

TRI_POINT_LONG* debris_data[5] = {
	&debris1_vert,
	&leaf_vert,
	&litter_vert,
	&debris2_vert,
	&debris3_vert,
};

VECTOR dummy = { 0 };

int gNight = 0;
u_char gRainCount = 30;
int gEffectsTimer = 41;

int NextDamagedPmeter = 0;
int SmashablesHit = 0;
DAMAGED_OBJECT damaged_object[MAX_SMASHED_OBJECTS];

int next_debris = 0;
short debris_alloc[MAX_DEBRIS];

int next_leaf = 0;
short leaf_alloc[MAX_LEAVES];

int next_smoke = 0;
short smoke_alloc[MAX_SMOKE];

int gNextRainDrop = 0;
short gRainAlloc[MAX_RAIN_DROPS];

RAIN_TYPE gRain[MAX_RAIN_DROPS];

char PoolPrimData[16] = {

	0x0,  0x8,  0x2,  0x9,
	0x8,  0x1,  0x9,  0x3,
	0x4,  0xA,  0x6,  0xB,
	0xA,  0x5,  0xB,  0x7
};

int LightSortCorrect = 0;

TEXTURE_DETAILS smoke_texture;
TEXTURE_DETAILS debris_texture;
TEXTURE_DETAILS litter_texture;
TEXTURE_DETAILS cop_texture;
TEXTURE_DETAILS light_texture;
TEXTURE_DETAILS gTyreTexture;
TEXTURE_DETAILS flare_texture;
TEXTURE_DETAILS sea_texture;
TEXTURE_DETAILS bird_texture1;
TEXTURE_DETAILS bird_texture2;
TEXTURE_DETAILS lensflare_texture;
TEXTURE_DETAILS sun_texture;
TEXTURE_DETAILS moon_texture;
TEXTURE_DETAILS drop_texture;
TEXTURE_DETAILS collon_texture;

TEXTURE_DETAILS texturePedHead;
TEXTURE_DETAILS tannerShadow_texture;

TEXTURE_DETAILS lightref_texture;
TEXTURE_DETAILS light_pool_texture;

LAMP_STREAK Known_Lamps[MAX_LAMP_STREAKS];
int NewLamp[MAX_LAMP_STREAKS];
int LightIndex = 0;

int variable_weather = 0;

int gDoLeaves = 1;

SMOKE* smoke_table;
SMOKE smoke[MAX_SMOKE];

SVECTOR leaf_rotvec;
LEAF leaf[MAX_LEAVES];

SVECTOR debris_rotvec;
DEBRIS debris[MAX_DEBRIS];

int StreakCount1 = 0;
int main_cop_light_pos = 0;
int NextDamagedLamp = 0;

CELL_OBJECT ground_debris[MAX_GROUND_DEBRIS];
int groundDebrisIndex = 0;

DAMAGED_LAMP damaged_lamp[MAX_DAMAGED_LAMPS];

MATRIX debris_mat;
MATRIX leaf_mat;

// [D] [T]
void PlacePoolForCar(CAR_DATA *cp, CVECTOR *col, int front, int in_car)
{
	short brightness;
	POLY_FT4 *poly;
	int i;
	SVECTOR s[27];
	SVECTOR sout[27];
	VECTOR s1[12];
	VECTOR mid_position;
	VECTOR toss;
	VECTOR *pos;
	CAR_COSMETICS* car_cos;
	CVECTOR color;
	int Z;
	int sub_level;
	int car_road_height;
	int count;

	pos = (VECTOR*)cp->hd.where.t;
	car_cos = &car_cosmetics[cp->ap.model];

	// [A] there was check that prevented in_car lights in game, but it was working in quick replays...

	if (front) 
	{
		s1[3].vz = -(car_cos->colBox.vz + 50);
		s1[8].vz = s1[3].vz - 1160;
		s1[6].vz = s1[3].vz;
		s1[7].vz = s1[3].vz;

		if (in_car) 
		{
			// slightly shifted vertices to make it look more beautiful
			s1[1].vz = s1[8].vz + 600;
			s1[0].vx = 136;
			s1[1].vx = -344;
			s1[2].vx = -21;
			s1[3].vx = -143;
			s1[4].vx = 344;
			s1[5].vx = -136;
			s1[6].vx = 143;
			s1[7].vx = 21;
			s1[8].vz = s1[8].vz - 400;
			s1[9].vz = s1[3].vz + 10;
			s1[8].vx = -82;
			s1[10].vx = 82;
			s1[9].vx = -82;
			s1[11].vx = 82;
			s1[4].vz = s1[1].vz;
			s1[5].vz = s1[1].vz;
			s1[10].vz = s1[8].vz;
			s1[11].vz = s1[9].vz;

			LightSortCorrect = -800;
			
			sub_level = 3;
		}
		else 
		{
			s1[1].vz = s1[8].vz + 100;
			s1[0].vx = 136;
			s1[1].vx = -344;
			s1[2].vx = -21;
			s1[3].vx = -143;
			s1[4].vx = 344;
			s1[5].vx = -136;
			s1[6].vx = 143;
			s1[7].vx = 21;
			s1[10].vx = 82;
			s1[11].vx = 82;
			s1[8].vx = -82;
			s1[9].vx = -82;
			s1[4].vz = s1[1].vz;
			s1[5].vz = s1[1].vz;
			s1[9].vz = s1[3].vz;
			s1[10].vz = s1[8].vz;
			s1[11].vz = s1[3].vz;

			sub_level = 3;

			if (player[CurrentPlayerView].cameraView == 2 && cp == &car_data[player[CurrentPlayerView].playerCarId])
				LightSortCorrect = -320;
			else
				LightSortCorrect = -200;
		}
	}
	else
	{
		// back light
	
		s1[0].vx = -204;
		s1[1].vx = 204;
		s1[2].vx = -204;
		s1[3].vx = 204;
		s1[3].vz = (car_cos->colBox.vz - 10);
		s1[1].vz = s1[3].vz + 204;

		sub_level = 0;
	}

	s1[0].vz = s1[1].vz;
	s1[2].vz = s1[3].vz;

	SetRotMatrix(&cp->hd.drawCarMat);

	mid_position.vx = 0;
	mid_position.vy = 0;
	mid_position.vz = -500;

	_MatrixRotate(&mid_position);

	mid_position.vx += pos->vx;
	mid_position.vy += pos->vy;
	mid_position.vz += pos->vz;

	car_road_height = MapHeight(&mid_position);
	
	if (sub_level == 3)
		count = 12;
	else
		count = 4;

	// adjust height and poisition for each vertex
	for(i = 0; i < count; i++)
	{
		int temp_y;

		s1[i].vy = 0;
		_MatrixRotate(&s1[i]);

		toss.vx = s1[i].vx + pos->vx;
		toss.vy = s1[i].vy + pos->vy;
		toss.vz = s1[i].vz + pos->vz;

		s[i].vx = toss.vx - camera_position.vx;
		s[i].vz = toss.vz - camera_position.vz;

		temp_y = MapHeight(&toss);

		if (ABS(-temp_y + car_road_height) > 500)
			s[i].vy = -car_road_height - camera_position.vy;
		else
			s[i].vy = -temp_y - camera_position.vy;
	}

	if (FIXEDH(s[0].vy * s[1].vz - s[0].vz * s[1].vy) * s[2].vx +
		FIXEDH(s[0].vz * s[1].vx - s[0].vx * s[1].vz) * s[2].vy + 
		FIXEDH(s[0].vx * s[1].vy - s[0].vy * s[1].vx) * s[2].vz >= 0)
	{
		gte_SetRotMatrix(&inv_camera_matrix);
		gte_SetTransVector(&dummy);

		if (sub_level == 0) 
		{
			gte_ldv3(&s[0], &s[1], &s[2]);
			gte_rtpt();

			gte_stszotz(&Z);

			if (Z > 40)
				Z -= 40;

			if (Z > 49)
			{
				poly = (POLY_FT4 *)current->primptr;

				// [A] Emit poly only after ot z checked
				setPolyFT4(poly);
				setSemiTrans(poly, 1);

				*(ushort*)&poly->u0 = *(ushort*)&light_pool_texture.coords.u0;
				*(ushort*)&poly->u1 = *(ushort*)&light_pool_texture.coords.u1;
				*(ushort*)&poly->u2 = *(ushort*)&light_pool_texture.coords.u2;
				*(ushort*)&poly->u3 = *(ushort*)&light_pool_texture.coords.u3;

				poly->r0 = col->r / 2;
				poly->g0 = col->g / 2;
				poly->b0 = col->b / 2;

				gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

				poly->tpage = light_pool_texture.tpageid | 0x20;
				poly->clut = light_pool_texture.clutid;

				gte_ldv0(&s[3]);
				gte_rtps();
				gte_stsxy(&poly->x3);

				addPrim(current->ot + (Z >> 1), poly);
				current->primptr += sizeof(POLY_FT4);
			}
		}
		else if (sub_level == 3)
		{
			for(i = 0; i < 12; i++)
			{
				gte_ldv0(&s[i]);
				gte_rtv0tr();
				gte_stsv(&sout[i]);
			}

			// draw front light quads
			for(i = 0; i < 4; i++)
			{
				char* VertIdx;
				
				VertIdx = PoolPrimData + i * 4;

				gte_SetRotMatrix(&identity);
				gte_SetTransVector(&dummy);

				if (i & 2)
					brightness = LeftLight + LeftLight * 4;
				else
					brightness = RightLight + RightLight * 4;

				if (brightness)
				{
					int test = col->r * brightness;

					color.r = MIN(255, col->r * brightness >> 4);
					color.g = MIN(255, col->g * brightness >> 4);
					color.b = MIN(255, col->b * brightness >> 4);

					if (i & 1) 
					{
						sQuad(sout + VertIdx[0],
						      sout + VertIdx[2],
						      sout + VertIdx[3],
						      sout + VertIdx[1], &color, LightSortCorrect);
					}
					else
					{
						sQuad(sout + VertIdx[1],
						      sout + VertIdx[3],
						      sout + VertIdx[2],
						      sout + VertIdx[0], &color, LightSortCorrect);
					}
				}
			}
		}

		LightSortCorrect = -10;
	}
}

// [D] [T]
int AllocateLeaf(void)
{
	if (next_leaf < MAX_LEAVES)
		return leaf_alloc[next_leaf++];

	return -1;
}

// [D] [T]
void ReleaseLeaf(short num)
{
	leaf_alloc[--next_leaf] = num;
}

// [D] [T]
void AddLeaf(VECTOR *Position, int num_leaves, int Type)
{
	int num;
	int temprand;
	int i;

	if (gDoLeaves == 0)
		return;

	Position->vy = -Position->vy;
	Position->pad = MapHeight(Position);
	for (i = 0; i < num_leaves; i++)
	{
		num = AllocateLeaf();
		
		if (num == -1)
			return;
	
		LEAF* myleaf = &leaf[num];
		
		temprand = rand();

		myleaf->position.vx = Position->vx + (temprand & 0xfe);
		myleaf->position.vz = Position->vz + (temprand >> 8 & 0xfe);

		if (Type == 1)
			myleaf->position.vy = -Position->vy;
		else
			myleaf->position.vy = -Position->pad;
	
		myleaf->position.pad = Position->pad;

		myleaf->life = 600;
		myleaf->flags = 0x2;
	
		myleaf->direction.vx = 0;
		myleaf->direction.vy = 0;
		myleaf->direction.vz = 0;
		
		myleaf->pos = (temprand >> 7) & 0xff;
		myleaf->step = (temprand & 7) + 1;

		if (Type == 1)
		{
			// tree leaves
			if ((temprand & 3) == 0)
			{
				myleaf->rgb.r = 110;
				myleaf->rgb.g = 112;
				myleaf->rgb.b = 15;
			}
			else if ((temprand & 3) == 1)
			{
				myleaf->rgb.r = 20;
				myleaf->rgb.g = 44;
				myleaf->rgb.b = 0;
			}
			else
			{
				myleaf->rgb.r = 60;
				myleaf->rgb.g = 50;
				myleaf->rgb.b = 30;
			}
		}
		else
		{
			// news, papers etc
			myleaf->rgb.r = myleaf->rgb.g = myleaf->rgb.b = temprand & 0x1f;
		}

		// apply colors
		if (gTimeOfDay == 3)
		{
			*(u_int*)&myleaf->rgb = *(u_int*)&myleaf->rgb >> 2 & 0x3f3f3f3f;
		}
		else if (gWeather == 1 || gWeather == 2)
		{
			*(u_int*)&myleaf->rgb = *(u_int*)&myleaf->rgb >> 1 & 0x7f7f7f7f;
		}

		myleaf->sin_index1 = temprand & 0xfff;
		myleaf->sin_index2 = temprand >> 4 & 0xfff;
		myleaf->sin_addition2 = -(temprand >> 8 & 7);
		myleaf->sin_addition1 = -(temprand & 3);
	
		myleaf->type = Type;
	}
}

// [D] [T]
void SwirlLeaves(CAR_DATA *cp)
{
	int XDiff;
	int ZDiff;
	LEAF *lpLeaf;
	int count;
	VECTOR plpos;

	lpLeaf = leaf;
	plpos.vx = cp->hd.where.t[0];
	plpos.vy = cp->hd.where.t[1];
	plpos.vz = cp->hd.where.t[2];

	if (cp->hd.wheel_speed + 39999U <= 0x1d4be || gDoLeaves == 0 || pauseflag != 0)
		return;

	for (count = 0; count < MAX_LEAVES; count++)
	{
		XDiff = plpos.vx - lpLeaf->position.vx;
		ZDiff = plpos.vz - lpLeaf->position.vz;

		if ((lpLeaf->flags & 0x2) && 
			lpLeaf->position.vy + plpos.vy > -180 &&
			XDiff > -360 && XDiff < 360 && ZDiff > -360 && ZDiff < 360)
		{
			// set lifting direction
			lpLeaf->direction.vy = -25 - (rand() & 0x1f);
			lpLeaf->position.vy -= 1;
		}
		
		lpLeaf++;
	}
}

// [D] [T]
void InitDebrisNames(void)
{
	GetTextureDetails("SMOKE", &smoke_texture);
	GetTextureDetails("DEBRIS", &debris_texture);
	GetTextureDetails("LITTER", &litter_texture);
	GetTextureDetails("COPLIGHT", &cop_texture);
	GetTextureDetails("LIGHT", &light_texture);
	GetTextureDetails("SKID", &gTyreTexture);
	GetTextureDetails("FLARE", &flare_texture);
	GetTextureDetails("SPLASH", &sea_texture);
	GetTextureDetails("SWBIRD1", &bird_texture1);
	GetTextureDetails("SWBIRD2", &bird_texture2);
	GetTextureDetails("LENSFLR", &lensflare_texture);
	GetTextureDetails("SKYSUN", &sun_texture);
	GetTextureDetails("SKYMOON", &moon_texture);
	GetTextureDetails("DROP", &drop_texture);

	GetTextureDetails("DIGIT", &digit_texture);
	SetCLUT16Flags(digit_texture.clutid, 6, 0);

	GetTextureDetails("COLLON", &collon_texture);
	GetTextureDetails("JEANS1", &jeans_texture);
	GetTextureDetails("ARM1", &arm1_texture);
	GetTextureDetails("FOREARM1", &forearm1_texture);
	GetTextureDetails("CHEST1", &chest1_texture);
	GetTextureDetails("LOWHEAD", &head1_texture);
	GetTextureDetails("ADDCAM", &addcam);
	GetTextureDetails("FRAMEADV", &frameadv);
	GetTextureDetails("AUTO", &autocam);
	GetTextureDetails("CHASEC", &chasecar);
	GetTextureDetails("CHOOSECA", &choosecar);
	GetTextureDetails("CLOCK", &clock);
	GetTextureDetails("DELCAM", &delcam);
	GetTextureDetails("EDITCAM", &editcam);
	GetTextureDetails("FIXEDCA", &fixedcam);
	GetTextureDetails("INCAR", &incar);
	GetTextureDetails("LENSCHA", &lenschan);
	GetTextureDetails("LOOKCAR", &lookcar);
	GetTextureDetails("MOVECMP", &movecam);
	GetTextureDetails("MOVECAM", &movecampos);
	GetTextureDetails("OK", &ok);
	GetTextureDetails("PAUSE", &pause);
	GetTextureDetails("PLAYCAM", &playcam);
	GetTextureDetails("PLAYPAU", &playpause);
	GetTextureDetails("SAVE2CA", &save2card);
	GetTextureDetails("RESTREP", &restart);
	GetTextureDetails("HEAD1", &texturePedHead);
	GetTextureDetails("TSHADOW", &tannerShadow_texture);

	texture_is_icon = 0;
	head1_texture.coords.u1 = head1_texture.coords.u0 + 8;
	head1_texture.coords.u3 = head1_texture.coords.u1;

	GetTextureDetails("LIGHTREF", &lightref_texture);
	GetTextureDetails("LIGHT", &light_pool_texture);

	InitButtonTextures();
	InitTannerShadow();
}

// [D] [T]
void InitDebris(void)
{
	int i, j;
	TRI_POINT_LONG temptri;

	texture_is_icon = 0;
	StreakCount1 = 0;
	next_debris = 0;
	next_smoke = 0;
	next_leaf = 0;
	NextDamagedLamp = 0;
	smoke_table = NULL;

	main_cop_light_pos = rand() % 7;

	gDoLeaves = (NumPlayers == 1); // [A] disable in multiplayer (temporarily) due to their flicker

	for (i = 0; i < MAX_LAMP_STREAKS; i++)
	{
		Known_Lamps[i].set = 0;
	}

	for (i = 0; i < MAX_DEBRIS; i++)
	{
		debris_alloc[i] = i;

		debris[i].pos = 0;
		debris[i].flags = 0;
		debris[i].num = i;
	}

	for (i = 0; i < MAX_GROUND_DEBRIS; i++)
	{
		ground_debris[i].type = 0xffff;
	}

	groundDebrisIndex = 0;

	debris_rotvec.vz = 0;
	debris_rotvec.vy = 0;
	debris_rotvec.vx = 0;

	leaf_rotvec.vz = 0;
	leaf_rotvec.vy = 0;
	leaf_rotvec.vx = 0;

	for (i = 0; i < 32; i++)
	{
		RotMatrixXYZ(&debris_mat, &debris_rotvec);
		RotMatrixXYZ(&leaf_mat, &leaf_rotvec);

		debris_rotvec.vx += 128;
		debris_rotvec.vy += 256;
		debris_rotvec.vz += 128;
		leaf_rotvec.vy += 128;

		for (j = 0; j < 5; j++)
		{
			if (j == 1)
				SetRotMatrix(&leaf_mat);
			else
				SetRotMatrix(&debris_mat);

			temptri = *debris_data[j];

			_MatrixRotate((VECTOR *)&temptri.v0);
			_MatrixRotate((VECTOR *)&temptri.v1);
			_MatrixRotate((VECTOR *)&temptri.v2);

			debris_rot_table[j][i].v0.vx = temptri.v0.vx;
			debris_rot_table[j][i].v0.vy = temptri.v0.vy;
			debris_rot_table[j][i].v0.vz = temptri.v0.vz;

			debris_rot_table[j][i].v1.vx = temptri.v1.vx;
			debris_rot_table[j][i].v1.vy = temptri.v1.vy;
			debris_rot_table[j][i].v1.vz = temptri.v1.vz;

			debris_rot_table[j][i].v2.vx = temptri.v2.vx;
			debris_rot_table[j][i].v2.vy = temptri.v2.vy;
			debris_rot_table[j][i].v2.vz = temptri.v2.vz;
		}
	}

	for (i = 0; i < MAX_SMOKE; i++)
	{
		smoke_alloc[i] = i;
		
		smoke[i].pos = 0;
		smoke[i].flags = 0;
		smoke[i].num = i;
	}

	for (i = 0; i < MAX_LEAVES; i++)
	{
		leaf_alloc[i] = i;

		leaf[i].pos = 0;
		leaf[i].flags = 0;
		leaf[i].num = i;
	}

	ClearMem((char*)&damaged_lamp, sizeof(damaged_lamp));

	for (i = 0; i < MAX_SMASHED_OBJECTS; i++)
		damaged_object[i].active = 0;

	LightSortCorrect = -10;
	SmashablesHit = 0;
}

// [D] [T]
int AllocateDebris(void)
{
	if (next_debris < MAX_DEBRIS)
		return debris_alloc[next_debris++];

	return -1;
}

// [D] [T]
void ReleaseDebris(short num)
{
	debris_alloc[--next_debris] = num;
}


// [D] [T]
int AllocateSmoke(void)
{
	if (next_smoke < MAX_SMOKE)
		return smoke_alloc[next_smoke++];

	return -1;
}

// [D] [T]
void ReleaseSmoke(short num)
{
	smoke_alloc[--next_smoke] = num;
}

// [D] [T]
void AddGroundDebris(void)
{
	int seed;
	int number;
	int zbound;
	int xbound;
	int type;
	CELL_OBJECT *cop;
	MODEL *model;
	int count;
	VECTOR Position;

	if (car_data[0].hd.wheel_speed + 99999U <= 0x30d3e)
		return;

	count = 0;
	cop = ground_debris;

	do {
		if (cop->type != 0xffff)
		{
			model = modelpointers[cop->type];

			xbound = ABS(cop->pos.vx - camera_position.vx);
			zbound = ABS(cop->pos.vz - camera_position.vz);

			if (xbound <= 9000 && zbound <= 9000 && (xbound > 7000 || zbound > 7000))
			{
				if (next_leaf >= MAX_LEAVES)
					return;

				seed = rand();

				Position.vy = -cop->pos.vy - 45;
				Position.vx = cop->pos.vx + ((seed & 0x3ff) - 512);
				Position.vz = cop->pos.vz + ((rand() & 0x3ff) - 512);

				number = seed & 7;

				if (model->flags2 & MODEL_FLAG_TREE)
				{
					type = 1;	// ground leaves
				}
				else 
				{
					number = seed & 3;
					type = 2;	// paper
				}

				AddLeaf(&Position, number + 1, type);
			}
		}

		count++;
		cop++;
	} while (count < MAX_GROUND_DEBRIS);
}


extern _pct plotContext;

// [D] [T] [A]
void DrawSmashable_sprites(void)
{
	DAMAGED_OBJECT *dam;
	MODEL *model;
	int count;
	VECTOR pos;
	MATRIX object_matrix;

	dam = damaged_object;
	count = 0;
	do {
		if (dam->active)
		{
			model = modelpointers[dam->cop.type];

			object_matrix.m[0][0] = ONE;
			object_matrix.m[0][1] = 0;
			object_matrix.m[0][2] = 0;

			object_matrix.m[1][0] = 0;
			object_matrix.m[1][1] = ONE;
			object_matrix.m[1][2] = 0;

			object_matrix.m[2][0] = 0;
			object_matrix.m[2][1] = 0;
			object_matrix.m[2][2] = ONE;

			if ((model->shape_flags & SHAPE_FLAG_SMASH_SPRITE) == 0)
				RotMatrixY(dam->rot_speed * dam->damage * 3 & 0xfff, &object_matrix);

			RotMatrixZ(dam->rot_speed * dam->damage & 0xfff, &object_matrix);

			pos.vx = dam->vx - camera_position.vx;
			pos.vy = dam->cop.pos.vy - camera_position.vy;
			pos.vz = dam->cop.pos.vz - camera_position.vz;

			Apply_Inv_CameraMatrix(&pos);

			gte_SetRotMatrix(&object_matrix);
			gte_SetTransVector(&pos);

			pos.vx = dam->vx;
			pos.vy = dam->cop.pos.vy;
			pos.vz = dam->cop.pos.vz;

			SetFrustrumMatrix();

			if (FrustrumCheck(&pos, model->bounding_sphere) != -1)
			{
				if (model->shape_flags & SHAPE_FLAG_SMASH_SPRITE)
				{
					UNIMPLEMENTED();

					if (gWeather - 1U < 2 || gTimeOfDay == 3)
					{
						plotContext.colour = NightAmbient << 0x10 | NightAmbient << 8 | NightAmbient | 0x2c000000;
					}
					else 
					{
						plotContext.colour = 0x2c808080;
					}

					// [A]
					// TODO:
					//current->primptr = Asm_PlotSprite(model, current->primptr, current->ot, 0);
				}
				else
				{
					PlotMDL_less_than_128(model);
				}
			}
		}
	
		count++;
		dam++;
	} while (count < MAX_SMASHED_OBJECTS);
}


// [D] [T]
int MoveSmashable_object(void)
{
	DAMAGED_OBJECT *dam;
	int count;

	dam = damaged_object;
	count = 0;

	do {
		if (dam->active) 
		{
			if (dam->cop.pos.vy < 50 - player[0].pos[1]) 
			{
				dam->vx += dam->velocity.vx;
	
				dam->cop.pos.vy += dam->velocity.vy;
				dam->cop.pos.vz += dam->velocity.vz;

				dam->velocity.vy += 10;

				dam->damage++;
			}
			else 
			{
				dam->active = 0;
			}

		}
		count++;
		dam++;
	} while (count < MAX_SMASHED_OBJECTS);

	return 0;
}

// [D] [T]
void DisplayLightReflections(VECTOR* v1, CVECTOR* col, short size, TEXTURE_DETAILS* texture)
{
	POLY_FT4* poly;
	SVECTOR vert[4];
	CVECTOR thiscol;
	int z;

	if (wetness > 9 && v1->vy > camera_position.vy)
	{
		thiscol.r = col->r * wetness >> 16;
		thiscol.g = col->g * wetness >> 16;
		thiscol.b = col->b * wetness >> 16;
		
		gte_SetTransVector(v1);

		Apply_Inv_CameraMatrix(v1);

		gte_SetTransVector(v1);
		gte_SetRotMatrix(&face_camera);

		vert[0].vx = -size;
		vert[2].vx = -size;
		vert[1].vx = size;
		vert[3].vx = size;

		vert[0].vy = 0;
		vert[0].vz = 0;
		vert[1].vy = 0;
		vert[1].vz = 0;
		vert[2].vy = 0;
		vert[2].vz = 0;
		vert[3].vy = 0;
		vert[3].vz = 0;

		gte_ldv0(&vert[0]);

		gte_rtps();

		gte_stsz(&z);

		if (z >= 150)
		{
			poly = (POLY_FT4*)current->primptr;
			setPolyFT4(poly);
			setSemiTrans(poly, 1);

			gte_stsxy(&poly->x0);

			vert[2].vy = (z >> 3) + 0xfa;
			vert[3].vy = (z >> 3) + 0xfa;

			gte_ldv3(&vert[1], &vert[2], &vert[3]);

			gte_rtpt();

			gte_stsxy3(&poly->x1, &poly->x2, &poly->x3);

			poly->u0 = texture->coords.u0;
			poly->v0 = texture->coords.v0;
			poly->u1 = texture->coords.u1;
			poly->v1 = texture->coords.v1;
			poly->u2 = texture->coords.u2;
			poly->v2 = texture->coords.v2;
			poly->u3 = texture->coords.u3;
			poly->v3 = texture->coords.v3;

			poly->tpage = texture->tpageid | 0x20;
			poly->clut = texture->clutid;

			poly->r0 = thiscol.r;
			poly->g0 = thiscol.g;
			poly->b0 = thiscol.b;

			addPrim(current->ot + (z >> 4), poly);
			current->primptr += sizeof(POLY_FT4);
		}
	}
}

// [D] [T]
int find_lamp_streak(int LampId)
{
	int count;

	for (count = 0; count < MAX_LAMP_STREAKS; count++)
	{
		if (Known_Lamps[count].id == LampId)
		{
			Known_Lamps[count].set = 1;
			return count;
		}
	}

	// allocate new streak
	if (StreakCount1 < MAX_LAMP_STREAKS)
	{
		NewLamp[StreakCount1++] = LampId;
	}

	return -1;
}

// [D] [T]
void AddSmallStreetLight(CELL_OBJECT *cop, int x, int y, int z, int type)
{
	int count;
	DAMAGED_LAMP* dam;
	int halo_size;
	short size;
	short angle;
	VECTOR v1;
	VECTOR v2;
	VECTOR v3;
	SVECTOR pos;
	CVECTOR col;
	CVECTOR col1;
	SVECTOR dpos;

	dam = damaged_lamp;
	col = {140, 140, 140};
	col1 = {45, 45, 45};

	angle = cop->yang;

	if (type == 0) 
	{
		halo_size = 25;
		size = 150;
	}
	else if (type == 1)
	{
		halo_size = 50;
		size = 150;
	}
	else
	{
		halo_size = 100;
		size = 300;
	}

	count = 0;
	do {
		if (dam->index == cop->pos.vx + cop->pos.vz) 
		{
			if (dam->damage > 2) 
				return;

			// do flicker
			col.r = col.g = col.b = (rand() & 0x3f) - (dam->damage * 32 - 90);
			col1.r = col1.g = col1.b = col.r / 2;

			break;
		}

		count++;
		dam++;
	} while (count < 4);

	dpos.vx = cop->pos.vx - camera_position.vx;
	dpos.vy = cop->pos.vy - camera_position.vy;
	dpos.vz = cop->pos.vz - camera_position.vz;

	if (angle & 0xf)
	{
		pos.vx = x;
		pos.vy = y;
		pos.vz = z;

		gte_SetRotMatrix(&matrixtable[angle]);
		gte_ldv0(&pos);

		gte_rtv0();

		gte_stsv(&pos);

		v1.vx = dpos.vx + pos.vx;
		v1.vy = dpos.vy + pos.vy;
		v1.vz = dpos.vz + pos.vz;
	}
	else
	{
		angle >>= 4;

		if (angle == 0)
		{
			v1.vx = dpos.vx + x;
			v1.vz = dpos.vz + z;
		}
		else if (angle == 1)
		{
			v1.vx = dpos.vx + z;
			v1.vz = dpos.vz - x;
		}
		else if (angle == 2)
		{
			v1.vx = dpos.vx - x;
			v1.vz = dpos.vz - z;
		}
		else if (angle == 3)
		{
			v1.vx = dpos.vx - z;
			v1.vz = dpos.vz + x;
		}

		v1.vy = dpos.vy + y;
	}

	v2.vx = v1.vx;
	v2.vz = v1.vz;
	v2.vy = -camera_position.vy - MapHeight((VECTOR*)&cop->pos);

	LightSortCorrect = -30;
	col.cd = 0;

	v3 = v1;

	LightIndex = find_lamp_streak(cop->pos.vx + cop->pos.vz + x); // [A] was pointer.

	if (LightIndex > -1)
		col.cd = 0x60;
	
	ShowLight(&v3, &col, halo_size, &light_texture);
	ShowLight1(&v3, &col1, size, &light_texture);

	DisplayLightReflections(&v2, &col1, halo_size * 2, &lightref_texture);

	LightSortCorrect = -10;
}

// [D] [T]
void AddLightEffect(CELL_OBJECT *cop, int x, int y, int z, int type, int colour)
{
	short yang;
	int angle;
	int size;
	VECTOR v1;
	VECTOR v2;
	VECTOR dpos;
	SVECTOR pos;
	CVECTOR col;

	yang = cop->yang;
	angle = yang;

	dpos.vx = cop->pos.vx - camera_position.vx;
	dpos.vy = cop->pos.vy - camera_position.vy;
	dpos.vz = cop->pos.vz - camera_position.vz;
	
	if (yang & 0xf) 
	{
		pos.vx = x;
		pos.vy = y;
		pos.vz = z;

		gte_SetRotMatrix(&matrixtable[angle]);
		gte_ldv0(&pos);

		gte_rtv0();

		gte_stsv(&pos);

		v1.vx = dpos.vx + pos.vx;
		v1.vy = dpos.vy + pos.vy;
		v1.vz = dpos.vz + pos.vz;
	}
	else
	{
		yang >>= 4;

		if (yang == 0)
		{
			v1.vx = dpos.vx + x;
			v1.vz = dpos.vz + z;
		}
		else if (yang == 1) 
		{
			v1.vx = dpos.vx + z;
			v1.vz = dpos.vz - x;
		}
		else if (yang == 2)
		{
			v1.vx = dpos.vx - x;
			v1.vz = dpos.vz - z;
		}
		else if (yang == 3)
		{
			v1.vx = dpos.vx - z;
			v1.vz = dpos.vz + x;
		}

		v1.vy = dpos.vy + y;
	}

	if (colour == 0)
	{
		col.r = 40;
		col.g = 10;
		col.b = 0;
	}
	else if (colour == 1) 
	{
		col.r = 0;
		col.g = 40;
		col.b = 0;
	}
	else if (colour == 2)
	{
		col.g = 70;
		col.r = 85;
		col.b = 5;
	}
	else if (colour == 3)
	{
		col.g = 40;
		col.b = 35;
		col.r = 40;
	}

	if (type == 0)
	{
		size = 400;
	}
	else if (type == 1)
	{
		size = 300;
	}
	else if (type == 2)
	{
		size = 200;
	}
	else if (type == 3)
	{
		size = 150;
	}

	v2.vx = v1.vx;
	v2.vz = v1.vz;
	v2.vy = -camera_position.vy - MapHeight((VECTOR*)&cop->pos);

	LightSortCorrect = -10;
	col.cd = 0;

	Apply_Inv_CameraMatrix(&v1);

	gte_SetRotMatrix(&identity);
	gte_SetTransVector(&v1);

	ShowLight1(&v1, &col, size, &light_texture);
	DisplayLightReflections(&v2, &col, (size << 0xd) >> 0x10, &lightref_texture);
}

// [D] [T]
void PreLampStreak(void)
{
	int count;

	for (count = 0; count < MAX_LAMP_STREAKS && StreakCount1 > 0; count++)
	{
		if (Known_Lamps[count].set == 0)
		{
			Known_Lamps[count].id = NewLamp[--StreakCount1];
			Known_Lamps[count].clock = FrameCnt - 2;
		}
	}

	for (count = 0; count < MAX_LAMP_STREAKS; count++)
	{
		Known_Lamps[count].set = 0;
		NewLamp[count] = 0;
	}

	StreakCount1 = 0;
}

// [D] [T]
int damage_lamp(CELL_OBJECT *cop)
{
	int old_damage;
	int count;
	DAMAGED_LAMP *dam;

	count = 0;
	dam = damaged_lamp;

	do {

		// [A] slow but works
		if (dam->index == cop->pos.vx + cop->pos.vz)
		{
			old_damage = dam->damage;
			dam->damage++;

			if (old_damage < 3) 
				return ((old_damage + 1) < 3) ^ 1;

			return 0;
		}

		dam++;
		count++;
	} while (count < MAX_DAMAGED_LAMPS);

	// store new cell object
	dam = &damaged_lamp[NextDamagedLamp];
	dam->damage = 0;
	dam->index = cop->pos.vx + cop->pos.vz; // copy

	if (++NextDamagedLamp > MAX_DAMAGED_LAMPS)
		NextDamagedLamp = 0;

	return 0;
}

// [D] [T]
int damage_object(CELL_OBJECT *cop, VECTOR *velocity)
{
	DAMAGED_OBJECT *dam;
	PACKED_CELL_OBJECT *pcop;

	dam = &damaged_object[NextDamagedPmeter];
	SmashablesHit++;
	
	if (NextDamagedPmeter < MAX_SMASHED_OBJECTS-1)
		NextDamagedPmeter++;
	else
		NextDamagedPmeter = 0;

	dam->active = 1;
	dam->damage = 0;

	dam->cop = *cop; // copy

	dam->vx = cop->pos.vx;

	dam->velocity.vx = velocity->vx >> 10;
	dam->velocity.vz = velocity->vz >> 10;

	pcop = pcoplist[cop->pad];
	pcop->value = 0xffff;
	pcop->pos.vy = 1;

	if (dam->velocity.vx < 0)
		dam->velocity.vy = velocity->vx;
	else 
		dam->velocity.vy = -velocity->vx;

	if (dam->velocity.vz < 0)
		dam->velocity.vy += velocity->vz;
	else
		dam->velocity.vy -= velocity->vz;

	dam->velocity.vy /= 2;

	if ((rand() & 1) == 0)
		dam->rot_speed = -dam->velocity.vy;
	else
		dam->rot_speed = dam->velocity.vy;

	if (dam->velocity.vy < -67)
		dam->velocity.vy = -67;

	cop->pos.vx = 0xFD46FEC0;

	return 0;
}

// [D] [T]
void ShowFlare(VECTOR* v1, CVECTOR* col, short size, int rotation)
{
	POLY_FT4* poly;
	SVECTOR vert[4];
	SVECTOR direction;
	MATRIX temp_matrix;
	int z;

	gte_SetTransVector(v1);

	direction.vy = 0;
	direction.vx = 0;
	direction.vz = rotation;

	RotMatrixXYZ(&temp_matrix, &direction);

	gte_SetRotMatrix(&temp_matrix);

	vert[0].vx = -size;
	vert[0].vy = -size;
	vert[0].vz = 0;

	vert[1].vx = -size;
	vert[1].vy = size;
	vert[1].vz = 0;

	vert[2].vx = size;
	vert[2].vy = -size;
	vert[2].vz = 0;

	vert[3].vx = size;
	vert[3].vy = size;
	vert[3].vz = 0;

	gte_ldv3(&vert[0], &vert[1], &vert[2]);

	gte_rtpt();

	poly = (POLY_FT4*)current->primptr;

	poly->u0 = flare_texture.coords.u0;
	poly->v0 = flare_texture.coords.v0;
	poly->u1 = flare_texture.coords.u1;
	poly->v1 = flare_texture.coords.v1;
	poly->u2 = flare_texture.coords.u2;
	poly->v2 = flare_texture.coords.v2 - 1;
	poly->u3 = flare_texture.coords.u3;
	poly->v3 = flare_texture.coords.v3 - 1;

	setPolyFT4(poly);
	setSemiTrans(poly, 1);

	poly->r0 = col->r >> 1;
	poly->g0 = col->g >> 1;
	poly->b0 = col->b >> 1;

	gte_stsz(&z);

	if (z >> 3 > 39)
	{
		z = (z >> 3) + LightSortCorrect;

		if (z < 1)
			z = 1;

		gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);
		gte_ldv0(&vert[3]);

		gte_rtps();
		gte_stsxy(&poly->x3);

		poly->tpage = flare_texture.tpageid | 0x20;
		poly->clut = flare_texture.clutid;

		addPrim(current->ot + z, poly);

		current->primptr += sizeof(POLY_FT4);
	}
}

// [D] [T]
void AddTrafficLight(CELL_OBJECT *cop, int x, int y, int z, int flag, int yang)
{
	int tempfade;
	int r;
	int lDiffAnglesX;
	int lDiffAnglesY;
	int AbsX;
	int AbsY;
	CVECTOR a;
	CVECTOR c;
	VECTOR v1;
	VECTOR v2;

	r = yang & 0xfff;
	v1.vy = (cop->pos.vy - camera_position.vy) + y;
	v1.vx = (cop->pos.vx - camera_position.vx) + FIXEDH(rcossin_tbl[r * 2 + 1] * x + rcossin_tbl[r * 2] * z);
	v1.vz = (cop->pos.vz - camera_position.vz) + FIXEDH(rcossin_tbl[r * 2 + 1] * z - rcossin_tbl[r * 2] * x);

	a.cd = 0;
	
	if (flag & 0x200) 
	{
		a.r = 255;
		a.g = 25;
		a.b = 25;
	}
	else if (flag & 0x400) 
	{
		a.r = 255;
		a.g = 100;
		a.b = 35;
	}
	else if (flag & 0x800)
	{
		a.r = 25;
		a.g = 255;
		a.b = 25;
	}

	lDiffAnglesX = ((camera_angle.vx + 2048) & 0xfff) - 2048;
	AbsX = ABS(lDiffAnglesX);

	lDiffAnglesY = ((-camera_angle.vy & 0xfffU) - yang + 2048 & 0xfff) - 2048;
	AbsY = ABS(lDiffAnglesY);

	c.r = a.r >> 3;
	c.b = a.b >> 3;
	c.g = a.g >> 3;

	v2.vx = v1.vx;
	v2.vz = v1.vz;
	v2.vy = -camera_position.vy - MapHeight((VECTOR*)&cop->pos);

	if (gNight)
		ShowGroundLight(&v2, &c, 300);
	
	if (AbsY < 1000)
	{
		if (AbsX + AbsY < 1000)
		{
			tempfade = 1000 - (AbsX + AbsY);

			if (tempfade < 0)
				tempfade = 0;

			a.r = (a.r * tempfade) >> 10;
			a.b = (a.b * tempfade) >> 10;
			a.g = (a.g * tempfade) >> 10;

			LightSortCorrect = -140;
			LightIndex = find_lamp_streak(cop->pos.vx + cop->pos.vz + x + y); // [A] was pointer.

			if (LightIndex < 0)
				a.cd = 0;
			else
				a.cd = 0x20;

			ShowLight(&v1, &a, 30, &light_texture);

			a.r >>= 1;
			a.b >>= 1;
			a.g >>= 1;

			if (gNight)
				ShowFlare(&v1, &a, 150, lDiffAnglesX + lDiffAnglesY + v1.vx + v1.vz >> 3 & 0x1ffe);

			DisplayLightReflections(&v2, &a, 50, &lightref_texture);
		}

		
		LightSortCorrect = -10;
	}
}

// [D] [T]
void InitFXPos(VECTOR *vec, SVECTOR *svec, CAR_DATA *cp)
{
	SVECTOR svectmp;

	gte_SetRotMatrix(&cp->hd.drawCarMat);
	gte_SetTransVector(vec);

	gte_ldv0(svec);

	gte_rtv0tr();

	gte_stlvnl(vec);
}

int CarLightFadeBack = 0;
int CarLightFadeFront = 0;

// [D] [T]
void FindCarLightFade(MATRIX *carToCamera)
{
	int zz;

	zz = carToCamera->m[2][2] / 4;
	
	CarLightFadeFront = zz - 124;
	CarLightFadeBack = -124 - zz;
}

// [D] [T]
void ShowCarlight(SVECTOR *v1, CAR_DATA *cp, CVECTOR *col, short size, short flare_size, TEXTURE_DETAILS *texture,int flag)
{
	int CarLightFade;
	VECTOR v1t;
	VECTOR v1l;
	CVECTOR flareCol;

	CarLightFade = 255;

	if (flag != 0xFF)
	{
		if (flag & 1)
			CarLightFade = CarLightFadeFront;
		else
			CarLightFade = CarLightFadeBack;

		if (CarLightFade < 0)
			return;
	}
	else
		flag = 0;

	flareCol.r = (col->r * CarLightFade) >> 10;
	flareCol.b = (col->b * CarLightFade) >> 10;
	flareCol.g = (col->g * CarLightFade) >> 10;
	flareCol.cd = flag;

	gte_SetRotMatrix(&cp->hd.drawCarMat);

	v1l.vx = cp->hd.where.t[0] - camera_position.vx;
	v1l.vz = cp->hd.where.t[2] - camera_position.vz;
	v1l.vy = -camera_position.vy - cp->hd.where.t[1];

	InitFXPos(&v1l, v1, cp);

	if (wetness > 9) 
	{
		v1t.vx = v1l.vx;
		v1t.vz = v1l.vz;
		v1t.vy = -camera_position.vy - MapHeight((VECTOR *)cp->hd.where.t);

		DisplayLightReflections(&v1t, &flareCol, flare_size / 2, &lightref_texture);
	}

	col->cd = flag;

	ShowLight(&v1l, &flareCol, size, texture);

	flareCol.r /= 2;
	flareCol.g /= 2;
	flareCol.b /= 2;

	ShowFlare(&v1l, &flareCol, flare_size, (v1->vx + v1->vz) / 4 + (cp->hd.direction - camera_angle.vy) * 2);
}

// [D] [T]
void ShowLight1(VECTOR *v1, CVECTOR *col, short size, TEXTURE_DETAILS *texture)
{
	POLY_FT4* poly;
	SVECTOR vert[4];
	int z;

	poly = (POLY_FT4*)current->primptr;

	vert[0].vz = 0;
	vert[1].vz = 0;
	vert[2].vz = 0;
	vert[3].vz = 0;

	vert[0].vx = -size;
	vert[0].vy = -size;

	vert[1].vx = size;
	vert[1].vy = -size;

	vert[2].vx = -size;
	vert[2].vy = size;

	vert[3].vx = size;
	vert[3].vy = size;

	gte_ldv3(&vert[0], &vert[1], &vert[2]);

	gte_rtpt();

	poly->u0 = (texture->coords).u0;
	poly->v0 = (texture->coords).v0;
	poly->u1 = (texture->coords).u1;
	poly->v1 = (texture->coords).v1;
	poly->u2 = (texture->coords).u2;
	poly->v2 = (texture->coords).v2;
	poly->u3 = (texture->coords).u3;
	poly->v3 = (texture->coords).v3;;

	setPolyFT4(poly);
	SetSemiTrans(poly, 1);

	poly->r0 = col->r;
	poly->g0 = col->g;
	poly->b0 = col->b;

	gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

	gte_stsz(&z);

	if (z > 39)
	{
		gte_ldv0(&vert[3]);

		gte_rtps();

		poly->tpage = texture->tpageid | 0x20;
		poly->clut = texture->clutid;

		z = (z >> 3) + LightSortCorrect;

		if (z < 0) 
			z = 0;

		gte_stsxy(&poly->x3);

		addPrim(current->ot + z, poly);

		current->primptr += sizeof(POLY_FT4);
	}
}

// [D] [T]
void ShowLight(VECTOR *v1, CVECTOR *col, short size, TEXTURE_DETAILS *texture)
{
	int x, y;
	POLY_FT3 *null;
	POLY_G4 *trail;
	POLY_FT4 *poly;
	int i;
	SVECTOR vert[4];
	int z;
	int index;
	SXYPAIR* trails;
	short* clock;
	int tail_width;

	// apply transform
	Apply_Inv_CameraMatrix(v1);

	gte_SetRotMatrix(&identity);
	gte_SetTransVector(v1);

	vert[0].vz = 0;
	vert[1].vz = 0;
	vert[2].vz = 0;
	vert[3].vz = 0;

	vert[0].vx = -size;
	vert[0].vy = -size;

	vert[1].vx = size;
	vert[1].vy = -size;

	vert[2].vx = -size;
	vert[2].vy = size;

	vert[3].vx = size;
	vert[3].vy = size;

	gte_ldv3(&vert[0], &vert[1], &vert[2]);
	gte_rtpt();

	gte_stsz(&z);

	// discard if too close
	if (z < 38)
		return;

	poly = (POLY_FT4 *)current->primptr;
	setPolyFT4(poly);
	setSemiTrans(poly, 1);

	poly->u0 = texture->coords.u0;
	poly->v0 = texture->coords.v0;
	poly->u1 = texture->coords.u1;
	poly->v1 = texture->coords.v1;
	poly->u2 = texture->coords.u2;
	poly->v2 = texture->coords.v2;
	poly->u3 = texture->coords.u3;
	poly->v3 = texture->coords.v3;

	poly->r0 = col->r;
	poly->g0 = col->g;
	poly->b0 = col->b;

	gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

	gte_ldv0(&vert[3]);
	gte_rtps();

	gte_stsxy(&poly->x3);

	poly->tpage = texture->tpageid | 0x20;
	poly->clut = texture->clutid;

	z = (z >> 3) + LightSortCorrect;

	if (z < 0)
		z = 0;

	if (z < 10000)
		tail_width = (10000 - z) >> 0xd;
	else
		tail_width = 0;

	addPrim(current->ot + z, poly);
	current->primptr += sizeof(POLY_FT4);

	
	if (CameraCnt <= 4 || NumPlayers > 1)	// [A] don't draw trails in multiplayer
		return;

	if ((col->cd & 0x20) && gLightsOn) 
	{
		trails = Known_Lamps[LightIndex].light_trails;
		clock = &Known_Lamps[LightIndex].clock;
	}
	else 
	{
		// get light index by flag
		if (col->cd & 0x2) 
			index = 0;
		else if (col->cd & 0x4) 
			index = 1;
		else if (col->cd & 0x8) 
			index = 2;
		else if (col->cd & 0x10) 
			index = 3;
		else
			index = -1;

		if (index == -1)
			return;
		
		trails = car_data[gcar_num].ap.light_trails[index];
		clock = &car_data[gcar_num].ap.old_clock[index];
	}

#ifndef PSX
	x = (poly->x0 + poly->x3) / 2.0f;
	y = (poly->y0 + poly->y3) / 2.0f;
#else
	x = (poly->x0 + poly->x3) / 2;
	y = (poly->y0 + poly->y3) / 2;
#endif
	
	// unified drawing both for car and lamps
	if (CameraChanged == 0 && *clock == (FrameCnt & 0xffffU)-1)
	{
		int old_x, old_y;

		old_x = trails[FrameCnt - 3U & 3].x;
		old_y = trails[FrameCnt - 3U & 3].y;

		trails[FrameCnt & 3].x = x;
		trails[FrameCnt & 3].y = y;

		if (size > 1 && ABS(old_x - x) + ABS(old_y - y) > 1)
		{
			int angle, width;
			VERTTYPE dx, dy;

			trail = (POLY_G4 *)current->primptr;

			setPolyG4(trail);
			setSemiTrans(trail, 1);

			angle = -ratan2(old_x - x,old_y - y) & 0xfff;
			width = ABS(poly->x0 - poly->x3);

#ifdef PSX
			dx = rcossin_tbl[angle * 2 + 1] * width * 3;
			dy = rcossin_tbl[angle * 2] * width * 3;
			
			if (col->cd & 0x40)
			{
				dx >>= 0x10;
				dy >>= 0x10;
			}
			else
			{
				dx >>= 0xf;
				dy >>= 0xf;
			}
			
			trail->x0 = x + dx * tail_width;
			trail->y0 = y + dy * tail_width;

			trail->x1 = x - dx * tail_width;
			trail->y1 = y - dy * tail_width;

			trail->x2 = old_x + dx;
			trail->y2 = old_y + dy;

			trail->x3 = old_x - dx;
			trail->y3 = old_y - dy;
#else
			dx = rcossin_tbl[angle * 2 + 1];
			dy = rcossin_tbl[angle * 2];
			
			if (col->cd & 0x40)
			{
				dx = dx / 40000.0f; // [A] slightly bigger light trail
				dy = dy / 40000.0f;
			}
			else
			{
				dx = dx / 32768.0f;
				dy = dy / 32768.0f;
			}

			trail->x0 = x + dx * width * 3 * tail_width;
			trail->y0 = y + dy * width * 3 * tail_width;

			trail->x1 = x - dx * width * 3 * tail_width;
			trail->y1 = y - dy * width * 3 * tail_width;

			trail->x2 = old_x + dx * width * 3;
			trail->y2 = old_y + dy * width * 3;

			trail->x3 = old_x - dx * width * 3;
			trail->y3 = old_y - dy * width * 3;
#endif

			if (col->cd & 0x18) 
			{
				trail->r0 = trail->r1 = col->r / 2;
				trail->g0 = trail->g1 = col->g / 2;
				trail->b0 = trail->b1 = col->b / 2;
			}
			else 
			{
				trail->r0 = trail->r1 = col->r;
				trail->g0 = trail->g1 = col->g;
				trail->b0 = trail->b1 = col->b;
			}
			
			trail->r2 = trail->r3 = 0;
			trail->g2 = trail->g3 = 0;
			trail->b2 = trail->b3 = 0;

			addPrim(current->ot + z, trail);
			current->primptr += sizeof(POLY_G4);

			null = (POLY_FT3 *)current->primptr;

			setPolyFT3(null);
			null->x0 = -1;
			null->y0 = -1;
			null->x1 = -1;
			null->y1 = -1;
			null->x2 = -1;
			null->y2 = -1;
			null->tpage = 0x20;

			addPrim(current->ot + z, null);
			current->primptr += sizeof(POLY_FT3);
	}
		}
	else
	{
		for (i = 0; i < 4; i++)
		{
			trails[i].x = x;
			trails[i].y = y;
		}
	}

	*clock = FrameCnt;
}

// [D] [T]
void ShowGroundLight(VECTOR *v1, CVECTOR *col, short size)
{
	POLY_FT4 *poly;
	SVECTOR vert[4];
	int z;

#ifndef PSX
	// [A] limit drawing distance to avoid artifacts
	if (ABS(v1->vx) > 32000 || ABS(v1->vz) > 32000)
		return;
#endif

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&dummy);

	// [A] might be incorrect
	vert[0].vx = v1->vx - size;
	vert[0].vy = v1->vy;
	vert[0].vz = v1->vz + size;

	vert[1].vx = v1->vx + size;
	vert[1].vy = v1->vy;
	vert[1].vz = v1->vz + size;

	vert[2].vx = v1->vx - size;
	vert[2].vy = v1->vy;
	vert[2].vz = v1->vz - size;

	vert[3].vx = v1->vx + size;
	vert[3].vy = v1->vy;
	vert[3].vz = v1->vz - size;

	gte_ldv3(&vert[0], &vert[1], &vert[2]);

	gte_rtpt();

	gte_stsz(&z);

	if (z - 150 < 9851) 
	{
		poly = (POLY_FT4 *)current->primptr;

		setPolyFT4(poly);
		setSemiTrans(poly, 1);

		*(ushort*)&poly->u0 = *(ushort*)&light_texture.coords.u0;
		*(ushort*)&poly->u1 = *(ushort*)&light_texture.coords.u1;
		*(ushort*)&poly->u2 = *(ushort*)&light_texture.coords.u2;
		*(ushort*)&poly->u3 = *(ushort*)&light_texture.coords.u3;

		poly->tpage = light_texture.tpageid | 0x20;
		poly->clut = light_texture.clutid;;

		poly->r0 = col->r;
		poly->g0 = col->g;
		poly->b0 = col->b;

		gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

		gte_ldv0(&vert[3]);

		gte_rtps();
		gte_stsxy(&poly->x3);

		addPrim(current->ot + (z >> 3), poly);
		current->primptr += sizeof(POLY_FT4);
	}
}

// [D] [T]
void RoundShadow(VECTOR *v1, CVECTOR *col, short size)
{
	POLY_FT4* poly;
	SVECTOR vert[4];
	int z;

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&dummy);

	vert[0].vz = 0;
	vert[1].vz = 0;
	vert[2].vz = 0;
	vert[3].vz = 0;

	vert[0].vx = v1->vx - size;
	vert[0].vy = v1->vy;
	vert[0].vz = size + v1->vz;

	vert[1].vx = size + v1->vx;
	vert[1].vy = v1->vy;
	vert[1].vz = size + v1->vz;

	vert[2].vx = v1->vx - size;
	vert[2].vy = v1->vy;
	vert[2].vz = v1->vz - size;

	vert[3].vx = size + v1->vx;
	vert[3].vy = v1->vy;
	vert[3].vz = v1->vz - size;

	gte_ldv3(&vert[0], &vert[1], &vert[2]);

	gte_rtpt();

	poly = (POLY_FT4*)current->primptr;

	poly->u0 = light_texture.coords.u0;
	poly->v0 = light_texture.coords.v0;
	poly->u1 = light_texture.coords.u1;
	poly->v1 = light_texture.coords.v1;
	poly->u2 = light_texture.coords.u2;
	poly->v2 = light_texture.coords.v2;
	poly->u3 = light_texture.coords.u3;
	poly->v3 = light_texture.coords.v3;

	poly->tpage = light_texture.tpageid | 0x40;
	poly->clut = light_texture.clutid;

	setPolyFT4(poly);
	setSemiTrans(poly, 1);

	poly->r0 = col->r;
	poly->g0 = col->g;
	poly->b0 = col->b;

	gte_stsz(&z);

	if (z - 150 < 9851)
	{
		gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

		gte_ldv0(&vert[3]);

		gte_rtps();

		gte_stsxy(&poly->x3);

		addPrim(current->ot + (z >> 3), poly);
		current->primptr += sizeof(POLY_FT4);
	}
}

// [D] [T weird and unused]
void DisplayWater(SMOKE *smoke)
{
	POLY_FT4* poly;
	VECTOR v;
	SVECTOR vert[4];
	
	int size;
	int z;
	int z1;
	int z2;
	int z3;
	int z4;

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&dummy);

	size = smoke->start_w;

	vert[0].vx = (smoke->position.vx - size) - camera_position.vx;
	vert[0].vy = 50 - camera_position.vy;
	vert[0].vz = (smoke->position.vz + size) - camera_position.vz;

	vert[1].vx = (smoke->position.vx + size) - camera_position.vx;
	vert[1].vy = 50 - camera_position.vy;
	vert[1].vz = (smoke->position.vz + size) - camera_position.vz;

	vert[2].vx = (smoke->position.vx - size) - camera_position.vx;
	vert[2].vy = 50 - camera_position.vy;
	vert[2].vz = (smoke->position.vz - size) - camera_position.vz;

	vert[3].vx = (smoke->position.vx + size) - camera_position.vx;
	vert[3].vy = 50 - camera_position.vy;
	vert[3].vz = (smoke->position.vz - size) - camera_position.vz;

	poly = (POLY_FT4*)current->primptr;

	gte_ldv3(&vert[0], &vert[1], &vert[2]);

	gte_rtpt();

	setPolyFT4(poly);

	poly->r0 = NightAmbient;
	poly->g0 = NightAmbient;
	poly->b0 = NightAmbient;
	poly->tpage = sea_texture.tpageid;

	gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

	gte_stsz3(&z1, &z2, &z3);

	gte_ldv0(&vert[3]);

	gte_rtps();

	gte_stsxy(&poly->x3);

	poly->u0 = sea_texture.coords.u0;
	poly->v0 = sea_texture.coords.v0;
	poly->u1 = sea_texture.coords.u1;
	poly->v1 = sea_texture.coords.v1;
	poly->u2 = sea_texture.coords.u2;
	poly->v2 = sea_texture.coords.v2;
	poly->u3 = sea_texture.coords.u3;
	poly->v3 = sea_texture.coords.v3;
	poly->clut = sea_texture.clutid;

	gte_stsz(&z4);

	z = z1 + z2 + z3 + z4 >> 5;

	if (z < 9)
		z = 9;

	addPrim(current->ot + z, poly);

	current->primptr += sizeof(POLY_FT4);
}

// [D] [T]
void DisplaySpark(SMOKE *spark)
{
	int colorind;
	POLY_G3 *poly;
	SVECTOR v[3];
	SVECTOR TrailPos;
	int z;

	TrailPos.vx = spark->position.vx - camera_position.vx;
	TrailPos.vy = spark->position.vy - camera_position.vy;
	TrailPos.vz = spark->position.vz - camera_position.vz;

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&dummy);

	v[0].vx = TrailPos.vx;
	v[0].vy = TrailPos.vy;
	v[0].vz = TrailPos.vz;

	v[1].vx = TrailPos.vx + 5;
	v[1].vy = TrailPos.vy;
	v[1].vz = TrailPos.vz + 5;

	v[2].vx = spark->final_tail_pos.vx - camera_position.vx;
	v[2].vy = spark->final_tail_pos.vy - camera_position.vy;
	v[2].vz = spark->final_tail_pos.vz - camera_position.vz;

	poly = (POLY_G3 *)current->primptr;

	gte_ldv3(&v[0], &v[1], &v[2]);
	gte_rtpt();

	setPolyG3(poly);

	if (spark->start_w == 2) 
	{
		colorind = spark->drift.vy * 3 & 3;

		if (gTimeOfDay == 1)
		{
			poly->r0 = grassColour[colorind][0];
			poly->g0 = grassColour[colorind][1];
			poly->b0 = grassColour[colorind][2];

			poly->r1 = grassColour[colorind][0];
			poly->g1 = grassColour[colorind][1];
			poly->b1 = grassColour[colorind][2];

			colorind = (spark->drift.vy + 2U) * 3 & 3;
			poly->r2 = grassColour[colorind][0];
			poly->g2 = grassColour[colorind][1];
			poly->b2 = grassColour[colorind][2];
		}
		else 
		{
			poly->r0 = 0;
			poly->g0 = (spark->transparency >> 3);
			poly->r1 = 0;
			poly->b0 = (spark->transparency >> 4);
			poly->g1 = (spark->transparency >> 3);
			poly->r2 = 12;
			poly->g2 = 4;
			poly->b2 = 4;
			poly->b1 = (spark->transparency >> 4);
		}
	}
	else
	{
		poly->r0 = spark->transparency;
		poly->g0 = spark->transparency;
		poly->b0 = spark->transparency / 2;
		poly->r1 = spark->transparency;
		poly->g1 = spark->transparency;
		poly->b1 = spark->transparency / 2;
		poly->r2 = spark->transparency;
		poly->g2 = 0;
		poly->b2 = 0;
	}

	gte_stsz(&z);

	if (z > 50)
	{
		if (z >> 3 < 9)
			z = 72;

		gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);
		addPrim(current->ot + (z >> 3), poly);

		current->primptr += sizeof(POLY_G3);
	}
}

int SmokeCnt = 0;

// [D] [T]
void GetSmokeDrift(VECTOR *Wind)
{
	static int SinTabIndex1 = 10;
	static int SinTabIndex2 = 0;
	static int SinTabIndex3 = 5;
	static int SinX = 0;
	static int CosX = 0;
	static int WindMagnitude = 0;

	if (SmokeCnt != CameraCnt)
	{
		SmokeCnt = CameraCnt;

		SinTabIndex1 = SinTabIndex1 + 3 & 0xfff;
		SinTabIndex2 = SinTabIndex2 + 5 & 0xfff;
		SinTabIndex3 = SinTabIndex3 + 7 & 0xfff;

		SinX = rcossin_tbl[SinTabIndex1 * 2] + rcossin_tbl[SinTabIndex2 * 2];
		CosX = rcossin_tbl[(SinTabIndex1 + 1024 & 0xfff) * 2] + rcossin_tbl[(SinTabIndex2 + 1024 & 0xfff) * 2];
		WindMagnitude = rcossin_tbl[SinTabIndex3 * 2] >> 0xb;
	}

	Wind->vy = 0;
	Wind->vx = FIXEDH(WindMagnitude * CosX);
	Wind->vz = FIXEDH(-WindMagnitude * SinX);
}

// [D] [T]
void Setup_Debris(VECTOR *ipos, VECTOR *ispeed, int num_debris, int type)
{
	int num;
	int seed;
	int col;
	int i;
	DEBRIS *mydebris;

	col = type >> 0x10;

	for (i = 0; i < num_debris; i++)
	{
		num = AllocateDebris();
		if (num == -1)
			return;

		mydebris = &debris[num];

		mydebris->position.vx = ipos->vx;
		mydebris->position.vy = ipos->vy;
		mydebris->position.vz = ipos->vz;

		if ((type & 0xffffU) < 8)
		{
			seed = rand();
			
			mydebris->step = seed;
			mydebris->rgb.r = debris_colour[GameLevel][col].r;
			mydebris->rgb.g = debris_colour[GameLevel][col].g;
			mydebris->rgb.b = debris_colour[GameLevel][col].b;

			if (gTimeOfDay == 3) 
			{
				mydebris->rgb.r >>= 1;
				mydebris->rgb.g >>= 1;
				mydebris->rgb.b >>= 1;
			}
			
			mydebris->direction.vx = FIXED((ispeed->vx + ((seed & 0x7f) - 64) * num_debris) * 1024);
			mydebris->direction.vy = -FIXED((seed & 0x7f00) * num_debris * 2);
			mydebris->direction.vz = FIXED(ispeed->vz + ((rand() & 0x7fff) - 16384) * num_debris * 2);
		}
		else 
		{
			mydebris->step = 2;
			
			mydebris->rgb.b = 60;
			mydebris->rgb.g = 60;
			mydebris->rgb.r = 60;

			mydebris->direction.vx = FIXED(ispeed->vx);
			mydebris->direction.vy = -FIXED(ispeed->vy);
			mydebris->direction.vz = FIXED(ispeed->vz);
		}

		mydebris->type = type & 7;

		mydebris->life = 128;
		mydebris->flags = 0x2;
		mydebris->pos = i & 0x1f;
	}
}

// [D] [T]
void Setup_Smoke(VECTOR *ipos, int start_w, int end_w, int SmokeType, int WheelSpeed, VECTOR *Drift, int Exhaust)
{
	int num;
	SMOKE *mysmoke;

	num = AllocateSmoke();
	if (num == -1)
		return;

	mysmoke = &smoke[num];

	if (SmokeType == SMOKE_FIRE) 
	{
		mysmoke->position.vx = ipos->vx;
		mysmoke->position.vy = ipos->vy;
		mysmoke->start_w = start_w;
		mysmoke->final_w = end_w;
		mysmoke->position.vz = ipos->vz;
		mysmoke->step = end_w - start_w >> 7 << 2;
		mysmoke->flags = 0x1000 | 0x4 | 0x2;
		mysmoke->life = 20;
		mysmoke->halflife = 10;

		if (WheelSpeed > 200000)
			mysmoke->transparency = (800000 - WheelSpeed >> 0xb);
		else
			mysmoke->transparency = 0xff;

		mysmoke->t_step = end_w - start_w >> 2;
	}
	else if (SmokeType == SMOKE_BLACK)
	{
		if (Exhaust)
		{
			mysmoke->position.vx = ipos->vx + (rand() & 9);
			mysmoke->position.vy = ipos->vy;
			mysmoke->position.vz = ipos->vz + (rand() & 9);
			
			mysmoke->flags = 0x2000 | 0x4 | 0x2;
			mysmoke->transparency = 140;
			mysmoke->t_step = 5;
			mysmoke->step = 1;
		}
		else
		{
			mysmoke->position.vx = ipos->vx;
			mysmoke->position.vy = ipos->vy;
			mysmoke->position.vz = ipos->vz;

			if (WheelSpeed > 200000)
				mysmoke->transparency = (800000 - WheelSpeed >> 0xb);
			else
				mysmoke->transparency = 255;
			
			mysmoke->t_step = end_w - start_w >> 5;
			mysmoke->step = (end_w - start_w) / 128 * 4;
		}

		mysmoke->start_w = start_w;
		mysmoke->final_w = end_w;
		
		mysmoke->flags = 0x2000 | 0x4 | 0x2;
		mysmoke->life = 40;
		mysmoke->halflife = 20;
	}
	else if (SmokeType == SMOKE_WHITE || SmokeType == 5)
	{
		if (Exhaust)
		{
			mysmoke->position.vx = ipos->vx + (rand() & 7);
			mysmoke->position.vy = ipos->vy;
			mysmoke->position.vz = ipos->vz + (rand() & 7);

			mysmoke->flags = 0x4000 | 0x4 | 0x2;
			mysmoke->transparency = 55;
			mysmoke->t_step = 2;
			mysmoke->step = 1;
			mysmoke->life = 24;
		}
		else
		{
			mysmoke->position.vx = ipos->vx + (rand() & 0x3f);
			mysmoke->position.vy = ipos->vy;
			mysmoke->position.vz = ipos->vz + (rand() & 0x3f);
			mysmoke->flags = 0x10 | 0x4 | 0x2;

			if (SmokeType == 5) // UNUSED
			{
				mysmoke->life = 32;
				mysmoke->step = end_w >> 5 << 2;
				mysmoke->t_step = end_w - start_w >> 5;
				mysmoke->transparency = WheelSpeed;
			}
			else
			{
				mysmoke->life = 128;
				mysmoke->step = (end_w - start_w) / 128 * 8;
				mysmoke->t_step = (end_w - start_w >> 6);
				mysmoke->transparency = 80;
			}
		}

		mysmoke->start_w = start_w;
		mysmoke->final_w = end_w;
		mysmoke->halflife = 64;
	}
	else if (SmokeType == 6) // UNUSED
	{
		mysmoke->position.vx = ipos->vx;
		mysmoke->position.vy = ipos->vy;
		mysmoke->position.vz = ipos->vz;
		mysmoke->flags = 0x40 | 0x4 | 0x2;
		mysmoke->transparency = 160;
		mysmoke->step = 20;
		mysmoke->t_step = 5;
		mysmoke->start_w = start_w;
		mysmoke->final_w = end_w;
		mysmoke->life = 78;
		mysmoke->halflife = 32;
	}
	else
	{
		mysmoke->position.vx = ipos->vx + (rand() & 0x3f);
		mysmoke->position.vy = ipos->vy;
		mysmoke->flags = 0x20 | 0x4 | 0x2;
		mysmoke->transparency = 60;
		mysmoke->t_step = 5;
		mysmoke->start_w = start_w;
		mysmoke->final_w = end_w;
		mysmoke->position.vz = ipos->vz + (rand() & 0x3f);

		mysmoke->step = (end_w / 128) * 8;
		mysmoke->life = 128;
		mysmoke->halflife = 64;
	}

	if (Exhaust != 0) 
	{
		mysmoke->drift.vx = Drift->vx;
		mysmoke->drift.vy = Drift->vy;
		mysmoke->drift.vz = Drift->vz;

		mysmoke->drift_change.vx = 0;
		mysmoke->drift_change.vy = 0;
		mysmoke->drift_change.vz = 0;
	}
	else
	{
		mysmoke->drift.vx = 0;
		mysmoke->drift.vy = 0;
		mysmoke->drift.vz = 0;

		if (mysmoke->life < 40 || SmokeType == 4)
		{
			mysmoke->drift_change.vx = 0;
			mysmoke->drift_change.vy = 1;
			mysmoke->drift_change.vz = 0;
		}
		else 
		{
			mysmoke->drift_change.vx = Drift->vx;
			mysmoke->drift_change.vy = Drift->vy;
			mysmoke->drift_change.vz = Drift->vz;
		}
	}
}

// [D] [T]
void Setup_Sparks(VECTOR *ipos, VECTOR *ispeed, int num_sparks, char SparkType)
{
	int num;
	int seed;
	int vz;
	int vy;
	int vx;
	int i;

	SMOKE *mysmoke;

	if (pauseflag != 0 || 0 >= num_sparks)
		return;

	for (i = 0; i < num_sparks; i++)
	{
		num = AllocateSmoke();
	
		if (num == -1)
			return;

		mysmoke = &smoke[num];

		seed = rand();

		mysmoke->position.vx = mysmoke->final_tail_pos.vx = ipos->vx;
		mysmoke->position.vy = mysmoke->final_tail_pos.vy = ipos->vy;
		mysmoke->position.vz = mysmoke->final_tail_pos.vz = ipos->vz;

		mysmoke->pos = (i << 2);
		mysmoke->step = seed & 0x3f;
		
		mysmoke->drift.vx = 2;
		mysmoke->flags = 0x8 | 0x2;

		vx = ispeed->vx;
		vy = ispeed->vy;
		vz = ispeed->vz;

		mysmoke->drift_change.vx = FIXED((vx - 16384 + (seed & 0x7f00)) * 4);
		mysmoke->drift_change.vy = -FIXED((vy + (seed & 0x7f)) * 1024);
		mysmoke->drift_change.vz = FIXED(vz - 64 + (rand() & 0x7f) >> 2);

		if (SparkType == 1)
		{
			mysmoke->life = 10;
			mysmoke->transparency = 200;
			mysmoke->t_step = 2;
			mysmoke->start_w = 0;
		}
		else if (SparkType == 2)
		{
			mysmoke->life = 10;
			mysmoke->transparency = 0xff;
			mysmoke->t_step = 10;
			mysmoke->start_w = 2;
			mysmoke->drift.vy = rand() & 3;
		}
		else
		{
			mysmoke->life = 40;
			mysmoke->transparency = 0xff;
			mysmoke->t_step = 10;
			mysmoke->start_w = 1;
		}
	}
}

// [D] [T]
void DisplayDebris(DEBRIS *debris, char type)
{
	int uVar3;
	TRI_POINT* tv;
	POLY_GT4 *poly1;
	POLY_FT3 *poly;
	SVECTOR v[4];
	VECTOR debrisvec;
	int z;

	debrisvec.vx = debris->position.vx - camera_position.vx;
	debrisvec.vy = debris->position.vy - camera_position.vy;
	debrisvec.vz = debris->position.vz - camera_position.vz;

	if (debrisvec.vx >= -10000 && 
		debrisvec.vz >= -10000 && 
		debrisvec.vx <= 10000 &&
		debrisvec.vz <= 10000)
	{
		tv = debris_rot_table[debris->type & 7] + (debris->pos >> 3 & 0x1fU);

		v[0].vx = tv->v0.vx + debrisvec.vx;
		v[0].vy = tv->v0.vy + debrisvec.vy;
		v[0].vz = tv->v0.vz + debrisvec.vz;

		v[1].vx = tv->v1.vx + debrisvec.vx;
		v[1].vy = tv->v1.vy + debrisvec.vy;
		v[1].vz = tv->v1.vz + debrisvec.vz;

		v[2].vx = tv->v2.vx + debrisvec.vx;
		v[2].vy = tv->v2.vy + debrisvec.vy;
		v[2].vz = tv->v2.vz + debrisvec.vz;

		gte_ldv3(&v[0], &v[1], &v[2]);
		gte_rtpt();

		if (type - 1U < 2) 
		{
			poly1 = (POLY_GT4 *)current->primptr;

			gte_stsxy3(&poly1->x0, &poly1->x1, &poly1->x2);
			gte_stsz(&z);

			if (z > 223)
			{
				*(ushort*)&poly1->u0 = *(ushort*)&litter_texture.coords.u0;
				*(ushort*)&poly1->u1 = *(ushort*)&litter_texture.coords.u1;
				*(ushort*)&poly1->u2 = *(ushort*)&litter_texture.coords.u2;
				*(ushort*)&poly1->u3 = *(ushort*)&litter_texture.coords.u3;

				poly1->clut = litter_texture.clutid;
				poly1->tpage = litter_texture.tpageid;

				v[3].vx = debrisvec.vx - tv->v0.vx;
				v[3].vy = debrisvec.vy - tv->v0.vy;
				v[3].vz = debrisvec.vz - tv->v0.vz;

				gte_ldv0(&v[3]);
				gte_rtps();

				gte_stsxy(&poly1->x3);

				if (type == 2) 
					uVar3 = (debris->rgb.b + combointensity) * 0x10000 | (debris->rgb.g + combointensity) * 0x100 | 0x3c000000 | debris->rgb.r + combointensity;
				else
					uVar3 = debris->rgb.b << 0x10 | debris->rgb.g << 8 | 0x3c000000 | debris->rgb.r;

				*(u_int *)&poly1->r0 = uVar3;
				*(u_int *)&poly1->r2 = uVar3;
				*(u_int *)&poly1->r1 = uVar3 + 0x202020;
				*(u_int *)&poly1->r3 = uVar3 + 0x303030;

				setPolyGT4(poly1);
				addPrim(current->ot + (z >> 3), poly1);
				current->primptr += sizeof(POLY_GT4);
			}
		}
		else
		{
			poly = (POLY_FT3 *)current->primptr;

			gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);
			gte_stsz(&z);

			if (z > 223)
			{
				*(ushort*)&poly->u0 = *(ushort*)&debris_texture.coords.u0;
				*(ushort*)&poly->u1 = *(ushort*)&debris_texture.coords.u1;
				*(ushort*)&poly->u2 = *(ushort*)&debris_texture.coords.u2;

				poly->r0 = debris->rgb.r;
				poly->g0 = debris->rgb.g;
				poly->b0 = debris->rgb.b;

				poly->tpage = debris_texture.tpageid;
				poly->clut = debris_texture.clutid;

				setPolyFT3(poly);
				addPrim(current->ot + (z >> 3), poly);
				current->primptr += sizeof(POLY_FT3);
			}
		}
	}
	else
	{
		debris->life = 1;
	}
}

// [D] [T]
void DisplaySmoke(SMOKE* smoke)
{
	int Z;
	int tmode;
	POLY_FT4* poly;
	VECTOR v;
	SVECTOR smokemesh[4];
	int smoke_z_offset;

	smoke_z_offset = 0;

	v.vx = smoke->position.vx - camera_position.vx;
	v.vy = smoke->position.vy - camera_position.vy;
	v.vz = smoke->position.vz - camera_position.vz;

	if (ABS(v.vx) > 20480 || ABS(v.vz) > 20480)
		return;

	Apply_Inv_CameraMatrix(&v);

	gte_SetTransVector(&v);
	gte_SetRotMatrix(&identity);

	smokemesh[0].vx = -smoke->start_w;
	smokemesh[0].vy = -smoke->start_w;
	smokemesh[0].vz = 0;

	smokemesh[1].vx = smoke->start_w;
	smokemesh[1].vy = -smoke->start_w;
	smokemesh[1].vz = 0;

	smokemesh[2].vx = -smoke->start_w;
	smokemesh[2].vy = smoke->start_w;
	smokemesh[2].vz = 0;

	smokemesh[3].vx = smoke->start_w;
	smokemesh[3].vy = smoke->start_w;
	smokemesh[3].vz = 0;

	poly = (POLY_FT4*)current->primptr;

	gte_ldv3(&smokemesh[0], &smokemesh[1], &smokemesh[2]);
	gte_rtpt();

	tmode = 0x20;

	if (smoke->flags & 0x4000)
	{
		poly->r0 = smoke->transparency;
		poly->g0 = smoke->transparency;
		poly->b0 = smoke->transparency;
	}
	else if (smoke->flags & 0x2000)
	{
		if (gNight)
		{
			poly->r0 = smoke->transparency / 2;
			poly->g0 = smoke->transparency / 2;
			poly->b0 = smoke->transparency / 2;
		}
		else
		{
			poly->r0 = smoke->transparency >> 2;
			poly->g0 = smoke->transparency >> 2;
			poly->b0 = smoke->transparency >> 2;
		}

		tmode = 0x40;
		smoke_z_offset = 17;
	}
	else if (smoke->flags & 0x1000)
	{
		if ((smoke->transparency >> 3) + 50 & 0xff < 60)
			poly->g0 = (smoke->transparency >> 3);
		else
			poly->g0 = smoke->transparency >> 2;

		smoke_z_offset = 18;

		poly->r0 = smoke->transparency;
		poly->b0 = smoke->transparency >> 3;
	}
	else if (smoke->flags & 0x20)
	{
		poly->r0 = smoke->transparency >> 1;
		poly->g0 = smoke->transparency;
		poly->b0 = smoke->transparency + 10;

		tmode = 0x40;
	}
	else if (smoke->flags & 0x40)
	{
		if (gNight == 0)
		{
			poly->r0 = smoke->transparency >> 2;
			poly->g0 = smoke->transparency >> 2;
			poly->b0 = smoke->transparency >> 2;
		}
		else
		{
			poly->r0 = smoke->transparency >> 3;
			poly->g0 = smoke->transparency >> 3;
			poly->b0 = smoke->transparency + 10 >> 3;
		}
	}
	else
	{
		if (gNight == 0)
		{
			poly->r0 = smoke->transparency;
			poly->g0 = smoke->transparency;
			poly->b0 = smoke->transparency + 10;
		}
		else
		{
			poly->r0 = smoke->transparency / 2;
			poly->g0 = smoke->transparency / 2;
			poly->b0 = smoke->transparency + 10 >> 1;
		}

		smoke_z_offset = 25;
	}

	gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

	gte_stsz(&Z);

	gte_ldv0(&smokemesh[3]);
	gte_rtps();

	poly->u0 = smoke_texture.coords.u0;
	poly->v0 = smoke_texture.coords.v0;
	poly->u1 = smoke_texture.coords.u1;
	poly->v1 = smoke_texture.coords.v1;
	poly->u2 = smoke_texture.coords.u2;
	poly->v2 = smoke_texture.coords.v2 - 4; // [A] ???
	poly->u3 = smoke_texture.coords.u3;
	poly->v3 = smoke_texture.coords.v3 - 4; // [A] ???

	poly->tpage = smoke_texture.tpageid | tmode;
	poly->clut = smoke_texture.clutid;

	setPolyFT4(poly);
	setSemiTrans(poly, 1);

	if (Z >> 3 > 0)
	{
		int x, y;

		smoke_z_offset = (Z >> 3) - smoke_z_offset;

		if (smoke_z_offset < 9)
			smoke_z_offset = 9;

		gte_stsxy(&poly->x3);
		addPrim(current->ot + smoke_z_offset, poly);

		// reduce size?
		if ((poly->x1 - poly->x0) / 2 > 100)
		{
			x = (poly->x0 + poly->x3) / 2;
			y = (poly->y0 + poly->y3) / 2;

			// FIXME:  * 0x10000 is needed because clipping issue
			poly->x0 = (y - 50) << 0x10;
			poly->y0 = x - 50;

			poly->x1 = (y - 50) << 0x10;
			poly->y1 = x + 50;

			poly->x2 = (y + 50) << 0x10;
			poly->y2 = x - 50;

			poly->x3 = (y + 50) << 0x10;
			poly->y3 = x + 50;
		}

		current->primptr += sizeof(POLY_FT4);
	}
}

int NoRainIndoors = 0;

// [D] [T]
void HandleDebris(void)
{
	int Height;
	SMOKE *sm;
	DEBRIS *db;
	LEAF *lf;
	int i;
	VECTOR Drift;
	
	GetSmokeDrift(&Drift);

	MoveHubcap();

	SetRotMatrix(&inv_camera_matrix);

	gte_SetTransVector(&dummy);

	db = debris;
	i = next_debris;

	while (i > 0)
	{
		if (db->flags & 0x2)
		{
			DisplayDebris(db, 0);
			
			if (pauseflag == 0)
			{
				if (--db->life == 0 || db->position.vy > 0) 
				{
					db->flags = 0;
					ReleaseDebris(db->num);
				}
				else
				{
					db->position.vx += db->direction.vx;
					db->position.vy += db->direction.vy;
					db->position.vz += db->direction.vz;
					db->pos += db->step;

					if (db->type == 3) 
						db->direction.vy += 1;
					else
						db->direction.vy += 6;
				}
			}
		}
		db++;
		i--;
	}

	lf = leaf;
	i = next_leaf;

	// Move leaves
	while (i > 0)
	{
		if (lf->flags & 0x2) 
		{
			DisplayDebris((DEBRIS *)lf, lf->type);
			
			if (pauseflag == 0)
			{
				if (lf->life == 1) 
				{
					lf->flags = 0;
					ReleaseLeaf(lf->num);
				}
				else
				{
					int sn1, sn2, cs1, cs2;

					GetSmokeDrift(&Drift);

					Height = -(lf->position.pad + 20);

					// first we move debris
					// SwirlLeaves basically changed direction vector
					// in order to lift leaf from ground fast
					if (lf->position.vy < Height)
					{
						lf->position.vx += lf->direction.vx + Drift.vx;
						lf->position.vy += lf->direction.vy + Drift.vy;
						lf->position.vz += lf->direction.vz + Drift.vz;

						lf->pos += lf->step;
						lf->pos &= 0xff;
					}
					else
					{
						lf->position.vy = Height;
					}

					lf->sin_index1 += lf->sin_addition1;
					lf->sin_index2 += lf->sin_addition2;
					lf->sin_index1 &= 0xfff;
					lf->sin_index2 &= 0xfff;

					sn1 = rcossin_tbl[lf->sin_index1 * 2];
					sn2 = rcossin_tbl[lf->sin_index2 * 2];

					cs1 = rcossin_tbl[lf->sin_index1 * 2 + 1];
					cs2 = rcossin_tbl[lf->sin_index2 * 2 + 1];

					// then we compute completely new direction
					lf->direction.vy = ((sn1 + sn2) >> 0xb) + 4;
					lf->direction.vx = ((sn1 + sn2) * 5 >> 0xb);
					lf->direction.vz = ((cs1 + cs2) * 5 >> 0xb);
				}
			}
		}
		lf++;
		i--;
	}

	for (i = 0; i < MAX_SMOKE; i++)
	{
		sm = &smoke[i];

		if (sm->flags & 0x2)
		{
			if (sm->flags & 0x8)
			{
				DisplaySpark(sm);	// yup, smoke particles are sparks too
			}
			else if (sm->flags & 0x4)
			{
				if (sm->flags & 0x8000)
					DisplayWater(sm);	// Really obsolete, water was only a thing in Driver 1
				else
					DisplaySmoke(sm);
			}
		}

		if (sm->flags & 0x2 && pauseflag == 0)
		{
			if (sm->flags & 0x8000) 
			{
				// OBSOLETE DRIVER 1 CODE
				/*
				ROUTE_DATA routeData;
				ROADS_GetRouteData(sm->position.vx - sm->start_w, sm->position.vz - sm->start_w, &routeData);
				ROADS_GetRouteData(sm->position.vx + sm->start_w, sm->position.vz + sm->start_w, &routeData);

				if (sm->start_w < 800 && (modelpointers[routeData.type]->shape_flags & MODEL_FLAG_ALLEY)) 
					sm->start_w += sm->step;
				else*/
					sm->start_w -= sm->step;
			}
			else if (sm->flags & 0x8)
			{
				sm->position.vx += sm->drift_change.vx;
				sm->position.vy += sm->drift_change.vy;
				sm->position.vz += sm->drift_change.vz;
				sm->drift_change.vy += 6;

				if (sm->drift.vx == 0)
				{
					sm->final_tail_pos.vx += sm->drift_change.vx;
					sm->final_tail_pos.vy += sm->drift_change.vy - 12;
					sm->final_tail_pos.vz += sm->drift_change.vz;
				}
				else
				{
					sm->drift.vx -= 1;
				}

				if (sm->position.vy > 0)
				{
					sm->flags = 0;
					ReleaseSmoke(sm->num);
					continue;
				}
			}
			else 
			{
				if (sm->start_w < 800)
					sm->start_w += sm->step;

				sm->position.vx += sm->drift.vx;
				sm->position.vy += sm->drift.vy;
				sm->position.vz += sm->drift.vz;
						
				if (sm->halflife < sm->life)
				{
					sm->drift.vx -= sm->drift_change.vx;
					sm->drift.vy -= sm->drift_change.vy;
					sm->drift.vz -= sm->drift_change.vz;
				}
			}

			if (sm->flags & 0x900C)
			{
				sm->transparency -= sm->t_step;

				if (sm->transparency < 1)
				{
					sm->transparency = 0;
					sm->life = 1;
				}

				if (--sm->life == 0)
				{
					sm->flags = 0;
					ReleaseSmoke(sm->num);
				}
			}
		}
	}

	if (pauseflag == 0)
	{
		main_cop_light_pos++;
		main_cop_light_pos &= 7;
	}

	if (variable_weather)
	{
		static int weather_level = 0;

		weather_level = rcossin_tbl[(CameraCnt & 0xfffU) * 2] + (int)*(short *)((int)rcossin_tbl + (CameraCnt & 0x3ffcU));
		
		if (weather_level < 1)
			gRainCount = -weather_level >> 8;
		else
			gRainCount = weather_level >> 8;

		if (gRainCount > MAX_RAIN_DROPS)
			gRainCount = MAX_RAIN_DROPS;
	}
}

// [D] [T]
void add_haze(int top_col, int bot_col, short ot_pos)
{
	TILE *polys;

	if (top_col > 9 && FastForward == 0)
	{
		polys = (TILE *)current->primptr;

		setTile(polys);

		polys->r0 = top_col;
		polys->g0 = top_col;
		polys->b0 = top_col;

		setSemiTrans(polys, 1);
#ifdef PSX
		polys->x0 = 0;
		polys->w = 320;
#else
		polys->x0 = -500;
		polys->w = 1200;
#endif
		polys->y0 = 0;
		polys->h = 256;
		addPrim(current->ot + ot_pos, polys);

		current->primptr += sizeof(TILE);

		POLY_FT3* null = (POLY_FT3*)current->primptr;
		setPolyFT3(null);

		null->x0 = -1;
		null->y0 = -1;
		null->x1 = -1;
		null->y1 = -1;
		null->x2 = -1;
		null->y2 = -1;
		null->tpage = 0x20;
		addPrim(current->ot + ot_pos, null);

		current->primptr += sizeof(POLY_FT3);
	}
}


// [D] [T]
void SetupRain(void)
{
	gNextRainDrop = 0;

	do {

		gRainAlloc[gNextRainDrop] = gNextRainDrop;
		gRain[gNextRainDrop].oldposition.pad = gNextRainDrop;

		gNextRainDrop++;
	} while (gNextRainDrop < MAX_RAIN_DROPS);

	gNextRainDrop = 0;
}

// [D] [T]
int AllocateRainDrop(void)
{
	if (gNextRainDrop < MAX_RAIN_DROPS)
		return gRainAlloc[gNextRainDrop++];

	return -1;
}

// [D] [T]
void ReleaseRainDrop(int RainIndex)
{
	gNextRainDrop--;
	gRainAlloc[gNextRainDrop] = RainIndex;
}

// [D] [T]
void DisplaySplashes(void)
{
	static u_int rand;

	int d1;
	int d2;
	VECTOR CamGnd;
	VECTOR Gnd1;
	VECTOR Gnd2;
	VECTOR Position;
	CVECTOR col = { 25, 25, 25 };
	int ang;
	int SplashNo, SplashFrac;

	if (pauseflag != 0)
		return;

	if (gRainCount >> 2 > 30)
		SplashNo = 30;
	else
		SplashNo = (gRainCount >> 2);

	SplashFrac = FIXEDH(SplashNo * FrAng * 3);

	gte_SetRotMatrix(&identity); // [A] norot

	CamGnd.vx = camera_position.vx;
	CamGnd.vz = camera_position.vz;
	CamGnd.vy = -camera_position.vy - MapHeight(&CamGnd);

	ang = FrAng - camera_angle.vy & 0xfff;

	Gnd1.vx = rcossin_tbl[ang * 2] + camera_position.vx;
	Gnd1.vz = rcossin_tbl[ang * 2 + 1] + camera_position.vz;

	Gnd1.vx = Gnd1.vx - CamGnd.vx;
	Gnd1.vy = -camera_position.vy - MapHeight(&Gnd1) - CamGnd.vy;
	Gnd1.vz = Gnd1.vz - CamGnd.vz;

	ang = -FrAng - camera_angle.vy & 0xfff;
	Gnd2.vx = rcossin_tbl[ang * 2] + camera_position.vx;
	Gnd2.vz = rcossin_tbl[ang * 2 + 1] + camera_position.vz;

	Gnd2.vx = Gnd2.vx - CamGnd.vx;
	Gnd2.vy = (-camera_position.vy - MapHeight(&Gnd2)) - CamGnd.vy;
	Gnd2.vz = Gnd2.vz - CamGnd.vz;

	while (--SplashFrac >= 0)
	{
		d2 = rand * 0x19660d + 0x3c6ef35f;
		d1 = d2 >> 4 & 0xfff;
		rand = d2 * 0x19660d + 0x3c6ef35f;
		d2 = rand >> 0xe & 0xfff;

		Position.vx = FIXEDH(Gnd1.vx * d1 + Gnd2.vx * d2);
		Position.vy = FIXEDH(Gnd1.vy * d1 + Gnd2.vy * d2) + CamGnd.vy;
		Position.vz = FIXEDH(Gnd1.vz * d1 + Gnd2.vz * d2);

		ShowLight(&Position, &col, 12, &drop_texture);
	}
}

#define RAIN_DROP_SPEED 30		// [A] was 20

// [D] [T]
void DrawRainDrops(void)
{
	int z;
	int Count;
	POLY_GT3 *poly;
	RAIN_TYPE *RainPtr;
	int col;
	int bright;
	SVECTOR v;
	VECTOR drift;

	if (gNextRainDrop == 0)
		return;

	GetSmokeDrift(&drift);

	bright = 70;

	if (bright < 50)
		bright = 50;

	if (gNight != 0)
		bright -= -15;

	col = bright >> 1 | (bright >> 1) << 8;
	col |= col | col << 0x10;

	DisplaySplashes();

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&dummy);

	RainPtr = gRain;
	Count = gNextRainDrop-1;

	poly = (POLY_GT3 *)current->primptr;
	
	while (Count > 0) 
	{
		v.vx = RainPtr->position.vx - camera_position.vx;
		v.vy = RainPtr->position.vy - camera_position.vy;
		v.vz = RainPtr->position.vz - camera_position.vz;

		if (pauseflag) 
		{
			// [A] old position imitation
			// works effectively when player not moving
			gte_ldv0(&v);
			gte_rtps();

			gte_stsxy(&poly->x0);

			v.vy += RAIN_DROP_SPEED;
			v.vx -= drift.vx * 2;
			v.vz -= drift.vz * 2;
		}
		else
		{
			RainPtr->position.vy += RAIN_DROP_SPEED;
			RainPtr->position.vx -= drift.vx * 2;
			RainPtr->position.vz -= drift.vz * 2;

			*(u_int *)&poly->x0 = *(u_int *)&RainPtr->oldposition;
		}

		gte_ldv0(&v);
		gte_rtps();

		*(u_int *)&poly->r2 = col;
		*(u_int *)&poly->r1 = col;
		*(u_int *)&poly->r0 = 0;

		setPolyGT3(poly);
		setSemiTrans(poly, 1);
		
		gte_stsxy(&poly->x2);

		gte_stsz(&z);

		if (z - 151U < 2000 && 
			poly->x2 > -101 && poly->x2 < 421 && 
			poly->y2 > -51 && poly->y2 < 257) 
		{
			if (*(u_int *)&RainPtr->oldposition != 0) 
			{				
				poly->x1 = poly->x2 - ((z >> 10) - 1);
				poly->x2 = poly->x2 + ((z >> 10) - 1);
				poly->y1 = poly->y2;

				*(u_int *)&RainPtr->oldposition = *(u_int *)&poly->x2;

				poly->clut = light_texture.clutid;
				poly->tpage = light_texture.tpageid | 0x20;

				*(ushort *)&poly->u0 = *(ushort *)&light_texture.coords.u0;
				*(ushort *)&poly->u1 = *(ushort *)&light_texture.coords.u1;
				*(ushort *)&poly->u2 = *(ushort *)&light_texture.coords.u2;

				addPrim(current->ot + (z >> 1), poly);
				poly++;
			}
			else
				*(u_int *)&RainPtr->oldposition = *(u_int *)&poly->x2;
		}
		else 
		{
			if(pauseflag == 0)
				ReleaseRainDrop(RainPtr->oldposition.pad);
		}

		RainPtr++;
		Count--;
	}

	current->primptr = (char*)poly;
}


// [D] [T]
void AddRainDrops(void)
{
	static u_int rand;

	int first;
	int RainIndex;
	int tmp;
	int i;
	SVECTOR v;
	ROUTE_DATA routeData;
	int count;
	RAIN_TYPE* rt;

	count = gRainCount;
	first = 1;

	if (pauseflag != 0 || NoRainIndoors != 0)
		return;

	wetness += count / 6;

	if (wetness > 7000)
		wetness = 7000;

	gte_SetRotMatrix(&camera_matrix);
	gte_SetTransVector(&camera_position);

	i = 0;
	while (i < count) 
	{
		i++;

		RainIndex = AllocateRainDrop();

		if (RainIndex < 0)
			return;

		tmp = rand * 0x19660d + 0x3c6ef35f;
		v.vz = (tmp >> 0x14 & 0x1ffU) + 400;
	
		tmp = tmp * 0x19660d + 0x3c6ef35f;
		v.vy = -((tmp >> 0x14) & 0x1ff);
	
		rand = tmp * 0x19660d + 0x3c6ef35f;
		v.vx = ((rand >> 0x14) & 0x1ff) - 256;

		if (v.vz > 512) 
		{
			int depth;
			depth = (v.vz >> 8) + 1;
			
			v.vx *= depth;
			v.vy *= depth;
		}

		gte_ldv0(&v);
		gte_rtv0tr();

		rt = &gRain[RainIndex];

		rt->oldposition.vx = 0;
		rt->oldposition.vy = 0;
		rt->oldposition.vz = 0;
		rt->oldposition.pad = RainIndex;

		gte_stlvnl(&rt->position);

		// OBSOLETE DRIVER 1 CODE
		/*
		if(first)
		{
			ROADS_GetRouteData(rt->position.vx, rt->position.vz, &routeData);

			if (modelpointers[routeData.type]->flags2 & MODEL_FLAG_HASROOF)
				break;
		}
		*/

		first = 0;
	}
}

int lightning = 0;
int LightningTimer = 10;
int ThunderTimer = 0;
static int ThunderDistance = 0;

// [D] [T]
void DoLightning(void)
{
	if (pauseflag != 0)
		return;

	if (LightningTimer < -10) 
		LightningTimer =  rand() & 0xff;
	else 
		LightningTimer--;
	
	if (LightningTimer < 0 && (rand() & 1) == 0)
	{
		RequestThunder();

		if ((rand() & 1) == 0) 
		{
			NightAmbient = NightAmbient << 1;

			if (NightAmbient > 128) 
				NightAmbient = 128;

			lightning = 2;
			return;
		}

		add_haze(50, 0, 4222);
	}

	lightning = 0;
}


// [D] [T]
void InitThunder(void)
{
	ThunderTimer = -1;
	ThunderDistance = rand() % 5000;
}


// [D] [T]
void RequestThunder(void)
{
	ThunderTimer = ThunderDistance >> 8;

	if (ThunderTimer < 1)
		ThunderTimer = 1;
}


// [D] [T]
void DoThunder(void)
{
	if (pauseflag)
		return;

	ThunderDistance = (ThunderDistance + 40) - rand() % 80;

	if (ThunderDistance < 250)
		ThunderDistance = 250;

	if (ThunderDistance > 5000) 
		ThunderDistance = 5000;

	if (ThunderTimer > -1)
	{
		ThunderTimer--;
		
		if(ThunderTimer == 0) 
			StartSound(-1, SOUND_BANK_SFX, 8, -ThunderDistance, (rand() % 2048) + 3072);
	}
}


// [D] [T]
void DoWeather(int weather)
{
	if (weather != 1)
		return;

	if(pauseflag == 0)
	{
		if (gEffectsTimer < 41) 
		{
			if ((FrameCnt & 7U) == 0) 
				gEffectsTimer++;
		}
		else
		{
			AddRainDrops();

			if ((FrameCnt & 7U) == 0)
				gRainCount++;

			if (gRainCount > 35)
				gRainCount = 35;
		}
	}

	DrawRainDrops();
}

// [D] [T]
int GetDebrisColour(CAR_DATA *cp)
{
	int car_model;

	car_model = MissionHeader->residentModels[cp->ap.model];

	if (car_model == 0)
		return 1;

	if(car_model < 8)
		return (car_model-1) * 6 + cp->ap.palette + 7;

	return car_model - 6;
}





