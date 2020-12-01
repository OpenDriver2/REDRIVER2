#include "EMULATOR.H"

#include "EMULATOR_VERSION.H"
#include "EMULATOR_GLOBALS.H"
#include "EMULATOR_PRIVATE.H"

#include "CRASHHANDLER.H"

#include "LIBETC.H"

//#include <stdio.h>
//#include <string.h>
#if !defined(__ANDROID__)
//#include <thread>
#endif
#include <assert.h>

#define FIXED_TIME_STEP_NTSC		(1.0/60.0)		// 60 FPS clock
#define FIXED_TIME_STEP_PAL			(1.0/50.0)		// 50 FPS clock

#define SWAP_INTERVAL		1

#define PSX_SCREEN_ASPECT	(240.0f / 320.0f)			// PSX screen is mapped always to this aspect

#include <stdio.h>
#include <string.h>
#include <SDL.h>

#include "EMULATOR_TIMER.H"

SDL_Window* g_window = NULL;
TextureID vramTexture;
TextureID whiteTexture;

GLuint dynamic_vertex_buffer;
GLuint dynamic_vertex_array;


int windowWidth = 0;
int windowHeight = 0;
char* pVirtualMemory = NULL;
SysCounter counters[3] = { 0 };
#if !defined(__ANDROID__)
//std::thread counter_thread;
#endif

timerCtx_t g_swapTimer;
int g_swapInterval = SWAP_INTERVAL;

int g_wireframeMode = 0;
int g_texturelessMode = 0;
int g_emulatorPaused = 0;
int g_polygonSelected = 0;
int g_pgxpTextureCorrection = 1;
int g_pgxpZBuffer = 1;
int g_bilinearFiltering = 0;
TextureID g_lastBoundTexture;
KeyboardMapping g_keyboard_mapping;

// Remap a value in the range [A,B] to [C,D].
#define RemapVal( val, A, B, C, D) \
	(C + (D - C) * (val - A) / (B - A))

// remaps screen coordinates to [0..1]
// without clamping
inline void ScreenCoordsToEmulator(Vertex* vertex, int count)
{
	while (count--)
	{
		float psxScreenW = activeDispEnv.disp.w;
		float psxScreenH = activeDispEnv.disp.h;

		vertex[count].x = RemapVal(vertex[count].x, 0.0f, psxScreenW, 0.0f, 1.0f);
		vertex[count].y = RemapVal(vertex[count].y, 0.0f, psxScreenH, 0.0f, 1.0f);
		// FIXME: what about Z?

		// also center
		vertex[count].x -= 0.5f;
		vertex[count].y -= 0.5f;
	}
}

void Emulator_ResetDevice()
{
#if defined(OGL)
	SDL_GL_SetSwapInterval(g_swapInterval);
#endif
}


static int Emulator_InitialiseGLContext(char* windowName, int fullscreen)
{
	int windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	if(fullscreen)
	{
		windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, windowFlags);

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

static int Emulator_InitialiseGLESContext(char* windowName, int fullscreen)
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

static int Emulator_InitialiseSDL(char* windowName, int width, int height, int fullscreen)
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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
#endif

#if defined(OGL) || defined(OGLES)
		SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 1 );
#endif
	}
	else
	{
		eprinterr("Error: Failed to initialise SDL\n");
		return FALSE;
	}

#if defined(OGL)
	if (Emulator_InitialiseGLContext(windowName, fullscreen) == FALSE)
	{
		eprinterr("Failed to Initialise GL Context!\n");
		return FALSE;
	}
#elif defined(OGLES)
	if (Emulator_InitialiseGLESContext(windowName, fullscreen) == FALSE)
	{
		eprinterr("Failed to Initialise GLES Context!\n");
		return FALSE;
	}
#endif

	return TRUE;
}

static int Emulator_InitialiseGLExt()
{
#if defined(GLEW)
	GLenum err = gladLoadGL();

	if (err == 0)
		return FALSE;

	const char* rend = (const char *) glGetString(GL_RENDERER);
	const char* vendor = (const char *) glGetString(GL_VENDOR);
	eprintf("*Video adapter: %s by %s\n", rend, vendor);

	const char* versionStr = (const char *) glGetString(GL_VERSION);
	eprintf("*OpenGL version: %s\n", versionStr);

	const char* glslVersionStr = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	eprintf("*GLSL version: %s\n", glslVersionStr);
	
	
#endif
	return TRUE;
}

