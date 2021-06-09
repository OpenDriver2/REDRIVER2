---
-- usage.lua
-- Usage and uses
--
-- Example
-- -------
--
-- usage "vendor"
--   defines "USING_VENDOR"
--   includedirs "include/vendor"
--   links "lib/vendor"
--
-- project "core"
--   kind "SharedLib"
--   uses "vendor"
--   uses "core"
--
-- usage "core"
--   links "openssh"
--   includedirs "include/core"
--
-- project "app"
--   kind "ConsoleApp"
--   uses "core_lib"
--
-- "core" will link vendor and openssh and define 'USING_VENDOR'
-- "app" will link 'core' and define 'USING_VENDOR'
-- If "core" was a StaticLib, the link dependencies would pass through.
-- "core" will define 'USING_VENDOR'
-- "app" would link 'vendor', 'core', and 'openssh' and still define
-- 'USING_VENDOR'
--
-- Notes
-- -----
--
-- 'uses' are recursive.
--
-- If a project and usage exist, the project is used first, then the usage.
--
-- If a project uses itself, any link dependencies in the usage will be
-- consumed by the project as needed. Otherwise those link dependencies
-- will pass onto to the user.
--
-- Using a project will link the project and resolves nested uses,
-- in addition to any declared usage.
--
-- TO CONSIDER: not sure this is needed anymore.
-- 'uses' can filter down to 'linkoptions' or 'buildoptions'
--    uses "linkoptions:opengl"
--    uses "buildoptions:opengl"
-- link options are defined as: links, linkoptions, libdirs.
-- buildoptions are defined as anything that isn't a link option.
-- TO CONSIDER: separate api, uses_linkoptions/uses_buildoptions?
--
-- The context of a 'usage' is the ultimate target context it is being
-- used in.
--
-- usage "external_lib"
--   links "external_lib-%{cfg.buildcfg}"
--
-- Filters work as you'd expect:
--
-- usage "debug_stuff"
--     defines "DEBUG_STUFF"
--
-- project "shared"
--   kind "SharedLib"
--   filter "configurations:debug"
--     uses "debug_stuff"
--
-- project "app"
--   kind "ConsoleApp"
--   uses "shared"  -- DEBUG_STUFF will be defined in the debug configuration.
--
-- Todo
-- ----
--
--   Cyclic reference detection. We are allowed to use a project more than
--   once, (eg. from different configurations) but not along the same call path.
--   Decide what to do with diamond shaped uses graphs, include twice, or
--   first use?
--
--   Handle block insertion ordering and 'removes' correctly
--

	local p = premake
	local oven = p.oven
	local context = p.context

--
-- 'uses' api
--

p.api.register {
	name = "uses",
		scope = { "config" },
		kind = "list:string",
	}

--
-- 'usage' container
--

	-- TODO: maybe lock down what can be specified in usage further?
	p.usage = p.api.container("usage", p.workspace, { "config" })

	function p.usage.new(mode)
		return p.container.new(p.usage, mode)
	end

--
-- Extend workspace with findusage
--

	function p.workspace.findusage(wks, name)
		name = name:lower()
		for _, usage in ipairs(wks.usages) do
			if name == usage.name:lower() then
				return usage
			end
		end
		return nil
	end

--
-- Given the current usage filter, does the new filter fit into it?
--

	local function compatibleUsage(currentUsageFilter, newUsageFilter)
		if newUsageFilter and currentUsageFilter then
			if currentUsageFilter ~= newUsageFilter then
				return false
			end
		end
		return true
	end


