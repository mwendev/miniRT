NAME = minirt
INCLUDES = minirt.h

W = -Wall -Werror -Wextra
SOURCE = main.c
OBJ = $(SOURCE:.c=.o)

$(NAME): $(OBJ) libft/libft.a
	gcc $(OBJ) -L ./libft -lft -lmlx -lXext -lX11 -lm -lz -o miniRT

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

%.o : %.c
	gcc $(W) -g -D BUFFER_SIZE=1000 $< -c