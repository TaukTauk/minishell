/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:38 by talin             #+#    #+#             */
/*   Updated: 2025/02/18 14:56:02 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <term.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# define ERROR_INVALID_QUOTE 1
# define ERROR_INVALID_REDIRECTION 2
# define ERROR_INVALID_PIPE 3

typedef struct s_lexer
{
	char	**tokens;
	int		token_count;
}	t_lexer;

typedef struct s_io_file
{
	char	*file_name;
	int		redirect_type;
}	t_io_file;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	t_io_file			*infile;
	t_io_file			*outfile;
	t_io_file			*delimeter;
	struct s_command	*next;
}	t_command;

typedef enum e_redirect_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC
}	t_redirect_type;

typedef struct s_data
{
	char		**env;
	t_command	*commands;
}	t_data;

int			ft_isspace(const char str);
size_t		ft_strnlen(const char *s, size_t max_len);
char		*ft_strndup(const char *s, size_t n);
void		add_token(t_lexer *lexer, char *token);
t_lexer		*tokenize(char *input);
void		free_lexer(t_lexer *lexer);
size_t		ft_strcspn(const char *str, const char *reject);
int			ft_tokenize_four(t_lexer *lexer, char *input);
int			ft_tokenize_three(t_lexer *lexer, char *input, int *i);
int			ft_tokenize_two(t_lexer *lexer, char *input, int *i);
int			ft_tokenize_one(t_lexer *lexer, char *input, int *i);
void		free_commands(t_command *cmd);
void		ft_free_io_file(t_io_file *file);
void		print_commands(t_command *cmd);
t_command	*parse_tokens(t_lexer *lexer);
int			add_argument(t_command *cmd, char *arg);
t_command	*create_command(void);
t_io_file	*create_io_file(char *file_name, int redirect_type);
int			ft_strcmp(const char *s1, const char *s2);
int			sanitize_tokens(char **tokens);
int			ft_parse_pipe(t_command **command_list, t_command **current_cmd);
int			ft_parse_in_red_two(t_command **command_list, \
t_command **current_cmd, int *i, t_lexer *lexer);
int			ft_parse_in_red(t_command **command_list, \
t_command **current_cmd, int *i, t_lexer *lexer);
int			ft_parse_out_red_two(t_command **command_list, \
t_command **current_cmd, int *i, t_lexer *lexer);
int			ft_parse_out_red(t_command **command_list, \
t_command **current_cmd, int *i, t_lexer *lexer);
int			ft_parse_cmd_arg(t_command **command_list, \
t_command **current_cmd, char *token);
int			parse_tokens_statement(t_command **command_list, \
t_command **current_cmd, int *i, t_lexer *lexer);
int			parameter_expansion(t_lexer *tokens, char **env);
int			execute_commands(t_data *data);
#endif