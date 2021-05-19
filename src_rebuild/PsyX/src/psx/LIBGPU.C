#include "psx/libgte.h"
#include "psx/libgpu.h"
#include "psx/libetc.h"

#include "../gpu/PsyX_GPU.h"
#include "PsyX/PsyX_render.h"
#include "PsyX/PsyX_public.h"

#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "PsyX/PsyX_globals.h"
#include "../PsyX_main.h"
//#include "../gpu/font.h"

//#define DEBUG_POLY_COUNT

#if defined(DEBUG_POLY_COUNT)
static int polygon_count = 0;
#endif

void(*drawsync_callback)(void) = NULL;

int ClearImage(RECT16* rect, u_char r, u_char g, u_char b)
{
	GR_ClearVRAM(rect->x, rect->y, rect->w, rect->h, r, g, b);

	// TODO: clear all affected backbuffers
	GR_Clear(rect->x, rect->y, rect->w, rect->h, r, g, b);
	return 0;
}

int ClearImage2(RECT16* rect, u_char r, u_char g, u_char b)
{
	GR_ClearVRAM(rect->x, rect->y, rect->w, rect->h, r, g, b);

	// TODO: clear all affected backbuffers
	GR_Clear(rect->x, rect->y, rect->w, rect->h, r, g, b);
	return 0;
}

int DrawSync(int mode)
{
	// Update VRAM seems needed to be here
	GR_UpdateVRAM();
	GR_ReadFramebufferDataToVRAM();

	if (g_splitIndex > 0)// && g_GPUDisabledState == 0) // don't do flips if nothing to draw.
	{
		DrawAllSplits();
		//PsyX_EndScene();
	}

	if (drawsync_callback != NULL)
	{
		drawsync_callback();
	}

	return 0;
}

int LoadImagePSX(RECT16* rect, u_long* p)
{
	GR_CopyVRAM((unsigned short*)p, 0, 0, rect->w, rect->h, rect->x, rect->y);
	return 0;
}

int LoadImage(RECT16* rect, u_long* p)
{
	LoadImagePSX(rect, p);	
	return 0;
}

int LoadImage2(RECT16* rect, u_long* p)
{
	LoadImagePSX(rect, p);

	// simulate immediate mode
	GR_UpdateVRAM();
	GR_ReadFramebufferDataToVRAM();
	
	return 0;
}

int MargePrim(void* p0, void* p1)
{
#if 0
	int v0 = ((unsigned char*)p0)[3];
	int v1 = ((unsigned char*)p1)[3];

	v0 += v1;
	v1 = v0 + 1;

	if (v1 < 0x11)
	{
		((char*)p0)[3] = v1;
		((int*)p1)[0] = 0;
		return 0;
	}

	return -1;
#endif //0

#if defined(USE_EXTENDED_PRIM_POINTERS)
	int v0 = ((int*)p0)[1];
	int v1 = ((int*)p1)[1];
#else
	int v0 = ((unsigned char*)p0)[3];
	int v1 = ((unsigned char*)p1)[3];
#endif

	v0 += v1;
	v1 = v0 + 1;

#if defined(USE_EXTENDED_PRIM_POINTERS)
	if (v1 < 0x12)
#else
	if (v1 < 0x11)
#endif
	{
#if defined(USE_EXTENDED_PRIM_POINTERS)
		((int*)p0)[1] = v1;
		((int*)p1)[1] = 0;
#else
		((char*)p0)[3] = v1;
		((int*)p1)[0] = 0;
#endif

		return 0;
	}

	return -1;
}

int MoveImage(RECT16* rect, int x, int y)
{
	GR_CopyVRAM(NULL, rect->x, rect->y, rect->w, rect->h, x, y);
	return 0;
}

