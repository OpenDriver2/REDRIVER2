#include "../decomp_defs.h"
#include "texture.h"

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

VECTOR dummy = { 0 };

/*
 * Offset 0x32C78
 * D:\driver2\game\C\DEBRIS.C (line 790)
 * Stack frame base $sp, length 848
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ PlacePoolForCar(struct _CAR_DATA *cp /*$s4*/, struct CVECTOR *col /*stack 4*/, int front /*$a2*/)
{ // line 1, address 0x32c78
	int car_road_height; // $s2
	struct SVECTOR s[27]; // stack address -832
	struct SVECTOR *ptr; // $s1
	struct SVECTOR sout[27]; // stack address -616
	struct VECTOR s1[12]; // stack address -400
	struct VECTOR *ptr1; // $s0
	struct POLY_FT4 *poly; // $t0
	struct MATRIX final_matrix; // stack address -208
	struct VECTOR averagepos; // stack address -176
	int in_car; // $t0
	int z; // stack address -48
	int sub_level; // $fp
	int count; // $s3
	struct VECTOR mid_position; // stack address -160
	{ // line 23, address 0x32d54
		short farz; // $a2
		short nearz; // $a0
	} // line 108, address 0x32f28
	{ // line 114, address 0x32f38
	} // line 130, address 0x32fa0
	{ // line 147, address 0x3301c
		struct VECTOR toss; // stack address -144
		int temp_y; // $a1
	} // line 161, address 0x330d4
	{ // line 164, address 0x3310c
		long n[4]; // stack address -128
	} // line 170, address 0x331d4
	{ // line 177, address 0x33258
		int count; // $s2
		{ // line 206, address 0x3342c
			long z[15]; // stack address -112
			{ // line 216, address 0x33484
				char *VertIdx; // $s0
				{ // line 228, address 0x33504
				} // line 233, address 0x33594
			} // line 234, address 0x33594
		} // line 235, address 0x335a4
	} // line 237, address 0x335a4
} // line 239, address 0x335ac
/*
 * Offset 0x335DC
 * D:\driver2\game\C\DEBRIS.C (line 1327)
 * Stack frame base $sp, length 48
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ AddLeaf(struct VECTOR *Position /*$s1*/, int num_leaves /*$s5*/, int Type /*$s3*/)
{ // line 1, address 0x335dc
	struct LEAF *myleaf; // $a1
	int num; // $v1
	int loop; // $s2
	int temprand; // $s0
	{ // line 16, address 0x33640
		{ // line 74, address 0x3374c
		} // line 79, address 0x33760
		{ // line 83, address 0x33774
			int temp; // $v0
		} // line 83, address 0x33774
		{ // line 89, address 0x337a0
			int temp; // $v0
		} // line 92, address 0x337b4
	} // line 93, address 0x337b4
} // line 101, address 0x337ec
/*
 * Offset 0x33814
 * D:\driver2\game\C\DEBRIS.C (line 1493)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ InitDebrisNames()
{ // line 2, address 0x33814
	
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
	SetCLUT16Flags(digit_texture.clutid, 0x6, 0);

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
	GetTextureDetails("MOVECAM", &movecampos);	// is that intended to be wrong???

	GetTextureDetails("OK", &ok);
	GetTextureDetails("PAUSE", &pause);
	GetTextureDetails("PLAYCAM", &playcam);
	GetTextureDetails("PLAYPAU", &playpause);
	GetTextureDetails("SAVE2CA", &save2card);
	GetTextureDetails("RESTREP", &restart);

	GetTextureDetails("HEAD1", &texturePedHead);
	GetTextureDetails("TSHADOW", &tannerShadow_texture);
	GetTextureDetails("LIGHTREF", &lightref_texture);

	GetTextureDetails("LIGHT", &light_pool_texture);

	texture_is_icon = 0;
	head1_texture.coords.u3 = head1_texture.coords.u0 + 8;
	head1_texture.coords.u1 = head1_texture.coords.u0 + 8;

	InitButtonTextures();
	InitTannerShadow();

} // line 62, address 0x33c04
/*
 * Offset 0x33C04
 * D:\driver2\game\C\DEBRIS.C (line 1564)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ InitDebris()
{ // line 2, address 0x33c04
	int loop; // $v1
	int count; // $s0
	struct TPAN texnum; // stack address -88
	struct TRI_POINT_LONG temptri; // stack address -80
	struct BVECTOR *debrisPTR; // $a0
	{ // line 37, address 0x33d5c
		{ // line 41, address 0x33d78
		} // line 46, address 0x33de8
	} // line 63, address 0x33e94
} // line 110, address 0x34010
/*
 * Offset 0x34010
 * D:\driver2\game\C\DEBRIS.C (line 1753)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ AddGroundDebris()
{ // line 2, address 0x34010
	struct VECTOR Position; // stack address -48
	int seed; // $s0
	int number; // $v0
	int count; // $s3
	int xbound; // $a1
	int zbound; // $a0
	int type; // $a2
	struct CELL_OBJECT *cop; // $s1
	struct MODEL *model; // $s2
	{ // line 30, address 0x340e4
	} // line 51, address 0x34168
} // line 54, address 0x34178
/*
 * Offset 0x341A0
 * D:\driver2\game\C\DEBRIS.C (line 1815)
 * Stack frame base $sp, length 144
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawSmashable_sprites()
{ // line 2, address 0x341a0
	int count; // $s6
	struct VECTOR pos; // stack address -128
	struct DAMAGED_OBJECT *dam; // $s2
	{ // line 11, address 0x3420c
		struct MATRIX object_matrix; // stack address -112
		struct MATRIX spritematrix; // stack address -80
		struct MATRIX *finalmatrix; // $s0
		struct MODEL *model; // $s3
		{ // line 46, address 0x343c4
			unsigned long colours; // $a0
		} // line 55, address 0x3441c
	} // line 60, address 0x34450
} // line 62, address 0x3448c
/*
 * Offset 0x3448C
 * D:\driver2\game\C\DEBRIS.C (line 1925)
 * Stack frame base $sp, length 128
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ AddSmallStreetLight(struct CELL_OBJECT *cop /*$s1*/, int x /*$s3*/, int y /*$s6*/, int z /*$s4*/, int type /*stack 16*/)
{ // line 1, address 0x3448c
	struct VECTOR v1; // stack address -112
	struct VECTOR v2; // stack address -96
	struct VECTOR v3; // stack address -80
	struct SVECTOR pos; // stack address -64
	struct CVECTOR col; // stack address -56
	struct CVECTOR col1; // stack address -48
	int count; // $v1
	short angle; // $s2
	int halo_size; // $fp
	int length; // $s5
	int LampId; // $s7
	struct DAMAGED_LAMP *dam; // $s0
	{ // line 36, address 0x34554
	} // line 42, address 0x345a8
} // line 114, address 0x34890
/*
 * Offset 0x348C0
 * D:\driver2\game\C\DEBRIS.C (line 2049)
 * Stack frame base $sp, length 104
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ AddLightEffect(struct CELL_OBJECT *cop /*$t0*/, int x /*$t2*/, int y /*$a2*/, int z /*$a3*/, int type /*stack 16*/, int colour /*stack 20*/)
{ // line 1, address 0x348c0
	struct VECTOR v1; // stack address -88
	struct VECTOR v2; // stack address -72
	struct VECTOR v3; // stack address -56
	struct SVECTOR pos; // stack address -40
	struct CVECTOR col; // stack address -32
	struct CVECTOR col1; // stack address -24
	short angle; // $v1
	int length; // $s1
} // line 126, address 0x34cd4
/*
 * Offset 0x34CD4
 * D:\driver2\game\C\DEBRIS.C (line 2178)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ PreLampStreak()
{ // line 2, address 0x34cd4
	int count; // $a3
} // line 20, address 0x34d84
/*
 * Offset 0x34D84
 * D:\driver2\game\C\DEBRIS.C (line 2230)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ damage_lamp(struct CELL_OBJECT *cop /*$a2*/)
{ // line 1, address 0x34d84
	int count; // $v1
	int old_damage; // $v0
} // line 15, address 0x34e14
/*
 * Offset 0x34E14
 * D:\driver2\game\C\DEBRIS.C (line 2255)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
int /*$ra*/ damage_object(struct CELL_OBJECT *cop /*$s1*/, struct VECTOR *velocity /*$a1*/)
{ // line 1, address 0x34e14
	struct DAMAGED_OBJECT *dam; // $s0
	{ // line 1, address 0x34e14
		struct PACKED_CELL_OBJECT *pcop; // $a0
	} // line 1, address 0x34e14
} // line 63, address 0x34fcc
/*
 * Offset 0x34FCC
 * D:\driver2\game\C\DEBRIS.C (line 2326)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ AddTrafficLight(struct CELL_OBJECT *cop /*$t4*/, int x /*$t6*/, int y /*$t7*/, int z /*$a3*/, int flag /*stack 16*/, int yang /*stack 20*/)
{ // line 1, address 0x34fcc
	struct CVECTOR a; // stack address -80
	struct CVECTOR b; // stack address -72
	struct CVECTOR c; // stack address -64
	struct VECTOR v1; // stack address -56
	struct VECTOR v2; // stack address -40
	int lDiffAnglesX; // $s2
	int lDiffAnglesY; // $s1
	int AbsX; // $a2
	int AbsY; // $a1
	int tempfade; // $v0
	{ // line 1, address 0x34fcc
		int c; // $t1
		int s; // $t2
	} // line 1, address 0x34fcc
} // line 90, address 0x35318
/*
 * Offset 0x35334
 * D:\driver2\game\C\DEBRIS.C (line 2462)
 * Stack frame base $sp, length 88
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
void /*$ra*/ ShowCarlight(struct SVECTOR *v1 /*$s6*/, struct _CAR_DATA *cp /*$s3*/, struct CVECTOR *col /*$s1*/, short length /*$s5*/, struct TEXTURE_DETAILS *texture /*stack 16*/, int flag /*stack 20*/)
{ // line 1, address 0x35334
	int CarLightFade; // $a1
	struct VECTOR v1t; // stack address -72
	struct VECTOR v1l; // stack address -56
	struct CVECTOR flareCol; // stack address -40
	int front; // $a0
} // line 52, address 0x3559c
/*
 * Offset 0x355C4
 * D:\driver2\game\C\DEBRIS.C (line 2523)
 * Stack frame base $sp, length 40
 */
