cmake_minimum_required(VERSION 3.17)
project(graphical)

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_DIR}/src/graphical.cpp)
add_executable(${PROJECT_NAME}_test main.cpp src/graphical.cpp src/graphical.h)