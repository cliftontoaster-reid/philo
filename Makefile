CC = clang

SRC_DIR = philo
BONUS_DIR = philo_bonus
OBJ_DIR = build

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c17
LDFLAGS = -pedantic
BASE_CFLAGS = -I$(SRC_DIR)
BONUS_CFLAGS = -I$(BONUS_DIR)

# If mold is available, use it for linking
ifeq ($(shell command -v mold 2> /dev/null),)
LDFLAGS += -fuse-ld=mold
endif

NAME = philo
BONUS_NAME = philo_bonus

SRC = \
	$(SRC_DIR)/philo.c \
	$(SRC_DIR)/worker.c \

BONUS = \
	$(BONUS_DIR)/philo.c \
	$(BONUS_DIR)/worker.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS:.c=.o))

all: $(NAME)
bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(BASE_CFLAGS)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(BONUS_CFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	$(CC) $(CFLAGS) $(BASE_CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	$(CC) $(CFLAGS) $(BONUS_CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

fmt: ~/.cache/trunkexe
	@echo "Formatting code..."
	@~/.cache/trunkexe install
	@~/.cache/trunkexe upgrade
	@~/.cache/trunkexe fmt -a --verbose

~/.cache/trunkexe:
	@mkdir -p ~/.cache
	@wget https://trunk.io/releases/trunk -O ~/.cache/trunkexe
	@chmod +x ~/.cache/trunkexe

.PHONY: all bonus clean fclean re fmt