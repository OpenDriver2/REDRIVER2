-- Font generator tool
project "FontTool"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files {
        "tools/font_tool/**.h", 
        "tools/font_tool/**.H", 
        "tools/font_tool/**.c", 
        "tools/font_tool/**.C", 
        "tools/font_tool/**.cpp",
        "tools/font_tool/**.CPP",
        "utils/stb_truetype.*", 
        "utils/targa.*",
    }

    defines {  }

    includedirs { 
		"utils",
        "PsyCross/include/psx"
    }

    filter "system:Windows"
	    defines { "_WINDOWS" }

    filter "configurations:Release"
        optimize "Speed"

	filter "configurations:Release_dev"
        optimize "Speed"

