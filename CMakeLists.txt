cmake_minimum_required(VERSION 3.28.6)
project(Timur_lab4 CXX)

set(CMAKE_CXX_STANDARD 23)


add_executable(Timur_lab4 main.cpp
)

target_include_directories(Timur_lab4 PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Containers
        ${CMAKE_CURRENT_SOURCE_DIR}/Sequences
        ${CMAKE_CURRENT_SOURCE_DIR}/Sequences/Generators
        ${CMAKE_CURRENT_SOURCE_DIR}/Utilities
        ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Exceptions
)

enable_testing()
add_subdirectory(tests)