void /*$ra*/ ShowLight1(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$a1*/, short length /*$a2*/, struct TEXTURE_DETAILS *texture /*$a3*/)
{ // line 1, address 0x355c4
	struct SVECTOR vert[4]; // stack address -40
	struct POLY_FT4 *poly; // $t0
	int z; // stack address -8
} // line 52, address 0x357b0
/*
 * Offset 0x357B8
 * D:\driver2\game\C\DEBRIS.C (line 2579)
 * Stack frame base $sp, length 104
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ ShowLight(struct VECTOR *v1 /*$s0*/, struct CVECTOR *col /*$s3*/, short length /*$s4*/, struct TEXTURE_DETAILS *texture /*$s2*/)
{ // line 1, address 0x357b8
	struct SVECTOR vert[4]; // stack address -88
	struct POLY_FT4 *poly; // $s1
	int z; // stack address -40
	int index; // $a1
	int tail_width; // $s5
	{ // line 65, address 0x35abc
		int loop; // $a1
	} // line 71, address 0x35b14
	{ // line 75, address 0x35b3c
		struct POLY_G4 *poly1; // $s0
		int dx; // $a0
		int dy; // $v0
		int angle; // $v0
		int width; // $s2
		int c; // $a0
		int s; // $a2
		int length; // $v0
		struct SVECTOR tail; // stack address -56
		struct SVECTOR head; // stack address -48
	} // line 130, address 0x35f20
	{ // line 148, address 0x35fd0
		int loop; // $a3
	} // line 154, address 0x36050
	{ // line 158, address 0x3608c
		struct POLY_G4 *poly1; // $s0
		int dx; // $a2
		int dy; // $a1
		int angle; // $v0
		int width; // $s1
		int c; // $a2
		int s; // $a1
		int length; // $v0
		struct SVECTOR tail; // stack address -56
		struct SVECTOR head; // stack address -48
	} // line 213, address 0x36470
} // line 215, address 0x36470
/*
 * Offset 0x36494
 * D:\driver2\game\C\DEBRIS.C (line 2804)
 * Stack frame base $sp, length 40
 */
