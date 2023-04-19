cmake_minimum_required(VERSION 3.22)
project(https_request)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_SSL "add support for SSL requests" ON)
option(FETCH_TRUSTED_CA "download trusted certificate authorities" ON)

include_directories(include)
add_subdirectory(src)