# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbrill <cbrill@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/01 19:50:07 by cbrill            #+#    #+#              #
#    Updated: 2018/11/15 13:22:08 by cbrill           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR = ./src/
SRC_FILES = ft_atoi.c ft_bzero.c ft_isspace.c ft_memalloc.c ft_memdel.c \
	ft_putendl.c ft_putstr_fd.c ft_strchr.c ft_strdel.c ft_strdup.c \
	ft_strjoin.c ft_strlen.c ft_strncat.c ft_strncpy.c ft_strndup.c \
	ft_strnew.c ft_strsplit.c ft_wordcount.c get_next_line.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR = ./includes/
INCLUDES = -I$(INC_DIR)

OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: obj $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

req: clean
	@rm -rf $(NAME)
	@make $(NAME)
	@make clean

.PHONY: all obj $(NAME) clean fclean re req
