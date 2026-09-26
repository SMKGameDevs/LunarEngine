file(GLOB_RECURSE LUNARENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(LunarEngine SHARED
    ${LUNARENGINE_SOURCES}
)
add_library(Lunar::Engine ALIAS LunarEngine)

target_include_directories(LunarEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Defined only while building the engine, so LUNAR_API switches between
# export (building the library) and import (consuming it).
target_compile_definitions(LunarEngine PRIVATE LUNAR_BUILD_DLL)

target_compile_options(LunarEngine PRIVATE
    -Wall -Wextra -Wpedantic
)

set_target_properties(LunarEngine PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