SDL_Thread* g_vblankThread = NULL;
SDL_mutex* g_vblankMutex = NULL;
volatile bool g_stopVblank = false;
volatile int g_vblanksDone = 0;
volatile int g_lastVblankCnt = 0;
timerCtx_t g_vblankTimer;

extern void(*vsync_callback)(void);

int Emulator_DoVSyncCallback()
{
	SDL_LockMutex(g_vblankMutex);

#if 1
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
#endif
	g_lastVblankCnt = g_vblanksDone;

	if (g_swapInterval == 0)
	{
		// extra speedup.
		// does not affect `vsync_callback` count
		g_vblanksDone += 1;
		g_lastVblankCnt += 1;
	}

	SDL_UnlockMutex(g_vblankMutex);

	return g_vblanksDone;
}

int vblankThreadMain(void* data)
{
	Emulator_InitHPCTimer(&g_vblankTimer);
	
	do
	{
		const long vmode = GetVideoMode();
		const double timestep = vmode == MODE_NTSC ? FIXED_TIME_STEP_NTSC : FIXED_TIME_STEP_PAL;
		
		double delta = Emulator_GetHPCTime(&g_vblankTimer, 0);
		
		if (delta > timestep)
		{
			// do vblank events
			SDL_LockMutex(g_vblankMutex);

			g_vblanksDone++;

			Emulator_GetHPCTime(&g_vblankTimer, 1);

#if 0
			if(vsync_callback)
				vsync_callback();
#endif
			SDL_UnlockMutex(g_vblankMutex);
		}
	} while (!g_stopVblank);

	return 0;
}

