cmake_minimum_required(VERSION 3.14)
project(space_invaders
  VERSION 1.0
  DESCRIPTION "Console Space Invader Game"
  LANGUAGES CXX
)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)



set(SOURCES
  src/main.cpp
  src/space_invader.cpp 
)

add_executable(space_invaders ${SOURCES})

target_include_directories(space_invaders
    PRIVATE
      ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(space_invaders Threads::Threads)