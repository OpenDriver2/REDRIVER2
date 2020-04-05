#include "THISDUST.H"
#include "TEXTURE.H"
#include "SYSTEM.H"


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
char* texturename_buffer = NULL;

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
void IncrementClutNum(RECT *clut)
{
	short sVar1;

	sVar1 = clut->x + 0x10;
	clut->x = sVar1;
	if (sVar1 == 0x400) {
		clut->x = 0x3c0;
		clut->y = clut->y + 1;
	}
	return;
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

void IncrementTPageNum(RECT *tpage)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar4 = 1;
	while (true) {
		iVar2 = iVar4 + -1;
		if (((tpage->x == (&tpagepos)[iVar2].x) &&
			(iVar3 = iVar4 << 2, tpage->y == (&tpagepos)[iVar2].y)) ||
			(iVar3 = iVar4 * 4, (&tpagepos)[iVar4].x == -1)) break;
		iVar4 = iVar4 + 1;
	}
	sVar1 = *(short *)((int)&tpagepos.x + iVar3);
	tpage->x = sVar1;
	tpage->y = *(short *)((int)&tpagepos.y + iVar3);
	if (sVar1 == -1) {
		NoTextureMemory = 100;
		tpage->x = (&tpagepos)[iVar2].x;
		tpage->y = (&tpagepos)[iVar2].y;
	}
	return;*/
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

int LoadTPageAndCluts(RECT *tpage, RECT *cluts, int tpage2send, char *tpageaddress)
{
	UNIMPLEMENTED();
	return 0;
	/*
	u_short uVar1;
	u_short *puVar2;
	int iVar3;
	int iVar4;
	short local_28;
	short local_26;
	short local_24;
	undefined2 local_22;

	iVar4 = *(int *)tpageaddress;
	tpageaddress = tpageaddress + 4;
	iVar3 = 0;
	if (0 < iVar4) {
		puVar2 = &texture_cluts + tpage2send * 0x20;
		do {
			LoadImage(cluts, tpageaddress);
			tpageaddress = tpageaddress + 0x20;
			iVar3 = iVar3 + 1;
			uVar1 = GetClut((int)cluts->x, (int)cluts->y);
			*puVar2 = uVar1;
			IncrementClutNum(cluts);
			puVar2 = puVar2 + 1;
		} while (iVar3 < iVar4);
	}
	local_28 = tpage->x;
	local_26 = tpage->y;
	local_24 = tpage->w;
	local_22 = 0x100;
	decomp_asm(&DAT_000f3000, tpageaddress);
	LoadImage(&local_28, &DAT_000f3000);
	uVar1 = GetTPage(0, 0, (int)tpage->x, (int)tpage->y);
	(&texture_pages)[tpage2send] = uVar1;
	IncrementTPageNum(tpage);
	return 1;
	*/
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
	UNIMPLEMENTED();
	return 0;
	/*
	byte *pbVar1;
	int iVar2;

	pbVar1 = (byte *)model->poly_block;
	iVar2 = 0;
	if (model->num_polys != 0) {
		do {
			switch ((uint)*pbVar1 & 0x1f) {
			case 4:
			case 5:
			case 6:
			case 7:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
				if ((uint)pbVar1[2] == t_id) {
					return 1;
				}
			}
			iVar2 = iVar2 + 1;
			pbVar1 = pbVar1 + PolySizes[*pbVar1];
		} while (iVar2 < (int)(uint)model->num_polys);
	}
	return 0;
	*/
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

TEXINF * GetTEXINFName(char *name, int *tpagenum, int *texturenum)
{
	UNIMPLEMENTED();
	return 0;
	/*
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
	pTVar6 = (TEXINF *)0x0;
	if (0 < tpage_amount) {
		ppTVar9 = tpage_ids128;
		piVar8 = &tpage_texamts;
		do {
			iVar5 = *piVar8;
			pTVar6 = *ppTVar9;
			iVar4 = 0;
			pTVar3 = pTVar6;
			if (0 < iVar5) {
				do {
					iVar2 = strcmp(pcVar1 + pTVar3->nameoffset, name);
					if (iVar2 == 0) {
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
	*/
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

TEXINF * GetTextureInfoName(char *name, TPAN *result)
{
	UNIMPLEMENTED();
	return 0;
	/*
	TEXINF *pTVar1;
	uchar local_10[4];
	uchar local_c[4];

	pTVar1 = GetTEXINFName(name, (int *)local_10, (int *)local_c);
	result->texture_page = local_10[0];
	result->texture_number = local_c[0];
	return pTVar1;
	*/
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

void update_slotinfo(int tpage, int slot, RECT *pos)
{
	UNIMPLEMENTED();
	/*
	(&tpageslots)[slot] = (uchar)tpage;
	tpageloaded[tpage] = (uchar)slot;
	(&slot_tpagepos)[slot].vx = pos->x;
	(&slot_tpagepos)[slot].vy = pos->y;
	return;
	*/
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

TP *tpage_position = NULL;
TEXINF* tpage_ids[128] = {0};
int texamount = 0;
int tpage_amount = 0;
int tpage_texamts[128];

int nspecpages = 0;
int nperms = 0;
XYPAIR *speclist = NULL;
XYPAIR *permlist = NULL;

// [D]
void ProcessTextureInfo(char *lump_ptr)
{
	int iVar1;
	TEXINF *pTVar2;
	int *amts;
	TEXINF **ids;

	iVar1 = *(int *)lump_ptr;
	texamount = *(int *)(lump_ptr + 4);
	tpage_position = (TP *)(lump_ptr + 8);

	pTVar2 = (TEXINF *)(tpage_position + iVar1 + 1);
	tpage_amount = iVar1;

	if (0 < iVar1) {
		ids = tpage_ids;
		amts = tpage_texamts;

		do {
			texamount = *(int *)&pTVar2->id;

			*ids = (TEXINF *)&pTVar2->x;
			ids = ids + 1;
			iVar1--;
			pTVar2 = (TEXINF *)&pTVar2->x + texamount;
			*amts = texamount;
			amts = (int *)((ulong *)amts + 1);
		} while (iVar1 != 0);
	}

	nspecpages = *(ulong *)&pTVar2[0x10].x;
	nperms = *(ulong *)&pTVar2->id;
	speclist = (XYPAIR *)(pTVar2 + 0x11);
	permlist = (XYPAIR *)&pTVar2->x;
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

void LoadPermanentTPages(int *sector)
{
	UNIMPLEMENTED();
	/*
	byte bVar1;
	byte bVar2;
	bool bVar3;
	_MISSION *p_Var4;
	short sVar5;
	short sVar6;
	short sVar7;
	short sVar8;
	u_short uVar9;
	int nsectors;
	int iVar10;
	uchar *puVar11;
	int *addr;
	int *piVar12;
	int iVar13;
	u_short *puVar14;
	uint tpage;
	DVECTOR *pDVar15;
	int nsectors_00;
	int iVar16;
	uint uVar17;
	char *tpageaddress;
	DVECTOR *pDVar18;

	puVar14 = &texture_pages;
	nsectors_00 = 0x7f;
	MaxSpecCluts = 0;
	do {
		uVar9 = GetTPage(0, 0, 0x3c0, 0);
		*puVar14 = uVar9;
		nsectors_00 = nsectors_00 + -1;
		puVar14 = puVar14 + 1;
	} while (-1 < nsectors_00);
	nsectors_00 = 0;
	iVar16 = 1;
	do {
		puVar14 = &texture_cluts + nsectors_00 * 0x20;
		nsectors_00 = 0x1f;
		do {
			uVar9 = GetClut(0x3c0, 0x10);
			*puVar14 = uVar9;
			nsectors_00 = nsectors_00 + -1;
			puVar14 = puVar14 + 1;
		} while (-1 < nsectors_00);
		bVar3 = iVar16 < 0x80;
		nsectors_00 = iVar16;
		iVar16 = iVar16 + 1;
	} while (bVar3);
	slotsused = 0;
	memset(tpageloaded, 0, 0x80);
	clutpos.x = 0x3c0;
	clutpos.y = 0x100;
	clutpos._4_4_ = 0x10010;
	tpage.w = 0x40;
	tpage.h = 0x100;
	mapclutpos.x = 0x3c0;
	mapclutpos.y = 0x100;
	mapclutpos.w = 0x10;
	mapclutpos.h = 1;
	tpage.x = tpagepos.x;
	tpage.y = tpagepos.y;
	nsectors_00 = 0;
	IncrementClutNum(&clutpos);
	fontclutpos.x = clutpos.x;
	fontclutpos.y = clutpos.y;
	fontclutpos._4_4_ = clutpos._4_4_;
	IncrementClutNum(&clutpos);
	ProcessPalletLump(palette_lump, 0);
	load_civ_palettes(&clutpos);
	tpageaddress = mallocptr;
	if (0 < nperms) {
		addr = &permlist->y;
		iVar16 = nperms;
		do {
			nsectors = *addr + 0x7ff;
			if (nsectors < 0) {
				nsectors = *addr + 0xffe;
			}
			nsectors_00 = nsectors_00 + (nsectors >> 0xb);
			iVar16 = iVar16 + -1;
			addr = addr + 2;
		} while (iVar16 != 0);
	}
	loadsectors(mallocptr, *sector, nsectors_00);
	*sector = *sector + nsectors_00;
	nsectors_00 = 0;
	if (0 < nperms) {
		do {
			nsectors = nsectors_00 + 1;
			iVar16 = permlist[nsectors_00].y;
			nsectors_00 = permlist[nsectors_00].x;
			update_slotinfo(nsectors_00, slotsused, &tpage);
			LoadTPageAndCluts(&tpage, &clutpos, nsectors_00, tpageaddress);
			slotsused = slotsused + 1;
			tpageaddress = tpageaddress + (iVar16 + 0x7ffU & 0xfffff800);
			nsectors_00 = nsectors;
		} while (nsectors < nperms);
	}
	iVar16 = slotsused;
	addr = (int *)mallocptr;
	nsectors_00 = GameLevel;
	slot_clutpos[slotsused].vx = clutpos.x;
	p_Var4 = MissionHeader;
	slot_clutpos[iVar16].vy = clutpos.y;
	nsectors = nsectors_00 * 0xc;
	nsectors_00 = nsectors_00 * 8;
	iVar13 = (p_Var4->residentModels[4] + -8) * 2;
	specialSlot = (short)slotsused;
	bVar1 = specTpages[iVar13 + nsectors];
	carTpages[nsectors_00 + 6] = bVar1;
	iVar16 = nspecpages;
	bVar2 = specTpages[iVar13 + nsectors + 1];
	bVar3 = nspecpages != 0;
	carTpages[nsectors_00 + 7] = bVar2;
	if (bVar3) {
		iVar13 = 0;
		nsectors_00 = 0;
		nsectors = 0;
		if (0 < iVar16) {
			piVar12 = &speclist->y;
			do {
				iVar10 = *piVar12 + 0x7ff;
				if (iVar10 < 0) {
					iVar10 = *piVar12 + 0xffe;
				}
				nsectors = nsectors + (iVar10 >> 0xb);
				iVar16 = iVar16 + -1;
				piVar12 = piVar12 + 2;
			} while (iVar16 != 0);
		}
		loadsectors((char *)addr, *sector, nsectors);
		*sector = *sector + nsectors;
		uVar17 = 0;
		if (0 < nspecpages) {
			do {
				iVar13 = iVar13 + *addr;
				iVar16 = speclist[uVar17].y;
				tpage = speclist[uVar17].x;
				if ((uVar17 & 1) != 0) {
					if (MaxSpecCluts < iVar13) {
						MaxSpecCluts = iVar13;
					}
					iVar13 = 0;
				}
				if ((tpage == (uint)bVar1) || (tpage == (uint)bVar2)) {
					update_slotinfo(tpage, slotsused, &tpage);
					LoadTPageAndCluts(&tpage, &clutpos, tpage, (char *)addr);
					nsectors_00 = nsectors_00 + *addr;
					slotsused = slotsused + 1;
				}
				uVar17 = uVar17 + 1;
				addr = (int *)((int)addr + (iVar16 + 0x7ffU & 0xfffff800));
			} while ((int)uVar17 < nspecpages);
		}
		if (nsectors_00 < MaxSpecCluts) {
			do {
				nsectors_00 = nsectors_00 + 1;
				IncrementClutNum(&clutpos);
			} while (nsectors_00 < MaxSpecCluts);
		}
	}
	if (clutpos.x != 0x3c0) {
		clutpos.y = clutpos.y + 1;
		clutpos.x = 0x3c0;
	}
	if (slotsused < 0x13) {
		pDVar18 = &slot_tpagepos + slotsused;
		pDVar15 = slot_clutpos + slotsused;
		nsectors_00 = slotsused;
		do {
			sVar8 = clutpos.y;
			sVar7 = clutpos.x;
			sVar6 = tpage.y;
			sVar5 = tpage.x;
			puVar11 = &tpageslots + nsectors_00;
			nsectors_00 = nsectors_00 + 1;
			*puVar11 = -1;
			pDVar15->vx = sVar7;
			pDVar15->vy = sVar8;
			pDVar18->vx = sVar5;
			pDVar18->vy = sVar6;
			IncrementTPageNum(&tpage);
			pDVar18 = pDVar18 + 1;
			clutpos.y = clutpos.y + 8;
			pDVar15 = pDVar15 + 1;
		} while (nsectors_00 < 0x13);
	}
	return;*/
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

void GetTextureDetails(char *name, TEXTURE_DETAILS *info)
{
	UNIMPLEMENTED();
	/*
	ushort uVar1;
	char *pcVar2;
	int iVar3;
	TEXINF *pTVar4;
	TEXINF **ppTVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	ushort *puVar9;
	int *piVar10;

	pcVar2 = texturename_buffer;
	iVar7 = 0;
	if (0 < tpage_amount) {
		ppTVar5 = tpage_ids128;
		piVar10 = &tpage_texamts;
		puVar9 = &texture_pages;
		do {
			iVar8 = *piVar10;
			pTVar4 = *ppTVar5;
			iVar6 = 0;
			if (0 < iVar8) {
				do {
					iVar3 = strcmp(pcVar2 + pTVar4->nameoffset, name);
					if ((iVar3 == 0) && ((texture_is_icon == 0 || (iVar7 == environmenttpage)))) {
						info->tpageid = *puVar9;
						uVar1 = (&texture_cluts)[iVar7 * 0x20 + iVar6];
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
			puVar9 = puVar9 + 1;
		} while (iVar7 < tpage_amount);
	}
	texture_is_icon = 0;
	GetTextureDetails((char *)&PTR_DAT_000aa9c0, info);
	return;
	*/
}