static int Emulator_InitialiseCore()
{
	Emulator_InitHPCTimer(&g_swapTimer);
	
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

static void Emulator_InitialiseInput()
{
	g_keyboard_mapping.kc_square = SDL_SCANCODE_X;
	g_keyboard_mapping.kc_circle = SDL_SCANCODE_V;
	g_keyboard_mapping.kc_triangle = SDL_SCANCODE_Z;
	g_keyboard_mapping.kc_cross = SDL_SCANCODE_C;

	g_keyboard_mapping.kc_l1 = SDL_SCANCODE_LSHIFT;
	g_keyboard_mapping.kc_l2 = SDL_SCANCODE_LCTRL;
	g_keyboard_mapping.kc_l3 = SDL_SCANCODE_LEFTBRACKET;

	g_keyboard_mapping.kc_r1 = SDL_SCANCODE_RSHIFT;
	g_keyboard_mapping.kc_r2 = SDL_SCANCODE_RCTRL;
	g_keyboard_mapping.kc_r3 = SDL_SCANCODE_RIGHTBRACKET;

	g_keyboard_mapping.kc_dpad_up = SDL_SCANCODE_UP;
	g_keyboard_mapping.kc_dpad_down = SDL_SCANCODE_DOWN;
	g_keyboard_mapping.kc_dpad_left = SDL_SCANCODE_LEFT;
	g_keyboard_mapping.kc_dpad_right = SDL_SCANCODE_RIGHT;

	g_keyboard_mapping.kc_select = SDL_SCANCODE_SPACE;
	g_keyboard_mapping.kc_start = SDL_SCANCODE_RETURN;
}

void Emulator_Initialise(char* windowName, int width, int height, int fullscreen)
{
	eprintf("Initialising Psy-X %d.%d\n", EMULATOR_MAJOR_VERSION, EMULATOR_MINOR_VERSION);
	eprintf("Build date: %s:%s\n", EMULATOR_COMPILE_DATE, EMULATOR_COMPILE_TIME);

	if (Emulator_InitialiseSDL(windowName, width, height, fullscreen) == FALSE)
	{
		eprinterr("Failed to Intialise SDL\n");
		Emulator_ShutDown();
	}

#if defined(GLEW)
	if (Emulator_InitialiseGLExt() == FALSE)
	{
		eprinterr("Failed to Intialise GL extensions\n");
		Emulator_ShutDown();
	}
#endif

	if (Emulator_InitialiseCore() == FALSE)
	{
		eprinterr("Failed to Intialise Psy-X Core.\n");
		Emulator_ShutDown();
	}

	if (Emulator_Initialise() == FALSE)
	{
		eprinterr("Failed to Intialise GL.\n");
		Emulator_ShutDown();
	}

	Emulator_InitialiseInput();
}

void Emulator_GetScreenSize(int& screenWidth, int& screenHeight)
{
	SDL_GetWindowSize(g_window, &screenWidth, &screenHeight);
}

void Emulator_SetCursorPosition(int x, int y)
{
	SDL_WarpMouseInWindow(g_window, x, y);
}

void Emulator_LineSwapSourceVerts(VERTTYPE* &p0, VERTTYPE* &p1, unsigned char* &c0, unsigned char* &c1)
{
	// swap line coordinates for left-to-right and up-to-bottom direction
	if ((p0[0] > p1[0]) || 
		(p0[1] > p1[1] && p0[0] == p1[0]))
	{
		VERTTYPE *tmp = p0;
		p0 = p1;
		p1 = tmp;

		unsigned char* tmpCol = c0;
		c0 = c1;
		c1 = tmpCol;
	}
}

void Emulator_GenerateLineArray(struct Vertex* vertex, VERTTYPE* p0, VERTTYPE* p1, ushort gteidx)
{
	VERTTYPE dx = p1[0] - p0[0];
	VERTTYPE dy = p1[1] - p0[1];

	float ofsX = activeDrawEnv.ofs[0] % activeDispEnv.disp.w;
	float ofsY = activeDrawEnv.ofs[1] % activeDispEnv.disp.h;

	if (dx > abs((short)dy)) { // horizontal
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
	vertex[0].scr_h = vertex[1].scr_h = vertex[2].scr_h = vertex[3].scr_h = 0.0f;
#endif

	ScreenCoordsToEmulator(vertex, 4);
}



inline void Emulator_ApplyVertexPGXP(Vertex* v, VERTTYPE* p, float ofsX, float ofsY, ushort gteidx)
{
#ifdef PGXP
	uint lookup = PGXP_LOOKUP_VALUE(p[0], p[1]);
	PGXPVData vd;
	if(g_pgxpTextureCorrection && PGXP_GetCacheData(vd, lookup, gteidx)) 
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
	}
#endif
}



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

	Emulator_ApplyVertexPGXP(&vertex[0], p0, ofsX, ofsY, gteidx-2);
	Emulator_ApplyVertexPGXP(&vertex[1], p1, ofsX, ofsY, gteidx-1);
	Emulator_ApplyVertexPGXP(&vertex[2], p2, ofsX, ofsY, gteidx);

	ScreenCoordsToEmulator(vertex, 3);
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

	Emulator_ApplyVertexPGXP(&vertex[0], p0, ofsX, ofsY, gteidx-2);
	Emulator_ApplyVertexPGXP(&vertex[1], p1, ofsX, ofsY, gteidx-2);
	Emulator_ApplyVertexPGXP(&vertex[2], p2, ofsX, ofsY, gteidx-1);
	Emulator_ApplyVertexPGXP(&vertex[3], p3, ofsX, ofsY, gteidx);

	ScreenCoordsToEmulator(vertex, 4);
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
	vertex[0].scr_h = vertex[1].scr_h = vertex[2].scr_h = vertex[3].scr_h = 0.0f;
#endif

	ScreenCoordsToEmulator(vertex, 4);
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
GLint u_Projection3D;

#define GPU_PACK_RG\
	"		float color_16 = (color_rg.y * 256.0 + color_rg.x) * 255.0;\n"

#define GPU_DISCARD\
	"		if (color_16 == 0.0) { discard; }\n"

#define GPU_DECODE_RG\
	"		fragColor = fract(floor(color_16 / vec4(1.0, 32.0, 1024.0, 32768.0)) / 32.0);\n"

#define GPU_PACK_RG_FUNC\
	"	float packRG(vec2 rg) { return (rg.y * 256.0 + rg.x) * 255.0;}\n"

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
    "    // returns 16 bit colour\n"\
    "    float samplePSX(vec2 tc){\n"\
    "        vec2 uv = (tc * vec2(0.25, 1.0) + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"\
    "        vec2 comp = VRAM(uv);\n"\
    "        int index = int(fract(tc.x / 4.0 + 0.0001) * 4.0);\n"\
    "        float v = comp[index / 2] * (255.0 / 16.0);\n"\
    "        float f = floor(v);\n"\
    "        vec2 c = vec2( (v - f) * 16.0, f );\n"\
    "        vec2 clut_pos = v_page_clut.zw;\n"\
    "        clut_pos.x += mix(c[0], c[1], mod(index, 2)) / 1024.0;\n"\
    "        clut_pos.x += 0.0001;\n"\
    "        clut_pos.y += 0.0001;\n"\
    "        return packRG(VRAM(clut_pos));\n"\
    "    }\n"

#define GPU_SAMPLE_TEXTURE_8BIT_FUNC\
	"	// returns 16 bit colour\n"\
	"	float samplePSX(vec2 tc){\n"\
	"		vec2 uv = (tc * vec2(0.5, 1.0) + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"\
	"		vec2 comp = VRAM(uv);\n"\
	"		vec2 clut_pos = v_page_clut.zw;\n"\
	"		int index = int(mod(tc.x, 2.0));\n"\
	"		clut_pos.x += comp[index] * 255.0 / 1024.0;\n"\
	"		vec2 color_rg = VRAM(clut_pos);\n"\
	"		return packRG(VRAM(clut_pos));\n"\
	"	}\n"

#define GPU_SAMPLE_TEXTURE_16BIT_FUNC\
	"	float samplePSX(vec2 tc){\n"\
	"		vec2 uv = (tc + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"\
	"		vec2 color_rg = VRAM(uv);\n"\
	"		return packRG(color_rg);\n"\
	"	}\n"


#define GPU_BILINEAR_SAMPLE_FUNC \
	"	float c_textureSize = 1;\n"\
	"	float c_onePixel = 1;\n"\
	"	vec4 BilinearTextureSample(vec2 P) {\n"\
	"		vec2 pixel = P + vec2(1.0, 1);\n"\
	"		vec2 frac = fract(pixel);\n"\
	"		pixel = floor(pixel) - vec2(c_onePixel * 0.5);\n"\
	"		float C11 = samplePSX(pixel + vec2( 0.0        , 0.0));\n"\
	"		float C21 = samplePSX(pixel + vec2( c_onePixel, 0.0));\n"\
	"		float C12 = samplePSX(pixel + vec2( 0.0        , c_onePixel));\n"\
	"		float C22 = samplePSX(pixel + vec2( c_onePixel, c_onePixel));\n"\
	"		float ax1 = mix(float(C11 > 0), float(C21 > 0), frac.x);\n"\
	"		float ax2 = mix(float(C12 > 0), float(C22 > 0), frac.x);\n"\
	"		if(mix(ax1, ax2, frac.y) < 0.25) { discard; }\n"\
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

#ifdef PGXP
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
	"	attribute vec4 a_zw;\n"\
	"	uniform mat4 Projection;\n"\
	"	uniform mat4 Projection3D;\n"\
	"	void main() {\n"\
	"		v_texcoord = a_texcoord;\n"\
	"		v_color = a_color;\n"\
	"		v_color.xyz *= a_texcoord.z;\n"\
	"		v_page_clut.x = fract(a_position.z / 16.0) * 1024.0;\n"\
	"		v_page_clut.y = floor(a_position.z / 16.0) * 256.0;\n"\
	"		v_page_clut.z = fract(a_position.w / 64.0);\n"\
	"		v_page_clut.w = floor(a_position.w / 64.0) / 512.0;\n"\
	GTE_PERSPECTIVE_CORRECTION\
	"		v_z = (gl_Position.z - 40) * 0.005;\n"\
	"	}\n"

#define GPU_FRAGMENT_SAMPLE_SHADER(bit) \
	GPU_PACK_RG_FUNC\
	GPU_DECODE_RG_FUNC\
	GPU_FETCH_VRAM_FUNC\
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
	GPU_FETCH_VRAM_FUNC
	"	void main() {\n"
	"		vec2 color_rg = VRAM(v_texcoord.xy);\n"
	GPU_PACK_RG
	GPU_DECODE_RG
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
		"precision lowp  int;\n"
		"precision highp float;\n"
        "#define VERTEX\n"
        "#define varying   out\n"
        "#define attribute in\n"
        "#define texture2D texture\n";

    const char *GLSL_HEADER_FRAG =
        "#version 330\n"
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

	if(g_bilinearFiltering)
	{
		strcat(extra_fs_defines, "#define BILINEAR_FILTER\n");
	}

    const char *vs_list[] = { GLSL_HEADER_VERT, extra_vs_defines, source };
    const char *fs_list[] = { GLSL_HEADER_FRAG, extra_fs_defines, source };

    GLuint program = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 3, vs_list, NULL);
    glCompileShader(vertexShader);
    Shader_CheckShaderStatus(vertexShader);
    glAttachShader(program, vertexShader);
    glDeleteShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 3, fs_list, NULL);
    glCompileShader(fragmentShader);
    Shader_CheckShaderStatus(fragmentShader);
    glAttachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    glBindAttribLocation(program, a_position, "a_position");
    glBindAttribLocation(program, a_texcoord, "a_texcoord");
    glBindAttribLocation(program, a_color,    "a_color");



