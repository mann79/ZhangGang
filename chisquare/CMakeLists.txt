cmake_minimum_required(VERSION 3.13)
project(chisquare VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(chisquare src/library.cpp src/library.h)