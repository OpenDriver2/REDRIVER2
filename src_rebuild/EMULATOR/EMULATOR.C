#include "EMULATOR.H"

#include "EMULATOR_VERSION.H"
#include "EMULATOR_GLOBALS.H"
#include "EMULATOR_PRIVATE.H"
#include "CRASHHANDLER.H"

#include "EMULATOR_PLATFORM_SETUP.H"

#include "LIBGPU.H"
#include "LIBETC.H"
#include "LIBPAD.H"

//#include <stdio.h>
//#include <string.h>
#if !defined(__ANDROID__)
//#include <thread>
#endif
#include <assert.h>

#if defined(NTSC_VERSION)
#define FIXED_TIME_STEP    16		// 16.6667	= 60 FPS
#else
#define FIXED_TIME_STEP    20		// 20.0		= 50 FPS
#endif

#define SWAP_INTERVAL      1

#include <stdio.h>
#include <string.h>
#include <SDL.h>

SDL_Window* g_window = NULL;
TextureID vramTexture;
TextureID whiteTexture;

#if defined(OGLES) || defined(OGL)
	GLuint dynamic_vertex_buffer;
	GLuint dynamic_vertex_array;
#elif defined(D3D9)
	IDirect3DVertexBuffer9 *dynamic_vertex_buffer = NULL;
	IDirect3D9             *d3d;
	IDirect3DDevice9       *d3ddev;
	D3DPRESENT_PARAMETERS  d3dpp;
#endif

int windowWidth = 0;
int windowHeight = 0;
char* pVirtualMemory = NULL;
SysCounter counters[3] = { 0 };
#if !defined(__ANDROID__)
//std::thread counter_thread;
#endif

unsigned int g_swapTime;
int g_swapInterval = SWAP_INTERVAL;
int g_wireframeMode = 0;
int g_texturelessMode = 0;
int g_emulatorPaused = 0;
int g_polygonSelected = 0;
int g_pgxpTextureCorrection = 1;
TextureID g_lastBoundTexture;

void Emulator_ResetDevice()
{
#if defined(OGLES) || defined(OGL)
	SDL_GL_SetSwapInterval(g_swapInterval);
#elif defined(D3D9)
	if (dynamic_vertex_buffer) {
		dynamic_vertex_buffer->Release();
		dynamic_vertex_buffer = NULL;
	}

	d3dpp.PresentationInterval = g_swapInterval ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.BackBufferWidth      = windowWidth;
	d3dpp.BackBufferHeight     = windowHeight;
	HRESULT hr = d3ddev->Reset(&d3dpp);
	assert(!FAILED(hr));

	hr = d3ddev->CreateVertexBuffer(sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, &dynamic_vertex_buffer, NULL);
	assert(!FAILED(hr));

	d3ddev->SetRenderState(D3DRS_ZENABLE,  D3DZB_FALSE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
#endif
}

#if defined(D3D9)
static int Emulator_InitialiseD3D9Context(char* windowName)
{
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window!\n");
		return FALSE;
	}

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(g_window, &wmInfo);

	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.Windowed               = TRUE;
	d3dpp.BackBufferCount        = 1;
	d3dpp.BackBufferFormat       = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth        = windowWidth;
	d3dpp.BackBufferHeight       = windowHeight;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow          = wmInfo.info.win.window;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_ONE;

	d3d =  Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) {
		eprinterr("Failed to initialise D3D\n");
		return FALSE;
	}

	HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	if (FAILED(hr)) {
		eprinterr("Failed to obtain D3D9 device!\n");
		return FALSE;
	}

	return TRUE;
}
#endif

static int Emulator_InitialiseGLContext(char* windowName)
{
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

#if defined(OGL)
	SDL_GL_CreateContext(g_window);
#endif

	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window or GL context!\n");
		return FALSE;
	}

	return TRUE;
}

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

static int Emulator_InitialiseGLESContext(char* windowName)
{
	unsigned int windowFlags = SDL_WINDOW_OPENGL;

#if defined(__ANDROID__)
	windowFlags |= SDL_WINDOW_FULLSCREEN;
#endif

    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, windowFlags);

	if(g_window == NULL)
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

#endif

static int Emulator_InitialiseSDL(char* windowName, int width, int height)
{
	windowWidth  = width;
	windowHeight = height;

	//Initialise SDL2
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
#if !defined(RO_DOUBLE_BUFFERED)
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
#endif

#if defined(OGLES)

#if defined(__ANDROID__)
        //Override to full screen.
        SDL_DisplayMode displayMode;
        if(SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
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
#elif defined(OGL)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
	}
	else
	{
		eprinterr("Error: Failed to initialise SDL\n");
		return FALSE;
	}

#if defined(OGL)
	if (Emulator_InitialiseGLContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise GL Context!\n");
		return FALSE;
	}
#elif defined(OGLES)
	if (Emulator_InitialiseGLESContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise GLES Context!\n");
		return FALSE;
	}
#elif defined(D3D9)
	if (Emulator_InitialiseD3D9Context(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise D3D9 Context!\n");
		return FALSE;
	}
#endif

	return TRUE;
}

static int Emulator_InitialiseGLEW()
{
#if defined(GLEW)
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		return FALSE;
	}
#endif
	return TRUE;
}

SDL_Thread* g_vblankThread = NULL;
SDL_mutex* g_vblankMutex = NULL;
volatile bool g_stopVblank = false;
volatile int g_vblanksDone = 0;
volatile int g_lastVblankCnt = 0;

extern void(*vsync_callback)(void);

int Emulator_DoVSyncCallback()
{
	SDL_LockMutex(g_vblankMutex);

	int vblcnt = g_vblanksDone - g_lastVblankCnt;

	static bool canDoCb = true;

	if (canDoCb && vsync_callback)	// prevent recursive calls
	{
		canDoCb = false;

		// do vblank callbacks
		int i = vblcnt;
		while (i)
		{
			vsync_callback();
			i--;
		}

		canDoCb = true;
	}

	g_lastVblankCnt = g_vblanksDone;

	SDL_UnlockMutex(g_vblankMutex);

	if (g_swapInterval == 0)
	{
		// extra speedup.
		// does not affect `vsync_callback` count
		g_vblanksDone += 200;
		g_lastVblankCnt += 200;
	}

	return g_vblanksDone;
}

int vblankThreadMain(void* data)
{
	int vblankTime = SDL_GetTicks();

	do
	{
		int delta = vblankTime + FIXED_TIME_STEP - SDL_GetTicks();

		if (delta < 0)
		{
			// do vblank events
			SDL_LockMutex(g_vblankMutex);

			g_vblanksDone++;
			vblankTime = SDL_GetTicks();

			SDL_UnlockMutex(g_vblankMutex);
		}
	} while (!g_stopVblank);

	return 0;
}

static int Emulator_InitialiseCore()
{
	g_vblankThread = SDL_CreateThread(vblankThreadMain, "vbl", NULL);

	if (NULL == g_vblankThread)
	{
		eprintf("SDL_CreateThread failed: %s\n", SDL_GetError());
		return FALSE;
	}

	g_vblankMutex = SDL_CreateMutex();
	if (NULL == g_vblankMutex)
	{
		eprintf("SDL_CreateMutex failed: %s\n", SDL_GetError());
		return FALSE;
	}

	return TRUE;
}

