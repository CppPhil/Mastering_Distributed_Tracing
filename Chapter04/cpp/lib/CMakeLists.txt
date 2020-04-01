cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cpp_lib_project VERSION 1.0.0)

### OBJECT LIBRARY
set(LIB_NAME cpp_lib)

set(LIB_HEADERS
    model/person.hpp
    tracing/init.hpp)

set(LIB_SOURCES
    model/person.cpp
    tracing/init.cpp)

add_library(
    ${LIB_NAME}
    OBJECT
    ${LIB_HEADERS}
    ${LIB_SOURCES}
)

target_link_libraries(
    ${LIB_NAME}
    PUBLIC
    Threads::Threads
    jaegertracing
    drogon
    Poco::JSON
    Poco::Foundation
)

target_include_directories(
    ${LIB_NAME}
    PUBLIC
    ${Chapter04_project_SOURCE_DIR}/external/philslib/include
    ${Chapter04_project_SOURCE_DIR}/external/optional/include
    ${Chapter04_project_SOURCE_DIR}/external/expected/include
)

target_include_directories(
    ${LIB_NAME}
    PUBLIC
    ${cpp_lib_project_SOURCE_DIR}
)

