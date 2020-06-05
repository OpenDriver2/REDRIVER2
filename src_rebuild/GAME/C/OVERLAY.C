#include "THISDUST.H"
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

// [D]
void InitOverlays(void)
{
	bool bVar1;

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
	short *psVar1;

	if (((NoPlayerControl == 0) && (gInGameCutsceneActive == 0)) && (gInGameCutsceneDelay == 0))
	{
		if (1 < NumPlayers) 
		{
			if (CurrentPlayerView == 0)
				return;

			SetFullscreenDrawing();
		}

		UpdateFlashValue();

		if (gShowMap == 0)
		{
			DrawPercentageBar(&PlayerDamageBar);
			DrawPercentageBar(&Player2DamageBar);
			DrawPercentageBar(&DamageBar);
			DrawPercentageBar(&FelonyBar);

			DrawDrivingGameOverlays();

			FastForward = 0;
			DrawOverheadMap();

			if (CopsCanSeePlayer != 0)
			{
				if (player[0].playerCarId < 0)
					psVar1 = &pedestrianFelony;
				else 
					psVar1 = &car_data[player[0].playerCarId].felonyRating;

				if (658 < *psVar1) 
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
	char *string;
	short sVar5;
	short uVar6;
	short uVar7;
	int y;
	char *pcVar8;
	short sVar9;
	CVECTOR temp;
	int max_y;

	if (bar->active != 0)
	{
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
				if (bar->max == 0) {
					trap(7);
				}
				sVar9 = sVar5 + (short)((int)((int)bar->width * (uint)bar->position) / (int)(uint)bar->max);
			}
			else 
			{
				sVar9 = bar->xpos + bar->width;
				if (bar->max == 0) {
					trap(7);
				}
				sVar5 = sVar9 - (short)((int)((int)bar->width * (uint)bar->position) / (int)(uint)bar->max);
			}
		}

		sVar1 = bar->ypos;
		sVar3 = sVar1 + bar->height;

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
			poly->y0 = sVar1;
			poly->x1 = sVar9;
			poly->y1 = sVar1;
			poly->b3 = temp.b;
			poly->x2 = sVar5;
			poly->x3 = sVar9;
			poly->y2 = sVar3;
			poly->y3 = sVar3;

			addPrim((u_long*)(current->ot + 1), poly);
			current->primptr += sizeof(POLY_G4);
		}

		sVar5 = bar->xpos;
		sVar9 = sVar5 + bar->width;
		poly2 = (POLY_G4 *)current->primptr;
		setPolyG4(poly2);
		setSemiTrans(poly2,1);
		poly2->x0 = sVar5;
		poly2->x2 = sVar5;
		poly2->code = ':';
		poly2->r0 = '\0';
		poly2->g0 = '\0';
		poly2->b0 = '\0';
		poly2->r1 = '\0';
		poly2->g1 = '\0';
		poly2->b1 = '\0';
		poly2->r2 = 'd';
		poly2->g2 = 'd';
		poly2->b2 = 'd';
		poly2->r3 = 'd';
		poly2->g3 = 'd';
		poly2->b3 = 'd';
		poly2->y0 = sVar1;
		poly2->x1 = sVar9;
		poly2->y1 = sVar1;
		poly2->x3 = sVar9;
		poly2->y2 = sVar3;
		poly2->y3 = sVar3;

		addPrim((u_long*)(current->ot+1), poly2);
		current->primptr += sizeof(POLY_G4);

		LINE_F4* lineF4 = (LINE_F4*)current->primptr;
		setLineF4(lineF4);
		lineF4->r0 = 80;
		lineF4->g0 = 80;
		lineF4->b0 = 80;

		uVar6 = ((uint)(((int)sVar5 + -1) * 0x10000) >> 0x10);
		uVar7 = ((uint)(((int)sVar1 + -1) * 0x10000) >> 0x10);

		lineF4->x0 = uVar6;
		lineF4->y0 = uVar7;

		lineF4->x1 = sVar9;
		lineF4->y1 = uVar7;

		lineF4->x2 = sVar9;
		lineF4->x3 = uVar6;

		lineF4->y2 = sVar3;
		lineF4->y3 = sVar3;

		addPrim((u_long*)(current->ot + 1), lineF4);
		current->primptr += sizeof(LINE_F4);
		
		LINE_F2* lineF2 = (LINE_F2*)current->primptr;
		setLineF2(lineF2);
		lineF2->r0 = 80;
		lineF2->g0 = 80;
		lineF2->b0 = 80;

		lineF2->x0 = uVar6;
		lineF2->y0 = uVar7;

		lineF2->x1 = uVar6;
		lineF2->y1 = sVar3;

		addPrim((u_long*)(current->ot + 1), lineF2);
		current->primptr += sizeof(LINE_F2);

		TransparencyOn(current->ot + 1, 0x20);
		
		string = bar->tag;
		if (string != NULL)
		{
			sVar5 = bar->xpos;
			y = ((bar->ypos - 0xb) * 0x10000) >> 0x10;

			SetTextColour(128, 128, 64);

			if ((bar->flags & 1U) == 0)
				PrintString(string, (int)sVar5 + 8, y);
			else
				PrintStringRightAligned(string, (int)sVar5 + (int)bar->width + -8, y);
		}
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

void DrawProximityBar(_PERCENTAGE_BAR *bar)
{
	UNIMPLEMENTED();
	/*
	short sVar1;
	DB *pDVar2;
	int iVar3;
	int y;
	uint *puVar4;
	char *string;
	short sVar5;
	undefined2 uVar6;
	undefined2 uVar7;
	char *pcVar8;
	short sVar9;
	short sVar10;
	short sVar11;

	if (bar->active != 0) {
		if ((int)(uint)bar->position < TAIL_TOOCLOSE) {
			bar->position = (ushort)TAIL_TOOCLOSE;
		}
		if (TAIL_TOOFAR < (int)(uint)bar->position) {
			bar->position = (ushort)TAIL_TOOFAR;
		}
		sVar1 = bar->width;
		y = (int)(((TAIL_TOOFAR & 0xffffU) - (TAIL_TOOCLOSE & 0xffffU)) * 0x10000) >> 0x10;
		if (y == 0) {
			trap(7);
		}
		iVar3 = (uint)bar->position - TAIL_TOOCLOSE;
		if (y == 0) {
			trap(7);
		}
		puVar4 = (uint *)current->primptr;
		*(char *)((int)puVar4 + 3) = '\x03';
		*(char *)((int)puVar4 + 7) = '`';
		*(char *)(puVar4 + 1) = '\x10';
		*(char *)((int)puVar4 + 5) = '\x10';
		*(char *)((int)puVar4 + 6) = '\x10';
		pDVar2 = current;
		*(short *)(puVar4 + 2) =
			(short)((uint)(((sVar1 * iVar3) / y + -1) * 0x10000) >> 0x10) + bar->xpos;
		sVar1 = bar->ypos;
		*(undefined2 *)(puVar4 + 3) = 2;
		*(short *)((int)puVar4 + 10) = sVar1;
		*(short *)((int)puVar4 + 0xe) = bar->height;
		*puVar4 = *puVar4 & 0xff000000 | pDVar2->ot[1] & 0xffffff;
		pDVar2->ot[1] = pDVar2->ot[1] & 0xff000000 | (uint)puVar4 & 0xffffff;
		string = pDVar2->primptr;
		pDVar2->primptr = string + 0x10;
		sVar1 = bar->xpos;
		sVar10 = bar->ypos;
		sVar9 = bar->width;
		sVar11 = bar->height;
		string[0x13] = '\b';
		string[0x17] = '8';
		string[0x14] = -1;
		string[0x15] = '\0';
		string[0x16] = '\0';
		string[0x1c] = '\0';
		string[0x1d] = -1;
		string[0x1e] = '\0';
		string[0x24] = -1;
		string[0x25] = '\0';
		string[0x26] = '\0';
		string[0x2c] = '\0';
		string[0x2d] = -1;
		string[0x2e] = '\0';
		pDVar2 = current;
		sVar9 = sVar1 + (sVar9 >> 1);
		sVar11 = sVar10 + sVar11;
		*(short *)(string + 0x18) = sVar1;
		*(short *)(string + 0x1a) = sVar10;
		*(short *)(string + 0x20) = sVar9;
		*(short *)(string + 0x22) = sVar10;
		*(short *)(string + 0x28) = sVar1;
		*(short *)(string + 0x2a) = sVar11;
		*(short *)(string + 0x30) = sVar9;
		*(short *)(string + 0x32) = sVar11;
		*(uint *)(string + 0x10) = *(uint *)(string + 0x10) & 0xff000000 | pDVar2->ot[1] & 0xffffff;
		pDVar2->ot[1] = pDVar2->ot[1] & 0xff000000 | (uint)(string + 0x10) & 0xffffff;
		string = pDVar2->primptr;
		pDVar2->primptr = string + 0x24;
		sVar1 = bar->ypos;
		sVar10 = bar->xpos;
		sVar9 = bar->width;
		sVar11 = bar->height;
		string[0x27] = '\b';
		string[0x2b] = '8';
		string[0x28] = '\0';
		string[0x29] = -1;
		string[0x2a] = '\0';
		string[0x30] = -1;
		string[0x31] = '\0';
		string[0x32] = '\0';
		string[0x38] = '\0';
		string[0x39] = -1;
		string[0x3a] = '\0';
		string[0x40] = -1;
		string[0x41] = '\0';
		string[0x42] = '\0';
		pDVar2 = current;
		sVar5 = sVar10 + (sVar9 >> 1);
		sVar10 = sVar10 + sVar9;
		sVar11 = sVar1 + sVar11;
		*(short *)(string + 0x2c) = sVar5;
		*(short *)(string + 0x2e) = sVar1;
		*(short *)(string + 0x34) = sVar10;
		*(short *)(string + 0x36) = sVar1;
		*(short *)(string + 0x3c) = sVar5;
		*(short *)(string + 0x3e) = sVar11;
		*(short *)(string + 0x44) = sVar10;
		*(short *)(string + 0x46) = sVar11;
		*(uint *)(string + 0x24) = *(uint *)(string + 0x24) & 0xff000000 | pDVar2->ot[1] & 0xffffff;
		pDVar2->ot[1] = pDVar2->ot[1] & 0xff000000 | (uint)(string + 0x24) & 0xffffff;
		pcVar8 = pDVar2->primptr;
		string = pcVar8 + 0x24;
		pDVar2->primptr = string;
		sVar10 = bar->xpos;
		sVar9 = sVar10 + bar->width;
		SetLineF4(string);
		pcVar8[0x28] = 'P';
		pcVar8[0x29] = 'P';
		pcVar8[0x2a] = 'P';
		pDVar2 = current;
		uVar6 = (undefined2)((uint)(((int)sVar10 + -1) * 0x10000) >> 0x10);
		*(undefined2 *)(pcVar8 + 0x2c) = uVar6;
		uVar7 = (undefined2)((uint)(((int)sVar1 + -1) * 0x10000) >> 0x10);
		*(undefined2 *)(pcVar8 + 0x2e) = uVar7;
		*(short *)(pcVar8 + 0x30) = sVar9;
		*(undefined2 *)(pcVar8 + 0x32) = uVar7;
		*(short *)(pcVar8 + 0x34) = sVar9;
		*(short *)(pcVar8 + 0x36) = sVar11;
		*(undefined2 *)(pcVar8 + 0x38) = uVar6;
		*(short *)(pcVar8 + 0x3a) = sVar11;
		*(uint *)(pcVar8 + 0x24) = *(uint *)(pcVar8 + 0x24) & 0xff000000 | pDVar2->ot[1] & 0xffffff;
		pDVar2->ot[1] = pDVar2->ot[1] & 0xff000000 | (uint)string & 0xffffff;
		pcVar8 = pDVar2->primptr;
		string = pcVar8 + 0x1c;
		pDVar2->primptr = string;
		SetLineF2(string);
		pcVar8[0x20] = 'P';
		pcVar8[0x21] = 'P';
		pcVar8[0x22] = 'P';
		pDVar2 = current;
		*(undefined2 *)(pcVar8 + 0x24) = uVar6;
		*(undefined2 *)(pcVar8 + 0x26) = uVar7;
		*(undefined2 *)(pcVar8 + 0x28) = uVar6;
		*(short *)(pcVar8 + 0x2a) = sVar11;
		*(uint *)(pcVar8 + 0x1c) = *(uint *)(pcVar8 + 0x1c) & 0xff000000 | pDVar2->ot[1] & 0xffffff;
		pDVar2->ot[1] = pDVar2->ot[1] & 0xff000000 | (uint)string & 0xffffff;
		pDVar2->primptr = pDVar2->primptr + 0x10;
		TransparencyOn(pDVar2->ot + 1, 0x20);
		string = bar->tag;
		if (string != (char *)0x0) {
			sVar1 = bar->xpos;
			y = (int)(((uint)(ushort)bar->ypos - 0xb) * 0x10000) >> 0x10;
			SetTextColour(-0x80, -0x80, '@');
			if ((bar->flags & 1U) == 0) {
				PrintString(string, (int)sVar1 + 8, y);
			}
			else {
				PrintStringRightAligned(string, (int)sVar1 + (int)bar->width + -8, y);
			}
		}
	}
	return;
	*/
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
	setDrawTPage(null, 1, 1, tpage);	// [A] might be incorrect

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

void DrawDrivingGameOverlays(void)
{
	UNIMPLEMENTED();
	/*
	int iVar1;
	int iVar2;
	int *piVar3;
	int y;
	int y_00;
	char acStack64[32];

	SetTextColour(-0x80, -0x80, '@');
	switch (GameType) {
	case GAME_GETAWAY:
		y = GameLevel * 10;
		y_00 = gSubGameNumber * 5;
		iVar1 = PrintString(s_Il_migliore__00010390, 0x10, 0x3c);
		PrintScoreTableTime(iVar1 + 3, 0x3c, ScoreTables.GetawayTable[y_00 + y].time);
		break;
	case GAME_GATERACE:
		if (NumPlayers != 1) {
			y = PrintString(s_Barriere__000103a0, 0x10, 0x24);
			sprintf(acStack64, s__d__d_000aa024, (int)gPlayerScore.items, 100);
			PrintString(acStack64, y + 3, 0x24);
			y = PrintString(s_Barriere__000103a0, 0x10, 0x96);
			sprintf(acStack64, s__d__d_000aa024, (int)gPlayerScore.P2items, 100);
		LAB_00015b28:
			PrintString(acStack64, y + 3, 0x96);
			return;
		}
		piVar3 = (int *)(GameLevel * 0x78 + gSubGameNumber * 0x3c + 0xda278);
		PrintStringRightAligned(s_Barriere__000103a0, 0x10e, 0x10);
		sprintf(acStack64, s__d__d_000aa024, (int)gPlayerScore.items, 100);
		PrintString(acStack64, 0x111, 0x10);
		y = PrintString(s_Il_migliore__00010390, 0x10, 0x24);
		PrintScoreTableTime(y + 3, 0x24, *piVar3);
		y = PrintString(s_Barriere__000103a0, 0x10, 0x34);
		if (*(short *)(piVar3 + 1) == -1) goto LAB_00015c00;
	LAB_00015c20:
		sprintf(acStack64, (char *)&PTR_DAT_000aa030);
		goto LAB_00015c2c;
	case GAME_CHECKPOINT:
		if (NumPlayers != 1) {
			y = PrintString(s_Tappe_000aa014, 0x10, 0x24);
			sprintf(acStack64, &DAT_000aa01c, (int)gPlayerScore.items);
			PrintString(acStack64, y + 3, 0x24);
			y = PrintString(s_Tappe_000aa014, 0x10, 0x96);
			sprintf(acStack64, &DAT_000aa01c, (int)gPlayerScore.P2items);
			goto LAB_00015b28;
		}
		piVar3 = (int *)(GameLevel * 0x78 + gSubGameNumber * 0x3c + 0xda458);
		PrintStringRightAligned(s_Tappe_000aa014, 0x10e, 0x10);
		sprintf(acStack64, &DAT_000aa01c, (int)gPlayerScore.items);
		PrintString(acStack64, 0x111, 0x10);
		goto LAB_00015c88;
	case GAME_TRAILBLAZER:
		piVar3 = (int *)(GameLevel * 0x78 + gSubGameNumber * 0x3c + 0xda638);
		PrintStringRightAligned(s_Coni__000aa034, 0xfa, 0x10);
		sprintf(acStack64, s__d__d_000aa024, (int)gPlayerScore.items, 100);
		PrintString(acStack64, 0xfd, 0x10);
		y = PrintString(s_Il_migliore__00010390, 0x10, 0x24);
		PrintScoreTableTime(y + 3, 0x24, *piVar3);
		y = PrintString(s_Coni__000aa034, 0x10, 0x34);
		if (*(short *)(piVar3 + 1) != -1) goto LAB_00015c20;
	LAB_00015c00:
		sprintf(acStack64, &DAT_000aa02c, 0xffffffff);
	LAB_00015c2c:
		PrintString(acStack64, y + 3, 0x34);
		break;
	case GAME_SURVIVAL:
		piVar3 = (int *)(GameLevel * 0x3c + gSubGameNumber * 0x3c + 0xda818);
	LAB_00015c88:
		y = PrintString(s_Il_migliore__00010390, 0x10, 0x24);
		PrintScoreTableTime(y + 3, 0x24, *piVar3);
		break;
	case GAME_CAPTURETHEFLAG:
		y = PrintString(s_Bandiere__000103ac, 0x10, 0x10);
		sprintf(acStack64, (char *)&PTR_DAT_000aa030, (int)gPlayerScore.items);
		PrintString(acStack64, y + 3, 0x10);
		y = PrintString(s_Bandiere__000103ac, 0x10, 0x84);
		sprintf(acStack64, (char *)&PTR_DAT_000aa030, (int)gPlayerScore.P2items);
		PrintString(acStack64, y + 3, 0x84);
		break;
	case GAME_SECRET:
		y_00 = 0x24;
		y = 0;
		if (0 < gNumRaceTrackLaps) {
			do {
				iVar2 = y + 1;
				sprintf(acStack64, s__s__d__000aa03c, &DAT_000aa044, iVar2);
				iVar1 = PrintString(acStack64, 0x10, y_00);
				PrintScoreTableTime(iVar1 + 3, y_00, (&gLapTimes)[y]);
				y = iVar2;
				y_00 = y_00 + 0x10;
			} while (iVar2 < gNumRaceTrackLaps);
		}
		y = 0x96;
		if ((1 < NumPlayers) && (y_00 = 0, 0 < gNumRaceTrackLaps)) {
			do {
				iVar2 = y_00 + 1;
				sprintf(acStack64, s__s__d__000aa03c, &DAT_000aa044, iVar2);
				iVar1 = PrintString(acStack64, 0x10, y);
				PrintScoreTableTime(iVar1 + 3, y, (&DAT_000d7c64)[y_00]);
				y_00 = iVar2;
				y = y + 0x10;
			} while (iVar2 < gNumRaceTrackLaps);
		}
	}
	return;*/
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

void PrintScoreTableTime(int x, int y, int time)
{
	UNIMPLEMENTED();
	/*
	char acStack48[32];

	if (time == -1) {
		sprintf(acStack48, s_________000aa04c);
	}
	else {
		sprintf(acStack48, &DAT_000103b8, time / 180000, time / 3000 + (time / 180000) * -0x3c,
			(time % 3000) / 0x1e);
	}
	PrintString(acStack48, x, y);
	return;
	*/
}





