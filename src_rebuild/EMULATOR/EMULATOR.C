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

#define VERTEX_COLOUR_MULT (2)

#if defined(NTSC_VERSION)
#define COUNTER_UPDATE_INTERVAL (263)
#else
#define COUNTER_UPDATE_INTERVAL (313)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

SDL_Window* g_window = NULL;

#if defined(OGL) || defined(OGLES)
GLuint vramTexture;
GLuint vramFrameBuffer = 0;
GLuint vramRenderBuffer = 0;
GLuint nullWhiteTexture;
GLint g_defaultFBO;

#elif defined(VK)

struct FrameBuffer vramFrameBuffer;

#define MAX_NUM_PHYSICAL_DEVICES (4)

VkWin32SurfaceCreateInfoKHR surfaceCreateInfo =
{
	VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR
};

VkSurfaceKHR surface = VK_NULL_HANDLE;
VkInstance instance = VK_NULL_HANDLE;
VkPhysicalDeviceMemoryProperties deviceMemoryProperties;

const char* enabledExtensionsDeviceCreateInfo[] =
{
	 VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

enum 
{
	MAX_DEVICE_COUNT = 8,
	MAX_QUEUE_COUNT = 4,
	MAX_PRESENT_MODE_COUNT = 6,
	MAX_SWAPCHAIN_IMAGES = 3,
	FRAME_COUNT = 2,
	PRESENT_MODE_MAILBOX_IMAGE_COUNT = 3,
	PRESENT_MODE_DEFAULT_IMAGE_COUNT = 2,
};

VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
uint32_t queueFamilyIndex;
VkQueue queue;
VkDevice device = VK_NULL_HANDLE;

unsigned int vramTexture;///@TODO trim me
unsigned int vramRenderBuffer = 0;
unsigned int nullWhiteTexture;
int g_defaultFBO;

const char* enabledExtensions[] =
{
	VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME
};

VkSwapchainKHR swapchain;
unsigned int swapchainImageCount;
VkImage swapchainImages[MAX_SWAPCHAIN_IMAGES];
VkExtent2D swapchainExtent;
VkSurfaceFormatKHR surfaceFormat;
unsigned int frameIndex = 0;
VkCommandPool commandPool;
VkCommandBuffer commandBuffers[FRAME_COUNT];
VkFence frameFences[FRAME_COUNT]; // Create with VK_FENCE_CREATE_SIGNALED_BIT.
VkSemaphore imageAvailableSemaphores[FRAME_COUNT];
VkSemaphore renderFinishedSemaphores[FRAME_COUNT];
#elif defined (D3D9)
SDL_Renderer* g_renderer;
IDirect3DDevice9* d3ddev;
IDirect3DTexture9* vramTexture = NULL;
IDirect3DSurface9* vramFrameBuffer = NULL;
IDirect3DVertexDeclaration9* g_vertexDecl = NULL;
unsigned int vramRenderBuffer = 0;///@FIXME delete unused?
IDirect3DTexture9* nullWhiteTexture = NULL;
IDirect3DSurface9* g_defaultFBO = NULL;
IDirect3DPixelShader9* g_defaultPixelShader = NULL;
IDirect3DVertexShader9* g_defaultVertexShader = NULL;
#else
unsigned int vramTexture;
unsigned int vramFrameBuffer = 0;
unsigned int vramRenderBuffer = 0;
unsigned int nullWhiteTexture;
int g_defaultFBO;
#endif

int screenWidth = 0;
int screenHeight = 0;
int windowWidth = 0;
int windowHeight = 0;
char* pVirtualMemory = NULL;
SysCounter counters[3] = { 0 };
#if !defined(__ANDROID__)
//std::thread counter_thread;
#endif
int g_hasHintedTextureAtlas = 0;
struct CachedTexture cachedTextures[MAX_NUM_CACHED_TEXTURES];

#if defined(D3D9)
static int Emulator_InitialiseD3D9Context(char* windowName)
{
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window!\n");
		return FALSE;
	}
	
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (g_renderer == NULL)
	{
		eprinterr("Failed to initialise SDL renderer!\n");
		return FALSE;
	}
	
	d3ddev = SDL_RenderGetD3D9Device(g_renderer);
	if (g_renderer == NULL)
	{
		eprinterr("Failed to obtain D3D9 devicer!\n");
		return FALSE;
	}

	return TRUE;
}
#endif

#if defined(VK)
static int Emulator_InitialiseVKContext(char* windowName)
{
	VkApplicationInfo appInfo;
	memset(&appInfo, 0, sizeof(VkApplicationInfo));
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = windowName;
	appInfo.applicationVersion = VK_MAKE_VERSION(EMULATOR_MAJOR_VERSION, EMULATOR_MINOR_VERSION, 0);
	appInfo.pEngineName = EMULATOR_NAME;
	appInfo.engineVersion = VK_MAKE_VERSION(EMULATOR_MAJOR_VERSION, EMULATOR_MINOR_VERSION, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo;
	memset(&createInfo, 0, sizeof(VkInstanceCreateInfo));
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = 2;
	createInfo.ppEnabledExtensionNames = enabledExtensions;
	createInfo.pNext = VK_NULL_HANDLE;

	//Create Vulkan Instance
	if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS)
	{
		eprinterr("Failed to create Vulkan instance!");
		return FALSE;
	}

	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_VULKAN);

#if defined(OGL)
	SDL_GL_CreateContext(g_window);
#endif

	if (g_window == NULL)
	{
		eprinterr("Failed to initialise Vulkan context!\n");
		return FALSE;
	}

	SDL_SysWMinfo sysInfo;
	SDL_VERSION(&sysInfo.version);
	SDL_GetWindowWMInfo(g_window, &sysInfo);
	surfaceCreateInfo.hinstance = GetModuleHandle(0);
	surfaceCreateInfo.hwnd = sysInfo.info.win.window;

	if (vkCreateWin32SurfaceKHR(instance, &surfaceCreateInfo, NULL, &surface) != VK_SUCCESS)
	{
		eprinterr("Failed to initialise Vulkan surface!\n");
		return FALSE;
	}

	unsigned int physicalDeviceCount;
	VkPhysicalDevice deviceHandles[MAX_DEVICE_COUNT];
	VkQueueFamilyProperties queueFamilyProperties[MAX_QUEUE_COUNT];
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	

	vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, 0);
	physicalDeviceCount = physicalDeviceCount > MAX_DEVICE_COUNT ? MAX_DEVICE_COUNT : physicalDeviceCount;
	vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, deviceHandles);

	for (unsigned int i = 0; i < physicalDeviceCount; ++i)//Maybe 0 needs to be 1
	{
		unsigned int queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(deviceHandles[i], &queueFamilyCount, NULL);
		queueFamilyCount = queueFamilyCount > MAX_QUEUE_COUNT ? MAX_QUEUE_COUNT : queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(deviceHandles[i], &queueFamilyCount, queueFamilyProperties);

		vkGetPhysicalDeviceProperties(deviceHandles[i], &deviceProperties);
		vkGetPhysicalDeviceFeatures(deviceHandles[i], &deviceFeatures);
		vkGetPhysicalDeviceMemoryProperties(deviceHandles[i], &deviceMemoryProperties);
		for (unsigned int j = 0; j < queueFamilyCount; ++j) {

			VkBool32 supportsPresent = VK_FALSE;
			vkGetPhysicalDeviceSurfaceSupportKHR(deviceHandles[i], j, surface, &supportsPresent);

			if (supportsPresent && (queueFamilyProperties[j].queueFlags & VK_QUEUE_GRAPHICS_BIT))
			{
				queueFamilyIndex = j;
				physicalDevice = deviceHandles[i];
				break;
			}
		}

		if (physicalDevice)
		{
			break;
		}
	}

	VkDeviceCreateInfo deviceCreateInfo;
	VkDeviceQueueCreateInfo deviceQueueCreateInfo;
	memset(&deviceCreateInfo, 0, sizeof(VkDeviceCreateInfo));
	memset(&deviceQueueCreateInfo, 0, sizeof(VkDeviceQueueCreateInfo));

	const float queuePriorities = { 1.0f };

	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
	deviceQueueCreateInfo.queueCount = 1;
	deviceQueueCreateInfo.pQueuePriorities = &queuePriorities;

	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = 0;
	deviceCreateInfo.enabledLayerCount = 0;
	deviceCreateInfo.ppEnabledLayerNames = 0;
	deviceCreateInfo.enabledExtensionCount = 1;
	deviceCreateInfo.ppEnabledExtensionNames = enabledExtensionsDeviceCreateInfo;
	deviceCreateInfo.pEnabledFeatures = 0;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;

	if (vkCreateDevice(physicalDevice, &deviceCreateInfo, NULL, &device) != VK_SUCCESS)
	{
		eprinterr("Failed to create VK device!\n");
		return FALSE;
	}

	vkGetDeviceQueue(device, queueFamilyIndex, 0, &queue);

	/* Initialise SwapChain */
	unsigned int formatCount = 1;
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, 0);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, &surfaceFormat);
	surfaceFormat.format = surfaceFormat.format == VK_FORMAT_UNDEFINED ? VK_FORMAT_B8G8R8A8_UNORM : surfaceFormat.format;

	unsigned int presentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, NULL);
	VkPresentModeKHR presentModes[MAX_PRESENT_MODE_COUNT];
	presentModeCount = presentModeCount > MAX_PRESENT_MODE_COUNT ? MAX_PRESENT_MODE_COUNT : presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes);

	VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
	for (unsigned int i = 0; i < presentModeCount; ++i)
	{
		if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
			break;
		}
	}
	swapchainImageCount = presentMode == VK_PRESENT_MODE_MAILBOX_KHR ? PRESENT_MODE_MAILBOX_IMAGE_COUNT : PRESENT_MODE_DEFAULT_IMAGE_COUNT;

	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCapabilities);

	swapchainExtent = surfaceCapabilities.currentExtent;
	//if (swapchainExtent.width == UINT32_MAX)
	//{
	//	swapchainExtent.width = clamp_u32(width, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width);
	//	swapchainExtent.height = clamp_u32(height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
	//}

	VkSwapchainCreateInfoKHR swapChainCreateInfo;
	memset(&swapChainCreateInfo, 0, sizeof(VkSwapchainCreateInfoKHR));
	swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapChainCreateInfo.surface = surface;
	swapChainCreateInfo.minImageCount = swapchainImageCount;
	swapChainCreateInfo.imageFormat = surfaceFormat.format;
	swapChainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
	swapChainCreateInfo.imageExtent = swapchainExtent;
	swapChainCreateInfo.imageArrayLayers = 1; // 2 for stereo
	swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapChainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
	swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapChainCreateInfo.presentMode = presentMode;
	swapChainCreateInfo.clipped = VK_TRUE;

	if (vkCreateSwapchainKHR(device, &swapChainCreateInfo, 0, &swapchain) != VK_SUCCESS)
	{
		eprinterr("Failed to create swap chain!\n");
		return FALSE;
	}

	vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, NULL);
	vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages);


	VkCommandPoolCreateInfo commandPoolCreateInfo;
	memset(&commandPoolCreateInfo, 0, sizeof(VkCommandPoolCreateInfo));
	commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;

	vkCreateCommandPool(device, &commandPoolCreateInfo, 0, &commandPool);

	VkCommandBufferAllocateInfo commandBufferAllocInfo;
	memset(&commandBufferAllocInfo, 0, sizeof(VkCommandBufferAllocateInfo));
	
	commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocInfo.commandPool = commandPool;
	commandBufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferAllocInfo.commandBufferCount = FRAME_COUNT;

	vkAllocateCommandBuffers(device, &commandBufferAllocInfo, commandBuffers);

	VkSemaphoreCreateInfo semaphoreCreateInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };

	vkCreateSemaphore(device, &semaphoreCreateInfo, 0, &imageAvailableSemaphores[0]);
	vkCreateSemaphore(device, &semaphoreCreateInfo, 0, &imageAvailableSemaphores[1]);
	vkCreateSemaphore(device, &semaphoreCreateInfo, 0, &renderFinishedSemaphores[0]);
	vkCreateSemaphore(device, &semaphoreCreateInfo, 0, &renderFinishedSemaphores[1]);

	VkFenceCreateInfo fenceCreateInfo;
	memset(&fenceCreateInfo, 0, sizeof(VkFenceCreateInfo));
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	vkCreateFence(device, &fenceCreateInfo, 0, &frameFences[0]);
	vkCreateFence(device, &fenceCreateInfo, 0, &frameFences[1]);

	uint32_t index = (frameIndex++) % FRAME_COUNT;
	vkWaitForFences(device, 1, &frameFences[index], VK_TRUE, UINT64_MAX);
	vkResetFences(device, 1, &frameFences[index]);

	uint32_t imageIndex;
	vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphores[index], VK_NULL_HANDLE, &imageIndex);

	VkCommandBufferBeginInfo beginInfo;
	memset(&beginInfo, 0, sizeof(VkCommandBufferBeginInfo));
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vkBeginCommandBuffer(commandBuffers[index], &beginInfo);
	
	vkEndCommandBuffer(commandBuffers[index]);

	VkSubmitInfo submitInfo;
	memset(&submitInfo, 0, sizeof(VkSubmitInfo));
	VkPipelineStageFlags writeDestStageMask = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &imageAvailableSemaphores[index];
	submitInfo.pWaitDstStageMask = &writeDestStageMask;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[index];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &renderFinishedSemaphores[index];
	vkQueueSubmit(queue, 1, &submitInfo, frameFences[index]);

	VkPresentInfoKHR presentInfo;
	memset(&presentInfo, 0, sizeof(VkPresentInfoKHR));
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &renderFinishedSemaphores[index];
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapchain;
	presentInfo.pImageIndices = &imageIndex;

	vkQueuePresentKHR(queue, &presentInfo);

	return TRUE;
}
#endif

