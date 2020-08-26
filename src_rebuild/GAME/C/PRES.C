#include "THISDUST.H"
#include "PRES.H"
#include "SYSTEM.H"
#include "TEXTURE.H"

#include <STRING.H>

extern TEXTURE_DETAILS digit_texture;

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

CVECTOR gFontColour;

short fonttpage = 0;
short fontclutid = 0;

char AsciiTable[256] = { 0 };
OUT_FONTINFO fontinfo[128];

// decompiled code
// original method signature: 
// void /*$ra*/ SetTextColour(unsigned char Red /*$a0*/, unsigned char Green /*$a1*/, unsigned char Blue /*$a2*/)
 // line 228, offset 0x00074a10
	/* begin block 1 */
		// Start line: 1308
	/* end block 1 */
	// End Line: 1309

	/* begin block 2 */
		// Start line: 456
	/* end block 2 */
	// End Line: 457

	/* begin block 3 */
		// Start line: 1309
	/* end block 3 */
	// End Line: 1310

// [D]
void SetTextColour(unsigned char Red, unsigned char Green, unsigned char Blue)
{
	gFontColour.r = Red;
	gFontColour.g = Green;
	gFontColour.b = Blue;
}



// decompiled code
// original method signature: 
// int /*$ra*/ StringWidth(char *pString /*$a0*/)
 // line 245, offset 0x00074a24
	/* begin block 1 */
		// Start line: 246
		// Start offset: 0x00074A24
		// Variables:
	// 		int w; // $a2
	// 		char let; // $a1

		/* begin block 1.1 */
			// Start line: 256
			// Start offset: 0x00074A60
			// Variables:
		// 		char convLet; // $v1
		/* end block 1.1 */
		// End offset: 0x00074A98
		// End Line: 266
	/* end block 1 */
	// End offset: 0x00074AB0
	// End Line: 269

	/* begin block 2 */
		// Start line: 1342
	/* end block 2 */
	// End Line: 1343

	/* begin block 3 */
		// Start line: 1343
	/* end block 3 */
	// End Line: 1344

// [D]
int StringWidth(char *pString)
{
	char bVar1;
	char *pbVar2;
	int iVar3;

	iVar3 = 0;
	bVar1 = *pString;
	pbVar2 = (pString + 1);
	while (bVar1 != 0) {
		if (bVar1 == 0x20) {
			iVar3 = iVar3 + 4;
		}
		else {
			if (((uint)bVar1 + 0x80 & 0xff) < 0xb) {
				iVar3 = iVar3 + 0x18;
			}
			else {
				if (AsciiTable[(uint)bVar1] != 0xff) {
					iVar3 = iVar3 + (uint)fontinfo[AsciiTable[(uint)bVar1]].width;
				}
			}
		}
		bVar1 = *pbVar2;
		pbVar2 = pbVar2 + 1;
	}
	return iVar3;
}



// decompiled code
// original method signature: 
// int /*$ra*/ OutputString(char *pString /*$s2*/, int formatting /*$s0*/, int x /*$a2*/, int y /*$s3*/, int xw /*stack 16*/, int r /*stack 20*/, int g /*stack 24*/, int b /*stack 28*/)
 // line 285, offset 0x00074ab0
	/* begin block 1 */
		// Start line: 286
		// Start offset: 0x00074AB0
		// Variables:
	// 		int xpos; // $s1

		/* begin block 1.1 */
			// Start line: 302
			// Start offset: 0x00074B14
		/* end block 1.1 */
		// End offset: 0x00074B14
		// End Line: 302
	/* end block 1 */
	// End offset: 0x00074B8C
	// End Line: 323

	/* begin block 2 */
		// Start line: 1405
	/* end block 2 */
	// End Line: 1406

	/* begin block 3 */
		// Start line: 1422
	/* end block 3 */
	// End Line: 1423

	/* begin block 4 */
		// Start line: 1423
	/* end block 4 */
	// End Line: 1424

