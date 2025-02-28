/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:38 by talin             #+#    #+#             */
/*   Updated: 2025/02/28 15:12:11 by rick             ###   ########.fr       */
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
	char				*file_name;
	int					redirect_type;
	char				*content;
	struct s_io_file	*next;
}	t_io_file;

typedef struct s_envp
{
	char					*key;
	char					*value;
	int						sign;
	struct s_envp			*next;
}	t_envp;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	t_io_file			*infile;
	t_io_file			*outfile;
	t_io_file			*delimeter;
	t_io_file			*outfileappend;
	int					builtin;
	int					fd_in;
	int					fd_out;
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
	t_envp		*envp;
	size_t		env_len;
	t_lexer		*lexer;
	int			cmd_count;
	int			status;
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
t_command	*parse_tokens(t_lexer *lexer, t_data *data);
int			add_argument(t_command *cmd, char *arg);
t_command	*create_command(void);
int			create_io_file(t_io_file **file_list, char *file_name, int redirect_type);
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
int 		execute_command(t_data *data);
void		cleanup_pipeline(t_data *data, pid_t *pids, int **pipe_fds);
void		close_both(int fd1, int fd2);
void		write_pipe(int fd[2], t_command *command);
void		execute_in_child(char *cmd_path, t_command *command, t_data *data);
void		execute_piped_command(t_command *command, t_data *data);
char		**realloc_env(char **env, int size);
int 		is_valid_identifier(const char *str);
void		export_env(char ***env, char *var);
void		unset_env(char **env, char *var);
int			execute_builtin(t_command *commands, t_data *data);
void		ft_free_arr(char **arr);
char		*ft_getenv(char *name, char **envp);
int			ft_check_set_unset(char **envp);
char		*ft_get_path(char *cmd, char **envp, int i);
void		execve_cmd(char *cmd, char **s_cmd, char **envp);
void		update_exit_status(pid_t pid, int fd[2], t_data *data);
void		handle_execution_status(pid_t pid, t_data *data);
void		print_err_nofile(char *filename, t_data *data);
void		close_err(int fd1, int fd2);
void		ft_error(const char *message);
void		handle_execution_error(t_command *command, t_data *data, char *cmd_path, int error_type);
void		cleanup_redirections(t_command *command);
int			handle_redirections(t_command *command, t_data *data);
void		setup_pipes(t_data *data, int **pipe_fds);
void		close_pipes(t_data *data, int **pipe_fds);
void		setup_child_pipes(t_data *data, int **pipe_fds, int i);
void		run_piped_command(t_data *data, int **pipe_fds, int i);
void		create_pipeline_processes(t_data *data, pid_t *pids, int **pipe_fds);
int			setup_delimeter(t_command *command, t_data *data);
int			setup_input_redirection(t_command *command, t_data *data);
int			setup_output_redirection(t_data *data, t_command *command);
void		error_malloc(t_data *data);
void		error_eof(char *token, t_data *data);
char		*env_name(const char **input);
void		error_syntax(char *token, t_data *data);
char		*env_value(t_data *data, const char *key);
void		error_file_not_found(char *path, t_data *data);
char		*expand_var_two(const char **pointer, t_data *data);
char		*expand_exit(t_data *data);
char		*expand_single(const char **string, t_data *data);
char		*expand_append(char *result, char *expanded, t_data *data);
char		*quote_expand(char *string, t_data *data);
void		error_delimeter(char *delimiter);
int			delimeter_content(t_io_file *delimeter);
int			delimeter_append(t_io_file *delimeter, char *line);
int			delimeter_lines(t_io_file *delimeter);
void		delimeter_expand(t_io_file *delimeter, t_data *data);
void		delimeter_read(t_io_file *delimeter, t_command *command, t_data *data);
#endif