--
-- resolveUsage
--

	local resolveAllUsesInBlock

	local function resolveUsage( targetProject, targetBlock,
								 usage, usageName, usageFilter,
								 inheritedCriteria )

		verbosef("\nProject %s is using usage %s %s\n",
				 targetProject.name, usage.name, usageFilter or "" )

		-- A map for how to copy the usage blocks into the target project.
		-- Each entry in the map creates a new block.

		local propagateMap = {}

		local commonFields = { "_criteria", "_basedir", "uses" }
		local linkFields   = { "links", "linkoptions", "libdirs" }

		if usageFilter == nil then

			-- We don't have a filter.
			-- Create one block with the build options,
			-- and another with only the links options that is filtered
			-- for just link targets.

			table.insert( propagateMap, {
					usageFilter   = "buildoptions",
					excludeFields = linkFields
				} )

			table.insert( propagateMap, {
					terms = {'kind:not StaticLib'},
					usageFilter   = "linkoptions",
					includeFields = table.join( commonFields, linkFields )
				} )
		else

			-- Respect the filter we have, and create one block with
			-- either build or linkoptions

			if usageFilter == "buildoptions" then
				table.insert( propagateMap, {
					usageFilter   = "buildoptions",
					excludeFields = linkFields
				} )
			end

			if usageFilter == "linkoptions" then
				table.insert( propagateMap, {
					usageFilter   = "linkoptions",
					includeFields = table.join( commonFields, linkFields )
				} )
			end

		end

		-- Clone each block in the usage and insert it into the target project

		for _,propagate in ipairs(propagateMap) do

			verbosef("\nApplying %s to project %s from using usage %s\n",
					 propagate.usageFilter, targetProject.name, usage.name )

			for _,usageBlock in ipairs(usage.blocks) do

				-- Merge the criteria for the usage, target, propagate
				-- with any inherited criteria

				local newBlock = table.deepcopy(usageBlock)

				newBlock._criteria.patterns = table.join(
					newBlock._criteria.patterns,
					targetBlock._criteria.patterns )

				if inheritedCriteria ~= nil then
					newBlock._criteria.patterns = table.join(
						newBlock._criteria.patterns,
						inheritedCriteria.patterns )
				end

				if propagate.terms ~= nil then
					local propagateCriteria =
						p.criteria.new( propagate.terms )

					newBlock._criteria.patterns = table.join(
						newBlock._criteria.patterns,
						propagateCriteria.patterns )
				end

				newBlock._criteria.data =
					p.criteria._compile(newBlock._criteria.patterns)

				-- todo: would be nice not to do this.
				--  	 needs to be in sync with internal block logic.
				if newBlock.filename then
					newBlock.filename = nil
					newBlock._basedir = newBlock.basedir
					newBlock.basedir = nil
				end

				-- Filter the field set of the new block to the ones we
				-- are propagating

				for field,v in pairs(usageBlock) do

					local reject = false

					if propagate.excludeFields ~= nil then
						reject = table.contains(
							propagate.excludeFields, field )
					end

					if propagate.includeFields ~= nil then
						reject = reject or not table.contains(
							propagate.includeFields, field )
					end

					if reject then
						verbosef("ignoring %s from %s %s",
								 field, usage.name, propagate.usageFilter)

						newBlock[field] = nil
					else
						verbosef("keeping %s from %s %s",
								 field, usage.name, propagate.usageFilter)
					end
				end

				-- Insert the new block into the target project.
				-- TODO: We need to insert as if at the call site,
				--  	 and it need to deal with with 'removes'
				--  	 merging between the two blocks.

				table.insert( targetProject.blocks, newBlock )

				-- Recurse into the new block and resolve any 'uses' there

				resolveAllUsesInBlock(
					targetProject,
					newBlock,
					propagate.usageFilter )
			end
		end
	end