#ifdef PGXP
	glBindAttribLocation(program, a_zw, "a_zw");
#endif

    glLinkProgram(program);
    Shader_CheckProgramStatus(program);

    GLint sampler = 0;
    glUseProgram(program);
    glUniform1iv(glGetUniformLocation(program, "s_texture"), 1, &sampler);
    glUseProgram(0);

    return program;
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
	u_Projection3D = glGetUniformLocation(g_gte_shader_4, "Projection3D");
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
#endif
}

int Emulator_Initialise()
{
	SDL_memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));
	Emulator_GenerateCommonTextures();
	Emulator_CreateGlobalShaders();

#if defined(OGL) || defined(OGLES)
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_STENCIL_TEST);
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
	glVertexAttribPointer(a_zw,		  4, GL_FLOAT,		   GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->z);

	glEnableVertexAttribArray(a_zw);
#else
	glVertexAttribPointer(a_position, 4, GL_SHORT,         GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->x);
#endif

	glVertexAttribPointer(a_texcoord, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->u);
	glVertexAttribPointer(a_color,    4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(Vertex), &((Vertex*)NULL)->r);

	glBindVertexArray(0);
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
#endif

	float ortho[16] = {
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		x, y, z, 1
	};

#if defined(OGL) || defined(OGLES)
	glUniformMatrix4fv(u_Projection, 1, GL_FALSE, ortho);
