cmake_minimum_required(VERSION 3.5)

project(serviceb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(serviceb main.cpp)

install(TARGETS serviceb
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