static int Emulator_InitialiseGLContext(char* windowName)
{
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

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

static int Emulator_InitialiseSDL(char* windowName, int screenWidth, int screenHeight)
{
	screenWidth = screenWidth;
	screenHeight = screenHeight;
	windowWidth = screenWidth;
	windowHeight = screenHeight;

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
#elif defined(VK)
	if (Emulator_InitialiseVKContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise VK Context!\n");
		return FALSE;
	}
#elif defined(D3D9)
	if (Emulator_InitialiseD3D9Context(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise D3D9 Context!\n");
		return FALSE;
	}
#endif

#if defined(OGL)
	SDL_GL_SetSwapInterval(1);
#elif defined(OGLES)
	eglSwapInterval(eglDisplay, 1);
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

static int Emulator_InitialiseCore()
{
	//Initialise texture cache
#if defined(OGL) || defined(OGLES)
	SDL_memset(&cachedTextures[0], -1, MAX_NUM_CACHED_TEXTURES * sizeof(struct CachedTexture));
#elif defined(D3D9)
	SDL_memset(&cachedTextures[0], 0, MAX_NUM_CACHED_TEXTURES * sizeof(struct CachedTexture));
#endif
	return TRUE;
}

void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight)
{
	eprintf("Initialising Emulator.\n");
	eprintf("VERSION: %d.%d\n", EMULATOR_MAJOR_VERSION, EMULATOR_MINOR_VERSION);
	eprintf("Compile Date: %s Time: %s\n", EMULATOR_COMPILE_DATE, EMULATOR_COMPILE_TIME);

	if (Emulator_InitialiseSDL(windowName, screenWidth, screenHeight) == FALSE)
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

#if defined(OGL) || defined(OGLES)
	if (Emulator_InitialiseGL() == FALSE)
	{
		eprinterr("Failed to Intialise GL.\n");
		Emulator_ShutDown();
	}
#elif defined(D3D9)
	if (Emulator_InitialiseD3D() == FALSE)
	{
		eprinterr("Failed to Intialise D3D.\n");
		Emulator_ShutDown();
	}
#endif

	//counter_thread = std::thread(Emulator_CounterLoop);
}

void Emulator_CounterLoop()
{
	static int numUpdates = 0;
	int last_time = 0;

	while (TRUE)
	{
		int now = SDL_GetTicks();

		if (now > last_time + 1000)
		{
			numUpdates = 0;
			last_time = now;
		}

		if (numUpdates++ <= 60)
		{
			for (int i = 0; i < 3; i++)
			{
				//if (!counters[i].IsStopped)
				{
					counters[i].cycle += COUNTER_UPDATE_INTERVAL;
					if (counters[i].target > 0)
					{
						counters[i].cycle %= counters[i].target;
					}
				}
			}
		}
	}
}

void Emulator_GenerateLineArray(struct Vertex* vertex, short* p0, short* p1, short* p2, short* p3)
{
	//Copy over position
	if (p0 != NULL)
	{
		vertex[0].x = (float)p0[0];
		vertex[0].y = (float)p0[1];
	}

	if (p1 != NULL)
	{
		vertex[1].x = (float)p1[0];
		vertex[1].y = (float)p1[1];
	}
}

void Emulator_GenerateVertexArrayQuad(struct Vertex* vertex, short* p0, short* p1, short* p2, short* p3, short w, short h)
{
#if defined(PGXP)
	PGXPVertex* pgxp_vertex_0 = NULL;
	PGXPVertex* pgxp_vertex_1 = NULL;
	PGXPVertex* pgxp_vertex_2 = NULL;
	PGXPVertex* pgxp_vertex_3 = NULL;

	//Locate each vertex based on SXY2 (very slow)
	for (int i = 0; i < pgxp_vertex_index; i++)
	{
		if (p0 != NULL)
		{
			if (((unsigned int*)p0)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_0 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (p1 != NULL)
		{
			if (((unsigned int*)p1)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_1 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (p2 != NULL)
		{
			if (((unsigned int*)p2)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_2 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (p3 != NULL)
		{
			if (((unsigned int*)p3)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_3 = &pgxp_vertex_buffer[i];
				continue;
			}
		}
	}
#endif

	//Copy over position
	if (p0 != NULL)
	{
#if defined(PGXP)
		if (pgxp_vertex_0 != NULL)
		{
			vertex[0].x = pgxp_vertex_0->x;
			vertex[0].y = pgxp_vertex_0->y;
		}
		else
		{
			vertex[0].x = (float)p0[0];
			vertex[0].y = (float)p0[1];
		}
#else
		vertex[0].x = (float)p0[0];
		vertex[0].y = (float)p0[1];
#endif
	}

	if (p1 != NULL)
	{
#if defined(PGXP)
		if (pgxp_vertex_1 != NULL)
		{
			vertex[1].x = pgxp_vertex_1->x;
			vertex[1].y = pgxp_vertex_1->y;
		}
		else
		{
			vertex[1].x = (float)p1[0];
			vertex[1].y = (float)p1[1];
		}
#else
		vertex[1].x = (float)p1[0];
		vertex[1].y = (float)p1[1];
#endif
	}
	else
	{
		if (p0 != NULL && w != -1 && h != -1)
		{
			vertex[1].x = (float)p0[0];
			vertex[1].y = (float)p0[1] + h;
		}
	}

	if (p2 != NULL)
	{
#if defined(PGXP)
		if (pgxp_vertex_2 != NULL)
		{
			vertex[2].x = pgxp_vertex_2->x;
			vertex[2].y = pgxp_vertex_2->y;
		}
		else
		{
			vertex[2].x = (float)p2[0];
			vertex[2].y = (float)p2[1];
		}
#else
		vertex[2].x = (float)p2[0];
		vertex[2].y = (float)p2[1];
#endif
	}
	else
	{
		if (p0 != NULL && w != -1 && h != -1)
		{
			vertex[2].x = (float)p0[0] + w;
			vertex[2].y = (float)p0[1] + h;
		}
	}

	if (p3 != NULL)
	{
#if defined(PGXP)
		if (pgxp_vertex_3 != NULL)
		{
			vertex[3].x = pgxp_vertex_3->x;
			vertex[3].y = pgxp_vertex_3->y;
		}
		else
		{
			vertex[3].x = (float)p3[0];
			vertex[3].y = (float)p3[1];
		}
#else
		vertex[3].x = (float)p3[0];
		vertex[3].y = (float)p3[1];
#endif
	}
	else
	{
		if (p0 != NULL && w != -1 && h != -1)
		{
			vertex[3].x = (float)p0[0] + w;
			vertex[3].y = (float)p0[1];
		}
	}
	return;
}


void Emulator_GenerateTexcoordArrayQuad(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short w, short h)
{
#if defined(PGXP) && 0
	/*
	Locate polygon in ztable
	*/

	PGXPPolygon* z0 = NULL;
	PGXPPolygon* z1 = NULL;
	PGXPPolygon* z2 = NULL;
	PGXPPolygon* z3 = NULL;

	//Can speed this up by storing last index found and using as start iter
	for (int i = pgxp_polgon_table_index; i > -1; i--)
	{
		if (uv0 != NULL)
		{
			if (((unsigned int*)uv0)[0] == pgxp_polygons[i].originalSXY)
			{
				z0 = &pgxp_polygons[i];
				//z0->bUsed = TRUE;
			}
		}

		if (uv1 != NULL)
		{
			if (((unsigned int*)uv1)[0] == pgxp_polygons[i].originalSXY)
			{
				z1 = &pgxp_polygons[i];
				//z1->bUsed = TRUE;
			}
		}

		if (uv2 != NULL)
		{
			if (((unsigned int*)uv2)[0] == pgxp_polygons[i].originalSXY)
			{
				z2 = &pgxp_polygons[i];
				//z2->bUsed = TRUE;
			}
		}

		if (uv3 != NULL)
		{
			if (((unsigned int*)uv3)[0] == pgxp_polygons[i].originalSXY)
			{
				z3 = &pgxp_polygons[i];
				//z3->bUsed = TRUE;
			}
		}

		if ((z0 != NULL || uv0 == NULL) && (z1 != NULL || uv1 == NULL) && (z2 != NULL || uv2 == NULL) && (z3 != NULL || uv3 == NULL))
			break;
	}

	//Copy over uvs
	if (uv0 != NULL)
	{
		if (z0 != NULL)
		{
			vertex[0].u0 = z0->x;
			vertex[0].v0 = z0->y;
		}
		else
		{
			vertex[0].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
			vertex[0].v0 = ((float)uv0[1]) / TPAGE_HEIGHT;
		}
	}

	if (uv1 != NULL)
	{
		if (z1 != NULL)
		{
			vertex[1].u0 = z1->x;
			vertex[1].v0 = z1->y;
		}
		else
		{
			vertex[1].u0 = ((float)uv1[0]) / TPAGE_WIDTH;
			vertex[1].v0 = ((float)uv1[1]) / TPAGE_HEIGHT;
		}
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[1].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
			vertex[1].v0 = ((float)uv0[1] + h) / TPAGE_HEIGHT;
		}
	}

	if (uv2 != NULL)
	{
		if (z2 != NULL)
		{
			vertex[2].u0 = z2->x;
			vertex[2].v0 = z2->y;
		}
		else
		{
			vertex[2].u0 = ((float)uv2[0]) / TPAGE_WIDTH;
			vertex[2].v0 = ((float)uv2[1]) / TPAGE_HEIGHT;
		}
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[2].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[2].v0 = ((float)uv0[1] + h) / TPAGE_HEIGHT;
		}
	}

	if (uv3 != NULL)
	{
		if (z3 != NULL)
		{
			vertex[3].u0 = z3->x;
			vertex[3].v0 = z3->y;
		}
		else
		{
			vertex[3].u0 = ((float)uv3[0]) / TPAGE_WIDTH;
			vertex[3].v0 = ((float)uv3[1]) / TPAGE_HEIGHT;
		}
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[3].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[3].v0 = ((float)uv0[1]) / TPAGE_HEIGHT;
		}
	}

#else
	//Copy over uvs
	if (uv0 != NULL)
	{
		vertex[0].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
		vertex[0].v0 = ((float)uv0[1]) / TPAGE_HEIGHT;
	}

	if (uv1 != NULL)
	{
		vertex[1].u0 = ((float)uv1[0]) / TPAGE_WIDTH;
		vertex[1].v0 = ((float)uv1[1]) / TPAGE_HEIGHT;
	}
	else
	{
		if (uv0 != NULL && w != -1 && h != -1)
		{
			vertex[1].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
			vertex[1].v0 = ((float)uv0[1] + h) / TPAGE_HEIGHT;
		}
	}

	if (uv2 != NULL)
	{
		vertex[2].u0 = ((float)uv2[0]) / TPAGE_WIDTH;
		vertex[2].v0 = ((float)uv2[1]) / TPAGE_HEIGHT;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[2].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[2].v0 = ((float)uv0[1] + h) / TPAGE_HEIGHT;
		}
	}

	if (uv3 != NULL)
	{
		vertex[3].u0 = ((float)uv3[0]) / TPAGE_WIDTH;
		vertex[3].v0 = ((float)uv3[1]) / TPAGE_HEIGHT;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[3].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[3].v0 = ((float)uv0[1]) / TPAGE_HEIGHT;
		}
	}
#endif
	return;
}

void Emulator_GenerateColourArrayQuad(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, int bMultiplyColour)
{
	//Copy over rgb vertex colours
	if (col0 != NULL)
	{
		if (bMultiplyColour)
		{
#if defined(OGL) || defined(OGLES)
			vertex[0].col[0] = ((1.0f / 255.0f) * col0[0]) * VERTEX_COLOUR_MULT;
			vertex[0].col[1] = ((1.0f / 255.0f) * col0[1]) * VERTEX_COLOUR_MULT;
			vertex[0].col[2] = ((1.0f / 255.0f) * col0[2]) * VERTEX_COLOUR_MULT;
			vertex[0].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[0].col = D3DCOLOR_RGBA(col0[2], col0[1], col0[0], 255);
#endif
		}
		else
		{
#if defined(OGL) || defined(OGLES)
			vertex[0].col[0] = (1.0f / 255.0f) * col0[0];
			vertex[0].col[1] = (1.0f / 255.0f) * col0[1];
			vertex[0].col[2] = (1.0f / 255.0f) * col0[2];
			vertex[0].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[0].col = D3DCOLOR_RGBA(col0[2], col0[1], col0[0], 255);
#endif
		}
	}

	if (col1 != NULL)
	{
		if (bMultiplyColour)
		{
#if defined(OGL) || defined(OGLES)
			vertex[1].col[0] = ((1.0f / 255.0f) * col1[0]) * VERTEX_COLOUR_MULT;
			vertex[1].col[1] = ((1.0f / 255.0f) * col1[1]) * VERTEX_COLOUR_MULT;
			vertex[1].col[2] = ((1.0f / 255.0f) * col1[2]) * VERTEX_COLOUR_MULT;
			vertex[1].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[1].col = D3DCOLOR_RGBA(col1[2], col1[1], col1[0], 255);
#endif
	}
		else
		{
#if defined(OGL) || defined(OGLES)
			vertex[1].col[0] = (1.0f / 255.0f) * col1[0];
			vertex[1].col[1] = (1.0f / 255.0f) * col1[1];
			vertex[1].col[2] = (1.0f / 255.0f) * col1[2];
			vertex[1].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[1].col = D3DCOLOR_RGBA(col1[2], col1[1], col1[0], 255);
#endif
}
	}
	else
	{
		if (bMultiplyColour)
		{
#if defined(OGL) || defined(OGLES)
			vertex[1].col[0] = ((1.0f / 255.0f) * col0[0]) * VERTEX_COLOUR_MULT;
			vertex[1].col[1] = ((1.0f / 255.0f) * col0[1]) * VERTEX_COLOUR_MULT;
			vertex[1].col[2] = ((1.0f / 255.0f) * col0[2]) * VERTEX_COLOUR_MULT;
			vertex[1].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[1].col = D3DCOLOR_RGBA(col0[2], col0[1], col0[0], 255);
#endif
		}
		else
		{
#if defined(OGL) || defined(OGLES)
			vertex[1].col[0] = (1.0f / 255.0f) * col0[0];
			vertex[1].col[1] = (1.0f / 255.0f) * col0[1];
			vertex[1].col[2] = (1.0f / 255.0f) * col0[2];
			vertex[1].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[1].col = D3DCOLOR_RGBA(col0[2], col0[1], col0[0], 255);
#endif
		}
	}

	if (col2 != NULL)
	{
		if (bMultiplyColour)
		{
#if defined(OGL) || defined(OGLES)
			vertex[2].col[0] = ((1.0f / 255.0f) * col2[0]) * VERTEX_COLOUR_MULT;
			vertex[2].col[1] = ((1.0f / 255.0f) * col2[1]) * VERTEX_COLOUR_MULT;
			vertex[2].col[2] = ((1.0f / 255.0f) * col2[2]) * VERTEX_COLOUR_MULT;
			vertex[2].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[2].col = D3DCOLOR_RGBA(col2[2], col2[1], col2[0], 255);
#endif
		}
		else
		{
#if defined(OGL) || defined(OGLES)
			vertex[2].col[0] = (1.0f / 255.0f) * col2[0];
			vertex[2].col[1] = (1.0f / 255.0f) * col2[1];
			vertex[2].col[2] = (1.0f / 255.0f) * col2[2];
			vertex[2].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[2].col = D3DCOLOR_RGBA(col2[2], col2[1], col2[0], 255);
#endif
		}
	}
	else
	{
		if (bMultiplyColour)
		{
#if defined(OGL) || defined(OGLES)
			vertex[2].col[0] = ((1.0f / 255.0f) * col0[0]) * VERTEX_COLOUR_MULT;
			vertex[2].col[1] = ((1.0f / 255.0f) * col0[1]) * VERTEX_COLOUR_MULT;
			vertex[2].col[2] = ((1.0f / 255.0f) * col0[2]) * VERTEX_COLOUR_MULT;
			vertex[2].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[2].col = D3DCOLOR_RGBA(col0[2], col0[1], col0[0], 255);
#endif
		}
		else
		{
#if defined(OGL) || defined(OGLES)
			vertex[2].col[0] = (1.0f / 255.0f) * col0[0];
			vertex[2].col[1] = (1.0f / 255.0f) * col0[1];
			vertex[2].col[2] = (1.0f / 255.0f) * col0[2];
			vertex[2].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[2].col = D3DCOLOR_RGBA(col0[2], col0[1], col0[0], 255);
#endif
		}
	}

	if (col3 != NULL)
	{
		if (bMultiplyColour)
		{
#if defined(OGL) || defined(OGLES)
			vertex[3].col[0] = ((1.0f / 255.0f) * col3[0]) * VERTEX_COLOUR_MULT;
			vertex[3].col[1] = ((1.0f / 255.0f) * col3[1]) * VERTEX_COLOUR_MULT;
			vertex[3].col[2] = ((1.0f / 255.0f) * col3[2]) * VERTEX_COLOUR_MULT;
			vertex[3].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[3].col = D3DCOLOR_RGBA(col3[2], col3[1], col3[0], 255);
#endif
		}
		else
		{
#if defined(OGL) || defined(OGLES)
			vertex[3].col[0] = (1.0f / 255.0f) * col3[0];
			vertex[3].col[1] = (1.0f / 255.0f) * col3[1];
			vertex[3].col[2] = (1.0f / 255.0f) * col3[2];
			vertex[3].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[3].col = D3DCOLOR_RGBA(col3[2], col3[1], col3[0], 255);
#endif
		}
	}
	else
	{
		if (bMultiplyColour)
		{
#if defined(OGL) || defined(OGLES)
			vertex[3].col[0] = ((1.0f / 255.0f) * col0[0]) * VERTEX_COLOUR_MULT;
			vertex[3].col[1] = ((1.0f / 255.0f) * col0[1]) * VERTEX_COLOUR_MULT;
			vertex[3].col[2] = ((1.0f / 255.0f) * col0[2]) * VERTEX_COLOUR_MULT;
			vertex[3].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[3].col = D3DCOLOR_RGBA(col0[2], col0[1], col0[0], 255);
#endif
		}
		else
		{
#if defined(OGL) || defined(OGLES)
			vertex[3].col[0] = (1.0f / 255.0f) * col0[0];
			vertex[3].col[1] = (1.0f / 255.0f) * col0[1];
			vertex[3].col[2] = (1.0f / 255.0f) * col0[2];
			vertex[3].col[3] = (1.0f / 255.0f) * 255;
#elif defined(D3D9)
			vertex[3].col = D3DCOLOR_RGBA(col0[2], col0[1], col0[0], 255);
#endif
		}
	}

	return;
}

#if defined(OGLES) || defined(OGL)
GLuint g_defaultShaderProgram;
#endif

void Emulator_CreateGlobalShaders()
{
#if defined(ES2_SHADERS)
	const char* vertexShaderSource = "attribute vec4 a_position; attribute vec2 a_texcoord; varying vec2 v_texcoord; attribute vec4 a_colour; varying vec4 v_colour; uniform mat4 Projection; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*a_position; }";
#elif defined(ES3_SHADERS)
	const char* vertexShaderSource = "#version 300 es\n in vec4 a_position; in vec2 a_texcoord; out vec2 v_texcoord; in vec4 a_colour; out vec4 v_colour; uniform mat4 Projection; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*a_position; }";
#elif defined(OGL)
	const char* vertexShaderSource = "#version 330 core\n in vec4 a_position; in vec2 a_texcoord; out vec2 v_texcoord; in vec4 a_colour; out vec4 v_colour; uniform mat4 Projection; uniform mat4 Scale; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*(a_position*Scale);  }";
#elif defined(D3D9)
	const char* vertexShaderSource = "struct VS_IN { float3 pos : POSITION; float2 texcoord : TEXCOORD0; float4 col : COLOR0; }; struct VS_OUT { float4 pos : POSITION; float2 texcoord : TEXCOORD0; float4 col : COLOR0; }; VS_OUT main(VS_IN input) { VS_OUT output; output.pos = float4(input.pos.xyz,1); output.texcoord = input.texcoord; output.col = input.col; return output; }";
#endif

#if defined(OGL) || defined(OGLES)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
#elif defined(D3D9)
	LPD3DXBUFFER vOutErrors = NULL;
	LPD3DXBUFFER vertexShaderObject = NULL;
	
	if FAILED(D3DXCompileShader(vertexShaderSource, strlen(vertexShaderSource), NULL, NULL, "main", "vs_3_0", 0, &vertexShaderObject, &vOutErrors, NULL))
	{
		eprinterr("Failed to compile vertex shader!\n")
	}
	
	if FAILED(d3ddev->CreateVertexShader((DWORD*)vertexShaderObject->GetBufferPointer(), &g_defaultVertexShader))
	{
		eprinterr("Failed to create vertex shader!\n");
	}
#endif

#if defined(ES2_SHADERS)
	const char* fragmentShaderSource = "precision mediump float; varying vec2 v_texcoord; varying vec4 v_colour; uniform bool bDiscardBlack; uniform sampler2D s_texture; void main() { gl_FragColor = texture2D(s_texture, v_texcoord); if (gl_FragColor.a == 0.0 && bDiscardBlack) { discard; } gl_FragColor *= v_colour; }";
#elif defined(ES3_SHADERS)
	const char* fragmentShaderSource = "#version 300 es\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform sampler2D s_texture; out vec4 fragColour; void main() { fragColour = texture(s_texture, v_texcoord) * v_colour; }";
#elif defined(OGL)
	const char* fragmentShaderSource = "#version 330 core\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform bool bDiscardBlack; uniform sampler2D s_texture; out vec4 fragColour; void main() { fragColour = texture(s_texture, v_texcoord); if (fragColour.a == 0.0 && bDiscardBlack) { discard; } fragColour *= v_colour; }";
#elif defined(D3D9)
	const char* fragmentShaderSource = "sampler tex : register(s0); bool bDiscardBlack = true; float4 main(in float2 texcoord : TEXCOORD0) : COLOR0 { float4 color = tex2D(tex, texcoord); float r = color.r; color.r = color.b; color.b = r; if(color.r == 0.0f && color.g == 0.0f && color.b == 0x0f) { discard; } return color; }";
#endif

#if defined(OGL) || defined(OGLES)
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
#elif defined(D3D9)
	LPD3DXBUFFER pOutErrors = NULL;
	LPD3DXBUFFER pixelShaderObject = NULL;
	
	if FAILED(D3DXCompileShader(fragmentShaderSource, strlen(fragmentShaderSource), NULL, NULL, "main", "ps_3_0", 0, &pixelShaderObject, &pOutErrors, NULL))
	{
		eprinterr("Failed to compile pixel shader!\n")
	}

	if FAILED(d3ddev->CreatePixelShader((DWORD*)pixelShaderObject->GetBufferPointer(), &g_defaultPixelShader))
	{
		eprinterr("Failed to create pixel shader!\n");
	}
#endif

#if defined(_DEBUG) && (defined(OGL) || defined(OGLES))
	char buff[1024];
	int maxLength = 1024;
	glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &buff[0]);

	printf("%s", &buff[0]);

	maxLength = 1024;
	glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &buff[0]);

	printf("%s", &buff[0]);
#endif

#if defined(OGL) || defined(OGLES)
	/* Default */
	g_defaultShaderProgram = glCreateProgram();
	glAttachShader(g_defaultShaderProgram, vertexShader);
	glAttachShader(g_defaultShaderProgram, fragmentShader);
	glLinkProgram(g_defaultShaderProgram);
	glUseProgram(g_defaultShaderProgram);
	GLint idx = glGetUniformLocation(g_defaultShaderProgram, "s_texture");
	GLint sampler = 0;
	glUniform1iv(idx, 1, &sampler);
	glActiveTexture(GL_TEXTURE0 + sampler);
#endif
}

unsigned short vram[VRAM_WIDTH * VRAM_HEIGHT];

int Emulator_InitialiseGL()
{
#if defined(OGL) || defined(OGLES)
	glEnable(GL_BLEND);

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &g_defaultFBO);
#endif

	/* Initialise VRAM */
	SDL_memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));

	/* Generate NULL white texture */
	Emulator_GenerateAndBindNullWhite();

