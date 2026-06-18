cmake_minimum_required(VERSION 3.14)

project(PGOF VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(libs)

add_library(pgof_structure
    src/main.cpp
    src/parking_lot_handler.cpp
    src/parking_space.cpp
    src/car_queue.cpp
    src/car.cpp
    src/time_handler.cpp
    src/fee_handler.cpp
)

add_library(pgof::structure ALIAS pgof_structure)

target_include_directories(pgof_structure
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()
add_subdirectory(tests)
