#include "DRIVER2.H"
#include "TEXTURE.H"
#include "SYSTEM.H"
#include "OVERMAP.H"
#include "MISSION.H"
#include "DRAW.H"

#include <string.h>

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

	{ -1, -1 }
};

char specTpages[4][12] = {
	{ 54, 55, 66, 67, 56, 57, 68, 69, 61, 64, 61, 64 },
	{ 38, 39, 38, 39, 42, 43, 44, 45, 48, 49, 48, 49 },
	{ 18, 19, 65, 66, 67, 68, 11, 12, 63, 64, 63, 64 },
	{ 66, 67, 77, 78, 73, 74, 75, 76, 69, 70, 71, 72 }
};

char carTpages[4][8] = {
	{ 01, 65, 62, 50, 63, 58, 54, 55 },
	{ 10, 35, 20, 37, 51, 36, 38, 39 },
	{ 41, 54, 62, 17, 32, 59, 18, 00 },
	{ 55, 57, 68, 58, 60, 59, 66, 67 }
};

char *palette_lump;

int texture_is_icon = 0;
char* texturename_buffer = NULL;
int NoTextureMemory = 0;

unsigned short texture_pages[128];
unsigned short texture_cluts[128][32];
unsigned char tpageloaded[128];

int MaxSpecCluts;
int slotsused;

RECT16 clutpos;
RECT16 fontclutpos;
RECT16 mapclutpos;
DVECTOR slot_clutpos[19];
DVECTOR slot_tpagepos[19];
unsigned char tpageslots[19];

TP *tpage_position = NULL;
TEXINF* tpage_ids[128] = { 0 };
int texamount = 0;
int tpage_amount = 0;
int tpage_texamts[128];

int nspecpages = 0;
int nperms = 0;
XYPAIR *speclist = NULL;
XYPAIR *permlist = NULL;

RECT16 tpage; // stupid naming, absolute ass

short specialSlot;

// decompiled code
// original method signature: 
// void /*$ra*/ IncrementClutNum(struct RECT *clut /*$a0*/)
 // line 116, offset 0x00080ddc
	/* begin block 1 */
		// Start line: 1163
	/* end block 1 */
	// End Line: 1164

	/* begin block 2 */
		// Start line: 232
	/* end block 2 */
	// End Line: 233

	/* begin block 3 */
		// Start line: 1164
	/* end block 3 */
	// End Line: 1165