#endif
}

void Emulator_Perspective3D(const float fov, const float width, const float height, const float zNear, const float zFar)
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

#if defined(OGL) || defined(OGLES)
	glUniformMatrix4fv(u_Projection3D, 1, GL_TRUE, persp);
#elif defined(D3D9)
	d3ddev->SetVertexShaderConstantF(u_Projection3D, persp, 4);
#endif
}

void Emulator_SetupClipMode(const RECT16& rect)
{
	// [A] isinterlaced dirty hack for widescreen
	bool enabled = activeDispEnv.isinter || (rect.x - activeDispEnv.disp.x > 0 ||
		rect.y - activeDispEnv.disp.y > 0 ||
		rect.w < activeDispEnv.disp.w - 1 ||
		rect.h < activeDispEnv.disp.h - 1);

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
		float emuScreenAspect = float(windowWidth) / float(windowHeight);

		clipRectX /= PSX_SCREEN_ASPECT * emuScreenAspect;
		clipRectW /= emuScreenAspect * PSX_SCREEN_ASPECT;

		clipRectX += 0.5f;
	}

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
#endif
}

void Emulator_GetPSXWidescreenMappedViewport(RECT16& rect)
{
	float emuScreenAspect = float(windowWidth) / float(windowHeight);

	float psxScreenW = activeDispEnv.disp.w;
	float psxScreenH = activeDispEnv.disp.h;

	rect.x = activeDispEnv.screen.x;
	rect.y = activeDispEnv.screen.y;

	rect.w = psxScreenW * emuScreenAspect * PSX_SCREEN_ASPECT; // windowWidth;
	rect.h = psxScreenH; // windowHeight;

	rect.x -= (rect.w - activeDispEnv.disp.w) / 2;

	rect.w += rect.x;
}

