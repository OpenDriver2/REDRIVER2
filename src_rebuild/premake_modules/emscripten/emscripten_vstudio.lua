--
-- emscripten_vstudio.lua
-- Emscripten integration for vstudio.
-- Copyright (c) 2012-2015 Manu Evans and the Premake project
--

	local p = premake
	local emscripten = p.modules.emscripten

	require "vstudio"

	local sln2005 = p.vstudio.sln2005
	local vc2010 = p.vstudio.vc2010
	local vstudio = p.vstudio
	local project = p.project
	local config = p.config


--
-- Add Emscripten tools to vstudio actions.
--

	if vstudio.vs2010_architectures ~= nil then
		vstudio.vs2010_architectures.emscripten = "Emscripten"
	end

	local function alreadyHas(t, key)
		for _, k in ipairs(t) do
			if string.find(k, key) then
				return true
			end
		end
		return false
	end

--
-- Extend configurationProperties.
--

	premake.override(vc2010, "platformToolset", function(orig, cfg)
		if cfg.system == p.EMSCRIPTEN then
			-- is there a reason to write this? default is fine.
--			_p(2,'<PlatformToolset>emcc</PlatformToolset>')
		else
			orig(cfg)
		end
	end)

	premake.override(vc2010, "configurationType", function(oldfn, cfg)
		if cfg.system == p.EMSCRIPTEN then
			if cfg.kind then
				local types = {
					StaticLib = "StaticLibrary",
					ConsoleApp = "JSApplication",
					WindowedApp = "Application",
					HTMLPage = "Application"
				}
				if not types[cfg.kind] then
					error("Invalid 'kind' for Emscripten: " .. cfg.kind, 2)
				else
					_p(2,'<ConfigurationType>%s</ConfigurationType>', types[cfg.kind])
				end
			end
		else
			oldfn(cfg)
		end
	end)


--
-- Extend outputProperties.
--

	premake.override(vc2010.elements, "outputProperties", function(oldfn, cfg)
		local elements = oldfn(cfg)
		if cfg.system == p.EMSCRIPTEN then
			elements = table.join(elements, {
				emscripten.clangPath,
				emscripten.emccPath
			})
		end
		return elements
	end)

	function emscripten.clangPath(cfg)
		if cfg.clangpath ~= nil then
--			local dirs = project.getrelative(cfg.project, includedirs)
--			dirs = path.translate(table.concat(fatalwarnings, ";"))
			_p(2,'<ClangPath>%s</ClangPath>', cfg.clangpath)
		end
	end

	function emscripten.emccPath(cfg)
		if cfg.emccpath ~= nil then
--			local dirs = project.getrelative(cfg.project, includedirs)
--			dirs = path.translate(table.concat(fatalwarnings, ";"))
			_p(2,'<EmccPath>%s</EmccPath>', cfg.emccpath)
		end
	end