void Emulator_Initialise(char* windowName, int width, int height)
{
	eprintf("Initialising Emulator.\n");
	eprintf("VERSION: %d.%d\n", EMULATOR_MAJOR_VERSION, EMULATOR_MINOR_VERSION);
	eprintf("Compile Date: %s Time: %s\n", EMULATOR_COMPILE_DATE, EMULATOR_COMPILE_TIME);

	if (Emulator_InitialiseSDL(windowName, width, height) == FALSE)
	{
		eprinterr("Failed to Intialise SDL\n");
		Emulator_ShutDown();
	}

#if defined(GLEW)
	if (Emulator_InitialiseGLEW() == FALSE)
	{
		eprinterr("Failed to Intialise GLEW\n");
		Emulator_ShutDown();
	}
#endif

	if (Emulator_InitialiseCore() == FALSE)
	{
		eprinterr("Failed to Intialise Emulator Core.\n");
		Emulator_ShutDown();
	}

	if (Emulator_Initialise() == FALSE)
	{
		eprinterr("Failed to Intialise GL.\n");
		Emulator_ShutDown();
	}

	g_swapTime = SDL_GetTicks() - FIXED_TIME_STEP;
}

void Emulator_GetScreenSize(int& screenWidth, int& screenHeight)
{
	SDL_GetWindowSize(g_window, &screenWidth, &screenHeight);
}

void Emulator_GenerateLineArray(struct Vertex* vertex, VERTTYPE* p0, VERTTYPE* p1, ushort gteidx)
{
	// swap line coordinates for left-to-right and up-to-bottom direction
	if (p0[0] > p1[0]) {
		VERTTYPE *tmp = p0;
		p0 = p1;
		p1 = tmp;
	} else if (p0[0] == p1[0]) {
		 if (p0[1] > p1[1]) {
			 VERTTYPE *tmp = p0;
			p0 = p1;
			p1 = tmp;
		 }
	}

	VERTTYPE dx = p1[0] - p0[0];
	VERTTYPE dy = p1[1] - p0[1];

	float ofsX = activeDrawEnv.ofs[0] % activeDispEnv.disp.w;
	float ofsY = activeDrawEnv.ofs[1] % activeDispEnv.disp.h;

	if (dx > abs(dy)) { // horizontal
		vertex[0].x = p0[0] + ofsX;
		vertex[0].y = p0[1] + ofsY;

		vertex[1].x = p1[0] + ofsX + 1;
		vertex[1].y = p1[1] + ofsY;

		vertex[2].x = vertex[1].x;
		vertex[2].y = vertex[1].y + 1;

		vertex[3].x = vertex[0].x;
		vertex[3].y = vertex[0].y + 1;
	} else { // vertical
		vertex[0].x = p0[0] + ofsX;
		vertex[0].y = p0[1] + ofsY;

		vertex[1].x = p1[0] + ofsX;
		vertex[1].y = p1[1] + ofsY + 1;

		vertex[2].x = vertex[1].x + 1;
		vertex[2].y = vertex[1].y;

		vertex[3].x = vertex[0].x + 1;
		vertex[3].y = vertex[0].y;
	} // TODO diagonal line alignment

#ifdef PGXP
	vertex[0].w = vertex[1].w = vertex[2].w = vertex[3].w = 1.0f;
	vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;
#endif
}

#ifdef PGXP

#define PGXP_APPLY(v, p) \
{\
	uint lookup = PGXP_LOOKUP_VALUE(p[0], p[1]);		\
	PGXPVData vd;									\
	if(g_pgxpTextureCorrection && PGXP_GetCacheData(vd, lookup, gteidx)) {		\
		v.x = vd.px + ofsX;\
		v.y = vd.py + ofsY;\
		v.w = vd.pz;\
		v.z = 0.0f;\
	} else { \
		v.w = 1.0f; \
		v.z = 0.0f; \
	}\
}

#else

#define PGXP_APPLY(v, p)

#endif

void Emulator_GenerateVertexArrayTriangle(struct Vertex* vertex, VERTTYPE* p0, VERTTYPE* p1, VERTTYPE* p2, ushort gteidx)
{
	assert(p0);
	assert(p1);
	assert(p2);

	float ofsX = activeDrawEnv.ofs[0] % activeDispEnv.disp.w;
	float ofsY = activeDrawEnv.ofs[1] % activeDispEnv.disp.h;

	vertex[0].x = p0[0] + ofsX;
	vertex[0].y = p0[1] + ofsY;

	vertex[1].x = p1[0] + ofsX;
	vertex[1].y = p1[1] + ofsY;

	vertex[2].x = p2[0] + ofsX;
	vertex[2].y = p2[1] + ofsY;

	PGXP_APPLY(vertex[0], p0);
	PGXP_APPLY(vertex[1], p1);
	PGXP_APPLY(vertex[2], p2);
}

void Emulator_GenerateVertexArrayQuad(struct Vertex* vertex, VERTTYPE* p0, VERTTYPE* p1, VERTTYPE* p2, VERTTYPE* p3, ushort gteidx)
{
	assert(p0);
	assert(p1);
	assert(p2);
	assert(p3);

	float ofsX = activeDrawEnv.ofs[0] % activeDispEnv.disp.w;
	float ofsY = activeDrawEnv.ofs[1] % activeDispEnv.disp.h;

	vertex[0].x = p0[0] + ofsX;
	vertex[0].y = p0[1] + ofsY;

	vertex[1].x = p1[0] + ofsX;
	vertex[1].y = p1[1] + ofsY;

	vertex[2].x = p2[0] + ofsX;
	vertex[2].y = p2[1] + ofsY;

	vertex[3].x = p3[0] + ofsX;
	vertex[3].y = p3[1] + ofsY;

	PGXP_APPLY(vertex[0], p0);
	PGXP_APPLY(vertex[1], p1);
	PGXP_APPLY(vertex[2], p2);
	PGXP_APPLY(vertex[3], p3);
}

void Emulator_GenerateVertexArrayRect(struct Vertex* vertex, VERTTYPE* p0, short w, short h, ushort gteidx)
{
	assert(p0);

	float ofsX = activeDrawEnv.ofs[0] % activeDispEnv.disp.w;
	float ofsY = activeDrawEnv.ofs[1] % activeDispEnv.disp.h;

	vertex[0].x = p0[0] + ofsX;
	vertex[0].y = p0[1] + ofsY;

	vertex[1].x = vertex[0].x;
	vertex[1].y = vertex[0].y + h;

	vertex[2].x = vertex[0].x + w;
	vertex[2].y = vertex[0].y + h;

	vertex[3].x = vertex[0].x + w;
	vertex[3].y = vertex[0].y;

#ifdef PGXP
	vertex[1].w = vertex[2].w = vertex[3].w = vertex[0].w = 1.0f;
	vertex[1].z = vertex[2].z = vertex[3].z = vertex[0].z = 0.0f;
#endif
}

