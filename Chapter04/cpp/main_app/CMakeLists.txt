cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cpp_exercise1_project VERSION 1.0.0)

#set(LIB_NAME cpp_lib)

### APPLICATION
set(APP_NAME cpp_exercise1_App)

set(APP_HEADERS
    hello.hpp
    say_hello_http_controller.hpp)

set(APP_SOURCES
    hello.cpp
    main.cpp
    say_hello_http_controller.cpp)

add_executable(
    ${APP_NAME}
    ${APP_HEADERS}
    ${APP_SOURCES}
)

target_link_libraries(
    ${APP_NAME}
    PRIVATE
    cpp_lib
    Poco::Foundation
    Poco::DataMySQL
)

