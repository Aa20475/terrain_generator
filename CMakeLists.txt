cmake_minimum_required(VERSION 3.21)

project(terrain-generator)

set(EXEC generator)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES src/*.cpp)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(GLFW3_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(GLFW3 3.3 REQUIRED)

if(GLFW3_FOUND)
  include_directories(${GLFW3_INCLUDE_DIR})
  link_libraries(${GLFW3_LIBRARY})
endif()

add_executable(${EXEC} ${SOURCES})
