workspace "kGeneticAlgorithm"
	architecture "x86_64"
	startproject "kGeneticAlgorithm"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["ImGui"] = "kGeneticAlgorithm/ThirdParty/imgui"
IncludeDir["SDL2"] = "kGeneticAlgorithm/ThirdParty/SDL2/include"
IncludeDir["SDL2_image"] = "kGeneticAlgorithm/ThirdParty/SDL2_image/include"
IncludeDir["GLAD"] = "kGeneticAlgorithm/ThirdParty/glad/include"
IncludeDir["SDL-gpu"] = "kGeneticAlgorithm/ThirdParty/SDL_gpu/include"

group "Dependencies"
	include "kGeneticAlgorithm/ThirdParty/imgui"
	include "kGeneticAlgorithm/ThirdParty/glad"

group ""

project "kGeneticAlgorithm"
	location "kGeneticAlgorithm"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
        "%{prj.name}/src",
		"%{prj.name}/src/Engine",
		"%{prj.name}/ThirdParty/spdlog/include",
		"%{IncludeDir.ImGui}",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.SDL2_image}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.SDL-gpu}"
	}

	libdirs
	{
		"%{prj.name}/ThirdParty/SDL2/lib/x64/",
		"%{prj.name}/ThirdParty/SDL2_image/lib/x64/",
		"%{prj.name}/ThirdParty/SDL2_gpu/lib/Release/"
	}

	links 
	{ 
		"GLAD",
        "ImGui",
        "SDL2",
        "SDL2_image",
        "SDL2main",
		"SDL2test",
		"SDL2_gpu.lib",
		"SDL2_gpu_s.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

    filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DIST"
		runtime "Release"
		optimize "on"