NAME := libft.a

PRINT_DIR := ft_printf
GNL_DIR := get_next_line
LST_DIR := ft_lst

CFLAGS := -Wall -Wextra -Werror
MAKEFLAGS += --no-print-directory

SRCS := ft_strlen.c\
	ft_atoi.c\
	ft_strlcpy.c\
	ft_strlcat.c\
	ft_itoa.c\
	ft_putnbr_fd.c\
	ft_tolower.c\
	ft_bzero.c\
	ft_memchr.c\
	ft_putstr_fd.c\
	ft_toupper.c\
	ft_calloc.c\
	ft_memcmp.c\
	ft_split.c\
	ft_strmapi.c\
	ft_isalnum.c\
	ft_memcpy.c\
	ft_strchr.c\
	ft_strncmp.c\
	ft_isalpha.c\
	ft_memmove.c\
	ft_strdup.c\
	ft_strnstr.c\
	ft_isascii.c\
	ft_memset.c\
	ft_striteri.c\
	ft_strrchr.c\
	ft_isdigit.c\
	ft_putchar_fd.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_isprint.c\
	ft_putendl_fd.c\
	ft_substr.c\
	ft_swap.c\
	ft_abs.c\
	ft_free_toodee.c\
	$(LST_DIR)/ft_lstnew.c\
	$(LST_DIR)/ft_lstadd_front.c\
	$(LST_DIR)/ft_lstsize.c\
	$(LST_DIR)/ft_lstlast.c\
	$(LST_DIR)/ft_lstadd_back.c\
	$(LST_DIR)/ft_lstdelone.c\
	$(LST_DIR)/ft_lstclear.c\
	$(LST_DIR)/ft_lstiter.c\
	$(LST_DIR)/ft_lstmap.c\
	$(PRINT_DIR)/ft_printf.c\
	$(PRINT_DIR)/ft_handle_conv.c\
	$(PRINT_DIR)/ft_handling_utils.c\
	$(GNL_DIR)/get_next_line.c\
	$(GNL_DIR)/get_next_line_utils.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "Creating libft archive file...\n"
	@$(AR) rcs $@ $^
	@printf "Done.\n"

clean:
	@printf "Cleaning up library object files...\n"
	@$(RM) -f $(OBJS)
	@printf "Done.\n"
	
fclean: clean
	@printf "Cleaning up archive...\n"
	@$(RM) -f $(NAME)
	@printf "Done.\n"

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(OBJS)