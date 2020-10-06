
-- EMULATOR layer
project "PSX"
    kind "StaticLib"
    language "C++"
    compileas "C++"
    targetdir "bin/%{cfg.buildcfg}"
	removeplatforms "psx" 

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

    includedirs { 
        SDL2_DIR.."/include",
        GLEW_DIR.."/include",
        OPENAL_DIR.."/include",
    }

    filter "system:Windows"
		defines { "_WINDOWS" }
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

        includedirs {
            "/usr/include/SDL2"
        }

        links {
            "GL",
            "GLEW",
            "openal", -- FIXME: is linux using openal-soft?
            "SDL2",
        }

    filter "configurations:Release"
        optimize "Full"