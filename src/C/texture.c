
#include "../decomp_defs.h"

SXYPAIR tpagepos[20] =
{
  { 640, 0 },
  { 704, 0 },
  { 768, 0 },
  { 832, 0 },
  { 896, 0 },
  { 960, 0 },
  { 512, 256 },
  { 576, 256 },
  { 640, 256 },
  { 704, 256 },
  { 768, 256 },
  { 832, 256 },
  { 896, 256 },
  { 448, 0 },
  { 512, 0 },
  { 576, 0 },
  { 320, 256 },
  { 384, 256 },
  { 448, 256 },
  { 65535, 65535 }
};

int texture_is_icon = 0;

/*
 * Offset 0x80590
 * D:\driver2\game\C\TEXTURE.C (line 126)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ IncrementTPageNum(struct RECT *tpage /*$t0*/)
{ // line 1, address 0x80590
	int i; // $a3
} // line 27, address 0x80654
/*
 * Offset 0x80654
 * D:\driver2\game\C\TEXTURE.C (line 191)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ Find_TexID(struct MODEL *model /*$t0*/, int t_id /*$a1*/)
{ // line 1, address 0x80654
	char *polylist; // $a2
	int i; // $a3
	{ // line 12, address 0x806a0
	} // line 15, address 0x806b8
	{ // line 18, address 0x806b8
	} // line 21, address 0x806b8
	{ // line 24, address 0x806b8
	} // line 27, address 0x806b8
	{ // line 31, address 0x806b8
	} // line 34, address 0x806b8
	{ // line 38, address 0x806b8
	} // line 41, address 0x806b8
	{ // line 44, address 0x806b8
	} // line 47, address 0x806b8
	{ // line 50, address 0x806b8
	} // line 53, address 0x806b8
	{ // line 56, address 0x806b8
	} // line 59, address 0x806b8
} // line 67, address 0x806f0
/*
 * Offset 0x806F0
 * D:\driver2\game\C\TEXTURE.C (line 378)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ LoadPermanentTPages(int *sector /*$fp*/)
{ // line 1, address 0x806f0
	int tloop; // $s1
	int i; // $s1
	int tset; // $s0
	int nsectors; // $s3
	char *tpagebuffer; // $s2
	{ // line 67, address 0x80944
		int specmodel; // $a1
		int page1; // $s6
		int page2; // $s5
		{ // line 87, address 0x809ec
			int temp; // $s4
			int clutsLoaded; // $s7
		} // line 126, address 0x80b40
	} // line 127, address 0x80b40
} // line 197, address 0x80c18
/*
 * Offset 0x80C18
 * D:\driver2\game\C\TEXTURE.C (line 602)
 * Stack frame base $sp, length 72
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
void /*$ra*/ GetTextureDetails(char *name /*stack 0*/, struct TEXTURE_DETAILS *info /*$s3*/)
{ // line 1, address 0x80c18
	int i; // $s2
	int j; // $s1
	int texamt; // $s4
	struct TEXINF *texinf; // $v1
	char *nametable; // stack address -56
} // line 45, address 0x80dd8
/*
 * Offset 0x80E08
 * D:\driver2\game\C\TEXTURE.C (line 290)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 ra
 */
struct TEXINF * /*$ra*/ GetTextureInfoName(char *name /*$a0*/, struct TPAN *result /*$s0*/)
{ // line 1, address 0x80e08
	int tpagenum; // stack address -16
	int texturenum; // stack address -12
} // line 10, address 0x80e44
/*
 * Offset 0x80E44
 * D:\driver2\game\C\TEXTURE.C (line 116)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ IncrementClutNum(struct RECT *clut /*$a0*/)
{
}
/*
 * Offset 0x80E7C
 * D:\driver2\game\C\TEXTURE.C (line 155)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 ra
 */
int /*$ra*/ LoadTPageAndCluts(struct RECT *tpage /*$s5*/, struct RECT *cluts /*$s2*/, int tpage2send /*$s6*/, char *tpageaddress /*$s0*/)
{ // line 1, address 0x80e7c
	int i; // $s3
	int npalettes; // $s4
	struct RECT temptpage; // stack address -40
} // line 30, address 0x80fa4
/*
 * Offset 0x80FA4
 * D:\driver2\game\C\TEXTURE.C (line 261)
 * Stack frame base $sp, length 56
 * Saved registers at address -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
 */
struct TEXINF * /*$ra*/ GetTEXINFName(char *name /*$fp*/, int *tpagenum /*stack 4*/, int *texturenum /*stack 8*/)
{ // line 1, address 0x80fa4
	int i; // $s4
	int j; // $s1
	int texamt; // $s2
	struct TEXINF *texinf; // $s3
	char *nametable; // $s6
} // line 26, address 0x810a0
/*
 * Offset 0x810A0
 * D:\driver2\game\C\TEXTURE.C (line 334)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ update_slotinfo(int tpage /*$a0*/, int slot /*$a1*/, struct RECT *pos /*$a2*/)
{
}
/*
 * Offset 0x810E8
 * D:\driver2\game\C\TEXTURE.C (line 347)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ ProcessTextureInfo(char *lump_ptr /*$a1*/)
{ // line 1, address 0x810e8
	int i; // $a0
} // line 28, address 0x81180
/*
 * Offset 0x81180
 * D:\driver2\game\C\TEXTURE.C (line 578)
 * Stack frame base $sp, length 104
 * Saved registers at address -8: ra
 */
void /*$ra*/ ReloadIcons()
{ // line 2, address 0x81180
	struct RECT tpage; // stack address -88
	struct RECT clutpos; // stack address -80
	char name[64]; // stack address -72
} // line 21, address 0x811a8