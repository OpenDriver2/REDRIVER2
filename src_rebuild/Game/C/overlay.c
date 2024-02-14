#include "driver2.h"
#include "overlay.h"
#include "system.h"
#include "mission.h"
#include "glaunch.h"
#include "main.h"
#include "pause.h"
#include "director.h"
#include "overmap.h"
#include "cop_ai.h"
#include "cutscene.h"
#include "cars.h"
#include "pres.h"
#include "players.h"
#include "camera.h"
#include "felony.h"
#include "scores.h"

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
void PrintScoreTableTime(int x, int y, int time)
{
	char string[32];

	if (time == -1)
		sprintf(string, "-:--.--");
	else
		sprintf(string, "%d:%02d.%02d", time / 180000, time / 3000 - (time / 180000) * 60, (time % 3000) / 30);

	PrintString(string, x, y);
}

// [D] [T]
void InitOverlays(void)
{
	gDoOverlays = 1;

	// [A] init defaults
	gOverlayXPos = 16;
	gOverlayXOppPos = 208;
	gMapXOffset = 249;
	gMapYOffset = 181;

	InitPercentageBar(&PlayerDamageBar, MaxPlayerDamage[0], playerDamageColour, G_LTXT(GTXT_Damage));

	PlayerDamageBar.xpos = gOverlayXPos;
	PlayerDamageBar.ypos = 24;

	PlayerDamageBar.active = 1;

	if (NumPlayers > 1)
	{
		InitPercentageBar(&Player2DamageBar, MaxPlayerDamage[1], playerDamageColour, G_LTXT(GTXT_Damage));
		Player2DamageBar.xpos = gOverlayXPos;
		Player2DamageBar.ypos = SCREEN_H / 2 + 12;
		Player2DamageBar.active = 1;
	}
	else
	{
		Player2DamageBar.active = 0;
	}

	InitPercentageBar(&FelonyBar, 4096, felonyColour, G_LTXT(GTXT_Felony));
	FelonyBar.xpos = gOverlayXPos;
	FelonyBar.ypos = 46;
	FelonyBar.active = 0;

	InitPercentageBar(&DamageBar, 1, damageColour, G_LTXT(GTXT_Damage));
	DamageBar.xpos = gOverlayXOppPos;
	DamageBar.ypos = 24;
	DamageBar.flags = 1;
	DamageBar.active = 0;

	InitPercentageBar(&ProxyBar, TAIL_TOOFAR - TAIL_TOOCLOSE, felonyColour, G_LTXT(GTXT_Proximity));
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

// [D] [T]
void SetFullscreenDrawing(int ofs)
{
	DR_ENV *drenv;
	DRAWENV drawenv;

	drawenv.clip.x = 256;
	SetDefDrawEnv(&drawenv, 0, current->draw.clip.y & 256, 320, 256);

	drenv = (DR_ENV*)current->primptr;
	SetDrawEnv(drenv, &drawenv);
	addPrim(current->ot + ofs, drenv);
	current->primptr += sizeof(DR_ENV);
}

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

// [D] [T]
void EnablePercentageBar(PERCENTAGE_BAR *bar, int max)
{
	bar->position = 0;
	bar->max = max;
	bar->active = 1;
}

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

		addPrim(current->ot + 1, poly);
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

	addPrim(current->ot+1, poly2);
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

	addPrim(current->ot + 1, lineF4);
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

	addPrim(current->ot + 1, lineF2);
	current->primptr += sizeof(LINE_F2);

	TransparencyOn(current->ot + 1, 0x20);

	if (bar->tag != NULL)
	{
		SetTextColour(128, 128, 64);

		if (bar->flags & 0x1)
			PrintStringRightAligned(bar->tag, max_x - 8, min_y - 11);
		else
			PrintString(bar->tag, min_x + 8, min_y - 11);
	}
}

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

	addPrim(current->ot + 1, lineF4);
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

	addPrim(current->ot + 1, lineF2);
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

	temp = ((scale - pColourBand->value) * 4096) / (pPrevColourBand->value - pColourBand->value);

	inv = 4096 - temp;

	pOut->r = FIXED(inv * pColourBand->colour.r + temp * pPrevColourBand->colour.r);
	pOut->g = FIXED(inv * pColourBand->colour.g + temp * pPrevColourBand->colour.g);
	pOut->b = FIXED(inv * pColourBand->colour.b + temp * pPrevColourBand->colour.b);
}

