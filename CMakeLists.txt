cmake_minimum_required(VERSION 3.17)

project(DoodleJump)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

include(import/FetchSFML.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)
elseif(WIN32)
    add_compile_options(/W4)
endif()

set(SOURCES
    src/Main.cpp
    src/Core.cpp
    src/Data.cpp
    src/Doodle.cpp
    src/Platform.cpp
    src/Boost.cpp
    src/Score.cpp
)

add_executable(DoodleJump ${SOURCES})

target_link_libraries(DoodleJump PRIVATE
    sfml-audio
    sfml-graphics
    sfml-system
    sfml-window
)