// [D]
void IncrementClutNum(RECT16 *clut)
{
	clut->x += 16;

	if (clut->x == 1024) {
		clut->x = 960;
		clut->y += 1;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ IncrementTPageNum(struct RECT *tpage /*$t0*/)
 // line 126, offset 0x00080528
	/* begin block 1 */
		// Start line: 127
		// Start offset: 0x00080528
		// Variables:
	// 		int i; // $a3
	/* end block 1 */
	// End offset: 0x000805EC
	// End Line: 153

	/* begin block 2 */
		// Start line: 252
	/* end block 2 */
	// End Line: 253

	/* begin block 3 */
		// Start line: 255
	/* end block 3 */
	// End Line: 256

// [D] [T]
void IncrementTPageNum(RECT16 *tpage)
{
	int i = 0;

	while (++i)
	{
		// proper tpage position?
		if ((tpage->x == tpagepos[i - 1].x) && (tpage->y == tpagepos[i - 1].y))
		{
			if (tpagepos[i].x == -1)
			{
				// out of tpages
				NoTextureMemory = 100;
			}
			else
			{
				// increment the tpage
				tpage->x = tpagepos[i].x;
				tpage->y = tpagepos[i].y;
			}

			// bust 'outta here, real fly
			break;
		}
		else
		{
			// last tpage?
			if (tpagepos[i].x == -1)
				break;
		}
	}
}


// decompiled code
// original method signature: 
// int /*$ra*/ LoadTPageAndCluts(struct RECT *tpage /*$s5*/, struct RECT *cluts /*$s2*/, int tpage2send /*$s6*/, char *tpageaddress /*$s0*/)
 // line 155, offset 0x00080e14
	/* begin block 1 */
		// Start line: 156
		// Start offset: 0x00080E14
		// Variables:
	// 		int i; // $s3
	// 		int npalettes; // $s4
	// 		struct RECT temptpage; // stack offset -40
	/* end block 1 */
	// End offset: 0x00080F3C
	// End Line: 185

	/* begin block 2 */
		// Start line: 1243
	/* end block 2 */
	// End Line: 1244

// [D] [T]
// Originally ASM function
char * unpackTexture(char *dest, char *src)
{
	char *ptr = dest + 0x7fff;

	do {
		char pix = *src++;
		
		if ((pix & 0x80) != 0)
		{
			char p = *src++;

			do (*ptr-- = p);
			while (pix++ <= 0);
		}
		else
		{
			do (*ptr-- = *src++);
			while (pix-- != 0);
		}
	} while (ptr >= dest);

	return src;
}

// [D] [A]
int LoadTPageAndCluts(RECT16 *tpage, RECT16 *cluts, int tpage2send, char *tpageaddress)
{
	int npalettes = *(int *)tpageaddress;
	tpageaddress += 4;

	for (int i = 0; i < npalettes; i++)
	{
		LoadImage(cluts, (u_long *)tpageaddress);
		tpageaddress += 32;

		texture_cluts[tpage2send][i] = GetClut(cluts->x, cluts->y);
		IncrementClutNum(cluts);
	}

	RECT16 temptpage;

	temptpage.x = tpage->x;
	temptpage.y = tpage->y;
	temptpage.w = tpage->w;
	temptpage.h = 0x100;

	unpackTexture(_other_buffer, tpageaddress);
	LoadImage(&temptpage, (u_long *)_other_buffer);

	texture_pages[tpage2send] = GetTPage(0, 0, tpage->x, tpage->y);
	IncrementTPageNum(tpage);

	return 1;
}



// decompiled code
// original method signature: 
// int /*$ra*/ Find_TexID(struct MODEL *model /*$t0*/, int t_id /*$a1*/)
 // line 191, offset 0x000805ec
	/* begin block 1 */
		// Start line: 192
		// Start offset: 0x000805EC
		// Variables:
	// 		char *polylist; // $a2
	// 		int i; // $a3

		/* begin block 1.1 */
			// Start line: 203
			// Start offset: 0x00080638
		/* end block 1.1 */
		// End offset: 0x00080650
		// End Line: 206

		/* begin block 1.2 */
			// Start line: 209
			// Start offset: 0x00080650
		/* end block 1.2 */
		// End offset: 0x00080650
		// End Line: 212

		/* begin block 1.3 */
			// Start line: 215
			// Start offset: 0x00080650
		/* end block 1.3 */
		// End offset: 0x00080650
		// End Line: 218

		/* begin block 1.4 */
			// Start line: 222
			// Start offset: 0x00080650
		/* end block 1.4 */
		// End offset: 0x00080650
		// End Line: 225

		/* begin block 1.5 */
			// Start line: 229
			// Start offset: 0x00080650
		/* end block 1.5 */
		// End offset: 0x00080650
		// End Line: 232

		/* begin block 1.6 */
			// Start line: 235
			// Start offset: 0x00080650
		/* end block 1.6 */
		// End offset: 0x00080650
		// End Line: 238

		/* begin block 1.7 */
			// Start line: 241
			// Start offset: 0x00080650
		/* end block 1.7 */
		// End offset: 0x00080650
		// End Line: 244

		/* begin block 1.8 */
			// Start line: 247
			// Start offset: 0x00080650
		/* end block 1.8 */
		// End offset: 0x00080650
		// End Line: 250
	/* end block 1 */
	// End offset: 0x00080688
	// End Line: 258

	/* begin block 2 */
		// Start line: 356
	/* end block 2 */
	// End Line: 357

	/* begin block 3 */
		// Start line: 395
	/* end block 3 */
	// End Line: 396

int Find_TexID(MODEL *model, int t_id)
{
	char *polylist = (char *)model->poly_block;

	for (int i = 0; i < model->num_polys; i++)
	{
		switch (*polylist & 0x1F) {
		case 4:
		case 5:
		case 6:
		case 7:
		case 20:
		case 21:
		case 22:
		case 23:
			if (polylist[2] == t_id)
				return 1;
		}

		polylist += PolySizes[*polylist];
	}
	
	return 0;
}



// decompiled code
// original method signature: 
// struct TEXINF * /*$ra*/ GetTEXINFName(char *name /*$fp*/, int *tpagenum /*stack 4*/, int *texturenum /*stack 8*/)
 // line 261, offset 0x00080f3c
	/* begin block 1 */
		// Start line: 262
		// Start offset: 0x00080F3C
		// Variables:
	// 		int i; // $s4
	// 		int j; // $s1
	// 		int texamt; // $s2
	// 		struct TEXINF *texinf; // $s3
	// 		char *nametable; // $s6
	/* end block 1 */
	// End offset: 0x00081038
	// End Line: 287

	/* begin block 2 */
		// Start line: 1407
	/* end block 2 */
	// End Line: 1408

	/* begin block 3 */
		// Start line: 1484
	/* end block 3 */
	// End Line: 1485

	/* begin block 4 */
		// Start line: 1490
	/* end block 4 */
	// End Line: 1491

// [D] [T]
TEXINF * GetTEXINFName(char *name, int *tpagenum, int *texturenum)
{
	char *nametable = texturename_buffer;

	for (int i = 0; i < tpage_amount; i++)
	{
		int texamt = tpage_texamts[i];
		TEXINF *texinf = tpage_ids[i];

		for (int j = 0; j < texamt; j++)
		{
			if (!strcmp(nametable + texinf->nameoffset, name))
			{
				*tpagenum = i;
				*texturenum = j;

				return texinf;
			}

			texinf++;
		}
	}

	return NULL;
}



// decompiled code
// original method signature: 
// struct TEXINF * /*$ra*/ GetTextureInfoName(char *name /*$a0*/, struct TPAN *result /*$s0*/)
 // line 290, offset 0x00080da0
	/* begin block 1 */
		// Start line: 291
		// Start offset: 0x00080DA0
		// Variables:
	// 		int tpagenum; // stack offset -16
	// 		int texturenum; // stack offset -12
	/* end block 1 */
	// End offset: 0x00080DDC
	// End Line: 300

	/* begin block 2 */
		// Start line: 580
	/* end block 2 */
	// End Line: 581

// [D]
TEXINF * GetTextureInfoName(char *name, TPAN *result)
{
	TEXINF *tex;
	int tpagenum;
	int texturenum;

	tex = GetTEXINFName(name, &tpagenum, &texturenum);

	result->texture_page = tpagenum;
	result->texture_number = texturenum;

	return tex;
}



// decompiled code
// original method signature: 
// void /*$ra*/ update_slotinfo(int tpage /*$a0*/, int slot /*$a1*/, struct RECT *pos /*$a2*/)
 // line 334, offset 0x00081038
	/* begin block 1 */
		// Start line: 1606
	/* end block 1 */
	// End Line: 1607

	/* begin block 2 */
		// Start line: 1654
	/* end block 2 */
	// End Line: 1655

	/* begin block 3 */
		// Start line: 1655
	/* end block 3 */
	// End Line: 1656

// [D]
void update_slotinfo(int tpage, int slot, RECT16 *pos)
{
	tpageslots[slot] = tpage;
	tpageloaded[tpage] = slot;
	slot_tpagepos[slot].vx = pos->x;
	slot_tpagepos[slot].vy = pos->y;
}



// decompiled code
// original method signature: 
// void /*$ra*/ ProcessTextureInfo(char *lump_ptr /*$a1*/)
 // line 347, offset 0x00081080
	/* begin block 1 */
		// Start line: 348
		// Start offset: 0x00081080
		// Variables:
	// 		int i; // $a0
	/* end block 1 */
	// End offset: 0x00081118
	// End Line: 375

	/* begin block 2 */
		// Start line: 1686
	/* end block 2 */
	// End Line: 1687

// [D]
void ProcessTextureInfo(char *lump_ptr)
{
	tpage_amount =  *(int *)lump_ptr;
	texamount = *(int *)(lump_ptr + 4);
	tpage_position = (TP *)(lump_ptr + 8);

	char *ptr = (char *)&tpage_position[tpage_amount + 1];

	if (tpage_amount > 0) {
		for (int i = 0; i < tpage_amount; i++)
		{
			texamount = *(int *)ptr;
			ptr += 4;

			tpage_ids[i] = (TEXINF *)ptr;
			ptr += (texamount * sizeof(TEXINF));

			tpage_texamts[i] = texamount;
		}
	}

	nperms = *(int *)ptr;
	permlist = (XYPAIR *)(ptr + 4);

	ptr = (char *)&permlist[16];

	nspecpages = *(int *)ptr;
	speclist = (XYPAIR *)(ptr + 4);
}



// decompiled code
// original method signature: 
// void /*$ra*/ LoadPermanentTPages(int *sector /*$fp*/)
 // line 378, offset 0x00080688
	/* begin block 1 */
		// Start line: 379
		// Start offset: 0x00080688
		// Variables:
	// 		int tloop; // $s1
	// 		int i; // $s1
	// 		int tset; // $s0
	// 		int nsectors; // $s3
	// 		char *tpagebuffer; // $s2

		/* begin block 1.1 */
			// Start line: 445
			// Start offset: 0x000808DC
			// Variables:
		// 		int specmodel; // $a1
		// 		int page1; // $s6
		// 		int page2; // $s5

			/* begin block 1.1.1 */
				// Start line: 465
				// Start offset: 0x00080984
				// Variables:
			// 		int temp; // $s4
			// 		int clutsLoaded; // $s7
			/* end block 1.1.1 */
			// End offset: 0x00080AD8
			// End Line: 504
		/* end block 1.1 */
		// End offset: 0x00080AD8
		// End Line: 505
	/* end block 1 */
	// End offset: 0x00080BB0
	// End Line: 575

	/* begin block 2 */
		// Start line: 762
	/* end block 2 */
	// End Line: 763

	/* begin block 3 */
		// Start line: 883
	/* end block 3 */
	// End Line: 884


#ifndef PSX
extern char g_CurrentLevelFileName[64];
#endif // !PSX

// [D]
void LoadPermanentTPages(int *sector)
{
	int nsectors;
	char *tpagebuffer;

	// init tpage and cluts
	MaxSpecCluts = 0;

	for (int tloop = 0; tloop < 128; tloop++)
		texture_pages[tloop] = GetTPage(0, 0, 960, 0);

	for (int tloop = 0; tloop < 128; tloop++)
	{
		for (int tset = 0; tset < 32; tset++)
			texture_cluts[tloop][tset] = GetClut(960, 16);
	}

	slotsused = 0;
	memset(tpageloaded, 0, sizeof(tpageloaded));

	clutpos.x = 960;
	clutpos.y = 256;
	clutpos.w = 16;
	clutpos.h = 1;

	mapclutpos.x = 960;
	mapclutpos.y = 256;
	mapclutpos.w = 16;
	mapclutpos.h = 1;

	tpage.x = tpagepos[0].x;
	tpage.y = tpagepos[0].y;
	tpage.w = 64;
	tpage.h = 256;

	IncrementClutNum(&clutpos);
	fontclutpos = clutpos;
	
	IncrementClutNum(&clutpos);
	ProcessPalletLump(palette_lump, 0);

	load_civ_palettes(&clutpos);

	tpagebuffer = mallocptr;
	nsectors = 0;

	for (int i = 0; i < nperms; i++)
		nsectors += (permlist[i].y + 2047) / CDSECTOR_SIZE;

#ifdef PSX
	loadsectors(tpagebuffer, *sector, nsectors_00);
#else
	loadsectorsPC(g_CurrentLevelFileName, tpagebuffer, *sector, nsectors);
#endif // PSX

	*sector += nsectors;

	for (int i = 0; i < nperms; i++)
	{
		int tp = permlist[i].x;

		update_slotinfo(tp, slotsused, &tpage);

		LoadTPageAndCluts(&tpage, &clutpos, tp, tpagebuffer);
		slotsused++;

		tpagebuffer += (permlist[i].y + 2047) & -CDSECTOR_SIZE;
	}
	
	tpagebuffer = mallocptr;

	slot_clutpos[slotsused].vx = clutpos.x;
	slot_clutpos[slotsused].vy = clutpos.y;

	int specmodel = (MissionHeader->residentModels[4] - 8) * 2;
	specialSlot = (short)slotsused;

	int page1 = specTpages[GameLevel][specmodel];
	int page2 = specTpages[GameLevel][specmodel + 1];

	carTpages[GameLevel][6] = page1;
	carTpages[GameLevel][7] = page2;

	if (nspecpages != 0)
	{
		int temp = 0;
		int clutsloaded = 0;

		nsectors = 0;

		for (int i = 0; i < nspecpages; i++)
			nsectors += (speclist[i].y + 2047) / CDSECTOR_SIZE;

#ifdef PSX
		loadsectors(tpagebuffer, *sector, nsectors);
#else
		loadsectorsPC(g_CurrentLevelFileName, tpagebuffer, *sector, nsectors);
#endif // PSX


		*sector += nsectors;
		
		for (int i = 0; i < nspecpages; i++)
		{
			int npalettes = *(int *)tpagebuffer;

			temp += npalettes;

			if ((i & 1) != 0)
			{
				if (temp > MaxSpecCluts)
					MaxSpecCluts = temp;

				temp = 0;
			}

			int tp = speclist[i].x;

			// find a special car TPAGEs
			if (page1 == tp || page2 == tp)
			{
				update_slotinfo(tp, slotsused, &tpage);
				LoadTPageAndCluts(&tpage, &clutpos, tp, tpagebuffer);

				clutsloaded += npalettes;
				slotsused++;
			}

			tpagebuffer += (speclist[i].y + 2047) & -CDSECTOR_SIZE;
		}

		while (clutsloaded < MaxSpecCluts)
		{
			IncrementClutNum(&clutpos);
			clutsloaded++;
		}
	}

	if (clutpos.x != 960) 
	{
		clutpos.x = 960;
		clutpos.y++;
	}

	for (int i = slotsused; i < 19; i++)
	{
		tpageslots[i] = 0xFF;

		slot_clutpos[i].vx = clutpos.x;
		slot_clutpos[i].vy = clutpos.y;

		slot_tpagepos[i].vx = tpage.x;
		slot_tpagepos[i].vy = tpage.y;

		IncrementTPageNum(&tpage);
		clutpos.y += 8;
	}

	//Emulator_SaveVRAM("VRAM_CLUTS_TPAGES.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
}



// decompiled code
// original method signature: 
// void /*$ra*/ ReloadIcons()
 // line 578, offset 0x00081118
	/* begin block 1 */
		// Start line: 580
		// Start offset: 0x00081118
		// Variables:
	// 		struct RECT tpage; // stack offset -88
	// 		struct RECT clutpos; // stack offset -80
	// 		char name[64]; // stack offset -72
	/* end block 1 */
	// End offset: 0x00081140
	// End Line: 599

	/* begin block 2 */
		// Start line: 1965
	/* end block 2 */
	// End Line: 1966

	/* begin block 3 */
		// Start line: 2169
	/* end block 3 */
	// End Line: 2170

	/* begin block 4 */
		// Start line: 2170
	/* end block 4 */
	// End Line: 2171

	/* begin block 5 */
		// Start line: 2174
	/* end block 5 */
	// End Line: 2175

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void ReloadIcons(void)
{
	ReportMode(0);
	ReportMode(1);
}



// decompiled code
// original method signature: 
// void /*$ra*/ GetTextureDetails(char *name /*stack 0*/, struct TEXTURE_DETAILS *info /*$s3*/)
 // line 602, offset 0x00080bb0
	/* begin block 1 */
		// Start line: 603
		// Start offset: 0x00080BB0
		// Variables:
	// 		int i; // $s2
	// 		int j; // $s1
	// 		int texamt; // $s4
	// 		struct TEXINF *texinf; // $v1
	// 		char *nametable; // stack offset -56
	/* end block 1 */
	// End offset: 0x00080D70
	// End Line: 647

	/* begin block 2 */
		// Start line: 1517
	/* end block 2 */
	// End Line: 1518

	/* begin block 3 */
		// Start line: 1545
	/* end block 3 */
	// End Line: 1546

	/* begin block 4 */
		// Start line: 1552
	/* end block 4 */
	// End Line: 1553

int environmenttpage = 0;

// [D] [T]
void GetTextureDetails(char *name, TEXTURE_DETAILS *info)
{
	char *nametable = texturename_buffer;

	for (int i = 0; i < tpage_amount; i++)
	{
		int texamt = tpage_texamts[i];
		TEXINF *texinf = tpage_ids[i];

		for (int j = 0; j < texamt; j++)
		{
			if (!strcmp(nametable + texinf->nameoffset, name))
			{
				if (!texture_is_icon || (i == environmenttpage))
				{
					info->tpageid = texture_pages[i];
					info->clutid = texture_cluts[i][j];
					info->texture_number = (char)j;
					info->texture_page = (char)i;

					setUVWH(&info->coords, texinf->x, texinf->y, texinf->width - 1, texinf->height - 1);

					// bust 'outta here, real fly
					return;
				}
			}

			texinf++;
		}
	}

	texture_is_icon = 0;
	GetTextureDetails("SEA", info);	// weird but ok, ok...
}