--
-- Resolve a single 'use', with a given filter and criteria,
-- into a target block of a target project
--

	local function resolveUse( targetProject, targetBlock,
							   usageName, usageFilter, inheritedCriteria )

		local targetWorkspace = targetProject.solution

		local sourceProject = p.workspace.findproject(
			targetWorkspace, usageName )

		local usage = p.workspace.findusage( targetWorkspace, usageName)

		if sourceProject == nil and usage == nil then
			error("Use of "
				  .. "'" .. usageName.. "'"
				  .. ", is not defined as a usage or project in workspace "
				  .. "'" .. targetWorkspace.name .. "'")
		end

		if sourceProject ~= nil and sourceProject.name ~= targetProject.name then

			verbosef("\nProject %s is using project %s\n",
					 targetProject.name, sourceProject.name )

			-- The source project might not be baked yet, bake it now.
			-- We need this for the configuration list.
			-- TODO: not sure if we need to do some project configuration
			-- mapping between source and target too? project.getconfig?

			sourceProject = p.container.bake(sourceProject)

			-- Iterate over the source project configurations and propagate
			-- any 'uses' in each configuration from the source project to
			-- the target project.
			-- We do this per configuration so we know the 'kind' of that
			-- configuration to influence what options are propagated
			-- through the project.

			for configName,configCtx in pairs(sourceProject.configs) do

				-- If this source configuration is link target, we only want to
				-- propagate buildoptions.
				-- For example, if the source project is a shared library,
				-- that linked with a static library, we don't also want the
				-- target to link the same static library since it's already
				-- linked in the source project.

				local configKind = context.fetchvalue(configCtx, 'kind')

				local configUsageFilter
				if configKind ~= 'StaticLib' then
					configUsageFilter = 'buildoptions'
				end

				if compatibleUsage( usageFilter, configUsageFilter ) then

					verbosef("== %s %s", configName,configKind)

					-- Resolve the 'uses' in this configuration to the target.
					-- Pass on this configuration as a criteria for the resolve.

					-- todo: already exists in configCtx._criteria
					-- todo: should be merging with inheritedCriteria?
					local configCriteria =
						p.criteria.new( {'configurations:' .. configName } )

					local configUses = context.fetchvalue( configCtx, 'uses' )

					local usedSelf = false

					for k,v in ipairs(configUses) do

						if v == sourceProject.name then
							usedSelf = true
							if usage then
								resolveUsage( targetProject, targetBlock,
											  usage, v, configUsageFilter or usageFilter,
											  configCriteria )
							else
								error( "Project " .. sourceProject.name
									   .. " used itself but declares no usage")
							end
						else
							resolveUse( targetProject,
										targetBlock,
										v,
										configUsageFilter or usageFilter,
										configCriteria )
						end
					end

					-- The project did not use it's own usage
					-- It is only exposing it only visible to other project.
					-- Don't apply configUsageFilter
					-- TO CONSIDER: not sure about that, but makes sense if we've not
					--              linked internally what's specified in our usage.

					if usage and not usedSelf then

						verbosef("= Project %s config %s, did not resolve own usage to %s. Resolving now\n",
								 sourceProject.name, configName, targetProject.name )

						resolveUsage( targetProject, targetBlock,
									  usage, usageName, usageFilter,
									  configCriteria )
					end

				end
			end

			-- When referring to a project, 'uses' acts like 'links' too.

			if usageFilter == nil or usageFilter == "linkoptions" then

				local linkBlock = targetBlock

				-- If we don't have a usageFilter, make sure this link only
				-- occurs on linkable targets.
				-- TODO: Functionally similar to block insertion for usages.
				-- same requirements/todos/bugs, should dedupe.

				if usageFilter == nil then
					linkBlock = {}

					-- todo: would be nice not to do this.
					--  	 needs to be in sync with internal block logic.
					if targetBlock.filename then
						linkBlock._basedir = targetBlock.basedir
					else
						linkBlock._basedir = targetBlock._basedir
					end

					local linkCriteria =
						p.criteria.new( {"kind:not StaticLib"} )

					linkBlock._criteria = {}

					linkBlock._criteria.patterns = table.join(
						targetBlock._criteria.patterns,
						linkCriteria.patterns)

					linkBlock._criteria.data =
						p.criteria._compile(linkBlock._criteria.patterns)

					table.insert( targetProject.blocks, linkBlock )
				end

				local key = "links"
				local field = p.field.get(key)
				linkBlock[key] = p.field.store( field,
												linkBlock[key],
												sourceProject.name )
			end

		elseif usage ~= nil then

			resolveUsage( targetProject, targetBlock,
						  usage, usageName, usageFilter,
						  inheritedCriteria )
		end

	end


--
-- Resolve all uses from a target block in a target project
--

	function resolveAllUsesInBlock( targetProject,
									targetBlock,
									inheritedUsageFilter )

		if targetBlock.uses then

			for _, usageKey in ipairs(targetBlock.uses) do

				local usageName = usageKey
				local usageFilter

				local separatorPos = usageKey:find(':')
				if separatorPos then
					usageName   = usageKey:sub(separatorPos + 1)
					usageFilter = usageKey:sub(0, separatorPos - 1)
				end

				if compatibleUsage(inheritedUsageFilter, usageFilter) then
					resolveUse( targetProject, targetBlock, usageName,
								inheritedUsageFilter or usageFilter )
				end

			end

		end
	end

--
-- Before baking a project, resolve all the 'uses'
--

	premake.override(p.project, "bake", function(base, self)

		-- Keep the list stable while we iterate and modify it

		local blocks = {}
		for k, v in pairs(self.blocks) do
			blocks[k] = v
		end

		for _, block in pairs(blocks) do
			resolveAllUsesInBlock(self, block)
		end

		return base(self)

	end)