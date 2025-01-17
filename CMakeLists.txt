cmake_minimum_required(VERSION 3.29)
project(farm_game)

set(CMAKE_CXX_STANDARD 20)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# BearLibTerminal: Add path to your prebuilt binaries
set(BEARLIBTERMINAL_DIR "lib/bearlibterminal")

# Include the BearLibTerminal headers and link the dynamic library
include_directories(${BEARLIBTERMINAL_DIR}/include)
link_directories(${BEARLIBTERMINAL_DIR}/lib/Linux64)

include(FetchContent)

set(FLECS_VERSION v4.0.2)
find_package(flecs QUIET) # QUIET or REQUIRED
if(NOT flecs_FOUND) # If there's none, fetch and build flecs
  FetchContent_Declare(
    flecs
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/SanderMertens/flecs/archive/refs/tags/${FLECS_VERSION}.tar.gz
  )
  FetchContent_GetProperties(flecs)
  if(NOT flecs_POPULATED) # Have we downloaded flecs yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(flecs)
  endif()
endif()

# Our own header files
include_directories(include)

# Our Project
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

# Linking required libraries
target_link_libraries(${PROJECT_NAME} BearLibTerminal)
target_link_libraries(${CMAKE_PROJECT_NAME} flecs::flecs_static)
