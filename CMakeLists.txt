cmake_minimum_required(VERSION 3.31)
project(SandSimulator)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML COMPONENTS graphics window system REQUIRED)

# Include your source files
add_executable(SandSimulator
        main.cpp
        Grid.cpp
        Grid.h
)

target_link_libraries(SandSimulator sfml-graphics sfml-window sfml-system)