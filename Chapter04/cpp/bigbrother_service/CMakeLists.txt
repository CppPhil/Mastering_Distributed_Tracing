cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(bigbrother_project VERSION 1.0.0)

set(APP_NAME bigbrother_app)

set(HEADERS
#    people/repository.hpp
    http_controller.hpp)

set(SOURCES
#    people/repository.cpp
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
#  Poco::DataMySQL
)

