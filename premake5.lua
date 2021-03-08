workspace "TinyEngine"
	architecture "x64"
	startproject "SandBox"
	cppdialect "C++17"

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
	kind "StaticLib"
	language "C++"
	staticruntime "on"

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
		systemversion "latest"

		defines
		{
			"TI_PLATFORM_WINDOWS",
			"TI_BUILD_DLL"
		}

		--postbuildcommands
		--{
			--("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/SandBox/\"")
		--}

	filter "configurations:Debug"
		defines "TI_DEGUB"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TI_DIST"
		runtime "Release"
		optimize "on"

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		systemversion "latest"

		defines
		{
			"TI_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "TI_DEGUB"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TI_DIST"
		runtime "Release"
		optimize "on"