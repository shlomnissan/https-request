cmake_minimum_required(VERSION 3.22)
project(https_request)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_SSL "add support for SSL requests" ON)

include_directories(include)
add_subdirectory(src)