-- premake-androidndk - a multi-ABI, multi-language ndk-build Android.mk generator for Premake.
-- Originally written by Vitaliy <Triang3l> Kuzmin.
-- See README.md for detailed usage and design information.
-- Available under the Unlicense (see UNLICENSE.txt) or the BSD 3-Clause "New" or "Revised" License (see LICENSE.txt).

local p = premake;
p.modules.androidndk = {};
local androidndk = p.modules.androidndk;
androidndk._VERSION = "1.0.0";

include("androidndk_project.lua");
include("androidndk_workspace.lua");

include("_preload.lua");

-- Inserts one or multiple values into a table.
-- Useful for inserting compiler flags from built-in Premake toolsets.
function androidndk.insertKeyedFlat(tbl, value)
	-- Skip if the value is nil, for instance, to quickly ignore irrelevant flags or values of settings without a mapping.
	if value == nil then
		return;
	end
	if type(value) == "table" then
		for i, element in ipairs(value) do
			androidndk.insertKeyedFlat(tbl, element);
		end
		return;
	end
	if tbl[value] ~= nil then
		return;
	end
	table.insert(tbl, value);
	tbl[value] = value;
end

-- Rules regarding special characters in the input and how they're handled in this module (as of NDK r23, checked with `$(warning "$(VARIABLE)")`):
-- * Whitespaces (tab, vertical tab, form feed, space) - defining the word "whitespace" as all of these, unlike just "space":
--   * Horizontal tab being the first on a line defines a recipe.
--   * Otherwise, all whitespace characters behave like whitespaces, at least in the syntax of GNU make itself.
--   * Trimming behavior in various contexts relevant to Android.mk:
--     * All sides of a variable assignment - left-hand, the operator itself, right-hand - have leading whitespaces trimmed.
--     * In the right-hand side of a variable assignment, each line (separated with a \-escaped newline) is treated as a list element, like a complete token.
--       Any amount (including zero) of whitespaces or escaped newlines between two non-empty elements is collapsed into a single " " space.
--       However, if the last non-whitespace character in an element is $ (not $$, but $ alone), no space is inserted, they're just removed (including the $).
--       This rule, however, is directly applicable only to inner newline separators, not the beginning or the end of the whole right-hand side.
--       Whitespaces and newlines before the first non-empty element are trimmed (as leading whitespaces in general).
--       Behavior for the last element is less consistent.
--       If the last non-empty element is followed only by whitespaces, all those trailing whitespaces are preserved as their original encoding.
--       If there's a \-escaped newline after the last non-empty element, however, all trailing whitespaces and newlines are collapsed into one " " space.
--       Within the boundaries of one list element, however, all original whitespaces are preserved.
--     * Function call argument lists (as a whole, not individual arguments) have leading whitespaces trimmed.
--   * $() can be prepended or appended to include leading or trailing whitespaces in an element or the first function argument.
--   * Resolution:
--     * Pass through directly.
--     * Single-line variable generation:
--       * Preserve project-provided leading whitespaces for the whole value (or the first table element) using $().
--     * Multiline list variable generation:
--       * Preserve project-provided leading and trailing whitespaces for each table element using $(), though not necessary for the last.
--       * Both "\" and " \" are fine for separating table elements.
--         However, using " \" is consistent with the general recipe line splitting rules of GNU make for joining with a space.
-- * Newline characters (carriage return, line feed):
--   * Start a new statement.
--   * Can be escaped with a backslash, but then the newline itself may be trimmed according to the whitespace trimming rules.
--   * True newlines can be kept in variable declarations using define/endef.
--   * Resolution:
--     * Replace unconditionally with spaces.
--     * Escaping handled separately.
--     * Not using define/endef until a real use in ndk-build scripts is found.
-- * Backslash:
--   * If the last character before a newline, behaves as a line split, trimmed according to the whitespace trimming rules.
--   * Escapes the number sign which starts a comment.
--   * In other cases, passed as a raw character.
--   * Resolution:
--     * Pass through directly.
--     * If the last character on a line and provided by the project, append $().
-- * Dollar sign:
--   * A single dollar sign is a prefix for a variable or a function reference.
--   * $(name arguments) and ${name arguments} are the regular syntax.
--   * If neither () nor {} are used, one character immediately following the $ is used as the variable name.
--   * $ alone directly in the end of a variable assignment is treated as a raw $ character.
--   * The effect of a trailing $ on variable assignments split into multiple lines is described in the section about whitespaces.
--   * $$ results in a raw $ character.
--   * Resolution:
--     * Pass through directly to allow using environment variables and built-in variables like TARGET_ARCH_ABI in scripts, as well as functions.
--     * Prevent unclosed variable and function references with an undefined, but safe result.
--       The easiest way is to close them - doesn't require insertion into the middle - with a special case for the trailing $ (convert to $$).
-- * Number sign:
--   * Starts a comment.
--   * Escaped with a backslash for passing as raw data, but the backslash itself may be escaped as well.
--     * Backslashes preceding a # are treated as n/2 backslashes ((n-1)/2 if there is an odd number of them) in other cases.
--     * An even number of backslashes before the # in the original file causes the comment not to be escaped.
--   * Resolution:
--     * Escape with a single backslash and a terminator to prevent dependence on the number of backslashes, as $()\#.
--     * This makes concatenation of a string ending with \ and one starting with an escaped # safe.