void Emulator_GenerateTexcoordArrayQuad(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short page, short clut, unsigned char dither)
{
	assert(uv0);
	assert(uv1);
	assert(uv2);
	assert(uv3);

	const unsigned char bright = 2;

	vertex[0].u      = uv0[0];
	vertex[0].v      = uv0[1];
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = page;
	vertex[0].clut   = clut;

	vertex[1].u      = uv1[0];
	vertex[1].v      = uv1[1];
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = page;
	vertex[1].clut   = clut;

	vertex[2].u      = uv2[0];
	vertex[2].v      = uv2[1];
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = page;
	vertex[2].clut   = clut;

	vertex[3].u      = uv3[0];
	vertex[3].v      = uv3[1];
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = page;
	vertex[3].clut   = clut;
}

void Emulator_GenerateTexcoordArrayTriangle(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, short page, short clut, unsigned char dither)
{
	assert(uv0);
	assert(uv1);
	assert(uv2);

	const unsigned char bright = 2;

	vertex[0].u      = uv0[0];
	vertex[0].v      = uv0[1];
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = page;
	vertex[0].clut   = clut;

	vertex[1].u      = uv1[0];
	vertex[1].v      = uv1[1];
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = page;
	vertex[1].clut   = clut;

	vertex[2].u      = uv2[0];
	vertex[2].v      = uv2[1];
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = page;
	vertex[2].clut   = clut;
}

void Emulator_GenerateTexcoordArrayRect(struct Vertex* vertex, unsigned char* uv, short page, short clut, short w, short h)
{
	assert(uv);
	//assert(int(uv[0]) + w <= 255);
	//assert(int(uv[1]) + h <= 255);
	// TODO
	if (int(uv[0]) + w > 255) w = 255 - uv[0];
	if (int(uv[1]) + h > 255) h = 255 - uv[1];

	const unsigned char bright = 2;
	const unsigned char dither = 0;

	vertex[0].u      = uv[0];
	vertex[0].v      = uv[1];
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = page;
	vertex[0].clut   = clut;

	vertex[1].u      = uv[0];
	vertex[1].v      = uv[1] + h;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = page;
	vertex[1].clut   = clut;

	vertex[2].u      = uv[0] + w;
	vertex[2].v      = uv[1] + h;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = page;
	vertex[2].clut   = clut;

	vertex[3].u      = uv[0] + w;
	vertex[3].v      = uv[1];
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = page;
	vertex[3].clut   = clut;
}

void Emulator_GenerateTexcoordArrayLineZero(struct Vertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u      = 0;
	vertex[0].v      = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = 0;
	vertex[0].clut   = 0;

	vertex[1].u      = 0;
	vertex[1].v      = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = 0;
	vertex[1].clut   = 0;

	vertex[2].u      = 0;
	vertex[2].v      = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = 0;
	vertex[2].clut   = 0;

	vertex[3].u      = 0;
	vertex[3].v      = 0;
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = 0;
	vertex[3].clut   = 0;
}

void Emulator_GenerateTexcoordArrayTriangleZero(struct Vertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u      = 0;
	vertex[0].v      = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = 0;
	vertex[0].clut   = 0;

	vertex[1].u      = 0;
	vertex[1].v      = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = 0;
	vertex[1].clut   = 0;

	vertex[2].u      = 0;
	vertex[2].v      = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = 0;
	vertex[2].clut   = 0;

}

void Emulator_GenerateTexcoordArrayQuadZero(struct Vertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u      = 0;
	vertex[0].v      = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = 0;
	vertex[0].clut   = 0;

	vertex[1].u      = 0;
	vertex[1].v      = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = 0;
	vertex[1].clut   = 0;

	vertex[2].u      = 0;
	vertex[2].v      = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = 0;
	vertex[2].clut   = 0;

	vertex[3].u      = 0;
	vertex[3].v      = 0;
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = 0;
	vertex[3].clut   = 0;
}

void Emulator_GenerateColourArrayLine(struct Vertex* vertex, unsigned char* col0, unsigned char* col1)
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

void Emulator_GenerateColourArrayTriangle(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2)
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

void Emulator_GenerateColourArrayQuad(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3)
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

ShaderID g_gte_shader_4;
ShaderID g_gte_shader_8;
ShaderID g_gte_shader_16;
ShaderID g_blit_shader;

#if defined(OGLES) || defined(OGL)
GLint u_Projection;


#define GTE_PACK_RG\
	"		float color_16 = (color_rg.y * 256.0 + color_rg.x) * 255.0;\n"

#define GTE_DISCARD\
	"		if (color_16 == 0.0) { discard; }\n"

#define GTE_DECODE_RG\
	"		fragColor = fract(floor(color_16 / vec4(1.0, 32.0, 1024.0, 32768.0)) / 32.0);\n"

#define GTE_DITHERING\
	"		fragColor *= v_color;\n"\
	"		mat4 dither = mat4(\n"\
	"			-4.0,  +0.0,  -3.0,  +1.0,\n"\
	"			+2.0,  -2.0,  +3.0,  -1.0,\n"\
	"			-3.0,  +1.0,  -4.0,  +0.0,\n"\
	"			+3.0,  -1.0,  +2.0,  -2.0) / 255.0;\n"\
	"		ivec2 dc = ivec2(fract(gl_FragCoord.xy / 4.0) * 4.0);\n"\
	"		fragColor.xyz += vec3(dither[dc.x][dc.y] * v_texcoord.w);\n"


#if (VRAM_FORMAT == GL_LUMINANCE_ALPHA)
	#define GTE_FETCH_VRAM_FUNC\
		"	uniform sampler2D s_texture;\n"\
		"	vec2 VRAM(vec2 uv) { return texture2D(s_texture, uv).ra; }\n"
#else
	#define GTE_FETCH_VRAM_FUNC\
		"	uniform sampler2D s_texture;\n"\
		"	vec2 VRAM(vec2 uv) { return texture2D(s_texture, uv).rg; }\n"
#endif

#ifdef PGXP
#define GTE_PERSPECTIVE_CORRECTION \
		"	vec4 fragPosition = Projection * vec4(a_position.xy, a_z, 1.0) * a_w;\n"\
		"	gl_Position = fragPosition;\n"
#else
#define GTE_PERSPECTIVE_CORRECTION
		"	gl_Position = Projection * vec4(a_position.xy, 0.0, 1.0);\n"
#endif