void /*$ra*/ ShowGroundLight(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$a1*/, short length /*$a2*/)
{ // line 1, address 0x36494
	struct SVECTOR vert[4]; // stack address -40
	struct POLY_FT4 *poly; // $t0
	int z; // stack address -8
} // line 54, address 0x366e8
/*
 * Offset 0x366F0
 * D:\driver2\game\C\DEBRIS.C (line 2869)
 * Stack frame base $sp, length 40
 */
void /*$ra*/ RoundShadow(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$a1*/, short length /*$a2*/)
{ // line 1, address 0x366f0
	struct SVECTOR vert[4]; // stack address -40
	struct POLY_FT4 *poly; // $t0
	int z; // stack address -8
} // line 64, address 0x36938
/*
 * Offset 0x36940
 * D:\driver2\game\C\DEBRIS.C (line 2945)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ ShowFlare(struct VECTOR *v1 /*$a0*/, struct CVECTOR *col /*$s2*/, short length /*$a2*/, int rotation /*$a3*/)
{ // line 1, address 0x36940
	struct SVECTOR vert[4]; // stack address -96
	struct POLY_FT4 *poly; // $t0
	struct SVECTOR direction; // stack address -64
	struct MATRIX temp_matrix; // stack address -56
	int z; // stack address -24
} // line 71, address 0x36bbc
/*
 * Offset 0x36BD4
 * D:\driver2\game\C\DEBRIS.C (line 3029)
 * Stack frame base $sp, length 64
 */
