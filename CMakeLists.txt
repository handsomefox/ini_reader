cmake_minimum_required(VERSION 3.21)
project(ini_reader)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

set(SOURCES
        src/IniParser/Parser.cpp
        src/IniParser/Parser.h
        src/IniParser/Token.cpp
        src/IniParser/Token.h
        src/IniParser/Value.cpp src/IniParser/Value.h src/IniParser/Utils.h src/IniParser/Result.cpp src/IniParser/Result.h src/IniParser/SectionValues.cpp src/IniParser/SectionValues.h)

add_executable(ini_reader main.cpp ${SOURCES})

add_custom_command(TARGET ini_reader POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/example.ini"
        $<TARGET_FILE_DIR:ini_reader>)
