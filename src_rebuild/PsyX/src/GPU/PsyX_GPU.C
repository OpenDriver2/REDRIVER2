#include "PsyX_GPU.H"

#include "PSYX_PUBLIC.H"
#include "PSYX_GLOBALS.H"
#include "PSYX_RENDER.H"

#include "../PSYX_SETUP.H"

#include <assert.h>
#include <math.h>
#include <string.h>

// Remap a value in the range [A,B] to [C,D].
#define RemapVal( val, A, B, C, D) \
	(C + (D - C) * (val - A) / (B - A))

#define GET_TPAGE_X(tpage)      (((tpage << 6) & 0x7C0) % (VRAM_WIDTH))
#define GET_TPAGE_Y(tpage)      (((((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200))) % (VRAM_HEIGHT))
#define GET_TPAGE_FORMAT(tpage) ((TexFormat)((tpage >> 7) & 0x3))
#define GET_TPAGE_BLEND(tpage)  ((BlendMode)(((tpage >> 5) & 3) + 1))

// TODO
#define GET_TPAGE_DITHER(tpage) 1
//#define GET_TPAGE_DITHER(tpage) 1((tpage >> 9) & 0x1)

#define GET_CLUT_X(clut)        ((clut & 0x3F) << 4)
#define GET_CLUT_Y(clut)        (clut >> 6)

OT_TAG prim_terminator = { -1, 0 }; // P_TAG with zero length

DISPENV activeDispEnv;
DRAWENV activeDrawEnv;
int g_GPUDisabledState = 0;

struct GPUDrawSplit
{
	DRAWENV			drawenv;
	DISPENV			dispenv;

	BlendMode		blendMode;

	TexFormat		texFormat;
	TextureID		textureId;

	u_short			startVertex;
	u_short			numVerts;
};

struct GrVertex g_vertexBuffer[MAX_NUM_POLY_BUFFER_VERTICES];
struct GPUDrawSplit g_splits[MAX_NUM_INDEX_BUFFERS];

int g_vertexIndex = 0;
int g_splitIndex = 0;

void ClearSplits()
{
	g_vertexIndex = 0;
	g_splitIndex = 0;
	g_splits[0].texFormat = (TexFormat)0xFFFF;
}

// remaps screen coordinates to [0..1]
// without clamping
inline void ScreenCoordsToEmulator(GrVertex* vertex, int count)
{
#ifdef USE_PGXP
	float curW;
	float curH;

	if (activeDrawEnv.dfe)
	{
		curW = activeDispEnv.disp.w;
		curH = activeDispEnv.disp.h;
	}
	else
	{
		curW = activeDrawEnv.clip.w;
		curH = activeDrawEnv.clip.h;
	}

	while (count--)
	{
		vertex[count].x = RemapVal(vertex[count].x, 0.0f, curW, 0.0f, 1.0f);
		vertex[count].y = RemapVal(vertex[count].y, 0.0f, curH, 0.0f, 1.0f);
		// FIXME: what about Z?

		// also center
		vertex[count].x -= 0.5f;
		vertex[count].y -= 0.5f;
	}
#endif
}

void LineSwapSourceVerts(VERTTYPE*& p0, VERTTYPE*& p1, unsigned char*& c0, unsigned char*& c1)
{
	// swap line coordinates for left-to-right and up-to-bottom direction
	if ((p0[0] > p1[0]) ||
		(p0[1] > p1[1] && p0[0] == p1[0]))
	{
		VERTTYPE* tmp = p0;
		p0 = p1;
		p1 = tmp;

		unsigned char* tmpCol = c0;
		c0 = c1;
		c1 = tmpCol;
	}
}

void MakeLineArray(struct GrVertex* vertex, VERTTYPE* p0, VERTTYPE* p1, ushort gteidx)
{
	VERTTYPE dx = p1[0] - p0[0];
	VERTTYPE dy = p1[1] - p0[1];

	float ofsX;
	float ofsY;

	if (activeDrawEnv.dfe)
	{
		ofsX = activeDrawEnv.ofs[0] % activeDispEnv.disp.w;
		ofsY = activeDrawEnv.ofs[1] % activeDispEnv.disp.h;
	}
	else
	{
		ofsX = 0.0f;
		ofsY = 0.0f;
	}

	memset(vertex, 0, sizeof(GrVertex) * 4);

	if (dx > abs((short)dy)) { // horizontal
		vertex[0].x = p0[0] + ofsX;
		vertex[0].y = p0[1] + ofsY;

		vertex[1].x = p1[0] + ofsX + 1;
		vertex[1].y = p1[1] + ofsY;

		vertex[2].x = vertex[1].x;
		vertex[2].y = vertex[1].y + 1;

		vertex[3].x = vertex[0].x;
		vertex[3].y = vertex[0].y + 1;
	}
	else { // vertical
		vertex[0].x = p0[0] + ofsX;
		vertex[0].y = p0[1] + ofsY;

		vertex[1].x = p1[0] + ofsX;
		vertex[1].y = p1[1] + ofsY + 1;

		vertex[2].x = vertex[1].x + 1;
		vertex[2].y = vertex[1].y;

		vertex[3].x = vertex[0].x + 1;
		vertex[3].y = vertex[0].y;
	} // TODO diagonal line alignment

#ifdef USE_PGXP
	vertex[0].scr_h = vertex[1].scr_h = vertex[2].scr_h = vertex[3].scr_h = 0.0f;
#endif

	ScreenCoordsToEmulator(vertex, 4);
}

