cmake_minimum_required(VERSION 3.19)
project(json_parser)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

aux_source_directory(example EXEC_LIST)

foreach (item ${EXEC_LIST})
    string(REGEX REPLACE "example/" "" tmp ${item})
    string(REGEX REPLACE ".cpp" "" tmp ${tmp})
    message(STATUS ${tmp})
    add_executable(${tmp} ${item}  common.cpp)
endforeach ()

add_executable(json_parser main.cpp common.cpp)
