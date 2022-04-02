cmake_minimum_required(VERSION 3.21)
project(ini_reader)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

set(SOURCES
        src/Ini.cpp
        src/Ini.h
        src/ini_parser.cpp
        src/ini_parser.h
        src/Token.cpp
        src/Token.h)

add_executable(ini_reader main.cpp ${SOURCES})