inline void ApplyVertexPGXP(GrVertex* v, VERTTYPE* p, float ofsX, float ofsY, ushort gteidx)
{
#ifdef USE_PGXP
	uint lookup = PGXP_LOOKUP_VALUE(p[0], p[1]);
	PGXPVData vd;
	if (g_pgxpTextureCorrection && PGXP_GetCacheData(vd, lookup, gteidx))
	{
		float gteOfsX = vd.ofx;
		float gteOfsY = vd.ofy;

		// FIXME: it must be clamped strictly to the current draw buffer bounds!
		// this is bad approach but it works for now
		if (gteOfsX > activeDispEnv.disp.w)
			gteOfsX -= activeDispEnv.disp.w;
		gteOfsX -= activeDispEnv.disp.w / 2;

		if (gteOfsY > activeDispEnv.disp.h)
			gteOfsY -= activeDispEnv.disp.h;
		gteOfsY -= activeDispEnv.disp.h / 2;

		v->x = vd.px;
		v->y = vd.py;
		v->z = vd.pz;
		v->ofsX = (ofsX + gteOfsX) / float(activeDispEnv.disp.w) * 2.0f;
		v->ofsY = (ofsY + gteOfsY) / float(activeDispEnv.disp.h) * 2.0f;

		v->scr_h = vd.scr_h;
	}
	else
	{
		v->scr_h = 0.0f;
		v->z = 0.0f;
	}
#endif
}

void MakeVertexTriangle(struct GrVertex* vertex, VERTTYPE* p0, VERTTYPE* p1, VERTTYPE* p2, ushort gteidx)
{
	assert(p0);
	assert(p1);
	assert(p2);

	float ofsX;
	float ofsY;

	if (activeDrawEnv.dfe)
	{
		ofsX = activeDrawEnv.ofs[0] % activeDispEnv.disp.w;
		ofsY = activeDrawEnv.ofs[1] % activeDispEnv.disp.h;
	}
	else
	{
		ofsX = 0.0f;
		ofsY = 0.0f;
	}

	memset(vertex, 0, sizeof(GrVertex) * 3);

	vertex[0].x = p0[0] + ofsX;
	vertex[0].y = p0[1] + ofsY;

	vertex[1].x = p1[0] + ofsX;
	vertex[1].y = p1[1] + ofsY;

	vertex[2].x = p2[0] + ofsX;
	vertex[2].y = p2[1] + ofsY;

	ApplyVertexPGXP(&vertex[0], p0, ofsX, ofsY, gteidx - 2);
	ApplyVertexPGXP(&vertex[1], p1, ofsX, ofsY, gteidx - 1);
	ApplyVertexPGXP(&vertex[2], p2, ofsX, ofsY, gteidx);

	ScreenCoordsToEmulator(vertex, 3);
}

void MakeVertexQuad(struct GrVertex* vertex, VERTTYPE* p0, VERTTYPE* p1, VERTTYPE* p2, VERTTYPE* p3, ushort gteidx)
{
	assert(p0);
	assert(p1);
	assert(p2);
	assert(p3);

	float ofsX;
	float ofsY;

	if (activeDrawEnv.dfe)
	{
		ofsX = activeDrawEnv.ofs[0] % activeDispEnv.disp.w;
		ofsY = activeDrawEnv.ofs[1] % activeDispEnv.disp.h;
	}
	else
	{
		ofsX = 0.0f;
		ofsY = 0.0f;
	}

	memset(vertex, 0, sizeof(GrVertex) * 4);

	vertex[0].x = p0[0] + ofsX;
	vertex[0].y = p0[1] + ofsY;

	vertex[1].x = p1[0] + ofsX;
	vertex[1].y = p1[1] + ofsY;

	vertex[2].x = p2[0] + ofsX;
	vertex[2].y = p2[1] + ofsY;

	vertex[3].x = p3[0] + ofsX;
	vertex[3].y = p3[1] + ofsY;

	ApplyVertexPGXP(&vertex[0], p0, ofsX, ofsY, gteidx - 2);
	ApplyVertexPGXP(&vertex[1], p1, ofsX, ofsY, gteidx - 2);
	ApplyVertexPGXP(&vertex[2], p2, ofsX, ofsY, gteidx - 1);
	ApplyVertexPGXP(&vertex[3], p3, ofsX, ofsY, gteidx);

	ScreenCoordsToEmulator(vertex, 4);
}

