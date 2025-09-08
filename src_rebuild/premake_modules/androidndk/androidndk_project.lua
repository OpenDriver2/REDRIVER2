-- premake-androidndk - a multi-ABI, multi-language ndk-build Android.mk generator for Premake.
-- Originally written by Vitaliy <Triang3l> Kuzmin.
-- See README.md for detailed usage and design information.
-- Available under the Unlicense (see UNLICENSE.txt) or the BSD 3-Clause "New" or "Revised" License (see LICENSE.txt).

local p = premake;
local androidndk = p.modules.androidndk;

androidndk.kindScripts = {
	[p.CONSOLEAPP] = "BUILD_EXECUTABLE",
	[p.SHAREDLIB] = "BUILD_SHARED_LIBRARY",
	[p.STATICLIB] = "BUILD_STATIC_LIBRARY",
};

androidndk.prebuiltKinds = {
	[p.SHAREDLIB] = {
		extension = ".so",
		script = "PREBUILT_SHARED_LIBRARY",
	},
	[p.STATICLIB] = {
		extension = ".a",
		script = "PREBUILT_STATIC_LIBRARY",
	},
};

function androidndk.isProjectSupported(project, reportWarnings)
	-- Not allowing references or escaped $ in project names as they complicate path building as well as including project Android.mk files.
	-- Premake treats any path beginning with $ as absolute.
	-- LOCAL_MODULE and LOCAL_STATIC_LIBRARIES sweeping result:
	-- Allowed directly on Linux: !+,-./@[]^_{}~
	-- Allowed if \-escaped on Linux: "`
	-- Allowed if \-escaped on Linux, misleadingly displayed with \ in the terminal: &'()*<>?
	-- Allowed if \\-escaped on Linux: \
	-- Disallowed: whitespaces, #$%:;=|
	-- Stricter than LOCAL_MODULE_FILENAME derived from it by default for : and = (no action required).
	-- However, more relaxed for / - to avoid issues, disallowing / too.
	if string.find(project.name, "%$") ~= nil or androidndk.staticallyHasPatternPostEsc(p.esc(project.name), "[%s#%$%%/:;=|]") then
		if reportWarnings then
			p.warn(
				"Skipping workspace '%s' project '%s' with name containing GNU make references, " ..
				"whitespaces or characters disallowed in an ndk-build module name #$%%/:;=|",
				project.workspace.name, project.name);
		end
		return false;
	end
	return true;
end

function androidndk.getConfigCondition(buildcfg, platform, abi)
	-- All requirements must be met by what is provided by ndk-build and the user for a configuration to be selected.
	-- This is done by removing (filtering out) the current state from the set of the requirements.
	-- If the resulting set is empty, the current state matches all the requirements.

	-- It's important that either all requirements are checked at once (like here), or the ABI check is the outermost ifeq.
	-- PREMAKE_ANDROIDNDK_CONFIGURATIONS and _PLATFORMS include _all_ needed configurations and are the same throughout the ndk-build execution.
	-- With nested buildcfg > platform > ABI conditionals, all ABIs would be entering the same buildcfg, and then the same platform within it.
	-- However, the ABI is the primary criteria for selecting the platform (and the buildcfg if it depends on it).
	-- The ABI should be narrowing down the selection either to one config, or to skipping the module.
	-- The result for multiple configurations for one ABI is undefined.

	local state = {};
	local requirements = {};

	-- Configs in projects are usually sorted by ABI (so ABI-agnostic fallbacks can be provided), then (by Premake) buildcfg, then platform.
	-- So, using this order as well for better readability of generated makefiles.

	-- ABI filtering is done only when the ABI specified.
	if abi ~= nil then
		if abi ~= androidndk.ABI_ALL then
			table.insert(state, "ABI=$(TARGET_ARCH_ABI)");
			table.insert(requirements, "ABI=" .. abi);
		end
	end

	-- At least one build configuration is required by Premake.
	table.insert(state, "$(PREMAKE_ANDROIDNDK_CONFIGURATIONS_PREFIXED)");
	table.insert(requirements, "CONFIGURATION=" .. p.esc(buildcfg));

	-- Platforms may be unspecified, in this case, configurations will have a nil platform.
	if platform ~= nil then
		table.insert(state, "$(PREMAKE_ANDROIDNDK_PLATFORMS_PREFIXED)");
		table.insert(requirements, "PLATFORM=" .. p.esc(platform));
	end

	return "ifeq ($(filter-out " .. table.concat(state, " ") .. "," .. table.concat(requirements, " ") .. "),)";
end

function androidndk.configUsesA32(config)
	-- LOCAL_ARM_MODE and the .arm suffix have no effect on ABIs where they're not relevant - no need to check the ABI.
	-- NDK uses T32 by default, and always switches to A32 for debug builds, but it's handled implicitly in it.
	return config.armisa == "A32";
end

function androidndk.configUsesNeon(config)
	-- LOCAL_ARM_NEON and the .neon suffix have no effect on ABIs where they're not relevant - no need to check the ABI.
	-- On NDK r21, NEON is enabled by default.
	-- Requiring setting vectorextensions to "ARMv7" (similar to "IA32") explicitly for disabling.
	return config.vectorextensions ~= "ARMv7";
end

function androidndk.shellEscapePreQuotesPostEsc(argument, temporaryVariables)
	if androidndk.hasNonEmptyMakeReferencesPostEsc(argument) then
		-- Escape while building, after expanding variable and function references.
		-- Can't use the text directly in a function call because it may contain brackets.
		return "$(call " .. androidndk.shellEscapePreQuotesMakeCall .. "," .. androidndk.getTemporaryVariableReference(temporaryVariables, argument) .. ")";
	end
	-- Unescape comment characters, which have \ in their escape sequence.
	argument = string.gsub(argument, androidndk.commentUnescapePattern, "#");
	-- Pre-escape.
	argument = string.gsub(string.gsub(argument, "\\", "\\\\"), "\"", "\\\"");
	-- Re-escape comment characters.
	argument = string.gsub(argument, "#", androidndk.commentEscapeString);
	return argument;
end

