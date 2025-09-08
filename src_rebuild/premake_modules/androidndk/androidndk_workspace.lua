-- premake-androidndk - a multi-ABI, multi-language ndk-build Android.mk generator for Premake.
-- Originally written by Vitaliy <Triang3l> Kuzmin.
-- See README.md for detailed usage and design information.
-- Available under the Unlicense (see UNLICENSE.txt) or the BSD 3-Clause "New" or "Revised" License (see LICENSE.txt).

local p = premake;
local androidndk = p.modules.androidndk;

-- Projects can add their own configurations and platforms.
-- So, the use of workspace.configurations, workspace.projects, and their product workspace.configs, should be avoided.
-- Instead, configs should be gathered from all projects.

-- Writes the setup of the variables used in configuration conditionals.
-- Required in both Application.mk and the workspace Android.mk because with Gradle, the Application.mk is optional.
function androidndk.setupConfigConditionalMakeVariables(usedBuildcfgs, usedPlatforms)
	-- Display generated workspace usage information.
	-- Using warning/error directly, not the __ndk_* counterparts.
	-- __ndk_* functions are internal, and it's more important to show this to the user than to respect NDK_NO_*.
	-- $(info) is not displayed in the build output in Android Studio, using $(warning) for everything.
	p.push("ifeq ($(filter %s,$(PREMAKE_ANDROIDNDK_CONFIGURATIONS)),)", table.concat(p.esc(usedBuildcfgs), " "));
	p.w("$(warning No configurations to build are specified in PREMAKE_ANDROIDNDK_CONFIGURATIONS.)");
	p.w("$(warning Specify one or multiple \"PREMAKE_ANDROIDNDK_CONFIGURATIONS+=configuration\" in the ndk-build arguments to build those configurations.)");
	p.w("$(warning For workspaces with multiple target platforms, you can also provide the list of the platforms to build via PREMAKE_ANDROIDNDK_PLATFORMS.)");
	p.w("$(warning If PREMAKE_ANDROIDNDK_PLATFORMS is not specified, the projects in this workspace will be built for all platforms they're targeting.)");
	p.w("$(warning Note that configuration and platform names are case-sensitive in this script.)");
	p.w("$(warning )");
	p.w("$(warning It's heavily recommended that only at most one configuration and platform specified corresponds to each targeted ABI.)");
	p.w("$(warning Otherwise, which set of project settings will actually be chosen for building for each ABI will be undefined.)");
	p.w("$(warning )");
	p.w("$(warning The recommended approach is to use configurations for the optimization mode, and, if needed, platforms for ABI filtering.)");
	p.w("$(warning This can be done by specifying different values of the Premake architecture setting for each platform using a platform filter.)");
	p.w("$(warning In this case, each ABI will unambiguously correspond to only one configuration and platform pair.)");
	p.w("$(warning )");
	p.w("$(warning Configurations for this workspace:)");
	for i, buildcfg in ipairs(usedBuildcfgs) do
		p.x("$(warning $()  %s)", buildcfg);
	end
	p.w("$(warning )");
	if #usedPlatforms > 0 then
		p.w("$(warning Platforms for this workspace:)");
		for i, platform in ipairs(usedPlatforms) do
			p.x("$(warning $()  %s)", platform);
		end
	else
		p.w("$(warning This workspace is platform-agnostic.)");
	end
	p.w("$(error Aborting.)");
	p.pop("endif");

	-- Generate variables used for configuration selection.
	-- As Application.mk variables are preserved in Android.mk, += may result in duplication.
	-- Only using := for this reason, and also not modifying the original PREMAKE_ANDROIDNDK_CONFIGURATIONS/PLATFORMS.
	p.w("PREMAKE_ANDROIDNDK_CONFIGURATIONS_PREFIXED := $(addprefix CONFIGURATION=,$(PREMAKE_ANDROIDNDK_CONFIGURATIONS))");
	if #usedPlatforms > 0 then
		p.push("ifneq ($(PREMAKE_ANDROIDNDK_PLATFORMS),)");
		p.w("PREMAKE_ANDROIDNDK_PLATFORMS_PREFIXED := $(addprefix PLATFORM=,$(PREMAKE_ANDROIDNDK_PLATFORMS))");
		p.pop();
		p.push("else");
		local usedPlatformsPrefixed = {};
		for i, platform in ipairs(usedPlatforms) do
			table.insert(usedPlatformsPrefixed, "PLATFORM=" .. p.esc(platform));
		end
		p.w("PREMAKE_ANDROIDNDK_PLATFORMS_PREFIXED := %s", table.concat(usedPlatformsPrefixed, " "));
		p.pop("endif");
	end