void MakeVertexRect(struct GrVertex* vertex, VERTTYPE* p0, short w, short h, ushort gteidx)
{
	assert(p0);

	float ofsX;
	float ofsY;

	if (activeDrawEnv.dfe)
	{
		ofsX = activeDrawEnv.ofs[0] % activeDispEnv.disp.w;
		ofsY = activeDrawEnv.ofs[1] % activeDispEnv.disp.h;
	}
	else
	{
		ofsX = 0.0f;
		ofsY = 0.0f;
	}

	memset(vertex, 0, sizeof(GrVertex) * 4);

	vertex[0].x = p0[0] + ofsX;
	vertex[0].y = p0[1] + ofsY;

	vertex[1].x = vertex[0].x;
	vertex[1].y = vertex[0].y + h;

	vertex[2].x = vertex[0].x + w;
	vertex[2].y = vertex[0].y + h;

	vertex[3].x = vertex[0].x + w;
	vertex[3].y = vertex[0].y;

#ifdef USE_PGXP
	vertex[0].scr_h = vertex[1].scr_h = vertex[2].scr_h = vertex[3].scr_h = 0.0f;
#endif

	ScreenCoordsToEmulator(vertex, 4);
}

void MakeTexcoordQuad(struct GrVertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short page, short clut, unsigned char dither)
{
	assert(uv0);
	assert(uv1);
	assert(uv2);
	assert(uv3);

	const unsigned char bright = 2;

	vertex[0].u = uv0[0];
	vertex[0].v = uv0[1];
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page = page;
	vertex[0].clut = clut;

	vertex[1].u = uv1[0];
	vertex[1].v = uv1[1];
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page = page;
	vertex[1].clut = clut;

	vertex[2].u = uv2[0];
	vertex[2].v = uv2[1];
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page = page;
	vertex[2].clut = clut;

	vertex[3].u = uv3[0];
	vertex[3].v = uv3[1];
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page = page;
	vertex[3].clut = clut;
	/*
	if (g_bilinearFiltering)
	{
		vertex[0].tcx = -1;
		vertex[0].tcy = -1;

		vertex[1].tcx = -1;
		vertex[1].tcy = -1;

		vertex[2].tcx = -1;
		vertex[2].tcy = -1;

		vertex[3].tcx = -1;
		vertex[3].tcy = -1;
	}*/
}

void MakeTexcoordTriangle(struct GrVertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, short page, short clut, unsigned char dither)
{
	assert(uv0);
	assert(uv1);
	assert(uv2);

	const unsigned char bright = 2;

	vertex[0].u = uv0[0];
	vertex[0].v = uv0[1];
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page = page;
	vertex[0].clut = clut;

	vertex[1].u = uv1[0];
	vertex[1].v = uv1[1];
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page = page;
	vertex[1].clut = clut;

	vertex[2].u = uv2[0];
	vertex[2].v = uv2[1];
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page = page;
	vertex[2].clut = clut;
	/*
	if (g_bilinearFiltering)
	{
		vertex[0].tcx = -1;
		vertex[0].tcy = -1;

		vertex[1].tcx = -1;
		vertex[1].tcy = -1;

		vertex[2].tcx = -1;
		vertex[2].tcy = -1;

		vertex[3].tcx = -1;
		vertex[3].tcy = -1;
	}*/
}

void MakeTexcoordRect(struct GrVertex* vertex, unsigned char* uv, short page, short clut, short w, short h)
{
	assert(uv);

	// sim overflow
	if (int(uv[0]) + w > 255) w = 255 - uv[0];
	if (int(uv[1]) + h > 255) h = 255 - uv[1];

	const unsigned char bright = 2;
	const unsigned char dither = 0;

	vertex[0].u = uv[0];
	vertex[0].v = uv[1];
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page = page;
	vertex[0].clut = clut;

	vertex[1].u = uv[0];
	vertex[1].v = uv[1] + h;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page = page;
	vertex[1].clut = clut;

	vertex[2].u = uv[0] + w;
	vertex[2].v = uv[1] + h;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page = page;
	vertex[2].clut = clut;

	vertex[3].u = uv[0] + w;
	vertex[3].v = uv[1];
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page = page;
	vertex[3].clut = clut;

	if (g_bilinearFiltering)
	{
		vertex[0].tcx = -1;
		vertex[0].tcy = -1;

		vertex[1].tcx = -1;
		vertex[1].tcy = -1;

		vertex[2].tcx = -1;
		vertex[2].tcy = -1;

		vertex[3].tcx = -1;
		vertex[3].tcy = -1;
	}
}

