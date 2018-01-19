cmake_minimum_required(VERSION 2.8)
project(debuggers C CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Widgets REQUIRED)

add_subdirectory(network_interface_debugger)
