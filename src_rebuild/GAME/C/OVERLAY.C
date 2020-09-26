#include "DRIVER2.H"
#include "OVERLAY.H"
#include "SYSTEM.H"
#include "MISSION.H"
#include "GLAUNCH.H"
#include "MAIN.H"
#include "PAUSE.H"
#include "DIRECTOR.H"
#include "OVERMAP.H"
#include "COP_AI.H"
#include "CUTSCENE.H"
#include "CARS.H"
#include "PRES.H"
#include "PLAYERS.H"
#include "CAMERA.H"
#include "SCORES.H"

COLOUR_BAND felonyColour[3] =
{
  { { 0u, 0u, 255u, 0u }, 0, 0 },
  { { 255u, 0u, 0u, 0u }, 659, 0 },
  { { 0u, 0u, 255u, 0u }, 4096, 2 }
};

COLOUR_BAND playerDamageColour[3] =
{
  { { 0u, 255u, 0u, 0u }, 0, 0 },
  { { 255u, 0u, 0u, 0u }, 3686, 0 },
  { { 0u, 0u, 0u, 0u }, 4096, 2 }
};

COLOUR_BAND damageColour[2] =
{ { { 0u, 255u, 0u, 0u }, 0, 0 }, { { 255u, 0u, 0u, 0u }, 4096, 0 } };


// decompiled code
// original method signature: 
// void /*$ra*/ InitOverlays()
 // line 270, offset 0x00014a58
	/* begin block 1 */
		// Start line: 540
	/* end block 1 */
	// End Line: 541

	/* begin block 2 */
		// Start line: 541
	/* end block 2 */
	// End Line: 542

/* WARNING: Unknown calling convention yet parameter storage is locked */

_PERCENTAGE_BAR PlayerDamageBar;
_PERCENTAGE_BAR Player2DamageBar;
_PERCENTAGE_BAR DamageBar;
_PERCENTAGE_BAR FelonyBar;
_PERCENTAGE_BAR ProxyBar;

int gDoOverlays = 1;

