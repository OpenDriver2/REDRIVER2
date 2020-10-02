-- Premake PSX module
-- By SoapyMan

	local p = premake
	local api = p.api

--
-- Register the PSX extension
--

	p.PSX = "psx"

	api.addAllowed("system", p.PSX)
	api.addAllowed("architecture", { "mips32" })

	local osoption = p.option.get("os")
	if osoption ~= nil then
		table.insert(osoption.allowed, { "psx",  "PSX" })
	end

	-- add system tags for PSX
	os.systemTags[p.PSX] = { "psx" }

	filter { "system:psx", "kind:ConsoleApp or WindowedApp" }
		targetextension ".exe"
		
	-- overlays
	filter { "system:psx", "kind:Overlay" }
		targetprefix ""
		targetextension ".bin"
		implibextension ".lib"

	filter { "system:psx", "kind:StaticLib" }
		targetprefix ""
		targetextension ".lib"
	
--
-- Register PSX properties
--

-- Compilation properties

	-- TODO
	
	return function(cfg)
		return (cfg.system == p.PSX)
	end
