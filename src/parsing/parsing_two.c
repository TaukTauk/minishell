/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:35:52 by talin             #+#    #+#             */
/*   Updated: 2025/03/14 12:31:23 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_parse_in_red(t_command **command_list,
	t_command **current_cmd, t_lexer **current, t_data *data)
{
	(void)data;

	if (!*current_cmd)
	{
		*command_list = create_command();
		if (!*command_list)
		{
			ft_putendl_fd("minishell: failed to allocate memory for command", 2);
			return (0);
		}
		*current_cmd = *command_list;
	}
	
	if (!ft_parse_in_red_two(command_list, current_cmd, current))
		return (0);
	
	return (1);
}

int	ft_parse_out_red_two(t_command **command_list,
	t_command **current_cmd, t_lexer **current, t_data *data)
{
	int			redirect_type;
	t_lexer		*next_token;
	(void)data;
	
	redirect_type = ((*current)->token_type == TKN_OUT) ? 
		REDIRECT_OUTPUT : REDIRECT_APPEND;
	next_token = get_next_token(*current);
	if (!next_token || next_token->token_type != TKN_WORD)
	{
		ft_putendl_fd("minishell: missing output file", 2);
		return (free_commands(*command_list), 0);
	}
	
	(*current_cmd)->red_order++;
	(*current_cmd)->output_order = (*current_cmd)->red_order;
	if (!create_io_file(&(*current_cmd)->redirections,
			next_token->value, redirect_type,
			(*current_cmd)->output_order))
	{
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
			ft_putendl_fd("minishell: failed to allocate memory for command", 2);
			return (0);
		}
		*current_cmd = *command_list;
	}
	
	if (!ft_parse_out_red_two(command_list, current_cmd, current, data))
		return (0);
	
	return (1);
}

int	ft_parse_cmd_arg(t_command **command_list,
	t_command **current_cmd, char *token_value)
{
	if (!*current_cmd)
	{
		*command_list = create_command();
		if (!*command_list)
		{
			perror("Error: Failed to allocate memory for command");
			return (0);
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

// int	ft_empty_token(t_data *data, int index)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->lexer->token_count && data->empty_list[i] != -1)
// 	{
// 		if (data->empty_list[i] == index)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

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
			if (!ft_parse_cmd_arg(command_list, current_cmd, (*current)->value))
				return (0);
	}
	return (1);
}

// int	parse_tokens_statement(t_command **command_list, \
// t_command **current_cmd, int *i, t_data *data)
// {
// 	char	*token;

// 	token = data->lexer->tokens[*i];
// 	if (ft_strcmp(token, "|") == 0)
// 	{
// 		if (!ft_parse_pipe(command_list, current_cmd))
// 			return (0);
// 	}
// 	else if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
// 	{
// 		if (!ft_parse_in_red(command_list, current_cmd, i, data))
// 			return (0);
// 	}
// 	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
// 	{
// 		if (!ft_parse_out_red(command_list, current_cmd, i, data))
// 			return (0);
// 	}
// 	else
// 	{
// 		if (!ft_empty_token(data, *i))
// 			if (!ft_parse_cmd_arg(command_list, current_cmd, token))
// 				return (0);
// 	}
// 	return (1);
// }
