cmake_minimum_required(VERSION 2.6)

project(sb6_ch03_ex03)

set(PROGRAM_NAME ogl_interface_block)

# sb6 framework
set(SB6_FRAMEWORK_ROOT ../framework)
set(SB6_FRAMEWORK_GLFW ${SB6_FRAMEWORK_ROOT}/extern/glfw-2.7.6)

include_directories("${SB6_FRAMEWORK_ROOT}/include")
find_library(SB6_LIB sb6 ${SB6_FRAMEWORK_ROOT}/lib)

include_directories("${SB6_FRAMEWORK_GLFW}/include")
find_library(GLFW glfw ${SB6_FRAMEWORK_GLFW}/lib/x11 NO_DEFAULT_PATH)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LINUX")

message("${SB6_LIB} ${GLFW}")

add_executable(${PROGRAM_NAME} main.cpp)
target_link_libraries(${PROGRAM_NAME} ${SB6_LIB} ${GLFW} GL dl)

