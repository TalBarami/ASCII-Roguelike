cmake_minimum_required(VERSION 3.5)
project(untitled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Enemy.cpp GameSystem.cpp Level.cpp Player.cpp)
add_executable(Roguelike ${SOURCE_FILES})