// [D]
void InitOverlays(void)
{
	bool bVar1;
	gDoOverlays = 1;

	InitPercentageBar(&PlayerDamageBar, MaxPlayerDamage[0], playerDamageColour, "Damage");

	PlayerDamageBar.xpos = 0x10;
	PlayerDamageBar.ypos = 0x18;

	bVar1 = 1 < NumPlayers;
	PlayerDamageBar.active = 1;

	if (bVar1)
	{
		InitPercentageBar(&Player2DamageBar, MaxPlayerDamage[1], playerDamageColour, "Damage");
		Player2DamageBar.xpos = 0x10;
		Player2DamageBar.ypos = 0x8c;
	}

	Player2DamageBar.active = (bVar1);

	InitPercentageBar(&FelonyBar, 0x1000, felonyColour, "Felony");
	FelonyBar.xpos = 0x10;
	FelonyBar.ypos = 0x2e;
	FelonyBar.active = 0;

	InitPercentageBar(&DamageBar, 1, damageColour, "Damage");
	DamageBar.xpos = 0xd0;
	DamageBar.ypos = 0x18;
	DamageBar.flags = 1;
	DamageBar.active = 0;

	InitPercentageBar(&ProxyBar, TAIL_TOOFAR - TAIL_TOOCLOSE, felonyColour, "Proximity");
	ProxyBar.xpos = 0x10;
	ProxyBar.ypos = 0x2e;
	ProxyBar.active = 0;

	InitOverheadMap();

	if (GameType == GAME_CAPTURETHEFLAG) {
		PlayerDamageBar.active = 0;
		Player2DamageBar.active = 0;
		gInvincibleCar = 1;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DisplayOverlays()
 // line 329, offset 0x00014c3c
	/* begin block 1 */
		// Start line: 701
	/* end block 1 */
	// End Line: 702

	/* begin block 2 */
		// Start line: 702
	/* end block 2 */
	// End Line: 703

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DisplayOverlays(void)
{
	short *felony;

	if (NoPlayerControl == 0 && gInGameCutsceneActive == 0 && gInGameCutsceneDelay == 0)
	{
		if (NumPlayers > 1) 
		{
			if (CurrentPlayerView == 0)
				return;

			SetFullscreenDrawing();
		}

		UpdateFlashValue();

		if (gShowMap == 0)
		{
			FastForward = 0;

			if (!gDoOverlays)
				return;

			DrawPercentageBar(&PlayerDamageBar);
			DrawPercentageBar(&Player2DamageBar);
			DrawPercentageBar(&DamageBar);
			DrawPercentageBar(&FelonyBar);

			DrawDrivingGameOverlays();			
			DrawOverheadMap();

			if (CopsCanSeePlayer != 0)
			{
				if (player[0].playerCarId < 0)
					felony = &pedestrianFelony;
				else 
					felony = &car_data[player[0].playerCarId].felonyRating;

				if (658 < *felony) 
					DrawCopIndicators();
			}
		}
		else 
		{
			FastForward = 1;
			DrawFullscreenMap();
		}
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetFullscreenDrawing()
 // line 378, offset 0x00015e70
	/* begin block 1 */
		// Start line: 380
		// Start offset: 0x00015E70
		// Variables:
	// 		struct DRAWENV drawenv; // stack offset -104
	// 		struct DR_ENV *dr_env; // $s0
	/* end block 1 */
	// End offset: 0x00015F20
	// End Line: 388

	/* begin block 2 */
		// Start line: 1447
	/* end block 2 */
	// End Line: 1448

	/* begin block 3 */
		// Start line: 756
	/* end block 3 */
	// End Line: 757

	/* begin block 4 */
		// Start line: 1448
	/* end block 4 */
	// End Line: 1449

	/* begin block 5 */
		// Start line: 1452
	/* end block 5 */
	// End Line: 1453

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void SetFullscreenDrawing(void)
{
	DR_ENV *drenv;
	DRAWENV drawenv;

	drenv = (DR_ENV *)current->primptr;

	drawenv.clip.x = 256;
	SetDefDrawEnv((DRAWENV *)&drawenv, 0, current->draw.clip.y & 256, 320, 256);

	SetDrawEnv(drenv, &drawenv);

	addPrim(current->ot + 8, drenv);
	current->primptr += sizeof(DR_ENV);
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitPercentageBar(struct _PERCENTAGE_BAR *bar /*$a0*/, int size /*$a1*/, struct COLOUR_BAND *pColourBand /*$a2*/, char *tag /*$a3*/)
 // line 395, offset 0x00015f20
	/* begin block 1 */
		// Start line: 1476
	/* end block 1 */
	// End Line: 1477

	/* begin block 2 */
		// Start line: 1484
	/* end block 2 */
	// End Line: 1485

	/* begin block 3 */
		// Start line: 1485
	/* end block 3 */
	// End Line: 1486

// [D]
void InitPercentageBar(_PERCENTAGE_BAR *bar, int size, COLOUR_BAND *pColourBand, char *tag)
{
	bar->xpos = 0x96;
	bar->ypos = 10;
	bar->width = 0x66;
	bar->height = 10;
	bar->position = 0;
	bar->max = (ushort)size;
	bar->pColourBand = pColourBand;
	bar->flags = 0;
	bar->tag = tag;
	bar->active = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ EnablePercentageBar(struct _PERCENTAGE_BAR *bar /*$a0*/, int max /*$a1*/)
 // line 414, offset 0x00015f58
	/* begin block 1 */
		// Start line: 1524
	/* end block 1 */
	// End Line: 1525

	/* begin block 2 */
		// Start line: 1525
	/* end block 2 */
	// End Line: 1526

	/* begin block 3 */
		// Start line: 1527
	/* end block 3 */
	// End Line: 1528

// [D]
void EnablePercentageBar(_PERCENTAGE_BAR *bar, int max)
{
	bar->position = 0;
	bar->max = (ushort)max;
	bar->active = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawPercentageBar(struct _PERCENTAGE_BAR *bar /*$fp*/)
 // line 426, offset 0x00014da8
	/* begin block 1 */
		// Start line: 427
		// Start offset: 0x00014DA8
		// Variables:
	// 		struct POLY_G4 *poly; // $s0
	// 		struct CVECTOR temp; // stack offset -56
	// 		int min_x; // $s1
	// 		int max_x; // $s7
	// 		int min_y; // $s2
	// 		int max_y; // stack offset -48
	// 		char *tag; // $s0

		/* begin block 1.1 */
			// Start line: 520
			// Start offset: 0x00015248
			// Variables:
		// 		short tagX; // $s1
		// 		short tagY; // $s2
		/* end block 1.1 */
		// End offset: 0x000152A4
		// End Line: 528
	/* end block 1 */
	// End offset: 0x000152D4
	// End Line: 530

	/* begin block 2 */
		// Start line: 895
	/* end block 2 */
	// End Line: 896

// [D]
void DrawPercentageBar(_PERCENTAGE_BAR *bar)
{
	short sVar1;
	short sVar3;
	uint uVar4;
	POLY_G4 *poly;
	POLY_G4 *poly2;
	short sVar5;
	short sVar9;
	CVECTOR temp;

	if (bar->active == 0)
		return;

	if (bar->max < bar->position) 
	{
		bar->position = bar->max;
	}

	if (bar->max == 0) 
	{
		sVar5 = bar->xpos;
		uVar4 = bar->flags;
		sVar9 = sVar5;
	}
	else 
	{
		uVar4 = bar->flags;

		if ((uVar4 & 1) == 0) 
		{
			sVar5 = bar->xpos;
			sVar9 = sVar5 + ((bar->width * bar->position) / bar->max);
		}
		else 
		{
			sVar9 = bar->xpos + bar->width;
			sVar5 = sVar9 - ((bar->width * bar->position) / bar->max);
		}
	}

	sVar1 = bar->ypos;
	sVar3 = bar->ypos + bar->height;

	if ((uVar4 & 2) == 0) 
	{
		poly = (POLY_G4 *)current->primptr;
		setPolyG4(poly);

		SetColourByValue(bar->pColourBand, (bar->position << 0xc) / bar->max, &temp);

		poly->r0 = temp.r;
		poly->g0 = temp.g;
		poly->b0 = temp.b;
		poly->r1 = temp.r;
		poly->g1 = temp.g;
		poly->b1 = temp.b;
		temp.r = temp.r >> 2;
		temp.g = temp.g >> 2;
		temp.b = temp.b >> 2;
		poly->r2 = temp.r;
		poly->g2 = temp.g;
		poly->b2 = temp.b;
		poly->r3 = temp.r;
		poly->g3 = temp.g;
		poly->x0 = sVar5;
		poly->y0 = bar->ypos;
		poly->x1 = sVar9;
		poly->y1 = bar->ypos;
		poly->b3 = temp.b;
		poly->x2 = sVar5;
		poly->x3 = sVar9;
		poly->y2 = bar->ypos + bar->height;
		poly->y3 = bar->ypos + bar->height;

		addPrim((u_long*)(current->ot + 1), poly);
		current->primptr += sizeof(POLY_G4);
	}

	poly2 = (POLY_G4 *)current->primptr;
	setPolyG4(poly2);
	setSemiTrans(poly2,1);
	poly2->x0 = bar->xpos;
	poly2->x2 = bar->xpos;
	poly2->r0 = 0;
	poly2->g0 = 0;
	poly2->b0 = 0;
	poly2->r1 = 0;
	poly2->g1 = 0;
	poly2->b1 = 0;
	poly2->r2 = 100;
	poly2->g2 = 100;
	poly2->b2 = 100;
	poly2->r3 = 100;
	poly2->g3 = 100;
	poly2->b3 = 100;
	poly2->y0 = bar->ypos;
	poly2->x1 = bar->xpos + bar->width;
	poly2->y1 = bar->ypos;
	poly2->x3 = bar->xpos + bar->width;
	poly2->y2 = bar->ypos + bar->height;
	poly2->y3 = bar->ypos + bar->height;

	addPrim((u_long*)(current->ot+1), poly2);
	current->primptr += sizeof(POLY_G4);

	LINE_F4* lineF4 = (LINE_F4*)current->primptr;
	setLineF4(lineF4);
	lineF4->r0 = 80;
	lineF4->g0 = 80;
	lineF4->b0 = 80;

	lineF4->x0 = bar->xpos - 1;
	lineF4->y0 = bar->ypos - 1;

	lineF4->x1 = bar->xpos + bar->width;
	lineF4->y1 = bar->ypos - 1;

	lineF4->x2 = bar->xpos + bar->width;
	lineF4->x3 = bar->xpos - 1;

	lineF4->y2 = bar->ypos + bar->height;
	lineF4->y3 = bar->ypos + bar->height;

	addPrim((u_long*)(current->ot + 1), lineF4);
	current->primptr += sizeof(LINE_F4);
		
	LINE_F2* lineF2 = (LINE_F2*)current->primptr;
	setLineF2(lineF2);
	lineF2->r0 = 80;
	lineF2->g0 = 80;
	lineF2->b0 = 80;

	lineF2->x0 = bar->xpos - 1;
	lineF2->y0 = bar->ypos - 1;

	lineF2->x1 = bar->xpos - 1;
	lineF2->y1 = bar->ypos + bar->height;

	addPrim((u_long*)(current->ot + 1), lineF2);
	current->primptr += sizeof(LINE_F2);

	TransparencyOn(current->ot + 1, 0x20);
		
	if (bar->tag != NULL)
	{
		SetTextColour(128, 128, 64);

		if ((bar->flags & 1U) == 0)
			PrintString(bar->tag, bar->xpos + 8, bar->ypos - 11);
		else
			PrintStringRightAligned(bar->tag, bar->xpos + bar->width - 8, bar->ypos - 11);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawProximityBar(struct _PERCENTAGE_BAR *bar /*$t3*/)
 // line 532, offset 0x000152d4
	/* begin block 1 */
		// Start line: 533
		// Start offset: 0x000152D4
		// Variables:
	// 		struct TILE *tile; // $a1
	// 		int min_x; // $s1
	// 		int max_x; // $s7
	// 		int min_y; // $s2
	// 		int max_y; // $fp
	// 		short total; // $v1
	// 		char *tag; // $s0

		/* begin block 1.1 */
			// Start line: 619
			// Start offset: 0x00015760
			// Variables:
		// 		short tagX; // $s1
		// 		short tagY; // $s2
		/* end block 1.1 */
		// End offset: 0x000157C4
		// End Line: 627
	/* end block 1 */
	// End offset: 0x000157F4
	// End Line: 629

	/* begin block 2 */
		// Start line: 1175
	/* end block 2 */
	// End Line: 1176

	/* begin block 3 */
		// Start line: 1178
	/* end block 3 */
	// End Line: 1179

// [D]
void DrawProximityBar(_PERCENTAGE_BAR *bar)
{
	int iVar3;
	TILE *tile;

	if (bar->active == 0)
		return;

	if (bar->position < TAIL_TOOCLOSE)
		bar->position = TAIL_TOOCLOSE;
	
	if (TAIL_TOOFAR < bar->position)
		bar->position = TAIL_TOOFAR;

	iVar3 = bar->position - TAIL_TOOCLOSE;

	tile = (TILE *)current->primptr;
	setTile(tile);
	tile->r0 = 16;
	tile->g0 = 16;
	tile->b0 = 16;

	tile->x0 = ((bar->width * iVar3) / (TAIL_TOOFAR - TAIL_TOOCLOSE) - 1) + bar->xpos;
	tile->w = 2;
	tile->y0 = bar->ypos;
	tile->h = bar->height;

	addPrim(current->ot + 1, tile);
	current->primptr += sizeof(TILE);

	POLY_G4* poly2 = (POLY_G4*)current->primptr;
	setPolyG4(poly2);
	poly2->r0 = 255;
	poly2->g0 = 0;
	poly2->b0 = 0;
	poly2->r1 = 0;
	poly2->g1 = 255;
	poly2->b1 = 0;
	poly2->r2 = 255;
	poly2->g2 = 0;
	poly2->b2 = 0;
	poly2->r3 = 0;
	poly2->g3 = 255;
	poly2->b3 = 0;

	poly2->x0 = bar->xpos;
	poly2->y0 = bar->ypos;
	poly2->x1 = bar->xpos + (bar->width / 2);
	poly2->y1 = bar->ypos;
	poly2->x2 = bar->xpos;
	poly2->y2 = bar->ypos + bar->height;
	poly2->x3 = bar->xpos + (bar->width / 2);
	poly2->y3 = bar->ypos + bar->height;

	addPrim(current->ot + 1, poly2);
	current->primptr += sizeof(POLY_G4);

	poly2 = (POLY_G4*)current->primptr;
	setPolyG4(poly2);

	poly2->r0 = 0;
	poly2->g0 = 255;
	poly2->b0 = 0;
	poly2->r1 = 255;
	poly2->g1 = 0;
	poly2->b1 = 0;
	poly2->r2 = 0;
	poly2->g2 = 255;
	poly2->b2 = 0;
	poly2->r3 = 255;
	poly2->g3 = 0;
	poly2->b3 = 0;

	poly2->x0 = bar->xpos + (bar->width / 2);
	poly2->y0 = bar->ypos;
	poly2->x1 = bar->xpos + bar->width;
	poly2->y1 = bar->ypos;
	poly2->x2 = bar->xpos + (bar->width / 2);
	poly2->y2 = bar->ypos + bar->height;
	poly2->x3 = bar->xpos + bar->width;
	poly2->y3 = bar->ypos + bar->height;

	addPrim(current->ot + 1, poly2);
	current->primptr += sizeof(POLY_G4);

	LINE_F4* lineF4 = (LINE_F4*)current->primptr;
	setLineF4(lineF4);
	lineF4->r0 = 80;
	lineF4->g0 = 80;
	lineF4->b0 = 80;

	lineF4->x0 = bar->xpos - 1;
	lineF4->y0 = bar->ypos - 1;

	lineF4->x1 = bar->xpos + bar->width;
	lineF4->y1 = bar->ypos - 1;

	lineF4->x2 = bar->xpos + bar->width;
	lineF4->x3 = bar->xpos - 1;

	lineF4->y2 = bar->ypos + bar->height;
	lineF4->y3 = bar->ypos + bar->height;

	addPrim((u_long*)(current->ot + 1), lineF4);
	current->primptr += sizeof(LINE_F4);

	LINE_F2* lineF2 = (LINE_F2*)current->primptr;
	setLineF2(lineF2);
	lineF2->r0 = 80;
	lineF2->g0 = 80;
	lineF2->b0 = 80;

	lineF2->x0 = bar->xpos - 1;
	lineF2->y0 = bar->ypos - 1;

	lineF2->x1 = bar->xpos - 1;
	lineF2->y1 = bar->ypos + bar->height;

	addPrim((u_long*)(current->ot + 1), lineF2);
	current->primptr += sizeof(LINE_F2);

	TransparencyOn(current->ot + 1, 0x20);

	TransparencyOn(current->ot + 1, 0x20);

	if (bar->tag != NULL)
	{
		SetTextColour(128, 128, 64);

		if ((bar->flags & 1U) == 0)
			PrintString(bar->tag, bar->xpos + 8, bar->ypos - 11);
		else 
			PrintStringRightAligned(bar->tag, bar->xpos + bar->width - 8, bar->ypos - 11);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetColourByValue(struct COLOUR_BAND *pColourBand /*$a3*/, int value /*$a1*/, struct CVECTOR *pOut /*$t0*/)
 // line 631, offset 0x00015f6c
	/* begin block 1 */
		// Start line: 632
		// Start offset: 0x00015F6C
		// Variables:
	// 		struct COLOUR_BAND *pPrevColourBand; // $a2
	// 		int scale; // $a0
	// 		int temp; // $a1
	/* end block 1 */
	// End offset: 0x00016098
	// End Line: 661

	/* begin block 2 */
		// Start line: 1960
	/* end block 2 */
	// End Line: 1961

	/* begin block 3 */
		// Start line: 1966
	/* end block 3 */
	// End Line: 1967

char OverlayFlashValue = 0;

// [D]
void SetColourByValue(COLOUR_BAND *pColourBand, int value, CVECTOR *pOut)
{
	COLOUR_BAND *pCVar1;
	COLOUR_BAND *pCVar2;

	int iVar3;
	int iVar4;

	pCVar2 = pColourBand + 1;

	if (pColourBand[1].value < value)
	{
		pCVar1 = pColourBand + 2;
		do {
			pCVar2 = pCVar1;
			pCVar1 = pCVar2 + 1;
		} while (pCVar2->value < value);
	}

	if ((pCVar2->flags != 0) && (pCVar2->flags == 2)) 
	{
		iVar3 = OverlayFlashValue * (pCVar2->value - pCVar2[-1].value);
		value = pCVar2[-1].value + (iVar3 >> 3);
	}

	iVar3 = pCVar2->value - pCVar2[-1].value;
	iVar4 = ((value - pCVar2[-1].value) * 0x1000) / iVar3;

	iVar3 = 0x1000 - iVar4;

	pOut->r = ((iVar3 * pCVar2[-1].colour.r + iVar4 * (pCVar2->colour).r) >> 0xc);
	pOut->g = ((iVar3 * pCVar2[-1].colour.g + iVar4 * (pCVar2->colour).g) >> 0xc);
	pOut->b = ((iVar3 * pCVar2[-1].colour.b + iVar4 * (pCVar2->colour).b) >> 0xc);
}



// decompiled code
// original method signature: 
// void /*$ra*/ TransparencyOn(void *potz /*$a0*/, unsigned short tpage /*$a1*/)
 // line 669, offset 0x00016098
	/* begin block 1 */
		// Start line: 670
		// Start offset: 0x00016098
		// Variables:
	// 		struct DR_TPAGE *null; // $a2
	/* end block 1 */
	// End offset: 0x00016114
	// End Line: 676

	/* begin block 2 */
		// Start line: 2036
	/* end block 2 */
	// End Line: 2037

	/* begin block 3 */
		// Start line: 2045
	/* end block 3 */
	// End Line: 2046

	/* begin block 4 */
		// Start line: 2048
	/* end block 4 */
	// End Line: 2049

// [D] [A] - bugged
void TransparencyOn(void *potz, ushort tpage)
{
	DR_TPAGE *null;
	null = (DR_TPAGE*)current->primptr;
	setDrawTPage(null, 1, 0, tpage);	// [A] might be incorrect

	// original mode:
	//*(char *)((int)puVar2 + 3) = '\x01';
	//puVar2[1] = (uint)tpage & 0x9ff | 0xe1000600;

	addPrim(potz, null);
	current->primptr += sizeof(DR_TPAGE);
}



// decompiled code
// original method signature: 
// void /*$ra*/ UpdateFlashValue()
 // line 687, offset 0x00016114
	/* begin block 1 */
		// Start line: 689
		// Start offset: 0x00016114
		// Variables:
	// 		char size; // $v1
	/* end block 1 */
	// End offset: 0x00016184
	// End Line: 700

	/* begin block 2 */
		// Start line: 2076
	/* end block 2 */
	// End Line: 2077

	/* begin block 3 */
		// Start line: 2088
	/* end block 3 */
	// End Line: 2089

	/* begin block 4 */
		// Start line: 2089
	/* end block 4 */
	// End Line: 2090

	/* begin block 5 */
		// Start line: 2091
	/* end block 5 */
	// End Line: 2092

/* WARNING: Unknown calling convention yet parameter storage is locked */

void UpdateFlashValue(void)
{
	int iVar1;
	int iVar2;
	uint uVar3;

	iVar2 = CameraCnt;

	if (gShowMap != 0) 
		iVar2 = FrameCnt;

	iVar1 = iVar2;

	uVar3 = iVar2 - (iVar1 >> 4) * 16 & 0xff;
	OverlayFlashValue = uVar3;

	if (7 < uVar3) 
		OverlayFlashValue = 16 - OverlayFlashValue;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawDrivingGameOverlays()
 // line 707, offset 0x000157f4
	/* begin block 1 */
		// Start line: 709
		// Start offset: 0x000157F4
		// Variables:
	// 		struct SCORE_ENTRY *table; // $s1
	// 		char string[32]; // stack offset -64
	// 		int i; // $s1
	// 		int x; // $s3
	// 		int y; // $s2

		/* begin block 1.1 */
			// Start line: 718
			// Start offset: 0x0001585C

			/* begin block 1.1.1 */
				// Start line: 732
				// Start offset: 0x000158D4
			/* end block 1.1.1 */
			// End offset: 0x000158D4
			// End Line: 732

			/* begin block 1.1.2 */
				// Start line: 757
				// Start offset: 0x000159E4
			/* end block 1.1.2 */
			// End offset: 0x00015AA8
			// End Line: 770
		/* end block 1.1 */
		// End offset: 0x00015E4C
		// End Line: 843
	/* end block 1 */
	// End offset: 0x00015E70
	// End Line: 844

	/* begin block 2 */
		// Start line: 1543
	/* end block 2 */
	// End Line: 1544

	/* begin block 3 */
		// Start line: 1622
	/* end block 3 */
	// End Line: 1623

	/* begin block 4 */
		// Start line: 1623
	/* end block 4 */
	// End Line: 1624

	/* begin block 5 */
		// Start line: 1628
	/* end block 5 */
	// End Line: 1629

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D]
void DrawDrivingGameOverlays(void)
{
	int iVar1;
	int iVar2;
	SCORE_ENTRY* table;
	int y;
	int y_00;
	char string[32];

	SetTextColour(128, 128, 64);

	switch (GameType) 
	{
		case GAME_GETAWAY:
			iVar1 = PrintString("Best: ", 0x10, 0x3c);
			PrintScoreTableTime(iVar1 + 3, 0x3c, ScoreTables.GetawayTable[GameLevel][gSubGameNumber][0].time);
			break;
		case GAME_GATERACE:

			if (NumPlayers != 1) 
			{
				y = PrintString("Gate:", 0x10, 0x24);
				sprintf(string, "%d / %d", gPlayerScore.items, 100);
				PrintString(string, y + 3, 0x24);
				y = PrintString("Gate:", 0x10, 0x96);
				sprintf(string, "%d / %d", gPlayerScore.P2items, 100);
			LAB_00015b28:
				PrintString(string, y + 3, 0x96);
				return;
			}

			
			table = &ScoreTables.GateRaceTable[GameLevel][gSubGameNumber][0];
			PrintStringRightAligned("Gate:", 0x10e, 0x10);
			sprintf(string, "%d / %d", gPlayerScore.items, 100);
			PrintString(string, 0x111, 0x10);
			y = PrintString("Best:", 0x10, 0x24);
			PrintScoreTableTime(y + 3, 0x24, table->time);
			y = PrintString("Gate:", 0x10, 0x34);

			if (table->items == -1)
				goto LAB_00015c00;

		LAB_00015c20:
			sprintf(string, "%d", table->items);
			goto LAB_00015c2c;

		case GAME_CHECKPOINT:

			if (NumPlayers != 1) 
			{
				y = PrintString("Checks", 0x10, 0x24);
				sprintf(string, "%d/5", gPlayerScore.items);
				PrintString(string, y + 3, 0x24);
				y = PrintString("Checks", 0x10, 0x96);
				sprintf(string, "%d/5", gPlayerScore.P2items);
				goto LAB_00015b28;
			}

			table = &ScoreTables.CheckpointTable[GameLevel][gSubGameNumber][0];
			PrintStringRightAligned("Checks", 0x10e, 0x10);
			sprintf(string, "%d/5", gPlayerScore.items);
			PrintString(string, 0x111, 0x10);

			goto LAB_00015c88;
		case GAME_TRAILBLAZER:
			
			table = &ScoreTables.TrailblazerTable[GameLevel][gSubGameNumber][0];
			PrintStringRightAligned("Cones:", 0xfa, 0x10);
			sprintf(string, "%d / %d", gPlayerScore.items, 100);
			PrintString(string, 0xfd, 0x10);
			y = PrintString("Best", 0x10, 0x24);
			PrintScoreTableTime(y + 3, 0x24, table->time);
			y = PrintString("Cones:", 0x10, 0x34);

			if (table->items != -1)
				goto LAB_00015c20;

		LAB_00015c00:
			sprintf(string, "-");
		LAB_00015c2c:
			PrintString(string, y + 3, 0x34);
			break;
		case GAME_SURVIVAL:
			table = &ScoreTables.SurvivalTable[GameLevel][gSubGameNumber][0];
		LAB_00015c88:
			y = PrintString("Best:", 0x10, 0x24);
			PrintScoreTableTime(y + 3, 0x24, table->time);
			break;
		case GAME_CAPTURETHEFLAG:
			y = PrintString("Flags:", 0x10, 0x10);
			sprintf(string, "%d", gPlayerScore.items);
			PrintString(string, y + 3, 0x10);
			y = PrintString("Flags:", 0x10, 0x84);
			sprintf(string, "%d", gPlayerScore.P2items);
			PrintString(string, y + 3, 0x84);
			break;
		case GAME_SECRET:
			y_00 = 0x24;
			y = 0;
			if (0 < gNumRaceTrackLaps)
			{
				do {
					iVar2 = y + 1;
					sprintf(string, "%s %d:", "Lap", iVar2);
					iVar1 = PrintString(string, 0x10, y_00);
					PrintScoreTableTime(iVar1 + 3, y_00, gLapTimes[0][y]);
					y = iVar2;
					y_00 = y_00 + 0x10;
				} while (iVar2 < gNumRaceTrackLaps);
			}

			y = 0x96;
			if ((1 < NumPlayers) && (y_00 = 0, 0 < gNumRaceTrackLaps))
			{
				do {
					iVar2 = y_00 + 1;
					sprintf(string, "%s %d:", "Lap", iVar2);
					iVar1 = PrintString(string, 0x10, y);
					PrintScoreTableTime(iVar1 + 3, y, gLapTimes[1][y_00]);
					y_00 = iVar2;
					y = y + 0x10;
				} while (iVar2 < gNumRaceTrackLaps);
			}
			break;
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ PrintScoreTableTime(int x /*$s0*/, int y /*$s1*/, int time /*$a0*/)
 // line 846, offset 0x00016184
	/* begin block 1 */
		// Start line: 847
		// Start offset: 0x00016184
		// Variables:
	// 		char string[32]; // stack offset -48
	// 		int min; // $t0
	// 		int frac; // $v1
	/* end block 1 */
	// End offset: 0x00016280
	// End Line: 861

	/* begin block 2 */
		// Start line: 2259
	/* end block 2 */
	// End Line: 2260

	/* begin block 3 */
		// Start line: 2406
	/* end block 3 */
	// End Line: 2407

// [D]
void PrintScoreTableTime(int x, int y, int time)
{
	char string[32];

	if (time == -1) 
		sprintf(string, "-:--.--");
	else
		sprintf(string, "%d:%02d.%02d", time / 180000, time / 3000 - (time / 180000) * 60, (time % 3000) / 30);

	PrintString(string, x, y);
}





