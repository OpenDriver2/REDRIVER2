-- if you want to build project with PsyCross - you have to include it to your workspace

-- Psy-Cross layer
project "PsyCross"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    defines { GAME_REGION }

    files {
        "PsyCross/**.h", 
        "PsyCross/**.H", 
        "PsyCross/**.c", 
        "PsyCross/**.C", 
        "PsyCross/**.cpp",
        "PsyCross/**.CPP",
    }

    defines {  }

    includedirs { 
        SDL2_DIR.."/include",
        OPENAL_DIR.."/include",
		"PsyCross/include"
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

	filter {"system:Windows", "platforms:x64"}
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

    filter "system:macosx"
        includedirs {
            MAC_SDL2_DIR.."/include",
            MAC_SDL2_DIR.."/include/SDL2",
            MAC_OPENAL_DIR.."/include",
        }

        libdirs {
            MAC_SDL2_DIR.."/lib",
            MAC_OPENAL_DIR.."/lib",
        }

        links {
            "Cocoa.framework",
            "openal",
            "SDL2",
        }

        if USE_VULKAN_RENDERER then
            local SHADERC_DIR = HOMEBREW_PREFIX .. "/opt/shaderc"
            defines { "RENDERER_VK", "USE_VULKAN", "USE_OPENGL_RENDERER=0" }
            includedirs {
                MAC_VULKAN_HEADERS .. "/include",
                SHADERC_DIR .. "/include",
            }
            libdirs    {
                MAC_VULKAN_LOADER .. "/lib",
                SHADERC_DIR .. "/lib",
            }
            -- libshaderc_combined.a bundles glslang+SPIRV-Tools statically;
            -- gives us GLSL→SPIR-V compilation at runtime without any dylib.
            linkoptions { SHADERC_DIR .. "/lib/libshaderc_combined.a" }
            links {
                "vulkan",
                "Metal.framework",
                "QuartzCore.framework",
                "IOSurface.framework",
            }
            -- Exclude OpenGL backend sources when building Vulkan
            removefiles {
                "PsyCross/src/render/PsyX_render.cpp",
                "PsyCross/src/render/glad.c",
            }
        else
            links { "OpenGL.framework" }
            -- Exclude Vulkan backend sources when building OpenGL
            removefiles {
                "PsyCross/src/render/PsyX_render_vk.cpp",
            }
        end

    filter "configurations:Release"
        optimize "Speed"

	filter "configurations:Release_dev"
        optimize "Speed"

    --filter { "files:**.c", "files:**.C" }
    --    compileas "C++"

usage "PsyCross"
	links "PsyCross"
	includedirs {
		"PsyCross/include",
		"PsyCross/include/psx"
	}