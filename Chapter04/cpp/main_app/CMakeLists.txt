cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(main_app_project VERSION 1.0.0)

### APPLICATION
set(APP_NAME main_app)

set(APP_HEADERS
    http_controller.hpp)

set(APP_SOURCES
    http_controller.cpp
    main.cpp)

add_executable(
    ${APP_NAME}
    ${APP_HEADERS}
    ${APP_SOURCES}
)

target_link_libraries(
    ${APP_NAME}
    PRIVATE
    cpp_lib
)

