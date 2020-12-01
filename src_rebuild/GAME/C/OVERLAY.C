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
#include "FELONY.H"
#include "SCORES.H"

COLOUR_BAND felonyColour[3] =
{
  { { 0, 0, 255, 0 }, 0, 0 },
  { { 255, 0, 0, 0 }, 659, 0 },
  { { 0, 0, 255, 0 }, 4096, 2 }
};

COLOUR_BAND playerDamageColour[3] =
{
  { { 0, 255, 0, 0 }, 0, 0 },
  { { 255, 0, 0, 0 }, 3686, 0 },
  { { 0, 0, 0, 0 }, 4096, 2 }
};

COLOUR_BAND damageColour[2] =
{
	{ { 0, 255, 0, 0 }, 0, 0 },
	{ { 255, 0, 0, 0 }, 4096, 0 }
};

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

PERCENTAGE_BAR PlayerDamageBar;
PERCENTAGE_BAR Player2DamageBar;
PERCENTAGE_BAR DamageBar;
PERCENTAGE_BAR FelonyBar;
PERCENTAGE_BAR ProxyBar;

int gDoOverlays = 1;
int gWidescreenOverlayAlign = 0; // [A] custom widescreen alignment by PSX hack

#define PERCENTAGE_BAR_WIDTH 102
#define PERCENTAGE_BAR_HEIGHT 10

// [A]
int gOverlayXPos = 16;
int gOverlayXOppPos = 208;

