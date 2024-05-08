project(LibMath)

add_library(${PROJECT_NAME} STATIC 
    Matrix.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${Pong-RL_SOURCE_DIR}/include/Math)

