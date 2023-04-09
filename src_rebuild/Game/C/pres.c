#include "driver2.h"
#include "pres.h"
#include "system.h"
#include "texture.h"

extern int gShowMap;

#ifndef PSX

#include "PsyX/PsyX_render.h"
#include "../utils/targa.h"
#include "../utils/hqfont.h"

#define HIRES_FONTS

struct FONT_QUAD
{
	float x0, y0, s0, t0; // top-left
	float x1, y1, s1, t1; // bottom-right
};

TextureID gHiresFontTexture = 0;
TextureID gHiresDigitsTexture = 0;

OUT_FN2RANGE gHiresFontRanges[4];
OUT_FN2INFO gHiresFontCharData[4][224];
int gHiresFontRangeCount = 0;

void InitHiresFonts()
{
	char namebuffer[64];
	u_char* data;

	// init digits
	if(!gHiresDigitsTexture)
	{
		int width, height, bpp;

		sprintf(namebuffer, "%s%s", gDataFolder, "GFX\\HQ\\digits.tga");
		FS_FixPathSlashes(namebuffer);

		if (LoadTGAImage(namebuffer, &data, width, height, bpp))
		{
			if (bpp == 32)
			{
				gHiresDigitsTexture = GR_CreateRGBATexture(width, height, data);
			}
			free(data);
			data = NULL;
		}
	}

	// init font2
	if(!gHiresFontTexture)
	{
		gHiresFontRangeCount = 0;

		int width, height, bpp;
		int x, y;
		int size;
		FILE* fp;
		sprintf(namebuffer, "%s%s", gDataFolder, "GFX\\HQ\\font2.fn2");
		FS_FixPathSlashes(namebuffer);

		fp = fopen(namebuffer, "rb");
		if (fp) 
		{
			int i;

			// read fn2 step by step
			OUT_FN2HEADER fn2hdr;
			fread(&fn2hdr, sizeof(fn2hdr), 1, fp);

			gHiresFontRangeCount = fn2hdr.range_count;
			for (i = 0; i < fn2hdr.range_count; ++i)
			{
				fread(&gHiresFontRanges[i], sizeof(gHiresFontRanges[i]), 1, fp);
				fread(gHiresFontCharData[i], sizeof(OUT_FN2INFO), gHiresFontRanges[i].count, fp);
			}

			fclose(fp);
		}

		// load TGA file
		sprintf(namebuffer, "%s%s", gDataFolder, "GFX\\HQ\\font2.tga");
		FS_FixPathSlashes(namebuffer);

		if (LoadTGAImage(namebuffer, &data, width, height, bpp))
		{
			if (bpp == 32)
			{
				gHiresFontTexture = GR_CreateRGBATexture(HIRES_FONT_SIZE_W, HIRES_FONT_SIZE_H, data);
			}
			free(data);
		}
	}
}

void SetHiresFontTexture(int enabled)
{
	if (gHiresFontTexture == 0)
	{
		return;
	}

	DR_PSYX_TEX* tex = (DR_PSYX_TEX*)current->primptr;
	if (enabled)
		SetPsyXTexture(tex, gHiresFontTexture, 255, 255);
	else
		SetPsyXTexture(tex, 0, 0, 0);

	if (gShowMap == 0) 
	{
		addPrim(current->ot, tex);
		current->primptr += sizeof(DR_PSYX_TEX);
	}
	else
	{
		DrawPrim(tex);
	}
}

void SetHiresDigitsTexture(int enabled)
{
	if (gHiresDigitsTexture == 0)
	{
		return;
	}

	DR_PSYX_TEX* tex = (DR_PSYX_TEX*)current->primptr;
	if (enabled)
		SetPsyXTexture(tex, gHiresDigitsTexture, 96, 59);
	else
		SetPsyXTexture(tex, 0, 0, 0);

	addPrim(current->ot, tex);
	current->primptr += sizeof(DR_PSYX_TEX);
}

