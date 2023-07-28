-- premake5.lua

workspace "BFCD"
    configurations { "Debug", "Release" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "BFCD"
    location "BFCD"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    -- Project files:
    files
    {
        "BFCD/src/**.h",
        "BFCD/src/**.cpp"
    }

    -- THIS IS NOT NEEDED, BUT MIGHT BE IF PROJECT DOES NOT COMPILE...
    -- Boost files:
    --files
    --{
    --    "BFCD/vendor/boost_1_82_0/libs/iostreams/src/**.cpp"
    --}

    includedirs
    {
        "%{prj.name}/vendor/boost_1_82_0"
    }

    filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

        defines
        {
            "BOOST_IOSTREAMS_NO_LIB"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"