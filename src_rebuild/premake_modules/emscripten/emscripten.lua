
--
-- Create an emscripten namespace to isolate the additions
--

	local p = premake

	p.modules.emscripten = {}

	local m = p.modules.emscripten
	m._VERSION = "0.0.1"

	include ( "_preload.lua" )

	if os.locate("premake-vstool/vstool.lua") or os.locate("vstool/vstool.lua") then
		require "vstool"
	end


	include("emscripten_emcc.lua")


	if premake.modules.vstool ~= nil then
		premake.override(premake.modules.vstool, "isclang", function(oldfn, cfg)
			return cfg.toolset == "emcc" or oldfn(cfg)
		end)

		premake.override(premake.modules.vstool, "isvstool", function(oldfn, cfg)
			return not (cfg.system == "emscripten" or cfg.toolset == "emcc") and oldfn(cfg)
		end)
	end

	include("emscripten_vstudio.lua")

	return m