#if defined(OGL) || defined(OGLES)
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_SCISSOR_TEST);
	glBlendColor(0.25f, 0.25f, 0.25f, 0.5f);
	glGenTextures(1, &vramTexture);

	Emulator_BindTexture(vramTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#endif

#if defined(OGLES)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &vram[0]);
#elif defined(OGL)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &vram[0]);
#endif
#if defined(OGL) || defined(OGLES)
	/* Generate VRAM Frame Buffer */
	glGenFramebuffers(1, &vramFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
#endif

	/* Bind VRAM texture to vram framebuffer */
#if defined (OGLES)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vramTexture, 0);
#elif defined(OGL)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, vramTexture, 0);
#endif

#if defined(OGL) || defined(OGLES)
	while (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error: %x\n", glGetError());
		eprinterr("Frame buffer status : %d\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
		exit(0);
	}
#endif

#if defined(OGL) || defined(OGLES)
	glLineWidth(RESOLUTION_SCALE);
#endif

#if defined(OGL)
	glEnable(GL_DEPTH_TEST);
#endif

#if defined(OGL) || defined(OGLES)
	Emulator_CreateGlobalShaders();
	Emulator_BindTexture(0);
	glBindFramebuffer(GL_FRAMEBUFFER, g_defaultFBO);
#endif
	return TRUE;
}

#if defined(D3D9)
int Emulator_InitialiseD3D()
{
	d3ddev->GetRenderTarget(0, &g_defaultFBO);
	d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(64, 64, 64, 128));
	d3ddev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	/* Initialise VRAM */
	SDL_memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));

	/* Generate NULL white texture */
	//Emulator_GenerateAndBindNullWhite();///@TODO