void /*$ra*/ DisplayWater(struct SMOKE *smoke /*$a0*/)
{ // line 1, address 0x36bd4
	struct POLY_FT4 *poly; // $t1
	struct VECTOR v; // stack address -64
	struct SVECTOR vert[4]; // stack address -48
	int length; // $t1
	int z; // $v0
	int z1; // stack address -16
	int z2; // stack address -12
	int z3; // stack address -8
	int z4; // stack address -4
} // line 58, address 0x36e80
/*
 * Offset 0x36E80
 * D:\driver2\game\C\DEBRIS.C (line 3102)
 * Stack frame base $sp, length 40
 */
void /*$ra*/ DisplaySpark(struct SMOKE *spark /*$t1*/)
{ // line 1, address 0x36e80
	int z; // stack address -8
	struct SVECTOR v[3]; // stack address -40
	struct SVECTOR TrailPos; // stack address -16
	struct POLY_G3 *poly; // $t0
	{ // line 33, address 0x36f98
		unsigned char *col; // $a0
	} // line 48, address 0x37048
} // line 68, address 0x371b8
/*
 * Offset 0x371C0
 * D:\driver2\game\C\DEBRIS.C (line 3182)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ GetSmokeDrift(struct VECTOR *Wind /*$t2*/)
{ // line 1, address 0x371c0
	static int SinTabIndex1; // address 0x158
	static int SinTabIndex2; // address 0x15c
	static int SinTabIndex3; // address 0x160
	static int WindMagnitude; // address 0x164
	static int SinX; // address 0x0
	static int CosX; // address 0x4
} // line 33, address 0x372b8
/*
 * Offset 0x372B8
 * D:\driver2\game\C\DEBRIS.C (line 3227)
 * Stack frame base $sp, length 64
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ Setup_Debris(struct VECTOR *ipos /*$fp*/, struct VECTOR *ispeed /*$s6*/, int num_debris /*$s7*/, int type /*$s5*/)
{ // line 1, address 0x372b8
	struct DEBRIS *mydebris; // $s1
	int num; // $v1
	int loop; // $s4
	int vx; // $s2
	int vy; // $s3
	int vz; // $a2
	int seed; // $s0
	int col; // $a3
	{ // line 18, address 0x3735c
	} // line 32, address 0x3741c
} // line 58, address 0x374ac
/*
 * Offset 0x374DC
 * D:\driver2\game\C\DEBRIS.C (line 3296)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ Setup_Smoke(struct VECTOR *ipos /*$s1*/, int start_w /*$s3*/, int end_w /*$s4*/, int SmokeType /*$s7*/, int WheelSpeed /*stack 16*/, struct VECTOR *Drift /*stack 20*/, int Exhaust /*stack 24*/)
{ // line 1, address 0x374dc
	struct SMOKE *mysmoke; // $s0
	int num; // $v1
	{ // line 39, address 0x375fc
	} // line 39, address 0x375fc
	{ // line 76, address 0x37708
	} // line 76, address 0x37708
	{ // line 86, address 0x37754
	} // line 91, address 0x37790
	{ // line 127, address 0x37874
	} // line 138, address 0x378ec
} // line 167, address 0x37988
/*
 * Offset 0x379B8
 * D:\driver2\game\C\DEBRIS.C (line 3475)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ Setup_Sparks(struct VECTOR *ipos /*$fp*/, struct VECTOR *ispeed /*$s7*/, int num_sparks /*stack 8*/, char SparkType /*$s5*/)
{ // line 1, address 0x379b8
	struct SMOKE *mysmoke; // $s2
	int num; // $s0
	int loop; // $s4
	int vx; // $s1
	int vy; // $s0
	int vz; // $v1
	int randtemp; // $v0
	{ // line 12, address 0x37a08
	} // line 74, address 0x37b38
} // line 75, address 0x37b4c
/*
 * Offset 0x37B7C
 * D:\driver2\game\C\DEBRIS.C (line 3564)
 * Stack frame base $sp, length 56
 */
