cmake_minimum_required(VERSION 3.10.0)
project(Pong-RL
    VERSION 1.0.0
    DESCRIPTION "The Game of Pong with different RL implementations"
    HOMEPAGE_URL "https://github.com/Retr0-code/Pong-RL"
)

include(CTest)

set(INSTALL_PREFIX /usr/local/bin CACHE PATH "Path for installed binaries")
set(BUILD_ARCH "amd64" CACHE STRING "Build architecture amd64/i386")
set(BUILD_CPU "RELEASE" CACHE STRING "Build target mode RELEASE/DEBUG")

set (CMAKE_CXX_STANDARD 20)

# Setting install prefix
set(CMAKE_INSTALL_PREFIX ${INSTALL_PREFIX})

# Add debug flags
if (BUILD_TARGET STREQUAL "DEBUG")
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-O0)
        add_compile_options(-ggdb)

    elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-O0)
        add_compile_options(-g)

    else()
        message(FATAL_ERROR "Unknown compiler ${CMAKE_C_COMPILER_ID}")
    endif()

    message(STATUS "Enabled debug mode")

endif()

# Add release flags
if (BUILD_TARGET STREQUAL "RELEASE")
    message(STATUS "Enabled release with -O3")
    add_compile_options(-O3)
    add_compile_options(-s)
endif()

# Process build architectures
if (BUILD_ARCH STREQUAL "amd64")
    message(STATUS "Build amd64 binary")
    add_compile_options(-m64)
    add_link_options(-m64)
    set(CMAKE_LIBRARY_PATH /usr/lib/x86_64-linux-gnu)
    include_directories(BEFORE /usr/include/x86_64-linux-gnu)
elseif (BUILD_ARCH STREQUAL "i386")
    message(STATUS "Build i386 binary")
    add_compile_options(-m32)
    add_link_options(-m32)
    set(CMAKE_LIBRARY_PATH /usr/lib/i386-linux-gnu)
    include_directories(BEFORE /usr/include/i386-linux-gnu)
else()
    message(FATAL_ERROR "Unknown building architecture ${BUILD_ARCH}")
endif()

set(BUILD_SHARED_LIBS OFF)

set(SRC_MAIN
	src/EnviromentPong.cpp
    src/AgentUCB.cpp
    src/PlayerUCB.cpp
    src/AgentLogger.cpp
    src/main.cpp
)

add_subdirectory(src/Math)
add_subdirectory(src/TheGameOfPong)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} ${SRC_MAIN})
target_include_directories(${PROJECT_NAME} PUBLIC ${Pong-RL_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} LibMath LibTheGameOfPong pthread)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
message(STATUS "WARNING! Installation prefix ${CMAKE_INSTALL_PREFIX}")

# Cleanup cache
unset(INSTALL_PREFIX CACHE)
unset(BUILD_ARCH CACHE)
unset(BUILD_TARGET CACHE)

unset(CMAKE_LIBRARY_PATH CACHE)
unset(CMAKE_INSTALL_PREFIX CACHE)