int ResetGraph(int mode)
{
	if(mode == 0)
	{
		// reset GPU state
		g_GPUDisabledState = 0;
		ClearImage(&activeDrawEnv.clip, 0, 0, 0);

		ClearSplits();
#ifdef USE_PGXP
		PGXP_ClearCache();
#endif

		PsyX_EndScene();
	}
	else if (mode == 1)
	{
		// cancell all rendering
		ClearSplits();
#ifdef USE_PGXP
		PGXP_ClearCache();
#endif
	
		PsyX_EndScene();
	}
	else if (mode == 3)
	{

	}

	return 0;
}

int SetGraphDebug(int level)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int StoreImage(RECT16* rect, u_long* p)
{
	GR_ReadVRAM((unsigned short*)p, rect->x, rect->y, rect->w, rect->h);
	return 0;
}

int StoreImage2(RECT16 *RECT16, u_long *p)
{
	int result = StoreImage(RECT16, p);
	// GPU reset?

	return result;
}


u_long* ClearOTag(u_long* ot, int n)
{
	if (n == 0)
		return NULL;

	// last is  aspecial terminator
	setaddr(&ot[n - P_LEN], &prim_terminator);
	setlen(&ot[n - P_LEN], 0);

	// make a linked list with it's next items
	for (int i = (n-1) * P_LEN; i >= 0; i -= P_LEN)
	{
		setaddr(&ot[i], &ot[i + P_LEN]);
		setlen(&ot[i], 0);
	}

	return NULL;
}

u_long* ClearOTagR(u_long* ot, int n)
{
	if (n == 0)
		return NULL;

	// first is a special terminator
	setaddr(ot, &prim_terminator);
	setlen(ot, 0);

	// initialize a linked list with it's previous items
	for (int i = 1 * P_LEN; i < n * P_LEN; i += P_LEN)
	{
		setaddr(&ot[i], &ot[i - P_LEN]);
		setlen(&ot[i], 0);
	}

	return NULL;
}

void SetDispMask(int mask)
{
	g_GPUDisabledState = (mask == 0);
}

int FntPrint(char* text, ...)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int GetODE(void)
{
	return 0;
}

DISPENV* GetDispEnv(DISPENV* env)//(F)
{
	memcpy(env, &activeDispEnv, sizeof(DISPENV));
	return env;
}

DISPENV* PutDispEnv(DISPENV* env)//To Finish
{
	memcpy((char*)&activeDispEnv, env, sizeof(DISPENV));
	return 0;
}

DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h)//(F)
{
	env->disp.x = x;
	env->disp.y = y;
	env->disp.w = w;
	env->disp.h = h;

	env->screen.x = 0;
	env->screen.y = 0;
	env->screen.w = 0;
	env->screen.h = 0;

	env->isrgb24 = 0;
	env->isinter = 0;

	env->pad1 = 0;
	env->pad0 = 0;
	
	return 0;
}

DRAWENV* GetDrawEnv(DRAWENV* env)
{
	PSYX_UNIMPLEMENTED();
	return NULL;
}

DRAWENV* PutDrawEnv(DRAWENV* env)//Guessed
{
	memcpy((char*)&activeDrawEnv, env, sizeof(DRAWENV));
	return 0;
}

DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h)//(F)
{
	env->clip.x = x;
	env->clip.y = y;
	env->clip.w = w;
	env->clip.h = h;

	env->tw.x = 0;
	env->tw.y = 0;
	env->tw.w = 0;
	env->tw.h = 0;
	env->r0 = 0;
	env->g0 = 0;
	env->b0 = 0;
	env->dtd = 1;

	if (GetVideoMode() == MODE_NTSC)
		env->dfe = h < 289 ? 1 : 0;
	else
		env->dfe = h < 257 ? 1 : 0;

	env->ofs[0] = x;
	env->ofs[1] = y;

	env->tpage = 10;
	env->isbg = 0;

	return env;
}

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env)
{
	dr_env->code[0] = ((env->clip.y & 0x3FF) << 10) | env->clip.x & 0x3FF | 0xE3000000;
	dr_env->code[1] = (((env->clip.y + env->clip.h - 1) & 0x3FF) << 10) | (env->clip.x + env->clip.w - 1) & 0x3FF | 0xE4000000;
	dr_env->code[2] = ((env->ofs[1] & 0x3FF) << 11) | env->ofs[0] & 0x7FF | 0xE5000000;
	dr_env->code[3] = 32 * (((256 - env->tw.h) >> 3) & 0x1F) | ((256 - env->tw.w) >> 3) & 0x1F | (((env->tw.y >> 3) & 0x1F) << 15) | (((env->tw.x >> 3) & 0x1F) << 10) | 0xE2000000;
	dr_env->code[4] = ((env->dtd != 0) << 9) | ((env->dfe != 0) << 10) | env->tpage & 0x1FF | 0xE1000000;

	// TODO: add missing logic when env->isbg != 0
	
	setlen(dr_env, 5);
}

void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT16* tw)
{
	setDrawMode(p, dfe, dtd, tpage, tw);
}

void SetDrawArea(DR_AREA *p, RECT16 *r)
{
	p->code[0] = (r->x & 0x3FF | ((r->y & 0x3FF) << 10)) | 0xE3000000;
	p->code[1] = (((r->x + r->w) & 0x3FF) | (((r->y + r->h) & 0x3FF) << 10)) | 0xE4000000;

	setlen(p, 2);
}

void SetDrawMove(DR_MOVE* p, RECT16* rect, int x, int y)
{
	char len;

	len = 5;

	if (rect->w == 0 || rect->h == 0)
		len = 0;

	p->code[0] = 0x1000000;
	p->code[1] = 0x80000000;
	p->code[2] = *(ulong*)&rect->x;
	p->code[3] = y << 0x10 | x & 0xffffU;
	p->code[4] = *(ulong *)&rect->w;

	setlen(p, len);
}

void SetDrawLoad(DR_LOAD* p, RECT16* RECT16)
{
	setDrawLoad(p, RECT16);
}

void SetDrawTPage(DR_TPAGE* p, int dfe, int dtd, int tpage)
{
	setDrawTPage(p, dfe, dtd, tpage);
}

u_long DrawSyncCallback(void(*func)(void))
{
	drawsync_callback = func;
	return 0;
}

u_short GetClut(int x, int y)
{
	return getClut(x, y);
}
//------------------------------------------------------------------

void DrawOTagEnv(u_long* p, DRAWENV* env)
{
	PutDrawEnv(env);
	DrawOTag(p);
}

void DrawOTag(u_long* p)
{
	do
	{
		if (g_GPUDisabledState)
		{
			ClearSplits();
#ifdef USE_PGXP
			PGXP_ClearCache();
#endif
			return;
		}

		if (PsyX_BeginScene())
		{
			ClearSplits();
		}

#if defined(DEBUG_POLY_COUNT)
		polygon_count = 0;
#endif

		if (activeDrawEnv.isbg)
			ClearImage(&activeDrawEnv.clip, activeDrawEnv.r0, activeDrawEnv.g0, activeDrawEnv.b0);

		ParsePrimitivesToSplits(p, 0);

		DrawAllSplits();
	} while (g_emulatorPaused);
}

void DrawPrim(void* p)
{
	if (g_GPUDisabledState)
	{
		ClearSplits();
#ifdef USE_PGXP
		PGXP_ClearCache();
#endif
		return;
	}

	if (PsyX_BeginScene())
	{
		ClearSplits();
	}

#if defined(DEBUG_POLY_COUNT)
	polygon_count = 0;
#endif

	if (activeDrawEnv.isbg)
		ClearImage(&activeDrawEnv.clip, activeDrawEnv.r0, activeDrawEnv.g0, activeDrawEnv.b0);

	ParsePrimitivesToSplits((u_long*)p, 1);
}

