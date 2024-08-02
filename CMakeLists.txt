cmake_minimum_required(VERSION 3.0)

project(minesweeper LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-O3 -DNDEBUG)
    elseif (MSVC)
        add_compile_options(/O2 /DNDEBUG)
    endif()
endif()

set(BUILD_SHARED_LIBS OFF)

set(RAYLIB_STATIC ON CACHE BOOL "" FORCE)
add_subdirectory(external/raylib)

set(SOURCE_FILES
    src/main.cpp
    src/raygui.cpp
    src/GameLogic.cpp
    src/Scene.cpp
)

set(HEADER_FILES
    src/GameLogic.h
    src/Scene.h
)

add_executable(minesweeper ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(minesweeper raylib)

target_include_directories(minesweeper PRIVATE external/raygui/src)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(minesweeper PRIVATE -Wall -Wextra)
endif()

if (UNIX)
    target_link_libraries(minesweeper pthread)
elseif (WIN32)
    target_link_libraries(minesweeper -static-libgcc -static-libstdc++)
endif()
