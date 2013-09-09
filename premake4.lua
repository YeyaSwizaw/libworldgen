solution "WorldGenLib"
	configurations { "debug", "release" }

project "worldgen"
	kind "SharedLib"
	language "C++"
	files { "src/**" }
	links { "noise" }
	objdir "build/obj"
	buildoptions { "-std=c++11" }

	configuration "debug"
		flags { "Symbols", "ExtraWarnings" }

	configuration "release"
		flags { "Optimize" }
