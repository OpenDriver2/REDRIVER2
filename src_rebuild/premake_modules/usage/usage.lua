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
--   uses "core"
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
-- "uses" do not respect configurations/filters due to havy optimizations
-- "usage" can contain configuration filters

	require 'stack'

	local p = premake
	local oven = p.oven
	local context = p.context

	local keyLinks 		= "links"
	local field 		= p.field
	local fieldLinks 	= field.get(keyLinks)

	newoption {
	   trigger     = "usage-optimization-off",
	   description = "Turn off optimization for usage module. Useful for debuging dependencies (50% slower generation)."
	}

	local optimization = (_OPTIONS["usage-optimization-off"] == nil)

---
-- Two stacks which stores actual order of projects and usages
-- Projects stack and uses stack are aligned
--
	local usesStack = Stack:Create()
	local sourcesStack = Stack:Create()

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

---
-- Push usage and source project name on stack
-- * if "usage" is already on stack it mean that "usage" in this configuration was in use, 
--

	local printUsesStack
	local function pushUsage( usageName, sourceName )

		-- search for uses
		local usesStackIndex = usesStack:find_value(usageName)

		if usesStackIndex == nil then
        	verbosef("{PUSH} USES_STACK [%s]: %s", sourceName, usageName)

			-- push on stack
			usesStack:push(usageName)
			sourcesStack:push(sourceName)
		else
        	verbosef("{EXIST} USES_STACK [%s]: %s", sourceName, usageName)

		end
	end

---
-- Pop usage and source name form stack
--

	local function popUsage( count )
		local count = count or 1
		for i = 1, count do

			-- pop form stack
			local sourceName = sourcesStack:pop()
			local usageName  = usesStack:pop()

			verbosef("{POP} USES_STACK [%s]: %s", sourceName, usageName)
		end 
	end

--
-- During baking we can start new bake so we have to stash current stack 
--
	local stackStash = Stack:Create()	

---
-- During "bake" process it is posible to call another "bake", 
-- to starts new bake we have to stash current uses stack and create new empty
---

	local function stashStack()	
		if _OPTIONS["verbose"] then
			for i , sourceName in ipairs(sourcesStack._et) do					
				verbosef("{STASH} USES_STACK [%s]: %s", sourceName, usesStack:get(i))
			end
		end		
		stackStash:push( {["sourcesStack"] = sourcesStack, ["usesStack"] = usesStack} )
		sourcesStack = Stack:Create()
		usesStack = Stack:Create()
	end

---
-- After "bake" previous uses stack have to be recreated
---

	local function unstashStack()			
		local stash  = stackStash:pop()		
		sourcesStack = stash.sourcesStack
		usesStack    = stash.usesStack
		if _OPTIONS["verbose"] then
			for i , sourceName in ipairs(sourcesStack._et) do					
				verbosef("{UNSTASH} USES_STACK [%s]: %s", sourceName, usesStack:get(i))
			end
		end	
	end

--
-- Print stack
--

	printUsesStack = function()
		-- reconstructed full stack from stashed and current stacks		
		local fullStack = {} 
		-- for formating we need max length of sourceName, it will be first column
		local maxSourceNameLen = 1 

		-- get full stack form stashed stacks. form oldest to newest
		for _, stacks in ipairs(stackStash._et) do
			if stacks.sourcesStack:getn() > 0 then
				for i, sourceName in ipairs(stacks.sourcesStack._et) do
					local len = sourceName:len()
					if len > maxSourceNameLen then
						maxSourceNameLen = len
					end
					table.insert(fullStack, { ["sourceName"] = sourceName, ["usageName"] = stacks.usesStack:get(i) } )
				end
			end 
		end

		-- get stack form currect "bake"
		for i, sourceName in ipairs(sourcesStack._et) do
			local len = sourceName:len()
			if len > maxSourceNameLen then
				maxSourceNameLen = len
			end
			table.insert(fullStack, { ["sourceName"] = sourceName, ["usageName"] = usesStack:get(i) } )
		end

		-- print full stack in three columns
		-- SOURCE: ACRION: USAGE:
		--
		-- Actions:
		-- BAKES - mean that usage requred "bake" project
		-- USES  - use project or usage
		print("\nUses stack:\n")
		local line = string.format("%-" .. maxSourceNameLen .. "s ACRION: USAGE: \n", "SOURCE:")
		print(line)
		for _, entry in ipairs(fullStack) do
			if not entry.sourceName:find('"bake"') then
				if entry.usageName:find('"bake"') then
					line = string.format("%-" .. maxSourceNameLen .. "s BAKES   %s", entry.sourceName, entry.usageName:gsub('"bake" ', ""))
				else
					line = string.format("%-" .. maxSourceNameLen .. "s USES    %s", entry.sourceName, entry.usageName)
				end
				print(line)
			end			
		end
	end

