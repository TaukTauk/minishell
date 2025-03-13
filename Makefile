SRC_PATH = src/
BUILTIN_PATH = $(SRC_PATH)builtin/
EXTCMD_PATH = $(SRC_PATH)extcmd/
LEXER_PATH = $(SRC_PATH)lexer/
PARSING_PATH = $(SRC_PATH)parsing/
PIPE_PATH = $(SRC_PATH)pipe/
REDIRECTION_PATH = $(SRC_PATH)redirection/
SIGNAL_PATH = $(SRC_PATH)signal/
UTILS_PATH = $(SRC_PATH)utils/

SRCS = main.c

SRCS_PREFIXED = $(addprefix $(SRC_PATH), $(SRCS))

SRCS_BUILTIN = ft_echo.c ft_exit.c ft_export.c  \
				ft_unset.c execute_builtin.c ft_cd.c ft_cd_two.c
SRCS_BUILTIN_PREFIXED = $(addprefix $(BUILTIN_PATH), $(SRCS_BUILTIN))

SRCS_EXTCMD = execute_external.c execute.c ft_get_path.c
SRCS_EXTCMD_PREFIXED = $(addprefix $(EXTCMD_PATH), $(SRCS_EXTCMD))

SRCS_LEXER = expanded_size.c expansion_one.c expansion.c remove_quote.c sanitize.c token_three.c token_two.c token.c
SRCS_LEXER_PREFIXED = $(addprefix $(LEXER_PATH), $(SRCS_LEXER))

SRCS_PARSING = parsing_one.c parsing_two.c parsing.c
SRCS_PARSING_PREFIXED = $(addprefix $(PARSING_PATH), $(SRCS_PARSING))

SRCS_PIPE = cleanup_pipe.c exec_pipe.c pipes.c 
SRCS_PIPE_PREFIXED = $(addprefix $(PIPE_PATH), $(SRCS_PIPE))

SRCS_REDIRECTION = handle_redirections_four.c handle_redirections_one.c handle_redirections_three.c \
					handle_redirections_two.c handle_redirections.c output_redirection.c input_redirection.c
SRCS_REDIRECTION_PREFIXED = $(addprefix $(REDIRECTION_PATH), $(SRCS_REDIRECTION))

SRCS_SIGNAL = signal.c
SRCS_SIGNAL_PREFIXED = $(addprefix $(SIGNAL_PATH), $(SRCS_SIGNAL))

SRCS_UTILS = error.c exit_status.c free_env.c free_two.c free.c get_env.c handle_err.c init_shell.c utils_two.c utils.c global.c
SRCS_UTILS_PREFIXED = $(addprefix $(UTILS_PATH), $(SRCS_UTILS))

INCLUDE = include/minishell.h

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 
LDFLAGS = -lreadline -lncurses

LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), \
    $(SRCS:.c=.o) \
    $(SRCS_BUILTIN:.c=.o) \
    $(SRCS_EXTCMD:.c=.o) \
    $(SRCS_LEXER:.c=.o) \
    $(SRCS_PARSING:.c=.o) \
    $(SRCS_PIPE:.c=.o) \
    $(SRCS_REDIRECTION:.c=.o) \
    $(SRCS_SIGNAL:.c=.o) \
    $(SRCS_UTILS:.c=.o))

all: SUBSYSTEMS $(OBJS) $(NAME)

SUBSYSTEMS:
	@make -C $(LIBFT_PATH) all -s

$(OBJS_DIR)%.o: $(SRC_PATH)%.c Makefile $(INCLUDE)
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling: $<\e[0m\n"

$(OBJS_DIR)%.o: $(BUILTIN_PATH)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling: $<\e[0m\n"

$(OBJS_DIR)%.o: $(EXTCMD_PATH)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling: $<\e[0m\n"

$(OBJS_DIR)%.o: $(LEXER_PATH)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling: $<\e[0m\n"

$(OBJS_DIR)%.o: $(PARSING_PATH)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling: $<\e[0m\n"

$(OBJS_DIR)%.o: $(PIPE_PATH)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling: $<\e[0m\n"

$(OBJS_DIR)%.o: $(REDIRECTION_PATH)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling: $<\e[0m\n"

$(OBJS_DIR)%.o: $(SIGNAL_PATH)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling: $<\e[0m\n"

$(OBJS_DIR)%.o: $(UTILS_PATH)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32mCompiling: $<\e[0m\n"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) $(LDFLAGS)
	@printf "\n\033[0;32m$(NAME) compiled\n\e[0m"

clean:
	@make -C $(LIBFT_PATH) clean -s
	@rm -rf $(OBJS_DIR)
	@printf "\033[0;31mCleaning process done!\n\e[0m"

fclean:
	@make -C $(LIBFT_PATH) fclean -s
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME)
	@printf "\033[0;31mFile cleaning process done!\n\e[0m"

re: fclean all

.PHONY: clean fclean re all
