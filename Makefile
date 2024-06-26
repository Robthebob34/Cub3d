# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rheck <rheck@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 12:47:51 by rheck             #+#    #+#              #
#    Updated: 2024/06/13 14:21:02 by rheck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g -o3
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
INC_DIR = ./inc
LIBFT_DIR = ./libft
SRC_DIR = ./src
OBJ_DIR = ./obj

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIBFT_DIR)/*.c)

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(patsubst $(LIBFT_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)))

# Target
TARGET = cub3d

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) -I $(INC_DIR) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all
