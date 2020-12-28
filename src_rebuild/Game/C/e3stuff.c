#include "driver2.h"
#include "E3stuff.h"

#include "pad.h"
#include "system.h"
#include "pres.h"
#include "pause.h"
#include "sound.h"

#include "LIBETC.H"

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

	draw.dfe = 1;
	
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
		PsyX_EndScene();
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
	draw.dfe = 1;

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
		PsyX_EndScene();
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
	draw.dfe = 1;

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
		PsyX_EndScene();
#endif

		col -= 4;
	} while (col > -4);


	DrawSync(0);

	setRECT16(&rect, 0, 0, 640, 512);
	ClearImage2(&rect, 0, 0, 0);
	DrawSync(0);
}

// [D] [T]
void SetupDefDrawEnv(DRAWENV *env, int x, int y, int w, int h)
{
	if (h < 257)
		SetDefDrawEnv(env, x, y, w, 256);
	else
		SetDefDrawEnv(env, x, y, w, 512);
}

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
	PsyX_BeginScene();
	SetDispMask(1);
#endif

	gShowMap = 1;
	SetTextColour(128, 128, 128);
	PrintStringCentred(G_LTXT(GTXT_PleaseWait),128);
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

	PsyX_EndScene();
#endif // PSX
	
}

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
		PsyX_EndScene();
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





