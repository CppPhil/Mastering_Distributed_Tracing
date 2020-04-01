cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(formatter_project VERSION 1.0.0)

set(APP_NAME formatter_app)

set(HEADERS
    format_greeting.hpp
    http_controller.hpp)

set(SOURCES
    format_greeting.cpp
    http_controller.cpp
    main.cpp)

add_executable(
  ${APP_NAME}
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries(
  ${APP_NAME}
  PRIVATE
  cpp_lib
)

