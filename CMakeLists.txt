cmake_minimum_required(VERSION 3.17)
project(test)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

add_executable(test src/main.cpp)

target_compile_features(test PUBLIC cxx_std_20)
target_link_libraries(test PRIVATE Qt6::Core)
