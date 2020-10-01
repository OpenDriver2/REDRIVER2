-- premake5.lua

require "premake_modules/psx"

-- you can redefine dependencies
SDL2_DIR = os.getenv("SDL2_DIR") or "dependencies/SDL2"
GLEW_DIR = os.getenv("GLEW_DIR") or "dependencies/glew"
OPENAL_DIR = os.getenv("OPENAL_DIR") or "dependencies/openal-soft"
JPEG_DIR = os.getenv("JPEG_DIR") or "dependencies/jpeg"

PSYQ_DIR = os.getenv("PSYQ_DIR") or "PSY-Q"

GAME_REGION = os.getenv("GAME_REGION") or "NTSC_VERSION" -- or PAL_VERSION

if not (GAME_REGION == "NTSC_VERSION" or GAME_REGION == "PAL_VERSION") then
    error("'GAME_REGION' should be 'NTSC_VERSION' or 'PAL_VERSION'")
end
	
workspace "REDRIVER2"
    configurations { "Debug", "Release", "Release Dev" }

    defines { VERSION } 

    filter "system:Windows or linux"
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
        
	if os.target() == "windows" then
		dofile("premake_libjpeg.lua")
	end
	
	if os.target() ~= "psx" then
		dofile("premake_emulator.lua")
	end
	
-- TODO: overlays

-- game iteslf
project "REDRIVER2"
    kind "ConsoleApp"
    language "C++"
    compileas "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { 
        "GAME", 
    }

    defines { GAME_REGION }

    files {
        "GAME/**.H",
        "GAME/**.C",
    }
	
	-- exclude sources which belong to overlays
	if os.target() == "psx" then
		excludes {
			"GAME/MEMCARD/**.C",
			"GAME/MEMCARD/**.H",
			"GAME/FRONTEND/**.C",
			"GAME/FRONTEND/**.H",
			"GAME/C/LEADAI.C",
			"GAME/C/PATHFIND.C",
		}
	end

    filter "system:Windows or linux"
        defines { "OGL", "GLEW", "SIMPLE_SPOOL" }
        dependson { "PSX" }
        links { "PSX", "jpeg" }
		
		includedirs { 
			"EMULATOR"
		}
		
		files {
			"utils/**.h",
			"utils/**.cpp",
			"redriver2_psxpc.cpp",
			"DebugOverlay.cpp",
		}

    filter "system:Windows"
		
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

        includedirs {
            "/usr/include/SDL2"
        }

        links {
            "GL",
            "GLEW",
            "openal",
            "SDL2",
        }

        linkoptions { "-z muldefs" }
		
	filter "system:psx"
		defines { "PSX" }
		includedirs {
            PSYQ_DIR.."/include"
        }
		links {
			PSYQ_DIR.."/LIBETC",
			PSYQ_DIR.."/LIBPAD",
			PSYQ_DIR.."/LIBGTE",
			PSYQ_DIR.."/LIBMCRD",
			PSYQ_DIR.."/LIBCD",
			PSYQ_DIR.."/LIBSN",
			PSYQ_DIR.."/LIBSPU",
			PSYQ_DIR.."/LIBAPI"
        }

    filter "configurations:Debug"
        defines { 
            "DEBUG_OPTIONS",
            "COLLISION_DEBUG" 
         }
		 symbols "On"

    filter "configurations:Release"
        optimize "Full"
		
	filter "configurations:Release Dev"
        defines { 
            "DEBUG_OPTIONS",
            "COLLISION_DEBUG" 
        }
        optimize "Full"