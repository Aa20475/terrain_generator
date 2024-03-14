cmake_minimum_required(VERSION 3.21)

project(terrain-generator)

set(EXEC generator)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES src/*.cpp)

add_executable(${EXEC} ${SOURCES})