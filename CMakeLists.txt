cmake_minimum_required(VERSION 3.17)
project(rang)

find_package(Qt6 REQUIRED COMPONENTS Core Network)
qt_standard_project_setup()

add_library(rang-lib
        src/main_task.cpp
        src/app_state.cpp
        src/buffer/buffer.cpp
        src/buffer/file_list_buffer.cpp
        src/register/register.cpp
        src/register/path_register.cpp
        src/buffer/file_info_buffer.cpp
        src/renderer/renderer.cpp
        src/renderer/terminal_renderer.cpp
        src/buffer/text_file_preview_buffer.cpp
        src/renderer/text_renderer.cpp
        src/ipc/listener.cpp
        src/client_task.cpp
        src/ipc/connection_handler.cpp
        src/ipc/messages/message.cpp
        src/ipc/messages/set_current_dir_message.cpp
        src/ipc/connection_to_client_handler.cpp
        src/buffer/path_buffer.cpp)

target_include_directories(rang-lib PUBLIC include)
target_compile_features(rang-lib PRIVATE cxx_std_20)
target_link_libraries(rang-lib PUBLIC Qt6::Core Qt6::Network)
target_precompile_headers(rang-lib PUBLIC <QtCore> <QtNetwork>)

add_executable(rang src/main.cpp)
target_compile_features(rang PRIVATE cxx_std_20)
target_link_libraries(rang PRIVATE rang-lib)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/build_timestamp_script.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/build_timestamp_script.cmake"
        @ONLY)

add_custom_target(rang-builddate ALL COMMAND ${CMAKE_COMMAND} -P
        "${CMAKE_CURRENT_BINARY_DIR}/build_timestamp_script.cmake")
target_include_directories(rang-lib PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/generated/")
add_dependencies(rang-lib rang-builddate)

option(ENABLE_TESTING "Enable Catch2 tests" OFF)

if(ENABLE_TESTING) 
        enable_testing()
        add_subdirectory(test)
endif()
