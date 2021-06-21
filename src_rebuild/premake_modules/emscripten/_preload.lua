--
-- Name:        emscripten/_preload.lua
-- Purpose:     Define the Emscripten API's.
-- Author:      Manu Evans
-- Copyright:   (c) 2013-2015 Manu Evans and the Premake project
--

	local p = premake
	local api = p.api

	premake.tools.emcc = {}

--
-- Register the Emscripten extension
--

	p.EMSCRIPTEN = "emscripten"
	p.EMCC = "emcc"

	api.addAllowed("system", { p.EMSCRIPTEN })
	api.addAllowed("kind", "HTMLPage")
	api.addAllowed("flags", {
		"NoClosureCompiler",
		"NoMinifyJavaScript",
		"NoMemoryInitFile",
		"NoExitRuntime",
		"IgnoreDynamicLinking",
	})


--
-- Register Emscripten properties
--

	api.register {
		name = "emccpath",
		scope = "config",
		kind = "path",
		tokens = true,
	}

	api.register {
		name = "linkeroptimize",
		scope = "config",
		kind = "string",
		allowed = {
			"Off",
			"Simple",
			"On",
			"Unsafe",
		}
	}

	api.register {
		name = "typedarrays",
		scope = "config",
		kind = "string",
		allowed = {
			"None",
			"Parallel",
			"Shared",
		}
	}

	api.register {
		name = "jsprepend",
		scope = "config",
		kind = "list:path",
		tokens = true,
	}

	api.register {
		name = "jsappend",
		scope = "config",
		kind = "list:path",
		tokens = true,
	}

	api.register {
		name = "exportedfunctions",
		scope = "config",
		kind = "list:string",
		tokens = true,
	}

--      <EmbedFile>embedRes;embed2;%(EmbedFile)</EmbedFile>
--      <PreloadFile>preloadRes;preload2;%(PreloadFile)</PreloadFile>
--      <HtmlShellFile>htmlShell;html2;%(HtmlShellFile)</HtmlShellFile>
--      <JsLibrary>jsLib;jsLib2;%(JsLibrary)</JsLibrary>



	filter { "platforms:Emscripten" }
		system "emscripten"
		toolset "emcc"

	filter {}

--
-- Decide when the full module should be loaded.
--

	return function(cfg)
		return cfg.system == "emscripten" or cfg.toolset == "emcc"
	end
