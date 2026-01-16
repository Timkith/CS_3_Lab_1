add_executable(tests 
    test.cpp
    dynamic_array.cpp
    append.cpp
    prepend.cpp
    concat.cpp
    take.cpp
    option.cpp
    cardinal.cpp
    ordinal.cpp
    linked_list.cpp
    pair.cpp
        ../Containers/HashMap.h
        hash_map.cpp
        ../Sequences/LazySequence.h
        lazy_sequence.cpp
        functor.cpp
)

target_include_directories(tests PUBLIC
    .
    ${CMAKE_CURRENT_SOURCE_DIR}/../Containers
    ${CMAKE_CURRENT_SOURCE_DIR}/../Sequences
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/Exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/../Sequences/Generators
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/Functors
)

add_test(NAME tests COMMAND tests)