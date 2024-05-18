project(Tests)

set(INCLUDE_LIB ${Pong-RL_SOURCE_DIR}/include)

enable_testing()
add_executable(MatrixTests MatrixTests.cpp)
add_executable(MathTests MathTests.cpp)
add_executable(FunctionContextTests FunctionContextTests.cpp)
add_executable(DifferentEnvironmentsExperiment
    DifferentEnvironmentsExperiment.cpp
    ${Pong-RL_SOURCE_DIR}/src/AgentUCB.cpp
    ${Pong-RL_SOURCE_DIR}/src/AgentLogger.cpp
    ${Pong-RL_SOURCE_DIR}/src/PlayerUCB.cpp
    ${Pong-RL_SOURCE_DIR}/src/EnvironmentPong.cpp
)

target_include_directories(MatrixTests PUBLIC ${INCLUDE_LIB})
target_include_directories(MathTests PUBLIC ${INCLUDE_LIB})
target_include_directories(FunctionContextTests PUBLIC ${INCLUDE_LIB})
target_include_directories(DifferentEnvironmentsExperiment PUBLIC ${INCLUDE_LIB})

target_link_libraries(MatrixTests boost_unit_test_framework LibMath)
target_link_libraries(MathTests boost_unit_test_framework LibMath)
target_link_libraries(FunctionContextTests boost_unit_test_framework LibMath)
target_link_libraries(DifferentEnvironmentsExperiment boost_unit_test_framework LibMath LibTheGameOfPong pthread)

add_test(NAME MatrixTests COMMAND MatrixTests --log_level=all)
add_test(NAME MathTests COMMAND MathTests --log_level=all)
add_test(NAME FunctionContextTests COMMAND MathTests --log_level=all)
add_test(NAME DifferentEnvironmentsExperiment COMMAND MathTests --log_level=all)
