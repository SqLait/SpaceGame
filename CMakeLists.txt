cmake_minimum_required(VERSION 3.14)
project(SpaceShooter C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Optional flag to enable Windows cross-compilation
option(Wind "Build for Windows using MinGW" OFF)

if (Wind)
    message(STATUS "▶ Windows cross-compilation enabled (Wind=ON)")

    if (NOT CMAKE_TOOLCHAIN_FILE)
        message(WARNING "⚠ Wind is ON but no toolchain file specified! Add -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-mingw.cmake")
    endif()

    add_compile_definitions(PLATFORM_WINDOWS)
    # Set Windows-specific output dir
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/win-bin)
else()
    message(STATUS "▶ Native build (Linux)")
    add_compile_definitions(PLATFORM_LINUX)
    # Default native output dir
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# Include headers from your own project
include_directories(include)
file(GLOB SOURCES "src/*.c")

# Use FetchContent to get raylib
include(FetchContent)
message(STATUS "Fetching raylib from GitHub...")
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
)
FetchContent_MakeAvailable(raylib)
message(STATUS "raylib has been fetched and made available.")

# Set warnings and build flags
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic --debug)
endif()

# Create your game executable
add_executable(main ${SOURCES})
target_link_libraries(main raylib)

# Add raylib include directory for clangd and tools
target_include_directories(main PRIVATE ${raylib_SOURCE_DIR}/src)

# Copy assets after build
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

