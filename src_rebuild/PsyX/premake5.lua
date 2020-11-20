
-- Psy-Cross layer
project "Psy-X"
    kind "StaticLib"
    language "C++"
    compileas "C++"
    targetdir "bin/%{cfg.buildcfg}"
	removeplatforms "psx" 

    defines { GAME_REGION }

    files {
        "**.h", 
        "**.H", 
        "**.c", 
        "**.C", 
        "**.cpp",
        "**.CPP",
    }

    defines {  }

    includedirs { 
        SDL2_DIR.."/include",
        OPENAL_DIR.."/include",
		OPENAL_DIR.."/include",
    }

    filter "system:Windows"
		defines { "_WINDOWS" }
        links { 
            "opengl32",
            "SDL2", 
            "OpenAL32"
        }
    
        libdirs { 
            SDL2_DIR.."/lib/x86",
            OPENAL_DIR.."/libs/Win32",
        }

    filter "system:linux"
        buildoptions {
            "-Wno-narrowing",
            "-m32",
        }

        includedirs {
            "/usr/include/SDL2"
        }

        links {
            "GL",
            "openal",
            "SDL2",
        }

        linkoptions {
            "-m32"
        }

    filter "configurations:Release"
        optimize "Full"
		
	filter "configurations:Release_Dev"
        optimize "Full"