const char* gte_shader_4 =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"varying vec4 v_page_clut;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
	"	attribute vec4 a_color;\n"
	"	attribute float a_z;\n"
	"	attribute float a_w;\n"
	"	uniform mat4 Projection;\n"
	"	void main() {\n"
	"		v_texcoord = a_texcoord;\n"
	"		v_color = a_color;\n"
	"		v_color.xyz *= a_texcoord.z;\n"
	"		v_page_clut.x = fract(a_position.z / 16.0) * 1024.0;\n"
	"		v_page_clut.y = floor(a_position.z / 16.0) * 256.0;\n"
	"		v_page_clut.z = fract(a_position.w / 64.0);\n"
	"		v_page_clut.w = floor(a_position.w / 64.0) / 512.0;\n"
	GTE_PERSPECTIVE_CORRECTION
	"	}\n"
	"#else\n"
	GTE_FETCH_VRAM_FUNC
	"	void main() {\n"
	"		vec2 uv = (v_texcoord.xy * vec2(0.25, 1.0) + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
	"		vec2 comp = VRAM(uv);\n"
	"		int index = int(fract(v_texcoord.x / 4.0 + 0.0001) * 4.0);\n"
	"\n"
	"		float v = comp[index / 2] * (255.0 / 16.0);\n"
	"		float f = floor(v);\n"
	"\n"
	"		vec2 c = vec2( (v - f) * 16.0, f );\n"
	"\n"
	"		vec2 clut_pos = v_page_clut.zw;\n"
	"		clut_pos.x += mix(c[0], c[1], fract(float(index) / 2.0) * 2.0) / 1024.0;\n"
	"		vec2 color_rg = VRAM(clut_pos);\n"
	GTE_PACK_RG
	GTE_DISCARD
	GTE_DECODE_RG
	GTE_DITHERING
	"	}\n"
	"#endif\n";

const char* gte_shader_8 =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"varying vec4 v_page_clut;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
	"	attribute vec4 a_color;\n"
	"	attribute float a_z;\n"
	"	attribute float a_w;\n"
	"	uniform mat4 Projection;\n"
	"	void main() {\n"
	"		v_texcoord = a_texcoord;\n"
	"		v_color = a_color;\n"
	"		v_color.xyz *= a_texcoord.z;\n"
	"		v_page_clut.x = fract(a_position.z / 16.0) * 1024.0;\n"
	"		v_page_clut.y = floor(a_position.z / 16.0) * 256.0;\n"
	"		v_page_clut.z = fract(a_position.w / 64.0);\n"
	"		v_page_clut.w = floor(a_position.w / 64.0) / 512.0;\n"
	GTE_PERSPECTIVE_CORRECTION
	"	}\n"
	"#else\n"
	GTE_FETCH_VRAM_FUNC
	"	void main() {\n"
	"		vec2 uv = (v_texcoord.xy * vec2(0.5, 1.0) + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
	"		vec2 comp = VRAM(uv);\n"
	"\n"
	"		vec2 clut_pos = v_page_clut.zw;\n"
	"		clut_pos.x += comp[int(mod(v_texcoord.x, 2.0))] * 255.0 / 1024.0;\n"
	"		vec2 color_rg = VRAM(clut_pos);\n"
	GTE_PACK_RG
	GTE_DISCARD
	GTE_DECODE_RG
	GTE_DITHERING
	"	}\n"
	"#endif\n";

const char* gte_shader_16 =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
	"	attribute vec4 a_color;\n"
	"	attribute float a_z;\n"
	"	attribute float a_w;\n"
	"	uniform mat4 Projection;\n"
	"	void main() {\n"
	"		vec2 page\n;"
	"		page.x = fract(a_position.z / 16.0) * 1024.0\n;"
	"		page.y = floor(a_position.z / 16.0) * 256.0;\n;"
	"		v_texcoord = a_texcoord;\n"
	"		v_texcoord.xy += page;\n"
	"		v_texcoord.xy *= vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
	"		v_color = a_color;\n"
	"		v_color.xyz *= a_texcoord.z;\n"
	GTE_PERSPECTIVE_CORRECTION
	"	}\n"
	"#else\n"
	GTE_FETCH_VRAM_FUNC
	"	void main() {\n"
	"		vec2 color_rg = VRAM(v_texcoord.xy);\n"
	GTE_PACK_RG
	GTE_DISCARD
	GTE_DECODE_RG
	GTE_DITHERING
	"	}\n"
	"#endif\n";

const char* blit_shader =
	"varying vec4 v_texcoord;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord;\n"
	"	void main() {\n"
	"		v_texcoord = a_texcoord * vec4(8.0 / 1024.0, 8.0 / 512.0, 0.0, 0.0);\n"
	"		gl_Position = vec4(a_position.xy, 0.0, 1.0);\n"
	"	}\n"
	"#else\n"
	GTE_FETCH_VRAM_FUNC
	"	void main() {\n"
	"		vec2 color_rg = VRAM(v_texcoord.xy);\n"
	GTE_PACK_RG
	GTE_DECODE_RG
	"	}\n"
	"#endif\n";

void Shader_CheckShaderStatus(GLuint shader)
{
    char info[1024];
    glGetShaderInfoLog(shader, sizeof(info), NULL, info);
    if (info[0] && strlen(info) > 8)
    {
        eprinterr("%s\n", info);
        assert(false);
    }
}

void Shader_CheckProgramStatus(GLuint program)
{
    char info[1024];
    glGetProgramInfoLog(program, sizeof(info), NULL, info);
    if (info[0] && strlen(info) > 8)
    {
        eprinterr("%s\n", info);
        assert(false);
    }
}

ShaderID Shader_Compile(const char *source)
{
#if defined(ES2_SHADERS)
    const char *GLSL_HEADER_VERT =
        "#version 100\n"
        "precision lowp  int;\n"
        "precision highp float;\n"
        "#define VERTEX\n";

    const char *GLSL_HEADER_FRAG =
        "#version 100\n"
        "precision lowp  int;\n"
        "precision highp float;\n"
        "#define fragColor gl_FragColor\n";
#elif defined(ES3_SHADERS)
    const char *GLSL_HEADER_VERT =
        "#version 300 es\n"
        "precision lowp  int;\n"
        "precision highp float;\n"
        "#define VERTEX\n"
        "#define varying   out\n"
        "#define attribute in\n"
        "#define texture2D texture\n";

    const char *GLSL_HEADER_FRAG =
        "#version 300 es\n"
        "precision lowp  int;\n"
        "precision highp float;\n"
        "#define varying     in\n"
        "#define texture2D   texture\n"
        "out vec4 fragColor;\n";
#else
    const char *GLSL_HEADER_VERT =
        "#version 330\n"
        "#define VERTEX\n"
        "#define varying   out\n"
        "#define attribute in\n"
        "#define texture2D texture\n";

    const char *GLSL_HEADER_FRAG =
        "#version 330\n"
        "#define varying     in\n"
        "#define texture2D   texture\n"
        "out vec4 fragColor;\n";
#endif

    const char *vs_list[] = { GLSL_HEADER_VERT, source };
    const char *fs_list[] = { GLSL_HEADER_FRAG, source };

    GLuint program = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 2, vs_list, NULL);
    glCompileShader(vertexShader);
    Shader_CheckShaderStatus(vertexShader);
    glAttachShader(program, vertexShader);
    glDeleteShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 2, fs_list, NULL);
    glCompileShader(fragmentShader);
    Shader_CheckShaderStatus(fragmentShader);
    glAttachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    glBindAttribLocation(program, a_position, "a_position");
    glBindAttribLocation(program, a_texcoord, "a_texcoord");
    glBindAttribLocation(program, a_color,    "a_color");

#ifdef PGXP
	glBindAttribLocation(program, a_z, "a_z");
	glBindAttribLocation(program, a_w, "a_w");
