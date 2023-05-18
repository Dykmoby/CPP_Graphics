project "yaml-cpp"
	kind "StaticLib"
	language "C++"
	
	targetdir ("lib/")
	objdir ("obj/")

	files {
		"src/**.h",
		"src/**.cpp"
	}
	
	includedirs {
		"include/"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
