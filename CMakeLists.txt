cmake_minimum_required(VERSION 3.21)

project(terrain-generator)

set(EXEC generator)
set(CMAKE_CXX_STANDARD 11)
set(DEPENDENCY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps)

include_directories(include)

file(GLOB SOURCES src/*.cpp)

# GLFW3
include_directories(${DEPENDENCY_PATH}/GLFW/include)
link_libraries(${DEPENDENCY_PATH}/GLFW/lib/glfw3.lib)

# GLEW
set(GLEW_USE_STATIC_LIBS TRUE)
set(GLEW_ROOT ${DEPENDENCY_PATH}/GLEW)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
add_definitions(-DGLEW_STATIC)


# OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARIES})

add_executable(${EXEC} ${SOURCES})
