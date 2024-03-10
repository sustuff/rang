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
        src/main_task.cpp
        src/app_state.cpp
        src/buffer/buffer.cpp
        src/buffer/buffer.hpp
        src/buffer/file_list_buffer.cpp
        src/buffer/file_list_buffer.hpp
        src/register/path_register.cpp
        src/buffer/file_info_buffer.cpp
        src/buffer/file_info_buffer.hpp
        src/renderer/renderer.cpp
        src/renderer/renderer.hpp
        src/renderer/terminal_renderer.cpp
        src/renderer/terminal_renderer.hpp
        src/buffer/text_file_preview_buffer.cpp
        src/buffer/text_file_preview_buffer.hpp
        src/renderer/text_renderer.cpp
        src/renderer/text_renderer.hpp)

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