--
-- Extend clCompile.
--

	premake.override(vc2010.elements, "clCompile", function(oldfn, cfg)
		local elements = oldfn(cfg)
		if cfg.system == p.EMSCRIPTEN then
			elements = table.join(elements, {
				emscripten.debugInformation,
				emscripten.enableWarnings,
				emscripten.languageStandard,
			})
		end
		return elements
	end)

	function emscripten.debugInformation(cfg)
		-- TODO: support these
		--     NoDebugInfo
		--     LimitedDebugInfo
		--     FullDebugInfo
		if cfg.flags.Symbols then
			_p(3,'<GenerateDebugInformation>FullDebugInfo</GenerateDebugInformation>')
		end
	end

	function emscripten.enableWarnings(cfg)
		if #cfg.enablewarnings > 0 then
			_x(3,'<EnableWarnings>%s</EnableWarnings>', table.concat(cfg.enablewarnings, ";"))
		end
	end

	function emscripten.languageStandard(cfg)
		local map = {
			c90         = "LanguageStandardC89",
			gnu90       = "LanguageStandardGnu89",
			c94         = "LanguageStandardC94",
			c99         = "LanguageStandardC99",
			gnu99       = "LanguageStandardGnu99",
			["c++98"]   = "LanguageStandardCxx03",
			["gnu++98"] = "LanguageStandardGnu++98",
			["c++11"]   = "LanguageStandardC++11",
			["gnu++11"] = "LanguageStandardGnu++11"
		}
		if cfg.languagestandard and map[cfg.languagestandard] then
			_p(3,'<LanguageStandardMode>%s</LanguageStandardMode>', map[cfg.languagestandard])
		end
	end

	premake.override(vc2010, "disableSpecificWarnings", function(oldfn, cfg)
		if cfg.system == p.EMSCRIPTEN then
			if #cfg.disablewarnings > 0 then
				local warnings = table.concat(cfg.disablewarnings, ";")
				warnings = premake.esc(warnings) .. ";%%(DisableWarnings)"
				vc2010.element('DisableWarnings', condition, warnings)
			end
		else
			oldfn(cfg)
		end
	end)

	premake.override(vc2010, "treatSpecificWarningsAsErrors", function(oldfn, cfg)
		if cfg.system == p.EMSCRIPTEN then
			if #cfg.fatalwarnings > 0 then
				local fatal = table.concat(cfg.fatalwarnings, ";")
				fatal = premake.esc(fatal) .. ";%%(SpecificWarningsAsErrors)"
				vc2010.element('SpecificWarningsAsErrors', condition, fatal)
			end
		else
			oldfn(cfg)
		end
	end)

	premake.override(vc2010, "undefinePreprocessorDefinitions", function(oldfn, cfg, undefines, escapeQuotes, condition)
		if cfg.system == p.EMSCRIPTEN then
			if #undefines > 0 then
				undefines = table.concat(undefines, ";")
				if escapeQuotes then
					undefines = undefines:gsub('"', '\\"')
				end
				undefines = premake.esc(undefines) .. ";%%(PreprocessorUndefinitions)"
				vc2010.element('PreprocessorUndefinitions', condition, undefines)
			end
		else
			oldfn(cfg, undefines, escapeQuotes, condition)
		end
	end)

	premake.override(vc2010, "exceptionHandling", function(oldfn, cfg)
		-- ignored for Emscripten
		if cfg.system ~= p.EMSCRIPTEN then
			oldfn(cfg)
		end
	end)

	premake.override(vc2010, "additionalCompileOptions", function(oldfn, cfg, condition)
		if cfg.system == p.EMSCRIPTEN then
			emscripten.additionalCompileOptions(cfg, condition)
		end
		return oldfn(cfg, condition)
	end)

	function emscripten.additionalCompileOptions(cfg, condition)

		if cfg.flags["C++11"] then
			table.insert(cfg.buildoptions, "-std=c++11")
		end

	end

	-- these should be silenced for Emscripten
	premake.override(vc2010, "precompiledHeader", function(oldfn, cfg, filecfg, condition)
		if cfg.system ~= p.EMSCRIPTEN then
			oldfn(cfg, filecfg, condition)
		end
	end)
	premake.override(vc2010, "floatingPointModel", function(oldfn, cfg)
		if cfg.system ~= p.EMSCRIPTEN then
			oldfn(cfg)
		end
	end)


