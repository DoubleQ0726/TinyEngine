workspace "TinyEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "TinyEngine/vecdor/GLFW/include"
IncludeDir["Glad"] = "TinyEngine/vecdor/Glad/include"

include "TinyEngine/vecdor/GLFW"
include "TinyEngine/vecdor/Glad"

project "TinyEngine"
	location "TinyEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "TinyPch.h"
	pchsource "TinyEngine/src/TinyPch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vecdor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TI_PLATFORM_WINDOWS",
			"TI_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/SandBox")
		}

	filter "configurations:Debug"
		defines "TI_DEGUB"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "TI_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "TI_DIST"
		buildoptions "/MD"
		optimize "On"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"TinyEngine/vecdor/spdlog/include",
		"TinyEngine/src"
	}

	links
	{
		"TinyEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TI_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "TI_DEGUB"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "TI_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "TI_DIST"
		buildoptions "/MD"
		optimize "On"