#endif

    glLinkProgram(program);
    Shader_CheckProgramStatus(program);

    GLint sampler = 0;
    glUseProgram(program);
    glUniform1iv(glGetUniformLocation(program, "s_texture"), 1, &sampler);
    glUseProgram(0);

    return program;
}
#elif defined(D3D9)

#include "shaders/gte_shader_4_vs.h"
#include "shaders/gte_shader_4_ps.h"
#include "shaders/gte_shader_8_vs.h"
#include "shaders/gte_shader_8_ps.h"
#include "shaders/gte_shader_16_vs.h"
#include "shaders/gte_shader_16_ps.h"
#include "shaders/blit_shader_vs.h"
#include "shaders/blit_shader_ps.h"

// shader registers
const int u_Projection = 0;

LPDIRECT3DVERTEXDECLARATION9 vertexDecl;

#define Shader_Compile(name) Shader_Compile_Internal((DWORD*)name##_vs, (DWORD*)name##_ps)

ShaderID Shader_Compile_Internal(const DWORD *vs_data, const DWORD *ps_data)
{
	ShaderID shader;
	HRESULT hr;
	hr = d3ddev->CreateVertexShader(vs_data, &shader.VS);
	assert(!FAILED(hr));
	hr = d3ddev->CreatePixelShader(ps_data, &shader.PS);
	assert(!FAILED(hr));
	return shader;
}
#else
    #error
#endif

void Emulator_CreateGlobalShaders()
{
	g_gte_shader_4  = Shader_Compile(gte_shader_4);
	g_gte_shader_8  = Shader_Compile(gte_shader_8);
	g_gte_shader_16 = Shader_Compile(gte_shader_16);
	g_blit_shader   = Shader_Compile(blit_shader);

#if defined(OGL) || defined(OGLES)
	u_Projection = glGetUniformLocation(g_gte_shader_4, "Projection");
#endif
}

unsigned short vram[VRAM_WIDTH * VRAM_HEIGHT];

void Emulator_GenerateCommonTextures()
{
	unsigned int pixelData = 0xFFFFFFFF;
#if defined(OGL) || defined(OGLES)
	glGenTextures(1, &whiteTexture);
	glBindTexture(GL_TEXTURE_2D, whiteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData);
	glBindTexture(GL_TEXTURE_2D, 0);
#elif defined(D3D9)
	HRESULT hr = d3ddev->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &whiteTexture, NULL);
	assert(!FAILED(hr));
	D3DLOCKED_RECT rect;
	hr = whiteTexture->LockRect(0, &rect, NULL, 0);
	assert(!FAILED(hr));
	memcpy(rect.pBits, &pixelData, sizeof(pixelData));
	whiteTexture->UnlockRect(0);
#endif
}

int Emulator_Initialise()
{
	SDL_memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));
	Emulator_GenerateCommonTextures();
	Emulator_CreateGlobalShaders();

#if defined(OGL) || defined(OGLES)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendColor(0.5f, 0.5f, 0.5f, 0.25f);

	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, VRAM_INTERNAL_FORMAT, VRAM_WIDTH, VRAM_HEIGHT, 0, VRAM_FORMAT, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &dynamic_vertex_buffer);
	glGenVertexArrays(1, &dynamic_vertex_array);
	glBindVertexArray(dynamic_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, dynamic_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);
	
    glEnableVertexAttribArray(a_color);
#if defined(PGXP)
	glVertexAttribPointer(a_position, 4, GL_FLOAT,         GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->x);

	glVertexAttribPointer(a_z, 1,		 GL_FLOAT,		   GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->z);
	glVertexAttribPointer(a_w, 1,		 GL_FLOAT,		   GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->w);

	glEnableVertexAttribArray(a_z);
	glEnableVertexAttribArray(a_w);
#else
	glVertexAttribPointer(a_position, 4, GL_SHORT,         GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->x);
#endif
	glVertexAttribPointer(a_texcoord, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->u);
	glVertexAttribPointer(a_color,    4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(Vertex), &((Vertex*)NULL)->r);
	glBindVertexArray(0);
#elif defined(D3D9)
	if (FAILED(d3ddev->CreateTexture(VRAM_WIDTH, VRAM_HEIGHT, 1, 0, D3DFMT_A8L8, D3DPOOL_MANAGED, &vramTexture, NULL)))
	{
		eprinterr("Failed to create render target texture!\n");
		return FALSE;
	}

	#define OFFSETOF(T, E)     ((size_t)&(((T*)0)->E))

	const D3DVERTEXELEMENT9 VERTEX_DECL[] = {
#if defined(PGXP)
		{0, OFFSETOF(Vertex, x), D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // a_position
#else
		{0, OFFSETOF(Vertex, x), D3DDECLTYPE_SHORT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // a_position
#endif
		{0, OFFSETOF(Vertex, u), D3DDECLTYPE_UBYTE4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0}, // a_texcoord
		{0, OFFSETOF(Vertex, r), D3DDECLTYPE_UBYTE4N,  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0}, // a_color
		D3DDECL_END()
	};

	d3ddev->CreateVertexDeclaration(VERTEX_DECL, &vertexDecl);

	#undef OFFSETOF
#else
	#error
#endif

	Emulator_ResetDevice();

    return TRUE;
}

void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
{
	float a = 2.0f / (right - left);
	float b = 2.0f / (top - bottom);
	float c = 2.0f / (znear - zfar);

	float x = (left + right) / (left - right);
	float y = (bottom + top) / (bottom - top);

#if defined(OGL) || defined(OGLES) // -1..1
	float z = (znear + zfar) / (znear - zfar);
#elif defined(D3D9) // 0..1
	float z = znear / (znear - zfar);
#endif

	float ortho[16] = {
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		x, y, z, 1
	};

#if defined(OGL) || defined(OGLES)
	glUniformMatrix4fv(u_Projection, 1, GL_FALSE, ortho);
#elif defined(D3D9)
	d3ddev->SetVertexShaderConstantF(u_Projection, ortho, 4);
#endif
}

void Emulator_SetupClipMode(const RECT16& rect)
{
	bool enabled = rect.x - activeDispEnv.disp.x > 0 ||
		rect.y - activeDispEnv.disp.y > 0 ||
		rect.w < activeDispEnv.disp.w - 1 ||
		rect.h < activeDispEnv.disp.h - 1;

	float clipRectX = (float)(rect.x - activeDispEnv.disp.x) / (float)activeDispEnv.disp.w;
	float clipRectY = (float)(rect.y - activeDispEnv.disp.y) / (float)activeDispEnv.disp.h;
	float clipRectW = (float)(rect.w) / (float)activeDispEnv.disp.w;
	float clipRectH = (float)(rect.h) / (float)activeDispEnv.disp.h;



#if defined(OGL) || defined(OGLES)
	if (!enabled)
	{
		glDisable(GL_SCISSOR_TEST);
		return;
	}

	float flipOffset = windowHeight - clipRectH * (float)windowHeight;

	glEnable(GL_SCISSOR_TEST);
	glScissor(clipRectX * (float)windowWidth, 
			  flipOffset - clipRectY * (float)windowHeight, 
		      clipRectW * (float)windowWidth,
		      clipRectH * (float)windowHeight);
#elif defined(D3D9)

#endif
}

void Emulator_SetShader(const ShaderID &shader)
{
#if defined(OGL) || defined(OGLES)
	glUseProgram(shader);
#elif defined(D3D9)
	d3ddev->SetVertexShader(shader.VS);
	d3ddev->SetPixelShader(shader.PS);
#else
	#error
#endif

	Emulator_Ortho2D(0.0f, activeDispEnv.disp.w, activeDispEnv.disp.h, 0, -1.0f, 1.0f);
}

void Emulator_SetTexture(TextureID texture, TexFormat texFormat)
{
	switch (texFormat)
	{
		case TF_4_BIT :
			Emulator_SetShader(g_gte_shader_4);
			break;
		case TF_8_BIT :
			Emulator_SetShader(g_gte_shader_8);
			break;
		case TF_16_BIT :
			Emulator_SetShader(g_gte_shader_16);
			break;
	}

	if (g_texturelessMode) {
		texture = whiteTexture;
	}

	if (g_lastBoundTexture == texture) {
		return;
	}

#if defined(OGL) || defined(OGLES)
	glBindTexture(GL_TEXTURE_2D, texture);
#elif defined(D3D9)
	d3ddev->SetTexture(0, texture);
#endif

	g_lastBoundTexture = texture;
}

void Emulator_DestroyTexture(TextureID texture)
{
#if defined(OGL) || defined(OGLES)
    glDeleteTextures(1, &texture);
#elif defined(D3D9)
    texture->Release();
#else
    #error
#endif
}

extern void Emulator_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
// TODO clear rect if it's necessary
#if defined(OGL) || defined(OGLES)
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
#elif defined(D3D9)
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000 | (r << 16) | (g << 8) | (b), 1.0f, 0);
#endif
}

