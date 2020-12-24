#ifndef PSYX_CONFIG_H
#define PSYX_CONFIG_H


// Required. Uses 32 bit pointers on P_TAG and other primitives
#define USE_EXTENDED_PRIM_POINTERS

// PGXP-Z: Precise GTE transform pipeline with Z-depth and widescreen fixes. Recommended
#define USE_PGXP

// Renderer to use. Currently only OpenGL is supported
#define RENDERER_OGL

#endif // PSYX_CONFIG_H