void /*$ra*/ DisplayDebris(struct DEBRIS *debris /*$t2*/, char type /*$t3*/)
{ // line 1, address 0x37b7c
	int pos; // $a1
	int z; // stack address -8
	struct SVECTOR v[4]; // stack address -56
	struct TRI_POINT *tv; // $t1
	struct VECTOR debrisvec; // stack address -24
	struct POLY_FT3 *poly; // $t0
	struct POLY_GT4 *poly1; // $t0
	{ // line 43, address 0x37dfc
		unsigned long cbgr; // $v1
	} // line 54, address 0x37e78
} // line 84, address 0x38068
/*
 * Offset 0x38070
 * D:\driver2\game\C\DEBRIS.C (line 3659)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
void /*$ra*/ HandleDebris()
{ // line 2, address 0x38070
	int count; // $s0
	int i; // $s3
	struct DEBRIS *lpDebris; // $s1
	struct SMOKE *smokeptr; // $s0
	struct VECTOR dummy; // stack address -80
	struct LEAF *lpLeaf; // $s1
	int Height; // $v0
	int SinX; // $s2
	int CosX; // $v1
	struct VECTOR Drift; // stack address -64
	{ // line 193, address 0x38484
		int offshore; // $s1
		struct ROUTE_DATA routeData; // stack address -48
	} // line 205, address 0x3851c
	{ // line 294, address 0x38758
		static int weather_level; // address 0x168
	} // line 307, address 0x387b8
} // line 308, address 0x387e4
/*
 * Offset 0x387E4
 * D:\driver2\game\C\DEBRIS.C (line 3983)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ DisplaySmoke(struct SMOKE *smoke /*$s0*/)
{ // line 1, address 0x387e4
	struct POLY_FT4 *poly; // $t0
	struct VECTOR v; // stack address -80
	struct SVECTOR smokemesh[4]; // stack address -64
	int x; // $s2
	int negx; // $s1
	int z; // stack address -32
	int smoke_z_offset; // $s3
	int tmode; // $a3
	int length; // $v0
	int centrex; // $a1
	int centrey; // $v1
	{ // line 58, address 0x389d8
		char red; // $a0
		char green; // $a1
		char blue; // $v1
	} // line 63, address 0x38a04
} // line 132, address 0x38d00
/*
 * Offset 0x38D1C
 * D:\driver2\game\C\DEBRIS.C (line 4118)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ add_haze(int top_col /*$a0*/, int bot_col /*$a1*/, short ot_pos /*$a2*/)
{ // line 1, address 0x38d1c
	struct TILE *polys; // $a1
} // line 23, address 0x38e68
/*
 * Offset 0x38E70
 * D:\driver2\game\C\DEBRIS.C (line 4208)
 * Stack frame base $sp, length 104
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ DrawRainDrops()
{ // line 2, address 0x38e70
	struct RAIN_TYPE *RainPtr; // $s0
	struct POLY_GT3 *poly; // $a3
	int Count; // $s2
	int z; // stack address -48
	struct SVECTOR v[3]; // stack address -88
	struct VECTOR drift; // stack address -64
	int tpage; // $fp
	int clut; // $s7
	int col; // $s1
	{ // line 51, address 0x3900c
		int notfirst; // $a1
	} // line 88, address 0x391c0
} // line 92, address 0x39204
/*
 * Offset 0x39204
 * D:\driver2\game\C\DEBRIS.C (line 4413)
 * Stack frame base $sp, length 64
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ AddRainDrops()
{ // line 2, address 0x39204
	struct SVECTOR v; // stack address -48
	struct RAIN_TYPE *RainPtr; // $a2
	int RainIndex; // $s0
	int RainNo; // $s1
	int first; // $s3
	static unsigned long rand; // address 0x8
	{ // line 40, address 0x393f0
		int depth; // $v0
	} // line 43, address 0x39418
	{ // line 53, address 0x3944c
		struct ROUTE_DATA routeData; // stack address -40
	} // line 61, address 0x3949c
} // line 64, address 0x394ac
/*
 * Offset 0x394D0
 * D:\driver2\game\C\DEBRIS.C (line 4489)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 s3 s4 ra
 */