// [D] [T]
void InitOverlays(void)
{
	gDoOverlays = 1;

	// [A] init defaults
	gOverlayXPos = 16;
	gOverlayXOppPos = 208;
	gMapXOffset = 249;
	gMapYOffset = 181;

	InitPercentageBar(&PlayerDamageBar, MaxPlayerDamage[0], playerDamageColour, "Damage");

	PlayerDamageBar.xpos = gOverlayXPos;
	PlayerDamageBar.ypos = 24;

	PlayerDamageBar.active = 1;

	if (NumPlayers > 1)
	{
		InitPercentageBar(&Player2DamageBar, MaxPlayerDamage[1], playerDamageColour, "Damage");
		Player2DamageBar.xpos = gOverlayXPos;
		Player2DamageBar.ypos = 140;
		Player2DamageBar.active = 1;
	}
	else
	{
		Player2DamageBar.active = 0;
	}

	InitPercentageBar(&FelonyBar, 4096, felonyColour, "Felony");
	FelonyBar.xpos = gOverlayXPos;
	FelonyBar.ypos = 46;
	FelonyBar.active = 0;

	InitPercentageBar(&DamageBar, 1, damageColour, "Damage");
	DamageBar.xpos = gOverlayXOppPos;
	DamageBar.ypos = 24;
	DamageBar.flags = 1;
	DamageBar.active = 0;

	InitPercentageBar(&ProxyBar, TAIL_TOOFAR - TAIL_TOOCLOSE, felonyColour, "Proximity");
	ProxyBar.xpos = gOverlayXPos;
	ProxyBar.ypos = 46;
	ProxyBar.active = 0;

	InitOverheadMap();

	if (GameType == GAME_CAPTURETHEFLAG)
	{
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

// [D] [T]
void DisplayOverlays(void)
{
	short *felony;

	if (NoPlayerControl != 0 || gInGameCutsceneActive != 0 || gInGameCutsceneDelay != 0)
		return;

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

#ifndef PSX
		if(gWidescreenOverlayAlign)
		{
			// align to PSX-mapped screen coordinates
			RECT16 emuViewport;
			Emulator_GetPSXWidescreenMappedViewport(&emuViewport);

			// recalc pos
			gOverlayXPos = 16 + emuViewport.x;
			gOverlayXOppPos = emuViewport.w - 16 - PERCENTAGE_BAR_WIDTH;
			gMapXOffset = emuViewport.w - 16 - MAP_SIZE_W;

			// set up
			PlayerDamageBar.xpos = gOverlayXPos;
			Player2DamageBar.xpos = gOverlayXPos;
			FelonyBar.xpos = gOverlayXPos;
			DamageBar.xpos = gOverlayXOppPos;
			ProxyBar.xpos = gOverlayXPos;
		}
#endif

		DrawPercentageBar(&PlayerDamageBar);
		DrawPercentageBar(&Player2DamageBar);
		DrawPercentageBar(&DamageBar);
		DrawPercentageBar(&FelonyBar);

		DrawDrivingGameOverlays();			
		DrawOverheadMap();

		if (CopsCanSeePlayer)
		{
			if (player[0].playerCarId < 0)
				felony = &pedestrianFelony;
			else 
				felony = &car_data[player[0].playerCarId].felonyRating;

			if (*felony > FELONY_MIN_VALUE) 
				DrawCopIndicators();
		}
	}
	else 
	{
		FastForward = 1;
		DrawFullscreenMap();
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
	// 		DRAWENV drawenv; // stack offset -104
	// 		DR_ENV *dr_env; // $s0
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

// [D] [T]
void SetFullscreenDrawing(void)
{
	DR_ENV *drenv;
	DRAWENV drawenv;

	drenv = (DR_ENV *)current->primptr;

	drawenv.clip.x = 256;
	SetDefDrawEnv(&drawenv, 0, current->draw.clip.y & 256, 320, 256);

	SetDrawEnv(drenv, &drawenv);

	addPrim(current->ot + 8, drenv);
	current->primptr += sizeof(DR_ENV);
}



// decompiled code
// original method signature: 
// void /*$ra*/ InitPercentageBar(PERCENTAGE_BAR *bar /*$a0*/, int size /*$a1*/, COLOUR_BAND *pColourBand /*$a2*/, char *tag /*$a3*/)
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

// [D] [T]
void InitPercentageBar(PERCENTAGE_BAR *bar, int size, COLOUR_BAND *pColourBand, char *tag)
{
	bar->xpos = 150;
	bar->ypos = 10;
	bar->width = PERCENTAGE_BAR_WIDTH;
	bar->height = PERCENTAGE_BAR_HEIGHT;
	bar->position = 0;
	bar->max = size;
	bar->pColourBand = pColourBand;
	bar->flags = 0;
	bar->tag = tag;
	bar->active = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ EnablePercentageBar(PERCENTAGE_BAR *bar /*$a0*/, int max /*$a1*/)
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

// [D] [T]
void EnablePercentageBar(PERCENTAGE_BAR *bar, int max)
{
	bar->position = 0;
	bar->max = max;
	bar->active = 1;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawPercentageBar(PERCENTAGE_BAR *bar /*$fp*/)
 // line 426, offset 0x00014da8
	/* begin block 1 */
		// Start line: 427
		// Start offset: 0x00014DA8
		// Variables:
	// 		POLY_G4 *poly; // $s0
	// 		CVECTOR temp; // stack offset -56
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

// [D] [T]
void DrawPercentageBar(PERCENTAGE_BAR *bar)
{
	POLY_G4 *poly;
	POLY_G4 *poly2;
	int min_x;
	int max_x;
	int min_y;
	int max_y;
	CVECTOR temp;

	if (bar->active == 0)
		return;

	if (bar->max < bar->position) 
	{
		bar->position = bar->max;
	}

	if (bar->max == 0) 
	{
		min_x = bar->xpos;
		max_x = min_x;
	}
	else 
	{
		if (bar->flags & 1) 
		{
			max_x = bar->xpos + bar->width;
			min_x = max_x - ((bar->width * bar->position) / bar->max);
		}
		else 
		{
			min_x = bar->xpos;
			max_x = min_x + ((bar->width * bar->position) / bar->max);
		}
	}

	min_y = bar->ypos;
	max_y = bar->ypos + bar->height;

	// draw the colour band that fills the bar
	if ((bar->flags & 2) == 0) 
	{
		poly = (POLY_G4 *)current->primptr;
		setPolyG4(poly);

		SetColourByValue(bar->pColourBand, (bar->position * 4096) / bar->max, &temp);

		poly->r0 = temp.r;
		poly->g0 = temp.g;
		poly->b0 = temp.b;
	
		poly->r1 = temp.r;
		poly->g1 = temp.g;
		poly->b1 = temp.b;
		
		temp.r = temp.r / 4;
		temp.g = temp.g / 4;
		temp.b = temp.b / 4;
		
		poly->r2 = temp.r;
		poly->g2 = temp.g;
		poly->b2 = temp.b;
		poly->r3 = temp.r;
		poly->g3 = temp.g;
		poly->x0 = min_x;
		poly->y0 = min_y;
		poly->x1 = max_x;
		poly->y1 = min_y;
		poly->b3 = temp.b;
		poly->x2 = min_x;
		poly->x3 = max_x;
		poly->y2 = max_y;
		poly->y3 = max_y;

		addPrim((u_long*)(current->ot + 1), poly);
		current->primptr += sizeof(POLY_G4);
	}

	// draw transparent part
	min_x = bar->xpos;
	max_x = bar->xpos + bar->width;

	poly2 = (POLY_G4 *)current->primptr;

	setPolyG4(poly2);
	setSemiTrans(poly2,1);
	poly2->x0 = min_x;
	poly2->x2 = min_x;
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
	poly2->y0 = min_y;
	poly2->x1 = max_x;
	poly2->y1 = min_y;
	poly2->x3 = max_x;
	poly2->y2 = max_y;
	poly2->y3 = max_y;

	addPrim((u_long*)(current->ot+1), poly2);
	current->primptr += sizeof(POLY_G4);

	// draw contours
	LINE_F4* lineF4 = (LINE_F4*)current->primptr;
	setLineF4(lineF4);
	lineF4->r0 = 80;
	lineF4->g0 = 80;
	lineF4->b0 = 80;

	lineF4->x0 = min_x - 1;
	lineF4->y0 = min_y - 1;

	lineF4->x1 = max_x;
	lineF4->y1 = min_y - 1;

	lineF4->x2 = max_x;
	lineF4->x3 = min_x - 1;

	lineF4->y2 = max_y;
	lineF4->y3 = max_y;

	addPrim((u_long*)(current->ot + 1), lineF4);
	current->primptr += sizeof(LINE_F4);
		
	LINE_F2* lineF2 = (LINE_F2*)current->primptr;
	setLineF2(lineF2);
	lineF2->r0 = 80;
	lineF2->g0 = 80;
	lineF2->b0 = 80;

	lineF2->x0 = min_x - 1;
	lineF2->y0 = min_y - 1;

	lineF2->x1 = min_x - 1;
	lineF2->y1 = max_y;

	addPrim((u_long*)(current->ot + 1), lineF2);
	current->primptr += sizeof(LINE_F2);

	TransparencyOn(current->ot + 1, 0x20);

	if (bar->tag != NULL)
	{
		SetTextColour(128, 128, 64);

		if ((bar->flags & 1U) == 0)
			PrintString(bar->tag, min_x + 8, min_y - 11);
		else
			PrintStringRightAligned(bar->tag, max_x - 8, min_y - 11);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawProximityBar(PERCENTAGE_BAR *bar /*$t3*/)
 // line 532, offset 0x000152d4
	/* begin block 1 */
		// Start line: 533
		// Start offset: 0x000152D4
		// Variables:
	// 		TILE *tile; // $a1
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

// [D] [T]
void DrawProximityBar(PERCENTAGE_BAR *bar)
{
	TILE *tile;
	short total;
	int min_x;
	int max_x;
	int min_y;
	int max_y;
	int half_width;
	
	if (bar->active == 0)
		return;

	total = bar->position;
	
	if (total < TAIL_TOOCLOSE)
		total = TAIL_TOOCLOSE;
	
	if (total > TAIL_TOOFAR)
		total = TAIL_TOOFAR;

	min_x = bar->xpos;
	max_x = bar->xpos + bar->width;

	min_y = bar->ypos;
	max_y = bar->ypos + bar->height;

	half_width = bar->width / 2;

	tile = (TILE *)current->primptr;
	setTile(tile);
	tile->r0 = 16;
	tile->g0 = 16;
	tile->b0 = 16;

	tile->x0 = ((bar->width * (total - TAIL_TOOCLOSE)) / (TAIL_TOOFAR - TAIL_TOOCLOSE) - 1) + min_x;
	tile->w = 2;
	tile->y0 = min_y;
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

	poly2->x0 = min_x;
	poly2->y0 = min_y;
	poly2->x1 = min_x + half_width;
	poly2->y1 = min_y;
	poly2->x2 = min_x;
	poly2->y2 = max_y;
	poly2->x3 = min_x + half_width;
	poly2->y3 = max_y;

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

	poly2->x0 = min_x + half_width;
	poly2->y0 = min_y;
	poly2->x1 = max_x;
	poly2->y1 = min_y;
	poly2->x2 = min_x + half_width;
	poly2->y2 = max_y;
	poly2->x3 = max_x;
	poly2->y3 = max_y;

	addPrim(current->ot + 1, poly2);
	current->primptr += sizeof(POLY_G4);

	LINE_F4* lineF4 = (LINE_F4*)current->primptr;
	setLineF4(lineF4);
	lineF4->r0 = 80;
	lineF4->g0 = 80;
	lineF4->b0 = 80;

	lineF4->x0 = min_x - 1;
	lineF4->y0 = min_y - 1;

	lineF4->x1 = max_x;
	lineF4->y1 = min_y - 1;

	lineF4->x2 = max_x;
	lineF4->x3 = min_x - 1;

	lineF4->y2 = max_y;
	lineF4->y3 = max_y;

	addPrim((u_long*)(current->ot + 1), lineF4);
	current->primptr += sizeof(LINE_F4);

	LINE_F2* lineF2 = (LINE_F2*)current->primptr;
	setLineF2(lineF2);
	lineF2->r0 = 80;
	lineF2->g0 = 80;
	lineF2->b0 = 80;

	lineF2->x0 = min_x - 1;
	lineF2->y0 = min_y - 1;

	lineF2->x1 = min_x - 1;
	lineF2->y1 = max_y;

	addPrim((u_long*)(current->ot + 1), lineF2);
	current->primptr += sizeof(LINE_F2);

	TransparencyOn(current->ot + 1, 0x20);

	if (bar->tag != NULL)
	{
		SetTextColour(128, 128, 64);

		if ((bar->flags & 1U) == 0)
			PrintString(bar->tag, min_x + 8, min_y - 11);
		else 
			PrintStringRightAligned(bar->tag, max_x - 8, min_y - 11);
	}
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetColourByValue(COLOUR_BAND *pColourBand /*$a3*/, int value /*$a1*/, CVECTOR *pOut /*$t0*/)
 // line 631, offset 0x00015f6c
	/* begin block 1 */
		// Start line: 632
		// Start offset: 0x00015F6C
		// Variables:
	// 		COLOUR_BAND *pPrevColourBand; // $a2
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

// [D] [T]
void SetColourByValue(COLOUR_BAND *pColourBand, int value, CVECTOR *pOut)
{
	COLOUR_BAND *pPrevColourBand;

	int temp;
	int scale;
	int inv;

	pPrevColourBand = pColourBand + 1;
	while (pPrevColourBand->value < value)
	{
		pColourBand++;
		pPrevColourBand++;
	}

	if (pPrevColourBand->flags == 2)
		scale = pColourBand->value + OverlayFlashValue * (pPrevColourBand->value - pColourBand->value) / 8;
	else
		scale = value;

	temp = ((scale - pColourBand->value) * 0x1000) / (pPrevColourBand->value - pColourBand->value);

	inv = 4096 - temp;

	pOut->r = FIXED(inv * pColourBand->colour.r + temp * pPrevColourBand->colour.r);
	pOut->g = FIXED(inv * pColourBand->colour.g + temp * pPrevColourBand->colour.g);
	pOut->b = FIXED(inv * pColourBand->colour.b + temp * pPrevColourBand->colour.b);
}



// decompiled code
// original method signature: 
// void /*$ra*/ TransparencyOn(void *potz /*$a0*/, unsigned short tpage /*$a1*/)
 // line 669, offset 0x00016098
	/* begin block 1 */
		// Start line: 670
		// Start offset: 0x00016098
		// Variables:
	// 		DR_TPAGE *null; // $a2
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

// [D] [T]
void TransparencyOn(void *potz, ushort tpage)
{
	DR_TPAGE *null;
	null = (DR_TPAGE*)current->primptr;
	setDrawTPage(null, 1, 0, tpage);

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

// [D] [T]
void UpdateFlashValue(void)
{
	int size;
	int flash;

	if (gShowMap != 0) 
		size = FrameCnt;
	else
		size = CameraCnt;
 
	flash = size % 16;

	if (flash > 7) 
		flash = 16 - flash;
	
	OverlayFlashValue = flash;
}



// decompiled code
// original method signature: 
// void /*$ra*/ DrawDrivingGameOverlays()
 // line 707, offset 0x000157f4
	/* begin block 1 */
		// Start line: 709
		// Start offset: 0x000157F4
		// Variables:
	// 		SCORE_ENTRY *table; // $s1
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

// [D] [T]
void DrawDrivingGameOverlays(void)
{
	SCORE_ENTRY* table;
	int x;
	int i;
	int y;
	char string[32];

	SetTextColour(128, 128, 64);

	switch (GameType) 
	{
		case GAME_GETAWAY:
			table = &ScoreTables.GetawayTable[GameLevel][gSubGameNumber][0];

			x = PrintString("Best: ", gOverlayXPos, 60);
			PrintScoreTableTime(x + 3, 60, table->time);
			break;
		case GAME_GATERACE:

			if (NumPlayers == 1) 
			{
				table = &ScoreTables.GateRaceTable[GameLevel][gSubGameNumber][0];
				x = PrintStringRightAligned("Gate:", gOverlayXOppPos + 50, 16);

				sprintf(string, "%d / %d", gPlayerScore.items, 100);
				PrintString(string, x + 3, 16);

				x = PrintString("Best:", gOverlayXPos, 36);
				PrintScoreTableTime(x + 3, 36, table->time);

				x = PrintString("Gate:", gOverlayXPos, 52);

				if (table->items == -1)
					sprintf(string, "-");
				else
					sprintf(string, "%d", table->items);

				PrintString(string, x + 3, 52);
			}
			else
			{
				x = PrintString("Gate:", gOverlayXPos, 36);
				sprintf(string, "%d / %d", gPlayerScore.items, 100);
				
				PrintString(string, x + 3, 36);
				x = PrintString("Gate:", gOverlayXPos, 150);
				
				sprintf(string, "%d / %d", gPlayerScore.P2items, 100);
				PrintString(string, x + 3, 150);
			}
			break;
		case GAME_CHECKPOINT:

			if (NumPlayers > 1) 
			{
				x = PrintString("Checks", gOverlayXPos, 36);
				
				sprintf(string, "%d/5", gPlayerScore.items);
				PrintString(string, x + 3, 36);
				
				x = PrintString("Checks", gOverlayXPos, 150);
				
				sprintf(string, "%d/5", gPlayerScore.P2items);
				PrintString(string, x + 3, 150);
			}
			else
			{
				table = &ScoreTables.CheckpointTable[GameLevel][gSubGameNumber][0];
				x = PrintStringRightAligned("Checks", gOverlayXOppPos + 70, 16);

				sprintf(string, "%d/5", gPlayerScore.items);
				PrintString(string, x + 3, 16);

				x = PrintString("Best:", gOverlayXPos, 36);
				PrintScoreTableTime(x + 3, 36, table->time);
			}
		
			break;
		case GAME_TRAILBLAZER:
			
			table = &ScoreTables.TrailblazerTable[GameLevel][gSubGameNumber][0];
			x = PrintStringRightAligned("Cones:", gOverlayXOppPos + 55, 16);
		
			sprintf(string, "%d / %d", gPlayerScore.items, 100);
			PrintString(string, x + 3, 16);
		
			x = PrintString("Best", gOverlayXPos, 36);
			PrintScoreTableTime(x + 3, 36, table->time);
			x = PrintString("Cones:", gOverlayXPos, 52);

			if (table->items != -1)
				sprintf(string, "%d", table->items);
			else
				sprintf(string, "-");
			
			PrintString(string, x + 3, 52);
		
			break;
		case GAME_SURVIVAL:
			table = &ScoreTables.SurvivalTable[GameLevel][gSubGameNumber][0];
			x = PrintString("Best:", gOverlayXPos, 36);
			PrintScoreTableTime(x + 3, 36, table->time);
			break;
		case GAME_CAPTURETHEFLAG:
			x = PrintString("Flags:", gOverlayXPos, 16);
			sprintf(string, "%d", gPlayerScore.items);
			PrintString(string, x + 3, 16);
		
			x = PrintString("Flags:", gOverlayXPos, 132);
			sprintf(string, "%d", gPlayerScore.P2items);
			PrintString(string, x + 3, 132);
			break;
		case GAME_SECRET:
			y = 36;

			i = 0;
			do
			{
				sprintf(string, "%s %d:", "Lap", i+1);
				
				x = PrintString(string, gOverlayXPos, y);
				PrintScoreTableTime(x + 3, y, gLapTimes[0][i]);
				
				y += 16;
				i++;
			} while (i < gNumRaceTrackLaps);

		
			if (NumPlayers > 1)
			{
				y = 150;
				
				i = 0;
				do
				{
					sprintf(string, "%s %d:", "Lap", i+1);

					x = PrintString(string, gOverlayXPos, y);
					PrintScoreTableTime(x + 3, y, gLapTimes[1][i]);

					y += 16;
					i++;
				} while (i < gNumRaceTrackLaps);
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

// [D] [T]
void PrintScoreTableTime(int x, int y, int time)
{
	char string[32];

	if (time == -1) 
		sprintf(string, "-:--.--");
	else
		sprintf(string, "%d:%02d.%02d", time / 180000, time / 3000 - (time / 180000) * 60, (time % 3000) / 30);

	PrintString(string, x, y);
}