#define NOFILE 0

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)

void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer)
{
#if NOFILE
	return;
#endif

#if defined(OGL) || defined(OGLES)
	FILE* f = fopen(outputFileName, "wb");
	if (f == NULL)
	{
		return;
	}

	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6];
	header[0] = (width % 256);
	header[1] = (width / 256);
	header[2] = (height % 256);
	header[3] = (height / 256);
	header[4] = 16;
	header[5] = 0;

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);

	//512 const is hdd sector size
	int numSectorsToWrite = (width * height * sizeof(unsigned short)) / 512;
	int numRemainingSectorsToWrite = (width * height * sizeof(unsigned short)) % 512;

	for (int i = 0; i < numSectorsToWrite; i++)
	{
		fwrite(&vram[i * 512 / sizeof(unsigned short)], 512, 1, f);
	}

	for (int i = 0; i < numRemainingSectorsToWrite; i++)
	{
		fwrite(&vram[numSectorsToWrite * 512 / sizeof(unsigned short)], numRemainingSectorsToWrite, 1, f);
	}

	fclose(f);

#elif defined(D3D9)
	//D3DXSaveSurfaceToFile(outputFileName, D3DXIFF_TGA, vramFrameBuffer, NULL, NULL);
#endif
}
#endif

bool vram_need_update = true;

void Emulator_StoreFrameBuffer(int x, int y, int w, int h)
{
	short *fb = (short*)SDL_malloc(windowWidth * windowHeight * sizeof(short));

#if defined(OGL) || defined(OGLES)
	int *data = (int*)SDL_malloc(windowWidth * windowHeight * sizeof(int));
	glReadPixels(0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);

	#define FLIP_Y (h - fy - 1)
#elif defined(D3D9)
	IDirect3DSurface9 *srcSurface, *dstSurface;
	HRESULT hr;
	D3DLOCKED_RECT rect;
	hr = d3ddev->GetRenderTarget(0, &srcSurface);
	assert(!FAILED(hr));
	hr = d3ddev->CreateOffscreenPlainSurface(windowWidth, windowHeight, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &dstSurface, NULL);
	assert(!FAILED(hr));
	hr = d3ddev->GetRenderTargetData(srcSurface, dstSurface);
	assert(!FAILED(hr));
	hr = dstSurface->LockRect(&rect, NULL, D3DLOCK_READONLY);
	assert(!FAILED(hr));
	assert(windowWidth * 4 == rect.Pitch);

	int *data = (int*)rect.pBits;

	#define FLIP_Y (fy)
#endif

	unsigned int   *data_src = (unsigned int*)data;
	unsigned short *data_dst = (unsigned short*)fb;

	for (int i = 0; i < windowHeight; i++) {
		for (int j = 0; j < windowWidth; j++) {
			unsigned int  c = *data_src++;
			unsigned char b = ((c >>  3) & 0x1F);
			unsigned char g = ((c >> 11) & 0x1F);
			unsigned char r = ((c >> 19) & 0x1F);
			*data_dst++ = r | (g << 5) | (b << 10) | 0x8000;
		}
	}

#if defined(OGL) || defined(OGLES)
	SDL_free(data);
#elif defined(D3D9)
	dstSurface->UnlockRect();

	dstSurface->Release();
	srcSurface->Release();
#endif

	short *ptr = (short*)vram + VRAM_WIDTH * y + x;

	for (int fy = 0; fy < h; fy++) {
		short *fb_ptr = fb + (windowHeight * FLIP_Y / h) * windowWidth;

		for (int fx = 0; fx < w; fx++) {
			ptr[fx] = fb_ptr[windowWidth * fx / w];
		}

		ptr += VRAM_WIDTH;
	}

	#undef FLIP_Y

	SDL_free(fb);

	vram_need_update = true;
}

void Emulator_CopyVRAM(unsigned short *src, int x, int y, int w, int h, int dst_x, int dst_y)
{
	vram_need_update = true;

    int stride = w;

    if (!src) {
        src    = vram;
        stride = VRAM_WIDTH;
    }

    src += x + y * stride;

    unsigned short *dst = vram + dst_x + dst_y * VRAM_WIDTH;

    for (int i = 0; i < h; i++) {
        SDL_memcpy(dst, src, w * sizeof(short));
        dst += VRAM_WIDTH;
        src += stride;
    }
}

void Emulator_ReadVRAM(unsigned short *dst, int x, int y, int dst_w, int dst_h)
{
	unsigned short *src = vram + x + VRAM_WIDTH * y;

	for (int i = 0; i < dst_h; i++) {
		SDL_memcpy(dst, src, dst_w * sizeof(short));
		dst += dst_w;
		src += VRAM_WIDTH;
	}
}

void Emulator_UpdateVRAM()
{
	if (!vram_need_update) {
		return;
	}
	vram_need_update = false;

#if defined(OGL) || defined(OGLES)
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, VRAM_WIDTH, VRAM_HEIGHT, VRAM_FORMAT, GL_UNSIGNED_BYTE, vram);
#elif defined(D3D9)
	D3DLOCKED_RECT rect;
	HRESULT hr = vramTexture->LockRect(0, &rect, NULL, 0);
	assert(!FAILED(hr));
	memcpy(rect.pBits, vram, VRAM_WIDTH * VRAM_HEIGHT * sizeof(short));
	vramTexture->UnlockRect(0);
