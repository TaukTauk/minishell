/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:38 by talin             #+#    #+#             */
/*   Updated: 2025/03/20 13:19:07 by talin            ###   ########.fr       */
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
# include <dirent.h>
# include <limits.h>

# define ERROR_INVALID_QUOTE 1
# define ERROR_INVALID_REDIRECTION 2
# define ERROR_INVALID_PIPE 3

extern volatile sig_atomic_t	g_delim_interrupt;

typedef enum e_token_type
{
	TKN_IN,
	TKN_OUT,
	TKN_RDAPPEND,
	TKN_RDHEREDOC,
	TKN_PIPE,
	TKN_WORD
}	t_token_type;

typedef struct s_lexer
{
	int				token_type;
	char			*value;
	int				error;
	int				expand;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_redirection
{
	int						type;
	char					*file_name;
	char					*content;
	int						order_value;
	int						error;
	int						expand;
	struct s_redirection	*next;
}	t_redirection;

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
	t_redirection		*redirections;
	int					builtin;
	int					fd_in;
	int					fd_out;
	int					red_order;
	int					input_order;
	int					output_order;
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
void		add_token(t_lexer **lexer, int token_type, char *value);
t_lexer		*tokenize(char *input, t_data *data);
char		*ft_tokenize_two_token(int start,
				int *i, char *input, t_data *data);
void		tokenize_three(char *input, int *i, int *in_quotes);
t_lexer		*get_token_at_index(t_lexer *lexer, int index);
int			get_token_count(t_lexer *lexer);
void		free_lexer(t_lexer *lexer);
int			get_token_type(char *token);
void		add_token(t_lexer **lexer, int token_type, char *value);
t_lexer		*new_lexer_node(int token_type, char *value);
size_t		ft_strcspn(const char *str, const char *reject);
int			ft_tokenize_four(t_lexer **lexer, char *input, t_data *data);
int			ft_tokenize_three(t_lexer **lexer,
				char *input, int *i, t_data *data);
int			ft_tokenize_two(t_lexer **lexer, char *input, int *i, t_data *data);
int			ft_tokenize_one(t_lexer **lexer, char *input, int *i);
void		free_commands(t_command *cmd);
void		ft_free_io_file(t_redirection *file);
t_command	*parse_tokens(t_lexer *lexer, t_data *data);
int			add_argument(t_command *cmd, char *arg);
t_command	*create_command(void);
int			create_io_file(t_redirection **file_list, char *file_name,
				int redirect_type, int order_num);
int			ft_strcmp(const char *s1, const char *s2);
int			sanitize_tokens(t_lexer *lexer, t_data *data);
char		*expand_variable(char *input, t_data *data);
int			ft_parse_pipe(t_command **command_list, t_command **current_cmd);
int			ft_parse_in_red_two(t_command **command_list,
				t_command **current_cmd, t_lexer **current, t_data *data);
t_lexer		*get_next_token(t_lexer *current);
int			ft_parse_in_red(t_command **command_list,
				t_command **current_cmd, t_lexer **current, t_data *data);
int			ft_parse_out_red_two(t_command **command_list,
				t_command **current_cmd, t_lexer **current, t_data *data);
int			ft_parse_out_red(t_command **command_list,
				t_command **current_cmd, t_lexer **current, t_data *data);
int			ft_parse_cmd_arg(t_command **command_list, \
t_command **current_cmd, char *token, t_data *data);
int			parse_tokens_statement(t_command **command_list,
				t_command **current_cmd, t_lexer **current, t_data *data);
int			parameter_expansion(t_lexer **tokens, t_data *data);
int			execute_commands(t_data *data);
int			execute_command(t_data *data);
void		clear_pipeline(t_data *data, pid_t *pids, int **pipe_fds);
void		close_both(int fd1, int fd2);
void		write_pipe(int fd[2], t_command *command);
void		execute_in_child(char *cmd_path, t_command *command, t_data *data);
void		execute_piped_command(t_command *command, t_data *data);
int			execute_builtin(t_command *commands, t_data *data);
void		ft_free_arr(char **arr);
char		*ft_getenv(char *name, char **envp);
int			ft_check_set_unset(char **envp);
char		*ft_get_path(char *cmd, char **envp, int i, t_data *data);
void		execve_cmd(char *cmd, char **s_cmd, char **envp, t_data *data);
void		update_exit_status(pid_t pid, int fd[2], t_data *data);
void		handle_execution_status(pid_t pid, t_data *data);
void		print_err_nofile(char *filename, t_data *data);
void		close_err(int fd1, int fd2);
void		ft_error(const char *message);
void		handle_execution_error(t_command *command,
				t_data *data, char *cmd_path, int error_type);
void		cleanup_redirections(t_command *command);
int			handle_redirections(t_command *command, t_data *data);
void		set_up_pipes(t_data *data, int **pipe_fds);
void		close_pipes(t_data *data, int **pipe_fds);
void		setup_child_pipes(t_data *data, int **pipe_fds, int i);
void		run_piped_command(t_data *data, int **pipe_fds, int i);
void		create_pipelines(t_data *data, pid_t *pids, int **pipe_fds);
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
int			delimeter_content(t_redirection *delimeter);
int			delimeter_append(t_redirection *delimeter, char *line);
int			delimeter_lines(t_redirection *delimeter, t_data *data);
int			delimeter_expand(t_redirection *delimeter, t_data *data);
int			delimeter_read(t_redirection *delimeter,
				t_command *command, t_data *data);
int			ft_echo(t_command *command, t_data *data);
int			ft_cd(t_command *command, t_data *data);
int			ft_exit(t_command *command, t_data *data);
void		error_args(char *command, t_data *data);
void		error_not_found(char *path, t_data *data);
void		error_permission(char *command, t_data *data);
void		error_directory(char *command, t_data *data);
char		*get_target(t_command *command, t_data *data);
char		*get_path(t_data *data, char *variable);
char		*ft_strcpy(char *dest, const char *src);
void		add_env(t_data *data, const char *key, const char *value, int sign);
int			update_pwd(t_data *data, const char *old_pwd);
void		error_numeric(char *command, t_data *data);
void		ft_export(t_command *commands, t_data *data);
void		ft_unset(t_command *commands, t_data *data);
size_t		calculate_expanded_size(const char *input, t_data *data);
void		ft_quote_handle(char **ptr, int *inside_single_quote,
				int *inside_double_quote);
void		get_value(char **ptr, t_data *data, char **output_ptr);
int			ft_is_valid_name_character(const char c);
char		*get_env_value(char *env[], const char *var_name);
void		remove_quote(char **str);
int			ft_check_builtin(char *cmd);
void		free_data(t_data *data);
void		free_envp(t_envp *envp);
void		free_command(t_command *cmd);
void		free_io_file(t_redirection *file);
char		*ft_multjoin(char **arr_str);
void		free_env(t_data *data);
void		free_environ(char **envp);
t_envp		*env_find(t_envp *envp, const char *key);
void		init_env(t_data *data);
void		add_env(t_data *data, const char *key, const char *value, int sign);
void		gen_env(t_data *data);
void		init_shell(t_data *data, char **envp);
void		update_shlvl(t_data *data);
void		handle_sigint(int signum);
int			ft_is_only_space(char *input);
int			ft_check_exec_access(char *path);
int			handle_heredoc(t_redirection *redir,
				t_command *command, t_data *data);
int			handle_input_file(t_redirection *redir,
				t_command *command, t_data *data);
int			handle_output_redirection(t_redirection *redir,
				t_command *command, t_data *data);
int			is_valid_variable_name(const char *name);
int			export_env_new(char *key, char *value,
				t_envp **envp, t_data **data);
int			export_env_search(t_envp *current, char *key, char *value);
void		handle_sigquit(int sig);
void		handle_sigint_two(int sig);
char		*ft_get_exec_path(char *cmd, char **allpath, int i);
char		*ft_get_home_path(char *cmd, char **envp);
void		free_command_lexer_in_exec(t_data *data);
int			ft_check_file_type(const char *path);
int			is_directory_character(char *cmd);
void		ft_error_directory(char *exec, t_data *data, int status);
char		*ft_get_exec_path(char *cmd, char **allpath, int i);
char		*ft_get_home_path(char *cmd, char **envp);
int			ft_contain_dollar_sign(char *cmd);
int			ft_is_empty(char *str);
int			empty_or_not(char *token);
int			expand_var(char **cmd, t_data *data, t_lexer **lexer, int *status);
int			is_valid_redirection(t_lexer *token, t_lexer *next_token);
int			check_unclosed_quotes(const char *token);
int			is_metacharacter(t_lexer *token);
int			single_quote_token(char *value);
void		ft_str_copy(char *dest, const char *src);
void		ft_error_in_red_two(t_data *data, t_command **command_list);
void		error_out_red_two(t_data *data, t_command **command_list);
int			empty_directory(char *dest_path);
#endif