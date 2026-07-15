cmake_minimum_required(VERSION 3.10)

project(powermenu)

# C++ 17
set(CMAKE_CXX_STANDARD 17)

# Default to release variant
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Qt6Widgets REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/mainWindow.cpp
)

# Header files
set(HEADERS
    src/mainWindow.h
)

qt6_wrap_cpp(MOC_SOURCES ${HEADERS})
add_executable(powermenu ${SOURCES} ${HEADERS} ${MOC_SOURCES})

# Include the generated header file location
target_include_directories(powermenu PRIVATE
    include
    ${CMAKE_CURRENT_BINARY_DIR}/src
)

target_link_libraries(powermenu Qt6::Widgets)

set(CMAKE_AUTOMOC ON)

target_compile_options(powermenu PRIVATE
    -Wall -Wextra -Wpedantic

    # Optimise for size
    $<$<CONFIG:Release>:-Os>

    $<$<CONFIG:Release>:-flto>
)

add_custom_command(
    TARGET powermenu
    POST_BUILD
    COMMAND ${CMAKE_STRIP} $<TARGET_FILE:powermenu>
    # Only execute in Release builds
    $<$<CONFIG:Release>:>
)
