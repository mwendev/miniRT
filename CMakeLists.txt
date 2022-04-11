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
        srcs/resize.c
        srcs/rotate.c
        )

set(SOURCE_FILES_BONUS
        srcs_bonus/main_bonus.c
        srcs_bonus/get_next_line_bonus.c
        srcs_bonus/get_next_line_utils_bonus.c
        srcs_bonus/parse_bonus.c
        srcs_bonus/parse_utils_bonus.c
        srcs_bonus/terminate_bonus.c
        srcs_bonus/tracer_bonus.c
        srcs_bonus/listen_bonus.c
        srcs_bonus/parse_shapes_bonus.c
        srcs_bonus/vector_utils_bonus.c
        srcs_bonus/tracer_camera_bonus.c
        srcs_bonus/put_pixel_bonus.c
        srcs_bonus/select_bonus.c
        srcs_bonus/color_utils_bonus.c
        srcs_bonus/sphere_utils_bonus.c
        srcs_bonus/plane_utils_bonus.c
        srcs_bonus/translate_bonus.c
        srcs_bonus/cylinder_utils_bonus.c
        srcs_bonus/diffuse_light_check_bonus.c
        srcs_bonus/diffuse_light_handle_bonus.c
        srcs_bonus/mem_utils_bonus.c
        srcs_bonus/cylinder_cap_utils_bonus.c
        )

include_directories(includes)

add_executable(miniRT ${SOURCE_FILES} ${LIBFT_FILES})
add_executable(miniRT_bonus ${SOURCE_FILES_BONUS} ${LIBFT_FILES})

target_link_libraries(miniRT mlx m z Xext X11)
target_link_libraries(miniRT_bonus mlx m z Xext X11)