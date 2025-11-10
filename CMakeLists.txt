cmake_minimum_required(VERSION 4.0)
project(SoftwareRasterizer C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include dir's
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/external)

# Source files
set(SOURCES
    src/main.cpp
    src/Framebuffer.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})