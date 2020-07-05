#include "THISDUST.H"
#include "DEBRIS.H"
#include "MOTION_C.H"
#include "TEXTURE.H"
#include "PRES.H"
#include "DIRECTOR.H"
#include "MOTION_C.H"
#include "PAUSE.H"
#include "SOUND.H"
#include "MAIN.H"
#include "SYSTEM.H"
#include "CARS.H"
#include "CAMERA.H"
#include "DR2ROADS.H"
#include "CONVERT.H"
#include "MAP.H"
#include "MISSION.H"
#include "DRAW.H"
#include "MODELS.H"
#include "PLAYERS.H"
#include "SHADOW.H"
#include "COSMETIC.H"
#include "DENTING.H"
#include "ROADBITS.H"

#include "../ASM/ASMTEST.H"

#include "INLINE_C.H"
#include "STRINGS.H"

#include <stdlib.h>

TEXTURE_DETAILS digit_texture;
TEXTURE_DETAILS pause;

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

// debris_colour[4][31]
CVECTOR debris_colour[124] =
{
  { 100u, 100u, 100u, 0u },
  { 214u, 214u, 244u, 0u },
  { 195u, 79u, 65u, 0u },
  { 83u, 83u, 101u, 0u },
  { 197u, 142u, 80u, 0u },
  { 222u, 204u, 196u, 0u },
  { 189u, 168u, 114u, 0u },
  { 203u, 180u, 121u, 0u },
  { 132u, 145u, 103u, 0u },
  { 168u, 143u, 122u, 0u },
  { 107u, 107u, 107u, 0u },
  { 192u, 110u, 110u, 0u },
  { 130u, 130u, 130u, 0u },
  { 101u, 129u, 145u, 0u },
  { 130u, 130u, 130u, 0u },
  { 181u, 88u, 88u, 0u },
  { 130u, 105u, 83u, 0u },
  { 164u, 164u, 164u, 0u },
  { 126u, 143u, 108u, 0u },
  { 140u, 163u, 181u, 0u },
  { 143u, 129u, 152u, 0u },
  { 156u, 138u, 118u, 0u },
  { 190u, 190u, 190u, 0u },
  { 203u, 112u, 112u, 0u },
  { 255u, 242u, 201u, 0u },
  { 167u, 145u, 90u, 0u },
  { 190u, 190u, 190u, 0u },
  { 150u, 164u, 184u, 0u },
  { 102u, 102u, 102u, 0u },
  { 140u, 114u, 99u, 0u },
  { 75u, 63u, 134u, 0u },
  { 100u, 100u, 100u, 0u },
  { 83u, 82u, 97u, 0u },
  { 138u, 179u, 201u, 0u },
  { 114u, 159u, 183u, 0u },
  { 107u, 61u, 46u, 0u },
  { 162u, 120u, 76u, 0u },
  { 235u, 227u, 214u, 0u },
  { 197u, 138u, 121u, 0u },
  { 159u, 169u, 131u, 0u },
  { 146u, 178u, 195u, 0u },
  { 181u, 151u, 101u, 0u },
  { 230u, 191u, 139u, 0u },
  { 147u, 147u, 151u, 0u },
  { 182u, 127u, 138u, 0u },
  { 160u, 165u, 127u, 0u },
  { 175u, 203u, 225u, 0u },
  { 211u, 175u, 117u, 0u },
  { 209u, 167u, 118u, 0u },
  { 157u, 147u, 140u, 0u },
  { 210u, 191u, 145u, 0u },
  { 155u, 185u, 148u, 0u },
  { 158u, 210u, 254u, 0u },
  { 206u, 176u, 134u, 0u },
  { 236u, 173u, 117u, 0u },
  { 146u, 146u, 146u, 0u },
  { 88u, 103u, 128u, 0u },
  { 96u, 96u, 96u, 0u },
  { 125u, 92u, 92u, 0u },
  { 184u, 174u, 155u, 0u },
  { 42u, 42u, 42u, 0u },
  { 219u, 37u, 130u, 0u },
  { 100u, 100u, 100u, 0u },
  { 112u, 110u, 112u, 0u },
  { 230u, 212u, 214u, 0u },
  { 178u, 181u, 175u, 0u },
  { 120u, 120u, 120u, 0u },
  { 102u, 101u, 115u, 0u },
  { 70u, 83u, 100u, 0u },
  { 206u, 108u, 88u, 0u },
  { 220u, 136u, 107u, 0u },
  { 97u, 97u, 97u, 0u },
  { 139u, 116u, 150u, 0u },
  { 173u, 173u, 173u, 0u },
  { 104u, 133u, 173u, 0u },
  { 224u, 196u, 139u, 0u },
  { 108u, 146u, 141u, 0u },
  { 82u, 82u, 82u, 0u },
  { 123u, 123u, 123u, 0u },
  { 140u, 67u, 67u, 0u },
  { 103u, 92u, 121u, 0u },
  { 219u, 192u, 148u, 0u },
  { 160u, 185u, 195u, 0u },
  { 158u, 173u, 130u, 0u },
  { 183u, 183u, 183u, 0u },
  { 126u, 98u, 84u, 0u },
  { 126u, 125u, 156u, 0u },
  { 36u, 74u, 203u, 0u },
  { 105u, 105u, 105u, 0u },
  { 162u, 179u, 183u, 0u },
  { 102u, 130u, 162u, 0u },
  { 149u, 88u, 88u, 0u },
  { 119u, 145u, 129u, 0u },
  { 100u, 100u, 100u, 0u },
  { 153u, 149u, 150u, 0u },
  { 118u, 110u, 131u, 0u },
  { 135u, 110u, 89u, 0u },
  { 191u, 102u, 66u, 0u },
  { 95u, 90u, 101u, 0u },
  { 157u, 171u, 186u, 0u },
  { 203u, 184u, 132u, 0u },
  { 221u, 100u, 100u, 0u },
  { 149u, 149u, 149u, 0u },
  { 100u, 118u, 145u, 0u },
  { 78u, 78u, 78u, 0u },
  { 105u, 128u, 107u, 0u },
  { 203u, 94u, 94u, 0u },
  { 163u, 178u, 152u, 0u },
  { 167u, 119u, 117u, 0u },
  { 117u, 139u, 142u, 0u },
  { 160u, 160u, 160u, 0u },
  { 92u, 92u, 92u, 0u },
  { 229u, 144u, 136u, 0u },
  { 145u, 167u, 149u, 0u },
  { 198u, 173u, 173u, 0u },
  { 137u, 163u, 175u, 0u },
  { 173u, 173u, 173u, 0u },
  { 143u, 143u, 143u, 0u },
  { 218u, 198u, 154u, 0u },
  { 104u, 134u, 78u, 0u },
  { 172u, 116u, 86u, 0u },
  { 155u, 170u, 185u, 0u },
  { 122u, 142u, 147u, 0u },
  { 193u, 193u, 193u, 0u }
};

unsigned char grassColour[4][3] = {
	{0x6E, 0x73, 0x43},
	{0x40, 0x37, 0x31},
	{0x5B, 0x68, 0x38},
	{0x76, 0x6C, 0x59}
};


TRI_POINT_LONG debris1_vert =
{
	{-0xf,0xf,0x0},{0x0,-0xf,0x0},{0xf,0xf,0x0}
};

TRI_POINT_LONG debris2_vert =
{
	{-0x4,0x4,0x0},{0x0,-0x4,0x0},{0x4,0x4,0x0}
};

TRI_POINT_LONG debris3_vert =
{
	{-0x50,0x0,0xf},{0x0, 0x0,0xf},{0x50,0x0,-0xf}
};

TRI_POINT_LONG leaf_vert =
{
	{-0x1e,0x5,0x7},{0x0,0x0,0xa},{0x0,0x0,-0x7}
};