void GetHiresBakedQuad(int char_index, float* xpos, float* ypos, FONT_QUAD* q)
{
	float ipw = 1.0f / (float)HIRES_FONT_SIZE_W;
	float iph = 1.0f / (float)HIRES_FONT_SIZE_H;

	const OUT_FN2INFO* b = gHiresFontCharData[0] + char_index - gHiresFontRanges[0].start;

	float scale = 0.275f;

	float s_x = b->x1 - b->x0;
	float s_y = b->y1 - b->y0;

	q->x0 = *xpos + b->xoff * scale;
	q->y0 = *ypos + b->yoff * scale;
	q->x1 = (b->xoff2 - b->xoff) * scale;
	q->y1 = (b->yoff2 - b->yoff) * scale;

	q->s0 = b->x0 * 255.0f * ipw;
	q->t0 = b->y0 * 255.0f * iph;
	q->s1 = s_x * 255.0f * ipw;
	q->t1 = s_y * 255.0f * iph;

	q->y0 += 14.0f;

	*xpos += b->xadvance * scale;
}

int StrighWidthHires(char* string)
{
	u_char chr;
	float width;
	width = 0;

	while ((chr = *string++) != 0)
	{
		if (chr >= 128 && chr <= 138)
		{
			width += 24;
			continue;
		}

		chr = (chr >= 32 && chr < 128 || chr > 138) ? chr : '?';

		float fx, fy;
		fx = 0.0f;
		fy = 0.0f;
		FONT_QUAD q;
		GetHiresBakedQuad(chr, &fx, &fy, &q);
		width += fx;
	}
	return width;
}

extern CVECTOR gFontColour;
extern short fontclutid;
extern short fonttpage;

int PrintStringHires(char* string, int x, int y)
{
	u_char chr;
	float width;
	u_int index;
	int showMap;

	showMap = gShowMap;
	width = x;

	SetHiresFontTexture(showMap);

	while ((chr = *string++) != 0)
	{
		if (chr >= 128 && chr <= 138)
		{
			if(showMap)
				SetHiresFontTexture(0);

			DrawButton(chr, current->primptr, width, y);

			if (showMap)
				SetHiresFontTexture(1);

			width += 24;
			x += 24;
			continue;
		}

		chr = (chr >= 32 && chr < 128 || chr > 138) ? chr : '?';

		POLY_FT4* fontFT4;
		POLY_FT4* shadowFT4;
		float fx, fy;
		fx = width;
		fy = y;
		FONT_QUAD q;
		GetHiresBakedQuad(chr, &fx, &fy, &q);

		fontFT4 = (POLY_FT4*)current->primptr;

		setPolyFT4(fontFT4);
		setSemiTrans(fontFT4, 1);

		setUVWH(fontFT4, q.s0, q.t0, q.s1, q.t1);

		fontFT4->clut = fontclutid;
		fontFT4->tpage = fonttpage;

		if (showMap == 0)
		{
			setRGB0(fontFT4, gFontColour.r, gFontColour.g, gFontColour.b);
			setXYWH(fontFT4, q.x0, q.y0, q.x1, q.y1);

			addPrim(current->ot, fontFT4);
			current->primptr += sizeof(POLY_FT4);

			shadowFT4 = (POLY_FT4*)current->primptr;

			// add shadow poly
			memcpy(shadowFT4, fontFT4, sizeof(POLY_FT4));
			setRGB0(shadowFT4, 0, 0, 0);
			setXYWH(shadowFT4, q.x0 + 0.5f, q.y0 + 0.5f, q.x1, q.y1);

			addPrim(current->ot, shadowFT4);
			current->primptr += sizeof(POLY_FT4);
		}
		else
		{
			setRGB0(fontFT4, 0, 0, 0);
			setXYWH(fontFT4, q.x0 + 0.5f, q.y0 + 0.5f, q.x1, q.y1);
			DrawPrim(fontFT4);

			setRGB0(fontFT4, gFontColour.r, gFontColour.g, gFontColour.b);
			setXYWH(fontFT4, q.x0, q.y0, q.x1, q.y1);
			DrawPrim(fontFT4);
		}

		width += fx - width;
	}

	SetHiresFontTexture(showMap == 0);
	if(showMap)
		DrawSync(0);

	return width;
}

