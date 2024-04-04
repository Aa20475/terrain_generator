cmake_minimum_required(VERSION 3.21)

project(terrain-generator)

set(EXEC generator)
set(CMAKE_CXX_STANDARD 11)
set(DEPENDENCY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps)
set(VENDOR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor)

include_directories(include)
include_directories(src)
include_directories(${VENDOR_PATH})

file(GLOB SOURCES src/*.cpp)
list(APPEND SOURCES ${VENDOR_PATH}/stb_image/stb_image.cpp)

# Append the list of files matching src/tests/*.cpp to SOURCES
file(GLOB TEST_SOURCES src/tests/*.cpp)
list(APPEND SOURCES ${TEST_SOURCES})

message(${SOURCES})

#imgui
file(GLOB IMGUI_SOURCES ${VENDOR_PATH}/imgui/*) 
add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})

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

target_link_libraries(${EXEC} PUBLIC ImGui)


# Copy the resource directory to binary directory
add_custom_command(TARGET ${EXEC} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
        $<TARGET_FILE_DIR:${EXEC}>/res)
