#include "../decomp_defs.h"

int sky_y_offset[4] = { 14, 14, 14, 14 };

unsigned char HorizonLookup[4][4] = {
	{0, 0, 0x14, 0x14},
	{0x14, 0x14, 0, 0},
	{0, 0, 0x14, 0x14},
	{0, 0, 0x14, 0x14},
};

unsigned char HorizonTextures[40] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB,
	0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13,
	0, 1, 2, 3, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1A, 0x1B, 0x10, 0x11, 0x12, 0x13
};

SVECTOR sun_position[4] =
{
  { 33536, 54536, 60536, 0 },
  { 33536, 54536, 60536, 0 },
  { 33536, 54536, 60536, 0 },
  { 33536, 54536, 60536, 0 }
};

SVECTOR moon_position[4] =
{
  { 33536, 54036, 47536, 0 },
  { 33536, 54036, 47536, 0 },
  { 33536, 54036, 47536, 0 },
  { 33536, 54036, 47536, 0 }
};

SVECTOR moon_shadow_position[4] =
{
  { 33536, 54036, 47536, 0 },
  { 33536, 54036, 47536, 0 },
  { 33536, 54036, 47536, 0 },
  { 33536, 10500, 47536, 0 }
};

FLAREREC flare_info[8] =
{
  { { 0, 0, 90, 0 }, '\x10', 12288 },
  { { 20480, 10240, 1024, 0 }, '\0', 48 },
  { { 72, 90, 0, 0 }, '\0', 12288 },
  { { 24576, 0, 23040, 0 }, '\0', 0 },
  { { 16, 144, 0, 0 }, 'Z', 0 },
  { { 16384, 40960, 23040, 23040 }, '\0', 0 },
  { { 0, 32, 184, 90 }, '\0', 0 },
  { { 0, 8192, 53248, 0 }, '\0', 0 }
};

VECTOR tunnelPos[3][2] =
{
	{
		{ 4294568646, 0, 4294806296, 0 },
		{ 4294626996, 2000, 4294864296, 0 }
	},
	{
		{ 272800, 0, 41200, 0 },
		{ 271963, 2000, 168187, 0 }
	},

	{ 
		{ 4294852196, 0, 4294774096, 0 },
		{ 4294853996, 4294966896, 4294834796, 0 }
	}
};



/*
 * Offset 0x77630
 * D:\driver2\game\C\SKY.C (line 145)
 * Stack frame base $sp, length 112
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ LoadSky()
{ // line 2, address 0x77630
	struct RECT rect; // stack address -96
	char name[16]; // stack address -88
	int x; // $s6
	int y; // $a1
	int i; // $t1
	int u; // $v1
	int v; // $s2
	int skynum; // $a2
	int address; // stack address -72
	{ // line 11, address 0x77670
		int flipped; // $t0
		int single; // $s5
		int ry; // $a2
	} // line 113, address 0x77838
} // line 174, address 0x779c4
/*
 * Offset 0x779C4
 * D:\driver2\game\C\SKY.C (line 327)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ DrawSkyDome()
{
}
/*
 * Offset 0x77AF4
 * D:\driver2\game\C\SKY.C (line 351)
 * Stack frame base $sp, length 80
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ DrawLensFlare()
{ // line 2, address 0x77af4
	static char last_attempt_failed; // address 0x0
	static short buffer[160]; // address 0x0
	struct DVECTOR sun_pers_conv_position; // stack address -64
	struct RECT source; // stack address -56
	struct DR_MOVE *sample_sun; // $s0
	int distance_to_sun; // $s0
	int xpos; // $t1
	int ypos; // $v0
	int xgap; // $s4
	int ygap; // $s2
	int flarez; // stack address -40
	int shade; // $t4
	int sun_intensity; // $s3
	struct POLY_FT4 *polys; // $a1
	struct CVECTOR col; // stack address -48
	int r; // $a2
	int g; // $a3
	int b; // $a0
	{ // line 36, address 0x77bc0
		int bufferX; // $a0
		int bufferY; // $v1
		unsigned short *pwBuffer; // $s0
	} // line 54, address 0x77c28
	{ // line 95, address 0x77d9c
		int temp; // $v0
		{ // line 107, address 0x77e38
			struct FLAREREC *pFlareInfo; // $t3
			int flaresize; // $t0
		} // line 144, address 0x78014
	} // line 145, address 0x78014
} // line 167, address 0x78100
/*
 * Offset 0x78124
 * D:\driver2\game\C\SKY.C (line 527)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 s3
 */
void /*$ra*/ DisplaySun(struct DVECTOR *pos /*$a0*/, struct CVECTOR *col /*$a1*/, int flare_col /*$a2*/)
{ // line 1, address 0x78124
	struct POLY_FT4 *polys; // $a1
	struct POLY_FT3 *null; // $a3
	struct VECTOR output; // stack address -32
	int width; // $t5
	int height; // $t4
} // line 73, address 0x785ac
/*
 * Offset 0x785AC
 * D:\driver2\game\C\SKY.C (line 609)
 * Stack frame base $sp, length 16
 */
void /*$ra*/ DisplayMoon(struct DVECTOR *pos /*$t4*/, struct CVECTOR *col /*$t6*/, int flip /*$a2*/)
{ // line 1, address 0x785ac
	struct POLY_FT3 *null; // $a0
	struct VECTOR output; // stack address -16
	int width; // $t5
	int height; // $t3
} // line 40, address 0x78818
/*
 * Offset 0x78818
 * D:\driver2\game\C\SKY.C (line 679)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ TunnelSkyFade()
{ // line 2, address 0x78818
	int tun; // $a3
	{ // line 16, address 0x78840
		int diffX; // $v1
		int diffZ; // $v0
		int dX; // $v1
		int dZ; // $v0
		int len; // $a1
		struct VECTOR *v1; // $t1
		struct VECTOR *v2; // $t0
		{ // line 46, address 0x788dc
			int l2; // $v1
		} // line 66, address 0x78950
	} // line 97, address 0x789c4
} // line 98, address 0x789c4
/*
 * Offset 0x789CC
 * D:\driver2\game\C\SKY.C (line 785)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
void /*$ra*/ calc_sky_brightness()
{
}
/*
 * Offset 0x78B80
 * D:\driver2\game\C\SKY.C (line 855)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ PlotSkyPoly(int skytexnum /*$t5*/, unsigned char r /*$a1*/, unsigned char g /*$a2*/, unsigned char b /*$a3*/, int address /*stack 16*/)
{ // line 1, address 0x78b80
	struct POLYFT4 *src; // $t1
	struct DVECTOR *outpoints; // $t0
	struct POLY_FT4 *prims; // $t2
} // line 39, address 0x78f24
/*
 * Offset 0x78F2C
 * D:\driver2\game\C\SKY.C (line 896)
 * Stack frame base $sp, length 80
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ PlotHorizonMDL(struct MODEL *model /*$s6*/, int horizontaboffset /*$a1*/)
{ // line 1, address 0x78f2c
	struct SVECTOR *verts; // $v1
	char *polys; // $s1
	int i; // $s0
	int p; // stack address -56
	int flag; // stack address -52
	short *zbuff; // $t5
	int z; // stack address -48
	unsigned char r; // $s5
	unsigned char g; // $s4
	unsigned char b; // $s3
} // line 49, address 0x7911c