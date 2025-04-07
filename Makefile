CC = clang

SRC_DIR = src
BONUS_DIR = src_bonus
OBJ_DIR = build

# Performance optimization flags
OPTFLAGS = -O3 -march=native -flto -fomit-frame-pointer -funroll-loops -fno-strict-aliasing -ffast-math -g3
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c17 $(OPTFLAGS)
LDFLAGS = -pedantic -flto -Wl,-O3 -Wl,--as-needed -Wl,--gc-sections -Wl,--strip-all -Wl,--no-undefined -Wl,-z,relro -Wl,-z,now

# Threading support
LDFLAGS += -pthread

BASE_CFLAGS = -I$(SRC_DIR)
BONUS_CFLAGS = -I$(BONUS_DIR)

# Colors
ORANGE = \033[33m
GREEN = \033[32m
BLUE = \033[34m
RESET = \033[0m

# If mold is available, use it for linking
ifneq ($(shell command -v mold 2> /dev/null),)
LDFLAGS += -fuse-ld=mold
endif
# Check for ccache
ifneq ($(shell command -v ccache 2> /dev/null),)
CC := ccache clang
endif

NAME = philo
BONUS_NAME = philo_bonus

SRC = \
	$(SRC_DIR)/philo.c \
	$(SRC_DIR)/worker.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/setup.c \

BONUS = \
	$(BONUS_DIR)/philo.c \
	$(BONUS_DIR)/worker.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS:.c=.o))

all: $(NAME)
bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	@echo -e "$(ORANGE)Linking $(BLUE)$@$(ORANGE)...$(RESET)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(BASE_CFLAGS)
	@echo -e "$(GREEN)Linked $(BLUE)$@$(GREEN) successfully!$(RESET)"

$(BONUS_NAME): $(BONUS_OBJ)
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
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
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