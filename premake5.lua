

configuration "macosx"
    -- OS X frameworks need the extension to be handled properly
    links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework" }


workspace "GameEngine"
    configurations { "Debug", "Release", "Dist" }
    architecture "x64"
    targetdir "bin/"
    objdir "bin/obj/"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        flags "FatalWarnings"
        optimize "On"

    filter "configurations:Dist"
        defines { "DIST" }
        flags "FatalWarnings"
        optimize "On"


    project "Engine"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        buildoptions { "-Wall" }
        -- location "Engine"

        files {
            "Engine/**.h",
            "Engine/**.hpp",
            "Engine/**.cpp",
            "vendor/stb/**.cpp",
            "vendor/imgui/*.cpp",
            "vendor/imgui/examples/imgui_impl_glfw.cpp",
            "vendor/imgui/examples/imgui_impl_opengl3.cpp",
        }
        includedirs {
            "vendor/spdlog/include",
            "vendor/glfw/include",
            "vendor/glad",
            "vendor/imgui",
            "vendor/glm",
            "vendor/stb"
        }
        libdirs {
            "vendor/glfw/build",
            "vendor/glad"
        }
        -- links { "glfw3", "glad" }


    project "EngineTests"
        kind "WindowedApp"
        language "C++"
        cppdialect "C++17"
        buildoptions { "-Wall" }

        files {
            "EngineTests/**.h",
            "EngineTests/**.hpp",
            "EngineTests/**.cpp",
        }
        includedirs {
            "vendor/spdlog/include",
            "vendor/glfw/include",
            "vendor/glad",
            "vendor/imgui",
            "vendor/glm",
            "vendor/stb"
        }
        libdirs {
            "vendor/glfw/build",
            "vendor/glad"
        }
        links { "Engine", "glfw3", "glad" }