#if defined(D3D9)
	D3DVERTEXELEMENT9 vertexDecl[] =
	{
	  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	  {0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	  {0, 20, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
	  D3DDECL_END()
	};

	if FAILED(d3ddev->CreateVertexDeclaration(vertexDecl, &g_vertexDecl))
	{
		eprinterr("Failed to create vertex declaration!\n");
		return FALSE;
	}

	d3ddev->SetVertexDeclaration(g_vertexDecl);

	if FAILED(d3ddev->CreateTexture(VRAM_WIDTH, VRAM_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &vramTexture, NULL))
	{
		eprinterr("Failed to create render target texture!\n");
		return FALSE;
	}

	vramTexture->GetSurfaceLevel(0, &vramFrameBuffer);

	if FAILED(d3ddev->CreateRenderTarget(VRAM_WIDTH, VRAM_HEIGHT, D3DFMT_A1R5G5B5, D3DMULTISAMPLE_NONE, 0, TRUE, &vramFrameBuffer, NULL))
	{
		eprinterr("Failed to create render target!\n");
		return FALSE;
	}

	d3ddev->SetRenderTarget(0, vramFrameBuffer);

	Emulator_CreateGlobalShaders();

#endif

	return TRUE;
}
#elif defined(VK)

unsigned int getMemoryType(unsigned int typeBits, VkMemoryPropertyFlags properties, VkBool32* memTypeFound)
{
	memTypeFound = NULL;

	for (unsigned int i = 0; i < deviceMemoryProperties.memoryTypeCount; i++)
	{
		if ((typeBits & 1) == 1)
		{
			if ((deviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				if (memTypeFound)
				{
					*memTypeFound = true;
				}
				return i;
			}
		}
		typeBits >>= 1;
	}

	if (memTypeFound)
	{
		*memTypeFound = false;
		return 0;
	}
	else
	{
		eprinterr("Could not find matching memory type!\n");
		assert(FALSE);
	}
}

int Emulator_InitialiseVK()
{
	//d3ddev->GetRenderTarget(0, &g_defaultRenderTarget);
	//d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	//d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(64, 64, 64, 128));
	//d3ddev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	/* Initialise VRAM */
	SDL_memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));

	/* Generate NULL white texture */
	//Emulator_GenerateAndBindNullWhite();///@TODO

	vramFrameBuffer.width = VRAM_WIDTH;
	vramFrameBuffer.height = VRAM_HEIGHT;

	// Find a suitable depth format
	VkFormat fbDepthFormat;
	//VkBool32 validDepthFormat = vks::tools::getSupportedDepthFormat(physicalDevice, &fbDepthFormat);
	//assert(validDepthFormat);

	// Color attachment
	VkImageCreateInfo imageCreateInfo;
	memset(&imageCreateInfo, 0, sizeof(VkImageCreateInfo));

	imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
	imageCreateInfo.format = VK_FORMAT_R5G5B5A1_UNORM_PACK16;
	imageCreateInfo.extent.width = vramFrameBuffer.width;
	imageCreateInfo.extent.height = vramFrameBuffer.height;
	imageCreateInfo.extent.depth = 1;
	imageCreateInfo.mipLevels = 1;
	imageCreateInfo.arrayLayers = 1;
	imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

	// We will sample directly from the color attachment
	imageCreateInfo.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VkMemoryAllocateInfo memoryAllocateInfo;
	memset(&memoryAllocateInfo, 0, sizeof(VkMemoryAllocateInfo));
	VkMemoryRequirements memReqs;
	memset(&memReqs, 0, sizeof(VkMemoryRequirements));
	if (vkCreateImage(device, &imageCreateInfo, nullptr, &vramFrameBuffer.color.image) != VK_SUCCESS)
	{
		eprinterr("Failed to create vram image!\n");
		return FALSE;
	}

	vkGetImageMemoryRequirements(device, vramFrameBuffer.color.image, &memReqs);
	memoryAllocateInfo.allocationSize = memReqs.size;
	memoryAllocateInfo.memoryTypeIndex = getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, NULL);
	if (vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &vramFrameBuffer.color.mem) != VK_SUCCESS)
	{
		eprinterr("Failed to allocate vram image memory!\n");
		return FALSE;
	}

	if (vkBindImageMemory(device, vramFrameBuffer.color.image, vramFrameBuffer.color.mem, 0) != VK_SUCCESS)
	{
		eprinterr("Failed to bind vram image memory!\n");
		return FALSE;
	}

	VkImageViewCreateInfo colorImageView;
	memset(&colorImageView, 0, sizeof(VkImageViewCreateInfo));

	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = VK_FORMAT_R5G5B5A1_UNORM_PACK16;
	colorImageView.subresourceRange = {};
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = vramFrameBuffer.color.image;

	if (vkCreateImageView(device, &colorImageView, nullptr, &vramFrameBuffer.color.view) != VK_SUCCESS)
	{
		eprinterr("Failed to create vram view image!\n");
		return FALSE;
	}

	// Create sampler to sample from the attachment in the fragment shader
	VkSamplerCreateInfo samplerInfo;
	memset(&samplerInfo, 0, sizeof(VkSamplerCreateInfo));

	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfo.addressModeV = samplerInfo.addressModeU;
	samplerInfo.addressModeW = samplerInfo.addressModeU;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.maxAnisotropy = 1.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 1.0f;
	samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	if (vkCreateSampler(device, &samplerInfo, nullptr, &vramFrameBuffer.sampler) != VK_SUCCESS)
	{
		eprinterr("Failed to create vram sampler!\n");
		return FALSE;
	}

	// Depth stencil attachment
	imageCreateInfo.format = fbDepthFormat;
	imageCreateInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	if (vkCreateImage(device, &imageCreateInfo, nullptr, &vramFrameBuffer.depth.image) != VK_SUCCESS)
	{
		eprinterr("Failed to create depth image!\n");
		return FALSE;
	}
	vkGetImageMemoryRequirements(device, vramFrameBuffer.depth.image, &memReqs);
	memoryAllocateInfo.allocationSize = memReqs.size;
	memoryAllocateInfo.memoryTypeIndex = getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, FALSE);
	if (vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &vramFrameBuffer.depth.mem) != VK_SUCCESS)
	{
		eprinterr("Failed to allocate depth image memory!\n");
		return FALSE;
	}
	if (vkBindImageMemory(device, vramFrameBuffer.depth.image, vramFrameBuffer.depth.mem, 0) != VK_SUCCESS)
	{
		eprinterr("Failed to allocate bind depth image memory!\n");
		return FALSE;
	}

	VkImageViewCreateInfo depthStencilView;
	memset(&depthStencilView, 0, sizeof(VkImageViewCreateInfo));

	depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	depthStencilView.format = fbDepthFormat;
	depthStencilView.flags = 0;
	depthStencilView.subresourceRange = {};
	depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
	depthStencilView.subresourceRange.baseMipLevel = 0;
	depthStencilView.subresourceRange.levelCount = 1;
	depthStencilView.subresourceRange.baseArrayLayer = 0;
	depthStencilView.subresourceRange.layerCount = 1;
	depthStencilView.image = vramFrameBuffer.depth.image;

	if (vkCreateImageView(device, &depthStencilView, nullptr, &vramFrameBuffer.depth.view) != VK_SUCCESS)
	{
		eprinterr("Failed to create depth image view!\n");
		return FALSE;
	}
	// Create a separate render pass for the offscreen rendering as it may differ from the one used for scene rendering
	VkAttachmentDescription attchmentDescriptions[2];
	memset(&attchmentDescriptions[0], 0, sizeof(VkAttachmentDescription) * 2);

	// Color attachment
	attchmentDescriptions[0].format = VK_FORMAT_R5G5B5A1_UNORM_PACK16;
	attchmentDescriptions[0].samples = VK_SAMPLE_COUNT_1_BIT;
	attchmentDescriptions[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attchmentDescriptions[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attchmentDescriptions[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attchmentDescriptions[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attchmentDescriptions[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attchmentDescriptions[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	// Depth attachment
	attchmentDescriptions[1].format = fbDepthFormat;
	attchmentDescriptions[1].samples = VK_SAMPLE_COUNT_1_BIT;
	attchmentDescriptions[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attchmentDescriptions[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attchmentDescriptions[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attchmentDescriptions[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attchmentDescriptions[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attchmentDescriptions[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference colorReference = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
	VkAttachmentReference depthReference = { 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };

	VkSubpassDescription subpassDescription = {};
	subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpassDescription.colorAttachmentCount = 1;
	subpassDescription.pColorAttachments = &colorReference;
	subpassDescription.pDepthStencilAttachment = &depthReference;

	// Use subpass dependencies for layout transitions
	VkSubpassDependency subPassDependencies[2];
	memset(&subPassDependencies[0], 0, sizeof(VkSubpassDependency) * 2);

	subPassDependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
	subPassDependencies[0].dstSubpass = 0;
	subPassDependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	subPassDependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subPassDependencies[0].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
	subPassDependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subPassDependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	subPassDependencies[1].srcSubpass = 0;
	subPassDependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
	subPassDependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subPassDependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	subPassDependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subPassDependencies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
	subPassDependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	// Create the actual renderpass
	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 2;
	renderPassInfo.pAttachments = &attchmentDescriptions[0];
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpassDescription;
	renderPassInfo.dependencyCount = 2;
	renderPassInfo.pDependencies = &subPassDependencies[0];

	if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &vramFrameBuffer.renderPass) != VK_SUCCESS)
	{
		eprinterr("Failed to create render pass!\n");
		return FALSE;
	}

	VkImageView attachments[2];
	attachments[0] = vramFrameBuffer.color.view;
	attachments[1] = vramFrameBuffer.depth.view;

	VkFramebufferCreateInfo fbufCreateInfo;
	memset(&fbufCreateInfo, 0, sizeof(VkFramebufferCreateInfo));
	fbufCreateInfo.renderPass = vramFrameBuffer.renderPass;
	fbufCreateInfo.attachmentCount = 2;
	fbufCreateInfo.pAttachments = attachments;
	fbufCreateInfo.width = vramFrameBuffer.width;
	fbufCreateInfo.height = vramFrameBuffer.height;
	fbufCreateInfo.layers = 1;

	if (vkCreateFramebuffer(device, &fbufCreateInfo, nullptr, &vramFrameBuffer.frameBuffer) != VK_SUCCESS)
	{
		eprinterr("Failed to create frame buffer!\n");
		return FALSE;
	}

	// Fill a descriptor for later use in a descriptor set 
	vramFrameBuffer.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	vramFrameBuffer.descriptor.imageView = vramFrameBuffer.color.view;
	vramFrameBuffer.descriptor.sampler = vramFrameBuffer.sampler;

	Emulator_CreateGlobalShaders();

	return TRUE;
}
#endif

unsigned int g_lastBoundTexture = -1;
#if defined(OGL) || defined(OGLES) || defined(VK)
void Emulator_BindTexture(unsigned int textureId)
#elif defined(D3D9)
void Emulator_BindTexture(IDirect3DTexture9* texture)
#endif
{
#if !defined(__EMSCRIPTEN__)
	//assert(textureId < 1000);
#endif
#if defined(OGL) || defined(OGLES)
	if (g_lastBoundTexture != textureId)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);

		g_lastBoundTexture = textureId;
	}
#elif defined(D3D9)
	d3ddev->SetTexture(0, texture);
#endif
}

#if defined(OGL) || defined(OGLES) || defined(VK)
void Emulator_DestroyTextures(int numTextures, unsigned int* textures)
#elif defined(D3D9)
void Emulator_DestroyTextures(IDirect3DTexture9* texture)
#endif
{
#if defined(OGL) || defined(OGLES)
	for (int i = 0; i < numTextures; i++)
	{
		if (textures[i] == g_lastBoundTexture)
		{
			g_lastBoundTexture = -1;
		}
	}
	glDeleteTextures(numTextures, textures);
#elif defined(D3D9)
	texture->Release();
#endif
}

void Emulator_GenerateAndBindNullWhite()
{
	unsigned char pixelData[4];
	((int*)&pixelData[0])[0] = 0x80808080;
#if defined(OGL) || defined(OGLES)
	glGenTextures(1, &nullWhiteTexture);
	Emulator_BindTexture(nullWhiteTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]);
#endif
}

void Emulator_CheckTextureIntersection(RECT16* rect)///@TODO internal upres
{
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		//Unused texture
#if defined(OGL) || defined(OGLES)
		if (cachedTextures[i].textureID == 0xFFFFFFFF)
#elif defined(D3D9)
		if (cachedTextures[i].texture == NULL)
#endif
			continue;

		unsigned short tpage = cachedTextures[i].tpage;
		unsigned int tpageX = ((tpage << 6) & 0x7C0) % VRAM_WIDTH;///@TODO macro
		unsigned int tpageY = (((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200)) % VRAM_HEIGHT;///@TODO macro

		if (rect->x < tpageX + TPAGE_WIDTH && rect->x + rect->w > tpageX&&
			rect->y > tpageY + TPAGE_WIDTH && rect->y + rect->h < tpageY)
		{
#if defined(OGL) || defined(OGLES)
			Emulator_DestroyTextures(1, &cachedTextures[i].textureID);
			SDL_memset(&cachedTextures[i], -1, sizeof(struct CachedTexture));
#elif defined(D3D9)
			Emulator_DestroyTextures(cachedTextures[i].texture);
			SDL_memset(&cachedTextures[i], 0, sizeof(struct CachedTexture));
#endif
		}
	}
}
#define NOFILE 0

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer)
{
#if NOFILE
	return;
#endif

#if defined(OGL) || defined(OGLES)
	glBindFramebuffer(GL_READ_FRAMEBUFFER, vramFrameBuffer);

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
	unsigned short* pixelData = new unsigned short[width * height];

	if (bReadFromFrameBuffer)
	{
		glReadPixels(x, y, width, height, GL_BGRA, TEXTURE_FORMAT, &pixelData[0]);
	}
	else
	{

		glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, TEXTURE_FORMAT, pixelData);
	}

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);

	//512 const is hdd sector size
	int numSectorsToWrite = (width * height * sizeof(unsigned short)) / 512;
	int numRemainingSectorsToWrite = (width * height * sizeof(unsigned short)) % 512;

	for (int i = 0; i < numSectorsToWrite; i++)
	{
		fwrite(&pixelData[i * 512 / sizeof(unsigned short)], 512, 1, f);
	}

	for (int i = 0; i < numRemainingSectorsToWrite; i++)
	{
		fwrite(&pixelData[numSectorsToWrite * 512 / sizeof(unsigned short)], numRemainingSectorsToWrite, 1, f);
	}

	fclose(f);
	delete[] pixelData;

#elif defined(D3D9)
	D3DXSaveSurfaceToFile(outputFileName, D3DXIFF_TGA, vramFrameBuffer, NULL, NULL);
#endif
}
#endif

void Emulator_BeginScene()
{
#if defined(D3D9)
	d3ddev->BeginScene();
#endif

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_JOYDEVICEADDED:
			if (SDL_IsGameController(event.jbutton.which))
			{
				padHandle[event.jbutton.which] = SDL_GameControllerOpen(event.jbutton.which);
			}
			break;
		case SDL_JOYDEVICEREMOVED:
			SDL_GameControllerClose(padHandle[event.jbutton.which]);
			break;
		case SDL_QUIT:
			Emulator_ShutDown();
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				Emulator_ShutDown();
				break;
			}
			break;
		}
	}
}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
void Emulator_TakeScreenshot()
{
	unsigned char* pixels = new unsigned char[512 * RESOLUTION_SCALE * 240 * RESOLUTION_SCALE * 4];
#if defined(OGL) || defined(OGLES)
	glReadPixels(0, 0, 512 * RESOLUTION_SCALE, 240 * RESOLUTION_SCALE, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
#endif
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, 512 * RESOLUTION_SCALE, 240 * RESOLUTION_SCALE, 8 * 4, 512 * RESOLUTION_SCALE * 4, 0, 0, 0, 0);
	SDL_SaveBMP(surface, "SCREENSHOT.BMP");
	SDL_FreeSurface(surface);

	delete[] pixels;
}
#endif

