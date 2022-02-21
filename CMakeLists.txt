cmake_minimum_required(VERSION 3.19)
project(miniRT C)

set(CMAKE_C_STANDARD 99)

set(LIBFT_FILES
        )

set(SOURCE_FILES
        main.c
        )

add_executable(miniRT ${SOURCE_FILES} ${LIBFT_FILES})