cmake_minimum_required(VERSION 3.15)

project(Forward_List)

set(CMAKE_CXX_STANDARD 20)

add_executable(Forward_List Src/main.cpp Headers/Forward_list.hpp Headers/Forward_List.tpp)
