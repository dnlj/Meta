require "build/action_clean"
require "build/action_deps"

--------------------------------------------------------------------------------
-- Constants
--------------------------------------------------------------------------------
local PROJECT_NAME = "Meta"
local CONFIG_TYPE_STR = '%{string.lower(string.match(cfg.buildcfg, "^([^_]+)"))}'

--------------------------------------------------------------------------------
-- The files and folders to delete when the "clean" action is run.
--------------------------------------------------------------------------------
action_clean_directories = {
	"./.vs",
	"./bin",
	"./obj",
	"./docs",
}	

action_clean_files = {
	-- Visual Studio files
	"./".. PROJECT_NAME ..".vcxproj",
	"./".. PROJECT_NAME ..".vcxproj.filters",
	"./".. PROJECT_NAME ..".vcxproj.user",
	"./".. PROJECT_NAME .."Test.vcxproj",
	"./".. PROJECT_NAME .."Test.vcxproj.filters",
	"./".. PROJECT_NAME .."Test.vcxproj.user",
	"./".. PROJECT_NAME .."Workspace.sln",
	"./".. PROJECT_NAME .."Workspace.VC.db",
	"./".. PROJECT_NAME .."Workspace.VC.VC.opendb"
}


--------------------------------------------------------------------------------
-- The main premake settings
--------------------------------------------------------------------------------
workspace(PROJECT_NAME .."Workspace")
	configurations {"Debug", "Release"}
	platforms {"Windows_x64"}
	characterset "Unicode"
	kind "ConsoleApp"
	language "C++"
	rtti "Off"
	warnings "Default"
	flags {
		"FatalWarnings",
		"MultiProcessorCompile",
	}
	targetdir "./bin/%{cfg.buildcfg}_%{cfg.platform}"
	objdir "./obj/%{prj.name}/%{cfg.buildcfg}_%{cfg.platform}"
	startproject(PROJECT_NAME)
	
	filter "action:vs*"
		systemversion "10.0.16299.0"
		buildoptions{
			"/std:c++latest", -- Use the latest version of C++
			"/wd4996", -- Disable some warnings about things Visual Studio has taken apon itself to deem "deprecated"
		}
	
	filter "platforms:Windows_x64"
        architecture "x64"
		defines {string.upper(PROJECT_NAME) .."_OS_WINDOWS"}
		
	filter "configurations:Debug*"
		symbols "On"
		defines {"DEBUG"}
	
	filter "configurations:Release*"
		optimize "Full"
		defines {"RELEASE"}
		flags {"LinkTimeOptimization"}

--------------------------------------------------------------------------------
-- Engine
--------------------------------------------------------------------------------
project(PROJECT_NAME)
	kind "None"

project("*")
	files {
		"./include/**",
	}
	
	includedirs {
		"./include",
	}

--------------------------------------------------------------------------------
-- Test
--------------------------------------------------------------------------------
project(PROJECT_NAME .."Test")
	defines {"RUNNING_TESTS"}

	files {
		"./test/**",
	}
	
	includedirs {
		"./deps/googletest/googlemock/include",
		"./deps/googletest/googletest/include",
	}
	
	libdirs {
		"./deps/googletest/lib/".. CONFIG_TYPE_STR,
	}
	
	filter {"platforms:Windows_x64", "configurations:Debug*"}
		links {
			"gtestd.lib",
			"gmockd.lib",
		}
		
	filter {"platforms:Windows_x64", "configurations:Release*"}
		links {
			"gtest.lib",
			"gmock.lib",
		}
