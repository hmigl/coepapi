NAME := api_cli

CFLAGS := -Wall -Wextra -Werror -g
CC := gcc $(CFLAGS)

SRC := api_cli.c man_cli.c err_cli.c
OBJ := $(SRC:.c=.o)

all: $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)

$(OBJ): %.o: %.c
	@$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
