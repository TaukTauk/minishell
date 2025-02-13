/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:35:52 by talin             #+#    #+#             */
/*   Updated: 2025/01/20 13:36:06 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_parse_in_red(t_command **command_list, \
t_command **current_cmd, int *i, t_lexer *lexer)
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
	if (*i + 1 < lexer->token_count)
	{
		if (!ft_parse_in_red_two(command_list, current_cmd, i, lexer))
			return (0);
	}
	else
	{
		perror("Syntax error: Missing input file");
		return (free_commands(*command_list), 0);
	}
	return (1);
}

int	ft_parse_out_red_two(t_command **command_list, \
t_command **current_cmd, int *i, t_lexer *lexer)
{
	char	*token;

	token = lexer->tokens[*i];
	if (ft_strcmp(token, ">") == 0)
	{
		(*current_cmd)->outfile = create_io_file(lexer->tokens[++(*i)], \
		REDIRECT_OUTPUT);
		if (!(*current_cmd)->outfile)
		{
			perror("Error: malloc for input redirection file");
			return (free_commands(*command_list), 0);
		}
	}
	else
	{
		(*current_cmd)->outfile = create_io_file(lexer->tokens[++(*i)], \
		REDIRECT_APPEND);
		if (!(*current_cmd)->outfile)
		{
			perror("Error: malloc for input redirection file");
			return (free_commands(*command_list), 0);
		}
	}
	return (1);
}

int	ft_parse_out_red(t_command **command_list, \
t_command **current_cmd, int *i, t_lexer *lexer)
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
	if (*i + 1 < lexer->token_count)
	{
		if (!ft_parse_out_red_two(command_list, current_cmd, i, lexer))
			return (0);
	}
	else
	{
		perror("Syntax error: Missing output file");
		return (free_commands(*command_list), 0);
	}
	return (1);
}

int	ft_parse_cmd_arg(t_command **command_list, \
t_command **current_cmd, char *token)
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
		(*current_cmd)->cmd = ft_strdup(token);
		if (!(*current_cmd)->cmd)
			return (free_commands(*command_list), 0);
		if (!add_argument(*current_cmd, token))
			return (free_commands(*command_list), 0);
	}
	else
		if (!add_argument(*current_cmd, token))
			return (free_commands(*command_list), 0);
	return (1);
}

int	parse_tokens_statement(t_command **command_list, \
t_command **current_cmd, int *i, t_lexer *lexer)
{
	char	*token;

	token = lexer->tokens[*i];
	if (ft_strcmp(token, "|") == 0)
	{
		if (!ft_parse_pipe(command_list, current_cmd))
			return (0);
	}
	else if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
	{
		if (!ft_parse_in_red(command_list, current_cmd, i, lexer))
			return (0);
	}
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
	{
		if (!ft_parse_out_red(command_list, current_cmd, i, lexer))
			return (0);
	}
	else
	{
		if (!ft_parse_cmd_arg(command_list, current_cmd, token))
			return (0);
	}
	return (1);
}
