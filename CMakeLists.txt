cmake_minimum_required(VERSION 3.19)
project(json_parser)

set(CMAKE_CXX_STANDARD 14)

add_executable(json_parser main.cpp json_token.hpp json_type.hpp json_lexer.hpp)
