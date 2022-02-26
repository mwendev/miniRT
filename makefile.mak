# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile.mak                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 10:00:09 by mwen              #+#    #+#              #
#    Updated: 2022/02/26 02:39:58 by mwen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

DIR_SRCS	=	srcs/
SRC			=	main.c get_next_line.c get_next_line_utils.c parse.c terminate.c\
				parse_utils.c
SRCS		=	$(addprefix $(DIR_SRCS), $(SRC))

CFLAG		=	#-Wall -Wextra -Werror
MFLAG		=	-framework OpenGL -framework AppKit

LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_DIR		=	libft/

MINILIBX		=	$(MINILIBX_DIR)libmlx.a
MINILIBX_DIR	=	minilibx_opengl/


.SILENT:

all:		$(NAME)
$(NAME):	$(OBJ)
			make -sC $(MINILIBX_DIR)
			make -sC $(LIBFT_DIR)
			gcc $(CFLAG) $(MFLAG) $(SRCS) $(LIBFT) $(MINILIBX) $^ -o $(NAME)
			printf '\033[32m[ ✔ ] %s\n\033[0m' "Created miniRT"

./objects/%.o: ./sources/%.cpp
	mkdir -p objects
	gcc -c $< -o $@

norme:
			norminette $(DIR_SRCS)
			norminette $(DIR_HEADERS)

clean:
			rm -rf objects
			/bin/rm -f *.o
			/bin/rm -rf ./objects/*.o
			make clean -sC $(LIBFT_DIR)
			make clean -sC $(MINILIBX_DIR)
			printf '\033[31m[ ✔ ] %s\n\033[0m' "Cleaned miniRT"

fclean: clean
			/bin/rm -f $(NAME)
			make fclean -sC $(LIBFT_DIR)
			make clean -sC $(MINILIBX_DIR)
			printf '\033[31m[ ✔ ] %s\n\033[0m' "Fcleaned miniRT"

re: fclean all

.PHONY: clean fclean re all test