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

#define SWAP_INTERVAL      (2)

#if defined(NTSC_VERSION)
#define COUNTER_UPDATE_INTERVAL (263)
#else
#define COUNTER_UPDATE_INTERVAL (313)
#endif

#include <stdio.h>
#include <string.h>
#include <SDL.h>

SDL_Window* g_window = NULL;

#if defined(VK)

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
unsigned int whiteTexture;
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
#endif

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

int g_swapInterval = SWAP_INTERVAL;
int g_wireframeMode = 0;
int g_texturelessMode = 0;
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
		vertex[0].x = p0[0];
		vertex[0].y = p0[1];
	}

	if (p1 != NULL)
	{
		vertex[1].x = p1[0];
		vertex[1].y = p1[1];
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
		vertex[0].x = p0[0];
		vertex[0].y = p0[1];
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
		vertex[1].x = p1[0];
		vertex[1].y = p1[1];
#endif
	}
	else
	{
		if (p0 != NULL && w != -1 && h != -1)
		{
			vertex[1].x = p0[0];
			vertex[1].y = p0[1] + h;
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
		vertex[2].x = p2[0];
		vertex[2].y = p2[1];
#endif
	}
	else
	{
		if (p0 != NULL && w != -1 && h != -1)
		{
			vertex[2].x = p0[0] + w;
			vertex[2].y = p0[1] + h;
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
		vertex[3].x = p3[0];
		vertex[3].y = p3[1];
#endif
	}
	else
	{
		if (p0 != NULL && w != -1 && h != -1)
		{
			vertex[3].x = p0[0] + w;
			vertex[3].y = p0[1];
		}
	}
}


void Emulator_GenerateTexcoordArrayQuad(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short page, short clut, unsigned char dither)
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
		vertex[0].x = p0[0];
		vertex[0].y = p0[1];
	}

	if (uv1 != NULL)
	{
		vertex[1].x = p1[0];
		vertex[1].y = p1[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[1].x = p0[0];
			vertex[1].y = p0[1] + h;
		}
	}

	if (uv2 != NULL)
	{
		vertex[2].x = p2[0];
		vertex[2].y = p2[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[2].x = p0[0] + w;
			vertex[2].y = p0[1] + h;
		}
	}

	if (uv3 != NULL)
	{
		vertex[3].x = p3[0];
		vertex[3].y = p3[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[3].x = p0[0] + w;
			vertex[3].y = p0[1];
		}
	}
#else
	assert(uv0);
	if (!uv1) uv1 = uv0;
	if (!uv2) uv2 = uv0;
	if (!uv3) uv3 = uv0;

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
#endif
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

void Emulator_GenerateTexcoordArrayZero(struct Vertex* vertex, unsigned char dither)
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

