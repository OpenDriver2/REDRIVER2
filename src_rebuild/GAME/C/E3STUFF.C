#include "DRIVER2.H"
#include "E3STUFF.H"

#include "PAD.H"
#include "LIBETC.H"
#include "SYSTEM.H"
#include "PRES.H"
#include "PAUSE.H"
#include "SOUND.H"

struct POLYCOORD
{
	short x;
	short y;
	short u;
	short v;
	short w;
	short h;
};

POLYCOORD polycoords[6] =
{
  { 0, 0, 640, 0, 256, 256 },
  { 256, 0, 768, 0, 256, 256 },
  { 512, 0, 896, 0, 128, 256 },
  { 0, 256, 640, 256, 256, 256 },
  { 256, 256, 768, 256, 256, 256 },
  { 512, 256, 896, 256, 128, 256 }
};

// decompiled code
// original method signature: 
// void /*$ra*/ ShowHiresScreens(char **names /*$s1*/, int delay /*$s4*/, int wait /*$s3*/)
 // line 139, offset 0x00044ce0
	/* begin block 1 */
		// Start line: 140
		// Start offset: 0x00044CE0
		// Variables:
	// 		char *filename; // $a0
	// 		int timedelay; // $s0
	/* end block 1 */
	// End offset: 0x00044DA0
	// End Line: 164

	/* begin block 2 */
		// Start line: 278
	/* end block 2 */
	// End Line: 279

// [D] [T]
void ShowHiresScreens(char **names, int delay, int wait)
{
	int timedelay;
	char *filename;

	filename = *names;

	do {
		if (!filename) 
			return;

		FadeInHiresScreen(filename);

		timedelay = delay-1;

		do {
			if (timedelay == 0)
				break;

			VSync(0);

			ReadControllers();
			timedelay--;

		} while ((wait != 0) || (Pads[0].dirnew & 0x40) == 0);

		FadeOutHiresScreen();

		filename = *(++names);
	} while (true);
}


// decompiled code
// original method signature: 
// void /*$ra*/ FadeInHiresScreen(char *filename /*stack 0*/)
 // line 171, offset 0x00044244
	/* begin block 1 */
		// Start line: 172
		// Start offset: 0x00044244
		// Variables:
	// 		DISPENV disp; // stack offset -488
	// 		DRAWENV draw; // stack offset -464
	// 		SPRT prims[6]; // stack offset -368
	// 		POLY_FT3 nulls[6]; // stack offset -248
	// 		RECT rect; // stack offset -56
	// 		unsigned long ot; // stack offset -48
	// 		int i; // $t5
	// 		int col; // $s1
	/* end block 1 */
	// End offset: 0x000445F4
	// End Line: 251

	/* begin block 2 */
		// Start line: 302
	/* end block 2 */
	// End Line: 303

	/* begin block 3 */
		// Start line: 342
	/* end block 3 */
	// End Line: 343