void /*$ra*/ DisplaySplashes()
{ // line 2, address 0x394d0
	int SplashNo; // $s4
	int SplashFrac; // $v0
	struct VECTOR CamGnd; // stack address -96
	struct VECTOR Gnd1; // stack address -80
	struct VECTOR Gnd2; // stack address -64
	struct VECTOR Position; // stack address -48
	struct CVECTOR col; // stack address -32
	static unsigned long rand; // address 0x170
	int d1; // $a0
	int d2; // $a2
} // line 58, address 0x39808
/*
 * Offset 0x39828
 * D:\driver2\game\C\DEBRIS.C (line 4550)
 * Stack frame base $sp, length 96
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DisplayLightReflections(struct VECTOR *v1 /*$s1*/, struct CVECTOR *col /*$s3*/, short length /*$a2*/, struct TEXTURE_DETAILS *texture /*$s2*/)
{ // line 1, address 0x39828
	struct SVECTOR vert[4]; // stack address -80
	struct POLY_FT4 *poly; // $a1
	struct CVECTOR thiscol; // stack address -48
	int z; // stack address -40
	int tpage; // $s5
	int clut; // $s4
} // line 52, address 0x39a98
/*
 * Offset 0x39ABC
 * D:\driver2\game\C\DEBRIS.C (line 1686)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ AllocateDebris()
{
}
/*
 * Offset 0x39AF8
 * D:\driver2\game\C\DEBRIS.C (line 1297)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ AllocateLeaf()
{
}
/*
 * Offset 0x39B34
 * D:\driver2\game\C\DEBRIS.C (line 1719)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ AllocateSmoke()
{
}
/*
 * Offset 0x39B70
 * D:\driver2\game\C\DEBRIS.C (line 2200)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ find_lamp_streak(int LampId /*$a0*/)
{ // line 1, address 0x39b70
	int count; // $a1
} // line 17, address 0x39be0
/*
 * Offset 0x39BE0
 * D:\driver2\game\C\DEBRIS.C (line 4607)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DoLightning()
{ // line 2, address 0x39be0
} // line 24, address 0x39cc0
/*
 * Offset 0x39CD0
 * D:\driver2\game\C\DEBRIS.C (line 2447)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ FindCarLightFade(struct MATRIX *carToCamera /*$a0*/)
{ // line 2, address 0x39cd0
	int zz; // $v0
} // line 5, address 0x39cf8
/*
 * Offset 0x39CF8
 * D:\driver2\game\C\DEBRIS.C (line 2428)
 * Stack frame base $sp, length 8
 */
