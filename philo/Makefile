NAME = philo

CC = cc
INCLUDES = -I ./include
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES)

SRCS_DIR = ./srcs
OBJS_DIR = ./obj
SRCS = main.c parsing.c time.c init.c utils.c start.c status.c routine.c fork.c
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME) with objects: $(OBJS)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(NAME) has been created."

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@echo "Compiling $< to $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Performing full clean..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re