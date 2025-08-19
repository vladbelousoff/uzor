cmake_minimum_required(VERSION 4.0)
project(uzor C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/code/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/code/*.h"
)

add_executable(uzor ${SOURCE_FILES})

target_compile_definitions(uzor PRIVATE
        $<$<CONFIG:Debug>:UZ_DEBUG>
        $<$<PLATFORM_ID:Windows>:_CRT_SECURE_NO_WARNINGS>
)
