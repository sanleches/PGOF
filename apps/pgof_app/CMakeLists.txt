add_executable(pgof main.cpp)

target_link_libraries(pgof
    PRIVATE
        pgof::structure
)
