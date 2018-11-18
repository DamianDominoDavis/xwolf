# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbrill <cbrill@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/17 22:04:42 by cbrill            #+#    #+#              #
#    Updated: 2018/11/17 22:05:13 by cbrill           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_DIR = ./src/
SRC_FILES = image.c player.c main.c ray.c map.c render.c util.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR = ./includes/
INCLUDES =  -I $(INC_DIR) $(FT_INC) $(MLX_INC)

OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

FT	= ./libft/
FT_LNK	= -L $(FT) -l ft
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I $(FT)includes

ifeq ($(shell uname), Linux)
	MLX	= ./miniLibX_X11/
	MLX_LNK	= -L $(MLX) -l mlx -lXext -lX11
else
	MLX	= ./miniLibX/
	MLX_LNK	= -L $(MLX) -l mlx -framework OpenGL -framework AppKit
endif
MLX_LIB	= $(addprefix $(MLX),libmlx.a)
MLX_INC	= -I $(MLX)


all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(FT_LIB):
	if [[ ! -e $(FT_LIB) ]]; then make -C $(FT) &> /dev/null; fi

$(MLX_LIB):
	if [[ ! -e $(MLX_LIB) ]]; then make -C $(MLX) &> /dev/null; fi

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(FT_LNK) $(MLX_LNK) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(FT) fclean &> /dev/null
	make -C $(MLX) clean &> /dev/null
	rm -rf $(NAME)

re: fclean all

do:
	make clean
	make
	make clean

.PHONY: all obj $(NAME) clean fclean re do
