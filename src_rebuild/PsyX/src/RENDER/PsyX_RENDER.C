#include "PSYX_PUBLIC.H"
#include "PSYX_RENDER.H"
#include "../PLATFORM_SETUP.H"
#include "UTIL/TIMER.H"

#include <assert.h>
#include <string.h>

#include "PSYX_GLOBALS.H"

#ifdef _WIN32
#include <windows.h>
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif //def WIN32

#define USE_PBO					1
#define USE_OFFSCREEN_BLIT		1
#define USE_FRAMEBUFFER_BLIT	1

extern SDL_Window* g_window;
extern int g_swapInterval;

#define PSX_SCREEN_ASPECT	(240.0f / 320.0f)			// PSX screen is mapped always to this aspect

int g_PreviousBlendMode = BM_NONE;
int g_PreviousDepthMode = 0;
int g_PreviousStencilMode = 0;
int g_PreviousScissorState = 0;
int g_PreviousOffscreenState = 0;
RECT16 g_PreviousFramebuffer = { 0,0,0,0 };
RECT16 g_PreviousOffscreen = { 0,0,0,0 };

ShaderID g_PreviousShader = -1;

TextureID g_vramTexture = -1;
TextureID g_fbTexture = -1;
TextureID g_offscreenRTTexture = -1;

TextureID g_whiteTexture = -1;
TextureID g_lastBoundTexture = -1;

int g_windowWidth = 0;
int g_windowHeight = 0;

int g_wireframeMode = 0;
int g_texturelessMode = 0;

int g_emulatorPaused = 0;
int g_polygonSelected = 0;
int g_pgxpTextureCorrection = 1;
int g_pgxpZBuffer = 1;
int g_bilinearFiltering = 0;

bool vram_need_update = true;
bool framebuffer_need_update = false;

#if defined(RENDERER_OGL)
struct GrPBO
{
	GLenum fmt;
	GLuint* pbos;
	uint64_t num_pbos;
	uint64_t dx;
	uint64_t num_downloads;

	int width;
	int height;
	int nbytes; /* number of bytes in the pbo buffer. */
	unsigned char* pixels; /* the downloaded pixels. */
};

int PBO_Init(GrPBO& pbo, GLenum format, int w, int h, int num)
{

	if (pbo.pbos)
	{
		eprinterr("Already initialized. Not necessary to initialize again; or shutdown first.");
		return -1;
	}

	if (0 >= num)
	{
		eprinterr("Invalid number of PBOs: %d", num);
		return -2;
	}

	pbo.fmt = format;
	pbo.width = w;
	pbo.height = h;
	pbo.num_pbos = num;

	if (GL_RED == pbo.fmt || GL_GREEN == pbo.fmt || GL_BLUE == pbo.fmt) {
		pbo.nbytes = pbo.width * pbo.height;
	}
	else if (GL_RGB == pbo.fmt || GL_BGR == pbo.fmt)
	{
		pbo.nbytes = pbo.width * pbo.height * 3;
	}
	else if (GL_RGBA == pbo.fmt || GL_BGRA == pbo.fmt) {
		pbo.nbytes = pbo.width * pbo.height * 4;
	}
	else
	{
		eprinterr("Unhandled pixel format, use GL_R, GL_RG, GL_RGB or GL_RGBA.");
		return -3;
	}

	if (pbo.nbytes == 0)
	{
		eprinterr("Invalid width or height given: %d x %d", pbo.width, pbo.height);
		return -4;
	}

	pbo.pbos = (GLuint*)malloc(sizeof(GLuint) * num);
	pbo.pixels = (u_char*)malloc(pbo.nbytes);

#if USE_PBO
	glGenBuffers(num, pbo.pbos);
	for (int i = 0; i < num; ++i)
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo.pbos[i]);
		glBufferData(GL_PIXEL_PACK_BUFFER, pbo.nbytes, NULL, GL_STREAM_READ);
	}

	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
#endif
	return 0;
}

void PBO_Destroy(GrPBO& pbo)
{
	if(pbo.pbos)
	{
		glDeleteBuffers(pbo.num_pbos, pbo.pbos);
	
		free(pbo.pbos);
		pbo.num_pbos = 0;
		pbo.pbos = NULL;
	}
	
	if (pbo.pixels)
	{
		free(pbo.pixels);
		pbo.pixels = NULL;
	}

	pbo.num_downloads = 0;
	pbo.dx = 0;
	pbo.fmt = 0;
	pbo.nbytes = 0;
}

void PBO_Download(GrPBO& pbo)
{
	unsigned char* ptr;
	
#if USE_PBO
	if (pbo.num_downloads < pbo.num_pbos)
	{
		/*
		   First we need to make sure all our pbos are bound, so glMap/Unmap will
		   read from the oldest bound buffer first.
		*/
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo.pbos[pbo.dx]);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		//glReadPixels(0, 0, pbo.width, pbo.height, pbo.fmt, GL_UNSIGNED_BYTE, 0);   /* When a GL_PIXEL_PACK_BUFFER is bound, the last 0 is used as offset into the buffer to read into. */
}
	else
	{
		/* Read from the oldest bound pbo. */
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo.pbos[pbo.dx]);

		ptr = (unsigned char*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
		if (NULL != ptr)
		{
			memcpy(pbo.pixels, ptr, pbo.nbytes);
			glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		}
		else
		{
			eprintwarn("Failed to map the buffer\n");
		}

		/* Trigger the next read. */
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	}

	++pbo.dx;
	pbo.dx = pbo.dx % pbo.num_pbos;

	pbo.num_downloads++;

	if (pbo.num_downloads == UINT64_MAX)
		pbo.num_downloads = pbo.num_pbos;

	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
#else
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0); /* just make sure we're not accidentilly using a PBO. */
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pbo.pixels);
#endif
}

GLuint		g_glVertexArray;
GLuint		g_glVertexBuffer;

GLuint		g_glBlitFramebuffer;
GrPBO		g_glFramebufferPBO;

GLuint		g_glVRAMFramebuffer;

GLuint		g_glOffscreenFramebuffer;
GrPBO		g_glOffscreenPBO;

#endif

#if defined(OGLES)
EGLint majorVersion = 0, minorVersion = 0;
EGLContext eglContext = NULL;
EGLSurface eglSurface = NULL;
EGLConfig eglConfig = NULL;
EGLDisplay eglDisplay = NULL;
int numConfigs = 0;