---
-- Resolve usage of targetProject.targetBlock
--
	local function resolveUsage( targetProject, targetBlock, usage )		


		verbosef("\nProject %s is using usage %s\n",
				 targetProject.name, usage.name)


		-- Clone each block in the usage and insert it into the target project
		for _,usageBlock in ipairs(usage.blocks) do
		
			-- Merge the criteria for the usage and target

			-- detach fat references before deepcopy
			usageOrigin        = usageBlock._origin
			usageBlock._origin = nil
			
			local newBlock = table.deepcopy(usageBlock)

			-- attach fat references after deepcopy
			newBlock._origin   = usageOrigin
			usageBlock._origin = usageOrigin
			

			newBlock._criteria.patterns = table.join(
			newBlock._criteria.patterns,
			targetBlock._criteria.patterns )

			newBlock._criteria.data =
				p.criteria._compile(newBlock._criteria.patterns)

			-- todo: would be nice not to do this.
			--  	 needs to be in sync with internal block logic.
			if newBlock.filename then
				newBlock.filename = nil
				newBlock._basedir = newBlock.basedir
				newBlock.basedir = nil
			end
		
			-- Insert the new block into the target project.
			-- TODO: We need to insert as if at the call site,
			--  	 and it need to deal with with 'removes'
			--  	 merging between the two blocks.
			table.insert( targetProject.blocks, newBlock )


			-- Recursion in usage is to fuzzy
			if newBlock.uses then
				error("Usage '" .. usage.name .. "'. Uses in usage is forbidden, move 'uses' to project.")
			end

		end
	end 

---
-- Insert usageName to outTable and push usageName on stack,
-- if srcProjectName and usageName are equal push is not performed.
-- This is common case and it should be in separeted function
--
	local function insertUsage( usesTable, usageName, sourceName )
		local usagePushed = 0
		-- project can use own usage and it is valid use
		-- without this check we will get error about double push on stack
		if usageName ~= sourceName then
			pushUsage( usageName, sourceName )
			usagePushed = 1
		end
		table.insert( usesTable, usageName )
		return usagePushed
	end

---
-- Manually run "bake" process on source project if need,
-- if "bake" on sourceProject is under way this mean that we have circular dependence
--
	local function bakeProject( sourceProject, targetProject )
		-- _isUsageBaking - is flag on project which informs that premake alredy starts "bake" process
				--                  such situation occure with circular dependence
		if sourceProject._isUsageBaking then
			printUsesStack()
			error("Use of "
				  .. "'" .. sourceProject.name .. "' in '" .. targetProject.name .. "'"
				  .." circular dependence!!!" )	
		else
			if not sourceProject._usageBaked then
				verbosef("\nUsage starts baking %s\n", sourceProject.name )

				sourceProject._isUsageBaking = true
				
				pushUsage( '"bake" ' .. sourceProject.name, targetProject.name ) -- source mark "bake" process on stack
				if optimization then
					bakeProjectUsage( sourceProject )
				else
					sourceProject.ctx = p.container.bake(sourceProject) -- bake context is temporary in current version of premake5, we have to store it
					sourceProject._isBaked = false -- premake5 thinks that object was not baked					
				end
				popUsage()
				
				sourceProject._isUsageBaking = false
				sourceProject._usageBaked = true
				
				verbosef("\nUsage ends baking %s\n", sourceProject.name )
			end
		end
	end

---
-- Resolve a sourceProject 'uses' into a target block of a target project
--

	local resolveUse

	local function resolveUses( sourceProject, targetProject, targetBlock )
		
		if optimization then
			local targetProjectResolvedUses			= targetProject.resolvedUses -- get table of already resolved uses for this projects
			local sourceProjectResolvedUses 		= sourceProject.resolvedUses
			local sourceProjectName					= sourceProject.name
			local targetBlockResolvedUsesLinks		= targetBlock.resolvedUsesLinks

			-- Iterate over the source project uses
			for usageName,usageInfo in pairs(sourceProjectResolvedUses) do
				-- project can use own usage and it is valid use
				-- without this check we will get error about double push on stack
				if usageName ~= usageInfo.parent  then
					pushUsage( '"bake" ' .. usageInfo.parent, '???' )
					pushUsage( usageName, usageInfo.parent )
					popUsage(2)
				end
				if not targetProjectResolvedUses[usageName] then

					usage = usageInfo.block
					-- sourceProject include own usage
					if usage then
						resolveUsage( targetProject, targetBlock, usage )
					end

					if usageInfo.type == "project" then
						-- When referring to a project, 'uses' acts like 'links' too.
						table.insert(targetBlockResolvedUsesLinks, usageName )
					end

					targetProjectResolvedUses[usageName] = usageInfo
				end
			end
		else
			local pushCount = 0

			-- Store feched uses for future usage
			if sourceProject.ctx.usesValues == nil then
				sourceProject.ctx.usesValues = context.fetchvalue( sourceProject.ctx, 'uses' )
			end 

			local usesToResolve = {}
			-- push all uses on stack before resolve, it guranty that all uses on current level are before uses are resolved
			-- this is essential for duplicated uses detection
			for k,v in ipairs(sourceProject.ctx.usesValues ) do
				if type(v) == "table" then
					for _, vName in ipairs(v) do
						pushCount = pushCount + insertUsage( usesToResolve, vName, sourceProject.name )
					end 
				else 
					pushCount = pushCount + insertUsage( usesToResolve, v, sourceProject.name )
				end
			end 

			-- Iterate over the source project uses' 
			for _,v in ipairs(usesToResolve) do
				if v == sourceProject.name then
					if not usage then
						error( "Project " .. sourceProject.name .. " used itself but declares no usage")
					end
				else							
					resolveUse( targetProject,
								targetBlock,
								v )
				end
			end	
			
			if pushCount > 0 then
				popUsage(pushCount)
			end
		end
	end
	
