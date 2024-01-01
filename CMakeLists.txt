cmake_minimum_required(VERSION 3.5)

project(awsiotcli)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# Set the runtime library for Release configuration
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:/MT>)

# Set the runtime library for Debug configuration
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:/MTd>)
