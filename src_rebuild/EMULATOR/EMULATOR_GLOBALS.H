#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H


#include <SDL_gamecontroller.h>


#if defined(D3D9)
extern IDirect3DTexture9* nullWhiteTexture;
extern IDirect3DTexture9* vramTexture;
extern IDirect3DSurface9* vramFrameBuffer;
extern LPDIRECT3DVERTEXBUFFER9 g_vertexBufferObject;
#elif defined(VK)

struct FrameBufferAttachment 
{
	VkImage image;
	VkDeviceMemory mem;
	VkImageView view;
};

struct FrameBuffer
{
	int32_t width, height;
	VkFramebuffer frameBuffer;
	FrameBufferAttachment color, depth;
	VkRenderPass renderPass;
	VkSampler sampler;
	VkDescriptorImageInfo descriptor;
};

extern struct FrameBuffer vramFrameBuffer;
extern unsigned int nullWhiteTexture;
#else
extern unsigned int nullWhiteTexture;
extern unsigned int vramFrameBuffer;
extern unsigned int vramTexture;
#endif
extern int screenWidth;
extern int screenHeight;
extern int windowWidth;
extern int windowHeight;
extern uint32_t DMAControlRegister;
extern int assetsLoaded;
extern unsigned int g_defaultShaderProgram;

#if defined(OGL) || defined(OGLES) || defined(VK)
extern int g_defaultFBO;
#elif defined(D3D9)
extern IDirect3DSurface9* g_defaultFBO;
#else
extern int g_defaultFBO;
#endif

struct CachedTexture
{
#if defined(OGL) || defined(OGLES)
	unsigned int textureID;
#elif defined(D3D9)
	IDirect3DTexture9* texture;
#endif
	unsigned short tpage;
	unsigned short clut;
	unsigned int lastAccess;
};

#define MAX_NUM_CACHED_TEXTURES (512)

extern struct CachedTexture cachedTextures[MAX_NUM_CACHED_TEXTURES];

extern unsigned short UpdateGameControllerInput(SDL_GameController* pad);
extern unsigned short UpdateKeyboardInput();

extern SDL_GameController* padHandle[];
extern unsigned char* padData[];
extern const unsigned char* keyboardState;

#endif