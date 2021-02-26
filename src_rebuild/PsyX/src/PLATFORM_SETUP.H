#ifndef EMULATOR_PLATFORM_SETUP_H
#define EMULATOR_PLATFORM_SETUP_H

#ifndef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

/*
 * Platform specific emulator setup
 */
#if (defined(_WINDOWS) || defined(__APPLE__) || defined(__linux__) || defined(__MINGW32__)) && !defined(__ANDROID__)
//Open Graphics Library (Embedded Systems)
//#define OGLES
//#define OGLES_VERSION 2

//Open Graphics Library
#define RENDERER_OGL

#if defined(RENDERER_OGL)
#define SDL2
#define GLEW
#endif

#elif defined(__EMSCRIPTEN__)
#define OGLES
#define OGLES_VERSION (2)
#elif defined(__ANDROID__)
#define OGLES
#define OGLES_VERSION (3)
#if OGLES_VERSION == 2
#define ES2_SHADERS
#elif OGLES_VERSION == 3
#define ES3_SHADERS
#endif
#define SDL2
#endif

#if defined(GLEW)
#define GL_GLEXT_PROTOTYPES 1
#include "COMMON/glad.h"
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

#if defined (RENDERER_OGL)
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
#endif

#if !defined (__EMSCRIPTEN__)
//#include <SDL_gamecontroller.h>
#endif

#if defined(RENDERER_OGL)
#define TEXTURE_FORMAT GL_UNSIGNED_SHORT_1_5_5_5_REV
#elif defined(OGLES)
#define TEXTURE_FORMAT GL_UNSIGNED_SHORT_5_5_5_1
#endif

#ifdef _MSC_VER
#define FUNCNAME __FUNCTION__
#else
#define FUNCNAME __func__
#endif

#if defined(__ANDROID__)
#include <android/log.h>
#define LOG_TAG_EMU "[PsyX] "
#define eprintf(fmt, ...)       __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG_EMU, fmt, ##__VA_ARGS__)
#define eprintinfof(fmt, ...)   __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG_EMU " [INFO]", fmt, ##__VA_ARGS__)
#define eprintwarnf(fmt, ...)   __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG_EMU " [WARN]", fmt, ##__VA_ARGS__)
#define eprinterr(fmt, ...)     eprintf("[%s] - " fmt, FUNCNAME, ##__VA_ARGS__);
#else
#include "PSYX_GLOBALS.H"
#define eprintf(fmt, ...)       PsyX_Log("[Psy-X] " fmt, ##__VA_ARGS__)
#define eprintinfo(fmt, ...)    PsyX_Log_Info("[Psy-X] " fmt, ##__VA_ARGS__)
#define eprintwarn(fmt, ...)    PsyX_Log_Warning("[Psy-X] " fmt, ##__VA_ARGS__)
#define eprinterr(fmt, ...)     PsyX_Log_Error("[Psy-X] [%s] - " fmt, FUNCNAME, ##__VA_ARGS__);
#endif

#if defined(__EMSCRIPTEN__) || !defined(_DEBUG)
#define PSYX_UNIMPLEMENTED()
#else
#define PSYX_UNIMPLEMENTED() eprinterr("Unimplemented!\n");
#endif

#endif