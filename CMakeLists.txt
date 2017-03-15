cmake_minimum_required(VERSION 3.6)
project(LZW)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp lzwCompress.cpp lzwCompress.h)
add_executable(LZW ${SOURCE_FILES})