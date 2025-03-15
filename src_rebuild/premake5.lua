-- premake5.lua

require "premake_modules/usage"
require "premake_modules/emscripten"

IS_ANDROID = (_ACTION == "androidndk")

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

WEBDEMO_DIR = os.getenv("WEBDEMO_DIR") or "../../../../content/web_demo@/"	-- FIXME: make it better
RED2_DIR = os.getenv("RED2_DIR") or "../../data@/"
WEBSHELL_PATH = "../platform/Emscripten"	-- must be relative to makefile path (SADLY)

GAME_REGION = os.getenv("GAME_REGION") or "NTSC_VERSION" -- or PAL_VERSION
GAME_VERSION = os.getenv("APPVEYOR_BUILD_VERSION") or nil

if not (GAME_REGION == "NTSC_VERSION" or GAME_REGION == "PAL_VERSION") then
    error("'GAME_REGION' should be 'NTSC_VERSION' or 'PAL_VERSION'")
end

------------------------------------------
	
workspace "REDRIVER2"
    location "project_%{_ACTION}_%{os.target()}"
    configurations { "Debug", "Release", "Release_dev" }
	
    defines { VERSION } 
	
	if os.target() == "emscripten" then
		platforms { "emscripten" }
	
		buildoptions { 
			"-s TOTAL_MEMORY=1073741824",
			"-s USE_SDL=2",
			"-s FULL_ES2=1",
			--"-s USE_WEBGL2=1",
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
			"-s TOTAL_MEMORY=1073741824",
			"-s USE_SDL=2",
			"-s FULL_ES2=1",
			--"-s USE_WEBGL2=1",
			"-s ASYNCIFY=1",
			"-s ALLOW_MEMORY_GROWTH=1",
			"-s GL_TESTING=1",
			("--shell-file " .. WEBSHELL_PATH .. "/shell.html"),
			("--preload-file " .. WEBDEMO_DIR),
			("--preload-file " .. RED2_DIR),
			"-s 'EXPORTED_RUNTIME_METHODS=[\"ccall\", \"writeArrayToMemory\"]'"
		}
		
		filter { "kind:*App" }
			targetextension ".html"
			
		postbuildcommands {
			"{COPY} " .. WEBSHELL_PATH .. "/style.css %{cfg.buildtarget.directory}",
			"{COPY} " .. WEBSHELL_PATH .. "/lsfs.js %{cfg.buildtarget.directory}"
		}

	elseif IS_ANDROID then		
		system "android"
		shortcommands "On"
		
		platforms {
			"android-arm", "android-arm64"
		}
		
		disablewarnings {
			"c++11-narrowing",
			"constant-conversion",
			"writable-strings",
			"unused-value",
			"switch",
			"shift-op-parentheses",
			"parentheses",
			"format",
		}
		
		buildoptions {
			"-fpermissive",
			"-fexceptions",
			"-pthread",
		}
		
		linkoptions {
			"--no-undefined",
			"-fexceptions",
			"-pthread",
			
			"-mfloat-abi=softfp",	-- force NEON to be used
			"-mfpu=neon"
		}

		filter "platforms:*-x86"
			architecture "x86"

		filter "platforms:*-x64"
			architecture "x64"

		filter "platforms:*-arm"
			architecture "arm"

		filter "platforms:*-arm64"
			architecture "arm64"
	else
		platforms { "x86", "x64" }
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
        
if os.target() == "windows" or os.target() == "emscripten" then
	include "premake_libjpeg.lua"
end

-- font tool
if os.target() ~= "emscripten" then
	include "premake5_font_tool.lua"
end

-- Psy-Cross layer
include "premake5_psycross.lua"



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
	defines { "BUILD_CONFIGURATION_STRING=\"%{cfg.buildcfg}\"" }
	
	if GAME_VERSION ~= nil then
		local resVersion = string.gsub(GAME_VERSION, "%.", ",")
		defines{ "GAME_VERSION_N=\""..GAME_VERSION.."\"" }
		defines{ "GAME_VERSION_RES="..resVersion.."" }
	end

    files {
        "Game/**.h",
        "Game/**.c"
    }

    filter {"system:Windows or linux or platforms:emscripten"}
        --dependson { "PsyX" }
        links { "jpeg" }
				
		files {
			"utils/**.h",
			"utils/**.cpp",
			"utils/**.c",
			"redriver2_psxpc.cpp",
		}
		
	filter "platforms:emscripten"
	    includedirs { 
			OPENAL_DIR.."/include",
			JPEG_DIR.."/",
        }
		files { 
            "platform/Emscripten/*.cpp",
        }

    filter "system:Windows"
		entrypoint "mainCRTStartup"
		
		files { -- TEMP
			"platform/Emscripten/*.h",
			"platform/Emscripten/*.css",
			"platform/Emscripten/*.html", 
        }
		
        files { 
            "platform/Windows/resource.h", 
            "platform/Windows/Resource.rc", 
            "platform/Windows/main.ico" 
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