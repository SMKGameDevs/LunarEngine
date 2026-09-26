file(GLOB_RECURSE LUNARRUNTIME_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(LunarRuntime
    ${LUNARRUNTIME_SOURCES}
)

target_include_directories(LunarRuntime
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(LunarRuntime PRIVATE Lunar::Engine)

target_compile_options(LunarRuntime PRIVATE
    -Wall -Wextra -Wpedantic
)

# Look for libLunarEngine.so next to the executable.
set_target_properties(LunarRuntime PROPERTIES
    BUILD_RPATH "$ORIGIN"
    INSTALL_RPATH "$ORIGIN"
)