///@FIXME keyboardState only accessible if padInitDirect called! Let the emulator manage input not the sub library!
void Emulator_DoDebugKeys()
{
	static unsigned int currentTime;
	static unsigned int lastTime;

	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 60)
	{
		if (keyboardState[SDL_SCANCODE_BACKSPACE])
		{
			if (g_swapInterval != 0)
			{
				SDL_GL_SetSwapInterval(0);
			}
			g_swapInterval = 0;
		}
		else
		{
			if (g_swapInterval != 1)
			{
				SDL_GL_SetSwapInterval(1);
			}
			g_swapInterval = 1;
		}

		if (keyboardState[SDL_SCANCODE_1])
		{
			g_wireframeMode ^= 1;
			eprintf("wireframe mode: %d\n", g_wireframeMode);
		}

		if (keyboardState[SDL_SCANCODE_2])
		{
			g_texturelessMode ^= 1;
			eprintf("textureless mode: %d\n", g_texturelessMode);
		}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
		if (keyboardState[SDL_SCANCODE_3])
		{
			eprintf("saving screenshot\n");
			Emulator_TakeScreenshot();
		}
#endif

		if (keyboardState[SDL_SCANCODE_4])
		{
			eprintf("saving VRAM.TGA\n");

			Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);

		}

		lastTime = currentTime;
	}
}

