solution "WorldGenLib"
	configurations { "debug", "release" }

project "worldgen"
	kind "SharedLib"
	language "C++"
	files { "src/**" }
	links { "noise" }
	objdir "build/obj"
	buildoptions { "-std=c++11" }
	defines { "WG_BUILD_OPS" }

	configuration "debug"
		flags { "Symbols", "ExtraWarnings" }

	configuration "release"
		flags { "Optimize" }