void Emulator_SetShader(const ShaderID &shader)
{
#if defined(OGL) || defined(OGLES)
	glUseProgram(shader);
#else
	#error
#endif

	float emuScreenAspect = float(windowWidth) / float(windowHeight);

	Emulator_Ortho2D(-0.5f * emuScreenAspect * PSX_SCREEN_ASPECT, 0.5f * emuScreenAspect * PSX_SCREEN_ASPECT, 0.5f, -0.5f, -1.0f, 1.0f);

	Emulator_Perspective3D(0.9265f, 1.0f, 1.0f / (emuScreenAspect * PSX_SCREEN_ASPECT), 1.0f, 1000.0f);
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
#endif

	g_lastBoundTexture = texture;
}

void Emulator_DestroyTexture(TextureID texture)
{
#if defined(OGL) || defined(OGLES)
    glDeleteTextures(1, &texture);
#else
    #error
#endif
}

extern void Emulator_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
// TODO clear rect if it's necessary
#if defined(OGL) || defined(OGLES)
	
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		fwrite(vram + VRAM_WIDTH * FLIP_Y, sizeof(short), VRAM_WIDTH, fp );
	}

	fclose(fp);

	#undef FLIP_Y
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
#endif

	short *ptr = (short*)vram + VRAM_WIDTH * y + x;

	for (int fy = 0; fy < h; fy++)
	{
		short *fb_ptr = fb + (windowHeight * FLIP_Y / h) * windowWidth;

		for (int fx = 0; fx < w; fx++)
		{
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
#endif
}

void Emulator_BlitVRAM()
{
#if 0
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
#endif
}

void Emulator_DoDebugKeys(int nKey, bool down); // forward decl
void Emulator_DoDebugMouseMotion(int x, int y);

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
			case SDL_MOUSEMOTION:
				
				Emulator_DoDebugMouseMotion(event.motion.x, event.motion.y);
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
	glClear(GL_STENCIL_BUFFER_BIT);
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
GameDebugMouseHandlerFunc gameDebugMouse = NULL;
int activeControllers = 0x1;

void Emulator_DoDebugMouseMotion(int x, int y)
{
	if (gameDebugMouse)
		gameDebugMouse(x, y);
}

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
#ifdef _DEBUG
			case SDL_SCANCODE_F1:
				g_wireframeMode ^= 1;
				eprintf("wireframe mode: %d\n", g_wireframeMode);
				break;

			case SDL_SCANCODE_F2:
				g_texturelessMode ^= 1;
				eprintf("textureless mode: %d\n", g_texturelessMode);
				break;

			case SDL_SCANCODE_F3:
				g_emulatorPaused ^= 1;
				break;

			case SDL_SCANCODE_UP:
			case SDL_SCANCODE_DOWN:
				if (g_emulatorPaused)
				{
					g_polygonSelected += (nKey == SDL_SCANCODE_UP) ? 3 : -3;
				}
				break;
			case SDL_SCANCODE_F10:
				eprintf("saving VRAM.TGA\n");
				Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
				break;
#endif
#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
			case SDL_SCANCODE_F12:
				eprintf("Saving screenshot\n");
				Emulator_TakeScreenshot();
				break;
#endif
			case SDL_SCANCODE_F4:

				activeControllers++;
				activeControllers = activeControllers % 4;

				if (activeControllers == 0)
					activeControllers++;

				eprintf("Active keyboard controller: %d\n", activeControllers);
				break;
			case SDL_SCANCODE_F5:
				g_pgxpTextureCorrection ^= 1;
				break;
			case SDL_SCANCODE_F6:
				g_pgxpZBuffer ^= 1;
				break;
				
		}
	}
}

