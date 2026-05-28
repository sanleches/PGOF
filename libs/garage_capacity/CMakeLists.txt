add_library(garage_capacity
    src/garage_capacity.cpp
)

add_library(pgof::garage_capacity ALIAS garage_capacity)

target_include_directories(garage_capacity
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)