#ifndef EMULATOR_PLATFORM_SETUP_H
#define EMULATOR_PLATFORM_SETUP_H

/*
 * Platform specific emulator setup
 */
#if (defined(_WINDOWS) || defined(__APPLE__) || defined(__linux__) || defined(__MINGW32__)) && !defined(__ANDROID__)
//Open Graphics Library (Embedded Systems)
//#define OGLES
//#define OGLES_VERSION 2

//Open Graphics Library
#define OGL

//Direct3D9
//#define D3D9

//Vulkan
//#define VK

#if defined(OGL)
#define SDL2
#define GLEW
#endif

#elif defined(__EMSCRIPTEN__) || defined(__ANDROID__)
#define OGLES
#define OGLES_VERSION (2)
#if OGLES_VERSION == 2
#define ES2_SHADERS
#elif OGLES_VERSION == 3
#define ES3_SHADERS
#endif
#define SDL2
#endif

#if defined(GLEW)
#define GL_GLEXT_PROTOTYPES 1
#include <GL/glew.h>
#endif

/*
 * Emulator render options.
 */
#define RO_DOUBLE_BUFFERED

#if defined(__APPLE__) || defined(__EMSCRIPTEN__)
//#include <stddef.h>
#endif

/*
 * SDL.H inclusion.
 */

#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#elif defined(__EMSCRIPTEN__)
#include <SDL2/SDL.h>
#elif (defined(_WINDOWS) || defined(__MINGW32__) || defined(__linux__)) && !defined(__ANDROID__)
#include <SDL.h>
#elif defined (__ANDROID__)
#include <SDL.h>
#endif

#if defined (OGL)
#include <SDL_opengl.h>///@FIXME see mac!
#elif defined (OGLES)
#include <SDL_syswm.h>
#if OGLES_VERSION == 2
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif OGLES_VERSION == 3
#include <GLES3/gl3.h>
#endif
#include <EGL/egl.h>
#elif defined(VK)
#include <SDL_syswm.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#elif defined(D3D9)
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#endif

#if !defined (__EMSCRIPTEN__)
//#include <SDL_gamecontroller.h>
#endif

#if defined(OGL)
#define TEXTURE_FORMAT GL_UNSIGNED_SHORT_1_5_5_5_REV
#elif defined(OGLES)
#define TEXTURE_FORMAT GL_UNSIGNED_SHORT_5_5_5_1
#endif

#endif