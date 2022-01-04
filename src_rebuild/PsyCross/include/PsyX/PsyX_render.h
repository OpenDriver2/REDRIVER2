#ifndef EMULATOR_H
#define EMULATOR_H

/*
 * Platform specific emulator setup
 */
#if (defined(_WIN32) || defined(__APPLE__) || defined(__linux__)) && !defined(__ANDROID__) && !defined(__EMSCRIPTEN__) && !defined(__RPI__)
#   define RENDERER_OGL
#   define USE_GLAD
#elif defined(__RPI__)
#   define RENDERER_OGLES
#   define OGLES_VERSION (3)
#elif defined(__EMSCRIPTEN__)
#   define RENDERER_OGLES
#   define OGLES_VERSION (2)
#elif defined(__ANDROID__)
#   define RENDERER_OGLES
#   define OGLES_VERSION (3)
#endif

#if defined(RENDERER_OGL) || defined(RENDERER_OGLES)
#   define USE_OPENGL 1
#endif

#if OGLES_VERSION == 2
#   define ES2_SHADERS
#elif OGLES_VERSION == 3
#   define ES3_SHADERS
#endif

 /*
  * OpenGL
  */
#if defined (RENDERER_OGL)

#   define GL_GLEXT_PROTOTYPES
#   include "common/glad.h"

#elif defined (RENDERER_OGLES)

#   define GL_GLEXT_PROTOTYPES

#   ifdef __EMSCRIPTEN__
#      include <GL/gl.h>
#   else
#      if OGLES_VERSION == 2
#          include <GLES2/gl2.h>
#          include <GLES2/gl2ext.h>
#      elif OGLES_VERSION == 3
#          include <GLES3/gl3.h>
#      endif
#   endif

#   include <EGL/egl.h>

#endif

  // setup renderer texture formats
#if defined(RENDERER_OGL)
#   define TEXTURE_FORMAT GL_UNSIGNED_SHORT_1_5_5_5_REV
#elif defined(RENDERER_OGLES)
#   define TEXTURE_FORMAT GL_UNSIGNED_SHORT_5_5_5_1
#endif

#include "psx/types.h"

#include "common/pgxp_defs.h"

#include "psx/libgte.h"
#include "psx/libgpu.h"

#include <stdio.h>
#include <stddef.h>

#ifndef NULL
#define NULL		0
#endif

/*
// FIXME: enable when needed
#if defined(RENDERER_OGLES)

#	define glGenVertexArrays       glGenVertexArraysOES
#	define glBindVertexArray       glBindVertexArrayOES
#	define glDeleteVertexArrays    glDeleteVertexArraysOES

#endif
*/

#if defined(RENDERER_OGL)
#	define VRAM_FORMAT            GL_RG
#	define VRAM_INTERNAL_FORMAT   GL_RG32F
#elif defined(RENDERER_OGLES)
#	define VRAM_FORMAT            GL_LUMINANCE_ALPHA
#	define VRAM_INTERNAL_FORMAT   GL_LUMINANCE_ALPHA
#endif

#define VRAM_WIDTH (1024)
#define VRAM_HEIGHT (512)

#define TPAGE_WIDTH (256)
#define TPAGE_HEIGHT (256)

#pragma pack(push,1)
typedef struct
{
#if defined(USE_PGXP)
	float		x, y, page, clut;
	float		z, scr_h, ofsX, ofsY;
#else
	short		x, y, page, clut;
#endif

	u_char		u, v, bright, dither;
	u_char		r, g, b, a;

	char		tcx, tcy, _p0, _p1;
} GrVertex;
#pragma pack(pop)

typedef enum 
{
	a_position,
	a_zw,
	a_texcoord,
	a_color,
	a_extra,
} ShaderAttrib;

typedef enum
{
	BM_NONE,
	BM_AVERAGE,
	BM_ADD,
	BM_SUBTRACT,
	BM_ADD_QUATER_SOURCE
} BlendMode;

typedef enum
{
	TF_4_BIT,
	TF_8_BIT,
	TF_16_BIT
} TexFormat;

#define MAX_NUM_POLY_BUFFER_VERTICES (32768)
#define MAX_NUM_INDEX_BUFFERS        (4096)

#if defined(RENDERER_OGLES) || defined(RENDERER_OGL)
typedef uint TextureID;
typedef uint ShaderID;
#else
#error
#endif

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern TextureID	g_whiteTexture;
extern TextureID	g_vramTexture;

extern void			GR_SwapWindow();

// PSX VRAM operations
extern void			GR_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer);
extern void			GR_CopyVRAM(unsigned short* src, int x, int y, int w, int h, int dst_x, int dst_y);
extern void			GR_ReadVRAM(unsigned short* dst, int x, int y, int dst_w, int dst_h);

extern void			GR_StoreFrameBuffer(int x, int y, int w, int h);
extern void			GR_UpdateVRAM();
extern void			GR_ReadFramebufferDataToVRAM();

extern TextureID	GR_CreateRGBATexture(int width, int height, u_char* data /*= nullptr*/);
extern ShaderID		GR_Shader_Compile(const char* source);

extern void			GR_SetShader(const ShaderID shader);
extern void			GR_Perspective3D(const float fov, const float width, const float height, const float zNear, const float zFar);
extern void			GR_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar);

extern void			GR_SetBlendMode(BlendMode blendMode);
extern void			GR_SetPolygonOffset(float ofs);
extern void			GR_SetStencilMode(int drawPrim);
extern void			GR_EnableDepth(int enable);
extern void			GR_SetScissorState(int enable);
extern void			GR_SetOffscreenState(const RECT16* offscreenRect, int enable);
extern void			GR_SetupClipMode(const RECT16* clipRect, int enable);
extern void			GR_SetViewPort(int x, int y, int width, int height);
extern void			GR_SetTexture(TextureID texture, TexFormat texFormat);
extern void			GR_SetWireframe(int enable);

extern void			GR_DestroyTexture(TextureID texture);
extern void			GR_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b);
extern void			GR_ClearVRAM(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b);
extern void			GR_UpdateVertexBuffer(const GrVertex* vertices, int count);
extern void			GR_DrawTriangles(int start_vertex, int triangles);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif