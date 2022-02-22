NAME := ft_waiter

SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := include

CFLAGS := -Wall -Wextra -Werror -g
CC := gcc

SRC = ft_waiter.c mongoose.c
SRC := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
