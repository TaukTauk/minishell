SRCS = ft_isdigit.c    ft_isprint.c  ft_memmove.c  ft_strlcat.c  ft_strnstr.c  ft_atoi.c \
      ft_isalnum.c  ft_memchr.c	 ft_memset.c   ft_strlcpy.c  ft_strrchr.c ft_bzero.c \
      ft_isalpha.c  ft_memcmp.c	 ft_strchr.c   ft_strlen.c   ft_tolower.c  ft_calloc.c \
      ft_isascii.c  ft_memcpy.c	 ft_strdup.c   ft_strncmp.c  ft_toupper.c ft_substr.c \
      ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
      ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line_bonus.c get_next_line_utils_bonus.c \
	  ft_parse.c ft_printf_char.c ft_printf_hex.c ft_printf_int.c ft_printf_ptr.c ft_printf_uint.c \
	  ft_printf.c ft_put_util.c ft_util.c ft_split_prime.c

INCLUDE = libft.h

OBJS_DIR = objs/
OBJS	 = $(SRCS:.c=.o)
SRCS_OBJS = $(addprefix $(OBJS_DIR), $(OBJS))

NAME = libft.a

CC = gcc
CFLAGS = -Werror -Wextra -Wall
ARCHIVE = ar
ARFLAGS = -rcs

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR): $(INCLUDE) Makefile
	@printf "\033[0;32mMaking libft.....\n\e[0m"
	@$(CC) $(CFLAGS) -c $(SRCS)
	@mkdir -p $@
	@mv *.o $@

$(NAME): $(SRCS)
	@$(ARCHIVE) $(ARFLAGS) $(NAME) $(SRCS_OBJS)
	@printf "\033[0;32mLibft library complete!\n\e[0m\n"


clean:
	@rm -rf $(OBJS_DIR)
	@printf "\033[0;31mLIBFT : Cleaning process done!\n\e[0m"

fclean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME)
	@printf "\033[0;31mLIBFT : File cleaning process done!\n\e[0m"

re: fclean all

.PHONY: clean fclean re all bonus
