NAME := minishell
CC := cc

LIBFT_PATH := libft
SRCS_PATH := srcs

INC_FLAGS := -Iincludes -Ilibft
LDFLAGS := -L./libft -lft -lreadline
CFLAGS := -Wall -Wextra -Werror $(INC_FLAGS)
MAKEFLAGS += --no-print-directory

SRCS := $(SRCS_PATH)/main.c\
		$(SRCS_PATH)/parsing/init_shell.c\
		$(SRCS_PATH)/parsing/parsing.c\
		$(SRCS_PATH)/parsing/tokenizer_get_words.c\
		$(SRCS_PATH)/parsing/tokenizer_main.c\
		$(SRCS_PATH)/parsing/check_quote.c\
		$(SRCS_PATH)/parsing/check_tokens.c\
		$(SRCS_PATH)/parsing/complete_pipe.c\
		$(SRCS_PATH)/utils/exit_error.c\
		$(SRCS_PATH)/utils/lst_utils.c\
		$(SRCS_PATH)/utils/memory_utils.c

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