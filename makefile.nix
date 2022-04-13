NAME = miniRT
NAME_BONUS = miniRT_bonus
INCLUDES = minirt.h

SRC_DIR := srcs/
SRC_DIR_BONUS := srcs_bonus/
MKDIR_P = mkdir -p
OBJ_DIR = obj

W = -Wall -Werror -Wextra

OBJ = obj/main.o obj/get_next_line.o obj/get_next_line_utils.o obj/parse.o \
obj/parse_utils.o obj/terminate.o obj/tracer.o obj/parse_shapes.o obj/listen.o \
obj/vector_utils.o obj/tracer_camera.o obj/put_pixel.o obj/color_utils.o \
obj/sphere_utils.o obj/cylinder_utils.o obj/translate.o obj/rotate.o \
obj/select.o obj/plane_utils.o obj/diffuse_light_check.o \
obj/diffuse_light_handle.o obj/mem_utils.o obj/cylinder_cap_utils.o \
obj/resize.o

OBJ_BONUS = obj/main_bonus.o obj/get_next_line_bonus.o obj/get_next_line_utils_bonus.o obj/parse_bonus.o \
obj/parse_utils_bonus.o obj/terminate_bonus.o obj/tracer_bonus.o obj/parse_shapes_bonus.o obj/listen_bonus.o \
obj/vector_utils_bonus.o obj/tracer_camera_bonus.o obj/put_pixel_bonus.o obj/color_utils_bonus.o \
obj/plane_utils_bonus.o obj/sphere_utils_bonus.o obj/cylinder_utils_bonus.o obj/translate_bonus.o \
obj/select_bonus.o obj/diffuse_light_check_bonus.o obj/diffuse_light_handle_bonus.o \
obj/mem_utils_bonus.o obj/cylinder_cap_utils_bonus.o obj/rotate_bonus.o obj/resize_bonus.o

$(NAME): directories $(OBJ) libft/libft.a minilibx-lin/libmlx.a
	gcc $(OBJ) -L ./libft -lft -L ./minilibx-lin -lmlx -lXext -lX11 -lm -lz -I ./includes -o miniRT

$(NAME_BONUS): directories $(OBJ_BONUS) libft/libft.a
	gcc $(OBJ_BONUS) -L ./libft -lft -lmlx -lXext -lX11 -lm -lz -I ./includes -o miniRT_bonus

directories: ${OBJ_DIR}

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

obj/main.o: srcs/main.c
	gcc -c -g $(W) srcs/main.c -I ./includes -I ./minilibx-lin -o obj/main.o

obj/get_next_line.o: srcs/get_next_line.c
	gcc -c -g $(W) srcs/get_next_line.c -I ./includes -I ./minilibx-lin -o obj/get_next_line.o

obj/get_next_line_utils.o: srcs/get_next_line_utils.c
	gcc -c -g $(W) srcs/get_next_line_utils.c -I ./includes -I ./minilibx-lin -o obj/get_next_line_utils.o

obj/parse.o: srcs/parse.c
	gcc -c -g $(W) srcs/parse.c -I ./includes -I ./minilibx-lin -o obj/parse.o

obj/parse_utils.o: srcs/parse_utils.c
	gcc -c -g $(W) srcs/parse_utils.c -I ./includes -I ./minilibx-lin -o obj/parse_utils.o

obj/terminate.o: srcs/terminate.c
	gcc -c -g $(W) srcs/terminate.c -I ./includes -I ./minilibx-lin -o obj/terminate.o

obj/tracer.o: srcs/tracer.c
	gcc -c -g srcs/tracer.c -I ./includes -I ./minilibx-lin -o obj/tracer.o

obj/parse_shapes.o: srcs/parse_shapes.c
	gcc -c -g $(W) srcs/parse_shapes.c -I ./includes -I ./minilibx-lin -o obj/parse_shapes.o

obj/listen.o: srcs/listen.c
	gcc -c -g $(W) srcs/listen.c -I ./includes -I ./minilibx-lin -o obj/listen.o

obj/vector_utils.o: srcs/vector_utils.c
	gcc -c -g $(W) srcs/vector_utils.c -I ./includes -I ./minilibx-lin -o obj/vector_utils.o

obj/tracer_camera.o: srcs/tracer_camera.c
	gcc -c -g $(W) srcs/tracer_camera.c -I ./includes -I ./minilibx-lin -o obj/tracer_camera.o

obj/put_pixel.o: srcs/put_pixel.c
	gcc -c -g $(W) srcs/put_pixel.c -I ./includes -I ./minilibx-lin -o obj/put_pixel.o

