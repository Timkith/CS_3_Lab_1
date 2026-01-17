cmake_minimum_required(VERSION 3.28.6)
project(Timur_lab4 CXX)

set(CMAKE_CXX_STANDARD 23)


add_executable(Timur_lab4 main.cpp
        Utilities/Functors/IFunctor.h
        Sequences/Generators/FunctorGenerator.h
        Utilities/Functors/Fib2Functor.h
        Utilities/Functors/FIb3Functor.h
        Utilities/Person.h
        Utilities/AlphaPtr.h
        Utilities/HashUtils.h
        Utilities/Exceptions/LazySequenceIsInf.h
)

target_include_directories(Timur_lab4 PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Containers
        ${CMAKE_CURRENT_SOURCE_DIR}/Sequences
        ${CMAKE_CURRENT_SOURCE_DIR}/Sequences/Generators
        ${CMAKE_CURRENT_SOURCE_DIR}/Utilities
        ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Functors
)

enable_testing()
add_subdirectory(tests)