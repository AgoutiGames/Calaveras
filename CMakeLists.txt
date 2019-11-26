project("Calaveras")

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT MSVC)
    # Add custom profile build type
    set (CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_RELEASE} -pg" CACHE STRING
        "Flags used by the C compiler during PROFILE builds."
        FORCE )
    set (CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_RELEASE} -pg" CACHE STRING
        "Flags used by the C++ compiler during PROFILE builds."
        FORCE )
    set (CMAKE_EXE_LINKER_FLAGS_PROFILE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -pg" CACHE STRING
        "Flags used for linking binaries during PROFILE builds."
        FORCE )
    set (CMAKE_SHARED_LINKER_FLAGS_PROFILE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -pg" CACHE STRING
        "Flags used by the shared libraries linker during maintainer builds."
        FORCE )
    MARK_AS_ADVANCED(
        CMAKE_C_FLAGS_PROFILE
        CMAKE_CXX_FLAGS_PROFILE
        CMAKE_EXE_LINKER_FLAGS_PROFILE
        CMAKE_SHARED_LINKER_FLAGS_PROFILE)
    # Update the documentation string of CMAKE_BUILD_TYPE for GUIs
    SET( CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Profile."
        FORCE )
endif()

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wfatal-errors")
endif()

set(LIB_TARGET ON CACHE BOOL "Build library version without event support")
add_subdirectory(salmon)

# Search library in libs folder residing beneath the bin folder
set(CMAKE_INSTALL_RPATH "$ORIGIN/../libs")

# Thic can/should get more granular over time
set(CORE_SOURCES
    src/core/main.cpp
    src/core/game_character.cpp
    src/core/game_scene.cpp
    src/core/scene_manager.cpp
    )

set(SCENE_SOURCES
    src/scenes/environment.cpp
    src/scenes/jump_stage.cpp
    src/scenes/menu.cpp
    )

set(CHARACTER_SOURCES
    src/characters/arrow.cpp
    src/characters/frog.cpp
    src/characters/cloud.cpp
    src/characters/button.cpp
    src/characters/player.cpp
    src/characters/small_enemy.cpp
    )

set(GAME_SOURCES
        ${CORE_SOURCES}
        ${SCENE_SOURCES}
        ${CHARACTER_SOURCES}
    )

# Nasty hack making possible to statically link twice
# This circumvents having to ship huge libgcc and libstd++ lib as dynamic libs
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-allow-multiple-definition")
endif()

add_executable(${PROJECT_NAME} ${GAME_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} PUBLIC Salmon)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
# Works only with CMake version 3.13+
install(TARGETS Salmon DESTINATION libs)