void Emulator_GenerateColourArrayQuad(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3)
{
	assert(col0);
	if (!col1) col1 = col0;
	if (!col2) col2 = col0;
	if (!col3) col3 = col0;

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

ShaderID g_gte_shader;
ShaderID g_blit_shader;

#if defined(OGLES) || defined(OGL)
GLint u_Projection;

// TODO: 8 bit palettized images and full mode textures
const char* gte_shader =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"varying vec4 v_page_clut;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
	"	attribute vec4 a_color;\n"
	"	uniform mat4 Projection;\n"
	"	void main() {\n"
	"		v_texcoord = a_texcoord;\n"
	"		v_color = a_color;\n"
	"		v_color.xyz *= a_texcoord.z;\n"
	"		v_page_clut.x = fract(a_position.z / 16.0) * 1024.0;\n"
	"		v_page_clut.y = floor(a_position.z / 16.0) * 256.0;\n"
	"		v_page_clut.z = fract(a_position.w / 64.0);\n"
	"		v_page_clut.w = floor(a_position.w / 64.0) / 512.0;\n"
	"		gl_Position = Projection * vec4(a_position.xy, 0.0, 1.0);\n"
	"	}\n"
	"#else\n"
	"	uniform sampler2D s_texture;\n"
	"	void main() {\n"
	"		vec2 uv = (v_texcoord.xy * vec2(0.25, 1.0) + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
	"		vec2 comp = texture2D(s_texture, uv).rg;\n"
	"		int index = int(fract(v_texcoord.x / 4.0 + 0.0001) * 4.0);\n"
	"\n"
	"		float v = comp[index / 2] * (255.0 / 16.0);\n"
	"		float f = floor(v);\n"
	"\n"
	"		vec2 c = vec2( (v - f) * 16.0, f );\n"
	"\n"
	"		vec2 clut_pos = v_page_clut.zw;\n"
	"		clut_pos.x += mix(c[0], c[1], fract(float(index) / 2.0) * 2.0) / 1024.0;\n"
	"		vec2 clut_color = texture2D(s_texture, clut_pos).rg * 255.0;\n"
	"\n"
	"		float color_16 = clut_color.y * 256.0 + clut_color.x;\n"
	"		vec4 color = fract(floor(color_16 / vec4(1.0, 32.0, 1024.0, 32768.0)) / 32.0);\n"
	"\n"
	"		fragColor = color * v_color;\n"
	"		if (fragColor.r == 0.0 && fragColor.b == 0.0 && fragColor.b == 0.0 && fragColor.a == 0.0) { discard; }\n"
	"\n"
	"		mat4 dither = mat4(\n"
	"			-4.0,  +0.0,  -3.0,  +1.0,\n"
	"			+2.0,  -2.0,  +3.0,  -1.0,\n"
	"			-3.0,  +1.0,  -4.0,  +0.0,\n"
	"			+3.0,  -1.0,  +2.0,  -2.0) / 255.0;\n"
	"		ivec2 dc = ivec2(fract(gl_FragCoord.xy / 4.0) * 4.0);\n"
	"		fragColor.xyz += vec3(dither[dc.x][dc.y] * v_texcoord.w);\n"
	"\n"
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
	"	uniform sampler2D s_texture;\n"
	"	void main() {\n"
	"		vec2 color_rg = texture2D(s_texture, v_texcoord.xy).rg * 255.0;\n"
	"		float color_16 = color_rg.y * 256.0 + color_rg.x;\n"
	"		fragColor = fract(floor(color_16 / vec4(1.0, 32.0, 1024.0, 32768.0)) / 32.0);\n"
	"		fragColor.a = 1.0;\n"
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

    glLinkProgram(program);
    Shader_CheckProgramStatus(program);

    GLint sampler = 0;
    glUseProgram(program);
    glUniform1iv(glGetUniformLocation(program, "s_texture"), 1, &sampler);
    glUseProgram(0);

    return program;
}
#elif defined(D3D9)

#include "shaders/gte_shader_vs.h"
#include "shaders/gte_shader_ps.h"
#include "shaders/blit_shader_vs.h"
#include "shaders/blit_shader_ps.h"

// shader registers
const int u_Projection = 0;
const int u_PageClut   = 4;

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
#elif
    #error
#endif

void Emulator_CreateGlobalShaders()
{
	g_gte_shader  = Shader_Compile(gte_shader);
	g_blit_shader = Shader_Compile(blit_shader);

#if defined(OGL) || defined(OGLES)
	u_Projection = glGetUniformLocation(g_gte_shader, "Projection");
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
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RG, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &dynamic_vertex_buffer);
	glGenVertexArrays(1, &dynamic_vertex_array);
	glBindVertexArray(dynamic_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, dynamic_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);
	
    glEnableVertexAttribArray(a_color);
	glVertexAttribPointer(a_position, 4, GL_SHORT,         GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->x);
	glVertexAttribPointer(a_texcoord, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->u);
	glVertexAttribPointer(a_color,    4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(Vertex), &((Vertex*)NULL)->r);
	glBindVertexArray(0);