void /*$ra*/ InitFXPos(struct VECTOR *vec /*$a0*/, struct SVECTOR *svec /*$a1*/, struct _CAR_DATA *cp /*$a2*/)
{ // line 1, address 0x39cf8
	struct SVECTOR svectmp; // stack address -8
} // line 9, address 0x39dd0
/*
 * Offset 0x39DD0
 * D:\driver2\game\C\DEBRIS.C (line 1704)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ReleaseDebris(short num /*$a0*/)
{
}
/*
 * Offset 0x39DF4
 * D:\driver2\game\C\DEBRIS.C (line 1313)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ReleaseLeaf(short num /*$a0*/)
{
}
/*
 * Offset 0x39E18
 * D:\driver2\game\C\DEBRIS.C (line 4190)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ReleaseRainDrop(int RainIndex /*$a0*/)
{
}
/*
 * Offset 0x39E3C
 * D:\driver2\game\C\DEBRIS.C (line 1737)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ReleaseSmoke(short num /*$a0*/)
{
}
/*
 * Offset 0x39E60
 * D:\driver2\game\C\DEBRIS.C (line 4152)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetupRain()
{ // line 2, address 0x39e60
} // line 11, address 0x39ebc
/*
 * Offset 0x39EBC
 * D:\driver2\game\C\DEBRIS.C (line 1437)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ SwirlLeaves(struct _CAR_DATA *cp /*$a0*/)
{ // line 1, address 0x39ebc
	int count; // $s2
	struct LEAF *lpLeaf; // $s0
	int XDiff; // $v0
	int ZDiff; // $a1
	struct VECTOR *CarPos; // $s1
	int WheelSpeed; // $a1
	{ // line 38, address 0x39fc8
	} // line 40, address 0x39fec
} // line 44, address 0x39ff8
/*
 * Offset 0x3A010
 * D:\driver2\game\C\DEBRIS.C (line 4725)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ GetDebrisColour(struct _CAR_DATA *cp /*$a0*/)
{ // line 1, address 0x3a010
	int car_model; // $v1
	int palette; // $a0
} // line 17, address 0x3a068
/*
 * Offset 0x3A068
 * D:\driver2\game\C\DEBRIS.C (line 4651)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DoWeather(int weather /*$a0*/)
{
}
/*
 * Offset 0x3A124
 * D:\driver2\game\C\DEBRIS.C (line 4635)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ InitThunder()
{ // line 1, address 0x3a124
} // line 1, address 0x3a188
/*
 * Offset 0x3A188
 * D:\driver2\game\C\DEBRIS.C (line 4636)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ RequestThunder()
{
}
/*
 * Offset 0x3A1AC
 * D:\driver2\game\C\DEBRIS.C (line 4638)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ DoThunder()
{ // line 2, address 0x3a1ac
} // line 9, address 0x3a28c
/*
 * Offset 0x3A29C
 * D:\driver2\game\C\DEBRIS.C (line 1886)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ MoveSmashable_object()
{ // line 2, address 0x3a29c
	int count; // $a3
	struct DAMAGED_OBJECT *dam; // $a1
	{ // line 10, address 0x3a2c0
		int groundlevel; // $v0
	} // line 25, address 0x3a328
} // line 28, address 0x3a33c
/*
 * Offset 0x3A33C
 * D:\driver2\game\C\DEBRIS.C (line 4173)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ AllocateRainDrop()
{
}