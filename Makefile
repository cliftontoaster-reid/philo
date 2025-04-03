CC = clang

SRC_DIR = philo
BONUS_DIR = philo_bonus
OBJ_DIR = build

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c17 -O3 -g3
LDFLAGS = -pedantic
BASE_CFLAGS = -I$(SRC_DIR)
BONUS_CFLAGS = -I$(BONUS_DIR)

# Colors
ORANGE = \033[33m
GREEN = \033[32m
BLUE = \033[34m
RESET = \033[0m

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

all: $(NAME)/$(NAME)
bonus: $(BONUS_NAME)/$(BONUS_NAME)

$(NAME)/$(NAME): $(OBJ)
	@echo -e "$(ORANGE)Linking $(BLUE)$@$(ORANGE)...$(RESET)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(BASE_CFLAGS)
	@echo -e "$(GREEN)Linked $(BLUE)$@$(GREEN) successfully!$(RESET)"

$(BONUS_NAME)/$(BONUS_NAME): $(BONUS_OBJ)
	@echo -e "$(ORANGE)Linking $(BLUE)$@$(ORANGE)...$(RESET)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(BONUS_CFLAGS)
	@echo -e "$(GREEN)Linked $(BLUE)$@$(GREEN) successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	@echo -e "$(ORANGE)Compiling $(BLUE)$<$(ORANGE) to $(BLUE)$@$(ORANGE)...$(RESET)"
	@$(CC) $(CFLAGS) $(BASE_CFLAGS) -c $< -o $@
	@echo -e "$(GREEN)Compiled $(BLUE)$<$(GREEN) successfully!$(RESET)"

$(BONUS_OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	@echo -e "$(ORANGE)Compiling $(BLUE)$<$(ORANGE) to $(BLUE)$@$(ORANGE)...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_CFLAGS) -c $< -o $@
	@echo -e "$(GREEN)Compiled $(BLUE)$<$(GREEN) successfully!$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "$(GREEN)Cleaned object files from $(BLUE)$(OBJ_DIR)$(RESET)"

fclean: clean
	@rm -f $(NAME)/$(NAME)
	@rm -f $(BONUS_NAME)/$(BONUS_NAME)
	@echo -e "$(GREEN)Cleaned executables $(BLUE)$(NAME)$(GREEN) and $(BLUE)$(BONUS_NAME)$(RESET)"

re: fclean all

fmt: ~/.cache/trunkexe
	@echo -e "$(ORANGE)Formatting code...$(RESET)"
	@~/.cache/trunkexe install
	@~/.cache/trunkexe upgrade
	@~/.cache/trunkexe fmt -a --verbose
	@echo -e "$(GREEN)Formatting complete$(RESET)"

~/.cache/trunkexe:
	@mkdir -p ~/.cache
	@echo -e "$(ORANGE)Installing trunk...$(RESET)"
	@wget https://trunk.io/releases/trunk -O ~/.cache/trunkexe
	@chmod +x ~/.cache/trunkexe
	@echo -e "$(GREEN)Installed trunk$(RESET)"

.PHONY: all bonus clean fclean re fmt