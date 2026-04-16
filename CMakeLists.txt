cmake_minimum_required(VERSION 3.22)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Og")
set(CMAKE_CXX_FLAGS_RELASE "-O2")
set(CMAKE_BUILD_PARALLEL_LEVEL 8)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB SOURCES
    "src/*.cpp"
)

file(GLOB HEADERS
    "inc/*.h"
)

project(Signal_processing CXX)
include_directories(
    ${PROJECT_SOURCE_DIR}/inc ${PROJECT_SOURCE_DIR}/src
    )

add_executable(wave_gen mains/wave_gen_main.cpp ${SOURCES})
add_executable(fourier mains/fourier_transform_main.cpp ${SOURCES})