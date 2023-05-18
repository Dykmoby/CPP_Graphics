workspace "CPP_Graphics"
	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

	flags {
		"MultiProcessorCompile"
	}
	startproject "CPP_Graphics"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SFML"] = "vendor/SFML/include"
IncludeDir["YAML_CPP"] = "vendor/YAML_CPP/include"

LibDir = {}
LibDir["SFML"] = "vendor/SFML/lib"
LibDir["YAML_CPP"] = "vendor/YAML_CPP/lib"

group "Dependencies"
-- Includes go here
group ""


project "CPP_Graphics"
	location "CPP_Graphics"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	debugdir ("bin/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"CPP_Graphics/src",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.YAML_CPP}",
	}


	libdirs { 
		"%{LibDir.SFML}",
		"%{LibDir.YAML_CPP}",
	}

	links {
		"openal32",
		"flac",
		"vorbisenc",
		"vorbisfile",
		"vorbis",
		"ogg",
		"opengl32",
		"freetype",
		"winmm",
		"gdi32"
	}

	defines {
		--"SFML_STATIC",
		--"SFML_USE_STATIC_STD_LIBS",
		--"SFML_STATIC_LIBRARIES"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		postbuildcommands {
			'{COPYFILE} "../vendor/SFML/bin/openal32.dll" "%{cfg.targetdir}/"',
			'{COPYFILE} "../vendor/SFML/bin/debug/**-d-2.dll" "%{cfg.targetdir}/"',
			'{MKDIR} "%{cfg.targetdir}/fonts/"',
			'{COPYFILE} "../CPP_Graphics/fonts/**.ttf" "%{cfg.targetdir}/fonts/"',
		}
		libSuffix = "-d"
		links { 
			"sfml-graphics" .. libSuffix,
			"sfml-window" .. libSuffix,
			"sfml-system" .. libSuffix,
			"yaml-cppd"
		}

	filter "configurations:Release"
		optimize "On"
		postbuildcommands {
			'{COPYFILE} "../vendor/SFML/bin/openal32.dll" "%{cfg.targetdir}/"',
			'{COPYFILE} "../vendor/SFML/bin/release/**-2.dll" "%{cfg.targetdir}/"',
			'{MKDIR} "%{cfg.targetdir}/fonts/"',
			'{COPYFILE} "../CPP_Graphics/fonts/**.ttf" "%{cfg.targetdir}/fonts/"',
		}
		libSuffix = ""
		links { 
			"sfml-graphics" .. libSuffix,
			"sfml-window" .. libSuffix,
			"sfml-system" .. libSuffix,
			"yaml-cpp"
		}