// [D] [T]
void FadeInHiresScreen(char *filename)
{
	int col;
	
	DISPENV disp;
	DRAWENV draw;
	SPRT prims[6];
	POLY_FT3 nulls[6];
	RECT16 rect;
	OTTYPE ot;

	POLY_FT3 *poly;
	SPRT *prim;
	POLYCOORD *pc;

	DrawSync(0);
	VSync(0);
	SetDispMask(0);
	ResetGraph(3);

	setRECT16(&rect, 0, 0, 512, 512);
	ClearImage2(&rect, 0, 0, 0);
	DrawSync(0);

	setRECT16(&rect, 512, 0, 512, 512);
	ClearImage2(&rect, 0, 0, 0);
	DrawSync(0);

	poly = nulls;
	pc = polycoords;

	prim = prims;

	// prepare polygons
	for(int i = 0; i < 6; i++)
	{
		// set primitive
		setSprt(prim);
		setUV0(prim, 0, 0);

		setClut(prim, 640, 511);

		setXY0(prim, pc->x, pc->y);
		setWH(prim, pc->w, pc->h);

		// set poly
		setPolyFT3(poly);
		setXY3(poly, -1,-1,-1,-1,-1,-1);

		setTPage(poly, 1, 0, pc->u, pc->v);

		prim++;
		poly++;
		pc++;
	}

	SetupDefDrawEnv(&draw, 0, 0, 640, 512);
	SetupDefDispEnv(&disp, 0, 0, 640, 512);
	VSync(0);
	PutDispEnv(&disp);
	PutDrawEnv(&draw);

	LoadfileSeg(filename, _overlay_buffer, 20, 0x4ff80);
	LoadClut((u_long*)_overlay_buffer, 640, 511);

	DrawSync(0);
	setRECT16(&rect, 640, 0, 320, 511);

	LoadImage(&rect, (u_long*)&_overlay_buffer[524]);

	DrawSync(0);
	SetDispMask(1);

	col = 0;

	do {
		DrawSync(0);
		VSync(0);
		PutDispEnv(&disp);
		PutDrawEnv(&draw);
		ClearOTagR((u_long*)&ot, 1);
		
		poly = nulls;
		prim = prims;

		for (int i = 0; i < 6; i++)
		{
			if (col < 129) 
			{
				setRGB0(prim, col, col, col);
			}
			else 
			{
				setRGB0(prim, 128, 128, 128);
			}

			addPrim(&ot, prim);
			addPrim(&ot, poly);
			poly++; prim++;
		}

		DrawOTag((u_long*)&ot);

#ifndef PSX
		Emulator_EndScene();
#endif

		col += 4;
	} while (col < 140);

	DrawSync(0);
}

#define GALLERY_IMAGES 24

// [A] displays bonus gallery
void ShowBonusGallery()
{
	char filename[64];
	int currentImage;

	DISPENV disp;
	DRAWENV draw;
	SPRT prims[6];
	POLY_FT3 nulls[6];
	RECT16 rect;
	OTTYPE ot;

	POLY_FT3 *poly;
	SPRT *prim;
	POLYCOORD *pc;

	DrawSync(0);
	VSync(0);
	SetDispMask(0);
	ResetGraph(3);

	setRECT16(&rect, 0, 0, 512, 512);
	ClearImage2(&rect, 0, 0, 0);
	DrawSync(0);

	setRECT16(&rect, 512, 0, 512, 512);
	ClearImage2(&rect, 0, 0, 0);
	DrawSync(0);

	poly = nulls;
	pc = polycoords;

	prim = prims;

	// prepare polygons
	for(int i = 0; i < 6; i++)
	{
		// set primitive
		setSprt(prim);
		setUV0(prim, 0, 0);

		setClut(prim, 640, 511);

		setXY0(prim, pc->x, pc->y);
		setWH(prim, pc->w, pc->h);

		// set poly
		setPolyFT3(poly);
		setXY3(poly, -1,-1,-1,-1,-1,-1);

		setTPage(poly, 1, 0, pc->u, pc->v);

		prim++;
		poly++;
		pc++;
	}

	SetupDefDrawEnv(&draw, 0, 0, 640, 512);
	SetupDefDispEnv(&disp, 0, 0, 640, 512);
	VSync(0);
	PutDispEnv(&disp);
	PutDrawEnv(&draw);

	currentImage = 0;

	// draw image cycle
	while(currentImage <= GALLERY_IMAGES)
	{
		if(currentImage == 0)
			sprintf(filename, "GFX\\GAL\\INTRO.TIM");
		else
			sprintf(filename, "GFX\\GAL\\IMG%d.TIM", currentImage-1);
		
		LoadfileSeg(filename, _other_buffer, 20, 0x4ff80);
		LoadClut((u_long*)_other_buffer, 640, 511);

		DrawSync(0);
		setRECT16(&rect, 640, 0, 320, 511);

		LoadImage(&rect, (u_long*)&_other_buffer[524]);

		DrawSync(0);
		SetDispMask(1);

		// now draw image
		DrawSync(0);
		VSync(0);

		PutDispEnv(&disp);
		PutDrawEnv(&draw);

		ClearOTagR((u_long*)&ot, 1);

		poly = nulls;
		prim = prims;

		for (int i = 0; i < 6; i++)
		{
			setRGB0(prim, 128, 128, 128);

			addPrim(&ot, prim);
			addPrim(&ot, poly);
			poly++; prim++;
		}

		DrawOTag((u_long*)&ot);

#ifndef PSX
		Emulator_EndScene();
#endif

		// wait for user input
		do {
			ReadControllers();
			VSync(-1);

			if(Pads[0].dirnew & 0x8000)
			{
				currentImage--;
				if (currentImage < 0)
				{
					FESound(1);
					currentImage = 0;
				}
				else
				{
					FESound(3);
					break;
				}
			}

			if(Pads[0].dirnew & 0x2000)
			{
				FESound(3);
				currentImage++;
				break;
			}

			if(Pads[0].dirnew & 0x10)
			{
				FESound(0);
				currentImage = GALLERY_IMAGES+1; // quit
				break;
			}
		} while (true);
	}

	DrawSync(0);
}


