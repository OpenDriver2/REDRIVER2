if(MSVC)

Message("Compiling for Windows!")

#SET(USE_VULKAN TRUE)
#SET(USE_D3D9 TRUE)

#
list(APPEND CMAKE_PREFIX_PATH ${EXTERN_LIB_PATH}/glew-2.1.0)
list(APPEND CMAKE_LIBRARY_PATH ${EXTERN_LIB_PATH}/glew-2.1.0/lib/Release/Win32)

#Find libs
find_package(SDL2 REQUIRED)
if(USE_VULKAN)
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIR})
elseif(USE_D3D9)
find_package(D3D9 REQUIRED)
include_directories(${DIRECTX_INCLUDE_DIRS})
else()
find_package(OpenGL REQUIRED)
#We want to link GLEW statically
set(GLEW_USE_STATIC_LIBS ON)
find_package(GLEW REQUIRED)

#Setup project include directories
include_directories(${GLEW_INCLUDE_DIR})
endif()

include_directories(${SDL2_INCLUDE_DIR})

endif()