cmake_minimum_required(VERSION 3.17)
project(rang)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

add_executable(rang src/main.cpp
        src/app_state.hpp
        src/register/register.hpp
        src/register/path_register.hpp
        src/app_info.hpp
        src/main_task.hpp
        src/main_task.cpp)

target_include_directories(rang PRIVATE src)
target_compile_features(rang PUBLIC cxx_std_20)
target_link_libraries(rang PRIVATE Qt6::Core)
target_precompile_headers(rang PRIVATE <QtCore>)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/build_timestamp_script.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/build_timestamp_script.cmake"
        @ONLY)

add_custom_target(rang-builddate ALL COMMAND ${CMAKE_COMMAND} -P
        "${CMAKE_CURRENT_BINARY_DIR}/build_timestamp_script.cmake")
target_include_directories(rang PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated/")
add_dependencies(rang rang-builddate)
