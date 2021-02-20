cmake_minimum_required(VERSION 3.17)
project(TradesKill C)

set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/gl/include)
link_directories(${PROJECT_SOURCE_DIR}/gl/lib)

add_executable(TradesKill global.h main.c mouse.c mouse.h)
target_link_libraries(TradesKill glew32s glfw3 gdi32 opengl32)