void PrintStringBoxedHires(char* string, int ix, int iy)
{
	char word[32];
	int x, y;
	int wordcount;

	wordcount = 1;

	x = ix;
	y = iy;

	while (*string)
	{
		string = GetNextWord(string, word);

		if (x + StringWidth(word) > 308 && (wordcount != 1 || *string != 0))
		{
			x = ix;
			y += 14;
		}

		x = PrintStringHires(word, x, y);

		wordcount++;
	}
}

#endif

extern TEXTURE_DETAILS digit_texture;

struct FONT_DIGIT
{
	char xOffset;
	char width;
};

FONT_DIGIT fontDigit[] = {
	{ 2, 14 },
	{ 17, 14},
	{ 32, 16},
	{ 49, 15},
	{ 65, 14 },
	{ 80, 14 },
	{ 4, 16 },
	{ 21, 14 },
	{ 36, 15 },
	{ 52, 17 },
	{ 70, 11 },
	{ 82, 7 },
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

// [D] [T]
void SetTextColour(u_char Red, u_char Green, u_char Blue)
{
	gFontColour.r = Red;
	gFontColour.g = Green;
	gFontColour.b = Blue;
}

// [D] [T]
int StringWidth(char *pString)
{
#ifdef HIRES_FONTS
	if (gHiresFontTexture)
	{
		return StrighWidthHires(pString);
	}
#endif

	u_char let;
	int w;

	w = 0;
	
	while (true)
	{
		let = *pString++;
		if (!let)
			break;
	
		if (let == 32)
			w += 4;
		else if ((let + 128 & 0xff) < 11) 
			w += 24;
		else if (AsciiTable[let] != -1) 
			w += fontinfo[AsciiTable[let]].width;
	}

	return w;
}

// [D] [T]
int OutputString(char *pString, int formatting, int x, int y, int xw, int r, int g, int b)
{
	int xpos;

	SetTextColour(r, g, b);

	if (formatting & 1) 
	{
		PrintString(pString, x, y);
	}
	else if (formatting & 2)
	{
		xpos = (xw - StringWidth(pString)) / 2;
		PrintString(pString, x + xpos, y);
	}
	else if (formatting & 4) 
	{
		PrintString(pString, x - StringWidth(pString), y);
	}

	return x;
}

// [D] [T]
int PrintStringRightAligned(char *pString, int x, int y)
{
	return PrintString(pString, x - StringWidth(pString), y);
}

// [D] [T]
void PrintStringCentred(char *pString, short y)
{
	PrintString(pString, (320 - StringWidth(pString)) / 2, y);
}

// [D] [T]
void LoadFont(char *buffer)
{
	int i;
	ushort *clut, *pclut;
	int nchars;
	char *file;
	RECT16 dest;

	fontclutpos.x = 976;
	fontclutpos.y = 256;
	fontclutpos.w = 16;
	fontclutpos.h = 1;
	
	if (buffer != NULL)
		file = buffer;
	else
		file = (char*)_primTab2;	// 0x11b400;		// [A] FIXME: this font address might be used somewhere else

	Loadfile("GFX\\FONT2.FNT",file);

	nchars = *(int *)file;
	file += sizeof(int);

	// copy character info
	memcpy((u_char*)fontinfo, (u_char*)file,nchars * sizeof(OUT_FONTINFO));

	file += nchars * sizeof(OUT_FONTINFO);
	memcpy((u_char*)AsciiTable, (u_char*)file, 256);

	file += 256;

	fontclutid = GetClut(fontclutpos.x,fontclutpos.y);

	clut = (ushort*)file;
	pclut = clut;

	for (i = 0; i < 16; i++)
		*pclut++ &= ~0x8000;

	clut[1] |= 0x8000;
	clut[2] |= 0x8000;

	setRECT(&dest, 960, 466, 64, 46);

	fonttpage = GetTPage(0,0, dest.x, dest.y);

	LoadImage(&fontclutpos, (u_long *)clut);	// upload clut
	LoadImage(&dest, (u_long *)(file + 32));	// upload font image

#ifdef HIRES_FONTS
	InitHiresFonts();
#endif

	DrawSync(0);
}

// [D] [T]
void StoreClut2(u_long *pDest, int x, int y)
{
	RECT16 rect;

	rect.x = x;
	rect.y = y;
	rect.w = 16;
	rect.h = 1;

	StoreImage2(&rect, pDest);
}

// [D] [T]
void SetCLUT16Flags(ushort clutID, ushort mask, char transparent)
{
	ushort *pCurrent;
	int ctr;
	int x, y;
	ushort buffer[16];

	x = (clutID & 63) * 16;
	y = (clutID >> 6);

	StoreClut2((ulong *)buffer, x, y);

	pCurrent = buffer;
	ctr = 1;

	while (pCurrent < &buffer[16]) 
	{
		if ((mask >> ctr) & 1 != 0) 
			*pCurrent |= 0x8000;
		else
			*pCurrent &= ~0x8000;

		buffer[transparent] = 0;
	
		pCurrent++;
		ctr++;
	}

	LoadClut2((u_long*)buffer, x,y);
}

// [D] [T]
int PrintString(char *string, int x, int y)
{
	u_char chr;
	int width;
	u_int index;
	SPRT *font;

	int showMap = gShowMap;

	if (current == NULL)
		return -1;

#ifdef HIRES_FONTS
	if (gHiresFontTexture)
	{
		return PrintStringHires(string, x, y);
	}
#endif

	font = (SPRT *)current->primptr;
	
	if (showMap != 0)
	{
		font = (SPRT*)SetFontTPage(font);
	}

	width = x;

	while ((chr = *string++) != 0)
	{
		if (chr == 32)
		{
			width += 4;
			continue;
		}

		if (chr < 32 || chr > 138 || chr < 128) 
		{
			if (AsciiTable[chr] == -1)
				index = AsciiTable[63];	// place a question mark
			else
				index = AsciiTable[chr];

			setSprt(font);
			setSemiTrans(font, 1);

			font->r0 = gFontColour.r;
			font->g0 = gFontColour.g;
			font->b0 = gFontColour.b;
			
			font->x0 = width;
			font->y0 = fontinfo[index].offy + y;
			font->u0 = fontinfo[index].x;
			font->v0 = fontinfo[index].y - 46;
			
			font->w = fontinfo[index].width;
			font->h = fontinfo[index].height;
			
			font->clut = fontclutid;

			if (showMap == 0)
			{
				addPrim(current->ot, font);
			}
			else 
			{
				DrawPrim(font);
			}

			font++;
			width += fontinfo[index].width;
		}
		else
		{
			if (showMap == 0)
				font = (SPRT *)SetFontTPage(font);

			font = (SPRT *)DrawButton(chr, font, width, y);
			width += 24;

			if (showMap != 0)
				font = (SPRT *)SetFontTPage(font);
		}
	}

	if (showMap == 0)
	{
		current->primptr = (char*)SetFontTPage(font);
	}
	else
		DrawSync(0);

	return width;
}

// [D] [T]
short PrintDigit(int x, int y, char *string)
{
	FONT_DIGIT* pDigit;
	char chr;
	short width;
	int index;
	SPRT *font;
	int fixedWidth;
	char vOff, h;

#ifdef HIRES_FONTS
	SetHiresDigitsTexture(0);
#endif

	width = x;
	font = (SPRT *)current->primptr;

	while ((chr = *string++) != 0)
	{
		if (chr == 58)
			index = 11;
		else if (chr == 47) 
			index = 10;
		else 
			index = chr - 48 & 0xff;

		pDigit = &fontDigit[index];
		
		if (chr == 58) 
			fixedWidth = 8;
		else
			fixedWidth = 16;

		if (index < 6) 
		{
			vOff = 0;
			h = 28;
		}
		else 
		{
			vOff = 28;
			h = 31;
		}

		setSprt(font);
		setSemiTrans(font, 1);

		font->r0 = gFontColour.r;
		font->g0 = gFontColour.g;
		font->b0 = gFontColour.b;

		font->x0 = width + (fixedWidth - pDigit->width) / 2;
		font->y0 = y;
		
#ifdef HIRES_FONTS
		if (gHiresDigitsTexture) 
		{
			font->u0 = pDigit->xOffset;
			font->v0 = vOff;
		}
		else
#endif
		{
			font->u0 = digit_texture.coords.u0 + pDigit->xOffset;
			font->v0 = digit_texture.coords.v0 + vOff;
		}

		font->w = pDigit->width;
		font->h = h;

		font->clut = digit_texture.clutid;

		addPrim(current->ot, font);
		
		width += fixedWidth;

		font++;
	}

	current->primptr = (char*)font;

	POLY_FT3* null = (POLY_FT3*)current->primptr;
	setPolyFT3(null);
	setSemiTrans(null, 1);

	null->x0 = -1;
	null->y0 = -1;
	null->x1 = -1;
	null->y1 = -1;
	null->x2 = -1;
	null->y2 = -1;
	null->tpage = digit_texture.tpageid;
	
	addPrim(current->ot, null);
	current->primptr += sizeof(POLY_FT3);

#ifdef HIRES_FONTS
	SetHiresDigitsTexture(1);
#endif

	return width;
}

// [D] [T]
int PrintStringFeature(char *string, int x, int y, int w, int h, int transparent)
{
	return PrintString(string, x, y);
}

// [D] [T]
void PrintStringBoxed(char *string, int ix, int iy)
{
	SPRT *font;
	char word[32];
	char *wpt;
	int x;
	int y;
	int index;
	int wordcount;

#ifdef HIRES_FONTS
	if (gHiresFontTexture)
	{
		PrintStringBoxedHires(string, ix, iy);
		return;
	}
#endif

	font = (SPRT *)current->primptr;

	wordcount = 1;
	
	x = ix;
	y = iy;

	while (*string)
	{
		string = GetNextWord(string, word);

		if (x + StringWidth(word) > 308 && (wordcount != 1 || *string != 0))
		{
			x = ix;
			y += 14;
		}

		wpt = word;

		u_char c = 0;
		
		while ((c = *wpt++) != 0) 
		{
			if (c == ' ') 
			{
				x += 4;
				continue;
			}

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

		wordcount++;
	}

	POLY_FT3* null = (POLY_FT3*)font;

	setPolyFT3(null);
	setSemiTrans(null, 1);

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

// [D] [T]
void InitButtonTextures(void)
{
	int i;

	for (i = 0; i < 11; i++)
	{
		GetTextureDetails(button_names[i], &button_textures[i]);
	}
}

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
	u_char vOff;

#ifdef HIRES_FONTS
	SetHiresDigitsTexture(0);
#endif

	font = (POLY_FT4 *)current->primptr;

	if (gShowMap != 0)
	{
		font = (POLY_FT4*)SetFontTPage(font);
	}

	width = StringWidth(string) * scale;
	x = (320 - (width / 16)) / 2;

	while (*string != 0)
	{
		c = *string - '0';

		if (*string == 32) // space
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
			setSemiTrans(font, 1);
			setRGB0(font, gFontColour.r, gFontColour.g, gFontColour.b);

			font->x0 = x;		// [A] no suitable macro in libgpu
			font->y0 = y0;
			font->x1 = x1;
			font->y1 = y0;
			font->x2 = x;
			font->y2 = y1;
			font->x3 = x1;
			font->y3 = y1;

#ifdef HIRES_FONTS
			if (gHiresDigitsTexture)
			{
				setUVWH(font, pDigit->xOffset, vOff, pDigit->width, height);
			}
			else
#endif
			{
				setUVWH(font, digit_texture.coords.u0 + pDigit->xOffset, digit_texture.coords.v0 + vOff, pDigit->width, height);
			}

			font->clut = digit_texture.clutid;
			font->tpage = digit_texture.tpageid;

			addPrim(current->ot, font);
			font++;
		}

		x += width;
		string++;
	}

	current->primptr = (char*)font;

#ifdef HIRES_FONTS
	SetHiresDigitsTexture(1);
#endif

	return x;
}

// [D] [T]
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

// [D] [T]
void* DrawButton(u_char button, void *prim, int x, int y)
{
	TEXTURE_DETAILS *btn;
	SPRT* sprt;
	POLY_FT3* null;

	btn = &button_textures[button - 128];
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

// [D] [T]
void* SetFontTPage(void *prim)
{
	POLY_FT3* null = (POLY_FT3*)prim;

	setPolyFT3(null);
	setSemiTrans(null, 1);

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