void Emulator_UpdateInput()
{
	// also poll events here
	Emulator_DoPollEvent();

	InternalPadUpdates();
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
#endif
#else
	glFinish();
#endif
}

void Emulator_WaitForTimestep(int count)
{
	const long vmode = GetVideoMode();
	const double timestep = vmode == MODE_NTSC ? FIXED_TIME_STEP_NTSC : FIXED_TIME_STEP_PAL;
	
	// additional wait for swap
	if (g_swapInterval > 0)
	{
		double delta;
		do
		{
			SDL_Delay(0); // yield
			delta = Emulator_GetHPCTime(&g_swapTimer, 0);
		} while (delta < timestep * count);

		Emulator_GetHPCTime(&g_swapTimer, 1);
	}
}

void Emulator_EndScene()
{
	if (!begin_scene_flag)
		return;

	assert(begin_scene_flag);

	if (g_wireframeMode)
	{
		Emulator_SetWireframe(false);
	}

#if defined(OGL) || defined(OGLES)
	glBindVertexArray(0);
#endif

	begin_scene_flag = false;

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

	SDL_DestroyWindow(g_window);
	SDL_Quit();
	exit(0);
}

int g_PreviousBlendMode = BM_NONE;

void Emulator_EnableDepth(int enable)
{
	if(enable && g_pgxpZBuffer)
	{
		glEnable(GL_DEPTH_TEST);
		//glDepthMask(GL_TRUE);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
		//glDepthMask(GL_FALSE);
	}
}

void Emulator_SetStencilMode(int drawPrim)
{
	if(drawPrim)
	{
		glStencilFunc( GL_ALWAYS, 1, 0x10 );
		glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE );
	}
	else
	{
		glStencilFunc( GL_NOTEQUAL, 1, 0xFF );
		glStencilOp( GL_REPLACE, GL_KEEP, GL_KEEP );
	}
}

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
			Emulator_EnableDepth(TRUE);
			break;
		case BM_AVERAGE:
			glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_COLOR);
			glBlendEquation(GL_FUNC_ADD);
			Emulator_EnableDepth(FALSE);
			break;
		case BM_ADD:
			glBlendFunc(GL_ONE, GL_ONE);
			glBlendEquation(GL_FUNC_ADD);
			Emulator_EnableDepth(FALSE);
			break;
		case BM_SUBTRACT:
			glBlendFunc(GL_ONE, GL_ONE);
			glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
			Emulator_EnableDepth(FALSE);
			break;
		case BM_ADD_QUATER_SOURCE:
			glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE);
			glBlendEquation(GL_FUNC_ADD);
			Emulator_EnableDepth(FALSE);
			break;
	}
#endif

	g_PreviousBlendMode = blendMode;
}

void Emulator_SetPolygonOffset(float ofs)
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
#endif
}

void Emulator_SetViewPort(int x, int y, int width, int height)
{
#if defined(OGL) || defined(OGLES)
	glViewport(x, y, width, height);
#endif
}

void Emulator_SetRenderTarget(const RenderTargetID &frameBufferObject)
{
#if defined(OGL) || defined(OGLES)
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
#else
    #error
#endif
}

void Emulator_SetWireframe(bool enable)
{
#if defined(OGL)
	glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
#endif
}

void Emulator_UpdateVertexBuffer(const Vertex *vertices, int num_vertices)
{
	assert(num_vertices <= MAX_NUM_POLY_BUFFER_VERTICES);
#if defined(OGL) || defined(OGLES)
	glBufferSubData(GL_ARRAY_BUFFER, 0, num_vertices * sizeof(Vertex), vertices);
#else
	#error
#endif
}

void Emulator_DrawTriangles(int start_vertex, int triangles)
{
#if defined(OGL) || defined(OGLES)
	glDrawArrays(GL_TRIANGLES, start_vertex, triangles * 3);
#else
	#error
#endif
}