obj/color_utils.o: srcs/color_utils.c
	gcc -c -g $(W) srcs/color_utils.c -I ./includes -I ./minilibx-lin -o obj/color_utils.o

obj/plane_utils.o: srcs/plane_utils.c
	gcc -c -g $(W) srcs/plane_utils.c -I ./includes -I ./minilibx-lin -o obj/plane_utils.o

obj/cylinder_utils.o: srcs/cylinder_utils.c
	gcc -c -g $(W) srcs/cylinder_utils.c -I ./includes -I ./minilibx-lin -o obj/cylinder_utils.o

obj/sphere_utils.o: srcs/sphere_utils.c
	gcc -c -g $(W) srcs/sphere_utils.c -I ./includes -I ./minilibx-lin -o obj/sphere_utils.o

obj/translate.o: srcs/translate.c
	gcc -c -g $(W) srcs/translate.c -I ./includes -I ./minilibx-lin -o obj/translate.o

obj/rotate.o: srcs/rotate.c
	gcc -c -g $(W) srcs/rotate.c -I ./includes -I ./minilibx-lin -o obj/rotate.o

obj/resize.o: srcs/resize.c
	gcc -c -g $(W) srcs/resize.c -I ./includes -I ./minilibx-lin -o obj/resize.o

obj/select.o: srcs/select.c
	gcc -c -g $(W) srcs/select.c -I ./includes -I ./minilibx-lin -o obj/select.o

obj/diffuse_light_check.o: srcs/diffuse_light_check.c
	gcc -c -g $(W) srcs/diffuse_light_check.c -I ./includes -I ./minilibx-lin -o obj/diffuse_light_check.o

obj/diffuse_light_handle.o: srcs/diffuse_light_handle.c
	gcc -c -g $(W) srcs/diffuse_light_handle.c -I ./includes -I ./minilibx-lin -o obj/diffuse_light_handle.o

obj/mem_utils.o: srcs/mem_utils.c
	gcc -c -g $(W) srcs/mem_utils.c -I ./includes -I ./minilibx-lin -o obj/mem_utils.o

obj/cylinder_cap_utils.o: srcs/cylinder_cap_utils.c
	gcc -c -g $(W) srcs/cylinder_cap_utils.c -I ./includes -I ./minilibx-lin -o obj/cylinder_cap_utils.o


obj/main_bonus.o: srcs_bonus/main_bonus.c
	gcc -c -g $(W) srcs_bonus/main_bonus.c -I ./includes -I ./minilibx-lin -o obj/main_bonus.o

obj/get_next_line_bonus.o: srcs_bonus/get_next_line_bonus.c
	gcc -c -g $(W) srcs_bonus/get_next_line_bonus.c -I ./includes -I ./minilibx-lin -o obj/get_next_line_bonus.o

obj/get_next_line_utils_bonus.o: srcs_bonus/get_next_line_utils_bonus.c
	gcc -c -g $(W) srcs_bonus/get_next_line_utils_bonus.c -I ./includes -I ./minilibx-lin -o obj/get_next_line_utils_bonus.o

obj/parse_bonus.o: srcs_bonus/parse_bonus.c
	gcc -c -g $(W) srcs_bonus/parse_bonus.c -I ./includes -I ./minilibx-lin -o obj/parse_bonus.o

obj/parse_utils_bonus.o: srcs_bonus/parse_utils_bonus.c
	gcc -c -g $(W) srcs_bonus/parse_utils_bonus.c -I ./includes -I ./minilibx-lin -o obj/parse_utils_bonus.o

obj/terminate_bonus.o: srcs_bonus/terminate_bonus.c
	gcc -c -g $(W) srcs_bonus/terminate_bonus.c -I ./includes -I ./minilibx-lin -o obj/terminate_bonus.o

obj/tracer_bonus.o: srcs_bonus/tracer_bonus.c
	gcc -c -g $(W) srcs_bonus/tracer_bonus.c -I ./includes -I ./minilibx-lin -o obj/tracer_bonus.o

obj/parse_shapes_bonus.o: srcs_bonus/parse_shapes_bonus.c
	gcc -c -g $(W) srcs_bonus/parse_shapes_bonus.c -I ./includes -I ./minilibx-lin -o obj/parse_shapes_bonus.o

obj/listen_bonus.o: srcs_bonus/listen_bonus.c
	gcc -c -g $(W) srcs_bonus/listen_bonus.c -I ./includes -I ./minilibx-lin -o obj/listen_bonus.o

