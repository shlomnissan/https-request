cmake_minimum_required(VERSION 3.22)

file(GLOB INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include")
file(GLOB SOURCE_FILES "*.cc")

add_executable(https_request ${INCLUDE_FILES} ${SOURCE_FILES})

if(USE_SSL)
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/ca-bundle.crt")
        message(
            FATAL_ERROR
            "ca-bundle.crt file is missing in the root directory. "
            "You can download a trusted CA certificate store from "
            "https://curl.se/docs/caextract.html"
        )
    endif()

    add_custom_command(
        TARGET https_request POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/ca-bundle.crt
        ${CMAKE_CURRENT_BINARY_DIR}/ca-bundle.crt
    )

    if(APPLE)
        set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
        set(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")
    endif()

    include(FetchContent)
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG origin/master
        GIT_SHALLOW true
    )

    FetchContent_GetProperties(fmt)
    
    if(NOT fmt_POPULATED)
        FetchContent_Populate(fmt)
        add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
    endif()

    find_package(OpenSSL REQUIRED)
    target_compile_definitions(https_request PUBLIC USE_SSL)
    target_link_libraries(https_request PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
        fmt::fmt
    )
endif()