const EGLint config16bpp[] =
{
#if OGLES_VERSION == 2
		EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,
#elif OGLES_VERSION == 3
		EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
#endif
		EGL_BUFFER_SIZE,24,
		EGL_RED_SIZE,8,
		EGL_GREEN_SIZE,8,
		EGL_BLUE_SIZE,8,
		EGL_ALPHA_SIZE,0,
		EGL_DEPTH_SIZE,24,
		EGL_STENCIL_SIZE,0,
		EGL_SAMPLE_BUFFERS,1,
		EGL_SAMPLES,4,
		EGL_NONE
};

int GR_InitialiseGLESContext(char* windowName, int fullscreen)
{
	unsigned int windowFlags = SDL_WINDOW_OPENGL;

#if defined(__ANDROID__)
	windowFlags |= SDL_WINDOW_FULLSCREEN;
#endif

	eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, windowFlags);

	if (g_window == NULL)
	{
		eprinterr("Failed to create SDL window!\n");
	}

	if (!eglInitialize(eglDisplay, &majorVersion, &minorVersion))
	{
		eprinterr("eglInitialize failure! Error: %x\n", eglGetError());
		return FALSE;
	}

	eglBindAPI(EGL_OPENGL_ES_API);

	if (!eglChooseConfig(eglDisplay, config16bpp, &eglConfig, 1, &numConfigs))
	{
		printf("eglChooseConfig failed\n");
		if (eglContext == 0)
		{
			printf("Error code: %d\n", eglGetError());
		}
	}

	SDL_SysWMinfo systemInfo;
	SDL_VERSION(&systemInfo.version);
	SDL_GetWindowWMInfo(g_window, &systemInfo);
#if defined(__EMSCRIPTEN__)
	EGLNativeWindowType dummyWindow;
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)dummyWindow, NULL);
#elif defined(__ANDROID__)
	eglSurface = systemInfo.info.android.surface;
#else
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)systemInfo.info.win.window, NULL);
#endif
	if (eglSurface == EGL_NO_SURFACE)
	{
		eprinterr("eglSurface failure! Error: %x\n", eglGetError());
		return FALSE;
	}

	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, OGLES_VERSION, EGL_NONE };
	eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);

	if (eglContext == EGL_NO_CONTEXT) {
		eprinterr("eglContext failure! Error: %x\n", eglGetError());
		return FALSE;
	}

	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);

	return TRUE;
}

#elif defined(RENDERER_OGL)
int GR_InitialiseGLContext(char* windowName, int fullscreen)
{
	int windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	if (fullscreen)
	{
		windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_windowWidth, g_windowHeight, windowFlags);

	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window!\n");
		return 0;
	}
	
#if defined(OGLES)

#if defined(__ANDROID__)
	//Override to full screen.
	SDL_DisplayMode displayMode;
	if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
	{
		screenWidth = displayMode.w;
		windowWidth = displayMode.w;
		screenHeight = displayMode.h;
		windowHeight = displayMode.h;
	}
#endif
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OGLES_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

	if(!SDL_GL_CreateContext(g_window))
	{
		eprinterr("Failed to initialise - OpenGL ES %d.x is not supported.\n", OGLES_VERSION);
		return 0;
	}
#elif defined(RENDERER_OGL)

	int major_version = 3;
	int minor_version = 3;
	int profile = SDL_GL_CONTEXT_PROFILE_CORE;

	// find best OpenGL version
	do
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major_version);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor_version);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);

		if (SDL_GL_CreateContext(g_window))
			break;
	
		minor_version--;
		
	} while (minor_version >= 0);

	if (minor_version == -1)
	{
		eprinterr("Failed to initialise - OpenGL 3.x is not supported. Please update video drivers.\n");
		return 0;
	}
#endif

	return 1;
}
#endif

int GR_InitialiseGLExt()
{
	GLenum err = gladLoadGL();

	if (err == 0)
		return 0;

	const char* rend = (const char*)glGetString(GL_RENDERER);
	const char* vendor = (const char*)glGetString(GL_VENDOR);
	eprintf("*Video adapter: %s by %s\n", rend, vendor);

	const char* versionStr = (const char*)glGetString(GL_VERSION);
	eprintf("*OpenGL version: %s\n", versionStr);

	const char* glslVersionStr = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	eprintf("*GLSL version: %s\n", glslVersionStr);

	return 1;
}

int GR_InitialiseRender(char* windowName, int width, int height, int fullscreen)
{
	g_windowWidth = width;
	g_windowHeight = height;

#if defined(RO_DOUBLE_BUFFERED)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#else
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
#endif

#if defined(RENDERER_OGL) || defined(OGLES)
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

#if defined(RENDERER_OGL)
	if (!GR_InitialiseGLContext(windowName, fullscreen))
	{
		eprinterr("Failed to Initialise GL Context!\n");
		return 0;
	}
#elif defined(OGLES)
	if (!GR_InitialiseGLESContext(windowName, fullscreen))
	{
		eprinterr("Failed to Initialise GLES Context!\n");
		return 0;
	}
#endif

	if (!GR_InitialiseGLExt())
	{
		eprinterr("Failed to Intialise GL extensions\n");
		PsyX_ShutDown();
	}
#endif
	
	return 1;
}

void GR_Shutdown()
{
#if defined(RENDERER_OGL) || defined(OGLES)
	glDeleteVertexArrays(1, &g_glVertexArray);
	glDeleteBuffers(1, &g_glVertexBuffer);

	PBO_Destroy(g_glFramebufferPBO);
	PBO_Destroy(g_glOffscreenPBO);

	glDeleteFramebuffers(1, &g_glBlitFramebuffer);
	glDeleteFramebuffers(1, &g_glOffscreenFramebuffer);
	glDeleteFramebuffers(1, &g_glVRAMFramebuffer);

	GR_DestroyTexture(g_vramTexture);
	GR_DestroyTexture(g_whiteTexture);
	GR_DestroyTexture(g_fbTexture);
	GR_DestroyTexture(g_offscreenRTTexture);
#endif
}

void GR_BeginScene()
{
	g_lastBoundTexture = 0;

#if defined(RENDERER_OGL) || defined(OGLES)
	glBindVertexArray(g_glVertexArray);

	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_STENCIL_BUFFER_BIT);
#endif

	GR_UpdateVRAM();
	GR_SetViewPort(0, 0, g_windowWidth, g_windowHeight);

	if (g_wireframeMode)
	{
		GR_SetWireframe(true);

#if defined(RENDERER_OGL) || defined(OGLES)
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
#endif
	}
}

