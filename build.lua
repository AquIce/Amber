workspace "Amber"
	configurations { "DEBUG", "RELEASE" }
	platforms { "run", "static-build", "dynamic-build" }
	startproject "AmberEngine"

	project "ARE"
	    language "C++"
		location "build/"
		entrypoint "main"

		files {
		    "src/are_main.cpp",
		    "src/ARE/*.cpp",
		    "src/include/ARE/*.hpp"
		}

		libdirs {
	       "bin"
		}

		links {
		    "mingw32",
		    "SDL2"
		}

		includedirs {
    		"src/include",
    	}

    	filter "action:gmake"
            buildoptions { "-Wall", "-Werror", "-Wpedantic", "-g3" }

    	filter "platforms:run"
    		kind "ConsoleApp"

    	filter "platforms:static-build"
    		kind "StaticLib"
    		removefiles { "adl_main.cpp" }

    	filter "platforms:dynamic-build"
    		kind "SharedLib"
    		removefiles { "adl_main.cpp" }

    	filter "configurations:debug"
    	    defines { "DEBUG" }
    		symbols "On"

    project "AmberEngine"
    	language "C++"
    	location "build/"
        kind "ConsoleApp"

    	files {
    		"src/main.cpp",
    		"src/Amber/**.cpp",
    		"src/include/Amber/**.hpp",
    	}

    	includedirs {
    		"src/include",
            "vendor/spdlog/include"
    	}

    	filter "action:gmake"
            buildoptions { "-Wall", "-Werror", "-Wpedantic", "-g3" }

    	filter "configurations:debug"
    	    defines { "DEBUG" }
    		symbols "On"