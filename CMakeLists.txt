cmake_minimum_required(VERSION 3.19)
project(miniRT C)

set(CMAKE_C_STANDARD 99)

set(LIBFT_FILES
        libft/ft_atoi.c
        libft/ft_strncmp.c
        libft/ft_strlen.c
        libft/ft_strchr.c
        libft/ft_split.c
        libft/ft_isdigit.c
        libft/ft_memchr.c
        libft/ft_calloc.c
        libft/ft_bzero.c
        libft/ft_memset.c
        libft/ft_itoa.c
        )

set(SOURCE_FILES
        srcs/main.c
        srcs/get_next_line.c
        srcs/get_next_line_utils.c
        srcs/parse.c
        srcs/parse_utils.c
        srcs/terminate.c
        srcs/tracer.c
        srcs/listen.c
        srcs/parse_shapes.c
        srcs/vector_utils.c
        srcs/tracer_camera.c
        srcs/put_pixel.c
        srcs/select.c
        srcs/color_utils.c
        srcs/sphere_utils.c
        srcs/plane_utils.c
        srcs/translate.c
        srcs/cylinder_utils.c
        srcs/diffuse_light_check.c
        srcs/diffuse_light_handle.c
        srcs/mem_utils.c
        srcs/cylinder_cap_utils.c
        )

include_directories(includes)

add_executable(miniRT ${SOURCE_FILES} ${LIBFT_FILES})

target_link_libraries(miniRT mlx m z Xext X11)