void Emulator_UpdateInput()
{
	//Update pad
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			if (padHandle[i] != NULL)
			{
				padData[i][0] = 0;
				padData[i][1] = 0x41;//?
				((unsigned short*)padData[i])[1] = UpdateGameControllerInput(padHandle[i]);
			}
		}
	}
	else
	{
		//Update keyboard
		if (padData[0] != NULL)
		{
			((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
		}
	}

#if defined(__ANDROID__)
    ///@TODO SDL_NumJoysticks always reports > 0 for some reason on Android.
    ((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
#endif

	Emulator_DoDebugKeys();
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
#if defined(RO_DOUBLE_BUFFERED)
#if defined(OGL)
	SDL_GL_SwapWindow(g_window);
#elif defined(OGLES)
	eglSwapBuffers(eglDisplay, eglSurface);
#elif defined(D3D9)
	d3ddev->Present(NULL, NULL, NULL, NULL);
#endif
#else
	glFinish();
#endif
}

void Emulator_EndScene()
{
#if defined(OGL) || defined(OGLES)
	glDisable(GL_BLEND);

	glUniform1i(glGetUniformLocation(g_defaultShaderProgram, "bDiscardBlack"), FALSE);
	//glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);///@TOCHECK is this really required?
#endif

#if defined(VK)
	//Unimplemented
	//assert(FALSE);
#else
	Emulator_BindFrameBuffer(g_defaultFBO);
#endif
	Emulator_SetScissorBox(0, 0, windowWidth * RESOLUTION_SCALE, windowHeight * RESOLUTION_SCALE);

#if defined(D3D9)
	d3ddev->SetRenderTarget(0, g_defaultFBO);
	d3ddev->SetVertexShader(g_defaultVertexShader);
	d3ddev->SetPixelShader(g_defaultPixelShader);
#endif

	float x = 1.0f / (VRAM_WIDTH / (float)(word_33BC.disp.x * RESOLUTION_SCALE));
	float y = 1.0f / (VRAM_HEIGHT / (float)(word_33BC.disp.y * RESOLUTION_SCALE));
	float h = 1.0f / (VRAM_HEIGHT / (float)(word_33BC.disp.h * RESOLUTION_SCALE));
	float w = 1.0f / (VRAM_WIDTH / (float)(word_33BC.disp.w * RESOLUTION_SCALE));

#if defined(OGL) || defined(OGLES)
	float vertexBuffer[] =
	{
		0.0f, (float)word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, x, y, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, x, y + h, 1.0f, 1.0f, 1.0f, 1.0f,
		(float)word_33BC.disp.w * RESOLUTION_SCALE, 0.0f, 0.0f, x + w, y + h, 1.0f, 1.0f, 1.0f, 1.0f,
		(float)word_33BC.disp.w * RESOLUTION_SCALE, (float)word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, x + w, y, 1.0f, 1.0f, 1.0f, 1.0f,
		(float)word_33BC.disp.w * RESOLUTION_SCALE, 0.0f, 0.0f, x + w, y + h, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, (float)word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, x, y, 1.0f, 1.0f, 1.0f, 1.0f,
	};
#elif defined(D3D9)

#if 0
	struct Vertex vertexBuffer[] =
	{
		0.0f, (float)word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, x, y + h, D3DCOLOR_RGBA(255, 255, 255, 255),
		(float)word_33BC.disp.w * RESOLUTION_SCALE, (float)word_33BC.disp.h* RESOLUTION_SCALE, 0.0f, x + w, y + h, D3DCOLOR_RGBA(255, 255, 255, 255),
		0.0f, 0.0f, 0.0f, x, y, D3DCOLOR_RGBA(255, 255, 255, 255),


		(float)word_33BC.disp.w * RESOLUTION_SCALE, 0.0f, 0.0f, x + w, y, D3DCOLOR_RGBA(255, 255, 255, 255),
		0.0f, 0.0f, 0.0f, x, y, D3DCOLOR_RGBA(255, 255, 255, 255),
		(float)word_33BC.disp.w * RESOLUTION_SCALE, (float)word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, x + w, y + h, D3DCOLOR_RGBA(255, 255, 255, 255),
	};
#else
	struct Vertex vertexBuffer[] =
	{
		//BL
		-1.0f, -1.0f, 0.0f, x, y + h, D3DCOLOR_RGBA(255, 255, 255, 255),
		//BR
		1.0f, -1.0f, 0.0f, x + w, y + h, D3DCOLOR_RGBA(255, 255, 255, 255),
		//TL
		-1.0f, 1.0f, 0.0f, x, y, D3DCOLOR_RGBA(255, 255, 255, 255),

		//TR
		1.0f, 1.0f, 0.0f, x + w, y, D3DCOLOR_RGBA(255, 255, 255, 255),
		//TL
		-1.0f, 1.0f, 0.0f, x, y, D3DCOLOR_RGBA(255, 255, 255, 255),
		//BR
	    1.0f, -1.0f, 0.0f, x + w, y + h, D3DCOLOR_RGBA(255, 255, 255, 255),
	};
#endif

#endif


#if defined(OGLES) || defined (OGL)
	GLuint vbo, ibo, vao;
	GLuint indexBuffer[] = { 0,1,2,0,2,3 };

#if (defined OGL) || (defined(OGLES) && OGLES_VERSION == 3)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
#else
	glGenVertexArraysOES(1, &vao);
	glBindVertexArrayOES(vao);
#endif

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indexBuffer, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), &vertexBuffer[0], GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
	GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
	GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(colAttrib);
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)20);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)12);
#elif defined (D3D9)
	LPDIRECT3DVERTEXBUFFER9 vertexBufferObject = NULL;
	d3ddev->CreateVertexBuffer(sizeof(struct Vertex) * 6, 0, (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0), D3DPOOL_MANAGED, &vertexBufferObject, NULL);
	VOID* pVertexData;
	vertexBufferObject->Lock(0, 0, (void**)&pVertexData, 0);
	memcpy(pVertexData, &vertexBuffer[0], sizeof(struct Vertex) * 6);
	vertexBufferObject->Unlock();
	d3ddev->SetStreamSource(0, vertexBufferObject, 0, sizeof(struct Vertex));

	/* Nasty, make texture from render target*/
	IDirect3DSurface9* surface = NULL;
	vramTexture->GetSurfaceLevel(0, &surface);
	d3ddev->StretchRect(vramFrameBuffer, NULL, surface, NULL, D3DTEXF_LINEAR);
	d3ddev->SetTexture(0, vramTexture);
#endif
	Emulator_Ortho2D(0.0f, word_33BC.disp.w * RESOLUTION_SCALE, 0.0f, word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, 1.0f);
	Emulator_Scalef(1.0f, 1.0f, 1.0f);

#if defined(OGLES) || defined (OGL)
	Emulator_BindTexture(vramTexture);

	//Delete buffers
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
#elif defined(D3D9)
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6);
#endif

#if defined(OGLES) || defined (OGL)
	glDisableVertexAttribArray(posAttrib);
	glDisableVertexAttribArray(colAttrib);
	glDisableVertexAttribArray(texAttrib);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
#if (defined OGL) || (defined(OGLES) && OGLES_VERSION == 3)
    glDeleteVertexArrays(1, &vao);
#else
    glDeleteVertexArraysOES(1, &vao);
#endif
#endif

#if _DEBUG && 0
	glBindFramebuffer(GL_READ_FRAMEBUFFER, vramFrameBuffer);
	Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
#else
	//Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
#endif

#if defined(D3D9)
	//texture->Release();
	d3ddev->SetVertexShader(NULL);
	d3ddev->SetPixelShader(NULL);
	d3ddev->EndScene();
#endif

	Emulator_SwapWindow();
#if defined(OGL) || defined(OGLES)
	glUseProgram(g_defaultShaderProgram);
#endif
}

void Emulator_ShutDown()
{
#if defined(OGL) || defined(OGLES)
	Emulator_DestroyFrameBuffer(&vramFrameBuffer);
	Emulator_DestroyTextures(1, &vramTexture);
	Emulator_DestroyTextures(1, &nullWhiteTexture);
#endif

	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
#if defined(OGL) || defined(OGLES)
		if (cachedTextures[i].textureID != 0xFFFFFFFF)
		{
			Emulator_DestroyTextures(1, &cachedTextures[i].textureID);
		}
#elif defined(D3D9)
		if (cachedTextures[i].texture != NULL)
		{
			Emulator_DestroyTextures(cachedTextures[i].texture);
		}
#endif
	}

#if defined(VK)
	vkDestroySurfaceKHR(instance, surface, 0);
	vkDestroyInstance(instance, NULL);
#elif defined(D3D9)
	if (g_defaultVertexShader != NULL)
	{
		g_defaultVertexShader->Release();
	}
	
	if (g_defaultPixelShader != NULL)
	{
		g_defaultPixelShader->Release();
	}

	SDL_DestroyRenderer(g_renderer);
#endif

	SDL_DestroyWindow(g_window);
	SDL_Quit();
	exit(0);
}

