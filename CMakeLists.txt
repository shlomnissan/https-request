cmake_minimum_required(VERSION 3.25)
project(http_request_ssl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(EXPRESS_USE_SSL "add support for SSL requests" ON)

include_directories(include)
add_subdirectory(src)