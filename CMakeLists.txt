cmake_minimum_required(VERSION 4.2)
project(StarxEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")
include_directories(${PROJECT_SOURCE_DIR}$/src)
include_directories(${PROJECT_SOURCE_DIR}$/matrixsrc)
include_directories(${PROJECT_SOURCE_DIR}$/network)
add_executable(StarxEngine
        main.cpp
        src/graph.cpp
        src/node.cpp)
