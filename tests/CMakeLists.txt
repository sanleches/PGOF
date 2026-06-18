add_executable(garage_capacity_tests
    garage_capacity_tests.cpp
)

target_link_libraries(garage_capacity_tests
    PRIVATE
        pgof::garage_capacity
)

add_test(NAME garage_capacity_tests COMMAND garage_capacity_tests)

add_executable(pgof_requirements_tests
    pgof_requirements_tests.cpp
)

target_link_libraries(pgof_requirements_tests
    PRIVATE
        pgof::structure
)

add_test(NAME pgof_requirements_tests COMMAND pgof_requirements_tests)
