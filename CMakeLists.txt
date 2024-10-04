cmake_minimum_required(VERSION 3.5)

project(powermenu)

# C++11
set(CMAKE_CXX_STANDARD 11)

# Default to release variant
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Function to read .env file to get Syncthing API key
function(load_env_file filepath)
    file(READ ${filepath} content)

    # Split the content into lines
    string(REPLACE "\n" ";" lines ${content})

    foreach(line IN LISTS lines)
        # Skip empty lines or comments
        string(STRIP ${line} stripped_line)
        if (stripped_line MATCHES "^[^#].*")  # Ignore lines starting with #
            string(REPLACE "=" ";" var_list ${stripped_line})
            list(LENGTH var_list num_elements)
            if(num_elements GREATER 1)
                list(GET var_list 0 var_name)
                list(GET var_list 1 var_value)
                set(${var_name} ${var_value} PARENT_SCOPE)
            endif()
        endif()
    endforeach()
endfunction()

load_env_file(${CMAKE_CURRENT_SOURCE_DIR}/.env)

# Set the API key from the environment variable
#set(SYNCTHING_API_KEY $ENV{SYNCTHING_API_KEY})
set(SYNCTHING_API_KEY ${SYNCTHING_API_KEY})

# Create a header file with the API key
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/syncthingApiKey.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/src/syncthingApiKey.h  # Place the output in the build directory
    @ONLY
)

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
