-- premake-androidndk - a multi-ABI, multi-language ndk-build Android.mk generator for Premake.
-- Originally written by Vitaliy <Triang3l> Kuzmin.
-- See README.md for detailed usage and design information.
-- Available under the Unlicense (see UNLICENSE.txt) or the BSD 3-Clause "New" or "Revised" License (see LICENSE.txt).

local p = premake;

p.api.addAllowed("system", p.ANDROID);
-- NEON is enabled by default, like in NDK r21.
-- Similar to how Premake defines "IA32" for x86, use "ARMv7" to disable NEON (and use the .neon suffix where needed).
p.api.addAllowed("vectorextensions", { "ARMv7", "NEON", "SSE4.2" });
if os.systemTags[p.ANDROID] == nil then
	os.systemTags[p.ANDROID] = { "android", "posix", "mobile" };
end

p.api.register({
	name = "armisa",
	scope = "config",
	kind = "string",
	allowed = {
		p.DEFAULT,
		"A32",
		"T32",
	},
});

p.api.register({
	name = "cppstl",
	scope = "config",
	kind = "string",
	allowed = {
		p.DEFAULT,
		-- As of NDK r18, only none, c++ and system are available, with the latter being deprecated.
		-- Supporting the older STLs is trivial, however.
		"c++",
		"gabi++",
		"gnustl",
		"none",
		"stlport",
		"system",
	},
});

p.api.register({
	name = "formatstringchecks",
	scope = "config",
	kind = "boolean",
});

p.api.register({
	name = "renderscriptcompatibility",
	scope = "config",
	kind = "boolean",
});

p.api.register({
	name = "renderscriptincludedirsoverride",
	scope = "config",
	kind = "boolean",
});

p.api.register({
	name = "shortcommands",
	scope = "config",
	kind = "boolean",
});

p.api.register({
	name = "thinarchive",
	scope = "config",
	kind = "boolean",
});

p.api.register({
	name = "undefinedsymbols",
	scope = "config",
	kind = "boolean",
});

-- Whether this static library project should be linked as a whole, even if not specified in `wholelibs` of dependent projects.
p.api.register({
	name = "wholelib",
	scope = "config",
	kind = "boolean",
});

-- Subset of `links` which need to be linked as a whole regardless of their `wholelib` setting.
p.api.register({
	name = "wholelibs",
	scope = "config",
	kind = "list:mixed",
	tokens = true,
});

newaction({
	trigger = "androidndk",
	shortname = "Android ndk-build",
	description = "Generate Android ndk-build makefiles",
	targetos = p.ANDROID,
	valid_kinds = { p.CONSOLEAPP, p.SHAREDLIB, p.STATICLIB },
	valid_languages = { p.C, p.CPP },
	-- Premake workspace and project names can include periods, so using suffixes for both.
	onWorkspace = p.modules.androidndk.onWorkspace,
	onProject = p.modules.androidndk.onProject,
});

-- Decide when the full module should be loaded.
return function(config)
	return _ACTION == "androidndk";
end;