void Emulator_GenerateFrameBuffer(unsigned int* fbo)
{
#if defined(OGL) || defined(OGLES)
	glGenFramebuffers(1, fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
#endif
}

struct CachedTexture* Emulator_FindTextureInCache(unsigned short tpage, unsigned short clut)
{
	if (g_hasHintedTextureAtlas)
	{
		for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
		{
			if (cachedTextures[i].tpage == tpage)
			{
				cachedTextures[i].lastAccess = SDL_GetTicks();
				return &cachedTextures[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
		{
			if (cachedTextures[i].tpage == tpage && cachedTextures[i].clut == clut)
			{
				cachedTextures[i].lastAccess = SDL_GetTicks();
				return &cachedTextures[i];
			}
		}
	}

	return NULL;
}

struct CachedTexture* Emulator_GetFreeCachedTexture()
{
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
#if defined(OGL) || defined(OGLES)
		if (cachedTextures[i].textureID == 0xFFFFFFFF)
#elif defined(D3D9)
		if (cachedTextures[i].texture == NULL)
#endif
		{

			return &cachedTextures[i];
		}
	}

	//Cache is full, this should never happen
	assert(0);

	return NULL;
}

#if defined(OGL) || defined(OGLES) || defined(VK)
unsigned int Emulator_GenerateTpage(unsigned short tpage, unsigned short clut)
#elif defined(D3D9)
IDirect3DTexture9* Emulator_GenerateTpage(unsigned short tpage, unsigned short clut)
#endif
{
	unsigned int textureType = GET_TPAGE_TYPE(tpage);
	unsigned int tpageX = GET_TPAGE_X(tpage);
	unsigned int tpageY = GET_TPAGE_Y(tpage)
	unsigned int clutX = GET_CLUT_X(clut);
	unsigned int clutY = GET_CLUT_Y(clut);

#if RESOLUTION_SCALE > 1
	if (tpageX >= 256)
	{
		tpageX += ((VRAM_WIDTH - (VRAM_WIDTH / RESOLUTION_SCALE)) / 2);
	}

	if (tpageY >= 256)
	{
		tpageY += ((VRAM_HEIGHT - (VRAM_HEIGHT / RESOLUTION_SCALE)) / 2);
	}
	if (clutX >= 256)
	{
		clutX += ((VRAM_WIDTH - (VRAM_WIDTH / RESOLUTION_SCALE)) / 2);
	}
	if (clutY >= 256)
	{
		clutY += ((VRAM_HEIGHT - (VRAM_HEIGHT / RESOLUTION_SCALE)) / 2);
	}
#endif

	struct CachedTexture* tpageTexture = Emulator_FindTextureInCache(tpage, clut);
	int bMustAddTexture = (tpageTexture == NULL) ? 1 : 0;

	if (bMustAddTexture)
	{
		tpageTexture = Emulator_GetFreeCachedTexture();
		tpageTexture->tpage = tpage;
		tpageTexture->clut = clut;
#if defined(OGL) || defined(OGLES)
		glGenTextures(1, &tpageTexture->textureID);
#endif
#if !defined(__EMSCRIPTEN__) && !defined(VK) && !defined(D3D9)
		assert(tpageTexture->textureID < 1000);
#endif
#if defined(OGL) || defined(OGLES)
		Emulator_BindTexture(tpageTexture->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#endif
	}
	else
	{
#if defined(OGL) || defined(OGLES)
		return tpageTexture->textureID;
#elif defined(D3D9)
		return tpageTexture->texture;
#endif
	}

	enum
	{
		TP_4BIT,
		TP_8BIT,
		TP_16BIT
	};

	switch (textureType)
	{
	case TP_16BIT:
	{
		unsigned short* tpage = (unsigned short*)SDL_malloc(TPAGE_WIDTH * TPAGE_HEIGHT * sizeof(unsigned short));
#if defined(OGL) || defined(OGLES)
		glReadPixels(tpageX, tpageY, TPAGE_WIDTH, TPAGE_HEIGHT, GL_RGBA, TEXTURE_FORMAT, tpage);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, TEXTURE_FORMAT, tpage);
#endif
#if defined(_DEBUG) && 0
		char buff[64];
		sprintf(&buff[0], "TPAGE_%d_%d.TGA", tpage, clut);
		FILE* f = fopen(buff, "wb");
		unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
		unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
		fwrite(TGAheader, sizeof(unsigned char), 12, f);
		fwrite(header, sizeof(unsigned char), 6, f);
		fwrite(tpage, sizeof(char), 256 * 256 * 2, f);
		fclose(f);
#endif

		SDL_free(tpage);
		break;
	}
	case TP_8BIT:
	{
		unsigned short* tpage = (unsigned short*)SDL_malloc(TPAGE_WIDTH * TPAGE_HEIGHT * sizeof(unsigned short));
#if defined(OGL) || defined(OGLES)
		glReadPixels(tpageX, tpageY, TPAGE_WIDTH, TPAGE_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &tpage[0]);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, &tpage[0]);
#endif
		
#if defined(_DEBUG) && 0
		char buff[64];
		sprintf(&buff[0], "TPAGE_%d_%d.TGA", tpage, clut);
		FILE* f = fopen(buff, "wb");
		unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
		unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
		fwrite(TGAheader, sizeof(unsigned char), 12, f);
		fwrite(header, sizeof(unsigned char), 6, f);
		fwrite(&tpage[0], sizeof(char), 256 * 256 * 2, f);
		fclose(f);
#endif
		SDL_free(tpage);
		break;
	}
	case TP_4BIT:
	{
		unsigned short clut[CLUT_WIDTH * CLUT_HEIGHT];

		//Read CLUT
#if defined(OGL) || defined(OGLES)
		glReadPixels(clutX, clutY, CLUT_WIDTH, CLUT_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &clut[0]);
#elif defined(D3D9)
		D3DLOCKED_RECT lockedRect;
		RECT convertedRect;
		convertedRect.top = clutY;
		convertedRect.bottom = clutY + CLUT_HEIGHT;
		convertedRect.left = clutX;
		convertedRect.right = clutX + CLUT_WIDTH;
		vramFrameBuffer->LockRect(&lockedRect, &convertedRect, D3DLOCK_READONLY);

		unsigned short* src = (unsigned short*)lockedRect.pBits;
		unsigned short* dest = clut;

		for (int y = 0; y < CLUT_HEIGHT; y++)
		{
			for (int x = 0; x < CLUT_WIDTH; x++)
			{
				dest[x] = src[x];
			}

			src += lockedRect.Pitch / sizeof(unsigned short);
			dest += CLUT_WIDTH;
		}

		vramFrameBuffer->UnlockRect();
#endif
		unsigned short* tpage = (unsigned short*)SDL_malloc(TPAGE_WIDTH / 4 * TPAGE_HEIGHT * sizeof(unsigned short));

#if defined(OGL) || defined(OGLES)
		//Read texture data
		glReadPixels(tpageX, tpageY, TPAGE_WIDTH / 4, TPAGE_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &tpage[0]);
#elif defined(D3D9)
		convertedRect.top = tpageY;
		convertedRect.bottom = tpageY + TPAGE_HEIGHT;
		convertedRect.left = tpageX;
		convertedRect.right = tpageX + (TPAGE_WIDTH / 4);
		vramFrameBuffer->LockRect(&lockedRect, &convertedRect, D3DLOCK_READONLY);

		src = (unsigned short*)lockedRect.pBits;
		dest = tpage;

		for (int y = 0; y < TPAGE_HEIGHT; y++)
		{
			for (int x = 0; x < (TPAGE_WIDTH / 4); x++)
			{
				dest[x] = src[x];
			}

			src += lockedRect.Pitch / sizeof(unsigned short);
			dest += (TPAGE_WIDTH / 4);
		}

		vramFrameBuffer->UnlockRect();
#endif

		unsigned short* convertedTpage = (unsigned short*)SDL_malloc(TPAGE_WIDTH * TPAGE_HEIGHT * sizeof(unsigned short));
		unsigned short* convertPixel = &convertedTpage[0];

		for (int xy = 0; xy < TPAGE_WIDTH / 4 * TPAGE_HEIGHT; xy++)
		{
			*convertPixel++ = clut[(tpage[xy] & (0xF << 0 * 4)) >> (0 * 4)];
			*convertPixel++ = clut[(tpage[xy] & (0xF << 1 * 4)) >> (1 * 4)];
			*convertPixel++ = clut[(tpage[xy] & (0xF << 2 * 4)) >> (2 * 4)];
			*convertPixel++ = clut[(tpage[xy] & (0xF << 3 * 4)) >> (3 * 4)];
		}

#if defined(OGLES)
#define ARGB1555toRGBA1555(x) ((x & 0x8000) >> 15) | ((x & 0x7FFF) << 1)
#pragma pack(push,1)
		struct rgba5551
		{
			unsigned short r : 5;
			unsigned short g : 5;
			unsigned short b : 5;
			unsigned short a : 1;
		};

		struct abgr1555
		{
			unsigned short a : 1;
			unsigned short b : 5;
			unsigned short g : 5;
			unsigned short r : 5;
		};
#pragma pack(pop)

		for (int xy = 0; xy < TPAGE_WIDTH * TPAGE_HEIGHT; xy++)
		{
			struct rgba5551* pixel = (struct rgba5551*) & convertedTpage[xy];
			struct abgr1555* pixel2 = (struct abgr1555*) & convertedTpage[xy];

			unsigned short r = pixel->r;
			unsigned short g = pixel->g;
			unsigned short b = pixel->b;
			unsigned short a = pixel->a;
			pixel2->a = a;
			pixel2->r = r;
			pixel2->g = g;
			pixel2->b = b;
		}

#endif

#if _DEBUG && 0
		char buff[64];
		sprintf(&buff[0], "TPAGE_%d_%d.TGA", tpage, clut);
		FILE* f = fopen(buff, "wb");
		unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
		unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
		fwrite(TGAheader, sizeof(unsigned char), 12, f);
		fwrite(header, sizeof(unsigned char), 6, f);
		fwrite(&convertedTpage[0], sizeof(char), 256 * 256 * 2, f);
		fclose(f);
#endif
#if defined(OGL) || defined(OGLES)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TPAGE_WIDTH, TPAGE_HEIGHT, 0, GL_RGBA, TEXTURE_FORMAT, &convertedTpage[0]);
#elif defined(D3D9)
		
		if FAILED(d3ddev->CreateTexture(TPAGE_WIDTH, TPAGE_HEIGHT, 0, 0, D3DFMT_A1R5G5B5, D3DPOOL_MANAGED, &tpageTexture->texture, NULL))
		{
			eprinterr("Failed to create tpage texture!\n");
			assert(FALSE);//Should never happen cannot continue anymore.
		}

		tpageTexture->texture->LockRect(0, &lockedRect, NULL, D3DLOCK_DISCARD);
		
		src = convertedTpage;
		dest = (unsigned short*)lockedRect.pBits;

		for (int y = 0; y < TPAGE_HEIGHT; y++)
		{
			for (int x = 0; x < TPAGE_WIDTH; x++)
			{
				dest[x] = src[x];
			}

			src += TPAGE_WIDTH;
			dest += lockedRect.Pitch / sizeof(unsigned short);
		}
		
		tpageTexture->texture->UnlockRect(0);

		//D3DXSaveTextureToFile("Debug.TGA", D3DXIFF_TGA, tpageTexture->texture, NULL);
#endif
		SDL_free(tpage);
		SDL_free(convertedTpage);
		
		break;
	}
	}

#if defined(OGL) || defined(OGLES)
	return tpageTexture->textureID;
#elif defined(D3D9)
	return tpageTexture->texture;
#elif defined(VK)
	return NULL;
#endif
}

void Emulator_DestroyFrameBuffer(unsigned int* fbo)
{
#if defined(OGL) || defined(OGLES)
	glDeleteFramebuffers(1, fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, g_defaultFBO);
#endif
}

static int g_PreviousBlendMode = -1;
static int g_PreviousSemiTrans = 0;

void Emulator_SetBlendMode(int mode, int semiTransparent)
{
	if (semiTransparent)
	{
		//If previous wasn't semi trans, enable blend
		if (g_PreviousSemiTrans == 0)
		{
#if defined(OGL) || defined(OGLES)
			glEnable(GL_BLEND);
#elif defined(D3D9)
			d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
#endif
		}

		if (g_PreviousBlendMode != mode)
		{
			switch (mode)
			{
			case BM_AVERAGE:
#if defined(OGL) || defined(OGLES)
				glBlendFuncSeparate(GL_CONSTANT_ALPHA, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
#elif defined(D3D9)
				d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
				d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BLENDFACTOR);
				d3ddev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
				d3ddev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
#endif
				break;
			case BM_ADD:
#if defined(OGL) || defined(OGLES)
				glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
#elif defined(D3D9)
				d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
				d3ddev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
#endif
				break;
			case BM_SUBTRACT:
#if defined(OGL) || defined(OGLES)
				glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
#elif defined(D3D9)
				d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
				d3ddev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
#endif
				break;
			case BM_ADD_QUATER_SOURCE:
#if defined(OGL) || defined(OGLES)
				glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
#elif defined(D3D9)
				d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
				d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
				d3ddev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
#endif
				break;
			default:
#if defined(OGL) || defined(OGLES)
				glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
#endif
				break;
			}

			g_PreviousBlendMode = mode;
		}
	}
	else
	{
		//If previous was semi trans disable blend
		if (g_PreviousSemiTrans)
		{
#if defined(OGL) || defined(OGLES)
			glDisable(GL_BLEND);
#elif defined(D3D9)
			d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
#endif
		}
	}

	g_PreviousSemiTrans = semiTransparent;
}

#if defined(OGLES) || defined(OGL) || defined(D3D9) || defined(VK)
void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
{
#if defined(OGL) || defined(OGLES)
	float a = 2.0f / (right - left);
	float b = 2.0f / (top - bottom);
	float c = -2.0f / (zfar - znear);

	float tx = -(right + left) / (right - left);
	float ty = -(top + bottom) / (top - bottom);
	float tz = -(zfar + znear) / (zfar - znear);

	float ortho[16] =
	{
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		tx, ty, tz, 1
	};

	GLint projectionUniform = glGetUniformLocation(g_defaultShaderProgram, "Projection");
	glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &ortho[0]);
#elif defined(D3D9)
	D3DXMATRIX ortho;
	D3DXMatrixOrthoOffCenterLH(&ortho, left, right, top, bottom, -1.0f, 1.0f);
	d3ddev->SetTransform(D3DTS_PROJECTION, &ortho);
#endif
}

void Emulator_Scalef(float sx, float sy, float sz)
{
#if defined(OGL) || defined(OGLES)
	float scale[16] =
	{
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1
	};

	GLint scaleUniform = glGetUniformLocation(g_defaultShaderProgram, "Scale");
	glUniformMatrix4fv(scaleUniform, 1, GL_FALSE, &scale[0]);
#endif

}

#endif

void Emulator_GetTopLeftAndBottomLeftTextureCoordinate(int* x, int* y, int* w, int* h, unsigned char* u, unsigned char* v)
{
	int topCoordX = -1;
	int topCoordY = -1;
	int bottomCoordX = -1;
	int bottomCoordY = -1;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			//Skip same coordinate
			if (i == j)
			{
				continue;
			}

			//This is a left coord
			if (u[j] < u[i])
			{
				topCoordX = u[j];
			}

			//This is a top coord
			if (v[i] < v[j])
			{
				topCoordY = v[i];
			}
		}
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			//Skip same coordinate
			if (i == j)
			{
				continue;
			}

			//This is a right coord
			if (u[j] > u[i])
			{
				bottomCoordX = u[j];
			}

			//This is a bottom coord
			if (v[i] > v[j])
			{
				bottomCoordY = v[i];
			}
		}
	}

	*x = topCoordX;
	*y = topCoordY;
	*w = (bottomCoordX - topCoordX) + 1;
	*h = (bottomCoordY - topCoordY) + 1;

	//Round up next multiple of 2
	//*w = (*w + 1) & ~0x1;
	//*h = (*h + 1) & ~0x1;

	//Round down next multiple of 2
	//*w -= (*w % 2);
	//*h -= (*h % 2);
}

#define EXTERNAL_LOGO

