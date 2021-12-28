cmake_minimum_required(VERSION 3.17)
project(graphical)

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME} SHARED
        src/graphical.cpp
        src/Incircle.cpp
        src/offset.cpp
        src/size.cpp
        src/rect.cpp
        src/path.cpp)

add_executable(${PROJECT_NAME}_test main.cpp
        src/graphical.cpp
        src/graphical.h
        src/Incircle.cpp
        src/Incircle.h
        src/offset.cpp
        src/offset.h
        src/size.cpp
        src/size.h
        src/rect.cpp
        src/rect.h
        src/path.cpp
        src/path.h)