#elif defined(D3D9)
	d3ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	if (FAILED(d3ddev->CreateTexture(VRAM_WIDTH, VRAM_HEIGHT, 1, 0, D3DFMT_A8L8, D3DPOOL_MANAGED, &vramTexture, NULL)))
	{
		eprinterr("Failed to create render target texture!\n");
		return FALSE;
	}

	#define OFFSETOF(T, E)     ((size_t)&(((T*)0)->E))

	const D3DVERTEXELEMENT9 VERTEX_DECL[] = {
		{0, OFFSETOF(Vertex, x), D3DDECLTYPE_SHORT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // a_position
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

#if 0
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

int Emulator_Initialise()
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

void Emulator_SetTexture(TextureID texture)
{
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
#elif
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

void Emulator_SetShader(const ShaderID &shader)
{
#if defined(OGL) || defined(OGLES)
    glUseProgram(shader);
#elif defined(D3D9)
    d3ddev->SetVertexShader(shader.VS);
    d3ddev->SetPixelShader(shader.PS);
#elif
    #error
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

    for (int y = 0; y < h; y++) {
        SDL_memcpy(dst, src, w * 2);
        dst += VRAM_WIDTH;
        src += stride;
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
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, VRAM_WIDTH, VRAM_HEIGHT, GL_RG, GL_UNSIGNED_BYTE, vram);
#elif defined(D3D9)
	D3DLOCKED_RECT rect;
	HRESULT hr = vramTexture->LockRect(0, &rect, NULL, 0);
	assert(!FAILED(hr));
	memcpy(rect.pBits, vram, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));
	vramTexture->UnlockRect(0);
#endif
}

void Emulator_BlitVRAM()
{
	if (activeDispEnv.isinter)
	{
		//Emulator_Clear(0, 0, activeDispEnv.disp.w, activeDispEnv.disp.h, 128, 128, 128);
		return;
	}

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
	Emulator_SetBlendMode(0, 0);
	Emulator_DrawTriangles(0, 2);

	Emulator_SetShader(g_gte_shader);
}

void Emulator_DoPollEvent()
{
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
#elif defined(D3D9)
	d3ddev->BeginScene();
	d3ddev->SetVertexDeclaration(vertexDecl);
	d3ddev->SetStreamSource(0, dynamic_vertex_buffer, 0, sizeof(Vertex));
#endif

	Emulator_UpdateVRAM();
	Emulator_SetTexture(vramTexture);
	Emulator_SetViewPort(0, 0, windowWidth, windowHeight);

	Emulator_SetShader(g_gte_shader);
	Emulator_Ortho2D(0.0f, activeDispEnv.disp.w, activeDispEnv.disp.h, 0.0f, 0.0f, 1.0f);

	begin_scene_flag = true;

	if (g_wireframeMode)
	{
		Emulator_SetWireframe(true);
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
	// also poll events here
	Emulator_DoPollEvent();

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
	if (g_swapInterval == 2) {
		// D3D9 support D3DPRESENT_INTERVAL_TWO only in fullscreen mode
		// so we add additional one frame wait here, bad hack
		Sleep(16 + 4); // 16 ms - 60 Hz
	}

	if (d3ddev->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST) {
		Emulator_ResetDevice();
	}
#endif
#else
	glFinish();
#endif
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
#if defined(OGL) || defined(OGLES)
	Emulator_DestroyTexture(vramTexture);
	Emulator_DestroyTexture(whiteTexture);
#endif

	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

#if defined(VK)
	vkDestroySurfaceKHR(instance, surface, 0);
	vkDestroyInstance(instance, NULL);
#elif defined(D3D9)
	d3ddev->Release();
	d3d->Release();
#endif

	SDL_DestroyWindow(g_window);
	SDL_Quit();
	exit(0);
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
				glBlendColor(0.5f, 0.5f, 0.5f, 0.5f);
				glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_COLOR);
				glBlendEquation(GL_FUNC_ADD);
#elif defined(D3D9)
				d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(128, 128, 128, 128));
				d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
				d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BLENDFACTOR);
#endif
				break;
			case BM_ADD:
#if defined(OGL) || defined(OGLES)
				glBlendFunc(GL_ONE, GL_ONE);
				glBlendEquation(GL_FUNC_ADD);
#elif defined(D3D9)
				d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
#endif
				break;
			case BM_SUBTRACT:
#if defined(OGL) || defined(OGLES)
				glBlendFunc(GL_ONE, GL_ONE);
				glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
#elif defined(D3D9)
				d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
				d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
#endif
				break;
			case BM_ADD_QUATER_SOURCE:
#if defined(OGL) || defined(OGLES)
				glBlendColor(0.25f, 0.25f, 0.25f, 0.25f);
				glBlendFunc(GL_CONSTANT_COLOR, GL_ONE);
				glBlendEquation(GL_FUNC_ADD);
#elif defined(D3D9)
				d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(64, 64, 64, 64));
				d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
				d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
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
	glUniformMatrix4fv(u_Projection, 1, GL_FALSE, &ortho[0]);
#elif defined(D3D9)
	d3ddev->SetVertexShaderConstantF(u_Projection, ortho, 4);
#endif
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
	D3DVIEWPORT9 viewport;
	viewport.X      = x;
	viewport.Y      = y;
	viewport.Width  = width;
	viewport.Height = height;
	viewport.MinZ   = 0.0f;
	viewport.MaxZ   = 1.0f;
	d3ddev->SetViewport(&viewport);
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

void Emulator_SetRenderTarget(const RenderTargetID &frameBufferObject)
{
#if defined(OGL) || defined(OGLES)
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
#elif defined(D3D9)
	d3ddev->SetRenderTarget(0, frameBufferObject);
#elif defined(VK)
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

void Emulator_DrawLines(int start_vertex, int lines)
{
#if defined(OGL) || defined(OGLES)
	glDrawArrays(GL_LINES, start_vertex, lines * 2);
#elif defined(D3D9)
	d3ddev->DrawPrimitive(D3DPT_LINELIST, start_vertex, lines);
#else
	#error
#endif
}
