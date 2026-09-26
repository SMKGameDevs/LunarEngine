cmake_minimum_required(VERSION 3.24)

project(Lunar
    VERSION 0.1.0
    LANGUAGES CXX
)

# ---- Global settings -------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Hide symbols by default; only LUNAR_API-marked symbols are exported.
# This makes the .so behave like a Windows DLL.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# Put the engine library and runtime executable side by side so the
# runtime can find the engine at load time.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#define debug and release
add_compile_definitions(
        $<$<CONFIG:Debug>:LUNAR_DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:LUNAR_RELEASE>
)

# ---- Projects --------------------------------------------------------------
add_subdirectory(LunarEngine)
add_subdirectory(LunarRuntime)
