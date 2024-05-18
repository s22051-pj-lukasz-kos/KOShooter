# project declaration
project(KOShooter)
cmake_minimum_required(VERSION 3.1)

# SDL libraries
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)

# C++ versions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# compile options
add_compile_options(-Wall -Wextra -Werror -Warray-bounds -g)

#Add the include directories of the (found) libraries.
include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src
)

# source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# executable file
add_executable(${PROJECT_NAME} ${SOURCES})

# link libraries
target_link_libraries(
        ${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        m
)
