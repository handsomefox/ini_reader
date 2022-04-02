cmake_minimum_required(VERSION 3.21)
project(ini_reader)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        Ini.cpp
        Ini.h
        IniParser.cpp
        IniParser.h
        Token.cpp
        Token.h)

add_executable(ini_reader main.cpp ${SOURCES})
