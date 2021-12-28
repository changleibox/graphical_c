cmake_minimum_required(VERSION 3.17)
project(graphical)

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME} SHARED
        src/graphical.cpp
        src/incircle.cpp
        src/offset.cpp
        src/size.cpp
        src/rect.cpp
        src/path.cpp src/offset_base.cpp src/offset_base.h)

add_executable(${PROJECT_NAME}_test main.cpp
        src/graphical.cpp
        src/graphical.h
        src/incircle.cpp
        src/incircle.h
        src/offset.cpp
        src/offset.h
        src/size.cpp
        src/size.h
        src/rect.cpp
        src/rect.h
        src/path.cpp
        src/path.h)