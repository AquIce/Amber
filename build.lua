workspace "Aqu1"
	configurations { "DEBUG", "RELEASE" }
	platforms { "run", "static-build", "dynamic-build" }
	startproject "AquEngine"

project "AquEngine"
	language "C++"
	location "build/"
	entrypoint "main"

	files {
		"src/main.cpp",
		"src/aquengine/**/*.cpp",
		"src/include/**/*.hpp",
	}

	includedirs {
		"src/include",
	}

	filter { "action:gmake" }
        buildoptions { "-Wall", "-Werror", "-Wpedantic", "-g3" }

	filter { "platforms:run" }
		kind "ConsoleApp"

	filter { "platforms:static-build" }
		kind "StaticLib"
		removefiles { "main.cpp" }

	filter { "platforms:dynamic-build" }
		kind "SharedLib"
		removefiles { "main.cpp" }

	filter { "configurations:debug" }
	    defines { "DEBUG" }
		symbols "On"
