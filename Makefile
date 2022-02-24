NAME := coepapi

SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := include

CFLAGS := -Wall -Wextra -Werror -g
LDFLAGS := -lcurl
CC := gcc $(CFLAGS)

SRC = coepapi.c http_server.c http_client.c \
	  fetch_third_party_api.c mongoose.c mjson.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $@

run: all
	./coepapi

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
