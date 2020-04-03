cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(main_app_project VERSION 1.0.0)

### APPLICATION
set(APP_NAME main_app)

set(APP_HEADERS
    format_greeting.hpp
    get_person.hpp
    http_controller.hpp
    pick_random_greeting.hpp
    say_hello.hpp
    send_request.hpp)

set(APP_SOURCES
    format_greeting.cpp
    get_person.cpp
    http_controller.cpp
    main.cpp
    pick_random_greeting.cpp
    say_hello.cpp
    send_request.cpp)

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