void GR_EndScene()
{
	framebuffer_need_update = true;
	
	if (g_wireframeMode)
		GR_SetWireframe(0);

#if defined(RENDERER_OGL) || defined(OGLES)
	glBindVertexArray(0);
#endif
}

//----------------------------------------------------------------------------------------

unsigned short vram[VRAM_WIDTH * VRAM_HEIGHT];

void GR_ResetDevice()
{
	PsyX_EnableSwapInterval(g_enableSwapInterval);
}

ShaderID g_gte_shader_4;
ShaderID g_gte_shader_8;
ShaderID g_gte_shader_16;

#if defined(OGLES) || defined(RENDERER_OGL)
GLint u_Projection;
GLint u_Projection3D;

#define GPU_PACK_RG\
	"		float color_16 = (color_rg.y * 256.0 + color_rg.x) * 255.0;\n"

#define GPU_DISCARD\
	"		if (color_16 == 0.0) { discard; }\n"

#define GPU_DECODE_RG\
	"		fragColor = fract(floor(color_16 / vec4(1.0, 32.0, 1024.0, 32768.0)) / 32.0);\n"

#define GPU_PACK_RG_FUNC\
	"	const float c_PackRange = 255.001;\n"\
	"	float packRG(vec2 rg) { return (rg.y * 256.0 + rg.x) * c_PackRange;}\n"

#define GPU_DECODE_RG_FUNC\
	"	vec4 decodeRG(float rg) { return fract(floor(rg / vec4(1.0, 32.0, 1024.0, 32768.0)) / 32.0); }\n"

#define GPU_DITHERING\
	"		fragColor *= v_color;\n"\
	"		mat4 dither = mat4(\n"\
	"			-4.0,  +0.0,  -3.0,  +1.0,\n"\
	"			+2.0,  -2.0,  +3.0,  -1.0,\n"\
	"			-3.0,  +1.0,  -4.0,  +0.0,\n"\
	"			+3.0,  -1.0,  +2.0,  -2.0) / 255.0;\n"\
	"		ivec2 dc = ivec2(fract(gl_FragCoord.xy / 4.0) * 4.0);\n"\
	"		fragColor.xyz += vec3(dither[dc.x][dc.y] * v_texcoord.w);\n"

#define GPU_SAMPLE_TEXTURE_4BIT_FUNC\
    "   // returns 16 bit colour\n"\
    "   float samplePSX(vec2 tc){\n"\
    "       vec2 uv = (tc * vec2(0.25, 1.0) + v_page_clut.xy) * c_VRAMTexel;\n"\
    "       vec2 comp = VRAM(uv);\n"\
    "       int index = int(fract(tc.x / 4.0 + 0.0001) * 4.0);\n"\
    "       float v = comp[index / 2] * (c_PackRange / 16.0);\n"\
    "       float f = floor(v);\n"\
    "       vec2 c = vec2( (v - f) * 16.0, f );\n"\
    "       vec2 clut_pos = v_page_clut.zw;\n"\
    "       clut_pos.x += mix(c[0], c[1], mod(index, 2)) * c_VRAMTexel.x;\n"\
    "       return packRG(VRAM(clut_pos));\n"\
    "   }\n"

#define GPU_SAMPLE_TEXTURE_8BIT_FUNC\
	"	// returns 16 bit colour\n"\
	"	float samplePSX(vec2 tc){\n"\
	"		vec2 uv = (tc * vec2(0.5, 1.0) + v_page_clut.xy) * c_VRAMTexel;\n"\
	"		vec2 comp = VRAM(uv);\n"\
	"		vec2 clut_pos = v_page_clut.zw;\n"\
	"		int index = int(mod(tc.x, 2.0));\n"\
	"		clut_pos.x += comp[index] * c_PackRange * c_VRAMTexel.x;\n"\
	"		vec2 color_rg = VRAM(clut_pos);\n"\
	"		return packRG(VRAM(clut_pos));\n"\
	"	}\n"

#define GPU_SAMPLE_TEXTURE_16BIT_FUNC\
	"	float samplePSX(vec2 tc){\n"\
	"		vec2 uv = (tc + v_page_clut.xy) * c_VRAMTexel;\n"\
	"		vec2 color_rg = VRAM(uv);\n"\
	"		return packRG(color_rg);\n"\
	"	}\n"


#define GPU_BILINEAR_SAMPLE_FUNC \
	"	float c_textureSize = 1;\n"\
	"	float c_onePixel = 1;\n"\
	"	vec4 BilinearTextureSample(vec2 P) {\n"\
	"		vec2 frac = fract(P);\n"\
	"		vec2 pixel = floor(P);\n"\
	"		float C11 = samplePSX(pixel);\n"\
	"		float C21 = samplePSX(pixel + vec2(c_onePixel, 0.0));\n"\
	"		float C12 = samplePSX(pixel + vec2(0.0, c_onePixel));\n"\
	"		float C22 = samplePSX(pixel + vec2(c_onePixel, c_onePixel));\n"\
	"		float ax1 = mix(float(C11 > 0), float(C21 > 0), frac.x);\n"\
	"		float ax2 = mix(float(C12 > 0), float(C22 > 0), frac.x);\n"\
	"		if(mix(ax1, ax2, frac.y) < 0.5) { discard; }\n"\
	"		vec4 x1 = mix(decodeRG(C11), decodeRG(C21), frac.x);\n"\
	"		vec4 x2 = mix(decodeRG(C12), decodeRG(C22), frac.x);\n"\
	"		return mix(x1, x2, frac.y);\n"\
	"	}\n"

#define GPU_NEAREST_SAMPLE_FUNC \
	"vec4 NearestTextureSample(vec2 P) {\n"\
	"	float color_16 = samplePSX(P);\n"\
	"	if(color_16 == 0.0) {discard;}\n"\
	"	return decodeRG(color_16);\n"\
	"}\n"

#if (VRAM_FORMAT == GL_LUMINANCE_ALPHA)
#define GTE_FETCH_VRAM_FUNC\
		"	uniform sampler2D s_texture;\n"\
		"	vec2 VRAM(vec2 uv) { return texture2D(s_texture, uv).ra; }\n"
#else
#define GPU_FETCH_VRAM_FUNC\
		"	uniform sampler2D s_texture;\n"\
		"	vec2 VRAM(vec2 uv) { return texture2D(s_texture, uv).rg; }\n"
