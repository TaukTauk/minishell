NAME        = minishell
LIBFT       = ./libft
HEADERS     = -I ./include -I ${LIBFT}

LIBS        = ${LIBFT}/libft.a

SRCS_DIR    = src/

SRC         = cleanup_pipe.c \
				exec_pipe.c \
				execute_builtin.c \
				execute.c \
				execute_external.c \
				exit_status.c \
				expansion.c \
				free.c \
				handle_err.c \
				handle_redirections.c \
				handle_redirections_one.c \
				handle_redirections_two.c \
				handle_redirections_three.c \
				handle_redirections_four.c \
				minishell.c \
				parsing.c \
				parsing_one.c \
				parsing_two.c \
				pipes.c \
				sanitize.c \
				setup_redirection.c \
				token.c \
				utils.c \
				ft_echo.c \
				ft_cd.c \
				ft_exit.c \
				ft_export.c \
				ft_unset.c \
				ft_get_path.c

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
