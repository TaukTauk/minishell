NAME        = minishell
LIBFT       = ./libft
HEADERS     = -I ./include -I ${LIBFT}

LIBS        = ${LIBFT}/libft.a

SRCS_DIR    = src/

SRC         = token.c \
				utils.c \
				minishell.c \
				parsing.c \
				parsing_one.c \
				parsing_two.c \
				free.c \
				sanitize.c \
				expansion.c \
				execute.c

SRCS        = $(addprefix ${SRCS_DIR}, ${SRC})
OBJS        = ${SRCS:.c=.o}

CC          = cc

CFLAGS      = -Wall -Werror -Wextra -g3 -fsanitize=address

LDFLAGS 	= -lreadline -lncurses

all:        libft ${NAME}

norm: 
	@norminette libft src include

libft:
	@${MAKE} -C ${LIBFT}

%.o: %.c include/minishell.h
	${CC} ${CFLAGS} -o $@ -c $< ${HEADERS}

${NAME}: ${OBJS} include/minishell.h Makefile
	${CC} ${CFLAGS} ${OBJS} ${LIBS} ${HEADERS} -o ${NAME} ${LDFLAGS}


clean:
	@rm -rf ${OBJS}
	@rm -rf ${LIBFT}/*.o

fclean:     clean
	@rm -rf ${NAME}
	@rm -rf ${LIBS}

re:         fclean all

.PHONY:     all clean fclean re libft norm