-- For calling with unescaped paths, otherwise paths starting with # will be considered absolute due to $()\# escaping.
-- In addition, may need to escape characters inserted by path.getrelative itself.
-- Unfortunately, if path.getrelative inserts any $ by itself while joining, they will be treated as references.
-- They wouldn't be able to be distinguished from references specified in the project itself.
function androidndk.getEscapedProjectRelativePath(project, file, joinWithLocalPath)
	-- Must be synchronized with LOCAL_PATH setting.
	-- Based on p.filename logic (relative to the location of the project's Android.mk).
	-- If a path starts with a GNU make variable or function reference, it's assumed to be absolute, to allow using paths like $(NDK_ROOT).
	-- Premake already treats paths starting with $ as absolute in path.getrelative, among other functions.
	-- Relative paths starting with $ must be prefixed with ./.
	local relativePath = path.getrelative(project.location or project.basedir, file);
	-- For something like ./$(VARIABLE) (relative), path.getrelative can possibly return $(VARIABLE), which will be treated as absolute.
	-- Premake treats all paths beginning with $ as absolute.
	-- In this case, the path must still be written as relative to $(LOCAL_PATH), but path.join won't work.
	-- path.join doesn't even work if the trailing part begins with ./$(VARIABLE).
	-- Using concatenation for this purpose instead.
	if joinWithLocalPath and (not path.isabsolute(relativePath) or (string.sub(relativePath, 1, 1) == "$" and string.sub(file, 1, 1) ~= "$")) then
		relativePath = "$(LOCAL_PATH)/" .. relativePath;
	end
	return p.esc(relativePath);
end

-- Excluding the .arm and .neon suffixes.
androidndk.asmExtension = ".asm";
androidndk.cExtension = ".c";
androidndk.sourceExtensions = { androidndk.asmExtension, androidndk.cExtension };
androidndk.compilerFlagsVariables = {
	[androidndk.asmExtension] = "ASMFLAGS",
	[androidndk.cExtension] = "CONLYFLAGS",
};
-- NDK r23 default-c++-extensions.
-- Strictly broader than path.iscppfile as of premake-core v5.0.0-alpha16.
-- path.iscppfile is not usable directly conveniently, however, as it also includes assembly and Objective-C/C++.
-- Do not use path.hasextension (or path.iscppfile) as it's case-insensitive unlike ndk-build, and will treat .C as C instead of C++.
-- Indexed for concatenation purposes.
androidndk.cppExtensions = { ".cc", ".cp", ".cxx", ".cpp", ".CPP", ".c++", ".C" };
table.foreachi(androidndk.cppExtensions, function(extension)
	-- Build a hash set for lookup in cppExtensions.
	androidndk.cppExtensions[extension] = extension;
	-- Register the extension as a C++ one.
	table.insert(androidndk.sourceExtensions, extension);
	androidndk.compilerFlagsVariables[extension] = "CPPFLAGS";
end);
-- NDK r23 default-rs-extensions.
androidndk.rsExtensions = { ".rs", ".fs" };
table.foreachi(androidndk.rsExtensions, function(extension)
	-- Build a hash set for lookup in rsExtensions.
	androidndk.rsExtensions[extension] = extension;
	-- Register the extension as a RenderScript one.
	table.insert(androidndk.sourceExtensions, extension);
	androidndk.compilerFlagsVariables[extension] = "RENDERSCRIPT_FLAGS";
end);
androidndk.asExtensions = { ".s", ".S" };
table.foreachi(androidndk.asExtensions, function(extension)
	-- Build a hash set for lookup in asExtensions.
	androidndk.asExtensions[extension] = extension;
	-- Register the extension as a GAS one.
	table.insert(androidndk.sourceExtensions, extension);
	androidndk.compilerFlagsVariables[extension] = "ASFLAGS";
end);
-- Build a hash set for lookup in sourceExtensions.
table.foreachi(androidndk.sourceExtensions, function(extension)
	androidndk.sourceExtensions[extension] = extension;
end);

-- Define variables usable by projects for language filtering via extension filters.
-- Lowercase because it's the public interface for projects.
androidndk.filefilters = {};
function androidndk.buildExtensionFileFilterTerms(extensions)
	local extensionsCaseInsensitive = {};
	-- Premake filters are case-insensitive - don't add the same extension twice.
	for i, extension in ipairs(extensions) do
		table.insertkeyed(extensionsCaseInsensitive, string.lower(extension));
	end
	-- Build filters including subdirectories, adding all possible ARM suffixes.
	local extensionFilters = {};
	for i, extension in ipairs(extensionsCaseInsensitive) do
		local extensionFilter = "**" .. extension;
		table.insert(extensionFilters, extensionFilter);
		table.insert(extensionFilters, extensionFilter .. ".arm");
		table.insert(extensionFilters, extensionFilter .. ".neon");
		table.insert(extensionFilters, extensionFilter .. ".arm.neon");
	end
	return extensionFilters;
end
-- Initializing public helpers (and thus lowercase names) - don't remove even though they are not referenced within the module itself!
(function()
	local languageFilterVariables = {
		{
			language = "as",
			extensions = androidndk.asExtensions,
		},
		{
			language = "asm",
			extensions = { androidndk.asmExtension },
		},
		{
			language = "c",
			extensions = { androidndk.cExtension },
		},
		{
			language = "cpp",
			-- Premake filters are case-insensitive, so C sources would pass **.C as well - skip it in the C++ filter.
			-- It's not recommended to use the .C extension at all for this reason.
			extensions = table.filter(
				androidndk.cppExtensions,
				function(extension)
					return extension ~= ".C";
				end),
		},
		{
			language = "rs",
			extensions = androidndk.rsExtensions,
		},
	};
	for i, languageFilterVariable in ipairs(languageFilterVariables) do
		local extensionsCaseInsensitive = {};
		-- Premake filters are case-insensitive - don't add the same extension twice.
		for i2, extension in ipairs(languageFilterVariable.extensions) do
			table.insertkeyed(extensionsCaseInsensitive, string.lower(extension));
		end
		-- Build arrays of raw extensions with all possible ARM suffixes:
		-- androidndk.prefixfilefilterextensions = { ".ext", ".ext.arm", ".ext.neon", ".ext.arm.neon"... }
		-- This allows arbitrary usage of table.translate, including to prepend a specific file name.
		local extensionsWithSuffixes = {};
		for i2, extension in ipairs(extensionsCaseInsensitive) do
			table.insert(extensionsWithSuffixes, extension);
			table.insert(extensionsWithSuffixes, extension .. ".arm");
			table.insert(extensionsWithSuffixes, extension .. ".neon");
			table.insert(extensionsWithSuffixes, extension .. ".arm.neon");
		end
		androidndk.filefilters[languageFilterVariable.language .. "extensions"] = extensionsWithSuffixes;
		-- Build inclusive filters for all subdirectories as a string.
		-- androidndk.filefilters.language = "files:**.ext or files:**.ext.arm or files:**.ext.neon or files:**.ext.arm.neon..."
		androidndk.filefilters[languageFilterVariable.language] =
			table.concat(
				table.translate(
					extensionsWithSuffixes,
					function(extension)
						return "files:**" .. extension;
					end),
					" or ");
		-- Build exclusive filters for all subdirectories as a table.
		-- androidndk.filefilters.notlanguage = { "files:not **.ext", "files:not **.ext.arm", "files:not **.ext.neon", "files:not **.ext.arm.neon"... }
		androidndk.filefilters["not" .. languageFilterVariable.language] =
			table.translate(
				extensionsWithSuffixes,
				function(extension)
					return "files:not **" .. extension;
				end);
	end
end)();

-- In this module, flags are gathered from both the project configuration and per-file configuration.
-- ndk-build, however, doesn't support per-file flags.
-- Per-file configuration is needed though because compilers for different languages may need different flags.
-- The `language` setting is a whole-project setting, it alone can't be used in a filter to specify which compiler should receive the flags.
-- Therefore, the file extension must be used as a filter.
-- This leads of a lot of duplication - every file in the project has project-level flags as well as extension-specific flags.
-- For this reason, each flag is added only once.
-- Because of this, a flag may contain one or multiple whitespace-separated compiler argument.
-- "-include a.h -include b.h -include \"c d.h\" -include \"c d.h\"" must NOT be deduplicated as:
-- { "-include", "a.h", "b.h", "\"c d.h\"" }
-- or as:
-- { "-include", "a.h", "b.h", "\"c", "d.h\"" }
-- It must be:
-- { "-include a.h", "-include b.h", "-include \"c d.h\"" }

-- Built-in flags (derived from from boolean or enumeration settings) here are added to the flags table directly as p.esc(value).
-- Most shell characters in them will be escaped at build time, however, " and \ will not.
-- So, it's possible to have built-in flags corresponding to one (possibly with quoted whitespaces) or multiple (with unquoted whitespaces) compiler arguments.
-- If a double quote character or a backslash needs to be used as a raw character, it needs to be pre-escaped manually in the flag literal here.
-- GNU make variable and function references should be used in built-in flags very carefully for the same reason.
-- Ordering of the flags is preserved only for their first occurrences in each of the LOCAL_languageFLAGS.
-- In Clang, if there are conflicting flags (such as -f and -fno), the ones later in the list take precedence.
-- Per-extension flags are therefore added after project-scope flags so the former can override the latter.

-- Makes the value a single command line arguments passed to the compiler with a prefix, which may be in the same or in a separate argument.
-- The value must be pre-escaped with p.esc.
-- The prefix (not pre-escaped) will be handled similar to built-in flags, and may contain unquoted whitespaces for separate command line arguments.
-- Examples of the output:
-- * -DCSTRING=\"Hello\"
-- * -D"CSTRING=\"Hello, world!\""
-- * -D "YASMSTRING=\"Hello, world!\""
-- * -include header.h
-- * -include "header file.h"
-- * PREMAKE_ANDROIDNDK_TEMPORARY_1 := $(ENVIRONMENT_VARIABLE)/New folder (2)/header file.h
--   -include "$(call PREMAKE_ANDROIDNDK_SHELL_ESCAPE_PRE_QUOTES,$(PREMAKE_ANDROIDNDK_TEMPORARY_1))"
function androidndk.getSingleArgumentPrefixedFlagPostValueEsc(value, prefix, temporaryVariables)
	local flagParts = { p.esc(prefix) };
	-- While it's completely safe to add excessive quotes in general, in some cases ndk-build doesn't expect them.
	-- One example being LOCAL_LDLIBS, which is designed only for linking to Android system libraries.
	-- ndk-build checks each entry against a list of known Android system libraries, and throws a warning if any non-system ones are specified.
	-- The intended usage pattern of LOCAL_LDLIBS `LOCAL_LDLIBS := -landroid -llog`, not ``LOCAL_LDLIBS := -l"android" -l"log"`.
	-- So, adding quotes only if there are whitespaces or references (for which it's not known whether they will be expanded to something containing whitespaces).
	local isQuoted = androidndk.hasNonEmptyMakeReferencesPostEsc(value) or androidndk.staticallyHasPatternPostEsc(value, "%s");
	if isQuoted then
		table.insert(flagParts, "\"");
	end
	table.insert(flagParts, androidndk.shellEscapePreQuotesPostEsc(value, temporaryVariables));
	if isQuoted then
		table.insert(flagParts, "\"");
	end
	return table.concat(flagParts);
end

-- System include directories are normally placed after the local ones, including in ndk-build itself.
androidndk.includeDirsConfigSettings = { "includedirs", "sysincludedirs" };

function androidndk.addIncludeDirs(includeDirs, config)
	-- In LOCAL_C_INCLUDES (tested on it, but LOCAL_RENDERSCRIPT_INCLUDES goes to the host-c-includes call too):
	-- Allowed directly on Linux: !%*+,-./:=?@[]^_{}~
	-- Allowed if \-escaped on Linux: "&'();<>\`|
	-- Escaped UNC paths (beginning with \\\\) are supported on Windows.
	-- Disallowed: whitespaces, #$
	-- In the NDK itself, either absolute or relative to the NDK root, not to the local path - need $(LOCAL_PATH) explicitly.
	for i, settingName in ipairs(androidndk.includeDirsConfigSettings) do
		local settingOutput = includeDirs[settingName];
		if settingOutput == nil then
			settingOutput = {};
			includeDirs[settingName] = settingOutput;
		end
		local settingInput = config[settingName];
		for i2, includeDir in ipairs(settingInput) do
			local includeDirPath = androidndk.getEscapedProjectRelativePath(config.project, includeDir, true);
			if androidndk.staticallyHasPatternPostEsc(includeDirPath, "[%s#%$]") then
				p.warn(
					"Skipping workspace '%s' project '%s' configuration '%s' include directory '%s' with whitespaces or disallowed characters #$",
					config.workspace.name, config.project.name, config.name, includeDir);
			else
				table.insert(settingOutput, includeDirPath);
			end
		end
	end
end

function androidndk.writeProjectIncludeDirs(includeDirsForAllVariables, variable, escapeShellCharacters)
	local includeDirsForVariable = includeDirsForAllVariables[variable];
	if includeDirsForVariable == nil then
		return false;
	end
	-- Merge all config settings the include directories are gathered from in the correct order.
	local includeDirsForVariableMerged = {};
	for i, configSettingName in ipairs(androidndk.includeDirsConfigSettings) do
		if includeDirsForVariable[configSettingName] ~= nil then
			for i2, includeDir in ipairs(includeDirsForVariable[configSettingName]) do
				table.insertkeyed(includeDirsForVariableMerged, includeDir);
			end
		end
	end
	local localVariable = "LOCAL_" .. variable;
	if androidndk.assignToVariablePostEsc(localVariable, includeDirsForVariableMerged, true, androidndk.shellEscapeChecker) then
		if escapeShellCharacters then
			androidndk.writePostProcessCall(localVariable, androidndk.shellEscapeMakeCall);
		end
		return true;
	end
	return false;
end

-- Assuming Clang - GCC was removed in NDK r13.
-- RenderScript is based on C99, but for writing compute kernels.

-- Supported values are built-in flags as single strings and tables of strings (will be separate flags table elements).

androidndk.asmFlagsSettingFlags = {
	{ key = "FatalCompileWarnings", value = "-Werror" },
};

androidndk.cCppFlagsSettingFlags = {
	{ key = "FatalCompileWarnings", value = "-Werror" },
	-- LinkTimeOptimization is per-project, not per-extension, as it needs to be easily queryable in static library dependency analysis.
	-- NoBufferSecurityCheck is C++-only in p.clang, but nothing precludes its usage in C.
	-- Android uses -fstack-protector-strong by default as of NDK r23.
	{ key = "NoBufferSecurityCheck", value = "-fno-stack-protector" },
	{ key = "ShadowedVariables", value = "-Wshadow" },
	{ key = "UndefinedIdentifiers", value = "-Wundef" },
};

androidndk.rsFlagsSettingFlags = {
	{ key = "FatalCompileWarnings", value = "-Werror" },
	{ key = "ShadowedVariables", value = "-Wshadow" },
	{ key = "UndefinedIdentifiers", value = "-Wundef" },
};

-- Instead of using p.clang and mapFlags (with all its complexity), listing only what's relevant to ndk-build.
-- Supported keys are only strings and booleans (as p.OFF and p.ON), no tables (to avoid the complexity of keeping a deterministic order).
-- Supported values are built-in flags as single strings and tables of strings (will be separate flags table elements).
-- Values may contain unquoted (for multiple options) or quoted whitespaces, or \-escaped " and \, but p.esc will be done before writing.

androidndk.asmSettingValueFlags = {
	{
		key = "warnings",
		values = {
			[p.OFF] = "-w",
		},
	},
};

androidndk.cCppSettingValueFlags = {
	-- architecture is chosen via APP_ABI.
	-- flags are handled separately to avoid ensuring deterministic table ordering.
	{
		key = "floatingpoint",
		values = {
			Fast = "-ffast-math",
		},
	},
	-- floatingpointexceptions not present in p.clang as of v5.0.0-alpha16, added here.
	{
		key = "floatingpointexceptions",
		values = {
			[p.ON] = "-ftrapping-math",
			[p.OFF] = "-fno-trapping-math",
		},
	},
	{
		key = "strictaliasing",
		values = {
			[p.OFF] = "-fno-strict-aliasing",
			Level1 = { "-fstrict-aliasing", "-Wstrict-aliasing=1" },
			Level2 = { "-fstrict-aliasing", "-Wstrict-aliasing=2" },
			Level3 = { "-fstrict-aliasing", "-Wstrict-aliasing=3" },
		},
	},
	-- optimize is chosen via APP_OPTIM.
	-- pic is always enabled by ndk-build and is required on Android.
	-- vectorextensions are per-architecture.
	-- isaextensions are per-architecture.
	{
		key = "warnings",
		values = {
			[p.OFF] = "-w",
			High = "-Wall",
			Extra = { "-Wall", "-Wextra" },
			Everything = "-Weverything",
		},
	},
	-- symbols are chosen via APP_DEBUG.
	{
		key = "unsignedchar",
		values = {
			[p.ON] = "-funsigned-char",
			[p.OFF] = "-fno-unsigned-char",
		},
	},
	-- omitframepointer Off is needed for the Address Sanitizer, so exposed here.
	-- More info about omitframepointer on Android: https://github.com/android/ndk/issues/824
	{
		key = "omitframepointer",
		values = {
			[p.ON] = "-fomit-frame-pointer",
			[p.OFF] = "-fno-omit-frame-pointer",
		},
	},
	-- visibility and inlinesvisibility are C++-only in p.clang in v5.0.0-alpha16, but nothing precludes their usage in C.
	{
		key = "visibility",
		values = {
			Default = "-fvisibility=default",
			Hidden = "-fvisibility=hidden",
			Internal = "-fvisibility=internal",
			Protected = "-fvisibility=protected",
		},
	},
	{
		key = "inlinesvisibility",
		values = {
			Hidden = "-fvisibility-inlines-hidden",
		},
	},
};

androidndk.cSettingValueFlags = {
	{
		key = "cdialect",
		values = {
			["C89"] = "-std=c89",
			["C90"] = "-std=c90",
			["C99"] = "-std=c99",
			["C11"] = "-std=c11",
			["gnu89"] = "-std=gnu89",
			["gnu90"] = "-std=gnu90",
			["gnu99"] = "-std=gnu99",
			["gnu11"] = "-std=gnu11",
		},
	},
}

androidndk.cppSettingValueFlags = {
	-- exceptionhandling is chosen via LOCAL_CPP_FEATURES.
	{
		key = "cppdialect",
		values = {
			["C++98"] = "-std=c++98",
			["C++0x"] = "-std=c++0x",
			["C++11"] = "-std=c++11",
			["C++1y"] = "-std=c++1y",
			["C++14"] = "-std=c++14",
			["C++1z"] = "-std=c++1z",
			["C++17"] = "-std=c++17",
			["C++2a"] = "-std=c++2a",
			["C++20"] = "-std=c++20",
			["gnu++98"] = "-std=gnu++98",
			["gnu++0x"] = "-std=gnu++0x",
			["gnu++11"] = "-std=gnu++11",
			["gnu++1y"] = "-std=gnu++1y",
			["gnu++14"] = "-std=gnu++14",
			["gnu++1z"] = "-std=gnu++1z",
			["gnu++17"] = "-std=gnu++17",
			["gnu++2a"] = "-std=gnu++2a",
			["gnu++20"] = "-std=gnu++20",
			["C++latest"] = "-std=c++20",
		},
	},
	-- rtti is chosen via LOCAL_CPP_FEATURES.
};

androidndk.rsSettingValueFlags = {
	{
		key = "warnings",
		values = {
			[p.OFF] = "-w",
			High = "-Wall",
			Extra = { "-Wall", "-Wextra" },
			Everything = "-Weverything",
		},
	},
	-- No other cCppFlagsSettingFlags and cSettingValueFlags are supported.
};

androidndk.asmWarningFlags = {
	{ key = "enablewarnings", prefix = "-W" },
	{ key = "disablewarnings", prefix = "-Wno-" },
	-- No -Werror= on YASM, pick the closest to the intention.
	{ key = "fatalwarnings", prefix = "-W" },
};

androidndk.cCppWarningFlags = {
	{ key = "enablewarnings", prefix = "-W" },
	{ key = "disablewarnings", prefix = "-Wno-" },
	{ key = "fatalwarnings", prefix = "-Werror=" },
};

function androidndk.addCompilerFlagsForExtension(flagsForExtension, extension, config, temporaryVariables)
	-- Make sure the table for generic flags exists.
	if flagsForExtension.buildoptions == nil then
		flagsForExtension.buildoptions = {};
	end

	local isCCpp = extension == androidndk.cExtension or androidndk.cppExtensions[extension] ~= nil;

	local languageDefinesPrefix = nil;
	local languageUndefinesPrefix = nil;
	local languageFlagsSettingFlags = nil;
	local languageSettingValueFlagsTables = {};
	local languageWarningFlags = nil;
	if extension == androidndk.asmExtension then
		-- The defines prefix is separated into a different argument.
		languageDefinesPrefix = "-D ";
		languageUndefinesPrefix = "-U ";
		languageFlagsSettingFlags = androidndk.asmFlagsSettingFlags;
		table.insert(languageSettingValueFlagsTables, androidndk.asmSettingValueFlags);
		languageWarningFlags = androidndk.asmWarningFlags;
	elseif isCCpp then
		-- The defines prefix is in the same argument (though separation also works, but ndk-build itself doesn't separate).
		languageDefinesPrefix = "-D";
		languageUndefinesPrefix = "-U";
		-- Currently only shared between C and C++.
		languageFlagsSettingFlags = androidndk.cCppFlagsSettingFlags;
		table.insert(languageSettingValueFlagsTables, androidndk.cCppSettingValueFlags);
		if androidndk.cppExtensions[extension] ~= nil then
			table.insert(languageSettingValueFlagsTables, androidndk.cppSettingValueFlags);
		else
			table.insert(languageSettingValueFlagsTables, androidndk.cSettingValueFlags);
		end
		languageWarningFlags = androidndk.cCppWarningFlags;
	elseif androidndk.rsExtensions[extension] ~= nil then
		-- -D and -U are not supported.
		languageFlagsSettingFlags = androidndk.rsFlagsSettingFlags;
		table.insert(languageSettingValueFlagsTables, androidndk.rsSettingValueFlags);
		languageWarningFlags = androidndk.cCppWarningFlags;
	end

	-- Preprocessor definitions (not supported by the GNU assembler).
	-- Potentially with whitespaces, but need to go to a single (quoted) argument.
	-- Defines before undefines for consistency with other Premake actions such as Visual Studio.
	-- Placing them in separate tables so they're not mixed if both defines are undefines are provided by both the project and the extension filter.
	-- Not doing the same for -D and -U provided via raw buildoptions though to avoid interfering with the project-provided order.
	if languageDefinesPrefix ~= nil then
		if flagsForExtension.defines == nil then
			flagsForExtension.defines = {};
		end
		for i, define in ipairs(config.defines) do
			table.insertkeyed(
				flagsForExtension.defines,
				androidndk.getSingleArgumentPrefixedFlagPostValueEsc(p.esc(define), languageDefinesPrefix, temporaryVariables));
		end
	end
	if languageUndefinesPrefix ~= nil then
		if flagsForExtension.undefines == nil then
			flagsForExtension.undefines = {};
		end
		for i, undefine in ipairs(config.undefines) do
			table.insertkeyed(
				flagsForExtension.undefines,
				androidndk.getSingleArgumentPrefixedFlagPostValueEsc(p.esc(undefine), languageUndefinesPrefix, temporaryVariables));
		end
	end

	-- Forced include paths (not supported by the GNU assembler).
	if extension == androidndk.asmExtension then
		for i, forceInclude in ipairs(config.forceincludes) do
			local forceIncludePath = androidndk.getEscapedProjectRelativePath(config.project, forceInclude, true);
			if androidndk.staticallyHasPatternPostEsc(forceIncludePath, "[\"';]") then
				p.warn(
					"Skipping workspace '%s' project '%s' configuration '%s' Yasm force include '%s' with path containing disallowed characters \"';",
					config.workspace.name, config.project.name, config.name, forceInclude);
			else
				table.insertkeyed(
					flagsForExtension.buildoptions,
					androidndk.getSingleArgumentPrefixedFlagPostValueEsc(forceIncludePath, "-P ", temporaryVariables));
			end
		end
	elseif isCCpp then
		-- -include is not supported by RenderScript.
		for i, forceInclude in ipairs(config.forceincludes) do
			local forceIncludePath = androidndk.getEscapedProjectRelativePath(config.project, forceInclude, true);
			-- -include %s becomes #include "%s", the inner " is considered a string terminator.
			if androidndk.staticallyHasPatternPostEsc(forceIncludePath, "[\"]") then
				p.warn(
					"Skipping workspace '%s' project '%s' configuration '%s' C/C++ force include '%s' with path containing a disallowed double quote character",
					config.workspace.name, config.project.name, config.name, forceInclude);
			else
				table.insertkeyed(
					flagsForExtension.buildoptions,
					androidndk.getSingleArgumentPrefixedFlagPostValueEsc(forceIncludePath, "-include ", temporaryVariables));
			end
		end
	end

	-- Flags for configuration flags setting.
	if languageFlagsSettingFlags ~= nil then
		for i, flagsSettingKeyValue in ipairs(languageFlagsSettingFlags) do
			if config.flags[flagsSettingKeyValue.key] then
				local flagsSettingValue = flagsSettingKeyValue.value;
				if type(flagsSettingValue) ~= "table" then
					flagsSettingValue = { flagsSettingValue };
				end
				for i2, flagsSettingValueBuildOption in ipairs(flagsSettingValue) do
					table.insertkeyed(flagsForExtension.buildoptions, p.esc(flagsSettingValueBuildOption));
				end
			end
		end
	end

	-- Flags for setting values.
	for i, languageSettingValueFlags in ipairs(languageSettingValueFlagsTables) do
		for i2, languageSettingValueKeyValues in ipairs(languageSettingValueFlags) do
			local settingValue = config[languageSettingValueKeyValues.key];
			if settingValue ~= nil then
				-- Convert boolean to off/on.
				if settingValue == false then
					settingValue = p.OFF;
				elseif settingValue == true then
					settingValue = p.ON;
				end
				local settingValueFlags = languageSettingValueKeyValues.values[settingValue];
				if settingValueFlags ~= nil then
					if type(settingValueFlags) ~= "table" then
						settingValueFlags = { settingValueFlags };
					end
					for i3, settingValueFlag in ipairs(settingValueFlags) do
						table.insertkeyed(flagsForExtension.buildoptions, p.esc(settingValueFlag));
					end
				end
			end
		end
	end

	-- Individual warnings.
	-- After generic setting flags which include the default warning behavior so -Wname can override -w.
	if languageWarningFlags ~= nil then
		for i, warningKeyPrefix in ipairs(languageWarningFlags) do
			for i2, warning in ipairs(config[warningKeyPrefix.key]) do
				table.insertkeyed(
					flagsForExtension.buildoptions,
					androidndk.getSingleArgumentPrefixedFlagPostValueEsc(p.esc(warning), warningKeyPrefix.prefix, temporaryVariables));
			end
		end
	end

	-- Add raw project-specified flags, as single or multiple arguments, after everything (so they can cancel internal flags).
	-- Quoting, or escaping of quotes, must be done by the project instead, as a single build option may contain multiple arguments.
	-- Build options are platform-dependent anyway - the module is free to establish any rules.
	for i, buildOption in ipairs(config.buildoptions) do
		local buildOptionEscaped = p.esc(buildOption);
		table.insertkeyed(flagsForExtension.buildoptions, buildOptionEscaped);
		if isCCpp and androidndk.isFltoOption(buildOptionEscaped) then
			-- Store the last (thus the highest-priority) -flto type used by the language.
			-- RenderScript doesn't support -flto.
			flagsForExtension.flto = buildOptionEscaped;
		end
	end
end

-- Defines before undefines for consistency with other Premake actions such as Visual Studio.
-- Everything special before everything generic (including raw project buildoptions) for the same reason.
-- Separate to make sure -D -U -D -U instead of -D -D -U -U doesn't happen if both are provided by both the project and the extension filter.
androidndk.projectCompilerFlagsOrder = { "defines", "undefines", "buildoptions" };

function androidndk.writeProjectCompilerFlags(flagsForAllVariables, variable, escapeShellCharacters)
	local flagsForVariable = flagsForAllVariables[variable];
	if flagsForVariable == nil then
		return false;
	end
	local flagsForVariableMerged = {};
	-- Merge all sources of flags in the correct order.
	for i, flagsTableName in ipairs(androidndk.projectCompilerFlagsOrder) do
		if flagsForVariable[flagsTableName] ~= nil then
			for i2, flag in ipairs(flagsForVariable[flagsTableName]) do
				table.insertkeyed(flagsForVariableMerged, flag);
			end
		end
	end
	local localVariable = "LOCAL_" .. variable;
	if androidndk.assignToVariablePostEsc(localVariable, flagsForVariableMerged, true, androidndk.shellEscapePostQuotesChecker) then
		if escapeShellCharacters then
			androidndk.writePostProcessCall(localVariable, androidndk.shellEscapePostQuotesMakeCall);
		end
		return true;
	end
	return false;
end

-- Built-in flags for ISA and vector extensions.

androidndk.abiIsaExtensions = {
	["x86"] = {
		MOVBE = "-mmovbe",
		POPCNT = "-mpopcnt",
		PCLMUL = "-mpclmul",
		LZCNT = "-mlzcnt",
		BMI = "-mbmi",
		BMI2 = "-mbmi2",
		F16C = "-mf16c",
		AES = "-maes",
		FMA = "-mfma",
		FMA4 = "-mfma4",
		RDRND = "-mrdrnd",
	},
};
androidndk.abiIsaExtensions["x86_64"] = androidndk.abiIsaExtensions["x86"];

androidndk.abiVectorExtensions = {
	["x86"] = {
		-- Up to SSSE3 are required.
		["SSE4.1"] = "-msse4.1",
		["SSE4.2"] = "-msse4.2",
		["AVX"] = "-mavx",
		["AVX2"] = "-mavx2",
	},
	["x86_64"] = {
		-- Up to SSE4.2 are required.
		["AVX"] = "-mavx",
		["AVX2"] = "-mavx2",
	},
};

-- Escaped or not doesn't matter.
function androidndk.isFltoOption(option)
	-- Remove quotes (so "-flto..." is handled like -flto...).
	-- Escaped or not doesn't matter as the pattern being checked doesn't include a backslash.
	option = string.gsub(option, "\"", "");
	-- Let -flto alone, or -flto=..., pass.
	return string.find(option, "^%s*%-flto%s$") ~= nil or string.find(option, "^%s*%-flto=") ~= nil;
end

-- ldFlagsUndefined receives -u and --undefined from `linkoptions`.
-- ldLibsDirFlags receives -L from `linkoptions` and -L for `links`.
-- ldLibsSysDirFlags receives -L for `syslibdirs`.
-- ldLibsLibFlags receives -l from `linkoptions` and -l for `links`.
-- ldFlags receives the rest of `linkoptions`.
-- Any output table can be nil.
-- In this case, only libraries to link to will be obtained and written to ldLibs*Flags.
-- Returns the last encountered (thus highest-priority) -flto option if any is passed (so non-default LTO types can be used with transitivity).
function androidndk.addSingleConfigLinkerFlags(config, ldFlagsUndefined, ldFlags, ldLibsDirFlags, ldLibsSysDirFlags, ldLibsLibFlags, temporaryVariables)
	-- NDK passes LDFLAGS before LDLIBS.
	-- It also placed local LDLIBS before imported LDLIBS.
	-- Entries for the system libraries (`syslibdirs` here specifically) should be the last according to this ordering also.
	-- The system can be considered the deepest import of everything.
	-- For LDFLAGS, it's the reverse, however - imported LDFLAGS are before local LDFLAGS.

	-- This module also distributes `linkoptions` between LDFLAGS and LDLIBS instead of passing all to LDFLAGS.
	-- LDLIBS is what's designed to hold the -l flags for the system libraries to link to.
	-- While LDFLAGS can contain -l too, it's not the intended way of passing them.
	-- The reason why this is taken into consideration, and `linkoptions` are parsed at all, is the special case of name collision resolution.
	-- A workspace may contain its own project, for example, named "log", and in this case a "log" link would be considered a sibling link, not a system one.
	-- An alternative would be to link to ":liblog.so".
	-- However, this will result in a warning as ndk-build uses simpler logic for checking whether only system libraries are specified which fails for that.
	-- Therefore, this module offers a way to pass "-llog" via `linkoptions`.

	-- Normally though -l should be used only for a small fixed set of Android NDK system libraries.
	-- All this logic is therefore a massive overkill.
	-- Prebuilt library projects normally should be used instead of -L and -l.
	-- However, for the ease of porting, and to avoid adding constraints, letting projects link directly to libraries via raw linker arguments anyway.
	-- Specifying anything but -l would throw a warning though.

	-- Search paths (-L) apply to all -l options regardless of the order.
	-- They can be written to either LDFLAGS or LDLIBS.
	-- This module implements dependency transitivity a custom way, stopping iterating at shared libraries (unlike NDK's internal exports).
	-- For this purpose, it only imports everything that goes to LDLIBS, but not to LDFLAGS - assuming it contains everything needed for library linkage.
	-- So, always writing search paths to LDLIBS here, not to LDFLAGS.

	-- Handling `linkoptions` before `links` and `syslibdirs` because the latter is conceptually closer to LDFLAGS, and the latter two to LDLIBS.
	-- Considering -L specified in `linkoptions` as the more generic `links` (which are placed before `syslibdirs`) for the same reason as well.

	local flto = nil;
	local longLinkOptions = {
		{
			name = "--library",
			destination = ldLibsLibFlags,
		},
		{
			name = "--library-path",
			destination = ldLibsDirFlags,
		},
		{
			name = "--undefined",
			destination = ldFlagsUndefined,
		},
	};
	for i, linkOptionUnescaped in ipairs(config.linkoptions) do
		local linkOption = p.esc(linkOptionUnescaped);
		-- Check which output table should receive the option.
		local linkOptionDestination = ldFlags;
		-- -flto is a Clang++ option, not an LLD one - don't check it if there's -Wl.
		-- Also, it's either a full option, or an option with a value - check it in a special way for this reason as well.
		if androidndk.isFltoOption(linkOption) then
			flto = linkOption;
		else
			-- Trim whitespaces (until the first quote if present).
			local linkOptionFirstNonWhitespace = string.find(linkOption, "[%S]");
			if linkOptionFirstNonWhitespace ~= nil then
				-- Remove quotes (so "-l..." is handled like -l...).
				-- Escaped or not doesn't matter as none of the checked prefixes include a backslash.
				local linkOptionForPrefix = string.gsub(string.sub(linkOption, linkOptionFirstNonWhitespace, -1), "\"", "");
				-- ndk-build passes the flags to Clang++, not to LLD directly.
				-- Therefore, most of linker options must be passed via -Wl, and for those that don't, the presence of -Wl doesn't matter.
				-- Specifically, -l and -L can be passed to both Clang++ and LLD, but --library and --library-path can't (and require -Wl).
				-- -l and -L can be either attached directly to the name or placed in a separate (whitespace-separated) argument.
				-- --library and --library-path can be either attached with a = or placed in a separate argument.
				-- Since --library and --library-path require -Wl, arguments are comma-separate rather than whitespace-separated.
				local wlPrefix = "-Wl,";
				local wlPrefixLength = string.len(wlPrefix);
				local hasWl = string.sub(linkOption, 1, string.len(wlPrefixLength)) == wlPrefix;
				if hasWl then
					linkOptionForPrefix = string.sub(linkOptionForPrefix, wlPrefixLength + 1, -1);
				end
				local linkOptionSingleCharacterPrefix = string.sub(linkOptionForPrefix, 1, 2);
				if linkOptionSingleCharacterPrefix == "-u" then
					linkOptionDestination = ldFlagsUndefined;
				elseif linkOptionSingleCharacterPrefix == "-l" then
					linkOptionDestination = ldLibsLibFlags;
				elseif linkOptionSingleCharacterPrefix == "-L" then
					linkOptionDestination = ldLibsDirFlags;
				else
					if hasWl then
						-- Check if --Wl,--option=value or --Wl,--option,value is used.
						for i2, longLinkOption in ipairs(longLinkOptions) do
							local longLinkOptionPrefixSub = string.sub(linkOptionForPrefix, 1, string.len(longLinkOption.name));
							if longLinkOption.name == (longLinkOptionPrefixSub .. "=") or longLinkOption.name == (longLinkOptionPrefixSub .. ",") then
								linkOptionDestination = longLinkOption.destination;
								break;
							end
						end
					end
				end
			end
		end
		-- Add the flag to the needed table if adding to one was requested at all.
		-- Quoting, or escaping of quotes, must be done by the project instead, as a single link option may contain multiple arguments.
		-- Link options are platform-dependent anyway - the module is free to establish any rules.
		if linkOptionDestination ~= nil then
			table.insertkeyed(linkOptionDestination, linkOption);
		end
	end

	-- Local search paths (`libdirs` and `links`).
	if ldLibsDirFlags ~= nil then
		for i, libDir in ipairs(p.config.getlinks(config, "system", "directory")) do
			local libDirRelativePath = androidndk.getEscapedProjectRelativePath(config.project, libDir, true);
			table.insertkeyed(
				ldLibsDirFlags,
				androidndk.getSingleArgumentPrefixedFlagPostValueEsc(libDirRelativePath, "-L", temporaryVariables));
		end
	end

	-- System search paths.
	if ldLibsSysDirFlags ~= nil then
		for i, sysLibDir in ipairs(config.syslibdirs) do
			local sysLibDirRelativePath = androidndk.getEscapedProjectRelativePath(config.project, sysLibDir, true);
			table.insertkeyed(
				ldLibsSysDirFlags,
				androidndk.getSingleArgumentPrefixedFlagPostValueEsc(sysLibDirRelativePath, "-L", temporaryVariables));
		end
	end

	-- Local links.
	-- Specifying the : prefix directly in `links` is allowed to force treatment of the name as a full file name instead of a short name.
	-- However, just specifying the full file name is also allowed for simplicity of the usage (especially of the usage of full paths).
	-- libname.so will be treated as libname.so, not as liblibname.so.a or liblibname.so.so.
	-- However, something like name.thumb will be treated as libname.thumb.a/libname.thumb.so still.
	-- Making no special assumptions about GNU make references (such as environment variables).
	-- The intended usage of LOCAL_LDLIBS is purely for linking to the libraries provided by the Android NDK via their short names anyway.
	-- To use, for instance, a full path from an environment variable (or a different kind of a GNU make reference), specify:
	-- links({ "$(dir $(VARIABLE))/:$(notdir $(VARIABLE))" })
	if ldLibsLibFlags ~= nil then
		for i, libName in ipairs(p.config.getlinks(config, "system", "name")) do
			local libNamePrefix = "";
			if string.sub(libName, 1, 1) ~= ":" then
				-- Full name not forced.
				-- Check if using the full name anyway.
				local libExtension = path.getextension(libName);
				if libExtension == ".a" or libExtension == ".so" then
					libNamePrefix = ":";
				end
			end
			table.insertkeyed(
				ldLibsLibFlags,
				androidndk.getSingleArgumentPrefixedFlagPostValueEsc(p.esc(libNamePrefix .. libName), "-l", temporaryVariables));
		end
	end

	return flto;
end

function androidndk.generateProjectConfig(config)
	local temporaryVariables = {};

	local configAbi = androidndk.getConfigAbi(config);
	assert(configAbi ~= nil, "Configurations with invalid ABIs must be skipped in isConfigSupported");

	local configUsesA32 = androidndk.configUsesA32(config);
	local configUsesNeon = androidndk.configUsesNeon(config);

	-- Get the precompiler header path.
	-- Handling of the ARM instruction set and NEON is done by ndk-build implicitly, not possible and not needed to specify suffixes.
	-- All the inclusion of the built header is done by ndk-build itself implicitly.
	-- At this point, it's needed for getting the file configuration for it so, if needed, C++-specific options can be extracted from it.
	local pch = nil;
	if not config.flags.NoPCH and config.pchheader ~= nil then
		pch = androidndk.getEscapedProjectRelativePath(config.project, config.pchheader, false);
		-- LOCAL_PCH is involved a value that goes to LOCAL_SRC_FILES internally in ndk-build, so the rules are the same.
		-- However, = is also not allowed.
		if androidndk.staticallyHasPatternPostEsc(pch, "[%s\"#%$&'%(%),;<=>`|]") then
			p.warn(
				"Skipping workspace '%s' project '%s' configuration '%s' precompiled header '%s' " ..
				"with path containing whitespaces or disallowed characters \"#$&'(),;<=>`|",
				config.workspace.name, config.project.name, config.name, pch);
			pch = nil;
		end
	end
	local pchFileConfig = nil;

	-- Gather source files not excluded from build.
	local sourceTree = p.project.getsourcetree(config.project);
	local configAbiSupportsYasm = configAbi == "x86" or configAbi == "x86_64" or configAbi == androidndk.ABI_ALL;
	-- External Android.mk files and prebuilt libraries.
	local sourcePrecreatedFiles = {};
	-- Keys - sequential indexes, paths without .arm and .neon suffixes.
	-- Values - paths with .arm and .neon suffixes.
	local sourceFiles = {};
	local sourceFilesYasmConditional = {};
	-- includeDirs[variable] and compilerFlags[variable] may be nil if no source files contributing to them have been found yet.
	-- Each includeDirs element optionally contains includedirs = {}, sysincludedirs = {}.
	local includeDirs = {};
	local renderScriptIncludeDirsVariable = iif(config.renderscriptincludedirsoverride == true, "RENDERSCRIPT_INCLUDES_OVERRIDE", "RENDERSCRIPT_INCLUDES");
	-- Each compilerFlags element optionally contains defines = {}, undefines = {}, buildoptions (used for the rest of flags) = {}, flto = "...".
	-- flto, if present, contains the last -flto flag encountered for this extension.
	local compilerFlags = {};
	-- For simplicity, for project-defined flags, using separate CONLYFLAGS and CPPFLAGS.
	-- Using LOCAL_CFLAGS is also undesirable because they go not only to C and C++, but to GNU assembly as well.
	-- See the definition of ev-compile-s-source in ndk-build.
	local configIncludeDirsAdded = {};
	local configCompilerFlagsAdded = {};
	p.tree.traverse(sourceTree, {
		onleaf = function(fileNode, depth)
			local fileConfig = p.fileconfig.getconfig(fileNode, config);
			-- Check if the file is present at all in the current configuration and not explicitly excluded with a file filter.
			if fileConfig ~= nil then
				-- abspath must be used, as with relpath or path, a path relative to the Android.mk location is written in the end, not to LOCAL_PATH.
				local sourceOriginalRelativePath = androidndk.getEscapedProjectRelativePath(config.project, fileNode.abspath, false);
				-- If this is the precompiled header, store the file configuration for it so it can be used later to obtain C++-specific settings.
				-- ExcludeFromBuild has no effect on whether the precompiled header is used in other Premake actions.
				if sourceOriginalRelativePath == pch then
					pchFileConfig = fileConfig;
				end
				if not fileConfig.flags.ExcludeFromBuild then
					-- Handle according to the extension.
					-- Supporting external Android.mk files, prebuilt libraries, source files (possibly with .arm and .neon suffixes).
					-- Unlike path.hasextension, ndk-build is case-sensitive (.C is treated as C++ by ndk-build by default).
					-- Therefore, using == for path.getextension instead of path.hasextension as the latter is case-insensitive.
					local sourceOriginalExtension = path.getextension(sourceOriginalRelativePath);
					local sourceOriginalBaseName = path.getbasename(sourceOriginalRelativePath);
					-- Check if the file name is not empty.
					if sourceOriginalBaseName ~= "" then
						if sourceOriginalExtension == ".mk" then
							-- Need the full path, not a relative path like in LOCAL_SRC_FILES.
							local sourceAndroidMkPath = androidndk.getEscapedProjectRelativePath(config.project, fileNode.abspath, true);
							-- Whitespaces in include statements are supported, but need to be escaped with \ which themselves are escapable in this case.
							-- Meaning, n/2 backslashes will be passed, and escaping will be done only by an odd number of backslashes.
							-- This makes it hard to handle cases of backslashes before whitespaces in the original path.
							-- Backslashes not before spaces are treated as raw characters, however - can't replace all with two backslashes.
							if androidndk.staticallyHasPatternPostEsc(sourceAndroidMkPath, "[%s]") then
								p.warn(
									"Skipping workspace '%s' project '%s' configuration '%s' file '%s' " ..
									"with path containing whitespaces, which are not supported",
									config.workspace.name, config.project.name, config.name, sourceAndroidMkPath);
							else
								table.insertkeyed(sourcePrecreatedFiles, sourceAndroidMkPath);
							end
						elseif sourceOriginalExtension == ".a" or sourceOriginalExtension == ".so" then
							-- LOCAL_SRC_FILES limitations for prebuilt libraries:
							-- Backslash escaping of shell characters is NOT supported on Windows.
							-- Escaping with a backslash works on Linux, however, but it's not needed for any of the allowed characters there.
							-- On Linux, the path goes to `cp`.
							-- Disallowed characters on Linux: whitespaces, "#$%&'()*:;<>?\`|
							-- * is treated as a wildcard, so it can't truly be a part of a file name either.
							-- \ is allowed on Windows, however, as a path separator.
							-- On Windows, the path goes to `copy` after replacing / with \.
							-- Disallowed characters on Windows: whitespaces, "#$%&*;<>?|
							-- : is allowed on Windows as a drive letter separator.
							-- Therefore, on Windows, strictly more different characters are allowed.
							-- The user may, however, possibly want to use the generated scripts on just Windows.
							-- For this reason, only paths with characters disallowed on both (not either) hosts must be filtered out here.
							-- There's no need to impose overly strict constraints, this check acts as a portability aid.
							if androidndk.staticallyHasPatternPostEsc(sourceOriginalRelativePath, "[%s\"#%$%%&%*;<>%?|]") then
								-- % needs to be escaped as %% in printf format strings.
								p.warn(
									"Skipping workspace '%s' project '%s' configuration '%s' file '%s' " ..
									"with path containing whitespaces or disallowed characters \"#$%%&*;<>?|",
									config.workspace.name, config.project.name, config.name, sourceOriginalRelativePath);
							else
								table.insertkeyed(sourcePrecreatedFiles, sourceOriginalRelativePath);
							end
						else
							-- .arm and .neon suffixes internally enable the A32 instruction set and NEON respectively for the base file.
							-- They're also supported on ABIs other than armeabi-v7a, having no effect in this case, the file is built as usual.
							-- With LOCAL_ARM_MODE := arm and LOCAL_ARM_NEON := true respectively, they have no effect also.
							-- These suffixes are allowed for all types of source files, even x86 assembly.
							local sourceRelativePath = sourceOriginalRelativePath;
							local sourceExtension = sourceOriginalExtension;
							-- Only .arm, .neon and .arm.neon combinations are supported - not .neon.arm.
							local sourceHasNeonForced = sourceExtension == ".neon";
							if sourceHasNeonForced then
								sourceRelativePath = path.removeextension(sourceRelativePath);
								sourceExtension = path.getextension(sourceRelativePath);
							end
							local sourceHasA32Forced = sourceExtension == ".arm";
							if sourceHasA32Forced then
								sourceRelativePath = path.removeextension(sourceRelativePath);
								sourceExtension = path.getextension(sourceRelativePath);
							end
							if sourceExtension == ".arm" or sourceExtension == ".neon" then
								p.warn(
									"Workspace '%s' project '%s' config '%s' file '%s' has an incorrect armeabi suffix - " ..
									"only .arm, .neon and .arm.neon are allowed by the NDK",
									config.workspace.name, config.project.name, config.name, fileNode.abspath);
							else
								local sourceBaseName = path.getbasename(sourceRelativePath);
								-- Check if the file name is not empty.
								if sourceBaseName ~= "" then
									-- Silently skipping files in the project unrelated to ndk-build, as well as headers.
									if androidndk.sourceExtensions[sourceExtension] ~= nil then
										-- Is a source file.

										-- LOCAL_SRC_FILES limitations for source files:
										-- Allowed directly on Linux: !%+-./=?@[]^_{}~
										-- Allowed if \-escaped on Linux: *
										-- (* works correctly on Linux, not as a wildcard.)
										-- : is allowed if escaped on Linux, but is the drive separator on Windows, and is not escapable there.
										-- Absolute paths are okay, so escaping should be disabled dynamically on Windows.
										-- Allowed and escapable on Windows, disallowed on Linux: \
										-- UNC paths are not supported on Windows.
										-- Disallowed: whitespaces, "#$&'(),;<>`|
										if androidndk.staticallyHasPatternPostEsc(sourceOriginalRelativePath, "[%s\"#%$&'%(%),;<>`|]") then
											p.warn(
												"Skipping workspace '%s' project '%s' configuration '%s' file '%s' " ..
												"with path containing whitespaces or disallowed characters \"#$&'(),;<>`|",
												config.workspace.name, config.project.name, config.name, sourceOriginalRelativePath);
										else
											-- Try adding the file to source files.
											local sourceFileTable = sourceFiles;
											if sourceExtension == androidndk.asmExtension then
												-- .asm (YASM) files can be assembled only for x86 and x86_64, giving warnings on other architectures.
												-- YASM files are explicitly added only for x86 and x86_64 as otherwise ndk-build will be throwing warnings.
												if configAbiSupportsYasm then
													if configAbi == androidndk.ABI_ALL then
														-- Add YASM sources conditionally for multi-ABI configurations.
														sourceFileTable = sourceFilesYasmConditional;
													else
														-- Add YASM sources directly to the main LOCAL_SRC_FILES assignment for x86 and x86_64.
														sourceFileTable = sourceFiles;
													end
												else
													sourceFileTable = nil;
												end
											end
											if sourceFileTable ~= nil and sourceFileTable[sourceRelativePath] == nil then
												-- New source file.

												-- Add the file to the table.
												-- Allowing A32 and NEON to be enabled for files using either the suffixes or file filters.
												-- Considering the suffixes more important as they're always specified for individual files, while filters can be less granular.
												local sourceRelativePathWithSuffixesParts = { sourceRelativePath };
												if not configUsesA32 and not sourceHasA32Forced then
													sourceHasA32Forced = androidndk.configUsesA32(fileConfig);
												end
												if sourceHasA32Forced then
													table.insert(sourceRelativePathWithSuffixesParts, ".arm");
												end
												if not configUsesNeon and not sourceHasNeonForced then
													sourceHasNeonForced = androidndk.configUsesNeon(fileConfig);
												end
												if sourceHasNeonForced then
													table.insert(sourceRelativePathWithSuffixesParts, ".neon");
												end
												local sourceRelativePathWithSuffixes = table.concat(sourceRelativePathWithSuffixesParts);
												sourceFileTable[sourceRelativePath] = sourceRelativePathWithSuffixes;
												table.insert(sourceFileTable, sourceRelativePathWithSuffixes);

												-- Gather include directories.
												-- C_INCLUDES is used for C, C++, GAS and YASM (all non-RenderScript source types supported), but not for RenderScript.
												local includeDirsVariable = iif(androidndk.rsExtensions[sourceExtension] ~= nil, renderScriptIncludeDirsVariable, "C_INCLUDES");
												local includeDirsForExtension = includeDirs[includeDirsVariable];
												if includeDirsForExtension == nil then
													includeDirsForExtension = {};
													includeDirs[includeDirsVariable] = includeDirsForExtension;
												end
												if not configIncludeDirsAdded[includeDirsVariable] then
													androidndk.addIncludeDirs(includeDirsForExtension, config);
												end
												-- Add extension-specific include directories.
												-- ndk-build doesn't support per-file include directories, but C/C++/GAS/YASM and RenderScript need to be distinguished from each other.
												androidndk.addIncludeDirs(includeDirsForExtension, fileConfig);

												-- Gather compiler flags.
												local compilerFlagsVariable = androidndk.compilerFlagsVariables[sourceExtension];
												if compilerFlagsVariable ~= nil then
													local compilerFlagsForExtension = compilerFlags[compilerFlagsVariable];
													if compilerFlagsForExtension == nil then
														compilerFlagsForExtension = {};
														compilerFlags[compilerFlagsVariable] = compilerFlagsForExtension;
													end
													-- Add non-extension-specific compiler options from the project configuration if hasn't done already.
													-- It's fine not to do filtering if the project, for example, contains only C or C++ files, but no assembly.
													if not configCompilerFlagsAdded[compilerFlagsVariable] then
														configCompilerFlagsAdded[compilerFlagsVariable] = true;
														androidndk.addCompilerFlagsForExtension(compilerFlagsForExtension, sourceExtension, config, temporaryVariables);
													end
													-- Add extension-specific compiler options.
													-- ndk-build doesn't support per-file flags, but C, C++, GAS and YASM need to be distinguished from each other.
													-- Doing this after the project-level flags so per-extension flags can override them (provide a -fno- for an -f or the opposite).
													androidndk.addCompilerFlagsForExtension(compilerFlagsForExtension, sourceExtension, fileConfig, temporaryVariables);
												end
											end
										end
									end
								end
							end
						end
					end
				end
			end
		end
	});

	-- Get the extension, or nil if not available, for the special case of precreated project files.
	-- These can be external Android.mk files and prebuilt libraries.
	-- To use one, it must be the only source file in the project.
	local precreatedExtension = nil;
	if #sourcePrecreatedFiles == 1 and not (#sourceFiles > 0 or #sourceFilesYasmConditional > 0) then
		precreatedExtension = path.getextension(sourcePrecreatedFiles[1]);
	end

	if precreatedExtension ~= nil then
		-- Check the special case of an external Android.mk file.
		-- Using Android.mk files not generated by Premake is allowed as long as:
		-- * Only one project is specified in it.
		-- * The project name, after all escaping and reference expansion, is the same as LOCAL_MODULE in it.
		-- * The kind matches the one used in it.
		if precreatedExtension == ".mk" then
			p.w("include %s", androidndk.preventWhitespaceTrimming(sourcePrecreatedFiles[1]));
			return;
		end

		-- Check the special case of a prebuilt library.
		local prebuiltKind = androidndk.prebuiltKinds[config.kind];
		if prebuiltKind ~= nil and precreatedExtension == prebuiltKind.extension then
			-- Backslash escaping is not supported for prebuilt library paths on Windows.
			androidndk.assignToVariablePostEsc("LOCAL_SRC_FILES", sourcePrecreatedFiles[1], false);
			p.w("include $(%s)", prebuiltKind.script);
			return;
		end
	end

	-- Warn if there are any external Android.mk files or prebuilt libraries in the projects, but they aren't used for some reason.
	-- It may be a mistake, the user might have wanted to use one, but has possibly configured the filters so that other files are still included.
	for i, file in ipairs(sourcePrecreatedFiles) do
		p.warn(
			"Workspace '%s' project '%s' configuration '%s' contains an external Android.mk or a prebuilt library '%s' among its source files, " ..
			"but it's not the only source file in the project, or it doesn't match the kind of the project",
			config.workspace.name, config.project.name, config.name, file);
	end

	-- Some variables may have values that are relevant only to a subset of the ABIs.
	-- Examples are LOCAL_ARM_MODE, LOCAL_ARM_NEON, .arm/.neon/.arm.neon and .asm in LOCAL_SRC_FILES.
	-- The general rule here is that most of the details of handling those are left to ndk-build itself.
	-- This is done to avoid introducing additional interference and constraints, as well as to simplify the code.
	-- ABI conditionals are added only when not having them would cause errors or warnings (like x86-specific CFLAGS on ARM).
	-- If the default behavior of ndk-build needs to be overriden, the project should explicitly use the needed filters.

	-- Gather C++ settings if the precompiled header is used, from the project and, if available, the file.
	-- The precompiled header is always compiled as C++ by ndk-build.
	-- Treat it as potentially encountering a C++ file for the first time, so it's compiled with the needed include directories and flags.
	-- Ignoring ExcludeFromBuild as it doesn't have effect on pchheader in other Premake actions.
	if pch ~= nil then
		if not configIncludeDirsAdded["C_INCLUDES"] then
			configIncludeDirsAdded["C_INCLUDES"] = true;
			local cIncludes = includeDirs["C_INCLUDES"];
			if cIncludes == nil then
				cIncludes = {};
				includeDirs["C_INCLUDES"] = cIncludes;
			end
			androidndk.addIncludeDirs(cIncludes, config);
			if pchFileConfig ~= nil then
				androidndk.addIncludeDirs(cIncludes, pchFileConfig);
			end
		end
		if not configCompilerFlagsAdded["CPPFLAGS"] then
			configCompilerFlagsAdded["CPPFLAGS"] = true;
			local cppFlags = compilerFlags["CPPFLAGS"];
			if cppFlags == nil then
				cppFlags = {};
				compilerFlags["CPPFLAGS"] = cppFlags;
			end
			androidndk.addCompilerFlagsForExtension(cppFlags, androidndk.cppExtensions[1], config, temporaryVariables);
			if pchFileConfig ~= nil then
				androidndk.addCompilerFlagsForExtension(cppFlags, androidndk.cppExtensions[1], pchFileConfig, temporaryVariables);
			end
		end
	end

	-- If the LinkTimeOptimization flag is enabled, apply the LTO type requested by the project explicitly via `buildoptions`, or the default "-flto".
	-- Also verify link-time optimization type consistency.
	local fltoCOverride = nil;
	if compilerFlags["CONLYFLAGS"] ~= nil then
		fltoCOverride = compilerFlags["CONLYFLAGS"].flto;
	end
	local fltoCppOverride = nil;
	if compilerFlags["CPPFLAGS"] ~= nil then
		fltoCppOverride = compilerFlags["CPPFLAGS"].flto;
	end
	-- This must not be used by the link options - they should be only verified against it.
	-- Static library analysis doesn't scan `buildoptions`, only `linkoptions`.
	local fltoBuildOption = fltoCppOverride or fltoCOverride or "-flto";
	if fltoCOverride ~= nil and fltoCOverride ~= fltoBuildOption then
		p.warn(
			"Workspace '%s' project '%s' configuration '%s' uses LTO type '%s' for C, while it uses '%s' for another language",
			config.workspace.name, config.project.name, config.name, fltoCOverride, fltoBuildOption);
	end
	if fltoCppOverride ~= nil and fltoCppOverride ~= fltoBuildOption then
		p.warn(
			"Workspace '%s' project '%s' configuration '%s' uses LTO type '%s' for C++, while it uses '%s' for another language",
			config.workspace.name, config.project.name, config.name, fltoCppOverride, fltoBuildOption);
	end
	if config.flags.LinkTimeOptimization then
		if fltoCOverride == nil then
			if compilerFlags["CONLYFLAGS"] == nil then
				compilerFlags["CONLYFLAGS"] = {}
			end
			if compilerFlags["CONLYFLAGS"].buildoptions == nil then
				compilerFlags["CONLYFLAGS"].buildoptions = {}
			end
			table.insertkeyed(compilerFlags["CONLYFLAGS"].buildoptions, fltoBuildOption);
		end
		if fltoCppOverride == nil then
			if compilerFlags["CPPFLAGS"] == nil then
				compilerFlags["CPPFLAGS"] = {}
			end
			if compilerFlags["CPPFLAGS"].buildoptions == nil then
				compilerFlags["CPPFLAGS"].buildoptions = {}
			end
			table.insertkeyed(compilerFlags["CPPFLAGS"].buildoptions, fltoBuildOption);
		end
	end

	-- Gather linker options (LDFLAGS and LDLIBS) from the module and its static library dependencies.
	-- Importing manually instead of using LOCAL_EXPORT_LDFLAGS/LDLIBS so there's no transitivity across shared libraries.
	-- This is consistent with the behavior of Visual Studio - only static libraries export their dependencies.
	-- Also it keeps syslibdirs of all static library dependencies last, after all local library directories.
	-- ndk-build puts imported LDFLAGS first, but imported LDLIBS last.
	-- For -u, which is usually passed via LDFLAGS, the order of local vs. imported options doesn't matter, however.
	-- all_depends in ndk-build is generated via a breadth-first walk of the dependency graph.
	local isLinked = config.kind == p.CONSOLEAPP or config.kind == p.SHAREDLIB;
	local ldFlags = {};
	local ldLibs = {};
	if isLinked then
		local ldFlagsUndefined = {};
		local ldFlagsLocal = {};
		local ldLibsDirFlags = {};
		local ldLibsSysDirFlags = {};
		local ldLibsLibFlags = {};
		local ldLinkTimeOptimization = config.flags.LinkTimeOptimization;
		local ldFlagsExplicitFlto = nil;
		-- Start recursion from the current project config.
		-- It will also result in local LDLIBS parts being added before the imports.
		local ldDependencies = { config, [config.project.name] = config };
		local ldDependencyIndex = 1;
		while ldDependencyIndex <= #ldDependencies do
			-- Gather -u LDFLAGS as well as LDLIBS parts for the project currently being processed.
			-- -u may be used to keep certain exports from static libraries in shared libraries, in a way more granular than whole static libraries.
			-- It is used, for example, to prevent stripping ANativeActivity_onCreate from the Android Native App Glue.
			local ldDependency = ldDependencies[ldDependencyIndex];
			local ldDependencyExplicitFlto =
				androidndk.addSingleConfigLinkerFlags(
					ldDependency, ldFlagsUndefined, nil, ldLibsDirFlags, ldLibsSysDirFlags, ldLibsLibFlags, temporaryVariables);
			-- The last -flto has the highest priority.
			-- However, -flto for the project itself is actually added after all dependencies here, not alongside them.
			if ldDependency ~= config and ldDependencyExplicitFlto ~= nil then
				if ldFlagsExplicitFlto ~= nil and ldFlagsExplicitFlto ~= ldDependencyExplicitFlto then
					p.warn(
						"Workspace '%s' project '%s' configuration '%s' has mismatching -flto link options " ..
						"among its static library dependencies ('%s' in project '%s' and '%s' in another project)",
						config.workspace.name, config.project.name, config.name,
						ldDependencyExplicitFlto, ldDependency.project.name, ldFlagsExplicitFlto);
				end
				ldFlagsExplicitFlto = ldDependencyExplicitFlto;
			end
			for i, ldDependencySibling in ipairs(p.config.getlinks(ldDependency, "siblings", "object")) do
				-- Only gather -u exports and as LDLIBS from static libraries, as shared libraries have already been linked as a complete object.
				-- Also check if not already handled, including to prevent circular dependencies.
				if ldDependencySibling.kind == p.STATICLIB and ldDependencies[ldDependencySibling.project.name] == nil then
					if androidndk.isProjectSupported(ldDependencySibling.project, false) then
						if androidndk.isConfigSupported(ldDependencySibling, false) then
							table.insert(ldDependencies, ldDependencySibling);
							ldDependencies[ldDependencySibling.project.name] = ldDependencySibling;
							if ldDependencySibling.flags.LinkTimeOptimization then
								ldLinkTimeOptimization = true;
							end
						end
					end
				end
			end
			ldDependencyIndex = ldDependencyIndex + 1;
		end
		-- Merge LDLIBS parts.
		local ldLibsFlagsTables = { ldLibsDirFlags, ldLibsSysDirFlags, ldLibsLibFlags };
		for i, ldLibsFlags in ipairs(ldLibsFlagsTables) do
			for i2, ldLibsFlag in ipairs(ldLibsFlags) do
				table.insertkeyed(ldLibs, ldLibsFlag);
			end
		end
		-- Gather local LDFLAGS other than -u after the imports.
		-- For LDFLAGS, the order mostly shouldn't matter though.
		-- Doing this just in a way consistent with how ndk-build itself gathers exported LDLIBS.
		local ldLocalFlagsExplicitFlto = androidndk.addSingleConfigLinkerFlags(config, nil, ldFlagsLocal, nil, nil, nil, temporaryVariables);
		if ldLocalFlagsExplicitFlto ~= nil then
			-- The last -flto has the highest priority.
			if ldFlagsExplicitFlto ~= nil and ldFlagsExplicitFlto ~= ldLocalFlagsExplicitFlto then
				p.warn(
					"Workspace '%s' project '%s' configuration '%s' has a -flto link option '%s' " ..
					"that doesn't match its value used by static library dependencies '%s'",
					config.workspace.name, config.project.name, config.name,
					ldLocalFlagsExplicitFlto, ldFlagsExplicitFlto);
			end
			ldFlagsExplicitFlto = ldLocalFlagsExplicitFlto;
		end
		if ldFlagsExplicitFlto ~= nil then
			ldLinkTimeOptimization = true;
		end
		-- If the project itself, or any of its static libraries, is compiled with LTO, link with LTO.
		-- Also, if the project or any of its static libraries has an explicit -flto option (possibly with a non-default type), use it instead.
		local ldFlagsFlto = ldFlagsExplicitFlto or "-flto";
		-- Checking if the build -flto is not nil because the project may, for instance, only link against static libraries with LTO.
		if fltoBuildOption ~= nil and fltoBuildOption ~= ldFlagsFlto then
			if ldFlagsFlto ~= nil then
				p.warn(
					"Workspace '%s' project '%s' configuration '%s' uses a -flto build option '%s' " ..
					"that differs from the value '%s' that will be used by the linker",
					config.workspace.name, config.project.name, config.name, fltoBuildOption, ldFlagsFlto);
			else
				p.warn(
					"Workspace '%s' project '%s' configuration '%s' uses a -flto build option '%s', " ..
					"but doesn't have the LinkTimeOptimization flag enabled or an -flto in its link options",
					config.workspace.name, config.project.name, config.name, fltoBuildOption);
			end
		end
		if ldLinkTimeOptimization then
			table.insertkeyed(ldFlags, ldFlagsFlto);
		end
		-- Merge LDFLAGS parts.
		local ldFlagsTables = { ldFlagsUndefined, ldFlagsLocal };
		for i, ldFlagsTable in ipairs(ldFlagsTables) do
			for i2, ldFlag in ipairs(ldFlagsTable) do
				table.insertkeyed(ldFlags, ldFlag);
			end
		end
	end

	-- Gather module dependencies for the current build configuration and platform.
	local sharedLibraries = {};
	local staticLibraries = {};
	local wholeStaticLibraries = {};
	for i, siblingLinkProjectConfig in ipairs(p.config.getlinks(config, "siblings", "object")) do
		if androidndk.isProjectSupported(siblingLinkProjectConfig.project, false) then
			if androidndk.isConfigSupported(siblingLinkProjectConfig, false) then
				local siblingLinksTable = nil;
				if siblingLinkProjectConfig.kind == p.SHAREDLIB then
					siblingLinksTable = sharedLibraries;
				elseif siblingLinkProjectConfig.kind == p.STATICLIB then
					if siblingLinkProjectConfig.wholelib == true or config.wholelibs[siblingLinkProjectConfig.project.name] ~= nil then
						siblingLinksTable = wholeStaticLibraries;
					else
						siblingLinksTable = staticLibraries;
					end
				end
				if siblingLinksTable ~= nil then
					table.insert(siblingLinksTable, siblingLinkProjectConfig.project.name);
				end
			end
		end
	end

	-- Assign the values to the variables.

	-- Write assignments to referenced intermediate variables.
	for i, temporaryVariable in ipairs(temporaryVariables) do
		androidndk.assignToVariablePostEsc(androidndk.temporaryVariablePrefix .. i, temporaryVariable, false);
	end

	-- LOCAL_ALLOW_UNDEFINED_SYMBOLS
	if isLinked and config.undefinedsymbols == true then
		p.w("LOCAL_ALLOW_UNDEFINED_SYMBOLS := true");
	end

	-- LOCAL_ASFLAGS
	androidndk.writeProjectCompilerFlags(compilerFlags, "ASFLAGS", true);

	-- LOCAL_ASMFLAGS
	androidndk.writeProjectCompilerFlags(compilerFlags, "ASMFLAGS", true);

	-- LOCAL_ARM_MODE
	-- NDK uses T32 by default, and always switches to A32 for debug builds, but it's handled implicitly in it.
	if configUsesA32 then
		p.w("LOCAL_ARM_MODE := arm");
	end

	-- LOCAL_ARM_NEON
	-- On NDK r21, NEON is enabled by default.
	-- Since that wasn't the case on older versions, both enabling and disabling it explicitly anyway.
	p.w("LOCAL_ARM_NEON := %s", iif(configUsesNeon, "true", "false"));

	-- LOCAL_CONLYFLAGS
	-- Potentially will be appending ISA and vector extensions, post-process later.
	local cOnlyFlagsNeedPostProcess = androidndk.writeProjectCompilerFlags(compilerFlags, "CONLYFLAGS", false);

	-- LOCAL_CPPFLAGS
	-- Potentially will be appending ISA and vector extensions, post-process later.
	local cppFlagsNeedPostProcess = androidndk.writeProjectCompilerFlags(compilerFlags, "CPPFLAGS", false);

	-- After writing LOCAL_CONLYFLAGS and LOCAL_CPPFLAGS, add ABI-specific C and C++ flags (not using LOCAL_CFLAGS at all).
	local cFlagsAbis;
	if configAbi == androidndk.ABI_ALL then
		cFlagsAbis = androidndk.knownAbis;
	else
		cFlagsAbis = { configAbi };
	end
	local abiCFlagsConditionalOpen = false;
	for i, cFlagsAbi in ipairs(cFlagsAbis) do
		local abiCFlags = {};
		-- vectorextensions
		if config.vectorextensions ~= nil then
			local abiVectorExtensions = androidndk.abiVectorExtensions[cFlagsAbi];
			if abiVectorExtensions ~= nil then
				local abiConfigVectorExtensions = abiVectorExtensions[config.vectorextensions];
				if abiConfigVectorExtensions ~= nil then
					table.insertkeyed(abiCFlags, p.esc(abiConfigVectorExtensions));
				end
			end
		end
		-- isaextensions
		local abiIsaExtensions = androidndk.abiIsaExtensions[cFlagsAbi];
		if abiIsaExtensions ~= nil then
			for i2, extension in ipairs(config.isaextensions) do
				local abiIsaExtension = abiIsaExtensions[extension];
				if abiIsaExtension ~= nil then
					table.insertkeyed(abiCFlags, p.esc(abiIsaExtension));
				end
			end
		end
		-- Write the conditional and the extensions.
		if #abiCFlags > 0 then
			if configAbi == androidndk.ABI_ALL then
				p.push("%sifeq ($(TARGET_ARCH_ABI),%s)", androidndk.getCaseElse(abiCFlagsConditionalOpen), cFlagsAbi);
				abiCFlagsConditionalOpen = true;
			end
			-- Safe to += even if no other CONLYFLAGS and CPPFLAGS were specified, set to an empty value by CLEAR_VARS.
			if androidndk.assignToVariablePostEsc("LOCAL_CONLYFLAGS", abiCFlags, true, androidndk.shellEscapePostQuotesChecker, "+=") then
				cOnlyFlagsNeedPostProcess = true;
			end
			if androidndk.assignToVariablePostEsc("LOCAL_CPPFLAGS", abiCFlags, true, androidndk.shellEscapePostQuotesChecker, "+=") then
				cppFlagsNeedPostProcess = true;
			end
			if configAbi == androidndk.ABI_ALL then
				p.pop();
			end
		end
	end
	if abiCFlagsConditionalOpen then
		assert(configAbi == androidndk.ABI_ALL, "Can have ABI conditionals for ABI-specific C flags only for ABI-agnostic configurations");
		p.w("endif");
	end

	if cOnlyFlagsNeedPostProcess then
		androidndk.writePostProcessCall("LOCAL_CONLYFLAGS", androidndk.shellEscapePostQuotesMakeCall);
	end
	if cppFlagsNeedPostProcess then
		androidndk.writePostProcessCall("LOCAL_CPPFLAGS", androidndk.shellEscapePostQuotesMakeCall);
	end

	-- LOCAL_CPP_FEATURES
	-- For Clang, Premake core modules check if these are not "Off" (rather than if they are "On").
	local cppFeatures = {};
	if config.exceptionhandling ~= p.OFF then
		table.insert(cppFeatures, "exceptions");
	end
	if config.rtti ~= p.OFF then
		table.insert(cppFeatures, "rtti");
	end
	if #cppFeatures > 0 then
		androidndk.assignToVariablePostEsc("LOCAL_CPP_FEATURES", cppFeatures, false);
	end

	-- LOCAL_C_INCLUDES
	androidndk.writeProjectIncludeDirs(includeDirs, "C_INCLUDES", true);

	-- LOCAL_DISABLE_FATAL_LINKER_WARNINGS
	-- Different than the Android.mk default (fatal by default), but for compatibility with other Premake actions.
	if isLinked and not config.flags.FatalLinkWarnings then
		p.w("LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true");
	end

	-- LOCAL_DISABLE_FORMAT_STRING_CHECKS
	-- Enabling format string checks by default (if nil).
	if config.formatstringchecks == false then
		p.w("LOCAL_DISABLE_FORMAT_STRING_CHECKS := true");
	end

	-- LOCAL_LDFLAGS
	if isLinked then
		if androidndk.assignToVariablePostEsc("LOCAL_LDFLAGS", ldFlags, true, androidndk.shellEscapePostQuotesChecker) then
			androidndk.writePostProcessCall("LOCAL_LDFLAGS", androidndk.shellEscapePostQuotesMakeCall);
		end
	end

	-- LOCAL_LDLIBS
	if isLinked then
		if androidndk.assignToVariablePostEsc("LOCAL_LDLIBS", ldLibs, true, androidndk.shellEscapePostQuotesChecker) then
			androidndk.writePostProcessCall("LOCAL_LDLIBS", androidndk.shellEscapePostQuotesMakeCall);
		end
	end

	-- LOCAL_MODULE_FILENAME
	-- Allowed directly on Linux: !+,-.=@[]^_{}~
	-- Allowed if \-escaped on Linux: "\`
	-- Allowed if \-escaped on Linux, misleadingly displayed with \ in the terminal: &'()*<>?
	-- : is allowed if escaped on Linux (displayed with \), disallowed on Windows (drive letter separator - only the name, not a path, in this variable).
	-- Disallowed: whitespaces, #$%/;|
	local moduleFileName = p.esc(config.buildtarget.prefix) .. p.esc(config.buildtarget.basename) .. p.esc(config.buildtarget.suffix);
	if androidndk.staticallyHasPatternPostEsc(moduleFileName, "[%s#%$%%/;|]") then
		-- % needs to be escaped as %% in printf format strings.
		p.warn(
			"Using the default build target name for workspace '%s' project '%s' configuration '%s' " ..
			"instead of '%s' (displayed as escaped) with whitespaces or disallowed characters #$%%/:;|",
			config.workspace.name, config.project.name, config.name, moduleFileName);
	else
		if androidndk.assignToVariablePostEsc("LOCAL_MODULE_FILENAME", moduleFileName, false, androidndk.shellEscapeModuleFileNameChecker) then
			androidndk.writePostProcessCall("LOCAL_MODULE_FILENAME", androidndk.shellEscapeModuleFileNameMakeCall);
		end
	end

	-- LOCAL_PCH
	if pch ~= nil then
		if androidndk.assignToVariablePostEsc("LOCAL_PCH", pch, false, androidndk.shellEscapeChecker) then
			androidndk.writePostProcessCall("LOCAL_PCH", androidndk.shellEscapeMakeCall);
		end
	end

	-- LOCAL_RENDERSCRIPT_COMPATIBILITY
	if config.renderscriptcompatibility == true then
		p.w("LOCAL_RENDERSCRIPT_COMPATIBILITY := true");
	end

	-- LOCAL_RENDERSCRIPT_FLAGS
	androidndk.writeProjectCompilerFlags(compilerFlags, "RENDERSCRIPT_FLAGS", true);

	-- LOCAL_RENDERSCRIPT_INCLUDES or LOCAL_RENDERSCRIPT_INCLUDES_OVERRIDE
	androidndk.writeProjectIncludeDirs(includeDirs, renderScriptIncludeDirsVariable, true);

	-- LOCAL_SHARED_LIBRARIES
	-- See LOCAL_MODULE for character rules.
	if androidndk.assignToVariablePostEsc("LOCAL_SHARED_LIBRARIES", p.esc(sharedLibraries), true, androidndk.shellEscapeChecker) then
		androidndk.writePostProcessCall("LOCAL_SHARED_LIBRARIES", androidndk.shellEscapeMakeCall);
	end

	-- LOCAL_SHORT_COMMANDS
	if config.shortcommands == true then
		p.w("LOCAL_SHORT_COMMANDS := true");
	end

	-- LOCAL_SRC_FILES
	-- See the validation of source files for information about disallowed characters.
	local sourceFilesNeedPostProcess = false;
	if androidndk.assignToVariablePostEsc("LOCAL_SRC_FILES", sourceFiles, true, androidndk.shellEscapeSrcFilesChecker) then
		sourceFilesNeedPostProcess = true;
	end
	-- Only add .asm files for x86 and x86_64 as otherwise the NDK will be throwing warnings.
	-- Single-ABI configurations are already handled while gathering the source file nodes.
	-- Write the assignment for multi-ABI configurations.
	if #sourceFilesYasmConditional > 0 then
		p.push("ifneq ($(filter x86 x86_64,$(TARGET_ARCH_ABI)),)");
		if androidndk.assignToVariablePostEsc("LOCAL_SRC_FILES", sourceFilesYasmConditional, true, androidndk.shellEscapeSrcFilesChecker, "+=") then
			sourceFilesNeedPostProcess = true;
		end
		p.pop("endif");
	end
	if sourceFilesNeedPostProcess then
		androidndk.writePostProcessCall("LOCAL_SRC_FILES", androidndk.shellEscapeSrcFilesMakeCall);
	end

	-- LOCAL_STATIC_LIBRARIES
	-- See LOCAL_MODULE for character rules.
	if androidndk.assignToVariablePostEsc("LOCAL_STATIC_LIBRARIES", p.esc(staticLibraries), true, androidndk.shellEscapeChecker) then
		androidndk.writePostProcessCall("LOCAL_STATIC_LIBRARIES", androidndk.shellEscapeMakeCall);
	end

	-- LOCAL_THIN_ARCHIVE
	if config.kind == p.STATICLIB and config.thinarchive == true then
		p.w("LOCAL_THIN_ARCHIVE := true");
	end

	-- LOCAL_WHOLE_STATIC_LIBRARIES
	-- See LOCAL_MODULE for character rules.
	if androidndk.assignToVariablePostEsc("LOCAL_WHOLE_STATIC_LIBRARIES", p.esc(wholeStaticLibraries), true, androidndk.shellEscapeChecker) then
		androidndk.writePostProcessCall("LOCAL_WHOLE_STATIC_LIBRARIES", androidndk.shellEscapeMakeCall);
	end

	-- Invoke the build script for the specified kind.
	local kindScript = androidndk.kindScripts[config.kind];
	assert(kindScript ~= nil, "Configurations with invalid kinds must be skipped in isConfigSupported");
	p.w("include $(%s)", kindScript);
