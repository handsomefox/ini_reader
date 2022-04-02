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

add_custom_command(TARGET ini_reader POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/example.ini"
        $<TARGET_FILE_DIR:ini_reader>)
