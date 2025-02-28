/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:35:52 by talin             #+#    #+#             */
/*   Updated: 2025/02/28 14:47:14 by rick             ###   ########.fr       */
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
		if (!create_io_file(&(*current_cmd)->outfile, lexer->tokens[++(*i)], REDIRECT_OUTPUT))
		{
			perror("Error: malloc for input redirection file");
			return (free_commands(*command_list), 0);
		}
	}
	else
	{
		if (!create_io_file(&(*current_cmd)->outfileappend, lexer->tokens[++(*i)], REDIRECT_APPEND))
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

int	ft_check_builtin(char *cmd)
{
	const char	*builtin[] = {"env", "pwd", "echo", "export", "unset", "cd", "exit"};
	int			i;

	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(cmd,builtin[i]) == 0)
			return (1);
	}
	return (0);
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
		if (ft_check_builtin((*current_cmd)->cmd))
			(*current_cmd)->builtin = 1;
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
