cmake_minimum_required(VERSION 3.25)

file(GLOB INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include")
file(GLOB SOURCE_FILES "*.cc")

add_executable(http_request_ssl ${INCLUDE_FILES} ${SOURCE_FILES})

if(EXPRESS_USE_SSL)
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/ca-bundle.crt")
        message(
            FATAL_ERROR
            "ca-bundle.crt file is missing in the root directory. "
            "You can download a trusted CA certificate store from "
            "https://curl.se/docs/caextract.html"
        )
    endif()

    find_package(OpenSSL REQUIRED)
    target_compile_definitions(http_request_ssl PUBLIC EXPRESS_USE_SSL)
    target_link_libraries(http_request_ssl PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
    )
endif()