// [D] [T]
void TransparencyOn(void *potz, ushort tpage)
{
	DR_TPAGE *null;
	null = (DR_TPAGE*)current->primptr;
	setDrawTPage(null, 1, 0, tpage);

	addPrim(potz, null);
	current->primptr += sizeof(DR_TPAGE);
}

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

			x = PrintString(G_LTXT(GTXT_Best), gOverlayXPos, 60);
			PrintScoreTableTime(x + 3, 60, table->time);
			break;
		case GAME_CHECKPOINT:

			if (NumPlayers == 1) 
			{
				table = &ScoreTables.CheckpointTable[GameLevel][gSubGameNumber][0];
				x = PrintStringRightAligned(G_LTXT(GTXT_Checks), gOverlayXOppPos + 70, 16);

				sprintf(string, "%d/5", gPlayerScore.items);
				PrintString(string, x + 3, 16);

				x = PrintString(G_LTXT(GTXT_Best), gOverlayXPos, 36);
				PrintScoreTableTime(x + 3, 36, table->time);
			}
			else
			{
				x = PrintString(G_LTXT(GTXT_Checks), gOverlayXPos, 36);

				sprintf(string, "%d/5", gPlayerScore.items);
				PrintString(string, x + 3, 36);

				x = PrintString(G_LTXT(GTXT_Checks), gOverlayXPos, SCREEN_H / 2 + 22);

				sprintf(string, "%d/5", gPlayerScore.P2items);
				PrintString(string, x + 3, SCREEN_H / 2 + 22);
			}
		
			break;
		case GAME_GATERACE:

			if (NumPlayers == 1)
			{
				table = &ScoreTables.GateRaceTable[GameLevel][gSubGameNumber][0];
				x = PrintStringRightAligned(G_LTXT(GTXT_Gate), gOverlayXOppPos + 50, 16);

				sprintf(string, "%d / %d", gPlayerScore.items, 100);
				PrintString(string, x + 3, 16);

				x = PrintString(G_LTXT(GTXT_Best), gOverlayXPos, 36);
				PrintScoreTableTime(x + 3, 36, table->time);

				sprintf(string, table->items != -1 ? "%s: %d" : "%s: -", G_LTXT(GTXT_Gates), table->items);
				PrintString(string, gOverlayXPos, 52);
			}
			else
			{
				x = PrintString(G_LTXT(GTXT_Gate), gOverlayXPos, 36);
				sprintf(string, "%d / %d", gPlayerScore.items, 100);

				PrintString(string, x + 3, 36);
				x = PrintString(G_LTXT(GTXT_Gate), gOverlayXPos, SCREEN_H / 2 + 22);

				sprintf(string, "%d / %d", gPlayerScore.P2items, 100);
				PrintString(string, x + 3, SCREEN_H / 2 + 22);
			}
			break;
		case GAME_TRAILBLAZER:
			
			table = &ScoreTables.TrailblazerTable[GameLevel][gSubGameNumber][0];
			x = PrintStringRightAligned(G_LTXT(GTXT_Cone), gOverlayXOppPos + 55, 16);
		
			sprintf(string, "%d / %d", gPlayerScore.items, 100);
			PrintString(string, x + 3, 16);
		
			x = PrintString(G_LTXT(GTXT_Best), gOverlayXPos, 36);
			PrintScoreTableTime(x + 3, 36, table->time);

			sprintf(string, table->items != -1 ? "%s: %d" : "%s: -", G_LTXT(GTXT_Cones), table->items);
			PrintString(string, gOverlayXPos, 52);

			break;
		case GAME_SURVIVAL:
			table = &ScoreTables.SurvivalTable[GameLevel][gSubGameNumber][0];
			x = PrintString(G_LTXT(GTXT_Best), gOverlayXPos, 36);
			PrintScoreTableTime(x + 3, 36, table->time);
			break;
		case GAME_CAPTURETHEFLAG:
			x = PrintString(G_LTXT(GTXT_Flags), gOverlayXPos, 16);
			sprintf(string, "%d", gPlayerScore.items);
			PrintString(string, x + 3, 16);
		
			x = PrintString(G_LTXT(GTXT_Flags), gOverlayXPos, 132);
			sprintf(string, "%d", gPlayerScore.P2items);
			PrintString(string, x + 3, SCREEN_H / 2 + 4);
			break;
		case GAME_SECRET:
			y = 36;

			for (i = 0; i < gNumRaceTrackLaps; i++)
			{
				sprintf(string, "%s %d:", G_LTXT(GTXT_Lap), i+1);
				
				x = PrintString(string, gOverlayXPos, y);
				PrintScoreTableTime(x + 3, y, gLapTimes[0][i]);
				
				y += 16;
			}

		
			if (NumPlayers > 1)
			{
				y = SCREEN_H / 2 + 22;
				
				for(i = 0; i < gNumRaceTrackLaps; i++)
				{
					sprintf(string, "%s %d:", G_LTXT(GTXT_Lap), i+1);

					x = PrintString(string, gOverlayXPos, y);
					PrintScoreTableTime(x + 3, y, gLapTimes[1][i]);

					y += 16;
				}
			}
			break;
	}
}


// [D] [T]
void DisplayOverlays(void)
{
	short* felony;

#ifndef PSX
	if (gWidescreenOverlayAlign)
	{
		// align to PSX-mapped screen coordinates
		RECT16 emuViewport;
		PsyX_GetPSXWidescreenMappedViewport(&emuViewport);

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

	if (NoPlayerControl || gInGameCutsceneActive || gInGameCutsceneDelay)
		return;

	if (NumPlayers > 1)
	{
		if (CurrentPlayerView == 0)
			return;

		SetFullscreenDrawing(2);
	}

	UpdateFlashValue();

	if (gShowMap == 0)
	{
		FastForward = 0;

		if (!gDoOverlays)
			return;

		if(!gInvincibleCar || ActiveCheats.cheat3)
		{
			DrawPercentageBar(&PlayerDamageBar);
			DrawPercentageBar(&Player2DamageBar);
		}

		if (!gPlayerImmune || ActiveCheats.cheat4)
		{
			DrawPercentageBar(&FelonyBar);
		}

		DrawPercentageBar(&DamageBar);

		DrawDrivingGameOverlays();
		DrawOverheadMap();

		if (CopsCanSeePlayer)
		{
			if (player[0].playerCarId < 0)
				felony = &pedestrianFelony;
			else
				felony = &car_data[player[0].playerCarId].felonyRating;

			if (*felony > FELONY_PURSUIT_MIN_VALUE)
				DrawCopIndicators();
		}
	}
	else
	{
		FastForward = 1;
		DrawFullscreenMap();
	}
}