-- Premake PSX module
-- By SoapyMan

local p = premake

if not p.modules.psx then

	include ( "_preload.lua" )

	require ("gmake")
	p.modules.psx = {}

	if _ACTION == "gmake" or _ACTION == "gmake2" then
		configuration { "psx" }
			system "psx"
	end
end

return p.modules.psx