TRI_POINT_LONG litter_vert =
{
	{-0x19,0x0,0x19},{0x19,0x0,0x19},{-0x19,0x0,-0x19}
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
char gRainCount = 30;
int gEffectsTimer = 41;

int NextDamagedPmeter = 0;
int SmashablesHit = 0;
DAMAGED_OBJECT damaged_object[9];

int next_debris = 0;
short debris_alloc[60];

int next_leaf = 0;
short leaf_alloc[50];

int next_smoke = 0;
short smoke_alloc[80];

int gNextRainDrop = 0;
short gRainAlloc[180];

RAIN_TYPE gRain[180];

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

LAMP_STREAK Known_Lamps[21];
int NewLamp[21];
int LightIndex = 0;

int variable_weather = 0;

// decompiled code
// original method signature: 
// void /*$ra*/ PlacePoolForCar(struct _CAR_DATA *cp /*$s4*/, struct CVECTOR *col /*stack 4*/, int front /*$a2*/)
 // line 790, offset 0x00032c10
	/* begin block 1 */
		// Start line: 791
		// Start offset: 0x00032C10
		// Variables:
	// 		int car_road_height; // $s2
	// 		struct SVECTOR s[27]; // stack offset -832
	// 		struct SVECTOR *ptr; // $s1
	// 		struct SVECTOR sout[27]; // stack offset -616
	// 		struct VECTOR s1[12]; // stack offset -400
	// 		struct VECTOR *ptr1; // $s0
	// 		struct POLY_FT4 *poly; // $t0
	// 		struct MATRIX final_matrix; // stack offset -208
	// 		struct VECTOR averagepos; // stack offset -176
	// 		int in_car; // $t0
	// 		int z; // stack offset -48
	// 		int sub_level; // $fp
	// 		int count; // $s3
	// 		struct VECTOR mid_position; // stack offset -160

		/* begin block 1.1 */
			// Start line: 813
			// Start offset: 0x00032CEC
			// Variables:
		// 		short farz; // $a2
		// 		short nearz; // $a0
		/* end block 1.1 */
		// End offset: 0x00032EC0
		// End Line: 898

		/* begin block 1.2 */
			// Start line: 904
			// Start offset: 0x00032ED0
		/* end block 1.2 */
		// End offset: 0x00032F38
		// End Line: 920

		/* begin block 1.3 */
			// Start line: 937
			// Start offset: 0x00032FB4
			// Variables:
		// 		struct VECTOR toss; // stack offset -144
		// 		int temp_y; // $a1
		/* end block 1.3 */
		// End offset: 0x0003306C
		// End Line: 951

		/* begin block 1.4 */
			// Start line: 954
			// Start offset: 0x000330A4
			// Variables:
		// 		long n[4]; // stack offset -128
		/* end block 1.4 */
		// End offset: 0x0003316C
		// End Line: 960

		/* begin block 1.5 */
			// Start line: 967
			// Start offset: 0x000331F0
			// Variables:
		// 		int count; // $s2

			/* begin block 1.5.1 */
				// Start line: 996
				// Start offset: 0x000333C4
				// Variables:
			// 		long z[15]; // stack offset -112

				/* begin block 1.5.1.1 */
					// Start line: 1006
					// Start offset: 0x0003341C
					// Variables:
				// 		char *VertIdx; // $s0

					/* begin block 1.5.1.1.1 */
						// Start line: 1018
						// Start offset: 0x0003349C
					/* end block 1.5.1.1.1 */
					// End offset: 0x0003352C
					// End Line: 1023
				/* end block 1.5.1.1 */
				// End offset: 0x0003352C
				// End Line: 1024
			/* end block 1.5.1 */
			// End offset: 0x0003353C
			// End Line: 1025
		/* end block 1.5 */
		// End offset: 0x0003353C
		// End Line: 1027
	/* end block 1 */
	// End offset: 0x00033544
	// End Line: 1029

	/* begin block 2 */
		// Start line: 1580
	/* end block 2 */
	// End Line: 1581

	/* begin block 3 */
		// Start line: 1590
	/* end block 3 */
	// End Line: 1591

/* WARNING: Could not reconcile some variable overlaps */

//POLY_G3 *spolys = NULL;
//short light_col = 0;

// [D]
void PlacePoolForCar(_CAR_DATA *cp, CVECTOR *col, int front, int in_car)
{
	unsigned char bVar1;
	DB *pDVar3;
	unsigned char uVar4;
	int iVar5;
	int iVar6;
	SVECTOR *pSVar7;
	SVECTOR *pSVar8;
	short sVar9;
	POLY_FT4 *poly;
	int uVar10;
	int uVar11;
	int uVar12;
	VECTOR *pos;
	uint uVar13;
	int iVar14;
	int iVar15;
	int iVar16;
	SVECTOR s[27];
	SVECTOR sout[27];
	VECTOR s1[12];
	MATRIX final_matrix;
	VECTOR averagepos;
	VECTOR mid_position;
	VECTOR toss;
	long n[4];
	long z[15];
	int local_30;

	pos = s1;
	pSVar7 = s;

	if (cp < car_data) 
	{
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	/*
	if ((cameraview == 2 && CAR_INDEX(cp) == CameraCar) || 
		player[CurrentPlayerView].cameraView == 2 && player[CurrentPlayerView].cameraCarId == CAR_INDEX(cp))	// bug fix
		in_car = true;
	*/

	if (front == 0) 
	{
		iVar15 = 0;
		s1[0].vx = -0xcc;
		s1[1].vx = 0xcc;
		s1[2].vx = -0xcc;
		s1[3].vx = 0xcc;
		s1[3].vz = ((car_cosmetics[cp->ap.model].colBox.vz - 10) * 0x10000) >> 0x10;
		s1[1].vz = (s1[3].vz + 0xcc) * 0x10000 >> 0x10;
	}
	else
	{
		s1[3].vz = -(car_cosmetics[cp->ap.model].colBox.vz + 0x32);
		s1[8].vz = (s1[3].vz + -0x488) * 0x10000 >> 0x10;
		s1[6].vz = s1[3].vz;
		s1[7].vz = s1[3].vz;

		if (in_car) 
		{
			s1[1].vz = s1[8].vz + 600;
			s1[0].vx = 0x88;
			s1[1].vx = -0x158;
			s1[2].vx = -0x15;
			s1[3].vx = -0x8f;
			s1[4].vx = 0x158;
			s1[5].vx = -0x88;
			s1[6].vx = 0x8f;
			s1[7].vx = 0x15;
			s1[8].vz = s1[8].vz + -400;
			s1[9].vz = s1[3].vz + 10;
			s1[8].vx = -0x52;
			s1[10].vx = 0x52;
			s1[9].vx = -0x52;
			s1[11].vx = 0x52;
			s1[4].vz = s1[1].vz;
			s1[5].vz = s1[1].vz;
			s1[10].vz = s1[8].vz;
			s1[11].vz = s1[9].vz;

			LightSortCorrect = -800;
			iVar15 = 3;
		}
		else 
		{
			s1[1].vz = s1[8].vz + 100;
			s1[0].vx = 0x88;
			s1[1].vx = -0x158;
			s1[2].vx = -0x15;
			s1[3].vx = -0x8f;
			s1[4].vx = 0x158;
			s1[5].vx = -0x88;
			s1[6].vx = 0x8f;
			s1[7].vx = 0x15;
			s1[10].vx = 0x52;
			s1[11].vx = 0x52;
			s1[8].vx = -0x52;
			s1[9].vx = -0x52;
			s1[4].vz = s1[1].vz;
			s1[5].vz = s1[1].vz;
			s1[9].vz = s1[3].vz;
			s1[10].vz = s1[8].vz;
			s1[11].vz = s1[3].vz;

			iVar15 = 3;
		}

		if (player[CurrentPlayerView].cameraView == 2 && cp == &car_data[player[CurrentPlayerView].playerCarId])
			LightSortCorrect = -320;
		else
			LightSortCorrect = -200;
	}

	s1[0].vz = s1[1].vz;
	s1[2].vz = s1[3].vz;

	SetRotMatrix(&cp->hd.drawCarMat);

	mid_position.vx = 0;
	mid_position.vy = 0;
	mid_position.vz = -500;

	_MatrixRotate(&mid_position);

	mid_position.vx += cp->hd.where.t[0];
	mid_position.vy += cp->hd.where.t[1];
	mid_position.vz += cp->hd.where.t[2];

	iVar5 = MapHeight(&mid_position);

	pSVar8 = pSVar7;
	iVar14 = 0;

	while (true)
	{
		in_car = iVar14 < 4;

		if (iVar15 == 3)
			in_car = iVar14 < 0xc;

		if (!in_car)
			break;

		pos->vy = 0;
		_MatrixRotate(pos);

		toss.vx = pos->vx + cp->hd.where.t[0];
		toss.vy = pos->vy + cp->hd.where.t[1];
		toss.vz = pos->vz + cp->hd.where.t[2];

		pSVar8->vx = toss.vx - camera_position.vx;
		pSVar8->vz = toss.vz - camera_position.vz;

		iVar16 = MapHeight(&toss);

		sVar9 = -iVar16;
		iVar6 = -iVar16 + iVar5;

		if (iVar6 < 0)
			iVar6 = -iVar5 + iVar16;

		if (500 < iVar6)
			sVar9 = -iVar5;

		pos = pos + 1;
		pSVar8 = pSVar8 + 1;
		s[iVar14].vy = sVar9 - camera_position.vy;

		iVar14++;
	}

	iVar16 = FIXED(s[0].vx * s[1].vy - s[0].vy * s[1].vx) *	s[2].vz;
	iVar5 =  FIXED(s[0].vy * s[1].vz - s[0].vz * s[1].vy) * s[2].vx +
			 FIXED(s[0].vz * s[1].vx - s[0].vx * s[1].vz) * s[2].vy + iVar16;

	if (-1 < iVar5)
	{
		if (iVar14 == 0) 
		{
			trap(7);
		}

		gte_SetRotMatrix(&inv_camera_matrix);
		gte_SetTransVector(&dummy);

		if (iVar15 == 0) 
		{
			gte_ldv3(&s[0], &s[1], &s[2]);
			gte_rtpt();

			gte_stszotz(&local_30);

			if (local_30 > 40)
				local_30 -= 40;

			if (local_30 > 49)
			{
				poly = (POLY_FT4 *)current->primptr;

				// [A] Emit poly only after ot z checked
				setPolyFT4(poly);
				setSemiTrans(poly, 1);

				poly->u0 = light_pool_texture.coords.u0;
				poly->v0 = light_pool_texture.coords.v0;
				poly->u1 = light_pool_texture.coords.u1;
				poly->v1 = light_pool_texture.coords.v1;
				poly->u2 = light_pool_texture.coords.u2;
				poly->v2 = light_pool_texture.coords.v2;
				poly->u3 = light_pool_texture.coords.u3;
				poly->v3 = light_pool_texture.coords.v3;

				poly->r0 = col->r >> 1;
				poly->g0 = col->b >> 1;
				poly->b0 = col->g >> 1;

				gte_stsxy3(&poly->x0, &poly->x1, &poly->x2);

				poly->tpage = light_pool_texture.tpageid | 0x20;
				poly->clut = light_pool_texture.clutid;

				gte_ldv0(&s[3]);

				gte_rtps();

				gte_stsxy(&poly->x3);

				addPrim(current->ot + (local_30 >> 1), poly);
				current->primptr += sizeof(POLY_FT4);
			}
		}
		else
		{
			if (iVar15 == 3)
			{
				iVar15 = 11;
				pSVar8 = sout;

				do {
					gte_ldv0(pSVar7);

					docop2(0x480012);

					// FIXME: here might be 'gte_stlvnl'
					gte_stsv(pSVar8);

					//uVar10 = getCopReg(2, 0x4800);
					//uVar11 = getCopReg(2, 0x5000);
					//uVar12 = getCopReg(2, 0x5800);
					//pSVar8->vx = (short)uVar10;
					//pSVar8->vy = (short)uVar11;
					//pSVar8->vz = (short)uVar12;

					pSVar8++;
					iVar15--;
					pSVar7++;
				} while (-1 < iVar15);

				uVar13 = 0;

				do {
					iVar15 = uVar13 * 4;

					MATRIX tempmatrix;

					{
						tempmatrix.m[0][0] = 0x1000;
						tempmatrix.m[1][0] = 0;
						tempmatrix.m[2][0] = 0;

						tempmatrix.m[0][1] = 0;
						tempmatrix.m[1][1] = 0x1000;
						tempmatrix.m[2][1] = 0;

						tempmatrix.m[0][2] = 0;
						tempmatrix.m[1][2] = 0;
						tempmatrix.m[2][2] = 0x1000;
					}

					//spolys = current->primptr;	// I'm getting rid of this...
					gte_SetRotMatrix(&tempmatrix);
					gte_SetTransVector(&dummy);

					bVar1 = RightLight;

					if ((uVar13 & 2) != 0)
						bVar1 = LeftLight;

					sVar9 = bVar1 * 4 + bVar1;

					if (sVar9 != 0)
					{
						if ((uVar13 & 1) == 0) 
						{
							sQuad(sout + PoolPrimData[iVar15 + 1],
								  sout + PoolPrimData[iVar15 + 3],
								  sout + PoolPrimData[iVar15 + 2],
								  sout + PoolPrimData[iVar15], sVar9 * 12, LightSortCorrect);
						}
						else
						{
							sQuad(sout + PoolPrimData[iVar15],
								  sout + PoolPrimData[iVar15 + 2],
								  sout + PoolPrimData[iVar15 + 3],
								  sout + PoolPrimData[iVar15 + 1], sVar9 * 12, LightSortCorrect);
						}

						//current->primptr = spolys;
					}
					uVar13++;
				} while (uVar13 < 4);
			}
		}

		LightSortCorrect = -10;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ AllocateLeaf()
 // line 1297, offset 0x00039a90
	/* begin block 1 */
		// Start line: 8721
	/* end block 1 */
	// End Line: 8722

	/* begin block 2 */
		// Start line: 2594
	/* end block 2 */
	// End Line: 2595

	/* begin block 3 */
		// Start line: 8722
	/* end block 3 */
	// End Line: 8723

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
int AllocateLeaf(void)
{
	if (next_leaf > 49)
		return -1;

	return leaf_alloc[next_leaf++];
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReleaseLeaf(short num /*$a0*/)
 // line 1313, offset 0x00039d8c
	/* begin block 1 */
		// Start line: 2626
	/* end block 1 */
	// End Line: 2627

	/* begin block 2 */
		// Start line: 12096
	/* end block 2 */
	// End Line: 12097

// [D]
void ReleaseLeaf(short num)
{
	next_leaf--;
	leaf_alloc[next_leaf] = num;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddLeaf(struct VECTOR *Position /*$s1*/, int num_leaves /*$s5*/, int Type /*$s3*/)
 // line 1327, offset 0x00033574
	/* begin block 1 */
		// Start line: 1328
		// Start offset: 0x00033574
		// Variables:
	// 		struct LEAF *myleaf; // $a1
	// 		int num; // $v1
	// 		int loop; // $s2
	// 		int temprand; // $s0

		/* begin block 1.1 */
			// Start line: 1343
			// Start offset: 0x000335D8

			/* begin block 1.1.1 */
				// Start line: 1401
				// Start offset: 0x000336E4
			/* end block 1.1.1 */
			// End offset: 0x000336F8
			// End Line: 1406

			/* begin block 1.1.2 */
				// Start line: 1410
				// Start offset: 0x0003370C
				// Variables:
			// 		int temp; // $v0
			/* end block 1.1.2 */
			// End offset: 0x0003370C
			// End Line: 1410

			/* begin block 1.1.3 */
				// Start line: 1416
				// Start offset: 0x00033738
				// Variables:
			// 		int temp; // $v0
			/* end block 1.1.3 */
			// End offset: 0x0003374C
			// End Line: 1419
		/* end block 1.1 */
		// End offset: 0x0003374C
		// End Line: 1420
	/* end block 1 */
	// End offset: 0x00033784
	// End Line: 1428

	/* begin block 2 */
		// Start line: 2983
	/* end block 2 */
	// End Line: 2984

	/* begin block 3 */
		// Start line: 2989
	/* end block 3 */
	// End Line: 2990

void AddLeaf(VECTOR *Position, int num_leaves, int Type)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte bVar2;
	int iVar3;
	uint uVar4;
	int iVar5;
	uint uVar6;
	uint uVar7;
	long lVar8;
	int iVar9;

	if (gDoLeaves != 0) {
		iVar9 = 0;
		Position->vy = -Position->vy;
		iVar3 = MapHeight(Position);
		Position->pad = iVar3;
		if (0 < num_leaves) {
			do {
				uVar4 = rand();
				iVar3 = AllocateLeaf();
				if (iVar3 < 0) {
					return;
				}
				leaf[iVar3].position.vx = Position->vx + (uVar4 & 0xfe);
				leaf[iVar3].position.vz = Position->vz + ((int)uVar4 >> 8 & 0xfeU);
				if (Type == 1) {
					iVar5 = Position->vy;
				}
				else {
					iVar5 = Position->pad;
				}
				leaf[iVar3].position.vy = -iVar5;
				lVar8 = Position->pad;
				leaf[iVar3].life = 600;
				leaf[iVar3].flags = 2;
				bVar1 = (byte)uVar4;
				leaf[iVar3].direction.vx = 0;
				leaf[iVar3].direction.vy = 0;
				leaf[iVar3].direction.vz = 0;
				leaf[iVar3].pos = (ushort)((int)uVar4 >> 7) & 0xff;
				leaf[iVar3].step = (bVar1 & 7) + 1;
				leaf[iVar3].position.pad = lVar8;
				if (Type == 1) {
					if ((uVar4 & 3) == 0) {
						leaf[iVar3].rgb.r = 'n';
						bVar2 = 0xf;
						leaf[iVar3].rgb.g = 'p';
						goto LAB_000336f4;
					}
					if ((uVar4 & 3) != 1) {
						leaf[iVar3].rgb.r = '<';
						bVar2 = 0x1e;
						leaf[iVar3].rgb.g = '2';
						goto LAB_000336f4;
					}
					leaf[iVar3].rgb.r = '\x14';
					leaf[iVar3].rgb.g = ',';
					leaf[iVar3].rgb.b = '\0';
				}
				else {
					bVar2 = bVar1 & 0x1f;
					leaf[iVar3].rgb.r = bVar2;
					leaf[iVar3].rgb.g = bVar2;
				LAB_000336f4:
					leaf[iVar3].rgb.b = bVar2;
				}
				if (gTimeOfDay == 3) {
					uVar7 = 0x3f3f3f3f;
					uVar6 = (int)leaf[iVar3].rgb >> 2;
				LAB_00033744:
					*(uint *)&leaf[iVar3].rgb = uVar6 & uVar7;
				}
				else {
					if (gWeather - 1U < 2) {
						uVar7 = 0x7f7f7f7f;
						uVar6 = (int)leaf[iVar3].rgb >> 1;
						goto LAB_00033744;
					}
				}
				iVar9 = iVar9 + 1;
				leaf[iVar3].sin_index1 = (ushort)uVar4 & 0xfff;
				leaf[iVar3].sin_index2 = (ushort)((int)uVar4 >> 4) & 0xfff;
				leaf[iVar3].sin_addition2 = -((byte)(uVar4 >> 8) & 7);
				leaf[iVar3].sin_addition1 = -(bVar1 & 3);
				leaf[iVar3].type = (char)Type;
			} while (iVar9 < num_leaves);
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ SwirlLeaves(struct _CAR_DATA *cp /*$a0*/)
 // line 1437, offset 0x00039e54
	/* begin block 1 */
		// Start line: 1438
		// Start offset: 0x00039E54
		// Variables:
	// 		int count; // $s2
	// 		struct LEAF *lpLeaf; // $s0
	// 		int XDiff; // $v0
	// 		int ZDiff; // $a1
	// 		struct VECTOR *CarPos; // $s1
	// 		int WheelSpeed; // $a1

		/* begin block 1.1 */
			// Start line: 1475
			// Start offset: 0x00039F60
		/* end block 1.1 */
		// End offset: 0x00039F84
		// End Line: 1477
	/* end block 1 */
	// End offset: 0x00039F90
	// End Line: 1481

	/* begin block 2 */
		// Start line: 17528
	/* end block 2 */
	// End Line: 17529

	/* begin block 3 */
		// Start line: 2874
	/* end block 3 */
	// End Line: 2875

	/* begin block 4 */
		// Start line: 17533
	/* end block 4 */
	// End Line: 17534

void SwirlLeaves(_CAR_DATA *cp)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	LEAF *pLVar3;
	int iVar4;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}
	if (((0x1d4be < (cp->hd).wheel_speed + 39999U) && (gDoLeaves != 0)) &&
		(pLVar3 = leaf, pauseflag == 0)) {
		iVar4 = 0x31;
		do {
			if ((((pLVar3->flags & 2) != 0) && (-0xb4 < (pLVar3->position).vy + (cp->hd).where.t[1])) &&
				((iVar2 = (cp->hd).where.t[2] - (pLVar3->position).vz,
				((cp->hd).where.t[0] - (pLVar3->position).vx) + 0x167U < 0x2cf &&
					((iVar2 < 0x168 && (-0x168 < iVar2)))))) {
				iVar2 = rand();
				iVar1 = (pLVar3->position).vy;
				(pLVar3->direction).vy = -0x19 - ((ushort)iVar2 & 0x1f);
				(pLVar3->position).vy = iVar1 + -1;
			}
			iVar4 = iVar4 + -1;
			pLVar3 = pLVar3 + 1;
		} while (-1 < iVar4);
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitDebrisNames()
 // line 1493, offset 0x000337ac
	/* begin block 1 */
		// Start line: 1495
		// Start offset: 0x000337AC
	/* end block 1 */
	// End offset: 0x00033B9C
	// End Line: 1555

	/* begin block 2 */
		// Start line: 3607
	/* end block 2 */
	// End Line: 3608

	/* begin block 3 */
		// Start line: 3608
	/* end block 3 */
	// End Line: 3609

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
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
	head1_texture.coords.u1 = head1_texture.coords.u0 + '\b';
	head1_texture.coords.u3 = head1_texture.coords.u1;

	GetTextureDetails("LIGHTREF", &lightref_texture);
	GetTextureDetails("LIGHT", &light_pool_texture);

	InitButtonTextures();
	InitTannerShadow();
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitDebris()
 // line 1564, offset 0x00033b9c
	/* begin block 1 */
		// Start line: 1566
		// Start offset: 0x00033B9C
		// Variables:
	// 		int loop; // $v1
	// 		int count; // $s0
	// 		struct TPAN texnum; // stack offset -88
	// 		struct TRI_POINT_LONG temptri; // stack offset -80
	// 		struct BVECTOR *debrisPTR; // $a0

		/* begin block 1.1 */
			// Start line: 1601
			// Start offset: 0x00033CF4

			/* begin block 1.1.1 */
				// Start line: 1605
				// Start offset: 0x00033D10
			/* end block 1.1.1 */
			// End offset: 0x00033D80
			// End Line: 1610
		/* end block 1.1 */
		// End offset: 0x00033E2C
		// End Line: 1627
	/* end block 1 */
	// End offset: 0x00033FA8
	// End Line: 1674

	/* begin block 2 */
		// Start line: 3743
	/* end block 2 */
	// End Line: 3744

	/* begin block 3 */
		// Start line: 3753
	/* end block 3 */
	// End Line: 3754

	/* begin block 4 */
		// Start line: 3754
	/* end block 4 */
	// End Line: 3755

	/* begin block 5 */
		// Start line: 3759
	/* end block 5 */
	// End Line: 3760

/* WARNING: Unknown calling convention yet parameter storage is locked */

SMOKE *smoke_table;
SMOKE smoke[80];

SVECTOR leaf_rotvec;
LEAF leaf[50];

SVECTOR debris_rotvec;
DEBRIS debris[60];

int StreakCount1 = 0;
int main_cop_light_pos = 0;
int NextDamagedLamp = 0;

CELL_OBJECT ground_debris[16];
int groundDebrisIndex = 0;

DAMAGED_LAMP damaged_lamp[5];

MATRIX debris_mat;
MATRIX leaf_mat;

// [D]
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

	i = 19;
	
	do {
		Known_Lamps[i].set = 0;
		i++;
	} while (i < 21);

	do {
		debris_alloc[i] = i;

		debris[i].pos = 0;
		debris[i].num = i;

		i++;
	} while (i < 60);

	do {
		ground_debris[i].type = 0xffff;
		i++;
	} while (i < 16);

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

	for (i = 0; i < 80; i++)
	{
		smoke_alloc[i] = i;
		
		smoke[i].pos = 0;
		smoke[i].flags = 0;
		smoke[i].num = i;
	}

	for (i = 0; i < 50; i++)
	{
		leaf_alloc[i] = i;

		leaf[i].pos = 0;
		leaf[i].num = i;
	}

	for (i = 0; i < 5; i++)
		damaged_lamp[i].cop = 0;

	for (i = 0; i < 9; i++)
		damaged_object[i].active = 0;

	LightSortCorrect = -10;
	SmashablesHit = 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ AllocateDebris()
 // line 1686, offset 0x00039a54
	/* begin block 1 */
		// Start line: 9103
	/* end block 1 */
	// End Line: 9104

	/* begin block 2 */
		// Start line: 3372
	/* end block 2 */
	// End Line: 3373

	/* begin block 3 */
		// Start line: 9104
	/* end block 3 */
	// End Line: 9105

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
int AllocateDebris(void)
{
	if (next_debris > 59)
		return -1;

	return debris_alloc[next_debris++];
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReleaseDebris(short num /*$a0*/)
 // line 1704, offset 0x00039d68
	/* begin block 1 */
		// Start line: 12485
	/* end block 1 */
	// End Line: 12486

	/* begin block 2 */
		// Start line: 3408
	/* end block 2 */
	// End Line: 3409

	/* begin block 3 */
		// Start line: 12486
	/* end block 3 */
	// End Line: 12487

// [D]
void ReleaseDebris(short num)
{
	next_debris--;
	debris_alloc[next_debris] = num;
}



// decompiled code
// original method signature: 
// int /*$ra*/ AllocateSmoke()
 // line 1719, offset 0x00039acc
	/* begin block 1 */
		// Start line: 9149
	/* end block 1 */
	// End Line: 9150

	/* begin block 2 */
		// Start line: 9567
	/* end block 2 */
	// End Line: 9568

	/* begin block 3 */
		// Start line: 9569
	/* end block 3 */
	// End Line: 9570

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
int AllocateSmoke(void)
{
	if (next_smoke > 79)
		return -1;

	return smoke_alloc[next_smoke++];
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReleaseSmoke(short num /*$a0*/)
 // line 1737, offset 0x00039dd4
	/* begin block 1 */
		// Start line: 3474
	/* end block 1 */
	// End Line: 3475

	/* begin block 2 */
		// Start line: 15398
	/* end block 2 */
	// End Line: 15399

// [D]
void ReleaseSmoke(short num)
{
	next_smoke--;
	smoke_alloc[next_smoke] = num;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddGroundDebris()
 // line 1753, offset 0x00033fa8
	/* begin block 1 */
		// Start line: 1755
		// Start offset: 0x00033FA8
		// Variables:
	// 		struct VECTOR Position; // stack offset -48
	// 		int seed; // $s0
	// 		int number; // $v0
	// 		int count; // $s3
	// 		int xbound; // $a1
	// 		int zbound; // $a0
	// 		int type; // $a2
	// 		struct CELL_OBJECT *cop; // $s1
	// 		struct MODEL *model; // $s2

		/* begin block 1.1 */
			// Start line: 1783
			// Start offset: 0x0003407C
		/* end block 1.1 */
		// End offset: 0x00034100
		// End Line: 1804
	/* end block 1 */
	// End offset: 0x00034110
	// End Line: 1807

	/* begin block 2 */
		// Start line: 4269
	/* end block 2 */
	// End Line: 4270

	/* begin block 3 */
		// Start line: 4349
	/* end block 3 */
	// End Line: 4350

	/* begin block 4 */
		// Start line: 4350
	/* end block 4 */
	// End Line: 4351

	/* begin block 5 */
		// Start line: 4357
	/* end block 5 */
	// End Line: 4358

/* WARNING: Unknown calling convention yet parameter storage is locked */

void AddGroundDebris(void)
{
	UNIMPLEMENTED();
	/*
	uint uVar1;
	uint uVar2;
	int iVar3;
	int Type;
	CELL_OBJECT *pCVar4;
	MODEL *pMVar5;
	int iVar6;
	VECTOR local_30;

	if (0x30d3e < car_data[0].hd.wheel_speed + 99999U) {
		iVar6 = 0;
		pCVar4 = ground_debris;
		do {
			if (pCVar4->type != 0xffff) {
				Type = (pCVar4->pos).vx - camera_position.vx;
				pMVar5 = modelpointers1536[pCVar4->type];
				iVar3 = (pCVar4->pos).vz - camera_position.vz;
				if (Type < 0) {
					Type = -Type;
				}
				if (iVar3 < 0) {
					iVar3 = -iVar3;
				}
				if (((Type < 0x2329) && (iVar3 < 0x2329)) && ((7000 < Type || (7000 < iVar3)))) {
					if (0x27 < next_leaf) {
						return;
					}
					uVar1 = rand();
					local_30.vy = -10000;
					local_30.vx = (pCVar4->pos).vx + ((uVar1 & 0x3ff) - 0x200);
					uVar2 = rand();
					local_30.vz = (pCVar4->pos).vz + ((uVar2 & 0x3ff) - 0x200);
					uVar2 = uVar1 & 7;
					if ((pMVar5->flags2 & 0x2000) == 0) {
						uVar2 = uVar1 & 3;
						Type = 2;
					}
					else {
						Type = 1;
					}
					AddLeaf(&local_30, uVar2 + 1, Type);
				}
			}
			iVar6 = iVar6 + 1;
			pCVar4 = pCVar4 + 1;
		} while (iVar6 < 0x10);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawSmashable_sprites()
 // line 1815, offset 0x00034138
	/* begin block 1 */
		// Start line: 1817
		// Start offset: 0x00034138
		// Variables:
	// 		int count; // $s6
	// 		struct VECTOR pos; // stack offset -128
	// 		struct DAMAGED_OBJECT *dam; // $s2

		/* begin block 1.1 */
			// Start line: 1826
			// Start offset: 0x000341A4
			// Variables:
		// 		struct MATRIX object_matrix; // stack offset -112
		// 		struct MATRIX spritematrix; // stack offset -80
		// 		struct MATRIX *finalmatrix; // $s0
		// 		struct MODEL *model; // $s3

			/* begin block 1.1.1 */
				// Start line: 1861
				// Start offset: 0x0003435C
				// Variables:
			// 		unsigned long colours; // $a0
			/* end block 1.1.1 */
			// End offset: 0x000343B4
			// End Line: 1870
		/* end block 1.1 */
		// End offset: 0x000343E8
		// End Line: 1875
	/* end block 1 */
	// End offset: 0x00034424
	// End Line: 1877

	/* begin block 2 */
		// Start line: 4518
	/* end block 2 */
	// End Line: 4519

	/* begin block 3 */
		// Start line: 4519
	/* end block 3 */
	// End Line: 4520

	/* begin block 4 */
		// Start line: 4523
	/* end block 4 */
	// End Line: 4524

/* WARNING: Unknown calling convention yet parameter storage is locked */

extern _pct plotContext;


// [D] [A]
void DrawSmashable_sprites(void)
{
	//undefined4 uVar1;
	DAMAGED_OBJECT *dam;
	MODEL *model;
	int count;
	VECTOR pos;
	MATRIX object_matrix;
	MATRIX spritematrix;

	dam = damaged_object;
	count = 7;
	do {
		if (dam->active != 0)
		{
			model = modelpointers[dam->cop.type];

			object_matrix.m[0][0] = 0x1000;
			object_matrix.m[0][1] = 0;
			object_matrix.m[0][2] = 0;

			object_matrix.m[1][0] = 0;
			object_matrix.m[1][1] = 0x1000;
			object_matrix.m[1][2] = 0;

			object_matrix.m[2][0] = 0;
			object_matrix.m[2][1] = 0;
			object_matrix.m[2][2] = 0x1000;

			if ((model->shape_flags & 0x4000) == 0)
				RotMatrixY(dam->rot_speed * dam->damage * 3 & 0xfff, &object_matrix);

			RotMatrixZ(dam->rot_speed * dam->damage & 0xfff, &object_matrix);

			// [A]
#ifndef PSX
			MulMatrix0(&aspect, &object_matrix, &object_matrix);
#endif

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
				if ((model->shape_flags & 0x4000) == 0)
				{
					PlotMDL_less_than_128(model);
				}
				else
				{
					UNIMPLEMENTED();

					if ((gWeather - 1U < 2) || (gTimeOfDay == 3))
					{
						plotContext.colour = NightAmbient << 0x10 | NightAmbient << 8 | NightAmbient | 0x2c000000;
					}
					else 
					{
						plotContext.colour = 0x2c808080;
					}

					// [A]
					//current->primptr = Asm_PlotSprite(model, current->primptr, current->ot, 0);

				}
			}
		}
		count--;
		dam++;
	} while (-1 < count);
}



// decompiled code
// original method signature: 
// int /*$ra*/ MoveSmashable_object()
 // line 1886, offset 0x0003a234
	/* begin block 1 */
		// Start line: 1888
		// Start offset: 0x0003A234
		// Variables:
	// 		int count; // $a3
	// 		struct DAMAGED_OBJECT *dam; // $a1

		/* begin block 1.1 */
			// Start line: 1896
			// Start offset: 0x0003A258
			// Variables:
		// 		int groundlevel; // $v0
		/* end block 1.1 */
		// End offset: 0x0003A2C0
		// End Line: 1911
	/* end block 1 */
	// End offset: 0x0003A2D4
	// End Line: 1914

	/* begin block 2 */
		// Start line: 3772
	/* end block 2 */
	// End Line: 3773

	/* begin block 3 */
		// Start line: 21340
	/* end block 3 */
	// End Line: 21341

	/* begin block 4 */
		// Start line: 21342
	/* end block 4 */
	// End Line: 21343

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
int MoveSmashable_object(void)
{
	char cVar1;
	short sVar2;
	short sVar3;
	int iVar4;
	DAMAGED_OBJECT *pDVar5;
	int iVar6;
	int iVar7;

	pDVar5 = damaged_object;
	iVar7 = 7;

	do {
		if (pDVar5->active != 0) 
		{
			iVar6 = pDVar5->cop.pos.vy;

			if (iVar6 < 50 - player[0].pos[1]) 
			{
				iVar4 = pDVar5->cop.pos.vz;
				pDVar5->vx = pDVar5->vx + pDVar5->velocity.vx;
				sVar2 = (pDVar5->velocity).vz;
				cVar1 = pDVar5->damage;
				pDVar5->cop.pos.vy = iVar6 + pDVar5->velocity.vy;
				sVar3 = (pDVar5->velocity).vy;
				pDVar5->cop.pos.vz = iVar4 + sVar2;
				pDVar5->damage = cVar1 + 1;
				pDVar5->velocity.vy = sVar3 + 10;
			}
			else 
			{
				pDVar5->active = 0;
			}

		}
		iVar7--;
		pDVar5++;
	} while (-1 < iVar7);
	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddSmallStreetLight(struct CELL_OBJECT *cop /*$s1*/, int x /*$s3*/, int y /*$s6*/, int z /*$s4*/, int type /*stack 16*/)
 // line 1925, offset 0x00034424
	/* begin block 1 */
		// Start line: 1926
		// Start offset: 0x00034424
		// Variables:
	// 		struct VECTOR v1; // stack offset -112
	// 		struct VECTOR v2; // stack offset -96
	// 		struct VECTOR v3; // stack offset -80
	// 		struct SVECTOR pos; // stack offset -64
	// 		struct CVECTOR col; // stack offset -56
	// 		struct CVECTOR col1; // stack offset -48
	// 		int count; // $v1
	// 		short angle; // $s2
	// 		int halo_size; // $fp
	// 		int size; // $s5
	// 		int LampId; // $s7
	// 		struct DAMAGED_LAMP *dam; // $s0

		/* begin block 1.1 */
			// Start line: 1961
			// Start offset: 0x000344EC
		/* end block 1.1 */
		// End offset: 0x00034540
		// End Line: 1967
	/* end block 1 */
	// End offset: 0x00034828
	// End Line: 2039

	/* begin block 2 */
		// Start line: 4795
	/* end block 2 */
	// End Line: 4796

	/* begin block 3 */
		// Start line: 4844
	/* end block 3 */
	// End Line: 4845

	/* begin block 4 */
		// Start line: 4854
	/* end block 4 */
	// End Line: 4855

/* WARNING: Could not reconcile some variable overlaps */

void AddSmallStreetLight(CELL_OBJECT *cop, int x, int y, int z, int type)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	undefined4 in_zero;
	undefined4 in_at;
	undefined uVar2;
	uint uVar3;
	int iVar4;
	uint uVar5;
	DAMAGED_LAMP *pDVar6;
	uint uVar7;
	int iVar8;
	short size;
	VECTOR local_70;
	VECTOR local_60;
	VECTOR local_50;
	uint local_40;
	uint local_3c;
	undefined4 local_38;
	CVECTOR local_30[2];

	pDVar6 = &damaged_lamp;
	local_38 = DAT_000aa370;
	local_30[0] = (CVECTOR)PTR_DAT_000aa374;
	bVar1 = cop->yang;
	uVar7 = (uint)bVar1;
	if (type == 0) {
		iVar8 = 0x19;
		size = 0x96;
	}
	else {
		iVar8 = 100;
		if (type == 1) {
			iVar8 = 0x32;
			size = 0x96;
		}
		else {
			size = 300;
		}
	}
	iVar4 = 0;
	do {
		if (cop == pDVar6->cop) {
			if (2 < (byte)pDVar6->damage) {
				return;
			}
			uVar3 = rand();
			uVar3 = (uVar3 & 0x3f) - ((uint)(byte)pDVar6->damage * 0x20 + -0x5a);
			local_38 = uVar3 & 0xff |
				(uint)CONCAT21(CONCAT11(local_38._3_1_, (char)uVar3), (char)uVar3) << 8;
			uVar3 = (uVar3 & 0xff) >> 1;
			uVar2 = (undefined)uVar3;
			local_30[0] = (CVECTOR)(uVar3 | (uint)CONCAT21(CONCAT11(local_30[0].cd, uVar2), uVar2) << 8);
			break;
		}
		iVar4 = iVar4 + 1;
		pDVar6 = pDVar6 + 1;
	} while (iVar4 < 4);
	if ((bVar1 & 0xf) == 0) {
		bVar1 = bVar1 >> 4;
		if (bVar1 == 1) {
			local_70.vx = ((cop->pos).vx - camera_position.vx) + z;
			local_70.vz = ((cop->pos).vz - camera_position.vz) - x;
		}
		else {
			if (bVar1 < 2) {
				if (bVar1 == 0) {
					local_70.vx = ((cop->pos).vx - camera_position.vx) + x;
					local_70.vz = ((cop->pos).vz - camera_position.vz) + z;
				}
			}
			else {
				if (bVar1 == 2) {
					local_70.vx = ((cop->pos).vx - camera_position.vx) - x;
					local_70.vz = ((cop->pos).vz - camera_position.vz) - z;
				}
				else {
					if (bVar1 == 3) {
						local_70.vx = ((cop->pos).vx - camera_position.vx) - z;
						local_70.vz = ((cop->pos).vz - camera_position.vz) + x;
					}
				}
			}
		}
		local_70.vy = ((cop->pos).vy - camera_position.vy) + y;
	}
	else {
		uVar3 = local_3c & 0xffff0000;
		local_3c = uVar3 | z & 0xffffU;
		setCopControlWord(2, 0, *(undefined4 *)(&matrixtable)[uVar7].m);
		setCopControlWord(2, 0x800, *(undefined4 *)((&matrixtable)[uVar7].m + 2));
		setCopControlWord(2, 0x1000, *(undefined4 *)((&matrixtable)[uVar7].m + 4));
		setCopControlWord(2, 0x1800, *(undefined4 *)((&matrixtable)[uVar7].m + 6));
		setCopControlWord(2, 0x2000, *(undefined4 *)((&matrixtable)[uVar7].m + 8));
		setCopReg(2, in_zero, x & 0xffffU | y << 0x10);
		setCopReg(2, in_at, local_3c);
		copFunction(2, 0x486012);
		uVar7 = getCopReg(2, 0x4800);
		iVar4 = getCopReg(2, 0x5000);
		uVar5 = getCopReg(2, 0x5800);
		local_40 = uVar7 & 0xffff | iVar4 << 0x10;
		local_3c = uVar3 | uVar5 & 0xffff;
		local_70.vx = ((cop->pos).vx - camera_position.vx) + (int)(short)uVar7;
		local_70.vy = ((cop->pos).vy - camera_position.vy) + (int)(short)iVar4;
		local_3c._0_2_ = (short)(uVar5 & 0xffff);
		local_70.vz = ((cop->pos).vz - camera_position.vz) + (int)(short)local_3c;
	}
	local_60.vx = local_70.vx;
	local_60.vz = local_70.vz;
	local_60.vy = MapHeight(&local_70);
	LightSortCorrect = -0x1e;
	local_38 = local_38 & 0xffffff;
	local_60.vy = -camera_position.vy - local_60.vy;
	local_50.vx = local_70.vx;
	local_50.vy = local_70.vy;
	local_50.vz = local_70.vz;
	local_50.pad = local_70.pad;
	LightIndex = find_lamp_streak((int)&(cop->pos).vx + x);
	if (-1 < LightIndex) {
		local_38 = CONCAT13(0x60, (undefined3)local_38);
	}
	ShowLight(&local_50, (CVECTOR *)&local_38, (short)iVar8, &light_texture);
	ShowLight1(&local_50, local_30, size, &light_texture);
	DisplayLightReflections(&local_60, local_30, (short)(iVar8 << 1), &lightref_texture);
	LightSortCorrect = -10;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddLightEffect(struct CELL_OBJECT *cop /*$t0*/, int x /*$t2*/, int y /*$a2*/, int z /*$a3*/, int type /*stack 16*/, int colour /*stack 20*/)
 // line 2049, offset 0x00034858
	/* begin block 1 */
		// Start line: 2050
		// Start offset: 0x00034858
		// Variables:
	// 		struct VECTOR v1; // stack offset -88
	// 		struct VECTOR v2; // stack offset -72
	// 		struct VECTOR v3; // stack offset -56
	// 		struct SVECTOR pos; // stack offset -40
	// 		struct CVECTOR col; // stack offset -32
	// 		struct CVECTOR col1; // stack offset -24
	// 		short angle; // $v1
	// 		int size; // $s1
	/* end block 1 */
	// End offset: 0x00034C6C
	// End Line: 2175

	/* begin block 2 */
		// Start line: 5163
	/* end block 2 */
	// End Line: 5164

/* WARNING: Could not reconcile some variable overlaps */

void AddLightEffect(CELL_OBJECT *cop, int x, int y, int z, int type, int colour)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	uint uVar2;
	undefined4 in_zero;
	undefined4 in_at;
	uint uVar3;
	int iVar4;
	uint uVar5;
	int unaff_s1;
	VECTOR local_58;
	VECTOR local_48;
	int local_38;
	int local_34;
	int local_30;
	long local_2c;
	uint local_28;
	uint local_24;
	CVECTOR local_20[4];

	bVar1 = cop->yang;
	uVar3 = (uint)bVar1;
	if ((bVar1 & 0xf) == 0) {
		bVar1 = bVar1 >> 4;
		if (bVar1 == 1) {
			local_58.vx = ((cop->pos).vx - camera_position.vx) + z;
			local_58.vz = ((cop->pos).vz - camera_position.vz) - x;
		}
		else {
			if (bVar1 < 2) {
				if (bVar1 == 0) {
					local_58.vx = ((cop->pos).vx - camera_position.vx) + x;
					local_58.vz = ((cop->pos).vz - camera_position.vz) + z;
				}
			}
			else {
				if (bVar1 == 2) {
					local_58.vx = ((cop->pos).vx - camera_position.vx) - x;
					local_58.vz = ((cop->pos).vz - camera_position.vz) - z;
				}
				else {
					if (bVar1 == 3) {
						local_58.vx = ((cop->pos).vx - camera_position.vx) - z;
						local_58.vz = ((cop->pos).vz - camera_position.vz) + x;
					}
				}
			}
		}
		local_58.vy = ((cop->pos).vy - camera_position.vy) + y;
	}
	else {
		uVar2 = local_24 & 0xffff0000;
		local_24 = uVar2 | z & 0xffffU;
		setCopControlWord(2, 0, *(undefined4 *)(&matrixtable)[uVar3].m);
		setCopControlWord(2, 0x800, *(undefined4 *)((&matrixtable)[uVar3].m + 2));
		setCopControlWord(2, 0x1000, *(undefined4 *)((&matrixtable)[uVar3].m + 4));
		setCopControlWord(2, 0x1800, *(undefined4 *)((&matrixtable)[uVar3].m + 6));
		setCopControlWord(2, 0x2000, *(undefined4 *)((&matrixtable)[uVar3].m + 8));
		setCopReg(2, in_zero, x & 0xffffU | y << 0x10);
		setCopReg(2, in_at, local_24);
		copFunction(2, 0x486012);
		uVar3 = getCopReg(2, 0x4800);
		iVar4 = getCopReg(2, 0x5000);
		uVar5 = getCopReg(2, 0x5800);
		local_28 = uVar3 & 0xffff | iVar4 << 0x10;
		local_24 = uVar2 | uVar5 & 0xffff;
		local_58.vx = ((cop->pos).vx - camera_position.vx) + (int)(short)uVar3;
		local_58.vy = ((cop->pos).vy - camera_position.vy) + (int)(short)iVar4;
		local_24._0_2_ = (short)(uVar5 & 0xffff);
		local_58.vz = ((cop->pos).vz - camera_position.vz) + (int)(short)local_24;
	}
	if ((byte)colour == 1) {
		local_20[0].r = '\0';
		local_20[0].g = '(';
		local_20[0].b = '\0';
	}
	else {
		if ((byte)colour < 2) {
			if ((byte)colour == 0) {
				local_20[0].r = '(';
				local_20[0].g = '\n';
				local_20[0].b = '\0';
			}
		}
		else {
			if ((byte)colour == 2) {
				local_20[0].g = 'F';
				local_20[0].r = 'U';
				local_20[0].b = '\x05';
			}
			else {
				if ((byte)colour == 3) {
					local_20[0].g = '(';
					local_20[0].b = '#';
					local_20[0].r = '(';
				}
			}
		}
	}
	if ((byte)type == 1) {
		unaff_s1 = 300;
	}
	else {
		if ((byte)type < 2) {
			if ((byte)type == 0) {
				unaff_s1 = 400;
			}
		}
		else {
			if ((byte)type == 2) {
				unaff_s1 = 200;
			}
			else {
				if ((byte)type == 3) {
					unaff_s1 = 0x96;
				}
			}
		}
	}
	local_48.vx = local_58.vx;
	local_48.vz = local_58.vz;
	local_48.vy = MapHeight(&local_58);
	LightSortCorrect = -10;
	local_20[0].cd = '\0';
	local_48.vy = -camera_position.vy - local_48.vy;
	local_38 = local_58.vx;
	local_34 = local_58.vy;
	local_30 = local_58.vz;
	local_2c = local_58.pad;
	Apply_Inv_CameraMatrix(&local_58);
	setCopControlWord(2, 0x2800, local_58.vx);
	setCopControlWord(2, 0x3000, local_58.vy);
	setCopControlWord(2, 0x3800, local_58.vz);
	setCopControlWord(2, 0, norot.m[0]._0_4_);
	setCopControlWord(2, 0x800, norot.m._4_4_);
	setCopControlWord(2, 0x1000, norot.m[1]._2_4_);
	setCopControlWord(2, 0x1800, norot.m[2]._0_4_);
	setCopControlWord(2, 0x2000, norot._16_4_);
	ShowLight1(&local_58, local_20, (short)unaff_s1, &light_texture);
	DisplayLightReflections
	(&local_48, local_20, (short)((uint)(unaff_s1 << 0xd) >> 0x10), &lightref_texture);
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ PreLampStreak()
 // line 2178, offset 0x00034c6c
	/* begin block 1 */
		// Start line: 2180
		// Start offset: 0x00034C6C
		// Variables:
	// 		int count; // $a3
	/* end block 1 */
	// End offset: 0x00034D1C
	// End Line: 2198

	/* begin block 2 */
		// Start line: 5470
	/* end block 2 */
	// End Line: 5471

	/* begin block 3 */
		// Start line: 5474
	/* end block 3 */
	// End Line: 5475

	/* begin block 4 */
		// Start line: 5475
	/* end block 4 */
	// End Line: 5476

	/* begin block 5 */
		// Start line: 5477
	/* end block 5 */
	// End Line: 5478

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void PreLampStreak(void)
{
	int count;

	for (count = 0; count < 21 && StreakCount1 != 0; count++)
	{
		if (Known_Lamps[count].set == 0)
		{
			StreakCount1--;
			Known_Lamps[count].id = NewLamp[StreakCount1];
			Known_Lamps[count].clock = FrameCnt - 2;
		}
	}

	for (count = 0; count < 21; count++)
	{
		Known_Lamps[count].set = 0;
		NewLamp[count] = 0;
	}

	StreakCount1 = 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ find_lamp_streak(int LampId /*$a0*/)
 // line 2200, offset 0x00039b08
	/* begin block 1 */
		// Start line: 2201
		// Start offset: 0x00039B08
		// Variables:
	// 		int count; // $a1
	/* end block 1 */
	// End offset: 0x00039B78
	// End Line: 2217

	/* begin block 2 */
		// Start line: 10055
	/* end block 2 */
	// End Line: 10056

	/* begin block 3 */
		// Start line: 10531
	/* end block 3 */
	// End Line: 10532

	/* begin block 4 */
		// Start line: 10534
	/* end block 4 */
	// End Line: 10535

// [D]
int find_lamp_streak(int LampId)
{
	int count;

	for (count = 0; count < 21; count++)
	{
		if (Known_Lamps[0].id == LampId)
		{
			Known_Lamps[0].set = 1;
			return count;
		}
	}

	// allocate new streak
	if (StreakCount1 < 21)
		NewLamp[StreakCount1++] = LampId;

	return -1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ damage_lamp(struct CELL_OBJECT *cop /*$a2*/)
 // line 2230, offset 0x00034d1c
	/* begin block 1 */
		// Start line: 2231
		// Start offset: 0x00034D1C
		// Variables:
	// 		int count; // $v1
	// 		int old_damage; // $v0
	/* end block 1 */
	// End offset: 0x00034DAC
	// End Line: 2245

	/* begin block 2 */
		// Start line: 5557
	/* end block 2 */
	// End Line: 5558

	/* begin block 3 */
		// Start line: 5590
	/* end block 3 */
	// End Line: 5591

int damage_lamp(CELL_OBJECT *cop)
{
	UNIMPLEMENTED();
	return 0;
	/*
	byte bVar1;
	int iVar2;
	uint uVar3;
	DAMAGED_LAMP *pDVar4;

	iVar2 = 0;
	pDVar4 = &damaged_lamp;
	do {
		iVar2 = iVar2 + 1;
		if (cop == pDVar4->cop) {
			bVar1 = pDVar4->damage;
			uVar3 = 0;
			pDVar4->damage = bVar1 + 1;
			if (bVar1 < 3) {
				uVar3 = (uint)((byte)(bVar1 + 1) < 3) ^ 1;
			}
			return uVar3;
		}
		pDVar4 = pDVar4 + 1;
	} while (iVar2 < 4);
	iVar2 = NextDamagedLamp + 1;
	(&damaged_lamp)[NextDamagedLamp].damage = '\0';
	(&damaged_lamp)[NextDamagedLamp].cop = cop;
	NextDamagedLamp = iVar2;
	if (4 < iVar2) {
		NextDamagedLamp = 0;
	}
	return 0;*/
}



// decompiled code
// original method signature: 
// int /*$ra*/ damage_object(struct CELL_OBJECT *cop /*$s1*/, struct VECTOR *velocity /*$a1*/)
 // line 2255, offset 0x00034dac
	/* begin block 1 */
		// Start line: 2256
		// Start offset: 0x00034DAC
		// Variables:
	// 		struct DAMAGED_OBJECT *dam; // $s0

		/* begin block 1.1 */
			// Start line: 2256
			// Start offset: 0x00034DAC
			// Variables:
		// 		struct PACKED_CELL_OBJECT *pcop; // $a0
		/* end block 1.1 */
		// End offset: 0x00034DAC
		// End Line: 2256
	/* end block 1 */
	// End offset: 0x00034F64
	// End Line: 2318

	/* begin block 2 */
		// Start line: 5636
	/* end block 2 */
	// End Line: 5637

	/* begin block 3 */
		// Start line: 5647
	/* end block 3 */
	// End Line: 5648

	/* begin block 4 */
		// Start line: 5653
	/* end block 4 */
	// End Line: 5654

// [D]
int damage_object(CELL_OBJECT *cop, VECTOR *velocity)
{
	DAMAGED_OBJECT *dam;
	PACKED_CELL_OBJECT *pcop;

	dam = &damaged_object[NextDamagedPmeter];
	SmashablesHit++;
	NextDamagedPmeter++;

	dam->active = 1;
	dam->damage = 0;

	dam->cop = *cop; // copy

	dam->vx = cop->pos.vx;

	dam->velocity.vx = (velocity->vx >> 10);
	dam->velocity.vz = (velocity->vz >> 10);

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

	if (7 < NextDamagedPmeter)
		NextDamagedPmeter = 0;

	cop->pos.vx = 0xFD46FEC0;

	return 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddTrafficLight(struct CELL_OBJECT *cop /*$t4*/, int x /*$t6*/, int y /*$t7*/, int z /*$a3*/, int flag /*stack 16*/, int yang /*stack 20*/)
 // line 2326, offset 0x00034f64
	/* begin block 1 */
		// Start line: 2327
		// Start offset: 0x00034F64
		// Variables:
	// 		struct CVECTOR a; // stack offset -80
	// 		struct CVECTOR b; // stack offset -72
	// 		struct CVECTOR c; // stack offset -64
	// 		struct VECTOR v1; // stack offset -56
	// 		struct VECTOR v2; // stack offset -40
	// 		int lDiffAnglesX; // $s2
	// 		int lDiffAnglesY; // $s1
	// 		int AbsX; // $a2
	// 		int AbsY; // $a1
	// 		int tempfade; // $v0

		/* begin block 1.1 */
			// Start line: 2327
			// Start offset: 0x00034F64
			// Variables:
		// 		int c; // $t1
		// 		int s; // $t2
		/* end block 1.1 */
		// End offset: 0x00034F64
		// End Line: 2327
	/* end block 1 */
	// End offset: 0x000352B0
	// End Line: 2416

	/* begin block 2 */
		// Start line: 5809
	/* end block 2 */
	// End Line: 5810

	/* begin block 3 */
		// Start line: 5818
	/* end block 3 */
	// End Line: 5819

void AddTrafficLight(CELL_OBJECT *cop, int x, int y, int z, int flag, int yang)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	uint uVar3;
	int iVar4;
	int iVar5;
	CVECTOR local_50[2];
	CVECTOR local_48[2];
	byte local_40;
	byte local_3f;
	byte local_3e;
	VECTOR local_38;
	VECTOR local_28;

	uVar3 = (int)(short)yang & 0xfff;
	local_38.vy = ((cop->pos).vy - camera_position.vy) + y;
	local_38.vx = ((cop->pos).vx - camera_position.vx) +
		(rcossin_tbl[uVar3 * 2 + 1] * x + rcossin_tbl[uVar3 * 2] * z + 0x800 >> 0xc);
	local_38.vz = ((cop->pos).vz - camera_position.vz) +
		((rcossin_tbl[uVar3 * 2 + 1] * z - rcossin_tbl[uVar3 * 2] * x) + 0x800 >> 0xc);
	if ((flag & 0x200U) == 0) {
		if ((flag & 0x400U) != 0) {
			local_50[0].r = 0xff;
			local_50[0].g = 100;
			local_50[0].b = 0x23;
			goto LAB_00035098;
		}
		if ((flag & 0x800U) == 0) goto LAB_00035098;
		local_50[0].r = 0x19;
		local_50[0].g = 0xff;
	}
	else {
		local_50[0].r = 0xff;
		local_50[0].g = 0x19;
	}
	local_50[0].b = 0x19;
LAB_00035098:
	local_50[0].cd = '\0';
	iVar5 = ((int)camera_angle.vx + 0x800U & 0xfff) - 0x800;
	iVar1 = iVar5;
	if (iVar5 < 0) {
		iVar1 = -iVar5;
	}
	iVar4 = (((-(int)camera_angle.vy & 0xfffU) - (int)(short)yang) + 0x800 & 0xfff) - 0x800;
	iVar2 = iVar4;
	if (iVar4 < 0) {
		iVar2 = -iVar4;
	}
	if (iVar2 < 0x3e9) {
		local_40 = local_50[0].r;
		local_48[0].r = local_50[0].r >> 3;
		local_3e = local_50[0].b;
		local_48[0].b = local_50[0].b >> 3;
		local_3f = local_50[0].g;
		local_48[0].g = local_50[0].g >> 3;
		local_28.vx = local_38.vx;
		local_28.vz = local_38.vz;
		if (iVar1 + iVar2 < 1000) {
			iVar1 = 1000 - (iVar1 + iVar2);
			if (iVar1 < 0) {
				iVar1 = 0;
			}
			local_50[0].r = (byte)((int)((uint)local_50[0].r * iVar1) >> 10);
			LightSortCorrect = -0x8c;
			local_50[0].b = (byte)((int)((uint)local_50[0].b * iVar1) >> 10);
			local_50[0].g = (byte)((int)((uint)local_50[0].g * iVar1) >> 10);
			local_40 = local_50[0].r;
			local_3f = local_50[0].g;
			local_3e = local_50[0].b;
			LightIndex = find_lamp_streak((int)&(cop->pos).vx + y + x);
			if (LightIndex < 0) {
				local_50[0].cd = '\0';
			}
			else {
				local_50[0].cd = ' ';
			}
			ShowLight(&local_38, local_50, 0x1e, &light_texture);
			local_50[0].r = local_50[0].r >> 1;
			local_50[0].b = local_50[0].b >> 1;
			local_50[0].g = local_50[0].g >> 1;
			if (gNight != 0) {
				ShowFlare(&local_38, local_50, 0x96, iVar5 + iVar4 + local_38.vx + local_38.vz >> 3 & 0x1ffe);
			}
		}
		local_28.vy = MapHeight(&local_38);
		local_28.vy = -camera_position.vy - local_28.vy;
		if (gNight != 0) {
			ShowGroundLight(&local_28, local_48, 300);
		}
		DisplayLightReflections(&local_28, local_50, 100, &lightref_texture);
		LightSortCorrect = -10;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitFXPos(struct VECTOR *vec /*$a0*/, struct SVECTOR *svec /*$a1*/, struct _CAR_DATA *cp /*$a2*/)
 // line 2428, offset 0x00039c90
	/* begin block 1 */
		// Start line: 2429
		// Start offset: 0x00039C90
		// Variables:
	// 		struct SVECTOR svectmp; // stack offset -8
	/* end block 1 */
	// End offset: 0x00039D68
	// End Line: 2437

	/* begin block 2 */
		// Start line: 13201
	/* end block 2 */
	// End Line: 13202

	/* begin block 3 */
		// Start line: 4856
	/* end block 3 */
	// End Line: 4857

	/* begin block 4 */
		// Start line: 13202
	/* end block 4 */
	// End Line: 13203

// [D]
void InitFXPos(VECTOR *vec, SVECTOR *svec, _CAR_DATA *cp)
{
	SVECTOR svectmp;

	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	gte_SetRotMatrix(&cp->hd.drawCarMat);
	gte_SetTransVector(vec);

	gte_ldv0(svec);

	docop2(0x480012);

	gte_stlvnl(vec);
}



// decompiled code
// original method signature: 
// void /*$ra*/ FindCarLightFade(struct MATRIX *carToCamera /*$a0*/)
 // line 2447, offset 0x00039c68
	/* begin block 1 */
		// Start line: 2449
		// Start offset: 0x00039C68
		// Variables:
	// 		int zz; // $v0
	/* end block 1 */
	// End offset: 0x00039C90
	// End Line: 2452

	/* begin block 2 */
		// Start line: 4894
	/* end block 2 */
	// End Line: 4895

	/* begin block 3 */
		// Start line: 13214
	/* end block 3 */
	// End Line: 13215

int CarLightFadeBack = 0;
int CarLightFadeFront = 0;

// [D]
void FindCarLightFade(MATRIX *carToCamera)
{
	int zz;
	zz = carToCamera->m[2][2] / 4; //(carToCamera->m[2][2] << 0x10) >> 0x12;
	CarLightFadeFront = zz - 124;
	CarLightFadeBack = -124 - zz;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ShowCarlight(struct SVECTOR *v1 /*$s6*/, struct _CAR_DATA *cp /*$s3*/, struct CVECTOR *col /*$s1*/, short size /*$s5*/, struct TEXTURE_DETAILS *texture /*stack 16*/, int flag /*stack 20*/)
 // line 2462, offset 0x000352cc
	/* begin block 1 */
		// Start line: 2463
		// Start offset: 0x000352CC
		// Variables:
	// 		int CarLightFade; // $a1
	// 		struct VECTOR v1t; // stack offset -72
	// 		struct VECTOR v1l; // stack offset -56
	// 		struct CVECTOR flareCol; // stack offset -40
	// 		int front; // $a0
	/* end block 1 */
	// End offset: 0x00035534
	// End Line: 2514

	/* begin block 2 */
		// Start line: 6201
	/* end block 2 */
	// End Line: 6202

void ShowCarlight(SVECTOR *v1, _CAR_DATA *cp, CVECTOR *col, short size, TEXTURE_DETAILS *texture,int flag)
{
	int iVar1;
	VECTOR v1t;
	VECTOR v1l;
	CVECTOR flareCol;


	if (cp < car_data) {
		while (FrameCnt != 0x78654321) {
			trap(0x400);
		}
	}

	iVar1 = 255;

	if (flag == 0xFF)
		flag = 0;
	else
	{
		iVar1 = CarLightFadeBack;

		if ((flag & 1U) != 0) 
			iVar1 = CarLightFadeFront;

		if (iVar1 < 0) 
			return;
	}
	col->r = ((col->r * iVar1) >> 10);
	col->b = ((col->b * iVar1) >> 10);
	col->g = ((col->g * iVar1) >> 10);

	gte_SetRotMatrix(&cp->hd.drawCarMat);

	v1l.vx = cp->hd.where.t[0] - camera_position.vx;
	v1l.vy = -camera_position.vy - cp->hd.where.t[1];
	v1l.vz = cp->hd.where.t[2] - camera_position.vz;

	InitFXPos(&v1l, v1, cp);

	if (wetness > 9) 
	{
		v1t.vx = v1l.vx;
		v1t.vy = v1l.vy;
		v1t.vz = v1l.vz;

		v1t.pad = v1l.pad;

		v1t.vy = -camera_position.vy - MapHeight((VECTOR *)cp->hd.where.t);
	}

	col->cd = flag;

	ShowLight(&v1l, col, size, texture);

	flareCol.r = col->r >> 1;
	flareCol.g = col->g >> 1;
	flareCol.b = col->b >> 1;

	ShowFlare(&v1l, &flareCol, size * 3, (v1->vx + v1->vz >> 2) + (cp->hd.direction - camera_angle.vy) * 2);

	DisplayLightReflections(&v1t, col, size, &lightref_texture);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ShowLight1(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$a1*/, short size /*$a2*/, struct TEXTURE_DETAILS *texture /*$a3*/)
 // line 2523, offset 0x0003555c
	/* begin block 1 */
		// Start line: 2524
		// Start offset: 0x0003555C
		// Variables:
	// 		struct SVECTOR vert[4]; // stack offset -40
	// 		struct POLY_FT4 *poly; // $t0
	// 		int z; // stack offset -8
	/* end block 1 */
	// End offset: 0x00035748
	// End Line: 2575

	/* begin block 2 */
		// Start line: 6361
	/* end block 2 */
	// End Line: 6362

void ShowLight1(VECTOR *v1, CVECTOR *col, short size, TEXTURE_DETAILS *texture)
{
	UNIMPLEMENTED();
	/*
	uchar uVar1;
	uint uVar2;
	int iVar3;
	DB *pDVar4;
	undefined4 in_zero;
	undefined4 in_at;
	uint *puVar5;
	uint local_24;
	undefined4 local_20;
	uint local_1c;
	uint local_14;
	undefined4 local_10;
	uint local_c;
	int local_8;

	uVar2 = -(int)size;
	puVar5 = (uint *)current->primptr;
	local_c = local_c & 0xffff0000;
	local_14 = local_14 & 0xffff0000;
	local_1c = local_1c & 0xffff0000;
	local_24 = local_24 & 0xffff0000;
	local_20 = CONCAT22((short)uVar2, size);
	local_10 = CONCAT22(size, size);
	setCopReg(2, in_zero, uVar2 & 0xffff | (int)size * -0x10000);
	setCopReg(2, in_at, local_24);
	setCopReg(2, uVar2, local_20);
	setCopReg(2, current, local_1c);
	setCopReg(2, v1, uVar2 & 0xffff | (uint)(ushort)size << 0x10);
	setCopReg(2, col, local_14);
	copFunction(2, 0x280030);
	*(uchar *)(puVar5 + 3) = (texture->coords).u0;
	*(uchar *)((int)puVar5 + 0xd) = (texture->coords).v0;
	*(uchar *)(puVar5 + 5) = (texture->coords).u1;
	*(uchar *)((int)puVar5 + 0x15) = (texture->coords).v1;
	*(uchar *)(puVar5 + 7) = (texture->coords).u2;
	*(uchar *)((int)puVar5 + 0x1d) = (texture->coords).v2;
	*(uchar *)(puVar5 + 9) = (texture->coords).u3;
	uVar1 = (texture->coords).v3;
	*(char *)((int)puVar5 + 3) = '\t';
	*(char *)((int)puVar5 + 7) = '.';
	*(uchar *)((int)puVar5 + 0x25) = uVar1;
	*(uchar *)(puVar5 + 1) = col->r;
	*(uchar *)((int)puVar5 + 5) = col->g;
	*(uchar *)((int)puVar5 + 6) = col->b;
	uVar2 = getCopReg(2, 0xc);
	puVar5[2] = uVar2;
	uVar2 = getCopReg(2, 0xd);
	puVar5[4] = uVar2;
	uVar2 = getCopReg(2, 0xe);
	puVar5[6] = uVar2;
	iVar3 = getCopReg(2, 0x13);
	if (0x27 < iVar3) {
		setCopReg(2, in_zero, local_10);
		setCopReg(2, in_at, local_c);
		copFunction(2, 0x180001);
		*(ushort *)((int)puVar5 + 0x16) = texture->tpageid | 0x20;
		*(ushort *)((int)puVar5 + 0xe) = texture->clutid;
		local_8 = (iVar3 >> 3) + LightSortCorrect;
		if (local_8 < 0) {
			local_8 = 0;
		}
		uVar2 = getCopReg(2, 0xe);
		puVar5[8] = uVar2;
		pDVar4 = current;
		*puVar5 = *puVar5 & 0xff000000 | current->ot[local_8] & 0xffffff;
		pDVar4->ot[local_8] = pDVar4->ot[local_8] & 0xff000000 | (uint)puVar5 & 0xffffff;
		pDVar4->primptr = pDVar4->primptr + 0x28;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ShowLight(struct VECTOR *v1 /*$s0*/, struct CVECTOR *col /*$s3*/, short size /*$s4*/, struct TEXTURE_DETAILS *texture /*$s2*/)
 // line 2579, offset 0x00035750
	/* begin block 1 */
		// Start line: 2580
		// Start offset: 0x00035750
		// Variables:
	// 		struct SVECTOR vert[4]; // stack offset -88
	// 		struct POLY_FT4 *poly; // $s1
	// 		int z; // stack offset -40
	// 		int index; // $a1
	// 		int tail_width; // $s5

		/* begin block 1.1 */
			// Start line: 2644
			// Start offset: 0x00035A54
			// Variables:
		// 		int loop; // $a1
		/* end block 1.1 */
		// End offset: 0x00035AAC
		// End Line: 2650

		/* begin block 1.2 */
			// Start line: 2654
			// Start offset: 0x00035AD4
			// Variables:
		// 		struct POLY_G4 *poly1; // $s0
		// 		int dx; // $a0
		// 		int dy; // $v0
		// 		int angle; // $v0
		// 		int width; // $s2
		// 		int c; // $a0
		// 		int s; // $a2
		// 		int length; // $v0
		// 		struct SVECTOR tail; // stack offset -56
		// 		struct SVECTOR head; // stack offset -48
		/* end block 1.2 */
		// End offset: 0x00035EB8
		// End Line: 2709

		/* begin block 1.3 */
			// Start line: 2727
			// Start offset: 0x00035F68
			// Variables:
		// 		int loop; // $a3
		/* end block 1.3 */
		// End offset: 0x00035FE8
		// End Line: 2733

		/* begin block 1.4 */
			// Start line: 2737
			// Start offset: 0x00036024
			// Variables:
		// 		struct POLY_G4 *poly1; // $s0
		// 		int dx; // $a2
		// 		int dy; // $a1
		// 		int angle; // $v0
		// 		int width; // $s1
		// 		int c; // $a2
		// 		int s; // $a1
		// 		int length; // $v0
		// 		struct SVECTOR tail; // stack offset -56
		// 		struct SVECTOR head; // stack offset -48
		/* end block 1.4 */
		// End offset: 0x00036408
		// End Line: 2792
	/* end block 1 */
	// End offset: 0x00036408
	// End Line: 2794

	/* begin block 2 */
		// Start line: 6495
	/* end block 2 */
	// End Line: 6496

/* WARNING: Could not reconcile some variable overlaps */


// [D]
void ShowLight(VECTOR *v1, CVECTOR *col, short size, TEXTURE_DETAILS *texture)
{
	MATRIX norot;

	unsigned char uVar1;
	short sVar2;
	short sVar3;
	bool bVar4;
	short sVar6;
	long lVar7;
	unsigned char bVar8;
	short sVar9;
	VECTOR *pVVar10;
	LAMP_STREAK *pLVar11;
	short *puVar12;
	int y;
	short sVar13;
	CVECTOR *pCVar14;
	int iVar15;
	int iVar16;
	int x;
	uint uVar17;
	short *psVar18;
	int iVar19;
	POLY_FT3 *null;
	POLY_G4 *polys;
	POLY_FT4 *poly;
	int iVar20;
	int iVar21;
	SVECTOR vert[4];
	SVECTOR tail;
	SVECTOR head;
	int z;
	int index;

	pVVar10 = v1;
	pCVar14 = col;

	Apply_Inv_CameraMatrix(v1);

	gte_SetRotMatrix(&aspect);
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

	gte_stsz(&iVar21);

	// discard if too close
	if (iVar21 < 38)
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
	z = (iVar21 >> 3) + LightSortCorrect;

	if (z < 0)
		z = 0;

	if (z < 10000)
		iVar21 = (10000 - z) >> 0xd;
	else
		iVar21 = 0;

	addPrim(current->ot + z, poly);
	current->primptr += sizeof(POLY_FT4);

	if (CameraCnt > 4)
	{
		bVar8 = col->cd;
		index = -1;

		if ((bVar8 & 0x20) == 0 || gLightsOn == 0) 
		{
			if ((bVar8 & 2) == 0) 
			{
				if ((bVar8 & 4) == 0) 
				{
					if ((bVar8 & 8) == 0) 
					{
						if ((bVar8 & 0x10) != 0) 
						{
							index = 3;
						}
					}
					else 
					{
						index = 2;
					}
				}
				else 
				{
					index = 1;
				}
			}
			else 
			{
				index = 0;
			}
		}
		else 
		{
			if (CameraChanged == 0 && Known_Lamps[LightIndex].clock == (FrameCnt & 0xffffU) - 1)
			{
				sVar2 = Known_Lamps[LightIndex].light_trails[FrameCnt - 3U & 3].x;
				sVar3 = Known_Lamps[LightIndex].light_trails[FrameCnt - 3U & 3].y;

				iVar15 = (poly->x0 + poly->x3) / 2;

				sVar9 = iVar15;
				sVar13 = poly->y0;
				sVar6 = poly->y3;

				Known_Lamps[LightIndex].clock = FrameCnt;
				Known_Lamps[LightIndex].light_trails[FrameCnt & 3].x = sVar9;

				y = (sVar13 + sVar6) / 2;
					
				iVar15 = sVar2 - iVar15;

				if (iVar15 < 0)
					iVar15 = -iVar15;

				sVar13 = y;

				Known_Lamps[LightIndex].light_trails[FrameCnt & 3].y = sVar13;

				y = sVar3 - y;

				if (y < 0)
					y = -y;

				iVar16 = poly->x0 - poly->x3;
				if (iVar16 < 0)
					iVar16 = -iVar16;

				if (1 < size && iVar15 + y > 1)
				{
					polys = (POLY_G4 *)current->primptr;

					setPolyG4(polys);
					setSemiTrans(polys, 1);

					sVar6 = (poly->x0 + poly->x3) / 2;
					//polys->x1 = sVar6;
					//polys->x0 = sVar6;

					lVar7 = ratan2(sVar2 - sVar9,sVar3 - sVar13);

					if ((col->cd & 0x40) == 0) 
					{
						uVar17 = -lVar7 & 0xfff;
						iVar19 = rcossin_tbl[uVar17 * 2 + 1] * iVar16 * 3 >> 0xf;
						iVar16 = rcossin_tbl[uVar17 * 2] * iVar16 * 3 >> 0xf;
					}
					else 
					{
						uVar17 = -lVar7 & 0xfff;
						iVar19 = rcossin_tbl[uVar17 * 2 + 1] * iVar16 * 3 >> 0x10;
						iVar16 = rcossin_tbl[uVar17 * 2] * iVar16 * 3 >> 0x10;
					}

					polys->x0 = sVar9 + iVar19;
					polys->y0 = sVar13 + iVar16;

					polys->x1 = sVar9 - iVar19;
					polys->y1 = sVar13 - iVar16;

					polys->x2 = sVar2;
					polys->y2 = sVar3 - iVar21;

					polys->x3 = sVar2;
					polys->y3 = sVar3 + iVar21;

					//*(int *)&polys->x0 = (sVar13 + iVar16) * 0x10000 + sVar9 + iVar19;
					//*(int *)&polys->x1 = (sVar13 - iVar16) * 0x10000 + (sVar9 - iVar19);
					//*(int *)&polys->x2 = (sVar3 - iVar21) * 0x10000 + (int)sVar2;
					//*(int *)&polys->x3 = (sVar3 + iVar21) * 0x10000 + (int)sVar2;

					polys->r0 = col->r >> 1;
					polys->g0 = col->g >> 1;
					polys->b0 = col->b >> 1;
					polys->r1 = col->r >> 1;
					polys->g1 = col->g >> 1;
					bVar8 = col->b;
					polys->r2 = 0;
					polys->g2 = 0;
					polys->b2 = 0;
					polys->r3 = 0;
					polys->g3 = 0;
					polys->b3 = 0;
					polys->b1 = bVar8 >> 1;

					addPrim(current->ot + z, polys);
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
				iVar16 = 3;

				do {
					Known_Lamps[LightIndex].light_trails[iVar16].x = (poly->x0 + poly->x3) / 2;
					Known_Lamps[LightIndex].light_trails[iVar16].y = (poly->y0 + poly->y3) / 2;

					iVar16--;
				} while (-1 < iVar16);

				Known_Lamps[LightIndex].clock = FrameCnt;
			}
		}

		if (index > -1)
		{
			if (CameraChanged == 0 && car_data[gcar_num].ap.old_clock[index] == (FrameCnt & 0xffffU)-1)
			{
				sVar2 = car_data[gcar_num].ap.light_trails[index][FrameCnt - 3U & 3].x;
				sVar3 = car_data[gcar_num].ap.light_trails[index][FrameCnt - 3U & 3].y;

				y = (poly->x0 + poly->x3) / 2;
				sVar9 = y;
				sVar13 = poly->y0;
				sVar6 = poly->y3;
				y = sVar2 - y;

				car_data[gcar_num].ap.old_clock[index] = FrameCnt;
				x = (sVar13 + sVar6) / 2;
				car_data[gcar_num].ap.light_trails[index][FrameCnt & 3U].x = sVar9;

				iVar19 = y;
				if (y < 0)
					iVar19 = -y;

				sVar13 = x;
				car_data[gcar_num].ap.light_trails[index][FrameCnt & 3U].y = sVar13;

				x = sVar3 - x;
				iVar16 = poly->x0 - poly->x3;
				if (iVar16 < 0)
					iVar16 = -iVar16;

				iVar15 = x;
				if (x < 0)
					iVar15 = -x;
		
				if (size < 2)
					return;

				if (iVar19 + iVar15 < 2)
					return;

				polys = (POLY_G4 *)current->primptr;

				setPolyG4(polys);
				setSemiTrans(polys, 1);

				lVar7 = ratan2(y,x);
				iVar19 = rcossin_tbl[(-lVar7 & 0xfffU) * 2 + 1] * iVar16 * 3 >> 0xf;
				iVar20 = rcossin_tbl[(-lVar7 & 0xfffU) * 2] * iVar16 * 3 >> 0xf;

				polys->x0 = sVar9 + iVar19;
				polys->y0 = sVar13 + iVar20;

				polys->x1 = sVar9 - iVar19;
				polys->y1 = sVar13 - iVar20;

				polys->x2 = sVar2;
				polys->y2 = sVar3 - iVar21;

				polys->x3 = sVar2;
				polys->y3 = sVar3 + iVar21;

				//*(int *)&polys->x0 = (sVar13 + iVar20) * 0x10000 + sVar9 + iVar19;
				//*(int *)&polys->x1 = (sVar13 - iVar20) * 0x10000 + (sVar9 - iVar19);
				//*(int *)&polys->x2 = (sVar3 - iVar21) * 0x10000 + (int)sVar2;
				//*(int *)&polys->x3 = (sVar3 + iVar21) * 0x10000 + (int)sVar2;

				if ((col->cd & 0x18) == 0) 
				{
					polys->r0 = col->r;
					polys->g0 = col->g;
					polys->b0 = col->b;
					polys->r1 = col->r;
					polys->g1 = col->g;
					polys->b1 = col->b;
				}
				else 
				{
					polys->r0 = col->r >> 1;
					polys->g0 = col->g >> 1;
					polys->b0 = col->b >> 1;
					polys->r1 = col->r >> 1;
					polys->g1 = col->g >> 1;
					polys->b1 = col->b >> 1;
				}

				polys->r2 = 0;
				polys->g2 = 0;
				polys->b2 = 0;
				polys->r3 = 0;
				polys->g3 = 0;
				polys->b3 = 0;

				addPrim(current->ot + z, polys);
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
			else
			{
				iVar20 = 0;

				while (iVar20 < 4)
				{
					car_data[gcar_num].ap.light_trails[index][iVar20].x = (poly->x0 + poly->x3) / 2;
					car_data[gcar_num].ap.light_trails[index][iVar20].y = (poly->y0 + poly->y3) / 2;

					iVar20++;
				}

				car_data[gcar_num].ap.old_clock[index] = FrameCnt;
			 }
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ ShowGroundLight(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$a1*/, short size /*$a2*/)
 // line 2804, offset 0x0003642c
	/* begin block 1 */
		// Start line: 2805
		// Start offset: 0x0003642C
		// Variables:
	// 		struct SVECTOR vert[4]; // stack offset -40
	// 		struct POLY_FT4 *poly; // $t0
	// 		int z; // stack offset -8
	/* end block 1 */
	// End offset: 0x00036680
	// End Line: 2858

	/* begin block 2 */
		// Start line: 7136
	/* end block 2 */
	// End Line: 7137

// [D]
void ShowGroundLight(VECTOR *v1, CVECTOR *col, short size)
{
	POLY_FT4 *poly;
	SVECTOR vert[4];
	int z;

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

	if (z - 150 < 0x267b) 
	{
		poly = (POLY_FT4 *)current->primptr;

		setPolyFT4(poly);
		setSemiTrans(poly, 1);

		poly->u0 = light_texture.coords.u0;
		poly->v0 = light_texture.coords.v0;
		poly->u1 = light_texture.coords.u1;
		poly->v1 = light_texture.coords.v1;
		poly->u2 = light_texture.coords.u2;
		poly->v2 = light_texture.coords.v2;
		poly->u3 = light_texture.coords.u3;
		poly->v3 = light_texture.coords.v3;

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



// decompiled code
// original method signature: 
// void /*$ra*/ RoundShadow(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$a1*/, short size /*$a2*/)
 // line 2869, offset 0x00036688
	/* begin block 1 */
		// Start line: 2870
		// Start offset: 0x00036688
		// Variables:
	// 		struct SVECTOR vert[4]; // stack offset -40
	// 		struct POLY_FT4 *poly; // $t0
	// 		int z; // stack offset -8
	/* end block 1 */
	// End offset: 0x000368D0
	// End Line: 2933

	/* begin block 2 */
		// Start line: 7286
	/* end block 2 */
	// End Line: 7287

void RoundShadow(VECTOR *v1, CVECTOR *col, short size)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	DB *pDVar2;
	ushort uVar3;
	undefined4 in_zero;
	undefined4 in_at;
	uint uVar4;
	uint uVar5;
	uint uVar6;
	int iVar7;
	uint *puVar8;
	undefined4 local_28;
	uint local_24;
	uint local_1c;
	undefined4 local_18;
	uint local_14;
	uint local_c;

	iVar7 = (int)size;
	setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
	setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
	setCopControlWord(2, 0x2800, dummy.vx);
	setCopControlWord(2, 0x3000, dummy.vy);
	setCopControlWord(2, 0x3800, dummy.vz);
	uVar1 = *(ushort *)&v1->vy;
	size = *(ushort *)&v1->vx - size;
	uVar6 = iVar7 + (uint)*(ushort *)&v1->vz;
	uVar4 = iVar7 + (uint)*(ushort *)&v1->vx;
	uVar5 = (uint)*(ushort *)&v1->vz - iVar7;
	local_28 = CONCAT22(uVar1, size);
	local_24 = local_24 & 0xffff0000 | uVar6 & 0xffff;
	local_1c = local_1c & 0xffff0000 | uVar6 & 0xffff;
	local_18 = CONCAT22(uVar1, size);
	local_14 = local_14 & 0xffff0000 | uVar5 & 0xffff;
	local_c = local_c & 0xffff0000 | uVar5 & 0xffff;
	setCopReg(2, in_zero, local_28);
	setCopReg(2, in_at, local_24);
	setCopReg(2, uVar4, uVar4 & 0xffff | (uint)uVar1 << 0x10);
	setCopReg(2, uVar5, local_1c);
	setCopReg(2, uVar6, local_18);
	setCopReg(2, col, local_14);
	copFunction(2, 0x280030);
	puVar8 = (uint *)current->primptr;
	*(uchar *)(puVar8 + 3) = light_texture.coords.u0;
	*(uchar *)((int)puVar8 + 0xd) = light_texture.coords.v0;
	*(uchar *)(puVar8 + 5) = light_texture.coords.u1;
	*(uchar *)((int)puVar8 + 0x15) = light_texture.coords.v1;
	*(uchar *)(puVar8 + 7) = light_texture.coords.u2;
	*(uchar *)((int)puVar8 + 0x1d) = light_texture.coords.v2;
	*(uchar *)(puVar8 + 9) = light_texture.coords.u3;
	*(uchar *)((int)puVar8 + 0x25) = light_texture.coords.v3;
	*(ushort *)((int)puVar8 + 0x16) = light_texture.tpageid | 0x40;
	uVar3 = light_texture.clutid;
	*(char *)((int)puVar8 + 3) = '\t';
	*(char *)((int)puVar8 + 7) = '.';
	*(ushort *)((int)puVar8 + 0xe) = uVar3;
	*(uchar *)(puVar8 + 1) = col->r;
	*(uchar *)((int)puVar8 + 5) = col->g;
	*(uchar *)((int)puVar8 + 6) = col->b;
	iVar7 = getCopReg(2, 0x13);
	if (iVar7 - 0x96U < 0x267b) {
		uVar5 = getCopReg(2, 0xc);
		puVar8[2] = uVar5;
		uVar5 = getCopReg(2, 0xd);
		puVar8[4] = uVar5;
		uVar5 = getCopReg(2, 0xe);
		puVar8[6] = uVar5;
		pDVar2 = current;
		setCopReg(2, in_zero, uVar4 & 0xffff | (uint)uVar1 << 0x10);
		setCopReg(2, in_at, local_c);
		copFunction(2, 0x180001);
		*puVar8 = *puVar8 & 0xff000000 | current->ot[iVar7 >> 3] & 0xffffff;
		pDVar2->ot[iVar7 >> 3] = pDVar2->ot[iVar7 >> 3] & 0xff000000 | (uint)puVar8 & 0xffffff;
		pDVar2->primptr = pDVar2->primptr + 0x28;
		uVar4 = getCopReg(2, 0xe);
		puVar8[8] = uVar4;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ ShowFlare(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$s2*/, short size /*$a2*/, int rotation /*$a3*/)
 // line 2945, offset 0x000368d8
	/* begin block 1 */
		// Start line: 2946
		// Start offset: 0x000368D8
		// Variables:
	// 		struct SVECTOR vert[4]; // stack offset -96
	// 		struct POLY_FT4 *poly; // $t0
	// 		struct SVECTOR direction; // stack offset -64
	// 		struct MATRIX temp_matrix; // stack offset -56
	// 		int z; // stack offset -24
	/* end block 1 */
	// End offset: 0x00036B54
	// End Line: 3016

	/* begin block 2 */
		// Start line: 7488
	/* end block 2 */
	// End Line: 7489

/* WARNING: Could not reconcile some variable overlaps */

// [D]
void ShowFlare(VECTOR *v1, CVECTOR *col, short size, int rotation)
{
	POLY_FT4 *poly;
	SVECTOR vert[4];
	SVECTOR direction;
	MATRIX temp_matrix;
	int z;

	gte_SetTransVector(v1);

	direction.vy = 0;
	direction.vx = 0;
	direction.vz = rotation;

	RotMatrixXYZ(&temp_matrix, &direction);
#ifndef PSX
	MulMatrix0(&aspect, &temp_matrix, &temp_matrix);
#endif

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

	poly = (POLY_FT4 *)current->primptr;

	poly->u0 = flare_texture.coords.u0;
	poly->v0 = flare_texture.coords.v0;
	poly->u1 = flare_texture.coords.u1;
	poly->v1 = flare_texture.coords.v1;
	poly->u2 = flare_texture.coords.u2;
	poly->v2 = flare_texture.coords.v2-1;
	poly->u3 = flare_texture.coords.u3;
	poly->v3 = flare_texture.coords.v3-1;

	setPolyFT4(poly);
	setSemiTrans(poly, 1);

	poly->r0 = col->r >> 1;
	poly->g0 = col->g >> 1;
	poly->b0 = col->b >> 1;

	gte_stsz(&z);

	if (39 < z >> 3) 
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



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayWater(struct SMOKE *smoke /*$a0*/)
 // line 3029, offset 0x00036b6c
	/* begin block 1 */
		// Start line: 3030
		// Start offset: 0x00036B6C
		// Variables:
	// 		struct POLY_FT4 *poly; // $t1
	// 		struct VECTOR v; // stack offset -64
	// 		struct SVECTOR vert[4]; // stack offset -48
	// 		int size; // $t1
	// 		int z; // $v0
	// 		int z1; // stack offset -16
	// 		int z2; // stack offset -12
	// 		int z3; // stack offset -8
	// 		int z4; // stack offset -4
	/* end block 1 */
	// End offset: 0x00036E18
	// End Line: 3087

	/* begin block 2 */
		// Start line: 7696
	/* end block 2 */
	// End Line: 7697

	/* begin block 3 */
		// Start line: 7703
	/* end block 3 */
	// End Line: 7704

void DisplayWater(SMOKE *smoke)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	short sVar2;
	uint uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	DB *pDVar7;
	undefined4 in_zero;
	undefined4 in_at;
	ushort uVar8;
	int iVar9;
	uint uVar10;
	ushort uVar11;
	short sVar12;
	uint *puVar13;
	undefined4 local_30;
	uint local_2c;
	uint local_24;
	undefined4 local_20;
	uint local_1c;
	uint local_14;

	setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
	setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
	setCopControlWord(2, 0x2800, dummy.vx);
	setCopControlWord(2, 0x3000, dummy.vy);
	setCopControlWord(2, 0x3800, dummy.vz);
	sVar1 = smoke->start_w;
	uVar8 = *(ushort *)&(smoke->position).vx;
	sVar12 = (uVar8 - sVar1) - (ushort)camera_position.vx;
	uVar11 = 0x32 - (short)camera_position.vy;
	local_30 = CONCAT22(uVar11, sVar12);
	sVar2 = *(short *)&(smoke->position).vz;
	uVar10 = ((uint)uVar8 + (int)sVar1) - (uint)(ushort)camera_position.vx;
	local_20 = CONCAT22(uVar11, sVar12);
	uVar8 = (sVar2 + sVar1) - (ushort)camera_position.vz;
	local_2c = local_2c & 0xffff0000 | (uint)uVar8;
	local_24 = local_24 & 0xffff0000 | (uint)uVar8;
	uVar8 = (sVar2 - sVar1) - (ushort)camera_position.vz;
	local_1c = local_1c & 0xffff0000 | (uint)uVar8;
	local_14 = local_14 & 0xffff0000 | (uint)uVar8;
	puVar13 = (uint *)current->primptr;
	setCopReg(2, in_zero, local_30);
	setCopReg(2, in_at, local_2c);
	setCopReg(2, current, uVar10 & 0xffff | (uint)uVar11 << 0x10);
	setCopReg(2, &local_30, local_24);
	setCopReg(2, (uint)(ushort)camera_position.vz, local_20);
	setCopReg(2, uVar10, local_1c);
	copFunction(2, 0x280030);
	*(char *)((int)puVar13 + 7) = ',';
	*(char *)((int)puVar13 + 3) = '\t';
	*(char *)(puVar13 + 1) = (char)NightAmbient;
	*(char *)((int)puVar13 + 5) = (char)NightAmbient;
	*(char *)((int)puVar13 + 6) = (char)NightAmbient;
	*(ushort *)((int)puVar13 + 0x16) = sea_texture.tpageid;
	uVar3 = getCopReg(2, 0xc);
	puVar13[2] = uVar3;
	uVar3 = getCopReg(2, 0xd);
	puVar13[4] = uVar3;
	uVar3 = getCopReg(2, 0xe);
	puVar13[6] = uVar3;
	iVar9 = getCopReg(2, 0x11);
	iVar4 = getCopReg(2, 0x12);
	iVar5 = getCopReg(2, 0x13);
	setCopReg(2, in_zero, uVar10 & 0xffff | (uint)uVar11 << 0x10);
	setCopReg(2, in_at, local_14);
	copFunction(2, 0x180001);
	*(uchar *)(puVar13 + 3) = sea_texture.coords.u0;
	*(uchar *)((int)puVar13 + 0xd) = sea_texture.coords.v0;
	*(uchar *)(puVar13 + 5) = sea_texture.coords.u1;
	*(uchar *)((int)puVar13 + 0x15) = sea_texture.coords.v1;
	*(uchar *)(puVar13 + 7) = sea_texture.coords.u2;
	*(uchar *)((int)puVar13 + 0x1d) = sea_texture.coords.v2;
	*(uchar *)(puVar13 + 9) = sea_texture.coords.u3;
	*(uchar *)((int)puVar13 + 0x25) = sea_texture.coords.v3;
	*(ushort *)((int)puVar13 + 0xe) = sea_texture.clutid;
	pDVar7 = current;
	iVar6 = getCopReg(2, 0x13);
	iVar9 = iVar9 + iVar4 + iVar5 + iVar6 >> 5;
	if (iVar9 < 9) {
		iVar9 = 9;
	}
	*puVar13 = *puVar13 & 0xff000000 | current->ot[iVar9] & 0xffffff;
	pDVar7->ot[iVar9] = pDVar7->ot[iVar9] & 0xff000000 | (uint)puVar13 & 0xffffff;
	uVar3 = getCopReg(2, 0xe);
	puVar13[8] = uVar3;
	current->primptr = current->primptr + 0x28;
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplaySpark(struct SMOKE *spark /*$t1*/)
 // line 3102, offset 0x00036e18
	/* begin block 1 */
		// Start line: 3103
		// Start offset: 0x00036E18
		// Variables:
	// 		int z; // stack offset -8
	// 		struct SVECTOR v[3]; // stack offset -40
	// 		struct SVECTOR TrailPos; // stack offset -16
	// 		struct POLY_G3 *poly; // $t0

		/* begin block 1.1 */
			// Start line: 3135
			// Start offset: 0x00036F30
			// Variables:
		// 		unsigned char *col; // $a0
		/* end block 1.1 */
		// End offset: 0x00036FE0
		// End Line: 3150
	/* end block 1 */
	// End offset: 0x00037150
	// End Line: 3170

	/* begin block 2 */
		// Start line: 7865
	/* end block 2 */
	// End Line: 7866

	/* begin block 3 */
		// Start line: 7881
	/* end block 3 */
	// End Line: 7882

void DisplaySpark(SMOKE *spark)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	ushort uVar2;
	DB *pDVar3;
	undefined4 in_zero;
	undefined4 in_at;
	uint uVar4;
	undefined2 uVar5;
	int iVar6;
	short sVar7;
	uint *puVar8;
	undefined4 local_28;
	uint local_24;
	undefined4 local_20;
	uint local_1c;
	undefined4 local_18;
	uint local_14;
	int local_8;

	setCopControlWord(2, 0, inv_camera_matrix.m[0]._0_4_);
	setCopControlWord(2, 0x800, inv_camera_matrix.m._4_4_);
	setCopControlWord(2, 0x1000, inv_camera_matrix.m[1]._2_4_);
	setCopControlWord(2, 0x1800, inv_camera_matrix.m[2]._0_4_);
	setCopControlWord(2, 0x2000, inv_camera_matrix._16_4_);
	setCopControlWord(2, 0x2800, dummy.vx);
	setCopControlWord(2, 0x3000, dummy.vy);
	setCopControlWord(2, 0x3800, dummy.vz);
	local_18 = CONCAT22((spark->final_tail_pos).vy - (ushort)camera_position.vy,
		*(short *)&(spark->final_tail_pos).vx - (short)camera_position.vx);
	sVar7 = *(short *)&(spark->position).vx - (short)camera_position.vx;
	local_14 = local_14 & 0xffff0000 |
		(uint)(ushort)(*(short *)&(spark->final_tail_pos).vz - (ushort)camera_position.vz);
	iVar6 = (uint)(ushort)(spark->position).vy - (uint)(ushort)camera_position.vy;
	uVar4 = (uint)*(ushort *)&(spark->position).vz - (uint)(ushort)camera_position.vz;
	local_24 = local_24 & 0xffff0000 | uVar4 & 0xffff;
	uVar4 = uVar4 + 5;
	uVar5 = (undefined2)iVar6;
	local_28 = CONCAT22(uVar5, sVar7);
	local_20 = CONCAT22(uVar5, sVar7 + 5);
	local_1c = local_1c & 0xffff0000 | uVar4 & 0xffff;
	puVar8 = (uint *)current->primptr;
	setCopReg(2, in_zero, local_28);
	setCopReg(2, in_at, local_24);
	setCopReg(2, uVar4, local_20);
	setCopReg(2, iVar6, local_1c);
	setCopReg(2, current, local_18);
	setCopReg(2, 0x9bdc4, local_14);
	copFunction(2, 0x280030);
	*(char *)((int)puVar8 + 7) = '0';
	*(char *)((int)puVar8 + 3) = '\x06';
	if (spark->start_w == 2) {
		iVar6 = (int)(spark->drift).vy * 3;
		if (gTimeOfDay == 1) {
			*(uchar *)(puVar8 + 1) = (&grassColour)[iVar6];
			*(uchar *)((int)puVar8 + 5) = (&UCHAR_s_0009c2e9)[iVar6];
			*(uchar *)((int)puVar8 + 6) = s_C__0009c2ea[iVar6];
			*(uchar *)(puVar8 + 3) = (&grassColour)[iVar6];
			*(uchar *)((int)puVar8 + 0xd) = (&UCHAR_s_0009c2e9)[iVar6];
			*(uchar *)((int)puVar8 + 0xe) = s_C__0009c2ea[iVar6];
			iVar6 = ((int)(spark->drift).vy + 2U & 3) * 3;
			*(uchar *)(puVar8 + 5) = (&grassColour)[iVar6];
			*(uchar *)((int)puVar8 + 0x15) = (&UCHAR_s_0009c2e9)[iVar6];
			*(uchar *)((int)puVar8 + 0x16) = s_C__0009c2ea[iVar6];
		}
		else {
			*(char *)(puVar8 + 1) = '\0';
			*(char *)((int)puVar8 + 5) = (char)((ushort)spark->transparency >> 3);
			uVar2 = spark->transparency;
			*(char *)(puVar8 + 3) = '\0';
			*(char *)((int)puVar8 + 6) = (char)(uVar2 >> 4);
			*(char *)((int)puVar8 + 0xd) = (char)((ushort)spark->transparency >> 3);
			uVar2 = spark->transparency;
			*(char *)(puVar8 + 5) = '\f';
			*(char *)((int)puVar8 + 0x15) = '\x04';
			*(char *)((int)puVar8 + 0x16) = '\x04';
			*(char *)((int)puVar8 + 0xe) = (char)(uVar2 >> 4);
		}
	}
	else {
		*(char *)(puVar8 + 1) = *(char *)&spark->transparency;
		*(char *)((int)puVar8 + 5) = *(char *)&spark->transparency;
		*(char *)((int)puVar8 + 6) = (char)((ushort)spark->transparency >> 1);
		*(char *)(puVar8 + 3) = *(char *)&spark->transparency;
		*(char *)((int)puVar8 + 0xd) = *(char *)&spark->transparency;
		*(char *)((int)puVar8 + 0xe) = (char)((ushort)spark->transparency >> 1);
		cVar1 = *(char *)&spark->transparency;
		*(char *)((int)puVar8 + 0x15) = '\0';
		*(char *)((int)puVar8 + 0x16) = '\0';
		*(char *)(puVar8 + 5) = cVar1;
	}
	local_8 = getCopReg(2, 0x13);
	if (0x32 < local_8) {
		if (local_8 >> 3 < 9) {
			local_8 = 0x48;
		}
		uVar4 = getCopReg(2, 0xc);
		puVar8[2] = uVar4;
		uVar4 = getCopReg(2, 0xd);
		puVar8[4] = uVar4;
		uVar4 = getCopReg(2, 0xe);
		puVar8[6] = uVar4;
		pDVar3 = current;
		*puVar8 = *puVar8 & 0xff000000 | current->ot[local_8 >> 3] & 0xffffff;
		pDVar3->ot[local_8 >> 3] = pDVar3->ot[local_8 >> 3] & 0xff000000 | (uint)puVar8 & 0xffffff;
		pDVar3->primptr = pDVar3->primptr + 0x1c;
	}
	return;
	*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ GetSmokeDrift(struct VECTOR *Wind /*$t2*/)
 // line 3182, offset 0x00037158
	/* begin block 1 */
		// Start line: 3183
		// Start offset: 0x00037158
		// Variables:
	// 		static int SinTabIndex1; // offset 0x158
	// 		static int SinTabIndex2; // offset 0x15c
	// 		static int SinTabIndex3; // offset 0x160
	// 		static int WindMagnitude; // offset 0x164
	// 		static int SinX; // offset 0x0
	// 		static int CosX; // offset 0x4
	/* end block 1 */
	// End offset: 0x00037250
	// End Line: 3215

	/* begin block 2 */
		// Start line: 8067
	/* end block 2 */
	// End Line: 8068

	/* begin block 3 */
		// Start line: 8076
	/* end block 3 */
	// End Line: 8077

int SmokeCnt = 0;

// [D]
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
		CosX = rcossin_tbl[(SinTabIndex1 + 0x400 & 0xfff) * 2] + rcossin_tbl[(SinTabIndex2 + 0x400 & 0xfff) * 2];
		WindMagnitude = (rcossin_tbl[SinTabIndex3 * 2] << 0x10) >> 0x1b;
	}

	Wind->vy = 0;
	Wind->vx = FIXED(WindMagnitude * CosX);
	Wind->vz = FIXED(-WindMagnitude * SinX);
}



// decompiled code
// original method signature: 
// void /*$ra*/ Setup_Debris(struct VECTOR *ipos /*$fp*/, struct VECTOR *ispeed /*$s6*/, int num_debris /*$s7*/, int type /*$s5*/)
 // line 3227, offset 0x00037250
	/* begin block 1 */
		// Start line: 3228
		// Start offset: 0x00037250
		// Variables:
	// 		struct DEBRIS *mydebris; // $s1
	// 		int num; // $v1
	// 		int loop; // $s4
	// 		int vx; // $s2
	// 		int vy; // $s3
	// 		int vz; // $a2
	// 		int seed; // $s0
	// 		int col; // $a3

		/* begin block 1.1 */
			// Start line: 3245
			// Start offset: 0x000372F4
		/* end block 1.1 */
		// End offset: 0x000373B4
		// End Line: 3259
	/* end block 1 */
	// End offset: 0x00037444
	// End Line: 3285

	/* begin block 2 */
		// Start line: 8194
	/* end block 2 */
	// End Line: 8195

	/* begin block 3 */
		// Start line: 8207
	/* end block 3 */
	// End Line: 8208

void Setup_Debris(VECTOR *ipos, VECTOR *ispeed, int num_debris, int type)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte bVar2;
	byte bVar3;
	ushort uVar4;
	int iVar5;
	uint uVar6;
	uint uVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int iVar12;

	iVar9 = type >> 0x10;
	iVar12 = 0;
	if (0 < num_debris) {
		do {
			iVar5 = AllocateDebris();
			if (iVar5 == -1) {
				return;
			}
			debris[iVar5].position.vx = ipos->vx;
			debris[iVar5].position.vy = ipos->vy;
			debris[iVar5].position.vz = ipos->vz;
			if ((type & 0xffffU) < 8) {
				uVar6 = rand();
				iVar11 = (uVar6 & 0x7f00) * num_debris * 2;
				iVar10 = (ispeed->vx + ((uVar6 & 0x7f) - 0x40) * num_debris) * 0x400;
				uVar7 = rand();
				iVar8 = ispeed->vz;
				bVar1 = debris_colour[GameLevel * 0x1f + iVar9].r;
				bVar2 = debris_colour[GameLevel * 0x1f + iVar9].g;
				bVar3 = debris_colour[GameLevel * 0x1f + iVar9].b;
				debris[iVar5].step = (char)uVar6;
				debris[iVar5].rgb.r = bVar1;
				debris[iVar5].rgb.g = bVar2;
				debris[iVar5].rgb.b = bVar3;
				iVar8 = iVar8 + ((uVar7 & 0x7fff) - 0x4000) * num_debris * 2;
				if (gTimeOfDay == 3) {
					debris[iVar5].rgb.r = bVar1 >> 1;
					debris[iVar5].rgb.g = bVar2 >> 1;
					debris[iVar5].rgb.b = bVar3 >> 1;
				}
			}
			else {
				iVar11 = ispeed->vy;
				iVar10 = ispeed->vx;
				iVar8 = ispeed->vz;
				debris[iVar5].step = '\x02';
				debris[iVar5].rgb.b = '<';
				debris[iVar5].rgb.g = '<';
				debris[iVar5].rgb.r = '<';
			}
			uVar4 = (ushort)iVar12;
			iVar12 = iVar12 + 1;
			debris[iVar5].type = (byte)type & 7;
			debris[iVar5].direction.vy = -(short)(iVar11 >> 0xc);
			debris[iVar5].life = 0x80;
			debris[iVar5].direction.vx = (short)(iVar10 >> 0xc);
			debris[iVar5].direction.vz = (short)(iVar8 >> 0xc);
			debris[iVar5].flags = 2;
			debris[iVar5].pos = uVar4 & 0x1f;
		} while (iVar12 < num_debris);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ Setup_Smoke(struct VECTOR *ipos /*$s1*/, int start_w /*$s3*/, int end_w /*$s4*/, int SmokeType /*$s7*/, int WheelSpeed /*stack 16*/, struct VECTOR *Drift /*stack 20*/, int Exhaust /*stack 24*/)
 // line 3296, offset 0x00037474
	/* begin block 1 */
		// Start line: 3297
		// Start offset: 0x00037474
		// Variables:
	// 		struct SMOKE *mysmoke; // $s0
	// 		int num; // $v1

		/* begin block 1.1 */
			// Start line: 3335
			// Start offset: 0x00037594
		/* end block 1.1 */
		// End offset: 0x00037594
		// End Line: 3335

		/* begin block 1.2 */
			// Start line: 3372
			// Start offset: 0x000376A0
		/* end block 1.2 */
		// End offset: 0x000376A0
		// End Line: 3372

		/* begin block 1.3 */
			// Start line: 3382
			// Start offset: 0x000376EC
		/* end block 1.3 */
		// End offset: 0x00037728
		// End Line: 3387

		/* begin block 1.4 */
			// Start line: 3423
			// Start offset: 0x0003780C
		/* end block 1.4 */
		// End offset: 0x00037884
		// End Line: 3434
	/* end block 1 */
	// End offset: 0x00037920
	// End Line: 3463

	/* begin block 2 */
		// Start line: 8537
	/* end block 2 */
	// End Line: 8538

/* WARNING: Removing unreachable block (ram,0x0003778c) */

void Setup_Smoke(VECTOR *ipos, int start_w, int end_w, int SmokeType, int WheelSpeed, VECTOR *Drift, int Exhaust)
{
	UNIMPLEMENTED();
	/*
	char cVar1;
	byte bVar2;
	short sVar3;
	short sVar4;
	int iVar5;
	int iVar6;
	uint uVar7;
	SMOKE *pSVar8;
	short sVar9;

	iVar5 = AllocateSmoke();
	if (iVar5 == -1) {
		return;
	}
	pSVar8 = smoke + iVar5;
	sVar3 = (short)start_w;
	sVar9 = (short)end_w;
	if (SmokeType == 4) {
		(pSVar8->position).vx = ipos->vx;
		end_w = end_w - start_w;
		smoke[iVar5].position.vy = *(short *)&ipos->vy;
		iVar6 = ipos->vz;
		smoke[iVar5].start_w = sVar3;
		smoke[iVar5].final_w = sVar9;
		smoke[iVar5].position.vz = iVar6;
		iVar6 = end_w;
		if (end_w < 0) {
			iVar6 = end_w + 0x7f;
		}
		smoke[iVar5].step = (uchar)((iVar6 >> 7) << 2);
		smoke[iVar5].flags = 0x1006;
		smoke[iVar5].life = '\x14';
		smoke[iVar5].halflife = '\n';
		if (WheelSpeed < 0x30d41) {
			sVar3 = 0xff;
		}
		else {
			sVar3 = (short)(800000 - WheelSpeed >> 0xb);
		}
		smoke[iVar5].transparency = sVar3;
		smoke[iVar5].t_step = (uchar)(end_w >> 2);
	}
	else {
		if (SmokeType == 1) {
			if (Exhaust == 0) {
				(pSVar8->position).vx = ipos->vx;
				smoke[iVar5].position.vy = *(short *)&ipos->vy;
				smoke[iVar5].position.vz = ipos->vz;
				if (WheelSpeed < 0x30d41) {
					sVar4 = 0xff;
				}
				else {
					sVar4 = (short)(800000 - WheelSpeed >> 0xb);
				}
				smoke[iVar5].transparency = sVar4;
				end_w = end_w - start_w;
				smoke[iVar5].t_step = (uchar)(end_w >> 5);
			}
			else {
				uVar7 = rand();
				(pSVar8->position).vx = ipos->vx + (uVar7 & 0x3f);
				smoke[iVar5].position.vy = *(short *)&ipos->vy;
				uVar7 = rand();
				end_w = end_w - start_w;
				iVar6 = ipos->vz;
				smoke[iVar5].flags = 0x2006;
				smoke[iVar5].transparency = 0x8c;
				smoke[iVar5].t_step = '\x02';
				smoke[iVar5].position.vz = iVar6 + (uVar7 & 0x3f);
			}
			smoke[iVar5].start_w = sVar3;
			smoke[iVar5].final_w = sVar9;
			if (end_w < 0) {
				end_w = end_w + 0x7f;
			}
			smoke[iVar5].step = (uchar)((end_w >> 7) << 2);
			smoke[iVar5].flags = 0x2006;
			smoke[iVar5].life = '(';
			smoke[iVar5].halflife = '\x14';
		}
		else {
			if ((SmokeType == 2) || (SmokeType == 5)) {
				if (Exhaust == 0) {
					uVar7 = rand();
					(pSVar8->position).vx = ipos->vx + (uVar7 & 0x3f);
					smoke[iVar5].position.vy = *(short *)&ipos->vy;
					uVar7 = rand();
					iVar6 = ipos->vz;
					smoke[iVar5].flags = 0x16;
					smoke[iVar5].position.vz = iVar6 + (uVar7 & 0x3f);
				}
				else {
					uVar7 = rand();
					(pSVar8->position).vx = ipos->vx + (uVar7 & 7);
					smoke[iVar5].position.vy = *(short *)&ipos->vy;
					uVar7 = rand();
					iVar6 = ipos->vz;
					smoke[iVar5].flags = 0x4006;
					smoke[iVar5].transparency = 0x46;
					smoke[iVar5].t_step = '\x02';
					smoke[iVar5].position.vz = iVar6 + (uVar7 & 7);
				}
				smoke[iVar5].start_w = sVar3;
				smoke[iVar5].final_w = sVar9;
				if (SmokeType == 5) {
					smoke[iVar5].life = ' ';
					end_w = end_w - start_w;
					iVar6 = end_w;
					if (end_w < 0) {
						iVar6 = end_w + 0x1f;
					}
					smoke[iVar5].step = (uchar)((iVar6 >> 5) << 2);
					smoke[iVar5].t_step = (uchar)(end_w >> 5);
					smoke[iVar5].transparency = (short)WheelSpeed;
				}
				else {
					smoke[iVar5].life = -0x80;
					smoke[iVar5].step = (uchar)((end_w - start_w) / 0x80 << 3);
					smoke[iVar5].t_step = (uchar)(end_w - start_w >> 6);
					smoke[iVar5].transparency = 0x50;
				}
			}
			else {
				if (SmokeType == 6) {
					(pSVar8->position).vx = ipos->vx;
					smoke[iVar5].position.vy = *(short *)&ipos->vy;
					iVar6 = ipos->vz;
					smoke[iVar5].flags = 0x46;
					smoke[iVar5].transparency = 0xa0;
					smoke[iVar5].step = '\x14';
					smoke[iVar5].t_step = '\x05';
					smoke[iVar5].start_w = sVar3;
					smoke[iVar5].final_w = sVar9;
					smoke[iVar5].life = -0x4e;
					smoke[iVar5].halflife = ' ';
					smoke[iVar5].position.vz = iVar6;
					goto LAB_00037884;
				}
				uVar7 = rand();
				(pSVar8->position).vx = ipos->vx + (uVar7 & 0x3f);
				smoke[iVar5].position.vy = *(short *)&ipos->vy;
				uVar7 = rand();
				end_w = end_w - start_w;
				iVar6 = ipos->vz;
				smoke[iVar5].flags = 0x26;
				smoke[iVar5].transparency = 0x3c;
				smoke[iVar5].t_step = '\x05';
				smoke[iVar5].start_w = sVar3;
				smoke[iVar5].final_w = sVar9;
				smoke[iVar5].position.vz = iVar6 + (uVar7 & 0x3f);
				if (end_w < 0) {
					end_w = end_w + 0x7f;
				}
				smoke[iVar5].step = (uchar)((end_w >> 7) << 3);
				smoke[iVar5].life = -0x80;
			}
			smoke[iVar5].halflife = '@';
		}
	}
LAB_00037884:
	if (Exhaust == 0) {
		bVar2 = smoke[iVar5].life;
		smoke[iVar5].drift.vx = '\0';
		smoke[iVar5].drift.vy = '\0';
		smoke[iVar5].drift.vz = '\0';
		if ((bVar2 < 0x28) || (SmokeType == 4)) {
			smoke[iVar5].drift_change.vx = '\0';
			smoke[iVar5].drift_change.vy = '\x01';
			smoke[iVar5].drift_change.vz = '\0';
		}
		else {
			smoke[iVar5].drift_change.vx = *(char *)&Drift->vx;
			smoke[iVar5].drift_change.vy = *(char *)&Drift->vy;
			smoke[iVar5].drift_change.vz = *(char *)&Drift->vz;
		}
	}
	else {
		smoke[iVar5].drift.vx = *(char *)&Drift->vx;
		smoke[iVar5].drift.vy = *(char *)&Drift->vy;
		cVar1 = *(char *)&Drift->vz;
		smoke[iVar5].drift_change.vx = '\0';
		smoke[iVar5].drift_change.vy = '\0';
		smoke[iVar5].drift_change.vz = '\0';
		smoke[iVar5].drift.vz = cVar1;
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ Setup_Sparks(struct VECTOR *ipos /*$fp*/, struct VECTOR *ispeed /*$s7*/, int num_sparks /*stack 8*/, char SparkType /*$s5*/)
 // line 3475, offset 0x00037950
	/* begin block 1 */
		// Start line: 3476
		// Start offset: 0x00037950
		// Variables:
	// 		struct SMOKE *mysmoke; // $s2
	// 		int num; // $s0
	// 		int loop; // $s4
	// 		int vx; // $s1
	// 		int vy; // $s0
	// 		int vz; // $v1
	// 		int randtemp; // $v0

		/* begin block 1.1 */
			// Start line: 3487
			// Start offset: 0x000379A0
		/* end block 1.1 */
		// End offset: 0x00037AD0
		// End Line: 3549
	/* end block 1 */
	// End offset: 0x00037AE4
	// End Line: 3550

	/* begin block 2 */
		// Start line: 9001
	/* end block 2 */
	// End Line: 9002

	/* begin block 3 */
		// Start line: 9007
	/* end block 3 */
	// End Line: 9008

void Setup_Sparks(VECTOR *ipos, VECTOR *ispeed, int num_sparks, char SparkType)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	int iVar2;
	uint uVar3;
	uint uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	if ((pauseflag == 0) && (iVar8 = 0, 0 < num_sparks)) {
		do {
			iVar2 = AllocateSmoke();
			if (iVar2 < 0) {
				return;
			}
			uVar3 = rand();
			iVar5 = ipos->vx;
			smoke[iVar2].position.vx = iVar5;
			sVar1 = *(short *)&ipos->vy;
			smoke[iVar2].position.vy = sVar1;
			iVar6 = ipos->vz;
			smoke[iVar2].final_tail_pos.vy = sVar1;
			smoke[iVar2].pos = (uchar)(iVar8 << 2);
			smoke[iVar2].step = (byte)uVar3 & 0x3f;
			smoke[iVar2].final_tail_pos.vx = iVar5;
			smoke[iVar2].drift.vx = '\x02';
			smoke[iVar2].flags = 10;
			smoke[iVar2].position.vz = iVar6;
			smoke[iVar2].final_tail_pos.vz = iVar6;
			iVar7 = ispeed->vx;
			iVar6 = ispeed->vy;
			uVar4 = rand();
			iVar5 = ispeed->vz;
			smoke[iVar2].drift_change.vx = (char)((int)((iVar7 + -0x4000 + (uVar3 & 0x7f00)) * 4) >> 0xc);
			smoke[iVar2].drift_change.vy = -(char)((int)((iVar6 + (uVar3 & 0x7f)) * 0x400) >> 0xc);
			smoke[iVar2].drift_change.vz = (char)(iVar5 + -0x40 + (uVar4 & 0x7f) >> 2);
			if (SparkType == '\x01') {
				smoke[iVar2].life = '\n';
				smoke[iVar2].transparency = 200;
				smoke[iVar2].t_step = '\x02';
				smoke[iVar2].start_w = 0;
			}
			else {
				if (SparkType == '\x02') {
					smoke[iVar2].life = '\n';
					smoke[iVar2].transparency = 0xff;
					smoke[iVar2].t_step = '\n';
					smoke[iVar2].start_w = 2;
					iVar5 = rand();
					smoke[iVar2].drift.vy = (byte)iVar5 & 3;
				}
				else {
					smoke[iVar2].life = '(';
					smoke[iVar2].transparency = 0xff;
					smoke[iVar2].t_step = '\n';
					smoke[iVar2].start_w = 1;
				}
			}
			iVar8 = iVar8 + 1;
		} while (iVar8 < num_sparks);
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayDebris(struct DEBRIS *debris /*$t2*/, char type /*$t3*/)
 // line 3564, offset 0x00037b14
	/* begin block 1 */
		// Start line: 3565
		// Start offset: 0x00037B14
		// Variables:
	// 		int pos; // $a1
	// 		int z; // stack offset -8
	// 		struct SVECTOR v[4]; // stack offset -56
	// 		struct TRI_POINT *tv; // $t1
	// 		struct VECTOR debrisvec; // stack offset -24
	// 		struct POLY_FT3 *poly; // $t0
	// 		struct POLY_GT4 *poly1; // $t0

		/* begin block 1.1 */
			// Start line: 3607
			// Start offset: 0x00037D94
			// Variables:
		// 		unsigned long cbgr; // $v1
		/* end block 1.1 */
		// End offset: 0x00037E10
		// End Line: 3618
	/* end block 1 */
	// End offset: 0x00038000
	// End Line: 3648

	/* begin block 2 */
		// Start line: 9290
	/* end block 2 */
	// End Line: 9291

void DisplayDebris(DEBRIS *debris, char type)
{
	UNIMPLEMENTED();
	/*
	DB *pDVar1;
	undefined4 in_zero;
	undefined4 in_at;
	uint uVar2;
	uint uVar3;
	int iVar4;
	uint *puVar5;
	char *pcVar6;
	undefined4 local_38;
	uint local_34;
	undefined4 local_30;
	uint local_2c;
	undefined4 local_28;
	uint local_24;
	undefined4 local_20;
	uint local_1c;
	short local_18;
	short local_14;
	short local_10;

	iVar4 = (debris->position).vx - camera_position.vx;
	uVar2 = (debris->position).vy - camera_position.vy;
	uVar3 = (debris->position).vz - camera_position.vz;
	if ((((iVar4 < -10000) || ((int)uVar3 < -10000)) || (10000 < iVar4)) || (10000 < (int)uVar3)) {
		debris->life = 1;
	}
	else {
		pcVar6 = debris_rot_table5[(byte)debris->type] + ((int)(uint)debris->pos >> 3 & 0x1fU) * 0xc;
		local_18 = (short)iVar4;
		local_14 = (short)uVar2;
		local_38 = CONCAT22(pcVar6[1] + local_14, *pcVar6 + local_18);
		local_10 = (short)uVar3;
		uVar3 = uVar3 & 0xffff;
		local_34 = local_34 & 0xffff0000 | (int)pcVar6[2] + uVar3 & 0xffff;
		local_30 = CONCAT22(pcVar6[5] + local_14, pcVar6[4] + local_18);
		local_2c = local_2c & 0xffff0000 | (uint)(ushort)(pcVar6[6] + local_10);
		iVar4 = (int)pcVar6[9] + (uVar2 & 0xffff);
		local_28 = CONCAT22((short)iVar4, pcVar6[8] + local_18);
		local_24 = local_24 & 0xffff0000 | (int)pcVar6[10] + uVar3 & 0xffff;
		setCopReg(2, in_zero, local_38);
		setCopReg(2, in_at, local_34);
		setCopReg(2, iVar4, local_30);
		setCopReg(2, (int)pcVar6[10] + uVar3, local_2c);
		setCopReg(2, (int)pcVar6[2] + uVar3, local_28);
		setCopReg(2, uVar3, local_24);
		copFunction(2, 0x280030);
		if ((uint)(byte)type - 1 < 2) {
			puVar5 = (uint *)current->primptr;
			local_20 = CONCAT22(local_14 - pcVar6[1], local_18 - *pcVar6);
			local_1c = local_1c & 0xffff0000 | (uint)(ushort)(local_10 - pcVar6[2]);
			puVar5[3] = CONCAT22(litter_texture.clutid, litter_texture.coords._0_2_);
			puVar5[6] = CONCAT22(litter_texture.tpageid, litter_texture.coords._2_2_);
			puVar5[9] = (uint)litter_texture.coords._4_2_;
			puVar5[0xc] = (uint)litter_texture.coords._6_2_;
			uVar2 = getCopReg(2, 0xc);
			puVar5[2] = uVar2;
			uVar2 = getCopReg(2, 0xd);
			puVar5[5] = uVar2;
			uVar2 = getCopReg(2, 0xe);
			puVar5[8] = uVar2;
			iVar4 = getCopReg(2, 0x13);
			if (0xdf < iVar4) {
				setCopReg(2, in_zero, local_20);
				setCopReg(2, in_at, local_1c);
				copFunction(2, 0x180001);
				uVar2 = (uint)(byte)combointensity;
				if (type == '\x02') {
					uVar2 = ((debris->rgb).b + uVar2) * 0x10000 |
						((debris->rgb).g + uVar2) * 0x100 | 0x3c000000 | (debris->rgb).r + uVar2;
				}
				else {
					uVar2 = (uint)(debris->rgb).b << 0x10 | (uint)(debris->rgb).g << 8 | 0x3c000000 |
						(uint)(debris->rgb).r;
				}
				puVar5[1] = uVar2;
				puVar5[7] = uVar2;
				puVar5[4] = uVar2 + 0x202020;
				puVar5[10] = uVar2 + 0x303030;
				*(char *)((int)puVar5 + 3) = '\f';
				pDVar1 = current;
				*puVar5 = *puVar5 & 0xff000000 | current->ot[iVar4 >> 3] & 0xffffff;
				pDVar1->ot[iVar4 >> 3] = pDVar1->ot[iVar4 >> 3] & 0xff000000 | (uint)puVar5 & 0xffffff;
				uVar2 = getCopReg(2, 0xe);
				puVar5[0xb] = uVar2;
				*(uint **)&current->primptr = puVar5 + 0xd;
			}
		}
		else {
			puVar5 = (uint *)current->primptr;
			*(char *)((int)puVar5 + 3) = '\a';
			*(char *)((int)puVar5 + 7) = '$';
			*(uchar *)(puVar5 + 3) = debris_texture.coords.u0;
			*(uchar *)((int)puVar5 + 0xd) = debris_texture.coords.v0;
			*(uchar *)(puVar5 + 5) = debris_texture.coords.u1;
			*(uchar *)((int)puVar5 + 0x15) = debris_texture.coords.v1;
			*(uchar *)(puVar5 + 7) = debris_texture.coords.u2;
			*(uchar *)((int)puVar5 + 0x1d) = debris_texture.coords.v2;
			uVar2 = getCopReg(2, 0xc);
			puVar5[2] = uVar2;
			uVar2 = getCopReg(2, 0xd);
			puVar5[4] = uVar2;
			uVar2 = getCopReg(2, 0xe);
			puVar5[6] = uVar2;
			iVar4 = getCopReg(2, 0x13);
			*(uchar *)(puVar5 + 1) = (debris->rgb).r;
			*(uchar *)((int)puVar5 + 5) = (debris->rgb).g;
			*(uchar *)((int)puVar5 + 6) = (debris->rgb).b;
			*(ushort *)((int)puVar5 + 0x16) = debris_texture.tpageid;
			*(ushort *)((int)puVar5 + 0xe) = debris_texture.clutid;
			pDVar1 = current;
			if (0xdf < iVar4) {
				*puVar5 = *puVar5 & 0xff000000 | current->ot[iVar4 >> 3] & 0xffffff;
				pDVar1->ot[iVar4 >> 3] = pDVar1->ot[iVar4 >> 3] & 0xff000000 | (uint)puVar5 & 0xffffff;
				pDVar1->primptr = pDVar1->primptr + 0x20;
			}
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ HandleDebris()
 // line 3659, offset 0x00038008
	/* begin block 1 */
		// Start line: 3661
		// Start offset: 0x00038008
		// Variables:
	// 		int count; // $s0
	// 		int i; // $s3
	// 		struct DEBRIS *lpDebris; // $s1
	// 		struct SMOKE *smokeptr; // $s0
	// 		struct VECTOR dummy; // stack offset -80
	// 		struct LEAF *lpLeaf; // $s1
	// 		int Height; // $v0
	// 		int SinX; // $s2
	// 		int CosX; // $v1
	// 		struct VECTOR Drift; // stack offset -64

		/* begin block 1.1 */
			// Start line: 3852
			// Start offset: 0x0003841C
			// Variables:
		// 		int offshore; // $s1
		// 		struct ROUTE_DATA routeData; // stack offset -48
		/* end block 1.1 */
		// End offset: 0x000384B4
		// End Line: 3864

		/* begin block 1.2 */
			// Start line: 3953
			// Start offset: 0x000386F0
			// Variables:
		// 		static int weather_level; // offset 0x168
		/* end block 1.2 */
		// End offset: 0x00038750
		// End Line: 3966
	/* end block 1 */
	// End offset: 0x0003877C
	// End Line: 3967

	/* begin block 2 */
		// Start line: 9541
	/* end block 2 */
	// End Line: 9542

	/* begin block 3 */
		// Start line: 9542
	/* end block 3 */
	// End Line: 9543

	/* begin block 4 */
		// Start line: 9545
	/* end block 4 */
	// End Line: 9546

/* WARNING: Unknown calling convention yet parameter storage is locked */

int NoRainIndoors = 0;

// [D]
void HandleDebris(void)
{
	unsigned char bVar1;
	unsigned char bVar2;
	char cVar3;
	char cVar4;
	short sVar5;
	short sVar6;
	short sVar7;
	char cVar8;
	ushort uVar9;
	short sVar10;
	uint uVar11;
	char cVar12;
	uint uVar13;
	int iVar14;
	int iVar15;
	int iVar16;
	SMOKE *sm;
	DEBRIS *db;
	LEAF *lf;
	int iVar17;
	VECTOR dummy;
	VECTOR Drift;
	ROUTE_DATA routeData;

	memset(&dummy, 0, 0x10);
	iVar17 = 0;
	GetSmokeDrift(&Drift);
	MoveHubcap();
	SetRotMatrix(&inv_camera_matrix);

	gte_SetTransVector(&dummy);

	if (next_debris != 0) 
	{
		db = db;
		iVar16 = next_debris;
		if (pauseflag == 0)
		{
			do {
				if ((db->flags & 2) != 0) 
				{
					DisplayDebris(db, 0);
					uVar9 = db->life - 1;
					db->life = uVar9;

					if ((uVar9 == 0) || (iVar15 = (db->position).vy, 0 < iVar15)) 
					{
						db->flags = 0;
						ReleaseDebris(db->num);
						iVar16 = iVar16 + -1;
					}
					else
					{
						sVar5 = db->direction.vy;
						sVar10 = db->direction.vz;
						db->position.vx = db->position.vx + db->direction.vx;
						bVar1 = db->step;
						db->position.vy = iVar15 + sVar5;
						uVar9 = db->pos;
						db->position.vz = db->position.vz + sVar10;
						db->pos = uVar9 + bVar1;
						sVar5 = db->direction.vy;
						sVar10 = sVar5 + 6;

						if (db->type == 3) 
							sVar10 = sVar5 + 1;

						db->direction.vy = sVar10;
						iVar16 = iVar16 + -1;
					}
				}
				db = db + 1;
			} while (iVar16 != 0);
		}
		else 
		{
			do {
				if ((db->flags & 2) != 0) 
				{
					DisplayDebris(db, 0);
					iVar16 = iVar16 + -1;
				}
				db = db + 1;
			} while (iVar16 != 0);
		}
	}

	if (next_leaf != 0) 
	{
		lf = leaf;
		iVar16 = next_leaf;
		if (pauseflag == 0) {
			do {
				if ((lf->flags & 2) != 0) {
					if (lf->life == 1) {
						lf->flags = 0;
						ReleaseLeaf(lf->num);
					}
					else
					{
						if (pauseflag == 0) 
						{
							uVar13 = lf->sin_index1 + lf->sin_addition1 & 0xfff;
							uVar11 = lf->sin_index2 + lf->sin_addition2 & 0xfff;
							sVar5 = rcossin_tbl[uVar13 * 2];
							sVar10 = rcossin_tbl[uVar11 * 2];
							lf->sin_index1 = (short)uVar13;
							lf->sin_index2 = (short)uVar11;
							sVar6 = rcossin_tbl[uVar13 * 2 + 1];
							sVar7 = rcossin_tbl[uVar11 * 2 + 1];
							iVar17 = (int)sVar5 + (int)sVar10;
							(lf->direction).vx = (short)(iVar17 * 5 >> 0xb);
							(lf->direction).vz =
								(short)(((int)sVar6 + (int)sVar7) * 5 >> 0xb);
						}

						GetSmokeDrift(&Drift);
						iVar14 = lf->position.vy;
						iVar15 = -((lf->position).pad + 0x14);

						if (iVar14 < iVar15) 
						{
							sVar5 = (lf->direction).vy;
							sVar10 = (lf->direction).vz;
							lf->position.vx = lf->position.vx + lf->direction.vx + Drift.vx;
							lf->position.vy = iVar14 + sVar5 + Drift.vy;
							uVar9 = lf->pos;
							bVar1 = lf->step;
							(lf->position).vz = (lf->position).vz + sVar10 + Drift.vz;
							lf->pos = uVar9 + bVar1 & 0xff;
						}
						else
						{
							lf->position.vy = iVar15;
						}

						lf->direction.vy = (iVar17 >> 0xb) + 4;
					}

					iVar16 = iVar16 + -1;
					DisplayDebris((DEBRIS *)lf, lf->type);
				}
				lf = lf + 1;
			} while (iVar16 != 0);
		}
		else {
			do {
				if ((lf->flags & 2) != 0) {
					iVar16 = iVar16 + -1;
					DisplayDebris((DEBRIS *)lf, lf->type);
				}
				lf = lf + 1;
			} while (iVar16 != 0);
		}
	}

	sm = smoke;
	iVar17 = 79;

	/*
	norot.m[0][0] = 0x1000;
	norot.m[1][0] = 0;
	norot.m[2][0] = 0;
	norot.m[0][1] = 0;
	norot.m[1][1] = 0x1000;
	norot.m[2][1] = 0;
	norot.m[0][2] = 0;
	norot.m[1][2] = 0;
	norot.m[2][2] = 0x1000;
	*/

	do {
		uVar9 = sm->flags;
		if ((uVar9 & 2) != 0) 
		{
			if ((uVar9 & 4) == 0)
			{
				if (((uVar9 & 8) != 0) && (DisplaySpark(sm), pauseflag == 0))
				{
					cVar12 = (sm->drift_change).vy;
					iVar16 = (int)(sm->drift_change).vx;
					iVar15 = (int)(sm->drift_change).vz;
					(sm->position).vx = (sm->position).vx + iVar16;
					(sm->position).vy = (sm->position).vy + (short)cVar12;
					cVar3 = (sm->drift).vx;
					(sm->position).vz = (sm->position).vz + iVar15;
					cVar8 = (sm->drift).vx;
					cVar12 = cVar12 + 6;
					(sm->drift_change).vy = cVar12;

					if (cVar8 == 0)
					{
						(sm->final_tail_pos).vx = (sm->final_tail_pos).vx + iVar16;
						(sm->final_tail_pos).vy = cVar12 + (sm->final_tail_pos).vy + -0xc;
						(sm->final_tail_pos).vz = (sm->final_tail_pos).vz + iVar15;
					}
					else 
					{
						(sm->drift).vx = cVar3 + -1;
					}

					if (0 < (sm->position).vy) {
						sm->flags = 0;
						ReleaseSmoke((ushort)sm->num);
					}
				}
			}
			else
			{
				if ((uVar9 & 0x8000) == 0) 
				{
					DisplaySmoke(sm);
				}
				else 
				{
					DisplayWater(sm);
				}

				if (pauseflag == 0) 
				{
					if ((sm->flags & 0x8000) == 0) 
					{
						if (sm->start_w < 800)
							sm->start_w += sm->step;

						cVar12 = (sm->drift).vy;
						cVar8 = (sm->drift).vz;
						(sm->position).vx = (sm->position).vx + (int)(sm->drift).vx;
						bVar1 = sm->life;
						(sm->position).vy = (sm->position).vy + (short)cVar12;
						bVar2 = sm->halflife;
						cVar3 = (sm->drift).vx;
						cVar4 = (sm->drift).vz;
						(sm->position).vz = (sm->position).vz + (int)cVar8;
						if (bVar2 < bVar1) {
							cVar8 = (sm->drift_change).vy;
							(sm->drift).vx = cVar3 - (sm->drift_change).vx;
							cVar3 = (sm->drift_change).vz;
							(sm->drift).vy = cVar12 - cVar8;
							(sm->drift).vz = cVar4 - cVar3;
						}
					}
					else 
					{
						ROADS_GetRouteData((sm->position).vx - (int)sm->start_w, (sm->position).vz - (int)sm->start_w, &routeData);
						uVar9 = modelpointers[routeData.type]->shape_flags;
						ROADS_GetRouteData((sm->position).vx + (int)sm->start_w, (sm->position).vz + (int)sm->start_w, &routeData);

						if ((sm->start_w < 800) && ((uVar9 & 0x80 & modelpointers[routeData.type]->shape_flags & 0x80) != 0)) 
							sm->start_w += sm->step;
						else
							sm->start_w -= sm->step;
					}
				}
			}
			if (((sm->flags & 0x900c) != 0) && (pauseflag == 0)) 
			{
				iVar16 = sm->transparency - sm->t_step;
				sm->transparency = (short)iVar16;
				if (iVar16 * 0x10000 < 1)
				{
					sm->transparency = 0;
					sm->life = 1;
				}
				cVar8 = sm->life - 1;
				sm->life = cVar8;
				if (cVar8 == 0) 
				{
					sm->flags = 0;
					ReleaseSmoke((ushort)sm->num);
				}
			}
		}
		iVar17--;
		sm++;
	} while (-1 < iVar17);

	if (pauseflag == 0)
		main_cop_light_pos = main_cop_light_pos + 1U & 7;

	if (variable_weather != 0)
	{
		static int weather_level;

		weather_level = (int)rcossin_tbl[(CameraCnt & 0xfffU) * 2] + (int)*(short *)((int)rcossin_tbl + (CameraCnt & 0x3ffcU));
		gRainCount = (char)((uint)weather_level >> 8);

		if (weather_level < 1)
			gRainCount = (char)((uint)-weather_level >> 8);

		if (0xb4 < gRainCount)
			gRainCount = -0x4c;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplaySmoke(struct SMOKE *smoke /*$s0*/)
 // line 3983, offset 0x0003877c
	/* begin block 1 */
		// Start line: 3984
		// Start offset: 0x0003877C
		// Variables:
	// 		struct POLY_FT4 *poly; // $t0
	// 		struct VECTOR v; // stack offset -80
	// 		struct SVECTOR smokemesh[4]; // stack offset -64
	// 		int x; // $s2
	// 		int negx; // $s1
	// 		int z; // stack offset -32
	// 		int smoke_z_offset; // $s3
	// 		int tmode; // $a3
	// 		int size; // $v0
	// 		int centrex; // $a1
	// 		int centrey; // $v1

		/* begin block 1.1 */
			// Start line: 4041
			// Start offset: 0x00038970
			// Variables:
		// 		char red; // $a0
		// 		char green; // $a1
		// 		char blue; // $v1
		/* end block 1.1 */
		// End offset: 0x0003899C
		// End Line: 4046
	/* end block 1 */
	// End offset: 0x00038C98
	// End Line: 4115

	/* begin block 2 */
		// Start line: 10349
	/* end block 2 */
	// End Line: 10350

	/* begin block 3 */
		// Start line: 10366
	/* end block 3 */
	// End Line: 10367

	/* begin block 4 */
		// Start line: 10372
	/* end block 4 */
	// End Line: 10373

/* WARNING: Could not reconcile some variable overlaps */

void DisplaySmoke(SMOKE *smoke)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	ushort uVar2;
	DB *pDVar3;
	undefined4 in_zero;
	undefined4 in_at;
	char cVar4;
	int iVar5;
	int iVar6;
	int *piVar7;
	long lVar8;
	uint uVar9;
	int iVar10;
	uint uVar11;
	int iVar12;
	uint uVar13;
	uint *puVar14;
	short sVar15;
	int local_50;
	int local_4c;
	int local_48;
	undefined4 local_40;
	undefined4 local_3c;
	undefined4 local_38;
	undefined4 local_34;
	undefined4 local_30;
	undefined4 local_2c;
	undefined4 local_28;
	undefined4 local_24;
	int local_20;

	local_20 = 0;
	local_50 = (smoke->position).vx - camera_position.vx;
	local_4c = (smoke->position).vy - camera_position.vy;
	sVar1 = smoke->start_w;
	local_48 = (smoke->position).vz - camera_position.vz;
	sVar15 = -sVar1;
	if ((local_50 < 0x5001) && (local_48 < 0x5001)) {
		piVar7 = &local_50;
		lVar8 = camera_position.vx;
		Apply_Inv_CameraMatrix(piVar7);
		setCopControlWord(2, 0x2800, local_50);
		setCopControlWord(2, 0x3000, local_4c);
		setCopControlWord(2, 0x3800, local_48);
		setCopControlWord(2, 0, norot.m[0]._0_4_);
		setCopControlWord(2, 0x800, norot.m._4_4_);
		setCopControlWord(2, 0x1000, norot.m[1]._2_4_);
		setCopControlWord(2, 0x1800, norot.m[2]._0_4_);
		setCopControlWord(2, 0x2000, norot._16_4_);
		local_40 = CONCAT22(sVar15, sVar15);
		local_3c = (uint)local_3c._2_2_ << 0x10;
		local_38 = CONCAT22(sVar15, sVar1);
		local_34 = (uint)local_34._2_2_ << 0x10;
		local_30 = CONCAT22(sVar1, sVar15);
		local_2c = (uint)local_2c._2_2_ << 0x10;
		local_28 = CONCAT22(sVar1, sVar1);
		local_24 = (uint)local_24._2_2_ << 0x10;
		puVar14 = (uint *)current->primptr;
		setCopReg(2, in_zero, local_40);
		setCopReg(2, in_at, local_3c);
		setCopReg(2, current, local_38);
		setCopReg(2, &local_40, local_34);
		setCopReg(2, piVar7, local_30);
		setCopReg(2, lVar8, local_2c);
		copFunction(2, 0x280030);
		uVar2 = smoke->flags;
		uVar13 = 0x20;
		if ((uVar2 & 0x4000) == 0) {
			if ((uVar2 & 0x2000) == 0) {
				if ((uVar2 & 0x1000) == 0) {
					if ((uVar2 & 0x20) == 0) {
						if ((uVar2 & 0x40) == 0) {
							if (gNight == 0) {
								*(char *)(puVar14 + 1) = *(char *)&smoke->transparency;
								*(char *)((int)puVar14 + 5) = *(char *)&smoke->transparency;
								cVar4 = *(char *)&smoke->transparency + '\n';
							}
							else {
								*(char *)(puVar14 + 1) = (char)((ushort)smoke->transparency >> 1);
								*(char *)((int)puVar14 + 5) = (char)((ushort)smoke->transparency >> 1);
								cVar4 = (char)((int)smoke->transparency + 10 >> 1);
							}
							*(char *)((int)puVar14 + 6) = cVar4;
							local_20 = 0x19;
						}
						else {
							if (gNight == 0) {
								*(char *)(puVar14 + 1) = (char)((ushort)smoke->transparency >> 2);
								*(char *)((int)puVar14 + 5) = (char)((ushort)smoke->transparency >> 2);
								*(char *)((int)puVar14 + 6) = (char)((ushort)smoke->transparency >> 2);
							}
							else {
								*(char *)(puVar14 + 1) = (char)((ushort)smoke->transparency >> 3);
								*(char *)((int)puVar14 + 5) = (char)((ushort)smoke->transparency >> 3);
								*(char *)((int)puVar14 + 6) = (char)((int)smoke->transparency + 10 >> 3);
							}
						}
					}
					else {
						*(char *)(puVar14 + 1) = (char)((ushort)smoke->transparency >> 1);
						*(char *)((int)puVar14 + 5) = *(char *)&smoke->transparency;
						uVar13 = 0x40;
						*(char *)((int)puVar14 + 6) = *(char *)&smoke->transparency + '\n';
					}
				}
				else {
					uVar11 = (uint)(ushort)smoke->transparency << 0x10;
					iVar5 = (int)uVar11 >> 0x13;
					uVar9 = iVar5 + 0x32U & 0xff;
					cVar4 = (char)uVar9;
					if (uVar9 < 0x3c) {
						cVar4 = (char)(uVar11 >> 0x12);
					}
					local_20 = 0x12;
					*(char *)(puVar14 + 1) = *(char *)&smoke->transparency;
					*(char *)((int)puVar14 + 5) = cVar4;
					*(char *)((int)puVar14 + 6) = (char)iVar5;
				}
			}
			else {
				if (gNight == 0) {
					*(char *)(puVar14 + 1) = (char)((ushort)smoke->transparency >> 2);
					*(char *)((int)puVar14 + 5) = (char)((ushort)smoke->transparency >> 2);
					cVar4 = (char)((ushort)smoke->transparency >> 2);
				}
				else {
					*(char *)(puVar14 + 1) = (char)((ushort)smoke->transparency >> 1);
					*(char *)((int)puVar14 + 5) = (char)((ushort)smoke->transparency >> 1);
					cVar4 = (char)((ushort)smoke->transparency >> 1);
				}
				*(char *)((int)puVar14 + 6) = cVar4;
				uVar13 = 0x40;
				local_20 = 0x11;
			}
		}
		else {
			*(char *)(puVar14 + 1) = *(char *)&smoke->transparency;
			*(char *)((int)puVar14 + 5) = *(char *)&smoke->transparency;
			*(char *)((int)puVar14 + 6) = *(char *)&smoke->transparency;
		}
		uVar9 = getCopReg(2, 0xc);
		puVar14[2] = uVar9;
		uVar9 = getCopReg(2, 0xd);
		puVar14[4] = uVar9;
		uVar9 = getCopReg(2, 0xe);
		puVar14[6] = uVar9;
		iVar5 = getCopReg(2, 0x13);
		setCopReg(2, in_zero, local_28);
		setCopReg(2, in_at, local_24);
		copFunction(2, 0x180001);
		puVar14[3] = CONCAT22(smoke_texture.clutid, smoke_texture.coords._0_2_);
		puVar14[5] = (uint)smoke_texture.coords._2_2_ | (smoke_texture.tpageid | uVar13) << 0x10;
		puVar14[7] = (uint)smoke_texture.coords._4_2_ - 0x400;
		uVar13 = (uint)smoke_texture.coords._6_2_;
		*(char *)((int)puVar14 + 3) = '\t';
		*(char *)((int)puVar14 + 7) = '.';
		puVar14[9] = uVar13 - 0x400;
		pDVar3 = current;
		if (0 < iVar5 >> 3) {
			local_20 = (iVar5 >> 3) - local_20;
			if (local_20 < 9) {
				local_20 = 9;
			}
			*puVar14 = *puVar14 & 0xff000000 | current->ot[local_20] & 0xffffff;
			pDVar3->ot[local_20] = pDVar3->ot[local_20] & 0xff000000 | (uint)puVar14 & 0xffffff;
			uVar13 = getCopReg(2, 0xe);
			puVar14[8] = uVar13;
			if (100 < (int)*(short *)(puVar14 + 4) - (int)*(short *)(puVar14 + 2) >> 1) {
				iVar10 = (int)*(short *)(puVar14 + 2) + (int)*(short *)(puVar14 + 8) >> 1;
				iVar12 = iVar10 + -0x32;
				iVar10 = iVar10 + 0x32;
				iVar6 = (int)*(short *)((int)puVar14 + 10) + (int)*(short *)((int)puVar14 + 0x22) >> 1;
				iVar5 = (iVar6 + -0x32) * 0x10000;
				iVar6 = (iVar6 + 0x32) * 0x10000;
				puVar14[2] = iVar12 + iVar5;
				puVar14[4] = iVar10 + iVar5;
				puVar14[6] = iVar12 + iVar6;
				puVar14[8] = iVar10 + iVar6;
			}
			current->primptr = current->primptr + 0x28;
		}
	}
	return;*/
}



// decompiled code
// original method signature: 
// void /*$ra*/ add_haze(int top_col /*$a0*/, int bot_col /*$a1*/, short ot_pos /*$a2*/)
 // line 4118, offset 0x00038cb4
	/* begin block 1 */
		// Start line: 4119
		// Start offset: 0x00038CB4
		// Variables:
	// 		struct TILE *polys; // $a1
	/* end block 1 */
	// End offset: 0x00038E00
	// End Line: 4141

	/* begin block 2 */
		// Start line: 10702
	/* end block 2 */
	// End Line: 10703

// [D]
void add_haze(int top_col, int bot_col, short ot_pos)
{
	unsigned char uVar2;
	TILE *polys;

	if ((9 < top_col) && (FastForward == 0))
	{
		polys = (TILE *)current->primptr;

		setTile(polys);

		polys->r0 = top_col;
		polys->g0 = top_col;
		polys->b0 = top_col;

		setSemiTrans(polys, 1);
		polys->w = 320;
		polys->x0 = 0;
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



// decompiled code
// original method signature: 
// void /*$ra*/ SetupRain()
 // line 4152, offset 0x00039df8
	/* begin block 1 */
		// Start line: 4154
		// Start offset: 0x00039DF8
	/* end block 1 */
	// End offset: 0x00039E54
	// End Line: 4163

	/* begin block 2 */
		// Start line: 20227
	/* end block 2 */
	// End Line: 20228

	/* begin block 3 */
		// Start line: 20228
	/* end block 3 */
	// End Line: 20229

	/* begin block 4 */
		// Start line: 20231
	/* end block 4 */
	// End Line: 20232

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void SetupRain(void)
{
	gNextRainDrop = 0;

	do {

		gRainAlloc[gNextRainDrop] = gNextRainDrop;
		gRain[gNextRainDrop].oldposition.pad = gNextRainDrop;

		gNextRainDrop++;
	} while (gNextRainDrop < 180);

	gNextRainDrop = 0;
}



// decompiled code
// original method signature: 
// int /*$ra*/ AllocateRainDrop()
 // line 4173, offset 0x0003a2d4
	/* begin block 1 */
		// Start line: 23682
	/* end block 1 */
	// End Line: 23683

	/* begin block 2 */
		// Start line: 25942
	/* end block 2 */
	// End Line: 25943

	/* begin block 3 */
		// Start line: 25943
	/* end block 3 */
	// End Line: 25944

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
int AllocateRainDrop(void)
{
	short *psVar1;

	if (gNextRainDrop > 179)
		return -1;

	return gRainAlloc[gNextRainDrop++];
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReleaseRainDrop(int RainIndex /*$a0*/)
 // line 4190, offset 0x00039db0
	/* begin block 1 */
		// Start line: 17849
	/* end block 1 */
	// End Line: 17850

	/* begin block 2 */
		// Start line: 17850
	/* end block 2 */
	// End Line: 17851

// [D]
void ReleaseRainDrop(int RainIndex)
{
	gNextRainDrop--;
	gRainAlloc[gNextRainDrop] = RainIndex;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawRainDrops()
 // line 4208, offset 0x00038e08
	/* begin block 1 */
		// Start line: 4210
		// Start offset: 0x00038E08
		// Variables:
	// 		struct RAIN_TYPE *RainPtr; // $s0
	// 		struct POLY_GT3 *poly; // $a3
	// 		int Count; // $s2
	// 		int z; // stack offset -48
	// 		struct SVECTOR v[3]; // stack offset -88
	// 		struct VECTOR drift; // stack offset -64
	// 		int tpage; // $fp
	// 		int clut; // $s7
	// 		int col; // $s1

		/* begin block 1.1 */
			// Start line: 4259
			// Start offset: 0x00038FA4
			// Variables:
		// 		int notfirst; // $a1
		/* end block 1.1 */
		// End offset: 0x00039158
		// End Line: 4296
	/* end block 1 */
	// End offset: 0x0003919C
	// End Line: 4300

	/* begin block 2 */
		// Start line: 10912
	/* end block 2 */
	// End Line: 10913

	/* begin block 3 */
		// Start line: 10913
	/* end block 3 */
	// End Line: 10914

	/* begin block 4 */
		// Start line: 10924
	/* end block 4 */
	// End Line: 10925

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DrawRainDrops(void)
{
	int z;
	DB *pDVar3;
	ushort uVar4;
	uint uVar5;
	uint iVar6;
	POLY_GT3 *poly;
	RAIN_TYPE *RainPtr;
	int iVar7;
	int col;
	SVECTOR v;
	VECTOR drift;

	if (gNextRainDrop == 0)
		return;

	GetSmokeDrift(&drift);

	//if (cameraview == 1)
	//	iVar7 = 70;
	//else
	iVar7 = 70;// -car_data[0].hd.wheel_speed;

	if (iVar7 < 50)
		iVar7 = 50;

	if (gNight != 0)
		iVar7 -= -15;

	col = iVar7 >> 1 | (iVar7 >> 1) << 8;
	col = col | col << 0x10;

	if (NoRainIndoors == 0)
		DisplaySplashes();

	gte_SetRotMatrix(&inv_camera_matrix);
	gte_SetTransVector(&dummy);

	RainPtr = gRain;
	iVar7 = gNextRainDrop-1;

	while (iVar7 >= 0) 
	{
		if (pauseflag == 0) 
		{
			RainPtr->position.vy = (RainPtr->position).vy + 0x14;
			RainPtr->position.vx = (RainPtr->position).vx + drift.vx * -2;
			RainPtr->position.vz = (RainPtr->position).vz + drift.vz * -2;
		}

		v.vx = RainPtr->position.vx - camera_position.vx;
		v.vy = RainPtr->position.vy - camera_position.vy;
		v.vz = RainPtr->position.vz - camera_position.vz;

		iVar6 = *(uint *)&RainPtr->oldposition;

		poly = (POLY_GT3 *)current->primptr;

		*(uint *)&poly->r2 = col;
		*(uint *)&poly->r1 = col;
		*(uint *)&poly->r0 = 0;

		gte_ldv0(&v);
		gte_rtps();

		setPolyGT3(poly);
		setSemiTrans(poly, 1);

		*(uint *)&poly->x0 = *(uint *)&RainPtr->oldposition;
		gte_stsxy(&poly->x2);
		gte_stsz(&z);

		if (z - 0x97U < 0x352 && -0x65 < poly->x2 && poly->x2 < 0x1a5 && -0x33 < poly->y2 && poly->y2 < 0x101) 
		{
			*(uint *)&RainPtr->oldposition = *(uint *)&poly->x2;

			if (iVar6 != 0) 
			{
				poly->x1 = poly->x2 - ((z >> 10) - 1);
				poly->x2 = poly->x2 + ((z >> 10) - 1);
				poly->y1 = poly->y2;

				poly->clut = light_texture.clutid;
				poly->tpage = light_texture.tpageid | 0x20;

				*(ushort *)&poly->u0 = *(ushort *)&light_texture.coords.u0;
				*(ushort *)&poly->u1 = *(ushort *)&light_texture.coords.u1;
				*(ushort *)&poly->u2 = *(ushort *)&light_texture.coords.u2;

				addPrim(current->ot + (z >> 3), poly);
				current->primptr += sizeof(POLY_GT3);
			}
		}
		else 
		{
			ReleaseRainDrop(RainPtr->oldposition.pad);
		}

		RainPtr++;
		iVar7--;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ AddRainDrops()
 // line 4413, offset 0x0003919c
	/* begin block 1 */
		// Start line: 4415
		// Start offset: 0x0003919C
		// Variables:
	// 		struct SVECTOR v; // stack offset -48
	// 		struct RAIN_TYPE *RainPtr; // $a2
	// 		int RainIndex; // $s0
	// 		int RainNo; // $s1
	// 		int first; // $s3
	// 		static unsigned long rand; // offset 0x8

		/* begin block 1.1 */
			// Start line: 4453
			// Start offset: 0x00039388
			// Variables:
		// 		int depth; // $v0
		/* end block 1.1 */
		// End offset: 0x000393B0
		// End Line: 4456

		/* begin block 1.2 */
			// Start line: 4466
			// Start offset: 0x000393E4
			// Variables:
		// 		struct ROUTE_DATA routeData; // stack offset -40
		/* end block 1.2 */
		// End offset: 0x00039434
		// End Line: 4474
	/* end block 1 */
	// End offset: 0x00039444
	// End Line: 4477

	/* begin block 2 */
		// Start line: 11241
	/* end block 2 */
	// End Line: 11242

	/* begin block 3 */
		// Start line: 11355
	/* end block 3 */
	// End Line: 11356

	/* begin block 4 */
		// Start line: 11356
	/* end block 4 */
	// End Line: 11357

	/* begin block 5 */
		// Start line: 11364
	/* end block 5 */
	// End Line: 11365

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void AddRainDrops(void)
{
	static unsigned long rand;

	long lVar1;
	bool first;
	short sVar3;
	int RainIndex;
	int iVar4;
	short sVar5;
	uint uVar6;
	short sVar7;
	int uVar8;
	SVECTOR v;
	ROUTE_DATA routeData;

	first = true;

	if (pauseflag != 0)
		return;

	uVar8 = gRainCount;
	NoRainIndoors = 0;
	wetness += uVar8 / 6;
	if (wetness > 7000)
		wetness = 7000;

	gte_SetRotMatrix(&camera_matrix);
	gte_SetTransVector(&camera_position);

	while (true) 
	{
		uVar8--;
		if (uVar8 == -1)
			return;

		RainIndex = AllocateRainDrop();

		if (RainIndex < 0)
			return;

		iVar4 = rand * 0x19660d + 0x3c6ef35f;
		uVar6 = (iVar4 >> 0x14 & 0x1ffU) + 400;
		iVar4 = iVar4 * 0x19660d + 0x3c6ef35f;
		sVar7 = -((iVar4 >> 0x14) & 0x1ff);
		rand = iVar4 * 0x19660d + 0x3c6ef35f;
		sVar5 = ((rand >> 0x14) & 0x1ff) - 0x100;

		v.vx = sVar5;
		v.vy = sVar7;
		v.vz = uVar6;

		if (512 < uVar6) 
		{
			sVar3 = (uVar6 * 0x10000 >> 0x18) + 1;
			v.vx = sVar5 * sVar3;
			v.vy = sVar7 * sVar3;
		}

		gte_ldv0(&v);
		docop2(0x480012);

		gRain[RainIndex].oldposition.vx = 0;
		gRain[RainIndex].oldposition.vy = 0;
		gRain[RainIndex].oldposition.vz = 0;
		gRain[RainIndex].oldposition.pad = RainIndex;

		gte_stlvnl(&gRain[RainIndex].position)

		if (first && (ROADS_GetRouteData(gRain[RainIndex].position.vx, gRain[RainIndex].position.vz, &routeData), modelpointers[routeData.type]->flags2 & 0x100) != 0)
			break;

		first = false;
	}

	NoRainIndoors = 1;
	ReleaseRainDrop(RainIndex);
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplaySplashes()
 // line 4489, offset 0x00039468
	/* begin block 1 */
		// Start line: 4491
		// Start offset: 0x00039468
		// Variables:
	// 		int SplashNo; // $s4
	// 		int SplashFrac; // $v0
	// 		struct VECTOR CamGnd; // stack offset -96
	// 		struct VECTOR Gnd1; // stack offset -80
	// 		struct VECTOR Gnd2; // stack offset -64
	// 		struct VECTOR Position; // stack offset -48
	// 		struct CVECTOR col; // stack offset -32
	// 		static unsigned long rand; // offset 0x170
	// 		int d1; // $a0
	// 		int d2; // $a2
	/* end block 1 */
	// End offset: 0x000397A0
	// End Line: 4547

	/* begin block 2 */
		// Start line: 11536
	/* end block 2 */
	// End Line: 11537

	/* begin block 3 */
		// Start line: 11537
	/* end block 3 */
	// End Line: 11538

	/* begin block 4 */
		// Start line: 11549
	/* end block 4 */
	// End Line: 11550

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DisplaySplashes(void)
{
	static unsigned long rand;

	int iVar1;
	uint uVar2;
	uint uVar3;
	int iVar4;
	VECTOR CamGnd;
	VECTOR Gnd1;
	VECTOR Gnd2;
	VECTOR Position;
	CVECTOR col = { 25, 25, 25};

	if (pauseflag != 0)
		return;

	uVar3 = (gRainCount >> 2);
	if (0x1e < gRainCount >> 2)
		uVar3 = 0x1e;

	iVar4 = FIXED(uVar3 * FrAng * 3);

	gte_SetRotMatrix(&aspect); // [A] norot

	CamGnd.vx = camera_position.vx;
	CamGnd.vz = camera_position.vz;
	iVar1 = MapHeight(&CamGnd);
	CamGnd.vy = -camera_position.vy - iVar1;
	uVar3 = FrAng - camera_angle.vy & 0xfff;
	Gnd1.vx = rcossin_tbl[uVar3 * 2] + camera_position.vx;
	Gnd1.vz = rcossin_tbl[uVar3 * 2 + 1] + camera_position.vz;
	iVar1 = MapHeight(&Gnd1);
	Gnd1.vx = Gnd1.vx - CamGnd.vx;
	Gnd1.vy = (-camera_position.vy - iVar1) - CamGnd.vy;
	Gnd1.vz = Gnd1.vz - CamGnd.vz;
	uVar3 = -FrAng - (int)camera_angle.vy & 0xfff;
	Gnd2.vx = rcossin_tbl[uVar3 * 2] + camera_position.vx;
	Gnd2.vz = rcossin_tbl[uVar3 * 2 + 1] + camera_position.vz;
	iVar1 = MapHeight(&Gnd2);
	Gnd2.vx = Gnd2.vx - CamGnd.vx;
	Gnd2.vy = (-camera_position.vy - iVar1) - CamGnd.vy;
	Gnd2.vz = Gnd2.vz - CamGnd.vz;

	while (iVar4 = iVar4 + -1, iVar4 != -1)
	{
		uVar3 = rand * 0x19660d + 0x3c6ef35f;
		uVar2 = uVar3 >> 4 & 0xfff;
		rand = uVar3 * 0x19660d + 0x3c6ef35f;
		uVar3 = rand >> 0xe & 0xfff;
		Position.vx = FIXED(Gnd1.vx * uVar2 + Gnd2.vx * uVar3);
		Position.vy = FIXED(Gnd1.vy * uVar2 + Gnd2.vy * uVar3) + CamGnd.vy;
		Position.vz = FIXED(Gnd1.vz * uVar2 + Gnd2.vz * uVar3);

		ShowLight(&Position, &col, 12, &drop_texture);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayLightReflections(struct VECTOR *v1 /*$s1*/, struct CVECTOR *col /*$s3*/, short size /*$a2*/, struct TEXTURE_DETAILS *texture /*$s2*/)
 // line 4550, offset 0x000397c0
	/* begin block 1 */
		// Start line: 4551
		// Start offset: 0x000397C0
		// Variables:
	// 		struct SVECTOR vert[4]; // stack offset -80
	// 		struct POLY_FT4 *poly; // $a1
	// 		struct CVECTOR thiscol; // stack offset -48
	// 		int z; // stack offset -40
	// 		int tpage; // $s5
	// 		int clut; // $s4
	/* end block 1 */
	// End offset: 0x00039A30
	// End Line: 4602

	/* begin block 2 */
		// Start line: 11756
	/* end block 2 */
	// End Line: 11757

/* WARNING: Could not reconcile some variable overlaps */

void DisplayLightReflections(VECTOR *v1, CVECTOR *col, short size, TEXTURE_DETAILS *texture)
{
	POLY_FT4 *poly;
	SVECTOR vert[4];
	CVECTOR thiscol;
	int z;

	if (9 < wetness && v1->vy > camera_position.vy)
	{
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

		if (0x95 < z) 
		{
			poly = (POLY_FT4 *)current->primptr;
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

			thiscol.r = col->r >> 3;
			thiscol.g = col->g >> 3;
			thiscol.b = col->b >> 3;

			poly->r0 = thiscol.r;
			poly->g0 = thiscol.g;
			poly->b0 = thiscol.b;

			addPrim(current->ot + (z >> 4), poly);
			current->primptr += sizeof(POLY_FT4);
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoLightning()
 // line 4607, offset 0x00039b78
	/* begin block 1 */
		// Start line: 4609
		// Start offset: 0x00039B78
	/* end block 1 */
	// End offset: 0x00039C58
	// End Line: 4631

	/* begin block 2 */
		// Start line: 12959
	/* end block 2 */
	// End Line: 12960

	/* begin block 3 */
		// Start line: 15350
	/* end block 3 */
	// End Line: 15351

	/* begin block 4 */
		// Start line: 15351
	/* end block 4 */
	// End Line: 15352

/* WARNING: Unknown calling convention yet parameter storage is locked */

int lightning = 0;
int LightningTimer = 10;
int ThunderTimer = 0;
static int ThunderDistance = 0;

// [D]
void DoLightning(void)
{
	uint uVar1;

	if (pauseflag == 0) 
	{
		if (LightningTimer < -10) 
		{
			uVar1 = rand();
			LightningTimer = uVar1 & 0xff;
		}
		else 
			LightningTimer = LightningTimer - 1;
	
		if ((LightningTimer < 0) && (uVar1 = rand(), (uVar1 & 1) == 0))
		{
			RequestThunder();
			uVar1 = rand();

			if ((uVar1 & 1) == 0) 
			{
				NightAmbient = NightAmbient << 1;
				if (0x80 < NightAmbient) 
					NightAmbient = 0x80;

				lightning = 2;
				return;
			}

			add_haze(0x32, 0, 0x107e);
		}

		lightning = 0;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitThunder()
 // line 4635, offset 0x0003a0bc
	/* begin block 1 */
		// Start line: 4636
		// Start offset: 0x0003A0BC
	/* end block 1 */
	// End offset: 0x0003A120
	// End Line: 4636

	/* begin block 2 */
		// Start line: 9270
	/* end block 2 */
	// End Line: 9271

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitThunder(void)
{
	ThunderTimer = -1;
	ThunderDistance = rand() % 5000;
}



// decompiled code
// original method signature: 
// void /*$ra*/ RequestThunder()
 // line 4636, offset 0x0003a120
	/* begin block 1 */
		// Start line: 24079
	/* end block 1 */
	// End Line: 24080

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void RequestThunder(void)
{
	ThunderTimer = ThunderDistance >> 8;

	if (ThunderTimer < 1)
		ThunderTimer = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoThunder()
 // line 4638, offset 0x0003a144
	/* begin block 1 */
		// Start line: 4640
		// Start offset: 0x0003A144
	/* end block 1 */
	// End offset: 0x0003A224
	// End Line: 4647

	/* begin block 2 */
		// Start line: 24083
	/* end block 2 */
	// End Line: 24084

	/* begin block 3 */
		// Start line: 24084
	/* end block 3 */
	// End Line: 24085

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DoThunder(void)
{
	int iVar1;
	int iVar2;

	if (pauseflag)
		return;

	iVar1 = rand();
	ThunderDistance = (ThunderDistance + 40) - rand() % 80;

	if (ThunderDistance < 250)
		ThunderDistance = 250;

	if (5000 < ThunderDistance) 
		ThunderDistance = 5000;

	iVar1 = ThunderTimer-1;

	if (ThunderTimer > -1 && (ThunderTimer = iVar1, iVar1 == 0)) 
	{
		iVar2 = rand();

		iVar1 = iVar2;

		if (iVar2 < 0)
			iVar1 = iVar2 + 0x7ff;

		StartSound(-1, 1, 12, -ThunderDistance, iVar2 - (iVar1 >> 0xb) * 2048 + 3072);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DoWeather(int weather /*$a0*/)
 // line 4651, offset 0x0003a000
	/* begin block 1 */
		// Start line: 24074
	/* end block 1 */
	// End Line: 24075

	/* begin block 2 */
		// Start line: 9302
	/* end block 2 */
	// End Line: 9303

	/* begin block 3 */
		// Start line: 24075
	/* end block 3 */
	// End Line: 24076

// [D]
void DoWeather(int weather)
{
	if (weather == 1 && pauseflag == 0) 
	{
		if (gEffectsTimer < 0x29) 
		{
			if ((FrameCnt & 7U) == 0) 
				gEffectsTimer++;
		}
		else
		{
			AddRainDrops();
			DrawRainDrops();

			if ((FrameCnt & 7U) == 0)
				gRainCount = gRainCount + 1;

			if (gRainCount > 35)
				gRainCount = 35;
		}
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ GetDebrisColour(struct _CAR_DATA *cp /*$a0*/)
 // line 4725, offset 0x00039fa8
	/* begin block 1 */
		// Start line: 4726
		// Start offset: 0x00039FA8
		// Variables:
	// 		int car_model; // $v1
	// 		int palette; // $a0
	/* end block 1 */
	// End offset: 0x0003A000
	// End Line: 4742

	/* begin block 2 */
		// Start line: 24129
	/* end block 2 */
	// End Line: 24130

	/* begin block 3 */
		// Start line: 24130
	/* end block 3 */
	// End Line: 24131

// [D]
int GetDebrisColour(_CAR_DATA *cp)
{
	int car_model;

	car_model = MissionHeader->residentModels[cp->ap.model];

	if (car_model == 0)
		return 1;

	if(car_model < 8)
		return (car_model-1) * 6 + cp->ap.palette + 7;

	return car_model - 6;
}





