workspace "TinyEngine"
	architecture "x64"
	startproject "SandBox"

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
IncludeDir["ImGui"] = "TinyEngine/vecdor/imgui"
IncludeDir["glm"] = "TinyEngine/vecdor/glm"

include "TinyEngine/vecdor/GLFW"
include "TinyEngine/vecdor/Glad"
include "TinyEngine/vecdor/imgui"


project "TinyEngine"
	location "TinyEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "TinyPch.h"
	pchsource "TinyEngine/src/TinyPch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vecdor/glm/glm/**.hpp",
		"%{prj.name}/vecdor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/vecdor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		--staticruntime "On"
		systemversion "latest"

		defines
		{
			"TI_PLATFORM_WINDOWS",
			"TI_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/SandBox/\"")
		}

	filter "configurations:Debug"
		defines "TI_DEGUB"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TI_DIST"
		runtime "Release"
		optimize "On"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

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
		"TinyEngine/vecdor/imgui",
		"TinyEngine/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"TinyEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		--staticruntime "On"
		systemversion "latest"

		defines
		{
			"TI_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "TI_DEGUB"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TI_DIST"
		runtime "Release"
		optimize "On"