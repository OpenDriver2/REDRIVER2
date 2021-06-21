-- premake5.lua

require "premake_modules/usage"
require "premake_modules/emscripten"

------------------------------------------

newoption {
   trigger     = "raspberry-pi",
   description = "adds specific define for compiling on Raspberry Pi"
}

table.insert(premake.option.get("os").allowed, { "emscripten", "Emscripten" })

------------------------------------------

-- you can redefine dependencies
SDL2_DIR = os.getenv("SDL2_DIR") or "dependencies/SDL2"
OPENAL_DIR = os.getenv("OPENAL_DIR") or "dependencies/openal-soft"
JPEG_DIR = os.getenv("JPEG_DIR") or "dependencies/jpeg"

WEBDEMO_DIR = os.getenv("WEBDEMO_DIR") or "../../content/web_demo@/"	-- FIXME: make it better
WEBSHELL_PATH = "../.emscripten"

GAME_REGION = os.getenv("GAME_REGION") or "NTSC_VERSION" -- or PAL_VERSION
GAME_VERSION = os.getenv("APPVEYOR_BUILD_VERSION") or nil

if not (GAME_REGION == "NTSC_VERSION" or GAME_REGION == "PAL_VERSION") then
    error("'GAME_REGION' should be 'NTSC_VERSION' or 'PAL_VERSION'")
end

------------------------------------------
	
workspace "REDRIVER2"
    configurations { "Debug", "Release", "Release_dev" }

    defines { VERSION } 
	
	if os.target() == "emscripten" then
		platforms { "emscripten" }
	
		buildoptions { 
			--"-s USE_PTHREADS=1", 
			"-s PTHREAD_POOL_SIZE=8", 
			"-s ABORTING_MALLOC=0", 
			"-s FETCH=1", 
			--"-s PROXY_TO_PTHREAD=1", 
			"-s WASM=1", 
			"-s TOTAL_MEMORY=1073741824",
			"-s USE_SDL=2",
			"-s FULL_ES2=1",
			"-s USE_WEBGL2=1",
			"-s ASYNCIFY=1",
			"-s ALLOW_MEMORY_GROWTH=1",
			"-s GL_TESTING=1",
			"-Wno-c++11-narrowing",
			"-Wno-constant-conversion",
			"-Wno-writable-strings",
			"-Wno-unused-value",
			"-Wno-switch",
			"-Wno-shift-op-parentheses",
			"-Wno-parentheses",
			"-Wno-format",
		}
		linkoptions  { 
			--"-s USE_PTHREADS=1", 
			"-s PTHREAD_POOL_SIZE=8", 
			"-s ABORTING_MALLOC=0", 
			"-s FETCH=1", 
			--"-s PROXY_TO_PTHREAD=1", 
			"-s WASM=1", 
			"-s TOTAL_MEMORY=1073741824",
			"-s USE_SDL=2",
			"-s FULL_ES2=1",
			"-s USE_WEBGL2=1",
			"-s ASYNCIFY=1",
			"-s ALLOW_MEMORY_GROWTH=1",
			"-s GL_TESTING=1",
			("--shell-file " .. WEBSHELL_PATH .. "/shell.html"),
			("--preload-file " .. WEBDEMO_DIR)
		}
		
		filter { "kind:*App" }
			targetextension ".html"
			
		postbuildcommands {
			"{COPY} " .. WEBSHELL_PATH .. "/style.css %{cfg.buildtarget.directory}"
		}

	else
		platforms { "x86" } --, "x86_64" }
	end
	
	startproject "REDRIVER2"
	
	configuration "raspberry-pi"
		defines { "__RPI__" }

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
	include "premake_libjpeg.lua"
end

-- Psy-Cross layer
include "PsyCross/premake5.lua"

-- game iteslf
project "REDRIVER2"
    kind "WindowedApp"

    language "c++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { 
        "Game", 
    }
	
	uses { 
		"PsyCross",
	}

    defines { GAME_REGION }
	
	if GAME_VERSION ~= nil then
		defines{ "GAME_VERSION_N=\""..GAME_VERSION.."\"" }
	end

    files {
        "Game/**.h",
        "Game/**.c"
    }

    filter "system:Windows or linux"
        --dependson { "PsyX" }
        links { "jpeg" }
				
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