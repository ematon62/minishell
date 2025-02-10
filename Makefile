NAME := minishell
CC := cc

LIBFT_PATH := libft
SRCS_PATH := srcs

INC_FLAGS := -Iincludes -Ilibft
LDFLAGS := -L./libft -lft -lreadline
CFLAGS := -Wall -Wextra -Werror $(INC_FLAGS)
MAKEFLAGS += --no-print-directory

SRCS := $(SRCS_PATH)/main.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cd $(LIBFT_PATH) && $(MAKE) all
	@printf "Compiling binary...\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@printf "Done.\n"

clean:
	@cd $(LIBFT_PATH) && $(MAKE) clean
	@rm -f $(OBJS)

fclean: clean
	@cd $(LIBFT_PATH) && $(MAKE) fclean
	@printf "Cleaning up binary...\n"
	@rm -f $(NAME)
	@printf "Done.\n"

re: fclean all

.PHONY: all clean fclean re 

.SILENT: $(OBJS) $(OBJS_BONUS)