void Emulator_HintTextureAtlas(unsigned short texTpage, unsigned short texClut, unsigned char u0, unsigned char v0, unsigned char u1, unsigned char v1, unsigned char u2, unsigned char v2, unsigned char u3, unsigned char v3, unsigned short bIsQuad)
{
	//Locate the 4-bit texture in vram, convert it and glTexSubImage to the atlas
	unsigned int tpageX = GET_TPAGE_X(texTpage);
	unsigned int tpageY = GET_TPAGE_Y(texTpage);
	unsigned int clutX = GET_CLUT_X(texClut);
	unsigned int clutY = GET_CLUT_Y(texClut);

	//Set this to true so the emulator uses atlas textures
	g_hasHintedTextureAtlas = 1;

	int x = 0, y = 0, w = 0, h = 0;
	unsigned char textureCoordsU[] = { u0, u1, u2, u3 };
	unsigned char textureCoordsV[] = { v0, v1, v2, v3 };

	/* Get the top left and bottom left coordinate for TOMB5, return them plus width height */
	Emulator_GetTopLeftAndBottomLeftTextureCoordinate(&x, &y, &w, &h, &textureCoordsU[0], &textureCoordsV[0]);

	//Check if this tpage is already in our cache!
	struct CachedTexture* tpageTexture = Emulator_FindTextureInCache(texTpage, texClut);
	int bMustAddTexture = (tpageTexture == NULL) ? 1 : 0;

	//If not in cache, generate new texture for this tpage!
	if (bMustAddTexture)
	{
		tpageTexture = Emulator_GetFreeCachedTexture();
		tpageTexture->tpage = texTpage;
		tpageTexture->clut = texClut;
#if defined(OGL) || defined(OGLES)
		glGenTextures(1, &tpageTexture->textureID);
		Emulator_BindTexture(tpageTexture->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TPAGE_WIDTH, TPAGE_HEIGHT, 0, GL_RGBA, TEXTURE_FORMAT, NULL);
#endif
	}
	else
	{
#if defined(OGL) || defined(OGLES)
		Emulator_BindTexture(tpageTexture->textureID);
#endif
	}

#if defined(OGL) || defined(OGLES)
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
#endif

	unsigned short* texturePage = (unsigned short*)SDL_malloc(sizeof(unsigned short) * w * h * 1024);
	unsigned short* clut = (unsigned short*)SDL_malloc(sizeof(unsigned short) * 16);
	unsigned short* convertedTpage = (unsigned short*)SDL_malloc(sizeof(unsigned short) * w * h * 1024);

#if defined(OGL) || defined(OGLES)
	//Read CLUT
	glReadPixels(clutX, clutY, CLUT_WIDTH, CLUT_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &clut[0]);

	//Read texture data
	glReadPixels(tpageX + (x / 4), tpageY + y, w / 4, h, GL_RGBA, TEXTURE_FORMAT, &texturePage[0]);
#endif

	unsigned short* convertPixel = &convertedTpage[0];

	for (int xy = 0; xy < (w / 4) * h; xy++)
	{
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 0 * 4)) >> (0 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 1 * 4)) >> (1 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 2 * 4)) >> (2 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 3 * 4)) >> (3 * 4)];
	}

#if defined(OGLES)
#define ARGB1555toRGBA1555(x) ((x & 0x8000) >> 15) | ((x & 0x7FFF) << 1)
#pragma pack(push,1)
	struct rgba5551
	{
		unsigned short r : 5;
		unsigned short g : 5;
		unsigned short b : 5;
		unsigned short a : 1;
	};

	struct abgr1555
	{
		unsigned short a : 1;
		unsigned short b : 5;
		unsigned short g : 5;
		unsigned short r : 5;
	};
#pragma pack(pop)

	for (int xy = 0; xy < w * h; xy++)
	{
		struct rgba5551* pixel = (struct rgba5551*) & convertedTpage[xy];
		struct abgr1555* pixel2 = (struct abgr1555*) & convertedTpage[xy];

		unsigned short r = pixel->r;
		unsigned short g = pixel->g;
		unsigned short b = pixel->b;
		unsigned short a = pixel->a;
		pixel2->a = a;
		pixel2->r = r;
		pixel2->g = g;
		pixel2->b = b;
	}

#endif

#if defined(OGL) || defined(OGLES)
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, TEXTURE_FORMAT, &convertedTpage[0]);
#endif

#if defined(_DEBUG) && 0
	char buf[32];
	sprintf(&buf[0], "TEX_%d.TGA", texTpage);
	Emulator_SaveVRAM(buf, 0, 0, TPAGE_WIDTH, TPAGE_HEIGHT, FALSE);
#endif

	SDL_free(clut);
	SDL_free(texturePage);
	SDL_free(convertedTpage);

	//Set this to false so the emulator can search up and add textures
	//That are not atlas hinted
	//g_hasHintedTextureAtlas = 0;
}


void Emulator_InjectTIM(char* fileName, unsigned short texTpage, unsigned short texClut, unsigned char u0, unsigned char v0, unsigned char u1, unsigned char v1, unsigned char u2, unsigned char v2, unsigned char u3, unsigned char v3)
{
	/* Take from atlas */
	g_hasHintedTextureAtlas = 1;

	int x = 0, y = 0, w = 0, h = 0;
	unsigned char textureCoordsU[] = { u0, u1, u2, u3 };
	unsigned char textureCoordsV[] = { v0, v1, v2, v3 };

	/* Get the top left and bottom left coordinate for TOMB5, return them plus width height */
	Emulator_GetTopLeftAndBottomLeftTextureCoordinate(&x, &y, &w, &h, &textureCoordsU[0], &textureCoordsV[0]);

	//Check if this tpage is already in our cache!
	struct CachedTexture* tpageTexture = Emulator_FindTextureInCache(texTpage, texClut);

	//Not in cache, why are we injecting? ; - )
	if (tpageTexture == NULL)
	{
		return;
	}

#if defined(OGL) || defined(OGLES)
	Emulator_BindTexture(tpageTexture->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
	unsigned short* texturePage = (unsigned short*)SDL_malloc(sizeof(unsigned short) * ((w * h) / 2));
	unsigned short* clut = (unsigned short*)SDL_malloc(sizeof(unsigned short) * 16);
	unsigned short* convertedTpage = (unsigned short*)SDL_malloc(sizeof(unsigned short) * (w * h));

	FILE* f = fopen("LOGO.TIM", "rb");
	fseek(f, 20, SEEK_SET);
	fread(&clut[0], 16 * sizeof(short), 1, f);
	fseek(f, 64, SEEK_SET);
	fread(&texturePage[0], (w * h) / 2, 1, f);
	fclose(f);

	//For LOGO only, temporarily set injection x y position on 256x256 tpage
	x = 0;
	y = 68;

	unsigned short* convertPixel = &convertedTpage[0];

	for (int xy = 0; xy < (w / 4) * h; xy++)
	{
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 0 * 4)) >> (0 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 1 * 4)) >> (1 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 2 * 4)) >> (2 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 3 * 4)) >> (3 * 4)];
	}

#if defined(OGLES)
#define ARGB1555toRGBA1555(x) ((x & 0x8000) >> 15) | ((x & 0x7FFF) << 1)
#pragma pack(push,1)
	struct rgba5551
	{
		unsigned short r : 5;
		unsigned short g : 5;
		unsigned short b : 5;
		unsigned short a : 1;
	};

	struct abgr1555
	{
		unsigned short a : 1;
		unsigned short b : 5;
		unsigned short g : 5;
		unsigned short r : 5;
	};
#pragma pack(pop)

	for (int xy = 0; xy < w * h; xy++)
	{
		struct rgba5551* pixel = (struct rgba5551*) & convertedTpage[xy];
		struct abgr1555* pixel2 = (struct abgr1555*) & convertedTpage[xy];

		unsigned short r = pixel->r;
		unsigned short g = pixel->g;
		unsigned short b = pixel->b;
		unsigned short a = pixel->a;
		pixel2->a = a;
		pixel2->r = r;
		pixel2->g = g;
		pixel2->b = b;
	}

#endif

#if defined(OGL) || defined(OGLES)
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, TEXTURE_FORMAT, &convertedTpage[0]);
#endif

#if defined(_DEBUG) && 0
	char buf[32];
	sprintf(&buf[0], "TEX_%d.TGA", texTpage);
	Emulator_SaveVRAM(buf, 0, 0, TPAGE_WIDTH, TPAGE_HEIGHT, FALSE);
#endif

	SDL_free(clut);
	SDL_free(texturePage);
	SDL_free(convertedTpage);

	//Set this to false so the emulator can search up and add textures
	//That are not atlas hinted
	g_hasHintedTextureAtlas = 1;
}

void Emulator_DestroyAllTextures()
{
	//Initial texture id is -1
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
#if defined(OGL) || defined(OGLES)
		if (cachedTextures[i].textureID != 0xFFFFFFFF)
		{
			Emulator_DestroyTextures(1, &cachedTextures[i].textureID);
		}
#elif defined(D3D9)
		if (cachedTextures[i].texture != NULL)
		{
			Emulator_DestroyTextures(cachedTextures[i].texture);
		}
#endif
	}

#if defined(OGL) || defined(OGLES)
	//Initialise texture cache
	SDL_memset(&cachedTextures[0], -1, MAX_NUM_CACHED_TEXTURES * sizeof(struct CachedTexture));
#elif defined(D3D9)
	SDL_memset(&cachedTextures[0], 0, MAX_NUM_CACHED_TEXTURES * sizeof(struct CachedTexture));
#endif
	return;
}

void Emulator_SetPGXPVertexCount(int vertexCount)
{
#if defined(PGXP)
	pgxp_vertex_count = vertexCount;
#endif
}

void Emulator_SetViewPort(int x, int y, int width, int height)
{
#if defined(OGL) || defined(OGLES)
	glViewport(x, y, width, height);
#elif defined(D3D9)
	D3DVIEWPORT9 viewPort;
	viewPort.X = x;
	viewPort.Y = y;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;
	d3ddev->SetViewport(&viewPort);
#elif defined(VK)
	VkViewport viewPort;
	viewPort.x = x;
	viewPort.y = y;
	viewPort.width = width;
	viewPort.height = height;
	viewPort.minDepth = 0.0f;
	viewPort.maxDepth = 1.0f;
	//assert(FALSE);//Unfinished see below.
	//vkCmdSetViewport(draw_cmd, 0, 1, &viewport);
#endif
}

void Emulator_SetScissorBox(int x, int y, int width, int height)
{
#if defined(OGL) || defined(OGLES)
	glScissor(x, y, width, height);
#elif defined(D3D9)
	RECT scissorBox;
	scissorBox.top = y;
	scissorBox.bottom = y + height;
	scissorBox.left = x;
	scissorBox.right = x + width;
	d3ddev->SetScissorRect(&scissorBox);
#elif defined(VK)
	VkRect2D scissorBox;
	scissorBox.offset.x = x;
	scissorBox.offset.y = y;
	scissorBox.extent.width = width;
	scissorBox.extent.height = height;
	//assert(FALSE);//Unfinished see below.
	//vkCmdSetScissor(draw_cmd, 0, 1, &scissor);
#endif
}

#if defined(OGL) || defined(OGLES)
void Emulator_BindFrameBuffer(GLuint frameBufferObject)
#elif defined(D3D9)
void Emulator_BindFrameBuffer(IDirect3DSurface9* frameBufferObject)
#elif defined(VK)
void Emulator_BindFrameBuffer(struct FrameBuffer frameBufferObject)
#endif
{
#if defined(OGL) || defined(OGLES)
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
#elif defined(D3D9)
	d3ddev->SetRenderTarget(0, frameBufferObject);
#elif defined(VK)
	//assert(FALSE);//unimplemented
#endif
}

void Emulator_CreateVertexBuffer(int numVertices, int vertexStride, void* pVertices)
{
#if defined(OGL) || defined(OGLES)
	glBufferData(GL_ARRAY_BUFFER, vertexStride * numVertices, pVertices, GL_STATIC_DRAW);
#elif defined(D3D9)
	d3ddev->CreateVertexBuffer(vertexStride * numVertices, 0, (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0), D3DPOOL_MANAGED, &g_vertexBufferObject, NULL);
	VOID* pVertexData;
	g_vertexBufferObject->Lock(0, 0, (void**)&pVertexData, 0);
	memcpy(pVertexData, pVertices, vertexStride * numVertices);
	g_vertexBufferObject->Unlock();
	d3ddev->SetStreamSource(0, g_vertexBufferObject, 0, vertexStride);
#elif defined(VK)

#endif
}