void MakeTexcoordLineZero(struct GrVertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u = 0;
	vertex[0].v = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page = 0;
	vertex[0].clut = 0;

	vertex[1].u = 0;
	vertex[1].v = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page = 0;
	vertex[1].clut = 0;

	vertex[2].u = 0;
	vertex[2].v = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page = 0;
	vertex[2].clut = 0;

	vertex[3].u = 0;
	vertex[3].v = 0;
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page = 0;
	vertex[3].clut = 0;
}

void MakeTexcoordTriangleZero(struct GrVertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u = 0;
	vertex[0].v = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page = 0;
	vertex[0].clut = 0;

	vertex[1].u = 0;
	vertex[1].v = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page = 0;
	vertex[1].clut = 0;

	vertex[2].u = 0;
	vertex[2].v = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page = 0;
	vertex[2].clut = 0;

}

void MakeTexcoordQuadZero(struct GrVertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u = 0;
	vertex[0].v = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page = 0;
	vertex[0].clut = 0;

	vertex[1].u = 0;
	vertex[1].v = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page = 0;
	vertex[1].clut = 0;

	vertex[2].u = 0;
	vertex[2].v = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page = 0;
	vertex[2].clut = 0;

	vertex[3].u = 0;
	vertex[3].v = 0;
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page = 0;
	vertex[3].clut = 0;
}

void MakeColourLine(struct GrVertex* vertex, unsigned char* col0, unsigned char* col1)
{
	assert(col0);
	assert(col1);

	vertex[0].r = col0[0];
	vertex[0].g = col0[1];
	vertex[0].b = col0[2];
	vertex[0].a = 255;

	vertex[1].r = col1[0];
	vertex[1].g = col1[1];
	vertex[1].b = col1[2];
	vertex[1].a = 255;

	vertex[2].r = col1[0];
	vertex[2].g = col1[1];
	vertex[2].b = col1[2];
	vertex[2].a = 255;

	vertex[3].r = col0[0];
	vertex[3].g = col0[1];
	vertex[3].b = col0[2];
	vertex[3].a = 255;
}

void MakeColourTriangle(struct GrVertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2)
{
	assert(col0);
	assert(col1);
	assert(col2);

	vertex[0].r = col0[0];
	vertex[0].g = col0[1];
	vertex[0].b = col0[2];
	vertex[0].a = 255;

	vertex[1].r = col1[0];
	vertex[1].g = col1[1];
	vertex[1].b = col1[2];
	vertex[1].a = 255;

	vertex[2].r = col2[0];
	vertex[2].g = col2[1];
	vertex[2].b = col2[2];
	vertex[2].a = 255;
}

void MakeColourQuad(struct GrVertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3)
{
	assert(col0);
	assert(col1);
	assert(col2);
	assert(col3);

	vertex[0].r = col0[0];
	vertex[0].g = col0[1];
	vertex[0].b = col0[2];
	vertex[0].a = 255;

	vertex[1].r = col1[0];
	vertex[1].g = col1[1];
	vertex[1].b = col1[2];
	vertex[1].a = 255;

	vertex[2].r = col2[0];
	vertex[2].g = col2[1];
	vertex[2].b = col2[2];
	vertex[2].a = 255;

	vertex[3].r = col3[0];
	vertex[3].g = col3[1];
	vertex[3].b = col3[2];
	vertex[3].a = 255;
}

void TriangulateQuad()
{
	/*
	Triangulate like this:

	v0--v1
	|  / |
	| /  |
	v2--v3

	NOTE: v2 swapped with v3 during primitive parsing but it not shown here
	*/

	g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 3];

	g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 2];
	g_vertexBuffer[g_vertexIndex + 2] = g_vertexBuffer[g_vertexIndex + 3];
	g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex + 1];
}

//------------------------------------------------------------------------------------------------------------------------

void AddSplit(bool semiTrans, TextureID textureId)
{
	int tpage = activeDrawEnv.tpage;
	GPUDrawSplit& curSplit = g_splits[g_splitIndex];

	BlendMode blendMode = semiTrans ? GET_TPAGE_BLEND(tpage) : BM_NONE;
	TexFormat texFormat = GET_TPAGE_FORMAT(tpage);

	// FIXME: compare drawing environment too?
	if (curSplit.blendMode == blendMode &&
		curSplit.texFormat == texFormat &&
		curSplit.textureId == textureId &&
		curSplit.drawenv.clip.x == activeDrawEnv.clip.x &&
		curSplit.drawenv.clip.y == activeDrawEnv.clip.y &&
		curSplit.drawenv.clip.w == activeDrawEnv.clip.w &&
		curSplit.drawenv.clip.h == activeDrawEnv.clip.h &&
		curSplit.drawenv.dfe == activeDrawEnv.dfe)
	{
		return;
	}

	curSplit.numVerts = g_vertexIndex - curSplit.startVertex;

	GPUDrawSplit& split = g_splits[++g_splitIndex];

	split.blendMode = blendMode;
	split.texFormat = texFormat;
	split.textureId = textureId;
	split.drawenv = activeDrawEnv;
	split.dispenv = activeDispEnv;

	split.startVertex = g_vertexIndex;
	split.numVerts = 0;
}

