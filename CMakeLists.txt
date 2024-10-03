cmake_minimum_required(VERSION 3.5)

project(powermenu)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Widgets REQUIRED)

add_executable(powermenu src/main.cpp)
target_link_libraries(powermenu Qt5::Widgets)