---
-- Resolve a single 'use' into a target block of a target project
--

	resolveUse = function( targetProject, targetBlock, usageName )

		-- get table of already resolved uses for this projects
		local resolvedUses = targetProject.resolvedUses

		local usageType = "project"
		local usageScriptPath = ""
		-- if use already resolved SKIP it
		if not resolvedUses[usageName] then

			local targetWorkspace = targetProject.solution

			local sourceProject = p.workspace.findproject( targetWorkspace, usageName )
			local usage 		= p.workspace.findusage(   targetWorkspace, usageName )

			if sourceProject ~= nil and sourceProject.name ~= targetProject.name then

				verbosef("\nProject %s is using project %s\n",
						 targetProject.name, sourceProject.name )

				-- The source project might not be baked yet, bake it now.
				-- We need this for the context.
				bakeProject( sourceProject, targetProject )

				resolveUses( sourceProject, targetProject, targetBlock )
				
				-- sourceProject include own usage
				if usage then
					resolveUsage( targetProject, targetBlock, usage )
				end

				-- When referring to a project, 'uses' acts like 'links' too.
				table.insert(targetBlock.resolvedUsesLinks, usageName )
				usageType 	    = "project"
				usageScriptPath = sourceProject.script
			elseif usage ~= nil then
				resolveUsage( targetProject, targetBlock, usage )
				usageType       = "usage"
				usageScriptPath = usage.script
			elseif sourceProject ~= nil then
				error( "Project " .. sourceProject.name
					   .. " used itself but declares no usage")
			else
				-- throw an error on Windows and keep going on Linux
				local isLinux = ( package.config:sub(1,1) == '/' )
				local messageText = "Use of "
					  .. "'" .. usageName.. "'"
					  .. ", is not defined as a usage or project in workspace "
					  .. "'" .. targetWorkspace.name .. "'" .. " for " .. targetProject.name
				if isLinux then
					print( messageText )
					return
				else
					error( messageText )
				end
			end

			resolvedUses[usageName] = { ["type"] = usageType, ["script"] = usageScriptPath, ["block"] = usage, ["parent"] = targetProject.name }
		end
	end


---
-- Resolve all uses from a target block in a target project
--

	local function resolveAllUsesInBlock( targetProject, targetBlock )		

		local pushCount = 0
		usesToResolve = {}
		
		for _, usageKey in ipairs(targetBlock.uses) do
			if type(usageKey) == "table" then
				for _, usageName in ipairs(usageKey) do
					pushCount = pushCount + insertUsage( usesToResolve, usageName, targetProject.name )
				end
			else
				pushCount = pushCount + insertUsage( usesToResolve, usageKey, targetProject.name )
			end 
		end

		for _, usageName in ipairs(usesToResolve) do
			resolveUse( targetProject, targetBlock, usageName )
		end
		if pushCount > 0 then
			popUsage(pushCount)
		end
		
	end

--
-- Before baking a project, resolve all the 'uses'
--

	function bakeProjectUsage( prj )

		-- do not resolve "uses" twice
		if prj.resolvedUses == nil then
			-- create table of already resolved uses for this projects
			prj.resolvedUses = {}

			stashStack()

			local blocks = {}
			for k, v in pairs(prj.blocks) do
				blocks[k] = v
			end
			pushUsage( prj.name, '"bake"' )
			for _, block in pairs(blocks) do
				if block.uses then
					block.resolvedUsesLinks = {}
					resolveAllUsesInBlock(prj, block)
					-- When referring to a project, 'uses' acts like 'links' too.
					block[keyLinks] = field.store( fieldLinks, block[keyLinks], fixOrder( block.resolvedUsesLinks ) )
				end
			end
			popUsage()		

			unstashStack()	
		end	
	end
	
--
--	Put the linked projects in the right order
--

	function fixOrder( resolvedUsesLinks )
		if next(resolvedUsesLinks) ~= nil then
			local fixedResolvedUsesLinks = {}
			for i = #resolvedUsesLinks, 1, -1 do
				table.insert( fixedResolvedUsesLinks, resolvedUsesLinks[ i ] )
			end
			return fixedResolvedUsesLinks
		end
		return resolvedUsesLinks
	end

--
-- Register override
--

	premake.override(p.project, "bake", function(base, self)

		bakeProjectUsage(self)

		return base(self)

	end)