void DrawSplit(const GPUDrawSplit& split)
{
	GR_SetTexture(split.textureId, split.texFormat);

	GR_SetupClipMode(split.drawenv.clip, split.drawenv.dfe);
	GR_SetOffscreenState(split.drawenv.clip, !split.drawenv.dfe);

	GR_SetBlendMode(split.blendMode);

	GR_DrawTriangles(split.startVertex, split.numVerts / 3);
}

//
// Draws all polygons after AggregatePTAG
//
void DrawAllSplits()
{
	if (g_emulatorPaused)
	{
		for (int i = 0; i < 3; i++)
		{
			struct GrVertex* vert = &g_vertexBuffer[g_polygonSelected + i];
			vert->r = 255;
			vert->g = 0;
			vert->b = 0;

			eprintf("==========================================\n");
			eprintf("POLYGON: %d\n", g_polygonSelected);
#ifdef USE_PGXP
			eprintf("X: %.2f Y: %.2f\n", (float)vert->x, (float)vert->y);
			eprintf("U: %.2f V: %.2f\n", (float)vert->u, (float)vert->v);
			eprintf("TP: %d CLT: %d\n", (int)vert->page, (int)vert->clut);
#else
			eprintf("X: %d Y: %d\n", vert->x, vert->y);
			eprintf("U: %d V: %d\n", vert->u, vert->v);
			eprintf("TP: %d CLT: %d\n", vert->page, vert->clut);
#endif
			
			eprintf("==========================================\n");
		}

		PsyX_UpdateInput();
	}

	// next code ideally should be called before EndScene
	GR_UpdateVertexBuffer(g_vertexBuffer, g_vertexIndex);

	for (int i = 1; i <= g_splitIndex; i++)
		DrawSplit(g_splits[i]);

	ClearSplits();

#ifdef USE_PGXP
	PGXP_ClearCache();
#endif
}

// forward declarations
int ParsePrimitive(uintptr_t primPtr);
int ParseLinkedPrimitiveList(uintptr_t packetStart, uintptr_t packetEnd);

void ParsePrimitivesToSplits(u_long* p, bool singlePrimitive)
{
	if (!p)
		return;

	if (singlePrimitive)
	{
#if defined(USE_PGXP) && defined(USE_EXTENDED_PRIM_POINTERS)
		P_TAG* pTag = (P_TAG*)p;
		pTag->pgxp_index = 0xFFFF;		// force
#endif

		// single primitive
		ParsePrimitive((uintptr_t)p);
		g_splits[g_splitIndex].numVerts = g_vertexIndex - g_splits[g_splitIndex].startVertex;
	}
	else
	{
		P_TAG* pTag = (P_TAG*)p;

		// P_TAG as primitive list
		//do
		while ((uintptr_t)pTag != (uintptr_t)&prim_terminator)
		{
			if (pTag->len > 0)
			{
				uintptr_t packetEnd = (uintptr_t)pTag + (pTag->len + P_LEN) * sizeof(u_long);

				int lastSize = ParseLinkedPrimitiveList((uintptr_t)pTag, packetEnd);
				if (lastSize == -1)
					break; // safe bailout
			}

			pTag = (P_TAG*)pTag->addr;
		}
	}
}

inline int IsNull(POLY_FT3* poly)
{
	return  poly->x0 == -1 &&
		poly->y0 == -1 &&
		poly->x1 == -1 &&
		poly->y1 == -1 &&
		poly->x2 == -1 &&
		poly->y2 == -1;
}

