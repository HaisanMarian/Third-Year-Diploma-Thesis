cmake_minimum_required(VERSION 3.11)
project(diploma_marian)

set(CMAKE_CXX_STANDARD 14)

# Політика для уникнення попереджень про завантаження
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# Fetch Raylib
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)

# Вимикаємо зайве в Raylib для швидкості
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

# Цей рядок вирішує вашу помилку "Compatibility with CMake < 3.5 has been removed"
set(CMAKE_POLICY_DEFAULT_CMP0000 NEW) 

FetchContent_MakeAvailable(raylib)

include_directories(.)

add_executable(diploma_marian
        LineSegment.cpp
        LineSegment.h
        main.cpp
        Point.cpp
        Point.h
        main.cpp
        main.cpp
        main.cpp)

# Лінкуємо Raylib
target_link_libraries(diploma_marian raylib)

if(UNIX AND NOT APPLE)
    target_link_libraries(diploma_marian m pthread dl rt X11)
endif()


