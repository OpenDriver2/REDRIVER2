#include "driver2.h"
#include "pres.h"
#include "system.h"
#include "texture.h"

#include <STRINGS.H>

extern TEXTURE_DETAILS digit_texture;

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
void SetTextColour(unsigned char Red, unsigned char Green, unsigned char Blue)
{
	gFontColour.r = Red;
	gFontColour.g = Green;
	gFontColour.b = Blue;
}

// [D] [T]
int StringWidth(char *pString)
{
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
		else if (AsciiTable[let] != 0xff) 
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

// [D] [T
void PrintStringCentred(char *pString, short y)
{
	PrintString(pString, (320 - StringWidth(pString)) / 2, y);
}

// [D] [T]
void LoadFont(char *buffer)
{
	int i;
	ushort *clut;
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
		file = _frontend_buffer;	// 0x11b400;		// [A] FIXME: this font address might be used somewhere else

	Loadfile("GFX\\FONT2.FNT",file);
	nchars = *(int *)file;

	// copy character info
	memcpy((u_char*)fontinfo,file + 4,nchars * sizeof(OUT_FONTINFO));

	file += sizeof(int) + nchars * 8;
	memcpy((u_char*)AsciiTable, file, 256);

	fontclutid = GetClut(fontclutpos.x,fontclutpos.y);

	i = 0;
	clut = (ushort*)(file + 0x100);
	do {
		*clut++ &= 0x7fff;
		i++;
	} while(i < 16);

	clut[1] |= 0x8000;
	clut[2] |= 0x8000;

	dest.x = 960;
	dest.y = 466;
	dest.w = 64;
	dest.h = 46;

	fonttpage = GetTPage(0,0,960,466);

	LoadImage(&fontclutpos, (u_long *)(file + 0x100));
	LoadImage(&dest, (u_long *)(file + 0x120));

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

	x = (clutID & 0x3f) << 4;
	y = (clutID >> 6);

	StoreClut2((ulong *)buffer,x,y);

	pCurrent = buffer;
	ctr = 1;

	while (pCurrent < &buffer[16]) 
	{
		if (mask >> (ctr & 1U) == 0) 
			*pCurrent &= 0x7fff;
		else
			*pCurrent |= 0x8000;

		buffer[transparent] = 0;
	
		pCurrent++;
		ctr++;
	}

	LoadClut2((u_long*)buffer, x,y);
}

// MAP.C ????
extern int gShowMap;

// [D] [T]
int PrintString(char *string, int x, int y)
{
	u_char chr;
	int width;
	uint index;
	SPRT *font;

	int showMap = gShowMap;

	if (current == NULL)
		return -1;

	font = (SPRT *)current->primptr;
	
	if (showMap != 0)
		font = (SPRT *)SetFontTPage(font);

	chr = *string++;
	width = x;

	while (chr != 0) 
	{
		if (chr == 32)
		{
			width += 4;
		}
		else if (chr < 32 || chr > 138 || chr < 128) 
		{
			if (AsciiTable[chr] == 0xff)
				index = AsciiTable[63];
			else
				index = AsciiTable[chr];

			chr = fontinfo[index].width;

			setSprt(font);
#ifdef PSX
			setSemiTrans(font, 1);
#endif

			font->r0 = gFontColour.r;
			font->g0 = gFontColour.g;
			font->b0 = gFontColour.b;
			
			font->x0 = width;
			font->y0 = fontinfo[index].offy + y;
			font->u0 = fontinfo[index].x;
			font->v0 = fontinfo[index].y - 46;
			
			font->w = chr;
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
			width += chr;
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

		chr = *string++;
	}

	if (showMap == 0)
		current->primptr = (char *)SetFontTPage(font);
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

	width = x;
	chr = *string++;

	font = (SPRT *)current->primptr;

	while (chr != 0) 
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
#ifdef PSX
		setSemiTrans(font, 1);
#endif

		font->r0 = gFontColour.r;
		font->g0 = gFontColour.g;
		font->b0 = gFontColour.b;

		font->x0 = width + (fixedWidth - pDigit->width) / 2;
		font->y0 = y;
		
		font->u0 = digit_texture.coords.u0 + pDigit->xOffset;
		font->v0 = vOff + digit_texture.coords.v0;

		font->w = pDigit->width;
		font->h = h;

		font->clut = digit_texture.clutid;

		addPrim(current->ot, font);
		
		width += fixedWidth;

		font++;
	
		chr = *string++;
	}

	current->primptr = (char*)font;

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

// [D] [T]
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

// [D] [T]
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





