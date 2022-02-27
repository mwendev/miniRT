NAME = miniRT
INCLUDES = minirt.h

SRC_DIR := srcs/

W = -Wall -Werror -Wextra

OBJ = obj/main.o obj/get_next_line.o obj/get_next_line_utils.o obj/parse.o obj/parse_utils.o \
obj/terminate.o obj/tracer.o obj/parse_shapes.o

$(NAME): $(OBJ) libft/libft.a
	gcc $(OBJ) -L ./libft -lft -lmlx -lXext -lX11 -lm -lz -o miniRT

obj/main.o: srcs/main.c
	gcc -c -g $(W) srcs/main.c -o obj/main.o

obj/get_next_line.o: srcs/get_next_line.c
	gcc -c -g $(W) srcs/get_next_line.c -o obj/get_next_line.o

obj/get_next_line_utils.o: srcs/get_next_line_utils.c
	gcc -c -g $(W) srcs/get_next_line_utils.c -o obj/get_next_line_utils.o

obj/parse.o: srcs/parse.c
	gcc -c -g $(W) srcs/parse.c -o obj/parse.o

obj/parse_utils.o: srcs/parse_utils.c
	gcc -c -g $(W) srcs/parse_utils.c -o obj/parse_utils.o

obj/terminate.o: srcs/terminate.c
	gcc -c -g $(W) srcs/terminate.c -o obj/terminate.o

obj/tracer.o: srcs/tracer.c
	gcc -c -g srcs/tracer.c -o obj/tracer.o

obj/parse_shapes.o: srcs/parse_shapes.c
	gcc -c -g $(W) srcs/parse_shapes.c -o obj/parse_shapes.o

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