// parses primitive and pushes it to VBO
// returns primitive size
// -1 means invalid primitive
int ParsePrimitive(uintptr_t primPtr)
{
	P_TAG* pTag = (P_TAG*)primPtr;

	bool semi_transparent = (pTag->code & 2) != 0;

#if defined(USE_PGXP) && defined(USE_EXTENDED_PRIM_POINTERS)
	unsigned short gte_index = pTag->pgxp_index;
#else
	unsigned short gte_index = 0xFFFF;
#endif

	switch (pTag->code & ~3)
	{
	case 0x0:
	{
		switch (pTag->code)
		{
			case 0x01:
			{
				DR_MOVE* drmove = (DR_MOVE*)pTag;

				int x, y;
				y = drmove->code[3] >> 0x10 & 0xFFFF;
				x = drmove->code[3] & 0xFFFF;

				RECT16 rect;
				*(ulong*)&rect.x = *(ulong*)&drmove->code[2];
				*(ulong*)&rect.w = *(ulong*)&drmove->code[4];

				MoveImage(&rect, x, y);

				break;
			}
			default:
			{
				eprinterr("Unknown command %02X!\n", pTag->code);
			}
		}


		break;
	}
	case 0x20:
	{
		POLY_F3* poly = (POLY_F3*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		MakeVertexTriangle(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, gte_index);
		MakeTexcoordTriangleZero(&g_vertexBuffer[g_vertexIndex], 0);
		MakeColourTriangle(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0);

		g_vertexIndex += 3;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x24:
	{
		POLY_FT3* poly = (POLY_FT3*)pTag;
		activeDrawEnv.tpage = poly->tpage;

		// It is an official hack from SCE devs to not use DR_TPAGE and instead use null polygon
		if (!IsNull(poly))
		{
			AddSplit(semi_transparent, g_vramTexture);

			MakeVertexTriangle(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, gte_index);
			MakeTexcoordTriangle(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u2, poly->tpage, poly->clut, GET_TPAGE_DITHER(lastTpage));
			MakeColourTriangle(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0);

			g_vertexIndex += 3;

#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
		}

		break;
	}
	case 0x28:
	{
		POLY_F4* poly = (POLY_F4*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		MakeVertexQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, gte_index);
		MakeTexcoordQuadZero(&g_vertexBuffer[g_vertexIndex], 0);
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

		TriangulateQuad();

		g_vertexIndex += 6;
#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x2C:
	{
		POLY_FT4* poly = (POLY_FT4*)pTag;
		activeDrawEnv.tpage = poly->tpage;

		AddSplit(semi_transparent, g_vramTexture);

		MakeVertexQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, gte_index);
		MakeTexcoordQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, poly->tpage, poly->clut, GET_TPAGE_DITHER(lastTpage));
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x30:
	{
		POLY_G3* poly = (POLY_G3*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		MakeVertexTriangle(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, gte_index);
		MakeTexcoordTriangleZero(&g_vertexBuffer[g_vertexIndex], 1);
		MakeColourTriangle(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r2);

		g_vertexIndex += 3;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x34:
	{
		POLY_GT3* poly = (POLY_GT3*)pTag;
		activeDrawEnv.tpage = poly->tpage;

		AddSplit(semi_transparent, g_vramTexture);

		MakeVertexTriangle(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, gte_index);
		MakeTexcoordTriangle(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u2, poly->tpage, poly->clut, GET_TPAGE_DITHER(lastTpage));
		MakeColourTriangle(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r2);

		g_vertexIndex += 3;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x38:
	{
		POLY_G4* poly = (POLY_G4*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		MakeVertexQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, gte_index);
		MakeTexcoordQuadZero(&g_vertexBuffer[g_vertexIndex], 1);
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x3C:
	{
		POLY_GT4* poly = (POLY_GT4*)pTag;
		activeDrawEnv.tpage = poly->tpage;

		AddSplit(semi_transparent, g_vramTexture);

		MakeVertexQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, gte_index);
		MakeTexcoordQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, poly->tpage, poly->clut, GET_TPAGE_DITHER(lastTpage));
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x40:
	{
		LINE_F2* poly = (LINE_F2*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		VERTTYPE* p0 = &poly->x0;
		VERTTYPE* p1 = &poly->x1;
		unsigned char* c0 = &poly->r0;
		unsigned char* c1 = c0;

		LineSwapSourceVerts(p0, p1, c0, c1);
		MakeLineArray(&g_vertexBuffer[g_vertexIndex], p0, p1, gte_index);
		MakeTexcoordLineZero(&g_vertexBuffer[g_vertexIndex], 0);
		MakeColourLine(&g_vertexBuffer[g_vertexIndex], c0, c1);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x48: // TODO (unused)
	{
		LINE_F3* poly = (LINE_F3*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		{
			VERTTYPE* p0 = &poly->x0;
			VERTTYPE* p1 = &poly->x1;
			unsigned char* c0 = &poly->r0;
			unsigned char* c1 = c0;

			LineSwapSourceVerts(p0, p1, c0, c1);
			MakeLineArray(&g_vertexBuffer[g_vertexIndex], p0, p1, gte_index);
			MakeTexcoordLineZero(&g_vertexBuffer[g_vertexIndex], 0);
			MakeColourLine(&g_vertexBuffer[g_vertexIndex], c0, c1);

			TriangulateQuad();

			g_vertexIndex += 6;
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
		}

		{
			VERTTYPE* p0 = &poly->x1;
			VERTTYPE* p1 = &poly->x2;
			unsigned char* c0 = &poly->r0;
			unsigned char* c1 = c0;

			LineSwapSourceVerts(p0, p1, c0, c1);
			MakeLineArray(&g_vertexBuffer[g_vertexIndex], p0, p1, gte_index);
			MakeTexcoordLineZero(&g_vertexBuffer[g_vertexIndex], 0);
			MakeColourLine(&g_vertexBuffer[g_vertexIndex], c0, c1);

			TriangulateQuad();

			g_vertexIndex += 6;
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
		}

		break;
	}
	case 0x4c:
	{
		int i;
		LINE_F4* poly = (LINE_F4*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		{
			VERTTYPE* p0 = &poly->x0;
			VERTTYPE* p1 = &poly->x1;
			unsigned char* c0 = &poly->r0;
			unsigned char* c1 = c0;

			LineSwapSourceVerts(p0, p1, c0, c1);
			MakeLineArray(&g_vertexBuffer[g_vertexIndex], p0, p1, gte_index);
			MakeTexcoordLineZero(&g_vertexBuffer[g_vertexIndex], 0);
			MakeColourLine(&g_vertexBuffer[g_vertexIndex], c0, c1);

			TriangulateQuad();

			g_vertexIndex += 6;
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
		}

		{
			VERTTYPE* p0 = &poly->x1;
			VERTTYPE* p1 = &poly->x2;
			unsigned char* c0 = &poly->r0;
			unsigned char* c1 = c0;

			LineSwapSourceVerts(p0, p1, c0, c1);
			MakeLineArray(&g_vertexBuffer[g_vertexIndex], p0, p1, gte_index);
			MakeTexcoordLineZero(&g_vertexBuffer[g_vertexIndex], 0);
			MakeColourLine(&g_vertexBuffer[g_vertexIndex], c0, c1);

			TriangulateQuad();

			g_vertexIndex += 6;
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
		}

		{
			VERTTYPE* p0 = &poly->x2;
			VERTTYPE* p1 = &poly->x3;
			unsigned char* c0 = &poly->r0;
			unsigned char* c1 = c0;

			LineSwapSourceVerts(p0, p1, c0, c1);
			MakeLineArray(&g_vertexBuffer[g_vertexIndex], p0, p1, gte_index);
			MakeTexcoordLineZero(&g_vertexBuffer[g_vertexIndex], 0);
			MakeColourLine(&g_vertexBuffer[g_vertexIndex], c0, c1);

			TriangulateQuad();

			g_vertexIndex += 6;
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
		}

		break;
	}
	case 0x50:
	{
		LINE_G2* poly = (LINE_G2*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		VERTTYPE* p0 = &poly->x0;
		VERTTYPE* p1 = &poly->x1;
		unsigned char* c0 = &poly->r0;
		unsigned char* c1 = &poly->r1;

		LineSwapSourceVerts(p0, p1, c0, c1);
		MakeLineArray(&g_vertexBuffer[g_vertexIndex], p0, p1, gte_index);
		MakeTexcoordLineZero(&g_vertexBuffer[g_vertexIndex], 0);
		MakeColourLine(&g_vertexBuffer[g_vertexIndex], c0, c1);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x60:
	{
		TILE* poly = (TILE*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		MakeVertexRect(&g_vertexBuffer[g_vertexIndex], &poly->x0, poly->w, poly->h, gte_index);
		MakeTexcoordQuadZero(&g_vertexBuffer[g_vertexIndex], 0);
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif

		break;
	}
	case 0x64:
	{
		SPRT* poly = (SPRT*)pTag;

		AddSplit(semi_transparent, g_vramTexture);

		MakeVertexRect(&g_vertexBuffer[g_vertexIndex], &poly->x0, poly->w, poly->h, gte_index);
		MakeTexcoordRect(&g_vertexBuffer[g_vertexIndex], &poly->u0, activeDrawEnv.tpage, poly->clut, poly->w, poly->h);
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x68:
	{
		TILE_1* poly = (TILE_1*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		MakeVertexRect(&g_vertexBuffer[g_vertexIndex], &poly->x0, 1, 1, gte_index);
		MakeTexcoordQuadZero(&g_vertexBuffer[g_vertexIndex], 0);
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x70:
	{
		TILE_8* poly = (TILE_8*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		MakeVertexRect(&g_vertexBuffer[g_vertexIndex], &poly->x0, 8, 8, gte_index);
		MakeTexcoordQuadZero(&g_vertexBuffer[g_vertexIndex], 0);
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x74:
	{
		SPRT_8* poly = (SPRT_8*)pTag;

		AddSplit(semi_transparent, g_vramTexture);

		MakeVertexRect(&g_vertexBuffer[g_vertexIndex], &poly->x0, 8, 8, gte_index);
		MakeTexcoordRect(&g_vertexBuffer[g_vertexIndex], &poly->u0, activeDrawEnv.tpage, poly->clut, 8, 8);
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x78:
	{
		TILE_16* poly = (TILE_16*)pTag;

		AddSplit(semi_transparent, g_whiteTexture);

		MakeVertexRect(&g_vertexBuffer[g_vertexIndex], &poly->x0, 16, 16, gte_index);
		MakeTexcoordQuadZero(&g_vertexBuffer[g_vertexIndex], 0);
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0x7C:
	{
		SPRT_16* poly = (SPRT_16*)pTag;

		AddSplit(semi_transparent, g_vramTexture);

		MakeVertexRect(&g_vertexBuffer[g_vertexIndex], &poly->x0, 16, 16, gte_index);
		MakeTexcoordRect(&g_vertexBuffer[g_vertexIndex], &poly->u0, activeDrawEnv.tpage, poly->clut, 16, 16);
		MakeColourQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

		TriangulateQuad();

		g_vertexIndex += 6;

#if defined(DEBUG_POLY_COUNT)
		polygon_count++;
#endif
		break;
	}
	case 0xA0:  // DR_LOAD commands
	{
		DR_LOAD* drload = (DR_LOAD*)pTag;

		RECT16 rect;
		*(ulong*)&rect.x = *(ulong*)&drload->code[1];
		*(ulong*)&rect.w = *(ulong*)&drload->code[2];

		LoadImagePSX(&rect, drload->p);
		//Emulator_UpdateVRAM();			// FIXME: should it be updated immediately?

		// FIXME: is there othercommands?

		break;
	}
	case 0xB0:
	{
		// [A] Psy-X custom texture packet
		DR_PSYX_TEX* drtex = (DR_PSYX_TEX*)pTag;
		break;
	}
	case 0xE0:  // DR_ENV commands
	{
		uint i;
		DR_ENV* drenv = (DR_ENV*)pTag;

		// parse each code of the command
		for (i = 0; i < pTag->len; i++)
		{
			u_long code = drenv->code[i];
			u_char drcode = code >> 24 & 0xFF;

			switch (drcode)
			{
			case 0xE1:
			{
				activeDrawEnv.tpage = (code & 0x1FF);
				activeDrawEnv.dtd = (code >> 9) & 1;
				activeDrawEnv.dfe = (code >> 10) & 1;

				break;
			}
			case 0xE2:
			{
				activeDrawEnv.tw.w = (code & 0x1F);
				activeDrawEnv.tw.h = ((code >> 5) & 0x1F);
				activeDrawEnv.tw.x = ((code >> 10) & 0x1F);
				activeDrawEnv.tw.y = ((code >> 15) & 0x1F);
				break;
			}
			case 0xE3:
			{
				activeDrawEnv.clip.x = code & 1023;
				activeDrawEnv.clip.y = (code >> 10) & 1023;
				break;
			}
			case 0xE4:
			{
				activeDrawEnv.clip.w = code & 1023;
				activeDrawEnv.clip.h = (code >> 10) & 1023;

				activeDrawEnv.clip.w -= activeDrawEnv.clip.x;
				activeDrawEnv.clip.h -= activeDrawEnv.clip.y;
				break;
			}
			case 0xE5:
			{
				activeDrawEnv.ofs[0] = code & 2047;
				activeDrawEnv.ofs[1] = (code >> 11) & 2047;

				break;
			}
			case 0xE6:
			{
				eprintf("Mask setting: %08x\n", code);
				//MaskSetOR = (*cb & 1) ? 0x8000 : 0x0000;
				//MaskEvalAND = (*cb & 2) ? 0x8000 : 0x0000;
				break;
			}
			}
		}
		break;
	}
	default:
	{
		//Unhandled poly type
		eprinterr("Unhandled primitive type: %02X type2:%02X\n", pTag->code, pTag->code & ~3);
		break;
	}
	}

	return (pTag->len + P_LEN) * sizeof(long);
}

int ParseLinkedPrimitiveList(uintptr_t packetStart, uintptr_t packetEnd)
{
	uintptr_t currentAddress = packetStart;

	int lastSize = -1;

	while (currentAddress != packetEnd)
	{
		lastSize = ParsePrimitive(currentAddress);

		if (lastSize == -1)	// not valid packets submitted
			break;

		currentAddress += lastSize;
	}

	g_splits[g_splitIndex].numVerts = g_vertexIndex - g_splits[g_splitIndex].startVertex;

	return lastSize;
}