// decompiled code
// original method signature: 
// void /*$ra*/ FadeOutHiresScreen()
 // line 258, offset 0x000445f4
	/* begin block 1 */
		// Start line: 260
		// Start offset: 0x000445F4
		// Variables:
	// 		DISPENV disp; // stack offset -496
	// 		DRAWENV draw; // stack offset -472
	// 		SPRT prims[6]; // stack offset -376
	// 		POLY_FT3 nulls[6]; // stack offset -256
	// 		RECT rect; // stack offset -64
	// 		unsigned long ot; // stack offset -56
	// 		int i; // $t5
	// 		int col; // $s1
	/* end block 1 */
	// End offset: 0x000448CC
	// End Line: 318

	/* begin block 2 */
		// Start line: 662
	/* end block 2 */
	// End Line: 663

	/* begin block 3 */
		// Start line: 670
	/* end block 3 */
	// End Line: 671

	/* begin block 4 */
		// Start line: 671
	/* end block 4 */
	// End Line: 672

	/* begin block 5 */
		// Start line: 680
	/* end block 5 */
	// End Line: 681

/* WARNING: Unknown calling convention yet parameter storage is locked */

// [D] [T]
void FadeOutHiresScreen(void)
{
	int col;

	DISPENV disp;
	DRAWENV draw;
	SPRT prims[6];
	POLY_FT3 nulls[6];
	RECT16 rect;
	OTTYPE ot;

	POLY_FT3 *poly;
	SPRT *prim;
	POLYCOORD *pc;

	poly = nulls;
	pc = polycoords;

	prim = prims;

	// prepare polygons
	for (int i = 0; i < 6; i++)
	{
		// set primitive
		setSprt(prim);
		setUV0(prim, 0, 0);

		setClut(prim, 640, 511);

		setXY0(prim, pc->x, pc->y);
		setWH(prim, pc->w, pc->h);

		// set poly
		setPolyFT3(poly);
		setXY3(poly, -1, -1, -1, -1, -1, -1);

		setTPage(poly, 1, 0, pc->u, pc->v);

		prim++;
		poly++;
		pc++;
	}

	SetupDefDrawEnv(&draw, 0, 0, 640, 512);
	SetupDefDispEnv(&disp, 0, 0, 640, 512);
	VSync(0); 
	PutDispEnv(&disp);
	PutDrawEnv(&draw);

	//g_wireframeMode = 1;

	DrawSync(0);
	SetDispMask(1);

	col = 128;
	do {
		DrawSync(0);
		VSync(0);
		PutDispEnv(&disp);
		PutDrawEnv(&draw);
		ClearOTagR((u_long*)&ot, 1);

		poly = nulls;
		prim = prims;

		for (int i = 0; i < 6; i++)
		{
			setRGB0(prim, col, col, col);

			// UNCERTAIN CODE
			// LEARN TO DECOMPILE MIPS FIRST
			addPrim(&ot, prim);
			addPrim(&ot, poly);
			poly++; prim++;
		}

		DrawOTag((u_long*)&ot);

#ifndef PSX
		Emulator_EndScene();
#endif

		col -= 4;
	} while (col > -4);


	DrawSync(0);

	setRECT16(&rect, 0, 0, 640, 512);
	ClearImage2(&rect, 0, 0, 0);
	DrawSync(0);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDefDrawEnv(DRAWENV *env /*$a0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/)
 // line 325, offset 0x00044e40
	/* begin block 1 */
		// Start line: 650
	/* end block 1 */
	// End Line: 651

// [D] [T]
void SetupDefDrawEnv(DRAWENV *env, int x, int y, int w, int h)
{
	if (h < 257)
		SetDefDrawEnv(env, x, y, w, 256);
	else
		SetDefDrawEnv(env, x, y, w, 512);
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetupDefDispEnv(DISPENV *env /*$s0*/, int x /*$a1*/, int y /*$a2*/, int w /*$a3*/, int h /*stack 16*/)
 // line 350, offset 0x00044da0
	/* begin block 1 */
		// Start line: 1213
	/* end block 1 */
	// End Line: 1214

	/* begin block 2 */
		// Start line: 1400
	/* end block 2 */
	// End Line: 1401

// [D] [T]
void SetupDefDispEnv(DISPENV *env, int x, int y, int w, int h)
{
	if (h < 257) 
	{
		SetDefDispEnv(env, x, y, w, 256);

		env->screen.x = draw_mode.framex;
		env->screen.y = draw_mode.framey;
		env->screen.h = 255;
		env->isinter = 0;
	}
	else
	{
		SetDefDispEnv(env, x, y, w, 512);

		env->screen.x = draw_mode.framex;
		env->screen.y = draw_mode.framey;
		env->screen.h = 255;
		env->isinter = 1;
	}

	env->isrgb24 = 0;
}



// decompiled code
// original method signature: 
// void /*$ra*/ SetPleaseWait(char *buffer /*$s2*/)
 // line 391, offset 0x000448cc
	/* begin block 1 */
		// Start line: 392
		// Start offset: 0x000448CC
		// Variables:
	// 		DISPENV disp; // stack offset -144
	// 		DRAWENV draw; // stack offset -120
	// 		RECT rect; // stack offset -24
	// 		char *exe; // $a0
	/* end block 1 */
	// End offset: 0x00044A40
	// End Line: 435

	/* begin block 2 */
		// Start line: 983
	/* end block 2 */
	// End Line: 984

	/* begin block 3 */
		// Start line: 1057
	/* end block 3 */
	// End Line: 1058

int lastrequesteddisc = 0;

// [D] [T]
void SetPleaseWait(char *buffer)
{
	char *filename;
	DISPENV disp;
	DRAWENV draw;
	RECT16 rect;

	DrawSync(0);
	VSync(0);
	SetDispMask(0);
	SetupDefDrawEnv(&draw,0,0,320,256);
	SetupDefDispEnv(&disp,0,0, 320, 256);

	draw.dfe = 1;

	PutDrawEnv(&draw);
	PutDispEnv(&disp);

	LoadFont(buffer);

	if (buffer == NULL)
		SetupDrawBuffers();
	else
		current->primptr = buffer;

	rect.x = 0;
	rect.y = 0;
	rect.w = 320;
	rect.h = 512;

	ClearImage(&rect,0,0,0);
	DrawSync(0);

#ifndef PSX
	Emulator_BeginScene();
	SetDispMask(1);
#endif

	gShowMap = 1;
	SetTextColour(128, 128, 128);
	PrintStringCentred("Please wait...",128);
	gShowMap = 0;

	VSync(0);
	

#ifdef PSX
	if (lastrequesteddisc == 0)
		filename = "\\SLES_029.96;1";
	else
		filename = "\\SLES_029.96;1";

	if (DiscSwapped(filename) != 4)
		ResetCityType();

#else
	ResetCityType();

	Emulator_EndScene();
#endif // PSX
	
}



// decompiled code
// original method signature: 
// void /*$ra*/ CheckForCorrectDisc(int disc /*$s0*/)
 // line 443, offset 0x00044a40
	/* begin block 1 */
		// Start line: 444
		// Start offset: 0x00044A40
		// Variables:
	// 		DISPENV disp; // stack offset -160
	// 		DRAWENV draw; // stack offset -136
	// 		RECT rect; // stack offset -40
	// 		char *mess1; // $s6
	// 		char *mess2; // $s3
	// 		char *exe; // $s4
	// 		int ret; // $s0
	// 		int discerror; // $s5

		/* begin block 1.1 */
			// Start line: 492
			// Start offset: 0x00044B70
		/* end block 1.1 */
		// End offset: 0x00044BF4
		// End Line: 522
	/* end block 1 */
	// End offset: 0x00044CB8
	// End Line: 538

	/* begin block 2 */
		// Start line: 1162
	/* end block 2 */
	// End Line: 1163

	/* begin block 3 */
		// Start line: 1171
	/* end block 3 */
	// End Line: 1172

	/* begin block 4 */
		// Start line: 1178
	/* end block 4 */
	// End Line: 1179

// [D] [T]
void CheckForCorrectDisc(int disc)
{
	CDTYPE ret;
	char *mess2;
	char *exe;
	int discerror;
	char *mess;
	DISPENV disp;
	DRAWENV draw;
	RECT16 rect;

	discerror = 0;

	if (lastrequesteddisc != disc) 
	{
		lastrequesteddisc = disc;
		ResetCityType();
	}

	if (disc == 0)
	{
		mess = "Please insert DISC 1";
		exe = ".\\SLES_029.96;1";
	}
	else 
	{
		mess = "Please insert DISC 2";
		exe = ".\\SLES_129.96;1";
	}

	if (DiscSwapped(exe) == CDTYPE_CORRECTDISC)
		return;

	LoadFont(NULL);

	SetupDrawBuffers();
	DrawSync(0);
	VSync(0);
	SetDispMask(0);

	rect.x = 0;
	rect.y = 0;
	rect.w = 0x140;
	rect.h = 0x200;

	ClearImage(&rect, 0, 0, 0);
	DrawSync(0);

	SetupDefDrawEnv(&draw, 0, 0, 0x140, 0x100);
	SetupDefDispEnv(&disp, 0, 0, 0x140, 0x100);
	draw.dfe = 1;

	PutDrawEnv(&draw);
	PutDispEnv(&disp);
	SetDispMask(1);

	do {
		VSync(10);

		ret = DiscSwapped(exe);

		switch (ret) 
		{
			case CDTYPE_NODISC:
				discerror = 0;
				mess2 = "No DISC inserted";
				break;
			case CDTYPE_SHELLOPEN:
			case CDTYPE_CORRECTDISC:
				discerror = 0;
				mess2 = "";
				break;
			case CDTYPE_DISCERROR:
				discerror++;

				if (discerror > 29)
					mess2 = "No DISC inserted";
				else
					mess2 = "Checking...";

				break;
			case CDTYPE_WRONGDISC:
				discerror = 0;
				mess2 = "Incorrect DISC inserted";
				break;
		}

		VSync(0);
		rect.y = 0x6e;
		rect.x = 0;
		rect.w = 0x140;
		rect.h = 0x3c;
		
		ClearImage(&rect, 0, 0, 0);
		DrawSync(0);
		gShowMap = 1;

		SetTextColour(128, 128, 128);
		PrintStringCentred(mess, 0x6e);

		SetTextColour(128, 16, 16);
		PrintStringCentred(mess2, 0x8c);

#ifndef PSX
		Emulator_EndScene();
#endif

		gShowMap = 0;
	} while (ret != CDTYPE_CORRECTDISC);

	rect.x = 0;
	rect.y = 0;
	rect.w = 0x140;
	rect.h = 0x200;
	ClearImage(&rect, 0, 0, 0);
	DrawSync(0);
}





