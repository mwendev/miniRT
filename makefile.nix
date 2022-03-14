NAME = miniRT
INCLUDES = minirt.h

SRC_DIR := srcs/

W = -Wall -Werror -Wextra

OBJ = obj/main.o obj/get_next_line.o obj/get_next_line_utils.o obj/parse.o \
obj/parse_utils.o obj/terminate.o obj/tracer.o obj/parse_shapes.o obj/listen.o \
obj/tracer_utils.o obj/tracer_camera.o obj/put_pixel.o

$(NAME): $(OBJ) libft/libft.a
	gcc $(OBJ) -L ./libft -lft -lmlx -lXext -lX11 -lm -lz -I ./includes -o miniRT

obj/main.o: srcs/main.c
	gcc -c -g $(W) srcs/main.c -I ./includes -o obj/main.o

obj/get_next_line.o: srcs/get_next_line.c
	gcc -c -g $(W) srcs/get_next_line.c -I ./includes -o obj/get_next_line.o

obj/get_next_line_utils.o: srcs/get_next_line_utils.c
	gcc -c -g $(W) srcs/get_next_line_utils.c -I ./includes -o obj/get_next_line_utils.o

obj/parse.o: srcs/parse.c
	gcc -c -g $(W) srcs/parse.c -I ./includes -o obj/parse.o

obj/parse_utils.o: srcs/parse_utils.c
	gcc -c -g $(W) srcs/parse_utils.c -I ./includes -o obj/parse_utils.o

obj/terminate.o: srcs/terminate.c
	gcc -c -g $(W) srcs/terminate.c -I ./includes -o obj/terminate.o

obj/tracer.o: srcs/tracer.c
	gcc -c -g srcs/tracer.c -I ./includes -o obj/tracer.o

obj/parse_shapes.o: srcs/parse_shapes.c
	gcc -c -g $(W) srcs/parse_shapes.c -I ./includes -o obj/parse_shapes.o

obj/listen.o: srcs/listen.c
	gcc -c -g $(W) srcs/listen.c -I ./includes -o obj/listen.o

obj/tracer_utils.o: srcs/tracer_utils.c
	gcc -c -g $(W) srcs/tracer_utils.c -I ./includes -o obj/tracer_utils.o

obj/tracer_camera.o: srcs/tracer_camera.c
	gcc -c -g $(W) srcs/tracer_camera.c -I ./includes -o obj/tracer_camera.o

obj/put_pixel.o: srcs/put_pixel.c
	gcc -c -g $(W) srcs/put_pixel.c -I ./includes -o obj/put_pixel.o

libft/libft.a:
	$(MAKE) -C libft

all: $(NAME)

clean:
	rm -f $(OBJ)

clean_all: clean clean_libft

clean_libft:
	cd libft && $(MAKE) clean

fclean: clean
	rm miniRT || echo File does not exist

fclean_all: fclean
	rm libft/*.o libft/libft.a || echo Library does not exist

re: fclean $(NAME)
