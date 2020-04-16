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

# Help emscripten find cross compiled libraries
if(CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    list(APPEND CMAKE_FIND_ROOT_PATH "${PROJECT_SOURCE_DIR}/emscripten_deps")
    list(APPEND CMAKE_SYSTEM_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/emscripten_deps/include")
    list(APPEND CMAKE_SYSTEM_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/emscripten_deps/lib")
    
    # Use all relevant emscripten ports
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[''png'',''bmp'',''jpg'']' -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2 -s USE_LIBJPEG=1 -s USE_LIBPNG=1 -s USE_OGG=1 -s USE_VORBIS=1 -s USE_FREETYPE=1 -s USE_ZLIB=1 -DBUFFERSIZE=4096 -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy -s EXIT_RUNTIME=1")
    
    # Make console logs in browser more useful
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g4 -s ASSERTIONS=2 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=2 --source-map-base http://localhost:8080/ --shell-file ../util/shell_debug.html")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} --shell-file ../util/shell_release.html")
    
    # Generate with complete default html
    SET(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

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
    src/scenes/jump_stage.cpp
    src/scenes/menu.cpp
    )

set(CHARACTER_SOURCES
    src/characters/arrow.cpp
    src/characters/frog.cpp
    src/characters/cloud.cpp
    src/characters/button.cpp
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
    # Surpress cmd window for windows builds
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-subsystem,windows")
endif()

add_executable(${PROJECT_NAME} ${GAME_SOURCES})

if(CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/data@/data/")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} PUBLIC Salmon)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
