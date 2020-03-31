#ifndef EMULATOR_H
#define EMULATOR_H

#include "EMULATOR_PLATFORM_SETUP.H"
#include "LIBGPU.H"

#include <stdio.h>
#include <stddef.h>

#ifndef TRUE
#define TRUE		1
#endif
#ifndef FALSE
#define FALSE		0
#endif
#ifndef NULL
#define NULL		0
#endif

#ifdef _MSC_VER
#define FUNCNAME __FUNCTION__
#else
#define FUNCNAME __func__
#endif

#if defined(__ANDROID__)
#include <android/log.h>
#define LOG_TAG_EMU "[EMU] "
#define eprintf(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG_EMU, fmt, ##__VA_ARGS__)
#define eprinterr(fmt, ...) eprintf("[%s] - " fmt, FUNCNAME, ##__VA_ARGS__);
#else
#define eprintf(fmt, ...) printf("[EMU] " fmt, ##__VA_ARGS__)
#define eprinterr(fmt, ...) eprintf("[%s] - " fmt, FUNCNAME, ##__VA_ARGS__);
#endif

#if defined(__EMSCRIPTEN__)
#define UNIMPLEMENTED() 0;
#else
#define UNIMPLEMENTED() eprinterr("Unimplemented!\n");
#endif

#define RESOLUTION_SCALE (1)

#define VRAM_WIDTH (1024 * RESOLUTION_SCALE)
#define VRAM_HEIGHT (512 * RESOLUTION_SCALE)

#define TPAGE_WIDTH (256)
#define TPAGE_HEIGHT (256)

#define CLUT_WIDTH (16)
#define CLUT_HEIGHT (1)

#define CTR_RUNNING (0)
#define CTR_STOPPED (1)

#define CTR_MODE_TO_FFFF (0)
#define CTR_MODE_TO_TARG (1)

#define CTR_CLOCK_SYS (0)
#define CTR_CLOCK_PIXEL (1)
#define CTR_HORIZ_RETRACE (1)

#define CTR_CLOCK_SYS_ONE (0)
#define CTR_CLOCK_SYS_ONE_EIGHTH (1)

#define GET_TPAGE_X(tpage) ((tpage << 6) & 0x7C0) % (VRAM_WIDTH / RESOLUTION_SCALE);
#define GET_TPAGE_Y(tpage) ((((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200))) % (VRAM_HEIGHT / RESOLUTION_SCALE);
#define GET_TPAGE_TYPE(tpage) (tpage >> 7) & 0x3;
#define GET_CLUT_X(clut) ((clut & 0x3F) << 4);
#define GET_CLUT_Y(clut) (clut >> 6);

typedef struct
{
	unsigned int i_cycle;

	union
	{
		unsigned short cycle;
		unsigned short unk00;
	};

	unsigned int i_value;

	union
	{
		unsigned short value;
		unsigned short unk01;
	};

	unsigned int i_target;

	union
	{
		unsigned short target;
		unsigned short unk02;
	};


	unsigned int padding00;
	unsigned int padding01;
} SysCounter;

extern SysCounter counters[3];

#pragma pack(push,1)
struct Vertex
{
	float x, y, z;
	float u0, v0;
#if defined(OGL) || defined(OGLES) || defined(VK)
	float col[4];
#elif defined(D3D9) 
	D3DCOLOR col;
#endif
};
#pragma pack(pop)


enum BlendMode
{
	BM_AVERAGE, 
	BM_ADD,
	BM_SUBTRACT,
	BM_ADD_QUATER_SOURCE,
	BM_DEFAULT
};

extern unsigned int g_lastBoundTexture;
#if defined(OGL) || defined(OGLES)
extern int Emulator_InitialiseGL();
#elif defined(D3D9)
extern int Emulator_InitialiseD3D();
#endif
extern void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer);
extern void Emulator_ShutDown();
extern void Emulator_SwapWindow();
#if defined(OGL) || defined(OGLES) || defined(VK)
extern unsigned int Emulator_GenerateTpage(unsigned short tpage, unsigned short clut);
#elif defined(D3D9)
IDirect3DTexture9* Emulator_GenerateTpage(unsigned short tpage, unsigned short clut);
#endif
extern void Emulator_DestroyFrameBuffer(unsigned int* fbo);
extern void Emulator_GenerateFrameBuffer(unsigned int* fbo);
extern void Emulator_GenerateAndBindNullWhite();
extern void Emulator_CheckTextureIntersection(RECT16* rect);
extern void Emulator_SetBlendMode(int mode, int semiTransparent);
extern void Emulator_CounterLoop();
extern void Emulator_GenerateLineArray(struct Vertex* vertex, short* p0, short* p1, short* p2, short* p3);
extern void Emulator_GenerateVertexArrayQuad(struct Vertex* vertex, short* p0, short* p1, short* p2, short* p3, short w, short h);
extern void Emulator_GenerateTexcoordArrayQuad(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short w, short h);
extern void Emulator_GenerateColourArrayQuad(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, int bMultiplyColour);
#if defined(OGL) || defined(OGLES) || defined(D3D9) || defined(VK)
extern void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar);
extern void Emulator_Scalef(float sx, float sy, float sz);
#endif
#if defined(OGL) || defined(OGLES) || defined(VK)
extern void Emulator_BindTexture(unsigned int textureId);
#elif defined(D3D9)
extern void Emulator_BindTexture(IDirect3DTexture9* texture);
#endif
extern void Emulator_DestroyTextures(int numTextures, unsigned int* textures);
extern void Emulator_SetViewPort(int x, int y, int width, int height);
extern void Emulator_SetScissorBox(int x, int y, int width, int height);
#if defined(OGL) || defined(OGLES)
extern void Emulator_BindFrameBuffer(GLuint frameBufferObject);
#elif defined(D3D9)
extern void Emulator_BindFrameBuffer(IDirect3DSurface9* frameBufferObject);
#elif defined(VK)
extern void Emulator_BindFrameBuffer(struct FrameBuffer frameBufferObject);
#else
extern void Emulator_BindFrameBuffer(int frameBufferObject);
#endif
extern void Emulator_CreateVertexBuffer(int numVertices, int vertexStride, void* pVertices);
#if defined(D3D9)
extern IDirect3DDevice9* d3ddev;
extern IDirect3DVertexDeclaration9* g_vertexDecl;
#endif

#endif