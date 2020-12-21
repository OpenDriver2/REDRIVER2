
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
        OPENAL_DIR.."/include"
    }

    filter "system:Windows"
	defines { "_WINDOWS" }
        links { 
            "opengl32",
            "SDL2", 
            "OpenAL32"
        }
		
	filter {"system:Windows", "platforms:x86"}
		libdirs { 
			SDL2_DIR.."/lib/x86",
			OPENAL_DIR.."/libs/Win32",
		}
		
	filter {"system:Windows", "platforms:x86_64"}
		libdirs { 
			SDL2_DIR.."/lib/x64",
			OPENAL_DIR.."/libs/Win64",
		}

    filter "system:linux"
        includedirs {
            "/usr/include/SDL2"
        }

        links {
            "GL",
            "openal",
            "SDL2",
        }

    filter {"configurations:Release", "configurations:Release_dev"}
        optimize "Speed"