end

function androidndk.onProject(project)
	if not androidndk.isProjectSupported(project, true) then
		return;
	end
	androidndk.setupGeneration();
	p.generate(project, ".prj.Android.mk", function(project)
		-- Must be synchronized with getEscapedProjectRelativePath.
		-- Using the Android.mk directory (location), not the base directory, as it's less likely to contain header files.
		-- There's undesirable behavior in NDK regarding the order of include directories.
		-- LOCAL_PATH is always implicitly an include directory, and the -I for it is passed after the STL include directories.
		-- That causes #include_next in C standard library headers to locate app headers with the same in LOCAL_PATH.
		-- https://github.com/android/ndk/issues/1582
		p.w("LOCAL_PATH := $(call my-dir)");
		p.w("include $(CLEAR_VARS)");
		-- Workaround for LOCAL_RENDERSCRIPT_COMPATIBILITY not being cleared in NDK r23 as it's not listed in modules-LOCALS.
		-- Clearing similar to clear-vars as of NDK r23, by defining as empty, not via `undefine`.
		p.w("LOCAL_RENDERSCRIPT_COMPATIBILITY :=");
		-- Project name already verified by androidndk.isProjectSupported.
		if androidndk.assignToVariablePostEsc("LOCAL_MODULE", p.esc(project.name), false, androidndk.shellEscapeChecker) then
			androidndk.writePostProcessCall("LOCAL_MODULE", androidndk.shellEscapeMakeCall);
		end
		-- Specify all extensions assumed to be C++ and RenderScript by this module.
		-- This allows for using extensions different than the default in this module if needed.
		-- Additionally, it ensures forward compatibility if the defaults in ndk-build are changed.
		androidndk.assignToVariablePostEsc("LOCAL_CPP_EXTENSION", table.concat(androidndk.cppExtensions, " "), false);
		androidndk.assignToVariablePostEsc("LOCAL_RS_EXTENSION", table.concat(androidndk.rsExtensions, " "), false);
		-- Gather valid configurations for each ABI.
		-- ABI-agnostic configurations are checked last.
		-- This allows both ABI specializations and ABI-agnostic fallbacks to be specified for building at the same time.
		-- Without this, the ABI-agnostic fallback would've been chosen over specializations depending on the order of the platforms table.
		local abisConfigs = {};
		for config in p.project.eachconfig(project) do
			if androidndk.isConfigSupported(config, true) then
				local configAbi = androidndk.getConfigAbi(config);
				if abisConfigs[configAbi] == nil then
					abisConfigs[configAbi] = { abi = configAbi, configs = {} };
					-- The ABI-agnostic configurations will be used as fallbacks when no ABI specialization is available.
					-- So, they need to be generated last.
					if configAbi ~= androidndk.ABI_ALL then
						table.insert(abisConfigs, abisConfigs[configAbi]);
					end
				end
				table.insert(abisConfigs[configAbi].configs, config);
			end
		end
		if abisConfigs[androidndk.ABI_ALL] ~= nil then
			table.insert(abisConfigs, abisConfigs[androidndk.ABI_ALL]);
		end
		local anyConfigWritten = false;
		for i, abiConfigs in ipairs(abisConfigs) do
			for i2, abiConfig in ipairs(abiConfigs.configs) do
				local configCondition = androidndk.getConfigCondition(abiConfig.buildcfg, abiConfig.platform, abiConfigs.abi);
				p.push("%s%s", androidndk.getCaseElse(anyConfigWritten), configCondition);
				androidndk.generateProjectConfig(abiConfig);
				p.pop();
				anyConfigWritten = true;
			end
		end
		if anyConfigWritten then
			p.w("endif");
		end
	end);
end