void SetSprt16(SPRT_16* p)
{
	setSprt16(p);
}

void SetSprt8(SPRT_8* p)
{
	setSprt8(p);
}

void SetTile(TILE* p)
{
	setTile(p);
}

void SetPolyGT4(POLY_GT4* p)
{
	setPolyGT4(p);
}

void SetSemiTrans(void* p, int abe)
{
	setSemiTrans(p, abe);
}

void SetShadeTex(void* p, int tge)
{
	setShadeTex(p, tge);
}

void SetSprt(SPRT* p)
{
	setSprt(p);
}

void SetDumpFnt(int id)
{
	PSYX_UNIMPLEMENTED();
}

void SetLineF3(LINE_F3* p)
{
	setLineF3(p);
}

void FntLoad(int tx, int ty)
{
	PSYX_UNIMPLEMENTED();
	/*
	g_debugFntClut = LoadClut2((u_long*)fontClutData, tx, ty + 0x80);
	g_debugFontTpage = LoadTPage((u_long*)fontTpageData, 0, 0, tx, ty, 0x80, 0x20);
	idx = 0;
	memset(&fontTiles, 0, 0x180);*/
}

void AddPrim(void* ot, void* p)
{
	addPrim(ot, p);
}

void AddPrims(void* ot, void* p0, void* p1)
{
	addPrims(ot, p0, p1);
}

void CatPrim(void* p0, void* p1)
{
	catPrim(p0, p1);
}

u_short LoadTPage(u_long* pix, int tp, int abr, int x, int y, int w, int h)
{
	RECT16 imageArea;
	imageArea.x = x;
	imageArea.y = y;
	imageArea.h = h;

	enum
	{
		TP_4BIT,
		TP_8BIT,
		TP_16BIT
	};

	switch (tp)
	{
	case TP_4BIT:
	{
		//loc_278
		if (w >= 0)
		{
			imageArea.w = w >> 2;
		}
		else
		{
			imageArea.w = (w + 3) >> 2;
		}
		break;
	}
	case TP_8BIT:
	{
		//loc_290
		imageArea.w = (w + (w >> 31)) >> 1;
		break;
	}
	case TP_16BIT:
	{
		//loc_2A4
		imageArea.w = w;
		break;
	}
	}

	//loc_2AC
	LoadImagePSX(&imageArea, pix);
	return GetTPage(tp, abr, x, y) & 0xFFFF;
}

u_short GetTPage(int tp, int abr, int x, int y)
{
	return getTPage(tp, abr, x, y);
}

u_short LoadClut(u_long* clut, int x, int y)
{
	RECT16 rect;//&var_18
	setRECT(&rect, x, y, 256, 1);
	LoadImagePSX(&rect, clut);
	return GetClut(x, y) & 0xFFFF;
}

u_short LoadClut2(u_long* clut, int x, int y)
{
	RECT16 drawArea;
	drawArea.x = x;
	drawArea.y = y;
	drawArea.w = 16;
	drawArea.h = 1;

	LoadImagePSX(&drawArea, clut);

	return getClut(x, y);
}

u_long* KanjiFntFlush(int id)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

u_long* FntFlush(int id)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int KanjiFntOpen(int x, int y, int w, int h, int dx, int dy, int cx, int cy, int isbg, int n)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

int FntOpen(int x, int y, int w, int h, int isbg, int n)
{
	PSYX_UNIMPLEMENTED();
	return 0;
}

void SetPolyF4(POLY_F4* p)
{
	setPolyF4(p);
}

void SetPolyFT4(POLY_FT4* p)
{
	setPolyFT4(p);
}

void SetPolyG4(POLY_G4* p)
{
	setPolyG4(p);
}

void TermPrim(void* p)
{
	termPrim(p);
}

void SetPsyXTexture(DR_PSYX_TEX* p, uint grTextureId)
{
	setlen(p, 1);
	p->code[0] = 0xB1000000 | grTextureId;
}
