# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 13:30:17 by thi-le            #+#    #+#              #
#    Updated: 2023/02/27 17:07:26 by thi-le           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#SETUP
#Variables

NAME		= fractol
MLX			= minilibx-linux
INCLUDE		= includes/
LIBFT		= libft
SRC_DIR		= srcs/
OBJ_DIR		= objs/
CC			= cc
CFLAGS		= -Werror -Wextra -Wall -I $(LIBFT) -I $(INCLUDE)
LFLAGS		= -Lminilibx-linux -lmlx_Linux -I $(MLX) -lXext -lX11 -lm -lz -lpthread
RM			= rm -rf
AR			= ar rcs

#Sources

SRC_FILES	=	main print_help color mandelbrot init \
				clean hook control_keyboard julia\
				control_mouse barnsley tricorn threading \
				antialiasing export config profiling \
				additional_fractals


SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
###

OBJF		=	.cache_exists


MAKEFLAGS += --no-print-directory

all:		lib mlx $(NAME)

$(NAME):	$(OBJ)
			@${CC} ${OBJ} ${CFLAGS} ${LFLAGS} libft/libft.a -o ${NAME}
			@echo "$(GREEN)$(NAME) created! -> Project successfully compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@$(CC) $(CFLAGS) -O3 -c $< -o $@
			@echo "$(BLUE)Creating object file -> $(WHITE)$(OBJ_DIR)... $(NOC)"


$(OBJF):
			@mkdir -p $(OBJ_DIR)

lib:
		@make -s -C $(LIBFT)
		@echo "$(GREEN)Libft files created$(CYAN)"
		
mlx:	
		@make -s -C $(MLX)
		@echo "$(GREEN)mlx files created$(CYAN)"

short:	$(NAME)

bonus:		all
	
clean:
			@$(RM) $(OBJ_DIR)
			@make clean -C $(LIBFT)
			@echo  "$(YELLOW)Object files deleted!$(DEFAULT)"

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C $(LIBFT)
			@$(RM) a.out
			@echo "$(RED)All deleted!$(DEFAULT)"

re:			fclean lib mlx all

norm:
			@norminette -R CheckForbiddenSourceHeader \
			$(SRC) $(INCLUDE) $(LIBFT) 

.PHONY:		all clean fclean re norm mlx lib bonus short
#COLORS
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m


