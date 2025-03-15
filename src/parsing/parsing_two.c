/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:35:52 by talin             #+#    #+#             */
/*   Updated: 2025/03/15 17:38:20 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_parse_in_red(t_command **command_list,
	t_command **current_cmd, t_lexer **current, t_data *data)
{
	if (!*current_cmd)
	{
		*command_list = create_command();
		if (!*command_list)
		{
			ft_putendl_fd("minishell: failed to allocate memory for command", 2);
			data->status = 2;
			return (free_commands(*command_list), 0);
		}
		*current_cmd = *command_list;
	}
	if (!ft_parse_in_red_two(command_list, current_cmd, current, data))
		return (0);
	return (1);
}

int	ft_parse_out_red_two(t_command **command_list,
	t_command **current_cmd, t_lexer **current, t_data *data)
{
	int			redirect_type;
	t_lexer		*next_token;

	if ((*current)->token_type == TKN_OUT)
		redirect_type = REDIRECT_OUTPUT;
	else
		redirect_type = REDIRECT_APPEND;
	next_token = get_next_token(*current);
	if (!next_token || next_token->token_type != TKN_WORD)
	{
		data->status = 2;
		ft_putendl_fd("minishell: missing output file", 2);
		return (free_commands(*command_list), 0);
	}
	(*current_cmd)->red_order++;
	(*current_cmd)->output_order = (*current_cmd)->red_order;
	if (!create_io_file(&(*current_cmd)->redirections,
			next_token->value, redirect_type,
			(*current_cmd)->output_order))
	{
		data->status = 2;
		ft_putendl_fd("minishell: malloc for output redirection file", 2);
		return (free_commands(*command_list), 0);
	}
	*current = next_token;
	return (1);
}

int	ft_parse_out_red(t_command **command_list,
	t_command **current_cmd, t_lexer **current, t_data *data)
{
	if (!*current_cmd)
	{
		*command_list = create_command();
		if (!*command_list)
		{
			data->status = 2;
			ft_putendl_fd("minishell: failed to allocate memory for command", 2);
			return (free_commands(*command_list), 0);
		}
		*current_cmd = *command_list;
	}
	if (!ft_parse_out_red_two(command_list, current_cmd, current, data))
		return (0);
	
	return (1);
}

int	ft_parse_cmd_arg(t_command **command_list,
	t_command **current_cmd, char *token_value, t_data *data)
{
	if (!*current_cmd)
	{
		*command_list = create_command();
		if (!*command_list)
		{
			data->status = 2;
			ft_putendl_fd("minishell: failed to allocate memory for command", 2);
			return (free_commands(*command_list), 0);
		}
		*current_cmd = *command_list;
	}
	if (!(*current_cmd)->cmd)
	{
		(*current_cmd)->cmd = ft_strdup(token_value);
		if (ft_check_builtin((*current_cmd)->cmd))
			(*current_cmd)->builtin = 1;
		if (!(*current_cmd)->cmd)
			return (free_commands(*command_list), 0);
		if (!add_argument(*current_cmd, token_value))
			return (free_commands(*command_list), 0);
	}
	else
		if (!add_argument(*current_cmd, token_value))
			return (free_commands(*command_list), 0);
	return (1);
}

int	parse_tokens_statement(t_command **command_list,
	t_command **current_cmd, t_lexer **current, t_data *data)
{
	int token_type;

	if (!*current)
		return (1);
	token_type = (*current)->token_type;
	if (token_type == TKN_PIPE)
	{
		if (!ft_parse_pipe(command_list, current_cmd))
			return (0);
	}
	else if (token_type == TKN_IN || token_type == TKN_RDHEREDOC)
	{
		if (!ft_parse_in_red(command_list, current_cmd, current, data))
			return (0);
	}
	else if (token_type == TKN_OUT || token_type == TKN_RDAPPEND)
	{
		if (!ft_parse_out_red(command_list, current_cmd, current, data))
			return (0);
	}
	else if (token_type == TKN_WORD)
	{
		if (!(*current)->error)
			if (!ft_parse_cmd_arg(command_list, current_cmd, (*current)->value, data))
				return (0);
	}
	return (1);
}