#endif
}

void Emulator_BlitVRAM()
{
	return; // is that needed?
	// FIXME: sorry, this does not work

	if (activeDispEnv.isinter)
	{
		//Emulator_StoreFrameBuffer(activeDispEnv.disp.x, activeDispEnv.disp.y, activeDispEnv.disp.w, activeDispEnv.disp.h);
		return;
	}

	Emulator_SetTexture(vramTexture, (TexFormat)-1);	// avoid shader setup
	Emulator_SetShader(g_blit_shader);

	u_char l = activeDispEnv.disp.x / 8;
	u_char t = activeDispEnv.disp.y / 8;
	u_char r = activeDispEnv.disp.w / 8 + l;
	u_char b = activeDispEnv.disp.h / 8 + t;

	Vertex blit_vertices[] =
	{
		{ +1, +1,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
		{ -1, -1,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ -1, +1,    0, 0,    l, t,    0, 0,    0, 0, 0, 0 },

		{ +1, -1,    0, 0,    r, b,    0, 0,    0, 0, 0, 0 },
		{ -1, -1,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ +1, +1,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
	};

	Emulator_UpdateVertexBuffer(blit_vertices, 6);
	Emulator_SetBlendMode(BM_NONE);
	Emulator_DrawTriangles(0, 2);
}

void Emulator_DoDebugKeys(int nKey, bool down); // forward decl

void Emulator_DoPollEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_CONTROLLERDEVICEADDED:
				padHandle[event.jbutton.which] = SDL_GameControllerOpen(event.cdevice.which);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				SDL_GameControllerClose(padHandle[event.cdevice.which]);
				break;
			case SDL_QUIT:
				Emulator_ShutDown();
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					windowWidth = event.window.data1;
					windowHeight = event.window.data2;
					Emulator_ResetDevice();
					break;
				case SDL_WINDOWEVENT_CLOSE:
					Emulator_ShutDown();
					break;
				}
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				int nKey = event.key.keysym.scancode;

				// lshift/right shift
				if (nKey == SDL_SCANCODE_RSHIFT)
					nKey = SDL_SCANCODE_LSHIFT;
				else if (nKey == SDL_SCANCODE_RCTRL)
					nKey = SDL_SCANCODE_LCTRL;
				else if (nKey == SDL_SCANCODE_RALT)
					nKey = SDL_SCANCODE_LALT;

				Emulator_DoDebugKeys(nKey, (event.type == SDL_KEYUP) ? false : true);
				break;
			}
		}
	}
}

bool begin_scene_flag = false;
bool vbo_was_dirty_flag = false;

bool Emulator_BeginScene()
{
	Emulator_DoPollEvent();

	if (begin_scene_flag)
		return false;

	assert(!begin_scene_flag);

	g_lastBoundTexture = NULL;

#if defined(OGL) || defined(OGLES)
	glBindVertexArray(dynamic_vertex_array);

	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);

#elif defined(D3D9)
	d3ddev->BeginScene();
	d3ddev->SetVertexDeclaration(vertexDecl);
	d3ddev->SetStreamSource(0, dynamic_vertex_buffer, 0, sizeof(Vertex));
#endif

	Emulator_UpdateVRAM();
	Emulator_SetViewPort(0, 0, windowWidth, windowHeight);

	Emulator_SetShader(g_gte_shader_4);
	Emulator_Ortho2D(0.0f, activeDispEnv.disp.w, activeDispEnv.disp.h, 0.0f, -1.0f, 1.0f);

	begin_scene_flag = true;

	if (g_wireframeMode)
	{
		Emulator_SetWireframe(true);

#if defined(OGL) || defined(OGLES)
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
#elif defined(D3D9)

#endif
	}

	return true;
}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
void Emulator_TakeScreenshot()
{
	unsigned char* pixels = new unsigned char[windowWidth * windowHeight * 4];
#if defined(OGL) || defined(OGLES)
	glReadPixels(0, 0, windowWidth, windowHeight, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
#endif
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, windowWidth, windowHeight, 8 * 4, windowWidth * 4, 0, 0, 0, 0);
	SDL_SaveBMP(surface, "SCREENSHOT.BMP");
	SDL_FreeSurface(surface);

	delete[] pixels;
}
#endif

GameDebugKeysHandlerFunc gameDebugKeys = NULL;
int activeControllers = 0x1;

void Emulator_DoDebugKeys(int nKey, bool down)
{
	if(gameDebugKeys)
		gameDebugKeys(nKey, down);

	if (nKey == SDL_SCANCODE_BACKSPACE)
	{
		if(down)
		{
			if (g_swapInterval != 0)
			{
				g_swapInterval = 0;
				Emulator_ResetDevice();
			}
		}
		else
		{
			if (g_swapInterval != SWAP_INTERVAL)
			{
				g_swapInterval = SWAP_INTERVAL;
				Emulator_ResetDevice();
			}
		}
	}

	if (!down)
	{
		switch (nKey)
		{
			case SDL_SCANCODE_1:
				g_wireframeMode ^= 1;
				eprintf("wireframe mode: %d\n", g_wireframeMode);
				break;

			case SDL_SCANCODE_2:
				g_texturelessMode ^= 1;
				eprintf("textureless mode: %d\n", g_texturelessMode);
				break;

			case SDL_SCANCODE_3:
				g_emulatorPaused ^= 1;
				break;

			case SDL_SCANCODE_UP:
			case SDL_SCANCODE_DOWN:
				if (g_emulatorPaused)
					g_polygonSelected += (nKey == SDL_SCANCODE_UP) ? 3 : -3;
				break;

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
			case SDL_SCANCODE_4:
				eprintf("saving screenshot\n");
				Emulator_TakeScreenshot();
				break;
#endif
			case SDL_SCANCODE_5:
				eprintf("saving VRAM.TGA\n");
				Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
				break;
			case SDL_SCANCODE_6:

				activeControllers++;
				activeControllers = activeControllers % 4;

				if (activeControllers == 0)
					activeControllers++;

				eprintf("Active keyboard controller: %d\n", activeControllers);
				break;
			case SDL_SCANCODE_7:
				g_pgxpTextureCorrection ^= 1;
				break;
				
		}
	}


}

void Emulator_UpdateInput()
{
	// also poll events here
	Emulator_DoPollEvent();

	unsigned short kbInputs = UpdateKeyboardInput();

	//Update pad
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			if (padHandle[i] != NULL)
			{
				unsigned short controllerInputs = UpdateGameControllerInput(padHandle[i]);

				PADRAW* pad = (PADRAW*)padData[i];
				pad->status = 0;	// PadStateStable?
				pad->id = 0;
				*(unsigned short*)pad->buttons = kbInputs & controllerInputs;
				pad->analog[0] = 128;
				pad->analog[1] = 128;
				pad->analog[2] = 128;
				pad->analog[3] = 128;
			}
		}
	}
	else
	{
		//Update keyboard
		if (padData[0] != NULL && activeControllers & 0x1)
		{
			PADRAW* pad = (PADRAW*)padData[0];

			pad->status = 0;	// PadStateStable?
			pad->id = 0x41;
			*(unsigned short*)pad->buttons = kbInputs;
			pad->analog[0] = 128;
			pad->analog[1] = 128;
			pad->analog[2] = 128;
			pad->analog[3] = 128;
		}

		//Update keyboard
		if (padData[1] != NULL && activeControllers & 0x2)
		{
			PADRAW* pad = (PADRAW*)padData[1];

			pad->status = 0;	// PadStateStable?
			pad->id = 0x41;
			*(unsigned short*)pad->buttons = kbInputs;
			pad->analog[0] = 128;
			pad->analog[1] = 128;
			pad->analog[2] = 128;
			pad->analog[3] = 128;
		}
	}

