-- premake-androidndk - a multi-ABI, multi-language ndk-build Android.mk generator for Premake.
-- Originally written by Vitaliy <Triang3l> Kuzmin.
-- See README.md for detailed usage and design information.
-- Available under the Unlicense (see UNLICENSE.txt) or the BSD 3-Clause "New" or "Revised" License (see LICENSE.txt).

return {
	"_preload.lua",
	"androidndk.lua",
	"androidndk_project.lua",
	"androidndk_workspace.lua",
};