obj/vector_utils_bonus.o: srcs_bonus/vector_utils_bonus.c
	gcc -c -g $(W) srcs_bonus/vector_utils_bonus.c -I ./includes -I ./minilibx-lin -o obj/vector_utils_bonus.o

obj/tracer_camera_bonus.o: srcs_bonus/tracer_camera_bonus.c
	gcc -c -g $(W) srcs_bonus/tracer_camera_bonus.c -I ./includes -I ./minilibx-lin -o obj/tracer_camera_bonus.o

obj/put_pixel_bonus.o: srcs_bonus/put_pixel_bonus.c
	gcc -c -g $(W) srcs_bonus/put_pixel_bonus.c -I ./includes -I ./minilibx-lin -o obj/put_pixel_bonus.o

obj/color_utils_bonus.o: srcs_bonus/color_utils_bonus.c
	gcc -c -g $(W) srcs_bonus/color_utils_bonus.c -I ./includes -I ./minilibx-lin -o obj/color_utils_bonus.o

obj/plane_utils_bonus.o: srcs_bonus/plane_utils_bonus.c
	gcc -c -g $(W) srcs_bonus/plane_utils_bonus.c -I ./includes -I ./minilibx-lin -o obj/plane_utils_bonus.o

obj/sphere_utils_bonus.o: srcs_bonus/sphere_utils_bonus.c
	gcc -c -g $(W) srcs_bonus/sphere_utils_bonus.c -I ./includes -I ./minilibx-lin -o obj/sphere_utils_bonus.o

obj/cylinder_utils_bonus.o: srcs_bonus/cylinder_utils_bonus.c
	gcc -c -g $(W) srcs_bonus/cylinder_utils_bonus.c -I ./includes -I ./minilibx-lin -o obj/cylinder_utils_bonus.o

obj/translate_bonus.o: srcs_bonus/translate_bonus.c
	gcc -c -g $(W) srcs_bonus/translate_bonus.c -I ./includes -I ./minilibx-lin -o obj/translate_bonus.o

obj/select_bonus.o: srcs_bonus/select_bonus.c
	gcc -c -g $(W) srcs_bonus/select_bonus.c -I ./includes -I ./minilibx-lin -o obj/select_bonus.o

obj/diffuse_light_check_bonus.o: srcs_bonus/diffuse_light_check_bonus.c
	gcc -c -g $(W) srcs_bonus/diffuse_light_check_bonus.c -I ./includes -I ./minilibx-lin -o obj/diffuse_light_check_bonus.o

obj/diffuse_light_handle_bonus.o: srcs_bonus/diffuse_light_handle_bonus.c
	gcc -c -g $(W) srcs_bonus/diffuse_light_handle_bonus.c -I ./includes -I ./minilibx-lin -o obj/diffuse_light_handle_bonus.o

obj/mem_utils_bonus.o: srcs_bonus/mem_utils_bonus.c
	gcc -c -g $(W) srcs_bonus/mem_utils_bonus.c -I ./includes -o obj/mem_utils_bonus.o

obj/cylinder_cap_utils_bonus.o: srcs_bonus/cylinder_cap_utils_bonus.c
	gcc -c -g $(W) srcs_bonus/cylinder_cap_utils_bonus.c -I ./includes -I ./minilibx-lin -o obj/cylinder_cap_utils_bonus.o

obj/rotate_bonus.o: srcs_bonus/rotate_bonus.c
	gcc -c -g $(W) srcs_bonus/rotate_bonus.c -I ./includes -I ./minilibx-lin -o obj/rotate_bonus.o

obj/resize_bonus.o: srcs_bonus/resize_bonus.c
	gcc -c -g $(W) srcs_bonus/resize_bonus.c -I ./includes -I ./minilibx-lin -o obj/resize_bonus.o

libft/libft.a:
	$(MAKE) -C libft

minilibx-lin/libmlx.a:
	$(MAKE) -C minilibx-lin

all: $(NAME)

clean:
	rm -f $(OBJ)

clean_bonus:
	rm -f $(OBJ_BONUS)

clean_all: clean clean_libft

clean_libft:
	cd libft && $(MAKE) clean

fclean: clean
	rm miniRT || echo File does not exist

fclean_bonus: clean_bonus
	rm miniRT_bonus || echo File does not exist

fclean_all: fclean
	rm libft/*.o libft/libft.a || echo Library does not exist

re: fclean $(NAME)

re_bonus: fclean_bonus $(NAME_BONUS)