end

function androidndk.findConfigForAppSetting(workspace, buildcfg, platform, predicate)
	-- In none of these checks should completely unrequested build configurations or platforms pass.
	-- This may lead, for instance, to systemversion for a totally different OS to be selected as a fallback.

	-- Considering the workspace (and, if it doesn't provide the needed value, the start project) highest-priority.
	-- Even when requesting platform-specific settings, but the start project is platform-agnostic (nil .platform), still prefer the start project.
	-- This makes settings more controllable than when some project can override the setting just because it has a platform specialization.

	-- Try to find in the workspace itself.
	for config in p.workspace.eachconfig(workspace) do
		if androidndk.isConfigSupported(config, false) then
			if config.buildcfg == buildcfg and (config.platform == nil or config.platform == platform) and predicate(config) then
				return config;
			end
		end
	end

	-- If didn't find in the workspace itself, try the main project in the workspace - the start project.
	if workspace.startproject ~= nil then
		local startProject = p.workspace.findproject(workspace, workspace.startproject);
		if startProject ~= nil and androidndk.isProjectSupported(startProject, false) then
			for config in p.project.eachconfig(startProject) do
				if androidndk.isConfigSupported(config, false) then
					if config.buildcfg == buildcfg and (config.platform == nil or config.platform == platform) and predicate(config) then
						return config;
					end
				end
			end
		end
	end

	-- This configuration may be used by just a subset of the projects.
	-- Platform-specific specializations and platform-agnostic fallbacks are obtained via separate findConfigForAppSetting calls in this case.
	-- ?= for platform-agnostic variables is done even if platform conditions pass - no need to look for them here for non-nil platforms.
	for project in p.workspace.eachproject(workspace) do
		if androidndk.isProjectSupported(project, false) then
			for config in p.project.eachconfig(project) do
				if androidndk.isConfigSupported(config, false) then
					if config.buildcfg == buildcfg and config.platform == platform and predicate(config) then
						return config;
					end
				end
			end
		end
	end

	-- Found nothing - don't add the setting.
	return nil;
end

-- Returns a table of { variable = "APP_...", value = ... }, with the variable values escaped.
-- Expecting the outer code to set APP_DEBUG to false if APP_OPTIM is release in the end to match Premake optimize/symbols logic.
function androidndk.gatherEscapedAppVariables(workspace, buildcfg, platform)
	-- If the value for a Premake setting is not specified by the projects for this configuration, the default must not be added to the table.
	-- This would make it impossible for another configuration, where the setting is explicitly defined, to override the value using ?=.
	-- Only returning variables corresponding to settings explicitly defined for this configuration.

	-- ndk-build defaults to non-debug (potentially no symbols) and optimized.
	-- Premake doesn't define a default for symbols, but unoptimized by default.
	-- Replicating the p.config.isDebugBuild and p.config.isOptimizedBuild logic.
	-- An optimized build is not considered a debug one at all, regardless of whether symbols are needed.
	local optimizeConfig = androidndk.findConfigForAppSetting(workspace, buildcfg, platform, function(config)
		return config.optimize ~= nil;
	end);
	-- optimizeConfig.optimize ~= nil checked previously.
	local isOptimized = optimizeConfig ~= nil and optimizeConfig.optimize ~= p.OFF and optimizeConfig.optimize ~= "Debug";
	local appOptim = nil;
	if optimizeConfig ~= nil then
		-- The configuration explicitly wants to enable or to disable optimizations.
		appOptim = iif(isOptimized, "release", "debug");
	end
	-- Expecting the outer code to set APP_DEBUG to false if APP_OPTIM is release.
	-- Thus, not explicitly returning APP_DEBUG ?= false for release APP_OPTIM.
	local appDebug = nil;
	if not isOptimized then
		local symbolsConfig = androidndk.findConfigForAppSetting(workspace, buildcfg, platform, function(config)
			return config.symbols ~= nil;
		end);
		if symbolsConfig ~= nil then
			-- p.config.isOptimizedBuild checked previously.
			appDebug = iif(symbolsConfig.symbols ~= p.OFF and symbolsConfig.symbols ~= p.DEFAULT, "true", "false");
		end
	end

	local appVariables = {};

	-- APP_DEBUG
	if appDebug ~= nil then
		table.insert(appVariables, { variable = "APP_DEBUG", value = appDebug });
	end

	-- APP_OPTIM
	if appOptim ~= nil then
		table.insert(appVariables, { variable = "APP_OPTIM", value = appOptim });
	end

	-- APP_PLATFORM
	local systemVersionConfig = androidndk.findConfigForAppSetting(workspace, buildcfg, platform, function(config)
		return p.project.systemversion(config) ~= nil;
	end);
	if systemVersionConfig ~= nil then
		table.insert(appVariables, { variable = "APP_PLATFORM", value = "android-" .. p.esc(p.project.systemversion(systemVersionConfig)) });
	end

	-- PREMAKE_ANDROIDNDK_APP_STL_RUNTIME (part of APP_STL)
	local stlConfig = androidndk.findConfigForAppSetting(workspace, buildcfg, platform, function(config)
		return config.cppstl ~= nil;
	end);
	if stlConfig ~= nil then
		-- The default, which in ndk-build is "none", is explicitly requested for this configuration.
		local stl = iif(stlConfig.cppstl == p.DEFAULT, "none", stlConfig.cppstl);
		table.insert(appVariables, { variable = "PREMAKE_ANDROIDNDK_APP_STL_RUNTIME", value = p.esc(stl) });
	end

	-- PREMAKE_ANDROIDNDK_APP_STL_LINKAGE (part of APP_STL)
	-- While for ndk-build, the default STL is "none", which doesn't have a linkage suffix, for CMake it's "c++_static".
	-- Therefore, considering static the default (treating explicitly specified "Default" as "On").
	local staticRuntimeConfig = androidndk.findConfigForAppSetting(workspace, buildcfg, platform, function(config)
		return config.staticruntime ~= nil;
	end);
	if staticRuntimeConfig ~= nil then
		local stlLinkage = iif(staticRuntimeConfig.staticruntime ~= p.OFF, "_static", "_shared");
		table.insert(appVariables, { variable = "PREMAKE_ANDROIDNDK_APP_STL_LINKAGE", value = stlLinkage });
	end

	return appVariables;
end

function androidndk.onWorkspace(workspace)
	-- Not allowing references or escaped $ in workspace names as they complicate path building as well as specifying APP_BUILD_SCRIPT.
	-- Premake treats any path beginning with $ as absolute.
	-- APP_BUILD_SCRIPT also doesn't allow #$ and whitespaces.
	if string.find(workspace.name, "%$") ~= nil or androidndk.staticallyHasPatternPostEsc(p.esc(workspace.name), "[%s#%$]") then
		p.warn("Skipping workspace '%s' with name containing GNU make references, whitespaces or disallowed characters #$", workspace.name);
		return;
	end

	androidndk.setupGeneration();

	-- Gather build configurations and platforms used by all projects for generating conditionals for application settings.
	-- Projects may add their configurations not present in the workspace itself, and they won't appear in workspace.configs.
	-- Some projects may have no platforms specified.
	-- In this case, they're built regardless of the platform, and also if some completely different platform is specified.
	-- At least one build configuration is required in a project, however.
	local usedBuildcfgs = {};
	local usedPlatforms = {};
	for project in p.workspace.eachproject(workspace) do
		if androidndk.isProjectSupported(project, false) then
			for config in p.project.eachconfig(project) do
				if androidndk.isConfigSupported(config, false) then
					table.insertkeyed(usedBuildcfgs, config.buildcfg);
					if config.platform ~= nil then
						table.insertkeyed(usedPlatforms, config.platform);
					end
				end
			end
		end
	end

	-- Application.mk.
	p.generate(workspace, ".Application.mk", function(workspace)
		-- Verify the correctness of the arguments, and set up the variables used for filtering in Application.mk.
		androidndk.setupConfigConditionalMakeVariables(usedBuildcfgs, usedPlatforms);

		-- Gather Application.mk variable values for selected configurations and platforms.
		-- As this is Application.mk, ABI filtering is not possible.
		-- Therefore, selection of the required build configurations and platforms will work differently than in projects.
		-- All selected build configurations and platforms must have the same values of settings written here.
		-- For example, APP_OPTIM may be wrong with `PREMAKE_ANDROIDNDK_CONFIGURATIONS := Debug Release` if they have different `optimize`.
		-- If one selected configuration-platform defines a value, while another doesn't care, pick from the one where it's explicitly set.
		-- So, using if/if and ?= instead of if/elseif and :=, unlike in projects (where only configuration-platform pair is supposed to be chosen).
		-- Most APP variables accept only one value - using ?= for them.
		-- APP_ABI, however, accumulates the needed ABIs (in this case, for selected configurations and platforms), so using += for it.

		-- First, clear values that will be set - they might have been set externally while invoking ndk-build, override them.
		-- Setting them to an empty value is not sufficient - `undefine` is required for ?= to work.
		-- clear-vars is called for known APP variables before including Application.mk, which, as of NDK r23, defines the values as empty, however.
		-- For this reason, if no value is provided, defining each of these variables as something (at least as empty).
		p.w("undefine APP_ABI");
		p.w("undefine APP_DEBUG");
		p.w("undefine APP_OPTIM");
		p.w("undefine APP_PLATFORM");
		p.w("undefine PREMAKE_ANDROIDNDK_APP_STL_RUNTIME");
		p.w("undefine PREMAKE_ANDROIDNDK_APP_STL_LINKAGE");

		-- Gather ABIs the projects are built for, for each configuration and platform for it.
		-- Can't just collect all ABIs used by all platforms into a single APP_ABI assignment.
		-- The reason is that some configurations may not even be targeting Android.
		-- For instance, may only want ARM builds for Android, but x86 builds only for Windows.
		-- If "all" is present in any platform-specific or platform-agnostic table, the whole platform must be treated as using "all".
		local buildcfgsAbis = {
			-- [1...] = [buildcfg] = {
			--   platformSpecific = {
			--     [1...] = [platform] = {
			--       [1...] = [abi] = abi,
			--     }
			--   },
			--   platformAgnostic = {
			--     [1...] = [abi] = abi,
			--   },
			-- }
		};
		local abiAgnosticConfigsUsed = false;
		for project in p.workspace.eachproject(workspace) do
			if androidndk.isProjectSupported(project, false) then
				for config in p.project.eachconfig(project) do
					if androidndk.isConfigSupported(config, false) then
						local buildcfgAbis = buildcfgsAbis[config.buildcfg];
						if buildcfgAbis == nil then
							buildcfgAbis = { platformSpecific = {}, platformAgnostic = {} };
							buildcfgsAbis[config.buildcfg] = buildcfgAbis;
						end
						local platformAbis;
						if config.platform ~= nil then
							platformAbis = buildcfgAbis.platformSpecific[config.platform];
							if platformAbis == nil then
								platformAbis = {};
								buildcfgAbis.platformSpecific[config.platform] = platformAbis;
							end
						else
							platformAbis = buildcfgAbis.platformAgnostic;
						end
						local abi = androidndk.getConfigAbi(config);
						table.insertkeyed(platformAbis, abi);
						if abi == androidndk.ABI_ALL then
							abiAgnosticConfigsUsed = true;
						end
					end
				end
			end
		end

		-- Gather the variables, and write the ABIs and variables.
		for i, buildcfg in ipairs(usedBuildcfgs) do
			local buildcfgConditionalOpen = false;

			local buildcfgAbis = buildcfgsAbis[buildcfg];
			-- Skip ABIs needed by platform-agnostic projects with this configuration from platform specializations.
			-- ABIs needed by platform-agnostic projects will be added regardless of the platform.
			local platformAgnosticAbis = nil;
			local platformAgnosticAbisAll = false;
			if buildcfgAbis ~= nil then
				platformAgnosticAbis = buildcfgAbis.platformAgnostic;
				platformAgnosticAbisAll = platformAgnosticAbis[androidndk.ABI_ALL] ~= nil;
			end

			-- Gather and write platform-specific ABIs and platform specializations of APP variables.
			for i2, platform in ipairs(usedPlatforms) do
				-- Gather ABIs that any projects, for this buildcfg-platform pair, need to be built for.
				-- Skip ABIs needed by platform-agnostic projects with this configuration from platform specializations.
				-- ABIs needed by platform-agnostic projects will be added regardless of the platform.
				local platformNewAbis = {};
				if buildcfgAbis ~= nil and not platformAgnosticAbisAll then
					if buildcfgAbis ~= nil then
						local platformAbisUnfiltered = buildcfgAbis.platformSpecific[platform];
						if platformAbisUnfiltered ~= nil then
							for i3, abi in ipairs(platformAbisUnfiltered) do
								if abi == androidndk.ABI_ALL then
									platformNewAbis = { androidndk.ABI_ALL };
									break;
								end
								if platformAgnosticAbis == nil or platformAgnosticAbis[abi] == nil then
									table.insert(platformNewAbis, abi);
								end
							end
							-- Sort alphabetically for stable output.
							table.sort(platformNewAbis);
						end
					end
				end
				-- Gather specializations of the APP variables for this platform.
				local platformAppVariables = androidndk.gatherEscapedAppVariables(workspace, buildcfg, platform);
				-- Write ABI additions and variable specializations for this platform.
				if #platformNewAbis > 0 or #platformAppVariables > 0 then
					if not buildcfgConditionalOpen then
						buildcfgConditionalOpen = true;
						p.push("ifneq ($(filter CONFIGURATION=%s,$(PREMAKE_ANDROIDNDK_CONFIGURATIONS_PREFIXED)),)", p.esc(buildcfg));
					end
					p.push("ifneq ($(filter PLATFORM=%s,$(PREMAKE_ANDROIDNDK_PLATFORMS_PREFIXED)),)", p.esc(platform));
					androidndk.assignToVariablePostEsc("APP_ABI", platformNewAbis, false, nil, "+=");
					for i3, variable in ipairs(platformAppVariables) do
						androidndk.assignToVariablePostEsc(variable.variable, variable.value, false, nil, "?=");
					end
					-- Close the platform conditional.
					p.pop("endif");
				end
			end

			-- Write ABIs for platform-agnostic projects and APP variable values used when no platform specialization has been chosen.
			local platformAgnosticAbisSorted = nil;
			if platformAgnosticAbis ~= nil then
				if platformAgnosticAbisAll then
					platformAgnosticAbisSorted = { androidndk.ABI_ALL };
				else
					platformAgnosticAbisSorted = table.arraycopy(platformAgnosticAbis);
					-- Sort alphabetically for stable output.
					table.sort(platformAgnosticAbisSorted);
				end
			end
			local platformAgnosticAppVariables = androidndk.gatherEscapedAppVariables(workspace, buildcfg, nil);
			if (platformAgnosticAbisSorted ~= nil and #platformAgnosticAbisSorted > 0) or #platformAgnosticAppVariables > 0 then
				if not buildcfgConditionalOpen then
					buildcfgConditionalOpen = true;
					p.push("ifneq ($(filter CONFIGURATION=%s,$(PREMAKE_ANDROIDNDK_CONFIGURATIONS_PREFIXED)),)", p.esc(buildcfg));
				end
				if platformAgnosticAbisSorted ~= nil then
					androidndk.assignToVariablePostEsc("APP_ABI", platformAgnosticAbisSorted, false, nil, "+=");
				end
				for i2, variable in ipairs(platformAgnosticAppVariables) do
					androidndk.assignToVariablePostEsc(variable.variable, variable.value, false, nil, "?=");
				end
			end

			if buildcfgConditionalOpen then
				p.pop("endif");
			end
		end

		-- Apply defaults if no configuration-specific overrides have been chosen, and normalize variables.
		-- Also set variables that don't depend on the configuration.

		-- APP_ABI
		-- Setting to "all" by default is not needed - empty already means `all`.
		-- Also, it can happen only when no configuration with projects to build is selected.
		-- Remove duplicates (sorting does that implicitly).
		p.w("APP_ABI := $(sort $(APP_ABI))");
		-- If "all" was set for any configuration, and += of any other ABIs happened, make APP_ABI just "all".
		if abiAgnosticConfigsUsed then
			p.push("ifneq ($(filter " .. androidndk.ABI_ALL .. ",$(APP_ABI)),)");
			p.w("APP_ABI := " .. androidndk.ABI_ALL);
			p.pop("endif");
		end

		-- APP_BUILD_SCRIPT
		-- In the same directory, no need for p.filename followed by making it relative.
		-- Also for this reason, no need for path.join, which may treat the name as an absolute path (for instance, if it begins with a $()\#-escaped #).
		p.w("APP_BUILD_SCRIPT := %s", "$(call my-dir)/" .. p.esc(workspace.name .. ".wks.Android.mk"));

		-- APP_DEBUG and APP_OPTIM
		-- Handling according to p.config.isDebugBuild and p.config.isOptimizedBuild logic (unoptimized by default, no symbols by default).
		-- p.config.isDebugBuild always returns false (no symbols) for optimized builds.
		-- For more information, see APP_DEBUG and APP_OPTIM gathering.
		p.w("APP_OPTIM ?= debug");
		p.push("ifeq ($(APP_OPTIM),release)");
		p.w("APP_DEBUG := false");
		p.pop();
		p.push("else");
		p.w("APP_DEBUG ?= false");
		p.pop("endif");

		-- APP_PLATFORM
		-- Reverting the `undefine` because as of NDK r23, ndk-build sets all APP variables to empty values.
		p.w("APP_PLATFORM ?=");

		-- APP_STL
		-- The default for ndk-build is "none". Also, since the default for CMake is "c++_static", assuming static linkage by default.
		p.w("PREMAKE_ANDROIDNDK_APP_STL_RUNTIME ?= none");
		p.w("PREMAKE_ANDROIDNDK_APP_STL_LINKAGE ?= _static");
		-- "none" and "system" don't have linkage suffixes.
		p.push("ifneq ($(filter none system,$(PREMAKE_ANDROIDNDK_APP_STL_RUNTIME)),)");
		p.w("PREMAKE_ANDROIDNDK_APP_STL_LINKAGE :=");
		p.pop("endif");
		p.w("APP_STL := $(PREMAKE_ANDROIDNDK_APP_STL_RUNTIME)$(PREMAKE_ANDROIDNDK_APP_STL_LINKAGE)");
	end);

	-- Android.mk.
	p.generate(workspace, ".wks.Android.mk", function(workspace)
		-- my-dir returns the directory containing the latest included file, not the directory with the current file.
		-- Therefore, if project makefiles are written to other directories, calling it every time will result in incorrect paths.
		p.w("PREMAKE_ANDROIDNDK_WORKSPACE_DIR := $(call my-dir)");

		-- Verify the correctness of the arguments, and set up the variables used for filtering in Android.mk.
		-- This needs to be in Android.mk even though it inherits Application.mk variables because with Gradle, Application.mk is optional.
		androidndk.setupConfigConditionalMakeVariables(usedBuildcfgs, usedPlatforms);

		-- Setup post-expansion escaping in text passed to command execution via the shell.
		-- In some variables - LOCAL_CFLAGS/LOCAL_LDFLAGS, LOCAL_C_INCLUDES, LOCAL_MODULE_FILENAME - path requirements are pretty relaxed.
		-- On Linux, file names may contain " or \, but they need to be escaped with \ prefix as otherwise they're interpreted by the shell.
		-- On Windows, " is not allowed in file names, but a single \ is treated as a path separator - no escaping required.
		-- Function for calling inside quoted arguments (to be followed by the function for a list of arguments).
		p.w("%s = $(subst \",\\\",$(subst \\,\\\\,$(1)))", androidndk.shellEscapePreQuotesMakeCall);
		-- Function for calling for lists of quoted arguments.
		local escapeFunction = { androidndk.shellEscapePostQuotesMakeCall, "_NO_BRACKETS = " };
		local bracketsEncountered = 0;
		for i = #androidndk.shellEscapedCharactersPostQuotes, 1, -1 do
			local character = androidndk.shellEscapedCharactersPostQuotes[i];
			if character == "(" or character == ")" then
				-- Brackets must be used in a ${} call, not $().
				bracketsEncountered = bracketsEncountered + 1;
			else
				if character == "#" then
					-- Escape the comment character similar to the way androidndk.esc does that, breaking the dependency on the number of backslashes.
					character = androidndk.commentEscapeString;
				elseif character == "$" then
					character = "$$";
				end
				table.insert(escapeFunction, "$(subst ");
				table.insert(escapeFunction, character);
				table.insert(escapeFunction, ",\\");
				table.insert(escapeFunction, character);
				table.insert(escapeFunction, ",");
			end
		end
		table.insert(escapeFunction, "$(1)");
		table.insert(escapeFunction, string.rep(")", #androidndk.shellEscapedCharactersPostQuotes - bracketsEncountered));
		p.w(table.concat(escapeFunction));
		-- Escape the brackets as well.
		p.w(
			"%s = ${subst ),\\),${subst (,\\(,${call %s_NO_BRACKETS,${1}}}}",
			androidndk.shellEscapePostQuotesMakeCall,
			androidndk.shellEscapePostQuotesMakeCall);
		-- Function for raw text without arguments containing whitespaces that need to be wrapped in true, unescaped quotes.
		p.w(
			"%s = $(call %s,$(call %s,$(1)))",
			androidndk.shellEscapeMakeCall,
			androidndk.shellEscapePostQuotesMakeCall,
			androidndk.shellEscapePreQuotesMakeCall);
		-- Function for LOCAL_MODULE_FILENAME.
		-- : must be \-escaped on Linux.
		-- It's a drive letter separator on Windows, however, so it's disallowed in LOCAL_MODULE_FILENAME there (it's a name, not a path).
		-- Therefore, there's no need to handle it separately on Windows and Linux - just \-escape : unconditionally.
		p.w("%s = $(subst :,\\:,$(call %s,$(1)))", androidndk.shellEscapeModuleFileNameMakeCall, androidndk.shellEscapeMakeCall);
		-- Function for LOCAL_SRC_FILES and LOCAL_PCH.
		-- : must be \-escaped on Linux, but cannot be escaped on non-Cygwin Windows, and is a drive letter separator there supported directly.
		p.push("ifeq ($(HOST_OS),windows)");
		p.w("%s = $(call %s,$(1))", androidndk.shellEscapeSrcFilesMakeCall, androidndk.shellEscapeMakeCall);
		p.pop();
		p.push("else");
		p.w("%s = $(subst :,\\:,$(call %s,$(1)))", androidndk.shellEscapeSrcFilesMakeCall, androidndk.shellEscapeMakeCall);
		p.pop("endif");

		-- Include makefiles of all projects.
		-- Same path logic as in p.generate.
		local workspaceDirectory = path.getdirectory(p.filename(workspace, ".wks.Android.mk"));
		for project in p.workspace.eachproject(workspace) do
			if androidndk.isProjectSupported(project, false) then
				p.w(
					"include %s",
					androidndk.preventWhitespaceTrimming(
						path.join(
							"$(PREMAKE_ANDROIDNDK_WORKSPACE_DIR)",
							p.esc(path.getrelative(workspaceDirectory, p.filename(project, ".prj.Android.mk"))))));
			end
		end
	end);
end
