SRC = ft_isdigit.c    ft_isprint.c  ft_memmove.c  ft_strlcat.c  ft_strnstr.c  ft_atoi.c \
      ft_isalnum.c  ft_memchr.c	 ft_memset.c   ft_strlcpy.c  ft_strrchr.c ft_bzero.c \
      ft_isalpha.c  ft_memcmp.c	 ft_strchr.c   ft_strlen.c   ft_tolower.c  ft_calloc.c \
      ft_isascii.c  ft_memcpy.c	 ft_strdup.c   ft_strncmp.c  ft_toupper.c ft_substr.c \
      ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
      ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line_bonus.c get_next_line_utils_bonus.c \
	  ft_parse.c ft_printf_char.c ft_printf_hex.c ft_printf_int.c ft_printf_ptr.c ft_printf_uint.c \
	  ft_printf.c ft_put_util.c ft_util.c
OBJ = ${SRC:.c=.o}
BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
	ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
BONUS_OBJ = ${BONUS:.c=.o}
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

NAME = libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	ar rcs ${NAME} ${OBJ}

all: ${NAME}
clean:
	${RM} ${OBJ} ${BONUS_OBJ}
fclean: clean
	${RM} ${NAME} ${bonus}
re: fclean all
bonus: ${NAME} ${BONUS_OBJ}
	ar rcs ${NAME} ${BONUS_OBJ}
.PHONY: all clean fclean re bonus
