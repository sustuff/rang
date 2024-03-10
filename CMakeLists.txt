cmake_minimum_required(VERSION 3.17)
project(test)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

add_subdirectory(src)