#endif

#ifdef USE_PGXP
#define GTE_PERSPECTIVE_CORRECTION \
		"	mat4 ofsMat = mat4(\n"\
		"		vec4(1.0,  0.0,  0.0,  0.0),\n"\
		"		vec4(0.0,  1.0,  0.0,  0.0),\n"\
		"		vec4(0.0,  0.0,  1.0,  0.0),\n"\
		"		vec4(a_zw.z, -a_zw.w,  0.0,  1.0));\n"\
		"	vec2 geom_ofs = vec2(0.5, 0.5);\n"\
		"	vec4 fragPosition = (a_zw.y > 100 ? ofsMat * (Projection3D * vec4((a_position.xy + geom_ofs) * vec2(1,-1) * a_zw.y, a_zw.x, 1.0)) : (Projection * vec4(a_position.xy, 0.5, 1.0)));\n" \
		"	gl_Position = fragPosition;\n"
#else
#define GTE_PERSPECTIVE_CORRECTION \
		"	gl_Position = Projection * vec4(a_position.xy, 0.0, 1.0);\n"
#endif

#define GTE_VERTEX_SHADER \
	"	attribute vec4 a_position;\n"\
	"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"\
	"	attribute vec4 a_color;\n"\
	"	attribute vec4 a_extra; // texcoord.xy ofs, unused.xy\n"\
	"	attribute vec4 a_zw;\n"\
	"	uniform mat4 Projection;\n"\
	"	uniform mat4 Projection3D;\n"\
	"	const vec2 c_UVFudge = vec2(0.00025, 0.00025);\n"\
	"	void main() {\n"\
	"		v_texcoord = a_texcoord;\n"\
	"		v_texcoord.xy += a_extra.xy * 0.5;\n"\
	"		v_color = a_color;\n"\
	"		v_color.xyz *= a_texcoord.z;\n"\
	"		v_page_clut.x = fract(a_position.z / 16.0) * 1024.0;\n"\
	"		v_page_clut.y = floor(a_position.z / 16.0) * 256.0;\n"\
	"		v_page_clut.z = fract(a_position.w / 64.0);\n"\
	"		v_page_clut.w = floor(a_position.w / 64.0) / 512.0;\n"\
	"		v_page_clut.xy += c_UVFudge;\n"\
	"		v_page_clut.zw += c_UVFudge;\n"\
	GTE_PERSPECTIVE_CORRECTION\
	"		v_z = (gl_Position.z - 40) * 0.005;\n"\
	"	}\n"

#define GPU_FRAGMENT_SAMPLE_SHADER(bit) \
	GPU_PACK_RG_FUNC\
	GPU_DECODE_RG_FUNC\
	GPU_FETCH_VRAM_FUNC\
	"	const vec2 c_VRAMTexel = vec2(1.0 / 1024.0, 1.0 / 512.0);\n"\
	GPU_SAMPLE_TEXTURE_## bit ##BIT_FUNC\
	"#ifdef BILINEAR_FILTER\n"\
	GPU_BILINEAR_SAMPLE_FUNC\
	"#else\n"\
	GPU_NEAREST_SAMPLE_FUNC\
	"#endif\n"\
	"	void main() {\n"\
	"#ifdef BILINEAR_FILTER\n"\
	"		fragColor = BilinearTextureSample(v_texcoord.xy);\n"\
	"#else\n"\
	"		fragColor = NearestTextureSample(v_texcoord.xy);\n"\
	"#endif\n"\
	GPU_DITHERING\
	"	}\n"

const char* gte_shader_4 =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"varying vec4 v_page_clut;\n"
	"varying float v_z;\n"
	"#ifdef VERTEX\n"
	GTE_VERTEX_SHADER
	"#else\n"
	GPU_FRAGMENT_SAMPLE_SHADER(4)
	"#endif\n";

const char* gte_shader_8 =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"varying vec4 v_page_clut;\n"
	"varying float v_z;\n"
	"#ifdef VERTEX\n"
	GTE_VERTEX_SHADER
	"#else\n"
	GPU_FRAGMENT_SAMPLE_SHADER(8)
	"#endif\n";

const char* gte_shader_16 =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"varying vec4 v_page_clut;\n"
	"varying float v_z;\n"
	"#ifdef VERTEX\n"
	GTE_VERTEX_SHADER
	"#else\n"
	GPU_FRAGMENT_SAMPLE_SHADER(16)
	"#endif\n";

int GR_Shader_CheckShaderStatus(GLuint shader)
{
	char info[1024];
	GLint result;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (result == GL_TRUE)
		return 1;
	
	glGetShaderInfoLog(shader, sizeof(info), NULL, info);
	if (info[0] && strlen(info) > 8)
	{
		eprinterr("%s\n", info);
		assert(0);
	}

	return 0;
}

int GR_Shader_CheckProgramStatus(GLuint program)
{
	char info[1024];
	GLint result;

	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if (result == GL_TRUE)
		return 1;

	glGetProgramInfoLog(program, sizeof(info), NULL, info);
	if (info[0] && strlen(info) > 8)
	{
		eprinterr("%s\n", info);
		assert(0);
	}

	return 0;
}

