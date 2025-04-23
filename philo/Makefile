CC      = clang
CFLAGS  = -Wall -Wextra -Werror -pthread -O3 -march=native -flto -funroll-loops -g3 -I. -MMD -MP -fPIC -pipe
LDFLAGS = -O3 -march=native -flto -g3
LDLIBS  = -lpthread

OBJ_DIR = $(abspath ../build)
DEP_DIR = $(OBJ_DIR)
NAME    = philo

SRCS    = $(wildcard *.c)
OBJS    = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS    = $(patsubst %.c,$(DEP_DIR)/%.d,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "Philosophers compiled successfully!"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MF $(DEP_DIR)/$*.d
	@echo "Compiling $<"

clean:
	$(RM) -r $(OBJ_DIR)
	@echo "Cleaned up build directory."

fclean: clean
	$(RM) $(NAME)
	@echo "Removed executable: $(NAME)"

re: fclean all

run: $(NAME)
	./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re run