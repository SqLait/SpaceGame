cmake_minimum_required(VERSION 3.14)
project(SpaceShooter C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include headers from your own project
include_directories(include)
file(GLOB SOURCES "src/*.c")

# Use FetchContent to get raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
)

# Let raylib build as a subproject
FetchContent_MakeAvailable(raylib)

# Create your game executable
add_executable(main ${SOURCES})

# After FetchContent_MakeAvailable(raylib)
target_link_libraries(main raylib)

# Also explicitly add raylib include directories for clangd
target_include_directories(main PRIVATE ${raylib_SOURCE_DIR}/src)

