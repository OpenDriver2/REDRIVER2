-- premake5.lua

workspace "REDRIVER2"
    configurations { "Debug", "Release" }

    defines { "NTSC_VERSION" } -- or PAL_VERSION

    filter "system:Windows"
        defines { "USE_32_BIT_ADDR", "PGXP" }

-- EMULATOR layer
project "PSX"
    kind "StaticLib"
    language "C++"
    compileas "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { 
        ".", 
        "EMULATOR"
    }

    files { 
        "EMULATOR/**.h", 
        "EMULATOR/**.c", 
        "EMULATOR/**.cpp",
    }

    defines { "OGL", "GLEW" }

    includedirs { 
        "dependencies/SDL2/include",
        "dependencies/glew/include",
        "dependencies/openal-soft/include",
    }

    filter "system:Windows"
        links { 
            "opengl32",
            "glew32", 
            "SDL2", 
            "OpenAL32"
        }
    
        libdirs { 
            "dependencies/SDL2/lib/x86",
            "dependencies/glew/lib/Release/Win32",
            "dependencies/openal-soft/libs/Win32",
        }

-- game iteslf
project "REDRIVER2"
    kind "ConsoleApp"
    language "C++"
    compileas "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { 
        ".", 
        "EMULATOR"
    }

    files { 
        "GAME/**.h", 
        "GAME/**.c", 
        "redriver2_psxpc.c",
        "DebugOverlay.cpp",
        --"THISDUST.C",
        "THISDUST.H",
    }

    filter "system:Windows"
        dependson { "PSX" }
        files { 
            "Windows/resource.h", 
            "Windows/Resource.rc", 
            "Windows/main.ico" 
        }

        defines { "OGL", "GLEW" }
    
        includedirs { 
            "dependencies/SDL2/include",
            "dependencies/glew/include",
            "dependencies/openal-soft/include",
        }

        links { "PSX" } -- only need to link emulator
    
        linkoptions {
			"/SAFESEH:NO", -- Image Has Safe Exception Handers: No. Because of openal-soft
		}

    filter "configurations:Debug"
        defines { 
            "DEBUG", 
            "DEBUG_OPTIONS",
            "COLLISION_DEBUG" 
         }
        symbols "On"

    filter "configurations:Release"
        defines { 
            "NDEBUG", 
            "DEBUG_OPTIONS",
            --"COLLISION_DEBUG" 
        }
        optimize "On"