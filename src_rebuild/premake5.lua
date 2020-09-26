-- premake5.lua

-- you can redefine dependencies
SDL2_DIR = os.getenv("SDL2_DIR") or "dependencies/SDL2"
GLEW_DIR = os.getenv("GLEW_DIR") or "dependencies/glew"
OPENAL_DIR = os.getenv("OPENAL_DIR") or "dependencies/openal-soft"
JPEG_DIR = os.getenv("JPEG_DIR") or "dependencies/jpeg"

GAME_REGION = os.getenv("GAME_REGION") or "NTSC_VERSION" -- or PAL_VERSION

if not (GAME_REGION == "NTSC_VERSION" or GAME_REGION == "PAL_VERSION") then
    error("'GAME_REGION' should be 'NTSC_VERSION' or 'PAL_VERSION'")
end

workspace "REDRIVER2"
    configurations { "Debug", "Release" }

    defines { VERSION } 
    defines { "USE_32_BIT_ADDR", "PGXP" }

    filter "configurations:Debug"
        defines { 
            "DEBUG", 
        }
        symbols "On"

    filter "configurations:Release"
        defines {
            "NDEBUG",
        }
        
    if _TARGET_OS == "Windows" then
        dofile("premake_libjpeg.lua")
    end

-- EMULATOR layer
project "PSX"
    kind "StaticLib"
    language "C++"
    compileas "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { 
        "EMULATOR"
    }

    defines { GAME_REGION }

    files {
        "EMULATOR/**.h", 
        "EMULATOR/**.H", 
        "EMULATOR/**.c", 
        "EMULATOR/**.C", 
        "EMULATOR/**.cpp",
        "EMULATOR/**.CPP",
    }

    defines { "OGL", "GLEW" }

    filter "system:Windows"
        includedirs { 
            SDL2_DIR.."/include",
            GLEW_DIR.."/include",
            OPENAL_DIR.."/include",
        }
        
        links { 
            "opengl32",
            "glew32", 
            "SDL2", 
            "OpenAL32"
        }
    
        libdirs { 
            SDL2_DIR.."/lib/x86",
            GLEW_DIR.."/lib/Release/Win32",
            OPENAL_DIR.."/libs/Win32",
        }

    filter "system:linux"
        buildoptions {
            "-Wno-narrowing"
        }

        links {
            "GL",
            "GLEW",
            "openal",
            "SDL2",
        }

    filter "configurations:Release"
        optimize "Full"

-- game iteslf
project "REDRIVER2"
    kind "ConsoleApp"
    language "C++"
    compileas "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { 
        "GAME", 
        "EMULATOR"
    }

    defines { GAME_REGION }
    defines { "OGL", "GLEW" }

    files {
        "GAME/**.H",
        "GAME/**.C",
        "utils/**.h",
        "utils/**.cpp",
        "redriver2_psxpc.cpp",
        "DebugOverlay.cpp",
    }

    links { "PSX", "jpeg" }

    filter "system:Windows"
        dependson { "PSX" }
        files { 
            "Windows/resource.h", 
            "Windows/Resource.rc", 
            "Windows/main.ico" 
        }
    
        includedirs { 
            SDL2_DIR.."/include",
            GLEW_DIR.."/include",
            OPENAL_DIR.."/include",
			JPEG_DIR.."/",
        }
    
        linkoptions {
			"/SAFESEH:NO", -- Image Has Safe Exception Handers: No. Because of openal-soft
        }
        
    filter "system:linux"
        buildoptions { "-Wno-narrowing", "-fpermissive" }

        cppdialect "C++11"

        links {
            "GL",
            "GLEW",
            "openal",
            "SDL2",
        }

        linkoptions { "-z muldefs" }

    filter "configurations:Debug"
        defines { 
            "DEBUG_OPTIONS",
            "COLLISION_DEBUG" 
         }

    filter "configurations:Release"
        defines { 
            --"DEBUG_OPTIONS",
            --"COLLISION_DEBUG" 
        }
        optimize "Full"