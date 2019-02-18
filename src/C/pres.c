#include "../decomp_defs.h"

FONT_DIGIT fontDigit[] = {
	{ 2, 0xE },
	{ 0x11, 0xE},
	{ 0x20, 0x10},
	{ 0x31, 0xF},
	{ 0x41, 0xE },
	{ 0x50, 0xE },
	{ 4, 0x10 },
	{ 0x15, 0xE },
	{ 0x24, 0xF },
	{ 0x34, 0x11 },
	{ 0x46, 0xB },
	{ 0x52, 7 },
};

TEXTURE_DETAILS button_textures[11];

char* button_names[11] = {
	"BTNTRIAN",
	"BTNCIRCL",
	"BTNCROSS",
	"BTNSQUAR",
	"BTNUP",
	"BTNDOWN",
	"BTNLEFT",
	"BTNRIGHT",
	"BTNSTART",
	"BTNSELEC",
	"BTNDPAD",
};

/*
 * Offset 0x73D30
 * D:\driver2\game\C\PRES.C (line 360)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ LoadFont(char *buffer /*$a0*/)
{ // line 1, address 0x73d30
	struct RECT dest; // stack address -24
	char *file; // $s1
	int i; // $v1
	int nchars; // $s0
} // line 48, address 0x73f08
/*
 * Offset 0x73F08
 * D:\driver2\game\C\PRES.C (line 457)
 * Stack frame base $sp, length 56
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 s6 s7 ra
 */
int /*$ra*/ PrintString(char *string /*$s3*/, int x /*$s2*/, int y /*$s6*/)
{ // line 1, address 0x73f08
	struct OUT_FONTINFO *pFontInfo; // $a1
	struct SPRT *font; // $s0
	unsigned char width; // $s1
	unsigned char c; // $s1
	int index; // $v1
} // line 79, address 0x741a8
/*
 * Offset 0x741A8
 * D:\driver2\game\C\PRES.C (line 539)
 * Stack frame base $sp, length 8
 * Saved registers at address -4: s0 s1
 */
short /*$ra*/ PrintDigit(int x /*$t3*/, int y /*$s1*/, char *string /*$a2*/)
{ // line 1, address 0x741a8
	struct FONT_DIGIT *pDigit; // $a1
	struct SPRT *font; // $t0
	char width; // $a3
	char fixedWidth; // $t1
	char vOff; // $t2
	char h; // $a0
	{ // line 13, address 0x741f8
		char let; // $v1
		char convLet; // $a0
	} // line 44, address 0x7425c
} // line 67, address 0x743cc
/*
 * Offset 0x743CC
 * D:\driver2\game\C\PRES.C (line 643)
 * Stack frame base $sp, length 80
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
void /*$ra*/ PrintStringBoxed(char *string /*$s2*/, int ix /*$s5*/, int iy /*$a2*/)
{ // line 1, address 0x743cc
	struct OUT_FONTINFO *pFontInfo; // $a1
	struct SPRT *font; // $s0
	char word[32]; // stack address -64
	char *wpt; // $t0
	char c; // $a0
	int x; // $s1
	int y; // $s3
	int index; // $a1
	int wordcount; // $s4
} // line 68, address 0x74644
/*
 * Offset 0x74644
 * D:\driver2\game\C\PRES.C (line 726)
 * Stack frame base $sp, length 48
 * Saved registers at address -8: s0 s1 s2 s3 s4 s5 ra
 */
int /*$ra*/ PrintScaledString(int y /*$s4*/, char *string /*$s1*/, int scale /*$s2*/)
{ // line 1, address 0x74644
	struct FONT_DIGIT *pDigit; // $a2
	struct POLY_FT4 *font; // $t0
	int x; // $s0
	int width; // $t3
	int height; // $t6
	int y0; // $t1
	int x1; // $t5
	int y1; // $v0
	unsigned char vOff; // $t8
	char c; // $a0
} // line 68, address 0x748c0
/*
 * Offset 0x748C0
 * D:\driver2\game\C\PRES.C (line 819)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void * /*$ra*/ DrawButton(unsigned char button /*$a0*/, void *prim /*$s1*/, int x /*$a2*/, int y /*$a3*/)
{ // line 1, address 0x748c0
	struct TEXTURE_DETAILS *btn; // $a1
	struct POLY_FT3 *null; // $s0
} // line 34, address 0x74a78
/*
 * Offset 0x74A78
 * D:\driver2\game\C\PRES.C (line 228)
 * Stack frame base $sp, length 0
 */
