# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 16:41:11 by mwen              #+#    #+#              #
#    Updated: 2021/11/22 12:08:15 by mwen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fdf
CC 				=	gcc
FLAGS			=	-Wall -Werror -Wextra 
FLAGS_FDF		=	-framework OpenGL -framework AppKit
RM				=	rm -rf

GNL_LIST		=	get_next_line.c get_next_line_utils.c
GNL_DIR			=	get_next_line/
GNL				=	$(addprefix $(GNL_DIR), $(GNL_LIST))

LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_DIR		=	libft/

MINILIBX		=	$(MINILIBX_DIR)libmlx.a
MINILIBX_DIR	=	minilibx/

HEADERS			=	fdf.h

SRCS_LIST		=	main.c init.c terminate.c read.c draw.c project.c listen.c\
					listen_utils.c draw_utils.c read_utils.c
SRCS_DIR		=	src/
SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS_DIR		=	obj/
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LIST)) $(GNL:.c=.o)

BONUS_LIST		=	main_bonus.c init_bonus.c terminate_bonus.c read_bonus.c\
					draw_bonus.c project_bonus.c listen_bonus.c read_utils.c\
					listen_utils_bonus.c draw_utils_bonus.c
BONUS_DIR		=	bonus/
BONUS			=	$(addprefix $(BONUS_DIR), $(BONUS_LIST))

BOBJS_LIST		=	$(patsubst %.c, %.o, $(BONUS_LIST))
BOBJS_DIR		=	obj/
BOBJS			=	$(addprefix $(OBJS_DIR), $(BOBJS_LIST)) $(GNL:.c=.o)

GREEN			=	\033[0;32m
RED				=	\033[0;31m
RESET			=	\033[0m

.PHONY:			all clean fclean re

all:			$(NAME)

$(NAME):		$(LIBFT) $(MINILIBX) $(OBJS_DIR) $(OBJS)
				@$(CC) $(FLAGS) $(FLAGS_FDF) $(OBJS) $(LIBFT) $(MINILIBX) -o $(NAME)
				@echo "Please enter: ./fdf test_maps/42.fdf"

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c 
				@$(CC) $(FLAGS) -c -I$(SRCS_DIR) $< -o $@

$(MINILIBX):
				@echo "$(GREEN)Compiling $(MINILIBX)...$(RESET)"
				@$(MAKE) -sC $(MINILIBX_DIR)

$(LIBFT):
				@echo "$(GREEN)Compiling $(LIBFT)...$(RESET)"
				@$(MAKE) -sC $(LIBFT_DIR)

$(BOBJS_DIR)%.o:$(BONUS_DIR)%.c 
				@$(CC) $(FLAGS) -c -I$(BONUS_DIR) $< -o $@

bonus:			$(LIBFT) $(MINILIBX) $(OBJS_DIR) $(BOBJS)
				@$(CC) $(FLAGS) $(FLAGS_FDF) $(BOBJS) $(LIBFT) $(MINILIBX) -o $(NAME)
				@echo "Please enter: ./fdf test_maps/42.fdf"
clean:
				@$(MAKE) -sC $(LIBFT_DIR) clean
				@$(MAKE) -sC $(MINILIBX_DIR) clean
				@$(RM) $(OBJS_DIR) $(GNL_DIR)*.o
				@echo "$(RED)cleaned$(RESET)"

fclean:			clean
				@$(MAKE) -sC $(LIBFT_DIR) fclean
				@$(RM) $(NAME)

re:				fclean all
