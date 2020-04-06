cmake_minimum_required(VERSION 3.13)
project(driver VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(include/)

add_executable(driver src/main.cpp)

target_link_libraries(driver PUBLIC include)

# add the binary tree to the search path for include files
# so that we will find library.h
target_include_directories(driver PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/include"
        )

