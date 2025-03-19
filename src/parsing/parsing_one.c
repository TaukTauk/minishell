/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:36:53 by talin             #+#    #+#             */
/*   Updated: 2025/03/19 22:53:32 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		return (ft_error_in_red_two(data, command_list), 0);
	(*current_cmd)->redirections->error = next_token->error;
	(*current_cmd)->redirections->expand = next_token->expand;
	return (*current = next_token, 1);
}
