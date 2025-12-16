cmake_minimum_required(VERSION 3.5)

project(powermenu)

# C++11
set(CMAKE_CXX_STANDARD 11)

# Default to release variant
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Qt5Widgets REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/mainWindow.cpp
)

# Header files
set(HEADERS
    src/mainWindow.h
)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_executable(powermenu ${SOURCES} ${HEADERS} ${MOC_SOURCES})

# Include the generated header file location
target_include_directories(powermenu PRIVATE
    include
    ${CMAKE_CURRENT_BINARY_DIR}/src
)

target_link_libraries(powermenu Qt5::Widgets)

set(CMAKE_AUTOMOC ON)
