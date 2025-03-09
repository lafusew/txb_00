cmake_minimum_required(VERSION 3.29)
project(txb__00)

set(CMAKE_CXX_STANDARD 20)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# BearLibTerminal: Add path to your prebuilt binaries
set(BEARLIBTERMINAL_DIR "lib/bearlibterminal")

# Include the BearLibTerminal headers and link the dynamic library
include_directories(${BEARLIBTERMINAL_DIR}/include)
link_directories(${BEARLIBTERMINAL_DIR}/lib/Linux64)

include(FetchContent)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if(NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if(NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES
        OFF
        CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

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
add_executable(
  ${CMAKE_PROJECT_NAME}
  src/main.cpp
  src/core/Game.cpp
  src/utils/AStar.cpp
  src/world/Area.cpp
  src/world/AreaManager.cpp
  src/systems/Movements.cpp
  src/systems/Rendering.cpp)

set(raylib_VERBOSE 1)
# Linking required libraries
target_link_libraries(${PROJECT_NAME} BearLibTerminal)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${CMAKE_PROJECT_NAME} flecs::flecs_static)

if(APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
