cmake_minimum_required(VERSION 3.10)
project(simd)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -march=native
    $<$<CONFIG:Debug>:-fsanitize=address>
    $<$<CONFIG:Debug>:-fsanitize=undefined>
)

add_link_options(
    $<$<CONFIG:Debug>:-fsanitize=address>
    $<$<CONFIG:Debug>:-fsanitize=undefined>
)

add_compile_definitions(
    # PRINT
)

add_executable(app 
    main.cpp
    task1.cpp
    task2.cpp
    task3.cpp
    task4.cpp
    task5.cpp

    common.cpp
)