#if defined(__ANDROID__)
    ///@TODO SDL_NumJoysticks always reports > 0 for some reason on Android.
    ((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
#endif
}

unsigned int Emulator_GetFPS()
{
#define FPS_INTERVAL 1.0

	static unsigned int lastTime = SDL_GetTicks();
	static unsigned int currentFps = 0;
	static unsigned int passedFrames = 0;

	passedFrames++;
	if (lastTime < SDL_GetTicks() - FPS_INTERVAL * 1000)
	{
		lastTime = SDL_GetTicks();
		currentFps = passedFrames;
		passedFrames = 0;
	}

	return currentFps;
}

void Emulator_SwapWindow()
{
	//Emulator_WaitForTimestep(1);

#if defined(RO_DOUBLE_BUFFERED)
#if defined(OGL)
	SDL_GL_SwapWindow(g_window);
#elif defined(OGLES)
	eglSwapBuffers(eglDisplay, eglSurface);
#elif defined(D3D9)
	if (d3ddev->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST) {
		Emulator_ResetDevice();
	}
#endif
#else
	glFinish();
#endif
}

void Emulator_WaitForTimestep(int count)
{
	// additional wait for swap
	if (g_swapInterval > 0)
	{
		int delta = g_swapTime + FIXED_TIME_STEP * count - SDL_GetTicks();

		if (delta > 0) {
			SDL_Delay(delta);
		}
	}

	g_swapTime = SDL_GetTicks();
}

void Emulator_EndScene()
{
	if (!begin_scene_flag)
		return;

	if (!vbo_was_dirty_flag)
		return;

	assert(begin_scene_flag);

	if (g_wireframeMode)
	{
		Emulator_SetWireframe(false);
	}

#if defined(OGL) || defined(OGLES)
	glBindVertexArray(0);
#elif defined(D3D9)
	d3ddev->EndScene();
#endif

	begin_scene_flag = false;
	vbo_was_dirty_flag = false;

	Emulator_SwapWindow();
}

void Emulator_ShutDown()
{
	// quit vblank thread
	if (g_vblankThread)
	{
		g_stopVblank = true;

		int returnValue;
		SDL_WaitThread(g_vblankThread, &returnValue);
	}

	if(g_vblankMutex)
		SDL_DestroyMutex(g_vblankMutex);

#if defined(OGL) || defined(OGLES)
	Emulator_DestroyTexture(vramTexture);
	Emulator_DestroyTexture(whiteTexture);
#endif

	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

#if defined(D3D9)
	d3ddev->Release();
	d3d->Release();
#endif

	SDL_DestroyWindow(g_window);
	SDL_Quit();
	exit(0);
}

int g_PreviousBlendMode = BM_NONE;

void Emulator_SetBlendMode(BlendMode blendMode)
{
	if (g_PreviousBlendMode == blendMode)
	{
		return;
	}

#if defined(OGL) || defined(OGLES)
	if (g_PreviousBlendMode == BM_NONE)
	{
		glEnable(GL_BLEND);
	}

	switch (blendMode)
	{
		case BM_NONE:
			glDisable(GL_BLEND);
			break;
		case BM_AVERAGE:
			glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_COLOR);
			glBlendEquation(GL_FUNC_ADD);
			break;
		case BM_ADD:
			glBlendFunc(GL_ONE, GL_ONE);
			glBlendEquation(GL_FUNC_ADD);
			break;
		case BM_SUBTRACT:
			glBlendFunc(GL_ONE, GL_ONE);
			glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
			break;
		case BM_ADD_QUATER_SOURCE:
			glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE);
			glBlendEquation(GL_FUNC_ADD);
			break;
	}
#elif defined(D3D9)
	if (g_PreviousBlendMode == BM_NONE)
	{
		d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	switch (blendMode)
	{
		case BM_NONE:
			d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			break;
		case BM_AVERAGE:
			d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(128, 128, 128, 128));
			d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
			d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BLENDFACTOR);
			break;
		case BM_ADD:
			d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case BM_SUBTRACT:
			d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case BM_ADD_QUATER_SOURCE:
			d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(64, 64, 64, 64));
			d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
			d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
	}
#endif

	g_PreviousBlendMode = blendMode;
}

extern void Emulator_SetPolygonOffset(float ofs)
{
#if defined(OGL) || defined(OGLES)
	if (ofs == 0.0f)
	{
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(0.0f, ofs);
	}
	
#elif defined(D3D9)

#endif
}

void Emulator_SetViewPort(int x, int y, int width, int height)
{
#if defined(OGL) || defined(OGLES)
	glViewport(x, y, width, height);
#elif defined(D3D9)
	D3DVIEWPORT9 viewport;
	viewport.X      = x;
	viewport.Y      = y;
	viewport.Width  = width;
	viewport.Height = height;
	viewport.MinZ   = 0.0f;
	viewport.MaxZ   = 1.0f;
	d3ddev->SetViewport(&viewport);
#endif
}

void Emulator_SetRenderTarget(const RenderTargetID &frameBufferObject)
{
#if defined(OGL) || defined(OGLES)
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
#elif defined(D3D9)
	d3ddev->SetRenderTarget(0, frameBufferObject);
#else
    #error
#endif
}

void Emulator_SetWireframe(bool enable)
{
#if defined(OGL)
	glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
#elif defined(D3D9)
	d3ddev->SetRenderState(D3DRS_FILLMODE, enable ? D3DFILL_WIREFRAME : D3DFILL_SOLID);
#endif
}

void Emulator_UpdateVertexBuffer(const Vertex *vertices, int num_vertices)
{
	assert(num_vertices <= MAX_NUM_POLY_BUFFER_VERTICES);
#if defined(OGL) || defined(OGLES)
	glBufferSubData(GL_ARRAY_BUFFER, 0, num_vertices * sizeof(Vertex), vertices);
#elif defined(D3D9)
	void *ptr;
	dynamic_vertex_buffer->Lock(0, 0, &ptr, D3DLOCK_DISCARD);
	memcpy(ptr, vertices, num_vertices * sizeof(Vertex));
	dynamic_vertex_buffer->Unlock();
#else
	#error
#endif

	vbo_was_dirty_flag = true;
}

void Emulator_DrawTriangles(int start_vertex, int triangles)
{
#if defined(OGL) || defined(OGLES)
	glDrawArrays(GL_TRIANGLES, start_vertex, triangles * 3);
#elif defined(D3D9)
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, start_vertex, triangles);
#else
	#error
#endif
}
