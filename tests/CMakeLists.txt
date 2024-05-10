project(Tests)

set(INCLUDE_LIB ${Pong-RL_SOURCE_DIR}/include)

enable_testing()
add_executable(MatrixTests MatrixTests.cpp)
add_executable(MathTests MathTests.cpp)
add_executable(FunctionContextTests FunctionContextTests.cpp)

target_include_directories(MatrixTests PUBLIC ${INCLUDE_LIB})
target_include_directories(MathTests PUBLIC ${INCLUDE_LIB})
target_include_directories(FunctionContextTests PUBLIC ${INCLUDE_LIB})

target_link_libraries(MatrixTests boost_unit_test_framework LibMath)
target_link_libraries(MathTests boost_unit_test_framework LibMath)
target_link_libraries(FunctionContextTests boost_unit_test_framework LibMath)

add_test(NAME MatrixTests COMMAND MatrixTests --log_level=all)
add_test(NAME MathTests COMMAND MathTests --log_level=all)
add_test(NAME FunctionContextTests COMMAND MathTests --log_level=all)
