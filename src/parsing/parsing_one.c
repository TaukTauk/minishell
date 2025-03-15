/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:36:53 by talin             #+#    #+#             */
/*   Updated: 2025/03/15 17:13:45 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_io_file(t_redirection **file_list,
		char *file_name, int redirect_type, int order_num)
{
	t_redirection	*new_file;
	t_redirection	*last;

	if (!file_name)
		return (0);
	new_file = malloc(sizeof(t_redirection));
	if (!new_file)
		return (0);
	new_file->file_name = ft_strdup(file_name);
	if (!new_file->file_name)
		return (0);
	new_file->type = redirect_type;
	new_file->order_value = order_num;
	new_file->content = NULL;
	new_file->next = NULL;
	if (!(*file_list))
		*file_list = new_file;
	else
	{
		last = *file_list;
		while (last->next)
			last = last->next;
		last->next = new_file;
	}
	return (1);
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->builtin = 0;
	cmd->input_order = 0;
	cmd->output_order = 0;
	cmd->red_order = 0;
	cmd->next = NULL;
	return (cmd);
}

int	add_argument(t_command *cmd, char *arg)
{
	int		arg_count;
	char	**new_args;
	int		i;

	arg_count = 0;
	if (!arg)
		return (0);
	if (cmd->args)
		while (cmd->args[arg_count])
			arg_count++;
	new_args = malloc(sizeof(char *) * (arg_count + 2));
	if (!new_args)
		return (0);
	i = -1;
	while (++i < arg_count)
		new_args[i] = cmd->args[i];
	free(cmd->args);
	new_args[arg_count] = ft_strdup(arg);
	if (!new_args[arg_count])
		return (0);
	new_args[arg_count + 1] = NULL;
	(cmd->args = new_args);
	return (1);
}

int	ft_parse_pipe(t_command **command_list, t_command **current_cmd)
{
	if (!*current_cmd)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token '|'", 2);
		return (free_commands(*command_list), 0);
	}
	(*current_cmd)->next = create_command();
	if (!(*current_cmd)->next)
	{
		ft_putendl_fd("minishell: failed to allocate memory for command", 2);
		return (free_commands(*command_list), 0);
	}
	(*current_cmd) = (*current_cmd)->next;
	return (1);
}

t_lexer	*get_next_token(t_lexer *current)
{
	if (!current)
		return (NULL);
	return (current->next);
}

int	ft_parse_in_red_two(t_command **command_list, 
	t_command **current_cmd, t_lexer **current, t_data *data)
{
	int			redirect_type;
	t_lexer		*next_token;
	
	if ((*current)->token_type == TKN_IN)
		redirect_type = REDIRECT_INPUT;
	else
		redirect_type = REDIRECT_HEREDOC;
	next_token = get_next_token(*current);
	if (!next_token || next_token->token_type != TKN_WORD)
	{
		data->status = 2;
		ft_putendl_fd("minishell: missing input file", 2);
		return (free_commands(*command_list), 0);
	}
	(*current_cmd)->red_order++;
	(*current_cmd)->input_order = (*current_cmd)->red_order;
	if (!create_io_file(&(*current_cmd)->redirections,
			next_token->value, redirect_type,
			(*current_cmd)->input_order))
	{
		data->status = 2;
		ft_putendl_fd("minishell: malloc for input redirection file", 2);
		return (free_commands(*command_list), 0);
	}
	*current = next_token;
	return (1);
}
