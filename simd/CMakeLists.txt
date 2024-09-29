cmake_minimum_required(VERSION 3.10)
project(simd)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app 
    main.cpp
    task1.cpp
    task2.cpp
    task3.cpp
    task4.cpp
    task5.cpp

    common.cpp
)

target_compile_options(app PRIVATE -march=native)

option(ENABLE_SANITIZERS "Enable sanitizers" ON)

if (ENABLE_SANITIZERS)
    target_compile_options(app PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
        $<$<CONFIG:Debug>:-fsanitize=undefined>
    )

    target_link_options(app PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
        $<$<CONFIG:Debug>:-fsanitize=undefined>
    )
endif()

target_compile_definitions(app PRIVATE
    # PRINT
)