ShaderID GR_Shader_Compile(const char* source)
{
#if defined(ES2_SHADERS)
	const char* GLSL_HEADER_VERT =
		"#version 100\n"
		"precision lowp  int;\n"
		"precision highp float;\n"
		"#define VERTEX\n";

	const char* GLSL_HEADER_FRAG =
		"#version 100\n"
		"precision lowp  int;\n"
		"precision highp float;\n"
		"#define fragColor gl_FragColor\n";
#elif defined(ES3_SHADERS)
	const char* GLSL_HEADER_VERT =
		"#version 300 es\n"
		"precision lowp  int;\n"
		"precision highp float;\n"
		"#define VERTEX\n"
		"#define varying   out\n"
		"#define attribute in\n"
		"#define texture2D texture\n";

	const char* GLSL_HEADER_FRAG =
		"#version 300 es\n"
		"precision lowp  int;\n"
		"precision highp float;\n"
		"#define varying     in\n"
		"#define texture2D   texture\n"
		"out vec4 fragColor;\n";
#else
	const char* GLSL_HEADER_VERT =
		"#version 140\n"
		"precision lowp  int;\n"
		"precision highp float;\n"
		"#define VERTEX\n"
		"#define varying   out\n"
		"#define attribute in\n"
		"#define texture2D texture\n";

	const char* GLSL_HEADER_FRAG =
		"#version 140\n"
		"precision lowp  int;\n"
		"precision highp float;\n"
		"#define varying     in\n"
		"#define texture2D   texture\n"
		"out vec4 fragColor;\n";
#endif

	char extra_vs_defines[1024];
	char extra_fs_defines[1024];
	extra_vs_defines[0] = 0;
	extra_fs_defines[0] = 0;

	if (g_bilinearFiltering)
	{
		strcat(extra_fs_defines, "#define BILINEAR_FILTER\n");
	}

	const char* vs_list[] = { GLSL_HEADER_VERT, extra_vs_defines, source };
	const char* fs_list[] = { GLSL_HEADER_FRAG, extra_fs_defines, source };

	GLuint program = glCreateProgram();

	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 3, vs_list, NULL);
		glCompileShader(vertexShader);

		if( GR_Shader_CheckShaderStatus(vertexShader) == 0 )
			eprinterr("Failed to compile Vertex Shader!\n");
	
		glAttachShader(program, vertexShader);
		glDeleteShader(vertexShader);
	}

	{
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 3, fs_list, NULL);
		glCompileShader(fragmentShader);

		if(GR_Shader_CheckShaderStatus(fragmentShader) == 0)
			eprinterr("Failed to compile Fragment Shader!\n");
	
		glAttachShader(program, fragmentShader);
		glDeleteShader(fragmentShader);
	}

	glBindAttribLocation(program, a_position, "a_position");
	glBindAttribLocation(program, a_texcoord, "a_texcoord");
	glBindAttribLocation(program, a_color, "a_color");


#ifdef USE_PGXP
	glBindAttribLocation(program, a_zw, "a_zw");
#endif

	glLinkProgram(program);
	if(GR_Shader_CheckProgramStatus(program) == 0)
		eprinterr("Failed to link Shader!\n");

	GLint sampler = 0;
	glUseProgram(program);
	glUniform1iv(glGetUniformLocation(program, "s_texture"), 1, &sampler);
	glUseProgram(0);

	return program;
}
#else
#error
#endif

//--------------------------------------------------------------------------------------------

