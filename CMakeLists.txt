cmake_minimum_required(VERSION 3.14)
project(space_invaders
  VERSION 1.0
  DESCRIPTION "Console Space Invader Game"
  LANGUAGES CXX
)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCES
  src/main.cpp
  src/space_invader.cpp 
)

add_executable(space_invaders ${SOURCES})

target_include_directories(space_invaders
    PRIVATE
      ${PROJECT_SOURCE_DIR}/include
)