void /*$ra*/ SetTextColour(unsigned char Red /*$a0*/, unsigned char Green /*$a1*/, unsigned char Blue /*$a2*/)
{
}
/*
 * Offset 0x74A8C
 * D:\driver2\game\C\PRES.C (line 245)
 * Stack frame base $sp, length 0
 */
int /*$ra*/ StringWidth(char *pString /*$a0*/)
{ // line 1, address 0x74a8c
	int w; // $a2
	char let; // $a1
	{ // line 11, address 0x74ac8
		char convLet; // $v1
	} // line 21, address 0x74b00
} // line 24, address 0x74b18
/*
 * Offset 0x74B18
 * D:\driver2\game\C\PRES.C (line 285)
 * Stack frame base $sp, length 40
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
int /*$ra*/ OutputString(char *pString /*$s2*/, int formatting /*$s0*/, int x /*$a2*/, int y /*$s3*/, int xw /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
{ // line 1, address 0x74b18
	int xpos; // $s1
	{ // line 17, address 0x74b7c
	} // line 17, address 0x74b7c
} // line 38, address 0x74bf4
/*
 * Offset 0x74BF4
 * D:\driver2\game\C\PRES.C (line 333)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ PrintStringRightAligned(char *pString /*$s1*/, int x /*$s0*/, int y /*$s2*/)
{
}
/*
 * Offset 0x74C40
 * D:\driver2\game\C\PRES.C (line 347)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: s0 s1 ra
 */
void /*$ra*/ PrintStringCentred(char *pString /*$s1*/, short y /*$a1*/)
{ // line 1, address 0x74c40
} // line 5, address 0x74c90
/*
 * Offset 0x74C90
 * D:\driver2\game\C\PRES.C (line 416)
 * Stack frame base $sp, length 32
 * Saved registers at address -8: ra
 */
void /*$ra*/ StoreClut2(unsigned long *pDest /*$a1*/, int x /*$a1*/, int y /*$a2*/)
{ // line 1, address 0x74c90
	struct RECT rect; // stack address -16
} // line 10, address 0x74ccc
/*
 * Offset 0x74CCC
 * D:\driver2\game\C\PRES.C (line 434)
 * Stack frame base $sp, length 72
 * Saved registers at address -8: s0 s1 s2 s3 ra
 */
void /*$ra*/ SetCLUT16Flags(unsigned short clutID /*$a0*/, unsigned short mask /*$s2*/, char transparent /*$s0*/)
{ // line 1, address 0x74ccc
	unsigned short buffer[16]; // stack address -56
	unsigned short *pCurrent; // $a0
	char ctr; // $a1
	int x; // $s3
	int y; // $s1
} // line 21, address 0x74d9c
/*
 * Offset 0x74D9C
 * D:\driver2\game\C\PRES.C (line 612)
 * Stack frame base $sp, length 24
 * Saved registers at address -8: ra
 */
int /*$ra*/ PrintStringFeature(char *string /*$a0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/, int transparent /*stack 20*/)
{
}
/*
 * Offset 0x74DBC
 * D:\driver2\game\C\PRES.C (line 800)
 * Stack frame base $sp, length 0
 */
char * /*$ra*/ GetNextWord(char *string /*$a0*/, char *word /*$a1*/)
{ // line 1, address 0x74dbc
	char c; // $v1
} // line 17, address 0x74dfc
/*
 * Offset 0x74DFC
 * D:\driver2\game\C\PRES.C (line 855)
 * Stack frame base $sp, length 24
 * Saved registers at address -4: s0 ra
 */
void * /*$ra*/ SetFontTPage(void *prim /*$a0*/)
{ // line 1, address 0x74dfc
	struct POLY_FT3 *null; // $s0
} // line 16, address 0x74ebc
/*
 * Offset 0x74EBC
 * D:\driver2\game\C\PRES.C (line 713)
 * Stack frame base $sp, length 32
 * Saved registers at address -4: s0 s1 s2 ra
 */
void /*$ra*/ InitButtonTextures()// (F)
{ // line 2, address 0x74ebc
	int i; // $s0
	for (i = 0; i < 11; i++)
	{
		GetTextureDetails(button_names[i], &button_textures[i]);
	}
} // line 6, address 0x74f1c