void GR_GenerateCommonTextures()
{
	unsigned int pixelData = 0xFFFFFFFF;

#if defined(RENDERER_OGL) || defined(OGLES)
	glGenTextures(1, &g_whiteTexture);
	{
		glBindTexture(GL_TEXTURE_2D, g_whiteTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
#endif
}

void GR_InitialisePSXShaders()
{
	g_gte_shader_4 = GR_Shader_Compile(gte_shader_4);
	g_gte_shader_8 = GR_Shader_Compile(gte_shader_8);
	g_gte_shader_16 = GR_Shader_Compile(gte_shader_16);

#if defined(RENDERER_OGL) || defined(OGLES)
	u_Projection = glGetUniformLocation(g_gte_shader_4, "Projection");
#ifdef USE_PGXP
	u_Projection3D = glGetUniformLocation(g_gte_shader_4, "Projection3D");
#endif
#endif
}

int GR_InitialisePSX()
{
	SDL_memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));
	GR_GenerateCommonTextures();
	GR_InitialisePSXShaders();

#if defined(RENDERER_OGL) || defined(OGLES)
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_STENCIL_TEST);
	glBlendColor(0.5f, 0.5f, 0.5f, 0.25f);

	// gen framebuffer
	{
		memset(&g_glFramebufferPBO, 0, sizeof(g_glFramebufferPBO));
		PBO_Init(g_glFramebufferPBO, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 2);
		
		// make a special texture
		// it will be resized later
		glGenTextures(1, &g_fbTexture);
		{
			glBindTexture(GL_TEXTURE_2D, g_fbTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			// default to VRAM size
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glGenFramebuffers(1, &g_glBlitFramebuffer);
		{
			glBindFramebuffer(GL_FRAMEBUFFER, g_glBlitFramebuffer);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_fbTexture, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	// gen offscreen RT
	{
		memset(&g_glOffscreenPBO, 0, sizeof(g_glOffscreenPBO));
		PBO_Init(g_glOffscreenPBO, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 2);
		
		// offscreen texture render target
		glGenTextures(1, &g_offscreenRTTexture);
		{
			glBindTexture(GL_TEXTURE_2D, g_offscreenRTTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			// default to VRAM size
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glGenFramebuffers(1, &g_glOffscreenFramebuffer);
		{
			glBindFramebuffer(GL_FRAMEBUFFER, g_glOffscreenFramebuffer);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_offscreenRTTexture, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	// gen VRAM textures.
	// double-buffered
	{
		glGenTextures(1, &g_vramTexture);

		{
			glBindTexture(GL_TEXTURE_2D, g_vramTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			// set storage size
			glTexImage2D(GL_TEXTURE_2D, 0, VRAM_INTERNAL_FORMAT, VRAM_WIDTH, VRAM_HEIGHT, 0, VRAM_FORMAT, GL_UNSIGNED_BYTE, NULL);
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		// VRAM framebuffer for offscreen blitting to VRAM
		glGenFramebuffers(1, &g_glVRAMFramebuffer);
		{
			glBindFramebuffer(GL_FRAMEBUFFER, g_glVRAMFramebuffer);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_vramTexture, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	// gen vertex buffer and index buffer
	{
		glGenBuffers(1, &g_glVertexBuffer);
		glGenVertexArrays(1, &g_glVertexArray);

		glBindVertexArray(g_glVertexArray);

		glBindBuffer(GL_ARRAY_BUFFER, g_glVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GrVertex) * MAX_NUM_POLY_BUFFER_VERTICES, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(a_position);
		glEnableVertexAttribArray(a_texcoord);
		glEnableVertexAttribArray(a_color);
		glEnableVertexAttribArray(a_extra);

#if defined(USE_PGXP)
		glVertexAttribPointer(a_position, 4, GL_FLOAT, GL_FALSE, sizeof(GrVertex), &((GrVertex*)NULL)->x);
		glVertexAttribPointer(a_zw, 4, GL_FLOAT, GL_FALSE, sizeof(GrVertex), &((GrVertex*)NULL)->z);

		glEnableVertexAttribArray(a_zw);
#else
		glVertexAttribPointer(a_position, 4, GL_SHORT, GL_FALSE, sizeof(GrVertex), &((GrVertex*)NULL)->x);
#endif

		glVertexAttribPointer(a_texcoord, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(GrVertex), &((GrVertex*)NULL)->u);
		glVertexAttribPointer(a_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GrVertex), &((GrVertex*)NULL)->r);
		glVertexAttribPointer(a_extra, 4, GL_BYTE, GL_FALSE, sizeof(GrVertex), &((GrVertex*)NULL)->tcx);

		glBindVertexArray(0);
	}
#else
#error
#endif

	GR_ResetDevice();
	PsyX_EnableSwapInterval(g_enableSwapInterval);

	return 1;
}

void PsyX_EnableSwapInterval(int enable)
{
	g_enableSwapInterval = enable;
#if defined(RENDERER_OGL)
	SDL_GL_SetSwapInterval(g_enableSwapInterval ? g_swapInterval : 0);
#endif
}

void GR_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
{
	float a = 2.0f / (right - left);
	float b = 2.0f / (top - bottom);
	float c = 2.0f / (znear - zfar);

	float x = (left + right) / (left - right);
	float y = (bottom + top) / (bottom - top);

#if defined(RENDERER_OGL) || defined(OGLES) // -1..1
	float z = (znear + zfar) / (znear - zfar);
#endif

	float ortho[16] = {
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		x, y, z, 1
	};

#if defined(RENDERER_OGL) || defined(OGLES)
	glUniformMatrix4fv(u_Projection, 1, GL_FALSE, ortho);
#endif
}

void GR_Perspective3D(const float fov, const float width, const float height, const float zNear, const float zFar)
{
	float sinF, cosF;
	sinF = sinf(0.5f * fov);
	cosF = cosf(0.5f * fov);

	float h = cosF / sinF;
	float w = (h * height) / width;

	float persp[16] = {
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, (zFar + zNear) / (zFar - zNear), -(2 * zFar * zNear) / (zFar - zNear),
		0, 0, 1, 0
	};

#if defined(RENDERER_OGL) || defined(OGLES)
	glUniformMatrix4fv(u_Projection3D, 1, GL_TRUE, persp);
#elif defined(D3D9)
	d3ddev->SetVertexShaderConstantF(u_Projection3D, persp, 4);
#endif
}

void GR_SetupClipMode(const RECT16& rect, int enable)
{
	// [A] isinterlaced dirty hack for widescreen
	bool scissorOn = enable && (activeDispEnv.isinter ||
		(rect.x - activeDispEnv.disp.x > 0 ||
			rect.y - activeDispEnv.disp.y > 0 ||
			rect.w < activeDispEnv.disp.w - 1 ||
			rect.h < activeDispEnv.disp.h - 1));

	GR_SetScissorState(scissorOn);

	if (!scissorOn)
		return;

	float psxScreenW = activeDispEnv.disp.w;
	float psxScreenH = activeDispEnv.disp.h;

	// first map to 0..1
	float clipRectX = (float)(rect.x - activeDispEnv.disp.x) / psxScreenW;
	float clipRectY = (float)(rect.y - activeDispEnv.disp.y) / psxScreenH;
	float clipRectW = (float)(rect.w) / psxScreenW;
	float clipRectH = (float)(rect.h) / psxScreenH;

	// then map to screen
	{
		clipRectX -= 0.5f;
#ifdef USE_PGXP
		float emuScreenAspect = float(g_windowWidth) / float(g_windowHeight);
#else
		float emuScreenAspect = (320.0f / 240.0f);
#endif

		clipRectX /= PSX_SCREEN_ASPECT * emuScreenAspect;
		clipRectW /= emuScreenAspect * PSX_SCREEN_ASPECT;

		clipRectX += 0.5f;
	}

#if defined(RENDERER_OGL) || defined(OGLES)	
	float flipOffset = g_windowHeight - clipRectH * (float)g_windowHeight;

	glScissor(clipRectX * (float)g_windowWidth,
		flipOffset - clipRectY * (float)g_windowHeight,
		clipRectW * (float)g_windowWidth,
		clipRectH * (float)g_windowHeight);
#endif
}

void PsyX_GetPSXWidescreenMappedViewport(struct _RECT16* rect)
{
#ifdef USE_PGXP
	float emuScreenAspect = float(g_windowWidth) / float(g_windowHeight);

	float psxScreenW = activeDispEnv.disp.w;
	float psxScreenH = activeDispEnv.disp.h;

	rect->x = activeDispEnv.screen.x;
	rect->y = activeDispEnv.screen.y;

	rect->w = psxScreenW * emuScreenAspect * PSX_SCREEN_ASPECT; // windowWidth;
	rect->h = psxScreenH; // windowHeight;

	rect->x -= (rect->w - activeDispEnv.disp.w) / 2;

	rect->w += rect->x;
#else
	rect->x = activeDispEnv.screen.x;
	rect->y = activeDispEnv.screen.y;
	rect->w = activeDispEnv.disp.w;
	rect->h = activeDispEnv.disp.h;
#endif
}

void GR_SetShader(const ShaderID& shader)
{
	if (g_PreviousShader != shader)
	{
#if defined(RENDERER_OGL) || defined(OGLES)
		glUseProgram(shader);
#else
#error
#endif

		g_PreviousShader = shader;
	}
}

void GR_SetTexture(TextureID texture, TexFormat texFormat)
{
	switch (texFormat)
	{
	case TF_4_BIT:
		GR_SetShader(g_gte_shader_4);
		break;
	case TF_8_BIT:
		GR_SetShader(g_gte_shader_8);
		break;
	case TF_16_BIT:
		GR_SetShader(g_gte_shader_16);
		break;
	}

	if (g_texturelessMode) {
		texture = g_whiteTexture;
	}

	if (g_lastBoundTexture == texture) {
		return;
	}

#if defined(RENDERER_OGL) || defined(OGLES)
	glBindTexture(GL_TEXTURE_2D, texture);
#endif

	g_lastBoundTexture = texture;
}

void GR_DestroyTexture(TextureID texture)
{
	if (texture == -1)
		return;

#if defined(RENDERER_OGL) || defined(OGLES)
	glDeleteTextures(1, &texture);
#else
#error
#endif
}

void GR_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
	// TODO clear rect if it's necessary
#if defined(RENDERER_OGL) || defined(OGLES)

	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
}

#define NOFILE 0

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)

void GR_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer)
{
#if NOFILE
	return;
#endif

#if defined(RENDERER_OGL) || defined(OGLES)

#define FLIP_Y (VRAM_HEIGHT - i - 1)

#endif

	FILE* fp = fopen(outputFileName, "wb");
	if (fp == NULL)
		return;

	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6];
	header[0] = (width % 256);
	header[1] = (width / 256);
	header[2] = (height % 256);
	header[3] = (height / 256);
	header[4] = 16;
	header[5] = 0;

	fwrite(TGAheader, sizeof(unsigned char), 12, fp);
	fwrite(header, sizeof(unsigned char), 6, fp);

	for (int i = 0; i < VRAM_HEIGHT; i++)
	{
		fwrite(vram + VRAM_WIDTH * FLIP_Y, sizeof(short), VRAM_WIDTH, fp);
	}

	fclose(fp);

#undef FLIP_Y
}
#endif

void GR_CopyRGBAFramebufferToVRAM(u_int* src, int x, int y, int w, int h, int update_vram, int flip_y)
{
	ushort* fb = (ushort*)malloc(w * h * sizeof(ushort));
	uint* data_src = (uint*)src;
	ushort* data_dst = (ushort*)fb;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			uint c = *data_src++;

			u_char b = ((c >> 3) & 0x1F);
			u_char g = ((c >> 11) & 0x1F);
			u_char r = ((c >> 19) & 0x1F);
			//u_char a = ((c >> 24) & 0x1F);

			int a = r == g == b == 0 ? 0 : 1;

			*data_dst++ = r | (g << 5) | (b << 10) | (a << 15);
		}
	}

	ushort* ptr = (ushort*)vram + VRAM_WIDTH * y + x;

	for (int fy = 0; fy < h; fy++)
	{
		int py = flip_y ? (h - fy - 1) : fy;
		ushort* fb_ptr = fb + (h * py / h) * w;

		for (int fx = 0; fx < w; fx++)
			ptr[fx] = fb_ptr[w * fx / w];

		ptr += VRAM_WIDTH;
	}

	free(fb);

	if (update_vram)
		vram_need_update = true;
}

void GR_ReadFramebufferDataToVRAM()
{
	int x, y, w, h;
	if (!framebuffer_need_update)
		return;

	framebuffer_need_update = false;

	x = g_PreviousFramebuffer.x;
	y = g_PreviousFramebuffer.y;
	w = g_PreviousFramebuffer.w;
	h = g_PreviousFramebuffer.h;

	// now we can read it back to VRAM texture
	{
#if defined(RENDERER_OGL) || defined(OGLES)	
		// reat the texture
		glBindTexture(GL_TEXTURE_2D, g_fbTexture);
		PBO_Download(g_glFramebufferPBO);
		glBindTexture(GL_TEXTURE_2D, 0);
		GR_CopyRGBAFramebufferToVRAM((u_int*)g_glFramebufferPBO.pixels, x, y, w, h, 0, 0);
#endif
	}
}

void GR_SetScissorState(int enable)
{
	if (g_PreviousScissorState == enable)
		return;

#if defined(RENDERER_OGL) || defined(OGLES)	
	if (g_PreviousScissorState)
		glDisable(GL_SCISSOR_TEST);
	else
		glEnable(GL_SCISSOR_TEST);
#endif
	g_PreviousScissorState = enable;
}

void GR_SetOffscreenState(const RECT16& offscreenRect, int enable)
{
	if (enable)
	{
		// setup render target viewport
#ifdef USE_PGXP
		GR_Ortho2D(-0.5f, 0.5f, 0.5f, -0.5f, -1.0f, 1.0f);
#else
		GR_Ortho2D(0, offscreenRect.w, offscreenRect.h, 0, -1.0f, 1.0f);
#endif
	}
	else
	{
		// setup default viewport
#ifdef USE_PGXP
		float emuScreenAspect = float(g_windowWidth) / float(g_windowHeight);
		GR_Ortho2D(-0.5f * emuScreenAspect * PSX_SCREEN_ASPECT, 0.5f * emuScreenAspect * PSX_SCREEN_ASPECT, 0.5f, -0.5f, -1.0f, 1.0f);
		GR_Perspective3D(0.9265f, 1.0f, 1.0f / (emuScreenAspect * PSX_SCREEN_ASPECT), 1.0f, 1000.0f);
#else
		GR_Ortho2D(0, activeDispEnv.disp.w, activeDispEnv.disp.h, 0, -1.0f, 1.0f);
#endif
	}

	if (g_PreviousOffscreenState == enable)
		return;

	g_PreviousOffscreenState = enable;

#if defined(RENDERER_OGL) || defined(OGLES)
	if (enable)
	{
		// set storage size first
		if (g_PreviousOffscreen.w != offscreenRect.w &&
			g_PreviousOffscreen.h != offscreenRect.h)
		{
			glBindTexture(GL_TEXTURE_2D, g_offscreenRTTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, offscreenRect.w, offscreenRect.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		g_PreviousOffscreen = offscreenRect;

		GR_SetViewPort(0, 0, offscreenRect.w, offscreenRect.h);
		glBindFramebuffer(GL_FRAMEBUFFER, g_glOffscreenFramebuffer);

		// clear it out
		glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else
	{
		GR_SetViewPort(0, 0, g_windowWidth, g_windowHeight);

#if USE_OFFSCREEN_BLIT
		// before drawing set source and target
		{
			glBindFramebuffer(GL_FRAMEBUFFER, g_glVRAMFramebuffer);
			
			// setup draw and read framebuffers
			glBindFramebuffer(GL_READ_FRAMEBUFFER, g_glOffscreenFramebuffer);					// source is backbuffer
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_glVRAMFramebuffer);

			glBlitFramebuffer(0, 0, g_PreviousOffscreen.w, g_PreviousOffscreen.h, 
								g_PreviousOffscreen.x, g_PreviousOffscreen.y + g_PreviousOffscreen.h, g_PreviousOffscreen.x + g_PreviousOffscreen.w, g_PreviousOffscreen.y,
								GL_COLOR_BUFFER_BIT, GL_NEAREST);

			// done, unbind
			glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		}
#endif
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// copy rendering results to VRAM texture
		{
			// reat the texture
			glBindTexture(GL_TEXTURE_2D, g_offscreenRTTexture);
			//glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			PBO_Download(g_glOffscreenPBO);
			glBindTexture(GL_TEXTURE_2D, g_lastBoundTexture);

			// Don't forcely update VRAM
			GR_CopyRGBAFramebufferToVRAM((u_int*)g_glOffscreenPBO.pixels, 
				g_PreviousOffscreen.x, g_PreviousOffscreen.y, g_PreviousOffscreen.w, g_PreviousOffscreen.h, 
				USE_OFFSCREEN_BLIT == 0, 1);
		}

	}
#endif
}

void GR_StoreFrameBuffer(int x, int y, int w, int h)
{
#if defined(RENDERER_OGL) || defined(OGLES)
	// set storage size first
	if (g_PreviousFramebuffer.w != w &&
		g_PreviousFramebuffer.h != h)
	{
		//PBO_Destroy(g_glFBPBO);
		//PBO_Init(g_glFBPBO, GL_RGBA, w, h, 1);
		
		glBindTexture(GL_TEXTURE_2D, g_fbTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	g_PreviousFramebuffer.x = x;
	g_PreviousFramebuffer.y = y;
	g_PreviousFramebuffer.w = w;
	g_PreviousFramebuffer.h = h;

	glBindFramebuffer(GL_FRAMEBUFFER, g_glBlitFramebuffer);

	// before drawing set source and target
	{
		// setup draw and read framebuffers
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);					// source is backbuffer
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_glBlitFramebuffer);

		glBlitFramebuffer(0, 0, g_windowWidth, g_windowHeight, x, y + h, x + w, y, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		// Blit framebuffer to VRAM screen area
#if USE_FRAMEBUFFER_BLIT
		// before drawing set source and target
		glBindFramebuffer(GL_FRAMEBUFFER, g_glVRAMFramebuffer);

		// setup draw and read framebuffers
		glBindFramebuffer(GL_READ_FRAMEBUFFER, g_glBlitFramebuffer);					// source is backbuffer
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_glVRAMFramebuffer);

		glBlitFramebuffer(0, 0, w, h,
			x, y + h, x + w, y,
			GL_COLOR_BUFFER_BIT, GL_NEAREST);
#endif
		
		// done, unbind
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	// after drawing
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glFlush();

	GR_ReadFramebufferDataToVRAM();
#endif
}

void GR_CopyVRAM(unsigned short* src, int x, int y, int w, int h, int dst_x, int dst_y)
{
	vram_need_update = true;

	int stride = w;

	if (!src)
	{
		framebuffer_need_update = true;

		src = vram;
		stride = VRAM_WIDTH;
	}

	src += x + y * stride;

	unsigned short* dst = vram + dst_x + dst_y * VRAM_WIDTH;

	for (int i = 0; i < h; i++) {
		SDL_memcpy(dst, src, w * sizeof(short));
		dst += VRAM_WIDTH;
		src += stride;
	}
}

void GR_ReadVRAM(unsigned short* dst, int x, int y, int dst_w, int dst_h)
{
	unsigned short* src = vram + x + VRAM_WIDTH * y;

	for (int i = 0; i < dst_h; i++) {
		SDL_memcpy(dst, src, dst_w * sizeof(short));
		dst += dst_w;
		src += VRAM_WIDTH;
	}
}

void GR_UpdateVRAM()
{
	if (!vram_need_update)
		return;

	vram_need_update = false;

#if defined(RENDERER_OGL) || defined(OGLES)
	glBindTexture(GL_TEXTURE_2D, g_vramTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, VRAM_FORMAT, GL_UNSIGNED_BYTE, vram);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, VRAM_WIDTH, VRAM_HEIGHT, VRAM_FORMAT, GL_UNSIGNED_BYTE, vram);
#endif
}

void GR_SwapWindow()
{
#if defined(RENDERER_OGL)
	SDL_GL_SwapWindow(g_window);
#elif defined(OGLES)
	eglSwapBuffers(eglDisplay, eglSurface);
#endif

	//glFinish();
}

void GR_EnableDepth(int enable)
{
	if (g_PreviousDepthMode == enable)
		return;

	g_PreviousDepthMode = enable;

#if defined(RENDERER_OGL) || defined(OGLES)
	if (enable && g_pgxpZBuffer)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
#endif
}

void GR_SetStencilMode(int drawPrim)
{
	if (g_PreviousStencilMode == drawPrim)
		return;

	g_PreviousStencilMode = drawPrim;

#if defined(RENDERER_OGL) || defined(OGLES)
	if (drawPrim)
	{
		glStencilFunc(GL_ALWAYS, 1, 0x10);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	}
	else
	{
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
	}
#endif
}

void GR_SetBlendMode(BlendMode blendMode)
{
	if (g_PreviousBlendMode == blendMode)
		return;

#if defined(RENDERER_OGL) || defined(OGLES)
	if (g_PreviousBlendMode == BM_NONE)
		glEnable(GL_BLEND);

	switch (blendMode)
	{
	case BM_NONE:
		glDisable(GL_BLEND);
		GR_EnableDepth(1);
		break;
	case BM_AVERAGE:
		glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_COLOR);
		glBlendEquation(GL_FUNC_ADD);
		GR_EnableDepth(0);
		break;
	case BM_ADD:
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);
		GR_EnableDepth(0);
		break;
	case BM_SUBTRACT:
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
		GR_EnableDepth(0);
		break;
	case BM_ADD_QUATER_SOURCE:
		glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);
		GR_EnableDepth(0);
		break;
	}
#endif

	g_PreviousBlendMode = blendMode;
}

void GR_SetPolygonOffset(float ofs)
{
#if defined(RENDERER_OGL) || defined(OGLES)
	if (ofs == 0.0f)
	{
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(0.0f, ofs);
	}
#endif
}

void GR_SetViewPort(int x, int y, int width, int height)
{
#if defined(RENDERER_OGL) || defined(OGLES)
	glViewport(x, y, width, height);
#endif
}

void GR_SetWireframe(bool enable)
{
#if defined(RENDERER_OGL)
	glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
#endif
}

void GR_UpdateVertexBuffer(const GrVertex* vertices, int num_vertices)
{
	assert(num_vertices <= MAX_NUM_POLY_BUFFER_VERTICES);
#if defined(RENDERER_OGL) || defined(OGLES)
	glBufferSubData(GL_ARRAY_BUFFER, 0, num_vertices * sizeof(GrVertex), vertices);
#else
#error
#endif
}

void GR_DrawTriangles(int start_vertex, int triangles)
{
#if defined(RENDERER_OGL) || defined(OGLES)
	glDrawArrays(GL_TRIANGLES, start_vertex, triangles * 3);
#else
#error
#endif
}
