CC = clang
SRC_DIR = .
OBJ_DIR = ../build

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c17 -O3
LDFLAGS = -pthread

SRC = \
	$(SRC_DIR)/philo.c \
	$(SRC_DIR)/worker.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/setup.c

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Cleaned object files from $(OBJ_DIR)"

fclean: clean
	@rm -f $(NAME)
	@echo "Removed $(NAME)"

re: fclean all