androidndk.commentEscapeString = "$()\\#";
androidndk.commentUnescapePattern = string.escapepattern(androidndk.commentEscapeString);

androidndk.whitespacesNonNewline = {
	["\t"] = "\t",
	["\v"] = "\v",
	["\f"] = "\f",
	[" "] = " ",
};

-- Due to escaping of #, this function can't be called again on its result.
function androidndk.esc(value)
	value = string.gsub(value, "#", androidndk.commentEscapeString);
	-- Replace newlines with safer spaces.
	value = string.gsub(value, "\r\n", " ");
	value = string.gsub(value, "\n", " ");
	value = string.gsub(value, "\r", " ");
	-- Make sure there are no unclosed variable and function references.
	-- Close $() and ${} with a bracket, and escape the final $.
	-- As a result, all references will be closed and balanced.
	local unclosedReferenceTerminators = {};
	local afterReferenceCharacter = false;
	-- Need a while loop as the for loop counter can't be modified from the body.
	local i = 1;
	while i <= string.len(value) do
		local character = string.sub(value, i, i);
		if character == "\\" and string.sub(value, i + 1, i + 1) == "#" then
			-- Escaped comment character.
			i = i + 1;
			character = "#";
		end
		if afterReferenceCharacter then
			-- The character after the $.
			-- Options: $ (escaped raw $), an opening bracket (opening a reference), any other character (single-character reference).
			if character == "(" then
				table.insert(unclosedReferenceTerminators, ")");
			elseif character == "{" then
				table.insert(unclosedReferenceTerminators, "}");
			end
			afterReferenceCharacter = false;
		else
			-- Not the character after the $.
			-- Options: $, a reference-closing bracket, any other raw character.
			if character == "$" then
				afterReferenceCharacter = true;
			elseif #unclosedReferenceTerminators > 0 and character == unclosedReferenceTerminators[#unclosedReferenceTerminators] then
				unclosedReferenceTerminators[#unclosedReferenceTerminators] = nil;
			end
		end
		i = i + 1;
	end
	local referencesClosed = { value };
	-- Escape the incomplete single-character reference as a raw $.
	if afterReferenceCharacter then
		table.insert(referencesClosed, "$");
	end
	-- Close the unclosed references.
	for i2 = 1, #unclosedReferenceTerminators do
		table.insert(referencesClosed, unclosedReferenceTerminators[#unclosedReferenceTerminators - i + 1]);
	end
	return table.concat(referencesClosed);
end

function androidndk.setupGeneration()
	-- The tab character is the recipe line prefix in makefiles.
	p.indent("  ");
	p.escaper(androidndk.esc);
	p.eol("\n");
end

-- Whether the string contains GNU make variable or function references.
-- p.esc should be done prior to this.
-- Empty references, that are $() or ${}, are not treated as references, merely as delimiters.
-- $() is used in comment sign escaping, for example.
function androidndk.hasNonEmptyMakeReferencesPostEsc(value)
	-- For strictness and simplicity, the lone trailing $ is treated as a reference too (can't be a result of p.esc anyway).
	local i = 0;
	while true do
		i = string.find(value, "%$", i + 1);
		if i == nil then
			return false;
		end
		if string.sub(value, i, i + 1) == "$$" then
			i = i + 1;
		else
			local potentiallyEmptyReference = string.sub(value, i, i + 2);
			if potentiallyEmptyReference == "$()" or potentiallyEmptyReference == "${}" then
				i = i + 2;
			else
				return true;
			end
		end
	end
end

-- Removes variable and function references and reverts p.esc's escaping of # and $ from a GNU make variable value (but not multiline).
-- Useful for coarse validation of string contents, whether there are unsupported characters.
-- What the references expand to isn't known at Premake time, but static value validation may be good to catch common issues.
-- To get a value that can be passed back to GNU make, do string.gsub of the "%$" pattern to "$$", and then p.esc.
-- For strictness and simplicity, the lone trailing $ is treated as a reference too (can't be a result of p.esc anyway).
function androidndk.unescapeAndRemoveMakeReferencesPostEsc(value)
	-- Unescape p.esc's escaping of the comment character.
	value = string.gsub(value, androidndk.commentUnescapePattern, "#");
	local newValue = {};
	local unclosedReferenceTerminators = {};
	local afterReferenceCharacter = false;
	for i = 1, string.len(value) do
		local character = string.sub(value, i, i);
		if afterReferenceCharacter then
			-- The character after the $.
			-- Options: $ (escaped raw $), an opening bracket (opening a reference), any other character (single-character reference).
			if character == "$" then
				if not (#unclosedReferenceTerminators > 0) then
					-- Escaped $.
					table.insert(newValue, "$");
				end
			elseif character == "(" then
				table.insert(unclosedReferenceTerminators, ")");
			elseif character == "{" then
				table.insert(unclosedReferenceTerminators, "}");
			end
			afterReferenceCharacter = false;
		else
			-- Not the character after the $.
			-- Options: $, a reference-closing bracket, any other raw character.
			if character == "$" then
				afterReferenceCharacter = true;
			else
				if #unclosedReferenceTerminators > 0 then
					if character == unclosedReferenceTerminators[#unclosedReferenceTerminators] then
						unclosedReferenceTerminators[#unclosedReferenceTerminators] = nil;
					end
				else
					-- A raw character outside references.
					table.insert(newValue, character);
				end
			end
		end
	end
	return table.concat(newValue);
end

function androidndk.staticallyHasPatternPostEsc(value, pattern)
	return string.find(androidndk.unescapeAndRemoveMakeReferencesPostEsc(value, true), pattern) ~= nil;
end

-- Characters that can be escaped with a backslash in Windows shell commands, except for \ itself and ".
-- \ and " should be escaped before these inside individual arguments as they may be wrapped in " by the module itself to include whitespaces.
-- On Windows, before other characters (except for \ and "), a \ is kept and treated as a directory separator instead.
-- Extracted by using all characters 33-126 (with special rules for #) prefixed with \ in a -Define and seeing the Clang error for its usage.
-- Matches Windows sh_chars_sh in GNU make, with the addition of a single quote.
-- On Linux, where \ is not a path separator, prefixing any character with \ results in it being escaped in the shell.
androidndk.shellEscapedCharactersPostQuotes = {
	"#", "$", "&", "'", "(", ")", "*", ";", "<", ">", "?", "[", "]", "^", "`", "{", "|", "}"
};

-- Checkers are meant to be used in assignToVariablePostEsc calls, and assume the input is pre-escaped and doesn't contain non-empty references.

function androidndk.shellEscapePostQuotesChecker(value)
	-- Comments are escaped as $()\# - contains an empty reference.
	-- However, this still includes the # itself, which needs to be escaped with a backslash in a shell command.
	-- Raw dollar signs ($$ representing $) need to be escaped in a shell command too.
	if string.find(value, "#") ~= nil or string.find(value, "%$%$") ~= nil then
		return true;
	end
	-- Remove empty references to check if the value contains (){}.
	-- It's assumed that these are the only kind of references that may be passed to checkers.
	value = string.gsub(string.gsub(value, "%$%(%)", ""), "%${}", "");
	return string.find(value, "[&'%(%)%*;<>%?%[%]%^`{|}]") ~= nil;
end

function androidndk.shellEscapeChecker(value)
	-- The only two usages of a backslash after androidndk.esc are a raw backslash and a # escape sequence.
	-- Both \ and # need to be escaped with \ in the shell.
	-- So, it's okay to return true if there is any \ at all.
	if string.find(value, "[\\\"]") ~= nil then
		return true;
	end
	return androidndk.shellEscapePostQuotesChecker(value);
end

function androidndk.shellEscapeModuleFileNameChecker(value)
	-- : must be \-escaped on Linux.
	-- It's a drive letter separator on Windows, however, so it's disallowed in LOCAL_MODULE_FILENAME there (it's a name, not a path).
	if string.find(value, "[:]") ~= nil then
		return true;
	end
	return androidndk.shellEscapeChecker(value);
end

function androidndk.shellEscapeSrcFilesChecker(value)
	-- : must be \-escaped on Linux, but cannot be escaped on non-Cygwin Windows, and is a drive letter separator there supported directly.
	-- The differences are handled at build time according to $(HOST_OS).
	if string.find(value, "[:]") ~= nil then
		return true;
	end
	return androidndk.shellEscapeChecker(value);
end

-- Using UPPER_CASE names because ndk-build reserves all lower-case names.
androidndk.shellEscapePreQuotesMakeCall = "PREMAKE_ANDROIDNDK_SHELL_ESCAPE_PRE_QUOTES";
androidndk.shellEscapePostQuotesMakeCall = "PREMAKE_ANDROIDNDK_SHELL_ESCAPE_POST_QUOTES";
androidndk.shellEscapeMakeCall = "PREMAKE_ANDROIDNDK_SHELL_ESCAPE";
androidndk.shellEscapeModuleFileNameMakeCall = "PREMAKE_ANDROIDNDK_SHELL_ESCAPE_MODULE_FILENAME";
androidndk.shellEscapeSrcFilesMakeCall = "PREMAKE_ANDROIDNDK_SHELL_ESCAPE_SRC_FILES";

androidndk.temporaryVariablePrefix = "PREMAKE_ANDROIDNDK_TEMPORARY_";

-- Gets or adds a temporary intermediate GNU make variable.
-- Useful for wrapping strings in GNU make function calls, for safety if they contain the closing bracket.
function androidndk.getTemporaryVariableReference(temporaryVariables, value)
	local index = temporaryVariables[value];
	if index == nil then
		index = #temporaryVariables + 1;
		temporaryVariables[index] = value;
		temporaryVariables[value] = index;
	end
	return "$(" .. androidndk.temporaryVariablePrefix .. index .. ")";
end

function androidndk.getCaseElse(anyCasesWritten)
	if anyCasesWritten then
		return "else ";
	end
	return "";
end

-- ABIs that be set by a combination of settings that can be expressed in a project.
-- With the architecture set to "universal" or nil, projects can be built for ABIs not in this list though.
-- If new ABIs are added to the NDK, they can be supported without updating this module at least in ABI-agnostic projects.
-- Sorted alphabetically.
androidndk.knownAbis = {
	"arm64-v8a",
	-- "armeabi" (ARMv5) was removed in NDK r17.
	"armeabi-v7a",
	-- "armeabi-v7a-hard" was removed in NDK r12.
	-- Building for both calling conventions at once (if passing this table to APP_ABI) would be pointless anyway.
	-- "mips" and "mips64" were removed in NDK r17.
	-- Premake has no built-in architecture values for MIPS.
	"x86",
	"x86_64",
};

androidndk.ABI_ALL = "all";

androidndk.architectureAbis = {
	[p.ARM] = "armeabi-v7a",
	[p.ARM64] = "arm64-v8a",
	[p.X86] = "x86",
	[p.X86_64] = "x86_64",
};

-- Returns:
-- * The ABI name for supported configurations.
-- * "all" (like the "all" that can be passed to APP_ABI) if the configuration doesn't have an ABI filter.
-- * nil for unsupported configurations.
function androidndk.getConfigAbi(config)
	-- While armeabi (ARMv5) and armeabi-v7a (ARMv7) may be both considered "ARM", ARMv5 is different enough to have its own `architecture` option.
	-- Support for ARMv5, however, was removed in NDK r17.
	-- If needed, it can be exposed via a separate configuration variable.
	-- MIPS support was also removed in r17.
	if config.architecture == nil or config.architecture == p.UNIVERSAL then
		return androidndk.ABI_ALL;
	end
	return androidndk.architectureAbis[config.architecture];
end

function androidndk.preventWhitespaceTrimming(value)
	if androidndk.whitespacesNonNewline[string.sub(value, 1, 1)] ~= nil then
		-- Prevent trimming of the leading whitespaces.
		value = "$()" .. value;
	end
	local trailingCharacter = string.sub(value, -1, -1);
	if trailingCharacter == "\\" or androidndk.whitespacesNonNewline[trailingCharacter] ~= nil then
		-- Don't treat the final backslash (like in a directory path) as line splitting.
		-- Also prevent trimming of the trailing whitespaces.
		value = value .. "$()";
	end
	return value;
end

-- Returns whether the post-processing call is needed for any element.
function androidndk.assignToVariablePostEsc(name, value, multiline, postProcessChecker, operator)
	if operator == nil then
		operator = ":=";
	end
	if type(value) == "string" then
		value = { value };
	end
	value = table.filterempty(value);
	if not (#value > 0) then
		return false;
	end
	local postProcessNeeded = false;
	if multiline then
		p.push("%s %s \\", name, operator);
		for i, element in ipairs(value) do
			local boundedLine = androidndk.preventWhitespaceTrimming(element);
			if i >= #value then
				p.w(boundedLine);
			else
				p.w("%s \\", boundedLine);
			end
			-- Post-processing is always needed if there are references because they are expanded to anything at runtime.
			-- However, if not needed, don't waste build time doing unnecessary substitutions.
			if postProcessChecker ~= nil and not postProcessNeeded and (androidndk.hasNonEmptyMakeReferencesPostEsc(element) or postProcessChecker(element)) then
				postProcessNeeded = true;
			end
		end
		p.pop();
	else
		-- Inner whitespaces are preserved within the right-hand side of an assignment, safe to concatenate.
		p.w("%s %s %s", name, operator, androidndk.preventWhitespaceTrimming(table.concat(value, " ")));
	end
	return postProcessNeeded;
end

function androidndk.writePostProcessCall(variableName, makeCall)
	p.w("%s := $(call %s,$(%s))", variableName, makeCall, variableName);
end

function androidndk.isConfigSupported(config, reportWarnings)
	if config.flags.ExcludeFromBuild then
		-- Intentionally excluded.
		-- Warnings specific to this module shouldn't be reported either as the configuration may not be targeting this module at all.
		return false;
	end
	if config.project ~= nil then
		assert(androidndk.isProjectSupported(config.project, false), "Usage of configurations for unsupported projects must not be attempted at all");
	end
	-- Wrong kind or ABI are a normal situation when the project has both Android and non-Android configs.
	-- Not reporting warnings for them (or any warnings as for non-Android targets these issues may be non-existent).
	if androidndk.kindScripts[config.kind] == nil or androidndk.getConfigAbi(config) == nil then
		return false;
	end
	local warningLocation;
	if reportWarnings then
		if config.project ~= nil then
			warningLocation = string.format("workspace '%s' project '%s' configuration '%s'", config.workspace.name, config.project.name, config.name);
		else
			warningLocation = string.format("workspace '%s' configuration '%s'", config.workspace.name, config.name);
		end
	end
	local configSupported = true;
	-- Whitespaces because configurations are placed in a whitespace-separated list.
	-- % because configurations and platforms are used in filter and filter-out, where % is a wildcard.
	-- It can be escaped with \, but then the case when the % is preceded by other backslashes is complicated to handle.
	-- The rest are disallowed due to usage of the names in GNU make function calls.
	local disallowedCharacters = "%(),";
	local disallowedPattern = "[%s%%%(%),]";
	if androidndk.staticallyHasPatternPostEsc(p.esc(config.buildcfg), disallowedPattern) then
		configSupported = false;
		if reportWarnings then
			p.warn(
				"Skipping %s with configuration name containing whitespaces or disallowed characters %s",
				warningLocation, disallowedCharacters);
		end
	end
	if config.platform ~= nil and androidndk.staticallyHasPatternPostEsc(p.esc(config.platform), disallowedPattern) then
		configSupported = false;
		if reportWarnings then
			p.warn(
				"Skipping %s with platform name containing whitespaces or disallowed characters %s",
				warningLocation, disallowedCharacters);
		end
	end
	return configSupported;
end

return androidndk;