--
-- Extend Link.
--

	premake.override(vc2010.elements, "link", function(oldfn, cfg, explicit)
		local elements = oldfn(cfg, explicit)
		if cfg.kind ~= p.STATICLIB and cfg.system == p.EMSCRIPTEN then
			elements = table.join(elements, {
				emscripten.linkerOptimizationLevel,
				emscripten.typedArrays,
				emscripten.closureCompiler,
				emscripten.minify,
				emscripten.ignoreDynamicLinking,
				emscripten.preJsFile,
				emscripten.postJsFile,
				emscripten.embedFile,
				emscripten.preloadFile,
				emscripten.htmlShellFile,
				emscripten.jsLibrary,
			})
		end
		return elements
	end)

	function emscripten.linkerOptimizationLevel(cfg)
		local map = {
			["Off"] = "O0",
			["Simple"] = "O1",
			["On"] = "O2",
			["Unsafe"] = "O3",
		}
		if cfg.linkeroptimize and map[cfg.linkeroptimize] then
			_p(3, '<LinkerOptimizationLevel>%s</LinkerOptimizationLevel>', map[cfg.linkeroptimize])
		end
	end

	function emscripten.typedArrays(cfg)
		local map = {
			["None"] = "NoTypedArrays",
			["Parallel"] = "ParallelTypedArrays",
			["Shared"] = "SharedTypedArrays",
		}
		if cfg.typedarrays and map[cfg.typedarrays] then
			_p(3, '<TypedArrays>%s</TypedArrays>', map[cfg.typedarrays])
		end
	end

	function emscripten.closureCompiler(cfg)
		if cfg.flags.NoClosureCompiler then
			_p(3, '<RunClosureCompiler>false</RunClosureCompiler>')
		end
	end

	function emscripten.minify(cfg)
		if cfg.flags.NoMinifyJavaScript then
			_p(3, '<RunMinify>false</RunMinify>')
		end
	end

	function emscripten.ignoreDynamicLinking(cfg)
		if cfg.flags.IgnoreDynamicLinking then
			_p(3, '<IgnoreDynamicLinking>true</IgnoreDynamicLinking>')
		end
	end

	function emscripten.preJsFile(cfg)
		if #cfg.jsprepend > 0 then
			local files = project.getrelative(cfg.project, cfg.jsprepend)
			_x(3, '<PreJsFile>%s;%%(PreJsFile)</PreJsFile>', table.concat(files, ";"))
		end
	end

	function emscripten.postJsFile(cfg)
		if #cfg.jsappend > 0 then
			local files = project.getrelative(cfg.project, cfg.jsappend)
			_x(3, '<PostJsFile>%s;%%(PostJsFile)</PostJsFile>', table.concat(files, ";"))
		end
	end

	function emscripten.embedFile(cfg)
--		_x(3, '<EmbedFile>embedRes;embed2;%(EmbedFile)</EmbedFile>', )
	end

	function emscripten.preloadFile(cfg)
--		_x(3, '<PreloadFile>preloadRes;preload2;%(PreloadFile)</PreloadFile>', )
	end

	function emscripten.htmlShellFile(cfg)
--		_x(3, '<HtmlShellFile>htmlShell;html2;%(HtmlShellFile)</HtmlShellFile>', )
	end

	function emscripten.jsLibrary(cfg)
--		_x(3, '<JsLibrary>jsLib;jsLib2;%(JsLibrary)</JsLibrary>', )
	end

	premake.override(vc2010, "additionalLinkOptions", function(oldfn, cfg)
		if cfg.system == p.EMSCRIPTEN then
			emscripten.additionalLinkOptions(cfg) -- TODO: should this be moved to bake or something?
		end
		return oldfn(cfg)
	end)

	-- these should be silenced for Emscripten
	premake.override(vc2010, "generateDebugInformation", function(oldfn, cfg)
		-- Note: Emscripten specifies the debug info in the clCompile section
		if cfg.system ~= p.EMSCRIPTEN then
			oldfn(cfg)
		end
	end)
	premake.override(vc2010, "subSystem", function(oldfn, cfg)
		if cfg.system ~= p.EMSCRIPTEN then
			oldfn(cfg)
		end
	end)
	premake.override(vc2010, "optimizeReferences", function(oldfn, cfg)
		if cfg.system ~= p.EMSCRIPTEN then
			oldfn(cfg)
		end
	end)
	premake.override(vc2010, "entryPointSymbol", function(oldfn, cfg)
		if cfg.system ~= p.EMSCRIPTEN then
			oldfn(cfg)
		end
	end)


--
-- Add options unsupported by Emscripten vs-tool UI to <AdvancedOptions>.
--
	function emscripten.additionalLinkOptions(cfg)

		if #cfg.exportedfunctions > 0 then
			local functions = table.implode(cfg.exportedfunctions, "'", "'", ", ")
			table.insert(cfg.linkoptions, "-s EXPORTED_FUNCTIONS=\"[" .. functions .. "]\"")
		end
		if cfg.flags.NoExitRuntime then
			table.insert(cfg.linkoptions, "-s NO_EXIT_RUNTIME=1")
		end
		if cfg.flags.NoMemoryInitFile then
			table.insert(cfg.linkoptions, "--memory-init-file 0")
		end

	end