// [D]
int OutputString(char *pString, int formatting, int x, int y, int xw, int r, int g, int b)
{
	int iVar1;

	SetTextColour((unsigned char)r, (unsigned char)g, (unsigned char)b);

	if ((formatting & 1U) == 0) {
		if ((formatting & 2U) == 0) {
			if ((formatting & 4U) != 0) {
				iVar1 = StringWidth(pString);
				PrintString(pString, x - iVar1, y);
			}
		}
		else {
			iVar1 = StringWidth(pString);
			x = (x + (xw - iVar1 >> 1)) * 0x10000 >> 0x10;
			PrintString(pString, x, y);
		}
	}
	else {
		PrintString(pString, x, y);
	}

	return x;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PrintStringRightAligned(char *pString /*$s1*/, int x /*$s0*/, int y /*$s2*/)
 // line 333, offset 0x00074b8c
	/* begin block 1 */
		// Start line: 1514
	/* end block 1 */
	// End Line: 1515

	/* begin block 2 */
		// Start line: 1525
	/* end block 2 */
	// End Line: 1526

// [D]
void PrintStringRightAligned(char *pString, int x, int y)
{
	int iVar1;

	iVar1 = StringWidth(pString);
	PrintString(pString, x - iVar1, y);
}



// decompiled code
// original method signature: 
// void /*$ra*/ PrintStringCentred(char *pString /*$s1*/, short y /*$a1*/)
 // line 347, offset 0x00074bd8
	/* begin block 1 */
		// Start line: 348
		// Start offset: 0x00074BD8
	/* end block 1 */
	// End offset: 0x00074C28
	// End Line: 352

	/* begin block 2 */
		// Start line: 1553
	/* end block 2 */
	// End Line: 1554

// [D]
void PrintStringCentred(char *pString, short y)
{
	int iVar1;

	iVar1 = StringWidth(pString);
	PrintString(pString, (0x140 - iVar1) * 0x8000 >> 0x10, y);
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadFont(char *buffer /*$a0*/)
 // line 360, offset 0x00073cc8
	/* begin block 1 */
		// Start line: 361
		// Start offset: 0x00073CC8
		// Variables:
	// 		struct RECT dest; // stack offset -24
	// 		char *file; // $s1
	// 		int i; // $v1
	// 		int nchars; // $s0
	/* end block 1 */
	// End offset: 0x00073EA0
	// End Line: 408

	/* begin block 2 */
		// Start line: 720
	/* end block 2 */
	// End Line: 721

	/* begin block 3 */
		// Start line: 722
	/* end block 3 */
	// End Line: 723

// [D]
void LoadFont(char *buffer)
{
	int *piVar1;
	char *pcVar2;
	u_long *puVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int *addr;
	RECT16 rect;

	fontclutpos.x = 976;
	fontclutpos.y = 256;
	fontclutpos.w = 16;
	fontclutpos.h = 1;
	//addr = (int *)&DAT_0011b400;		// [A] FIXME: this font address might be used somewhere else
	addr = (int*)_frontend_buffer;
	if (buffer != NULL) {
		addr = (int *)buffer;
	}
	Loadfile("GFX\\FONT2.FNT", (char *)addr);
	iVar6 = *addr;
	memcpy(fontinfo, addr + 1, iVar6 * 8);
	addr = addr + 1 + iVar6 * 2;
	pcVar2 = AsciiTable;

	memcpy(AsciiTable, addr, 256);

	fontclutid = GetClut((int)fontclutpos.x, (int)fontclutpos.y);
	iVar6 = 0xf;
	puVar3 = (u_long *)(addr + 0x40);
	do {
		iVar6 = iVar6 + -1;
		*(ushort *)puVar3 = *(ushort *)puVar3 & 0x7fff;
		puVar3 = (u_long *)((int)puVar3 + 2);
	} while (-1 < iVar6);
	*(ushort *)((int)addr + 0x102) = *(ushort *)((int)addr + 0x102) | 0x8000;
	*(ushort *)(addr + 0x41) = *(ushort *)(addr + 0x41) | 0x8000;
	LoadImage(&fontclutpos, (u_long *)(addr + 0x40));
	rect.x = 960;
	rect.y = 466;
	rect.w = 64;
	rect.h = 46;
	fonttpage = GetTPage(0, 0, 960, 466);
	LoadImage(&rect, (u_long *)(addr + 0x48));
	DrawSync(0);
	return;
}



// decompiled code
// original method signature: 
// void /*$ra*/ StoreClut2(unsigned long *pDest /*$a1*/, int x /*$a1*/, int y /*$a2*/)
 // line 416, offset 0x00074c28
	/* begin block 1 */
		// Start line: 417
		// Start offset: 0x00074C28
		// Variables:
	// 		struct RECT rect; // stack offset -16
	/* end block 1 */
	// End offset: 0x00074C64
	// End Line: 426

	/* begin block 2 */
		// Start line: 1628
	/* end block 2 */
	// End Line: 1629

	/* begin block 3 */
		// Start line: 1693
	/* end block 3 */
	// End Line: 1694

	/* begin block 4 */
		// Start line: 1696
	/* end block 4 */
	// End Line: 1697

// [D]
void StoreClut2(ulong *pDest, int x, int y)
{
	RECT16 local_10;

	local_10.x = (short)x;
	local_10.y = (short)y;
	local_10.w = 0x10;
	local_10.h = 1;
	StoreImage2(&local_10, pDest);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetCLUT16Flags(unsigned short clutID /*$a0*/, unsigned short mask /*$s2*/, char transparent /*$s0*/)
 // line 434, offset 0x00074c64
	/* begin block 1 */
		// Start line: 435
		// Start offset: 0x00074C64
		// Variables:
	// 		unsigned short buffer[16]; // stack offset -56
	// 		unsigned short *pCurrent; // $a0
	// 		char ctr; // $a1
	// 		int x; // $s3
	// 		int y; // $s1
	/* end block 1 */
	// End offset: 0x00074D34
	// End Line: 455

	/* begin block 2 */
		// Start line: 1731
	/* end block 2 */
	// End Line: 1732

	/* begin block 3 */
		// Start line: 1740
	/* end block 3 */
	// End Line: 1741

// [D]
void SetCLUT16Flags(ushort clutID, ushort mask, char transparent)
{
#ifdef PSX
	ushort uVar1;
	ushort *puVar2;
	uint uVar3;
	ushort *pCurrent;
	int x;
	ushort buffer[16];

	x = ((uint)clutID & 0x3f) << 4;

	StoreClut2((ulong *)buffer, x, (uint)(clutID >> 6));

	pCurrent = buffer + transparent;
	uVar3 = 1;

	// [A]
	while ((pCurrent - buffer) < 16)
	{
		if (((int)(uint)mask >> (uVar3 & 0x1f) & 1U) == 0) 
		{
			uVar1 = *pCurrent & 0x7fff;
		}
		else 
		{
			uVar1 = *pCurrent | 0x8000;
		}

		*pCurrent++ = uVar1;
		uVar3 = uVar3 + 1 & 0xff;
	}

	LoadClut2((u_long*)buffer, x, (uint)(clutID >> 6));
#endif // PSX
}



// decompiled code
// original method signature: 
// int /*$ra*/ PrintString(char *string /*$s3*/, int x /*$s2*/, int y /*$s6*/)
 // line 457, offset 0x00073ea0
	/* begin block 1 */
		// Start line: 458
		// Start offset: 0x00073EA0
		// Variables:
	// 		struct OUT_FONTINFO *pFontInfo; // $a1
	// 		struct SPRT *font; // $s0
	// 		unsigned char width; // $s1
	// 		unsigned char c; // $s1
	// 		int index; // $v1
	/* end block 1 */
	// End offset: 0x00074140
	// End Line: 536

	/* begin block 2 */
		// Start line: 895
	/* end block 2 */
	// End Line: 896

	/* begin block 3 */
		// Start line: 945
	/* end block 3 */
	// End Line: 946

	/* begin block 4 */
		// Start line: 953
	/* end block 4 */
	// End Line: 954

// MAP.C ????
extern int gShowMap;

// [D]
int PrintString(char *string, int x, int y)
{
	u_char chr;
	char bVar1;
	unsigned char uVar2;
	int iVar3;
	short sVar4;
	DB *pDVar5;
	int x_00;
	char *pcVar6;
	uint uVar7;
	SPRT *font;
	char *pbVar8;

	int showMap = gShowMap;

	x_00 = -1;
	if (current != NULL)
	{
		font = (SPRT *)current->primptr;

		if (showMap != 0)
			font = (SPRT *)SetFontTPage(font);

		chr = *string;
		pbVar8 = (string + 1);
		x_00 = x;
		while (chr != 0) 
		{
			if (chr == 0x20)
			{
				x_00 = x_00 + 4;
			}
			else
			{
				if (chr < 0x20 || 0x8a < chr || chr < 0x80) 
				{
					bVar1 = AsciiTable[chr];
					if (AsciiTable[chr] == 0xff)
						bVar1 = AsciiTable[63];

					uVar7 = (uint)bVar1;
					chr = fontinfo[uVar7].width;

					setSprt(font);
#ifdef PSX
					setSemiTrans(font, 1);
#endif

					//*(undefined *)((int)&font->tag + 3) = 4;
					//font->code = 'f';

					font->r0 = gFontColour.r;
					font->g0 = gFontColour.g;
					uVar2 = gFontColour.b;
					font->x0 = (short)x_00;
					font->b0 = uVar2;
					font->y0 = (short)fontinfo[uVar7].offy + (short)y;
					font->u0 = fontinfo[uVar7].x;
					uVar2 = fontinfo[uVar7].y;
					font->w = (ushort)chr;
					font->v0 = uVar2 - 46;
					sVar4 = fontclutid;

					font->h = (ushort)fontinfo[uVar7].height;
					font->clut = sVar4;
					pDVar5 = current;

					if (showMap == 0)
					{
						addPrim(current->ot, font);
					}
					else 
					{
						DrawPrim(font);
					}

					font = font + 1;
					x_00 = x_00 + (uint)chr;
				}
				else
				{
					if (showMap == 0)
						font = (SPRT *)SetFontTPage(font);

					font = (SPRT *)DrawButton(chr, font, x_00, y);
					x_00 = x_00 + 0x18;

					if (showMap != 0)
						font = (SPRT *)SetFontTPage(font);
				}
			}
			chr = *pbVar8;
			pbVar8 = pbVar8 + 1;
		}

		if (showMap == 0)
			current->primptr = (char *)SetFontTPage(font);
		else
			DrawSync(0);
	}

	return x_00;
}



// decompiled code
// original method signature: 
// short /*$ra*/ PrintDigit(int x /*$t3*/, int y /*$s1*/, char *string /*$a2*/)
 // line 539, offset 0x00074140
	/* begin block 1 */
		// Start line: 540
		// Start offset: 0x00074140
		// Variables:
	// 		struct FONT_DIGIT *pDigit; // $a1
	// 		struct SPRT *font; // $t0
	// 		char width; // $a3
	// 		char fixedWidth; // $t1
	// 		char vOff; // $t2
	// 		char h; // $a0

		/* begin block 1.1 */
			// Start line: 552
			// Start offset: 0x00074190
			// Variables:
		// 		char let; // $v1
		// 		char convLet; // $a0
		/* end block 1.1 */
		// End offset: 0x000741F4
		// End Line: 583
	/* end block 1 */
	// End offset: 0x00074364
	// End Line: 606

	/* begin block 2 */
		// Start line: 1125
	/* end block 2 */
	// End Line: 1126

	/* begin block 3 */
		// Start line: 1129
	/* end block 3 */
	// End Line: 1130

// [D]
short PrintDigit(int x, int y, char *string)
{
	char bVar1;
	char bVar2;
	unsigned char uVar3;
	DB *pDVar4;
	short sVar5;
	uint uVar6;
	ulong *puVar7;
	SPRT *font;
	int iVar8;
	char cVar9;

	sVar5 = (short)x;
	bVar1 = *string;

	while (bVar1 != 0) 
	{
		bVar1 = *string;
		string++;

		if (bVar1 == 0x3a)
		{
			uVar6 = 0xb;
		}
		else if (bVar1 == 0x2f) 
		{
			uVar6 = 10;
		}
		else 
		{
			uVar6 = (uint)bVar1 - 0x30 & 0xff;
		}

		bVar2 = fontDigit[uVar6].width;
		iVar8 = 0x10;

		if (bVar1 == 0x3a) 
		{
			iVar8 = 8;
		}

		cVar9 = '\0';

		if (uVar6 < 6) 
		{
			sVar5 = 0x1c;
		}
		else 
		{
			cVar9 = '\x1c';
			sVar5 = 0x1f;
		}

		font = (SPRT *)current->primptr;
		current->primptr += sizeof(SPRT);

		setSprt(font);
#ifdef PSX
		setSemiTrans(font, 1);
#endif

		font->r0 = gFontColour.r;
		font->g0 = gFontColour.g;
		font->b0 = gFontColour.b;

		font->x0 = (short)x + (short)((int)(iVar8 - (uint)bVar2) >> 1);
		font->y0 = (short)y;
		
		font->u0 = digit_texture.coords.u0 + fontDigit[uVar6].xOffset;
		font->v0 = cVar9 + digit_texture.coords.v0;

		font->w = (ushort)bVar2;
		font->h = sVar5;
		
		pDVar4 = current;
		font->clut = digit_texture.clutid;

		addPrim(current->ot, font);
		
		x = x + iVar8;
		sVar5 = (short)x;

		bVar1 = *string;
		font = font + 1;
	}

	POLY_FT3* null = (POLY_FT3*)current->primptr;
	setPolyFT3(null);
#ifdef PSX
	setSemiTrans(null, 1);
#endif

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = digit_texture.tpageid;
	
	addPrim(current->ot, null);
	current->primptr += sizeof(POLY_FT3);

	pDVar4 = current;
	
	return sVar5;
}



// decompiled code
// original method signature: 
// int /*$ra*/ PrintStringFeature(char *string /*$a0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/, int transparent /*stack 20*/)
 // line 612, offset 0x00074d34
	/* begin block 1 */
		// Start line: 1968
	/* end block 1 */
	// End Line: 1969

	/* begin block 2 */
		// Start line: 2126
	/* end block 2 */
	// End Line: 2127

	/* begin block 3 */
		// Start line: 2127
	/* end block 3 */
	// End Line: 2128

// [D]
int PrintStringFeature(char *string, int x, int y, int w, int h, int transparent)
{
	int iVar1;

	iVar1 = PrintString(string, x, y);
	return iVar1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ PrintStringBoxed(char *string /*$s2*/, int ix /*$s5*/, int iy /*$a2*/)
 // line 643, offset 0x00074364
	/* begin block 1 */
		// Start line: 644
		// Start offset: 0x00074364
		// Variables:
	// 		struct OUT_FONTINFO *pFontInfo; // $a1
	// 		struct SPRT *font; // $s0
	// 		char word[32]; // stack offset -64
	// 		char *wpt; // $t0
	// 		char c; // $a0
	// 		int x; // $s1
	// 		int y; // $s3
	// 		int index; // $a1
	// 		int wordcount; // $s4
	/* end block 1 */
	// End offset: 0x000745DC
	// End Line: 711

	/* begin block 2 */
		// Start line: 1338
	/* end block 2 */
	// End Line: 1339

	/* begin block 3 */
		// Start line: 1376
	/* end block 3 */
	// End Line: 1377

	/* begin block 4 */
		// Start line: 1387
	/* end block 4 */
	// End Line: 1388

// [D] [A]
void PrintStringBoxed(char *string, int ix, int iy)
{
	SPRT *font;
	char word[32];
	char *wpt;
	int x;
	int y;
	int index;
	int wordcount;

	font = (SPRT *)current->primptr;

	if (*string != 0) 
	{
		wordcount = 1;
		
		x = ix;
		y = iy;

		do
		{
			string = GetNextWord(string, word);

			if ((x + StringWidth(word)) > 308 && (wordcount != 1 || (*string != 0)))
			{
				x = ix;
				y += 14;
			}

			wpt = word;

			char c = 0;
			
			while ((c = *wpt++) != 0) 
			{
				if (c == ' ') 
				{
					x += 4;
				}
				else 
				{
					index = AsciiTable[c];

					if (index != -1) 
					{
						OUT_FONTINFO *pFontInfo = &fontinfo[index];

						setSprt(font);

						setRGB0(font, gFontColour.r, gFontColour.g, gFontColour.b);
						setXY0(font, x, y + pFontInfo->offy);
						setUV0(font, pFontInfo->x, pFontInfo->y - 46);
						setWH(font, pFontInfo->width, pFontInfo->height);
						
						font->clut = fontclutid;

						addPrim(current->ot, font);
						font++;

						x += pFontInfo->width;
					}
				}
			}

			wordcount++;
		} while (*string != 0);
	}

	POLY_FT3* null = (POLY_FT3*)font;

	setPolyFT3(null);
#ifdef PSX
	setSemiTrans(null, 1);
#endif

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = fonttpage;

	addPrim(current->ot, null);
	null++;

	current->primptr = (char *)null;
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitButtonTextures()
 // line 713, offset 0x00074e54
	/* begin block 1 */
		// Start line: 715
		// Start offset: 0x00074E54
		// Variables:
	// 		int i; // $s0
	/* end block 1 */
	// End offset: 0x00074EB4
	// End Line: 719

	/* begin block 2 */
		// Start line: 2500
	/* end block 2 */
	// End Line: 2501

	/* begin block 3 */
		// Start line: 1426
	/* end block 3 */
	// End Line: 1427

	/* begin block 4 */
		// Start line: 2501
	/* end block 4 */
	// End Line: 2502

	/* begin block 5 */
		// Start line: 2503
	/* end block 5 */
	// End Line: 2504

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void InitButtonTextures(void)
{
	int i;
	i = 0;
	while (i < 11)
	{
		GetTextureDetails(button_names[i], &button_textures[i]);
		i++;
	}
}



// decompiled code
// original method signature: 
// int /*$ra*/ PrintScaledString(int y /*$s4*/, char *string /*$s1*/, int scale /*$s2*/)
 // line 726, offset 0x000745dc
	/* begin block 1 */
		// Start line: 727
		// Start offset: 0x000745DC
		// Variables:
	// 		struct FONT_DIGIT *pDigit; // $a2
	// 		struct POLY_FT4 *font; // $t0
	// 		int x; // $s0
	// 		int width; // $t3
	// 		int height; // $t6
	// 		int y0; // $t1
	// 		int x1; // $t5
	// 		int y1; // $v0
	// 		unsigned char vOff; // $t8
	// 		char c; // $a0
	/* end block 1 */
	// End offset: 0x00074858
	// End Line: 794

	/* begin block 2 */
		// Start line: 1580
	/* end block 2 */
	// End Line: 1581

	/* begin block 3 */
		// Start line: 1596
	/* end block 3 */
	// End Line: 1597

//
// PrintScaledString - prints digits with specified scale
//
// [D] [T]
int PrintScaledString(int y, char *string, int scale)
{
	int y0;
	int y1;
	int x;
	int x1;
	int width;
	char c;
	POLY_FT4 *font;
	int height;
	unsigned char vOff;

	font = (POLY_FT4 *)current->primptr;

	if (gShowMap != 0)
		font = (POLY_FT4 *)SetFontTPage(font);

	width = StringWidth(string) * scale;
	x = (320 - (width / 16)) / 2;

	while (*string != 0)
	{
		c = *string - '0';

		if (*string == 0x20) // space
		{
			width = (scale / 4);
		}
		else if (c < 10)
		{
			FONT_DIGIT* pDigit = &fontDigit[c];

			vOff = 0;

			if (c < 6)
			{
				height = 28;
			}
			else
			{
				vOff = 28;
				height = 31;
			}

			y1 = (height / 2 * scale) / 16;
			width = (pDigit->width * scale) / 16;

			y0 = y - y1;
			y1 = y + y1;
			x1 = x + width;

			setPolyFT4(font);

			setRGB0(font, gFontColour.r, gFontColour.g, gFontColour.b);

			font->x0 = x;		// [A] no suitable macro in libgpu
			font->y0 = y0;
			font->x1 = x1;
			font->y1 = y0;
			font->x2 = x;
			font->y2 = y1;
			font->x3 = x1;
			font->y3 = y1;

			setUVWH(font, digit_texture.coords.u0 + pDigit->xOffset, digit_texture.coords.v0 + vOff, pDigit->width, height);

			font->clut = digit_texture.clutid;
			font->tpage = digit_texture.tpageid;

			addPrim(current->ot, font);
			font++;
		}

		x += width;
		string++;
	}

	current->primptr = (char*)font;

	return x;
}



// decompiled code
// original method signature: 
// char * /*$ra*/ GetNextWord(char *string /*$a0*/, char *word /*$a1*/)
 // line 800, offset 0x00074d54
	/* begin block 1 */
		// Start line: 801
		// Start offset: 0x00074D54
		// Variables:
	// 		char c; // $v1
	/* end block 1 */
	// End offset: 0x00074D94
	// End Line: 817

	/* begin block 2 */
		// Start line: 2336
	/* end block 2 */
	// End Line: 2337

	/* begin block 3 */
		// Start line: 2502
	/* end block 3 */
	// End Line: 2503

	/* begin block 4 */
		// Start line: 2505
	/* end block 4 */
	// End Line: 2506

// [D]
char * GetNextWord(char *string, char *word)
{
	char c = *string;

	while (c != 0)
	{
		string++;

		if ((*word++ = c) == ' ')
			break;

		c = *string;
	}

	// add null-terminator
	*word = '\0';

	return string;
}



// decompiled code
// original method signature: 
// void * /*$ra*/ DrawButton(unsigned char button /*$a0*/, void *prim /*$s1*/, int x /*$a2*/, int y /*$a3*/)
 // line 819, offset 0x00074858
	/* begin block 1 */
		// Start line: 820
		// Start offset: 0x00074858
		// Variables:
	// 		struct TEXTURE_DETAILS *btn; // $a1
	// 		struct POLY_FT3 *null; // $s0
	/* end block 1 */
	// End offset: 0x00074A10
	// End Line: 853

	/* begin block 2 */
		// Start line: 1807
	/* end block 2 */
	// End Line: 1808

	/* begin block 3 */
		// Start line: 1833
	/* end block 3 */
	// End Line: 1834

// [D]
void* DrawButton(unsigned char button, void *prim, int x, int y)
{
	TEXTURE_DETAILS *btn;
	SPRT* sprt;
	POLY_FT3* null;

	btn = &button_textures[button - 0x80];
	sprt = (SPRT*)prim;
	 
	setSprt(sprt);

	sprt->r0 = 128;
	sprt->g0 = 128;
	sprt->b0 = 128;
	sprt->x0 = x;
	sprt->y0 = y - 3;
	sprt->u0 = btn->coords.u0;
	sprt->v0 = btn->coords.v0;
	sprt->w = btn->coords.u1 - btn->coords.u0;
	sprt->h = btn->coords.v2 - btn->coords.v0;
	sprt->clut = btn->clutid;

	null = (POLY_FT3*)(sprt + 1);
	setPolyFT3(null);
	setSemiTrans(null, 1);

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = btn->tpageid;

	if (gShowMap == 0)
	{
		addPrim(current->ot, sprt);
		addPrim(current->ot, null);
	}
	else 
	{
		DrawPrim(null);
		DrawPrim(sprt);
	}

	return null+1;
}



// decompiled code
// original method signature: 
// void * /*$ra*/ SetFontTPage(void *prim /*$a0*/)
 // line 855, offset 0x00074d94
	/* begin block 1 */
		// Start line: 856
		// Start offset: 0x00074D94
		// Variables:
	// 		struct POLY_FT3 *null; // $s0
	/* end block 1 */
	// End offset: 0x00074E54
	// End Line: 871

	/* begin block 2 */
		// Start line: 2581
	/* end block 2 */
	// End Line: 2582

	/* begin block 3 */
		// Start line: 2620
	/* end block 3 */
	// End Line: 2621

// [D]
void* SetFontTPage(void *prim)
{
	POLY_FT3* null = (POLY_FT3*)prim;

	setPolyFT3(null);
#ifdef PSX
	setSemiTrans(null, 1);
#endif

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = fonttpage;

	if (gShowMap == 0) 
	{
		addPrim(current->ot, null);
	}
	else 
	{
		DrawPrim(prim);
	}

	return null+1;
}





