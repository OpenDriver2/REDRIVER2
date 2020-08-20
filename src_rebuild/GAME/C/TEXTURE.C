#include "THISDUST.H"
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
	{ 0x36, 0x37, 0x42, 0x43, 0x38, 0x39, 0x44, 0x45, 0x3D, 0x40, 0x3D, 0x40},
	{ 0x26, 0x27, 0x26, 0x27, 0x2A, 0x2B, 0x2C, 0x2D, 0x30, 0x31, 0x30, 0x31},
	{ 0x12, 0x13, 0x41, 0x42, 0x43, 0x44, 0xB, 0xC, 0x3F, 0x40, 0x3F, 0x40},
	{ 0x42, 0x43, 0x4D, 0x4E, 0x49, 0x4A, 0x4B, 0x4C, 0x45, 0x46, 0x47, 0x48}
};

char carTpages[4][8] = {
	{1, 0x41, 0x3E, 0x32, 0x3F, 0x3A, 0x36, 0x37},
	{0xA, 0x23, 0x14, 0x25, 0x33, 0x24, 0x26, 0x27},
	{0x29, 0x36, 0x3E, 0x11, 0x20, 0x3B, 0x12, 0},
	{0x37, 0x39, 0x44, 0x3A, 0x3C, 0x3B, 0x42, 0x43}
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

// [D]
void IncrementTPageNum(RECT16 *tpage)
{
	int i;
	i = 1;

	while (true) 
	{
		if (tpage->x == tpagepos[i-1].x &&	// proper tpage position
			tpage->y == tpagepos[i-1].y || 
			tpagepos[i].x == -1)			// or out of tpages?
			break;
		i++;
	}

	tpage->x = tpagepos[i].x;
	tpage->y = tpagepos[i].y;

	if (tpagepos[i].x == -1)
	{
		NoTextureMemory = 100;

		tpage->x = tpagepos[i-1].x;
		tpage->y = tpagepos[i-1].y;
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

// [D]
// Originally ASM function
char* unpackTexture(char *dest, char *src)
{
	bool bVar1;
	char cVar2;
	char *pcVar3;
	char *pcVar4;
	uint uVar5;

	pcVar4 = dest + 0x7fff;
	do {
		uVar5 = (*src);
		pcVar3 = src + 1;
		cVar2 = *pcVar3;
		if ((uVar5 & 0x80) == 0) {
			while (true) {
				pcVar3 = pcVar3 + 1;
				*pcVar4 = cVar2;
				pcVar4 = pcVar4 + -1;
				bVar1 = uVar5 == 0;
				uVar5 = uVar5 - 1;
				if (bVar1) break;
				cVar2 = *pcVar3;
			}
		}
		else {
			pcVar3 = src + 2;
			*pcVar4 = cVar2;
			pcVar4 = pcVar4 + -1;
			do {
				*pcVar4 = cVar2;
				pcVar4 = pcVar4 + -1;
				bVar1 = uVar5 != 0;
				uVar5 = uVar5 + 1;
			} while (bVar1);
		}
		src = pcVar3;
	} while (dest <= pcVar4);
	return pcVar3;
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

//[D]
TEXINF * GetTEXINFName(char *name, int *tpagenum, int *texturenum)
{
	char *pcVar1;
	int iVar2;
	TEXINF *pTVar3;
	int iVar4;
	int iVar5;
	TEXINF *pTVar6;
	int iVar7;
	int *piVar8;
	TEXINF **ppTVar9;

	pcVar1 = texturename_buffer;
	iVar7 = 0;
	pTVar6 = NULL;

	if (0 < tpage_amount) 
	{
		ppTVar9 = tpage_ids;
		piVar8 = tpage_texamts;

		do {
			iVar5 = *piVar8;
			pTVar6 = *ppTVar9;
			iVar4 = 0;
			pTVar3 = pTVar6;

			if (0 < iVar5) 
			{
				do {
					iVar2 = strcmp(pcVar1 + pTVar3->nameoffset, name);

					if (iVar2 == 0) 
					{
						*tpagenum = iVar7;
						*texturenum = iVar4;
						return pTVar3;
					}

					iVar4 = iVar4 + 1;
					pTVar3 = pTVar3 + 1;
				} while (iVar4 < iVar5);
			}

			ppTVar9 = ppTVar9 + 1;
			iVar7 = iVar7 + 1;
			piVar8 = piVar8 + 1;

		} while (iVar7 < tpage_amount);
	}
	return pTVar6;
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
	int page1;
	int page2;

	bool bVar3;
	short sVar5;
	short sVar6;
	short sVar7;
	short sVar8;
	u_short uVar9;
	int nsectors;
	int iVar10;
	unsigned char *puVar11;
	int *addr;
	int *piVar12;
	int iVar13;
	ushort *psVar14;
	u_short *puVar15;
	int tpageId;
	DVECTOR *pDVar16;
	int nsectors_00;
	int iVar17;
	uint uVar18;
	char *tpageaddress;
	DVECTOR *pDVar19;

	// init tpage and cluts
	psVar14 = texture_pages;
	nsectors_00 = 127;
	MaxSpecCluts = 0;
	do {
		*psVar14 = GetTPage(0, 0, 960, 0);
		nsectors_00--;
		psVar14++;
	} while (-1 < nsectors_00);

	nsectors_00 = 0;
	iVar17 = 1;

	do {
		puVar15 = texture_cluts[nsectors_00];

		nsectors_00 = 31;
		do {
			*puVar15 = GetClut(960, 16);
			nsectors_00--;
			puVar15++;
		} while (-1 < nsectors_00);

		bVar3 = iVar17 < 128;
		nsectors_00 = iVar17;
		iVar17++;
	} while (bVar3);

	slotsused = 0;
	memset(tpageloaded, 0, sizeof(tpageloaded));

	clutpos.x = 960;
	clutpos.y = 256;
	clutpos.w = 16;
	clutpos.h = 1;

	tpage.w = 64;
	tpage.h = 256;

	mapclutpos.x = 960;
	mapclutpos.y = 256;
	mapclutpos.w = 16;
	mapclutpos.h = 1;

	tpage.x = tpagepos[0].x;
	tpage.y = tpagepos[0].y;
	nsectors_00 = 0;

	IncrementClutNum(&clutpos);
	fontclutpos.x = clutpos.x;
	fontclutpos.y = clutpos.y;
	fontclutpos.w = clutpos.w;
	fontclutpos.h = clutpos.h;

	IncrementClutNum(&clutpos);
	ProcessPalletLump(palette_lump, 0);

	load_civ_palettes(&clutpos);

	tpageaddress = mallocptr;
	if (0 < nperms)
	{
		XYPAIR* perm = permlist;
		iVar17 = nperms;

		do {
			nsectors_00 += (perm->y + 2047) / CDSECTOR_SIZE;
			iVar17--;
			perm++;
		} while (iVar17 != 0);
	}

#ifdef PSX
	loadsectors(tpageaddress, *sector, nsectors_00);
#else
	loadsectorsPC(g_CurrentLevelFileName, tpageaddress, *sector, nsectors_00);
#endif // PSX

	*sector += nsectors_00;

	nsectors_00 = 0;
	if (0 < nperms) 
	{
		do {
			nsectors = nsectors_00 + 1;
			iVar17 = permlist[nsectors_00].y;
			nsectors_00 = permlist[nsectors_00].x;

			update_slotinfo(nsectors_00, slotsused, &tpage);

			LoadTPageAndCluts(&tpage, &clutpos, nsectors_00, tpageaddress);
			slotsused++;

			tpageaddress += (iVar17 + 0x7ffU & 0xfffff800);
			nsectors_00 = nsectors;
		} while (nsectors < nperms);
	}

	addr = (int *)mallocptr;

	slot_clutpos[slotsused].vx = clutpos.x;
	slot_clutpos[slotsused].vy = clutpos.y;

	iVar13 = (MissionHeader->residentModels[4] - 8) * 2;		// int specmodel
	specialSlot = (short)slotsused;

	page1 = specTpages[GameLevel][iVar13];
	page2 = specTpages[GameLevel][iVar13 + 1];

	carTpages[GameLevel][6] = page1;
	carTpages[GameLevel][7] = page2;

	if (nspecpages != 0)
	{
		iVar13 = 0;
		nsectors_00 = 0;
		nsectors = 0;

		iVar17 = nspecpages;

		if (0 < iVar17)
		{
			XYPAIR* spec = speclist;
			do {
				nsectors += ((spec->y + 0x7ff) / 2048);
				iVar17--;
				spec++;
			} while (iVar17 != 0);
		}

#ifdef PSX
		loadsectors((char *)addr, *sector, nsectors);
#else
		loadsectorsPC(g_CurrentLevelFileName, (char *)addr, *sector, nsectors);
#endif // PSX


		*sector += nsectors;
		uVar18 = 0;

		if (0 < nspecpages) 
		{
			do {
				iVar13 += *addr;

				iVar17 = speclist[uVar18].y;	// must be size
				tpageId = speclist[uVar18].x;

				if ((uVar18 & 1) != 0) 
				{
					if (iVar13 > MaxSpecCluts)
						MaxSpecCluts = iVar13;

					iVar13 = 0;
				}

				// find a special car TPAGEs
				if (page1 == tpageId || page2 == tpageId)
				{
					update_slotinfo(tpageId, slotsused, &tpage);
					LoadTPageAndCluts(&tpage, &clutpos, tpageId, (char *)addr);

					nsectors_00 += *addr;
					slotsused++;
				}

				uVar18++;
				addr = (int *)((int)addr + (iVar17 + 0x7ffU & 0xfffff800));	// [A] don't touch this sphaget for now

			} while (uVar18 < nspecpages);
		}

		if (nsectors_00 < MaxSpecCluts)
		{
			do {
				nsectors_00++;
				IncrementClutNum(&clutpos);
			} while (nsectors_00 < MaxSpecCluts);
		}
	}

	if (clutpos.x != 960) 
	{
		clutpos.y++;
		clutpos.x = 960;
	}

	if (slotsused < 19) 
	{
		pDVar19 = &slot_tpagepos[slotsused];
		pDVar16 = &slot_clutpos[slotsused];

		nsectors_00 = slotsused;

		do {
			tpageslots[nsectors_00] = 0xFF;

			pDVar16->vx = clutpos.x;
			pDVar16->vy = clutpos.y;
			pDVar19->vx = tpage.x;
			pDVar19->vy = tpage.y;

			IncrementTPageNum(&tpage);
			clutpos.y += 8;

			pDVar19++;
			pDVar16++;

			nsectors_00++;
		} while (nsectors_00 < 19);
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
	return;
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

// [D]
void GetTextureDetails(char *name, TEXTURE_DETAILS *info)
{
	ushort uVar1;
	char *pcVar2;
	int iVar3;
	TEXINF *pTVar4;
	TEXINF **ppTVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	unsigned short *psVar9;
	int *piVar10;

	pcVar2 = texturename_buffer;
	iVar7 = 0;

	if (0 < tpage_amount) 
	{
		ppTVar5 = tpage_ids;
		piVar10 = tpage_texamts;
		psVar9 = texture_pages;

		do {
			iVar8 = *piVar10;
			pTVar4 = *ppTVar5;
			iVar6 = 0;

			if (0 < iVar8) 
			{
				do {
					iVar3 = strcmp(pcVar2 + pTVar4->nameoffset, name);

					if ((iVar3 == 0) && ((texture_is_icon == 0 || (iVar7 == environmenttpage)))) 
					{
						info->tpageid = *psVar9;
						uVar1 = texture_cluts[iVar7][iVar6];
						info->texture_number = (char)iVar6;
						info->texture_page = (char)iVar7;
						info->clutid = uVar1;
						(info->coords).u0 = pTVar4->x;
						(info->coords).v0 = pTVar4->y;
						(info->coords).u1 = pTVar4->x + pTVar4->width + -1;
						(info->coords).v1 = pTVar4->y;
						(info->coords).u2 = pTVar4->x;
						(info->coords).v2 = pTVar4->y + pTVar4->height + -1;
						(info->coords).u3 = pTVar4->x + pTVar4->width + -1;
						(info->coords).v3 = pTVar4->y + pTVar4->height + -1;
						return;
					}

					iVar6 = iVar6 + 1;
					pTVar4 = pTVar4 + 1;
				} while (iVar6 < iVar8);
			}

			ppTVar5 = ppTVar5 + 1;
			piVar10 = piVar10 + 1;
			iVar7 = iVar7 + 1;
			psVar9++;

		} while (iVar7 < tpage_amount);
	}

	texture_is_icon = 0;
	GetTextureDetails("SEA", info);	// weird but ok, ok...
}





