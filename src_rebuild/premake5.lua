-- premake5.lua

require "premake_modules/psx"

-- you can redefine dependencies
SDL2_DIR = os.getenv("SDL2_DIR") or "dependencies/SDL2"
OPENAL_DIR = os.getenv("OPENAL_DIR") or "dependencies/openal-soft"
JPEG_DIR = os.getenv("JPEG_DIR") or "dependencies/jpeg"

PSYQ_DIR = os.getenv("PSYQ_DIR") or "PSY-Q"

GAME_REGION = os.getenv("GAME_REGION") or "NTSC_VERSION" -- or PAL_VERSION

if not (GAME_REGION == "NTSC_VERSION" or GAME_REGION == "PAL_VERSION") then
    error("'GAME_REGION' should be 'NTSC_VERSION' or 'PAL_VERSION'")
end
	
workspace "REDRIVER2"
    configurations { "Debug", "Release", "Release_dev" }
	platforms { "x86" } --, "x86_64" }

    defines { VERSION } 

	filter "system:Linux"
		buildoptions {
            "-Wno-narrowing",
			"-Wno-endif-labels",
			"-Wno-write-strings",
			"-Wno-format-security",
			"-Wno-unused-result",
            "-fpermissive"
        }
		
		cppdialect "C++11"
		
	filter {"system:Linux", "platforms:x86"}
		buildoptions {
			"-m32"
		}
		
		linkoptions {
			"-m32"
		}

	filter "system:Windows"
		disablewarnings { "4996", "4554", "4244", "4101", "4838", "4309" }

    filter "configurations:Debug"
        defines { 
            "_DEBUG", 
	        "DEBUG"
        }
        symbols "On"

    filter "configurations:Release"
        defines {
            "NDEBUG",
        }
		
	filter "configurations:Release_dev"
        defines {
            "NDEBUG",
        }
        
	if os.target() == "windows" then
		dofile("premake_libjpeg.lua")
	end
	
	if os.target() ~= "psx" then
		dofile("PsyX/premake5.lua")
	end
	
-- TODO: overlays

-- game iteslf
project "REDRIVER2"
    kind "WindowedApp"

    language "c++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { 
        "Game", 
    }

    defines { GAME_REGION }

    files {
        "Game/**.h",
        "Game/**.c"
    }
	
	-- exclude sources which belong to overlays
	if os.target() == "psx" then
		excludes {
			"Game/MemCard/**.c",
			"Game/MemCard/**.h",
			"Game/Frontend/**.c",
			"Game/Frontend/**.h",
			"Game/C/leadai.c",
			"Game/C/pathfind.c",
		}
    end

    filter "system:Windows or linux"
        defines { "SIMPLE_SPOOL" }
        dependson { "PsyX" }
        links { "Psy-X", "jpeg" }
		
		includedirs { 
			"PsyX/include"
		}
		
		files {
			"utils/**.h",
			"utils/**.cpp",
			"utils/**.c",
			"redriver2_psxpc.cpp",
			"DebugOverlay.cpp",
		}

    filter "system:Windows"
		entrypoint "mainCRTStartup"
		
        files { 
            "Windows/resource.h", 
            "Windows/Resource.rc", 
            "Windows/main.ico" 
        }

        includedirs { 
            SDL2_DIR.."/include",
            OPENAL_DIR.."/include",
			JPEG_DIR.."/",
        }
    
        linkoptions {
			"/SAFESEH:NO", -- Image Has Safe Exception Handers: No. Because of openal-soft
        }
        
    filter "system:linux"
        includedirs {
            "/usr/include/SDL2"
        }

        links {
            "GL",
            "openal",
            "SDL2",
            "dl",
        }
		
	filter "system:psx"
		defines { "PSX" }
		includedirs {
            PSYQ_DIR.."/include"
        }
		links {
			PSYQ_DIR.."/lib/LIBETC",
			PSYQ_DIR.."/lib/LIBPAD",
			PSYQ_DIR.."/lib/LIBGTE",
			PSYQ_DIR.."/lib/LIBMCRD",
			PSYQ_DIR.."/lib/LIBCD",
			PSYQ_DIR.."/lib/LIBSN",
			PSYQ_DIR.."/lib/LIBSPU",
			PSYQ_DIR.."/lib/LIBAPI"
        }

    filter "configurations:Debug"
		targetsuffix "_dbg"
        defines { 
            "DEBUG_OPTIONS",
            "COLLISION_DEBUG",
			"CUTSCENE_RECORDER"
         }
		 symbols "On"

    filter "configurations:Release"
        optimize "Speed"
		
	filter "configurations:Release_dev"
		targetsuffix "_dev"
        defines { 
            "DEBUG_OPTIONS",
            "COLLISION_DEBUG",
			"CUTSCENE_RECORDER"
        }
        optimize "Speed"

    filter { "files:**.c", "files:**.C" }
        compileas "C++"